#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path

from clash_dat_source_expr import SourceExpressionRenderer
from decompile_clash_dat import parse_bsave


def main() -> int:
    ir = parse_bsave(Path("CLASH.DAT"))
    deffacts = ir["deffacts"]

    assert ir["deffacts_module_count"] == 1
    assert len(deffacts) == 1

    initial = deffacts[0]
    assert initial["index"] == 0
    assert initial["name"] == "initial-fact"
    assert initial["module"] == 0
    assert initial["next"] == -1
    assert initial["assert_list_expr"] == 5235

    rendered = SourceExpressionRenderer(ir).node(initial["assert_list_expr"])
    assert rendered == "(assert (initial-fact))"

    print("CLASH.DAT deffacts contract: PASS")
    print(
        f"modules={ir['deffacts_module_count']} deffacts={len(deffacts)} "
        f"name={initial['name']} assert-expr={initial['assert_list_expr']} source={rendered}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
