#!/usr/bin/env python3
"""Regenerate the #include list of case files in tests/unit/test_all.c.

Includes every tests/unit/cases/test_*.c (sorted) except any ending in
.bad (quarantined). Idempotent: rewrites the block between the smoke include
and the CASES-INCLUDE-MARKER line.
"""
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TA = os.path.join(ROOT, "tests/unit/test_all.c")
MARK = "/* CASES-INCLUDE-MARKER"


def main():
    cases = sorted(
        os.path.basename(p)
        for p in glob.glob(os.path.join(ROOT, "tests/unit/cases/test_*.c"))
    )
    incls = "\n".join(f'#include "cases/{c}"' for c in cases)
    text = open(TA).read()
    lines = text.splitlines()
    # find the marker line, replace everything from the first cases include
    # section start up to (not including) the marker.
    out = []
    i = 0
    inserted = False
    while i < len(lines):
        if lines[i].lstrip().startswith(MARK):
            out.append(incls)
            out.append(lines[i])
            inserted = True
            i += 1
            continue
        # drop pre-existing case includes (they get regenerated)
        if lines[i].startswith('#include "cases/'):
            i += 1
            continue
        out.append(lines[i])
        i += 1
    assert inserted, "marker not found"
    open(TA, "w").write("\n".join(out) + "\n")
    print(f"wired {len(cases)} case files")


if __name__ == "__main__":
    main()
