/* cov2_00: second-pass coverage top-up for a mixed cluster of Rules_*
 * registration/print helpers, Class_SlotExistPCommand, MapTile ownership
 * checks, CRT TLS teardown, and assorted small standalone helpers (see
 * cov2_batches/cov2_00.json). Every TEST below is prefixed cov2_00_ to avoid
 * symbol collisions with the first-pass cov00-23 files and other cov2_NN
 * batches. Each test runs in its own forked+alarm-watchdog child (see
 * tests/unit/test_all.c), so it is safe to call functions that crash, exit,
 * or spin -- coverage up to that point is kept regardless. */

/* ---- shared bootstrap helper: many Rules_Register.../Rules_Add... functions
 * allocate host-function/expression nodes from the dword_54DBA8 reserve-block
 * arena and intern symbols into the dword_54DD50 atom tables. Both are NULL
 * until carved out, exactly like the pattern cov13/cov17/cov19 use. */
static void cov2_00_bootstrap_engine(void) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
}

/* ---- shared safe "empty arg chain + readable RtnUnknown fallback" context,
 * same technique as cov16_setup_safe_argctx: backs dword_51A960 so
 * Rules_RtnArgCount's walk terminates at 0 and Rules_RtnUnknown's
 * not-found branch chases real, zeroed memory instead of a NULL pointer. */
static void cov2_00_setup_argctx(unsigned char *argnode, _DWORD *funcrec,
                                  _DWORD *symnode) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  dword_51A960 = (int)(intptr_t)argnode;
}

/* ---- Rules_RegisterMiscFunctions / Rules_RegisterFactCommands /
 * Module_RegisterDefmoduleCommands: previously called cold (no arena),
 * crashing on the very first Rules_RegisterHostFunction call and leaving
 * only 1-2 lines covered. Every Rules_RegisterHostFunction call here stores
 * its "restriction string" arg (a3) raw into the node without dereferencing
 * it, so an uninitialized/UB arg in that slot is harmless; only a *false*
 * a5 (arg-spec string) is ever strlen()'d, and every call in these three
 * functions passes either 0 or a real string constant for a5. With the
 * arena bootstrapped, the whole registration chain should run cleanly. */
TEST(cov2_00_rules, register_misc_functions) {
  cov2_00_bootstrap_engine();
  TOUCH(Rules_RegisterMiscFunctions());
}

TEST(cov2_00_rules, register_fact_commands) {
  cov2_00_bootstrap_engine();
  TOUCH(Rules_RegisterFactCommands());
}

TEST(cov2_00_module, register_defmodule_commands) {
  cov2_00_bootstrap_engine();
  TOUCH(Module_RegisterDefmoduleCommands());
}

/* ---- MainMenu_WriteButtonWidgetTemplateRecord: static helper, never called
 * from any first-pass test. Straight-line record writer, no branches -- one
 * call reaches every line. ---- */
TEST(cov2_00_mainmenu, write_button_widget_template_record) {
  static unsigned char record[64];
  memset(record, 0xAA, sizeof record);
  MainMenu_WriteButtonWidgetTemplateRecord(record, 10, 20, 3, 4, 0, "click.wav");
  CHECK_EQ(*(int *)(record + 0), 10);
  CHECK_EQ(record[8], 1);
}

/* ---- Object_ConstructInt256Array: __thiscall one-liner forwarding to
 * _wcpp_4_ctor_array__(this, 256); never called before. ---- */
TEST(cov2_00_object, construct_int256_array) {
  static unsigned char buf[2048];
  memset(buf, 0, sizeof buf);
  TOUCH(Object_ConstructInt256Array(buf));
}

/* ---- Building_NewAt: sets a couple of override globals, forwards to
 * Building_New, then clears the override flag. Never called before. ---- */
TEST(cov2_00_building, new_at) {
  TOUCH(Building_NewAt(1, 2, 0, 0, 0.0, "b", 0));
  CHECK_EQ(g_BuildingNewOverrideActive, 0);
}

/* ---- Cheat_RevealMapForCurrentPlayer: two straight-line calls, never
 * exercised before. ---- */
TEST(cov2_00_cheat, reveal_map_for_current_player) {
  TOUCH(Cheat_RevealMapForCurrentPlayer());
}

/* ---- CRT_DestroyTlsIndexAndThreadData: dwTlsIndex defaults to -1 (skip the
 * TlsFree branch); allocate a real slot via TlsAlloc() to also exercise the
 * "!= -1" branch (TlsGetValue on a fresh slot returns NULL, so
 * CRT_DetachThreadDataAndMaybeCloseHandle's own inner branch is skipped --
 * safe) and the TlsFree()/reset-to-(-1) lines. ---- */
TEST(cov2_00_crt, destroy_tls_index_default) {
  DWORD saved = dwTlsIndex;
  dwTlsIndex = (DWORD)-1;
  TOUCH(CRT_DestroyTlsIndexAndThreadData());
  dwTlsIndex = saved;
}

TEST(cov2_00_crt, destroy_tls_index_allocated) {
  DWORD saved = dwTlsIndex;
  dwTlsIndex = TlsAlloc();
  TOUCH(CRT_DestroyTlsIndexAndThreadData());
  dwTlsIndex = saved;
}

/* ---- MapTile_HasOwnOrVisibleEnemyUnitStack: redirect the `gameData` base
 * pointer (a plain weak int, 0 by default) at a large static buffer so both
 * inner helpers' deep dereferences (offsets ~147178/147180/147894 relative
 * to the tile value) land on real, controllable memory instead of a bogus
 * absolute address. Existing coverage already exercises the
 * both-false path; these two add the two "return 1" branches (own-unit-stack
 * true, and -- when own is false -- visible-enemy-stack true), which share
 * the exact same underlying byte offsets in both callees. */
TEST(cov2_00_maptile, has_own_unit_stack_true) {
  static unsigned char gamebuf[700000];
  int saved_gd = gameData;
  int saved_pi = g_CurrentPlayerIndex;
  intptr_t tileAddr;

  memset(gamebuf, 0, sizeof gamebuf);
  gameData = (int)(intptr_t)gamebuf;
  g_CurrentPlayerIndex = 5;

  tileAddr = (intptr_t)gamebuf + 556374; /* TILE_INDEX(0,0) */
  *(unsigned __int16 *)tileAddr = 1;                 /* tile value v3 = 1, <= 0x1F4 */
  *(__int16 *)(gamebuf + 725 * 1 + 147180) = 0;       /* <= 0x28 */
  *(unsigned char *)(gamebuf + 725 * 1 + 147178) = 5; /* == g_CurrentPlayerIndex */

  CHECK_EQ(MapTile_HasOwnOrVisibleEnemyUnitStack(0, 0), 1);

  gameData = saved_gd;
  g_CurrentPlayerIndex = saved_pi;
}

TEST(cov2_00_maptile, has_visible_enemy_unit_stack_true) {
  static unsigned char gamebuf[700000];
  int saved_gd = gameData;
  int saved_pi = g_CurrentPlayerIndex;
  intptr_t tileAddr;

  memset(gamebuf, 0, sizeof gamebuf);
  gameData = (int)(intptr_t)gamebuf;
  g_CurrentPlayerIndex = 5;

  tileAddr = (intptr_t)gamebuf + 556374; /* TILE_INDEX(0,0) */
  *(unsigned __int16 *)tileAddr = 1;                 /* tile value v3 = 1, <= 0x1F4 */
  *(__int16 *)(gamebuf + 725 * 1 + 147180) = 0;       /* <= 0x28 */
  *(unsigned char *)(gamebuf + 725 * 1 + 147178) = 9; /* != g_CurrentPlayerIndex(5) ->
                                                          own-unit-stack false */
  *(unsigned char *)(gamebuf + 725 * 1 + 147894) = 0; /* visible-enemy-stack true */

  CHECK_EQ(MapTile_HasOwnOrVisibleEnemyUnitStack(0, 0), 1);

  gameData = saved_gd;
  g_CurrentPlayerIndex = saved_pi;
}

/* ---- Compat_FileSystemQueryResultRelease: cov09 already drives every
 * branch (null query, null vtable, non-matching vtable, FileStream triple,
 * Query triple); nothing left to add safely, but a token call keeps this
 * batch's target list complete. ---- */
TEST(cov2_00_compat, filesystem_query_result_release_noop) {
  Compat_FileSystemQueryResultRelease(0);
}

/* ---- Compat_FileSystemOpenIfReady: a1==0 short-circuit already covered
 * elsewhere (cov09). Try a "shaped" file-system object whose vtable doesn't
 * match either recognized dtor pair, so Compat_FileSystemQueryOpen falls
 * through to File_OpenMountRootEntry -- which needs dword_54DD00 (the mount
 * root path) to resolve a real entry; left at its NULL default here it
 * returns 0 quickly, so this still can't reach the "ready" branch, but it
 * exercises the call chain beyond the a1==0 guard for whatever partial
 * coverage that unlocks. Isolation covers the rest. ---- */
TEST(cov2_00_compat, filesystem_open_if_ready_unmounted) {
  static unsigned char fakeFs[64];
  memset(fakeFs, 0, sizeof fakeFs);
  TOUCH(Compat_FileSystemOpenIfReady((int)(intptr_t)fakeFs, 0));
}

/* ---- Method_FindByIndex: already exhaustively covered by cov21 (zero
 * count / found-first / found-second / hits-limit); token call only. ---- */
TEST(cov2_00_method, find_by_index_noop) {
  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  a1[8] = 0;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1, 1), -1);
}

/* ---- UnitStack_CopyFromTemplate: a1/a2 direct copies are safe; the second
 * _wcpp_4_copy_array__(v7) call reads a genuine decompiler-uninitialized
 * local (v7), so it may fault right after the first three field copies and
 * the first _wcpp_4_copy_array__(a3) call -- still real extra coverage over
 * not calling it at all. ---- */
TEST(cov2_00_unitstack, copy_from_template) {
  static unsigned char a1buf[2048];
  static unsigned char a2buf[2048];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  *(_WORD *)(a2buf + 316) = 9;
  *(_BYTE *)(a2buf + 720) = 4;
  *(_DWORD *)(a2buf + 721) = 7;
  TOUCH(UnitStack_CopyFromTemplate((int)(intptr_t)a1buf, (int)(intptr_t)a2buf, 0));
}

/* ---- Rules_PrintMultifieldRange: existing cov13 tests only exercise a4<=a3
 * (loop runs once) with a5 0 and 1. Add the a4>a3 (loop skipped) shape for
 * both a5 values to round out the remaining branch. ---- */
TEST(cov2_00_rules, print_multifield_range_loop_skipped) {
  static unsigned char buf[512];
  static const char logical[] = "stdout";
  memset(buf, 0, sizeof buf);
  TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 5, 0));
  TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 5, 1));
}

/* ---- ObjectsCompiler_CloseConstructFileGroup: existing cov21 test drives a
 * single 16-iteration loop with a1 entries all 1 / a4==0. Add a second shape
 * with different a3/a4 and a1 entries at 0 to perturb the
 * Rules_ConstructCodeFileClose() calls differently. ---- */
TEST(cov2_00_objcompiler, close_construct_file_group_variant) {
  static int a1arr[16];
  static _DWORD a2arr[16];
  int i;
  memset(a1arr, 0, sizeof a1arr);
  memset(a2arr, 0, sizeof a2arr);
  for (i = 0; i < 16; ++i) a1arr[i] = 0;
  TOUCH(ObjectsCompiler_CloseConstructFileGroup(a1arr, a2arr, 1, 100));
}

/* ---- Rules_PrintFactLabel: sprintf_ + Output_Write, no branches; never
 * called before. Output_Write's own UB (v2) doesn't affect this function's
 * lines (the call is the function's last statement either way). ---- */
TEST(cov2_00_rules, print_fact_label) {
  static _DWORD a2buf[16];
  memset(a2buf, 0, sizeof a2buf);
  a2buf[6] = 123; /* offset 24 bytes -> *(DWORD*)(a2+24) */
  TOUCH(Rules_PrintFactLabel(0, (int)(intptr_t)a2buf));
}

/* ---- Rules_BatchCommand: cov15's existing test uses an empty arg chain
 * (count 0), landing on the Lexer_TokenExpect(1)==-1 early-return path.
 * Give it a single-node chain (count 1, matching a1==1) instead -- for
 * every UB branch shape observed so far (Lexer_TokenExpect's internal
 * decompiler-lost comparison), a matching result/a1 pair takes the success
 * path, letting this reach the Rules_GetFileNameArg() call and the
 * if(result)/return lines after it. */
TEST(cov2_00_rules, batch_command_matching_arg_count) {
  static _DWORD anchor[16];
  static _DWORD node[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  *(short *)node = 2;                  /* Rules_GetFileNameArg success tag */
  *(_DWORD *)((char *)node + 2) = (int)(intptr_t)node;
  *(_DWORD *)((char *)node + 10) = 0;   /* terminate the 1-node arg-count walk */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)node;
  dword_51A960 = (int)(intptr_t)anchor;
  TOUCH(Rules_BatchCommand(1, 0.0));
  dword_51A960 = saved;
}

/* ---- Lexer_TokenExpect: cov11 already drives both the match and mismatch
 * outcomes at its own call site; the remaining two branches are gated by a
 * genuinely undefined local ('v2') with no argument to seed it from. Call
 * from a fresh site (different surrounding locals) on the chance the
 * decompiler-lost value differs here, same technique used for
 * Rules_HostStringp/Rules_BatchCommand above. ---- */
TEST(cov2_00_lexer, token_expect_fresh_site) {
  static _DWORD fake_expr[16];
  int saved = dword_51A960;
  memset(fake_expr, 0, sizeof fake_expr);
  dword_51A960 = (int)(intptr_t)fake_expr;
  TOUCH(Lexer_TokenExpect(2));
  dword_51A960 = saved;
}

/* ---- Rules_HostStringp: same Lexer_TokenExpect(1) + Rules_RtnUnknown shape
 * as cov16's predicate battery, called from a fresh site. ---- */
TEST(cov2_00_rules, host_stringp) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  cov2_00_setup_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_HostStringp(0.0));
  dword_51A960 = saved;
}

/* ---- Deffunction_CloseCodeFiles: cov21 already drives all four a1/a2
 * zero/nonzero combinations against Rules_ConstructCodeFileClose. Add a
 * both-nonzero shape (a1 && a2 both set) to reach the a2-branch's call
 * *and* the LABEL_5 fallthrough in the same invocation. ---- */
TEST(cov2_00_deffunction, close_code_files_both_nonzero) {
  TOUCH(Deffunction_CloseCodeFiles(1, 1, 5, 0));
}

/* ---- Object_ConstructInt256Array / Rules_WriteConstructHeaderToCode: the
 * latter's `Compiler_WriteSymbolReference(a1, *v9, v10)` dereferences a
 * genuinely uninitialized decompiler local ('v9') unconditionally right
 * after the first Output_WriteFormatted call, so every invocation faults at
 * the same early point regardless of arguments; cov18 already exercises
 * both a2+16 shapes for whatever it's worth. One more call from a fresh
 * call site in case the stack garbage differs here. ---- */
TEST(cov2_00_rules, write_construct_header_to_code) {
  static unsigned char a2buf[256];
  memset(a2buf, 0, sizeof a2buf);
  *(int *)(a2buf + 16) = 7;
  TOUCH(Rules_WriteConstructHeaderToCode(0, (int)(intptr_t)a2buf, 3, 1, 2, 'x'));
}

/* ---- Rules_ApplyPatternKeywordFlags: takes no args and switches on a
 * genuinely undefined local; it also calls Rules_CreateLHSParseNode(), which
 * itself dereferences another undefined local, so it's essentially
 * guaranteed to crash a couple of lines in regardless of engine bootstrap.
 * Bootstrap the arena anyway (so the *first* uninitialized-arena crash
 * inside Rules_CreateLHSParseNode's node allocation is avoided, possibly
 * reaching one line further before the unavoidable one) and call it from a
 * fresh site. ---- */
TEST(cov2_00_rules, apply_pattern_keyword_flags) {
  cov2_00_bootstrap_engine();
  TOUCH(Rules_ApplyPatternKeywordFlags());
}

/* ---- Rules_TestConstraintAttributeParsedFlag: the whole chain past the
 * first (a1 vs "type") check is gated by undefined locals (v3, v5, v6, ...)
 * fed straight into strcmp_; cov23 already tries every named constant. Add
 * one more call from a fresh site (different preceding locals) on the
 * chance the garbage differs here; no way to target a specific comparison
 * deliberately. ---- */
TEST(cov2_00_rules, test_constraint_attribute_parsed_flag_fresh_site) {
  static _DWORD bits[4];
  char pad[37]; /* perturb whatever stack slot different call sites reuse */
  memset(bits, 0, sizeof bits);
  memset(pad, 0, sizeof pad);
  bits[0] = 1;
  TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)"unmatched-name-2", bits));
}

/* ---- Class_SlotExistPCommand: Class_CheckSlotExists -> Class_ParseClass-
 * Reference -> Lexer_ParseValueList(1,...) -> Rules_RtnUnknown(1,...) first.
 * cov22's basic test leaves dword_51A960 backed only for Rules_RtnArgCount
 * (offset +6), not for Rules_RtnUnknown's not-found fallback chase (offset
 * +2), so that chase dereferences a NULL pointer and the whole chain
 * segfaults before Class_ParseClassReference can even fail cleanly. Using
 * the full cov2_00_setup_argctx (empty chain + readable +2 fallback, same
 * as Rules_HostStringp above) lets Rules_RtnUnknown's not-found branch run
 * safely, so Lexer_ParseValueList returns 0 (dword_51A964 gets set),
 * Class_ParseClassReference returns 0, and Class_CheckSlotExists returns 0
 * without ever crashing -- reaching several lines in
 * Class_SlotExistPCommand that were previously unreachable. ---- */
TEST(cov2_00_class, slot_exist_pcommand_safe_parse_failure) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static int a1val;
  int saved = dword_51A960;

  cov2_00_bootstrap_engine();
  cov2_00_setup_argctx(argnode, funcrec, symnode);
  a1val = 1;

  TOUCH(Class_SlotExistPCommand(&a1val, 1.0));

  dword_51A960 = saved;
}

/* ---- CastleProduction_ReloadLicenceSlotSprites: the `for` loop's
 * "increment" clause is the *only* place `i` is touched after its initial
 * 0, so this recovered loop never actually increments -- it's either an
 * infinite loop (until the alarm(8) watchdog fires) or the first inner call
 * faults (as cov04 arranges by leaving dword_532218 at 0). Either way the
 * final `return CastleProduction_DrawLicenceGrid();` line is unreachable
 * through this entry point; token call only for completeness. ---- */
TEST(cov2_00_castleprod, reload_licence_slot_sprites_noop) {
  TOUCH(CastleProduction_ReloadLicenceSlotSprites(1));
}

/* ---- Compat_StringHolderCopyText: cov09 already drives every branch
 * (NULL holder, NULL/empty source, real source of various lengths);
 * token call only. ---- */
TEST(cov2_00_compat, string_holder_copy_text_noop) {
  static _DWORD holder[4];
  memset(holder, 0, sizeof holder);
  Compat_StringHolderCopyText(holder, "cov2");
}

/* ---- Rules_GetFileNameArg: cov11 already drives both the success (tag==2)
 * and wrong-type outcomes via Rules_RtnUnknown's "found" branch. Add the
 * "not found" shape (empty arg chain, Rules_RtnUnknown's fallback path) from
 * a fresh call site. ---- */
TEST(cov2_00_rules, get_file_name_arg_not_found) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = dword_51A960;
  cov2_00_setup_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));
  dword_51A960 = saved;
}

/* ---- ProcParam_GetWildcardArgumentValue: simple pointer-chasing wrapper
 * around ProcParam_BuildWildcardMultifield; never called before. ---- */
TEST(cov2_00_procparam, get_wildcard_argument_value) {
  static _DWORD a1buf[16];
  static _DWORD a2buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  a1buf[4] = 0; /* offset 16 -> payload pointer; 0 is a safe, readable "value" */
  TOUCH(ProcParam_GetWildcardArgumentValue((int)(intptr_t)a1buf, a2buf));
}

/* ---- Rules_MathExp: cov17's battery already exercises the
 * Rules_MathParseSingleArg failure path (empty arg chain, count mismatch).
 * Add the same "matching count" trick used for Rules_BatchCommand above,
 * hoping to unlock the success path (exp(v5[0]) return line) here too. ---- */
TEST(cov2_00_rules, math_exp_matching_arg_count) {
  static _DWORD anchor[16];
  static _DWORD node[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)node; /* 1-node chain, count 1 */
  *(_DWORD *)((char *)node + 10) = 0;
  dword_51A960 = (int)(intptr_t)anchor;
  TOUCH(Rules_MathExp(0, 0, 0, 0.0));
  dword_51A960 = saved;
}

/* ---- Class_IsDeletableAlt: dword_51A1AC (Rules_IsBloaded's backing flag) is
 * a real, directly writable global. cov19 already calls this cold (bloaded
 * flag left at its default 0, so it falls into the undefined-'v0' branch);
 * add the bloaded==true shape here, which deterministically short-circuits
 * before ever touching 'v0'. ---- */
TEST(cov2_00_class, is_deletable_alt_bloaded) {
  int saved = dword_51A1AC;
  dword_51A1AC = 1;
  CHECK_EQ(Class_IsDeletableAlt(), 0);
  dword_51A1AC = saved;
}

/* ---- Rules_FindExistingJoinTestNode: cov23 already covers the null head,
 * one fallback-chain hop (a4==0), and one AND-chain hop (a4!=0) with a
 * mismatching a2 (short-circuiting before ever calling
 * Rules_JoinTestNodeMatches). Add a longer chain that walks *both* the
 * AND-chain (v10[8]) and OR-chain (v10[7]) links down to a null terminator,
 * still keeping a2 permanently mismatched so the (unverified, potentially
 * unsafe) Rules_JoinTestNodeMatches call is never reached. ---- */
TEST(cov2_00_rules, find_existing_join_test_node_multi_hop) {
  static _DWORD n1[16], n2[16], n3[16];
  memset(n1, 0, sizeof n1);
  memset(n2, 0, sizeof n2);
  memset(n3, 0, sizeof n3);
  n1[4] = 111;              /* mismatch vs a2 below */
  n1[8] = (int)(intptr_t)n2; /* AND-chain hop (a4 != 0) */
  n2[4] = 111;
  n2[8] = 0;                 /* end AND-chain -> outer do-while falls to n1[7] */
  n1[7] = (int)(intptr_t)n3; /* OR-chain hop */
  n3[4] = 111;
  n3[7] = 0;                 /* end OR-chain -> return 0 */
  n3[8] = 0;
  TOUCH(Rules_FindExistingJoinTestNode(n1, 999, 0, 1, 0, 0, 0, 0, 0, 0));
}

/* ---- Unit_BuildSelectedUnitPanelIconPalettePath: cov02 already exercises
 * both parity shapes of the UnitType_GetResourceKey-driven loop (unit_type 0
 * and 34); the single remaining uncovered line is an internal "c" literal
 * copy loop whose length (1, hard-coded via strcpy(v23,"c")) is fixed
 * regardless of any argument, so its break-vs-loop-exit alternate branch is
 * genuinely unreachable through this entry point. Token call only. ---- */
TEST(cov2_00_unit, build_selected_unit_panel_icon_palette_path_noop) {
  static char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildSelectedUnitPanelIconPalettePath(buf, 5, 0));
}
