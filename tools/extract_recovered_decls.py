#!/usr/bin/env python3
"""Extract the canonical recovered declaration database (P3.2).

Reads the two declaration umbrellas:
  - src/recovered_foundation.h : extern globals + function prototypes
  - src/recovered_functions.h  : legacy import decls, normalized internal
    prototypes, and the CLASH95_TESTING test-seam block

and emits data/recovered_decls.json (schema 1) — the single, hand-editable
home of every declaration's EXACT text, keyed by symbol name:

  {
    "schema_version": 1,
    "functions": { name: { "decl": "<verbatim>", "home": "<subsystem>",
                            "class": "manifest|test-seam|legacy-import" } },
    "globals":   { name: { "decl": "<verbatim>",
                            "owner": "<state TU>" } }
  }

"home" is the defining subsystem from data/recovered_sources.json. The
api/internal split is intentionally NOT stored here: it derives from measured
cross-subsystem usage and is computed fresh by tools/gen_subsystem_headers.py
each run (a stored field would silently go stale); the durable public-surface
record is data/header_surface_baseline.json.

Declaration text is copied VERBATIM (mirror, never re-derive): a re-derived
prototype could disagree with what every TU compiled against and change call
codegen. Signature-typing campaigns edit THIS file and regenerate.

Usage:
  python3 tools/extract_recovered_decls.py            # write + report
  python3 tools/extract_recovered_decls.py --check    # verify freshness
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
FOUNDATION = REPO / "src" / "recovered_foundation.h"
FUNCTIONS_H = REPO / "src" / "recovered_functions.h"
MANIFEST = REPO / "data" / "recovered_sources.json"
OUT = REPO / "data" / "recovered_decls.json"

FUNC_NAME = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
GLOBAL_NAME = re.compile(
    r"\b([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])*\s*(?:=[^;]*)?;\s*(?://.*)?$"
)


def items(path: Path):
    """Yield (decl_text, in_testing_block) top-level `;`-terminated items."""
    text = path.read_text(encoding="latin-1")
    lines = [l.rstrip("\r") for l in text.split("\n")]
    in_testing = False
    depth_pp = 0
    i, n = 0, len(lines)
    while i < n:
        stripped = lines[i].strip()
        if stripped.startswith("#"):
            if re.match(r"#\s*ifdef\s+CLASH95_TESTING", stripped):
                in_testing = True
                depth_pp = 1
            elif in_testing and re.match(r"#\s*if", stripped):
                depth_pp += 1
            elif in_testing and re.match(r"#\s*endif", stripped):
                depth_pp -= 1
                if depth_pp == 0:
                    in_testing = False
            i += 1
            continue
        if not stripped or stripped.startswith("//"):
            i += 1
            continue
        if stripped.startswith("/*"):
            while i < n and "*/" not in lines[i]:
                i += 1
            i += 1
            continue
        # code item: consume to top-level ';'
        depth = 0
        blk = []
        while i < n:
            l = lines[i]
            blk.append(l)
            done = False
            for ch in l.split("//")[0]:
                if ch in "{(":
                    depth += 1
                elif ch in "})":
                    depth -= 1
                elif ch == ";" and depth <= 0:
                    done = True
                    break
            i += 1
            if done:
                break
        yield "\n".join(blk).strip(), in_testing


def classify(decl: str):
    """Return ("global"|"function", name) for one declaration."""
    code = decl.split("//")[0]
    # attributes confuse name extraction; drop them for classification only
    # (the stored decl text keeps them verbatim). Inner parens are handled:
    # __attribute__((aligned(4))) needs one nesting level.
    code = re.sub(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", " ", code)
    if "(" in code:
        # extern object of function-pointer type (scalar or array), with an
        # optional calling-convention macro: (__thiscall *g_X). Only valid
        # when the (*name) group is the FIRST function-ish paren -- a
        # prototype like `extern void PlayAvi(char *f, int (*cb)(void))`
        # also contains (*cb) but has `PlayAvi(` before it.
        mptr = re.search(
            r"\(\s*(?:__\w+\s+)?\*\s*([A-Za-z_][A-Za-z0-9_]*)"
            r"\s*(?:\[[^\]]*\])?\s*\)", code
        )
        if mptr and re.match(r"\s*extern\b", code):
            prefix = code[: mptr.start()]
            if not re.search(r"\b[A-Za-z_][A-Za-z0-9_]*\s*\(", prefix):
                return "global", mptr.group(1)
        # function RETURNING a function pointer:
        #   extern int (*Name (params)) (params);
        mret = re.search(
            r"\(\s*(?:__\w+\s+)?\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\(", code
        )
        if mret:
            return "function", mret.group(1)
        m = FUNC_NAME.search(code)
        if m:
            return "function", m.group(1)
    m = GLOBAL_NAME.search(code.strip())
    if m:
        return "global", m.group(1)
    raise ValueError(f"unclassifiable declaration: {decl[:100]!r}")


def has_param_list(decl: str) -> bool:
    """True when the declaration's own parameter parens are non-empty (a real
    prototype, including (void)); False for K&R empty parens."""
    code = decl.split("//")[0]
    code = re.sub(r"__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)", " ", code)
    m = re.search(r"\b[A-Za-z_][A-Za-z0-9_]*\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*;?\s*$",
                  code.strip())
    if not m:
        # fn-returning-fn-ptr etc.: treat outer-most paren group after name
        m = re.search(r"\b[A-Za-z_][A-Za-z0-9_]*\s*\(([^()]*)\)", code)
    return bool(m and m.group(1).strip())


def better_global_decl(a: str, b: str) -> str:
    """Between two compatible redeclarations prefer the more specific one
    (explicit array size beats unsized; otherwise the longer text)."""
    a_sized = bool(re.search(r"\[\s*\d", a))
    b_sized = bool(re.search(r"\[\s*\d", b))
    if a_sized != b_sized:
        return a if a_sized else b
    return a if len(a) >= len(b) else b


def build():
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    home = {r["name"]: r["subsystem"] for r in manifest["functions"]}
    state_owner = manifest["state_owner"]

    functions: dict[str, dict] = {}
    globals_: dict[str, dict] = {}
    problems: list[str] = []

    for path in (FOUNDATION, FUNCTIONS_H):
        for decl, in_testing in items(path):
            # invariant since P3.1: the declaration umbrellas hold ONLY extern
            # objects and function prototypes -- type definitions and pragmas
            # belong in recovered_types.h
            head = decl.lstrip()
            if re.match(r"(typedef|struct|union|enum)\b", head) or "#pragma" in decl:
                problems.append(
                    f"type/pragma item in {path.name} (move to "
                    f"recovered_types.h): {head[:80]!r}")
                continue
            try:
                kind, name = classify(decl)
            except ValueError as exc:
                problems.append(str(exc))
                continue
            if kind == "global":
                prev = globals_.get(name)
                if prev and prev["decl"] != decl:
                    # benign unsized/sized redeclaration pair -- keep the more
                    # specific spelling (both were visible TU-wide before, so
                    # emitting only the composite-compatible one is equivalent)
                    prev["decl"] = better_global_decl(prev["decl"], decl)
                    continue
                globals_.setdefault(name, {"decl": decl, "owner": state_owner})
                continue
            cls = ("test-seam" if in_testing
                   else "manifest" if name in home
                   else "legacy-import")
            prev = functions.get(name)
            if prev:
                # Duplicate declarations: the umbrella included BOTH, and the
                # later (typically full-prototype) one refined the earlier
                # empty-paren spelling at every call site. Keep the decl with
                # a real parameter list; two DIFFERENT real prototypes are an
                # error.
                if prev["decl"] != decl:
                    prev_proto = has_param_list(prev["decl"])
                    new_proto = has_param_list(decl)
                    if prev_proto and new_proto:
                        problems.append(
                            f"conflicting function prototypes for {name}")
                    elif new_proto:
                        prev["decl"] = decl
                        prev["class"] = cls if cls != "legacy-import" else prev["class"]
                continue
            functions[name] = {
                "decl": decl,
                "home": home.get(name, "legacy"),
                "class": cls,
            }
    return functions, globals_, problems


def main() -> int:
    if not FOUNDATION.exists():
        print("historical tool: the declaration umbrellas were deleted at the "
              "P3 header narrowing; data/recovered_decls.json is now the "
              "canonical declaration home (edit it and regenerate via "
              "tools/gen_subsystem_headers.py --write).")
        return 0
    functions, globals_, problems = build()
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    manifest_names = {r["name"] for r in manifest["functions"]}
    declared = {n for n, r in functions.items() if r["class"] != "legacy-import"}
    undeclared_manifest = sorted(manifest_names - set(functions))
    counts = {
        "functions": len(functions),
        "manifest_declared": sum(1 for r in functions.values() if r["class"] == "manifest"),
        "test_seam": sum(1 for r in functions.values() if r["class"] == "test-seam"),
        "legacy_import": sum(1 for r in functions.values() if r["class"] == "legacy-import"),
        "globals": len(globals_),
        "manifest_functions_without_decl": len(undeclared_manifest),
    }
    print(json.dumps(counts, indent=1))
    if undeclared_manifest:
        print("manifest functions with no umbrella decl (first 10):")
        for nm in undeclared_manifest[:10]:
            print("  ", nm)
    for p in problems[:10]:
        print("PROBLEM:", p)

    payload = {
        "schema_version": 1,
        "functions": {k: functions[k] for k in sorted(functions)},
        "globals": {k: globals_[k] for k in sorted(globals_)},
    }
    text = json.dumps(payload, indent=1, sort_keys=True) + "\n"

    if "--check" in sys.argv:
        current = OUT.read_text(encoding="utf-8") if OUT.exists() else None
        if current != text:
            print("STALE: data/recovered_decls.json out of date -- rerun extractor")
            return 1
        print("decl DB up to date")
        return 0

    OUT.write_text(text, encoding="utf-8")
    print(f"wrote {OUT.relative_to(REPO)}")
    return 0 if not problems else 1


if __name__ == "__main__":
    sys.exit(main())
