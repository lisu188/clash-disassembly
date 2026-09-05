#!/usr/bin/env python3
"""Declaration-helper metadata and header-placement regressions.

Run from the repository root in Linux/WSL:
  python3 -m unittest discover -s tests/tools -p 'test_gen_subsystem_headers.py'

Fixtures use temporary files and mock preprocessing; retail assets and GCC
are not needed for this focused metadata/generation check.
"""

from __future__ import annotations

import contextlib
import importlib.util
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest import mock


REPO = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location(
    "gen_subsystem_headers", REPO / "tools" / "gen_subsystem_headers.py")
assert SPEC is not None and SPEC.loader is not None
GEN = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GEN)


class HelperDeclarationsTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.repo = Path(self.temp.name)
        self.sources = {
            sub: f"src/{sub}/{sub}.c"
            for sub in ("persistence", "media", "clips", "state")
        }
        self.sources["persistence_caller"] = "src/persistence/caller.c"
        for rel in self.sources.values():
            path = self.repo / rel
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text("/* fixture source */\n", encoding="latin-1")
        self.manifest = {
            "functions": [
                {"name": f"{sub.title()}_ManifestFunction",
                 "subsystem": sub, "source": self.sources[sub]}
                for sub in ("persistence", "media", "clips")
            ] + [{"name": "Persistence_CallerFunction",
                  "subsystem": "persistence",
                  "source": self.sources["persistence_caller"]}],
            "state_owner": self.sources["state"],
        }
        self.decls = {
            "schema_version": 1,
            "functions": {
                rec["name"]: {
                    "class": "manifest",
                    "decl": f"void {rec['name']}(void);",
                    "home": rec["subsystem"],
                }
                for rec in self.manifest["functions"]
            },
            "globals": {},
        }
        self.decls_path = self.repo / "data" / "recovered_decls.json"
        self.manifest_path = self.repo / "data" / "recovered_sources.json"
        self.surface_path = self.repo / "data" / "subsystem_api.json"
        self.decls_path.parent.mkdir(parents=True)
        patches = mock.patch.multiple(
            GEN, REPO=self.repo, DECLS=self.decls_path,
            MANIFEST=self.manifest_path, SURFACE_OUT=self.surface_path)
        patches.start()
        self.addCleanup(patches.stop)

    def add_helper(self, name="Options_RebuildMainMenuWidgetTemplates",
                   home="persistence", **overrides):
        rec = {
            "class": "helper",
            "decl": f"void {name}(void);",
            "home": home,
            "source": self.sources[home],
        }
        rec.update(overrides)
        self.decls["functions"][name] = rec
        return rec

    def write_metadata(self):
        self.decls_path.write_text(json.dumps(self.decls), encoding="utf-8")
        self.manifest_path.write_text(
            json.dumps(self.manifest), encoding="utf-8")

    def assert_invalid(self):
        self.write_metadata()
        with contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit):
                GEN.load()

    def test_helper_in_existing_source_is_valid(self):
        self.add_helper()
        self.write_metadata()
        decls, manifest = GEN.load()
        self.assertEqual(decls, self.decls)
        self.assertEqual(manifest, self.manifest)

    def test_unknown_class_is_rejected(self):
        self.add_helper(**{"class": "helpr"})
        self.assert_invalid()

    def test_helper_cannot_replace_manifest_classification(self):
        self.add_helper(name="Persistence_ManifestFunction")
        self.assert_invalid()

    def test_helper_requires_source(self):
        rec = self.add_helper()
        del rec["source"]
        self.assert_invalid()

    def test_helper_source_must_exist(self):
        self.add_helper()
        (self.repo / self.sources["persistence"]).unlink()
        self.assert_invalid()

    def test_helper_home_must_match_source_subsystem(self):
        self.add_helper(source=self.sources["media"])
        self.assert_invalid()

    def test_helper_home_must_be_known(self):
        rec = self.add_helper()
        rec["home"] = "unknown"
        self.assert_invalid()

    def test_helper_source_must_be_manifest_backed(self):
        source = "src/persistence/extra.c"
        (self.repo / source).write_text(
            "/* exists but is not scanned */\n", encoding="latin-1")
        self.add_helper(source=source)
        self.assert_invalid()

    def test_helpers_are_generated_in_measured_subsystem_headers(self):
        options = "Options_RebuildMainMenuWidgetTemplates"
        rules = "Rules_EnsureFactPatternEntityRecord"
        # Insert helper names out of alphabetical order to check stable
        # ordering after the manifest-ordered declarations.
        self.add_helper(name="Zeta_Helper")
        self.add_helper(name=options)
        self.add_helper(name="Alpha_Helper")
        self.add_helper(name=rules, home="media",
                        decl=f"CLASH95_INTERNAL void {rules}(void);")
        self.write_metadata()
        tokens = {
            self.sources["persistence"]: {options, "Zeta_Helper", "Alpha_Helper"},
            self.sources["persistence_caller"]: {options},
            self.sources["media"]: {rules},
            self.sources["clips"]: {rules},
            self.sources["state"]: set(),
        }
        expanded = {
            ("fn", name): name for name in self.decls["functions"]
        }
        with mock.patch.object(GEN, "scan_usage", return_value=tokens), \
                mock.patch.object(GEN, "expanded_names", return_value=expanded), \
                mock.patch("sys.argv", ["gen_subsystem_headers.py", "--write"]), \
                contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(GEN.main(), 0)

        persistence_internal = (
            self.repo / "src/persistence/persistence_internal.h"
        ).read_text(encoding="latin-1")
        persistence_api = (
            self.repo / "src/persistence/persistence_api.h"
        ).read_text(encoding="latin-1")
        media_api = (self.repo / "src/media/media_api.h").read_text(
            encoding="latin-1")
        media_internal = (self.repo / "src/media/media_internal.h").read_text(
            encoding="latin-1")
        legacy = (self.repo / "src/recovered_legacy_imports.h").read_text(
            encoding="latin-1")
        self.assertIn(f"void {options}(void);", persistence_internal)
        ordered = ["Persistence_ManifestFunction", "Persistence_CallerFunction",
                   "Alpha_Helper", options, "Zeta_Helper"]
        positions = [persistence_internal.index(name) for name in ordered]
        self.assertEqual(positions, sorted(positions))
        self.assertNotIn(options, persistence_api)
        self.assertIn(f"CLASH95_INTERNAL void {rules}(void);", media_api)
        self.assertNotIn(rules, media_internal)
        self.assertNotIn(options, legacy)
        self.assertNotIn(rules, legacy)
        surface = json.loads(self.surface_path.read_text(encoding="utf-8"))
        self.assertEqual(surface["subsystems"]["media"]["api_functions"],
                         [rules])
        self.assertEqual(surface["subsystems"]["persistence"]["api_functions"],
                         [])
        self.assertEqual(surface["peer_edges"], {"clips->media": 1})
        self.assertEqual(surface["legacy_import_count"], 0)


if __name__ == "__main__":
    unittest.main()
