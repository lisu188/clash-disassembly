"""Inventory failures that would silently omit or misclassify class migration."""

import copy
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import unittest


REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))
SPEC = importlib.util.spec_from_file_location("game_class_catalog", REPO / "tools/game_class_catalog.py")
catalog = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(catalog)


class GameClassCatalogTests(unittest.TestCase):
    def setUp(self):
        self.manifest = {"functions": [{
            "name": "UnitStack_HasBuilder", "subsystem": "units",
            "source": "src/units/original.cpp", "original_source": "src/recovered/units/original.inc.c",
            "original_address": "0x00411AB0",
        }]}
        self.registry = {"schema_version": 1, "identities": [{
            "name": "UnitStack_HasBuilder", "identity_kind": "original",
            "original_address": "0x00411AB0", "legacy_subsystem": "units",
            "legacy_source": "src/units/original.cpp", "original_source": "src/recovered/units/original.inc.c",
            "classification": "game-method", "class_owner": "UnitStack", "method": "UnitStack_HasBuilder",
            "logical_subsystem": "units", "final_header": "src/units/UnitStack.hpp",
            "final_source": "src/units/UnitStack.cpp",
            "rationale": "Builder membership is an observed query over packed stack slots.",
            "evidence": ["clash95.asm@0x00411AB0"],
        }], "helpers": []}
        self.declarations = {"functions": {}}

    def errors(self):
        return catalog.validate_registry(self.registry, self.manifest, self.declarations)

    def test_complete_repository_inventory_and_read_only_cli(self):
        paths = [catalog.REGISTRY, catalog.MANIFEST, catalog.DECLARATIONS]
        before = [path.read_bytes() for path in paths]
        registry, manifest, declarations = [json.loads(data) for data in before]
        self.assertEqual(catalog.validate_registry(registry, manifest, declarations), [])
        self.assertEqual(len(registry["identities"]), len(manifest["functions"]))
        process = subprocess.run([sys.executable, str(REPO / "tools/game_class_catalog.py"), "--check"],
                                 cwd=REPO, text=True, capture_output=True)
        self.assertEqual(process.returncode, 0, process.stderr)
        self.assertEqual(json.loads(process.stdout)["identities"], len(manifest["functions"]))
        self.assertEqual([path.read_bytes() for path in paths], before)

    def test_new_manifest_identity_fails_without_prefix_inference(self):
        new = dict(self.manifest["functions"][0], name="UnitStack_NewUnreviewedMethod")
        self.manifest["functions"].append(new)
        self.assertIn("unclassified manifest identity UnitStack_NewUnreviewedMethod", self.errors())

    def test_duplicate_and_stale_registry_entries_fail(self):
        self.registry["identities"].append(copy.deepcopy(self.registry["identities"][0]))
        self.assertTrue(any("duplicate registry identity" in error for error in self.errors()))
        self.registry["identities"][1]["name"] = "NoLongerInManifest"
        self.assertTrue(any("unknown registry identity NoLongerInManifest" in error for error in self.errors()))

    def test_missing_or_catchall_owner_fails(self):
        for owner in (None, "Misc", "SubsystemOperations", "UnknownUnits"):
            with self.subTest(owner=owner):
                self.registry["identities"][0]["class_owner"] = owner
                self.assertTrue(any("concrete class_owner" in error for error in self.errors()))

    def test_address_and_historical_source_are_pinned(self):
        entry = self.registry["identities"][0]
        entry["original_address"] = "0x00411AB1"
        entry["original_source"] = "invented.inc.c"
        errors = self.errors()
        self.assertTrue(any("original address differs" in error for error in errors))
        self.assertTrue(any("historical original source differs" in error for error in errors))

    def test_class_named_relocation_and_explicit_shards_are_accepted(self):
        self.assertEqual(self.errors(), [])
        self.manifest["functions"][0]["source"] = "src/units/UnitStack.cpp"
        self.assertEqual(self.errors(), [])
        self.manifest["functions"][0]["source"] = "src/units/UnitStack.part02.cpp"
        self.assertTrue(any("neither legacy" in error for error in self.errors()))
        self.registry["identities"][0]["additional_sources"] = ["src/units/UnitStack.part02.cpp"]
        self.assertEqual(self.errors(), [])

    def test_non_class_named_and_escaping_paths_fail(self):
        for path in ("src/units/everything.cpp", "../UnitStack.cpp", "/src/units/UnitStack.cpp"):
            with self.subTest(path=path):
                self.registry["identities"][0]["final_source"] = path
                self.assertTrue(any("class-named" in error for error in self.errors()))

    def test_boundaries_need_rationale_and_cannot_hide_class_implementations(self):
        entry = self.registry["identities"][0]
        entry.update(classification="retained-boundary", rationale="", evidence=[])
        errors = self.errors()
        self.assertTrue(any("rationale" in error for error in errors))
        self.assertTrue(any("evidence" in error for error in errors))
        self.assertTrue(any("procedural boundary" in error for error in errors))

    def test_clips_surface_exceptions_cannot_be_excluded_by_folder(self):
        entry = self.registry["identities"][0]
        original = self.manifest["functions"][0]
        name = "Surface_DDCopyBitmap"
        entry.update(name=name, legacy_subsystem="clips", classification="excluded-library")
        original.update(name=name, subsystem="clips")
        self.assertTrue(any("CLIPS boundary requires game-method" in error for error in self.errors()))

    def test_clips_and_runtime_library_implementations_stay_procedural(self):
        self.registry["identities"][0]["legacy_subsystem"] = "clips"
        self.manifest["functions"][0]["subsystem"] = "clips"
        self.assertTrue(any("requires excluded-library" in error for error in self.errors()))
        self.registry["identities"][0].update(legacy_subsystem="runtime", original_address="0x00500000")
        self.manifest["functions"][0].update(subsystem="runtime", original_address="0x00500000")
        self.assertTrue(any("runtime CLIPS/CRT tail" in error for error in self.errors()))

    def test_manifest_helpers_cannot_gain_fake_addresses(self):
        del self.manifest["functions"][0]["original_address"]
        self.registry["identities"][0]["identity_kind"] = "support-helper"
        self.assertTrue(any("must not invent an original address" in error for error in self.errors()))
        del self.registry["identities"][0]["original_address"]
        self.assertEqual(self.errors(), [])

    def test_helper_registry_detects_new_removed_and_duplicate_helpers(self):
        self.declarations["functions"]["UnitStack_InitializeHelper"] = {
            "class": "helper", "source": "src/units/original.cpp"}
        self.assertIn("unclassified support helper UnitStack_InitializeHelper", self.errors())
        helper = {"name": "UnitStack_InitializeHelper", "source": "src/units/original.cpp",
                  "classification": "retained-boundary", "evidence": ["declarations"],
                  "rationale": "Explicit boundary helper without an original binary address."}
        self.registry["helpers"] = [helper]
        self.assertEqual(self.errors(), [])
        self.registry["helpers"].append(dict(helper))
        self.assertTrue(any("duplicates registered identity" in error for error in self.errors()))
        self.registry["helpers"] = [dict(helper, name="UnknownHelper")]
        self.assertIn("unknown support helper UnknownHelper", self.errors())

    def test_malformed_top_level_is_a_reported_error(self):
        self.assertEqual(catalog.validate_registry([], self.manifest), ["registry and manifest must be objects"])


if __name__ == "__main__":
    unittest.main()
