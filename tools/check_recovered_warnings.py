#!/usr/bin/env python3
"""Check recovered-source compiler warnings against a ratcheted baseline.

The input is ordinary GCC or Clang build output.  Warning diagnostics emitted
for files below the configured recovered-source prefixes are grouped by their
``[-Woption]`` suffix.  Compiler diagnostics without an option are retained in
an explicit ``<compiler>/unknown`` bucket instead of being silently ignored.

Examples::

    python3 tools/check_recovered_warnings.py build/gcc.log --compiler gcc
    python3 tools/check_recovered_warnings.py build/clang.log --compiler clang \
        --mode report
    python3 tools/check_recovered_warnings.py build/gcc.log --compiler gcc \
        --mode update
"""

from __future__ import annotations

import argparse
import json
import posixpath
import re
import sys
from collections import Counter
from pathlib import Path
from typing import Any, Iterable


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BASELINE = ROOT / "data" / "recovered_warning_baseline.json"
DEFAULT_SOURCE_PREFIXES = ("src/recovered/",)
SUPPORTED_COMPILERS = ("gcc", "clang")

DIAGNOSTIC_RE = re.compile(
    r"^(?P<origin>.*?)(?::(?P<line>\d+)(?::(?P<column>\d+))?)?:\s*"
    r"warning:\s*(?P<message>.*)$"
)
OPTION_RE = re.compile(r"\[(-W[^\]\s]+)\](?:\s|$)")
GCC_DRIVER_RE = re.compile(r"(?:^|[/\\])(?:gcc|cc1)(?:\.exe)?$", re.IGNORECASE)
CLANG_DRIVER_RE = re.compile(
    r"(?:^|[/\\])clang(?:-[^/\\:]+)?(?:\.exe)?$", re.IGNORECASE
)


class BaselineError(ValueError):
    """Raised when the warning baseline is missing or malformed."""


def normalized_path(value: str) -> str:
    """Return a slash-normalized path suitable for prefix matching."""

    return posixpath.normpath(value.strip().replace("\\", "/"))


def is_recovered_origin(origin: str, source_prefixes: Iterable[str]) -> bool:
    path = normalized_path(origin)
    padded_path = f"/{path.strip('/')}/"
    return any(
        f"/{normalized_path(prefix).strip('/')}/" in padded_path
        for prefix in source_prefixes
    )


def is_compiler_origin(origin: str, compiler: str) -> bool:
    origin = origin.strip()
    if compiler == "gcc":
        return bool(GCC_DRIVER_RE.search(origin))
    return bool(CLANG_DRIVER_RE.search(origin))


def detect_compiler(text: str) -> str:
    """Detect a compiler only when the build output provides clear evidence."""

    clang = bool(re.search(r"\bclang(?:\s+version|-\d+|\.exe)\b", text, re.IGNORECASE))
    gcc = bool(
        re.search(r"\b(?:gcc|GNU C)(?:\s+version|-\d+|\.exe)\b", text, re.IGNORECASE)
    )
    if clang == gcc:
        raise BaselineError(
            "could not unambiguously detect GCC or Clang; pass --compiler gcc "
            "or --compiler clang"
        )
    return "clang" if clang else "gcc"


def warning_counts(
    text: str, compiler: str, source_prefixes: Iterable[str]
) -> tuple[Counter[str], int]:
    """Parse warning categories and return counts plus ignored warning lines."""

    counts: Counter[str] = Counter()
    ignored = 0
    for raw_line in text.splitlines():
        match = DIAGNOSTIC_RE.match(raw_line.strip())
        if match is None:
            continue

        origin = match.group("origin")
        if not (
            is_recovered_origin(origin, source_prefixes)
            or is_compiler_origin(origin, compiler)
        ):
            ignored += 1
            continue

        option_matches = OPTION_RE.findall(match.group("message"))
        category = option_matches[-1] if option_matches else f"{compiler}/unknown"
        counts[category] += 1
    return counts, ignored


def empty_baseline(source_prefixes: Iterable[str]) -> dict[str, Any]:
    return {
        "schema_version": 1,
        "source_prefixes": list(source_prefixes),
        "profiles": {
            compiler: {
                "status": "unseeded",
                "total": 0,
                "warnings": {},
            }
            for compiler in SUPPORTED_COMPILERS
        },
    }


def load_baseline(path: Path, *, allow_missing: bool) -> dict[str, Any]:
    if not path.exists():
        if allow_missing:
            return empty_baseline(DEFAULT_SOURCE_PREFIXES)
        raise BaselineError(f"warning baseline does not exist: {path}")

    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        raise BaselineError(f"cannot read warning baseline {path}: {exc}") from exc

    if not isinstance(data, dict) or data.get("schema_version") != 1:
        raise BaselineError("warning baseline must be an object with schema_version 1")
    prefixes = data.get("source_prefixes")
    if not isinstance(prefixes, list) or not prefixes or not all(
        isinstance(item, str) and item for item in prefixes
    ):
        raise BaselineError("source_prefixes must be a non-empty string array")
    profiles = data.get("profiles")
    if not isinstance(profiles, dict):
        raise BaselineError("profiles must be an object")

    for compiler, profile in profiles.items():
        if compiler not in SUPPORTED_COMPILERS or not isinstance(profile, dict):
            raise BaselineError(f"invalid compiler profile: {compiler!r}")
        if profile.get("status") not in {"seeded", "unseeded"}:
            raise BaselineError(f"{compiler} profile has an invalid status")
        warnings = profile.get("warnings")
        if not isinstance(warnings, dict) or not all(
            isinstance(key, str)
            and key
            and isinstance(value, int)
            and not isinstance(value, bool)
            and value >= 0
            for key, value in warnings.items()
        ):
            raise BaselineError(f"{compiler} warnings must map categories to counts")
        total = profile.get("total")
        if total != sum(warnings.values()):
            raise BaselineError(f"{compiler} total does not match its warning counts")
    return data


def read_logs(paths: list[Path]) -> str:
    chunks: list[str] = []
    if not paths:
        chunks.append(sys.stdin.read())
    for path in paths:
        try:
            chunks.append(path.read_text(encoding="utf-8", errors="replace"))
        except OSError as exc:
            raise BaselineError(f"cannot read compiler log {path}: {exc}") from exc
    return "\n".join(chunks)


def comparison_rows(
    current: Counter[str], baseline: dict[str, int]
) -> list[tuple[str, int, int, int]]:
    return [
        (category, current.get(category, 0), baseline.get(category, 0),
         current.get(category, 0) - baseline.get(category, 0))
        for category in sorted(set(current) | set(baseline))
    ]


def print_report(
    compiler: str,
    current: Counter[str],
    baseline: dict[str, int] | None,
    ignored: int,
) -> list[tuple[str, int, int, int]]:
    print(
        f"{compiler}: {sum(current.values())} recovered warning(s) in "
        f"{len(current)} category/categories"
    )
    if ignored:
        print(f"ignored {ignored} warning(s) outside recovered-source scope")

    if baseline is None:
        for category, count in sorted(current.items()):
            print(f"  {category}: {count}")
        return []

    rows = comparison_rows(current, baseline)
    for category, count, limit, delta in rows:
        marker = "INCREASE" if delta > 0 else "decrease" if delta < 0 else "same"
        print(
            f"  {category}: current={count} baseline={limit} "
            f"delta={delta:+d} ({marker})"
        )
    return rows


def update_profile(
    baseline: dict[str, Any], compiler: str, current: Counter[str]
) -> None:
    profiles = baseline.setdefault("profiles", {})
    for supported in SUPPORTED_COMPILERS:
        profiles.setdefault(
            supported, {"status": "unseeded", "total": 0, "warnings": {}}
        )
    profiles[compiler] = {
        "status": "seeded",
        "total": sum(current.values()),
        "warnings": dict(sorted(current.items())),
    }


def write_baseline(path: Path, baseline: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(baseline, indent=2) + "\n", encoding="utf-8")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "logs",
        nargs="*",
        type=Path,
        help="compiler build logs (reads standard input when omitted)",
    )
    parser.add_argument(
        "--baseline", type=Path, default=DEFAULT_BASELINE,
        help=f"baseline JSON (default: {DEFAULT_BASELINE.relative_to(ROOT)})",
    )
    parser.add_argument(
        "--compiler", choices=("auto", *SUPPORTED_COMPILERS), default="auto",
        help="compiler that produced the log; auto requires an identifiable version/command",
    )
    parser.add_argument(
        "--mode", choices=("check", "report", "update"), default="check",
        help="check the ratchet, report without failing, or replace one compiler profile",
    )
    parser.add_argument(
        "--source-prefix",
        action="append",
        dest="source_prefixes",
        help="source path fragment to include (repeatable; defaults to baseline scope)",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        baseline = load_baseline(
            args.baseline, allow_missing=args.mode == "update"
        )
        text = read_logs(args.logs)
        compiler = detect_compiler(text) if args.compiler == "auto" else args.compiler
        source_prefixes = args.source_prefixes or baseline["source_prefixes"]
        current, ignored = warning_counts(text, compiler, source_prefixes)

        if args.mode == "update":
            baseline["source_prefixes"] = list(source_prefixes)
            update_profile(baseline, compiler, current)
            write_baseline(args.baseline, baseline)
            print_report(compiler, current, None, ignored)
            print(f"updated warning baseline: {args.baseline}")
            return 0

        profile = baseline.get("profiles", {}).get(compiler)
        if not isinstance(profile, dict) or profile.get("status") != "seeded":
            if args.mode == "report":
                print_report(compiler, current, None, ignored)
                print(f"report: {compiler} warning profile is unseeded")
                return 0
            raise BaselineError(
                f"{compiler} warning profile is unseeded; run with --mode update "
                "using a reviewed compiler log"
            )
        expected = profile["warnings"]
        rows = print_report(compiler, current, expected, ignored)
        increases = [row for row in rows if row[3] > 0]

        if args.mode == "report":
            if increases:
                print(f"report: {len(increases)} category increase(s) observed")
            else:
                print("report: no warning category increased")
            return 0

        if increases:
            print(
                f"FAIL: recovered warning ratchet increased in {len(increases)} "
                "category/categories",
                file=sys.stderr,
            )
            return 1
        print("PASS: recovered warnings did not increase")
        return 0
    except BaselineError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
