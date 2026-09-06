#!/usr/bin/env python3

from __future__ import annotations

import re
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

PATTERNS = {
    "decompiler_locals": re.compile(r"\b(?:v\d+|a\d+)\b"),
    "legacy_globals": re.compile(r"\b(?:byte|word|dword|qword)_[0-9A-Fa-f]+\b"),
    "raw_pointer_offsets": re.compile(r"\*\s*\([^\n;]*\*\)\s*\([^\n;]*\+\s*(?:0x[0-9A-Fa-f]+|\d+)\)"),
    "goto": re.compile(r"\bgoto\s+[A-Za-z_]\w*\s*;"),
    "labels": re.compile(r"(?m)^\s*LABEL_\d+\s*:"),
    "unknown_types": re.compile(r"\b_UNKNOWN\b"),
    "integer_pointer_casts": re.compile(r"\(uintptr_t\)|\(intptr_t\)"),
}


def source_files() -> list[Path]:
    return sorted(path for path in SRC.rglob("*") if path.suffix in {".c", ".cpp", ".h"})


def main() -> int:
    totals: Counter[str] = Counter()
    per_file: list[tuple[int, Path, Counter[str]]] = []

    for path in source_files():
        text = path.read_text(encoding="utf-8", errors="replace")
        counts = Counter({name: len(pattern.findall(text)) for name, pattern in PATTERNS.items()})
        totals.update(counts)
        score = sum(counts.values())
        if score:
            per_file.append((score, path.relative_to(ROOT), counts))

    print("Recovered C/C++ human-readability debt")
    print("==================================")
    for name in PATTERNS:
        print(f"{name:24} {totals[name]:8d}")

    print("\nHighest-debt files")
    print("------------------")
    for score, path, counts in sorted(per_file, reverse=True)[:25]:
        details = ", ".join(f"{name}={counts[name]}" for name in PATTERNS if counts[name])
        print(f"{score:8d}  {path}  {details}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
