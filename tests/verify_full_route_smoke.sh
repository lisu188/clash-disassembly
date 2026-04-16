#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "bootstrap binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

smoke_root="${TMPDIR:-/tmp}/clash95-full-route-smoke-$$"
mkdir -p "$smoke_root"
log_path="$smoke_root/full-route.log"
trap 'rm -rf "$smoke_root"' EXIT

set +e
setsid env \
  SDL_VIDEODRIVER=dummy \
  SDL_AUDIODRIVER=dummy \
  "$bootstrap_bin" >"$log_path" 2>&1 &
pid=$!
set -e

sleep 2

if ! kill -0 "$pid" 2>/dev/null; then
  wait "$pid"
  status=$?
  echo "full-route smoke exited before external shutdown with status $status" >&2
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
  echo "full-route smoke left processes in the bootstrap process group" >&2
  pgrep -ag "$pid" >&2 || true
  exit 1
fi

if grep -q "Segmentation fault" "$log_path" || grep -q "Aborted" "$log_path"; then
  echo "full-route smoke reported a crash" >&2
  cat "$log_path" >&2
  exit 1
fi
