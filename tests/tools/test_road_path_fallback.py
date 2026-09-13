#!/usr/bin/env python3
"""Original-measured Road/path fallback traces using the actual native body.

Five scripted callee boundaries observe caller behavior, not gameplay.
Raw non-Direction8 Facing results are explicitly conditional boundary cases.
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

SOURCE = builder_road.REPO / "src/strategic/00453110_00455720_strategic_002.cpp"
FUNCTION = "Rules_BuildRoadOrStepTowardQueuedPath"
CALLS = ("facing", "owner", "bridge", "road", "move")
MUTABLE_FIELDS = ("arena", "selected") + tuple(
    f"{axis}{arena}_{slot}" for arena in range(2) for slot in range(4)
    for axis in ("row", "column")) + tuple(
    f"{field}{arena}_{slot}" for field in ("count", "probe", "other")
    for arena in range(2) for slot in range(4))
STATE_FIELDS = MUTABLE_FIELDS + tuple(f"path_hash{arena}_{slot}" for arena in range(2) for slot in range(4))
INPUT_FIELDS = ("unit", "a2", "a3_low", "a3_high", "probe_index", "path_seed", "event_count")
EVENT_WORDS = 1 + 6 + len(STATE_FIELDS)
FINAL_WORDS = 1 + len(STATE_FIELDS) + 2
ARENA_BYTES = 150200
MAX_EVENTS = 7


def event(call, result=0, **mutations):
    return dict(call=call, result=result & 0xFFFFFFFF,
                mutations={key: value & 0xFFFFFFFF for key, value in mutations.items()})


def default_state(count):
    state = dict(arena=0, selected=0x12345678)
    for arena in range(2):
        for slot in range(4):
            state[f"row{arena}_{slot}"] = 30 + arena * 4 + slot
            state[f"column{arena}_{slot}"] = 40 + arena * 4 + slot
            state[f"count{arena}_{slot}"] = max(1, count)
            state[f"probe{arena}_{slot}"] = 0x80A5281E + arena * 257 + slot * 259
            state[f"other{arena}_{slot}"] = 0xFEDCBA98 - arena * 257 - slot * 259
    return state


def cases():
    records = []
    finite_bits = (0, 0x8000000000000000, 0x3FF8000000000000, 0xC002000000000000,
                   1, 0x0010000000000000, 0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF)
    neighbor = ((0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1))
    attempts = {1: (0, 2), 3: (4, 2), 5: (4, 6), 7: (0, 6)}

    def script(direction, mode, outcomes, truth=1):
        prefix = [event("facing", direction), event("owner", 0 if mode == "unowned" else truth)]
        if mode != "unowned":
            prefix.append(event("bridge", 0 if mode == "movement" else truth))
        calls = [call for _ in attempts.get(direction, (direction,))
                 for call in (("move",) if mode == "movement" else ("road", "move"))]
        if len(outcomes) > len(calls):
            raise AssertionError("too many scripted outcomes")
        return prefix + [event(call, truth if result else 0) for call, result in zip(calls, outcomes)]

    def add(name, count, direction=0, mode="unowned", outcomes=None, initial=None,
            events=None, pattern=0, unit=None, arena=0, conditional=False):
        unit = pattern % 4 if unit is None else unit
        state = default_state(count)
        state.update(arena=arena)
        state[f"row{arena}_{unit}"] = 30
        state[f"column{arena}_{unit}"] = 40
        state[f"count{arena}_{unit}"] = count
        row_delta, column_delta = neighbor[direction] if 0 <= direction < 8 else (1, 1)
        state[f"probe{arena}_{unit}"] = ((0x8000 + pattern) << 16) | ((40 + column_delta) << 8) | (30 + row_delta)
        state.update(initial or {})
        if events is None:
            if not count:
                events = []
            else:
                maximum = len(attempts.get(direction, (direction,))) * (1 if mode == "movement" else 2)
                events = script(direction, mode, [0] * maximum if outcomes is None else outcomes,
                                (1, 0xFFFFFFFF, 0x80000000)[pattern % 3])
        bits = finite_bits[pattern % 8]
        a2 = (0, 1, 0xFFFFFFFF, 0x80000000, 0x12345678, 0x55555555, 0xAAAAAAAA, 0x7FFFFFFF)[pattern % 8]
        header = [unit, a2, bits & 0xFFFFFFFF, bits >> 32, max(0, count - 1), 17 + pattern, len(events)]
        records.append(dict(name=name, conditional_direction=conditional,
                            header=[value & 0xFFFFFFFF for value in header],
                            initial={key: value & 0xFFFFFFFF for key, value in state.items()}, events=events))

    for count in range(101):
        add(f"capacity-count-{count}", count, direction=count % 8,
            mode=("unowned", "movement", "bridge")[count % 3], pattern=count % 8, arena=count % 2)
    for arena in range(2):
        for unit in range(4):
            add(f"empty-arena-{arena}-unit-{unit}", 0, arena=arena, unit=unit, pattern=arena * 4 + unit)
    for direction in range(8):
        for mode in ("unowned", "movement", "bridge"):
            maximum = len(attempts.get(direction, (direction,))) * (1 if mode == "movement" else 2)
            for success in range(maximum + 1):
                outcomes = [0] * success + ([1] if success < maximum else [])
                add(f"direction-{direction}-{mode}-first-success-{success}", (1, 2, 99, 100)[success % 4],
                    direction, mode, outcomes, pattern=(direction + success) % 8)
    # Coordinate width cases choose a real Facing output consistent with the
    # observed signs; no alternate Facing implementation is compiled here.
    def facing(row, column):
        return (7 if column < 0 else 5 if column > 0 else 6) if row < 0 else (
            (1 if column < 0 else 3 if column > 0 else 2) if row > 0 else (0 if column < 0 else 4))
    for pattern, (row, column, target_row, target_column) in enumerate(
            ((-32768, -32768, 255, 255), (32767, 32767, 0, 0),
             (-32768, 32767, 128, 127), (32767, -32768, 127, 128),
             (0, 0, 0, 0), (127, 128, 127, 128), (255, 255, 255, 0), (-1, -129, 0, 255))):
        for cost in (0, 0xFFFF):
            unit = pattern % 4
            add(f"coordinate-width-{pattern}-cost-{cost}", (1, 2, 99, 100)[pattern % 4],
                facing(target_row - row, target_column - column), pattern=pattern, unit=unit,
                initial={f"row0_{unit}": row, f"column0_{unit}": column,
                         f"probe0_{unit}": target_row | (target_column << 8) | (cost << 16)})
    for direction in (8, 128, 255, 256, -1, -2147483648, 2147483647):
        for mode in ("movement", "bridge"):
            add(f"conditional-facing-{direction & 0xFFFFFFFF:08x}-{mode}", 100,
                direction, mode, pattern=7, conditional=True)
    # Every invocation in the longest chain gets an independent mutation case,
    # followed by one chain changing the live state at every boundary.
    for boundary_index in range(7):
        events = script(3, "bridge", [0, 0, 0, 0], 0x80000000)
        events[boundary_index]["mutations"] = {
            "arena": 1, "selected": 3, "row1_1": 32767, "column1_1": 0xFFFF8000,
            "count0_1": 2, "count1_1": 99, "probe0_1": 0xFEDCFF00,
            "probe1_1": 0x89AB007F, "other1_1": 0x12345678}
        add(f"live-state-at-boundary-{boundary_index}-{events[boundary_index]['call']}", 100,
            3, events=events, unit=1, pattern=3)
    events = script(7, "bridge", [0, 0, 0, 0], 0xFFFFFFFF)
    for index, item in enumerate(events):
        arena = (index + 1) % 2
        item["mutations"] = {"arena": arena, "selected": (index + 1) % 4,
                             f"row{arena}_2": (-32768 if index % 2 else 32767) & 0xFFFFFFFF,
                             f"column{arena}_2": index + 127, f"count{arena}_2": (0, 1, 2, 99, 100, 7, 88)[index],
                             f"probe{arena}_2": (0xFFFF0000 | index << 8 | (255 - index)),
                             f"other{arena}_2": 0x01234567 + index}
    add("live-state-at-every-boundary", 99, 7, events=events, unit=2, pattern=6)
    # Preserve all original 231 encoded cases above. These additional cases
    # have backed raw addresses despite exceeding typed waypoint capacity.
    for high in (1, 2, 3):
        for low in (0, 1, 2, 99, 100, 101, 102):
            raw = high * 0x40000000 + low
            arena = high % 2
            direction = 7 if low == 0 else 3 if low > 100 else low % 8
            add(f"raw-count-period-{raw:08x}", max(1, min(low, 100)), direction,
                "bridge", initial={f"count{arena}_3": raw}, pattern=high + low % 4,
                arena=arena, unit=3)
            records[-1]["raw_count_case"] = True
    for raw in (101, 102, 0xFFFFFFFF):
        add(f"raw-count-adjacent-{raw:08x}", 100, 3, "bridge",
            initial={"count1_3": raw}, pattern=7, arena=1, unit=3)
        records[-1]["raw_count_case"] = True
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
static_assert(STATE_WORDS == 50 && INPUT_WORDS == 7);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(offsetof(UnitStackRecord, queued_path) == 316);
static_assert(std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex;
alignas(16) static unsigned char arenas[2][150200];
alignas(16) static unsigned char expected_final_arenas[2][150200];
static uint32_t input[INPUT_WORDS];
static unsigned int case_index, event_index;
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
static unsigned char *path_address(uint32_t index) {
  return arenas[index / 4] + UNIT_STACK_TABLE_OFFSET + (index % 4) * UNIT_STACK_STRIDE + UNIT_STACK_PATH_OFFSET;
}
static uint32_t word(const void *address) {
  uint32_t value; std::memcpy(&value, address, 4); return value;
}
static void put_word(void *address, uint32_t value) { std::memcpy(address, &value, 4); }
static uint32_t get_state(uint32_t field) {
  if (field >= S_PATH_HASH0_0 && field < STATE_WORDS)
    return hash_bytes(path_address(field - S_PATH_HASH0_0), UNIT_STACK_PATH_BYTES);
  if (field >= S_COUNT0_0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_COUNT0_0;
    const uint32_t position = index < 8 ? 0 : 4 + 4 * (index < 16 ? input[IN_PROBE_INDEX] : (input[IN_PROBE_INDEX] == 0 ? 1 : 0));
    return word(path_address(index % 8) + position);
  }
  if (field >= S_ROW0_0 && field < S_COUNT0_0) {
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
  if (field >= S_COUNT0_0 && field < S_PATH_HASH0_0) {
    const uint32_t index = field - S_COUNT0_0;
    const uint32_t position = index < 8 ? 0 : 4 + 4 * (index < 16 ? input[IN_PROBE_INDEX] : (input[IN_PROBE_INDEX] == 0 ? 1 : 0));
    put_word(path_address(index % 8) + position, value); return;
  }
  if (field >= S_ROW0_0 && field < S_COUNT0_0) {
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
  std::memcpy(expected_final_arenas, arenas, sizeof arenas);
  return item.result;
}
static signed int Facing_DirectionFromDelta8(int row_delta, int column_delta) {
  return (int32_t)boundary(C_FACING, row_delta, column_delta);
}
static BOOL Map_TileHasOwner(int row, int column) { return (int32_t)boundary(C_OWNER, row, column); }
static signed int Rules_IsQueuedPathTargetBridgeCrossing(int unit) { return (int32_t)boundary(C_BRIDGE, unit); }
static signed int Road_Build(int unit, int direction, char carried_direction, DWORD context, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_ROAD, unit, direction, (uint8_t)carried_direction, context,
                           (uint32_t)bits, (uint32_t)(bits >> 32));
}
static signed int UnitStack_MoveOneTileInDirection(int unit, int direction, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_MOVE, unit, direction, (uint32_t)bits, (uint32_t)(bits >> 32));
}
@BODY@

static uint32_t read_input() {
  uint32_t result;
  if (std::fread(&result, 4, 1, stdin) != 1) fail("incomplete input fixture");
  return result;
}
int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX) fail("fixture storage must fit positive signed low32");
  const unsigned int count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    for (uint32_t &word : input) word = read_input();
    if (input[IN_UNIT] > 3 || input[IN_PROBE_INDEX] > 99 || input[IN_EVENT_COUNT] > 7)
      fail("invalid backed header");
    std::memset(arenas, 0x5A, sizeof arenas);
    for (unsigned int arena = 0; arena < 2; ++arena)
      for (unsigned int slot = 0; slot < 4; ++slot)
        for (unsigned int index = 0; index < UNIT_STACK_PATH_BYTES; ++index)
          path_address(arena * 4 + slot)[index] = (unsigned char)(input[IN_PATH_SEED] + arena * 53 + slot * 29 + index * 37);
    for (uint32_t field = 0; field < S_PATH_HASH0_0; ++field) set_state(field, read_input());
    const uint32_t initial_count = word(path_address(current_arena() * 4 + input[IN_UNIT]));
    if (initial_count) {
      const uint32_t address = (uint32_t)gameData + UNIT_STACK_TABLE_OFFSET
          + input[IN_UNIT] * UNIT_STACK_STRIDE + UNIT_STACK_PATH_OFFSET + initial_count * 4u;
      bool backed = false;
      for (uint32_t arena = 0; arena < 2; ++arena)
        backed |= address >= (uintptr_t)arenas[arena]
            && (uint64_t)address + sizeof(PathWaypoint) <= (uintptr_t)arenas[arena] + sizeof arenas[arena];
      if (!backed) fail("resolved raw waypoint address is outside fixture arena backing");
    }
    std::memcpy(expected_final_arenas, arenas, sizeof arenas);
    script.clear(); output.clear(); event_index = 0;
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
    const int result = Rules_BuildRoadOrStepTowardQueuedPath((int32_t)input[IN_UNIT], input[IN_A2], std::bit_cast<double>(bits));
    if (event_index != script.size()) fail("missing callback boundary");
    if (initial_count)
      put_word(expected_final_arenas[current_arena()] + UNIT_STACK_TABLE_OFFSET
                + input[IN_UNIT] * UNIT_STACK_STRIDE + UNIT_STACK_PATH_OFFSET, 0);
    if (std::memcmp(arenas, expected_final_arenas, sizeof arenas))
      fail("final cleanup differs from exactly four bytes in the fresh arena at the input stack index");
    output.push_back((uint32_t)result); snapshot();
    output.push_back(hash_bytes(arenas[0], sizeof arenas[0]));
    output.push_back(hash_bytes(arenas[1], sizeof arenas[1]));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input bytes");
}
'''


class RoadPathFallbackTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "road-path-fallback-provenance.json").read_text())
        self.assertEqual(provenance["input_fields"], list(INPUT_FIELDS))
        self.assertEqual(provenance["state_fields"], list(STATE_FIELDS))
        self.assertEqual(provenance["calls"], list(CALLS))
        self.assertEqual(provenance["event_words"], EVENT_WORDS)
        self.assertEqual(provenance["final_words"], FINAL_WORDS)
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-road-fallback-") as temporary:
            directory = Path(temporary)
            source = directory / "road_fallback.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("road-fallback-" + optimization[1:])
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

    def test_gcc_original_road_path_fallback_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_road_path_fallback_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
