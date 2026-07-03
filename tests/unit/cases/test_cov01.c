/* cov01 cluster: sprite RLE scans, tile/building predicates, worldmap/text-sprite
 * plumbing, unit-slot/stack action-point + combat-stat helpers */

TEST(cov01_copyfour, basic) {
  unsigned char src[16], dst[16];
  memset(src, 0, sizeof src);
  memset(dst, 0xAA, sizeof dst);
  src[0] = 0x11; src[1] = 0x22; src[2] = 0x33; src[3] = 0x44;
  TOUCH(RenderSurface_CopyFourByteFields(dst, src));
  CHECK_EQ(dst[0], 0x11);
  CHECK_EQ(dst[3], 0x44);
}

/* Shared RLE sprite-row builder used by the four UnitBattle_* sprite scanners
 * below. Each row is encoded as:
 *   0x84                 -> "run" of 4  (top bit set)
 *   0x06 + 6 filler bytes -> literal run of 6 (top bit clear, nonzero)
 *   0x00 + 4 zero bytes   -> zero-length marker branch (self-referential
 *                            offset 0 so the backward index stays in-bounds)
 *   0x8A                  -> "run" of 10 (top bit set) -> total width 20
 * A pure "all blank" row is a single 0x94 byte (run of 20 == width). */
TEST(cov01_sprite, scans_all_branches) {
  /* static: the DWORD data-pointer field is truncated to 32 bits by the
   * recovered code's own (_DWORD) field width, so the backing storage must
   * live at a low (non-ASLR'd) address -- true of static/global storage under
   * this project's -no-pie build, not of ordinary stack locals. */
  static unsigned __int16 hdr[16];
  static unsigned char data[64];
  int n;

  memset(data, 0, sizeof data);
  n = 0;
  data[n++] = 0x94; /* row 0: fully blank (20) */
  data[n++] = 0x84; data[n++] = 0x06;
  data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0;
  data[n++] = 0x00; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0;
  data[n++] = 0x8A; /* row 1: mixed, contains a literal (non-blank) byte */
  data[n++] = 0x84; data[n++] = 0x06;
  data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0;
  data[n++] = 0x00; data[n++] = 0; data[n++] = 0; data[n++] = 0; data[n++] = 0;
  data[n++] = 0x8A; /* row 2: mixed again */

  memset(hdr, 0, sizeof hdr);
  hdr[0] = 20;  /* width */
  hdr[1] = 3;   /* height */
  hdr[2] = 0;   /* flag == 0 -> enter scan loop */
  *(_DWORD *)((char *)hdr + 10) = (_DWORD)(uintptr_t)data;

  TOUCH(UnitBattle_ScanSpriteMinOpaqueRunLength(hdr));
  TOUCH(UnitBattle_ScanSpriteFirstOpaqueRunLength(hdr));
  TOUCH(UnitBattle_CountLeadingBlankSpriteRows(hdr));
  TOUCH(UnitBattle_CountTrailingBlankSpriteRows(hdr));

  /* flag != 0 -> all four functions skip the scan entirely (early-exit branch) */
  hdr[2] = 1;
  TOUCH(UnitBattle_ScanSpriteMinOpaqueRunLength(hdr));
  TOUCH(UnitBattle_ScanSpriteFirstOpaqueRunLength(hdr));
  TOUCH(UnitBattle_CountLeadingBlankSpriteRows(hdr));
  TOUCH(UnitBattle_CountTrailingBlankSpriteRows(hdr));

  /* height == 0 -> for-loop body never runs, but flag == 0 so the branch is taken */
  hdr[1] = 0;
  hdr[2] = 0;
  TOUCH(UnitBattle_ScanSpriteMinOpaqueRunLength(hdr));
  TOUCH(UnitBattle_ScanSpriteFirstOpaqueRunLength(hdr));
  TOUCH(UnitBattle_CountLeadingBlankSpriteRows(hdr));
  TOUCH(UnitBattle_CountTrailingBlankSpriteRows(hdr));
}

/* MapTile_HasOwnOrVisibleEnemyUnitStack / MapTile_HasBuilding both start by
 * dereferencing TILE_INDEX(a1,a2) == gameData + 556374 + 200*a1 + 2*a2.
 * gameData itself is a plain (zero-initialized, never-set-here) `int`, so its
 * *value* is 0 and this expression is really just a small absolute address --
 * dereferencing it directly would segfault. We instead pick a1/a2 so that the
 * computed address lands inside a real local buffer we own, and give that
 * buffer a tile value large enough (0xFFFF) that every downstream helper's
 * bounds check (`<= 0x1F4`, or the building "- 0x8000 <= 0x64" check) fails,
 * short-circuiting before any *other* gameData-based dereference happens. */
TEST(cov01_tile, has_own_or_visible_enemy_and_building_safe_false) {
  static unsigned char fake_tile[64]; /* must be a low, stable (non-stack) address */
  intptr_t target, off;
  int a1, a2;
  long long rem;

  memset(fake_tile, 0, sizeof fake_tile);
  *(unsigned __int16 *)(fake_tile + 16) = 0xFFFF; /* at the redirected address, see below */

  target = (intptr_t)(fake_tile + 16); /* leave slack on both sides */
  off = target - 556374;               /* == 200*a1 + 2*a2, solve for ints */
  a1 = (int)(off / 200);
  rem = off - (long long)a1 * 200;
  a2 = (int)(rem / 2);

  CHECK_EQ(TILE_INDEX(a1, a2), target);

  TOUCH(MapTile_HasOwnOrVisibleEnemyUnitStack(a1, a2));
  TOUCH(MapTile_HasBuilding(a1, a2));
}

/* NOTE: WorldMap_HandleSaveGameAction is deliberately NOT exercised here. It
 * forwards into SaveSlotDialog_Run(), which (like WorldMap_LoadResources
 * above) reaches a missing-resource-file path that calls the __noreturn
 * App_RequestQuit() -> CRT_ExitProcessWithFinalizers(), terminating the whole
 * test binary rather than raising a catchable signal -- confirmed via an
 * isolated run (process exit code 1, no SIGSEGV) during development of this
 * file. That would truncate every test registered after it, in every batch,
 * so it is not safe to call from this shared coverage suite. */

TEST(cov01_worldmap, defer_building_action_callback) {
  unsigned char widget[64];
  memset(widget, 0, sizeof widget);
  CHECK_EQ(WorldMap_DeferBuildingActionCallback((uintptr_t)widget), 0);
  CHECK_EQ(WorldMap_DeferBuildingActionCallback(0), 0);
}

/* NOTE: WorldMap_Initialize is deliberately NOT exercised here. It forwards
 * into WorldMap_LoadResources -> DLXSpriteSet_Load("frame.s32", ...), and
 * when that resource file is missing (as in this unit-test environment) the
 * recovered code calls the __noreturn App_RequestQuit(), which terminates
 * the whole test process outright (not a catchable SIGSEGV/SIGABRT) -- that
 * would silently truncate every test registered after it, in every batch. */

TEST(cov01_textsprite, get_resource_slot_bounds) {
  TextSpriteResourceSlotRecord *slot;

  slot = TextSprite_GetResourceSlot(0);
  CHECK(slot != 0);
  slot = TextSprite_GetResourceSlot(-1);
  CHECK(slot == 0);
  slot = TextSprite_GetResourceSlot(1000000);
  CHECK(slot == 0);
}

TEST(cov01_ui, draw_text_fmt_v_and_x_offset) {
  int result;

  TOUCH(UI_GetTextXOffset(0));   /* in range */
  TOUCH(UI_GetTextXOffset(-1));  /* out of range -> 0 */

  /* format == NULL branch */
  {
    va_list dummy;
    memset(&dummy, 0, sizeof dummy);
    result = UI_DrawTextFmtV(0, 0, 1, 0, 0, dummy);
    TOUCH(result);
  }
}

/* vsnprintf branch of UI_DrawTextFmtV needs a real va_list; build one via a
 * tiny variadic wrapper rather than faking a va_list by hand. */
static int cov01_call_draw_text_fmt(int a1, int a2, int a3, int a4, const char *fmt, ...) {
  va_list ap;
  int r;
  va_start(ap, fmt);
  r = UI_DrawTextFmtV(a1, a2, a3, a4, fmt, ap);
  va_end(ap);
  return r;
}

TEST(cov01_ui, draw_text_fmt_v_formatted) {
  TOUCH(cov01_call_draw_text_fmt(0, 0, 1, 0, "hi %d", 5));
}

TEST(cov01_textsprite, release_all_resource_slots) {
  TOUCH(TextSprite_ReleaseAllResourceSlots());
}

TEST(cov01_menu, enable_disable_entry) {
  /* a1 is an `int` standing in for a pointer -- must fit in 32 bits, so the
   * backing storage must be static, not an ASLR'd stack address. */
  static unsigned char buf[512];
  memset(buf, 0, sizeof buf);
  CHECK_EQ(UI_MenuEntry_Enable((int)(intptr_t)buf, 2), 2);
  CHECK_EQ(*(_DWORD *)(buf + 40 * 2 + 26), 1);
  CHECK_EQ(UI_MenuEntry_Disable((int)(intptr_t)buf, 2), 2);
  CHECK_EQ(*(_DWORD *)(buf + 40 * 2 + 26), 0);
}

/* Map_ClassifyFogOfWarOverlayForPlayer probes Map_IsTileVisibleToPlayer at the
 * 9 tiles around (a1,a2). That helper short-circuits on `a1 < 0 || a2 < 0`
 * *before* touching gameData, so keeping both coordinates comfortably negative
 * for every probed neighbor keeps the whole thing gameData-free and safe. */
TEST(cov01_map, classify_fog_of_war_all_neighbors_negative) {
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-5, -5, 0));
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-20, -20, 1));
  /* The tail of this function branches on decompiler-flagged "possibly
   * undefined" locals (v9/v10) that were never assigned on this path, so
   * which of the many equivalent return-code branches gets hit is outside
   * our control; vary the call site a bit for a better chance of covering
   * more of them. */
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-1, -100, 2));
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-100, -1, 0));
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-2, -2, 3));
}

TEST(cov01_unitslot, init_from_type) {
  /* result is an `int`-typed pointer -- needs static (low, stable) storage. */
  static unsigned char buf[64];

  memset(buf, 0, sizeof buf);
  TOUCH(UnitSlot_InitFromType((int)(intptr_t)buf, 0, 0));

  /* unitType == -1 -> both action-points/morale assignments are skipped */
  memset(buf, 0, sizeof buf);
  TOUCH(UnitSlot_InitFromType((int)(intptr_t)buf, -1, 0));

  /* g_UnitTypeFlags[0] has bit 2 clear -> morale = 10 branch already covered
   * above (weak 1-entry table is all zero); flip stance bits so the masks at
   * the tail (offsets 17/22/13) exercise nonzero source bytes too. */
  memset(buf, 0, sizeof buf);
  buf[12] = (char)0xFF; /* stance bits */
  buf[17] = (char)0xFF;
  buf[22] = (char)0xFF;
  buf[13] = (char)0xFF;
  TOUCH(UnitSlot_InitFromType((int)(intptr_t)buf, 0, 3));

  /* g_UnitTypeFlags is the 1-entry weak stand-in for the real per-unit-type
   * flag table and is always zero, so the "(flags & 2) != 0 -> morale = 6"
   * branch is otherwise unreachable. Flip the bit just for this call, then
   * restore it immediately so no other test observes the change. */
  memset(buf, 0, sizeof buf);
  g_UnitTypeFlags[0] |= 2;
  TOUCH(UnitSlot_InitFromType((int)(intptr_t)buf, 0, 0));
  g_UnitTypeFlags[0] &= ~2;
}

TEST(cov01_unitstack, kill_by_index) {
  /* UnitStack_KillByIndex is a single forwarding line to Unit_Kill(); the
   * computed UNIT_STACK() address is an unmapped gameData-relative address,
   * so this call is expected to reach Unit_Kill (covering our target's only
   * line) even if the deeper call itself later faults -- the harness isolates
   * that as a CRASH without losing coverage already recorded for this line. */
  TOUCH(UnitStack_KillByIndex(0, 0, 0, 0.0));
}

TEST(cov01_unitstack, unlink_if_empty_false_branch) {
  __int16 buf[16];
  memset(buf, 0, sizeof buf);
  buf[3] = 0; /* != -1 -> takes the safe "return result" branch, no recursion */
  CHECK(UnitStack_UnlinkIfEmpty(buf, 0.0) == buf);
  CHECK(Rules_LinkArmyFinalize(buf, 0.0) == buf);
}

TEST(cov01_unitstack, unlink_if_empty_true_branch) {
  __int16 buf[16];
  memset(buf, 0, sizeof buf);
  buf[3] = -1; /* == -1 -> recurses into Rules_UnlinkArmyFact/UnitStack_RemoveFromTile,
                * which dereferences fixed gameData-relative addresses (140000/140004)
                * and may fault; harness isolates any such crash per-test. */
  TOUCH(UnitStack_UnlinkIfEmpty(buf, 0.0));
}

TEST(cov01_unitstack, unlink_if_empty_true_branch2) {
  __int16 buf[16];
  memset(buf, 0, sizeof buf);
  buf[3] = -1;
  TOUCH(Rules_LinkArmyFinalize(buf, 0.0));
}

TEST(cov01_facing, direction_from_delta8_all_octants) {
  CHECK_EQ(Facing_DirectionFromDelta8(-1, -1), 7);
  CHECK_EQ(Facing_DirectionFromDelta8(-1, 1), 5);
  CHECK_EQ(Facing_DirectionFromDelta8(-1, 0), 6);
  CHECK_EQ(Facing_DirectionFromDelta8(0, -1), 0);
  CHECK_EQ(Facing_DirectionFromDelta8(0, 0), 4);
  CHECK_EQ(Facing_DirectionFromDelta8(1, -1), 1);
  CHECK_EQ(Facing_DirectionFromDelta8(1, 1), 3);
  CHECK_EQ(Facing_DirectionFromDelta8(1, 0), 2);
}

TEST(cov01_unitslot, get_base_action_points) {
  __int16 a1[8];
  memset(a1, 0, sizeof a1);
  a1[0] = 0; /* unit type index 0 (in-bounds of the tiny weak table) */
  TOUCH(UnitSlot_GetBaseActionPoints(a1));
}

TEST(cov01_unitstack, clear_remaining_action_points_null) {
  CHECK(UnitStack_ClearRemainingActionPoints(0, 0, 0.0) == 0);
}

TEST(cov01_unitstack, clear_remaining_action_points_break_early) {
  unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1; /* slot0 terminator -> loop breaks on i==0 */
  TOUCH(UnitStack_ClearRemainingActionPoints((__int16 *)buf, 0, 0.0));
}

TEST(cov01_unitstack, clear_remaining_action_points_full_loop) {
  unsigned char buf[1024];
  int i;
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0; /* 10 valid slots -> loop runs to completion */
  TOUCH(UnitStack_ClearRemainingActionPoints((__int16 *)buf, 0, 0.0));
}

/* UnitStack_SubtractActionPointsFloorZero's final line unconditionally calls
 * Rules_LinkArmyFact(), which (for an all-zero buffer, i.e. tile row/col 0,0)
 * chains into a fixed, unmapped gameData-relative dereference and faults --
 * confirmed via gdb during development (crash inside Rules_CreateArmyFact,
 * not inside our target function). That fault only ever happens *after* our
 * target's own loop has already fully executed, so it doesn't cost us any of
 * our target's own line coverage -- but it DOES abort the rest of the
 * enclosing TEST body via siglongjmp, so each branch scenario below gets its
 * own TEST rather than sharing one (a crash in an earlier scenario must not
 * skip the later ones). */
TEST(cov01_unitstack, subtract_action_points_floor_zero_immediate_terminator) {
  unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1; /* immediate terminator -> loop body never executes */
  TOUCH(UnitStack_SubtractActionPointsFloorZero((__int16 *)buf, 5, 0, 0.0));
}

TEST(cov01_unitstack, subtract_action_points_floor_zero_clamp_branch) {
  unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 0;
  buf[14] = 3; /* slot AP (buf+6+8=buf+14) <= a2 -> "clamp to 0" branch */
  *(__int16 *)(buf + 6 + 31) = -1;
  TOUCH(UnitStack_SubtractActionPointsFloorZero((__int16 *)buf, 5, 0, 0.0));
}

TEST(cov01_unitstack, subtract_action_points_floor_zero_subtract_and_full_loop) {
  unsigned char buf[1024];
  int i;
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i) {
    *(__int16 *)(buf + 6 + 31 * i) = 0;
    buf[6 + 31 * i + 8] = 50; /* slot AP > a2 -> "subtract" branch */
  }
  TOUCH(UnitStack_SubtractActionPointsFloorZero((__int16 *)buf, 5, 0, 0.0));
}

TEST(cov01_unitstats, melee_attack_and_icon) {
  unsigned char buf[64];

  memset(buf, 0, sizeof buf);
  *(__int16 *)buf = 0;   /* unit type index 0 */
  buf[9] = 50;
  buf[11] = 10;
  buf[12] = 0;           /* status level bits */
  TOUCH(UnitStats_CalcEffectiveMeleeAttack((char *)buf, 0)); /* a2==0 -> UNIT_SLOT_STATUS_LEVEL */
  TOUCH(UnitStats_CalcEffectiveMeleeAttack((char *)buf, 1)); /* a2!=0 -> v2=3 */
  TOUCH(UnitStats_GetMeleeIconIndex((__int16 *)buf));
}

TEST(cov01_unitstats, defense_power_and_icon) {
  unsigned char buf[64];

  memset(buf, 0, sizeof buf);
  *(__int16 *)buf = 0;
  buf[9] = 50;
  buf[11] = 10;
  buf[22] = 0; /* bit0 clear -> skip the 320*v2 rescale branch */
  TOUCH(UnitStats_CalcEffectiveDefensePower((char *)buf, 0));
  TOUCH(UnitStats_CalcEffectiveDefensePower((char *)buf, 1));

  memset(buf, 0, sizeof buf);
  *(__int16 *)buf = 0;
  buf[9] = 50;
  buf[11] = 10;
  buf[22] = 1; /* bit0 set -> take the rescale branch */
  TOUCH(UnitStats_CalcEffectiveDefensePower((char *)buf, 0));
  TOUCH(UnitStats_GetDefenseIconIndex((__int16 *)buf));
}

TEST(cov01_unitstats, shot_power) {
  unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  *(__int16 *)buf = 0;
  buf[9] = 50;
  buf[11] = 10;
  TOUCH(UnitStats_CalcEffectiveShotPower((__int16 *)buf));
}
