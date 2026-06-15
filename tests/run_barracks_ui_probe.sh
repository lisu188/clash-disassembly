#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "barracks UI probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

for tool in Xvfb xdotool timeout grep head tail awk wc; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "barracks UI probe skipped; missing $tool" >&2
    exit 77
  fi
done
if [ "${CLASH95_BARRACKS_UI_GDB:-0}" = "1" ] && ! command -v gdb >/dev/null 2>&1; then
  echo "barracks UI probe skipped; missing gdb" >&2
  exit 77
fi

probe_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-barracks-ui.XXXXXX")"
log_path="$probe_root/barracks-ui.log"
frame_prefix="$probe_root/frame"
pid=""
xvfb_pid=""

fail_probe() {
  local message="$1"

  echo "$message" >&2
  tail -n "${CLASH95_BARRACKS_UI_FAIL_TAIL_LINES:-400}" "$log_path" >&2 || true
  echo "barracks UI probe artifacts: $probe_root" >&2
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
  echo "barracks UI probe artifacts: $probe_root" >&2
}
trap cleanup EXIT

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

run_command=("$bootstrap_bin")
if [ "${CLASH95_BARRACKS_UI_GDB:-0}" = "1" ]; then
  run_command=(
    gdb -q -batch
    -ex run
    -ex "thread apply all bt"
    -ex quit
    --args "$bootstrap_bin"
  )
fi

set +e
setsid timeout "${CLASH95_BARRACKS_UI_TIMEOUT_SECONDS:-90}s" env \
  SDL_AUDIODRIVER=dummy \
  CLASH95_SKIP_BOOT_AVI=1 \
  CLASH95_TRACE_WORLD_CLICK=1 \
  CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
  CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-0}" \
  CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-260}" \
  CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_DETAIL="${CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_DETAIL:-1}" \
  "${run_command[@]}" >>"$log_path" 2>&1 &
pid=$!
set -e
echo "[probe] launched bootstrap pid=$pid" >>"$log_path"

click_at() {
  local window="$1"
  local x="$2"
  local y="$3"
  local hold="${4:-0.18}"
  local gap="${5:-0.55}"
  local label="${6:-click}"
  local button="${7:-1}"

  echo "[probe] ${label}: button ${button} at ${x},${y}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep 0.08
  xdotool mousedown "$button"
  sleep "$hold"
  xdotool mouseup "$button"
  sleep "$gap"
}

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
      fail_probe "barracks UI probe process exited while waiting for ${label}: $pattern"
    fi
    sleep 0.1
  done
  fail_probe "barracks UI probe timed out waiting for ${label}: $pattern"
}

sleep "${CLASH95_BARRACKS_UI_INITIAL_WAIT:-2}"
window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
if [ -z "$window" ]; then
  fail_probe "barracks UI probe could not find the SDL window"
fi
echo "[probe] found window: $window" >>"$log_path"

click_at "$window" "${CLASH95_CLICK_CAMPAIGN_X:-245}" "${CLASH95_CLICK_CAMPAIGN_Y:-186}" 0.18 "${CLASH95_BARRACKS_UI_CAMPAIGN_GAP:-0.55}" "campaign"
click_at "$window" "${CLASH95_CLICK_CAMPAIGN_FIRST_X:-220}" "${CLASH95_CLICK_CAMPAIGN_FIRST_Y:-298}" 0.18 "${CLASH95_BARRACKS_UI_CAMPAIGN_FIRST_GAP:-0.55}" "campaign-first"

skip_index=1
while [ "$skip_index" -le "${CLASH95_BARRACKS_UI_SKIP_COUNT:-6}" ]; do
  click_at "$window" "${CLASH95_CLICK_SKIP_X:-320}" "${CLASH95_CLICK_SKIP_Y:-240}" 0.12 0.45 "skip-${skip_index}"
  if grep -Fq "${CLASH95_BARRACKS_UI_HUMAN_TURN_PATTERN:-human_turn_enter idx=1 owner=0 tile=31,44}" "$log_path"; then
    break
  fi
  skip_index=$((skip_index + 1))
done
wait_for_log "${CLASH95_BARRACKS_UI_HUMAN_TURN_PATTERN:-human_turn_enter idx=1 owner=0 tile=31,44}" "human turn" "${CLASH95_BARRACKS_UI_HUMAN_TURN_TIMEOUT:-25}"

click_at "$window" "${CLASH95_CLICK_NEXT_BUILDING_X:-544}" "${CLASH95_CLICK_NEXT_BUILDING_Y:-400}" 0.22 0.80 "next-building"
sleep "${CLASH95_BARRACKS_UI_AFTER_NEXT_BUILDING_WAIT:-1.0}"
click_at "$window" \
  "${CLASH95_CLICK_BUILDING_TILE_X:-320}" \
  "${CLASH95_CLICK_BUILDING_TILE_Y:-240}" \
  "${CLASH95_CLICK_BUILDING_TILE_HOLD:-0.25}" \
  "${CLASH95_CLICK_BUILDING_TILE_GAP:-1.50}" \
  "building-tile"

if [ "${CLASH95_BARRACKS_UI_CLICK_BARRACKS:-0}" = "1" ]; then
  sleep "${CLASH95_BARRACKS_UI_BEFORE_BARRACKS_WAIT:-1.0}"
  click_at "$window" "${CLASH95_CLICK_BARRACKS_X:-0}" "${CLASH95_CLICK_BARRACKS_Y:-0}" 0.25 2.0 "barracks-hotspot"
fi

if [ "${CLASH95_BARRACKS_UI_CLICK_SLOT:-0}" = "1" ]; then
  sleep "${CLASH95_BARRACKS_UI_BEFORE_SLOT_WAIT:-0.8}"
  click_at "$window" \
    "${CLASH95_CLICK_BARRACKS_SLOT_X:-142}" \
    "${CLASH95_CLICK_BARRACKS_SLOT_Y:-110}" \
    "${CLASH95_CLICK_BARRACKS_SLOT_HOLD:-1.5}" \
    "${CLASH95_CLICK_BARRACKS_SLOT_GAP:-0.4}" \
    "barracks-slot" \
    "${CLASH95_CLICK_BARRACKS_SLOT_BUTTON:-1}"
fi

sleep "${CLASH95_BARRACKS_UI_POST_ROUTE_WAIT:-4.0}"
echo "[probe] route complete" >>"$log_path"

frame_count=0
last_frame=""
for captured_frame in "$frame_prefix"-*.bmp; do
  if [ -f "$captured_frame" ]; then
    frame_count=$((frame_count + 1))
    last_frame="$captured_frame"
  fi
done
echo "[probe] captured_frames=$frame_count last_frame=${last_frame:-none}" >>"$log_path"
if [ "$frame_count" -eq 0 ]; then
  fail_probe "barracks UI probe did not capture any frames"
fi

kill -TERM "-$pid" 2>/dev/null || true
sleep 1
kill -KILL "-$pid" 2>/dev/null || true
wait "$pid" 2>/dev/null || true
pid=""
