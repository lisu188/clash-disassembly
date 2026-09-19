#!/usr/bin/env python3
"""Actual builder-menu body against measured original instruction traces.

Child functions are explicit recording boundaries. The real reconstruction
initializers are separately checked at first use; no assets are required.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import shutil
import subprocess
import tempfile
import unittest

import test_builder_road as builder

FIXTURES = Path(__file__).resolve().parent / "fixtures/builder_menu"
SOURCE = builder.WORLD2
FUNCTION = "WorldMap_HandleBuilderActionMenu"


def load_contract(path=None):
    path = path or FIXTURES / "contract.py"
    specification = importlib.util.spec_from_file_location("builder_menu_contract", path)
    module = importlib.util.module_from_spec(specification)
    specification.loader.exec_module(module)
    return module


def harness_source(body=None, contract=None):
    contract = contract or load_contract()
    _, road, widgets, relocations = builder.fixtures()
    main = json.loads((builder.FIXTURES / "main-callbacks.json").read_text())
    callbacks = [row["canonical_symbol"] for row in main["callbacks"]]
    assert callbacks[4] == FUNCTION
    symbols = {row["canonical_symbol"] for row in relocations if row.get("canonical_symbol")}
    symbols.update(callbacks)
    symbols.difference_update((FUNCTION, builder.SELECTOR, "g_ActionButtonSpriteSet"))
    spies = "\n".join(f'static int {name}() {{ fail("address-only callback invoked"); }}' for name in sorted(symbols))
    masks = {"road": bytearray(len(road)), "builder": bytearray(len(widgets))}
    checks = []
    for index, item in enumerate(relocations):
        table = "builder" if item["table"] == "builder-widgets" else "road"
        actual = "g_UI_YesNoDims" if table == "builder" else "g_RoadBuildData"
        offset = item["region_offset"]
        masks[table][offset:offset + 4] = b"\1" * 4
        field = f"{actual} + {offset}"
        if item.get("canonical_symbol"):
            checks.append(f"check_pointer({field}, (uintptr_t)&{item['canonical_symbol']});")
        elif "raw_hex" in item:
            checks.append(builder.byte_array(f"text_{index}", bytes.fromhex(item["raw_hex"]) + b"\0"))
            checks.append(f"check_text({field}, text_{index}, sizeof text_{index});")
        else:
            assert int(item["original_pointer"], 16) == 0
            checks.append(f"check_pointer({field}, 0);")
    bodies = "\n\n".join(builder.extract(path, name) for path, name in (
        (builder.BUILDER_WIDGETS, builder.SELECTOR),
        (SOURCE, "WorldMap_WriteActionWidgetRecord"),
        (builder.BUILDER_WIDGETS, "WorldMap_EnsureBuilderWidgetTables"),
        (SOURCE, "WorldMap_EnsureActionButtonWidgetTable"),
    ))
    data = "".join(builder.byte_array(name, value) for name, value in (
        ("original_road", road), ("original_builder", widgets),
        ("road_pointer_mask", masks["road"]), ("builder_pointer_mask", masks["builder"])))
    template = (FIXTURES / "native_harness.cpp").read_text()
    replacements = {
        "@CALL_ENUM@": ", ".join(f"C_{name.upper()} = {number}" for name, number in contract.CALLS.items()),
        "@SPIES@": spies, "@INITIALIZERS@": bodies,
        "@BODY@": body if body is not None else builder.extract(SOURCE, FUNCTION),
        "@DATA@": data, "@POINTER_CHECKS@": "\n".join(checks),
        "@MAIN_CALLBACKS@": ", ".join(f"(uintptr_t)&{name}" for name in callbacks),
    }
    for marker, value in replacements.items():
        template = template.replace(marker, value)
    return template


def compiler_command(compiler, optimization, source, executable):
    return [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
            "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
            "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
            "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
            "-isystem", str(builder.REPO / "src"), str(source), "-o", str(executable)]


class BuilderMenuTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        contract = load_contract()
        provenance = json.loads((FIXTURES / "provenance.json").read_text())
        records = contract.cases()
        encoded = contract.pack_inputs(records)
        self.assertEqual(hashlib.sha256((FIXTURES / "contract.py").read_bytes()).hexdigest(),
                         provenance["bindings"]["contract"]["sha256"])
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(list(contract.CALLS), provenance["calls"])
        self.assertEqual(contract.STATE_FIELDS, provenance["state_fields"])
        self.assertEqual([case["name"] for case in records], provenance["case_names"])
        self.assertEqual(contract.EVENT_WORDS, provenance["event_words"])
        self.assertEqual(contract.FINAL_WORDS, provenance["final_words"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-builder-menu-") as temporary:
            directory = Path(temporary)
            source = directory / "builder_menu.cpp"
            source.write_text(harness_source(contract=contract))
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("builder-menu-" + optimization[1:])
                    command = compiler_command(compiler, optimization, source, executable)
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    for case, trace, expected in zip(records, contract.decode_output(run.stdout, records),
                                                     provenance["case_trace_sha256"], strict=True):
                        self.assertEqual(hashlib.sha256(trace).hexdigest(), expected,
                                         case["name"] + ": original event/state/memory trace differs")
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_builder_menu_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_builder_menu_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
