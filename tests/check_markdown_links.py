#!/usr/bin/env python3
"""Lightweight local Markdown link/path checker.

The checker focuses on current navigation docs. It skips archived historical
notes so old batch entries can keep the paths that were true when written.
"""

from __future__ import annotations

import re
import subprocess
import sys
import urllib.parse
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
SKIP_PREFIXES = (
    ".agent/",
    ".agents/",
    ".worktrees/",
    "docs/archive/",
)
MARKDOWN_LINK_RE = re.compile(r"!?\[[^\]]*\]\(([^)]+)\)")
BACKTICK_PATH_RE = re.compile(r"`([^`\s]+?\.(?:md|json|sh|py|cpp|c|h|csv|env|script))`")
URL_RE = re.compile(r"^[a-zA-Z][a-zA-Z0-9+.-]*:")


def git_markdown_files(*args: str) -> set[Path]:
    result = subprocess.run(
        ["git", "ls-files", *args, "--", "*.md"],
        cwd=REPO_ROOT,
        check=True,
        text=True,
        capture_output=True,
    )
    files: set[Path] = set()
    for line in result.stdout.splitlines():
        if line.startswith(SKIP_PREFIXES):
            continue
        files.add(REPO_ROOT / line)
    return files


def markdown_files() -> list[Path]:
    files = git_markdown_files()
    files.update(git_markdown_files("--others", "--exclude-standard"))
    return sorted(files)


def clean_target(target: str) -> str | None:
    target = target.strip()
    if not target or target.startswith("#"):
        return None
    target = target.split("#", 1)[0]
    target = target.split("?", 1)[0]
    target = target.strip()
    if not target or URL_RE.match(target):
        return None
    if target.startswith("/"):
        return None
    return urllib.parse.unquote(target)


def path_exists(source: Path, target: str, root_relative: bool) -> bool:
    if root_relative:
        candidates = [REPO_ROOT / target]
    else:
        candidates = [source.parent / target, REPO_ROOT / target]
    return any(candidate.exists() for candidate in candidates)


def check_file(path: Path) -> list[str]:
    rel = path.relative_to(REPO_ROOT)
    text = path.read_text(encoding="utf-8")
    errors: list[str] = []

    for match in MARKDOWN_LINK_RE.finditer(text):
        target = clean_target(match.group(1))
        if target and not path_exists(path, target, root_relative=False):
            errors.append(f"{rel}: missing Markdown link target: {target}")

    for match in BACKTICK_PATH_RE.finditer(text):
        target = clean_target(match.group(1))
        if target and not path_exists(path, target, root_relative=False):
            errors.append(f"{rel}: missing referenced path: {target}")

    return errors


def main() -> int:
    errors: list[str] = []
    for path in markdown_files():
        errors.extend(check_file(path))

    if errors:
        for error in errors:
            print(error)
        return 1

    print("markdown link/path check passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
