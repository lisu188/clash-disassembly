#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "castle economy probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

if [ "${CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION:-0}" != "1" ]; then
  echo "castle economy probe skipped; set CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION=1 to run" >&2
  exit 77
fi

for tool in Xvfb xdotool timeout grep head tail find sort python3; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "castle economy probe skipped; missing $tool" >&2
    exit 77
  fi
done

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
probe_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-castle-economy.XXXXXX")"
log_path="$probe_root/castle-economy.log"
frame_prefix="$probe_root/frame"
pid=""
xvfb_pid=""
preserve_artifacts=0
: >"$log_path"

fail_probe() {
  local message="$1"

  echo "$message" >&2
  tail -n "${CLASH95_CASTLE_ECONOMY_FAIL_TAIL_LINES:-400}" "$log_path" >&2 || true
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
    echo "castle economy probe artifacts: $probe_root" >&2
  else
    rm -rf "$probe_root"
  fi
}
trap cleanup EXIT

click_at() {
  local window="$1"
  local x="$2"
  local y="$3"
  local hold="${4:-0.18}"
  local gap="${5:-0.55}"
  local label="${6:-click}"

  echo "[probe] ${label}: click at ${x},${y} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep 0.08
  xdotool mousedown 1
  sleep "$hold"
  xdotool mouseup 1
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
      fail_probe "castle economy probe process exited while waiting for ${label}: $pattern"
    fi
    sleep 0.1
  done
  fail_probe "castle economy probe timed out waiting for ${label}: $pattern"
}

latest_modified_frame() {
  find "$probe_root" -maxdepth 1 -type f -name 'frame-*.bmp' -printf '%T@ %p\n' \
    | sort -n \
    | tail -n 1 \
    | sed 's/^[^ ]* //'
}

check_latest_frame_nonblank() {
  local label="$1"
  local latest_frame

  latest_frame="$(latest_modified_frame)"
  if [ -z "$latest_frame" ] || [ ! -f "$latest_frame" ]; then
    fail_probe "castle economy probe has no frame for ${label}"
  fi
  echo "[probe] nonblank-check ${label}: ${latest_frame}" >>"$log_path"
  python3 "$repo_root/tests/frame_metrics.py" \
    "$latest_frame" \
    --min-mean "${CLASH95_CASTLE_ECONOMY_MIN_FRAME_MEAN:-1}" \
    --min-nonblack "${CLASH95_CASTLE_ECONOMY_MIN_NONBLACK_PIXELS:-1000}" \
    --min-colors "${CLASH95_CASTLE_ECONOMY_MIN_COLORS:-8}" \
    --quiet >>"$log_path" 2>&1 \
    || fail_probe "castle economy probe captured a blank/low-detail frame for ${label}: ${latest_frame}"
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

setsid timeout "${CLASH95_CASTLE_ECONOMY_TIMEOUT_SECONDS:-95}s" env \
  SDL_AUDIODRIVER=dummy \
  CLASH95_SKIP_BOOT_AVI=1 \
  CLASH95_TRACE_WORLD_CLICK=1 \
  CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
  CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-0}" \
  CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-64}" \
  CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER="${CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER:-1}" \
  "$bootstrap_bin" >>"$log_path" 2>&1 &
pid=$!
echo "[probe] launched bootstrap pid=$pid" >>"$log_path"

sleep "${CLASH95_CASTLE_ECONOMY_INITIAL_WAIT:-2}"
window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
if [ -z "$window" ]; then
  fail_probe "castle economy probe could not find the SDL window"
fi
echo "[probe] found window: $window" >>"$log_path"

wait_for_log "${CLASH95_CASTLE_ECONOMY_MAIN_MENU_PATTERN:-[pcx] load path=gfx\\menu\\main.gfx}" "main menu" 20
click_at "$window" "${CLASH95_CLICK_CAMPAIGN_X:-245}" "${CLASH95_CLICK_CAMPAIGN_Y:-186}" 0.18 0.55 "campaign"
click_at "$window" "${CLASH95_CLICK_CAMPAIGN_FIRST_X:-220}" "${CLASH95_CLICK_CAMPAIGN_FIRST_Y:-298}" 0.18 0.55 "campaign-first"

skip_index=1
while [ "$skip_index" -le "${CLASH95_CASTLE_ECONOMY_SKIP_COUNT:-6}" ]; do
  click_at "$window" "${CLASH95_CLICK_SKIP_X:-320}" "${CLASH95_CLICK_SKIP_Y:-240}" 0.12 0.45 "skip-${skip_index}"
  if grep -Fq "${CLASH95_CASTLE_ECONOMY_HUMAN_TURN_PATTERN:-human_turn_enter idx=1 owner=0 tile=31,44}" "$log_path"; then
    break
  fi
  skip_index=$((skip_index + 1))
done
wait_for_log "${CLASH95_CASTLE_ECONOMY_HUMAN_TURN_PATTERN:-human_turn_enter idx=1 owner=0 tile=31,44}" "human turn" 25

click_at "$window" "${CLASH95_CLICK_NEXT_BUILDING_X:-544}" "${CLASH95_CLICK_NEXT_BUILDING_Y:-400}" 0.22 0.80 "next-building"
sleep "${CLASH95_CASTLE_ECONOMY_AFTER_NEXT_BUILDING_WAIT:-1.0}"
click_at "$window" "${CLASH95_CLICK_BUILDING_TILE_X:-320}" "${CLASH95_CLICK_BUILDING_TILE_Y:-240}" 0.25 1.50 "building-tile"
wait_for_log "[castle] first_present building_idx=0" "castle first present" 30
wait_for_log "[castle] hotspot pixel=255" "castle economy hotspot" 5

click_at "$window" "${CLASH95_CLICK_CASTLE_ECONOMY_X:-548}" "${CLASH95_CLICK_CASTLE_ECONOMY_Y:-412}" 0.25 2.0 "castle-economy"
wait_for_log "[economy] first_present building_idx=0" "economy first present" 20
sleep "${CLASH95_CASTLE_ECONOMY_PRESENT_WAIT:-0.8}"
check_latest_frame_nonblank "economy"

click_at \
  "$window" \
  "${CLASH95_CLICK_ECONOMY_LIST_NEXT_X:-475}" \
  "${CLASH95_CLICK_ECONOMY_LIST_NEXT_Y:-350}" \
  "${CLASH95_CLICK_ECONOMY_LIST_NEXT_HOLD:-0.08}" \
  "${CLASH95_CLICK_ECONOMY_LIST_NEXT_GAP:-0.90}" \
  "economy-list-next"
wait_for_log "[economy] list_next" "economy list next" 10
check_latest_frame_nonblank "economy-list-next"

click_at "$window" "${CLASH95_CLICK_ECONOMY_BACK_X:-90}" "${CLASH95_CLICK_ECONOMY_BACK_Y:-451}" 0.22 1.20 "economy-back"
wait_for_log "[economy] back exit_signal=1" "economy back signal" 10
wait_for_log "[economy] exit building_idx=0" "economy exit" 10

if ! kill -0 "$pid" 2>/dev/null; then
  fail_probe "castle economy probe process exited immediately after economy back"
fi

kill -TERM "-$pid" 2>/dev/null || true
sleep 1
kill -KILL "-$pid" 2>/dev/null || true
wait "$pid" 2>/dev/null || true
pid=""
