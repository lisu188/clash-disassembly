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

/* Crash isolation: a test that dereferences a bad pointer must not zero out
 * coverage accumulated by earlier tests. Recover via siglongjmp and continue. */
static sigjmp_buf g_crash_jmp;
static volatile sig_atomic_t g_in_test = 0;

static void clash_crash_handler(int sig) {
  if (g_in_test) {
    siglongjmp(g_crash_jmp, sig);
  }
  _exit(139);
}

/* ---- test case files (included, not separately compiled) ---- */
#include "cases/test_cov00.c"
#include "cases/test_cov02.c"
#include "cases/test_cov08.c"
#include "cases/test_cov09.c"
#include "cases/test_cov10.c"
#include "cases/test_smoke.c"
/* CASES-INCLUDE-MARKER (tooling appends #include lines above this marker) */

int main(void) {
  int i, passed = 0, failed = 0, crashed = 0;

  signal(SIGSEGV, clash_crash_handler);
  signal(SIGBUS, clash_crash_handler);
  signal(SIGFPE, clash_crash_handler);
  signal(SIGABRT, clash_crash_handler);

  for (i = 0; i < g_clash_test_count; ++i) {
    int sig;
    g_clash_cur_failed = 0;
    g_in_test = 1;
    sig = sigsetjmp(g_crash_jmp, 1);
    if (sig == 0) {
      g_clash_tests[i].fn();
      g_in_test = 0;
      if (g_clash_cur_failed) {
        ++failed;
        fprintf(stderr, "FAIL  %s\n", g_clash_tests[i].name);
      } else {
        ++passed;
      }
    } else {
      g_in_test = 0;
      ++crashed;
      fprintf(stderr, "CRASH(sig %d) %s\n", sig, g_clash_tests[i].name);
    }
  }

  fprintf(stderr, "\n== %d passed, %d failed, %d crashed, %d total ==\n", passed,
          failed, crashed, g_clash_test_count);
  return (failed || crashed) ? 1 : 0;
}
