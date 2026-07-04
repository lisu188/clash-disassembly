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
