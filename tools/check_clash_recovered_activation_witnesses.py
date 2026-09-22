#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

from check_clash_recovered_clips_load import ERROR_MARKERS, _clips_string, _render_host_stubs
from clash_dat_lhs import recover_rule_lhs
from clash_dat_matcher_eval import FactMatcherContext, evaluate_fact_condition
from decompile_clash_dat import parse_bsave
from generate_clash_recovered_constraints import render_recovered_program

ACTIVATION_RE = re.compile(r"^\s*(-?\d+)\s+([^:\s]+):", re.MULTILINE)
DONE_RE = re.compile(r"^CLASH_ACTIVATION_WITNESSES_DONE$", re.MULTILINE)

SCENARIOS = [
    {
        "name": "misja_1",
        "template": "misja",
        "fields": [1],
        "globals": {"zasieg_dzialan": 10},
        "commands": ["(reset)", "(assert (misja 1))"],
        "candidate_rules": ["zmiana_zasiegu_misja_1", "zmiana_zasiegu_misja_11"],
    },
    {
        "name": "misja_11",
        "template": "misja",
        "fields": [11],
        "globals": {"zasieg_dzialan": 10},
        "commands": ["(reset)", "(assert (misja 11))"],
        "candidate_rules": ["zmiana_zasiegu_misja_1", "zmiana_zasiegu_misja_11"],
    },
    {
        "name": "misja_1_wrong_global",
        "template": "misja",
        "fields": [1],
        "globals": {"zasieg_dzialan": 9},
        "commands": ["(reset)", "(bind ?*zasieg_dzialan* 9)", "(assert (misja 1))"],
        "candidate_rules": ["zmiana_zasiegu_misja_1", "zmiana_zasiegu_misja_11"],
    },
    {
        "name": "najblizej_six_fields",
        "template": "najblizej",
        "fields": [0, 0, 0, 0, 0, 0],
        "globals": {},
        "commands": ["(reset)", "(assert (najblizej 0 0 0 0 0 0))"],
        "candidate_rules": ["ustaw_odleglosc_waga", "kasuj_najblizej"],
    },
    {
        "name": "najblizej_five_fields",
        "template": "najblizej",
        "fields": [0, 0, 0, 0, 0],
        "globals": {},
        "commands": ["(reset)", "(assert (najblizej 0 0 0 0 0))"],
        "candidate_rules": ["ustaw_odleglosc_waga", "kasuj_najblizej"],
    },
    {
        "name": "kasuj_swiatynie",
        "template": "kasuj",
        "fields": ["swiatynie", 0, 0],
        "globals": {},
        "commands": ["(reset)", "(assert (kasuj swiatynie 0 0))"],
        "candidate_rules": ["kasuj_kasuj_swiatynie"],
    },
    {
        "name": "kasuj_wrong_constant",
        "template": "kasuj",
        "fields": ["nie_swiatynie", 0, 0],
        "globals": {},
        "commands": ["(reset)", "(assert (kasuj nie_swiatynie 0 0))"],
        "candidate_rules": ["kasuj_kasuj_swiatynie"],
    },
]


def parse_scenario_agenda(output: str, name: str) -> list[dict]:
    begin_marker = f"CLASH_SCENARIO_BEGIN|{name}"
    end_marker = f"CLASH_SCENARIO_END|{name}"
    begin = output.find(begin_marker)
    end = output.find(end_marker, begin + len(begin_marker))
    if begin < 0 or end < 0:
        raise AssertionError(f"missing agenda markers for scenario {name}")
    segment = output[begin + len(begin_marker):end]
    return [
        {"salience": int(salience), "name": rule_name}
        for salience, rule_name in ACTIVATION_RE.findall(segment)
    ]


def _rule_by_name(lhs: dict, name: str) -> dict:
    matches = [rule for rule in lhs["rules"] if rule["name"] == name]
    if len(matches) != 1:
        raise AssertionError(f"expected exactly one recovered rule named {name}, found {len(matches)}")
    return matches[0]


def _template_name(condition: dict) -> str:
    if condition["kind"] != "fact":
        raise AssertionError("activation witness candidate is not a fact condition")
    return condition["pattern"].split("(", 1)[1].split(None, 1)[0]


def build_bsave_oracle(ir: dict, lhs: dict, scenario: dict) -> tuple[list[dict], list[dict]]:
    context = FactMatcherContext(
        fields=tuple(scenario["fields"]),
        globals=dict(scenario["globals"]),
    )
    expected = []
    checks = []
    for name in scenario["candidate_rules"]:
        rule = _rule_by_name(lhs, name)
        if len(rule["conditions"]) != 1:
            raise AssertionError(f"witness candidate {name} is no longer a one-condition rule")
        if rule["dynamic_salience_expr"] != -1:
            raise AssertionError(f"witness candidate {name} unexpectedly has dynamic salience")
        condition = rule["conditions"][0]
        template = _template_name(condition)
        if template != scenario["template"]:
            raise AssertionError(
                f"witness candidate {name} template {template} != {scenario['template']}"
            )
        matched = evaluate_fact_condition(ir, condition, context)
        checks.append(
            {
                "rule": name,
                "record_index": rule["index"],
                "salience": rule["salience"],
                "alpha_test_indices": list(condition["alpha_test_indices"]),
                "join_test_index": condition["join_test_index"],
                "matched": matched,
            }
        )
        if matched:
            expected.append({"salience": rule["salience"], "name": name})
    expected.sort(key=lambda item: item["salience"], reverse=True)
    return expected, checks


def run_activation_witnesses(source: Path, clips_exe: str) -> tuple[str, dict]:
    ir = parse_bsave(source)
    lhs = recover_rule_lhs(source, ir)
    program, _manifest = render_recovered_program(source, ir)
    stub_source, _ = _render_host_stubs(ir)

    scenario_oracles = {}
    for scenario in SCENARIOS:
        expected, checks = build_bsave_oracle(ir, lhs, scenario)
        scenario_oracles[scenario["name"]] = {
            "expected": expected,
            "checks": checks,
        }

    with tempfile.TemporaryDirectory(prefix="clash-clips-activation-witnesses-") as tmp_name:
        tmp = Path(tmp_name)
        recovered = tmp / "CLASH_recovered.clp"
        stubs = tmp / "host_stubs.clp"
        batch = tmp / "activation_witnesses.clp"
        recovered.write_text(program, encoding="utf-8")
        stubs.write_text(stub_source, encoding="utf-8")

        commands = [
            "(clear)",
            f'(load "{_clips_string(stubs)}")',
            f'(load "{_clips_string(recovered)}")',
        ]
        for scenario in SCENARIOS:
            commands.extend(scenario["commands"])
            commands.extend(
                [
                    f'(printout t "CLASH_SCENARIO_BEGIN|{scenario["name"]}" crlf)',
                    "(agenda)",
                    f'(printout t "CLASH_SCENARIO_END|{scenario["name"]}" crlf)',
                ]
            )
        commands.extend(
            [
                '(printout t "CLASH_ACTIVATION_WITNESSES_DONE" crlf)',
                "(exit)",
                "",
            ]
        )
        batch.write_text("\n".join(commands), encoding="utf-8")

        proc = subprocess.run(
            [clips_exe, "-f2", str(batch)],
            cwd=tmp,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace",
            check=False,
            timeout=90,
        )

    output = proc.stdout
    if proc.returncode != 0:
        raise AssertionError(f"CLIPS exited with {proc.returncode}\n{output}")
    if not DONE_RE.search(output):
        raise AssertionError(f"CLIPS did not finish activation witness run\n{output}")
    if any(marker in output for marker in ERROR_MARKERS):
        raise AssertionError(f"CLIPS reported parser/runtime diagnostics\n{output}")

    details = []
    failures = []
    for scenario in SCENARIOS:
        oracle = scenario_oracles[scenario["name"]]
        actual = parse_scenario_agenda(output, scenario["name"])
        detail = {
            "name": scenario["name"],
            "template": scenario["template"],
            "fields": scenario["fields"],
            "globals": scenario["globals"],
            "commands": scenario["commands"],
            "bsave_oracle": oracle["checks"],
            "expected": oracle["expected"],
            "actual": actual,
            "matches": actual == oracle["expected"],
        }
        details.append(detail)
        if not detail["matches"]:
            failures.append(detail)

    report = {
        "source": source.name,
        "scenario_count": len(details),
        "matching_scenario_count": len(details) - len(failures),
        "mismatch_count": len(failures),
        "scenarios": details,
        "oracle": "direct evaluation of recovered BSAVE matcher expressions",
        "behavioral_equivalence_verified": False,
        "equivalence_scope": "seven controlled fact-only activation witnesses",
    }
    if failures:
        raise AssertionError("activation witness mismatch: " + json.dumps(failures, sort_keys=True))
    return output, report


def main() -> int:
    parser = argparse.ArgumentParser(description="Validate non-empty recovered-rule activation witnesses")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clips", default=os.environ.get("CLIPS", "clips"))
    parser.add_argument("--json")
    args = parser.parse_args()
    clips_exe = shutil.which(args.clips) if os.path.sep not in args.clips else args.clips
    if not clips_exe or not Path(clips_exe).exists():
        raise SystemExit(f"CLIPS executable not found: {args.clips}")
    _, report = run_activation_witnesses(Path(args.input), clips_exe)
    if args.json:
        Path(args.json).write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("CLASH_recovered.clp activation-witness contract: PASS")
    print(
        f"scenarios={report['scenario_count']} matched={report['matching_scenario_count']} "
        f"mismatches={report['mismatch_count']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
