/* cov4 batch 03: final-pass precise-line coverage lift for a grab-bag of
 * mostly-covered functions (see scratchpad/cov4_batches/cov4_03.json). Each
 * test targets the EXACT clash95.c line numbers listed as still-uncovered in
 * that batch file, read directly out of clash95.c around each function's
 * start_line/end_line.
 *
 * Every test runs isolated in its own forked child (per tests/unit/test_all.c
 * running each TEST under fork()+alarm(8)), so calls that crash, exit(), or
 * spin are safe -- we chase genuine extra line coverage of the *target*
 * function rather than avoiding risk in whatever it calls further down.
 * Buffers whose address is threaded through a narrowed 32-bit int/_DWORD
 * field are declared `static` so they land in the low .bss image instead of
 * a stack address that would truncate to garbage on this 64-bit -no-pie
 * build. */

/* ---- shared helper: a single/pair "argument node" chain compatible with
 * Rules_RtnArgCount/Lexer_TokenExpect (which read *(dword_51A960+6) as the
 * head node, and each node's +10 offset as the "next" link) and with
 * Parser_ParseForm's tag-driven dispatch (tag stored as a `short` at +0, a
 * payload pointer at +2, matching cov3_07_arg1/cov3_02_arg_node_init in the
 * earlier batches). `value_ptr` is expected to point at a zeroed buffer whose
 * DWORD at byte offset 16 holds the actual scalar payload (int/pointer). */
static void cov4_03_arg_node_init(unsigned char *node, short type_tag,
                                   void *value_ptr, unsigned char *next_node) {
  memset(node, 0, 32);
  *(short *)(node + 0) = type_tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)value_ptr;
  *(_DWORD *)(node + 10) = (_DWORD)(intptr_t)next_node;
}

static void cov4_03_install_arg_chain(unsigned char *argnode,
                                       unsigned char *head_node) {
  memset(argnode, 0, 32);
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)head_node;
  dword_51A960 = (int)(intptr_t)argnode;
}

/* =========================================================================
 * Lexer_ReadToken (115848-115911, uncovered 115863/115865/115867/115869/
 * 115871/115873/115877/115879): the append loop's `for` reads characters via
 * Lexer_PeekChar/Lexer_SkipChar against whatever text router IO_OpenTextSource
 * installed at dword_51A604/dword_51A608 (same mechanism test_cov14.c already
 * uses successfully). Each `if (i == X) break;` guard is independently
 * reachable by making that character the very first byte of the stream (so
 * none of the earlier guards fire first); a plain a1 router key + zeroed
 * output-flag slot is all Lexer_ReadToken needs. The remaining guard
 * (IsTable[(i+1)] & 8) == 0 -- line 115879 -- needs a first byte that is
 * none of the special punctuation, isn't the outer loop's own terminator
 * (60, '<'), and whose IsTable[i+1] entry lacks bit 0x8; IsTable[2] (for
 * i==1, a raw SOH control byte) is '\x01', which qualifies. ========================= */
static void cov4_03_read_token_case(const char *label, const char *text,
                                     int text_len) {
  static int outflag;
  static int case_id;
  /* Must be `static`: IO_OpenTextSource does `strlen((const char *)a1)` on
   * this router-key argument, i.e. it round-trips as a REAL string pointer
   * (not just an opaque int token) through the narrowed 32-bit `int a1`
   * field. A stack address would truncate to garbage on this 64-bit
   * -no-pie build; static/global storage sits at a low, stable address that
   * survives the round trip (same convention as the rest of this file). */
  static char route[64];
  ++case_id;
  snprintf(route, sizeof route, "cov4_03_lex_%s_%d", label, case_id);
  outflag = 0;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(IO_RegisterStringRouter());
  TOUCH(IO_OpenTextSource((int)(intptr_t)route, text, text_len, 0));
  g_TokenBuf = 0;
  g_TokenLen = 0;
  g_TokenCap = 0;
  TOUCH(Lexer_ReadToken((int)(intptr_t)route, 0, (_DWORD *)&outflag, 0));
}

TEST(cov4_03_lexreadtoken, breaks_on_double_quote) {
  cov4_03_read_token_case("dquote", "\"ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_open_paren) {
  cov4_03_read_token_case("lparen", "(ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_close_paren) {
  cov4_03_read_token_case("rparen", ")ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_ampersand) {
  cov4_03_read_token_case("amp", "&ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_pipe) {
  cov4_03_read_token_case("pipe", "|ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_tilde) {
  cov4_03_read_token_case("tilde", "~ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_semicolon) {
  cov4_03_read_token_case("semi", ";ab", 3);
}

TEST(cov4_03_lexreadtoken, breaks_on_non_appendable_char) {
  /* byte value 1 (SOH): not '<'(60) so the outer for-loop condition is still
   * true, not any of the punctuation break chars, and IsTable[1+1] == 1,
   * whose bit 0x8 is clear -> hits the final "not appendable" break. */
  cov4_03_read_token_case("nonappend", "\x01" "ab", 3);
}

/* =========================================================================
 * Deffacts_CloseCodeFiles (161388-161415, uncovered 161401/161402/161403):
 * fully deterministic and crash-free once traced through
 * Rules_ConstructCodeFileClose: with a5==0 (the literal 0 this wrapper always
 * passes) the "v8 > *a2" branch is unreachable (both operands equal a1's own
 * a4 argument, so `>` is always false), a5==0 skips the "*a5=0" write, and
 * `!result` is false because `result` is set to `a2` (this test's nonzero
 * "file handle" int) -- so it falls straight through to the harmless
 * Output_WriteFormatted/fclose_ tail (fclose_ is the compat stub, which
 * safely no-ops for any handle that isn't in its registered-stream table)
 * and returns cleanly. That lets us reach both outcomes of
 * Deffacts_CloseCodeFiles's own `if (!a1)` guard on the line right after. ==== */
TEST(cov4_03_deffacts, close_code_files_a1_zero_returns_early) {
  TOUCH(Deffacts_CloseCodeFiles(0, 4242 /* fake nonzero file handle */, 0, 0));
}

TEST(cov4_03_deffacts, close_code_files_a1_nonzero_falls_through) {
  TOUCH(Deffacts_CloseCodeFiles(9999 /* fake nonzero a1 handle */,
                                 4242 /* fake nonzero a2 handle */, 0, 0));
}

/* =========================================================================
 * AI_FindBestStrategicTargetNearTile (72853-72925, uncovered 72919/72920/
 * 72921): gameData is a plain, zero-valued `int` base (never actually mapped
 * memory); the established trick (see test_cov2_01.c's
 * Map_ClassifyFogOfWarOverlayForPlayer coverage) is to repoint the writable
 * `gameData` global itself at a real owned static buffer, then populate the
 * map-width/height bounds (offset 140000/140004) and every gameData-relative
 * field the callee chain touches. AI_EvaluateStrategicTargetAtTile's tile
 * lookup (TILE_INDEX) needs a value > 0x1F4 to take the "special tile"
 * branch, and MapTile_HasHiddenTreasure needs the word at
 * gameData+1400*row+14*col to be 752 or 755 to report a treasure (v12 = 3).
 * Whether that candidate actually becomes the tracked "best" (and so
 * whether v11 ends up 3, landing on the `v11 == 3 || v11 == 4` -> `return
 * 100 * v11` lines) depends on the score comparison
 * `v15 = (double)(int)_CHP(v16, a1);` -- v16 there is a genuinely
 * decompiler-uninitialized stack slot (the real x87 return value of
 * AI_CalcStrategicPriorityScore got lost by the decompiler), so we cannot
 * prove statically which way that comparison goes; use TOUCH rather than
 * asserting an exact return value here. Getting past the gameData bounds
 * checks and into the treasure branch at all is still new coverage of this
 * region regardless of the final score comparison's outcome. ============ */
TEST(cov4_03_ai, find_best_strategic_target_hits_treasure_branch) {
  static char gd[650000];
  int saved = gameData;
  int row, col;

  memset(gd, 0, sizeof gd);
  *(int *)(gd + 140000) = 200; /* map width */
  *(int *)(gd + 140004) = 200; /* map height */
  for (row = 45; row <= 55; ++row) {
    for (col = 45; col <= 55; ++col) {
      *(unsigned __int16 *)(gd + 556374 + 200 * row + 2 * col) = 999; /* TILE_INDEX word > 0x1F4 */
      *(unsigned __int16 *)(gd + 1400 * row + 14 * col) = 752;        /* MapTile_HasHiddenTreasure marker */
    }
  }
  gameData = (int)(intptr_t)gd;

  TOUCH(AI_FindBestStrategicTargetNearTile(-1, -1, 50, 50, 1));

  gameData = saved;
}

/* =========================================================================
 * CRT_TzYearStartsInDaylightTime (145223-145248, uncovered 145238/145241):
 * setting a1[8] (offset 32) nonzero takes the direct "goto LABEL_6" path
 * (skipping the a1[4]-vs-*(a2+32) comparisons entirely), reaching the first
 * CRT_TzRuleDayOfYear(a1, a3) call with fully real, owned-buffer arguments --
 * a deterministic, crash-free way to cover line 145238. The second
 * CRT_TzRuleDayOfYear call on the very next line passes a genuinely
 * decompiler-uninitialized `v7` pointer as its first argument; we still
 * attempt it (isolated by the harness), since reaching that call at all is
 * new coverage of line 145241 regardless of what happens inside. ========= */
TEST(cov4_03_crt, tz_year_starts_in_daylight_goto_label6) {
  static _DWORD a1buf[16];
  static _DWORD a2buf[16];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  a1buf[8] = 1; /* nonzero -> direct goto LABEL_6, bypassing a1[4]/*(a2+32) */
  TOUCH(CRT_TzYearStartsInDaylightTime(a1buf, (int)(intptr_t)a2buf, 0));
}

/* =========================================================================
 * PlayGameMenu_HandleCloseButton (65027-65040, uncovered 65033/65034): a
 * plain two-line wrapper (play an animation, set an exit-request flag, return
 * the animation call's result); nothing gates it, so a bare call reaches
 * both remaining lines deterministically. ================================ */
TEST(cov4_03_playgamemenu, handle_close_button) {
  TOUCH(PlayGameMenu_HandleCloseButton(0));
}

/* =========================================================================
 * BuildingEconomyDialog_SetExitSignal (44264-44277, uncovered 44271): the
 * trailing fprintf is gated on Diagnostics_IsWorldMapClickTraceEnabled(),
 * which (on its very first call in the process) reads env var
 * CLASH95_TRACE_WORLD_CLICK and latches the result in a function-local
 * static -- set it before the first call in this forked child to force the
 * "enabled" branch and reach the fprintf line. ============================ */
TEST(cov4_03_buildingeconomy, set_exit_signal_trace_enabled) {
  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 1);
  TOUCH(BuildingEconomyDialog_SetExitSignal(0, 0));
}

/* =========================================================================
 * Cheat_RevealMapForCurrentPlayer (69021-69029, uncovered 69024): a plain
 * two-call wrapper; the only line missing is its own final return, reached by
 * simply calling it (both callees are direct-write world-map functions with
 * no argument-driven guard here). ========================================= */
TEST(cov4_03_cheat, reveal_map_for_current_player) {
  TOUCH(Cheat_RevealMapForCurrentPlayer());
}

/* =========================================================================
 * Unit_BuildShotAnimSpritePath (27969-28069, uncovered 28001): the first
 * copy loop's `if (!v5) break;` fires only when the *current* source byte
 * (aUnits_at[0]) is already NUL. aUnits_at is a plain (non-const) global
 * char[10] initialized to "units_at\\", so its first byte is never 0 in the
 * normal build -- temporarily zero it out (save/restore) to force the
 * immediate-break path, which also conveniently avoids ever reaching the
 * later UnitType_GetResourceKey-driven loops. ============================= */
TEST(cov4_03_unit, build_shot_anim_sprite_path_immediate_empty_prefix) {
  static char out[64];
  char saved[10];
  memcpy(saved, aUnits_at, sizeof saved);
  memset(out, 0, sizeof out);
  aUnits_at[0] = 0;
  TOUCH(Unit_BuildShotAnimSpritePath(out, 0, 0));
  memcpy(aUnits_at, saved, sizeof saved);
}

/* =========================================================================
 * Rules_Log (93895-93906, uncovered 93901): Rules_StringToFact parses a
 * genuine fact string via IO_OpenStringSource/Rules_ParseAssertRHSPattern; in
 * CLIPS-style engines a simple parenthesized symbol list is a valid "implied"
 * fact even with no deftemplate registered, so after bootstrapping the
 * reserve arena and atom tables it should return a real (non-NULL) fact
 * pointer, driving the `if (result) return
 * Rules_AssertFactDriver(result, a3);` line. Isolated in case the deeper
 * assert path still needs more engine bring-up than this. ================= */
TEST(cov4_03_rules, log_simple_fact_string) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_Log("(cov4-03-fact a b c)", 0, 0.0));
}

/* =========================================================================
 * Rules_HostRemoveFile (125320-125339, uncovered 125331): same
 * Lexer_TokenExpect(1) + Rules_GetFileNameArg shape already exercised for
 * Rules_LoadStarCommand/itself in earlier batches (test_cov3_07.c). Feed a
 * real one-node argument chain whose value node's tag (3, STRING) is one of
 * Parser_ParseForm's *safe* dispatch cases (no decompiler-undefined locals
 * touched on that path), so Rules_GetFileNameArg resolves a genuine
 * (nonexistent-on-disk) path string and `result` comes back non-NULL,
 * reaching the `return Rules_BloadDeleteFile(v4, v3);` line -- v4/v3
 * themselves are decompiler-lost registers, so what happens *inside*
 * Rules_BloadDeleteFile is not controllable, but the call line itself is
 * reached deterministically. ============================================= */
TEST(cov4_03_rules, host_remove_file_filename_resolves) {
  static unsigned char argnode[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov4_03_missing_bload_file.bin";
  int saved = dword_51A960;
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (int)(intptr_t)path; /* offset+16 payload slot */
  cov4_03_arg_node_init(node, 3, valnode, 0);
  cov4_03_install_arg_chain(argnode, node);
  TOUCH(Rules_HostRemoveFile(0.0));
  dword_51A960 = saved;
}

/* =========================================================================
 * Rules_MathParseSingleArg (129414-129432, uncovered 129423/129425/129426/
 * 129428) and Rules_MathSech (129792-129807, uncovered 129801): both route
 * through Lexer_ParseValueList, whose very first check
 * (`a3 == *(_DWORD*)(v7 + 4)`, evaluated unconditionally for every call
 * regardless of which branch is ultimately taken) dereferences a genuine
 * decompiler-uninitialized local -- the exact "known hard ceiling" shape
 * called out for this batch. Attempt once with a real one-node INTEGER
 * argument (the shape that would reach the success path if that dereference
 * happened to be benign); isolated by the harness if it faults instead. ==== */
TEST(cov4_03_rulesmath, math_parse_single_arg_real_integer_arg) {
  static unsigned char argnode[32], node[32];
  static _DWORD valnode[8];
  double out = 0.0;
  int saved = dword_51A960;
  memset(valnode, 0, sizeof valnode);
  valnode[4] = 7; /* offset+16 payload: integer value 7 */
  cov4_03_arg_node_init(node, 1 /* INTEGER */, valnode, 0);
  cov4_03_install_arg_chain(argnode, node);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathParseSingleArg(&out, 0, 0.0));
  TOUCH(Rules_MathSech(0, 0, 0, 0.0));
  dword_51A960 = saved;
}

/* =========================================================================
 * Class_SlotExistPCommand (172416-172455, uncovered 172431/172433-172436/
 * 172438-172440/172442/172444/172445/172447): the whole remaining body sits
 * behind Class_CheckSlotExists -> Class_ParseClassReference ->
 * Lexer_ParseValueList, i.e. the same hard-ceiling call chain as above, twice
 * over (Class_ParseClassReference itself makes two Lexer_ParseValueList
 * calls). Attempt once with a real two-node SYMBOL argument chain (class
 * name, then "inherit" keyword) bootstrapped like the other Lexer/atom-table
 * driven tests in this file; isolated if it faults inside
 * Lexer_ParseValueList's own undefined-register dereference before ever
 * reaching Class_CheckSlotExists's caller-visible branches. ============== */
TEST(cov4_03_class, slot_exist_p_command_real_two_node_chain) {
  static unsigned char argnode[32], node1[32], node2[32];
  static _DWORD classval[8], inheritval[8];
  static const char *class_name = "Cov4_03FakeClass";
  static int a1out[8];
  int saved = dword_51A960;
  memset(classval, 0, sizeof classval);
  memset(inheritval, 0, sizeof inheritval);
  memset(a1out, 0, sizeof a1out);
  classval[4] = (int)(intptr_t)class_name;
  inheritval[4] = (int)(intptr_t)"inherit";
  cov4_03_arg_node_init(node2, 2 /* SYMBOL */, inheritval, 0);
  cov4_03_arg_node_init(node1, 2 /* SYMBOL */, classval, node2);
  cov4_03_install_arg_chain(argnode, node1);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Class_SlotExistPCommand(a1out, 0.0));
  dword_51A960 = saved;
}

/* =========================================================================
 * Rules_ExpressionConstraintsCompatible (116270-116299, uncovered 116279-
 * 116283/116285/116286/116290/116291): Rules_BuildLHSNodeFromToken(a1) only
 * avoids its own undefined-register path when *a1 is one of {11,12,13,14,15,
 * 16} (the "safe" tag list that goes straight to Rules_CreateLHSParseNode());
 * giving it such a token lets us get *past* that first call cleanly. Past
 * that point, though, v3/v4/v5 (fed into AST_DecrementNodeRefCount /
 * Rules_ConstraintIsUnmatchable) are themselves decompiler-lost registers
 * with no way to influence them from here -- attempt once and let the
 * harness isolate whatever happens. ======================================= */
TEST(cov4_03_rules, expression_constraints_compatible_safe_token_tag) {
  static __int16 tokbuf[8];
  memset(tokbuf, 0, sizeof tokbuf);
  tokbuf[0] = 12; /* one of Rules_BuildLHSNodeFromToken's safe dispatch tags */
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_ExpressionConstraintsCompatible(tokbuf));
}

/* =========================================================================
 * Rules_WriteConstructHeaderToCode (133135-133174, uncovered 133152-133157/
 * 133159): every remaining line reads a decompiler-lost register
 * (v9/v10/v11/...) as either a raw pointer dereference (`*v9` feeding
 * Compiler_WriteSymbolReference on the very first statement) or an
 * Output_WriteFormatted argument; there is no input-controllable path around
 * the initial `*v9` dereference. Attempt once with plausible-looking
 * arguments; isolated if it faults immediately. =========================== */
TEST(cov4_03_rules, write_construct_header_to_code_attempt) {
  static _DWORD a2buf[8];
  memset(a2buf, 0, sizeof a2buf);
  TOUCH(Rules_WriteConstructHeaderToCode(0, (int)(intptr_t)a2buf, 1, 0, 0, 0));
}

/* =========================================================================
 * Defgeneric_GetMethodRestrictionsCommand (119794-119816, uncovered 119803-
 * 119805/119807/119811): gated entirely behind the very first
 * Lexer_ParseValueList call in the `if` chain, which hits the same
 * unconditional undefined-register dereference described above before its
 * result is even used. Attempt once with a real SYMBOL argument (matching
 * the shape earlier batches used for this same function). ================ */
TEST(cov4_03_defgeneric, get_method_restrictions_command_real_symbol) {
  static unsigned char argnode[32], node[32];
  static _DWORD symval[8];
  static _DWORD out[16];
  static const char *generic_name = "Cov4_03FakeGeneric";
  int saved = dword_51A960;
  memset(symval, 0, sizeof symval);
  memset(out, 0, sizeof out);
  symval[4] = (int)(intptr_t)generic_name;
  cov4_03_arg_node_init(node, 2 /* SYMBOL */, symval, 0);
  cov4_03_install_arg_chain(argnode, node);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(out, 0, 0.0));
  dword_51A964 = 0;
  dword_51A960 = saved;
}

/* =========================================================================
 * UnitStack_CopyFromTemplate (27081-27103, uncovered 27093-27096): the
 * second `_wcpp_4_copy_array__(v7)` call (an identity stub, see
 * compat/decomp_runtime_stubs.c) reads a genuine decompiler-uninitialized
 * local `v7`, so `v4` (its result) is whatever garbage register/stack value
 * happened to be live; the following `*(_BYTE*)(v4+400) = ...` write depends
 * on that unpredictable address. Both existing earlier-batch attempts
 * (test_cov02.c, test_cov2_00.c) already documented the same fault; try once
 * more with fresh static buffers in case different preceding stack content
 * changes what v7 resolves to. ============================================ */
TEST(cov4_03_unitstack, copy_from_template_attempt) {
  static unsigned char a1buf[2048];
  static unsigned char a2buf[2048];
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  TOUCH(UnitStack_CopyFromTemplate((int)(intptr_t)a1buf, (int)(intptr_t)a2buf,
                                    (int)(intptr_t)a1buf));
}

/* =========================================================================
 * AST_GetHashedNodeIndex (115497-115512, uncovered 115505/115506/115508):
 * the a1==NULL early-return is already covered elsewhere; reaching the
 * remaining lines needs AST_FindHashedNodeChain(a1, &v3) to return without
 * crashing, but that function's very first write (`*v5 = v4;`, right after
 * hashing the node) targets a genuinely decompiler-uninitialized `v5`
 * pointer -- a hard-ceiling dereference with no way to steer it from a
 * caller. Attempt once with a plausible small AST-node-shaped buffer. ===== */
TEST(cov4_03_ast, get_hashed_node_index_nonnull_attempt) {
  static __int16 node[16];
  memset(node, 0, sizeof node);
  Mem_InitReserveBlock(0, 0);
  TOUCH(AST_GetHashedNodeIndex(node));
}

/* =========================================================================
 * Rules_ParseStandardConstraintAttribute (178476-178534, uncovered 178499/
 * 178503/178514): Rules_TestConstraintAttributeParsedFlag's *only*
 * input-controllable branch is `a1 == "type"` (every other name compares
 * against the function's own decompiler-lost registers); giving it "type"
 * with the flag's bit0 already clear makes it return 0 ("not yet parsed"),
 * which is required to even reach this function's `else` branch at all. Once
 * inside, though, the first real dispatch check literally compares a
 * hard-coded constant 0 (not our a2!) against "range" (`strcmp_(0,
 * aRange_0)`), so the "range/cardinality" line (178499) can only be reached
 * by the second half of that `||` -- itself a decompiler-lost register -- and
 * the "type" (178503) / "allowed values" (178514) lines are gated the same
 * way. strcmp_ itself (CompatSafeStrcmp) is crash-safe for any garbage
 * pointer, so this at least exercises the reachable comparison chain without
 * faulting, even though none of our three specific target lines are
 * reachable through deliberate input. ===================================== */
TEST(cov4_03_rules, parse_standard_constraint_attribute_type_not_parsed) {
  static _BYTE flags[8];
  memset(flags, 0, sizeof flags);
  flags[0] = 0; /* bit0 clear -> "type" not yet parsed -> takes the else branch */
  TOUCH(Rules_ParseStandardConstraintAttribute((char *)"unused", "type", flags,
                                                0, 0));
}

/* =========================================================================
 * Rules_Dependencies (111290-111310, uncovered 111301/111302): reaching
 * these needs Rules_ResolveFactOrInstanceArg to return without crashing, but
 * that function's very first use of its own Rules_RtnUnknown result
 * (`v6 = *(_DWORD *)(v5 + 4);`) dereferences a decompiler-uninitialized `v5`
 * unconditionally -- another hard-ceiling case. Attempt once with a real
 * one-node argument chain (matching the Lexer_TokenExpect(1) shape) so at
 * least the guard line executes for real. ================================= */
TEST(cov4_03_rules, dependencies_real_one_node_chain) {
  static unsigned char argnode[32], node[32];
  static _DWORD valnode[8];
  int saved = dword_51A960;
  memset(valnode, 0, sizeof valnode);
  valnode[4] = (int)(intptr_t)"Cov4_03FakeInstance";
  cov4_03_arg_node_init(node, 2 /* SYMBOL */, valnode, 0);
  cov4_03_install_arg_chain(argnode, node);
  TOUCH(Rules_Dependencies(0.0));
  dword_51A960 = saved;
}

/* =========================================================================
 * CRT_RegisterFinalizer (104745-104764, uncovered 104756): the unconditional
 * `*v3 = g_CrtFinalizerListHead;` write (v3 a decompiler-lost pointer) sits
 * directly before the target return line, with no controllable path around
 * it. Attempt once with plausible-looking arguments. ====================== */
TEST(cov4_03_crt, register_finalizer_attempt) {
  static __lock lockbuf;
  memset(&lockbuf, 0, sizeof lockbuf);
  TOUCH(CRT_RegisterFinalizer(0, &lockbuf, 0));
}

/* =========================================================================
 * Instance_MessageModifyInstanceFunction (136485-136500, uncovered 136493):
 * the line right before it, `Instance_ActiveMessageModifyInstanceFunction(v1,
 * v2);`, passes two entirely decompiler-lost locals (v1/v2, never assigned
 * anywhere in this function) as its own arguments -- a hard-ceiling
 * dereference risk before our target line is ever reached. Attempt once. == */
TEST(cov4_03_instance, message_modify_instance_function_attempt) {
  TOUCH(Instance_MessageModifyInstanceFunction(0.0));
}

/* =========================================================================
 * Defgeneric_ClearDefgenericsReady (161518-161538, uncovered 161530): needs
 * Rules_IsBloaded() (a plain global read) to differ from the function's own
 * decompiler-lost `v1` comparison target to even enter the loop, and then
 * needs Defgeneric_GetNextInModule(0) (an empty-by-default module/class
 * enumeration) to return non-zero to run the loop body even once -- neither
 * of which this test can force without a much deeper defgeneric-registration
 * bring-up than fits this batch. Attempt a bare bootstrapped call. ========= */
TEST(cov4_03_defgeneric, clear_defgenerics_ready_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Defgeneric_ClearDefgenericsReady());
}

/* =========================================================================
 * Rules_BuildSlotUnboundTestExpression (183797-183808, uncovered 183803):
 * a straight-line two-call wrapper ending in `return v2;` where v2 is a
 * decompiler-lost local never assigned in this function -- the return value
 * itself is unpredictable, but reaching the line at all just needs both
 * AST_NewNode(0, 0) and Rules_BuildSlotConstraintBitmapTestNode(0, a1) to
 * complete without faulting, which needs the reserve-block arena bootstrapped
 * first (both allocate AST/constraint nodes from it). ===================== */
TEST(cov4_03_rules, build_slot_unbound_test_expression_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BuildSlotUnboundTestExpression(0));
}
