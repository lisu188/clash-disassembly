#!/usr/bin/env python3
"""T1 warning tranche: give zero-argument recovered functions real prototypes.

`int Foo();` (unspecified args, K&R-era) fires -Wstrict-prototypes once per
including TU; with 138 TUs the ~600 empty-paren declarations in
src/recovered_foundation.h account for the bulk of the entire recovered warning
baseline. For every function whose DEFINITION is old-style zero-argument
(`int Foo()` with an empty parameter list), this tool rewrites both the header
declaration and the definition to `(void)`.

Strictly definition-derived: a declaration is rewritten ONLY when the manifest
locates exactly one definition and that definition itself has empty parens.
Nothing is inferred; no parameters are ever invented. Function-pointer
declarations (`int (*g_X)();`) and names without a manifest definition (legacy
imports — a later tranche) are skipped and reported.

Identity: the edit changes tokens only in signature/declaration positions —
manifest body hashes (opening brace onward) are untouched, and at -O0 the
generated code for a no-argument call/definition is identical, so
obj_diff_gate.sh must report byte-identical disassembly. A pp_token --allow
plan (`[")"] -> ["void", ")"]` pairs) is emitted for the token gate.

Usage:
  python3 tools/gen_void_prototypes.py                  # dry-run report
  python3 tools/gen_void_prototypes.py --write \
      --allow-plan plans/pp_allow/t1_void_prototypes.json \
      [--exclude NAME ...]                              # apply
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
FOUNDATION = REPO / "src" / "recovered_foundation.h"
MANIFEST = REPO / "data" / "recovered_sources.json"

NAME_RE = r"[A-Za-z_][A-Za-z0-9_]*"


def decl_candidates(text: str):
    """Yield (line_idx, name) for plain empty-paren prototypes (no fn-ptrs)."""
    for i, line in enumerate(text.split("\n")):
        stripped = line.strip()
        if not stripped or stripped.startswith(("//", "/*", "#")):
            continue
        # plain decl: ... Name ( ) ; with no '*' immediately inside the parens
        m = re.match(
            rf"^(?:extern\s+)?[A-Za-z_][\w\s\*]*?\b({NAME_RE})\s*\(\s*\)\s*;",
            stripped,
        )
        if not m:
            continue
        if re.search(r"\(\s*\*", stripped):  # function-pointer decl
            continue
        yield i, m.group(1)


def find_definition(src_text: str, name: str):
    """Return (line_idx, line) of the unique old-style zero-arg definition.

    A definition line is column-0-anchored `... Name()` whose statement opens a
    body: the line ends with `)` or `) {`-style and the following non-blank
    line starts the body with `{` (or the brace is on the same line).
    Returns None when not found; raises ValueError when ambiguous.
    """
    lines = src_text.split("\n")
    hits = []
    pat = re.compile(rf"^[A-Za-z_][\w\s\*]*?\b{re.escape(name)}\s*\(\s*\)\s*(\{{)?\s*$")
    for i, line in enumerate(lines):
        code = line.split("//")[0].rstrip()
        m = pat.match(code)
        if not m:
            continue
        if m.group(1):  # brace on same line
            hits.append(i)
            continue
        j = i + 1
        while j < len(lines) and not lines[j].strip():
            j += 1
        if j < len(lines) and lines[j].lstrip().startswith("{"):
            hits.append(i)
    if not hits:
        return None
    if len(hits) > 1:
        raise ValueError(f"{name}: {len(hits)} zero-arg definition-like lines")
    return hits[0], lines[hits[0]]


def rewrite_empty_parens(line: str, name: str) -> str:
    """Rewrite the first `Name(<spaces>)` on the line to `Name(void)`."""
    out, n = re.subn(
        rf"(\b{re.escape(name)}\s*\(\s*)\)", r"\1void)", line, count=1
    )
    if n != 1:
        raise ValueError(f"could not rewrite parens for {name!r} in: {line!r}")
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--write", action="store_true", help="apply edits")
    ap.add_argument("--allow-plan", type=Path,
                    help="emit pp_token_gate --allow plan here")
    ap.add_argument("--exclude", nargs="*", default=[],
                    help="function names to skip (build-error quarantine)")
    ap.add_argument("--report", type=Path, help="write JSON report here")
    args = ap.parse_args()
    excluded = set(args.exclude)

    if not FOUNDATION.exists():
        print("historical tool (T1 executed pre-P3.6): the foundation header "
              "was deleted at the P3 narrowing; future prototype tranches "
              "edit data/recovered_decls.json and regenerate instead.")
        return 0

    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    by_name = {}
    for rec in manifest["functions"]:
        by_name.setdefault(rec["name"], []).append(rec)

    foundation_bytes = FOUNDATION.read_bytes()
    newline = b"\r\n" if b"\r\n" in foundation_bytes[:4096] else b"\n"
    foundation = foundation_bytes.decode("latin-1")
    flines = foundation.split("\n")

    rewritten = []          # (name, decl_line_idx, source, def_line_idx)
    skipped = {}            # name -> reason
    per_source_edits = {}   # source path -> list of (line_idx, name)

    for line_idx, name in decl_candidates(foundation):
        if name in excluded:
            skipped[name] = "excluded (quarantined)"
            continue
        recs = by_name.get(name)
        if not recs:
            skipped[name] = "no manifest definition (legacy import; later tranche)"
            continue
        if len(recs) > 1:
            skipped[name] = "multiple manifest records"
            continue
        src = REPO / recs[0]["source"]
        src_text = src.read_text(encoding="latin-1")
        try:
            found = find_definition(src_text, name)
        except ValueError as exc:
            skipped[name] = f"ambiguous: {exc}"
            continue
        if found is None:
            skipped[name] = "definition is not old-style zero-arg"
            continue
        def_idx, _def_line = found
        rewritten.append((name, line_idx, recs[0]["source"], def_idx))
        per_source_edits.setdefault(recs[0]["source"], []).append((def_idx, name))

    print(f"candidates rewritten: {len(rewritten)}; skipped: {len(skipped)}")
    for name, reason in sorted(skipped.items()):
        print(f"  skip {name}: {reason}")

    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(json.dumps({
            "rewritten": [
                {"name": n, "decl_line": d + 1, "source": s, "def_line": f + 1}
                for n, d, s, f in rewritten
            ],
            "skipped": skipped,
        }, indent=1, sort_keys=True), encoding="utf-8")
        print(f"report -> {args.report}")

    if args.allow_plan:
        # one ')' -> 'void' ')' pair per edit site (decl + definition)
        pairs = [[[")"], ["void", ")"]]] * (len(rewritten) * 2)
        args.allow_plan.parent.mkdir(parents=True, exist_ok=True)
        args.allow_plan.write_text(json.dumps(
            {"entries": [{"pp_allow": p} for p in pairs]}, indent=None
        ), encoding="utf-8")
        print(f"allow plan ({len(pairs)} pairs) -> {args.allow_plan}")

    if not args.write:
        print("(dry run -- nothing written; pass --write to apply)")
        return 0

    # apply header edits
    for name, line_idx, _src, _def_idx in rewritten:
        flines[line_idx] = rewrite_empty_parens(flines[line_idx], name)
    FOUNDATION.write_bytes("\n".join(flines).encode("latin-1"))

    # apply definition edits, grouped per file
    for src_rel, edits in per_source_edits.items():
        p = REPO / src_rel
        text = p.read_text(encoding="latin-1")
        lines = text.split("\n")
        for def_idx, name in edits:
            lines[def_idx] = rewrite_empty_parens(lines[def_idx], name)
        p.write_text("\n".join(lines), encoding="latin-1", newline="")

    print(f"applied: {len(rewritten)} decl+definition pairs "
          f"across {1 + len(per_source_edits)} files")
    return 0


if __name__ == "__main__":
    sys.exit(main())
