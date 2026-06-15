#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap-or-clash95_cpp_regen" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "direct-a0 smoke binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

smoke_root="${TMPDIR:-/tmp}/clash95-direct-a0-smoke-$$"
mkdir -p "$smoke_root"
log_path="$smoke_root/direct-a0.log"
trap 'rm -rf "$smoke_root"' EXIT

set +e
setsid env \
  SDL_VIDEODRIVER=dummy \
  SDL_AUDIODRIVER=dummy \
  "$bootstrap_bin" /A0 >"$log_path" 2>&1 &
pid=$!
set -e

sleep "${CLASH95_DIRECT_A0_SMOKE_LIVENESS_SECONDS:-0.75}"

if ! kill -0 "$pid" 2>/dev/null; then
  set +e
  wait "$pid"
  status=$?
  set -e
  echo "direct-a0 smoke exited before external shutdown with status $status" >&2
  cat "$log_path" >&2 || true
  exit 1
fi

kill -TERM "-$pid" 2>/dev/null || true
sleep 1
if kill -0 "$pid" 2>/dev/null; then
  kill -KILL "-$pid" 2>/dev/null || true
fi
wait "$pid" 2>/dev/null || true

if pgrep -g "$pid" >/dev/null 2>&1; then
  echo "direct-a0 smoke left processes in the bootstrap process group" >&2
  pgrep -ag "$pid" >&2 || true
  exit 1
fi

if grep -q "Segmentation fault" "$log_path" || grep -q "Aborted" "$log_path"; then
  echo "direct-a0 smoke reported a crash" >&2
  cat "$log_path" >&2
  exit 1
fi
