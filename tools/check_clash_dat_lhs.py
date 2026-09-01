#!/usr/bin/env python3
from pathlib import Path

from clash_dat_lhs import recover_rule_lhs, render_recovered_lhs
from decompile_clash_dat import parse_bsave


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = recover_rule_lhs(source, ir)

    assert report["rule_count"] == 95
    assert report["condition_occurrence_count"] == 425
    assert report["class_report"]["counts"]["classes"] == 24
    assert report["class_report"]["counts"]["slot_names"] == 17

    rules = {item["name"]: item for item in report["rules"]}

    shrine = rules["podejdz_do_swiatyni_najblizej_init"]
    assert [item["join_index"] for item in shrine["conditions"]] == [1, 27, 26, 25, 24, 23]
    assert [item["kind"] for item in shrine["conditions"]] == ["fact", "object", "fact", "fact", "fact", "fact"]
    assert shrine["conditions"][1]["classes"] == ("oddzial",)
    assert shrine["conditions"][1]["tested_slots"] == (
        "system-slot#0", "id", "gracz", "x", "y", "PA"
    )
    assert [item["negated"] for item in shrine["conditions"]] == [False, False, False, True, True, True]

    castle = rules["postaw_zamek"]
    assert [item["join_index"] for item in castle["conditions"]] == [1, 210, 209, 225, 224, 223]
    assert castle["conditions"][-1]["classes"] == ("oddzial",)
    assert castle["conditions"][-1]["tested_slots"] == (
        "system-slot#0", "id", "gracz", "x", "y"
    )

    production = rules["produkcja_main_1"]
    assert len(production["conditions"]) == 6
    assert production["conditions"][-1]["join_test"] is not None
    assert "fact-join-compare" in production["conditions"][-1]["join_test"]

    recovered = render_recovered_lhs(report, ir)
    assert recovered.count("(defrule ") == 95
    assert "(defrule postaw_zamek" in recovered
    assert "(object (is-a oddzial) ...)" in recovered
    assert "object slots referenced by alpha bitmap: system-slot#0, id, gracz, x, y" in recovered
    assert "normalized source-like LHS recovered from RETE" in recovered

    print("CLASH.DAT LHS recovery contract: PASS")
    print("rules=95 condition-occurrences=425; fact/object LHS patterns and compiled tests rendered")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
