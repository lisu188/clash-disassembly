#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "main-menu exit probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

for tool in Xvfb xdotool timeout grep head tail find sort python3; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "main-menu exit probe skipped; missing $tool" >&2
    exit 77
  fi
done

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
probe_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-main-menu-exit.XXXXXX")"
log_path="$probe_root/main-menu-exit.log"
frame_prefix="$probe_root/frame"
pid=""
xvfb_pid=""
preserve_artifacts=0
: >"$log_path"

fail_probe() {
  local message="$1"

  echo "$message" >&2
  tail -n "${CLASH95_MAIN_MENU_EXIT_FAIL_TAIL_LINES:-240}" "$log_path" >&2 || true
  preserve_artifacts=1
  exit 1
}

cleanup() {
  if [ -n "${pid:-}" ]; then
    kill -TERM "-$pid" 2>/dev/null || true
    kill -KILL "-$pid" 2>/dev/null || true
  fi
  if [ -n "${xvfb_pid:-}" ]; then
    kill "$xvfb_pid" 2>/dev/null || true
  fi
  if [ "${CLASH95_KEEP_SMOKE_ARTIFACTS:-0}" = "1" ] || [ "$preserve_artifacts" = "1" ]; then
    echo "main-menu exit probe artifacts: $probe_root" >&2
  else
    rm -rf "$probe_root"
  fi
}
trap cleanup EXIT

wait_for_log() {
  local pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_seconds="$SECONDS"

  echo "[probe] wait-for-log: ${label}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$pattern" "$log_path"; then
      echo "[probe] wait-for-log-done: ${label}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "main-menu exit probe process exited while waiting for ${label}: $pattern"
    fi
    sleep 0.1
  done
  fail_probe "main-menu exit probe timed out waiting for ${label}: $pattern"
}

latest_modified_frame() {
  find "$probe_root" -maxdepth 1 -type f -name 'frame-*.bmp' -printf '%T@ %p\n' \
    | sort -n \
    | tail -n 1 \
    | sed 's/^[^ ]* //'
}

check_latest_frame_nonblank() {
  local latest_frame

  latest_frame="$(latest_modified_frame)"
  if [ -z "$latest_frame" ] || [ ! -f "$latest_frame" ]; then
    fail_probe "main-menu exit probe did not capture any frames"
  fi
  echo "[probe] nonblank-check main-menu: ${latest_frame}" >>"$log_path"
  python3 "$repo_root/tests/frame_metrics.py" \
    "$latest_frame" \
    --min-mean "${CLASH95_MAIN_MENU_EXIT_MIN_FRAME_MEAN:-1}" \
    --min-nonblack "${CLASH95_MAIN_MENU_EXIT_MIN_NONBLACK_PIXELS:-1000}" \
    --min-colors "${CLASH95_MAIN_MENU_EXIT_MIN_COLORS:-8}" \
    --quiet >>"$log_path" 2>&1 \
    || fail_probe "main-menu exit probe captured a blank/low-detail frame: ${latest_frame}"
}

display_number="${CLASH95_XVFB_DISPLAY_NUMBER:-$((190 + RANDOM % 800))}"
Xvfb ":$display_number" -screen 0 "${CLASH95_XVFB_SCREEN:-800x600x24}" >"$probe_root/xvfb.log" 2>&1 &
xvfb_pid=$!
sleep 1
if ! kill -0 "$xvfb_pid" 2>/dev/null; then
  cat "$probe_root/xvfb.log" >&2 || true
  exit 77
fi
export DISPLAY=":$display_number"
echo "[probe] using DISPLAY=$DISPLAY" >>"$log_path"

setsid timeout "${CLASH95_MAIN_MENU_EXIT_TIMEOUT_SECONDS:-30}s" env \
  SDL_AUDIODRIVER=dummy \
  CLASH95_SKIP_BOOT_AVI=1 \
  CLASH95_TRACE_WORLD_CLICK=1 \
  CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
  CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-0}" \
  CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-32}" \
  "$bootstrap_bin" >>"$log_path" 2>&1 &
pid=$!
echo "[probe] launched bootstrap pid=$pid" >>"$log_path"

sleep "${CLASH95_MAIN_MENU_EXIT_INITIAL_WAIT:-2}"
window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
if [ -z "$window" ]; then
  fail_probe "main-menu exit probe could not find the SDL window"
fi
echo "[probe] found window: $window" >>"$log_path"

wait_for_log "${CLASH95_MAIN_MENU_EXIT_MENU_PATTERN:-[pcx] load path=gfx\\menu\\main.gfx}" "main menu load" 20
sleep "${CLASH95_MAIN_MENU_EXIT_SETTLE_WAIT:-0.3}"
check_latest_frame_nonblank

echo "[probe] exit: click at ${CLASH95_CLICK_MAIN_MENU_EXIT_X:-245},${CLASH95_CLICK_MAIN_MENU_EXIT_Y:-226}" >>"$log_path"
xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
xdotool mousemove --window "$window" "${CLASH95_CLICK_MAIN_MENU_EXIT_X:-245}" "${CLASH95_CLICK_MAIN_MENU_EXIT_Y:-226}"
sleep 0.08
xdotool mousedown 1
sleep "${CLASH95_CLICK_MAIN_MENU_EXIT_HOLD:-0.22}"
xdotool mouseup 1

start_seconds="$SECONDS"
while [ $((SECONDS - start_seconds)) -lt "${CLASH95_MAIN_MENU_EXIT_WAIT_SECONDS:-8}" ]; do
  if ! kill -0 "$pid" 2>/dev/null; then
    wait "$pid" 2>/dev/null || true
    pid=""
    exit 0
  fi
  sleep 0.1
done

fail_probe "main-menu exit probe process did not exit after clicking Exit"
