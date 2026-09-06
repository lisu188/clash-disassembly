#!/usr/bin/env python3
"""Actual WorldGeometry bodies and ABI adapters against separately repaired references."""
import json
import unittest
from world_geometry_fixture import ROOT, FIXTURES, frozen, actual, run_profiles, assert_table_image

DIRECTORY = FIXTURES / "class_world_geometry"
NAMES = ["Facing_DirectionFromDelta8", "Math_SinDegreesQ16", "Math_CeilSqrt"]

class WorldGeometryClassTests(unittest.TestCase):
    def test_whole_family_matches_actual_frozen_bodies(self):
        assert_table_image(self)
        provenance = json.loads((DIRECTORY / "provenance.json").read_text())
        self.assertRegex(provenance["reference_commit"], r"^[0-9a-f]{40}$")
        self.assertEqual([record["name"] for record in provenance["functions"]], NAMES)
        snippets, headers, records = actual(self, NAMES)
        self.assertEqual(headers, {"world/WorldGeometry.hpp"})
        parts = ['#include "units/units_internal.h"', '#include "units/units_state.h"',
                 '#include "world/WorldGeometry.hpp"']
        for reference in provenance["functions"]:
            name = reference["name"]
            self.assertEqual(records[name]["original_address"], reference["original_address"])
            self.assertEqual(records[name]["implementation"]["qualified_name"],
                             "clash95::WorldGeometry::" + name)
            parts.append(frozen(self, DIRECTORY, reference))
        parts.extend(snippets)
        parts.append((DIRECTORY / "harness.cpp").read_text())
        run_profiles(self, parts, label="world-geometry",
                     output_pattern=r"facing_cases=169 sine_cases=82669 sqrt_cases=220954 guarded_table_bytes=4096 direct_and_abi=pass")

if __name__ == "__main__":
    unittest.main()
