#!/usr/bin/env python3
"""Actual-source DLX loader equivalence, with explicit compatibility limits.

The frozen canonical body is an oracle for this readability migration, not a
claim that every compatibility path matches the original. An independent
assembly/data-flow contract checks the common successful path. No retail assets
or original executable are needed; original instructions are not executed.
"""
from pathlib import Path
import hashlib
import json
import shutil
import subprocess
import sys
import tempfile
import unittest


REPO = Path(__file__).resolve().parents[2]
FIXTURE = Path(__file__).resolve().parent / "fixtures/dlx_cached_entry"
sys.path.insert(0, str(REPO / "tools"))
from split_source_index import scan_definitions, body_sha256  # noqa: E402


def actual_definition(text, name):
    definitions = scan_definitions(text, {name})
    if len(definitions) != 1:
        raise AssertionError(f"expected one actual definition of {name}")
    definition = definitions[0]
    return text[definition.start:definition.end]


class DLXCachedEntryTests(unittest.TestCase):
    def test_frozen_oracle_provenance(self):
        provenance = json.loads((FIXTURE / "provenance.json").read_text())
        frozen = (FIXTURE / "baseline.cpp").read_bytes()
        self.assertEqual(hashlib.sha256(frozen).hexdigest(), provenance["fixture_sha256"])
        text = frozen.decode("utf-8")
        definition = scan_definitions(text, {provenance["function"]})[0]
        self.assertEqual(body_sha256(text, definition), provenance["source_body_sha256"])
        self.assertEqual(provenance["commit"], "5376757fe8cefd1af5eab0907601fab3ab9bc121")

    def check_compiler(self, candidates):
        if not sys.platform.startswith("linux"):
            self.skipTest("recovered low32 executable checks run in Linux/WSL")
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((FIXTURE / "provenance.json").read_text())
        original = (FIXTURE / "baseline.cpp").read_text(encoding="utf-8")
        actual = actual_definition(
            (REPO / provenance["source"]).read_text(encoding="utf-8"),
            provenance["function"],
        )
        source = (FIXTURE / "harness.cpp").read_text(encoding="utf-8")
        source = source.replace("@FROZEN_BODY@", original).replace("@ACTUAL_BODY@", actual)
        with tempfile.TemporaryDirectory(prefix="clash-dlx-cached-entry-") as temporary:
            directory = Path(temporary)
            harness = directory / "harness.cpp"
            harness.write_text(source, encoding="utf-8")
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / (Path(compiler).name + optimization)
                    command = [
                        compiler, "-std=gnu++20", optimization, "-fno-pie", "-no-pie",
                        "-Wall", "-Wextra", "-Werror", "-I", str(REPO / "src"),
                        str(harness), "-o", str(executable),
                    ]
                    built = subprocess.run(command, capture_output=True, text=True)
                    self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                    ran = subprocess.run([str(executable)], capture_output=True, text=True)
                    self.assertEqual(ran.returncode, 0, ran.stdout + ran.stderr)
                    self.assertIn("36 cases; actual/frozen traces and byte contracts agree", ran.stdout)

    def test_actual_loader_gcc(self):
        self.check_compiler(("g++-13", "g++"))

    def test_actual_loader_clang(self):
        self.check_compiler(("clang++-18", "clang++"))

    def test_contract_detects_ownership_and_stale_size_regressions(self):
        if not sys.platform.startswith("linux"):
            self.skipTest("recovered low32 executable checks run in Linux/WSL")
        compiler = shutil.which("g++-13") or shutil.which("g++")
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: g++-13, g++")
        original = (FIXTURE / "baseline.cpp").read_text(encoding="utf-8")
        template = (FIXTURE / "harness.cpp").read_text(encoding="utf-8")
        mutants = {
            "ownership": original.replace(
                "  *(_DWORD *)(uintptr_t)(sprite + 10) = 0;",
                "  *(_DWORD *)(uintptr_t)(sprite + 18) = 1;\n"
                "  *(_DWORD *)(uintptr_t)(sprite + 10) = 0;",
            ),
            "cached-size": original.replace(
                "payload_size = *(_DWORD *)(uintptr_t)(sprite + 14) - 10;",
                "payload_size = entry_end_offset - entry_offset - 10;",
            ),
        }
        with tempfile.TemporaryDirectory(prefix="clash-dlx-cached-entry-mutants-") as temporary:
            directory = Path(temporary)
            for name, mutant in mutants.items():
                with self.subTest(mutant=name):
                    self.assertNotEqual(original, mutant)
                    harness = directory / (name + ".cpp")
                    harness.write_text(
                        template.replace("@FROZEN_BODY@", original).replace("@ACTUAL_BODY@", mutant),
                        encoding="utf-8",
                    )
                    executable = directory / name
                    built = subprocess.run(
                        [compiler, "-std=gnu++20", "-O2", "-fno-pie", "-no-pie",
                         "-I", str(REPO / "src"), str(harness), "-o", str(executable)],
                        capture_output=True, text=True,
                    )
                    self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                    ran = subprocess.run([str(executable)], capture_output=True, text=True)
                    self.assertNotEqual(ran.returncode, 0, "negative control escaped the contract")
                    expected = "ownership/canary" if name == "ownership" else "post-header uint32"
                    self.assertIn(expected, ran.stderr)


if __name__ == "__main__":
    unittest.main()
