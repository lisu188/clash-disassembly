#!/usr/bin/env python3
"""Generate one normalized source-like CLIPS program from retail CLASH.DAT.

The generator deliberately separates exact recovered structure from synthetic source
choices.  RETE ordering, negation, rule metadata, RHS expression trees, globals,
deﬀunction bodies, class/slot names, and primitive accessor semantics come from the
binary image.  Pattern-variable spellings and the compact pattern syntax are stable,
synthetic names because CLIPS BSAVE does not preserve the original source text.
"""
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from clash_dat_classes import parse_defclass
from clash_dat_lhs import recover_rule_lhs
from decompile_clash_dat import parse_bsave, render_clips

GAME_CLASS_NAMES = {
    "clash-class",
    "gracz",
    "budowla",
    "straznica",
    "twierdza",
    "zamek",
    "oddzial",
}


def _direct_superclasses(cls: dict, class_report: dict) -> list[str]:
    count = cls["direct_superclass_count"]
    start = cls["superclass_list_index"]
    if count == 0 or start == -1:
        return []
    links = class_report["class_links"]
    classes = class_report["classes"]
    result = []
    for class_index in links[start : start + count]:
        if 0 <= class_index < len(classes):
            result.append(classes[class_index]["name"])
        else:
            result.append(f"class#{class_index}")
    return result


def _render_recovered_classes(class_report: dict) -> str:
    lines = [
        ";;; DEFCLASSES",
        ";;; Game class names, inheritance and declared slot names are recovered from BSAVE.",
        ";;; Slot cardinality/default/constraint syntax is intentionally normalized to `(slot ...)`",
        ";;; until those source-level declarations are reconstructed exactly.",
    ]
    classes = {item["name"]: item for item in class_report["classes"]}
    for name in sorted(GAME_CLASS_NAMES, key=lambda n: classes[n]["index"] if n in classes else 10_000):
        if name not in classes:
            continue
        cls = classes[name]
        supers = _direct_superclasses(cls, class_report) or ["USER"]
        lines.append(f"(defclass {name}")
        lines.append("  (is-a " + " ".join(supers) + ")")
        for slot_name in class_report["declared_slots"].get(name, []):
            lines.append(f"  (slot {slot_name})")
        lines.append(")")
        lines.append("")
    return "\n".join(lines).rstrip()


def _extract_rhs_blocks(ir: dict) -> list[list[str]]:
    """Reuse the established RHS decompiler and extract rule action lines in record order."""
    rendered = render_clips(ir)
    marker = ";;; DEFRULES"
    if marker not in rendered:
        raise ValueError("decompiler output has no DEFRULES marker")
    tail = rendered.split(marker, 1)[1]
    lines = tail.splitlines()
    blocks: list[list[str]] = []
    i = 0
    while i < len(lines):
        if not lines[i].startswith("(defrule "):
            i += 1
            continue
        while i < len(lines) and lines[i].strip() != "=>":
            i += 1
        if i >= len(lines):
            raise ValueError("unterminated defrule before =>")
        i += 1
        actions = []
        while i < len(lines) and lines[i] != ")":
            if lines[i].strip():
                actions.append(lines[i].strip())
            i += 1
        if i >= len(lines):
            raise ValueError("unterminated defrule action block")
        blocks.append(actions)
        i += 1
    if len(blocks) != len(ir["rules"]):
        raise ValueError(f"RHS block count {len(blocks)} != rule count {len(ir['rules'])}")
    return blocks


def _unique_rule_names(rules: list[dict]) -> list[str]:
    totals = Counter(item["name"] for item in rules)
    seen: Counter[str] = Counter()
    result = []
    for item in rules:
        name = item["name"]
        seen[name] += 1
        if totals[name] == 1 or seen[name] == 1:
            result.append(name)
        else:
            result.append(f"{name}__disjunct{seen[name]}")
    return result


def _fact_pattern(condition: dict) -> tuple[str, dict]:
    order = condition["order"]
    template = condition["pattern"].split("(", 1)[1].split(None, 1)[0]
    fact_var = f"?f{order}"
    fields_var = f"$?f{order}_fields"
    inner = f"({template} {fields_var})"
    if condition["negated"]:
        form = f"(not {inner})"
        binding = {
            "condition": order,
            "kind": "fact",
            "fact_address": None,
            "fields": fields_var,
            "template": template,
            "negated": True,
        }
    else:
        form = f"{fact_var} <- {inner}"
        binding = {
            "condition": order,
            "kind": "fact",
            "fact_address": fact_var,
            "fields": fields_var,
            "template": template,
            "negated": False,
        }
    return form, binding


def _object_pattern(condition: dict) -> tuple[str, dict]:
    order = condition["order"]
    object_var = f"?o{order}"
    classes = list(condition.get("classes") or [])
    tested_slots = list(condition.get("tested_slots") or [])
    slot_bindings = {slot: f"?o{order}_{slot}" for slot in tested_slots}

    pieces = ["(object"]
    if len(classes) == 1:
        pieces.append(f" (is-a {classes[0]})")
    elif classes:
        pieces.append(f" (is-a ?o{order}_class)")
    for slot, variable in slot_bindings.items():
        pieces.append(f" ({slot} {variable})")
    pieces.append(")")
    inner = "".join(pieces)

    if condition["negated"]:
        form = f"(not {inner})"
        address = None
    else:
        form = f"{object_var} <- {inner}"
        address = object_var

    binding = {
        "condition": order,
        "kind": "object",
        "object_address": address,
        "classes": classes,
        "class_variable": f"?o{order}_class" if len(classes) > 1 else None,
        "slots": slot_bindings,
        "negated": bool(condition["negated"]),
    }
    return form, binding


def _render_rule(rule: dict, output_name: str, rhs_actions: list[str]) -> tuple[str, dict]:
    lines = [f"(defrule {output_name}"]
    if output_name != rule["name"]:
        lines.append(f"  ;;; original BSAVE rule/disjunct name: {rule['name']}")
    lines.append(f"  (declare (salience {rule['salience']}))")
    if rule["dynamic_salience_expr"] != -1:
        lines.append(f"  ;;; dynamic-salience expression root: {rule['dynamic_salience_expr']}")
    lines.append(f"  ;;; terminal RETE join: J{rule['last_join']}")

    bindings = []
    unresolved_test_count = 0
    for condition in rule["conditions"]:
        if condition["kind"] == "fact":
            form, binding = _fact_pattern(condition)
        else:
            form, binding = _object_pattern(condition)
        lines.append("  " + form)
        bindings.append(binding)

        classes = list(condition.get("classes") or [])
        if condition["kind"] == "object" and len(classes) > 1:
            lines.append("    ;;; allowed classes from alpha bitmap: " + ", ".join(classes))
        for alpha in condition["alpha_tests"]:
            unresolved_test_count += 1
            lines.append("    ;;; recovered alpha-test: " + alpha)
        if condition["join_test"] is not None:
            unresolved_test_count += 1
            lines.append("    ;;; recovered join-test: " + condition["join_test"])

    lines.append("  =>")
    if rhs_actions:
        for action in rhs_actions:
            lines.append("  " + action)
    else:
        lines.append("  ;;; no RHS actions")
    lines.append(")")

    manifest = {
        "record_index": rule["index"],
        "original_name": rule["name"],
        "output_name": output_name,
        "terminal_join": rule["last_join"],
        "condition_count": len(rule["conditions"]),
        "synthetic_bindings": bindings,
        "commented_compiled_test_count": unresolved_test_count,
        "actions_expr": rule["actions_expr"],
        "rhs_action_count": len(rhs_actions),
    }
    return "\n".join(lines), manifest


def render_recovered_program(path: Path, ir: dict) -> tuple[str, dict]:
    lhs = recover_rule_lhs(path, ir)
    rhs_blocks = _extract_rhs_blocks(ir)
    output_names = _unique_rule_names(lhs["rules"])

    base = render_clips(ir)
    prefix = base.split(";;; DEFRULES", 1)[0].rstrip()
    class_source = _render_recovered_classes(lhs["class_report"])
    # Place recovered classes before deffunctions so the generated file reads like source.
    if ";;; DEFFUNCTIONS" in prefix:
        before, after = prefix.split(";;; DEFFUNCTIONS", 1)
        prefix = before.rstrip() + "\n\n" + class_source + "\n\n;;; DEFFUNCTIONS" + after
    else:
        prefix += "\n\n" + class_source

    rule_sources = []
    rule_manifest = []
    for rule, output_name, rhs in zip(lhs["rules"], output_names, rhs_blocks):
        source, manifest = _render_rule(rule, output_name, rhs)
        rule_sources.append(source)
        rule_manifest.append(manifest)

    header = "\n".join(
        [
            ";;; CLASH_recovered.clp",
            ";;; Unified normalized source reconstructed from retail CLASH.DAT (CLIPS 6.00 BSAVE).",
            ";;; Exact binary evidence is retained in the parser/RETE/class IR; this file is a readable source projection.",
            ";;; Synthetic ?fN/?oN variable names are stable generator names, not claims about original spelling.",
            ";;; Compiled alpha/join tests remain comments until every accessor can be translated back to source constraints.",
            ";;; Therefore this is a recompilation-oriented scaffold, not yet a semantic round-trip replacement for CLASH.DAT.",
            "",
        ]
    )
    program = header + prefix + "\n\n;;; DEFRULES — unified recovered LHS + RHS\n\n" + "\n\n".join(rule_sources) + "\n"

    duplicate_source_names = {name: count for name, count in Counter(r["name"] for r in lhs["rules"]).items() if count > 1}
    manifest = {
        "source": path.name,
        "version": ir["version"],
        "rules": len(rule_manifest),
        "conditions": lhs["condition_occurrence_count"],
        "defglobals": len(ir["globals"]),
        "deffunctions": len(ir["deffunctions"]),
        "game_defclasses_emitted": [name for name in GAME_CLASS_NAMES if name in {c["name"] for c in lhs["class_report"]["classes"]}],
        "duplicate_bsave_rule_names": duplicate_source_names,
        "synthetic_rule_renames": {
            item["output_name"]: item["original_name"]
            for item in rule_manifest
            if item["output_name"] != item["original_name"]
        },
        "commented_compiled_test_count": sum(item["commented_compiled_test_count"] for item in rule_manifest),
        "rules_manifest": rule_manifest,
        "recompilation_status": "source scaffold; compiled tests still represented as evidence comments",
    }
    return program, manifest


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate unified source-like CLASH_recovered.clp from CLASH.DAT")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clp", default="CLASH_recovered.clp")
    parser.add_argument("--manifest", default="CLASH_recovered_manifest.json")
    args = parser.parse_args()

    source = Path(args.input)
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    Path(args.clp).write_text(program, encoding="utf-8")
    Path(args.manifest).write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
    print(
        f"generated {args.clp}: rules={manifest['rules']} conditions={manifest['conditions']} "
        f"compiled-tests-commented={manifest['commented_compiled_test_count']}"
    )
    print(args.manifest)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
