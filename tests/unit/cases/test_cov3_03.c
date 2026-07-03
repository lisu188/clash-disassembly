/* Second-pass (round 3) coverage additions for a batch of already partially
 * covered functions. No #include / no main -- TEST-only, aggregated by
 * test_all.c. Suite prefix: cov3_03_. */

/* ---- Compat_FileSystemQueryResultRelease ----
 * The existing test_cov09.c coverage of this function uses NON-static
 * locals (`_DWORD query[4]`, `uintptr_t vt_stream[3]` etc). The function
 * itself does `(uintptr_t)(unsigned int)opened_query` before dereferencing
 * (and again for the stored vtable word before comparing it against the
 * known Compat_* function pointers) -- i.e. it round-trips every pointer
 * through a 32-bit truncation, exactly the pattern the harness notes
 * requires *static* storage. With ordinary stack locals the truncated
 * "address" read back out is garbage, so the FileStream/Query vtable
 * matches, and even the plain "null vtable slot" comparison, never actually
 * land on the right memory -- explaining why those branches are still
 * uncovered despite test_cov09.c appearing to drive them. Redo the same
 * cases with `static` storage so the round-trip is lossless. */
TEST(cov3_03_compat, query_result_release_static_null_vtable) {
  static _DWORD query[4];
  memset(query, 0, sizeof query);
  query[0] = 0; /* vtable word itself is 0 -> hits the "if (!vtable) return;" */
  TOUCH(Compat_FileSystemQueryResultRelease(query));
}

TEST(cov3_03_compat, query_result_release_static_non_matching_vtable) {
  static _DWORD query[4];
  static uintptr_t vt_none[3];
  memset(query, 0, sizeof query);
  vt_none[0] = 0x1234;
  vt_none[1] = 0x5678;
  vt_none[2] = 0x9abc;
  query[0] = (_DWORD)(uintptr_t)vt_none;
  TOUCH(Compat_FileSystemQueryResultRelease(query));
}

TEST(cov3_03_compat, query_result_release_static_filestream_triple) {
  static _DWORD query[4];
  static uintptr_t vt_stream[3];
  memset(query, 0, sizeof query);
  vt_stream[0] = (uintptr_t)Compat_FileStreamSeekFromStart;
  vt_stream[1] = (uintptr_t)Compat_FileStreamTell;
  vt_stream[2] = (uintptr_t)Compat_FileStreamSeekFromEnd;
  query[0] = (_DWORD)(uintptr_t)vt_stream;
  query[1] = 0; /* keep result[1] == 0 so the internal fclose_() path is skipped */
  TOUCH(Compat_FileSystemQueryResultRelease(query));
}

TEST(cov3_03_compat, query_result_release_static_query_triple) {
  static _DWORD query[4];
  static uintptr_t vt_query[3];
  memset(query, 0, sizeof query);
  vt_query[0] = (uintptr_t)Compat_QuerySkipBytes;
  vt_query[1] = (uintptr_t)Compat_QueryGetLength;
  vt_query[2] = (uintptr_t)Compat_QuerySkipBytesFromBase;
  query[0] = (_DWORD)(uintptr_t)vt_query;
  query[1] = 0;
  TOUCH(Compat_FileSystemQueryResultRelease(query));
}

/* ---- CRT_HasActiveWindow ----
 * test_cov19.c's comment says this was intentionally left uncalled because
 * LoadLibraryA/GetProcAddress had no definition anywhere and would break the
 * whole coverage binary's link. test_all.c has since grown benign stub
 * definitions for both (LoadLibraryA() returns 0, GetProcAddress() returns
 * 0), so the link hazard no longer applies: LibraryA ends up NULL, the
 * inner `if (LibraryA)` block is skipped, and the function returns 0
 * deterministically and safely. */
TEST(cov3_03_crt, has_active_window) {
  CHECK_EQ(CRT_HasActiveWindow(), 0);
}

/* ---- Castle_RequestManagementScreenExit ----
 * test_cov03.c intentionally skips this because UIWidget_PlayPressedRelease-
 * AnimationWithDelay busy-waits ~20 real seconds via the render pump. Per
 * the updated harness, every TEST now runs in its own forked child under an
 * 8s alarm that still flushes gcov on timeout, which is exactly the
 * "spin forever" case the harness is designed to tolerate -- so drive it
 * anyway; whatever coverage accrues before the watchdog fires is banked. */
TEST(cov3_03_castle, request_management_screen_exit) {
  TOUCH(Castle_RequestManagementScreenExit((uintptr_t)0, 0));
}

/* ---- Class_GetDefmessageHandlerListCommand ----
 * test_cov22.c's existing test builds an arg-context whose offset+6 field
 * (the arg-node chain head Rules_RtnArgCount() walks) points at a non-null
 * node, so Rules_RtnArgCount() returns 1 there and the `!Rules_RtnArgCount()`
 * guard is always false. Leave that field at its memset-0 default instead
 * (empty arg chain -> Rules_RtnArgCount() == 0) to take the other side of
 * the guard: `return Class_MessageHandlerListFunction(0, 0);`. */
TEST(cov3_03_class, getdefmessagehandlerlist_zero_args) {
  static unsigned char argctx[64];
  int savedCtx = dword_51A960;
  memset(argctx, 0, sizeof argctx);
  dword_51A960 = (int)(intptr_t)argctx;
  TOUCH(Class_GetDefmessageHandlerListCommand(1, 1.0));
  dword_51A960 = savedCtx;
}

/* ---- Class_ParseClassNameArg ----
 * Lexer_ParseValueList() (called internally) first calls Rules_RtnUnknown()
 * unconditionally, then -- only if the global "evaluation halted" flag
 * dword_51A964 is zero -- falls into a line that dereferences a genuinely
 * uninitialized decompiler local, crashing before it can return. Setting
 * dword_51A964 nonzero makes Lexer_ParseValueList() take its
 * `if (dword_51A964) return 0;` short-circuit instead, safely returning 0.
 * Back in Class_ParseClassNameArg that makes `result` false, exercising the
 * previously-uncovered `if (result)`-false path and the final
 * `return result;`. Pair it with test_cov16.c's "safe empty arg chain"
 * pattern (offset+2 -> a func-record -> a symbol node, arg-chain head at
 * offset+6 left null) so Rules_RtnUnknown's own not-found branch -- which
 * runs before the dword_51A964 check -- also completes without touching
 * unmapped memory. */
TEST(cov3_03_class, parseclassnamearg_evaluation_halted) {
  static unsigned char argctx[64];
  static _DWORD funcrec[8], symnode[8];
  int savedCtx = dword_51A960;
  int saved964 = dword_51A964;
  memset(argctx, 0, sizeof argctx);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argctx + 2) = (_DWORD)(intptr_t)funcrec;
  dword_51A960 = (int)(intptr_t)argctx;
  dword_51A964 = 1;

  TOUCH(Class_ParseClassNameArg(1, 1.0));

  dword_51A960 = savedCtx;
  dword_51A964 = saved964;
}

/* ---- Defgeneric_ClearDefgenerics / Defgeneric_RemoveConstruct ----
 * Both gate on Rules_IsBloaded(), which is just `return dword_51A1AC;`.
 * Setting that flag makes Defgeneric_ClearDefgenerics() take its
 * `if (Rules_IsBloaded() == 1) return 0;` fast path (previously uncovered),
 * and makes Defgeneric_IsDeletable()'s `!Rules_IsBloaded() && ...`
 * short-circuit to false *without* touching the uninitialized local it
 * would otherwise dereference on the second operand -- so
 * Defgeneric_RemoveConstruct(nonzero) safely reaches its own
 * previously-uncovered `if (result)`-false path and final `return result;`,
 * and Defgeneric_RemoveConstruct(0) safely reaches the previously-uncovered
 * `if (!Defgeneric_ClearDefgenerics()) return 0;` true branch (since
 * Defgeneric_ClearDefgenerics() itself now deterministically returns 0). */
TEST(cov3_03_defgeneric, clear_defgenerics_bloaded) {
  int saved = dword_51A1AC;
  dword_51A1AC = 1;
  TOUCH(Defgeneric_ClearDefgenerics());
  dword_51A1AC = saved;
}

TEST(cov3_03_defgeneric, remove_construct_nonzero_bloaded) {
  static _DWORD obj[128];
  int saved = dword_51A1AC;
  memset(obj, 0, sizeof obj);
  dword_51A1AC = 1;
  TOUCH(Defgeneric_RemoveConstruct((int)(intptr_t)obj));
  dword_51A1AC = saved;
}

TEST(cov3_03_defgeneric, remove_construct_zero_bloaded) {
  int saved = dword_51A1AC;
  dword_51A1AC = 1;
  TOUCH(Defgeneric_RemoveConstruct(0));
  dword_51A1AC = saved;
}

/* ---- Rules_ListInstancesForClassOrModule ----
 * Only the a3==0 branches were previously safe/covered (module-lookup path
 * needs uninitialized locals feeding Class_LookupByModule). Per the updated
 * isolation model, drive the a3!=0 path anyway: even if Class_LookupByModule
 * crashes on the fake state, the lines up to that call are still banked. */
TEST(cov3_03_instances, list_for_class_or_module_a3_nonzero_a4_zero) {
  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 1, 0));
}

TEST(cov3_03_instances, list_for_class_or_module_a3_nonzero_a4_nonzero) {
  TOUCH(Rules_ListInstancesForClassOrModule(0, 0, 1, 1));
}

/* ---- Rules_BloadCommand / Rules_HostFloatp ----
 * Both gate on Lexer_TokenExpect(1), which compares Rules_RtnArgCount()
 * (the walked length of the arg-node chain at offset+6 of the
 * dword_51A960 context) against the requested count. The existing
 * test_cov10.c / test_cov16.c coverage uses an *empty* chain, so the
 * comparison always mismatches and Lexer_TokenExpect returns -1,
 * short-circuiting both functions before their interesting lines. Build a
 * chain with exactly one node (next-pointer at offset+10 left null) so
 * Rules_RtnArgCount() == 1, matching the requested count of 1, in hopes of
 * reaching Rules_GetFileNameArg() / Rules_RtnUnknown() respectively. */
TEST(cov3_03_rules, bload_command_one_arg) {
  static unsigned char argctx[64];
  static unsigned char argnode1[64];
  int saved = dword_51A960;
  memset(argctx, 0, sizeof argctx);
  memset(argnode1, 0, sizeof argnode1);
  *(int *)(argctx + 6) = (int)(intptr_t)argnode1; /* one-node chain, next==0 */
  dword_51A960 = (int)(intptr_t)argctx;

  TOUCH(Rules_BloadCommand(0, 0.0));

  dword_51A960 = saved;
}

TEST(cov3_03_rules, host_floatp_one_arg) {
  static unsigned char argctx[64];
  static unsigned char argnode1[64];
  int saved = dword_51A960;
  memset(argctx, 0, sizeof argctx);
  memset(argnode1, 0, sizeof argnode1);
  *(int *)(argctx + 6) = (int)(intptr_t)argnode1;
  dword_51A960 = (int)(intptr_t)argctx;

  TOUCH(Rules_HostFloatp(0.0));

  dword_51A960 = saved;
}

/* ---- Rules_ResetDataObjectValue ----
 * test_cov18.c's existing coverage passes a NON-static local buffer through
 * `(int)(intptr_t)buf`, which the harness's own guidance flags as unsafe on
 * this 64-bit/32-bit-pointer-modeling build. Redo it with static storage so
 * every write through `a1` at least lands on the intended object; whatever
 * happens with the function's own decompiler-lost local ('v2', used for the
 * final few field updates) is then whatever it is, but the first several
 * lines get a fair, non-garbage run. */
TEST(cov3_03_rules, reset_data_object_value_static) {
  static unsigned char buf[256];
  memset(buf, 0, sizeof buf);
  TOUCH(Rules_ResetDataObjectValue((int)(intptr_t)buf));
}

/* ---- Rules_MultifieldDeleteRange ----
 * Past its own range-validity guard, the recovered source reads a
 * "decompiler-lost" local ('v9') as `*(_DWORD *)(v9 + 12)` to seed the
 * "copy elements before/after the deleted range" loop counters. In the
 * original x86 (clash95.asm, sub_4A28E0) that stack slot is provably the
 * spilled/reloaded second parameter (`a2`) -- the decompiler simply failed
 * to track it -- so semantically this value is meant to be `a2[3]`
 * (the source multifield's start index). Whether or not the *recompiled* C
 * build's uninitialized 'v9' happens to line up with that (it is still
 * technically UB in this rebuild), constructing an a2 whose real a2[3]/a2[4]
 * and a3/a4 would, under that original semantics, enter both copy loops
 * (v7 = a4+a2[3]-1 = 1 > a2[3] = 0, so "v10 < v7" wants a4 > 1) is worth
 * attempting -- either it hits the extra loop-body lines, or it's a no-op
 * best-effort like the existing test_cov16.c attempt. */
TEST(cov3_03_range, delete_range_wide_source_attempt) {
  static _DWORD storage[64];
  static _DWORD a1buf[8], a2buf[8];
  int i;
  memset(storage, 0, sizeof storage);
  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);

  for (i = 0; i < 5; i++) {
    *(short *)((char *)storage + 6 * i + 14) = 2;
    *(int *)((char *)storage + 6 * i + 16) = i + 1;
  }
  a2buf[2] = (_DWORD)(intptr_t)storage;
  a2buf[3] = 0; /* begin index */
  a2buf[4] = 4; /* end index -> count 5 */

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  /* delete range [2..3] (1-based) out of 5 elements */
  TOUCH(Rules_MultifieldDeleteRange(a1buf, a2buf, 3, 2, 0));
}

/* ---- Rules_DeleteFunction / Class_GetDefmessageHandlerListCommand siblings
 * already covered above; Rules_WriteConstructHeaderToCode and
 * AST_GetHashedNodeIndex are not retried here beyond what test_cov18.c /
 * test_cov2_00.c / test_cov14.c already established: both are blocked by an
 * *unconditional* dereference of a genuinely uninitialized decompiler local
 * one line into a helper (Compiler_WriteSymbolReference's '*v9' for the
 * former; AST_FindHashedNodeChain's '*v5 = v4' write for the latter) that
 * fires regardless of the arguments passed in, so no reachable input
 * unlocks further lines in either. Rules_DeleteFunction is blocked the same
 * way one level down, through Lexer_ParseValueList's own lost register --
 * the only way to make that call return without crashing (forcing
 * dword_51A964) forces it to return 0, i.e. the *same* failing branch
 * test_cov16.c already drives, so it cannot unlock the success path either. */
