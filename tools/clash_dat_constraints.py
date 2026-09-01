#!/usr/bin/env python3
"""Conservative translation of recovered CLIPS matcher tests back to source CEs.

The input strings are produced by clash_dat_lhs.render_expression. Translation is
accepted only when every compiled accessor can be mapped to a synthetic binding in
one rule. Unknown/ambiguous primitives stay unresolved instead of being guessed.
"""
from __future__ import annotations

from dataclasses import dataclass
import re


@dataclass(frozen=True)
class ConstraintTranslation:
    source: str
    translated: str | None
    reason: str | None

    @property
    def resolved(self) -> bool:
        return self.translated is not None


_FACT_FIELD_END = re.compile(r"fact\[p(\d+)\]\.slot\[(\d+)\]\.field-from-end\[(\d+)\]")
_FACT_FIELD = re.compile(r"fact\[p(\d+)\]\.slot\[(\d+)\]\.field\[(\d+)\]")
_FACT_ALL = re.compile(r"fact\[p(\d+)\]\.slot\[(\d+)\](?!\.)")
_FACT_ADDR = re.compile(r"fact\[p(\d+)\](?!\.)")
_FACT_MULTI = re.compile(
    r"fact\[p(\d+)\]\.slot\[(\d+)\]\.multifield\(begin\+(\d+),end-(\d+)\)"
)
_CURRENT_FIELD_END = re.compile(r"current-fact\.slot\[(\d+)\]\.field-from-end\[(\d+)\]")
_CURRENT_FIELD = re.compile(r"current-fact\.slot\[(\d+)\]\.field\[(\d+)\]")
_CURRENT_MULTI = re.compile(
    r"current-fact\.slot\[(\d+)\]\.multifield\(begin\+(\d+),end-(\d+)\)"
)
_OBJECT_SLOT = re.compile(r"object\[p(\d+)\]\.([A-Za-z0-9_#-]+)(?:\[(\d+)\])?")
_OBJECT_ADDR = re.compile(r"object\[p(\d+)\](?!\.)")

_FACT_LENGTH = re.compile(r"^fact-slot-length\(slot=(\d+),(exact|minimum)=(\d+)\)$")
_FACT_CONST = re.compile(
    r"^fact-pn-constant\(slot=(\d+),(begin|end)\+(\d+) (==|!=) <arg>\) args=\((.*)\)$"
)
_FACT_JOIN_CMP = re.compile(
    r"^fact-join-compare\(slot1=(\d+),offset1=(\d+),pattern2=(\d+),slot2=(\d+),offset2=(\d+),pass=(\d+),fail=(\d+)\)$"
)
_OBJ_JOIN_CMP = re.compile(
    r"^object-join-compare\(p(\d+)\.slot\[(\d+)\],p(\d+)\.slot\[(\d+)\],pass=(\d+),fail=(\d+)\)$"
)


def _condition_map(conditions: list[dict]) -> dict[int, dict]:
    return {int(item["order"]): item for item in conditions}


def _fact_binding(order: int, conditions: list[dict]) -> dict | None:
    item = _condition_map(conditions).get(order)
    if item is None or item["kind"] != "fact" or item["negated"]:
        return None
    return item


def _object_binding(raw_pattern: int, slot: str | None, conditions: list[dict]) -> int | None:
    by_order = _condition_map(conditions)
    candidates = []
    for order in (raw_pattern, raw_pattern + 1):
        item = by_order.get(order)
        if item is None or item["kind"] != "object" or item["negated"]:
            continue
        if slot is not None:
            tested = set(item.get("tested_slots") or ())
            if tested and slot not in tested:
                continue
        candidates.append(order)
    unique = sorted(set(candidates))
    return unique[0] if len(unique) == 1 else None


def _fact_pattern_binding(raw_pattern: int, conditions: list[dict]) -> int | None:
    by_order = _condition_map(conditions)
    candidates = []
    for order in (raw_pattern, raw_pattern + 1):
        item = by_order.get(order)
        if item is not None and item["kind"] == "fact" and not item["negated"]:
            candidates.append(order)
    unique = sorted(set(candidates))
    return unique[0] if len(unique) == 1 else None


def _nth(fields: str, zero_based: int) -> str:
    return f"(nth$ {zero_based + 1} {fields})"


def _nth_from_end(fields: str, zero_based: int) -> str:
    return f"(nth$ (- (length$ {fields}) {zero_based}) {fields})"


def _slice(fields: str, begin_offset: int, end_offset: int) -> str:
    start = begin_offset + 1
    end = f"(- (length$ {fields}) {end_offset})"
    return f"(subseq$ {fields} {start} {end})"


def _comparison(pass_flag: int, fail_flag: int) -> str | None:
    if pass_flag == 1 and fail_flag == 0:
        return "eq"
    if pass_flag == 0 and fail_flag == 1:
        return "neq"
    return None


def _replace_accessors(text: str, current_order: int, conditions: list[dict]) -> tuple[str | None, str | None]:
    failure: str | None = None

    def fail(reason: str) -> None:
        nonlocal failure
        if failure is None:
            failure = reason

    def fact_multi(match: re.Match[str]) -> str:
        order, slot, begin, end = map(int, match.groups())
        if slot != 0 or _fact_binding(order, conditions) is None:
            fail(f"unresolved fact multifield accessor p{order}/slot{slot}")
            return match.group(0)
        return _slice(f"$?f{order}_fields", begin, end)

    text = _FACT_MULTI.sub(fact_multi, text)

    def current_multi(match: re.Match[str]) -> str:
        slot, begin, end = map(int, match.groups())
        current = _condition_map(conditions).get(current_order)
        if slot != 0 or current is None or current["kind"] != "fact":
            fail(f"unresolved current-fact multifield accessor slot{slot}")
            return match.group(0)
        return _slice(f"$?f{current_order}_fields", begin, end)

    text = _CURRENT_MULTI.sub(current_multi, text)

    def fact_field_end(match: re.Match[str]) -> str:
        order, slot, field = map(int, match.groups())
        if slot != 0 or _fact_binding(order, conditions) is None:
            fail(f"unresolved fact field-from-end accessor p{order}/slot{slot}")
            return match.group(0)
        return _nth_from_end(f"$?f{order}_fields", field)

    text = _FACT_FIELD_END.sub(fact_field_end, text)

    def fact_field(match: re.Match[str]) -> str:
        order, slot, field = map(int, match.groups())
        if slot != 0 or _fact_binding(order, conditions) is None:
            fail(f"unresolved fact field accessor p{order}/slot{slot}")
            return match.group(0)
        return _nth(f"$?f{order}_fields", field)

    text = _FACT_FIELD.sub(fact_field, text)

    def current_field_end(match: re.Match[str]) -> str:
        slot, field = map(int, match.groups())
        current = _condition_map(conditions).get(current_order)
        if slot != 0 or current is None or current["kind"] != "fact":
            fail(f"unresolved current-fact field-from-end accessor slot{slot}")
            return match.group(0)
        return _nth_from_end(f"$?f{current_order}_fields", field)

    text = _CURRENT_FIELD_END.sub(current_field_end, text)

    def current_field(match: re.Match[str]) -> str:
        slot, field = map(int, match.groups())
        current = _condition_map(conditions).get(current_order)
        if slot != 0 or current is None or current["kind"] != "fact":
            fail(f"unresolved current-fact field accessor slot{slot}")
            return match.group(0)
        return _nth(f"$?f{current_order}_fields", field)

    text = _CURRENT_FIELD.sub(current_field, text)

    def fact_all(match: re.Match[str]) -> str:
        order, slot = map(int, match.groups())
        if slot != 0 or _fact_binding(order, conditions) is None:
            fail(f"unresolved fact slot accessor p{order}/slot{slot}")
            return match.group(0)
        return f"$?f{order}_fields"

    text = _FACT_ALL.sub(fact_all, text)

    def fact_addr(match: re.Match[str]) -> str:
        order = int(match.group(1))
        if _fact_binding(order, conditions) is None:
            fail(f"unresolved fact address p{order}")
            return match.group(0)
        return f"?f{order}"

    text = _FACT_ADDR.sub(fact_addr, text)

    def object_slot(match: re.Match[str]) -> str:
        raw = int(match.group(1))
        slot = match.group(2)
        field = match.group(3)
        order = _object_binding(raw, slot, conditions)
        if order is None:
            fail(f"ambiguous object accessor p{raw}.{slot}")
            return match.group(0)
        base = f"?o{order}_{slot}"
        if field is not None:
            return _nth(base, int(field))
        return base

    text = _OBJECT_SLOT.sub(object_slot, text)

    def object_addr(match: re.Match[str]) -> str:
        raw = int(match.group(1))
        order = _object_binding(raw, None, conditions)
        if order is None:
            fail(f"ambiguous object address p{raw}")
            return match.group(0)
        return f"?o{order}"

    text = _OBJECT_ADDR.sub(object_addr, text)
    return (None, failure) if failure is not None else (text, None)


def translate_test(source: str, current_order: int, conditions: list[dict]) -> ConstraintTranslation:
    source = source.strip()

    length_match = _FACT_LENGTH.match(source)
    if length_match:
        slot = int(length_match.group(1))
        mode = length_match.group(2)
        length = int(length_match.group(3))
        current = _condition_map(conditions).get(current_order)
        if slot != 0 or current is None or current["kind"] != "fact":
            return ConstraintTranslation(source, None, "fact length test is not ordered slot 0")
        op = "=" if mode == "exact" else ">="
        return ConstraintTranslation(source, f"({op} (length$ $?f{current_order}_fields) {length})", None)

    const_match = _FACT_CONST.match(source)
    if const_match:
        slot = int(const_match.group(1))
        direction = const_match.group(2)
        offset = int(const_match.group(3))
        op = const_match.group(4)
        argument = const_match.group(5).strip()
        current = _condition_map(conditions).get(current_order)
        if slot != 0 or current is None or current["kind"] != "fact":
            return ConstraintTranslation(source, None, "fact constant test is not ordered slot 0")
        fields = f"$?f{current_order}_fields"
        lhs = _nth(fields, offset) if direction == "begin" else _nth_from_end(fields, offset)
        clips_op = "eq" if op == "==" else "neq"
        replaced_arg, reason = _replace_accessors(argument, current_order, conditions)
        if replaced_arg is None:
            return ConstraintTranslation(source, None, reason)
        return ConstraintTranslation(source, f"({clips_op} {lhs} {replaced_arg})", None)

    fact_cmp = _FACT_JOIN_CMP.match(source)
    if fact_cmp:
        slot1, offset1, pattern2, slot2, offset2, passed, failed = map(int, fact_cmp.groups())
        op = _comparison(passed, failed)
        previous = _fact_pattern_binding(pattern2, conditions)
        current = _condition_map(conditions).get(current_order)
        if op is None:
            return ConstraintTranslation(source, None, "fact compare pass/fail mode unresolved")
        if slot1 != 0 or slot2 != 0 or current is None or current["kind"] != "fact" or previous is None:
            return ConstraintTranslation(source, None, "fact compare pattern/slot mapping ambiguous")
        lhs = _nth(f"$?f{current_order}_fields", offset1)
        rhs = _nth(f"$?f{previous}_fields", offset2)
        return ConstraintTranslation(source, f"({op} {lhs} {rhs})", None)

    obj_cmp = _OBJ_JOIN_CMP.match(source)
    if obj_cmp:
        p1, slot1, p2, slot2, passed, failed = map(int, obj_cmp.groups())
        op = _comparison(passed, failed)
        if op is None:
            return ConstraintTranslation(source, None, "object compare pass/fail mode unresolved")
        return ConstraintTranslation(source, None, f"object compare needs slot-id mapping ({slot1},{slot2})")

    replaced, reason = _replace_accessors(source, current_order, conditions)
    if replaced is None:
        return ConstraintTranslation(source, None, reason)
    opaque_markers = (
        "prim", "fact-pn-constant(", "fact-join-compare(", "object-pn-constant(",
        "object-join-compare(", "current-fact.", "fact[p", "object[p", "handler-get(", "handler-put("
    )
    if any(marker in replaced for marker in opaque_markers):
        return ConstraintTranslation(source, None, "contains unresolved compiled primitive")
    return ConstraintTranslation(source, replaced, None)


def translate_condition_tests(condition: dict, conditions: list[dict]) -> list[ConstraintTranslation]:
    result = [translate_test(item, int(condition["order"]), conditions) for item in condition["alpha_tests"]]
    if condition["join_test"] is not None:
        result.append(translate_test(condition["join_test"], int(condition["order"]), conditions))
    return result
