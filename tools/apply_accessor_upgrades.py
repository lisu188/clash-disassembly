#!/usr/bin/env python3
"""Upgrade named-offset address arithmetic to the prelude accessor macros.

Converts the verbose canonical form the workstream-A batches produced, e.g.
  gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * i   ->  UNIT_STACK(i)
into the idiomatic accessor the prelude already defines and uses (203 candidate
sites: UNIT_STACK 188, BUILDING_RECORD 11, PLAYER_DATA 4).

FINDING (do NOT land under this repo's proof discipline): the change is
value-identical (integer addition is associative/commutative, so the computed
address is the same), but it is NOT mechanically provable. The accessor macro's
canonical term order (gameData + OFFSET + STRIDE*i) differs from the source term
order (often gameData + STRIDE*i + OFFSET), and this repo builds at -O0
(-std=gnu89 with no -O flag), where gcc emits code following the source
expression structure literally. tools/obj_diff_gate.sh therefore reports a real
instruction-selection difference (e.g. imul-then-add vs lea-then-imul in
WorldMap_RefreshUnitStatusPanel) - not a behavior change, but neither the
preprocessed-token gate nor the object-diff gate can prove preservation. Since
every campaign change must carry a mechanical proof, and this is a lateral
readability change rather than semantic recovery, the upgrade is deferred. It
would become provable only under term-order-preserving macros or an -O1+ build
where the constant fold makes the object code converge.

This tool is retained for that future scenario. Replacement is confined to code
segments via apply_sub_renames.split_code_and_literals; only simple-identifier
indices are matched.

Usage:
  python3 tools/apply_accessor_upgrades.py [--accessor UNIT_STACK] [--apply]
  # then verify with: bash tools/obj_diff_gate.sh <snapshot>  (expected: NOT ok at -O0)
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc

IDX = r"([A-Za-z_][A-Za-z0-9_]*)"

# Each accessor: the macro name, and the three term-order permutations of its
# canonical expansion `gameData + <OFFSET> + <STRIDE> * idx`. Group 1 = index.
SPECS = {
    "UNIT_STACK": {
        "offset": "UNIT_STACK_TABLE_OFFSET", "stride": "UNIT_STACK_STRIDE",
    },
    "BUILDING_RECORD": {
        "offset": "BUILDING_TABLE_OFFSET", "stride": "BUILDING_RECORD_SIZE",
    },
    "PLAYER_DATA": {
        "offset": "PLAYER_RUNTIME_STATE_OFFSET", "stride": "PLAYER_DATA_STRIDE",
    },
}


def patterns_for(spec):
    off, st = spec["offset"], spec["stride"]
    # three canonical additive orders; \b-bounded so leftover terms survive
    return [
        re.compile(r"gameData \+ %s \+ %s \* %s\b" % (off, st, IDX)),
        re.compile(r"%s \* %s \+ gameData \+ %s\b" % (st, IDX, off)),
        re.compile(r"gameData \+ %s \* %s \+ %s\b" % (st, IDX, off)),
    ]


def main():
    which = None
    if "--accessor" in sys.argv:
        which = sys.argv[sys.argv.index("--accessor") + 1]
    do_apply = "--apply" in sys.argv
    accessors = [which] if which else list(SPECS)

    total = {}
    for rel in lc.apply_files():
        path = os.path.join(lc.REPO, rel)
        with open(path, errors="replace") as f:
            text = f.read()
        segs = lc.split_code_and_literals(text)
        changed = False
        rebuilt = []
        for is_code, seg in segs:
            if is_code:
                for name in accessors:
                    for pat in patterns_for(SPECS[name]):
                        def repl(m, _n=name):
                            total[_n] = total.get(_n, 0) + 1
                            return "%s(%s)" % (_n, m.group(1))
                        seg, n = pat.subn(repl, seg)
                        if n:
                            changed = True
            rebuilt.append(seg)
        if changed and do_apply:
            with open(path, "w") as f:
                f.write("".join(rebuilt))

    import json
    print(json.dumps({"accessor_upgrades": total,
                      "applied": do_apply}, indent=1))


if __name__ == "__main__":
    main()
