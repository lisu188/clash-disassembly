/* cov02 cluster: unit-slot/stack combat stats, sprite path builders, queued path helpers */

TEST(cov02_shotpower, base) {
  __int16 a1[8];
  memset(a1, 0, sizeof a1);
  a1[0] = 0;                 /* unit type index 0 (in-bounds of tiny weak tables) */
  ((char *)a1)[11] = 20;
  TOUCH(UnitStats_GetBaseShotPower(a1));
  a1[0] = 0;
  ((char *)a1)[11] = -5;
  TOUCH(UnitStats_GetBaseShotPower(a1));
}

TEST(cov02_wallattack, both_branches) {
  char buf[64];
  memset(buf, 0, sizeof buf);
  *(__int16 *)buf = 0;   /* unit type index 0 */
  buf[9] = 50;
  buf[11] = 10;
  buf[12] = 0;           /* stance bits -> status level 0 */
  TOUCH(UnitStats_CalcEffectiveWallAttack(buf, 0)); /* a2==0 -> uses UNIT_SLOT_STATUS_LEVEL */
  TOUCH(UnitStats_CalcEffectiveWallAttack(buf, 1)); /* a2!=0 -> v2=3 */
}

TEST(cov02_fatigue, severe) {
  char buf[32];
  memset(buf, 0, sizeof buf);
  buf[10] = 90;
  CHECK(UnitSlot_HasSevereFatigue((int)(intptr_t)buf) != 0);
  buf[10] = 10;
  CHECK(UnitSlot_HasSevereFatigue((int)(intptr_t)buf) == 0);
}

TEST(cov02_extract, special_shift_and_immediate_terminator) {
  unsigned char src[512];
  unsigned char dst[128];

  /* Case 1: first entry is special (GOLD_CARGO), remaining slots normal (type 0).
   * Exercises the "found special" branch, the inner shift loop, and the trailing
   * "else" branch as later normal entries get scanned. */
  memset(src, 0, sizeof src);
  memset(dst, 0, sizeof dst);
  *(__int16 *)(src + 0) = 31;  /* UNIT_TYPE_GOLD_CARGO */
  TOUCH(UnitSlots_ExtractSpecialEntries((char *)src, 5, (char *)dst));
  TOUCH(UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)src, 5, (char *)dst));

  /* Case 2: immediate terminator -> breaks out of outer while right away. */
  memset(src, 0, sizeof src);
  memset(dst, 0, sizeof dst);
  *(__int16 *)(src + 0) = -1;
  TOUCH(UnitSlots_ExtractSpecialEntries((char *)src, 5, (char *)dst));

  /* Case 3: no special entries at all -> pure "else" branch each iteration. */
  memset(src, 0, sizeof src);
  memset(dst, 0, sizeof dst);
  *(__int16 *)(src + 0 * 31) = 0;
  *(__int16 *)(src + 1 * 31) = 1;
  *(__int16 *)(src + 2 * 31) = -1;
  TOUCH(UnitSlots_ExtractSpecialEntries((char *)src, 3, (char *)dst));
}

TEST(cov02_append, building_attack) {
  unsigned char dest[128];
  unsigned char src[128];
  memset(dest, 0, sizeof dest);
  memset(src, 0, sizeof src);
  *(__int16 *)(dest + 0) = -1;      /* dest has zero entries already present */
  *(__int16 *)(src + 0 * 31) = 5;
  *(__int16 *)(src + 1 * 31) = 6;
  *(__int16 *)(src + 2 * 31) = -1;  /* src has 2 entries */
  TOUCH(UnitSlots_AppendEntriesForBuildingAttack((char *)dest, (char *)src));
}

TEST(cov02_cargo, gold_and_peasant) {
  unsigned char buf[512];
  int i;

  /* immediate match */
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 31; /* UNIT_TYPE_GOLD_CARGO */
  CHECK(UnitStack_HasGoldCargo((int)(intptr_t)buf) == 1);

  /* immediate terminator -> not found */
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1;
  CHECK(UnitStack_HasGoldCargo((int)(intptr_t)buf) == 0);

  /* 10 non-matching entries -> loop exhausts and returns 0 */
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0;
  CHECK(UnitStack_HasGoldCargo((int)(intptr_t)buf) == 0);

  /* peasant cargo variants */
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 32; /* UNIT_TYPE_PEASANT_CARGO */
  CHECK(UnitStack_HasPeasantCargo((int)(intptr_t)buf) == 1);

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1;
  CHECK(UnitStack_HasPeasantCargo((int)(intptr_t)buf) == 0);

  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0;
  CHECK(UnitStack_HasPeasantCargo((int)(intptr_t)buf) == 0);
}

TEST(cov02_predicate, always) {
  CHECK(UnitSlot_PredicateAlways(0) == 1);
  CHECK(UnitSlot_PredicateAlways(12345) == 1);
}

TEST(cov02_cycle, order_state_all_values) {
  unsigned char buf[32];
  int v;
  for (v = 0; v < 256; ++v) {
    memset(buf, 0, sizeof buf);
    buf[12] = (unsigned char)v;
    TOUCH(UnitSlot_CycleOrderState((int)(intptr_t)buf));
  }
}

TEST(cov02_cycle, stack_orders_early_return) {
  unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1;               /* slot0 terminator -> early-return path */
  *(_DWORD *)(buf + 721) = 1;               /* fake "fact" so EnsureArmyFactForStack
                                              * takes the safe fact!=0 early-return
                                              * branch instead of dereferencing gameData */
  TOUCH(UnitStack_CycleAllSlotOrders((__int16 *)buf, 0, 0.0));
}

TEST(cov02_cycle, stack_orders_full_loop) {
  unsigned char buf[1024];
  int i;
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0;      /* 10 valid (non -1) slots -> loop runs to
                                               * completion, exercising UnitSlot_CycleOrderState
                                               * for every slot before the final sync call. */
  TOUCH(UnitStack_CycleAllSlotOrders((__int16 *)buf, 0, 0.0));
}

TEST(cov02_special, has_special_units) {
  unsigned char buf[512];
  int i;

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 33; /* SPECIAL_FOOT_PERSONAGE */
  CHECK(UnitStack_HasSpecialPersonageUnits((intptr_t)buf) == 1);

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 34; /* SPECIAL_MOUNTED_PERSONAGE */
  CHECK(UnitStack_HasSpecialPersonageUnits((intptr_t)buf) == 1);

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1;
  CHECK(UnitStack_HasSpecialPersonageUnits((intptr_t)buf) == 0);

  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0;
  CHECK(UnitStack_HasSpecialPersonageUnits((intptr_t)buf) == 0);
}

TEST(cov02_combat, strength_with_special_check) {
  unsigned char buf[256];

  /* a2 <= 0 -> skip the scanning loop entirely */
  memset(buf, 0, sizeof buf);
  TOUCH(UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)buf, 0, 0));

  /* scan finds a special personage mid-way -> v5 becomes 1 and loop breaks */
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 0 * 31) = 0;
  *(__int16 *)(buf + 1 * 31) = 33; /* special foot personage */
  *(__int16 *)(buf + 2 * 31) = 0;
  TOUCH(UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)buf, 3, 5));

  /* scan runs through without finding any special unit */
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 0 * 31) = 0;
  *(__int16 *)(buf + 1 * 31) = 1;
  *(__int16 *)(buf + 2 * 31) = 2;
  TOUCH(UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)buf, 3, 0));
}

TEST(cov02_military, calc_strength_zero_squads) {
  unsigned char buf[512];
  memset(buf, 0, sizeof buf);
  /* Force Unit_GetSquadCount(a1) == 0 so the (decompiler-uninitialized) second
   * pointer parameter of the inner combat-score call is never dereferenced -
   * UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck skips its whole
   * body when a2==0. This still exercises every line of the wrapper safely. */
  *(__int16 *)(buf + 6) = -1;
  TOUCH(UnitStack_CalcMilitaryStrength((int)(intptr_t)buf));
}

TEST(cov02_garrison, calc_strength) {
  unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  /* Building_CalcGarrisonStrength reads a decompiler-uninitialized local for
   * its Building_CountGarrison() call; this can fault on the second line. The
   * harness catches such crashes via siglongjmp, and the first computed line
   * (Building_CalcWallDefenseBonus) is still exercised beforehand. */
  TOUCH(Building_CalcGarrisonStrength((int)(intptr_t)buf, 0));
}

TEST(cov02_track, build_blank) {
  _DWORD result[8];
  memset(result, 0xAA, sizeof result);
  TOUCH(UnitTrackElementStack_BuildBlank(result));
  CHECK_EQ(result[0], 0);
}

TEST(cov02_stack, copy_from_template) {
  unsigned char a1[1024];
  unsigned char a2[1024];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  *(_WORD *)(a2 + 316) = 7;
  *(_BYTE *)(a2 + 720) = 3;
  *(_DWORD *)(a2 + 721) = 42;
  /* UnitStack_CopyFromTemplate reads a decompiler-uninitialized local (v7) for
   * one of its writes; may fault partway through. Still exercises the first
   * assignments safely before that point. */
  TOUCH(UnitStack_CopyFromTemplate((int)(intptr_t)a1, (int)(intptr_t)a2, (int)(intptr_t)a1));
}

TEST(cov02_battle, copy_merging_packed_flags) {
  unsigned char result[64];
  unsigned char a2[64];
  memset(result, 0, sizeof result);
  memset(a2, 0xFF, sizeof a2);
  TOUCH(BattleUnitEntry_CopyMergingPackedFlags((int)(intptr_t)result, (int)(intptr_t)a2));

  memset(result, 0xFF, sizeof result);
  memset(a2, 0, sizeof a2);
  TOUCH(BattleUnitEntry_CopyMergingPackedFlags((int)(intptr_t)result, (int)(intptr_t)a2));
}

TEST(cov02_track, copy_stack_from_template) {
  _DWORD a1[4];
  _DWORD a2[4];
  memset(a1, 0, sizeof a1);
  a2[0] = 0x12345678;
  TOUCH(UnitTrackElementStack_CopyFromTemplate(a1, a2, 100));
  CHECK_EQ(a1[0], a2[0]);
}

TEST(cov02_track, copy_element_from_template) {
  unsigned char result[16];
  unsigned char a2[16];
  memset(result, 0, sizeof result);
  memset(a2, 0x55, sizeof a2);
  TOUCH(UnitTrackElement_CopyFromTemplate((int)(intptr_t)result, (int)(intptr_t)a2));
  CHECK_EQ(result[0], 0x55);
}

TEST(cov02_resource, get_key_in_and_out_of_range) {
  TOUCH(UnitType_GetResourceKey(0));
  TOUCH(UnitType_GetResourceKey(34));
  TOUCH(UnitType_GetResourceKey(-1));
  TOUCH(UnitType_GetResourceKey(35));
  TOUCH(UnitType_GetResourceKey(1000));
}

TEST(cov02_path, build_go_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildGoSpriteFilePath(buf, 0, '0'));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildGoSpriteFilePath(buf, 34, '5'));
}

TEST(cov02_ui, begin_unit_info) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(UI_BeginUnitInfo(buf, 0, '0'));
  memset(buf, 0, sizeof buf);
  TOUCH(UI_BeginUnitInfo(buf, 34, '9'));
}

TEST(cov02_path, build_garrison_slot_icon_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildGarrisonSlotIconSpritePath(buf, 0, 0));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildGarrisonSlotIconSpritePath(buf, 34, 7));
}

TEST(cov02_path, build_selected_unit_panel_icon_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildSelectedUnitPanelIconSpritePath(buf, 0, 0));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildSelectedUnitPanelIconSpritePath(buf, 34, 7));
}

TEST(cov02_path, build_selected_unit_panel_icon_palette) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildSelectedUnitPanelIconPalettePath(buf, 0, 0));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildSelectedUnitPanelIconPalettePath(buf, 34, 7));
}

TEST(cov02_path, build_attack_anim_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildAttackAnimSpritePath(buf, 0, '0'));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildAttackAnimSpritePath(buf, 34, '9'));
}

TEST(cov02_path, build_shot_anim_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildShotAnimSpritePath(buf, 0, '0'));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildShotAnimSpritePath(buf, 34, '9'));
}

TEST(cov02_path, build_shot_anim_palette_sprite) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildShotAnimPaletteSpritePath(buf, 0));
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildShotAnimPaletteSpritePath(buf, 34));
}

TEST(cov02_queuedpath, starts_at_tile) {
  _DWORD a1[4];

  memset(a1, 0, sizeof a1);
  CHECK(QueuedPath_StartsAtTile(a1, 5, 7) == 0); /* a1[0]==0 -> return 0 */

  a1[0] = 1;
  a1[1] = (7 << 8) | 5; /* low byte=5, next byte=7 */
  CHECK(QueuedPath_StartsAtTile(a1, 5, 7) != 0);

  a1[1] = (9 << 8) | 5; /* mismatch on second field */
  CHECK(QueuedPath_StartsAtTile(a1, 5, 7) == 0);

  a1[1] = (7 << 8) | 6; /* mismatch on first field */
  CHECK(QueuedPath_StartsAtTile(a1, 5, 7) == 0);
}
