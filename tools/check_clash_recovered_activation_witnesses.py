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
from clash_dat_classes import parse_defclass
from clash_dat_lhs import recover_rule_lhs
from clash_dat_matcher_eval import FactMatcherContext, evaluate_condition
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
    {
        "name": "usunieto_armie_oddz_join_match",
        "facts": [
            {"template": "usunieto", "fields": ["armie", 42]},
            {"template": "oddz", "fields": [42]},
        ],
        "globals": {},
        "commands": ["(reset)", "(assert (usunieto armie 42))", "(assert (oddz 42))"],
        "candidate_rules": [
            "kasuj_fakty_dla_usunietej_armii_oddz",
            "kasuj_fakt_usunieto_armie",
            "kasuj_oddz",
        ],
    },
    {
        "name": "usunieto_armie_oddz_join_mismatch",
        "facts": [
            {"template": "usunieto", "fields": ["armie", 42]},
            {"template": "oddz", "fields": [43]},
        ],
        "globals": {},
        "commands": ["(reset)", "(assert (usunieto armie 42))", "(assert (oddz 43))"],
        "candidate_rules": [
            "kasuj_fakty_dla_usunietej_armii_oddz",
            "kasuj_fakt_usunieto_armie",
            "kasuj_oddz",
        ],
    },
    {
        "name": "usunieto_armie_transfer_match",
        "facts": [
            {"template": "usunieto", "fields": ["armie", 42]},
            {"template": "budowanie", "fields": ["transfer", 0, 0, 42]},
        ],
        "globals": {},
        "commands": ["(reset)", "(assert (usunieto armie 42))", "(assert (budowanie transfer 0 0 42))"],
        "candidate_rules": [
            "kasuj_fakty_dla_transferu",
            "kasuj_fakty_dla_usunietej_armii_budowanie",
            "kasuj_fakt_usunieto_armie",
        ],
    },
    {
        "name": "usunieto_armie_transfer_kind_mismatch",
        "facts": [
            {"template": "usunieto", "fields": ["armie", 42]},
            {"template": "budowanie", "fields": ["inne", 0, 0, 42]},
        ],
        "globals": {},
        "commands": ["(reset)", "(assert (usunieto armie 42))", "(assert (budowanie inne 0 0 42))"],
        "candidate_rules": [
            "kasuj_fakty_dla_transferu",
            "kasuj_fakty_dla_usunietej_armii_budowanie",
            "kasuj_fakt_usunieto_armie",
        ],
    },
    {
        "name": "ustaw_pa_object_match",
        "facts": [{"template": "gracz", "fields": [1]}],
        "objects": [
            {"name": "unit-pa-match", "class": "oddzial", "slots": {"gracz": 1, "PA": 1}},
        ],
        "globals": {},
        "commands": [
            "(reset)",
            "(assert (gracz 1))",
            "(make-instance [unit-pa-match] of oddzial (gracz 1) (PA 1))",
        ],
        "candidate_rules": ["ustaw_PA_0"],
    },
    {
        "name": "ustaw_pa_object_zero",
        "facts": [{"template": "gracz", "fields": [1]}],
        "objects": [
            {"name": "unit-pa-zero", "class": "oddzial", "slots": {"gracz": 1, "PA": 0}},
        ],
        "globals": {},
        "commands": [
            "(reset)",
            "(assert (gracz 1))",
            "(make-instance [unit-pa-zero] of oddzial (gracz 1) (PA 0))",
        ],
        "candidate_rules": ["ustaw_PA_0"],
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


def _scenario_facts(scenario: dict) -> list[dict]:
    if "facts" in scenario:
        return list(scenario["facts"])
    return [{"template": scenario["template"], "fields": scenario["fields"]}]


def _scenario_objects(scenario: dict) -> list[dict]:
    return list(scenario.get("objects", ()))


def build_bsave_oracle(
    ir: dict,
    lhs: dict,
    class_report: dict,
    scenario: dict,
) -> tuple[list[dict], list[dict]]:
    facts = _scenario_facts(scenario)
    facts_by_template = {
        item["template"]: tuple(item["fields"])
        for item in facts
    }
    objects = _scenario_objects(scenario)
    slot_id_by_name = {
        name: int(slot_id)
        for slot_id, name in class_report["slot_name_by_id"].items()
    }

    expected = []
    checks = []
    for name in scenario["candidate_rules"]:
        rule = _rule_by_name(lhs, name)
        if rule["dynamic_salience_expr"] != -1:
            raise AssertionError(f"witness candidate {name} unexpectedly has dynamic salience")

        pattern_fields: dict[int, tuple] = {}
        object_pattern_slots: dict[int, dict[int, object]] = {}
        object_pattern_addresses: dict[int, str] = {}
        condition_checks = []
        matched = True

        for order, condition in enumerate(rule["conditions"], start=1):
            if condition["kind"] == "fact":
                template = _template_name(condition)
                fields = facts_by_template.get(template)
                if fields is None:
                    matched = False
                    condition_checks.append(
                        {
                            "order": order,
                            "kind": "fact",
                            "template": template,
                            "matched": False,
                            "reason": "scenario has no fact for this template",
                        }
                    )
                    break
                current_object_slots = dict(object_pattern_slots)
                current_object_addresses = dict(object_pattern_addresses)
                context = FactMatcherContext(
                    fields=fields,
                    globals=dict(scenario["globals"]),
                    pattern_fields={**pattern_fields, order: fields},
                    object_pattern_slots=current_object_slots,
                    object_pattern_addresses=current_object_addresses,
                )
                condition_matched = evaluate_condition(ir, condition, context)
                condition_checks.append(
                    {
                        "order": order,
                        "kind": "fact",
                        "template": template,
                        "fields": list(fields),
                        "alpha_test_indices": list(condition["alpha_test_indices"]),
                        "join_test_index": condition["join_test_index"],
                        "matched": condition_matched,
                    }
                )
                if condition_matched and not condition["negated"]:
                    pattern_fields[order] = fields
            elif condition["kind"] == "object":
                allowed = set(condition.get("classes") or ())
                object_spec = next(
                    (
                        item
                        for item in objects
                        if not allowed or item["class"] in allowed
                    ),
                    None,
                )
                if object_spec is None:
                    matched = False
                    condition_checks.append(
                        {
                            "order": order,
                            "kind": "object",
                            "classes": sorted(allowed),
                            "matched": False,
                            "reason": "scenario has no object for the recovered class bitmap",
                        }
                    )
                    break

                slots_by_id = {}
                for slot_name, value in object_spec.get("slots", {}).items():
                    if slot_name not in slot_id_by_name:
                        raise AssertionError(f"unknown recovered object slot name: {slot_name}")
                    slots_by_id[slot_id_by_name[slot_name]] = value

                current_slots = {**object_pattern_slots, order: slots_by_id}
                current_addresses = {
                    **object_pattern_addresses,
                    order: object_spec["name"],
                }
                context = FactMatcherContext(
                    fields=tuple(),
                    globals=dict(scenario["globals"]),
                    pattern_fields=dict(pattern_fields),
                    object_pattern_slots=current_slots,
                    object_pattern_addresses=current_addresses,
                )
                condition_matched = evaluate_condition(ir, condition, context)
                condition_checks.append(
                    {
                        "order": order,
                        "kind": "object",
                        "class": object_spec["class"],
                        "name": object_spec["name"],
                        "slots": object_spec.get("slots", {}),
                        "classes": list(condition.get("classes") or ()),
                        "tested_slots": list(condition.get("tested_slots") or ()),
                        "alpha_test_indices": list(condition["alpha_test_indices"]),
                        "join_test_index": condition["join_test_index"],
                        "matched": condition_matched,
                    }
                )
                if condition_matched and not condition["negated"]:
                    object_pattern_slots[order] = slots_by_id
                    object_pattern_addresses[order] = object_spec["name"]
            else:
                raise AssertionError(f"unsupported recovered condition kind: {condition['kind']}")

            if not condition_matched:
                matched = False
                break

        checks.append(
            {
                "rule": name,
                "record_index": rule["index"],
                "salience": rule["salience"],
                "conditions": condition_checks,
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
    class_report = parse_defclass(source, ir)
    program, _manifest = render_recovered_program(source, ir)
    stub_source, _ = _render_host_stubs(ir)

    scenario_oracles = {}
    for scenario in SCENARIOS:
        expected, checks = build_bsave_oracle(ir, lhs, class_report, scenario)
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
            "facts": _scenario_facts(scenario),
            "objects": _scenario_objects(scenario),
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
        "equivalence_scope": "thirteen controlled activation witnesses spanning fact joins and OBJ_GET_SLOT_JNVAR1",
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
