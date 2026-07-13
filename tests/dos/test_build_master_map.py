import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "dos"))

import build_master_map as builder


class MasterMapTests(unittest.TestCase):
    def test_registered_ground_truth_rejects_conflicting_direct_evidence(self):
        master, conflicts, dropped = builder.merge_sources(
            existing={0x100: {"name": "GroundTruth"}},
            registered={0x100: {"name": "GroundTruth"}},
            anchors={0x100: {"name": "WrongName", "evidence": "error id"}},
            string_matches={},
            alignments={},
            transfers={},
        )
        self.assertEqual(master[0x100]["name"], "GroundTruth")
        self.assertEqual(conflicts, [])
        self.assertEqual(dropped[0]["dropped_anchor"], "WrongName")

    def test_alignment_only_fills_unnamed_address(self):
        master, conflicts, _ = builder.merge_sources(
            existing={0x100: {"name": "Existing"}},
            registered={},
            anchors={},
            string_matches={},
            alignments={0x100: {"name": "Replacement"}, 0x200: {"name": "NewAlignment"}},
            transfers={},
        )
        self.assertEqual(master[0x100]["name"], "Existing")
        self.assertEqual(master[0x200]["name"], "NewAlignment")
        self.assertEqual(conflicts[0]["kind"], "clips-align-cannot-overwrite")

    def test_transfer_name_collision_is_rejected(self):
        master, conflicts, _ = builder.merge_sources(
            existing={0x100: {"name": "Existing"}},
            registered={},
            anchors={},
            string_matches={},
            alignments={},
            transfers={0x200: {"name": "Existing", "source": "clash95-transfer"}},
        )
        self.assertNotIn(0x200, master)
        self.assertEqual(conflicts[0]["kind"], "clash95-transfer-name-collision")

    def test_output_rows_are_sorted_by_address(self):
        rows = builder.canonical_rows({
            0x200: {"name": "B", "source": "existing"},
            0x100: {"name": "A", "source": "existing"},
        })
        self.assertEqual([row["ea"] for row in rows], ["0x100", "0x200"])


if __name__ == "__main__":
    unittest.main()
