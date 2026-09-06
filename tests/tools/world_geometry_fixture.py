"""Shared compiler plumbing for separately gated sine recovery and class parity."""
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

ROOT = Path(__file__).resolve().parents[2]
FIXTURES = Path(__file__).parent / "fixtures"
COMMON = FIXTURES / "world_geometry_common"
sys.path.insert(0, str(ROOT / "tools"))
from recovered_implementation import index_manifest_definitions
from split_source_index import body_sha256, scan_definitions

def frozen(test, directory, record, *, name=None, body_key="body_sha256"):
    identity = name or record["name"]
    raw = (directory / record["fixture"]).read_bytes()
    test.assertEqual(hashlib.sha256(raw).hexdigest(), record["file_sha256"])
    source = raw.decode()
    definitions = scan_definitions(source, {identity})
    test.assertEqual(len(definitions), 1)
    test.assertEqual(body_sha256(source, definitions[0]), record[body_key])
    renamed, count = re.subn(r"\b" + re.escape(identity) + r"(?=\s*\()", "Reference_" + identity, source, count=1)
    test.assertEqual(count, 1)
    return renamed

def actual(test, names):
    manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
    records = {record["name"]: record for record in manifest["functions"] if record["name"] in names}
    test.assertEqual(set(records), set(names))
    sources = {record["source"] for record in records.values()}
    sources.update(record["adapter"]["source"] for record in records.values() if record.get("adapter"))
    indexed = index_manifest_definitions(manifest, ROOT, sources)
    snippets = []
    headers = set()
    for name in names:
        record = records[name]
        if record.get("implementation", {}).get("kind") == "method":
            headers.add(record["implementation"]["header"].removeprefix("src/"))
        for role in ("canonical", "adapter") if record.get("adapter") else ("canonical",):
            resolved = indexed[(name, role)]
            expected = record["body_sha256"] if role == "canonical" else record["adapter"]["body_sha256"]
            test.assertEqual(resolved.body_sha256, expected, name + " " + role)
            source = (ROOT / resolved.target.source).read_text()
            snippets.append(source[resolved.definition.start:resolved.definition.end])
    return snippets, headers, records

def assert_table_image(test):
    source = (ROOT / "src/state/00000000_0054FFFF_recovered_state.cpp").read_text()
    match = re.search(r"\bint\s+g_MathSinTableQ16\s*\[\s*363\s*\]\s*=\s*\{([^}]*)\}", source)
    test.assertIsNotNone(match, "canonical sine table definition must stay explicit")
    actual_values = [int(word.strip()) for word in match.group(1).split(",") if word.strip()]
    expected_values = [int(word.strip()) for word in (COMMON / "sine_table.inc").read_text().split(",") if word.strip()]
    test.assertEqual(actual_values, expected_values)
    test.assertEqual(len(actual_values), 363)
    test.assertEqual(actual_values[0], 0)
    test.assertEqual((min(actual_values), max(actual_values)), (-65536, 65536))

def run_profiles(test, parts, *, label, output_pattern):
    if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
        test.skipTest("the original 32-bit addressing oracle requires Linux x86-64")
    with tempfile.TemporaryDirectory(prefix="clash95-" + label + "-") as temporary:
        directory = Path(temporary)
        source = directory / "actual-and-reference.cpp"
        source.write_text("\n".join(parts))
        for compiler in ("g++-13", "clang++-18"):
            test.assertIsNotNone(shutil.which(compiler), "required compiler missing: " + compiler)
            for optimization in ("-O0", "-O2"):
                with test.subTest(compiler=compiler, optimization=optimization):
                    binary = directory / (compiler + optimization)
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions",
                               "-fno-rtti", "-fno-pie", "-no-pie", optimization,
                               "-fsanitize=undefined", "-fsanitize-undefined-trap-on-error",
                               "-Wall", "-Wextra", "-Werror", "-I", str(ROOT / "src"),
                               "-I", str(COMMON), str(source), "-o", str(binary)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    test.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                    executed = subprocess.run([str(binary)], capture_output=True, text=True, timeout=30)
                    test.assertEqual(executed.returncode, 0, executed.stdout + executed.stderr)
                    test.assertRegex(executed.stdout, output_pattern)
                    print(label, compiler, optimization, executed.stdout.strip(), flush=True)
