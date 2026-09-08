#!/usr/bin/env python3

import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
TOOL = REPO / "tools" / "update_split_manifest_hashes.py"
sys.path.insert(0, str(REPO / "tools"))

from split_source_index import body_sha256, scan_definitions


class ScopedManifestHashUpdateTests(unittest.TestCase):
    def source_text(self, alpha_value: int, beta_value: int) -> str:
        return (
            "//----- (00401000) --------------------------------------------------------\n"
            "int Alpha(void)\n"
            "{\n"
            f"  return {alpha_value};\n"
            "}\n\n"
            "//----- (00401010) --------------------------------------------------------\n"
            "int Beta(void)\n"
            "{\n"
            f"  return {beta_value};\n"
            "}\n"
        )

    def create_fixture(self, root: Path) -> tuple[Path, Path, dict[str, str]]:
        source = root / "src/core/example.cpp"
        source.parent.mkdir(parents=True)
        source.write_text(self.source_text(1, 2), encoding="utf-8")
        definitions = scan_definitions(source.read_text(encoding="utf-8"), {"Alpha", "Beta"})
        digests = {
            definition.name: body_sha256(source.read_text(encoding="utf-8"), definition)
            for definition in definitions
        }
        manifest = root / "data/recovered_sources.json"
        manifest.parent.mkdir(parents=True)
        manifest.write_text(
            json.dumps(
                {
                    "schema_version": 2,
                    "cutover": "canonical-split",
                    "legacy_manifest": "clash95.c",
                    "address_marker_count": 2,
                    "functions": [
                        {
                            "name": "Alpha",
                            "source": "src/core/example.cpp",
                            "body_sha256": digests["Alpha"],
                        },
                        {
                            "name": "Beta",
                            "source": "src/core/example.cpp",
                            "body_sha256": digests["Beta"],
                        },
                    ],
                },
                indent=2,
            )
            + "\n",
            encoding="utf-8",
        )
        return source, manifest, digests

    def run_tool(self, root: Path, *args: str) -> subprocess.CompletedProcess[str]:
        return subprocess.run(
            [
                sys.executable,
                str(TOOL),
                "--root",
                str(root),
                "--manifest",
                "data/recovered_sources.json",
                *args,
            ],
            cwd=REPO,
            text=True,
            capture_output=True,
            check=False,
        )

    def test_only_updates_selected_changed_function(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, manifest, original = self.create_fixture(root)
            source.write_text(self.source_text(3, 2), encoding="utf-8")

            result = self.run_tool(root, "--update", "--only", "Alpha")
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("updated 1 selected canonical body hashes", result.stdout)

            payload = json.loads(manifest.read_text(encoding="utf-8"))
            records = {record["name"]: record for record in payload["functions"]}
            text = source.read_text(encoding="utf-8")
            alpha, beta = scan_definitions(text, {"Alpha", "Beta"})
            self.assertEqual(records["Alpha"]["body_sha256"], body_sha256(text, alpha))
            self.assertEqual(records["Alpha"]["legacy_body_sha256"], original["Alpha"])
            self.assertEqual(records["Beta"]["body_sha256"], original["Beta"])
            self.assertNotIn("legacy_body_sha256", records["Beta"])

    def test_unselected_changed_function_aborts_without_writing_manifest(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, manifest, _ = self.create_fixture(root)
            before = manifest.read_text(encoding="utf-8")
            source.write_text(self.source_text(3, 4), encoding="utf-8")

            result = self.run_tool(root, "--update", "--only", "Alpha")
            self.assertEqual(result.returncode, 1)
            self.assertIn("Beta: canonical body hash differs outside --only selection", result.stdout)
            self.assertEqual(manifest.read_text(encoding="utf-8"), before)

    def test_unknown_selected_function_fails_closed(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, manifest, _ = self.create_fixture(root)
            before = manifest.read_text(encoding="utf-8")

            result = self.run_tool(root, "--update", "--only", "MissingFunction")
            self.assertEqual(result.returncode, 1)
            self.assertIn("MissingFunction: not present in manifest", result.stdout)
            self.assertEqual(manifest.read_text(encoding="utf-8"), before)

    def test_only_requires_update_mode(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.create_fixture(root)

            result = self.run_tool(root, "--only", "Alpha")
            self.assertEqual(result.returncode, 2)
            self.assertIn("--only requires --update", result.stderr)


if __name__ == "__main__":
    unittest.main()
