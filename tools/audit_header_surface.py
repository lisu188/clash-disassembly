#!/usr/bin/env python3
"""Header-surface audit and coupling ratchet (P3.7).

Keeps the narrowed per-subsystem header architecture honest after the umbrella
deletion. Three passes:

1. FRESHNESS — the generated headers, data/subsystem_api.json, and every TU's
   marker-delimited include block must match a clean regeneration
   (tools/gen_subsystem_headers.py --check / --check-tu-includes).
2. INCLUDE POLICY — production recovered TUs may include recovered headers
   only inside the generated block; no TU may include another subsystem's
   <S>_internal.h or <S>_state.h; src/recovered_all.h is tests-only; the
   deleted umbrella names must not return.
3. COUPLING RATCHET — per-subsystem public-surface size (api function count),
   shared-global count, and peer edges are compared against
   data/header_surface_baseline.json: any INCREASE fails (decreases pass and
   are locked in with --mode update). This is the "new coupling is a
   deliberate choice" gate.

Usage:
  python3 tools/audit_header_surface.py --mode check    (CI)
  python3 tools/audit_header_surface.py --mode update   (conscious re-seed)
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
SURFACE = REPO / "data" / "subsystem_api.json"
BASELINE = REPO / "data" / "header_surface_baseline.json"
GEN = REPO / "tools" / "gen_subsystem_headers.py"

MARK_BEGIN = "/* CLASH95_GENERATED_INCLUDES_BEGIN"
MARK_END = "/* CLASH95_GENERATED_INCLUDES_END */"
FORBIDDEN_UMBRELLA = ("recovered_internal.h", "recovered_functions.h",
                      "recovered_foundation.h")


def run_gen(*flags: str) -> int:
    proc = subprocess.run([sys.executable, str(GEN), *flags],
                          capture_output=True, text=True)
    if proc.returncode != 0:
        print(proc.stdout.strip())
        print(proc.stderr.strip())
    return proc.returncode


def include_policy_errors() -> list[str]:
    errors = []
    manifest = json.loads(
        (REPO / "data" / "recovered_sources.json").read_text(encoding="utf-8"))
    sources = sorted({r["source"] for r in manifest["functions"]}
                     | {manifest["state_owner"]})
    inc_re = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
    for rel in sources:
        text = (REPO / rel).read_text(encoding="latin-1")
        sub = rel.split("/")[1]
        m = re.search(re.escape(MARK_BEGIN) + r".*?" + re.escape(MARK_END),
                      text, flags=re.DOTALL)
        block_span = m.span() if m else (0, 0)
        for im in inc_re.finditer(text):
            inc = im.group(1)
            inside = block_span[0] <= im.start() < block_span[1]
            base = inc.rsplit("/", 1)[-1]
            if base in FORBIDDEN_UMBRELLA:
                errors.append(f"{rel}: deleted umbrella include returned: {inc}")
            if base == "recovered_all.h":
                errors.append(f"{rel}: tests-only aggregate included in production")
            if not inside and ("recovered_" in inc or "_api.h" in inc
                               or "_internal.h" in inc or "_state.h" in inc):
                errors.append(f"{rel}: recovered include outside generated block: {inc}")
            fm = re.match(r"(?:\.\./)?([a-z]+)/\1_(internal|state)\.h$", inc)
            if fm and fm.group(1) != sub:
                # the state group is the definition site of every global and
                # includes ALL *_state.h slices so definitions stay decl-checked
                if not (sub == "state" and fm.group(2) == "state"):
                    errors.append(f"{rel}: foreign {fm.group(2)} header: {inc}")
    return errors


def surface_metrics() -> dict:
    s = json.loads(SURFACE.read_text(encoding="utf-8"))
    return {
        "api_counts": {k: len(v["api_functions"])
                       for k, v in s["subsystems"].items()},
        "shared_global_count": len(s["shared_globals"]),
        "peer_edges": s["peer_edges"],
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--mode", choices=("check", "update"), default="check")
    args = ap.parse_args()

    ok = True
    if run_gen("--check") != 0:
        print("FRESHNESS: generated headers/surface stale"); ok = False
    if run_gen("--check-tu-includes") != 0:
        print("FRESHNESS: TU include blocks stale"); ok = False

    errors = include_policy_errors()
    for e in errors[:15]:
        print("POLICY:", e)
    if errors:
        ok = False

    cur = surface_metrics()
    if args.mode == "update":
        if not ok:
            print("refusing to update baseline with failures present")
            return 1
        BASELINE.write_text(json.dumps(
            {"schema_version": 1, **cur}, indent=1, sort_keys=True) + "\n",
            encoding="utf-8")
        print(f"updated header-surface baseline -> {BASELINE.relative_to(REPO)}")
        return 0

    if BASELINE.exists():
        base = json.loads(BASELINE.read_text(encoding="utf-8"))
        regressions = []
        for s_, n in cur["api_counts"].items():
            b = base.get("api_counts", {}).get(s_, 0)
            if n > b:
                regressions.append(f"api surface of {s_} grew {b} -> {n}")
        if cur["shared_global_count"] > base.get("shared_global_count", 0):
            regressions.append(
                f"shared globals grew {base.get('shared_global_count')} -> "
                f"{cur['shared_global_count']}")
        for edge, n in cur["peer_edges"].items():
            b = base.get("peer_edges", {}).get(edge, 0)
            if n > b:
                regressions.append(f"peer edge {edge} grew {b} -> {n}")
        for r in regressions[:15]:
            print("RATCHET:", r)
        if regressions:
            print("(a deliberate surface increase re-seeds with --mode update)")
            ok = False
    else:
        print("note: no header-surface baseline; seed with --mode update")

    print(f"header-surface audit: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
