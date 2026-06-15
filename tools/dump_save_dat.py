#!/usr/bin/env python3
"""Inspect recovered Clash save-slot DAT files.

The save-slot DAT format is a 16-byte label followed by a raw gameData image.
This tool is intentionally read-only and only decodes fields with recovered
offset evidence.
"""

from __future__ import annotations

import argparse
import json
import os
import struct
import sys
from collections import Counter
from pathlib import Path
from typing import Any, Dict, Iterable, List, Optional, Tuple


LABEL_SIZE = 16
GAME_DATA_SIZE = 0x8F29E
DAT_SIZE = LABEL_SIZE + GAME_DATA_SIZE

PLAYER_DATA_STRIDE = 1423
PLAYER_RUNTIME_STATE_OFFSET = 140024
PLAYER_DISPLAY_NAME_OFFSET = 4
PLAYER_CAMERA_LEFT_OFFSET = 15
PLAYER_CAMERA_TOP_OFFSET = 19
PLAYER_MINIMAP_VISIBLE_OFFSET = 23
PLAYER_IS_HUMAN_OFFSET = 27
PLAYER_AI_INTELLIGENCE_OFFSET = 31
PLAYER_RELIGION_FLAG_OFFSET = 39
PLAYER_TECH_LEVEL_OFFSET = 47
PLAYER_LAST_REPORTED_TECH_LEVEL_OFFSET = 48
PLAYER_REVEALED_TILES_OFFSET = 57
PLAYER_REVEALED_TILES_SIZE = 1300
PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET = 1419
PLAYER_QUEEN_PORTRAIT_INDEX_OFFSET = 1420
PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN_OFFSET = 1421

MAP_THEME_INDEX_OFFSET = 140016
ACTIVE_MISSION_INDEX_OFFSET = 140017
GAME_TURN_COUNTER_OFFSET = 140022
MAP_WIDTH_TILES_OFFSET = 140000
MAP_HEIGHT_TILES_OFFSET = 140004
MAP_VIEW_LEFT_OFFSET = 140008
MAP_VIEW_TOP_OFFSET = 140012
TURN_OWNER_PLAYER_INDEX_OFFSET = 147139
VIEWED_PLAYER_INDEX_OFFSET = 147143

UNIT_STACK_TABLE_OFFSET = 147174
UNIT_STACK_STRIDE = 725
UNIT_STACK_COUNT = 500
UNIT_STACK_SLOT_BASE_OFFSET = 6
UNIT_STACK_SLOT_STRIDE = 31
UNIT_STACK_PATH_OFFSET = 316
UNIT_STACK_HIDDEN_OFFSET = 720

BUILDING_TABLE_OFFSET = 509674
BUILDING_RECORD_SIZE = 467
BUILDING_RECORD_COUNT = 100

TILE_MAP_OFFSET = 556374
TILE_MAP_SIZE = 20000
TILE_TRAP_OWNER_MASK_OFFSET = 576374
TILE_TRAP_OWNER_MASK_SIZE = 10000

PORT_ROW_OFFSET = 586374
PORT_COLUMN_OFFSET = 586378
PORT_NEXT_REINFORCEMENT_TURN_OFFSET = 586382
PORT_REINFORCEMENT_READY_FLAG_OFFSET = 586386
PORT_REINFORCEMENT_UNIT_COUNT_OFFSET = 586390
PORT_SHORE_VARIANT_FLAG_OFFSET = 586394


REGIONS: Tuple[Tuple[str, int, int], ...] = (
    ("label", 0, LABEL_SIZE),
    ("map_tile_records", LABEL_SIZE + 0, 140000),
    ("world_session_header", LABEL_SIZE + 140000, 24),
    ("player_runtime_records", LABEL_SIZE + PLAYER_RUNTIME_STATE_OFFSET, PLAYER_DATA_STRIDE * 5),
    ("turn_view_indices", LABEL_SIZE + TURN_OWNER_PLAYER_INDEX_OFFSET, 8),
    ("unknown_pre_unit_stack_gap", LABEL_SIZE + 147147, 27),
    ("unit_stack_records", LABEL_SIZE + UNIT_STACK_TABLE_OFFSET, UNIT_STACK_STRIDE * UNIT_STACK_COUNT),
    ("building_records", LABEL_SIZE + BUILDING_TABLE_OFFSET, BUILDING_RECORD_SIZE * BUILDING_RECORD_COUNT),
    ("occupancy_index_layer", LABEL_SIZE + TILE_MAP_OFFSET, TILE_MAP_SIZE),
    ("trap_owner_mask_layer", LABEL_SIZE + TILE_TRAP_OWNER_MASK_OFFSET, TILE_TRAP_OWNER_MASK_SIZE),
    ("port_runtime_state", LABEL_SIZE + PORT_ROW_OFFSET, 24),
)


def read_exact_dat(path: Path) -> bytes:
    data = path.read_bytes()
    if len(data) != DAT_SIZE:
        raise ValueError(f"{path}: expected {DAT_SIZE} bytes, got {len(data)}")
    return data


def unpack(fmt: str, data: bytes, offset: int) -> int:
    return struct.unpack_from(fmt, data, offset)[0]


def u8(data: bytes, offset: int) -> int:
    return data[offset]


def i8(data: bytes, offset: int) -> int:
    value = data[offset]
    return value - 256 if value >= 128 else value


def u16(data: bytes, offset: int) -> int:
    return unpack("<H", data, offset)


def i16(data: bytes, offset: int) -> int:
    return unpack("<h", data, offset)


def i32(data: bytes, offset: int) -> int:
    return unpack("<i", data, offset)


def decode_c_string(raw: bytes) -> str:
    head = raw.split(b"\x00", 1)[0]
    return head.decode("cp1250", errors="replace")


def decode_label(raw: bytes) -> Dict[str, Any]:
    return {
        "raw_hex": raw.hex(),
        "bytes": list(raw),
        "best_effort_text": decode_c_string(raw),
        "nul_terminated": b"\x00" in raw,
    }


def decode_world(game_data: bytes) -> Dict[str, int]:
    return {
        "map_width_tiles": i32(game_data, MAP_WIDTH_TILES_OFFSET),
        "map_height_tiles": i32(game_data, MAP_HEIGHT_TILES_OFFSET),
        "map_view_left": i32(game_data, MAP_VIEW_LEFT_OFFSET),
        "map_view_top": i32(game_data, MAP_VIEW_TOP_OFFSET),
        "map_theme_index": u8(game_data, MAP_THEME_INDEX_OFFSET),
        "active_mission_index": i32(game_data, ACTIVE_MISSION_INDEX_OFFSET),
        "game_turn_counter": u16(game_data, GAME_TURN_COUNTER_OFFSET),
        "turn_owner_player_index": i32(game_data, TURN_OWNER_PLAYER_INDEX_OFFSET),
        "viewed_player_index": i32(game_data, VIEWED_PLAYER_INDEX_OFFSET),
    }


def decode_players(game_data: bytes) -> Dict[str, Any]:
    players: List[Dict[str, Any]] = []
    active_count = 0
    human_count = 0
    for index in range(5):
        base = PLAYER_RUNTIME_STATE_OFFSET + PLAYER_DATA_STRIDE * index
        active = i32(game_data, base) != 0
        human = i32(game_data, base + PLAYER_IS_HUMAN_OFFSET) != 0
        if active:
            active_count += 1
        if human:
            human_count += 1
        revealed = game_data[
            base + PLAYER_REVEALED_TILES_OFFSET : base + PLAYER_REVEALED_TILES_OFFSET + PLAYER_REVEALED_TILES_SIZE
        ]
        players.append(
            {
                "index": index,
                "is_active": active,
                "display_name": decode_c_string(
                    game_data[base + PLAYER_DISPLAY_NAME_OFFSET : base + PLAYER_DISPLAY_NAME_OFFSET + 11]
                ),
                "camera_left": i32(game_data, base + PLAYER_CAMERA_LEFT_OFFSET),
                "camera_top": i32(game_data, base + PLAYER_CAMERA_TOP_OFFSET),
                "minimap_visible": i32(game_data, base + PLAYER_MINIMAP_VISIBLE_OFFSET) != 0,
                "controller_mode": i32(game_data, base + PLAYER_IS_HUMAN_OFFSET),
                "ai_intelligence": i32(game_data, base + PLAYER_AI_INTELLIGENCE_OFFSET),
                "religion_flag": i32(game_data, base + PLAYER_RELIGION_FLAG_OFFSET),
                "tech_level": u8(game_data, base + PLAYER_TECH_LEVEL_OFFSET),
                "last_reported_tech_level": u8(game_data, base + PLAYER_LAST_REPORTED_TECH_LEVEL_OFFSET),
                "revealed_tile_bytes_nonzero": sum(1 for value in revealed if value),
                "queen_relationship_state": i8(game_data, base + PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET),
                "queen_portrait_index": u8(game_data, base + PLAYER_QUEEN_PORTRAIT_INDEX_OFFSET),
                "queen_next_relationship_check_turn": u16(
                    game_data, base + PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN_OFFSET
                ),
            }
        )
    return {"active_count": active_count, "human_controller_count": human_count, "records": players}


def decode_unit_stacks(game_data: bytes) -> Dict[str, Any]:
    active_count = 0
    hidden_count = 0
    queued_path_count = 0
    owner_counts: Counter[str] = Counter()
    samples: List[Dict[str, Any]] = []
    for index in range(UNIT_STACK_COUNT):
        base = UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * index
        first_type = i16(game_data, base + UNIT_STACK_SLOT_BASE_OFFSET)
        active = 0 <= first_type <= 40
        if not active:
            continue
        active_count += 1
        owner = u8(game_data, base + 4)
        owner_counts[str(owner)] += 1
        if u8(game_data, base + UNIT_STACK_HIDDEN_OFFSET):
            hidden_count += 1
        if i32(game_data, base + UNIT_STACK_PATH_OFFSET):
            queued_path_count += 1
        if len(samples) < 12:
            occupied_slots = 0
            for slot in range(10):
                slot_type = i16(
                    game_data,
                    base + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * slot,
                )
                if 0 <= slot_type <= 40:
                    occupied_slots += 1
            samples.append(
                {
                    "index": index,
                    "tile_row": i16(game_data, base),
                    "tile_column": i16(game_data, base + 2),
                    "owner_player_index": owner,
                    "facing": u8(game_data, base + 5),
                    "first_unit_type_id": first_type,
                    "occupied_slot_count": occupied_slots,
                    "is_hidden_on_world_map": bool(u8(game_data, base + UNIT_STACK_HIDDEN_OFFSET)),
                    "queued_path_count": i32(game_data, base + UNIT_STACK_PATH_OFFSET),
                }
            )
    return {
        "record_count": UNIT_STACK_COUNT,
        "active_count": active_count,
        "hidden_count": hidden_count,
        "queued_path_count": queued_path_count,
        "active_by_owner": dict(sorted(owner_counts.items())),
        "active_samples": samples,
    }


def decode_buildings(game_data: bytes) -> Dict[str, Any]:
    active_count = 0
    completed_count = 0
    owner_counts: Counter[str] = Counter()
    samples: List[Dict[str, Any]] = []
    for index in range(BUILDING_RECORD_COUNT):
        base = BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * index
        construction = i16(game_data, base + 16)
        footprint_class = u8(game_data, base + 4)
        active = construction != -1 and footprint_class < 4
        if not active:
            continue
        active_count += 1
        if construction == 0:
            completed_count += 1
        owner = u8(game_data, base + 2)
        owner_counts[str(owner)] += 1
        if len(samples) < 12:
            samples.append(
                {
                    "index": index,
                    "tile_row": u8(game_data, base),
                    "tile_column": u8(game_data, base + 1),
                    "owner_player_index": owner,
                    "footprint_class": footprint_class,
                    "display_name": decode_c_string(game_data[base + 5 : base + 16]),
                    "construction_turns_remaining": construction,
                    "stored_money": unpack("<I", game_data, base + 438),
                    "castle_addon_flags": u8(game_data, base + 416),
                    "castle_fact_id": i32(game_data, base + 463),
                }
            )
    return {
        "record_count": BUILDING_RECORD_COUNT,
        "active_count": active_count,
        "completed_count": completed_count,
        "active_by_owner": dict(sorted(owner_counts.items())),
        "active_samples": samples,
    }


def decode_traps(game_data: bytes) -> Dict[str, Any]:
    trap_bytes = game_data[
        TILE_TRAP_OWNER_MASK_OFFSET : TILE_TRAP_OWNER_MASK_OFFSET + TILE_TRAP_OWNER_MASK_SIZE
    ]
    nonzero = [(idx // 100, idx % 100, value) for idx, value in enumerate(trap_bytes) if value]
    owner_bit_counts: Counter[str] = Counter()
    for _, _, mask in nonzero:
        for owner in range(8):
            if mask & (1 << owner):
                owner_bit_counts[str(owner)] += 1
    return {
        "nonzero_tile_count": len(nonzero),
        "owner_bit_counts": dict(sorted(owner_bit_counts.items())),
        "samples": [
            {"row": row, "column": column, "owner_mask": mask}
            for row, column, mask in nonzero[:12]
        ],
    }


def decode_port(game_data: bytes) -> Dict[str, int]:
    return {
        "port_tile_row": i32(game_data, PORT_ROW_OFFSET),
        "port_tile_column": i32(game_data, PORT_COLUMN_OFFSET),
        "next_reinforcement_turn": i32(game_data, PORT_NEXT_REINFORCEMENT_TURN_OFFSET),
        "reinforcement_ready_flag": i32(game_data, PORT_REINFORCEMENT_READY_FLAG_OFFSET),
        "pending_reinforcement_unit_count": i32(game_data, PORT_REINFORCEMENT_UNIT_COUNT_OFFSET),
        "shoreline_variant_visual_flag": i32(game_data, PORT_SHORE_VARIANT_FLAG_OFFSET),
    }


def summarize_fac(path: Optional[Path]) -> Optional[Dict[str, Any]]:
    if path is None:
        return None
    raw = path.read_bytes()
    lines = raw.splitlines()
    decoded_lines = [line.decode("cp1250", errors="replace") for line in lines[:12]]
    return {
        "path": str(path),
        "size": len(raw),
        "line_count": len(lines),
        "starts_with_initial_fact": raw.startswith(b"(initial-fact)"),
        "first_lines": decoded_lines,
    }


def inspect_dat(path: Path, fac_path: Optional[Path]) -> Dict[str, Any]:
    data = read_exact_dat(path)
    game_data = data[LABEL_SIZE:]
    return {
        "path": str(path),
        "size": len(data),
        "layout": {
            "label_size": LABEL_SIZE,
            "game_data_size": GAME_DATA_SIZE,
            "total_size": DAT_SIZE,
            "file_offset_formula": "0x10 + gameData offset",
        },
        "label": decode_label(data[:LABEL_SIZE]),
        "world": decode_world(game_data),
        "players": decode_players(game_data),
        "unit_stacks": decode_unit_stacks(game_data),
        "buildings": decode_buildings(game_data),
        "traps": decode_traps(game_data),
        "port": decode_port(game_data),
        "fac": summarize_fac(fac_path),
    }


def region_for_offset(file_offset: int) -> str:
    for name, start, size in REGIONS:
        if start <= file_offset < start + size:
            return name
    return "unmapped"


def diff_dat(left_path: Path, right_path: Path) -> Dict[str, Any]:
    left = read_exact_dat(left_path)
    right = read_exact_dat(right_path)
    region_counts: Counter[str] = Counter()
    region_samples: Dict[str, List[int]] = {}
    total = 0
    for offset, (left_byte, right_byte) in enumerate(zip(left, right)):
        if left_byte == right_byte:
            continue
        total += 1
        region = region_for_offset(offset)
        region_counts[region] += 1
        region_samples.setdefault(region, [])
        if len(region_samples[region]) < 12:
            region_samples[region].append(offset)
    return {
        "left": str(left_path),
        "right": str(right_path),
        "size": DAT_SIZE,
        "total_changed_bytes": total,
        "regions": [
            {
                "name": name,
                "changed_bytes": region_counts[name],
                "first_changed_file_offsets": [f"0x{offset:06X}" for offset in region_samples.get(name, [])],
            }
            for name in sorted(region_counts)
        ],
    }


def print_summary(result: Dict[str, Any]) -> None:
    label = result["label"]
    world = result["world"]
    players = result["players"]
    unit_stacks = result["unit_stacks"]
    buildings = result["buildings"]
    traps = result["traps"]
    port = result["port"]
    print(f"path: {result['path']}")
    print(f"size: {result['size']} bytes")
    print(f"label: {label['best_effort_text']!r} ({label['raw_hex']})")
    print(
        "world: "
        f"{world['map_width_tiles']}x{world['map_height_tiles']} "
        f"view=({world['map_view_left']},{world['map_view_top']}) "
        f"theme={world['map_theme_index']} mission={world['active_mission_index']} "
        f"turn={world['game_turn_counter']}"
    )
    print(
        "players: "
        f"active={players['active_count']} human={players['human_controller_count']} "
        f"turn_owner={world['turn_owner_player_index']} viewed={world['viewed_player_index']}"
    )
    print(
        "unit_stacks: "
        f"active={unit_stacks['active_count']} hidden={unit_stacks['hidden_count']} "
        f"queued_paths={unit_stacks['queued_path_count']} by_owner={unit_stacks['active_by_owner']}"
    )
    print(
        "buildings: "
        f"active={buildings['active_count']} completed={buildings['completed_count']} "
        f"by_owner={buildings['active_by_owner']}"
    )
    print(
        "traps: "
        f"nonzero_tiles={traps['nonzero_tile_count']} owner_bits={traps['owner_bit_counts']}"
    )
    print(
        "port: "
        f"row={port['port_tile_row']} column={port['port_tile_column']} "
        f"ready={port['reinforcement_ready_flag']} units={port['pending_reinforcement_unit_count']}"
    )
    fac = result.get("fac")
    if fac:
        print(
            "fac: "
            f"size={fac['size']} lines={fac['line_count']} "
            f"starts_with_initial_fact={fac['starts_with_initial_fact']}"
        )


def print_diff_summary(result: Dict[str, Any]) -> None:
    print(f"left: {result['left']}")
    print(f"right: {result['right']}")
    print(f"total_changed_bytes: {result['total_changed_bytes']}")
    for region in result["regions"]:
        samples = ", ".join(region["first_changed_file_offsets"])
        print(f"{region['name']}: {region['changed_bytes']} changed bytes ({samples})")


def parse_args(argv: Optional[Iterable[str]] = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Inspect recovered Clash save-slot DAT files")
    parser.add_argument("dat", nargs="?", type=Path, help="save/N.dat file to inspect")
    parser.add_argument("--fac", type=Path, help="optional save/N.fac sidecar to summarize")
    parser.add_argument("--json", action="store_true", help="emit JSON")
    parser.add_argument("--diff", nargs=2, metavar=("LEFT.dat", "RIGHT.dat"), type=Path, help="diff two DAT files by recovered region")
    return parser.parse_args(argv)


def main(argv: Optional[Iterable[str]] = None) -> int:
    args = parse_args(argv)
    try:
        if args.diff:
            result = diff_dat(args.diff[0], args.diff[1])
            if args.json:
                json.dump(result, sys.stdout, indent=2)
                print()
            else:
                print_diff_summary(result)
            return 0
        if args.dat is None:
            raise ValueError("expected DAT path or --diff LEFT.dat RIGHT.dat")
        result = inspect_dat(args.dat, args.fac)
        if args.json:
            json.dump(result, sys.stdout, indent=2)
            print()
        else:
            print_summary(result)
        return 0
    except (OSError, ValueError, struct.error) as exc:
        print(f"dump_save_dat.py: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
