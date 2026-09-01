#!/usr/bin/env python3
"""Generate CLASH_recovered.clp with conservative compiled-test translation."""
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from clash_dat_message_handlers import recover_message_handlers, render_message_handlers
from clash_dat_object_constraints import translate_condition_tests
from clash_dat_lhs import recover_rule_lhs
from clash_dat_rete import rete_report
from clash_dat_slot_facets import render_recovered_classes
from decompile_clash_dat import parse_bsave, render_clips
from generate_clash_recovered_clp import (
    GAME_CLASS_NAMES,
    _extract_rhs_blocks,
    _fact_pattern,
    _object_pattern,
    _unique_rule_names,
)


def _unwrap_not(form: str) -> str:
    prefix = "(not "
    if not form.startswith(prefix) or not form.endswith(")"):
        raise ValueError(f"expected normalized not CE, got {form!r}")
    return form[len(prefix) : -1]


def _render_condition(
    condition: dict,
    all_conditions: list[dict],
    class_report: dict,
    object_nodes: list[dict],
) -> tuple[list[str], dict]:
    if condition["kind"] == "fact":
        form, binding = _fact_pattern(condition)
    else:
        form, binding = _object_pattern(condition)

    translated = translate_condition_tests(condition, all_conditions, class_report, object_nodes)
    resolved = [item.translated for item in translated if item.translated is not None]
    unresolved = [item for item in translated if item.translated is None]

    classes = list(condition.get("classes") or [])
    class_test = None
    if condition["kind"] == "object" and len(classes) > 1:
        class_var = binding["class_variable"]
        class_test = "(or " + " ".join(f"(eq {class_var} {name})" for name in classes) + ")"
        resolved.insert(0, class_test)

    if not resolved:
        lines = [form]
    elif condition["negated"]:
        inner = _unwrap_not(form)
        lines = ["(not (and", "  " + inner]
        lines.extend("  (test " + expr + ")" for expr in resolved)
        lines.append("))")
    else:
        lines = ["(and", "  " + form]
        lines.extend("  (test " + expr + ")" for expr in resolved)
        lines.append(")")

    for item in unresolved:
        reason = item.reason or "unresolved"
        lines.append(f";;; unresolved compiled-test ({reason}): {item.source}")

    detail = {
        "condition": condition["order"],
        "binding": binding,
        "compiled_test_count": len(translated),
        "translated_test_count": sum(item.resolved for item in translated),
        "unresolved_test_count": len(unresolved),
        "class_bitmap_test_emitted": class_test is not None,
        "translations": [
            {
                "source": item.source,
                "translated": item.translated,
                "reason": item.reason,
            }
            for item in translated
        ],
    }
    return lines, detail


def _render_rule(
    rule: dict,
    output_name: str,
    rhs_actions: list[str],
    class_report: dict,
    object_nodes: list[dict],
) -> tuple[str, dict]:
    lines = [f"(defrule {output_name}"]
    if output_name != rule["name"]:
        lines.append(f"  ;;; original BSAVE rule/disjunct name: {rule['name']}")
    lines.append(f"  (declare (salience {rule['salience']}))")
    if rule["dynamic_salience_expr"] != -1:
        lines.append(f"  ;;; dynamic-salience expression root: {rule['dynamic_salience_expr']}")
    lines.append(f"  ;;; terminal RETE join: J{rule['last_join']}")

    condition_manifest = []
    for condition in rule["conditions"]:
        condition_lines, detail = _render_condition(
            condition, rule["conditions"], class_report, object_nodes
        )
        lines.extend("  " + line for line in condition_lines)
        condition_manifest.append(detail)

    lines.append("  =>")
    if rhs_actions:
        lines.extend("  " + action for action in rhs_actions)
    else:
        lines.append("  ;;; no RHS actions")
    lines.append(")")

    return "\n".join(lines), {
        "record_index": rule["index"],
        "original_name": rule["name"],
        "output_name": output_name,
        "terminal_join": rule["last_join"],
        "condition_count": len(rule["conditions"]),
        "conditions": condition_manifest,
        "compiled_test_count": sum(item["compiled_test_count"] for item in condition_manifest),
        "translated_test_count": sum(item["translated_test_count"] for item in condition_manifest),
        "unresolved_test_count": sum(item["unresolved_test_count"] for item in condition_manifest),
        "class_bitmap_tests_emitted": sum(item["class_bitmap_test_emitted"] for item in condition_manifest),
        "actions_expr": rule["actions_expr"],
        "rhs_action_count": len(rhs_actions),
    }


def render_recovered_program(path: Path, ir: dict) -> tuple[str, dict]:
    lhs = recover_rule_lhs(path, ir)
    rete = rete_report(path, ir)
    object_nodes = rete["object_patterns"]
    class_report = lhs["class_report"]
    class_source, slot_report = render_recovered_classes(ir, class_report, GAME_CLASS_NAMES)
    handler_report = recover_message_handlers(path, ir)
    handler_source = render_message_handlers(handler_report, ir).rstrip()
    rhs_blocks = _extract_rhs_blocks(ir)
    output_names = _unique_rule_names(lhs["rules"])

    base = render_clips(ir)
    prefix = base.split(";;; DEFRULES", 1)[0].rstrip()
    if ";;; DEFFUNCTIONS" in prefix:
        before, after = prefix.split(";;; DEFFUNCTIONS", 1)
        prefix = before.rstrip() + "\n\n" + class_source + "\n\n;;; DEFFUNCTIONS" + after
    else:
        prefix += "\n\n" + class_source

    rule_sources = []
    rule_manifest = []
    for rule, output_name, rhs in zip(lhs["rules"], output_names, rhs_blocks):
        source, manifest = _render_rule(rule, output_name, rhs, class_report, object_nodes)
        rule_sources.append(source)
        rule_manifest.append(manifest)

    translated = sum(item["translated_test_count"] for item in rule_manifest)
    unresolved = sum(item["unresolved_test_count"] for item in rule_manifest)
    compiled = sum(item["compiled_test_count"] for item in rule_manifest)
    class_tests = sum(item["class_bitmap_tests_emitted"] for item in rule_manifest)
    object_join_translations = sum(
        1
        for rule in rule_manifest
        for condition in rule["conditions"]
        for item in condition["translations"]
        if item["translated"] is not None and item["source"].startswith("object-join-compare(")
    )
    object_constant_translations = sum(
        1
        for rule in rule_manifest
        for condition in rule["conditions"]
        for item in condition["translations"]
        if item["translated"] is not None and item["source"].startswith("object-pn-constant(")
    )

    header = "\n".join([
        ";;; CLASH_recovered.clp",
        ";;; Unified normalized source reconstructed from retail CLASH.DAT (CLIPS 6.00 BSAVE).",
        ";;; RETE alpha/join tests are emitted as real (test ...) CEs when accessors map unambiguously.",
        ";;; Object JN comparisons use recovered global slot-name ids; object PN constants use pattern-node slot context.",
        ";;; Defclass slot form/facets/default values are restored from compact BSAVE slot descriptors.",
        ";;; Defmessage-handler class/name/type/arity/actions are recovered from 28-byte BSAVE handler records.",
        ";;; Direct handler slot primitives are restored as ?self:<slot> and (bind ?self:<slot> ...).",
        ";;; Unresolved compiled primitives remain evidence comments; no guessed matcher constraint is emitted.",
        ";;; Synthetic ?fN/?oN and handler ?pN variables are stable generator names, not recovered original spelling.",
        f";;; slots={slot_report['slot_count']} multislots={slot_report['multislot_count']} dynamic-defaults={slot_report['dynamic_default_count']} no-defaults={slot_report['no_default_count']} constraints={slot_report['constraint_count']}",
        f";;; compiled-tests={compiled} translated={translated} unresolved={unresolved} class-bitmap-tests={class_tests}",
        f";;; object-join-tests={object_join_translations} object-constant-tests={object_constant_translations}",
        f";;; message-handlers={handler_report['count']} system={handler_report['system_count']} user={handler_report['user_count']} variadic={handler_report['variadic_count']}",
        "",
    ])
    program = (
        header
        + prefix
        + "\n\n"
        + handler_source
        + "\n\n;;; DEFRULES — recovered constraints + RHS\n\n"
        + "\n\n".join(rule_sources)
        + "\n"
    )

    duplicate_source_names = {
        name: count for name, count in Counter(r["name"] for r in lhs["rules"]).items() if count > 1
    }
    manifest = {
        "source": path.name,
        "version": ir["version"],
        "rules": len(rule_manifest),
        "conditions": lhs["condition_occurrence_count"],
        "defglobals": len(ir["globals"]),
        "deffunctions": len(ir["deffunctions"]),
        "defclass_slots": slot_report["slot_count"],
        "defclass_slot_facets": slot_report,
        "defmessage_handlers": handler_report["count"],
        "system_message_handlers": handler_report["system_count"],
        "user_message_handlers": handler_report["user_count"],
        "variadic_message_handlers": handler_report["variadic_count"],
        "message_handler_type_counts": handler_report["type_counts"],
        "message_handler_class_counts": handler_report["class_counts"],
        "message_handlers_manifest": handler_report["handlers"],
        "game_defclasses_emitted": [
            name for name in GAME_CLASS_NAMES
            if name in {c["name"] for c in class_report["classes"]}
        ],
        "duplicate_bsave_rule_names": duplicate_source_names,
        "synthetic_rule_renames": {
            item["output_name"]: item["original_name"]
            for item in rule_manifest if item["output_name"] != item["original_name"]
        },
        "compiled_test_count": compiled,
        "translated_test_count": translated,
        "unresolved_test_count": unresolved,
        "class_bitmap_tests_emitted": class_tests,
        "object_join_translated_count": object_join_translations,
        "object_constant_translated_count": object_constant_translations,
        "rules_manifest": rule_manifest,
        "recompilation_status": "slot facets/defaults, message handlers and named object comparisons restored; unsaved slot constraints and remaining matcher primitives stay explicit",
    }
    return program, manifest


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate CLASH_recovered.clp with restored matcher constraints")
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
        f"slots={manifest['defclass_slots']} handlers={manifest['defmessage_handlers']} "
        f"compiled-tests={manifest['compiled_test_count']} translated={manifest['translated_test_count']} "
        f"unresolved={manifest['unresolved_test_count']} object-joins={manifest['object_join_translated_count']} "
        f"object-constants={manifest['object_constant_translated_count']}"
    )
    print(args.manifest)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
