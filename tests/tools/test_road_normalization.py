#!/usr/bin/env python3
"""Asset-free regression for the original Road normalization lookup.

The complete uint16 domain is compared with a digest of original x86 results.
The canonical normalizer and initializer execute unchanged. Their callback
addresses are checked against existing relocation fixtures; callback bodies are
recording boundaries and must never be called. No retail executable is needed.

Packed records exclude alignment from UBSan, as in test_builder_road. The
initializer's low32 pointer representation requires the non-PIE Linux harness.
"""
from pathlib import Path
import hashlib
import json
import shutil
import struct
import subprocess
import tempfile
import unittest

import test_builder_road as builder_road


def harness_source():
    _, road, builder, relocations = builder_road.fixtures()
    provenance = json.loads((builder_road.FIXTURES / "normalization-provenance.json").read_text())
    lookup = provenance["shared_lookup"]
    offset, count = lookup["road_offset"], lookup["entries"]
    assert hashlib.sha256(road[offset:offset + 2 * count]).hexdigest() == lookup["sha256"]
    symbols = {entry["canonical_symbol"] for entry in relocations if entry.get("canonical_symbol")}
    symbols.remove("g_ActionButtonSpriteSet")
    boundaries = "\n".join("static int " + name + "() { ++callback_calls; return 0; }"
                           for name in sorted(symbols))
    masks = {"road": bytearray(len(road)), "builder": bytearray(len(builder))}
    checks = []
    for index, entry in enumerate(relocations):
        table = "builder" if entry["table"] == "builder-widgets" else "road"
        data = builder if table == "builder" else road
        actual = "g_UI_YesNoDims" if table == "builder" else "g_RoadBuildData"
        position = entry["region_offset"]
        assert struct.unpack_from("<I", data, position)[0] == int(entry["original_pointer"], 16)
        assert not any(masks[table][position:position + 4])
        masks[table][position:position + 4] = b"\1" * 4
        field = f"{actual} + {position}"
        if entry.get("canonical_symbol"):
            checks.append(f'check_pointer({field}, (uintptr_t)&{entry["canonical_symbol"]});')
        elif "raw_hex" in entry:
            checks.append(builder_road.byte_array(f"text_{index}", bytes.fromhex(entry["raw_hex"]) + b"\0"))
            checks.append(f"check_text({field}, text_{index}, sizeof text_{index});")
        else:
            assert int(entry["original_pointer"], 16) == 0
            checks.append(f"check_pointer({field}, 0);")
    bodies = "\n\n".join(builder_road.extract(path, name) for path, name in (
        (builder_road.WORLD2, "WorldMap_EnsureBuilderWidgetTables"),
        (builder_road.BUILDINGS, "Map_NormalizeRoadOverlayTileId"),
    ))
    data = "".join(builder_road.byte_array(name, values) for name, values in (
        ("original_road", road), ("original_builder", builder),
        ("road_pointer_mask", masks["road"]), ("builder_pointer_mask", masks["builder"]),
    ))
    source = HARNESS.replace("@BOUNDARIES@", boundaries).replace("@BODIES@", bodies)
    source = source.replace("@DATA@", data).replace("@POINTER_CHECKS@", "\n".join(checks))
    source = source.replace("@FIRST_ID@", str(lookup["first_input"]))
    source = source.replace("@LOOKUP_OFFSET@", str(offset)).replace("@LOOKUP_COUNT@", str(count))
    return source, provenance


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int gameData;
int g_ActionButtonSpriteSet;
int g_BuilderRoadWidgetsInitialized;
alignas(4) _BYTE g_RoadBuildData[ROAD_BUILD_DATA_BYTES];
alignas(4) _BYTE g_UI_YesNoDims[BUILDER_ACTION_WIDGET_TABLE_BYTES];
alignas(4) static unsigned char game_memory[256];
static int callback_calls;
@BOUNDARIES@
@BODIES@
@DATA@

static const char *phase;
static int input_id;
static constexpr int first_lookup_id = @FIRST_ID@;
static constexpr int lookup_count = @LOOKUP_COUNT@;
static constexpr int lookup_offset = @LOOKUP_OFFSET@;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "%s input=%d: %s\n", phase, input_id, message);
  std::exit(1);
}

static uint32_t word(const unsigned char *address) {
  uint32_t value;
  std::memcpy(&value, address, sizeof value);
  return value;
}

static void check_pointer(const unsigned char *field, uintptr_t expected) {
  if (expected > INT_MAX || word(field) != expected) fail("relocated pointer differs");
}

static void check_text(const unsigned char *field, const unsigned char *expected, size_t length) {
  const uintptr_t address = word(field);
  if (!address || address > INT_MAX
      || std::memcmp((const void *)address, expected, length)) fail("relocated text differs");
}

struct State {
  unsigned char road[sizeof g_RoadBuildData], builder[sizeof g_UI_YesNoDims];
  unsigned char memory[sizeof game_memory];
  int initialized, game_data, sprite_holder, callbacks;
  State() : initialized(g_BuilderRoadWidgetsInitialized), game_data(gameData),
            sprite_holder(g_ActionButtonSpriteSet), callbacks(callback_calls) {
    std::memcpy(road, g_RoadBuildData, sizeof road);
    std::memcpy(builder, g_UI_YesNoDims, sizeof builder);
    std::memcpy(memory, game_memory, sizeof memory);
  }
  void unrelated_unchanged() const {
    if (gameData != game_data || g_ActionButtonSpriteSet != sprite_holder
        || callback_calls != callbacks || std::memcmp(memory, game_memory, sizeof memory))
      fail("initializer dependency or unrelated state changed");
  }
  void unchanged() const {
    unrelated_unchanged();
    if (g_BuilderRoadWidgetsInitialized != initialized
        || std::memcmp(road, g_RoadBuildData, sizeof road)
        || std::memcmp(builder, g_UI_YesNoDims, sizeof builder)) fail("shared state changed");
  }
};

static int normalize(int id) {
  input_id = id;
  return Map_NormalizeRoadOverlayTileId(id);
}

static void reset_cold() {
  std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
  std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
  std::memset(game_memory, 0xC3, sizeof game_memory);
  g_BuilderRoadWidgetsInitialized = 0;
  gameData = 0;
  g_ActionButtonSpriteSet = 0;
  callback_calls = 0;
}

static void check_initialized_tables() {
  for (size_t index = 0; index < sizeof g_RoadBuildData; ++index)
    if (!road_pointer_mask[index] && g_RoadBuildData[index] != original_road[index])
      fail("cold Road template differs");
  for (size_t index = 0; index < sizeof g_UI_YesNoDims; ++index)
    if (!builder_pointer_mask[index] && g_UI_YesNoDims[index] != original_builder[index])
      fail("cold builder template differs");
  @POINTER_CHECKS@
  if (g_BuilderRoadWidgetsInitialized != 1) fail("cold guard was not set");
}

static void check_cold_calls() {
  phase = "cold nonlookup";
  const int outside[] = {INT_MIN, -1, 0, 818, 862, 876, 877, 949, 950, 65535, INT_MAX};
  for (int id : outside) {
    reset_cold();
    const State before;
    normalize(id);
    before.unchanged();
  }
  phase = "cold lookup";
  for (int index = 0; index < lookup_count; ++index) {
    reset_cold();
    const State before;
    uint16_t original_result;
    std::memcpy(&original_result, original_road + lookup_offset + 2 * index, sizeof original_result);
    if (normalize(first_lookup_id + index) != original_result) fail("original lookup result differs");
    before.unrelated_unchanged();
    check_initialized_tables();
  }
}

static void check_live_holder() {
  phase = "live sprite holder";
  reset_cold();
  normalize(first_lookup_id);
  check_initialized_tables();
  const uintptr_t holder = word(g_UI_YesNoDims + 12);
  check_pointer(g_UI_YesNoDims + 12, (uintptr_t)&g_ActionButtonSpriteSet);
  // Initialization before asset loading must retain the holder's address.
  const int holder_values[] = {0, 0x12345678, 0};
  for (int value : holder_values) {
    g_ActionButtonSpriteSet = value;
    const State before;
    normalize(first_lookup_id);
    if (*(const int *)holder != value) fail("sprite holder contents were cached");
    before.unchanged();
  }
}

static void check_warm_mutations() {
  phase = "warm shared lookup";
  const uint16_t values[] = {0, 0x7FFF, 0x8000, 0xFFFF};
  const int guards[] = {1, -7};
  for (int guard : guards) {
    for (int index = 0; index < lookup_count; ++index) {
      for (uint16_t value : values) {
        // Poison every other byte, including neighboring words and UI records.
        // A duplicate lookup table or an initializer reset must be observable.
        std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
        std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
        std::memcpy(g_RoadBuildData + lookup_offset + 2 * index, &value, sizeof value);
        g_BuilderRoadWidgetsInitialized = guard;
        gameData = (int)(uintptr_t)game_memory;
        g_ActionButtonSpriteSet = 0x12345678;
        const State before;
        if (normalize(first_lookup_id + index) != value) fail("live unsigned word differs");
        before.unchanged();
      }
    }
  }
}

int main() {
  static_assert(std::endian::native == std::endian::little);
  static_assert(sizeof(int32_t) == 4);
  phase = "fixture address";
  if ((uintptr_t)game_memory + sizeof game_memory > INT_MAX) fail("game memory is not signed low32");
  check_cold_calls();
  check_live_holder();
  check_warm_mutations();

  phase = "original uint16 domain";
  reset_cold();
  WorldMap_EnsureBuilderWidgetTables();
  check_initialized_tables();
  const State before;
  static int32_t results[65536];
  for (int id = 0; id < 65536; ++id) {
    results[id] = normalize(id);
    before.unchanged();
  }
  if (std::fwrite(results, sizeof results, 1, stdout) != 1) fail("cannot write results");
}
'''


class RoadNormalizationTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        source, provenance = harness_source()
        oracle = provenance["original_results"]
        with tempfile.TemporaryDirectory(prefix="clash95-road-normalization-") as temporary:
            directory = Path(temporary)
            path = directory / "road_normalization.cpp"
            path.write_text(source)
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("road-normalization-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(builder_road.REPO / "src"), str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], capture_output=True, timeout=30)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    self.assertEqual(len(run.stdout), oracle["bytes"])
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), oracle["sha256"])

    def test_gcc_original_normalization_and_shared_initialization(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_normalization_and_shared_initialization(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
