#!/usr/bin/env python3
"""Conservative numeric census regressions; fixtures never rewrite sources."""

import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))
import literal_inventory as inventory


class NumericCensusTests(unittest.TestCase):
    def census(self, body, **kwargs):
        return inventory.census_source(body, "src/world/example.cpp", **kwargs)

    def test_small_selectors_and_zero_one_are_not_blanket_exempt(self):
        sites = self.census("int choose(int mode) {\n"
                            "  if (mode == 1) return 2;\n"
                            "  switch (mode) { case 3: return 0; }\n"
                            "  return 9;\n}\n")
        self.assertEqual([s["raw"] for s in sites], ["1", "2", "3", "0", "9"])
        self.assertTrue(all(s["classification"] == "unresolved" for s in sites))
        self.assertEqual(sites[0]["context"], "comparison")
        self.assertEqual(sites[2]["context"], "case_label")
        self.assertTrue(all(s["fn"] == "choose" for s in sites))

    def test_float_and_integer_spelling_radix_suffix_and_separators_survive(self):
        source = ("double sample(void) {\n"
                  "  consume(1.0f, .5, 2e-3L, 0x1.8p+2F, 0xFFuLL, 077, 0b101U, 1'024UL);\n"
                  "  return 1.;\n}\n")
        sites = self.census(source)
        self.assertEqual([s["raw"] for s in sites],
                         ["1.0f", ".5", "2e-3L", "0x1.8p+2F", "0xFFuLL", "077", "0b101U", "1'024UL", "1."])
        self.assertEqual([s["kind"] for s in sites], ["float"] * 4 + ["integer"] * 4 + ["float"])
        self.assertEqual([s["suffix"] for s in sites], ["f", "", "L", "F", "uLL", "", "U", "UL", ""])
        self.assertEqual([s["value"] for s in sites[4:8]], [255, 63, 5, 1024])
        self.assertEqual([s["literal_type"] for s in sites[:4]],
                         ["float", "double", "long double", "float"])
        self.assertTrue(all(s["fn"] == "sample" for s in sites))

    def test_only_matching_simple_zero_based_loop_origins_and_unit_steps_are_arithmetic(self):
        source = ("void loops(int n) {\n"
                  "  for (int i = 0; i < n; i += 1) use(i, 1);\n"
                  "  for (j = 0; j != 8; ++j) use(j);\n"
                  "  for (k = 0; k < n; k = k + 1u) use(k);\n"
                  "  for (a = 1; a < n; a += 1) use(a);\n"
                  "  for (b = -1; b < n; b += 1) use(b);\n"
                  "  for (c = +0; c < n; c += 1) use(c);\n"
                  "  for (d = 0; d < n; d += 2) use(d);\n"
                  "  for (e = 0; mode < n; ++e) use(e);\n"
                  "  while (n != 0) n -= 1;\n"
                  "}\n")
        sites = self.census(source)
        legitimate = [s for s in sites if s["classification"] == "legitimate"]
        self.assertEqual([(s["line"], s["raw"]) for s in legitimate],
                         [(2, "0"), (2, "1"), (3, "0"), (4, "0"), (4, "1u")])
        self.assertTrue(all("for-loop induction variable" in s["reason"] for s in legitimate))

    def test_comments_strings_characters_raw_strings_and_directives_are_skipped(self):
        source = ('#define NUMBER 83 \\\n + 84.0\n'
                  '// 85 \\\n 851\n/* 86.0 */\n'
                  'const char *a = "87 \\\" 88";\n'
                  'const char *b = R"tag(89 " 90)tag";\n'
                  "char c = '9';\n"
                  'int actual(void) { return 7; }\n')
        self.assertEqual([s["raw"] for s in self.census(source)], ["7"])

    def test_global_payload_does_not_include_dimensions_or_local_initializers(self):
        source = ('unsigned char before[4] = { 1, 2, 3, 4 };\n'
                  'int actual(void) {\n  int local[2] = { 5, 6 };\n  return 8;\n}\n'
                  'unsigned char after[2][2] = { { 9, 10 }, { 11, 12 } };\n')
        sites = self.census(source)
        legitimate = [s["raw"] for s in sites if s["classification"] == "legitimate"]
        self.assertEqual(legitimate, ["1", "2", "3", "4", "9", "10", "11", "12"])
        self.assertEqual(sites[0]["classification"], "unresolved")
        self.assertEqual(sites[-1]["fn"], None)
        self.assertEqual(next(s for s in sites if s["raw"] == "5")["fn"], "actual")

    def test_equal_values_keep_domain_candidates_separate_and_do_not_match_floats(self):
        entries = [dict(name="PLAYER_STRIDE", value=725, tier=1, family="player",
                        anchors=["playerData"], forbid_anchors=["unitData"], cooccur_values=[]),
                   dict(name="UNIT_STRIDE", value=725, tier=1, family="unit",
                        anchors=["unitData"], forbid_anchors=["playerData"], cooccur_values=[])]
        source = ("int offsets(int n) {\n"
                  "  use(playerData + 725 * n, unitData + 725 * n, 725.0);\n}\n")
        sites = self.census(source, entries=entries)
        self.assertEqual([s["candidate_constants"] for s in sites],
                         [["PLAYER_STRIDE"], ["UNIT_STRIDE"], []])
        self.assertEqual([s["classification"] for s in sites],
                         ["replaceable", "replaceable", "unresolved"])

    def test_initializer_calls_arithmetic_lambdas_and_subscript_assignment_are_not_raw_data(self):
        sources = [
            "int data[2] = { calculate_cost(5), 8 * 7 };\n",
            "int data[1] = { []() { if (mode == 7) return 9; return 11; }() };\n",
            "auto init = []() { int local[2] = { 7, 8 }; return local[0]; };\n",
            "int a[2]; int b = a[1] = { 77 };\n",
            "int data[2] = { 1 + 2, 4 };\n",
        ]
        for source in sources:
            with self.subTest(source=source):
                self.assertTrue(all(s["classification"] == "unresolved" for s in self.census(source)))

    def test_signed_literal_payloads_and_linkage_blocks_remain_data(self):
        sites = self.census('extern "C" {\nint data[2][2] = { { -7, +8 }, { 9, 10 } };\n}\n')
        self.assertEqual([s["raw"] for s in sites if s["classification"] == "legitimate"],
                         ["7", "8", "9", "10"])

    def test_colliding_eligible_names_require_review(self):
        entries = [dict(name=name, value=725, tier=1, family="test", anchors=["data"],
                        forbid_anchors=[], cooccur_values=[]) for name in ("ONE", "TWO")]
        sites = self.census("int f(void) { return *(data + 725); }\n", entries=entries)
        self.assertEqual(sites[0]["candidate_constants"], ["ONE", "TWO"])
        self.assertEqual(sites[0]["classification"], "unresolved")

    def test_review_rules_are_scoped_evidence_bearing_and_count_checked(self):
        rule = {"id": "mode-two", "classification": "unresolved", "reason": "selector domain not recovered",
                "evidence": ["clash95.asm:known-function"],
                "match": {"file": "src/world/*.cpp", "fn": "choose", "raw": "2", "context": "comparison"},
                "expected_count": 1}
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "review.json"
            path.write_text(json.dumps({"schema_version": 1, "rules": [rule]}))
            rules = inventory.load_dispositions(path)
        sites = self.census("int choose(int n) { if (n == 2) return 2; }\n", dispositions=rules)
        self.assertEqual(sites[0]["review_rule"], "mode-two")
        self.assertNotIn("review_rule", sites[1])
        summary = inventory.summarize_census(sites, ["src/world/example.cpp"], rules)
        self.assertEqual(summary["review_rules"], [{"id": "mode-two", "matched": 1}])
        with self.assertRaisesRegex(ValueError, "expected 2 sites, found 1"):
            inventory.summarize_census(sites, ["src/world/example.cpp"], [{**rule, "expected_count": 2}])

    def test_invalid_or_overlapping_reviews_fail_closed(self):
        rule = {"id": "r", "classification": "legitimate", "reason": "reviewed value",
                "evidence": ["retained evidence"], "match": {"file": "src/world/*.cpp"}}
        for change in ({"evidence": []}, {"classification": "replaceable"},
                       {"match": {"raw": "2"}}, {"match": {"file": "*", "typo": "x"}}):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as directory:
                path = Path(directory) / "review.json"
                path.write_text(json.dumps({"schema_version": 1, "rules": [{**rule, **change}]}))
                with self.assertRaises(ValueError):
                    inventory.load_dispositions(path)
        with self.assertRaisesRegex(ValueError, "overlapping dispositions"):
            self.census("int f(void) { return 2; }\n", dispositions=[rule, {**rule, "id": "s"}])

    def test_counts_are_deterministic_include_empty_files_and_count_each_site_once(self):
        sites = self.census("int f(void) { consume(0, 1, 2.0f, 16); }\n")
        files = ["src/world/empty.cpp", "src/world/example.cpp"]
        first = inventory.summarize_census(sites, files, include_sites=True)
        self.assertEqual(first, inventory.summarize_census(sites, list(reversed(files)), include_sites=True))
        self.assertEqual(first["total"], 4)
        self.assertEqual(first["small_integer_sites"], 2)
        self.assertEqual(first["by_kind"], {"float": 1, "integer": 3})
        self.assertEqual(first["by_file"]["src/world/empty.cpp"]["total"], 0)
        self.assertEqual(sum(first["by_classification"].values()), 4)

    def test_cli_retains_legacy_fields_and_adds_census_without_site_array_by_default(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "sample.cpp"
            path.write_text("int f(void) { consume(2, 1.5f, 725); }\n")
            with mock.patch.object(inventory.lc, "REPO", directory), \
                    mock.patch.object(inventory.lc, "apply_files", return_value=["sample.cpp"]), \
                    mock.patch.object(inventory.lc, "load_manifest", return_value=([], {})), \
                    mock.patch.object(inventory.lc, "load_source_manifest", return_value={"functions": []}), \
                    mock.patch.object(inventory, "git_head", return_value="fixture"), \
                    mock.patch.object(sys, "argv", ["literal_inventory.py"]), \
                    contextlib.redirect_stdout(io.StringIO()) as output:
                inventory.main()
        document = json.loads(output.getvalue())
        self.assertTrue({"commit", "files", "constants", "derived_candidates", "unmapped_frequent"} <= document.keys())
        self.assertEqual(document["census"]["total"], 3)
        self.assertNotIn("sites", document["census"])


if __name__ == "__main__":
    unittest.main()
