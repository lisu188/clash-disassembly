/* cov4_07: final-pass precise-line coverage for a mixed batch of 22 functions
 * (see scratchpad/cov4_batches/cov4_07.json). Every TEST below uses the
 * unique suite prefix cov4_07_. Each test runs in its own forked+watchdog
 * child (tests/unit/test_all.c), so calling anything that might crash, exit,
 * or hang is safe -- coverage banked up to the crash point is kept.
 *
 * This is a 64-bit -no-pie build of code whose recovered signatures model
 * pointers as 32-bit ints (_DWORD/int). A plain stack buffer lives at a high
 * 64-bit address that silently truncates to garbage when squeezed through
 * such a field, so every buffer whose address crosses into a recovered
 * function through an int/_DWORD field is declared `static` (lands in the
 * low .bss image instead), matching the convention used throughout
 * tests/unit/cases/test_cov*.c. */

/* =========================================================================
 * Shared helper: the "argument node" trick used throughout this test suite
 * (test_cov11.c, test_cov3_02.c, test_cov3_05.c, ...): Rules_RtnArgCount() /
 * Rules_RtnUnknown() / Lexer_ParseValueList() all walk a chain of "argument
 * nodes" rooted at *(dword_51A960 + 6), each node shaped as
 * (int16 type_tag @ 0; DWORD value @ 2; DWORD next @ 10). Parser_ParseForm's
 * "simple literal" case (type_tag in {0,1,2,3,5,7,8}) copies the node's raw
 * value field straight into the caller's out-param, so pointing that value
 * field at our own scratch buffer hands the caller a real, deterministic
 * argument value. ========================================================= */
static void cov4_07_arg_node_init(unsigned char *node, short type_tag,
                                   void *value_ptr, void *next_node) {
  memset(node, 0, 32);
  *(short *)(node + 0) = type_tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)value_ptr;
  *(_DWORD *)(node + 10) = (_DWORD)(intptr_t)next_node;
}

static void cov4_07_install_arg_chain(unsigned char *argnode, void *head_node) {
  /* dword_51A960+2 must point at a "function record" whose own first field
   * points at a zeroed "symbol" node -- Rules_RtnUnknown's "argument not
   * found" fallback (Rules_NonexistentArgError) dereferences this chain
   * unconditionally even when the arg list is empty, matching the safety
   * net test_cov3_02.c's cov3_02_install_arg_chain already established. */
  static _DWORD funcrec[8];
  static _DWORD symnode[8];
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  funcrec[0] = (_DWORD)(intptr_t)symnode;

  memset(argnode, 0, 32);
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)head_node;
  dword_51A960 = (int)(intptr_t)argnode;
}

/* =========================================================================
 * Shared helper: register one fake, always-in-scope class in the real class
 * hash table (dword_51AD68), same technique as test_cov3_02.c's
 * cov3_02_register_fake_class -- duplicated locally (with a cov4_07_ prefix)
 * to keep this file self-contained. Class_HashClassName's own bucket range
 * is what dword_51AD68's real table is sized for; 0xA7 slots matches what
 * the rest of the suite already established as safe. ========================= */
static int *cov4_07_register_fake_class(const char *name) {
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

  classRecord[0] = (_DWORD)(intptr_t)symbol;   /* offset0: class-name symbol ptr */
  *((unsigned char *)classRecord + 20) |= 1;    /* offset20 bit0: "defined" flag */
  classRecord[25] = 0;                          /* offset100: next-in-bucket == 0 */
  classRecord[26] = (_DWORD)(intptr_t)scopeInfo; /* offset104: scope info ptr */

  classTable[bucket % 0xA7u] = (_DWORD)(intptr_t)classRecord;
  dword_51AD68 = (int)(intptr_t)classTable;

  fakeModule[6] = 0; /* offset24: bit index 0 into the scope bitmask */
  dword_51A9B0 = (int)(intptr_t)fakeModule;

  return (int *)(intptr_t)classRecord;
}

/* =========================================================================
 * Parser_RegisterProceduralFunctionParsers -- a straight-line chain of
 * "if (!Parser_AddFunctionParser(name, handler)) return 0;" checks.
 * Parser_AddFunctionParser succeeds only when Rules_MakeSymbol finds `name`
 * already present in the function-name hash table, which only happens for
 * names we've pre-registered via Rules_RegisterHostFunctionNoRestrictions
 * (see Rules_RegisterControlFlowFunctions, which registers every one of
 * these 8 keywords before ever calling this function for real). By
 * registering only a PREFIX of the 8 keywords before calling this function
 * ourselves, the first not-yet-registered keyword's AddFunctionParser call
 * fails, walking us one "return 0" deeper each time -- covering every
 * intermediate return-0 line (152244, 152246, 152248, 152250, 152252,
 * 152254) that a from-scratch or full-success call can't reach. ========== */
static void cov4_07_parser_bootstrap(void) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  Rules_InitFunctionNameHashTable();
}

TEST(cov4_07_parser, progn_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aProgn -> line 152244 */
}

TEST(cov4_07_parser, if_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aIf -> line 152246 */
}

TEST(cov4_07_parser, while_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aIf, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aWhile -> line 152248 */
}

TEST(cov4_07_parser, loopforcount_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aIf, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aWhile, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aLoopForCount -> line 152250 */
}

TEST(cov4_07_parser, return_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aIf, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aWhile, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aLoopForCount, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aReturn -> line 152252 */
}

TEST(cov4_07_parser, break_check_fails) {
  cov4_07_parser_bootstrap();
  Rules_RegisterHostFunctionNoRestrictions(aBind, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aProgn, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aIf, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aWhile, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aLoopForCount, 'i', 0, 0);
  Rules_RegisterHostFunctionNoRestrictions(aReturn, 'i', 0, 0);
  CHECK_EQ(Parser_RegisterProceduralFunctionParsers(), 0); /* fails at aBreak -> line 152254 */
}

/* =========================================================================
 * Rules_ValueSatisfiesRangeConstraint: the while-loop walks two parallel
 * "bounded CE value" node lists (a3+10 lower list, a3+14 upper list), each
 * node shaped (int16 kind @0; DWORD value @2; ... DWORD next @10).
 * Rules_CompareBoundedCEValues checks "a3==dword_54DD68" (our own value
 * field vs. the callee's own "+oo" placeholder) before ever looking at a1/a4,
 * so we can deterministically force either loop entry or immediate exit
 * purely with plain ints -- no engine bootstrap needed. ================== */
TEST(cov4_07_rangeconstraint, loop_body_next_null_returns_zero) {
  static unsigned char constraintBuf[32];
  static unsigned char v4node[32];
  static unsigned char v5node[32];

  memset(constraintBuf, 0, sizeof constraintBuf);
  memset(v4node, 0, sizeof v4node);
  memset(v5node, 0, sizeof v5node);

  dword_54DD68 = 0x7f000001; /* sentinel "+oo" marker value */
  *(int *)(v4node + 2) = dword_54DD68; /* Cmp(v4): a3==dword_54DD68 -> 0 -> !0 true, short-circuits v5 cmp */
  *(int *)(v4node + 10) = 0;           /* next == NULL -> loop body hits "if (!v4) return 0;" */

  *(int *)(constraintBuf + 10) = (int)(intptr_t)v4node;
  *(int *)(constraintBuf + 14) = (int)(intptr_t)v5node;

  CHECK_EQ(Rules_ValueSatisfiesRangeConstraint(0, 0xdead, (int)(intptr_t)constraintBuf), 0);
}

TEST(cov4_07_rangeconstraint, immediate_exit_returns_one) {
  static unsigned char constraintBuf[32];
  static unsigned char v4node[32];
  static unsigned char v5node[32];
  int a2val = 0x12345;

  memset(constraintBuf, 0, sizeof constraintBuf);
  memset(v4node, 0, sizeof v4node);
  memset(v5node, 0, sizeof v5node);

  /* Both lists' first node has value==a2val, so Rules_CompareBoundedCEValues's
   * very first check ("a2==a3") returns 2 for both Cmp(v4) and Cmp(v5):
   * !2 is false and 2==1 is false, so the while condition is false on the
   * very first check -- loop body never runs, straight to "return 1". */
  *(int *)(v4node + 2) = a2val;
  *(int *)(v5node + 2) = a2val;

  *(int *)(constraintBuf + 10) = (int)(intptr_t)v4node;
  *(int *)(constraintBuf + 14) = (int)(intptr_t)v5node;

  CHECK_EQ(Rules_ValueSatisfiesRangeConstraint(0, a2val, (int)(intptr_t)constraintBuf), 1);
}

/* =========================================================================
 * Method_PrintWatchStatusLine (120299-120303): PROVEN unreachable, not
 * attempted. test_cov15.c / test_cov2_08.c / test_cov3_07.c each already
 * built a "safe, zeroed generic+method record" fixture and called this with
 * confident-sounding comments about reaching further -- yet all four target
 * lines are still uncovered per this batch, which is the tell. Tracing why:
 * line 120298's Defgeneric_FormatMethodRestrictionsString(v11, 59, v7, a2)
 * calls Method_FindByIndex(a2, v7) inside Defgeneric_AppendMethodSignatureText,
 * and -- REGARDLESS of the method-count/index outcome -- that function's
 * very first few lines (before any branch) do:
 *     sprintf_(v13, "%-2d ", *v16);
 *     ((void (*)(void))strncat_)();
 * `strncat_` is declared only as `_UNKNOWN strncat_;` (== `unsigned char
 * strncat_;`, clash95.c line 4915) with NO implementation anywhere in this
 * repo (unlike sprintf_/strncpy_/strcmp_, which all have real wrappers in
 * compat/decomp_runtime_stubs.c) -- the decompiler lost this call's actual
 * arguments entirely and emitted a bare zero-arg call through a plain,
 * zero-initialized data byte. Casting that (0) to a function pointer and
 * calling it is a guaranteed NULL-pointer call, unconditionally, on every
 * single invocation of Defgeneric_AppendMethodSignatureText. There is no
 * fixture that avoids this: it is not gated by any branch we control. This
 * makes everything downstream of line 120298 (120299-120303) provably
 * unreachable through this entry point. ================================= */

/* =========================================================================
 * MessageHandler_UndefineForClassOrAll: a1==0 (all-classes path) with a4==0
 * (skips the "v7=TypeIndexFromKeyword" branch, matching a3-arg literal 3rd
 * param 0) drives the do/while over Class_GetNextRecord(0)'s enumeration.
 * That enumeration walks Module_GetItem(0, dword_54E6BC)'s "current module"
 * items array -> list wrapper -> list head, the exact same rig test_cov2_09.c
 * already used for Rules_GetNextDefrule's sibling Class_Enum(0, ...) call.
 * A single all-zero fake class record makes
 * MessageHandler_RemoveByNameAndType(v10,...) take its "a1[24]==0 && !a3"
 * fast path (always returns 1), so the loop runs exactly once: the body's
 * if-check, the Class_GetNextRecord(v10) advance, and the trailing
 * while(v10) check all execute (166463, 166465, 166467). Getting the
 * "v12=0" branch (166464) as well would additionally require
 * Class_FindMessageHandlerNameGroup to complete a real binary search over
 * a1[22]/a1[23] handler arrays -- out of scope for this pass. ============ */
TEST(cov4_07_msghandler, undefine_for_all_classes_one_record) {
  static _DWORD moduleStruct[16];
  static _DWORD itemsArray[32];
  static _DWORD listWrapper[8];
  static _DWORD fakeClassRecord[32];
  static int nameHolder = 0x4007;
  int savedCurrentModule = dword_51A9B0;
  int savedClassEnumSlot = dword_54E6BC;

  memset(moduleStruct, 0, sizeof moduleStruct);
  memset(itemsArray, 0, sizeof itemsArray);
  memset(listWrapper, 0, sizeof listWrapper);
  memset(fakeClassRecord, 0, sizeof fakeClassRecord);

  dword_54E6BC = 0; /* class construct-type slot index (0 by default) */
  moduleStruct[2] = (_DWORD)(intptr_t)itemsArray;        /* +8: items array */
  itemsArray[0] = (_DWORD)(intptr_t)listWrapper;         /* index 0 == dword_54E6BC */
  listWrapper[1] = (_DWORD)(intptr_t)fakeClassRecord;    /* +4: list head */
  /* fakeClassRecord+16 (next-in-Class_Enum chain) and +96 (a1[24], handler
   * count) both stay 0 from memset -> single, harmless enumeration step. */
  dword_51A9B0 = (int)(intptr_t)moduleStruct;

  TOUCH(MessageHandler_UndefineForClassOrAll(0, (signed int *)&nameHolder, 0, 0));

  dword_51A9B0 = savedCurrentModule;
  dword_54E6BC = savedClassEnumSlot;
}

/* =========================================================================
 * Rules_RefreshCommand: driving Rules_GetConstructNameArg to its success
 * branch (same single-node SYMBOL arg-chain fixture used throughout this
 * suite, e.g. test_cov11.c's get_construct_name_arg_success) reaches
 * "v4 = Rules_FindDefruleByName(result, v3);" where v3 is a genuinely
 * decompiler-undefined register forwarded straight into
 * Rules_FindConstructByNameGeneric as a raw (uintptr_t) struct pointer whose
 * +16/+28 fields get read AND CALLED as function pointers. Whatever garbage
 * ends up there reliably faults a frame down (matching the fact that line
 * 97061's call is already covered by some earlier attempt, while the
 * if/return lines right after it, 97062/97063/97065, never got reached) --
 * a hard ceiling. One attempt, TOUCH-only, to bank whatever's reachable. == */
TEST(cov4_07_refresh, refresh_command_arg_present_best_effort) {
  static unsigned char argnode[32], node[32];
  static int nameHolder[8];
  static const char ruleName[] = "cov4_07_NoSuchRule";
  int saved = dword_51A960;

  memset(nameHolder, 0, sizeof nameHolder);
  nameHolder[4] = (int)(intptr_t)ruleName; /* byte offset 16 -> name string */

  cov4_07_arg_node_init(node, 2 /* SYMBOL */, nameHolder, 0);
  cov4_07_install_arg_chain(argnode, node);

  TOUCH(Rules_RefreshCommand(1, 0.0));

  dword_51A960 = saved;
}

/* =========================================================================
 * Rules_HostStringp: Lexer_TokenExpect(1) needs Rules_RtnArgCount()==1 (a
 * one-node arg chain), then Rules_RtnUnknown(1, v3, a1) funnels through
 * Parser_ParseForm's literal fast path, which copies the node's raw type
 * tag straight into v3[1]. Tag 3 (STRING) drives the "return 1" success
 * branch; any other tag falls through the existing (already-covered) "not a
 * string" path. Lexer_TokenExpect(1)'s own outcome additionally depends on
 * its own decompiler-undefined 'v2' (documented already in test_cov11.c's
 * token_expect_match_and_mismatch test) -- with our chain giving
 * Rules_RtnArgCount()==1==a1, every v2 value Lexer_TokenExpect actually
 * branches on (0, 1, or 2) returns success, so this is very likely to hit
 * the target lines, but TOUCH rather than CHECK_EQ to stay safe against
 * genuinely other leftover v2 values. ==================================== */
TEST(cov4_07_hoststringp, string_tagged_arg_returns_true) {
  static unsigned char argnode[32], node[32];
  static unsigned char val[32];
  int saved = dword_51A960;

  memset(val, 0, sizeof val);
  cov4_07_arg_node_init(node, 3 /* STRING */, val, 0);
  cov4_07_install_arg_chain(argnode, node);

  TOUCH(Rules_HostStringp(0.0));

  dword_51A960 = saved;
}

/* =========================================================================
 * Rules_GetFileNameArg: Rules_RtnUnknown(a1, &v5, a3) funnels through the
 * SAME Parser_ParseForm literal fast path used above -- with a1==1 walking
 * to our chain's single node and its tag (2, SYMBOL) copied straight into
 * the caller's v6, the "v6==3||v6==2" check succeeds and returns
 * *(v7+16), reading our own scratch buffer's offset16 (left zeroed, so the
 * dereference itself is what we're after, not any particular value). ===== */
TEST(cov4_07_filenamearg, symbol_tagged_arg_reaches_success_return) {
  static unsigned char argnode[32], node[32];
  static unsigned char val[32];
  int saved = dword_51A960;

  memset(val, 0, sizeof val);
  cov4_07_arg_node_init(node, 2 /* SYMBOL */, val, 0);
  cov4_07_install_arg_chain(argnode, node);

  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));

  dword_51A960 = saved;
}

/* =========================================================================
 * Class_SuperclassPCommand: Class_ParseTwoClassNameArgs calls
 * Lexer_ParseValueList(1, ...) unconditionally (no Rules_RtnArgCount()
 * guard), so an unset/empty dword_51A960 crashes a frame down before ever
 * returning to the "if (result)" check -- that's why even the falsy branch
 * needs a real (if empty) arg-chain anchor. A two-class SYMBOL arg chain
 * (same registration technique as test_cov3_02.c's
 * cov3_02_register_fake_class, duplicated locally above) drives the full
 * success chain through to Class_HasSuperclass. ========================== */
TEST(cov4_07_superclassp, empty_arg_chain_returns_falsy) {
  static unsigned char argnode[32];
  int saved = dword_51A960;
  int savedErr = dword_51A964;

  /* head_node==NULL -> empty arg list -> Rules_RtnUnknown's "not found"
   * fallback fires, which is exactly why the +2 safety net inside
   * cov4_07_install_arg_chain is required here (unlike the "found" tests,
   * this path always dereferences it). */
  cov4_07_install_arg_chain(argnode, 0);
  dword_51A964 = 0;

  CHECK_EQ(Class_SuperclassPCommand(1.0), 0);

  dword_51A960 = saved;
  dword_51A964 = savedErr;
}

TEST(cov4_07_superclassp, two_real_classes_success) {
  static unsigned char argnode[32], node1[32], node2[32];
  static unsigned char val1[32], val2[32];
  static const char classNameA[] = "Cov4_07FakeClassA";
  int saved51AD68 = dword_51AD68;
  int saved51A9B0 = dword_51A9B0;
  int saved51A960 = dword_51A960;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov4_07_register_fake_class(classNameA);
  /* register_fake_class overwrites dword_51AD68 wholesale each call, so we
   * only need ONE fake class -- both parsed names resolve to it. */

  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  *(const char **)(val1 + 16) = classNameA;
  *(const char **)(val2 + 16) = classNameA;
  cov4_07_arg_node_init(node2, 2 /* SYMBOL */, val2, 0);
  cov4_07_arg_node_init(node1, 2 /* SYMBOL */, val1, node2);
  cov4_07_install_arg_chain(argnode, node1);

  TOUCH(Class_SuperclassPCommand(1.0));

  dword_51AD68 = saved51AD68;
  dword_51A9B0 = saved51A9B0;
  dword_51A960 = saved51A960;
}

/* =========================================================================
 * Unit_BuildGoSpriteFilePath: the first copy loop (aUnits_go, a fixed
 * 9-character global "units_go\\") always has ODD length, so its "if (!v5)
 * break;" (line 27412) can only ever fire if a null byte lands on the FIRST
 * byte of a 2-byte-stepped pair -- with a fixed 9-char source this never
 * happens (the loop always exits one step later, via the trailing
 * "while (v6)" check instead). That break is genuinely dead code for this
 * call site; not attempted. The THIRD copy loop's source is the 2-byte
 * local buffer {a3+49, 0} -- (char)(a3+49)==0 iff a3==-49, which directly
 * and deterministically fires ITS break (line 27440) on the loop's very
 * first iteration. ======================================================== */
TEST(cov4_07_unitpath, third_fragment_empty_breaks_immediately) {
  static char outbuf[256];
  memset(outbuf, 0, sizeof outbuf);
  TOUCH(Unit_BuildGoSpriteFilePath(outbuf, 0, (char)-49));
}

/* =========================================================================
 * Defgeneric_GetDefmethodListCommand: with a real one-node arg chain but a
 * type tag that does NOT match the requested SYMBOL type (2), the "&&"
 * short-circuits on Lexer_ParseValueList's own type-mismatch "return 0"
 * (deterministic, no crash) -- WITHOUT ever calling
 * Defgeneric_CheckGenericExists (whose own Defgeneric_LookupWithImports
 * reads through the never-registered dword_54E6A0 global and crashes a
 * frame down, per test_cov3_02.c's note on the sibling
 * Defgeneric_GetMethodRestrictionsCommand). That drives the "else" branch
 * (119710) cleanly. Reaching the true branch (119708) would additionally
 * require a fully-registered defgeneric construct behind
 * Symbol_LookupInModule/Rules_FindImportExportConstruct's module-import
 * machinery -- out of scope for this pass. ================================ */
TEST(cov4_07_defmethodlist, type_mismatch_takes_error_branch) {
  static unsigned char argnode[32], node[32];
  static int intval[8];
  static _DWORD out[16];
  int saved = dword_51A960;

  memset(intval, 0, sizeof intval);
  memset(out, 0, sizeof out);
  cov4_07_arg_node_init(node, 1 /* INTEGER, not SYMBOL(2) -> type mismatch */, intval, 0);
  cov4_07_install_arg_chain(argnode, node);

  TOUCH(Defgeneric_GetDefmethodListCommand(out, 0, 0.0));

  dword_51A964 = 0;
  dword_51A960 = saved;
}

/* ---- Palette_LoadFromQueryHandle: takes genuine intptr_t params (no 32-bit
 * truncation here), so a plain static int table is enough. The palette name
 * doesn't need to resolve to a real file -- Compat_LoadPalCOLIntoTable's
 * FileSystem_ResolveReadPath/Compat_Query* helpers handle a missing file
 * the same safe way other Compat_Query-based tests elsewhere already rely
 * on. ---- */
TEST(cov4_07_palette, load_from_query_handle_nonzero_table) {
  static int table[256];
  memset(table, 0, sizeof table);
  TOUCH(Palette_LoadFromQueryHandle((intptr_t)table, (intptr_t)"cov4_07_missing.col"));
}

/* ---- ProcParam_GetWildcardArgumentValue: a1+16 must hold a real "payload"
 * pointer that's itself dereferenced once more inside
 * ProcParam_BuildWildcardMultifield. With dword_51ABC8 at its process
 * default (0), that callee falls into its Mem_HeapAllocWithRetry-backed
 * allocation path, which just needs the standard reserve-block bootstrap. */
TEST(cov4_07_procparam, get_wildcard_argument_value_returns_one) {
  static _DWORD a1buf[8];
  static int payload;
  static _DWORD a2buf[8];

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  payload = 0;
  a1buf[4] = (_DWORD)(intptr_t)&payload; /* +16 bytes: "payload" pointer */

  CHECK_EQ(ProcParam_GetWildcardArgumentValue((int)(intptr_t)a1buf, a2buf), 1);
}

/* =========================================================================
 * Rules_AtanBuiltin: same hard ceiling test_cov3_07.c already documented in
 * detail for the sibling Rules_MathCsch (and, per that file, its own
 * math-builtin battery in test_cov17.c): the guard
 * "if (Rules_MathParseSingleArg(...))" already covers the failure path
 * everywhere else in this suite, but reaching line 129674 (the success-path
 * atan2 call) needs Rules_MathParseSingleArg's internal
 * Lexer_ParseValueList() call to report "success", which is gated on a
 * genuinely decompiler-undefined register inside Lexer_ParseValueList
 * itself -- not something any caller-side fixture can pin down. Repeating
 * with varying leftover stack contents (matching test_cov3_07.c's
 * "csch_retry_for_leftover_register_luck" idiom) in case it differs here;
 * TOUCH-only since the outcome is unpredictable either way. ============== */
TEST(cov4_07_atanbuiltin, retry_for_leftover_register_luck) {
  static unsigned char argnode[256];
  char pad[256];
  int i;
  int saved = dword_51A960;

  memset(argnode, 0, sizeof argnode);
  dword_51A960 = (int)(intptr_t)argnode;
  for (i = 0; i < 4; ++i) {
    memset(pad, i + 3, (size_t)(41 + i * 13));
    TOUCH(Rules_AtanBuiltin(0, 0, 0, 0.0));
  }
  dword_51A960 = saved;
}

/* ---- Rules_PrintJoinNetworkSharingReport: Rules_ClearJoinNetworkMarkedFlags
 * loops over Module_NextEnum(0), which returns 0 immediately with no modules
 * registered (the process default) -- so the whole call completes cleanly
 * and control reaches the tail-call return statement (133626). Whatever
 * garbage feeds Rules_PrintJoinNetworkNodeRuleOwners after that is
 * irrelevant to this line's coverage. ---- */
TEST(cov4_07_joinnetwork, print_report_reaches_return_line) {
  TOUCH(Rules_PrintJoinNetworkSharingReport());
}

/* ---- CRT_CheckReadOnlyBeforeOpen: to hit the "(a2&2)!=0 && (attrs&1)!=0"
 * branch we need a real, existing path whose access(W_OK) genuinely fails
 * even for root -- ordinary chmod bits don't do this (root bypasses them),
 * but a path under a filesystem mounted read-only at the OS level does.
 * This sandbox mounts /mnt/skills/public read-only; probe for a known file
 * there and fall back to the already-covered /tmp case if it's ever
 * unavailable so this test never spuriously fails in a different
 * environment. ---- */
TEST(cov4_07_crt, check_readonly_before_open_real_ro_mount) {
  const char *path = "/mnt/skills/public/docx/LICENSE.txt";
  FILE *probe = fopen(path, "r");
  if (probe) {
    fclose(probe);
  } else {
    path = "/tmp";
  }
  TOUCH(CRT_CheckReadOnlyBeforeOpen(path, 2, 0));
}

/* =========================================================================
 * Class_ClassSlotsCommand: Class_ParseClassNameAndInheritFlag succeeds via
 * the same one-class registration fixture as Class_SuperclassPCommand
 * above. A SINGLE-node arg chain makes Rules_RtnArgCount()==1 (!=2), so the
 * callee takes its simpler "return v7;" branch directly (skips the second
 * Lexer_ParseValueList/"inherit" keyword parse entirely), giving
 * Class_ClassSlotsCommand a truthy v2 and reaching the
 * Class_SlotsFunction(...) return line. ================================== */
TEST(cov4_07_classslots, one_real_class_reaches_slots_function) {
  static unsigned char argnode[32], node[32];
  static unsigned char val[32];
  static const char className[] = "Cov4_07FakeClassSlots";
  int saved51AD68 = dword_51AD68;
  int saved51A9B0 = dword_51A9B0;
  int saved51A960 = dword_51A960;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov4_07_register_fake_class(className);

  memset(val, 0, sizeof val);
  *(const char **)(val + 16) = className;
  cov4_07_arg_node_init(node, 2 /* SYMBOL */, val, 0);
  cov4_07_install_arg_chain(argnode, node);

  TOUCH(Class_ClassSlotsCommand(0, 1.0));

  dword_51AD68 = saved51AD68;
  dword_51A9B0 = saved51A9B0;
  dword_51A960 = saved51A960;
}

/* =========================================================================
 * Rules_ConstructCodeFileOpen: a1!=0 takes the very first early-return
 * (line 133084) directly; that path's Output_WriteFormatted uses asc_508250
 * (",\n", no printf specifiers) so it's unconditionally safe. With a1==0,
 * a10 selects between the a11-array source (a10!=0) and the a2/a4/a5 source
 * (a10==0) for v14/v15/v16, both of which feed straight into
 * Rules_OpenConstructCodeFile -> IO_FOpen with a real, writable scratch
 * path -- exercising the a10!=0 success tail (133091/133093/133094), whose
 * own trailing Output_WriteFormatted also uses the argument-free
 * asc_508250. The a10==0 success tail (133098-133103) reaches two MORE
 * Output_WriteFormatted calls using aSS_0/aExternSS ("%s %s[] = {\n" /
 * "extern %s %s[];\n"), each wanting 2 string args while the real call site
 * only supplies 1 (a8, a genuinely decompiler-lost second vararg) -- so
 * whatever garbage lands in the missing %s slot could fault inside the
 * formatter. TOUCH-only for that one: it should at minimum bank 133098-101
 * (arguably 102/103 too, if the missing vararg happens to be readable). == */
TEST(cov4_07_ccfo, a1_nonzero_early_return) {
  static int a5val = 7;
  TOUCH(Rules_ConstructCodeFileOpen(99, "cov4_07", 0, (const char *)(intptr_t)1,
                                     &a5val, 0, 0, 'x', "cov4_07_a9", 0, 0));
}

TEST(cov4_07_ccfo, a10_nonzero_open_success) {
  static const char *a11arr[3];
  static char pathPrefix[512];

  /* Plain /tmp (rather than this session's scratchpad dir) so the file
   * write target is stable across whatever environment actually builds and
   * runs this test suite. */
  snprintf(pathPrefix, sizeof pathPrefix, "/tmp/cov4_07_ccfo_a10_");
  a11arr[0] = pathPrefix;
  a11arr[1] = (const char *)(intptr_t)3;
  a11arr[2] = (const char *)(intptr_t)4;

  TOUCH(Rules_ConstructCodeFileOpen(0, 0, 0, 0, 0, 0, 0, 'y', 0, 1, a11arr));
}

TEST(cov4_07_ccfo, a10_zero_open_success) {
  static int a5val = 3;
  static char pathPrefix[512];

  snprintf(pathPrefix, sizeof pathPrefix, "/tmp/cov4_07_ccfo_a10z_");

  TOUCH(Rules_ConstructCodeFileOpen(0, pathPrefix, 5, (const char *)(intptr_t)2,
                                     &a5val, 9, 0, 'z', "cov4_07_a9z", 0, 0));
}

/* =========================================================================
 * Rules_ListInstancesForClassOrModule: a3!=0 (99180) reads uninitialized
 * locals feeding Class_LookupByModule directly (v11/v10 are leftover
 * registers from the discarded Module_GetCurrent() call, not real
 * parameters) -- test_cov11.c already documented this as unsafe to
 * construct; not attempted here either. a3==0 && a4!=0 (99191) walks the
 * SAME Class_GetNextRecord(0) module-item-list enumeration rig used above
 * for MessageHandler_UndefineForClassOrAll. a3==0 && a4==0 (99197-99205)
 * needs Rules_GetNextInstanceInScope(0) to find a real instance: pointing
 * dword_51AD0C at a fake instance whose owning class (offset44) is our
 * fake, always-in-scope class record makes Class_IsInScope's first check
 * true, so the search loop never iterates and returns that same instance
 * immediately (matching this codebase's repeated "possibly-undefined
 * register reused" wire-through this suite already established for
 * comparable cases -- Class_LookupInScope, Rules_RtnUnknown, etc.). ====== */
TEST(cov4_07_instances, class_or_module_all_classes_one_class) {
  static _DWORD moduleStruct[16];
  static _DWORD itemsArray[32];
  static _DWORD listWrapper[8];
  static _DWORD fakeClassRecord[32];
  int savedCurrentModule = dword_51A9B0;
  int savedClassSlot;

  memset(moduleStruct, 0, sizeof moduleStruct);
  memset(itemsArray, 0, sizeof itemsArray);
  memset(listWrapper, 0, sizeof listWrapper);
  memset(fakeClassRecord, 0, sizeof fakeClassRecord);

  savedClassSlot = dword_54E6BC;
  dword_54E6BC = 0;
  moduleStruct[2] = (_DWORD)(intptr_t)itemsArray;
  itemsArray[0] = (_DWORD)(intptr_t)listWrapper;
  listWrapper[1] = (_DWORD)(intptr_t)fakeClassRecord;
  dword_51A9B0 = (int)(intptr_t)moduleStruct;

  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 0, 1));

  dword_51A9B0 = savedCurrentModule;
  dword_54E6BC = savedClassSlot;
}

TEST(cov4_07_instances, class_or_module_scope_walk_one_instance) {
  static _DWORD fakeInstance[32];
  int *fakeClass;
  int saved51AD0C = dword_51AD0C;
  int saved51AD68 = dword_51AD68;
  int saved51A9B0 = dword_51A9B0;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  fakeClass = cov4_07_register_fake_class("Cov4_07FakeInstanceOwner");

  memset(fakeInstance, 0, sizeof fakeInstance);
  fakeInstance[11] = (_DWORD)(intptr_t)fakeClass; /* offset44: owning class ptr */
  dword_51AD0C = (int)(intptr_t)fakeInstance;

  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 0, 0));

  dword_51AD0C = saved51AD0C;
  dword_51AD68 = saved51AD68;
  dword_51A9B0 = saved51A9B0;
}

/* =========================================================================
 * Skipped, with rationale (per cov4 instructions, "genuinely unreachable /
 * hard ceiling -- note and move on"):
 *
 * - Rules_MathCsch (129819-129827): identical hard ceiling to
 *   Rules_AtanBuiltin above, already exhaustively retried by
 *   test_cov3_07.c's csch_retry_for_leftover_register_luck test.
 *
 * - Building_ApplySiegeDamageToWallSections (33549): test_cov3_07.c already
 *   built a fixture assuming the decompiler-undefined 'v10' aliases 'a1',
 *   and that line is STILL uncovered per this batch, so that assumption
 *   does not hold in the real compiled binary. Genuinely-undefined register
 *   feeding a byte dereference right before this line; not re-attempted.
 *
 * - WCIsvListBase_PopFrontValue (56181, "if (!link) return a2;"): PROVABLY
 *   dead code. WCCompat_LinkFromHandle is a pure identity cast
 *   ((WCCompatLink*)(uintptr_t)handle) -- it can only return NULL when its
 *   input is 0. WCIsvListBase_base_sget() already performs this exact same
 *   check internally before returning a truthy link_handle, so by the time
 *   PopFrontValue re-resolves that handle, it is structurally guaranteed
 *   non-NULL. No fixture can reach this line.
 *
 * - Compat_StringHolderInsertText (86854, "if (!copy) return;" after
 *   Compat_AllocLow32Bytes fails): the only way to make this real allocator
 *   fail (compat/decomp_runtime_stubs.c) for a moderate request is to
 *   exhaust the MAP_32BIT-restricted low address space, which needs
 *   existing_size+inserted_size to approach ~2GB -- i.e. constructing
 *   gigabyte-scale strings in a unit test. Impractical for this pass.
 *
 * - Compat_FileSystemOpenIfReady (88694/88696): Compat_FileSystemQueryOpen
 *   always falls through to the real FileSystem_DiskMountOpenFileQuery /
 *   File_OpenMountRootEntry mount-query chain for any non-null vtable'd
 *   input; getting a genuinely "ready" or "not ready" opened_query back
 *   needs a fully fabricated mounted-filesystem object graph. Out of scope.
 *
 * - Defgeneric_GetDefmethodListCommand line 119708 (the CheckGenericExists
 *   "true" branch) and Rules_ListInstancesForClassOrModule line 99180: see
 *   inline rationale above each respective test.
 * ========================================================================= */
