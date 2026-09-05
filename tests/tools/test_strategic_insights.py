from __future__ import annotations

from contextlib import redirect_stderr
from copy import deepcopy
import io
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import check_clash_dat_unresolved as inventory
import generate_clash_recovered_constraints as generator
from decompile_clash_dat import parse_bsave
from split_source_index import scan_definitions


def sample_ir() -> dict:
    return {
        "expressions": [(10, 0, 1, -1), (10, 1, 2, 4), (29, 0, -1, 3), (1, 0, -1, -1), (1, 0, -1, -1)],
        "functions": ["and", "eq"],
        "bitmaps": [bytes(4)],
        "integers": [7],
    }


def sample_manifest(negated: bool = False) -> dict:
    condition = {
        "condition": 2, "join_index": 17, "depth": 2, "negated": negated,
        "binding": {"kind": "object"}, "alpha_test_indices": [], "join_test_index": 0,
        "unresolved_test_count": 1,
        "translations": [{"source": "(and (eq object[p1].x 7) TRUE)", "translated": None, "reason": "ambiguous binding"}],
    }
    rule = {
        "record_index": 3, "original_name": "sample", "output_name": "sample", "terminal_join": 17,
        "unresolved_test_count": 1, "conditions": [condition],
    }
    return {"compiled_test_count": 1, "translated_test_count": 0, "unresolved_test_count": 1, "rules_manifest": [rule]}


class MatcherEvidenceTests(unittest.TestCase):
    def test_primitive_families_are_never_blank(self):
        for source, expected in (
            ("(eq x y)", "eq"), ("  (and (eq x y))", "and"),
            ("fact-join-compare(a,b)", "fact-join-compare"), ("prim99[4]", "prim99[4]"),
            ("", "<unknown>"), (" () ", "<unknown>"),
        ):
            with self.subTest(source=source):
                self.assertEqual(inventory.primitive_family(source), expected)

    def test_nested_typed_payloads_and_provenance(self):
        report = inventory.inventory_from_manifest(Path("sample.dat"), sample_ir(), sample_manifest(True))
        self.assertEqual(report["by_primitive_family"], {"and": 1})
        self.assertEqual(report["by_nested_primitive"], {"FACT_JN_VAR1": 1})
        self.assertEqual(report["by_primitive_payload"], {"FACT_JN_VAR1:00000000": 1})
        self.assertEqual(report["unresolved_negated_test_count"], 1)
        entry = report["entries"][0]
        self.assertEqual((entry["expression_index"], entry["phase"], entry["join_index"], entry["depth"]), (0, "join", 17, 2))
        self.assertEqual([node["expression_index"] for node in entry["expression_nodes"]], [0, 1, 2, 3, 4])
        primitive = entry["expression_nodes"][2]["primitive"]
        self.assertEqual(primitive["bitmap_index"], 0)
        self.assertIn("which_pattern", primitive["fields"])
        self.assertFalse(report["behavioral_equivalence_verified"])

    def test_root_sibling_is_not_part_of_test(self):
        ir = sample_ir()
        ir["expressions"] = [(10, 0, -1, 999)]
        self.assertEqual(len(inventory.expression_evidence(ir, 0)), 1)

    def test_cycles_and_bad_indices_fail_explicitly(self):
        for expressions in (
            [(10, 0, 0, -1)],
            [(10, 0, 1, -1), (1, 0, -1, 1)],
            [(10, 0, 99, -1)],
            [(10, 0, -1, -1)],
        ):
            ir = sample_ir()
            ir["expressions"] = expressions
            with self.subTest(expressions=expressions), self.assertRaises(ValueError):
                inventory.expression_evidence(ir, 99 if len(expressions) == 1 and expressions[0][2] == -1 else 0)

    def test_provenance_count_mismatch_is_rejected(self):
        manifest = sample_manifest()
        manifest["rules_manifest"][0]["conditions"][0]["join_test_index"] = -1
        with self.assertRaisesRegex(ValueError, "provenance mismatch"):
            inventory.inventory_from_manifest(Path("sample.dat"), sample_ir(), manifest)

    def test_binding_blocked_candidate_is_still_unresolved(self):
        manifest = sample_manifest()
        condition = manifest["rules_manifest"][0]["conditions"][0]
        condition["binding"] = {"kind": "fact", "fields": None}
        condition["translations"][0].update(translated="(eq ?f1 7)", reason=None)
        report = inventory.inventory_from_manifest(Path("sample.dat"), sample_ir(), manifest)
        self.assertEqual(report["unresolved_test_count"], 1)
        self.assertEqual(report["entries"][0]["reason"], "source form lacks a legal binding")

    def test_gate_rejects_positive_and_negative_incomplete_tests(self):
        for negated in (False, True):
            with self.subTest(negated=negated), self.assertRaisesRegex(ValueError, "remain unresolved"):
                generator.require_complete_matchers(sample_manifest(negated))

    def test_gate_accepts_complete_matchers_but_not_inconsistent_counts(self):
        complete = {"compiled_test_count": 0, "translated_test_count": 0, "unresolved_test_count": 0, "rules_manifest": []}
        generator.require_complete_matchers(complete)
        broken = deepcopy(complete)
        broken["compiled_test_count"] = 1
        with self.assertRaisesRegex(ValueError, "inconsistent"):
            generator.require_complete_matchers(broken)

    def test_strict_cli_never_creates_or_overwrites_outputs_on_refusal(self):
        for existing in (False, True):
            with self.subTest(existing=existing), tempfile.TemporaryDirectory() as directory:
                clp = Path(directory) / "program.clp"
                manifest = Path(directory) / "manifest.json"
                if existing:
                    clp.write_text("keep source")
                    manifest.write_text("keep manifest")
                argv = ["generate", "sample.dat", "--clp", str(clp), "--manifest", str(manifest), "--require-complete-matchers"]
                with patch.object(sys, "argv", argv), patch.object(generator, "parse_bsave", return_value={}), patch.object(generator, "render_recovered_program", return_value=("replacement", sample_manifest(True))), redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as caught:
                    generator.main()
                self.assertEqual(caught.exception.code, 2)
                if existing:
                    self.assertEqual(clp.read_text(), "keep source")
                    self.assertEqual(manifest.read_text(), "keep manifest")
                else:
                    self.assertFalse(clp.exists())
                    self.assertFalse(manifest.exists())


class RetailMatcherEvidenceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.path = ROOT / "CLASH.DAT"
        cls.ir = parse_bsave(cls.path)
        cls.program, cls.manifest = generator.render_recovered_program(cls.path, cls.ir)
        cls.report = inventory.inventory_from_manifest(cls.path, cls.ir, cls.manifest)

    def test_all_test_occurrences_keep_exact_expression_provenance(self):
        total = 0
        for rule in self.manifest["rules_manifest"]:
            for condition in rule["conditions"]:
                count = len(condition["alpha_test_indices"]) + (condition["join_test_index"] != -1)
                self.assertEqual(count, condition["compiled_test_count"])
                self.assertIsInstance(condition["join_index"], int)
                self.assertIsInstance(condition["depth"], int)
                total += count
        self.assertEqual(total, 753)

    def test_no_blank_families_and_no_coverage_regression(self):
        self.assertNotIn("", self.report["by_primitive_family"])
        self.assertLessEqual(self.report["unresolved_test_count"], 333)
        self.assertGreaterEqual(self.report["translated_test_count"], 420)
        self.assertTrue(self.report["by_nested_primitive"])
        self.assertTrue(self.report["by_primitive_payload"])
        self.assertEqual(sum(self.report["by_primitive_family"].values()), self.report["unresolved_test_count"])
        for entry in self.report["entries"]:
            self.assertIn(entry["phase"], ("alpha", "join"))
            self.assertTrue(entry["expression_nodes"])

    def test_completeness_metrics_agree_without_claiming_equivalence(self):
        for key in ("fully_translated_rule_count", "unresolved_negated_test_count"):
            self.assertEqual(self.report[key], self.manifest[key])
        self.assertEqual(self.manifest["matcher_complete"], self.manifest["unresolved_test_count"] == 0)
        self.assertFalse(self.manifest["behavioral_equivalence_verified"])
        self.assertIn("SOURCE PROJECTION", self.program)
        if self.manifest["unresolved_test_count"]:
            with self.assertRaises(ValueError):
                generator.require_complete_matchers(self.manifest)


NATIVE_PRELUDE = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define __int16 short
#define __int8 char
#define _DWORD int32_t
#define qmemcpy memcpy
typedef uint32_t DWORD;
typedef unsigned char _BYTE;
static _Alignas(16) unsigned char state[600000];
static uintptr_t gameData;
#define MAP_WIDTH_TILES_OFFSET 0x222E0
#define MAP_HEIGHT_TILES_OFFSET 0x222E4
#define UNIT_STACK_STRIDE 725
#define BUILDING_RECORD_SIZE 467
#define TILE_OCCUPANT_BUILDING_INDEX_BASE 32768
#define TILE_INDEX(x,y) (gameData + 0x87D56 + 200 * (x) + 2 * (y))
#define UNIT_RECORD(i) (gameData + 0x7C6EA + BUILDING_RECORD_SIZE * (i))
static double priority;
static int score_calls, treasure, religious;
static double AI_CalcStrategicPriorityScore(int kind, DWORD x, int ox, int y, int oy) {
    assert(kind >= 1 && kind <= 4);
    assert(x == 7 && y == 19 && ox == 11 && oy == 23);
    ++score_calls;
    return priority;
}
static int MapTile_HasHiddenTreasure(int x, int y) {
    assert(x == 7 && y == 19);
    return treasure;
}
static int MapTile_GetReligiousSiteCategory(int x, int y) {
    assert(x == 7 && y == 19);
    return religious;
}
static void put16(size_t offset, uint16_t value) { memcpy(state + offset, &value, sizeof value); }
static void put32(size_t offset, int32_t value) { memcpy(state + offset, &value, sizeof value); }
'''

NATIVE_CHECKS = r'''
static void evaluate(int filter, int owner, int id, double value, int *kind, int *target, float *score) {
    put16(0x87D56 + 200 * 7 + 2 * 19, (uint16_t)id);
    priority = value;
    AI_EvaluateStrategicTargetAtTile(filter, owner, 19, 7, 11, 23, kind, target, score);
}
static void check_scores(void) {
    gameData = (uintptr_t)state;
    put32(MAP_WIDTH_TILES_OFFSET, 32);
    put32(MAP_HEIGHT_TILES_OFFSET, 32);
    put16(147180 + 2 * UNIT_STACK_STRIDE, 0);
    put16(147180 + 4 * UNIT_STACK_STRIDE, 0);
    state[147178 + 2 * UNIT_STACK_STRIDE] = 4;
    state[147178 + 4 * UNIT_STACK_STRIDE] = 4;
    int kind = -1, target = -1;
    float score = -1.0f;
    evaluate(2, 4, 2, 7.9, &kind, &target, &score);
    assert(kind == 2 && target == 2 && score == 7.0f);
    evaluate(2, 4, 4, 8.1, &kind, &target, &score);
    assert(target == 4 && score == 8.0f);
    evaluate(2, 4, 2, 8.9, &kind, &target, &score);
    assert(target == 4 && score == 8.0f);
    int calls = score_calls;
    evaluate(1, 4, 2, 99, &kind, &target, &score);
    evaluate(2, 3, 2, 99, &kind, &target, &score);
    assert(score_calls == calls && target == 4);
    evaluate(-1, -1, 2, 12.7, &kind, &target, &score);
    assert(target == 2 && score == 12.0f);
    score = -1.0f;
    evaluate(2, -1, 4, -0.5, &kind, &target, &score);
    assert(target == 4 && score == 0.0f);
    score = -3.0f;
    evaluate(2, 4, 2, -2.9, &kind, &target, &score);
    assert(target == 2 && score == -2.0f);
    score = -1.0f;
    evaluate(2, 4, 4, -1.9, &kind, &target, &score);
    assert(target == 2 && score == -1.0f);
    evaluate(2, 4, 4, 0.0, &kind, &target, &score);
    assert(target == 4 && score == 0.0f);
    evaluate(2, 4, 2, 7.999999, &kind, &target, &score);
    assert(target == 2 && score == 7.0f);
    evaluate(2, 4, 4, 8.0, &kind, &target, &score);
    assert(target == 4 && score == 8.0f);
    calls = score_calls;
    AI_EvaluateStrategicTargetAtTile(-1, -1, 19, -1, 11, 23, &kind, &target, &score);
    AI_EvaluateStrategicTargetAtTile(-1, -1, 19, 32, 11, 23, &kind, &target, &score);
    AI_EvaluateStrategicTargetAtTile(-1, -1, -1, 7, 11, 23, &kind, &target, &score);
    AI_EvaluateStrategicTargetAtTile(-1, -1, 32, 7, 11, 23, &kind, &target, &score);
    assert(score_calls == calls);
    treasure = 1;
    evaluate(-1, -1, 65535, 20.5, &kind, &target, &score);
    assert(kind == 3 && target == -1 && score == 20.0f);
    treasure = 0;
    religious = 1;
    evaluate(4, -1, 65535, 21.5, &kind, &target, &score);
    assert(kind == 4 && target == -1 && score == 21.0f);
    religious = 0;
    calls = score_calls;
    evaluate(-1, -1, 65535, 99.0, &kind, &target, &score);
    assert(score_calls == calls && score == 21.0f);
}
static void check_records(const signed char *keys, const int *expected, int count, int keep) {
    _BYTE records[684] = {0}, original[684] = {0};
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < 31; ++j) records[31 * i + j] = (_BYTE)(37 * i + j);
        records[31 * i + 9] = (_BYTE)keys[i];
    }
    memcpy(original, records, sizeof records);
    assert(regroup_records(records, count) == keep);
    for (int i = 0; i < count; ++i) assert(memcmp(records + 31 * i, original + 31 * expected[i], 31) == 0);
}
int main(void) {
    check_scores();
    check_records((signed char[]){9, 1, 8, 2}, (int[]){1, 2, 3, 0}, 4, 2);
    check_records((signed char[]){1, 2, 0}, (int[]){0, 1, 2}, 3, 0);
    check_records((signed char[]){-1, 1}, (int[]){0, 1}, 2, 0);
    check_records((signed char[]){1, -1}, (int[]){1, 0}, 2, 0);
    check_records((signed char[]){8}, (int[]){0}, 1, 1);
    check_records((signed char[]){8, 8}, (int[]){0, 1}, 2, 2);
    check_records((signed char[]){0}, (int[]){0}, 0, 0);
    signed char keys[22];
    int expected[22];
    for (int i = 0; i < 22; ++i) { keys[i] = (signed char)(22 - i); expected[i] = (i + 1) % 22; }
    check_records(keys, expected, 22, 10);
    puts("production strategic score + retail regrouping fidelity: PASS");
    return 0;
}
'''


class NativeStrategicDataflowTests(unittest.TestCase):
    def test_production_bodies_with_both_optimization_and_char_modes(self):
        compiler = shutil.which("cc")
        if compiler is None:
            self.skipTest("native C compiler unavailable")
        if not sys.platform.startswith("linux"):
            self.skipTest("Linux compiler/sanitizer fixture")
        source = (ROOT / "src/strategic/004589C0_004602F0_strategic_004.c").read_text()
        name = "AI_EvaluateStrategicTargetAtTile"
        definitions = scan_definitions(source, {name})
        self.assertEqual(len(definitions), 1)
        definition = definitions[0]
        evaluate = source[definition.start:definition.end]
        start = source.index("  sorted_flag = 0;")
        end = source.index("  writeback_cursor = merged_units;", start)
        regroup = """static int regroup_records(_BYTE *merged_units, int total_units) {
int sorted_flag, sort_limit, outer_index, outer_offset, inner_index, compare_index, compare_offset, healthy_scan_offset, keep_count;
_BYTE *swap_a, *swap_b, swap_buffer[28], swap_tail[3];
""" + source[start:end] + "\nreturn keep_count;\n}\n"
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "strategic.c"
            path.write_text(NATIVE_PRELUDE + evaluate + "\n" + regroup + NATIVE_CHECKS)
            for optimize in ("-O0", "-O2"):
                for char_mode in ("-fsigned-char", "-funsigned-char"):
                    with self.subTest(optimize=optimize, char_mode=char_mode):
                        binary = Path(directory) / "strategic"
                        command = [compiler, "-std=c17", optimize, char_mode, "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all", str(path), "-o", str(binary)]
                        built = subprocess.run(command, capture_output=True, text=True, timeout=45)
                        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
                        result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=15)
                        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
                        self.assertIn("PASS", result.stdout)


if __name__ == "__main__":
    unittest.main()
