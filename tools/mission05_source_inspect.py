#!/usr/bin/env python3

from pathlib import Path

SOURCE = Path("clash95.c")
OUTPUT = Path("mission05-source-slices.txt")
START_LINE = 73060
END_LINE = 73790


def main() -> None:
    lines = SOURCE.read_text(encoding="utf-8", errors="replace").splitlines()
    selected = []
    for line_number in range(START_LINE, min(END_LINE, len(lines)) + 1):
        selected.append(f"{line_number}: {lines[line_number - 1]}")
    OUTPUT.write_text("\n".join(selected) + "\n", encoding="utf-8")
    print(f"{OUTPUT} {OUTPUT.stat().st_size} bytes")


if __name__ == "__main__":
    main()
