/* cov12 cluster: Rules_Print*, Rules_*ToSymbol, exit/host-function setup, IO
 * router matching, CRT lock/thread-data helpers, CRT string/hex formatting,
 * CRT file/dir Win32-shim wrappers, misc builtin stubs, deftemplate module
 * patch. */

/* Str_Intern (used by Rules_FloatToSymbol/Rules_LongIntegerToSymbol/
 * Rules_RegisterHostFunction) and Module_BeginEnum (used by
 * Rules_PatchDeftemplateSlotModuleRef) both index through global arenas
 * (dword_54DBA8, dword_54DD50, ...) that stay NULL until the recovered
 * allocator/atom-table bootstrap runs. Do that once, lazily, before poking
 * anything that needs it. */
static int cov12_globals_ready = 0;
static void cov12_ensure_globals(void) {
  if (cov12_globals_ready) return;
  cov12_globals_ready = 1;
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
}

/* ---- Rules_PrintLongInteger / Rules_PrintTally (Output_Write plumbing) --- */
TEST(cov12_rules, print_long_integer) {
  int router = (int)(intptr_t)(uintptr_t)"werror";
  TOUCH(Rules_PrintLongInteger(router, 12345));
  TOUCH(Rules_PrintLongInteger(router, -42));
  TOUCH(Rules_PrintLongInteger(router, 0));
}

TEST(cov12_rules, print_tally_zero) {
  int router = (int)(intptr_t)(uintptr_t)"werror";
  /* a2 == 0 -> early return, skips the whole body */
  TOUCH(Rules_PrintTally(router, 0, 0, 0));
}

TEST(cov12_rules, print_tally_one) {
  int router = (int)(intptr_t)(uintptr_t)"werror";
  /* a2 == 1 -> takes the "!= 1" false branch (a4 kept) */
  TOUCH(Rules_PrintTally(router, 1, 0, (int)(intptr_t)(uintptr_t)"unit"));
}

TEST(cov12_rules, print_tally_many) {
  int router = (int)(intptr_t)(uintptr_t)"werror";
  /* a2 != 1 -> takes the "!= 1" true branch (a4 replaced) */
  TOUCH(Rules_PrintTally(router, 5, 0, (int)(intptr_t)(uintptr_t)"units"));
}

/* ---- Rules_FloatToSymbol / Rules_LongIntegerToSymbol (Str_Intern users) -- */
TEST(cov12_rules, float_to_symbol_plain) {
  cov12_ensure_globals();
  /* sprintf_ "%.16g" produces a '.' or 'e' -> early-return branch */
  TOUCH(Rules_FloatToSymbol(0, 3.5));
  TOUCH(Rules_FloatToSymbol(0, -2.25));
}

TEST(cov12_rules, float_to_symbol_integral) {
  cov12_ensure_globals();
  /* An integral value formatted via "%.16g" has neither '.' nor 'e' for
   * small magnitudes, forcing the reversal-copy loop at the bottom. */
  TOUCH(Rules_FloatToSymbol(0, 4.0));
  TOUCH(Rules_FloatToSymbol(0, 0.0));
}

TEST(cov12_rules, long_integer_to_symbol) {
  cov12_ensure_globals();
  TOUCH(Rules_LongIntegerToSymbol(7));
  TOUCH(Rules_LongIntegerToSymbol(-99));
  TOUCH(Rules_LongIntegerToSymbol(0));
}

/* ---- Rules_RegisterExitFunction: host-function + router bootstrap ------- */
TEST(cov12_rules, register_exit_function) {
  cov12_ensure_globals();
  TOUCH(Rules_RegisterExitFunction());
}

/* ---- IO_RouterMatchesName: exercises all three branches ----------------- */
static int cov12_router_query_zero(int a1) {
  (void)a1;
  return 0;
}
static int cov12_router_query_one(int a1) {
  (void)a1;
  return 1;
}

TEST(cov12_io, router_matches_name_no_write_ptr) {
  /* static: this address is truncated to a 32-bit "int" by the recovered
   * signature, so it must live in the binary's low static/BSS range rather
   * than on the (high, 64-bit-only) call stack. */
  static _DWORD router[16];
  memset(router, 0, sizeof(router));
  /* offset 4 (index 1) is zero -> immediate "return 0" */
  CHECK_EQ(IO_RouterMatchesName(0, (int)(intptr_t)(uintptr_t)router), 0);
}

TEST(cov12_io, router_matches_name_no_query_ptr) {
  static _DWORD router[16];
  memset(router, 0, sizeof(router));
  router[1] = 1; /* offset 4 nonzero */
  router[3] = 0; /* offset 12 zero -> "return 0" */
  CHECK_EQ(IO_RouterMatchesName(0, (int)(intptr_t)(uintptr_t)router), 0);
}

TEST(cov12_io, router_matches_name_query_returns_zero) {
  static _DWORD router[16];
  memset(router, 0, sizeof(router));
  router[1] = 1;
  router[3] = (_DWORD)(uintptr_t)cov12_router_query_zero;
  CHECK_EQ(IO_RouterMatchesName(0, (int)(intptr_t)(uintptr_t)router), 0);
}

TEST(cov12_io, router_matches_name_query_returns_one) {
  static _DWORD router[16];
  memset(router, 0, sizeof(router));
  router[1] = 1;
  router[3] = (_DWORD)(uintptr_t)cov12_router_query_one;
  CHECK_EQ(IO_RouterMatchesName(0, (int)(intptr_t)(uintptr_t)router), 1);
}

/* ---- CRT_LockLeave: only the "reached zero" branch is safely testable --- */
TEST(cov12_crt, lock_leave_noop) {
  static _DWORD lockobj[64];
  memset(lockobj, 0, sizeof(lockobj));
  lockobj[3] = 0; /* offset 12 == 0 -> function does nothing */
  TOUCH((CRT_LockLeave((int)(intptr_t)(uintptr_t)lockobj), 0));
}

TEST(cov12_crt, lock_leave_decrement_only) {
  static _DWORD lockobj[64];
  memset(lockobj, 0, sizeof(lockobj));
  lockobj[3] = 5; /* offset 12 != 0 and != 1 -> decrement only, no unlock */
  TOUCH((CRT_LockLeave((int)(intptr_t)(uintptr_t)lockobj), 0));
  CHECK_EQ(lockobj[3], 4);
}

TEST(cov12_crt, lock_leave_release) {
  static CRITICAL_SECTION cs;
  static _DWORD lockobj[64];
  memset(&cs, 0, sizeof(cs));
  memset(lockobj, 0, sizeof(lockobj));
  InitializeCriticalSection(&cs);
  EnterCriticalSection(&cs);
  *(_DWORD *)&lockobj[0] = (_DWORD)(uintptr_t)&cs; /* offset 0: critical section ptr */
  lockobj[3] = 1; /* offset 12 == 1 -> release path */
  TOUCH((CRT_LockLeave((int)(intptr_t)(uintptr_t)lockobj), 0));
  CHECK_EQ(lockobj[2], 0); /* offset 8 cleared */
}

/* NOTE: CRT_GetOrCreateThreadDataPreserveLastError,
 * CRT_DetachThreadDataAndMaybeCloseHandle and
 * CRT_DestroyTlsIndexAndThreadData all unconditionally emit calls to
 * _GetThreadData_/_ReallocThreadData_/_RemoveThreadData_, which have no
 * definition anywhere in this tree (only commented-out "weak" declarations).
 * Calling any of them makes those symbols live and breaks the link for the
 * whole coverage binary (confirmed experimentally), so they are intentionally
 * left uncovered here. */

/* ---- CRT_RegisterFinalizer: __lock_p/__lock_v are safe no-op shims but the
 * recovered body dereferences an uninitialized local ('v3' - decompiler
 * artifact); tolerate a possible crash per harness rules. */
TEST(cov12_crt, register_finalizer) {
  _DWORD lockbuf[16];
  memset(lockbuf, 0, sizeof(lockbuf));
  TOUCH(CRT_RegisterFinalizer(0, (__lock *)lockbuf, 0));
}

/* ---- CRT_FarStrLenBounded: MK_FP ignores the segment, a1 is a real ptr --- */
TEST(cov12_crt, far_strlen_bounded_hits_nul) {
  static char buf[64];
  memset(buf, 0, sizeof(buf));
  strcpy(buf, "hello");
  CHECK_EQ(CRT_FarStrLenBounded((int)(intptr_t)(uintptr_t)buf, 0, 100), 5);
}

TEST(cov12_crt, far_strlen_bounded_hits_limit) {
  static char buf[64];
  memset(buf, 'x', sizeof(buf));
  buf[63] = 0;
  CHECK_EQ(CRT_FarStrLenBounded((int)(intptr_t)(uintptr_t)buf, 0, 3), 3);
}

/* ---- CRT_FormatPaddedHexDigits: hex format + left zero-pad ------------- */
TEST(cov12_crt, format_padded_hex_digits) {
  char buf[64];
  memset(buf, 0, sizeof(buf));
  TOUCH(CRT_FormatPaddedHexDigits(255, buf, 8));
  CHECK(strlen(buf) == 8);
}

TEST(cov12_crt, format_padded_hex_digits_exact_width) {
  char buf[64];
  memset(buf, 0, sizeof(buf));
  /* result string already fills a3, so the zero-pad while-loop body never
   * executes (result goes negative immediately). */
  TOUCH(CRT_FormatPaddedHexDigits(0x1234, buf, 4));
}

/* ---- CRT_ToUpperInPlace: empty-string path is safe; non-empty path hits a
 * decompiler bug (uninitialized 'v3' pointer write) - tolerate the crash. */
TEST(cov12_crt, to_upper_in_place_empty) {
  _BYTE buf[8];
  memset(buf, 0, sizeof(buf));
  TOUCH(CRT_ToUpperInPlace(buf, 0));
}

TEST(cov12_crt, to_upper_in_place_nonempty) {
  _BYTE buf[8];
  memset(buf, 0, sizeof(buf));
  buf[0] = 'a';
  TOUCH(CRT_ToUpperInPlace(buf, 0));
}

/* ---- CRT_OpenFile / CRT_OpenFileShared intentionally skipped: they funnel
 * into CRT_CreateFileHandleFromPath, which reads the global function pointer
 * off_51A574 (initialized to &j___NTAddFileHandle_, a symbol with no
 * definition anywhere in this tree). Touching that global keeps its
 * initializer live and breaks the coverage-binary link. */

TEST(cov12_process, get_current_id) {
  TOUCH(Process_GetCurrentId());
}

/* ---- CRT_PutcCallbackForWrite: CRT_PutcToStream is a safe no-op shim ---- */
TEST(cov12_crt, putc_callback_for_write) {
  _DWORD a1[16];
  memset(a1, 0, sizeof(a1));
  TOUCH(CRT_PutcCallbackForWrite(a1, 'A'));
  CHECK_EQ(a1[4], 1);
}

/* ---- CRT_DeleteFile: exercise both success and failure paths ----------- */
TEST(cov12_crt, delete_file_missing) {
  TOUCH(CRT_DeleteFile("/nonexistent/path/cov12_missing_file.tmp", 0));
}

TEST(cov12_crt, delete_file_existing) {
  FILE *f = fopen("/tmp/cov12_delete_me.tmp", "w");
  if (f) fclose(f);
  TOUCH(CRT_DeleteFile("/tmp/cov12_delete_me.tmp", 0));
}

/* ---- Compat_FileTimeToUnixSeconds: below/above the 1970 epoch threshold - */
TEST(cov12_crt, filetime_to_unix_below_epoch) {
  CHECK_EQ(Compat_FileTimeToUnixSeconds(0, 0), 0);
}

TEST(cov12_crt, filetime_to_unix_above_epoch) {
  TOUCH(Compat_FileTimeToUnixSeconds(0, 0xFFFFFFFFu));
}

/* ---- CRT_FindFirstFile / CRT_FillFindDataRecord ------------------------ */
TEST(cov12_crt, find_first_file) {
  _DWORD out[128];
  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/tmp/*", out, 0));
}

TEST(cov12_crt, find_first_file_missing) {
  _DWORD out[128];
  memset(out, 0, sizeof(out));
  TOUCH(CRT_FindFirstFile("/no/such/dir/at/all/*", out, 0));
}

TEST(cov12_crt, fill_find_data_record_null_args) {
  _DWORD out[128];
  memset(out, 0, sizeof(out));
  CHECK_EQ(CRT_FillFindDataRecord(0, out), 0);
  CHECK_EQ(CRT_FillFindDataRecord((int)(intptr_t)(uintptr_t)out, 0), 0);
}

/* ---- CRT_MakeDirectory / CRT_RemoveDirectory --------------------------- */
TEST(cov12_crt, make_and_remove_directory) {
  TOUCH(CRT_MakeDirectory("/tmp/cov12_test_dir", 0));
  TOUCH(CRT_RemoveDirectory("/tmp/cov12_test_dir", 0));
  /* Removing again should hit the failure/_set_errno_nt_ path. */
  TOUCH(CRT_RemoveDirectory("/tmp/cov12_test_dir", 0));
}

/* ---- Trivial builtin stubs (all pure constant returns) ----------------- */
TEST(cov12_builtins, trivial_stub_returns) {
  CHECK_EQ(Rules_Builtin_0(), 0);
  CHECK_EQ(Rules_Builtin_2(), 0);
  CHECK_EQ(Rules_Builtin_3(), 0);
  CHECK_EQ(IO_StreambufStubZero(), 0);
  CHECK_EQ(Rules_Builtin_4(), 0);
}

/* ---- Rules_PatchDeftemplateSlotModuleRef: no modules registered -> the
 * enum-empty early-return path (Module_BeginEnum/NextEnum/EndEnum stay
 * balanced). */
TEST(cov12_rules, patch_deftemplate_slot_module_ref_no_modules) {
  cov12_ensure_globals();
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(0, 0));
}
