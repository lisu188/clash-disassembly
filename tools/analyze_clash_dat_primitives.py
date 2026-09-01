#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path

from clash_dat_primitives import bitmap_primitive_report, decode_all_primitives
from decompile_clash_dat import parse_bsave


def render_text(ir: dict) -> str:
    decoded = decode_all_primitives(ir)
    counts = Counter(item.type_name for item in decoded)
    lines = [
        "CLASH.DAT compiled primitive recovery",
        f"decoded bitmap expressions: {len(decoded)}",
        "",
        "Decoded types:",
    ]
    for name, count in sorted(counts.items()):
        lines.append(f"  {name}: {count}")
    lines.extend(["", "Representative decoded expressions:"])
    seen = set()
    for item in decoded:
        if item.type_name in seen:
            continue
        seen.add(item.type_name)
        lines.append(
            f"  expr[{item.expression_index}] {item.type_name} "
            f"bitmap[{item.bitmap_index}]={item.raw_hex} -> {item.semantic}"
        )
    handler_count = sum(1 for expression in ir["expressions"] if expression[0] in (58, 59))
    lines.extend(
        [
            "",
            f"HANDLER_GET/HANDLER_PUT references retained as raw typed bitmaps: {handler_count}",
            "Their 6-byte direct-slot reference layout remains intentionally unresolved.",
        ]
    )
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Decode compiled CLIPS fact/object primitives in CLASH.DAT"
    )
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--json", dest="json_path")
    parser.add_argument("--text", dest="text_path")
    args = parser.parse_args()

    ir = parse_bsave(Path(args.input))
    report = bitmap_primitive_report(ir)
    text = render_text(ir)

    if args.json_path:
        Path(args.json_path).write_text(
            json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8"
        )
    if args.text_path:
        Path(args.text_path).write_text(text + "\n", encoding="utf-8")

    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
