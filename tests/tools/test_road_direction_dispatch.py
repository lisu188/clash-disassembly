#!/usr/bin/env python3
"""Asset-free traces of the actual selected Road-direction callback.

Valid post-animation selectors use an original-instruction oracle. Invalid
selectors use the pre-refactor canonical oracle because original EDX is not a
declared argument on that path. Callees are explicit recording/mutating
boundaries; this fixture does not claim their gameplay or rendering behavior.
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


INPUT_FIELDS = ("pre_selector", "post_selector", "pre_selected", "post_selected",
                "road_selected", "redraw_selected", "a2", "a3_low", "a3_high",
                "animation_return", "road_return", "redraw_return", "initial_hook_class",
                "redraw_mutates_hook")
TRACE_FIELDS = ("animation_call", "animation_widget_match", "animation_widget_copy_match",
                "animation_selector", "animation_selected", "animation_hook_class",
                "road_call", "road_selected_argument", "road_direction", "callback_byte_matches_symbol",
                "road_a2", "road_a3_low", "road_a3_high", "road_hook_class", "road_selector",
                "road_selected_global", "redraw_call", "redraw_argument", "redraw_hook_class",
                "redraw_selected", "redraw_selector", "handler_result", "final_hook_class",
                "final_selected", "final_selector", "widget_memory_matches", "unrelated_state_matches")


def cases():
    valid, invalid = [], []
    double_bits = (0x0000000000000000, 0x8000000000000000, 0x3FF8000000000000,
                   0xC002000000000000, 0x0000000000000001, 0x0010000000000000,
                   0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF)
    dword_values = (0, 0xFFFFFFFF, 0x80000000, 0x12345678, 0x55555555, 0xAAAAAAAA,
                    0x01020304, 0x7FFFFFFF)

    def add(target, before, after, pattern):
        index = len(valid) + len(invalid)
        bits = double_bits[pattern]
        values = (before, after, (4, -1, 2147483647, -2147483648)[index % 4],
                  (17, -2, 0, 65535)[index % 4], (123, -123, 1, 2)[index % 4],
                  (7, -7, 100, 999)[index % 4], dword_values[pattern],
                  bits & 0xFFFFFFFF, bits >> 32, (0, 1, -1, -2147483648)[index % 4],
                  0x34560000 + index, 0 if pattern == 0 else -index - 10,
                  index % 2, (index // 2) % 2)
        target.append(dict(name=f"selector-{before:x}-to-{after:x}-double-{pattern}",
                           words=[value & 0xFFFFFFFF for value in values]))

    for after in range(27, 31):
        for pattern in range(len(double_bits)):
            for before in (after, 27 + (after - 26) % 4, 0, 0x8000001B):
                add(valid, before, after, pattern)
    for after in (0, 26, 31, 0xFFFFFFFF, 0x8000001B, 0x80000000, 0x7FFFFFFF):
        for pattern in range(len(double_bits)):
            for before in (after, 27):
                add(invalid, before, after, pattern)
    return valid, invalid


def encode_cases(records):
    return struct.pack("<I", len(records)) + b"".join(
        struct.pack("<14I", *case["words"]) for case in records)


def harness_source():
    body = builder_road.extract(builder_road.BUILDINGS, "RoadBuildMode_BuildInSelectedDirection")
    inputs = ", ".join("IN_" + field.upper() for field in INPUT_FIELDS) + ", INPUT_WORDS"
    trace = ", ".join(field.upper() for field in TRACE_FIELDS) + ", TRACE_WORDS"
    return HARNESS.replace("@BODY@", body).replace("@INPUT_ENUM@", inputs).replace("@TRACE_ENUM@", trace)


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

enum InputField { @INPUT_ENUM@ };
enum TraceField { @TRACE_ENUM@ };
using OverlayHook = int (__fastcall *)(_DWORD, _DWORD);
int gameData;
int g_SelectedUnitIndex;
OverlayHook g_WorldMapTileOverlayDrawHook;
alignas(4) static unsigned char widget[53];
static unsigned char expected_widget[sizeof widget];
static unsigned char unrelated[64];
static uint32_t input[INPUT_WORDS], trace[TRACE_WORDS];
static unsigned int case_index;
static int stage;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u boundary=%d: %s\n", case_index, stage, message);
  std::exit(1);
}

static int initial_hook(_DWORD, _DWORD) { fail("initial hook invoked"); }
static int animation_hook(_DWORD, _DWORD) { fail("animation hook invoked"); }
static int build_hook(_DWORD, _DWORD) { fail("build hook invoked"); }
static int redraw_hook(_DWORD, _DWORD) { fail("redraw hook invoked"); }
static int RoadBuildMode_HighlightBuildableAdjacentTile(_DWORD, _DWORD) {
  fail("highlight callback invoked");
}

static uint32_t hook_class() {
  const OverlayHook hook = g_WorldMapTileOverlayDrawHook;
  if (!hook) return 0;
  if (hook == initial_hook) return 1;
  if (hook == animation_hook) return 2;
  if (hook == RoadBuildMode_HighlightBuildableAdjacentTile) return 3;
  if (hook == build_hook) return 4;
  if (hook == redraw_hook) return 5;
  return 255;
}

static uint32_t selector() {
  uint32_t value;
  std::memcpy(&value, widget + 16, sizeof value);
  return value;
}

static void enter_boundary(int expected) {
  if (++stage != expected) fail("boundary order or call count differs");
}

static int UIWidget_PlayPressedReleaseAnimationWithDelay(uintptr_t address, int copied_address) {
  enter_boundary(1);
  trace[ANIMATION_CALL] = 1;
  trace[ANIMATION_WIDGET_MATCH] = (uintptr_t)address == (uintptr_t)widget;
  trace[ANIMATION_WIDGET_COPY_MATCH] = (uintptr_t)copied_address == (uintptr_t)widget;
  trace[ANIMATION_SELECTOR] = selector();
  trace[ANIMATION_SELECTED] = (uint32_t)g_SelectedUnitIndex;
  trace[ANIMATION_HOOK_CLASS] = hook_class();
  // Event callbacks during animation may change both later dispatch inputs.
  std::memcpy(widget + 16, input + IN_POST_SELECTOR, sizeof(uint32_t));
  g_SelectedUnitIndex = (int32_t)input[IN_POST_SELECTED];
  g_WorldMapTileOverlayDrawHook = animation_hook;
  return (int32_t)input[IN_ANIMATION_RETURN];
}

static int Road_Build(int selected, int direction, char callback, DWORD a2, double a3) {
  enter_boundary(2);
  uint64_t bits;
  std::memcpy(&bits, &a3, sizeof bits);
  trace[ROAD_CALL] = 2;
  trace[ROAD_SELECTED_ARGUMENT] = (uint32_t)selected;
  trace[ROAD_DIRECTION] = (uint32_t)direction;
  trace[CALLBACK_BYTE_MATCHES_SYMBOL] = (unsigned char)callback
      == ((uintptr_t)&RoadBuildMode_HighlightBuildableAdjacentTile & 0xFF);
  trace[ROAD_A2] = a2;
  trace[ROAD_A3_LOW] = (uint32_t)bits;
  trace[ROAD_A3_HIGH] = (uint32_t)(bits >> 32);
  trace[ROAD_HOOK_CLASS] = hook_class();
  trace[ROAD_SELECTOR] = selector();
  trace[ROAD_SELECTED_GLOBAL] = (uint32_t)g_SelectedUnitIndex;
  g_SelectedUnitIndex = (int32_t)input[IN_ROAD_SELECTED];
  g_WorldMapTileOverlayDrawHook = build_hook;
  return (int32_t)input[IN_ROAD_RETURN];
}

static int WorldMap_RedrawViewport(int argument) {
  enter_boundary(3);
  trace[REDRAW_CALL] = 3;
  trace[REDRAW_ARGUMENT] = (uint32_t)argument;
  trace[REDRAW_HOOK_CLASS] = hook_class();
  trace[REDRAW_SELECTED] = (uint32_t)g_SelectedUnitIndex;
  trace[REDRAW_SELECTOR] = selector();
  g_SelectedUnitIndex = (int32_t)input[IN_REDRAW_SELECTED];
  if (input[IN_REDRAW_MUTATES_HOOK]) g_WorldMapTileOverlayDrawHook = redraw_hook;
  return (int32_t)input[IN_REDRAW_RETURN];
}

@BODY@

static void read_exact(void *target, size_t bytes) {
  if (std::fread(target, 1, bytes, stdin) != bytes) fail("short fixture input");
}

int main() {
  static_assert(std::endian::native == std::endian::little);
  static_assert(sizeof(DWORD) == 4 && sizeof(double) == 8);
  if ((uintptr_t)widget + sizeof widget > INT_MAX) fail("widget is not signed low32");
  unsigned int count;
  read_exact(&count, sizeof count);
  if (!count || count > 1024) fail("invalid fixture count");
  for (case_index = 0; case_index < count; ++case_index) {
    read_exact(input, sizeof input);
    if (input[IN_INITIAL_HOOK_CLASS] > 1 || input[IN_REDRAW_MUTATES_HOOK] > 1) fail("invalid hook case");
    stage = 0;
    std::memset(trace, 0, sizeof trace);
    std::memset(widget, 0xA5, sizeof widget);
    std::memcpy(widget + 16, input + IN_PRE_SELECTOR, sizeof(uint32_t));
    std::memcpy(expected_widget, widget, sizeof widget);
    std::memcpy(expected_widget + 16, input + IN_POST_SELECTOR, sizeof(uint32_t));
    std::memset(unrelated, 0x5A, sizeof unrelated);
    gameData = 0x11223344;
    g_SelectedUnitIndex = (int32_t)input[IN_PRE_SELECTED];
    g_WorldMapTileOverlayDrawHook = input[IN_INITIAL_HOOK_CLASS] ? initial_hook : nullptr;
    const uint64_t bits = input[IN_A3_LOW] | ((uint64_t)input[IN_A3_HIGH] << 32);
    double value;
    std::memcpy(&value, &bits, sizeof value);
    const int result = RoadBuildMode_BuildInSelectedDirection((int)(uintptr_t)widget, input[IN_A2], value);
    if (stage != 3) fail("missing boundary call");
    trace[HANDLER_RESULT] = (uint32_t)result;
    trace[FINAL_HOOK_CLASS] = hook_class();
    trace[FINAL_SELECTED] = (uint32_t)g_SelectedUnitIndex;
    trace[FINAL_SELECTOR] = selector();
    trace[WIDGET_MEMORY_MATCHES] = std::memcmp(widget, expected_widget, sizeof widget) == 0;
    bool unchanged = gameData == 0x11223344;
    for (unsigned char byte : unrelated) unchanged = unchanged && byte == 0x5A;
    trace[UNRELATED_STATE_MATCHES] = unchanged;
    if (std::fwrite(trace, sizeof trace, 1, stdout) != 1) fail("cannot write trace");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing fixture input");
}
'''


class RoadDirectionDispatchTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "direction-dispatch-provenance.json").read_text())
        self.assertEqual(list(INPUT_FIELDS), provenance["input_fields"])
        self.assertEqual(list(TRACE_FIELDS), provenance["trace_fields"])
        with tempfile.TemporaryDirectory(prefix="clash95-road-dispatch-") as temporary:
            directory = Path(temporary)
            path = directory / "direction_dispatch.cpp"
            path.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("direction-dispatch-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(builder_road.REPO / "src"), str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    for group, records in zip(("valid", "invalid"), cases()):
                        oracle = provenance[group]
                        encoded = encode_cases(records)
                        self.assertEqual(hashlib.sha256(encoded).hexdigest(), oracle["input_sha256"])
                        golden = oracle["trace_words"]
                        self.assertEqual(len(golden), len(records))
                        expected = b"".join(struct.pack("<27I", *trace) for trace in golden)
                        self.assertEqual(hashlib.sha256(expected).hexdigest(), oracle["trace_sha256"])
                        run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=30)
                        error = run.stderr.decode()
                        failed = re.search(r"case=(\d+)", error)
                        label = records[int(failed[1])]["name"] if failed and int(failed[1]) < len(records) else group
                        self.assertEqual(run.returncode, 0, label + ": " + error)
                        self.assertEqual(error, "")
                        self.assertEqual(len(run.stdout), len(expected))
                        actual = list(struct.iter_unpack("<27I", run.stdout))
                        for case, observed, wanted in zip(records, actual, golden, strict=True):
                            for field, value, target in zip(TRACE_FIELDS, observed, wanted, strict=True):
                                self.assertEqual(value, target,
                                                 f"{group} {case['name']} {field}: {value:#x} != {target:#x}")

    def test_gcc_original_valid_dispatch_and_canonical_invalid_dispatch(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_valid_dispatch_and_canonical_invalid_dispatch(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
