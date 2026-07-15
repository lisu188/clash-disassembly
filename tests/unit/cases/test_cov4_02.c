/* cov4 batch 02: precise-line coverage for a grab-bag of mostly-covered
 * functions (see scratchpad/cov4_batches/cov4_02.json). Each section below
 * targets the EXACT uncovered clash95.c line numbers listed for that
 * function. Buffers whose address is threaded through a narrowed 32-bit
 * int/_DWORD field are declared `static` (64-bit -no-pie build; a stack
 * address truncates to garbage when squeezed through such a field). Every
 * TEST runs in its own forked child under the harness's fork()+alarm(8), so
 * a crash/hang inside a callee is safe and simply caps how much of the
 * target function's own body got reached before it happened. */

/* =========================================================================
 * Rules_PrintMultifieldRange (109333-109367, uncovered 109352-109355,109357):
 * the do/while loop body over an inline array of {int16 tag; int valueptr}
 * multifield-element slots at (a2+14). a4<=a3 (0<=0) enters the loop once;
 * one INTEGER-tagged (tag=1) self-referential slot lets Rules_PrintAtomValue
 * take its safe "case 1: Rules_PrintLongInteger(v3, a3[4])" branch (a3[4] is
 * read as a plain int, never dereferenced further, so any int is safe). That
 * covers the loop-body assignment/increment lines and both the `if`/`while`
 * re-tests of the (decompiler-lost) v8 counter unconditionally. ====== */
TEST(cov4_02_printmfrange, one_element_loop_body) {
  static unsigned char a2buf[64];
  memset(a2buf, 0, sizeof a2buf);
  *(short *)(a2buf + 14) = 1;                    /* element 0: tag INTEGER */
  *(int *)(a2buf + 16) = (int)(intptr_t)a2buf;    /* element 0: self-pointer value */
  *(int *)(a2buf + 32) = 42;                      /* that struct's own +16 (offset 32) payload */
  TOUCH(Rules_PrintMultifieldRange(0, (int)(intptr_t)a2buf, 0, 0, 0));
}

/* =========================================================================
 * UnitSlot_CycleOrderState (26784-26808, uncovered 26797,26798,26800,26801):
 * pure bit-twiddling on byte (result+12), no decompiler-lost variables at
 * all. Brute-forced in python: starting byte 8 (order-state bits == 2) drives
 * v1=3, taking the outer "> 2u" branch AND the inner "(v2&3u)<3" branch, so a
 * single call reaches all four target lines. ============================= */
TEST(cov4_02_unitslot, cycle_order_state_wraps_both_branches) {
  static unsigned char slot[16];
  memset(slot, 0, sizeof slot);
  slot[12] = 8;
  TOUCH(UnitSlot_CycleOrderState((int)(intptr_t)slot));
}

/* =========================================================================
 * Rules_LogTreasureFact (70847-70855) / Rules_RetractTreasureFact
 * (70859-70870): the batch's line numbers for "Rules_LogTreasureFact"
 * actually span into the very next function (Rules_RetractTreasureFact) --
 * 70860 is that function's own signature line and 70868/70869 are its body.
 * Both are trivial sprintf_+Rules_Log wrappers; test_cov10.c already
 * establishes that Rules_Log(...) is safe to call directly even with no
 * deftemplate registered (Rules_StringToFact just fails and returns 0
 * through the "result==0" early-return, no crash). ======================= */
TEST(cov4_02_treasure, log_and_retract_treasure_fact) {
  TOUCH(Rules_LogTreasureFact(1, 2));
  TOUCH(Rules_RetractTreasureFact(1, 2));
}

/* =========================================================================
 * Rules_CreateJoinPartialMatch (110753-110789, uncovered 110772,110779,
 * 110781): test_cov13.c already covers the "no action, no join" branch
 * (a3[9]==0 && a3[5]==0) with zeroed a1/a2 headers so Rules_MergeMultifield-
 * Values takes its no-copy fast path. Reusing that exact safe a1/a2 setup,
 * setting a3[5] ("join") to a small fake join-node record drives the two
 * remaining branches. Rules_DriveJoinNetwork's very first check
 * (`if (dword_51B354 && (*a2 & 0x10) == 0) return result;`) is an
 * unconditional early, crash-free return when the join node's first byte
 * has bit 0x10 clear -- setting the global watch flag makes both the
 * "direct join match" call (join+16 == a3) and the "walk the join list"
 * do/while loop (join+16 != a3, then join+28 == 0 ends the loop after one
 * iteration) resolve through that same safe early return, regardless of a3
 * (the requested join type). ============================================= */
TEST(cov4_02_joinpm, direct_join_match_branch) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], joinbuf[16];
  int saved = g_IncrementalResetInProgress;
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(joinbuf, 0, sizeof joinbuf);
  Mem_InitReserveBlock(0, 0);
  g_IncrementalResetInProgress = 1; /* Rules_DriveJoinNetwork's bit-0x10 guard now short-circuits safely */
  a3buf[9] = 0;      /* no action */
  a3buf[5] = (_DWORD)(intptr_t)joinbuf; /* join */
  joinbuf[4] = (_DWORD)(intptr_t)a3buf; /* join+16 == a3 -> direct-match branch (line 110772) */
  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
  g_IncrementalResetInProgress = saved;
}

TEST(cov4_02_joinpm, join_network_loop_then_exit) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], joinbuf[16];
  int saved = g_IncrementalResetInProgress;
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(joinbuf, 0, sizeof joinbuf);
  Mem_InitReserveBlock(0, 0);
  g_IncrementalResetInProgress = 1;
  a3buf[9] = 0;
  a3buf[5] = (_DWORD)(intptr_t)joinbuf;
  joinbuf[4] = 0; /* join+16 != a3 -> do/while loop branch (line 110779) */
  joinbuf[7] = 0; /* join+28 == 0 -> "while (join);" (line 110781) exits after one pass */
  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
  g_IncrementalResetInProgress = saved;
}

/* =========================================================================
 * Rules_MultifieldInsertRange (128414-128552, uncovered 128458,128536):
 * test_cov16.c already drives the a2==NULL scalar-insert path but with a4==1
 * (v9==1, so "v9 < a4" is false); bumping a4 to 5 with the same otherwise
 *-safe scalar (a3[1] != 4) setup trips that assignment. Line 128536 is
 * reached only via the a2==NULL && a3[1]==4 combination, which test_cov16.c
 * itself documents as routing into Rules_AssignMultifieldRangeCopy's own
 * decompiler-lost-pointer bug (dereferences an unassigned local) and
 * "expected to CRASH" before ever reaching the RegisterEphemeralMultifield
 * call -- so that line is left uncovered here too (same known ceiling). */
TEST(cov4_02_mfinsert, v9_less_than_a4_reassigns) {
  static _DWORD a1buf[8], a3buf[8];
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  a3buf[1] = 2; /* scalar insert value, type != 4 (cov16's proven-safe shape) */
  a3buf[2] = 555;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, 0, a3buf, 5, 0), 1);
}

/* =========================================================================
 * CRT_OpenFile (105861-105867, uncovered 105861,105863): trivial one-line
 * forwarder to CRT_OpenFileShared. test_cov2_06.c already demonstrates
 * CRT_OpenFileShared itself is safe to call directly with a nonexistent
 * path (the off_51A574/j___NTAddFileHandle_ link hazard test_cov12.c
 * warned about has since been resolved by test_all.c's stub), so the one
 * extra forwarding layer here is equally safe. ========================== */
TEST(cov4_02_crt, open_file_forwards) {
  TOUCH(CRT_OpenFile(0, "cov4_02_nonexistent.dat", 0));
}

/* =========================================================================
 * Diagnostics_ShouldTraceWorldMapActionStage (38260-38302, uncovered 38268):
 * Diagnostics_IsWorldMapActionVerbose() caches its result in a function-
 * local `static int checked`, initialized fresh in this test's own forked
 * child, and reads the CLASH95_TRACE_WORLD_ACTION_VERBOSE env var. Setting
 * it truthy before the call takes the early "return 1;" branch. ========= */
TEST(cov4_02_diag, verbose_env_var_returns_true) {
  setenv("CLASH95_TRACE_WORLD_ACTION_VERBOSE", "1", 1);
  CHECK_EQ(Diagnostics_ShouldTraceWorldMapActionStage("any_stage"), 1);
}

/* =========================================================================
 * Scenario_LoadAllAiMultiplayerMapAndInitView (66064-66087, uncovered
 * 66083): test_cov2_07.c already backs `gameData` with a large zeroed
 * buffer and calls this exact function, yet the batch data shows line 66083
 * (the final `return Game_InitPlayerViewState();`) still uncovered -- so
 * something in the Scenario_LoadMultiplayerMapAndSeedPlayers/Map_LoadFromFile/
 * MiniMap_CreateSurface chain it drives through evidently still faults
 * before returning, even though each of those individually inspects as safe
 * for a missing map file (Map_LoadFromFile's own early-outs on failed
 * alloc/path-resolve are clean "return 0"s). Re-attempting with the same
 * proven-safe buffer shape per the harness instructions ("attempt once");
 * if this still doesn't reach 66083 the fault is one level deeper
 * (likely MiniMap_CreateSurface's render/sprite calls) and out of scope to
 * chase further here. */
TEST(cov4_02_scenario, load_all_ai_multiplayer_map_reattempt) {
  static unsigned char fakeGameData[2200000];
  int savedGD = gameData;
  memset(fakeGameData, 0, sizeof fakeGameData);
  gameData = (int)(intptr_t)fakeGameData;
  TOUCH(Scenario_LoadAllAiMultiplayerMapAndInitView(0));
  gameData = savedGD;
}

/* =========================================================================
 * Rules_PrintFloat (103310-103316, uncovered 103315): straight-line
 * two-call wrapper, never previously invoked. Rules_FloatToSymbol/
 * Output_Write are both already exercised safely elsewhere with arbitrary
 * int "stream handle" arguments (no router registered == no-op). ======== */
TEST(cov4_02_printfloat, prints_float_value) {
  TOUCH(Rules_PrintFloat(0, 3.5));
}

/* =========================================================================
 * Rules_BatchStarCommand (123065-123076, uncovered 123074): unlike the
 * Lexer_ParseValueList-gated arithmetic builtins, Rules_GetFileNameArg calls
 * Rules_RtnUnknown() DIRECTLY (no Lexer_ParseValueList in between), so it
 * never hits that family's own decompiler-lost-variable crash. A one-node
 * STRING-tagged (tag=3) argument chain matching Lexer_TokenExpect(1) makes
 * Parser_ParseForm's LABEL_4 fast path set the out-array's tag/value
 * cleanly, Rules_GetFileNameArg's "v6==3" check succeeds, and it hands back
 * a real (bogus/nonexistent) filename pointer -- Rules_BatchStar then calls
 * IO_FOpen on that path, which fails cleanly (Rules_OpenFileErrorMessage;
 * return 0) exactly like test_cov2_02.c's analogous
 * Rules_ParseLoadFactsCommand case. ======================================*/
TEST(cov4_02_batchstar, filename_parsed_open_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov4_02_missing_batch.clp";
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;
  int saved968 = g_ClipsHaltExecution;

  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  memset(valnode, 0, sizeof valnode);

  valnode[4] = (_DWORD)(intptr_t)path; /* offset 16: the parsed string pointer */
  *(short *)node = 3;                  /* STRING tag */
  *(int *)(node + 2) = (int)(intptr_t)valnode;
  *(int *)(node + 10) = 0;
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(int *)(anchor + 2) = (int)(intptr_t)funcrec;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  g_ClipsEvaluationError = 0;
  g_ClipsHaltExecution = 0;

  TOUCH(Rules_BatchStarCommand(0, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
  g_ClipsHaltExecution = saved968;
}

/* =========================================================================
 * Rules_MathTanh (129777-129789, uncovered 129786) and Rules_MathLog10
 * (130002-130026, uncovered 130014,130016,130017,130019,130020,130021,
 * 130022): both gate their remaining lines on Rules_MathParseSingleArg()
 * succeeding, which goes through Lexer_ParseValueList -- and that function's
 * very first line after a successful (non-"arg not found") Rules_RtnUnknown
 * lookup unconditionally dereferences an uninitialized local
 * (`a3 == *(_DWORD *)(v7 + 4)`, decompiler-lost 'v7') before it can ever
 * return 1, as documented in test_cov3_04.c. test_cov3_02.c already attempts
 * exactly this technique for this exact function (three cases: negative,
 * zero, and positive FLOAT argument nodes), yet the coverage data behind
 * this batch -- generated from a run that already includes test_cov3_02.c's
 * tests -- still lists every one of Rules_MathLog10's post-parse lines as
 * uncovered. That is strong evidence the v7 dereference really does fault
 * in practice for this call site (matching test_cov3_04.c's analysis, not
 * test_cov3_02.c's optimistic comment), so re-running the identical
 * technique here would not add anything: left uncovered as a confirmed hard
 * ceiling for both functions. */

/* =========================================================================
 * Instance_ModifyInstanceFunction (136470-136479, uncovered 136478): a
 * straight-line wrapper, but Instance_ActiveModifyInstanceFunction (the
 * middle call) unconditionally writes through its *own* a1 parameter
 * (`a1[1] = 2; a1[2] = ...`), and that a1 is Instance_ModifyInstanceFunction's
 * decompiler-lost, never-assigned local 'v1' -- an uncontrollable garbage
 * pointer from our side, so that write is likely to fault before the middle
 * call can return, which would keep line 136478 (the final
 * Rules_SetObjectPatternMatchDelay return) out of reach regardless of any
 * fixture we supply. Bootstrapping dword_51A960 at least avoids an *earlier*
 * guaranteed-crash (Instance_ActiveModifyInstanceFunction's very first
 * statement dereferences dword_51A960+6 unconditionally), banking as much
 * coverage as this input can reach; attempted once per the harness
 * instructions. */
TEST(cov4_02_instmodify, modify_instance_function_attempt) {
  static unsigned char anchor[32], node[32];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  /* anchor+6 must itself be a valid pointer (not just any nonzero anchor
   * address) since Instance_ActiveModifyInstanceFunction immediately reads
   * *(int*)(*(int*)(dword_51A960+6) + 10); a zeroed anchor+6 slot would
   * deref near-NULL address 10 before even reaching the a1-write hazard. */
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Instance_ModifyInstanceFunction(0.0));
  g_ClipsCurrentExpression = saved;
}

/* =========================================================================
 * Module_PrintPPFormByName (155360-155382, uncovered 155375): test_cov20.c
 * only drives the "not found" branch (no symbol registered). Interning the
 * lookup name for real (so Rules_FindSymbolEntry succeeds) and wiring a
 * hand-built module record into dword_51A9AC whose first field is that same
 * symbol pointer makes Module_FindByName find it on the very first
 * comparison (matches test_cov20.c's own Module_PrintAllNamesWithTally
 * fake-module-node technique). Leaving the fake module's own +4 field
 * ("PPForm") zero makes Module_GetPPForm return falsy, skipping the inner
 * Output_WriteLongString call and landing straight on `return 1;`. ======= */
TEST(cov4_02_module, print_pp_form_found_no_pp_form) {
  static _DWORD moduleNode[16];
  static const char modname[] = "Cov4_02FakeModule";
  int saved9AC = g_DefmoduleListHead;
  int *symbol;

  memset(moduleNode, 0, sizeof moduleNode);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  symbol = (int *)Str_Intern((char *)modname, 0);
  moduleNode[0] = (_DWORD)(intptr_t)symbol; /* offset0: matches Module_FindByName's *result check */
  moduleNode[1] = 0;                        /* offset4: PPForm == NULL */
  moduleNode[7] = 0;                        /* offset28-ish "next" terminator field used elsewhere */
  g_DefmoduleListHead = (int)(intptr_t)moduleNode;

  CHECK_EQ(Module_PrintPPFormByName(
               (_BYTE *)modname,
               (signed int)(intptr_t)"cov4_02_stream"),
           1);

  g_DefmoduleListHead = saved9AC;
}

/* =========================================================================
 * Rules_BuildSlotBoundTestExpression (183702-183709, uncovered 183708):
 * straight-line AST_NewNode + Rules_BuildSlotConstraintBitmapTestNode
 * wrapper ending in `return v2;` (decompiler-lost, unpredictable value but
 * harmless to return). Needs the AST/constraint memory pool bootstrapped
 * (same Mem_InitReserveBlock/Rules_InitAtomTables pattern used by the
 * sibling test in test_cov4_03.c for Rules_BuildSlotUnboundTestExpression,
 * which has an identical shape). ========================================*/
TEST(cov4_02_rules, build_slot_bound_test_expression) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BuildSlotBoundTestExpression(0));
}

/* =========================================================================
 * Defgeneric_ClearDefgenerics (161658-161698, uncovered 161677-161690):
 * test_cov3_03.c already covers the Rules_IsBloaded()==1 fast-return path.
 * The remaining lines are all inside the loop body over real defgeneric
 * constructs (Defgeneric_GetNextInModule/RemoveAllExplicitMethods/
 * RemoveDefgeneric), which needs an actual "defgeneric" construct registered
 * in the module system to enter at all -- there is no lightweight public API
 * to fabricate one (unlike the fact/class/module records faked elsewhere in
 * this suite), it would need the full defgeneric-construct parser machinery.
 * Out of scope for this batch; left uncovered. */

/* =========================================================================
 * Rules_TestConstraintAttributeParsedFlag (179406-179442, uncovered
 * 179422-179440): every branch after the first is a strcmp_ against a
 * decompiler-lost local (v3/v5/v6/.../v13) fed by whatever garbage happens
 * to sit on the stack at this exact call site. test_cov23.c, test_cov2_00.c
 * and test_cov3_04.c already tried three different fresh call-site stack
 * shapes without covering any of these lines. One more distinct local
 * layout, on the chance the garbage resolves differently here (low
 * confidence; matches the harness instructions' "attempt once, then move
 * on" guidance for this class of function). ============================= */
TEST(cov4_02_testparsedflag, yet_another_fresh_call_site) {
  double pad1;
  char pad2[17];
  int pad3[3];
  short pad4;
  memset(&pad1, 0, sizeof pad1);
  memset(pad2, 0, sizeof pad2);
  memset(pad3, 0, sizeof pad3);
  pad4 = 0;
  (void)pad4;
  TOUCH(Rules_TestConstraintAttributeParsedFlag(
      (int)(intptr_t)"cov4-02-unmatched-attr", (_DWORD *)pad3));
}

/* =========================================================================
 * Rules_CheckLiteralSlotValueConstraint (109720-109745, uncovered
 * 109731-109739): dereferences a decompiler-lost local ('v3', never
 * assigned) as a pointer base (`*(_DWORD *)(v3 + 8)`) to compute the second
 * argument to Rules_CheckFieldExprListAgainstConstraint, immediately after
 * the Rules_StaticConstraintCheckingEnabled() guard passes -- the same
 * "uninitialized-local-used-as-pointer-base" hazard documented for
 * Lexer_ParseValueList. test_cov2_02.c already attempts this exact function
 * (enabling the flag and driving a one-node field-expr list), but the
 * coverage data behind this batch -- which already includes test_cov2_02.c's
 * tests -- lists every line from 109731 onward as still uncovered,
 * confirming that dereference does fault here in practice. Left uncovered
 * as a confirmed hard ceiling. */

/* =========================================================================
 * Rules_DeleteFunction (127231-127251, uncovered 127240,127241,127242,
 * 127247): all four lines are only reachable once the first of three
 * chained Lexer_ParseValueList() calls returns truthy -- which requires
 * surviving the same unconditional-uninitialized-dereference hazard
 * described above for Rules_MathLog10/Rules_CheckLiteralSlotValueConstraint.
 * Confirmed hard ceiling; left uncovered. */

/* =========================================================================
 * Class_GetDefmessageHandlerListCommand (173569-173583, uncovered
 * 173579,173580,173582): all three lines require Class_ParseClassName-
 * AndInheritFlag to actually return (truthy or falsy) from its own
 * Lexer_ParseValueList(1, ..., 2, a3) call. Since Class_GetDefmessage-
 * HandlerListCommand's own early gate (`if (!Rules_RtnArgCount()) return
 * ...;`) already requires a nonzero argument count to reach line 173578 at
 * all, the requested argument position is always found (never the "not
 * found" -> dword_51A964 short-circuit that skips the crash), so the same
 * confirmed Lexer_ParseValueList uninitialized-dereference hazard applies
 * unconditionally here too. Confirmed hard ceiling; left uncovered. */

/* =========================================================================
 * WCIsvListBase_PopUntilMatchOrEmpty (54159-54175, uncovered 54170,54174):
 * test_cov04.c already investigated this and documented that both target
 * lines depend on the popped value coincidentally matching a decompiler-
 * lost, never-assigned local ('v4') -- not something a real or fake linked
 * list can make deterministic, and a wrong fake list risks spinning without
 * ever clearing the count field. Matches that documented ceiling; left
 * uncovered. */

/* =========================================================================
 * CRT_HasActiveWindow (144522-144537, uncovered 144532,144533,144534):
 * test_all.c's LoadLibraryA() stub unconditionally returns 0, so
 * `if (LibraryA)` can never be true in this harness -- test_cov3_03.c
 * already documents this and asserts the deterministic `return 0` path.
 * The three target lines live inside that always-skipped block and are
 * unreachable given the fixed stub; left uncovered. */

/* =========================================================================
 * Unit_BuildSelectedUnitPanelIconPalettePath (27768-27865, uncovered
 * 27829): the third copy loop always copies from the hardcoded local
 * `strcpy(v23, "c")`, so its first byte is always 'c' (never 0) -- the
 * `if (!v14) break;` at line 27829 can only fire when that first byte is
 * NUL, which this function's own hardcoded literal makes impossible to
 * reach from any caller-supplied input. Genuinely dead given the current
 * source; left uncovered. */

/* =========================================================================
 * Compat_StringHolderRemoveRange (87073-87102, uncovered 87090): reached
 * only when j_Mem_Alloc(text_len + 1) returns NULL. j_Mem_Alloc is a real,
 * unstubbed allocator in this build (test_cov2_02.c/test_cov09.c already
 * rely on the same underlying arena working correctly for
 * Compat_StringHolderCopyText), and there is no safe, deterministic way to
 * force a small allocation to fail without corrupting global allocator
 * state for every other test in the shared binary. Left uncovered. */
