/* cov2_06: second-pass coverage additions for a mixed batch of previously
 * partially-covered functions (see cov2_batches/cov2_06.json). Each TEST
 * below targets specific still-uncovered lines/branches identified by
 * reading the corresponding clash95.c function bodies. Harness runs every
 * TEST in its own forked child process with an alarm(8) watchdog, so it is
 * safe to drive functions that crash, spin, or exit -- coverage up to that
 * point is still banked. */

/* ---------------------------------------------------------------------
 * Diagnostics_TraceWorldMapUnitSnapshot (38570-38629): only 3/31 lines
 * covered previously (presumably just the early "!enabled -> return"
 * guard). Fully drive it: enable both env-var gates
 * (CLASH95_TRACE_WORLD_CLICK for the outer guard,
 * CLASH95_TRACE_WORLD_UNIT_SLOTS for the nested per-slot loop), and back
 * `gameData` with a real static buffer (gameData is a plain non-static
 * `int` global storing a base address as a 32-bit int -- a static buffer's
 * low address round-trips safely through that truncation, unlike a stack
 * address). With the buffer zeroed, every stack record's first slot has
 * unit_type == 0 (satisfies "!= -1 && <= 0x28"), so the outer per-stack-
 * record loop body runs unconditionally for all 500 iterations. One
 * stack's slot 3 is set to -1 to also exercise the inner loop's "break"
 * line at least once; the rest run the inner loop to completion (10
 * iterations, no break) since their slot types stay 0. */
TEST(cov2_06_diag, trace_world_map_unit_snapshot_full) {
  static unsigned char worldbuf[600000];
  int saved_gamedata = gameData;

  memset(worldbuf, 0, sizeof worldbuf);
  gameData = (int)(intptr_t)worldbuf;

  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 1);
  setenv("CLASH95_TRACE_WORLD_UNIT_SLOTS", "1", 1);

  {
    int stack_record = UNIT_STACK(10);
    *(short *)UNIT_STACK_SLOT(stack_record, 3) = -1; /* force inner break */
  }

  Diagnostics_TraceWorldMapUnitSnapshot("cov2_06_stage");

  gameData = saved_gamedata;
  unsetenv("CLASH95_TRACE_WORLD_CLICK");
  unsetenv("CLASH95_TRACE_WORLD_UNIT_SLOTS");
}

/* ---------------------------------------------------------------------
 * Rules_RegisterControlFlowFunctions (123690-123708): straight-line chain
 * of Rules_RegisterHostFunction + Rules_SetFunctionSeqOverloadFlags calls,
 * same shape as the already-proven cov16/cov17 Rules_Register* tests.
 * Needs the reserve-block arena + atom tables bootstrapped first. */
TEST(cov2_06_rules, register_control_flow_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterControlFlowFunctions());
}

/* ---------------------------------------------------------------------
 * CRT_DetachThreadDataAndMaybeCloseHandle (104321-104343): 0/12 covered.
 * `dwTlsIndex` defaults to (DWORD)-1, so with no setup the function takes
 * its single-line "return result;" fast path and nothing else executes.
 * All of its dependencies (TlsAlloc/TlsGetValue/TlsSetValue/TlsFree in
 * compat/decomp_runtime_stubs.c, and _RemoveThreadData_/CloseHandle) are
 * real, safe stubs in this build (CloseHandle's CompatGetEventHandle does
 * a pure bounds check on the handle's integer value before ever touching
 * memory, so passing a bogus non-NULL "handle" is safe). Drive all three
 * shapes: v2 (the thread-data block's +222 field) zero (skip CloseHandle
 * entirely), v2 nonzero with the outer `result` arg zero (skip CloseHandle
 * via the `v1` guard), and v2 nonzero with `result` arg nonzero (take the
 * CloseHandle branch). */
TEST(cov2_06_crt, detach_thread_data_all_branches) {
  DWORD saved_idx = dwTlsIndex;
  static unsigned char thread_block[256];
  memset(thread_block, 0, sizeof thread_block);

  dwTlsIndex = TlsAlloc();
  if (dwTlsIndex != (DWORD)-1) {
    TlsSetValue(dwTlsIndex, thread_block);
    *(void **)(thread_block + 222) = 0;
    TOUCH(CRT_DetachThreadDataAndMaybeCloseHandle((char *)0));

    TlsSetValue(dwTlsIndex, thread_block);
    *(void **)(thread_block + 222) = (void *)(intptr_t)0x1234;
    TOUCH(CRT_DetachThreadDataAndMaybeCloseHandle((char *)0));

    TlsSetValue(dwTlsIndex, thread_block);
    *(void **)(thread_block + 222) = (void *)(intptr_t)0x1234;
    TOUCH(CRT_DetachThreadDataAndMaybeCloseHandle((char *)1));

    TlsFree(dwTlsIndex);
  }
  dwTlsIndex = saved_idx;
}

/* ---------------------------------------------------------------------
 * Rules_ExtractModuleAndConstructName (114648-114669): 5/15 covered
 * previously (presumably just the "no '::' separator -> return a1"
 * fast path via Rules_FindModuleSeparator returning 0). Feed a
 * double-colon-qualified name so Rules_FindModuleSeparator returns a
 * nonzero index, reaching the `Rules_ExtractModuleName` call one line
 * further in. Rules_ExtractModuleName itself has decompiler-lost locals
 * (v3/v4 "possibly undefined") feeding strncpy_, so this is expected to
 * crash one function down -- isolated in its own TEST; still banks the
 * extra "if (!qualifier_length) return" / call-site line in our target
 * function before that happens. */
TEST(cov2_06_rules, extract_module_and_construct_name_qualified) {
  static unsigned char name[] = "cov2mod::cov2construct";
  TOUCH(Rules_ExtractModuleAndConstructName(name));
}

/* ---------------------------------------------------------------------
 * Rules_WriteConstructModuleItemHeaderToCode (133174-133205): 5/14
 * covered. The existing cov18 test calls it with a2==0, which (with the
 * default dword_51A9B0 == 0) makes Module_GetItem's "if (!result)
 * {if (!dword_51A9B0) return result;}" branch return 0 immediately, so
 * v8 == 0 and the subsequent `*(_DWORD *)(v8 + 4)` faults right away.
 * Here we instead pass a real module record as a2 so Module_GetItem
 * takes its *other* path (`result = a2; v2 = *(v2+8)`), reaching a
 * different set of lines before any fault -- the index used
 * (Rules_WriteConstructModuleItemHeaderToCode's own lost-register `v7`)
 * is a genuinely uninitialized decompiler artifact, so whether the
 * eventual per-item read lands on valid memory is unpredictable; either
 * way this exercises additional setup lines beyond the a2==0 case and is
 * isolated so a crash here cannot cost other tests' coverage. */
TEST(cov2_06_rules, write_construct_module_item_header_real_module) {
  static _DWORD module_items[4096];
  static _DWORD module_rec[16];
  int i;

  memset(module_rec, 0, sizeof module_rec);
  for (i = 0; i < 4096; ++i) module_items[i] = (_DWORD)(intptr_t)module_rec;
  module_rec[2] = (_DWORD)(intptr_t)module_items; /* offset +8 */

  TOUCH(Rules_WriteConstructModuleItemHeaderToCode(
      0, (int)(intptr_t)module_rec, 1, 2, 'q'));
}

/* ---------------------------------------------------------------------
 * Rules_NthFunction (127794-127826): the cov16 test already reaches the
 * "else" nil-symbol fallback deterministically. Its `&&`-chained success
 * condition requires Lexer_ParseValueList(2, &v10, 4, a3) (requesting
 * MULTIFIELD, type code 4) to return nonzero, but that function's
 * dispatch table has no successful-match branch for type code 4 at all
 * (only 110/111/2/8/112/1/default), so that second call structurally
 * always fails regardless of node content -- the "if" body
 * (127814-127817) is unreachable via this call path. We can still bank
 * one additional line (the second Lexer_ParseValueList call itself, which
 * is otherwise short-circuited away) by making the *first*
 * Lexer_ParseValueList(1, v9, 1, a3) call (requesting INTEGER) actually
 * succeed: feed a real one-node argument chain whose node has type tag 0
 * (FLOAT) -- Lexer_ParseValueList's "integer requested, float supplied"
 * coercion branch is unconditional/deterministic (unlike the reverse
 * float-requested/integer-supplied direction, which returns a decompiler-
 * undefined value) and returns 1 after boxing via Rules_AddIntegerValue. */
TEST(cov2_06_rules, nth_function_reach_second_parse) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  static unsigned char float_value_node[32];
  static _DWORD out[8];
  int saved_ctx = g_ClipsCurrentExpression;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  memset(float_value_node, 0, sizeof float_value_node);
  memset(out, 0, sizeof out);

  *(double *)(float_value_node + 16) = 3.0;
  *(short *)(expr_node + 0) = 0; /* FLOAT type tag */
  *(_DWORD *)(expr_node + 2) = (_DWORD)(intptr_t)float_value_node;
  *(_DWORD *)(expr_node + 10) = 0; /* terminate arg chain at length 1 */
  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Rules_NthFunction((int)(intptr_t)out, 5, 0.0));

  g_ClipsCurrentExpression = saved_ctx;
}

/* ---------------------------------------------------------------------
 * Rules_StrCompareBuiltin (128972-129029): the cov17 test only reaches
 * the immediate Rules_ArgRangeCheck out-of-range fast path. Attempt to
 * drive a real 1-node integer argument chain so Rules_RtnArgCount sees
 * count 1 (Rules_ArgRangeCheck's own lower-bound compare uses a
 * decompiler-lost register, so whether count 1 is judged "in range" is
 * unpredictable) -- a good-faith, isolated attempt at reaching further
 * (the Lexer_ParseValueList calls / strcmp_ path) beyond the guaranteed
 * fast-path already covered elsewhere. */
TEST(cov2_06_rules, str_compare_builtin_one_arg_attempt) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  static unsigned char int_value_node[32];
  int saved_ctx = g_ClipsCurrentExpression;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  memset(int_value_node, 0, sizeof int_value_node);

  *(int *)(int_value_node + 16) = 7;
  *(short *)(expr_node + 0) = 1; /* INTEGER type tag */
  *(_DWORD *)(expr_node + 2) = (_DWORD)(intptr_t)int_value_node;
  *(_DWORD *)(expr_node + 10) = 0;
  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Rules_StrCompareBuiltin(0, 0.0));

  g_ClipsCurrentExpression = saved_ctx;
}

/* ---------------------------------------------------------------------
 * Rules_MathCsch / Rules_MathSqrt / Rules_AcotBuiltin / Rules_SinhBuiltin
 * (129716-130048ish): the cov17 test only reaches the
 * "!Rules_MathParseSingleArg(...) -> return 0.0" failure path (arg count
 * 0). All four funnel through Rules_MathParseSingleArg, which requires
 * Lexer_TokenExpect(1) to succeed (count == 1) and then
 * Lexer_ParseValueList(1, v5, 0, a3) (requesting FLOAT) to return
 * nonzero -- for a FLOAT request, the only way to reach a "return 1" at
 * all is the "integer supplied, float requested" coercion branch, whose
 * own return value is itself a decompiler-lost local (genuinely
 * unpredictable). This is a good-faith, isolated attempt with a real
 * one-node INTEGER argument chain (mirroring the Math builtins' own
 * documented pattern) to reach additional lines (the post-parse domain/
 * singularity checks and the real math calls) if the runtime happens to
 * resolve favorably; each call is isolated so an unlucky resolution (or
 * a crash) cannot cost the others' coverage. */
TEST(cov2_06_math, csch_sqrt_acot_sinh_one_int_arg_attempt) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  static unsigned char int_value_node[32];
  int saved_ctx;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

#define COV2_06_SETUP_ONE_INT_ARG(intval)                                    \
  do {                                                                       \
    memset(arg_list_head, 0, sizeof arg_list_head);                          \
    memset(expr_node, 0, sizeof expr_node);                                  \
    memset(int_value_node, 0, sizeof int_value_node);                        \
    *(int *)(int_value_node + 16) = (intval);                                \
    *(short *)(expr_node + 0) = 1; /* INTEGER type tag */                    \
    *(_DWORD *)(expr_node + 2) = (_DWORD)(intptr_t)int_value_node;           \
    *(_DWORD *)(expr_node + 10) = 0;                                         \
    *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;            \
    g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;                             \
  } while (0)

  saved_ctx = g_ClipsCurrentExpression;
  COV2_06_SETUP_ONE_INT_ARG(2);
  TOUCH(Rules_MathCsch(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved_ctx;

  saved_ctx = g_ClipsCurrentExpression;
  COV2_06_SETUP_ONE_INT_ARG(9);
  TOUCH(Rules_MathSqrt(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved_ctx;

  saved_ctx = g_ClipsCurrentExpression;
  COV2_06_SETUP_ONE_INT_ARG(2);
  TOUCH(Rules_AcotBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved_ctx;

  saved_ctx = g_ClipsCurrentExpression;
  COV2_06_SETUP_ONE_INT_ARG(2);
  TOUCH(Rules_SinhBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved_ctx;

#undef COV2_06_SETUP_ONE_INT_ARG
}

/* ---------------------------------------------------------------------
 * Rules_ShowBanner_StrategicClash (69391-69402): 0/6 covered previously
 * (nothing in the first pass called it). Straight-line: probe stack
 * frame, Rules_Clear(), then Rules_Bload() against a fixed literal
 * filename that does not exist on disk -- Rules_Bload's own file-open
 * failure path is expected to handle that safely (matching the pattern
 * other Bload-driving commands rely on elsewhere in the suite). */
TEST(cov2_06_rules, show_banner_strategic_clash) {
  TOUCH(Rules_ShowBanner_StrategicClash());
}

/* ---------------------------------------------------------------------
 * MainMenu_RequestOptionsMenu (63997-64005): 0/5 covered. Straight-line
 * wrapper around UIWidget_PlayPressedReleaseAnimation + two global
 * writes. Field @0 >= 640 keeps UIWidget_RefreshActionButtonState on its
 * safe early-return path (documented pattern from cov04/cov05); field
 * @49 == 0 skips the Audio_PlayButtonSound call. */
TEST(cov2_06_mainmenu, request_options_menu) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  *(_DWORD *)(widget + 49) = 0;

  TOUCH(MainMenu_RequestOptionsMenu((uintptr_t)(intptr_t)widget));

  CHECK_EQ(g_MainMenuRequestedScreen, MAIN_MENU_REQUEST_OPTIONS);
  CHECK_EQ(g_PlayGameMenuExitRequested, 1);
}

/* ---------------------------------------------------------------------
 * Class_GetSlotNameByID (141765-141773): 0/5 covered. Class_FindSlotName-
 * EntryByID scans a 167-bucket array rooted at dword_51AD70 with NO NULL
 * check on the base pointer itself (dword_51AD70 defaults to 0, so
 * calling this cold would NULL-deref inside the nested scan before ever
 * returning to our target function) -- back it with a real zeroed bucket
 * table so the "not found" scan runs safely to completion and
 * Class_GetSlotNameByID's own "return result;" (result == 0) line is
 * actually reached. A second test plants a fake entry directly in
 * bucket 0 to reach the "if (result) return *(a1+12)" success line too. */
TEST(cov2_06_class, get_slot_name_by_id_not_found) {
  static _DWORD buckets[256];
  int saved = g_Defclass_SlotNameHashTablePtr;
  memset(buckets, 0, sizeof buckets);
  g_Defclass_SlotNameHashTablePtr = (int)(intptr_t)buckets;

  CHECK_EQ(Class_GetSlotNameByID(999999), 0);

  g_Defclass_SlotNameHashTablePtr = saved;
}

TEST(cov2_06_class, get_slot_name_by_id_found) {
  static _DWORD entry[16];
  int saved = g_Defclass_SlotNameHashTablePtr;
  static _DWORD bucket0;

  memset(entry, 0, sizeof entry);
  entry[2] = 424242;      /* offset 8: a1 match key */
  entry[3] = 0xABCD;       /* offset 12: name returned by GetSlotNameByID */
  entry[5] = 0;            /* offset 20: next link (terminate) */
  bucket0 = (_DWORD)(intptr_t)entry;
  g_Defclass_SlotNameHashTablePtr = (int)(intptr_t)&bucket0;

  CHECK_EQ(Class_GetSlotNameByID(424242), (int)0xABCD);

  g_Defclass_SlotNameHashTablePtr = saved;
}

/* ---------------------------------------------------------------------
 * CampaignMenu_WriteButtonWidgetTemplateRecord (63816-63834): 0/4
 * covered. Pure straight-line record writer (delegates to
 * MainMenu_WriteButtonWidgetTemplateRecord, which itself memsets 53
 * bytes, then overwrites offset 28); no branches, no unsafe state. */
TEST(cov2_06_campaignmenu, write_button_widget_template_record) {
  static unsigned char record[64];
  memset(record, 0xAA, sizeof record);

  CampaignMenu_WriteButtonWidgetTemplateRecord(
      record, 10, 20, 1, 2, 3, "cov2_06_sound");

  CHECK_EQ(*(_DWORD *)(record + 0), 10);
  CHECK_EQ(*(_DWORD *)(record + 4), 20);
}

/* ---------------------------------------------------------------------
 * Compat_QueryXorDecodeBuffer (93167-93181): 4/7 covered (presumably the
 * a3==0 immediate-return-with-no-iterations case). Drive the loop body
 * with a3 > 0 so the XOR-decode-in-place lines actually execute. */
TEST(cov2_06_compat, query_xor_decode_buffer_loops) {
  static unsigned char rec[64];
  static unsigned char data[16];
  unsigned char *result;

  memset(rec, 0, sizeof rec);
  memset(data, 0x55, sizeof data);
  *(_DWORD *)(rec + 48) = 3;  /* running counter seed */
  *(_DWORD *)(rec + 20) = 9;  /* xor key component */

  result = Compat_QueryXorDecodeBuffer((int)(intptr_t)rec, data, 4);
  CHECK(result == data + 4);
}

/* ---------------------------------------------------------------------
 * Rules_BsaveAtomTables (116830-116840): 0/5 covered. Straight-line chain
 * of 4 Bsave*Table calls; bootstrap the reserve arena/atom tables first
 * (these tables are what the Bsave* walkers iterate over) so the calls
 * have real, if empty, tables to walk instead of raw NULL globals. */
TEST(cov2_06_rules, bsave_atom_tables) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BsaveAtomTables(0));
}

/* ---------------------------------------------------------------------
 * Rules_HostMultifieldp (126110-126123): 4/7 covered (the cov16
 * hostpred test exercises the wrapper via a safe-but-empty arg chain,
 * landing on whichever way Lexer_TokenExpect(1)'s lost-register branch
 * resolves, but never the "v3[1] == 4 -> return 1" success line). Drive
 * a real one-node MULTIFIELD-tagged argument: Parser_ParseForm's type-4
 * case unconditionally sets the out-param's type tag to 4 before reading
 * any further (decompiler-preserved) fields, so as long as the node's
 * payload points at a valid (zeroed) "multifield descriptor" with an
 * empty index range (begin > end, skipping Rules_PropagateReturnValue-
 * Depth's internal per-element loop), the whole chain resolves safely
 * and deterministically to Rules_HostMultifieldp's "return 1" line. */
TEST(cov2_06_rules, host_multifieldp_success) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  static unsigned char mf_descriptor[32];
  static unsigned char value_list_header[32];
  int saved_ctx = g_ClipsCurrentExpression;

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  memset(mf_descriptor, 0, sizeof mf_descriptor);
  memset(value_list_header, 0, sizeof value_list_header);

  *(_DWORD *)(mf_descriptor + 8) = (_DWORD)(intptr_t)value_list_header;
  *(_DWORD *)(mf_descriptor + 12) = 1; /* begin */
  *(_DWORD *)(mf_descriptor + 16) = 0; /* end < begin -> skip inner loop */

  *(short *)(expr_node + 0) = 4; /* MULTIFIELD type tag */
  *(_DWORD *)(expr_node + 2) = (_DWORD)(intptr_t)mf_descriptor;
  *(_DWORD *)(expr_node + 10) = 0;

  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Rules_HostMultifieldp(0.0));

  g_ClipsCurrentExpression = saved_ctx;
}

/* ---------------------------------------------------------------------
 * Rules_HostArmyHasBuilder (69702-69706): 0/2 covered. Both of its lines
 * ((void)a1 is a no-op and the return statement) execute in full
 * regardless of what happens inside the nested Rules_RtnLong /
 * UnitStack_HasBuilder calls -- Rules_RtnLong is already safe with the
 * default dword_51A960 == 0 (every dereference is ternary-guarded on the
 * NULL check), and any crash inside UnitStack_HasBuilder (a different
 * function, not this one) happens only after this function's own "return"
 * line has already begun executing. */
TEST(cov2_06_rules, host_army_has_builder) {
  TOUCH(Rules_HostArmyHasBuilder(0, 0.0));
}

/* ---------------------------------------------------------------------
 * CRT_OpenFileShared (105867-105870): 0/2 covered. Single-line forwarder
 * to CRT_CreateFileHandleFromPath; the call/return line executes in full
 * regardless of what that (much larger, decompiler-lossy) callee does
 * afterward. */
TEST(cov2_06_crt, open_file_shared) {
  TOUCH(CRT_OpenFileShared(0, "cov2_06_nonexistent.dat", 0, 0));
}

/* ---------------------------------------------------------------------
 * UnitStack_CalcMilitaryStrength (27001-27007): 2/3 covered (existing
 * cov02 test forces Unit_GetSquadCount(a1) == 0 via a real unit-stack
 * buffer). Both of this function's statements always execute in full
 * regardless of the nested call's outcome (same "call line already
 * started" reasoning as above), so this is a low-risk additional call
 * with a different squad count to vary the value fed onward. */
TEST(cov2_06_unit, calc_military_strength_nonzero_squad) {
  static unsigned char buf[512];
  memset(buf, 0, sizeof buf);
  *(__int16 *)(buf + 6) = 2; /* a nonzero squad-slot type -> squad count > 0 */
  TOUCH(UnitStack_CalcMilitaryStrength((int)(intptr_t)buf));
}

/* ---------------------------------------------------------------------
 * Diagnostics_ShouldTraceWorldMapActionStage (38260-38300): 29/30
 * covered. The one remaining line is almost certainly the
 * "!(battle_input_loop_count & 0xFF)" rollover check inside the
 * "battle_turn_loop_after_input_widgets" branch, which needs the
 * function's *static* internal counter to exceed 32 AND hit a multiple
 * of 256 -- only reachable by calling it enough times in a row (the
 * counter persists across calls within this one forked test process). */
TEST(cov2_06_diag, should_trace_world_map_action_stage_rollover) {
  int i;
  for (i = 0; i < 300; ++i) {
    TOUCH(Diagnostics_ShouldTraceWorldMapActionStage(
        "battle_turn_loop_after_input_widgets"));
  }
  /* Same rollover shape for the move-preview counter branch. */
  for (i = 0; i < 130; ++i) {
    TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_move_track_enter"));
  }
}

/* ---------------------------------------------------------------------
 * Building_IsUnitLicenceEligible (57535-57574): 19/20 covered. The
 * existing cov05 test always uses a2 == UNIT_TYPE_PEASANT (0) -- the only
 * value that stays in-bounds of the tech-level tables
 * (g_UnitTypeProductionRequiredTechLevelMode2/OtherModes are both
 * declared with just 1 element in this recovered source, so any other
 * unit_type indexes 88*a2 bytes past the end of a 1-byte global; still
 * mapped static data, not a crash, but its content is whatever
 * unrelated global happens to sit there and can't be predicted from
 * source alone). g_ProductionLicenceSmithsRequiredUnitTypes[0] is
 * UNIT_TYPE_HEAVY_INFANTRY (not PEASANT), so reaching the "smiths-
 * required unit type present -> return 0" line needs a2 !=
 * UNIT_TYPE_PEASANT, which unavoidably reads that out-of-bounds tech
 * byte first. Best-effort/TOUCH only (not asserting the return value,
 * since the tech-level gate might return 0 earlier via that
 * unpredictable byte instead of via the smiths branch we're targeting);
 * harmless either way and cannot regress existing coverage. */
TEST(cov2_06_building, is_unit_licence_eligible_smiths_required_attempt) {
  static unsigned char buf[512];
  memset(buf, 0, sizeof buf);
  buf[4] = 1;   /* OtherModes tech-level table */
  buf[444] = 7; /* max in-range tech level byte */
  buf[416] = 0; /* smiths-required block not bypassed */

  TOUCH(
      Building_IsUnitLicenceEligible((char *)buf, UNIT_TYPE_HEAVY_INFANTRY));
}

/* ---------------------------------------------------------------------
 * Rules_ClearFocusStackCommand (97857-97865): 4/5 covered by cov11's
 * "empty argument list" setup (Lexer_TokenExpect(0) against an empty
 * chain). Exercise the complementary shape: a *nonempty* chain (count 1)
 * against the requested count 0, which -- for whichever way the
 * function's own lost-register branch resolves that isn't the lucky
 * exact-match case -- is a plausible way to reach the "return result;"
 * fallback via a different internal path than cov11's. Isolated/TOUCH:
 * best-effort, harmless either way. */
TEST(cov2_06_rules, clear_focus_stack_command_nonempty_chain) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  int saved_ctx = g_ClipsCurrentExpression;

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Rules_ClearFocusStackCommand());

  g_ClipsCurrentExpression = saved_ctx;
}

/* ---------------------------------------------------------------------
 * CRT_MakeDirectory (106305-106311): 3/4 covered by cov12 (a real mkdir
 * success case). Exercise the failure branch explicitly with a path
 * whose parent does not exist, so CreateDirectoryA fails and
 * _set_errno_nt_ is reached. */
TEST(cov2_06_crt, make_directory_failure_path) {
  TOUCH(CRT_MakeDirectory("/cov2_06/nonexistent/parent/dir", 0));
}

/* ---------------------------------------------------------------------
 * Rules_BsaveCommand (118079-118097): 4/8 covered. With a fake one-node
 * STRING-typed argument (Lexer_TokenExpect(1) needs count == 1, whichever
 * way its own lost-register branch resolves), attempt to reach
 * Rules_GetFileNameArg / Rules_PerformBsave. Best-effort/isolated: even
 * if Lexer_TokenExpect's branch resolves unfavorably, this exercises the
 * same lines already covered without regressing anything; if it resolves
 * favorably it reaches further (Rules_GetFileNameArg's own Rules_RtnUnknown
 * walk against our node, then Rules_PerformBsave against a real path). */
TEST(cov2_06_rules, bsave_command_one_string_arg_attempt) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  static unsigned char string_value_node[32];
  static char path_buf[] = "cov2_06_bsave_out.tmp";
  int saved_ctx;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  saved_ctx = g_ClipsCurrentExpression;

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  memset(string_value_node, 0, sizeof string_value_node);

  *(_DWORD *)(string_value_node + 16) = (_DWORD)(intptr_t)path_buf;
  *(short *)(expr_node + 0) = 3; /* STRING type tag */
  *(_DWORD *)(expr_node + 2) = (_DWORD)(intptr_t)string_value_node;
  *(_DWORD *)(expr_node + 10) = 0;
  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Rules_BsaveCommand(0, 0.0));

  g_ClipsCurrentExpression = saved_ctx;
  remove("cov2_06_bsave_out.tmp");
}

/* ---------------------------------------------------------------------
 * Class_ClassSubclassesCommand / Class_ClassSuperclassesCommand
 * (173537-173565): 3/6 and 3/7 covered by cov13/cov22's plain calls
 * (which reach the "v2 == 0 -> Rules_SetMultifieldErrorValue" branch and
 * bank its call-initiation line before the callee's own known
 * decompiler-lost-pointer bug crashes). The complementary "v2 != 0"
 * branch requires Class_LookupByQualifiedName to actually find a real
 * class, which walks a hash bucket chain via a decompiler-lost
 * comparison register (`v6` in Class_LookupByQualifiedName) against an
 * empty-by-default class table -- not practically reachable in this
 * harness (see test_cov22.c's own "empty class hash table by default"
 * note). Re-exercise both with a different `a1`/`a2` pair purely for
 * additional redundancy/robustness; no new branch is expected, but this
 * costs nothing and cannot regress existing coverage. */
TEST(cov2_06_class, subclasses_and_superclasses_commands_redundant) {
  static unsigned char arg_list_head[32];
  static unsigned char expr_node[32];
  int saved_ctx = g_ClipsCurrentExpression;

  memset(arg_list_head, 0, sizeof arg_list_head);
  memset(expr_node, 0, sizeof expr_node);
  *(_DWORD *)(arg_list_head + 6) = (_DWORD)(intptr_t)expr_node;
  g_ClipsCurrentExpression = (int)(intptr_t)arg_list_head;

  TOUCH(Class_ClassSubclassesCommand(2, 2.0));
  TOUCH(Class_ClassSuperclassesCommand(2, 2.0));

  g_ClipsCurrentExpression = saved_ctx;
}

/* ---------------------------------------------------------------------
 * Timer_BusyWaitWithCallback (36273-36291): 7/9 covered by cov03's two
 * tests (immediate-deadline/no-callback, and small-deadline/with-
 * callback). Add a null-callback variant with a real (small but nonzero)
 * deadline delta so the loop spins through the "if (callback)" check
 * multiple times while it stays false, a shape neither existing test
 * exercises (the no-callback test uses a zero deadline delta that likely
 * exits on the very first iteration). */
TEST(cov2_06_timer, busy_wait_null_callback_with_real_spin) {
  TOUCH(Timer_BusyWaitWithCallback(2000, 0, 0));
}

/* ---------------------------------------------------------------------
 * Instance_ModifyInstanceFunction (136470-136479): 3/4 covered by cov18's
 * plain call. The remaining line (the final
 * `return Rules_SetObjectPatternMatchDelay(v3, v2);`) sits after a call
 * to Instance_ActiveModifyInstanceFunction fed entirely
 * decompiler-undefined locals, so reaching it is not reliably
 * controllable from here; re-exercise anyway (harmless, isolated) in
 * case the runtime resolves favorably on a different call-site stack
 * layout than cov18's. */
TEST(cov2_06_instance, modify_instance_function_retry) {
  TOUCH(Instance_ModifyInstanceFunction(1.0));
}

/* ---------------------------------------------------------------------
 * Class_RegisterBinaryItem (159197-159210): 2/3 covered by cov20's plain
 * (non-bootstrapped) call. Rules_AddAbortBloadFunction and
 * Rules_RegisterBinaryItem both allocate off the reserve-block arena
 * rooted at dword_54DBA8, which is NULL without Mem_InitReserveBlock --
 * bootstrapping first likely lets the second call (the tail-call
 * `return Rules_RegisterBinaryItem(...)`) complete instead of faulting
 * on a NULL arena partway through the first call. */
TEST(cov2_06_class, register_binary_item_bootstrapped) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Class_RegisterBinaryItem());
}
