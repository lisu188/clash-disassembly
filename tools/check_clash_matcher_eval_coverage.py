#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from clash_dat_lhs import recover_rule_lhs
from clash_dat_matcher_eval import SUPPORTED_FACT_MATCHER_PRIMITIVE_TYPES
from clash_dat_primitives import DECODED_BITMAP_TYPES, TYPE_NAMES
from decompile_clash_dat import parse_bsave

RETAIL_FACT_MATCHER_PRIMITIVE_TYPES = frozenset({24, 25, 28, 31, 33})


def _siblings(ir: dict, start: int) -> list[int]:
    result = []
    seen = set()
    current = start
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in expression sibling chain at {current}")
        if not 0 <= current < len(ir["expressions"]):
            raise ValueError(f"expression sibling chain points outside array: {current}")
        seen.add(current)
        result.append(current)
        current = ir["expressions"][current][3]
    return result


def _walk_expression(ir: dict, root: int) -> set[int]:
    result: set[int] = set()
    stack = [root]
    while stack:
        index = stack.pop()
        if index == -1 or index in result:
            continue
        if not 0 <= index < len(ir["expressions"]):
            raise ValueError(f"expression tree points outside array: {index}")
        result.add(index)
        arg = ir["expressions"][index][2]
        if arg != -1:
            stack.extend(_siblings(ir, arg))
    return result


def coverage_report(source: Path) -> dict:
    ir = parse_bsave(source)
    lhs = recover_rule_lhs(source, ir)

    fact_only_rules = [
        rule
        for rule in lhs["rules"]
        if all(condition["kind"] == "fact" for condition in rule["conditions"])
    ]

    occurrences: Counter[int] = Counter()
    rule_types: dict[str, list[int]] = {}
    for rule in fact_only_rules:
        types: set[int] = set()
        roots = []
        for condition in rule["conditions"]:
            roots.extend(int(index) for index in condition.get("alpha_test_indices", ()))
            join_test = int(condition.get("join_test_index", -1))
            if join_test != -1:
                roots.append(join_test)

        for root in roots:
            for index in _walk_expression(ir, root):
                type_id = int(ir["expressions"][index][0])
                if type_id in DECODED_BITMAP_TYPES:
                    occurrences[type_id] += 1
                    types.add(type_id)
        rule_types[rule["name"]] = sorted(types)

    used = frozenset(occurrences)
    unsupported = used - SUPPORTED_FACT_MATCHER_PRIMITIVE_TYPES

    return {
        "source": source.name,
        "fact_only_rule_count": len(fact_only_rules),
        "used_primitive_types": sorted(used),
        "used_primitive_names": [TYPE_NAMES[type_id] for type_id in sorted(used)],
        "supported_primitive_types": sorted(SUPPORTED_FACT_MATCHER_PRIMITIVE_TYPES),
        "unsupported_primitive_types": sorted(unsupported),
        "occurrences": {
            TYPE_NAMES[type_id]: occurrences[type_id]
            for type_id in sorted(occurrences)
        },
        "rules_by_primitive": {
            TYPE_NAMES[type_id]: sorted(
                name for name, types in rule_types.items() if type_id in types
            )
            for type_id in sorted(used)
        },
        "retail_contract_types": sorted(RETAIL_FACT_MATCHER_PRIMITIVE_TYPES),
        "complete": not unsupported and used == RETAIL_FACT_MATCHER_PRIMITIVE_TYPES,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description="Audit direct-BSAVE evaluator coverage for fact-only matchers")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--json")
    args = parser.parse_args()

    report = coverage_report(Path(args.input))
    if args.json:
        Path(args.json).write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    if report["used_primitive_types"] != report["retail_contract_types"]:
        raise AssertionError(
            f"retail fact matcher primitive set changed: "
            f"{report['used_primitive_types']} != {report['retail_contract_types']}"
        )
    if report["unsupported_primitive_types"]:
        raise AssertionError(
            f"direct matcher evaluator lacks primitive types: {report['unsupported_primitive_types']}"
        )
    if not report["complete"]:
        raise AssertionError("fact matcher primitive coverage is incomplete")

    print("CLASH.DAT fact matcher oracle coverage: PASS")
    print(
        f"fact-only-rules={report['fact_only_rule_count']} "
        f"primitive-types={report['used_primitive_types']} "
        f"occurrences={report['occurrences']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
