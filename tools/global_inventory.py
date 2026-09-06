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

from split_source_index import mask_c, scan_definitions
from recovered_implementation import manifest_sources, manifest_targets

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCE_MANIFEST = os.path.join(REPO, "data", "recovered_sources.json")
GLOBAL_RE = re.compile(
    r"\b((?:dword|byte|word|off|unk|flt|dbl|qword|xmmword)_[0-9A-F]{4,})\b"
)
DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ *\[\]]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")


def load_source_manifest(path=SOURCE_MANIFEST):
    with open(path, encoding="utf-8") as stream:
        document = json.load(stream)
    if document.get("schema_version") not in (2, 3):
        raise ValueError("recovered source manifest must use schema_version 2 or 3")
    functions = document.get("functions")
    if not isinstance(functions, list):
        raise ValueError("recovered source manifest has no function list")
    return document


def recovered_source_files(document=None):
    """Return canonical manifest-owned C/C++ files in stable path order."""
    document = document or load_source_manifest()
    sources = manifest_sources(document)
    missing = [source for source in sorted(sources)
               if not os.path.isfile(os.path.join(REPO, source))]
    if missing:
        raise ValueError("canonical source files are missing: %s" % ", ".join(missing))
    return sorted(sources)


def find_defs(lines):
    """Return qualified definitions and zero-based lines, including helpers."""
    return [(definition.name, definition.line - 1)
            for definition in scan_definitions("".join(lines), None)]


def main():
    info = {}
    document = load_source_manifest()
    sources = recovered_source_files(document)
    identity_names = {target.name: target.identity for target in manifest_targets(document)}
    for rel in sources:
        with open(os.path.join(REPO, rel), errors="replace") as stream:
            lines = stream.readlines()
        text = "".join(lines)
        code_lines = mask_c(text).splitlines(keepends=True)
        defs = scan_definitions(text, None)
        fn_at = [None] * (len(lines) + 1)
        for definition in defs:
            end = text.count("\n", 0, definition.end) + 1
            for line_index in range(definition.line - 1, end):
                fn_at[line_index] = identity_names.get(definition.name, definition.name)

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
