#!/usr/bin/env python3
"""Compare production class methods and legacy adapters to frozen free bodies.

All generated translation units and executables live in a temporary directory.
Production definitions are located through the manifest, so source relocation
does not turn this into a stale implementation-copy test. No retail assets.
"""

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
FIXTURES = Path(__file__).parent / "fixtures/class_unit_pilot"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions


class UnitClassDifferentialTests(unittest.TestCase):
    def fixture_bodies(self):
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

    def test_frozen_fixture_hashes_and_identity_provenance(self):
        self.assertEqual(set(self.fixture_bodies()), {
            "UnitStack_GetMinCurrentActionPoints", "UnitStack_HasReadyUnits",
            "UnitStack_HasBuilder", "QueuedPath_StartsAtTile"})

    def test_actual_methods_and_abi_match_reference_on_both_compilers(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("the supported low32 LP64 runtime fixture requires Linux x86-64")
        references = self.fixture_bodies()
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        records = {record["name"]: record for record in manifest["functions"]}
        sources = set()
        for name in references:
            self.assertEqual(records[name]["implementation"]["kind"], "method")
            sources.update((records[name]["source"], records[name]["adapter"]["source"]))
        indexed = index_manifest_definitions(manifest, ROOT, sources)
        source_parts = [r'''
#include "units/units_internal.h"
#include "recovered_structs.h"
#include "units/UnitStack.hpp"
#include "units/QueuedPath.hpp"
#include <sys/mman.h>
#include <limits.h>
int gameData;
''']
        for name, text in references.items():
            renamed, count = re.subn(r"\b" + re.escape(name) + r"(?=\s*\()",
                                     "Reference_" + name, text, count=1)
            self.assertEqual(count, 1)
            # The frozen x86 reference deliberately retains its historical
            # unaligned dereferences. Only the new methods/adapters must meet
            # the alignment-safe class interface, so exempt the reference.
            source_parts.append('__attribute__((no_sanitize("alignment")))\n' + renamed)
        for name in references:
            for role in ("canonical", "adapter"):
                resolved = indexed[(name, role)]
                wanted_hash = records[name]["body_sha256"] if role == "canonical" else records[name]["adapter"]["body_sha256"]
                self.assertEqual(resolved.body_sha256, wanted_hash,
                                 f"unrecorded {role} source change for {name}")
                text = (ROOT / resolved.target.source).read_text()
                definition = resolved.definition
                source_parts.append(text[definition.start:definition.end])
        source_parts.append((FIXTURES / "harness.cpp").read_text())
        with tempfile.TemporaryDirectory(prefix="clash95-class-unit-") as temporary:
            directory = Path(temporary)
            source = directory / "production-and-reference.cpp"
            source.write_text("\n".join(source_parts))
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
                        if shutil.which(compiler) is None:
                            self.skipTest(f"required supported compiler not installed: {compiler}")
                        binary = directory / (compiler + optimization)
                        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions",
                                   "-fno-rtti", "-fno-pie", "-no-pie", optimization,
                                   "-fsanitize=alignment", "-fsanitize-undefined-trap-on-error",
                                   "-Wall", "-Wextra", "-Werror", "-I", str(ROOT / "src"),
                                   str(source), "-o", str(binary)]
                        built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        executed = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30)
                        self.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
                        self.assertIn("stack_cases=6176 path_cases=38928 alignments=16", executed.stdout)


if __name__ == "__main__":
    unittest.main()
