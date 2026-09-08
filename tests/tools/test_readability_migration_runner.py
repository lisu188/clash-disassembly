#!/usr/bin/env python3

import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
TOOL = REPO / "tools" / "apply_readability_migration.py"
sys.path.insert(0, str(REPO / "tools"))

from split_source_index import body_sha256, scan_definitions


class ReadabilityMigrationRunnerTests(unittest.TestCase):
    def create_fixture(self, root: Path) -> tuple[Path, Path, str]:
        source = root / "src/media/example.cpp"
        source.parent.mkdir(parents=True)
        source.write_text(
            "/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */\n"
            '#include "../recovered_layout.h"\n'
            "/* CLASH95_GENERATED_INCLUDES_END */\n\n"
            "int Example_GetValue(int value)\n"
            "{\n"
            "  return value + 1;\n"
            "}\n",
            encoding="utf-8",
        )
        text = source.read_text(encoding="utf-8")
        definition, = scan_definitions(text, {"Example_GetValue"})
        old_hash = body_sha256(text, definition)

        spec = root / "data/readability_migrations/example.json"
        spec.parent.mkdir(parents=True)
        spec.write_text(
            json.dumps(
                {
                    "schema_version": 1,
                    "source": "src/media/example.cpp",
                    "includes": ["example_view.h"],
                    "functions": [
                        {
                            "name": "Example_GetValue",
                            "expected_body_sha256": old_hash,
                            "replacement_body": "{\n  return value + 2;\n}",
                        }
                    ],
                },
                indent=2,
            )
            + "\n",
            encoding="utf-8",
        )
        return source, spec, old_hash

    def run_tool(self, root: Path, spec: Path, *args: str) -> subprocess.CompletedProcess[str]:
        return subprocess.run(
            [sys.executable, str(TOOL), str(spec), "--root", str(root), *args],
            cwd=REPO,
            text=True,
            capture_output=True,
            check=False,
        )

    def test_dry_run_does_not_modify_source(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, spec, _ = self.create_fixture(root)
            before = source.read_text(encoding="utf-8")

            result = self.run_tool(root, spec)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("readability migration: PLAN", result.stdout)
            self.assertEqual(source.read_text(encoding="utf-8"), before)

    def test_write_replaces_only_body_and_adds_local_view_include(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, spec, _ = self.create_fixture(root)

            result = self.run_tool(root, spec, "--write")
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            text = source.read_text(encoding="utf-8")
            self.assertIn('#include "example_view.h"', text)
            self.assertIn("return value + 2;", text)
            self.assertNotIn("return value + 1;", text)

            definition, = scan_definitions(text, {"Example_GetValue"})
            spec_payload = json.loads(spec.read_text(encoding="utf-8"))
            replacement = spec_payload["functions"][0]["replacement_body"]
            from apply_readability_migration import body_text_sha256
            self.assertEqual(body_sha256(text, definition), body_text_sha256(replacement))

            second = self.run_tool(root, spec, "--write")
            self.assertEqual(second.returncode, 0, second.stdout + second.stderr)
            self.assertIn("functions=already-applied", second.stdout)
            self.assertEqual(text, source.read_text(encoding="utf-8"))

    def test_unexpected_current_hash_fails_without_writing(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, spec, _ = self.create_fixture(root)
            source.write_text(
                source.read_text(encoding="utf-8").replace(
                    "return value + 1;", "return value + 99;"
                ),
                encoding="utf-8",
            )
            before = source.read_text(encoding="utf-8")

            result = self.run_tool(root, spec, "--write")
            self.assertEqual(result.returncode, 1)
            self.assertIn("matches neither expected", result.stdout)
            self.assertEqual(source.read_text(encoding="utf-8"), before)

    def test_non_view_manual_include_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, spec, _ = self.create_fixture(root)
            payload = json.loads(spec.read_text(encoding="utf-8"))
            payload["includes"] = ["media_internal.h"]
            spec.write_text(json.dumps(payload), encoding="utf-8")

            result = self.run_tool(root, spec, "--write")
            self.assertEqual(result.returncode, 1)
            self.assertIn("local *_view.h basenames", result.stdout)


if __name__ == "__main__":
    unittest.main()
