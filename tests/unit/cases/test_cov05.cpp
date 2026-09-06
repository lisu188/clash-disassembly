/* Batch 05: WCIsvListBase compat-list helpers, Building garrison/plague
 * helpers, Str/BattleMap filename helpers, SaveSlot path formatting,
 * DecisionDialog/QueenMarriageProposal/YesNoWindow widget helpers, and
 * Debug_GetUsedMemoryCount. */

/* ------------------------------------------------------------------ */
/* WCIsvListBase / WCCompat_* list-handle helpers                     */
/* ------------------------------------------------------------------ */

TEST(cov05_wclist, from_helpers) {
  static WCIsvListBase this_obj[4];
  memset(this_obj, 0, sizeof this_obj);
  TOUCH(WCCompat_ListFromBase(this_obj));
  TOUCH(WCCompat_ListFromHandle((int)(intptr_t)this_obj));
  TOUCH(WCCompat_ListFromHandle(0));
  TOUCH(WCCompat_LinkFromHandle((int)(intptr_t)this_obj));
  TOUCH(WCCompat_LinkFromHandle(0));
}

TEST(cov05_wclist, dtor_variant104_no_tail) {
  static WCCompatListBase list;
  memset(&list, 0, sizeof list);
  list.tail_link = 0; /* WCIsvListBase_dtor's tail_link!=0 branch skipped */
  TOUCH(WCIsvListBase_dtorVariant104((WCIsvListBase *)&list));
  CHECK(list.vtable != 0);
}

TEST(cov05_wclist, dtor_variant104_with_tail) {
  static WCCompatListBase list;
  memset(&list, 0, sizeof list);
  /* Any non-zero value is fine: WCIsvListBase_dtor only checks truthiness
   * before calling the no-op nullsub_7(this). */
  list.tail_link = 0xABCD;
  TOUCH(WCIsvListBase_dtorVariant104((WCIsvListBase *)&list));
  CHECK(list.vtable != 0);
}

TEST(cov05_wclist, base_next_null_and_empty) {
  static WCCompatListBase emptyList;
  memset(&emptyList, 0, sizeof emptyList);
  CHECK_EQ(WCIsvListBase_base_next(0, 0), 0);
  CHECK_EQ(WCIsvListBase_base_next((int)(intptr_t)&emptyList, 0), 0);
}

TEST(cov05_wclist, base_next_traversal) {
  static WCCompatListBase list;
  static WCCompatLink a, b;
  int handle, aHandle, bHandle;

  memset(&list, 0, sizeof list);
  memset(&a, 0, sizeof a);
  memset(&b, 0, sizeof b);

  aHandle = (int)(intptr_t)&a;
  bHandle = (int)(intptr_t)&b;
  a.next_link = bHandle;
  a.value = 1;
  b.next_link = 0;
  b.value = 2;
  list.head_link = aHandle;
  list.tail_link = bHandle;
  list.count = 2;
  handle = (int)(intptr_t)&list;

  /* cursor 0 never matches a real link address -> falls through to the
   * "return list->head_link" fallback. */
  CHECK_EQ(WCIsvListBase_base_next(handle, 0), aHandle);
  /* cursor matches the first node -> returns its next_link. */
  CHECK_EQ(WCIsvListBase_base_next(handle, aHandle), bHandle);
  /* cursor matches the last node -> returns 0 (its next_link). */
  CHECK_EQ(WCIsvListBase_base_next(handle, bHandle), 0);
  /* cursor matches nothing (arbitrary non-address int; never dereferenced,
   * only compared) -> same fallback path as cursor 0. */
  CHECK_EQ(WCIsvListBase_base_next(handle, 0x11223344), aHandle);
}

TEST(cov05_wclist, base_insert_branches) {
  static WCCompatListBase list;
  static WCCompatLink linkA, linkB;
  int handle, aHandle, bHandle;

  memset(&list, 0, sizeof list);
  memset(&linkA, 0, sizeof linkA);
  memset(&linkB, 0, sizeof linkB);
  handle = (int)(intptr_t)&list;
  aHandle = (int)(intptr_t)&linkA;
  bHandle = (int)(intptr_t)&linkB;

  /* !list branch */
  CHECK_EQ(WCIsvListBase_base_insert(0, aHandle), 0);
  /* !link branch */
  CHECK_EQ(WCIsvListBase_base_insert(handle, 0), 0);

  /* tail_link == 0 branch: sets list->head_link. */
  CHECK_EQ(WCIsvListBase_base_insert(handle, aHandle), aHandle);
  CHECK_EQ(list.head_link, aHandle);
  CHECK_EQ(list.count, 1);

  /* Simulate what the real caller (WCIsvListBase_AppendValue) does after
   * a successful insert: record the new tail. */
  list.tail_link = aHandle;

  /* tail_link != 0 branch: links onto the existing tail's next_link. */
  CHECK_EQ(WCIsvListBase_base_insert(handle, bHandle), bHandle);
  CHECK_EQ(linkA.next_link, bHandle);
  CHECK_EQ(list.count, 2);
}

TEST(cov05_wclist, base_sget_null_and_empty) {
  static WCCompatListBase emptyList;
  memset(&emptyList, 0, sizeof emptyList);
  CHECK_EQ(WCIsvListBase_base_sget(0), 0);
  CHECK_EQ(WCIsvListBase_base_sget((int)(intptr_t)&emptyList), 0);
}

TEST(cov05_wclist, base_sget_pop_to_empty) {
  static WCCompatListBase list;
  static WCCompatLink a, b;
  int handle, aHandle, bHandle;

  memset(&list, 0, sizeof list);
  memset(&a, 0, sizeof a);
  memset(&b, 0, sizeof b);
  aHandle = (int)(intptr_t)&a;
  bHandle = (int)(intptr_t)&b;
  a.next_link = bHandle;
  b.next_link = 0;
  list.head_link = aHandle;
  list.tail_link = bHandle;
  list.count = 5; /* > 0, exercises the decrement branch twice */
  handle = (int)(intptr_t)&list;

  CHECK_EQ(WCIsvListBase_base_sget(handle), aHandle);
  CHECK_EQ(list.head_link, bHandle);
  CHECK_EQ(list.count, 4);

  CHECK_EQ(WCIsvListBase_base_sget(handle), bHandle);
  /* head_link became 0 -> tail_link cleared too. */
  CHECK_EQ(list.head_link, 0);
  CHECK_EQ(list.tail_link, 0);
  CHECK_EQ(list.count, 3);

  /* Now the list is empty. */
  CHECK_EQ(WCIsvListBase_base_sget(handle), 0);
}

TEST(cov05_wclist, base_sget_count_not_positive) {
  static WCCompatListBase list;
  static WCCompatLink only;
  int handle;

  memset(&list, 0, sizeof list);
  memset(&only, 0, sizeof only);
  only.next_link = 0;
  list.head_link = (int)(intptr_t)&only;
  list.tail_link = (int)(intptr_t)&only;
  list.count = 0; /* count > 0 branch is false -> no decrement */
  handle = (int)(intptr_t)&list;

  TOUCH(WCIsvListBase_base_sget(handle));
  CHECK_EQ(list.count, 0);
}

TEST(cov05_wclist, append_and_pop_front) {
  static WCCompatListBase list;
  int handle;

  memset(&list, 0, sizeof list);
  handle = (int)(intptr_t)&list;

  /* Pop-front on an empty list returns the caller-supplied default. */
  CHECK_EQ(WCIsvListBase_PopFrontValue(handle, 777), 777);

  /* First append: base_insert's tail_link==0 branch. */
  CHECK(WCIsvListBase_AppendValue(handle, 10) != 0);
  /* Second append: base_insert's tail_link!=0 branch. */
  CHECK(WCIsvListBase_AppendValue(handle, 20) != 0);
  CHECK(WCIsvListBase_AppendValue(handle, 30) != 0);
  CHECK_EQ(list.count, 3);

  CHECK_EQ(WCIsvListBase_PopFrontValue(handle, -1), 10);
  CHECK_EQ(WCIsvListBase_PopFrontValue(handle, -1), 20);
  CHECK_EQ(WCIsvListBase_PopFrontValue(handle, -1), 30);
  /* List drained again. */
  CHECK_EQ(WCIsvListBase_PopFrontValue(handle, 999), 999);
}

TEST(cov05_wclist, base_destroy_drains_all) {
  static WCCompatListBase list;
  int handle;

  memset(&list, 0, sizeof list);
  handle = (int)(intptr_t)&list;
  TOUCH(WCIsvListBase_AppendValue(handle, 1));
  TOUCH(WCIsvListBase_AppendValue(handle, 2));
  TOUCH(WCIsvListBase_AppendValue(handle, 3));

  WCIsvListBase_base_destroy((WCIsvListBase *)&list);
  CHECK_EQ(list.head_link, 0);
  CHECK_EQ(list.tail_link, 0);
}

TEST(cov05_wclist, copy_append_all) {
  static WCCompatListBase src;
  static _DWORD dest[8];
  int srcHandle;

  memset(&src, 0, sizeof src);
  memset(dest, 0, sizeof dest);
  srcHandle = (int)(intptr_t)&src;

  TOUCH(WCIsvListBase_AppendValue(srcHandle, 100));
  TOUCH(WCIsvListBase_AppendValue(srcHandle, 200));
  TOUCH(WCIsvListBase_AppendValue(srcHandle, 300));

  TOUCH(WCIsvListBase_CopyAppendAll(dest, (_DWORD *)&src, 0));
}

/* ------------------------------------------------------------------ */
/* Building garrison / plague helpers                                 */
/* ------------------------------------------------------------------ */

TEST(cov05_building, clear_garrison_timers) {
  static unsigned char buf[512];
  int addr;

  memset(buf, 0xFF, sizeof buf);
  addr = (int)(intptr_t)buf;
  CHECK_EQ(Building_ClearGarrisonTrainingTimer(addr, 0), addr);
  CHECK_EQ((buf[390] & 0x07), 0);

  memset(buf, 0xFF, sizeof buf);
  CHECK_EQ(Building_ClearGarrisonRepairTimer(addr, 0), addr);
  CHECK_EQ((buf[390] & 0x38), 0);
}

TEST(cov05_building, count_special_personage_entries) {
  static unsigned char buf[1024];
  int addr;
  int i;

  /* All 12 slots empty (-1) -> loop reaches the "a1==v1" exit immediately
   * on the first slot. */
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(__int16 *)(buf + 18 + 31 * i) = -1;
  addr = (int)(intptr_t)buf;
  CHECK_EQ(Building_CountSpecialPersonageGarrisonEntries(addr), 0);
  CHECK_EQ(Building_DrawGarrisonRow(addr), 0);

  /* Mix of special-personage slots and ordinary/empty slots. */
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(__int16 *)(buf + 18 + 31 * i) = -1;
  *(__int16 *)(buf + 18 + 31 * 0) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
  *(__int16 *)(buf + 18 + 31 * 1) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
  *(__int16 *)(buf + 18 + 31 * 2) = UNIT_TYPE_PEASANT; /* non-matching, non -1 */
  CHECK_EQ(Building_CountSpecialPersonageGarrisonEntries(addr), 2);
  CHECK_EQ(Building_DrawGarrisonRow(addr), 2);
}

TEST(cov05_building, count_noncombat_garrison_entries) {
  static unsigned char buf[1024];
  int addr;
  int i;

  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(__int16 *)(buf + 18 + 31 * i) = -1;
  addr = (int)(intptr_t)buf;
  CHECK_EQ(Building_CountNonCombatGarrisonEntries(addr), 0);

  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(__int16 *)(buf + 18 + 31 * i) = -1;
  *(__int16 *)(buf + 18 + 31 * 0) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
  *(__int16 *)(buf + 18 + 31 * 1) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
  *(__int16 *)(buf + 18 + 31 * 2) = UNIT_TYPE_GOLD_CARGO;
  *(__int16 *)(buf + 18 + 31 * 3) = UNIT_TYPE_PEASANT_CARGO;
  *(__int16 *)(buf + 18 + 31 * 4) = UNIT_TYPE_PEASANT; /* non-matching */
  CHECK_EQ(Building_CountNonCombatGarrisonEntries(addr), 4);
}

TEST(cov05_building, has_special_personage_entries) {
  static unsigned char buf[1024];
  int addr;
  int i;

  /* No matching slot within the first 12 -> returns 0. */
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(__int16 *)(buf + 18 + 31 * i) = UNIT_TYPE_PEASANT;
  addr = (int)(intptr_t)buf;
  CHECK_EQ(Building_HasSpecialPersonageGarrisonEntries(addr), 0);

  /* Matching slot found -> returns 1 (break path). */
  *(__int16 *)(buf + 18 + 31 * 3) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
  CHECK_EQ(Building_HasSpecialPersonageGarrisonEntries(addr), 1);
}

TEST(cov05_building, is_unit_licence_eligible) {
  static unsigned char buf[512];
  int a2 = UNIT_TYPE_PEASANT; /* index 0 into the size-1 tech-level tables */

  /* a1[4] == 0 -> immediate false. */
  memset(buf, 0, sizeof buf);
  CHECK_EQ(Building_IsUnitLicenceEligible((char *)buf, (unit_type)a2), 0);

  /* a1[4] != 2 (OtherModes table), tech level insufficient -> false. */
  memset(buf, 0, sizeof buf);
  buf[4] = 1;
  buf[444] = 0;
  CHECK_EQ(Building_IsUnitLicenceEligible((char *)buf, (unit_type)a2), 0);

  /* a1[4] == 2 (Mode2 table), tech sufficient, smiths bit clear (loop
   * scanned), workshop bit clear (loop scanned) -> reaches final return. */
  memset(buf, 0, sizeof buf);
  buf[4] = 2;
  buf[444] = 7;
  buf[416] = 0;
  TOUCH(Building_IsUnitLicenceEligible((char *)buf, (unit_type)a2));

  /* a1[4] != 2, tech sufficient, smiths-required bit set (skip loop),
   * workshop-bypass bit set -> early "return 1". */
  memset(buf, 0, sizeof buf);
  buf[4] = 1;
  buf[444] = 7;
  buf[416] = 0x10 | 0x04;
  CHECK_EQ(Building_IsUnitLicenceEligible((char *)buf, (unit_type)a2), 1);
}

TEST(cov05_building, nation_total_value) {
  static unsigned char data[GAMEDATA_SAVE_IMAGE_BYTES];
  static unsigned char before[GAMEDATA_SAVE_IMAGE_BYTES];
  const int saved_game_data = gameData;
  const uintptr_t data_address = (uintptr_t)data;

  CHECK(data_address + sizeof data <= INT32_MAX);
  if ( data_address + sizeof data > INT32_MAX )
    return;
  memset(data, 0, sizeof data);
  gameData = (int)data_address;

  /* Fixture writes use memcpy: the original records have odd strides. */
  const auto put_word = [&](int offset, int16_t value) {
    memcpy(data + offset, &value, sizeof value);
  };
  const auto set_building = [&](int index, unsigned char owner,
                                unsigned char kind, int16_t construction,
                                uint16_t population, uint32_t gold) {
    const int offset = BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * index;
    data[offset + 2] = owner;
    data[offset + 4] = kind;
    put_word(offset + 16, construction);
    memset(data + offset + 402, 0xFF, 12);
    memcpy(data + offset + 430, &population, sizeof population);
    memcpy(data + offset + 438, &gold, sizeof gold);
  };
  const auto expect_score = [&](int player, int expected) {
    memcpy(before, data, sizeof data);
    CHECK_EQ(AI_TickNationPostTurn(player), expected);
    CHECK(memcmp(before, data, sizeof data) == 0);
  };
  for ( int index = 0; index < UNIT_STACK_TABLE_COUNT; ++index )
    put_word(UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * index + 6, -1);

  /* Fixed original-code results, not a duplicate implementation oracle. */
  for ( int player = 0; player < 6; ++player )
    expect_score(player, 0);
  set_building(0, 0, 2, 0, 100, 400);
  expect_score(0, 500);
  set_building(99, 0, 1, 7, 150, 600);
  expect_score(0, 1250);
  memcpy(before, data, sizeof data);
  CHECK_EQ(Building_GetTotalValue(gameData + BUILDING_TABLE_OFFSET), 500);
  CHECK_EQ(Building_GetTotalValue(gameData + BUILDING_TABLE_OFFSET + 99 * BUILDING_RECORD_SIZE), 750);
  CHECK(memcmp(before, data, sizeof data) == 0);

  const int last_building = BUILDING_TABLE_OFFSET + 99 * BUILDING_RECORD_SIZE;
  data[last_building + 2] = 1;
  expect_score(0, 500);
  expect_score(1, 750);
  data[last_building + 2] = 0;
  const unsigned char excluded_kinds[] = {0, 3, 127, 128, 255};
  for ( unsigned char kind : excluded_kinds )
  {
    data[last_building + 4] = kind;
    expect_score(0, 500);
  }
  data[last_building + 4] = 1;
  put_word(last_building + 16, -1);
  expect_score(0, 500);
  put_word(last_building + 16, INT16_MIN);
  expect_score(0, 1250); /* The original excludes only the -1 sentinel. */
  put_word(last_building + 16, 0);

  const int first_stack = UNIT_STACK_TABLE_OFFSET;
  const int last_stack = UNIT_STACK_TABLE_OFFSET + 499 * UNIT_STACK_STRIDE;
  put_word(first_stack + 6, UNIT_TYPE_GOLD_CARGO);
  data[first_stack + 15] = 10;
  put_word(first_stack + 6 + UNIT_STACK_SLOT_STRIDE, -1);
  put_word(first_stack + 6 + 9 * UNIT_STACK_SLOT_STRIDE, UNIT_TYPE_PEASANT_CARGO);
  data[first_stack + 15 + 9 * UNIT_STACK_SLOT_STRIDE] = 0x80;
  expect_score(0, 1132); /* -128 cargo after an empty intermediate slot. */

  put_word(last_stack + 6, UNIT_TYPE_PEASANT);
  put_word(last_stack + 6 + 9 * UNIT_STACK_SLOT_STRIDE, UNIT_TYPE_GOLD_CARGO);
  data[last_stack + 15 + 9 * UNIT_STACK_SLOT_STRIDE] = 0xFF;
  expect_score(0, 1131); /* Last stack/slot contributes signed -1. */
  put_word(first_stack + 6, -1);
  expect_score(0, 1249); /* Empty first slot suppresses that whole stack. */
  data[last_stack + 4] = 1;
  expect_score(0, 1250);
  expect_score(1, -1);
  expect_score(-1, 0);
  expect_score(256, 0);
  gameData = saved_game_data;
}

TEST(cov05_building, update_plague_state) {
  static unsigned char buf[512];
  int addr;

  /* Plague already active (offset 435 low 3 bits != 0): decays plague
   * counter and shrinks population. */
  memset(buf, 0, sizeof buf);
  buf[435] = 3;
  *(_WORD *)(buf + 430) = 500;
  addr = (int)(intptr_t)buf;
  TOUCH(Building_UpdatePlagueState((unsigned int)addr));

  /* No active plague, population below 1000 -> skips the outbreak roll
   * entirely. */
  memset(buf, 0, sizeof buf);
  buf[435] = 0;
  *(_WORD *)(buf + 430) = 200;
  TOUCH(Building_UpdatePlagueState((unsigned int)addr));

  /* No active plague, population >= 1000 -> takes the outbreak-roll path
   * (may or may not trip below 100 depending on RNG, but both are cheap
   * to exercise across repeated calls). */
  {
    int i;
    for (i = 0; i < 20; ++i) {
      memset(buf, 0, sizeof buf);
      buf[435] = 0;
      *(_WORD *)(buf + 430) = 1000;
      TOUCH(Building_UpdatePlagueState((unsigned int)addr));
    }
  }
}

/* ------------------------------------------------------------------ */
/* Str_SwapAndConcatInPlace / BattleMap_GetOutcomeVariantFileName      */
/* ------------------------------------------------------------------ */

TEST(cov05_str, swap_and_concat_in_place) {
  static char a1buf[128];
  static char a2buf[128];

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  strcpy(a1buf, "AB");
  strcpy(a2buf, "CD");
  TOUCH(Str_SwapAndConcatInPlace(a1buf, a2buf));
}

TEST(cov05_battlemap, outcome_variant_filename_n_prefix) {
  static unsigned char fakeGameData[2048];
  static char nameBuf[64];
  int saved_gameData = gameData;

  memset(fakeGameData, 0, sizeof fakeGameData);
  /* tile = gameData + 1400*a2 + 14*a3; a2=0,a3=0 -> tile == gameData. */
  *(_WORD *)(fakeGameData + 0) = 0;      /* primary */
  *(_WORD *)(fakeGameData + 2) = 0xFFFF; /* secondary: force invalid */
  *(_WORD *)(fakeGameData + 4) = 0;      /* tertiary: valid, index 0 -> "nt" */

  gameData = (int)(intptr_t)fakeGameData;
  memset(nameBuf, 0, sizeof nameBuf);
  /* BattleMapFileName's Debug_Log call only touches its args, safe. */
  TOUCH(BattleMap_GetOutcomeVariantFileName(nameBuf, 0, 0));
  gameData = saved_gameData;
}

TEST(cov05_battlemap, outcome_variant_filename_non_n_prefix) {
  static unsigned char fakeGameData[2048];
  static char nameBuf[64];
  int saved_gameData = gameData;

  memset(fakeGameData, 0, sizeof fakeGameData);
  *(_WORD *)(fakeGameData + 1400 + 0) = 0; /* primary */
  *(_WORD *)(fakeGameData + 1400 + 2) = 0; /* secondary valid -> off_516410[0]+1 == "t" */
  *(_WORD *)(fakeGameData + 1400 + 4) = 0; /* tertiary (unused, secondary wins) */

  gameData = (int)(intptr_t)fakeGameData;
  memset(nameBuf, 0, sizeof nameBuf);
  TOUCH(BattleMap_GetOutcomeVariantFileName(nameBuf, 1, 0));
  gameData = saved_gameData;
}

/* ------------------------------------------------------------------ */
/* SaveSlot path formatting                                           */
/* ------------------------------------------------------------------ */

TEST(cov05_saveslot, format_paths) {
  static char pathBuf[64];

  memset(pathBuf, 0, sizeof pathBuf);
  TOUCH(SaveSlot_FormatDataFilePath(3, pathBuf));
  CHECK(strstr(pathBuf, "save\\") != NULL);

  memset(pathBuf, 0, sizeof pathBuf);
  TOUCH(SaveSlot_FormatFactsFilePath(7, pathBuf));
  CHECK(strstr(pathBuf, "save\\") != NULL);
}

/* ------------------------------------------------------------------ */
/* DecisionDialog / QueenMarriageProposal / YesNoWindow widget helpers */
/* ------------------------------------------------------------------ */

TEST(cov05_decision, confirm_and_cancel) {
  static unsigned char widget[128];
  int saved_active = g_AppIsActive;
  int saved_disabled = g_DecisionDialogConfirmDisabled;

  memset(widget, 0, sizeof widget);
  /* Keep UIWidget_RefreshActionButtonState on its safe path: field @0 >=
   * 640 skips the arbitrary widget-transition-callback dispatch. */
  *(_DWORD *)(widget + 0) = 1000;
  /* field @49 == 0 skips Audio_PlayButtonSound. */
  *(_DWORD *)(widget + 49) = 0;
  /* g_AppIsActive == 1 keeps Platform_PumpMessagesAndBlitFrame on its
   * fast, non-blocking early-return path (avoids the real Win32-message
   * GetMessageA wait loop). */
  g_AppIsActive = 1;

  g_DecisionDialogConfirmDisabled = 0;
  TOUCH(DecisionDialog_ConfirmIfAllowed((uintptr_t)widget, 0));
  CHECK_EQ(g_DecisionDialogExitSignal, 1);
  CHECK_EQ(g_DecisionDialogResult, 1);

  g_DecisionDialogConfirmDisabled = 1;
  TOUCH(DecisionDialog_ConfirmIfAllowed((uintptr_t)widget, 0));

  TOUCH(DecisionDialog_Cancel((uintptr_t)widget, 0));
  CHECK_EQ(g_DecisionDialogExitSignal, 1);
  CHECK_EQ(g_DecisionDialogResult, 0);

  g_AppIsActive = saved_active;
  g_DecisionDialogConfirmDisabled = saved_disabled;
}

TEST(cov05_queen, write_and_rebuild_widgets) {
  static unsigned char record[64];
  static unsigned char widgets[3 * 64];
  static _DWORD *spriteHolder;
  static const char soundName[] = "male";

  memset(record, 0xAA, sizeof record);
  QueenMarriageProposal_WriteButtonWidgetRecord(
      record, 10, 20, 1, 2, 0x12345678, &spriteHolder, soundName);
  CHECK_EQ(*(_DWORD *)(record + 0), 10);
  CHECK_EQ(*(_DWORD *)(record + 4), 20);

  memset(widgets, 0xAA, sizeof widgets);
  QueenMarriageProposal_RebuildButtonWidgets(widgets, &spriteHolder, 5, 6, 7);
  CHECK_EQ(*(_DWORD *)(widgets + 0), 5);
  CHECK_EQ(*(_DWORD *)(widgets + 53 + 0), 7);
}

TEST(cov05_yesno, write_and_rebuild_widgets) {
  static unsigned char record[64];
  static unsigned char widgets[3 * 64];

  memset(record, 0xAA, sizeof record);
  YesNoWindow_WriteButtonWidgetRecord(record, 1, 2, 3, 4, 0x87654321);
  CHECK_EQ(*(_DWORD *)(record + 0), 1);
  CHECK_EQ(*(_DWORD *)(record + 4), 2);

  memset(widgets, 0xAA, sizeof widgets);
  YesNoWindow_RebuildButtonWidgets(widgets, 8, 9, 10);
  CHECK_EQ(*(_DWORD *)(widgets + 0), 8);
  CHECK_EQ(*(_DWORD *)(widgets + 53 + 0), 10);
}

/* ------------------------------------------------------------------ */
/* Debug_GetUsedMemoryCount                                            */
/* ------------------------------------------------------------------ */

TEST(cov05_debug, used_memory_count) {
  CHECK_EQ(Debug_GetUsedMemoryCount(), 0);
}
