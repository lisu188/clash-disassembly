#!/usr/bin/env python3
from pathlib import Path

from clash_dat_classes import parse_defclass
from clash_dat_handler_slots import handler_reference_report
from clash_dat_primitives import (
    DECODED_BITMAP_TYPES,
    bitmap_primitive_report,
    decode_primitive,
    typed_expressions,
    typed_joins,
    typed_rules,
)
from clash_dat_templates import deftemplate_report
from decompile_clash_dat import parse_bsave

EXPECTED_COUNTS = {
    "FACT_JN_CMP2": 103,
    "FACT_SLOT_LENGTH": 32,
    "FACT_PN_VAR3": 4,
    "FACT_JN_VAR1": 36,
    "FACT_JN_VAR3": 421,
    "FACT_PN_CONSTANT2": 30,
    "OBJ_GET_SLOT_JNVAR1": 630,
    "OBJ_PN_CONSTANT": 2,
    "OBJ_JN_CMP1": 15,
}

EXPECTED_SAMPLES = {
    4: (24, "0102020001000000", {"slot1": 0, "pattern2": 1, "slot2": 0}),
    55: (25, "04010000", {"min_length": 4, "exactly": True, "which_slot": 0}),
    434: (28, "01000000", {"from_beginning": True, "which_slot": 0}),
    1987: (29, "05000000", {"fact_address": True, "which_pattern": 1, "source_pattern_ordinal": 2}),
    1: (31, "09000900", {"begin_offset": 2, "which_pattern": 9, "source_pattern_ordinal": 10}),
    56: (33, "03000000", {"test_for_equality": True, "from_beginning": True}),
    2: (47, "0280020001000000", {"which_slot": 2, "which_pattern": 5, "all_fields": True}),
    553: (50, "80040000", {"pass": True, "from_beginning": True}),
    59: (52, "0780070003020000", {"first_slot": 7, "second_slot": 7, "first_pattern": 3, "second_pattern": 2}),
}


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = bitmap_primitive_report(ir)

    assert report["decoded_expression_count"] == 1273
    assert report["decoded_type_counts"] == EXPECTED_COUNTS
    assert len(typed_expressions(ir)) == 5237
    assert len(typed_rules(ir)) == 95
    assert len(typed_joins(ir)) == 295

    used_decoded_types = {
        expression[0]
        for expression in ir["expressions"]
        if expression[0] in DECODED_BITMAP_TYPES
    }
    assert used_decoded_types == DECODED_BITMAP_TYPES

    for expression_index, (type_id, raw_hex, expected_fields) in EXPECTED_SAMPLES.items():
        expression = ir["expressions"][expression_index]
        assert expression[0] == type_id
        decoded = decode_primitive(expression, ir, expression_index)
        assert decoded is not None
        assert decoded.raw_hex == raw_hex
        for name, expected in expected_fields.items():
            assert decoded.fields[name] == expected, (
                expression_index,
                decoded.type_name,
                name,
                decoded.fields[name],
                expected,
            )

    handler_get = [e for e in ir["expressions"] if e[0] == 58]
    handler_put = [e for e in ir["expressions"] if e[0] == 59]
    assert len(handler_get) == 47
    assert len(handler_put) == 23
    assert all(len(ir["bitmaps"][e[1]]) == 6 for e in handler_get + handler_put)
    assert len(report["handler_slot_references"]) == 70

    classes = parse_defclass(source, ir)
    handlers = handler_reference_report(ir, classes)
    assert handlers["count"] == 70
    assert handlers["get_count"] == 47
    assert handlers["put_count"] == 23
    assert all(not item["class_name"].startswith("class#") for item in handlers["references"])
    assert all(not item["slot_name"].startswith("system-slot#") for item in handlers["references"])
    assert {"id", "gracz", "x", "y"}.issubset(set(handlers["slots"]))
    assert all(item["clips_target"].startswith("?self:") for item in handlers["references"])

    templates = deftemplate_report(ir)
    assert templates["count"] == 25
    assert templates["implied_count"] == 24
    assert templates["explicit_count"] == 1
    assert templates["serialized_slot_count"] == 0
    assert templates["all_slot_lists_null"] is True
    assert templates["templates"][0]["name"] == "initial-fact"
    assert templates["templates"][0]["implied"] is False
    assert all(item["implied"] for item in templates["templates"][1:])

    print("CLASH.DAT primitive decoder contract: PASS")
    print("decoded=1273 matcher bitmap primitives across 9 types")
    print("deftemplates=25 implied=24 serialized-slots=0 (ordered facts)")
    print("HANDLER_GET/PUT=70 decoded as uint16 class_id + uint32 slot_name_id")
    print(f"handler-classes={len(handlers['classes'])} handler-slots={len(handlers['slots'])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
