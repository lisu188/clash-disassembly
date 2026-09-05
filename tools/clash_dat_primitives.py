#!/usr/bin/env python3
"""Semantic decoders for CLIPS 6.00 compiled expression primitives in CLASH.DAT."""
from __future__ import annotations

from dataclasses import asdict, dataclass
from typing import Callable

TYPE_NAMES = {
    0: "FLOAT", 1: "INTEGER", 2: "SYMBOL", 3: "STRING", 8: "INSTANCE_NAME",
    10: "FCALL", 12: "PCALL", 13: "GBL_VARIABLE",
    24: "FACT_JN_CMP2", 25: "FACT_SLOT_LENGTH", 28: "FACT_PN_VAR3",
    29: "FACT_JN_VAR1", 31: "FACT_JN_VAR3", 33: "FACT_PN_CONSTANT2",
    34: "FACT_STORE_MULTIFIELD", 35: "DEFTEMPLATE_PTR",
    47: "OBJ_GET_SLOT_JNVAR1", 50: "OBJ_PN_CONSTANT", 52: "OBJ_JN_CMP1",
    57: "DEFCLASS_PTR", 58: "HANDLER_GET", 59: "HANDLER_PUT",
    60: "DEFGLOBAL_PTR", 65: "PROC_PARAM", 66: "PROC_WILD_PARAM",
    67: "PROC_GET_BIND", 68: "PROC_BIND",
}

DECODED_BITMAP_TYPES = {24, 25, 28, 29, 31, 33, 47, 50, 52}
HANDLER_BITMAP_TYPES = {58, 59}


@dataclass(frozen=True)
class PackedExpression:
    index: int
    type: int
    value: int
    arg: int
    next: int

    @property
    def type_name(self) -> str:
        return TYPE_NAMES.get(self.type, f"TYPE_{self.type}")


@dataclass(frozen=True)
class DefruleRecord:
    index: int
    name: str
    module: int
    next: int
    salience: int
    local_var_count: int
    complexity_flags: int
    dynamic_salience_expr: int
    actions_expr: int
    logical_join: int
    last_join: int
    disjunct: int


@dataclass(frozen=True)
class JoinRecord:
    index: int
    fields: tuple[int, int, int, int, int, int, int, int]


@dataclass(frozen=True)
class PrimitiveDecode:
    expression_index: int
    type: int
    type_name: str
    bitmap_index: int
    raw_hex: str
    fields: dict[str, int | bool]
    semantic: str

    def as_json(self) -> dict:
        return asdict(self)


def _bits(blob: bytes, start: int, width: int) -> int:
    return (int.from_bytes(blob, "little", signed=False) >> start) & ((1 << width) - 1)


def _flag(blob: bytes, bit: int) -> bool:
    return bool(_bits(blob, bit, 1))


def _require_size(blob: bytes, size: int, type_name: str) -> None:
    if len(blob) != size:
        raise ValueError(f"{type_name} expects {size} bitmap bytes, got {len(blob)}")


def _decode_fact_jn_cmp2(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 8, "FACT_JN_CMP2")
    return {
        "pass": _flag(blob, 0), "fail": _flag(blob, 1),
        "slot1": _bits(blob, 2, 7), "from_beginning1": _flag(blob, 9),
        "offset1": _bits(blob, 10, 7), "pattern2": _bits(blob, 17, 8),
        "slot2": _bits(blob, 25, 7), "from_beginning2": _flag(blob, 32),
        "offset2": _bits(blob, 33, 7),
    }


def _decode_fact_slot_length(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "FACT_SLOT_LENGTH")
    return {"min_length": _bits(blob, 0, 8), "exactly": _flag(blob, 8), "which_slot": _bits(blob, 9, 8)}


def _decode_fact_pn_var3(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "FACT_PN_VAR3")
    return {
        "from_beginning": _flag(blob, 0), "from_end": _flag(blob, 1),
        "begin_offset": _bits(blob, 2, 7), "end_offset": _bits(blob, 9, 7),
        "which_slot": _bits(blob, 16, 8),
    }


def _decode_fact_jn_var1(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "FACT_JN_VAR1")
    stored_pattern = _bits(blob, 2, 8)
    return {
        "fact_address": _flag(blob, 0), "all_fields": _flag(blob, 1),
        "which_pattern": stored_pattern, "source_pattern_ordinal": stored_pattern + 1,
        "which_slot": _bits(blob, 10, 8), "which_field": _bits(blob, 18, 8),
    }


def _decode_fact_jn_var3(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "FACT_JN_VAR3")
    stored_pattern = _bits(blob, 16, 8)
    return {
        "from_beginning": _flag(blob, 0), "from_end": _flag(blob, 1),
        "begin_offset": _bits(blob, 2, 7), "end_offset": _bits(blob, 9, 7),
        "which_pattern": stored_pattern, "source_pattern_ordinal": stored_pattern + 1,
        "which_slot": _bits(blob, 24, 8),
    }


def _decode_fact_pn_constant2(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "FACT_PN_CONSTANT2")
    return {
        "test_for_equality": _flag(blob, 0), "from_beginning": _flag(blob, 1),
        "offset": _bits(blob, 2, 8), "which_slot": _bits(blob, 10, 8),
    }


def _decode_obj_get_slot_jnvar1(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 8, "OBJ_GET_SLOT_JNVAR1")
    return {
        "which_slot": _bits(blob, 0, 15), "which_pattern": _bits(blob, 15, 8),
        "which_field": _bits(blob, 23, 8), "object_address": _flag(blob, 31),
        "all_fields": _flag(blob, 32),
    }


def _decode_obj_pn_constant(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 4, "OBJ_PN_CONSTANT")
    return {
        "offset": _bits(blob, 0, 7), "pass": _flag(blob, 7), "fail": _flag(blob, 8),
        "general": _flag(blob, 9), "from_beginning": _flag(blob, 10),
    }


def _decode_obj_jn_cmp1(blob: bytes) -> dict[str, int | bool]:
    _require_size(blob, 8, "OBJ_JN_CMP1")
    return {
        "first_slot": _bits(blob, 0, 15), "pass": _flag(blob, 15),
        "second_slot": _bits(blob, 16, 15), "fail": _flag(blob, 31),
        "first_pattern": _bits(blob, 32, 8), "second_pattern": _bits(blob, 40, 8),
    }


DECODERS: dict[int, Callable[[bytes], dict[str, int | bool]]] = {
    24: _decode_fact_jn_cmp2,
    25: _decode_fact_slot_length,
    28: _decode_fact_pn_var3,
    29: _decode_fact_jn_var1,
    31: _decode_fact_jn_var3,
    33: _decode_fact_pn_constant2,
    47: _decode_obj_get_slot_jnvar1,
    50: _decode_obj_pn_constant,
    52: _decode_obj_jn_cmp1,
}


def _fact_var_semantic(prefix: str, fields: dict[str, int | bool]) -> str:
    """Describe the exact FactGetVar3 selector mode.

    CLIPS factgen.c uses the two direction bits as a three-way selector:
    beginning-only and end-only are single-field references, while both bits set
    denotes a multifield segment. Treating every Var3 as a multifield loses the
    scalar/multifield distinction and produces invalid source comparisons.
    """
    slot = fields["which_slot"]
    from_beginning = bool(fields["from_beginning"])
    from_end = bool(fields["from_end"])
    if from_beginning and from_end:
        return (
            f"{prefix}.slot[{slot}]"
            f".multifield(begin+{fields['begin_offset']},end-{fields['end_offset']})"
        )
    if from_beginning:
        return f"{prefix}.slot[{slot}].field[{fields['begin_offset']}]"
    if from_end:
        return f"{prefix}.slot[{slot}].field-from-end[{fields['end_offset']}]"
    return f"{prefix}.slot[{slot}].selector-invalid"


def semantic_text(type_id: int, fields: dict[str, int | bool]) -> str:
    if type_id == 29:
        p = int(fields["source_pattern_ordinal"])
        if fields["fact_address"]:
            return f"fact[p{p}]"
        if fields["all_fields"]:
            return f"fact[p{p}].slot[{fields['which_slot']}]"
        return f"fact[p{p}].slot[{fields['which_slot']}].field[{fields['which_field']}]"
    if type_id == 31:
        return _fact_var_semantic(f"fact[p{fields['source_pattern_ordinal']}]​".replace("\u200b", ""), fields)
    if type_id == 28:
        return _fact_var_semantic("current-fact", fields)
    if type_id == 47:
        p = fields["which_pattern"]
        if fields["object_address"]:
            return f"object[p{p}]"
        if fields["all_fields"]:
            return f"object[p{p}].slot[{fields['which_slot']}]"
        return f"object[p{p}].slot[{fields['which_slot']}].field[{fields['which_field']}]"
    if type_id == 24:
        return (
            "fact-join-compare("
            f"slot1={fields['slot1']},offset1={fields['offset1']},"
            f"pattern2={fields['pattern2']},slot2={fields['slot2']},offset2={fields['offset2']},"
            f"pass={int(bool(fields['pass']))},fail={int(bool(fields['fail']))})"
        )
    if type_id == 25:
        mode = "exact" if fields["exactly"] else "minimum"
        return f"fact-slot-length(slot={fields['which_slot']},{mode}={fields['min_length']})"
    if type_id == 33:
        op = "==" if fields["test_for_equality"] else "!="
        direction = "begin" if fields["from_beginning"] else "end"
        return f"fact-pn-constant(slot={fields['which_slot']},{direction}+{fields['offset']} {op} <arg>)"
    if type_id == 50:
        return (
            "object-pn-constant("
            f"offset={fields['offset']},from_beginning={int(bool(fields['from_beginning']))},"
            f"general={int(bool(fields['general']))},pass={int(bool(fields['pass']))},"
            f"fail={int(bool(fields['fail']))},value=<arg>)"
        )
    if type_id == 52:
        return (
            "object-join-compare("
            f"p{fields['first_pattern']}.slot[{fields['first_slot']}],"
            f"p{fields['second_pattern']}.slot[{fields['second_slot']}],"
            f"pass={int(bool(fields['pass']))},fail={int(bool(fields['fail']))})"
        )
    raise KeyError(type_id)


def decode_primitive(expression: tuple[int, int, int, int] | PackedExpression, ir: dict, index: int | None = None) -> PrimitiveDecode | None:
    if isinstance(expression, PackedExpression):
        expression_index, type_id, bitmap_index = expression.index, expression.type, expression.value
    else:
        if index is None:
            raise ValueError("index is required for tuple expressions")
        expression_index, type_id, bitmap_index = index, expression[0], expression[1]
    decoder = DECODERS.get(type_id)
    if decoder is None:
        return None
    bitmap = ir["bitmaps"][bitmap_index]
    fields = decoder(bitmap)
    return PrimitiveDecode(
        expression_index=expression_index,
        type=type_id,
        type_name=TYPE_NAMES[type_id],
        bitmap_index=bitmap_index,
        raw_hex=bitmap.hex(),
        fields=fields,
        semantic=semantic_text(type_id, fields),
    )


def decode_all_primitives(ir: dict) -> list[PrimitiveDecode]:
    result = []
    for index, expression in enumerate(ir["expressions"]):
        decoded = decode_primitive(expression, ir, index)
        if decoded is not None:
            result.append(decoded)
    return result


def typed_expressions(ir: dict) -> list[PackedExpression]:
    return [PackedExpression(i, item[0], item[1], item[2], item[3]) for i, item in enumerate(ir["expressions"])]


def typed_rules(ir: dict) -> list[DefruleRecord]:
    return [
        DefruleRecord(
            index=item["index"], name=item["name"], module=item["module"], next=item["next"],
            salience=item["salience"], local_var_count=item["local_var_count"],
            complexity_flags=item["complexity_flags"], dynamic_salience_expr=item["dynamic_salience_expr"],
            actions_expr=item["actions_expr"], logical_join=item["logical_join"],
            last_join=item["last_join"], disjunct=item["disjunct"],
        )
        for item in ir["rules"]
    ]


def typed_joins(ir: dict) -> list[JoinRecord]:
    return [JoinRecord(index=item["index"], fields=tuple(item["raw"])) for item in ir["joins"]]


def primitive_histogram(ir: dict) -> dict[str, int]:
    histogram: dict[str, int] = {}
    for expr in typed_expressions(ir):
        name = TYPE_NAMES.get(expr.type, f"TYPE_{expr.type}")
        histogram[name] = histogram.get(name, 0) + 1
    return dict(sorted(histogram.items()))


def bitmap_primitive_report(ir: dict) -> dict:
    decoded = decode_all_primitives(ir)
    decoded_counts: dict[str, int] = {}
    for item in decoded:
        decoded_counts[item.type_name] = decoded_counts.get(item.type_name, 0) + 1

    handler_refs = []
    for expr in typed_expressions(ir):
        if expr.type not in HANDLER_BITMAP_TYPES:
            continue
        bitmap = ir["bitmaps"][expr.value]
        handler_refs.append({
            "expression_index": expr.index,
            "type": expr.type,
            "type_name": expr.type_name,
            "bitmap_index": expr.value,
            "raw_hex": bitmap.hex(),
            "status": "typed, bitmap layout unresolved",
        })

    return {
        "decoded_expression_count": len(decoded),
        "decoded_type_counts": dict(sorted(decoded_counts.items())),
        "expression_type_histogram": primitive_histogram(ir),
        "decoded": [item.as_json() for item in decoded],
        "handler_slot_references": handler_refs,
    }
