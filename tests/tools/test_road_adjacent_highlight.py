#!/usr/bin/env python3
"""Original-measured contract traces of the actual adjacent Road highlight body.

The actual initializer and shared packed tables execute. Eligibility and widget
refresh are explicit recording/mutating boundaries, not gameplay simulations.
Inputs exclude canonical signed overflow and unbacked memory accesses.
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


INPUT_FIELDS = (
    "tile_row", "tile_column", "selected_row", "selected_column", "view_left", "view_top",
    "frame", "bounce_seed", "marker_seed_x", "marker_seed_y", "initial_target",
    "mutate_between_calls", "aligned_return", "bare_return", "bridge_ap", "move_cost",
    "castle_return", "ordinary_ap", "surface_return", "refresh_return", "initializer_guard",
    "refresh_mutates_target", "refresh_target_after", "initial_selected", "initial_map",
    "refresh_return_kind", "nonadjacent_guard",
)
HEADER_FIELDS = (
    "return_kind", "return_value", "final_selected", "final_map", "final_target", "final_frame",
    "initializer_check", "map_memory_unchanged", "address_spies_unused", "boundary_count",
)
BOUNDARY_FIELDS = (
    "callee_id", "ordinal", "arg0", "arg1", "arg2", "arg3", "selected", "map", "target", "frame",
    "NX", "NY", "EX", "EY", "SX", "SY", "WX", "WY", "approach43", "approach44",
)
OUTPUT_WORDS = 427


def cases():
    records = []
    deltas = ((0, -1), (1, 0), (0, 1), (-1, 0))

    def add(name, direction=None, **changes):
        index = len(records)
        values = dict(zip(INPUT_FIELDS, (
            30, 40, 30, 40, 28, 38, 0, 3, 101, 103, (0, 1, -7)[index % 3],
            0, 0, 0, 6, 2, 0, 3, 0, (0, -31, -2147483648, 2147483647, 123)[index % 5],
            (1, -7)[index % 2], 0, -55, index % 4, (index // 4) % 2, 0, 0,
        ), strict=True))
        values.update(changes)
        if direction is not None:
            delta_row, delta_column = deltas[direction]
            values["tile_row"] = values["selected_row"] + delta_row
            values["tile_column"] = values["selected_column"] + delta_column
        records.append(dict(name=name, words=[values[field] & 0xFFFFFFFF for field in INPUT_FIELDS]))

    paths = (
        ("aligned-bridge", dict(aligned_return=7, bare_return=-13)),
        ("negative-aligned", dict(aligned_return=-3, bridge_ap=7)),
        ("bare-bridge", dict(bare_return=2)),
        ("bridge-ap5-cost0", dict(aligned_return=1, bridge_ap=5, move_cost=0)),
        ("bare-ap5-castle", dict(bare_return=1, bridge_ap=5, castle_return=-17)),
        ("ordinary-cost0", dict(move_cost=0)),
        ("ordinary-castle", dict(castle_return=19)),
        ("ordinary-ap-below", dict(ordinary_ap=2)),
        ("surface185", dict(surface_return=185)),
        ("ordinary-ap-exact", {}),
        ("ordinary-ap-above", dict(ordinary_ap=4, surface_return=184)),
        ("negative-cost", dict(move_cost=-2, ordinary_ap=-1, surface_return=-1)),
        ("minimum-ap", dict(move_cost=1, ordinary_ap=-2147483648)),
        ("maximum-ap", dict(move_cost=2147483646, ordinary_ap=2147483647, surface_return=186)),
        ("bridge-minimum-ap-fallback", dict(aligned_return=1, bridge_ap=-2147483648)),
    )
    for direction in range(4):
        for name, changes in paths:
            for mutate in (0, 1):
                add(f"direction{direction}-{name}-mutate{mutate}", direction,
                    mutate_between_calls=mutate, **changes)
        for frame in (*range(11), 23, 36, 49):
            add(f"direction{direction}-live-bounce{frame}", direction,
                frame=frame, aligned_return=1, mutate_between_calls=1)
        for viewport in (0, 0xFFFFFFFF, 0x7FFFFFFF, 0x40000000, 0x80000000, 41):
            add(f"direction{direction}-viewport{viewport:x}", direction,
                view_left=viewport, view_top=viewport)
        for row, column in ((-32768, -32768), (32767, 32767), (-32768, 32767), (0, -1)):
            delta_row, delta_column = deltas[direction]
            add(f"direction{direction}-signed-{row}-{column}", direction,
                selected_row=row, selected_column=column,
                view_left=row + delta_row, view_top=column + delta_column)
        for mutate in (0, 1):
            add(f"direction{direction}-cold-mutate{mutate}", direction,
                initializer_guard=0, mutate_between_calls=mutate)
            add(f"direction{direction}-refresh-pointer-mutate{mutate}", direction,
                refresh_return_kind=1, refresh_mutates_target=1, mutate_between_calls=mutate)
        add(f"direction{direction}-negative-bare", direction, bare_return=-2)
        for bounce in (0, -4, 17):
            add(f"direction{direction}-bounce-value{bounce}", direction, bounce_seed=bounce)

    for column in (-32768, -1, 0, 32767):
        for guarded in (0, 1):
            for row_delta, column_delta, category in ((2, 0, "base"), (-1, 1, "column")):
                add(f"nonadjacent-{category}-column{column}-guard{guarded}",
                    selected_column=column, tile_row=30 + row_delta, tile_column=column + column_delta,
                    nonadjacent_guard=guarded, frame=2147483647)
    for row, column in ((30, 40), (30, 42), (31, 41), (29, 39)):
        for cold in (0, 1):
            add(f"nonadjacent-{row}-{column}-cold{cold}", tile_row=row, tile_column=column,
                initializer_guard=0 if cold else -7, nonadjacent_guard=1, frame=-2147483648)
    for value in (0x700000, 0x800000, 0x5142B8):
        add(f"raw-pointer-overlap-castle-{value:x}", 0, castle_return=value)
        add(f"raw-pointer-overlap-ap-{value:x}", 0, move_cost=value + 1, ordinary_ap=value)
        add(f"raw-pointer-overlap-refresh-{value:x}", 0, refresh_return=value)
    for direction in range(4):
        for mutate in (0, 1):
            add(f"direction{direction}-bare-ap5-full-fallback-mutate{mutate}", direction,
                bare_return=1, bridge_ap=5, mutate_between_calls=mutate)
    for mutate in (0, 1):
        add(f"direction2-south-X-bounce36-sensitive-mutate{mutate}", 2,
            frame=36, marker_seed_x=0x12340056, initial_target=1,
            mutate_between_calls=mutate, aligned_return=1, refresh_return=-31,
            initializer_guard=1, initial_selected=2, initial_map=1)
    assert len({record["name"] for record in records}) == len(records)
    return records


def encode_cases(records):
    return struct.pack("<I", len(records)) + b"".join(
        struct.pack("<27I", *record["words"]) for record in records)


def harness_source(body=None):
    _, road, builder, relocations = builder_road.fixtures()
    target = "RoadBuildMode_HighlightBuildableAdjacentTile"
    symbols = {entry["canonical_symbol"] for entry in relocations if entry.get("canonical_symbol")}
    symbols.difference_update((target, "g_ActionButtonSpriteSet"))
    spies = "\n".join("static int " + name + "() { ++address_spy_calls; return 0; }"
                      for name in sorted(symbols))
    masks = {"road": bytearray(len(road)), "builder": bytearray(len(builder))}
    checks, fields = [], []
    for index, entry in enumerate(relocations):
        table = "builder" if entry["table"] == "builder-widgets" else "road"
        original = builder if table == "builder" else road
        actual = "g_UI_YesNoDims" if table == "builder" else "g_RoadBuildData"
        offset = entry["region_offset"]
        value = int(entry["original_pointer"], 16)
        assert struct.unpack_from("<I", original, offset)[0] == value
        assert not any(masks[table][offset:offset + 4])
        masks[table][offset:offset + 4] = b"\1" * 4
        fields.append(f"{{{int(table == 'builder')}, {offset}, {value}U}}")
        field = f"{actual} + {offset}"
        if entry.get("canonical_symbol"):
            checks.append(f"check_pointer({field}, (uintptr_t)&{entry['canonical_symbol']});")
        elif "raw_hex" in entry:
            checks.append(builder_road.byte_array(f"text_{index}", bytes.fromhex(entry["raw_hex"]) + b"\0"))
            checks.append(f"check_text({field}, text_{index}, sizeof text_{index});")
        else:
            assert value == 0
            checks.append(f"check_pointer({field}, 0);")
    data = "".join(builder_road.byte_array(name, values) for name, values in (
        ("original_road", road), ("original_builder", builder),
        ("road_pointer_mask", masks["road"]), ("builder_pointer_mask", masks["builder"]),
    ))
    if body is None:
        body = builder_road.extract(builder_road.BUILDINGS, target)
    bodies = builder_road.extract(builder_road.WORLD2, "WorldMap_EnsureBuilderWidgetTables") + "\n" + body
    return (HARNESS.replace("@INPUT_ENUM@", ", ".join("IN_" + name.upper() for name in INPUT_FIELDS))
            .replace("@SPIES@", spies).replace("@BODIES@", bodies).replace("@DATA@", data)
            .replace("@POINTER_CHECKS@", "\n".join(checks))
            .replace("@POINTER_FIELDS@", ",\n".join(fields)))


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>

enum InputField { @INPUT_ENUM@, INPUT_WORDS };
static_assert(INPUT_WORDS == 27 && std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex, g_ActionButtonSpriteSet;
int g_BuilderRoadWidgetsInitialized, g_RoadBuildModeAnimationFrameIndex, g_RoadBuildModeHasBuildTarget;
alignas(4) _BYTE g_RoadBuildData[ROAD_BUILD_DATA_BYTES];
alignas(4) _BYTE g_UI_YesNoDims[BUILDER_ACTION_WIDGET_TABLE_BYTES];
alignas(4096) static unsigned char maps[2][163840];
static unsigned char expected_maps[sizeof maps];
static unsigned char initialized_road[sizeof g_RoadBuildData], initialized_builder[sizeof g_UI_YesNoDims];
static uint32_t input[INPUT_WORDS], output[427];
static unsigned int case_index, boundary_count, address_spy_calls;
static constexpr size_t marker_offsets[] = {172, 176, 225, 229, 278, 282, 331, 335};

int RoadBuildMode_HighlightBuildableAdjacentTile(int, int);
signed int MapTile_HasAlignedBridgeApproachRoadOverlay(int, int, int, int);
BOOL MapTile_IsBareBridgeCrossingRoadOverlayCandidate(int, int);
signed int UnitStack_GetMinCurrentActionPoints(intptr_t);
signed int UnitStack_GetTileMoveCostOrZero(__int16 *, int, int, int);
BOOL MapTile_IsCastleFoundationTile(int, signed int, int);
signed int Map_GetTileSurfaceClassOrUnexplored(int, signed int);
int UIWidget_RefreshActionButtonState(uintptr_t, int);
@SPIES@
@BODIES@
@DATA@

struct PointerField { unsigned int table, offset; uint32_t original; };
static constexpr PointerField pointer_fields[] = { @POINTER_FIELDS@ };

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u boundary=%u: %s\n", case_index, boundary_count, message);
  std::exit(1);
}

static uint32_t word(const void *address) {
  uint32_t value;
  std::memcpy(&value, address, sizeof value);
  return value;
}

static void write_word(void *address, uint32_t value) {
  std::memcpy(address, &value, sizeof value);
}

static void check_pointer(const void *address, uintptr_t expected) {
  if (expected > INT_MAX || word(address) != expected) fail("initializer pointer differs");
}

static void check_text(const void *address, const unsigned char *expected, size_t length) {
  const uintptr_t pointer = word(address);
  if (!pointer || pointer > INT_MAX || std::memcmp((const void *)pointer, expected, length))
    fail("initializer text differs");
}

static int map_id(uintptr_t address) {
  for (int index = 0; index < 2; ++index)
    if (address == (uintptr_t)maps[index]) return index;
  fail("unregistered gameData base");
}

static uint32_t map_argument(uintptr_t address) {
  for (unsigned int index = 0; index < 2; ++index) {
    const uintptr_t base = (uintptr_t)maps[index];
    if (address >= base && address < base + sizeof maps[index])
      return 0x10000000U + index * 0x100000U + (uint32_t)(address - base);
  }
  fail("unregistered map pointer argument");
}

static uint32_t road_argument(uintptr_t address) {
  const uintptr_t base = (uintptr_t)g_RoadBuildData;
  if (address < base || address >= base + sizeof g_RoadBuildData)
    fail("unregistered Road pointer argument");
  return 0x30000000U + (uint32_t)(address - base);
}

static void record(unsigned int callee, uint32_t a0 = 0, uint32_t a1 = 0,
                   uint32_t a2 = 0, uint32_t a3 = 0) {
  if (boundary_count >= 8) fail("too many boundary calls");
  uint32_t *entry = output + 10 + 20 * boundary_count;
  entry[0] = callee;
  entry[1] = ++boundary_count;
  entry[2] = a0; entry[3] = a1; entry[4] = a2; entry[5] = a3;
  entry[6] = (uint32_t)g_SelectedUnitIndex;
  entry[7] = (uint32_t)map_id((uintptr_t)gameData);
  entry[8] = (uint32_t)g_RoadBuildModeHasBuildTarget;
  entry[9] = (uint32_t)g_RoadBuildModeAnimationFrameIndex;
  for (size_t index = 0; index < 8; ++index)
    entry[10 + index] = word(g_RoadBuildData + marker_offsets[index]);
  entry[18] = word(g_RoadBuildData + 43 * 4);
  entry[19] = word(g_RoadBuildData + 44 * 4);
}

static void mutate() {
  if (input[IN_MUTATE_BETWEEN_CALLS]) {
    g_SelectedUnitIndex = (int)((boundary_count + 1) % 4);
    gameData = (int)(uintptr_t)maps[boundary_count % 2];
  }
}

signed int MapTile_HasAlignedBridgeApproachRoadOverlay(int row, int column, int candidate_column, int candidate_row) {
  record(1, (uint32_t)row, (uint32_t)column, (uint32_t)candidate_column, (uint32_t)candidate_row);
  mutate();
  return (int32_t)input[IN_ALIGNED_RETURN];
}

BOOL MapTile_IsBareBridgeCrossingRoadOverlayCandidate(int row, int column) {
  record(2, (uint32_t)row, (uint32_t)column);
  mutate();
  return (int32_t)input[IN_BARE_RETURN];
}

signed int UnitStack_GetMinCurrentActionPoints(intptr_t stack) {
  const bool ordinary = boundary_count && output[10 + 20 * (boundary_count - 1)] == 5;
  record(ordinary ? 6 : 3, map_argument((uintptr_t)stack));
  mutate();
  return (int32_t)input[ordinary ? IN_ORDINARY_AP : IN_BRIDGE_AP];
}

signed int UnitStack_GetTileMoveCostOrZero(__int16 *stack, int row, int data, int column) {
  record(4, map_argument((uintptr_t)stack), (uint32_t)row,
         map_argument((uintptr_t)data), (uint32_t)column);
  mutate();
  return (int32_t)input[IN_MOVE_COST];
}

BOOL MapTile_IsCastleFoundationTile(int row, signed int column, int mode) {
  record(5, (uint32_t)row, (uint32_t)column, (uint32_t)mode);
  mutate();
  return (int32_t)input[IN_CASTLE_RETURN];
}

signed int Map_GetTileSurfaceClassOrUnexplored(int row, signed int column) {
  record(7, (uint32_t)row, (uint32_t)column);
  mutate();
  return (int32_t)input[IN_SURFACE_RETURN];
}

int UIWidget_RefreshActionButtonState(uintptr_t widget, int argument) {
  record(8, road_argument(widget), (uint32_t)argument);
  mutate();
  if (input[IN_REFRESH_MUTATES_TARGET])
    g_RoadBuildModeHasBuildTarget = (int32_t)input[IN_REFRESH_TARGET_AFTER];
  return input[IN_REFRESH_RETURN_KIND] ? (int)widget : (int32_t)input[IN_REFRESH_RETURN];
}

static void capture_initializer_reference() {
  g_ActionButtonSpriteSet = 0x12345678;
  g_BuilderRoadWidgetsInitialized = 0;
  WorldMap_EnsureBuilderWidgetTables();
  for (size_t index = 0; index < sizeof g_RoadBuildData; ++index)
    if (!road_pointer_mask[index] && g_RoadBuildData[index] != original_road[index])
      fail("initial Road nonpointer bytes differ");
  for (size_t index = 0; index < sizeof g_UI_YesNoDims; ++index)
    if (!builder_pointer_mask[index] && g_UI_YesNoDims[index] != original_builder[index])
      fail("initial builder nonpointer bytes differ");
  @POINTER_CHECKS@
  if (g_BuilderRoadWidgetsInitialized != 1 || g_ActionButtonSpriteSet != 0x12345678 || address_spy_calls)
    fail("initializer state differs");
  std::memcpy(initialized_road, g_RoadBuildData, sizeof initialized_road);
  std::memcpy(initialized_builder, g_UI_YesNoDims, sizeof initialized_builder);
}

static void protect(void *address, size_t size, int protection) {
  if (mprotect(address, size, protection)) fail("mprotect failed");
}

static void put_coordinates(unsigned int map, unsigned int selected, int row, int column) {
  if (map > 1 || selected > 3 || row < INT16_MIN || row > INT16_MAX || column < INT16_MIN || column > INT16_MAX)
    fail("coordinates outside fixture domain");
  const int16_t coordinates[] = {(int16_t)row, (int16_t)column};
  std::memcpy(maps[map] + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * selected, coordinates, sizeof coordinates);
}

static void prepare() {
  std::memset(output, 0, sizeof output);
  boundary_count = address_spy_calls = 0;
  std::memset(maps, 0x5A, sizeof maps);
  for (unsigned int map = 0; map < 2; ++map) {
    for (unsigned int selected = 0; selected < 4; ++selected)
      put_coordinates(map, selected, 100 + 100 * (int)map + 11 * (int)selected,
                      200 + 100 * (int)map + 13 * (int)selected);
    write_word(maps[map] + MAP_VIEW_LEFT_OFFSET, input[IN_VIEW_LEFT]);
    write_word(maps[map] + MAP_VIEW_TOP_OFFSET, input[IN_VIEW_TOP]);
  }
  put_coordinates(input[IN_INITIAL_MAP], input[IN_INITIAL_SELECTED],
                  (int32_t)input[IN_SELECTED_ROW], (int32_t)input[IN_SELECTED_COLUMN]);
  std::memcpy(expected_maps, maps, sizeof maps);
  gameData = (int)(uintptr_t)maps[input[IN_INITIAL_MAP]];
  g_SelectedUnitIndex = (int)input[IN_INITIAL_SELECTED];
  g_RoadBuildModeAnimationFrameIndex = (int32_t)input[IN_FRAME];
  g_RoadBuildModeHasBuildTarget = (int32_t)input[IN_INITIAL_TARGET];
  g_BuilderRoadWidgetsInitialized = (int32_t)input[IN_INITIALIZER_GUARD];
  if (g_BuilderRoadWidgetsInitialized) {
    std::memcpy(g_RoadBuildData, initialized_road, sizeof g_RoadBuildData);
    std::memcpy(g_UI_YesNoDims, initialized_builder, sizeof g_UI_YesNoDims);
    for (size_t index = 0; index < 8; ++index)
      write_word(g_RoadBuildData + marker_offsets[index], input[index % 2 ? IN_MARKER_SEED_Y : IN_MARKER_SEED_X]);
    for (unsigned int index = 0; index < 9; ++index)
      write_word(g_RoadBuildData + ROAD_BUILD_BOUNCE_OFFSETS_OFFSET + 4 * index, input[IN_BOUNCE_SEED]);
  } else {
    std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
    std::memset(g_UI_YesNoDims, 0xA5, sizeof g_UI_YesNoDims);
  }
  protect(maps, sizeof maps, PROT_READ);
  if (input[IN_NONADJACENT_GUARD])
    for (auto &map : maps) protect(map + 34 * 4096, 4096, PROT_NONE);
}

static void finish(int result) {
  protect(maps, sizeof maps, PROT_READ | PROT_WRITE);
  output[1] = (uint32_t)result;
  if (!boundary_count) {
    for (unsigned int map = 0; map < 2; ++map) {
      const uintptr_t value = (uint32_t)result, base = (uintptr_t)maps[map];
      if (value >= base && value < base + sizeof maps[map]) {
        output[0] = 1 + map;
        output[1] = (uint32_t)(value - base);
      }
    }
  } else if (output[10 + 20 * (boundary_count - 1)] == 8 && input[IN_REFRESH_RETURN_KIND]) {
    output[0] = 3;
    output[1] = road_argument((uintptr_t)(uint32_t)result) - 0x30000000U;
  }
  output[2] = (uint32_t)g_SelectedUnitIndex;
  output[3] = (uint32_t)map_id((uintptr_t)gameData);
  output[4] = (uint32_t)g_RoadBuildModeHasBuildTarget;
  output[5] = (uint32_t)g_RoadBuildModeAnimationFrameIndex;
  const int expected_guard = input[IN_INITIALIZER_GUARD] ? (int32_t)input[IN_INITIALIZER_GUARD] : 1;
  bool initializer_ok = g_BuilderRoadWidgetsInitialized == expected_guard && g_ActionButtonSpriteSet == 0x12345678;
  unsigned char *normalized = (unsigned char *)(output + 170);
  std::memcpy(normalized, g_RoadBuildData, sizeof g_RoadBuildData);
  std::memcpy(normalized + sizeof g_RoadBuildData, g_UI_YesNoDims, sizeof g_UI_YesNoDims);
  for (const PointerField &field : pointer_fields) {
    const unsigned char *actual = field.table ? g_UI_YesNoDims : g_RoadBuildData;
    const unsigned char *reference = field.table ? initialized_builder : initialized_road;
    const uint32_t value = word(actual + field.offset);
    const bool unchanged = value == word(reference + field.offset);
    initializer_ok = initializer_ok && unchanged;
    if (unchanged)
      write_word(normalized + (field.table ? sizeof g_RoadBuildData : 0) + field.offset, field.original);
  }
  output[6] = initializer_ok;
  output[7] = std::memcmp(maps, expected_maps, sizeof maps) == 0;
  output[8] = address_spy_calls == 0;
  output[9] = boundary_count;
}

int main() {
  std::setvbuf(stdout, nullptr, _IONBF, 0);
  if ((uintptr_t)maps + sizeof maps > INT_MAX || (uintptr_t)g_RoadBuildData + sizeof g_RoadBuildData > INT_MAX)
    fail("fixture requires positive signed-low32 addresses");
  capture_initializer_reference();
  uint32_t count;
  if (std::fread(&count, sizeof count, 1, stdin) != 1) fail("missing input count");
  for (case_index = 0; case_index < count; ++case_index) {
    if (std::fread(input, sizeof input, 1, stdin) != 1) fail("missing input record");
    prepare();
    const int result = RoadBuildMode_HighlightBuildableAdjacentTile((int32_t)input[IN_TILE_ROW], (int32_t)input[IN_TILE_COLUMN]);
    finish(result);
    if (std::fwrite(output, sizeof output, 1, stdout) != 1) fail("cannot write output");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing fixture input");
}
'''


class RoadAdjacentHighlightTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "adjacent-highlight-provenance.json").read_text())
        self.assertEqual(list(INPUT_FIELDS), provenance["input_fields"])
        self.assertEqual(list(HEADER_FIELDS), provenance["header_fields"])
        self.assertEqual(list(BOUNDARY_FIELDS), provenance["boundary_fields"])
        self.assertEqual(OUTPUT_WORDS, provenance["output_words"])
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(provenance["trace_words"]), len(records))
        self.assertEqual(len(provenance["table_state_indexes"]), len(records))
        table_states = [bytes.fromhex(value) for value in provenance["table_states_hex"]]
        for state in table_states:
            self.assertEqual(len(state), 706 + 322)
        golden = []
        for trace, state_index in zip(provenance["trace_words"], provenance["table_state_indexes"], strict=True):
            self.assertEqual(len(trace), 170)
            self.assertTrue(0 <= state_index < len(table_states))
            golden.append(trace + list(struct.unpack("<257I", table_states[state_index])))
        expected = b"".join(struct.pack("<427I", *trace) for trace in golden)
        self.assertEqual(hashlib.sha256(expected).hexdigest(), provenance["output_sha256"])
        with tempfile.TemporaryDirectory(prefix="clash95-road-highlight-") as temporary:
            directory = Path(temporary)
            source = directory / "adjacent_highlight.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("adjacent-highlight-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(builder_road.REPO / "src"), str(source), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=30)
                    error = run.stderr.decode()
                    failed = re.search(r"case=(\d+)", error)
                    failed_index = int(failed[1]) if failed else len(run.stdout) // (OUTPUT_WORDS * 4)
                    label = records[failed_index]["name"] if failed_index < len(records) else "fixture setup/output"
                    self.assertEqual(run.returncode, 0, label + ": " + error)
                    self.assertEqual(error, "")
                    self.assertEqual(len(run.stdout), len(expected))
                    for case, observed, wanted in zip(records, struct.iter_unpack("<427I", run.stdout), golden, strict=True):
                        for index in range(170):
                            if index < 10:
                                field = HEADER_FIELDS[index]
                            else:
                                boundary, field_index = divmod(index - 10, 20)
                                field = f"boundary{boundary + 1}.{BOUNDARY_FIELDS[field_index]}"
                            self.assertEqual(observed[index], wanted[index],
                                             f"{case['name']} {field}: {observed[index]:#x} != {wanted[index]:#x}")
                        actual_tables = struct.pack("<257I", *observed[170:])
                        expected_tables = struct.pack("<257I", *wanted[170:])
                        for offset, (value, target) in enumerate(zip(actual_tables, expected_tables, strict=True)):
                            table, position = ("Road", offset) if offset < 706 else ("Builder", offset - 706)
                            self.assertEqual(value, target,
                                             f"{case['name']} {table}[{position}]: {value:#x} != {target:#x}")

    def test_gcc_original_adjacent_highlight_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_adjacent_highlight_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
