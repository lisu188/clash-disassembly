/* cov2_01: second-pass coverage additions for a mixed batch of previously
 * partially-covered functions (Rules_MultifieldReplaceRange, Rules_MathPow,
 * Map_ClassifyFogOfWarOverlayForPlayer, Rules_BsaveSymbolTable,
 * Rules_RegisterBuiltinFunctionGroups, UnitStack_HasGoldCargo,
 * Compat_FileSystemFindMountedPathById, Building_FindFreePrisonerSlot,
 * Definstances_DeleteRecord, Rules_CreateJoinPartialMatch,
 * Building_HandleUpgradeButtonAction, Rules_Dependencies,
 * Rules_MergeConstraintValueList, Rules_BloadCommand, Rules_BatchStarCommand,
 * Module_PrintPPFormByName, Rules_PortCollectSupply,
 * Rules_ReportSymbolTypeError, Rules_HostSymbolp,
 * Defglobal_CloseConstructCodeFiles, MapTile_HasBuilding,
 * SaveSlot_LoadReservedSlot10, Compat_FileFinderGetSize,
 * Defglobal_RegisterResetGlobalsCommands, Unit_BuildShotAnimPaletteSpritePath,
 * WCIsvListBase_base_insert, Compat_StringHolderFindSubstringOffset,
 * Rules_HashBitmapValue, Rules_DribbleOffCommand,
 * Rules_WriteExpressionRefToCode, Rules_RetractObjectPatternMatches,
 * Compiler_WriteObjectPatternsAndRulesToCode).
 *
 * Each test runs isolated in its own forked child (per tests/unit/test_all.c),
 * so calls that crash/exit/spin are safe; we chase real additional line
 * coverage rather than avoiding risk. Several of the existing first-pass
 * tests for functions in this batch turned out to pass a *stack* buffer's
 * address through a 32-bit int/DWORD parameter -- on this 64-bit -no-pie
 * build that truncates to a wild address and crashes almost immediately,
 * which explains why some of these functions show much lower coverage than
 * their existing test file would suggest. Every buffer below whose address
 * is threaded through such a narrowed field is declared `static` for that
 * reason. */

/* ------------------------------------------------------------------ */
/* Rules_MultifieldReplaceRange -- drive the copy-loop body and the       */
/* a5-is-itself-a-multifield splice branch, neither of which the existing */
/* test_cov16.c success-path test reaches (it uses a4=1, which makes the  */
/* prefix-copy loop trip count 0, and a scalar a5, skipping the a5[1]==4  */
/* branch entirely).                                                     */
/* ------------------------------------------------------------------ */
TEST(cov2_01_multifieldreplace, prefix_loop_and_multifield_splice) {
  static _DWORD storage[64], storage2[64];
  static _DWORD a1buf[8], a2buf[8], a5buf[8];
  memset(storage, 0, sizeof storage);
  memset(storage2, 0, sizeof storage2);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a5buf, 0, sizeof a5buf);

  /* source multifield: begin=0, end=2 -> count 3 */
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0;
  a2buf[4] = 2;

  /* replacement value is itself a multifield (type tag 4): begin=0, end=1
   * -> count 2, splicing 2 elements in place of the replaced range. */
  a5buf[1] = 4;
  a5buf[2] = (_DWORD)(intptr_t)storage2;
  a5buf[3] = 0;
  a5buf[4] = 1;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  /* a3=3 (range end), a4=2 (range start) -> prefix of 1 element (index 0)
   * gets copied by the main copy loop before the replacement is spliced in. */
  TOUCH(Rules_MultifieldReplaceRange(a1buf, a2buf, 3, 2, a5buf, 0));
}

/* ------------------------------------------------------------------ */
/* Rules_MathPow -- the existing test_cov17.c call only ever exercises   */
/* the Lexer_TokenExpect(2) mismatch branch (fake zeroed arg chain ->    */
/* count 0). Build a real 2-node argument chain so Rules_RtnArgCount()   */
/* reports 2, giving Lexer_TokenExpect(2) a chance to take its "match"   */
/* branch and drive into the two Lexer_ParseValueList calls (whose       */
/* Rules_RtnUnknown "not found" fallback needs a valid function-record   */
/* chain to stay memory-safe, same net as documented in test_cov16.c).   */
/* ------------------------------------------------------------------ */
TEST(cov2_01_mathpow, two_arg_chain_attempt) {
  static unsigned char root[64], node1[64], node2[64];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  memset(node2, 0, sizeof node2);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);

  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(root + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = (_DWORD)(intptr_t)node2;
  *(_DWORD *)(node2 + 10) = 0;

  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_MathPow(0.0));
  dword_51A960 = saved;
}

/* ------------------------------------------------------------------ */
/* Map_ClassifyFogOfWarOverlayForPlayer -- the existing test_cov01.c     */
/* test only ever calls it with every neighbor coordinate negative (so   */
/* Map_IsTileVisibleToPlayer short-circuits to false for all 9 probes    */
/* before ever touching gameData). Give it a real, populated gameData    */
/* buffer and in-bounds coordinates instead, sweeping several different  */
/* "revealed tile" bit patterns around the center tile so the 9 probe    */
/* results (and thus the decompiler-lost v9/v10 tail-branch selection)   */
/* differ from run to run, chasing more of the many equivalent          */
/* return-code branches at the end of the function. */
/* ------------------------------------------------------------------ */
static void cov2_01_set_revealed(char *gd, int player, int row, int col) {
  /* mirrors PLAYER_DATA/PLAYER_REVEALED_TILE_ROW_BYTES/PLAYER_REVEALED_TILES_OFFSET */
  int byte_off = 140024 + 1423 * player + 13 * row + (col >> 3) + 57;
  gd[byte_off] |= (1 << (col & 7));
}

TEST(cov2_01_fogofwar, populated_gamedata_sweep) {
  static char gd[2200000];
  int saved = gameData;
  int savedPlayer = g_CurrentPlayerIndex;
  memset(gd, 0, sizeof gd);
  *(_DWORD *)(gd + 140000) = 200; /* map width */
  *(_DWORD *)(gd + 140004) = 200; /* map height */
  gameData = (int)(intptr_t)gd;
  g_CurrentPlayerIndex = 0;

  /* center + a scattering of neighbors revealed -> a real, non-trivial v9 */
  cov2_01_set_revealed(gd, 0, 50, 50);
  cov2_01_set_revealed(gd, 0, 49, 49);
  cov2_01_set_revealed(gd, 0, 50, 49);
  cov2_01_set_revealed(gd, 0, 51, 51);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(50, 50, 0));

  /* different subset of neighbors revealed */
  memset(gd + 140024, 0, 2000000);
  cov2_01_set_revealed(gd, 0, 60, 60);
  cov2_01_set_revealed(gd, 0, 61, 60);
  cov2_01_set_revealed(gd, 0, 61, 61);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(60, 60, 0));

  /* every one of the 9 probed tiles revealed */
  {
    int r, c;
    for (r = 69; r <= 71; ++r)
      for (c = 69; c <= 71; ++c)
        cov2_01_set_revealed(gd, 0, r, c);
  }
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(70, 70, 0));

  /* only the far corner revealed */
  memset(gd + 140024, 0, 2000000);
  cov2_01_set_revealed(gd, 0, 81, 81);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(80, 80, 0));

  gameData = saved;
  g_CurrentPlayerIndex = savedPlayer;
}

/* ------------------------------------------------------------------ */
/* Rules_BsaveSymbolTable -- the existing test_cov14.c call bootstraps   */
/* the atom tables but never interns anything into them, so the table's  */
/* buckets are all empty and the recovered bucket-sweep's inner          */
/* "for (i = *v2; i; i = *i)" traversal never actually runs its body.    */
/* Intern a batch of real strings first (via the string-builtins         */
/* registration path, which calls Rules_RegisterHostFunction ->          */
/* Str_Intern for each function name) so the table Rules_GetSymbolTable()*/
/* returns (dword_54DD50, the exact table Str_Intern populates) has real */
/* bucket chains to walk before the documented 32-vs-64-bit stride bug   */
/* eventually runs the sweep off the end of the allocation. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_bsavesymtab, populated_table_sweep) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterStringBuiltins());
  TOUCH(Rules_RegisterMathBuiltins());
  TOUCH(Rules_BsaveSymbolTable(0));
}

/* ------------------------------------------------------------------ */
/* Rules_RegisterBuiltinFunctionGroups -- the existing test_cov10.c call */
/* never bootstraps the reserve arena / atom tables first, so the first  */
/* Rules_Register*Functions() call in the chain (which interns host      */
/* function names via Str_Intern into the NULL-by-default dword_54DD50   */
/* table) crashes immediately, and every subsequent call in this         */
/* straight-line wrapper is unreachable. Bootstrapping first lets the    */
/* whole chain complete. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_registerbuiltingroups, bootstrapped) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterBuiltinFunctionGroups());
}

/* ------------------------------------------------------------------ */
/* UnitStack_HasGoldCargo -- the existing test_cov02.c test passes a     */
/* *stack* buffer's address through the `int a1` parameter, which        */
/* truncates to a wild address on this 64-bit build and crashes on the   */
/* very first dereference; redo the same three scenarios with static    */
/* storage so they actually complete and cover the full function body.   */
/* ------------------------------------------------------------------ */
TEST(cov2_01_hasgoldcargo, static_buffer_all_branches) {
  static unsigned char buf[512];
  int i;

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = UNIT_TYPE_GOLD_CARGO;
  CHECK_EQ(UnitStack_HasGoldCargo((int)(intptr_t)buf), 1);

  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1;
  CHECK_EQ(UnitStack_HasGoldCargo((int)(intptr_t)buf), 0);

  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0;
  CHECK_EQ(UnitStack_HasGoldCargo((int)(intptr_t)buf), 0);
}

/* ------------------------------------------------------------------ */
/* Compat_FileSystemFindMountedPathById -- same stack-vs-static issue as */
/* above (test_cov09.c's a1buf/entries are plain stack arrays); redo     */
/* with static storage. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_findmountedpath, static_buffer_all_branches) {
  static _DWORD a1buf[16];
  static _DWORD entries[8];

  memset(a1buf, 0, sizeof(a1buf));
  memset(entries, 0, sizeof(entries));

  a1buf[28 / 4] = 0;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 42), 0);

  entries[0] = 1234;
  entries[1] = 5678;
  a1buf[20 / 4] = (_DWORD)(intptr_t)entries;
  a1buf[28 / 4] = 1;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 1234), 5678);
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 9999), 0);

  entries[4] = 111;
  entries[5] = 222;
  a1buf[28 / 4] = 2;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 111), 222);
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 1234), 5678);
}

/* ------------------------------------------------------------------ */
/* Building_FindFreePrisonerSlot -- pure linear scan over 3 prisoner     */
/* slots; drive both the "found a free slot" and "all slots occupied"   */
/* branches with static storage. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_findfreeprisonerslot, found_and_full) {
  static unsigned char building[1024];

  memset(building, 0, sizeof building);
  /* slot 0 occupied (type != -1), slot 1 free (type == -1) */
  *(char *)(building + BUILDING_PRISONER_SLOT_BASE_OFFSET) = 3;
  *(char *)(building + BUILDING_PRISONER_SLOT_BASE_OFFSET + BUILDING_PRISONER_SLOT_STRIDE) = -1;
  CHECK_EQ(Building_FindFreePrisonerSlot((int)(intptr_t)building), 1);

  memset(building, 0, sizeof building);
  {
    int i;
    for (i = 0; i < BUILDING_PRISONER_SLOT_COUNT; ++i)
      *(char *)(building + BUILDING_PRISONER_SLOT_BASE_OFFSET + BUILDING_PRISONER_SLOT_STRIDE * i) = (char)(i + 1);
  }
  CHECK_EQ(Building_FindFreePrisonerSlot((int)(intptr_t)building), -1);
}

/* ------------------------------------------------------------------ */
/* Definstances_DeleteRecord -- the existing test_cov21.c call leaves    */
/* dword_51A1AC (Rules_IsBloaded's backing flag) at its default 0, so    */
/* the "if (Rules_IsBloaded()) return 0;" branch is never taken. Flip it */
/* to exercise that guard explicitly. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_definstdeleterecord, bloaded_guard) {
  int saved = dword_51A1AC;
  dword_51A1AC = 1;
  CHECK_EQ(Definstances_DeleteRecord(), 0);
  dword_51A1AC = saved;
}

TEST(cov2_01_definstdeleterecord, not_bloaded_variety) {
  int saved = dword_51A1AC;
  dword_51A1AC = 0;
  TOUCH(Definstances_DeleteRecord());
  dword_51A1AC = saved;
}

/* ------------------------------------------------------------------ */
/* Rules_CreateJoinPartialMatch -- the existing test_cov13.c test sets   */
/* a3[9] (action) and a3[5] (join) both to 0, skipping the activation    */
/* and join-network branches entirely. Drive both: a nonzero action      */
/* (Rules_AddActivation), and a nonzero join whose own back-pointer      */
/* matches a3 (single Rules_DriveJoinNetwork call), plus a join chain     */
/* whose back-pointer does *not* match (drives the do-while loop over    */
/* the +28 "next join" links). */
/* ------------------------------------------------------------------ */
TEST(cov2_01_createjoinpartialmatch, action_and_direct_join_match) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], joinbuf[16];
  Mem_InitReserveBlock(0, 0);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(joinbuf, 0, sizeof joinbuf);

  a3buf[9] = 1; /* nonzero action -> Rules_AddActivation branch */
  a3buf[5] = (_DWORD)(intptr_t)joinbuf; /* join */
  joinbuf[4] = (_DWORD)(intptr_t)a3buf; /* join+16 == a3 -> single-call branch */
  joinbuf[7] = 0; /* join+28 next -> unused on this branch */

  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
}

TEST(cov2_01_createjoinpartialmatch, join_chain_do_while) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], join1[16], join2[16];
  Mem_InitReserveBlock(0, 0);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(join1, 0, sizeof join1);
  memset(join2, 0, sizeof join2);

  a3buf[9] = 0;
  a3buf[5] = (_DWORD)(intptr_t)join1;
  join1[4] = 0; /* join1+16 != a3 -> do-while branch */
  join1[7] = (_DWORD)(intptr_t)join2; /* next join */
  join2[4] = 0;
  join2[7] = 0; /* chain ends */

  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
}

/* ------------------------------------------------------------------ */
/* Building_HandleUpgradeButtonAction -- not exercised at all by the     */
/* first pass (deemed unsafe under the old single-process harness). The  */
/* "v2" the recovered C reads inside Building_TryStartUpgrade is really   */
/* the same a1 register reloaded (confirmed against the disassembly at   */
/* 0041F890: `mov edx, eax` then `call sub_41F850` with edx pushed/popped */
/* across the call), so it is a real, controllable pointer, not garbage. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_buildingupgradebtn, cannot_start_upgrade) {
  static unsigned char rec[1024];
  int saved = g_SelectedBuildingRecord;
  memset(rec, 0, sizeof rec);
  rec[421] = 2; /* Building_CanStartUpgrade's first condition (< 2) fails */
  g_SelectedBuildingRecord = (int)(intptr_t)rec;
  CHECK_EQ(Building_HandleUpgradeButtonAction(), 0);
  g_SelectedBuildingRecord = saved;
}

TEST(cov2_01_buildingupgradebtn, can_start_upgrade_succeeds) {
  static unsigned char rec[1024];
  int saved = g_SelectedBuildingRecord;
  memset(rec, 0, sizeof rec);
  rec[421] = 0;                     /* < 2 */
  rec[444] = 2;                     /* (rec[444]&7)-1 == 1 > rec[421] */
  rec[429] = 0;                     /* not already upgrading */
  *(int *)(rec + 438) = 1;          /* >= byte_513A7F[0] (1) */
  g_SelectedBuildingRecord = (int)(intptr_t)rec;
  TOUCH(Building_HandleUpgradeButtonAction());
  g_SelectedBuildingRecord = saved;
}

/* ------------------------------------------------------------------ */
/* Rules_Dependencies -- the existing test_cov13.c call never points     */
/* dword_51A960 at anything, so Lexer_TokenExpect(1) -> Rules_RtnArgCount */
/* dereferences address 0+6 and crashes on the very first line. Point it */
/* at a zeroed empty-list node first (matching the established safe      */
/* pattern) so the guard executes cleanly, then also try a real 1-node   */
/* chain in case it drives further into Rules_ResolveFactOrInstanceArg.  */
/* ------------------------------------------------------------------ */
TEST(cov2_01_dependencies, empty_chain_safe) {
  static _DWORD fake_expr[16];
  int saved = dword_51A960;
  memset(fake_expr, 0, sizeof fake_expr);
  dword_51A960 = (int)(intptr_t)fake_expr;
  TOUCH(Rules_Dependencies(0.0));
  dword_51A960 = saved;
}

TEST(cov2_01_dependencies, one_node_chain_attempt) {
  static unsigned char root[64], node1[64];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);

  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(root + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = 0;

  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_Dependencies(0.0));
  dword_51A960 = saved;
}

/* ------------------------------------------------------------------ */
/* Rules_MergeConstraintValueList -- the existing test_cov23.c test only */
/* drives the "no match anywhere in the chain" path. Build a chain whose  */
/* head node's value matches `result` (the first argument) immediately,  */
/* so the inner while's "if (result == v3) break;" fires and the         */
/* AST_NewNode-based list-prepend code actually runs. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_mergeconstraintvaluelist, immediate_match_prepends_node) {
  static unsigned char node1[64], a3buf[64], a2buf[64];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(node1, 0, sizeof(node1));
  memset(a3buf, 0, sizeof(a3buf));
  memset(a2buf, 0, sizeof(a2buf));

  *(short *)(node1 + 0) = 999;   /* matches `result` == v3 immediately */
  *(int *)(node1 + 2) = 1234;    /* payload word read by AST_NewNode */
  *(int *)(node1 + 10) = 0;      /* fallback/next chain -> ends cleanly */

  *(int *)(a3buf + 6) = (int)(intptr_t)node1; /* a3+6 -> head */

  TOUCH(Rules_MergeConstraintValueList(999, (int)(intptr_t)a2buf, (int)(intptr_t)a3buf));
}

/* ------------------------------------------------------------------ */
/* Rules_BloadCommand / Rules_BatchStarCommand -- the existing            */
/* test_cov10.c/test_cov15.c calls always use a zeroed (count-0) arg      */
/* chain, so Lexer_TokenExpect(1) always mismatches and the wrapper       */
/* returns 0 before ever calling Rules_GetFileNameArg. Try a real 1-node  */
/* chain (with the safe function-record net Rules_GetFileNameArg's own    */
/* Rules_RtnUnknown call needs) for a chance at reaching further. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_bloadcommand, one_node_chain_attempt) {
  static unsigned char root[64], node1[64];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);

  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(root + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = 0;

  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_BloadCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov2_01_batchstarcommand, one_node_chain_attempt) {
  static unsigned char root[64], node1[64];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);

  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(root + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = 0;

  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_BatchStarCommand(0, 0.0));
  dword_51A960 = saved;
}

/* ------------------------------------------------------------------ */
/* Module_PrintPPFormByName -- the existing test_cov20.c test only        */
/* exercises the "module not found" branch. Intern a real module name via */
/* Str_Intern (the same table Module_FindByName's Rules_FindSymbolEntry    */
/* call looks up) and register a fake module record whose own symbol      */
/* pointer matches, with a non-NULL pretty-print form, to drive the        */
/* "found, has a PP form" branch (Module_GetPPForm + Output_WriteLongString).*/
/* ------------------------------------------------------------------ */
TEST(cov2_01_printppformbyname, found_with_ppform) {
  static _DWORD module_node[32];
  static const char ppform_text[] = "cov2-01 pretty-printed form";
  int saved = dword_51A9AC;
  void *atom;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(module_node, 0, sizeof module_node);

  atom = Str_Intern((char *)"Cov2_01Module", 0);
  module_node[0] = (_DWORD)(intptr_t)atom; /* module's own symbol ptr */
  module_node[1] = (_DWORD)(intptr_t)ppform_text; /* Module_GetPPForm result */
  module_node[7] = 0; /* next -> end of module list */

  dword_51A9AC = (int)(intptr_t)module_node;
  CHECK_EQ(Module_PrintPPFormByName((_BYTE *)"Cov2_01Module", (signed int)"cov2_01_out"), 1);

  dword_51A9AC = saved;
}

/* ------------------------------------------------------------------ */
/* Rules_PortCollectSupply / SaveSlot_LoadReservedSlot10 -- thin forwarders */
/* previously left unexercised or under-exercised; the new per-test       */
/* isolation makes calling them cold safe regardless of what the callee   */
/* does with default-zeroed global state. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_portcollectsupply, basic) {
  TOUCH(Rules_PortCollectSupply(0, 0, 0, 0.0));
}

TEST(cov2_01_savereservedslot10, basic) {
  TOUCH(SaveSlot_LoadReservedSlot10(0, 0.0));
}

/* ------------------------------------------------------------------ */
/* Rules_ReportSymbolTypeError -- the existing test_cov11.c test only      */
/* exercises the "symbol not found" branch (Rules_MakeSymbol returns 0).   */
/* Register the string builtins (which interns "str-compare" both as a    */
/* raw atom and, via Rules_RegisterHostFunction, into the symbol-value     */
/* table Rules_MakeSymbol's second lookup walks) so Rules_MakeSymbol can    */
/* actually succeed and drive the "found" branch. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_reportsymboltypeerror, found_symbol_branch) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterStringBuiltins());
  TOUCH(Rules_ReportSymbolTypeError((_BYTE *)aStrCompare, 2));
}

/* ------------------------------------------------------------------ */
/* Rules_HostSymbolp -- already exercised (both possible outcomes of the   */
/* decompiler-lost v3[1] check) by test_cov16.c's all_type_predicates      */
/* test via the shared "safe empty arg chain" helper. Vary the call site   */
/* with a real (non-empty) 1-node argument chain instead, for a different  */
/* set of leftover stack contents feeding that same undefined check. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_hostsymbolp, one_node_chain_variety) {
  static unsigned char root[64], node1[64];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);

  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(root + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = 0;

  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_HostSymbolp(0.0));
  dword_51A960 = saved;
}

/* ------------------------------------------------------------------ */
/* Defglobal_CloseConstructCodeFiles -- test_cov21.c already covers      */
/* (0,0,5,0), (0,0,5,1), (0,1,5,0) and (1,0,5,0). The remaining line is   */
/* the "goto LABEL_5;" taken from *inside* the `if (a2)` block (a1 and a2 */
/* both nonzero), distinct from directly entering LABEL_5 via `if (a1)`.  */
/* ------------------------------------------------------------------ */
TEST(cov2_01_closeconstructcodefiles, both_handles_nonzero_goto_path) {
  TOUCH(Defglobal_CloseConstructCodeFiles(1, 1, 5, 0));
}

/* ------------------------------------------------------------------ */
/* MapTile_HasBuilding -- test_cov01.c only drives the tile-out-of-range  */
/* short circuit (0xFFFF tile value) inside both helper predicates, never */
/* reaching MapTile_HasBuilding's own "return 1" lines. Populate a real    */
/* gameData buffer with an in-range building-slot tile and a matching/    */
/* mismatching owner byte to drive both. */
/* ------------------------------------------------------------------ */
static void cov2_01_setup_building_tile(char *gd, int a1, int a2, int slot,
                                         int owner) {
  int tile_addr = 556374 + 200 * a1 + 2 * a2;
  int rec_addr = 509674 + 467 * slot; /* UNIT_RECORD(slot) relative to gameData */
  *(unsigned short *)(gd + tile_addr) = (unsigned short)(0x8000 + slot);
  *(char *)(gd + rec_addr + 4) = 0;      /* < 4 */
  *(short *)(gd + rec_addr + 16) = 1;    /* != -1 */
  *(unsigned char *)(gd + rec_addr + 2) = (unsigned char)owner;
}

TEST(cov2_01_maptilehasbuilding, own_building_true) {
  static char gd[600000];
  int savedGd = gameData;
  int savedPlayer = g_CurrentPlayerIndex;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  g_CurrentPlayerIndex = 0;
  cov2_01_setup_building_tile(gd, 0, 0, 5, 0 /* owner == current player */);
  CHECK_EQ(MapTile_HasBuilding(0, 0), 1);
  gameData = savedGd;
  g_CurrentPlayerIndex = savedPlayer;
}

TEST(cov2_01_maptilehasbuilding, enemy_building_true) {
  static char gd[600000];
  int savedGd = gameData;
  int savedPlayer = g_CurrentPlayerIndex;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  g_CurrentPlayerIndex = 0;
  cov2_01_setup_building_tile(gd, 0, 0, 5, 1 /* owner != current player */);
  CHECK_EQ(MapTile_HasBuilding(0, 0), 1);
  gameData = savedGd;
  g_CurrentPlayerIndex = savedPlayer;
}

/* ------------------------------------------------------------------ */
/* Compat_FileFinderGetSize -- test_cov09.c's `finder` is a plain stack   */
/* array threaded through an `int` parameter; redo with static storage.  */
/* ------------------------------------------------------------------ */
TEST(cov2_01_filefindergetsize, static_buffer) {
  static _DWORD finder[16];
  memset(finder, 0, sizeof(finder));
  finder[20 / 4] = 4096;
  CHECK_EQ(Compat_FileFinderGetSize((int)(intptr_t)finder), 4096);
}

/* ------------------------------------------------------------------ */
/* Defglobal_RegisterResetGlobalsCommands -- test_cov21.c's call never    */
/* bootstraps the reserve arena, so the first Rules_RegisterHostFunction   */
/* call (which interns via Str_Intern into the NULL-by-default             */
/* dword_54DBA8/dword_54DD50 arenas) crashes immediately. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_registerresetglobals, bootstrapped) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Defglobal_RegisterResetGlobalsCommands());
}

/* ------------------------------------------------------------------ */
/* Unit_BuildShotAnimPaletteSpritePath -- already 45/46 covered by         */
/* test_cov02.c across a2=0 and a2=34. Sweep more unit-type indices for a  */
/* chance at whichever odd-length resource-key string trips the last      */
/* uncovered line. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_shotanimpalettepath, sweep_unit_types) {
  static char buf[256];
  int a2;
  for (a2 = 1; a2 < 40; ++a2) {
    memset(buf, 0, sizeof buf);
    TOUCH(Unit_BuildShotAnimPaletteSpritePath(buf, (unsigned __int8)a2));
  }
}

/* ------------------------------------------------------------------ */
/* Compat_StringHolderFindSubstringOffset -- the existing test_cov09.c    */
/* test deliberately avoids the "found both a2 and *a1 truthy" branch      */
/* because it calls through the weak, never-defined `strstr_` symbol,     */
/* which crashes under the old single-process harness. Under the new      */
/* per-test-fork isolation that crash is free real estate: it still       */
/* covers this line before dying. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_findsubstringoffset, real_call_expect_crash) {
  static _DWORD a1buf[4];
  memset(a1buf, 0, sizeof(a1buf));
  a1buf[0] = 1; /* *a1 truthy */
  TOUCH(Compat_StringHolderFindSubstringOffset(a1buf, 1, 0));
}

/* ------------------------------------------------------------------ */
/* Rules_HashBitmapValue -- test_cov11.c only ever uses a small divisor   */
/* (7), whose remainder can never have the sign bit set, so the           */
/* "return -v11" branch is unreachable there. Force a large accumulated    */
/* byte-sum (via 0xFE-valued input bytes packed 4 at a time into the      */
/* bulk-copy loop) together with a divisor just above that sum, so the    */
/* modulo is a direct, sign-bit-set pass-through. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_hashbitmapvalue, negative_remainder_branch) {
  static unsigned char data[8];
  memset(data, 0xFE, sizeof data);
  /* one 4-byte bulk block (a3=4): v13 packs to 0xFEFEFEFE, so v3 ends at
   * 0xFEFEFEFE; with a2 == 0xFFFFFFFF (> v3), v3 % a2 == v3 itself, whose
   * top bit is set. */
  TOUCH(Rules_HashBitmapValue((int)(intptr_t)data, 0xFFFFFFFFu, 4));
}

/* ------------------------------------------------------------------ */
/* Rules_DribbleOffCommand -- test_cov15.c's call uses a zeroed (count-0) */
/* arg chain, matching Lexer_TokenExpect(0)'s expected count and taking    */
/* the "success -> call Dribble_TurnOff()" branch; the "count mismatch ->  */
/* return 0" branch is never reached because there's no way to get a      */
/* mismatch against an *empty* expected count other than a *non-empty*     */
/* real chain. Build a real 1-node (count 1) chain to force the mismatch.  */
/* ------------------------------------------------------------------ */
TEST(cov2_01_dribbleoffcommand, mismatch_branch) {
  static unsigned char root[64], node1[64];
  int saved = dword_51A960;
  memset(root, 0, sizeof root);
  memset(node1, 0, sizeof node1);
  *(_DWORD *)(root + 6) = (_DWORD)(intptr_t)node1;
  *(_DWORD *)(node1 + 10) = 0;
  dword_51A960 = (int)(intptr_t)root;
  TOUCH(Rules_DribbleOffCommand());
  dword_51A960 = saved;
}

/* ------------------------------------------------------------------ */
/* Rules_WriteExpressionRefToCode -- vary a3 (used as both a modulus and  */
/* the Output_WriteFormatted logical-name arg) across both branches for   */
/* additional call-site variety. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_writeexpressionref, extra_variants) {
  __int16 buf[64];
  memset(buf, 0, sizeof(buf));
  TOUCH(Rules_WriteExpressionRefToCode(0, 0, -1, 0));
  TOUCH(Rules_WriteExpressionRefToCode(0, buf, 1, 5));
}

/* ------------------------------------------------------------------ */
/* Rules_RetractObjectPatternMatches -- test_cov19.c's bitmap-intersect    */
/* test always removes the *head* link (previous_link stays 0 the whole   */
/* time), so the "*(_DWORD*)previous_link = next_link" line (removing a    */
/* non-head node) is never reached. Build a 2-link list where the first    */
/* link doesn't match (kept, becomes previous_link) and the second does.  */
/* ------------------------------------------------------------------ */
TEST(cov2_01_retractobjpatternmatches, removes_non_head_link) {
  static _DWORD instance[32];
  static _DWORD pattern_keep[16], pattern_remove[16];
  static _DWORD dependency[16], partialMatch[16];
  static unsigned short depBitmap[8], bitmapArg[8];
  static _DWORD link1[16], link2[16];

  memset(instance, 0, sizeof instance);
  memset(pattern_keep, 0, sizeof pattern_keep);
  memset(pattern_remove, 0, sizeof pattern_remove);
  memset(dependency, 0, sizeof dependency);
  memset(partialMatch, 0, sizeof partialMatch);
  memset(depBitmap, 0, sizeof depBitmap);
  memset(bitmapArg, 0, sizeof bitmapArg);
  memset(link1, 0, sizeof link1);
  memset(link2, 0, sizeof link2);

  Mem_InitReserveBlock(0, 0);

  depBitmap[0] = 8;
  ((unsigned char *)depBitmap)[2] = 0xFF;
  bitmapArg[0] = 8;
  ((unsigned char *)bitmapArg)[2] = 0xFF;
  *(_DWORD *)((char *)dependency + 16) = (_DWORD)(intptr_t)depBitmap;
  *(_DWORD *)((char *)pattern_remove + 24) = (_DWORD)(intptr_t)dependency;
  /* pattern_keep's +24 stays 0 -> dependency_bitmap short-circuits to 0,
   * so link1 never intersects and is kept as previous_link. */

  *(_DWORD *)((char *)link1 + 0) = (_DWORD)(intptr_t)link2; /* next -> link2 */
  *(_DWORD *)((char *)link1 + 8) = (_DWORD)(intptr_t)pattern_keep;

  *(_DWORD *)((char *)link2 + 0) = 0;
  *(_DWORD *)((char *)link2 + 4) = (_DWORD)(intptr_t)partialMatch;
  *(_DWORD *)((char *)link2 + 8) = (_DWORD)(intptr_t)pattern_remove;

  *(_DWORD *)((char *)instance + 16) = (_DWORD)(intptr_t)link1;
  *(_DWORD *)((char *)instance + 40) = 1;
  *(_DWORD *)((char *)instance + 4) = 0;

  TOUCH(Rules_RetractObjectPatternMatches(instance, bitmapArg, 0.0));
  /* link1 (head) survives; link2 was unlinked via previous_link's own
   * next-field write rather than the instance+16 head-field write. */
  CHECK_EQ(*(_DWORD *)((char *)instance + 16), (_DWORD)(intptr_t)link1);
}

/* ------------------------------------------------------------------ */
/* Compiler_WriteObjectPatternsAndRulesToCode -- test_cov23.c only covers */
/* the empty-networks (result==0, immediate "return result") path. Give   */
/* it a populated object-pattern list so Compiler_WriteObjectPatternNodesToCode */
/* has a chance to return nonzero and drive into the second call plus the */
/* "if (result) return 1;" line. */
/* ------------------------------------------------------------------ */
TEST(cov2_01_writeobjpatandrules, populated_pattern_list) {
  static _DWORD patNode[16];
  int savedRoot = dword_51AEAC;
  int savedList = dword_51AEB0;
  memset(patNode, 0, sizeof(patNode));
  dword_51AEAC = (int)(intptr_t)patNode;
  dword_51AEB0 = 0;
  TOUCH(Compiler_WriteObjectPatternsAndRulesToCode("cov2_01test", 0, 0, 0, 0));
  dword_51AEAC = savedRoot;
  dword_51AEB0 = savedList;
}
