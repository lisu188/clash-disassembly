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

smoke_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-r-command-shutdown.XXXXXX")"
log_path="$smoke_root/r-command.log"
trap 'rm -rf "$smoke_root"' EXIT

set +e
env \
  SDL_VIDEODRIVER=dummy \
  SDL_AUDIODRIVER=dummy \
  timeout 5s "$bootstrap_bin" r >"$log_path" 2>&1
status=$?
set -e

if [ "$status" -eq 124 ]; then
  echo "r-command shutdown smoke did not exit before timeout" >&2
  cat "$log_path" >&2 || true
  exit 1
fi

if [ "$status" -ne 0 ]; then
  echo "r-command shutdown smoke exited with status $status" >&2
  cat "$log_path" >&2 || true
  exit 1
fi

if grep -q "Segmentation fault" "$log_path" || grep -q "Aborted" "$log_path"; then
  echo "r-command shutdown smoke reported a crash" >&2
  cat "$log_path" >&2
  exit 1
fi
