#!/usr/bin/env python3
"""Class/adapter regressions for the upstream bounded migration runners."""
from __future__ import annotations
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))
from split_source_index import body_sha256, scan_definitions

MARKER = "/* CLASH95_GENERATED_INCLUDES_END */\n"


class ClassMigrationRunnerTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.anchor = "src/media/example.cpp"
        self.alpha = "src/units/Example.cpp"
        self.beta = "src/units/Second.cpp"
        self.put("src/media/example_view.h", "#pragma once\n")
        self.put("src/units/Example.hpp", "namespace clash95 { struct Example { "
                 "int Alpha(int value) const noexcept; int Beta(int value) const noexcept; }; }\n")
        self.put(self.alpha, '#include "Example.hpp"\n' + MARKER +
                 "int clash95::Example::Alpha(int value) const noexcept\n{ return value + 1; }\n")
        self.put(self.beta, '#include "Example.hpp"\n' + MARKER +
                 "int clash95::Example::Beta(int value) const noexcept\n{ return value + 2; }\n")
        self.put(self.anchor, '#include "../units/Example.hpp"\n' + MARKER +
                 "//----- (00401000) --------------------------------------------------------\n"
                 "int Alpha(int value) { return clash95::Example{}.Alpha(value); }\n"
                 "//----- (00401010) --------------------------------------------------------\n"
                 "int Beta(int value) { return clash95::Example{}.Beta(value); }\n")
        self.manifest = {"schema_version": 3, "cutover": "canonical-split",
                         "legacy_manifest": "clash95.c", "address_marker_count": 2,
                         "functions": []}
        for name, path in (("Alpha", self.alpha), ("Beta", self.beta)):
            self.manifest["functions"].append({
                "name": name, "source": path,
                "original_address": "0x00401000" if name == "Alpha" else "0x00401010",
                "body_sha256": self.digest(path, "clash95::Example::" + name),
                "legacy_body_sha256": "9" * 64,
                "implementation": {"kind": "method", "qualified_name": "clash95::Example::" + name},
                "adapter": {"source": self.anchor, "body_sha256": self.digest(self.anchor, name)},
            })
        self.write_manifest()
        self.put("data/recovered_decls.json", json.dumps({"functions": {}}))
        self.spec_path = "data/readability_migrations/example.json"
        self.spec = {"schema_version": 1, "source": self.anchor,
                     "includes": ["example_view.h"], "functions": [{
                         "name": "Alpha", "expected_body_sha256": self.record("Alpha")["body_sha256"],
                         "replacement_body": "{ return value + 3; }"}]}
        self.write_spec()

    def put(self, path, text):
        target = self.root / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding="utf-8")

    def replace(self, path, old, new):
        self.put(path, (self.root / path).read_text().replace(old, new))

    def digest(self, path, name):
        text = (self.root / path).read_text()
        definition, = scan_definitions(text, {name})
        return body_sha256(text, definition)

    def record(self, name):
        return next(record for record in self.manifest["functions"] if record["name"] == name)

    def write_manifest(self):
        self.put("data/recovered_sources.json", json.dumps(self.manifest, indent=2) + "\n")

    def write_spec(self):
        self.put(self.spec_path, json.dumps(self.spec, indent=2) + "\n")

    def snapshot(self):
        return {str(path.relative_to(self.root)): path.read_bytes()
                for path in self.root.rglob("*") if path.is_file()}

    def run_tool(self, name, *args):
        return subprocess.run([sys.executable, str(REPO / "tools" / name),
                               "--root", str(self.root), *args],
                              text=True, capture_output=True)

    def hash_update(self, *args):
        return self.run_tool("update_split_manifest_hashes.py", *args)

    def readability(self, *args):
        return self.run_tool("apply_readability_migration.py", self.spec_path, *args)

    def test_selected_canonical_and_adapter_update_preserves_history_and_schema(self):
        self.replace(self.alpha, "+ 1", "+ 5")
        self.replace(self.anchor, ".Alpha(value)", ".Alpha(value + 1)")
        untouched = dict(self.record("Beta"))
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        updated = json.loads((self.root / "data/recovered_sources.json").read_text())
        self.assertEqual(updated["schema_version"], 3)
        self.assertEqual(updated["address_marker_count"], 2)
        alpha, beta = updated["functions"]
        self.assertEqual(beta, untouched)
        self.assertEqual(alpha["legacy_body_sha256"], "9" * 64)
        self.assertEqual(alpha["body_sha256"], self.digest(self.alpha, "clash95::Example::Alpha"))
        self.assertEqual(alpha["adapter"]["body_sha256"], self.digest(self.anchor, "Alpha"))
        self.assertEqual(self.hash_update().returncode, 0)

    def test_adapter_only_refresh_does_not_create_historical_body_hash(self):
        self.record("Alpha").pop("legacy_body_sha256")
        self.write_manifest()
        self.replace(self.anchor, ".Alpha(value)", ".Alpha(value + 1)")
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        updated = json.loads((self.root / "data/recovered_sources.json").read_text())
        self.assertNotIn("legacy_body_sha256", updated["functions"][0])

    def test_unselected_adapter_drift_rejects_all_writes(self):
        self.replace(self.alpha, "+ 1", "+ 5")
        self.replace(self.anchor, ".Beta(value)", ".Beta(value + 1)")
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 1)
        self.assertIn("Beta: adapter body hash differs outside --only selection", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_unselected_method_drift_rejects_all_writes(self):
        self.replace(self.alpha, "+ 1", "+ 5")
        self.replace(self.beta, "+ 2", "+ 8")
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 1)
        self.assertIn("Beta: canonical body hash differs outside --only selection", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_qualified_selector_rejected_in_favor_of_historical_identity(self):
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "clash95::Example::Alpha")
        self.assertEqual(result.returncode, 1)
        self.assertIn("not present in manifest", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_idempotent_scoped_update_does_not_seed_other_records(self):
        self.record("Beta").pop("legacy_body_sha256")
        self.write_manifest()
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(self.snapshot(), before)

    def test_duplicate_canonical_definition_rejects_hash_update(self):
        self.put(self.alpha, (self.root / self.alpha).read_text() +
                 "int clash95::Example::Alpha(int value) const noexcept { return 0; }\n")
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "Alpha")
        self.assertEqual(result.returncode, 1)
        self.assertIn("found 2", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_readability_changes_qualified_method_and_keeps_adapter_bytes(self):
        anchor = (self.root / self.anchor).read_bytes()
        manifest = (self.root / "data/recovered_sources.json").read_bytes()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        text = (self.root / self.alpha).read_text()
        self.assertIn("clash95::Example::Alpha(int value) const noexcept", text)
        self.assertIn("return value + 3", text)
        self.assertIn('#include "../media/example_view.h"', text)
        self.assertEqual((self.root / self.anchor).read_bytes(), anchor)
        self.assertEqual((self.root / "data/recovered_sources.json").read_bytes(), manifest)
        after = self.snapshot()
        self.assertEqual(self.readability("--write").returncode, 0)
        self.assertEqual(self.snapshot(), after)

    def test_readability_dry_run_preserves_every_file(self):
        before = self.snapshot()
        result = self.readability()
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(self.snapshot(), before)

    def test_readability_can_target_relocated_canonical_path_directly(self):
        self.spec["source"] = self.alpha
        self.spec["includes"] = []
        self.write_spec()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("return value + 3", (self.root / self.alpha).read_text())

    def test_readability_refuses_adapter_body_hash_as_canonical_proof(self):
        self.spec["functions"][0]["expected_body_sha256"] = self.record("Alpha")["adapter"]["body_sha256"]
        self.write_spec()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("matches neither expected", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_readability_stages_all_class_files_before_any_write(self):
        self.spec["functions"].append({"name": "Beta", "expected_body_sha256": "0" * 64,
                                       "replacement_body": "{ return value + 9; }"})
        self.write_spec()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("Beta: current body hash", result.stdout)
        self.assertEqual(self.snapshot(), before)
        self.spec["functions"][1]["expected_body_sha256"] = self.record("Beta")["body_sha256"]
        self.write_spec()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("return value + 3", (self.root / self.alpha).read_text())
        self.assertIn("return value + 9", (self.root / self.beta).read_text())

    def test_readability_refuses_unrelated_spec_source(self):
        self.spec["source"] = "src/media/unrelated.cpp"
        self.write_spec()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("neither canonical nor adapter source", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_readability_refuses_missing_identity_with_a_same_named_free_function(self):
        self.manifest["functions"] = [self.record("Beta")]
        self.write_manifest()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("historical identity is absent", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_readability_method_and_adapter_compile_and_execute_both_compilers(self):
        available = [compiler for compiler in ("g++-13", "clang++-18") if shutil.which(compiler)]
        if len(available) != 2:
            self.skipTest("both supported compilers required")
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.put("main.cpp", '#include "src/units/Example.hpp"\n'
                 "int Alpha(int); int Beta(int);\n"
                 "int main() { return Alpha(4) == 7 && clash95::Example{}.Alpha(4) == 7 "
                 "&& Beta(4) == 6 && clash95::Example{}.Beta(4) == 6 ? 0 : 1; }\n")
        for compiler in available:
            for opt in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, opt=opt):
                    output = self.root / (compiler + opt)
                    compile_result = subprocess.run([compiler, "-std=gnu++20", "-Wall", "-Wextra", "-Werror",
                                                     "-fno-exceptions", "-fno-rtti", opt,
                                                     self.alpha, self.beta, self.anchor, "main.cpp", "-o", str(output)],
                                                    cwd=self.root, text=True, capture_output=True)
                    self.assertEqual(compile_result.returncode, 0, compile_result.stdout + compile_result.stderr)
                    self.assertEqual(subprocess.run([str(output)]).returncode, 0)

    def add_historical_alias(self, source=None):
        source = source or self.anchor
        body = "int FormerAlpha(int value) { return Alpha(value); }\n"
        if source == self.anchor:
            self.put(source, (self.root / source).read_text() + body)
        else:
            self.put(source, "int Alpha(int);\n" + body)
        self.record("Alpha")["historical_names"] = ["FormerAlpha"]
        self.record("Alpha")["compatibility_aliases"] = [{
            "name": "FormerAlpha", "source": source,
            "body_sha256": self.digest(source, "FormerAlpha"),
            "reason": "Preserve the prior recovered spelling at its original anchor.",
        }]
        self.write_manifest()
        self.spec["functions"][0]["name"] = "FormerAlpha"
        self.spec["source"] = source
        self.spec["includes"] = []
        self.write_spec()

    def test_scoped_hash_selection_resolves_historical_alias_to_canonical_record(self):
        self.add_historical_alias()
        self.replace(self.alpha, "+ 1", "+ 7")
        before_alias = (self.root / self.anchor).read_bytes()
        result = self.hash_update("--update", "--only", "FormerAlpha")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        updated = json.loads((self.root / "data/recovered_sources.json").read_text())
        self.assertEqual(updated["functions"][0]["name"], "Alpha")
        self.assertEqual(updated["functions"][0]["body_sha256"],
                         self.digest(self.alpha, "clash95::Example::Alpha"))
        self.assertEqual(updated["functions"][0]["historical_names"], ["FormerAlpha"])
        self.assertEqual(updated["functions"][0]["compatibility_aliases"],
                         self.record("Alpha")["compatibility_aliases"])
        self.assertEqual((self.root / self.anchor).read_bytes(), before_alias)

    def test_scoped_hash_selection_rejects_ambiguous_historical_alias(self):
        self.add_historical_alias()
        self.record("Beta")["historical_names"] = ["FormerAlpha"]
        self.write_manifest()
        before = self.snapshot()
        result = self.hash_update("--update", "--only", "FormerAlpha")
        self.assertEqual(result.returncode, 1)
        self.assertIn("ambiguous historical identity", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_historical_alias_spec_resolves_only_actual_canonical_method(self):
        self.add_historical_alias()
        alias_bytes = (self.root / self.anchor).read_bytes()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("return value + 3", (self.root / self.alpha).read_text())
        self.assertEqual((self.root / self.anchor).read_bytes(), alias_bytes)

    def test_historical_alias_source_is_accepted_after_class_relocation(self):
        alias_source = "src/core/old_alias.cpp"
        self.add_historical_alias(alias_source)
        before_alias = (self.root / alias_source).read_bytes()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("return value + 3", (self.root / self.alpha).read_text())
        self.assertEqual((self.root / alias_source).read_bytes(), before_alias)

    def test_historical_alias_body_hash_is_never_canonical_proof(self):
        self.add_historical_alias()
        self.spec["functions"][0]["expected_body_sha256"] = self.digest(self.anchor, "FormerAlpha")
        self.write_spec()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("matches neither expected", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_ambiguous_historical_alias_rejects_all_writes(self):
        self.add_historical_alias()
        self.record("Beta")["historical_names"] = ["FormerAlpha"]
        self.write_manifest()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("ambiguous historical identity", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_historical_alias_does_not_authorize_unrelated_source(self):
        self.add_historical_alias()
        self.spec["source"] = "src/media/unrelated.cpp"
        self.write_spec()
        before = self.snapshot()
        result = self.readability("--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("neither canonical nor adapter source", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def identity_spec(self):
        path = "data/function_identity_migrations/example.json"
        self.put(path, json.dumps({"schema_version": 1, "old_name": "Alpha", "new_name": "RenamedAlpha",
                                  "source": self.anchor, "compatibility_source": "src/media/stubs.cpp",
                                  "original_address": "0x00401000", "expected_body_sha256": "0" * 64,
                                  "expected_compat_body_sha256": "0" * 64}))
        return path

    def test_identity_rename_refuses_class_backed_metadata_before_writes(self):
        spec = self.identity_spec()
        before = self.snapshot()
        result = self.run_tool("apply_function_identity_migration.py", spec, "--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("class-backed identity migration", result.stdout)
        self.assertEqual(self.snapshot(), before)

    def test_identity_rename_refuses_unmigrated_schema3_history_before_writes(self):
        alpha = self.record("Alpha")
        alpha["implementation"] = {"kind": "free", "qualified_name": "Alpha"}
        alpha.pop("adapter")
        self.write_manifest()
        spec = self.identity_spec()
        before = self.snapshot()
        result = self.run_tool("apply_function_identity_migration.py", spec, "--write")
        self.assertEqual(result.returncode, 1)
        self.assertIn("schema 3 identity migration", result.stdout)
        self.assertEqual(self.snapshot(), before)


if __name__ == "__main__":
    unittest.main()
