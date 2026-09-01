#!/usr/bin/env python3
from pathlib import Path

from clash_dat_templates import deftemplate_report
from decompile_clash_dat import parse_bsave

EXPECTED_NAMES = [
    "initial-fact",
    "gracz",
    "misja",
    "najblizej",
    "kasuj",
    "oddz",
    "swiatynia",
    "skarb",
    "pulapka",
    "budowanie",
    "usunieto",
    "port",
    "gameinfo",
    "tura",
    "zamek",
    "zdobyty",
    "schemat",
    "zginal-zamek",
    "zbudowano",
    "wyznaczony",
    "zamek_place",
    "maszeruj",
    "ilosc-zamkow",
    "ilosc-twierdz",
    "zamek-wyslal-bron-biologiczna",
]

EXPECTED_PATTERN_NETWORK = [
    0, 1, 7, 10, 20, 23, 31, 32, 33, 34, 41, 42, 43,
    45, 47, 49, 50, 51, 52, 53, 59, 60, 61, 62, 63,
]


def main() -> int:
    ir = parse_bsave(Path("CLASH.DAT"))
    report = deftemplate_report(ir)
    templates = report["templates"]

    assert report["count"] == 25
    assert report["implied_count"] == 24
    assert report["explicit_count"] == 1
    assert report["serialized_slot_count"] == 0
    assert report["all_slot_lists_null"] is True
    assert [item["name"] for item in templates] == EXPECTED_NAMES
    assert [item["pattern_network"] for item in templates] == EXPECTED_PATTERN_NETWORK

    assert templates[0]["name"] == "initial-fact"
    assert templates[0]["implied"] is False
    assert all(item["implied"] for item in templates[1:])
    assert all(item["number_of_slots"] == 0 for item in templates)
    assert all(item["slot_list"] == -1 for item in templates)

    # Strategic facts are ordered implied relations. Field numbers in FACT_*
    # compiled primitives are positional fields, not named template slots.
    print("CLASH.DAT deftemplate contract: PASS")
    print("templates=25 implied=24 explicit=1 serialized-slots=0")
    print("strategic relations are ordered implied facts")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
