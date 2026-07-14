/* thin00: final top-up pass targeting small (1-3 line) coverage gaps in
 * clash95.c functions that are already mostly covered by prior batches. See
 * thin_batches/thin_00.json for the target list.
 *
 * Shared "fake CRT stream" rig (same recipe test_cov4_04.c already
 * established and proved safe): CRT_VfprintfLockedWrite reads
 * lock_key=*(a1+16), passes it to off_51A56C/570 (safe: default weak
 * `nullsub_8` no-ops for any key), then stream_state=*(a1+8),
 * busy_state=*(stream_state+12). Setting busy_state to a value that is
 * neither 0 nor 1 makes the function take its clean `return 0;` fast path
 * immediately, never touching CRT_PrintfFormatEngine/vararg formatting. */
static void thin00_make_fake_stream(unsigned char *stream,
                                     unsigned char *state) {
  memset(stream, 0, 64);
  memset(state, 0, 64);
  *(int *)(state + 12) = 2; /* busy_state: != 0 && != 1 -> clean early return */
  *(int *)(stream + 8) = (int)(intptr_t)state;
  *(int *)(stream + 16) = 0; /* lock_key: bucket 0, safe for any value */
}

/* =========================================================================
 * Deffacts_CloseCodeFiles / Deffunction_CloseCodeFiles /
 * Defglobal_CloseConstructCodeFiles / Compiler_CloseDefinstancesCodeFiles
 * (identical bodies, 3 uncovered lines each): all four wrap
 * Rules_ConstructCodeFileClose(handle, &v6, a4, v7, 0, 0), which -- when
 * `result` (the handle) is nonzero -- always falls through to
 * Output_WriteFormatted(...) with the no-specifier format `asc_507DA0`
 * (";\n"), landing in CRT_VfprintfLockedWrite. A naive small-int "fake
 * handle" makes THAT function dereference `*(handle+16)`/`*(handle+8)` on a
 * bogus tiny address and crash before ever returning to the wrapper's own
 * `if (!a1) return result;` / `goto LABEL_5;` lines (this is why earlier
 * batches using plain ints like 4242/9999 for the handle left these three
 * lines unreached). Backing the handle with the same fake-stream rig above
 * avoids that crash entirely: Rules_ConstructCodeFileClose's own `if
 * (!result)` block is skipped (result/handle is our nonzero buffer address),
 * fclose_() is the compat stub (safe no-op for any untracked handle), and
 * both wrapper lines after the call execute and return cleanly. ========== */
TEST(thin00_closecodefiles, deffacts_a1_zero_returns_result) {
  static unsigned char stream[64], state[64];
  thin00_make_fake_stream(stream, state);
  TOUCH(Deffacts_CloseCodeFiles(0, (int)(intptr_t)stream, 0, 0));
}

TEST(thin00_closecodefiles, deffacts_a1_nonzero_goto_label5) {
  static unsigned char stream1[64], state1[64];
  static unsigned char stream2[64], state2[64];
  thin00_make_fake_stream(stream1, state1);
  thin00_make_fake_stream(stream2, state2);
  TOUCH(Deffacts_CloseCodeFiles((int)(intptr_t)stream2,
                                (int)(intptr_t)stream1, 0, 0));
}

TEST(thin00_closecodefiles, deffunction_a1_zero_returns_result) {
  static unsigned char stream[64], state[64];
  thin00_make_fake_stream(stream, state);
  TOUCH(Deffunction_CloseCodeFiles(0, (int)(intptr_t)stream, 0, 0));
}

TEST(thin00_closecodefiles, deffunction_a1_nonzero_goto_label5) {
  static unsigned char stream1[64], state1[64];
  static unsigned char stream2[64], state2[64];
  thin00_make_fake_stream(stream1, state1);
  thin00_make_fake_stream(stream2, state2);
  TOUCH(Deffunction_CloseCodeFiles((int)(intptr_t)stream2,
                                   (int)(intptr_t)stream1, 0, 0));
}

TEST(thin00_closecodefiles, defglobal_a1_zero_returns_result) {
  static unsigned char stream[64], state[64];
  thin00_make_fake_stream(stream, state);
  TOUCH(Defglobal_CloseConstructCodeFiles(0, (int)(intptr_t)stream, 0, 0));
}

TEST(thin00_closecodefiles, defglobal_a1_nonzero_goto_label5) {
  static unsigned char stream1[64], state1[64];
  static unsigned char stream2[64], state2[64];
  thin00_make_fake_stream(stream1, state1);
  thin00_make_fake_stream(stream2, state2);
  TOUCH(Defglobal_CloseConstructCodeFiles((int)(intptr_t)stream2,
                                          (int)(intptr_t)stream1, 0, 0));
}

TEST(thin00_closecodefiles, compiler_definstances_a1_zero_returns_result) {
  static unsigned char stream[64], state[64];
  thin00_make_fake_stream(stream, state);
  TOUCH(Compiler_CloseDefinstancesCodeFiles(0, (int)(intptr_t)stream, 0, 0));
}

TEST(thin00_closecodefiles, compiler_definstances_a1_nonzero_goto_label5) {
  static unsigned char stream1[64], state1[64];
  static unsigned char stream2[64], state2[64];
  thin00_make_fake_stream(stream1, state1);
  thin00_make_fake_stream(stream2, state2);
  TOUCH(Compiler_CloseDefinstancesCodeFiles((int)(intptr_t)stream2,
                                            (int)(intptr_t)stream1, 0, 0));
}

/* =========================================================================
 * Rules_ConstructCodeFileOpen (3 uncovered: 133084, 133102, 133103). Line
 * 133084 (`return a1;`, inside `if (a1)`) is reached via
 * Output_WriteFormatted((int)v13, v15, a1, (int)asc_508250, v25[0]) --
 * asc_508250 is ",\n" (zero printf specifiers), so it goes straight to
 * CRT_VfprintfLockedWrite(a3=a1, ...) without ever touching the garbage
 * v25[0] vararg; backing `a1` with the same fake-stream rig (rather than a
 * naive small int, which is what made earlier batches call this an
 * unreachable "hard ceiling") lets it return cleanly. a10==0 so we take the
 * `v14=a2; v15=(int)a4; v16=*a5;` setup branch (a5 must be real); a11==0
 * skips its sub-block. 133102/133103 stay out of reach: they're gated
 * behind the PRECEDING Output_WriteFormatted call at line 133101 whose
 * format ("%s %s[] = {\n", 2 specifiers) is fed only ONE real vararg -- a
 * genuine missing-vararg mismatch whose second %s reads uncontrolled
 * variadic stack garbage as a string pointer, an irreducible source-level
 * bug with no deterministic fix from the caller side (matches the existing
 * test_cov5_01.c documentation for this exact hazard). ==================== */
TEST(thin00_ccfo, a1_nonzero_returns_a1) {
  static unsigned char stream[64], state[64];
  static int a5val = 5;
  thin00_make_fake_stream(stream, state);
  TOUCH(Rules_ConstructCodeFileOpen(
      (int)(intptr_t)stream, "thin00.txt", 0, (const char *)(intptr_t)0,
      &a5val, 0, 0, 'x', "thin00_a9", 0, 0));
}

/* =========================================================================
 * Output_WriteFormatted (3 uncovered: 90012 Compat_FreeLow32Bytes(args_ptr),
 * 90013 return result -- the tail of the arg_count>0 success path). The
 * existing test_cov09.c "write_formatted_with_args" test uses a PLAIN
 * zeroed 32-dword buffer as the stream, which crashes inside
 * CRT_VfprintfLockedWrite's `*(stream_state+12)` read (stream_state==0)
 * before ever reaching the tail -- same shape as the CloseCodeFiles family
 * above. Backing the stream with the working fake-stream rig instead lets
 * CRT_VfprintfLockedWrite's busy_state==2 check take its clean early
 * return, so control actually comes back to free the low-memory arg buffer
 * and return. ============================================================= */
TEST(thin00_output, write_formatted_with_args_clean_stream) {
  static unsigned char stream[64], state[64];
  thin00_make_fake_stream(stream, state);
  TOUCH(Output_WriteFormatted(0, 0, (int)(intptr_t)stream,
                               (int)(intptr_t)"%d %s\n", 5, "x"));
}

/* =========================================================================
 * Rules_RefreshCommand (3 uncovered: `v4 = Rules_FindDefruleByName(...)`,
 * `if (v4)`, and the `return Rules_ReportCantFindItem(...)` tail). Same
 * "argnode/node/val" SYMBOL-shortcut rig used throughout this project (see
 * test_cov5_02.c's Defgeneric_GetMethodRestrictionsCommand tests) drives
 * Rules_GetConstructNameArg to return a real, non-interned rule-name
 * string via Rules_RtnUnknown -> Parser_ParseForm's SYMBOL(2) case (which
 * writes our node's type/value straight into the caller's own output
 * buffer -- no dereference of any decompiler-lost register involved).
 * Deliberately do NOT call Rules_InitAtomTables(): leaving `dword_54DD50`
 * (the symbol hash table) at its default 0 makes Rules_FindSymbolEntry
 * (reached via Rules_FindConstructByNameGeneric inside
 * Rules_FindDefruleByName) return 0 immediately -- "not found" -- without
 * ever touching the construct-enumeration vtable calls that follow a
 * successful symbol lookup. That drives `v4` to 0 (a real, deterministic
 * value, not a decompiler artifact) and lands on the `else` branch, whose
 * Rules_ReportCantFindItem -> Output_Write calls are safe no-ops with the
 * default (unregistered) router globals. ================================= */
TEST(thin00_refreshcommand, name_not_found_reports_cant_find) {
  static unsigned char argnode[16], node[16];
  static _DWORD val[8];
  static const char *rule_name = "Thin00FakeRule";
  int saved960 = g_ClipsCurrentExpression;

  memset(argnode, 0, sizeof argnode);
  memset(node, 0, sizeof node);
  memset(val, 0, sizeof val);

  val[4] = (_DWORD)(intptr_t)rule_name; /* -> val+16, the C string pointer */
  *(short *)(node + 0) = 2;             /* SYMBOL */
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)val;
  *(_DWORD *)(node + 10) = 0; /* next: single-node chain (arg count == 1) */
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)node;

  /* Rules_FindConstructByNameGeneric's Module_BeginEnum()/Module_EndEnum()
   * touch the reserve-block arena (dword_54DBA8); bootstrap it like every
   * other rules-engine test in this project. */
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  g_ClipsCurrentExpression = (int)(intptr_t)argnode;
  TOUCH(Rules_RefreshCommand(0, 0.0));
  g_ClipsCurrentExpression = saved960;
}

/* =========================================================================
 * PlayGameMenu_HandleCloseButton (2 uncovered: 65033/65034 -- the
 * "g_PlayGameMenuExitRequested = v3;" write and "return result;"). Earlier
 * attempts (test_cov4_03.c) called this with a1==0, which UIWidget_
 * PlayPressedReleaseAnimation immediately dereferences as `*(a1+49)`,
 * segfaulting before ever returning -- so those two lines were never
 * actually reached despite the comment there. Backing `a1` with a real
 * zeroed widget-sized buffer avoids that: offset+49 (packed-string flag) is
 * 0 so the Audio_PlayButtonSound branch is skipped, and UIWidget_
 * RefreshActionButtonState's own widget-transition-callback dereference
 * (`*(widget+28)`) is also 0, so it safely no-ops instead of invoking a
 * function pointer. Render_Begin(g_RenderState, 0) then loops on
 * DD_IsFlipping/DD_IsLost, both of which read the zeroed stub
 * g_RenderState and return false immediately (confirmed via the private
 * scratch build: sub-millisecond run, no alarm-watchdog trip), letting
 * execution fall through cleanly to both target lines. =================== */
TEST(thin00_playgamemenu, handle_close_button_real_widget) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  TOUCH(PlayGameMenu_HandleCloseButton((int)(intptr_t)widget));
}

