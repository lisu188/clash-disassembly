/* cov15: Deffunction/Defglobal/Class watch-flag + ProcParam/Parser + Dribble/Batch/Load/Save
 * command + misc host-function registration cluster
 *
 * NOTE: this process is a native 64-bit build of code whose recovered
 * signatures model pointers as 32-bit ints (_DWORD/int). A plain automatic
 * (stack) buffer lives at a high 64-bit address that does NOT fit back into
 * 32 bits, so `(int)(intptr_t)&stack_local` silently truncates to garbage and
 * reliably segfaults the callee. `static` locals (and globals) live in the
 * low, non-PIE .bss/.data segment and truncate losslessly, matching the
 * convention already used by tests/unit/cases/test_cov10.c. Every buffer
 * whose address crosses into a recovered function below is therefore
 * declared `static`. */

/* ---- Method_PrintWatchStatusLine: a2 is a "construct" pointer; field0 self-
 * references so Rules_GetConstructNameString's (*(int*)a2)+16 deref lands back
 * inside our buffer, field+28 is aimed (with the -40 offset applied inside
 * Defgeneric_FormatMethodRestrictionsString/Method_FindByIndex when the
 * "method count" field+32 is zero) at a small method-record buffer so the
 * downstream signature-formatting helper reads real (zeroed) memory instead of
 * a wild pointer. a1 is a valid, non-null logical-name string so Output_Write's
 * unconditional strcmp_ against the real router-name table doesn't fault on a
 * NULL "name" argument. */
TEST(cov15_method, print_watch_status_line) {
  static _DWORD conbuf[64];
  static _DWORD methodbuf[32];
  memset(conbuf, 0, sizeof(conbuf));
  memset(methodbuf, 0, sizeof(methodbuf));
  conbuf[0] = (_DWORD)(intptr_t)conbuf;                 /* self ptr for name deref */
  conbuf[4] = (_DWORD)(intptr_t)"cov15_MockGeneric";    /* name string at +16 */
  conbuf[7] = (_DWORD)(intptr_t)methodbuf + 40;          /* +28: cancels Method_FindByIndex's -40 */
  conbuf[8] = 0;                                         /* +32: method count 0 -> FindByIndex returns -1 fast */
  TOUCH(Method_PrintWatchStatusLine((int)(intptr_t)"cov15_MockRouter", (int)(intptr_t)conbuf, 0));
}

/* ---- Deffunction_Delete / Deffunction_IsDeletable / Defglobal_IsDeletable:
 * these recovered signatures take no parameters (the real callee reads the
 * item pointer from a register the decompiler lost); call as declared and let
 * the crash harness absorb whatever the leftover-stack-garbage pointer does. */
TEST(cov15_deffunction, delete_no_args) {
  TOUCH(Deffunction_Delete());
}

TEST(cov15_deffunction, is_deletable_no_args) {
  TOUCH(Deffunction_IsDeletable());
}

TEST(cov15_defglobal, is_deletable_no_args) {
  TOUCH(Defglobal_IsDeletable());
}

/* ---- Deffunction_IncrementBusyCount: ++*(result+20). */
TEST(cov15_deffunction, increment_busy_count) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof(obj));
  TOUCH(Deffunction_IncrementBusyCount((int)(intptr_t)obj));
  CHECK_EQ(obj[5], 1); /* byte offset 20 == DWORD index 5 */
}

/* ---- Deffunction_ReportCantDelete: swaps its args into
 * Rules_ReportCantDeleteItem(a2,a1), whose own "a1" parameter is unused and
 * whose "a2" is only ever passed through as an opaque int content argument to
 * Output_Write (never dereferenced while the router tables are empty), so any
 * integers are safe here. */
TEST(cov15_deffunction, report_cant_delete) {
  TOUCH(Deffunction_ReportCantDelete(0, 0));
  TOUCH(Deffunction_ReportCantDelete(1, 2));
}

/* ---- Deffunction_SetWatchFlagField / Deffunction_GetWatchFlagField: plain
 * 16-bit field accessors at byte offset 28. */
TEST(cov15_deffunction, set_get_watch_flag_field) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof(obj));
  TOUCH(Deffunction_SetWatchFlagField(1, (int)(intptr_t)obj));
  CHECK_EQ(Deffunction_GetWatchFlagField((int)(intptr_t)obj), 1);
  TOUCH(Deffunction_SetWatchFlagField(0, (int)(intptr_t)obj));
  CHECK_EQ(Deffunction_GetWatchFlagField((int)(intptr_t)obj), 0);
}

/* ---- Class_IncrementBusyCount: ++*(result+24). */
TEST(cov15_class, increment_busy_count) {
  static _DWORD obj[64];
  memset(obj, 0, sizeof(obj));
  TOUCH(Class_IncrementBusyCount((int)(intptr_t)obj));
  CHECK_EQ(obj[6], 1); /* byte offset 24 == DWORD index 6 */
}

/* ---- ProcParam_GetWildcardArgumentValue: reads payload = *(a1+16), then
 * defers to ProcParam_BuildWildcardMultifield, which (since the memory pool
 * global dword_54DBA8 defaults to NULL in this unit-test process, exactly as
 * every other allocator-touching Register-family function in this codebase's
 * test suite does) is expected to fault deep inside the allocator path;
 * still exercised for whatever coverage the entry lines give before that. */
TEST(cov15_procparam, get_wildcard_argument_value) {
  static _DWORD a1buf[64];
  static _DWORD a2buf[64];
  memset(a1buf, 0, sizeof(a1buf));
  memset(a2buf, 0, sizeof(a2buf));
  a1buf[4] = 0; /* +16 payload */
  TOUCH(ProcParam_GetWildcardArgumentValue((int)(intptr_t)a1buf, a2buf));
}

/* ---- Parser_FindProcParamIndex: walks a singly linked list of param nodes
 * (id at byte offset 2, next pointer at byte offset 10) looking for a1,
 * falling back to comparing against a3 when the list is empty/exhausted.
 * Exercises: empty-list match, empty-list mismatch, found mid-chain (normal
 * while-exit), and exhausted-chain match/mismatch (via the internal goto). */
TEST(cov15_parser, find_proc_param_index) {
  static unsigned char node1[32], node2[32];
  memset(node1, 0, sizeof(node1));
  memset(node2, 0, sizeof(node2));

  *(_DWORD *)(node1 + 2) = 10;
  *(_DWORD *)(node1 + 10) = (_DWORD)(intptr_t)node2;
  *(_DWORD *)(node2 + 2) = 20;
  *(_DWORD *)(node2 + 10) = 0;

  /* empty list, a1 == a3 -> returns 1 */
  CHECK_EQ(Parser_FindProcParamIndex(42, 0, 42), 1);
  /* empty list, a1 != a3 -> returns 0 */
  CHECK_EQ(Parser_FindProcParamIndex(42, 0, 99), 0);
  /* found at 2nd node -> normal while-loop exit, returns 2 */
  CHECK_EQ(Parser_FindProcParamIndex(20, (int)(intptr_t)node1, 0), 2);
  /* exhausted chain, a1 == a3 fallback -> returns 3 (result already advanced) */
  CHECK_EQ(Parser_FindProcParamIndex(99, (int)(intptr_t)node1, 99), 3);
  /* exhausted chain, a1 != a3 -> returns 0 */
  CHECK_EQ(Parser_FindProcParamIndex(99, (int)(intptr_t)node1, 5), 0);
}

/* ---- Rules_RegisterFileIOCommands / Rules_RegisterControlFlowFunctions /
 * Rules_RegisterMiscFunctions / Rules_RegisterIOHostFunctions: pure
 * side-effecting registration wrappers, called the same way test_cov10.c
 * calls its own Rules_Register-family targets -- safe to invoke directly
 * even though the underlying allocator pool is uninitialized in this
 * process. */
TEST(cov15_rules, register_file_io_commands) {
  TOUCH(Rules_RegisterFileIOCommands());
}

TEST(cov15_rules, register_control_flow_functions) {
  TOUCH(Rules_RegisterControlFlowFunctions());
}

TEST(cov15_rules, register_misc_functions) {
  TOUCH(Rules_RegisterMiscFunctions());
}

TEST(cov15_rules, register_io_host_functions) {
  TOUCH(Rules_RegisterIOHostFunctions());
}

/* ---- Dribble_GetcRouter: deactivates/activates the (empty by default)
 * "Dribble" router -- both no-ops while dword_51A604 is NULL -- then peeks a
 * char and appends it; every step is a documented no-op under the default
 * zeroed global router/dribble state, so this is safe to call directly. */
TEST(cov15_dribble, getc_router) {
  TOUCH(Dribble_GetcRouter());
}

/* ---- Rules_DribbleOnCommand / Rules_BatchCommand / Rules_BatchStarCommand /
 * Rules_LoadCommand / Rules_LoadStarCommand / Rules_SaveCommand /
 * Rules_HostRemoveFile / Rules_HostRenameFile: all start with
 * Lexer_TokenExpect(N), whose Rules_RtnArgCount/Rules_RtnUnknown helpers walk
 * a list rooted at the global dword_51A960 (NULL by default, which would
 * fault at address+6). Point it at a zeroed buffer so the arg-count walk
 * terminates at 0 instead of crashing; with 0 real arguments the expected
 * count (1) mismatches, so each of these commands takes its early
 * "return 0" branch deterministically. */
TEST(cov15_rules, dribble_on_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_DribbleOnCommand(0, 0.0));
  dword_51A960 = saved;
}

/* ---- Rules_DribbleOffCommand: Lexer_TokenExpect(0) against the same zeroed
 * (0-length) arg chain matches the expected count of 0, so this drives past
 * the guard into Dribble_TurnOff(), which is itself a safe no-op chain under
 * default-zeroed dribble globals. */
TEST(cov15_rules, dribble_off_command) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_DribbleOffCommand());
  dword_51A960 = saved;
}

TEST(cov15_rules, batch_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_BatchCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, batch_star_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_BatchStarCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, load_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_LoadCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, load_star_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_LoadStarCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, save_command_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_SaveCommand(0, 0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, host_remove_file) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_HostRemoveFile(0.0));
  dword_51A960 = saved;
}

TEST(cov15_rules, host_rename_file) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_HostRenameFile(0.0));
  dword_51A960 = saved;
}

/* ---- Rules_HostRandom / Rules_HostSeed: also gated by Lexer_TokenExpect,
 * against dword_51A960. Rules_HostRandom expects 0 args (matches the zeroed
 * 0-length chain) so it falls through to j_rand_(); Rules_HostSeed expects 1
 * arg (mismatches) so it takes the early return branch. */
TEST(cov15_rules, host_random) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_HostRandom());
  dword_51A960 = saved;
}

TEST(cov15_rules, host_seed_bad_args) {
  static unsigned char argnode[256];
  memset(argnode, 0, sizeof(argnode));
  int saved = dword_51A960;
  dword_51A960 = (int)(intptr_t)argnode;
  TOUCH(Rules_HostSeed(0, 0.0));
  dword_51A960 = saved;
}

/* ---- Rules_BatchQueryStdin: plain strcmp_ wrapper; strcmp_'s own recovered
 * signature narrows its pointer args to 32-bit _DWORD, so the string buffer
 * must be `static` (low, truncation-safe address) rather than a stack local. */
TEST(cov15_rules, batch_query_stdin) {
  static char buf[16];
  memset(buf, 0, sizeof(buf));
  Compat_CopyPrefixN(buf, "stdin", 6);
  CHECK(Rules_BatchQueryStdin(buf));
  Compat_CopyPrefixN(buf, "notstdin", 9);
  CHECK(!Rules_BatchQueryStdin(buf));
}

/* ---- Rules_BatchGetChar: falls into Rules_BatchReadChar, which
 * unconditionally dereferences *(dword_51ACA8+4) before anything else; point
 * that global at a zeroed scratch buffer so the walk sees "0 bytes buffered"
 * and safely falls through to the (stubbed, no-op) fgetc_/CRT_PutcToStream
 * layer instead of faulting on the default-NULL global. */
TEST(cov15_rules, batch_get_char) {
  static _DWORD streambuf[8];
  memset(streambuf, 0, sizeof(streambuf));
  int saved = dword_51ACA8;
  dword_51ACA8 = (_DWORD)(intptr_t)streambuf;
  TOUCH(Rules_BatchGetChar(4242));
  dword_51ACA8 = saved;
}

/* ---- Rules_BatchExitFunction: delegates to Rules_CloseAllBatchSources,
 * which is a safe no-op chain (dword_54E6C8/dword_51ACB4 are 0 by default,
 * and the router tables are empty). */
TEST(cov15_rules, batch_exit_function) {
  static int scratch;
  scratch = 0;
  TOUCH(Rules_BatchExitFunction(&scratch));
}
