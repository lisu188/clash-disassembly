/* cov3 batch 06: second-pass-of-second-pass coverage lift for a grab-bag of
 * partially covered functions (see scratchpad cov3_batches/cov3_06.json):
 * Rules_MathPow/Rules_MathAcsch (two-arg / one-arg numeric parsing),
 * Rules_BsaveSymbolTable, Rules_RestFunction, Rules_ExpressionConstraints-
 * Compatible, Instance_FindByName, Rules_LoadCommand/Rules_BatchStarCommand
 * (file-arg command wrappers), WorldMap_Initialize, Compiler_Generate-
 * ConstructTables, Defgeneric_CloseCodeFiles/Deffacts_CloseCodeFiles,
 * Rules_CheckFactExistp, MainMenu_RequestLoadGameMenu, Rules_RefreshCommand,
 * and Rules_ParseStandardConstraintAttribute.
 *
 * ---- Shared "successful argument parse" technique (see also
 * tests/unit/cases/test_cov2_02.c, which this reuses/extends) ----
 * Lexer_ParseValueList(pos, out, wanted_type, a4) calls Rules_RtnUnknown(pos,
 * out, a4), which walks a singly linked "argument node" chain rooted at
 * dword_51A960+6 (next pointers live at node+10) to the pos'th node, then
 * calls Parser_ParseForm(node, out, (int)out, a4). For scalar tags in
 * {0,1,2,3,5,7,8} Parser_ParseForm takes its LABEL_4 fast path: out[1] =
 * *(short*)node (the tag); out[2] = *(int*)(node+2) (a pointer whose own +16
 * offset holds the actual scalar payload). For tag==4 (MULTIFIELD),
 * Parser_ParseForm instead copies out[2..4] from *(int*)(node+2)+{8,12,16}. */
static void cov3_06_arg1(unsigned char *anchor, unsigned char *node, short tag,
                          void *valptr) {
  memset(anchor, 0, 32);
  memset(node, 0, 32);
  *(short *)node = tag;
  *(int *)(node + 2) = (int)(intptr_t)valptr;
  *(int *)(node + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

static void cov3_06_arg2(unsigned char *anchor, unsigned char *node1,
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

#define COV3_06_SAVE_ARGCTX()                                                \
  int cov3_06_saved960 = g_ClipsCurrentExpression;                                       \
  int cov3_06_saved964 = g_ClipsEvaluationError;                                       \
  int cov3_06_saved968 = g_ClipsHaltExecution;                                       \
  g_ClipsEvaluationError = 0;                                                          \
  g_ClipsHaltExecution = 0

#define COV3_06_RESTORE_ARGCTX()                                             \
  do {                                                                       \
    g_ClipsCurrentExpression = cov3_06_saved960;                                         \
    g_ClipsEvaluationError = cov3_06_saved964;                                         \
    g_ClipsHaltExecution = cov3_06_saved968;                                         \
  } while (0)

/* ---- Rules_MathPow: both Lexer_ParseValueList calls request wanted_type==0
 * (FLOAT). With an INTEGER-tagged (1) arg node, Lexer_ParseValueList's
 * "a2[1]==1 && !a3" guard deterministically enters the int->float coercion
 * branch (no dependence on the decompiler-lost fast-path register); whether
 * the subsequent garbage-return propagates as "success" back up through
 * Rules_MathPow is not fully controllable from C, but entering the coercion
 * branch itself is deterministic and reaches further than the always-empty
 * chain pass one used, at zero risk (Rules_AddDoubleValue is a normal
 * arena-backed allocator once bootstrapped). ---- */
TEST(cov3_06_mathpow, int_arg_coercion_attempt) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV3_06_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  val1[4] = 3;
  val2[4] = 2;
  cov3_06_arg2(anchor, node1, 1, val1, node2, 1, val2);
  TOUCH(Rules_MathPow(0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- Rules_MathAcsch: Rules_MathParseSingleArg funnels through the same
 * Lexer_ParseValueList(1, ..., 0, a3) shape as Rules_MathPow's calls; same
 * int->float coercion attempt. ---- */
TEST(cov3_06_mathacsch, int_arg_coercion_attempt) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV3_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 5;
  cov3_06_arg1(anchor, node, 1, val);
  TOUCH(Rules_MathAcsch(0, 0, 0, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- Rules_BsaveSymbolTable: both loops walk every bucket of the symbol
 * table rooted at Rules_GetSymbolTable() (== dword_54DD50), but pass one's
 * default (post-bootstrap, no extra interned symbols with the "needed in
 * bsave image" bit set) run never took either loop's if-body. Manually
 * flagging one freshly interned symbol's flags byte (offset 12, bit 0x2)
 * makes both loops' conditional bodies execute (count/length accumulation in
 * the first pass, the actual Rules_BsaveWriteBlock call in the second).
 * Passing a1==0 keeps every Rules_BsaveWriteBlock call a safe no-op: its
 * fwrite_ wrapper returns immediately when the file_handle argument is 0. */
TEST(cov3_06_bsavesymtbl, one_flagged_symbol) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static char symname[] = "cov3_06_bsave_flagged_symbol";
  signed int *sym = Str_Intern(symname, 0);
  if (sym) {
    ((unsigned char *)sym)[12] |= 2;
  }
  TOUCH(Rules_BsaveSymbolTable(0));
}

/* ---- Rules_RestFunction: same shape as Rules_FirstFunction (see
 * test_cov2_02.c's multifield_success_* tests) -- a MULTIFIELD-tagged (4)
 * one-node chain makes Parser_ParseForm's case-4 handler copy the multifield
 * descriptor's three fields (+8/+12/+16) into the out array, letting us reach
 * both sides of the final "pick a bound" if/else that pass one's always-
 * failing empty chain could never enter. mfdesc is filled with the repeating
 * byte 0x01 first (not left zeroed) so Rules_PropagateReturnValueDepth's
 * slot-walk over mfdesc+32.. hits only the safe "default" arm for every
 * micro-slot (tag 0x0101 is not one of the switch's handled tags). */
TEST(cov3_06_restfn, multifield_if_branch) {
  static unsigned char anchor[32], node[32], mfdesc[128];
  static _DWORD out[8];
  COV3_06_SAVE_ARGCTX();
  memset(mfdesc, 0x01, sizeof mfdesc);
  *(int *)(mfdesc + 8) = (int)(intptr_t)mfdesc; /* self-pointer: readable */
  *(int *)(mfdesc + 12) = 7;  /* v8 */
  *(int *)(mfdesc + 16) = 3;  /* v9 < v8+... -> v8+1 > v9+1 branch */
  cov3_06_arg1(anchor, node, 4, mfdesc);
  memset(out, 0, sizeof out);
  TOUCH(Rules_RestFunction(out, 2, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

TEST(cov3_06_restfn, multifield_else_branch) {
  static unsigned char anchor[32], node[32], mfdesc[128];
  static _DWORD out[8];
  COV3_06_SAVE_ARGCTX();
  memset(mfdesc, 0x01, sizeof mfdesc);
  *(int *)(mfdesc + 8) = (int)(intptr_t)mfdesc;
  *(int *)(mfdesc + 12) = 3;  /* v8 */
  *(int *)(mfdesc + 16) = 7;  /* v9 -> v8+1 <= v9+1 -> else branch */
  cov3_06_arg1(anchor, node, 4, mfdesc);
  memset(out, 0, sizeof out);
  TOUCH(Rules_RestFunction(out, 2, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- Rules_ExpressionConstraintsCompatible: Rules_BuildLHSNodeFromToken's
 * "*a1 in {11..16 minus 10}" fast path (tag 15 chosen) is the only branch that
 * avoids dereferencing a decompiler-lost pointer, and just allocates+tags a
 * fresh LHS parse node via the (bootstrapped) reserve arena. That reaches
 * every remaining straight-line call in the target function (Rules_Apply-
 * PatternKeywordFlags, Rules_IntersectConstraints, both AST_DecrementNode-
 * RefCount calls) before the final branch, whose outcome depends on
 * unrecoverable decompiler state and isn't chased further. */
TEST(cov3_06_exprconstraint, build_and_intersect) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static __int16 token[4];
  token[0] = 15;
  TOUCH(Rules_ExpressionConstraintsCompatible(token));
}

/* ---- Instance_FindByName: pass one's default plain name covers the
 * qualifier_length==0 branch. A name that is exactly "::" makes
 * Rules_FindModuleSeparator return 1 (two leading colons), taking the
 * qualifier_length==1 branch; feeding that same "::" string on into
 * Rules_ExtractConstructName(1, "::", 1) hits its own "strlen(a2) <= a1+1"
 * (2 <= 2) fast return-0 guard, safely avoiding its otherwise decompiler-
 * lost-variable-driven Mem_SmallBlockAlloc/strncpy_ path, and still reaches
 * Instance_FindByName's own "return Instance_LookupInHashBucket(...)" line.
 * A "MOD::thing" name additionally drives the qualifier_length>1 branch
 * (module-qualified lookup) at least as far as the Rules_ExtractModuleName
 * call line, on a best-effort basis. */
TEST(cov3_06_instfindbyname, qualifier_one_fast_return) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static _DWORD obj[8];
  static char name[] = "::";
  memset(obj, 0, sizeof obj);
  obj[4] = (_DWORD)(intptr_t)name; /* offset 16: name pointer */
  TOUCH(Instance_FindByName((int)(intptr_t)obj));
}

TEST(cov3_06_instfindbyname, qualifier_many_module_lookup) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  static _DWORD obj[8];
  static char name[] = "MOD::thing";
  memset(obj, 0, sizeof obj);
  obj[4] = (_DWORD)(intptr_t)name;
  TOUCH(Instance_FindByName((int)(intptr_t)obj));
}

/* ---- Rules_LoadCommand / Rules_BatchStarCommand: both funnel through
 * Lexer_TokenExpect(1) -> Rules_GetFileNameArg(1, ..., a2), whose success
 * path only reads back *(v7+16) (the filename pointer) regardless of the
 * decompiler-lost middle argument -- an established-safe pattern (see
 * test_cov2_02.c's Rules_HostRemoveFile/Rules_ParseLoadFactsCommand tests).
 * Feeding a nonexistent path makes the downstream Rules_Load/Rules_BatchStar
 * IO_FOpen call fail cleanly (result 0) without ever touching either
 * function's own decompiler-lost success-path variables, landing on the
 * "open failed" report branch instead of pass one's immediate TokenExpect-
 * mismatch return. ---- */
TEST(cov3_06_loadcommand, filename_parsed_open_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov3_06_missing_load.clp";
  COV3_06_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)path;
  cov3_06_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_LoadCommand(0, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

TEST(cov3_06_batchstarcmd, filename_parsed_open_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov3_06_missing_batch.clp";
  COV3_06_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)path;
  cov3_06_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_BatchStarCommand(0, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- WorldMap_Initialize: unconditional straight-line sequence; simply
 * never invoked in earlier passes (0 covered). Safe to call cold per the
 * fork/alarm isolation even if resource loading misbehaves without a real
 * game asset directory. ---- */
TEST(cov3_06_worldmap, initialize_once) {
  TOUCH(WorldMap_Initialize(0, 0));
}

/* ---- Compiler_GenerateConstructTables: a straight-line chain of six
 * Compiler_Write*File calls threaded entirely through decompiler-lost
 * variables (the "filename" fed to the first call is whatever raw value
 * Rules_SetAtomicValueIndices(1) happens to leave in eax, wholly independent
 * of this function's own DWORD argument), so no input we choose can change
 * which lines execute before the first internal fopen-on-garbage-pointer
 * likely aborts the chain. Called once on a best-effort basis; still reaches
 * its own first two lines even if every downstream Write*File call crashes
 * immediately. ---- */
TEST(cov3_06_compilertables, generate_once) {
  TOUCH(Compiler_GenerateConstructTables(0));
}

/* ---- Defgeneric_CloseCodeFiles: a fixed 5-iteration do-while loop over
 * a1[0..4] (file "handles") / a2[0..4] (walked purely as a bookkeeping
 * pointer, dereferenced only to zero it out each iteration). Giving every
 * a1[] slot a nonzero value makes Rules_ConstructCodeFileClose's inner
 * "if (!result)" branch (the one that dereferences the outer accumulator as
 * a real construct-descriptor pointer) always false, so the whole loop just
 * runs the safe Output_WriteFormatted/fclose_/bookkeeping tail each time --
 * exercising every line of the 5-iteration loop body without needing a real
 * descriptor array for the outer a4 argument. ---- */
TEST(cov3_06_defgenclose, five_iteration_loop) {
  static int handles[8];
  static _DWORD walk[16];
  int i;
  for (i = 0; i < 8; ++i) handles[i] = 1;
  memset(walk, 0, sizeof walk);
  TOUCH(Defgeneric_CloseCodeFiles(handles, walk, 0, 0));
}

/* ---- Deffacts_CloseCodeFiles: pure-int-argument variant of the same
 * Rules_ConstructCodeFileClose wrapper shape, called with a5==0 so its
 * "if (a5) *a5 = 0;" guard is skipped entirely and, with a nonzero handle,
 * its "if (!result)" branch is likewise skipped -- safe regardless of the
 * handle's actual value. Two shapes: (a1 nonzero, a2 zero) reaches the
 * second call via the plain "if (a1)" entry (not the goto); (both nonzero)
 * reaches it via the "goto LABEL_5" fallthrough after the first call. ---- */
TEST(cov3_06_deffactsclose, only_a1_direct_entry) {
  TOUCH(Deffacts_CloseCodeFiles(5, 0, 0, 0));
}

TEST(cov3_06_deffactsclose, both_nonzero_goto_fallthrough) {
  TOUCH(Deffacts_CloseCodeFiles(7, 9, 0, 0));
}

/* ---- Rules_CheckFactExistp: Lexer_TokenExpect(1) success (one-node chain)
 * then Rules_ResolveFactArgument's "tag==1 (INTEGER) && value>=0" branch
 * (itself decompiler-lost-variable-free for this tag) calls the always-safe
 * Rules_FindFactByIndex (no facts registered -> returns 0 cleanly), so
 * Rules_CheckFactStillAsserted(0) takes its own "!result" fast return --
 * exercising every remaining line in the target function. ---- */
TEST(cov3_06_checkfactexistp, integer_arg_resolved) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV3_06_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 5;
  cov3_06_arg1(anchor, node, 1, val);
  TOUCH(Rules_CheckFactExistp(0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- MainMenu_RequestLoadGameMenu: straight-line sequence, never invoked in
 * earlier passes (2/5 covered -- likely just the guard before a crash inside
 * UIWidget_PlayPressedReleaseAnimation on a bad/absent widget). A zeroed
 * widget-sized static buffer makes its "*(a1+49)" check false (skip the audio
 * call) and lets the rest of the wrapper run to completion. ---- */
TEST(cov3_06_mainmenu, request_load_game_menu) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  TOUCH(MainMenu_RequestLoadGameMenu((uintptr_t)(intptr_t)widget));
}

/* ---- Rules_RefreshCommand: repeat the "name parsed, rule not found" shape
 * (test_cov2_02.c already established this exact pattern) on a fresh call
 * site; the remaining "rule found" success branch needs a real registered
 * defrule (full construct-class function-pointer table), out of reach
 * without standing up much more of the rules engine. ---- */
TEST(cov3_06_refreshcmd, name_parsed_rule_not_found) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static char name[] = "cov3-06-missing-rule";
  COV3_06_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (_DWORD)(intptr_t)name;
  cov3_06_arg1(anchor, node, 2, valnode);
  TOUCH(Rules_RefreshCommand(0, 0.0));
  COV3_06_RESTORE_ARGCTX();
}

/* ---- Rules_ParseStandardConstraintAttribute: test_cov23.c/test_cov2_07.c
 * already drove the "already parsed" branch, the aType_0 branch, and the
 * aCardinality/aAllowedSymbols members of the two OR-chains. Since those are
 * short-circuiting "||" chains fed by decompiler-lost registers (but which
 * so far have behaved as if each successive strcmp_ call really does compare
 * against the *same* real attribute-name argument), driving every other
 * named attribute gives the remaining chain members every chance to be
 * reached, plus one unmatched name that should skip the whole if/elseif nest
 * and fall straight to the shared MarkConstraintAttributeParsed+return
 * tail. ---- */
TEST(cov3_06_parsestdattr, remaining_named_attributes) {
  char a1buf[256];
  _DWORD a3buf[64];

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedStrings,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedLexemes,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedInteg_0,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedFloats,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedNumbers,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedInstanc,
                                                (_BYTE *)a3buf, 0, 0));

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, aAllowedValues,
                                                (_BYTE *)a3buf, 0, 0));
}

TEST(cov3_06_parsestdattr, unmatched_name_tail) {
  char a1buf[256];
  _DWORD a3buf[64];
  static const char unmatched[] = "cov3-06-unmatched-attribute-name";

  memset(a1buf, 0, sizeof(a1buf));
  memset(a3buf, 0, sizeof(a3buf));
  TOUCH(Rules_ParseStandardConstraintAttribute(a1buf, unmatched,
                                                (_BYTE *)a3buf, 0, 0));
}
