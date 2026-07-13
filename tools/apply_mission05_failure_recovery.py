#!/usr/bin/env python3

from pathlib import Path


def replace_once(text: str, old: str, new: str, label: str) -> str:
    count = text.count(old)
    if count != 1:
        raise RuntimeError(f"{label}: expected one match, found {count}")
    return text.replace(old, new, 1)


def replace_exact_count(text: str, old: str, new: str, expected: int, label: str) -> str:
    count = text.count(old)
    if count != expected:
        raise RuntimeError(f"{label}: expected {expected} matches, found {count}")
    return text.replace(old, new)


def update_file(path: str, transform) -> None:
    file_path = Path(path)
    original = file_path.read_text(encoding="utf-8")
    updated = transform(original)
    if updated == original:
        raise RuntimeError(f"{path}: transform made no changes")
    file_path.write_text(updated, encoding="utf-8")


def update_clash95(text: str) -> str:
    text = replace_once(
        text,
        "#define ACTIVE_MISSION_INDEX_OFFSET 140017\n#define GAME_TURN_COUNTER_OFFSET 140022",
        "#define ACTIVE_MISSION_INDEX_OFFSET 140017\n#define MISSION_FAILURE_FLAG_OFFSET 140021\n#define GAME_TURN_COUNTER_OFFSET 140022",
        "mission failure offset",
    )
    text = replace_once(
        text,
        "#define ACTIVE_MISSION_INDEX (*(_DWORD *)(gameData + ACTIVE_MISSION_INDEX_OFFSET))\n#define GAME_TURN_COUNTER (*(_WORD *)(gameData + GAME_TURN_COUNTER_OFFSET))",
        "#define ACTIVE_MISSION_INDEX (*(_DWORD *)(gameData + ACTIVE_MISSION_INDEX_OFFSET))\n#define MISSION_FAILURE_FLAG (*((unsigned __int8 *)(gameData + MISSION_FAILURE_FLAG_OFFSET)))\n#define GAME_TURN_COUNTER (*(_WORD *)(gameData + GAME_TURN_COUNTER_OFFSET))",
        "mission failure accessor",
    )
    text = replace_exact_count(
        text,
        "Mission_MarkObjective05CompleteOnAttack",
        "Mission05_MarkFailureOnFriendlyAttack",
        4,
        "mission 05 helper rename",
    )
    text = replace_exact_count(
        text,
        "UI_CheckDialogAccepted",
        "Mission_CheckFailureCondition",
        3,
        "mission failure dispatcher rename",
    )
    old_body = """int  Mission05_MarkFailureOnFriendlyAttack(int result, int a2)
{
  if ( g_LanguageIndex && !result && (a2 == 1 || a2 == 2) )
  {
    result = gameData;
    *(_BYTE *)(gameData + 140021) = 1;
  }
  return result;
}"""
    new_body = """int  Mission05_MarkFailureOnFriendlyAttack(int result, int target_owner_index)
{
  if ( g_LanguageIndex && !result && (target_owner_index == 1 || target_owner_index == 2) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      \"mission05_failure_friendly_attack\",
      g_SelectedUnitIndex,
      result,
      target_owner_index,
      GAME_TURN_COUNTER);
    result = gameData;
    MISSION_FAILURE_FLAG = 1;
  }
  return result;
}"""
    text = replace_once(text, old_body, new_body, "mission 05 helper body")
    text = replace_exact_count(
        text,
        "return *(unsigned __int8 *)(gameData + 140021);",
        "return MISSION_FAILURE_FLAG;",
        2,
        "mission failure reads",
    )
    text = replace_exact_count(
        text,
        "*(_BYTE *)(gameData + 140021) = 1;",
        "MISSION_FAILURE_FLAG = 1;",
        1,
        "mission 15 failure write",
    )
    return text


def update_tests(text: str) -> str:
    marker = "TEST(objectives, mission05_friendly_attack_sets_failure_condition)"
    if marker in text:
        raise RuntimeError("mission 05 failure tests already present")
    addition = r'''

TEST(objectives, mission05_friendly_attack_sets_failure_condition) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  CHECK_EQ(Mission_CheckFailureCondition(), 0);
  Mission05_MarkFailureOnFriendlyAttack(0, 1);
  CHECK_EQ(MISSION_FAILURE_FLAG, 1);
  CHECK_EQ(Mission_CheckFailureCondition(), 1);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_failure_ignores_enemy_attack_and_zero_language) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  Mission05_MarkFailureOnFriendlyAttack(0, 3);
  Mission05_MarkFailureOnFriendlyAttack(1, 2);
  CHECK_EQ(MISSION_FAILURE_FLAG, 0);
  CHECK_EQ(Mission_CheckFailureCondition(), 0);
  cov_m05_reset(0);
  Mission05_MarkFailureOnFriendlyAttack(0, 1);
  CHECK_EQ(MISSION_FAILURE_FLAG, 0);
  CHECK_EQ(Mission_CheckFailureCondition(), 0);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}
'''
    return text.rstrip() + addition


def update_status(text: str) -> str:
    text = text.replace("Last consolidated: 2026-07-12.", "Last consolidated: 2026-07-13.")
    text = replace_once(
        text,
        "`UI_CheckDialogAccepted` separately treats a player-0 attack on players `1`\nor `2` as mission failure.",
        "`Mission_CheckFailureCondition` separately reads the mission failure flag set\nby `Mission05_MarkFailureOnFriendlyAttack` when player `0` attacks players `1`\nor `2`.",
        "status mission 05 failure description",
    )
    validation = """## Latest Validation

2026-07-13 mission-05 failure-predicate recovery:

- renamed the reached attack helper to `Mission05_MarkFailureOnFriendlyAttack` and the defeat dispatcher to `Mission_CheckFailureCondition`;
- introduced the recovered `MISSION_FAILURE_FLAG` accessor for `gameData + 140021` and preserved mission-05/mission-15 flag behavior;
- added a trace-gated `mission05_failure_friendly_attack` marker with attacker owner, target owner, selected stack, and turn evidence;
- added asset-independent tests for the active nonzero-language failure branch and its zero-language/enemy-attack exclusions.

"""
    return replace_once(text, "## Latest Validation\n\n", validation, "status latest validation")


def update_structures(text: str) -> str:
    text = replace_exact_count(
        text,
        '"Mission_MarkObjective05CompleteOnAttack"',
        '"Mission05_MarkFailureOnFriendlyAttack"',
        1,
        "structure helper participant",
    )
    text = replace_exact_count(
        text,
        '"UI_CheckDialogAccepted"',
        '"Mission_CheckFailureCondition"',
        1,
        "structure dispatcher participant",
    )
    text = replace_once(
        text,
        "Mission_MarkObjective05CompleteOnAttack sets the mission-local byte when player 0 attacks player 1 or 2 in the nonzero-language branch; UI_CheckDialogAccepted reads that byte as the mission-ending failure condition before the objective-complete check.",
        "Mission05_MarkFailureOnFriendlyAttack sets the mission-local failure byte when player 0 attacks player 1 or 2 in the nonzero-language branch; Mission_CheckFailureCondition reads that byte before the objective-complete check.",
        "structure evidence names",
    )
    return text


def prepend_section(text: str, title: str, body: str) -> str:
    marker = title + "\n\n"
    return replace_once(text, marker, marker + body.rstrip() + "\n\n", title)


def main() -> None:
    update_file("clash95.c", update_clash95)
    update_file("tests/unit/cases/test_gameplay_objectives.c", update_tests)
    update_file("docs/STATUS.md", update_status)
    update_file("RECOVERED_STRUCTURES.json", update_structures)
    update_file(
        "docs/archive/SUB_RENAME_INDEX.md",
        lambda text: replace_exact_count(
            replace_exact_count(
                text,
                "Mission_MarkObjective05CompleteOnAttack",
                "Mission05_MarkFailureOnFriendlyAttack",
                1,
                "rename index mission 05",
            ),
            "UI_CheckDialogAccepted",
            "Mission_CheckFailureCondition",
            1,
            "rename index failure dispatcher",
        ),
    )
    update_file(
        "docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md",
        lambda text: prepend_section(
            text,
            "# Reverse Engineering Rename Log",
            """## 2026-07-13 - Mission 05 failure-predicate recovery

- `Mission_MarkObjective05CompleteOnAttack` -> `Mission05_MarkFailureOnFriendlyAttack`: the helper does not mark objective completion. In the nonzero-language branch it sets `gameData + 140021` only when player `0` attacks player `1` or `2`.
- `UI_CheckDialogAccepted` -> `Mission_CheckFailureCondition`: the switch is the campaign defeat-condition dispatcher called before objective completion checks.
- Added `MISSION_FAILURE_FLAG_OFFSET` / `MISSION_FAILURE_FLAG` for the shared mission-local byte used by missions `05` and `15`.
- Added the trace-gated `mission05_failure_friendly_attack` marker without changing objective, ownership, combat, or turn state.""",
        ),
    )
    update_file(
        "docs/archive/COMPILATION_PROGRESS.md",
        lambda text: prepend_section(
            text,
            "# Compilation Progress",
            """## 2026-07-13 - Mission 05 failure-predicate recovery

- Current frontier: mission `05` authentic completion without attacking allied players `1` or `2`.
- Recovered semantics: renamed the mission-05 friendly-attack helper and the shared mission failure-condition dispatcher; introduced a named accessor for `gameData + 140021`.
- Observability: added a trace-gated marker when the active nonzero-language mission-05 branch records a forbidden player-0 attack against player `1` or `2`.
- Regression coverage: added asset-independent tests proving the failure flag is set only for the recovered friendly-attack condition and remains clear for player `3`, non-player-0 attackers, and the zero-language branch.""",
        ),
    )

    for path in (
        ".github/workflows/mission05-source-inspect.yml",
        "tools/mission05_source_inspect.py",
        ".github/workflows/mission05-apply-recovery.yml",
        "tools/apply_mission05_failure_recovery.py",
    ):
        candidate = Path(path)
        if candidate.exists():
            candidate.unlink()


if __name__ == "__main__":
    main()
