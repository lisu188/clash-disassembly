#!/usr/bin/env python3
"""Recovered regroup body against original-measured synthetic records.

The expected records were measured by executing the original i386 instructions.
This public regression requires no original executable, Wine, or retail assets.
Regroup's external movement/lifecycle boundaries are deliberately scripted; this
does not assert equivalence of those callees or their diagnostic-only contexts.
"""
from __future__ import annotations
import gzip
import hashlib
import json
import os
from pathlib import Path
import platform
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(os.environ.get("CLASH95_SOURCE_ROOT", Path(__file__).resolve().parents[2]))
FIXTURE = Path(__file__).parent / "fixtures/unit_regroup_recovery"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import scan_definitions

FAMILIES = {
    "regroup": ("UnitStack_RegroupWithOtherStackByHealth",),
}


class UnitRegroupRecoveryTests(unittest.TestCase):
    def test_actual_regroup_body_matches_original_measurements(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("requires the Linux x86-64 low32 reconstruction ABI")
        provenance = json.loads((FIXTURE / "provenance.json").read_text())
        for record in provenance["fixtures"]:
            self.assertEqual(hashlib.sha256((FIXTURE / record["file"]).read_bytes()).hexdigest(),
                             record["sha256"], record["file"])
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        names = {name for family in FAMILIES.values() for name in family}
        records = {r["name"]: r for r in manifest["functions"] if r["name"] in names}
        self.assertEqual(set(records), names)
        # This is the behavior-repair gate before extraction. Extend direct
        # method dispatch explicitly when these identities migrate to classes.
        self.assertEqual({r["implementation"]["kind"] for r in records.values()}, {"free"})
        indexed = index_manifest_definitions(manifest, ROOT, {r["source"] for r in records.values()})
        common = (FIXTURE / "native-prelude.hpp").read_text()
        with tempfile.TemporaryDirectory(prefix="clash95-unit-regroup-") as directory:
            temporary = Path(directory)
            for family, family_names in FAMILIES.items():
                sources = []
                for name in family_names:
                    resolved = indexed[(name, "canonical")]
                    self.assertEqual(resolved.body_sha256, records[name]["body_sha256"], name)
                    text = (ROOT / resolved.target.source).read_text()
                    source = temporary / (name + ".cpp")
                    source.write_text(common + text[resolved.definition.start:resolved.definition.end])
                    sources.append(str(source))
                if family == "regroup":
                    text = (ROOT / "src/compatibility/decomp_runtime_stubs.cpp").read_text()
                    definitions = scan_definitions(text, {"abs32"})
                    self.assertEqual(len(definitions), 1)
                    definition = definitions[0]
                    source = temporary / "abs32.cpp"
                    source.write_text(common + text[definition.start:definition.end])
                    sources.append(str(source))
                harness = temporary / (family + "-harness.cpp")
                harness.write_text(common + (FIXTURE / (family + "-native-harness.cpp")).read_text())
                sources.append(str(harness))
                golden = json.loads(gzip.decompress((FIXTURE / (family + "-original-measured.json.gz")).read_bytes()))
                for compiler in ("g++-13", "clang++-18"):
                    self.assertIsNotNone(shutil.which(compiler), compiler)
                    for optimization in ("-O0", "-O2"):
                        with self.subTest(family=family, compiler=compiler, optimization=optimization):
                            binary = temporary / (family + compiler + optimization)
                            command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                                       "-fno-pie", "-no-pie", "-fno-exceptions", "-fno-rtti",
                                       "-fno-builtin", "-ftrivial-auto-var-init=pattern",
                                       "-fsanitize=undefined", "-fsanitize-undefined-trap-on-error",
                                       "-I", str(ROOT / "src"), *sources, "-o", str(binary)]
                            built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                            self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                            run = subprocess.run([str(binary)], capture_output=True, timeout=60)
                            self.assertEqual(run.returncode, 0, run.stderr.decode(errors="replace"))
                            size = golden["record_bytes"]
                            self.assertEqual(len(run.stdout), golden["cases"] * size)
                            mismatches = [i for i, expected in enumerate(golden["case_sha256"])
                                          if hashlib.sha256(run.stdout[i * size:(i + 1) * size]).hexdigest() != expected]
                            self.assertEqual(mismatches, [], "first mismatches: " + repr(mismatches[:20]))
                            self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), golden["stream_sha256"])
                            print(f"unit-{family} {compiler} {optimization}: {golden['cases']} original-measured cases PASS", flush=True)


if __name__ == "__main__":
    unittest.main()
