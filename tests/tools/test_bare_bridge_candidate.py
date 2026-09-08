#!/usr/bin/env python3
"""Asset-free, original-measured checks for the bare bridge candidate predicate.

Inputs exercise the actual canonical body. Expected returns are a digest of
unchanged original x86 results, not a second implementation of the predicate.
Read-only arenas and protected dimension pages check the memory-access boundary.
Packed records exclude alignment from UBSan. Negative/extreme coordinates occur
only in measured early-return cases; general overflow is outside this fixture.
The low32, protected-page harness requires non-PIE Linux with 4096-byte pages.
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


DIRECTIONS = ("north", "south", "west", "east")


def cases():
    result = []

    def add(name, *, width=100, height=100, row=37, column=61, terrain=603,
            overlay=65535, road=32768, neighbors=(65535,) * 4, poison=0xA5):
        result.append(dict(name=name, words=[width, height, row, column, terrain,
                                            overlay, road, *neighbors, poison]))

    def isolated(direction, value):
        neighbors = [65535] * 4
        neighbors[direction] = value
        return neighbors

    values = (*range(7), 818, 819, 861, 866, 867, 876, *range(877, 949),
              949, 950, 32767, 32768, 65535)
    connecting = (877, 878, 880, 881)
    for direction, name in enumerate(DIRECTIONS):
        for value in values:
            add(f"{name}-word-{value}", neighbors=isolated(direction, value))
        for terrain in (0, 602, *range(603, 611), 611, 32767, 32768, 65535):
            add(f"{name}-terrain-{terrain}", terrain=terrain,
                neighbors=isolated(direction, connecting[direction]))
        for overlay in (0, 1, 877, 32768, 65534, 65535):
            add(f"{name}-overlay-{overlay}", overlay=overlay,
                neighbors=isolated(direction, connecting[direction]))
        for road in (0, 1, 866, 867, 877, 948, 949, 32768, 65535):
            add(f"{name}-ignored-center-road-{road}", road=road,
                neighbors=isolated(direction, connecting[direction]))
    for poison in (0, 0x7F, 0x80, 0xFF):
        add(f"ignored-bytes-{poison}-disconnected", poison=poison)
        for direction, name in enumerate(DIRECTIONS):
            add(f"ignored-bytes-{poison}-{name}", poison=poison,
                neighbors=isolated(direction, connecting[direction]))
    for kind, words in (("raw", (0, 1, 3, 4)), ("animated", connecting)):
        for mask in range(16):
            add(f"mixed-{kind}-{mask}",
                neighbors=[words[index] if mask & (1 << index) else 65535 for index in range(4)])
    positions = ((100, 100, 1, 1), (100, 100, 1, 98), (100, 100, 98, 1),
                 (100, 100, 98, 98), (7, 11, 5, 9), (11, 7, 9, 5),
                 (7, 11, 6, 9), (7, 11, 5, 10), (11, 7, 10, 5), (11, 7, 9, 6),
                 (100, 100, 0, 37), (100, 100, 99, 37),
                 (100, 100, 37, 0), (100, 100, 37, 99),
                 (0, 100, -1, 37), (-1, 100, -2, 37),
                 (100, 0, 37, -1), (100, -1, 37, -2))
    for width, height, row, column in positions:
        for direction, name in enumerate(DIRECTIONS):
            add(f"position-{width}-{height}-{row}-{column}-{name}",
                width=width, height=height, row=row, column=column,
                neighbors=isolated(direction, connecting[direction]))
    assert len({case["name"] for case in result}) == len(result)
    return result


def encode_cases(records):
    return struct.pack("<I", len(records)) + b"".join(
        struct.pack("<4i8I", *case["words"]) for case in records)


def guard_cases():
    # width/height, row/column, readable dimension pages, null gameData.
    result = [(100, 100, 0, -2147483648, 0, 1), (100, 100, 0, 2147483647, 0, 1)]
    limits = ((100, 99), (0, -1), (4294967295, -2),
              (2147483648, 2147483647), (2147483649, -2147483648))
    result.extend((width, 100, row, 37, 1, 0) for width, row in limits)
    result.append((100, 100, 1, 0, 1, 0))
    result.extend((100, height, 1, column, 2, 0) for height, column in limits)
    return result


def harness_source(count):
    body = builder_road.extract(builder_road.BUILDINGS, "MapTile_IsBareBridgeCrossingRoadOverlayCandidate")
    guards = ",\n".join("{" + ",".join(map(str, values)) + "}" for values in guard_cases())
    return HARNESS.replace("@BODY@", body).replace("@COUNT@", str(count)).replace("@GUARDS@", guards)


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

int gameData;
@BODY@

static constexpr int page_size = 4096;
static constexpr int prefix_size = 4096;
alignas(page_size) static unsigned char memory[64 * page_size];
static unsigned char before[sizeof memory];
alignas(page_size) static unsigned char guarded[36 * page_size];
static unsigned char guarded_before[sizeof guarded];
static const char *phase;
static unsigned int case_index;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "%s case=%u: %s\n", phase, case_index, message);
  std::exit(1);
}

static void protect(void *address, size_t bytes, int protection) {
  if (mprotect(address, bytes, protection)) fail("mprotect failed");
}

static void read_exact(void *target, size_t bytes) {
  if (std::fread(target, 1, bytes, stdin) != bytes) fail("short case stream");
}

static void write_tile_word(int row, int column, int field, uint16_t value) {
  const int offset = prefix_size + 1400 * row + 14 * column + field;
  if (offset < 0 || (size_t)offset > sizeof memory - sizeof value) fail("case outside arena");
  std::memcpy(memory + offset, &value, sizeof value);
}

struct GuardCase {
  uint32_t width, height;
  int row, column, readable_pages, null_game_data;
};

static void check_boundary_access() {
  phase = "boundary access";
  const GuardCase cases[] = {@GUARDS@};
  // Width ends one page; height begins the next. Every tile page is denied.
  const int width_offset = 35 * page_size - 4;
  const int game_offset = width_offset - MAP_WIDTH_TILES_OFFSET;
  for (case_index = 0; case_index < sizeof cases / sizeof cases[0]; ++case_index) {
    const GuardCase &item = cases[case_index];
    std::memset(guarded, 0xA5, sizeof guarded);
    std::memcpy(guarded + width_offset, &item.width, 4);
    std::memcpy(guarded + width_offset + 4, &item.height, 4);
    std::memcpy(guarded_before, guarded, sizeof guarded);
    const int base = item.null_game_data ? 0 : (int)(uintptr_t)(guarded + game_offset);
    gameData = base;
    protect(guarded, sizeof guarded, PROT_NONE);
    if (item.readable_pages)
      protect(guarded + 34 * page_size, item.readable_pages * page_size, PROT_READ);
    const int actual = MapTile_IsBareBridgeCrossingRoadOverlayCandidate(item.row, item.column);
    protect(guarded, sizeof guarded, PROT_READ | PROT_WRITE);
    if (actual != 0) fail("original boundary return differs");
    if (gameData != base || std::memcmp(guarded_before, guarded, sizeof guarded))
      fail("boundary state changed");
  }
}

int main() {
  static_assert(std::endian::native == std::endian::little);
  static_assert(sizeof(int32_t) == 4);
  phase = "fixture layout";
  if (sysconf(_SC_PAGESIZE) != page_size) fail("fixture requires 4096-byte pages");
  if ((uintptr_t)memory + sizeof memory > INT_MAX
      || (uintptr_t)guarded + sizeof guarded > INT_MAX) fail("arena is not signed low32");
  check_boundary_access();
  phase = "original case";
  unsigned int count;
  read_exact(&count, sizeof count);
  if (count != @COUNT@) fail("unexpected case count");
  static int32_t results[@COUNT@];
  for (case_index = 0; case_index < count; ++case_index) {
    int32_t descriptor[12];
    read_exact(descriptor, sizeof descriptor);
    if (descriptor[11] < 0 || descriptor[11] > 255) fail("invalid poison byte");
    std::memset(memory, descriptor[11], sizeof memory);
    const int row = descriptor[2], column = descriptor[3];
    write_tile_word(row, column, 0, (uint16_t)descriptor[4]);
    write_tile_word(row, column, 2, (uint16_t)descriptor[5]);
    write_tile_word(row, column, 4, (uint16_t)descriptor[6]);
    write_tile_word(row - 1, column, 4, (uint16_t)descriptor[7]);
    write_tile_word(row + 1, column, 4, (uint16_t)descriptor[8]);
    write_tile_word(row, column - 1, 4, (uint16_t)descriptor[9]);
    write_tile_word(row, column + 1, 4, (uint16_t)descriptor[10]);
    std::memcpy(memory + prefix_size + MAP_WIDTH_TILES_OFFSET, descriptor, 4);
    std::memcpy(memory + prefix_size + MAP_HEIGHT_TILES_OFFSET, descriptor + 1, 4);
    std::memcpy(before, memory, sizeof before);
    const int base = (int)(uintptr_t)(memory + prefix_size);
    gameData = base;
    protect(memory, sizeof memory, PROT_READ);
    results[case_index] = MapTile_IsBareBridgeCrossingRoadOverlayCandidate(row, column);
    protect(memory, sizeof memory, PROT_READ | PROT_WRITE);
    if (gameData != base || std::memcmp(before, memory, sizeof memory)) fail("case state changed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing case bytes");
  if (std::fwrite(results, sizeof results, 1, stdout) != 1) fail("cannot write results");
}
'''


class BareBridgeCandidateTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        records = cases()
        encoded = encode_cases(records)
        provenance = json.loads((builder_road.FIXTURES / "bare-bridge-provenance.json").read_text())
        self.assertEqual(len(records), provenance["cases"])
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual([list(values) for values in guard_cases()], provenance["boundary_cases"])
        with tempfile.TemporaryDirectory(prefix="clash95-bare-bridge-") as temporary:
            directory = Path(temporary)
            path = directory / "bare_bridge.cpp"
            path.write_text(harness_source(len(records)))
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("bare-bridge-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(builder_road.REPO / "src"), str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=30)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    self.assertEqual(len(run.stdout), 4 * len(records))
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["original_output_sha256"])

    def test_gcc_original_bare_bridge_candidate_and_boundaries(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_bare_bridge_candidate_and_boundaries(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
