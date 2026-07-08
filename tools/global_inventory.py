#!/usr/bin/env python3
"""Inventory machine-named globals in clash95.c for the rename campaign.

For each dword_/byte_/word_/off_/unk_/flt_/dbl_/qword_ symbol: capture its
declaration line (type + initializer), and up to N usage sites with the
enclosing function name, so agents can propose evidence-based names.

Emits JSON: {"globals": [{name, decl, decl_line, count, users:[fn...],
samples:[lines]}], ...}
"""
import json
import re
import sys

SRC = "clash95.c"
GLOBAL_RE = re.compile(
    r"\b((?:dword|byte|word|off|unk|flt|dbl|qword|xmmword)_[0-9A-F]{4,})\b"
)
DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ *\[\]]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


def find_defs(lines):
    defs = []
    for i, ln in enumerate(lines):
        m = re.match(r"^[A-Za-z_][A-Za-z0-9_ *]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", ln)
        if not m:
            continue
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "return", "sizeof"):
            continue
        j = i
        depth = 0
        isdef = False
        sc = 0
        while j < len(lines) and sc < 60:
            done = False
            for ch in lines[j]:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                elif ch == ";" and depth <= 0:
                    done = True
                    break
                elif ch == "{" and depth <= 0:
                    isdef = True
                    done = True
                    break
            if done:
                break
            j += 1
            sc += 1
        if isdef:
            defs.append((name, i))
    return defs


def main():
    lines = open(SRC, errors="replace").readlines()
    defs = find_defs(lines)
    # map line -> enclosing function
    fn_at = [None] * (len(lines) + 1)
    for k, (name, start) in enumerate(defs):
        end = defs[k + 1][1] if k + 1 < len(defs) else len(lines)
        for ln in range(start, end):
            fn_at[ln] = name

    info = {}
    for i, ln in enumerate(lines):
        for m in GLOBAL_RE.finditer(ln):
            g = m.group(1)
            d = info.setdefault(
                g, {"name": g, "decl": "", "decl_line": 0, "count": 0,
                    "users": set(), "samples": []}
            )
            d["count"] += 1
            # a file-scope declaration: line begins at column 0 with a type,
            # names g, then ends in ';' or has an initializer '='. The IDA
            # "// weak" trailer is a strong confirmation.
            stripped = ln.strip()
            code_part = ln.split("//")[0]
            decl_pat = re.compile(
                r"^[A-Za-z_][A-Za-z0-9_ *]*\b" + re.escape(g) + r"\b\s*(\[[^\]]*\])?\s*(=|;)"
            )
            # file-scope decls in this file start at column 0 (no indent).
            is_decl = (
                ln[:1] not in (" ", "\t")
                and (decl_pat.search(ln) is not None)
                and g in code_part
            )
            if is_decl and not d["decl"]:
                d["decl"] = stripped[:200]
                d["decl_line"] = i + 1
            fn = fn_at[i]
            if fn:
                d["users"].add(fn)
                if len(d["samples"]) < 6:
                    d["samples"].append(f"{fn}:{i+1}: {stripped[:140]}")

    out = []
    for g, d in info.items():
        d["users"] = sorted(d["users"])[:15]
        out.append(d)
    out.sort(key=lambda d: -d["count"])
    json.dump({"globals": out, "count": len(out)}, sys.stdout, indent=1)


if __name__ == "__main__":
    main()
