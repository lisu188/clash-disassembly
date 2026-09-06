"""Compile and compare actual generated class bodies using temporary fixtures."""

import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock


REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))
import migrate_game_class_bodies as migration
import audit_header_surface as header_audit
import gen_subsystem_headers as header_generation
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions


class ClassBodyMigrationTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="clash-class-migration-")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        (self.root / "data").mkdir()
        (self.root / "src/units").mkdir(parents=True)
        (self.root / "src/recovered_types.h").write_text("#pragma once\n#define CLASH95_INTERNAL\n#include <cstdint>\n")
        (self.root / "src/recovered_layout.h").write_text('#pragma once\n#include "recovered_types.h"\n')

    def fixture(self, bodies=None, globals_=None, macros="", extra_functions=""):
        if bodies is None:
            bodies = {"Probe_Increment": "int Probe_Increment(int amount)\n{ counter += amount; values[1] += counter; return values[1]; }",
                      "Probe_Peek": "int Probe_Peek(void)\n{ return counter + values[1]; }"}
        if globals_ is None:
            globals_ = {"counter": "extern int counter;", "values": "extern int values[3];"}
        definitions = []
        for name, declaration in globals_.items():
            if name == "values":
                definitions.append("int values[3] = {3, 5, 7};")
            elif "*" in declaration:
                definitions.append("int backing_value = 9; int *" + name + " = &backing_value;")
            else:
                definitions.append(declaration.removeprefix("extern ").removesuffix(";") + " = 2;")
        declarations = {name: {"class": "manifest", "home": "units", "decl": body[:body.index("{")].strip() + ";"} for name, body in bodies.items()}
        header = '#pragma once\n#include "../recovered_layout.h"\nextern "C" {\n' + "\n".join(item["decl"] for item in declarations.values()) + "\n}\n"
        (self.root / "src/units/public.h").write_text(header)
        source = '#include "public.h"\n' + macros + "\n".join(definitions) + "\n" + extra_functions + "\n" + "\n\n".join(bodies.values()) + "\n"
        (self.root / "src/units/original.cpp").write_text(source)
        indexed = {definition.name: definition for definition in scan_definitions(source, set(bodies))}
        records, entries = [], []
        for index, name in enumerate(bodies):
            records.append({"name": name, "original_address": f"0x{0x410000 + index * 16:08X}",
                            "source": "src/units/original.cpp", "subsystem": "units", "linkage": "external",
                            "original_source": "src/recovered/original.inc.c", "body_sha256": body_sha256(source, indexed[name]),
                            "implementation": {"kind": "free", "qualified_name": name}})
            entries.append({"name": name, "classification": "game-method", "class_owner": "Probe",
                            "method": name, "logical_subsystem": "units", "final_header": "src/units/Probe.hpp",
                            "final_source": "src/units/Probe.cpp"})
        self.manifest = {"schema_version": 3, "function_count": len(records), "source_file_count": 1, "functions": records}
        self.registry = {"schema_version": 1, "identities": entries, "helpers": []}
        self.declarations = {"functions": declarations, "globals": {name: {"decl": declaration} for name, declaration in globals_.items()}}
        self.save_metadata()

    def save_metadata(self):
        for name, data in (("recovered_sources", self.manifest), ("game_class_registry", self.registry), ("recovered_decls", self.declarations)):
            (self.root / f"data/{name}.json").write_text(json.dumps(data, indent=2) + "\n")

    def snapshot(self):
        return {path.relative_to(self.root).as_posix(): path.read_bytes() for path in self.root.rglob("*") if path.is_file()}

    def compile_run(self, compiler, test_main, optimization="-O0", extra_flags=()):
        (self.root / "main.cpp").write_text('#include "src/units/public.h"\n' + test_main)
        sources = sorted(str(path) for path in (self.root / "src/units").glob("*.cpp"))
        binary = self.root / "run"
        process = subprocess.run([compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                                  "-Wall", "-Wextra", "-Werror", "-fno-exceptions", "-fno-rtti",
                                  "-fno-pie", "-no-pie", "-D_REENTRANT", *extra_flags, *sources,
                                  str(self.root / "main.cpp"), "-o", str(binary)], capture_output=True, text=True, timeout=60)
        self.assertEqual(process.returncode, 0, process.stderr)
        process = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30)
        self.assertEqual(process.returncode, 0, process.stderr)
        return process.stdout

    def assert_header_policy(self):
        manifest = json.loads((self.root / "data/recovered_sources.json").read_text())
        with (mock.patch.object(header_audit, "REPO", self.root),
              mock.patch.object(header_audit, "DECLS", self.root / "data/recovered_decls.json"),
              mock.patch.object(header_generation, "REPO", self.root)):
            self.assertEqual(header_audit.class_header_policy_errors(manifest), [])

    def test_default_cli_is_read_only_and_global_bindings_compile_on_both_profiles(self):
        self.fixture()
        before = self.snapshot()
        process = subprocess.run([sys.executable, str(REPO / "tools/migrate_game_class_bodies.py"), "--root", str(self.root), "--class", "Probe"],
                                 capture_output=True, text=True)
        self.assertEqual(process.returncode, 0, process.stdout)
        self.assertFalse(json.loads(process.stdout)["written"])
        self.assertEqual(self.snapshot(), before)
        main = 'extern int counter; extern int values[3]; int main() { if (Probe_Increment(4)!=11) return 1; counter=20; return Probe_Peek()!=31 || values[0]!=3 || values[2]!=7; }\n'
        compilers = [path for name in ("g++-13", "clang++-18") if (path := shutil.which(name))]
        self.assertEqual(len(compilers), 2, "both supported compilers are required for class extraction tests")
        for compiler in compilers:
            self.compile_run(compiler, main)
        migration.make_plan(self.root, "Probe").apply()
        generated = (self.root / "src/units/Probe.hpp").read_text()
        self.assertIn("state_type_1 = int[3]", generated)
        self.assertIn("state_type_0 &state_field_0_", generated)
        self.assertNotIn("counter", generated)
        self.assertNotIn("values", generated)
        self.assertIn("static Probe borrow() noexcept;", generated)
        self.assertIn("return Probe(::counter, ::values);", (self.root / "src/units/original.cpp").read_text())
        self.assert_header_policy()
        binding = json.loads((self.root / "data/game_class_registry.json").read_text())["class_bindings"][0]
        self.assertEqual(binding["source"], "src/units/original.cpp")
        self.assertEqual(binding["referenced_globals"], ["counter", "values"])
        self.assertNotIn("original_address", binding)
        factory_source = (self.root / binding["source"]).read_text()
        factory = scan_definitions(factory_source, {binding["qualified_name"]})
        self.assertEqual(len(factory), 1)
        self.assertEqual(binding["body_sha256"], body_sha256(factory_source, factory[0]))
        for compiler in compilers:
            self.compile_run(compiler, main)
        migrated = json.loads((self.root / "data/recovered_sources.json").read_text())
        resolved = index_manifest_definitions(migrated, self.root)
        for record in migrated["functions"]:
            self.assertEqual(record["body_sha256"], resolved[(record["name"], "canonical")].body_sha256)
            self.assertEqual(record["adapter"]["body_sha256"], resolved[(record["name"], "adapter")].body_sha256)
        migration.make_plan(self.root, "Probe", "relocate").apply()
        self.assert_header_policy()
        for compiler in compilers:
            self.compile_run(compiler, main)
        old = (self.root / "src/units/original.cpp").read_text()
        self.assertIn("int values[3] = {3, 5, 7};", old)
        self.assertNotIn("int clash95::Probe::Probe_Increment", old)
        self.assertIn("clash95::Probe clash95::Probe::borrow() noexcept", old)
        self.assertNotIn("::borrow() noexcept", (self.root / "src/units/Probe.cpp").read_text())
        self.assertIn("int clash95::Probe::Probe_Increment", (self.root / "src/units/Probe.cpp").read_text())
        relocated = (self.root / "src/units/Probe.cpp").read_text()
        self.assertEqual(relocated.count(migration.INCLUDES_BEGIN), 1)
        self.assertEqual(relocated.count(migration.INCLUDES_END), 1)
        self.assertEqual(json.loads((self.root / "data/game_class_registry.json").read_text())["class_bindings"], [binding])
        self.assertEqual(binding["body_sha256"], body_sha256(old, scan_definitions(old, {binding["qualified_name"]})[0]))

    def test_stateless_class_and_callback_address_use_global_adapter(self):
        self.fixture({"Probe_Increment": "int Probe_Increment(int amount)\n{ return amount+1; }",
                      "Probe_Peek": "int Probe_Peek(void)\n{ return (&Probe_Increment)(4); }"}, {})
        migration.make_plan(self.root, "Probe").apply()
        self.assertIn("(&::Probe_Increment)(4)", (self.root / "src/units/original.cpp").read_text())
        self.compile_run(shutil.which("g++-13"), "int main() { return Probe_Peek()!=5; }\n")

    def test_same_class_calls_and_recursion_are_direct_with_abi_boundaries_preserved(self):
        bodies = {
            "Probe_Mark": "int Probe_Mark(int tag)\n{ counter=counter*10+tag; return tag; }",
            "Probe_Combine": "int Probe_Combine(int first, int second, int third)\n{ return first*100+second*10+third; }",
            "Probe_Run": "int Probe_Run(void)\n{ return Probe_Combine(Probe_Mark(1),Probe_Mark(2),Probe_Mark(3)); }",
            "Probe_Recurse": "int Probe_Recurse(int depth)\n{ if (depth<=0) return counter; return depth+Probe_Recurse(depth-1); }",
            "Probe_Explicit": "int Probe_Explicit(void)\n{ return ::Probe_Recurse(2); }",
            "Probe_Variadic": "int Probe_Variadic(int first, ...)\n{ return first; }",
            "Probe_VariadicRun": "int Probe_VariadicRun(void)\n{ return Probe_Variadic(Probe_Mark(4),Probe_Mark(5),Probe_Mark(6)); }",
            "Probe_CallbackAddress": "intptr_t Probe_CallbackAddress(void)\n{ return (intptr_t)&Probe_Combine; }",
            "Probe_Indirect": "int Probe_Indirect(void)\n{ return (Probe_Combine)(1,2,3); }",
            "Probe_FromTable": "int Probe_FromTable(void)\n{ int (*callbacks[1])(int,int,int)={Probe_Combine}; return callbacks[0](1,2,3); }",
        }
        self.fixture(bodies, {"counter": "extern int counter;"})
        harness = r'''
#include <cstdio>
extern int counter;
int main() {
  counter=0; int combined=Probe_Run(); int fixedOrder=counter;
  counter=0; int variadic=Probe_VariadicRun(); int variadicOrder=counter;
  counter=7; int recursive=Probe_Recurse(6); int explicitCall=Probe_Explicit();
  int callback=(Probe_CallbackAddress()==(intptr_t)&Probe_Combine);
  int indirect=Probe_Indirect(); int table=Probe_FromTable();
  if (combined!=123 || variadic!=4 || recursive!=28 || explicitCall!=10
      || !callback || indirect!=123 || table!=123 || counter!=7) return 1;
  std::printf("%d %d %d %d %d %d %d %d %d\n",combined,fixedOrder,variadic,variadicOrder,
              recursive,explicitCall,callback,indirect,table);
  return 0;
}
'''
        baseline = {}
        for stage in ("before", "extract", "relocate"):
            if stage != "before":
                plan = migration.make_plan(self.root, "Probe", stage)
                if stage == "extract":
                    text = plan.changes["src/units/original.cpp"]
                    self.assertIn("this->Probe_Combine(this->Probe_Mark(1),this->Probe_Mark(2),this->Probe_Mark(3))", text)
                    self.assertIn("depth+this->Probe_Recurse(depth-1)", text)
                    self.assertIn("return this->Probe_Recurse(2)", text)
                    self.assertIn("::Probe_Variadic(this->Probe_Mark(4),this->Probe_Mark(5),this->Probe_Mark(6))", text)
                    self.assertIn("(intptr_t)&::Probe_Combine", text)
                    self.assertIn("(::Probe_Combine)(1,2,3)", text)
                    self.assertEqual({(item["caller"],item["callee"],item["kind"]) for item in plan.call_boundaries}, {
                        ("Probe_VariadicRun","Probe_Variadic","variadic-callee"),
                        ("Probe_CallbackAddress","Probe_Combine","function-address"),
                        ("Probe_Indirect","Probe_Combine","function-value-or-indirect-call"),
                        ("Probe_FromTable","Probe_Combine","function-value-or-indirect-call"),
                    })
                    self.assertEqual(plan.summary()["retained_same_class_boundaries"], plan.call_boundaries)
                plan.apply()
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(stage=stage, compiler=compiler, optimization=optimization):
                        output = self.compile_run(compiler, harness, optimization)
                        key = compiler, optimization
                        if stage == "before":
                            baseline[key] = output
                        else:
                            # The language does not order independent arguments.
                            # Compare each compiler/profile to its own original
                            # trace, including every unused variadic expression.
                            self.assertEqual(output, baseline[key])

    def test_class_includes_remain_inside_regenerable_marker_blocks(self):
        self.fixture()
        source = self.root / "src/units/original.cpp"
        source.write_text(source.read_text().replace('#include "public.h"\n',
                          migration.INCLUDES_BEGIN + '\n#include "public.h"\n' + migration.INCLUDES_END + '\n'))
        migration.make_plan(self.root, "Probe").apply()
        original = source.read_text()
        include = '#include "Probe.hpp"'
        self.assertLess(original.index(migration.INCLUDES_BEGIN), original.index(include))
        self.assertLess(original.index(include), original.index(migration.INCLUDES_END))
        migration.make_plan(self.root, "Probe", "relocate").apply()
        relocated = (self.root / "src/units/Probe.cpp").read_text()
        replacement = migration.INCLUDES_BEGIN + '\n#include "Probe.hpp"\n' + migration.INCLUDES_END
        regenerated = header_generation.replace_tu_include_block(relocated, replacement)
        self.assertIn("int clash95::Probe::Probe_Increment", regenerated)

    def test_local_static_true_varargs_and_register_calls_refuse_entire_class(self):
        cases = ["int Probe_Peek(void)\n{ static int value=0; return ++value; }",
                 "int Probe_Peek(int value, ...)\n{ va_list args; va_start(args, value); return va_arg(args,int); }",
                 "int __fastcall Probe_Peek(int value)\n{ return value; }"]
        for body in cases:
            with self.subTest(body=body):
                self.fixture({"Probe_Increment": "int Probe_Increment(int amount)\n{ return amount+1; }", "Probe_Peek": body}, {})
                before = self.snapshot()
                with self.assertRaises(migration.MigrationError):
                    migration.make_plan(self.root, "Probe")
                self.assertEqual(self.snapshot(), before)

    def test_unused_variadic_values_preserve_caller_side_effects(self):
        self.fixture({"Probe_Increment": "int Probe_Increment(int amount, ...)\n{ return amount+1; }"}, {})
        for stage in ("extract", "relocate"):
            migration.make_plan(self.root, "Probe", stage).apply()
            self.assertNotIn("...", (self.root / "src/units/Probe.hpp").read_text())
            canonical = self.root / ("src/units/original.cpp" if stage == "extract" else "src/units/Probe.cpp")
            text = canonical.read_text()
            method, = scan_definitions(text, {"clash95::Probe::Probe_Increment"})
            self.assertNotIn("...", text[method.start:method.opening_brace])
            self.assertIn("Probe_Increment(int amount, ...)", (self.root / "src/units/original.cpp").read_text())
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    self.compile_run(compiler, '#include "src/units/Probe.hpp"\n#include <type_traits>\n'
                                     'static_assert(std::is_same_v<decltype(&clash95::Probe::Probe_Increment),int(clash95::Probe::*)(int)>);\n'
                                     'int main() { int side=0; int value=Probe_Increment(2,++side); '
                                     'return value!=3 || side!=1 || clash95::Probe::borrow().Probe_Increment(2)!=3; }\n', optimization)

    def test_global_pointer_is_borrowed_by_reference(self):
        self.fixture({"Probe_Increment": "int Probe_Increment(int amount)\n{ *pointer += amount; return *pointer; }"}, {"pointer": "extern int *pointer;"})
        migration.make_plan(self.root, "Probe").apply()
        self.compile_run(shutil.which("g++-13"), "extern int *pointer; int main() { int value=2; pointer=&value; return Probe_Increment(4)!=6 || value!=6; }\n")

    def test_transitive_macro_state_is_expanded_and_borrowed_without_macro_leaks(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return GET_COUNT; }"}, {"counter": "extern int counter;"},
                     macros="#define GET_COUNT GET_VALUE\n#define GET_VALUE counter\n")
        before = self.snapshot()
        plan = migration.make_plan(self.root, "Probe")
        self.assertEqual(self.snapshot(), before)
        self.assertEqual(plan.bindings, ["counter"])
        self.assertEqual(plan.macro_expansions[0]["expanded"], "counter")
        self.assertEqual(len(plan.macro_expansions[0]["verified_profiles"]), 8)
        plan.apply()
        migration.make_plan(self.root, "Probe", "relocate").apply()
        relocated = (self.root / "src/units/Probe.cpp").read_text()
        self.assertIn("return this->state_field_0_;", relocated)
        self.assertNotIn("GET_COUNT", relocated)
        self.assertNotIn("#define", relocated)
        for compiler in ("g++-13", "clang++-18"):
            self.compile_run(compiler, "extern int counter; int main() { counter=17; return Probe_Peek()!=17; }\n")

    def test_real_preprocessing_resolves_token_pasting_and_inactive_definitions(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return READ_STATE; }"}, {"gameData": "extern int gameData;"},
                     macros="#define JOIN(a,b) a ## b\n#if 0\n#define READ_STATE g_Unknown\n#else\n#define READ_STATE JOIN(game, Data)\n#endif\n")
        plan = migration.make_plan(self.root, "Probe")
        self.assertEqual(plan.bindings, ["gameData"])
        self.assertEqual(plan.macro_expansions[0]["expanded"], "gameData")

    def test_angle_include_and_compact_function_macro_are_discovered(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return READ_STATE(); }"},
                     {"counter": "extern int counter;"}, macros="#include <binding_macros.h>\n")
        (self.root / "src/binding_macros.h").write_text("#define READ_STATE()counter\n")
        plan = migration.make_plan(self.root, "Probe")
        self.assertEqual(plan.bindings, ["counter"])
        self.assertEqual(plan.macro_expansions[0]["expanded"], "counter")

    def test_stringified_global_and_callback_names_remain_literal_spellings(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ const char *label=TEXT(counter); return label[0]=='c' && sizeof(TEXT(Probe_Peek))==11; }"},
                     {"counter": "extern int counter;"}, macros="#define TEXT(name) #name\n")
        plan = migration.make_plan(self.root, "Probe")
        self.assertEqual(plan.bindings, [])
        self.assertEqual([item["expanded"] for item in plan.macro_expansions], ['"counter"', '"Probe_Peek"'])
        plan.apply()
        migration.make_plan(self.root, "Probe", "relocate").apply()
        for compiler in ("g++-13", "clang++-18"):
            self.compile_run(compiler, "int main() { return Probe_Peek()!=1; }\n")

    def test_profile_dependent_macro_state_refuses_without_writes(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return READ_STATE; }"}, {"counter": "extern int counter;"},
                     macros="#ifdef __clang__\n#define READ_STATE (counter+1)\n#else\n#define READ_STATE counter\n#endif\n")
        before = self.snapshot()
        with self.assertRaisesRegex(migration.MigrationError, "differs across compiler/build profiles"):
            migration.make_plan(self.root, "Probe")
        self.assertEqual(self.snapshot(), before)

    def test_context_macros_and_invocation_boundary_changes_refuse(self):
        examples = [("#define READ_STATE (counter + __LINE__)\n", "READ_STATE", "context-sensitive"),
                    ("#define CALL(x) (counter + (x))\n#define FACTORY() CALL\n", "FACTORY()(2)", "invocation boundaries")]
        for macros, expression, message in examples:
            with self.subTest(expression=expression):
                self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return " + expression + "; }"},
                             {"counter": "extern int counter;"}, macros=macros)
                before = self.snapshot()
                with self.assertRaisesRegex(migration.MigrationError, message):
                    migration.make_plan(self.root, "Probe")
                self.assertEqual(self.snapshot(), before)

    def test_packed_alias_writes_and_live_pointer_loads_match_before_extract_and_relocate(self):
        body = """int Probe_Transfer(unsigned char *replacement, int index)
{
  int before = READ_WORD(index++);
  currentBytes = replacement;
  READ_DWORD(index) += before;
  return READ_WORD(index - 1) + index;
}"""
        reference = body.replace("Probe_Transfer", "Reference_Transfer", 1)
        macros = ("#define RECORD_WORD(base,index) (*(packed_word *)((base) + 3 + 7 * (index)))\n"
                  "#define READ_WORD(index) RECORD_WORD(currentBytes,index)\n"
                  "#define READ_DWORD(index) (*(packed_dword *)(currentBytes + 5 + 7 * (index)))\n")
        self.fixture({"Probe_Transfer": body}, {"currentBytes": "extern unsigned char *currentBytes;"}, macros=macros,
                     extra_functions=reference)
        layout = self.root / "src/recovered_layout.h"
        layout.write_text(layout.read_text() + "typedef uint16_t packed_word __attribute__((aligned(1), may_alias));\n"
                          "typedef uint32_t packed_dword __attribute__((aligned(1), may_alias));\n")
        source = self.root / "src/units/original.cpp"
        source.write_text(source.read_text().replace("int backing_value = 9; int *currentBytes = &backing_value;",
                                                     "unsigned char backing_value[128]; unsigned char *currentBytes = backing_value;"))
        harness = r'''
#include <cstring>
#if __has_include("src/units/Probe.hpp")
#include "src/units/Probe.hpp"
#endif
extern unsigned char *currentBytes;
int Reference_Transfer(unsigned char *, int);
int main() {
  unsigned char referenceA[160], referenceB[160], actualA[160], actualB[160];
  for (int offset=0; offset<16; ++offset) {
    for (int index=0; index<9; ++index) {
      for (int kind=0; kind<2; ++kind) {
        for (int i=0; i<160; ++i) { referenceA[i]=(i*17+offset)&255; referenceB[i]=(i*29+index)&255; }
        memcpy(actualA,referenceA,sizeof actualA); memcpy(actualB,referenceB,sizeof actualB);
        currentBytes=referenceA+offset;
        int expected=Reference_Transfer(referenceB+offset,index);
        currentBytes=actualA+offset;
        int result;
#if __has_include("src/units/Probe.hpp")
        if (kind) {
          auto borrowed=clash95::Probe::borrow();
          // Rebind after borrowing: the object must retain the pointer cell.
          currentBytes=actualB+offset;
          currentBytes=actualA+offset;
          result=borrowed.Probe_Transfer(actualB+offset,index);
        } else
#endif
          result=Probe_Transfer(actualB+offset,index);
        if (result!=expected || currentBytes!=actualB+offset
            || memcmp(actualA,referenceA,sizeof actualA) || memcmp(actualB,referenceB,sizeof actualB)) return 1;
      }
    }
  }
  return 0;
}
'''
        for stage in ("before", "extract", "relocate"):
            if stage != "before":
                plan = migration.make_plan(self.root, "Probe", stage)
                if stage == "extract":
                    self.assertEqual(plan.bindings, ["currentBytes"])
                    self.assertTrue(any("packed_word" in item["expanded"] for item in plan.macro_expansions))
                    self.assertTrue(any("packed_dword" in item["expanded"] for item in plan.macro_expansions))
                plan.apply()
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(stage=stage, compiler=compiler, optimization=optimization):
                        self.compile_run(compiler, harness, optimization,
                                         ("-fsanitize=alignment", "-fsanitize-undefined-trap-on-error"))

    def test_actual_minimap_body_macros_and_complete_game_images_match_all_stages(self):
        # Copy the actual recovered body and its local header closure, including
        # canonical aliases. This fixture never writes to the production tree.
        name = "MiniMap_IsSpanWithinViewportBounds"
        manifest = json.loads((REPO / "data/recovered_sources.json").read_text())
        record = next(item for item in manifest["functions"] if item["name"] == name)
        original = (REPO / record["source"]).read_text()
        definition = scan_definitions(original, {name})[0]
        self.assertEqual(body_sha256(original, definition), record["body_sha256"])
        body = original[definition.start:definition.end]
        declarations = json.loads((REPO / "data/recovered_decls.json").read_text())["globals"]
        globals_ = {key: declarations[key]["decl"] for key in
                    ("gameData", "g_MiniMapRectLeft", "g_MiniMapRectTop", "g_MiniMapRectHeight")}
        self.fixture({name: body}, globals_)
        pending, seen = [Path("src/recovered_layout.h")], set()
        while pending:
            relative = pending.pop()
            if relative in seen:
                continue
            seen.add(relative)
            source = REPO / relative
            text = source.read_text()
            destination = self.root / relative
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_text(text)
            for include in re.findall(r'(?m)^\s*#\s*include\s+"([^"\n]+)"', text):
                target = (source.parent / include).resolve()
                if target.is_file() and target.is_relative_to(REPO):
                    pending.append(target.relative_to(REPO))
        harness = r'''
#include <sys/mman.h>
#include <cstring>
#if __has_include("src/units/Probe.hpp")
#include "src/units/Probe.hpp"
#endif
extern int gameData;
extern __int16 g_MiniMapRectLeft, g_MiniMapRectTop, g_MiniMapRectHeight;
int main() {
  const int bytes=GAMEDATA_SAVE_IMAGE_BYTES+32;
  unsigned char *a=(unsigned char *)mmap(nullptr,bytes,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
  unsigned char *b=(unsigned char *)mmap(nullptr,bytes,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
  if (a==MAP_FAILED || b==MAP_FAILED || (uintptr_t)a+bytes>=0x80000000u || (uintptr_t)b+bytes>=0x80000000u) return 90;
  unsigned char expectedA[GAMEDATA_SAVE_IMAGE_BYTES+32], expectedB[GAMEDATA_SAVE_IMAGE_BYTES+32];
  for (int offset=0; offset<16; ++offset) {
    memset(a,0xA5,bytes); memset(b,0x5A,bytes);
    for (int player=0; player<4; ++player) {
      uint32_t selected=player, enabled=1, disabled=0;
      memcpy(a+offset+VIEWED_PLAYER_INDEX_OFFSET,&selected,4);
      memcpy(b+offset+VIEWED_PLAYER_INDEX_OFFSET,&selected,4);
      memcpy(a+offset+PLAYER_RUNTIME_STATE_OFFSET+PLAYER_DATA_STRIDE*player+PLAYER_MINIMAP_VISIBLE_OFFSET,&enabled,4);
      memcpy(b+offset+PLAYER_RUNTIME_STATE_OFFSET+PLAYER_DATA_STRIDE*player+PLAYER_MINIMAP_VISIBLE_OFFSET,&disabled,4);
      memcpy(expectedA,a,bytes); memcpy(expectedB,b,bytes);
      g_MiniMapRectLeft=10; g_MiniMapRectTop=20; g_MiniMapRectHeight=10;
      gameData=(int)(uintptr_t)(a+offset);
#if __has_include("src/units/Probe.hpp")
      auto borrowed=clash95::Probe::borrow();
#endif
      for (int which=0; which<2; ++which) {
        gameData=(int)(uintptr_t)((which ? b : a)+offset);
        const unsigned short lefts[]={0,9,10,65535}, bottoms[]={0,29,30,65535};
        for (unsigned short left:lefts) for (unsigned short bottom:bottoms) {
          int expected=(!which && left>=10 && bottom<=30);
          if (MiniMap_IsSpanWithinViewportBounds(left,bottom)!=expected) return 1;
#if __has_include("src/units/Probe.hpp")
          if (borrowed.MiniMap_IsSpanWithinViewportBounds(left,bottom)!=expected) return 2;
#endif
          if (memcmp(a,expectedA,bytes) || memcmp(b,expectedB,bytes)) return 3;
        }
      }
      if (g_MiniMapRectLeft!=10 || g_MiniMapRectTop!=20 || g_MiniMapRectHeight!=10) return 4;
    }
  }
  munmap(a,bytes); munmap(b,bytes); return 0;
}
'''
        for stage in ("before", "extract", "relocate"):
            if stage != "before":
                plan = migration.make_plan(self.root, "Probe", stage)
                if stage == "extract":
                    self.assertEqual(set(plan.bindings), set(globals_))
                    self.assertTrue(any(item["macro"] == "PLAYER_MINIMAP_VISIBLE" for item in plan.macro_expansions))
                    self.assertTrue(any(item["macro"] == "g_MiniMapRectLeft_523344" for item in plan.macro_expansions))
                plan.apply()
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    with self.subTest(stage=stage, compiler=compiler, optimization=optimization):
                        self.compile_run(compiler, harness, optimization, ("-Wno-comment",))

    def test_explicit_global_qualification_and_parameter_shadowing_are_preserved(self):
        self.fixture({"Probe_Increment": "int Probe_Increment(int counter)\n{ ::counter += counter; return ::counter; }"},
                     {"counter": "extern int counter;"})
        migration.make_plan(self.root, "Probe").apply()
        original = (self.root / "src/units/original.cpp").read_text()
        self.assertIn("this->state_field_0_ += counter; return this->state_field_0_;", original)
        self.assert_header_policy()
        self.compile_run(shutil.which("g++-13"), "int main() { return Probe_Increment(4)!=6; }\n")

    def test_unknown_state_unsupported_global_types_and_stale_hash_refuse(self):
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return g_Unknown; }"}, {})
        with self.assertRaisesRegex(migration.MigrationError, "lacks canonical declarations"):
            migration.make_plan(self.root, "Probe")
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return counter; }"}, {"counter": "static int counter;"})
        with self.assertRaisesRegex(migration.MigrationError, "static storage|unsupported global declaration"):
            migration.make_plan(self.root, "Probe")
        self.fixture()
        path = self.root / "src/units/original.cpp"
        path.write_text(path.read_text().replace("counter += amount", "counter -= amount"))
        with self.assertRaisesRegex(migration.MigrationError, "source/hash changed"):
            migration.make_plan(self.root, "Probe")

    def test_concurrent_edit_is_not_overwritten_by_write(self):
        self.fixture()
        plan = migration.make_plan(self.root, "Probe")
        path = self.root / "src/units/original.cpp"
        edited = path.read_text() + "// concurrent work\n"
        path.write_text(edited)
        with self.assertRaisesRegex(migration.MigrationError, "input changed"):
            plan.apply()
        self.assertEqual(path.read_text(), edited)
        self.assertFalse((self.root / "src/units/Probe.hpp").exists())

    def test_stale_borrowing_glue_refuses_whole_class_relocation(self):
        self.fixture()
        migration.make_plan(self.root, "Probe").apply()
        path = self.root / "src/units/original.cpp"
        path.write_text(path.read_text().replace("return Probe(::counter, ::values);", "return Probe(::values[0], ::values);"))
        before = self.snapshot()
        with self.assertRaisesRegex(migration.MigrationError, "borrowing glue source/hash changed"):
            migration.make_plan(self.root, "Probe", "relocate")
        self.assertEqual(self.snapshot(), before)

    def test_failed_file_replace_rolls_back_the_complete_batch(self):
        self.fixture()
        before = self.snapshot()
        plan = migration.make_plan(self.root, "Probe")
        replace = Path.replace
        calls = 0

        def fail_second(path, destination):
            nonlocal calls
            calls += 1
            if calls == 2:
                raise OSError("injected replacement failure")
            return replace(path, destination)

        with mock.patch.object(Path, "replace", fail_second):
            with self.assertRaisesRegex(OSError, "injected"):
                plan.apply()
        self.assertEqual(self.snapshot(), before)

    def test_macro_callback_retains_global_adapter_and_source_local_callable_still_refuses(self):
        self.fixture({"Probe_Increment": "int Probe_Increment(int amount)\n{ return amount+1; }",
                      "Probe_Peek": "int Probe_Peek(void)\n{ return (&PICK)(4); }",
                      "Probe_Address": "intptr_t Probe_Address(void)\n{ return (intptr_t)&PICK; }"},
                     {}, macros="#define PICK Probe_Increment\n")
        for stage in ("before", "extract", "relocate"):
            if stage != "before":
                migration.make_plan(self.root, "Probe", stage).apply()
            if stage == "extract":
                self.assertIn("(&::Probe_Increment)(4)", (self.root / "src/units/original.cpp").read_text())
            for compiler in ("g++-13", "clang++-18"):
                for optimization in ("-O0", "-O2"):
                    self.compile_run(compiler, "int main() { return Probe_Peek()!=5 || Probe_Address()!=(intptr_t)&Probe_Increment; }\n", optimization)
        (self.root / "src/units/Probe.hpp").unlink()
        (self.root / "src/units/Probe.cpp").unlink()
        self.fixture({"Probe_Peek": "int Probe_Peek(void)\n{ return Private_Helper(); }"}, {}, extra_functions="static int Private_Helper() { return 2; }")
        self.declarations["functions"]["Private_Helper"] = {"class": "tu-local", "decl": "static int Private_Helper(void);"}
        self.save_metadata()
        with self.assertRaisesRegex(migration.MigrationError, "file-local callable"):
            migration.make_plan(self.root, "Probe")

    def test_partially_migrated_class_existing_header_and_support_helpers_refuse(self):
        self.fixture()
        self.registry["helpers"] = [{"name": "Probe_Helper", "class_owner": "Probe"}]
        self.save_metadata()
        with self.assertRaisesRegex(migration.MigrationError, "support helpers"):
            migration.make_plan(self.root, "Probe")
        self.registry["helpers"] = []
        self.save_metadata()
        migration.make_plan(self.root, "Probe").apply()
        with self.assertRaisesRegex(migration.MigrationError, "partially extracted|borrowing glue is already registered"):
            migration.make_plan(self.root, "Probe")

    def test_relocation_shards_keep_complete_bodies_and_original_adapters(self):
        bodies = {f"Probe_{index}": f"int Probe_{index}(int amount)\n{{\n" + "\n".join("  amount += 1;" for _ in range(10)) + "\n  return amount;\n}" for index in range(4)}
        self.fixture(bodies, {})
        migration.make_plan(self.root, "Probe").apply()
        plan = migration.make_plan(self.root, "Probe", "relocate", max_lines=35)
        shards = [text for path, text in plan.changes.items() if "/Probe" in path and path.endswith(".cpp")]
        self.assertGreater(len(shards), 1)
        self.assertTrue(all(len(text.splitlines()) <= 35 for text in shards))
        plan.apply()
        self.compile_run(shutil.which("g++-13"), "int main() { return Probe_0(0)!=10 || Probe_3(3)!=13; }\n")


if __name__ == "__main__":
    unittest.main()
