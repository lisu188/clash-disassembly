/* Minimal dependency-free unit-test framework for the clash95 coverage TU.
 *
 * Test cases are compiled into a single translation unit (test_all.c) that
 * also #includes clash95.c, so both static and external recovered functions
 * are directly callable. Each TEST(...) auto-registers via a constructor. */
#ifndef CLASH_TEST_H
#define CLASH_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>

typedef void (*clash_test_fn)(void);

typedef struct {
  const char *name;
  clash_test_fn fn;
} clash_test_entry;

#define CLASH_MAX_TESTS 40000
extern clash_test_entry g_clash_tests[CLASH_MAX_TESTS];
extern int g_clash_test_count;
extern int g_clash_cur_failed;

void clash_register(const char *name, clash_test_fn fn);

#define TEST(suite, name)                                                    \
  static void suite##_##name##_body(void);                                   \
  __attribute__((constructor)) static void suite##_##name##_reg(void) {      \
    clash_register(#suite "." #name, suite##_##name##_body);                 \
  }                                                                          \
  static void suite##_##name##_body(void)

#define CHECK(cond)                                                          \
  do {                                                                       \
    if (!(cond)) {                                                           \
      fprintf(stderr, "  CHECK failed: %s (%s:%d)\n", #cond, __FILE__,       \
              __LINE__);                                                     \
      g_clash_cur_failed = 1;                                                \
    }                                                                        \
  } while (0)

#define CHECK_EQ(a, b)                                                       \
  do {                                                                       \
    long long _va = (long long)(a), _vb = (long long)(b);                    \
    if (_va != _vb) {                                                        \
      fprintf(stderr, "  CHECK_EQ failed: %s(%lld) != %s(%lld) (%s:%d)\n",   \
              #a, _va, #b, _vb, __FILE__, __LINE__);                         \
      g_clash_cur_failed = 1;                                                \
    }                                                                        \
  } while (0)

/* Execute an expression purely for coverage; value/behavior unchecked. */
#define TOUCH(expr)                                                          \
  do {                                                                       \
    (void)(expr);                                                            \
  } while (0)

#endif
