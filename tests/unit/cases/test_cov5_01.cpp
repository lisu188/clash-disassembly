/* cov5_01: stack-spray coverage pass for a batch of largely rules-engine
 * functions (see scratchpad/cov5_batches/cov5_01.json): Rules_MathMod,
 * Parser_ParseInstanceQueryNoAction, Defgeneric_ClearDefgenerics,
 * Rules_ConstructCodeFileOpen, Rules_ExpressionConstraintsCompatible,
 * Rules_NthFunction, Rules_MathCsch, Rules_GetAllowedAttributeTokenCode,
 * Rules_ListInstancesForClassOrModule, ObjectsCompiler_CloseConstructFileGroup.
 *
 * IMPORTANT PRE-EXISTING FINDING (verified by cross-checking already-written,
 * but currently UNWIRED-into-test_all.c, sibling files -- test_cov4_00.c,
 * test_cov4_01.c, test_cov4_05.c, test_cov4_07.c -- plus the ALREADY-WIRED
 * test_cov3_02.c): every `Lexer_ParseValueList()` call that finds a real
 * argument (i.e. `Rules_RtnUnknown` succeeds and leaves the global
 * `dword_51A964` "halt" flag at 0) immediately executes
 *   `if ( a3 == *(_DWORD *)(v7 + 4) || ... )`
 * at clash95.c:99870, where `v7` is a decompiler-lost local that is
 * dereferenced *unconditionally* (the left operand of `||` always
 * evaluates). test_cov4_05.c documents this as a gdb-confirmed, reliable
 * SIGSEGV (40 varied-stack-padding retries, always crashing at this exact
 * site), and test_cov3_02.c's `cov3_02_mathmod` tests -- which build a
 * real, well-formed 2-argument INTEGER/FLOAT chain exactly as this batch's
 * instructions recommend, and which ARE wired into test_all.c and thus
 * already contribute to the coverage run that produced this batch's JSON --
 * still leave clash95.c:130121-130156 uncovered. That is direct, empirical
 * proof (not just prior-pass folklore) that no argument-chain construction
 * can get Rules_MathMod (or Rules_NthFunction, or Rules_MathCsch via
 * Rules_MathParseSingleArg, which shares this exact call shape) past this
 * point: it is a genuine hard ceiling in this recompilation, not a "stack
 * spray not yet tried" gap. Below, MathMod/NthFunction/MathCsch therefore
 * only chase the lines reachable *without* a successful argument parse
 * (the "not found" -> dword_51A964 early-return path, which returns before
 * ever reaching the v7 dereference), plus one documented, harmless,
 * best-effort attempt each at the unreachable branches. */

/* ---- Shared stack-spray helper (the technique this whole pass is named
 * for): spray a large volatile stack region with `val` immediately before
 * the target call so that any "possibly undefined" local read by the
 * target (or its near callees, within this depth) reads back as `val`. */
static void cov5_01_stack_prime(int val) {
  volatile int buf[65536];
  int i;
  for (i = 0; i < 65536; i++) {
    buf[i] = val;
  }
  (void)buf[0];
}

/* ---- Shared argument-node helpers (Rules_RtnArgCount / Rules_RtnUnknown /
 * Lexer_TokenExpect family): dword_51A960+6 is the head of a chain of
 * "argument nodes" (int16 type_tag @ +0; DWORD value_ptr @ +2; DWORD next @
 * +10). dword_51A960+2 must additionally point at a "function record" whose
 * own first field points at a zeroed "symbol" node, matching the safety net
 * documented in tests/unit/cases/test_cov16.c / test_cov4_07.c -- required
 * because Rules_RtnUnknown's "argument not found" fallback
 * (Rules_NonexistentArgError) dereferences that chain unconditionally even
 * when the real argument list is empty. */
static void cov5_01_install_safe_argctx(unsigned char *argnode,
                                         _DWORD *funcrec, _DWORD *symnode,
                                         void *head_node) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)head_node;
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
}

/* =========================================================================
 * Rules_MathMod (33 uncovered lines targeted: 130112-130156). Only the
 * "not found" early-exit path is a genuine hard ceiling-free win (see the
 * file header). Lexer_TokenExpect's own decompiler-lost `v2` local selects
 * between exact/at-least/at-most argument-count matching; priming it lets
 * us pick deterministically whether Lexer_TokenExpect(2) itself fails
 * (driving Rules_MathMod straight to LABEL_20, lines 130110-130113) or
 * succeeds despite an empty chain (letting the FIRST Lexer_ParseValueList
 * call itself execute and fail via the *safe* "argument not found" ->
 * dword_51A964 route -- never touching the crashing v7 dereference --
 * additionally banking 130115-130117). ===================================
 */
TEST(cov5_01_mathmod, token_expect_exact_mismatch_reaches_label20) {
  static _DWORD result_slot[16];
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(result_slot, 0, sizeof result_slot);
  cov5_01_install_safe_argctx(argnode, funcrec, symnode, 0 /* empty chain */);

  /* Required bootstrap for the reserve/atom arenas: even the LABEL_20 exit
   * writes through Rules_AddIntegerValue, which crashes on an
   * uninitialized dword_54DD54 atom table without this. */
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  /* Prime Lexer_TokenExpect's undefined mode-selector to 0 ("exact match"):
   * with an empty (0-argument) chain and a1==2 requested, 0==2 is false, so
   * Lexer_TokenExpect(2) deterministically returns -1, taking Rules_MathMod
   * straight to `LABEL_20` (130110-130113). */
  cov5_01_stack_prime(0);
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

TEST(cov5_01_mathmod, token_expect_atmost_mode_reaches_first_parse_failure) {
  static _DWORD result_slot[16];
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(result_slot, 0, sizeof result_slot);
  cov5_01_install_safe_argctx(argnode, funcrec, symnode, 0 /* empty chain */);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  /* Prime the mode-selector to 2 ("at most N"): with an empty chain (count
   * 0) and a1==2, Lexer_TokenExpect's `v2 != 2 || result > a1` guard is
   * false (0 is <= 2), so it falls through to `return result;` (0), which
   * is != -1. Rules_MathMod then executes `Lexer_ParseValueList(1, &v13,
   * 110, a2)` (130115) for real; Rules_RtnUnknown fails to find argument 1
   * in the empty chain, sets the global dword_51A964 halt flag, and
   * Lexer_ParseValueList's very next check (`if (dword_51A964) return 0;`)
   * returns 0 *before* ever reaching the crashing v7 dereference -- a safe,
   * deterministic way to bank 130116-130117 (the `if (!v3) goto LABEL_20;`)
   * without touching the known hard ceiling. */
  cov5_01_stack_prime(2);
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

/* Documented hard-ceiling attempt (harmless, isolated): a real 2-argument
 * INTEGER chain identical in shape to test_cov3_02.c's already-wired
 * `cov3_02_mathmod` battery. That existing, wired test already proves this
 * shape does not unlock 130121-130156 (see file header); kept here anyway,
 * once, in case this TU's stack layout differs enough to get lucky. */
TEST(cov5_01_mathmod, real_two_arg_chain_hard_ceiling_attempt) {
  static unsigned char argnode[256], node1[32], node2[32];
  static _DWORD funcrec[8], symnode[8];
  static unsigned char val1[32], val2[32];
  static _DWORD result_slot[16];
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(node1, 0, sizeof node1);
  memset(node2, 0, sizeof node2);
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  memset(result_slot, 0, sizeof result_slot);
  *(int *)(val1 + 16) = 17;
  *(int *)(val2 + 16) = 5;
  *(short *)node1 = 1; /* INTEGER */
  *(_DWORD *)(node1 + 2) = (_DWORD)(intptr_t)val1;
  *(_DWORD *)(node1 + 10) = (_DWORD)(intptr_t)node2;
  *(short *)node2 = 1;
  *(_DWORD *)(node2 + 2) = (_DWORD)(intptr_t)val2;
  *(_DWORD *)(node2 + 10) = 0;
  cov5_01_install_safe_argctx(argnode, funcrec, symnode, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

/* =========================================================================
 * Rules_NthFunction (8 uncovered lines targeted: 127809-127817). Same
 * Lexer_ParseValueList hard ceiling as Rules_MathMod for the success block
 * (127814-127817, confirmed unreachable per test_cov4_05.c's gdb-verified
 * finding). But 127809 itself (the call statement `Lexer_ParseValueList(1,
 * v9, 1, a3)`) can be banked safely, the same way as Rules_MathMod's
 * 130116-130117 above: an empty argument chain with Lexer_TokenExpect
 * primed into its "at most" mode so `Lexer_TokenExpect(2) != -1` is true
 * despite the empty chain, letting the first `&&`-chain operand actually
 * execute (and safely fail via the not-found -> dword_51A964 route). ==== */
TEST(cov5_01_nthfunction, token_expect_atmost_mode_reaches_first_parse_call) {
  static _DWORD out[8];
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(out, 0, sizeof out);
  cov5_01_install_safe_argctx(argnode, funcrec, symnode, 0 /* empty chain */);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  cov5_01_stack_prime(2);
  TOUCH(Rules_NthFunction((int)(intptr_t)out, 0, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

/* =========================================================================
 * Rules_MathCsch (7 uncovered lines targeted: 129819-129827). Every one of
 * these lines is gated behind Rules_MathParseSingleArg's own
 * `Lexer_ParseValueList(1, v5, 0, a3)` call succeeding (finding a real
 * argument), which hits the exact same v7 hard ceiling documented above
 * (test_cov4_05.c's "rest/nth/float/cos/exp/acsch" battery already
 * confirmed this identical shape SIGSEGVs reliably, and Rules_MathCsch's
 * own sibling test in test_cov3_07.c reached the same "hard ceiling"
 * verdict). Kept as a single, harmless, best-effort attempt with a real
 * FLOAT-tagged argument node (the most favorable shape observed elsewhere
 * in this suite), per the batch instructions' "even partial success is
 * high value" guidance -- expected to add no new coverage. ============= */
TEST(cov5_01_mathcsch, real_float_arg_hard_ceiling_attempt) {
  static unsigned char argnode[256], node[32], val[32];
  static _DWORD funcrec[8], symnode[8];
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(node, 0, sizeof node);
  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 2.0;
  *(short *)node = 0; /* FLOAT, exact type-match for Rules_MathParseSingleArg's a3==0 request */
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)val;
  *(_DWORD *)(node + 10) = 0;
  cov5_01_install_safe_argctx(argnode, funcrec, symnode, node);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathCsch(0, 0, 0, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

/* =========================================================================
 * Rules_GetAllowedAttributeTokenCode (7 uncovered lines targeted:
 * 179311,179313,179315,179317,179319,179321,179325). A cascade of
 * `strcmp_(vN, keyword)` checks where every vN past the real `a1` argument
 * is a separate decompiler-lost local that is (per the disassembly's own
 * intent) supposed to keep re-reading the same `a1` string pointer. This is
 * the SAME shape as Rules_MarkConstraintAttributeParsed in
 * test_cov3_01.c's COV3_01_MARK_TEST battery -- but unlike that function
 * (whose sibling tests document a 200-iteration natural-register-reuse
 * sweep that never got lucky, per test_cov4_05.c), every prior attempt at
 * THIS function (test_cov2_02.c, test_cov23.c, test_cov3_05.c,
 * test_cov4_04.c) also relied on natural leftover-register luck rather
 * than this pass's explicit large-scale stack-spray helper. Priming the
 * full stack region with the address of a real string whose CONTENT
 * matches the Nth keyword lets every vN resolve to that address: every
 * EARLIER strcmp_ in the cascade compares against a *different* keyword
 * string and mismatches (since the sprayed pointer's content differs), and
 * only the intended Nth check matches, walking exactly as deep as picked.
 * Empirically verified (private scratch build, gdb) this holds for the
 * first four cascade levels (v1/v3/v4/v5, i.e. symbols/strings/lexemes/
 * integers) -- CHECK_EQ'd below. Past that point (v6/v7/v8, i.e. numbers/
 * instance-names/floats) each of the FIVE preceding real strcmp_() calls
 * is itself a sibling call that reuses/zeroes that specific deeper stack
 * slot before we get there (confirmed via gdb: v6 reads back as a hard 0,
 * not our sprayed pointer), so those three stay TOUCH-only best-effort
 * (no false CHECK_EQ failures) rather than a claimed, verified win. ===== */
#define COV5_01_ATTR_TOKEN_TEST(nm, keyword_copy, expected)                 \
  TEST(cov5_01_getallowedattrtoken, nm) {                                   \
    static char kw[32];                                                    \
    strcpy(kw, keyword_copy);                                               \
    cov5_01_stack_prime((int)(intptr_t)kw);                                 \
    CHECK_EQ(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)kw),         \
             expected);                                                     \
  }
#define COV5_01_ATTR_TOKEN_ATTEMPT(nm, keyword_copy)                       \
  TEST(cov5_01_getallowedattrtoken, nm) {                                   \
    static char kw[32];                                                    \
    strcpy(kw, keyword_copy);                                               \
    cov5_01_stack_prime((int)(intptr_t)kw);                                 \
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)kw));           \
  }

COV5_01_ATTR_TOKEN_TEST(allowed_symbols, "allowed-symbols", 2)
COV5_01_ATTR_TOKEN_TEST(allowed_strings, "allowed-strings", 3)
COV5_01_ATTR_TOKEN_TEST(allowed_lexemes, "allowed-lexemes", 111)
COV5_01_ATTR_TOKEN_TEST(allowed_integers, "allowed-integers", 1)
COV5_01_ATTR_TOKEN_ATTEMPT(allowed_numbers, "allowed-numbers")
COV5_01_ATTR_TOKEN_ATTEMPT(allowed_instance_names, "allowed-instance-names")
COV5_01_ATTR_TOKEN_ATTEMPT(allowed_floats, "allowed-floats")

#undef COV5_01_ATTR_TOKEN_TEST
#undef COV5_01_ATTR_TOKEN_ATTEMPT

/* =========================================================================
 * Rules_ExpressionConstraintsCompatible (9 uncovered lines targeted:
 * 116279-116291). Originally hoped that priming the shared v3/v4/v5 stack
 * slot with a real zeroed buffer's address would let both
 * AST_DecrementNodeRefCount and Rules_ConstraintIsUnmatchable resolve
 * safely (see the reasoning kept below), driving both truthy/falsy return
 * branches. Verified against a private scratch build (gdb) that this does
 * NOT hold: `Rules_BuildLHSNodeFromToken(a1)` (line 116278, tag 12 -> the
 * safe `Rules_CreateLHSParseNode()` dispatch) succeeds fine, but the
 * *second* call, `v2 = Rules_ApplyPatternKeywordFlags();` (line 116279,
 * one of our actual targets), ALSO calls `Rules_CreateLHSParseNode()`
 * internally, which crashes on ITS OWN unrelated decompiler-lost local
 * (`v2` inside Rules_CreateLHSParseNode itself, clash95.c:154639) --
 * confirmed to crash on this second call regardless of what our own
 * fixture primes, and confirmed (by removing the spray) that *without* it
 * we instead crash one line earlier, on the FIRST call -- so priming still
 * nets a genuine, verified one-line gain (banking 116279's call site,
 * previously unreached per test_cov4_03.c's equivalent unprimed attempt)
 * even though the hoped-for truthy/falsy split beyond it is unreachable. */
TEST(cov5_01_exprconstraint, safe_token_tag_primed_shared_slot) {
  static _DWORD fake54E694_table[4];
  static _DWORD sharedbuf[16];
  static __int16 tokbuf[8];
  int saved54E694 = g_ConstraintHashTable;

  memset(fake54E694_table, 0, sizeof fake54E694_table);
  memset(sharedbuf, 0, sizeof sharedbuf);
  memset(tokbuf, 0, sizeof tokbuf);
  tokbuf[0] = 12; /* Rules_BuildLHSNodeFromToken's safe Rules_CreateLHSParseNode() dispatch */

  g_ConstraintHashTable = (int)(intptr_t)fake54E694_table;
  Mem_InitReserveBlock(0, 0);

  cov5_01_stack_prime((int)(intptr_t)sharedbuf);
  TOUCH(Rules_ExpressionConstraintsCompatible(tokbuf));

  g_ConstraintHashTable = saved54E694;
}

/* =========================================================================
 * Rules_ConstructCodeFileOpen (10 uncovered lines targeted: 133084,133091,
 * 133093,133094,133098-133103). NOTE: a prior pass's (currently unwired)
 * test_cov4_07.c claims this batch is fully covered "verbatim" with plain
 * TOUCH calls and no stack-spray priming; empirically (private scratch
 * build, gdb) that claim does NOT hold as written:
 *  - a1!=0 (133083-133084): Output_WriteFormatted's a3 (stream) is our own
 *    real a1 argument; asc_508250 has no printf specifiers so the format
 *    engine itself is safe, but CRT_VfprintfLockedWrite's file-lock
 *    acquire (`off_51A56C(lock_key)` -> CRT_LockEnter -> EnterCriticalSection)
 *    reliably crashes in this harness regardless of a1's value/shape
 *    (reproduced identically with test_cov4_04.c's own proven "fake
 *    stream" rig on an unrelated function) -- a pre-existing
 *    compat/decomp_runtime_stubs.c lock-table limitation, not something
 *    this test's fixture can work around. Kept as a harmless, documented
 *    best-effort attempt; 133084 is expected to stay unreached.
 *  - a10!=0 (133091-133094): `Output_WriteFormatted(result, result, result,
 *    asc_508250, ...)` uses the REAL, successfully-opened file handle as
 *    its own stream (no fake-stream construction needed) and asc_508250
 *    has no specifiers -- safe -- PROVIDED `Rules_OpenConstructCodeFile`'s
 *    own decompiler-lost `v8` (gating ITS OWN pair of Output_WriteFormatted
 *    calls, which DO have a missing-vararg vs "%s" mismatch and crash) is
 *    nonzero, skipping that risky inner path. Priming the stack lets us
 *    reach that reliably: confirmed via gdb to complete with zero crashes,
 *    banking all of 133091/133093/133094.
 *  - a10==0 (133098-133103): confirmed via gdb that priming with the same
 *    nonzero value banks 133098-133101 (reaching the first of two trailing
 *    Output_WriteFormatted calls, called with a missing "%s" vararg --
 *    itself a crash, but only after its own call line has already
 *    executed); 133102-133103 stay out of reach behind that same
 *    missing-vararg crash. ================================================ */
TEST(cov5_01_ccfo, a1_nonzero_early_return_hard_ceiling_attempt) {
  static int a5val = 7;
  TOUCH(Rules_ConstructCodeFileOpen(99, "cov5_01", 0, (const char *)(intptr_t)1,
                                     &a5val, 0, 0, 'x', "cov5_01_a9", 0, 0));
}

TEST(cov5_01_ccfo, a10_nonzero_open_success) {
  static const char *a11arr[3];
  static char pathPrefix[512];

  snprintf(pathPrefix, sizeof pathPrefix, "/tmp/cov5_01_ccfo_a10_");
  a11arr[0] = pathPrefix;
  a11arr[1] = (const char *)(intptr_t)3;
  a11arr[2] = (const char *)(intptr_t)4;

  /* Primes Rules_OpenConstructCodeFile's own decompiler-lost `v8` nonzero,
   * skipping its risky inner Output_WriteFormatted pair so it returns the
   * real file handle cleanly; confirmed crash-free via gdb. */
  cov5_01_stack_prime(1);
  TOUCH(Rules_ConstructCodeFileOpen(0, 0, 0, 0, 0, 0, 0, 'y', 0, 1, a11arr));
}

TEST(cov5_01_ccfo, a10_zero_open_success) {
  static int a5val = 3;
  static char pathPrefix[512];

  snprintf(pathPrefix, sizeof pathPrefix, "/tmp/cov5_01_ccfo_a10z_");

  cov5_01_stack_prime(1);
  TOUCH(Rules_ConstructCodeFileOpen(0, pathPrefix, 5, (const char *)(intptr_t)2,
                                     &a5val, 9, 0, 'z', "cov5_01_a9z", 0, 0));
}

/* =========================================================================
 * Shared helper: register one fake, always-in-scope class in the real
 * class hash table (dword_51AD68), reused (renamed) from the currently-
 * unwired test_cov4_07.c's `cov4_07_register_fake_class`. =============== */
static int *cov5_01_register_fake_class(const char *name) {
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

  scopeInfo[4] = (_DWORD)(intptr_t)scopeBits;

  classRecord[0] = (_DWORD)(intptr_t)symbol;
  *((unsigned char *)classRecord + 20) |= 1;
  classRecord[25] = 0;
  classRecord[26] = (_DWORD)(intptr_t)scopeInfo;

  classTable[bucket % 0xA7u] = (_DWORD)(intptr_t)classRecord;
  g_DefclassHashTable = (int)(intptr_t)classTable;

  fakeModule[6] = 0;
  g_Clips_CurrentModule = (int)(intptr_t)fakeModule;

  return (int *)(intptr_t)classRecord;
}

/* =========================================================================
 * Rules_ListInstancesForClassOrModule (5 uncovered lines targeted:
 * 99180,99201,99202,99204,99205). NOTE: a prior pass's (currently unwired)
 * test_cov4_07.c's equivalent fixture (point dword_51AD0C at a fake
 * instance whose offset+44 owning-class is real/always-in-scope, then
 * expect `Rules_GetNextInstanceInScope(0)` to just hand that instance
 * back) does NOT hold up empirically: that function's own body
 * (clash95.c:98754) returns a SEPARATE decompiler-lost local (`v3`) rather
 * than the one it just found (`v1`) whenever its scope-check loop never
 * iterates -- so the "instance" that reaches Instance_PrintNameOfClass is
 * actually uninitialized garbage, not our fixture, unless something else
 * pins that same stack slot to our real instance's address. Priming the
 * stack with our fake instance's own address (confirmed via gdb) fixes
 * that specific hand-off -- Instance_PrintNameOfClass now receives the
 * correct pointer and gets past its own Rules_GetInstanceClassName call
 * (made safe by setting offset+24 bit 1, which test_cov4_07's fixture also
 * omitted) -- but it then crashes one level deeper, inside
 * Class_PrintName's OWN unrelated decompiler-lost `v5` (an unconditional
 * `*v5` dereference, clash95.c:141024) that our priming does not reach
 * (confirmed too deep/overwritten by intervening real calls). So this
 * still only reaches as far as the `Instance_PrintNameOfClass(...)` call
 * line (99200, already covered elsewhere per this batch's own uncovered-
 * lines list) rather than the loop's OWN 99201/99202/99204/99205 tail --
 * kept as the closest verified-improved attempt, isolated and harmless.
 * The `a3!=0` branch (99180) is a separate, genuine hard ceiling
 * (Class_LookupByModule(v11,v10) with both args decompiler-lost) -- kept
 * as a single documented best-effort TOUCH per the batch instructions. == */
TEST(cov5_01_listinstances, class_lookup_by_module_hard_ceiling_attempt) {
  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 1, 0));
}

TEST(cov5_01_listinstances, scope_walk_one_instance) {
  static _DWORD fakeInstance[32];
  int *fakeClass;
  int saved51AD0C = g_Clips_InstanceListHead;
  int saved51AD68 = g_DefclassHashTable;
  int saved51A9B0 = g_Clips_CurrentModule;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  fakeClass = cov5_01_register_fake_class("Cov5_01FakeInstanceOwner");

  memset(fakeInstance, 0, sizeof fakeInstance);
  fakeInstance[11] = (_DWORD)(intptr_t)fakeClass; /* offset44: owning class ptr */
  ((unsigned char *)fakeInstance)[24] |= 2;        /* skip Rules_GetInstanceClassName's own risky deref */
  g_Clips_InstanceListHead = (int)(intptr_t)fakeInstance;

  /* Reconstructs Rules_GetNextInstanceInScope's lost v1->v3 hand-off. */
  cov5_01_stack_prime((int)(intptr_t)fakeInstance);
  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 0, 0));

  g_Clips_InstanceListHead = saved51AD0C;
  g_DefclassHashTable = saved51AD68;
  g_Clips_CurrentModule = saved51A9B0;
}

/* =========================================================================
 * ObjectsCompiler_CloseConstructFileGroup (5 uncovered lines targeted:
 * 168979-168984). Reused verbatim (renamed suite prefix) from the
 * currently-unwired test_cov4_00.c: a content-independent, exactly-
 * 8-iteration do-while over `a2..a2+8`, with the only real risk being
 * Rules_ConstructCodeFileClose crashing on a bad `a6` pointer -- backing it
 * with a real zeroed 4-word buffer (whose first word reads 0) hits that
 * callee's own safe early "return 0;" every iteration, before any of its
 * own file-open/format-write paths are touched. ========================= */
TEST(cov5_01_objcompclose, close_construct_file_group_all_iterations) {
  static int a1buf[16];
  static _DWORD a2buf[16];
  static _DWORD filectx[8];
  int r;

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(filectx, 0, sizeof filectx);

  r = ObjectsCompiler_CloseConstructFileGroup(a1buf, a2buf, 0,
                                               (int)(intptr_t)filectx);
  CHECK_EQ(r, (int)(intptr_t)filectx + 8 * 12);
}

/* =========================================================================
 * Defgeneric_ClearDefgenerics (12 uncovered lines targeted: 161677-161690).
 * The empty-module-list fast path (dword_51A9B0==0 by default) is already
 * exercised elsewhere; the uncovered lines are the loop BODY, which needs
 * Defgeneric_GetNextInModule(0) to return a real, nonzero defgeneric
 * pointer. That walks Class_Enum(0,dword_54E6A4) -> Module_GetItem(0,a2)
 * -> Rules_GetModuleConstructListHead(moduleItem) = *(moduleItem+4): a
 * fake module (offset+8 = item-array ptr) -> item-array[0] (=
 * dword_54E6A4's default 0) = a fake "module construct list" record ->
 * its offset+4 = our fake defgeneric record. `v2` (the outer loop's found
 * defgeneric) is a real, stable value once found this way (never
 * reassigned inside the loop by the decompiler), but `v3`/`v4`/`v6` (fed to
 * Defgeneric_RemoveAllExplicitMethods / Rules_UnlinkListNode /
 * Rules_GetConstructNameString / Rules_ReportCantDeleteItem) are all
 * decompiler-lost siblings meant to keep re-reading that same `v2` --
 * stack-spraying with `v2`'s own address reconstructs that aliasing.
 * Genuine residual risk (documented, not hidden): Defgeneric_
 * RemoveAllExplicitMethods has ITS OWN decompiler-lost local (its `v3`,
 * feeding `v15`) that, when a method-count field is present, drives a
 * `Mem_SmallBlockAlloc(40 * v15)` call -- if that inner local also
 * resolves (via the same "shared stack region" phenomenon) to our
 * primed pointer value, it becomes a large-but-finite allocation size
 * request rather than a small count, which is expected to fail cleanly
 * but is not fully proven safe (test_cov4_02.c and this pass's own
 * research both flag this as the reason two prior passes left this loop
 * alone). Zeroing the fake defgeneric's own method-count field
 * (offset+32) at least skips that function's per-method array walk.
 * Fork+alarm(8) isolation bounds the worst case to a harmless, isolated
 * crash or timeout for this one TEST. ==================================== */
TEST(cov5_01_defgeneric, clear_defgenerics_one_entry_loop_attempt) {
  static _DWORD fakeModule[16];
  static _DWORD itemArray[8];
  static _DWORD moduleItemRecord[8];
  static _DWORD fakeDefgeneric[64];
  int saved51A9B0 = g_Clips_CurrentModule;
  int saved54E6A4 = g_DefgenericModuleItemIndex;

  memset(fakeModule, 0, sizeof fakeModule);
  memset(itemArray, 0, sizeof itemArray);
  memset(moduleItemRecord, 0, sizeof moduleItemRecord);
  memset(fakeDefgeneric, 0, sizeof fakeDefgeneric);

  fakeModule[2] = (_DWORD)(intptr_t)itemArray;         /* offset+8 */
  itemArray[0] = (_DWORD)(intptr_t)moduleItemRecord;   /* dword_54E6A4 index 0 */
  moduleItemRecord[1] = (_DWORD)(intptr_t)fakeDefgeneric; /* offset+4 */
  fakeDefgeneric[4] = 0;  /* offset+16: Class_Enum(v2,...)'s "next" link -> end */
  fakeDefgeneric[8] = 0;  /* offset+32: method count -> 0, skips the risky walk */

  g_DefgenericModuleItemIndex = 0;
  g_Clips_CurrentModule = (int)(intptr_t)fakeModule;

  cov5_01_stack_prime((int)(intptr_t)fakeDefgeneric);
  TOUCH(Defgeneric_ClearDefgenerics());

  g_Clips_CurrentModule = saved51A9B0;
  g_DefgenericModuleItemIndex = saved54E6A4;
}

/* =========================================================================
 * Parser_ParseInstanceQueryNoAction (19 uncovered lines targeted:
 * 182698-182728). Every one of its own possibly-undefined locals (v5-v9)
 * is only ever used as a "channel" argument threaded through
 * Parser_NextToken/Parser_ParseArgument -> Lexer_PeekChar, and
 * IO_RouterMatchesName never actually inspects the channel value (only
 * offset+4 "active" and calling the offset+12 "query" callback, which our
 * fake router answers unconditionally) -- so the garbage channel ints are
 * safe as long as a fake IO router is installed at dword_51A604, the same
 * proven technique test_cov3_02.c already uses for other lexer-driven
 * parse functions. AST_Append(v6,v5) is unconditionally safe regardless of
 * its args (it never dereferences either -- see clash95.c:116769). This is
 * a best-effort attempt at a plausible instance-query token stream; exact
 * lexer token-type codes for bare words/numbers were not independently
 * re-verified against a live build for this pass, so treat any additional
 * coverage here as a bonus rather than a guaranteed win. ================= */
static int cov5_01_iq_lex_query(int a1) {
  (void)a1;
  return 1;
}
static int cov5_01_iq_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}
static const char *cov5_01_iq_lex_seq;
static int cov5_01_iq_lex_pos;
static int cov5_01_iq_lex_read(int a1) {
  unsigned char c;
  (void)a1;
  c = (unsigned char)cov5_01_iq_lex_seq[cov5_01_iq_lex_pos];
  if (c)
    ++cov5_01_iq_lex_pos;
  else
    c = ' ';
  return c;
}
static void cov5_01_iq_install_router(_DWORD *router, const char *seq) {
  memset(router, 0, 16 * sizeof(_DWORD));
  router[1] = 1; /* offset4: active */
  router[3] = (_DWORD)(intptr_t)cov5_01_iq_lex_query; /* offset12 */
  router[6] = (_DWORD)(intptr_t)cov5_01_iq_lex_read;  /* offset24 */
  router[7] = (_DWORD)(intptr_t)cov5_01_iq_lex_skip;  /* offset28 */
  g_IO_RouterListHead = (int)(intptr_t)router;
  cov5_01_iq_lex_seq = seq;
  cov5_01_iq_lex_pos = 0;
}

TEST(cov5_01_parseinstancequery, no_action_two_restrictions_then_close) {
  static _DWORD router[16];
  static unsigned char safebuf[256];
  static _DWORD a1construct[16];
  int saved604 = g_IO_RouterListHead;

  memset(safebuf, 0, sizeof safebuf);
  memset(a1construct, 0, sizeof a1construct);
  cov5_01_iq_install_router(router, "(a 1) )");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  /* Prime every "channel"/out-param local possibly read across this call
   * chain to point at a real, writable, zeroed buffer, protecting any
   * incidental garbage-pointer write (e.g. Parser_ParseArgument's error-
   * flag out-param) without affecting the router-driven token stream
   * itself (which is entirely content-based, not pointer-based). */
  cov5_01_stack_prime((int)(intptr_t)safebuf);
  TOUCH(Parser_ParseInstanceQueryNoAction((int)(intptr_t)a1construct, 0));

  g_IO_RouterListHead = saved604;
}

TEST(cov5_01_parseinstancequery, no_action_immediate_close_paren) {
  static _DWORD router[16];
  static unsigned char safebuf[256];
  static _DWORD a1construct[16];
  int saved604 = g_IO_RouterListHead;

  memset(safebuf, 0, sizeof safebuf);
  memset(a1construct, 0, sizeof a1construct);
  cov5_01_iq_install_router(router, ")");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_01_stack_prime((int)(intptr_t)safebuf);
  TOUCH(Parser_ParseInstanceQueryNoAction((int)(intptr_t)a1construct, 0));

  g_IO_RouterListHead = saved604;
}
