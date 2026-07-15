# Unit Testing and Coverage

The opt-in unit-test harness exercises recovered pure functions from the GNU
C17 split build. It is separate from the SDL route-smoke tests and remains
disabled in ordinary builds unless `CLASH95_COVERAGE=ON` is selected.

## Coverage denominator

Coverage is measured over the frozen set of 718 pure testable functions in
`tests/unit/pure_set.json`. The set excludes functions whose bodies depend on
game state, I/O, rendering, allocation, platform services, or indirect/vtable
dispatch. Those paths belong to the executable route tests rather than the
isolated unit harness.

The recovered implementation is no longer included into a test aggregator.
Coverage identities are resolved through `data/recovered_sources.json`, so a
frozen function follows its manifest entry into its canonical source file.
This preserves the 718-function denominator after the source split without
depending on removed unified-source line ranges.

## Build and test layout

With coverage enabled, CMake creates
`clash95_recovered_coverage_objects` from all 138 recovered split translation
units. Recovered code and the test/support code are compiled separately as GNU
C17:

- every test source under `tests/unit/cases/` is an independent translation unit;
- `tests/unit/case_prelude.h` provides the common case declarations;
- `tests/unit/test_runner.c` owns registration, sharding, and process
  isolation;
- `tests/unit/test_compat_stubs.c` owns the test-only compatibility symbols;
- platform, instrumentation, and compatibility support are linked as their own
  sources.

Test and support code must pass `-Wall -Wextra -Wpedantic -Werror`. The
recovered coverage objects use the recovered-code warning profile and make
implicit declarations, implicit `int`, and missing returns fatal.
Thirty frozen pure helpers that are local in production are declared and
exported only under `CLASH95_TESTING`; the remaining production-local helpers
stay inaccessible to the harness.

There is no aggregate recovered implementation source, no direct inclusion of
implementation `.c` files, and no case-file inclusion chain in the current
harness.

## Fault isolation and coverage shards

Decompiler output can dereference an invalid reconstructed pointer, call a
hard-exit path, or enter a message-style loop. The runner therefore distributes
the registered cases across 16 worker processes and runs every case in a
further fork-isolated child. Each child has a one-second alarm and handlers for
the expected fatal signals. An explicit test assertion failure is reported as
`FAIL`; an arbitrary exit, signal, or timeout is reported as `CRASH`. Crash
classification keeps hostile coverage probes from terminating the suite, but
does not turn a failed assertion into a pass.

`tests/unit/run_split_coverage.sh` gives each worker a private gcov prefix under
`/tmp`, then copies only the recovered-object profiles to
`<build>/coverage-shards/worker-0..15`. The manifest-backed coverage reader runs
gcov over those profiles and unions line execution across workers. Keeping the
profiles separate avoids unreliable `gcov-tool` merges while retaining the
only metric needed here: whether each frozen executable line ran.

## Building and running

From Linux or WSL:

```sh
cmake -S . -B build/coverage -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON
cmake --build build/coverage --target clash95_unit_tests -j"$(nproc)"
ctest --test-dir build/coverage -R '^clash95_unit_tests$' --output-on-failure
python3 tools/measure_pure_coverage.py build/coverage \
  --minimum 89.7 --require-functions 718 --require-zero-uncovered --worst 40
```

The CTest entry invokes `tests/unit/run_split_coverage.sh`, which prepares the
worker profiles consumed by `tools/measure_pure_coverage.py`. Running the test
executable directly remains useful for case diagnostics, but does not create
the persisted shard layout expected by the measurement command.

## Adding tests

1. Add a test source under `tests/unit/cases/` containing `TEST(suite, name)`
   blocks.
   Do not add `main` or include another `.c` file.
2. Reconfigure or rebuild. The CMake `CONFIGURE_DEPENDS` glob discovers the new
   case and compiles it independently.
3. Run the CTest entry and re-measure coverage.

Back pointer arguments with static storage where the recovered ABI stores a
pointer in a 32-bit integer field. A stack address can truncate when it passes
through that representation on the 64-bit host. For rules-engine functions,
initialize the required recovered arenas and atom tables before calling into
them. Do not initialize a decompiler-lost local merely to make a test reach a
branch; recover it from binary evidence or treat the branch as an unresolved
artifact.

## Current result

The latest split-profile measurement covers **5963 of 6636 executable lines
(89.86%)** across all **718 frozen functions**. No frozen function is
zero-covered.

The remaining gap is concentrated in decompiler artifacts such as values that
the original binary held in registers but the recovered C leaves undefined,
and in reconstructed 32-bit pointer layouts on the 64-bit host. Tests may use
`TOUCH(...)` to exercise an evidence-backed call without asserting a value that
depends on such a lost local. Coverage is not justification for guessing an
initializer or changing recovered behavior.

## Related tools and data

- `tests/unit/pure_set.json`: frozen 718-function denominator.
- `tools/pure_function_set.py`: pure-set analysis and metadata validation.
- `tools/coverage_source_manifest.py`: manifest-backed source and gcov mapping.
- `tools/measure_pure_coverage.py`: frozen-set coverage report.
- `data/recovered_sources.json`: authoritative canonical and historical
  function identity.
- `docs/SOURCE_SPLIT.md`: source-layout, build, cutover evidence, and remaining
  validation debt.
