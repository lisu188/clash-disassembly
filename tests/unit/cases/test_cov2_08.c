/* cov2 batch 08: second-pass coverage top-ups for a mixed cluster of Rules
 * engine helpers (CLIPS-style host functions, multifield range editors,
 * agenda/module bookkeeping, math builtins), plus a handful of CRT/UI/
 * dribble-router and unit-sprite-path leaves. See cov2_batches/cov2_08.json.
 *
 * Shared background (documented at length in tests/unit/cases/test_cov16.c,
 * reused here): pointer-typed arguments that the recovered 32-bit code
 * stores into an `int`/`_DWORD` field and later reads back as a pointer MUST
 * be backed by `static` (or global) storage -- this is a 64-bit -no-pie
 * build, so a stack address's high bits get silently truncated away, but
 * static/global data lives in the low sub-4GB image and round-trips intact.
 * True native pointer-typed parameters (declared `const char *`, `int *`,
 * etc. in the recovered signature) do NOT have this problem -- they are
 * full 64-bit pointers within this recompiled TU -- so plain locals /
 * string literals are fine for those.
 *
 * Also shared: the rules-engine argument-parsing primitives
 * (Lexer_ParseValueList / Rules_RtnUnknown / Parser_ParseForm) read a
 * "current argument list" rooted at dword_51A960. Rules_RtnArgCount and
 * Rules_RtnUnknown's chain walk only need each argument node's byte-offset
 * +10 "next" pointer; Parser_ParseForm's simple-constant path (form types
 * 0 FLOAT / 1 INTEGER / 2 SYMBOL / ...) just copies byte-offset +2 (a
 * payload pointer) into the caller's out-param and marks its type -- no
 * lexer/token-stream needed. This lets a few of the tests below construct a
 * single real "already-parsed" argument node and drive
 * Lexer_ParseValueList to a genuine success return, instead of always
 * hitting the (already well covered) "no argument supplied" failure path. */

static void cov2_08_setup_one_arg(unsigned char *ctx, unsigned char *formnode,
                                   unsigned char *valnode, int form_type,
                                   const void *value_bits, size_t value_size) {
  memset(ctx, 0, 64);
  memset(formnode, 0, 64);
  memset(valnode, 0, 64);
  *(int16_t *)(formnode + 0) = (int16_t)form_type;
  *(uint32_t *)(formnode + 2) = (uint32_t)(uintptr_t)valnode;
  *(uint32_t *)(formnode + 10) = 0; /* single-argument chain */
  memcpy(valnode + 16, value_bits, value_size);
  *(uint32_t *)(ctx + 6) = (uint32_t)(uintptr_t)formnode;
  dword_51A960 = (int)(intptr_t)ctx;
}

/* ---- Rules_MultifieldInsertRange: two remaining gaps not exercised by
 * test_cov16.c's already-thorough sweep (guard-reject, a2==NULL scalar/
 * multifield, a2-present scalar/multifield "tail copy" success paths):
 * (1) the "copy existing head elements before the insertion point" loop
 * (only entered when the insertion index leaves at least one pre-existing
 * element strictly before it), and (2) the a3[1]==4 (multifield insert
 * value) branch when the inserted multifield's own range is empty
 * (a3[3] > a3[4]), which skips its inner do-while entirely. */
TEST(cov2_08_insertrange, head_copy_loop_then_tail_copy) {
  static _DWORD storage[64];
  static _DWORD a1buf[8], a2buf[8], a3buf[8];
  memset(storage, 0, sizeof storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);

  *(short *)((char *)storage + 6 * 0 + 14) = 2;
  *(int *)((char *)storage + 6 * 0 + 16) = 10;
  *(short *)((char *)storage + 6 * 1 + 14) = 2;
  *(int *)((char *)storage + 6 * 1 + 16) = 20;
  *(short *)((char *)storage + 6 * 2 + 14) = 2;
  *(int *)((char *)storage + 6 * 2 + 16) = 30;
  *(short *)((char *)storage + 6 * 3 + 14) = 2;
  *(int *)((char *)storage + 6 * 3 + 16) = 40;
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0; /* begin */
  a2buf[4] = 3; /* end -> count 4 */
  a3buf[1] = 2; /* scalar insert value, type != 4 */
  a3buf[2] = 555;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  /* insert at position 3 -> two pre-existing elements copied ahead of the
   * insertion point first (the previously-uncovered head-copy loop). */
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, a2buf, a3buf, 3, 0), 1);
}

TEST(cov2_08_insertrange, multifield_insert_value_with_empty_range) {
  static _DWORD storage[64];
  static _DWORD a1buf[8], a2buf[8], a3buf[8];
  memset(storage, 0, sizeof storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);

  *(short *)((char *)storage + 6 * 0 + 14) = 2;
  *(int *)((char *)storage + 6 * 0 + 16) = 1;
  *(short *)((char *)storage + 6 * 1 + 14) = 2;
  *(int *)((char *)storage + 6 * 1 + 16) = 2;
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0;
  a2buf[4] = 1; /* count 2 */

  a3buf[1] = 4;   /* multifield insert value ... */
  a3buf[3] = 1;   /* ... but begin (1) > end (0), so its do-while body is */
  a3buf[4] = 0;   /* skipped -- keeps the allocation size (a3[4]-a3[3]+1+v8) non-negative */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, a2buf, a3buf, 1, 0), 1);
}

/* ---- Rules_MVDeleteFunction: test_cov16.c already exercises the "no
 * argument supplied" failure at the *first* Lexer_ParseValueList call. This
 * makes that first call actually succeed (a genuine INTEGER-vs-FLOAT type
 * coercion inside Lexer_ParseValueList's tail: `a2[1]==0 && a3==1` hard-
 * codes `return 1`, no decompiler-lost-variable ambiguity involved), which
 * newly exercises the short-circuited *second* Lexer_ParseValueList call
 * line (a3==4, MULTIFIELD) -- itself guaranteed to fail (no success branch
 * exists for a3==4 other than an unreachable decompiler-lost comparison),
 * routing into Rules_RtnUnknown's "not found" arg-error path and crashing
 * one frame down (same known-buggy null dereference documented in
 * test_cov16.c) -- but only after this function's own call-site line for
 * the second parse has already executed, banking that previously-
 * unreachable line. Isolated in its own TEST. */
TEST(cov2_08_mvdelete, first_arg_parses_second_call_now_reached) {
  static unsigned char ctx[64], formnode[64], valnode[64];
  static _DWORD out[8];
  double v = 3.5;
  memset(out, 0, sizeof out);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov2_08_setup_one_arg(ctx, formnode, valnode, 0 /* FLOAT */, &v, sizeof v);
  TOUCH(Rules_MVDeleteFunction(out, 3, 0.0));
}

/* ---- Rules_SubseqFunction: same shape as Rules_MVDeleteFunction above, but
 * its *first* Lexer_ParseValueList call requests a3==4 (MULTIFIELD)
 * directly, which -- as established above -- has no reachable success
 * branch at all via the constant-form fast path. So this stays on the
 * already-covered "first call fails" shape; recorded here only to keep this
 * function's cold-call safety net alongside its sibling above (isolated so
 * a crash one frame down in the shared Rules_SetMultifieldErrorValue bug
 * cannot affect other tests). */
TEST(cov2_08_subseq, no_args_first_call_fails) {
  static _DWORD out[8];
  int saved960 = dword_51A960;
  memset(out, 0, sizeof out);
  dword_51A960 = 0;
  TOUCH(Rules_SubseqFunction(out, 0.0));
  dword_51A960 = saved960;
}

/* ---- Rules_ReorderAgenda: `result` truthy takes the outer if directly
 * (skipping the Module_NextEnum(0) probe); `result` falsy with no defrule
 * modules defined makes Module_NextEnum(0) return 0 too, skipping the whole
 * do-while. Both shapes are cheap and safe to call; the do-while body
 * itself additionally requires a real per-module activation list from
 * Rules_GetDefruleModuleItem, which is exercised indirectly through the
 * nonzero-result call once the reserve arena exists. */
TEST(cov2_08_reorderagenda, zero_result_no_modules) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ReorderAgenda(0));
}

TEST(cov2_08_reorderagenda, nonzero_result_enters_loop) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ReorderAgenda(1));
}

/* ---- Rules_ConstructCodeFileOpen: exercise the a10==0 (positional) vs
 * a10!=0 (already-resolved-name) argument-shape branches, both the
 * top-level a1!=0 shortcut and the a1==0 "actually open the file" path, and
 * -- when the open call reports success -- both the a10!=0 and a10==0
 * (sprintf_ naming + two Output_WriteFormatted calls) success sub-shapes.
 * a2/a4/a9 are genuine native `const char *` parameters (no truncation
 * concern); a5/a11 likewise genuine native pointers, backed by statics only
 * for tidiness. */
TEST(cov2_08_ccfopen, top_level_shortcut_a1_truthy) {
  static int a5val;
  static const char *a11arr[4];
  a5val = 0;
  memset(a11arr, 0, sizeof a11arr);
  CHECK_EQ(Rules_ConstructCodeFileOpen(77, "foo", 1, "bar", &a5val, 9, 8, 'X',
                                        "pfx_", 0, a11arr),
           77);
}

TEST(cov2_08_ccfopen, a10_zero_positional_args_with_a11) {
  static int a5val;
  static const char *a11arr[4];
  a5val = 0;
  memset(a11arr, 0, sizeof a11arr);
  TOUCH(Rules_ConstructCodeFileOpen(0, "foo", 1, "bar", &a5val, 9, 8, 'X',
                                     "pfx_", 0, a11arr));
}

TEST(cov2_08_ccfopen, a10_nonzero_resolved_name_with_a11) {
  static int a5val;
  static const char *a11arr[4];
  a5val = 0;
  a11arr[0] = "AA";
  a11arr[1] = "BB";
  a11arr[2] = "CC";
  TOUCH(Rules_ConstructCodeFileOpen(0, "foo", 1, "bar", &a5val, 9, 8, 'X',
                                     "pfx_", 1, a11arr));
}

/* a10!=0 with a11==NULL: reports a system error and unwinds via
 * IO_RunRouterExitCallbacks (documented in the shared cov2 instructions as
 * safe to call now -- the forked-child isolation absorbs the exit/abort). */
TEST(cov2_08_ccfopen, a10_nonzero_null_a11_reports_error) {
  static int a5val;
  a5val = 0;
  TOUCH(Rules_ConstructCodeFileOpen(0, "foo", 1, "bar", &a5val, 9, 8, 'X',
                                     "pfx_", 1, 0));
}

/* ---- Rules_ParseDefruleRHS: Parser_ParseProgram's second argument is an
 * uninitialized local in the recovered caller (a decompiler-lost variable),
 * so this cold call is expected to behave unpredictably a frame down;
 * isolated in its own TEST so whichever outcome occurs cannot affect other
 * tests, while still banking this function's own leading
 * IO_OutWriteToken/Rules_SetIndentDepth/Parser_ParseProgram call-site
 * lines. */
TEST(cov2_08_parsedefrulerhs, cold_call) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ParseDefruleRHS(0));
}

/* ---- Rules_MarkConstraintAttributeParsed: a light top-up alongside
 * test_cov23.c's already-exhaustive sweep over every known keyword plus one
 * unmatched name (which walks every strcmp_ branch in the chain both ways).
 * Repeated here on a freshly-zeroed flags byte in case any residual gap
 * remains from a stale coverage snapshot. */
TEST(cov2_08_markconstraint, sweep_all_keywords_again) {
  _BYTE a1buf[8];
  memset(a1buf, 0, sizeof a1buf);
  TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aRange_0));
  memset(a1buf, 0, sizeof a1buf);
  TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedValues));
  memset(a1buf, 0, sizeof a1buf);
  TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t) "nope"));
}

/* ---- CRT_TzYearStartsInDaylightTime: drive all three structurally distinct
 * shapes -- (1) a1[8]!=0 jumps straight to the shared LABEL_6 tail without
 * ever comparing a1[4]/a2+16; (2) a1[4] > *(a2+16) returns 1 immediately,
 * never reaching LABEL_6; (3) a1[4] < *(a2+16) skips LABEL_6 too, falling
 * straight through to the final `return 0;` (the only way to reach that
 * line without executing the CRT_TzRuleDayOfYear comparison at all). */
TEST(cov2_08_tzdaylight, a1_flag_set_jumps_to_shared_tail) {
  static _DWORD a1buf[16], a2buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  a1buf[8] = 1;
  TOUCH(CRT_TzYearStartsInDaylightTime(a1buf, (int)(intptr_t)a2buf, 0));
}

TEST(cov2_08_tzdaylight, v3_greater_returns_one_immediately) {
  static _DWORD a1buf[16], a2buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  a1buf[4] = 100;
  a2buf[4] = 5; /* *(a2+16) */
  CHECK_EQ(CRT_TzYearStartsInDaylightTime(a1buf, (int)(intptr_t)a2buf, 0), 1);
}

TEST(cov2_08_tzdaylight, v3_less_falls_through_to_plain_return_zero) {
  static _DWORD a1buf[16], a2buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  a1buf[4] = 3;
  a2buf[4] = 100;
  CHECK_EQ(CRT_TzYearStartsInDaylightTime(a1buf, (int)(intptr_t)a2buf, 0), 0);
}

/* ---- Rules_MathLog / Rules_MathSech: Rules_MathParseSingleArg hard-codes
 * requesting a FLOAT (type 0) value from Lexer_ParseValueList. Supplying a
 * real INTEGER-typed constant argument node (via cov2_08_setup_one_arg)
 * takes Lexer_ParseValueList's `a2[1]==1 && !a3` INTEGER-to-FLOAT coercion
 * branch, which converts the supplied integer into the double these Math
 * functions then inspect -- exercising the positive/negative/zero branches
 * that a "no argument supplied" cold call can never reach. */
TEST(cov2_08_mathlog, positive_value_takes_log_branch) {
  static unsigned char ctx[64], formnode[64], valnode[64];
  int v = 5;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov2_08_setup_one_arg(ctx, formnode, valnode, 1 /* INTEGER */, &v, sizeof v);
  TOUCH(Rules_MathLog(1, 2, 3, 0.0));
}

TEST(cov2_08_mathlog, negative_value_takes_domain_error_branch) {
  static unsigned char ctx[64], formnode[64], valnode[64];
  int v = -7;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov2_08_setup_one_arg(ctx, formnode, valnode, 1 /* INTEGER */, &v, sizeof v);
  TOUCH(Rules_MathLog(1, 2, 3, 0.0));
}

TEST(cov2_08_mathlog, zero_value_takes_overflow_error_branch) {
  static unsigned char ctx[64], formnode[64], valnode[64];
  int v = 0;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov2_08_setup_one_arg(ctx, formnode, valnode, 1 /* INTEGER */, &v, sizeof v);
  TOUCH(Rules_MathLog(1, 2, 3, 0.0));
}

TEST(cov2_08_mathsech, value_via_int_arg_takes_success_branch) {
  static unsigned char ctx[64], formnode[64], valnode[64];
  int v = 2;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov2_08_setup_one_arg(ctx, formnode, valnode, 1 /* INTEGER */, &v, sizeof v);
  TOUCH(Rules_MathSech(1, 2, 3, 0.0));
}

/* ---- Rules_PlaceInBreadthList: pure linked-list walk over caller-owned
 * nodes; drives the "key greater -> return current" early-out, the
 * "advance to next node" branch, the "tie on key but v3 fits -> break"
 * branch, and the "tie on key but v3 doesn't fit -> keep advancing" branch,
 * all with no engine bootstrap required. */
TEST(cov2_08_breadthlist, advance_then_return_on_greater_key) {
  static _DWORD node0[8], node1[8], a2buf[8];
  memset(node0, 0, sizeof node0);
  memset(node1, 0, sizeof node1);
  memset(a2buf, 0, sizeof a2buf);
  node0[2] = 10; /* key */
  node0[7] = (_DWORD)(intptr_t)node1;
  node1[2] = 3; /* key */
  a2buf[2] = 5; /* v2 */
  a2buf[3] = 0; /* v3 */
  CHECK_EQ(Rules_PlaceInBreadthList(node0, (int)(intptr_t)a2buf), (_DWORD)(intptr_t)node0);
}

TEST(cov2_08_breadthlist, tie_on_key_breaks_immediately) {
  static _DWORD node0[8], a2buf[8];
  memset(node0, 0, sizeof node0);
  memset(a2buf, 0, sizeof a2buf);
  node0[2] = 5;  /* key */
  node0[3] = 2;  /* v3 field */
  a2buf[2] = 5;  /* v2 */
  a2buf[3] = 2;  /* v3 */
  CHECK_EQ(Rules_PlaceInBreadthList(node0, (int)(intptr_t)a2buf), 0);
}

TEST(cov2_08_breadthlist, tie_on_key_keeps_advancing_to_null) {
  static _DWORD node0[8], a2buf[8];
  memset(node0, 0, sizeof node0);
  memset(a2buf, 0, sizeof a2buf);
  node0[2] = 5; /* key */
  node0[3] = 1; /* v3 field, smaller than a2's v3 -> don't break */
  node0[7] = 0; /* next -> NULL */
  a2buf[2] = 5; /* v2 */
  a2buf[3] = 5; /* v3 */
  CHECK_EQ(Rules_PlaceInBreadthList(node0, (int)(intptr_t)a2buf), (_DWORD)(intptr_t)node0);
}

/* ---- MessageHandler_RegisterSystemHandlers / Rules_RegisterAllHostFunctions
 * / Rules_RegisterModifyDuplicateFunctions / Rules_ResetEngineOnLoad:
 * straight-line registration/bring-up sequences that only need the reserve
 * arena and atom tables carved out first (same one-time bootstrap used
 * throughout tests/unit/cases/test_cov16.c and test_cov17.c). */
TEST(cov2_08_register, message_handler_register_system_handlers) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(MessageHandler_RegisterSystemHandlers());
}

TEST(cov2_08_register, rules_register_all_host_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterAllHostFunctions());
}

TEST(cov2_08_register, rules_register_modify_duplicate_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterModifyDuplicateFunctions());
}

TEST(cov2_08_register, rules_reset_engine_on_load) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ResetEngineOnLoad());
}

/* ---- Method_PrintWatchStatusLine: straight-line output sequence ending in
 * a trace-flag if/else; called twice with different generic-method-shaped
 * buffers to probe both sides of that final branch (best effort -- the
 * decompiler-lost `v3` feeding Defgeneric_GetMethodTraceFlag's internal
 * lookup is not something we can pin down exactly, but with no output
 * router registered Output_Write no-ops safely either way, matching the
 * documented-safe pattern in test_cov10.c). */
TEST(cov2_08_watchline, trace_flag_zeroed_buffer) {
  static _DWORD gm[64];
  memset(gm, 0, sizeof gm);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Method_PrintWatchStatusLine(0, (int)(intptr_t)gm, 0));
}

TEST(cov2_08_watchline, trace_flag_nonzero_buffer) {
  static _DWORD gm[64];
  memset(gm, 0xFF, sizeof gm);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Method_PrintWatchStatusLine(0, (int)(intptr_t)gm, 0));
}

/* ---- CRT_RemoveUnhandledExceptionFilter: g_CrtThreadDataAccessor defaults
 * to a safe bootstrap accessor (documented in test_cov22.c), so a cold call
 * with arbitrary ints is safe and exercises whichever way the internal
 * exception-filter-pointer branch happens to fall. */
TEST(cov2_08_crtexcfilter, cold_call) {
  TOUCH(CRT_RemoveUnhandledExceptionFilter(1, 2));
}

/* ---- CRT_IsExtendedMbcsLeadByte: intentionally NOT exercised. It
 * references `ismbclegal_`, which has no definition anywhere in this port
 * (confirmed in test_cov23.c's own header comment via a link probe) --
 * calling it pulls an unresolved symbol into the link and breaks the whole
 * coverage binary, not just this one test. Left uncovered on purpose. */

/* ---- Rules_ClearActivationsForModule: the decompiler lost the loop's
 * "next" variable (`v1`), so once the do-while body runs once it may loop
 * indefinitely on stale register contents; the per-test alarm(8) watchdog
 * bounds that, and the first iteration's lines are banked regardless. */
TEST(cov2_08_clearactivations, cold_call) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ClearActivationsForModule());
}

/* ---- Dribble_GetcRouter: takes no arguments, so there is nothing a caller
 * can vary -- its several decompiler-lost locals are fixed by whatever the
 * real machine code leaves in those registers. A single cold call is all
 * that is possible here; it either progresses further than before or it
 * doesn't, but it cannot regress anything else since the child is
 * isolated. */
TEST(cov2_08_dribblerouter, cold_call) {
  TOUCH(Dribble_GetcRouter());
}

/* ---- Rules_MVDeleteFunction's sibling Rules_ReplaceFunction-style helpers
 * are out of this batch; ---- Rules_SetInheritedFlagBit4: walk a short
 * "class"-style linked list (next pointer at byte offset 48), exercising
 * both the zero-iteration (a2==0) and multi-iteration shapes. */
TEST(cov2_08_inheritflag, zero_iterations) {
  CHECK_EQ(Rules_SetInheritedFlagBit4(1, 0), 0);
}

TEST(cov2_08_inheritflag, two_node_chain) {
  static unsigned char node0[64], node1[64];
  memset(node0, 0, sizeof node0);
  memset(node1, 0, sizeof node1);
  *(uint32_t *)(node0 + 48) = (uint32_t)(uintptr_t)node1;
  *(uint32_t *)(node1 + 48) = 0;
  TOUCH(Rules_SetInheritedFlagBit4(1, (int)(intptr_t)node0));
}

/* ---- Unit_BuildGarrisonSlotIconSpritePath: nearly fully covered already;
 * probe a different resource-key index to try to close the last gap in the
 * final copy loop. */
TEST(cov2_08_garrisonicon, alternate_index) {
  static char out[256];
  memset(out, 0, sizeof out);
  TOUCH(Unit_BuildGarrisonSlotIconSpritePath(out, 3, 0));
}

/* ---- Tooltip_RestoreIfTextMatches: strcmp_ against the caller-supplied
 * text; drive both the "match" (calls Tooltip_RestoreBackdrop) and
 * "mismatch" (returns strcmp_'s nonzero result directly) branches. */
TEST(cov2_08_tooltipmatch, matching_text) {
  static char text[16];
  memset(text, 0, sizeof text);
  strcpy(text, "same");
  /* On a match this returns Tooltip_RestoreBackdrop()'s value (a rendering
   * call, not a fixed constant), so just touch it for coverage rather than
   * asserting a specific result. */
  TOUCH(Tooltip_RestoreIfTextMatches((int)(intptr_t)text, (int)(intptr_t)text));
}

TEST(cov2_08_tooltipmatch, mismatching_text) {
  static char a[16], b[16];
  memset(a, 0, sizeof a);
  memset(b, 0, sizeof b);
  strcpy(a, "aaa");
  strcpy(b, "bbb");
  TOUCH(Tooltip_RestoreIfTextMatches((int)(intptr_t)a, (int)(intptr_t)b));
}

/* ---- Rules_SyncArmyFactStrength: best-effort cold call. Reaching its
 * internal "fact strength changed" branch would require a fully bootstrapped
 * unit-stack/castle-fact engine state that is out of scope for a unit test;
 * this at minimum re-exercises the function with the reserve arena present
 * (unlike an entirely cold call) so whichever branch Rules_EnsureArmyFactForStack
 * happens to take with a zeroed stack record is banked. */
TEST(cov2_08_syncarmyfact, cold_call_zeroed_stack) {
  static unsigned char stack_record[1024];
  memset(stack_record, 0, sizeof stack_record);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_SyncArmyFactStrength((__int16 *)(intptr_t)stack_record, 0, 0, 0,
                                    0, 0.0));
}

/* ---- Rules_GetFocusStackFunction: Lexer_TokenExpect(0) succeeds (returns
 * 0, matching the requested count) when the current argument chain is
 * empty (dword_51A960 left at its all-zero default), taking the
 * Rules_BuildFocusStackList call branch; it fails (-1) when the chain has
 * at least one node while 0 arguments were requested, which
 * Rules_RtnArgCount can determine purely by walking "next" pointers (no
 * Parser_ParseForm/value validation needed), taking the direct
 * `return result;` branch instead. */
TEST(cov2_08_focusstack, empty_chain_takes_success_path) {
  int saved960 = dword_51A960;
  dword_51A960 = 0;
  TOUCH(Rules_GetFocusStackFunction());
  dword_51A960 = saved960;
}

TEST(cov2_08_focusstack, nonempty_chain_mismatch_returns_error) {
  static unsigned char ctx[64], node[64];
  int saved960 = dword_51A960;
  memset(ctx, 0, sizeof ctx);
  memset(node, 0, sizeof node);
  *(uint32_t *)(node + 10) = 0; /* single-node chain -> RtnArgCount() == 1 */
  *(uint32_t *)(ctx + 6) = (uint32_t)(uintptr_t)node;
  dword_51A960 = (int)(intptr_t)ctx;
  /* Expected to return -1 (count/request mismatch), but Lexer_TokenExpect's
   * own decompiler-lost comparison mode could in principle take a different
   * branch, so just touch it rather than hard-asserting the exact value. */
  TOUCH(Rules_GetFocusStackFunction());
  dword_51A960 = saved960;
}

/* ---- Rules_FindLogicalDependencyEntry: the count field is packed into
 * v3[0] via `(*v3 << 17) >> 23` (arithmetic shift); `count << 6` recovers
 * the raw word needed to make that expression evaluate back to `count`.
 * Drive the "immediate match, count reached" success path and the
 * "mismatch at the very first slot, no next node" not-found path. */
TEST(cov2_08_finddepentry, match_within_first_node) {
  static _DWORD a1buf[8];
  static _DWORD node[8];
  memset(a1buf, 0, sizeof a1buf);
  memset(node, 0, sizeof node);
  node[0] = 2 << 6; /* count == 2 */
  node[2] = 0xAAAA; /* slot 0 key */
  node[1 + 2] = 0xBBBB; /* slot 1 key (node+4 elements -> index 3) */
  node[1] = 0; /* no next node */
  a1buf[2] = (_DWORD)(intptr_t)node; /* a1+8 */
  {
    static _DWORD keys[8];
    keys[2] = 0xAAAA; /* *(a2+8) for i=0 */
    keys[1 + 2] = 0xBBBB; /* *(a2+4+8) for i=1 */
    CHECK_EQ(Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf,
                                               (int)(intptr_t)keys),
             (_DWORD)(intptr_t)node);
  }
}

TEST(cov2_08_finddepentry, mismatch_first_slot_no_next_returns_zero) {
  static _DWORD a1buf[8];
  static _DWORD node[8];
  static _DWORD keys[8];
  memset(a1buf, 0, sizeof a1buf);
  memset(node, 0, sizeof node);
  memset(keys, 0, sizeof keys);
  node[0] = 1 << 6; /* count == 1 */
  node[2] = 0x1111;
  node[1] = 0; /* no next node */
  a1buf[2] = (_DWORD)(intptr_t)node;
  keys[2] = 0x2222; /* mismatches node[2] */
  CHECK_EQ(Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf,
                                             (int)(intptr_t)keys),
           0);
}

/* ---- Instance_DuplicateInstanceFunction: no branches, just a straight-line
 * chain of two Rules_SetObjectPatternMatchDelay calls around
 * Instance_ActiveDuplicateInstanceFunction; a single bootstrapped call
 * exercises every line. */
TEST(cov2_08_dupinstance, cold_call) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Instance_DuplicateInstanceFunction(0.0));
}

/* ---- Rules_IsClassBitmapEmpty: the outer "v2 == 0 immediately" guard is
 * unreachable for any real 16-bit `*a1` (max value still leaves v2 in
 * [1, 8192]), but the *inner* copy of the same check (reached once the
 * scan loop's decrementing v2 counter itself reaches 0) is reachable when
 * every scanned byte is zero all the way down. Drive that, plus the
 * "encounters a nonzero byte first" early-return-0 branch. */
TEST(cov2_08_classbitmap, all_zero_bytes_reaches_v2_zero) {
  static unsigned __int16 bitmap[8];
  memset(bitmap, 0, sizeof bitmap);
  bitmap[0] = 8; /* v2 starts at (8>>3)+1 == 2 */
  CHECK_EQ(Rules_IsClassBitmapEmpty(bitmap), 1);
}

TEST(cov2_08_classbitmap, nonzero_byte_returns_zero) {
  static unsigned __int16 bitmap[8];
  memset(bitmap, 0, sizeof bitmap);
  bitmap[0] = 8;
  ((unsigned char *)bitmap)[3] = 0xFF; /* v2==2 -> first probed byte is at (v2+1) == 3 */
  CHECK_EQ(Rules_IsClassBitmapEmpty(bitmap), 0);
}

/* ---- Rules_AssertCastleFact: five independent flag-bit if/else pairs each
 * pick between the aTak_ and aNie_ strings; a single call only ever banks one
 * side of each pair, so call once with every bit set and once with every
 * bit clear to cover all ten assignment lines. */
TEST(cov2_08_assertcastlefact, all_flags_set) {
  static unsigned char a1buf[600];
  memset(a1buf, 0, sizeof a1buf);
  a1buf[416] = 0x1F; /* bits 0,1,2,3,4 all set */
  TOUCH(Rules_AssertCastleFact(a1buf, 1));
}

TEST(cov2_08_assertcastlefact, all_flags_clear) {
  static unsigned char a1buf[600];
  memset(a1buf, 0, sizeof a1buf);
  a1buf[416] = 0;
  TOUCH(Rules_AssertCastleFact(a1buf, 2));
}

/* ---- Castle_InvokeEconomyPanel: a thin static wrapper around
 * BuildingEconomyDialog_Run; not previously called at all (0/2 covered).
 * BuildingEconomyDialog_Run may pump a modal message loop, in which case
 * the per-test alarm(8) watchdog bounds it -- either way the call-site line
 * is banked immediately. */
TEST(cov2_08_castleeconomy, cold_call) {
  static _DWORD building_record[128];
  memset(building_record, 0, sizeof building_record);
  TOUCH(Castle_InvokeEconomyPanel((int)(intptr_t)building_record, 0, 0));
}

/* ---- Compiler_CloseDefinstancesCodeFiles: two independent-looking ifs
 * that actually funnel into the same tail via a goto; drive all three
 * reachable shapes (a2==0/a1!=0, a2!=0/a1==0, a2!=0/a1!=0) so both the
 * `goto LABEL_5` merge and the plain `a2!=0` early return are hit. */
TEST(cov2_08_closedefinst, a2_zero_a1_nonzero) {
  TOUCH(Compiler_CloseDefinstancesCodeFiles(7, 0, 1, 2));
}

TEST(cov2_08_closedefinst, a2_nonzero_a1_zero) {
  TOUCH(Compiler_CloseDefinstancesCodeFiles(0, 5, 1, 2));
}

TEST(cov2_08_closedefinst, a2_nonzero_a1_nonzero_hits_goto_merge) {
  TOUCH(Compiler_CloseDefinstancesCodeFiles(7, 5, 1, 2));
}
