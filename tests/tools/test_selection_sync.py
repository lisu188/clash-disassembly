#!/usr/bin/env python3
"""Execute the actual selection-sync caller against measured original traces."""

import hashlib
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

import test_builder_road as source_tools

SOURCE = source_tools.WORLD2
FUNCTION = "UnitStackSelection_SyncForCurrentSelection"
FIXTURES = Path(__file__).resolve().parent / "fixtures/selection_sync"


def load_contract(path=None):
    specification = importlib.util.spec_from_file_location(
        "selection_sync_contract", path or FIXTURES / "contract.py"
    )
    module = importlib.util.module_from_spec(specification)
    specification.loader.exec_module(module)
    return module


def harness_source(body=None):
    actual_body = body if body is not None else source_tools.extract(SOURCE, FUNCTION)
    return HARNESS.replace("@BODY@", actual_body)


def compiler_command(compiler, optimization, source, executable):
    return [
        compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
        "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
        "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
        "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
        "-isystem", str(source_tools.REPO / "src"), str(source),
        "-o", str(executable),
    ]


HARNESS = r'''
#include "recovered_layout.h"
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr uint32_t stateWords = 3;
constexpr size_t arenaBytes = 150200;
static_assert(sizeof(UnitStackRecord) == 725);
static_assert(UNIT_STACK_TABLE_OFFSET == 147174 && UNIT_STACK_STRIDE == 725);
int gameData, g_SelectedUnitIndex, g_UnitStackSelectionActiveUnitIndex;
alignas(4096) static unsigned char arenas[2][arenaBytes];
static uint32_t caseIndex, eventIndex, entryPointerBits;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> changes; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "selection-sync case=%u event=%u: %s\n", caseIndex, eventIndex, message);
  std::exit(1);
}

static uint32_t arenaBits(uint32_t identity) {
  if (identity >= 4) fail("invalid arena identity");
  const uint32_t base = (uint32_t)(uintptr_t)arenas[identity % 2];
  return base + (identity >= 2 ? 0x80000000u : 0);
}

static uint32_t arenaIdentity(uint32_t bits) {
  for (uint32_t identity = 0; identity < 4; ++identity) {
    if (bits == arenaBits(identity)) return identity;
  }
  fail("live gameData is not a declared arena");
}

static uint32_t getState(uint32_t field) {
  switch (field) {
    case 0: return arenaIdentity((uint32_t)gameData);
    case 1: return (uint32_t)g_SelectedUnitIndex;
    case 2: return (uint32_t)g_UnitStackSelectionActiveUnitIndex;
    default: fail("invalid state field");
  }
}

static void setState(uint32_t field, uint32_t value) {
  switch (field) {
    case 0: gameData = (int32_t)arenaBits(value); return;
    case 1: g_SelectedUnitIndex = (int32_t)value; return;
    case 2: g_UnitStackSelectionActiveUnitIndex = (int32_t)value; return;
    default: fail("invalid mutation field");
  }
}

static void snapshot() {
  for (uint32_t field = 0; field < stateWords; ++field) {
    output.push_back(getState(field));
  }
}

static int32_t boundary(uint32_t call, uint32_t first, uint32_t second) {
  if (eventIndex >= script.size() || script[eventIndex].call != call) {
    fail("unexpected callback order");
  }
  const Event &event = script[eventIndex++];
  output.insert(output.end(), {call, first, second, event.result});
  snapshot();
  for (const Mutation &mutation : event.changes) {
    setState(mutation.field, mutation.value);
  }
  return (int32_t)event.result;
}

static int Unit_GetSquadCount(intptr_t address) {
  // Compare the full native argument before representing the low32 address.
  // Scripted boundaries observe even the synthetic unbacked high addresses.
  for (uint32_t arena = 0; arena < 4; ++arena) {
    for (int32_t slot = -1; slot <= 1; ++slot) {
      const uint32_t expected = arenaBits(arena) + UNIT_STACK_TABLE_OFFSET
              + UNIT_STACK_STRIDE * (uint32_t)slot;
      if ((uintptr_t)address == (uintptr_t)expected) {
        return boundary(1, arena, (uint32_t)slot);
      }
    }
  }
  fail("count argument is not a declared zero-extended low32 stack address");
}

static int UnitStackSelection_End(void *pointer) {
  const uintptr_t address = (uintptr_t)pointer;
  if (address == (uintptr_t)entryPointerBits) return boundary(2, 0, 0);
  for (uint32_t arena = 0; arena < 4; ++arena) {
    const uint32_t table = arenaBits(arena) + UNIT_STACK_TABLE_OFFSET;
    if (address == (uintptr_t)table) return boundary(2, arena + 1, 0);
  }
  fail("End pointer is neither exact entry bits nor a declared table base");
}

static int UnitStackSelection_BeginForSelectedStack(DWORD context) {
  return boundary(3, context, 0);
}

static int UnitStackSelection_RefreshForSelectedStack(DWORD context) {
  return boundary(4, context, 0);
}

@BODY@

static uint32_t readInput() {
  uint32_t value;
  if (std::fread(&value, 4, 1, stdin) != 1) fail("incomplete fixture input");
  return value;
}

int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX) {
    fail("fixture arenas must fit positive low32");
  }
  const uint32_t count = readInput();
  for (caseIndex = 0; caseIndex < count; ++caseIndex) {
    entryPointerBits = readInput();
    const DWORD context = readInput();
    const uint32_t eventCount = readInput();
    if (eventCount > 4) fail("fixture exceeds three queries and one terminal call");
    for (uint32_t arena = 0; arena < 4; ++arena) {
      if (entryPointerBits == arenaBits(arena) + UNIT_STACK_TABLE_OFFSET) {
        fail("entry pointer aliases a table base");
      }
    }
    for (uint32_t field = 0; field < stateWords; ++field) {
      setState(field, readInput());
    }
    script.clear();
    output.clear();
    eventIndex = 0;
    for (uint32_t index = 0; index < eventCount; ++index) {
      Event event;
      event.call = readInput();
      event.result = readInput();
      const uint32_t changeCount = readInput();
      if (changeCount > stateWords) fail("too many callback changes");
      for (uint32_t change = 0; change < changeCount; ++change) {
        const uint32_t field = readInput();
        const uint32_t value = readInput();
        event.changes.push_back({field, value});
      }
      script.push_back(event);
    }
    UnitStackSelection_SyncForCurrentSelection((void *)(uintptr_t)entryPointerBits, context);
    if (eventIndex != script.size()) fail("missing callback");
    // The caller is void. Only its final live state follows the event trace.
    snapshot();
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) {
      fail("trace output failed");
    }
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input");
}
'''


class SelectionSyncTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        contract = load_contract()
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        records = contract.cases()
        encoded = contract.pack_inputs(records)
        self.assertEqual(
            hashlib.sha256((FIXTURES / "contract.py").read_bytes()).hexdigest(),
            provenance["bindings"]["contract"]["sha256"],
        )
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(list(contract.CALLS), provenance["calls"])
        self.assertEqual(contract.STATE_FIELDS, provenance["state_fields"])
        self.assertEqual(contract.EVENT_WORDS, provenance["event_words"])
        self.assertEqual(contract.FINAL_WORDS, provenance["final_words"])
        self.assertEqual([case["name"] for case in records], provenance["case_names"])
        with tempfile.TemporaryDirectory(prefix="clash95-selection-sync-") as temporary:
            directory = Path(temporary)
            source = directory / "selection_sync.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("selection-" + optimization[1:])
                    command = compiler_command(compiler, optimization, source, executable)
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    self.assertEqual(built.stderr, "")
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    traces = contract.decode_output(run.stdout, records)
                    for case, trace, expected in zip(
                        records, traces, provenance["case_trace_sha256"], strict=True
                    ):
                        self.assertEqual(hashlib.sha256(trace).hexdigest(), expected, case["name"])
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_selection_sync_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_selection_sync_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
