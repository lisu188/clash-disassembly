#!/usr/bin/env python3
"""Original-measured Temple caller traces, exact writes and five boundaries."""
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
FUNCTION = 'Rules_MarchToTemple'
STACK_INDICES = (-1, 0, 1, 499, 500, 501)
ARENA_BASES = (0x10000000, 0x7FFE0000)
ARENA_BYTES = 0x90000
TRACK_BASES = (0x30000000, 0xA0000000)
TRACK_BYTES = 512
CALLS = ('generate', 'free', 'execute', 'integer', 'put')
ARITIES = (4, 0, 6, 1, 7)
INPUT_FIELDS = ('unit', 'row', 'column', 'double_low', 'double_high', 'seed', 'event_count')
MUTABLE_FIELDS = ('arena', 'selected') + tuple(
    f'{field}{arena}_{slot}' for arena in range(2) for slot in range(6)
    for field in ('row', 'column', 'type', 'count', 'first', 'instance')) + tuple(
        f'track_{field}{track}' for track in range(2) for field in ('count', 'first', 'last'))
STATE_FIELDS = MUTABLE_FIELDS + tuple(
    f'path_hash{arena}_{slot}' for arena in range(2) for slot in range(6)) + ('track_hash0', 'track_hash1')
FINAL_WORDS = 1 + len(STATE_FIELDS) + 4


def unsigned(value):
    return value & 0xFFFFFFFF


def signed(value):
    return (value & 0x7FFFFFFF) - (value & 0x80000000)


def signed_short(value):
    return (value & 0x7FFF) - (value & 0x8000)


def event(call, result=0, **mutations):
    return dict(call=call, result=unsigned(result),
                mutations={name: unsigned(value) for name, value in mutations.items()})


def cases():
    records = []

    def add(name, index=1, arena=0, count=1, first=0xBEEF2814,
            row=20, column=40, first_type=5, generated=0, generated_count=1,
            node=0x12345678, put_result=1, double_bits=0x3FF0000000000000,
            initial=None, generate_mut=None, free_mut=None, execute_mut=None,
            integer_mut=None, put_mut=None):
        unit = unsigned(index)
        slot = STACK_INDICES.index(index)
        state = dict(arena=arena, selected=3)
        for region in range(2):
            for number in range(6):
                for field, value in (('row', 30 + number), ('column', 40 + number),
                                     ('type', 5), ('count', 1), ('first', 0xBEEF2814),
                                     ('instance', 0x18000000 + region * 0x10000 + number * 0x100)):
                    state[f'{field}{region}_{number}'] = unsigned(value)
        for track in range(2):
            state.update({f'track_count{track}': unsigned(generated_count),
                          f'track_first{track}': 0x12341234 + track * 0x11110000,
                          f'track_last{track}': 0x8765FEDC - track * 0x11110000})
        state.update({f'count{arena}_{slot}': unsigned(count),
                      f'first{arena}_{slot}': unsigned(first),
                      f'type{arena}_{slot}': unsigned(first_type)})
        state.update({key: unsigned(value) for key, value in (initial or {}).items()})
        initial_state = state.copy()
        events, defects = [], []

        def defect(classification, phase):
            defects.append(dict(classification=classification, phase=phase))

        def distance(argument, byte, phase):
            difference = signed(argument) - byte
            if not -0x80000000 <= difference <= 0x7FFFFFFF:
                defect('signed-subtraction-overflow', phase)
            wrapped = signed(unsigned(difference))
            if wrapped == -0x80000000:
                defect('signed-abs-negation-overflow', phase)
            return signed(unsigned(-wrapped if wrapped < 0 else wrapped))

        def step(call, result, mutations):
            events.append(event(call, result, **(mutations or {})))
            state.update(events[-1]['mutations'])

        entry_count = f'count{state["arena"]}_{slot}'
        if state[entry_count]:
            if ARENA_BASES[state['arena']] + 147174 > 0x7FFFFFFF:
                defect('signed-add-overflow', 'entry-first-waypoint-base')
            waypoint = state[f'first{state["arena"]}_{slot}']
            if (distance(row, waypoint & 255, 'entry-row-distance') > 1
                    or distance(column, (waypoint >> 8) & 255, 'entry-column-distance') > 1):
                state[entry_count] = 0
        cleared = state[entry_count] != initial_state[entry_count]
        if not state[entry_count]:
            step('generate', generated, generate_mut)
            if generated:
                if ARENA_BASES[state['arena']] + 147174 > 0x7FFFFFFF:
                    defect('signed-add-overflow', 'post-generate-copy-base')
                track = generated - 1
                state[f'count{state["arena"]}_{slot}'] = state[f'track_count{track}']
                state[f'first{state["arena"]}_{slot}'] = state[f'track_first{track}']
                step('free', 0, free_mut)
        if state[f'count{state["arena"]}_{slot}']:
            base = ARENA_BASES[state['arena']]
            record = signed(unsigned(base + 725 * unit))
            coordinate_address = record + 147174
            if not -0x80000000 <= coordinate_address <= 0x7FFFFFFF:
                defect('signed-add-overflow', 'pre-execute-coordinates')
            elif coordinate_address < 0:
                defect('sign-extended-native-pointer', 'pre-execute-coordinates')
            previous = tuple(signed_short(state[f'{field}{state["arena"]}_{slot}']) for field in ('row', 'column'))
            step('execute', 0, execute_mut)
            if unit <= 500:
                defect('uninitialized-v10', 'post-execute-type')
                if 0 <= signed_short(state[f'type{state["arena"]}_{slot}']) <= 40:
                    current = tuple(signed_short(state[f'{field}{state["arena"]}_{slot}']) for field in ('row', 'column'))
                    if current == previous:
                        step('integer', node, integer_mut)
                        defect('uninitialized-v13', 'slot-put-argument')
                        step('put', put_result, put_mut)
            result = 1
        else:
            result = 0
        domain = dict(classification=defects[0]['classification'] if defects else 'defined',
                      first_failing_read=defects[0]['phase'] if defects else None,
                      original_path_defects=defects)
        records.append(dict(name=name, before_domain=domain, count_cleared=cleared,
                            expected_result=result, conditional_boundary_state=True,
                            header=[unit, unsigned(row), unsigned(column), double_bits & 0xFFFFFFFF,
                                    double_bits >> 32, 17 + len(records) % 29, len(events)],
                            initial=initial_state, events=events))

    for arena in range(2):
        for index in STACK_INDICES:
            for generated in (0, 1, 2):
                add(f'empty-arena-{arena}-index-{index}-track-{generated}', index=index,
                    arena=arena, count=0, generated=generated, generated_count=0)
    for index in STACK_INDICES:
        for unit_type in (-32768, -1, 0, 1, 39, 40, 41, 32767):
            add(f'index-{index}-type-{unit_type}', index=index, first_type=unit_type)
    for count in (2, 100, 0x40000000, 0x80000000, 0xFFFFFFFF):
        add(f'raw-near-count-{count:08x}', count=count)
        add(f'raw-far-count-{count:08x}', count=count, row=22)
    for first_row, first_column in ((0, 255), (127, 128), (128, 127), (255, 0)):
        for delta in (-2, -1, 0, 1, 2):
            waypoint = first_row | first_column << 8 | 0xCAFE0000
            add(f'row-delta-{first_row}-{first_column}-{delta}', first=waypoint,
                row=first_row + delta, column=first_column)
            add(f'column-delta-{first_row}-{first_column}-{delta}', first=waypoint,
                row=first_row, column=first_column + delta)
    for row, column, first in ((-0x80000000, 40, 0x2800), (-0x80000000, 40, 0x2801),
                               (-0x80000000, 40, 0x28FF), (20, -0x80000000, 0x14),
                               (20, -0x80000000, 0x114), (20, -0x80000000, 0xFF14),
                               (22, -0x80000000, 0x114), (0x7FFFFFFF, -0x80000000, 0),
                               (-0x7FFFFFFF, 40, 0x2801), (20, -0x7FFFFFFF, 0x114)):
        add(f'distance-bits-{unsigned(row):08x}-{unsigned(column):08x}-{first:08x}',
            row=row, column=column, first=first)
    for generated in (1, 2):
        for count in (0, 1, 100, 0xFFFFFFFF):
            add(f'copy-track-{generated}-count-{count:08x}', count=0,
                generated=generated, generated_count=count)
        add(f'far-replaced-track-{generated}', row=22, generated=generated)
        add(f'copy-fresh-high-track-{generated}', count=0, generated=generated,
            generate_mut={'arena': 1, 'selected': 501, 'row1_2': 99, 'column1_2': 255,
                          'track_first0': 0xDEADBEEF, 'track_last1': 0x76543210})
    add('null-generator-publishes-path', count=0, generate_mut={'count0_2': 7, 'row0_2': 99})
    add('null-generator-switches-high-nonempty', count=0, generate_mut={'arena': 1, 'row1_2': 99})
    add('null-generator-switches-high-empty', count=0, generate_mut={'arena': 1, 'count1_2': 0})
    for index in (-1, 0, 499, 500, 501):
        add(f'null-generator-high-coordinate-domain-{index}', count=0, index=index,
            generate_mut={'arena': 1})
    add('copy-zero-free-publishes-path', count=0, generated=1, generated_count=0,
        free_mut={'count0_2': 0x80000000, 'column0_2': 256})
    add('free-clears-copied-count', count=0, generated=1, free_mut={'count0_2': 0})
    add('free-switches-high-empty', count=0, generated=2,
        free_mut={'arena': 1, 'count1_2': 0, 'selected': 499})
    add('free-switches-high-fresh-coordinates', count=0, generated=1,
        free_mut={'arena': 1, 'row1_2': 99, 'column1_2': -32768})
    add('generator-high-copy-free-returns-low-empty', count=0, generated=2,
        generate_mut={'arena': 1}, free_mut={'arena': 0, 'count0_2': 0})
    add('generator-mutates-source-before-copy', count=0, generated=2,
        generate_mut={'track_count1': 100, 'track_first1': 0xFFFFFFFF,
                      'track_last1': 0x01020304, 'count0_2': 0x12345678})
    add('free-mutates-source-after-copy', count=0, generated=1,
        free_mut={'track_count0': 0, 'track_first0': 0xABCDEF01, 'track_last0': 0xFFFFFFFF})
    for column in (-32768, -257, -256, -129, -128, -1, 0, 127, 128, 255, 256, 32767):
        add(f'column-byte-{column}', initial={'column0_2': column})
    for row, column in ((-32768, 32767), (32767, -32768), (0, 0), (128, 255)):
        start = {'row0_2': row, 'column0_2': column}
        add(f'coordinates-{row}-{column}-row-change', initial=start,
            execute_mut={'row0_2': row + (1 if row < 32767 else -1)})
        add(f'coordinates-{row}-{column}-column-change', initial=start,
            execute_mut={'column0_2': column + (1 if column < 32767 else -1)})
    add('execute-switches-high-same-coordinates', execute_mut={'arena': 1})
    add('execute-switches-high-row-change', execute_mut={'arena': 1, 'row1_2': 99})
    add('execute-switches-high-column-change', execute_mut={'arena': 1, 'column1_2': 99})
    add('execute-switches-high-invalid-type', execute_mut={'arena': 1, 'type1_2': -1})
    add('execute-invalidates-type-in-place', execute_mut={'type0_2': 41})
    add('execute-clears-count-still-puts', execute_mut={'count0_2': 0})
    add('integer-switches-high-instance', integer_mut={'arena': 1, 'instance1_2': 0xFEDCBA98})
    add('integer-mutates-instance', integer_mut={'instance0_2': 0xABCDEF01, 'selected': 500})
    add('integer-mutates-coordinates-no-recheck', integer_mut={'row0_2': -32768, 'column0_2': 32767})
    add('put-mutates-world-no-writeback', put_mut={'arena': 1, 'selected': 501, 'count0_2': 0,
        'type0_2': -1, 'row1_2': -1, 'instance1_2': 0xABCDEF01, 'track_last0': 0})
    for index in STACK_INDICES:
        add(f'high-entry-index-{index}', arena=1, index=index)
    for bits in (0, 0x8000000000000000, 1, 0x8000000000000001,
                 0x0010000000000000, 0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF):
        add(f'finite-double-{bits:016x}', double_bits=bits, count=0, generated=2)
    for node in (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
        add(f'conditional-node-bits-{node:08x}', node=node)
    for result in (0, 1, -1, 0x80000000):
        add(f'put-result-ignored-{unsigned(result):08x}', put_result=result)
    add('out-of-range-execute-switches-high-no-late-read', index=501, execute_mut={'arena': 1})
    assert len({case['name'] for case in records}) == len(records)
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
static_assert(STATE_WORDS == 94 && INPUT_WORDS == 7 && S_PATH_HASH0_0 == 80);
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(QueuedPathBuffer) == 404);
static_assert(offsetof(UnitStackRecord, queued_path) == 316);
static_assert(offsetof(UnitStackRecord, unrecovered_0x2D1_0x2D5) == 721);
static_assert(std::endian::native == std::endian::little);
static constexpr uintptr_t arena_bases[] = {0x10000000, 0x7FFE0000};
static constexpr uintptr_t track_bases[] = {0x30000000, 0xA0000000};
static constexpr size_t arena_bytes = 0x90000, track_bytes = 512;
static constexpr int stack_indices[] = {-1, 0, 1, 499, 500, 501};
int gameData, g_SelectedUnitIndex;
static int expected_game_data, expected_selected;
static const char aPa_0[] = "PA";
static unsigned char expected_arenas[2][arena_bytes], expected_tracks[2][track_bytes];
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
static unsigned char *track_address(unsigned track) { return (unsigned char *)track_bases[track]; }
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
static uint32_t record_offset() { return 147174u + 725u * input[IN_UNIT]; }
static uint32_t get_state(unsigned field) {
  if (field == S_ARENA) return current_arena();
  if (field == S_SELECTED) return g_SelectedUnitIndex;
  if (field >= S_PATH_HASH0_0 && field < S_TRACK_HASH0)
    return hash_bytes(record_address(field - S_PATH_HASH0_0) + 316, 404);
  if (field >= S_TRACK_HASH0 && field < STATE_WORDS)
    return hash_bytes(track_address(field - S_TRACK_HASH0), 404);
  if (field >= S_TRACK_COUNT0 && field < S_PATH_HASH0_0) {
    static constexpr unsigned offsets[] = {0, 4, 400};
    return word(track_address((field - S_TRACK_COUNT0) / 3) + offsets[(field - S_TRACK_COUNT0) % 3]);
  }
  if (field >= S_ROW0_0 && field < S_TRACK_COUNT0) {
    const unsigned record = (field - S_ROW0_0) / 6;
    const unsigned item = (field - S_ROW0_0) % 6;
    static constexpr unsigned offsets[] = {0, 2, 6, 316, 320, 721};
    const unsigned char *address = record_address(record) + offsets[item];
    if (item < 3) { int16_t value; std::memcpy(&value, address, 2); return (uint32_t)(int32_t)value; }
    return word(address);
  }
  fail("invalid state field");
}
static void set_state(unsigned field, uint32_t value) {
  if (field == S_ARENA) { if (value > 1) fail("invalid arena"); gameData = (int32_t)arena_bases[value]; return; }
  if (field == S_SELECTED) { g_SelectedUnitIndex = (int32_t)value; return; }
  if (field >= S_TRACK_COUNT0 && field < S_PATH_HASH0_0) {
    static constexpr unsigned offsets[] = {0, 4, 400};
    put_word(track_address((field - S_TRACK_COUNT0) / 3) + offsets[(field - S_TRACK_COUNT0) % 3], value);
    return;
  }
  if (field >= S_ROW0_0 && field < S_TRACK_COUNT0) {
    const unsigned record = (field - S_ROW0_0) / 6;
    const unsigned item = (field - S_ROW0_0) % 6;
    static constexpr unsigned offsets[] = {0, 2, 6, 316, 320, 721};
    unsigned char *address = record_address(record) + offsets[item];
    if (item < 3) { const uint16_t narrow = (uint16_t)value; std::memcpy(address, &narrow, 2); }
    else put_word(address, value);
    return;
  }
  fail("invalid mutation field");
}
static void remember_state() {
  for (unsigned arena = 0; arena < 2; ++arena) std::memcpy(expected_arenas[arena], arena_address(arena), arena_bytes);
  for (unsigned track = 0; track < 2; ++track) std::memcpy(expected_tracks[track], track_address(track), track_bytes);
  expected_game_data = gameData; expected_selected = g_SelectedUnitIndex;
}
static void require_expected() {
  for (unsigned arena = 0; arena < 2; ++arena)
    if (std::memcmp(expected_arenas[arena], arena_address(arena), arena_bytes)) fail("unexpected caller arena write");
  for (unsigned track = 0; track < 2; ++track)
    if (std::memcmp(expected_tracks[track], track_address(track), track_bytes)) fail("caller wrote track bytes");
  if (gameData != expected_game_data || g_SelectedUnitIndex != expected_selected) fail("caller wrote globals");
}
static int32_t wrapped_distance(uint32_t target, uint32_t point) {
  const uint32_t delta = target - point;
  return (int32_t)((int32_t)delta < 0 ? 0u - delta : delta);
}
static void expect_initial_clear() {
  unsigned char *path = expected_arenas[current_arena()] + record_offset() + 316;
  if (!word(path)) return;
  const uint32_t first = word(path + 4);
  if (wrapped_distance(input[IN_ROW], first & 255) > 1 ||
      wrapped_distance(input[IN_COLUMN], (first >> 8) & 255) > 1) put_word(path, 0);
}
static void snapshot() { for (unsigned field = 0; field < STATE_WORDS; ++field) output.push_back(get_state(field)); }
static uint32_t boundary(uint32_t call, std::initializer_list<uint32_t> args) {
  require_expected();
  static constexpr unsigned arities[] = {0, 4, 0, 6, 1, 7};
  if (call > 5 || args.size() != arities[call]) fail("invalid boundary arity");
  if (event_index >= script.size() || script[event_index].call != call) fail("unexpected callback order");
  output.push_back(call); output.insert(output.end(), args.begin(), args.end()); snapshot();
  const Event &event = script[event_index++];
  for (const Mutation &mutation : event.mutations) set_state(mutation.field, mutation.value);
  remember_state();
  if (call == 1 && event.result) {
    if (event.result > 2) fail("invalid generated track selector");
    std::memcpy(expected_arenas[current_arena()] + record_offset() + 316,
                track_address(event.result - 1), 404);
  }
  return event.result;
}
static int *Temple_GenerateApproachTrack(unsigned index, int row, int repeated_row, int column) {
  const uint32_t selected = boundary(1, {index, (uint32_t)row, (uint32_t)repeated_row, (uint32_t)column});
  return selected ? (int *)track_address(selected - 1) : nullptr;
}
static int j__nfree_() { return (int32_t)boundary(2, {}); }
static void UnitStack_ExecuteQueuedPath(unsigned int index, int animate, char carry, DWORD opaque, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  boundary(3, {index, (uint32_t)animate, (uint8_t)carry, opaque, (uint32_t)bits, (uint32_t)(bits >> 32)});
}
static int Rules_AddIntegerValue(int value) { return (int32_t)boundary(4, {(uint32_t)value}); }
static signed int Rules_PutInstanceSlotValue(int instance, _BYTE *name, int argument, _DWORD *value, double context) {
  const uint32_t key = (uint8_t)name[0] | (uint32_t)(uint8_t)name[1] << 8 | (uint32_t)(uint8_t)name[2] << 16;
  const uint64_t bits = std::bit_cast<uint64_t>(context);
  return (int32_t)boundary(5, {(uint32_t)instance, key, (uint32_t)argument, value[1], value[2], (uint32_t)bits, (uint32_t)(bits >> 32)});
}
// Exact current compatibility helper for unchanged-before calls; no safe oracle patch.
int __cdecl abs32(int value) { return value < 0 ? -value : value; }
@BODY@

static uint32_t read_input() { uint32_t value; if (std::fread(&value, 4, 1, stdin) != 1) fail("incomplete input"); return value; }
int main() {
  for (unsigned arena = 0; arena < 2; ++arena)
    if (mmap(arena_address(arena), arena_bytes, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) != arena_address(arena)) fail("cannot map fixed fixture arena");
  for (unsigned track = 0; track < 2; ++track)
    if (mmap(track_address(track), 4096, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0) != track_address(track)) fail("cannot map fixed fixture track");
  const uint32_t count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    for (uint32_t &item : input) item = read_input();
    bool valid = false;
    for (int index : stack_indices) valid |= input[IN_UNIT] == (uint32_t)index;
    if (!valid || input[IN_EVENT_COUNT] > 5) fail("invalid backed header");
    for (unsigned arena = 0; arena < 2; ++arena) std::memset(arena_address(arena), 0x5A, arena_bytes);
    for (unsigned record = 0; record < 12; ++record)
      for (unsigned byte = 0; byte < 404; ++byte) record_address(record)[316 + byte] = (unsigned char)(input[IN_SEED] + record * 29 + byte * 37);
    for (unsigned track = 0; track < 2; ++track)
      for (unsigned byte = 0; byte < track_bytes; ++byte) track_address(track)[byte] = (unsigned char)(input[IN_SEED] + track * 53 + byte * 41);
    for (unsigned field = 0; field < S_PATH_HASH0_0; ++field) set_state(field, read_input());
    remember_state(); expect_initial_clear(); script.clear(); output.clear(); event_index = 0;
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
    const int result = Rules_MarchToTemple(input[IN_UNIT], (int32_t)input[IN_ROW], (int32_t)input[IN_COLUMN], std::bit_cast<double>(bits));
    if (event_index != script.size()) fail("missing callback boundary");
    require_expected(); output.push_back((uint32_t)result); snapshot();
    for (unsigned arena = 0; arena < 2; ++arena) output.push_back(hash_bytes(arena_address(arena), arena_bytes));
    for (unsigned track = 0; track < 2; ++track) output.push_back(hash_bytes(track_address(track), track_bytes));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input");
}
'''


class TempleMarchTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest('required C++ compiler unavailable: ' + ', '.join(candidates))
        provenance = json.loads((builder_road.FIXTURES / 'temple-march-provenance.json').read_text())
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance['input_sha256'])
        self.assertEqual(provenance['input_fields'], list(INPUT_FIELDS))
        self.assertEqual(provenance['state_fields'], list(STATE_FIELDS))
        self.assertEqual(provenance['calls'], list(CALLS))
        self.assertEqual(provenance['arities'], list(ARITIES))
        with tempfile.TemporaryDirectory(prefix='clash95-temple-march-') as temporary:
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

    def test_gcc_original_temple_march_contract(self):
        self.check_compiler(('g++-13', 'g++'))

    def test_clang_original_temple_march_contract(self):
        self.check_compiler(('clang++-18', 'clang++'))


if __name__ == '__main__':
    unittest.main()
