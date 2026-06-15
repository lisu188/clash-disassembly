#!/usr/bin/env python3
"""Check local Markdown links in current documentation.

Historical archives intentionally preserve old absolute paths and legacy
references, so docs/archive is skipped unless a file inside it is passed
explicitly.
"""

import argparse
import os
import re
import sys
from pathlib import Path
from urllib.parse import unquote


LINK_RE = re.compile(r"!?\[[^\]]*\]\(([^)]+)\)")


def is_external(target: str) -> bool:
    return (
        "://" in target
        or target.startswith("#")
        or target.startswith("mailto:")
        or target.startswith("/")
    )


def strip_title_and_anchor(target: str) -> str:
    target = target.strip()
    if target.startswith("<") and ">" in target:
        target = target[1 : target.index(">")]
    elif " " in target:
        target = target.split(" ", 1)[0]
    return unquote(target.split("#", 1)[0])


def iter_markdown_files(root: Path, start_paths: list[Path], skip_dirs: set[Path]):
    for start in start_paths:
        if start.is_file():
            yield start
            continue
        for path in start.rglob("*.md"):
            if any(path.is_relative_to(skip) for skip in skip_dirs):
                continue
            yield path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("paths", nargs="*", default=["README.md", "docs"])
    parser.add_argument("--include-archive", action="store_true")
    args = parser.parse_args()

    root = Path.cwd()
    start_paths = [Path(p) for p in args.paths]
    skip_dirs = set()
    if not args.include_archive:
        skip_dirs.add(root / "docs" / "archive")

    failures = []
    for path in sorted(iter_markdown_files(root, start_paths, skip_dirs)):
        text = path.read_text(encoding="utf-8")
        for lineno, line in enumerate(text.splitlines(), 1):
            for match in LINK_RE.finditer(line):
                target = strip_title_and_anchor(match.group(1))
                if not target or is_external(target):
                    continue
                resolved = (path.parent / target).resolve()
                try:
                    resolved.relative_to(root.resolve())
                except ValueError:
                    failures.append((path, lineno, target, "escapes repository"))
                    continue
                if not resolved.exists():
                    failures.append((path, lineno, target, "missing target"))

    for path, lineno, target, reason in failures:
        print(f"{path}:{lineno}: {target}: {reason}", file=sys.stderr)
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
