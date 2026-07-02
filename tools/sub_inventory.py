#!/usr/bin/env python3
"""Inventory sub_XXXXXX placeholder functions in clash95.c.

Emits JSON with, per sub_ symbol: definition line range, body size,
callees, callers, and nearby string literals — the raw material for
evidence-based semantic renaming.
"""
import json
import re
import sys

SRC = "clash95.c"
SUB = re.compile(r"\bsub_[0-9A-F]{6}\b")
# A definition line: return type at column 0 on same or previous line, name(...) then '{'
DEF_LINE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ *]*\b(sub_[0-9A-F]{6})\s*\(")
IDENT = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
STRLIT = re.compile(r'"((?:[^"\\]|\\.){3,120})"')


def main():
    with open(SRC, "r", errors="replace") as f:
        lines = f.readlines()

    # Find all function definitions (any name) to bound bodies.
    # Heuristic: a def starts at a line matching `^\w.*\bNAME(` and the body is
    # brace-balanced starting from the first '{' at column 0 or end of signature.
    defs = []  # (name, start_line_idx)
    for i, ln in enumerate(lines):
        m = re.match(r"^[A-Za-z_][A-Za-z0-9_ *]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", ln)
        if not m:
            continue
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "return", "sizeof"):
            continue
        # must eventually be followed by '{' before ';' (definition, not decl)
        j = i
        depth_paren = 0
        is_def = False
        scanned = 0
        while j < len(lines) and scanned < 60:
            s = lines[j]
            for ch in s:
                if ch == "(":
                    depth_paren += 1
                elif ch == ")":
                    depth_paren -= 1
                elif ch == ";" and depth_paren <= 0:
                    j = len(lines)
                    break
                elif ch == "{" and depth_paren <= 0:
                    is_def = True
                    break
            if is_def or j >= len(lines):
                break
            j += 1
            scanned += 1
        if is_def:
            defs.append((name, i))

    # bound each body by next def start
    inventory = {}
    all_names = set(n for n, _ in defs)
    callers = {}
    for k, (name, start) in enumerate(defs):
        end = defs[k + 1][1] if k + 1 < len(defs) else len(lines)
        body = "".join(lines[start:end])
        callees = sorted(set(IDENT.findall(body)) & all_names - {name})
        for c in callees:
            callers.setdefault(c, set()).add(name)
        if SUB.fullmatch(name):
            strings = STRLIT.findall(body)[:8]
            inventory[name] = {
                "line": start + 1,
                "end": end,
                "size_lines": end - start,
                "callees": callees,
                "strings": strings,
                "signature": lines[start].strip(),
            }

    for name, info in inventory.items():
        info["callers"] = sorted(callers.get(name, set()))

    # sub_ symbols referenced but never defined in clash95.c
    text = "".join(lines)
    referenced = set(SUB.findall(text))
    undefined = sorted(referenced - set(inventory))

    out = {
        "defined": inventory,
        "undefined_refs": undefined,
        "counts": {
            "defined": len(inventory),
            "undefined_refs": len(undefined),
            "total_unique": len(referenced),
        },
    }
    json.dump(out, sys.stdout, indent=1)


if __name__ == "__main__":
    main()
