#!/usr/bin/env python3
"""Original-measured movement-commit caller traces with five exact boundaries."""
from pathlib import Path
import hashlib
import json
import shutil
import struct
import subprocess
import tempfile
import unittest

import test_builder_road as builder_road

SOURCE = builder_road.REPO / 'src/strategic/00453110_00455720_strategic_002.cpp'
FUNCTION = 'Move_CommitIfWithinCost'
STACK_INDICES = (-1, 0, 1, 499, 500, 501)
ARENA_BASES = (0x10000000, 0x7FFE0000)
ARENA_BYTES = 0x90000
CALLS = ('execute', 'bridge', 'road', 'integer', 'put')
ARITIES = (6, 1, 4, 1, 7)
INPUT_FIELDS = ('unit', 'a2', 'a3', 'double_low', 'double_high', 'seed', 'event_count')
MUTABLE_FIELDS = ('arena', 'selected') + tuple(
    f'{field}{arena}_{slot}' for arena in range(2) for slot in range(6)
    for field in ('row', 'column', 'type', 'count', 'instance'))
STATE_FIELDS = MUTABLE_FIELDS + tuple(f'path_hash{arena}_{slot}' for arena in range(2) for slot in range(6))
FINAL_WORDS = 1 + len(STATE_FIELDS) + 2


def unsigned(value):
    return value & 0xFFFFFFFF


def signed(value):
    return (value & 0x7FFFFFFF) - (value & 0x80000000)


def event(call, result=0, **mutations):
    return dict(call=call, result=unsigned(result),
                mutations={name: unsigned(value) for name, value in mutations.items()})


def cases():
    records = []

    def add(name, index=1, arena=0, count=1, first_type=5, bridge=0,
            road_result=0, node=0x12345678, put_result=1, a2=0x89ABCDEF,
            a3=None, double_bits=0x3FF0000000000000, initial=None,
            execute_mut=None, bridge_mut=None, road_mut=None,
            integer_mut=None, put_mut=None):
        unit = unsigned(index)
        slot = STACK_INDICES.index(index)
        state = dict(arena=arena, selected=3)
        for region in range(2):
            for number in range(6):
                for field, value in (('row', 30 + number), ('column', 40 + number),
                                     ('type', 5), ('count', 1),
                                     ('instance', 0x18000000 + region * 0x10000 + number * 0x100)):
                    state[f'{field}{region}_{number}'] = value
        state[f'count{arena}_{slot}'] = unsigned(count)
        state[f'type{arena}_{slot}'] = unsigned(first_type)
        state.update({key: unsigned(value) for key, value in (initial or {}).items()})
        initial_state = state.copy()
        events = []
        domain = {'classification': 'defined', 'first_failing_read': None}
        offset = signed(unsigned(725 * unit))

        def read_before(phase, field_offset, separate_offset=False):
            if domain['classification'] != 'defined':
                return
            base = ARENA_BASES[state['arena']]
            terms = (offset, base, field_offset) if separate_offset else (signed(unsigned(base + offset)), field_offset)
            total = terms[0]
            for term in terms[1:]:
                total += term
                if total < -0x80000000 or total > 0x7FFFFFFF:
                    domain.update(classification='signed-add-overflow', first_failing_read=phase)
                    return
            if total < 0:
                domain.update(classification='sign-extended-native-pointer', first_failing_read=phase)

        def step(call, result, mutations):
            events.append(event(call, result, **(mutations or {})))
            state.update(events[-1]['mutations'])

        if unsigned(count):
            previous = (state[f'row{arena}_{slot}'], state[f'column{arena}_{slot}'])
            read_before('entry-coordinates', 147174)
            step('execute', 0, execute_mut)
            if unit <= 500:
                read_before('post-execute-unit-type', 147180, True)
                if signed(state[f'type{state["arena"]}_{slot}']) in range(41):
                    step('bridge', bridge, bridge_mut)
                    if bridge:
                        step('road', road_result, road_mut)
                    read_before('post-query-coordinates', 147174)
                    current = (state[f'row{state["arena"]}_{slot}'], state[f'column{state["arena"]}_{slot}'])
                    if current == previous:
                        step('integer', node, integer_mut)
                        read_before('post-integer-instance', 147895, True)
                        step('put', put_result, put_mut)
        argument = unit if a3 is None else unsigned(a3)
        records.append(dict(name=name, before_domain=domain,
                            defined_before_argument_mismatch=bool(events and argument != unit and domain['classification'] == 'defined'),
                            conditional_bridge_return=bridge not in (0, 1),
                            conditional_road_return=bool(bridge and road_result not in (0, 1)),
                            header=[unit, unsigned(a2), argument, double_bits & 0xFFFFFFFF,
                                    double_bits >> 32, 17 + len(records) % 29, len(events)],
                            initial=initial_state, events=events))

    for arena in range(2):
        for index in STACK_INDICES:
            add(f'empty-arena-{arena}-index-{index}', index=index, arena=arena, count=0, a3=0xFEDCBA98)
    for index in STACK_INDICES:
        for unit_type in (-32768, -1, 0, 1, 39, 40, 41, 32767):
            add(f'index-{index}-type-{unit_type}', index=index, first_type=unit_type)
    for count in (2, 100, 0x40000000, 0x80000000, 0xFFFFFFFF):
        add(f'raw-nonzero-count-{count:08x}', count=count)
    for result in (0, 1, 2, -1, 0x80000000):
        add(f'bridge-result-{unsigned(result):08x}', bridge=result)
    for result in (0, 1, -1, 0x80000000):
        add(f'road-result-ignored-{unsigned(result):08x}', bridge=1, road_result=result)
        add(f'put-result-ignored-{unsigned(result):08x}', put_result=result)
    for index in (0, 1, 499, 500):
        for a3 in (0x12345678, 0x80000000, 0xFFFFFFFF):
            add(f'opaque-arg-index-{index}-value-{a3:08x}', index=index, a3=a3, bridge=index % 2)
    for a2 in (0, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        add(f'unused-a2-{a2:08x}', a2=a2)
    for bits in (0, 0x8000000000000000, 1, 0x8000000000000001,
                 0x0010000000000000, 0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF):
        add(f'finite-double-{bits:016x}', double_bits=bits, bridge=1)
    for row, column in ((-32768, 32767), (32767, -32768), (0, 0), (128, 255)):
        start = {'row0_2': unsigned(row), 'column0_2': unsigned(column)}
        add(f'coordinates-{row}-{column}-unchanged', initial=start)
        add(f'coordinates-{row}-{column}-row-change', initial=start, execute_mut={'row0_2': row + (1 if row < 32767 else -1)})
        add(f'coordinates-{row}-{column}-column-change', initial=start, execute_mut={'column0_2': column + (1 if column < 32767 else -1)})
    add('move-away-then-road-restores', bridge=1, execute_mut={'row0_2': 90}, road_mut={'row0_2': 32})
    add('execute-clears-count-still-queries', execute_mut={'count0_2': 0})
    add('bridge-clears-count-still-road', bridge=1, bridge_mut={'count0_2': 0, 'type0_2': 0xFFFFFFFF})
    add('road-changes-type-no-recheck', bridge=1, road_mut={'type0_2': 0xFFFFFFFF})
    add('integer-changes-coordinates-no-recheck', integer_mut={'row0_2': 0xFFFF8000, 'column0_2': 32767})
    add('integer-changes-instance-fresh-read', integer_mut={'instance0_2': 0xABCDEF01, 'selected': 500})
    add('put-changes-all-state-no-writeback', bridge=1, put_mut={'arena': 1, 'selected': 501, 'count0_2': 0, 'type0_2': 0xFFFFFFFF, 'row1_2': 65535, 'instance1_2': 0xABCDEF01})
    for index in STACK_INDICES:
        add(f'high-entry-index-{index}', arena=1, index=index)
    add('execute-switches-high-before-type', execute_mut={'arena': 1, 'selected': 500})
    add('execute-switches-high-invalid-type', execute_mut={'arena': 1, 'type1_2': 0xFFFFFFFF})
    add('bridge-switches-high-before-coordinates', bridge_mut={'arena': 1})
    add('road-switches-high-before-coordinates', bridge=1, road_mut={'arena': 1})
    add('integer-switches-high-before-instance', integer_mut={'arena': 1, 'instance1_2': 0xFEDCBA98})
    add('put-switches-high-no-late-read', put_mut={'arena': 1})
    add('out-of-range-execute-switches-high-no-late-read', index=501, execute_mut={'arena': 1})
    for node in (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        add(f'conditional-node-bits-{node:08x}', node=node)
    add('bridge-switches-high-with-row-change', bridge_mut={'arena': 1, 'row1_2': 99})
    add('road-switches-high-with-column-change', bridge=1, road_mut={'arena': 1, 'column1_2': 99})
    return records


def encode_cases(records):
    words = [len(records)]
    for case in records:
        words += case['header'] + [case['initial'][field] for field in MUTABLE_FIELDS]
        for item in case['events']:
            words += [CALLS.index(item['call']) + 1, item['result'], len(item['mutations'])]
            for field, value in item['mutations'].items():
                words += [MUTABLE_FIELDS.index(field), value]
    return struct.pack(f'<{len(words)}I', *words)


def split_output(data, records):
    position = 0
    for case in records:
        words = FINAL_WORDS + sum(1 + ARITIES[CALLS.index(item['call'])] + len(STATE_FIELDS)
                                  for item in case['events'])
        end = position + words * 4
        if end > len(data):
            raise AssertionError('incomplete trace for ' + case['name'])
        yield data[position:end]
        position = end
    if position != len(data):
        raise AssertionError('trailing trace bytes')


def harness_source(body=None):
    if body is None:
        body = builder_road.extract(SOURCE, FUNCTION)
    return (HARNESS.replace('@STATE_ENUM@', ', '.join('S_' + field.upper() for field in STATE_FIELDS))
            .replace('@INPUT_ENUM@', ', '.join('IN_' + field.upper() for field in INPUT_FIELDS))
            .replace('@BODY@', body))


def compile_command(compiler, optimization, source, executable):
    return [compiler, '-std=gnu++20', '-U_GNU_SOURCE', optimization,
            '-fno-exceptions', '-fno-rtti', '-fno-pie', '-no-pie',
            '-Wall', '-Wextra', '-Werror', '-fsanitize=undefined',
            '-fno-sanitize=alignment', '-fsanitize-undefined-trap-on-error',
            '-isystem', str(builder_road.REPO / 'src'), str(source), '-o', str(executable)]


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <sys/mman.h>
#include <vector>

enum StateField { @STATE_ENUM@, STATE_WORDS };
enum InputField { @INPUT_ENUM@, INPUT_WORDS };
static_assert(STATE_WORDS == 74 && INPUT_WORDS == 7);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(offsetof(UnitStackRecord, queued_path) == 316);
static_assert(offsetof(UnitStackRecord, unrecovered_0x2D1_0x2D5) == 721);
static_assert(std::endian::native == std::endian::little);
static constexpr uintptr_t arena_bases[] = {0x10000000, 0x7FFE0000};
static constexpr size_t arena_bytes = 0x90000;
static constexpr int stack_indices[] = {-1, 0, 1, 499, 500, 501};
int gameData, g_SelectedUnitIndex;
static int expected_game_data, expected_selected;
static const char aPa[] = "PA";
static unsigned char expected_arenas[2][arena_bytes];
static uint32_t input[INPUT_WORDS];
static unsigned case_index, event_index;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> mutations; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u event=%u: %s\n", case_index, event_index, message);
  std::exit(1);
}
static unsigned char *arena_address(unsigned arena) { return (unsigned char *)arena_bases[arena]; }
static unsigned char *record_address(unsigned record) {
  return arena_address(record / 6) + 147174 + 725 * stack_indices[record % 6];
}
static uint32_t hash_bytes(const void *address, size_t bytes) {
  const auto *data = (const unsigned char *)address;
  uint32_t hash = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) hash = (hash ^ data[index]) * 16777619u;
  return hash;
}
static uint32_t word(const void *address) { uint32_t value; std::memcpy(&value, address, 4); return value; }
static void put_word(void *address, uint32_t value) { std::memcpy(address, &value, 4); }
static uint32_t current_arena() {
  for (unsigned arena = 0; arena < 2; ++arena)
    if ((uint32_t)gameData == arena_bases[arena]) return arena;
  fail("unknown arena pointer");
}
static uint32_t get_state(unsigned field) {
  if (field == S_ARENA) return current_arena();
  if (field == S_SELECTED) return g_SelectedUnitIndex;
  if (field >= S_PATH_HASH0_0 && field < STATE_WORDS)
    return hash_bytes(record_address(field - S_PATH_HASH0_0) + 316, 404);
  if (field >= S_ROW0_0 && field < S_PATH_HASH0_0) {
    const unsigned record = (field - S_ROW0_0) / 5;
    const unsigned item = (field - S_ROW0_0) % 5;
    static constexpr unsigned offsets[] = {0, 2, 6, 316, 721};
    const unsigned char *address = record_address(record) + offsets[item];
    if (item < 3) { int16_t value; std::memcpy(&value, address, 2); return (uint32_t)(int32_t)value; }
    return word(address);
  }
  fail("invalid state field");
}
static void set_state(unsigned field, uint32_t value) {
  if (field == S_ARENA) { if (value > 1) fail("invalid arena"); gameData = (int32_t)arena_bases[value]; return; }
  if (field == S_SELECTED) { g_SelectedUnitIndex = (int32_t)value; return; }
  if (field >= S_ROW0_0 && field < S_PATH_HASH0_0) {
    const unsigned record = (field - S_ROW0_0) / 5;
    const unsigned item = (field - S_ROW0_0) % 5;
    static constexpr unsigned offsets[] = {0, 2, 6, 316, 721};
    unsigned char *address = record_address(record) + offsets[item];
    if (item < 3) { const uint16_t narrow = (uint16_t)value; std::memcpy(address, &narrow, 2); }
    else put_word(address, value);
    return;
  }
  fail("invalid mutation field");
}
static void remember_state() {
  for (unsigned arena = 0; arena < 2; ++arena) std::memcpy(expected_arenas[arena], arena_address(arena), arena_bytes);
  expected_game_data = gameData; expected_selected = g_SelectedUnitIndex;
}
static void require_unchanged() {
  for (unsigned arena = 0; arena < 2; ++arena)
    if (std::memcmp(expected_arenas[arena], arena_address(arena), arena_bytes)) fail("caller wrote arena bytes");
  if (gameData != expected_game_data || g_SelectedUnitIndex != expected_selected) fail("caller wrote globals");
}
static void snapshot() { for (unsigned field = 0; field < STATE_WORDS; ++field) output.push_back(get_state(field)); }
static uint32_t boundary(uint32_t call, std::initializer_list<uint32_t> args) {
  require_unchanged();
  static constexpr unsigned arities[] = {0, 6, 1, 4, 1, 7};
  if (call > 5 || args.size() != arities[call]) fail("invalid boundary arity");
  if (event_index >= script.size() || script[event_index].call != call) fail("unexpected callback order");
  output.push_back(call); output.insert(output.end(), args.begin(), args.end()); snapshot();
  const Event &event = script[event_index++];
  for (const Mutation &mutation : event.mutations) set_state(mutation.field, mutation.value);
  remember_state();
  return event.result;
}
static void UnitStack_ExecuteQueuedPath(unsigned int index, int animate, char carry, DWORD opaque, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  boundary(1, {index, (uint32_t)animate, (uint8_t)carry, opaque, (uint32_t)bits, (uint32_t)(bits >> 32)});
}
static signed int Rules_IsQueuedPathTargetBridgeCrossing(int index) { return (int32_t)boundary(2, {(uint32_t)index}); }
static signed int Rules_BuildRoadOrStepTowardQueuedPath(int index, DWORD opaque, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(3, {(uint32_t)index, opaque, (uint32_t)bits, (uint32_t)(bits >> 32)});
}
static int Rules_AddIntegerValue(int value) { return (int32_t)boundary(4, {(uint32_t)value}); }
static signed int Rules_PutInstanceSlotValue(int instance, _BYTE *name, int argument, _DWORD *value, double context) {
  const uint32_t key = (uint8_t)name[0] | (uint32_t)(uint8_t)name[1] << 8 | (uint32_t)(uint8_t)name[2] << 16;
  const uint64_t bits = std::bit_cast<uint64_t>(context);
  return (int32_t)boundary(5, {(uint32_t)instance, key, (uint32_t)argument, value[1], value[2], (uint32_t)bits, (uint32_t)(bits >> 32)});
}
@BODY@

static uint32_t read_input() { uint32_t value; if (std::fread(&value, 4, 1, stdin) != 1) fail("incomplete input"); return value; }
int main() {
  for (unsigned arena = 0; arena < 2; ++arena)
    if (mmap(arena_address(arena), arena_bytes, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) != arena_address(arena)) fail("cannot map fixed fixture arena");
  const uint32_t count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    for (uint32_t &item : input) item = read_input();
    bool valid = false;
    for (int index : stack_indices) valid |= input[IN_UNIT] == (uint32_t)index;
    if (!valid || input[IN_EVENT_COUNT] > 5) fail("invalid backed header");
    for (unsigned arena = 0; arena < 2; ++arena) std::memset(arena_address(arena), 0x5A, arena_bytes);
    for (unsigned record = 0; record < 12; ++record)
      for (unsigned byte = 0; byte < 404; ++byte) record_address(record)[316 + byte] = (unsigned char)(input[IN_SEED] + record * 29 + byte * 37);
    for (unsigned field = 0; field < S_PATH_HASH0_0; ++field) set_state(field, read_input());
    remember_state(); script.clear(); output.clear(); event_index = 0;
    for (unsigned index = 0; index < input[IN_EVENT_COUNT]; ++index) {
      Event item; item.call = read_input(); item.result = read_input();
      const uint32_t mutations = read_input();
      if (mutations > S_PATH_HASH0_0) fail("invalid mutation count");
      for (unsigned mutation = 0; mutation < mutations; ++mutation) {
        const uint32_t field = read_input(), value = read_input(); item.mutations.push_back({field, value});
      }
      script.push_back(item);
    }
    const uint64_t bits = (uint64_t)input[IN_DOUBLE_LOW] | (uint64_t)input[IN_DOUBLE_HIGH] << 32;
    const int result = Move_CommitIfWithinCost(input[IN_UNIT], (int32_t)input[IN_A2], input[IN_A3], std::bit_cast<double>(bits));
    if (event_index != script.size()) fail("missing callback boundary");
    require_unchanged(); output.push_back((uint32_t)result); snapshot();
    for (unsigned arena = 0; arena < 2; ++arena) output.push_back(hash_bytes(arena_address(arena), arena_bytes));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input");
}
'''


class MovementCommitTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest('required C++ compiler unavailable: ' + ', '.join(candidates))
        provenance = json.loads((builder_road.FIXTURES / 'movement-commit-provenance.json').read_text())
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance['input_sha256'])
        self.assertEqual(provenance['input_fields'], list(INPUT_FIELDS))
        self.assertEqual(provenance['state_fields'], list(STATE_FIELDS))
        self.assertEqual(provenance['calls'], list(CALLS))
        self.assertEqual(provenance['arities'], list(ARITIES))
        with tempfile.TemporaryDirectory(prefix='clash95-movement-commit-') as temporary:
            directory = Path(temporary)
            source = directory / 'recorder.cpp'
            source.write_text(harness_source())
            for optimization in ('-O0', '-O2'):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / optimization[1:]
                    built = subprocess.run(compile_command(compiler, optimization, source, executable), capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, built.stderr)
                    self.assertEqual(built.stderr, '')
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=90)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b'')
                    for case, observed, expected in zip(records, split_output(run.stdout, records), provenance['case_trace_sha256'], strict=True):
                        self.assertEqual(hashlib.sha256(observed).hexdigest(), expected, case['name'])
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance['output_sha256'])

    def test_gcc_original_movement_commit_contract(self):
        self.check_compiler(('g++-13', 'g++'))

    def test_clang_original_movement_commit_contract(self):
        self.check_compiler(('clang++-18', 'clang++'))


if __name__ == '__main__':
    unittest.main()
