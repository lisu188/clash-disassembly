# Unit Testing & Coverage

This project has an opt-in unit-test and line-coverage harness for the recovered
pure functions in `clash95.c`. It is separate from the route-smoke integration
tests (which drive the real SDL executable) and is disabled by default so
ordinary builds and `ctest` runs are unaffected.

## What is covered

Coverage is measured over a **frozen "pure testable" set** of functions in
`clash95.c` — those whose bodies reference no global/`gameData` state, call no
impure/IO/render/alloc/platform helper, and perform no indirect/vtable dispatch.
This set is generated deterministically by `tools/pure_function_set.py` and
frozen in `tests/unit/pure_set.json` (the coverage denominator). The other
~2,750 functions are bound to `gameData`, DirectDraw/DirectSound, the CLIPS
engine, save files, or CD assets, and are exercised by the route-smoke
integration tests instead — covering them in isolated unit tests is not the goal
here.

## How it works

Because ~300 of the recovered functions are `static` (internal linkage), the
tests cannot link against them from a separate translation unit. Instead,
`tests/unit/test_all.c` is a single aggregator TU that `#include`s `clash95.c`
directly, making every recovered function — static or external — callable by
name **without modifying the recovered source**. Each `tests/unit/cases/*.c`
file is `#include`d into that TU (not compiled separately) and contributes
`TEST(...)` cases.

### Fault isolation

Decompiled code is hostile to unit testing: a test may segfault on a bad
pointer, call `exit()`/`abort()` (e.g. `App_RequestQuit`), or spin forever in a
`GetMessageA`-style modal loop. So the runner executes **each test in its own
forked child process** with:

- signal handlers (`SIGSEGV`/`SIGBUS`/`SIGFPE`/`SIGABRT`) that recover via
  `siglongjmp`,
- an `alarm(8)` watchdog for infinite loops,
- an explicit `__gcov_dump()` before the child exits, so libgcov merges each
  child's counters into the shared `.gcda` regardless of how the test ended.

A crashing, exiting, or hanging test therefore never truncates the run or loses
the coverage accumulated by other tests.

### Link stubs

The coverage target does not link `bootstrap_main.c` or Win32/CRT import
libraries. `test_all.c` provides benign stubs for the handful of symbols the
game build resolves elsewhere (`_no_support_loaded`, `g_RenderHook`,
`GetTimeZoneInformation`, thread/CRT helpers, `CreateThread`, `LoadLibraryA`,
etc.) so that gc-sections-kept recovered code links and those functions become
testable.

## Building and running

```sh
cmake -S . -B build-cov -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON
cmake --build build-cov --target clash95_unit_tests -j4
./build-cov/bin/clash95_unit_tests          # runs all tests (fork-isolated)
python3 tools/measure_pure_coverage.py build-cov --worst 40
```

`measure_pure_coverage.py` runs `gcov` on the coverage TU and reports line
coverage restricted to the pure-set line ranges, plus the least-covered
functions. The unit tests are also registered as the `clash95_unit_tests` CTest
test (label `unit`) when `CLASH95_COVERAGE=ON`.

## Tooling

- `tools/pure_function_set.py` — regenerate the pure testable set (denominator).
- `tools/gen_pure_decls.py` — extern prototypes for the pure set (reference).
- `tools/wire_cov_cases.py` — regenerate the `#include` block of case files in
  `test_all.c` (run after adding a `tests/unit/cases/test_*.c` file).
- `tools/measure_pure_coverage.py` — measure coverage over the pure set.

## Adding tests

1. Add a `tests/unit/cases/test_<name>.c` file containing `TEST(suite, name)`
   blocks. No `#include`s, no `main`; use a unique `suite` prefix.
2. Run `python3 tools/wire_cov_cases.py`, rebuild, run, and re-measure.

Back every pointer argument with a **`static`** buffer: this is a 64-bit
`-no-pie` build of code that models pointers as 32-bit `int`/`_DWORD`, so a
stack address truncates to garbage when the recovered code round-trips it
through `(int)`. For rules-engine functions, call `Mem_InitReserveBlock(0, 0)`
and `Rules_InitAtomTables()` first to initialize the global arenas.

## Current coverage

Line coverage of the 718-function pure testable set (6636 executable lines),
measured by `tools/measure_pure_coverage.py`:

- **Cumulative: ~90% (best observed 5972/6636 = 89.99%)** via
  `tests/unit/run_coverage.sh` (accumulates gcov counters across runs).
- Single-run deterministic floor: ~89.7%.

The gap between the single-run and cumulative figures, and the ~10% that stays
uncovered, are both consequences of the source being **decompiler output**:

- A subset of recovered functions read values the original binary held in CPU
  registers that the recompiled C leaves **uninitialized** — the decompiler
  flags these itself with `// variable 'vN' is possibly undefined` trailer
  comments. Reaching the code past such a read requires a fixture that lands a
  specific value in an uninitialized stack slot, which depends on the exact
  stack layout of a given run. Those lines are therefore covered on some runs
  and not others; accumulating runs (`run_coverage.sh`) captures the full
  reachable set, which is why cumulative > single-run.
- The remaining uncovered lines are **genuinely unreachable in the recompiled
  build**: the same undefined-register reads that always crash (e.g.
  `Lexer_ParseValueList` dereferences an undefined `v7`; `Rules_GetTypeNameToken\
Code` reads ten undefined locals the decompiler split from one register), plus
  a handful of real 32-bit-vs-64-bit pointer-stride/truncation bugs the
  decompiler baked in. These were confirmed unreachable by gdb across many
  independent analyses; no test input can execute them. They form a hard
  decompiler-artifact ceiling at ~90% of *all* executable lines. Coverage of the
  *reachable* subset (excluding these provably-dead lines) is well above 90%.

Regenerate with `tests/unit/run_coverage.sh` (add `WORST=40` to list the least-
covered functions).
