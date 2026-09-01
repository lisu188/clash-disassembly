#!/usr/bin/env python3
from pathlib import Path

from decompile_clash_dat import parse_bsave, render_clips

EXPECTED_PRIOR = {
    1: 15.0,
    2: 20.0,
    3: 10.0,
    4: 10.0,
}

EXPECTED_GLOBALS = {
    "zasieg_dzialan": 10,
    "koszt_ruchu": 8,
    "odleglosc_waga": 0,
    "atak_zamku_waga": 0.9,
    "atak_oddzialu_waga": 0.8,
    "waga_komputer": 0.5,
}

EXPECTED_DEFFUNCTIONS = {
    "atakowanie_oddzialu",
    "atakowanie_zamku",
    "Licence_To_Buy_Kuznia",
    "Licence_To_Buy_Warsztat",
    "Licence_To_Buy_Koszary",
    "Licence-Product",
    "Procent",
}


def expression_value(ir, index):
    type_id, value, _, _ = ir["expressions"][index]
    if type_id == 0:
        return ir["floats"][value]
    if type_id == 1:
        return ir["integers"][value]
    raise AssertionError(f"unexpected global initializer type {type_id} at expression {index}")


def parse_prior(path):
    result = {}
    for raw_line in path.read_text(encoding="latin1").splitlines():
        line = raw_line.split(";;;", 1)[0].strip()
        if not line:
            continue
        target_type, weight = line.split()[:2]
        result[int(target_type)] = float(weight)
    return result


def main():
    ir = parse_bsave(Path("CLASH.DAT"))

    assert ir["version"] == "V6.00"
    assert ir["function_count"] == 122
    assert ir["symbol_count"] == 316
    assert len(ir["floats"]) == 9
    assert len(ir["integers"]) == 48
    assert len(ir["bitmaps"]) == 210
    assert ir["expression_count"] == 5237
    assert ir["rule_counts"] == {"modules": 1, "rules": 95, "joins": 295}
    assert len(ir["templates"]) == 25
    assert len(ir["deffunctions"]) == 7
    assert len(ir["globals"]) == 6

    globals_ = {
        item["name"]: expression_value(ir, item["initial_expr"])
        for item in ir["globals"]
    }
    assert globals_ == EXPECTED_GLOBALS

    deffunctions = {item["name"] for item in ir["deffunctions"]}
    assert deffunctions == EXPECTED_DEFFUNCTIONS

    rule_names = {item["name"] for item in ir["rules"]}
    assert "postaw_zamek" in rule_names
    assert "produkcja_main_1" in rule_names
    assert "atakowanie_oddzialu" not in rule_names

    clp = render_clips(ir)
    assert clp.count("(defrule ") == 95
    assert clp.count("(deffunction ") == 7
    assert "?*atak_zamku_waga* = 0.9" in clp
    assert "?*atak_oddzialu_waga* = 0.8" in clp
    assert "?*waga_komputer* = 0.5" in clp
    assert "(defrule postaw_zamek" in clp
    assert "(deffunction atakowanie_oddzialu" in clp

    assert parse_prior(Path("PRIOR")) == EXPECTED_PRIOR

    print("CLASH.DAT BSAVE contract: PASS")
    print("version=V6.00 functions=122 symbols=316 expressions=5237 rules=95 joins=295")
    print("deftemplates=25 deffunctions=7 defglobals=6 bitmaps=210")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
