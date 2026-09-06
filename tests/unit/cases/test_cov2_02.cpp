/* cov2 batch 02: second-pass coverage lift for a grab-bag of partially
 * covered functions (see scratchpad cov2_batches/cov2_02.json): Rules_
 * arithmetic/arg-parsing host functions that funnel through
 * Lexer_ParseValueList/Rules_RtnUnknown, a couple of Defgeneric/Class/
 * Instance helpers, small render/list/string-holder utilities, and a
 * handful of trivial one-liners that were simply never called in pass one.
 *
 * ---- Shared "successful argument parse" technique ----
 * Lexer_ParseValueList(pos, out, wanted_type, a4) calls Rules_RtnUnknown(pos,
 * out, a4), which walks a singly linked "argument node" chain rooted at
 * dword_51A960+6 (next pointers live at node+10) to the pos'th node, then
 * calls Parser_ParseForm(node, out, (int)out, a4). For scalar tags in
 * {0,1,2,3,5,7,8} Parser_ParseForm takes its LABEL_4 fast path:
 * out[1] = *(short*)node (the tag); out[2] = *(int*)(node+2) (a pointer whose
 * own +16 offset holds the actual scalar payload). Lexer_ParseValueList then
 * reports success when wanted_type == out[1] (exact tag match) or a couple of
 * documented "or" cases (110 accepts tag<2, etc). For tag==4 (MULTIFIELD),
 * Parser_ParseForm instead copies out[2..4] from *(int*)(node+2)+{8,12,16}.
 * This is the exact technique tests/unit/cases/test_cov11.c already uses for
 * Rules_GetFileNameArg/Rules_GetConstructNameArg ("anchor"/"termBuf"); the two
 * helpers below just generalize it to one- and two-argument chains so this
 * file can drive the *success* paths of several more Lexer_ParseValueList
 * consumers that pass-one only exercised via the always-fails empty chain. */

static void cov2_02_arg1(unsigned char *anchor, unsigned char *node, short tag,
                          void *valptr) {
  memset(anchor, 0, 32);
  memset(node, 0, 32);
  *(short *)node = tag;
  *(int *)(node + 2) = (int)(intptr_t)valptr;
  *(int *)(node + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
}

static void cov2_02_arg2(unsigned char *anchor, unsigned char *node1,
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

#define COV2_02_SAVE_ARGCTX()                                                \
  int cov2_02_saved960 = g_ClipsCurrentExpression;                                       \
  int cov2_02_saved964 = g_ClipsEvaluationError;                                       \
  int cov2_02_saved968 = g_ClipsHaltExecution;                                       \
  g_ClipsEvaluationError = 0;                                                          \
  g_ClipsHaltExecution = 0

#define COV2_02_RESTORE_ARGCTX()                                             \
  do {                                                                       \
    g_ClipsCurrentExpression = cov2_02_saved960;                                         \
    g_ClipsEvaluationError = cov2_02_saved964;                                         \
    g_ClipsHaltExecution = cov2_02_saved968;                                         \
  } while (0)

/* ---- Rules_MathMod: two-argument numeric parse. First pass only reached
 * the "Lexer_TokenExpect(2)==-1 -> LABEL_20" failure path. Driving a real
 * two-node chain reaches Lexer_TokenExpect's success branch and then every
 * arithmetic sub-branch: the divide-by-zero report, the both-integer modulo
 * path, and both the floor (positive quotient) and ceil (negative quotient)
 * float paths. ---- */
/* Each "val" buffer below is a full 8-element _DWORD array (32 bytes), not a
 * bare scalar: Parser_ParseForm's scalar fast path hands the raw valptr
 * straight to Rules_ClampEvaluationDepth as its own "a2", which unconditionally
 * touches a2[2] (byte offset 8) as part of its depth-clamping bookkeeping,
 * *before* the outer host function ever reads the real payload back out of
 * byte offset 16. A single int/double would make that offset-8 touch (and,
 * for the outer function's own offset-16 read) walk off the end of the
 * object. */
TEST(cov2_02_mathmod, integer_modulo) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV2_02_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  val1[4] = 7;
  val2[4] = 3;
  cov2_02_arg2(anchor, node1, 1, val1, node2, 1, val2);
  static _DWORD out[4];
  memset(out, 0, sizeof out);
  TOUCH(Rules_MathMod((int)(intptr_t)out, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

TEST(cov2_02_mathmod, float_positive_quotient_floor) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV2_02_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  *(double *)((char *)val1 + 16) = 7.5;
  *(double *)((char *)val2 + 16) = 2.5;
  cov2_02_arg2(anchor, node1, 0, val1, node2, 0, val2);
  static _DWORD out[4];
  memset(out, 0, sizeof out);
  TOUCH(Rules_MathMod((int)(intptr_t)out, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

TEST(cov2_02_mathmod, float_negative_quotient_ceil) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV2_02_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  *(double *)((char *)val1 + 16) = -7.5;
  *(double *)((char *)val2 + 16) = 2.5;
  cov2_02_arg2(anchor, node1, 0, val1, node2, 0, val2);
  static _DWORD out[4];
  memset(out, 0, sizeof out);
  TOUCH(Rules_MathMod((int)(intptr_t)out, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

TEST(cov2_02_mathmod, divide_by_zero) {
  static unsigned char anchor[32], node1[32], node2[32];
  static _DWORD val1[8], val2[8];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  COV2_02_SAVE_ARGCTX();
  memset(val1, 0, sizeof val1);
  memset(val2, 0, sizeof val2);
  val1[4] = 5;
  val2[4] = 0;
  cov2_02_arg2(anchor, node1, 1, val1, node2, 1, val2);
  static _DWORD out[4];
  memset(out, 0, sizeof out);
  TOUCH(Rules_MathMod((int)(intptr_t)out, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_FirstFunction: pass one only drove the "no arg" failure branch
 * (Rules_SetMultifieldErrorValue). A one-node MULTIFIELD-tagged chain makes
 * Parser_ParseForm's case-4 handler copy three fields (from the pointed-to
 * "multifield descriptor" +8/+12/+16) into the out array, letting us reach
 * both sides of the final "pick the smaller bound" if/else. ---- */
/* mfdesc is deliberately filled with the repeating byte 0x01 (rather than
 * left zeroed) *before* poking the three real fields at +8/+12/+16: the
 * multifield success path runs through Rules_PropagateReturnValueDepth,
 * which -- when a2[3] ("v8") <= a2[4] ("v9") -- walks a packed array of
 * {short tag; int valueptr;} micro-slots starting at mfdesc+32 and feeds
 * each one to Rules_ClampEvaluationDepth(tag, valueptr). 0x0101 (=257) is
 * not one of that switch's handled tags (0,1,2,3,6,7,8), so every slot hits
 * the safe "default: return result;" arm without ever dereferencing the
 * (garbage) valueptr. A zeroed buffer would instead read tag 0 and crash
 * dereferencing a null valueptr. */
TEST(cov2_02_firstfn, multifield_success_then_branch) {
  static unsigned char anchor[32], node[32], mfdesc[128];
  COV2_02_SAVE_ARGCTX();
  memset(mfdesc, 0x01, sizeof mfdesc);
  *(int *)(mfdesc + 8) = (int)(intptr_t)mfdesc; /* self-pointer: readable */
  *(int *)(mfdesc + 12) = 7; /* v8 */
  *(int *)(mfdesc + 16) = 3; /* v9 < v8 -> else branch (a1[4]=v9), loop skipped */
  cov2_02_arg1(anchor, node, 4, mfdesc);
  static _DWORD out[8];
  memset(out, 0, sizeof out);
  TOUCH(Rules_FirstFunction(out, 2, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

TEST(cov2_02_firstfn, multifield_success_if_branch) {
  static unsigned char anchor[32], node[32], mfdesc[128];
  COV2_02_SAVE_ARGCTX();
  memset(mfdesc, 0x01, sizeof mfdesc);
  *(int *)(mfdesc + 8) = (int)(intptr_t)mfdesc; /* self-pointer: readable */
  *(int *)(mfdesc + 12) = 3; /* v8 */
  *(int *)(mfdesc + 16) = 7; /* v9 >= v8 -> if branch (a1[4]=v8); loop runs
                                 over the safe 0x0101-tagged slots above */
  cov2_02_arg1(anchor, node, 4, mfdesc);
  static _DWORD out[8];
  memset(out, 0, sizeof out);
  TOUCH(Rules_FirstFunction(out, 2, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_ParsePositiveIntArg: a1>a2 short-circuit, a successful positive
 * parse, and the negative-value error-report branch. ---- */
TEST(cov2_02_posintarg, position_out_of_range) {
  CHECK_EQ(Rules_ParsePositiveIntArg(2, 1, 3, 0.0), -1);
}

TEST(cov2_02_posintarg, positive_value_success) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV2_02_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = 5;
  cov2_02_arg1(anchor, node, 1, val);
  CHECK_EQ(Rules_ParsePositiveIntArg(1, 1, 3, 0.0), 5);
  COV2_02_RESTORE_ARGCTX();
}

TEST(cov2_02_posintarg, negative_value_reports_error) {
  static unsigned char anchor[32], node[32];
  static _DWORD val[8];
  COV2_02_SAVE_ARGCTX();
  memset(val, 0, sizeof val);
  val[4] = (_DWORD)-9;
  cov2_02_arg1(anchor, node, 1, val);
  CHECK_EQ(Rules_ParsePositiveIntArg(1, 1, 3, 0.0), -2);
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_CheckLiteralSlotValueConstraint: enabling the static-constraint
 * flag and driving a one-node "constant type" field-expr list with a
 * distinctive out-of-range tag (105) makes the nested
 * Rules_CheckFieldExprListAgainstConstraint -> Rules_CheckValueAgainstConstraint
 * chain return 1 via Method_TypeCodeAllowsRestriction's very first "tag==105"
 * guard (no need to fabricate a real constraint record), which lands on the
 * "not equal to 5" print branch back in the outer function. ---- */
TEST(cov2_02_litslot, enabled_reports_violation) {
  static _DWORD fieldnode[8];
  static _DWORD a2buf[8];
  int saved = g_CLIPS_StaticConstraintCheckingFlag;
  memset(fieldnode, 0, sizeof fieldnode);
  memset(a2buf, 0, sizeof a2buf);
  *(short *)fieldnode = 105; /* not a constant-type tag, not ==10 either */
  g_CLIPS_StaticConstraintCheckingFlag = 1;
  TOUCH(Rules_CheckLiteralSlotValueConstraint((int *)fieldnode,
                                               (int)(intptr_t)a2buf));
  g_CLIPS_StaticConstraintCheckingFlag = saved;
}

TEST(cov2_02_litslot, disabled_fast_return) {
  int saved = g_CLIPS_StaticConstraintCheckingFlag;
  g_CLIPS_StaticConstraintCheckingFlag = 0;
  CHECK_EQ(Rules_CheckLiteralSlotValueConstraint(0, 0), 1);
  g_CLIPS_StaticConstraintCheckingFlag = saved;
}

/* ---- Rules_ParseLoadFactsCommand: Lexer_TokenExpect(1) success (one-node
 * chain) then Rules_GetFileNameArg's tag==3 success branch hands back a
 * (bogus, nonexistent) filename, driving Rules_LoadFactsFromFile's failure
 * return so the command falls through to the shared "return result;" tail
 * instead of pass one's immediate "TokenExpect==-1 -> return 0". ---- */
TEST(cov2_02_loadfacts, filename_parsed_load_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov2_02_missing_facts.clp";
  COV2_02_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (int)(intptr_t)path; /* offset 16: the parsed string pointer */
  cov2_02_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_ParseLoadFactsCommand(0, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_GetAllowedAttributeTokenCode: pure sequential strcmp_ chain
 * against eight known constraint-name literals; drive every early "return"
 * plus the final no-match -1 fallback. ---- */
TEST(cov2_02_allowedattr, every_known_name_and_no_match) {
  CHECK_EQ(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedValues),
           103);
  /* Later comparisons consume decompiler-lost locals. Exercise them without
   * asserting stack-layout-dependent results across translation units. */
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedSymbols));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedStrings));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedLexemes));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInteg_0));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedNumbers));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInstanc));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedFloats));
  static const char no_match[] = "cov2-02-no-such-allowed-name";
  CHECK_EQ(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)no_match), -1);
}

/* ---- Rules_FindImportExportConstruct: the module-separator fast return,
 * and the "no such construct" not-found path (no real modules registered, so
 * the success branch needing a live module item is out of reach here). ---- */
TEST(cov2_02_importexport, module_separator_fast_return) {
  static char name[] = "MOD::thing";
  static _DWORD out;
  out = 0xdeadbeef;
  CHECK_EQ(
      Rules_FindImportExportConstruct((char *)"thing", &out, (_BYTE *)name, 0, 0),
      0);
  CHECK_EQ(out, 0);
}

TEST(cov2_02_importexport, not_found_no_modules) {
  static char name[] = "plainname";
  static _DWORD out;
  out = 0xdeadbeef;
  TOUCH(Rules_FindImportExportConstruct((char *)"thing", &out, (_BYTE *)name, 0, 0));
}

/* ---- Castle_DrawAllAmbientAnimationLayers: pure 1..10 loop calling
 * Castle_DrawAmbientAnimationLayer once per iteration; never called in pass
 * one (0 covered). ---- */
TEST(cov2_02_castle, draw_all_ambient_layers) {
  static _DWORD this_obj[16];
  memset(this_obj, 0, sizeof this_obj);
  TOUCH(Castle_DrawAllAmbientAnimationLayers(this_obj));
}

/* ---- Defgeneric_GetMethodRestrictionsCommand: a one-node SYMBOL-tagged
 * chain gets past the first Lexer_ParseValueList call so
 * Defgeneric_CheckGenericExists actually runs its "no such generic function"
 * report path (still safe: it only searches an empty table), reaching one
 * more line than pass one's immediately-failing empty chain. ---- */
TEST(cov2_02_defgenmethod, name_parsed_generic_missing) {
  static unsigned char anchor[32], node[32];
  static _DWORD symnode[8];
  static char genname[] = "cov2-02-missing-generic";
  COV2_02_SAVE_ARGCTX();
  memset(symnode, 0, sizeof symnode);
  symnode[4] = (int)(intptr_t)genname; /* offset 16: symbol name pointer */
  cov2_02_arg1(anchor, node, 2, symnode);
  static _DWORD out[8];
  memset(out, 0, sizeof out);
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(out, 2, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- WorldMap_HandleSaveGameAction: unconditional straight-line sequence;
 * simply never invoked in pass one (0 covered). Safe to call cold per the
 * fork/alarm isolation even if the dialog/viewport calls misbehave. ---- */
TEST(cov2_02_worldmap, handle_save_game_action) {
  TOUCH(WorldMap_HandleSaveGameAction(0, 0, 0.0));
}

/* ---- Rules_RefreshCommand: a one-node SYMBOL-tagged chain drives
 * Rules_GetConstructNameArg's success branch (matching
 * tests/unit/cases/test_cov11.c's construct-name-arg pattern), and with no
 * defrule registered Rules_FindDefruleByName returns 0, landing on the
 * Rules_ReportCantFindItem branch instead of pass one's immediate
 * "GetConstructNameArg failed -> return result" path. ---- */
TEST(cov2_02_refreshcmd, name_parsed_rule_not_found) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static char name[] = "cov2-02-missing-rule";
  COV2_02_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (int)(intptr_t)name;
  cov2_02_arg1(anchor, node, 2, valnode);
  TOUCH(Rules_RefreshCommand(0, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_HostRemoveFile: Lexer_TokenExpect(1) success (one-node chain)
 * then Rules_GetFileNameArg's tag==3 success branch feeds a filename into
 * Rules_BloadDeleteFile, reaching that call line instead of pass one's
 * immediate TokenExpect failure. ---- */
TEST(cov2_02_hostremovefile, filename_parsed) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov2_02_bload.bin";
  COV2_02_SAVE_ARGCTX();
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (int)(intptr_t)path;
  cov2_02_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_HostRemoveFile(0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Rules_FindTemplateForFactAddress: pure pointer-chasing helper over
 * three linked records; drive the immediate-match success chain all the way
 * to the final `return v4[1]`, and a not-found walk (mismatch, one hop via
 * the +68 next pointer, then falling off the end). ---- */
TEST(cov2_02_findtemplate, immediate_match_full_chain_success) {
  static unsigned char rec[80], v3buf[80], v4buf[80];
  memset(rec, 0, sizeof rec);
  memset(v3buf, 0, sizeof v3buf);
  memset(v4buf, 0, sizeof v4buf);
  *(int *)(rec + 4) = 100; /* matches a1 immediately */
  *(int *)(rec + 64) = (int)(intptr_t)v3buf;
  *(int *)v3buf = 17;                        /* *v3 == 17 */
  *(int *)(v3buf + 68) = (int)(intptr_t)v4buf; /* v3[17] */
  *(int *)v4buf = 2;                         /* *v4 == 2 */
  *(int *)(v4buf + 4) = 42;                  /* v4[1]: return value */
  *(int *)(v4buf + 64) = 0;                  /* !v4[16] */
  *(int *)(v4buf + 68) = 0;                  /* !v4[17] */
  CHECK_EQ(Rules_FindTemplateForFactAddress(100, (int)(intptr_t)rec), 42);
}

TEST(cov2_02_findtemplate, walk_then_not_found) {
  static unsigned char rec1[80], rec2[80];
  memset(rec1, 0, sizeof rec1);
  memset(rec2, 0, sizeof rec2);
  *(int *)(rec1 + 4) = 1;   /* mismatch vs a1==100 */
  *(int *)(rec1 + 68) = 0;  /* next -> NULL, walk ends without a match */
  CHECK_EQ(Rules_FindTemplateForFactAddress(100, (int)(intptr_t)rec1), 0);
}

/* ---- Rules_HostUnitAttack: thin wrapper always returning 1; never invoked
 * in pass one. ---- */
TEST(cov2_02_hostunit, attack_wrapper) {
  CHECK_EQ(Rules_HostUnitAttack(1, 2, 0, 0, 0.0), 1);
}

/* ---- Instance_PutSlotValue: forcing the slot-value tag away from {4,105}
 * and leaving dynamic constraint checking disabled (its default) makes
 * Instance_ValidateSlotValueConstraints fall through to its final "return 1"
 * branch, so PutSlotValue reaches its own success call to
 * Instance_StoreSlotValueAndMatch instead of pass one's always-0 path. ---- */
TEST(cov2_02_putslot, validate_succeeds_then_store) {
  static _DWORD a1buf[16];
  static unsigned char slotdesc[32];
  static int a2holder;
  static _DWORD a3buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(slotdesc, 0, sizeof slotdesc);
  memset(a3buf, 0, sizeof a3buf);
  a3buf[1] = 1; /* tag != 4 and != 105 */
  a2holder = (int)(intptr_t)slotdesc;
  TOUCH(Instance_PutSlotValue(a1buf, &a2holder, a3buf, 0.0));
}

/* ---- Rules_HostLexemep: a one-node SYMBOL-tagged chain drives the
 * "tag==2||tag==3 -> return 1" success branch that pass one's empty-chain
 * safety net could only ever fail. ---- */
TEST(cov2_02_hostlexeme, tagged_symbol_returns_true) {
  static unsigned char anchor[32], node[32];
  static _DWORD symnode[8];
  COV2_02_SAVE_ARGCTX();
  memset(symnode, 0, sizeof symnode);
  cov2_02_arg1(anchor, node, 2, symnode);
  /* argType is a decompiler-lost local; only exercise the reached path. */
  TOUCH(Rules_HostLexemep(0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- Class_SuperclassPCommand: cold call with the default empty argument
 * chain (Class_ParseTwoClassNameArgs fails immediately) -- still reaches a
 * different line mix than whatever pass one already banked, cheaply and
 * without needing a live class hierarchy. ---- */
TEST(cov2_02_superclasscmd, no_args_parse_fails) {
  CHECK_EQ(Class_SuperclassPCommand(0.0), 0);
}

/* ---- Building_CalcGarrisonStrength / BuildingPrisoner_GetAction: plain
 * arithmetic helpers, just drive them with a couple of plausible inputs. ---- */
TEST(cov2_02_building, calc_garrison_strength) {
  TOUCH(Building_CalcGarrisonStrength(0, 1));
  TOUCH(Building_CalcGarrisonStrength(3, 2));
}

TEST(cov2_02_prisoner, get_action) {
  TOUCH(BuildingPrisoner_GetAction(0, 0));
  TOUCH(BuildingPrisoner_GetAction(1, 3));
}

/* ---- Rules_PrintFactWithIndex: sprintf_ + Output_Write + Rules_PrintFact
 * straight-line sequence; a2 just needs a readable dword at +24. ---- */
TEST(cov2_02_printfact, print_with_index) {
  static _DWORD fact[16];
  memset(fact, 0, sizeof fact);
  fact[6] = 5; /* offset 24 */
  TOUCH(Rules_PrintFactWithIndex(0, (int)(intptr_t)fact));
}

/* ---- MessageHandler_PrintHandlerListTally: drive all three shapes of the
 * a2/a4 branch nest (a2==0 class-enumeration loop; a2!=0 with a4!=0 taking
 * the direct-offset path; a2!=0 with a4==0 taking the local out-param
 * path). No message handlers/classes are registered, so
 * MessageHandler_CountAndPrintHandlers just sees an empty list each time. ---- */
TEST(cov2_02_msghandler, tally_shapes) {
  static unsigned char classrec[64];
  memset(classrec, 0, sizeof classrec);
  TOUCH(MessageHandler_PrintHandlerListTally(0, 0, 0, 0));
  TOUCH(MessageHandler_PrintHandlerListTally(0, (int)(intptr_t)classrec, 0, 1));
  TOUCH(MessageHandler_PrintHandlerListTally(0, (int)(intptr_t)classrec, 0, 0));
}

/* ---- Compat_RenderDeviceFillSolidRect: reuse the fake-linear-surface setup
 * from tests/unit/cases/test_cov03.c with a couple of extra edge shapes
 * (single-row rect, color 0) chasing the one remaining uncovered line. ---- */
TEST(cov2_02_render, fill_solid_rect_edge_shapes) {
  extern _UNKNOWN *g_RenderDevice;
  extern int g_Surface_BaseVtable[17];
  _UNKNOWN *saved_device = g_RenderDevice;
  static _DWORD fake_surface[64];
  static unsigned char pixels[4096];

  memset(fake_surface, 0, sizeof(fake_surface));
  memset(pixels, 0, sizeof(pixels));
  fake_surface[0] = (32u << 16) | 32u;
  fake_surface[1] = (_DWORD)(uintptr_t)pixels;
  fake_surface[46] = (_DWORD)(uintptr_t)g_Surface_BaseVtable;
  g_RenderDevice = (_UNKNOWN *)fake_surface;

  TOUCH(Compat_RenderDeviceFillSolidRect(5, 5, 5, 5, 0));   /* single pixel */
  TOUCH(Compat_RenderDeviceFillSolidRect(0, 10, 31, 10, 9)); /* single row */

  g_RenderDevice = saved_device;
}

/* ---- WCIsvListBase_CopyAppendAll: full two-node source-list traversal
 * appending both values into a fresh destination list (alloc via the reserve
 * arena, since alloc_fn/free_fn are both 0/inherited from the source). ---- */
TEST(cov2_02_wclist, copy_append_all_traversal) {
  Mem_InitReserveBlock(0, 0);
  static WCCompatListBase src, dst;
  static WCCompatLink a, b;
  memset(&src, 0, sizeof src);
  memset(&dst, 0, sizeof dst);
  memset(&a, 0, sizeof a);
  memset(&b, 0, sizeof b);
  a.next_link = (int)(intptr_t)&b;
  a.value = 11;
  b.next_link = 0;
  b.value = 22;
  src.head_link = (int)(intptr_t)&a;
  src.tail_link = (int)(intptr_t)&b;
  src.count = 2;
  src.alloc_fn = 0;
  src.free_fn = 0;
  TOUCH(WCIsvListBase_CopyAppendAll((_DWORD *)&dst, (_DWORD *)&src, 0));
}

/* ---- Compat_StringHolderRemoveRange: drive the whole-string-destroy branch
 * (removed length == full text length), the partial-copy branch with
 * trailing content left over (second Compat_CopyPrefixN call), and the
 * partial-copy branch with nothing left over (no trailing copy). Uses
 * Compat_StringHolderCopyText for real (arena-backed) text storage, matching
 * tests/unit/cases/test_cov09.c's established pattern; j__nfree_ is a no-op
 * stub either way (see compat/decomp_runtime_stubs.c). ---- */
TEST(cov2_02_strholder, remove_range_destroy_whole) {
  Mem_InitReserveBlock(0, 0);
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));
  Compat_StringHolderCopyText(holder, "hello world");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 0, 0, 11));
}

TEST(cov2_02_strholder, remove_range_partial_with_tail) {
  Mem_InitReserveBlock(0, 0);
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));
  Compat_StringHolderCopyText(holder, "hello world");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 2, 0, 3));
}

TEST(cov2_02_strholder, remove_range_partial_no_tail) {
  Mem_InitReserveBlock(0, 0);
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));
  Compat_StringHolderCopyText(holder, "hello world");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 6, 0, 5));
}

/* ---- Instance_NotifyCreated: single-line wrapper, never invoked before. ---- */
TEST(cov2_02_instnotify, notify_created) {
  static _DWORD obj[8];
  memset(obj, 0, sizeof obj);
  TOUCH(Instance_NotifyCreated(obj, 0.0));
}

/* ---- Rules_CosBuiltin: default empty chain drives the parse-failed
 * "v5[1]=0.0; return 0.0;" branch; a one-node FLOAT-tagged chain drives the
 * success branch (return cos(value)). ---- */
TEST(cov2_02_cosbuiltin, parse_fails_returns_zero) {
  CHECK(Rules_CosBuiltin(0, 0, 0, 0.0) == 0.0);
}

TEST(cov2_02_cosbuiltin, parse_succeeds_returns_cos) {
  static unsigned char anchor[32], node[32];
  static double val;
  COV2_02_SAVE_ARGCTX();
  val = 0.6;
  cov2_02_arg1(anchor, node, 0, &val);
  TOUCH(Rules_CosBuiltin(0, 0, 0, 0.0));
  COV2_02_RESTORE_ARGCTX();
}

/* ---- IO_RenameFile: exercise both the real MoveFileA success branch (via
 * the compat POSIX rename shim) and the failure/_set_errno_nt_ branch (source
 * file does not exist). ---- */
TEST(cov2_02_renamefile, success_and_failure) {
  const char *src = "/tmp/claude-0/-home-user-clash-disassembly/"
                     "d4d0d676-5586-5b40-9f14-d9dffd44a5a5/scratchpad/"
                     "cov2_02_rename_src.tmp";
  const char *dst = "/tmp/claude-0/-home-user-clash-disassembly/"
                     "d4d0d676-5586-5b40-9f14-d9dffd44a5a5/scratchpad/"
                     "cov2_02_rename_dst.tmp";
  FILE *f = fopen(src, "w");
  if (f) {
    fclose(f);
    CHECK_EQ(IO_RenameFile(src, dst, 0), 0);
    remove(dst);
  }
  CHECK(IO_RenameFile("/nonexistent/cov2_02_no_such_source.tmp", dst, 0) != 0);
}

/* ---- IO_ScanfDigitValue: decimal digit, hex letter (via tolower_), and an
 * out-of-range character. ---- */
TEST(cov2_02_scanfdigit, all_branches) {
  CHECK_EQ(IO_ScanfDigitValue('5', 0, '5'), 5);
  CHECK_EQ(IO_ScanfDigitValue(200, 0, 'A'), 10);
  CHECK_EQ(IO_ScanfDigitValue(200, 0, 'z'), 16);
}

/* ---- Rules_BuildSlotBoundTestExpression: trivial two-call sequence, needs
 * the reserve arena for AST_NewNode's allocation. ---- */
TEST(cov2_02_slotbound, build_test_expression) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BuildSlotBoundTestExpression(0));
}

/* ---- CRT_BeginThread: dwTlsIndex starts at -1 (its real static initializer)
 * so the first call takes the CRT_AllocateTlsIndex/InitializeThreadAndFile
 * HandleHooks branch; CreateThread is stubbed to always fail in test_all.c,
 * so both calls also cover the "!Thread -> ThreadId[0]=-1" branch. ---- */
TEST(cov2_02_crtthread, begin_thread_cold_and_warm) {
  extern DWORD dwTlsIndex;
  DWORD saved = dwTlsIndex;
  dwTlsIndex = 0xFFFFFFFFu; /* force the AllocateTlsIndex branch */
  TOUCH(CRT_BeginThread(0, 4096, 0));
  TOUCH(CRT_BeginThread(0, 4096, 0)); /* dwTlsIndex now set -> skip branch */
  dwTlsIndex = saved;
}

/* ---- Original reveal propagation fills the midpoint to a revealed tile
 * two cells away. Keep the existing radius-two family probe last. ---- */
TEST(cov2_02_map, reveal_tiles_radius2) {
  static const int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
  static const int dy[8] = {0, 0, -1, 1, -1, -1, 1, 1};
  alignas(4) static unsigned char gd[0x25000];
  int saved_game_data = gameData;
  int saved_draw_mask = g_MiniMapDrawMask;
  int saved_surface = g_MiniMapSurface;
  char saved_scale = g_MiniMapPixelsPerTile;
  CHECK((uintptr_t)gd + sizeof gd <= INT32_MAX);
  memset(gd, 0, sizeof gd);
  *(_DWORD *)(gd + MAP_WIDTH_TILES_OFFSET) = 100;
  *(_DWORD *)(gd + MAP_HEIGHT_TILES_OFFSET) = 100;
  gameData = (int)(intptr_t)gd;
  /* Real minimap callback remains active; its software writer accepts a
   * null surface, and mask zero avoids asset-backed color tables. */
  g_MiniMapDrawMask = 0;
  g_MiniMapSurface = 0;
  g_MiniMapPixelsPerTile = 1;
  for (int player = 0; player < 6; ++player) {
    for (int direction = 0; direction < 8; ++direction) {
      memset(gd + PLAYER_RUNTIME_STATE_OFFSET, 0, 6 * PLAYER_DATA_STRIDE);
      int endpoint_x = 50 + 2 * dx[direction];
      int endpoint_y = 50 + 2 * dy[direction];
      int endpoint_byte = PLAYER_RUNTIME_STATE_OFFSET + player * PLAYER_DATA_STRIDE +
          PLAYER_REVEALED_TILES_OFFSET + PLAYER_REVEALED_TILE_ROW_BYTES * endpoint_x + endpoint_y / 8;
      gd[endpoint_byte] |= (unsigned char)(1u << (endpoint_y & 7));
      CHECK_EQ(Map_IsTileVisibleToPlayer(50, 50, player), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(50, 50, player), 1);
      CHECK_EQ(Map_IsTileVisibleToPlayer(50, 50, player), 1);
      CHECK_EQ(Map_IsTileVisibleToPlayer(endpoint_x, endpoint_y, player), 1);
      for (int neighbor = 0; neighbor < 8; ++neighbor)
        CHECK_EQ(Map_IsTileVisibleToPlayer(50 + dx[neighbor], 50 + dy[neighbor], player),
                 neighbor == direction);
      CHECK_EQ(Map_IsTileVisibleToPlayer(50, 50, (player + 1) % 6), 0);
      CHECK_EQ(Map_IsTileVisibleToPlayer(50 + dx[direction], 50 + dy[direction], (player + 1) % 6), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(50, 50, player), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(-1, 50, player), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(100, 50, player), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(50, -1, player), 0);
      CHECK_EQ(Map_RevealTileWithPropagation(50, 100, player), 0);
    }
  }
  gameData = saved_game_data;
  g_MiniMapDrawMask = saved_draw_mask;
  g_MiniMapSurface = saved_surface;
  g_MiniMapPixelsPerTile = saved_scale;
  TOUCH(Map_RevealTilesInRadius2ForPlayer(10, 10, 0));
}

/* ---- Defgeneric_ClearDefgenerics: both sides of the Rules_IsBloaded guard,
 * plus the empty-module-list immediate "return 1" (a real defgeneric-bearing
 * module is out of reach without a full rules-engine bring-up). ---- */
TEST(cov2_02_defgenclear, bloaded_and_not) {
  int saved = g_Rules_FactsBloadedFlag;
  g_Rules_FactsBloadedFlag = 1;
  CHECK_EQ(Defgeneric_ClearDefgenerics(), 0);
  g_Rules_FactsBloadedFlag = 0;
  CHECK_EQ(Defgeneric_ClearDefgenerics(), 1);
  g_Rules_FactsBloadedFlag = saved;
}
