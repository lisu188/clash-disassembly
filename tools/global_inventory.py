#!/usr/bin/env python3
"""Inventory machine-named globals in the canonical recovered split sources.

For each dword_/byte_/word_/off_/unk_/flt_/dbl_/qword_ symbol: capture its
declaration line (type + initializer), and up to N usage sites with the
enclosing function name, so agents can propose evidence-based names.

The implementation source set comes exclusively from
``data/recovered_sources.json``; the temporary unified oracle and legacy
``.inc.c`` fragments are never scanned.

Emits JSON: {"globals": [{name, decl, decl_file, decl_line, count,
users:[fn...], samples:[lines]}], ...}
"""
import json
import os
import re
import sys

from split_source_index import mask_c

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCE_MANIFEST = os.path.join(REPO, "data", "recovered_sources.json")
GLOBAL_RE = re.compile(
    r"\b((?:dword|byte|word|off|unk|flt|dbl|qword|xmmword)_[0-9A-F]{4,})\b"
)
DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ *\[\]]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


def load_source_manifest(path=SOURCE_MANIFEST):
    with open(path, encoding="utf-8") as stream:
        document = json.load(stream)
    if document.get("schema_version") != 2:
        raise ValueError("recovered source manifest must use schema_version 2")
    functions = document.get("functions")
    if not isinstance(functions, list):
        raise ValueError("recovered source manifest has no function list")
    return document


def recovered_source_files(document=None):
    """Return canonical manifest-owned C files in stable path order."""
    document = document or load_source_manifest()
    sources = {record.get("source") for record in document["functions"]}
    state_owner = document.get("state_owner")
    if state_owner:
        sources.add(state_owner)
    invalid = sorted(
        source for source in sources
        if not isinstance(source, str) or not source.endswith(".c")
    )
    if invalid:
        raise ValueError("invalid canonical source paths: %r" % invalid)
    missing = [source for source in sorted(sources)
               if not os.path.isfile(os.path.join(REPO, source))]
    if missing:
        raise ValueError("canonical source files are missing: %s" % ", ".join(missing))
    return sorted(sources)


def find_defs(lines):
    lines = mask_c("".join(lines)).splitlines(keepends=True)
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
    info = {}
    sources = recovered_source_files()
    for rel in sources:
        with open(os.path.join(REPO, rel), errors="replace") as stream:
            lines = stream.readlines()
        code_lines = mask_c("".join(lines)).splitlines(keepends=True)
        defs = find_defs(code_lines)
        fn_at = [None] * (len(lines) + 1)
        for k, (name, start) in enumerate(defs):
            end = defs[k + 1][1] if k + 1 < len(defs) else len(lines)
            for line_index in range(start, end):
                fn_at[line_index] = name

        for i, (ln, code_line) in enumerate(zip(lines, code_lines)):
            for match in GLOBAL_RE.finditer(code_line):
                name = match.group(1)
                data = info.setdefault(
                    name,
                    {"name": name, "decl": "", "decl_file": "",
                     "decl_line": 0, "count": 0, "users": set(), "samples": []},
                )
                data["count"] += 1
                stripped = ln.strip()
                code_part = code_line
                decl_pattern = re.compile(
                    r"^(?:CLASH95_[A-Z_]+\s+)?[A-Za-z_][A-Za-z0-9_ *]*\b"
                    + re.escape(name) + r"\b\s*(\[[^\]]*\])?\s*(=|;)"
                )
                is_decl = (
                    ln[:1] not in (" ", "\t")
                    and decl_pattern.search(code_line) is not None
                    and name in code_part
                )
                if is_decl and not data["decl"]:
                    data["decl"] = stripped[:200]
                    data["decl_file"] = rel
                    data["decl_line"] = i + 1
                function = fn_at[i]
                if function:
                    data["users"].add(function)
                    if len(data["samples"]) < 6:
                        data["samples"].append(
                            f"{rel}:{function}:{i + 1}: {stripped[:140]}"
                        )

    out = []
    for g, d in info.items():
        d["users"] = sorted(d["users"])[:15]
        out.append(d)
    out.sort(key=lambda d: -d["count"])
    json.dump(
        {"source_manifest": "data/recovered_sources.json",
         "source_count": len(sources), "globals": out, "count": len(out)},
        sys.stdout,
        indent=1,
    )


if __name__ == "__main__":
    main()
