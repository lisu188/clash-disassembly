#!/usr/bin/env python3
from pathlib import Path

from clash_dat_rete import rete_report
from decompile_clash_dat import parse_bsave

EXPECTED_DEPTHS = {1: 19, 2: 62, 3: 52, 4: 42, 5: 41, 6: 34, 7: 20, 8: 14, 9: 8, 10: 2, 11: 1}


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = rete_report(source, ir)

    assert report["join_count"] == 295
    assert report["fact_pattern_count"] == 64
    assert report["object_alpha_count"] == 20
    assert report["object_pattern_count"] == 14
    assert report["mapped_join_count"] == 295
    assert report["fact_owned_join_count"] == 218
    assert report["object_owned_join_count"] == 77

    joins = report["joins"]
    assert sum(j["first_join"] for j in joins) == 19
    assert sum(j["logical_join"] for j in joins) == 0
    assert sum(j["join_from_the_right"] for j in joins) == 0
    assert sum(j["pattern_is_negated"] for j in joins) == 113
    assert {j["rhs_type"] for j in joins} == {0, 1}
    assert all((j["rhs_type"] == 0) == (j["rhs"]["kind"] == "fact") for j in joins)
    assert all((j["rhs_type"] == 1) == (j["rhs"]["kind"] == "object") for j in joins)

    depths = {}
    for join in joins:
        depths[join["depth"]] = depths.get(join["depth"], 0) + 1
    assert depths == EXPECTED_DEPTHS

    facts = report["fact_patterns"]
    assert len(facts) == 64
    assert sum(node["stop_node"] for node in facts) == 55
    assert sum(node["entry_join"] != -1 for node in facts) == 55
    assert {node["which_slot"] for node in facts} == {0}
    assert {node["template"] for node in facts} == {item["name"] for item in ir["templates"]}

    objects = report["object_patterns"]
    assert len(objects) == 14
    assert all(node["which_field"] == 1 for node in objects)
    assert all(node["multifield_node"] is False for node in objects)
    assert all(node["end_slot"] is False for node in objects)

    by_name = {rule["name"]: rule for rule in report["rules"]}
    shrine = by_name["podejdz_do_swiatyni_najblizej_init"]
    assert [j["index"] for j in shrine["join_path"]] == [1, 27, 26, 25, 24, 23]
    assert [j["rhs"]["kind"] for j in shrine["join_path"]] == ["fact", "object", "fact", "fact", "fact", "fact"]
    assert [j["rhs"].get("template") for j in shrine["join_path"]] == ["gracz", None, "swiatynia", "budowanie", "najblizej", "oddz"]
    assert [j["pattern_is_negated"] for j in shrine["join_path"]] == [False, False, False, True, True, True]

    castle = by_name["postaw_zamek"]
    assert [j["index"] for j in castle["join_path"]] == [1, 210, 209, 225, 224, 223]
    assert [j["rhs"].get("template") for j in castle["join_path"][:-1]] == ["gracz", "ilosc-zamkow", "zamek_place", "budowanie", "maszeruj"]
    assert castle["join_path"][-1]["rhs"]["kind"] == "object"
    assert castle["join_path"][-1]["rhs"]["alpha_node"] == 0

    production = by_name["produkcja_main_1"]
    assert [j["index"] for j in production["join_path"]] == [1, 182, 181, 180, 179, 178]
    assert [j["pattern_is_negated"] for j in production["join_path"]] == [False, False, True, True, False, True]

    print("CLASH.DAT RETE contract: PASS")
    print("joins=295 mapped=295 fact=218 object=77 negated=113")
    print("fact-patterns=64 object-alphas=20 object-patterns=14")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
