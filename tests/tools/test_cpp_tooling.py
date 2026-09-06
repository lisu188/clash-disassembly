#!/usr/bin/env python3
"""C/C++ migration regressions; fixtures never modify canonical sources."""

from __future__ import annotations

import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))

import apply_diag_respells as respells
import audit_c_readability as readability
import audit_header_surface as headers
import audit_split_sources as split
import check_recovered_warnings as warnings
import coverage_source_manifest as coverage
import global_inventory as globals_inventory
import literal_common as literals
import pp_token_diff as tokens
import wire_cov_cases as cases_audit
from split_source_index import body_sha256, scan_definitions


class DefinitionTests(unittest.TestCase):
    def test_enum_guards_retain_shared_c_cpp_body(self):
        source = ('#ifdef __cplusplus\ntypedef enum unit_type : unsigned int\n'
                  '#else\ntypedef enum unit_type\n#endif\n'
                  '{ FIRST = 0, SECOND, LAST = 34 } unit_type;\n')
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'types.h'
            path.write_text(source)
            self.assertEqual(literals.parse_prelude_enums(path),
                             {'FIRST': 0, 'SECOND': 1, 'LAST': 34})

    def test_enum_guards_accept_cpp_underlying_type(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'types.h'
            path.write_text('enum values : unsigned int { FIRST = 1, SECOND };\n')
            self.assertEqual(literals.parse_prelude_enums(path),
                             {'FIRST': 1, 'SECOND': 2})

    def test_linkage_blocks_preserve_function_identity_and_body_hash(self):
        plain = 'int first(void) { return 17; }\nstatic int second(void) { return 20; }\n'
        linked = 'extern "C" {\n' + plain + '}\n'
        original = scan_definitions(plain, {"first", "second"})
        migrated = scan_definitions(linked, {"first", "second"})
        self.assertEqual([d.name for d in migrated], ["first", "second"])
        self.assertEqual([body_sha256(plain, d) for d in original],
                         [body_sha256(linked, d) for d in migrated])
        self.assertEqual([d.line for d in migrated], [2, 3])

    def test_nested_linkage_blocks_and_declarations(self):
        source = ('extern "C" int first(void);\nextern "C++" {\n'
                  'extern "C" {\nint first(void) { return 1; }\n}\n}\n')
        definitions = scan_definitions(source, {"first"})
        self.assertEqual(len(definitions), 1)
        self.assertEqual(definitions[0].line, 4)

    def test_comment_or_literal_does_not_create_linkage_block(self):
        source = ('// extern "C" {\n'
                  'const char *label = "extern \\"C\\" {";\n'
                  'int first(void) { return 1; }\n')
        self.assertEqual([d.name for d in scan_definitions(source, {"first"})], ["first"])

    def test_unbalanced_linkage_block_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "unbalanced language-linkage"):
            scan_definitions('extern "C" {\nint first(void) { return 1; }', {"first"})


class WarningTests(unittest.TestCase):
    def test_cpp_driver_warnings_are_counted(self):
        for compiler, driver in [("gcc", "g++-13"), ("gcc", "cc1plus"),
                                 ("clang", "/usr/bin/clang++-18")]:
            with self.subTest(driver=driver):
                counts, ignored = warnings.warning_counts(
                    f"{driver}: warning: unsupported option [-Wunknown-warning-option]\n"
                    "src/core/example.cpp:2:3: warning: narrow [-Wconversion]\n",
                    compiler, warnings.DEFAULT_SOURCE_PREFIXES)
                self.assertEqual(dict(counts), {"-Wunknown-warning-option": 1,
                                               "-Wconversion": 1})
                self.assertEqual(ignored, 0)

    def test_cpp_driver_detection(self):
        self.assertEqual(warnings.detect_compiler("g++-13 -c example.cpp"), "gcc")
        self.assertEqual(warnings.detect_compiler("GNU C++ version 13.3"), "gcc")
        self.assertEqual(warnings.detect_compiler("clang++-18 -c example.cpp"), "clang")

    def test_c_driver_detection_and_unknown_warning_bucket_remain(self):
        self.assertEqual(warnings.detect_compiler("gcc-13 -c example.c"), "gcc")
        counts, ignored = warnings.warning_counts("cc1: warning: legacy diagnostic\n",
                                                  "gcc", ())
        self.assertEqual(dict(counts), {"gcc/unknown": 1})
        self.assertEqual(ignored, 0)


class SourcePolicyTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "src" / "support").mkdir(parents=True)

    def test_source_inclusion_ban_covers_cpp_sources_and_targets(self):
        (self.root / "src/support/file.cpp").write_text('#include "other.cpp"\n')
        with mock.patch.object(split, "ROOT", self.root):
            audit = split.Audit()
            split.audit_production_layout(audit)
        self.assertTrue(any("other.cpp" in error for error in audit.errors), audit.errors)

    def test_cpp_unified_source_is_rejected(self):
        (self.root / "clash95.cpp").write_text("int f() { return 1; }\n")
        with mock.patch.object(split, "ROOT", self.root):
            audit = split.Audit()
            split.audit_production_layout(audit)
        self.assertIn("unified clash95.cpp still exists", audit.errors)

    def test_cpp_support_cannot_include_test_aggregate(self):
        (self.root / "data").mkdir()
        (self.root / "src/state").mkdir()
        (self.root / "src/state/storage.cpp").write_text("")
        (self.root / "src/support/file.cpp").write_text('#include "recovered_all.h"\n')
        (self.root / "data/recovered_sources.json").write_text(json.dumps({
            "functions": [], "state_owner": "src/state/storage.cpp"}))
        decls = self.root / "data/recovered_decls.json"
        decls.write_text("{}")
        with mock.patch.object(headers, "REPO", self.root), mock.patch.object(headers, "DECLS", decls):
            errors = headers.include_policy_errors()
        self.assertTrue(any("src/support/file.cpp: tests-only aggregate" in e for e in errors), errors)

    def test_tu_local_headers_are_private_to_own_generated_block(self):
        (self.root / "data").mkdir()
        (self.root / "src/core").mkdir()
        sources = ["src/core/first.cpp", "src/core/second.c"]
        (self.root / "data/recovered_sources.json").write_text(json.dumps({
            "functions": [{"source": source} for source in sources], "state_owner": sources[0]}))
        decls = self.root / "data/recovered_decls.json"
        decls.write_text("{}")
        for consumer, include, inside, allowed in [
                (sources[0], "first_local.h", True, True),
                (sources[0], "first_local.h", False, False),
                (sources[1], "first_local.h", True, False),
                (sources[0], "../world/first_local.h", True, False),
                ("src/support/file.cpp", "../core/first_local.h", False, False)]:
            with self.subTest(consumer=consumer, include=include, inside=inside):
                for source in sources + ["src/support/file.cpp"]:
                    (self.root / source).write_text("")
                text = f'#include "{include}"\n'
                if inside:
                    text = headers.MARK_BEGIN + " */\n" + text + headers.MARK_END + "\n"
                (self.root / consumer).write_text(text)
                with mock.patch.object(headers, "REPO", self.root), mock.patch.object(headers, "DECLS", decls):
                    errors = headers.include_policy_errors()
                self.assertEqual(not errors, allowed, errors)

    def test_readability_includes_both_languages(self):
        for suffix in ("c", "cpp", "h", "txt"):
            (self.root / f"src/support/file.{suffix}").write_text("")
        with mock.patch.object(readability, "SRC", self.root / "src"):
            self.assertEqual({p.suffix for p in readability.source_files()}, {".c", ".cpp", ".h"})

    def test_respeller_accepts_cpp_diagnostics_but_not_headers(self):
        text = "\n".join(f"src/core/file.{suffix}:3:4: warning: cast [-Wint-to-pointer-cast]"
                         for suffix in ("c", "cpp", "h"))
        self.assertEqual(set(respells.collect_sites(text, {"int-to-pointer-cast"}, None)),
                         {"src/core/file.c", "src/core/file.cpp"})

    def test_global_inventory_keeps_all_manifest_c_and_cpp_sources(self):
        sources = ["src/support/first.c", "src/support/second.cpp"]
        for source in sources:
            (self.root / source).write_text("")
        with mock.patch.object(globals_inventory, "REPO", str(self.root)):
            self.assertEqual(globals_inventory.recovered_source_files({
                "functions": [{"source": source} for source in sources]}), sources)

    def test_case_audit_requires_cpp_sources_to_be_registered(self):
        case_dir = self.root / "tests/unit/cases"
        case_dir.mkdir(parents=True)
        for suffix in ("c", "cpp"):
            (case_dir / f"test_{suffix}.{suffix}").write_text(f"TEST(Language, {suffix}) {{}}\n")
        cmake = self.root / "CMakeLists.txt"
        for include_cpp in (False, True):
            with self.subTest(include_cpp=include_cpp):
                globs = ["tests/unit/cases/test_*.c"]
                if include_cpp:
                    globs.append("tests/unit/cases/test_*.cpp")
                cmake.write_text("file(GLOB CLASH95_UNIT_CASE_SOURCES\n" + "\n".join(globs)
                                 + ")\nadd_executable(unit ${CLASH95_UNIT_CASE_SOURCES})\n")
                output = io.StringIO()
                with mock.patch.object(cases_audit, "ROOT", self.root), \
                        mock.patch.object(cases_audit, "CASE_DIR", case_dir), \
                        mock.patch.object(cases_audit, "CMAKE", cmake), \
                        mock.patch.object(cases_audit, "LEGACY_AGGREGATE", self.root / "tests/unit/test_all.c"), \
                        mock.patch.object(sys, "argv", ["wire_cov_cases.py", "--json"]), \
                        contextlib.redirect_stdout(output):
                    result = cases_audit.main()
                payload = json.loads(output.getvalue())
                self.assertEqual(payload["case_source_count"], 2)
                self.assertEqual(payload["test_count"], 2)
                self.assertEqual(result, 0 if include_cpp else 1, payload["errors"])

    def manifest_audit(self, root, language, suffixes, extra_source=False):
        (root / "src/core").mkdir(parents=True)
        (root / "data").mkdir()
        sources, records = [], []
        for index, suffix in enumerate(suffixes):
            name = f"retained_{index}"
            source = f"src/core/{name}{suffix}"
            text = f"int {name}(void) {{ return {index}; }}\n"
            (root / source).write_text(text)
            digest = body_sha256(text, scan_definitions(text, {name})[0])
            sources.append(source)
            records.append({"name": name, "source": source, "original_source": "legacy.c",
                            "legacy_path": "legacy.c", "original_line": index + 1,
                            "original_address": None,
                            "original_address_range": {"start": None, "end_exclusive": None},
                            "linkage": "external", "body_sha256": digest,
                            "legacy_body_sha256": digest})
        for record in records:
            record["state_owner"] = sources[0]
        if extra_source:
            (root / "src/core/unlisted.cpp").write_text("int unlisted(void) { return 0; }\n")
        source_list = root / "src/sources.cmake"
        source_list.write_text("set(SOURCES\n" + "".join(f"  {s}\n" for s in sources) + ")\n")
        manifest = root / "data/recovered_sources.json"
        manifest.write_text(json.dumps({"schema_version": 2, "cutover": "canonical-split",
                                       "language": language, "functions": records,
                                       "function_count": len(records), "source_file_count": len(sources),
                                       "state_owner": sources[0], "address_marker_count": 0}))
        with mock.patch.object(split, "ROOT", root), mock.patch.object(split, "SOURCE_ROOT", root / "src"), \
                mock.patch.object(split, "SOURCE_LIST", source_list):
            return split.run(manifest, 1500, 2000)

    def test_source_manifest_accepts_c_cpp_and_mixed_inventory(self):
        for index, (language, suffixes) in enumerate([
                ("GNU C17", [".c"]), ("GNU C++20", [".cpp"]),
                ("mixed GNU C17/C++20", [".c", ".cpp"])]):
            with self.subTest(language=language):
                audit = self.manifest_audit(self.root / str(index), language, suffixes)
                self.assertEqual(audit.errors, [])
                self.assertEqual(audit.checks["manifest functions"], len(suffixes))

    def test_manifest_language_cannot_conceal_unmigrated_sources(self):
        audit = self.manifest_audit(self.root / "mismatch", "GNU C++20", [".c"])
        self.assertTrue(any("does not match manifest language" in error for error in audit.errors),
                        audit.errors)

    def test_cpp_inventory_cannot_hide_unlisted_translation_unit(self):
        audit = self.manifest_audit(self.root / "unlisted", "mixed GNU C17/C++20", [".c"], True)
        self.assertIn("recovered subsystem directories differ from the manifest-backed source inventory",
                      audit.errors)


class TokenTests(unittest.TestCase):
    def test_path_normalization_requires_explicit_option_and_boundary(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "sample.i"
            path.write_text('CLASH95_PP_TRANSLATION_UNIT_BOUNDARY_0000 "src/core/a.cpp";\n'
                            'const char *path = "src/core/a.cpp";\n')
            strict = tokens.lex(path)
            normalized = tokens.lex(path, normalize_cpp_paths=True)
        self.assertEqual(strict.count('"src/core/a.cpp"'), 2)
        self.assertEqual(normalized.count('"src/core/a.cpp"'), 1)
        self.assertEqual(normalized.count('"src/core/a.c"'), 1)


@unittest.skipUnless(all(shutil.which(tool) for tool in ("bash", "gcc", "g++", "objdump", "gcov")),
                     "Linux C/C++ compiler and coverage tools required")
class CompilerGateTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="clash95-cpp-tool-test-")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for directory in ("tools", "data", "src/core"):
            (self.root / directory).mkdir(parents=True)
        for name in ("obj_diff_gate.sh", "pp_token_gate.sh", "pp_token_diff.py"):
            shutil.copy2(REPO / "tools" / name, self.root / "tools" / name)
        self.env = dict(os.environ, CC="gcc", CXX="g++", PYTHON=sys.executable)

    def command(self, *args):
        return subprocess.run(args, cwd=self.root, env=self.env, capture_output=True, text=True)

    def manifest(self, sources):
        (self.root / "data/recovered_sources.json").write_text(json.dumps({
            "functions": [{"source": source} for source in sources],
            "source_file_count": len(sources)}))

    def snapshot(self, script, name, *extra):
        path = self.root / name
        result = self.command("bash", f"tools/{script}", "--snapshot", str(path), *extra)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return path.read_text()

    def test_mixed_sources_use_their_own_compiler_language(self):
        (self.root / "src/core/c_only.c").write_text(
            '#ifdef __cplusplus\n#error C source compiled as C++\n#endif\n'
            'int c_only(void) { return 17; }\n')
        (self.root / "src/core/cpp_only.cpp").write_text(
            '#if !defined(__cplusplus) || __cplusplus < 202002L\n#error need C++20\n#endif\n'
            '#ifdef _GNU_SOURCE\n#error C++ must preserve C feature profile\n#endif\n'
            'extern "C" int cpp_only(void) { return 20; }\n')
        self.manifest(["src/core/c_only.c", "src/core/cpp_only.cpp"])
        for script in ("obj_diff_gate.sh", "pp_token_gate.sh"):
            with self.subTest(script=script):
                output = self.snapshot(script, script + ".snapshot")
                self.assertIn("c_only", output)
                self.assertIn("cpp_only", output)

    def test_single_language_cpp_mode_uses_cpp20(self):
        (self.root / "src/core/only.cpp").write_text(
            '#if !defined(__cplusplus) || __cplusplus < 202002L\n#error need C++20\n#endif\n'
            '#ifdef _GNU_SOURCE\n#error C++ must preserve C feature profile\n#endif\n'
            'extern "C" int only(void) { return 20; }\n')
        self.manifest(["src/core/only.cpp"])
        for script in ("obj_diff_gate.sh", "pp_token_gate.sh"):
            with self.subTest(script=script):
                self.assertIn("only", self.snapshot(script, script + ".snapshot"))

    def test_cpp_object_gate_rejects_string_literal_const_removal(self):
        (self.root / "src/core/literal.cpp").write_text('char *literal(void) { return "read only"; }\n')
        self.manifest(["src/core/literal.cpp"])
        result = self.command("bash", "tools/obj_diff_gate.sh", "--snapshot", "literal.snapshot")
        self.assertNotEqual(result.returncode, 0, "g++ must not accept this C++ extension silently")
        self.assertIn("write-strings", result.stderr)

    def test_path_only_migration_requires_explicit_normalization(self):
        source = 'int same(void) { return 17; }\n'
        (self.root / "src/core/same.c").write_text(source)
        self.manifest(["src/core/same.c"])
        for script in ("obj_diff_gate.sh", "pp_token_gate.sh"):
            self.snapshot(script, script + ".before")
        # A separate declaration gives the C++ definition its original C name.
        (self.root / "src/core/same.cpp").write_text('extern "C" int same(void);\n' + source)
        self.manifest(["src/core/same.cpp"])
        strict = self.command("bash", "tools/obj_diff_gate.sh", "obj_diff_gate.sh.before")
        self.assertNotEqual(strict.returncode, 0)
        normalized = self.command("bash", "tools/obj_diff_gate.sh", "obj_diff_gate.sh.before",
                                  "--normalize-cpp-paths")
        self.assertEqual(normalized.returncode, 0, normalized.stdout + normalized.stderr)
        # The preprocessor must still report the added linkage declaration.
        result = self.command("bash", "tools/pp_token_gate.sh", "pp_token_gate.sh.before",
                              "--normalize-cpp-paths")
        self.assertNotEqual(result.returncode, 0)

    def test_cpp_coverage_note_and_profile_are_found(self):
        source = "src/core/covered.cpp"
        (self.root / source).write_text('extern "C" int covered(void) { return 0; }\n'
                                       'int main() { return covered(); }\n')
        build = self.root / "build"
        obj = build / "CMakeFiles/clash95_recovered_coverage_objects.dir" / (source + ".o")
        obj.parent.mkdir(parents=True)
        executable = build / "coverage_fixture"
        for command in [("g++", "-std=gnu++20", "--coverage", "-c", str(self.root / source), "-o", str(obj)),
                        ("g++", "--coverage", str(obj), "-o", str(executable)), (str(executable),)]:
            result = self.command(*command)
            self.assertEqual(result.returncode, 0, result.stderr)
        result = coverage.collect_split_gcov(build, {source})
        self.assertEqual(set(result), {source})
        self.assertTrue(result[source])
        self.assertTrue(all(result[source].values()))


if __name__ == "__main__":
    unittest.main()
