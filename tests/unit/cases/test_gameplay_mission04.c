/* Characterization tests for the mission-04 objective gate — the documented
 * campaign frontier (docs/STATUS.md). These drive real gameData-based gameplay
 * logic (not the "pure" coverage set) to lock in the recovered win condition
 * against regression and to document the objective's exact structure offsets.
 *
 * Recovered logic (Mission_CheckObjectiveComplete, case ACTIVE_MISSION_INDEX==4):
 *   idx   = *(u16*)(gameData + 567712) - 0x8000          // target castle index
 *   owner = *(u8*)(467*idx + gameData + 509676)          // its owner byte
 *   objective complete (return 1) iff owner == 0, else blocked (return 0).
 * (467 = BUILDING_RECORD stride; +509674 is the building-record region base,
 * so +509676 is the owner byte at record offset +2.)
 *
 * gameData is modeled as a 32-bit int base address; this is a -no-pie build so
 * a static buffer sits at a low, 32-bit-safe address. Globals are saved and
 * restored so tests don't leak state (each test also runs in its own fork). */

static unsigned char cov_m04_gamedata[600000];

static void cov_m04_setup(int mission, int castle_idx, int owner) {
  memset(cov_m04_gamedata, 0, sizeof cov_m04_gamedata);
  gameData = (int)(intptr_t)cov_m04_gamedata;
  g_CheatForceWinMissionFlag = 0; /* force-win cheat flag off */
  ACTIVE_MISSION_INDEX = mission;
  *(unsigned short *)(gameData + 567712) = (unsigned short)(0x8000 + castle_idx);
  *(unsigned char *)(467 * castle_idx + gameData + 509676) = (unsigned char)owner;
}

TEST(mission04, objective_complete_when_castle_owner_zero) {
  int saved_gd = gameData, saved_cheat = g_CheatForceWinMissionFlag;
  cov_m04_setup(4, 1, 0); /* target castle idx 1, owner byte 0 */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = saved_gd;
  g_CheatForceWinMissionFlag = saved_cheat;
}

TEST(mission04, objective_blocked_when_castle_owner_nonzero) {
  int saved_gd = gameData, saved_cheat = g_CheatForceWinMissionFlag;
  cov_m04_setup(4, 1, 2); /* owner byte 2 -> objective not yet met */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = saved_gd;
  g_CheatForceWinMissionFlag = saved_cheat;
}

/* The force-win cheat flag short-circuits the whole objective check to complete
 * and clears itself (recovered top-of-function behavior). */
TEST(mission04, force_win_cheat_short_circuits) {
  int saved_gd = gameData, saved_cheat = g_CheatForceWinMissionFlag;
  cov_m04_setup(4, 1, 2); /* would otherwise be blocked */
  g_CheatForceWinMissionFlag = 1;
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  CHECK_EQ(g_CheatForceWinMissionFlag, 0); /* flag consumed */
  gameData = saved_gd;
  g_CheatForceWinMissionFlag = saved_cheat;
}

/* A non-zero target index exercises the 467-byte record stride arithmetic. */
TEST(mission04, objective_complete_respects_castle_index_stride) {
  int saved_gd = gameData, saved_cheat = g_CheatForceWinMissionFlag;
  cov_m04_setup(4, 5, 0); /* idx 5: owner at 467*5 + base + 509676 */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  /* poisoning idx 0's owner byte must not affect idx 5's verdict */
  cov_m04_setup(4, 5, 0);
  *(unsigned char *)(gameData + 509676) = 3; /* idx 0 owner nonzero */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = saved_gd;
  g_CheatForceWinMissionFlag = saved_cheat;
}
