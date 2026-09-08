#!/usr/bin/env python3
"""Compare the actual queued-path footprint method/adapter to its frozen body.

The staged extraction can be checked before its coordinator updates the shared
manifest; after integration, canonical and adapter sources/hashes are resolved
through that manifest, including any later class-named relocation.
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
FIXTURES = Path(__file__).parent / "fixtures/class_queued_path"
NAME = "QueuedPath_StartsInBuildingFootprint"
QUALIFIED = "clash95::QueuedPath::" + NAME
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions


class QueuedPathClassTests(unittest.TestCase):
    def reference(self):
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        self.assertRegex(provenance["reference_commit"], r"^[0-9a-f]{40}$")
        self.assertEqual(len(provenance["functions"]), 1)
        record = provenance["functions"][0]
        self.assertEqual(record["name"], NAME)
        self.assertEqual(record["original_address"], "0x00415D00")
        raw = (FIXTURES / record["fixture"]).read_bytes()
        self.assertEqual(hashlib.sha256(raw).hexdigest(), record["file_sha256"])
        text = raw.decode()
        definitions = scan_definitions(text, {NAME})
        self.assertEqual(len(definitions), 1)
        self.assertEqual(body_sha256(text, definitions[0]), record["body_sha256"])
        return text, record

    def production(self):
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        record = next(item for item in manifest["functions"] if item["name"] == NAME)
        self.assertEqual(record["original_address"], "0x00415D00")
        if record.get("implementation", {}).get("kind") == "method":
            self.assertEqual(record["implementation"]["qualified_name"], QUALIFIED)
            sources = {record["source"], record["adapter"]["source"]}
            indexed = index_manifest_definitions(manifest, ROOT, sources)
            result = []
            for role in ("canonical", "adapter"):
                resolved = indexed[(NAME, role)]
                expected = record["body_sha256"] if role == "canonical" else record["adapter"]["body_sha256"]
                self.assertEqual(resolved.body_sha256, expected)
                text = (ROOT / resolved.target.source).read_text()
                result.append(text[resolved.definition.start:resolved.definition.end])
            return result

        # An authorized source-only extraction precedes shared manifest writes.
        # Require the still-recorded pre-extraction body identity, then locate
        # both actual definitions in the original anchor without copying them.
        _, reference_record = self.reference()
        self.assertEqual(record["body_sha256"], reference_record["body_sha256"])
        text = (ROOT / record["source"]).read_text()
        result = []
        for name in (QUALIFIED, NAME):
            definitions = scan_definitions(text, {name})
            self.assertEqual(len(definitions), 1)
            definition = definitions[0]
            result.append(text[definition.start:definition.end])
        return result

    def test_frozen_identity_and_actual_definition_resolution(self):
        self.reference()
        self.assertEqual(len(self.production()), 2)

    def test_actual_method_and_adapter_match_frozen_body_on_both_compilers(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("the supported low32 LP64 fixture requires Linux x86-64")
        reference, _ = self.reference()
        renamed, count = re.subn(r"\b" + NAME + r"(?=\s*\()", "Reference_" + NAME, reference, count=1)
        self.assertEqual(count, 1)
        parts = [r'''
#include "units/units_internal.h"
#include "units/QueuedPath.hpp"
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
int gameData;
''', '__attribute__((no_sanitize("alignment")))\n' + renamed]
        parts.extend(self.production())
        parts.append((FIXTURES / "harness.cpp").read_text())
        with tempfile.TemporaryDirectory(prefix="clash95-queued-path-") as temporary:
            directory = Path(temporary)
            source = directory / "production-and-reference.cpp"
            source.write_text("\n".join(parts))
            for compiler in ("g++-13", "clang++-18"):
                self.assertIsNotNone(shutil.which(compiler), f"required compiler missing: {compiler}")
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
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
                        self.assertRegex(executed.stdout, r"cases=26880 rebindings=26880 changed_results=[0-9]+ alignments=16 guarded_images=3")


if __name__ == "__main__":
    unittest.main()
