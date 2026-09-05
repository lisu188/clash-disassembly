#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from clash_dat_rete import rete_report, render_rete_dot
from decompile_clash_dat import parse_bsave


def rule_skeleton(rule: dict) -> str:
    lines = [f"rule {rule['name']} (terminal J{rule['last_join']}):"]
    for join in rule["join_path"]:
        rhs = join.get("rhs")
        if rhs is None:
            pattern = "<unmapped>"
        elif rhs["kind"] == "fact":
            pattern = f"({rhs['template']} ... ) [fact-node {rhs['pattern_node']}]"
        else:
            pattern = (
                f"(object ... ) [alpha {rhs['alpha_node']}, "
                f"object-pattern {rhs['pattern_node']}, "
                f"class-bitmap {rhs['class_bitmap']}, slot-bitmap {rhs['slot_bitmap']}]"
            )
        if join["pattern_is_negated"]:
            pattern = f"(not {pattern})"
        test = "" if join["network_test"] == -1 else f" test=expr[{join['network_test']}]"
        lines.append(f"  {join['depth']:02d}. J{join['index']} {pattern}{test}")
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="Recover CLASH.DAT RETE join and pattern graphs")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--json", dest="json_path")
    parser.add_argument("--dot", dest="dot_path")
    parser.add_argument("--rules", dest="rules_path")
    parser.add_argument("--rule", action="append", default=[], help="print only matching rule name(s)")
    args = parser.parse_args()

    source = Path(args.input)
    ir = parse_bsave(source)
    report = rete_report(source, ir)

    joins = report["joins"]
    depths = Counter(item["depth"] for item in joins)
    negated = sum(item["pattern_is_negated"] for item in joins)
    first = sum(item["first_join"] for item in joins)

    summary = [
        "CLASH.DAT RETE recovery",
        f"joins={report['join_count']} mapped={report['mapped_join_count']}",
        f"fact-patterns={report['fact_pattern_count']} fact-joins={report['fact_owned_join_count']}",
        f"object-alphas={report['object_alpha_count']} object-patterns={report['object_pattern_count']} object-joins={report['object_owned_join_count']}",
        f"first-joins={first} negated-joins={negated} depths={dict(sorted(depths.items()))}",
    ]

    selected = report["rules"]
    if args.rule:
        wanted = set(args.rule)
        selected = [rule for rule in selected if rule["name"] in wanted]
    skeletons = "\n\n".join(rule_skeleton(rule) for rule in selected)

    print("\n".join(summary))
    if args.rule:
        print()
        print(skeletons)

    if args.json_path:
        Path(args.json_path).write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8")
    if args.dot_path:
        Path(args.dot_path).write_text(render_rete_dot(report), encoding="utf-8")
    if args.rules_path:
        Path(args.rules_path).write_text(skeletons + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
