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
from clash_dat_message_handlers import render_handler

_PROC_PARAM = re.compile(r"(?<![$A-Za-z0-9_])\?p(\d+)\b")
_PROC_WILD_PARAM = re.compile(r"\$\?p(\d+)\b")
_SCALAR_HEAD = re.compile(r"^\((?:=|<>|neq|eq|>|<|>=|<=|\+|-|\*|/|integer|abs|min|max)\b")


def source_fact_pattern(condition: dict) -> tuple[str, dict]:
    order = int(condition["order"])
    template = condition["pattern"].split("(", 1)[1].split(None, 1)[0]
    fact_var = f"?f{order}"

    # initial-fact is the sole explicit deftemplate in this image and has no
    # slots. The other strategic relations are implied ordered facts.
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
    """Reject translations which are readable evidence but not legal CLIPS expressions.

    Standalone fact-slot-length primitives have a dedicated translator. When the
    semantic debug spelling survives inside a larger FCALL tree, the original
    source expression is still unknown and must remain an evidence comment.
    Similarly a recovered multifield slice cannot be fed to a scalar arithmetic
    or comparison function without knowing whether the original accessor selected
    a field or a multifield value.
    """
    result: list[ConstraintTranslation] = []
    for item in items:
        translated = item.translated
        if translated is None:
            result.append(item)
            continue
        if "fact-slot-length" in translated or "slot=" in translated:
            result.append(
                ConstraintTranslation(item.source, None, "nested compiled fact-slot-length has no safe source form")
            )
            continue
        if "(subseq$ " in translated and _SCALAR_HEAD.match(translated):
            result.append(
                ConstraintTranslation(item.source, None, "multifield accessor is used by a scalar expression")
            )
            continue
        result.append(item)
    return result


def _shift_handler_proc_params(source: str) -> str:
    """Map compiled handler procedure indices to explicit source parameters.

    Handler procedure index 1 is the implicit `?self`; explicit source
    parameters therefore start at compiled index 2. This differs from
    deffunction procedure indexing, where index 1 is the first explicit arg.
    """
    lines = source.splitlines()
    if not lines:
        return source

    # Do not rewrite the synthetic declaration line itself; its ?p1..?pN list
    # is already source-level and excludes implicit ?self.
    body = "\n".join(lines[1:])

    def wild(match: re.Match[str]) -> str:
        index = int(match.group(1))
        if index <= 1:
            return "$?self"
        return f"$?p{index - 1}"

    def scalar(match: re.Match[str]) -> str:
        index = int(match.group(1))
        if index == 1:
            return "?self"
        if index > 1:
            return f"?p{index - 1}"
        return match.group(0)

    body = _PROC_WILD_PARAM.sub(wild, body)
    body = _PROC_PARAM.sub(scalar, body)
    return lines[0] + ("\n" + body if body else "")


def render_source_message_handlers(report: dict, ir: dict) -> str:
    """Render only user-authored handlers as legal CLIPS source.

    System handlers are preserved in the BSAVE report but omitted from textual
    source. CLIPS creates built-in handlers and slot accessor handlers itself.
    """
    user_handlers = [item for item in report["handlers"] if not item["system"]]
    header = [
        ";;; DEFMESSAGE-HANDLERS",
        ";;; User handlers are emitted; system/implicit handlers remain binary evidence only.",
        f";;; bsave-handlers={report['count']} system-omitted={report['system_count']} user-emitted={len(user_handlers)}",
        "",
    ]
    rendered = []
    for item in user_handlers:
        source = render_handler(item, ir, report["class_report"])
        rendered.append(_shift_handler_proc_params(source))
    return "\n\n".join(["\n".join(header)] + rendered) + "\n"
