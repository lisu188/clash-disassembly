#!/usr/bin/env python3
"""CLIPS-source compatibility layer for normalized CLASH.DAT recovery.

The binary evidence model deliberately keeps system matcher slots and system
message handlers. A textual CLIPS source file must not emit those objects
literally: CLIPS recreates them from class declarations. This module converts
that exact binary evidence into legal source-level forms without changing the
underlying recovery report.
"""
from __future__ import annotations

import re

from clash_dat_constraints import ConstraintTranslation
from clash_dat_handler_slots import decode_handler_reference
from clash_dat_primitives import decode_primitive
from clash_dat_source_expr import SourceExpressionRenderer
from decompile_clash_dat import bitmap_int

_SCALAR_HEAD = re.compile(r"^\((?:=|<>|neq|eq|>|<|>=|<=|\+|-|\*|/|integer|abs|min|max)\b")


def source_fact_pattern(condition: dict) -> tuple[str, dict]:
    order = int(condition["order"])
    template = condition["pattern"].split("(", 1)[1].split(None, 1)[0]
    fact_var = f"?f{order}"
    if template == "initial-fact":
        inner = "(initial-fact)"
        fields_var = None
    else:
        fields_var = f"$?f{order}_fields"
        inner = f"({template} {fields_var})"
    if condition["negated"]:
        form = f"(not {inner})"
        address = None
    else:
        form = f"{fact_var} <- {inner}"
        address = fact_var
    return form, {
        "condition": order,
        "kind": "fact",
        "fact_address": address,
        "fields": fields_var,
        "template": template,
        "negated": bool(condition["negated"]),
    }


def source_object_pattern(condition: dict) -> tuple[str, dict]:
    order = int(condition["order"])
    object_var = f"?o{order}"
    classes = list(condition.get("classes") or [])
    evidence_slots = list(condition.get("tested_slots") or [])
    source_slots = [name for name in evidence_slots if not name.startswith("system-slot#")]
    slot_bindings = {slot: f"?o{order}_{slot}" for slot in source_slots}
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
    return form, {
        "condition": order,
        "kind": "object",
        "object_address": address,
        "classes": classes,
        "class_variable": f"?o{order}_class" if len(classes) > 1 else None,
        "slots": slot_bindings,
        "system_slots_omitted": [name for name in evidence_slots if name.startswith("system-slot#")],
        "negated": bool(condition["negated"]),
    }


def legalize_constraint_translations(items: list[ConstraintTranslation]) -> list[ConstraintTranslation]:
    result: list[ConstraintTranslation] = []
    for item in items:
        translated = item.translated
        if translated is None:
            result.append(item)
            continue
        if "fact-slot-length" in translated or "slot=" in translated:
            result.append(ConstraintTranslation(item.source, None, "nested compiled fact-slot-length has no safe source form"))
            continue
        if "(subseq$ " in translated and _SCALAR_HEAD.match(translated):
            result.append(ConstraintTranslation(item.source, None, "multifield accessor is used by a scalar expression"))
            continue
        result.append(item)
    return result


def _handler_params(handler: dict) -> list[str]:
    explicit_count = max(0, int(handler["min_params"]) - 1)
    result = [f"?p{i}" for i in range(1, explicit_count + 1)]
    if int(handler["max_params"]) == -1:
        result.append(f"$?p{explicit_count + 1}")
    return result


def _handler_resolver(ir: dict, class_report: dict):
    def resolve(index: int, type_id: int, value: int, args: list[int], renderer: SourceExpressionRenderer) -> str | None:
        if type_id == 57:
            if 0 <= value < len(class_report["classes"]):
                return class_report["classes"][value]["name"]
            return None
        if type_id == 65:
            decoded = bitmap_int(ir["bitmaps"], value)
            if decoded in (0, 1):
                return "?self"
            if decoded is not None and decoded > 1:
                return f"?p{decoded - 1}"
        if type_id == 66:
            decoded = bitmap_int(ir["bitmaps"], value)
            if decoded is not None and decoded > 1:
                return f"$?p{decoded - 1}"
        if type_id in (58, 59):
            ref = decode_handler_reference(index, ir["expressions"][index], ir, class_report)
            if ref is None:
                return None
            if type_id == 58:
                return ref.clips_target
            return "(bind " + " ".join([ref.clips_target] + [renderer.node(item) for item in args]) + ")"
        return None
    return resolve


def render_source_message_handlers(report: dict, ir: dict) -> str:
    user_handlers = [item for item in report["handlers"] if not item["system"]]
    header = [
        ";;; DEFMESSAGE-HANDLERS",
        ";;; User handlers are emitted; system/implicit handlers remain binary evidence only.",
        f";;; bsave-handlers={report['count']} system-omitted={report['system_count']} user-emitted={len(user_handlers)}",
        "",
    ]
    renderer = SourceExpressionRenderer(ir, _handler_resolver(ir, report["class_report"]))
    rendered: list[str] = []
    for item in user_handlers:
        params = " ".join(_handler_params(item))
        lines = [f"(defmessage-handler {item['class_name']} {item['name']} {item['handler_type']} ({params})"]
        lines.append(
            f"  ;;; bsave handler#{item['index']} actions={item['actions_expr']} "
            f"locals={item['local_var_count']} dispatch-order={item['dispatch_order']}"
        )
        actions = renderer.action_list(int(item["actions_expr"]))
        if actions:
            lines.extend("  " + action for action in actions)
        else:
            lines.append("  ;;; no action expression")
        lines.append(")")
        rendered.append("\n".join(lines))
    return "\n\n".join(["\n".join(header)] + rendered) + "\n"


def _condition_map(conditions: list[dict]) -> dict[int, dict]:
    return {int(item["order"]): item for item in conditions}


def _positive_object_order(raw_pattern: int, slot_name: str | None, conditions: list[dict]) -> int | None:
    by_order = _condition_map(conditions)
    candidates: list[int] = []
    for order in (raw_pattern, raw_pattern + 1):
        condition = by_order.get(order)
        if condition is None or condition["kind"] != "object" or condition["negated"]:
            continue
        if slot_name is not None:
            tested = set(condition.get("tested_slots") or ())
            if tested and slot_name not in tested:
                continue
        candidates.append(order)
    unique = sorted(set(candidates))
    return unique[0] if len(unique) == 1 else None


def _rule_rhs_resolver(ir: dict, conditions: list[dict], class_report: dict):
    by_order = _condition_map(conditions)

    def resolve(index: int, type_id: int, value: int, args: list[int], renderer: SourceExpressionRenderer) -> str | None:
        decoded = decode_primitive(ir["expressions"][index], ir, index)
        if decoded is None:
            return None
        fields = decoded.fields
        if type_id == 29:
            order = int(fields["source_pattern_ordinal"])
            condition = by_order.get(order)
            if condition is None or condition["kind"] != "fact" or condition["negated"]:
                return None
            if fields["fact_address"]:
                return f"?f{order}"
            if fields["all_fields"]:
                return f"$?f{order}_fields"
            if int(fields["which_slot"]) == 0:
                return f"(nth$ {int(fields['which_field']) + 1} $?f{order}_fields)"
            return None
        if type_id == 31:
            order = int(fields["source_pattern_ordinal"])
            condition = by_order.get(order)
            if condition is None or condition["kind"] != "fact" or condition["negated"] or int(fields["which_slot"]) != 0:
                return None
            seq = f"$?f{order}_fields"
            begin = int(fields["begin_offset"])
            end = int(fields["end_offset"])
            from_beginning = bool(fields["from_beginning"])
            from_end = bool(fields["from_end"])
            if from_beginning and from_end:
                return f"(subseq$ {seq} {begin + 1} (- (length$ {seq}) {end}))"
            if from_beginning:
                return f"(nth$ {begin + 1} {seq})"
            if from_end:
                return f"(nth$ (- (length$ {seq}) {end}) {seq})"
            return None
        if type_id == 47:
            slot_id = int(fields["which_slot"])
            slot_name = class_report["slot_name_by_id"].get(slot_id)
            raw_pattern = int(fields["which_pattern"])
            order = _positive_object_order(raw_pattern, None if fields["object_address"] else slot_name, conditions)
            if order is None:
                return None
            if fields["object_address"]:
                return f"?o{order}"
            if slot_name is None or slot_name.startswith("system-slot#"):
                return None
            base = f"?o{order}_{slot_name}"
            if fields["all_fields"]:
                return base
            field = int(fields["which_field"])
            return base if field == 0 else f"(nth$ {field + 1} {base})"
        return None

    return resolve


def render_rule_rhs(rule: dict, ir: dict, class_report: dict) -> list[str]:
    renderer = SourceExpressionRenderer(ir, _rule_rhs_resolver(ir, rule["conditions"], class_report))
    return renderer.action_list(int(rule["actions_expr"]))


def render_source_prelude(ir: dict, class_source: str) -> str:
    renderer = SourceExpressionRenderer(ir)
    lines = [";;; DEFGLOBALS", "(defglobal"]
    for item in ir["globals"]:
        lines.append(f"  ?*{item['name']}* = {renderer.node(int(item['initial_expr']))}")
    lines.extend([")", "", ";;; DEFTEMPLATES"])
    for item in ir["templates"]:
        lines.append(f";;; (deftemplate {item['name']})")
    lines.extend(["", class_source, "", ";;; DEFFUNCTIONS"])
    for item in ir["deffunctions"]:
        max_params = int(item["max_params"])
        min_params = int(item["min_params"])
        if max_params == -1:
            params = [f"?p{i}" for i in range(1, min_params + 1)] + [f"$?p{min_params + 1}"]
        else:
            params = [f"?p{i}" for i in range(1, max_params + 1)]
        lines.append(f"(deffunction {item['name']} ({' '.join(params)})")
        actions = renderer.action_list(int(item["code_expr"]))
        lines.extend("  " + action for action in actions)
        lines.extend([")", ""])
    return "\n".join(lines).rstrip()
