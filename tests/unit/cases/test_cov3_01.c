/* cov3_01: third-pass coverage additions for a batch of partially-covered
 * functions (Rules_MultifieldReplaceRange, Rules_FormatCountConversionSpecs,
 * Rules_BuildFactAddressList, Rules_ConstructCodeFileOpen,
 * Rules_MarkConstraintAttributeParsed, Parser_ParseNumericFormCompat,
 * Rules_MathLog, Rules_RefreshAgendaCommand, Rules_PrintMultifieldRange,
 * UnitSlot_CycleOrderState, Rules_ReadLineWithEscaping,
 * MessageHandler_PreviewSendForSymbol, Output_WriteFormatted,
 * Rules_CreateJoinPartialMatch, Rules_HostStringp, Class_SuperclassPCommand,
 * Building_CalcGarrisonStrength).
 *
 * KEY TECHNIQUE (new this pass): several of these functions read a
 * genuinely-uninitialized decompiler local ("variable 'vN' is possibly
 * undefined" in clash95.c) at a point where the *previous* pass could only
 * shrug and call it "unpredictable". Empirically (verified with a private,
 * isolated compile of clash95.c against this same test harness shape,
 * outside the shared build) that leftover value is just whatever was last
 * written to that exact stack slot by an earlier sibling call in the same
 * test body -- because every sibling call from the same TEST(...) function
 * starts from the *same* stack pointer. So calling a helper that sprays a
 * large volatile array with a chosen value, immediately before the target
 * call, reliably makes that uninitialized local read back as the sprayed
 * value. This unlocks whole branches (and in one case the entire back half
 * of a function) that were previously unreachable without crashing.
 * Kept deliberately generous in size (65536 ints = 256KB) so it comfortably
 * covers the stack depth used by Mem_InitReserveBlock/Rules_InitAtomTables/
 * the anchor-chain setup that typically precedes the target call. */
static void cov3_01_stack_prime(int val) {
  volatile int buf[65536];
  int i;
  for (i = 0; i < 65536; i++) {
    buf[i] = val;
  }
}

/* =====================================================================
 * Rules_MultifieldReplaceRange (35/68 covered, 33 uncovered): the
 * remaining lines are the entire back half of the function, gated behind
 * `v15 = *(_DWORD *)(v14 + 12);` where v14 is undefined -- this crashed
 * immediately for every prior test, truncating coverage right there.
 * Priming with the address of a real (zeroed) multifield-storage buffer
 * makes v14 resolve to that buffer, so v15 starts at 0 (a sane "no prior
 * elements copied" state) and the rest of the function runs for real.
 * Two shapes cover the remaining branches:
 *   (1) a5 itself a multifield -> both `if (a5[1] == 4)` sites true, and
 *       a3 == source count so there's nothing left for the final tail
 *       copy loop.
 *   (2) a5 a scalar (a5[1] != 4) with a3 < source count, so the tail copy
 *       loop (previously wholly unreached) has real trailing elements to
 *       carry over.
 * ===================================================================== */
TEST(cov3_01_multifieldreplace, primed_multifield_splice_full_run) {
  static _DWORD storage[64], storage2[64];
  static _DWORD a1buf[8], a2buf[8], a5buf[8];
  memset(storage, 0, sizeof storage);
  memset(storage2, 0, sizeof storage2);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a5buf, 0, sizeof a5buf);

  /* source multifield: begin=0, end=2 -> count 3 */
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0;
  a2buf[4] = 2;

  /* replacement value is itself a multifield (type tag 4): begin=0, end=1
   * -> count 2, splicing 2 elements in place of the replaced range. */
  a5buf[1] = 4;
  a5buf[2] = (_DWORD)(intptr_t)storage2;
  a5buf[3] = 0;
  a5buf[4] = 1;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov3_01_stack_prime((int)(intptr_t)storage);
  /* a3=3 (range end == source count), a4=2 (range start): prefix of 1
   * element copied, then the whole rest of the function runs to
   * completion (no tail-copy trip needed since a3 == source count). */
  TOUCH(Rules_MultifieldReplaceRange(a1buf, a2buf, 3, 2, a5buf, 0));
}

TEST(cov3_01_multifieldreplace, primed_scalar_splice_with_tail_copy) {
  static _DWORD storage3[64];
  static _DWORD a1buf3[8], a2buf3[8], a5buf3[8];
  memset(storage3, 0, sizeof storage3);
  memset(a1buf3, 0, sizeof a1buf3);
  memset(a2buf3, 0, sizeof a2buf3);
  memset(a5buf3, 0, sizeof a5buf3);

  /* source multifield: 5 elements (indices 0..4) */
  a2buf3[2] = (_DWORD)(intptr_t)storage3;
  a2buf3[3] = 0;
  a2buf3[4] = 4;

  /* a5 is a SCALAR (a5[1] != 4) -> exercises the else branches at the v12
   * formula and the splice site, and leaves fewer elements written than
   * the output length, which forces the final tail-copy loop to run for
   * the 2 leftover source elements after the replaced range. */
  a5buf3[1] = 2;
  a5buf3[2] = 0x1234;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov3_01_stack_prime((int)(intptr_t)storage3);
  /* a3=3 (range end), a4=2 (range start): replace elements [1..2] with the
   * scalar, leaving elements 3,4 for the tail copy loop. */
  TOUCH(Rules_MultifieldReplaceRange(a1buf3, a2buf3, 3, 2, a5buf3, 0));
}

/* =====================================================================
 * Rules_FormatCountConversionSpecs (4/20 covered): the existing tests only
 * ever reach the immediate "no argument supplied" failure return. The
 * function's *own* call is `Lexer_ParseValueList(2, v7, 3, a2)` -- note
 * the literal `2`: it asks Rules_RtnUnknown for the *second* positional
 * argument, so a chain with only one real node (as prior attempts used)
 * always dead-ends in Rules_RtnUnknown's "not found" branch. Providing a
 * 2-node chain (a placeholder first node, a real STRING second node)
 * lets Rules_RtnUnknown succeed. That still isn't enough on its own:
 * Lexer_ParseValueList's *own* first real check is
 * `a3 == *(_DWORD *)(v7 + 4)` with v7 undefined -- priming that address to
 * point at a small buffer whose word at +4 equals the requested a3 (3 ==
 * STRING) makes the whole call succeed, unlocking the entire "scan the
 * format string for %-specs" loop and both count-match/mismatch endings. */
TEST(cov3_01_formatcount, primed_two_node_chain_mismatch_count) {
  static _DWORD anchor[16];
  static _DWORD node1[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  static char fmt[16] = "a%dbc";
  static _DWORD lexTarget[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(node1, 0, sizeof node1);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  memset(lexTarget, 0, sizeof lexTarget);
  lexTarget[1] = 3; /* so *(_DWORD*)(v7+4) == 3, matching the a3==3 (STRING) request */

  *(short *)termBuf = 3; /* STRING tag, matches a3==3 */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0; /* no third arg */
  valnode[4] = (_DWORD)(intptr_t)fmt;    /* +16: string payload pointer */

  *(_DWORD *)((char *)node1 + 10) = (int)(intptr_t)termBuf; /* node1 -> node2(termBuf) */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)node1;   /* chain head -> node1 */

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  cov3_01_stack_prime((int)(intptr_t)lexTarget);
  /* a1=2 expected specs, format has 1 -> count-mismatch error branch */
  TOUCH(Rules_FormatCountConversionSpecs(2, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov3_01_formatcount, primed_two_node_chain_matching_count) {
  static _DWORD anchor2[16];
  static _DWORD node1b[16];
  static _DWORD termBuf2[64];
  static _DWORD valnode2[8];
  static char fmt2[16] = "no-percent-signs";
  static _DWORD lexTarget2[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor2, 0, sizeof anchor2);
  memset(node1b, 0, sizeof node1b);
  memset(termBuf2, 0, sizeof termBuf2);
  memset(valnode2, 0, sizeof valnode2);
  memset(lexTarget2, 0, sizeof lexTarget2);
  lexTarget2[1] = 3;

  *(short *)termBuf2 = 3;
  *(_DWORD *)((char *)termBuf2 + 2) = (int)(intptr_t)valnode2;
  *(_DWORD *)((char *)termBuf2 + 10) = 0;
  valnode2[4] = (_DWORD)(intptr_t)fmt2;

  *(_DWORD *)((char *)node1b + 10) = (int)(intptr_t)termBuf2;
  *(_DWORD *)((char *)anchor2 + 6) = (int)(intptr_t)node1b;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor2;
  cov3_01_stack_prime((int)(intptr_t)lexTarget2);
  /* a1=2 expected specs (a1-2==0), format has 0 -> count-match success
   * return branch (previously entirely unreached). */
  TOUCH(Rules_FormatCountConversionSpecs(2, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* =====================================================================
 * Rules_MarkConstraintAttributeParsed (23/32 covered): a cascade of
 * `strcmp_(vN, aKeyword)` checks where every vN past the first is a
 * separate undefined local that (per the decompiler's own lost-SSA
 * comments) is supposed to keep re-reading the same `a2` argument at each
 * successive level. Priming every one of those stack slots with the
 * address of the actual keyword string passed in reconstructs that
 * intended aliasing, letting a single call walk as deep into the
 * if/else-if chain as its keyword dictates. Sweeping all ten real
 * keywords plus one non-matching name exercises effectively the whole
 * function (every prior test only ever drove the shallow, un-primed,
 * garbage-dependent depth). */
#define COV3_01_MARK_TEST(nm, str)                                          \
  TEST(cov3_01_markconstraint, nm) {                                        \
    static _BYTE a1buf[4];                                                  \
    static char kw[32];                                                     \
    memset(a1buf, 0, sizeof a1buf);                                         \
    strcpy(kw, str);                                                        \
    cov3_01_stack_prime((int)(intptr_t)kw);                                 \
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)kw));   \
  }

COV3_01_MARK_TEST(kw_range, "range")
COV3_01_MARK_TEST(kw_type, "type")
COV3_01_MARK_TEST(kw_cardinality, "cardinality")
COV3_01_MARK_TEST(kw_allowed_symbols, "allowed-symbols")
COV3_01_MARK_TEST(kw_allowed_strings, "allowed-strings")
COV3_01_MARK_TEST(kw_allowed_lexemes, "allowed-lexemes")
COV3_01_MARK_TEST(kw_allowed_integers, "allowed-integers")
COV3_01_MARK_TEST(kw_allowed_floats, "allowed-floats")
COV3_01_MARK_TEST(kw_allowed_numbers, "allowed-numbers")
COV3_01_MARK_TEST(kw_allowed_values, "allowed-values")
COV3_01_MARK_TEST(kw_no_match, "zzz-no-match-cov3-01")

#undef COV3_01_MARK_TEST

/* =====================================================================
 * Rules_RefreshAgendaCommand (4/10 covered): gated behind
 * `Lexer_TokenExpect(1)`, whose own undefined `v2` selects an "exact
 * count" vs "at-least count" comparison mode. Priming that slot to 0
 * (exact mode) together with a real 1-node argument chain makes
 * Lexer_TokenExpect(1) return 1, entering the `result == 1` branch
 * (Rules_GetModuleNameArg + Rules_RefreshAgenda). Priming to 1
 * ("at-least" mode) with a 2-node chain makes it return 2 (> requested
 * 1), landing in the previously-unreached `else` branch
 * (Module_GetCurrent + Rules_RefreshAgenda). Both calls go on to fault a
 * frame or two down in unrelated CRT/module code once inside the callee
 * -- isolated per TEST so that's harmless; the point is banking this
 * function's own branch lines, which it does. */
TEST(cov3_01_refreshagenda, primed_exact_match_one_arg) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 2;
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0; /* argcount == 1 */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  cov3_01_stack_prime(0); /* Lexer_TokenExpect's mode local -> 0 (exact) */
  TOUCH(Rules_RefreshAgendaCommand(0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov3_01_refreshagenda, primed_at_least_mode_two_args) {
  static _DWORD anchor2[16];
  static _DWORD termBuf2[64];
  static _DWORD termBuf3[64];
  static _DWORD valnode2[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor2, 0, sizeof anchor2);
  memset(termBuf2, 0, sizeof termBuf2);
  memset(termBuf3, 0, sizeof termBuf3);
  memset(valnode2, 0, sizeof valnode2);
  *(short *)termBuf2 = 2;
  *(_DWORD *)((char *)termBuf2 + 2) = (int)(intptr_t)valnode2;
  *(_DWORD *)((char *)termBuf2 + 10) = (int)(intptr_t)termBuf3; /* 2nd arg node */
  *(short *)termBuf3 = 2;
  *(_DWORD *)((char *)termBuf3 + 2) = (int)(intptr_t)valnode2;
  *(_DWORD *)((char *)termBuf3 + 10) = 0;
  *(_DWORD *)((char *)anchor2 + 6) = (int)(intptr_t)termBuf2;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor2;
  cov3_01_stack_prime(1); /* mode -> 1 ("at least"), count(2) > a1(1) */
  TOUCH(Rules_RefreshAgendaCommand(0.0));
  g_ClipsCurrentExpression = saved;
}

/* =====================================================================
 * Rules_HostStringp (4/7 covered): identical Lexer_TokenExpect(1) +
 * Rules_RtnUnknown(1, v3, a1) shape as above, gated further behind
 * `v3[1] == 3`. A primed 1-node STRING-tagged chain (mode 0 == exact)
 * makes Lexer_TokenExpect succeed and Rules_RtnUnknown populate v3[1]==3,
 * reaching the previously-unreached `return 1;`. ===================== */
TEST(cov3_01_hoststringp, primed_string_arg_matches) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static _DWORD valnode[8];
  int saved = g_ClipsCurrentExpression;

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  memset(valnode, 0, sizeof valnode);
  *(short *)termBuf = 3; /* STRING tag, matches v3[1]==3 */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)valnode;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  cov3_01_stack_prime(0);
  CHECK_EQ(Rules_HostStringp(0.0), 1);
  g_ClipsCurrentExpression = saved;
}

/* =====================================================================
 * Building_CalcGarrisonStrength (2/4 covered): `Building_CountGarrison(v3)`
 * with v3 undefined faulted immediately in every prior attempt, before
 * even that call-site line executed. Priming with a real (zeroed) buffer
 * address gets the call itself to execute (banking that line); it still
 * faults a frame down inside Building_CountGarrison's own body on a
 * decompiler-lost value, which is outside this batch's function -- the
 * per-test isolation absorbs that harmlessly. ===================== */
TEST(cov3_01_garrison, primed_call_site) {
  static _DWORD scratch[256];
  memset(scratch, 0, sizeof scratch);
  cov3_01_stack_prime((int)(intptr_t)scratch);
  TOUCH(Building_CalcGarrisonStrength((int)(intptr_t)scratch, 1));
}

/* =====================================================================
 * Rules_CreateJoinPartialMatch (13/16 covered): existing tests
 * (test_cov13.c, test_cov2_01.c) already drive three of the four
 * action/join combinations (no-action+no-join, action+direct-join-match,
 * no-action+join-chain do-while). Round out the 2x2 matrix with the two
 * remaining combinations: action set together with the join do-while
 * chain, and no action together with a direct (single-call) join match. */
TEST(cov3_01_createjoinpartialmatch, action_and_join_chain_do_while) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], join1[16], join2[16];
  Mem_InitReserveBlock(0, 0);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(join1, 0, sizeof join1);
  memset(join2, 0, sizeof join2);

  a3buf[9] = 1; /* nonzero action -> Rules_AddActivation branch */
  a3buf[5] = (_DWORD)(intptr_t)join1;
  join1[4] = 0; /* join1+16 != a3 -> do-while branch */
  join1[7] = (_DWORD)(intptr_t)join2;
  join2[4] = 0;
  join2[7] = 0; /* chain ends */

  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
}

TEST(cov3_01_createjoinpartialmatch, no_action_direct_join_match) {
  static _DWORD a1buf[16], a2buf[16], a3buf[16], joinbuf[16];
  Mem_InitReserveBlock(0, 0);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(joinbuf, 0, sizeof joinbuf);

  a3buf[9] = 0; /* no action -> skip Rules_AddActivation */
  a3buf[5] = (_DWORD)(intptr_t)joinbuf;
  joinbuf[4] = (_DWORD)(intptr_t)a3buf; /* join+16 == a3 -> single-call branch */
  joinbuf[7] = 0;

  TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
}

/* =====================================================================
 * Rules_PrintMultifieldRange (12/17 covered): existing tests only ever
 * give it a loop trip count of exactly 0 or 1. Widen the source range so
 * the internal do-while has more than one element to walk (the loop's
 * continuation depends on `v8 = v10 + 1` with v10 undefined on the first
 * pass, but v10 is only ever used arithmetically here -- never
 * dereferenced -- so a larger range is safe to try regardless of what
 * garbage value it resolves to). ===================== */
TEST(cov3_01_printmultifieldrange, wider_range_multi_element) {
  static unsigned char buf[512];
  static const char logical[] = "stdout";
  memset(buf, 0, sizeof buf);
  TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 2, 1));
  TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 3, 0));
}

/* =====================================================================
 * Rules_ReadLineWithEscaping (5/9 covered): the existing test only drives
 * the immediate EOF guard. Registering `a1` as the fast-path internal
 * stream (dword_51A608), backed by a real readable byte buffer, drives
 * Lexer_PeekChar into returning genuine characters, which exercises the
 * while-loop body's Str_AppendCharEscaping calls. Isolated in its own
 * TEST since Str_AppendCharEscaping's own allocation path a frame down is
 * outside this batch and may behave unpredictably. ===================== */
TEST(cov3_01_readline, real_stream_chars) {
  static _DWORD strm[4]; /* {current-ptr, remaining-count} */
  static unsigned char text[8] = "ab";
  int savedStream = g_IO_FastLoadFilePtr;
  int a2out = 0;
  unsigned int a3out = 0;

  memset(strm, 0, sizeof strm);
  strm[0] = (_DWORD)(intptr_t)text;
  strm[1] = 2; /* remaining count */

  Mem_InitReserveBlock(0, 0);
  g_IO_FastLoadFilePtr = (int)(intptr_t)strm;
  TOUCH(Rules_ReadLineWithEscaping((int)(intptr_t)strm, &a2out, &a3out, 0));
  g_IO_FastLoadFilePtr = savedStream;
}

/* =====================================================================
 * Rules_BuildFactAddressList (15/27 covered): reads a chain of several
 * genuinely-undefined locals (v0 through v15) starting from the very
 * first statement (`Module_BeginEnum(); v1 = v0;`). Unlike the single
 * clean "v14" case in Rules_MultifieldReplaceRange, this function's
 * first write-through-undefined-pointer site (`v3[1] = 4;`) lands in a
 * narrow few-byte gap between two sibling call frames that the stack-
 * priming spray could not be made to reach in local experimentation
 * (confirmed via gdb: the target address sits just above where the spray
 * buffer's own top element lands, in the small frame-boundary region
 * rather than within the sprayed range). Kept as the existing
 * bootstrap-only best-effort call; still useful for the lines up through
 * Module_BeginEnum(). ===================== */
TEST(cov3_01_buildfactaddresslist, bootstrap_cold_call) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BuildFactAddressList());
}
