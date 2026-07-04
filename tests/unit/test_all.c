/* Coverage aggregator translation unit.
 *
 * This is the ONLY place clash95.c is compiled for the unit-test/coverage
 * target. Including it here (rather than linking it) makes the ~300 static
 * recovered helpers directly reachable from test cases without modifying the
 * recovered source. Each tests/unit/cases/*.c is #included below (not compiled
 * as its own TU) so it shares this TU's view of clash95.c.
 *
 * Coverage is measured over clash95.c line ranges only (the pure testable set
 * frozen in tests/unit/pure_set.json); see tools/measure_pure_coverage.py. */

#include "clash95.c"

#include "clash_test.h"

/* Provided by bootstrap_main.c in the game build; the coverage TU does not
 * link that file, so supply the same trivial fallback (referenced by two weak
 * function-pointer globals in clash95.c). */
int _no_support_loaded(void) { return 0; }

/* Symbols the game build resolves via bootstrap_main.c / Win32 import libs /
 * weak CRT stubs, which the coverage target does not link. Provide benign
 * fallbacks so gc-sections-kept recovered code links; crash isolation covers
 * any that misbehave when actually exercised. */
static int cov_render_hook_noop(int a1, char a2, DWORD a3) {
  (void)a1;
  (void)a2;
  (void)a3;
  return 0;
}
int (*g_RenderHook)(int a1, char a2, DWORD a3) = cov_render_hook_noop;

DWORD __stdcall GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lp) {
  if (lp) {
    memset(lp, 0, sizeof(*lp));
  }
  return 0; /* TIME_ZONE_ID_UNKNOWN */
}

int getenv_(void) { return 0; }
int _brktime_(_DWORD a1, _DWORD a2) {
  (void)a1;
  (void)a2;
  return 0;
}
int wcstombs_(_DWORD a1, _DWORD a2) {
  (void)a1;
  (void)a2;
  return 0;
}
/* Referenced once via an implicit (int, K&R) declaration inside clash95.c;
 * match that to avoid a conflicting-type error. */
int _I8D() { return 0; }

/* Thread/CRT/Win32 symbols with no definition in this port. In the game link
 * they are dropped by --gc-sections (nothing reachable calls them); providing
 * benign stubs here lets the unit tests exercise the recovered functions that
 * DO reference them (CRT thread setup, _beginthread, mbcs, guarded init)
 * instead of leaving those functions un-linkable and uncovered. */
static _DWORD cov_thread_data_block[256];
int _GetThreadData_(void) {
  memset(cov_thread_data_block, 0, sizeof cov_thread_data_block);
  return (int)(intptr_t)cov_thread_data_block;
}
int _ReallocThreadData_(void) { return (int)(intptr_t)cov_thread_data_block; }
int _RemoveThreadData_(void) { return 0; }
int ismbclegal_(_DWORD a1, _DWORD a2) {
  (void)a1;
  (void)a2;
  return 1;
}
_DWORD j___NTAddFileHandle_(void) { return 0; }
int __cdecl CRT_RunGuardedStaticLocalInit(void) { return 0; }
int LoadLibraryA() { return 0; } /* implicit-int at its only call site */
FARPROC __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
  (void)hModule;
  (void)lpProcName;
  return 0;
}
HANDLE __stdcall CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
                              SIZE_T dwStackSize,
                              LPTHREAD_START_ROUTINE lpStartAddress,
                              LPVOID lpParameter, DWORD dwCreationFlags,
                              LPDWORD lpThreadId) {
  (void)lpThreadAttributes;
  (void)dwStackSize;
  (void)lpStartAddress;
  (void)lpParameter;
  (void)dwCreationFlags;
  if (lpThreadId) {
    *lpThreadId = 0;
  }
  return 0; /* pretend thread creation failed; callers take the error path */
}

/* CRT thread-data / lock / exception / console internals referenced (via
 * gc-dropped paths in the game link) by recovered CRT_* functions the unit
 * tests now exercise. All are matched to their implicit int call-site type
 * except SetUnhandledExceptionFilter (which has an active prototype). */
int GetCurrentThread() { return 0; }
int WriteFile() { return 0; }
int UnhandledExceptionFilter() { return 0; }
LPTOP_LEVEL_EXCEPTION_FILTER __stdcall
SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER f) {
  (void)f;
  return 0;
}
int CRT_ConstructThreadDataBlock() { return 0; }
int CRT_DestroyThreadDataBlock() { return 0; }
int CRT_DispatchRegisteredFpeHandler() { return 0; }
int _fatal_runtime_error_() { return 0; }
int _NTConsoleOutput_() { return 0; }
int _AddThreadData_() { return 1; }
int _InitThreadData_() { return 0; }
int _NTRemoveFileHandle_() { return 0; }
int j___NTRemoveFileHandle_() { return 0; }
int j___NTAddFileHandle__0() { return 0; }
void endthread_() {}
/* calloc_ result is used as a pointer; return distinct low (.bss) addresses
 * that survive the recovered code's 32-bit pointer round-trip. */
int calloc_(int a, int b) {
  static char cov_arena[1 << 20];
  static int cov_off = 0;
  int n = (a > 0 ? a : 1) * (b > 0 ? b : 1);
  if (n <= 0 || n > 8192) {
    n = 8192;
  }
  if (cov_off + n > (int)sizeof cov_arena) {
    cov_off = 0;
  }
  {
    char *p = cov_arena + cov_off;
    cov_off += n;
    memset(p, 0, n);
    return (int)(intptr_t)p;
  }
}

clash_test_entry g_clash_tests[CLASH_MAX_TESTS];
int g_clash_test_count = 0;
int g_clash_cur_failed = 0;

void clash_register(const char *name, clash_test_fn fn) {
  if (g_clash_test_count < CLASH_MAX_TESTS) {
    g_clash_tests[g_clash_test_count].name = name;
    g_clash_tests[g_clash_test_count].fn = fn;
    ++g_clash_test_count;
  }
}

/* Fault isolation: each test runs in a forked child so a segfault, a hard
 * exit()/abort(), OR an infinite GetMessageA-style spin inside recovered code
 * cannot take down the whole run or truncate coverage. The child installs an
 * alarm() watchdog and flushes its gcov counters (libgcov merges them into the
 * shared .gcda) before terminating, so every test's coverage accumulates no
 * matter how the test ends. */
#include <unistd.h>
#include <sys/wait.h>

extern void __gcov_dump(void);

static sigjmp_buf g_crash_jmp;
static volatile sig_atomic_t g_in_test = 0;

static void clash_crash_handler(int sig) {
  if (g_in_test) {
    siglongjmp(g_crash_jmp, sig);
  }
  _exit(139);
}

/* ---- test case files (included, not separately compiled) ---- */
#include "cases/test_smoke.c"
/* >>> COV CASES BEGIN (generated by tools/wire_cov_cases.py) */
#include "cases/test_cov00.c"
#include "cases/test_cov01.c"
#include "cases/test_cov02.c"
#include "cases/test_cov03.c"
#include "cases/test_cov04.c"
#include "cases/test_cov05.c"
#include "cases/test_cov06.c"
#include "cases/test_cov07.c"
#include "cases/test_cov08.c"
#include "cases/test_cov09.c"
#include "cases/test_cov10.c"
#include "cases/test_cov11.c"
#include "cases/test_cov12.c"
#include "cases/test_cov13.c"
#include "cases/test_cov14.c"
#include "cases/test_cov15.c"
#include "cases/test_cov16.c"
#include "cases/test_cov17.c"
#include "cases/test_cov18.c"
#include "cases/test_cov19.c"
#include "cases/test_cov20.c"
#include "cases/test_cov21.c"
#include "cases/test_cov22.c"
#include "cases/test_cov23.c"
#include "cases/test_cov2_00.c"
#include "cases/test_cov2_01.c"
#include "cases/test_cov2_02.c"
#include "cases/test_cov2_04.c"
#include "cases/test_cov2_05.c"
#include "cases/test_cov2_06.c"
#include "cases/test_cov2_07.c"
#include "cases/test_cov2_08.c"
#include "cases/test_cov2_09.c"
#include "cases/test_cov3_00.c"
#include "cases/test_cov3_01.c"
#include "cases/test_cov3_02.c"
#include "cases/test_cov3_03.c"
#include "cases/test_cov3_04.c"
#include "cases/test_cov3_05.c"
#include "cases/test_cov3_06.c"
#include "cases/test_cov3_07.c"
#include "cases/test_cov4_00.c"
#include "cases/test_cov4_01.c"
#include "cases/test_cov4_02.c"
#include "cases/test_cov4_03.c"
#include "cases/test_cov4_04.c"
#include "cases/test_cov4_05.c"
#include "cases/test_cov4_06.c"
#include "cases/test_cov4_07.c"
#include "cases/test_cov5_00.c"
#include "cases/test_cov5_01.c"
#include "cases/test_cov5_02.c"
#include "cases/test_extra.c"
#include "cases/test_gameplay_mission04.c"
#include "cases/test_gameplay_objectives.c"
#include "cases/test_thin00.c"
#include "cases/test_thin01.c"
#include "cases/test_thin02.c"
#include "cases/test_thin03.c"
/* <<< COV CASES END */

/* Run one test in a child process; returns 0 pass, 1 fail, 2 crashed/exited. */
static int run_one(int idx) {
  pid_t pid = fork();
  if (pid < 0) {
    g_clash_cur_failed = 0;
    g_clash_tests[idx].fn(); /* fallback: inline, no isolation for this one */
    return g_clash_cur_failed ? 1 : 0;
  }
  if (pid == 0) {
    int sig;
    signal(SIGSEGV, clash_crash_handler);
    signal(SIGBUS, clash_crash_handler);
    signal(SIGFPE, clash_crash_handler);
    signal(SIGABRT, clash_crash_handler);
    signal(SIGALRM, clash_crash_handler);
    g_clash_cur_failed = 0;
    g_in_test = 1;
    sig = sigsetjmp(g_crash_jmp, 1);
    if (sig == 0) {
      alarm(8); /* watchdog for GetMessageA-style infinite spins */
      g_clash_tests[idx].fn();
      alarm(0);
      g_in_test = 0;
      __gcov_dump(); /* flush coverage before a clean child exit */
      _exit(g_clash_cur_failed ? 1 : 0);
    }
    g_in_test = 0;
    __gcov_dump(); /* recovered from a fatal signal/timeout: keep what ran */
    _exit(2);
  }
  {
    int status = 0;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      int rc = WEXITSTATUS(status);
      return (rc == 1) ? 1 : (rc >= 2 ? 2 : 0);
    }
    return 2; /* killed by an uncaught signal */
  }
}

int main(void) {
  int i, passed = 0, failed = 0, crashed = 0;

  for (i = 0; i < g_clash_test_count; ++i) {
    int r = run_one(i);
    if (r == 0) {
      ++passed;
    } else if (r == 1) {
      ++failed;
      fprintf(stderr, "FAIL  %s\n", g_clash_tests[i].name);
    } else {
      ++crashed;
      fprintf(stderr, "CRASH %s\n", g_clash_tests[i].name);
    }
  }

  fprintf(stderr, "\n== %d passed, %d failed, %d crashed, %d total ==\n", passed,
          failed, crashed, g_clash_test_count);
  return failed ? 1 : 0;
}
