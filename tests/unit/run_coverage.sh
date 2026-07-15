#!/usr/bin/env bash
# Reproducible split-object coverage measurement for the frozen pure set.
# The CTest wrapper runs every independently compiled case in isolated workers
# and preserves their recovered-object profiles as merge-free shards.
#
# Usage: tests/unit/run_coverage.sh
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
BUILD="${CLASH95_COV_BUILD:-build-cov}"

if [ "$#" -ne 0 ]; then
  echo "run_coverage.sh no longer accepts a repeat count; one sharded run is deterministic" >&2
  exit 2
fi

cmake -S . -B "$BUILD" -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON >/dev/null
cmake --build "$BUILD" --target clash95_unit_tests -j"$(nproc)" >/dev/null

ctest --test-dir "$BUILD" -R '^clash95_unit_tests$' --output-on-failure
python3 tools/measure_pure_coverage.py "$BUILD" \
  --minimum "${MINIMUM_COVERAGE:-89.7}" \
  --require-functions 718 \
  --require-zero-uncovered \
  --worst "${WORST:-0}"
