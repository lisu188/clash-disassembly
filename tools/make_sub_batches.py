#!/usr/bin/env python3
"""Generate per-batch analysis context files for the sub_ rename campaign.

Reads the inventory JSON produced by sub_inventory.py, re-derives the full
function-definition list from clash95.c for neighborhood context, and writes
batch_NNN.json files (address-ordered clusters) into the output directory.
"""
import json
import os
import re
import sys

SRC = "clash95.c"
BATCH_SIZE = 40


def find_defs(lines):
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
        is_def = False
        scanned = 0
        while j < len(lines) and scanned < 60:
            s = lines[j]
            done = False
            for ch in s:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                elif ch == ";" and depth <= 0:
                    done = True
                    break
                elif ch == "{" and depth <= 0:
                    is_def = True
                    done = True
                    break
            if done:
                break
            j += 1
            scanned += 1
        if is_def:
            defs.append((name, i + 1))
    return defs


def main():
    inv_path, out_dir = sys.argv[1], sys.argv[2]
    with open(inv_path) as f:
        inv = json.load(f)
    with open(SRC, errors="replace") as f:
        lines = f.readlines()
    defs = find_defs(lines)
    os.makedirs(out_dir, exist_ok=True)

    # neighborhood: for each def index, nearest non-sub names before/after
    names = [n for n, _ in defs]
    pos = {n: k for k, n in enumerate(names)}

    def neighbors(name, span=6):
        k = pos.get(name)
        if k is None:
            return []
        out = []
        for kk in range(max(0, k - span), min(len(names), k + span + 1)):
            if kk != k:
                out.append(names[kk])
        return out

    subs = sorted(inv["defined"].items(), key=lambda kv: kv[0])
    batches = [subs[i : i + BATCH_SIZE] for i in range(0, len(subs), BATCH_SIZE)]
    for bi, batch in enumerate(batches):
        payload = []
        for name, info in batch:
            payload.append(
                {
                    "name": name,
                    "def_line": info["line"],
                    "end_line": info["end"],
                    "size_lines": info["size_lines"],
                    "signature": info["signature"],
                    "callers": info["callers"][:12],
                    "callees": info["callees"][:12],
                    "strings": info["strings"],
                    "file_neighbors": neighbors(name),
                }
            )
        with open(os.path.join(out_dir, f"batch_{bi:03d}.json"), "w") as f:
            json.dump(payload, f, indent=1)
    print(f"wrote {len(batches)} batches to {out_dir}")


if __name__ == "__main__":
    main()
