#!/usr/bin/env python3
"""Header-surface audit and coupling ratchet (P3.7).

Keeps the narrowed per-subsystem header architecture honest after the umbrella
deletion. Three passes:

1. FRESHNESS — the generated headers, data/subsystem_api.json, and every TU's
   marker-delimited include block must match a clean regeneration
   (tools/gen_subsystem_headers.py --check / --check-tu-includes).
2. INCLUDE POLICY — production recovered TUs may include recovered headers
   only inside the generated block; no TU may include another subsystem's
   <S>_internal.h, <S>_state.h or <S>_shared_state.h. The shared-state aggregate
   stays within the state definition group and tests; src/recovered_all.h is
   tests-only; the deleted umbrella names must not return. Consumer and TU
   shared-state visibility records must agree with their measured references.
   Consumer-slice policy is enabled by recovered_decls.json's explicit
   shared_state_layout=consumer setting; the default aggregate layout retains
   its existing policy until a validated generator cutover.
3. COUPLING RATCHET — per-subsystem public-surface size (api function count),
   shared-global count, and peer edges are compared against
   data/header_surface_baseline.json: any INCREASE fails (decreases pass and
   are locked in with --mode update). This is the "new coupling is a
   deliberate choice" gate.

Usage:
  python3 tools/audit_header_surface.py --mode check    (CI)
  python3 tools/audit_header_surface.py --mode update   (conscious re-seed)
"""

from __future__ import annotations

import argparse
import json
import posixpath
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
SURFACE = REPO / "data" / "subsystem_api.json"
DECLS = REPO / "data" / "recovered_decls.json"
BASELINE = REPO / "data" / "header_surface_baseline.json"
GEN = REPO / "tools" / "gen_subsystem_headers.py"

MARK_BEGIN = "/* CLASH95_GENERATED_INCLUDES_BEGIN"
MARK_END = "/* CLASH95_GENERATED_INCLUDES_END */"
FORBIDDEN_UMBRELLA = ("recovered_internal.h", "recovered_functions.h",
                      "recovered_foundation.h")


def run_gen(*flags: str) -> int:
    proc = subprocess.run([sys.executable, str(GEN), *flags],
                          capture_output=True, text=True)
    if proc.returncode != 0:
        print(proc.stdout.strip())
        print(proc.stderr.strip())
    return proc.returncode


def consumer_shared_state_enabled() -> bool:
    decls = json.loads(DECLS.read_text(encoding="utf-8"))
    return decls.get("shared_state_layout", "aggregate") == "consumer"


def include_policy_errors() -> list[str]:
    errors = []
    consumer_layout = consumer_shared_state_enabled()
    manifest = json.loads(
        (REPO / "data" / "recovered_sources.json").read_text(encoding="utf-8"))
    sources = sorted({r["source"] for r in manifest["functions"]}
                     | {manifest["state_owner"]})
    # Support files keep hand-maintained includes, but the hard bans (deleted
    # umbrella must not return; tests-only aggregate stays out of production)
    # apply to every production .c under src/.
    support = sorted(
        str(p.relative_to(REPO)).replace("\\", "/")
        for p in (REPO / "src").rglob("*.c")
        if str(p.relative_to(REPO)).replace("\\", "/") not in sources)
    # both quoted and angle-bracket forms resolve via -I flags; lint both
    inc_re = re.compile(r'^\s*#\s*include\s+["<]([^">]+)[">]', re.M)
    generated_basenames = re.compile(
        r"(recovered_|_api\.h$|_internal\.h$|_state\.h$|"
        r"^state_shared\.h$|^state_local\.h$)")
    for rel in sources + support:
        text = (REPO / rel).read_text(encoding="latin-1")
        parts = rel.split("/")
        sub = parts[1] if len(parts) > 2 else ""
        is_recovered_tu = rel in sources
        m = re.search(re.escape(MARK_BEGIN) + r".*?" + re.escape(MARK_END),
                      text, flags=re.DOTALL)
        block_span = m.span() if m else (0, 0)
        for im in inc_re.finditer(text):
            inc = im.group(1)
            inside = block_span[0] <= im.start() < block_span[1]
            # Treat source-relative, -I src, repository-root, and normalized
            # ../ spellings alike. Header ownership is encoded in its basename,
            # so a foreign slice cannot bypass policy by changing its path.
            base = posixpath.basename(posixpath.normpath(inc.replace("\\", "/")))
            if base in FORBIDDEN_UMBRELLA:
                errors.append(f"{rel}: deleted umbrella include returned: {inc}")
            if base == "recovered_all.h":
                errors.append(f"{rel}: tests-only aggregate included in production")
            if not is_recovered_tu:
                continue  # support files: hard bans only
            if not inside and generated_basenames.search(base):
                errors.append(f"{rel}: recovered include outside generated block: {inc}")
            if consumer_layout and base == "state_shared.h" and sub != "state":
                errors.append(f"{rel}: shared-state aggregate outside state group: {inc}")
            if consumer_layout:
                fm = re.fullmatch(
                    r"([a-z][a-z0-9_]*?)_(internal|shared_state|state)\.h", base)
            else:
                fm = re.match(r"(?:\.\./)?([a-z]+)/\1_(internal|state)\.h$", inc)
            if fm and fm.group(1) != sub:
                # the state group is the definition site of every global and
                # includes ALL *_state.h slices so definitions stay decl-checked
                if not (sub == "state" and fm.group(2) == "state"):
                    errors.append(f"{rel}: foreign {fm.group(2)} header: {inc}")
    return errors


def shared_state_surface_errors() -> list[str]:
    """Check declaration visibility without changing the coupling ratchet.

    References measure dependencies; visible declarations measure exposure.
    Fresh generation checks the source evidence, while this check enforces the
    relationship between those two explicitly separate sets.
    """
    if not consumer_shared_state_enabled():
        return []
    surface = json.loads(SURFACE.read_text(encoding="utf-8"))
    manifest = json.loads(
        (REPO / "data" / "recovered_sources.json").read_text(encoding="utf-8"))
    errors = []
    shared = set(surface["shared_globals"])
    expected_consumers = set(surface["subsystems"]) - {"state"}
    sources = {r["source"] for r in manifest["functions"]} | {manifest["state_owner"]}
    expected_sources = {rel for rel in sources if rel.split("/")[1] != "state"}

    def mapping(field: str, expected: set[str]) -> dict:
        value = surface.get(field)
        if not isinstance(value, dict):
            errors.append(f"{field}: required object missing or invalid")
            return {}
        missing, extra = expected - value.keys(), value.keys() - expected
        if missing:
            errors.append(f"{field}: missing entries: {', '.join(sorted(missing))}")
        if extra:
            errors.append(f"{field}: unexpected entries: {', '.join(sorted(extra))}")
        return value

    def names(value, label: str) -> set[str] | None:
        if not isinstance(value, list) or not all(isinstance(n, str) for n in value):
            errors.append(f"{label}: expected a sorted list of shared-global DB keys")
            return None
        result = set(value)
        if value != sorted(result):
            errors.append(f"{label}: keys must be sorted and unique")
        if result - shared:
            errors.append(f"{label}: keys are not shared globals: "
                          f"{', '.join(sorted(result - shared))}")
        return result

    consumers = mapping("shared_state_consumers", expected_consumers)
    visibility = mapping("tu_shared_state_visibility", expected_sources)
    slices = {sub: names(value, f"shared_state_consumers.{sub}")
              for sub, value in consumers.items()}
    references = {sub: set() for sub in expected_consumers}
    for rel, record in visibility.items():
        label = f"tu_shared_state_visibility.{rel}"
        if not isinstance(record, dict) or set(record) != {"referenced", "visible"}:
            errors.append(f"{label}: expected referenced and visible fields")
            continue
        referenced = names(record["referenced"], f"{label}.referenced")
        visible = names(record["visible"], f"{label}.visible")
        if referenced is None or visible is None or rel not in expected_sources:
            continue
        sub = rel.split("/")[1]
        if sub not in references:
            errors.append(f"{label}: subsystem {sub!r} missing from surface")
            continue
        references[sub].update(referenced)
        if referenced - visible:
            errors.append(f"{label}: referenced globals are not visible")
        consumer_slice = slices.get(sub)
        if consumer_slice is not None:
            expected_visible = consumer_slice if referenced else set()
            if visible != expected_visible:
                errors.append(f"{label}: visible globals must equal the consumer "
                              "slice when referenced, otherwise be empty")
    for sub, referenced in references.items():
        if slices.get(sub) is not None and slices[sub] != referenced:
            errors.append(f"shared_state_consumers.{sub}: slice differs from "
                          "the union of TU references")
    return errors


def surface_metrics() -> dict:
    s = json.loads(SURFACE.read_text(encoding="utf-8"))
    return {
        "api_counts": {k: len(v["api_functions"])
                       for k, v in s["subsystems"].items()},
        "shared_global_count": len(s["shared_globals"]),
        "peer_edges": s["peer_edges"],
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--mode", choices=("check", "update"), default="check")
    args = ap.parse_args()

    ok = True
    if run_gen("--check") != 0:
        print("FRESHNESS: generated headers/surface stale"); ok = False
    if run_gen("--check-tu-includes") != 0:
        print("FRESHNESS: TU include blocks stale"); ok = False

    errors = include_policy_errors()
    for e in errors[:15]:
        print("POLICY:", e)
    if errors:
        ok = False

    errors = shared_state_surface_errors()
    for e in errors[:15]:
        print("VISIBILITY:", e)
    if errors:
        ok = False

    cur = surface_metrics()
    if args.mode == "update":
        if not ok:
            print("refusing to update baseline with failures present")
            return 1
        BASELINE.write_text(json.dumps(
            {"schema_version": 1, **cur}, indent=1, sort_keys=True) + "\n",
            encoding="utf-8")
        print(f"updated header-surface baseline -> {BASELINE.relative_to(REPO)}")
        return 0

    if BASELINE.exists():
        base = json.loads(BASELINE.read_text(encoding="utf-8"))
        regressions = []
        for s_, n in cur["api_counts"].items():
            b = base.get("api_counts", {}).get(s_, 0)
            if n > b:
                regressions.append(f"api surface of {s_} grew {b} -> {n}")
        if cur["shared_global_count"] > base.get("shared_global_count", 0):
            regressions.append(
                f"shared globals grew {base.get('shared_global_count')} -> "
                f"{cur['shared_global_count']}")
        for edge, n in cur["peer_edges"].items():
            b = base.get("peer_edges", {}).get(edge, 0)
            if n > b:
                regressions.append(f"peer edge {edge} grew {b} -> {n}")
        for r in regressions[:15]:
            print("RATCHET:", r)
        if regressions:
            print("(a deliberate surface increase re-seeds with --mode update)")
            ok = False
    else:
        print("note: no header-surface baseline; seed with --mode update")

    print(f"header-surface audit: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
