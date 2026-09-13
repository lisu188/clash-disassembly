#!/usr/bin/env python3
"""Original-measured queued-path bridge-query traces using the actual native body.

The sole callee is a recording/mutation boundary. Its original result range
is 0/5; other scripted returns are explicitly conditional normalization cases.
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
FUNCTION = "Rules_IsQueuedPathTargetBridgeCrossing"
CALLS = ("bridge_cost",)
MUTABLE_FIELDS = ("arena", "selected") + tuple(
    f"{axis}{arena}_{slot}" for arena in range(2) for slot in range(4)
    for axis in ("row", "column")) + tuple(
    f"{field}{arena}_{slot}" for field in ("count", "probe", "other")
    for arena in range(2) for slot in range(4))
STATE_FIELDS = MUTABLE_FIELDS + tuple(f"path_hash{arena}_{slot}" for arena in range(2) for slot in range(4))
INPUT_FIELDS = ("unit", "probe_index", "path_seed", "event_count")
EVENT_WORDS = 1 + 2 + len(STATE_FIELDS)
FINAL_WORDS = 1 + len(STATE_FIELDS) + 2
ARENA_BYTES = 150200
MAX_EVENTS = 1


def event(result, **mutations):
    return dict(call="bridge_cost", result=result & 0xFFFFFFFF,
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

    def add(name, count, result=0, initial=None, mutations=None, pattern=0,
            unit=None, arena=0, raw_count=None):
        unit = pattern % 4 if unit is None else unit
        state = default_state(count)
        state.update(arena=arena)
        state[f"count{arena}_{unit}"] = count if raw_count is None else raw_count
        state[f"probe{arena}_{unit}"] = ((0x8000 + pattern) << 16) | (((40 + pattern) & 255) << 8) | ((30 + pattern * 3) & 255)
        state.update(initial or {})
        events = [event(result, **(mutations or {}))] if count or raw_count else []
        records.append(dict(name=name, conditional_return=bool(events and result not in (0, 5)),
                            raw_count_case=raw_count is not None,
                            header=[unit, max(0, count - 1), 17 + pattern, len(events)],
                            initial={key: value & 0xFFFFFFFF for key, value in state.items()}, events=events))

    for count in range(101):
        for result in ((0,) if count == 0 else (0, 5)):
            add(f"capacity-count-{count}-result-{result}", count, result,
                pattern=count % 8, arena=count % 2)
    for arena in range(2):
        for unit in range(4):
            add(f"empty-arena-{arena}-unit-{unit}", 0, arena=arena, unit=unit, pattern=arena * 4 + unit)
    for pattern, (row, column) in enumerate(((0, 0), (0, 255), (255, 0), (127, 128),
                                            (128, 127), (255, 255), (1, 254), (254, 1))):
        for cost in (0, 0xFFFF):
            unit = pattern % 4
            add(f"waypoint-bytes-{row}-{column}-cost-{cost}", (1, 2, 99, 100)[pattern % 4],
                (0, 5)[pattern % 2], pattern=pattern, unit=unit,
                initial={f"probe0_{unit}": row | column << 8 | cost << 16,
                         f"row0_{unit}": -32768 if pattern % 2 else 32767,
                         f"column0_{unit}": 32767 if pattern % 2 else -32768})
    for high in (1, 2, 3):
        for low in (0, 1, 2, 99, 100, 101, 102):
            raw = high * 0x40000000 + low
            for result in (0, 5):
                add(f"raw-count-period-{raw:08x}-result-{result}", max(1, min(low, 100)), result,
                    raw_count=raw, unit=3, arena=high % 2, pattern=high + low % 4)
    for raw in (101, 102, 0xFFFFFFFF):
        for result in (0, 5):
            add(f"raw-count-adjacent-{raw:08x}-result-{result}", 100, result,
                raw_count=raw, unit=3, arena=1, pattern=7)
    for pattern, result in enumerate((1, 2, -1, 0x7FFFFFFF, 0x80000000, 0x12345678)):
        add(f"conditional-return-{result & 0xFFFFFFFF:08x}", 100, result, pattern=pattern)
    for pattern, (result, late_count) in enumerate(((0, 99), (5, 0), (5, 100), (0x80000000, 1))):
        add(f"live-callee-state-result-{result & 0xFFFFFFFF:08x}-count-{late_count}", 100, result,
            unit=1, pattern=pattern,
            mutations={"arena": 1, "selected": 3, "row0_1": -32768, "column0_1": 32767,
                       "row1_1": 32767, "column1_1": -32768, "count0_1": 2,
                       "count1_1": late_count, "probe0_1": 0xFEDCFF00,
                       "probe1_1": 0x89AB007F, "other1_1": 0x12345678})
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
static_assert(STATE_WORDS == 50 && INPUT_WORDS == 4);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(offsetof(UnitStackRecord, queued_path) == 316);
static_assert(std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex;
static int expected_game_data, expected_selected;
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
static uint32_t boundary(uint32_t call, uint32_t row, uint32_t column) {
  if (std::memcmp(arenas, expected_final_arenas, sizeof arenas))
    fail("caller changed arena bytes before the callback");
  if (gameData != expected_game_data || g_SelectedUnitIndex != expected_selected)
    fail("caller changed globals before the callback");
  if (event_index >= script.size() || script[event_index].call != call) {
    std::fprintf(stderr, "actual call=%u expected=%u\n", call,
                 event_index < script.size() ? script[event_index].call : 0);
    fail("unexpected callee order");
  }
  output.insert(output.end(), {call, row, column});
  snapshot();
  const Event &item = script[event_index++];
  for (const Mutation &mutation : item.mutations) set_state(mutation.field, mutation.value);
  std::memcpy(expected_final_arenas, arenas, sizeof arenas);
  expected_game_data = gameData; expected_selected = g_SelectedUnitIndex;
  return item.result;
}
static signed int Map_GetBridgeCrossingCostOrZero(int row, int column) {
  return (int32_t)boundary(C_BRIDGE_COST, row, column);
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
    if (input[IN_UNIT] > 3 || input[IN_PROBE_INDEX] > 99 || input[IN_EVENT_COUNT] > 1)
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
    expected_game_data = gameData; expected_selected = g_SelectedUnitIndex;
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
    const int result = Rules_IsQueuedPathTargetBridgeCrossing((int32_t)input[IN_UNIT]);
    if (event_index != script.size()) fail("missing callback boundary");
    if (std::memcmp(arenas, expected_final_arenas, sizeof arenas))
      fail("caller changed arena bytes after initialization or the callback");
    if (gameData != expected_game_data || g_SelectedUnitIndex != expected_selected)
      fail("caller changed globals after initialization or the callback");
    output.push_back((uint32_t)result); snapshot();
    output.push_back(hash_bytes(arenas[0], sizeof arenas[0]));
    output.push_back(hash_bytes(arenas[1], sizeof arenas[1]));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input bytes");
}
'''


class QueuedPathBridgeQueryTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "queued-path-bridge-query-provenance.json").read_text())
        self.assertEqual(provenance["input_fields"], list(INPUT_FIELDS))
        self.assertEqual(provenance["state_fields"], list(STATE_FIELDS))
        self.assertEqual(provenance["calls"], list(CALLS))
        self.assertEqual(provenance["event_words"], EVENT_WORDS)
        self.assertEqual(provenance["final_words"], FINAL_WORDS)
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-bridge-query-") as temporary:
            directory = Path(temporary)
            source = directory / "bridge_query.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("bridge-query-" + optimization[1:])
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

    def test_gcc_original_queued_path_bridge_query_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_queued_path_bridge_query_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
