/* cov4_01: final-pass, precise-line coverage for a mixed batch of functions
 * (see scratchpad/cov4_batches/cov4_01.json for the exact uncovered
 * clash95.c line numbers targeted below):
 * Parser_CollectFunctionArguments, Rules_GetTypeNameTokenCode,
 * Rules_PatchDeftemplateSlotModuleRef, Rules_MathLog,
 * Compiler_GenerateConstructTables, WorldMap_Initialize,
 * Rules_ReadLineWithEscaping, Map_RevealTilesInRadius2ForPlayer,
 * CRT_FormatPaddedHexDigits, Rules_MVDeleteFunction,
 * Class_ClassSuperclassesCommand, Building_NewAt, Rules_ReportSymbolTypeError,
 * Rules_HostSymbolp, Unit_BuildSelectedUnitPanelIconSpritePath,
 * Castle_DrawAllAmbientAnimationLayers, BattleMap_GetOutcomeVariantFileName,
 * Compat_StringHolderFindSubstringOffset, Instance_NotifyCreated,
 * Rules_BatchCommand, Rules_SinhBuiltin, Instance_MakeInstanceFunction,
 * Rules_MatchesCommand, Rules_FindExistingJoinTestNode.
 *
 * Every test runs isolated in its own forked child (fork()+alarm(8) per
 * tests/unit/test_all.c), so calls that crash/exit/hang are safe -- new
 * coverage is banked up to whatever point execution reached. Buffers whose
 * address gets threaded through a narrowed 32-bit int/_DWORD field (64-bit
 * -no-pie build; stack addresses truncate to garbage through such a field)
 * are declared `static`. */

/* =========================================================================
 * Shared helper: the plain "argument anchor" trick (same shape as
 * tests/unit/cases/test_cov3_07.c's cov3_07_arg1) for the Rules_RtnUnknown /
 * Lexer_ParseValueList family: dword_51A960+6 is the head of a chain of
 * "argument nodes" (int16 type_tag @ +0; DWORD value_ptr @ +2; DWORD next @
 * +10). Parser_ParseForm's "simple literal" case (type_tag in
 * {0,1,2,3,5,7,8}) copies type_tag/value_ptr straight into the caller's
 * out-param without evaluating anything, and Lexer_ParseValueList's exact
 * type-match fast path (`a3 == <raw arg type>`) succeeds whenever the
 * requested type code equals the node's own type_tag -- so pointing a node's
 * value_ptr at our own scratch buffer (value stored at buffer+16, per this
 * codebase's atom-value convention) gives Lexer_ParseValueList/Rules_RtnUnknown
 * a real, well-typed argument deterministically, with no funcrec/symnode
 * fallback needed since we always supply enough real nodes for the
 * requested argument index. ========================================== */
static void cov4_01_arg1(unsigned char *anchor, unsigned char *node, short tag,
                          void *valptr) {
  memset(anchor, 0, 32);
  memset(node, 0, 32);
  *(short *)node = tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)valptr;
  *(_DWORD *)(node + 10) = 0;
  *(_DWORD *)(anchor + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

static void cov4_01_arg2(unsigned char *anchor, unsigned char *node1,
                          unsigned char *node2, short tag1, void *valptr1,
                          short tag2, void *valptr2) {
  memset(anchor, 0, 32);
  memset(node1, 0, 32);
  memset(node2, 0, 32);
  *(short *)node2 = tag2;
  *(_DWORD *)(node2 + 2) = (_DWORD)(intptr_t)valptr2;
  *(_DWORD *)(node2 + 10) = 0;
  *(short *)node1 = tag1;
  *(_DWORD *)(node1 + 2) = (_DWORD)(intptr_t)valptr1;
  *(_DWORD *)(node1 + 10) = (_DWORD)(intptr_t)node2;
  *(_DWORD *)(anchor + 6) = (_DWORD)(intptr_t)node1;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

/* Shared helper: fake character-source IO router (same shape as
 * test_cov3_02.c's cov3_02_install_lex_router). IO_RouterMatchesName only
 * requires offset4 (active) truthy and offset12 (query) returning exactly 1,
 * so the "name" argument passed to Lexer_PeekChar is irrelevant -- our query
 * callback matches unconditionally. */
static int cov4_01_lex_query(int a1) {
  (void)a1;
  return 1;
}
static int cov4_01_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}
static const char *cov4_01_lex_seq;
static int cov4_01_lex_pos;
static int cov4_01_lex_read(int a1) {
  unsigned char c;
  (void)a1;
  c = (unsigned char)cov4_01_lex_seq[cov4_01_lex_pos];
  if (c)
    ++cov4_01_lex_pos;
  else
    c = ' ';
  return c;
}
static void cov4_01_install_lex_router(_DWORD *router, const char *seq) {
  memset(router, 0, 16 * sizeof(_DWORD));
  router[1] = 1; /* offset4: active */
  router[3] = (_DWORD)(intptr_t)cov4_01_lex_query; /* offset12 */
  router[6] = (_DWORD)(intptr_t)cov4_01_lex_read;  /* offset24 */
  router[7] = (_DWORD)(intptr_t)cov4_01_lex_skip;  /* offset28 */
  g_IO_RouterListHead = (int)(intptr_t)router;
  cov4_01_lex_seq = seq;
  cov4_01_lex_pos = 0;
}

/* Shared helper: register one fake class record in the class hash table (same
 * recipe as test_cov3_02.c's cov3_02_register_fake_class), for the
 * Class_LookupInScope / Class_LookupByQualifiedName family. */
static int *cov4_01_register_fake_class(const char *name) {
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

  classRecord[0] = (_DWORD)(intptr_t)symbol;     /* offset0: class-name symbol */
  *((unsigned char *)classRecord + 20) |= 1;      /* offset20 bit0: "defined" */
  classRecord[25] = 0;                            /* offset100: next-in-bucket */
  classRecord[26] = (_DWORD)(intptr_t)scopeInfo;  /* offset104: scope info ptr */

  classTable[bucket % 0xA7u] = (_DWORD)(intptr_t)classRecord;
  g_DefclassHashTable = (int)(intptr_t)classTable;

  fakeModule[6] = 0; /* offset24: bit index 0 into the scope bitmask */
  g_Clips_CurrentModule = (int)(intptr_t)fakeModule;

  return (int *)(intptr_t)classRecord;
}

/* =========================================================================
 * Parser_CollectFunctionArguments (target lines: 151974,976,977,979-982,984,
 * 986-989). test_cov3_02.c already tried a router-fed two-symbol sequence and
 * an "unexpected token" sequence, yet these lines remain uncovered per this
 * batch -- v5 (initial v10[0]) and v8 (the running "last appended node"
 * pointer) are both decompiler-lost locals never assigned in the visible
 * source, so whether the loop's branches are taken depends on register
 * garbage left over from the exact preceding call sequence, not on anything
 * this test can force directly. Retry with a few different token sequences /
 * stack contexts (same spirit as test_cov3_07.c's "retry from a fresh call
 * site" trick) to gather a fresh chance at a favorable garbage value. */
TEST(cov4_01_collectargs, two_symbols_then_eof_fresh_context) {
  static _DWORD router[16];
  static _DWORD a1buf[64];
  int saved604 = g_IO_RouterListHead;
  char pad[64];
  memset(pad, 0x11, sizeof pad);
  memset(a1buf, 0, sizeof a1buf);
  cov4_01_install_lex_router(router, "xy zw");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(pad[0]);
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 424242, 0));

  g_IO_RouterListHead = saved604;
}

TEST(cov4_01_collectargs, three_symbols_then_eof_fresh_context) {
  static _DWORD router[16];
  static _DWORD a1buf[64];
  int saved604 = g_IO_RouterListHead;
  char pad[128];
  memset(pad, 0x22, sizeof pad);
  memset(a1buf, 0, sizeof a1buf);
  cov4_01_install_lex_router(router, "qr st uv");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(pad[1]);
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 434343, 0));

  g_IO_RouterListHead = saved604;
}

TEST(cov4_01_collectargs, unexpected_token_immediately_fresh_context) {
  static _DWORD router[16];
  static _DWORD a1buf[64];
  int saved604 = g_IO_RouterListHead;
  char pad[32];
  memset(pad, 0x33, sizeof pad);
  memset(a1buf, 0, sizeof a1buf);
  cov4_01_install_lex_router(router, "|)");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(pad[2]);
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 444444, 0));

  g_IO_RouterListHead = saved604;
}

/* =========================================================================
 * Rules_GetTypeNameTokenCode (target: 179354,356,358,364,368,372,376,380,384,
 * 391): a pure sequential strcmp_ chain against fixed uppercase type-name
 * string constants (aSymbol_7="SYMBOL", aString_3="STRING", etc.) -- no
 * engine bootstrap needed at all, just feed the exact matching literal for
 * each still-uncovered branch. ========================================= */
TEST(cov4_01_typenametoken, string_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"STRING"), 3);
}
TEST(cov4_01_typenametoken, lexeme_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"LEXEME"), 111);
}
TEST(cov4_01_typenametoken, integer_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"INTEGER"), 1);
}
TEST(cov4_01_typenametoken, number_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"NUMBER"), 110);
}
TEST(cov4_01_typenametoken, instance_name_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"INSTANCE-NAME"), 8);
}
TEST(cov4_01_typenametoken, instance_address_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"INSTANCE-ADDRESS"), 7);
}
TEST(cov4_01_typenametoken, instance_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"INSTANCE"), 112);
}
TEST(cov4_01_typenametoken, external_address_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"EXTERNAL-ADDRESS"), 5);
}
TEST(cov4_01_typenametoken, fact_address_type) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"FACT-ADDRESS"), 6);
}
TEST(cov4_01_typenametoken, float_type_falls_through_to_result) {
  CHECK_EQ(Rules_GetTypeNameTokenCode((int)(intptr_t)"FLOAT"), 0);
}

/* =========================================================================
 * Rules_PatchDeftemplateSlotModuleRef (target: 106930,936,938,939,940,942,
 * 943,944). test_cov3_07.c's existing test drives exactly one module-enum
 * trip with an all-zero fake module whose Rules_GetNextDeftemplate(0) result
 * is 0 (never breaks the outer while(1)), documenting that the nested
 * deftemplate-walk loop was out of scope for that batch. Here we wire up a
 * real (fake) per-module construct-item array so Class_Enum(0,dword_54E654)
 * -> Module_GetItem(0,0) -> itemArray[0] -> Rules_GetModuleConstructListHead
 * (*(item+4)) resolves to a real first "deftemplate" record, breaking the
 * outer loop and entering the inner "while (v5 != *(v4+32))" walk (v5 aliases
 * this function's own a1 search key, matching Rules_DeleteFunction's
 * analogous *(v6[2]+16) pattern one function above; v7 aliases the final
 * matched v4). Two shapes: a 2-deftemplate chain whose second entry matches
 * a1 (normal-exit through the patch+return lines), and a single non-matching
 * deftemplate with no further link (forces "goto LABEL_5" when
 * Rules_GetNextDeftemplate exhausts the chain). ======================== */
TEST(cov4_01_patchdeftemplate, two_deftemplate_chain_second_matches) {
  static _DWORD fakeModule[16];
  static _DWORD itemArray[4];
  static _DWORD moduleItem[8];
  static _DWORD dt1[16], dt2[16];
  int savedNextEnum = g_DefmoduleListHead;

  Mem_InitReserveBlock(0, 0);
  memset(fakeModule, 0, sizeof fakeModule);
  memset(itemArray, 0, sizeof itemArray);
  memset(moduleItem, 0, sizeof moduleItem);
  memset(dt1, 0, sizeof dt1);
  memset(dt2, 0, sizeof dt2);

  fakeModule[2] = (_DWORD)(intptr_t)itemArray; /* offset8: per-construct array */
  itemArray[0] = (_DWORD)(intptr_t)moduleItem; /* dword_54E654 == 0 by default */
  moduleItem[1] = (_DWORD)(intptr_t)dt1;       /* offset4: deftemplate list head */

  dt1[4] = (_DWORD)(intptr_t)dt2; /* offset16: next deftemplate in module */
  dt1[8] = 0xAAAA;                /* offset32: module-ref field, != search key */
  dt2[4] = 0;                     /* offset16: end of chain */
  dt2[8] = 12345;                 /* offset32: matches search key -> normal exit */

  g_DefmoduleListHead = (int)(intptr_t)fakeModule;
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(12345, 999));
  g_DefmoduleListHead = savedNextEnum;
}

TEST(cov4_01_patchdeftemplate, single_nonmatching_deftemplate_takes_goto) {
  static _DWORD fakeModule[16];
  static _DWORD itemArray[4];
  static _DWORD moduleItem[8];
  static _DWORD dt1[16];
  int savedNextEnum = g_DefmoduleListHead;

  Mem_InitReserveBlock(0, 0);
  memset(fakeModule, 0, sizeof fakeModule);
  memset(itemArray, 0, sizeof itemArray);
  memset(moduleItem, 0, sizeof moduleItem);
  memset(dt1, 0, sizeof dt1);

  fakeModule[2] = (_DWORD)(intptr_t)itemArray;
  itemArray[0] = (_DWORD)(intptr_t)moduleItem;
  moduleItem[1] = (_DWORD)(intptr_t)dt1;

  dt1[4] = 0;      /* offset16: no further deftemplate -> forces goto LABEL_5 */
  dt1[8] = 0xBBBB; /* offset32: never matches search key 12345 */

  g_DefmoduleListHead = (int)(intptr_t)fakeModule;
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(12345, 999));
  g_DefmoduleListHead = savedNextEnum;
}

/* =========================================================================
 * Rules_MathLog (target: 129990,992,993,995,996,997,998): identical shape to
 * test_cov3_02.c's Rules_MathLog10 battery -- a single real FLOAT literal
 * argument (exact type-match with Rules_MathParseSingleArg's a3==0 request)
 * drives the domain-error, overflow-error and success log() branches. ===== */
TEST(cov4_01_mathlog, negative_argument_domain_error) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  memset(val, 0, sizeof val);
  *(double *)(val + 16) = -3.0;
  cov4_01_arg1(anchor, node, 0 /* FLOAT */, val);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

TEST(cov4_01_mathlog, zero_argument_overflow_error) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 0.0;
  cov4_01_arg1(anchor, node, 0, val);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

TEST(cov4_01_mathlog, positive_argument_success) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 42.0;
  cov4_01_arg1(anchor, node, 0, val);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathLog(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* =========================================================================
 * Rules_SinhBuiltin (target: 129771 -- the sinh(v5[0]) success return): same
 * single-real-FLOAT-argument recipe. ==================================== */
TEST(cov4_01_sinhbuiltin, real_float_argument_success) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  memset(val, 0, sizeof val);
  *(double *)(val + 16) = 1.5;
  cov4_01_arg1(anchor, node, 0, val);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_SinhBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* =========================================================================
 * Compiler_GenerateConstructTables (target: 174518-174523): every "filepath"
 * first-argument threaded through this entire six-call chain
 * (Compiler_Write*File(v1/v3/v5/v7/v9/v11, ...)) is its own decompiler-lost
 * local (see the trailing "possibly undefined" comments for v1,v3,v5,v7,v9,
 * v11 right after this function) -- none of them derive from any parameter
 * this test controls, and Compiler_WriteConstantsReferenceFile's first
 * parameter is a real `const char *` that gets dereferenced as a path
 * immediately. One attempt below banks whatever prefix of the chain survives
 * before the inevitable garbage-pointer dereference; per the harness's crash
 * isolation this cannot regress anything even if it faults immediately after
 * entering the first Write call. ======================================== */
TEST(cov4_01_genconstructtables, single_attempt_lost_filepath_chain) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Compiler_GenerateConstructTables(0));
}

/* =========================================================================
 * WorldMap_Initialize (target: 21693-21696): deliberately NOT exercised here.
 * WorldMap_LoadResources unconditionally Mem_Alloc()s (a real malloc-backed
 * allocator that always succeeds regardless of engine bootstrap) and then
 * calls DLXSpriteSet_Load(buf, "frame.s32"); with no game asset directory
 * present in this environment, FileSystem_ResolveReadPath always fails,
 * which drives DLXSpriteSet_Load's __noreturn App_RequestQuit() ->
 * CRT_ExitProcessWithFinalizers() path deterministically (confirmed by
 * test_cov01.c's own isolated-run note). That terminates the forked child
 * before WorldMap_LoadResources can ever return, so WorldMap_Initialize's
 * four lines after the WorldMap_LoadResources call are unreachable in this
 * harness regardless of arguments; test_cov3_06.c already attempted the
 * plain call and, per this batch's line list, did not get past it either. */

/* =========================================================================
 * Rules_ReadLineWithEscaping (target: 125860,862,863,865): install the fake
 * lex router (same shape used throughout the cov3 batches) with a sequence
 * that yields one non-terminator character before a newline, so the while
 * loop's body (Str_AppendCharEscaping + re-peek) executes once and then
 * exits normally into the final flush call. *a3 (capacity) and *a2 (length)
 * both start at 0 so Str_AppendCharEscaping's own realloc-from-NULL path
 * runs cleanly via Mem_Realloc. ========================================= */
TEST(cov4_01_readlinewithescaping, one_char_then_newline) {
  static _DWORD router[16];
  int saved604 = g_IO_RouterListHead;
  int length = 0;
  unsigned int capacity = 0;
  unsigned int savedEvalErr = g_ClipsHaltExecution;

  cov4_01_install_lex_router(router, "Q\n");
  g_ClipsHaltExecution = 0; /* Rules_GetEvaluationErrorFlag() must read false */

  /* Channel id must differ from dword_51A608's default (0), otherwise
   * Lexer_PeekChar takes the unrelated "current input file" fast path
   * instead of walking the dword_51A604 router chain. */
  TOUCH(Rules_ReadLineWithEscaping(777, &length, &capacity, 0));

  g_IO_RouterListHead = saved604;
  g_ClipsHaltExecution = savedEvalErr;
}

/* =========================================================================
 * Map_RevealTilesInRadius2ForPlayer (target: 67280,282,283): the inner
 * do/while's exit test ("while (v5+1 < v10)") compares against v5, a
 * decompiler-lost local ("possibly undefined") never assigned anywhere in
 * the visible source -- its value is whatever register garbage happens to be
 * live at that point, so whether the outer for-loop's body ever finishes an
 * iteration (reaching ++v3/Locale_DrawInteger/the closing brace) is not
 * something this test can force directly. test_cov2_02.c already tried
 * (10,10,0) without reaching these lines. Retry with a few different
 * arguments / preceding stack perturbations (same idea as
 * test_cov3_07.c's Rules_MathCsch retry) for a fresh chance at a favorable
 * garbage value; each gets its own forked child so a hang is capped at the
 * 8s alarm and cannot cost other tests anything. ======================== */
TEST(cov4_01_revealtiles, radius2_alternate_coords_a) {
  char pad[64];
  memset(pad, 0x44, sizeof pad);
  TOUCH(pad[0]);
  TOUCH(Map_RevealTilesInRadius2ForPlayer(3, 3, 0));
}

TEST(cov4_01_revealtiles, radius2_alternate_coords_b) {
  char pad[96];
  memset(pad, 0x55, sizeof pad);
  TOUCH(pad[0]);
  TOUCH(Map_RevealTilesInRadius2ForPlayer(0, 0, 0));
}

/* =========================================================================
 * CRT_FormatPaddedHexDigits (target: 105199,200,201): the reverse-copy loop
 * body just needs Str_FormatSignedRadixDigits to produce any non-empty hex
 * string in a2, which it always does (even "0" for a1==0) -- pure
 * straight-line coverage, no engine bootstrap needed. =================== */
TEST(cov4_01_formatpaddedhex, nonzero_value_padded) {
  static char buf[32];
  memset(buf, 0, sizeof buf);
  TOUCH(CRT_FormatPaddedHexDigits(0x1A2B, buf, 8));
}

/* =========================================================================
 * Rules_MVDeleteFunction (target: 127261,262,267): two real arguments (exact
 * type-match, per the shared arg-chain helper): an INTEGER literal for the
 * a3==1 request (Lexer_ParseValueList(1,&v6,1,a3)) and a MULTIFIELD
 * descriptor for the a3==4 request (Lexer_ParseValueList(2,v5,4,a3)), giving
 * Rules_MultifieldDeleteRange a well-formed multifield/begin/end input (the
 * decompiler-lost "v7" alias resolves to the first parse's own out-buffer
 * index2, i.e. our own val1 pointer, per the identical pattern in the
 * adjacent, non-decompiler-lost Rules_DeleteFunction just above this
 * function, which uses `v6[2]+16`/`v7[2]+16` directly on its own equivalent
 * buffers). ============================================================= */
TEST(cov4_01_mvdelete, integer_index_and_multifield_argument) {
  static unsigned char anchor[32], node1[32], node2[32];
  static unsigned char val1[32];
  static _DWORD mfHeader[8];
  static _DWORD storage[128];
  static _DWORD out[16];

  memset(val1, 0, sizeof val1);
  memset(mfHeader, 0, sizeof mfHeader);
  memset(storage, 0, sizeof storage);
  memset(out, 0, sizeof out);

  *(int *)(val1 + 16) = 0; /* begin==end==0 range to delete */
  mfHeader[2] = (_DWORD)(intptr_t)storage; /* offset8: base */
  mfHeader[3] = 0;                         /* offset12: begin */
  mfHeader[4] = 2;                         /* offset16: end (3 elements) */

  cov4_01_arg2(anchor, node1, node2, 1 /* INTEGER */, val1, 4 /* MULTIFIELD */,
               mfHeader);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MVDeleteFunction(out, 0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* =========================================================================
 * Class_ClassSuperclassesCommand (target: 173545,546,548): a real, registered
 * SYMBOL class-name argument drives Class_ParseClassNameAndInheritFlag's
 * single-arg success path (returning the class record directly), reaching
 * the Class_SuperclassesFunction call; a plain empty argument chain drives
 * Rules_RtnArgCount()==0, hitting the "else" Rules_SetMultifieldErrorValue
 * fallback deterministically. ========================================== */
TEST(cov4_01_classsuperclasses, real_class_lookup_success) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  static const char class_name[] = "Cov4_01FakeClassSuper";
  int saved51AD68 = g_DefclassHashTable;
  int saved51A9B0 = g_Clips_CurrentModule;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov4_01_register_fake_class(class_name);

  memset(val, 0, sizeof val);
  *(const char **)(val + 16) = class_name;
  cov4_01_arg1(anchor, node, 2 /* SYMBOL */, val);

  TOUCH(Class_ClassSuperclassesCommand(1, 1.0));

  g_ClipsCurrentExpression = 0;
  g_DefclassHashTable = saved51AD68;
  g_Clips_CurrentModule = saved51A9B0;
}

TEST(cov4_01_classsuperclasses, empty_argument_chain_error_path) {
  int saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = 0;
  TOUCH(Class_ClassSuperclassesCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* =========================================================================
 * Building_NewAt (target: 34320,321): Building_New immediately reads
 * `gameData + 725*stack_index + 147178` for g_CurrentPlayerIndex; with
 * gameData==0 (never set up by Game_Init in this harness) that's a
 * guaranteed segfault (documented in test_cov03.c). Pointing gameData at a
 * real zeroed static buffer avoids that crash; with row==col==0 and
 * stack_index==0, MapTile_IsCastleFoundationTile(0,0,building_type=0) ->
 * Map_GetTileSurfaceClassOrUnexplored(0,0) reads all-zero tile data (v4=207,
 * "unexplored") and Map_IsTileVisibleToPlayer(0,0,0) reads a zeroed map
 * width/height (both 0), so `0 < 0` is false and visibility is false too,
 * giving Map_GetTileSurfaceClassOrUnexplored's "not visible" result of 1 --
 * which matches MapTile_IsCastleFoundationTile's very first exclusion check
 * (v4==1), returning 0 immediately. With force(a5)==0, Building_New's
 * `if (!result) return result;` then returns false right away, well before
 * any of the function's much riskier, deeper gameData offsets are touched --
 * letting Building_NewAt reach its post-Building_New epilogue. ========== */
TEST(cov4_01_buildingnewat, safe_zeroed_gamedata_early_false_return) {
  static unsigned char fakeGameData[200000];
  int saved = gameData;
  memset(fakeGameData, 0, sizeof fakeGameData);
  gameData = (int)(intptr_t)fakeGameData;

  TOUCH(Building_NewAt(0, 0, 0, 0, 0.0, "cov4_01_bld", 0));

  gameData = saved;
}

/* =========================================================================
 * Rules_ReportSymbolTypeError (target: 100323,324): Rules_MakeSymbol just
 * needs the atom-table bootstrap to succeed (interning a fresh symbol always
 * returns non-NULL); the freshly-interned symbol's restriction-string field
 * (offset+17) is zero, so Rules_GetArgRestrictionType safely returns its
 * default (117) without touching anything risky, and Rules_GetArgTypeName /
 * Parser_ReportError are both pure/safe formatting helpers used pervasively
 * elsewhere in this suite. ============================================= */
TEST(cov4_01_reportsymboltypeerror, fresh_symbol_reaches_error_report) {
  static const char sym_name[] = "cov4_01_symtypeerror";
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ReportSymbolTypeError((_BYTE *)sym_name, 0));
}

/* =========================================================================
 * Rules_HostSymbolp (target: 126037,038): a real single SYMBOL argument
 * (exact type-match) makes Lexer_TokenExpect(1) succeed and Rules_RtnUnknown
 * populate v3[1]==2, driving the "return 1" line. ======================= */
TEST(cov4_01_hostsymbolp, real_symbol_argument) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  static const char sym_name[] = "cov4_01_hostsymbolp_sym";
  memset(val, 0, sizeof val);
  *(const char **)(val + 16) = sym_name;
  cov4_01_arg1(anchor, node, 2 /* SYMBOL */, val);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_HostSymbolp(0.0));
  g_ClipsCurrentExpression = 0;
}

/* =========================================================================
 * Unit_BuildSelectedUnitPanelIconSpritePath (target: 27728): the third of
 * four identical 2-byte-at-a-time copy loops always copies from a *fixed*
 * local buffer the function itself initializes via `strcpy(v23, "c")` --
 * regardless of any caller argument. "c\0" is exactly 2 bytes, so the loop's
 * very first iteration reads v14='c' (nonzero, doesn't break) then
 * v15=v12[1]=0 (the terminator, landing in the *second* byte of the pair),
 * ending the loop via the bottom `while(v15)` check without ever taking the
 * top `if(!v14) break;` -- this specific line is provably unreachable for
 * any input, since the source string is a hardcoded internal constant, not
 * something a test can vary. Left uncovered; no test added. */

/* =========================================================================
 * Castle_DrawAllAmbientAnimationLayers (target: 37356 -- the final `return
 * result;` after the for-loop completes all 10 iterations):
 * Castle_DrawAmbientAnimationLayer dereferences g_SelectedBuildingRecord+416
 * (and, for case 6, +4) unconditionally in every switch case; with
 * g_SelectedBuildingRecord==0 (default) that's a guaranteed segfault.
 * Pointing it at a real zeroed static buffer makes every case's flag-bit
 * check read 0 (all flags clear), so none of the
 * Castle_DrawAmbientAnimationSprite calls fire and the loop completes
 * cleanly across all 10 iterations, reaching the final return. ========= */
TEST(cov4_01_castleambient, zeroed_building_record_all_flags_clear) {
  static unsigned char fakeRecord[512];
  int saved = g_SelectedBuildingRecord;
  memset(fakeRecord, 0, sizeof fakeRecord);
  g_SelectedBuildingRecord = (int)(intptr_t)fakeRecord;

  TOUCH(Castle_DrawAllAmbientAnimationLayers((void *)(intptr_t)fakeRecord));

  g_SelectedBuildingRecord = saved;
}

/* =========================================================================
 * BattleMap_GetOutcomeVariantFileName (target: 59335 -- the `name = a1;`
 * "no backslash found" fallback): BattleMapFileName unconditionally begins
 * with `strcpy(a1, aMaps)` where aMaps == "maps\\" (a literal backslash),
 * and only ever *appends* further characters afterward -- so any successful
 * call leaves a1 with a backslash always present, making strrchr(a1,'\\')
 * return non-NULL deterministically. This line is structurally unreachable
 * through a normal call to this function; no test added. */

/* =========================================================================
 * Compat_StringHolderFindSubstringOffset (target: 86991): `strstr_` is
 * declared only as an untyped weak data symbol (`_UNKNOWN strstr_; // weak`)
 * with no definition anywhere in clash95.c or compat/ -- as a weak common
 * symbol it resolves to address 0, so the call
 * `((int(*)(int))strstr_)(a3)` unconditionally jumps to NULL and segfaults
 * the instant `a2 && *a1` are both true, before ever reaching the `!= 0`
 * comparison that guards line 86991. That return line is unreachable in this
 * build regardless of arguments; no test added. */

/* =========================================================================
 * Instance_NotifyCreated (target: 102600 -- the function's epilogue, i.e.
 * Rules_ObjectMatchAction must actually return): test_cov11.c and
 * test_cov2_02.c already call this with an all-zero object buffer, but
 * a1==(unsigned __int16*)1 drives Rules_ObjectMatchAction into
 * Rules_AssertNewObjectIntoNetwork -> Rules_MarkDependentRulesForSlotChange,
 * which unconditionally reads `*(_DWORD*)(dword_51B478 + 44)` (dword_51B478
 * having just been set to our object pointer) and then dereferences *that*
 * pointer's own +24 field -- with an all-zero object, offset+44 is 0, so the
 * next dereference (0+24) segfaults. Pointing our object's offset+44 field at
 * a second real (zeroed) scratch buffer avoids that crash; with all the
 * relevant globals (dword_51AEB4, dword_51AEB0, dword_51AEAC, dword_51AEA8,
 * dword_51A958) at their pristine zero defaults, every subsequent traversal
 * this call chain reaches is an empty-list no-op, letting
 * Rules_ObjectMatchAction run to completion. ============================ */
TEST(cov4_01_instance, notify_created_completes_without_crash) {
  static _DWORD obj[64];
  static _DWORD slotRecord[64];
  memset(obj, 0, sizeof obj);
  memset(slotRecord, 0, sizeof slotRecord);
  obj[11] = (_DWORD)(intptr_t)slotRecord; /* offset+44 */

  TOUCH(Instance_NotifyCreated(obj, 0.0));
}

/* =========================================================================
 * Rules_BatchCommand (target: 122893): same "real STRING filename argument"
 * recipe used throughout test_cov3_07.c for the sibling Rules_Load*Command
 * functions -- Rules_GetFileNameArg's v6==3 check matches our STRING-tagged
 * node exactly, returning our literal path pointer straight through, which
 * reaches the Rules_OpenBatch call regardless of whether the (nonexistent)
 * file can actually be opened. ========================================== */
TEST(cov4_01_batchcommand, real_string_filename_argument) {
  static unsigned char anchor[32], node[32];
  static unsigned char val[32];
  static const char *path = "/nonexistent/cov4_01_missing_batch_file.clp";

  /* value_ptr must point at a buffer whose +16 offset holds the string
   * pointer, matching Rules_GetFileNameArg's `*(_DWORD*)(v7+16)` read. */
  memset(val, 0, sizeof val);
  *(const char **)(val + 16) = path;
  cov4_01_arg1(anchor, node, 3 /* STRING */, val);

  TOUCH(Rules_BatchCommand(0, 0.0));
  g_ClipsCurrentExpression = 0;
}

/* =========================================================================
 * Instance_MakeInstanceFunction (target: 135354 -- the final
 * Rules_SetObjectPatternMatchDelay return, i.e. Instance_ActiveMakeInstance
 * Function must return normally): test_cov18.c and test_cov2_05.c both pass
 * small integer literals (1 or 0) as `a1`, but Instance_ActiveMakeInstance
 * Function immediately *writes* through a1 (`*(_DWORD*)(a1+4) = 2;`) --
 * a1 is really an output-object pointer, so those calls fault on that very
 * first write. Passing the address of a real static buffer for a1 fixes
 * that; feeding a single non-SYMBOL/non-INSTANCE-NAME (type_tag 1, INTEGER)
 * leading argument then drives Parser_ParseForm's tag check
 * (`parsed[1] != 2 && parsed[1] != 8`) into the function's own early,
 * lightweight "expected a value" error-report-and-return path, completely
 * avoiding the much deeper (and unreachable-without-a-full-class-system)
 * Instance_BuildInstance machinery below it. ============================ */
TEST(cov4_01_instancemake, non_symbol_argument_early_error_return) {
  static _DWORD a1buf[16];
  static unsigned char anchor[32], node[32];
  int saved = g_ClipsCurrentExpression;

  memset(a1buf, 0, sizeof a1buf);
  cov4_01_arg1(anchor, node, 1 /* INTEGER, not SYMBOL(2)/INSTANCE-NAME(8) */,
               anchor /* dummy value_ptr, never read on this path */);

  TOUCH(Instance_MakeInstanceFunction((uintptr_t)(intptr_t)a1buf, 0, 0.0));

  g_ClipsCurrentExpression = saved;
}

/* =========================================================================
 * Rules_MatchesCommand (target: 153208 -- the Rules_ListDefruleMatches
 * success return): reaching this needs Rules_FindDefruleByName to actually
 * find a defrule, which forwards into Rules_FindConstructByNameGeneric using
 * a *second* parameter that is itself decompiler-lost in Rules_MatchesCommand
 * ("v3 is possibly undefined") -- Rules_FindConstructByNameGeneric
 * immediately dereferences that parameter's own offset+16/+28 fields as
 * function pointers, so whatever register garbage ends up there is entirely
 * outside this test's control. test_cov2_09.c already reaches the
 * Rules_FindSymbolEntry-misses "not found" branch with this same recipe;
 * interning the matching symbol first at least lets the lookup itself
 * succeed, in case the garbage "v3" happens to be usable, but this is a
 * best-effort attempt against a fundamentally uncontrollable value. ===== */
TEST(cov4_01_matchescommand, interned_rule_name_construct_arg_success) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  static char ruleName[16] = "cov4_01rule";
  int saved = g_ClipsCurrentExpression;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  Str_Intern(ruleName, 0); /* pre-intern so Rules_FindSymbolEntry can hit */

  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2; /* tag == 2 -> Parser_ParseForm LABEL_4 fast path */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)termBuf + 16) = (int)(intptr_t)ruleName;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;

  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_MatchesCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* =========================================================================
 * Rules_FindExistingJoinTestNode (target: 181033 -- the "found match, return
 * v10" line): a fully deterministic fixture, chosen so that every
 * decompiler-lost/uninitialized local along the way (Rules_JoinTestNodeMatches'
 * own "v10 possibly undefined" loop-bound counter) is neutralized by
 * construction rather than relied upon:
 *  - a2==v10[4] (offset16) makes the outer index match.
 *  - node[0]==0 makes both `a4 != (node[0]&1)` and
 *    `a3 != (node[0]<<28>>31)` pass when outer a3==a4==0.
 *  - outer a5==0 short-circuits the `a3==1 && ...` sub-check to false
 *    unconditionally (a5 maps to Rules_JoinTestNodeMatches' own a3 param).
 *  - node[3]==0 (AST list) and outer a6==NULL make
 *    AST_NodeListsEqual(0,0)==1 (empty lists trivially equal).
 *  - outer a7==INT_MAX guarantees the "while(a7 < v10)" loop body never
 *    executes, for *any* possible garbage value of the undefined counter
 *    (no int can exceed INT_MAX), so v9 stays == our fake node.
 *  - node[5]==0 (offset20) makes the final
 *    `(v13 = *(v9+20)) == 0` clause true, so the overall return is true
 *    regardless of outer a8/a9. ========================================= */
TEST(cov4_01_findjointestnode, deterministic_immediate_match) {
  static _DWORD node[16];
  memset(node, 0, sizeof node);
  node[4] = 5; /* offset16: matched against outer a2 */
  node[3] = 0; /* offset12: AST list head (NULL) */
  node[5] = 0; /* offset20: forces JoinTestNodeMatches' final OR true */
  node[0] = 0; /* offset0: bit0/bit3 both clear */

  TOUCH(Rules_FindExistingJoinTestNode(node, /*a2*/ 5, /*a3*/ 0, /*a4*/ 0,
                                        /*a5*/ 0, /*a6*/ (__int16 *)0,
                                        /*a7*/ 0x7FFFFFFF, /*a8*/ 0, /*a9*/ 0,
                                        /*a10*/ 0));
}
