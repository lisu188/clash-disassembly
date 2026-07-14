/* thin03: final top-up pass for a batch of clash95.c functions that are
 * already mostly covered, each missing 1-3 lines (see scratchpad/
 * thin_batches/thin_03.json). Every remaining function in the batch was
 * analyzed and, in most cases, also empirically probed with a standalone
 * debug harness; only two targets turned out to be reachable by a
 * genuinely deterministic fixture (no stack-spray / uninitialized-register
 * luck). Both are verified to hit their target line on every run in a
 * private scratch build.
 *
 * Skipped as crash-inevitable / dead-code / harness-blocked (analysis
 * and, where noted, direct gdb reproduction confirm every path to the
 * target line is either mathematically unreachable or dereferences a
 * decompiler-lost "possibly undefined" register/pointer):
 *   Rules_SinhBuiltin, Rules_MathTanh, Rules_MathSech, Rules_MathAsinh,
 *   Rules_MathExp (the success line is only reachable if
 *   Rules_MathParseSingleArg returns true, which requires Lexer_TokenExpect
 *   to avoid its error path -- gated on `if (!v2)` with v2 a genuinely
 *   uninitialized local, comment "variable 'v2' is possibly undefined");
 *   Rules_WriteExpressionRefToCode (AST_FindHashedNodeChain's `*v5 = v4;`
 *   with v5 undefined fires on every non-null second-arg call, matching
 *   test_cov4_06.c's own documented attempt at this exact line);
 *   Instance_ModifyInstanceFunction / Instance_MessageModifyInstanceFunction
 *   / Instance_DuplicateInstanceFunction /
 *   Instance_MessageDuplicateInstanceFunction (each Instance_Active* callee
 *   writes `a1[1] = 2; a1[2] = ...;` through the caller's undefined v1 on
 *   every path, before the target line can be reached);
 *   Defgeneric_ClearDefgenericsReady (the loop body needs a real defgeneric
 *   construct registered in the module system -- no lightweight fixture
 *   exists for that anywhere in this suite -- and Defgeneric_
 *   RemoveAllExplicitMethods' own logic is additionally gated by its own
 *   undefined v3 on the non-trivial paths);
 *   Rules_MatchesCommand (the "construct class" descriptor threaded into
 *   Rules_FindConstructByNameGeneric is the caller's undefined v3, used
 *   there as two indirect function-pointer calls -- inherently unsafe to
 *   drive to a chosen outcome);
 *   Rules_IsClassBitmapEmpty (the target branch needs a 16-bit value to
 *   wrap past 0, impossible given *a1's actual domain: (uint16>>3)+1 maxes
 *   out at 8192, so `!(_WORD)v2` can never be true -- unreachable for any
 *   valid input, not merely untested);
 *   Class_ClassSlotsCommand (Class_SlotsFunction writes `a2[1] = 4; ...`
 *   through the caller's undefined v3 unconditionally on entry, before any
 *   branch);
 *   Rules_FetchJoinObjectSlotFieldSimple (Rules_FetchObjectSlotFieldSimpleCore
 *   writes `result[1] = ...; result[2] = ...;` through the caller's
 *   undefined v3 "result" out-param);
 *   Rules_BuildSlotBoundTestExpression / Rules_BuildSlotUnboundTestExpression
 *   (every one of the four return paths through
 *   Rules_BuildSlotConstraintBitmapTestNode converges on `*v3 = ...;`
 *   with v3 its own undefined local -- there is no path through that
 *   callee that avoids it);
 *   Class_LookupClassOrReportError / Class_ParseClassNameArg /
 *   Class_SuperclassPCommand / Class_SubclassPCommand (all initially looked
 *   tractable via a real registered fake class plus a tag==8 "simple
 *   literal" node -- reusing the recipes tests/unit/cases/test_cov5_02.c
 *   and test_cov4_01.c/test_cov4_06.c already established for sibling
 *   functions -- but direct gdb reproduction in a standalone debug harness
 *   shows: (1) Class_LookupByQualifiedName's no-"::" fast path calls
 *   `Class_LookupInScope(v1)` with v1 a genuinely undefined local that
 *   resolves to NULL once the symbol table is actually initialized,
 *   crashing inside Rules_HashSymbolName on `*a1`; and (2)
 *   Lexer_ParseValueList's very first statement unconditionally
 *   dereferences its own undefined v7 (`*(_DWORD *)(v7 + 4)`) before any
 *   of our chosen type-tag logic can matter, and in this call context v7
 *   is a bad pointer, so it segfaults immediately. test_cov4_06.c's
 *   plain-tag==2 attempt at Class_ParseClassNameArg hitting this exact
 *   wall is presumably why 172707 was still uncovered going into this
 *   batch. Neither hazard is avoidable by choosing different argument
 *   values -- both are unconditional dereferences ahead of any branch we
 *   control);
 *   CRT_BeginThread (the target line is behind `if (Thread)`, but the
 *   shared test harness's own CreateThread stub in test_all.c always
 *   returns 0 -- unreachable given the fixed harness environment);
 *   CRT_IsExtendedMbcsLeadByte (target line is behind `!ismbclegal_(...)`,
 *   but the shared harness's ismbclegal_ stub always returns 1 -- same
 *   harness-level block);
 *   Rules_PrintJoinNetworkSharingReport (looked reachable in isolation --
 *   Rules_ClearJoinNetworkMarkedFlags safely no-ops with an empty module
 *   list -- but the tail-call return line itself,
 *   `return Rules_PrintJoinNetworkNodeRuleOwners(v1, v0);`, passes the
 *   function's OWN undefined v1/v0 locals into a callee that dereferences
 *   them as a node pointer whenever they're non-zero; confirmed via gdb to
 *   crash inside Rules_PrintJoinNetworkNodeRuleOwners on this exact call
 *   path with no way to zero v1/v0 from the caller side). */

/* ---- Rules_FindExistingJoinTestNode (target 181033, `return v10;` on a
 * genuine match): a2==v10[4] is fully under our control (both 0), the four
 * OR-clauses in Rules_JoinTestNodeMatches's first guard all evaluate false
 * for an all-zero node (bit0==0, bit3==0; a3(inner)!=1 short-circuits the
 * third clause; AST_NodeListsEqual(NULL,NULL)==1 satisfies the fourth). The
 * function then computes `v11 = a9 + 4*v10_local` where v10_local is a
 * genuinely decompiler-lost local -- rather than guessing its value, we pin
 * outer a7 (mapped to inner a6, the while-loop bound) to INT_MAX, which
 * makes `a6 < v10_local` false for EVERY possible 32-bit signed v10_local
 * (there is no int greater than INT_MAX), so the while loop is skipped
 * deterministically regardless of the garbage. With the loop skipped, v9
 * still equals our own node pointer, so the tail expression
 * `a8 && (*(v9+36) || *(v9+8))` and the final `return a8 || ...` only touch
 * fields inside our own zeroed buffer, and outer a9 (mapped to inner a8) is
 * set to 1 so the final return short-circuits true on its very first
 * operand without evaluating anything else. Verified in a private scratch
 * build: hits line 181033 on every run. */
TEST(thin03_joinnode, exact_match_returns_node) {
  static _DWORD node[16];
  memset(node, 0, sizeof node);
  /* node[4] (offset16) == outer a2 (both 0); node[2]/node[3]/node[9] all 0
   * satisfy the AST_NodeListsEqual/tail-guard checks. */
  TOUCH(Rules_FindExistingJoinTestNode(
      node, /* a1 */
      0,    /* a2 == node[4] */
      0,    /* a3 -> inner a4: node bit3 == 0 */
      0,    /* a4 -> inner a2: node bit0 == 0; also outer's own !a4 break */
      0,    /* a5 -> inner a3: != 1, short-circuits the busy-slot clause */
      0,    /* a6 -> inner a5: AST_NodeListsEqual(NULL, NULL) == 1 */
      0x7FFFFFFF, /* a7 -> inner a6: neutralizes the undefined while bound */
      0,          /* a8 -> inner a7: unused by the callee */
      1,          /* a9 -> inner a8: forces `return a8 || ...` true */
      0));        /* a10 -> inner a9: unused (dead code, loop skipped) */
}

/* ---- MessageHandler_UndefineForClassOrAll (target 166464, `v12 = 0;`):
 * extends the fixture test_cov4_07.c's cov4_07_msghandler test already
 * established (a single fake class record reachable via Class_GetNextRecord
 * enumeration, a1==0/a4==0 driving the "all classes" loop) with a real
 * "busy handler" so MessageHandler_RemoveByNameAndType actually returns 0
 * instead of its unconditional default of 1: with fakeClassRecord[24]
 * (offset 96, handler count) nonzero and fakeClassRecord[22] (offset 88,
 * handler array) pointing at a record whose own +4 field is nonzero,
 * MessageHandler_AnyHandlerBusy's for-loop condition `!*(i+4)` is false on
 * its very first check, so it falls straight through to `return 1;`
 * (busy) -- which routes MessageHandler_RemoveByNameAndType into the
 * "Rules_GetConstructNameString + MessageHandler_ReportUnableToDelete;
 * return 0" branch. Rules_GetConstructNameString's `*(*(a1)+16)` double
 * dereference is satisfied by pointing fakeClassRecord[0] at a small,
 * separate name-holder buffer (kept distinct from fakeClassRecord[4], which
 * Class_Enum's "next" chain field also uses, to avoid the two roles
 * colliding). Verified in a private scratch build: hits line 166464 on
 * every run. */
TEST(thin03_msghandler, undefine_for_all_classes_busy_handler_fails_remove) {
  static _DWORD moduleStruct[16];
  static _DWORD itemsArray[32];
  static _DWORD listWrapper[8];
  static _DWORD fakeClassRecord[64];
  static _DWORD nameHolderBuf[8];
  static _DWORD handlerRecord[16];
  static int nameHolder = 0x4008;
  int savedCurrentModule = g_Clips_CurrentModule;
  int savedClassEnumSlot = g_CLIPS_DefclassModuleItemIndex;

  memset(moduleStruct, 0, sizeof moduleStruct);
  memset(itemsArray, 0, sizeof itemsArray);
  memset(listWrapper, 0, sizeof listWrapper);
  memset(fakeClassRecord, 0, sizeof fakeClassRecord);
  memset(nameHolderBuf, 0, sizeof nameHolderBuf);
  memset(handlerRecord, 0, sizeof handlerRecord);

  g_CLIPS_DefclassModuleItemIndex = 0; /* class construct-type slot index (0 by default) */
  moduleStruct[2] = (_DWORD)(intptr_t)itemsArray;     /* +8: items array */
  itemsArray[0] = (_DWORD)(intptr_t)listWrapper;       /* index 0 == dword_54E6BC */
  listWrapper[1] = (_DWORD)(intptr_t)fakeClassRecord;  /* +4: list head */
  g_Clips_CurrentModule = (int)(intptr_t)moduleStruct;

  nameHolderBuf[4] = (_DWORD)(intptr_t)"Thin03MsgHandlerClass"; /* +16 */
  fakeClassRecord[0] = (_DWORD)(intptr_t)nameHolderBuf; /* Rules_GetConstructNameString */
  /* fakeClassRecord[4] (next-in-Class_Enum chain) stays 0 -> single-record
   * enumeration, same as test_cov4_07.c's version. */
  handlerRecord[1] = 1;                                 /* +4: busy flag */
  fakeClassRecord[22] = (_DWORD)(intptr_t)handlerRecord; /* +88 */
  fakeClassRecord[24] = 1;                               /* +96: handler count */

  TOUCH(MessageHandler_UndefineForClassOrAll(0, (signed int *)&nameHolder, 0, 0));

  g_Clips_CurrentModule = savedCurrentModule;
  g_CLIPS_DefclassModuleItemIndex = savedClassEnumSlot;
}
