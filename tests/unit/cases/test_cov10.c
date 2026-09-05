/* cov10 cluster: Compat_Query*, Rules_Fact*, Rules_Place*InList, agenda/refresh
 * command wrappers around 0x479C90-0x4826xx (see cov_batches/cov_10.json). */

/* ---- Compat_QueryXorDecodeBuffer: xor-decode a byte buffer using a running
 * counter seeded from a1+48, keyed by a1+20; loop runs a3 times. ---- */
TEST(cov10_compat, xor_decode_buffer) {
  _DWORD ctx[16];
  unsigned char buf[32];
  int i;

  memset(ctx, 0, sizeof(ctx));
  ctx[12] = 7;   /* offset 48 bytes / 4 = index 12 */
  ctx[5] = 3;    /* offset 20 bytes / 4 = index 5 */
  for (i = 0; i < 32; ++i) buf[i] = (unsigned char)(i * 5 + 1);

  unsigned char *end = Compat_QueryXorDecodeBuffer((int)(intptr_t)ctx, buf, 10);
  CHECK(end == buf + 10);

  /* a3 == 0: loop body never runs, result == a2 unchanged. */
  unsigned char *end0 = Compat_QueryXorDecodeBuffer((int)(intptr_t)ctx, buf, 0);
  CHECK(end0 == buf);
}

TEST(cov10_compat, query_get_length) {
  _DWORD obj[8];
  memset(obj, 0, sizeof(obj));
  obj[2] = 12345; /* offset 8 bytes -> index 2 */
  CHECK_EQ(Compat_QueryGetLength((int)(intptr_t)obj), 12345);
}

/* ---- Fact ref-count helpers: trivial increment/decrement through offset 8. */
TEST(cov10_facts, ref_count_inc_dec) {
  _DWORD fact[8];
  memset(fact, 0, sizeof(fact));
  fact[2] = 5;
  TOUCH(Rules_IncrementFactRefCount((int)(intptr_t)fact));
  CHECK_EQ(fact[2], 6);
  TOUCH(Rules_DecrementFactRefCount((int)(intptr_t)fact));
  CHECK_EQ(fact[2], 5);
}

TEST(cov10_facts, get_fact_index) {
  _DWORD fact[16];
  memset(fact, 0, sizeof(fact));
  fact[6] = 42; /* offset 24 bytes -> index 6 */
  CHECK_EQ(Rules_GetFactIndex((int)(intptr_t)fact), 42);
}

/* ---- Rules_PrintFactWithIndex / Rules_PrintFactLabel: format a small string
 * via sprintf_ and route it through Output_Write. With no router registered
 * (dword_51A604/dword_51A60C both default 0), Output_Write short-circuits at
 * LABEL_5 without ever touching the message pointer, so this is safe even
 * though the callee's own "a1" router-name argument is decompiler-garbage. */
TEST(cov10_facts, print_fact_with_index_and_label) {
  _DWORD fact[16];
  memset(fact, 0, sizeof(fact));
  fact[6] = 99; /* offset 24 -> printed index */
  /* fact[4] (offset 16) is the deftemplate pointer used by Rules_PrintFact;
   * point it at a small zeroed struct so the slot-flag byte read is safe and
   * takes the "no template" formatting branch. */
  _DWORD tmpl[8];
  memset(tmpl, 0, sizeof(tmpl));
  fact[4] = (_DWORD)(intptr_t)tmpl;
  TOUCH(Rules_PrintFactWithIndex(0, (int)(intptr_t)fact));
  TOUCH(Rules_PrintFactLabel(0, (int)(intptr_t)fact));
}

/* ---- Rules_Log: builds a fact from a string then asserts it. With no
 * deftemplate registered, Rules_StringToFact is expected to fail (return 0)
 * for a bogus string, exercising the "result == 0" early-return branch. */
TEST(cov10_facts, log_bad_string) {
  TOUCH(Rules_Log("(", 0, 0.0));
  TOUCH(Rules_Log("not-a-fact-string !!", 5, 1.0));
}

/* ---- Rules_FindFactByIndex: with no facts asserted, Rules_GetNextFact(0)
 * returns 0 (empty list), so the function takes the early "!result" return. */
TEST(cov10_facts, find_fact_by_index_empty) {
  TOUCH(Rules_FindFactByIndex(0));
}

/* ---- Rules_RegisterFactCommands: registers a batch of host functions/
 * commands into the (global) command tables; pure side-effecting setup call,
 * safe to invoke directly. */
TEST(cov10_facts, register_fact_commands) {
  TOUCH(Rules_RegisterFactCommands());
}

/* ---- Rules_GetFactDuplicationCommand: reads the duplication flag then
 * expects zero parser args; Lexer_TokenExpect/Rules_RtnArgCount walk a list
 * rooted at global dword_51A960, which defaults to NULL and would fault at
 * address 6. Point it at a zeroed buffer so the arg-count walk terminates
 * safely at count 0 instead of crashing. */
TEST(cov10_facts, get_fact_duplication_command) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_GetFactDuplicationCommand());
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_ParsePositiveIntArg: a1 > a2 short-circuits to -1 without
 * touching parser state at all -- cheap, safe branch coverage. */
TEST(cov10_parse, positive_int_arg_range_short_circuit) {
  CHECK_EQ(Rules_ParsePositiveIntArg(5, 1, 0, 0.0), -1);
}

/* Drive past the a1<=a2 guard with a fake arg-list so Lexer_ParseValueList's
 * internal Rules_RtnUnknown call sees a zeroed (but non-NULL) node chain
 * rather than dereferencing NULL+6. */
TEST(cov10_parse, positive_int_arg_with_fake_argnode) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_ParsePositiveIntArg(1, 3, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_ParseLoadFactsCommand: Lexer_TokenExpect(1) will fail (arg
 * count mismatch against a default-empty arg chain) and return 0 early. */
TEST(cov10_parse, load_facts_command_bad_args) {
  TOUCH(Rules_ParseLoadFactsCommand(0, 0.0));
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_ParseLoadFactsCommand(0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_AssertParsedFact: frees a1 (AST_Free tolerates 0), logs a
 * fixed banner, then delegates the heavy lifting to
 * Rules_ParseAssertCommand/Rules_ParseAssertRHSPattern (outside this batch);
 * called with zeroed scratch args for coverage of this wrapper's own lines. */
TEST(cov10_parse, assert_parsed_fact) {
  TOUCH(Rules_AssertParsedFact(0, 0, 0));
}

/* ---- Rules_ClearCommand / Rules_ResetCommand: thin wrappers around
 * Lexer_TokenExpect(0) + Rules_Clear()/Rules_Reset(). Exercise with a fake
 * arg-node so the token-count walk does not fault on the default NULL
 * dword_51A960. */
TEST(cov10_cmds, clear_and_reset_command) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_ClearCommand());
  TOUCH(Rules_ResetCommand());
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_BloadCommand: Lexer_TokenExpect(1) against the same fake empty
 * arg chain (count 0 != 1) takes the early "return 0" path deterministically
 * via the -1 mismatch code, still exercising the wrapper's own lines. */
TEST(cov10_cmds, bload_command) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_BloadCommand(0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_RegisterBuiltinFunctionGroups: chains a dozen "Rules_Register*"
 * setup calls; pure registration side effects, safe standalone. */
TEST(cov10_cmds, register_builtin_function_groups) {
  TOUCH(Rules_RegisterBuiltinFunctionGroups());
}

/* ---- Rules_ShutdownEngine: sets the evaluation error flag, closes batch
 * sources (no sources open -> no-op loop), and (re)installs the SIGINT-style
 * handler; safe to call repeatedly. */
TEST(cov10_cmds, shutdown_engine) {
  TOUCH(Rules_ShutdownEngine());
}

/* ---- Rules_BloadDeleteFile / Rules_RenameFile: thin wrappers around
 * IO_RemoveFileByPath / IO_RenameFile with a nonexistent path -- exercised
 * for both the "call succeeded" (==0) and "call failed" comparison lines. */
TEST(cov10_cmds, bload_delete_and_rename_file) {
  TOUCH(Rules_BloadDeleteFile(0, (int)(intptr_t)"/nonexistent/cov10_delete_me"));
  TOUCH(Rules_RenameFile("/nonexistent/cov10_src", "/nonexistent/cov10_dst", 0));
}

/* ---- Rules_PlaceInDepthList / Rules_PlaceInBreadthList: walk a singly
 * linked list of "activation" records (fields at word-indices 2,3 = depth-
 * pair, 7 = next) looking for the insertion point relative to a2's depth
 * pair. Build a 3-node list to exercise both the "insert before head" and
 * "walk past a node" branches, plus the NULL-list early return. */
TEST(cov10_agenda, place_in_depth_list) {
  _DWORD nodeA[8], nodeB[8], nodeC[8], newnode[8];
  memset(nodeA, 0, sizeof(nodeA));
  memset(nodeB, 0, sizeof(nodeB));
  memset(nodeC, 0, sizeof(nodeC));
  memset(newnode, 0, sizeof(newnode));

  nodeA[2] = 10; nodeA[3] = 1; nodeA[7] = (_DWORD)(intptr_t)nodeB;
  nodeB[2] = 5;  nodeB[3] = 2; nodeB[7] = (_DWORD)(intptr_t)nodeC;
  nodeC[2] = 1;  nodeC[3] = 0; nodeC[7] = 0;

  /* new node with high depth: should stop at head (v2>v5 immediately). */
  newnode[2] = 20; newnode[3] = 0;
  TOUCH(Rules_PlaceInDepthList(nodeA, (int)(intptr_t)newnode));

  /* new node with low depth: walks the whole chain to the end. */
  newnode[2] = 0; newnode[3] = 0;
  TOUCH(Rules_PlaceInDepthList(nodeA, (int)(intptr_t)newnode));

  /* empty list -> immediate NULL return. */
  CHECK(Rules_PlaceInDepthList((_DWORD *)0, (int)(intptr_t)newnode) == 0);

  /* equal-depth tie broken on the second field. */
  newnode[2] = 10; newnode[3] = 5;
  TOUCH(Rules_PlaceInDepthList(nodeA, (int)(intptr_t)newnode));
}

TEST(cov10_agenda, place_in_breadth_list) {
  _DWORD nodeA[8], nodeB[8], nodeC[8], newnode[8];
  memset(nodeA, 0, sizeof(nodeA));
  memset(nodeB, 0, sizeof(nodeB));
  memset(nodeC, 0, sizeof(nodeC));
  memset(newnode, 0, sizeof(newnode));

  nodeA[2] = 1; nodeA[3] = 9; nodeA[7] = (_DWORD)(intptr_t)nodeB;
  nodeB[2] = 5; nodeB[3] = 5; nodeB[7] = (_DWORD)(intptr_t)nodeC;
  nodeC[2] = 10; nodeC[3] = 1; nodeC[7] = 0;

  newnode[2] = 0; newnode[3] = 0;
  TOUCH(Rules_PlaceInBreadthList(nodeA, (int)(intptr_t)newnode));

  newnode[2] = 20; newnode[3] = 0;
  TOUCH(Rules_PlaceInBreadthList(nodeA, (int)(intptr_t)newnode));

  CHECK(Rules_PlaceInBreadthList((_DWORD *)0, (int)(intptr_t)newnode) == 0);

  newnode[2] = 1; newnode[3] = 20;
  TOUCH(Rules_PlaceInBreadthList(nodeA, (int)(intptr_t)newnode));
}

/* ---- Rules_PlaceInRandomList: three-key comparison (fields 3,2,5) walking
 * the same style of linked list. */
TEST(cov10_agenda, place_in_random_list) {
  _DWORD nodeA[8], nodeB[8], newnode[8];
  memset(nodeA, 0, sizeof(nodeA));
  memset(nodeB, 0, sizeof(nodeB));
  memset(newnode, 0, sizeof(newnode));

  nodeA[2] = 5; nodeA[3] = 5; nodeA[5] = 5; nodeA[7] = (_DWORD)(intptr_t)nodeB;
  nodeB[2] = 1; nodeB[3] = 1; nodeB[5] = 1; nodeB[7] = 0;

  newnode[2] = 10; newnode[3] = 10; newnode[5] = 10;
  TOUCH(Rules_PlaceInRandomList(nodeA, newnode));

  newnode[2] = 0; newnode[3] = 0; newnode[5] = 0;
  TOUCH(Rules_PlaceInRandomList(nodeA, newnode));

  CHECK(Rules_PlaceInRandomList((_DWORD *)0, newnode) == 0);

  /* tie on field 2, differ on field 5 */
  newnode[2] = 5; newnode[3] = 5; newnode[5] = 0;
  TOUCH(Rules_PlaceInRandomList(nodeA, newnode));

  /* tie on 2 and 5, differ on 3 -> exercises final "v2 <= a1[3]" compare */
  newnode[2] = 5; newnode[3] = 3; newnode[5] = 5;
  TOUCH(Rules_PlaceInRandomList(nodeA, newnode));
}

/* ---- Rules_GetStrategyName: exercise every switch case plus default. */
TEST(cov10_agenda, get_strategy_name) {
  int i;
  for (i = 0; i <= 7; ++i) {
    TOUCH(Rules_GetStrategyName(i));
  }
  TOUCH(Rules_GetStrategyName(-1));
}

/* ---- Rules_ActivationsCommand: a thin argument-forwarding wrapper around
 * Rules_ListConstructsAcrossModules; safe with no modules registered (the
 * inner enum loop just terminates immediately). */
TEST(cov10_agenda, activations_command) {
  TOUCH(Rules_ActivationsCommand(0, 0));
}

/* ---- Rules_ClearActivationsForModule: reads the current module's
 * activation list head via Rules_GetDefruleModuleItem(0); with no defrule
 * module data installed this is expected to yield NULL and return
 * immediately without entering the removal loop. */
TEST(cov10_agenda, clear_activations_for_module_empty) {
  TOUCH(Rules_ClearActivationsForModule());
}

/* ---- Rules_ReorderAgenda: result==0 path asks Module_NextEnum(0) for the
 * first module; with none registered it returns 0 and the do/while body is
 * skipped entirely (early "if" false branch). */
TEST(cov10_agenda, reorder_agenda_no_modules) {
  CHECK_EQ(Rules_ReorderAgenda(0), 0);
}

/* ---- Rules_RefreshCommand / Rules_RefreshAgendaCommand: parser-arg
 * wrappers; drive them past the token-count guard with the same fake
 * arg-node trick used above so the wrapper's own branch structure gets
 * exercised instead of faulting on a NULL global. */
TEST(cov10_agenda, refresh_command_and_agenda_command) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_RefreshCommand(0, 0.0));
  TOUCH(Rules_RefreshAgendaCommand(0.0));
  g_ClipsCurrentExpression = 0;
}
