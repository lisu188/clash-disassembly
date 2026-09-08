#!/usr/bin/env python3
"""Check the separate INT_MIN recovery against the original x86 instructions."""
import hashlib
import json
import unittest
from world_geometry_fixture import ROOT, FIXTURES, COMMON, frozen, actual, run_profiles, assert_table_image

DIRECTORY = FIXTURES / "math_sin_degrees_q16"
NAME = "Math_SinDegreesQ16"

class SineRecoveryTests(unittest.TestCase):
    def test_recovered_body_matches_x86_and_preserves_defined_original_inputs(self):
        assert_table_image(self)
        provenance = json.loads((DIRECTORY / "provenance.json").read_text())
        self.assertRegex(provenance["reference_commit"], r"^[0-9a-f]{40}$")
        self.assertEqual(provenance["original_address"], "0x00415D80")
        self.assertEqual(hashlib.sha256((COMMON / "sine_table.inc").read_bytes()).hexdigest(),
                         provenance["table_file_sha256"])
        reference = frozen(self, DIRECTORY, provenance, body_key="before_body_sha256")
        snippets, headers, records = actual(self, [NAME])
        self.assertEqual(records[NAME]["original_address"], provenance["original_address"])
        parts = ['#include "units/units_internal.h"', '#include "units/units_state.h"']
        parts.extend('#include "' + header + '"' for header in sorted(headers))
        # The former INT_MIN UB is deliberately isolated in a child process.
        # All recovered bodies and class methods retain full UBSan coverage.
        parts.append('__attribute__((noinline, no_sanitize("undefined")))\n' + reference)
        parts.extend(snippets)
        parts.append((DIRECTORY / "harness.cpp").read_text())
        run_profiles(self, parts, label="sine-recovery",
                     output_pattern=r"repair_cases=82669 guarded_table_bytes=4096 x86_oracle=pass")

if __name__ == "__main__":
    unittest.main()
