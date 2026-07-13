/* Characterization tests for additional campaign mission objective gates in
 * Mission_CheckObjectiveComplete. Extends test_gameplay_mission04.c to the
 * other tractable win conditions (missions validated complete in
 * docs/STATUS.md), locking each as an executable spec runnable without retail
 * assets. Each documents the disassembly-derived gameData structure it reads.
 *
 * Tile array stride: gameData + 1400*row + 14*col (first _WORD = tile type;
 * +2 = religious-site sub-type). Castle capture gate: owner byte at
 * 467*idx + gameData + 509676, idx = *(u16*)(gameData + <castle_ref>) - 0x8000. */

static unsigned char cov_obj_gamedata[600000];

static void cov_obj_reset(int mission) {
  memset(cov_obj_gamedata, 0, sizeof cov_obj_gamedata);
  gameData = (int)(intptr_t)cov_obj_gamedata;
  dword_5448A0 = 0;
  ACTIVE_MISSION_INDEX = mission;
}

static void cov_obj_set_tile_word(int row, int col, unsigned short w) {
  *(unsigned short *)(gameData + 1400 * row + 14 * col) = w;
}

static void cov_obj_set_capture(int castle_ref_off, int idx, int owner) {
  *(unsigned short *)(gameData + castle_ref_off) = (unsigned short)(0x8000 + idx);
  *(unsigned char *)(467 * idx + gameData + 509676) = (unsigned char)owner;
}

/* Mission 01 (shrine): complete iff the tile at (16,11) is an EMPTY_SHRINE
 * (religious-site category 2), whose recovered tile-type values are
 * 0x2D9/0x2DB/0x2DD (see MapTile_GetReligiousSiteCategory). */
TEST(objectives, mission01_shrine_complete) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(1);
  *(unsigned short *)(gameData + 1400 * 16 + 14 * 11 + 2) = 0x2D9; /* empty shrine */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch;
}

TEST(objectives, mission01_shrine_blocked) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(1);
  *(unsigned short *)(gameData + 1400 * 16 + 14 * 11 + 2) = 0; /* not a shrine */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch;
}

/* Mission 02 (Treg Rock capture): castle-ref at gameData+564710. */
TEST(objectives, mission02_capture_complete_and_blocked) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(2);
  cov_obj_set_capture(564710, 3, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  cov_obj_reset(2);
  cov_obj_set_capture(564710, 3, 2);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch;
}

/* Mission 06 (capture): castle-ref at gameData+574456. */
TEST(objectives, mission06_capture_complete_and_blocked) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(6);
  cov_obj_set_capture(574456, 2, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  cov_obj_reset(6);
  cov_obj_set_capture(574456, 2, 5);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch;
}

/* Mission 07 (treasure): complete iff NO hidden treasure remains at any of the
 * four map locations; hidden-treasure tile-type values are 752 and 755. */
TEST(objectives, mission07_treasure_complete_when_all_dug) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(7);
  /* all four tiles cleared (not 752/755) -> complete */
  cov_obj_set_tile_word(55, 45, 0);
  cov_obj_set_tile_word(50, 27, 0);
  cov_obj_set_tile_word(35, 63, 0);
  cov_obj_set_tile_word(14, 68, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch;
}

TEST(objectives, mission07_treasure_blocked_when_one_remains) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(7);
  cov_obj_set_tile_word(55, 45, 755); /* one hidden treasure still present */
  cov_obj_set_tile_word(50, 27, 0);
  cov_obj_set_tile_word(35, 63, 0);
  cov_obj_set_tile_word(14, 68, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch;
}

/* Missions 03 and 13 (survival): complete iff the game turn counter
 * (*(u16*)(gameData + 140022) == GAME_TURN_COUNTER) exceeds 10, i.e. the
 * player has survived through turn 11. */
TEST(objectives, mission03_survival_gate_on_turn_counter) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(3);
  GAME_TURN_COUNTER = 11; /* > 10 -> survived */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  cov_obj_reset(3);
  GAME_TURN_COUNTER = 10; /* not yet past 10 -> blocked */
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch;
}

TEST(objectives, mission13_shares_survival_gate) {
  int gd = gameData, ch = dword_5448A0;
  cov_obj_reset(13); /* case 0xD falls through to the same survival check */
  GAME_TURN_COUNTER = 25;
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch;
}

/* Mission 05 uses two language-dependent elimination branches. The nonzero
 * language branch targets player 3. The zero-language branch targets players
 * 1 and 2. A building is live while construction_turns_remaining != -1; a
 * stack is live while at least one of its ten unit slots is occupied. */
static unsigned char cov_m05_gamedata[600000];

static void cov_m05_reset(int language_index) {
  memset(cov_m05_gamedata, 0, sizeof cov_m05_gamedata);
  gameData = (int)(intptr_t)cov_m05_gamedata;
  dword_5448A0 = 0;
  ACTIVE_MISSION_INDEX = 5;
  g_LanguageIndex = language_index;
}

static void cov_m05_set_building(int index, int owner, int live) {
  unsigned char *building = BUILDING_RECORD(index);
  memset(building, 0, BUILDING_RECORD_SIZE);
  building[2] = (unsigned char)owner;
  *(short *)(building + 16) = live ? 0 : -1;
}

static void cov_m05_set_stack(int index, int owner, int live) {
  unsigned char *stack = UNIT_STACK(index);
  int slot_index;

  memset(stack, 0, UNIT_STACK_STRIDE);
  UNIT_STACK_TILE_ROW(stack) = 10;
  UNIT_STACK_TILE_COLUMN(stack) = 10;
  UNIT_STACK_OWNER_INDEX(stack) = (unsigned char)owner;
  for (slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index)
    UNIT_SLOT_TYPE(UNIT_STACK_SLOT(stack, slot_index)) = -1;
  if (live)
    UNIT_SLOT_TYPE(UNIT_STACK_SLOT(stack, 0)) = UNIT_TYPE_PEASANT;
}

TEST(objectives, mission05_nonzero_language_complete_without_player3_survivors) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  cov_m05_set_building(4, 0, 1);
  cov_m05_set_stack(11, 0, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_nonzero_language_blocked_by_live_player3_building) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  cov_m05_set_building(4, 3, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_nonzero_language_ignores_destroyed_player3_building) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  cov_m05_set_building(4, 3, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_nonzero_language_blocked_by_live_player3_stack) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  cov_m05_set_stack(11, 3, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_nonzero_language_ignores_empty_player3_stack) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(1);
  cov_m05_set_stack(11, 3, 0);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

TEST(objectives, mission05_zero_language_targets_players1_and2_not_player3) {
  int gd = gameData, ch = dword_5448A0, lang = g_LanguageIndex;
  cov_m05_reset(0);
  cov_m05_set_building(4, 3, 1);
  cov_m05_set_stack(11, 3, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 1);
  cov_m05_reset(0);
  cov_m05_set_building(4, 1, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  cov_m05_reset(0);
  cov_m05_set_stack(11, 2, 1);
  CHECK_EQ(Mission_CheckObjectiveComplete(0, 0.0), 0);
  gameData = gd; dword_5448A0 = ch; g_LanguageIndex = lang;
}

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
