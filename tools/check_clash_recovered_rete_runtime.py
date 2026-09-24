#!/usr/bin/env python3
"""Validate recovered rule path depth after recompilation by stock CLIPS."""
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

DONE_RE = re.compile(r"^CLASH_RETE_DONE$", re.MULTILINE)
BEGIN_RE = re.compile(r"^CLASH_RULE_BEGIN\|([^|]+)\|([0-9]+)$", re.MULTILINE)
PATTERN_RE = re.compile(r"^Matches for Pattern ([0-9]+)$", re.MULTILINE)


def parse_rule_match_depths(output: str) -> dict[str, dict]:
    markers = list(BEGIN_RE.finditer(output))
    result: dict[str, dict] = {}
    for index, marker in enumerate(markers):
        name = marker.group(1)
        expected = int(marker.group(2))
        end_marker = f"CLASH_RULE_END|{name}"
        search_end = markers[index + 1].start() if index + 1 < len(markers) else len(output)
        segment = output[marker.end():search_end]
        end_at = segment.find(end_marker)
        if end_at < 0:
            raise AssertionError(f"missing end marker for {name}")
        patterns = [int(value) for value in PATTERN_RE.findall(segment[:end_at])]
        if patterns != list(range(1, len(patterns) + 1)):
            raise AssertionError(f"non-contiguous CLIPS pattern numbering for {name}: {patterns}")
        result[name] = {
            "expected_condition_count": expected,
            "compiled_pattern_count": len(patterns),
            "matches": len(patterns) == expected,
        }
    return result


def run_rete_depth_test(source: Path, clips_exe: str) -> tuple[str, dict]:
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    stub_source, _ = _render_host_stubs(ir)

    with tempfile.TemporaryDirectory(prefix="clash-clips-rete-") as tmp_name:
        tmp = Path(tmp_name)
        recovered = tmp / "CLASH_recovered.clp"
        stubs = tmp / "host_stubs.clp"
        batch = tmp / "rete.clp"
        recovered.write_text(program, encoding="utf-8")
        stubs.write_text(stub_source, encoding="utf-8")
        commands = [
            "(clear)",
            f'(load "{_clips_string(stubs)}")',
            f'(load "{_clips_string(recovered)}")',
            '(printout t "CLASH_RETE_BEGIN" crlf)',
        ]
        for rule in manifest["rules_manifest"]:
            name = rule["output_name"]
            count = rule["condition_count"]
            commands.extend([
                f'(printout t "CLASH_RULE_BEGIN|{name}|{count}" crlf)',
                f"(matches {name})",
                f'(printout t "CLASH_RULE_END|{name}" crlf)',
            ])
        commands.extend([
            '(printout t "CLASH_RETE_DONE" crlf)',
            "(exit)",
            "",
        ])
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
        raise AssertionError(f"CLIPS did not finish RETE-depth inspection\n{output}")
    if any(marker in output for marker in ERROR_MARKERS):
        raise AssertionError(f"CLIPS reported parser/runtime diagnostics\n{output}")

    rules = parse_rule_match_depths(output)
    expected_names = {rule["output_name"] for rule in manifest["rules_manifest"]}
    if set(rules) != expected_names:
        missing = sorted(expected_names - set(rules))
        extra = sorted(set(rules) - expected_names)
        raise AssertionError(f"rule marker mismatch: missing={missing} extra={extra}")

    mismatches = {
        name: detail for name, detail in rules.items()
        if not detail["matches"]
    }
    report = {
        "source": source.name,
        "rules": len(rules),
        "expected_condition_occurrences": manifest["conditions"],
        "compiled_pattern_occurrences": sum(item["compiled_pattern_count"] for item in rules.values()),
        "matching_rule_count": len(rules) - len(mismatches),
        "mismatch_count": len(mismatches),
        "mismatches": mismatches,
        "rules_detail": rules,
        "behavioral_equivalence_verified": False,
    }
    if mismatches:
        raise AssertionError(
            "recompiled rule path depth differs from recovered retail conditions: "
            + json.dumps(mismatches, sort_keys=True)
        )
    if report["compiled_pattern_occurrences"] != manifest["conditions"]:
        raise AssertionError(
            f"compiled pattern occurrence total mismatch: {report['compiled_pattern_occurrences']} "
            f"!= {manifest['conditions']}"
        )
    return output, report


def main() -> int:
    parser = argparse.ArgumentParser(description="Compare recovered condition counts with stock-CLIPS compiled rule paths")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clips", default=os.environ.get("CLIPS", "clips"))
    parser.add_argument("--json")
    args = parser.parse_args()
    clips_exe = shutil.which(args.clips) if os.path.sep not in args.clips else args.clips
    if not clips_exe or not Path(clips_exe).exists():
        raise SystemExit(f"CLIPS executable not found: {args.clips}")
    _, report = run_rete_depth_test(Path(args.input), clips_exe)
    if args.json:
        Path(args.json).write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print("CLASH_recovered.clp stock-CLIPS RETE path-depth contract: PASS")
    print(
        f"rules={report['rules']} matched={report['matching_rule_count']} "
        f"patterns={report['compiled_pattern_occurrences']} mismatches={report['mismatch_count']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
