import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
SUMMARY = re.compile(r"== (\d+) passed, (\d+) failed, (\d+) crashed, (\d+) total ==")
FIXTURE = r'''
#include "clash_test.h"
#include <unistd.h>

extern "C" void __gcov_dump(void) {}
extern "C" pid_t __real_fork(void);
extern "C" pid_t __wrap_fork(void) {
  if (getenv("RUNNER_FORCE_FORK_ERROR") != NULL) {
    errno = EAGAIN;
    return -1;
  }
  return __real_fork();
}

TEST(stable, first) { CHECK_EQ(2 + 2, 4); }
TEST(stable, second) { CHECK(1); }
TEST(assertion, failed) { CHECK(0); }
TEST(assertion, failed_then_signal) { CHECK(0); raise(SIGSEGV); }
TEST(hazard, signal) { raise(SIGSEGV); }
TEST(hazard, timeout) { for (;;) pause(); }
TEST(hazard, exit_zero) { _exit(0); }
TEST(hazard, exit_nonzero) { _exit(42); }
TEST(hazard, abort) { abort(); }
TEST(hazard, uncaught_signal) { raise(SIGTERM); }
'''


@unittest.skipUnless(sys.platform.startswith("linux"), "runner requires Linux process isolation")
class UnitRunnerTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        requested = os.environ.get("CLASH95_RUNNER_TEST_CXX")
        if requested:
            compiler = shutil.which(requested)
            if compiler is None:
                raise RuntimeError(f"Requested compiler is unavailable: {requested}")
            compilers = [compiler]
        else:
            compilers = [
                shutil.which("g++-13") or shutil.which("g++"),
                shutil.which("clang++-18") or shutil.which("clang++"),
            ]
            compilers = list(dict.fromkeys(c for c in compilers if c))
        if not compilers:
            raise unittest.SkipTest("a C++ compiler is required")
        cls.directory = tempfile.TemporaryDirectory(prefix="clash-runner-tests-")
        cls.addClassCleanup(cls.directory.cleanup)
        cls.root = Path(cls.directory.name)
        fixture = cls.root / "cases.cpp"
        fixture.write_text(FIXTURE, encoding="utf-8")
        cls.profiles = []
        for index, compiler in enumerate(compilers):
            for optimization in ("-O0", "-O2"):
                executable = cls.root / f"runner-{index}-{optimization[1:]}"
                command = [
                    compiler, "-std=gnu++20", optimization,
                    "-Wall", "-Wextra", "-Wpedantic", "-Werror",
                    "-fno-exceptions", "-fno-rtti", "-U_GNU_SOURCE",
                    "-I", str(ROOT / "tests/unit"),
                    str(ROOT / "tests/unit/test_runner.cpp"), str(fixture),
                    "-Wl,--wrap=fork", "-o", str(executable),
                ]
                built = subprocess.run(command, capture_output=True, text=True, timeout=30)
                if built.returncode:
                    raise RuntimeError(f"{' '.join(command)}\n{built.stdout}\n{built.stderr}")
                cls.profiles.append((compiler, optimization, executable))

    def run_case(self, arguments, expected_code, expected_stats=None, extra_env=None):
        for compiler, optimization, executable in self.profiles:
            with self.subTest(compiler=compiler, optimization=optimization, arguments=arguments):
                env = os.environ.copy()
                for key in ("CLASH95_GCOV_SHARD_ROOT", "GCOV_PREFIX", "GCOV_PREFIX_STRIP",
                            "RUNNER_FORCE_FORK_ERROR"):
                    env.pop(key, None)
                env.update(extra_env or {})
                result = subprocess.run(
                    [str(executable), *arguments], cwd=self.root, env=env,
                    capture_output=True, text=True, timeout=10,
                )
                self.assertEqual(result.returncode, expected_code, result.stdout + result.stderr)
                summary = SUMMARY.search(result.stderr)
                if expected_stats is not None:
                    self.assertIsNotNone(summary, result.stderr)
                    self.assertEqual(tuple(map(int, summary.groups())), expected_stats, result.stderr)
                else:
                    self.assertIsNone(summary, result.stderr)

    def test_default_run_preserves_assertion_failures(self):
        self.run_case([], 1, (2, 2, 6, 10))

    def test_exploratory_crashes_remain_nonfatal(self):
        self.run_case(["--filter", "hazard."], 0, (0, 0, 6, 6))

    def test_strict_crashes_fail(self):
        self.run_case(["--strict-crashes", "--filter", "hazard."], 1, (0, 0, 6, 6))

    def test_strict_success_and_filter_order(self):
        self.run_case(["--filter", "stable.", "--strict-crashes"], 0, (2, 0, 0, 2))

    def test_filter_is_a_literal_case_sensitive_substring(self):
        self.run_case(["--filter", "table.f"], 0, (1, 0, 0, 1))
        self.run_case(["--filter", "STABLE"], 2)
        self.run_case(["--filter", "stable.*"], 2)

    def test_assertion_before_signal_is_not_downgraded_to_crash(self):
        self.run_case(["--filter", "assertion.failed_then_signal"], 1, (0, 1, 0, 1))

    def test_early_success_exit_is_not_a_completed_test(self):
        self.run_case(["--filter", "hazard.exit_zero"], 0, (0, 0, 1, 1))
        self.run_case(["--strict-crashes", "--filter", "hazard.exit_zero"], 1, (0, 0, 1, 1))

    def test_unmatched_filter_fails_in_both_modes(self):
        self.run_case(["--filter", "missing-test"], 2)
        self.run_case(["--strict-crashes", "--filter", "missing-test"], 2)

    def test_invalid_arguments_do_not_execute_tests(self):
        for arguments in (["--unknown"], ["--filter"], ["--filter", ""],
                          ["--filter", "--strict-crashes"],
                          ["--filter", "stable", "--filter", "hazard"],
                          ["--help", "--strict-crashes"]):
            self.run_case(arguments, 2)

    def test_help_does_not_execute_tests(self):
        self.run_case(["--help"], 0)

    def test_shard_setup_failure_is_fatal_in_both_modes(self):
        env = {"CLASH95_GCOV_SHARD_ROOT": str(self.root / "missing-parent" / "shards")}
        self.run_case(["--filter", "stable."], 1, (0, 16, 0, 0), env)
        self.run_case(["--strict-crashes", "--filter", "stable."], 1, (0, 16, 0, 0), env)

    def test_fork_failure_does_not_execute_test_in_parent(self):
        env = {"RUNNER_FORCE_FORK_ERROR": "1"}
        self.run_case(["--filter", "hazard.signal"], 1, (0, 1, 0, 1), env)
        self.run_case(["--strict-crashes", "--filter", "hazard.signal"], 1, (0, 1, 0, 1), env)


if __name__ == "__main__":
    unittest.main()
