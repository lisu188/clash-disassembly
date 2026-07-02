#!/usr/bin/env python3
"""Regenerate docs/archive/SUB_RENAME_INDEX.md from the accumulated rename JSONL.

Usage: gen_sub_rename_index.py accum.jsonl
"""
import json
import sys

HEADER = """# sub_ Rename Index

Machine-generated index of the bulk `sub_XXXXXX` -> semantic-name campaign.
The `sub_` name encodes the original virtual address and remains the canonical
anchor into `clash95.asm` / `clash95.map`; grep this file to map either
direction. Confidence follows `docs/REVERSE_ENGINEERING.md` section 2:
high = 2+ independent signals, medium = strongly suggested, low = honest
mechanical description only (gameplay role unproven).

| Original | Recovered name | Confidence | Area | Evidence |
| --- | --- | --- | --- | --- |
"""


def esc(s):
    return str(s).replace("|", "\\|").replace("\n", " ").strip()


def main():
    rows = {}
    with open(sys.argv[1]) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            e = json.loads(line)
            rows[e["old"]] = e
    out = [HEADER]
    for old in sorted(rows):
        e = rows[old]
        out.append(
            f"| `{old}` | `{e['new']}` | {esc(e.get('confidence', '?'))} "
            f"| {esc(e.get('area', ''))} | {esc(e.get('evidence', ''))} |\n"
        )
    with open("docs/archive/SUB_RENAME_INDEX.md", "w") as f:
        f.writelines(out)
    print(f"wrote {len(rows)} index rows")


if __name__ == "__main__":
    main()
