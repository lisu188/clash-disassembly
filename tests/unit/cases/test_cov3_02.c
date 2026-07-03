/* cov3_02: third-pass coverage additions for a mixed batch of functions that
 * are still only partially covered after the first two passes
 * (Rules_MathMod, Rules_ReorderAgenda, Parser_CollectFunctionArguments,
 * Rules_ParseDefruleRHS, CRT_BeginThread, Rules_NthFunction,
 * Rules_MathLog10, Rules_FindImportExportConstruct,
 * Defgeneric_GetMethodRestrictionsCommand, UnitStack_CopyFromTemplate,
 * Rules_IntegerFunction, Class_ClassSubclassesCommand,
 * Rules_FindFactByIndex, IO_StringRouterPrint, Rules_HostNumberp,
 * Class_SubclassPCommand, Unit_BuildGoSpriteFilePath -- see
 * scratchpad/cov3_batches/cov3_02.json).
 *
 * Every test runs isolated in its own forked child (per tests/unit/test_all.c
 * running each TEST under fork()+alarm(8)), so calls that crash, exit or spin
 * are safe -- we chase genuine extra line coverage of the *target* batch
 * function rather than avoiding risk in whatever it calls further down.
 * Buffers whose address is threaded through a narrowed 32-bit int/_DWORD
 * field (this is a 64-bit -no-pie build; stack addresses truncate to
 * garbage when squeezed through such a field) are declared `static` so they
 * land in the low .bss image instead. */

/* =========================================================================
 * Shared helper #1: the Rules "argument chain" trick (same family used by
 * tests/unit/cases/test_cov10.c, test_cov16.c, test_cov17.c, test_cov2_04.c):
 * Rules_RtnArgCount()/Rules_RtnUnknown() walk a chain of "argument nodes"
 * rooted at dword_51A960+6, each node being (int16 type_tag; DWORD value;
 * ... DWORD next @ offset 10). Parser_ParseForm's "simple literal" case
 * (type_tag in {0,1,2,3,5,7,8}) copies the node's raw value field straight
 * into the caller's out-param without evaluating anything -- so pointing
 * that value field at our own scratch buffer lets us hand
 * Lexer_ParseValueList() a real, well-typed argument value deterministically.
 * dword_51A960+2 is also wired to a funcrec->symnode safety net so that if
 * some code path instead falls into Rules_RtnUnknown's "argument not found"
 * branch, it dereferences valid zeroed memory instead of chasing NULL.
 * ========================================================================= */
static void cov3_02_arg_node_init(unsigned char *node, short type_tag,
                                   void *value_ptr, unsigned char *next_node) {
  memset(node, 0, 32);
  *(short *)(node + 0) = type_tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)value_ptr;
  *(_DWORD *)(node + 10) = (_DWORD)(intptr_t)next_node;
}

static void cov3_02_install_arg_chain(unsigned char *argnode, _DWORD *funcrec,
                                       _DWORD *symnode,
                                       unsigned char *head_node) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)head_node;
  dword_51A960 = (int)(intptr_t)argnode;
}

/* =========================================================================
 * Shared helper #2: a fake character-source IO router (same shape as
 * tests/unit/cases/test_cov2_04.c's Lexer_ReadToken helper), reused here to
 * drive Parser_NextToken/Parser_ParseProgram with real tokens instead of an
 * always-EOF unregistered channel. IO_RouterMatchesName only requires
 * offset4 (active) truthy and offset12 (query) returning exactly 1 -- our
 * query callback matches unconditionally, so the channel int itself is
 * irrelevant. Lexer_PeekChar calls the offset24 "read" callback fresh on
 * every invocation (there is no separate peek-ahead cache at this layer),
 * so the callback below hands out one character of a fixed string per call,
 * falling back to a space once exhausted. Lexer_SkipChar's offset28 "skip"
 * callback is an intentional no-op stub. */
static int cov3_02_lex_query(int a1) {
  (void)a1;
  return 1;
}
static int cov3_02_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}
static const char *cov3_02_lex_seq;
static int cov3_02_lex_pos;
static int cov3_02_lex_read(int a1) {
  unsigned char c;
  (void)a1;
  c = (unsigned char)cov3_02_lex_seq[cov3_02_lex_pos];
  if (c)
    ++cov3_02_lex_pos;
  else
    c = ' ';
  return c;
}
static void cov3_02_install_lex_router(_DWORD *router, const char *seq) {
  memset(router, 0, 16 * sizeof(_DWORD));
  router[1] = 1; /* offset4: active */
  router[3] = (_DWORD)(intptr_t)cov3_02_lex_query;  /* offset12 */
  router[6] = (_DWORD)(intptr_t)cov3_02_lex_read;   /* offset24 */
  router[7] = (_DWORD)(intptr_t)cov3_02_lex_skip;   /* offset28 */
  dword_51A604 = (int)(intptr_t)router;
  cov3_02_lex_seq = seq;
  cov3_02_lex_pos = 0;
}

/* =========================================================================
 * Rules_MathMod (7/40 covered): the existing test_cov17.c test only reaches
 * the Lexer_TokenExpect(2)==-1 early-fail path (LABEL_20). Build a real
 * 2-argument chain (INTEGER/FLOAT literals via helper #1) so both
 * Lexer_ParseValueList(...,110,...) calls can succeed, driving into the
 * divide-by-zero check, the integer-modulo branch and the floating-point
 * floor/ceil branch. Each shape gets its own TEST (own forked child) so an
 * evaluation-error flag or crash set by one attempt cannot affect another.
 * ========================================================================= */
TEST(cov3_02_mathmod, integer_mod_nonzero_divisor) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static _DWORD result_slot[16];

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  memset(result_slot, 0, sizeof result_slot);
  *(int *)(val1 + 16) = 17; /* dividend */
  *(int *)(val2 + 16) = 5;  /* divisor */

  cov3_02_arg_node_init(node2, 1 /* INTEGER */, val2, 0);
  cov3_02_arg_node_init(node1, 1 /* INTEGER */, val1, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

TEST(cov3_02_mathmod, integer_divide_by_zero) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static _DWORD result_slot[16];

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  memset(result_slot, 0, sizeof result_slot);
  *(int *)(val1 + 16) = 10;
  *(int *)(val2 + 16) = 0; /* divisor 0 -> divide-by-zero branch */

  cov3_02_arg_node_init(node2, 1, val2, 0);
  cov3_02_arg_node_init(node1, 1, val1, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

TEST(cov3_02_mathmod, float_positive_quotient_takes_floor) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static _DWORD result_slot[16];

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  memset(result_slot, 0, sizeof result_slot);
  *(double *)(val1 + 16) = 7.5;  /* dividend, positive */
  *(double *)(val2 + 16) = 2.0;  /* divisor, positive -> quotient >= 0 -> floor() */

  cov3_02_arg_node_init(node2, 0 /* FLOAT */, val2, 0);
  cov3_02_arg_node_init(node1, 0 /* FLOAT */, val1, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

TEST(cov3_02_mathmod, float_negative_quotient_takes_ceil) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static _DWORD result_slot[16];

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  memset(result_slot, 0, sizeof result_slot);
  *(double *)(val1 + 16) = -7.5; /* dividend, negative -> quotient < 0 -> ceil() */
  *(double *)(val2 + 16) = 2.0;

  cov3_02_arg_node_init(node2, 0, val2, 0);
  cov3_02_arg_node_init(node1, 0, val1, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * Rules_ReorderAgenda (6/21 covered): the existing test_cov10.c test only
 * calls Rules_ReorderAgenda(0) with no modules registered, so the do/while
 * body is skipped entirely. Passing a nonzero "current module" pointer
 * directly (bypassing Module_NextEnum(0)) enters the do/while loop with
 * v2==0, which makes the "if (!v2) break;" test at the bottom fire straight
 * after the *first* module's activation list is processed -- so the inner
 * while (activation-list rebuild via Rules_InsertActivationSorted) gets
 * exercised without needing a full multi-module rules-engine bring-up.
 * Rules_GetDefruleModuleItem(v1) resolves to
 * Rules_GetModuleConstructData->Module_GetItem(v1, dword_54E64C), and
 * dword_54E64C defaults to 0 (Rules_RegisterDefruleModuleItem is never
 * called), so Module_GetItem reads itemArray[0] off our fake module's
 * offset+8 field. ========================================================= */
TEST(cov3_02_reorderagenda, single_module_with_activation_chain) {
  static _DWORD fakeModule[16];
  static _DWORD itemArray[4];
  static _DWORD fakeModuleItem[16];
  static _DWORD act1[16], act2[16];
  int savedSort = dword_51A1D8;

  memset(fakeModule, 0, sizeof fakeModule);
  memset(itemArray, 0, sizeof itemArray);
  memset(fakeModuleItem, 0, sizeof fakeModuleItem);
  memset(act1, 0, sizeof act1);
  memset(act2, 0, sizeof act2);

  fakeModule[2] = (_DWORD)(intptr_t)itemArray;      /* offset8 */
  itemArray[0] = (_DWORD)(intptr_t)fakeModuleItem;  /* dword_54E64C == 0 by default */
  fakeModuleItem[3] = (_DWORD)(intptr_t)act1;        /* offset12: activation list head */
  act1[7] = (_DWORD)(intptr_t)act2;                  /* offset28: next activation */
  act2[7] = 0;

  dword_51A1D8 = 0; /* depth-list sort strategy (default) */
  TOUCH(Rules_ReorderAgenda((int)(intptr_t)fakeModule));

  dword_51A1D8 = savedSort;
}

/* =========================================================================
 * Parser_CollectFunctionArguments (5/17 covered): the existing test_cov20.c
 * test uses an unrecognized channel, so Parser_NextToken sees immediate EOF
 * and the while(1) body is skipped entirely. Registering the fake lexer
 * router (helper #2) with real characters lets Parser_ParseArgument's
 * "simple literal" branch (AST_NewNode) succeed for real, driving the
 * append-to-list logic and the loop running a second time; a trailing ')'
 * then produces the EOF(101) token that breaks the loop into the normal
 * epilogue. A second TEST feeds a '|' (global-variable marker token, type
 * 92) as the very first token, which Parser_ParseArgument's "unexpected
 * token" branch turns into *a2=1 -- driving CollectFunctionArguments' own
 * "if (v10[0]==1) { AST_Free(a1); return 0; }" branch that the
 * loop-continuation shape above never reaches. a1 is `static` because it is
 * both written through (*(a1+6)=...) and truncated through the 32-bit int
 * parameter. ========================================================= */
TEST(cov3_02_collectargs, two_symbols_then_close_paren) {
  static _DWORD router[16];
  static _DWORD a1buf[64];
  int saved604 = dword_51A604;

  memset(a1buf, 0, sizeof a1buf);
  cov3_02_install_lex_router(router, "ab cd)");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 909090, 0));

  dword_51A604 = saved604;
}

TEST(cov3_02_collectargs, unexpected_token_sets_error_flag) {
  static _DWORD router[16];
  static _DWORD a1buf[64];
  int saved604 = dword_51A604;

  memset(a1buf, 0, sizeof a1buf);
  cov3_02_install_lex_router(router, "|)");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 909091, 0));

  dword_51A604 = saved604;
}

/* =========================================================================
 * Rules_ParseDefruleRHS (4/14 covered): the existing test_cov20.c test uses
 * no registered router, so the nested Parser_ParseProgram call reaches EOF
 * immediately and returns 0 (the "early return" branch). Feeding it a real
 * token via the same fake router lets Parser_ParseProgram's first-token
 * SYMBOL check take its "return v17" shortcut (a real, non-NULL AST node),
 * making Parser_ParseProgram return truthy and driving Rules_ParseDefruleRHS
 * into its "if (result)" body (the two IO_OutNewline calls, IO_OutWriteToken,
 * and the v6==101 check) -- lines the early-return test never reaches. The
 * channel value itself does not need to be a real pointer since our router's
 * query callback matches unconditionally. ========================================= */
TEST(cov3_02_parsedefrulerhs, real_token_drives_success_branch) {
  static _DWORD router[16];
  int saved604 = dword_51A604;

  cov3_02_install_lex_router(router, "ab)");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ParseDefruleRHS(818181));

  dword_51A604 = saved604;
}

/* =========================================================================
 * CRT_BeginThread (12/21 covered): test_cov2_02.c already exercises both
 * sides of "if (dwTlsIndex == -1)" by toggling dwTlsIndex directly, but
 * CreateThread is unconditionally stubbed to fail in tests/unit/test_all.c,
 * so the "if (Thread) WaitForSingleObject(...)" branch can never be reached
 * in this harness (dead in the test build, not a gap we can close). The
 * still-uncovered branch is CRT_AllocateTlsIndex()'s OWN failure path
 * ("if (!result) return result;"): TlsAlloc() only returns
 * TLS_OUT_OF_INDEXES once every real compat TLS slot (64 of them, see
 * compat/decomp_runtime_stubs.c) is exhausted. Call TlsAlloc() enough times
 * to exhaust them all first, then force dwTlsIndex back to -1 so
 * CRT_BeginThread takes the allocate-tls-index path and observes the
 * failure. ========================================================= */
TEST(cov3_02_crtbeginthread, allocate_tls_index_failure_path) {
  DWORD saved = dwTlsIndex;
  int i;
  for (i = 0; i < 128; ++i) {
    TlsAlloc();
  }
  dwTlsIndex = 0xFFFFFFFFu;
  TOUCH(CRT_BeginThread(0, 4096, 0));
  dwTlsIndex = saved;
}

/* =========================================================================
 * Rules_NthFunction (7/15 covered): the existing test_cov16.c test uses the
 * safe-but-empty argument chain, which deterministically fails the "&&"
 * guard chain and takes the "else" Str_Intern(nil) fallback. Build a real
 * 2-argument chain (INTEGER index, MULTIFIELD data) using the same
 * base/begin/end multifield-descriptor convention already used by
 * tests/unit/cases/test_cov2_01.c and test_cov16.c's
 * Rules_MultifieldFindElementPosition test, to attempt the "found" branch's
 * own lines. Several of this function's locals (v5, v7) are themselves
 * decompiler-lost ("possibly undefined"), so the exact bytes read back are
 * not something we can fully pin down statically -- a crash partway through
 * the success block is expected and still banks real, new coverage of the
 * lines executed before it. ========================================= */
TEST(cov3_02_nthfunction, two_arg_index_and_multifield) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char idxval[32];
  static _DWORD mfHeader[8];
  static _DWORD storage[128];
  static _DWORD out[8];

  memset(idxval, 0, sizeof idxval);
  memset(mfHeader, 0, sizeof mfHeader);
  memset(storage, 0, sizeof storage);
  memset(out, 0, sizeof out);

  *(int *)(idxval + 16) = 2; /* nth index, 1-based */
  mfHeader[2] = (_DWORD)(intptr_t)storage; /* base */
  mfHeader[3] = 0;                         /* begin */
  mfHeader[4] = 2;                         /* end -> 3 elements */

  cov3_02_arg_node_init(node2, 4 /* MULTIFIELD */, mfHeader, 0);
  cov3_02_arg_node_init(node1, 1 /* INTEGER */, idxval, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_NthFunction((int)(intptr_t)out, 5, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * Rules_MathLog10 (6/13 covered): the existing test_cov17.c test uses the
 * fake-empty argnode, which fails Rules_MathParseSingleArg's own
 * Lexer_TokenExpect(1) guard and returns 0.0 immediately. Rules_MathLog10's
 * remaining branches (domain error for negative input, overflow error for
 * exactly zero, and the real log10() call) all need
 * Rules_MathParseSingleArg to succeed with a real FLOAT argument -- one
 * literal node whose type_tag (0 == FLOAT) matches Lexer_ParseValueList's
 * a3==0 request exactly. Each numeric case gets its own TEST. ============ */
TEST(cov3_02_mathlog10, negative_argument_domain_error) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];

  memset(val, 0, sizeof val);
  *(double *)(val + 16) = -5.0;
  cov3_02_arg_node_init(node, 0 /* FLOAT */, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog10(0, 0, 0, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

TEST(cov3_02_mathlog10, zero_argument_overflow_error) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];

  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 0.0;
  cov3_02_arg_node_init(node, 0, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog10(0, 0, 0, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

TEST(cov3_02_mathlog10, positive_argument_success) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];

  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 100.0;
  cov3_02_arg_node_init(node, 0, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog10(0, 0, 0, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * Rules_FindImportExportConstruct (9/15 covered): test_cov14.c already
 * covers the "has module separator" early-return and the
 * "no separator, construct not found" (Module_FindItemByName returns 0)
 * paths. The remaining branch needs Module_FindItemByName("fn") to find a
 * real module record whose offset+24 field is also truthy.
 * Module_FindItemByName just walks the plain global list rooted at
 * dword_51A9BC comparing *(int*)current against the name pointer via
 * strcmp_, so seeding that global directly with one fake record (name
 * pointer at offset0, "has exports" flag at offset+24, next==0) drives the
 * "found" branch without needing full module-system bring-up. ============ */
TEST(cov3_02_fie, found_construct_with_exports_flag) {
  static const char fie_name[] = "fn";
  static _DWORD fakeModule[16];
  static _DWORD a2[4];
  static char a3[16];
  int saved51A9BC = dword_51A9BC;

  memset(fakeModule, 0, sizeof fakeModule);
  fakeModule[0] = (_DWORD)(intptr_t)fie_name; /* offset0: module name ptr */
  fakeModule[6] = 1;                          /* offset24: nonzero flag */
  fakeModule[7] = 0;                          /* offset28: next == 0 */
  dword_51A9BC = (int)(intptr_t)fakeModule;

  memset(a2, 0, sizeof a2);
  strcpy(a3, "plain");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_FindImportExportConstruct((char *)fie_name, a2, (_BYTE *)a3, 0, 0));

  dword_51A9BC = saved51A9BC;
}

/* =========================================================================
 * Defgeneric_GetMethodRestrictionsCommand (3/8 covered): the existing
 * test_cov14.c test uses an empty/failing argument chain, so only the
 * top-level guard and the "else" Rules_SetMultifieldErrorValue fallback are
 * reached. A real SYMBOL argument (matching Lexer_ParseValueList's a3==2
 * request) lets the "&&" chain reach the Defgeneric_CheckGenericExists()
 * call, which is new coverage for this function regardless of what happens
 * inside that (out-of-batch) callee -- Defgeneric_LookupWithImports reads
 * through the never-registered dword_54E6A0 defgeneric-module-item global,
 * so a crash a frame down is expected and isolated. ========================= */
TEST(cov3_02_defgeneric_getmethodrestrictions, real_symbol_argument) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];
  static const char generic_name[] = "cov3_02FakeGeneric";
  static _DWORD out[16];

  memset(val, 0, sizeof val);
  memset(out, 0, sizeof out);
  *(const char **)(val + 16) = generic_name;
  cov3_02_arg_node_init(node, 2 /* SYMBOL */, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(out, 0, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * UnitStack_CopyFromTemplate (7/11 covered): both existing attempts
 * (test_cov02.c, test_cov2_00.c) already document that this function reads
 * a genuine decompiler-uninitialized local (v7) for its second
 * _wcpp_4_copy_array__ call, faulting shortly after on
 * "*(_BYTE*)(v4+400) = ...:" once v7 (which becomes v4, since
 * _wcpp_4_copy_array__ is just an identity stub -- see
 * compat/decomp_runtime_stubs.c) resolves to whatever garbage register/stack
 * value happened to be live at that point. Try a fresh call site with
 * different preceding stack content in case it happens to leave a more
 * favorable value there. ========================= */
TEST(cov3_02_unitstack, copy_from_template_fresh_stack_context) {
  static unsigned char a1buf[2048];
  static unsigned char a2buf[2048];
  int filler[37];
  memset(filler, 0, sizeof filler);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  *(_WORD *)(a2buf + 316) = 3;
  *(_BYTE *)(a2buf + 720) = 9;
  *(_DWORD *)(a2buf + 721) = 1234;
  TOUCH(filler[0]);
  TOUCH(UnitStack_CopyFromTemplate((int)(intptr_t)a1buf, (int)(intptr_t)a2buf, (int)(intptr_t)a1buf));
}

/* =========================================================================
 * Rules_IntegerFunction (4/8 covered): the existing test_cov16.c test uses
 * the safe empty argument chain and CHECK_EQ's the result to 0 (either the
 * Lexer_TokenExpect(1)==-1 branch or a failed Lexer_ParseValueList). Feed a
 * real single INTEGER argument (a3==1 request, matching type_tag 1 exactly)
 * so the "if (result) return *(int*)(v3[2]+16);" success branch gets
 * exercised too. ========================= */
TEST(cov3_02_integerfunction, real_integer_argument_success) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];

  memset(val, 0, sizeof val);
  *(int *)(val + 16) = 42;
  cov3_02_arg_node_init(node, 1 /* INTEGER */, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_IntegerFunction(1, 0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * Class_ClassSubclassesCommand (3/7) and Class_SubclassPCommand (2/5): both
 * route through Class_ParseClassNameAndInheritFlag / Class_ParseTwoClassNameArgs
 * -> Class_LookupByQualifiedName -> Class_LookupInScope, which (for a name
 * without "::") is a clean, deterministic hash lookup: Rules_FindSymbolEntry
 * finds the interned name symbol via the SAME table/hash Str_Intern uses,
 * Class_HashClassName(symbol) picks a bucket in the class hash table rooted
 * at the plain global dword_51AD68 (normally allocated by the class
 * subsystem's own init, never called here -- so we allocate + wire it up by
 * hand), and Class_IsInScope reads a scope-bitmask through the class
 * record's offset+104 field against the "current module"'s offset+24 field
 * (Module_GetCurrent() == dword_51A9B0, also a plain global we control
 * directly). Unlike the Lexer_TokenExpect-guarded arithmetic functions
 * above, Rules_RtnArgCount() itself has no decompiler-lost variables, so
 * this path is fully deterministic. ========================= */
static int *cov3_02_register_fake_class(const char *name) {
  static _DWORD classTable[0xA7];
  static _DWORD classRecord[128];
  static _DWORD scopeInfo[8];
  static unsigned char scopeBits[8];
  static _DWORD fakeModule[16];
  signed int *symbol;
  unsigned int bucket;

  memset(classTable, 0, sizeof classTable);
  memset(classRecord, 0, sizeof classRecord);
  memset(scopeInfo, 0, sizeof scopeInfo);
  memset(scopeBits, 0xFF, sizeof scopeBits);
  memset(fakeModule, 0, sizeof fakeModule);

  symbol = Str_Intern((char *)name, 0);
  bucket = Class_HashClassName((int)(intptr_t)symbol);

  scopeInfo[4] = (_DWORD)(intptr_t)scopeBits; /* offset16: scope bitmask array */

  classRecord[0] = (_DWORD)(intptr_t)symbol; /* offset0: class-name symbol ptr */
  *((unsigned char *)classRecord + 20) |= 1;  /* offset20 bit0: "defined" flag */
  classRecord[25] = 0;                        /* offset100: next-in-bucket == 0 */
  classRecord[26] = (_DWORD)(intptr_t)scopeInfo; /* offset104: scope info ptr */

  classTable[bucket % 0xA7u] = (_DWORD)(intptr_t)classRecord;
  dword_51AD68 = (int)(intptr_t)classTable;

  fakeModule[6] = 0; /* offset24: bit index 0 into the scope bitmask */
  dword_51A9B0 = (int)(intptr_t)fakeModule;

  return (int *)(intptr_t)classRecord;
}

TEST(cov3_02_classsubclasses, real_class_lookup_success) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];
  static const char class_name[] = "Cov3_02FakeClassA";
  int saved51AD68 = dword_51AD68;
  int saved51A9B0 = dword_51A9B0;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov3_02_register_fake_class(class_name);

  memset(val, 0, sizeof val);
  *(const char **)(val + 16) = class_name;
  cov3_02_arg_node_init(node, 2 /* SYMBOL */, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  TOUCH(Class_ClassSubclassesCommand(1, 1.0));

  dword_51A960 = 0;
  dword_51AD68 = saved51AD68;
  dword_51A9B0 = saved51A9B0;
}

TEST(cov3_02_subclasspcommand, real_two_class_lookup_success) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static const char class_name[] = "Cov3_02FakeClassB";
  int saved51AD68 = dword_51AD68;
  int saved51A9B0 = dword_51A9B0;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov3_02_register_fake_class(class_name);

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  *(const char **)(val1 + 16) = class_name;
  *(const char **)(val2 + 16) = class_name;
  cov3_02_arg_node_init(node2, 2, val2, 0);
  cov3_02_arg_node_init(node1, 2, val1, node2);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node1);

  TOUCH(Class_SubclassPCommand(1.0));

  dword_51A960 = 0;
  dword_51AD68 = saved51AD68;
  dword_51A9B0 = saved51A9B0;
}

/* =========================================================================
 * Rules_FindFactByIndex (6/9 covered): the existing test_cov10.c test
 * asserts no facts, so Rules_GetNextFact(0) (== global dword_51A15C)
 * returns 0 and the function takes its immediate "!result" return. Seed
 * dword_51A15C with a small real fact chain (two entries, offset+29 byte
 * non-negative so Rules_GetNextFact keeps walking, offset+36 the "next"
 * link) so the while-loop body and its Rules_GetNextFact() re-fetch line
 * execute at least once, regardless of which way the function's own
 * decompiler-lost `v1` comparison happens to land. ========================= */
TEST(cov3_02_findfactbyindex, real_fact_chain) {
  static _DWORD fact1[16], fact2[16];
  int saved = dword_51A15C;

  memset(fact1, 0, sizeof fact1);
  memset(fact2, 0, sizeof fact2);
  *((char *)fact1 + 29) = 0; /* not deleted */
  *(_DWORD *)((char *)fact1 + 36) = (_DWORD)(intptr_t)fact2;
  fact1[6] = 111; /* offset24 */
  *((char *)fact2 + 29) = 0;
  *(_DWORD *)((char *)fact2 + 36) = 0; /* end of chain */
  fact2[6] = 222;

  dword_51A15C = (int)(intptr_t)fact1;
  TOUCH(Rules_FindFactByIndex());
  dword_51A15C = saved;
}

/* =========================================================================
 * IO_StringRouterPrint (10/13 covered): the existing test_cov14.c tests all
 * register a matching router first, exercising the "not equal 1" early
 * return, the buffer-full early return and the successful-write path.
 * IO_FindStringRouter safely returns 0 for an unregistered name (it just
 * walks the plain dword_51A9C8 list, defaulting to empty/0), so the
 * remaining "if (!v4) { Rules_ReportSystemError(...); IO_RunRouterExitCallbacks(); }"
 * branch is reachable by simply naming a router that was never opened; the
 * subsequent v4[4] dereference of the resulting NULL is expected to crash,
 * which is fine -- the two new lines in *this* function are reached first.
 * ========================= */
TEST(cov3_02_stringrouterprint, unregistered_router_name) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_StringRouterPrint((int)(intptr_t)"cov3_02_never_opened_router", "x"));
}

/* =========================================================================
 * Rules_HostNumberp (4/7 covered): the existing test_cov16.c test uses the
 * safe empty argument chain (Rules_RtnUnknown's not-found path), which never
 * sets v3[1] to a real type tag, so the "if (v3[1] <= 1u) return 1;" branch
 * is not reliably reached. A real single-arg INTEGER chain gives Lexer_
 * TokenExpect(1) a real count of 1 and Rules_RtnUnknown a real type tag of 1
 * (<=1u), driving the "return 1" line. ========================= */
TEST(cov3_02_hostnumberp, real_integer_argument) {
  static unsigned char argnode[256], node[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val[32];

  memset(val, 0, sizeof val);
  *(int *)(val + 16) = 7;
  cov3_02_arg_node_init(node, 1 /* INTEGER */, val, 0);
  cov3_02_install_arg_chain(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_HostNumberp(0.0));

  dword_51A964 = 0;
  dword_51A960 = 0;
}

/* =========================================================================
 * Unit_BuildGoSpriteFilePath (46/48 covered): near-complete already; try a
 * boundary unit-type index (forcing UnitType_GetResourceKey's out-of-range
 * "peon" default explicitly) and an extreme a3 byte value in case either
 * still-uncovered line is in one of the four copy loops' edge handling.
 * ========================= */
TEST(cov3_02_buildgospritepath, boundary_unit_type_and_suffix) {
  char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Unit_BuildGoSpriteFilePath(buf, 255, (char)-1));
}
