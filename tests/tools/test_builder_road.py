#!/usr/bin/env python3
"""Asset-free checks against original-measured builder and bridge fixtures.

The selector and bridge predicate execute their actual canonical bodies. Golden
returns came from unchanged original x86 instructions, not a second C++ formula.
The actual initializer is checked against both PE data blocks, with only pointer
fields relocated. Callback bodies other than the selector are inert boundaries:
their identities are checked, but their UI/gameplay behavior is not simulated.

Packed accesses exclude alignment from UBSan. Inputs stay in the map and signed
32-bit arithmetic range; these tests do not establish general overflow safety.
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

REPO = Path(__file__).resolve().parents[2]
FIXTURES = Path(__file__).resolve().parent / "fixtures/builder_road"
WORLD1 = REPO / "src/world/00408030_0040A0A0_world_001.cpp"
WORLD2 = REPO / "src/world/0040A0E0_0040B020_world_002.cpp"
BUILDINGS = REPO / "src/buildings/00422B50_004254E0_buildings_005.cpp"
SELECTOR = "WorldMap_ComputeBuildMenuActionFromCursor"


def extract(path, name):
    match = re.search(r"^[^\n;{}]*\b" + re.escape(name) + r"\([^;{}]*\)\n\{.*?^\}",
                      path.read_text(), re.M | re.S)
    if not match:
        raise AssertionError("actual canonical function missing: " + name)
    return match.group()


def byte_array(name, data):
    return "static const unsigned char " + name + "[] = {" + ",".join(map(str, data)) + "};\n"


def fixtures():
    provenance = json.loads((FIXTURES / "provenance.json").read_text())
    road = (FIXTURES / "original-road.bin").read_bytes()
    builder = (FIXTURES / "original-builder.bin").read_bytes()
    for name, data in (("road", road), ("builder", builder)):
        assert len(data) == provenance["blocks"][name]["bytes"]
        assert hashlib.sha256(data).hexdigest() == provenance["blocks"][name]["sha256"]
    cases = json.loads((FIXTURES / "cases.json").read_text())
    assert len(cases) == 672 == provenance["cases"]
    assert len({case["name"] for case in cases}) == len(cases)
    assert sum(case["op"] == 0 for case in cases) == 636
    measured = b"".join(struct.pack("<ii6I", case["expected"],
                                   case["expected"] if case["op"] else -12345,
                                   0, 0, 0, case["op"], case["op"], 0) for case in cases)
    assert hashlib.sha256(measured).hexdigest() == provenance["original_output_sha256"]
    relocations = json.loads((FIXTURES / "pointer-relocations.json").read_text())["relocations"]
    return cases, road, builder, relocations


def encode_cases(cases):
    result = bytearray(struct.pack("<I", len(cases)))
    for case in cases:
        result.extend(struct.pack("<9i", case["op"], *case["args"], case["ground"],
                                  case["overlay"], case["expected"], len(case["patches"])))
        for offset, value in case["patches"]:
            result.extend(struct.pack("<II", offset, value))
    return result


def harness_source():
    cases, road, builder, relocations = fixtures()
    main = json.loads((FIXTURES / "main-callbacks.json").read_text())
    assert main["record_bytes"] == 53 and len(main["callbacks"]) == 6
    assert main["callbacks"][4]["original_pointer"] == "0x40a0e0"
    main_callbacks = [item["canonical_symbol"] for item in main["callbacks"]]
    assert main_callbacks[4] == "WorldMap_HandleBuilderActionMenu"
    symbols = {entry["canonical_symbol"] for entry in relocations if entry.get("canonical_symbol")}
    symbols.update(main_callbacks)
    symbols.difference_update((SELECTOR, "g_ActionButtonSpriteSet"))
    boundaries = "\n".join("static int " + name + "() { return 0; }" for name in sorted(symbols))
    checks = []
    masks = {"road": bytearray(len(road)), "builder": bytearray(len(builder))}
    seen = set()
    for index, entry in enumerate(relocations):
        table = "builder" if entry["table"] == "builder-widgets" else "road"
        data = builder if table == "builder" else road
        actual = "g_UI_YesNoDims" if table == "builder" else "g_RoadBuildData"
        offset = entry["region_offset"]
        assert (table, offset) not in seen
        seen.add((table, offset))
        assert struct.unpack_from("<I", data, offset)[0] == int(entry["original_pointer"], 16)
        masks[table][offset:offset+4] = b"\1" * 4
        field = f"{actual} + {offset}"
        label = f"{entry['table']}[{entry['index']}].{entry['field']}"
        if entry.get("canonical_symbol"):
            checks.append(f'check_pointer({field}, (uintptr_t)&{entry["canonical_symbol"]}, "{label}");')
        elif "raw_hex" in entry:
            raw = bytes.fromhex(entry["raw_hex"]) + b"\0"
            checks.append(byte_array(f"expected_text_{index}", raw))
            checks.append(f'check_text({field}, expected_text_{index}, sizeof expected_text_{index}, "{label}");')
        else:
            assert int(entry["original_pointer"], 16) == 0
            checks.append(f'check_pointer({field}, 0, "{label}");')
    bodies = "\n\n".join(extract(path, name) for path, name in (
        (WORLD1, SELECTOR),
        (WORLD2, "WorldMap_WriteActionWidgetRecord"),
        (WORLD2, "WorldMap_EnsureActionButtonWidgetTable"),
        (WORLD2, "WorldMap_EnsureBuilderWidgetTables"),
        (BUILDINGS, "MapTile_HasAlignedBridgeApproachRoadOverlay"),
    ))
    source = HARNESS.replace("@BOUNDARIES@", boundaries).replace("@BODIES@", bodies)
    source = source.replace("@RAW_DATA@", byte_array("original_road", road)
                            + byte_array("original_builder", builder)
                            + byte_array("road_pointer_mask", masks["road"])
                            + byte_array("builder_pointer_mask", masks["builder"]))
    source = source.replace("@POINTER_CHECKS@", "\n".join(checks))
    source = source.replace("@MAIN_CALLBACKS@", ",".join("(uintptr_t)&" + name for name in main_callbacks))
    return source, cases


HARNESS = r'''
#include "recovered_layout.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int gameData;
int g_ActionButtonSpriteSet;
int g_WorldMapBuilderMenuAction;
int g_BuilderRoadWidgetsInitialized;
int g_WorldMapActionWidgetsInitialized;
alignas(4) _BYTE g_RoadBuildData[ROAD_BUILD_DATA_BYTES];
alignas(4) _BYTE g_UI_YesNoDims[BUILDER_ACTION_WIDGET_TABLE_BYTES];
alignas(4) unsigned char g_WorldMapActionButtonWidgetTable[322];
static int animation_calls, animation_widget;
static int UIWidget_PlayPressedReleaseAnimationWithDelay(int widget, int delay) {
  (void)delay;
  ++animation_calls;
  animation_widget = widget;
  return 0;
}
@BOUNDARIES@
@BODIES@
@RAW_DATA@
alignas(16) static unsigned char memory[140000];
alignas(4) static unsigned char widget[53];
static unsigned char memory_before[sizeof memory], widget_before[sizeof widget];
static unsigned char road_before[sizeof g_RoadBuildData], builder_before[sizeof g_UI_YesNoDims];
static unsigned int case_index;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "builder-road case=%u: %s\n", case_index, message);
  std::exit(1);
}

static unsigned int word(const void *address) {
  unsigned int result;
  std::memcpy(&result, address, 4);
  return result;
}

static void read_exact(void *destination, size_t bytes) {
  if (std::fread(destination, 1, bytes, stdin) != bytes) fail("incomplete fixture");
}

static void check_pointer(const void *field, uintptr_t expected, const char *label) {
  if (expected > INT_MAX || word(field) != expected) fail(label);
}

static void check_text(const void *field, const unsigned char *expected, size_t count,
                       const char *label) {
  const uintptr_t pointer = word(field);
  if (pointer < 0x10000 || pointer > INT_MAX) fail(label);
  if (std::memcmp((const void *)pointer, expected, count)) fail(label);
}

static void check_nonpointer_bytes(const unsigned char *actual, const unsigned char *expected,
                                   const unsigned char *mask, size_t count) {
  for (size_t offset = 0; offset < count; ++offset) {
    if (!mask[offset] && actual[offset] != expected[offset]) {
      std::fprintf(stderr, "byte offset=%zu actual=%u expected=%u\n", offset, actual[offset], expected[offset]);
      fail("original table data differs outside pointer fields");
    }
  }
}

static void check_layout() {
  static_assert(sizeof g_RoadBuildData == 706);
  static_assert(sizeof g_UI_YesNoDims == 322);
  static_assert(WORLD_MAP_ACTION_WIDGET_RECORD_SIZE == 53);
  static_assert(WORLD_MAP_ACTION_WIDGET_COUNT == 6);
  std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
  std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
  WorldMap_EnsureBuilderWidgetTables();
  if (g_BuilderRoadWidgetsInitialized != 1) fail("builder initialization marker");
  check_nonpointer_bytes(g_RoadBuildData, original_road, road_pointer_mask, sizeof original_road);
  check_nonpointer_bytes(g_UI_YesNoDims, original_builder, builder_pointer_mask, sizeof original_builder);
  @POINTER_CHECKS@

  // These aliases refer to the original physical backing, including odd offsets.
  if ((unsigned char *)g_BridgeApproachRoadOverlayTileIds != g_RoadBuildData
      || (unsigned char *)g_RoadBuildModeMarkerBounceOffsets != g_RoadBuildData + 0x88
      || g_RoadBuildModeDirectionalWidgets != g_RoadBuildData + 0xAC
      || (unsigned char *)g_RoadBuildModeControlWidgets != g_RoadBuildData + 0x180)
    fail("road backing aliases");
  int *markers[] = {&g_RoadBuildModeNorthMarkerX, &g_RoadBuildModeNorthMarkerY,
    &g_RoadBuildModeEastMarkerX, &g_RoadBuildModeEastMarkerY,
    &g_RoadBuildModeSouthMarkerX, &g_RoadBuildModeSouthMarkerY,
    &g_RoadBuildModeWestMarkerX, &g_RoadBuildModeWestMarkerY, &g_RoadBuildModeControlWidgetState};
  const unsigned int offsets[] = {0xAC,0xB0,0xE1,0xE5,0x116,0x11A,0x14B,0x14F,0x188};
  for (unsigned int index = 0; index < 9; ++index) {
    if ((unsigned char *)markers[index] != g_RoadBuildData + offsets[index]) fail("marker alias offset");
    *markers[index] = 62000 + index;
    if (word(g_RoadBuildData + offsets[index]) != 62000 + index) fail("marker write does not alias");
  }
  if (g_BridgeApproachRoadOverlayTileIds[43] != 62000
      || g_BridgeApproachRoadOverlayTileIds[44] != 62001) fail("live north marker scan overlap");
  g_RoadBuildModeMarkerBounceOffsets[8] = 63000;
  g_UI_YesNoDims[8] = 7;
  std::memcpy(road_before, g_RoadBuildData, sizeof road_before);
  std::memcpy(builder_before, g_UI_YesNoDims, sizeof builder_before);
  WorldMap_EnsureBuilderWidgetTables();
  if (std::memcmp(road_before, g_RoadBuildData, sizeof road_before)
      || std::memcmp(builder_before, g_UI_YesNoDims, sizeof builder_before)) fail("initializer overwrites live tables");

  // The original main Building record at index 4 dispatches 0x40A0E0.
  // Other callback identities are retained to catch record-stride corruption.
  WorldMap_EnsureActionButtonWidgetTable();
  const uintptr_t callbacks[] = {@MAIN_CALLBACKS@};
  for (unsigned int index = 0; index < 6; ++index)
    check_pointer(g_WorldMapActionButtonWidgetTable + index * 53 + 32, callbacks[index], "main action callback");
  if (word(g_WorldMapActionButtonWidgetTable + 318) != UINT_MAX) fail("main action sentinel");
}

int main() {
  if ((uintptr_t)memory + sizeof memory > INT_MAX || (uintptr_t)widget + sizeof widget > INT_MAX)
    fail("fixture memory is not signed low32");
  const int base = (int)(uintptr_t)memory;
  gameData = base;
  check_layout();
  unsigned int count;
  read_exact(&count, sizeof count);
  if (count != 672) fail("invalid case count");
  for (case_index = 0; case_index < count; ++case_index) {
    int descriptor[9];
    read_exact(descriptor, sizeof descriptor);
    std::memset(memory, 0, sizeof memory);
    std::memset(widget, 0xA5, sizeof widget);
    // Gate calls the real, already initialized helper: it must preserve mutations.
    std::memcpy(g_RoadBuildData, original_road, sizeof original_road);
    if (descriptor[8] < 0 || descriptor[8] > 100) fail("invalid patch count");
    for (int patch = 0; patch < descriptor[8]; ++patch) {
      unsigned int item[2];
      read_exact(item, sizeof item);
      if (item[0] > sizeof g_RoadBuildData - 4) fail("patch outside road backing");
      std::memcpy(g_RoadBuildData + item[0], item + 1, 4);
    }
    if (descriptor[0] == 0) {
      const int column = descriptor[3], row = descriptor[4];
      if (column < 0 || column >= 100 || row < 0 || row >= 100) fail("tile outside fixture map");
      const size_t tile = 1400 * row + 14 * column;
      const unsigned short terrain = (unsigned short)descriptor[5], overlay = (unsigned short)descriptor[6];
      std::memcpy(memory + tile, &terrain, 2);
      std::memcpy(memory + tile + 2, &overlay, 2);
    } else {
      std::memcpy(widget + 16, descriptor + 1, 4);
    }
    std::memcpy(memory_before, memory, sizeof memory);
    std::memcpy(widget_before, widget, sizeof widget);
    std::memcpy(road_before, g_RoadBuildData, sizeof road_before);
    animation_calls = 0;
    animation_widget = 0;
    g_WorldMapBuilderMenuAction = 0x12345678;
    int actual;
    if (descriptor[0] == 0) {
      actual = MapTile_HasAlignedBridgeApproachRoadOverlay(descriptor[1], descriptor[2], descriptor[3], descriptor[4]);
      if (animation_calls || g_WorldMapBuilderMenuAction != 0x12345678) fail("gate changed selector state");
    } else if (descriptor[0] == 1) {
      const int address = (int)(uintptr_t)widget;
      actual = WorldMap_ComputeBuildMenuActionFromCursor(address, descriptor[2]);
      if (animation_calls != 1 || animation_widget != address) fail("animation boundary call");
      if (g_WorldMapBuilderMenuAction != descriptor[7]) fail("original menu result differs");
    } else fail("invalid fixture operation");
    if (actual != descriptor[7]) {
      std::fprintf(stderr, "actual=%d expected=%d\n", actual, descriptor[7]);
      fail("original return differs");
    }
    if (std::memcmp(memory_before, memory, sizeof memory)) fail("gameData mutated");
    if (std::memcmp(widget_before, widget, sizeof widget)) fail("widget mutated");
    if (std::memcmp(road_before, g_RoadBuildData, sizeof road_before)) fail("road backing mutated");
    if (gameData != base) fail("gameData pointer changed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing fixture bytes");
  std::printf("builder-road cases=%u layout=706+322 callbacks=6\n", count);
}
'''


class BuilderRoadTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        source, cases = harness_source()
        with tempfile.TemporaryDirectory(prefix="clash95-builder-road-") as temporary:
            directory = Path(temporary)
            path = directory / "builder_road.cpp"
            path.write_text(source)
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("builder-road-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(REPO / "src"), str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encode_cases(cases),
                                         capture_output=True, timeout=30)
                    error = run.stderr.decode()
                    failed = re.search(r"case=(\d+)", error)
                    name = cases[int(failed[1])]["name"] if failed and int(failed[1]) < len(cases) else "layout"
                    self.assertEqual(run.returncode, 0, name + ": " + error)
                    self.assertEqual(run.stdout.decode(), "builder-road cases=672 layout=706+322 callbacks=6\n")
                    self.assertEqual(error, "")

    def test_gcc_actual_builder_selector_tables_and_bridge_gate(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_actual_builder_selector_tables_and_bridge_gate(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
