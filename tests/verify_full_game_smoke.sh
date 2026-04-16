#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/executable" >&2
  exit 2
fi

exe="$1"
if [ ! -x "$exe" ]; then
  echo "executable is not runnable: $exe" >&2
  exit 2
fi

log_path="${TMPDIR:-/tmp}/clash95-full-game-smoke-$$.log"
trap 'rm -f "$log_path"' EXIT

set +e
timeout -s KILL 2s "$exe" >"$log_path" 2>&1
status=$?
set -e

if [ "$status" -ne 137 ]; then
  echo "full-game smoke exited with unexpected status $status" >&2
  cat "$log_path" >&2
  exit 1
fi
if grep -q "dumped core" "$log_path"; then
  echo "full-game smoke reported a core dump" >&2
  cat "$log_path" >&2
  exit 1
fi
