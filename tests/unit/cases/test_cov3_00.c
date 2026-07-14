/* cov3_00: second-pass coverage for partially-covered functions around
 * 19936-186300 (see cov3_batches/cov3_00.json). Every finding below was
 * empirically verified against a private scratch build of the exact same
 * clash95.c (same compiler/flags) before being written here, using gdb to
 * confirm which source lines are actually reached.
 *
 * Recurring theme across this batch: several of these Rules_* command
 * wrappers (Rules_ParseLoadFactsCommand, Rules_SaveCommand,
 * Rules_HostRenameFile, Rules_StrCompareBuiltin, Rules_MathCoth) go through
 * Lexer_TokenExpect()/Rules_RtnUnknown()/Lexer_ParseValueList(), which walk
 * a fake "argument chain" rooted at the global dword_51A960. Building a
 * minimal one/two-node chain (a "head" struct whose byte-offset+6 holds the
 * first node pointer, each node's byte-offset+10 holding the next pointer)
 * lets Lexer_TokenExpect's own arg-count check succeed. The parsed-value
 * struct these helpers fill in is passed by pointer (Parser_ParseForm writes
 * through it directly), so as long as we also point each node's
 * byte-offset+2 field at a small scratch buffer (avoiding a NULL deref a few
 * frames down in Rules_ClampEvaluationDepth), the whole chain runs without
 * crashing and our target functions progress well past their previous
 * "Lexer_TokenExpect failed -> return 0" early exit. */

/* ---- shared arg-chain node helpers ---- */
static void cov3_00_mk_node(unsigned char *node, short type_tag,
                             unsigned char *valbuf) {
  memset(node, 0, 64);
  memset(valbuf, 0, 64);
  *(short *)(node + 0) = type_tag;   /* Parser_ParseForm's `*a1` type switch */
  *(int *)(node + 2) = (int)(intptr_t)valbuf; /* keeps the propagate-depth
                                                  chain off a NULL deref */
}

/* ---- Rules_ParseLoadFactsCommand: previously only exercised the
 * Lexer_TokenExpect(1)==-1 early "return 0" (3/9 lines). A real one-node arg
 * chain gets Lexer_TokenExpect(1) to succeed, reaching the
 * Rules_GetFileNameArg call, its "if (result)" check (false, since the
 * decompiler lost the register carrying the parsed-value's type tag back to
 * a *named* local here, so GetFileNameArg's own success check always reads
 * stale/unrelated stack content) and the final "return result" -- 3 more
 * lines than before, without crashing. ---- */
TEST(cov3_00_rules, parse_load_facts_command_reaches_getfilenamearg) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;

  memset(head, 0, sizeof head);
  cov3_00_mk_node(node1, 0, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;

  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_ParseLoadFactsCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_SaveCommand: identical shape/gating to the above; reaches the
 * GetFileNameArg call, the `v5 = result;` copy, the `if (result)` check, and
 * the final `return result;` -- the 4 previously-uncovered lines. ---- */
TEST(cov3_00_rules, save_command_reaches_getfilenamearg) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char valbuf1[64];
  int saved;

  memset(head, 0, sizeof head);
  cov3_00_mk_node(node1, 0, valbuf1);
  *(int *)(head + 6) = (int)(intptr_t)node1;

  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_SaveCommand(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_HostRenameFile: takes 2 args, so Lexer_TokenExpect(2) needs a
 * 2-node chain. Reaches the first GetFileNameArg call, its "if (result)"
 * check (false) and the final "return result;" line. ---- */
TEST(cov3_00_rules, host_rename_file_reaches_getfilenamearg) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char node2[64];
  static unsigned char valbuf1[64];
  static unsigned char valbuf2[64];
  int saved;

  memset(head, 0, sizeof head);
  cov3_00_mk_node(node1, 0, valbuf1);
  cov3_00_mk_node(node2, 0, valbuf2);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  *(int *)(node1 + 10) = (int)(intptr_t)node2;

  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_HostRenameFile(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_StrCompareBuiltin: Rules_ArgRangeCheck((int)aStrCompare, 3)
 * returns the real Rules_RtnArgCount() value when it's in range, so a
 * 2-node chain makes v2==2 (the "else strcmp_" branch) and a 3-node chain
 * makes v2==3 (the "if (v2==3)" branch with a 3rd Lexer_ParseValueList
 * call). Unlike Rules_GetFileNameArg above, Lexer_ParseValueList reads its
 * output through the *same pointer* it was written through (a2[1]/a2[2],
 * not separately-named locals), so giving each node a type tag of 3
 * (STRING) makes `a3==111 && (a2[1]==2||a2[1]==3)` true and the parse
 * actually "succeeds" here, driving deep into both variants before an
 * eventual crash on the genuinely-lost `v4`/`v9` locals a few lines later
 * (isolated; the lines up to that point are the real payoff). ---- */
TEST(cov3_00_rules, strcompare_builtin_two_args_else_branch) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char node2[64];
  static unsigned char valbuf1[64];
  static unsigned char valbuf2[64];
  int saved;

  memset(head, 0, sizeof head);
  cov3_00_mk_node(node1, 3, valbuf1); /* STRING type tag */
  cov3_00_mk_node(node2, 3, valbuf2);
  *(int *)(head + 6) = (int)(intptr_t)node1;
  *(int *)(node1 + 10) = (int)(intptr_t)node2;

  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_StrCompareBuiltin(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov3_00_rules, strcompare_builtin_three_args_v2_eq_3_branch) {
  static unsigned char head[64];
  static unsigned char node1[64];
  static unsigned char node2[64];
  static unsigned char node3[64];
  static unsigned char valbuf1[64];
  static unsigned char valbuf2[64];
  static unsigned char valbuf3[64];
  int saved;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  memset(head, 0, sizeof head);
  cov3_00_mk_node(node1, 3, valbuf1);
  cov3_00_mk_node(node2, 3, valbuf2);
  cov3_00_mk_node(node3, 0, valbuf3); /* FLOAT type tag: Lexer_ParseValueList's
                                         "integer requested, float supplied"
                                         coercion path is deterministic and
                                         boxes via Rules_AddIntegerValue,
                                         which needs the atom tables above. */
  *(int *)(head + 6) = (int)(intptr_t)node1;
  *(int *)(node1 + 10) = (int)(intptr_t)node2;
  *(int *)(node2 + 10) = (int)(intptr_t)node3;

  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)head;
  TOUCH(Rules_StrCompareBuiltin(0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_MathCoth: Rules_MathParseSingleArg's OWN body uses a real
 * local array (not disconnected named locals), so its post-parse behavior
 * is controllable in principle -- but it gates on Lexer_TokenExpect(1)
 * first, and (verified empirically against a private scratch build)
 * Lexer_TokenExpect's "expected vs. actual arg count" comparison reads a
 * decompiler-lost register whose garbage value is a property of *this*
 * call site's stack frame, not of anything we pass in. From
 * Rules_MathCoth's call chain that garbage lands in the unconditional-error
 * bucket every time (unlike the Rules_*Command wrappers above, where the
 * same trick landed in the "compare against real arg count" bucket) --
 * so Rules_MathParseSingleArg always fails here regardless of chain setup,
 * and the singularity/near-zero/tanh branches below it are unreachable via
 * any external call. No test added for this one; see cov3_00_rules'
 * strcompare/save/load/rename tests above for where the identical-looking
 * technique *does* pay off. ---- */

/* ---- UnitBattle_GetTargetCrowdingScale: switches on
 * UnitBattle_CountAdjacentEnemies(a1), which walks 8 fixed "neighbor delta"
 * entries sourced from the (decompiler-truncated to single-element)
 * dword_514500/dword_514504 arrays -- indices beyond 0 are out-of-bounds
 * reads of whatever happens to sit next to them in .data/.bss, which proved
 * link-composition-dependent even across two of our own private scratch
 * builds (differing in how many other static buffers were linked in), so
 * hand-picking exact tile offsets to land on precise counts isn't portable
 * to the real coverage binary's own link composition.
 *
 * Instead of guessing exact offsets, sweep a "poison radius": for a range
 * of radii, mark every tile within [y-radius, y+radius] of the unit's row
 * as owned by a mismatching faction (all other rows match the unit's own
 * faction, so they never count). Whatever the real in-bounds neighbor
 * offsets turn out to be in this build, CountAdjacentEnemies' resulting
 * count is a non-decreasing step function of the radius (monotonically
 * poisoning strictly more of the fixed candidate offsets as radius grows),
 * so sweeping many radii from 0 up to comfortably past every offset we've
 * ever observed (-1, 0, +8) is far more likely to pass through the case-3/
 * case-4/case-5 thresholds than any single hand-picked layout -- verified
 * against a private scratch build of this exact clash95.c, this sweep does
 * hit all three (in addition to the already-covered default/0-2 cases). */
TEST(cov3_00_unitbattle, get_target_crowding_scale_radius_sweep) {
  static _DWORD mapbuf[4096];
  static unsigned char unit[16];
  static const int radii[] = {0, 1, 2, 3, 4,  5,  6,  7,
                               8, 9, 10, 15, 20, 30, 40};
  int saved = g_MapData;
  int x = 50, y = 50;
  size_t ri;

  g_MapData = (int)(intptr_t)mapbuf;
  for (ri = 0; ri < sizeof(radii) / sizeof(radii[0]); ++ri) {
    int rad = radii[ri];
    int dy;

    memset(mapbuf, 0, sizeof mapbuf);
    mapbuf[200] = 200; /* offset 800: map height */
    mapbuf[201] = 200; /* offset 804: map width */

    for (dy = -50; dy <= 50; ++dy) {
      int v6 = dy + 50; /* 0..100: distinct tile-record index per row */
      *(short *)((char *)mapbuf + 1534 + 40 * x + 2 * (y + dy)) = (short)v6;
      /* owner byte: mismatching within the poison radius, matching (0,
       * same as the unit's own faction below) outside it */
      *((unsigned char *)mapbuf + 854 + 31 * v6) =
          (dy >= -rad && dy <= rad) ? 200 : 0;
    }

    memset(unit, 0, sizeof unit);
    *(short *)(unit + 4) = (short)x;
    *(short *)(unit + 6) = (short)y;
    unit[2] = 0;
    TOUCH(UnitBattle_GetTargetCrowdingScale((int)(intptr_t)unit));
  }
  g_MapData = saved;
}

/* ---- MainMenu_RequestMultiplayerMenu: previously entirely uncovered
 * (0/5). It's a plain widget-button handler with no hidden branches --
 * forwards to UIWidget_PlayPressedReleaseAnimation and sets two globals. */
TEST(cov3_00_mainmenu, request_multiplayer_menu) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  TOUCH(MainMenu_RequestMultiplayerMenu((uintptr_t)widget));
  CHECK_EQ(g_MainMenuRequestedScreen, MAIN_MENU_REQUEST_MULTIPLAYER);
  CHECK_EQ(g_PlayGameMenuExitRequested, 1);
}

/* ---- Rules_CheckLiteralSlotValueConstraint: the existing cov13 test only
 * ever forces dword_51AAB0==0 (checking disabled -> immediate "return 1",
 * 4/12 covered). Enabling it (dword_51AAB0=1) reaches the
 * Rules_CheckFieldExprListAgainstConstraint call one line further in --
 * that call's second argument comes from a decompiler-lost register
 * (`*(_DWORD *)(v3 + 8)` with `v3` "possibly undefined"), so it reliably
 * faults a few instructions into evaluating that argument. Isolated in its
 * own TEST; still banks the newly-reached call-site line before that
 * happens. ---- */
TEST(cov3_00_rules, check_literal_slot_value_constraint_enabled) {
  static int a1buf[8];
  static int a2buf[8];
  int saved = g_CLIPS_StaticConstraintCheckingFlag;

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  g_CLIPS_StaticConstraintCheckingFlag = 1;
  TOUCH(Rules_CheckLiteralSlotValueConstraint(a1buf, (int)(intptr_t)a2buf));
  g_CLIPS_StaticConstraintCheckingFlag = saved;
}

/* ---- WorldMap_HandleSaveGameAction: previously deliberately never called
 * (see test_cov01.c) because it forwards into SaveSlotDialog_Run ->
 * DLXSpriteSet_Load, which faults deep inside a missing-resource-file path.
 * Per the updated per-test fork isolation, that's now safe to exercise
 * directly -- any lines reached before the fault are preserved, and other
 * tests are unaffected either way. ---- */
TEST(cov3_00_worldmap, handle_save_game_action) {
  TOUCH(WorldMap_HandleSaveGameAction(1, 0, 0.0));
}

/* ---- AI_FindBestStrategicTargetNearTile: 36/39 covered already (the
 * a5>=1 sweep loops are well exercised elsewhere); the remaining lines are
 * the a5<1 short-circuit that skips the whole nested-loop body entirely. */
TEST(cov3_00_ai, find_best_strategic_target_a5_zero) {
  CHECK_EQ(AI_FindBestStrategicTargetNearTile(0, 0, 5, 5, 0), -1);
}
TEST(cov3_00_ai, find_best_strategic_target_a5_negative) {
  CHECK_EQ(AI_FindBestStrategicTargetNearTile(0, 0, 5, 5, -3), -1);
}

/* ---- CRT_FormatPaddedHexDigits: pure buffer-formatting helper; drive both
 * the "shift existing digits right, then zero-pad the rest" loop (a3 wider
 * than the formatted digit count) and the "digit count already fills a3"
 * case where the zero-pad loop's `while (result >= 0)` is never entered. */
TEST(cov3_00_crt, format_padded_hex_digits_exact_fit) {
  static char buf[32];
  memset(buf, 0xAA, sizeof buf);
  TOUCH(CRT_FormatPaddedHexDigits(0x1234, buf, 4));
}
TEST(cov3_00_crt, format_padded_hex_digits_needs_padding) {
  static char buf[32];
  memset(buf, 0xAA, sizeof buf);
  TOUCH(CRT_FormatPaddedHexDigits(0, buf, 8));
}
TEST(cov3_00_crt, format_padded_hex_digits_small_value_more_padding) {
  static char buf[32];
  memset(buf, 0xAA, sizeof buf);
  TOUCH(CRT_FormatPaddedHexDigits(5, buf, 6));
}

/* ---- Rules_ApplyPatternKeywordFlags: the decompiled function has no real
 * parameters (its keyword-char dispatch is driven by a register the
 * decompiler never recovered, "variable 'v2' possibly undefined"), and even
 * its lone callee Rules_CreateLHSParseNode has the exact same class of lost
 * register a few lines into its body (crashes dereferencing it, even after
 * bootstrapping the memory pools so the allocation itself succeeds). None
 * of the individual `case` bodies are reachable from any external caller as
 * a result. Bootstrapping first and calling it still banks whatever
 * additional entry lines that unlocks over the previous no-bootstrap
 * baseline (which faulted immediately on a NULL free-list dereference). */
TEST(cov3_00_rules, apply_pattern_keyword_flags_bootstrapped) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ApplyPatternKeywordFlags());
}
