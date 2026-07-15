#!/usr/bin/env python3
"""Measure coverage of the frozen pure-function set.

Split coverage is keyed by function/file identity from
``data/recovered_sources.json``.

Usage:
  measure_pure_coverage.py <build_dir> [--worst N] [--json OUT]
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
    parser.add_argument("--worst", type=int, default=0)
    parser.add_argument("--json", dest="jsonout", type=Path)
    parser.add_argument(
        "--minimum",
        type=float,
        help="fail when line coverage is below this percentage",
    )
    parser.add_argument(
        "--require-functions",
        type=int,
        help="fail unless the frozen denominator contains exactly this many functions",
    )
    parser.add_argument(
        "--require-zero-uncovered",
        action="store_true",
        help="fail when any function has zero covered executable lines",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    build_dir = args.build_dir.resolve()
    pure_document, functions = load_pure_set(require_manifest=True)
    ranges = split_ranges(functions)
    source_coverage = collect_split_gcov(
        build_dir, {function["source"] for function in functions}
    )
    per_fn = []
    total = covered = 0
    for function in functions:
        source, low, high = ranges[function["name"]]
        executable = source_coverage[source]
        lines = [line for line in range(low, high) if line in executable]
        covered_lines = [line for line in lines if executable[line]]
        per_fn.append((function["name"], len(covered_lines), len(lines)))
        total += len(lines)
        covered += len(covered_lines)
    mode = "split"

    percentage = (100.0 * covered / total) if total else 0.0
    fully_covered = sum(1 for _, count, size in per_fn if size and count == size)
    zero_covered = sum(1 for _, count, size in per_fn if size and count == 0)
    partially_covered = sum(
        1 for _, count, size in per_fn if size and 0 < count < size
    )
    print(f"coverage mode:         {mode}")
    print(f"pure functions:        {len(functions)}")
    print(f"executable lines:      {total}")
    print(f"covered lines:         {covered}")
    print(f"LINE COVERAGE:         {percentage:.2f}%")
    print(f"functions fully cov:   {fully_covered}")
    print(f"functions partial:     {partially_covered}")
    print(f"functions zero cov:    {zero_covered}")

    if args.worst:
        print(f"\n--- {args.worst} least-covered functions (name: covered/exec) ---")
        ranked = sorted(
            (item for item in per_fn if item[2] > 0),
            key=lambda item: (item[1] / item[2], -item[2]),
        )
        for name, count, size in ranked[: args.worst]:
            print(f"  {name}: {count}/{size}")

    if args.jsonout:
        with args.jsonout.open("w", encoding="utf-8", newline="\n") as stream:
            json.dump(
                {
                    "mode": mode,
                    "identity_source": pure_document.get("identity_source"),
                    "pct": percentage,
                    "covered": covered,
                    "total": total,
                    "functions": [
                        {"name": name, "covered": count, "exec": size}
                        for name, count, size in per_fn
                    ],
                },
                stream,
                indent=1,
            )
            stream.write("\n")
    failures = []
    if args.minimum is not None and percentage + 1e-12 < args.minimum:
        failures.append(
            f"coverage {percentage:.2f}% is below required {args.minimum:.2f}%"
        )
    if args.require_functions is not None and len(functions) != args.require_functions:
        failures.append(
            f"function denominator {len(functions)} is not required {args.require_functions}"
        )
    if args.require_zero_uncovered and zero_covered:
        failures.append(f"{zero_covered} frozen functions have zero coverage")
    if failures:
        for failure in failures:
            print(f"coverage gate: FAIL: {failure}")
        return 1
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except CoverageMetadataError as error:
        raise SystemExit(str(error)) from error
