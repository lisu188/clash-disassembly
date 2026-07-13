#!/usr/bin/env python3

from pathlib import Path
import re

SOURCE = Path("clash95.c")
TARGETS = [
    "Mission_CheckObjectiveComplete",
    "UI_CheckDialogAccepted",
    "Mission_MarkObjective05CompleteOnAttack",
    "Unit_Attack",
    "Unit_AttackBuilding",
    "WorldMap_RunHumanTurnLoop",
]


def extract_function(text: str, name: str) -> str:
    pattern = re.compile(r"(?m)^.*\b" + re.escape(name) + r"\s*\([^;\n]*$")
    for match in pattern.finditer(text):
        start = text.rfind("\n", 0, match.start()) + 1
        brace = text.find("{", match.end())
        semicolon = text.find(";", match.end(), brace if brace >= 0 else len(text))
        if brace < 0 or semicolon >= 0:
            continue
        depth = 0
        i = brace
        in_string = False
        in_char = False
        escaped = False
        while i < len(text):
            ch = text[i]
            if escaped:
                escaped = False
            elif ch == "\\" and (in_string or in_char):
                escaped = True
            elif ch == '"' and not in_char:
                in_string = not in_string
            elif ch == "'" and not in_string:
                in_char = not in_char
            elif not in_string and not in_char:
                if ch == "{":
                    depth += 1
                elif ch == "}":
                    depth -= 1
                    if depth == 0:
                        return text[start : i + 1]
            i += 1
    return "<not found>"


def main() -> None:
    text = SOURCE.read_text(encoding="utf-8", errors="replace")
    for name in TARGETS:
        print(f"\n===== {name} =====")
        print(extract_function(text, name))
    print("\n===== mission-05 related references =====")
    for line_number, line in enumerate(text.splitlines(), 1):
        if any(token in line for token in ("Mission05", "mission05", "Objective05", "g_LanguageIndex")):
            print(f"{line_number}: {line}")


if __name__ == "__main__":
    main()
