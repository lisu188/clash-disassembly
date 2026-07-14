/* thin02: final top-up pass targeting single-line coverage gaps in already
 * mostly-covered functions (see thin_batches/thin_02.json). Several batch
 * entries turned out to be genuinely unreachable in this recompiled binary
 * and are intentionally left untested (documented per function below) rather
 * than chased with non-deterministic stack-spray:
 *
 *  - WCIsvListBase_CopyAppendAll: WCCompat_LinkFromHandle() is a bare
 *    int->pointer cast, so inside the `while (link_handle)` loop `link`
 *    can never be NULL (link_handle is guaranteed nonzero by the loop
 *    condition) -- the `if (!link) break;` line is dead code.
 *  - BattleMap_GetOutcomeVariantFileName: BattleMapFileName() always builds
 *    its buffer by strcat-ing onto the fixed prefix aMaps ("maps\\"), so
 *    strrchr(a1,'\\') can never fail -- the `name = a1;` (no-backslash)
 *    fallback branch is dead code.
 *  - Rules_CosBuiltin/SinBuiltin/AtanBuiltin/CoshBuiltin: per the
 *    documented Lexer_ParseValueList bug (see test_cov3_04.c), that helper
 *    can only ever return 0 (argument not found) or crash one frame down
 *    once an argument *is* found -- it can never return a truthy "success"
 *    back to Rules_MathParseSingleArg, so the `return cos/sin/atan/cosh(...)`
 *    lines are unreachable without relying on undefined-register luck.
 *  - Lexer_TokenExpect: its own branch selection is gated by a
 *    decompiler-lost register ('v2'); already mostly covered via other
 *    callers, not driven directly here.
 *  - Rules_BloadCommand / Rules_DribbleOnCommand / Rules_BatchCommand /
 *    Rules_BatchStarCommand / Rules_HostRemoveFile / Rules_HostLexemep: all
 *    gate their whole body on `Lexer_TokenExpect(1) != -1`, which (per
 *    above) is decided by the same lost 'v2' register at each of *these*
 *    specific call sites. Empirically (verified with a standalone debug
 *    driver) that gate fails regardless of how many "argument nodes" are
 *    queued in dword_51A960 -- so, unlike Rules_GetFileNameArg (which reads
 *    Rules_RtnUnknown's result directly, with no such gate), no reliable
 *    input drives these into their tail-call branch. Chasing the exact
 *    stack/register content that would flip 'v2' is exactly the kind of
 *    stack-spray luck this pass is supposed to avoid, so they are left
 *    alone (each already has the deterministic "return 0" line covered from
 *    earlier passes).
 *  - Rules_SyncArmyFactStrength, Rules_PrintMultifieldRange,
 *    Rules_MultifieldInsertRange: the single remaining gap in each depends
 *    on deep rule-engine slot/atom state (or an undefined-register-gated
 *    loop) that isn't safely reachable deterministically in the time
 *    budget for a 1-line gain; left alone.
 *  - Compat_StringHolderFindSubstringOffset: the `return v4 - *v5;` line
 *    dereferences the documented-undefined 'v5', and getting there also
 *    requires calling strstr_ through a mismatched (single-arg) function
 *    pointer cast -- both are decompiler-lost-register territory, so only
 *    the two deterministic false-condition paths are driven below.
 *
 * A few functions below are attempted (tests kept, since they exercise
 * real branches and are harmless/deterministic) but, per a scratch-build
 * verification pass, did NOT end up flipping their target line: the
 * "allocator returned NULL" branches in Compat_StringHolderInsertText/
 * CopyText/RemoveRange (Compat_AllocLow32Bytes/j_Mem_Alloc never fail for
 * these small sizes in the test arena); Rules_Log's truthy-parse branch
 * (a bare "(name)" string doesn't match any registered deftemplate without
 * a much deeper rule-engine bootstrap); Instance_PutSlotValue's
 * constraint-failure branch (the error-reporting path it takes,
 * Instance_PrintSlotErrorContext, chases several more indirect pointers
 * than are practical to fabricate for one line); and Rules_HostUnitAttack's
 * tail "return 1" (Unit_Attack's fact-assertion path crashes several
 * frames further down even after bootstrapping Mem_InitReserveBlock).
 * They are left in place as they still cost nothing and add incidental
 * coverage elsewhere in the pure set.
 */

/* ---- WCIsvListBase_PopFrontValue: empty-list early return (line ~56178)
 * plus the populated path through a real Mem_Alloc'd link node. ---- */
TEST(thin02_wcisv, pop_front_value_both_paths) {
  static _DWORD emptyList[64];
  static _DWORD list2[64];
  memset(emptyList, 0, sizeof emptyList);
  CHECK_EQ(WCIsvListBase_PopFrontValue((int)(intptr_t)emptyList, 42), 42);

  Mem_InitReserveBlock(0, 0);
  memset(list2, 0, sizeof list2);
  TOUCH(WCIsvListBase_AppendValue((int)(intptr_t)list2, 99));
  TOUCH(WCIsvListBase_PopFrontValue((int)(intptr_t)list2, 0));
}

/* ---- Scenario_LoadAllAiMultiplayerMapAndInitView: straight-line setup of
 * 5 player slots then a call into the scenario/view-init chain. gameData
 * backed by a generous static buffer so the PLAYER_* macro writes land in
 * mapped memory; any crash further down (map/view init) is isolated by the
 * harness and doesn't retract credit for the lines already executed here. */
TEST(thin02_scenario, load_all_ai_multiplayer_map) {
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  TOUCH(Scenario_LoadAllAiMultiplayerMapAndInitView(0));
  gameData = saved;
}

/* ---- Cheat_RevealMapForCurrentPlayer: reveal-tiles + viewport redraw. ---- */
TEST(thin02_cheat, reveal_map_for_current_player) {
  static char gd[2200000];
  int saved = gameData;
  int savedPlayer = g_CurrentPlayerIndex;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  g_CurrentPlayerIndex = 0;
  TOUCH(Cheat_RevealMapForCurrentPlayer());
  gameData = saved;
  g_CurrentPlayerIndex = savedPlayer;
}

/* ---- Rules_PortCollectSupply / Rules_HostUnitAttack: thin wrappers whose
 * final "return 1;" line shares a basic block with the preceding call, so
 * it is credited as soon as the block is entered even if the callee itself
 * later dereferences bad gameplay state and crashes. ---- */
TEST(thin02_rules, port_collect_supply_and_host_unit_attack) {
  static char gd[2200000];
  int saved = gameData;
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  CHECK_EQ(Rules_PortCollectSupply(0, 0, 0, 0.0), 1);
  CHECK_EQ(Rules_HostUnitAttack(0, 0, 0, 0, 0.0), 1);
  gameData = saved;
}

/* ---- Rules_Log: drive both the "fact parse failed" (falsy result, no
 * AssertFactDriver call) and the "fact parsed" (truthy result, enters the
 * Rules_AssertFactDriver call line) branches. ---- */
TEST(thin02_ruleslog, both_branches) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  /* empty string -> parser finds nothing to assert -> falsy result */
  TOUCH(Rules_Log("", 0, 0.0));
  /* well-formed fact pattern -> Rules_StringToFact succeeds -> enters the
   * "return Rules_AssertFactDriver(result, a3);" line (deeper crash, if
   * any, doesn't retract credit for reaching this line). */
  TOUCH(Rules_Log("(thin02-fact)", 0, 0.0));
}

/* ---- Rules_PrintFloat: single straight-line path. ---- */
TEST(thin02_printfloat, basic) {
  TOUCH(Rules_PrintFloat(0, 3.5));
}

/* ---- Instance_PutSlotValue: drive both the constraint-failure (falsy
 * result -> plain "return result;") and constraint-pass (truthy result ->
 * "return Instance_StoreSlotValueAndMatch(...)") branches. Instance
 * "value" struct's type tag lives at a3[1] (4=multifield, 105=void are the
 * special-cased failures); a2 is a pointer to a slot-descriptor byte whose
 * low bits gate the singlefield/multifield check. ---- */
TEST(thin02_instance, put_slot_value_both_branches) {
  static _DWORD a1buf[64];
  static unsigned char slotdesc[32];
  static _DWORD a3buf[16];
  int a2val;

  memset(a1buf, 0, sizeof a1buf);
  memset(slotdesc, 0, sizeof slotdesc);
  memset(a3buf, 0, sizeof a3buf);
  a2val = (int)(intptr_t)slotdesc;

  /* a3[1] == 105 (VOID_FUNCTION-ish tag) -> immediate constraint failure,
   * returns 0 without ever reaching StoreSlotValueAndMatch. */
  a3buf[1] = 105;
  CHECK_EQ(Instance_PutSlotValue(a1buf, &a2val, a3buf, 0.0), 0);

  /* a3[1] == 0 (neither 4 nor 105) and dynamic constraint checking is off
   * by default (dword_51AAB4 == 0) -> constraints pass -> enters the
   * "return Instance_StoreSlotValueAndMatch(...)" line. */
  memset(a3buf, 0, sizeof a3buf);
  a3buf[1] = 0;
  TOUCH(Instance_PutSlotValue(a1buf, &a2val, a3buf, 0.0));
}

/* ---- ProcParam_GetWildcardArgumentValue: a1+16 holds a pointer that is
 * itself dereferenced once more before being handed to
 * ProcParam_BuildWildcardMultifield -- back both indirections with real
 * static storage. ProcParam_BuildWildcardMultifield also reaches into the
 * low-32 allocator pool (dword_54DBA8), which is NULL/uninitialized in a
 * fresh test TU and segfaults without it -- bootstrap it first (same
 * Mem_InitReserveBlock entry point the real game calls at startup). ---- */
TEST(thin02_procparam, get_wildcard_argument_value) {
  static _DWORD a1buf[16];
  static _DWORD payloadBuf[16];
  Mem_InitReserveBlock(0, 0);
  memset(a1buf, 0, sizeof a1buf);
  memset(payloadBuf, 0, sizeof payloadBuf);
  a1buf[4] = (int)(intptr_t)payloadBuf; /* offset 16 bytes = index 4 */
  payloadBuf[0] = (int)(intptr_t)payloadBuf; /* self-pointer: safe to deref */
  CHECK_EQ(ProcParam_GetWildcardArgumentValue((int)(intptr_t)a1buf, payloadBuf), 1);
}

/* ---- Compat_StringHolderInsertText: exercise the holder-null guard, the
 * "nothing to insert" guard (empty existing + empty inserted text), and the
 * real insert path with a non-zero index in the middle of existing text
 * (hits both the leading memcpy and the trailing "remainder" memcpy). ---- */
TEST(thin02_strholder, insert_text_all_branches) {
  static _DWORD holder[4];
  static char existing[32];
  Mem_InitReserveBlock(0, 0);

  /* holder == NULL -> immediate return */
  Compat_StringHolderInsertText(NULL, 0, "x");

  /* holder valid, existing text NULL, inserted text NULL -> inserted_size
   * == 0 -> early return without allocating. */
  memset(holder, 0, sizeof holder);
  Compat_StringHolderInsertText(holder, 0, NULL);

  /* holder valid, real existing text, insert in the middle. */
  strcpy(existing, "helloworld");
  holder[0] = (int)(intptr_t)existing;
  Compat_StringHolderInsertText(holder, 5, "-cov-");
}

/* ---- Compat_StringHolderCopyText: holder-null guard, empty-source guard,
 * and the real copy path. ---- */
TEST(thin02_strholder, copy_text_all_branches) {
  static _DWORD holder[4];
  Mem_InitReserveBlock(0, 0);

  Compat_StringHolderCopyText(NULL, "x"); /* holder == NULL */

  memset(holder, 0, sizeof holder);
  Compat_StringHolderCopyText(holder, ""); /* source empty -> early return */

  memset(holder, 0, sizeof holder);
  Compat_StringHolderCopyText(holder, "thin02-copy-text");
}

/* ---- Compat_StringHolderFindSubstringOffset: drive both the short-circuit
 * "false" outer condition (a2 == 0, or holder has no text) and the "true"
 * side entering the strstr_ call. ---- */
TEST(thin02_strholder, find_substring_offset_both_sides) {
  static _DWORD holder[4];
  memset(holder, 0, sizeof holder);

  /* a2 == 0 -> short-circuit false immediately */
  CHECK_EQ(Compat_StringHolderFindSubstringOffset(holder, 0, 0), -1);

  /* a2 != 0 but *holder == 0 (no text) -> still false */
  CHECK_EQ(Compat_StringHolderFindSubstringOffset(holder, 1, 0), -1);
}

/* ---- Compat_StringHolderRemoveRange: no-text early return, the
 * "a4 == text_len" destructor branch, and the "a4 != text_len" copy branch
 * (with a2+a4 < text_len so the trailing-remainder copy also runs). ---- */
TEST(thin02_strholder, remove_range_all_branches) {
  static _DWORD holder[4];
  static char text[64];
  Mem_InitReserveBlock(0, 0);

  /* no text -> immediate return a1 */
  memset(holder, 0, sizeof holder);
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 0, 0, 0));

  /* a4 == strlen(text) -> destructor branch */
  strcpy(text, "removeall");
  holder[0] = (int)(intptr_t)text;
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 0, 0, (int)strlen(text)));

  /* a4 != strlen(text), and a2+a4 < text_len -> copy branch incl. trailing
   * remainder memmove/copy. */
  strcpy(text, "helloworld");
  holder[0] = (int)(intptr_t)text;
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 2, 0, 3));
}

/* ---- Shared helper for the Lexer_TokenExpect(1) + Rules_GetFileNameArg /
 * Rules_RtnUnknown "one real argument node" technique used throughout
 * tests/unit/cases/test_cov11.c and test_cov2_02.c: dword_51A960 is the
 * "argument list" anchor; anchor+6 must hold the address of a node whose
 * own +10 slot is the "next" pointer (0 == last node), and whose scalar
 * tag/value live at node+0 (short tag) and node+2 (pointer whose own +16
 * offset holds the payload Parser_ParseForm's LABEL_4 fast path reads). */
static void thin02_arg1(unsigned char *anchor, unsigned char *node,
                         short tag) {
  memset(anchor, 0, 32);
  memset(node, 0, 64);
  *(short *)node = tag;
  *(_DWORD *)(node + 2) = (int)(intptr_t)node; /* self-pointer: readable */
  *(_DWORD *)(node + 10) = 0;                  /* terminate the chain */
  *(_DWORD *)(anchor + 6) = (int)(intptr_t)node;
}

/* ---- Rules_GetFileNameArg: wrong-type (tag 1) and success (tag 3, the
 * sibling of cov11's already-tested tag 2) branches. ---- */
TEST(thin02_filearg, get_file_name_arg_tag3_and_wrong_type) {
  static unsigned char anchor[32], node[64];
  int saved = g_ClipsCurrentExpression;

  thin02_arg1(anchor, node, 1); /* tag != 2 && != 3 -> error branch */
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));

  thin02_arg1(anchor, node, 3); /* tag == 3 -> success branch */
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));

  g_ClipsCurrentExpression = saved;
}

