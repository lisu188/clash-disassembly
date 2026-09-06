from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from dataclasses import dataclass
from itertools import zip_longest
from pathlib import Path
from typing import Any, Callable, Sequence


LABEL_BYTES = 16
GAME_DATA_BYTES = 586398
DAT_BYTES = LABEL_BYTES + GAME_DATA_BYTES
WORLD_HEADER_OFFSET = 140000
WORLD_HEADER_BYTES = 24
PLAYER_TABLE_OFFSET = 140024
PLAYER_RECORD_BYTES = 1423
PLAYER_COUNT = 5
VISIBILITY_OFFSET = 57
VISIBILITY_BYTES = 1300
TURN_VIEW_OFFSET = 147139
STACK_TABLE_OFFSET = 147174
STACK_RECORD_BYTES = 725
STACK_COUNT = 500
SLOT_OFFSET = 6
SLOT_BYTES = 31
SLOT_COUNT = 10
SLOT_AP_OFFSET = 8
PATH_OFFSET = 316
WAYPOINT_BYTES = 4
WAYPOINT_CAPACITY = 100
STACK_HIDDEN_OFFSET = 720
TILE_BYTES = 14
TILE_COUNT = 10000
ROAD_OFFSET = 4
SAMPLE_LIMIT = 8
REGION_NAMES = ("world_header", "turn_and_viewed_player", "stack_header", "unit_slots",
                "active_path", "stack_hidden_flag", "player_visibility", "road_overlays")


@dataclass(frozen=True)
class Region:
    name: str
    offset: int
    data: bytes
    stride: int = 1
    item_bytes: int = 1

    def file_offset(self, index: int) -> int:
        return LABEL_BYTES + self.offset + index // self.item_bytes * self.stride + index % self.item_bytes


@dataclass(frozen=True)
class Snapshot:
    sha256: str
    state: dict[str, Any]
    regions: tuple[Region, ...]


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def bounded_index(value: int, limit: int, name: str) -> None:
    if type(value) is not int or not 0 <= value < limit:
        raise ValueError(f"{name} must be in 0..{limit - 1}")


def decode_snapshot(raw: bytes, stack_index: int, player_index: int) -> Snapshot:
    bounded_index(stack_index, STACK_COUNT, "stack index")
    bounded_index(player_index, PLAYER_COUNT, "player index")
    if len(raw) != DAT_BYTES:
        raise ValueError(f"expected {DAT_BYTES} DAT bytes, got {len(raw)}")
    data = raw[LABEL_BYTES:]
    base = STACK_TABLE_OFFSET + stack_index * STACK_RECORD_BYTES
    path_count = struct.unpack_from("<i", data, base + PATH_OFFSET)[0]
    if not 0 <= path_count <= WAYPOINT_CAPACITY:
        raise ValueError(f"stack {stack_index}: invalid active path count {path_count}")
    slots = data[base + SLOT_OFFSET:base + PATH_OFFSET]
    occupied_ap = [
        slots[index * SLOT_BYTES + SLOT_AP_OFFSET]
        for index in range(SLOT_COUNT)
        if struct.unpack_from("<h", slots, index * SLOT_BYTES)[0] != -1
    ]
    if not occupied_ap:
        raise ValueError(f"stack {stack_index}: no occupied unit slots")
    visibility_start = PLAYER_TABLE_OFFSET + player_index * PLAYER_RECORD_BYTES + VISIBILITY_OFFSET
    visibility = data[visibility_start:visibility_start + VISIBILITY_BYTES]
    position = list(struct.unpack_from("<hh", data, base))
    if any(not 0 <= coordinate < 100 for coordinate in position):
        raise ValueError(f"stack {stack_index}: coordinates outside the stored 100x100 grid: {position}")
    state = {
        "mission": struct.unpack_from("<i", data, WORLD_HEADER_OFFSET + 17)[0],
        "turn": struct.unpack_from("<H", data, WORLD_HEADER_OFFSET + 22)[0],
        "failure_flag": data[WORLD_HEADER_OFFSET + 21],
        "turn_owner": struct.unpack_from("<i", data, TURN_VIEW_OFFSET)[0],
        "viewed_player": struct.unpack_from("<i", data, TURN_VIEW_OFFSET + 4)[0],
        "stack_index": stack_index,
        "player_index": player_index,
        "position": position,
        "stack_owner": data[base + 4],
        "occupied_slots": len(occupied_ap),
        "min_ap": min(occupied_ap),
        "active_path_count": path_count,
        "visibility_set_bits": sum(value.bit_count() for value in visibility),
        "visibility_sha256": digest(visibility),
    }
    roads = b"".join(data[index * TILE_BYTES + ROAD_OFFSET:index * TILE_BYTES + ROAD_OFFSET + 2]
                     for index in range(TILE_COUNT))
    regions = (
        Region("world_header", WORLD_HEADER_OFFSET, data[WORLD_HEADER_OFFSET:WORLD_HEADER_OFFSET + WORLD_HEADER_BYTES]),
        Region("turn_and_viewed_player", TURN_VIEW_OFFSET, data[TURN_VIEW_OFFSET:TURN_VIEW_OFFSET + 8]),
        Region("stack_header", base, data[base:base + SLOT_OFFSET]),
        Region("unit_slots", base + SLOT_OFFSET, slots),
        Region("active_path", base + PATH_OFFSET,
               data[base + PATH_OFFSET:base + PATH_OFFSET + 4 + path_count * WAYPOINT_BYTES]),
        Region("stack_hidden_flag", base + STACK_HIDDEN_OFFSET, data[base + STACK_HIDDEN_OFFSET:base + STACK_HIDDEN_OFFSET + 1]),
        Region("player_visibility", visibility_start, visibility),
        Region("road_overlays", ROAD_OFFSET, roads, TILE_BYTES, 2),
    )
    return Snapshot(digest(raw), state, regions)


def compare_region(reference: Region, candidate: Region) -> dict[str, Any]:
    if (reference.name, reference.offset, reference.stride, reference.item_bytes) != (
        candidate.name, candidate.offset, candidate.stride, candidate.item_bytes
    ):
        raise ValueError("comparison region layouts differ")
    differences = 0
    samples = []
    for index, (left, right) in enumerate(zip_longest(reference.data, candidate.data)):
        if left == right:
            continue
        differences += 1
        if len(samples) < SAMPLE_LIMIT:
            samples.append({
                "reference_file_offset": reference.file_offset(index) if left is not None else None,
                "candidate_file_offset": candidate.file_offset(index) if right is not None else None,
                "reference_byte": left,
                "candidate_byte": right,
            })
    return {
        "name": reference.name,
        "reference_bytes": len(reference.data),
        "candidate_bytes": len(candidate.data),
        "reference_sha256": digest(reference.data),
        "candidate_sha256": digest(candidate.data),
        "differing_bytes": differences,
        "first_differences": samples,
    }


def compare_snapshots(reference: Snapshot, candidate: Snapshot, expected: dict[str, Any]) -> dict[str, Any]:
    for snapshot in (reference, candidate):
        if tuple(region.name for region in snapshot.regions) != REGION_NAMES:
            raise ValueError("missing or reordered checkpoint regions")
    unknown = set(expected) - set(reference.state)
    if unknown:
        raise ValueError(f"unknown expected fields: {', '.join(sorted(unknown))}")
    if (reference.state["stack_index"], reference.state["player_index"]) != (
        candidate.state["stack_index"], candidate.state["player_index"]
    ):
        raise ValueError("reference and candidate must select the same stack and player")
    regions = [compare_region(left, right) for left, right in zip(reference.regions, candidate.regions, strict=True)]
    failures = [
        {"side": side, "field": field, "expected": value, "actual": snapshot.state[field]}
        for side, snapshot in (("reference", reference), ("candidate", candidate))
        for field, value in expected.items()
        if snapshot.state[field] != value
    ]
    return {
        "schema_version": 1,
        "status": "match" if not failures and not any(item["differing_bytes"] for item in regions) else "mismatch",
        "comparison_scope": "selected campaign checkpoint fields; not whole-save or gameplay equivalence",
        "reference_provenance_verified": False,
        "authentic_route_verified": False,
        "visual_equivalence_verified": False,
        "campaign_completion_verified": False,
        "reference": {"dat_sha256": reference.sha256, "state": reference.state},
        "candidate": {"dat_sha256": candidate.sha256, "state": candidate.state},
        "expectations": dict(expected),
        "expectation_failures": failures,
        "regions": regions,
        "not_compared": [
            "save label", "inactive waypoint storage", "cached rules fact handle",
            "FAC sidecars", "other stacks and buildings", "terrain and non-road tile fields",
            "other player state", "options and port state", "runtime input and rendered frames",
        ],
    }


def read_dat(path: Path) -> bytes:
    if not path.is_file():
        raise ValueError(f"{path}: expected a regular DAT file")
    with path.open("rb") as stream:
        data = stream.read(DAT_BYTES + 1)
    if len(data) != DAT_BYTES:
        raise ValueError(f"{path}: expected exactly {DAT_BYTES} DAT bytes, got {'at least ' if len(data) > DAT_BYTES else ''}{len(data)}")
    return data


def integer_range(lower: int, upper: int) -> Callable[[str], int]:
    def parse(value: str) -> int:
        number = int(value)
        if not lower <= number <= upper:
            raise argparse.ArgumentTypeError(f"expected {lower}..{upper}, got {value}")
        return number
    return parse


def sha256_argument(value: str) -> str:
    if len(value) != 64 or any(character not in "0123456789abcdefABCDEF" for character in value):
        raise argparse.ArgumentTypeError("expected a 64-character SHA256 hex digest")
    return value.lower()


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Read-only, bounded comparison of original and reconstructed campaign DAT checkpoints")
    parser.add_argument("reference", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--stack", type=integer_range(0, STACK_COUNT - 1), required=True)
    parser.add_argument("--player", type=integer_range(0, PLAYER_COUNT - 1), required=True)
    parser.add_argument("--mission", type=integer_range(0, 19))
    parser.add_argument("--turn", type=integer_range(0, 65535))
    parser.add_argument("--position", type=integer_range(0, 99), nargs=2, metavar=("ROW_FIELD", "COLUMN_FIELD"))
    parser.add_argument("--min-ap", type=integer_range(0, 255))
    parser.add_argument("--failure-flag", type=integer_range(0, 255))
    parser.add_argument("--visibility-sha256", type=sha256_argument)
    parser.add_argument("--require-no-path", action="store_true")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args(argv)
    try:
        if args.reference.samefile(args.candidate):
            raise ValueError("reference and candidate must be distinct files, not aliases of the same file")
        expected = {field: getattr(args, field) for field in (
            "mission", "turn", "position", "min_ap", "failure_flag", "visibility_sha256"
        ) if getattr(args, field) is not None}
        if args.require_no_path:
            expected["active_path_count"] = 0
        reference = decode_snapshot(read_dat(args.reference), args.stack, args.player)
        candidate = decode_snapshot(read_dat(args.candidate), args.stack, args.player)
        result = compare_snapshots(reference, candidate, expected)
        result["reference"]["path"] = str(args.reference)
        result["candidate"]["path"] = str(args.candidate)
        if args.json:
            print(json.dumps(result, indent=2))
        else:
            print(f"{result['status'].upper()}: bounded checkpoint comparison only")
            for failure in result["expectation_failures"]:
                print(f"{failure['side']}.{failure['field']}: expected {failure['expected']!r}, got {failure['actual']!r}")
            for region in result["regions"]:
                print(f"{region['name']}: {region['differing_bytes']} differing bytes")
        return 0 if result["status"] == "match" else 1
    except (OSError, ValueError, struct.error) as exc:
        print(f"compare_campaign_checkpoints.py: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
