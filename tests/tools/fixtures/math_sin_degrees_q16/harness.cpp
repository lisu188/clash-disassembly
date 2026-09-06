#include "harness.hpp"

namespace {
void isolate_unrepaired_edge()
{
  int descriptors[2];
  require(pipe(descriptors) == 0, "child result pipe");
  const pid_t child = fork();
  require(child >= 0, "fork unrepaired edge probe");
  if (child == 0) {
    close(descriptors[0]);
    const rlimit core_limit = {0, 0};
    setrlimit(RLIMIT_CORE, &core_limit);
    alarm(2);
    int (*volatile reference)(int) = Reference_Math_SinDegreesQ16;
    const int result = reference(INT_MIN);
    const ssize_t written = write(descriptors[1], &result, sizeof(result));
    _exit(written == sizeof(result) ? 0 : 3);
  }
  close(descriptors[1]);
  int status = 0;
  require(waitpid(child, &status, 0) == child, "wait unrepaired edge probe");
  int result = 0;
  const ssize_t received = read(descriptors[0], &result, sizeof(result));
  close(descriptors[0]);
  if (WIFSIGNALED(status))
    std::printf("unrepaired_INT_MIN=signal:%d\n", WTERMSIG(status));
  else if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && received == sizeof(result))
    std::printf("unrepaired_INT_MIN=returned:%d\n", result);
  else
    std::printf("unrepaired_INT_MIN=exit:%d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}
}

int main()
{
  prepare_table();
  isolate_unrepaired_edge();
  sine_corpus([](int angle) {
    const int expected = x86_sine(angle);
    const int actual = Math_SinDegreesQ16(angle);
    require(actual == expected, "repaired sine differs from original x86 instructions");
    if (angle != INT_MIN)
      require(Reference_Math_SinDegreesQ16(angle) == actual, "defined original sine behavior changed");
    if (angle == INT_MIN)
      require(actual == 0, "INT_MIN must address immutable table[0]");
    unchanged();
    ++cases;
  });
  std::printf("repair_cases=%llu guarded_table_bytes=%zu x86_oracle=pass\n",
              static_cast<unsigned long long>(cases), kPage);
}
