/* cov3_04: second-pass coverage for a batch of partially-covered functions.
 *
 * Research method: all the "gated by Lexer_ParseValueList" functions below
 * were probed in an isolated standalone harness (outside this repo, not
 * checked in) before writing these cases, to determine which additional
 * branches are actually *reachable* vs structurally dead in this build:
 *
 *   Lexer_ParseValueList() unconditionally dereferences an uninitialized
 *   local ('v7', decompiler-lost-variable) immediately after any successful
 *   (non-error) Rules_RtnUnknown() lookup, and before it can ever return 1.
 *   So Lexer_ParseValueList can only ever (a) return 0 via the "argument not
 *   found" path (dword_51A964 gets set before the buggy read), or (b) crash
 *   one frame down inside itself once an argument *is* found. It can never
 *   return a truthy "success" back to its caller in this recompiled binary.
 *
 * That means for functions whose *first* Lexer_ParseValueList/Lexer_TokenExpect
 * call gates all of their remaining body (Rules_SubseqFunction,
 * Rules_ParsePositiveIntArg, Rules_MVDeleteFunction, ...), the existing
 * first-pass tests already reach the maximum safely-reachable line (the
 * "if (!Lexer_ParseValueList(...))" call site) -- driving a "found" argument
 * there only moves the crash *inside* Lexer_ParseValueList without adding
 * any new line to the caller, so those are intentionally not re-tested here.
 *
 * Where a function has an *independent* earlier gate (Lexer_TokenExpect
 * succeeding/failing on arg *count* before ever calling ParseValueList,
 * or a completely different arg-count-driven branch), driving that earlier
 * gate the other way does reach genuinely new lines in the caller itself,
 * even though the deeper call still ultimately crashes one or more frames
 * down -- that's exercised below (Rules_Dependents, Rules_FloatFunction,
 * Rules_MathParseSingleArg, Class_ClassSlotsCommand).
 */

/* ---- CRT_GetOrCreateThreadDataPreserveLastError: TlsGetValue-driven, not
 * related to the parser/Lexer machinery at all. Previously fully uncovered
 * (0/15) -- likely because no existing test touches TLS state for it. All
 * three branches (slot empty/not-found, slot found with no realloc needed,
 * slot found needing realloc) are independently reachable via TlsAlloc/
 * TlsSetValue/dwTlsIndex, verified crash-free in isolation. ---- */
TEST(cov3_04_crt_tls, not_found_default_state) {
  DWORD savedIdx = dwTlsIndex;
  DWORD savedErr;
  void *p;
  dwTlsIndex = (DWORD)-1; /* default: no TLS slot allocated yet */
  SetLastError(1234);
  p = CRT_GetOrCreateThreadDataPreserveLastError();
  TOUCH(p);
  savedErr = GetLastError();
  CHECK_EQ(savedErr, 1234);
  dwTlsIndex = savedIdx;
}

TEST(cov3_04_crt_tls, found_no_realloc_needed) {
  static unsigned char buf[256];
  DWORD savedIdx = dwTlsIndex;
  DWORD idx;
  memset(buf, 0, sizeof buf);
  buf[83] = 0; /* Value[83] falsy -> skip the realloc branch */
  idx = TlsAlloc();
  TlsSetValue(idx, buf);
  dwTlsIndex = idx;
  SetLastError(55);
  TOUCH(CRT_GetOrCreateThreadDataPreserveLastError());
  CHECK_EQ(GetLastError(), 55);
  dwTlsIndex = savedIdx;
}

TEST(cov3_04_crt_tls, found_realloc_branch) {
  static unsigned char buf[256];
  DWORD savedIdx = dwTlsIndex;
  DWORD idx;
  memset(buf, 0, sizeof buf);
  buf[83] = 1; /* Value[83] truthy -> takes the _ReallocThreadData_ branch */
  idx = TlsAlloc();
  TlsSetValue(idx, buf);
  dwTlsIndex = idx;
  SetLastError(77);
  TOUCH(CRT_GetOrCreateThreadDataPreserveLastError());
  CHECK_EQ(GetLastError(), 77);
  dwTlsIndex = savedIdx;
}

/* ---- CRT_IsExtendedMbcsLeadByte: contrary to a stale comment elsewhere in
 * this test suite claiming this pulls in undefined CRT symbols and breaks
 * the link, `ismbclegal_` already has a benign stub in test_all.c's own
 * fallback set and `IsTable` is a real defined global array in clash95.c --
 * verified this links and runs cleanly in isolation. The harness's
 * ismbclegal_ stub always returns 1 (truthy), so the "!ismbclegal_(...)"
 * inner-return branch is unreachable through this entry point regardless of
 * input, but the guard check and the final range-comparison return line are
 * both real, safely reachable lines. ---- */
TEST(cov3_04_crt_mbcs, lead_byte_various_inputs) {
  TOUCH(CRT_IsExtendedMbcsLeadByte(0x81, 0x40));
  TOUCH(CRT_IsExtendedMbcsLeadByte(0, 0));
  TOUCH(CRT_IsExtendedMbcsLeadByte(0x82, 0x81));
  TOUCH(CRT_IsExtendedMbcsLeadByte(-1, -1));
}

/* ---- Parser_RegisterProceduralFunctionParsers: a straight-line chain of
 * "if (!Parser_AddFunctionParser(name, handler)) return 0;" checks.
 * Parser_AddFunctionParser succeeds only if Rules_MakeSymbol finds the name
 * already present in the *function-name* hash table (dword_54DD40) -- a
 * table that is only lazily allocated (and left EMPTY) by
 * Rules_InitFunctionNameHashTable, itself only invoked as a side effect of
 * Rules_RegisterHostFunction. Without bootstrapping that table at all, the
 * very first call dereferences dword_54DD40 while still NULL and crashes
 * one frame down inside Rules_MakeSymbol (this is likely why the previous,
 * un-bootstrapped call site only reached partial coverage). Allocating the
 * table (without populating it) reaches further: every AddFunctionParser
 * call now completes and returns 0 (symbol not found), taking the very
 * first "return 0" branch cleanly. Additionally pre-registering all 8
 * keyword symbols as host functions makes Rules_MakeSymbol find each one,
 * so every AddFunctionParser call succeeds and the whole success chain
 * (every intermediate check plus the final return) executes end to end. */
TEST(cov3_04_parser, register_procedural_table_bootstrapped_only) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  Rules_InitFunctionNameHashTable();
  TOUCH(Parser_RegisterProceduralFunctionParsers());
}

TEST(cov3_04_parser, register_procedural_full_success_chain) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  Rules_InitFunctionNameHashTable();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aIf, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aWhile, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aLoopForCount, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aReturn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aBreak, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aSwitch, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 1);
}

/* ---- Rules_Dependents: was fully uncovered (0/7). The existing sibling
 * test (test_cov13.c) calls Rules_Dependencies() first with dword_51A960
 * left at its process-default NULL, which crashes inside Rules_RtnArgCount
 * (NULL+6 deref) before the *second* TOUCH(Rules_Dependents(0.0)) in that
 * same TEST body is ever reached -- so this function's own lines are never
 * executed at all in that test. Isolating it here with a safe (non-NULL,
 * empty) arg chain reaches Lexer_TokenExpect(1), which mismatches (count 0
 * != 1) and returns -1, taking the early "return result;" path. A second
 * case gives it exactly one real argument node so Lexer_TokenExpect(1)
 * matches and the "if (result != -1)" body is entered, reaching the
 * Rules_ResolveFactOrInstanceArg call line before it (and the crash lands a
 * frame down, in that unrelated callee, per the Lexer_ParseValueList family
 * of bugs described at the top of this file). */
TEST(cov3_04_dependents, token_mismatch_returns_early) {
  static unsigned char argnode[256];
  int saved = g_ClipsCurrentExpression;
  memset(argnode, 0, sizeof argnode);
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ((intptr_t)Rules_Dependents(0.0), -1);
  g_ClipsCurrentExpression = saved;
}

TEST(cov3_04_dependents, token_match_enters_body) {
  static unsigned char anchor[64];
  static unsigned char node[64];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  *(_DWORD *)(anchor + 6) = (int)(intptr_t)node; /* one arg node -> count 1 */
  *(_DWORD *)(node + 10) = 0;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_Dependents(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Class_ClassSlotsCommand: previously reached only 3/6 lines. The
 * chain is Class_ClassSlotsCommand -> Class_ParseClassNameAndInheritFlag,
 * which itself gates on Rules_RtnArgCount(): a *nonzero* count drives it
 * into its own Lexer_ParseValueList call (which then crashes one frame
 * down before Class_ParseClassNameAndInheritFlag can return at all -- so
 * Class_ClassSlotsCommand's own "if (v2)" check is never reached that way).
 * A *zero* arg count instead takes Class_ParseClassNameAndInheritFlag's own
 * safe "Rules_ExpectedCountError; return 0;" branch, which completes
 * cleanly and returns 0 up to Class_ClassSlotsCommand -- reaching its own
 * "if (v2)" check (false) and the "return Rules_SetMultifieldErrorValue(...)"
 * call line, which is new coverage even though (per the existing cov16
 * notes on that same helper's decompiler-lost-pointer bug) it then crashes
 * one frame further down inside Rules_SetMultifieldErrorValue itself. */
TEST(cov3_04_classslots, empty_args_reaches_error_branch) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  int saved = g_ClipsCurrentExpression;
  memset(argnode, 0, sizeof argnode);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec; /* Rules_RtnArgCount()==0 */
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Class_ClassSlotsCommand(1, 1.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_FloatFunction: the existing test (test_cov16.c) uses an empty
 * arg chain so Lexer_TokenExpect(1) mismatches and returns -1, taking the
 * first "v8=0.0; return 0.0;" branch. Giving it exactly one real argument
 * node instead makes Lexer_TokenExpect(1) match, entering the
 * "else if (Lexer_ParseValueList(...))" line -- a genuinely different,
 * previously-unreached line in this function, even though the deeper call
 * still ends up crashing inside Lexer_ParseValueList's own known bug. */
TEST(cov3_04_floatfn, token_match_enters_parsevaluelist_line) {
  static unsigned char anchor[64];
  static unsigned char node[64];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  *(_DWORD *)(anchor + 6) = (int)(intptr_t)node;
  *(_DWORD *)(node + 2) = (int)(intptr_t)node; /* self-pointer: avoids a NULL deref */
  *(_DWORD *)(node + 10) = 0;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_FloatFunction(1, 2, 3, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_MathParseSingleArg: same shape as Rules_FloatFunction above --
 * cov17's existing test uses an empty chain (TokenExpect(1) mismatch,
 * returns 0 early). Matching the arg count instead reaches the
 * "result = Lexer_ParseValueList(1, v5, 0, a3);" line before the deeper
 * crash. */
TEST(cov3_04_mathparse, token_match_enters_parsevaluelist_line) {
  static unsigned char anchor[64];
  static unsigned char node[64];
  int saved = g_ClipsCurrentExpression;
  double out = 0.0;
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  *(_DWORD *)(anchor + 6) = (int)(intptr_t)node;
  *(_DWORD *)(node + 2) = (int)(intptr_t)node;
  *(_DWORD *)(node + 10) = 0;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MathParseSingleArg(&out, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_TestConstraintAttributeParsedFlag: every branch past the first
 * ("type") check is gated by a chain of decompiler-lost locals fed straight
 * into strcmp_, so which comparison actually "matches" depends on whatever
 * garbage happens to be on the stack at each distinct call site (cov23 and
 * cov2_00 already tried this from two different sites). One more fresh
 * call site, with yet another local stack shape ahead of it, on the chance
 * the garbage resolves differently here and lands on one of the
 * still-uncovered comparison branches. */
TEST(cov3_04_testparsedflag, another_fresh_call_site) {
  _DWORD bits[4];
  char pad1[11];
  int pad2[5];
  memset(bits, 0, sizeof bits);
  memset(pad1, 0, sizeof pad1);
  memset(pad2, 0, sizeof pad2);
  bits[0] = 1;
  TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)"cov3-04-unmatched", bits));
}
