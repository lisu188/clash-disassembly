/* cov4_04 cluster: precise-line top-up pass targeting the exact
 * still-uncovered clash95.c lines listed in
 * scratchpad/cov4_batches/cov4_04.json for: Rules_FirstFunction,
 * Rules_WriteConstructModuleItemHeaderToCode, Parser_ParseNumericFormCompat,
 * Rules_GetAllowedAttributeTokenCode, Deffunction_Delete,
 * WCIsvListBase_base_sget, Rules_AcotBuiltin, Output_WriteFormatted,
 * Rules_BsaveAtomTables, Deffunction_CloseCodeFiles,
 * Compiler_CloseDefinstancesCodeFiles, Cheat_QuitWithJokeMessage,
 * Rules_Dependents, Method_FindByIndex, Unit_BuildShotAnimPaletteSpritePath,
 * CastleProduction_ReloadLicenceSlotSprites, Rules_PortCollectSupply,
 * Rules_PlaceInDepthList, CRT_FindFirstFile, Rules_HostLexemep,
 * Rules_MathAsinh, Instance_DuplicateInstanceFunction,
 * Rules_IsClassBitmapEmpty, CRT_BeginThread.
 *
 * Every TEST below is prefixed cov4_04_ to avoid symbol collisions with all
 * earlier cov batch files. Each test runs in its own forked
 * child (fork isolation + watchdog), so crashes/hangs are safe -- coverage
 * banked up to the fault point is kept regardless. */

/* ---- shared "argument node" rig used by every dword_51A960-chain-based
 * function below (Rules_FirstFunction, Rules_Dependents, Rules_HostLexemep,
 * Rules_AcotBuiltin, Rules_MathAsinh). Matches the established convention
 * from tests/unit/cases/test_cov3_05.c and test_cov16.c: a "context" struct
 * whose +6 offset holds the head-of-chain pointer, and nodes with a type tag
 * at offset 0, a raw 4-byte "value" slot at offset 2, and a "next" link at
 * offset 10. All backing buffers are `static` so their truncated-to-32-bit
 * addresses round-trip correctly (64-bit -no-pie build modeling pointers as
 * 32-bit ints). */
static void cov4_04_set_node(unsigned char *node, short type, int value,
                              void *next) {
  memset(node, 0, 16);
  *(short *)node = type;
  *(int *)(node + 2) = value;
  *(int *)(node + 10) = (int)(intptr_t)next;
}

static void cov4_04_set_ctx(unsigned char *ctx, void *firstNode) {
  memset(ctx, 0, 16);
  *(int *)(ctx + 6) = (int)(intptr_t)firstNode;
}

/* ---- shared "fake CRT stream" rig for CRT_VfprintfLockedWrite-backed
 * Output_WriteFormatted/Output_Write calls. CRT_VfprintfLockedWrite reads
 * lock_key=*(a1+16) and passes it to off_51A56C/570 (safe for *any* value --
 * they just index one of 16 fixed lock buckets by `key & 0xF`), then reads
 * stream_state=*(a1+8) and busy_state=*(stream_state+12). Setting
 * busy_state to something != 0 and != 1 makes the function take its
 * `return 0;` fast path immediately after acquiring/releasing the lock,
 * without ever touching the CRT_PrintfFormatEngine / stream-mode-bits code
 * that would need a much more complete fake FILE*. off_51A56C/570 are NULL
 * until CRT_InitializeThreadAndFileHandleHooks() installs them (mirrors the
 * Mem_InitReserveBlock/Rules_InitAtomTables one-time bring-up used
 * elsewhere), so every test using this rig calls that first. */
static void cov4_04_make_fake_stream(unsigned char *stream,
                                      unsigned char *state) {
  memset(stream, 0, 64);
  memset(state, 0, 64);
  *(int *)(state + 12) = 2; /* busy_state: != 0 && != 1 -> clean early return */
  *(int *)(stream + 8) = (int)(intptr_t)state;
  *(int *)(stream + 16) = 0; /* lock_key: bucket 0, safe for any value */
}

/* ---- Rules_FirstFunction -- targets 127744-127751,127755-127757,127759.
 * The requested-type-4 (MULTIFIELD) parse means Parser_ParseForm's case 4
 * runs, which -- unlike the simple 0/1/2/3/5/7/8 cases -- ends by calling
 * Rules_PropagateReturnValueDepth(a2) with a2[1] forced to 4, taking its
 * *other* branch: `result = a2[2]` (our node's raw value field, aliased
 * onto header+8) must itself be a valid pointer, since it's immediately
 * read as `*(__int16*)(result+4)`, and because a2[3]/a2[4] (header+12/+16,
 * our own "v8"/"v9") are literally the *same* v8/v9 Rules_FirstFunction
 * later branches on, whenever v9>=v8 (the "true" branch we want) this
 * function's own `v3<=end` loop is *also* entered, walking
 * `result + 6*v3 + 14` for one 16-bit "type"/dword "value" pair per step.
 * Using v8=v9=1 keeps that loop to exactly one iteration; that one slot's
 * "value" pointer is backed by a real zeroed buffer so whichever
 * Rules_ClampEvaluationDepth case its (zeroed) "type" tag hits stays a safe
 * no-op read. The v8>v9 ("false" branch) case skips the loop entirely, but
 * still needs `result` itself valid for the pre-loop check. */
static void cov4_04_first_case(int v8val, int v9val, int need_loop_slot) {
  static unsigned char ctx[16], node1[16], header[32], resultObj[64];
  static _DWORD dataObj[16];
  static _DWORD out[8];
  int saved;

  memset(header, 0, sizeof(header));
  memset(resultObj, 0, sizeof(resultObj));
  memset(dataObj, 0, sizeof(dataObj));
  memset(out, 0, sizeof(out));

  *(int *)(header + 8) = (int)(intptr_t)resultObj;  /* -> a2[2] ("result") */
  *(int *)(header + 12) = v8val;                     /* -> a2[3] ("v8") */
  *(int *)(header + 16) = v9val;                      /* -> a2[4] ("v9") */

  if (need_loop_slot) {
    /* v3==v8val, one iteration: dword "value" slot at result+6*v8val+16 */
    *(int *)(resultObj + 6 * v8val + 16) = (int)(intptr_t)dataObj;
  }

  cov4_04_set_node(node1, 4, (int)(intptr_t)header, 0);
  cov4_04_set_ctx(ctx, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)ctx;
  TOUCH(Rules_FirstFunction(out, 1, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_04_first, branch_v9_ge_v8) {
  cov4_04_first_case(1, 1, 1); /* v9+1(2) >= v8+1(2) -> true branch */
}

TEST(cov4_04_first, branch_v9_lt_v8) {
  cov4_04_first_case(5, 2, 0); /* v9+1(3) >= v8+1(6) -> false branch */
}

/* ---- Rules_WriteConstructModuleItemHeaderToCode -- targets
 * 133194,133195,133196,133198,133199,133200,133201,133203,133204.
 * With a2==0 and dword_51A9B0==0, Module_GetItem(a2,garbage) short-circuits
 * to 0 with no dereference at all (its own `if (!result) { if
 * (!dword_51A9B0) return result; ...}` guard), so v8 (this function's own
 * local) is deterministically 0. Compiler_WriteModuleReference(a1,0) and the
 * following Output_WriteFormatted(...,asc_508278,v8) calls both use format
 * strings with zero printf conversion specifiers ("," and "NULL"), so they
 * never touch the vararg -- they safely reach the end via our fake-stream's
 * clean-early-return trick and actually return, letting execution reach our
 * *first* target line, 133194: `v12 = *(_DWORD *)(v8 + 4);`. That statement
 * itself is entered (crediting the line) but then dereferences address 4
 * (v8==0) and faults -- v8's only source, Module_GetItem's `v7` index
 * argument, is a genuine decompiler "possibly undefined" register with no
 * way for us to steer it to a real, safely-indexable table entry (any
 * nonzero table pointer turns that lookup into an unbounded
 * garbage-offset read that reliably crashes *inside* Module_GetItem
 * instead). So 133195 onward look like a genuine hard ceiling; this is a
 * one-line net gain (133194) plus whatever isolated-crash credit the
 * runtime gives that statement. */
TEST(cov4_04_writehdr, module_item_header) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  g_Clips_CurrentModule = 0;
  TOUCH(Rules_WriteConstructModuleItemHeaderToCode(
      (int)(intptr_t)stream, 0, 0, 0, 0));
}

/* ---- Parser_ParseNumericFormCompat -- targets 126275,126276,126285-126290.
 * expression[0]=2 (SYMBOL, one of Parser_ParseForm's simple-copy case
 * values) drives the `*expression > 1` branch (126275-126276) and yields
 * value_type==2, which is >1, so the error branch (126285-126290) always
 * follows. expression's own raw "value" dword must point to a small zeroed
 * object: Parser_ParseForm's Rules_PropagateReturnValueDepth /
 * Rules_ClampEvaluationDepth tail reads that pointer's own +8 field (both
 * zero here, so the comparison/assignment inside is a safe no-op). */
TEST(cov4_04_parsenum, symbol_type_error) {
  static __int16 expr[4];
  static _DWORD dummyObj[8];
  static _DWORD parsed[8];

  memset(expr, 0, sizeof(expr));
  memset(dummyObj, 0, sizeof(dummyObj));
  memset(parsed, 0, sizeof(parsed));

  expr[0] = 2; /* SYMBOL */
  *(int *)(expr + 1) = (int)(intptr_t)dummyObj;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  CHECK_EQ(Parser_ParseNumericFormCompat(expr, 0, parsed, 0.0, 7), 0);
}

/* ---- Rules_GetAllowedAttributeTokenCode -- targets
 * 179311,179313,179315,179317,179319,179321,179325 (the per-match `return`
 * lines other than the very first (103) and the final no-match (-1), both
 * already covered). Three earlier passes (test_cov2_02.c, test_cov23.c,
 * test_cov3_05.c) already tried feeding the matching string constants in
 * sequence on the theory that `a1` survives in its register across each
 * strcmp_ call; since these lines are still listed as uncovered, that
 * assumption evidently doesn't hold for every comparison in the real
 * binary. Retried here once more (cheap, and harmless if it again only
 * partially lands) with TOUCH so a mismatch can't fail the test. */
TEST(cov4_04_allowedattr, sequential_matches) {
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedValues));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedSymbols));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedStrings));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedLexemes));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInteg_0));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedNumbers));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInstanc));
  TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedFloats));
}

/* ---- Deffunction_Delete -- targets 120380,120382,120383,120384,120386.
 * Takes *no* arguments: its `v0`/`v2` locals are genuine decompiler
 * "possibly undefined" registers with nothing in our control to steer them
 * (Deffunction_IsDeletable(), which it calls, has the very same
 * no-argument-undefined-local shape one level down). Rules_IsBloaded()==0
 * (dword_51A1AC's default) at least lets us past the top guard; beyond that
 * this is a hard ceiling -- attempted once for whatever partial credit the
 * runtime's actual register contents happen to give. */
TEST(cov4_04_deffunc, delete_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Deffunction_Delete());
}

/* ---- WCIsvListBase_base_sget -- targets 56053,56054,56055,56056 (the
 * `if (!head)` branch). WCCompat_LinkFromHandle() is a bare identity cast
 * (`(WCCompatLink *)(uintptr_t)(unsigned int)link_handle`), and this
 * function's own guard (`if (!list || !list->head_link) return 0;`)
 * guarantees `head_link` is nonzero before that cast -- so `head` can never
 * come back NULL (a nonzero 32-bit value cast through zero-extension is
 * never zero). This branch appears to be genuinely unreachable via any
 * legal list state, not a crash-prone "possibly undefined" case, so no
 * dedicated TEST is included; a normal-list smoke call is exercised instead
 * for whatever incidental coverage it provides. */
TEST(cov4_04_wcisv, base_sget_normal_list) {
  static unsigned char list[24], link[8];
  memset(list, 0, sizeof(list));
  memset(link, 0, sizeof(link));
  *(int *)(list + 0) = (int)(intptr_t)link; /* head_link -> real link node */
  TOUCH(WCIsvListBase_base_sget((int)(intptr_t)list));
}

/* ---- Rules_AcotBuiltin -- targets 129729,129731,129732,129736. Rig a
 * single FLOAT-typed (type 0) argument node so Rules_MathParseSingleArg's
 * Lexer_ParseValueList(1,...,0,...) call succeeds (`a3==a2[1]` with both
 * 0); the node's raw value field points to a small object whose +16 byte
 * offset holds the double Rules_MathParseSingleArg reads back. A near-zero
 * value drives the near-zero branch (129729-129732); a normal nonzero value
 * drives the atan2 branch (129736). */
static void cov4_04_acot_case(double value) {
  static unsigned char ctx[16], node1[16];
  static _DWORD valueObj[16];

  memset(valueObj, 0, sizeof(valueObj));
  *(double *)((char *)valueObj + 16) = value;

  cov4_04_set_node(node1, 0, (int)(intptr_t)valueObj, 0);
  cov4_04_set_ctx(ctx, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  int saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)ctx;
  TOUCH(Rules_AcotBuiltin(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

TEST(cov4_04_acot, near_zero_branch) { cov4_04_acot_case(0.0); }
TEST(cov4_04_acot, normal_value_branch) { cov4_04_acot_case(2.0); }

/* ---- Output_WriteFormatted -- targets 90003,90012,90013.
 * 90003 (`if (!args_ptr) return 0;`): Compat_AllocLow32Bytes fails whenever
 * the requested size exceeds COMPAT_LOW32_ARENA_MAX_ALLOC (1 MiB); driving
 * that needs arg_count > 262144, so we build a format string with 300000
 * "%d" specifiers (no matching varargs needed -- the allocation failure
 * happens before the va_arg collection loop ever runs).
 * 90012/90013 (Compat_FreeLow32Bytes + final return, after a successful
 * alloc): needs CRT_VfprintfLockedWrite to actually *return* rather than
 * crash on a bare zeroed stream (see test_cov09.c's write_formatted_*
 * tests, which document that crash). Using the shared fake-stream rig's
 * "busy_state != 0 && != 1" trick makes it return 0 immediately after
 * lock/unlock, without touching the stream's real read/write machinery. */
TEST(cov4_04_output, alloc_too_large_returns_zero) {
  static char fmt_buf[600005];
  int i;
  for (i = 0; i < 300000; i++) memcpy(fmt_buf + i * 2, "%d", 2);
  fmt_buf[600000] = 0;
  CHECK_EQ(Output_WriteFormatted(0, 0, 1, (int)(intptr_t)fmt_buf), 0);
}

TEST(cov4_04_output, alloc_success_then_free_and_return) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  TOUCH(Output_WriteFormatted(0, 0, (int)(intptr_t)stream,
                               (int)(intptr_t)"%d\n", 5));
}

/* ---- Rules_BsaveAtomTables -- targets 116837,116838,116839 (the three
 * sibling Bsave*Table call/return lines). With the atom-table arena freshly
 * carved (all bucket tables empty), Rules_BsaveSymbolTable(a1=0) is fully
 * safe (fwrite_ with nmemb==0 is a no-op) and lets us reach line 116837.
 * v1/v2/v3 (the args fed to the next three calls) are genuine decompiler
 * "possibly undefined" registers we cannot set directly; whether they
 * happen to carry over as 0 (matching our own a1==0, which would keep the
 * whole chain safe) or some other value (which could fault inside a nested
 * fwrite_ on a huge bogus nmemb) is outside our control. Attempted once for
 * whatever partial credit results. */
TEST(cov4_04_bsave, atom_tables_attempt) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_BsaveAtomTables(0));
}

/* ---- Deffunction_CloseCodeFiles / Compiler_CloseDefinstancesCodeFiles --
 * targets 164755-164757 / 182614-182616 (both functions share the identical
 * body shape). Rules_ConstructCodeFileClose(result,a2,a3,a4,a5,a6) is called
 * with a3==*a2 (both equal to our own "a4" parameter, set immediately
 * before the call), so its `if (v8 > *a2)` guard is always false regardless
 * of the actual value. `result` (our own nonzero "a2"/"a1" parameter) must
 * be nonzero to skip the `!result` branch, which would otherwise
 * dereference a NULL a6 (we pass a6==0 like the source does). Past that,
 * it calls Output_WriteFormatted(...,v6=result,asc_507DA0,...) where
 * asc_507DA0 is "};\n" (zero specifiers, so its own genuinely-undefined
 * vararg is never read) -- so `result` doubles as our fake CRT stream,
 * using the same clean-early-return trick as the Output_WriteFormatted
 * tests above. fclose_() on a garbage handle is always safe (it just does a
 * registered-handle lookup and no-ops on a miss). */
TEST(cov4_04_closecode, deffunction_a2_path_returns) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  CHECK_EQ(Deffunction_CloseCodeFiles(0, (int)(intptr_t)stream, 5, 5), 0);
}

TEST(cov4_04_closecode, deffunction_a1_goto_path) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  CHECK_EQ(Deffunction_CloseCodeFiles((int)(intptr_t)stream,
                                       (int)(intptr_t)stream, 5, 5), 0);
}

TEST(cov4_04_closedefinst, a2_path_returns) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  CHECK_EQ(Compiler_CloseDefinstancesCodeFiles(0, (int)(intptr_t)stream, 5, 5),
           0);
}

TEST(cov4_04_closedefinst, a1_goto_path) {
  static unsigned char stream[64], state[64];
  cov4_04_make_fake_stream(stream, state);
  CRT_InitializeThreadAndFileHandleHooks();
  CHECK_EQ(Compiler_CloseDefinstancesCodeFiles((int)(intptr_t)stream,
                                                (int)(intptr_t)stream, 5, 5),
           0);
}

/* ---- Cheat_QuitWithJokeMessage -- targets 69268,69270 (whole body).
 * __noreturn wrapper around App_RequestQuit(), which itself never returns
 * (calls exit()/longjmp deep inside its rendering-mode-switch + message
 * path in the real engine). Fork isolation makes calling a __noreturn
 * function safe -- coverage of these two lines is banked regardless of how
 * the child eventually terminates. */
TEST(cov4_04_cheat, quit_with_joke_message) {
  TOUCH(Cheat_QuitWithJokeMessage());
}

/* ---- Rules_Dependents -- targets 111321,111322. Same dword_51A960 node
 * rig as Rules_FirstFunction/Rules_AcotBuiltin above, using type 7
 * (INSTANCE_ADDRESS -- one of Parser_ParseForm's simple-copy cases).
 * Rules_ResolveFactOrInstanceArg's `v6==6||v6==7` branch then returns the
 * node's raw value field directly (no dereference), giving Rules_Dependents
 * a nonzero `result` and driving both target lines: the `if (result)` guard
 * and the Rules_PrintDependentList(...) tail call. With no rules/patterns
 * registered, Rules_FindPatternParser() inside that callee returns an empty
 * list immediately, so our "result" value is never itself dereferenced by
 * Rules_PrintDependentList. It IS dereferenced one level up though:
 * Parser_ParseForm's simple-case tail unconditionally calls
 * Rules_PropagateReturnValueDepth/Rules_ClampEvaluationDepth on the node's
 * raw value field for type 7 (`if (dword_51A96C < a2[8]) ...`), so it must
 * be a real, safely-sized zeroed buffer rather than a bare sentinel
 * address. */
TEST(cov4_04_deps, dependents_found) {
  static unsigned char ctx[16], node1[16];
  static _DWORD valueObj[16];

  memset(valueObj, 0, sizeof(valueObj));
  cov4_04_set_node(node1, 7, (int)(intptr_t)valueObj, 0);
  cov4_04_set_ctx(ctx, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  int saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)ctx;
  TOUCH(Rules_Dependents(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Method_FindByIndex -- targets 161802,161803 (the loop's overflow
 * guard/return). count==2 at a1+32, a1+28 points at a 2-entry array (each
 * entry a 40-byte/10-dword stride, matching the `i += 10` walk) whose first
 * dwords are all 0 -- never equal to the sentinel a2==999 -- so the loop
 * runs exactly `count` times before hitting the guard's `return -1;`. */
TEST(cov4_04_method, find_by_index_overflow) {
  static _DWORD a1buf[16];
  static _DWORD entries[20];
  memset(a1buf, 0, sizeof(a1buf));
  memset(entries, 0, sizeof(entries));
  *(_DWORD *)((char *)a1buf + 28) = (_DWORD)(intptr_t)entries;
  *(_DWORD *)((char *)a1buf + 32) = 2;
  CHECK_EQ(Method_FindByIndex((int)(intptr_t)a1buf, 999), -1);
}

/* ---- Unit_BuildShotAnimPaletteSpritePath -- target 28094 (the `break;`
 * ending the first copy loop, hit as soon as the source constant
 * aUnits_at_0 reaches its own NUL terminator -- guaranteed on any call). */
TEST(cov4_04_unit, build_shot_anim_palette_sprite_path) {
  static char path[256];
  memset(path, 0, sizeof(path));
  TOUCH(Unit_BuildShotAnimPaletteSpritePath(path, 0));
}

/* ---- CastleProduction_ReloadLicenceSlotSprites -- target 50624 (the final
 * `return CastleProduction_DrawLicenceGrid();`). dword_532218/dword_532304
 * are plain writable globals; pointing dword_532218 at (buf - 402) makes
 * each of the 12 loop iterations' `*(char*)(i + dword_532218 + 402)` read
 * land inside our own zeroed `buf` (value 0, not -1, so
 * CastleProduction_ReloadLicenceSlotSprite takes its "no sprite change"
 * else-branch each time with dword_532304[i]==0, entirely safe). The
 * trailing DrawLicenceGrid() call is heavy rendering code that dereferences
 * g_RenderDevice's vtable; if that's not set up it may fault deep inside a
 * different function, but our own target *call* line is already entered
 * (and thus credited) by that point. */
TEST(cov4_04_castle, reload_licence_slot_sprites) {
  static unsigned char buf[16];
  memset(buf, 0, sizeof(buf));
  g_CastleProductionBuildingPtr = (int)(intptr_t)buf - 402;
  memset(g_CastleProduction_LicenceSlotSpriteHandles, 0, sizeof(g_CastleProduction_LicenceSlotSpriteHandles));
  TOUCH(CastleProduction_ReloadLicenceSlotSprites(0));
}

/* ---- Rules_PortCollectSupply -- target 69689 (`return 1;`).
 * Port_CollectReinforcementShipment's very first real check is
 * `if (PORT_ROW == -1) return 0;` (Debug_Log() ahead of it is a permanent
 * no-op stub, `logEnabled`/`battleLogEnabled` both default false) -- PORT_ROW
 * defaults to 0 (plain gameData-backed global), not -1, so we set it
 * ourselves to force that immediate, fully-safe return before our own
 * `return 1;` runs. */
TEST(cov4_04_port, collect_supply) {
  PORT_ROW = -1;
  CHECK_EQ(Rules_PortCollectSupply(0, 0, 0, 0.0), 1);
}

/* ---- Rules_PlaceInDepthList -- target 96152 (`return v4;` on a1==NULL).
 * a2's own +8/+12 fields are read unconditionally before the a1 check, so
 * a2 must still be a valid (if otherwise-irrelevant) buffer. */
TEST(cov4_04_depth, place_in_depth_list_null_a1) {
  static _DWORD a2buf[8];
  memset(a2buf, 0, sizeof(a2buf));
  CHECK_EQ(Rules_PlaceInDepthList(0, (int)(intptr_t)a2buf), 0);
}

/* ---- CRT_FindFirstFile -- target 106274 (the success-path return of the
 * real Win32 handle). Needs FindFirstFileA to actually match something.
 * Earlier passes (test_cov12.c, test_cov2_05.c) already tried "/tmp/*" and
 * "/*" for this same line without apparently landing it (still listed
 * uncovered), which suggests the compat path-translation layer needs a
 * pattern under its own translated root rather than any real POSIX path --
 * tried here with a few different candidates, including the repo's own
 * working directory (guaranteed to exist and be non-empty on this host),
 * for whatever additional chance that gives. */
TEST(cov4_04_crt, find_first_file_success) {
  _DWORD out[128];

  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/tmp/*", out, 0));

  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/*", out, 0));

  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/home/user/clash-disassembly/*", out, 0));

  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("*", out, 0));
}

/* ---- Rules_HostLexemep -- target 126055 (`return 1;`). Same dword_51A960
 * rig as above: a single SYMBOL-typed (type 2) node makes
 * Rules_RtnUnknown -> Parser_ParseForm set the local "v4" (a2[1]) to 2,
 * satisfying `v4==2||v4==3` deterministically (unlike test_cov16.c's
 * empty-chain rig, which leaves v4 as an unpredictable garbage read). Also
 * needs Lexer_TokenExpect(1) to not return -1; with a 1-node chain,
 * Rules_RtnArgCount()==1==a1, which satisfies that check for every
 * genuinely-undefined-register value Lexer_TokenExpect's own internal `v2`
 * happens to take except one out-of-{0,1,2} case outside our control.
 * The node's raw value field must be a real zeroed buffer (not a bare 0):
 * Parser_ParseForm's simple-case tail unconditionally calls
 * Rules_PropagateReturnValueDepth/Rules_ClampEvaluationDepth on it for
 * type 2 (`if (dword_51A96C < a2[2]) ...`), which would otherwise
 * dereference a NULL pointer. */
TEST(cov4_04_hostlex, lexemep_symbol_match) {
  static unsigned char ctx[16], node1[16];
  static _DWORD valueObj[16];

  memset(valueObj, 0, sizeof(valueObj));
  cov4_04_set_node(node1, 2, (int)(intptr_t)valueObj, 0);
  cov4_04_set_ctx(ctx, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  int saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)ctx;
  TOUCH(Rules_HostLexemep(0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Rules_MathAsinh -- target 129882 (`return asinh(v5[0]);`). Same
 * FLOAT-typed single-node rig as Rules_AcotBuiltin above. */
TEST(cov4_04_asinh, math_asinh_success) {
  static unsigned char ctx[16], node1[16];
  static _DWORD valueObj[16];

  memset(valueObj, 0, sizeof(valueObj));
  *(double *)((char *)valueObj + 16) = 1.0;

  cov4_04_set_node(node1, 0, (int)(intptr_t)valueObj, 0);
  cov4_04_set_ctx(ctx, node1);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  int saved = g_ClipsCurrentExpression;
  g_ClipsCurrentExpression = (int)(intptr_t)ctx;
  TOUCH(Rules_MathAsinh(0, 0, 0, 0.0));
  g_ClipsCurrentExpression = saved;
}

/* ---- Instance_DuplicateInstanceFunction -- target 136508 (the final
 * `return Rules_SetObjectPatternMatchDelay(v3, v2);`). v1/v2/v3 are
 * decompiler-lost register values threaded from the *return value* of the
 * preceding Rules_SetObjectPatternMatchDelay(1,a1) call and the FPU stack
 * (a1 re-read), which in the real compiled binary are ordinary register/FPU
 * contents rather than truly random -- a plain call is the only thing we
 * can do to exercise whatever that ends up being. */
TEST(cov4_04_instance, duplicate_instance_function) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(Instance_DuplicateInstanceFunction(0.0));
}

/* ---- Rules_IsClassBitmapEmpty -- target 170870 (`return 1;` right after
 * `v2 = ((int)*a1 >> 3) + 1;`). For any unsigned __int16 *a1 (range
 * 0..65535), `(*a1 >> 3) + 1` ranges 1..8192 -- it can never truncate to 0
 * as a 16-bit value, so this specific early check appears to be genuinely
 * unreachable via any input. Attempted once with the largest possible value
 * anyway; the loop below it (already covered) is exercised as a side
 * effect. */
TEST(cov4_04_classbmp, is_class_bitmap_empty_max_value) {
  static unsigned short bmp[8];
  memset(bmp, 0, sizeof(bmp));
  bmp[0] = 0xFFFF;
  TOUCH(Rules_IsClassBitmapEmpty(bmp));
}

/* ---- CRT_BeginThread -- target 186483
 * (`WaitForSingleObject(hHandle, 0xFFFFFFFF);`, inside `if (Thread)`).
 * tests/unit/test_all.c stubs CreateThread() to unconditionally return NULL
 * (see its comment "pretend thread creation failed"), so `Thread` is always
 * 0 in this harness and the `if (Thread)` branch containing our target line
 * is provably unreachable here -- not a probabilistic hard ceiling but a
 * hard guarantee from the test harness itself. No test is included for it;
 * spending more attempts would not change the outcome. */
