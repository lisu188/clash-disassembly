/* cov21 cluster: Class/Deffacts/Defgeneric/Method/Deffunction/Defglobal/
 * MessageHandler/Definstances/ObjectsCompiler/Rules construct-registration,
 * codegen-close, and small accessor helpers.
 *
 * Note: many of these recovered functions declare pointer-shaped arguments
 * as plain `int` (a 32-bit address in the original x86 binary). On this
 * 64-bit test build, a stack-local buffer's real address does not fit in an
 * `int`, so any buffer whose address we hand to such a param is declared
 * `static` (landing it in a fixed, low, sub-4GB .bss address under the
 * non-PIE build) rather than on the stack, matching the pattern already
 * used in tests/unit/cases/test_cov20.c. */

/* ---- Class_BsaveWriteHandlerDispatchTable: forwards to
 * Rules_BsaveWriteBlock(4*count, a2, dataptr); with count==0 the nested
 * fwrite_ is skipped entirely (safe); with count!=0 fwrite_ is called with
 * a2==0 as the file handle, which its compat stub explicitly guards
 * (`!file_handle` check), so both branches are safe. ---- */

TEST(cov21_class, bsave_write_handler_dispatch_table_zero_count) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof obj);
  obj[23] = 0; /* *(a1+92): data pointer */
  obj[24] = 0; /* *(a1+96): count */
  TOUCH(Class_BsaveWriteHandlerDispatchTable((int)(intptr_t)obj, 0));
}

TEST(cov21_class, bsave_write_handler_dispatch_table_nonzero_count) {
  static _DWORD obj[64];
  static _DWORD data[16];
  memset(obj, 0, sizeof obj);
  memset(data, 0, sizeof data);
  obj[23] = (int)(intptr_t)data; /* *(a1+92) */
  obj[24] = 1;                   /* *(a1+96) */
  TOUCH(Class_BsaveWriteHandlerDispatchTable((int)(intptr_t)obj, 0));
}

/* ---- Deffacts_CommandDefinitions: plain registration wrapper, safe to call
 * with no arguments. ---- */

TEST(cov21_deffacts, command_definitions) {
  TOUCH(Deffacts_CommandDefinitions());
}

/* ---- Deffacts_ResetAction: *(result+20) selects between a trivial return
 * and a nested Parser_ParseForm call (isolated in its own TEST). ---- */

TEST(cov21_deffacts, reset_action_no_expression) {
  static _DWORD rec[16];
  memset(rec, 0, sizeof rec);
  rec[5] = 0; /* *(record+20) == 0 -> trivial return path */
  CHECK_EQ(Deffacts_ResetAction((int)(intptr_t)rec, 0), (int)(intptr_t)rec);
}

TEST(cov21_deffacts, reset_action_with_expression) {
  static _DWORD rec[16];
  static __int16 toks[8];
  memset(rec, 0, sizeof rec);
  memset(toks, 0, sizeof toks);
  rec[5] = (int)(intptr_t)toks; /* *(record+20) nonzero -> parse path */
  TOUCH(Deffacts_ResetAction((int)(intptr_t)rec, 0));
}

/* ---- Deffacts_RegisterBinaryItem: plain registration wrapper. ---- */

TEST(cov21_deffacts, register_binary_item) {
  TOUCH(Deffacts_RegisterBinaryItem());
}

/* ---- Deffacts_CloseCodeFiles / Deffunction_CloseCodeFiles /
 * Defglobal_CloseConstructCodeFiles: identical shape; each "handle" arg is
 * forwarded (as a fake FILE*-ish token) to Rules_ConstructCodeFileClose,
 * which isn't in this batch; each branch gets its own TEST so a crash in one
 * handle branch can't suppress coverage of the others. ---- */

TEST(cov21_deffacts, close_code_files_all_zero) {
  CHECK_EQ(Deffacts_CloseCodeFiles(0, 0, 5, 0), 0);
}

TEST(cov21_deffacts, close_code_files_a4) {
  TOUCH(Deffacts_CloseCodeFiles(0, 0, 5, 1));
}

TEST(cov21_deffacts, close_code_files_a2) {
  TOUCH(Deffacts_CloseCodeFiles(0, 1, 5, 0));
}

TEST(cov21_deffacts, close_code_files_a1) {
  TOUCH(Deffacts_CloseCodeFiles(1, 0, 5, 0));
}

TEST(cov21_deffunction, close_code_files_all_zero) {
  CHECK_EQ(Deffunction_CloseCodeFiles(0, 0, 5, 0), 0);
}

TEST(cov21_deffunction, close_code_files_a4) {
  TOUCH(Deffunction_CloseCodeFiles(0, 0, 5, 1));
}

TEST(cov21_deffunction, close_code_files_a2) {
  TOUCH(Deffunction_CloseCodeFiles(0, 1, 5, 0));
}

TEST(cov21_deffunction, close_code_files_a1) {
  TOUCH(Deffunction_CloseCodeFiles(1, 0, 5, 0));
}

TEST(cov21_defglobal, close_construct_code_files_all_zero) {
  CHECK_EQ(Defglobal_CloseConstructCodeFiles(0, 0, 5, 0), 0);
}

TEST(cov21_defglobal, close_construct_code_files_a4) {
  TOUCH(Defglobal_CloseConstructCodeFiles(0, 0, 5, 1));
}

TEST(cov21_defglobal, close_construct_code_files_a2) {
  TOUCH(Defglobal_CloseConstructCodeFiles(0, 1, 5, 0));
}

TEST(cov21_defglobal, close_construct_code_files_a1) {
  TOUCH(Defglobal_CloseConstructCodeFiles(1, 0, 5, 0));
}

/* ---- Defgeneric_ClearDefgenericsReady / Defgeneric_ClearDefgenerics: no
 * direct pointer args; both drive global generic-function list state via
 * Rules_IsBloaded()/Defgeneric_GetNextInModule(), which is empty by default
 * in a fresh process, so calling with no setup is safe. ---- */

TEST(cov21_defgeneric, clear_defgenerics_ready) {
  TOUCH(Defgeneric_ClearDefgenericsReady());
}

TEST(cov21_defgeneric, clear_defgenerics) {
  TOUCH(Defgeneric_ClearDefgenerics());
}

/* ---- Defgeneric_MethodsExecuting / Method_FindByIndex: direct offsets into
 * a1: *(a1+32) is a method count, *(a1+28) is a pointer to an array of
 * 40-byte method records. ---- */

TEST(cov21_defgeneric, methods_executing_zero_count) {
  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  a1[8] = 0; /* *(a1+32) count == 0 */
  CHECK_EQ(Defgeneric_MethodsExecuting((int)(intptr_t)a1), 0);
}

TEST(cov21_defgeneric, methods_executing_found_immediately) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[1] = 1; /* *(i+4) nonzero on first record: loop body never runs */
  a1[8] = 1;      /* count */
  a1[7] = (int)(intptr_t)methods; /* *(a1+28) */
  CHECK_EQ(Defgeneric_MethodsExecuting((int)(intptr_t)a1), 1);
}

TEST(cov21_defgeneric, methods_executing_hits_limit) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[1] = 0; /* *(i+4) == 0: enters loop body */
  a1[8] = 1;      /* count == 1 */
  a1[7] = (int)(intptr_t)methods;
  CHECK_EQ(Defgeneric_MethodsExecuting((int)(intptr_t)a1), 0);
}

TEST(cov21_defgeneric, methods_executing_advances_then_found) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[1] = 0;      /* record 0: sentinel not set, loop advances (i+=40) */
  methods[10 + 1] = 1; /* record 1: sentinel set -> break, return 1 */
  a1[8] = 2;           /* count == 2 */
  a1[7] = (int)(intptr_t)methods;
  CHECK_EQ(Defgeneric_MethodsExecuting((int)(intptr_t)a1), 1);
}

TEST(cov21_method, find_by_index_zero_count) {
  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  a1[8] = 0;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1, 42), -1);
}

TEST(cov21_method, find_by_index_found_first) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[0] = 42; /* *i */
  a1[8] = 1;
  a1[7] = (int)(intptr_t)methods;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1, 42), 0);
}

TEST(cov21_method, find_by_index_found_second) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[0] = 7;
  methods[10] = 42;
  a1[8] = 2;
  a1[7] = (int)(intptr_t)methods;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1, 42), 1);
}

TEST(cov21_method, find_by_index_not_found_hits_limit) {
  static _DWORD a1[16];
  static _DWORD methods[3 * 10];
  memset(a1, 0, sizeof a1);
  memset(methods, 0, sizeof methods);
  methods[0] = 1;
  a1[8] = 1;
  a1[7] = (int)(intptr_t)methods;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1, 999), -1);
}

/* ---- Defgeneric_CloseCodeFiles / ObjectsCompiler_CloseConstructFileGroup:
 * loop over a fixed-size array (5 / 8 elements respectively), forwarding
 * each element to Rules_ConstructCodeFileClose. These take real `int *` /
 * `_DWORD *` parameters (not truncated `int` addresses), so ordinary local
 * arrays are fine here. Kept in a dedicated TEST since the nested call chain
 * may fault deep inside I/O helpers outside this batch; our own loop
 * body/lines are reached either way. ---- */

TEST(cov21_defgeneric, close_code_files_loop) {
  int a1arr[8];
  _DWORD a2arr[8];
  int i;
  memset(a1arr, 0, sizeof a1arr);
  memset(a2arr, 0, sizeof a2arr);
  for (i = 0; i < 8; ++i) {
    a1arr[i] = 1; /* nonzero "result" token per Rules_ConstructCodeFileClose */
  }
  TOUCH(Defgeneric_CloseCodeFiles(a1arr, a2arr, 5, 0));
}

TEST(cov21_objectscompiler, close_construct_file_group_loop) {
  int a1arr[16];
  _DWORD a2arr[16];
  int i;
  memset(a1arr, 0, sizeof a1arr);
  memset(a2arr, 0, sizeof a2arr);
  for (i = 0; i < 16; ++i) {
    a1arr[i] = 1;
  }
  TOUCH(ObjectsCompiler_CloseConstructFileGroup(a1arr, a2arr, 5, 0));
}

/* ---- Defgeneric_RestrictionTypeToCode: forwards to Output_WriteFormatted
 * (a1==0 makes it return early) and ObjectsCompiler_WriteDefclassPointerRef;
 * the latter reads an uninitialized local internally (decompiler artifact),
 * so behavior beyond that point is inherently unpredictable but harness
 * isolated. ---- */

TEST(cov21_defgeneric, restriction_type_to_code) {
  TOUCH(Defgeneric_RestrictionTypeToCode(0, 0, 0));
}

/* ---- Method_AppendParameterNode: allocates an AST node via AST_NewNode,
 * which needs the AST memory pool initialized (Mem_InitReserveBlock sets the
 * dword_54DBA8 free-list head used by AST_NewNode); without that the nested
 * allocator would dereference an uninitialized global. ---- */

TEST(cov21_method, append_parameter_node_a1_zero) {
  static _DWORD a2[16];
  memset(a2, 0, sizeof a2);
  Mem_InitReserveBlock(0, 0);
  TOUCH(Method_AppendParameterNode(0, (int)(intptr_t)a2, 1));
}

TEST(cov21_method, append_parameter_node_a1_nonzero) {
  static _DWORD a2[16];
  memset(a2, 0, sizeof a2);
  Mem_InitReserveBlock(0, 0);
  TOUCH(Method_AppendParameterNode(1, (int)(intptr_t)a2, 2));
}

/* ---- Method_FindApplicableMethod: walks a restriction-record array rooted
 * at *(a1+28), sized by *(a1+32); with a2==0 the walk starts at the array
 * base. A zeroed record array keeps the nested
 * Method_RestrictionsSatisfiedByArgs reads in-bounds and predictable. ---- */

TEST(cov21_method, find_applicable_method_a2_zero) {
  static _DWORD a1[16];
  static _DWORD restrictions[4 * 20];
  memset(a1, 0, sizeof a1);
  memset(restrictions, 0, sizeof restrictions);
  a1[8] = 1; /* *(a1+32) count */
  a1[7] = (int)(intptr_t)restrictions; /* *(a1+28) base */
  TOUCH(Method_FindApplicableMethod((int)(intptr_t)a1, 0, 0.0));
}

TEST(cov21_method, find_applicable_method_zero_count) {
  static _DWORD a1[16];
  memset(a1, 0, sizeof a1);
  a1[8] = 0; /* count == 0: v4 >= bound immediately -> return 0 */
  a1[7] = (int)(intptr_t)a1;
  CHECK_EQ(Method_FindApplicableMethod((int)(intptr_t)a1, 0, 0.0), 0);
}

/* ---- Defglobal_GetWatchFlagField / Defglobal_SetWatchFlagField: pure
 * bit-twiddling on the caller's buffer; fully safe both ways. ---- */

TEST(cov21_defglobal, get_watch_flag_field_set) {
  static _DWORD a1[8];
  memset(a1, 0, sizeof a1);
  a1[5] = 1; /* *(a1+20) & 1 */
  CHECK_EQ(Defglobal_GetWatchFlagField((int)(intptr_t)a1), 1);
}

TEST(cov21_defglobal, get_watch_flag_field_clear) {
  static _DWORD a1[8];
  memset(a1, 0, sizeof a1);
  a1[5] = 0;
  CHECK_EQ(Defglobal_GetWatchFlagField((int)(intptr_t)a1), 0);
}

TEST(cov21_defglobal, set_watch_flag_field_true) {
  static _DWORD a2[8];
  memset(a2, 0, sizeof a2);
  CHECK_EQ(Defglobal_SetWatchFlagField(1, (int)(intptr_t)a2), 1);
}

TEST(cov21_defglobal, set_watch_flag_field_false) {
  static _DWORD a2[8];
  memset(a2, 0xFF, sizeof a2);
  CHECK_EQ(Defglobal_SetWatchFlagField(0, (int)(intptr_t)a2), 0);
}

/* ---- Defglobal_RegisterResetGlobalsCommands: plain registration
 * wrapper. ---- */

TEST(cov21_defglobal, register_reset_globals_commands) {
  TOUCH(Defglobal_RegisterResetGlobalsCommands());
}

/* ---- Defglobals_ResetCallback: forwards a1 through a mismatched function
 * pointer cast to Output_WriteFormatted (decompiler artifact reflecting a
 * lost-ABI callsite); isolated since remaining args are read from whatever
 * garbage occupies the missing argument slots. ---- */

TEST(cov21_defglobals, reset_callback) {
  TOUCH(Defglobals_ResetCallback(0));
}

/* ---- Runtime_ExprDescriptorNoop: trivial passthrough. ---- */

TEST(cov21_runtime, expr_descriptor_noop) {
  CHECK_EQ(Runtime_ExprDescriptorNoop(1234), 1234);
  CHECK_EQ(Runtime_ExprDescriptorNoop(0), 0);
}

/* ---- MessageHandler_EnumNext: direct offsets a1+88 / a1+96, no nested
 * calls. ---- */

TEST(cov21_messagehandler, enum_next_a2_zero_has_handlers) {
  static _DWORD a1[32];
  memset(a1, 0, sizeof a1);
  a1[22] = 1; /* *(a1+88) nonzero */
  CHECK_EQ(MessageHandler_EnumNext((int)(intptr_t)a1, 0), 1);
}

TEST(cov21_messagehandler, enum_next_a2_zero_no_handlers) {
  static _DWORD a1[32];
  memset(a1, 0, sizeof a1);
  a1[22] = 0;
  CHECK_EQ(MessageHandler_EnumNext((int)(intptr_t)a1, 0), 0);
}

TEST(cov21_messagehandler, enum_next_a2_matches_last) {
  static _DWORD a1[32];
  memset(a1, 0, sizeof a1);
  a1[24] = 5; /* *(a1+96) */
  CHECK_EQ(MessageHandler_EnumNext((int)(intptr_t)a1, 5), 0);
}

TEST(cov21_messagehandler, enum_next_a2_advances) {
  static _DWORD a1[32];
  memset(a1, 0, sizeof a1);
  a1[24] = 5;
  CHECK_EQ(MessageHandler_EnumNext((int)(intptr_t)a1, 2), 3);
}

/* ---- MessageHandler_PrintHandlerListTally: with a2==0 it walks the
 * class-record list via Class_GetNextRecord, which is empty by default in a
 * fresh process (safe, trivial loop). With a2/a4 nonzero it takes the direct
 * "specific class" branch, backed by a real buffer. ---- */

TEST(cov21_messagehandler, print_handler_list_tally_a2_zero) {
  TOUCH(MessageHandler_PrintHandlerListTally((int)"werror", 0, 0, 0));
}

TEST(cov21_messagehandler, print_handler_list_tally_a2_a4_nonzero) {
  static _DWORD a2[32];
  memset(a2, 0, sizeof a2);
  TOUCH(MessageHandler_PrintHandlerListTally((int)"werror", (int)(intptr_t)a2, 0, 1));
}

TEST(cov21_messagehandler, print_handler_list_tally_a2_nonzero_a4_zero) {
  static _DWORD a2[32];
  memset(a2, 0, sizeof a2);
  TOUCH(MessageHandler_PrintHandlerListTally((int)"werror", (int)(intptr_t)a2, 0, 0));
}

/* ---- MessageHandler_PreviewSendForSymbol: a2 is a real `_BYTE *`, so an
 * ordinary local buffer is fine. With no symbol table registered
 * (dword_54DD50 == 0 by default), Rules_FindSymbolEntry returns NULL, so
 * this safely exercises the "not found" branch. ---- */

TEST(cov21_messagehandler, preview_send_for_symbol_not_found) {
  static _BYTE name[16];
  memset(name, 0, sizeof name);
  memcpy(name, "foo", 4);
  CHECK_EQ((intptr_t)MessageHandler_PreviewSendForSymbol((int)"werror", name), 0);
}

/* ---- MessageHandler_RegisterSystemHandlers: plain registration
 * wrapper. ---- */

TEST(cov21_messagehandler, register_system_handlers) {
  TOUCH(MessageHandler_RegisterSystemHandlers());
}

/* ---- MessageHandler_UndefineForClassOrAll: a1/a2 are real `_DWORD *` /
 * `signed int *` params, so ordinary local buffers are fine. a1==0 walks the
 * (empty by default) class-record list; a1!=0 takes the direct-class branch
 * via MessageHandler_RemoveByNameAndType. a2==0 forces a Str_Intern lookup
 * instead. a4 selects whether MessageHandler_TypeIndexFromKeyword is
 * consulted first. ---- */

TEST(cov21_messagehandler, undefine_for_class_or_all_a1_zero_a4_zero) {
  TOUCH(MessageHandler_UndefineForClassOrAll(0, 0, 0, 0));
}

TEST(cov21_messagehandler, undefine_for_class_or_all_a1_zero_a2_nonzero_a4_nonzero) {
  static signed int a2[4];
  memset(a2, 0, sizeof a2);
  TOUCH(MessageHandler_UndefineForClassOrAll(0, a2, 0, 1));
}

TEST(cov21_messagehandler, undefine_for_class_or_all_a1_nonzero) {
  /* a1/a2 get re-cast to `int` internally (e.g. MessageHandler_RemoveByNameAndType's
   * `(int)a2`), which loses the high bits of a real 64-bit stack address; use
   * static storage so the truncated 32-bit value still resolves correctly. */
  static _DWORD a1[32];
  static signed int a2[4];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  TOUCH(MessageHandler_UndefineForClassOrAll(a1, a2, 0, 0));
}

/* ---- Definstances_IsDeletable / Definstances_DeleteRecord: no explicit
 * arguments; the recovered source reads an uninitialized local internally
 * (decompiler artifact), so behavior is not fully controllable, but calling
 * them is harness-isolated. ---- */

TEST(cov21_definstances, is_deletable) {
  TOUCH(Definstances_IsDeletable());
}

TEST(cov21_definstances, delete_record) {
  TOUCH(Definstances_DeleteRecord());
}

/* ---- Definstances_ReportCannotDelete: forwards to
 * Rules_ReportCantDeleteItem(a2, a1). ---- */

TEST(cov21_definstances, report_cannot_delete) {
  CHECK_EQ(Definstances_ReportCannotDelete(0, 0), 0);
}

/* ---- Rules_IsObjectPatternKeyword: strcmp_ against the literal "object".
 * `this` is a real `void *`, but strcmp_'s own signature narrows both
 * operands to `_DWORD` (32-bit), so a genuine 64-bit stack address would be
 * truncated to garbage; use static storage to keep the (still-truncated but
 * now correct) low 32 bits resolvable. Exercise both the match and mismatch
 * branches with real NUL-terminated strings. ---- */

TEST(cov21_rules, is_object_pattern_keyword_match) {
  static char buf[16];
  memset(buf, 0, sizeof buf);
  strcpy(buf, "object");
  CHECK(Rules_IsObjectPatternKeyword(buf));
}

TEST(cov21_rules, is_object_pattern_keyword_mismatch) {
  static char buf[16];
  memset(buf, 0, sizeof buf);
  strcpy(buf, "widget");
  CHECK(!Rules_IsObjectPatternKeyword(buf));
}
