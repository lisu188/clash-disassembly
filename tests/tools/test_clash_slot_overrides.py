"""BSAVE-derived slot message names and live CLIPS activation regressions."""
from __future__ import annotations

import copy
import os
from pathlib import Path
import re
import shutil
import sys
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import check_clash_recovered_activation_witnesses as witnesses
from check_clash_recovered_clips_load import ERROR_MARKERS
from clash_dat_classes import parse_defclass
from clash_dat_slot_facets import _render_slot, recover_slot_facets, render_recovered_classes
from decompile_clash_dat import parse_bsave
from generate_clash_recovered_clp import GAME_CLASS_NAMES


class SlotOverrideTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.source = ROOT / "CLASH.DAT"
        cls.ir = parse_bsave(cls.source)
        cls.classes = parse_defclass(cls.source, cls.ir)
        cls.report = recover_slot_facets(cls.ir, cls.classes)

    def test_all_serialized_handler_names_are_emitted_exactly(self):
        rendered, report = render_recovered_classes(self.ir, self.classes, GAME_CLASS_NAMES)
        expected = [slot["override_message_name"] for slot in self.classes["slot_descriptors"]]
        self.assertEqual(len(expected), 23)
        self.assertEqual(re.findall(r"\(override-message ([^()\s]+)\)", rendered), expected)
        self.assertEqual(report, self.report)
        self.assertEqual(report["custom_override_message_count"], 0)
        self.assertIn("(override-message put-PA)", rendered)
        self.assertNotIn("(override-message DEFAULT)", rendered)

    def test_custom_handler_is_not_replaced_by_a_default(self):
        slot = copy.deepcopy(self.report["slots"][0])
        slot.update(override_message="assign-custom", override_message_is_default=False)
        rendered = "\n".join(_render_slot(slot))
        self.assertIn("(override-message assign-custom)", rendered)
        self.assertNotIn("(override-message put-id)", rendered)

    def test_message_dispatch_errors_are_not_parser_success(self):
        output = "[MSGFUN1] No applicable primary message-handlers found for DEFAULT."
        self.assertTrue(any(marker in output for marker in ERROR_MARKERS))

    def clips(self):
        executable = shutil.which(os.environ.get("CLIPS", "clips"))
        if not executable:
            self.skipTest("stock CLIPS is required for the live activation regression")
        return executable

    def test_all_thirteen_activation_witnesses_match_bsave(self):
        output, report = witnesses.run_activation_witnesses(self.source, self.clips())
        self.assertEqual(report["scenario_count"], 13)
        self.assertEqual(report["matching_scenario_count"], 13)
        self.assertEqual(report["mismatch_count"], 0)
        cases = {case["name"]: case for case in report["scenarios"]}
        self.assertEqual(cases["ustaw_pa_object_match"]["actual"],
                         [{"name": "ustaw_PA_0", "salience": -8900}])
        self.assertEqual(cases["ustaw_pa_object_zero"]["actual"], [])
        self.assertFalse(any(marker in output for marker in ERROR_MARKERS))

    def test_failed_object_creation_cannot_pass_negative_witness(self):
        # On the old projection the PA=0 case falsely passed: both an absent
        # object and a successfully created zero-AP object give an empty agenda.
        executable = self.clips()
        program, manifest = witnesses.render_recovered_program(self.source, self.ir)
        broken = re.sub(r"\(override-message put-[^()\s]+\)",
                        "(override-message DEFAULT)", program)
        self.assertNotEqual(program, broken)
        zero_case = [case for case in witnesses.SCENARIOS if case["name"] == "ustaw_pa_object_zero"]
        with patch.object(witnesses, "render_recovered_program", return_value=(broken, manifest)), \
                patch.object(witnesses, "SCENARIOS", zero_case):
            with self.assertRaisesRegex(AssertionError, "CLIPS reported parser/runtime diagnostics"):
                witnesses.run_activation_witnesses(self.source, executable)


if __name__ == "__main__":
    unittest.main()
