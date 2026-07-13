/* cov4 batch 00: precise-line coverage for the functions listed in
 * scratchpad/cov4_batches/cov4_00.json. Each section targets the EXACT
 * uncovered clash95.c line numbers given for that function. Buffers whose
 * address is threaded through a narrowed 32-bit int/_DWORD field are
 * declared `static` (64-bit -no-pie build; a stack address truncates to
 * garbage when squeezed through such a field). Every TEST runs in its own
 * forked child under the harness's fork()+alarm(8), so a crash/hang inside a
 * callee is safe and simply caps how much of the target function's own body
 * got reached before it happened.
 *
 * Investigation notes (verified with a standalone scratch harness that links
 * clash95.c + platform_sdl_runtime.c + compat/decomp_runtime_stubs.c the
 * same way the coverage CMake target does, run under gdb):
 *
 * - UnitBattle_CountAdjacentEnemies walks dword_514500/dword_514504, each
 *   recovered as a single-element weak array; indices 2..14 read whatever
 *   sits next to them in .data. In the scratch build all 8 neighbor deltas
 *   collapsed to only two distinct dy values (one shared by 6 of the 8
 *   entries), making the achievable adjacent-enemy counts a fixed set
 *   {0,1,6,7} regardless of tile/width/height -- 3,4,5 are not reachable via
 *   any input. (Matches test_cov2_04.c's independent conclusion.)
 * - Rules_GetFileNameArg's success path goes through Rules_RtnUnknown()
 *   DIRECTLY (not Lexer_ParseValueList), so building a one-node STRING
 *   argument at dword_51A960+6 (the technique test_cov4_02.c already proved
 *   out for Rules_BatchStarCommand) lets it return a real filename pointer
 *   without hitting the decompiler-lost-variable crash that blocks the
 *   Lexer_ParseValueList family.
 * - Functions gated on Lexer_ParseValueList / Rules_MathParseSingleArg
 *   (Rules_IntegerFunction, Rules_MathCoth, Rules_CoshBuiltin, Rules_HostSeed)
 *   remain a confirmed hard ceiling: Lexer_ParseValueList's very first
 *   post-Rules_RtnUnknown line unconditionally dereferences a decompiler-lost
 *   local ('v7') before it can ever return 1 (test_cov3_04.c / test_cov4_02.c
 *   already document this).
 * - Lexer_TokenExpect's own 'v2' is a genuinely lost register value (not
 *   derived from any argument or global we can set) -- verified via gdb that
 *   it holds arbitrary stack garbage unrelated to the arg-count machinery,
 *   so its {1,2}-valued branches cannot be steered from a normal C caller.
 */

/* =========================================================================
 * UnitBattle_GetTargetCrowdingScale (41757-41785, uncovered 41768-41779):
 * switch over UnitBattle_CountAdjacentEnemies(a1)'s return value. As noted
 * above, only counts in {0,1,6,7} are reachable given this build's
 * dword_514500/514504 contents, so only the `default:` case (128, count not
 * in 0-5) is coverable here; cases 3/4/5 (lines 41768-41776) are a confirmed
 * hard ceiling. Sweep a range of tile positions/widths anyway in case the
 * real coverage binary's adjacent .data contents differ from this
 * investigation build. */
TEST(cov4_00_crowding, get_target_crowding_scale_sweep) {
  static _DWORD mapbuf[4096];
  static unsigned char unit[8];
  int saved532048 = g_MapData;
  int tx, ty, w;

  memset(mapbuf, 0, sizeof mapbuf);
  mapbuf[200] = 500; /* offset 800: map height */
  mapbuf[201] = 500; /* offset 804: map width  */
  g_MapData = (int)(intptr_t)mapbuf;

  for (w = 0; w < 6; ++w) {
    for (tx = 0; tx < 4; ++tx) {
      for (ty = 0; ty < 4; ++ty) {
        memset(unit, 0, sizeof unit);
        *(short *)(unit + 4) = (short)(tx * 37 + w);
        *(short *)(unit + 6) = (short)(ty * 53 + w);
        unit[2] = (unsigned char)(tx + ty + w + 1);
        TOUCH(UnitBattle_GetTargetCrowdingScale((int)(intptr_t)unit));
      }
    }
  }
  g_MapData = saved532048;
}

/* =========================================================================
 * Rules_ParseDefruleRHS (153895-153924, uncovered 153907-153923): only
 * reaches its own body past `if (result)` when Parser_ParseProgram(a1, v2, 1)
 * returns nonzero, but `v2` here is Rules_ParseDefruleRHS's own decompiler-
 * lost local, passed straight through as Parser_ParseProgram's `unsigned int
 * *a2` output-struct pointer -- an uncontrollable garbage address that gets
 * dereferenced (`*a2`) as literally the first statement inside
 * Parser_ParseProgram. Confirmed via gdb to fault there before any return.
 * Hard ceiling; attempted once per the harness instructions. */
TEST(cov4_00_defrulerhs, parse_defrule_rhs_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_ParseDefruleRHS(0));
}

/* =========================================================================
 * Instance_FindByName (101755-101792, uncovered 101777-101787): the
 * qualifier_length>1 ("Module::name") branch calls Rules_ExtractModuleName,
 * whose own decompiler-lost locals ('v3','v4') are passed directly into
 * strncpy_(v4, v3) as BOTH the destination and source pointers -- confirmed
 * via gdb to fault inside strncpy_ on the first write, before
 * Rules_ExtractModuleName can return. That keeps every line past the call
 * (101777 onward) out of reach regardless of what name string we supply.
 * Hard ceiling; attempted once with a qualified name so the call is at least
 * reached. */
TEST(cov4_00_instfindname, find_by_qualified_name_attempt) {
  static _DWORD a1buf[16];
  static unsigned char name[32];

  memset(a1buf, 0, sizeof a1buf);
  strcpy((char *)name, "SomeModule::SomeInstance");
  a1buf[4] = (int)(intptr_t)name; /* *(a1+16): the name-text pointer */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Instance_FindByName((int)(intptr_t)a1buf));
}

/* =========================================================================
 * Rules_MathCoth (129831-129855, uncovered 129843-129851): all remaining
 * lines are gated on Rules_MathParseSingleArg() returning nonzero, which
 * requires Lexer_ParseValueList to succeed -- a confirmed hard ceiling (see
 * file header). Attempted once. */
TEST(cov4_00_mathcoth, math_coth_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0));
}

/* =========================================================================
 * Definstances_DeleteRecord (166788-166806, uncovered 166798-166805): once
 * Rules_IsBloaded() is forced false (dword_51A1AC=0), the function reads its
 * own decompiler-lost local 'v0' -- genuinely uninitialized, but (per the
 * harness's fork isolation) safe to just try. Definstances_IsDeletable()
 * has the exact same 'v0'-is-lost pattern internally. Attempted with the
 * bload flag cleared so at least the early `Rules_IsBloaded()` truthy
 * shortcut is bypassed. */
TEST(cov4_00_definstdel, delete_record_attempt) {
  int saved = g_Rules_FactsBloadedFlag;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  g_Rules_FactsBloadedFlag = 0;
  TOUCH(Definstances_DeleteRecord());
  g_Rules_FactsBloadedFlag = saved;
}

/* =========================================================================
 * ObjectsCompiler_CloseConstructFileGroup (168959-168985, uncovered
 * 168979-168984): a straight-line 8-iteration do/while over a2..a2+8 calling
 * Rules_ConstructCodeFileClose(v7, &v9, a3, &v10, a2, a4) each time, with the
 * uncovered lines being the loop's own tail (result=v12+12; ++v6; v12+=12).
 * Rules_ConstructCodeFileClose(0, ptr-to-0, 0, ptr, a5, a6): with a3(0) not
 * greater than *a2(0) it skips the first branch; with a5 (our a2 array,
 * nonnull) it clears *a5=0; with `result`(v7, from our all-zero a1 array)
 * falsy it enters the `if (!result)` block, but a6 pointing at a zeroed
 * 4-word buffer makes `*(_DWORD *)a6` (dereferenced as `v9`) read 0, hitting
 * the function's own safe early `return 0;` before any of its file-open/
 * format-write paths (which need real engine I/O state) are touched. That
 * makes every one of the 8 calls return cleanly, covering the full loop
 * tail on every iteration. */
TEST(cov4_00_objcompclose, close_construct_file_group_all_iterations) {
  static int a1buf[16];
  static _DWORD a2buf[16];
  static _DWORD filectx[8];
  int r;

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(filectx, 0, sizeof filectx); /* filectx[0] == 0 -> Rules_ConstructCodeFileClose's safe early return */

  r = ObjectsCompiler_CloseConstructFileGroup(a1buf, a2buf, 0, (int)(intptr_t)filectx);
  CHECK_EQ(r, (int)(intptr_t)filectx + 8 * 12);
}

/* =========================================================================
 * Rules_SaveCommand (123225-123256, uncovered 123239,123241,123245,123246)
 * and Rules_DribbleOnCommand (122655-122666, uncovered 122664): both gate on
 * Lexer_TokenExpect(1)!=-1 then Rules_GetFileNameArg(1,...) returning a real
 * filename pointer. Rules_GetFileNameArg's success path goes through
 * Rules_RtnUnknown() directly (no Lexer_ParseValueList), so wiring a
 * one-node STRING(tag=3) argument list at dword_51A960 -- the same fixture
 * test_cov4_02.c already proved out for Rules_BatchStarCommand's identical
 * Rules_GetFileNameArg dependency -- lets it hand back a real (bogus,
 * nonexistent-path) filename. A nonexistent-directory path makes the
 * downstream file-open fail cleanly in both cases:
 *  - Rules_Save's own success path would fall through to a decompiler-lost
 *    'v4' passed to fclose_() when its internal save-callback list is empty
 *    (dword_51A188==0, the default), so we specifically want Rules_Save to
 *    FAIL (open error) to stay on its safe `return result;` (falsy) path --
 *    that covers Rules_SaveCommand's `if(Rules_Save(...))` test (123239) and
 *    its else branch (123245-123246); the truthy branch (123241) would need
 *    Rules_Save to survive that fclose_ hazard and is left as a hard
 *    ceiling.
 *  - Dribble_TurnOn handles both its own open-success and open-failure paths
 *    safely, so Rules_DribbleOnCommand's `return Dribble_TurnOn(...)`
 *    (122664) is reached regardless of which way that resolves. */
TEST(cov4_00_savecmd, save_command_open_fails) {
  static unsigned char anchor[32], node[32];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov4_00_save_target.clp";
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;
  int saved968 = g_ClipsHaltExecution;

  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  memset(valnode, 0, sizeof valnode);

  valnode[4] = (_DWORD)(intptr_t)path; /* offset 16: the parsed string pointer */
  *(short *)node = 3;                  /* STRING tag */
  *(int *)(node + 2) = (int)(intptr_t)valnode;
  *(int *)(node + 10) = 0;
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(int *)(anchor + 2) = (int)(intptr_t)funcrec;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  g_ClipsEvaluationError = 0;
  g_ClipsHaltExecution = 0;

  TOUCH(Rules_SaveCommand(0, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
  g_ClipsHaltExecution = saved968;
}

TEST(cov4_00_dribblecmd, dribble_on_command_attempt) {
  static unsigned char anchor[32], node[32];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov4_00_dribble_target.txt";
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;
  int saved968 = g_ClipsHaltExecution;

  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  memset(valnode, 0, sizeof valnode);

  valnode[4] = (_DWORD)(intptr_t)path;
  *(short *)node = 3;
  *(int *)(node + 2) = (int)(intptr_t)valnode;
  *(int *)(node + 10) = 0;
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(int *)(anchor + 2) = (int)(intptr_t)funcrec;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;
  g_ClipsEvaluationError = 0;
  g_ClipsHaltExecution = 0;

  TOUCH(Rules_DribbleOnCommand(0, 0.0));

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
  g_ClipsHaltExecution = saved968;
}

/* =========================================================================
 * Class_ClassSubclassesCommand (173553-173565, uncovered 173561,173562,
 * 173564,173565): Class_ParseClassNameAndInheritFlag's very first check is
 * `if (Rules_RtnArgCount())`; with the default empty argument list
 * (dword_51A960 left at 0, Rules_RtnArgCount()==0) it takes the safe
 * "expected count error" branch and returns 0 without ever reaching
 * Lexer_ParseValueList's hard-ceiling dereference. That makes v2==0 back in
 * Class_ClassSubclassesCommand, taking the `else` branch and reaching
 * Rules_SetMultifieldErrorValue(v3) -- v3 is Class_ClassSubclassesCommand's
 * own decompiler-lost local, so that call itself faults (confirmed via gdb),
 * but the crash happens *inside* the callee, after the call statement (line
 * 173564) and the `if(v2)` test (173561) have both already executed, so
 * fork isolation still banks those two lines. The truthy branch (173562)
 * and the function's closing line (173565, only reached if the else branch
 * returns normally) are not reachable this way. */
TEST(cov4_00_classsubclasses, class_subclasses_command_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Class_ClassSubclassesCommand(0, 0.0));
}

/* =========================================================================
 * Lexer_TokenExpect (99781-99813, uncovered 99800,99801,99807): its 'v2' is
 * a genuinely lost register value at this call site (verified via gdb to
 * hold arbitrary stack garbage, e.g. 4331149, completely unrelated to
 * Rules_RtnArgCount()'s return value or any global argument-count state) --
 * there is no argument or global reachable from a normal C caller that
 * steers it into the {1,2}-valued branches this function's remaining lines
 * need. Hard ceiling; attempted once. */
TEST(cov4_00_tokenexpect, token_expect_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Lexer_TokenExpect(1));
}

/* =========================================================================
 * Rules_IntegerFunction (126982-126997, uncovered 126991-126993): gated on
 * Lexer_ParseValueList, a confirmed hard ceiling (see file header).
 * Attempted once. */
TEST(cov4_00_integerfn, integer_function_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_IntegerFunction(0, 0.0));
}

/* =========================================================================
 * Class_SubclassPCommand (172403-172416, uncovered 172410-172412):
 * Class_ParseTwoClassNameArgs calls Lexer_ParseValueList directly (no
 * Rules_RtnArgCount guard), so its hard-ceiling 'v7' dereference fires
 * unconditionally UNLESS dword_51A964 (Lexer_ParseValueList's own
 * bload-style short-circuit flag) is truthy, in which case it returns 0
 * immediately -- safely, before ever reaching that dereference. But before
 * that check even runs, Lexer_ParseValueList unconditionally calls
 * Rules_RtnUnknown(), which itself unconditionally dereferences
 * dword_51A960+6 as the first argument node. Giving it a real (non-empty)
 * STRING-literal node there is NOT safe: Rules_RtnUnknown hands that node to
 * Parser_ParseForm, and Class_ParseTwoClassNameArgs' own decompiled
 * `_DWORD v8[2]` BYREF output buffer is undersized for what
 * Parser_ParseForm actually writes through it, tripping the stack
 * protector (verified: "*** stack smashing detected ***" before
 * Lexer_ParseValueList's dword_51A964 check is ever reached). Leaving the
 * arg list EMPTY instead (dword_51A960+6 == 0) sends Rules_RtnUnknown down
 * its "nonexistent arg" error-reporting branch, which never touches
 * Parser_ParseForm; that branch only needs dword_51A960+2 to chain to a
 * valid (if inert) "current function" record for its error message, the
 * same funcrec/symnode fixture used by the Rules_SaveCommand/
 * Rules_DribbleOnCommand tests above. Rules_RtnUnknown then returns
 * normally, Lexer_ParseValueList's dword_51A964 check fires and returns 0,
 * yielding result==0 in Class_SubclassPCommand: covers the `if(result)`
 * test (172410, always evaluated) and the falsy `return result;` (172412).
 * Only the truthy branch (172411, Class_HasSuperclass call) needs the
 * Lexer_ParseValueList success path and stays a hard ceiling. */
TEST(cov4_00_subclassp, subclass_p_command_falsy) {
  static unsigned char anchor[32];
  static _DWORD funcrec[8], symnode[8];
  signed int r;
  int saved960 = g_ClipsCurrentExpression;
  int saved964 = g_ClipsEvaluationError;

  memset(anchor, 0, sizeof anchor);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(int *)(anchor + 2) = (int)(intptr_t)funcrec; /* offset+2: "current function" record */
  /* offset+6 (first arg node) left 0: empty arg list, no Parser_ParseForm call */
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  g_ClipsEvaluationError = 1;
  r = Class_SubclassPCommand(0.0);
  CHECK_EQ(r, 0);

  g_ClipsCurrentExpression = saved960;
  g_ClipsEvaluationError = saved964;
}

/* =========================================================================
 * Rules_CoshBuiltin (129747-129759, uncovered 129756): gated on
 * Rules_MathParseSingleArg, a confirmed hard ceiling (see file header).
 * Attempted once. */
TEST(cov4_00_coshbuiltin, cosh_builtin_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_CoshBuiltin(0, 0, 0, 0.0));
}

/* =========================================================================
 * Instance_InitializeInstanceFunction (135336-135347, uncovered 135343):
 * Instance_ActiveInitializeInstanceFunction writes through its own `a1`
 * parameter (`*(a1+4)=2; *(a1+8)=...`), so a1 must be a real writable
 * buffer address (not 0/NULL, which is all our earlier attempt supplied).
 * It also calls Instance_ResolveArgumentToInstance, which -- regardless of
 * arg-list contents -- unconditionally dereferences dword_51A960+6 as the
 * first argument node before it can do anything else. An all-zeroed node
 * is NOT safe here (tag 0 sends Parser_ParseForm down a recursive
 * "function call" evaluation path -- Rules_PropagateReturnValueDepth ->
 * Rules_ClampEvaluationDepth -- that dereferences a null "a2" record and
 * faults, confirmed via gdb); reusing the same one-node STRING(tag=3)
 * literal fixture as the Rules_SaveCommand/Rules_DribbleOnCommand tests
 * above keeps Parser_ParseForm on its plain-literal path instead. With a
 * real outbuf and that fixture, Instance_ResolveArgumentToInstance runs to
 * completion (returns falsy: a string is not a valid instance-name arg),
 * short-circuiting the rest of Instance_ActiveInitializeInstanceFunction
 * safely and letting Instance_InitializeInstanceFunction reach its own
 * final `return Rules_SetObjectPatternMatchDelay(...)` line cleanly
 * (verified: returns 1, no crash). */
TEST(cov4_00_instinitfn, initialize_instance_function) {
  static _DWORD outbuf[16];
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  int saved960 = g_ClipsCurrentExpression;
  int r;

  memset(outbuf, 0, sizeof outbuf);
  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  memset(valnode, 0, sizeof valnode);
  *(short *)node = 3; /* STRING tag: a plain literal, no recursive eval */
  *(int *)(node + 2) = (int)(intptr_t)valnode;
  *(int *)(node + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node; /* offset+6: first arg node */
  g_ClipsCurrentExpression = (int)(intptr_t)anchor;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  r = Instance_InitializeInstanceFunction((uintptr_t)(intptr_t)outbuf, 0, 0.0);
  CHECK_EQ(r, 1);

  g_ClipsCurrentExpression = saved960;
}

/* =========================================================================
 * Rules_BsavePackSharedRecordHeader (149897-149931, uncovered 149913): fully
 * deterministic bit-packing logic with no decompiler-lost locals reachable
 * from our inputs -- just needs *(a2+8) (v3) nonzero to take the
 * `v4 = *(_DWORD*)(v3+4)` branch instead of the `v4=-1` default. */
TEST(cov4_00_bsavepack, pack_shared_record_header_nonzero_v3) {
  static _DWORD resultbuf[16];
  static _DWORD a2buf[16];
  static _DWORD inner[16];
  int r;

  memset(resultbuf, 0, sizeof resultbuf);
  memset(a2buf, 0, sizeof a2buf);
  memset(inner, 0, sizeof inner);
  a2buf[2] = (int)(intptr_t)inner; /* offset+8 */
  inner[1] = 0x1234;               /* offset+4 within the pointed-to record */

  r = Rules_BsavePackSharedRecordHeader((int)(intptr_t)resultbuf, (int)(intptr_t)a2buf);
  CHECK_EQ(r, (int)(intptr_t)resultbuf);
  CHECK_EQ(resultbuf[0], 0x1234);
}

/* =========================================================================
 * Rules_FetchJoinObjectSlotFieldSimple (176156-176168, uncovered 176167):
 * its own 'v3' (never assigned by any statement) is passed as
 * Rules_FetchObjectSlotFieldSimpleCore's `result` output parameter, which
 * that function unconditionally writes through (`result[1] = ...`) on every
 * path -- confirmed via gdb that reaching the call always faults on that
 * write before Rules_FetchJoinObjectSlotFieldSimple's own `return 1;` can
 * execute. Hard ceiling; attempted once with a join-binding setup that at
 * least reaches the call. */
TEST(cov4_00_fetchjoin, fetch_join_object_slot_field_simple_attempt) {
  static _DWORD a1buf[64];
  static _DWORD v2buf[64];

  memset(a1buf, 0, sizeof a1buf);
  memset(v2buf, 0, sizeof v2buf);
  a1buf[4] = (int)(intptr_t)v2buf; /* *(a1+16) */
  v2buf[1] = 1;                    /* (unsigned __int8)*(v2+4) - 1 -> binding index */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_FetchJoinObjectSlotFieldSimple((int)(intptr_t)a1buf, 0));
}

/* =========================================================================
 * Building_HandleUpgradeButtonAction (36714-36722, uncovered 36720): only
 * reaches `return CRT_RunGuardedStaticLocalInit();` when
 * Building_TryStartUpgrade() returns truthy, but that function's own 'v2'
 * (never assigned) is used AS the building-record pointer itself
 * (`v2+421`, `v2+429`, `v2+438`) once Building_CanStartUpgrade(a1) is true --
 * confirmed via gdb to fault there. Hard ceiling; attempted once with a
 * building record crafted so Building_CanStartUpgrade(a1) is true (maximizes
 * how far the attempt gets before the inevitable fault). */
TEST(cov4_00_buildingupgrade, handle_upgrade_button_action_attempt) {
  static unsigned char rec[512];
  int saved;

  memset(rec, 0, sizeof rec);
  rec[444] = 7; /* Building_CanStartUpgrade: a1[421](0)<2 && 0<(a1[444]&7)-1 && !a1[429] */
  saved = g_SelectedBuildingRecord;
  g_SelectedBuildingRecord = (int)(intptr_t)rec;

  TOUCH(Building_HandleUpgradeButtonAction());

  g_SelectedBuildingRecord = saved;
}

/* =========================================================================
 * Compat_StringHolderCopyText (86865-86881, uncovered 86878): the `!copy`
 * branch needs Compat_AllocLow32Bytes() to fail, which (per
 * compat/decomp_runtime_stubs.c) only happens on a non-positive size or a
 * genuine allocation failure (arena exhaustion / address-space-fit failure /
 * malloc failure) -- none of which a single unit test can force
 * deterministically without an implausibly large string or actually
 * exhausting memory. Attempted once with a very large source string in case
 * the low32 arena's 32-bit-address-fit check trips; otherwise left as a
 * practical hard ceiling. */
TEST(cov4_00_stringholder, copy_text_large_source_attempt) {
  static _DWORD holder[4];
  static char bigsrc[4000000];

  memset(holder, 0, sizeof holder);
  memset(bigsrc, 'a', sizeof(bigsrc) - 1);
  bigsrc[sizeof(bigsrc) - 1] = 0;

  Compat_StringHolderCopyText(holder, bigsrc);
}

/* =========================================================================
 * Instance_PutSlotValue (101888-101896, uncovered 101895): needs
 * Instance_ValidateSlotValueConstraints to return falsy, which only happens
 * via its two error branches (both print through several layers of
 * error-context helpers ending in a genuinely deep, uncontrollable chain of
 * "current message handler"/router globals) or its dynamic-constraint-check
 * branch (which requires Rules_DynamicConstraintCheckingEnabled() true and a
 * real constraint record). All three were attempted; the print-path
 * branches reliably fault a few calls deep (confirmed via gdb) before
 * Instance_ValidateSlotValueConstraints can return, so the falsy path
 * remains out of reach. Left as a practical hard ceiling; one attempt kept
 * below (the a1[1]==4 "singlefield" branch, which reaches furthest). */
TEST(cov4_00_putslotvalue, put_slot_value_attempt) {
  static _DWORD a1buf[64], a3buf[64];
  static int a2buf[64];
  static _DWORD slotdesc[64];
  signed int r;

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0, sizeof a3buf);
  memset(slotdesc, 0, sizeof slotdesc);
  a3buf[1] = 4; /* ValidateSlotValueConstraints' a1[1]==4 -> falsy branch attempt */
  a2buf[0] = (int)(intptr_t)slotdesc;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  r = Instance_PutSlotValue(a1buf, a2buf, a3buf, 0.0);
  (void)r;
}

/* =========================================================================
 * Rules_AssertParsedFact (94691-94708, uncovered 94702,94703): both
 * remaining lines are unconditional (Rules_DecrementIndentDepth(8); return
 * v4;) once Rules_ParseAssertCommand returns, and v4 is only ever *returned*
 * (never dereferenced), so this should be safe -- except
 * Rules_ParseAssertCommand's own parser chain (Rules_ParseAssertRHSPattern ->
 * Parser_NextToken) reads a decompiler-lost local as a BYREF token-output
 * pointer and writes through it unconditionally, faulting before
 * Rules_ParseAssertCommand can return (confirmed via gdb). That keeps the
 * call at line 94701 from ever completing. Hard ceiling; attempted once. */
TEST(cov4_00_assertparsedfact, assert_parsed_fact_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_AssertParsedFact(0, 0, 0));
}

/* =========================================================================
 * Unit_BuildAttackAnimSpritePath (27869-27965, uncovered 27901,27929):
 * - Line 27901 (break in the first copy-loop, over the fixed global string
 *   aUnits_at_1 == "units_at\\", length 9): with a fixed odd-length string
 *   the null terminator always lands at an odd index, so the loop always
 *   exits via the outer `while(v6)` check on the even/odd byte pair, never
 *   via this `if(!v5) break;` -- a compile-time-constant, permanently dead
 *   branch regardless of any argument we supply. Left uncovered.
 * - Line 27929 (break in the third copy-loop, over `v23` where
 *   `v23[0] = a3 + 49`): a3 is a caller-supplied `char`, so a3 == -49 makes
 *   v23[0] == 0, taking the break on the very first iteration. Reachable. */
TEST(cov4_00_attackanimpath, build_path_a3_forces_third_loop_break) {
  static char out[256];

  memset(out, 0, sizeof out);
  TOUCH(Unit_BuildAttackAnimSpritePath(out, 0, (char)-49));
}

/* =========================================================================
 * Unit_BuildGarrisonSlotIconSpritePath (27566-27663, uncovered 27627): the
 * break at line 27627 is in a copy-loop over `v23`, which is unconditionally
 * initialized via `strcpy(v23, "g")` -- a fixed 1-character (odd-length,
 * hence its null terminator lands on the checked-second/odd byte) literal
 * with no caller-controllable input feeding it. The loop always exits via
 * the outer `while(v15)` check on the very first iteration (v23[1]==0),
 * never via this inner `if(!v14) break;`. A compile-time-constant,
 * permanently dead branch; left uncovered (no test added -- there is no
 * input that changes this). */

/* =========================================================================
 * Building_CountNonCombatGarrisonEntries (57429-57463, uncovered 57462):
 * the final `return v2;` (distinct from the early return inside the
 * loop) is only reached once the outer `while (v1 != v3)` check fails
 * *without* ever taking the inner LABEL_5 early-return path. Giving every
 * one of the 12 garrison-slot entries a type of 0 (not -1, and not any of
 * the four "special" unit-type constants) makes every iteration fall
 * through to `v1 += 31;` (the non-LABEL_5 increment) and walk off the end of
 * the array, hitting this final return. */
TEST(cov4_00_buildingnoncombat, count_noncombat_all_type_zero) {
  static unsigned char rec[512];
  int i, r;

  memset(rec, 0, sizeof rec);
  for (i = 0; i < 12; i++) {
    *(short *)(rec + i * 31 + 18) = 0;
  }
  r = Building_CountNonCombatGarrisonEntries((int)(intptr_t)rec);
  CHECK_EQ(r, 0);
}
