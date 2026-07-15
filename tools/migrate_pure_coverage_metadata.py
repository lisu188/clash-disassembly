#!/usr/bin/env python3
"""Migrate the frozen pure denominator to manifest-backed source identities.

The command is intentionally strict: all 718 frozen functions must be present
exactly once in ``data/recovered_sources.json`` before the checked-in metadata
is rewritten. Split line ranges are derived from their canonical source files
instead of storing aggregate-file line coordinates.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

from coverage_source_manifest import (
    CoverageMetadataError,
    PURE_SET,
    enrich_pure_set,
    load_json,
    load_manifest,
    split_ranges,
)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--check",
        action="store_true",
        help="validate identities and split ranges without rewriting pure_set.json",
    )
    args = parser.parse_args()

    current = load_json(PURE_SET)
    _, manifest_by_name = load_manifest()
    migrated = enrich_pure_set(current, manifest_by_name)
    if migrated["count"] != 718:
        raise CoverageMetadataError(
            f"frozen denominator changed: expected 718, got {migrated['count']}"
        )
    ranges = split_ranges(migrated["functions"])
    if len(ranges) != 718:
        raise CoverageMetadataError(
            f"resolved {len(ranges)} split ranges for the 718-function denominator"
        )
    if args.check and current.get("schema_version", 1) >= 2 and current != migrated:
        raise CoverageMetadataError(
            "checked-in pure coverage metadata is stale; rerun without --check"
        )
    if not args.check:
        with PURE_SET.open("w", encoding="utf-8", newline="\n") as stream:
            json.dump(migrated, stream, indent=1)
            stream.write("\n")
        print(f"wrote 718 manifest-backed identities to {PURE_SET}")
    else:
        print("validated 718 manifest-backed pure functions and split source ranges")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except CoverageMetadataError as error:
        raise SystemExit(str(error)) from error
