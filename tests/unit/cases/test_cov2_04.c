/* cov2_04: second-pass coverage additions for a mixed batch of
 * partially-covered functions (see scratchpad/cov2_batches/cov2_04.json).
 * Every test that can be driven to a fully deterministic outcome uses
 * CHECK/CHECK_EQ; anything that funnels through a genuinely uninitialized
 * decompiler-lost register ("possibly undefined" in clash95.c) or a deep,
 * only-partially-reconstructible callee uses TOUCH only, since the actual
 * branch taken there cannot be predicted from static reading alone. Crashes
 * from those deep calls are expected and are isolated by the per-test fork
 * + alarm(8) watchdog described in the harness instructions -- coverage up
 * to the crash point is still banked. */

/* =======================================================================
 * Shared helpers for the Rules "argument chain" tricks (same family as the
 * cov10/cov16/cov17/cov20 precedents already in this tree).
 * ======================================================================= */

/* Empty-but-safe context: Rules_RtnArgCount's walk (dword_51A960+6) sees a
 * valid non-NULL zeroed node with a NULL "next" link (count 0), and
 * Rules_RtnUnknown's "not found" error path can safely chase
 * dword_51A960+2 -> funcrec[0] -> symnode without touching unmapped memory
 * (identical shape to cov16_setup_safe_argctx). */
static void cov2_04_setup_empty_ctx(unsigned char *argnode, _DWORD *funcrec,
                                     _DWORD *symnode) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
}

/* One-real-argument context: makes Rules_RtnArgCount's chain length exactly
 * 1 (Lexer_TokenExpect(1) match / Lexer_TokenExpect(0) mismatch), and makes
 * Rules_RtnUnknown's "fetch argument at position 1" walk find that SAME
 * node (the walk breaks at i>=1 before ever touching the node's own "next"
 * link) and hand it to Parser_ParseForm as an expression: offset+0 (int16)
 * is the value's type tag, offset+2 (a plain 32-bit slot) is a pointer to
 * the value's storage. `type_tag` should be one of Parser_ParseForm's
 * "simple constant" set (0,1,2,3,5,7,8) so the safe assignment path
 * (v5[1]=type; v5[2]=*(value slot)) is taken; `valbuf` backs the value slot
 * with real, zeroed, owned memory so the downstream
 * Rules_ClampEvaluationDepth bookkeeping (which treats it as a small
 * struct) never touches unmapped memory. Also wires the funcrec/symnode
 * safety net in case a not-found path is reached elsewhere. */
static void cov2_04_setup_arg1_ctx(unsigned char *argnode, _DWORD *funcrec,
                                    _DWORD *symnode, unsigned char *node,
                                    _DWORD *valbuf, short type_tag) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  memset(node, 0, 32);
  memset(valbuf, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  *(short *)(node + 0) = type_tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)valbuf;
  *(_DWORD *)(node + 10) = 0;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
}

/* =======================================================================
 * Lexer_ReadToken (0/32 covered): builds a fake IO-router record mirroring
 * IO_AddRouter's field layout (offset4=active flag, offset12=name-match
 * "query" function, offset24=peek/"read" function, offset28=skip function)
 * so Lexer_PeekChar's router-chain walk drives real character data through
 * the token-accumulation loop, entirely without touching the buffered-file
 * (dword_51A608) fast path. The router's read callback replays a fixed
 * string one character per invocation via a static index. IsTable[c+1] has
 * bit 0x08 set for 'a'-'z' (97-122) and for '['/']' (91/93), so those
 * characters keep the accumulation loop going; a space (32) is one of the
 * loop's explicit break characters, terminating the token cleanly. This is
 * all in the same executable (-fno-pie/-no-pie per CMakeLists.txt), so
 * these helper functions' addresses are low, 32-bit-safe addresses just
 * like clash95.c's own recovered functions. */
static int cov2_04_lex_query(int a1) {
  (void)a1;
  return 1;
}
static int cov2_04_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}
static const char *cov2_04_lex_seq;
static int cov2_04_lex_pos;
static int cov2_04_lex_read(int a1) {
  unsigned char c;
  (void)a1;
  c = (unsigned char)cov2_04_lex_seq[cov2_04_lex_pos];
  if (c)
    ++cov2_04_lex_pos;
  else
    c = ' ';
  return c;
}

TEST(cov2_04_lexreadtoken, plain_symbol_else_branch) {
  static _DWORD router[16];
  int saved604 = g_IO_RouterListHead;
  int outflag = 0;

  memset(router, 0, sizeof router);
  router[1] = 1;
  router[3] = (_DWORD)(intptr_t)cov2_04_lex_query;
  router[6] = (_DWORD)(intptr_t)cov2_04_lex_read;
  router[7] = (_DWORD)(intptr_t)cov2_04_lex_skip;
  g_IO_RouterListHead = (int)(intptr_t)router;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov2_04_lex_seq = "abc ";
  cov2_04_lex_pos = 0;
  TOUCH(Lexer_ReadToken(424242, 0, (_DWORD *)&outflag, 0));
  CHECK_EQ(outflag, 2);

  g_IO_RouterListHead = saved604;
}

TEST(cov2_04_lexreadtoken, bracket_if_branch) {
  static _DWORD router[16];
  int saved604 = g_IO_RouterListHead;
  int outflag = 0;

  memset(router, 0, sizeof router);
  router[1] = 1;
  router[3] = (_DWORD)(intptr_t)cov2_04_lex_query;
  router[6] = (_DWORD)(intptr_t)cov2_04_lex_read;
  router[7] = (_DWORD)(intptr_t)cov2_04_lex_skip;
  g_IO_RouterListHead = (int)(intptr_t)router;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov2_04_lex_seq = "[xy] ";
  cov2_04_lex_pos = 0;
  TOUCH(Lexer_ReadToken(424242, 0, (_DWORD *)&outflag, 0));
  CHECK_EQ(outflag, 8);

  g_IO_RouterListHead = saved604;
}

/* ---- Instance_RegisterModifyAndDuplicateFunctions: straight-line chain of
 * Rules_RegisterHostFunction/Rules_AddFunctionParser calls, same one-time
 * bring-up bootstrap used throughout the suite. ---- */
TEST(cov2_04_instance, register_modify_and_duplicate_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Instance_RegisterModifyAndDuplicateFunctions());
}

/* ---- CRT_GetOrCreateThreadDataPreserveLastError: intentionally NOT
 * exercised. It unconditionally emits calls to
 * _GetThreadData_/_ReallocThreadData_, which (per tests/unit/cases/
 * test_cov12.c's documented finding) have no definition anywhere in this
 * tree and break the link for the whole coverage binary once referenced. */

/* ---- UnitBattle_GetTargetCrowdingScale: switch over
 * UnitBattle_CountAdjacentEnemies(a1), which walks 8 fixed map-neighbor
 * offsets sourced from dword_514500/dword_514504 (each recovered as a
 * single-element weak array, so indices beyond 0 read whatever data
 * happens to sit next to them in .data -- not reconstructible). Backing
 * g_MapData (the map-data pointer) with a zeroed static buffer keeps
 * every dereference inside owned memory regardless of what those stray
 * "delta" values turn out to be, and varying a1's own faction byte and
 * neighboring-tile bounds sweeps whatever mix of case values the corrupted
 * deltas happen to land on. ---- */
TEST(cov2_04_unitbattle, get_target_crowding_scale_sweep) {
  /* Sized generously: dword_514500/dword_514504 are each recovered as a
   * single-element array, so indices 2..14 read whatever data happens to
   * sit next to them in .data (uncontrollable, but deterministic per
   * build) -- if that garbage happens to pass the "0 <= v4 < width" style
   * bounds checks below, v4/v5 could land anywhere in [0, width). Keep the
   * backing buffer comfortably larger than the worst case
   * (40*width + 2*width + 1534 + slack) so any such read still lands on
   * owned, zeroed memory instead of unrelated globals. */
  static _DWORD mapbuf[4096];
  unsigned char unit[8];
  int saved532048 = g_MapData;
  int i;

  memset(mapbuf, 0, sizeof mapbuf);
  mapbuf[200] = 200; /* offset 800: map height */
  mapbuf[201] = 200; /* offset 804: map width  */
  g_MapData = (int)(intptr_t)mapbuf;

  for (i = 0; i < 8; ++i) {
    memset(unit, 0, sizeof unit);
    *(short *)(unit + 4) = 50; /* tile x */
    *(short *)(unit + 6) = 50; /* tile y */
    unit[2] = (unsigned char)i; /* faction byte, varied per call */
    TOUCH(UnitBattle_GetTargetCrowdingScale((int)(intptr_t)unit));
  }

  g_MapData = saved532048;
}

/* ---- MessageHandler_UndefineForClassOrAll: sweep a1 (class record vs
 * NULL), a2 (pre-resolved symbol vs NULL, forcing the Str_Intern branch)
 * and a4 (zero vs nonzero, forcing the MessageHandler_TypeIndexFromKeyword
 * branch). a1==NULL drives the Class_GetNextRecord(0) enumeration loop,
 * empty by default (same precedent as test_cov11.c's
 * list_for_class_or_module_all_classes_empty). ---- */
TEST(cov2_04_msghandler, undefine_a2_null_a4_zero) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(MessageHandler_UndefineForClassOrAll(0, 0, (int)(intptr_t)"cov2_04_undef_a", 0));
}

TEST(cov2_04_msghandler, undefine_a2_null_a4_nonzero) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(MessageHandler_UndefineForClassOrAll(0, 0, (int)(intptr_t)"cov2_04_undef_b", 1));
}

TEST(cov2_04_msghandler, undefine_a1_present_a2_present) {
  static _DWORD cls[256];
  static _DWORD sym[8];
  memset(cls, 0, sizeof cls);
  memset(sym, 0, sizeof sym);
  TOUCH(MessageHandler_UndefineForClassOrAll(cls, (signed int *)sym, 0, 0));
}

TEST(cov2_04_msghandler, undefine_a1_present_a4_nonzero) {
  static _DWORD cls[256];
  static _DWORD sym[8];
  memset(cls, 0, sizeof cls);
  memset(sym, 0, sizeof sym);
  TOUCH(MessageHandler_UndefineForClassOrAll(cls, (signed int *)sym, 0, 1));
}

/* ---- Rules_LoadStarCommand: Lexer_TokenExpect(1) guard, then
 * Rules_GetFileNameArg(1,...) which itself calls Rules_RtnUnknown directly
 * (not through the buggy Lexer_ParseValueList v7-dereference path used
 * elsewhere), so its outcome IS fully controllable via the arg1 context
 * helper above. Type tag 2 (SYMBOL) satisfies GetFileNameArg's
 * "v6==3||v6==2" success check; the value slot's offset+16 word controls
 * whether the returned "filename" is 0 (clean early-return branch) or
 * nonzero (drives one call into the real Rules_Load with a bogus filename
 * pointer -- isolated in its own TEST since that is expected to fault). */
TEST(cov2_04_rulesload, token_mismatch_returns_error) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_empty_ctx(argnode, funcrec, symnode);
  TOUCH(Rules_LoadStarCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_04_rulesload, filename_arg_resolves_to_null) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 2);
  /* valbuf[4] (offset16) already zeroed by the helper -> "filename" == 0 */
  TOUCH(Rules_LoadStarCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_04_rulesload, filename_arg_resolves_nonzero_hits_load) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 2);
  valbuf[4] = 1; /* offset16 -> nonzero "filename" pointer (bogus) */
  TOUCH(Rules_LoadStarCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_RegisterFileIOCommands / Rules_RegisterIOHostFunctions:
 * straight-line chains of Rules_RegisterHostFunction calls; only need the
 * one-time reserve-arena/atom-table bootstrap. ---- */
TEST(cov2_04_rulesreg, register_file_io_commands) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterFileIOCommands());
}

TEST(cov2_04_rulesreg, register_io_host_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterIOHostFunctions());
}

/* ---- Building_ApplySiegeDamageToWallSections: a2>=200 drives the first
 * while loop (up to its v5<=2 cap of 2 iterations) consuming from a
 * populated wall-section byte array at a1+422..a1+428; leaving a
 * remaining-damage value (v3) after that loop reaches the second if-block,
 * which does one more Rng_RandRange-guided pass over the same array. ---- */
TEST(cov2_04_building, apply_siege_damage_drives_both_blocks) {
  static unsigned char wall[512];
  memset(wall, 0, sizeof wall);
  memset(wall + 422, 5, 7); /* 7 candidate wall-section byte values */
  TOUCH(Building_ApplySiegeDamageToWallSections((int)(intptr_t)wall, 250));
}

/* ---- Deffunction_Delete: reads decompiler-lost registers ('v0','v2')
 * unconditionally at entry, so the branch taken cannot be predicted
 * statically; call it a few times so whichever path the leftover register
 * state happens to take gets exercised (isolated in its own TEST in case
 * one of those paths dereferences the lost 'v2' and faults). ---- */
TEST(cov2_04_deffunction, delete_repeated) {
  TOUCH(Deffunction_Delete());
  TOUCH(Deffunction_Delete());
  TOUCH(Deffunction_Delete());
}

/* ---- MainMenu_RequestMultiplayerMenu / Castle_RequestManagementScreenExit:
 * both forward to UIWidget_PlayPressedReleaseAnimation[WithDelay], which
 * reads widget offset 49 (skip Audio_PlayButtonSound when zero) then keeps
 * UIWidget_RefreshActionButtonState on its safe "offset0 >= 640" early-
 * return branch, avoiding UI_InvokeWidgetTransitionCallback entirely. This
 * exact widget shape is the proven-safe pattern already used successfully
 * for the sibling MainMenu_RequestOptionsMenu in test_cov2_06.c. ---- */
TEST(cov2_04_mainmenu, request_multiplayer_menu) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  *(_DWORD *)(widget + 49) = 0;

  TOUCH(MainMenu_RequestMultiplayerMenu((uintptr_t)(intptr_t)widget));

  CHECK_EQ(g_MainMenuRequestedScreen, MAIN_MENU_REQUEST_MULTIPLAYER);
  CHECK_EQ(g_PlayGameMenuExitRequested, 1);
}

TEST(cov2_04_castle, request_management_screen_exit) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  *(_DWORD *)(widget + 49) = 0;

  TOUCH(Castle_RequestManagementScreenExit((uintptr_t)(intptr_t)widget, 0));

  CHECK_EQ(g_CastleScreenExitRequested, 1);
}

/* ---- Rules_ResetDataObjectValue: pure straight-line bit twiddling over a
 * caller-owned buffer plus a read of Rules_GetIncrementalReset() (a plain
 * global read); no branches at all. ---- */
TEST(cov2_04_rulesreset, reset_data_object_value) {
  static _DWORD obj[8];
  memset(obj, 0, sizeof obj);
  obj[3] = 0xFFFFFFFFu;
  TOUCH(Rules_ResetDataObjectValue((int)(intptr_t)obj));
}

/* ---- Rules_CheckFactExistp: Lexer_TokenExpect(1) mismatch (empty chain)
 * for the early-return branch, then a real one-argument success chain
 * (type INTEGER) so Rules_ResolveFactArgument's
 * "v9==1 && *(v10+16)>=0" branch is taken, calling the real
 * Rules_FindFactByIndex() -- which, per test_cov10.c's documented finding,
 * returns 0 with no facts asserted (the default state here), avoiding both
 * of Rules_ResolveFactArgument's decompiler-lost-register branches (only
 * reachable via its OTHER outcomes) and Rules_CheckFactStillAsserted's
 * dereferencing branch (only taken for a nonzero fact pointer). ---- */
TEST(cov2_04_rulescheckfact, token_mismatch_returns_error) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_empty_ctx(argnode, funcrec, symnode);
  TOUCH(Rules_CheckFactExistp(0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_04_rulescheckfact, resolves_argument_no_facts_asserted) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 1);
  CHECK_EQ(Rules_CheckFactExistp(0.0), 0);
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_IntegerFunction: Lexer_TokenExpect(1) success drives it into
 * Lexer_ParseValueList, whose very next line dereferences a genuinely
 * uninitialized decompiler-lost register ('v7' in clash95.c) regardless of
 * outcome -- an unavoidable fault one frame down for any successful parse
 * across this whole family of functions. Still banks this function's own
 * "result = Lexer_ParseValueList(...)" call line before that happens.
 * Isolated in its own TEST. ---- */
TEST(cov2_04_rulesint, integer_function_success_chain_hits_known_bug) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 1);
  TOUCH(Rules_IntegerFunction(1, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- MessageHandler_PreviewSendForSymbol: Rules_FindSymbolEntry only
 * returns nonzero for a name that has actually been interned into the
 * symbol table; do that first via Str_Intern (after the usual reserve-
 * arena/atom-table bootstrap) so the "if (result)" true branch is taken,
 * banking the "MessageHandler_BuildPreviewHandlerCore(...)" call line
 * before it (a separate decompiler-lost-register bug in that callee, 'v10'
 * used as a raw address) is expected to fault. Isolated in its own TEST. */
TEST(cov2_04_msghandler, preview_send_for_interned_symbol) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Str_Intern((char *)"cov2_04_preview_symbol", 0));
  TOUCH(MessageHandler_PreviewSendForSymbol(0, (_BYTE *)"cov2_04_preview_symbol"));
}

/* ---- AI_FindBestStrategicTargetNearTile: a5 (search radius) < 1 skips the
 * entire nested-loop body (which would otherwise call
 * AI_EvaluateStrategicTargetAtTile through caller-supplied BYREF state),
 * leaving the "best" accumulator at its initialized -1 sentinel and taking
 * the "if (v11 == -1) return -1;" branch -- fully deterministic, no lost
 * registers or external state involved. ---- */
TEST(cov2_04_ai, find_best_strategic_target_zero_radius) {
  CHECK_EQ(AI_FindBestStrategicTargetNearTile(0, 0, 0, 0, 0), -1);
}

/* ---- IO_StringRouterPrint: builds a fake string-router record (matching
 * the field shape IO_FindStringRouter's chain walk expects: offset0=name
 * compared via strcmp_, offset20=next) so a router is "found" without
 * crashing, then drives both of its remaining safe early-return branches
 * (offset16 flag != 1; offset12 capacity - 1 <= offset8 position) while
 * deliberately avoiding the only combination that would fall through into
 * the strncpy_ call -- that call's destination is the raw offset8 value
 * (not a base+offset computation, a decompiler flattening bug), so a small
 * placeholder int there is not a valid pointer. ---- */
TEST(cov2_04_iostrouter, print_inactive_router_returns_1) {
  static _DWORD router[8];
  int saved = g_StringRouterListHead;
  memset(router, 0, sizeof router);
  router[0] = (_DWORD)(intptr_t)"cov2_04_router_a";
  router[4] = 0; /* != 1 -> immediate "return 1;" */
  router[5] = 0;
  g_StringRouterListHead = (int)(intptr_t)router;
  CHECK_EQ(IO_StringRouterPrint((int)(intptr_t)"cov2_04_router_a", "x"), 1);
  g_StringRouterListHead = saved;
}

TEST(cov2_04_iostrouter, print_router_at_capacity_returns_flag) {
  static _DWORD router[8];
  int saved = g_StringRouterListHead;
  memset(router, 0, sizeof router);
  router[0] = (_DWORD)(intptr_t)"cov2_04_router_b";
  router[4] = 1;   /* active */
  router[3] = 1;   /* capacity */
  router[2] = 100; /* position >= capacity - 1: never dereferenced here */
  router[5] = 0;
  g_StringRouterListHead = (int)(intptr_t)router;
  CHECK_EQ(IO_StringRouterPrint((int)(intptr_t)"cov2_04_router_b", "x"), 1);
  g_StringRouterListHead = saved;
}

/* ---- Rules_HostFloatp: Lexer_TokenExpect(1) success calls
 * Rules_RtnUnknown directly into this function's OWN local out-param (no
 * Lexer_ParseValueList involved, so none of that family's lost-register
 * crash applies here), fully deterministic given the arg1 context helper.
 * type_tag 0 makes the out-param's type field 0 (falsy), taking the
 * "if (!v3[1]) return 1;" branch -- the function's last remaining line,
 * "return result;" (0), is already reachable via the plain mismatch path
 * (documented/covered pattern from test_cov16.c). ---- */
TEST(cov2_04_ruleshostfloat, token_success_falsy_type_returns_1) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 0);
  CHECK_EQ(Rules_HostFloatp(0.0), 1);
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_04_ruleshostfloat, token_mismatch_returns_result) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_empty_ctx(argnode, funcrec, symnode);
  TOUCH(Rules_HostFloatp(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Unit_BuildAttackAnimSpritePath: near-fully covered already (57/59);
 * the two remaining lines depend on the exact byte-length parity of the
 * fixed global path-fragment strings interleaved with UnitType_GetResourceKey's
 * per-type result, so sweep several unit types/team bytes best-effort. ---- */
TEST(cov2_04_unit, build_attack_anim_sprite_path_sweep) {
  static char path[256];
  unsigned char a2;
  for (a2 = 0; a2 < 8; ++a2) {
    memset(path, 0, sizeof path);
    TOUCH(Unit_BuildAttackAnimSpritePath(path, a2, (char)(a2 & 1)));
  }
}

/* ---- Rules_HostCollectPortSupply: thin wrapper delegating to the (much
 * larger, out-of-batch) Rules_PortCollectSupply/Port_CollectReinforcement-
 * Shipment; the call line itself is this function's entire body, so it is
 * banked the instant the call is issued regardless of what happens deeper
 * in that callee. ---- */
TEST(cov2_04_rulesport, host_collect_port_supply) {
  TOUCH(Rules_HostCollectPortSupply());
}

/* ---- Instance_GetSlotValueBySymbol: fully engineered success path. Builds
 * a fake class-record + slot-name-hash-bucket + slot-index-table +
 * slot-value-table chain so Instance_ResolveSlotIndex's
 * Class_FindSlotNameID lookup succeeds (bucket 0, pointer-identity match
 * against our own symbol buffer) and resolves to slot index 0, driving the
 * function all the way through its "found" return line. ---- */
TEST(cov2_04_instance, get_slot_value_by_symbol_found) {
  static _DWORD obj[32];       /* the instance ("a1") */
  static _DWORD cls[32];       /* class record */
  static _DWORD symbolBuf[8];  /* slot-name argument ("a2") */
  static _DWORD slotNode[8];   /* Class_FindSlotNameID hash-bucket entry */
  static _DWORD bucketTable[0xA8];
  static _DWORD slotIndexTable[8];
  static _DWORD slotValueTable[8];
  int saved51AD70 = g_Defclass_SlotNameHashTablePtr;

  memset(obj, 0, sizeof obj);
  memset(cls, 0, sizeof cls);
  memset(symbolBuf, 0, sizeof symbolBuf);
  memset(slotNode, 0, sizeof slotNode);
  memset(bucketTable, 0, sizeof bucketTable);
  memset(slotIndexTable, 0, sizeof slotIndexTable);
  memset(slotValueTable, 0, sizeof slotValueTable);

  symbolBuf[3] = 0; /* offset12 -> hash input 0 -> bucket 0 */

  slotNode[2] = 0; /* offset8: resolved slot id */
  slotNode[3] = (_DWORD)(intptr_t)symbolBuf; /* offset12: pointer-identity key */
  slotNode[5] = 0; /* offset20: next = NULL */
  bucketTable[0] = (_DWORD)(intptr_t)slotNode;
  g_Defclass_SlotNameHashTablePtr = (int)(intptr_t)bucketTable;

  cls[19] = 5; /* offset76: max slot id (>= 0) */
  cls[15] = (_DWORD)(intptr_t)slotIndexTable; /* offset60 */
  slotIndexTable[0] = 1; /* -1 below yields slot_index 0 */

  obj[11] = (_DWORD)(intptr_t)cls;             /* offset44: class record */
  obj[18] = (_DWORD)(intptr_t)slotValueTable;  /* offset72: slot value table */
  slotValueTable[0] = 12345;

  CHECK_EQ(Instance_GetSlotValueBySymbol((int)(intptr_t)obj, (int)(intptr_t)symbolBuf), 12345);

  g_Defclass_SlotNameHashTablePtr = saved51AD70;
}

TEST(cov2_04_instance, get_slot_value_by_symbol_not_found) {
  static _DWORD obj[32];
  static _DWORD cls[32];
  static _DWORD symbolBuf[8];
  int saved51AD70 = g_Defclass_SlotNameHashTablePtr;

  memset(obj, 0, sizeof obj);
  memset(cls, 0, sizeof cls);
  memset(symbolBuf, 0, sizeof symbolBuf);
  symbolBuf[3] = 0;
  g_Defclass_SlotNameHashTablePtr = 0; /* no hash table carved out -> Class_FindSlotNameID -1 */
  obj[11] = (_DWORD)(intptr_t)cls;

  CHECK_EQ(Instance_GetSlotValueBySymbol((int)(intptr_t)obj, (int)(intptr_t)symbolBuf), 0);

  g_Defclass_SlotNameHashTablePtr = saved51AD70;
}

/* ---- Rules_FetchJoinObjectSlotFieldSimple: best-effort. Backs
 * dword_51ACFC (normally NULL) with an owned static table so
 * Rules_ResolveJoinBindingRecord's fallback lookup lands on real memory
 * instead of a near-NULL offset, letting the call actually return instead
 * of faulting immediately; the function's own final
 * Rules_FetchObjectSlotFieldSimpleCore call reads a genuinely
 * uninitialized decompiler-lost pointer ('v3' in clash95.c) so a fault
 * there (if any) is expected and isolated in its own TEST. ---- */
TEST(cov2_04_rulesjoin, fetch_join_object_slot_field_simple) {
  static _DWORD a1buf[16];
  static unsigned char joinInfo[32];
  static _DWORD factListTable[64];
  static _DWORD factCell[8];
  int saved51ACFC = g_Clips_CurrentPartialMatch;
  int saved51AD00 = g_Rules_GlobalRHSBinds;

  memset(a1buf, 0, sizeof a1buf);
  memset(joinInfo, 0, sizeof joinInfo);
  memset(factListTable, 0, sizeof factListTable);
  memset(factCell, 0, sizeof factCell);

  g_Rules_GlobalRHSBinds = 0; /* keep Rules_ResolveJoinBindingRecord on its fallback branch */
  joinInfo[4] = 1;  /* offset4 byte -> (byte-1) == 0 -> offset 0 into the table */
  a1buf[4] = (_DWORD)(intptr_t)joinInfo; /* offset16 */
  factListTable[2] = (_DWORD)(intptr_t)factCell; /* offset8 relative to table base */
  g_Clips_CurrentPartialMatch = (int)(intptr_t)factListTable;

  TOUCH(Rules_FetchJoinObjectSlotFieldSimple((int)(intptr_t)a1buf, 0));

  g_Clips_CurrentPartialMatch = saved51ACFC;
  g_Rules_GlobalRHSBinds = saved51AD00;
}

/* ---- Unit_NewTurnRegen: sweeps the outer countdown-flag branch (both the
 * "reaches zero" and "still counting down" sub-cases) and the inner
 * per-byte regen loop's saturation-clamp branch, over a real owned
 * buffer. ---- */
TEST(cov2_04_unit, new_turn_regen_countdown_reaches_zero_and_clamps) {
  static unsigned char u[512];
  memset(u, 0, sizeof u);
  u[429] = 1; /* countdown -> 0 this call -> ++u[421] */
  memset(u + 422, 95, 7); /* regen values near the 100 cap -> clamp branch */
  TOUCH(Unit_NewTurnRegen(u));
}

TEST(cov2_04_unit, new_turn_regen_countdown_still_running_no_clamp) {
  static unsigned char u[512];
  memset(u, 0, sizeof u);
  u[429] = 5; /* countdown decrements but stays nonzero */
  memset(u + 422, 50, 7); /* well under the cap -> no clamp */
  TOUCH(Unit_NewTurnRegen(u));
}

TEST(cov2_04_unit, new_turn_regen_countdown_zero_and_regen_at_cap) {
  static unsigned char u[512];
  memset(u, 0, sizeof u);
  u[429] = 0; /* skip the whole outer countdown block */
  memset(u + 422, 100, 7); /* already at the cap -> inner "< 0x64" is false */
  TOUCH(Unit_NewTurnRegen(u));
}

/* ---- Building_CountSpecialPersonageGarrisonEntries: pure array scan, no
 * external state -- fully deterministic. 12 fixed-stride (31 bytes)
 * records span exactly a1..a1+372; two are tagged as special-personage
 * unit types. ---- */
TEST(cov2_04_building, count_special_personage_matches) {
  static unsigned char buf[512];
  int i;
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 12; ++i)
    *(short *)(buf + i * 31 + 18) = 0;
  *(short *)(buf + 5 * 31 + 18) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
  *(short *)(buf + 8 * 31 + 18) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
  CHECK_EQ(Building_CountSpecialPersonageGarrisonEntries((int)(intptr_t)buf), 2);
}

/* ---- Rules_ClearCommand: Lexer_TokenExpect(0) against a real one-node
 * chain (count 1, mismatching the expected 0) drives the OTHER return
 * branch from test_cov10.c's existing count-0 test (which matches and
 * calls the real Rules_Clear()). Which literal value comes back depends on
 * a decompiler-lost register inside Lexer_TokenExpect itself, so this is
 * TOUCH-only. ---- */
TEST(cov2_04_rulesclear, token_count_one_vs_expected_zero) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8], valbuf[8];
  int saved = g_ClipsCurrentExpression;
  cov2_04_setup_arg1_ctx(argnode, funcrec, symnode, node, valbuf, 1);
  TOUCH(Rules_ClearCommand());
  g_ClipsCurrentExpression = saved;
}

/* ---- CRT_RegisterFinalizer: already exercised (and documented as an
 * expected crash one line before its own final return) in
 * tests/unit/cases/test_cov12.c; call it once more with different lock
 * bytes purely as cheap best-effort insurance. ---- */
TEST(cov2_04_crt, register_finalizer_again) {
  _DWORD lockbuf[16];
  memset(lockbuf, 0xAA, sizeof lockbuf);
  TOUCH(CRT_RegisterFinalizer(0, (__lock *)lockbuf, 0));
}

/* ---- Instance_InitializeInstanceFunction: straight-line (no branches) --
 * toggles the object-pattern-match-delay flag, delegates to
 * Instance_ActiveInitializeInstanceFunction, then restores the flag. ---- */
TEST(cov2_04_instance, initialize_instance_function) {
  TOUCH(Instance_InitializeInstanceFunction(0, 0, 0.0));
}

/* ---- Rules_BsavePackSharedRecordHeader: already both-branch-covered by
 * test_cov20.c; one more bit-pattern sweep as cheap best-effort insurance
 * against any remaining arithmetic-only line. ---- */
TEST(cov2_04_rulesbsave, pack_shared_record_header_extra_bits) {
  _DWORD result[16], a2[16], sub[16];
  memset(result, 0, sizeof result);
  memset(a2, 0, sizeof a2);
  memset(sub, 0, sizeof sub);
  sub[1] = 0xFFFFFFFFu;
  a2[2] = (int)(intptr_t)sub;
  a2[3] = 0xFFFFFFFFu;
  TOUCH(Rules_BsavePackSharedRecordHeader((int)(intptr_t)result, (int)(intptr_t)a2));
}
