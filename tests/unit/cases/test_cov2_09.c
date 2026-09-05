/* cov2_09: second-pass coverage batch. Targets (see cov2_batches/cov2_09.json):
 * Rules_MVSubseqFunction, Rules_FormatCountConversionSpecs,
 * Parser_RegisterProceduralFunctionParsers, Parser_CollectFunctionArguments,
 * Rules_GetTypeNameTokenCode, Rules_CompileStrategicRulesFile,
 * UnitStack_CycleAllSlotOrders, Rules_MathLog10, Rules_RefreshAgendaCommand,
 * Compiler_GenerateConstructTables, Rules_FindFactByIndex,
 * Defgeneric_CloseCodeFiles, Res_StreamSeekClamped, Rules_DribbleOnCommand,
 * Rules_MatchesCommand, UI_WaitForKeyOrTimeout, Rules_RemoveAllBreakFlags,
 * Rules_HostSeed, Deffacts_CloseCodeFiles, Palette_LoadFromQueryHandle,
 * WCIsvListBase_AppendValue, Compat_StringHolderAssignJoined,
 * Rules_SetInheritedFlagBit5, Unit_BuildSelectedUnitPanelIconSpritePath,
 * BuildingEconomyDialog_SetExitSignal, Compat_StringHolderInsertText,
 * Rules_FindInstanceSlot, Event_ClearHandlers, Rules_MathAsinh,
 * Instance_MessageDuplicateInstanceFunction, Class_LookupClassOrReportError.
 *
 * Many of these fan out through the shared Rules_RtnUnknown/Lexer_ParseValueList
 * "argument parsing" machinery documented in tests/unit/cases/test_cov11.c and
 * test_cov16.c: dword_51A960 is an "argument list" global whose +6 offset must
 * hold the address of the first argument node; Parser_ParseForm's LABEL_4 fast
 * path (scalar tags {0,1,2,3,5,7,8}) writes tag into a2[1] and
 * *(node+2) into a2[2] without needing a real parser/lexer running. */

/* ---- Res_StreamSeekClamped: fully deterministic, no UB locals. ---- */
TEST(cov2_09_res, stream_seek_clamped_negative) {
  static _DWORD stream[8];
  memset(stream, 0, sizeof stream);
  stream[3] = 100; /* +12: length */
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)stream, -5));
  CHECK_EQ(stream[2], 0);
}

TEST(cov2_09_res, stream_seek_clamped_within_length) {
  static _DWORD stream[8];
  memset(stream, 0, sizeof stream);
  stream[3] = 100;
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)stream, 40));
  CHECK_EQ(stream[2], 40);
}

TEST(cov2_09_res, stream_seek_clamped_past_length) {
  static _DWORD stream[8];
  memset(stream, 0, sizeof stream);
  stream[3] = 100;
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)stream, 500));
  CHECK_EQ(stream[2], 100);
}

/* ---- Rules_SetInheritedFlagBit5: walks a +48-linked chain; no UB. ---- */
TEST(cov2_09_rules, set_inherited_flag_bit5_chain) {
  static _DWORD nodeA[16], nodeB[16];
  memset(nodeA, 0, sizeof nodeA);
  memset(nodeB, 0, sizeof nodeB);
  *(_DWORD *)((char *)nodeA + 48) = (int)(intptr_t)nodeB;
  *(_DWORD *)((char *)nodeB + 48) = 0;
  TOUCH(Rules_SetInheritedFlagBit5(1, (int)(intptr_t)nodeA));
  TOUCH(Rules_SetInheritedFlagBit5(0, 0));
}

/* ---- Palette_LoadFromQueryHandle: null branch already covered; drive the
 * non-null branch through the real (compat, non-UB) loader helper. ---- */
TEST(cov2_09_palette, load_from_query_handle_null) {
  CHECK_EQ(Palette_LoadFromQueryHandle(0, 0), 0);
}

TEST(cov2_09_palette, load_from_query_handle_real) {
  static int palette_table[256];
  static char name[16] = "nope.col";
  memset(palette_table, 0, sizeof palette_table);
  TOUCH(Palette_LoadFromQueryHandle((intptr_t)palette_table, (intptr_t)name));
}

/* ---- WCIsvListBase_AppendValue: a1==0 -> WCCompat_ListFromHandle(0)==NULL
 * -> WCIsvListBase_AllocLinkNode returns 0 -> nullsub_7/return-0 branch. ---- */
TEST(cov2_09_wcisv, append_value_alloc_fail) {
  CHECK_EQ(WCIsvListBase_AppendValue(0, 0), 0);
}

/* ---- Rules_FindInstanceSlot: intern the slot name so Rules_FindSymbolEntry
 * actually finds it, driving the "found" branch (the call into
 * Instance_GetSlotValueBySymbol executes; whatever happens further down in
 * that unrelated callee doesn't affect this function's own line coverage). */
TEST(cov2_09_rules, find_instance_slot_found) {
  static _BYTE slotName[16];
  memcpy(slotName, "myslot", 7);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Str_Intern((char *)slotName, 0));
  TOUCH(Rules_FindInstanceSlot(0, slotName));
}

/* ---- Event_ClearHandlers: point dword_51A264 at a one-node chain so the
 * for-loop body (clearing the +25 word) executes once, then terminates via
 * the node's own +27 "next" field being 0. ---- */
TEST(cov2_09_event, clear_handlers_one_node) {
  static _DWORD node[16];
  int saved = g_Rules_HostFunctionListHead;
  memset(node, 0, sizeof node);
  g_Rules_HostFunctionListHead = (int)(intptr_t)node;
  TOUCH(Event_ClearHandlers());
  g_Rules_HostFunctionListHead = saved;
}

/* ---- UnitStack_CycleAllSlotOrders: MUST use a STATIC backing buffer --
 * the recovered code truncates the __int16* argument through a 32-bit `int`
 * (`stack_record = (int)(uintptr_t)a1`) before dereferencing it, so a plain
 * stack-local buffer's high 64-bit address bits get lost and the very first
 * slot read segfaults before any loop-body line runs (this is exactly what
 * happened to the pre-existing test_cov02 attempts at this function). A
 * static buffer's low address survives the round trip. ---- */
TEST(cov2_09_unitstack, cycle_all_slot_orders_early_return) {
  static unsigned char buf[1024];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = -1; /* slot0 terminator -> early-return path */
  TOUCH(UnitStack_CycleAllSlotOrders((__int16 *)buf, 0, 0.0));
}

TEST(cov2_09_unitstack, cycle_all_slot_orders_full_loop) {
  static unsigned char buf[1024];
  int i;
  memset(buf, 0, sizeof buf);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(buf + 6 + 31 * i) = 0; /* 10 valid (non -1) slots */
  TOUCH(UnitStack_CycleAllSlotOrders((__int16 *)buf, 0, 0.0));
}

/* ---- Unit_BuildSelectedUnitPanelIconSpritePath: the one uncovered line is
 * the `while (v15)` check inside the "c" (v23) copy loop -- structurally
 * fixed by that literal's own length, so a2/a3 can't move it. But the
 * "UnitType_GetResourceKey(a2)" copy loop right before it shares the same
 * destination cursor arithmetic, so varying a2 changes how many bytes get
 * written before the v23 loop starts, which can shift byte alignment enough
 * to flip whether the v14/v15 pair lands on an odd or even boundary. Try a
 * spread of a2 values. ---- */
TEST(cov2_09_unit, build_icon_sprite_path_vary_a2) {
  static char out[256];
  unsigned int a2;
  for (a2 = 0; a2 < 32; ++a2) {
    memset(out, 0, sizeof out);
    TOUCH(Unit_BuildSelectedUnitPanelIconSpritePath(out, (unsigned __int8)a2, 0));
  }
}

/* ---- BuildingEconomyDialog_SetExitSignal: the missing line is the
 * diagnostics fprintf gated on Diagnostics_IsWorldMapClickTraceEnabled(),
 * which is a real (non-UB) env-var-gated static in this compat port. ---- */
TEST(cov2_09_building, set_exit_signal_trace_enabled) {
  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 1);
  TOUCH(BuildingEconomyDialog_SetExitSignal(0, 0));
  unsetenv("CLASH95_TRACE_WORLD_CLICK");
}

/* ---- Rules_CompileStrategicRulesFile: never called in the first pass
 * (0/8); just call it once for whatever coverage is reachable before it
 * inevitably crashes/exits deep in the engine bring-up chain. ---- */
TEST(cov2_09_rules, compile_strategic_rules_file) {
  TOUCH(Rules_CompileStrategicRulesFile());
}

/* ---- Compiler_GenerateConstructTables: never called before (2/8). It
 * always crashes one frame down inside Rules_SetAtomicValueIndices, whose
 * bucket-array walk uses `int **`-typed (8-byte-stride) cursors over what
 * is really a packed 32-bit (_DWORD-stride) bucket table -- a 64-bit-port
 * pointer-width mismatch baked into that recovered function itself, not an
 * artifact of our arguments or global state. Confirmed via an isolated gdb
 * repro: even with Mem_InitReserveBlock/Rules_InitAtomTables bootstrapped
 * (so the buckets hold Rules_InitAtomTables' own interned true/false/o/O
 * symbols instead of being NULL), the mismatched cursor stride walks into
 * the middle of adjacent bucket slots and dereferences the resulting
 * garbage as a node pointer. So this reaches the exact same two lines
 * either way; call it plain to match the pre-existing (unreachable-further)
 * baseline. ---- */
TEST(cov2_09_compiler, generate_construct_tables) {
  TOUCH(Compiler_GenerateConstructTables(0));
}

/* ---- UI_WaitForKeyOrTimeout: thin wrapper, only ever needs the two call
 * sites reached; the per-test alarm(8) watchdog bounds any spin inside
 * UI_WaitForAnyKeyOrClick's message pump. ---- */
TEST(cov2_09_ui, wait_for_key_or_timeout) {
  TOUCH(UI_WaitForKeyOrTimeout(0, 0));
}

/* ---- Rules_RemoveAllBreakFlags: Module_NextEnum(0) reads dword_51A9AC
 * directly; point it at a fake single-module chain (next-module field at
 * +28 is 0, so the outer loop runs exactly once). The inner
 * Rules_GetNextDefrule(0)->Class_Enum(0, dword_54E64C)->Module_GetItem(0, a2)
 * chain reads dword_51A9B0 (current-module pointer) -> +8 "items" array ->
 * index dword_54E64C (0 by default, never set without a Rules_Init call) ->
 * "list wrapper" -> +4 "list head". Chain all of that to a single zeroed
 * defrule node so Rules_ClearBreakFlag has exactly one (harmless, all-zero)
 * node to clear before its own +48 chain terminates. ---- */
TEST(cov2_09_rules, remove_all_break_flags_one_module_one_rule) {
  static _DWORD outerModule[16];
  static _DWORD moduleStruct[16];
  static _DWORD itemsArray[32];
  static _DWORD listWrapper[8];
  static _DWORD fakeDefrule[16];
  int savedNextEnum = g_DefmoduleListHead;
  int savedCurrentModule = g_Clips_CurrentModule;

  memset(outerModule, 0, sizeof outerModule);
  memset(moduleStruct, 0, sizeof moduleStruct);
  memset(itemsArray, 0, sizeof itemsArray);
  memset(listWrapper, 0, sizeof listWrapper);
  memset(fakeDefrule, 0, sizeof fakeDefrule);

  /* outerModule+28 == 0 -> Module_NextEnum returns it once, then next call
   * (with a1==outerModule) reads *(outerModule+28) == 0 -> outer loop ends. */
  moduleStruct[2] = (_DWORD)(intptr_t)itemsArray; /* +8 offset */
  itemsArray[0] = (_DWORD)(intptr_t)listWrapper;  /* index dword_54E64C==0 */
  listWrapper[1] = (_DWORD)(intptr_t)fakeDefrule; /* +4 offset: list head */
  /* fakeDefrule+16 (next-in-Class_Enum chain) and +48 (break-flag chain) and
   * byte+29 all stay 0 from memset -> single safe iteration each. */

  g_DefmoduleListHead = (int)(intptr_t)outerModule;
  g_Clips_CurrentModule = (int)(intptr_t)moduleStruct;

  TOUCH(Rules_RemoveAllBreakFlags());

  g_DefmoduleListHead = savedNextEnum;
  g_Clips_CurrentModule = savedCurrentModule;
}

/* ---- Rules_FindFactByIndex: dword_51A15C is the "first fact" global.
 * Point it at a fact whose byte+29 is >=0 (so Rules_GetNextFact doesn't
 * immediately bail) and whose +36 "next fact" chains onward, so any
 * loop-continuation the (decompiler-lost) comparison drives still safely
 * terminates. Empirically the loop's uninitialized comparator reads as 0
 * in a fresh forked test, so a single all-zero fact only exercises the
 * "match immediately" exit; give fact1 a non-zero +24 field so the first
 * comparison mismatches and drives the loop body (the re-entrant
 * Rules_GetNextFact call and its `!result` check) before chaining to an
 * all-zero fact2 that lets a subsequent comparison match and exit
 * normally. ---- */
TEST(cov2_09_rules, find_fact_by_index_two_facts) {
  static _DWORD fact1[16], fact2[16];
  int saved = g_Rules_FactListHead;
  memset(fact1, 0, sizeof fact1);
  memset(fact2, 0, sizeof fact2);
  *(_DWORD *)((char *)fact1 + 24) = 0xdead;      /* likely mismatches the
                                                     uninitialized comparator */
  *(_DWORD *)((char *)fact1 + 36) = (_DWORD)(intptr_t)fact2; /* next fact */
  /* fact2 is all-zero: +24 == 0 and +36 == 0 (chain terminator). */
  g_Rules_FactListHead = (int)(intptr_t)fact1;
  TOUCH(Rules_FindFactByIndex(0));
  g_Rules_FactListHead = saved;
}

/* ---- Defgeneric_CloseCodeFiles: the do/while always runs exactly 5 times
 * (v11 = a2+5 is fixed by the loop shape). Rules_ConstructCodeFileClose's
 * `Output_WriteFormatted(...)` tail path needs a real CRT-lock-initialized
 * stream object we can't fake here, so instead keep every `result` (a1[i])
 * zero to take its OTHER branch, and back a4 with a zeroed handle-table
 * whose first DWORD is 0 so `if (!*(_DWORD*)v9) return 0;` returns
 * immediately, safely, before ever reaching that stream write -- letting
 * Defgeneric_CloseCodeFiles's own loop tail (increment/compare/return) run
 * to completion across all 5 iterations. ---- */
TEST(cov2_09_defgeneric, close_code_files_five_iterations) {
  static int a1arr[8];
  static _DWORD a2arr[8];
  static _DWORD handleTable[32]; /* >= 5 entries * 12-byte stride, all zero */
  memset(a1arr, 0, sizeof a1arr);
  memset(a2arr, 0, sizeof a2arr);
  memset(handleTable, 0, sizeof handleTable);
  TOUCH(Defgeneric_CloseCodeFiles(a1arr, a2arr, 3, (int)(intptr_t)handleTable));
}

/* ---- Deffacts_CloseCodeFiles: reaching the a1&&a2-both-true tail
 * (LABEL_5) requires `result` (== our `a2` argument, forwarded verbatim as
 * Rules_ConstructCodeFileClose's own "result" formal) to be non-zero, which
 * forces that callee down its direct Output_WriteFormatted/stream-write
 * path -- the same real CRT-lock bring-up Defgeneric's five-iteration test
 * above sidesteps by staying on the `!result` branch instead. Not
 * reachable without that bring-up, so this only re-drives the already
 * -covered a1==0/a2==0 single-arg shapes. ---- */
TEST(cov2_09_deffacts, close_code_files_neither_arg) {
  TOUCH(Deffacts_CloseCodeFiles(0, 0, 3, 100));
}

/* ---- Rules_MatchesCommand: force Rules_GetConstructNameArg's
 * Rules_RtnArgCount()==1 && Parser_ParseForm-tag==2 "success" path (the same
 * anchor/termBuf recipe test_cov11.c already validates for
 * Rules_Get{File,Construct}NameArg) so `result` comes back non-NULL.
 * Rules_FindDefruleByName forwards into Rules_FindConstructByNameGeneric,
 * which unconditionally calls Module_BeginEnum() first -- that dereferences
 * the reserve-block arena base (dword_54DBA8), so it needs the same
 * Mem_InitReserveBlock bring-up other batches use. With no symbol table
 * entries interned, the inner Rules_FindSymbolEntry lookup then safely
 * misses and returns 0 *before* touching its own uninitialized-int second
 * argument, so this reaches the "not found" branch instead of crashing. */
TEST(cov2_09_rules, matches_command_construct_arg_success_not_found) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static char ruleName[16] = "myrule";
  int saved = g_ClipsCurrentExpression;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2; /* tag == 2 -> Parser_ParseForm LABEL_4 fast path */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;  /* valNode == self */
  *(_DWORD *)((char *)termBuf + 10) = 0;                      /* argcount == 1 */
  *(_DWORD *)((char *)termBuf + 16) = (int)(intptr_t)ruleName;/* *(valNode+16) */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MatchesCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_DribbleOnCommand: same anchor/termBuf success recipe (this
 * time via Rules_GetFileNameArg's direct v6/v7 read, no extra indirection)
 * to get a non-NULL filename and reach the Dribble_TurnOn call. Whether
 * Lexer_TokenExpect(1) actually returns something other than -1 depends on
 * the same decompiler-lost comparison as everywhere else in this file; if it
 * doesn't, this still safely re-exercises the already-covered early-return
 * path. ---- */
TEST(cov2_09_rules, dribble_on_command_success_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static char fname[32] = "cov2_09_dribble_scratch.txt";
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2;
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)termBuf + 16) = (int)(intptr_t)fname;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_DribbleOnCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;

  remove(fname);
}

/* Second attempt with a perturbed local stack layout (extra padding array
 * ahead of the anchor/termBuf pair) -- Lexer_TokenExpect's decompiler-lost
 * comparison depends on whatever this call site's compiled stack slot
 * happens to hold, and that can differ from the attempt above's. */
TEST(cov2_09_rules, dribble_on_command_success_attempt2) {
  static _DWORD padding[37];
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static char fname[32] = "cov2_09_dribble_scratch2.txt";
  int saved = g_ClipsCurrentExpression;

  memset(padding, 0, sizeof padding);
  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2;
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)termBuf + 16) = (int)(intptr_t)fname;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_DribbleOnCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;

  remove(fname);
}

TEST(cov2_09_rules, dribble_on_command_wrong_type_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 1; /* tag != 2,3 -> Rules_GetFileNameArg "wrong type" */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_DribbleOnCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_RefreshAgendaCommand: an empty (but valid, zeroed) arg chain
 * makes Rules_RtnArgCount() deterministically return 0, which forces
 * Lexer_TokenExpect(1) to return either 0 or -1 (never 1) -- empirically
 * that took the already-covered immediate-return path with no gain. Try
 * instead the argcount==1 anchor/termBuf recipe already proven to reach
 * Rules_Get{File,Construct}NameArg's success branch elsewhere in this file:
 * with the arg count exactly matching Lexer_TokenExpect's `a1==1`, its
 * decompiler-lost comparison is far more likely to land on `result==1`,
 * entering the branch that calls Rules_GetModuleNameArg at all (previously
 * unreached). ---- */
TEST(cov2_09_rules, refresh_agenda_command_one_arg) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 2; /* tag == 2 -> Parser_ParseForm LABEL_4 fast path */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0; /* argcount == 1 */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_RefreshAgendaCommand(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_HostSeed / Rules_MVSubseqFunction / Rules_FormatCountConversionSpecs
 * / Rules_MathLog10 / Rules_MathAsinh: all gate their real work behind
 * Lexer_ParseValueList, whose *own* first check reads a genuinely
 * uninitialized local (`v7` in the recovered code, see clash95.c comment at
 * 481574) before ever consulting a2/a3. Best-effort: set up the same
 * argcount==1/tag-matching-type anchor+termBuf chain Rules_Get*Arg uses
 * successfully elsewhen, in case that stack slot happens to line up; if not,
 * these just re-exercise the already-covered early-fail path harmlessly. */
TEST(cov2_09_rules, host_seed_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 1; /* INTEGER, matches a3==1 in Rules_HostSeed's call */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  valnode[4] = 7; /* +16: raw integer payload */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_HostSeed(1, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_09_rules, mv_subseq_function_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  static _DWORD out[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  memset(out, 0, sizeof out);
  *(short *)termBuf = 1;
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  valnode[4] = 3;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MVSubseqFunction(out, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_09_rules, format_count_conversion_specs_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  static char fmt[8] = "%d";
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 3; /* STRING, matches a3==3 in the Lexer_ParseValueList call */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  valnode[4] = (_DWORD)(intptr_t)fmt; /* +16: string payload pointer */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_FormatCountConversionSpecs(2, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_09_rules, math_log10_and_asinh_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 0; /* FLOAT, matches a3==0 in Rules_MathParseSingleArg's call */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(double *)((char *)valnode + 16) = 4.0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MathLog10(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_09_rules, math_asinh_attempt) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 0;
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(double *)((char *)valnode + 16) = 1.5;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MathAsinh(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Parser_RegisterProceduralFunctionParsers: a straight-line chain of
 * Parser_AddFunctionParser calls, each of which succeeds deterministically
 * (no UB) once Rules_MakeSymbol has a live reserve-block arena + atom tables
 * to intern into -- the same one-time bring-up other batches use. ---- */
TEST(cov2_09_parser, register_procedural_function_parsers) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Parser_RegisterProceduralFunctionParsers());
}

/* ---- Parser_CollectFunctionArguments: drive with a fake logical-name
 * channel distinct from the default-zero stream globals (same recipe as
 * test_cov20.c's collect_function_arguments case) so Parser_NextToken hits
 * EOF quickly instead of blocking. a1 is backed by a static buffer since a
 * truthy v10[0]==1 branch would otherwise call AST_Free on a truncated
 * stack address. ---- */
TEST(cov2_09_parser, collect_function_arguments_eof) {
  static _DWORD a1buf[64];
  memset(a1buf, 0, sizeof a1buf);
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 424242, 0));
}

/* ---- Rules_GetTypeNameTokenCode: every one of its comparisons reads a
 * decompiler-lost local that (per clash95.c's own comments) is never
 * actually assigned from `a1`, so which branch fires is independent of our
 * input. Call it with every named type string (as test_cov23.c already
 * does) plus a couple of repeats, on the chance that varying call order
 * shifts whatever stack garbage those reads observe. ---- */
TEST(cov2_09_rules, get_type_name_token_code_sweep) {
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aSymbol_7));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aFloat_4));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aNumber_2));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstanceName_4));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstanceAddr_8));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstance_6));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aExternalAddr_1));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aFactAddress_2));
  TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)"zzz-unmatched-again"));
  TOUCH(Rules_GetTypeNameTokenCode(0));
}

/* ---- Instance_MessageDuplicateInstanceFunction: best-effort with the
 * shared safe empty arg-chain (see test_cov16.c's cov16_setup_safe_argctx)
 * so the deep dword_51A960 chase in Instance_ActiveMessageDuplicateInstanceFunction
 * lands on real (if empty) memory instead of a wild pointer. ---- */
TEST(cov2_09_instance, message_duplicate_instance_function_attempt) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(argnode, 0, sizeof argnode);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)funcrec; /* +10/+10 chase target */
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;

  TOUCH(Instance_MessageDuplicateInstanceFunction(0.0));

  g_ClipsCurrentExpression = saved;
}

/* ---- Class_LookupClassOrReportError: best-effort at the "found" branch --
 * a name with no "::" module separator takes Class_LookupByQualifiedName's
 * simple Class_LookupInScope path; without any classes registered this most
 * likely still reports "not found" (already covered), but costs nothing to
 * retry with a distinct name. ---- */
TEST(cov2_09_class, lookup_class_or_report_error_attempt) {
  static _BYTE name[16];
  memcpy(name, "SomeClass", 10);
  TOUCH(Class_LookupClassOrReportError(0, name));
}
