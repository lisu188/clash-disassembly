#!/usr/bin/env python3
"""Reproducible naming audit for clash-disassembly.

Counts remaining opaque / generated identifiers across both recovery tracks so the
semantic-naming campaign's definition-of-done can be verified mechanically.

Tracks:
  win95  -> the recovered Win95 source (clash95.c aggregator + src/**/*.inc.c fragments,
            plus bootstrap_main.c / platform_sdl_runtime.c / runtime_mission_trace.c)
  dos    -> the DOS Hex-Rays dump (clash.c). NOTE: clash.c is a *generated* artifact;
            durable DOS names live in tools/dos/dos_master_map.json and are applied via
            regeneration, so the DOS function/global audit is reported against BOTH the
            generated text and the master map (source of truth).

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
"""
import re, os, sys, json, glob

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

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

def main():
    out = {}
    # WIN95 track: aggregator fragments + standalone runtime/platform C
    win_files = (glob.glob(os.path.join(REPO, "src", "**", "*.inc.c"), recursive=True)
                 + [os.path.join(REPO, f) for f in
                    ("bootstrap_main.c", "platform_sdl_runtime.c", "runtime_mission_trace.c")])
    win_files = [f for f in win_files if os.path.exists(f)]
    win = blank(); per_win = {}
    for f in win_files:
        r = audit_file(f); per_win[os.path.relpath(f, REPO)] = summarize(r); merge(win, r)
    out["win95"] = {"total": summarize(win), "per_file": per_win, "file_count": len(win_files)}

    # DOS track: generated clash.c (text) + master-map coverage
    dos_c = os.path.join(REPO, "clash.c")
    dos = audit_file(dos_c) if os.path.exists(dos_c) else blank()
    # master map = durable DOS names (source of truth). Count named vs total functions.
    mm = os.path.join(REPO, "tools", "dos", "dos_master_map.json")
    named = 0
    if os.path.exists(mm):
        named = len(json.load(open(mm)))
    total_funcs = len(re.findall(r'(?m)^//----- \(', open(dos_c, encoding="latin-1").read())) if os.path.exists(dos_c) else 0
    out["dos"] = {"generated_text": summarize(dos),
                  "master_map_named_functions": named,
                  "total_functions": total_funcs,
                  "unnamed_functions": total_funcs - named}

    if "--json" in sys.argv:
        p = sys.argv[sys.argv.index("--json") + 1]
        json.dump(out, open(p, "w"), indent=1)
        print("wrote", p)
    # human summary
    w = out["win95"]["total"]; d = out["dos"]
    print("=== WIN95 track (clash95 src, %d files) ===" % out["win95"]["file_count"])
    print("  opaque function names (sub_):", w["func_sub_distinct"])
    print("  generated globals (distinct):", w["globals_distinct_total"], w["globals_distinct"])
    print("  positional params (a1..) occurrences:", w["param_aN_occurrences"])
    print("  generated locals (v1..) occurrences: ", w["local_vN_occurrences"])
    print("=== DOS track (clash.c generated + master map) ===")
    print("  total functions:", d["total_functions"], "| named in master map:", d["master_map_named_functions"],
          "| unnamed:", d["unnamed_functions"])
    print("  generated-text globals (distinct):", d["generated_text"]["globals_distinct_total"])
    print("  generated-text params/locals:", d["generated_text"]["param_aN_occurrences"], "/", d["generated_text"]["local_vN_occurrences"])

if __name__ == "__main__":
    main()
