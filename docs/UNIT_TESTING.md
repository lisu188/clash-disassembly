# Unit Testing and Coverage

The opt-in unit-test harness exercises recovered pure functions from the GNU++20
split build. It is separate from the SDL route-smoke tests and remains
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
`clash95_recovered_coverage_objects` from all 140 recovered split translation
units. Recovered code and the test/support code are compiled separately as GNU++20:

- every test source under `tests/unit/cases/` is an independent translation unit;
- `tests/unit/case_prelude.h` provides the common case declarations;
- `tests/unit/test_runner.cpp` owns registration, sharding, and process
  isolation;
- `tests/unit/test_compat_stubs.cpp` owns the test-only compatibility symbols;
- platform, instrumentation, and compatibility support are linked as their own
  sources.

Test and support code must pass `-Wall -Wextra -Wpedantic -Werror`. The
recovered coverage objects use the recovered-code warning profile and make
undeclared calls and missing returns fatal.
Thirty frozen pure helpers that are local in production are declared and
exported only under `CLASH95_TESTING`; the remaining production-local helpers
stay inaccessible to the harness.

There is no aggregate recovered implementation source, no direct inclusion of
implementation `.cpp` files, and no case-file inclusion chain in the current
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
CXX=g++-13 cmake -S . -B build/coverage -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON
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

1. Add a `.cpp` test source under `tests/unit/cases/` containing `TEST(suite, name)`
   blocks.
   Do not add `main` or include another implementation file.
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

The builder-Road batch preserves all 1589 registrations and the same 530 crash
identities: **1059 passed, zero assertion failures, 530 isolated crashes**. The
fresh final coverage build uses dummy SDL and retains stable source/binary hashes.
Coverage is **6167/6662 (92.57%)**, all **718** frozen functions covered; two fewer
lines are covered than the prior batch, both in the unchanged RNG-dependent
branch of `Building_UpdatePlagueState`. The independent review records this
without inferring a cause or reseeding the denominator. The added asset-free selector/table
regression passes 672 original-measured cases across GCC/Clang O0/O2, and all
107 tooling tests pass. Exact native attempts, commands and comparison:
`artifacts/runtime-recovery/builder-road-menu-20260906/native-review/`.

The subsequent manual-crossing repair retains exactly the same 1589 native
registrations and crash identities: **1059 passed, zero assertion failures,
530 isolated crashes**. Coverage remains 6169/6662 (92.60%) across all 718
functions with none uncovered. A fresh GCC 13 GNU++20 coverage build and the
canonical dummy-SDL wrapper supply this result; it is not a crash-free gate.
Exact commands and independent before/after comparison:
`artifacts/runtime-recovery/manual-crossing-20260906/native-review/`.

The 2026-09-06 nation-score recovery, with explicit headless SDL drivers,
covers **6169 of 6662 executable lines (92.60%)**, all **718 frozen functions**,
none uncovered. The native harness reports **1059 passed, zero assertion
failures, 530 isolated crashes, 1589 total**. All 1588 prior registrations
remain; the new `cov05_building.nation_total_value` case checks 24 score calls
and two helper calls against original instruction results, with unchanged
game-memory assertions. The permanent tooling regression checks 308 original
goldens in four compiler/optimization profiles; all 105 tooling tests pass.

The first native run used ambient SDL settings and reported 1053 passed,
zero assertion failures and 536 crashes, with 6161/6662 lines covered. Its
logs and all coverage shards remain in
`artifacts/runtime-recovery/nation-score-20260906/native-initial/`. Six extra
UI/event cases return in both binaries under isolated dummy-SDL debugger calls
and do not crash in the controlled headless repeat. Those observations do not
establish their original signal or exact cause. The native wrapper now defaults
video/audio to dummy drivers; explicit overrides must also remain headless.

The remaining additional crash versus the reveal baseline is the previously
documented file-output defect: its filename buffer moves from `0x3449b00` to
`0x3569380`, narrowing from null to invalid `0xffffff80` before `strlen`.
Paired debugger calls reproduce this and do not enter the score function.
No favorable address is restored and no assertion or baseline is weakened.

The score fix retains packed-load alignment debt and signed-overflow limits.
Actual original code validates 1020 bounded cases in eight profiles; alignment
is explicitly excluded from the sanitizer checks. Separate overflow cases
demonstrate original wrapping and current C++ traps. No full-range portability
claim follows from the measured agreement. Exact commands, original bytes,
live inputs, tests, both native runs and triage:
`artifacts/runtime-recovery/nation-score-20260906/`.

The preceding 2026-09-06 reveal-propagation recovery covers **6171 of 6662 executable
lines (92.63%)**, all **718 frozen functions**, none uncovered. All **1588**
native registrations remain: **1059 passed, zero assertion failures, 529
isolated crashes**. The existing radius-two case now also checks propagation
in every direction and player slice through the actual minimap and visibility
helpers. Its earlier radius-two coverage call remains. The permanent tooling
test checks 2034 cases per GCC/Clang O0/O2 profile with undefined-behavior traps,
including independent closure checks and measured original callback order.

No case gains crash status. The one file-output case that faulted in the fog
build survives again because its new buffer address truncates to null; two
debugger calls confirm the same incorrect empty-name include. This is an
existing address-sensitive recovery defect, not a file-output repair. The
reveal function is not reached. Exact source/test hashes, crash identities,
commands and evidence are in `artifacts/runtime-recovery/reveal-20260906/`.
No test identity or baseline was removed or weakened.

The preceding 2026-09-06 fog-classifier recovery covers **6169 of 6662 executable lines
(92.60%)**, all **718 frozen functions**, none uncovered. All **1588** native
registrations remain: **1058 passed, zero assertion failures, 530 isolated
crashes**. The existing fog case now asserts every mask, all six player slices,
player isolation and style effects through the actual visibility helper. The
asset-free regression additionally checks call order and clipped map edges on
GCC/Clang O0/O2 with undefined-behavior traps, using a measured original table.

Compared with the preceding radix run, only
`cov4_07_ccfo.a10_nonzero_open_success` gains crash status. Paired debugger
calls identify retained filename-pointer-to-char truncation in
`Rules_OpenConstructCodeFile`: the previous address truncated to null and was
handled as an empty string, while the new address becomes invalid and faults
in strlen. This is a concrete address-sensitive recovery defect, not evidence
of repaired file output. The classifier is not reached on that path. Exact
unit identities, crash differences, coverage logs and debugger evidence live
under `artifacts/runtime-recovery/fog-20260906/`. No test or baseline was weakened.

The preceding 2026-09-06 radix-formatter recovery covers **6163 of 6663 executable lines
(92.50%)** over all **718 frozen functions**, with none zero-covered. The
native suite retains all 1,588 cases and reports **1059 passed, zero assertion
failures, and 529 isolated crashes**. The existing formatter case now checks
exact strings, termination, guards and returned destination pointers. Its
supporting asset-free tool regression runs 10,220 inputs in eight compiler,
optimization and undefined-behavior-check profiles without retail data.

Against the fresh pre-repair C++ run (1056/0/532), no cases gain crash status;
the cold/warm thread, nonzero padded-hex and one file-open case lose it. Exact
names and results are retained in
artifacts/runtime-recovery/radix-20260906/unit-comparison.json and the unit and
coverage logs in that directory. Original PE instruction execution independently
proves the repaired formatter contract. This does not establish that other
thread, file or CRT paths are correct. No test identity or assertion was removed.

The preceding 2026-09-05 GNU++20 migration measurement covers **6157 of 6661
executable lines (92.43%)** across all **718 frozen functions**, with none
zero-covered. The frozen function set and 89.7% CI floor are unchanged.
All 62 native harness/case translation units now compile as C++, retaining
all 1,588 registrations and the assertion, isolation, and reporting behavior.
The run reports 1056 passed, zero assertion failures, and 532 isolated crashes.
CTest success does not mean zero crashes.

Against the frozen C run, `cov2_02_crtthread.begin_thread_cold_and_warm` gains
crash status and `cov5_02_crtbeginthread.normal_call_exercises_reachable_lines`
loses it. Matched C/C++ harnesses using identical recovered objects also have
an exact 1057/0/531 repeat. Debugger evidence with ASLR enabled finds the same
existing `Str_FormatUnsignedRadixDigits` scratch-buffer corruption in both
harnesses. Intermittent thread-test success is not evidence of a CRT repair.

Full output, crash comparisons, compiler commands, and fresh-shard coverage
are retained under `artifacts/cpp-migration/20260905-a/`: `final2-unit-details.log`,
artifacts/cpp-migration/20260905-a/final2-unit-comparison.json,
`final2-coverage.log`, and `unit-candidates/`.
Earlier tactical-slot and migration-stage measurements remain historical
evidence. See [STATUS.md](STATUS.md) and [CPP_MIGRATION.md](CPP_MIGRATION.md)
for the final migration scope and remaining readiness limits.

The remaining gap is concentrated in decompiler artifacts such as values that
the original binary held in registers but the recovered C leaves undefined,
and in reconstructed 32-bit pointer layouts on the 64-bit host. Tests may use
`TOUCH(...)` to exercise an evidence-backed call without asserting a value that
depends on such a lost local. Coverage is not justification for guessing an
initializer or changing recovered behavior.

## Related tools and data

- `tests/unit/pure_set.json`: frozen 718-function denominator. Its
  `original_source`/`original_line` fields intentionally keep pre-cutover
  (unified-era) paths — they are the frozen identity keys that
  `tools/migrate_pure_coverage_metadata.py --check` resolves through the
  manifest; do not "fix" them to canonical paths.
- `tools/pure_function_set.py`: pure-set analysis and metadata validation.
- `tools/coverage_source_manifest.py`: manifest-backed source and gcov mapping.
- `tools/measure_pure_coverage.py`: frozen-set coverage report.
- `data/recovered_sources.json`: authoritative canonical and historical
  function identity.
- `docs/SOURCE_SPLIT.md`: source-layout, build, cutover evidence, and remaining
  validation debt.
