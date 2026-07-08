#!/usr/bin/env python3
"""Apply validated identifier renames (globals, nullsubs, etc.) to the sources.

General-purpose sibling of apply_sub_renames.py: works for any old identifier
(not just sub_XXXXXX). Token-aware (skips strings/comments), validates new names
are unique valid C identifiers absent from the code, auto-suffixes collisions
with a short disambiguator.

Usage: apply_renames.py mapping.json [mapping2.json ...]
mapping entry: {"old","new","confidence","evidence","area"}
"""
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from apply_sub_renames import split_code_and_literals  # noqa: E402
from apply_sub_renames import CODE_FILES as BASE_CODE_FILES  # noqa: E402
import glob as _glob  # noqa: E402

# Also rewrite the unit-test sources, which call recovered symbols by name.
CODE_FILES = list(BASE_CODE_FILES) + sorted(
    _glob.glob("tests/unit/**/*.c", recursive=True)
    + _glob.glob("tests/unit/*.h")
)

IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
MACHINE_RE = re.compile(
    r"^(sub|dword|byte|word|off|unk|flt|dbl|qword|xmmword|loc|nullsub|a|v)_?[0-9A-Fa-f]"
)


def main():
    entries = []
    for path in sys.argv[1:]:
        entries.extend(json.load(open(path)))

    texts = {}
    for cf in CODE_FILES:
        try:
            texts[cf] = open(cf, "r", errors="replace").read()
        except FileNotFoundError:
            pass
    all_code = "\n".join(texts.values())
    existing = set(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", all_code))

    accepted, rejected, used_new = [], [], set()
    for e in entries:
        old, new = e.get("old", ""), e.get("new", "")
        if not IDENT_RE.match(old or ""):
            rejected.append((old, new, "bad old"))
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
    for cf, text in texts.items():
        segs = split_code_and_literals(text)
        rebuilt = "".join(
            pat.sub(lambda m: mapping[m.group(1)], seg) if is_code else seg
            for is_code, seg in segs
        )
        if rebuilt != text:
            open(cf, "w").write(rebuilt)

    accum = os.environ.get("RENAME_ACCUM", "/tmp/applied_global_renames.jsonl")
    with open(accum, "a") as f:
        for e in accepted:
            f.write(json.dumps(e) + "\n")
    print(json.dumps(
        {"applied": len(accepted),
         "collisions": [e["old"] for e in accepted if "collision_from" in e],
         "rejected": rejected}, indent=1))


if __name__ == "__main__":
    main()
