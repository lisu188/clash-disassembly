#!/usr/bin/env python3
"""Asset-free original-measured checks of the actual nation/building value code.

Fixed outcomes were measured using unchanged original PE functions at 0x43F240
and 0x43F340 and the original 40-record unit metadata table. These fixtures only
construct input bytes; no expected-score formula or replacement body is used.
The test needs canonical source and a C++ compiler, never retail or artifacts.

UBSan excludes alignment because these recovered functions read packed fields.
Inputs keep licence indices within the 40 physical records and signed sums in
int32 range. This does not establish overflow fidelity or general UB safety.
"""
from pathlib import Path
import re
import shutil
import struct
import subprocess
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
SOURCE = REPO / "src/buildings/0043E500_0043FDE0_buildings_006.cpp"
STATE = REPO / "src/state/00000000_0054FFFF_recovered_state.cpp"
BUILDING = 509674
STACK = 147174

# Original executable outcomes, in fixture_cases() order. These constants are
# independent of the canonical implementation and its runtime metadata values.
ORIGINAL_RESULTS = (
    0, 500, 1250, 500, 750, 500, 500, 500, 500, 500, 500, 1250,
    1132, 1131, 1249, 1250, -1, 0, 0, 0, 500, 500, 0, 0,
    0, 0, 0, 500, 0, 500, 500, 500, 500, 500, 500, 0,
    0, 0, 0, 0, 0, 127, 127, 0, 0, -128, -128, 0,
    0, -1, -1, 0, 198960, 0, 500, 500, 0, 0, 0, 0,
    0, 500, 0, 500, 500, 500, 500, 500, 500, 0, 0, 0,
    0, 0, 0, 127, 127, 0, 0, -128, -128, 0, 0, -1,
    -1, 0, 198960, 0, 500, 500, 0, 0, 0, 0, 0, 500,
    0, 500, 500, 500, 500, 500, 500, 0, 0, 0, 0, 0,
    0, 127, 127, 0, 0, -128, -128, 0, 0, -1, -1, 0,
    198960, 0, 500, 500, 0, 0, 0, 0, 0, 500, 0, 500,
    500, 500, 500, 500, 500, 0, 0, 0, 0, 0, 0, 127,
    127, 0, 0, -128, -128, 0, 0, -1, -1, 0, 198960, 0,
    500, 500, 0, 0, 0, 0, 0, 500, 0, 500, 500, 500,
    500, 500, 500, 0, 0, 0, 0, 0, 0, 127, 127, 0,
    0, -128, -128, 0, 0, -1, -1, 0, 198960, 0, 500, 500,
    0, 0, 0, 0, 0, 500, 0, 500, 500, 500, 500, 500,
    500, 0, 0, 0, 0, 0, 0, 127, 127, 0, 0, -128,
    -128, 0, 0, -1, -1, 0, 198960, 500, 700, 700, 900, 690,
    890, 890, 1090, 900, 1100, 1100, 1300, 1090, 1290, 1290, 1490, 730,
    930, 930, 1130, 920, 1120, 1120, 1320, 1130, 1330, 1330, 1530, 1320,
    1520, 1520, 1720, -1, 999, 0, 1000, 4094, 5094, -1, 999, -1,
    999, 4094, 5094, 500, 510, 530, 530, 550, 600, 700, 650, 650,
    560, 740, 790, 800, 550, 900, 600, 580, 580, 750, 800, 780,
    770, 790, 780, 900, 880, 800, 850, 900, 880, 1050, 880, 880,
    880, 880, 500, 500, 500, 500, 500, 1810,
)


def patch(offset, value, fmt):
    return (offset, struct.pack("<" + fmt, value))


def building(index=0, owner=0, kind=2, valid=0, pop=100, gold=400, flags=0, licences=None):
    base = BUILDING + 467 * index
    return [patch(base+2, owner, "B"), patch(base+4, kind & 255, "B"),
            patch(base+16, valid & 65535, "H"), patch(base+430, pop & 65535, "H"),
            patch(base+438, gold & 0xffffffff, "I"), patch(base+416, flags, "I"),
            (base+402, bytes([255]*12 if licences is None else [x & 255 for x in licences]))]


def cargo(index=0, owner=0, slots=()):
    base = STACK + 725 * index
    result = [patch(base+4, owner, "B")]
    for slot, unit_type, value in slots:
        result.extend([patch(base+6+31*slot, unit_type & 65535, "H"),
                       patch(base+15+31*slot, value & 255, "B")])
    return result


def fixture_cases():
    cases = []

    def add(name, patches=(), player=0, operation=0):
        cases.append((name, operation, player, patches))

    first = building()
    last = building(99, kind=1, valid=7, pop=150, gold=600)
    add("native-empty")
    add("native-single-500", first)
    add("native-two-1250", first+last)
    other = first+last+[patch(BUILDING+467*99+2, 1, "B")]
    add("native-owner0-500", other)
    add("native-owner1-750", other, 1)
    for kind in (0, 3, 127, 128, 255):
        add(f"native-kind-{kind}", first+last+[patch(BUILDING+467*99+4, kind, "B")])
    add("native-construction-ffff", first+last+[patch(BUILDING+467*99+16, 65535, "H")])
    add("native-construction-8000", first+last+[patch(BUILDING+467*99+16, 32768, "H")])
    gap = [patch(BUILDING+467*99+16, 0, "H")]+cargo(slots=[(0,31,10), (1,-1,0), (9,32,128)])
    last_cargo = cargo(499, slots=[(0,0,0), (9,31,255)])
    add("native-cargo-gapped-1132", first+last+gap)
    add("native-last-stack-1131", first+last+gap+last_cargo)
    absent = first+last+gap+last_cargo+[patch(STACK+6, 65535, "H")]
    add("native-first-slot-empty-1249", absent)
    other_cargo = absent+[patch(STACK+499*725+4, 1, "B")]
    add("native-last-stack-other-1250", other_cargo)
    add("native-last-stack-owner1-minus1", other_cargo, 1)
    add("native-query-minus1", other_cargo, -1)
    add("native-query-256", other_cargo, 256)

    for player in range(6):
        add(f"empty-player-{player}", player=player)
        for owner, kind in ((player,1), (player,2), ((player+1)%6,2)):
            add(f"owner-{owner}-kind-{kind}-query-{player}",
                building(99, owner=owner, kind=kind), player)
        for kind in (-128, -1, 4, 127):
            add(f"signed-kind-{kind}-query-{player}", building(owner=player, kind=kind), player)
        for valid in (-32768, -1, 0, 32767):
            add(f"valid-{valid}-query-{player}", building(owner=player, valid=valid), player)
        for index in (0, 1, 98, 99, 100):
            add(f"building-index-{index}-query-{player}", building(index, owner=player), player)
        for value in (0, 127, 128, 255):
            for unit_type in (30, 31, 32, 33):
                add(f"cargo-p{player}-type{unit_type}-v{value}",
                    cargo(499, player, [(0,0,0), (9,unit_type,value)]), player)
        all_buildings = []
        for index in range(100):
            all_buildings += building(index, owner=player, kind=1+index%2,
                                      pop=index, gold=1000+7*index, flags=index%32)
        add(f"all100-buildings-player{player}", all_buildings, player)
    for mask in range(32):
        add(f"building-addons-{mask}", building(flags=mask), operation=1)
    for population in (0, 1, 4095, 4096, 32768, 65535):
        for gold in (-1, 999):
            add(f"building-pop{population}-gold{gold}", building(pop=population, gold=gold), operation=1)
    for licence in range(40):
        add(f"building-licence-{licence}", building(licences=[licence]+[-1]*11), operation=1)
    add("building-all12-licences", building(licences=list(range(12))), operation=1)
    return cases


def encode_cases(cases):
    data = bytearray(struct.pack("<I", len(cases)))
    for (_, operation, argument, patches), expected in zip(cases, ORIGINAL_RESULTS):
        data.extend(struct.pack("<iiii", operation, argument, expected, len(patches)))
        for offset, raw in patches:
            data.extend(struct.pack("<II", offset, len(raw)))
            data.extend(raw)
    return data


HARNESS = r'''
#include "recovered_layout.h"
#include "buildings/buildings_api.h"
#include "buildings/buildings_shared_state.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int gameData;
@METADATA@
@BUILDING@
@NATION@

alignas(16) static unsigned char memory[GAMEDATA_SAVE_IMAGE_BYTES];
static unsigned char before[sizeof memory];
static unsigned char metadata_before[sizeof g_UnitTypeRuntimeCoreMetadata];
static unsigned int case_index;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "nation-score case=%u: %s\n", case_index, message);
  std::exit(1);
}

static void read_exact(void *destination, size_t bytes) {
  if (std::fread(destination, 1, bytes, stdin) != bytes) fail("incomplete fixture");
}

static void blank_image() {
  // Same neutral input bytes used for the original PE measurements.
  std::memset(memory, 0, sizeof memory);
  for (unsigned int index = 0; index < 500; ++index) {
    const unsigned int base = 147174 + 725 * index;
    memory[base+4] = 255;
    memory[base+6] = memory[base+7] = 255;
  }
  for (unsigned int index = 0; index < 100; ++index) {
    const unsigned int base = BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * index;
    memory[base+2] = 255;
    memory[base+16] = memory[base+17] = 255;
    std::memset(memory+base+402, 255, 12);
  }
}

int main() {
  if ((uintptr_t)memory + sizeof memory > INT_MAX) fail("gameData is not signed low32");
  const int base = (int)(intptr_t)memory;
  gameData = base;
  std::memcpy(metadata_before, g_UnitTypeRuntimeCoreMetadata, sizeof metadata_before);
  unsigned int count;
  read_exact(&count, sizeof count);
  if (count == 0 || count > 10000) fail("invalid case count");
  for (case_index = 0; case_index < count; ++case_index) {
    // operation=0: nation score for argument player; operation=1: building
    // value for argument index. Golden return was measured in original code.
    int descriptor[4];
    read_exact(descriptor, sizeof descriptor);
    blank_image();
    if (descriptor[3] < 0 || descriptor[3] > 10000) fail("invalid patch count");
    for (int patch = 0; patch < descriptor[3]; ++patch) {
      unsigned int location[2];
      read_exact(location, sizeof location);
      if (location[1] > sizeof memory || location[0] > sizeof memory - location[1])
        fail("fixture patch outside game image");
      read_exact(memory + location[0], location[1]);
    }
    std::memcpy(before, memory, sizeof before);
    int actual;
    if (descriptor[0] == 0) {
      actual = AI_TickNationPostTurn(descriptor[1]);
    } else if (descriptor[0] == 1 && descriptor[1] >= 0 && descriptor[1] < 100) {
      actual = Building_GetTotalValue(base + BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * descriptor[1]);
    } else {
      fail("invalid fixture operation");
    }
    if (actual != descriptor[2]) {
      std::fprintf(stderr, "actual=%d expected=%d\n", actual, descriptor[2]);
      fail("original return mismatch");
    }
    if (std::memcmp(memory, before, sizeof memory)) fail("gameData mutated");
    if (std::memcmp(g_UnitTypeRuntimeCoreMetadata, metadata_before, sizeof metadata_before))
      fail("runtime metadata mutated");
    if (gameData != base) fail("gameData pointer changed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing fixture bytes");
  std::printf("nation-score cases=%u\n", count);
}
'''


class NationScoreTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        cases = fixture_cases()
        self.assertEqual(len(cases), len(ORIGINAL_RESULTS))
        self.assertEqual(len({case[0] for case in cases}), len(cases))
        source = HARNESS
        canonical = SOURCE.read_text()
        for placeholder, name in (("BUILDING", "Building_GetTotalValue"), ("NATION", "AI_TickNationPostTurn")):
            match = re.search(r"^int\s+" + name + r"\([^\n]*\)\n\{.*?^\}", canonical, re.M | re.S)
            self.assertIsNotNone(match, "actual canonical definition missing: " + name)
            source = source.replace("@" + placeholder + "@", match.group())
        table = re.search(r"^const UnitTypeRuntimeCoreMetadataRecord g_UnitTypeRuntimeCoreMetadata\[[^\]]+\] =\n\{.*?^\};",
                          STATE.read_text(), re.M | re.S)
        self.assertIsNotNone(table, "actual canonical runtime metadata missing")
        source = source.replace("@METADATA@", table.group())
        with tempfile.TemporaryDirectory(prefix="clash95-nation-test-") as temporary:
            directory = Path(temporary)
            path = directory / "nation.cpp"
            path.write_text(source)
            inputs = directory / "cases.bin"
            inputs.write_bytes(encode_cases(cases))
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("nation-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               # The canonical DWORD reads are packed and unaligned.
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(REPO / "src"), str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    with inputs.open("rb") as stdin:
                        run = subprocess.run([str(executable)], stdin=stdin, capture_output=True,
                                             text=True, timeout=30)
                    failed = re.search(r"case=(\d+)", run.stderr)
                    name = cases[int(failed[1])][0] if failed and int(failed[1]) < len(cases) else "unknown"
                    self.assertEqual(run.returncode, 0, name + ": " + run.stdout + run.stderr)
                    self.assertEqual(run.stdout, f"nation-score cases={len(cases)}\n")
                    self.assertEqual(run.stderr, "")

    def test_gcc_actual_nation_and_building_values(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_actual_nation_and_building_values(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
