#!/usr/bin/env python3
"""Measure line coverage of the pure testable set from gcov output.

Runs gcov on the coverage TU (test_all.c), parses the produced clash95.c.gcov,
and reports covered/total executable lines restricted to the frozen pure
function set (tests/unit/pure_set.json).

Usage:
  measure_pure_coverage.py <build_dir> [--worst N] [--json OUT]
"""
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PURE = os.path.join(ROOT, "tests/unit/pure_set.json")


def run_gcov(build_dir):
    objdir = os.path.join(build_dir, "CMakeFiles/clash95_unit_tests.dir/tests/unit")
    gcda = os.path.join(objdir, "test_all.c.gcda")
    if not os.path.exists(gcda):
        sys.exit(f"no gcda at {gcda}; run the unit-test binary first")
    # Run gcov inside the objdir so .gcov files (including for the #included
    # clash95.c) are emitted there.
    subprocess.run(
        ["gcov", "test_all.c.gcno"],
        cwd=objdir, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
    )
    cand = os.path.join(objdir, "clash95.c.gcov")
    if not os.path.exists(cand):
        for f in os.listdir(objdir):
            if f.endswith("clash95.c.gcov"):
                cand = os.path.join(objdir, f)
                break
    if not os.path.exists(cand):
        sys.exit("gcov did not produce clash95.c.gcov")
    return cand


def parse_gcov(path):
    """Return {lineno: covered_bool} for executable lines only."""
    execline = {}
    with open(path, errors="replace") as f:
        for line in f:
            parts = line.split(":", 2)
            if len(parts) < 3:
                continue
            cnt = parts[0].strip()
            try:
                ln = int(parts[1].strip())
            except ValueError:
                continue
            if ln == 0:
                continue
            if cnt in ("-",):
                continue  # non-executable
            if cnt in ("#####", "====="):
                execline[ln] = False
            else:
                execline[ln] = True  # a numeric count => executed
    return execline


def main():
    build_dir = sys.argv[1]
    worst = 0
    jsonout = None
    args = sys.argv[2:]
    for i, a in enumerate(args):
        if a == "--worst":
            worst = int(args[i + 1])
        if a == "--json":
            jsonout = args[i + 1]

    gcov = run_gcov(build_dir)
    execline = parse_gcov(gcov)
    pure = json.load(open(PURE))["functions"]

    total = covered = 0
    per_fn = []
    for fn in pure:
        lo, hi = fn["start_line"], fn["end_line"]
        ex = [ln for ln in range(lo, hi) if ln in execline]
        cov = [ln for ln in ex if execline[ln]]
        per_fn.append((fn["name"], len(cov), len(ex)))
        total += len(ex)
        covered += len(cov)

    pct = (100.0 * covered / total) if total else 0.0
    fns_full = sum(1 for _, c, e in per_fn if e and c == e)
    fns_zero = sum(1 for _, c, e in per_fn if e and c == 0)
    fns_partial = sum(1 for _, c, e in per_fn if e and 0 < c < e)
    print(f"pure functions:        {len(pure)}")
    print(f"executable lines:      {total}")
    print(f"covered lines:         {covered}")
    print(f"LINE COVERAGE:         {pct:.2f}%")
    print(f"functions fully cov:   {fns_full}")
    print(f"functions partial:     {fns_partial}")
    print(f"functions zero cov:    {fns_zero}")

    if worst:
        print(f"\n--- {worst} least-covered functions (name: covered/exec) ---")
        ranked = sorted(
            (p for p in per_fn if p[2] > 0),
            key=lambda p: (p[1] / p[2], -p[2]),
        )
        for name, c, e in ranked[:worst]:
            print(f"  {name}: {c}/{e}")

    if jsonout:
        json.dump(
            {
                "pct": pct,
                "covered": covered,
                "total": total,
                "functions": [
                    {"name": n, "covered": c, "exec": e} for n, c, e in per_fn
                ],
            },
            open(jsonout, "w"),
            indent=1,
        )


if __name__ == "__main__":
    main()
