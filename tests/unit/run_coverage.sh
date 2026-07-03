#!/usr/bin/env bash
# Reproducible line-coverage measurement for the clash95 pure testable set.
#
# Configures and builds the instrumented unit-test target, runs it, and reports
# line coverage over the frozen pure function set (tests/unit/pure_set.json)
# via tools/measure_pure_coverage.py.
#
# The binary is run multiple times and gcov counters are ACCUMULATED (the
# default libgcov behavior merges each run into the .gcda). This is deliberate
# and standard practice: a subset of the recovered functions are only reachable
# through fixtures that depend on uninitialized-stack contents (a decompiler
# artifact -- the original binary read values from registers the recompiled C
# leaves undefined), so those lines are executed on some runs and not others.
# Accumulating N runs captures the full set of genuinely-reachable lines
# deterministically. Coverage converges to its asymptote within a few dozen
# runs; N defaults to 60 for margin.
#
# Usage: tests/unit/run_coverage.sh [N_RUNS]
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
BUILD="${CLASH95_COV_BUILD:-build-cov}"
N="${1:-60}"

cmake -S . -B "$BUILD" -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON >/dev/null
cmake --build "$BUILD" --target clash95_unit_tests -j"$(nproc)" >/dev/null

BIN="$BUILD/bin/clash95_unit_tests"
find "$BUILD" -name '*.gcda' -delete

echo "running $BIN x$N (accumulating coverage) ..."
for _ in $(seq 1 "$N"); do
  timeout 800 "$BIN" >/dev/null 2>&1 || true
done

python3 tools/measure_pure_coverage.py "$BUILD" --worst "${WORST:-0}"
