#!/usr/bin/env python3
"""Freeze-check repaired controls; compile actual production bodies in separate TUs.

Only --output is written. Clock/log boundaries are controlled; actual Debug_Log,
GameRandom methods/factory/adapters and UnitTurn damage method/factory/adapter
are compiled. No repaired reference algorithm is rewritten in the harness.
"""
from pathlib import Path
import argparse
import hashlib
import json
import re
import shutil
import subprocess
import sys
sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root, output = args.root.resolve(), args.output.resolve()
    if output == root or output.is_relative_to(root):
        raise ValueError("output must be outside source root")
    output.mkdir(parents=True, exist_ok=False)
    sys.path.insert(0, str(root / "tools"))
    from recovered_implementation import index_manifest_definitions
    from split_source_index import body_sha256, scan_definitions
    from class_binding_inventory import validate_binding_metadata
    sha = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
    inputs = {}
    def read(path):
        inputs[str(path)] = sha(path)
        return path.read_text()
    manifest = json.loads(read(root / "data/recovered_sources.json"))
    registry = json.loads(read(root / "data/game_class_registry.json"))
    declarations = json.loads(read(root / "data/recovered_decls.json"))
    assert not validate_binding_metadata(registry, manifest, declarations)
    records = {r["name"]: r for r in manifest["functions"]}
    names = ["initRandomSeed", "Rng_RandRange", "Unit_UpdatePerTurn", "Debug_Log"]
    sources = {records[n]["source"] for n in names}
    sources.update(records[n]["adapter"]["source"] for n in names if records[n].get("adapter"))
    indexed = index_manifest_definitions(manifest, root, sources)
    headers = ["units/units_internal.h", "units/units_state.h", "units/units_shared_state.h",
               "buildings/buildings_api.h", "core/GameRandom.hpp", "units/UnitTurn.hpp"]
    common = "\n".join('#include "' + h + '"' for h in headers) + "\n"
    bindings = [b for b in registry["class_bindings"] if b["class_owner"] in ("GameRandom", "UnitTurn")]
    assert len(bindings) == 2
    for binding in bindings:
        common += "\n".join(declarations["globals"][g]["decl"] for g in binding["referenced_globals"]) + "\n"
    units = {}
    for name in names:
        record = records[name]
        if name != "Debug_Log":
            owner = "UnitTurn" if name == "Unit_UpdatePerTurn" else "GameRandom"
            assert record["implementation"]["qualified_name"] == "clash95::" + owner + "::" + name
        for role in ("canonical", "adapter") if record.get("adapter") else ("canonical",):
            item = indexed[(name, role)]
            expected = record["body_sha256"] if role == "canonical" else record["adapter"]["body_sha256"]
            assert item.body_sha256 == expected
            text = read(root / item.target.source)
            warning = '#pragma GCC diagnostic warning "-Wchar-subscripts"\n' if name == "Unit_UpdatePerTurn" else ""
            units[name + "-" + role + ".cpp"] = common + warning + text[item.definition.start:item.definition.end]
    for binding in bindings:
        text = read(root / binding["source"])
        definitions = scan_definitions(text, {binding["qualified_name"]})
        assert len(definitions) == 1
        definition = definitions[0]
        assert body_sha256(text, definition) == binding["body_sha256"]
        units[binding["class_owner"] + "-borrow.cpp"] = common + text[definition.start:definition.end]
    provenance = json.loads(read(HERE / "references/provenance.json"))
    assert provenance["reference_commit"] == "79d700c86e253180b1bb81c0a2833b48ae5fe1ba"
    for record in provenance["functions"]:
        path = HERE / "references" / record["fixture"]
        text = read(path)
        assert sha(path) == record["file_sha256"]
        definitions = scan_definitions(text, {record["name"]})
        assert len(definitions) == 1 and body_sha256(text, definitions[0]) == record["body_sha256"]
        assert records[record["name"]]["original_address"] == record["original_address"]
        text, count = re.subn(r"\b" + record["name"] + r"(?=\s*\()", "Reference_" + record["name"], text, count=1)
        assert count == 1
        units["reference-" + record["name"] + ".cpp"] = common + text
    caller = provenance["caller"]
    path = HERE / "references" / caller["fixture"]
    text = read(path)
    assert sha(path) == caller["file_sha256"]
    definitions = scan_definitions(text, {caller["qualified_name"]})
    assert len(definitions) == 1 and body_sha256(text, definitions[0]) == caller["body_sha256"]
    reference_class = read(HERE / "reference_unit_turn.hpp")
    units["reference-UnitTurn.cpp"] = common + '#pragma GCC diagnostic warning "-Wchar-subscripts"\n' + reference_class + text.replace(caller["qualified_name"], "ReferenceUnitTurn::Unit_UpdatePerTurn", 1)
    units["harness.cpp"] = common + reference_class + read(HERE / "harness.cpp")
    for header in ("core/GameRandom.hpp", "units/UnitTurn.hpp"):
        read(root / "src" / header)
    sources = []
    for name, text in units.items():
        source = output / name
        source.write_text(text)
        sources.append(str(source))
    profiles = []
    for compiler in ("g++-13", "clang++-18"):
        assert shutil.which(compiler), "required compiler missing " + compiler
        for opt in ("-O0", "-O2"):
            label = compiler + opt
            binary = output / label
            command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                       "-fno-pie", "-no-pie", opt, "-fsanitize=undefined", "-fsanitize-undefined-trap-on-error",
                       "-Wall", "-Wextra", "-Werror", "-I", str(root / "src"), *sources,
                       "-Wl,--wrap=Debug_Log", "-o", str(binary)]
            built = subprocess.run(command, capture_output=True, text=True, timeout=60)
            (output / (label + ".build.log")).write_text(built.stdout + built.stderr)
            row = {"profile": label, "command": command, "build": built.returncode}
            if built.returncode:
                row["build_output"] = built.stdout + built.stderr
            else:
                executed = subprocess.run([str(binary)], capture_output=True, text=True, timeout=45)
                (output / (label + ".run.log")).write_text(executed.stdout + executed.stderr)
                row.update(run=executed.returncode, stdout=executed.stdout, stderr=executed.stderr, binary_sha256=sha(binary))
            profiles.append(row)
            print(json.dumps(row), flush=True)
    unchanged = all(Path(p).exists() and sha(Path(p)) == value for p, value in inputs.items())
    (output / "summary.json").write_text(json.dumps({"reference_commit": provenance["reference_commit"],
        "root": str(root), "inputs_unchanged": unchanged, "input_sha256": inputs, "profiles": profiles,
        "limitations": ["controlled clock/log boundaries; no runtime or campaign promotion",
                        "original zero-range difference remains documented in GAME_RANDOM_RECOVERY.md"]}, indent=2) + "\n")
    return 0 if unchanged and all(p.get("build") == 0 and p.get("run") == 0 for p in profiles) else 1

if __name__ == "__main__":
    raise SystemExit(main())
