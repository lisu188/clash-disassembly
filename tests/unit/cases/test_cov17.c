/* cov17 cluster: Rules_Register{String,Math,Help}Builtins, string/math/help
 * builtin functions around 0x4A2988-0x4A6620 (see cov_batches/cov_17.json). */

/* ---- helper: point dword_51A960 at a zeroed fake arg-node chain so
 * Rules_RtnArgCount()'s walk (which dereferences dword_51A960+6) sees a
 * safe non-NULL head with a zero "next" link, terminating at count 0
 * instead of faulting on the default NULL global (same trick as cov10).
 *
 * Also wire up the secondary pointer chain Rules_RtnUnknown's "nonexistent
 * arg" error path reads: `Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD
 * **)(dword_51A960 + 2) + 16), a1)`. On this 64-bit build `_DWORD **` is a
 * real 8-byte pointer type, so argnode+2 must hold an actual pointer (to a
 * "mid" node), whose own first 4 bytes must in turn hold an int that, +16,
 * is a safely readable address -- point it at a third zeroed buffer. With
 * all three hooked up, any caller that falls through to this error path
 * (e.g. via Lexer_ParseValueList -> Rules_RtnUnknown when the fake chain
 * has zero real args) prints an error instead of dereferencing NULL. */
static void cov17_set_fake_argnode(unsigned char *argnode, int size) {
  static unsigned char midNode[64];
  static unsigned char innerBuf[64];
  memset(argnode, 0, size);
  memset(midNode, 0, sizeof(midNode));
  memset(innerBuf, 0, sizeof(innerBuf));
  *(_DWORD **)(argnode + 2) = (_DWORD *)midNode;
  *(_DWORD *)(midNode + 0) = (_DWORD)(intptr_t)innerBuf;
  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
}

/* ---- Rules_RegisterStringBuiltins / Rules_RegisterMathBuiltins /
 * Rules_RegisterHelpFunctions: pure registration side effects (chains of
 * Rules_RegisterHostFunction calls). Rules_RegisterHostFunction allocates
 * host-function nodes out of the global reserve-block arena rooted at
 * dword_54DBA8 (via Mem_InitReserveBlock, as cov13's registration tests
 * already do), and each registration also interns a symbol via
 * Str_Intern(), which indexes the global symbol hash table rooted at
 * dword_54DD50 -- also NULL until carved out, by Rules_InitAtomTables().
 * Both are one-time setup helpers pulled straight out of the real engine
 * bring-up sequence (Rules_InitializeEngine), so calling them here mirrors
 * how the real code always reaches these registration routines. */
TEST(cov17_reg, register_string_builtins) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterStringBuiltins());
}

TEST(cov17_reg, register_math_builtins) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterMathBuiltins());
}

TEST(cov17_reg, register_help_functions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterHelpFunctions());
}

/* ---- Rules_StrCatBuiltin / Rules_SymCatBuiltin: thin wrappers delegating
 * to Rules_ConcatBuiltinCore(a1, {3,2}, a2, a3). The core writes through a1
 * (its own result slot) so back it with a generously sized zeroed buffer;
 * the arg-count walk is driven to 0 via the fake arg-node so the "no args"
 * path (v8 < 1) executes deterministically. NOTE: Rules_ConcatBuiltinCore
 * itself then does `*(_DWORD *)(v5 + 8) = v4;` where v5 is a genuinely
 * uninitialized decompiler artifact ("possibly undefined" per clash95.c's
 * own annotation at 4A2C6F) rather than something derivable from our
 * inputs, so this reliably segfaults a few lines in on both call shapes;
 * still exercises the wrapper + core's setup lines before that, and the
 * harness's crash isolation keeps it from affecting other tests. Each
 * builtin gets its own TEST so one crashing doesn't skip the other. */
TEST(cov17_str, strcat_builtin) {
  static unsigned char argnode[256];
  /* obj must be `static`: the core writes through a1 as a raw address
   * encoded in a 32-bit int (`*(_DWORD *)(a1 + 4) = a2`). On this 64-bit
   * build an ordinary stack address truncated to 32 bits does not survive
   * round-tripping, but static/global storage sits at a low, non-PIE
   * address that does. */
  static _DWORD obj[64];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(obj, 0, sizeof(obj));
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_StrCatBuiltin((int)(intptr_t)obj, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

TEST(cov17_str, symcat_builtin) {
  static unsigned char argnode[256];
  static _DWORD obj[64];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(obj, 0, sizeof(obj));
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_SymCatBuiltin((int)(intptr_t)obj, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_StrCompareBuiltin: Rules_ArgRangeCheck(aStrCompare,3) reads
 * arg count via the same fake-argnode-driven Rules_RtnArgCount(); with a
 * zeroed chain (count 0) the range check very likely takes its "out of
 * range" error branch (prints via Output_Write, whose default 0 router
 * short-circuits harmlessly) and returns 0 before touching the parsed
 * value slots -- exercises the wrapper's setup lines plus the error-path
 * plumbing safely. */
TEST(cov17_str, str_compare_builtin) {
  static unsigned char argnode[256];
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_StrCompareBuiltin(0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_MathParseSingleArg: Lexer_TokenExpect(1) consults the same
 * arg-count walk; with the fake zeroed chain (count 0 != 1) it takes the
 * mismatch/error branch and returns 0 without dereferencing v5[2],
 * exercising the guard line plus the "return 0" path. */
TEST(cov17_math, math_parse_single_arg) {
  static unsigned char argnode[256];
  double out = 0.0;
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_MathParseSingleArg(&out, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_MathIsNearZero: pure double comparison, no parser state
 * needed. Exercise both the "within tolerance" and "outside tolerance"
 * branches directly. */
TEST(cov17_math, math_is_near_zero_both_branches) {
  CHECK(Rules_MathIsNearZero(0.0, 1e-6) != 0);
  CHECK(Rules_MathIsNearZero(5.0, 1e-6) == 0);
  CHECK(Rules_MathIsNearZero(-1e-9, 1e-6) != 0);
}

/* ---- One-argument trig/hyperbolic/exp/log math builtins: all funnel
 * through Rules_MathParseSingleArg first. With the fake zeroed arg-node
 * chain the parse fails (count 0 vs expected 1), so each builtin takes its
 * "!Rules_MathParseSingleArg(...)" early-return branch -- safe and
 * deterministic, exercising the wrapper's own setup + failure-path lines.
 * (Their post-parse success branches touch floating point domain checks
 * that depend on unrecoverable decompiler BYREF state, so we don't chase
 * those here; the failure path is still real coverage.) */
TEST(cov17_math, single_arg_builtins_parse_fail_path) {
  static unsigned char argnode[256];
  cov17_set_fake_argnode(argnode, sizeof(argnode));

  TOUCH(Rules_CosBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_SinBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_AtanBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_AcotBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_CoshBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_SinhBuiltin(0, 0, 0, 0.0));
  TOUCH(Rules_MathTanh(0, 0, 0, 0.0));
  TOUCH(Rules_MathSech(0, 0, 0, 0.0));
  TOUCH(Rules_MathCsch(0, 0, 0, 0.0));
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0));
  TOUCH(Rules_MathAsinh(0, 0, 0, 0.0));
  TOUCH(Rules_MathAcsch(0, 0, 0, 0.0));
  TOUCH(Rules_MathExp(0, 0, 0, 0.0));
  TOUCH(Rules_MathLog(0, 0, 0, 0.0));
  TOUCH(Rules_MathLog10(0, 0, 0, 0.0));
  TOUCH(Rules_MathSqrt(0, 0, 0, 0.0));

  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_MathPow: Lexer_TokenExpect(2) against the fake zeroed chain
 * (count 0 != 2) takes the early mismatch/error return, exercising its own
 * guard line. */
TEST(cov17_math, math_pow_parse_fail_path) {
  static unsigned char argnode[256];
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_MathPow(0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Rules_MathMod: same Lexer_TokenExpect(2) guard; on failure it
 * writes an integer-0 result through a1 (offset 4 = type tag, offset 8 =
 * value pointer via Rules_AddIntegerValue), so back a1 with a real zeroed
 * buffer. */
TEST(cov17_math, math_mod_parse_fail_path) {
  static unsigned char argnode[256];
  /* Must be `static` for the same reason as `obj` above: Rules_MathMod
   * writes through a1 as a 32-bit-int-encoded address. */
  static _DWORD result_slot[16];
  memset(result_slot, 0, sizeof(result_slot));
  Mem_InitReserveBlock(0, 0);
  cov17_set_fake_argnode(argnode, sizeof(argnode));
  TOUCH(Rules_MathMod((int)(intptr_t)result_slot, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* ---- Help_RouterQueryMatchesWhelp: plain strcmp against the literal
 * "whelp"; exercise both the match and no-match branches with real
 * NUL-terminated strings. */
TEST(cov17_help, router_query_matches_whelp) {
  CHECK(Help_RouterQueryMatchesWhelp((void *)"whelp") != 0);
  CHECK(Help_RouterQueryMatchesWhelp((void *)"not-whelp") == 0);
}

/* ---- Rules_HelpRouterPrint: forwards to Output_Write(aStdout_3, a2, a1);
 * with no output router registered (default globals) Output_Write
 * short-circuits before touching the message pointer, so any small ints
 * are safe here. */
TEST(cov17_help, help_router_print) {
  TOUCH(Rules_HelpRouterPrint(0, 0));
  TOUCH(Rules_HelpRouterPrint(1, 2));
}

/* ---- Rules_HelpRouterGetc / Rules_HelpRouterUngetc: forward to
 * Lexer_PeekChar/Lexer_SkipChar against the "stdin" router name; with no
 * router chain registered (dword_51A604 default 0) and the name not
 * matching the special dword_51A608 buffered-file case (default 0 too,
 * and aStdin_3 is a nonzero string literal), both take the
 * "unrecognized router" early-return path safely. */
TEST(cov17_help, help_router_getc_ungetc) {
  TOUCH(Rules_HelpRouterGetc((void *)0));
  TOUCH(Rules_HelpRouterUngetc(0, 'x'));
  TOUCH(Rules_HelpRouterUngetc(1, 0));
}
