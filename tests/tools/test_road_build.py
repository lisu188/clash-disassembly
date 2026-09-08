#!/usr/bin/env python3
"""Original-measured Road_Build boundary traces using the actual native body.

The boundaries are scripted observations, not callee gameplay simulations.
Unknown original uninitialized approach mappings remain outside the fixture.
"""
from pathlib import Path
import hashlib
import json
import re
import shutil
import struct
import subprocess
import tempfile
import unittest

import test_builder_road as builder_road

SOURCE = builder_road.BUILDINGS
FUNCTION = "Road_Build"
CALLS = ("log", "north", "south", "west", "east", "aligned", "bare", "cost",
         "castle", "min_ap", "surface", "rebuild", "path", "free", "execute", "spend", "panel")
MUTABLE_FIELDS = ("arena", "selected", "turn0", "turn1") + tuple(
    f"{axis}{arena}_{slot}" for arena in range(2) for slot in range(4)
    for axis in ("row", "column")) + tuple(
    f"{position}_{field}{arena}" for arena in range(2) for position in ("origin", "target")
    for field in ("terrain", "overlay", "road", "tick"))
STATE_FIELDS = MUTABLE_FIELDS + tuple(f"path_hash{arena}_{slot}" for arena in range(2) for slot in range(4))
INPUT_FIELDS = ("unit", "direction", "a3", "a4", "a5_low", "a5_high", "origin_row",
                "origin_column", "target_row", "target_column", "path_seed", "event_count")
EVENT_WORDS = 1 + 6 + len(STATE_FIELDS)
FINAL_WORDS = 1 + len(STATE_FIELDS) + 3
ARENA_BYTES = 150200
MAX_EVENTS = 40


def event(call, result=0, **mutations):
    return dict(call=call, result=result & 0xFFFFFFFF,
                mutations={key: value & 0xFFFFFFFF for key, value in mutations.items()})


def default_state():
    state = dict.fromkeys(MUTABLE_FIELDS, 0)
    state.update(selected=0x12345678, turn0=0x8001, turn1=0xFFFE)
    for arena in range(2):
        for slot in range(4):
            state[f"row{arena}_{slot}"] = 30
            state[f"column{arena}_{slot}"] = 40
        for position in ("origin", "target"):
            state[f"{position}_terrain{arena}"] = 1
            state[f"{position}_overlay{arena}"] = 0xFFFF
            state[f"{position}_road{arena}"] = 0xFFFF
            state[f"{position}_tick{arena}"] = 0x12345678 + arena
    return state


def cases():
    records = []
    finite_bits = (0, 0x8000000000000000, 0x3FF8000000000000, 0xC002000000000000,
                   1, 0x0010000000000000, 0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF)
    mapping = {544: 928, 546: 925, 547: 927, 549: 930, 564: 880, 566: 877,
               567: 879, 569: 882, 576: 904, 578: 901, 579: 903, 581: 906}

    def add(name, direction, events, initial=None, pattern=0, unit=None):
        state = default_state()
        state.update(initial or {})
        dx, dy = {0: (0, -1), 2: (1, 0), 4: (0, 1), 6: (-1, 0)}.get(direction, (1, 0))
        bits = finite_bits[pattern]
        header = [pattern % 4 if unit is None else unit, direction, (0, 1, 127, 128, 255, 85, 170, 254)[pattern],
                  (0, 0xFFFFFFFF, 0x80000000, 0x12345678, 0x55555555, 0xAAAAAAAA, 0x01020304, 0x7FFFFFFF)[pattern],
                  bits & 0xFFFFFFFF, bits >> 32, 30, 40, 30 + dx, 40 + dy, 17 + pattern, len(events)]
        records.append(dict(name=name, header=[word & 0xFFFFFFFF for word in header],
                            initial={key: value & 0xFFFFFFFF for key, value in state.items()}, events=events))

    def queries(mask=0, truth=1):
        return [event(call, truth if mask & (1 << index) else 0)
                for index, call in enumerate(("north", "south", "west", "east"))]

    def body(mask=0, truth=1, aligned=0, bare=0, cost=2, castle=0, ap=3,
             origin_surface=0, target_surface=0, path=1, rebuild=0xFFFF):
        events = [event("log"), *queries(mask, truth), event("aligned", aligned),
                  event("bare", bare), event("cost", cost), event("castle", castle)]
        if castle or cost == 0:
            return events
        events.append(event("min_ap", ap))
        signed = lambda value: (value & 0x7FFFFFFF) - (value & 0x80000000)
        if signed(ap) < signed((cost + 1) & 0xFFFFFFFF):
            return events
        events.append(event("surface", origin_surface))
        if origin_surface == 185:
            return events
        events.append(event("surface", target_surface))
        if target_surface == 185:
            return events
        events.append(event("rebuild", 0xABCD1234, target_road0=rebuild))
        if not aligned and not bare:
            events += queries(mask ^ 15, truth)
        events.append(event("path", path))
        if path:
            events += [event("free"), event("execute"), event("spend", 0x87654321), event("panel", 0xDEADBEEF)]
        return events

    for direction in (0, 2, 4, 6):
        for mask in range(16):
            for truth in (1, 0x80000000):
                for path in (0, 1):
                    add(f"direction-{direction}-mask-{mask:02x}-truth-{truth:08x}-path-{path}", direction,
                        body(mask=mask, truth=truth, path=path), pattern=(mask + path) % 8)
    for direction in (1, 3, 5, 7, 8, 0xFFFFFFFF, 0x80000000, 0x7FFFFFFF):
        add(f"invalid-direction-{direction:08x}", direction, [event("log"), *queries(15, 0xFFFFFFFF)])
    for overlay in mapping:
        for saved in (0, 0xFFFF, 867):
            for cost in (0, 2):
                add(f"approach-{overlay}-saved-{saved}-cost-{cost}", 6,
                    body(aligned=1, cost=cost),
                    {"target_overlay0": overlay, "target_terrain0": 605, "target_road0": saved})
    for direction in (0, 2, 4, 6):
        for saved in (0, 0xFFFF, 903):
            for gate, changes in (("success", {}), ("zero-cost", {"cost": 0}),
                                  ("castle", {"castle": 0x80000000}), ("ap-low", {"ap": 2}),
                                  ("origin185", {"origin_surface": 185}), ("target185", {"target_surface": 185}),
                                  ("null-path", {"path": 0})):
                add(f"bare-direction-{direction}-saved-{saved}-{gate}", direction,
                    body(bare=0xFFFFFFFF, **changes), {"target_road0": saved, "origin_road0": 904},
                    pattern=(direction + saved) % 8)
        add(f"sequential-approach-and-bare-{direction}", direction,
            body(aligned=1, bare=1), {"target_overlay0": 567, "target_terrain0": 605, "target_road0": 0})
    for terrain in (602, 603, 610, 611, 642, 643, 0xFFFF):
        for road in (0, 0xFFFF, 0x8000, 904):
            add(f"origin-preservation-terrain-{terrain}-road-{road}", 0,
                body(mask=3), {"origin_terrain0": terrain, "origin_road0": road})
    for prior in (0, 0xFFFF, 0x8000, 904):
        for rebuilt in (0, 0xFFFF, 866, 0x8000):
            add(f"target-restoration-prior-{prior}-rebuilt-{rebuilt}", 2,
                body(rebuild=rebuilt), {"target_road0": prior})
    for cost, ap in ((-2, -2), (-2, -1), (-1, 0), (1, 1), (1, 2),
                     (0x7FFFFFFE, 0x7FFFFFFE), (0x7FFFFFFE, 0x7FFFFFFF),
                     (0x7FFFFFFF, 0x7FFFFFFF), (0x7FFFFFFF, 0x80000000),
                     (0x80000000, 0x80000000), (0x80000000, 0x80000001)):
        add(f"cost-ap-boundary-{cost & 0xFFFFFFFF:08x}-{ap & 0xFFFFFFFF:08x}", 4,
            body(cost=cost, ap=ap))
    # All mutations occur at explicit instrumented call boundaries. The real
    # callee contract is not claimed by using a scripted return or mutation.
    chain = body(aligned=1)
    edits = {
        "log": dict(arena=1, row1_1=30, column1_1=40, selected=0xFFFFFFFF),
        "north": dict(arena=0, row0_1=-32768, column0_1=32767),
        "south": dict(arena=1, row1_1=32767, column1_1=-32768),
        "west": dict(arena=0, turn0=0xFFFF), "east": dict(arena=1, turn1=0x1234),
        "aligned": dict(arena=0, target_overlay0=567, target_road0=0xFFFF),
        "bare": dict(arena=1), "cost": dict(arena=0), "castle": dict(arena=1),
        "min_ap": dict(arena=0), "rebuild": dict(arena=1, target_road1=0xFFFF),
        "path": dict(arena=0, row0_1=13, column0_1=-129, selected=3),
        "free": dict(arena=1), "execute": dict(arena=0, selected=2),
        "spend": dict(arena=1, selected=0), "panel": dict(arena=0, selected=0x80000000),
    }
    surface_count = 0
    for item in chain:
        if item["call"] == "surface":
            item["mutations"]["arena"] = surface_count % 2
            surface_count += 1
        elif item["call"] in edits:
            item["mutations"] = {key: value & 0xFFFFFFFF for key, value in edits[item["call"]].items()}
    add("live-arena-unit-and-turn-at-every-boundary", 6, chain,
        {"row0_1": 5, "column0_1": 7, "target_overlay0": 567, "target_overlay1": 567}, pattern=7, unit=1)
    for pattern, column in enumerate((0, 127, 128, 255, -1, -129, -32768, 32767)):
        events = body(bare=1)
        next(item for item in events if item["call"] == "east")["mutations"] = {
            f"row0_{pattern % 4}": (32767 if pattern % 2 else -32768) & 0xFFFFFFFF,
            f"column0_{pattern % 4}": column & 0xFFFFFFFF}
        next(item for item in events if item["call"] == "path")["mutations"] = {
            f"column0_{pattern % 4}": (column ^ 0xFF) & 0xFFFFFFFF}
        add(f"finite-forwarding-current-column-{column}", 2, events, pattern=pattern)
    for turn in (0, 1, 0xFFFF, 0x10000, 0xFFFFFFFF):
        add(f"turn-word-zero-extension-{turn:08x}", 6, body(aligned=1, cost=0),
            {"turn0": turn, "target_overlay0": 567, "target_tick0": 0xFFFFFFFF, "target_road0": 0})
    events = body(mask=5)
    seen = dict.fromkeys(("north", "south", "west", "east"), 0)
    for item in events:
        if item["call"] in seen:
            seen[item["call"]] += 1
            if seen[item["call"]] == 2:
                arena = int(item["call"] in ("north", "west", "east"))
                item["mutations"] = {"arena": arena, "selected": 99,
                                      f"row{arena}_2": 17, f"column{arena}_2": (-129) & 0xFFFFFFFF}
    add("live-state-after-each-unused-target-connection", 4, events, unit=2)
    assert len({case["name"] for case in records}) == len(records)
    assert all(len(case["events"]) <= MAX_EVENTS for case in records)
    return records


def encode_cases(records):
    words = [len(records)]
    for case in records:
        words += case["header"]
        words += [case["initial"][field] for field in MUTABLE_FIELDS]
        for item in case["events"]:
            words += [CALLS.index(item["call"]) + 1, item["result"], len(item["mutations"])]
            for field, value in item["mutations"].items():
                words += [MUTABLE_FIELDS.index(field), value]
    return struct.pack(f"<{len(words)}I", *words)


def split_output(data, records):
    position = 0
    for case in records:
        size = 4 * (len(case["events"]) * EVENT_WORDS + FINAL_WORDS)
        if position + size > len(data):
            raise AssertionError("incomplete trace for " + case["name"])
        yield data[position:position + size]
        position += size
    if position != len(data):
        raise AssertionError("trailing trace bytes")


def harness_source(body=None):
    if body is None:
        body = builder_road.extract(SOURCE, FUNCTION)
    return (HARNESS.replace("@STATE_ENUM@", ", ".join("S_" + field.upper() for field in STATE_FIELDS))
            .replace("@INPUT_ENUM@", ", ".join("IN_" + field.upper() for field in INPUT_FIELDS))
            .replace("@CALL_ENUM@", ", ".join("C_" + call.upper() for call in CALLS))
            .replace("@BODY@", body))


def compile_command(compiler, optimization, source, executable):
    # The original leaves the approach local uninitialized outside its twelve
    # recovered mappings. Preserve that unresolved domain; never invent a zero
    # fallback just to silence a diagnostic. Only this diagnostic is allowed.
    warning_exception = "-Wno-error=uninitialized" if "clang" in str(compiler) else "-Wno-error=maybe-uninitialized"
    return [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
            "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
            "-Wall", "-Wextra", "-Werror", warning_exception, "-fsanitize=undefined",
            "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
            "-isystem", str(builder_road.REPO / "src"), str(source), "-o", str(executable)]


def check_compile_diagnostics(stderr):
    warnings = [line for line in stderr.splitlines() if "warning:" in line]
    for warning in warnings:
        if "bridgeApproachOverlayId" not in warning or not re.search(r"uninitialized", warning):
            raise AssertionError("unexpected warning: " + warning)


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

enum StateField { @STATE_ENUM@, STATE_WORDS };
enum InputField { @INPUT_ENUM@, INPUT_WORDS };
enum Call { C_UNUSED, @CALL_ENUM@ };
static_assert(STATE_WORDS == 44 && INPUT_WORDS == 12);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(sizeof(MapTileRecord) == 14 && std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex;
char aRoad_buildDD[18] = "Road_Build(%d,%d)";
alignas(16) static unsigned char arenas[2][150200];
alignas(16) static unsigned char expected_copy_arenas[2][150200];
alignas(4) static unsigned char path_data[404];
static uint32_t input[INPUT_WORDS];
static unsigned int case_index, event_index, log_checks, copy_checks;
static bool returned_path;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> mutations; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u event=%u: %s\n", case_index, event_index, message);
  std::exit(1);
}
static uint32_t word(const void *address) {
  uint32_t value;
  std::memcpy(&value, address, 4);
  return value;
}
static void put_word(void *address, uint32_t value) { std::memcpy(address, &value, 4); }
static uint32_t hash_bytes(const void *address, size_t bytes) {
  const unsigned char *data = (const unsigned char *)address;
  uint32_t value = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) value = (value ^ data[index]) * 16777619u;
  return value;
}
static unsigned char *tile_address(uint32_t index) {
  const uint32_t arena = index / 8;
  const bool target = (index % 8) >= 4;
  return arenas[arena] + TILE_TERRAIN_ROW_STRIDE * input[target ? IN_TARGET_ROW : IN_ORIGIN_ROW]
      + TILE_TERRAIN_RECORD_STRIDE * input[target ? IN_TARGET_COLUMN : IN_ORIGIN_COLUMN];
}
static uint32_t current_arena() {
  for (uint32_t index = 0; index < 2; ++index)
    if (gameData == (int)(uintptr_t)arenas[index]) return index;
  fail("unknown game-state pointer");
}
static uint32_t get_state(uint32_t field) {
  if (field >= S_PATH_HASH0_0 && field < STATE_WORDS) {
    const uint32_t index = field - S_PATH_HASH0_0;
    return hash_bytes(arenas[index / 4] + UNIT_STACK_TABLE_OFFSET + (index % 4) * UNIT_STACK_STRIDE
                      + UNIT_STACK_PATH_OFFSET, UNIT_STACK_PATH_BYTES);
  }
  if (field >= S_ORIGIN_TERRAIN0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_ORIGIN_TERRAIN0;
    const unsigned int offsets[] = {0, 2, 4, 10};
    const void *address = tile_address(index) + offsets[index % 4];
    if (index % 4 == 3) return word(address);
    uint16_t value;
    std::memcpy(&value, address, 2);
    return value;
  }
  if (field >= S_ROW0_0 && field < S_ORIGIN_TERRAIN0) {
    const uint32_t index = field - S_ROW0_0;
    int16_t value;
    std::memcpy(&value, arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, 2);
    return (uint32_t)(int32_t)value;
  }
  if (field == S_ARENA) return current_arena();
  if (field == S_SELECTED) return g_SelectedUnitIndex;
  if (field == S_TURN0 || field == S_TURN1) {
    uint16_t value;
    std::memcpy(&value, arenas[field - S_TURN0] + GAME_TURN_COUNTER_OFFSET, 2);
    return value;
  }
  fail("invalid state field");
}
static void set_state(uint32_t field, uint32_t value) {
  if (field >= S_ORIGIN_TERRAIN0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_ORIGIN_TERRAIN0;
    const unsigned int offsets[] = {0, 2, 4, 10};
    void *address = tile_address(index) + offsets[index % 4];
    if (index % 4 == 3) put_word(address, value);
    else {
      const uint16_t narrowed = (uint16_t)value;
      std::memcpy(address, &narrowed, 2);
    }
    return;
  }
  if (field >= S_ROW0_0 && field < S_ORIGIN_TERRAIN0) {
    const uint32_t index = field - S_ROW0_0;
    const uint16_t coordinate = (uint16_t)value;
    std::memcpy(arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, &coordinate, 2);
    return;
  }
  if (field == S_ARENA) {
    if (value > 1) fail("invalid arena index");
    gameData = (int)(uintptr_t)arenas[value]; return;
  }
  if (field == S_SELECTED) { g_SelectedUnitIndex = (int32_t)value; return; }
  if (field == S_TURN0 || field == S_TURN1) {
    const uint16_t narrowed = (uint16_t)value;
    std::memcpy(arenas[field - S_TURN0] + GAME_TURN_COUNTER_OFFSET, &narrowed, 2);
    return;
  }
  fail("invalid mutation field");
}
static void snapshot() {
  for (uint32_t field = 0; field < STATE_WORDS; ++field) output.push_back(get_state(field));
}
static uint32_t boundary(uint32_t call, uint32_t a0=0, uint32_t a1=0,
                         uint32_t a2=0, uint32_t a3=0, uint32_t a4=0, uint32_t a5=0) {
  if (event_index >= script.size() || script[event_index].call != call) {
    std::fprintf(stderr, "actual call=%u expected=%u\n", call,
                 event_index < script.size() ? script[event_index].call : 0);
    fail("unexpected callee order");
  }
  output.insert(output.end(), {call, a0, a1, a2, a3, a4, a5});
  snapshot();
  const Event &item = script[event_index++];
  for (const Mutation &mutation : item.mutations) set_state(mutation.field, mutation.value);
  return item.result;
}
static uint32_t stack_identity(uintptr_t address) {
  for (uint32_t arena = 0; arena < 2; ++arena)
    for (uint32_t index = 0; index < 4; ++index)
      if (address == (uintptr_t)(arenas[arena] + UNIT_STACK_TABLE_OFFSET + index * UNIT_STACK_STRIDE))
        return arena * 4 + index;
  fail("argument is not an exact backed stack pointer");
}
static void Debug_Log(int unit, char opaque_byte, DWORD context, int format, ...) {
  if (++log_checks != 1 || (uint32_t)unit != input[IN_UNIT] || (uint8_t)opaque_byte != input[IN_A3]
      || context != input[IN_A4] || (uint32_t)format != (uintptr_t)aRoad_buildDD
      || std::memcmp(aRoad_buildDD, "Road_Build(%d,%d)", sizeof aRoad_buildDD))
    fail("native log forwarding differs");
  boundary(C_LOG);
}
static BOOL MapTile_HasNorthRoadConnection(int row, int column) { return (int32_t)boundary(C_NORTH, row, column); }
static BOOL MapTile_HasSouthRoadConnection(int row, int column) { return (int32_t)boundary(C_SOUTH, row, column); }
static BOOL MapTile_HasWestRoadConnection(int row, int column) { return (int32_t)boundary(C_WEST, row, column); }
static BOOL MapTile_HasEastRoadConnection(int row, int column) { return (int32_t)boundary(C_EAST, row, column); }
static signed int MapTile_HasAlignedBridgeApproachRoadOverlay(int ref_row, int ref_column, int column, int row) {
  return (int32_t)boundary(C_ALIGNED, ref_row, ref_column, column, row);
}
static BOOL MapTile_IsBareBridgeCrossingRoadOverlayCandidate(int row, int column) {
  return (int32_t)boundary(C_BARE, row, column);
}
static signed int UnitStack_GetTileMoveCostOrZero(__int16 *stack, int row, int carried, int column) {
  const uint32_t identity = stack_identity((uintptr_t)stack);
  return (int32_t)boundary(C_COST, identity / 4, identity % 4, row, carried, column);
}
static BOOL MapTile_IsCastleFoundationTile(int row, signed int column, int mode) {
  return (int32_t)boundary(C_CASTLE, row, column, mode);
}
static signed int UnitStack_GetMinCurrentActionPoints(intptr_t stack) {
  const uint32_t identity = stack_identity((uintptr_t)stack);
  return (int32_t)boundary(C_MIN_AP, identity / 4, identity % 4);
}
static signed int Map_GetTileSurfaceClassOrUnexplored(int row, signed int column) {
  return (int32_t)boundary(C_SURFACE, row, column);
}
static int Map_RebuildRoadOverlayAtTile(int row, int column) { return (int32_t)boundary(C_REBUILD, row, column); }
static int *Unit_MoveTrack(int unit, int source_row, int target_row, int source_column, DWORD carried, int target_column) {
  const uint32_t result = boundary(C_PATH, unit, source_row, target_row, source_column, carried, target_column);
  if (result > 1) fail("invalid scripted path identity");
  returned_path = result != 0;
  if (!returned_path) return nullptr;
  std::memcpy(expected_copy_arenas, arenas, sizeof arenas);
  std::memcpy(expected_copy_arenas[current_arena()] + UNIT_STACK_TABLE_OFFSET
              + UNIT_STACK_STRIDE * input[IN_UNIT] + UNIT_STACK_PATH_OFFSET, path_data, sizeof path_data);
  return (int *)path_data;
}
static int __fastcall j__nfree_(void) {
  if (!returned_path || ++copy_checks != 1 || std::memcmp(arenas, expected_copy_arenas, sizeof arenas))
    fail("caller did not copy exactly404 bytes to the fresh game-state destination before free boundary");
  return (int32_t)boundary(C_FREE);
}
static void UnitStack_ExecuteQueuedPath(unsigned int unit, int animate, char column, DWORD offset, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  boundary(C_EXECUTE, unit, animate, (uint8_t)column, offset, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static signed int UnitStack_SpendActionPointsClamped(__int16 *stack, int amount, DWORD offset, double value) {
  const uint32_t identity = stack_identity((uintptr_t)stack);
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_SPEND, identity / 4, identity % 4, amount, offset,
                          (uint32_t)bits, (uint32_t)(bits >> 32));
}
static void *WorldMap_RefreshUnitStatusPanel(DWORD offset) {
  return (void *)(uintptr_t)boundary(C_PANEL, offset);
}
@BODY@

static uint32_t read_input() {
  uint32_t result;
  if (std::fread(&result, 4, 1, stdin) != 1) fail("incomplete input fixture");
  return result;
}
int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX || (uintptr_t)path_data + sizeof path_data > INT_MAX)
    fail("fixture storage must fit positive signed low32");
  const unsigned int count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    for (uint32_t &word : input) word = read_input();
    if (input[IN_UNIT] > 3 || input[IN_EVENT_COUNT] > 40 || !input[IN_EVENT_COUNT]) fail("invalid header");
    for (unsigned int coordinate : {IN_ORIGIN_ROW, IN_ORIGIN_COLUMN, IN_TARGET_ROW, IN_TARGET_COLUMN})
      if (input[coordinate] > 90) fail("tile probe outside fixture backing");
    std::memset(arenas, 0x5A, sizeof arenas);
    for (size_t index = 0; index < sizeof path_data; ++index)
      path_data[index] = (unsigned char)(input[IN_PATH_SEED] + index * 37);
    for (uint32_t field = 0; field < S_PATH_HASH0_0; ++field) set_state(field, read_input());
    script.clear(); output.clear();
    event_index = log_checks = copy_checks = 0;
    returned_path = false;
    for (uint32_t index = 0; index < input[IN_EVENT_COUNT]; ++index) {
      Event item;
      item.call = read_input(); item.result = read_input();
      const uint32_t mutations = read_input();
      if (mutations > S_PATH_HASH0_0) fail("invalid mutation count");
      for (uint32_t mutation = 0; mutation < mutations; ++mutation) {
        const uint32_t field = read_input(), value = read_input();
        item.mutations.push_back({field, value});
      }
      script.push_back(item);
    }
    const uint64_t bits = (uint64_t)input[IN_A5_LOW] | ((uint64_t)input[IN_A5_HIGH] << 32);
    const int result = Road_Build((int32_t)input[IN_UNIT], (int32_t)input[IN_DIRECTION],
                                  (char)(uint8_t)input[IN_A3], input[IN_A4], std::bit_cast<double>(bits));
    if (event_index != script.size() || log_checks != 1 || copy_checks != (unsigned)returned_path)
      fail("missing boundary or copy check");
    output.push_back((uint32_t)result);
    snapshot();
    output.push_back(hash_bytes(arenas[0], sizeof arenas[0]));
    output.push_back(hash_bytes(arenas[1], sizeof arenas[1]));
    output.push_back(hash_bytes(path_data, sizeof path_data));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input bytes");
}
'''


class RoadBuildTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "road-build-provenance.json").read_text())
        self.assertEqual(provenance["input_fields"], list(INPUT_FIELDS))
        self.assertEqual(provenance["state_fields"], list(STATE_FIELDS))
        self.assertEqual(provenance["calls"], list(CALLS))
        self.assertEqual(provenance["event_words"], EVENT_WORDS)
        self.assertEqual(provenance["final_words"], FINAL_WORDS)
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-road-build-") as temporary:
            directory = Path(temporary)
            source = directory / "road_build.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("road-build-" + optimization[1:])
                    command = compile_command(compiler, optimization, source, executable)
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    check_compile_diagnostics(built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    for case, observed, expected in zip(records, split_output(run.stdout, records),
                                                       provenance["case_trace_sha256"], strict=True):
                        self.assertEqual(hashlib.sha256(observed).hexdigest(), expected,
                                         case["name"] + ": original call/state/memory trace differs")
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_road_build_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_road_build_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
