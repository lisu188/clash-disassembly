#!/usr/bin/env python3
"""Validate the first activation-level invariant of the recovered CLASH rules.

The recovered source does not emit game facts or instances on reset. Stock CLIPS
does create the system initial-fact deffacts, matching the single deffacts record
serialized in retail CLASH.DAT. This gives a deterministic zero-game-state
working memory whose agenda can be predicted directly from the recovered LHS.
"""
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

DONE_RE = re.compile(r"^CLASH_RESET_AGENDA_DONE$", re.MULTILINE)
AGENDA_BEGIN = "CLASH_RESET_AGENDA_BEGIN"
AGENDA_END = "CLASH_RESET_AGENDA_END"
ACTIVATION_RE = re.compile(r"^\s*(-?\d+)\s+([^:\s]+):", re.MULTILINE)


def condition_matches_reset(condition: dict) -> bool:
    binding = condition["binding"]
    kind = binding["kind"]
    negated = bool(condition["negated"])

    if kind == "fact":
        present = binding.get("template") == "initial-fact"
    elif kind == "object":
        present = False
    else:
        raise AssertionError(f"unknown recovered condition kind: {kind!r}")

    return not present if negated else present


def expected_reset_activations(manifest: dict) -> list[dict]:
    expected = []
    for rule in manifest["rules_manifest"]:
        if all(condition_matches_reset(condition) for condition in rule["conditions"]):
            expected.append(
                {
                    "name": rule["output_name"],
                    "salience": rule["salience"],
                    "record_index": rule["record_index"],
                    "condition_count": rule["condition_count"],
                }
            )
    return expected


def parse_agenda(output: str) -> list[dict]:
    begin = output.find(AGENDA_BEGIN)
    end = output.find(AGENDA_END, begin + len(AGENDA_BEGIN))
    if begin < 0 or end < 0:
        raise AssertionError("missing reset agenda output markers")
    segment = output[begin + len(AGENDA_BEGIN):end]
    return [
        {"salience": int(salience), "name": name}
        for salience, name in ACTIVATION_RE.findall(segment)
    ]


def run_reset_agenda_test(source: Path, clips_exe: str) -> tuple[str, dict]:
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    stub_source, _ = _render_host_stubs(ir)
    expected = expected_reset_activations(manifest)

    with tempfile.TemporaryDirectory(prefix="clash-clips-reset-agenda-") as tmp_name:
        tmp = Path(tmp_name)
        recovered = tmp / "CLASH_recovered.clp"
        stubs = tmp / "host_stubs.clp"
        batch = tmp / "reset_agenda.clp"
        recovered.write_text(program, encoding="utf-8")
        stubs.write_text(stub_source, encoding="utf-8")
        batch.write_text(
            "\n".join(
                [
                    "(clear)",
                    f'(load "{_clips_string(stubs)}")',
                    f'(load "{_clips_string(recovered)}")',
                    "(reset)",
                    f'(printout t "{AGENDA_BEGIN}" crlf)',
                    "(agenda)",
                    f'(printout t "{AGENDA_END}" crlf)',
                    '(printout t "CLASH_RESET_AGENDA_DONE" crlf)',
                    "(exit)",
                    "",
                ]
            ),
            encoding="utf-8",
        )
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
        raise AssertionError(f"CLIPS did not finish reset-agenda inspection\n{output}")
    if any(marker in output for marker in ERROR_MARKERS):
        raise AssertionError(f"CLIPS reported parser/runtime diagnostics\n{output}")

    actual = parse_agenda(output)
    expected_by_name = {item["name"]: item for item in expected}
    actual_by_name: dict[str, list[int]] = {}
    for item in actual:
        actual_by_name.setdefault(item["name"], []).append(item["salience"])

    missing = sorted(set(expected_by_name) - set(actual_by_name))
    unexpected = sorted(set(actual_by_name) - set(expected_by_name))
    duplicate = sorted(name for name, values in actual_by_name.items() if len(values) != 1)
    salience_mismatches = {
        name: {
            "expected": expected_by_name[name]["salience"],
            "actual": actual_by_name[name][0],
        }
        for name in sorted(set(expected_by_name).intersection(actual_by_name))
        if len(actual_by_name[name]) == 1
        and actual_by_name[name][0] != expected_by_name[name]["salience"]
    }

    report = {
        "source": source.name,
        "working_memory": "stock CLIPS reset with only system initial-fact and no emitted game instances",
        "rules": manifest["rules"],
        "expected_activation_count": len(expected),
        "actual_activation_count": len(actual),
        "expected": expected,
        "actual": actual,
        "missing": missing,
        "unexpected": unexpected,
        "duplicate": duplicate,
        "salience_mismatches": salience_mismatches,
        "matches": not missing and not unexpected and not duplicate and not salience_mismatches,
        "behavioral_equivalence_verified": False,
        "equivalence_scope": "zero-game-state reset agenda only",
    }
    if not report["matches"]:
        raise AssertionError(
            "recovered reset agenda differs from the LHS oracle: "
            + json.dumps(
                {
                    "missing": missing,
                    "unexpected": unexpected,
                    "duplicate": duplicate,
                    "salience_mismatches": salience_mismatches,
                },
                sort_keys=True,
            )
        )
    return output, report


def main() -> int:
    parser = argparse.ArgumentParser(description="Compare recovered reset-time rule eligibility with stock-CLIPS agenda")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clips", default=os.environ.get("CLIPS", "clips"))
    parser.add_argument("--json")
    args = parser.parse_args()
    clips_exe = shutil.which(args.clips) if os.path.sep not in args.clips else args.clips
    if not clips_exe or not Path(clips_exe).exists():
        raise SystemExit(f"CLIPS executable not found: {args.clips}")
    _, report = run_reset_agenda_test(Path(args.input), clips_exe)
    if args.json:
        Path(args.json).write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("CLASH_recovered.clp reset-agenda contract: PASS")
    print(
        f"rules={report['rules']} expected-activations={report['expected_activation_count']} "
        f"actual-activations={report['actual_activation_count']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
