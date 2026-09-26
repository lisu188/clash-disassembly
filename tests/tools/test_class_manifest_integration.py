"""Ensure an ownership inventory cannot bless a conflicting implementation."""
import copy
from argparse import Namespace
import contextlib
import io
import json
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from game_class_catalog import validate_registry
from sync_game_class_manifest import synchronize
import measure_pure_coverage


class ClassManifestIntegrationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        cls.registry = json.loads((ROOT / "data/game_class_registry.json").read_text())
        cls.declarations = json.loads((ROOT / "data/recovered_decls.json").read_text())

    def test_procedural_identity_cannot_claim_a_method(self):
        manifest = copy.deepcopy(self.manifest)
        record = next(item for item in manifest["functions"] if item["name"] == "Rules_HashSymbolName")
        record["implementation"] = {"kind": "method", "qualified_name": "clash95::Bad::Rules_HashSymbolName",
                                    "header": "src/clips/Bad.hpp"}
        self.assertTrue(any("procedural disposition" in error for error in validate_registry(self.registry, manifest)))

    def test_changed_method_owner_is_rejected(self):
        manifest = copy.deepcopy(self.manifest)
        record = next(item for item in manifest["functions"] if item.get("implementation", {}).get("kind") == "method")
        record["implementation"]["qualified_name"] = "clash95::Wrong::" + record["name"]
        self.assertTrue(any("implementation owner" in error for error in validate_registry(self.registry, manifest)))

    def test_disposition_sync_preserves_body_and_adapter_hashes(self):
        result = synchronize(self.manifest, self.registry, self.declarations)
        for before, after in zip(self.manifest["functions"], result["functions"]):
            self.assertEqual(before["body_sha256"], after["body_sha256"])
            self.assertEqual(before["legacy_body_sha256"], after["legacy_body_sha256"])
            self.assertEqual(before.get("adapter"), after.get("adapter"))
            self.assertEqual(before.get("historical_names"), after.get("historical_names"))
            self.assertEqual(before.get("compatibility_aliases"), after.get("compatibility_aliases"))

    def test_missing_method_lines_cannot_pass_at_one_hundred_percent(self):
        functions = [{"name": name, "source": "src/units/UnitStack.cpp"}
                     for name in ("covered", "missing")]
        args = Namespace(build_dir=ROOT, worst=0, jsonout=None, minimum=89.7,
                         require_functions=2, require_zero_uncovered=True,
                         gcov_command=["gcov"])
        ranges = {"covered": (functions[0]["source"], 1, 3),
                  "missing": (functions[0]["source"], 4, 6)}
        with patch.object(measure_pure_coverage, "parse_args", return_value=args), \
             patch.object(measure_pure_coverage, "load_pure_set", return_value=({}, functions)), \
             patch.object(measure_pure_coverage, "split_ranges", return_value=ranges), \
             patch.object(measure_pure_coverage, "collect_split_gcov",
                          return_value={functions[0]["source"]: {1: True}}), \
             contextlib.redirect_stdout(io.StringIO()) as output:
            self.assertEqual(measure_pure_coverage.main(), 1)
        self.assertIn("100.00%", output.getvalue())
        self.assertIn("no executable lines: missing", output.getvalue())


if __name__ == "__main__":
    unittest.main()
