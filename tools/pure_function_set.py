#!/usr/bin/env python3
"""Emit the frozen manifest-backed pure-function coverage denominator.

The 718-function set is intentionally frozen.  This command validates that
every identity still resolves exactly once in the generated split sources and
then emits the schema-v2 metadata.  It does not rediscover a new denominator
from source heuristics, which could silently change the historical coverage
floor during cleanup.
"""

from __future__ import annotations

import json

from coverage_source_manifest import (
    CoverageMetadataError,
    load_pure_set,
    split_ranges,
)


def main() -> int:
    document, functions = load_pure_set(require_manifest=True)
    if len(functions) != 718:
        raise CoverageMetadataError(
            f"frozen denominator changed: expected 718, got {len(functions)}"
        )
    ranges = split_ranges(functions)
    if len(ranges) != 718:
        raise CoverageMetadataError(
            f"resolved {len(ranges)} source ranges for 718 frozen functions"
        )
    print(json.dumps(document, indent=1))
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except CoverageMetadataError as error:
        raise SystemExit(str(error)) from error
