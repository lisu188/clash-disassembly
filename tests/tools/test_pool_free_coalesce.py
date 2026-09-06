#!/usr/bin/env python3
"""Exercise the actual recovered pool unlink/free logic without retail assets.

Original assembly at clash95.asm:178374-178419 preserves the removed pool in
EAX across both _nfree_ calls. ECX only traverses neighboring pool links.
The fixture records the requested free and checks every surviving link; it
does not replace nfree_ in the native unit suite or duplicate the function.
"""

from __future__ import annotations

import os
from pathlib import Path
import platform
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))
from split_source_index import scan_definitions


PRELUDE = r"""
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
typedef uint32_t _DWORD;
int g_HeapChunkHeaderSize = 16;
int g_MemPoolBlockHeaderSize = 16;
int g_MemPoolListHead;
static _DWORD freed_address;
static int free_count;
/* Non-PIE static storage gives aligned addresses; check low32 before use. */
static _DWORD arena[3][20];
static _DWORD address(const void *p) { return (_DWORD)(uintptr_t)p; }
int nfree_(_DWORD p) { freed_address = p; ++free_count; return 0; }
"""

HARNESS = r"""
static int run_case(const char *name, int previous, int next) {
  _DWORD *removed = arena[1];
  _DWORD *block = removed + 4;
  _DWORD *left = arena[0];
  _DWORD *right = arena[2];
  _DWORD *head = previous ? left : removed;
  _DWORD expected_free = (previous || next) ? address(removed) : 0;
  int failed = 0;
  if ((uintptr_t)(arena + 3) > UINT32_MAX) return 99;
  memset(arena, 0, sizeof(arena));
  freed_address = 0;
  free_count = 0;
  removed[0] = next ? address(right) : 0;
  removed[1] = previous ? address(left) : 0;
  removed[2] = 0; /* no existing free blocks */
  removed[3] = 32; /* one allocated block occupies the whole pool */
  block[3] = (_DWORD)-32;
  left[0] = address(removed);
  left[3] = 0xAABBCCDDu;
  right[1] = address(removed);
  right[3] = 0x12345678u;
  g_MemPoolListHead = (int)address(head);
  if (Mem_PoolFreeCoalesce((int)address(block + 4), 32) != 1) failed = 1;
  if (freed_address != expected_free || free_count != (expected_free != 0)) failed = 1;
  if (previous && left[0] != (next ? address(right) : 0)) failed = 1;
  if (next && right[1] != (previous ? address(left) : 0)) failed = 1;
  if ((_DWORD)g_MemPoolListHead !=
      (previous ? address(left) : (next ? address(right) : address(removed)))) failed = 1;
  if (left[3] != 0xAABBCCDDu || right[3] != 0x12345678u) failed = 1;
  if (expected_free) {
    _DWORD cursor = (_DWORD)g_MemPoolListHead;
    int seen = 0;
    while (cursor && seen < 4) {
      if (cursor == address(removed) || cursor == freed_address) failed = 1;
      if (cursor != address(left) && cursor != address(right)) { failed = 1; break; }
      cursor = *((_DWORD *)(uintptr_t)cursor);
      ++seen;
    }
    if (cursor || seen != previous + next) failed = 1;
  }
  if (failed)
    fprintf(stderr, "%s: freed=%08x expected=%08x calls=%d\n",
            name, freed_address, expected_free, free_count);
  return failed;
}
int main(void) {
  int failed = 0;
  failed += run_case("head", 0, 1);
  failed += run_case("middle", 1, 1);
  failed += run_case("tail", 1, 0);
  failed += run_case("sole retained", 0, 0);
  return failed;
}
"""


class PoolFreeCoalesceTest(unittest.TestCase):
    def test_frees_removed_pool_and_preserves_neighbor_chain(self):
        if sys.platform != "linux" or platform.machine() != "x86_64":
            self.skipTest("recovered native ABI probe requires Linux x86-64")
        stem = REPO / "src/media/00471C60_00473570_media_008"
        source = stem.with_suffix(".cpp")
        if not source.exists():
            source = stem.with_suffix(".c")
        text = source.read_text(encoding="latin-1")
        definitions = scan_definitions(text, {"Mem_PoolFreeCoalesce"})
        self.assertEqual(len(definitions), 1)
        definition = definitions[0]
        body = text[definition.start:definition.end]

        if os.environ.get("CXX"):
            compilers = [shlex.split(os.environ["CXX"])]
        else:
            compilers = []
            for family in (("g++-13", "g++"), ("clang++-18", "clang++")):
                selected = next((name for name in family if shutil.which(name)), None)
                if selected:
                    compilers.append([selected])
        if not compilers:
            self.skipTest("no supported C++ compiler available")

        with tempfile.TemporaryDirectory(prefix="clash-pool-free-") as temporary:
            directory = Path(temporary)
            probe = directory / ("probe" + source.suffix)
            probe.write_text(PRELUDE + body + HARNESS, encoding="utf-8")
            for compiler in compilers:
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization,
                                      source=source.name):
                        selected = list(compiler)
                        flags = ["-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions",
                                 "-fno-rtti", "-Werror=write-strings"]
                        if source.suffix == ".c":
                            # Transitional C source uses its existing CMake
                            # reference policy. The final .cpp path always
                            # compiles unchanged as strict GNU++20 above.
                            selected[0] = selected[0].replace("g++", "gcc").replace("clang++", "clang")
                            flags = ["-std=gnu17", "-Wno-error=int-conversion",
                                     "-Wno-error=incompatible-pointer-types"]
                        if shutil.which(selected[0]) is None:
                            self.skipTest(f"compiler unavailable: {selected[0]}")
                        binary = directory / "probe"
                        command = selected + flags + [optimization, "-fno-pie", "-no-pie",
                                                       str(probe), "-o", str(binary)]
                        compiled = subprocess.run(command, capture_output=True, text=True)
                        self.assertEqual(compiled.returncode, 0,
                                         f"{shlex.join(command)}\n{compiled.stderr}")
                        result = subprocess.run([str(binary)], capture_output=True, text=True)
                        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
