/* cov2_05: second-pass coverage additions targeting already-partially-covered
 * functions (see scratchpad/cov2_batches/cov2_05.json). Every test runs in
 * its own forked+alarm(8)-watchdog child (see tests/unit/test_all.c), so it
 * is safe to call functions that crash, exit(), or spin -- coverage up to
 * that point is kept regardless.
 *
 * Two conventions carried over from the first pass:
 *  - Any buffer whose address is handed to recovered code through a 32-bit
 *    int/_DWORD field must be `static` (this is a 64-bit -no-pie build; a
 *    plain stack address truncates to garbage when squeezed through a
 *    32-bit field, a static/global address does not).
 *  - `Mem_InitReserveBlock(0,0); Rules_InitAtomTables();` must run before any
 *    Rules_Add*Value / Str_Intern-using call, or the global arenas
 *    (dword_54DBA8, dword_54DD50) are NULL and those calls crash before
 *    doing anything useful.
 *
 * NOTE: CRT_OpenFile / CRT_OpenFileShared are intentionally NOT exercised
 * here (same reason documented in test_cov12.c): their callee
 * CRT_CreateFileHandleFromPath reads off_51A574, a function pointer
 * initialized to the address of a weak, nowhere-defined symbol
 * (j___NTAddFileHandle_). That's harmless while dead (gc-sections drops the
 * reference), but calling the function keeps it live and the link needs to
 * resolve the initializer -- breaking the whole coverage binary for every
 * batch. Left uncovered on purpose.
 */

/* ---- Rules_SetConstraintAllowedTypeFlag: first pass (cov23) already swept
 * the documented boundary values for both a3=0/1; add a few more scattered
 * values (mid-range gaps, the a3=0 side of already-swept values, and an
 * out-of-range high value) purely to raise confidence all branches are
 * being re-hit under this batch's own suite name too. */
TEST(cov2_05_allowedtypeflag, more_values) {
  static unsigned char buf[64];
  unsigned int vals[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x66u, 0x67u, 0x68u,
                          0x6Du, 0x6Eu, 0x6Fu, 111u, 200u, 0xFFFFFFFFu};
  size_t i;
  for (i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
    memset(buf, 0, sizeof(buf));
    TOUCH(Rules_SetConstraintAllowedTypeFlag(vals[i], (int)(intptr_t)buf, 0));
    memset(buf, 0xFF, sizeof(buf));
    TOUCH(Rules_SetConstraintAllowedTypeFlag(vals[i], (int)(intptr_t)buf, 1));
  }
}

/* ---- Parser_ParseInstanceQueryNoAction: funnels through
 * Parser_ParseInstanceQueryRestrictions first; with no real token stream set
 * up that will most likely fail fast and return NULL (the "return result;"
 * final line), which is still new coverage over an unexercised function.
 * Calling it at all is now safe even if it crashes deeper (isolated). */
TEST(cov2_05_instquery, no_action_cold_call) {
  TOUCH(Parser_ParseInstanceQueryNoAction(0, 0));
}

/* ---- Rules_PatchDeftemplateSlotModuleRef: Module_BeginEnum/Module_NextEnum
 * walk the live defmodule list. With no modules registered, Module_NextEnum
 * returns 0 immediately -> Module_EndEnum() branch. Registering the main
 * module first (via Module_InitializeDefmodules, also one of our targets)
 * gives the enum loop at least one module to visit, reaching the
 * Module_SetCurrent/Rules_GetNextDeftemplate lines too. */
TEST(cov2_05_patchslotmodref, cold_no_modules) {
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(0, 0));
}

TEST(cov2_05_patchslotmodref, with_main_module) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Module_InitializeDefmodules());
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(0, 0x1234));
}

/* ---- Instance_FindByName: the qualifier-separator dispatch has 3 shapes:
 * no "::" at all, exactly "::" (qualifier_length==1, extract-with-len-1
 * shortcut), and "Module::Name" (qualifier_length>1, extracts a module name
 * and looks it up). Each takes a symbol-like record whose offset+16 holds
 * the name text, matching the "node+16 = value" convention used across this
 * codebase's parsed-argument records. */
TEST(cov2_05_findbyname, no_separator) {
  static _DWORD sym[16];
  memset(sym, 0, sizeof(sym));
  sym[4] = (_DWORD)(intptr_t)"plainname";
  TOUCH(Instance_FindByName((int)(intptr_t)sym));
}

TEST(cov2_05_findbyname, bare_double_colon) {
  static _DWORD sym[16];
  memset(sym, 0, sizeof(sym));
  sym[4] = (_DWORD)(intptr_t)"::";
  TOUCH(Instance_FindByName((int)(intptr_t)sym));
}

TEST(cov2_05_findbyname, module_qualified) {
  static _DWORD sym[16];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(sym, 0, sizeof(sym));
  sym[4] = (_DWORD)(intptr_t)"Mod::Name";
  TOUCH(Instance_FindByName((int)(intptr_t)sym));
}

/* ---- CRT_FillFindDataRecord: cov12 only exercised the NULL-argument guard.
 * Drive a fully populated WIN32_FIND_DATAA through it so every attribute-bit
 * branch (hidden/directory/readonly/archive/system) and the timestamp /
 * filename copy lines execute. */
TEST(cov2_05_fillfind, all_attribute_bits_set) {
  static WIN32_FIND_DATAA fd;
  static _DWORD out[128];
  memset(&fd, 0, sizeof(fd));
  memset(out, 0, sizeof(out));
  fd.dwFileAttributes = 0x20u | 0x10u | 2u | 1u | 4u;
  fd.ftCreationTimeLow = 100;
  fd.ftCreationTimeHigh = 0;
  fd.ftLastAccessTimeLow = 200;
  fd.ftLastAccessTimeHigh = 0;
  fd.ftLastWriteTimeLow = 300;
  fd.ftLastWriteTimeHigh = 0;
  fd.nFileSizeLow = 12345;
  strcpy(fd.cFileName, "test.txt");
  TOUCH(CRT_FillFindDataRecord((int)(intptr_t)&fd, out));
}

/* ---- CRT_FindFirstFile: give it a glob guaranteed to match something ("/*"
 * always lists root-level entries) to reach the success branch that calls
 * CRT_FillFindDataRecord, on top of cov12's missing-directory failure case. */
TEST(cov2_05_findfirstfile, root_glob_matches) {
  static _DWORD out[128];
  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/*", out, 0));
}

/* ---- Parser_ParseNumericFormCompat: static helper, fully local logic (no
 * parser globals needed for the fast path). Cover: both NULL guards, the
 * "tag <= 1" fast path (both with and without the integer->float coerce),
 * and the "goes through Parser_ParseForm and comes back with an invalid
 * (>1) numeric tag" error path. */
TEST(cov2_05_numformcompat, null_guards) {
  static _DWORD parsed[8];
  static _DWORD expr[4];
  memset(parsed, 0, sizeof(parsed));
  memset(expr, 0, sizeof(expr));
  CHECK_EQ(Parser_ParseNumericFormCompat(0, 0, parsed, 0.0, 0), 0);
  CHECK_EQ(Parser_ParseNumericFormCompat((__int16 *)expr, 0, 0, 0.0, 0), 0);
}

TEST(cov2_05_numformcompat, fast_path_no_coerce) {
  static _DWORD expr[4];
  static _DWORD parsed[8];
  memset(expr, 0, sizeof(expr));
  memset(parsed, 0, sizeof(parsed));
  *(short *)expr = 1;                        /* tag <= 1u -> fast path */
  *(_DWORD *)((char *)expr + 2) = 42;         /* raw integer value */
  CHECK_EQ(Parser_ParseNumericFormCompat((__int16 *)expr, 0, parsed, 0.0, 0), 1);
  CHECK_EQ(parsed[1], 1);
}

TEST(cov2_05_numformcompat, fast_path_with_coerce) {
  static _DWORD expr[4];
  static _DWORD parsed[8];
  static _DWORD valrec[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(expr, 0, sizeof(expr));
  memset(parsed, 0, sizeof(parsed));
  memset(valrec, 0, sizeof(valrec));
  valrec[4] = 7; /* readable at (value+16) for the (double)*(int*)(value+16) cast */
  *(short *)expr = 1;
  *(_DWORD *)((char *)expr + 2) = (_DWORD)(intptr_t)valrec;
  TOUCH(Parser_ParseNumericFormCompat((__int16 *)expr, 1 /* coerce */, parsed, 0.0, 0));
}

TEST(cov2_05_numformcompat, via_parseform_invalid_tag) {
  static _DWORD expr[4];
  static _DWORD parsed[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(expr, 0, sizeof(expr));
  memset(parsed, 0, sizeof(parsed));
  *(short *)expr = 2; /* tag > 1u -> Parser_ParseForm path; ParseForm's fast
                        * LABEL_4 copies this same tag(2) into parsed[1],
                        * which is >1 -> invalid-numeric-type error branch */
  TOUCH(Parser_ParseNumericFormCompat((__int16 *)expr, 0, parsed, 0.0, 3));
}

/* ---- Rules_SaveCommand: Lexer_TokenExpect(1) + Rules_GetFileNameArg(1,...)
 * + Rules_Save. Empty arg-list drives the immediate-fail branch; a single
 * populated argument-chain node (tag 2, matching the recipe validated in
 * test_cov11.c's Rules_GetFileNameArg tests) drives the call all the way
 * through to Rules_Save/Rules_OpenFileErrorMessage. */
TEST(cov2_05_savecmd, empty_arglist) {
  static _DWORD anchor[16];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_SaveCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_05_savecmd, one_arg_filename) {
  static _DWORD anchor[16];
  static _DWORD node[16];
  static char fname[32] = "/tmp/cov2_05_save.tmp";
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  memset(node, 0, sizeof(node));
  *(short *)node = 2;                              /* success tag */
  *(_DWORD *)((char *)node + 2) = (_DWORD)(intptr_t)node; /* self ptr */
  node[4] = (_DWORD)(intptr_t)fname;               /* value at node+16 */
  *(_DWORD *)((char *)node + 10) = 0;               /* terminate chain */
  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_SaveCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_FloatFunction: Lexer_TokenExpect(1) + Lexer_ParseValueList(1,
 * &v6, 0, a4). Lexer_ParseValueList's `a2[1]==1 && !a3` branch (a3==0 here)
 * coerces an integer-tagged node to a double via Rules_AddDoubleValue, which
 * needs the atom/reserve arenas bootstrapped. */
TEST(cov2_05_floatfn, empty_arglist) {
  static _DWORD anchor[16];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_FloatFunction(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_05_floatfn, integer_arg_coerced) {
  static _DWORD anchor[16];
  static _DWORD node[16];
  static _DWORD valrec[8];
  int saved = g_ClipsCurrentExpression;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(anchor, 0, sizeof(anchor));
  memset(node, 0, sizeof(node));
  memset(valrec, 0, sizeof(valrec));
  valrec[4] = 9; /* value+16 read as int for the double coercion */
  *(short *)node = 1; /* integer tag */
  *(_DWORD *)((char *)node + 2) = (_DWORD)(intptr_t)valrec;
  *(_DWORD *)((char *)node + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_FloatFunction(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- WCIsvListBase_PopUntilMatchOrEmpty: the empty-immediately case was
 * covered in test_cov04.c. Reaching the loop body requires a real 1-node
 * list: one variant whose node value never matches the (list-pointer)
 * sentinel and drains to empty (inner "if(!tail_link) return 0" branch);
 * another whose node's value equals the list-pointer sentinel by
 * construction, taking the match/break -> return 1 branch. */
TEST(cov2_05_wcisv, pop_until_drains_to_empty) {
  static WCCompatListBase list;
  static WCCompatLink node;
  int handle;
  memset(&list, 0, sizeof(list));
  memset(&node, 0, sizeof(node));
  handle = (int)(intptr_t)&list;
  node.next_link = 0;
  node.value = 0xDEAD; /* != handle identity -> no match */
  list.head_link = (int)(intptr_t)&node;
  list.tail_link = (int)(intptr_t)&node; /* offset+8 truthy -> enter loop */
  list.count = 1;
  CHECK_EQ(WCIsvListBase_PopUntilMatchOrEmpty(0, handle), 0);
}

TEST(cov2_05_wcisv, pop_until_match_found) {
  static WCCompatListBase list;
  static WCCompatLink node;
  int handle;
  memset(&list, 0, sizeof(list));
  memset(&node, 0, sizeof(node));
  handle = (int)(intptr_t)&list;
  node.next_link = 0;
  node.value = handle; /* == the sentinel passed as both list+default -> match */
  list.head_link = (int)(intptr_t)&node;
  list.tail_link = 1; /* just needs to be non-zero */
  list.count = 1;
  CHECK_EQ(WCIsvListBase_PopUntilMatchOrEmpty(0, handle), 1);
}

/* ---- Rules_HostRenameFile: Lexer_TokenExpect(2), then two
 * Rules_GetFileNameArg calls chained through a 2-node argument list (same
 * per-node recipe as test_cov11.c), followed by Rules_RenameFile. */
TEST(cov2_05_hostrenamefile, empty_arglist) {
  static _DWORD anchor[16];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_HostRenameFile(0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_05_hostrenamefile, two_args_success) {
  static _DWORD anchor[16];
  static _DWORD node1[16], node2[16];
  static char nameA[32] = "/tmp/cov2_05_old.tmp";
  static char nameB[32] = "/tmp/cov2_05_new.tmp";
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  memset(node1, 0, sizeof(node1));
  memset(node2, 0, sizeof(node2));

  *(short *)node1 = 2;
  *(_DWORD *)((char *)node1 + 2) = (_DWORD)(intptr_t)node1;
  node1[4] = (_DWORD)(intptr_t)nameA;
  *(_DWORD *)((char *)node1 + 10) = (_DWORD)(intptr_t)node2;

  *(short *)node2 = 2;
  *(_DWORD *)((char *)node2 + 2) = (_DWORD)(intptr_t)node2;
  node2[4] = (_DWORD)(intptr_t)nameB;
  *(_DWORD *)((char *)node2 + 10) = 0;

  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node1;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_HostRenameFile(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- MainMenu_RequestCreditsCinematic: never called by any prior batch. */
TEST(cov2_05_mainmenu, request_credits_cinematic) {
  TOUCH(MainMenu_RequestCreditsCinematic(0));
  CHECK_EQ(g_PlayGameMenuExitRequested, 1);
}

/* ---- Class_PrintModuleList: Rules_GetModuleConstructListHead(a1) just
 * reads *(a1+4); giving it a non-null "head" pointer (any readable static
 * address) takes the outer `if (result)` branch and reaches the
 * Output_WriteLongString/Output_Write/MessageHandler_EnumNext lines. With no
 * registered message-handler records, MessageHandler_EnumNext(a1, 0) returns
 * 0, so the inner for-loop body itself is not reached, but every line up to
 * and including that call is new coverage over the previously-unexercised
 * function. */
TEST(cov2_05_printmodulelist, with_fake_head) {
  static _DWORD modrec[16];
  static const char headtext[] = "cov2_05_head";
  memset(modrec, 0, sizeof(modrec));
  modrec[1] = (_DWORD)(intptr_t)headtext; /* *(a1+4) */
  TOUCH(Class_PrintModuleList((int)(intptr_t)modrec));
}

TEST(cov2_05_printmodulelist, null_head) {
  static _DWORD modrec[16];
  memset(modrec, 0, sizeof(modrec));
  CHECK_EQ(Class_PrintModuleList((int)(intptr_t)modrec), 0);
}

/* ---- Module_InitializeDefmodules: straight-line construct/host-function
 * registration chain; needs the atom tables bootstrapped or the very first
 * Str_Intern-driven registration call segfaults before reaching the rest. */
TEST(cov2_05_moduleinit, register_defmodules) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Module_InitializeDefmodules());
}

/* ---- Rules_DeleteFunction: three chained Lexer_ParseValueList calls (arg
 * indices 1,2,3 expecting types 4,1,1 respectively). Build a 3-node argument
 * chain so the first call succeeds via the multifield-type(4) match branch
 * and the next two via the integer(1)-vs-a3(1) match branch, driving it all
 * the way to the Rules_MultifieldDeleteRange call. A separate empty-list
 * variant exercises the immediate Lexer_ErrorRecover/SetMultifieldErrorValue
 * fallback. */
TEST(cov2_05_deletefn, empty_arglist) {
  static _DWORD a1buf[16];
  int saved = g_ClipsCurrentExpression;
  memset(a1buf, 0, sizeof(a1buf));
  g_ClipsCurrentExpression = 0;
  TOUCH(Rules_DeleteFunction(a1buf, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov2_05_deletefn, three_arg_chain) {
  static _DWORD a1buf[16];
  static _DWORD anchor[16];
  static _DWORD node1[16], node2[16], node3[16];
  static _DWORD val1[8], val2[8], val3[8];
  int saved = g_ClipsCurrentExpression;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a1buf, 0, sizeof(a1buf));
  memset(anchor, 0, sizeof(anchor));
  memset(node1, 0, sizeof(node1));
  memset(node2, 0, sizeof(node2));
  memset(node3, 0, sizeof(node3));
  memset(val1, 0, sizeof(val1));
  memset(val2, 0, sizeof(val2));
  memset(val3, 0, sizeof(val3));

  /* node1: multifield-like tag(4) -> Parser_ParseForm's case 4 always sets
   * a2[1]=4 regardless of the raw tag value stored here, reading the
   * "multifield header" fields from *(a1+1). Point that at val1 (zeroed is
   * fine -- just needs to be a readable pointer). */
  *(short *)node1 = 4;
  *(_DWORD *)((char *)node1 + 2) = (_DWORD)(intptr_t)val1;

  *(short *)node2 = 1; /* integer tag */
  *(_DWORD *)((char *)node2 + 2) = (_DWORD)(intptr_t)val2;
  val2[4] = 11; /* value+16 */

  *(short *)node3 = 1;
  *(_DWORD *)((char *)node3 + 2) = (_DWORD)(intptr_t)val3;
  val3[4] = 22;

  *(_DWORD *)((char *)node1 + 10) = (_DWORD)(intptr_t)node2;
  *(_DWORD *)((char *)node2 + 10) = (_DWORD)(intptr_t)node3;
  *(_DWORD *)((char *)node3 + 10) = 0;

  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node1;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_DeleteFunction(a1buf, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Class_GenerateDefaultSlotHandlersAndFlag: two independent do-while
 * loops gated by result[16] and result[24]. Guard-false variant skips both;
 * guard-true variant enters both. The first loop's trip count depends on a
 * decompiler-lost register (v3) so it may iterate an unpredictable number of
 * times (potentially spinning until the alarm(8) watchdog fires) -- that's
 * fine, isolated per-test. Point the base pointer fields at large static
 * scratch buffers so at least the first several iterations stay in mapped,
 * zeroed memory instead of faulting immediately. */
TEST(cov2_05_classgen, guards_false) {
  static _DWORD rec[32];
  memset(rec, 0, sizeof(rec));
  TOUCH(Class_GenerateDefaultSlotHandlersAndFlag(rec));
}

TEST(cov2_05_classgen, both_loops_enter) {
  static _DWORD rec[32];
  static _DWORD scratch1[4096];
  static _DWORD scratch2[64];
  memset(rec, 0, sizeof(rec));
  memset(scratch1, 0, sizeof(scratch1));
  memset(scratch2, 0, sizeof(scratch2));
  rec[16] = 1;
  rec[13] = (_DWORD)(intptr_t)scratch1;
  rec[24] = 1;
  rec[22] = (_DWORD)(intptr_t)scratch2;
  TOUCH(Class_GenerateDefaultSlotHandlersAndFlag(rec));
}

/* ---- Output_WriteFormatted: cov09 already exercises the guards, the
 * no-specifier fast path (straight to CRT_VfprintfLockedWrite) and a small
 * "%d %s" argument-collecting call. Add a call with many more specifiers to
 * broaden the varargs-collection loop's iteration count. */
TEST(cov2_05_outputfmt, many_args) {
  static _DWORD fake_stream[32];
  memset(fake_stream, 0, sizeof(fake_stream));
  TOUCH(Output_WriteFormatted(0, 0, (int)(intptr_t)fake_stream,
                               (int)(intptr_t)"%d %d %d %d %d %d %d %d\n",
                               1, 2, 3, 4, 5, 6, 7, 8));
}

/* ---- AST_GetHashedNodeIndex: NULL guard already trivially reachable; a
 * non-null pointer takes the AST_FindHashedNodeChain path. With the global
 * hash chains empty by default the chain lookup will most likely also
 * report "not found", but that still reaches the intervening lines. */
TEST(cov2_05_asthashidx, null_and_nonnull) {
  static __int16 node[8];
  memset(node, 0, sizeof(node));
  CHECK_EQ(AST_GetHashedNodeIndex(0), -1);
  TOUCH(AST_GetHashedNodeIndex(node));
}

/* ---- Rules_HostIntegerp: cov16 already drives it through the
 * "not-found" RtnUnknown safety-net path. Build a proper matching 1-node
 * argument chain (tag==1, integer) so Lexer_TokenExpect(1) sees count==1 and
 * Rules_RtnUnknown resolves a real node whose type comes back exactly 1,
 * taking the "return 1" branch that batch didn't reach. */
TEST(cov2_05_hostintegerp, single_integer_arg) {
  static _DWORD anchor[16];
  static _DWORD node[16];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  memset(node, 0, sizeof(node));
  *(short *)node = 1; /* integer tag */
  *(_DWORD *)((char *)node + 2) = (_DWORD)(intptr_t)node;
  *(_DWORD *)((char *)node + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_HostIntegerp(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Class_ClassSlotsCommand: Class_ParseClassNameAndInheritFlag against a
 * cold/default environment most likely fails to resolve a class, taking the
 * Rules_SetMultifieldErrorValue branch; still new coverage over an
 * unexercised function either way. */
TEST(cov2_05_classslotscmd, cold_call) {
  TOUCH(Class_ClassSlotsCommand(0, 0.0));
}

/* ---- Unit_BuildShotAnimSpritePath: sweep every UnitType_GetResourceKey
 * table index (0..34) plus one out-of-range index (fallback "peon"), and
 * an a3 whose "+49" byte wraps to 0 (0xCF/-49), which makes the small
 * numeral-suffix copy loop break on its very first byte instead of copying
 * a real character -- the one branch shape the existing 57/59-covered test
 * in this area is unlikely to have hit. */
TEST(cov2_05_shotanimpath, sweep_unit_types_and_suffix_wrap) {
  static char out[256];
  int a2;
  for (a2 = 0; a2 <= 35; ++a2) {
    memset(out, 0, sizeof(out));
    TOUCH(Unit_BuildShotAnimSpritePath(out, (unsigned __int8)a2, 0));
  }
  memset(out, 0, sizeof(out));
  TOUCH(Unit_BuildShotAnimSpritePath(out, 0, (char)-49)); /* a3+49 == 0 */
}

/* ---- Rules_HostPortHasSupplyReady: trivial one-line forwarder, never
 * called by any prior batch. */
TEST(cov2_05_hostport, supply_ready) {
  TOUCH(Rules_HostPortHasSupplyReady());
}

/* ---- Module_RegisterBsaveBloadHandlers: straight-line bsave/bload
 * registration chain; needs the atom tables bootstrapped for the interning
 * calls inside Rules_RegisterBinaryItem. */
TEST(cov2_05_moduleregister, bsave_bload_handlers) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Module_RegisterBsaveBloadHandlers());
}

/* ---- Time_Now: both the zero-Frequency (raw counter) and non-zero
 * (calibrated division) branches. */
TEST(cov2_05_timenow, both_frequency_branches) {
  long long saved = Frequency.QuadPart;
  Frequency.QuadPart = 0;
  TOUCH(Time_Now(0, 0));
  Frequency.QuadPart = 1000000;
  TOUCH(Time_Now(0, 0));
  Frequency.QuadPart = saved;
}

/* ---- Building_CountNonCombatGarrisonEntries: walks 12 garrison-slot
 * records (372/31 == 12) starting at a1, each a 31-byte record whose
 * __int16 at offset+18 is the occupant unit type (-1 == empty slot). Cover
 * a record whose type isn't -1 and doesn't match any of the four counted
 * "non-combat" special types (the one line this batch's JSON says is still
 * uncovered: falling through to the plain `v1 += 31;` skip at the bottom of
 * the do-while without ++v2). */
TEST(cov2_05_garrisoncount, one_non_special_occupied_slot) {
  static unsigned char buf[372 + 31];
  memset(buf, 0, sizeof(buf));
  memset(buf, 0xFF, 372); /* all slots empty: __int16 -1 */
  *(short *)(buf + 18) = 5; /* first slot: some ordinary unit type */
  CHECK_EQ(Building_CountNonCombatGarrisonEntries((int)(intptr_t)buf), 0);
}

/* ---- Rules_ResetCommand: Lexer_TokenExpect(0) with an empty arg list
 * matches count(0)==a1(0) on at least the "v2==0" resolution, driving the
 * Rules_Reset() call (a heavyweight global-state reset, safe to call cold
 * under isolation). */
TEST(cov2_05_resetcmd, empty_arglist_reset) {
  static _DWORD anchor[16];
  int saved = g_ClipsCurrentExpression;
  memset(anchor, 0, sizeof(anchor));
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_ResetCommand());
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_CoshBuiltin: Rules_MathParseSingleArg's failure path is already
 * covered (cov17). Build a matching 1-node integer-tagged argument chain so
 * Lexer_TokenExpect(1)/Lexer_ParseValueList(1,...,0,...) succeed, reaching
 * the `return cosh(v5[0]);` success line. */
TEST(cov2_05_coshbuiltin, single_integer_arg_success) {
  static _DWORD anchor[16];
  static _DWORD node[16];
  static _DWORD valrec[8];
  int saved = g_ClipsCurrentExpression;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(anchor, 0, sizeof(anchor));
  memset(node, 0, sizeof(node));
  memset(valrec, 0, sizeof(valrec));
  valrec[4] = 2;
  *(short *)node = 1;
  *(_DWORD *)((char *)node + 2) = (_DWORD)(intptr_t)valrec;
  *(_DWORD *)((char *)node + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  TOUCH(Rules_CoshBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Instance_MakeInstanceFunction: never directly exercised; a cold call
 * still runs the SetObjectPatternMatchDelay bracket around
 * Instance_ActiveMakeInstanceFunction. */
TEST(cov2_05_makeinstfn, cold_call) {
  TOUCH(Instance_MakeInstanceFunction(0, 0, 0.0));
}

/* ---- Rules_RegisterDefglobalBinaryItem: straight-line bsave/bload
 * registration chain for defglobals; needs the atom tables bootstrapped. */
TEST(cov2_05_defglobalbinitem, register_it) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterDefglobalBinaryItem());
}
