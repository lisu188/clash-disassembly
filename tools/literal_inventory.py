#!/usr/bin/env python3
"""Inventory magic-number literals against tools/constants_manifest.json.

For each manifest constant: count call sites of its value across the canonical
independently compiled sources listed by ``data/recovered_sources.json``,
classified by expression shape (see tools/literal_common.py), with eligibility
per the manifest tier gating. Also reports derived-candidate literals
(base < v <= base + stride for offset/stride pairs) and frequent unmapped
values.

Usage:
  python3 tools/literal_inventory.py                > literal_inventory.json
  python3 tools/literal_inventory.py --full         # include every site
  python3 tools/literal_inventory.py --unmapped 40  # top-N unmapped values
"""
import json
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc


def git_head():
    try:
        return subprocess.check_output(
            ["git", "rev-parse", "HEAD"], cwd=lc.REPO
        ).decode().strip()
    except Exception:
        return "unknown"


def main():
    full = "--full" in sys.argv
    unmapped_top = 40
    if "--unmapped" in sys.argv:
        unmapped_top = int(sys.argv[sys.argv.index("--unmapped") + 1])

    entries, families = lc.load_manifest()
    by_value = {}
    for e in entries:
        if e.get("regex_only"):
            continue  # bit flags etc. are bound to a field, not value-counted
        by_value.setdefault(e["value"], []).append(e)

    # derived-candidate windows: (table offset, record size) per family
    derived_windows = []
    for fam in set(e.get("family") for e in entries):
        fam_entries = [e for e in entries if e.get("family") == fam]
        offsets = [e for e in fam_entries if e.get("kind") == "offset" and e["value"] > 10000]
        strides = [e for e in fam_entries if e.get("kind") == "stride"]
        for off in offsets:
            for st in strides:
                derived_windows.append((off["value"], st["value"], off["name"], st["name"]))

    stats = {
        e["name"]: {
            "name": e["name"], "value": e["value"], "spelling": e["spelling"],
            "tier": e.get("tier"), "family": e.get("family"),
            "deferred": bool(e.get("deferred")), "total": 0,
            "eligible": 0,
            "by_class": {}, "files": {}, "samples": [], "sites": [],
        }
        for e in entries
    }
    wanted = set(by_value)
    derived_hits = {}
    unmapped_counts = {}

    for rel in lc.apply_files():
        path = os.path.join(lc.REPO, rel)
        with open(path, errors="replace") as f:
            text = f.read()
        toks, sites = lc.iter_literal_sites(text)
        fn_lookup, line_of, _fn_range = lc.build_fn_map(text)
        for (idx, value) in sites:
            if value not in wanted:
                if value >= 10:
                    unmapped_counts[value] = unmapped_counts.get(value, 0) + 1
                for (base, stride, bname, sname) in derived_windows:
                    if base < value <= base + stride:
                        key = (value, bname)
                        d = derived_hits.setdefault(
                            key, {"value": value, "base": bname,
                                  "delta": value - base, "count": 0, "samples": []})
                        d["count"] += 1
                        if len(d["samples"]) < 4:
                            d["samples"].append(
                                "%s:%d" % (rel, line_of(toks[idx].start) + 1))
                continue
            for entry in by_value[value]:
                fam_names = families.get(entry.get("family", ""), set())
                cls, info = lc.classify_site(text, toks, idx, entry, fam_names)
                st = stats[entry["name"]]
                st["total"] += 1
                st["by_class"][cls] = st["by_class"].get(cls, 0) + 1
                st["files"][rel] = st["files"].get(rel, 0) + 1
                ok = lc.eligible(cls, info, entry)
                if ok:
                    st["eligible"] += 1
                line = line_of(toks[idx].start) + 1
                site = {
                    "file": rel, "line": line,
                    "fn": fn_lookup(toks[idx].start),
                    "class": cls, "eligible": ok,
                    "raw": toks[idx].text,
                    "expr": (info.get("span") or "")[:160],
                }
                if len(st["samples"]) < 6:
                    st["samples"].append(site)
                if full:
                    st["sites"].append(site)

    out_stats = []
    for e in entries:
        st = stats[e["name"]]
        if not full:
            st.pop("sites")
        out_stats.append(st)
    out_stats.sort(key=lambda s: (-s["total"], s["name"]))

    unmapped = sorted(
        ({"value": v, "count": c} for v, c in unmapped_counts.items() if c >= 8),
        key=lambda d: -d["count"],
    )[:unmapped_top]

    json.dump(
        {
            "commit": git_head(),
            "files": lc.apply_files(),
            "constants": out_stats,
            "derived_candidates": sorted(
                derived_hits.values(), key=lambda d: -d["count"]),
            "unmapped_frequent": unmapped,
        },
        sys.stdout, indent=1,
    )
    sys.stdout.write("\n")


if __name__ == "__main__":
    main()
