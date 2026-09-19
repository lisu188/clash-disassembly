#!/usr/bin/env python3
"""Actual-source UnitSlot method/adapter parity against pinned production bodies."""
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
FIXTURES = Path(__file__).parent / "fixtures/class_unit_slot"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions

class UnitSlotClassTests(unittest.TestCase):
    def references(self):
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        self.assertRegex(provenance["reference_commit"], r"^[0-9a-f]{40}$")
        self.assertEqual(len(provenance["functions"]), 4)
        result = {}
        for record in provenance["functions"]:
            raw = (FIXTURES / record["fixture"]).read_bytes()
            self.assertEqual(hashlib.sha256(raw).hexdigest(), record["file_sha256"])
            text = raw.decode()
            definitions = scan_definitions(text, {record["name"]})
            self.assertEqual(len(definitions), 1)
            self.assertEqual(body_sha256(text, definitions[0]), record["body_sha256"])
            result[record["name"]] = text
        return result

    def test_reference_identity_hashes(self):
        self.assertEqual(set(self.references()), {
            "UnitSlot_ShouldGainFatigueFromLowActionPoints", "UnitSlot_CanRecoverFatigue",
            "UnitSlot_HasSevereFatigue", "UnitSlot_CycleOrderState"})

    def test_actual_methods_and_callbacks_preserve_all_record_bytes(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("supported packed low32 fixture requires Linux x86-64")
        references = self.references()
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        records = {r["name"]: r for r in manifest["functions"]}
        sources = set()
        for name in references:
            self.assertEqual(records[name]["implementation"]["kind"], "method")
            sources.update((records[name]["source"], records[name]["adapter"]["source"]))
        indexed = index_manifest_definitions(manifest, ROOT, sources)
        prefix = '#include "units/UnitSlot.hpp"\n#include "units/units_internal.h"\n#include "recovered_structs.h"\n'
        parts = {"reference": [prefix], "canonical": [prefix], "adapter": [prefix]}
        for name, text in references.items():
            renamed, count = re.subn(r"\b" + re.escape(name) + r"(?=\s*\()", "Reference_" + name, text, count=1)
            self.assertEqual(count, 1)
            parts["reference"].append(renamed)
            for role in ("canonical", "adapter"):
                resolved = indexed[(name, role)]
                wanted = records[name]["body_sha256"] if role == "canonical" else records[name]["adapter"]["body_sha256"]
                self.assertEqual(resolved.body_sha256, wanted, f"unrecorded {role} body change: {name}")
                source = (ROOT / resolved.target.source).read_text()
                parts[role].append(source[resolved.definition.start:resolved.definition.end])
        with tempfile.TemporaryDirectory(prefix="clash95-unit-slot-class-") as temporary:
            directory = Path(temporary)
            files = []
            for role, source in parts.items():
                path = directory / (role + ".cpp")
                path.write_text("\n".join(source))
                files.append(str(path))
            harness = directory / "harness.cpp"
            harness.write_text((FIXTURES / "harness.cpp").read_text())
            files.append(str(harness))
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
                        self.assertIsNotNone(shutil.which(compiler), f"required supported compiler missing: {compiler}")
                        binary = directory / (compiler + optimization)
                        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                                   "-fno-pie", "-no-pie", optimization, "-fsanitize=undefined",
                                   "-fsanitize-undefined-trap-on-error", "-Wall", "-Wextra", "-Werror",
                                   "-Wno-parentheses", "-I", str(ROOT / "src"), *files, "-o", str(binary)]
                        built = subprocess.run(command, text=True, capture_output=True, timeout=90)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        executed = subprocess.run([str(binary)], text=True, capture_output=True, timeout=90)
                        self.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
                        self.assertIn("scenarios=1048576 operations=4 alignments=16 arena_bytes=256 callback_and_method=pass", executed.stdout)

if __name__ == "__main__":
    unittest.main()
