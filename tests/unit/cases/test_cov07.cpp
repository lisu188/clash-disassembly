/* cov07 cluster: building/army rule facts, castle logging, host-script glue, AI target search, render-state tail helpers */

/* Several functions below reach into the low-32-bit compat allocator pool
 * (Compat_AllocLow32Bytes / Str_Intern's atom tables) and into the "gameData"
 * game-state blob. Both are weak globals that default to 0/uninitialized in
 * this unit-test TU, so we (a) run the two cheap initializer entry points the
 * real game calls at startup, and (b) point gameData at a zeroed, generously
 * sized *static* buffer before touching anything that indexes through it.
 * Buffers are declared `static` (not plain stack locals) because this 64-bit
 * build still round-trips addresses through 32-bit ints/intptr_t all over
 * clash95.c; only static/global storage is guaranteed to live in the low
 * (sub-4GB) address range those truncating casts require. */
static void cov07_init_rules_env(void) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
}

TEST(cov07_rules, host_unit_attack_building) {
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(Rules_HostUnitAttackBuilding(0, 0, 0, 0, 0.0));
  gameData = saved;
}

TEST(cov07_army, calc_fact_strength_both_branches) {
  static unsigned char buf[2048];
  memset(buf, 0, sizeof buf);
  /* slot 0: action-point scale 100, no fatigue -> melee(1) > shot(0), else-branch */
  *(__int16 *)(buf + 6) = 0;      /* unit type 0 */
  buf[6 + 9] = 100;               /* a1[9] scale factor */
  buf[6 + 11] = 0;                /* a1[11] fatigue/level term */
  /* remaining 9 slots stay zeroed -> melee(0) <= shot(0), if-branch */
  TOUCH(UnitStack_CalcArmyFactStrength((int)(intptr_t)buf));

  /* all-zero buffer: pure if-branch (melee<=shot) for every slot */
  memset(buf, 0, sizeof buf);
  TOUCH(UnitStack_CalcArmyFactStrength((int)(intptr_t)buf));
}

TEST(cov07_army, sync_fact_strength) {
  cov07_init_rules_env();
  static unsigned char stack_buf[2048];
  static unsigned char fact_buf[2048];
  memset(stack_buf, 0, sizeof stack_buf);
  memset(fact_buf, 0, sizeof fact_buf);
  /* a1[3] (stack "moc"/threshold field) stays <=0x28 and offset 721 ("fact")
   * points at a real, zeroed static object -> Rules_EnsureArmyFactForStack
   * takes its safe "fact already exists" early-return (result==0) branch,
   * driving Rules_SyncArmyFactStrength into its main body without touching
   * gameData-based fact creation. */
  *(_DWORD *)(stack_buf + 721) = (int)(intptr_t)fact_buf;
  TOUCH(Rules_SyncArmyFactStrength((__int16 *)stack_buf, 0, 0, 0, 0, 0.0));
}

TEST(cov07_facts, trap_and_temple_and_treasure) {
  cov07_init_rules_env();
  TOUCH(Rules_LogTrapFact(1, 2));
  TOUCH(Rules_RetractTrapFact(3, 4));
  TOUCH(Rules_LogTempleFact(5, 6));
  TOUCH(Rules_LogTreasureFact(7, 8));
}

TEST(cov07_castle, assert_castle_fact_all_flags) {
  cov07_init_rules_env();
  static char gd[2200000];
  static unsigned char castle[2048];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  memset(castle, 0, sizeof castle);
  castle[416] = 0x1F; /* all five Tak/Nie garrison-building flags set */
  castle[1] = 7;       /* y */
  castle[0] = 3;        /* x */
  castle[2] = 1;         /* owning player */
  TOUCH(Rules_AssertCastleFact(castle, 5));
  gameData = saved;
}

TEST(cov07_castle, assert_castle_fact_no_flags) {
  cov07_init_rules_env();
  static char gd[2200000];
  static unsigned char castle[2048];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  memset(castle, 0, sizeof castle);
  TOUCH(Rules_AssertCastleFact(castle, 6));
  gameData = saved;
}

TEST(cov07_castle, build_castle) {
  cov07_init_rules_env();
  static char gd[2200000];
  static char namebuf[16] = "castle";
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(Rules_BuildCastle(0, 0, 0, 0, namebuf, 0.0));
  gameData = saved;
}

TEST(cov07_castle, log_site_transfer_new_destroyed) {
  cov07_init_rules_env();
  TOUCH(Rules_LogCastleSiteFact(1, 2));
  TOUCH(Rules_LogBuildingTransferFact(1, 2, 3));
  TOUCH(Rules_LogNewCastleFact(1, 2));
  TOUCH(Rules_LogCastleDestroyedFact(1, 2));
}

TEST(cov07_castle, log_scheme_captured_construction_built) {
  cov07_init_rules_env();
  TOUCH(Rules_LogCastleSchemeFact(1, 2));
  TOUCH(Rules_LogBuildingCapturedFact(1, 2, 3));
  TOUCH(Rules_LogCastleUnderConstructionFact(1));
  TOUCH(Rules_LogCastleBuiltFactAndScheme(1, 2));
}

TEST(cov07_castle, log_assigned_castle_and_player) {
  cov07_init_rules_env();
  TOUCH(Rules_LogAssignedCastleFact(1, 2));
  TOUCH(Rules_LogAssignedPlayerFact(1, 2));
}

TEST(cov07_map, castle_site_distance_default) {
  /* default-zeroed g_CastleSiteAnchorRows/Columns -> scans the tiny anchor
   * cache and returns 1 (nothing recorded closer than the candidate). */
  TOUCH(Map_IsCastleSiteDistanceMinimal(0, 0, 5, 5));
}

TEST(cov07_map, castle_site_distance_too_close) {
  int saved_row = g_CastleSiteAnchorRows[1];
  int saved_col = g_CastleSiteAnchorColumns[1];
  g_CastleSiteAnchorRows[1] = 5;
  g_CastleSiteAnchorColumns[1] = 5;
  /* candidate far from origin but right on top of the recorded anchor -> the
   * "closer anchor found" branch returns 0. */
  CHECK(Map_IsCastleSiteDistanceMinimal(0, 0, 100, 100) == 0);
  g_CastleSiteAnchorRows[1] = saved_row;
  g_CastleSiteAnchorColumns[1] = saved_col;
}

TEST(cov07_map, castle_site_distance_fast_path) {
  int saved_row = g_CastleSiteAnchorRows[1];
  g_CastleSiteAnchorRows[1] = -1; /* empty anchor cache -> immediate return 1 */
  CHECK(Map_IsCastleSiteDistanceMinimal(0, 0, 5, 5) == 1);
  g_CastleSiteAnchorRows[1] = saved_row;
}

TEST(cov07_rules, register_building_and_army_host_functions) {
  cov07_init_rules_env();
  TOUCH(Rules_RegisterBuildingHostFunctions());
  TOUCH(Rules_RegisterArmyHostFunctions());
}

TEST(cov07_script, unit_add_to_group) {
  cov07_init_rules_env();
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(Script_UnitAddToGroup(0, 0, 0, 0.0));
  gameData = saved;
}

TEST(cov07_rules, host_army_has_only_unit_type) {
  cov07_init_rules_env();
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(Rules_HostArmyHasOnlyUnitType(0, 0.0));
  gameData = saved;
}

TEST(cov07_ai, find_best_strategic_target_radius0) {
  /* a5 (search radius) < 1 -> skip the ring-scan loop entirely, fall through
   * to the "nothing found" return -1 path. */
  CHECK_EQ(AI_FindBestStrategicTargetNearTile(-1, -1, 10, 10, 0), -1);
}

TEST(cov07_ai, find_best_strategic_target_radius2) {
  /* a5>=1 drives the expanding-ring scan; give it a real gameData blob so the
   * per-tile probe (which reads map width/height off gameData) stays inside
   * the zeroed backing buffer instead of going out of bounds. */
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(AI_FindBestStrategicTargetNearTile(-1, -1, 10, 10, 2));
  gameData = saved;
}

TEST(cov07_mission, trace_objective_blocked_dedup_and_change) {
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  Mission_TraceObjectiveBlocked(1, 2, 3, 4);
  Mission_TraceObjectiveBlocked(1, 2, 3, 4); /* identical args -> dedup early return */
  Mission_TraceObjectiveBlocked(2, 3, 4, 5); /* different args -> falls through and re-logs */
  gameData = saved;
}

TEST(cov07_compat, render_state_tail_fields_and_probe_trace) {
  CHECK(Compat_RenderStateTailFields(0) != 0);
  TOUCH(Compat_MenuProbeTraceEnabled());
}

TEST(cov07_render, warp_cursor_and_pump) {
  static unsigned char obj[2048];
  memset(obj, 0, sizeof obj);
  TOUCH(RenderState_WarpCursorAndPump((_DWORD *)obj, 5, 5));
}

TEST(cov07_render, recalc_cursor_bounds) {
  static unsigned char result_buf[2048];
  static __int16 inner[64];
  memset(result_buf, 0, sizeof result_buf);
  memset(inner, 0, sizeof inner);
  ((_DWORD *)result_buf)[15] = (_DWORD)(intptr_t)inner;
  TOUCH(RenderState_RecalculateCursorBoundsForRect((_DWORD *)result_buf, 1, 2, 3, 4));
}
