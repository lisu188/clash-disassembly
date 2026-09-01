#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path

from clash_dat_lhs import recover_rule_lhs, render_recovered_lhs, render_rule
from decompile_clash_dat import parse_bsave


def main() -> int:
    parser = argparse.ArgumentParser(description="Recover source-like CLASH.DAT rule LHS from compiled RETE")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--json", dest="json_path")
    parser.add_argument("--clp", dest="clp_path")
    parser.add_argument("--rule", action="append", default=[], help="print matching rule(s)")
    args = parser.parse_args()

    source = Path(args.input)
    ir = parse_bsave(source)
    report = recover_rule_lhs(source, ir)

    print("CLASH.DAT LHS recovery")
    print(f"rules={report['rule_count']} condition-occurrences={report['condition_occurrence_count']}")
    print(
        "classes={classes} slot-names={slot_names} slot-descriptors={slot_descriptors}".format(
            **report["class_report"]["counts"]
        )
    )

    if args.rule:
        wanted = set(args.rule)
        for rule in report["rules"]:
            if rule["name"] in wanted:
                print()
                print(render_rule(rule, ir, report["class_report"]))

    if args.json_path:
        Path(args.json_path).write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8")
    if args.clp_path:
        Path(args.clp_path).write_text(render_recovered_lhs(report, ir), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
