from __future__ import annotations

import contextlib
from dataclasses import replace
import hashlib
import importlib.util
import io
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools/compare_campaign_checkpoints.py"
SPEC = importlib.util.spec_from_file_location("campaign_checkpoint_compare", TOOL)
assert SPEC is not None and SPEC.loader is not None
checkpoint = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = checkpoint
SPEC.loader.exec_module(checkpoint)


def synthetic_dat(stack: int = 4, player: int = 0, path_count: int = 0) -> bytes:
    raw = bytearray(586414)
    raw[:16] = b"SYNTHETIC TEST\x00\x00"
    struct.pack_into("<iiii", raw, 16 + 140000, 100, 100, 47, 48)
    struct.pack_into("<i", raw, 16 + 140017, 5)
    struct.pack_into("<H", raw, 16 + 140022, 6)
    struct.pack_into("<ii", raw, 16 + 147139, player, player)
    base = 16 + 147174 + 725 * stack
    struct.pack_into("<hhBB", raw, base, 49, 50, player, 3)
    for slot in range(10):
        offset = base + 6 + 31 * slot
        struct.pack_into("<h", raw, offset, -1)
    for slot, ap in ((0, 2), (1, 7)):
        offset = base + 6 + 31 * slot
        struct.pack_into("<h", raw, offset, slot + 1)
        raw[offset + 2] = player
        raw[offset + 8] = ap
        raw[offset + 9] = 100
    struct.pack_into("<i", raw, base + 316, path_count)
    for waypoint in range(max(0, min(path_count, 100))):
        struct.pack_into("<BBH", raw, base + 320 + waypoint * 4, 50, 51, 6 + waypoint)
    visibility = 16 + 140024 + player * 1423 + 57
    raw[visibility] = 3
    raw[visibility + 1299] = 128
    for tile in range(10000):
        struct.pack_into("<H", raw, 16 + tile * 14 + 4, 65535)
    struct.pack_into("<H", raw, 16 + 14 * (50 * 100 + 49) + 4, 879)
    return bytes(raw)


class CampaignCheckpointTests(unittest.TestCase):
    def setUp(self):
        self.raw = synthetic_dat()
        self.reference = checkpoint.decode_snapshot(self.raw, 4, 0)
        self.base = 16 + 147174 + 725 * 4
        self.visibility = 16 + 140024 + 57

    def compare(self, raw: bytes, expected=None):
        return checkpoint.compare_snapshots(
            self.reference, checkpoint.decode_snapshot(raw, 4, 0), expected or {}
        )

    def mutate(self, offset: int, value: int | None = None) -> bytes:
        raw = bytearray(self.raw)
        raw[offset] = raw[offset] ^ 1 if value is None else value
        return bytes(raw)

    def region(self, result, name):
        return next(item for item in result["regions"] if item["name"] == name)

    def test_layout_sizes_and_state_decoding(self):
        self.assertEqual(len(self.raw), checkpoint.DAT_BYTES)
        self.assertEqual(self.reference.state["position"], [49, 50])
        self.assertEqual(self.reference.state["min_ap"], 2)
        self.assertEqual(self.reference.state["occupied_slots"], 2)
        self.assertEqual(self.reference.state["visibility_set_bits"], 3)
        sizes = {region.name: len(region.data) for region in self.reference.regions}
        self.assertEqual(sizes, dict(world_header=24, turn_and_viewed_player=8,
                                     stack_header=6, unit_slots=310, active_path=4,
                                     stack_hidden_flag=1, player_visibility=1300, road_overlays=20000))

    def test_matching_scope_never_claims_gameplay_or_provenance(self):
        result = self.compare(self.raw, {"mission": 5, "turn": 6})
        self.assertEqual(result["status"], "match")
        for field in ("reference_provenance_verified", "authentic_route_verified",
                      "visual_equivalence_verified", "campaign_completion_verified"):
            self.assertIs(result[field], False)
        self.assertEqual(result["expectations"], {"mission": 5, "turn": 6})
        self.assertEqual(result["reference"]["dat_sha256"], hashlib.sha256(self.raw).hexdigest())
        self.assertIn("FAC sidecars", result["not_compared"])

    def test_every_world_header_and_turn_view_byte_is_compared(self):
        for start, size, name in ((16 + 140000, 24, "world_header"), (16 + 147139, 8, "turn_and_viewed_player")):
            for offset in range(start, start + size):
                with self.subTest(offset=offset):
                    result = self.compare(self.mutate(offset))
                    self.assertEqual(result["status"], "mismatch")
                    self.assertEqual(self.region(result, name)["differing_bytes"], 1)

    def test_stack_coordinates_owner_facing_and_hidden_are_compared(self):
        for offset in (0, 2, 4, 5, 720):
            with self.subTest(offset=offset):
                self.assertEqual(self.compare(self.mutate(self.base + offset))["status"], "mismatch")

    def test_every_byte_in_all_ten_slots_is_compared_including_empty_slots(self):
        for offset in range(310):
            with self.subTest(slot=offset // 31, byte=offset % 31):
                result = self.compare(self.mutate(self.base + 6 + offset))
                region = self.region(result, "unit_slots")
                self.assertEqual(region["differing_bytes"], 1)
                self.assertEqual(region["first_differences"][0]["candidate_file_offset"], self.base + 6 + offset)

    def test_equal_minimum_ap_does_not_hide_other_slot_changes(self):
        changed = self.mutate(self.base + 6 + 31 + 8, 8)
        candidate = checkpoint.decode_snapshot(changed, 4, 0)
        self.assertEqual(candidate.state["min_ap"], self.reference.state["min_ap"])
        self.assertEqual(self.compare(changed)["status"], "mismatch")

    def test_equal_visibility_counts_do_not_hide_different_bits(self):
        changed = self.mutate(self.visibility, 5)
        result = self.compare(changed)
        self.assertEqual(result["reference"]["state"]["visibility_set_bits"], result["candidate"]["state"]["visibility_set_bits"])
        self.assertNotEqual(result["reference"]["state"]["visibility_sha256"], result["candidate"]["state"]["visibility_sha256"])
        self.assertEqual(self.region(result, "player_visibility")["differing_bytes"], 1)
        self.assertEqual(result["status"], "mismatch")

    def test_visibility_tail_is_not_truncated(self):
        result = self.compare(self.mutate(self.visibility + 1299))
        sample = self.region(result, "player_visibility")["first_differences"][0]
        self.assertEqual(sample["reference_file_offset"], self.visibility + 1299)

    def test_every_road_cell_byte_has_exact_file_offset(self):
        region = self.reference.regions[-1]
        for index in range(20000):
            self.assertEqual(region.file_offset(index), 16 + (index // 2) * 14 + 4 + index % 2)
        for tile in (0, 4950, 5049, 9999):
            for byte in (0, 1):
                offset = 16 + tile * 14 + 4 + byte
                with self.subTest(tile=tile, byte=byte):
                    result = self.compare(self.mutate(offset))
                    road = self.region(result, "road_overlays")
                    self.assertEqual(road["differing_bytes"], 1)
                    self.assertEqual(road["first_differences"][0]["candidate_file_offset"], offset)

    def test_transposed_roads_do_not_pass(self):
        raw = bytearray(self.raw)
        first, second = 16 + 14 * 5049 + 4, 16 + 14 * 4950 + 4
        raw[first:first + 2], raw[second:second + 2] = raw[second:second + 2], raw[first:first + 2]
        self.assertEqual(self.compare(bytes(raw))["status"], "mismatch")

    def test_active_path_compares_cost_and_coordinates(self):
        raw = synthetic_dat(path_count=2)
        reference = checkpoint.decode_snapshot(raw, 4, 0)
        for byte in range(8):
            changed = bytearray(raw)
            changed[self.base + 320 + byte] ^= 1
            result = checkpoint.compare_snapshots(reference, checkpoint.decode_snapshot(bytes(changed), 4, 0), {})
            self.assertEqual(self.region(result, "active_path")["differing_bytes"], 1)

    def test_different_path_lengths_include_unpaired_bytes(self):
        candidate = checkpoint.decode_snapshot(synthetic_dat(path_count=1), 4, 0)
        for left, right in ((self.reference, candidate), (candidate, self.reference)):
            result = checkpoint.compare_snapshots(left, right, {})
            path = self.region(result, "active_path")
            self.assertEqual(path["differing_bytes"], 5)
            self.assertEqual(sorted((path["reference_bytes"], path["candidate_bytes"])), [4, 8])
            self.assertIsNone(path["first_differences"][1]["reference_byte"] if left is self.reference else path["first_differences"][1]["candidate_byte"])

    def test_maximum_path_count_checks_last_waypoint(self):
        raw = synthetic_dat(path_count=100)
        left = checkpoint.decode_snapshot(raw, 4, 0)
        changed = bytearray(raw)
        changed[self.base + 719] ^= 1
        result = checkpoint.compare_snapshots(left, checkpoint.decode_snapshot(bytes(changed), 4, 0), {})
        self.assertEqual(self.region(result, "active_path")["reference_bytes"], 404)
        self.assertEqual(self.region(result, "active_path")["differing_bytes"], 1)

    def test_inactive_paths_labels_and_fact_handles_are_explicitly_outside_scope(self):
        raw = bytearray(self.raw)
        for offset in (0, self.base + 320, self.base + 719, self.base + 721, self.base + 724):
            raw[offset] ^= 1
        result = self.compare(bytes(raw))
        self.assertEqual(result["status"], "match")
        self.assertNotEqual(result["reference"]["dat_sha256"], result["candidate"]["dat_sha256"])
        self.assertIn("inactive waypoint storage", result["not_compared"])
        self.assertIn("cached rules fact handle", result["not_compared"])

    def test_other_players_and_nonroad_tile_data_are_outside_scope(self):
        for offset in (self.visibility + 1423, 16, 16 + 2, 16 + 6, 16 + 139999):
            with self.subTest(offset=offset):
                self.assertEqual(self.compare(self.mutate(offset))["status"], "match")

    def test_last_player_and_stack_indices_do_not_alias_first(self):
        raw = synthetic_dat(stack=499, player=4)
        left = checkpoint.decode_snapshot(raw, 499, 4)
        self.assertEqual(left.state["stack_owner"], 4)
        self.assertEqual(left.state["min_ap"], 2)
        changed = bytearray(raw)
        offset = 16 + 140024 + 4 * 1423 + 57 + 1299
        changed[offset] ^= 1
        result = checkpoint.compare_snapshots(left, checkpoint.decode_snapshot(bytes(changed), 499, 4), {})
        self.assertEqual(self.region(result, "player_visibility")["first_differences"][0]["reference_file_offset"], offset)

    def test_invalid_indices_are_rejected(self):
        for stack, player in ((-1, 0), (500, 0), (4, -1), (4, 5), (True, 0), (4, False)):
            with self.subTest(stack=stack, player=player), self.assertRaises(ValueError):
                checkpoint.decode_snapshot(self.raw, stack, player)

    def test_wrong_lengths_and_raw_memory_images_are_rejected(self):
        for raw in (b"", self.raw[:-1], self.raw[16:], self.raw + b"x"):
            with self.subTest(size=len(raw)), self.assertRaises(ValueError):
                checkpoint.decode_snapshot(raw, 4, 0)

    def test_invalid_path_counts_are_rejected(self):
        for count in (-1, 101, -2147483648, 2147483647):
            with self.subTest(count=count), self.assertRaisesRegex(ValueError, "path count"):
                checkpoint.decode_snapshot(synthetic_dat(path_count=count), 4, 0)

    def test_empty_stack_and_out_of_grid_positions_are_rejected(self):
        raw = bytearray(self.raw)
        for slot in range(10):
            struct.pack_into("<h", raw, self.base + 6 + slot * 31, -1)
        with self.assertRaisesRegex(ValueError, "no occupied"):
            checkpoint.decode_snapshot(bytes(raw), 4, 0)
        for position in ((-1, 50), (49, 100)):
            raw = bytearray(self.raw)
            struct.pack_into("<hh", raw, self.base, *position)
            with self.assertRaisesRegex(ValueError, "coordinates"):
                checkpoint.decode_snapshot(bytes(raw), 4, 0)

    def test_expectations_validate_both_sides_even_when_bytes_match(self):
        result = self.compare(self.raw, {"turn": 7, "position": [48, 50], "min_ap": 16})
        self.assertEqual(result["status"], "mismatch")
        self.assertEqual(len(result["expectation_failures"]), 6)
        self.assertEqual({failure["side"] for failure in result["expectation_failures"]}, {"reference", "candidate"})

    def test_unknown_expectations_and_different_selections_fail(self):
        with self.assertRaisesRegex(ValueError, "unknown expected"):
            self.compare(self.raw, {"trun": 6})
        candidate = checkpoint.decode_snapshot(synthetic_dat(stack=5), 5, 0)
        with self.assertRaisesRegex(ValueError, "same stack"):
            checkpoint.compare_snapshots(self.reference, candidate, {})

    def test_missing_reordered_and_incompatible_regions_fail(self):
        for regions in ((), self.reference.regions[:-1], tuple(reversed(self.reference.regions))):
            with self.assertRaisesRegex(ValueError, "regions"):
                checkpoint.compare_snapshots(self.reference, replace(self.reference, regions=regions), {})
        regions = list(self.reference.regions)
        regions[-1] = replace(regions[-1], stride=2)
        with self.assertRaisesRegex(ValueError, "layouts"):
            checkpoint.compare_snapshots(self.reference, replace(self.reference, regions=tuple(regions)), {})

    def test_all_differences_are_counted_when_samples_are_capped(self):
        raw = bytearray(self.raw)
        for byte in range(20):
            raw[self.visibility + byte] ^= 1
        region = self.region(self.compare(bytes(raw)), "player_visibility")
        self.assertEqual(region["differing_bytes"], 20)
        self.assertEqual(len(region["first_differences"]), 8)


class CampaignCheckpointCLITests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        self.reference = self.root / "reference.dat"
        self.candidate = self.root / "candidate.dat"
        self.raw = synthetic_dat()
        self.reference.write_bytes(self.raw)
        self.candidate.write_bytes(self.raw)

    def run_cli(self, extra=(), candidate=None):
        return subprocess.run([sys.executable, str(TOOL), str(self.reference),
                               str(candidate or self.candidate), "--stack", "4", "--player", "0", *extra],
                              text=True, capture_output=True, timeout=10)

    def test_success_json_and_input_bytes_unchanged(self):
        result = self.run_cli(("--json", "--mission", "5", "--turn", "6", "--position", "49", "50",
                               "--min-ap", "2", "--failure-flag", "0", "--require-no-path"))
        self.assertEqual(result.returncode, 0, result.stderr)
        parsed = json.loads(result.stdout)
        self.assertEqual(parsed["status"], "match")
        self.assertEqual(parsed["expectations"]["active_path_count"], 0)
        self.assertEqual(parsed["reference"]["path"], str(self.reference))
        self.assertEqual(self.reference.read_bytes(), self.raw)
        self.assertEqual(self.candidate.read_bytes(), self.raw)

    def test_mismatch_json_is_nonzero_and_contains_evidence(self):
        raw = bytearray(self.raw)
        raw[16 + 140022] = 7
        self.candidate.write_bytes(raw)
        result = self.run_cli(("--json", "--turn", "6"))
        self.assertEqual(result.returncode, 1, result.stderr)
        parsed = json.loads(result.stdout)
        self.assertEqual(parsed["status"], "mismatch")
        self.assertEqual(parsed["expectation_failures"][0]["side"], "candidate")

    def test_visibility_digest_expectation_is_exact(self):
        digest = hashlib.sha256(self.raw[16 + 140081:16 + 140081 + 1300]).hexdigest()
        self.assertEqual(self.run_cli(("--visibility-sha256", digest.upper())).returncode, 0)
        result = self.run_cli(("--visibility-sha256", "0" * 64, "--json"))
        self.assertEqual(result.returncode, 1)
        self.assertEqual(len(json.loads(result.stdout)["expectation_failures"]), 2)

    def test_same_path_hardlink_and_symlink_are_rejected(self):
        paths = [self.reference]
        hardlink, symlink = self.root / "hardlink.dat", self.root / "symlink.dat"
        os.link(self.reference, hardlink)
        symlink.symlink_to(self.reference)
        paths.extend((hardlink, symlink))
        for path in paths:
            with self.subTest(path=path):
                result = self.run_cli(candidate=path)
                self.assertEqual(result.returncode, 2)
                self.assertIn("distinct files", result.stderr)
                self.assertEqual(result.stdout, "")

    def test_missing_truncated_oversized_and_directory_inputs_fail(self):
        paths = [self.root / "missing.dat", self.root]
        for name, raw in (("short.dat", self.raw[:-1]), ("long.dat", self.raw + b"x" * 100)):
            path = self.root / name
            path.write_bytes(raw)
            paths.append(path)
        for path in paths:
            with self.subTest(path=path):
                result = self.run_cli(("--json",), candidate=path)
                self.assertEqual(result.returncode, 2)
                self.assertEqual(result.stdout, "")
                self.assertNotIn("Traceback", result.stderr)

    @unittest.skipUnless(hasattr(os, "mkfifo"), "FIFO fixture requires POSIX")
    def test_fifo_is_rejected_without_waiting_for_a_writer(self):
        fifo = self.root / "fifo.dat"
        os.mkfifo(fifo)
        self.assertEqual(self.run_cli(candidate=fifo).returncode, 2)

    def test_invalid_cli_arguments_fail_without_reporting_a_match(self):
        for extra in (("--stack", "500"), ("--player", "-1"), ("--turn", "65536"),
                      ("--mission", "20"), ("--position", "-1", "50"), ("--min-ap", "256"),
                      ("--min-ap", "wrong"), ("--failure-flag", "256"),
                      ("--visibility-sha256", "not-a-hash"), ("--unexpected",)):
            with self.subTest(extra=extra):
                result = self.run_cli(extra)
                self.assertEqual(result.returncode, 2)
                self.assertEqual(result.stdout, "")

    def test_stack_and_player_selections_are_mandatory(self):
        result = subprocess.run([sys.executable, str(TOOL), str(self.reference), str(self.candidate)],
                                capture_output=True, text=True, timeout=10)
        self.assertEqual(result.returncode, 2)
        self.assertIn("required", result.stderr)

    def test_text_output_and_help(self):
        result = self.run_cli()
        self.assertEqual(result.returncode, 0)
        self.assertIn("MATCH: bounded checkpoint comparison only", result.stdout)
        with contextlib.redirect_stdout(io.StringIO()) as output, self.assertRaises(SystemExit) as exit_state:
            checkpoint.main(["--help"])
        self.assertEqual(exit_state.exception.code, 0)
        self.assertIn("--require-no-path", output.getvalue())


if __name__ == "__main__":
    unittest.main()
