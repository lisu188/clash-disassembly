#!/usr/bin/env python3
"""Diagnostic-driven mechanical respeller (P5 warning tranches T4-T6).

Reads `file:line:col: warning: ... [-Wcategory]` sites from a captured CLEAN
FULL build log and applies the category's value-identical respell at each
site, bottom-up per file so positions stay stable:

  int-to-pointer-cast   (T *)intexpr  ->  (T *)(uintptr_t)intexpr
  pointer-to-int-cast   (int)ptrexpr  ->  (int)(intptr_t)ptrexpr

The inserted intermediate cast reproduces the compiler's own implementation-
defined conversion exactly (sign-extension int->pointer, truncation
pointer->int), so object code MUST be identical - verify each batch with
tools/obj_diff_gate.sh. Body tokens change, so manifest hashes are refreshed
(same helper the rename tools use). Sites the parser cannot prove (caret not
at a cast's opening paren, header-attributed / macro-definition sites) are
NEVER force-edited - they go to the review list.

Usage:
  python3 tools/apply_diag_respells.py BUILDLOG \
      --category int-to-pointer-cast [--subsystem battle] [--write]
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc  # noqa: E402

REPO = Path(__file__).resolve().parents[1]

RULES = {
    "int-to-pointer-cast": "(uintptr_t)",
    "pointer-to-int-cast": "(intptr_t)",
    "int-to-void-pointer-cast": "(uintptr_t)",   # clang spelling
    "void-pointer-to-int-cast": "(intptr_t)",    # clang spelling
}

# Annotation categories: caret points at an identifier in its declaration;
# append the attribute macro after the declarator. Codegen-free.
ANNOTATE = {
    "unused-variable": " CLASH95_UNUSED",
    "unused-but-set-variable": " CLASH95_UNUSED",
    "unused-parameter": " CLASH95_UNUSED",
}
IDENT_AT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")

DIAG = re.compile(
    r"^(?P<file>[^:\n\s][^:\n]*):(?P<line>\d+):(?P<col>\d+):\s+warning:.*"
    r"\[-W(?P<cat>[a-z0-9-]+)\]\s*$", re.M)


def collect_sites(log_text: str, categories, subsystem: str | None):
    """rel -> {(line, col): insert}. All requested categories are collected
    TOGETHER so one bottom-up application pass edits each file in a single
    coordinate space - applying category B from a log whose positions predate
    category A's insertions corrupts lines that carry both diagnostics."""
    sites = {}
    for m in DIAG.finditer(log_text):
        cat = m.group("cat")
        if cat not in categories:
            continue
        f = m.group("file").replace("\\", "/")
        idx = f.find("src/")
        if idx == -1:
            continue
        rel = f[idx:]
        if not rel.endswith(".c"):
            continue  # header/macro-definition site -> review separately
        parts = rel.split("/")
        if len(parts) < 3:
            continue
        if subsystem and parts[1] != subsystem:
            continue
        key = (int(m.group("line")), int(m.group("col")))
        prev = sites.setdefault(rel, {}).get(key)
        if prev and prev != {**RULES, **ANNOTATE}[cat]:
            # same site flagged with conflicting rules -> leave for review
            sites[rel][key] = None
        else:
            sites[rel][key] = {**RULES, **ANNOTATE}[cat]
    return sites


def matching_paren(text: str, open_idx: int) -> int:
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


def apply_file(rel: str, positions):
    """positions: {(line, col): insert-or-None}; single bottom-up pass."""
    p = REPO / rel
    raw = p.read_bytes()
    nl = b"\r\n" if b"\r\n" in raw[:4096] else b"\n"
    text = raw.decode("latin-1")
    lines = text.split("\r\n" if nl == b"\r\n" else "\n")
    applied, review = 0, []
    for (line_no, col), insert in sorted(positions.items(), reverse=True):
        if insert is None:
            review.append((line_no, col, "conflicting categories"))
            continue
        if line_no - 1 >= len(lines):
            review.append((line_no, col, "line out of range"))
            continue
        line = lines[line_no - 1]
        i = col - 1
        if insert.startswith(" "):   # annotation rule: caret at identifier
            m = IDENT_AT.match(line, i)
            if not m:
                review.append((line_no, col, "caret not at identifier"))
                continue
            # function-pointer declarators (`void (*v24)(void)`,
            # `void (__fastcall **m)(...)`) cannot take the attribute right
            # after the identifier; if the nearest unclosed paren before the
            # caret contains only stars/convention tokens, leave to review
            stack = []
            for k, ch in enumerate(line[:i]):
                if ch == "(":
                    stack.append(k)
                elif ch == ")" and stack:
                    stack.pop()
            if stack:
                between = line[stack[-1] + 1: i]
                if re.fullmatch(r"[\s\*]*(?:__\w+[\s\*]*)*", between):
                    review.append((line_no, col, "fn-ptr declarator"))
                    continue
            end = m.end()
            # array declarators: the attribute goes AFTER the [...] suffixes
            while end < len(line) and line[end] == "[":
                close_b = line.find("]", end)
                if close_b == -1:
                    break
                end = close_b + 1
            if line[end: end + len(insert)] == insert:
                continue  # idempotent
            lines[line_no - 1] = line[:end] + insert + line[end:]
            applied += 1
            continue
        if i >= len(line) or line[i] != "(":
            review.append((line_no, col, "caret not at cast paren"))
            continue
        close = matching_paren(line, i)
        if close == -1:
            review.append((line_no, col, "unbalanced cast paren"))
            continue
        already = line[close + 1: close + 1 + len(insert)]
        if already == insert:
            continue  # idempotent
        lines[line_no - 1] = line[: close + 1] + insert + line[close + 1:]
        applied += 1
    p.write_bytes(("\r\n" if nl == b"\r\n" else "\n").join(lines)
                  .encode("latin-1"))
    return applied, review


def syntax_check(rels) -> list[str]:
    """gcc -fsyntax-only each touched TU; any failure names a mis-insert."""
    import subprocess
    bad = []
    for rel in rels:
        proc = subprocess.run(
            ["gcc", "-std=gnu17", "-fsyntax-only", "-w",
             "-I", str(REPO / "src"), "-I", str(REPO),
             "-I", str(REPO / "src" / Path(rel).parent.name),
             str(REPO / rel)],
            capture_output=True, text=True, encoding="latin-1",
            cwd=str(REPO / rel).rsplit("/", 1)[0])
        if proc.returncode != 0:
            bad.append(f"{rel}: {proc.stderr.splitlines()[0][:160]}")
    return bad


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("buildlog", type=Path)
    ap.add_argument("--category", required=True, action="append",
                    choices=sorted({**RULES, **ANNOTATE}),
                    help="repeatable; all given categories apply in ONE pass")
    ap.add_argument("--subsystem")
    ap.add_argument("--write", action="store_true")
    ap.add_argument("--report", type=Path)
    args = ap.parse_args()

    cats = set(args.category)
    sites = collect_sites(args.buildlog.read_text(errors="replace"),
                          cats, args.subsystem)
    total = sum(len(v) for v in sites.values())
    print(f"categories {sorted(cats)}: {total} sites in {len(sites)} files"
          + (f" (subsystem {args.subsystem})" if args.subsystem else ""))
    if not args.write:
        print("(dry run)")
        return 0

    grand_applied, grand_review = 0, {}
    for rel in sorted(sites):
        applied, review = apply_file(rel, sites[rel])
        grand_applied += applied
        if review:
            grand_review[rel] = review
    print(f"applied {grand_applied} respells; "
          f"review {sum(map(len, grand_review.values()))} sites")

    bad = syntax_check(sorted(sites))
    if bad:
        for b in bad[:8]:
            print("SYNTAX FAIL:", b)
        print("aborting before hash refresh - revert with git checkout -- src")
        return 1

    touched = sorted(sites)
    refreshed = lc.refresh_source_manifest_body_hashes(set(touched))
    print(f"manifest body hashes refreshed: {refreshed}")

    if args.report:
        args.report.write_text(json.dumps({
            "categories": sorted(cats), "applied": grand_applied,
            "review": {k: [list(x) for x in v] for k, v in grand_review.items()},
        }, indent=1), encoding="utf-8")
        print(f"report -> {args.report}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
