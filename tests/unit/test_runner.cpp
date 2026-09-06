/* Unit-test runner. Recovered code and every case are separate translation
 * units; this file owns only registration and process isolation. */

#include "clash_test.h"

#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

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

/* Every test runs in a child so a signal, hard exit, or message-loop spin
 * cannot terminate the suite. Child coverage counters are flushed before
 * exit and libgcov merges them into the shared split-source data. */
#ifdef __cplusplus
extern "C" {
#endif
extern void __gcov_dump(void);
#ifdef __cplusplus
}
#endif

static sigjmp_buf g_crash_jmp;
static volatile sig_atomic_t g_in_test = 0;
static const char *g_test_filter = NULL;

static void clash_crash_handler(int sig) {
  if (g_in_test) {
    siglongjmp(g_crash_jmp, sig);
  }
  _exit(139);
}

static int run_one(int idx) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("test fork");
    return 3;
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
      alarm(1);
      g_clash_tests[idx].fn();
      alarm(0);
      g_in_test = 0;
      __gcov_dump();
      _exit(g_clash_cur_failed ? 100 : 102);
    }
    g_in_test = 0;
    __gcov_dump();
    _exit(g_clash_cur_failed ? 100 : 101);
  }
  {
    int status = 0;
    pid_t waited;
    do {
      waited = waitpid(pid, &status, 0);
    } while (waited < 0 && errno == EINTR);
    if (waited != pid) {
      perror("test waitpid");
      return 3;
    }
    if (WIFEXITED(status)) {
      int rc = WEXITSTATUS(status);
      return rc == 102 ? 0 : (rc == 100 ? 1 : 2);
    }
    return 2;
  }
}

typedef struct clash_test_stats {
  int passed;
  int failed;
  int crashed;
  int total;
} clash_test_stats;

static clash_test_stats run_shard(int shard_index, int shard_count) {
  clash_test_stats stats = {0, 0, 0, 0};
  int i;

  for (i = shard_index; i < g_clash_test_count; i += shard_count) {
    if (g_test_filter != NULL &&
        strstr(g_clash_tests[i].name, g_test_filter) == NULL) {
      continue;
    }
    int result = run_one(i);
    ++stats.total;
    if (result == 0) {
      ++stats.passed;
    } else if (result == 1) {
      ++stats.failed;
      fprintf(stderr, "FAIL  %s\n", g_clash_tests[i].name);
    } else if (result == 3) {
      ++stats.failed;
      fprintf(stderr, "ERROR %s: test isolation failed\n", g_clash_tests[i].name);
    } else {
      ++stats.crashed;
      fprintf(stderr, "CRASH %s\n", g_clash_tests[i].name);
    }
  }
  return stats;
}

static void add_stats(clash_test_stats *total, const clash_test_stats *part) {
  total->passed += part->passed;
  total->failed += part->failed;
  total->crashed += part->crashed;
  total->total += part->total;
}

int main(int argc, char **argv) {
  enum { worker_count = 16 };
  int result_pipes[worker_count][2];
  pid_t workers[worker_count];
  clash_test_stats total = {0, 0, 0, 0};
  int worker;
  int strict_crashes = 0;
  int selected_count = 0;

  for (int arg = 1; arg < argc; ++arg) {
    if (strcmp(argv[arg], "--strict-crashes") == 0) {
      strict_crashes = 1;
    } else if (strcmp(argv[arg], "--filter") == 0 &&
               g_test_filter == NULL && arg + 1 < argc &&
               argv[arg + 1][0] != '\0' && argv[arg + 1][0] != '-') {
      g_test_filter = argv[++arg];
    } else if (strcmp(argv[arg], "--help") == 0 && argc == 2) {
      printf("Usage: %s [--strict-crashes] [--filter SUBSTRING]\n", argv[0]);
      return 0;
    } else {
      fprintf(stderr, "Invalid argument: %s\n", argv[arg]);
      fprintf(stderr, "Usage: %s [--strict-crashes] [--filter SUBSTRING]\n", argv[0]);
      return 2;
    }
  }
  for (int i = 0; i < g_clash_test_count; ++i) {
    if (g_test_filter == NULL ||
        strstr(g_clash_tests[i].name, g_test_filter) != NULL) {
      ++selected_count;
    }
  }
  if (selected_count == 0) {
    fprintf(stderr, "No tests selected%s%s\n",
            g_test_filter == NULL ? "" : " by filter: ",
            g_test_filter == NULL ? "" : g_test_filter);
    return 2;
  }

  for (worker = 0; worker < worker_count; ++worker) {
    workers[worker] = -1;
    result_pipes[worker][0] = -1;
    result_pipes[worker][1] = -1;
    if (pipe(result_pipes[worker]) != 0) {
      clash_test_stats part = run_shard(worker, worker_count);
      add_stats(&total, &part);
      continue;
    }
    workers[worker] = fork();
    if (workers[worker] < 0) {
      clash_test_stats part;
      close(result_pipes[worker][0]);
      close(result_pipes[worker][1]);
      result_pipes[worker][0] = -1;
      result_pipes[worker][1] = -1;
      part = run_shard(worker, worker_count);
      add_stats(&total, &part);
      continue;
    }
    if (workers[worker] == 0) {
      clash_test_stats part;
      ssize_t written;
      const char *shard_root = getenv("CLASH95_GCOV_SHARD_ROOT");
      char shard_prefix[1024];
      close(result_pipes[worker][0]);
      if (shard_root != NULL && shard_root[0] != '\0') {
        int length = snprintf(shard_prefix, sizeof(shard_prefix),
                              "%s/worker-%d", shard_root, worker);
        if (length <= 0 || (size_t)length >= sizeof(shard_prefix) ||
            (mkdir(shard_prefix, 0700) != 0 && errno != EEXIST) ||
            setenv("GCOV_PREFIX", shard_prefix, 1) != 0) {
          close(result_pipes[worker][1]);
          _exit(2);
        }
      }
      part = run_shard(worker, worker_count);
      written = write(result_pipes[worker][1], &part, sizeof(part));
      close(result_pipes[worker][1]);
      _exit(written == (ssize_t)sizeof(part) ? 0 : 2);
    }
    close(result_pipes[worker][1]);
    result_pipes[worker][1] = -1;
  }

  for (worker = 0; worker < worker_count; ++worker) {
    if (workers[worker] > 0) {
      clash_test_stats part;
      ssize_t received =
          read(result_pipes[worker][0], &part, sizeof(part));
      int status = 0;
      close(result_pipes[worker][0]);
      waitpid(workers[worker], &status, 0);
      if (received == (ssize_t)sizeof(part) && WIFEXITED(status) &&
          WEXITSTATUS(status) == 0) {
        add_stats(&total, &part);
      } else {
        ++total.failed;
      }
    }
  }

  fprintf(stderr, "\n== %d passed, %d failed, %d crashed, %d total ==\n",
          total.passed, total.failed, total.crashed, total.total);
  return total.failed || total.total != selected_count ||
                 (strict_crashes && total.crashed) ? 1 : 0;
}
