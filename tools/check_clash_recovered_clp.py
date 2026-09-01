#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

from decompile_clash_dat import parse_bsave
from generate_clash_recovered_clp import GAME_CLASS_NAMES
from generate_clash_recovered_constraints import render_recovered_program


def assert_balanced_clips(text: str) -> None:
    depth = 0
    in_string = False
    escaped = False
    in_comment = False
    for char in text:
        if in_comment:
            if char == "\n":
                in_comment = False
            continue
        if in_string:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == '"':
                in_string = False
            continue
        if char == ";":
            in_comment = True
        elif char == '"':
            in_string = True
        elif char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
            assert depth >= 0, "closing parenthesis before matching open"
    assert not in_string, "unterminated string literal"
    assert depth == 0, f"unbalanced CLIPS parentheses: depth={depth}"


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)

    assert manifest["version"] == "V6.00"
    assert manifest["rules"] == 95
    assert manifest["conditions"] == 425
    assert manifest["defglobals"] == 6
    assert manifest["deffunctions"] == 7
    assert manifest["defclass_slots"] == 23
    slot_report = manifest["defclass_slot_facets"]
    assert slot_report["slot_count"] == 23
    assert slot_report["constraint_count"] == 0
    assert slot_report["single_slot_count"] + slot_report["multislot_count"] == 23
    assert manifest["defmessage_handlers"] == 69
    assert manifest["system_message_handlers"] + manifest["user_message_handlers"] == 69
    assert manifest["system_message_handlers"] > 0
    assert manifest["user_message_handlers"] > 0
    assert len(manifest["message_handlers_manifest"]) == 69
    assert sum(manifest["message_handler_type_counts"].values()) == 69
    assert sum(manifest["message_handler_class_counts"].values()) == 69
    assert set(manifest["game_defclasses_emitted"]) == GAME_CLASS_NAMES

    rules = manifest["rules_manifest"]
    assert len(rules) == 95
    assert len({item["output_name"] for item in rules}) == 95
    assert sum(item["condition_count"] for item in rules) == 425
    assert all(item["terminal_join"] >= 0 for item in rules)

    compiled = manifest["compiled_test_count"]
    translated = manifest["translated_test_count"]
    unresolved = manifest["unresolved_test_count"]
    assert compiled > 0
    assert translated > 0
    assert translated + unresolved == compiled
    assert manifest["class_bitmap_tests_emitted"] > 0
    assert manifest["object_join_translated_count"] > 0
    assert manifest["object_constant_translated_count"] > 0
    assert sum(item["compiled_test_count"] for item in rules) == compiled
    assert sum(item["translated_test_count"] for item in rules) == translated
    assert sum(item["unresolved_test_count"] for item in rules) == unresolved

    assert program.count("(defrule ") == 95
    assert program.count("(deffunction ") == 7
    assert program.count("(defmessage-handler ") == 69
    assert program.count("(defclass ") == 7
    assert program.count("  =>") == 95
    assert ";;; DEFMESSAGE-HANDLERS" in program
    assert ";;; LHS unavailable as original source" not in program
    assert ";;; DEFRULES — recovered constraints + RHS" in program
    assert "?f1 <- (gracz $?f1_fields)" in program
    assert "(not (" in program
    assert "(test " in program
    assert "(length$ $?f" in program or "(nth$ " in program
    assert "?o" in program and "_x" in program
    assert "?self:" in program
    assert "handler-get(" not in program
    assert "handler-put(" not in program
    assert "Buduj-Zamek" in program
    assert "produkcja_main_1" in program
    assert "postaw_zamek" in program
    assert "(defclass oddzial" in program
    assert "  (slot x\n" in program or "  (multislot x\n" in program
    assert "  (slot y\n" in program or "  (multislot y\n" in program
    assert program.count("    (storage ") == 23
    assert program.count("    (access ") == 23
    assert program.count("    (propagation ") == 23
    assert program.count("    (source ") == 23
    assert program.count("    (pattern-match ") == 23
    assert program.count("    (visibility ") == 23
    assert program.count("    (create-accessor ") == 23
    assert program.count("    (override-message ") == 23
    assert "No constraint records were serialized" in program

    duplicate_names = manifest["duplicate_bsave_rule_names"]
    assert duplicate_names, "expected BSAVE disjunct records sharing source rule names"
    assert manifest["synthetic_rule_renames"], "duplicate rule/disjunct names must be made unique"

    assert program.count(";;; unresolved compiled-test") == unresolved
    assert_balanced_clips(program)

    print("CLASH_recovered.clp slot + constraint + message-handler recovery contract: PASS")
    print(
        f"rules={manifest['rules']} conditions={manifest['conditions']} slots={manifest['defclass_slots']} "
        f"multislots={slot_report['multislot_count']} constraints={slot_report['constraint_count']} "
        f"handlers={manifest['defmessage_handlers']} system-handlers={manifest['system_message_handlers']} "
        f"user-handlers={manifest['user_message_handlers']} compiled-tests={compiled} "
        f"translated={translated} unresolved={unresolved} "
        f"object-joins={manifest['object_join_translated_count']} "
        f"object-constants={manifest['object_constant_translated_count']}"
    )
    print(f"handler-types={manifest['message_handler_type_counts']}")
    print(f"synthetic-disjunct-renames={len(manifest['synthetic_rule_renames'])}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
