#!/usr/bin/env python3
"""Emit per-function uncovered source line numbers from the coverage gcov.

Usage: uncovered_lines.py <build_dir> [--json OUT] [--min N]
Lists each pure-set function with uncovered executable lines, giving the exact
clash95.c line numbers still marked '#####' so a targeting wave knows precisely
what to hit. --min filters to functions with >= N uncovered lines.
"""
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PURE = os.path.join(ROOT, "tests/unit/pure_set.json")


def gcov_lines(build_dir):
    objdir = os.path.join(build_dir, "CMakeFiles/clash95_unit_tests.dir/tests/unit")
    subprocess.run(["gcov", "test_all.c.gcno"], cwd=objdir,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    path = os.path.join(objdir, "clash95.c.gcov")
    if not os.path.exists(path):
        for f in os.listdir(objdir):
            if f.endswith("clash95.c.gcov"):
                path = os.path.join(objdir, f)
                break
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
            if ln == 0 or cnt == "-":
                continue
            execline[ln] = cnt not in ("#####", "=====")
    return execline


def main():
    build_dir = sys.argv[1]
    jsonout = None
    minn = 1
    for i, a in enumerate(sys.argv):
        if a == "--json":
            jsonout = sys.argv[i + 1]
        if a == "--min":
            minn = int(sys.argv[i + 1])
    execline = gcov_lines(build_dir)
    pure = json.load(open(PURE))["functions"]
    rows = []
    for fn in pure:
        unc = [ln for ln in range(fn["start_line"], fn["end_line"])
               if execline.get(ln) is False]
        if len(unc) >= minn:
            rows.append({"name": fn["name"], "start_line": fn["start_line"],
                         "end_line": fn["end_line"], "uncovered_lines": unc,
                         "uncovered": len(unc)})
    rows.sort(key=lambda r: -r["uncovered"])
    if jsonout:
        json.dump(rows, open(jsonout, "w"), indent=1)
    print(f"{len(rows)} functions with >= {minn} uncovered lines; "
          f"total {sum(r['uncovered'] for r in rows)} uncovered")
    for r in rows[:30]:
        print(f"  {r['uncovered']:3d}  {r['name']}  lines {r['uncovered_lines'][:8]}"
              f"{'...' if len(r['uncovered_lines'])>8 else ''}")


if __name__ == "__main__":
    main()
