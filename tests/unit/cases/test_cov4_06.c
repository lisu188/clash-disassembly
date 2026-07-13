/* cov4 batch 06: final-pass precise-line coverage lift for a grab-bag of
 * mostly-covered functions (see scratchpad cov4_batches/cov4_06.json):
 * Rules_ExtractModuleAndConstructName, Rules_ParsePositiveIntArg,
 * Rules_LoadCommand, Rules_MathSqrt, Class_PrintModuleList,
 * Rules_RefreshAgendaCommand, Method_FindApplicableMethod,
 * Rules_ReorderAgenda, Rules_HostRenameFile,
 * MessageHandler_PreviewSendForSymbol, Building_CalcGarrisonStrength,
 * Compat_StringHolderAssignJoined, Rules_BsaveCommand,
 * Rules_LinkClassToSuperclasses, UnitSlots_CalcDefenseScore,
 * WCIsvListBase_CopyAppendAll, Rules_SyncArmyFactStrength,
 * Rules_ClearActivationsForModule, Rules_FindLogicalDependencyEntry,
 * Rules_SinBuiltin, Rules_WriteExpressionRefToCode, Class_IsDeletableAlt,
 * Class_ParseClassNameArg.
 *
 * ---- Shared "successful argument parse" technique (see also
 * tests/unit/cases/test_cov2_02.c / test_cov3_06.c / test_cov3_07.c) ----
 * Lexer_ParseValueList(pos, out, wanted_type, a4) / Rules_GetFileNameArg /
 * Rules_GetModuleNameArg all funnel through Rules_RtnUnknown(pos, out, a4),
 * which walks a singly linked "argument node" chain rooted at
 * dword_51A960+6 (next pointers live at node+10) to the pos'th node, then
 * calls Parser_ParseForm(node, out, (int)out, a4). For scalar tags in
 * {0,1,2,3,5,7,8} Parser_ParseForm takes its fast path: out[1] = the node's
 * tag; out[2] = the node's value pointer, whose own +16 offset holds the
 * actual scalar payload (an int at byte 16 for tag==1/2/3/8, a double at
 * byte 16 for tag==0). test_cov2_02.c's cov2_02_posintarg tests already
 * establish (via CHECK_EQ on exact returned values) that exact tag/
 * wanted_type matches are reliable in this recompiled binary despite
 * Lexer_ParseValueList's first check nominally depending on a decompiler-
 * lost register. */
static void cov4_06_arg1(unsigned char *anchor, unsigned char *node,
                          short tag, void *valptr) {
  memset(anchor, 0, 32);
  memset(node, 0, 32);
  *(short *)node = tag;
  *(int *)(node + 2) = (int)(intptr_t)valptr;
  *(int *)(node + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

static void cov4_06_arg2(unsigned char *anchor, unsigned char *node1,
                          short tag1, void *val1, unsigned char *node2,
                          short tag2, void *val2) {
  memset(anchor, 0, 32);
  memset(node1, 0, 32);
  memset(node2, 0, 32);
  *(short *)node1 = tag1;
  *(int *)(node1 + 2) = (int)(intptr_t)val1;
  *(int *)(node1 + 10) = (int)(intptr_t)node2;
  *(short *)node2 = tag2;
  *(int *)(node2 + 2) = (int)(intptr_t)val2;
  *(int *)(node2 + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node1;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

#define COV4_06_SAVE_ARGCTX()                                                \
  int cov4_06_saved960 = g_ClipsCurrentExpression;                                       \
  int cov4_06_saved964 = g_ClipsEvaluationError;                                       \
  int cov4_06_saved968 = g_ClipsHaltExecution;                                       \
  g_ClipsEvaluationError = 0;                                                          \
  g_ClipsHaltExecution = 0

#define COV4_06_RESTORE_ARGCTX()                                             \
  do {                                                                       \
    g_ClipsCurrentExpression = cov4_06_saved960;                                         \
    g_ClipsEvaluationError = cov4_06_saved964;                                         \
    g_ClipsHaltExecution = cov4_06_saved968;                                         \
  } while (0)

/* ---- Rules_ExtractModuleAndConstructName: reaching any of lines 114659-
 * 114668 requires Rules_ExtractModuleName()/Rules_ExtractConstructName() to
 * *return* (not crash). Both of those helpers immediately feed decompiler-
 * lost registers ('v4'/'v3' resp. 'v7'/'v8') straight into strncpy_(), so a
 * qualified "MOD::name" input reaches the qualifier-split logic but then
 * crashes inside the strncpy_ callee before Rules_ExtractModuleName can
 * return -- a single attempt below per the known-hard-ceiling guidance. */
TEST(cov4_06_extractmoduleconstruct, qualified_name_attempt) {
  static char qualified[] = "MOD::thing";
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ExtractModuleAndConstructName((_BYTE *)qualified));
}

/* ---- Rules_ParsePositiveIntArg: cov2_02_posintarg already CHECK_EQ-
 * verifies the positive-success (94303,304,311) and negative-report
 * (94303,304,306-309) branches via an exact INTEGER-tag match. The one gap
 * is the "Lexer_ParseValueList itself fails" branch (94302). Rules_RtnUnknown
 * dereferences dword_51A960+6 unconditionally, so dword_51A960==0 (a "no
 * chain at all" anchor) crashes before ever reaching the failure check;
 * instead keep a real, valid one-node chain (so Rules_RtnUnknown parses it
 * cleanly) but force Lexer_ParseValueList's own dword_51A964 "error already
 * flagged" gate directly, which it checks *after* calling Rules_RtnUnknown
 * and *before* looking at the parsed tag. ---- */
TEST(cov4_06_posintarg, parse_list_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 7;
  cov4_06_arg1(anchor, node, 1, val);
  g_ClipsEvaluationError = 1;
  CHECK_EQ(Rules_ParsePositiveIntArg(1, 1, 3, 0.0), -2);
  COV4_06_RESTORE_ARGCTX();
}

TEST(cov4_06_posintarg, positive_value_success) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 7;
  cov4_06_arg1(anchor, node, 1, val);
  CHECK_EQ(Rules_ParsePositiveIntArg(1, 1, 3, 0.0), 7);
  COV4_06_RESTORE_ARGCTX();
}

TEST(cov4_06_posintarg, negative_value_reports_error) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = (_DWORD)-11;
  cov4_06_arg1(anchor, node, 1, val);
  CHECK_EQ(Rules_ParsePositiveIntArg(1, 1, 3, 0.0), -2);
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Rules_LoadCommand: same "resolved-but-nonexistent path" technique as
 * test_cov3_06.c's cov3_06_loadcommand, reaching the SetLoadInProgress(1) /
 * open-failed-report branch (123169,177,178,179) plus the Rules_Load call
 * site itself (123170). A second attempt with a real (empty, existing)
 * file targets the success branch (123170,172,173); Rules_Load's own
 * decompiler-lost locals feeding Rules_LoadConstructsFromLogicalName make
 * this a best-effort attempt. ---- */
TEST(cov4_06_loadcommand, filename_parsed_open_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov4_06_missing_load.clp";
  COV4_06_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)path;
  cov4_06_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_LoadCommand(0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

TEST(cov4_06_loadcommand, filename_parsed_open_succeeds_attempt) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path =
      "/tmp/claude-0/-home-user-clash-disassembly/"
      "d4d0d676-5586-5b40-9f14-d9dffd44a5a5/scratchpad/"
      "cov4_06_empty_load.clp";
  FILE *f = fopen(path, "w");
  if (f)
    fclose(f);
  COV4_06_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)path;
  cov4_06_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_LoadCommand(0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Rules_MathSqrt: Rules_MathParseSingleArg funnels through
 * Lexer_ParseValueList(1, ..., 0, a3) (FLOAT wanted). An exact FLOAT-tag
 * fixture (double payload at byte offset 16 of a real 32-byte value
 * buffer, matching test_cov2_02.c's cov2_02_mathmod float fixtures)
 * targets both the non-negative sqrt() branch (130038,039) and the
 * negative domain-error branch (130040-043). ---- */
TEST(cov4_06_mathsqrt, non_negative_returns_sqrt) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  *(double *)((char *)val + 16) = 9.0;
  cov4_06_arg1(anchor, node, 0, val);
  TOUCH(Rules_MathSqrt(0, 0, 0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

TEST(cov4_06_mathsqrt, negative_domain_error) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  *(double *)((char *)val + 16) = -9.0;
  cov4_06_arg1(anchor, node, 0, val);
  TOUCH(Rules_MathSqrt(0, 0, 0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Rules_SinBuiltin: same Rules_MathParseSingleArg shape as
 * Rules_MathSqrt; the FLOAT-tag success fixture reaches the sin() return
 * (129519). ---- */
TEST(cov4_06_sinbuiltin, parse_succeeds_returns_sin) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  *(double *)((char *)val + 16) = 0.5;
  cov4_06_arg1(anchor, node, 0, val);
  TOUCH(Rules_SinBuiltin(0, 0, 0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Class_ParseClassNameArg: wanted_type==2 (SYMBOL); an exact SYMBOL-
 * tag fixture reaches the success return (172707). ---- */
TEST(cov4_06_parseclassnamearg, symbol_tag_success) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV4_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 42;
  cov4_06_arg1(anchor, node, 2, val);
  TOUCH(Class_ParseClassNameArg(0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Class_PrintModuleList: test_cov2_05.c's cov2_05_printmodulelist
 * already reaches everything up to (and including) the first
 * MessageHandler_EnumNext(a1,0) call by giving *(a1+4) a non-null "head"
 * pointer but leaving *(a1+88)/*(a1+96) zero (no handler records), so the
 * for-loop body itself was never entered. Rig *(a1+88) to point at one real
 * handler-record slot (36 bytes, PP-form pointer at +32) so
 * MessageHandler_EnumNext(a1,0) returns 1 (a1+88 non-null), driving the
 * loop body once: MessageHandler_GetRecordPPForm (140887), its non-null
 * check (140888), both Output_* calls (140890,891), and the next
 * MessageHandler_EnumNext call (140893) that ends the loop. ---- */
TEST(cov4_06_printmodulelist, one_handler_record) {
  static _DWORD a1buf[32];
  static unsigned char record[64];
  static const char headtext[] = "cov4_06_head";
  static const char ppform_text[] = "cov4_06 pp form";
  memset(a1buf, 0, sizeof a1buf);
  memset(record, 0, sizeof record);
  a1buf[1] = (_DWORD)(intptr_t)headtext;      /* *(a1+4): module head */
  a1buf[22] = (_DWORD)(intptr_t)record;       /* *(a1+88): handler array */
  a1buf[24] = 1;                              /* *(a1+96): handler count */
  *(int *)(record + 32) = (int)(intptr_t)ppform_text; /* record[0]+32 */
  TOUCH(Class_PrintModuleList((int)(intptr_t)a1buf));
}

/* ---- Rules_RefreshAgendaCommand: a one-node SYMBOL-tagged chain drives
 * Lexer_TokenExpect(1) to its "result==1" branch; Rules_GetModuleNameArg's
 * *a3=0 reset stays untouched (the module IS found, so the string-mismatch
 * error path that would set *a3=1 is skipped entirely), reaching the
 * "!v3[0]" success branch (97160,161). Module_FindByName needs a real
 * interned atom matching the raw name string, registered into the
 * dword_51A9AC module list (same technique as test_cov2_01.c's
 * cov2_01_printppformbyname). ---- */
TEST(cov4_06_refreshagendacmd, module_found_refreshes) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  static _DWORD module_node[32];
  static const char modname[] = "Cov4_06Module";
  int saved9AC = g_DefmoduleListHead;
  void *atom;
  COV4_06_SAVE_ARGCTX();

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  atom = Str_Intern((char *)modname, 0);

  memset(module_node, 0, sizeof module_node);
  module_node[0] = (_DWORD)(intptr_t)atom; /* module's own symbol ptr */
  module_node[7] = 0;                      /* next -> end of list */
  g_DefmoduleListHead = (int)(intptr_t)module_node;

  memset(val, 0, sizeof val);
  val[4] = (_DWORD)(intptr_t)modname;
  cov4_06_arg1(anchor, node, 2, val);
  TOUCH(Rules_RefreshAgendaCommand(0.0));

  g_DefmoduleListHead = saved9AC;
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Method_FindApplicableMethod: a2!=0 drives 164419's "v4=a2+40"
 * assignment; sizing the method table so the very first bound check fails
 * (v4 already >= 40*count+base) returns 0 immediately without ever
 * touching the decompiler-lost 'v6' used by the loop's "keep searching"
 * tail (164429-431), which is left as a documented best-effort attempt
 * below (real method-table entry, restrictions likely unsatisfied). ---- */
TEST(cov4_06_findapplicablemethod, explicit_start_out_of_range) {
  static _DWORD a1buf[16];
  memset(a1buf, 0, sizeof a1buf);
  a1buf[7] = 100; /* *(a1+28): base address of method table */
  a1buf[8] = 0;   /* *(a1+32): method count */
  TOUCH(Method_FindApplicableMethod((int)(intptr_t)a1buf, 1000, 0.0));
}

TEST(cov4_06_findapplicablemethod, one_method_restriction_check_attempt) {
  static _DWORD a1buf[16];
  static unsigned char methodrec[64];
  memset(a1buf, 0, sizeof a1buf);
  memset(methodrec, 0, sizeof methodrec);
  a1buf[7] = (_DWORD)(intptr_t)methodrec; /* *(a1+28): method table base */
  a1buf[8] = 1;                           /* *(a1+32): method count */
  TOUCH(Method_FindApplicableMethod((int)(intptr_t)a1buf, 0, 0.0));
}

/* ---- Rules_ReorderAgenda: called with result==0 drives the
 * Module_NextEnum(0)-seeded path (v2=1). Registering one fake module (via
 * dword_51A9AC, same shape as the RefreshAgendaCommand fixture above) with
 * an empty defrule-item-array entry (item+12==0, no activations) skips the
 * inner activation-splicing loop but still reaches the do-while's tail:
 * Module_NextEnum(v1) (97034), v1=Enum (97035), and the while(Enum) re-test
 * (97037), ending the outer loop when the module's own "next" field (index
 * 7) is 0. ---- */
TEST(cov4_06_reorderagenda, one_module_no_activations) {
  static _DWORD module_node[32];
  static _DWORD itemArray[32];
  static _DWORD P[8];
  int saved9AC = g_DefmoduleListHead;

  memset(module_node, 0, sizeof module_node);
  memset(itemArray, 0, sizeof itemArray);
  memset(P, 0, sizeof P);

  int i; for (i = 0; i < 32; ++i)
    itemArray[i] = (_DWORD)(intptr_t)P; /* P+12 == 0: no activation list */
  module_node[2] = (_DWORD)(intptr_t)itemArray; /* *(module+8) */
  module_node[7] = 0;                           /* *(module+28): next */
  g_DefmoduleListHead = (int)(intptr_t)module_node;

  TOUCH(Rules_ReorderAgenda(0));

  g_DefmoduleListHead = saved9AC;
}

/* ---- Rules_ClearActivationsForModule: making Rules_GetDefruleModuleItem(0)
 * resolve to a real (but activation-less) item skips the do-while loop
 * (result==0 from the start) and reaches the trailing "return result"
 * (96988) without ever touching the decompiler-lost 'v1' the loop body
 * would otherwise dereference. Rigs dword_51A9B0 -> module record ->
 * item array -> defrule module item, same shape as
 * test_cov3_05.c's cov3_05_clearactivationsformodule but with the
 * activation-list head left at 0 instead of populated. ---- */
TEST(cov4_06_clearactivationsformodule, no_activations_returns_immediately) {
  static unsigned char P[32], M[32];
  static _DWORD itemArray[8];
  int saved9B0 = g_Clips_CurrentModule;

  memset(P, 0, sizeof P);
  memset(M, 0, sizeof M);
  memset(itemArray, 0, sizeof itemArray);

  /* *(int *)(P + 12) left 0: Rules_GetDefruleModuleItem()+12 == 0 */
  itemArray[0] = (int)(intptr_t)P;
  *(int *)(M + 8) = (int)(intptr_t)itemArray;

  g_Clips_CurrentModule = (int)(intptr_t)M;
  CHECK_EQ((intptr_t)Rules_ClearActivationsForModule(), 0);
  g_Clips_CurrentModule = saved9B0;
}

/* ---- Rules_HostRenameFile: same double-Rules_GetFileNameArg-call shape as
 * Rules_LoadStarCommand/Rules_HostRemoveFile (test_cov3_07.c); a two-node
 * STRING chain resolves both filenames, reaching the second
 * Rules_GetFileNameArg call (125350), its success check (125351), and the
 * Rules_RenameFile call site (125352). Rules_RenameFile's own first
 * argument is a decompiler-lost local, so the callee itself may crash --
 * but that happens *inside* Rules_RenameFile/IO_RenameFile, after our
 * target line's coverage is already banked. ---- */
TEST(cov4_06_hostrenamefile, two_filenames_resolved) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  static const char *path1 = "/nonexistent/cov4_06_rename_src.clp";
  static const char *path2 = "/nonexistent/cov4_06_rename_dst.clp";
  COV4_06_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  val1[4] = (_DWORD)(intptr_t)path1;
  val2[4] = (_DWORD)(intptr_t)path2;
  cov4_06_arg2(anchor, node1, 3, val1, node2, 3, val2);
  TOUCH(Rules_HostRenameFile(0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- MessageHandler_PreviewSendForSymbol: Rules_FindSymbolEntry(a2) needs
 * a real registered atom to succeed, but MessageHandler_BuildPreviewHandler-
 * Core's own first parameter is fed straight from a decompiler-lost
 * register in the caller ('v4'), which BuildPreviewHandlerCore immediately
 * dereferences (*(v10+46)) -- a documented hard-ceiling shape. Attempted
 * once with a bootstrapped, real symbol lookup. ---- */
TEST(cov4_06_previewsendforsymbol, symbol_found_attempt) {
  static char symname[] = "cov4_06_previewsym";
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Str_Intern(symname, 0));
  TOUCH(MessageHandler_PreviewSendForSymbol(0, (_BYTE *)symname));
}

/* ---- Building_CalcGarrisonStrength: Building_CountGarrison() is called
 * with the *caller's* decompiler-lost 'v3' (never assigned before use),
 * immediately dereferenced (*(v3+18)) -- a hard-ceiling shape regardless of
 * what a1/a2 we pass in. Attempted once with a real, sized unit-record
 * buffer. ---- */
TEST(cov4_06_calcgarrisonstrength, attempt) {
  static unsigned char a1buf[512];
  memset(a1buf, 0, sizeof a1buf);
  int i; for (i = 0; i < 7; ++i)
    a1buf[422 + i] = 50;
  TOUCH(Building_CalcGarrisonStrength((int)(intptr_t)a1buf, 0));
}

/* ---- Compat_StringHolderAssignJoined: reaching the "allocation failed"
 * branch (86818,819) requires Compat_AllocLow32Bytes() to return 0. Its
 * arena path caps single allocations at 1MB but transparently falls back to
 * mmap/malloc beyond that (bounded only by whether the resulting address
 * fits a signed 32-bit pointer), so forcing a real failure cheaply/
 * deterministically isn't practical here -- left uncovered rather than
 * spend a multi-GB allocation chasing an address-space fluke. The
 * remaining reachable lines (already-covered branches) are exercised by
 * test_cov09.c. */

/* ---- Rules_BsaveCommand: the "if" line (118092) and the file-parsed
 * predecessor are exercised by driving Rules_GetFileNameArg to succeed via
 * the established one-node STRING-chain technique; Rules_PerformBsave's
 * write path is a large, decompiler-lost-register-heavy serialization
 * routine, so the "return 1" branch (118093) is a best-effort attempt with
 * a writable scratch path. ---- */
TEST(cov4_06_bsavecommand, filename_parsed_bsave_attempt) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path =
      "/tmp/claude-0/-home-user-clash-disassembly/"
      "d4d0d676-5586-5b40-9f14-d9dffd44a5a5/scratchpad/"
      "cov4_06_bsave_out.bsave";
  COV4_06_SAVE_ARGCTX();
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)path;
  cov4_06_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_BsaveCommand(0, 0.0));
  COV4_06_RESTORE_ARGCTX();
}

/* ---- Rules_LinkClassToSuperclasses: a1's superclass count (word at +34)
 * of 1, with the single superclass-table entry pointing at a zeroed
 * "class record" whose own +40 sub-array (old link count 0) makes
 * Class_InsertLinkEntry's copy-in a safe zero-byte memcpy. The do-while
 * body runs exactly once, re-reading the (unchanged) count (171901) and
 * failing the "< result" continue test (171903), ending the loop. ---- */
TEST(cov4_06_linkclasstosuperclasses, one_superclass) {
  static unsigned char a1buf[64];
  static _DWORD arr[4];
  static unsigned char classrec_buf[128];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a1buf, 0, sizeof a1buf);
  memset(arr, 0, sizeof arr);
  memset(classrec_buf, 0, sizeof classrec_buf);
  *(unsigned short *)(a1buf + 34) = 1;
  *(int *)(a1buf + 36) = (int)(intptr_t)arr;
  arr[0] = (int)(intptr_t)classrec_buf;
  TOUCH(Rules_LinkClassToSuperclasses((int)(intptr_t)a1buf));
}

/* ---- UnitSlots_CalcDefenseScore: a2==1 runs the outer loop body exactly
 * once; the first 31-byte unit slot's leading int16 > 0x28 drives the inner
 * while's body (33507) once before the second slot (int16==0) exits it. ---- */
TEST(cov4_06_calcdefensescore, inner_while_advances) {
  static unsigned char units[93];
  memset(units, 0, sizeof units);
  *(short *)(units + 0) = 999;  /* first slot: > 0x28, triggers 33507 */
  *(short *)(units + 31) = 0;   /* second slot: <= 0x28, exits inner while */
  TOUCH(UnitSlots_CalcDefenseScore((char *)units, 1, 0));
}

/* ---- WCIsvListBase_CopyAppendAll: WCCompat_LinkFromHandle(link_handle) is
 * a bare (WCCompatLink*)(uintptr_t)(unsigned)link_handle cast, so it can
 * only be null when link_handle itself is 0 -- but the while loop already
 * requires link_handle != 0 to run the body containing the "if (!link)
 * break;" (56129) check. That makes 56129 structurally unreachable given
 * these two recovered function bodies; attempted once anyway with a
 * one-link list to exercise everything else in the loop. ---- */
TEST(cov4_06_copyappendall, one_link_list) {
  static unsigned char srcbase[32], dstbase[32];
  memset(srcbase, 0, sizeof srcbase);
  memset(dstbase, 0, sizeof dstbase);
  TOUCH(WCIsvListBase_CopyAppendAll((_DWORD *)dstbase, (_DWORD *)srcbase, 0));
}

/* ---- Rules_SyncArmyFactStrength: Rules_EnsureArmyFactForStack returning
 * non-zero skips the entire inner block and jumps straight to the trailing
 * "return result" (70723). Its "else" (create) branch always returns 1
 * unconditionally as long as a1[3] (uint16 at byte 6) <= 0x28 and the fact
 * pointer (DWORD at byte 721) is 0 -- Rules_CreateArmyFact then takes its
 * own early "result <= 0x28 -> return result" exit before touching
 * Rules_AssertFact, so this is fully deterministic and crash-free. ---- */
TEST(cov4_06_syncarmyfactstrength, ensure_returns_nonzero_skips_body) {
  static unsigned char stack[800];
  static char gd[2200000];
  int saved_gameData = gameData;
  memset(stack, 0, sizeof stack);
  memset(gd, 0, sizeof gd);
  gameData = (int)(intptr_t)gd;
  /* *stack (int16 @0) and stack[1] (int16 @2) left 0; a1[3] (int16 @6) left
   * 0 (<= 0x28); DWORD @721 left 0 (no existing fact). Rules_CreateArmyFact
   * reads gameData+556374, so gameData must point at a real, zeroed
   * buffer (matching test_cov07.c's established fixture). */
  TOUCH(Rules_SyncArmyFactStrength((__int16 *)stack, 0, 0, 0, 0, 0.0));
  gameData = saved_gameData;
}

/* ---- Rules_FindLogicalDependencyEntry: a two-node chain where the first
 * node's packed count field (bits 6-14 of its first DWORD) decodes to 1 and
 * whose comparison slot mismatches the search key forces the inner for-loop
 * to break after i==0, then falls into "v3 = v3[1]" (a real second node) and
 * takes the "continue" branch (111026). The second node's own count field
 * decodes to 0, so the next inner-loop pass returns it immediately without
 * touching the mismatch path again. ---- */
TEST(cov4_06_findlogicaldependencyentry, chain_continues_to_second_node) {
  static _DWORD a1buf[4], a2buf[4];
  static _DWORD node1[4], node2[4];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(node1, 0, sizeof node1);
  memset(node2, 0, sizeof node2);

  node2[0] = 0; /* packed count decodes to 0: immediate return on node2 */

  node1[0] = 64; /* packed count decodes to 1 (see derivation in comment) */
  node1[1] = (_DWORD)(intptr_t)node2; /* v3[1]: next node, non-zero */
  node1[2] = 111;                     /* mismatches a2buf[2] below */

  a1buf[2] = (_DWORD)(intptr_t)node1; /* *(a1+8) */
  a2buf[2] = 222;                     /* *(a2+8): mismatch key */

  TOUCH(Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf,
                                          (int)(intptr_t)a2buf));
}

/* ---- Rules_WriteExpressionRefToCode: reaching 132585 requires
 * AST_GetHashedNodeIndex(a2) to *return*, but AST_FindHashedNodeChain
 * immediately writes through its own decompiler-lost 'v5' pointer
 * ("*v5 = v4;") whenever its input is non-null -- a hard-ceiling shape.
 * Attempted once with a bootstrapped, real AST-node-shaped buffer. ---- */
TEST(cov4_06_writeexpressionreftocode, non_null_node_attempt) {
  static __int16 astnode[8];
  memset(astnode, 0, sizeof astnode);
  TOUCH(Rules_WriteExpressionRefToCode(0, astnode, 4, 0));
}

/* ---- Class_IsDeletableAlt: line 140722's branch depends entirely on the
 * decompiler-lost local 'v0' (never assigned anywhere in the recovered
 * body), which is not controllable from a C test; attempted once anyway
 * with Rules_IsBloaded() forced false so at least the guard clause is
 * skipped and whatever 'v0' resolves to at runtime gets exercised. ---- */
TEST(cov4_06_isdeletablealt, not_bloaded_attempt) {
  int saved = g_Rules_FactsBloadedFlag;
  g_Rules_FactsBloadedFlag = 0;
  TOUCH(Class_IsDeletableAlt());
  g_Rules_FactsBloadedFlag = saved;
}
