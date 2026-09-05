#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from decompile_clash_dat import parse_bsave
from generate_clash_recovered_constraints import render_recovered_program


def primitive_family(source: str) -> str:
    head, separator, _ = source.partition("(")
    return head if separator else source


def build_inventory(path: Path) -> dict:
    ir = parse_bsave(path)
    _, manifest = render_recovered_program(path, ir)
    entries = []

    for rule in manifest["rules_manifest"]:
        for condition in rule["conditions"]:
            translations = condition["translations"]
            binding = condition["binding"]
            binding_blocks_tests = (
                binding["kind"] == "fact"
                and binding.get("fields") is None
                and any(item["translated"] is not None for item in translations)
            )
            condition_entries = []
            for item in translations:
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
                    "primitive_family": primitive_family(item["source"]),
                    "source": item["source"],
                    "candidate_translation": item["translated"],
                    "reason": reason,
                })
            assert len(condition_entries) == condition["unresolved_test_count"], (
                rule["output_name"],
                condition["condition"],
                len(condition_entries),
                condition["unresolved_test_count"],
            )
            entries.extend(condition_entries)

    assert len(entries) == manifest["unresolved_test_count"]
    assert manifest["compiled_test_count"] == (
        manifest["translated_test_count"] + manifest["unresolved_test_count"]
    )

    by_reason = Counter(item["reason"] for item in entries)
    by_family = Counter(item["primitive_family"] for item in entries)
    by_rule = Counter(item["output_rule"] for item in entries)

    return {
        "schema_version": 1,
        "source": path.name,
        "compiled_test_count": manifest["compiled_test_count"],
        "translated_test_count": manifest["translated_test_count"],
        "unresolved_test_count": manifest["unresolved_test_count"],
        "translation_coverage_percent": round(
            100.0 * manifest["translated_test_count"] / manifest["compiled_test_count"], 2
        ) if manifest["compiled_test_count"] else 100.0,
        "by_reason": dict(sorted(by_reason.items())),
        "by_primitive_family": dict(sorted(by_family.items())),
        "by_rule": dict(sorted(by_rule.items())),
        "entries": entries,
    }


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
        f"coverage={report['translation_coverage_percent']:.2f}%"
    )
    print("by primitive family:")
    for name, count in sorted(report["by_primitive_family"].items(), key=lambda item: (-item[1], item[0])):
        print(f"  {count:4d}  {name}")
    print("by reason:")
    for name, count in sorted(report["by_reason"].items(), key=lambda item: (-item[1], item[0])):
        print(f"  {count:4d}  {name}")
    if args.json:
        print(args.json)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
