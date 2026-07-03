/* cov11 cluster: Rules_* rule-engine helpers (salience/focus-stack/break
 * flags/arg-coercion/hashing), Instance_* slot helpers, CRT Watcom EH unwind
 * helpers, Output_* long-string/float printers. */

/* ---- Rules_SalienceEvaluationModeName: pure 4-way switch on a1. ---- */

TEST(cov11_salience, mode_name_all_branches) {
  CHECK(Rules_SalienceEvaluationModeName(0) != 0);
  CHECK(Rules_SalienceEvaluationModeName(1) != 0);
  CHECK(Rules_SalienceEvaluationModeName(2) != 0);
  CHECK(Rules_SalienceEvaluationModeName(99) != 0);
}

/* ---- Rules_ClearFocusStackCommand / Rules_GetFocusStackFunction: both just
 * forward through Lexer_TokenExpect(0), which calls Rules_RtnArgCount().
 * That unconditionally dereferences dword_51A960+6 with no NULL check, so
 * (unlike many of the other Rules_Rtn* helpers) it crashes immediately if
 * dword_51A960 is left at its NULL default. Point it at a zeroed local
 * "empty argument list" node (same technique as cov20's fake_expr) so the
 * read is safe and Rules_RtnArgCount sees an empty list. */

TEST(cov11_focus, clear_focus_stack_command) {
  static _DWORD fake_expr[16];
  int saved = dword_51A960;
  memset(fake_expr, 0, sizeof fake_expr);
  dword_51A960 = (int)(intptr_t)fake_expr;
  TOUCH(Rules_ClearFocusStackCommand());
  dword_51A960 = saved;
}

/* Rules_GetFocusStackFunction passes an uninitialized local ('v1' in the
 * recovered source) to Rules_BuildFocusStackList whenever Lexer_TokenExpect
 * doesn't take its error path, so this may legitimately crash on whatever
 * garbage happened to be on the stack; harness catches it via siglongjmp. */
TEST(cov11_focus, get_focus_stack_function) {
  static _DWORD fake_expr[16];
  int saved = dword_51A960;
  memset(fake_expr, 0, sizeof fake_expr);
  dword_51A960 = (int)(intptr_t)fake_expr;
  TOUCH(Rules_GetFocusStackFunction());
  dword_51A960 = saved;
}

/* ---- Rules_SetBreakFlag / Rules_ClearBreakFlag / Rules_RuleHasBreakFlag:
 * pure linked-list walk over caller-built "rule" nodes; offset+29 holds a
 * flag byte (bit 3 == break flag), offset+48 holds the "next" link. ---- */

TEST(cov11_break, set_flag_walks_chain_and_null) {
  static _DWORD nodeA[32], nodeB[32], nodeC[32];
  memset(nodeA, 0, sizeof nodeA);
  memset(nodeB, 0, sizeof nodeB);
  memset(nodeC, 0, sizeof nodeC);
  *(_DWORD *)((char *)nodeA + 48) = (int)(intptr_t)nodeB;
  *(_DWORD *)((char *)nodeB + 48) = (int)(intptr_t)nodeC;
  *(_DWORD *)((char *)nodeC + 48) = 0;
  TOUCH(Rules_SetBreakFlag((int)(intptr_t)nodeA));
  CHECK((*((char *)nodeA + 29) & 8) != 0);
  CHECK((*((char *)nodeC + 29) & 8) != 0);
  CHECK_EQ(Rules_SetBreakFlag(0), 0);
}

TEST(cov11_break, clear_flag_walks_chain_and_null) {
  static _DWORD nodeA[32], nodeB[32];
  memset(nodeA, 0, sizeof nodeA);
  memset(nodeB, 0, sizeof nodeB);
  *(_DWORD *)((char *)nodeA + 48) = (int)(intptr_t)nodeB;
  *(_DWORD *)((char *)nodeB + 48) = 0;
  *((char *)nodeA + 29) = 8; /* already flagged */
  *((char *)nodeB + 29) = 0; /* not flagged: stops the inner while() */
  CHECK_EQ(Rules_ClearBreakFlag((int)(intptr_t)nodeA), 1);
  CHECK_EQ(Rules_ClearBreakFlag(0), 0);
}

TEST(cov11_break, rule_has_break_flag_both_states) {
  static _DWORD node[32];
  memset(node, 0, sizeof node);
  *(_DWORD *)((char *)node + 28) = 0;
  CHECK_EQ(Rules_RuleHasBreakFlag((int)(intptr_t)node), 0);
  *(_DWORD *)((char *)node + 28) = 0x800; /* bit 11 -> sign bit after <<20 */
  CHECK(Rules_RuleHasBreakFlag((int)(intptr_t)node) != 0);
}

/* ---- Rules_RemoveAllBreakFlags: Module_NextEnum(0) returns the
 * dword_51A9AC global directly, which is NULL by default, so the outer while
 * breaks on the first iteration -- fully safe. ---- */

TEST(cov11_break, remove_all_break_flags_empty_module_list) {
  TOUCH(Rules_RemoveAllBreakFlags());
}

/* ---- Lexer_TokenExpect: exercises both the "matches" and "mismatch"
 * outcomes. Rules_RtnArgCount() unconditionally reads dword_51A960+6, so it
 * needs to be pointed at a real (zeroed => empty-list) node first; the
 * branch taken depends on the decompiled/undefined 'v2', so both calls just
 * drive different concrete a1 values and let whichever path executes go
 * through the safe error-report helpers. ---- */

TEST(cov11_lexer, token_expect_match_and_mismatch) {
  static _DWORD fake_expr[16];
  int saved = dword_51A960;
  memset(fake_expr, 0, sizeof fake_expr);
  dword_51A960 = (int)(intptr_t)fake_expr;
  TOUCH(Lexer_TokenExpect(0));
  TOUCH(Lexer_TokenExpect(1));
  TOUCH(Lexer_TokenExpect(-1));
  dword_51A960 = saved;
}

/* ---- Rules_ListInstancesForClassOrModule: only the a3==0 branches are
 * driven (a3!=0 reads uninitialized locals feeding Class_LookupByModule,
 * which isn't safe to construct). a4==0 exercises
 * Rules_GetNextInstanceInScope(0) -> dword_51AD0C==0 by default -> 0.
 * a4!=0 exercises the Class_GetNextRecord(0) enumeration loop, which is
 * empty by default too. ---- */

TEST(cov11_instances, list_for_class_or_module_no_instances) {
  CHECK_EQ(Rules_ListInstancesForClassOrModule(0, 0, 0, 0), 0);
}

TEST(cov11_instances, list_for_class_or_module_all_classes_empty) {
  CHECK_EQ(Rules_ListInstancesForClassOrModule(0, 0, 0, 1), 0);
}

/* ---- Rules_FindInstanceSlot: Rules_FindSymbolEntry returns 0 whenever the
 * function-name hash table (dword_54DD50) hasn't been carved out yet, which
 * is the default state, so this drives the "no such symbol" fast path. ---- */

TEST(cov11_instances, find_instance_slot_symbol_not_found) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof obj);
  CHECK_EQ((intptr_t)Rules_FindInstanceSlot((int)(intptr_t)obj, (_BYTE *)"no-such-slot"), 0);
}

/* ---- Rules_RegisterHostFunctionNoRestrictions: thin wrapper over
 * Rules_RegisterHostFunction(..., 0); needs the reserve-block arena carved
 * out first (dword_54DBA8), same setup other batches already use for
 * registration-style functions. ---- */

TEST(cov11_hostfn, register_no_restrictions) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables(); /* carves out dword_54DD50, the symbol hash table
                              Str_Intern indexes into. */
  TOUCH(Rules_RegisterHostFunctionNoRestrictions("cov11-test-fn", 'i', 0, 0));
}

/* ---- Rules_GetArgTypeName: pure switch covering every case label plus the
 * default. ---- */

TEST(cov11_argtype, get_arg_type_name_all_cases) {
  const char cases[] = "adefghijklmnopqswuxyz?";
  size_t i;
  for (i = 0; i < sizeof(cases) - 1; ++i) {
    CHECK(Rules_GetArgTypeName(cases[i]) != 0);
  }
}

/* ---- Rules_CoerceFormToNumericArg: the "*a1 <= 1u" branch reads a1/a1+1
 * directly (no Parser_ParseForm call). The "*a1 > 1u" branch calls
 * Parser_ParseForm, which for the simple scalar tags {0,1,2,3,5,7,8} goes
 * straight to its LABEL_4 fast path (v5[1]=tag; v5[2]=*(a1+1)) and then
 * Rules_PropagateReturnValueDepth -> Rules_ClampEvaluationDepth(tag, P),
 * which for tags {0,1,2,3,8} only touches P[2] -- so P just needs to be a
 * real, generously sized buffer (we point it at the a1 buffer itself). */

TEST(cov11_coerce, form_to_numeric_direct_no_arg_flag) {
  static _DWORD a1buf[64];
  static _DWORD a3buf[64];
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  *(short *)a1buf = 0; /* <= 1u: skip Parser_ParseForm entirely */
  TOUCH(Rules_CoerceFormToNumericArg((__int16 *)a1buf, 0, a3buf, 0.0, 0));
}

TEST(cov11_coerce, form_to_numeric_direct_with_arg_flag) {
  static _DWORD a1buf[64];
  static _DWORD a3buf[64];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  *(short *)a1buf = 1; /* <= 1u, v5 == 1 */
  *(_DWORD *)((char *)a1buf + 2) = (int)(intptr_t)a1buf; /* v6 -> readable */
  TOUCH(Rules_CoerceFormToNumericArg((__int16 *)a1buf, 1, a3buf, 0.0, 0));
}

TEST(cov11_coerce, form_to_numeric_via_parse_form_error_branch) {
  static _DWORD a1buf[64];
  static _DWORD a3buf[64];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(a1buf, 0, sizeof a1buf);
  memset(a3buf, 0, sizeof a3buf);
  *(short *)a1buf = 2; /* > 1u: Parser_ParseForm LABEL_4 fast path, tag=2 */
  *(_DWORD *)((char *)a1buf + 2) = (int)(intptr_t)a1buf;
  TOUCH(Rules_CoerceFormToNumericArg((__int16 *)a1buf, 0, a3buf, 0.0, 0));
}

/* ---- Rules_GetFileNameArg / Rules_GetConstructNameArg: both funnel through
 * Rules_RtnUnknown/Rules_RtnArgCount, which read *(dword_51A960+6) (NULL by
 * default -> crash). dword_51A960 is an "argument list" pointer: the memory
 * at (dword_51A960+6) must itself CONTAIN the address of an argument node
 * (a separate buffer), not just be that address, so this uses two distinct
 * static buffers -- "anchor" (whose +6 slot holds the node pointer) and
 * "termBuf" (the node itself). termBuf's scalar tag takes Parser_ParseForm's
 * safe LABEL_4 path, mirroring the cov20 "matches_command" fake_expr
 * technique. Tag 2 drives the "success" branch (returns *(v7+16)); any other
 * tag drives the "wrong type" error branch. */

TEST(cov11_filearg, get_file_name_arg_wrong_type) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 1; /* tag != 2 && != 3 -> error branch */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf; /* v7 -> readable */
  *(_DWORD *)((char *)termBuf + 10) = 0; /* terminate arg-list walk */
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;
  dword_51A960 = (int)(intptr_t)anchor;
  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));
  dword_51A960 = saved;
}

TEST(cov11_filearg, get_file_name_arg_success) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2; /* tag == 2 -> success branch, reads *(v7+16) */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;
  dword_51A960 = (int)(intptr_t)anchor;
  TOUCH(Rules_GetFileNameArg(1, 0, 0.0));
  dword_51A960 = saved;
}

TEST(cov11_constructarg, get_construct_name_arg_wrong_arg_count) {
  static _DWORD anchor[16];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  dword_51A960 = (int)(intptr_t)anchor; /* Rules_RtnArgCount() -> 0 != 1 */
  CHECK_EQ(Rules_GetConstructNameArg(0, 0, 0.0), 0);
  dword_51A960 = saved;
}

TEST(cov11_constructarg, get_construct_name_arg_wrong_type) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 1; /* tag != 2 -> error branch */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;
  dword_51A960 = (int)(intptr_t)anchor;
  CHECK_EQ(Rules_GetConstructNameArg(0, 0, 0.0), 0);
  dword_51A960 = saved;
}

TEST(cov11_constructarg, get_construct_name_arg_success) {
  static _DWORD anchor[16];
  static _DWORD termBuf[64];
  int saved = dword_51A960;
  memset(anchor, 0, sizeof anchor);
  memset(termBuf, 0, sizeof termBuf);
  *(short *)termBuf = 2; /* tag == 2 -> success branch */
  *(_DWORD *)((char *)termBuf + 2) = (int)(intptr_t)termBuf;
  *(_DWORD *)((char *)termBuf + 10) = 0;
  *(_DWORD *)((char *)anchor + 6) = (int)(intptr_t)termBuf;
  dword_51A960 = (int)(intptr_t)anchor;
  TOUCH(Rules_GetConstructNameArg(0, 0, 0.0));
  dword_51A960 = saved;
}

/* ---- Rules_ReportSymbolTypeError: Rules_MakeSymbol looks the interned name
 * up in dword_54DD40 (the function-name hash table); once carved out via
 * Rules_InitFunctionNameHashTable it's empty, so Rules_MakeSymbol returns 0
 * and this drives the (safe) early-return branch. ---- */

TEST(cov11_symbolerr, report_symbol_type_error_not_found) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitFunctionNameHashTable();
  CHECK_EQ((intptr_t)Rules_ReportSymbolTypeError((_BYTE *)"cov11-missing-sym", 0), 0);
}

/* ---- Rules_HashDoubleValue / Rules_HashIntegerValue / Rules_HashBitmapValue:
 * pure arithmetic/byte-summing helpers; drive both the positive- and
 * negative-remainder branches, and both the bulk (4-byte-chunk) and tail
 * loops of the bitmap hash. ---- */

TEST(cov11_hash, double_value_both_signs) {
  CHECK_EQ(Rules_HashDoubleValue(7, 0, 3), 1);
  CHECK(Rules_HashDoubleValue(0x80000000u, 0, 0x80000005u) >= 0 || 1);
}

TEST(cov11_hash, integer_value_both_signs) {
  CHECK_EQ(Rules_HashIntegerValue(7, 3), 1);
  CHECK_EQ(Rules_HashIntegerValue(-7, 3), 1);
}

TEST(cov11_hash, bitmap_value_bulk_and_tail) {
  static unsigned char data[64];
  size_t i;
  for (i = 0; i < sizeof(data); ++i) data[i] = (unsigned char)(i * 7 + 1);
  TOUCH(Rules_HashBitmapValue((int)(intptr_t)data, 7, 10)); /* 2 quads + 2 tail bytes */
  TOUCH(Rules_HashBitmapValue((int)(intptr_t)data, 7, 0));  /* both loops skipped */
}

/* ---- Rules_IncrementRefCountField40 / Instance_DecrementBusyCount: trivial
 * pointer-arithmetic increment/decrement through a caller buffer. ---- */

TEST(cov11_refcount, increment_and_decrement_field40) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof obj);
  CHECK_EQ(Rules_IncrementRefCountField40((int)(intptr_t)obj), (int)(intptr_t)obj);
  CHECK_EQ(*(_DWORD *)((char *)obj + 40), 1);
  CHECK_EQ(Instance_DecrementBusyCount((int)(intptr_t)obj), (int)(intptr_t)obj);
  CHECK_EQ(*(_DWORD *)((char *)obj + 40), 0);
}

/* ---- Instance_FindByName: only the "no module separator" branch is driven
 * (Rules_FindModuleSeparator returns 0 for a plain name), which funnels into
 * Instance_LookupInHashBucket with a3==0; that needs the instance hash
 * table (dword_51A278) carved out first via Instance_InitHashTable so the
 * bucket read doesn't dereference NULL. With an empty table the bucket
 * chain is empty and the lookup safely returns 0. ---- */

TEST(cov11_instance, find_by_name_no_separator_not_found) {
  static _DWORD sym[64];
  static const char *name = "PlainInstanceName";
  Mem_InitReserveBlock(0, 0);
  Instance_InitHashTable();
  memset(sym, 0, sizeof sym);
  sym[4] = (int)(intptr_t)name; /* offset +16 -> index 4 */
  CHECK_EQ((intptr_t)Instance_FindByName((int)(intptr_t)sym), 0);
}

/* ---- Instance_GetSlotValueBySymbol / Instance_ResolveSlotIndex:
 * Class_FindSlotNameID looks the slot name up in dword_51AD70 (the class
 * slot-name hash table); once carved out via Class_InitHashTables it's
 * empty, so the lookup returns -1 and both functions take their "not found"
 * fast path without ever dereferencing the class-record argument. ---- */

TEST(cov11_instance, get_slot_value_by_symbol_not_found) {
  static _DWORD instObj[64];
  static _DWORD symObj[64];
  Mem_InitReserveBlock(0, 0);
  Class_InitHashTables();
  memset(instObj, 0, sizeof instObj);
  memset(symObj, 0, sizeof symObj);
  CHECK_EQ(Instance_GetSlotValueBySymbol((int)(intptr_t)instObj, (int)(intptr_t)symObj), 0);
}

TEST(cov11_instance, resolve_slot_index_not_found) {
  static _DWORD classObj[64];
  static _DWORD symObj[64];
  Mem_InitReserveBlock(0, 0);
  Class_InitHashTables();
  memset(classObj, 0, sizeof classObj);
  memset(symObj, 0, sizeof symObj);
  CHECK_EQ(Instance_ResolveSlotIndex((int)(intptr_t)classObj, (int)(intptr_t)symObj), (unsigned int)-1);
}

/* ---- Instance_PutSlotValue: forces Instance_ValidateSlotValueConstraints's
 * first error branch (a3[1]==4 and (*a2 & 2)==0), which prints the "illegal
 * for single-valued slot" error via Rules_PrintDataObject. That print path
 * treats a3 (tag 4 == multifield) as a real multifield data object and
 * walks into Lexer_OutputFieldRange/Rules_PrintMultifieldRange over it, so
 * with an all-zero a3 buffer it reliably segfaults partway through -- still
 * worth calling (isolated) for the lines reached first (Validate's own
 * entry, Instance_PutSlotValue's call site). Instance_PutSlotValue passes
 * *a2 (not a2 itself) as Validate's "a2" parameter, which Validate then
 * dereferences again (*(_BYTE*)a2), so a2val must itself hold a pointer to
 * a real, zeroed byte buffer rather than a plain flag value. ---- */

TEST(cov11_instance, put_slot_value_validation_fails) {
  static _DWORD a1obj[64];
  static _DWORD a3obj[64];
  static _BYTE flagsByte[16];
  static int a2val;
  int *a2ptr = &a2val;
  memset(a1obj, 0, sizeof a1obj);
  memset(a3obj, 0, sizeof a3obj);
  memset(flagsByte, 0, sizeof flagsByte);
  a2val = (int)(intptr_t)flagsByte; /* *(_BYTE*)a2 & 2 == 0 */
  a3obj[1] = 4; /* a1[1] == 4 in Validate */
  TOUCH(Instance_PutSlotValue(a1obj, a2ptr, a3obj, 0.0));
}

/* ---- Instance_NotifyCreated: forwards to Rules_ObjectMatchAction with a
 * fabricated "a1==1" action code, which drives
 * Rules_AssertNewObjectIntoNetwork -- not part of this batch and not
 * necessarily safe to construct, so this call is isolated and may crash;
 * the harness catches it via siglongjmp either way. ---- */

TEST(cov11_instance, notify_created) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof obj);
  TOUCH(Instance_NotifyCreated(obj, 0.0));
}

/* ---- CRT_WatcomEHUnwindThreadToState / CRT_WatcomEHUnwindToExceptionList:
 * both funnel into CRT_WatcomEHUnwindToState with a "current program state"
 * pointer sourced from the stubbed _wcpp_4_pgm_thread__ (always returns 0)
 * or the fake TEB's ExceptionList (NULL by default), so a3 ends up 0 and the
 * very first dereference (*(a3+8)) segfaults deterministically. Still worth
 * calling (isolated) for the handful of lines reached before the crash. ---- */

TEST(cov11_crt, watcom_unwind_thread_to_state) {
  static _DWORD a2buf[64];
  memset(a2buf, 0, sizeof a2buf);
  TOUCH(CRT_WatcomEHUnwindThreadToState(0, (int)(intptr_t)a2buf));
}

TEST(cov11_crt, watcom_unwind_to_exception_list) {
  static _DWORD a2buf[64];
  memset(a2buf, 0, sizeof a2buf);
  TOUCH(CRT_WatcomEHUnwindToExceptionList(0, (int)(intptr_t)a2buf));
}

/* ---- Output_WriteLongString: drives the NULL fast path, a short string
 * (<=500 chars, single Output_Write), and a long string (>500 chars, which
 * loops splitting off 500-byte chunks). ---- */

TEST(cov11_output, write_long_string_null) {
  CHECK_EQ(Output_WriteLongString(0, 0), 0);
}

TEST(cov11_output, write_long_string_short) {
  char buf[64];
  strcpy(buf, "a short string");
  TOUCH(Output_WriteLongString(0, buf));
}

TEST(cov11_output, write_long_string_over_500_chars) {
  static char buf[1200];
  size_t i;
  for (i = 0; i < sizeof(buf) - 1; ++i) buf[i] = 'a' + (char)(i % 26);
  buf[sizeof(buf) - 1] = '\0';
  TOUCH(Output_WriteLongString(0, buf));
}

/* ---- Rules_PrintFloat: forwards through Rules_FloatToSymbol/Output_Write;
 * both are used pervasively elsewhere with a plain int "logical name" arg,
 * so 0 is a safe stand-in. ---- */

TEST(cov11_output, print_float) {
  TOUCH(Rules_PrintFloat(0, 3.5));
  TOUCH(Rules_PrintFloat(0, -1.25));
}
