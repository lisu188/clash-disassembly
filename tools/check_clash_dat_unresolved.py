#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
from collections import Counter
from pathlib import Path

from clash_dat_primitives import TYPE_NAMES, decode_primitive
from decompile_clash_dat import parse_bsave
from generate_clash_recovered_constraints import render_recovered_program


def primitive_family(source: str) -> str:
    match = re.match(r"\s*\(*\s*([^\s(),]+)", source)
    return match.group(1) if match else "<unknown>"


def expression_evidence(ir: dict, root: int) -> list[dict]:
    expressions = ir["expressions"]
    nodes = []
    visited: set[int] = set()
    active: set[int] = set()
    pending = [(root, False)]
    while pending:
        index, leaving = pending.pop()
        if leaving:
            active.remove(index)
            visited.add(index)
            continue
        if not 0 <= index < len(expressions):
            raise ValueError(f"matcher expression points outside array: {index}")
        if index in active:
            raise ValueError(f"cycle in matcher expression at {index}")
        if index in visited:
            continue
        active.add(index)
        type_id, value, arg, next_index = expressions[index]
        node = {
            "expression_index": index,
            "type": type_id,
            "type_name": TYPE_NAMES.get(type_id, f"TYPE_{type_id}"),
            "value_index": value,
            "arg_index": arg,
            "next_index": next_index,
        }
        if type_id == 10 and 0 <= value < len(ir.get("functions", [])):
            node["function"] = ir["functions"][value]
        primitive = decode_primitive(expressions[index], ir, index)
        if primitive is not None:
            node["primitive"] = primitive.as_json()
        nodes.append(node)
        children = []
        sibling_seen: set[int] = set()
        while arg != -1:
            if not 0 <= arg < len(expressions):
                raise ValueError(f"matcher argument points outside array: {arg}")
            if arg in sibling_seen:
                raise ValueError(f"cycle in matcher argument chain at {arg}")
            sibling_seen.add(arg)
            children.append(arg)
            arg = expressions[arg][3]
        pending.append((index, True))
        pending.extend((child, False) for child in reversed(children))
    return nodes


def inventory_from_manifest(path: Path, ir: dict, manifest: dict) -> dict:
    entries = []
    for rule in manifest["rules_manifest"]:
        for condition in rule["conditions"]:
            translations = condition["translations"]
            binding = condition["binding"]
            roots = [(index, "alpha") for index in condition["alpha_test_indices"]]
            if condition["join_test_index"] != -1:
                roots.append((condition["join_test_index"], "join"))
            if len(roots) != len(translations):
                raise ValueError(f"matcher provenance mismatch in {rule['output_name']} CE{condition['condition']}")
            binding_blocks_tests = (
                binding["kind"] == "fact"
                and binding.get("fields") is None
                and any(item["translated"] is not None for item in translations)
            )
            condition_entries = []
            for item, (root, phase) in zip(translations, roots):
                if item["translated"] is not None and not binding_blocks_tests:
                    continue
                reason = item["reason"] or "source form lacks a legal binding"
                condition_entries.append({
                    "rule_record": rule["record_index"],
                    "rule": rule["original_name"],
                    "output_rule": rule["output_name"],
                    "terminal_join": rule["terminal_join"],
                    "condition": condition["condition"],
                    "binding_kind": binding["kind"],
                    "join_index": condition["join_index"],
                    "depth": condition["depth"],
                    "negated": condition["negated"],
                    "phase": phase,
                    "expression_index": root,
                    "expression_nodes": expression_evidence(ir, root),
                    "primitive_family": primitive_family(item["source"]),
                    "source": item["source"],
                    "candidate_translation": item["translated"],
                    "reason": reason,
                })
            if len(condition_entries) != condition["unresolved_test_count"]:
                raise ValueError(f"unresolved count mismatch in {rule['output_name']} CE{condition['condition']}")
            entries.extend(condition_entries)

    if len(entries) != manifest["unresolved_test_count"]:
        raise ValueError("unresolved matcher total does not match inventory")
    if manifest["compiled_test_count"] != manifest["translated_test_count"] + len(entries):
        raise ValueError("compiled matcher total does not match translation totals")

    by_reason = Counter(item["reason"] for item in entries)
    by_family = Counter(item["primitive_family"] for item in entries)
    by_rule = Counter(item["output_rule"] for item in entries)
    by_nested_primitive: Counter[str] = Counter()
    by_payload: Counter[str] = Counter()
    for item in entries:
        for node in item["expression_nodes"]:
            primitive = node.get("primitive")
            if primitive is not None:
                by_nested_primitive[primitive["type_name"]] += 1
                by_payload[f"{primitive['type_name']}:{primitive['raw_hex']}"] += 1

    return {
        "schema_version": 2,
        "source": path.name,
        "compiled_test_count": manifest["compiled_test_count"],
        "translated_test_count": manifest["translated_test_count"],
        "unresolved_test_count": len(entries),
        "translation_coverage_percent": round(
            100.0 * manifest["translated_test_count"] / manifest["compiled_test_count"], 2
        ) if manifest["compiled_test_count"] else 100.0,
        "fully_translated_rule_count": sum(
            rule["unresolved_test_count"] == 0 for rule in manifest["rules_manifest"]
        ),
        "unresolved_negated_test_count": sum(item["negated"] for item in entries),
        "behavioral_equivalence_verified": False,
        "by_reason": dict(sorted(by_reason.items())),
        "by_primitive_family": dict(sorted(by_family.items())),
        "by_nested_primitive": dict(sorted(by_nested_primitive.items())),
        "by_primitive_payload": dict(sorted(by_payload.items())),
        "nested_count_semantics": "Unique expression nodes per unresolved test occurrence; contained primitives are not individually proven failure causes.",
        "by_rule": dict(sorted(by_rule.items())),
        "entries": entries,
    }


def build_inventory(path: Path) -> dict:
    ir = parse_bsave(path)
    _, manifest = render_recovered_program(path, ir)
    return inventory_from_manifest(path, ir, manifest)


def main() -> int:
    parser = argparse.ArgumentParser(description="Inventory unresolved CLASH.DAT compiled matcher tests")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--json")
    args = parser.parse_args()

    report = build_inventory(Path(args.input))
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")

    print(
        "CLASH.DAT unresolved matcher inventory: "
        f"compiled={report['compiled_test_count']} "
        f"translated={report['translated_test_count']} "
        f"unresolved={report['unresolved_test_count']} "
        f"coverage={report['translation_coverage_percent']:.2f}% "
        f"fully-translated-rules={report['fully_translated_rule_count']} "
        f"unresolved-under-not={report['unresolved_negated_test_count']}"
    )
    for title, field in (
        ("by primitive family", "by_primitive_family"),
        ("contained primitive nodes (not isolated failure causes)", "by_nested_primitive"),
        ("by reason", "by_reason"),
    ):
        print(title + ":")
        for name, count in sorted(report[field].items(), key=lambda item: (-item[1], item[0])):
            print(f"  {count:4d}  {name}")
    if args.json:
        print(args.json)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
