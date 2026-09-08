#!/usr/bin/env python3

from __future__ import annotations

import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


REPO = Path(__file__).resolve().parents[2]
TOOLS = REPO / "tools"
sys.path.insert(0, str(TOOLS))
from split_source_index import body_sha256, scan_definitions

SCRIPT = TOOLS / "apply_function_identity_migration.py"


class FunctionIdentityMigrationTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / "src/render/render.cpp"
        self.compat = self.root / "src/compatibility/stubs.cpp"
        self.manifest = self.root / "data/recovered_sources.json"
        self.decls = self.root / "data/recovered_decls.json"
        self.spec = self.root / "data/function_identity_migrations/example.json"
        self.source.parent.mkdir(parents=True)
        self.compat.parent.mkdir(parents=True)
        self.manifest.parent.mkdir(parents=True)
        self.spec.parent.mkdir(parents=True)

        self.source.write_text(
            "int OldFunction(int surface, int value)\n"
            "{\n"
            "  return surface + value;\n"
            "}\n",
            encoding="latin-1",
        )
        self.compat.write_text(
            "int NewFunction(int surface, int value)\n"
            "{\n"
            "  return surface + value;\n"
            "}\n\n"
            "int OtherFunction(void)\n"
            "{\n"
            "  return 7;\n"
            "}\n",
            encoding="latin-1",
        )
        self.manifest_payload = {
            "schema_version": 2,
            "functions": [{
                "name": "OldFunction",
                "subsystem": "render",
                "source": "src/render/render.cpp",
                "linkage": "external",
                "body_sha256": self.digest(self.source, "OldFunction"),
                "original_address_range": {
                    "start": "0x00404A40",
                    "end_exclusive": "0x00404A60",
                },
            }],
            "state_owner": "src/state/state.cpp",
        }
        self.decls_payload = {
            "schema_version": 1,
            "functions": {
                "OldFunction": {
                    "class": "manifest",
                    "decl": "int OldFunction(int surface, int value);",
                    "home": "render",
                },
                "NewFunction": {
                    "class": "legacy-import",
                    "decl": "int NewFunction(int, int);",
                },
            },
            "globals": {},
        }
        self.write_metadata()
        self.spec.write_text(json.dumps({
            "schema_version": 1,
            "old_name": "OldFunction",
            "new_name": "NewFunction",
            "source": "src/render/render.cpp",
            "compatibility_source": "src/compatibility/stubs.cpp",
            "original_address": "0x00404A40",
            "expected_body_sha256": self.digest(self.source, "OldFunction"),
            "expected_compat_body_sha256": self.digest(self.compat, "NewFunction"),
        }, indent=2), encoding="utf-8")

    @staticmethod
    def digest(path: Path, name: str) -> str:
        text = path.read_text(encoding="latin-1")
        definition, = scan_definitions(text, {name})
        return body_sha256(text, definition)

    def write_metadata(self):
        self.manifest.write_text(json.dumps(self.manifest_payload, indent=2) + "\n", encoding="utf-8")
        self.decls.write_text(json.dumps(self.decls_payload, indent=2) + "\n", encoding="utf-8")

    def run_tool(self, *extra: str):
        return subprocess.run(
            [sys.executable, str(SCRIPT), str(self.spec), "--root", str(self.root), *extra],
            capture_output=True,
            text=True,
        )

    def test_applies_identity_and_removes_duplicate_definition(self):
        result = self.run_tool("--write")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        manifest = json.loads(self.manifest.read_text())
        self.assertEqual(manifest["functions"][0]["name"], "NewFunction")
        source_text = self.source.read_text(encoding="latin-1")
        self.assertNotIn("OldFunction", source_text)
        self.assertEqual(len(scan_definitions(source_text, {"NewFunction"})), 1)
        compat_text = self.compat.read_text(encoding="latin-1")
        self.assertEqual(len(scan_definitions(compat_text, {"NewFunction"})), 0)
        self.assertIn("OtherFunction", compat_text)
        decls = json.loads(self.decls.read_text())
        self.assertNotIn("OldFunction", decls["functions"])
        self.assertEqual(decls["functions"]["NewFunction"]["class"], "manifest")
        self.assertIn("NewFunction", decls["functions"]["NewFunction"]["decl"])

    def test_is_idempotent_after_complete_migration(self):
        first = self.run_tool("--write")
        self.assertEqual(first.returncode, 0, first.stdout + first.stderr)
        snapshot = {
            path: path.read_bytes()
            for path in (self.source, self.compat, self.manifest, self.decls)
        }
        second = self.run_tool("--write")
        self.assertEqual(second.returncode, 0, second.stdout + second.stderr)
        self.assertIn("already-applied", second.stdout)
        for path, content in snapshot.items():
            self.assertEqual(path.read_bytes(), content)

    def test_rejects_canonical_body_drift_without_writes(self):
        before = self.source.read_bytes()
        self.source.write_text(
            self.source.read_text(encoding="latin-1").replace(
                "return surface + value;", "return surface - value;"
            ),
            encoding="latin-1",
        )
        drifted = self.source.read_bytes()
        result = self.run_tool("--write")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("canonical body hash", result.stdout)
        self.assertEqual(self.source.read_bytes(), drifted)
        self.assertNotEqual(before, drifted)
        self.assertEqual(json.loads(self.manifest.read_text())["functions"][0]["name"], "OldFunction")

    def test_rejects_compatibility_body_drift(self):
        self.compat.write_text(
            self.compat.read_text(encoding="latin-1").replace(
                "return surface + value;", "return value;", 1
            ),
            encoding="latin-1",
        )
        result = self.run_tool("--write")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("compatibility body hash", result.stdout)
        self.assertIn("OldFunction", self.source.read_text(encoding="latin-1"))

    def test_rejects_wrong_destination_declaration_class(self):
        self.decls_payload["functions"]["NewFunction"]["class"] = "helper"
        self.write_metadata()
        result = self.run_tool("--write")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("legacy-import", result.stdout)
        self.assertIn("OldFunction", self.source.read_text(encoding="latin-1"))


if __name__ == "__main__":
    unittest.main()
