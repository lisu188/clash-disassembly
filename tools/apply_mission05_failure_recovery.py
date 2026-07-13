#!/usr/bin/env python3

from pathlib import Path


def replace_once(text, old, new, label):
    count = text.count(old)
    if count != 1:
        raise RuntimeError("%s: expected one match, found %d" % (label, count))
    return text.replace(old, new, 1)


def replace_count(text, old, new, expected, label):
    count = text.count(old)
    if count != expected:
        raise RuntimeError("%s: expected %d matches, found %d" % (label, expected, count))
    return text.replace(old, new)


def write_changed(path, updated):
    file_path = Path(path)
    original = file_path.read_text(encoding="utf-8")
    if updated == original:
        raise RuntimeError("%s: no changes" % path)
    file_path.write_text(updated, encoding="utf-8")


def patch_clash95():
    path = Path("clash95.c")
    text = path.read_text(encoding="utf-8")
    text = replace_once(
        text,
        "#define ACTIVE_MISSION_INDEX_OFFSET 140017\n#define GAME_TURN_COUNTER_OFFSET 140022",
        "#define ACTIVE_MISSION_INDEX_OFFSET 140017\n#define MISSION_FAILURE_FLAG_OFFSET 140021\n#define GAME_TURN_COUNTER_OFFSET 140022",
        "failure flag offset",
    )
    text = replace_once(
        text,
        "#define ACTIVE_MISSION_INDEX (*(_DWORD *)(gameData + ACTIVE_MISSION_INDEX_OFFSET))\n#define GAME_TURN_COUNTER (*(_WORD *)(gameData + GAME_TURN_COUNTER_OFFSET))",
        "#define ACTIVE_MISSION_INDEX (*(_DWORD *)(gameData + ACTIVE_MISSION_INDEX_OFFSET))\n#define MISSION_FAILURE_FLAG (*((unsigned __int8 *)(gameData + MISSION_FAILURE_FLAG_OFFSET)))\n#define GAME_TURN_COUNTER (*(_WORD *)(gameData + GAME_TURN_COUNTER_OFFSET))",
        "failure flag accessor",
    )
    text = replace_count(
        text,
        "Mission_MarkObjective05CompleteOnAttack",
        "Mission05_MarkFailureOnFriendlyAttack",
        4,
        "mission 05 helper rename",
    )
    text = replace_count(
        text,
        "UI_CheckDialogAccepted",
        "Mission_CheckFailureCondition",
        3,
        "failure dispatcher rename",
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
    text = replace_count(
        text,
        "return *(unsigned __int8 *)(gameData + 140021);",
        "return MISSION_FAILURE_FLAG;",
        2,
        "failure flag reads",
    )
    text = replace_count(
        text,
        "*(_BYTE *)(gameData + 140021) = 1;",
        "MISSION_FAILURE_FLAG = 1;",
        1,
        "mission 15 failure write",
    )
    path.write_text(text, encoding="utf-8")


def patch_tests():
    path = Path("tests/unit/cases/test_gameplay_objectives.c")
    text = path.read_text(encoding="utf-8").rstrip()
    marker = "TEST(objectives, mission05_friendly_attack_sets_failure_condition)"
    if marker in text:
        raise RuntimeError("mission 05 failure tests already present")
    text += r'''

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
    path.write_text(text, encoding="utf-8")


def patch_metadata():
    path = Path("RECOVERED_STRUCTURES.json")
    text = path.read_text(encoding="utf-8")
    text = replace_count(text, '"Mission_MarkObjective05CompleteOnAttack"', '"Mission05_MarkFailureOnFriendlyAttack"', 1, "metadata helper")
    text = replace_count(text, '"UI_CheckDialogAccepted"', '"Mission_CheckFailureCondition"', 1, "metadata dispatcher")
    text = replace_once(
        text,
        "Mission_MarkObjective05CompleteOnAttack sets the mission-local byte when player 0 attacks player 1 or 2 in the nonzero-language branch; UI_CheckDialogAccepted reads that byte as the mission-ending failure condition before the objective-complete check.",
        "Mission05_MarkFailureOnFriendlyAttack sets the mission-local failure byte when player 0 attacks player 1 or 2 in the nonzero-language branch; Mission_CheckFailureCondition reads that byte before the objective-complete check.",
        "metadata evidence",
    )
    path.write_text(text, encoding="utf-8")


def patch_status():
    path = Path("docs/STATUS.md")
    text = path.read_text(encoding="utf-8")
    text = text.replace("Last consolidated: 2026-07-12.", "Last consolidated: 2026-07-13.")
    text = replace_once(
        text,
        "`UI_CheckDialogAccepted` separately treats a player-0 attack on players `1`\nor `2` as mission failure.",
        "`Mission_CheckFailureCondition` reads the mission failure flag set by\n`Mission05_MarkFailureOnFriendlyAttack` when player `0` attacks players `1` or\n`2`.",
        "status failure description",
    )
    section = """## Latest Validation

2026-07-13 mission-05 failure-predicate recovery:

- renamed the misidentified attack helper to `Mission05_MarkFailureOnFriendlyAttack` and the defeat dispatcher to `Mission_CheckFailureCondition`;
- introduced `MISSION_FAILURE_FLAG` for `gameData + 140021` while preserving mission-05 and mission-15 behavior;
- added the trace-gated `mission05_failure_friendly_attack` marker;
- added asset-independent tests for the friendly-attack failure branch and its exclusions.

"""
    text = replace_once(text, "## Latest Validation\n\n", section, "latest validation")
    path.write_text(text, encoding="utf-8")


def patch_index_and_logs():
    path = Path("docs/archive/SUB_RENAME_INDEX.md")
    text = path.read_text(encoding="utf-8")
    text = replace_count(text, "Mission_MarkObjective05CompleteOnAttack", "Mission05_MarkFailureOnFriendlyAttack", 1, "rename index helper")
    text = replace_count(text, "UI_CheckDialogAccepted", "Mission_CheckFailureCondition", 1, "rename index dispatcher")
    path.write_text(text, encoding="utf-8")

    path = Path("docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md")
    text = path.read_text(encoding="utf-8")
    entry = """# Reverse Engineering Rename Log

## 2026-07-13 - Mission 05 failure-predicate recovery

- `Mission_MarkObjective05CompleteOnAttack` -> `Mission05_MarkFailureOnFriendlyAttack`: the helper sets the mission-local failure byte when player `0` attacks player `1` or `2`; it does not complete the objective.
- `UI_CheckDialogAccepted` -> `Mission_CheckFailureCondition`: the switch dispatches campaign defeat conditions before objective checks.
- Added `MISSION_FAILURE_FLAG_OFFSET` / `MISSION_FAILURE_FLAG` for `gameData + 140021` and a trace-gated mission-05 friendly-attack marker.

"""
    text = replace_once(text, "# Reverse Engineering Rename Log\n\n", entry, "rename log heading")
    path.write_text(text, encoding="utf-8")

    path = Path("docs/archive/COMPILATION_PROGRESS.md")
    text = path.read_text(encoding="utf-8")
    entry = """# Compilation Progress

## 2026-07-13 - Mission 05 failure-predicate recovery

- Corrected two reached semantic names in the mission-05 defeat path and named the shared mission failure byte at `gameData + 140021`.
- Added read-only failure tracing plus asset-independent regression coverage; no objective, combat, ownership, or turn behavior was changed.

"""
    text = replace_once(text, "# Compilation Progress\n\n", entry, "compilation log heading")
    path.write_text(text, encoding="utf-8")


def cleanup_helpers():
    for name in (
        ".github/workflows/mission05-source-inspect.yml",
        "tools/mission05_source_inspect.py",
        ".github/workflows/mission05-apply-recovery-clean.yml",
        "tools/apply_mission05_failure_recovery.py",
        "tools/trigger_mission05_apply.txt",
    ):
        path = Path(name)
        if path.exists():
            path.unlink()


def main():
    patch_clash95()
    patch_tests()
    patch_metadata()
    patch_status()
    patch_index_and_logs()
    cleanup_helpers()


if __name__ == "__main__":
    main()
