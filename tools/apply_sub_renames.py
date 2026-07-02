#!/usr/bin/env python3
"""Apply validated sub_XXXXXX -> semantic-name renames to the recovered sources.

Usage: apply_sub_renames.py mapping.json [mapping2.json ...]

mapping.json: list of {"old": "sub_XXXXXX", "new": "Name", "confidence": "...",
"evidence": "...", "area": "..."}

Rules enforced here:
- token-aware replacement: string literals, char literals, and comments are
  left untouched so historical anchors and runtime trace text stay stable;
- new names must be valid C identifiers, unique in the batch, and absent from
  the code surface before the rename;
- collisions are auto-disambiguated by appending the hex address suffix.

Accepted mappings are appended to docs/archive/SUB_RENAME_INDEX.md by the
caller (this script prints an index-row block on stdout).
"""
import json
import os
import re
import sys

CODE_FILES = [
    "clash95.c",
    "bootstrap_main.c",
    "platform_sdl_runtime.c",
    "platform_sdl.h",
    "defs.h",
    "windows.h",
    "compat/decomp_runtime_stubs.c",
]

IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")


def split_code_and_literals(text):
    """Yield (is_code, segment) pairs; literals/comments are is_code=False."""
    out = []
    i, n = 0, len(text)
    start = 0
    while i < n:
        c = text[i]
        nxt = text[i + 1] if i + 1 < n else ""
        if c == '"' or c == "'":
            out.append((True, text[start:i]))
            q = c
            j = i + 1
            while j < n:
                if text[j] == "\\":
                    j += 2
                    continue
                if text[j] == q:
                    j += 1
                    break
                j += 1
            out.append((False, text[i:j]))
            i = j
            start = i
        elif c == "/" and nxt == "/":
            out.append((True, text[start:i]))
            j = text.find("\n", i)
            j = n if j == -1 else j
            out.append((False, text[i:j]))
            i = j
            start = i
        elif c == "/" and nxt == "*":
            out.append((True, text[start:i]))
            j = text.find("*/", i + 2)
            j = n if j == -1 else j + 2
            out.append((False, text[i:j]))
            i = j
            start = i
        else:
            i += 1
    out.append((True, text[start:]))
    return out


def main():
    entries = []
    for path in sys.argv[1:]:
        with open(path) as f:
            data = json.load(f)
        entries.extend(data)

    texts = {}
    for cf in CODE_FILES:
        try:
            with open(cf, "r", errors="replace") as f:
                texts[cf] = f.read()
        except FileNotFoundError:
            pass

    all_code = "\n".join(texts.values())
    existing_idents = set(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", all_code))

    accepted = []
    rejected = []
    used_new = set()
    for e in entries:
        old, new = e.get("old", ""), e.get("new", "")
        if not re.fullmatch(r"sub_[0-9A-F]{6}", old):
            rejected.append((old, new, "bad old symbol"))
            continue
        if not IDENT_RE.fullmatch(new) or new.startswith("sub_"):
            rejected.append((old, new, "bad new identifier"))
            continue
        if old not in existing_idents:
            rejected.append((old, new, "old symbol not present in code"))
            continue
        if new in existing_idents or new in used_new:
            alt = f"{new}_{old[4:]}"
            if alt in existing_idents or alt in used_new:
                rejected.append((old, new, "collision even with suffix"))
                continue
            e = dict(e)
            e["collision_from"] = new
            e["new"] = new = alt
        used_new.add(new)
        accepted.append(e)

    if not accepted:
        print(json.dumps({"applied": 0, "rejected": rejected}))
        return

    pat = re.compile(
        r"\b(" + "|".join(re.escape(e["old"]) for e in accepted) + r")\b"
    )
    mapping = {e["old"]: e["new"] for e in accepted}

    for cf, text in texts.items():
        segs = split_code_and_literals(text)
        rebuilt = "".join(
            pat.sub(lambda m: mapping[m.group(1)], seg) if is_code else seg
            for is_code, seg in segs
        )
        if rebuilt != text:
            with open(cf, "w") as f:
                f.write(rebuilt)

    report = {
        "applied": len(accepted),
        "rejected": rejected,
        "collisions": [e["old"] for e in accepted if "collision_from" in e],
    }
    print(json.dumps(report, indent=1))
    accum = os.environ.get(
        "SUB_RENAME_ACCUM", "/tmp/applied_renames_accum.jsonl"
    )
    with open(accum, "a") as f:
        for e in accepted:
            f.write(json.dumps(e) + "\n")


if __name__ == "__main__":
    main()
