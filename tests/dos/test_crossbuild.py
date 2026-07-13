import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "dos"))

import crossbuild_match as matcher


class CrossBuildMatcherTests(unittest.TestCase):
    def test_multiline_ida_signature_and_literal_reference(self):
        text = '''char aShared[7] = "shared";
//----- (00020000) --------------------------------------------------------
int __cdecl
sub_20000(
        int a1,
        int a2)
{
  return puts(aShared) + a1 + a2;
}
'''
        parsed = matcher.parse_ida_c_text(text)
        self.assertEqual(parsed[0x20000]["name"], "sub_20000")
        self.assertEqual(parsed[0x20000]["literals"], ["shared"])

    def test_feature_export_normalizes_structural_review_fields(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "features.json"
            path.write_text(json.dumps({"functions": [{
                "ea": "0x20000",
                "name": "sub_20000",
                "bb": 3,
                "size": 20,
                "edges": 4,
                "back_edges": 1,
                "constants": ["0x20", "0x10"],
                "callees": ["0x30000"],
                "data_refs": ["0x40000"],
                "literals": ["shared"]
            }]}), encoding="utf-8")
            row = matcher.load_feature_export(path)[0x20000]
        self.assertEqual(row["constants"], ["0x10", "0x20"])
        self.assertEqual(row["edges"], 4)
        self.assertEqual(row["back_edges"], 1)
        candidate = matcher.candidate_row(0x20000, 0x50000, ["shared"], row, row, {"name": "Named", "confidence": "high"})
        self.assertEqual(candidate["dos_data_refs"], ["0x40000"])
        self.assertEqual(candidate["dos_constants"], ["0x10", "0x20"])

    def test_shared_literal_must_be_unique_in_both_builds(self):
        dos = {
            1: {"literals": ["unique", "shared-many"]},
            2: {"literals": ["shared-many"]},
        }
        clash95 = {
            10: {"literals": ["unique", "shared-many"]},
            20: {"literals": ["shared-many"]},
        }
        pairs = matcher.unique_shared_pairs(dos, clash95, minimum_length=5)
        self.assertEqual(pairs, {(1, 10): {"unique"}})

    def test_pair_collapsing_keeps_multiple_literals(self):
        pairs = {(1, 10): {"alpha", "bravo"}}
        accepted, rejected = matcher.collapse_bijection(pairs)
        self.assertEqual(accepted[(1, 10)], ["alpha", "bravo"])
        self.assertEqual(rejected, [])

    def test_bijection_conflicts_are_rejected(self):
        pairs = {(1, 10): {"alpha"}, (1, 20): {"bravo"}}
        accepted, rejected = matcher.collapse_bijection(pairs)
        self.assertEqual(accepted, {})
        self.assertEqual(len(rejected), 2)
        self.assertTrue(all(row["reason"] == "bijection-conflict" for row in rejected))

    def test_confidence_and_basic_block_filters(self):
        dos = {
            0x20000: {"name": "sub_20000", "bb": 3, "size": 10, "literals": ["first-literal"], "callees": []},
            0x21000: {"name": "sub_21000", "bb": 2, "size": 10, "literals": ["second-literal"], "callees": []},
            0x22000: {"name": "sub_22000", "bb": 4, "size": 10, "literals": ["third-literal"], "callees": []},
        }
        clash95 = {
            0x400000: {"name": "NamedA", "bb": 4, "size": 10, "literals": ["first-literal"], "callees": []},
            0x401000: {"name": "NamedB", "bb": 4, "size": 10, "literals": ["second-literal"], "callees": []},
            0x402000: {"name": "NamedC", "bb": 4, "size": 10, "literals": ["third-literal"], "callees": []},
        }
        index = {
            0x400000: {"name": "NamedA", "confidence": "high"},
            0x401000: {"name": "NamedB", "confidence": "high"},
            0x402000: {"name": "NamedC", "confidence": "low"},
        }
        proposals, calibration, rejected = matcher.build_candidates(
            dos, clash95, index, {}, 0x12C6E, 0x88370, 3, 5
        )
        self.assertEqual([row["proposed_name"] for row in proposals], ["NamedA"])
        self.assertEqual(calibration, [])
        self.assertEqual({row["reason"] for row in rejected}, {"basic-block-gate", "clash95-confidence-gate"})

    def test_deterministic_ordering(self):
        rows = [{"dos_ea": hex(value)} for value in range(100)]
        selected_a = matcher.evenly_spaced(rows, 40)
        selected_b = matcher.evenly_spaced(rows, 40)
        self.assertEqual(selected_a, selected_b)
        self.assertEqual(len(selected_a), 40)
        self.assertEqual(selected_a[0], rows[0])
        self.assertEqual(selected_a[-1], rows[-1])

    def test_calibration_requires_complete_review_and_95_percent(self):
        calibration = [
            {"dos_ea": hex(0x90000 + index), "clash95_ea": hex(0x400000 + index), "proposed_name": f"N{index}"}
            for index in range(40)
        ]
        reviews = {
            "calibration": [
                {
                    "dos_ea": row["dos_ea"],
                    "clash95_ea": row["clash95_ea"],
                    "verdict": "CONFIRM" if index < 38 else "UNCERTAIN",
                    "reason": "reviewed",
                }
                for index, row in enumerate(calibration)
            ],
            "game": [],
        }
        _, _, _, summary = matcher.apply_reviews([], calibration, reviews)
        self.assertTrue(summary["complete"])
        self.assertTrue(summary["passed"])
        self.assertEqual(summary["confirmation_ratio"], 0.95)
        reviews["calibration"][0]["verdict"] = "REJECT"
        _, _, _, summary = matcher.apply_reviews([], calibration, reviews)
        self.assertFalse(summary["passed"])

    def test_rename_index_parser(self):
        text = '''| Old | New | Confidence | Area | Evidence |
|---|---|---|---|---|
| `sub_401000` | `World_DoThing` | high | world | literal |
'''
        parsed = matcher.parse_rename_index_text(text)
        self.assertEqual(parsed[0x401000]["name"], "World_DoThing")
        self.assertEqual(parsed[0x401000]["confidence"], "high")


if __name__ == "__main__":
    unittest.main()
