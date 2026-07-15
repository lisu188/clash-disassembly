#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 2 ]]; then
  echo "usage: $0 <unit-test-executable> <build-directory>" >&2
  exit 2
fi

test_executable=$(realpath "$1")
build_directory=$(realpath "$2")
case "$build_directory" in
  */clash-disassembly/build/*) ;;
  *)
    echo "refusing unexpected coverage build directory: $build_directory" >&2
    exit 2
    ;;
esac

shard_root=$(mktemp -d /tmp/clash95-gcov.XXXXXX)
cleanup() {
  case "$shard_root" in
    /tmp/clash95-gcov.*) rm -rf -- "$shard_root" ;;
  esac
}
trap cleanup EXIT

relative_build=${build_directory#/}
IFS=/ read -r -a build_components <<< "$relative_build"
export GCOV_PREFIX_STRIP=${#build_components[@]}
export CLASH95_GCOV_SHARD_ROOT=$shard_root

set +e
"$test_executable"
test_status=$?
set -e

# The frozen metric needs only whether a line ran, not summed counters. Keep
# recovered-only worker profiles separate and let the manifest-backed reader
# union their gcov results; this avoids gcov-tool counter-merge bugs.
profile_root=$build_directory/coverage-shards
case "$profile_root" in
  "$build_directory"/*) rm -rf -- "$profile_root" ;;
  *) exit 2 ;;
esac
for worker in $(seq 0 15); do
  destination=$profile_root/worker-$worker/CMakeFiles
  mkdir -p "$destination"
  cp -a \
    "$shard_root/worker-$worker/CMakeFiles/clash95_recovered_coverage_objects.dir" \
    "$destination/"
done

exit "$test_status"
