/* cov3_05: second-pass coverage top-up for a mixed cluster of Rules_* value
 * parsing functions (Rules_MVSubseqFunction, Rules_FirstFunction,
 * Rules_MathSqrt, Rules_AcotBuiltin, Rules_ValueSatisfiesRangeConstraint,
 * Rules_GetAllowedAttributeTokenCode, Rules_MatchesCommand,
 * Rules_ClearActivationsForModule), Lexer_ReadToken, Rules_PlaceInRandomList,
 * Instance_ResolveSlotIndex, Deffunction_Delete, Dribble_GetcRouter,
 * MainMenu_RequestCreditsCinematic and Class_ClassSuperclassesCommand (see
 * cov3_batches/cov3_05.json). Every TEST below is prefixed cov3_05_ to avoid
 * symbol collisions with earlier cov00-23/cov2_NN files and other cov3_NN
 * batches.
 *
 * Each test runs in its own forked+alarm-watchdog child, so it is safe to
 * call functions that crash, exit, or spin -- coverage up to that point is
 * kept regardless. Several of the recovered functions below read
 * "possibly undefined" locals (decompiler artifacts); we cannot control
 * those, so some tests are best-effort and may crash partway through a
 * *different* (uninstrumented) callee after already covering the lines we
 * were after in our target function. */

/* ---- shared bootstrap: many Rules_ and Lexer_ functions allocate from the
 * dword_54DBA8 reserve-block arena and intern symbols into the dword_54DD50
 * atom tables. Both are NULL until carved out (same pattern cov13/17/18/19
 * and cov2_00 use). */
static void cov3_05_bootstrap(void) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
}

/* ---- shared "expression node" rig -------------------------------------
 * Parser_ParseForm / Rules_RtnUnknown / Rules_CompareBoundedCEValues all walk
 * a common node shape: int16 type tag at offset 0, a raw 4-byte "value" slot
 * at offset 2, and a "next" link at offset 10. Rules_RtnUnknown/RtnArgCount
 * find the head of the chain via *(int*)(dword_51A960 + 6). All buffers must
 * be `static` so their truncated-to-32-bit addresses round-trip correctly
 * (this is a 64-bit -no-pie build modeling pointers as 32-bit ints). */
static void cov3_05_set_node_simple(unsigned char *node, short type,
                                     void *valueSlot, void *next) {
  memset(node, 0, 16);
  *(short *)node = type;
  *(int *)(node + 2) = (int)(intptr_t)valueSlot;
  *(int *)(node + 10) = (int)(intptr_t)next;
}

static void cov3_05_set_ctx(unsigned char *ctx, void *firstNode) {
  memset(ctx, 0, 16);
  *(int *)(ctx + 6) = (int)(intptr_t)firstNode;
}

/* =======================================================================
 * Rules_MVSubseqFunction -- 3/27 covered previously (only the first failing
 * Lexer_ParseValueList check was ever reached). Rig a 3-node arg chain
 * (int, int, multifield) so all three Lexer_ParseValueList calls can
 * succeed, then vary the parsed values to walk every comparison/clamp
 * branch and the final success tail.
 * ======================================================================= */
static void cov3_05_mvsubseq_case(short t1, short t2, short t3, int v3val,
                                   int v4val, int resultLen, int v10raw) {
  static unsigned char ctx[16], node1[16], node2[16], node3[16];
  static unsigned char header[32], mfObj[16];
  static int valObj1[16], valObj2[16];
  static _DWORD out[8];
  int saved;

  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(node2, 0, sizeof(node2));
  memset(node3, 0, sizeof(node3));
  memset(header, 0, sizeof(header));
  memset(mfObj, 0, sizeof(mfObj));
  memset(valObj1, 0, sizeof(valObj1));
  memset(valObj2, 0, sizeof(valObj2));
  memset(out, 0, sizeof(out));

  valObj1[4] = v3val; /* byte offset 16 -> "v3" (arg1 value) */
  valObj2[4] = v4val; /* byte offset 16 -> "v4" (arg2 value) */

  *(int *)(header + 8) = (int)(intptr_t)mfObj; /* -> a2[2] for type-4 parse */
  *(int *)(header + 12) = v10raw;              /* -> a2[3] ("v10") */
  *(int *)(mfObj + 6) = resultLen;             /* -> "result" (multifield len) */

  cov3_05_set_node_simple(node1, t1, valObj1, node2);
  cov3_05_set_node_simple(node2, t2, valObj2, node3);
  cov3_05_set_node_simple(node3, t3, header, 0);
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Rules_MVSubseqFunction(out, 0.0));
  dword_51A960 = saved;
}

TEST(cov3_05_mvsubseq, success_basic) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 1, 3, 5, 0);
}

TEST(cov3_05_mvsubseq, reload_v4_gt_result) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 1, 8, 5, 0);
}

TEST(cov3_05_mvsubseq, v3_gt_result_error) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 10, 10, 5, 0);
}

TEST(cov3_05_mvsubseq, v4_lt_one_error) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 1, 0, 5, 0);
}

TEST(cov3_05_mvsubseq, v4_lt_v3_error) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 5, 2, 5, 0);
}

TEST(cov3_05_mvsubseq, arg2_parse_fail) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 2, 4, 1, 3, 5, 0);
}

TEST(cov3_05_mvsubseq, arg3_parse_fail) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 1, 1, 3, 5, 0);
}

TEST(cov3_05_mvsubseq, v3_lt_one_clamp) {
  cov3_05_bootstrap();
  cov3_05_mvsubseq_case(1, 1, 4, 0, 2, 5, 0);
}

/* =======================================================================
 * Rules_FirstFunction -- 4/15 covered previously (only the first failing
 * Lexer_ParseValueList check was reached). Rig a single multifield-typed
 * arg node so the parse succeeds, then vary the two header fields to walk
 * both sides of "if (v9+1 >= v8+1)".
 * ======================================================================= */
static void cov3_05_first_case(int v8val, int v9val) {
  static unsigned char ctx[16], node1[16], header[32];
  static _DWORD out[8];
  int saved;

  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(header, 0, sizeof(header));
  memset(out, 0, sizeof(out));

  *(int *)(header + 12) = v8val; /* -> a2[3] ("v8") */
  *(int *)(header + 16) = v9val; /* -> a2[4] ("v9") */

  cov3_05_set_node_simple(node1, 4, header, 0);
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Rules_FirstFunction(out, 1, 0.0));
  dword_51A960 = saved;
}

TEST(cov3_05_first, branch_v9_ge_v8) {
  cov3_05_bootstrap();
  cov3_05_first_case(3, 5); /* v9+1(6) >= v8+1(4) -> true branch */
}

TEST(cov3_05_first, branch_v9_lt_v8) {
  cov3_05_bootstrap();
  cov3_05_first_case(5, 2); /* v9+1(3) >= v8+1(6) -> false branch */
}

/* =======================================================================
 * Lexer_ReadToken -- 23/32 covered previously (the loop body's append/
 * continuation lines and the bracketed-multifield-name branch were never
 * reached). Rig a fake IO router (match/read/skip callbacks) so
 * Lexer_PeekChar/Lexer_SkipChar deterministically stream "[ab] " through
 * the tokenizer: '[' and ']' both pass the IsTable word-char test on this
 * build, so the accumulated token is "[ab]" and the a2>2 && buf[0]=='['
 * && buf[len-1]==']' bracket-stripping branch fires.
 * ======================================================================= */
static const char *cov3_05_lex_stream;
static int cov3_05_lex_pos;

static int cov3_05_lex_match(int a1) {
  (void)a1;
  return 1;
}

static int cov3_05_lex_read(int a1) {
  int c;
  (void)a1;
  c = (unsigned char)cov3_05_lex_stream[cov3_05_lex_pos];
  if (cov3_05_lex_stream[cov3_05_lex_pos] != 0)
    cov3_05_lex_pos++;
  return c;
}

static int cov3_05_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}

TEST(cov3_05_lexreadtoken, bracket_multifield_name) {
  static unsigned char router[64];
  static _DWORD outType[4];
  int saved604, saved608;

  cov3_05_bootstrap();

  memset(router, 0, sizeof(router));
  *(int *)(router + 4) = 1;
  *(int *)(router + 12) = (int)(intptr_t)cov3_05_lex_match;
  *(int *)(router + 24) = (int)(intptr_t)cov3_05_lex_read;
  *(int *)(router + 28) = (int)(intptr_t)cov3_05_lex_skip;
  *(int *)(router + 32) = 0;

  saved604 = g_IO_RouterListHead;
  saved608 = g_IO_FastLoadFilePtr;
  g_IO_RouterListHead = (int)(intptr_t)router;
  g_IO_FastLoadFilePtr = 0x7A7A7A00; /* sentinel a1 will never equal */

  cov3_05_lex_stream = "[ab] ";
  cov3_05_lex_pos = 0;

  memset(outType, 0, sizeof(outType));
  TOUCH(Lexer_ReadToken(0x1234, 0, outType, 999));

  g_IO_RouterListHead = saved604;
  g_IO_FastLoadFilePtr = saved608;
}

/* =======================================================================
 * Rules_PlaceInRandomList -- 14/22 covered previously; walk every
 * comparison/return combination in the linked-list search.
 * ======================================================================= */
static void cov3_05_place_run(int keyV3, int keyV2, int keyV4, int haveNode,
                               int nodeV6, int nodeV3, int nodeV8) {
  static _DWORD key[8], node[8];
  _DWORD *a1;

  memset(key, 0, sizeof(key));
  memset(node, 0, sizeof(node));
  key[2] = keyV3;
  key[3] = (unsigned int)keyV2;
  key[5] = keyV4;

  a1 = 0;
  if (haveNode) {
    node[2] = nodeV6;
    node[3] = nodeV3;
    node[5] = nodeV8;
    node[7] = 0; /* no next node */
    a1 = node;
  }
  TOUCH(Rules_PlaceInRandomList(a1, key));
}

TEST(cov3_05_placerandom, null_list) { cov3_05_place_run(0, 0, 0, 0, 0, 0, 0); }

TEST(cov3_05_placerandom, key_below_node_fallthrough) {
  cov3_05_place_run(1, 0, 0, 1, 5, 0, 0);
}

TEST(cov3_05_placerandom, key_above_node_immediate_return) {
  cov3_05_place_run(10, 0, 0, 1, 5, 0, 0);
}

TEST(cov3_05_placerandom, v4_lt_v8_return) {
  cov3_05_place_run(5, 0, 1, 1, 5, 0, 5);
}

TEST(cov3_05_placerandom, equal_keys_break) {
  cov3_05_place_run(5, 3, 5, 1, 5, 10, 5);
}

/* =======================================================================
 * Deffunction_Delete -- 4/11 covered previously. dword_51A1AC backs
 * Rules_IsBloaded(); toggling it deterministically covers the early
 * "return 0" branch. The remaining branches key off decompiler-UB locals
 * we cannot control, so we also just call it plainly a couple more times.
 * ======================================================================= */
TEST(cov3_05_deffunctiondelete, isbloaded_true) {
  int saved = g_Rules_FactsBloadedFlag;
  g_Rules_FactsBloadedFlag = 1;
  TOUCH(Deffunction_Delete());
  g_Rules_FactsBloadedFlag = saved;
}

TEST(cov3_05_deffunctiondelete, isbloaded_false_a) {
  int saved = g_Rules_FactsBloadedFlag;
  g_Rules_FactsBloadedFlag = 0;
  cov3_05_bootstrap();
  TOUCH(Deffunction_Delete());
  g_Rules_FactsBloadedFlag = saved;
}

TEST(cov3_05_deffunctiondelete, isbloaded_false_b) {
  int saved = g_Rules_FactsBloadedFlag;
  g_Rules_FactsBloadedFlag = 0;
  cov3_05_bootstrap();
  TOUCH(Deffunction_Delete());
  g_Rules_FactsBloadedFlag = saved;
}

/* =======================================================================
 * Rules_GetAllowedAttributeTokenCode -- 12/19 covered previously. This is a
 * cascade of strcmp_ checks against successive "possibly undefined" locals
 * that (per this build's calling convention) alias the original a1 value
 * reloaded from the stack before each call, so passing a name that matches
 * none of the constants walks the whole cascade to the final comparison.
 * ======================================================================= */
TEST(cov3_05_allowedattrtok, no_match_falls_through) {
  static char name[] = "totally-unrelated-value";
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)name));
}

TEST(cov3_05_allowedattrtok, matches_last_constant) {
  static char name[] = "allowed-floats";
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)name));
}

/* =======================================================================
 * Rules_MathSqrt / Rules_AcotBuiltin -- both funnel through
 * Rules_MathParseSingleArg(&out, a3, a4), which calls
 * Lexer_TokenExpect(1) (UB branch we cannot pin down) and then
 * Lexer_ParseValueList(1, v5, 0, a3). Rig a single float-typed (type 0)
 * arg node so the parse can succeed, then vary the parsed double to walk
 * the domain-error / near-zero / normal branches.
 * ======================================================================= */
static void cov3_05_mathsqrt_case(double val) {
  static unsigned char ctx[16], node1[16];
  static double valObj[8];
  int saved;

  cov3_05_bootstrap();
  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(valObj, 0, sizeof(valObj));
  valObj[2] = val; /* byte offset 16 */

  cov3_05_set_node_simple(node1, 0, valObj, 0);
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Rules_MathSqrt(0, 0, 1, 0.0));
  dword_51A960 = saved;
}

TEST(cov3_05_mathsqrt, positive_value) { cov3_05_mathsqrt_case(4.0); }
TEST(cov3_05_mathsqrt, negative_value_domain_error) {
  cov3_05_mathsqrt_case(-4.0);
}

static void cov3_05_acot_case(double val) {
  static unsigned char ctx[16], node1[16];
  static double valObj[8];
  int saved;

  cov3_05_bootstrap();
  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(valObj, 0, sizeof(valObj));
  valObj[2] = val;

  cov3_05_set_node_simple(node1, 0, valObj, 0);
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Rules_AcotBuiltin(0, 0, 1, 0.0));
  dword_51A960 = saved;
}

TEST(cov3_05_acot, near_zero) { cov3_05_acot_case(0.0); }
TEST(cov3_05_acot, normal_value) { cov3_05_acot_case(2.0); }

/* =======================================================================
 * Rules_ValueSatisfiesRangeConstraint -- 8/13 covered previously. Rig a
 * constraint record with one lower-bound and one upper-bound node (both
 * float-typed, matching the a1==0 comparison branch inside
 * Rules_CompareBoundedCEValues) and vary the tested value so we both enter
 * the while loop (and hit the inside-loop "return 0") and skip it entirely
 * (falling through to the final "return 1").
 * ======================================================================= */
static void cov3_05_rangeconstraint_case(unsigned int outerType, double val,
                                          double lo, double hi) {
  static unsigned char rec[32], lowerNode[16], upperNode[16];
  static double valueObj[8], lowerObj[8], upperObj[8];

  memset(rec, 0, sizeof(rec));
  memset(lowerNode, 0, sizeof(lowerNode));
  memset(upperNode, 0, sizeof(upperNode));
  memset(valueObj, 0, sizeof(valueObj));
  memset(lowerObj, 0, sizeof(lowerObj));
  memset(upperObj, 0, sizeof(upperObj));

  valueObj[2] = val;
  lowerObj[2] = lo;
  upperObj[2] = hi;

  cov3_05_set_node_simple(lowerNode, 0, lowerObj, 0);
  cov3_05_set_node_simple(upperNode, 0, upperObj, 0);
  *(int *)(rec + 10) = (int)(intptr_t)lowerNode;
  *(int *)(rec + 14) = (int)(intptr_t)upperNode;

  TOUCH(Rules_ValueSatisfiesRangeConstraint(outerType, (int)(intptr_t)valueObj,
                                             (int)(intptr_t)rec));
}

TEST(cov3_05_rangeconstraint, below_lower_inside_loop_return0) {
  cov3_05_rangeconstraint_case(0, 1.0, 5.0, 10.0);
}

TEST(cov3_05_rangeconstraint, within_range_return1_after_loop) {
  cov3_05_rangeconstraint_case(0, 7.0, 5.0, 10.0);
}

/* =======================================================================
 * Instance_ResolveSlotIndex -- 4/8 covered previously (Class_FindSlotNameID
 * always returned -1 because dword_51AD70's hash bucket table was NULL).
 * Rig a one-entry hash bucket table so the lookup succeeds and returns a
 * controlled slot id, then vary the class's slot-count threshold to walk
 * both the "slot_id > threshold" early-return and the final table lookup.
 * ======================================================================= */
static void cov3_05_resolveslot_case(int threshold, int tableVal) {
  static unsigned char inst[128], slotDesc[32], entryNode[32];
  static int bucketTable[256], slotTable[16];
  int saved;

  memset(inst, 0, sizeof(inst));
  memset(slotDesc, 0, sizeof(slotDesc));
  memset(entryNode, 0, sizeof(entryNode));
  memset(bucketTable, 0, sizeof(bucketTable));
  memset(slotTable, 0, sizeof(slotTable));

  *(int *)(slotDesc + 12) = 0; /* hash key -> bucket 0 */

  *(int *)(entryNode + 8) = 3;                          /* resolved slot_id */
  *(int *)(entryNode + 12) = (int)(intptr_t)slotDesc;   /* identity match */
  bucketTable[0] = (int)(intptr_t)entryNode;

  saved = dword_51AD70;
  dword_51AD70 = (int)(intptr_t)bucketTable;

  *(int *)(inst + 76) = threshold;
  *(int *)(inst + 60) = (int)(intptr_t)slotTable;
  slotTable[3] = tableVal;

  TOUCH(Instance_ResolveSlotIndex((int)(intptr_t)inst, (int)(intptr_t)slotDesc));

  dword_51AD70 = saved;
}

TEST(cov3_05_resolveslot, success_lookup) {
  cov3_05_resolveslot_case(10, 5);
}

TEST(cov3_05_resolveslot, over_threshold_error) {
  cov3_05_resolveslot_case(1, 5);
}

/* =======================================================================
 * Rules_AcotBuiltin/Rules_MathSqrt above already bootstrap the engine;
 * MainMenu_RequestCreditsCinematic just needs a plausible widget struct so
 * UIWidget_PlayPressedReleaseAnimation doesn't fault before the two flag
 * assignments and return.
 * ======================================================================= */
TEST(cov3_05_mainmenucredits, basic) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof(widget));
  TOUCH(MainMenu_RequestCreditsCinematic((uintptr_t)(intptr_t)widget));
}

/* =======================================================================
 * Rules_ClearActivationsForModule -- 4/7 covered previously (result was
 * always NULL because dword_51A9B0/the defrule module item table were
 * unset). Rig dword_51A9B0 -> module record -> item array -> defrule
 * module item -> one activation node so the do/while body executes
 * Rules_RemoveActivation once with fields set so it completes without
 * touching the "possibly undefined" locals it reads on other paths.
 * ======================================================================= */
TEST(cov3_05_clearactivationsformodule, one_activation) {
  static unsigned char act[64], actTarget[64], P[32], M[32];
  static _DWORD itemArray[8];
  int saved;

  cov3_05_bootstrap();
  memset(act, 0, sizeof(act));
  memset(actTarget, 0, sizeof(actTarget));
  memset(P, 0, sizeof(P));
  memset(M, 0, sizeof(M));
  memset(itemArray, 0, sizeof(itemArray));

  *(int *)(act + 0) = (int)(intptr_t)actTarget; /* *v4 -> zeroed struct */
  *(int *)(act + 4) = 0;                        /* v10 (a3==1 path) skip */
  *(int *)(act + 16) = 0;                        /* a1[4] skip FreePartialMatch */
  *(int *)(act + 24) = (int)(intptr_t)actTarget; /* a1[6] nonzero -> v6 branch */
  *(int *)(act + 28) = 0;                        /* a1[7] -> v12 == 0 */

  *(int *)(P + 12) = (int)(intptr_t)act; /* Rules_GetDefruleModuleItem()+12 */
  itemArray[0] = (int)(intptr_t)P;
  *(int *)(M + 8) = (int)(intptr_t)itemArray;

  saved = dword_51A9B0;
  dword_51A9B0 = (int)(intptr_t)M;

  TOUCH(Rules_ClearActivationsForModule());

  dword_51A9B0 = saved;
}

/* =======================================================================
 * Dribble_GetcRouter -- 3/6 covered previously (Lexer_PeekChar likely
 * crashed dereferencing dword_51A608+4 because the UB router-name local
 * happened to equal dword_51A608's default 0). Point dword_51A608 at an
 * improbable sentinel so that comparison is false, forcing the safe
 * "no matching router" fallback inside Lexer_PeekChar instead.
 * ======================================================================= */
TEST(cov3_05_dribblegetcrouter, avoid_file_router_crash) {
  int saved604 = g_IO_RouterListHead;
  int saved608 = g_IO_FastLoadFilePtr;
  g_IO_RouterListHead = 0;
  g_IO_FastLoadFilePtr = 0x7A7A7A00;
  TOUCH(Dribble_GetcRouter());
  g_IO_RouterListHead = saved604;
  g_IO_FastLoadFilePtr = saved608;
}

TEST(cov3_05_dribblegetcrouter, plain_call) { TOUCH(Dribble_GetcRouter()); }

/* =======================================================================
 * Rules_MatchesCommand -- 5/8 covered previously (Rules_RtnArgCount() never
 * matched 1 so Rules_GetConstructNameArg always hit its error branch). Rig
 * a one-node arg chain with a symbol-typed node so
 * Rules_GetConstructNameArg succeeds, driving Rules_MatchesCommand into its
 * "result truthy" branch and the Rules_FindDefruleByName call (which then
 * likely faults inside Rules_FindConstructByNameGeneric on its own
 * decompiler-UB second argument -- caught by the harness, but only after
 * the lines we want here have already executed).
 * ======================================================================= */
TEST(cov3_05_matchescommand, best_effort_arg_present) {
  static unsigned char ctx[16], node1[16];
  static char ruleName[] = "MyRule";
  static int nameHolder[8];
  int saved;

  cov3_05_bootstrap();
  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(nameHolder, 0, sizeof(nameHolder));
  nameHolder[4] = (int)(intptr_t)ruleName; /* byte offset 16 */

  cov3_05_set_node_simple(node1, 2, nameHolder, 0); /* type 2 == symbol */
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Rules_MatchesCommand(0, 0.0));
  dword_51A960 = saved;
}

/* =======================================================================
 * Class_ClassSuperclassesCommand -- 3/6 covered previously. Best-effort:
 * rig the same one-node symbol-typed arg chain so
 * Class_ParseClassNameAndInheritFlag's Lexer_ParseValueList call succeeds
 * and Class_LookupByQualifiedName actually gets invoked (its own internal
 * "possibly undefined" locals make the outcome unpredictable, but this at
 * least exercises more of the parse-and-lookup path than a bare call).
 * ======================================================================= */
TEST(cov3_05_classsuperclasses, best_effort_arg_present) {
  static unsigned char ctx[16], node1[16];
  static char className[] = "NoSuchClass";
  static int nameHolder[8];
  int saved;

  cov3_05_bootstrap();
  memset(ctx, 0, sizeof(ctx));
  memset(node1, 0, sizeof(node1));
  memset(nameHolder, 0, sizeof(nameHolder));
  nameHolder[4] = (int)(intptr_t)className;

  cov3_05_set_node_simple(node1, 2, nameHolder, 0);
  cov3_05_set_ctx(ctx, node1);

  saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)ctx;
  TOUCH(Class_ClassSuperclassesCommand(0, 0.0));
  dword_51A960 = saved;
}

/* =======================================================================
 * Map_ClassifyFogOfWarOverlayForPlayer -- 31/45 covered previously. The
 * function's mid-body locals (v8, v10) are decompiler artifacts fed by
 * whatever the compiler leaves in registers/stack after the eight
 * Map_IsTileVisibleToPlayer calls, so we cannot pick exact return codes;
 * instead we vary which neighbouring tiles are "revealed" in a fake
 * gameData blob (same technique as cov07/cov05) across several calls to
 * maximize the chance of walking different parts of the big if/else-if
 * classification cascade.
 * ======================================================================= */
static void cov3_05_fog_setup(char *gd, int width, int height) {
  memset(gd, 0, 2200000);
  gameData = (int)(intptr_t)gd;
  *(int *)(gd + 140000) = width;
  *(int *)(gd + 140004) = height;
}

static void cov3_05_fog_reveal(char *gd, int tileRow, int tileCol,
                                int player) {
  long base = 140024L + 1423L * player + 57L + 13L * tileRow;
  int byteOff = tileCol >> 3;
  long idx = base + byteOff;
  if (idx >= 0 && idx < 2200000)
    gd[idx] |= (char)(1 << (tileCol & 7));
}

TEST(cov3_05_fogclassify, all_neighbors_hidden) {
  static char gd[2200000];
  int saved = gameData;
  cov3_05_fog_setup(gd, 200, 200);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(50, 50, 0));
  gameData = saved;
}

TEST(cov3_05_fogclassify, last_neighbor_visible) {
  static char gd[2200000];
  int saved = gameData;
  cov3_05_fog_setup(gd, 200, 200);
  /* Map_ClassifyFogOfWarOverlayForPlayer's last visibility probe is
   * (a1+1, a2+1, a3); reveal exactly that tile. */
  cov3_05_fog_reveal(gd, 51, 51, 0);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(50, 50, 0));
  gameData = saved;
}

TEST(cov3_05_fogclassify, several_neighbors_visible_diff_player) {
  static char gd[2200000];
  int saved = gameData;
  cov3_05_fog_setup(gd, 200, 200);
  cov3_05_fog_reveal(gd, 19, 30, 1);
  cov3_05_fog_reveal(gd, 20, 29, 1);
  cov3_05_fog_reveal(gd, 21, 31, 1);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(20, 30, 1));
  gameData = saved;
}

TEST(cov3_05_fogclassify, center_visible_immediate_return) {
  static char gd[2200000];
  int saved = gameData;
  cov3_05_fog_setup(gd, 200, 200);
  cov3_05_fog_reveal(gd, 20, 30, 0);
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(20, 30, 0));
  gameData = saved;
}
