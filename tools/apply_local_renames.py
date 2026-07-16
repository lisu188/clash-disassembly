#!/usr/bin/env python3
"""Apply function-scoped parameter/local renames to the recovered Win95 sources.

Unlike apply_renames.py (file/global scope), a1/v37 are function-local: `a1` in
one function is unrelated to `a1` in another. This tool renames such identifiers
ONLY within the byte range of the named function, token-aware (skips strings and
comments so trailing `// reg@n` anchors stay stable).

Input JSON: a list of
  {"file": "src/battle/0042CB50_0042E8B0_battle_001.c",
   "func": "UnitBattle_HandleRetreatAction",
   "renames": {"a1": "unitStack", "v5": "targetTileRow", ...},
   "confidence": "...", "evidence": "..."}
The function identity is resolved through ``data/recovered_sources.json``;
``file`` is retained as review metadata and may be a canonical or historical
path. Only whole-word generated identifiers (a\\d+, v\\d+) are accepted as
`old`, and each `new` must be a valid C identifier that is not already a
generated name. Approved writes refresh the manifest's canonical body hashes.

Usage: apply_local_renames.py mapping.json [mapping2.json ...]
Prints a JSON report. Appends provenance to $LOCAL_RENAME_ACCUM.
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc  # noqa: E402

IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
GEN_LOCAL = re.compile(r"^(a|v)\d+$")
# A function definition: return-type/qualifiers + Name( at column 0, then `{`.
# Non-greedy over type tokens so we capture the function name before the FIRST
# paren, not an inner paren of a function-pointer parameter like BOOL (*a3)(int).
SIG = re.compile(r"^[A-Za-z_][A-Za-z0-9_ \t\*]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


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


def code_identifiers(segment_text):
    """Set of identifier tokens appearing in the CODE (non string/comment) parts."""
    idents = set()
    for is_code, s in lc.split_code_and_literals(segment_text):
        if is_code:
            idents.update(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", s))
    return idents


def drop_collisions(body, mapping):
    """Remove old->new pairs whose NEW name already exists as a distinct identifier
    in the function body (would create a duplicate declaration / shadow). Also drop
    pairs where two olds map to the same new. Returns (clean_mapping, dropped)."""
    existing = code_identifiers(body)
    clean, dropped, targets = {}, [], set()
    for old, new in mapping.items():
        if new in existing and new != old:
            dropped.append((old, new, "target-exists")); continue
        if new in targets:
            dropped.append((old, new, "dup-target")); continue
        targets.add(new)
        clean[old] = new
    return clean, dropped


def scoped_sub(segment_text, mapping):
    pat = re.compile(r"\b(" + "|".join(re.escape(x) for x in mapping) + r")\b")
    segs = lc.split_code_and_literals(segment_text)
    return "".join(
        pat.sub(lambda m: mapping[m.group(1)], s) if is_code else s
        for is_code, s in segs
    )


def main():
    entries = []
    for p in sys.argv[1:]:
        entries.extend(json.load(open(p)))
    manifest = lc.load_source_manifest()
    manifest_by_name = {
        record["name"]: record for record in manifest["functions"]
    }
    by_file = {}
    for e in entries:
        record = manifest_by_name.get(e.get("func"))
        if record is None:
            by_file.setdefault(None, []).append(e)
            continue
        resolved = dict(e)
        resolved["requested_file"] = e.get("file")
        resolved["file"] = record["source"]
        by_file.setdefault(record["source"], []).append(resolved)

    applied = 0
    rejected = []
    accepted_prov = []
    touched = set()
    for f, ents in by_file.items():
        if f is None:
            for e in ents:
                rejected.append(
                    [e.get("file"), e.get("func"),
                     "func absent from source manifest"]
                )
            continue
        path = os.path.join(lc.REPO, f)
        if not os.path.exists(path):
            for e in ents:
                rejected.append([e.get("file"), e.get("func"), "file missing"])
            continue
        text = open(path, errors="replace").read()
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
            m, dropped = drop_collisions(body, m)
            for old, new, why in dropped:
                rejected.append([f, fn, f"collision {old}->{new} ({why})"])
            if not m:
                continue
            newbody = scoped_sub(body, m)
            if newbody != body:
                text = text[:s] + newbody + text[en:]
                applied += 1
                touched.add(f.replace(os.sep, "/"))
                accepted_prov.append({"file": f, "func": fn, "renames": m,
                                      "requested_file": e.get("requested_file"),
                                      "confidence": e.get("confidence", "inferred"),
                                      "evidence": e.get("evidence", "")})
        open(path, "w").write(text)

    refreshed = lc.refresh_source_manifest_body_hashes(touched)
    accum = os.environ.get("LOCAL_RENAME_ACCUM", "/tmp/applied_local_renames.jsonl")
    with open(accum, "a") as fh:
        for e in accepted_prov:
            fh.write(json.dumps(e) + "\n")
    print(json.dumps({"functions_edited": applied,
                      "manifest_body_hashes_refreshed": refreshed,
                      "rejected_count": len(rejected),
                      "rejected_sample": rejected[:10]}, indent=1))


if __name__ == "__main__":
    main()
