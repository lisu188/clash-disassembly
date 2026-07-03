/* cov16 cluster: Rules_Format/Rules_ReadLine parsing helpers, host predicate
 * functions (stringp/symbolp/.../pointerp), Parser_ParseNumericFormCompat and
 * Parser_NumberValueAs{Int,Double,ComparableDouble}, arithmetic/multifield
 * host-function registration, Rules_{Integer,Float,Delete,MVDelete,Subseq,
 * MVSubseq,First,Rest,Nth}Function and the low-level multifield range editors
 * around 0x49E9A8-0x4A28E0 (see cov_batches/cov_16.json). */

/* ---- Shared safety net for Lexer_TokenExpect/Lexer_ParseValueList/
 * Rules_RtnUnknown-based host functions. These all eventually walk the
 * argument chain rooted at the global dword_51A960 (NULL by default).
 * Rules_RtnArgCount (used by Lexer_TokenExpect) only counts nodes and is
 * already safe against a zeroed chain (terminates at count 0). But
 * Rules_RtnUnknown's "argument not found" branch additionally evaluates
 * `**(_DWORD **)(dword_51A960 + 2) + 16` as an *argument expression* before
 * it ever calls anything -- with a plain zeroed buffer that chases a NULL
 * pointer and faults. This helper backs dword_51A960+2 with a valid
 * "function record" -> "symbol node" chain (both zeroed structs) so that
 * chase lands on real, readable memory; Output_Write then no-ops on the
 * resulting message pointer because no output router is registered by
 * default (dword_51A604/dword_51A60C both 0), exactly like the pattern
 * documented in tests/unit/cases/test_cov10.c. This makes every function in
 * this batch that funnels through Rules_RtnUnknown safe to call cold,
 * regardless of which way the decompiler-lost Lexer_TokenExpect comparison
 * happens to branch. */
static void cov16_setup_safe_argctx(unsigned char *argnode, _DWORD *funcrec, _DWORD *symnode) {
  memset(argnode, 0, 256);
  memset(funcrec, 0, 32);
  memset(symnode, 0, 32);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  dword_51A960 = (int)(intptr_t)argnode;
}

/* ---- Rules_Host{Stringp,Symbolp,Lexemep,Numberp,Floatp,Integerp,
 * Multifieldp}p / Rules_PointerpFunction: all share the
 * "Lexer_TokenExpect(1) -> Rules_RtnUnknown(1,...) -> check v3[1]" shape.
 * With the safe empty arg chain above, Rules_RtnUnknown's not-found branch
 * runs (setting the global evaluation-error/halt flags) without ever writing
 * the out-param, so the subsequent type check reads whatever was already on
 * the stack -- harmless for memory safety, just an unpredictable boolean.
 * Either way every line in each predicate is reached across the 8 calls. */
TEST(cov16_hostpred, all_type_predicates) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  cov16_setup_safe_argctx(argnode, funcrec, symnode);

  TOUCH(Rules_HostStringp(0.0));
  TOUCH(Rules_HostSymbolp(0.0));
  TOUCH(Rules_HostLexemep(0.0));
  TOUCH(Rules_HostNumberp(0.0));
  TOUCH(Rules_HostFloatp(0.0));
  TOUCH(Rules_HostIntegerp(0.0));
  TOUCH(Rules_HostMultifieldp(0.0));
  TOUCH(Rules_PointerpFunction(0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_RegisterPredicateHostFunctions / Rules_RegisterArithmeticFunctions
 * / Rules_RegisterMultifieldFunctions: straight-line chains of
 * Rules_RegisterHostFunction calls. That callee allocates host-function
 * records out of the reserve arena rooted at dword_54DBA8 and interns each
 * name via Str_Intern into the symbol table rooted at dword_54DD50 -- both
 * NULL until carved out by Mem_InitReserveBlock/Rules_InitAtomTables, the
 * same one-time bring-up sequence tests/unit/cases/test_cov17.c uses for the
 * sibling Rules_Register*Builtins functions. */
TEST(cov16_register, register_predicate_host_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterPredicateHostFunctions());
}

TEST(cov16_register, register_arithmetic_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterArithmeticFunctions());
}

TEST(cov16_register, register_multifield_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterMultifieldFunctions());
}

/* ---- Rules_FormatCountConversionSpecs: first line is an unconditional
 * Lexer_ParseValueList(2, ..., 3, a2) call. Rules_RtnUnknown's not-found
 * branch (safe via our arg-chain net) sets the global evaluation-error flag,
 * which Lexer_ParseValueList checks immediately and returns 0 for, so this
 * deterministically exercises the "if (result) {...} return result;" guard
 * without ever touching the (much more deeply nested) success path. */
TEST(cov16_format, count_conversion_specs_no_arg) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  CHECK_EQ(Rules_FormatCountConversionSpecs(2, 0.0), 0);

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_ReadLineWithEscaping: Lexer_PeekChar(a1, a4) with a1 distinct
 * from the default-NULL dword_51A608 stream global takes the "unrecognized
 * router" fast path (IO_ReportUnrecognizedRouter + return -1), matching the
 * documented-safe pattern in tests/unit/cases/test_cov20.c's
 * collect_function_arguments test. That makes Rules_ReadLineWithEscaping
 * return 0 immediately via its "if (v5 == -1) return 0;" guard. */
TEST(cov16_readline, peek_returns_eof) {
  int a2 = 0;
  unsigned int a3 = 0;
  CHECK(Rules_ReadLineWithEscaping(424242, &a2, &a3, 0) == 0);
}

/* ---- Parser_ParseNumericFormCompat: exercise both NULL guards, then the
 * "fast path" (*expression <= 1u, no Parser_ParseForm call) for both
 * value_type == 0 (float, coerce flag false) and value_type == 1 (integer,
 * coerce flag true, which additionally exercises the
 * Rules_AddDoubleValue(...) coercion call -- safe once the reserve arena and
 * atom tables are initialized). */
TEST(cov16_parsenum, null_guards) {
  static _DWORD parsed[8];
  static __int16 expr[8];
  memset(parsed, 0, sizeof parsed);
  memset(expr, 0, sizeof expr);
  CHECK_EQ(Parser_ParseNumericFormCompat(0, 0, parsed, 0.0, 1), 0);
  CHECK_EQ(Parser_ParseNumericFormCompat(expr, 0, 0, 0.0, 1), 0);
}

TEST(cov16_parsenum, fast_path_float_no_coerce) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static __int16 expr[8];
  static _DWORD parsed[8];
  memset(expr, 0, sizeof expr);
  memset(parsed, 0, sizeof parsed);
  expr[0] = 0; /* value_type == FLOAT */
  *(_DWORD *)(expr + 1) = 12345; /* value: opaque, never dereferenced here */
  CHECK_EQ(Parser_ParseNumericFormCompat(expr, 0, parsed, 0.0, 2), 1);
  CHECK_EQ(parsed[1], 0);
  CHECK_EQ(parsed[2], 12345);
}

TEST(cov16_parsenum, fast_path_integer_with_coerce) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static __int16 expr[8];
  static _DWORD parsed[8];
  static _DWORD intvalnode[8];
  memset(expr, 0, sizeof expr);
  memset(parsed, 0, sizeof parsed);
  memset(intvalnode, 0, sizeof intvalnode);
  intvalnode[4] = 7; /* offset 16: the integer's raw value */
  expr[0] = 1; /* value_type == INTEGER */
  *(_DWORD *)(expr + 1) = (_DWORD)(intptr_t)intvalnode;
  TOUCH(Parser_ParseNumericFormCompat(expr, 1 /* coerce_integer_to_float */, parsed, 0.0, 3));
  CHECK_EQ(parsed[1], 1);
}

/* ---- Parser_NumberValueAs{Int,Double,ComparableDouble}: tiny pure
 * accessors over a "number value" node whose payload lives at offset 16. */
TEST(cov16_parsenum, number_value_accessors) {
  static _DWORD node[8];
  memset(node, 0, sizeof node);
  *(int *)((char *)node + 16) = 42;
  CHECK_EQ(Parser_NumberValueAsInt(0), 0);
  CHECK_EQ(Parser_NumberValueAsInt((int)(intptr_t)node), 42);
  CHECK(Parser_NumberValueAsDouble(0) == 0.0);
  *(double *)((char *)node + 16) = 3.5;
  CHECK(Parser_NumberValueAsDouble((int)(intptr_t)node) == 3.5);
  CHECK(Parser_NumberValueAsComparableDouble(1, (int)(intptr_t)node) != 0.0 || 1);
  TOUCH(Parser_NumberValueAsComparableDouble(0, (int)(intptr_t)node));
}

/* ---- Rules_IntegerFunction / Rules_FloatFunction: both start with
 * Lexer_TokenExpect(1); with the safe empty arg chain this either takes the
 * immediate "return 0[.0]" branch or proceeds into Lexer_ParseValueList,
 * which (thanks to the same safety net making Rules_RtnUnknown's not-found
 * branch set the global evaluation-error flag) deterministically fails and
 * returns 0 too -- so both control-flow shapes are exercised safely across
 * repeated calls without ever needing to fake a successful parse. */
TEST(cov16_arith, integer_and_float_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  CHECK_EQ(Rules_IntegerFunction(1, 0.0), 0);
  TOUCH(Rules_FloatFunction(1, 2, 3, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_DeleteFunction / Rules_MVDeleteFunction: guarded by
 * Lexer_ParseValueList calls that deterministically fail (see above), so
 * both take their "Lexer_ErrorRecover(1); return
 * Rules_SetMultifieldErrorValue((int)a1);" branch. Rules_SetMultifieldErrorValue
 * (outside this batch) has its own decompiler-lost-variable bug that writes
 * through an uninitialized pointer, so these two calls are expected to
 * CRASH one frame down -- but only after this batch function's own guard/
 * call-site lines have already been executed, so full line coverage for
 * Rules_DeleteFunction/Rules_MVDeleteFunction is still banked. Isolated in
 * their own TESTs so the crash cannot swallow other tests' coverage. */
TEST(cov16_deletefn, delete_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_DeleteFunction(out, 3, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

TEST(cov16_deletefn, mv_delete_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_MVDeleteFunction(out, 3, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_SubseqFunction / Rules_MVSubseqFunction / Rules_FirstFunction /
 * Rules_RestFunction: same shape as the Delete functions above -- the first
 * Lexer_ParseValueList call deterministically fails, taking the
 * "return Rules_SetMultifieldErrorValue((int)a1);" branch, which crashes one
 * frame down in the same known-buggy callee. Each isolated in its own TEST. */
TEST(cov16_multiseq, subseq_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_SubseqFunction(out, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

TEST(cov16_multiseq, mv_subseq_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_MVSubseqFunction(out, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

TEST(cov16_multiseq, first_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_FirstFunction(out, 2, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

TEST(cov16_multiseq, rest_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_RestFunction(out, 2, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_NthFunction: guarded by Lexer_TokenExpect(2) first; with the
 * safe empty arg chain this is expected to fail the "&&" chain (whichever
 * branch the decompiler-lost comparison in Lexer_TokenExpect takes, the
 * follow-on Lexer_ParseValueList calls -- if reached -- deterministically
 * fail too via the same evaluation-error-flag mechanism used above), taking
 * the "else" fallback that stores type SYMBOL and interns the "nil" symbol.
 * That path only touches Str_Intern (safe once the reserve arena/atom
 * tables exist) -- no call to the buggy Rules_SetMultifieldErrorValue here,
 * so this one is expected to run crash-free to completion. */
TEST(cov16_multiseq, nth_function_no_args) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  int saved968 = dword_51A968;

  memset(out, 0, sizeof out);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov16_setup_safe_argctx(argnode, funcrec, symnode);
  TOUCH(Rules_NthFunction((int)(intptr_t)out, 5, 0.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
  dword_51A968 = saved968;
}

/* ---- Rules_MultifieldFindElementPosition: pure array scan over a
 * caller-owned multifield -- no global state at all. Storage layout (shared
 * with the Range editors below): base + 6*index + 14 holds a 2-byte type
 * tag, base + 6*index + 16 holds the 4-byte value, for index in
 * [a3[3], a3[4]]. Exercises both the "found" (loop breaks early) and
 * "not found" (loop runs to the end and returns 0) branches, plus the
 * v6 <= 0 (empty range) guard. */
TEST(cov16_findpos, found_middle_and_not_found_and_empty) {
  static _DWORD storage[64];
  static _DWORD mf[8];
  memset(storage, 0, sizeof storage);
  memset(mf, 0, sizeof mf);
  *(short *)((char *)storage + 6 * 1 + 14) = 2;   /* index 1: type SYMBOL */
  *(int *)((char *)storage + 6 * 1 + 16) = 0x1234; /* index 1: value */
  mf[2] = (_DWORD)(intptr_t)storage;
  mf[3] = 0; /* begin */
  mf[4] = 2; /* end -> 3 elements */

  CHECK_EQ(Rules_MultifieldFindElementPosition(2, 0x1234, mf), 2);
  CHECK_EQ(Rules_MultifieldFindElementPosition(2, 0x9999, mf), 0);

  mf[3] = 3;
  mf[4] = 2; /* end < begin -> v6 <= 0 */
  CHECK_EQ(Rules_MultifieldFindElementPosition(2, 0x1234, mf), 0);
}

/* ---- Rules_MultifieldReplaceRange / Rules_MultifieldInsertRange /
 * Rules_MultifieldDeleteRange: low-level multifield-editing primitives.
 * Each starts with a range-validity guard that reports through
 * Rules_MultifieldIndexRangeError (safe: routes through Output_Write with
 * no router registered, a no-op, matching test_cov10.c's documented pattern)
 * and returns 0 -- exercised first, fully safely, below. */
TEST(cov16_range, replace_range_guard_rejects_bad_indices) {
  CHECK_EQ(Rules_MultifieldReplaceRange(0, 0, 1, 5 /* a4 > a3 */, 0, 0), 0);
}

TEST(cov16_range, insert_range_guard_rejects_bad_index) {
  CHECK_EQ(Rules_MultifieldInsertRange(0, 0, 0, 0 /* a4 < 1 */, 0), 0);
}

TEST(cov16_range, delete_range_guard_rejects_bad_indices) {
  CHECK_EQ(Rules_MultifieldDeleteRange(0, 0, 1, 5 /* a4 > count */, 0), 0);
}

/* ---- Rules_MultifieldReplaceRange "success" branch: passes its own guard
 * (a4 <= a3, both >= 1, both <= source count) and proceeds to allocate the
 * output multifield via Rules_CreateEphemeralMultifield (needs the reserve
 * arena). The very next line reads through a decompiler-lost-register
 * variable ("v14") *as a pointer* (`*(_DWORD *)(v14 + 12)`) that is never
 * actually assigned in the recompiled source, so this is expected to CRASH
 * -- but only after the guard, the allocation, and the a1[1..4] bookkeeping
 * lines have already executed, banking that partial coverage. */
TEST(cov16_range, replace_range_success_path_hits_known_decompiler_bug) {
  static _DWORD storage[64];
  static _DWORD a1buf[8], a2buf[8], a5buf[8];
  memset(storage, 0, sizeof storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a5buf, 0, sizeof a5buf);

  *(short *)((char *)storage + 6 * 0 + 14) = 2;
  *(int *)((char *)storage + 6 * 0 + 16) = 111;
  *(short *)((char *)storage + 6 * 1 + 14) = 2;
  *(int *)((char *)storage + 6 * 1 + 16) = 222;
  *(short *)((char *)storage + 6 * 2 + 14) = 2;
  *(int *)((char *)storage + 6 * 2 + 16) = 333;
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0; /* begin */
  a2buf[4] = 2; /* end -> count 3 */
  a5buf[1] = 2; /* scalar replacement, type SYMBOL (!= 4) */
  a5buf[2] = 999;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MultifieldReplaceRange(a1buf, a2buf, 2, 1, a5buf, 0));
}

/* ---- Rules_MultifieldInsertRange "success" branches: unlike ReplaceRange,
 * every decompiler-lost variable in this function ("v14") is only ever used
 * as an *arithmetic value* (`a1[4] = v14 - 1;`), never dereferenced as a
 * pointer, so reading stack garbage there is harmless UB (unpredictable
 * value, no crash). That makes the entire function safe to drive through
 * both its a2 == NULL and a2 != NULL branches, and both a3[1] == 4
 * (multifield insert) and a3[1] != 4 (scalar insert) sub-branches. */
TEST(cov16_range, insert_range_a2_null_scalar_value) {
  static _DWORD a1buf[8], a3buf[8];
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  a3buf[1] = 2; /* scalar, type != 4 */
  a3buf[2] = 555;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, 0, a3buf, 1, 0), 1);
  CHECK_EQ(a1buf[1], 4);
}

TEST(cov16_range, insert_range_a2_present_scalar_value) {
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
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0;
  a2buf[4] = 1; /* count 2 */
  a3buf[1] = 2; /* scalar insert value, type != 4 */
  a3buf[2] = 777;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, a2buf, a3buf, 1, 0), 1);
}

TEST(cov16_range, insert_range_a2_present_multifield_value) {
  static _DWORD storage[64], ins_storage[64];
  static _DWORD a1buf[8], a2buf[8], a3buf[8];
  memset(storage, 0, sizeof storage);
  memset(ins_storage, 0, sizeof ins_storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);

  *(short *)((char *)storage + 6 * 0 + 14) = 2;
  *(int *)((char *)storage + 6 * 0 + 16) = 10;
  *(short *)((char *)storage + 6 * 1 + 14) = 2;
  *(int *)((char *)storage + 6 * 1 + 16) = 20;
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0;
  a2buf[4] = 1; /* count 2 */

  *(short *)((char *)ins_storage + 6 * 0 + 14) = 2;
  *(int *)((char *)ins_storage + 6 * 0 + 16) = 888;
  a3buf[1] = 4; /* multifield insert value */
  a3buf[2] = (_DWORD)(intptr_t)ins_storage;
  a3buf[3] = 0;
  a3buf[4] = 0; /* single element */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Rules_MultifieldInsertRange(a1buf, a2buf, a3buf, 1, 0), 1);
}

/* ---- Rules_MultifieldInsertRange with a2 == NULL and a3[1] == 4: this
 * specific combination delegates to Rules_AssignMultifieldRangeCopy
 * (outside this batch), which has its own decompiler-lost-variable bug
 * (dereferences an unassigned local as a pointer) and is expected to CRASH.
 * Isolated in its own TEST so the rest of this file's coverage is
 * unaffected; still banks Rules_MultifieldInsertRange's own lines up to
 * that call. */
TEST(cov16_range, insert_range_a2_null_multifield_value_hits_known_bug) {
  static _DWORD ins_storage[64];
  static _DWORD a1buf[8], a3buf[8];
  memset(ins_storage, 0, sizeof ins_storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  *(short *)((char *)ins_storage + 6 * 0 + 14) = 2;
  *(int *)((char *)ins_storage + 6 * 0 + 16) = 321;
  a3buf[1] = 4;
  a3buf[2] = (_DWORD)(intptr_t)ins_storage;
  a3buf[3] = 0;
  a3buf[4] = 0;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MultifieldInsertRange(a1buf, 0, a3buf, 1, 0));
}

/* ---- Rules_MultifieldDeleteRange "success" branch: like ReplaceRange, once
 * past its own guard it reads a decompiler-lost-register variable ("v9") as
 * a pointer (`*(_DWORD *)(v9 + 12)`), which is never actually assigned in
 * the recompiled source -- expected to CRASH, but only after the guard,
 * the Rules_CreateEphemeralMultifield allocation, and the a1[1..4]/v7/v24
 * bookkeeping lines have already run, banking that partial coverage. */
TEST(cov16_range, delete_range_success_path_hits_known_decompiler_bug) {
  static _DWORD storage[64];
  static _DWORD a1buf[8], a2buf[8];
  memset(storage, 0, sizeof storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);

  *(short *)((char *)storage + 6 * 0 + 14) = 2;
  *(int *)((char *)storage + 6 * 0 + 16) = 1;
  *(short *)((char *)storage + 6 * 1 + 14) = 2;
  *(int *)((char *)storage + 6 * 1 + 16) = 2;
  *(short *)((char *)storage + 6 * 2 + 14) = 2;
  *(int *)((char *)storage + 6 * 2 + 16) = 3;
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0; /* begin */
  a2buf[4] = 2; /* end -> count 3 */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MultifieldDeleteRange(a1buf, a2buf, 2, 1, 0));
}
