/* cov14: Module/IO-router/AST-node/Rules-bsave/Defgeneric cluster */

/* NOTE: clash95.c is 32-bit-legacy decompiled code that represents every
 * pointer as a plain `int`/`_DWORD`. On this 64-bit test build, any address
 * that flows through that representation must fit in (and round-trip
 * through) 32 bits, or the truncated value becomes a wild pointer on
 * dereference. Stack addresses on x86_64 Linux are far above 4GB, so every
 * buffer whose address is ever cast to int/passed to these functions is
 * declared `static` (placing it in the low-address .bss segment) instead of
 * as a plain stack-local array. */

/* ---- small helpers: build 14-byte packed AST-node records --------------
 * Layout matches AST_* helpers in clash95.c: offset0 = __int16 tag,
 * offset2 = _DWORD value, offset6 = _DWORD child ptr, offset10 = _DWORD
 * next ptr. Buffers are zeroed first so unused fields are always readable
 * zeros (never garbage pointers). */
static void cov14_set_node(unsigned char *base, int tag, int val, void *child,
                            void *next) {
  *(short *)(base + 0) = (short)tag;
  *(int *)(base + 2) = val;
  *(int *)(base + 6) = (int)(intptr_t)child;
  *(int *)(base + 10) = (int)(intptr_t)next;
}

TEST(cov14_mod, init_defmodules) {
  Mem_InitReserveBlock(0, 0);
  /* Module_InitializeDefmodules interns symbols (Str_Intern), which indexes
   * straight into the global symbol table -- that table must be allocated
   * first or the lookup dereferences a NULL table pointer. */
  TOUCH(Rules_InitAtomTables());
  TOUCH(Module_InitializeDefmodules());
}

TEST(cov14_mod, get_pp_form) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  obj[1] = 77; /* offset 4 */
  CHECK_EQ(Module_GetPPForm((int)(intptr_t)obj), 77);
}

/* ---------------------------------------------------------------------- */
/* IO string-router family: IO_RegisterStringRouter / IO_StringRouterPrint /
 * IO_StringRouterGetc. Each router "found" path requires a matching entry
 * registered via IO_OpenStringDestination/IO_OpenTextSource first -- the
 * "not found" path in these functions dereferences a NULL unconditionally,
 * so we always ensure a match to stay memory-safe. */

TEST(cov14_io, register_string_router) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_RegisterStringRouter());
}

TEST(cov14_io, string_router_print_small_dest_early_return) {
  static _DWORD dummy[4];
  memset(dummy, 0, sizeof dummy);
  Mem_InitReserveBlock(0, 0);
  /* capacity 0 -> Print's "buffer too small" branch returns immediately,
   * never reaching the buggy strncpy_ call. */
  TOUCH(IO_OpenStringDestination((int)(intptr_t)"cov14routerG", dummy, 0));
  TOUCH(IO_StringRouterPrint((int)(intptr_t)"cov14routerG", "hi"));
}

TEST(cov14_io, string_router_print_dest_write_branch) {
  static char buf[256];
  memset(buf, 0, sizeof buf);
  Mem_InitReserveBlock(0, 0);
  /* fresh destination -> write position is 0 on the first Print call only,
   * which keeps the (buggy) strncpy_(write_pos, msg) call memory-safe. */
  TOUCH(IO_OpenStringDestination((int)(intptr_t)"cov14routerH", buf, 200));
  TOUCH(IO_StringRouterPrint((int)(intptr_t)"cov14routerH", "hello"));
}

TEST(cov14_io, string_router_print_source_not_dest) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_OpenStringSource((int)(intptr_t)"cov14routerI", "payload", 0));
  /* v4[4] == 0 for a source router -> "not equal 1" early-return branch. */
  TOUCH(IO_StringRouterPrint((int)(intptr_t)"cov14routerI", "x"));
}

TEST(cov14_io, string_router_getc_dest_returns_minus1) {
  static char buf[64];
  memset(buf, 0, sizeof buf);
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_OpenStringDestination((int)(intptr_t)"cov14routerD", buf, 60));
  CHECK_EQ(IO_StringRouterGetc((int)(intptr_t)"cov14routerD"), -1);
}

TEST(cov14_io, string_router_getc_source_reads_char) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_OpenStringSource((int)(intptr_t)"cov14routerE", "xy", 0));
  TOUCH(IO_StringRouterGetc((int)(intptr_t)"cov14routerE"));
  TOUCH(IO_StringRouterGetc((int)(intptr_t)"cov14routerE"));
}

TEST(cov14_io, string_router_getc_source_exhausted) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_OpenTextSource((int)(intptr_t)"cov14routerF", 0, 0, 0));
  TOUCH(IO_StringRouterGetc((int)(intptr_t)"cov14routerF"));
}

/* Lexer_ReadToken reads through Lexer_PeekChar/Lexer_SkipChar, which route
 * to whichever IO router's name matches its `int a1` logical-name argument
 * -- wiring a real "string" router (IO_RegisterStringRouter, which the
 * codebase names "string") backed by IO_OpenTextSource content lets us
 * drive real characters through the token loop instead of guessing at the
 * "router not found" fallback (which the routing helpers dereference
 * unconditionally, so it is not memory-safe to exercise deliberately). */
TEST(cov14_lexer, read_token_plain_word) {
  static _DWORD a3[4];
  memset(a3, 0, sizeof a3);
  Mem_InitReserveBlock(0, 0);
  /* Lexer_ReadToken ends by interning the built token via Str_Intern, which
   * indexes straight into the global symbol table. */
  TOUCH(Rules_InitAtomTables());
  TOUCH(IO_RegisterStringRouter());
  /* 'a','b' both pass the IsTable "appendable" bitmask, '<' (60) stops the
   * loop -> exercises the append-loop body and the non-bracket return. */
  TOUCH(IO_OpenTextSource((int)(intptr_t)"cov14lex1", "ab<", 3, 0));
  g_TokenBuf = 0;
  g_TokenLen = 0;
  g_TokenCap = 0;
  TOUCH(Lexer_ReadToken((int)(intptr_t)"cov14lex1", 0, a3, 0));
}

TEST(cov14_lexer, read_token_bracketed_field) {
  static _DWORD a3[4];
  memset(a3, 0, sizeof a3);
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_InitAtomTables());
  TOUCH(IO_RegisterStringRouter());
  /* '[', 'a', 'b', ']' are all appendable too, and produce a token whose
   * first/last chars are '['/']' -> exercises the bracketed-field branch. */
  TOUCH(IO_OpenTextSource((int)(intptr_t)"cov14lex2", "[ab]<", 5, 0));
  g_TokenBuf = 0;
  g_TokenLen = 0;
  g_TokenCap = 0;
  TOUCH(Lexer_ReadToken((int)(intptr_t)"cov14lex2", 0, a3, 0));
}

/* ---------------------------------------------------------------------- */

TEST(cov14_rules, extract_module_and_construct_name_no_separator) {
  static char name[16];
  strcpy(name, "plainname");
  CHECK((int)(intptr_t)Rules_ExtractModuleAndConstructName((_BYTE *)name) ==
        (int)(intptr_t)name);
}

TEST(cov14_rules, extract_module_and_construct_name_with_separator) {
  /* Drives the module-qualifier lookup path; downstream helpers walk
   * global module/symbol tables that may not resolve a match, but the
   * call itself is exercised for coverage regardless of outcome. */
  Mem_InitReserveBlock(0, 0);
  static char name[16];
  strcpy(name, "mod::item");
  TOUCH(Rules_ExtractModuleAndConstructName((_BYTE *)name));
}

TEST(cov14_rules, find_import_export_construct_separator_early_return) {
  static _DWORD a2[4];
  memset(a2, 0, sizeof a2);
  static char a3[16];
  strcpy(a3, "a::b");
  int r = Rules_FindImportExportConstruct((char *)"fn", a2, (_BYTE *)a3, 0, 0);
  CHECK_EQ(r, 0);
  CHECK_EQ(a2[0], 0);
}

TEST(cov14_rules, find_import_export_construct_no_separator) {
  static _DWORD a2[4];
  memset(a2, 0, sizeof a2);
  Mem_InitReserveBlock(0, 0);
  static char a3[16];
  strcpy(a3, "plain");
  TOUCH(Rules_FindImportExportConstruct((char *)"fn", a2, (_BYTE *)a3, 0, 0));
}

TEST(cov14_rules, increment_busy_count) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  obj[7] = 5; /* offset 28 */
  int r = Rules_IncrementBusyCount((int)(intptr_t)obj);
  CHECK_EQ(r, (int)(intptr_t)obj);
  CHECK_EQ(obj[7], 6);
}

/* ---------------------------------------------------------------------- */

TEST(cov14_ast, copy_node_chain_to_array_empty) {
  CHECK_EQ(AST_CopyNodeChainToArray(0, (int)(intptr_t)0, 3), 3);
}

TEST(cov14_ast, copy_node_chain_to_array_full) {
  static unsigned char src[64];
  static unsigned char out[2048];
  memset(src, 0, sizeof src);
  memset(out, 0, sizeof out);
  /* node A: has both a child (node C) and a next (node B) */
  cov14_set_node(src + 0, 1, 10, src + 28, src + 14);
  /* node B: no child, no next */
  cov14_set_node(src + 14, 2, 20, 0, 0);
  /* node C (child of A): no child, no next */
  cov14_set_node(src + 28, 3, 30, 0, 0);

  int result =
      AST_CopyNodeChainToArray((int)(intptr_t)src, (int)(intptr_t)out, 0);
  CHECK(result >= 3);
}

TEST(cov14_ast, hash_node_chain_no_child) {
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  cov14_set_node(buf, 5, 100, 0, 0);
  TOUCH(AST_HashNodeChain((__int16 *)buf));
}

TEST(cov14_ast, hash_node_chain_with_child_and_list) {
  /* AST_HashNodeChain's recovered "next" traversal reads it as
   * `*(__int16 **)(v1 + 5)`: a real 8-byte pointer read on this 64-bit
   * build, even though the packed node format only reserves 4 bytes for
   * that field. Node records must therefore be spaced far enough apart
   * that the 4 padding bytes past each node's "next" field are always
   * zero, or that wide read spills into the next node's tag/value bytes
   * and manufactures a wild pointer. */
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  /* node A has a child (node B, placed well past A's padding) and no next */
  cov14_set_node(buf + 0, 3, 11, buf + 32, 0);
  /* node B (child): no child, no next */
  cov14_set_node(buf + 32, 7, 22, 0, 0);
  TOUCH(AST_HashNodeChain((__int16 *)buf));
}

TEST(cov14_ast, get_hashed_node_index_null) {
  CHECK_EQ(AST_GetHashedNodeIndex(0), -1);
}

TEST(cov14_ast, get_hashed_node_index_nonnull_best_effort) {
  /* AST_FindHashedNodeChain (called internally) writes through an
   * uninitialized local pointer in the recovered decompilation, so this
   * call may legitimately crash: the harness isolates it. */
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  cov14_set_node(buf, 9, 1, 0, 0);
  TOUCH(AST_GetHashedNodeIndex((__int16 *)buf));
}

TEST(cov14_ast, expression_constraints_compatible_best_effort) {
  /* Body relies on several uninitialized locals (v3..v5) that get
   * dereferenced downstream in the recovered decompilation regardless of
   * input; call is still exercised for partial coverage. */
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  cov14_set_node(buf, 2, 1, 0, 0);
  TOUCH(Rules_ExpressionConstraintsCompatible((__int16 *)buf));
}

TEST(cov14_rules, tag_is_constant_type_all_branches) {
  CHECK_EQ(Rules_TagIsConstantType(0), 1);
  CHECK_EQ(Rules_TagIsConstantType(1), 1);
  CHECK_EQ(Rules_TagIsConstantType(2), 1);
  CHECK_EQ(Rules_TagIsConstantType(3), 1);
  CHECK_EQ(Rules_TagIsConstantType(7), 1);
  CHECK_EQ(Rules_TagIsConstantType(8), 1);
  CHECK_EQ(Rules_TagIsConstantType(99), 0);
  CHECK_EQ(Rules_TagIsConstantType(-1), 0);
}

TEST(cov14_ast, count_list_nodes_empty_and_chain) {
  CHECK_EQ(AST_CountListNodes(0), 0);

  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  cov14_set_node(buf + 0, 1, 0, 0, buf + 14);
  cov14_set_node(buf + 14, 2, 0, 0, buf + 28);
  cov14_set_node(buf + 28, 3, 0, 0, 0);
  CHECK_EQ(AST_CountListNodes((uintptr_t)buf), 3);
}

TEST(cov14_ast, count_tree_nodes_empty_and_tree) {
  CHECK_EQ(AST_CountTreeNodes(0), 0);

  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  cov14_set_node(buf + 0, 1, 10, buf + 28, buf + 14);
  cov14_set_node(buf + 14, 2, 20, 0, 0);
  cov14_set_node(buf + 28, 3, 30, 0, 0);
  CHECK_EQ(AST_CountTreeNodes((int)(intptr_t)buf), 3);
}

TEST(cov14_ast, append_node_list_variants) {
  static unsigned char tail[64];
  memset(tail, 0, sizeof tail);

  /* a1 == 0 -> returns a2 unchanged */
  CHECK_EQ(AST_AppendNodeList(0, 42), 42);

  /* a2 == 0 -> returns a1 unchanged without traversal */
  cov14_set_node(tail + 0, 1, 0, 0, 0);
  CHECK_EQ(AST_AppendNodeList((int)(intptr_t)tail, 0), (int)(intptr_t)tail);

  /* multi-node chain -> traverses to the real tail before appending a2 */
  static unsigned char chain[64];
  memset(chain, 0, sizeof chain);
  cov14_set_node(chain + 0, 1, 0, 0, chain + 14);
  cov14_set_node(chain + 14, 2, 0, 0, chain + 28);
  cov14_set_node(chain + 28, 3, 0, 0, 0);
  int appended_marker = 0x1234;
  int r = AST_AppendNodeList((int)(intptr_t)chain, appended_marker);
  CHECK_EQ(r, (int)(intptr_t)chain);
  CHECK_EQ(*(int *)(chain + 28 + 10), appended_marker);
}

/* ---------------------------------------------------------------------- */

TEST(cov14_rules, bsave_atom_tables_and_symbol_table) {
  /* Best-effort: Rules_BsaveSymbolTable's recovered bucket-sweep uses an
   * `int ***` stride (`++v2` / `v2 != (int ***)(v8 + 4052)`) that advances
   * 8 bytes per step on this 64-bit build against a table sized for 4-byte
   * (32-bit pointer) buckets. 4052 is not a multiple of 8, so the loop's
   * exact-equality exit condition can never be hit and it walks off the
   * end of the allocation regardless of table contents -- this is a
   * structural 32-vs-64-bit artifact in the recovered code, not something
   * fixable via input choice. The call still exercises the header-write
   * lines before the eventual wild read. */
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_InitAtomTables());
  TOUCH(Rules_BsaveAtomTables(0));
  TOUCH(Rules_BsaveSymbolTable(0));
}

TEST(cov14_rules, bsave_command_best_effort) {
  /* Give the global "current expression" a safe, fully-zeroed target so
   * Rules_RtnArgCount (reached via Lexer_TokenExpect) doesn't dereference
   * a NULL pointer; downstream behavior is still best-effort. */
  static _DWORD fake_expr[64];
  memset(fake_expr, 0, sizeof fake_expr);
  g_ClipsCurrentExpression = (int)(intptr_t)fake_expr;
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_BsaveCommand(0, 0.0));
  g_ClipsCurrentExpression = 0;
}

TEST(cov14_event, clear_handlers) {
  TOUCH(Event_ClearHandlers());
}

/* ---------------------------------------------------------------------- */

TEST(cov14_defgeneric, is_deletable_best_effort) {
  /* Recovered body dereferences an uninitialized local (v0); harness
   * isolates the likely crash while still exercising the call. */
  TOUCH(Defgeneric_IsDeletable());
}

TEST(cov14_defgeneric, remove_construct_zero_arg_safe_path) {
  Mem_InitReserveBlock(0, 0);
  /* a1 == 0 takes the ClearDefgenericsReady/ClearDefgenerics path, which
   * avoids the always-crashing Defgeneric_IsDeletable() call used when
   * a1 != 0. */
  TOUCH(Defgeneric_RemoveConstruct(0));
}

TEST(cov14_defgeneric, remove_construct_nonzero_best_effort) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  TOUCH(Defgeneric_RemoveConstruct((int)(intptr_t)obj));
}

TEST(cov14_defgeneric, format_method_restrictions_string_best_effort) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  TOUCH(Defgeneric_FormatMethodRestrictionsString("name", 0, 0,
                                                   (int)(intptr_t)obj));
}

TEST(cov14_defgeneric, trace_flag_get_set_roundtrip) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  Defgeneric_SetTraceFlag(1, (int)(intptr_t)obj);
  CHECK_EQ(Defgeneric_GetTraceFlag((int)(intptr_t)obj), 1);
  Defgeneric_SetTraceFlag(0, (int)(intptr_t)obj);
  CHECK_EQ(Defgeneric_GetTraceFlag((int)(intptr_t)obj), 0);
}

TEST(cov14_defgeneric, set_method_trace_flag_best_effort) {
  /* Dereferences an uninitialized local (v5) in the recovered
   * decompilation regardless of arguments; best-effort call. */
  TOUCH(Defgeneric_SetMethodTraceFlag(1, 0, 0));
  TOUCH(Defgeneric_SetMethodTraceFlag(0, 0, 0));
}

TEST(cov14_defgeneric, get_defmethod_list_command_zero_args) {
  static _DWORD fake_expr[64];
  memset(fake_expr, 0, sizeof fake_expr);
  g_ClipsCurrentExpression = (int)(intptr_t)fake_expr;
  Mem_InitReserveBlock(0, 0);

  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  /* Rules_RtnArgCount() == 0 here -> takes the
   * Defgeneric_BuildMethodListValue(0, a1) branch directly, which stays
   * memory-safe as long as the module system has no current module. */
  TOUCH(Defgeneric_GetDefmethodListCommand(a1, 0, 0.0));

  g_ClipsCurrentExpression = 0;
}

TEST(cov14_defgeneric, get_method_restrictions_command_best_effort) {
  static _DWORD inner[64];
  static _DWORD outer[64];
  memset(inner, 0, sizeof inner);
  memset(outer, 0, sizeof outer);
  *(int *)((char *)outer + 2) = (int)(intptr_t)inner;
  g_ClipsCurrentExpression = (int)(intptr_t)outer;
  Mem_InitReserveBlock(0, 0);

  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(a1, 0, 0.0));

  g_ClipsCurrentExpression = 0;
}

TEST(cov14_defgeneric, increment_generic_busy_count) {
  static _DWORD obj[128];
  memset(obj, 0, sizeof obj);
  obj[5] = 3; /* offset 20 */
  int r = Defgeneric_IncrementGenericBusyCount((int)(intptr_t)obj);
  CHECK_EQ(r, (int)(intptr_t)obj);
  CHECK_EQ(obj[5], 4);
}
