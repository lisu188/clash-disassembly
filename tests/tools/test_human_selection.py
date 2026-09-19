#!/usr/bin/env python3
"""Actual human-selection cleanup against a small measured original oracle."""
from pathlib import Path
import hashlib
import importlib.util
import json
import shutil
import subprocess
import tempfile
import unittest

import test_builder_road as source_tools

SOURCE = source_tools.WORLD2
FUNCTION = "WorldMap_SyncSelectionForHumanPlayer"
FIXTURES = Path(__file__).resolve().parent / "fixtures/human_selection"


def load_contract(path=None):
    specification = importlib.util.spec_from_file_location("human_selection_contract", path or FIXTURES / "contract.py")
    module = importlib.util.module_from_spec(specification)
    specification.loader.exec_module(module)
    return module


def harness_source(body=None):
    return HARNESS.replace("@BODY@", body if body is not None else source_tools.extract(SOURCE, FUNCTION))


def compiler_command(compiler, optimization, source, executable):
    return [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
            "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
            "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
            "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
            "-isystem", str(source_tools.REPO / "src"), str(source), "-o", str(executable)]


HARNESS = r'''
#include "recovered_layout.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sys/mman.h>

constexpr uint32_t stateWords = 15;
constexpr size_t arenaBytes = 150200;
static_assert(sizeof(PlayerRuntimeState) == 1423 && offsetof(PlayerRuntimeState, controller_mode) == 27);
static_assert(sizeof(UnitStackRecord) == 725 && offsetof(UnitStackRecord, unit_slots) == 6);
static_assert(sizeof(UnitSlotRecord::unit_type_id) == 2);
int gameData, g_CurrentPlayerIndex, g_SelectedUnitIndex;
alignas(4096) static unsigned char arenas[2][arenaBytes];
static uint32_t caseIndex, eventIndex;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call; std::vector<Mutation> changes; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "human-selection case=%u event=%u: %s\n", caseIndex, eventIndex, message);
  std::exit(1);
}
static uint32_t arenaBits(uint32_t identity) {
  if (identity >= 6) fail("invalid arena identity");
  const uint32_t base = (uint32_t)(uintptr_t)arenas[identity % 2];
  if (identity >= 4) return base - (1423u << 20);
  return base + (identity >= 2 ? 0x80000000u : 0);
}
static uint32_t arenaIdentity(uintptr_t address) {
  for (uint32_t identity = 0; identity < 6; ++identity)
    if (address == arenaBits(identity)) return identity;
  fail("callback pointer is not a declared zero-extended low32 arena");
}
static PlayerRuntimeState *playerAt(uint32_t arena, uint32_t player) {
  return (PlayerRuntimeState *)(arenas[arena] + PLAYER_RUNTIME_STATE_OFFSET + player * PLAYER_DATA_STRIDE);
}
static UnitStackRecord *stackAt(uint32_t arena, uint32_t stack) {
  return (UnitStackRecord *)(arenas[arena] + UNIT_STACK_TABLE_OFFSET + stack * UNIT_STACK_STRIDE);
}
static uint32_t getState(uint32_t field) {
  if (field >= 3 && field < 7) {
    const uint32_t index = field - 3;
    return (uint32_t)playerAt(index / 2, index % 2)->controller_mode;
  }
  if (field >= 7 && field < stateWords) {
    const uint32_t index = field - 7;
    return (uint32_t)(int32_t)stackAt(index / 4, index % 4 / 2)->unit_slots[index % 2].unit_type_id;
  }
  switch (field) {
    case 0: return arenaIdentity((uint32_t)gameData);
    case 1: return g_CurrentPlayerIndex;
    case 2: return g_SelectedUnitIndex;
    default: fail("invalid state field");
  }
}
static void setState(uint32_t field, uint32_t value) {
  if (field >= 3 && field < 7) {
    const uint32_t index = field - 3;
    playerAt(index / 2, index % 2)->controller_mode = (int32_t)value;
    return;
  }
  if (field >= 7 && field < stateWords) {
    const uint32_t index = field - 7;
    stackAt(index / 4, index % 4 / 2)->unit_slots[index % 2].unit_type_id = (int16_t)(uint16_t)value;
    return;
  }
  switch (field) {
    case 0: gameData = (int32_t)arenaBits(value); return;
    case 1: g_CurrentPlayerIndex = (int32_t)value; return;
    case 2: g_SelectedUnitIndex = (int32_t)value; return;
    default: fail("invalid mutation field");
  }
}
static void snapshot() { for (uint32_t field = 0; field < stateWords; ++field) output.push_back(getState(field)); }
static void boundary(uint32_t call, void *arena, DWORD context) {
  if (eventIndex >= script.size() || script[eventIndex].call != call) fail("unexpected callback order");
  if (call == 1 && g_SelectedUnitIndex != -1) fail("selection must be cleared before refresh");
  output.insert(output.end(), {call, arenaIdentity((uintptr_t)arena), context});
  snapshot();
  const Event &event = script[eventIndex++];
  for (const Mutation &mutation : event.changes) setState(mutation.field, mutation.value);
}
static void WorldMap_RefreshActionButtonBarState(void *arena) { boundary(1, arena, 0); }
static void UnitStackSelection_SyncForCurrentSelection(void *arena, DWORD context) { boundary(2, arena, context); }
@BODY@
static uint32_t readInput() {
  uint32_t value;
  if (std::fread(&value, 4, 1, stdin) != 1) fail("incomplete fixture input");
  return value;
}
static uint32_t hashBytes(const unsigned char *data, size_t bytes) {
  uint32_t value = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) value = (value ^ data[index]) * 16777619u;
  return value;
}
static void guardRejectedStackReads() {
  // These exact unsupported stack addresses occur only in nonhuman cases.
  // A premature load faults deterministically instead of reading incidental data.
  for (uint32_t arena = 0; arena < 4; ++arena) {
    const uint32_t address = arenaBits(arena) + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET
            + UNIT_STACK_STRIDE * 0x70000000u;
    void *page = (void *)(uintptr_t)(address & ~4095u);
    void *mapped = mmap(page, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    if (mapped != page) fail("cannot reserve nonhuman stack guard page without replacement");
  }
}
int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX) fail("fixture arenas must fit positive low32");
  guardRejectedStackReads();
  const uint32_t count = readInput();
  for (caseIndex = 0; caseIndex < count; ++caseIndex) {
    const DWORD context = readInput();
    const uint32_t eventCount = readInput();
    if (eventCount > 2) fail("fixture exceeds the two-boundary contract");
    std::memset(arenas, 0x5A, sizeof arenas);
    for (uint32_t field = 0; field < stateWords; ++field) setState(field, readInput());
    script.clear(); output.clear(); eventIndex = 0;
    for (uint32_t index = 0; index < eventCount; ++index) {
      Event event; event.call = readInput();
      const uint32_t countChanges = readInput();
      if (countChanges > stateWords) fail("too many callback changes");
      for (uint32_t mutation = 0; mutation < countChanges; ++mutation) {
        const uint32_t field = readInput(), value = readInput();
        event.changes.push_back({field, value});
      }
      script.push_back(event);
    }
    WorldMap_SyncSelectionForHumanPlayer(context);
    if (eventIndex != script.size()) fail("missing callback");
    // The original function is void: there is no fabricated EAX return word.
    snapshot();
    output.push_back(hashBytes(arenas[0], arenaBytes));
    output.push_back(hashBytes(arenas[1], arenaBytes));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input");
}
'''


class HumanSelectionTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        contract = load_contract()
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        records = contract.cases()
        encoded = contract.pack_inputs(records)
        self.assertEqual(hashlib.sha256((FIXTURES / "contract.py").read_bytes()).hexdigest(),
                         provenance["bindings"]["public_contract"]["sha256"])
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(list(contract.CALLS), provenance["calls"])
        self.assertEqual(contract.STATE_FIELDS, provenance["state_fields"])
        self.assertEqual(contract.EVENT_WORDS, provenance["event_words"])
        self.assertEqual(contract.FINAL_WORDS, provenance["final_words"])
        self.assertEqual([case["name"] for case in records], provenance["case_names"])
        with tempfile.TemporaryDirectory(prefix="clash95-human-selection-") as temporary:
            directory = Path(temporary)
            source = directory / "human_selection.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("selection-" + optimization[1:])
                    command = compiler_command(compiler, optimization, source, executable)
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    for case, trace, expected in zip(records, contract.decode_output(run.stdout, records),
                                                     provenance["case_trace_sha256"], strict=True):
                        self.assertEqual(hashlib.sha256(trace).hexdigest(), expected, case["name"])
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_human_selection_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_human_selection_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
