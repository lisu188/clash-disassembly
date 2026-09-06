/* cov4_05: final-pass coverage targeting the exact uncovered clash95.c lines
 * listed in cov4_batches/cov4_05.json. Every finding below was empirically
 * verified against a private scratch build of the exact same clash95.c (same
 * compiler/flags: -std=gnu89 -w -g -O0 --coverage -fno-pie
 * -ffunction-sections -fdata-sections, linked against platform_sdl_runtime.c
 * + compat/decomp_runtime_stubs.c), using gdb + gcov to confirm which lines
 * are actually reached before writing anything here. The shared build/
 * test_all.c were never run or edited for this verification.
 *
 * One function (Rules_PlaceInBreadthList) is an unconditional, register-
 * independent win. Two more (Rules_ParseLoadFactsCommand, Rules_BloadCommand)
 * gated on Lexer_TokenExpect()'s own decompiler-lost `v2` local -- verified
 * to reach their target lines in this private harness, but since that
 * outcome is a function of whatever garbage happens to sit in that stack
 * slot (which depends on the exact call history leading up to it), it may
 * differ in the real, much larger test_all.c TU; kept because the shape is
 * otherwise correct and this is the established pattern used elsewhere in
 * the suite (e.g. test_cov3_07.c's "leftover register luck" tests).
 *
 * The rest hit hard, reproducible ceilings -- documented with the exact
 * crash site or structural reason, matching the "known hard ceiling"
 * categories called out in the batch instructions (decompiler-lost register
 * dereferenced in a callee, or a call chain that depends on engine state
 * this harness never bootstraps). Each is still exercised once via TOUCH
 * (fork-isolated in the real suite, so harmless) in case the real harness's
 * stack/heap layout differs enough to get lucky. */

static void cov4_05_mk_arg_node(unsigned char *node, short type_tag,
                                 unsigned char *valbuf) {
  memset(node, 0, 64);
  memset(valbuf, 0, 64);
  *(short *)(node + 0) = type_tag;
  *(int *)(node + 2) = (int)(intptr_t)valbuf;
}

/* ==== Confirmed working (new coverage verified via private gcov) ==== */

/* ---- Rules_PlaceInBreadthList: a1==NULL is a trivial, unconditional
 * "return v4;" -- no gating at all. Confirmed hits line 96183. ---- */
TEST(cov4_05_rules, place_in_breadth_list_null_head) {
  static _DWORD a2buf[8];
  memset(a2buf, 0, sizeof a2buf);
  TOUCH(Rules_PlaceInBreadthList(0, (int)(intptr_t)a2buf));
}

/* ---- Rules_ParseLoadFactsCommand: NOTE dword_51A960 == 0 (a null "arg
 * chain") is NOT a safe way to reach the early return -- Rules_RtnArgCount
 * dereferences `dword_51A960 + 6` unconditionally, so a literal 0 there
 * SIGSEGVs immediately, before Lexer_TokenExpect can even return -1
 * (confirmed via gdb). A real one-node chain avoids that crash (a valid,
 * non-null dword_51A960); whether Lexer_TokenExpect(1) then succeeds or
 * takes the early "return 0;" (line 94402) at this call site depends on
 * Lexer_TokenExpect's own decompiler-lost `v2` local, which in turn depends
 * on the exact call history before this point -- verified both ways across
 * two otherwise-identical private-harness runs that differed only in an
 * earlier test's shape. When it does fail here (the common case observed),
 * this hits line 94402. When it instead succeeds, Rules_GetFileNameArg's
 * result reads back through a separately-named local (the same
 * "stale content" pattern documented for it in test_cov3_00.c) and comes
 * back falsy regardless of the node's type tag, so lines 94406-94408 stay
 * out of reach either way. ---- */
TEST(cov4_05_rules, parse_load_facts_command_early_return) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 0, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_ParseLoadFactsCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_BloadCommand: at this call site Lexer_TokenExpect(1) was
 * observed to succeed with a one-node arg chain (consistently, across
 * repeated private-harness runs), so Rules_GetFileNameArg actually runs.
 * Its result reads back through a separately-named local (same
 * "stale content" issue documented for Rules_GetFileNameArg in
 * test_cov3_00.c) and comes back falsy regardless of the node's type tag,
 * so `if (result)` is false. Confirmed via gcov: hits both line 95872 (the
 * if-check) and 95874 (the falsy "return result;"); line 95873 (needs
 * GetFileNameArg truthy) stays out of reach. ---- */
TEST(cov4_05_rules, bload_command_reaches_getfilenamearg) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 3, valbuf1); /* STRING type tag */
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_BloadCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ==== Confirmed hard ceilings (attempted, documented, harmless) ==== */

/* ---- Rules_RestFunction / Rules_NthFunction / Rules_FloatFunction /
 * Rules_CosBuiltin / Rules_MathExp / Rules_MathAcsch: all funnel into
 * Lexer_ParseValueList(), whose very first real check
 * (`a3 == *(_DWORD *)(v7 + 4) || ...` at clash95.c:99870) dereferences its
 * own decompiler-lost local `v7` *unconditionally*, before even looking at
 * a3. Confirmed via gdb: this reliably SIGSEGVs inside Lexer_ParseValueList
 * itself, so none of these callers' post-success lines are ever reached
 * (Rules_RestFunction 127775-127790, Rules_NthFunction 127809-127817,
 * Rules_FloatFunction 127017-127025, Rules_CosBuiltin 129504,
 * Rules_MathExp 129972, Rules_MathAcsch 129937-129940). This matches the
 * batch instructions' "known hard ceiling" (lines after a
 * Lexer_ParseValueList call). Attempted anyway per instructions (isolated,
 * harmless); a 40-iteration varied-stack-padding retry (private build) only
 * ever reached Lexer_ParseValueList on the very first call and crashed
 * there every time. ---- */
TEST(cov4_05_rules, rest_function_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  static _DWORD out[8];
  int saved;
  memset(head, 0, sizeof head);
  memset(out, 0, sizeof out);
  cov4_05_mk_arg_node(node1, 4, valbuf1); /* MULTIFIELD type tag -> a3==4 */
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_RestFunction(out, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_05_rules, nth_function_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char node2[64];
  static unsigned char valbuf1[64];
  static unsigned char valbuf2[64];
  static _DWORD out[8];
  int saved;
  memset(head, 0, sizeof head);
  memset(out, 0, sizeof out);
  cov4_05_mk_arg_node(node1, 1, valbuf1); /* INTEGER (index arg) */
  cov4_05_mk_arg_node(node2, 4, valbuf2); /* MULTIFIELD */
  *(int *)(node1 + 10) = (int)(intptr_t)node2;
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_NthFunction((int)(intptr_t)out, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_05_rules, float_function_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 1, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_FloatFunction(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_05_rules, cos_builtin_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 1, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_CosBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_05_rules, math_exp_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 1, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_MathExp(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_05_rules, math_acsch_success_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 1, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_MathAcsch(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_MarkConstraintAttributeParsed: every level past the first
 * strcmp_(a2, "Range") passes a decompiler-lost local (v4..v12) as the
 * compare argument, so hitting any of the 9 uncovered assignment lines
 * (179574/78/83/88/93/98/603/608/613) needs that garbage pointer to
 * coincidentally equal one of the attribute-name strings. A 200-iteration
 * varied-stack-padding sweep (private build, one call per attribute name
 * per iteration) never got lucky once. Attempted here too, isolated. ---- */
TEST(cov4_05_rules, mark_constraint_attribute_parsed_deep_chain) {
  static unsigned char attr[4];
  static char name[] = "AllowedValues";
  memset(attr, 0, sizeof attr);
  TOUCH(Rules_MarkConstraintAttributeParsed(attr, (int)(intptr_t)name));
}

/* ---- Rules_LoadStarCommand: Lexer_TokenExpect(1) deterministically fails
 * at *this* call site (unlike Rules_BloadCommand above -- the outcome is a
 * property of the caller's own stack-frame shape, not a global constant;
 * confirmed both ways via gdb), so the Rules_GetFileNameArg call and
 * everything after it (123207/208/210/214/215) is unreachable here. ---- */
TEST(cov4_05_rules, load_star_command_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  static char fname[] = "/nonexistent/cov4_05_loadstar_test.clp";
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 3, valbuf1);
  *(int *)(valbuf1 + 16) = (int)(intptr_t)fname;
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_LoadStarCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Defglobal_CloseConstructCodeFiles: reaching 165963/165964/165965
 * needs the nested Rules_ConstructCodeFileClose(a2, &v6, a4, v7, 0, 0) call
 * to actually return. For this call shape (a5 is always the literal 0),
 * that function unconditionally forwards its own "result" parameter into
 * Output_WriteFormatted(...) as the CRT_VfprintfLockedWrite stream handle,
 * which dereferences it as a real FILE*-like struct. test_cov09.c and
 * test_cov3_07.c already established (for the identical
 * Deffunction_CloseCodeFiles / Compiler_CloseDefinstancesCodeFiles callers)
 * that not even a fully zeroed, address-real backing buffer survives that
 * dereference -- confirmed here too via gdb (crashes inside
 * CRT_VfprintfLockedWrite before Rules_ConstructCodeFileClose can return).
 * Attempted both a1 branches anyway. ---- */
TEST(cov4_05_defglobal, close_construct_code_files_a1_zero) {
  static _DWORD fakeHandle[64];
  memset(fakeHandle, 0, sizeof fakeHandle);
  TOUCH(Defglobal_CloseConstructCodeFiles(0, (int)(intptr_t)fakeHandle, 0, 0));
}
TEST(cov4_05_defglobal, close_construct_code_files_a1_nonzero) {
  static _DWORD fakeHandle[64];
  memset(fakeHandle, 0, sizeof fakeHandle);
  TOUCH(Defglobal_CloseConstructCodeFiles((int)(intptr_t)fakeHandle,
                                           (int)(intptr_t)fakeHandle, 0, 0));
}

/* ---- WorldMap_HandleSaveGameAction: forwards into SaveSlotDialog_Run,
 * which (per test_cov01.c / test_cov3_00.c, and reconfirmed here via gdb)
 * reaches a missing-resource-file path that calls the __noreturn
 * App_RequestQuit() -> CRT_ExitProcessWithFinalizers(), terminating the
 * process (exit code 1, no signal) before returning -- so lines 19939/19940
 * are never reached regardless of arguments. Already attempted in
 * test_cov3_00.c; re-attempted here too since it's harmless either way. ---- */
TEST(cov4_05_worldmap, handle_save_game_action) {
  TOUCH(WorldMap_HandleSaveGameAction(0, 0, 0.0));
}

/* ---- Rules_AssertCastleFact: the sprintf'd fact string is really handed to
 * the live CLIPS assert/parse engine (Rules_AssertFact -> IO_OpenStringSource
 * -> Instance_FindByName -> Rules_FindModuleSeparator), which crashes on a
 * NULL argument several frames deep even after Mem_InitReserveBlock() +
 * Rules_InitAtomTables() bootstrap -- there's no deftemplate for "zamek"
 * registered, and standing one up is well beyond a two-line fixture. Lines
 * 70953/70954 (writing back Rules_AssertFact's result and calling
 * Building_OnGarrisonChange) never execute because Rules_AssertFact itself
 * never returns. ---- */
TEST(cov4_05_rules, assert_castle_fact_attempt) {
  static unsigned char castle[600];
  memset(castle, 0, sizeof castle);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_AssertCastleFact(castle, 1));
}

/* ---- Rules_FindImportExportConstruct: getting construct_record truthy
 * (via a synthetic dword_51A9BC module-list node) does reach the
 * Rules_SearchImportExportModules(...) call, but that function dereferences
 * a derived "current_module" pointer that isn't valid for our synthetic node
 * (confirmed via gdb: SIGSEGV at clash95.c:114755 inside
 * Rules_SearchImportExportModules, well before returning), so lines
 * 114690/114691 (Module_EndEnum + return result, after the call) are never
 * reached. Standing up a real module object is beyond this fixture's
 * scope. ---- */
TEST(cov4_05_rules, find_import_export_construct_attempt) {
  static char name[] = "Foo";
  static unsigned char a3buf[8];
  static _DWORD a2out[4];
  static unsigned char modnode[64];
  int saved;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a3buf, 0, sizeof a3buf);
  memset(a2out, 0, sizeof a2out);
  memset(modnode, 0, sizeof modnode);
  *(int *)(modnode + 0) = (int)(intptr_t)name; /* name ptr at offset 0 */
  *(int *)(modnode + 24) = 1;                  /* truthy flag at +24 */
  *(int *)(modnode + 28) = 0;                  /* next = NULL */
  saved = g_ModuleItemDescriptorListHead;
  g_ModuleItemDescriptorListHead = (int)(intptr_t)modnode;
  TOUCH(Rules_FindImportExportConstruct(name, a2out, a3buf, 0, 0));
  g_ModuleItemDescriptorListHead = saved;
}

/* ---- MessageHandler_PrintHandlerListTally: the a2==0 branch's for-loop
 * body (166366/166367) only runs while Class_GetNextRecord(0) keeps
 * returning truthy, i.e. only if at least one class is registered. Per
 * test_cov11.c ("the Class_GetNextRecord(0) enumeration loop, which is
 * empty by default"), there is no registered class without a full defclass
 * bootstrap, so Class_GetNextRecord(0) returns 0 immediately and the loop
 * body never executes. Attempted anyway. ---- */
TEST(cov4_05_messagehandler, print_handler_list_tally_a2_zero) {
  TOUCH(MessageHandler_PrintHandlerListTally(0, 0, 0, 0));
}

/* ---- Compat_RenderDeviceFillSolidRect: line 31154 (`if (!surface_pixels)
 * return 0;`, surface_pixels == surface[1]) is structurally unreachable.
 * The guard right above it only lets execution continue when
 * RenderSurface_IsLinearSoftware(surface) is true, and that helper's own
 * body (clash95.c:8930) returns false whenever `!surface[1]` -- so by the
 * time line 31154 runs, surface[1] is already guaranteed nonzero. Attempted
 * with a real-ish surface anyway in case some other g_RenderDevice shape
 * changes this. ---- */
TEST(cov4_05_compat, render_device_fill_solid_rect_null_pixels) {
  TOUCH(Compat_RenderDeviceFillSolidRect(0, 0, 1, 1, 0));
}

/* ---- WCIsvListBase_base_insert: line 56030
 * (`list->head_link = link_handle;` in the tail-lookup-failed else branch)
 * is structurally unreachable in this port. WCCompat_LinkFromHandle(x) is
 * just `(WCCompatLink *)(uintptr_t)(unsigned int)x` -- an identity
 * reinterpret-cast -- so it can only return NULL when x itself is 0, and
 * the surrounding `if (list->tail_link)` guard already guarantees
 * list->tail_link != 0 before WCCompat_LinkFromHandle(list->tail_link) is
 * even called. So `tail` can never be NULL there. Attempted anyway. ---- */
TEST(cov4_05_wcisv, base_insert_tail_present) {
  static unsigned char list[64];
  static unsigned char link1[64];
  static unsigned char link2[64];
  memset(list, 0, sizeof list);
  memset(link1, 0, sizeof link1);
  memset(link2, 0, sizeof link2);
  *(int *)(list + 4) = (int)(intptr_t)link1; /* tail_link */
  TOUCH(WCIsvListBase_base_insert((int)(intptr_t)list, (int)(intptr_t)link2));
}

/* ---- Rules_HostUnitAttack: `return 1;` (line 70330) only executes if
 * Unit_Attack() returns normally first. With a1=a2=0 it does not: it falls
 * into a debug-logging path (Unit_Attack -> Render_DrawSprite_v3 ->
 * Unit_DebugDumpFormationSizesForStackIndex -> Unit_DebugDumpFormationSizes
 * -> Debug_LogUnitSquadDetails -> Unit_GetSquadCount) that dereferences
 * uninitialized game-state tables never populated in this harness (no
 * mission/world bootstrap). Confirmed via gdb: SIGSEGV inside
 * Unit_GetSquadCount before Unit_Attack returns. ---- */
TEST(cov4_05_rules, host_unit_attack_attempt) {
  TOUCH(Rules_HostUnitAttack(0, 0, 0, 0, 0.0));
}

/* ---- Rules_CheckFactExistp: with a 1-node arg chain (type tag 6, so
 * Rules_ResolveFactArgument's own `v9 == 6` branch is taken and stays inside
 * our zeroed valbuf), Lexer_TokenExpect(1)/Rules_RtnUnknown do succeed at
 * this call site, but Rules_RtnUnknown's own Parser_ParseForm call crashes
 * on a completely unrelated decompiler-lost local a few frames further in
 * (confirmed via gdb: SIGSEGV inside Parser_ParseForm at clash95.c:111515,
 * reading a garbage type/tag value), so it never returns and line 108153 is
 * never reached. ---- */
TEST(cov4_05_rules, check_fact_existp_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 6, valbuf1); /* FACT-ADDRESS type tag */
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_CheckFactExistp(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Instance_MessageDuplicateInstanceFunction: reaching line 136523
 * needs Instance_ActiveMessageDuplicateInstanceFunction() to return. With a
 * 2-node dword_51A960 chain (so its first dereference chain,
 * `*(*(*(dword_51A960+6)+10)+10)`, resolves to a real node address instead
 * of NULL+10), it gets one statement further but then crashes at
 * clash95.c:136445 dereferencing `**(dword_51A960 + 2)` -- a different head
 * field (offset +2, not +6) that our node-chain fixture doesn't populate
 * meaningfully. Getting further would need a from-scratch model of this
 * function's specific argument-list shape. ---- */
TEST(cov4_05_instance, message_duplicate_instance_function_attempt) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char node2[64];
  static unsigned char valbuf1[64];
  static unsigned char valbuf2[64];
  int saved;
  memset(head, 0, sizeof head);
  cov4_05_mk_arg_node(node1, 1, valbuf1);
  cov4_05_mk_arg_node(node2, 1, valbuf2);
  *(int *)(node1 + 10) = (int)(intptr_t)node2;
  *(int *)(head + 6) = (int)(intptr_t)node1;
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Instance_MessageDuplicateInstanceFunction(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Class_LookupClassOrReportError: with no scope separator in the name,
 * this resolves to Class_LookupInScope(a2) -> Rules_FindSymbolEntry(a2),
 * which (per test_cov11.c: "returns 0 whenever the function-name hash table
 * (dword_54DD50) hasn't been carved out yet, which is the default state")
 * returns 0/not-found by default even after Mem_InitReserveBlock() +
 * Rules_InitAtomTables(), so `result` at line 172694 is always the falsy
 * not-found value; a real defclass registration would be needed to make it
 * truthy, which is out of scope here. ---- */
TEST(cov4_05_class, lookup_class_or_report_error_attempt) {
  static char name[] = "Nope";
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Class_LookupClassOrReportError(0, (unsigned char *)name));
}

/* ---- Defgeneric_RemoveConstruct: reaching 119440-119442 needs
 * Defgeneric_IsDeletable() to return truthy, but that function
 * unconditionally dereferences its own decompiler-lost local `v0`
 * (clash95.c:119348, `*(_DWORD *)(v0 + 20)`) with zero arguments to
 * influence it. Confirmed via gdb (SIGSEGV inside Defgeneric_IsDeletable);
 * a 300-iteration varied-stack-padding retry (private build) never once
 * avoided the crash. ---- */
TEST(cov4_05_defgeneric, remove_construct_attempt) {
  TOUCH(Defgeneric_RemoveConstruct(1));
}

/* ---- CRT_IsExtendedMbcsLeadByte: line 187699 is only reachable when
 * `!ismbclegal_(a2, a1)` is true, but this coverage harness's own
 * ismbclegal_() stub (defined once in tests/unit/test_all.c, matching the
 * "using guessed type" external-function annotation on this call) always
 * returns 1, so `!ismbclegal_(...)` is always false in this build
 * regardless of input -- only line 187700 is reachable here. Not something
 * a test file can work around without changing that shared stub. ---- */
TEST(cov4_05_crt, is_extended_mbcs_lead_byte_attempt) {
  TOUCH(CRT_IsExtendedMbcsLeadByte(0x82, 0x40));
}
