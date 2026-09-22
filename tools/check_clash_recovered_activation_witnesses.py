#!/usr/bin/env python3
"""Exercise recovered strategic-AI matchers with non-empty working-memory witnesses."""
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
from decompile_clash_dat import parse_bsave
from generate_clash_recovered_constraints import render_recovered_program

ACTIVATION_RE = re.compile(r"^\s*(-?\d+)\s+([^:\s]+):", re.MULTILINE)
DONE_RE = re.compile(r"^CLASH_ACTIVATION_WITNESSES_DONE$", re.MULTILINE)

SCENARIOS = [
    {
        "name": "misja_1",
        "commands": ["(reset)", "(assert (misja 1))"],
        "expected": [{"salience": 9900, "name": "zmiana_zasiegu_misja_1"}],
    },
    {
        "name": "misja_11",
        "commands": ["(reset)", "(assert (misja 11))"],
        "expected": [{"salience": 9900, "name": "zmiana_zasiegu_misja_11"}],
    },
    {
        "name": "misja_1_wrong_global",
        "commands": ["(reset)", "(bind ?*zasieg_dzialan* 9)", "(assert (misja 1))"],
        "expected": [],
    },
    {
        "name": "najblizej_six_fields",
        "commands": ["(reset)", "(assert (najblizej 0 0 0 0 0 0))"],
        "expected": [
            {"salience": 801, "name": "ustaw_odleglosc_waga"},
            {"salience": -9000, "name": "kasuj_najblizej"},
        ],
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


def _rule_by_name(manifest: dict, name: str) -> dict:
    matches = [rule for rule in manifest["rules_manifest"] if rule["output_name"] == name]
    if len(matches) != 1:
        raise AssertionError(f"expected exactly one recovered rule named {name}, found {len(matches)}")
    return matches[0]


def validate_witness_evidence(manifest: dict) -> None:
    mission_1 = _rule_by_name(manifest, "zmiana_zasiegu_misja_1")
    mission_11 = _rule_by_name(manifest, "zmiana_zasiegu_misja_11")
    nearest_weight = _rule_by_name(manifest, "ustaw_odleglosc_waga")
    nearest_cleanup = _rule_by_name(manifest, "kasuj_najblizej")

    for rule, value in ((mission_1, 1), (mission_11, 11)):
        assert rule["salience"] == 9900
        assert rule["condition_count"] == 1
        condition = rule["conditions"][0]
        assert condition["binding"]["kind"] == "fact"
        assert condition["binding"]["template"] == "misja"
        assert condition["compiled_test_count"] == 2
        assert condition["translated_test_count"] == 2
        translations = [item["translated"] for item in condition["translations"]]
        assert translations == [
            f"(and (= (length$ $?f1_fields) 1) (= (nth$ 1 $?f1_fields) {value}))",
            "(= ?*zasieg_dzialan* 10)",
        ]

    assert nearest_weight["salience"] == 801
    assert nearest_weight["condition_count"] == 1
    nearest_condition = nearest_weight["conditions"][0]
    assert nearest_condition["binding"]["template"] == "najblizej"
    assert [item["translated"] for item in nearest_condition["translations"]] == [
        "(= (length$ $?f1_fields) 6)"
    ]

    assert nearest_cleanup["salience"] == -9000
    assert nearest_cleanup["condition_count"] == 1
    cleanup_condition = nearest_cleanup["conditions"][0]
    assert cleanup_condition["binding"]["template"] == "najblizej"
    assert cleanup_condition["compiled_test_count"] == 0


def run_activation_witnesses(source: Path, clips_exe: str) -> tuple[str, dict]:
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    validate_witness_evidence(manifest)
    stub_source, _ = _render_host_stubs(ir)

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
        actual = parse_scenario_agenda(output, scenario["name"])
        detail = {
            "name": scenario["name"],
            "commands": scenario["commands"],
            "expected": scenario["expected"],
            "actual": actual,
            "matches": actual == scenario["expected"],
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
        "behavioral_equivalence_verified": False,
        "equivalence_scope": "four controlled fact-only activation witnesses",
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
