#!/usr/bin/env python3

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CASES = ROOT / "tests/unit/cases"
PATTERN = re.compile(r"Lexer_TokenExpect\(([^(),]+)\)")


def main() -> int:
    changed = []
    replacements = 0
    for path in sorted(CASES.glob("test_*.c")):
        text = path.read_text(encoding="utf-8")
        migrated, count = PATTERN.subn(r"Lexer_TokenExpect(0, 0, \1)", text)
        if count:
            path.write_text(migrated, encoding="utf-8", newline="\n")
            changed.append(path.relative_to(ROOT).as_posix())
            replacements += count
    if replacements != 6:
        raise SystemExit(f"expected 6 one-argument Lexer_TokenExpect calls, found {replacements}: {changed}")
    print(f"migrated {replacements} calls in {len(changed)} files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
