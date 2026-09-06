#!/usr/bin/env python3
"""Compile the recovered interfaces in C/C++ and exercise their C ABI.

Run in Linux/WSL with GCC, or set CC/CXX to the corresponding Clang pair:
  python3 -m unittest discover -s tests/tools -p 'test_cpp_headers.py'

The fixtures compile only interface declarations and small representative
definitions. They need no recovered runtime, display, or retail game assets.
"""

from __future__ import annotations

import os
import importlib.util
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import unittest
from unittest import mock


REPO = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location(
    "gen_cpp_headers", REPO / "tools" / "gen_subsystem_headers.py")
assert SPEC is not None and SPEC.loader is not None
GEN = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GEN)


class CppHeadersTest(unittest.TestCase):
    def setUp(self):
        self.cc = shlex.split(os.environ.get("CC", "gcc"))
        self.cxx = shlex.split(os.environ.get("CXX", "g++"))
        for command in (self.cc, self.cxx, ["nm"], ["readelf"]):
            if not command or shutil.which(command[0]) is None:
                self.skipTest(f"required tool is unavailable: {command}")
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)

    def run_command(self, command):
        result = subprocess.run(command, cwd=self.root, text=True,
                                capture_output=True, check=False)
        self.assertEqual(result.returncode, 0,
                         f"{shlex.join(str(x) for x in command)}\n"
                         f"{result.stdout}\n{result.stderr}")
        return result.stdout

    def source(self, name, text):
        path = self.root / name
        path.write_text(text, encoding="utf-8")
        return path

    def compile(self, path, *, cxx, testing=False, syntax_only=False):
        command = (self.cxx if cxx else self.cc) + [
            "-std=gnu++20" if cxx else "-std=gnu17",
            "-Werror=pragmas", "-I", str(REPO / "src")]
        if cxx:
            # Match the C reference's libc feature profile; g++ otherwise
            # defines _GNU_SOURCE and can select different CRT imports.
            command += ["-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                        "-Werror=write-strings"]
        else:
            command += ["-Werror=strict-prototypes"]
        if testing:
            command.append("-DCLASH95_TESTING")
        output = path.with_suffix(".o")
        command += ["-fsyntax-only", str(path)] if syntax_only else [
            "-c", str(path), "-o", str(output)]
        self.run_command(command)
        return output

    def test_aggregate_headers_compile_in_both_languages_and_visibility_modes(self):
        common = '''#include "recovered_all.h"
CLASH95_STATIC_ASSERT(sizeof(low32_ptr) == 4, "low32 handle width");
CLASH95_STATIC_ASSERT(sizeof(UnitSlotRecord) == 31, "unit slot stride");
CLASH95_STATIC_ASSERT(sizeof(WorldMapActionWidgetRecord) == 53, "widget stride");
'''
        c_path = self.source("headers.c", common)
        # Templates and overloads after the aggregate detect a leaked linkage
        # block, including one accidentally placed around included headers.
        cpp_path = self.source("headers.cpp", common + '''#include <type_traits>
template<class T> constexpr bool layout_is_stable = std::is_standard_layout_v<T>;
static_assert(layout_is_stable<UnitSlotRecord>);
int Header_LinkageProbe(int);
double Header_LinkageProbe(double);
''')
        for cxx, path in ((False, c_path), (True, cpp_path)):
            for testing in (False, True):
                with self.subTest(cxx=cxx, testing=testing):
                    self.compile(path, cxx=cxx, testing=testing,
                                 syntax_only=True)

    def test_cpp_definitions_inherit_linkage_and_link_to_a_c_consumer(self):
        definitions = self.source("definitions.cpp", '''#include "recovered_all.h"
int App_Shutdown(void) { return 17; }
CLASH95_INTERNAL int Runtime_DescriptorNoop(void) { return 23; }
CLASH95_TEST_VISIBLE int Runtime_ExprDescriptorNoop(int value) { return value + 1; }
''')
        consumer = self.source("consumer.c", '''#include "core/core_api.h"
#include "state/state_api.h"
#include "recovered_test_seams.h"
int main(void) {
  return App_Shutdown() != 17 || Runtime_DescriptorNoop() != 23
      || Runtime_ExprDescriptorNoop(4) != 5;
}
''')
        cpp_object = self.compile(definitions, cxx=True, testing=True)
        c_object = self.compile(consumer, cxx=False, testing=True)
        names = {line.split()[-1] for line in self.run_command(
            ["nm", "--defined-only", "-g", str(cpp_object)]).splitlines()}
        self.assertEqual(names, {"App_Shutdown", "Runtime_DescriptorNoop",
                                 "Runtime_ExprDescriptorNoop"})
        symbols = self.run_command(["readelf", "--wide", "--syms",
                                    str(cpp_object)])
        internal = next(line for line in symbols.splitlines()
                        if line.split()[-1:] == ["Runtime_DescriptorNoop"])
        self.assertIn("HIDDEN", internal)
        executable = self.root / "abi-consumer"
        self.run_command(self.cxx + [str(cpp_object), str(c_object), "-o",
                                    str(executable)])
        self.run_command([str(executable)])

    def test_unit_type_retains_c_unsigned_representation_and_sentinel_domain(self):
        common = '''#include "recovered_all.h"
CLASH95_STATIC_ASSERT(sizeof(unit_type) == sizeof(unsigned int), "unit type width");
CLASH95_STATIC_ASSERT((unit_type)-1 == 0xFFFFFFFFu, "unit type sentinel bits");
CLASH95_STATIC_ASSERT((unit_type)-1 > (unit_type)0, "unit type unsigned ordering");
'''
        c = self.source("enum-domain.c", common + '''
_Static_assert(_Generic((unit_type)0 + 0, unsigned int: 1, default: 0),
               "C enum arithmetic has unsigned integer type");
int main(void) {
  const unsigned int values[] = {0, 34, 0x7FFFFFFFu, 0x80000000u, 0xFFFFFFFFu};
  for (unsigned int i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    if ((unsigned int)(unit_type)values[i] != values[i]) return 1;
  return 0;
}
''')
        cpp = self.source("enum-domain.cpp", common + '''#include <type_traits>
static_assert(std::is_same_v<std::underlying_type_t<unit_type>, unsigned int>);
static_assert(std::is_same_v<decltype((unit_type)0 + 0), unsigned int>);
int main(void) {
  constexpr unsigned int values[] = {0, 34, 0x7FFFFFFFu, 0x80000000u, 0xFFFFFFFFu};
  for (unsigned int value : values)
    if ((unsigned int)(unit_type)value != value) return 1;
  return 0;
}
''')
        for cxx, path in ((False, c), (True, cpp)):
            with self.subTest(cxx=cxx):
                obj = self.compile(path, cxx=cxx)
                binary = path.with_suffix(".exe")
                self.run_command((self.cxx if cxx else self.cc) +
                                 [str(obj), "-o", str(binary)])
                self.run_command([str(binary)])

    def test_test_seam_definition_remains_local_in_production(self):
        path = self.source("production.cpp", '''#include "recovered_all.h"
#include "clips/004CCEC0_004CEAC0_clips_004_local.h"
#include "units/0041A960_0041C8B0_units_007_local.h"
CLASH95_TEST_VISIBLE int Runtime_ExprDescriptorNoop(int value) { return value + 1; }
CLASH95_LOCAL int Diagnostics_ForceAutoresolveEnabled(void) { return 1; }
extern "C" int Header_ProductionVisibilityProbe(void) {
  return Runtime_ExprDescriptorNoop(4) + Diagnostics_ForceAutoresolveEnabled();
}
''')
        obj = self.compile(path, cxx=True)
        symbols = self.run_command(["nm", "--defined-only", str(obj)])
        exported = self.run_command(["nm", "--defined-only", "-g", str(obj)])
        for name in ("Runtime_ExprDescriptorNoop", "Diagnostics_ForceAutoresolveEnabled"):
            with self.subTest(symbol=name):
                symbol = next(line for line in symbols.splitlines()
                              if name in line)
                self.assertEqual(symbol.split()[1:], ["t", name])
                self.assertNotIn(name, exported)

    def test_usage_scan_follows_each_source_language_during_transition(self):
        for compiler in ("gcc", "g++"):
            if shutil.which(compiler) is None:
                self.skipTest(f"usage scanner needs {compiler}")
        source_dir = self.root / "src/core"
        source_dir.mkdir(parents=True)
        (source_dir.parent / "recovered_types.h").write_text(
            "/* minimal fixture foundation */\n", encoding="utf-8")
        body = '''#ifdef __cplusplus
void Cpp_Consumer(void) { Cpp_OnlyDependency(); }
#else
void C_Consumer(void) { C_OnlyDependency(); }
#endif
'''
        for extension in ("c", "cpp"):
            (source_dir / f"entry.{extension}").write_text(body, encoding="utf-8")
        manifest = {
            "functions": [{"source": "src/core/entry.c"},
                          {"source": "src/core/entry.cpp"}],
            "state_owner": "src/core/entry.c",
        }
        with mock.patch.object(GEN, "REPO", self.root):
            tokens = GEN.scan_usage(manifest)
        self.assertIn("C_OnlyDependency", tokens["src/core/entry.c"])
        self.assertNotIn("Cpp_OnlyDependency", tokens["src/core/entry.c"])
        self.assertIn("Cpp_OnlyDependency", tokens["src/core/entry.cpp"])
        self.assertNotIn("C_OnlyDependency", tokens["src/core/entry.cpp"])


if __name__ == "__main__":
    unittest.main()
