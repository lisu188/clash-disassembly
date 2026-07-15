#!/usr/bin/env python3
"""Audit independently compiled unit/coverage case sources.

The split build discovers ``tests/unit/cases/test_*.c`` directly in CMake;
there is no generated ``test_all.c`` include block anymore.  This command is
therefore deliberately read-only: it inventories case files and verifies that
the CMake registration remains independent and that no unit source includes a
``.c`` implementation.

Usage:
  python3 tools/wire_cov_cases.py [--json]
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CASE_DIR = ROOT / "tests" / "unit" / "cases"
CMAKE = ROOT / "CMakeLists.txt"
LEGACY_AGGREGATE = ROOT / "tests" / "unit" / "test_all.c"

TEST_RE = re.compile(
    r"(?m)^\s*TEST\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*,\s*"
    r"([A-Za-z_][A-Za-z0-9_]*)\s*\)"
)
C_INCLUDE_RE = re.compile(r'(?m)^\s*#\s*include\s*[<\"]([^>\"]+\.c)[>\"]')


def repo_path(path: Path) -> str:
    return path.relative_to(ROOT).as_posix()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--json", action="store_true", help="emit the complete inventory as JSON"
    )
    args = parser.parse_args()

    errors: list[str] = []
    cases = sorted(CASE_DIR.glob("test_*.c"))
    if not cases:
        errors.append("no tests/unit/cases/test_*.c sources found")

    cmake = CMAKE.read_text(encoding="utf-8")
    if not re.search(
        r"file\s*\(\s*GLOB\s+CLASH95_UNIT_CASE_SOURCES\b[\s\S]*?"
        r"tests/unit/cases/test_\*\.c\s*\)",
        cmake,
    ):
        errors.append("CMake does not glob test_*.c into CLASH95_UNIT_CASE_SOURCES")
    if "${CLASH95_UNIT_CASE_SOURCES}" not in cmake:
        errors.append("CMake does not add CLASH95_UNIT_CASE_SOURCES to the unit target")
    if LEGACY_AGGREGATE.exists():
        errors.append("legacy tests/unit/test_all.c aggregate still exists")

    inventory: list[dict[str, object]] = []
    owners: dict[str, str] = {}
    for case in cases:
        text = case.read_text(encoding="utf-8")
        included_c = C_INCLUDE_RE.findall(text)
        if included_c:
            errors.append(
                f"{repo_path(case)} includes C source(s): {', '.join(included_c)}"
            )

        tests = [f"{suite}.{name}" for suite, name in TEST_RE.findall(text)]
        if not tests:
            errors.append(f"{repo_path(case)} declares no TEST(...) cases")
        for test in tests:
            previous = owners.setdefault(test, repo_path(case))
            if previous != repo_path(case):
                errors.append(
                    f"duplicate TEST({test}) in {previous} and {repo_path(case)}"
                )
        inventory.append(
            {"source": repo_path(case), "test_count": len(tests), "tests": tests}
        )

    payload = {
        "ok": not errors,
        "compilation_model": "independent-c17-translation-units",
        "case_source_count": len(cases),
        "test_count": sum(int(item["test_count"]) for item in inventory),
        "cases": inventory,
        "errors": errors,
    }
    if args.json:
        print(json.dumps(payload, indent=2))
    else:
        print(
            "coverage case audit: "
            f"{payload['case_source_count']} sources, {payload['test_count']} tests, "
            f"{'ok' if payload['ok'] else 'FAILED'}"
        )
        for error in errors:
            print(f"error: {error}")
    return 0 if payload["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
