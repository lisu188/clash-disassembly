#!/usr/bin/env python3
"""Original-measured one-tile movement traces using the actual native body.

Scripted boundaries observe caller behavior; they do not simulate gameplay.
The original overlapping neighbor windows have an explicit common projection.
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
FUNCTION = "UnitStack_MoveOneTileInDirection"
STATE_SOURCE = builder_road.REPO / "src/state/00000000_0054FFFF_recovered_state.cpp"
CALLS = ("path", "free", "execute", "panel")
MUTABLE_FIELDS = ("arena", "selected") + tuple(
    f"{axis}{arena}_{slot}" for arena in range(2) for slot in range(4)
    for axis in ("row", "column")) + tuple(f"neighbor{index}" for index in range(64))
STATE_FIELDS = MUTABLE_FIELDS + tuple(f"path_hash{arena}_{slot}" for arena in range(2) for slot in range(4))
INPUT_FIELDS = ("unit", "direction", "a3_low", "a3_high", "path_seed", "event_count")
EVENT_WORDS = 1 + 6 + len(STATE_FIELDS)
FINAL_WORDS = 1 + len(STATE_FIELDS) + 3
ARENA_BYTES = 150200
MAX_EVENTS = 4
NEIGHBORS = (0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1,
             -1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 1, 0, 1, -1, 1, 0,
             1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, -1, 1, 0, 1,
             -1, 1, -1, 0, -1, 1, -1, 0, -1, -1, -1, 0, -1, -1, 0, -1)


def event(call, result=0, **mutations):
    return dict(call=call, result=result & 0xFFFFFFFF,
                mutations={key: value & 0xFFFFFFFF for key, value in mutations.items()})


def default_state():
    state = dict(arena=0, selected=0x12345678)
    for arena in range(2):
        for slot in range(4):
            state[f"row{arena}_{slot}"] = 30 + arena * 4 + slot
            state[f"column{arena}_{slot}"] = 40 + arena * 4 + slot
    state.update({f"neighbor{index}": value for index, value in enumerate(NEIGHBORS)})
    return state


def cases():
    records = []
    finite_bits = (0, 0x8000000000000000, 0x3FF8000000000000, 0xC002000000000000,
                   1, 0x0010000000000000, 0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF)

    def add(name, direction, path, initial=None, events=None, pattern=0, unit=None):
        state = default_state()
        state.update(initial or {})
        if events is None:
            events = [event("path", path)]
            if path:
                events += [event("free", 0x80000000), event("execute", 0xFFFFFFFF), event("panel", 0xDEADBEEF)]
        bits = finite_bits[pattern % 8]
        header = [pattern % 4 if unit is None else unit, direction,
                  bits & 0xFFFFFFFF, bits >> 32, 17 + pattern, len(events)]
        records.append(dict(name=name, header=[value & 0xFFFFFFFF for value in header],
                            initial={key: value & 0xFFFFFFFF for key, value in state.items()}, events=events))

    for direction in range(32):
        for arena in range(2):
            for path in (0, 1):
                add(f"backed-direction-{direction}-arena-{arena}-path-{path}", direction, path,
                    {"arena": arena}, pattern=(direction + arena + path) % 8)
    # Distinct coefficients discriminate DX/DY, the stride-two lookup and
    # accidental reuse of the first eight semantic directions.
    distinct = {f"neighbor{index}": (index + 1) * (-17 if index % 2 else 31) for index in range(64)}
    for direction in range(32):
        add(f"distinct-neighbor-window-{direction}", direction, 1, distinct, pattern=direction % 8)
    for pattern, column in enumerate((0, 127, 128, 255, -1, -129, -32768, 32767)):
        for row in (-32768, 32767):
            for path in (0, 1):
                add(f"signed-coordinates-row-{row}-column-{column}-path-{path}", pattern, path,
                    {f"row0_{pattern % 4}": row, f"column0_{pattern % 4}": column}, pattern=pattern)
    for axis in ("row", "column"):
        for coordinate, coefficient in ((1, 0x7FFFFFFF), (-1, 0x80000000),
                                        (32767, 0x7FFFFFFF), (-32768, 0x80000000),
                                        (0, 0x80000000), (0, 0x7FFFFFFF),
                                        (-32768, 0x7FFFFFFF), (32767, 0x80000000)):
            for path in (0, 1):
                add(f"wrapping-{axis}-{coordinate}-{coefficient:08x}-path-{path}", 31, path,
                    {f"{axis}0_2": coordinate, f"neighbor{62 if axis == 'row' else 63}": coefficient},
                    pattern=6, unit=2)
    for call_index, call in enumerate(CALLS):
        events = [event("path", 1), event("free", 0xFFFFFFFF), event("execute", 0x80000000), event("panel", 0x12345678)]
        events[call_index]["mutations"] = {"arena": 1, "selected": 3,
                                             "row0_1": 0xFFFF8000, "column0_1": 0xFFFF8001,
                                             "row1_1": 32767, "column1_1": 128,
                                             "neighbor62": 0x7FFFFFFF, "neighbor63": 0x80000000}
        add(f"live-state-at-{call}", 31, 1, events=events, pattern=3, unit=1)
    chain = [event("path", 1, arena=1, selected=3, row1_2=-32768, column1_2=128,
                   neighbor4=0x7FFFFFFF, neighbor5=0x80000000),
             event("free", 0xFFFFFFFF, arena=0, selected=0, row0_2=32767, column0_2=255),
             event("execute", 0x80000000, arena=1, selected=1, row1_2=0, column1_2=-1),
             event("panel", 0xDEADBEEF, arena=0, selected=0x80000000, row0_2=-1, column0_2=-129)]
    add("live-state-at-every-boundary", 2, 1, events=chain, pattern=7, unit=2)
    add("null-path-retains-callee-mutations", 0, 0,
        events=[event("path", 0, arena=1, selected=0xFFFFFFFF, row1_0=-32768, column1_0=32767)])
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


def neighbor_initializers():
    text = STATE_SOURCE.read_text()
    declarations = []
    for name, length in (("DX", 64), ("DY", 63)):
        match = re.search(rf"(?ms)^int Map_Neighbor{name}\[{length}\] =\s*\{{.*?^\}};", text)
        if match is None:
            raise AssertionError("missing actual neighbor initializer: " + name)
        declarations.append(match.group())
    return "\n".join(declarations)


def harness_source(body=None):
    if body is None:
        body = builder_road.extract(SOURCE, FUNCTION)
    return (HARNESS.replace("@STATE_ENUM@", ", ".join("S_" + field.upper() for field in STATE_FIELDS))
            .replace("@INPUT_ENUM@", ", ".join("IN_" + field.upper() for field in INPUT_FIELDS))
            .replace("@CALL_ENUM@", ", ".join("C_" + call.upper() for call in CALLS))
            .replace("@NEIGHBORS@", neighbor_initializers()).replace("@BODY@", body))


def compile_command(compiler, optimization, source, executable):
    return [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
            "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
            "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
            "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
            "-isystem", str(builder_road.REPO / "src"), str(source), "-o", str(executable)]


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
static_assert(STATE_WORDS == 90 && INPUT_WORDS == 6);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(offsetof(UnitStackRecord, queued_path) == 316);
static_assert(std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex;
@NEIGHBORS@
alignas(16) static unsigned char arenas[2][150200];
alignas(16) static unsigned char expected_copy_arenas[2][150200];
alignas(4) static unsigned char path_data[404];
static uint32_t expected_neighbors[64];
static uint32_t input[INPUT_WORDS];
static unsigned int case_index, event_index, copy_checks;
static bool returned_path;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> mutations; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u event=%u: %s\n", case_index, event_index, message);
  std::exit(1);
}
static uint32_t hash_bytes(const void *address, size_t bytes) {
  const unsigned char *data = (const unsigned char *)address;
  uint32_t value = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) value = (value ^ data[index]) * 16777619u;
  return value;
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
  if (field >= S_NEIGHBOR0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_NEIGHBOR0;
    return index % 2 ? Map_NeighborDY[index - 1] : Map_NeighborDX[index];
  }
  if (field >= S_ROW0_0 && field < S_NEIGHBOR0) {
    const uint32_t index = field - S_ROW0_0;
    int16_t value;
    std::memcpy(&value, arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, 2);
    return (uint32_t)(int32_t)value;
  }
  if (field == S_ARENA) return current_arena();
  if (field == S_SELECTED) return g_SelectedUnitIndex;
  fail("invalid state field");
}
static void set_state(uint32_t field, uint32_t value) {
  if (field >= S_NEIGHBOR0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_NEIGHBOR0;
    Map_NeighborDX[index] = (int32_t)value;
    if (index) Map_NeighborDY[index - 1] = (int32_t)value;
    expected_neighbors[index] = value;
    return;
  }
  if (field >= S_ROW0_0 && field < S_NEIGHBOR0) {
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
  fail("invalid mutation field");
}
static void snapshot() {
  // The common trace uses the 64-word original projection. Independently check
  // every element of both native arrays, including the unused odd elements.
  for (unsigned int index = 0; index < 64; ++index) {
    if ((uint32_t)Map_NeighborDX[index] != expected_neighbors[index]
        || (index && (uint32_t)Map_NeighborDY[index - 1] != expected_neighbors[index]))
      fail("native neighbor array changed outside scripted projection");
  }
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
    fail("caller did not copy exactly 404 bytes to the fresh game-state destination before free boundary");
  return (int32_t)boundary(C_FREE);
}
static void UnitStack_ExecuteQueuedPath(unsigned int unit, int animate, char column, DWORD carried, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  boundary(C_EXECUTE, unit, animate, (uint8_t)column, carried, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static void *WorldMap_RefreshUnitStatusPanel(DWORD carried) {
  return (void *)(uintptr_t)boundary(C_PANEL, carried);
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
  for (unsigned int index = 0; index < 63; ++index)
    if (Map_NeighborDX[index + 1] != Map_NeighborDY[index]) fail("actual initializer overlap differs");
  const unsigned int count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    for (uint32_t &word : input) word = read_input();
    if (input[IN_UNIT] > 3 || input[IN_DIRECTION] > 31 || input[IN_EVENT_COUNT] > 4 || !input[IN_EVENT_COUNT])
      fail("invalid backed header");
    std::memset(arenas, 0x5A, sizeof arenas);
    for (size_t index = 0; index < sizeof path_data; ++index)
      path_data[index] = (unsigned char)(input[IN_PATH_SEED] + index * 37);
    for (uint32_t field = 0; field < S_PATH_HASH0_0; ++field) {
      const uint32_t value = read_input();
      if (!case_index && field >= S_NEIGHBOR0 && get_state(field) != value)
        fail("actual native neighbor initializer differs from original case0");
      set_state(field, value);
    }
    script.clear(); output.clear(); event_index = copy_checks = 0; returned_path = false;
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
    const uint64_t bits = (uint64_t)input[IN_A3_LOW] | ((uint64_t)input[IN_A3_HIGH] << 32);
    const int result = UnitStack_MoveOneTileInDirection((int32_t)input[IN_UNIT],
                            (int32_t)input[IN_DIRECTION], std::bit_cast<double>(bits));
    if (event_index != script.size() || copy_checks != (unsigned)returned_path)
      fail("missing boundary or copy check");
    output.push_back((uint32_t)result); snapshot();
    output.push_back(hash_bytes(arenas[0], sizeof arenas[0]));
    output.push_back(hash_bytes(arenas[1], sizeof arenas[1]));
    output.push_back(hash_bytes(path_data, sizeof path_data));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input bytes");
}
'''


class OneTileMovementTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "one-tile-movement-provenance.json").read_text())
        self.assertEqual(provenance["input_fields"], list(INPUT_FIELDS))
        self.assertEqual(provenance["state_fields"], list(STATE_FIELDS))
        self.assertEqual(provenance["calls"], list(CALLS))
        self.assertEqual(provenance["event_words"], EVENT_WORDS)
        self.assertEqual(provenance["final_words"], FINAL_WORDS)
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-one-tile-") as temporary:
            directory = Path(temporary)
            source = directory / "one_tile.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("one-tile-" + optimization[1:])
                    command = compile_command(compiler, optimization, source, executable)
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    self.assertEqual(built.stderr, "")
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    for case, observed, expected in zip(records, split_output(run.stdout, records),
                                                       provenance["case_trace_sha256"], strict=True):
                        self.assertEqual(hashlib.sha256(observed).hexdigest(), expected,
                                         case["name"] + ": original boundary/state trace or memory fingerprint differs")
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_one_tile_movement_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_one_tile_movement_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
