#!/usr/bin/env python3
"""Object-specific source recovery layered on clash_dat_constraints.

OBJ_JN_CMP1 carries global CLIPS slot-name ids directly. OBJ_PN_CONSTANT gets
its current slot from the object pattern node containing the network test. This
module supplies that missing context without guessing original variable names.
"""
from __future__ import annotations

from dataclasses import dataclass
import re

from clash_dat_constraints import ConstraintTranslation, _comparison, _replace_accessors, translate_test

_OBJ_JOIN_CMP = re.compile(
    r"^object-join-compare\(p(\d+)\.slot\[(\d+)\],p(\d+)\.slot\[(\d+)\],pass=(\d+),fail=(\d+)\)$"
)
_OBJ_PN_CONST = re.compile(
    r"^object-pn-constant\(offset=(\d+),from_beginning=(\d+),general=(\d+),pass=(\d+),fail=(\d+),value=<arg>\)(?: args=\((.*)\))?$"
)


@dataclass(frozen=True)
class ObjectAlphaTestContext:
    expression_index: int
    pattern_node: int
    slot_name_id: int
    slot_name: str
    multifield_node: bool
    which_field: int
    leave_fields: int


def object_alpha_test_contexts(condition: dict, object_nodes: list[dict], class_report: dict) -> list[ObjectAlphaTestContext]:
    """Return object pattern-node context in the same order as condition alpha_tests."""
    if condition["kind"] != "object" or condition["pattern_node"] == -1:
        return []
    by_index = {item["index"]: item for item in object_nodes}
    current = int(condition["pattern_node"])
    reverse: list[ObjectAlphaTestContext] = []
    seen: set[int] = set()
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in object alpha last-level chain at {current}")
        node = by_index.get(current)
        if node is None:
            raise ValueError(f"object alpha chain points outside pattern array: {current}")
        seen.add(current)
        expr_index = int(node["network_test"])
        if expr_index != -1:
            slot_id = int(node["slot_name_id"])
            reverse.append(
                ObjectAlphaTestContext(
                    expression_index=expr_index,
                    pattern_node=current,
                    slot_name_id=slot_id,
                    slot_name=class_report["slot_name_by_id"].get(slot_id, f"system-slot#{slot_id}"),
                    multifield_node=bool(node["multifield_node"]),
                    which_field=int(node["which_field"]),
                    leave_fields=int(node["leave_fields"]),
                )
            )
        current = int(node["last_level"])
    return list(reversed(reverse))


def _condition_map(conditions: list[dict]) -> dict[int, dict]:
    return {int(item["order"]): item for item in conditions}


def _object_binding(raw_pattern: int, slot_name: str, current_order: int, conditions: list[dict]) -> int | None:
    """Resolve zero/one based compiled object pattern ids by unique evidence.

    A negated object CE can be referenced only while translating its own join test;
    variables from earlier negated CEs are out of scope and are rejected.
    """
    by_order = _condition_map(conditions)
    candidates = []
    for order in (raw_pattern, raw_pattern + 1):
        item = by_order.get(order)
        if item is None or item["kind"] != "object":
            continue
        if item["negated"] and order != current_order:
            continue
        tested = set(item.get("tested_slots") or ())
        if tested and slot_name not in tested:
            continue
        candidates.append(order)
    unique = sorted(set(candidates))
    return unique[0] if len(unique) == 1 else None


def translate_object_test(
    source: str,
    current_order: int,
    conditions: list[dict],
    class_report: dict,
    alpha_context: ObjectAlphaTestContext | None = None,
) -> ConstraintTranslation:
    source = source.strip()

    match = _OBJ_JOIN_CMP.match(source)
    if match:
        p1, slot1_id, p2, slot2_id, passed, failed = map(int, match.groups())
        op = _comparison(passed, failed)
        if op is None:
            return ConstraintTranslation(source, None, "object compare pass/fail mode unresolved")
        slot1 = class_report["slot_name_by_id"].get(slot1_id)
        slot2 = class_report["slot_name_by_id"].get(slot2_id)
        if slot1 is None or slot2 is None:
            return ConstraintTranslation(source, None, f"object compare uses system/unknown slot ids ({slot1_id},{slot2_id})")
        order1 = _object_binding(p1, slot1, current_order, conditions)
        order2 = _object_binding(p2, slot2, current_order, conditions)
        if order1 is None or order2 is None:
            return ConstraintTranslation(source, None, "object compare pattern mapping ambiguous")
        return ConstraintTranslation(source, f"({op} ?o{order1}_{slot1} ?o{order2}_{slot2})", None)

    match = _OBJ_PN_CONST.match(source)
    if match:
        offset, from_beginning, general, passed, failed = map(int, match.groups()[:5])
        argument = (match.group(6) or "").strip()
        op = _comparison(passed, failed)
        if op is None:
            return ConstraintTranslation(source, None, "object constant pass/fail mode unresolved")
        if alpha_context is None:
            return ConstraintTranslation(source, None, "object constant lacks pattern-node slot context")
        if alpha_context.slot_name.startswith("system-slot#"):
            return ConstraintTranslation(source, None, "object constant targets a system slot")
        if general:
            return ConstraintTranslation(source, None, "general object constant comparison requires full multifield expression recovery")
        if alpha_context.multifield_node:
            return ConstraintTranslation(source, None, "object constant is inside a multifield slot")
        if offset != 0 or not from_beginning:
            return ConstraintTranslation(source, None, "object constant uses non-trivial slot offset")
        current = _condition_map(conditions).get(current_order)
        if current is None or current["kind"] != "object":
            return ConstraintTranslation(source, None, "object constant attached to non-object condition")
        if alpha_context.slot_name not in set(current.get("tested_slots") or ()):
            return ConstraintTranslation(source, None, "object constant slot is not exposed by alpha slot bitmap")
        if not argument:
            return ConstraintTranslation(source, None, "object constant argument missing")
        replaced, reason = _replace_accessors(argument, current_order, conditions)
        if replaced is None:
            return ConstraintTranslation(source, None, reason)
        return ConstraintTranslation(source, f"({op} ?o{current_order}_{alpha_context.slot_name} {replaced})", None)

    return translate_test(source, current_order, conditions)


def translate_condition_tests(
    condition: dict,
    conditions: list[dict],
    class_report: dict,
    object_nodes: list[dict],
) -> list[ConstraintTranslation]:
    contexts = object_alpha_test_contexts(condition, object_nodes, class_report)
    if contexts and len(contexts) != len(condition["alpha_tests"]):
        raise ValueError(
            f"condition {condition['order']} alpha context count {len(contexts)} != tests {len(condition['alpha_tests'])}"
        )
    result = []
    for index, source in enumerate(condition["alpha_tests"]):
        context = contexts[index] if contexts else None
        result.append(translate_object_test(source, int(condition["order"]), conditions, class_report, context))
    if condition["join_test"] is not None:
        result.append(
            translate_object_test(condition["join_test"], int(condition["order"]), conditions, class_report, None)
        )
    return result
