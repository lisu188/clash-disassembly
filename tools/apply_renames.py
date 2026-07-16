#!/usr/bin/env python3
"""Apply validated identifier renames (globals, nullsubs, etc.) to split sources.

Works for non-function identifiers. Token-aware replacement skips strings and
comments, validates new names are unique valid C identifiers absent from the
code, and auto-suffixes collisions with a short disambiguator. Canonical
implementation files come from ``data/recovered_sources.json``; approved
writes refresh their manifest body hashes.

Usage: apply_renames.py mapping.json [mapping2.json ...]
mapping entry: {"old","new","confidence","evidence","area"}
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc  # noqa: E402
import glob as _glob  # noqa: E402

PRIVATE_HEADERS = (
    "src/recovered/split/recovered_abi.h",
    "src/recovered/split/recovered_foundation.h",
    "src/recovered/split/recovered_functions.h",
    "src/recovered/split/recovered_internal.h",
    "src/recovered/split/recovered_layout.h",
)
SUPPORT_FILES = (
    "src/bootstrap/bootstrap_main.c",
    "src/platform/platform_sdl_runtime.c",
    "src/platform/platform_sdl.h",
    "src/instrumentation/runtime_mission_trace.c",
    "src/instrumentation/runtime_mission_trace.h",
    "src/compatibility/decomp_runtime_stubs.c",
    "src/compatibility/defs.h",
)


def existing_files(paths):
    return [path for path in paths
            if os.path.isfile(os.path.join(lc.REPO, path))]


# Tests and private declarations call/reference recovered symbols by name.
test_files = [
    os.path.relpath(path, lc.REPO).replace(os.sep, "/")
    for path in (
        _glob.glob(os.path.join(lc.REPO, "tests", "unit", "**", "*.c"), recursive=True)
        + _glob.glob(os.path.join(lc.REPO, "tests", "unit", "*.h"))
    )
]
CODE_FILES = existing_files(
    lc.apply_files() + list(PRIVATE_HEADERS) + list(SUPPORT_FILES) + sorted(test_files)
)

IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
MACHINE_RE = re.compile(
    r"^(sub|dword|byte|word|off|unk|flt|dbl|qword|xmmword|loc|nullsub|a|v)_?[0-9A-Fa-f]"
)


def main():
    entries = []
    for path in sys.argv[1:]:
        entries.extend(json.load(open(path)))

    manifest = lc.load_source_manifest()
    manifest_function_names = {record["name"] for record in manifest["functions"]}
    constant_entries, _ = lc.load_manifest()
    constant_names = {entry["name"] for entry in constant_entries}
    texts = {}
    for cf in CODE_FILES:
        try:
            texts[cf] = open(os.path.join(lc.REPO, cf), "r", errors="replace").read()
        except FileNotFoundError:
            pass
    existing = set()
    for text in texts.values():
        for is_code, segment in lc.split_code_and_literals(text):
            if is_code:
                existing.update(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", segment))

    accepted, rejected, used_new = [], [], set()
    for e in entries:
        old, new = e.get("old", ""), e.get("new", "")
        if not IDENT_RE.match(old or ""):
            rejected.append((old, new, "bad old"))
            continue
        if old in manifest_function_names:
            rejected.append((old, new, "function identity requires manifest migration"))
            continue
        if old in constant_names:
            rejected.append((old, new, "constant identity requires manifest migration"))
            continue
        if not IDENT_RE.match(new or "") or MACHINE_RE.match(new):
            rejected.append((old, new, "bad/again-machine new"))
            continue
        if old not in existing:
            rejected.append((old, new, "old not present"))
            continue
        if new == old:
            rejected.append((old, new, "no-op"))
            continue
        if new in existing or new in used_new:
            suffix = old.split("_")[-1]
            alt = f"{new}_{suffix}"
            if alt in existing or alt in used_new:
                rejected.append((old, new, "collision"))
                continue
            e = dict(e)
            e["collision_from"], e["new"], new = new, alt, alt
        used_new.add(new)
        accepted.append(e)

    if not accepted:
        print(json.dumps({"applied": 0, "rejected": rejected}, indent=1))
        return

    mapping = {e["old"]: e["new"] for e in accepted}
    pat = re.compile(r"\b(" + "|".join(re.escape(k) for k in mapping) + r")\b")
    canonical_sources = set(lc.apply_files())
    touched_sources = set()
    for cf, text in texts.items():
        segs = lc.split_code_and_literals(text)
        rebuilt = "".join(
            pat.sub(lambda m: mapping[m.group(1)], seg) if is_code else seg
            for is_code, seg in segs
        )
        if rebuilt != text:
            open(os.path.join(lc.REPO, cf), "w").write(rebuilt)
            if cf in canonical_sources:
                touched_sources.add(cf)

    refreshed = lc.refresh_source_manifest_body_hashes(touched_sources)
    accum = os.environ.get("RENAME_ACCUM", "/tmp/applied_global_renames.jsonl")
    with open(accum, "a") as f:
        for e in accepted:
            f.write(json.dumps(e) + "\n")
    print(json.dumps(
        {"applied": len(accepted),
         "manifest_body_hashes_refreshed": refreshed,
         "collisions": [e["old"] for e in accepted if "collision_from" in e],
         "rejected": rejected}, indent=1))


if __name__ == "__main__":
    main()
