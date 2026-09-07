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
WATCOM_CTOR_RE = re.compile(r"W\?\$ct:([A-Za-z_]\w*)\$")
WATCOM_DTOR_RE = re.compile(r"W\?\$dt:([A-Za-z_]\w*)\$")
WATCOM_METHOD_RE = re.compile(r"W\?[^\s:]+\$:([A-Za-z_]\w*)\$")
CPP_METHOD_RE = re.compile(r"\b([A-Za-z_]\w*)::([A-Za-z_]\w*)\b")


def family_of(symbol):
    return symbol.split("_", 1)[0]


def new_evidence():
    return {
        "symbols": set(),
        "files": set(),
        "vtable_mentions": 0,
        "constructor_mentions": 0,
        "destructor_mentions": 0,
        "thiscall_mentions": 0,
        "array_runtime_mentions": 0,
        "map_methods": set(),
        "map_constructor_mentions": 0,
        "map_destructor_mentions": 0,
    }


def collect_map_evidence(root, evidence):
    map_path = Path(root) / "clash95.map"
    if not map_path.exists():
        return
    for line in map_path.read_text(encoding="latin-1", errors="replace").splitlines():
        ctor_classes = set(WATCOM_CTOR_RE.findall(line))
        dtor_classes = set(WATCOM_DTOR_RE.findall(line))
        for class_name in ctor_classes:
            evidence[class_name]["map_constructor_mentions"] += 1
            evidence[class_name]["map_methods"].add("<ctor>")
        for class_name in dtor_classes:
            evidence[class_name]["map_destructor_mentions"] += 1
            evidence[class_name]["map_methods"].add("<dtor>")
        for class_name in set(WATCOM_METHOD_RE.findall(line)) - ctor_classes - dtor_classes:
            method_match = re.search(r"W\?([^\s:]+)\$:" + re.escape(class_name) + r"\$", line)
            method_name = method_match.group(1) if method_match else "<method>"
            evidence[class_name]["map_methods"].add(method_name)
        for class_name, method_name in CPP_METHOD_RE.findall(line):
            evidence[class_name]["map_methods"].add(method_name)


def collect_candidates(root):
    root = Path(root)
    src = root / "src"
    evidence = defaultdict(new_evidence)

    if src.exists():
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

    collect_map_evidence(root, evidence)

    candidates = []
    for family, item in evidence.items():
        symbol_count = len(item["symbols"])
        map_method_count = len(item["map_methods"])
        score = min(symbol_count, 12)
        score += 5 * item["vtable_mentions"]
        score += 3 * item["constructor_mentions"]
        score += 3 * item["destructor_mentions"]
        score += 2 * item["thiscall_mentions"]
        score += 2 * item["array_runtime_mentions"]
        score += 4 * min(map_method_count, 20)
        score += 8 * item["map_constructor_mentions"]
        score += 8 * item["map_destructor_mentions"]
        if not any((
            item["vtable_mentions"], item["constructor_mentions"],
            item["destructor_mentions"], item["thiscall_mentions"],
            map_method_count, item["map_constructor_mentions"],
            item["map_destructor_mentions"],
        )):
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
            "map_method_count": map_method_count,
            "map_constructor_mentions": item["map_constructor_mentions"],
            "map_destructor_mentions": item["map_destructor_mentions"],
            "sample_map_methods": sorted(item["map_methods"])[:8],
            "sample_symbols": sorted(item["symbols"])[:8],
            "sample_files": sorted(item["files"])[:5],
        })

    candidates.sort(key=lambda item: (-item["score"], item["family"]))
    return candidates


def print_table(candidates):
    header = (
        f"{'family':28} {'score':>5} {'sym':>4} {'files':>5} "
        f"{'vt':>3} {'ctor':>4} {'dtor':>4} {'this':>4} {'array':>5} "
        f"{'map':>4} {'mct':>3} {'mdt':>3}"
    )
    print(header)
    print("-" * len(header))
    for item in candidates:
        print(
            f"{item['family'][:28]:28} {item['score']:5d} "
            f"{item['symbol_count']:4d} {item['file_count']:5d} "
            f"{item['vtable_mentions']:3d} {item['constructor_mentions']:4d} "
            f"{item['destructor_mentions']:4d} {item['thiscall_mentions']:4d} "
            f"{item['array_runtime_mentions']:5d} {item['map_method_count']:4d} "
            f"{item['map_constructor_mentions']:3d} {item['map_destructor_mentions']:3d}"
        )


def main():
    parser = argparse.ArgumentParser(
        description="Rank recovered C++ class-family candidates from source and original-map evidence."
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
