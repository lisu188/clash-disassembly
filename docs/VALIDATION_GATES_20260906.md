# Independent CI gates and strict runner contracts

## Scope and evidence

Track: Win95 reconstruction, validation support. Base: `41552c9`.
This batch changes the CI workflow and the isolated native test runner, not
recovered gameplay bodies, data layouts, warning/link/header baselines,
coverage thresholds, or campaign-route status.

The current mission-05 endpoint and next gameplay action remain those in
[STATUS.md](STATUS.md). No bridge continuation, arrival save, tactical exchange,
visual comparison, or campaign promotion is claimed by this batch.

## Independent CI gates

The native warning, linked-surface and asset-free CTest steps each require a
successful build and an uncancelled job. A failed warning or link guard no
longer suppresses the other checks. All remain required; there is no
`continue-on-error` and no baseline update. CTest retains the four explicit
asset-free gates and now fails if its selection contains no tests.

Python repository checks require checkout and Python setup. Loading the CLP
also requires the CLIPS installation. A failed header guard no longer hides
Markdown validation or whitespace checks. Generated inventory JSON is checked
in its generation step, not mixed into validation of checked-in JSON files.

Compiler, warning, link-surface and CTest logs are uploaded together. The
header-surface log has its own artifact. Uploads can run after failed checks;
expensive validation does not continue after cancellation. The scheduling
conditions follow the GitHub Actions
[status-check semantics](https://docs.github.com/en/actions/reference/workflows-and-actions/expressions#status-check-functions).

## Strict native correctness runs

The native runner accepts `--strict-crashes` and one `--filter SUBSTRING`.
The filter is literal and case-sensitive, not a glob or regular expression.
`--help` prints usage without executing tests. Unknown arguments, missing or
empty filter values, duplicate filters and selections matching no registered
tests return status 2 rather than producing a vacuous pass.

Use an isolated diagnostic build for filtered runs. For example, after building
the coverage target described in [BUILD_AND_TEST.md](BUILD_AND_TEST.md):

```sh
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy build/coverage/bin/clash95_unit_tests --help
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy build/coverage/bin/clash95_unit_tests --strict-crashes --filter cov05_building.nation_total_value
```

The example selects an existing registered case; this batch does not certify
that case or the recovered game as crash-free. A strict run succeeds only when
all selected tests finish without assertion failures, crashes or missing
results. Assertion and infrastructure failures remain fatal in both modes.
Without `--strict-crashes`, crashes remain reported but nonfatal, preserving
the exploratory coverage policy. The existing CTest coverage wrapper still
runs all registrations without a filter. Filtered runs are not a substitute
for the frozen 718-function coverage measurement or its persisted shards.

Two false-pass paths are repaired: a test calling `_exit(0)` is no longer
mistaken for a normal return, and an assertion failure followed by a caught
signal remains a failure instead of being downgraded to a tolerated crash.
A failed test-child fork is an infrastructure failure; it no longer executes
the test unsafely in its parent. Interrupted child waits are retried. These
corrections can change historical native counts; old counts are not a fresh
measurement of the changed runner.

## Asset-free regression and validation limits

[The workflow tests](../tests/tools/test_ci_workflow.py) lock prerequisites,
unchanged required thresholds and diagnostic retention. They execute the actual
pipeline commands against success/failure fixtures to check that `tee` cannot
hide a failed guard. They do not emulate the GitHub Actions service.

[The runner tests](../tests/tools/test_unit_runner.py) compile the actual runner
and its unmodified framework header with independent synthetic cases. Only the
gcov flush function is stubbed; fork failure is injected through the linker.
Cases cover normal completion, assertions, caught and uncaught signals,
timeouts, early exits, filter errors and infrastructure failure. GCC and Clang
are exercised at O0/O2 when available. The CI compiler matrix supplies an
explicit compiler, whose absence is an error rather than a skip.

```sh
python3 -m unittest discover -s tests/tools -p 'test_ci_workflow.py' -v
python3 -m unittest discover -s tests/tools -p 'test_unit_runner.py' -v
CLASH95_RUNNER_TEST_CXX=g++-13 python3 -m unittest discover -s tests/tools -p 'test_unit_runner.py' -v
CLASH95_RUNNER_TEST_CXX=clang++-18 python3 -m unittest discover -s tests/tools -p 'test_unit_runner.py' -v
git diff --check
```

Local focused validation on 2026-09-06: 21 tests passed, using GCC 14.2.0 and
Clang 17.0.0 at O0/O2 with warnings as errors. The local environment did not
provide GCC 13, Clang 18, a complete checkout or retail assets. This is not a
full native coverage, supported-compiler game-build or runtime result. Public
CI must supply its own fresh evidence; known baseline failures are not hidden.
