#!/usr/bin/env python3
from pathlib import Path

from clash_dat_classes import decode_class_bitmap, decode_slot_bitmap, parse_defclass
from decompile_clash_dat import parse_bsave

EXPECTED_COUNTS = {
    "modules": 1,
    "classes": 24,
    "class_links": 137,
    "slot_names": 17,
    "slot_descriptors": 23,
    "instance_template_links": 43,
    "slot_name_map": 80,
    "handlers": 69,
    "max_class_id_count": 24,
}

EXPECTED_DECLARED_SLOTS = {
    "gracz": ["id", "nazwa_gracza", "religia", "pieniadze", "WN"],
    "budowla": ["id", "gracz", "x", "y", "moc"],
    "twierdza": ["szpital", "szkola", "warsztat", "kuznia", "koszary"],
    "oddzial": ["id", "gracz", "x", "y", "tiredness", "PA", "moc", "jednostki"],
}


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = parse_defclass(source, ir)

    assert report["counts"] == EXPECTED_COUNTS
    assert [item["class_id"] for item in report["classes"]] == list(range(24))
    assert [item["name"] for item in report["classes"][-7:]] == [
        "clash-class", "gracz", "budowla", "straznica", "twierdza", "zamek", "oddzial"
    ]

    for class_name, slots in EXPECTED_DECLARED_SLOTS.items():
        assert report["declared_slots"][class_name] == slots
    assert report["declared_slots"]["straznica"] == []
    assert report["declared_slots"]["zamek"] == []

    assert report["slot_name_by_id"][2] == "id"
    assert report["slot_name_by_id"][7] == "gracz"
    assert report["slot_name_by_id"][8] == "x"
    assert report["slot_name_by_id"][9] == "y"
    assert report["slot_name_by_id"][10] == "moc"
    assert report["slot_name_by_id"][17] == "PA"
    assert report["slot_name_by_id"][18] == "jednostki"

    oddzial = decode_class_bitmap(ir, 185, report)
    assert oddzial["ids"] == [23]
    assert oddzial["names"] == ["oddzial"]

    zamek = decode_class_bitmap(ir, 101, report)
    assert zamek["ids"] == [22]
    assert zamek["names"] == ["zamek"]

    buildings = decode_class_bitmap(ir, 160, report)
    assert buildings["ids"] == [20, 21, 22]
    assert buildings["names"] == ["straznica", "twierdza", "zamek"]

    xy_slots = decode_slot_bitmap(ir, 99, report)
    assert xy_slots["ids"] == [0, 2, 7, 8, 9]
    assert xy_slots["names"] == ["system-slot#0", "id", "gracz", "x", "y"]

    print("CLASH.DAT defclass contract: PASS")
    print("classes=24 slot-names=17 slot-descriptors=23 handlers=69")
    print("game classes and object-pattern class/slot bitmaps decoded")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
