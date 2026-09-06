/* cov20 cluster: CRT timezone helpers, Rules_* registration/codegen/parse
 * helpers, Parser_* helpers, Module_* helpers. */

/* ---- CRT_TzYearStartsInDaylightTime / CRT_CompareTzTransitionDate ---- */

TEST(cov20_crt, tz_year_starts_return1_v3_gt_v4) {
  _DWORD a1[64];
  _DWORD a2[64];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[8] = 0;          /* skip goto LABEL_6 on first check */
  a2[8] = 0;          /* *(a2+32) == 0 */
  a1[4] = 10;         /* v3 */
  a2[4] = 5;          /* v4 at byte offset 16 -> index 4 */
  CHECK_EQ(CRT_TzYearStartsInDaylightTime(a1, (int)(intptr_t)a2, 2020), 1);
}

TEST(cov20_crt, tz_year_starts_return0_v3_lt_v4) {
  _DWORD a1[64];
  _DWORD a2[64];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[8] = 0;
  a2[8] = 0;
  a1[4] = 1;
  a2[4] = 100;
  CHECK_EQ(CRT_TzYearStartsInDaylightTime(a1, (int)(intptr_t)a2, 2020), 0);
}

TEST(cov20_crt, tz_year_starts_label6_a1_flag_set) {
  /* Forces the goto LABEL_6 path (a1[8] nonzero). This dereferences an
   * uninitialized local ('v7') inside the recovered function on the second
   * CRT_TzRuleDayOfYear call, so it may legitimately crash; harness catches
   * it via siglongjmp. Set a1[8]=1 so the *first* CRT_TzRuleDayOfYear call
   * (on the real a1 pointer) is safe and returns quickly. */
  _DWORD a1[64];
  _DWORD a2[64];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[8] = 1;
  a1[7] = 5;
  a2[8] = 0;
  TOUCH(CRT_TzYearStartsInDaylightTime(a1, (int)(intptr_t)a2, 2020));
}

TEST(cov20_crt, compare_tz_transition_v2_lt_v3) {
  _DWORD a1[8], a2[8];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[2] = 1;
  a2[2] = 5;
  CHECK_EQ(CRT_CompareTzTransitionDate(a1, a2), 1);
}

TEST(cov20_crt, compare_tz_transition_v2_gt_v3) {
  _DWORD a1[8], a2[8];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[2] = 9;
  a2[2] = 1;
  CHECK_EQ(CRT_CompareTzTransitionDate(a1, a2), 0);
}

TEST(cov20_crt, compare_tz_transition_eq_v5_lt_v6) {
  _DWORD a1[8], a2[8];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[2] = 3; a2[2] = 3;
  a1[1] = 1; a2[1] = 5;
  CHECK_EQ(CRT_CompareTzTransitionDate(a1, a2), 1);
}

TEST(cov20_crt, compare_tz_transition_eq_v5_eq_v6_a0_lt) {
  _DWORD a1[8], a2[8];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[2] = 3; a2[2] = 3;
  a1[1] = 2; a2[1] = 2;
  a1[0] = 1; a2[0] = 9;
  CHECK_EQ(CRT_CompareTzTransitionDate(a1, a2), 1);
}

TEST(cov20_crt, compare_tz_transition_eq_all_false) {
  _DWORD a1[8], a2[8];
  memset(a1, 0, sizeof a1);
  memset(a2, 0, sizeof a2);
  a1[2] = 3; a2[2] = 3;
  a1[1] = 2; a2[1] = 2;
  a1[0] = 9; a2[0] = 1;
  CHECK_EQ(CRT_CompareTzTransitionDate(a1, a2), 0);
}

/* ---- Rules_Register*BinaryItem / Rules_RegisterRuleCommands: plain
 * registration wrappers that append to global linked lists; safe to call
 * repeatedly with no arguments. ---- */

TEST(cov20_rules, register_deftemplate_binary_item) {
  TOUCH(Rules_RegisterDeftemplateBinaryItem());
}

TEST(cov20_rules, register_defrule_binary_item) {
  TOUCH(Rules_RegisterDefruleBinaryItem());
}

TEST(cov20_rules, register_defglobal_binary_item) {
  TOUCH(Rules_RegisterDefglobalBinaryItem());
}

TEST(cov20_rules, register_rule_commands) {
  TOUCH(Rules_RegisterRuleCommands());
}

TEST(cov20_rules, register_modify_duplicate_functions) {
  TOUCH(Rules_RegisterModifyDuplicateFunctions());
}

TEST(cov20_defgeneric, register_binary_item) {
  TOUCH(Defgeneric_RegisterBinaryItem());
}

TEST(cov20_deffunction, register_binary_item) {
  TOUCH(Deffunction_RegisterBinaryItem());
}

TEST(cov20_class, register_binary_item) {
  TOUCH(Class_RegisterBinaryItem());
}

TEST(cov20_module, register_defmodule_commands) {
  TOUCH(Module_RegisterDefmoduleCommands());
}

TEST(cov20_parser, register_procedural_function_parsers) {
  TOUCH(Parser_RegisterProceduralFunctionParsers());
}

/* ---- Rules_BsavePackSharedRecordHeader: pure bit-twiddling on caller
 * buffers, no calls out; fully safe. ---- */

TEST(cov20_rules, bsave_pack_shared_record_header_v3_nonzero) {
  _DWORD result[16], a2[16], sub[16];
  memset(result, 0, sizeof result);
  memset(a2, 0, sizeof a2);
  memset(sub, 0, sizeof sub);
  sub[1] = 0x1234;          /* *(v3+4) */
  a2[2] = (int)(intptr_t)sub;  /* v3 = *(a2+8) nonzero */
  a2[3] = 0x7;               /* bits for the OR sequence */
  TOUCH(Rules_BsavePackSharedRecordHeader((int)(intptr_t)result,
                                          (int)(intptr_t)a2));
}

TEST(cov20_rules, bsave_pack_shared_record_header_v3_zero) {
  _DWORD result[16], a2[16];
  memset(result, 0, sizeof result);
  memset(a2, 0, sizeof a2);
  a2[2] = 0;                /* v3 == 0 branch: v4 = -1 */
  a2[3] = 0;
  TOUCH(Rules_BsavePackSharedRecordHeader((int)(intptr_t)result,
                                          (int)(intptr_t)a2));
}

/* ---- Parser_CollectFunctionArguments / Parser_ParseArgument: drives the
 * lexer with an unregistered logical-name channel so Lexer_PeekChar hits the
 * "unrecognized router" fast path (dword_51A604 == 0 by default) rather than
 * blocking on real IO; this makes Parser_NextToken return EOF quickly. ---- */

TEST(cov20_parser, collect_function_arguments) {
  _DWORD a1buf[64];
  memset(a1buf, 0, sizeof a1buf);
  /* nonzero channel distinct from the default-zero stream globals so
   * Lexer_PeekChar takes its safe "no router" branch instead of the
   * buffered-stream branch that would deref a NULL global. */
  TOUCH(Parser_CollectFunctionArguments((int)(intptr_t)a1buf, 424242, 0));
}

/* ---- Rules_MatchesCommand: forces Rules_RtnArgCount() (which normally
 * derefs the NULL-by-default global dword_51A960+6) to see a valid, empty
 * argument list instead of crashing immediately, by pointing that global at
 * a zeroed local buffer for the duration of the call. ---- */

TEST(cov20_rules, matches_command) {
  static _DWORD fake_expr[32];
  int saved = g_ClipsCurrentExpression;
  memset(fake_expr, 0, sizeof fake_expr);
  g_ClipsCurrentExpression = (int)(intptr_t)fake_expr;
  TOUCH(Rules_MatchesCommand(424242, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_ParseDefruleRHS: with no lexer input registered, the nested
 * Parser_ParseProgram call reaches EOF immediately and returns 0, so this
 * exercises the "early return" path safely. ---- */

TEST(cov20_rules, parse_defrule_rhs) {
  _DWORD a1buf[64];
  memset(a1buf, 0, sizeof a1buf);
  TOUCH(Rules_ParseDefruleRHS((int)(intptr_t)a1buf));
}

/* ---- Rules_PrepareDefrulesForCodeGen: forwards to
 * Rules_JoinNetworkAssignCodeGenIds with real stack-backed out params. ---- */

TEST(cov20_rules, prepare_defrules_for_codegen) {
  TOUCH(Rules_PrepareDefrulesForCodeGen());
}

/* ---- Rules_{Deftemplate,Defrule}CodeGenCloseFiles /
 * Rules_CloseDefruleCodeFiles: each "handle" arg is forwarded (as a fake
 * FILE*-ish token) to Rules_ConstructCodeFileClose, which isn't in this
 * batch; put every distinct branch in its own TEST so a crash in one handle
 * branch can't suppress coverage of the others. ---- */

TEST(cov20_rules, deftemplate_codegen_close_files_all_zero) {
  CHECK_EQ(Rules_DeftemplateCodeGenCloseFiles(0, 0, 5, 0), 0);
}

TEST(cov20_rules, deftemplate_codegen_close_files_a4) {
  TOUCH(Rules_DeftemplateCodeGenCloseFiles(0, 0, 5, 1));
}

TEST(cov20_rules, deftemplate_codegen_close_files_a2) {
  TOUCH(Rules_DeftemplateCodeGenCloseFiles(0, 1, 5, 0));
}

TEST(cov20_rules, deftemplate_codegen_close_files_a1) {
  TOUCH(Rules_DeftemplateCodeGenCloseFiles(1, 0, 5, 0));
}

TEST(cov20_rules, close_defrule_code_files_all_zero) {
  CHECK_EQ(Rules_CloseDefruleCodeFiles(0, 0, 5, 0), 0);
}

TEST(cov20_rules, close_defrule_code_files_a4) {
  TOUCH(Rules_CloseDefruleCodeFiles(0, 0, 5, 1));
}

TEST(cov20_rules, close_defrule_code_files_a2) {
  TOUCH(Rules_CloseDefruleCodeFiles(0, 1, 5, 0));
}

TEST(cov20_rules, close_defrule_code_files_a1) {
  TOUCH(Rules_CloseDefruleCodeFiles(1, 0, 5, 0));
}

/* ---- Rules_SetLHSParseNodeDefaultFlags / Rules_SetLHSParseNodeExtendedFlags:
 * pure bit-twiddling on the caller's buffer; fully safe both ways. ---- */

TEST(cov20_rules, set_lhs_parse_node_default_flags_a2_true) {
  _BYTE buf[16];
  memset(buf, 0, sizeof buf);
  TOUCH(Rules_SetLHSParseNodeDefaultFlags(buf, 1));
}

TEST(cov20_rules, set_lhs_parse_node_default_flags_a2_false) {
  _BYTE buf[16];
  memset(buf, 0xFF, sizeof buf);
  TOUCH(Rules_SetLHSParseNodeDefaultFlags(buf, 0));
}

TEST(cov20_rules, set_lhs_parse_node_extended_flags_a2_true) {
  _DWORD buf[8];
  memset(buf, 0, sizeof buf);
  TOUCH(Rules_SetLHSParseNodeExtendedFlags((int)(intptr_t)buf, 1));
}

TEST(cov20_rules, set_lhs_parse_node_extended_flags_a2_false) {
  _DWORD buf[8];
  memset(buf, 0xFF, sizeof buf);
  TOUCH(Rules_SetLHSParseNodeExtendedFlags((int)(intptr_t)buf, 0));
}

/* ---- Rules_ApplyPatternKeywordFlags: takes no arguments and switches on an
 * uninitialized local ('v2' in the recovered source); it also calls
 * Rules_CreateLHSParseNode(), which itself dereferences another uninitialized
 * local, so this is essentially guaranteed to crash partway through. Still
 * worth calling (isolated) for whatever partial coverage is reachable before
 * that. ---- */

TEST(cov20_rules, apply_pattern_keyword_flags) {
  TOUCH(Rules_ApplyPatternKeywordFlags());
}

/* ---- Module_SaveAllPPFormsToFile / Module_PrintAllNamesWithTally: drive the
 * module enumeration loop by pointing the module-list-head global directly
 * at a fabricated node (both are ordinary globals in this TU, so we can set
 * them directly instead of needing a real defmodule construct). ---- */

TEST(cov20_module, save_all_pp_forms_to_file_empty_list) {
  int saved = g_DefmoduleListHead;
  g_DefmoduleListHead = 0;
  TOUCH(Module_SaveAllPPFormsToFile((signed int)(intptr_t)"werror"));
  g_DefmoduleListHead = saved;
}

TEST(cov20_module, save_all_pp_forms_to_file_one_node) {
  static _DWORD module_node[32];
  static const char *pp_form = "(defmodule FAKE)";
  int saved = g_DefmoduleListHead;
  memset(module_node, 0, sizeof module_node);
  module_node[1] = (int)(intptr_t)pp_form; /* Module_GetPPForm -> offset 4 */
  module_node[7] = 0;                      /* next == 0: one iteration */
  g_DefmoduleListHead = (int)(intptr_t)module_node;
  TOUCH(Module_SaveAllPPFormsToFile((signed int)(intptr_t)"werror"));
  g_DefmoduleListHead = saved;
}

TEST(cov20_module, print_all_names_with_tally_empty_list) {
  int saved = g_DefmoduleListHead;
  g_DefmoduleListHead = 0;
  TOUCH(Module_PrintAllNamesWithTally((int)(intptr_t)"werror"));
  g_DefmoduleListHead = saved;
}

TEST(cov20_module, print_all_names_with_tally_one_node) {
  static _DWORD sym_entry[8];
  static _DWORD module_node[32];
  static const char *name = "FakeModule";
  int saved = g_DefmoduleListHead;
  memset(sym_entry, 0, sizeof sym_entry);
  memset(module_node, 0, sizeof module_node);
  sym_entry[4] = (int)(intptr_t)name;      /* Module_GetName reads +16 off *a1 */
  module_node[0] = (int)(intptr_t)sym_entry;
  module_node[7] = 0;
  g_DefmoduleListHead = (int)(intptr_t)module_node;
  TOUCH(Module_PrintAllNamesWithTally((int)(intptr_t)"werror"));
  g_DefmoduleListHead = saved;
}

/* ---- Module_PrintPPFormByName: without a registered symbol table entry,
 * Module_FindByName(a1) returns NULL, so this safely exercises the
 * "not found" branch. ---- */

TEST(cov20_module, print_pp_form_by_name_not_found) {
  CHECK_EQ(Module_PrintPPFormByName((_BYTE *)"NoSuchModule",
                                    (signed int)(intptr_t)"werror"),
           0);
}

/* ---- Rules_FindTemplateForFactAddress: pure pointer-chasing over
 * caller-built nodes; fully safe. ---- */

TEST(cov20_rules, find_template_for_fact_address_null_a2) {
  CHECK_EQ(Rules_FindTemplateForFactAddress(1, 0), 0);
}

TEST(cov20_rules, find_template_for_fact_address_mismatch_then_zero) {
  _DWORD node[32];
  memset(node, 0, sizeof node);
  node[1] = 999;  /* offset 4: does not match a1 */
  node[17] = 0;   /* offset 68: next == 0 -> LABEL_4, v2 stays 0 */
  CHECK_EQ(Rules_FindTemplateForFactAddress(1, (int)(intptr_t)node), 0);
}

TEST(cov20_rules, find_template_for_fact_address_v3_wrong_tag) {
  _DWORD node[32], v3buf[32];
  memset(node, 0, sizeof node);
  memset(v3buf, 0, sizeof v3buf);
  node[1] = 1;              /* matches a1 immediately */
  v3buf[0] = 5;              /* *v3 != 17 */
  node[16] = (int)(intptr_t)v3buf; /* offset 64 */
  CHECK_EQ(Rules_FindTemplateForFactAddress(1, (int)(intptr_t)node), 0);
}

TEST(cov20_rules, find_template_for_fact_address_full_chain) {
  _DWORD nodeC[32], nodeD[32], v3buf[32], v4buf[32];
  memset(nodeC, 0, sizeof nodeC);
  memset(nodeD, 0, sizeof nodeD);
  memset(v3buf, 0, sizeof v3buf);
  memset(v4buf, 0, sizeof v4buf);

  v4buf[0] = 2;    /* *v4 == 2 */
  v4buf[1] = 777;  /* return value v4[1] */
  v4buf[16] = 0;   /* !v4[16] */
  v4buf[17] = 0;   /* !v4[17] */

  v3buf[0] = 17;                       /* *v3 == 17 */
  v3buf[17] = (int)(intptr_t)v4buf;    /* v3[17] -> v4 */

  nodeD[1] = 1;                          /* matches a1 == 1 */
  nodeD[16] = (int)(intptr_t)v3buf;      /* offset 64 */

  nodeC[1] = 999;                         /* mismatch on first loop check */
  nodeC[17] = (int)(intptr_t)nodeD;       /* offset 68 -> next node */

  CHECK_EQ(Rules_FindTemplateForFactAddress(1, (int)(intptr_t)nodeC), 777);
}

TEST(cov20_rules, parse_modify) {
  TOUCH(Rules_ParseModify(0, 0));
}

TEST(cov20_rules, parse_duplicate) {
  TOUCH(Rules_ParseDuplicate(0, 0));
}

TEST(cov20_rules, modify_command) {
  TOUCH(Rules_ModifyCommand(424242, 0.0));
}

TEST(cov20_rules, duplicate_command) {
  TOUCH(Rules_DuplicateCommand(424242, 0.0));
}
