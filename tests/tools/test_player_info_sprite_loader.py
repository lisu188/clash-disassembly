#!/usr/bin/env python3
"""Check the actual player-info loader body at its allocation/loading seams.

The call order and filename increment come from UI_SetCurrentPlayer at
0x423370 (clash95.asm, lines 54311-54361). The zero allocator context is an
explicit adaptation of the current Mem_Alloc's ignored argument, not an
original-register claim. Recording substitutes never dereference their fake
addresses. Null and high-address results exercise the caller contract; they
do not establish that the real allocator or loader produces those results.
In particular, synthetic loader pointers above 4 GiB only check truncation at
publication; they are outside the production allocator's low32 address domain.
This fixture is not original-executable, asset, rendering, or campaign proof.
"""

from pathlib import Path
import hashlib
import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(os.environ.get("CLASH95_SOURCE_ROOT", Path(__file__).resolve().parents[2])).resolve()
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import definition_targets
from split_source_index import body_sha256, scan_definitions

NAME = "UI_LoadCurrentPlayerInfoSpriteSet"
HARNESS = r'''
#include "buildings/buildings_api.h"
#include "buildings/buildings_state.h"
#include "render/render_api.h"
#include "runtime/runtime_api.h"
#include "recovered_legacy_imports.h"

static_assert(sizeof(int) == 4 && sizeof(uintptr_t) == 8);
int g_CurrentPlayerInfoSpriteSet;

struct LoaderCase
{
  const char *name;
  int player;
  uint32_t old_handle;
  uint32_t allocation;
  uintptr_t loaded_pointer;
  unsigned char log_byte;
  DWORD log_context;
  int unused_context;
  const char *file_name;
  const char *events;
  uintptr_t returned_pointer;
  uint32_t published_handle;
};

// Explicit expected values include INC's signed 32-bit boundary behavior.
static const LoaderCase cases[] = {
  {"fresh", 0, 0, 0x1200, 0x2400, 0, 0, 17,
   "info1.s32", "SAL", 0x2400, 0x2400},
  {"replace", 3, 0x87654321, 0x12345678, 0xabcdef10, 0x7f, 0xffffffff, -1,
   "info4.s32", "FSAL", 0xabcdef10, 0xabcdef10},
  {"minus-one", -1, 0, 0x80000000, 0x80000000, 0x80, 0x80000000, 0,
   "info0.s32", "SAL", 0x80000000, 0x80000000},
  {"maximum-player", 2147483647, 7, 0xffffffff, 0xffffffff, 0xff, 0x12345678, 91,
   "info-2147483648.s32", "FSAL", 0xffffffff, 0xffffffff},
  {"minimum-player", (-2147483647 - 1), 0, 0x4000, 0x87654321, 1, 9, -31,
   "info-2147483647.s32", "SAL", 0x87654321, 0x87654321},
  {"null-fresh", 1, 0, 0, 0xdead, 0x42, 0, 2147483647,
   "info2.s32", "SA", 0, 0},
  {"null-replacement", -2, 0xffffffff, 0, 0xbeef, 0xfe, 0xffffffff, (-2147483647 - 1),
   "info-1.s32", "FSA", 0, 0},
  {"wide-loader-result", 7, 0x3000, 0x1000, 0x123456789ULL, 0x81, 42, 5,
   "info8.s32", "FSAL", 0x123456789ULL, 0x23456789},
  {"null-loader-result", 2, 0x2000, 0x80000001, 0, 3, 0x76543210, -19,
   "info3.s32", "FSAL", 0, 0},
  {"zero-low-word-result", 8, 0, 0x7000, 0x100000000ULL, 0, 1, 44,
   "info9.s32", "SAL", 0x100000000ULL, 0},
};

static const LoaderCase *active;
static char events[8];
static unsigned event_count;

static void require(bool condition, const char *message)
{
  if (!condition)
  {
    fprintf(stderr, "%s: %s\n", active->name, message);
    exit(1);
  }
}

static void record(char event, uint32_t expected_global)
{
  require(event_count + 1 < sizeof(events), "too many helper calls");
  require(static_cast<uint32_t>(g_CurrentPlayerInfoSpriteSet) == expected_global,
          "global changed before its required publication point");
  events[event_count++] = event;
  events[event_count] = '\0';
}

int nfree_(_DWORD handle)
{
  record('F', active->old_handle);
  require(handle == active->old_handle, "wrong old allocation freed");
  return 0;
}

int sprintf_(char *buffer, const char *format, ...)
{
  record('S', 0);
  require(strcmp(format, "info%d.s32") == 0, "wrong sprite filename format");
  va_list arguments;
  va_start(arguments, format);
  const int result = vsnprintf(buffer, 24, format, arguments);
  va_end(arguments);
  require(result >= 0 && result < 24, "filename exceeds recovered buffer");
  require(strcmp(buffer, active->file_name) == 0, "wrong player filename");
  return result;
}

int Mem_Alloc(int size, int ignored_context, char log_byte, DWORD log_context)
{
  record('A', 0);
  require(size == 0x1010, "wrong sprite-set object allocation size");
  require(ignored_context == 0, "ignored allocator context is not defined zero");
  require(static_cast<unsigned char>(log_byte) == active->log_byte,
          "logging byte was not forwarded");
  require(log_context == active->log_context, "logging context was not forwarded");
  return static_cast<int32_t>(active->allocation);
}

_DWORD *DLXSpriteSet_Load(_DWORD *sprite_set, const void *file_name)
{
  record('L', 0);
  require(active->allocation != 0, "loader called after null allocation");
  require(reinterpret_cast<uintptr_t>(sprite_set) == active->allocation,
          "allocation bits were sign-extended or otherwise changed");
  require(strcmp(static_cast<const char *>(file_name), active->file_name) == 0,
          "loader received the wrong filename");
  return reinterpret_cast<_DWORD *>(active->loaded_pointer);
}

@ACTUAL_BODY@

int main()
{
  for (const LoaderCase &test_case : cases)
  {
    active = &test_case;
    g_CurrentPlayerInfoSpriteSet = static_cast<int32_t>(active->old_handle);
    event_count = 0;
    events[0] = '\0';
    _DWORD *result = UI_LoadCurrentPlayerInfoSpriteSet(
        active->player, active->unused_context,
        static_cast<char>(active->log_byte), active->log_context);
    require(strcmp(events, active->events) == 0, "helper call sequence differs");
    require(reinterpret_cast<uintptr_t>(result) == active->returned_pointer,
            "wrong returned loader pointer");
    require(static_cast<uint32_t>(g_CurrentPlayerInfoSpriteSet) == active->published_handle,
            "wrong published low32 handle");
  }
  puts("PASS player_info_loader_cases=10");
}
'''


def actual_body():
    """Resolve and bind the canonical function rather than copying a candidate."""
    manifest_path = ROOT / "data/recovered_sources.json"
    manifest = json.loads(manifest_path.read_text())
    record = next(item for item in manifest["functions"] if item["name"] == NAME)
    targets = definition_targets(record)
    if len(targets) != 1 or targets[0].name != NAME:
        raise AssertionError("loader migration requires its canonical method and ABI adapter in this fixture")
    source = ROOT / targets[0].source
    text = source.read_text()
    definitions = scan_definitions(text, {NAME})
    if len(definitions) != 1:
        raise AssertionError(f"expected one canonical loader in {source}")
    definition = definitions[0]
    if body_sha256(text, definition) != record["body_sha256"]:
        raise AssertionError("loader source and manifest body hash differ")
    inputs = {
        str(path): hashlib.sha256(path.read_bytes()).hexdigest()
        for path in (manifest_path, source, Path(__file__).resolve())
    }
    return text[definition.start:definition.end], inputs


class PlayerInfoSpriteLoaderTests(unittest.TestCase):
    def check_compiler(self, compiler):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("recovered pointer conversion fixture requires Linux x86-64")
        compiler_path = shutil.which(compiler)
        if compiler_path is None:
            self.skipTest("supported compiler unavailable: " + compiler)
        body, inputs = actual_body()
        evidence = os.environ.get("CLASH95_PLAYER_INFO_LOADER_EVIDENCE")
        with tempfile.TemporaryDirectory(prefix="clash95-player-info-loader-") as temporary:
            directory = Path(temporary)
            source = directory / "loader.cpp"
            source.write_text(HARNESS.replace("@ACTUAL_BODY@", body))
            results = []
            try:
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
                        label = compiler + optimization
                        executable = directory / label
                        command = [compiler_path, "-std=gnu++20", "-U_GNU_SOURCE",
                                   "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                                   optimization, "-Wall", "-Wextra", "-Werror",
                                   "-fsanitize=undefined", "-fno-sanitize-recover=undefined",
                                   "-I", str(ROOT / "src"), str(source), "-o", str(executable)]
                        built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                        (directory / (label + ".build.log")).write_text(built.stdout + built.stderr)
                        result = {"command": command, "build_exit": built.returncode}
                        results.append(result)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        run = subprocess.run([str(executable)], capture_output=True, text=True, timeout=15)
                        (directory / (label + ".run.log")).write_text(run.stdout + run.stderr)
                        result.update(run_exit=run.returncode, stdout=run.stdout, stderr=run.stderr)
                        self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                        self.assertEqual(run.stdout, "PASS player_info_loader_cases=10\n")
                        self.assertEqual(run.stderr, "")
                for path, digest in inputs.items():
                    self.assertEqual(hashlib.sha256(Path(path).read_bytes()).hexdigest(), digest,
                                     "fixture input changed during validation: " + path)
            finally:
                (directory / "summary.json").write_text(json.dumps({
                    "source_root": str(ROOT), "input_sha256": inputs, "profiles": results,
                    "evidence_scope": "actual source body with recording helper substitutes",
                }, indent=2) + "\n")
                if evidence:
                    shutil.copytree(directory, Path(evidence).resolve() / compiler)

    def test_gcc_loader_contract(self):
        self.check_compiler("g++-13")

    def test_clang_loader_contract(self):
        self.check_compiler("clang++-18")


if __name__ == "__main__":
    unittest.main()
