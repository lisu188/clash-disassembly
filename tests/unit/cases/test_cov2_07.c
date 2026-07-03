/* cov2_07 cluster (second pass): raise line coverage on already-partially-
 * covered functions - Rules_ rule-engine registration/parsing helpers,
 * multifield range delete, math trig-inverse host functions, agenda
 * depth-list placement, fact hashing/break-flag walkers, a couple of
 * MainMenu/PlayGameMenu button handlers, Castle_InvokePrisonerPanel, and
 * assorted single-branch helpers (see cov2_batches/cov2_07.json).
 *
 * Shared trick used throughout: this is a -no-pie 64-bit build of code that
 * models pointers as 32-bit int/_DWORD, so any buffer whose address gets
 * cast to int and handed to a recovered function must be `static` (low
 * .bss address) rather than a plain stack local, or the truncating cast
 * produces a wild pointer. Rule-engine/atom-table-touching calls are
 * preceded by the same Mem_InitReserveBlock(0,0)+Rules_InitAtomTables()
 * bring-up used throughout the existing cov/cov2 suite.
 *
 * Another shared trick (validated against tests/unit/cases/test_cov14.c and
 * test_cov16.c, which already use it successfully): the rule-engine's
 * "current argument list" lives at dword_51A960, a chain of 14-byte
 * expression nodes (offset0 = int16 type tag, offset2 = _DWORD value,
 * offset6 = _DWORD child, offset10 = _DWORD next), with the list head's
 * offset6 pointing at the first node. Rules_RtnArgCount/Rules_RtnUnknown/
 * Lexer_TokenExpect walk that chain, and Parser_ParseForm evaluates a node
 * of type 1 (INTEGER)/3 (STRING)/5 straight from its fields without needing
 * any deeper lexer state - letting us drive several Lexer_TokenExpect(N)-
 * gated host functions past their previously-only-tested "wrong arg count"
 * early-return branch into their real body. */

static void cov2_07_set_node(unsigned char *base, int tag, int val,
                              void *child, void *next) {
  *(short *)(base + 0) = (short)tag;
  *(int *)(base + 2) = val;
  *(int *)(base + 6) = (int)(intptr_t)child;
  *(int *)(base + 10) = (int)(intptr_t)next;
}

/* ---- Rules_MultifieldDeleteRange: the existing (first-pass) test only
 * drove the early "bad range" guard-error branch. Build an a2 multifield
 * whose [3]/[4] fields describe a valid 5-element source range, with a3/a4
 * chosen so the guard passes, driving the function into its main body
 * (Rules_CreateEphemeralMultifield allocation + copy loops), which needs
 * the reserve-block arena carved out first. */
TEST(cov2_07_multifield, delete_range_main_body) {
  static _DWORD a1obj[16];
  static _DWORD a2obj[16];
  memset(a1obj, 0, sizeof a1obj);
  memset(a2obj, 0, sizeof a2obj);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  a2obj[3] = 1; /* source range base index */
  a2obj[4] = 5; /* source range end index -> v6 (length) = 5 */
  TOUCH(Rules_MultifieldDeleteRange(a1obj, a2obj, 4, 2, 0));
}

/* ---- Rules_RegisterRuleCommands: straight-line chain of
 * Rules_RegisterHostFunction calls (same shape as the sibling
 * Rules_Register*Functions helpers already exercised in test_cov16/19). */
TEST(cov2_07_rules, register_rule_commands) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterRuleCommands());
}

/* ---- Scenario_LoadAllAiMultiplayerMapAndInitView: builds its player-state
 * table entirely on its own stack (never handed to us), so no truncation
 * concerns; back gameData with a large zeroed buffer since the callees it
 * drives into index through it. */
TEST(cov2_07_scenario, load_all_ai_multiplayer_map) {
  static unsigned char fakeGameData[2200000];
  int savedGD = gameData;
  memset(fakeGameData, 0, sizeof fakeGameData);
  gameData = (int)(intptr_t)fakeGameData;
  TOUCH(Scenario_LoadAllAiMultiplayerMapAndInitView(0));
  gameData = savedGD;
}

/* ---- Rules_BuildFactAddressList: module-enum + fact-list walk, all
 * through the rule-engine's own globals once the reserve/atom-table arenas
 * exist. */
TEST(cov2_07_rules, build_fact_address_list) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BuildFactAddressList());
}

/* ---- Rules_LoadCommand: the first-pass test only drove the "0 args"
 * mismatch branch. Build a real 1-node STRING argument (chain rooted at
 * dword_51A960) so Lexer_TokenExpect(1) matches and Rules_GetFileNameArg
 * resolves an actual (nonexistent) filename, driving into Rules_Load's
 * open-failure branch instead of the early return. */
TEST(cov2_07_rules, load_command_with_filename_arg) {
  static unsigned char strNode[32], exprNode[32], argHead[32];
  static const char filename[] = "COV2_07_NOFILE.CLP";
  int saved = dword_51A960;

  memset(strNode, 0, sizeof strNode);
  memset(exprNode, 0, sizeof exprNode);
  memset(argHead, 0, sizeof argHead);
  *(intptr_t *)(strNode + 16) = (intptr_t)filename;
  cov2_07_set_node(exprNode, 3 /* STRING */, (int)(intptr_t)strNode, 0, 0);
  cov2_07_set_node(argHead, 0, 0, exprNode, 0);
  dword_51A960 = (int)(intptr_t)argHead;

  TOUCH(Rules_LoadCommand(0, 0.0));

  dword_51A960 = saved;
}

/* ---- Deffacts_CommandDefinitions: straight-line registration chain, same
 * shape/setup as Rules_RegisterRuleCommands above. */
TEST(cov2_07_deffacts, command_definitions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Deffacts_CommandDefinitions());
}

/* CRT_HasActiveWindow is intentionally NOT exercised here: like
 * test_cov19.c documents for the same function, it calls
 * LoadLibraryA/GetProcAddress, which have no definition anywhere in this
 * project and are normally dead-stripped by -Wl,--gc-sections. Calling it
 * would pull in two undefined externs and break the whole coverage
 * binary's link. */

/* ---- Rules_MathCoth / Rules_MathAcsch / Rules_MathTanh: the first-pass
 * tests only drove Rules_MathParseSingleArg's "no argument" failure path
 * (via a zeroed/absent dword_51A960 chain). Feed a real 1-node INTEGER
 * argument (auto-coerced to float by Lexer_ParseValueList, which needs the
 * reserve/atom arenas for Rules_AddDoubleValue) to reach the post-parse
 * branches: an exact-zero value drives the singularity/domain-error
 * branches, a nonzero value drives the real trig computation. */
static void cov2_07_set_math_arg(unsigned char *argHead, unsigned char *exprNode,
                                  unsigned char *intValNode, int value) {
  memset(argHead, 0, 32);
  memset(exprNode, 0, 32);
  memset(intValNode, 0, 32);
  *(int *)(intValNode + 16) = value;
  cov2_07_set_node(exprNode, 1 /* INTEGER */, (int)(intptr_t)intValNode, 0, 0);
  cov2_07_set_node(argHead, 0, 0, exprNode, 0);
}

TEST(cov2_07_math, coth_zero_and_nonzero) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  int saved = dword_51A960;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 0);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0)); /* v6 == 0.0 -> singularity error */

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 3);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0)); /* v6 == 3.0 -> 1.0/tanh(v6) */

  dword_51A960 = saved;
}

TEST(cov2_07_math, acsch_zero_and_nonzero) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  int saved = dword_51A960;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 0);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Rules_MathAcsch(0, 0, 0, 0.0)); /* v5 == 0.0 -> domain error */

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 2);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Rules_MathAcsch(0, 0, 0, 0.0)); /* v5 == 2.0 -> asinh(1.0/v5) */

  dword_51A960 = saved;
}

TEST(cov2_07_math, tanh_success_path) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  int saved = dword_51A960;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 4);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Rules_MathTanh(0, 0, 0, 0.0)); /* parse succeeds -> return tanh(v5[0]) */

  dword_51A960 = saved;
}

/* ---- Rules_PlaceInDepthList: the first-pass test (test_cov10.c) already
 * covers "insert before head", "walk to end", "empty list", and an
 * equal-depth tie that *does* break. It never exercises an equal-depth tie
 * that does *not* break (v2==v5 but v3 < a1[3]), which falls through past
 * the inner break check into the ordinary "advance to next node" lines. */
TEST(cov2_07_agenda, place_in_depth_list_tie_no_break) {
  static _DWORD nodeA[8], nodeB[8], newnode[8];
  memset(nodeA, 0, sizeof nodeA);
  memset(nodeB, 0, sizeof nodeB);
  memset(newnode, 0, sizeof newnode);
  nodeA[2] = 10; nodeA[3] = 1; nodeA[7] = (_DWORD)(intptr_t)nodeB;
  nodeB[2] = 1;  nodeB[3] = 0; nodeB[7] = 0;

  newnode[2] = 10; newnode[3] = 0; /* tie on [2], but 0 < nodeA[3](1) */
  TOUCH(Rules_PlaceInDepthList(nodeA, (int)(intptr_t)newnode));
}

/* ---- sub_4A94D0_Impl: reuses the same fake-module-record setup validated
 * in test_cov18.c's Rules_InitConstructModuleRecord/sub_4A94D0_Impl test,
 * with our own distinctly-named statics to avoid cross-file aliasing. */
TEST(cov2_07_construct, module_record_impl) {
  static int fakeModRec[8];
  int savedList = dword_51A9BC;
  int savedCur = dword_51A9B0;
  static unsigned char constructData[64];
  static const char name[] = "cov2_07_modname";

  memset(fakeModRec, 0, sizeof(fakeModRec));
  memset(constructData, 0, sizeof(constructData));
  fakeModRec[0] = (int)(intptr_t)name; /* name pointer compared via strcmp_ */
  fakeModRec[1] = 0;                   /* index used as a2 for Module_GetItem */
  fakeModRec[7] = 0;                   /* offset 28 -> next == NULL */

  dword_51A9BC = (int)(intptr_t)fakeModRec;
  dword_51A9B0 = 0;

  TOUCH(sub_4A94D0_Impl((int)(intptr_t)name, (int)(intptr_t)constructData,
                        (int)(intptr_t)constructData));

  dword_51A9BC = savedList;
  dword_51A9B0 = savedCur;
}

/* ---- MainMenu_RequestLoadGameMenu / PlayGameMenu_HandleCloseButton: both
 * forward through UIWidget_PlayPressedReleaseAnimation -> Render_Begin,
 * whose DD_IsFlipping/DD_IsLost checks read byte a1+44 of their argument;
 * with a1 == 0 that's an unmapped low read, same cold-call precedent
 * already used successfully for the sibling MainMenu_RequestCampaignMenu
 * in test_cov2_03.c. */
TEST(cov2_07_menu, request_load_game_menu) {
  TOUCH(MainMenu_RequestLoadGameMenu(0));
}

TEST(cov2_07_menu, play_game_menu_handle_close_button) {
  TOUCH(PlayGameMenu_HandleCloseButton(0));
}

/* Rules_ValueSatisfiesRangeConstraint: test_cov19.c already documents (in
 * detail) why the comparison loop's remaining lines cannot be driven
 * safely on this 64-bit rebuild -- v4/v5 are read via overlapping 8-byte
 * pointer loads from a 4-byte-apart 32-bit struct layout, so no byte
 * pattern makes both simultaneously dereferenceable. Not re-attempted
 * here; nothing new to add beyond that existing analysis. */

/* ---- Defgeneric_SetMethodTraceFlag: drive the cheap "no methods yet"
 * branch through Method_FindByIndex (offset+32 == 0 -> immediate -1),
 * which the first-pass suite never called at all. */
TEST(cov2_07_defgeneric, set_method_trace_flag_no_methods) {
  static _DWORD genrec[16];
  memset(genrec, 0, sizeof genrec);
  TOUCH(Defgeneric_SetMethodTraceFlag(1, (int)(intptr_t)genrec, 0));
}

/* ---- Class_GetDefmessageHandlerListCommand / Defgeneric_GetDefmethodListCommand:
 * both start with an "if (!Rules_RtnArgCount()) return <cheap path>;" guard
 * that the first-pass tests only exercised with an empty/absent argument
 * chain. Feed a real 1-node argument chain (count == 1) to drive past the
 * guard into the deeper class-name/generic-name parsing calls. */
TEST(cov2_07_class, get_defmessage_handler_list_nonzero_argcount) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  int saved = dword_51A960;
  cov2_07_set_math_arg(argHead, exprNode, intValNode, 5);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Class_GetDefmessageHandlerListCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov2_07_defgeneric, get_defmethod_list_nonzero_argcount) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  int saved = dword_51A960;
  cov2_07_set_math_arg(argHead, exprNode, intValNode, 5);
  dword_51A960 = (int)(intptr_t)argHead;
  TOUCH(Defgeneric_GetDefmethodListCommand((_DWORD *)0, 0, 0.0));
  dword_51A960 = saved;
}

/* ---- Rules_DecrementFactRefCount: never called at all in the first pass
 * (covered 0/3). Trivial one-line decrement over a fake fact record. */
TEST(cov2_07_rules, decrement_fact_ref_count) {
  static _DWORD fact[8];
  memset(fact, 0, sizeof fact);
  fact[2] = 5; /* offset 8 == the ref-count field */
  CHECK_EQ(Rules_DecrementFactRefCount((int)(intptr_t)fact), (int)(intptr_t)fact);
  CHECK_EQ(fact[2], 4);
}

/* ---- Rules_PointerpFunction: the first-pass test (test_cov16.c) only
 * drove the "no argument" early-return branch. Feed a real 1-node argument
 * of type 5 so Lexer_TokenExpect(1) succeeds and Rules_RtnUnknown's "found"
 * branch runs, taking the v3[1]==5 -> "return 1" branch this function
 * never reached before. */
TEST(cov2_07_rules, pointerp_function_true_branch) {
  static unsigned char argHead[32], exprNode[32];
  int saved = dword_51A960;
  memset(argHead, 0, sizeof argHead);
  memset(exprNode, 0, sizeof exprNode);
  cov2_07_set_node(exprNode, 5, 0, 0, 0);
  cov2_07_set_node(argHead, 0, 0, exprNode, 0);
  dword_51A960 = (int)(intptr_t)argHead;
  CHECK_EQ(Rules_PointerpFunction(0.0), 1);
  dword_51A960 = saved;
}

/* ---- Rules_ParseStandardConstraintAttribute: the first-pass test
 * (test_cov23.c) only exercised the aType_0 name. The Range/Cardinality
 * check's first half compares against a hardcoded 0 (always false), so
 * only the aCardinality half is reachable; the AllowedValues check's first
 * member (aAllowedSymbols) is compared against the real attribute name
 * argument, so it is directly reachable. Both drive previously-uncalled
 * Rules_Parse*Attribute branches. */
TEST(cov2_07_parsestdattr, cardinality_branch) {
  char a1buf[256];
  _DWORD a3buf[64];
  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aCardinality,
                                                (_BYTE *)a3buf, 0, 0));
}

TEST(cov2_07_parsestdattr, allowed_symbols_branch) {
  char a1buf[256];
  _DWORD a3buf[64];
  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedSymbols,
                                                (_BYTE *)a3buf, 0, 0));
}

/* ---- Castle_InvokePrisonerPanel: never called at all in the first pass.
 * Forwards straight into Building_ShowPrisonerManagementPanel; per the
 * updated harness, any hang/crash inside is isolated and still credits
 * whatever it reaches first. */
TEST(cov2_07_castle, invoke_prisoner_panel) {
  static unsigned char buildingRec[512];
  memset(buildingRec, 0, sizeof buildingRec);
  TOUCH(Castle_InvokePrisonerPanel((int)(intptr_t)buildingRec, 0, 0));
}

/* ---- Rules_HostArmyHasNormalCombatUnits: feed a real 1-node INTEGER
 * argument (same chain trick as the math functions above) so Rules_RtnLong
 * actually resolves a unit-stack index instead of the caller never being
 * exercised at all; back gameData so the downstream UnitStack lookup reads
 * zeroed (not garbage) memory. */
TEST(cov2_07_rules, host_army_has_normal_combat_units) {
  static unsigned char argHead[32], exprNode[32], intValNode[32];
  static unsigned char fakeGameData[2200000];
  int savedCtx = dword_51A960;
  int savedGD = gameData;

  cov2_07_set_math_arg(argHead, exprNode, intValNode, 0);
  memset(fakeGameData, 0, sizeof fakeGameData);
  dword_51A960 = (int)(intptr_t)argHead;
  gameData = (int)(intptr_t)fakeGameData;

  TOUCH(Rules_HostArmyHasNormalCombatUnits(0, 0.0));

  dword_51A960 = savedCtx;
  gameData = savedGD;
}

/* ---- IO_StringRouterGetc: the first-pass test (test_cov14.c) always
 * registered a matching router first. Call with a name that was never
 * registered so IO_FindStringRouter returns NULL, driving the
 * Rules_ReportSystemError/IO_RunRouterExitCallbacks branch this function
 * never reached before. */
TEST(cov2_07_io, string_router_getc_not_found) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_StringRouterGetc((int)(intptr_t)"cov2_07_missing_router"));
}

/* ---- UI_BeginUnitInfo: the first-pass test (test_cov02.c) only tried
 * a3 == '0'/'9'. v23[0] = a3 + 49; with a3 == -49 that wraps to 0 as a
 * char, so the third copy-loop's source string is immediately empty and
 * breaks on its very first iteration without ever reading the attribute
 * byte -- the one line that test never reached. */
TEST(cov2_07_ui, begin_unit_info_a3_wraps_to_zero) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(UI_BeginUnitInfo(buf, 0, (char)-49));
}

/* ---- Diagnostics_TraceCastleHotspots: the first-pass test (test_cov04.c)
 * marked one pixel per hotspot id (248..255), so every count[index] was
 * nonzero and the "if (!count[index]) continue;" line in the reporting
 * loop was never taken. Mark only a few ids so the rest stay at count 0. */
TEST(cov2_07_diag, trace_castle_hotspots_partial) {
  static _DWORD surface[64];
  static unsigned char pixels[64];
  int i;

  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 1);

  memset(surface, 0, sizeof surface);
  memset(pixels, 0, sizeof pixels);
  surface[46] = (unsigned int)(uintptr_t)off_50EE24;
  surface[0] = 8 | (8 << 16); /* width=8 height=8 */
  surface[1] = (unsigned int)(uintptr_t)pixels;
  for (i = 0; i < 3; ++i)
    pixels[i * 8 + i] = (unsigned char)(248 + i); /* only ids 248..250 hit */
  TOUCH((Diagnostics_TraceCastleHotspots((int)(intptr_t)surface), 0));
}

/* BattleMap_GetOutcomeVariantFileName's one uncovered line is the
 * "name = a1;" fallback taken when strrchr finds no backslash in the
 * generated path. BattleMapFileName always strcpy's the "maps\\" prefix
 * first, so that fallback is unreachable through any (a2,a3) combination --
 * not re-attempted here. */

/* ---- Rules_ClearBreakFlag: the first-pass test (test_cov11.c) only hit
 * the "return v1" inside the inner NULL check. Use a single already-
 * flagged node whose next is NULL: the do-while body clears the flag and
 * advances to NULL, so the outer `while (a1)` ends normally, reaching the
 * function's final `return 1;` line for the first time. */
TEST(cov2_07_rules, clear_break_flag_final_return) {
  static _DWORD node[32];
  memset(node, 0, sizeof node);
  *((char *)node + 29) = 8;               /* break flag already set */
  *(_DWORD *)((char *)node + 48) = 0;     /* next == NULL */
  CHECK_EQ(Rules_ClearBreakFlag((int)(intptr_t)node), 1);
}

/* ---- Rules_HashFactEntry: the first-pass test (test_cov13.c) only hit
 * the "result >= 0" path. Give the fact a single integer-constant field
 * whose hashed contribution (29 * -50 == -1450) is large enough in
 * magnitude that (field_hash + relation_hash) % 1013 stays negative
 * regardless of the (small, non-negative) relation-name hash, driving the
 * "if (result < 0) return -result;" branch for the first time. */
TEST(cov2_07_rules, hash_fact_entry_negative_result) {
  static unsigned char factBuf[256];
  static unsigned char slotBuf[64];
  static unsigned char symBuf[64];
  static const char name[] = "A";
  memset(factBuf, 0, sizeof factBuf);
  memset(slotBuf, 0, sizeof slotBuf);
  memset(symBuf, 0, sizeof symBuf);

  *(intptr_t *)(symBuf + 16) = (intptr_t)name;
  *(intptr_t *)(slotBuf + 0) = (intptr_t)symBuf;
  *(intptr_t *)(factBuf + 16) = (intptr_t)slotBuf;

  *(_WORD *)(factBuf + 40 + 6) = 1;   /* field-list count == 1 */
  *(_WORD *)(factBuf + 40 + 14) = 5;  /* field type 5: direct int constant */
  *(int *)(factBuf + 40 + 16) = -50;  /* value -> 29 * -50 == -1450 */

  TOUCH(Rules_HashFactEntry((int)(intptr_t)factBuf));
}

/* ---- Instance_MessageModifyInstanceFunction / Defgeneric_ClearDefgenericsReady:
 * both already have a first-pass call; their one remaining uncovered line
 * sits behind decompiler-lost (register-reuse) intermediate values we
 * cannot directly control. Re-call with the rule engine actually
 * bootstrapped (the first-pass tests didn't), which is the only lever we
 * have to possibly change which way those reused registers land. */
TEST(cov2_07_instance, message_modify_instance_function) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Instance_MessageModifyInstanceFunction(2.0));
}

TEST(cov2_07_defgeneric, clear_defgenerics_ready) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Defgeneric_ClearDefgenericsReady());
}
