/* cov5_00: stack-spray coverage pass for a batch of partially-covered
 * functions (Rules_ApplyPatternKeywordFlags, Rules_MathPow,
 * Parser_CollectFunctionArguments, Rules_ExtractModuleAndConstructName,
 * UnitBattle_GetTargetCrowdingScale, Rules_CheckLiteralSlotValueConstraint,
 * Rules_StrCompareBuiltin, Rules_WriteConstructHeaderToCode,
 * Compiler_GenerateConstructTables, Definstances_DeleteRecord).
 *
 * Every candidate above was investigated with a private, isolated compile of
 * clash95.c against this same harness shape (outside the shared build), run
 * under gdb, using the stack-spray technique documented in
 * tests/unit/cases/test_cov3_01.c: fill a large volatile stack buffer with a
 * chosen value immediately before the target call so a decompiler
 * "possibly undefined" local resolves to that value instead of whatever
 * garbage the stack happened to hold.
 *
 * Two functions below were cracked further than any previous pass:
 * Rules_CheckLiteralSlotValueConstraint and Rules_ExtractModuleAndConstruct-
 * Name. The rest of the batch turned out to be confirmed hard ceilings, each
 * for a *different* structural reason discovered during this investigation
 * (documented inline at each attempted call site so future passes don't
 * re-walk the same dead end):
 *   - Rules_MathPow / Rules_StrCompareBuiltin: both funnel through
 *     Lexer_ParseValueList, whose very first post-Rules_RtnUnknown line
 *     unconditionally dereferences a decompiler-lost local ('v7') at a
 *     small/garbage address (confirmed via gdb: a hard-coded small integer
 *     left over from the Lexer_TokenExpect call, NOT influenced by any
 *     external stack spray, and always < the kernel's mmap_min_addr so it
 *     can never be mapped in). Matches test_cov3_04.c/test_cov4_02.c's
 *     independent conclusion.
 *   - Rules_ApplyPatternKeywordFlags: its lone callee
 *     Rules_CreateLHSParseNode calls Rules_SetLHSParseNodeDefaultFlags(v1,1)
 *     immediately before dereferencing its own lost local; that call
 *     deterministically zeroes the register in question (confirmed via gdb),
 *     so priming the caller's stack before entry cannot survive the
 *     intervening real call.
 *   - Definstances_DeleteRecord / Rules_WriteConstructHeaderToCode: the
 *     specific lost locals here (rbp-0xc and rbp-0x8 respectively, per gdb
 *     disassembly) sit closer to the frame's return address than this
 *     -fstack-protector-strong build's canary/argument-spill area, which is
 *     exactly the region test_cov3_01.c's Rules_BuildFactAddressList note
 *     already flagged as unreachable by a caller-side spray buffer (which
 *     bottoms out ~0x14-0x20 bytes short of the callee's rbp).
 *   - Compiler_GenerateConstructTables: Rules_SetAtomicValueIndices (called
 *     before the first lost local is ever read) itself has a real 64-bit-
 *     port bug -- an `int **` (8-byte-stride) cursor walking a packed
 *     32-bit bucket table -- and crashes on its own, independent of any
 *     argument or global state. Matches test_cov2_09.c/test_cov3_06.c's
 *     independent conclusion.
 *   - Parser_CollectFunctionArguments: its callee Parser_ParseArgument passes
 *     its own on-stack output buffer through a 32-bit `int` parameter to
 *     Parser_NextToken; on this 64-bit build the real (64-bit) stack address
 *     truncates to a small/negative 32-bit value that, once sign-extended
 *     back to a pointer, lands outside any mappable user address -- a
 *     pointer-width port bug in Parser_ParseArgument itself, not something
 *     any caller-side argument or spray can route around.
 *   - UnitBattle_GetTargetCrowdingScale: switches on
 *     UnitBattle_CountAdjacentEnemies()'s return value, which (per this
 *     binary's actual dword_514500/dword_514504 .data contents) can only
 *     ever produce {0,1,6,7}; counts 3/4/5 are mathematically unreachable
 *     from any input. Matches test_cov2_04.c/test_cov4_00.c's independent
 *     conclusion.
 */

static void cov5_00_stack_prime(int val) {
  volatile int buf[65536];
  int i;
  for (i = 0; i < 65536; i++) {
    buf[i] = val;
  }
}

/* =====================================================================
 * Rules_CheckLiteralSlotValueConstraint (8 uncovered): with static
 * constraint checking enabled, the very next statement reads a decompiler-
 * lost local ('v3') as `*(_DWORD *)(v3 + 8)` to build the second argument to
 * Rules_CheckFieldExprListAgainstConstraint -- immediately after the
 * Rules_StaticConstraintCheckingEnabled() guard, with no intervening call,
 * exactly the "clean spray" shape from test_cov3_01.c. Priming with the
 * address of a zeroed buffer makes that dereference read back 0, so
 * Rules_CheckFieldExprListAgainstConstraint(NULL, 0) is called with a1=NULL:
 * its own field-expr walk is skipped (empty list), Method_ParamRangeInBounds
 * (0,0,0) short-circuits true, and it returns 0 for the "empty list is
 * trivially satisfied" case -- landing on the outer function's previously
 * unreached `if (!v5) return 1;` path. (test_cov2_02.c already attempted
 * this function without spraying and, per test_cov4_02.c's coverage-data
 * check, could not get past the v3 dereference; the spray is what unlocks
 * it.) ===================== */
TEST(cov5_00_litslot, checking_enabled_v3_primed_zero) {
  static _DWORD v3buf[16];
  int saved = g_CLIPS_StaticConstraintCheckingFlag;
  memset(v3buf, 0, sizeof v3buf);
  /* v3buf+8 == 0 -> the second arg to
   * Rules_CheckFieldExprListAgainstConstraint resolves to 0. */
  g_CLIPS_StaticConstraintCheckingFlag = 1; /* static constraint checking enabled */
  cov5_00_stack_prime((int)(intptr_t)v3buf);
  CHECK_EQ(Rules_CheckLiteralSlotValueConstraint((int *)0, 0), 1);
  g_CLIPS_StaticConstraintCheckingFlag = saved;
}

/* =====================================================================
 * Rules_ExtractModuleAndConstructName (10 uncovered): a clean, UB-free
 * chain (Rules_FindModuleSeparator -> Rules_ExtractModuleName ->
 * Module_FindByName -> Module_SetCurrent -> Rules_ExtractConstructName), but
 * every previous attempt (test_cov4_06.c, test_cov14.c, test_cov2_06.c)
 * fell straight through the "MOD::name" qualifier-split without ever
 * priming Rules_ExtractModuleName's own internal decompiler-lost locals
 * ('v3'/'v4', fed straight into strncpy_ right after its lone
 * Mem_SmallBlockAlloc() call -- another "clean spray" shape), so
 * module_symbol never came back non-NULL before. Priming with the address
 * of the qualified-name buffer itself lets Rules_ExtractModuleName's
 * strncpy_ succeed and actually intern a module-name symbol, unlocking
 * Module_FindByName/Module_SetCurrent/Rules_ExtractConstructName below it.
 * Three shapes cover as much of the 0-vs-nonzero decision tree as this
 * batch's investigation could get to behave deterministically:
 *   (1) "::b" gives a qualifier length of exactly 1, which
 *       Rules_ExtractModuleName's own `if (a1 <= 1) return 0;` guard catches
 *       before ever touching its lost locals -- banks the module_symbol-NULL
 *       branch safely.
 *   (2) "ab::cd" with the real (default, empty) module list banks the
 *       module_record-NULL branch once module_symbol is non-NULL.
 *   (3) "ab::cd" again, but first calling Rules_ExtractModuleName(2)
 *       ourselves (under the same priming) to discover the *actual* symbol
 *       it interns (its own internal length/copy arithmetic is itself
 *       decompiler-lost, so the interned text is not guaranteed to be
 *       exactly "ab"), then registering a one-entry fake module list
 *       (dword_51A9AC) whose head record's symbol field matches that exact
 *       symbol. Module_FindByName then succeeds for real, letting
 *       Module_SetCurrent and Rules_ExtractConstructName's own call line run
 *       (Rules_ExtractConstructName's *own* decompiler-lost locals are a
 *       further, separate ceiling this batch didn't crack, but the call
 *       site itself and everything before it is now reached). ===== */
TEST(cov5_00_extractmod, qualifier_length_one_module_symbol_null) {
  static char name[64];
  strcpy(name, "::b");
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_00_stack_prime((int)(intptr_t)name);
  TOUCH(Rules_ExtractModuleAndConstructName((_BYTE *)name));
}

TEST(cov5_00_extractmod, qualified_name_module_record_not_found) {
  static char name[64];
  strcpy(name, "ab::cd");
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_00_stack_prime((int)(intptr_t)name);
  TOUCH(Rules_ExtractModuleAndConstructName((_BYTE *)name));
}

TEST(cov5_00_extractmod, qualified_name_module_record_found) {
  static char name[64];
  static _DWORD moduleNode[16];
  int *presym;
  int saved9AC = g_DefmoduleListHead;
  strcpy(name, "ab::cd");
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  /* Discover the actual symbol Rules_ExtractModuleName interns for this
   * input (its own copy-length arithmetic is decompiler-lost, so this is
   * empirical rather than assumed). */
  cov5_00_stack_prime((int)(intptr_t)name);
  presym = Rules_ExtractModuleName(2);

  if (presym) {
    memset(moduleNode, 0, sizeof moduleNode);
    moduleNode[0] = (_DWORD)(intptr_t)presym; /* module record "symbol" slot */
    g_DefmoduleListHead = (int)(intptr_t)moduleNode; /* one-entry fake module list */
  }

  cov5_00_stack_prime((int)(intptr_t)name);
  TOUCH(Rules_ExtractModuleAndConstructName((_BYTE *)name));
  g_DefmoduleListHead = saved9AC;
}
