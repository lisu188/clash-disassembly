#!/usr/bin/env python3
"""AP methods and original adapters resolve to actual manifest-backed bodies."""
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
FIXTURES = Path(__file__).parent / "fixtures/class_unit_slot_ap"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, mask_c, scan_definitions

class UnitSlotActionPointTests(unittest.TestCase):
    def references(self):
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        self.assertRegex(provenance["reference_commit"], r"^[0-9a-f]{40}$")
        self.assertEqual(len(provenance["functions"]), 2)
        result = {}
        for record in provenance["functions"]:
            raw = (FIXTURES / record["fixture"]).read_bytes()
            self.assertEqual(hashlib.sha256(raw).hexdigest(), record["file_sha256"])
            text = raw.decode()
            found = scan_definitions(text, {record["name"]})
            self.assertEqual(len(found), 1)
            self.assertEqual(body_sha256(text, found[0]), record["body_sha256"])
            result[record["name"]] = text
        self.assertEqual(hashlib.sha256((FIXTURES / "table.cpp").read_bytes()).hexdigest(),
                         provenance["table_file_sha256"])
        return provenance, result

    def test_reference_provenance(self):
        _, refs = self.references()
        self.assertEqual(set(refs), {"UnitSlot_CalcActionPointsFromFatigue", "UnitSlot_GetBaseActionPoints"})

    def test_actual_methods_adapters_and_table_accessor(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("supported packed low32/LP64 fixture requires Linux x86-64")
        provenance, references = self.references()
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        rows = {r["name"]: r for r in manifest["functions"]}
        sources = set()
        for name in references:
            self.assertEqual(rows[name]["implementation"]["kind"], "method")
            sources.update((rows[name]["source"], rows[name]["adapter"]["source"]))
        indexed = index_manifest_definitions(manifest, ROOT, sources)
        prefix = ('#include "units/UnitSlot.hpp"\n#include "units/units_internal.h"\n'
                  '#include "units/units_shared_state.h"\n#include "recovered_structs.h"\n'
                  'extern "C" const UnitTypeRuntimeCoreMetadataRecord *UnitSlot_BorrowTypeMetadata(void);\n')
        parts = {"canonical": [prefix], "adapter": [prefix],
                 "reference": [prefix, """
extern const UnitTypeRuntimeCoreMetadataRecord *fixtureMetadata;
#undef g_UnitTypeBaseActionPoints
#define g_UnitTypeBaseActionPoints ((const unsigned char *)&fixtureMetadata[0].base_action_points)
"""]}
        for name, text in references.items():
            renamed, count = re.subn(r"\b" + re.escape(name) + r"(?=\s*\()", "Reference_" + name, text, count=1)
            self.assertEqual(count, 1)
            # The frozen getter retains its original unaligned int16 read.
            parts["reference"].append('__attribute__((no_sanitize("alignment")))\n' + renamed)
            for role in ("canonical", "adapter"):
                resolved = indexed[(name, role)]
                expected = rows[name]["body_sha256"] if role == "canonical" else rows[name]["adapter"]["body_sha256"]
                self.assertEqual(resolved.body_sha256, expected, f"unrecorded {role} change: {name}")
                text = (ROOT / resolved.target.source).read_text()
                parts[role].append(text[resolved.definition.start:resolved.definition.end])
        helper = provenance["binding"]
        db = json.loads((ROOT / "data/recovered_decls.json").read_text())
        declaration = db["functions"][helper["name"]]
        self.assertEqual(declaration["class"], "helper")
        self.assertEqual(declaration["source"], helper["source"])
        text = (ROOT / declaration["source"]).read_text()
        found = scan_definitions(text, {helper["name"]})
        self.assertEqual(len(found), 1)
        self.assertEqual(body_sha256(text, found[0]), helper["body_sha256"])
        table_start = text.index("const UnitTypeRuntimeCoreMetadataRecord g_UnitTypeRuntimeCoreMetadata[")
        masked = mask_c(text)
        opening = masked.index("{", table_start)
        depth, closing = 1, opening + 1
        while depth:
            depth += (masked[closing] == "{") - (masked[closing] == "}")
            closing += 1
        closing = masked.index(";", closing) + 1
        actual_table = text[table_start:closing] + "\n"
        self.assertEqual(hashlib.sha256(actual_table.encode()).hexdigest(), provenance["table_file_sha256"],
                         "immutable metadata table changed since the migration reference")
        parts["binding"] = [prefix, text[found[0].start:found[0].end], actual_table]
        with tempfile.TemporaryDirectory(prefix="clash95-unit-slot-ap-") as temporary:
            directory = Path(temporary)
            files = []
            for role, source in parts.items():
                path = directory / (role + ".cpp")
                path.write_text("\n".join(source))
                files.append(str(path))
            harness = directory / "harness.cpp"
            harness.write_bytes((FIXTURES / "harness.cpp").read_bytes())
            files.append(str(harness))
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(compiler=compiler, optimization=optimization):
                        self.assertIsNotNone(shutil.which(compiler), f"required compiler missing: {compiler}")
                        binary = directory / (compiler + optimization)
                        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                                   "-fno-pie", "-no-pie", optimization, "-fsanitize=undefined",
                                   "-fsanitize-undefined-trap-on-error", "-Wall", "-Wextra", "-Werror",
                                   "-Wno-parentheses", "-I", str(ROOT / "src"), *files,
                                   "-Wl,--wrap=UnitSlot_BorrowTypeMetadata", "-o", str(binary)]
                        built = subprocess.run(command, text=True, capture_output=True, timeout=120)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        executed = subprocess.run([str(binary)], text=True, capture_output=True, timeout=150)
                        self.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
                        self.assertIn("cases=7143424", executed.stdout)
                        self.assertIn("alignments=16 pointer_widths=2 helper_and_callbacks=pass", executed.stdout)

if __name__ == "__main__":
    unittest.main()
