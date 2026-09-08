#!/usr/bin/env python3
"""A covered ABI wrapper cannot satisfy recovered class-body coverage."""

from __future__ import annotations

from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import coverage_source_manifest as coverage


class CanonicalCoverageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "src/world").mkdir(parents=True)
        self.source = "src/world/WorldMap.cpp"
        self.record = {"name": "WorldMap_Refresh", "source": self.source,
                       "original_source": "legacy.c", "original_line": 9,
                       "implementation": {"kind": "method", "qualified_name": "clash95::WorldMap::WorldMap_Refresh"}}
        self.text = ("int WorldMap_Refresh() { return binding().WorldMap_Refresh(); }\n"
                     "namespace clash95 {\n"
                     "int WorldMap::WorldMap_Refresh() const noexcept\n"
                     "{\n"
                     "  if (counter)\n"
                     "    return 7;\n"
                     "  return 3;\n"
                     "}\n"
                     "}\n")
        (self.root / self.source).write_text(self.text)

    def ranges(self):
        with mock.patch.object(coverage, "ROOT", self.root):
            return coverage.split_ranges([self.record])

    def test_range_is_method_but_public_key_remains_historical(self):
        self.assertEqual(self.ranges(), {"WorldMap_Refresh": (self.source, 3, 9)})

    def test_covered_adapter_and_uncovered_method_do_not_count_as_covered(self):
        source, low, high = self.ranges()["WorldMap_Refresh"]
        executable = {1: True, 5: False, 6: False, 7: False}
        measured = [line for line in range(low, high) if line in executable]
        self.assertEqual(measured, [5, 6, 7])
        self.assertFalse(any(executable[line] for line in measured))

    def test_method_on_another_line_remains_same_identity(self):
        (self.root / self.source).write_text("\n\n" + self.text)
        self.assertEqual(self.ranges()["WorldMap_Refresh"], (self.source, 5, 11))

    def test_no_fallback_to_adapter_when_method_is_missing(self):
        (self.root / self.source).write_text(self.text.splitlines()[0] + "\n")
        with self.assertRaisesRegex(coverage.CoverageMetadataError, "found 0"):
            self.ranges()

    def test_enrichment_carries_mapping_without_changing_frozen_name(self):
        with mock.patch.object(coverage, "load_aliases", return_value={}):
            enriched = coverage.enrich_pure_set(
                {"functions": [{"name": "WorldMap_Refresh"}]},
                {"WorldMap_Refresh": self.record})
        self.assertEqual(enriched["count"], 1)
        self.assertEqual(enriched["functions"][0]["name"], "WorldMap_Refresh")
        self.assertEqual(enriched["functions"][0]["implementation"], self.record["implementation"])

    def test_legacy_free_definition_retains_existing_range(self):
        free = dict(self.record)
        free.pop("implementation")
        with mock.patch.object(coverage, "ROOT", self.root):
            self.assertEqual(coverage.split_ranges([free]), {"WorldMap_Refresh": (self.source, 1, 2)})


if __name__ == "__main__":
    unittest.main()
