#!/usr/bin/env python3

from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPLACEMENTS = {
    "tests/unit/cases/test_cov2_09.c": (
        "TOUCH(Rules_FindFactByIndex());",
        "TOUCH(Rules_FindFactByIndex(0));",
    ),
    "tests/unit/cases/test_cov3_02.c": (
        "TOUCH(Rules_FindFactByIndex());",
        "TOUCH(Rules_FindFactByIndex(222));",
    ),
}


def main() -> int:
    for relative, (old, new) in REPLACEMENTS.items():
        path = ROOT / relative
        text = path.read_text(encoding="utf-8")
        count = text.count(old)
        if count != 1:
            raise SystemExit(f"expected one stale call in {relative}, found {count}")
        path.write_text(text.replace(old, new), encoding="utf-8", newline="\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
