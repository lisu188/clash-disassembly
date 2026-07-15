#!/usr/bin/env python3
"""Report uncovered lines by manifest-backed recovered function identity.

Usage: uncovered_lines.py <build_dir> [--json OUT] [--min N]
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from coverage_source_manifest import (
    CoverageMetadataError,
    collect_split_gcov,
    load_pure_set,
    split_ranges,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("build_dir", type=Path)
    parser.add_argument("--json", dest="jsonout", type=Path)
    parser.add_argument("--min", dest="minimum", type=int, default=1)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    build_dir = args.build_dir.resolve()
    _, functions = load_pure_set(require_manifest=True)
    ranges = split_ranges(functions)
    coverage = collect_split_gcov(
        build_dir, {function["source"] for function in functions}
    )
    rows = []
    for function in functions:
        source, low, high = ranges[function["name"]]
        uncovered = [
            line
            for line in range(low, high)
            if coverage[source].get(line) is False
        ]
        if len(uncovered) >= args.minimum:
            rows.append(
                {
                    "name": function["name"],
                    "source": source,
                    "start_line": low,
                    "end_line": high,
                    "uncovered_lines": uncovered,
                    "uncovered": len(uncovered),
                }
            )
    mode = "split"

    rows.sort(key=lambda row: -row["uncovered"])
    if args.jsonout:
        with args.jsonout.open("w", encoding="utf-8", newline="\n") as stream:
            json.dump({"mode": mode, "functions": rows}, stream, indent=1)
            stream.write("\n")
    print(
        f"coverage mode: {mode}; {len(rows)} functions with >= {args.minimum} "
        f"uncovered lines; total {sum(row['uncovered'] for row in rows)} uncovered"
    )
    for row in rows[:30]:
        preview = row["uncovered_lines"][:8]
        suffix = "..." if len(row["uncovered_lines"]) > 8 else ""
        print(
            f"  {row['uncovered']:3d}  {row['name']}  "
            f"{row['source']}:{preview}{suffix}"
        )
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except CoverageMetadataError as error:
        raise SystemExit(str(error)) from error
