#!/usr/bin/env python3
"""Apply function-scoped parameter/local renames to the recovered Win95 sources.

Unlike apply_renames.py (file/global scope), a1/v37 are function-local: `a1` in
one function is unrelated to `a1` in another. This tool renames such identifiers
ONLY within the byte range of the named function, token-aware (skips strings and
comments so trailing `// reg@n` anchors stay stable).

Input JSON: a list of
  {"file": "src/game/070_battle.inc.c",
   "func": "UnitBattle_HandleRetreatAction",
   "renames": {"a1": "unitStack", "v5": "targetTileRow", ...},
   "confidence": "...", "evidence": "..."}
Only whole-word generated identifiers (a\\d+, v\\d+) are accepted as `old`, and
each `new` must be a valid C identifier that is not already a generated name.

Usage: apply_local_renames.py mapping.json [mapping2.json ...]
Prints a JSON report. Appends provenance to $LOCAL_RENAME_ACCUM.
"""
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from apply_sub_renames import split_code_and_literals  # noqa: E402

IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
GEN_LOCAL = re.compile(r"^(a|v)\d+$")
# A function definition: return-type/qualifiers + Name(...) at column 0, then `{`.
SIG = re.compile(r"^[A-Za-z_].*\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


def find_functions(text):
    """Return {func_name: (body_start_idx, body_end_idx)} spanning sig..matching }."""
    lines = text.splitlines(keepends=True)
    # byte offset of each line start
    offs, o = [], 0
    for ln in lines:
        offs.append(o)
        o += len(ln)
    funcs = {}
    i = 0
    n = len(lines)
    while i < n:
        ln = lines[i]
        m = SIG.match(ln)
        if m and not ln.lstrip().startswith(("//", "*", "/*")) and ";" not in ln.split("//")[0]:
            # find the opening brace line (this line or subsequent, before another sig)
            j = i
            while j < n and "{" not in lines[j]:
                if j > i and (lines[j].strip() == "" or SIG.match(lines[j])):
                    break
                j += 1
            if j < n and "{" in lines[j] and lines[j].startswith("{"):
                # brace-match from here
                depth = 0
                k = j
                started = False
                while k < n:
                    depth += lines[k].count("{") - lines[k].count("}")
                    if lines[k].count("{"):
                        started = True
                    if started and depth <= 0:
                        break
                    k += 1
                if k < n:
                    funcs[m.group(1)] = (offs[i], offs[k] + len(lines[k]))
                    i = k + 1
                    continue
        i += 1
    return funcs


def scoped_sub(segment_text, mapping):
    pat = re.compile(r"\b(" + "|".join(re.escape(x) for x in mapping) + r")\b")
    segs = split_code_and_literals(segment_text)
    return "".join(
        pat.sub(lambda m: mapping[m.group(1)], s) if is_code else s
        for is_code, s in segs
    )


def main():
    entries = []
    for p in sys.argv[1:]:
        entries.extend(json.load(open(p)))
    by_file = {}
    for e in entries:
        by_file.setdefault(e["file"], []).append(e)

    applied = 0
    rejected = []
    accepted_prov = []
    for f, ents in by_file.items():
        if not os.path.exists(f):
            for e in ents:
                rejected.append([e.get("file"), e.get("func"), "file missing"])
            continue
        text = open(f, errors="replace").read()
        funcs = find_functions(text)
        # apply from last function to first so byte ranges stay valid
        edits = []
        for e in ents:
            fn = e["func"]
            if fn not in funcs:
                rejected.append([f, fn, "func not found"])
                continue
            m = {}
            for old, new in e["renames"].items():
                if not GEN_LOCAL.match(old):
                    rejected.append([f, fn, f"bad old {old}"]); continue
                if not IDENT.match(new) or GEN_LOCAL.match(new) or re.match(r"^(sub|dword|byte|word|off|unk)_", new):
                    rejected.append([f, fn, f"bad new {new}"]); continue
                m[old] = new
            if m:
                edits.append((funcs[fn][0], funcs[fn][1], m, fn, e))
        edits.sort(key=lambda x: x[0], reverse=True)
        for s, en, m, fn, e in edits:
            body = text[s:en]
            newbody = scoped_sub(body, m)
            if newbody != body:
                text = text[:s] + newbody + text[en:]
                applied += 1
                accepted_prov.append({"file": f, "func": fn, "renames": m,
                                      "confidence": e.get("confidence", "inferred"),
                                      "evidence": e.get("evidence", "")})
        open(f, "w").write(text)

    accum = os.environ.get("LOCAL_RENAME_ACCUM", "/tmp/applied_local_renames.jsonl")
    with open(accum, "a") as fh:
        for e in accepted_prov:
            fh.write(json.dumps(e) + "\n")
    print(json.dumps({"functions_edited": applied, "rejected_count": len(rejected),
                      "rejected_sample": rejected[:10]}, indent=1))


if __name__ == "__main__":
    main()
