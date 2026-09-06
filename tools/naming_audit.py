#!/usr/bin/env python3
"""Reproducible naming audit for clash-disassembly.

Counts remaining opaque/generated identifiers in the canonical recovered
GNU C17 translation units from ``data/recovered_sources.json``, plus current
bootstrap/platform/instrumentation support sources, so the
semantic-naming campaign's definition-of-done can be verified mechanically.

Kinds counted (distinct where noted):
  func_sub      : sub_<hex> used as a function name  (definitions / declarations)
  global_*      : dword_/word_/byte_/qword_/off_/unk_/dbl_/flt_ distinct symbols
  param_aN      : positional parameters a1,a2,... in function signatures (occurrences)
  local_vN      : generated locals v1,v2,... in bodies (occurrences)

Legacy identifiers that appear ONLY inside line/# comments or string literals are not
counted as unresolved code identifiers.

Usage:
  python tools/naming_audit.py               # human summary
  python tools/naming_audit.py --json out.json
  python tools/naming_audit.py --literals    # add magic-literal counts
                                             # (tools/constants_manifest.json)
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
from global_inventory import recovered_source_files  # noqa: E402

GLOBAL_PREFIXES = ["dword_", "word_", "byte_", "qword_", "off_", "unk_", "dbl_", "flt_", "loc_"]

def strip_noncode(line):
    """Remove // comments and string/char literals so we count code identifiers only."""
    # drop // comment
    q = line.find("//")
    if q != -1:
        line = line[:q]
    # remove string and char literals (best-effort, no nested escapes handling needed for counts)
    line = re.sub(r'"(?:[^"\\]|\\.)*"', '""', line)
    line = re.sub(r"'(?:[^'\\]|\\.)*'", "''", line)
    return line

def in_block_comment_split(text):
    """Yield code-only lines with /* */ block comments removed."""
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.DOTALL)
    return text.split("\n")

FUNC_MARKER = re.compile(r'^//----- \(([0-9A-Fa-f]+)\)')
SUBNAME = re.compile(r'\bsub_[0-9A-F]+\b')
PARAM = re.compile(r'\ba\d+\b')
LOCAL = re.compile(r'\bv\d+\b')

def audit_file(path):
    """Return dict of counts for one source file (code-only)."""
    raw = open(path, encoding="latin-1", errors="replace").read()
    lines = in_block_comment_split(raw)
    res = {"func_sub_defs": 0, "func_sub_tokens": set(),
           "globals": {p: set() for p in GLOBAL_PREFIXES},
           "param_aN": 0, "local_vN": 0}
    global_res = {p: re.compile(r'\b'+p+r'[0-9A-F]+\b') for p in GLOBAL_PREFIXES}
    prev_marker = False
    for ln in lines:
        code = strip_noncode(ln)
        if not code.strip():
            continue
        # function definitions: a marker line then a signature; count sub_ names as defs
        for m in SUBNAME.finditer(code):
            res["func_sub_tokens"].add(m.group(0))
        for p, rx in global_res.items():
            for m in rx.finditer(code):
                res["globals"][p].add(m.group(0))
        res["param_aN"] += len(PARAM.findall(code))
        res["local_vN"] += len(LOCAL.findall(code))
    return res

def merge(a, b):
    a["func_sub_tokens"] |= b["func_sub_tokens"]
    for p in GLOBAL_PREFIXES:
        a["globals"][p] |= b["globals"][p]
    a["param_aN"] += b["param_aN"]
    a["local_vN"] += b["local_vN"]
    return a

def blank():
    return {"func_sub_tokens": set(), "globals": {p: set() for p in GLOBAL_PREFIXES},
            "param_aN": 0, "local_vN": 0}

def summarize(res):
    return {"func_sub_distinct": len(res["func_sub_tokens"]),
            "globals_distinct": {p: len(res["globals"][p]) for p in GLOBAL_PREFIXES},
            "globals_distinct_total": sum(len(res["globals"][p]) for p in GLOBAL_PREFIXES),
            "param_aN_occurrences": res["param_aN"],
            "local_vN_occurrences": res["local_vN"]}

def audit_literals():
    """Magic-literal progress counts (tools/constants_manifest.json values,
    canonical manifest sources only -- see tools/literal_common.py)."""
    sys.path.insert(0, os.path.join(REPO, "tools"))
    import literal_common as lc
    entries, families = lc.load_manifest()
    by_value = {}
    for e in entries:
        # regex_only constants (e.g. bit flags) are meaningful only bound to a
        # specific field, not as bare values; a value census over them would
        # count every unrelated 1/2/4/8 occurrence, so skip them here.
        if e.get("regex_only"):
            continue
        by_value.setdefault(e["value"], []).append(e)
    per_value = {}
    total_eligible = total_review = 0
    for rel in lc.apply_files():
        with open(os.path.join(REPO, rel), errors="replace") as f:
            text = f.read()
        toks, sites = lc.iter_literal_sites(text, set(by_value))
        for (idx, value) in sites:
            for e in by_value[value]:
                fam = families.get(e.get("family", ""), set())
                cls, info = lc.classify_site(text, toks, idx, e, fam)
                d = per_value.setdefault(
                    e["name"], {"value": value, "eligible": 0, "review": 0})
                if lc.eligible(cls, info, e):
                    d["eligible"] += 1
                    total_eligible += 1
                else:
                    d["review"] += 1
                    total_review += 1
    return {"total_eligible": total_eligible, "total_review": total_review,
            "per_value": {k: per_value[k] for k in sorted(per_value)}}


def main():
    out = {}
    support = (
        "src/bootstrap/bootstrap_main.c",
        "src/platform/platform_sdl_runtime.c",
        "src/instrumentation/runtime_mission_trace.c",
    )
    support += tuple(path[:-2] + ".cpp" for path in support)
    win_files = [os.path.join(REPO, rel) for rel in recovered_source_files()]
    win_files.extend(os.path.join(REPO, rel) for rel in support)
    win_files = [f for f in win_files if os.path.exists(f)]
    win = blank(); per_win = {}
    for f in win_files:
        r = audit_file(f); per_win[os.path.relpath(f, REPO)] = summarize(r); merge(win, r)
    out["win95"] = {"total": summarize(win), "per_file": per_win, "file_count": len(win_files)}
    if "--literals" in sys.argv:
        out["win95"]["magic_literals"] = audit_literals()

    if "--json" in sys.argv:
        p = sys.argv[sys.argv.index("--json") + 1]
        json.dump(out, open(p, "w"), indent=1)
        print("wrote", p)
    # human summary
    w = out["win95"]["total"]
    print("=== WIN95 track (clash95 src, %d files) ===" % out["win95"]["file_count"])
    print("  opaque function names (sub_):", w["func_sub_distinct"])
    print("  generated globals (distinct):", w["globals_distinct_total"], w["globals_distinct"])
    print("  positional params (a1..) occurrences:", w["param_aN_occurrences"])
    print("  generated locals (v1..) occurrences: ", w["local_vN_occurrences"])
    ml = out["win95"].get("magic_literals")
    if ml:
        print("  magic literals: eligible-unreplaced:", ml["total_eligible"],
              " review-only:", ml["total_review"])

if __name__ == "__main__":
    main()
