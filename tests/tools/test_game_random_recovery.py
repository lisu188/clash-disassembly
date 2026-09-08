#!/usr/bin/env python3
"""Actual GameRandom recovery bodies, logging boundary and x86 DIV/LEA regression."""
from __future__ import annotations
import hashlib
import json
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
FIXTURE = Path(__file__).parent / "fixtures/game_random"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions

NAMES = ("initRandomSeed", "Rng_RandRange")

def renamed(test, record):
    raw = (FIXTURE / record["fixture"]).read_bytes()
    test.assertEqual(hashlib.sha256(raw).hexdigest(), record["file_sha256"])
    source = raw.decode()
    definitions = scan_definitions(source, {record["name"]})
    test.assertEqual(len(definitions), 1)
    test.assertEqual(body_sha256(source, definitions[0]), record["body_sha256"])
    output, count = re.subn(r"\b" + re.escape(record["name"]) + r"(?=\s*\()",
                           "Before_" + record["name"], source, count=1)
    test.assertEqual(count, 1)
    return output

class GameRandomTests(unittest.TestCase):
    def test_actual_bodies_against_frozen_references_and_x86(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("requires Linux x86-64 for the original DIV/LEA instruction oracle")
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        records = {r["name"]: r for r in manifest["functions"] if r["name"] in (*NAMES, "Debug_Log")}
        self.assertEqual(set(records), {*NAMES, "Debug_Log"})
        sources = {r["source"] for r in records.values()}
        sources.update(r["adapter"]["source"] for r in records.values() if r.get("adapter"))
        indexed = index_manifest_definitions(manifest, ROOT, sources)
        headers = ['#include "units/units_internal.h"', '#include "units/units_state.h"',
                   '#include "units/units_shared_state.h"', '#include "buildings/buildings_api.h"']
        implementations = {records[name]["implementation"]["kind"] for name in NAMES}
        self.assertIn(implementations, ({"free"}, {"method"}))
        classed = implementations == {"method"}
        if classed:
            self.assertEqual({records[name]["implementation"]["header"] for name in NAMES},
                             {"src/core/GameRandom.hpp"})
            headers += ['#include "core/GameRandom.hpp"', '#define GAME_RANDOM_CLASS 1']
        common = "\n".join(headers) + "\n"
        harness = [common, (FIXTURE / "preamble.hpp").read_text()]
        harness.append("""extern "C" {
void Before_initRandomSeed(char, DWORD);
unsigned int Before_Rng_RandRange(int, int);
void __real_Debug_Log(int, char, DWORD, int, ...);
void __wrap_Debug_Log(int a1, char a2, DWORD a3, int a4, ...) {
  events.push_back({3, static_cast<uint32_t>(g_RngState), a1, a2, a3, static_cast<uint32_t>(a4)});
  __real_Debug_Log(a1, a2, a3, a4);
}
}""")
        provenance = json.loads((FIXTURE / "provenance.json").read_text())
        self.assertEqual(provenance["reference_commit"], "e13abc0266707de6291be39fdea28dca4f3e7e2b")
        self.assertEqual([r["name"] for r in provenance["functions"]], list(NAMES))
        units = {}
        # Only intentionally unrepaired frozen controls contain these defects.
        # Pattern local initialization and UBSan expose them independently.
        before_prefix = common + """
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wuninitialized"
#else
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
extern "C" { void Before_initRandomSeed(char, DWORD);
unsigned int Before_Rng_RandRange(int, int); }
"""
        for reference in provenance["functions"]:
            self.assertEqual(records[reference["name"]]["original_address"], reference["original_address"])
            units["before-" + reference["name"] + ".cpp"] = before_prefix + renamed(self, reference)
        for name in (*NAMES, "Debug_Log"):
            record = records[name]
            if classed and name in NAMES:
                self.assertEqual(record["implementation"]["qualified_name"], "clash95::GameRandom::" + name)
            for role in ("canonical", "adapter") if record.get("adapter") else ("canonical",):
                resolved = indexed[(name, role)]
                expected = record["body_sha256"] if role == "canonical" else record["adapter"]["body_sha256"]
                self.assertEqual(resolved.body_sha256, expected)
                source = (ROOT / resolved.target.source).read_text()
                units[name + "-" + role + ".cpp"] = common + source[resolved.definition.start:resolved.definition.end]
        if classed:
            registry = json.loads((ROOT / "data/game_class_registry.json").read_text())
            bindings = [b for b in registry["class_bindings"] if b["class_owner"] == "GameRandom"]
            self.assertEqual(len(bindings), 1)
            binding = bindings[0]
            source = (ROOT / binding["source"]).read_text()
            definitions = scan_definitions(source, {binding["qualified_name"]})
            self.assertEqual(len(definitions), 1)
            definition = definitions[0]
            self.assertEqual(body_sha256(source, definition), binding["body_sha256"])
            units["GameRandom-borrow.cpp"] = common + source[definition.start:definition.end]
        harness.append((FIXTURE / "harness.cpp").read_text())
        units["harness.cpp"] = "\n".join(harness)
        with tempfile.TemporaryDirectory(prefix="clash95-game-random-") as temporary:
            path = Path(temporary)
            sources = []
            for name, text in units.items():
                source = path / name
                source.write_text(text)
                sources.append(str(source))
            for compiler in ("g++-13", "clang++-18"):
                self.assertIsNotNone(shutil.which(compiler), "required compiler missing: " + compiler)
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
                        binary = path / (compiler + optimization)
                        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions",
                                   "-fno-rtti", "-fno-pie", "-no-pie", optimization,
                                   "-ftrivial-auto-var-init=pattern", "-fsanitize=undefined",
                                   "-fsanitize-undefined-trap-on-error", "-Wall", "-Wextra", "-Werror",
                                   "-I", str(ROOT / "src"), *sources, "-Wl,--wrap=Debug_Log", "-o", str(binary)]
                        built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        executed = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30)
                        self.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
                        self.assertRegex(executed.stdout, r"cases=68932 sequence_steps=4096 storage_bytes=64 clocks_per_draw=2 dispatch=" + ("direct_and_abi" if classed else "free") + r" pass")
                        print("game-random", compiler, optimization, executed.stdout.strip(), flush=True)
if __name__ == "__main__":
    unittest.main()
