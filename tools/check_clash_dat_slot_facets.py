#!/usr/bin/env python3
from pathlib import Path

from clash_dat_classes import parse_defclass
from clash_dat_slot_facets import recover_slot_facets, render_recovered_classes
from decompile_clash_dat import parse_bsave
from generate_clash_recovered_clp import GAME_CLASS_NAMES

EXPECTED_SLOT_NAMES_BY_CLASS = {
    "gracz": ["id", "nazwa_gracza", "religia", "pieniadze", "WN"],
    "budowla": ["id", "gracz", "x", "y", "moc"],
    "twierdza": ["szpital", "szkola", "warsztat", "kuznia", "koszary"],
    "oddzial": ["id", "gracz", "x", "y", "tiredness", "PA", "moc", "jednostki"],
}


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    classes = parse_defclass(source, ir)
    report = recover_slot_facets(ir, classes)
    rendered, rendered_report = render_recovered_classes(ir, classes, GAME_CLASS_NAMES)

    assert report == rendered_report
    assert report["slot_count"] == 23
    assert report["single_slot_count"] + report["multislot_count"] == 23
    assert report["constraint_count"] == 0
    assert report["constraint_serialization_status"].startswith("not serialized")
    assert all(item["constraint_index"] == -1 for item in report["slots"])
    assert all(item["constraint_serialized"] is False for item in report["slots"])
    assert all(item["default_source"].startswith("(default") for item in report["slots"])
    assert all(item["form"] in {"slot", "multislot"} for item in report["slots"])
    assert all(item["override_message"] for item in report["slots"])
    assert all(item["default_override_message"] for item in report["slots"])

    by_class = {}
    for item in report["slots"]:
        by_class.setdefault(item["class_name"], []).append(item["slot_name"])
    assert by_class == EXPECTED_SLOT_NAMES_BY_CLASS

    for item in report["slots"]:
        facets = item["facets"]
        assert set(facets) == {
            "shared", "multiple", "composite", "no_inherit", "no_write",
            "initialize_only", "dynamic_default", "no_default", "reactive",
            "public_visibility", "create_read_accessor", "create_write_accessor",
        }
        if item["default_expression"] != -1:
            assert 0 <= item["default_expression"] < ir["expression_count"]

    assert rendered.count("(defclass ") == 7
    assert rendered.count("    (storage ") == 23
    assert rendered.count("    (access ") == 23
    assert rendered.count("    (propagation ") == 23
    assert rendered.count("    (source ") == 23
    assert rendered.count("    (pattern-match ") == 23
    assert rendered.count("    (visibility ") == 23
    assert rendered.count("    (create-accessor ") == 23
    assert rendered.count("    (override-message ") == 23
    assert "No constraint records were serialized" in rendered
    assert "(defclass oddzial" in rendered
    assert "(defclass gracz" in rendered

    print("CLASH.DAT defclass slot-facet contract: PASS")
    print(
        f"slots={report['slot_count']} single={report['single_slot_count']} "
        f"multi={report['multislot_count']} shared={report['shared_count']} "
        f"dynamic-default={report['dynamic_default_count']} no-default={report['no_default_count']}"
    )
    print(
        f"composite={report['composite_count']} no-inherit={report['no_inherit_count']} "
        f"read-only={report['read_only_count']} initialize-only={report['initialize_only_count']} "
        f"public={report['public_count']} custom-override={report['custom_override_message_count']}"
    )
    print("constraints=0: source type/range/cardinality restrictions were not serialized")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
