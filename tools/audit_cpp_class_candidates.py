#!/usr/bin/env python3

import argparse
import json
import re
from collections import defaultdict
from pathlib import Path

SYMBOL_RE = re.compile(r"\b(?:g_)?([A-Z][A-Za-z0-9]*_[A-Za-z0-9_]+)\b")
VTABLE_RE = re.compile(r"(?:V[Tt]able|[Vv]table)")
CTOR_RE = re.compile(r"(?:Construct|Ctor|CopyConstruct)", re.IGNORECASE)
DTOR_RE = re.compile(r"(?:Destruct|Dtor|Destructor|DeletingDtor)", re.IGNORECASE)


def family_of(symbol):
    return symbol.split("_", 1)[0]


def collect_candidates(root):
    root = Path(root)
    src = root / "src"
    evidence = defaultdict(lambda: {
        "symbols": set(),
        "files": set(),
        "vtable_mentions": 0,
        "constructor_mentions": 0,
        "destructor_mentions": 0,
        "thiscall_mentions": 0,
        "array_runtime_mentions": 0,
    })

    for path in sorted(src.rglob("*.cpp")):
        text = path.read_text(encoding="utf-8", errors="replace")
        relative = path.relative_to(root).as_posix()
        symbols = set(SYMBOL_RE.findall(text))
        for symbol in symbols:
            family = family_of(symbol)
            item = evidence[family]
            item["symbols"].add(symbol)
            item["files"].add(relative)

        for line in text.splitlines():
            line_symbols = set(SYMBOL_RE.findall(line))
            families = {family_of(symbol) for symbol in line_symbols}
            for family in families:
                item = evidence[family]
                if VTABLE_RE.search(line) and family.lower() in line.lower():
                    item["vtable_mentions"] += 1
                if CTOR_RE.search(line) and family.lower() in line.lower():
                    item["constructor_mentions"] += 1
                if DTOR_RE.search(line) and family.lower() in line.lower():
                    item["destructor_mentions"] += 1
                if "__thiscall" in line and family.lower() in line.lower():
                    item["thiscall_mentions"] += 1
                if ("_wcpp_4_ctor_array__" in line or "_wcpp_4_dtor_array_store__" in line):
                    item["array_runtime_mentions"] += 1

    candidates = []
    for family, item in evidence.items():
        symbol_count = len(item["symbols"])
        score = min(symbol_count, 12)
        score += 5 * item["vtable_mentions"]
        score += 3 * item["constructor_mentions"]
        score += 3 * item["destructor_mentions"]
        score += 2 * item["thiscall_mentions"]
        score += 2 * item["array_runtime_mentions"]
        if item["vtable_mentions"] == 0 and item["constructor_mentions"] == 0 \
                and item["destructor_mentions"] == 0 and item["thiscall_mentions"] == 0:
            continue
        candidates.append({
            "family": family,
            "score": score,
            "symbol_count": symbol_count,
            "file_count": len(item["files"]),
            "vtable_mentions": item["vtable_mentions"],
            "constructor_mentions": item["constructor_mentions"],
            "destructor_mentions": item["destructor_mentions"],
            "thiscall_mentions": item["thiscall_mentions"],
            "array_runtime_mentions": item["array_runtime_mentions"],
            "sample_symbols": sorted(item["symbols"])[:8],
            "sample_files": sorted(item["files"])[:5],
        })

    candidates.sort(key=lambda item: (-item["score"], item["family"]))
    return candidates


def print_table(candidates):
    header = (
        f"{'family':28} {'score':>5} {'sym':>4} {'files':>5} "
        f"{'vt':>3} {'ctor':>4} {'dtor':>4} {'this':>4} {'array':>5}"
    )
    print(header)
    print("-" * len(header))
    for item in candidates:
        print(
            f"{item['family'][:28]:28} {item['score']:5d} "
            f"{item['symbol_count']:4d} {item['file_count']:5d} "
            f"{item['vtable_mentions']:3d} {item['constructor_mentions']:4d} "
            f"{item['destructor_mentions']:4d} {item['thiscall_mentions']:4d} "
            f"{item['array_runtime_mentions']:5d}"
        )


def main():
    parser = argparse.ArgumentParser(
        description="Rank recovered C++ class-family candidates from code evidence."
    )
    parser.add_argument("--root", default=Path(__file__).resolve().parents[1])
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--min-score", type=int, default=6)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()

    candidates = [
        item for item in collect_candidates(args.root)
        if item["score"] >= args.min_score
    ][:args.limit]

    if args.json:
        print(json.dumps(candidates, indent=2, sort_keys=True))
    else:
        print_table(candidates)
        print()
        print("Scores rank evidence for review; they do not prove original class boundaries.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
