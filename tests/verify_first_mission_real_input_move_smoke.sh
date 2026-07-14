#!/usr/bin/env bash
# Optional end-turn hotkey probe: set CLASH95_FIRST_MISSION_MOVE_END_TURN_KEY
# to an xdotool key name. The script sends it before the existing end-turn click.
set -euo pipefail

# Opt-in real-input route smoke for the first mission.
#
# Required:
#   CLASH95_ENABLE_REAL_INPUT_SMOKES=1
#
# Common validation knobs:
#   CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET=route,world-click
#   CLASH95_FIRST_MISSION_MOVE_REQUIRE_FRAMES=1
#   CLASH95_FIRST_MISSION_MOVE_REJECT_BLANK_FRAMES=1
#   CLASH95_KEEP_SMOKE_ARTIFACTS=1
#
# Optional route extensions:
#   CLASH95_FIRST_MISSION_MOVE_SECOND_ACTION=1
#   CLASH95_SECOND_ACTION_WAIT_FOR_MOVE=1
#   CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET=...,enemy-attack
#   CLASH95_FIRST_MISSION_MOVE_END_TURN=1
#   CLASH95_FIRST_MISSION_MOVE_POST_END_TURN_SKIPS=4
#   CLASH95_FIRST_MISSION_MOVE_FIFTH_ACTION=1
#   CLASH95_FIRST_MISSION_MOVE_SIXTH_ACTION=1
#   CLASH95_FIRST_MISSION_MOVE_SEVENTH_ACTION=1
#   CLASH95_FIRST_MISSION_STACK4_CHASE_REPEATS=8
#   CLASH95_FIRST_MISSION_STACK5_PROBE=1
#   CLASH95_FIRST_MISSION_TACTICAL_ACTION=1
#
# Coordinates and timings are environment-overridable; see the click_at calls
# below for the exact CLASH95_CLICK_* variable names.

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "first-mission real-input smoke binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

if [ "${CLASH95_ENABLE_REAL_INPUT_SMOKES:-0}" != "1" ]; then
  echo "first-mission real-input smoke skipped; set CLASH95_ENABLE_REAL_INPUT_SMOKES=1 to run" >&2
  exit 77
fi

for tool in Xvfb xdotool timeout grep head pgrep tail wc awk cp mkdir find sort; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "first-mission real-input smoke skipped; missing $tool" >&2
    exit 77
  fi
done
if [ "${CLASH95_FIRST_MISSION_MOVE_GDB:-0}" = "1" ] && ! command -v gdb >/dev/null 2>&1; then
  echo "first-mission real-input smoke skipped; missing gdb" >&2
  exit 77
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
export CLASH95_ARTIFACT_PRUNE_AFTER_RUN="${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}"
export CLASH95_ARTIFACT_PRUNE_MAX_BYTES="${CLASH95_ARTIFACT_PRUNE_MAX_BYTES:-805306368}"
smoke_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-first-mission-move.XXXXXX")"
log_path="$smoke_root/first-mission-move.log"
frame_prefix="$smoke_root/frame"
world_input_script="$smoke_root/world-input.txt"
platform_input_script="$smoke_root/platform-input.txt"
battle_input_script="$smoke_root/battle-input.txt"
pid=""
xvfb_pid=""
preserve_artifacts=0
: >"$world_input_script"
: >"$platform_input_script"
: >"$battle_input_script"

fail_smoke() {
  local message="$1"

  echo "$message" >&2
  if [ "${CLASH95_SMOKE_FAIL_FULL_LOG:-0}" = "1" ]; then
    cat "$log_path" >&2 || true
  else
    tail -n "${CLASH95_SMOKE_FAIL_TAIL_LINES:-400}" "$log_path" >&2 || true
  fi
  preserve_artifacts=1
  exit 1
}

is_unsigned_integer() {
  case "${1:-}" in
    ""|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
}

copy_capped_first_mission_log() {
  local source_path="$1"
  local target_path="$2"
  local max_bytes="${CLASH95_FIRST_MISSION_MAX_LOG_BYTES:-12000000}"
  local head_lines="${CLASH95_FIRST_MISSION_LOG_HEAD_LINES:-1200}"
  local tail_lines="${CLASH95_FIRST_MISSION_LOG_TAIL_LINES:-2400}"

  durable_log_bytes="$(wc -c <"$source_path" 2>/dev/null || echo 0)"
  durable_log_bytes="${durable_log_bytes//[[:space:]]/}"
  durable_log_truncated=0

  if ! is_unsigned_integer "$max_bytes" || [ "$max_bytes" = "0" ]; then
    cp -f "$source_path" "$target_path" 2>/dev/null || true
    return 0
  fi
  if ! is_unsigned_integer "$head_lines"; then
    head_lines=1200
  fi
  if ! is_unsigned_integer "$tail_lines"; then
    tail_lines=2400
  fi
  if [ "${durable_log_bytes:-0}" -le "$max_bytes" ]; then
    cp -f "$source_path" "$target_path" 2>/dev/null || true
    return 0
  fi

  durable_log_truncated=1
  {
    echo "[smoke] durable log truncated"
    echo "original_bytes=${durable_log_bytes:-0}"
    echo "max_bytes=$max_bytes"
    echo "head_lines=$head_lines"
    echo "tail_lines=$tail_lines"
    echo
    echo "--- log head ---"
    head -n "$head_lines" "$source_path" || true
    echo
    echo "--- log tail ---"
    tail -n "$tail_lines" "$source_path" || true
  } >"$target_path" 2>/dev/null || true
}

copy_capped_first_mission_frames() {
  local target_dir="$1"
  local max_frames="${CLASH95_FIRST_MISSION_MAX_COPIED_FRAMES:-160}"
  local head_count="${CLASH95_FIRST_MISSION_COPIED_FRAME_HEAD_COUNT:-8}"
  local tail_count
  local index
  local start_index
  local captured_frame
  local -A copied_frame_paths=()

  copied_frames=0
  captured_frames_total=0
  frames_truncated=0
  copied_frame_cap="$max_frames"
  last_frame=""

  if ! is_unsigned_integer "$max_frames"; then
    max_frames=160
  fi
  copied_frame_cap="$max_frames"
  if ! is_unsigned_integer "$head_count"; then
    head_count=8
  fi

  shopt -s nullglob
  local captured_frames=( "$frame_prefix"-*.bmp )
  shopt -u nullglob
  captured_frames_total="${#captured_frames[@]}"
  if [ "$captured_frames_total" -eq 0 ]; then
    return 0
  fi
  last_frame="${captured_frames[$((captured_frames_total - 1))]}"
  if [ "$max_frames" -eq 0 ]; then
    frames_truncated=1
    return 0
  fi

  copy_one_frame() {
    local frame_path="$1"

    if [ ! -f "$frame_path" ]; then
      return 0
    fi
    if [ -n "${copied_frame_paths[$frame_path]+x}" ]; then
      return 0
    fi
    cp -f "$frame_path" "$target_dir/" 2>/dev/null || true
    copied_frame_paths[$frame_path]=1
    copied_frames=$((copied_frames + 1))
  }

  if [ "$captured_frames_total" -le "$max_frames" ]; then
    for captured_frame in "${captured_frames[@]}"; do
      copy_one_frame "$captured_frame"
    done
    return 0
  fi

  frames_truncated=1
  if [ "$head_count" -ge "$max_frames" ]; then
    head_count=$((max_frames - 1))
  fi
  if [ "$head_count" -lt 0 ]; then
    head_count=0
  fi
  tail_count=$((max_frames - head_count))

  index=0
  while [ "$index" -lt "$head_count" ] && [ "$index" -lt "$captured_frames_total" ]; do
    copy_one_frame "${captured_frames[$index]}"
    index=$((index + 1))
  done

  start_index=$((captured_frames_total - tail_count))
  if [ "$start_index" -lt 0 ]; then
    start_index=0
  fi
  index="$start_index"
  while [ "$index" -lt "$captured_frames_total" ]; do
    copy_one_frame "${captured_frames[$index]}"
    index=$((index + 1))
  done
}

prune_old_first_mission_runs() {
  local durable_root="$1"
  local keep_runs="${CLASH95_FIRST_MISSION_KEEP_RUNS:-12}"
  local root_real
  local artifacts_real
  local candidate
  local candidate_real

  if ! is_unsigned_integer "$keep_runs" || [ "$keep_runs" = "0" ]; then
    return 0
  fi
  if [ ! -d "$durable_root" ]; then
    return 0
  fi

  root_real="$(cd "$durable_root" && pwd -P)" || return 0
  mkdir -p "$repo_root/artifacts" 2>/dev/null || true
  artifacts_real="$(cd "$repo_root/artifacts" && pwd -P)" || return 0
  case "$root_real" in
    "$artifacts_real"|"$artifacts_real"/*) ;;
    *)
      echo "[smoke] skip artifact pruning outside repo artifacts: $root_real" >&2
      return 0
      ;;
  esac

  find "$root_real" -mindepth 1 -maxdepth 1 -type d -printf '%T@ %p\n' 2>/dev/null \
    | sort -rn \
    | awk -v keep="$keep_runs" 'NR > keep { first = index($0, " "); if (first > 0) print substr($0, first + 1) }' \
    | while IFS= read -r candidate; do
        candidate_real="$(cd "$candidate" && pwd -P 2>/dev/null)" || continue
        if [ "$candidate_real" = "$root_real" ]; then
          continue
        fi
        case "$candidate_real" in
          "$root_real"/*)
            rm -rf -- "$candidate_real"
            echo "[smoke] pruned old artifact run: $candidate_real" >&2
            ;;
        esac
      done
}

prune_repo_artifacts_if_requested() {
  if [ "${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-0}" != "1" ]; then
    return 0
  fi
  if [ ! -f "$repo_root/tests/prune_artifacts.sh" ]; then
    return 0
  fi

  CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP="${CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP:-${CLASH95_FIRST_MISSION_KEEP_RUNS:-12}}" \
    bash "$repo_root/tests/prune_artifacts.sh" --apply --quiet >&2 || true
}

persist_mission_artifacts() {
  local durable_root
  local run_id
  local durable_run
  local copied_frames
  local captured_frames_total
  local copied_frame_cap
  local frames_truncated
  local captured_frame
  local copied_xvfb
  local last_frame
  local frame_mean
  local frame_mean_tool
  local durable_log_bytes
  local durable_log_truncated
  local objective_complete_count
  local objective_blocked_count
  local summary_path
  local xvfb_log
  local route_env_path
  local route_input_step_count

  if [ "${CLASH95_FIRST_MISSION_DURABLE_ARTIFACTS:-1}" != "1" ]; then
    return 0
  fi

  durable_root="${CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR:-$repo_root/artifacts/first-campaign/mission-00}"
  run_id="${CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_RUN_ID:-$(date -u +%Y%m%dT%H%M%SZ)-$$}"
  durable_run="$durable_root/$run_id"
  mkdir -p "$durable_run"
  {
    echo "[smoke] durable_artifacts=$durable_run"
  } >>"$log_path" 2>/dev/null || true
  copy_capped_first_mission_log "$log_path" "$durable_run/first-mission-move.log"
  cp -f "$world_input_script" "$durable_run/world-input.txt" 2>/dev/null || true
  cp -f "$platform_input_script" "$durable_run/platform-input.txt" 2>/dev/null || true
  cp -f "$battle_input_script" "$durable_run/battle-input.txt" 2>/dev/null || true
  route_env_path="${CLASH95_FIRST_MISSION_ROUTE_ENV_FILE:-$repo_root/tests/first_campaign_arc_routes/mission_00.env}"
  if [ -f "$route_env_path" ]; then
    cp -f "$route_env_path" "$durable_run/mission_00.env" 2>/dev/null || true
  fi
  env | grep '^CLASH95_' | sort >"$durable_run/clash95-env.txt" 2>/dev/null || true
  copy_capped_first_mission_frames "$durable_run"
  copied_xvfb=0
  for xvfb_log in "$smoke_root"/xvfb-*.log; do
    if [ -f "$xvfb_log" ]; then
      cp -f "$xvfb_log" "$durable_run/" 2>/dev/null || true
      copied_xvfb=$((copied_xvfb + 1))
    fi
  done
  frame_mean=""
  frame_mean_tool=""
  if [ -n "$last_frame" ] && [ -f "$last_frame" ]; then
    if command -v identify >/dev/null 2>&1; then
      frame_mean="$(identify -format '%[mean]' "$last_frame" 2>/dev/null || true)"
      frame_mean_tool="identify"
    elif command -v magick >/dev/null 2>&1; then
      frame_mean="$(magick identify -format '%[mean]' "$last_frame" 2>/dev/null || true)"
      frame_mean_tool="magick"
    elif command -v python3 >/dev/null 2>&1; then
      frame_mean="$(python3 - "$last_frame" <<'PY' 2>/dev/null || true
import struct
import sys

path = sys.argv[1]
with open(path, "rb") as fh:
    data = fh.read()
if len(data) < 54 or data[:2] != b"BM":
    raise SystemExit(1)
pixel_offset = struct.unpack_from("<I", data, 10)[0]
dib_size = struct.unpack_from("<I", data, 14)[0]
if dib_size < 40:
    raise SystemExit(1)
width = struct.unpack_from("<i", data, 18)[0]
height = struct.unpack_from("<i", data, 22)[0]
bpp = struct.unpack_from("<H", data, 28)[0]
compression = struct.unpack_from("<I", data, 30)[0]
if width == 0 or height == 0 or bpp not in (24, 32) or compression not in (0, 3):
    raise SystemExit(1)
width = abs(width)
height = abs(height)
bytes_per_pixel = bpp // 8
stride = ((width * bytes_per_pixel + 3) // 4) * 4
total = 0
count = 0
for row in range(height):
    start = pixel_offset + row * stride
    end = start + width * bytes_per_pixel
    pixels = data[start:end]
    if len(pixels) < width * bytes_per_pixel:
        raise SystemExit(1)
    total += sum(pixels)
    count += len(pixels)
print("{:.6f}".format(total / count if count else 0.0))
PY
)"
      frame_mean_tool="python3-bmp"
    else
      frame_mean_tool="unavailable"
    fi
  fi
  objective_complete_count="$(grep -Fc "mission_objective_complete" "$log_path" 2>/dev/null || true)"
  objective_blocked_count="$(grep -Fc "mission_objective_blocked" "$log_path" 2>/dev/null || true)"
  route_input_step_count="$(awk 'index($0, "[smoke] route-input-step ") { count++ } END { print count + 0 }' "$log_path" 2>/dev/null || echo 0)"
  summary_path="$durable_run/summary.txt"
  {
    echo "durable_run=$durable_run"
    echo "captured_frames_total=$captured_frames_total"
    echo "copied_frames=$copied_frames"
    echo "copied_frame_cap=$copied_frame_cap"
    echo "frames_truncated=$frames_truncated"
    echo "copied_xvfb_logs=$copied_xvfb"
    echo "last_frame=$last_frame"
    echo "last_frame_mean=${frame_mean:-unavailable}"
    echo "last_frame_mean_tool=${frame_mean_tool:-none}"
    echo "durable_log_bytes=${durable_log_bytes:-0}"
    echo "durable_log_truncated=${durable_log_truncated:-0}"
    echo "mission_objective_complete_count=${objective_complete_count:-0}"
    echo "mission_objective_blocked_count=${objective_blocked_count:-0}"
    echo "route_input_step_count=${route_input_step_count:-0}"
    echo
    echo "mission markers:"
    grep -F "mission_objective_" "$log_path" | tail -n 40 || true
    echo
    echo "route input timeline:"
    grep -E "route-input-step|route-input-after|route-input-context|world-script|platform-script|battle-script|tactical" "$log_path" | tail -n 260 || true
    echo
    echo "turn and queen markers:"
    grep -E "queen_proposal|turn_advance|advance_turn_return|playgame_before_human_turn|after_turn_advance" "$log_path" | tail -n 80 || true
    echo
    echo "stack10 markers:"
    grep -E "idx=10|selected=10|next_unit_selected selected=10|unit_new_turn_stack selected=10|status_panel_refresh_done selected=10" "$log_path" | tail -n 100 || true
    echo
    echo "combat markers:"
    grep -E "enemy_attack_|unit_attack_|battle_|capture_defeated|unit_kill" "$log_path" | tail -n 120 || true
    echo
    echo "recent smoke log:"
    tail -n 160 "$log_path" || true
  } >"$summary_path" 2>/dev/null || true
  {
    echo "latest_run=$durable_run"
    echo "captured_frames_total=$captured_frames_total"
    echo "copied_frames=$copied_frames"
    echo "frames_truncated=$frames_truncated"
    echo "copied_xvfb_logs=$copied_xvfb"
    echo "last_frame_mean=${frame_mean:-unavailable}"
    echo "last_frame_mean_tool=${frame_mean_tool:-none}"
    echo "durable_log_bytes=${durable_log_bytes:-0}"
    echo "durable_log_truncated=${durable_log_truncated:-0}"
    echo "mission_objective_complete_count=${objective_complete_count:-0}"
    echo "mission_objective_blocked_count=${objective_blocked_count:-0}"
    echo "route_input_step_count=${route_input_step_count:-0}"
    echo "summary=$summary_path"
  } >"$durable_root/latest.txt" 2>/dev/null || true
  prune_old_first_mission_runs "$durable_root"
  prune_repo_artifacts_if_requested
  echo "[smoke] durable artifacts: $durable_run" >&2
  echo "[smoke] durable summary: $summary_path" >&2
}

require_fixed_log_pattern() {
  local expected_pattern="$1"
  local label="${2:-$1}"

  if ! grep -Fq "$expected_pattern" "$log_path"; then
    fail_smoke "first-mission real-input smoke did not find expected log pattern for ${label}: $expected_pattern"
  fi
}

wait_for_fixed_log_pattern() {
  local expected_pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_seconds="$SECONDS"

  echo "[smoke] wait-for-log: ${label} timeout=${timeout_seconds}s" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$expected_pattern" "$log_path"; then
      echo "[smoke] wait-for-log-done: ${label}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "first-mission real-input smoke process exited while waiting for log pattern ${label}: $expected_pattern"
    fi
    sleep 0.1
  done
  fail_smoke "first-mission real-input smoke timed out waiting for log pattern ${label}: $expected_pattern"
}

try_wait_for_fixed_log_pattern() {
  local expected_pattern="$1"
  local timeout_seconds="${2:-2}"
  local start_seconds="$SECONDS"

  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$expected_pattern" "$log_path"; then
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      return 1
    fi
    sleep 0.1
  done
  return 1
}

next_log_line_number() {
  local line_count
  line_count="$(wc -l <"$log_path" 2>/dev/null || echo 0)"
  echo $((line_count + 1))
}

log_has_fixed_pattern_since() {
  local expected_pattern="$1"
  local start_line="${2:-1}"

  awk -v start="$start_line" -v pattern="$expected_pattern" 'NR >= start && index($0, pattern) { found = 1; exit } END { exit found ? 0 : 1 }' "$log_path"
}

latest_stack_path_since() {
  local start_line="${1:-1}"
  local stack_index="${2:-10}"

  awk -v start="$start_line" -v stack_index="$stack_index" '
    NR >= start && (index($0, "unit_new_turn_stack selected=" stack_index " ") || index($0, "after_turn_advance idx=" stack_index " ")) {
      for (i = 1; i <= NF; ++i) {
        if ($i ~ /^c=/) {
          sub(/^c=/, "", $i)
          path = $i
        } else if ($i ~ /^path=/) {
          sub(/^path=/, "", $i)
          path = $i
        }
      }
    }
    END {
      if (path != "") {
        print path
      }
    }
  ' "$log_path"
}

latest_stack_ap_since() {
  local start_line="${1:-1}"
  local stack_index="${2:-10}"

  awk -v start="$start_line" -v stack_index="$stack_index" '
    NR >= start && (index($0, "human_turn_enter idx=" stack_index " ") || index($0, "after_turn_advance idx=" stack_index " ")) {
      for (i = 1; i <= NF; ++i) {
        if ($i ~ /^ap=/) {
          sub(/^ap=/, "", $i)
          ap = $i
        }
      }
    }
    END {
      if (ap != "") {
        print ap
      }
    }
  ' "$log_path"
}

latest_stack10_path_since() {
  latest_stack_path_since "$1" 10
}

latest_stack10_ap_since() {
  latest_stack_ap_since "$1" 10
}

wait_for_fixed_log_pattern_since() {
  local expected_pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_line="${4:-1}"
  local start_seconds="$SECONDS"

  echo "[smoke] wait-for-log-since: ${label} timeout=${timeout_seconds}s start=${start_line}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if log_has_fixed_pattern_since "$expected_pattern" "$start_line"; then
      echo "[smoke] wait-for-log-since-done: ${label}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "first-mission real-input smoke process exited while waiting for fresh log pattern ${label}: $expected_pattern"
    fi
    sleep 0.1
  done
  fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${label}: $expected_pattern"
}

try_wait_for_fixed_log_pattern_since() {
  local expected_pattern="$1"
  local timeout_seconds="${2:-2}"
  local start_line="${3:-1}"
  local start_seconds="$SECONDS"

  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if log_has_fixed_pattern_since "$expected_pattern" "$start_line"; then
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      return 1
    fi
    sleep 0.1
  done
  return 1
}

cleanup() {
  if [ -n "${pid:-}" ]; then
    kill -TERM "-$pid" 2>/dev/null || true
    kill -KILL "-$pid" 2>/dev/null || true
  fi
  if [ -n "${xvfb_pid:-}" ]; then
    kill "$xvfb_pid" 2>/dev/null || true
  fi
  persist_mission_artifacts
  if [ "${CLASH95_KEEP_SMOKE_ARTIFACTS:-0}" = "1" ] || [ "$preserve_artifacts" = "1" ]; then
    echo "first-mission real-input smoke artifacts: $smoke_root" >&2
  else
    rm -rf "$smoke_root"
  fi
}
trap cleanup EXIT

if [ "${CLASH95_XVFB_DISPLAY_NUMBER:-}" ]; then
  xvfb_candidates="$CLASH95_XVFB_DISPLAY_NUMBER"
else
  xvfb_candidates="$((90 + RANDOM % 1000)) $((90 + RANDOM % 1000)) $((90 + RANDOM % 1000)) $((90 + RANDOM % 1000)) $((90 + RANDOM % 1000))"
fi

for display_number in $xvfb_candidates; do
  echo "[smoke] trying Xvfb display :$display_number" >>"$log_path"
  Xvfb ":$display_number" -screen 0 "${CLASH95_XVFB_SCREEN:-800x600x24}" >"$smoke_root/xvfb-$display_number.log" 2>&1 &
  xvfb_pid=$!
  sleep 1
  if kill -0 "$xvfb_pid" 2>/dev/null; then
    break
  fi
  cat "$smoke_root/xvfb-$display_number.log" >>"$log_path" 2>/dev/null || true
  xvfb_pid=""
done

if [ -z "${xvfb_pid:-}" ]; then
  echo "first-mission real-input smoke skipped; Xvfb did not start on any candidate display" >&2
  cat "$log_path" >&2 || true
  exit 77
fi
export DISPLAY=":$display_number"
echo "[smoke] using DISPLAY=$DISPLAY" >>"$log_path"

click_hold="${CLASH95_REAL_INPUT_CLICK_HOLD:-0.18}"
click_gap="${CLASH95_REAL_INPUT_CLICK_GAP:-0.55}"
route_input_step=0

log_route_input_step() {
  local channel="$1"
  local action="$2"
  local label="${3:-}"
  local log_line
  local objective_complete_count
  local objective_blocked_count
  local recent_objective
  local recent_stack
  local recent_battle

  route_input_step=$((route_input_step + 1))
  log_line="$(next_log_line_number 2>/dev/null || echo 0)"
  objective_complete_count="$(grep -Fc "mission_objective_complete" "$log_path" 2>/dev/null || true)"
  objective_blocked_count="$(grep -Fc "mission_objective_blocked" "$log_path" 2>/dev/null || true)"
  recent_objective="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /ACTIVE_MISSION_INDEX|mission_objective_/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  recent_stack="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /selected=[0-9]|idx=[0-9]|unit_new_turn_stack|status_panel_refresh_done/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  recent_battle="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /enemy_attack_|unit_attack_|battle_|capture_defeated|unit_kill/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  echo "[smoke] route-input-step step=${route_input_step} line=${log_line} channel=${channel} action=${action} label=${label} objective_complete_count=${objective_complete_count:-0} objective_blocked_count=${objective_blocked_count:-0}" >>"$log_path"
  if [ -n "$recent_objective" ]; then
    echo "[smoke] route-input-context step=${route_input_step} phase=before kind=objective last=${recent_objective}" >>"$log_path"
  fi
  if [ -n "$recent_stack" ]; then
    echo "[smoke] route-input-context step=${route_input_step} phase=before kind=stack last=${recent_stack}" >>"$log_path"
  fi
  if [ -n "$recent_battle" ]; then
    echo "[smoke] route-input-context step=${route_input_step} phase=before kind=battle last=${recent_battle}" >>"$log_path"
  fi
}

log_route_input_after_step() {
  local step="${1:-$route_input_step}"
  local objective_complete_count
  local objective_blocked_count
  local recent_objective
  local recent_stack
  local recent_battle

  objective_complete_count="$(grep -Fc "mission_objective_complete" "$log_path" 2>/dev/null || true)"
  objective_blocked_count="$(grep -Fc "mission_objective_blocked" "$log_path" 2>/dev/null || true)"
  recent_objective="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /ACTIVE_MISSION_INDEX|mission_objective_/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  recent_stack="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /selected=[0-9]|idx=[0-9]|unit_new_turn_stack|status_panel_refresh_done/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  recent_battle="$(awk 'index($0, "[smoke] route-input-") == 0 && ($0 ~ /enemy_attack_|unit_attack_|battle_|capture_defeated|unit_kill/) { line = $0 } END { print line }' "$log_path" 2>/dev/null || true)"
  echo "[smoke] route-input-after step=${step} objective_complete_count=${objective_complete_count:-0} objective_blocked_count=${objective_blocked_count:-0}" >>"$log_path"
  if [ -n "$recent_objective" ]; then
    echo "[smoke] route-input-context step=${step} phase=after kind=objective last=${recent_objective}" >>"$log_path"
  fi
  if [ -n "$recent_stack" ]; then
    echo "[smoke] route-input-context step=${step} phase=after kind=stack last=${recent_stack}" >>"$log_path"
  fi
  if [ -n "$recent_battle" ]; then
    echo "[smoke] route-input-context step=${step} phase=after kind=battle last=${recent_battle}" >>"$log_path"
  fi
}

click_at() {
  local window="$1"
  local x="$2"
  local y="$3"
  local hold="${4:-$click_hold}"
  local gap="${5:-$click_gap}"
  local label="${6:-click}"

  log_route_input_step "xdotool" "click" "$label"
  echo "[smoke] ${label}: click at ${x},${y} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep 0.08
  xdotool mousedown 1
  sleep "$hold"
  xdotool mouseup 1
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

move_at() {
  local window="$1"
  local x="$2"
  local y="$3"
  local gap="${4:-0.25}"
  local label="${5:-move}"

  log_route_input_step "xdotool" "move" "$label"
  echo "[smoke] ${label}: move to ${x},${y} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

hold_key() {
  local window="$1"
  local key="$2"
  local hold="${3:-0.18}"
  local gap="${4:-0.20}"
  local label="${5:-key}"

  log_route_input_step "xdotool" "key" "$label"
  echo "[smoke] ${label}: key ${key} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool keydown --clearmodifiers "$key"
  sleep "$hold"
  xdotool keyup "$key"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

world_script_click_at() {
  local x="$1"
  local y="$2"
  local reads="${3:-4}"
  local gap="${4:-0.70}"
  local label="${5:-world-script-click}"

  log_route_input_step "world" "click" "$label"
  echo "[smoke] ${label}: world-script click at ${x},${y} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'click %s %s %s\n' "$x" "$y" "$reads" >>"$world_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

world_script_wait_reads() {
  local reads="${1:-8}"
  local gap="${2:-0.40}"
  local label="${3:-world-script-wait}"

  log_route_input_step "world" "wait" "$label"
  echo "[smoke] ${label}: world-script wait reads=${reads} gap=${gap}" >>"$log_path"
  printf 'wait %s\n' "$reads" >>"$world_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

world_script_key_pulse() {
  local scan_code="$1"
  local reads="${2:-4}"
  local gap="${3:-0.40}"
  local label="${4:-world-script-key}"

  log_route_input_step "world" "key" "$label"
  echo "[smoke] ${label}: world-script key scan=${scan_code} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'key %s %s\n' "$scan_code" "$reads" >>"$world_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

platform_script_click_at() {
  local x="$1"
  local y="$2"
  local reads="${3:-4}"
  local gap="${4:-0.70}"
  local label="${5:-platform-script-click}"

  log_route_input_step "platform" "click" "$label"
  echo "[smoke] ${label}: platform-script click at ${x},${y} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'click %s %s %s\n' "$x" "$y" "$reads" >>"$platform_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

platform_script_pulse() {
  local dx="$1"
  local dy="$2"
  local left="${3:-1}"
  local right="${4:-0}"
  local reads="${5:-4}"
  local gap="${6:-0.70}"
  local label="${7:-platform-script-pulse}"

  log_route_input_step "platform" "pulse" "$label"
  echo "[smoke] ${label}: platform-script pulse delta=${dx},${dy} buttons=${left},${right} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'pulse %s %s %s %s %s\n' "$dx" "$dy" "$left" "$right" "$reads" >>"$platform_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

battle_script_click_at() {
  local x="$1"
  local y="$2"
  local reads="${3:-4}"
  local gap="${4:-0.70}"
  local label="${5:-battle-script-click}"

  log_route_input_step "battle" "click" "$label"
  echo "[smoke] ${label}: battle-script click at ${x},${y} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'click %s %s %s\n' "$x" "$y" "$reads" >>"$battle_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

battle_script_wait_reads() {
  local reads="${1:-8}"
  local gap="${2:-0.40}"
  local label="${3:-battle-script-wait}"

  log_route_input_step "battle" "wait" "$label"
  echo "[smoke] ${label}: battle-script wait reads=${reads} gap=${gap}" >>"$log_path"
  printf 'wait %s\n' "$reads" >>"$battle_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

battle_script_key_pulse() {
  local scan_code="$1"
  local reads="${2:-4}"
  local gap="${3:-0.40}"
  local label="${4:-battle-script-key}"

  log_route_input_step "battle" "key" "$label"
  echo "[smoke] ${label}: battle-script key scan=${scan_code} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'key %s %s\n' "$scan_code" "$reads" >>"$battle_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

battle_script_pulse() {
  local dx="${1:-0}"
  local dy="${2:-0}"
  local left="${3:-1}"
  local right="${4:-0}"
  local reads="${5:-4}"
  local gap="${6:-0.40}"
  local label="${7:-battle-script-pulse}"

  log_route_input_step "battle" "pulse" "$label"
  echo "[smoke] ${label}: battle-script pulse delta=${dx},${dy} buttons=${left},${right} reads=${reads} gap=${gap}" >>"$log_path"
  printf 'pulse %s %s %s %s %s\n' "$dx" "$dy" "$left" "$right" "$reads" >>"$battle_input_script"
  sleep "$gap"
  log_route_input_after_step "$route_input_step"
}

route_env_value() {
  local name="$1"
  local default_value="${2:-}"

  if [ -n "${!name+x}" ]; then
    printf '%s' "${!name}"
  else
    printf '%s' "$default_value"
  fi
}

blocker_chase_env_value() {
  local target_index="$1"
  local suffix="$2"
  local default_value="${3:-}"
  local fallback

  fallback="$(route_env_value "CLASH95_STACK10_BLOCKER_CHASE_${suffix}" "$default_value")"
  route_env_value "CLASH95_STACK${target_index}_CHASE_${suffix}" "$fallback"
}

blocker_chase_click_env_value() {
  local target_index="$1"
  local suffix="$2"
  local default_value="${3:-}"
  local fallback

  fallback="$(route_env_value "CLASH95_CLICK_STACK10_BLOCKER_CHASE_${suffix}" "$default_value")"
  route_env_value "CLASH95_CLICK_STACK${target_index}_CHASE_${suffix}" "$fallback"
}

tactical_click_at() {
  local window="$1"
  local x="$2"
  local y="$3"
  local hold="$4"
  local gap="$5"
  local label="$6"

  if [ "${CLASH95_TACTICAL_ACTION_USE_BATTLE_SCRIPT:-1}" = "1" ]; then
    battle_script_click_at \
      "$x" \
      "$y" \
      "${CLASH95_TACTICAL_ACTION_BATTLE_SCRIPT_READS:-4}" \
      "$gap" \
      "$label"
  elif [ "${CLASH95_TACTICAL_ACTION_USE_PLATFORM_SCRIPT:-0}" = "1" ]; then
    platform_script_click_at \
      "$x" \
      "$y" \
      "${CLASH95_TACTICAL_ACTION_PLATFORM_SCRIPT_READS:-4}" \
      "$gap" \
      "$label"
  else
    click_at "$window" "$x" "$y" "$hold" "$gap" "$label"
  fi
}

move_window_to() {
  local window="$1"
  local x="$2"
  local y="$3"
  local gap="${4:-0.25}"
  local label="${5:-window-move}"

  echo "[smoke] ${label}: window move to ${x},${y} gap=${gap}" >>"$log_path"
  xdotool windowmove "$window" "$x" "$y" >/dev/null 2>&1 || true
  sleep "$gap"
}

run_command=("$bootstrap_bin")
if [ "${CLASH95_FIRST_MISSION_MOVE_GDB:-0}" = "1" ]; then
  run_command=(
    gdb -q -batch
    -ex run
    -ex "thread apply all bt full"
    -ex "info registers"
    -ex quit
    --args "$bootstrap_bin"
  )
fi

set +e
setsid timeout "${CLASH95_FIRST_MISSION_MOVE_TIMEOUT_SECONDS:-85}s" env \
  SDL_AUDIODRIVER=dummy \
  CLASH95_SKIP_BOOT_AVI=1 \
  CLASH95_HOST_CLICK_PULSE_READS="${CLASH95_HOST_CLICK_PULSE_READS:-4}" \
  CLASH95_TRACE_WORLD_CLICK=1 \
  CLASH95_TRACE_WORLD_INPUT_SCRIPT="${CLASH95_TRACE_WORLD_INPUT_SCRIPT:-1}" \
  CLASH95_WORLD_INPUT_SCRIPT="$world_input_script" \
  CLASH95_TRACE_BATTLE_INPUT_SCRIPT="${CLASH95_TRACE_BATTLE_INPUT_SCRIPT:-1}" \
  CLASH95_BATTLE_INPUT_SCRIPT="$battle_input_script" \
  CLASH95_INPUT_SCRIPT="$platform_input_script" \
  CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP="${CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP:-1}" \
  CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
  CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-260}" \
  CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-48}" \
  "${run_command[@]}" >>"$log_path" 2>&1 &
pid=$!
set -e
echo "[smoke] launched bootstrap pid=$pid" >>"$log_path"

sleep 2
if ! kill -0 "$pid" 2>/dev/null; then
  set +e
  wait "$pid"
  status=$?
  set -e
  fail_smoke "first-mission real-input smoke exited early with status $status"
fi

window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
if [ -z "$window" ]; then
  fail_smoke "first-mission real-input smoke could not find the SDL window"
  kill -TERM "-$pid" 2>/dev/null || true
fi
echo "[smoke] found window: $window" >>"$log_path"
xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
pre_route_wait="${CLASH95_FIRST_MISSION_MOVE_PRE_ROUTE_WAIT:-0}"
if [ "$pre_route_wait" != "0" ] && [ "$pre_route_wait" != "0.0" ]; then
  echo "[smoke] pre-route-wait: ${pre_route_wait}s" >>"$log_path"
  sleep "$pre_route_wait"
fi

if [ "${CLASH95_FIRST_MISSION_WAIT_FOR_MAIN_MENU:-1}" = "1" ]; then
  wait_for_fixed_log_pattern \
    "${CLASH95_FIRST_MISSION_MAIN_MENU_PATTERN:-[pcx] load path=gfx\\menu\\main.gfx}" \
    "main menu load" \
    "${CLASH95_FIRST_MISSION_MAIN_MENU_TIMEOUT:-20}"
  menu_settle_wait="${CLASH95_FIRST_MISSION_MAIN_MENU_SETTLE_WAIT:-0.2}"
  if [ "$menu_settle_wait" != "0" ] && [ "$menu_settle_wait" != "0.0" ]; then
    echo "[smoke] main-menu-settle-wait: ${menu_settle_wait}s" >>"$log_path"
    sleep "$menu_settle_wait"
  fi
fi

click_at "$window" "${CLASH95_CLICK_CAMPAIGN_X:-245}" "${CLASH95_CLICK_CAMPAIGN_Y:-186}" "$click_hold" "$click_gap" "campaign"
click_at "$window" "${CLASH95_CLICK_CAMPAIGN_FIRST_X:-220}" "${CLASH95_CLICK_CAMPAIGN_FIRST_Y:-298}" "$click_hold" "$click_gap" "campaign-first"

human_turn_pattern="human_turn_enter idx=1 owner=0 tile=31,44"
skip_count="${CLASH95_FIRST_MISSION_MOVE_SKIP_COUNT:-6}"
skip_index=1
while [ "$skip_index" -le "$skip_count" ]; do
  click_at "$window" "${CLASH95_CLICK_SKIP_X:-320}" "${CLASH95_CLICK_SKIP_Y:-240}" 0.12 0.45 "skip-${skip_index}"
  if [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_HUMAN_TURN:-1}" = "1" ]; then
    if try_wait_for_fixed_log_pattern "$human_turn_pattern" "${CLASH95_FIRST_MISSION_MOVE_SKIP_WAIT_SLICE:-2}"; then
      echo "[smoke] human-turn-detected-after-skip: ${skip_index}" >>"$log_path"
      break
    fi
  fi
  skip_index=$((skip_index + 1))
done

if [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_HUMAN_TURN:-1}" = "1" ]; then
  wait_for_fixed_log_pattern \
    "$human_turn_pattern" \
    "first-mission human turn" \
    "${CLASH95_FIRST_MISSION_MOVE_HUMAN_TURN_TIMEOUT:-25}"
fi

after_skip_wait="${CLASH95_FIRST_MISSION_MOVE_AFTER_SKIP_WAIT:-0}"
if [ "$after_skip_wait" != "0" ] && [ "$after_skip_wait" != "0.0" ]; then
  echo "[smoke] after-skip-wait: ${after_skip_wait}s" >>"$log_path"
  sleep "$after_skip_wait"
fi

click_at "$window" "${CLASH95_CLICK_NEXT_UNIT_X:-496}" "${CLASH95_CLICK_NEXT_UNIT_Y:-416}" 0.22 0.70 "next-unit"
if [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_NEXT_UNIT:-1}" = "1" ]; then
  wait_for_fixed_log_pattern \
    "next_unit_selected selected=1 a=31 b=44" \
    "first-mission next unit selection" \
    "${CLASH95_FIRST_MISSION_MOVE_NEXT_UNIT_TIMEOUT:-10}"
fi
click_at "$window" "${CLASH95_CLICK_UNIT_SLOT_X:-54}" "${CLASH95_CLICK_UNIT_SLOT_Y:-432}" 0.22 0.70 "unit-slot"
if [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_SLOT_TOGGLE:-1}" = "1" ]; then
  wait_for_fixed_log_pattern \
    "selection_slot_toggle selected=1 a=0 b=1" \
    "first-mission slot toggle" \
    "${CLASH95_FIRST_MISSION_MOVE_SLOT_TOGGLE_TIMEOUT:-10}"
fi
if [ -n "${CLASH95_CLICK_EXTRA_UNIT_SLOTS:-}" ]; then
  extra_slot_index=1
  old_ifs="$IFS"
  IFS=';'
  for extra_slot_click in $CLASH95_CLICK_EXTRA_UNIT_SLOTS; do
    IFS=','
    set -- $extra_slot_click
    IFS="$old_ifs"
    if [ "$#" -ge 2 ]; then
      click_at "$window" "$1" "$2" 0.22 "${CLASH95_CLICK_EXTRA_UNIT_SLOT_GAP:-0.70}" "unit-slot-extra-${extra_slot_index}"
    fi
    extra_slot_index=$((extra_slot_index + 1))
    IFS=';'
  done
  IFS="$old_ifs"
fi
click_at \
  "$window" \
  "${CLASH95_CLICK_MOVE_TARGET_X:-320}" \
  "${CLASH95_CLICK_MOVE_TARGET_Y:-304}" \
  "${CLASH95_CLICK_MOVE_TARGET_HOLD:-0.65}" \
  "${CLASH95_CLICK_MOVE_TARGET_GAP:-3.0}" \
  "move-target"

if [ "${CLASH95_FIRST_MISSION_MOVE_SECOND_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_SECOND_ACTION_CLICK_NEXT_UNIT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SECOND_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
      "${CLASH95_CLICK_SECOND_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
      0.22 \
      0.70 \
      "second-next-unit"
    if [ "${CLASH95_SECOND_ACTION_WAIT_FOR_NEXT_UNIT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_SECOND_ACTION_NEXT_UNIT_PATTERN:-next_unit_selected selected=10 a=31 b=45}" \
        "first-mission second next unit selection" \
        "${CLASH95_SECOND_ACTION_NEXT_UNIT_TIMEOUT:-10}"
    fi
  fi
  if [ "${CLASH95_SECOND_ACTION_CLICK_UNIT_SLOT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SECOND_UNIT_SLOT_X:-${CLASH95_CLICK_UNIT_SLOT_X:-569}}" \
      "${CLASH95_CLICK_SECOND_UNIT_SLOT_Y:-${CLASH95_CLICK_UNIT_SLOT_Y:-187}}" \
      0.22 \
      0.70 \
      "second-unit-slot"
  fi
  second_action_attack_start="$(next_log_line_number)"
  click_at \
    "$window" \
    "${CLASH95_CLICK_SECOND_MOVE_TARGET_X:-384}" \
    "${CLASH95_CLICK_SECOND_MOVE_TARGET_Y:-336}" \
    "${CLASH95_CLICK_SECOND_MOVE_TARGET_HOLD:-0.65}" \
    "${CLASH95_CLICK_SECOND_MOVE_TARGET_GAP:-3.0}" \
    "second-move-target"

  if [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_ENEMY_ATTACK:-0}" = "1" ]; then
    enemy_attack_pattern="${CLASH95_FIRST_MISSION_MOVE_ENEMY_ATTACK_PATTERN:-enemy_attack_call selected=10 a=3 b=46 c=45}"
    enemy_attack_retry_count="${CLASH95_FIRST_MISSION_MOVE_ENEMY_ATTACK_RETRY_COUNT:-2}"
    enemy_attack_retry_index=0
    while ! try_wait_for_fixed_log_pattern \
      "$enemy_attack_pattern" \
      "${CLASH95_FIRST_MISSION_MOVE_ENEMY_ATTACK_WAIT_SLICE:-3}"; do
      if [ "$enemy_attack_retry_index" -ge "$enemy_attack_retry_count" ]; then
        fail_smoke "first-mission real-input smoke did not reach enemy attack marker: $enemy_attack_pattern"
      fi
      enemy_attack_retry_index=$((enemy_attack_retry_index + 1))
      click_at \
        "$window" \
        "${CLASH95_CLICK_SECOND_MOVE_TARGET_X:-384}" \
        "${CLASH95_CLICK_SECOND_MOVE_TARGET_Y:-336}" \
        "${CLASH95_CLICK_SECOND_MOVE_TARGET_HOLD:-0.65}" \
        "${CLASH95_CLICK_SECOND_MOVE_TARGET_GAP:-1.0}" \
        "second-attack-retry-${enemy_attack_retry_index}"
    done
    echo "[smoke] enemy-attack-detected-after-retries: ${enemy_attack_retry_index}" >>"$log_path"
    if [ "${CLASH95_SECOND_ACTION_CLICK_BATTLE_PROMPT:-0}" = "1" ]; then
      if [ "${CLASH95_SECOND_ACTION_WAIT_FOR_BATTLE_PROMPT:-1}" = "1" ]; then
        wait_for_fixed_log_pattern_since \
          "${CLASH95_SECOND_ACTION_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
          "first-mission second-action battle prompt" \
          "${CLASH95_SECOND_ACTION_BATTLE_PROMPT_TIMEOUT:-10}" \
          "$second_action_attack_start"
      fi
      click_at \
        "$window" \
        "${CLASH95_CLICK_SECOND_BATTLE_PROMPT_X:-354}" \
        "${CLASH95_CLICK_SECOND_BATTLE_PROMPT_Y:-158}" \
        "${CLASH95_CLICK_SECOND_BATTLE_PROMPT_HOLD:-0.22}" \
        "${CLASH95_CLICK_SECOND_BATTLE_PROMPT_GAP:-4.0}" \
        "second-battle-prompt"
      if [ "${CLASH95_SECOND_ACTION_WAIT_FOR_BATTLE_RESULT:-1}" = "1" ]; then
        wait_for_fixed_log_pattern_since \
          "${CLASH95_SECOND_ACTION_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=10 a=3}" \
          "first-mission second-action battle result" \
          "${CLASH95_SECOND_ACTION_BATTLE_RESULT_TIMEOUT:-20}" \
          "$second_action_attack_start"
      fi
      if [ "${CLASH95_SECOND_ACTION_WAIT_FOR_BATTLE_RETURN:-1}" = "1" ]; then
        wait_for_fixed_log_pattern_since \
          "${CLASH95_SECOND_ACTION_BATTLE_RETURN_PATTERN:-unit_attack_autoresolve_return selected=10 a=3}" \
          "first-mission second-action battle return" \
          "${CLASH95_SECOND_ACTION_BATTLE_RETURN_TIMEOUT:-20}" \
          "$second_action_attack_start"
      fi
    elif [ "${CLASH95_FIRST_MISSION_MOVE_WAIT_FOR_ENEMY_ATTACK_RETURN:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_FIRST_MISSION_MOVE_ENEMY_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=10 a=3 b=46 c=45}" \
        "first-mission enemy attack return" \
        "${CLASH95_FIRST_MISSION_MOVE_ENEMY_ATTACK_RETURN_TIMEOUT:-10}"
    fi
  fi
  if [ "${CLASH95_SECOND_ACTION_WAIT_FOR_MOVE:-0}" = "1" ]; then
    wait_for_fixed_log_pattern_since \
      "${CLASH95_SECOND_ACTION_MOVE_PATTERN:-unit_move_after_path_state selected=10}" \
      "first-mission second-action move" \
      "${CLASH95_SECOND_ACTION_MOVE_TIMEOUT:-30}" \
      "$second_action_attack_start"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_END_TURN:-0}" = "1" ]; then
  end_turn_key="${CLASH95_FIRST_MISSION_MOVE_END_TURN_KEY:-}"
  if [ -n "${end_turn_key}" ]; then
    echo "[smoke] end-turn-key: ${end_turn_key}" >> "${log_path}"
    xdotool key --clearmodifiers "${end_turn_key}"
    sleep "${click_gap}"
  fi
  click_at \
    "$window" \
    "${CLASH95_CLICK_END_TURN_X:-500}" \
    "${CLASH95_CLICK_END_TURN_Y:-10}" \
    "${CLASH95_CLICK_END_TURN_HOLD:-0.22}" \
    "${CLASH95_CLICK_END_TURN_GAP:-5.0}" \
    "end-turn"

  if [ "${CLASH95_FIRST_MISSION_MOVE_POST_END_TURN_SKIPS:-0}" != "0" ]; then
    post_end_turn_skip_count="${CLASH95_FIRST_MISSION_MOVE_POST_END_TURN_SKIPS:-4}"
    post_end_turn_skip_index=1
    while [ "$post_end_turn_skip_index" -le "$post_end_turn_skip_count" ]; do
      click_at \
        "$window" \
        "${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}" \
        "${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}" \
        "${CLASH95_CLICK_POST_END_TURN_SKIP_HOLD:-0.12}" \
        "${CLASH95_CLICK_POST_END_TURN_SKIP_GAP:-0.65}" \
        "post-end-turn-skip-${post_end_turn_skip_index}"
      post_end_turn_skip_index=$((post_end_turn_skip_index + 1))
    done
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_THIRD_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_THIRD_ACTION_WAIT_FOR_READY:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_THIRD_ACTION_READY_PATTERN:-human_turn_enter idx=10 owner=0 tile=36,45 first=0}" \
      "first-mission third-action ready" \
      "${CLASH95_THIRD_ACTION_READY_TIMEOUT:-25}"
  fi
  if [ "${CLASH95_THIRD_ACTION_CLICK_SELECT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_THIRD_SELECT_X:-384}" \
      "${CLASH95_CLICK_THIRD_SELECT_Y:-240}" \
      "${CLASH95_CLICK_THIRD_SELECT_HOLD:-0.22}" \
      "${CLASH95_CLICK_THIRD_SELECT_GAP:-0.70}" \
      "third-select"
  fi
  if [ "${CLASH95_THIRD_ACTION_WAIT_FOR_SELECT:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_THIRD_ACTION_SELECT_PATTERN:-status_panel_refresh_done selected=10}" \
      "first-mission third-action selection" \
      "${CLASH95_THIRD_ACTION_SELECT_TIMEOUT:-10}"
  fi
  if [ "${CLASH95_THIRD_ACTION_CLICK_EXECUTE:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_THIRD_EXECUTE_X:-${CLASH95_CLICK_THIRD_SELECT_X:-384}}" \
      "${CLASH95_CLICK_THIRD_EXECUTE_Y:-${CLASH95_CLICK_THIRD_SELECT_Y:-240}}" \
      "${CLASH95_CLICK_THIRD_EXECUTE_HOLD:-0.35}" \
      "${CLASH95_CLICK_THIRD_EXECUTE_GAP:-3.0}" \
      "third-execute"
  fi
  if [ "${CLASH95_THIRD_ACTION_WAIT_FOR_MOVE:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_THIRD_ACTION_MOVE_PATTERN:-unit_move_after_path_state selected=10}" \
      "first-mission third-action queued move" \
      "${CLASH95_THIRD_ACTION_MOVE_TIMEOUT:-15}"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_FOURTH_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_FOURTH_ACTION_CLICK_TOP_CLOSE:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_TOP_CLOSE_X:-500}" \
      "${CLASH95_CLICK_FOURTH_TOP_CLOSE_Y:-2}" \
      "${CLASH95_CLICK_FOURTH_TOP_CLOSE_HOLD:-0.25}" \
      "${CLASH95_CLICK_FOURTH_TOP_CLOSE_GAP:-2.0}" \
      "fourth-top-close"
  fi
  fourth_post_skip_count="${CLASH95_FOURTH_ACTION_POST_TURN_SKIPS:-2}"
  fourth_post_skip_index=1
  while [ "$fourth_post_skip_index" -le "$fourth_post_skip_count" ]; do
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
      "${CLASH95_CLICK_FOURTH_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
      "${CLASH95_CLICK_FOURTH_POST_SKIP_HOLD:-0.12}" \
      "${CLASH95_CLICK_FOURTH_POST_SKIP_GAP:-0.8}" \
      "fourth-post-turn-skip-${fourth_post_skip_index}"
    fourth_post_skip_index=$((fourth_post_skip_index + 1))
  done
  if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_READY:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_FOURTH_ACTION_READY_PATTERN:-human_turn_enter idx=10 owner=0 tile=41,45 first=0}" \
      "first-mission fourth-action ready" \
      "${CLASH95_FOURTH_ACTION_READY_TIMEOUT:-25}"
  fi
  if [ "${CLASH95_FOURTH_ACTION_CLICK_SELECT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_SELECT_X:-448}" \
      "${CLASH95_CLICK_FOURTH_SELECT_Y:-240}" \
      "${CLASH95_CLICK_FOURTH_SELECT_HOLD:-0.22}" \
      "${CLASH95_CLICK_FOURTH_SELECT_GAP:-0.70}" \
      "fourth-select"
  fi
  if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_SELECT:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_FOURTH_ACTION_SELECT_PATTERN:-status_panel_refresh_done selected=10}" \
      "first-mission fourth-action selection" \
      "${CLASH95_FOURTH_ACTION_SELECT_TIMEOUT:-10}"
  fi
  if [ "${CLASH95_FOURTH_ACTION_CLICK_PAN:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_PAN_X:-565}" \
      "${CLASH95_CLICK_FOURTH_PAN_Y:-183}" \
      "${CLASH95_CLICK_FOURTH_PAN_HOLD:-0.22}" \
      "${CLASH95_CLICK_FOURTH_PAN_GAP:-0.70}" \
      "fourth-pan"
  fi
  if [ "${CLASH95_FOURTH_ACTION_CLICK_ATTACK:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_ATTACK_X:-384}" \
      "${CLASH95_CLICK_FOURTH_ATTACK_Y:-368}" \
      "${CLASH95_CLICK_FOURTH_ATTACK_HOLD:-0.85}" \
      "${CLASH95_CLICK_FOURTH_ATTACK_GAP:-4.0}" \
      "fourth-attack"
  fi
  if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_ATTACK:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_FOURTH_ACTION_ATTACK_PATTERN:-unit_attack_adjacent selected=10}" \
      "first-mission fourth-action adjacent attack" \
      "${CLASH95_FOURTH_ACTION_ATTACK_TIMEOUT:-20}"
  fi
  if [ "${CLASH95_FOURTH_ACTION_CLICK_BATTLE_PROMPT:-0}" = "1" ]; then
    if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_BATTLE_PROMPT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_FOURTH_ACTION_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
        "first-mission fourth-action battle prompt" \
        "${CLASH95_FOURTH_ACTION_BATTLE_PROMPT_TIMEOUT:-10}"
    fi
    click_at \
      "$window" \
      "${CLASH95_CLICK_FOURTH_BATTLE_PROMPT_X:-354}" \
      "${CLASH95_CLICK_FOURTH_BATTLE_PROMPT_Y:-158}" \
      "${CLASH95_CLICK_FOURTH_BATTLE_PROMPT_HOLD:-0.22}" \
      "${CLASH95_CLICK_FOURTH_BATTLE_PROMPT_GAP:-4.0}" \
      "fourth-battle-prompt"
    if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_BATTLE_RESULT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_FOURTH_ACTION_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=10}" \
        "first-mission fourth-action battle result" \
        "${CLASH95_FOURTH_ACTION_BATTLE_RESULT_TIMEOUT:-20}"
    fi
    if [ "${CLASH95_FOURTH_ACTION_WAIT_FOR_ATTACK_RETURN:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_FOURTH_ACTION_ATTACK_RETURN_PATTERN:-unit_attack_autoresolve_return selected=10}" \
        "first-mission fourth-action attack return" \
        "${CLASH95_FOURTH_ACTION_ATTACK_RETURN_TIMEOUT:-20}"
    fi
  fi
fi

if [ "${CLASH95_FIRST_MISSION_TACTICAL_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_TACTICAL_ACTION_WAIT_FOR_LOOP:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_TACTICAL_ACTION_LOOP_PATTERN:-battle_turn_loop_after_input_widgets}" \
      "first-mission tactical input loop" \
      "${CLASH95_TACTICAL_ACTION_LOOP_TIMEOUT:-30}"
  fi
  if [ "${CLASH95_TACTICAL_ACTION_CLICK_NEXT_UNIT:-1}" = "1" ]; then
    tactical_next_start_line="$(next_log_line_number)"
    tactical_click_at \
      "$window" \
      "${CLASH95_CLICK_TACTICAL_NEXT_UNIT_X:-577}" \
      "${CLASH95_CLICK_TACTICAL_NEXT_UNIT_Y:-386}" \
      "${CLASH95_CLICK_TACTICAL_NEXT_UNIT_HOLD:-0.22}" \
      "${CLASH95_CLICK_TACTICAL_NEXT_UNIT_GAP:-1.0}" \
      "tactical-next-unit"
    if [ "${CLASH95_TACTICAL_ACTION_WAIT_FOR_NEXT_UNIT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern_since \
        "${CLASH95_TACTICAL_ACTION_NEXT_UNIT_PATTERN:-battle_action_next_unit_selected}" \
        "first-mission tactical next-unit action" \
        "${CLASH95_TACTICAL_ACTION_NEXT_UNIT_TIMEOUT:-10}" \
        "$tactical_next_start_line"
    fi
  fi
  if [ "${CLASH95_TACTICAL_ACTION_CLICK_PREPARE_DEFENCE:-1}" = "1" ]; then
    tactical_defence_start_line="$(next_log_line_number)"
    tactical_click_at \
      "$window" \
      "${CLASH95_CLICK_TACTICAL_PREPARE_DEFENCE_X:-514}" \
      "${CLASH95_CLICK_TACTICAL_PREPARE_DEFENCE_Y:-448}" \
      "${CLASH95_CLICK_TACTICAL_PREPARE_DEFENCE_HOLD:-0.22}" \
      "${CLASH95_CLICK_TACTICAL_PREPARE_DEFENCE_GAP:-1.5}" \
      "tactical-prepare-defence"
    if [ "${CLASH95_TACTICAL_ACTION_WAIT_FOR_PREPARE_DEFENCE:-1}" = "1" ]; then
      wait_for_fixed_log_pattern_since \
        "${CLASH95_TACTICAL_ACTION_PREPARE_DEFENCE_PATTERN:-battle_action_prepare_defence_done}" \
        "first-mission tactical prepare-defence action" \
        "${CLASH95_TACTICAL_ACTION_PREPARE_DEFENCE_TIMEOUT:-10}" \
        "$tactical_defence_start_line"
    fi
  fi
  if [ "${CLASH95_TACTICAL_ACTION_CLICK_EXIT:-0}" = "1" ]; then
    tactical_exit_start_line="$(next_log_line_number)"
    tactical_click_at \
      "$window" \
      "${CLASH95_CLICK_TACTICAL_EXIT_X:-520}" \
      "${CLASH95_CLICK_TACTICAL_EXIT_Y:-14}" \
      "${CLASH95_CLICK_TACTICAL_EXIT_HOLD:-0.22}" \
      "${CLASH95_CLICK_TACTICAL_EXIT_GAP:-1.0}" \
      "tactical-exit"
    wait_for_fixed_log_pattern_since \
      "${CLASH95_TACTICAL_ACTION_EXIT_PATTERN:-battle_action_loop_exit_requested}" \
      "first-mission tactical exit action" \
      "${CLASH95_TACTICAL_ACTION_EXIT_TIMEOUT:-10}" \
      "$tactical_exit_start_line"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_FIFTH_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_FIFTH_ACTION_CLICK_NEXT_UNIT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FIFTH_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
      "${CLASH95_CLICK_FIFTH_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
      "${CLASH95_CLICK_FIFTH_NEXT_UNIT_HOLD:-0.22}" \
      "${CLASH95_CLICK_FIFTH_NEXT_UNIT_GAP:-0.70}" \
      "fifth-next-unit"
    if [ "${CLASH95_FIFTH_ACTION_WAIT_FOR_NEXT_UNIT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern \
        "${CLASH95_FIFTH_ACTION_NEXT_UNIT_PATTERN:-next_unit_selected selected=1 a=31 b=44}" \
        "first-mission fifth-action next unit selection" \
        "${CLASH95_FIFTH_ACTION_NEXT_UNIT_TIMEOUT:-10}"
    fi
  fi
  if [ "${CLASH95_FIFTH_ACTION_CLICK_MINIMAP:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FIFTH_MINIMAP_X:-441}" \
      "${CLASH95_CLICK_FIFTH_MINIMAP_Y:-29}" \
      "${CLASH95_CLICK_FIFTH_MINIMAP_HOLD:-0.22}" \
      "${CLASH95_CLICK_FIFTH_MINIMAP_GAP:-1.0}" \
      "fifth-minimap-next-blocker"
  fi
  if [ "${CLASH95_FIFTH_ACTION_CLICK_ATTACK:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_FIFTH_ATTACK_X:-448}" \
      "${CLASH95_CLICK_FIFTH_ATTACK_Y:-368}" \
      "${CLASH95_CLICK_FIFTH_ATTACK_HOLD:-1.2}" \
      "${CLASH95_CLICK_FIFTH_ATTACK_GAP:-4.0}" \
      "fifth-attack-next-blocker"
  fi
  if [ "${CLASH95_FIFTH_ACTION_WAIT_FOR_ATTACK:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_FIFTH_ACTION_ATTACK_PATTERN:-enemy_attack_call selected=1 a=4 b=15 c=6}" \
      "first-mission fifth-action next-blocker attack" \
      "${CLASH95_FIFTH_ACTION_ATTACK_TIMEOUT:-20}"
  fi
  if [ "${CLASH95_FIFTH_ACTION_WAIT_FOR_ATTACK_RETURN:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_FIFTH_ACTION_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=1 a=4 b=15 c=6}" \
      "first-mission fifth-action next-blocker attack return" \
      "${CLASH95_FIFTH_ACTION_ATTACK_RETURN_TIMEOUT:-20}"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_SIXTH_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_SIXTH_ACTION_CLICK_END_TURN:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SIXTH_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
      "${CLASH95_CLICK_SIXTH_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
      "${CLASH95_CLICK_SIXTH_END_TURN_HOLD:-0.25}" \
      "${CLASH95_CLICK_SIXTH_END_TURN_GAP:-2.0}" \
      "sixth-end-turn"
  fi
  sixth_post_skip_count="${CLASH95_SIXTH_ACTION_POST_TURN_SKIPS:-2}"
  sixth_post_skip_index=1
  while [ "$sixth_post_skip_index" -le "$sixth_post_skip_count" ]; do
    click_at \
      "$window" \
      "${CLASH95_CLICK_SIXTH_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
      "${CLASH95_CLICK_SIXTH_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
      "${CLASH95_CLICK_SIXTH_POST_SKIP_HOLD:-0.12}" \
      "${CLASH95_CLICK_SIXTH_POST_SKIP_GAP:-0.8}" \
      "sixth-post-turn-skip-${sixth_post_skip_index}"
    sixth_post_skip_index=$((sixth_post_skip_index + 1))
  done
  if [ "${CLASH95_SIXTH_ACTION_WAIT_FOR_READY:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_SIXTH_ACTION_READY_PATTERN:-human_turn_enter idx=1 owner=0 tile=27,42 first=0 slots=6}" \
      "first-mission sixth-action queued path ready" \
      "${CLASH95_SIXTH_ACTION_READY_TIMEOUT:-25}"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_SEVENTH_ACTION:-0}" = "1" ]; then
  if [ "${CLASH95_SEVENTH_ACTION_CLICK_SELECT:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SEVENTH_SELECT_X:-64}" \
      "${CLASH95_CLICK_SEVENTH_SELECT_Y:-112}" \
      "${CLASH95_CLICK_SEVENTH_SELECT_HOLD:-0.22}" \
      "${CLASH95_CLICK_SEVENTH_SELECT_GAP:-0.70}" \
      "seventh-select-stack1"
  fi
  if [ "${CLASH95_SEVENTH_ACTION_WAIT_FOR_SELECT:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_SEVENTH_ACTION_SELECT_PATTERN:-status_panel_refresh_done selected=1}" \
      "first-mission seventh-action stack selection" \
      "${CLASH95_SEVENTH_ACTION_SELECT_TIMEOUT:-10}"
  fi
  if [ "${CLASH95_SEVENTH_ACTION_CLICK_MINIMAP:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SEVENTH_MINIMAP_X:-441}" \
      "${CLASH95_CLICK_SEVENTH_MINIMAP_Y:-29}" \
      "${CLASH95_CLICK_SEVENTH_MINIMAP_HOLD:-0.22}" \
      "${CLASH95_CLICK_SEVENTH_MINIMAP_GAP:-1.0}" \
      "seventh-minimap-next-blocker"
  fi
  if [ "${CLASH95_SEVENTH_ACTION_CLICK_ATTACK:-1}" = "1" ]; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_SEVENTH_ATTACK_X:-448}" \
      "${CLASH95_CLICK_SEVENTH_ATTACK_Y:-368}" \
      "${CLASH95_CLICK_SEVENTH_ATTACK_HOLD:-1.2}" \
      "${CLASH95_CLICK_SEVENTH_ATTACK_GAP:-4.0}" \
      "seventh-attack-next-blocker"
  fi
  if [ "${CLASH95_SEVENTH_ACTION_WAIT_FOR_ATTACK:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_SEVENTH_ACTION_ATTACK_PATTERN:-enemy_attack_call selected=1 a=4 b=15 c=6}" \
      "first-mission seventh-action next-blocker attack" \
      "${CLASH95_SEVENTH_ACTION_ATTACK_TIMEOUT:-20}"
  fi
  if [ "${CLASH95_SEVENTH_ACTION_WAIT_FOR_ATTACK_RETURN:-1}" = "1" ]; then
    wait_for_fixed_log_pattern \
      "${CLASH95_SEVENTH_ACTION_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=1 a=4 b=15 c=6}" \
      "first-mission seventh-action next-blocker attack return" \
      "${CLASH95_SEVENTH_ACTION_ATTACK_RETURN_TIMEOUT:-20}"
  fi
fi

stack4_chase_repeats="${CLASH95_FIRST_MISSION_STACK4_CHASE_REPEATS:-0}"
stack4_chase_index=1
while [ "$stack4_chase_index" -le "$stack4_chase_repeats" ]; do
  chase_label="stack4-chase-${stack4_chase_index}"
  chase_turn_start="$(next_log_line_number)"
  click_at \
    "$window" \
    "${CLASH95_CLICK_STACK4_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
    "${CLASH95_CLICK_STACK4_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
    "${CLASH95_CLICK_STACK4_CHASE_END_TURN_HOLD:-0.25}" \
    "${CLASH95_CLICK_STACK4_CHASE_END_TURN_GAP:-2.0}" \
    "${chase_label}-end-turn"

  chase_post_skip_count="${CLASH95_STACK4_CHASE_POST_TURN_SKIPS:-2}"
  chase_post_skip_index=1
  while [ "$chase_post_skip_index" -le "$chase_post_skip_count" ]; do
    click_at \
      "$window" \
      "${CLASH95_CLICK_STACK4_CHASE_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
      "${CLASH95_CLICK_STACK4_CHASE_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
      "${CLASH95_CLICK_STACK4_CHASE_POST_SKIP_HOLD:-0.12}" \
      "${CLASH95_CLICK_STACK4_CHASE_POST_SKIP_GAP:-0.8}" \
      "${chase_label}-post-turn-skip-${chase_post_skip_index}"
    chase_post_skip_index=$((chase_post_skip_index + 1))
  done

  wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK4_CHASE_READY_PATTERN:-human_turn_enter idx=1 owner=0}" \
    "${chase_label} stack 1 ready" \
    "${CLASH95_STACK4_CHASE_READY_TIMEOUT:-25}" \
    "$chase_turn_start"

  chase_select_start="$(next_log_line_number)"
  click_at \
    "$window" \
    "${CLASH95_CLICK_STACK4_CHASE_SELECT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
    "${CLASH95_CLICK_STACK4_CHASE_SELECT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
    "${CLASH95_CLICK_STACK4_CHASE_SELECT_HOLD:-0.22}" \
    "${CLASH95_CLICK_STACK4_CHASE_SELECT_GAP:-0.70}" \
    "${chase_label}-select-stack1"
  wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK4_CHASE_SELECT_PATTERN:-next_unit_selected selected=1}" \
    "${chase_label} stack selection" \
    "${CLASH95_STACK4_CHASE_SELECT_TIMEOUT:-10}" \
    "$chase_select_start"

  click_at \
    "$window" \
    "${CLASH95_CLICK_STACK4_CHASE_MINIMAP_X:-441}" \
    "${CLASH95_CLICK_STACK4_CHASE_MINIMAP_Y:-29}" \
    "${CLASH95_CLICK_STACK4_CHASE_MINIMAP_HOLD:-0.22}" \
    "${CLASH95_CLICK_STACK4_CHASE_MINIMAP_GAP:-1.0}" \
    "${chase_label}-minimap-next-blocker"

  chase_attack_start="$(next_log_line_number)"
  click_at \
    "$window" \
    "${CLASH95_CLICK_STACK4_CHASE_ATTACK_X:-448}" \
    "${CLASH95_CLICK_STACK4_CHASE_ATTACK_Y:-368}" \
    "${CLASH95_CLICK_STACK4_CHASE_ATTACK_HOLD:-1.2}" \
    "${CLASH95_CLICK_STACK4_CHASE_ATTACK_GAP:-4.0}" \
    "${chase_label}-attack-next-blocker"
  wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK4_CHASE_ATTACK_PATTERN:-enemy_attack_call selected=1 a=4 b=15 c=6}" \
    "${chase_label} next-blocker attack" \
    "${CLASH95_STACK4_CHASE_ATTACK_TIMEOUT:-20}" \
    "$chase_attack_start"

  if try_wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK4_CHASE_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
    "${CLASH95_STACK4_CHASE_BATTLE_PROMPT_WAIT_SLICE:-2}" \
    "$chase_attack_start"; then
    click_at \
      "$window" \
      "${CLASH95_CLICK_STACK4_CHASE_BATTLE_PROMPT_X:-354}" \
      "${CLASH95_CLICK_STACK4_CHASE_BATTLE_PROMPT_Y:-158}" \
      "${CLASH95_CLICK_STACK4_CHASE_BATTLE_PROMPT_HOLD:-0.22}" \
      "${CLASH95_CLICK_STACK4_CHASE_BATTLE_PROMPT_GAP:-4.0}" \
      "${chase_label}-battle-prompt"
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK4_CHASE_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=1 a=4}" \
      "${chase_label} battle result" \
      "${CLASH95_STACK4_CHASE_BATTLE_RESULT_TIMEOUT:-20}" \
      "$chase_attack_start"
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK4_CHASE_BATTLE_RETURN_PATTERN:-unit_attack_autoresolve_return selected=1 a=4}" \
      "${chase_label} attack return" \
      "${CLASH95_STACK4_CHASE_BATTLE_RETURN_TIMEOUT:-20}" \
      "$chase_attack_start"
  else
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK4_CHASE_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=1 a=4 b=15 c=6}" \
      "${chase_label} next-blocker attack return" \
      "${CLASH95_STACK4_CHASE_ATTACK_RETURN_TIMEOUT:-20}" \
      "$chase_attack_start"
  fi

  if try_wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK4_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=5 a=48 b=14 c=5}" \
    "${CLASH95_STACK4_CHASE_OBJECTIVE_WAIT_SLICE:-3}" \
    "$chase_attack_start"; then
    echo "[smoke] ${chase_label}: stack4 defeated and objective advanced" >>"$log_path"
    break
  fi

  stack4_chase_index=$((stack4_chase_index + 1))
done

if [ "${CLASH95_FIRST_MISSION_STACK5_PROBE:-0}" = "1" ]; then
  stack5_probe_start="$(next_log_line_number)"
  wait_for_fixed_log_pattern \
    "${CLASH95_STACK5_PROBE_OBJECTIVE_PATTERN:-mission_objective_blocked selected=5 a=48 b=14 c=5}" \
    "stack5-probe objective active" \
    "${CLASH95_STACK5_PROBE_OBJECTIVE_TIMEOUT:-10}"

  if [ "${CLASH95_STACK5_PROBE_CLICK_NEXT_UNIT:-1}" = "1" ]; then
    if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_SELECT:-1}" = "1" ]; then
      stack5_select_pattern="${CLASH95_STACK5_PROBE_SELECT_PATTERN:-next_unit_selected selected=10}"
      stack5_select_retry=1
      stack5_select_retries="${CLASH95_STACK5_PROBE_NEXT_UNIT_RETRIES:-3}"
      stack5_select_done=0
      while [ "$stack5_select_retry" -le "$stack5_select_retries" ]; do
        stack5_select_start="$(next_log_line_number)"
        if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_NEXT_UNIT:-1}" = "1" ]; then
          world_script_click_at \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
            "${CLASH95_STACK5_PROBE_NEXT_UNIT_SCRIPT_READS:-32}" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_GAP:-0.70}" \
            "stack5-probe-next-unit-${stack5_select_retry}"
        else
          click_at \
            "$window" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_HOLD:-0.35}" \
            "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_GAP:-0.70}" \
            "stack5-probe-next-unit-${stack5_select_retry}"
        fi
        if try_wait_for_fixed_log_pattern_since \
          "$stack5_select_pattern" \
          "${CLASH95_STACK5_PROBE_SELECT_RETRY_WAIT:-3}" \
          "$stack5_select_start"; then
          echo "[smoke] wait-for-log-since-done: stack5-probe stack selection" >>"$log_path"
          stack5_select_done=1
          break
        fi
        stack5_select_retry=$((stack5_select_retry + 1))
      done
      if [ "$stack5_select_done" != "1" ]; then
        fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern stack5-probe stack selection: $stack5_select_pattern"
      fi
    else
      if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_NEXT_UNIT:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
          "${CLASH95_STACK5_PROBE_NEXT_UNIT_SCRIPT_READS:-32}" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_GAP:-0.70}" \
          "stack5-probe-next-unit"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_HOLD:-0.35}" \
          "${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_GAP:-0.70}" \
          "stack5-probe-next-unit"
      fi
    fi
  fi

  stack5_attack_pattern="${CLASH95_STACK5_PROBE_ATTACK_PATTERN:-enemy_attack_call selected=10 a=5 b=48 c=14}"
  stack5_attack_start="$(next_log_line_number)"
  stack5_attack_detected=0

  if [ "${CLASH95_STACK5_PROBE_CANDIDATE_SWEEP:-1}" = "1" ]; then
    stack5_candidates="${CLASH95_STACK5_PROBE_CANDIDATES:-565,59,0,0,0,491,363,452,391 526,0,0,0,0,448,304,452,391 526,0,0,0,0,448,305,452,391 526,0,9,0.12,0.16,448,343,452,425 526,0,10,0.12,0.16,448,279,452,425 526,0,11,0.12,0.16,448,215,452,425 526,0,12,0.12,0.16,448,151,452,425}"
    stack5_candidate_index=1
    for stack5_candidate in $stack5_candidates; do
      old_ifs="$IFS"
      IFS=,
      set -- $stack5_candidate
      IFS="$old_ifs"

      stack5_candidate_minimap_x="${1:-526}"
      stack5_candidate_minimap_y="${2:-0}"
      stack5_candidate_scroll_count="${3:-0}"
      stack5_candidate_scroll_hold="${4:-0.02}"
      stack5_candidate_scroll_gap="${5:-0.10}"
      stack5_candidate_attack_x="${6:-448}"
      stack5_candidate_attack_y="${7:-368}"
      stack5_candidate_rebase_x="${8:-${CLASH95_MOVE_STACK5_PROBE_REBASE_X:-452}}"
      stack5_candidate_rebase_y="${9:-${CLASH95_MOVE_STACK5_PROBE_REBASE_Y:-391}}"

      if [ "${CLASH95_STACK5_PROBE_REBASE_BEFORE_MINIMAP:-1}" = "1" ] && [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_MINIMAP:-1}" != "1" ]; then
        move_at \
          "$window" \
          "$stack5_candidate_rebase_x" \
          "$stack5_candidate_rebase_y" \
          "${CLASH95_MOVE_STACK5_PROBE_REBASE_GAP:-0.25}" \
          "stack5-probe-candidate-${stack5_candidate_index}-rebase"
      fi

      if [ "${CLASH95_STACK5_PROBE_CLICK_MINIMAP:-1}" = "1" ]; then
        if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_MINIMAP:-1}" = "1" ]; then
          world_script_click_at \
            "$stack5_candidate_minimap_x" \
            "$stack5_candidate_minimap_y" \
            "${CLASH95_STACK5_PROBE_MINIMAP_SCRIPT_READS:-12}" \
            "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_GAP:-0.70}" \
            "stack5-probe-candidate-${stack5_candidate_index}-minimap"
          world_script_wait_reads \
            "${CLASH95_STACK5_PROBE_MINIMAP_SETTLE_READS:-120}" \
            "${CLASH95_STACK5_PROBE_MINIMAP_SETTLE_GAP:-1.0}" \
            "stack5-probe-candidate-${stack5_candidate_index}-minimap-settle"
        else
          click_at \
            "$window" \
            "$stack5_candidate_minimap_x" \
            "$stack5_candidate_minimap_y" \
            "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_HOLD:-0.22}" \
            "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_GAP:-0.70}" \
            "stack5-probe-candidate-${stack5_candidate_index}-minimap"
        fi
      fi

      stack5_scroll_index=1
      while [ "$stack5_scroll_index" -le "$stack5_candidate_scroll_count" ]; do
        hold_key \
          "$window" \
          "${CLASH95_STACK5_PROBE_SCROLL_UP_KEY:-Down}" \
          "$stack5_candidate_scroll_hold" \
          "$stack5_candidate_scroll_gap" \
          "stack5-probe-candidate-${stack5_candidate_index}-scroll-up-${stack5_scroll_index}"
        stack5_scroll_index=$((stack5_scroll_index + 1))
      done

      stack5_candidate_attack_start="$(next_log_line_number)"
      if [ "${CLASH95_STACK5_PROBE_CLICK_ATTACK:-1}" = "1" ]; then
        if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_ATTACK:-1}" = "1" ]; then
          world_script_click_at \
            "$stack5_candidate_attack_x" \
            "$stack5_candidate_attack_y" \
            "${CLASH95_STACK5_PROBE_ATTACK_SCRIPT_READS:-96}" \
            "${CLASH95_CLICK_STACK5_PROBE_ATTACK_GAP:-1.0}" \
            "stack5-probe-candidate-${stack5_candidate_index}-attack"
        else
          click_at \
            "$window" \
            "$stack5_candidate_attack_x" \
            "$stack5_candidate_attack_y" \
            "${CLASH95_CLICK_STACK5_PROBE_ATTACK_HOLD:-0.85}" \
            "${CLASH95_CLICK_STACK5_PROBE_ATTACK_GAP:-1.0}" \
            "stack5-probe-candidate-${stack5_candidate_index}-attack"
        fi
      fi
      if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_ATTACK:-1}" = "1" ]; then
        if try_wait_for_fixed_log_pattern_since \
          "$stack5_attack_pattern" \
          "${CLASH95_STACK5_PROBE_CANDIDATE_WAIT_SLICE:-2}" \
          "$stack5_candidate_attack_start"; then
          echo "[smoke] wait-for-log-since-done: stack5-probe attack candidate ${stack5_candidate_index}" >>"$log_path"
          stack5_attack_start="$stack5_candidate_attack_start"
          stack5_attack_detected=1
          break
        fi
      fi
      stack5_candidate_index=$((stack5_candidate_index + 1))
    done
  else
    if [ "${CLASH95_STACK5_PROBE_REBASE_BEFORE_MINIMAP:-1}" = "1" ] && [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_MINIMAP:-1}" != "1" ]; then
      move_at \
        "$window" \
        "${CLASH95_MOVE_STACK5_PROBE_REBASE_X:-452}" \
        "${CLASH95_MOVE_STACK5_PROBE_REBASE_Y:-391}" \
        "${CLASH95_MOVE_STACK5_PROBE_REBASE_GAP:-0.25}" \
        "stack5-probe-rebase"
    fi

    if [ "${CLASH95_STACK5_PROBE_CLICK_MINIMAP:-1}" = "1" ]; then
      if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_MINIMAP:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_X:-565}" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_Y:-59}" \
          "${CLASH95_STACK5_PROBE_MINIMAP_SCRIPT_READS:-12}" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_GAP:-1.0}" \
          "stack5-probe-minimap"
        world_script_wait_reads \
          "${CLASH95_STACK5_PROBE_MINIMAP_SETTLE_READS:-120}" \
          "${CLASH95_STACK5_PROBE_MINIMAP_SETTLE_GAP:-1.0}" \
          "stack5-probe-minimap-settle"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_X:-565}" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_Y:-59}" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_HOLD:-0.22}" \
          "${CLASH95_CLICK_STACK5_PROBE_MINIMAP_GAP:-1.0}" \
          "stack5-probe-minimap"
      fi
    fi

    if [ "${CLASH95_STACK5_PROBE_SCROLL_UP_COUNT:-0}" != "0" ]; then
      stack5_scroll_index=1
      stack5_scroll_count="${CLASH95_STACK5_PROBE_SCROLL_UP_COUNT:-0}"
      while [ "$stack5_scroll_index" -le "$stack5_scroll_count" ]; do
        hold_key \
          "$window" \
          "${CLASH95_STACK5_PROBE_SCROLL_UP_KEY:-Up}" \
          "${CLASH95_STACK5_PROBE_SCROLL_UP_HOLD:-0.12}" \
          "${CLASH95_STACK5_PROBE_SCROLL_UP_GAP:-0.16}" \
          "stack5-probe-scroll-up-${stack5_scroll_index}"
        stack5_scroll_index=$((stack5_scroll_index + 1))
      done
    fi

    if [ "${CLASH95_STACK5_PROBE_CLICK_ATTACK:-1}" = "1" ]; then
      if [ "${CLASH95_STACK5_PROBE_USE_WORLD_SCRIPT_ATTACK:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_X:-491}" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_Y:-363}" \
          "${CLASH95_STACK5_PROBE_ATTACK_SCRIPT_READS:-96}" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_GAP:-4.0}" \
          "stack5-probe-attack"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_X:-491}" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_Y:-363}" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_HOLD:-1.2}" \
          "${CLASH95_CLICK_STACK5_PROBE_ATTACK_GAP:-4.0}" \
          "stack5-probe-attack"
      fi
    fi
  fi

  if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_ATTACK:-1}" = "1" ]; then
    if [ "$stack5_attack_detected" != "1" ]; then
      wait_for_fixed_log_pattern_since \
        "$stack5_attack_pattern" \
        "stack5-probe attack" \
        "${CLASH95_STACK5_PROBE_ATTACK_TIMEOUT:-20}" \
        "$stack5_attack_start"
    fi
  fi

  if try_wait_for_fixed_log_pattern_since \
    "${CLASH95_STACK5_PROBE_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
    "${CLASH95_STACK5_PROBE_BATTLE_PROMPT_WAIT_SLICE:-2}" \
    "$stack5_attack_start"; then
    if [ "${CLASH95_STACK5_PROBE_CLICK_BATTLE_PROMPT:-1}" = "1" ]; then
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_PROBE_BATTLE_PROMPT_X:-354}" \
        "${CLASH95_CLICK_STACK5_PROBE_BATTLE_PROMPT_Y:-158}" \
        "${CLASH95_CLICK_STACK5_PROBE_BATTLE_PROMPT_HOLD:-0.22}" \
        "${CLASH95_CLICK_STACK5_PROBE_BATTLE_PROMPT_GAP:-4.0}" \
        "stack5-probe-battle-prompt"
    fi
    if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_BATTLE_RESULT:-1}" = "1" ]; then
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_PROBE_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=10 a=5}" \
        "stack5-probe battle result" \
        "${CLASH95_STACK5_PROBE_BATTLE_RESULT_TIMEOUT:-20}" \
        "$stack5_attack_start"
    fi
    if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_ATTACK_RETURN:-1}" = "1" ]; then
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_PROBE_BATTLE_RETURN_PATTERN:-unit_attack_autoresolve_return selected=10 a=5}" \
        "stack5-probe battle return" \
        "${CLASH95_STACK5_PROBE_BATTLE_RETURN_TIMEOUT:-20}" \
        "$stack5_attack_start"
    fi
  elif [ "${CLASH95_STACK5_PROBE_WAIT_FOR_ATTACK_RETURN:-1}" = "1" ]; then
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_PROBE_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=10 a=5 b=48 c=14}" \
      "stack5-probe attack return" \
      "${CLASH95_STACK5_PROBE_ATTACK_RETURN_TIMEOUT:-20}" \
      "$stack5_attack_start"
  fi

  stack5_chase_repeats="${CLASH95_FIRST_MISSION_STACK5_CHASE_REPEATS:-0}"
  stack5_chase_index=1
  while [ "$stack5_chase_index" -le "$stack5_chase_repeats" ]; do
    stack5_chase_label="stack5-chase-${stack5_chase_index}"
    stack5_chase_turn_start="$(next_log_line_number)"
    stack5_chase_normalized_window="${CLASH95_STACK5_CHASE_NORMALIZE_WINDOW:-1}"
    if [ "$stack5_chase_normalized_window" = "1" ]; then
      move_window_to \
        "$window" \
        "${CLASH95_STACK5_CHASE_WINDOW_X:-0}" \
        "${CLASH95_STACK5_CHASE_WINDOW_Y:-0}" \
        "${CLASH95_STACK5_CHASE_WINDOW_MOVE_GAP:-0.35}" \
        "${stack5_chase_label}-window"
    fi

    stack5_chase_turn_retry=1
    stack5_chase_turn_retries="${CLASH95_STACK5_CHASE_END_TURN_RETRIES:-3}"
    stack5_chase_turn_done=0
    while [ "$stack5_chase_turn_retry" -le "$stack5_chase_turn_retries" ]; do
      stack5_chase_turn_click_start="$(next_log_line_number)"
      if [ "${CLASH95_STACK5_CHASE_USE_WORLD_SCRIPT_END_TURN:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
          "${CLASH95_STACK5_CHASE_END_TURN_SCRIPT_READS:-4}" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_GAP:-2.0}" \
          "${stack5_chase_label}-end-turn-${stack5_chase_turn_retry}"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_HOLD:-0.25}" \
          "${CLASH95_CLICK_STACK5_CHASE_END_TURN_GAP:-2.0}" \
          "${stack5_chase_label}-end-turn-${stack5_chase_turn_retry}"
      fi
      if try_wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_CHASE_TURN_ADVANCE_PATTERN:-turn_advance_enter}" \
        "${CLASH95_STACK5_CHASE_END_TURN_RETRY_WAIT:-5}" \
        "$stack5_chase_turn_click_start"; then
        echo "[smoke] wait-for-log-since-done: ${stack5_chase_label} turn advance" >>"$log_path"
        stack5_chase_turn_done=1
        break
      fi
      stack5_chase_turn_retry=$((stack5_chase_turn_retry + 1))
    done
    if [ "$stack5_chase_turn_done" != "1" ]; then
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${stack5_chase_label} turn advance: ${CLASH95_STACK5_CHASE_TURN_ADVANCE_PATTERN:-turn_advance_enter}"
    fi

    stack5_chase_post_skip_count="${CLASH95_STACK5_CHASE_POST_TURN_SKIPS:-2}"
    stack5_chase_post_skip_index=1
    while [ "$stack5_chase_post_skip_index" -le "$stack5_chase_post_skip_count" ]; do
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_CHASE_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
        "${CLASH95_CLICK_STACK5_CHASE_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
        "${CLASH95_CLICK_STACK5_CHASE_POST_SKIP_HOLD:-0.12}" \
        "${CLASH95_CLICK_STACK5_CHASE_POST_SKIP_GAP:-0.8}" \
        "${stack5_chase_label}-post-turn-skip-${stack5_chase_post_skip_index}"
      stack5_chase_post_skip_index=$((stack5_chase_post_skip_index + 1))
    done

    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_CHASE_READY_PATTERN:-after_turn_advance idx=10 owner=0}" \
      "${stack5_chase_label} stack 10 ready" \
      "${CLASH95_STACK5_CHASE_READY_TIMEOUT:-35}" \
      "$stack5_chase_turn_start"

    stack5_chase_default_select_x="${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_X:-452}"
    stack5_chase_default_select_y="${CLASH95_CLICK_STACK5_PROBE_NEXT_UNIT_Y:-344}"
    stack5_chase_default_minimap_x=565
    stack5_chase_default_minimap_y=59
    stack5_chase_default_attack_x=448
    stack5_chase_default_attack_y=304
    if [ "$stack5_chase_normalized_window" = "1" ]; then
      stack5_chase_default_select_x="${CLASH95_CLICK_NEXT_UNIT_X:-496}"
      stack5_chase_default_select_y="${CLASH95_CLICK_NEXT_UNIT_Y:-416}"
      stack5_chase_default_minimap_x=565
      stack5_chase_default_minimap_y=59
      stack5_chase_default_attack_x=491
      stack5_chase_default_attack_y=363
    fi

    stack5_chase_select_pattern="${CLASH95_STACK5_CHASE_SELECT_PATTERN:-next_unit_selected selected=10}"
    stack5_chase_select_retry=1
    stack5_chase_select_retries="${CLASH95_STACK5_CHASE_SELECT_RETRIES:-3}"
    stack5_chase_select_done=0
    while [ "$stack5_chase_select_retry" -le "$stack5_chase_select_retries" ]; do
      stack5_chase_select_start="$(next_log_line_number)"
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_CHASE_SELECT_X:-$stack5_chase_default_select_x}" \
        "${CLASH95_CLICK_STACK5_CHASE_SELECT_Y:-$stack5_chase_default_select_y}" \
        "${CLASH95_CLICK_STACK5_CHASE_SELECT_HOLD:-0.35}" \
        "${CLASH95_CLICK_STACK5_CHASE_SELECT_GAP:-0.70}" \
        "${stack5_chase_label}-select-stack10-${stack5_chase_select_retry}"
      if try_wait_for_fixed_log_pattern_since \
        "$stack5_chase_select_pattern" \
        "${CLASH95_STACK5_CHASE_SELECT_RETRY_WAIT:-3}" \
        "$stack5_chase_select_start"; then
        echo "[smoke] wait-for-log-since-done: ${stack5_chase_label} stack selection" >>"$log_path"
        stack5_chase_select_done=1
        break
      fi
      stack5_chase_select_retry=$((stack5_chase_select_retry + 1))
    done
    if [ "$stack5_chase_select_done" != "1" ]; then
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${stack5_chase_label} stack selection: $stack5_chase_select_pattern"
    fi

    if [ "${CLASH95_STACK5_CHASE_USE_WORLD_SCRIPT_MINIMAP:-1}" = "1" ]; then
      world_script_click_at \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_X:-$stack5_chase_default_minimap_x}" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_Y:-$stack5_chase_default_minimap_y}" \
        "${CLASH95_STACK5_CHASE_MINIMAP_SCRIPT_READS:-12}" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_GAP:-0.70}" \
        "${stack5_chase_label}-minimap-next-blocker"
      world_script_wait_reads \
        "${CLASH95_STACK5_CHASE_MINIMAP_SETTLE_READS:-120}" \
        "${CLASH95_STACK5_CHASE_MINIMAP_SETTLE_GAP:-1.0}" \
        "${stack5_chase_label}-minimap-settle"
    else
      move_at \
        "$window" \
        "${CLASH95_MOVE_STACK5_CHASE_REBASE_X:-452}" \
        "${CLASH95_MOVE_STACK5_CHASE_REBASE_Y:-391}" \
        "${CLASH95_MOVE_STACK5_CHASE_REBASE_GAP:-0.25}" \
        "${stack5_chase_label}-rebase"
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_X:-$stack5_chase_default_minimap_x}" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_Y:-$stack5_chase_default_minimap_y}" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_HOLD:-0.22}" \
        "${CLASH95_CLICK_STACK5_CHASE_MINIMAP_GAP:-0.70}" \
        "${stack5_chase_label}-minimap-next-blocker"
    fi

    stack5_chase_attack_start="$(next_log_line_number)"
    if [ "${CLASH95_STACK5_CHASE_USE_WORLD_SCRIPT_ATTACK:-1}" = "1" ]; then
      world_script_click_at \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_X:-$stack5_chase_default_attack_x}" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_Y:-$stack5_chase_default_attack_y}" \
        "${CLASH95_STACK5_CHASE_ATTACK_SCRIPT_READS:-96}" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_GAP:-1.0}" \
        "${stack5_chase_label}-attack-next-blocker"
    else
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_X:-$stack5_chase_default_attack_x}" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_Y:-$stack5_chase_default_attack_y}" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_HOLD:-0.85}" \
        "${CLASH95_CLICK_STACK5_CHASE_ATTACK_GAP:-1.0}" \
        "${stack5_chase_label}-attack-next-blocker"
    fi
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_CHASE_ATTACK_PATTERN:-enemy_attack_call selected=10 a=5 b=48 c=14}" \
      "${stack5_chase_label} next-blocker attack" \
      "${CLASH95_STACK5_CHASE_ATTACK_TIMEOUT:-20}" \
      "$stack5_chase_attack_start"

    if try_wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_CHASE_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
      "${CLASH95_STACK5_CHASE_BATTLE_PROMPT_WAIT_SLICE:-2}" \
      "$stack5_chase_attack_start"; then
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK5_CHASE_BATTLE_PROMPT_X:-354}" \
        "${CLASH95_CLICK_STACK5_CHASE_BATTLE_PROMPT_Y:-158}" \
        "${CLASH95_CLICK_STACK5_CHASE_BATTLE_PROMPT_HOLD:-0.22}" \
        "${CLASH95_CLICK_STACK5_CHASE_BATTLE_PROMPT_GAP:-4.0}" \
        "${stack5_chase_label}-battle-prompt"
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_CHASE_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=10 a=5}" \
        "${stack5_chase_label} battle result" \
        "${CLASH95_STACK5_CHASE_BATTLE_RESULT_TIMEOUT:-20}" \
        "$stack5_chase_attack_start"
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_CHASE_BATTLE_RETURN_PATTERN:-unit_attack_autoresolve_return selected=10 a=5}" \
        "${stack5_chase_label} attack return" \
        "${CLASH95_STACK5_CHASE_BATTLE_RETURN_TIMEOUT:-20}" \
        "$stack5_chase_attack_start"
    else
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK5_CHASE_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=10 a=5 b=48 c=14}" \
        "${stack5_chase_label} next-blocker attack return" \
        "${CLASH95_STACK5_CHASE_ATTACK_RETURN_TIMEOUT:-20}" \
        "$stack5_chase_attack_start"
    fi

    if try_wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=6 a=35 b=11 c=1}" \
      "${CLASH95_STACK5_CHASE_OBJECTIVE_WAIT_SLICE:-3}" \
      "$stack5_chase_attack_start"; then
      echo "[smoke] ${stack5_chase_label}: stack5 defeated and objective advanced" >>"$log_path"
      break
    fi

    stack5_chase_index=$((stack5_chase_index + 1))
  done

  if [ "${CLASH95_STACK5_PROBE_WAIT_FOR_OBJECTIVE_ADVANCE:-0}" = "1" ]; then
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK5_PROBE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=6 a=35 b=11 c=1}" \
      "stack5-probe objective advance" \
      "${CLASH95_STACK5_PROBE_OBJECTIVE_ADVANCE_TIMEOUT:-20}" \
      "$stack5_probe_start"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_STACK6_CHASE_REPEATS:-0}" -gt 0 ]; then
  stack6_chase_start_pattern="${CLASH95_STACK6_CHASE_START_PATTERN:-mission_objective_blocked selected=6 a=35 b=11 c=1}"
  if ! grep -Fq -- "$stack6_chase_start_pattern" "$log_path"; then
    fail_smoke "first-mission real-input smoke cannot start stack6 chase before objective pattern: $stack6_chase_start_pattern"
  fi

  stack6_chase_start="$(next_log_line_number)"
  stack6_chase_index=1
  stack6_chase_after_manual_return=0
  while [ "$stack6_chase_index" -le "${CLASH95_FIRST_MISSION_STACK6_CHASE_REPEATS:-0}" ]; do
    stack6_chase_label="stack6-chase-${stack6_chase_index}"
    stack6_chase_turn_start="$(next_log_line_number)"

    if [ "${CLASH95_STACK6_CHASE_NORMALIZE_WINDOW:-1}" = "1" ]; then
      move_window_to \
        "$window" \
        "${CLASH95_STACK6_CHASE_WINDOW_X:-0}" \
        "${CLASH95_STACK6_CHASE_WINDOW_Y:-0}" \
        "${CLASH95_STACK6_CHASE_WINDOW_GAP:-0.35}" \
        "${stack6_chase_label}-window"
    fi

    stack6_chase_turn_retry=1
    stack6_chase_turn_retries="${CLASH95_STACK6_CHASE_END_TURN_RETRIES:-2}"
    stack6_chase_turn_done=0
    while [ "$stack6_chase_turn_retry" -le "$stack6_chase_turn_retries" ]; do
      if [ "${CLASH95_STACK6_CHASE_USE_WORLD_SCRIPT_END_TURN:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
          "${CLASH95_STACK6_CHASE_END_TURN_SCRIPT_READS:-4}" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_GAP:-${CLASH95_CLICK_END_TURN_GAP:-2.0}}" \
          "${stack6_chase_label}-end-turn-${stack6_chase_turn_retry}"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_HOLD:-${CLASH95_CLICK_END_TURN_HOLD:-0.25}}" \
          "${CLASH95_CLICK_STACK6_CHASE_END_TURN_GAP:-${CLASH95_CLICK_END_TURN_GAP:-2.0}}" \
          "${stack6_chase_label}-end-turn-${stack6_chase_turn_retry}"
      fi
      if try_wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK6_CHASE_TURN_ADVANCE_PATTERN:-turn_advance_enter}" \
        "${CLASH95_STACK6_CHASE_TURN_ADVANCE_RETRY_WAIT:-4}" \
        "$stack6_chase_turn_start"; then
        echo "[smoke] wait-for-log-since-done: ${stack6_chase_label} turn advance" >>"$log_path"
        stack6_chase_turn_done=1
        break
      fi
      stack6_chase_turn_retry=$((stack6_chase_turn_retry + 1))
    done
    if [ "$stack6_chase_turn_done" != "1" ]; then
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${stack6_chase_label} turn advance: ${CLASH95_STACK6_CHASE_TURN_ADVANCE_PATTERN:-turn_advance_enter}"
    fi

    stack6_chase_post_skip_count="${CLASH95_STACK6_CHASE_POST_TURN_SKIPS:-2}"
    stack6_chase_post_skip_index=1
    while [ "$stack6_chase_post_skip_index" -le "$stack6_chase_post_skip_count" ]; do
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK6_CHASE_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
        "${CLASH95_CLICK_STACK6_CHASE_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
        "${CLASH95_CLICK_STACK6_CHASE_POST_SKIP_HOLD:-0.12}" \
        "${CLASH95_CLICK_STACK6_CHASE_POST_SKIP_GAP:-0.8}" \
        "${stack6_chase_label}-post-turn-skip-${stack6_chase_post_skip_index}"
      stack6_chase_post_skip_index=$((stack6_chase_post_skip_index + 1))
    done

    if try_wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=7 a=49 b=39 c=1}" \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_POST_TURN_WAIT_SLICE:-1}" \
      "$stack6_chase_turn_start"; then
      echo "[smoke] ${stack6_chase_label}: stack6 defeated and objective advanced after turn handoff" >>"$log_path"
      break
    fi

    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_READY_PATTERN:-after_turn_advance idx=10 owner=0}" \
      "${stack6_chase_label} stack 10 ready" \
      "${CLASH95_STACK6_CHASE_READY_TIMEOUT:-35}" \
      "$stack6_chase_turn_start"

    stack6_chase_select_pattern="${CLASH95_STACK6_CHASE_SELECT_PATTERN:-next_unit_selected selected=10}"
    stack6_chase_select_mode="${CLASH95_STACK6_CHASE_SELECT_MODE:-next-unit}"
    if [ "${CLASH95_STACK6_CHASE_DIRECT_SELECT_AFTER_MANUAL_RETURN:-0}" = "1" ] && \
      [ "$stack6_chase_after_manual_return" = "1" ]; then
      stack6_chase_select_mode="world-tile"
    fi
    if [ "$stack6_chase_select_mode" = "world-tile" ]; then
      stack6_chase_direct_select_start="$(next_log_line_number)"
      if [ "${CLASH95_STACK6_CHASE_USE_WORLD_SCRIPT_DIRECT_SELECT:-1}" = "1" ]; then
        world_script_click_at \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_X:-512}" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_Y:-304}" \
          "${CLASH95_STACK6_CHASE_DIRECT_SELECT_SCRIPT_READS:-48}" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_GAP:-0.80}" \
          "${stack6_chase_label}-direct-select-stack10"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_X:-512}" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_Y:-304}" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_HOLD:-0.22}" \
          "${CLASH95_CLICK_STACK6_CHASE_DIRECT_SELECT_GAP:-0.80}" \
          "${stack6_chase_label}-direct-select-stack10"
      fi
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK6_CHASE_DIRECT_SELECT_PATTERN:-status_panel_refresh_done selected=10}" \
        "${stack6_chase_label} direct stack10 selection" \
        "${CLASH95_STACK6_CHASE_DIRECT_SELECT_TIMEOUT:-12}" \
        "$stack6_chase_direct_select_start"
      echo "[smoke] wait-for-log-since-done: ${stack6_chase_label} direct stack selection" >>"$log_path"
    else
      stack6_chase_select_retry=1
      stack6_chase_select_retries="${CLASH95_STACK6_CHASE_SELECT_RETRIES:-3}"
      stack6_chase_select_done=0
      while [ "$stack6_chase_select_retry" -le "$stack6_chase_select_retries" ]; do
        stack6_chase_select_start="$(next_log_line_number)"
        click_at \
          "$window" \
          "${CLASH95_CLICK_STACK6_CHASE_SELECT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
          "${CLASH95_CLICK_STACK6_CHASE_SELECT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
          "${CLASH95_CLICK_STACK6_CHASE_SELECT_HOLD:-0.35}" \
          "${CLASH95_CLICK_STACK6_CHASE_SELECT_GAP:-0.70}" \
          "${stack6_chase_label}-select-stack10-${stack6_chase_select_retry}"
        if try_wait_for_fixed_log_pattern_since \
          "$stack6_chase_select_pattern" \
          "${CLASH95_STACK6_CHASE_SELECT_RETRY_WAIT:-3}" \
          "$stack6_chase_select_start"; then
          echo "[smoke] wait-for-log-since-done: ${stack6_chase_label} stack selection" >>"$log_path"
          stack6_chase_select_done=1
          break
        fi
        stack6_chase_select_retry=$((stack6_chase_select_retry + 1))
      done
      if [ "$stack6_chase_select_done" != "1" ]; then
        fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${stack6_chase_label} stack selection: $stack6_chase_select_pattern"
      fi
    fi

    if [ "${CLASH95_STACK6_CHASE_USE_WORLD_SCRIPT_MINIMAP:-1}" = "1" ]; then
      world_script_click_at \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_X:-513}" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_Y:-47}" \
        "${CLASH95_STACK6_CHASE_MINIMAP_SCRIPT_READS:-12}" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_GAP:-0.70}" \
        "${stack6_chase_label}-minimap-next-blocker"
      world_script_wait_reads \
        "${CLASH95_STACK6_CHASE_MINIMAP_SETTLE_READS:-120}" \
        "${CLASH95_STACK6_CHASE_MINIMAP_SETTLE_GAP:-1.0}" \
        "${stack6_chase_label}-minimap-settle"
    else
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_X:-513}" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_Y:-47}" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_HOLD:-0.22}" \
        "${CLASH95_CLICK_STACK6_CHASE_MINIMAP_GAP:-0.70}" \
        "${stack6_chase_label}-minimap-next-blocker"
    fi

    stack6_chase_attack_start="$(next_log_line_number)"
    if [ "${CLASH95_STACK6_CHASE_USE_WORLD_SCRIPT_ATTACK:-1}" = "1" ]; then
      world_script_click_at \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_X:-480}" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_Y:-336}" \
        "${CLASH95_STACK6_CHASE_ATTACK_SCRIPT_READS:-96}" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_GAP:-1.0}" \
        "${stack6_chase_label}-attack-next-blocker"
    else
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_X:-480}" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_Y:-336}" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_HOLD:-0.85}" \
        "${CLASH95_CLICK_STACK6_CHASE_ATTACK_GAP:-1.0}" \
        "${stack6_chase_label}-attack-next-blocker"
    fi
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_ATTACK_PATTERN:-enemy_attack_call selected=10 a=6 b=35 c=11}" \
      "${stack6_chase_label} next-blocker attack" \
      "${CLASH95_STACK6_CHASE_ATTACK_TIMEOUT:-20}" \
      "$stack6_chase_attack_start"

    if try_wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}" \
      "${CLASH95_STACK6_CHASE_BATTLE_PROMPT_WAIT_SLICE:-2}" \
      "$stack6_chase_attack_start"; then
      stack6_chase_battle_prompt_x="${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_X:-354}"
      stack6_chase_battle_prompt_y="${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_Y:-158}"
      if [ "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_MILESTONE:-0}" = "1" ]; then
        stack6_chase_battle_prompt_x="${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_X:-${CLASH95_CLICK_STACK6_CHASE_MANUAL_BATTLE_PROMPT_X:-276}}"
        stack6_chase_battle_prompt_y="${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_Y:-${CLASH95_CLICK_STACK6_CHASE_MANUAL_BATTLE_PROMPT_Y:-158}}"
      fi
      click_at \
        "$window" \
        "$stack6_chase_battle_prompt_x" \
        "$stack6_chase_battle_prompt_y" \
        "${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_HOLD:-0.22}" \
        "${CLASH95_CLICK_STACK6_CHASE_BATTLE_PROMPT_GAP:-4.0}" \
        "${stack6_chase_label}-battle-prompt"
      if [ "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_MILESTONE:-0}" = "1" ]; then
        wait_for_fixed_log_pattern_since \
          "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_PATTERN:-battle_turn_loop_after_input_widgets}" \
          "${stack6_chase_label} manual battle input loop" \
          "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_TIMEOUT:-30}" \
          "$stack6_chase_attack_start"
        echo "[smoke] ${stack6_chase_label}: manual battle input loop reached" >>"$log_path"
        if [ "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE:-}" ]; then
          if [ ! -f "$CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE" ]; then
            fail_smoke "first-mission real-input smoke stack6 manual battle script file does not exist: $CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE"
          fi
          echo "[smoke] ${stack6_chase_label}: append manual battle script file ${CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE}" >>"$log_path"
          : >"$battle_input_script"
          cat "$CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE" >>"$battle_input_script"
          sleep "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_GAP:-1.0}"
        fi
        if [ "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT:-}" ]; then
          echo "[smoke] ${stack6_chase_label}: append manual battle script from env" >>"$log_path"
          : >"$battle_input_script"
          printf '%b\n' "$CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT" >>"$battle_input_script"
          sleep "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_GAP:-1.0}"
        fi
        if [ "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_EXPECT_PATTERN:-}" ]; then
          wait_for_fixed_log_pattern_since \
            "$CLASH95_STACK6_CHASE_MANUAL_BATTLE_EXPECT_PATTERN" \
            "${stack6_chase_label} manual battle script result" \
            "${CLASH95_STACK6_CHASE_MANUAL_BATTLE_EXPECT_TIMEOUT:-20}" \
            "$stack6_chase_attack_start"
        fi
        stack6_tactical_sequence="${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE:-}"
        if [ "${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE:-}" ]; then
          if [ ! -f "$CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE" ]; then
            fail_smoke "first-mission real-input smoke stack6 tactical sequence file does not exist: $CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE"
          fi
          stack6_tactical_sequence="$(
            while IFS= read -r stack6_tactical_sequence_line; do
              stack6_tactical_sequence_line="${stack6_tactical_sequence_line#"${stack6_tactical_sequence_line%%[![:space:]]*}"}"
              stack6_tactical_sequence_line="${stack6_tactical_sequence_line%"${stack6_tactical_sequence_line##*[![:space:]]}"}"
              case "$stack6_tactical_sequence_line" in
                ""|\#*) continue ;;
              esac
              printf '%s\n' "$stack6_tactical_sequence_line"
            done <"$CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE"
          )"
        fi
        if [ "$stack6_tactical_sequence" ]; then
          old_ifs="$IFS"
          for stack6_tactical_step in $stack6_tactical_sequence; do
            IFS=,
            set -- $stack6_tactical_step
            IFS="$old_ifs"

            stack6_tactical_label="${1:-step}"
            stack6_tactical_x="${2:-0}"
            stack6_tactical_y="${3:-0}"
            stack6_tactical_pattern="${4:-}"
            stack6_tactical_timeout="${5:-12}"
            stack6_tactical_hold="${6:-0.22}"
            stack6_tactical_gap="${7:-1.0}"
            if [ "$stack6_tactical_label" = "wait" ]; then
              battle_script_wait_reads \
                "${2:-8}" \
                "${3:-0.40}" \
                "${stack6_chase_label}-tactical-wait"
              continue
            fi
            if [ "$stack6_tactical_label" = "key" ]; then
              stack6_tactical_start="$(next_log_line_number)"
              battle_script_key_pulse \
                "${2:-0}" \
                "${3:-4}" \
                "${6:-0.40}" \
                "${stack6_chase_label}-tactical-key-${2:-0}"
              stack6_tactical_pattern="${4:-}"
              if [ -n "$stack6_tactical_pattern" ] && [ "$stack6_tactical_pattern" != "-" ]; then
                wait_for_fixed_log_pattern_since \
                  "$stack6_tactical_pattern" \
                  "${stack6_chase_label} tactical key ${2:-0}" \
                  "${5:-12}" \
                  "$stack6_tactical_start"
              fi
              continue
            fi
            if [ "$stack6_tactical_label" = "battle-click" ]; then
              stack6_tactical_start="$(next_log_line_number)"
              battle_script_click_at \
                "${2:-0}" \
                "${3:-0}" \
                "${6:-4}" \
                "${7:-1.0}" \
                "${stack6_chase_label}-tactical-battle-click"
              stack6_tactical_pattern="${4:-}"
              if [ -n "$stack6_tactical_pattern" ] && [ "$stack6_tactical_pattern" != "-" ]; then
                wait_for_fixed_log_pattern_since \
                  "$stack6_tactical_pattern" \
                  "${stack6_chase_label} tactical battle-click" \
                  "${5:-12}" \
                  "$stack6_tactical_start"
              fi
              continue
            fi
            if [ "$stack6_tactical_label" = "pulse" ]; then
              stack6_tactical_start="$(next_log_line_number)"
              battle_script_pulse \
                "${2:-0}" \
                "${3:-0}" \
                "${6:-1}" \
                "${7:-0}" \
                "${8:-4}" \
                "${9:-0.40}" \
                "${stack6_chase_label}-tactical-pulse"
              stack6_tactical_pattern="${4:-}"
              if [ -n "$stack6_tactical_pattern" ] && [ "$stack6_tactical_pattern" != "-" ]; then
                wait_for_fixed_log_pattern_since \
                  "$stack6_tactical_pattern" \
                  "${stack6_chase_label} tactical pulse" \
                  "${5:-12}" \
                  "$stack6_tactical_start"
              fi
              continue
            fi
            case "$stack6_tactical_label" in
              next-unit)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_X:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_X:-577}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_Y:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_Y:-386}}}"
                stack6_tactical_pattern="${4:-battle_action_next_unit_selected}"
                ;;
              defence)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_X:-${CLASH95_CLICK_TACTICAL_DEFENCE_X:-514}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_Y:-${CLASH95_CLICK_TACTICAL_DEFENCE_Y:-448}}}"
                stack6_tactical_pattern="${4:-battle_action_prepare_defence_done}"
                ;;
              shoot)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_SHOOT_X:-${CLASH95_CLICK_TACTICAL_SHOOT_X:-514}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_SHOOT_Y:-${CLASH95_CLICK_TACTICAL_SHOOT_Y:-386}}}"
                stack6_tactical_pattern="${4:-battle_action_shoot_toggle_done}"
                ;;
              charge)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_CHARGE_X:-${CLASH95_CLICK_TACTICAL_CHARGE_X:-514}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_CHARGE_Y:-${CLASH95_CLICK_TACTICAL_CHARGE_Y:-417}}}"
                stack6_tactical_pattern="${4:-battle_action_charge_toggle_done}"
                ;;
              retreat)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_RETREAT_X:-${CLASH95_CLICK_TACTICAL_RETREAT_X:-577}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_RETREAT_Y:-${CLASH95_CLICK_TACTICAL_RETREAT_Y:-417}}}"
                stack6_tactical_pattern="${4:--}"
                ;;
              exit)
                stack6_tactical_x="${2:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_X:-${CLASH95_CLICK_TACTICAL_EXIT_X:-520}}}"
                stack6_tactical_y="${3:-${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_Y:-${CLASH95_CLICK_TACTICAL_EXIT_Y:-14}}}"
                stack6_tactical_pattern="${4:-battle_action_loop_exit_requested}"
                ;;
            esac
            stack6_tactical_start="$(next_log_line_number)"

            tactical_click_at \
              "$window" \
              "$stack6_tactical_x" \
              "$stack6_tactical_y" \
              "$stack6_tactical_hold" \
              "$stack6_tactical_gap" \
              "${stack6_chase_label}-tactical-${stack6_tactical_label}"
            if [ -n "$stack6_tactical_pattern" ] && [ "$stack6_tactical_pattern" != "-" ]; then
              wait_for_fixed_log_pattern_since \
                "$stack6_tactical_pattern" \
                "${stack6_chase_label} tactical ${stack6_tactical_label}" \
                "$stack6_tactical_timeout" \
                "$stack6_tactical_start"
            fi
          done
          IFS="$old_ifs"
          echo "[smoke] ${stack6_chase_label}: manual tactical sequence reached" >>"$log_path"
        fi
        if [ "${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_PATTERN:-}" ]; then
          wait_for_fixed_log_pattern_since \
            "$CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_PATTERN" \
            "${stack6_chase_label} manual tactical sequence result" \
            "${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_TIMEOUT:-20}" \
            "$stack6_chase_attack_start"
        fi
        if [ "${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_ACTION:-0}" = "1" ]; then
          stack6_tactical_start="$(next_log_line_number)"
          tactical_click_at \
            "$window" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_X:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_X:-577}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_Y:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_Y:-386}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_HOLD:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_HOLD:-0.22}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_NEXT_UNIT_GAP:-${CLASH95_CLICK_TACTICAL_NEXT_UNIT_GAP:-1.0}}" \
            "${stack6_chase_label}-tactical-next-unit"
          wait_for_fixed_log_pattern_since \
            "${CLASH95_STACK6_CHASE_TACTICAL_NEXT_UNIT_PATTERN:-battle_action_next_unit_selected}" \
            "${stack6_chase_label} tactical next unit" \
            "${CLASH95_STACK6_CHASE_TACTICAL_NEXT_UNIT_TIMEOUT:-12}" \
            "$stack6_tactical_start"

          stack6_tactical_start="$(next_log_line_number)"
          tactical_click_at \
            "$window" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_X:-${CLASH95_CLICK_TACTICAL_DEFENCE_X:-514}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_Y:-${CLASH95_CLICK_TACTICAL_DEFENCE_Y:-448}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_HOLD:-${CLASH95_CLICK_TACTICAL_DEFENCE_HOLD:-0.22}}" \
            "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_DEFENCE_GAP:-${CLASH95_CLICK_TACTICAL_DEFENCE_GAP:-1.0}}" \
            "${stack6_chase_label}-tactical-defence"
          wait_for_fixed_log_pattern_since \
            "${CLASH95_STACK6_CHASE_TACTICAL_DEFENCE_PATTERN:-battle_action_prepare_defence_done}" \
            "${stack6_chase_label} tactical prepare defence" \
            "${CLASH95_STACK6_CHASE_TACTICAL_DEFENCE_TIMEOUT:-12}" \
            "$stack6_tactical_start"

          if [ "${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_EXIT:-0}" = "1" ]; then
            stack6_tactical_start="$(next_log_line_number)"
            tactical_click_at \
              "$window" \
              "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_X:-${CLASH95_CLICK_TACTICAL_EXIT_X:-520}}" \
              "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_Y:-${CLASH95_CLICK_TACTICAL_EXIT_Y:-14}}" \
              "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_HOLD:-${CLASH95_CLICK_TACTICAL_EXIT_HOLD:-0.22}}" \
              "${CLASH95_CLICK_STACK6_CHASE_TACTICAL_EXIT_GAP:-${CLASH95_CLICK_TACTICAL_EXIT_GAP:-1.0}}" \
              "${stack6_chase_label}-tactical-exit"
            wait_for_fixed_log_pattern_since \
              "${CLASH95_STACK6_CHASE_TACTICAL_EXIT_PATTERN:-battle_action_loop_exit_requested}" \
              "${stack6_chase_label} tactical exit" \
              "${CLASH95_STACK6_CHASE_TACTICAL_EXIT_TIMEOUT:-12}" \
              "$stack6_tactical_start"
          fi
          echo "[smoke] ${stack6_chase_label}: manual tactical action sequence reached" >>"$log_path"
        fi
        if [ "${CLASH95_STACK6_CHASE_CONTINUE_AFTER_MANUAL_BATTLE:-0}" != "1" ]; then
          break
        fi
        if try_wait_for_fixed_log_pattern_since \
          "${CLASH95_STACK6_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=7 a=49 b=39 c=1}" \
          "${CLASH95_STACK6_CHASE_OBJECTIVE_WAIT_SLICE:-3}" \
          "$stack6_chase_attack_start"; then
          echo "[smoke] ${stack6_chase_label}: stack6 defeated and objective advanced" >>"$log_path"
          break
        fi
        stack6_chase_after_manual_return=1
        stack6_chase_index=$((stack6_chase_index + 1))
        continue
      fi
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK6_CHASE_BATTLE_RESULT_PATTERN:-unit_attack_autoresolve_done selected=10 a=6}" \
        "${stack6_chase_label} battle result" \
        "${CLASH95_STACK6_CHASE_BATTLE_RESULT_TIMEOUT:-20}" \
        "$stack6_chase_attack_start"
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK6_CHASE_BATTLE_RETURN_PATTERN:-unit_attack_autoresolve_return selected=10 a=6}" \
        "${stack6_chase_label} attack return" \
        "${CLASH95_STACK6_CHASE_BATTLE_RETURN_TIMEOUT:-20}" \
        "$stack6_chase_attack_start"
    else
      wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK6_CHASE_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=10 a=6 b=35 c=11}" \
        "${stack6_chase_label} next-blocker attack return" \
        "${CLASH95_STACK6_CHASE_ATTACK_RETURN_TIMEOUT:-20}" \
        "$stack6_chase_attack_start"
    fi

    if try_wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=7 a=49 b=39 c=1}" \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_WAIT_SLICE:-3}" \
      "$stack6_chase_attack_start"; then
      echo "[smoke] ${stack6_chase_label}: stack6 defeated and objective advanced" >>"$log_path"
      break
    fi

    stack6_chase_index=$((stack6_chase_index + 1))
  done

  if [ "${CLASH95_STACK6_CHASE_WAIT_FOR_OBJECTIVE_ADVANCE:-0}" = "1" ]; then
    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=7 a=49 b=39 c=1}" \
      "stack6-chase objective advance" \
      "${CLASH95_STACK6_CHASE_OBJECTIVE_ADVANCE_TIMEOUT:-20}" \
      "$stack6_chase_start"
  fi
fi

run_stack10_world_blocker_chase() {
  local chase_name="$1"
  local target_index="$2"
  local target_x="$3"
  local target_y="$4"
  local minimap_x="$5"
  local minimap_y="$6"
  local attack_x="$7"
  local attack_y="$8"
  local objective_pattern="$9"
  local repeats="${10}"
  local direct_first="${11:-0}"
  local chaser_index="${12:-${CLASH95_STACK10_BLOCKER_CHASE_CHASER_INDEX:-10}}"
  local chase_index=1
  local used_direct_select=0

  while [ "$chase_index" -le "$repeats" ]; do
    local chase_label="${chase_name}-${chase_index}"
    local chase_turn_start
    chase_turn_start="$(next_log_line_number)"

    move_window_to \
      "$window" \
      "${CLASH95_STACK10_BLOCKER_CHASE_WINDOW_X:-0}" \
      "${CLASH95_STACK10_BLOCKER_CHASE_WINDOW_Y:-0}" \
      "${CLASH95_STACK10_BLOCKER_CHASE_WINDOW_GAP:-0.35}" \
      "${chase_label}-window"

    local chase_turn_retry=1
    local chase_turn_retries="${CLASH95_STACK10_BLOCKER_CHASE_END_TURN_RETRIES:-3}"
    local chase_turn_done=0
    while [ "$chase_turn_retry" -le "$chase_turn_retries" ]; do
      local chase_turn_click_start
      chase_turn_click_start="$(next_log_line_number)"
      world_script_click_at \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_END_TURN_X:-${CLASH95_CLICK_END_TURN_X:-500}}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_END_TURN_Y:-${CLASH95_CLICK_END_TURN_Y:-2}}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_END_TURN_SCRIPT_READS:-4}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_END_TURN_GAP:-2.0}" \
        "${chase_label}-end-turn-${chase_turn_retry}"
      if try_wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK10_BLOCKER_CHASE_TURN_ADVANCE_PATTERN:-turn_advance_enter}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_END_TURN_RETRY_WAIT:-5}" \
        "$chase_turn_click_start"; then
        echo "[smoke] wait-for-log-since-done: ${chase_label} turn advance" >>"$log_path"
        chase_turn_done=1
        break
      fi
      chase_turn_retry=$((chase_turn_retry + 1))
    done
    if [ "$chase_turn_done" != "1" ]; then
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${chase_label} turn advance"
    fi

    local chase_post_skip_index=1
    local chase_post_skip_count="${CLASH95_STACK10_BLOCKER_CHASE_POST_TURN_SKIPS:-2}"
    while [ "$chase_post_skip_index" -le "$chase_post_skip_count" ]; do
      click_at \
        "$window" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_POST_SKIP_X:-${CLASH95_CLICK_POST_END_TURN_SKIP_X:-${CLASH95_CLICK_SKIP_X:-320}}}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_POST_SKIP_Y:-${CLASH95_CLICK_POST_END_TURN_SKIP_Y:-${CLASH95_CLICK_SKIP_Y:-240}}}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_POST_SKIP_HOLD:-0.12}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_POST_SKIP_GAP:-0.8}" \
        "${chase_label}-post-turn-skip-${chase_post_skip_index}"
      chase_post_skip_index=$((chase_post_skip_index + 1))
    done

    if [ "${CLASH95_HANDLE_QUEEN_PROPOSAL_DIALOG:-1}" = "1" ] \
      && try_wait_for_fixed_log_pattern_since \
        "${CLASH95_QUEEN_PROPOSAL_READY_PATTERN:-queen_dialog_after_present}" \
        "${CLASH95_QUEEN_PROPOSAL_READY_WAIT_SLICE:-1}" \
        "$chase_turn_start"; then
      local queen_click_start
      queen_click_start="$(next_log_line_number)"
      if [ "${CLASH95_QUEEN_PROPOSAL_USE_PLATFORM_PULSE:-1}" = "1" ]; then
        platform_script_pulse \
          "${CLASH95_QUEEN_PROPOSAL_PULSE_DX:-365}" \
          "${CLASH95_QUEEN_PROPOSAL_PULSE_DY:--113}" \
          1 \
          0 \
          "${CLASH95_QUEEN_PROPOSAL_SCRIPT_READS:-6}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_GAP:-1.0}" \
          "${chase_label}-queen-proposal"
      elif [ "${CLASH95_QUEEN_PROPOSAL_USE_PLATFORM_SCRIPT:-1}" = "1" ]; then
        platform_script_click_at \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_X:-528}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_Y:-339}" \
          "${CLASH95_QUEEN_PROPOSAL_SCRIPT_READS:-6}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_GAP:-1.0}" \
          "${chase_label}-queen-proposal"
      else
        click_at \
          "$window" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_X:-528}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_Y:-339}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_HOLD:-0.30}" \
          "${CLASH95_CLICK_QUEEN_PROPOSAL_GAP:-1.0}" \
          "${chase_label}-queen-proposal"
      fi
      wait_for_fixed_log_pattern_since \
        "${CLASH95_QUEEN_PROPOSAL_RETURN_PATTERN:-queen_proposal_dialog_return}" \
        "${chase_label} queen proposal return" \
        "${CLASH95_QUEEN_PROPOSAL_RETURN_TIMEOUT:-20}" \
        "$queen_click_start"
    fi

    if try_wait_for_fixed_log_pattern_since \
      "$objective_pattern" \
      "${CLASH95_STACK10_BLOCKER_CHASE_OBJECTIVE_POST_TURN_WAIT_SLICE:-1}" \
      "$chase_turn_start"; then
      echo "[smoke] ${chase_label}: blocker ${target_index} defeated and objective advanced after turn handoff" >>"$log_path"
      return 0
    fi

    wait_for_fixed_log_pattern_since \
      "${CLASH95_STACK10_BLOCKER_CHASE_READY_PATTERN:-after_turn_advance idx=${chaser_index} owner=0}" \
      "${chase_label} stack ${chaser_index} ready" \
      "${CLASH95_STACK10_BLOCKER_CHASE_READY_TIMEOUT:-35}" \
      "$chase_turn_start"

    local chaser_ready_ap
    local chaser_ready_path
    chaser_ready_ap="$(latest_stack_ap_since "$chase_turn_start" "$chaser_index")"
    chaser_ready_path="$(latest_stack_path_since "$chase_turn_start" "$chaser_index")"
    if [ "${CLASH95_STACK10_BLOCKER_CHASE_SKIP_ZERO_AP:-1}" = "1" ] \
      && [ "${chaser_ready_ap:-}" = "0" ]; then
      echo "[smoke] ${chase_label}: stack${chaser_index} has ap=0 path=${chaser_ready_path:-unknown}; resting until a later turn can act" >>"$log_path"
      chase_index=$((chase_index + 1))
      continue
    fi
    if [ "${CLASH95_STACK10_BLOCKER_CHASE_SKIP_ZERO_AP_QUEUED_PATH:-1}" = "1" ] \
      && [ "${chaser_ready_ap:-}" = "0" ] \
      && [ -n "${chaser_ready_path:-}" ] \
      && [ "$chaser_ready_path" != "0" ]; then
      echo "[smoke] ${chase_label}: stack${chaser_index} has ap=0 path=${chaser_ready_path}; skipping selector until a later turn can continue queued path" >>"$log_path"
      chase_index=$((chase_index + 1))
      continue
    fi

    local chaser_already_selected=0
    if [ "${CLASH95_STACK10_BLOCKER_CHASE_SKIP_SELECT_IF_ALREADY_SELECTED:-0}" = "1" ]; then
      if log_has_fixed_pattern_since \
        "${CLASH95_STACK10_BLOCKER_CHASE_ALREADY_SELECTED_PATTERN:-unit_new_turn_stack selected=${chaser_index}}" \
        "$chase_turn_start"; then
        chaser_already_selected=1
      elif [ -n "${CLASH95_STACK10_BLOCKER_CHASE_ALREADY_SELECTED_ALT_PATTERN:-human_turn_enter idx=${chaser_index}}" ] \
        && log_has_fixed_pattern_since \
          "${CLASH95_STACK10_BLOCKER_CHASE_ALREADY_SELECTED_ALT_PATTERN:-human_turn_enter idx=${chaser_index}}" \
          "$chase_turn_start"; then
        chaser_already_selected=1
      fi
    fi

    local chaser_selected=0
    if [ "$chaser_already_selected" = "1" ]; then
      echo "[smoke] ${chase_label}: stack ${chaser_index} already selected after turn handoff; skipping selector click" >>"$log_path"
      chaser_selected=1
    elif [ "$direct_first" = "1" ] && { [ "$used_direct_select" = "0" ] || [ "${CLASH95_STACK10_BLOCKER_CHASE_DIRECT_SELECT_EACH_REPEAT:-0}" = "1" ]; }; then
      local direct_select_start
      direct_select_start="$(next_log_line_number)"
      world_script_click_at \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_DIRECT_SELECT_X:-512}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_DIRECT_SELECT_Y:-304}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_DIRECT_SELECT_SCRIPT_READS:-48}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_DIRECT_SELECT_GAP:-0.80}" \
        "${chase_label}-direct-select-stack${chaser_index}"
      used_direct_select=1
      echo "[smoke] wait-for-log-since: ${chase_label} direct stack${chaser_index} selection timeout=${CLASH95_STACK10_BLOCKER_CHASE_DIRECT_SELECT_TIMEOUT:-12}s start=${direct_select_start}" >>"$log_path"
      if try_wait_for_fixed_log_pattern_since \
        "${CLASH95_STACK10_BLOCKER_CHASE_DIRECT_SELECT_PATTERN:-status_panel_refresh_done selected=${chaser_index}}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_DIRECT_SELECT_TIMEOUT:-12}" \
        "$direct_select_start"; then
        echo "[smoke] wait-for-log-since-done: ${chase_label} direct stack${chaser_index} selection" >>"$log_path"
        chaser_selected=1
      else
        echo "[smoke] ${chase_label}: direct stack${chaser_index} selection did not prove selected=${chaser_index}; falling back to next-unit selector" >>"$log_path"
      fi
    fi

    if [ "$chaser_selected" != "1" ]; then
      local select_retry=1
      local select_retries="${CLASH95_STACK10_BLOCKER_CHASE_SELECT_RETRIES:-4}"
      local select_done=0
      while [ "$select_retry" -le "$select_retries" ]; do
        local select_start
        local select_pattern
        local select_alt_pattern
        select_start="$(next_log_line_number)"
        select_pattern="${CLASH95_STACK10_BLOCKER_CHASE_SELECT_PATTERN:-next_unit_selected selected=${chaser_index}}"
        select_alt_pattern="${CLASH95_STACK10_BLOCKER_CHASE_SELECT_ALT_PATTERN:-status_panel_refresh_done selected=${chaser_index}}"
        if [ "${CLASH95_STACK10_BLOCKER_CHASE_USE_WORLD_SCRIPT_SELECT:-1}" = "1" ]; then
          world_script_click_at \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
            "${CLASH95_STACK10_BLOCKER_CHASE_SELECT_SCRIPT_READS:-32}" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_GAP:-0.70}" \
            "${chase_label}-select-stack${chaser_index}-${select_retry}"
        else
          click_at \
            "$window" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_X:-${CLASH95_CLICK_NEXT_UNIT_X:-496}}" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_Y:-${CLASH95_CLICK_NEXT_UNIT_Y:-416}}" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_HOLD:-0.35}" \
            "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_SELECT_GAP:-0.70}" \
            "${chase_label}-select-stack${chaser_index}-${select_retry}"
        fi
        if try_wait_for_fixed_log_pattern_since \
          "$select_pattern" \
          "${CLASH95_STACK10_BLOCKER_CHASE_SELECT_RETRY_WAIT:-3}" \
          "$select_start"; then
          echo "[smoke] wait-for-log-since-done: ${chase_label} stack selection" >>"$log_path"
          select_done=1
          break
        fi
        if [ -n "$select_alt_pattern" ] && log_has_fixed_pattern_since "$select_alt_pattern" "$select_start"; then
          echo "[smoke] wait-for-log-since-done: ${chase_label} stack selection alternate" >>"$log_path"
          select_done=1
          break
        fi
        select_retry=$((select_retry + 1))
      done
      if [ "$select_done" != "1" ]; then
        fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${chase_label} stack selection"
      fi
    fi

    if [ "${CLASH95_STACK10_BLOCKER_CHASE_POST_SELECT_SETTLE_READS:-8}" -gt 0 ]; then
      world_script_wait_reads \
        "${CLASH95_STACK10_BLOCKER_CHASE_POST_SELECT_SETTLE_READS:-8}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_POST_SELECT_SETTLE_GAP:-0.25}" \
        "${chase_label}-post-select-settle"
    fi

    local queued_path_count
    queued_path_count="$(latest_stack_path_since "$chase_turn_start" "$chaser_index")"
    if [ "$(blocker_chase_env_value "$target_index" "CONTINUE_QUEUED_PATH" "0")" = "1" ] \
      && [ -n "$queued_path_count" ] \
      && [ "$queued_path_count" != "0" ]; then
      local continue_start
      continue_start="$(next_log_line_number)"
      echo "[smoke] ${chase_label}: continue queued path count=${queued_path_count}" >>"$log_path"
      world_script_click_at \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_CONTINUE_X:-384}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_CONTINUE_Y:-208}" \
        "${CLASH95_STACK10_BLOCKER_CHASE_CONTINUE_SCRIPT_READS:-96}" \
        "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_CONTINUE_GAP:-2.5}" \
        "${chase_label}-continue-queued-path"
      local continue_pattern
      local continue_timeout
      continue_pattern="$(blocker_chase_env_value "$target_index" "CONTINUE_PATTERN" "unit_move_after_path_state selected=${chaser_index}")"
      continue_timeout="$(blocker_chase_env_value "$target_index" "CONTINUE_TIMEOUT" "25")"
      local continue_wait_start_seconds="$SECONDS"
      local continue_outcome=""

      echo "[smoke] wait-for-log-since: ${chase_label} queued path continuation timeout=${continue_timeout}s start=${continue_start}" >>"$log_path"
      while [ $((SECONDS - continue_wait_start_seconds)) -lt "$continue_timeout" ]; do
        if log_has_fixed_pattern_since "$objective_pattern" "$continue_start"; then
          continue_outcome="objective"
          break
        fi
        if log_has_fixed_pattern_since "$continue_pattern" "$continue_start"; then
          continue_outcome="move"
          break
        fi
        if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
          fail_smoke "first-mission real-input smoke process exited while waiting for fresh log pattern ${chase_label} queued path continuation"
        fi
        sleep 0.1
      done
      if [ "$continue_outcome" = "objective" ]; then
        echo "[smoke] ${chase_label}: blocker ${target_index} defeated and objective advanced during queued path continuation" >>"$log_path"
        return 0
      fi
      if [ "$continue_outcome" != "move" ]; then
        if [ "$(blocker_chase_env_value "$target_index" "REQUIRE_CONTINUE_MOVE" "0")" = "1" ]; then
          fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${chase_label} queued path continuation: ${continue_pattern}"
        fi
        echo "[smoke] ${chase_label}: queued path continuation did not move; falling through to blocker attack input" >>"$log_path"
      else
        echo "[smoke] wait-for-log-since-done: ${chase_label} queued path continuation" >>"$log_path"
        if try_wait_for_fixed_log_pattern_since \
          "$objective_pattern" \
          "$(blocker_chase_env_value "$target_index" "OBJECTIVE_WAIT_SLICE" "3")" \
          "$continue_start"; then
          echo "[smoke] ${chase_label}: blocker ${target_index} defeated and objective advanced after queued path continuation" >>"$log_path"
          return 0
        fi
        if [ "$(blocker_chase_env_value "$target_index" "ATTACK_AFTER_CONTINUE_MOVE" "1")" != "1" ]; then
          chase_index=$((chase_index + 1))
          continue
        fi
        echo "[smoke] ${chase_label}: queued path moved; continuing with target click in the same turn" >>"$log_path"
      fi
    fi

    world_script_click_at \
      "$minimap_x" \
      "$minimap_y" \
      "${CLASH95_STACK10_BLOCKER_CHASE_MINIMAP_SCRIPT_READS:-12}" \
      "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_MINIMAP_GAP:-0.70}" \
      "${chase_label}-minimap-${target_index}"
    world_script_wait_reads \
      "${CLASH95_STACK10_BLOCKER_CHASE_MINIMAP_SETTLE_READS:-120}" \
      "${CLASH95_STACK10_BLOCKER_CHASE_MINIMAP_SETTLE_GAP:-1.0}" \
      "${chase_label}-minimap-settle"

    local attack_start
    attack_start="$(next_log_line_number)"
    world_script_click_at \
      "$attack_x" \
      "$attack_y" \
      "${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_SCRIPT_READS:-96}" \
      "${CLASH95_CLICK_STACK10_BLOCKER_CHASE_ATTACK_GAP:-1.0}" \
      "${chase_label}-attack-${target_index}"

    local attack_pattern
    local attack_move_pattern
    local attack_input_timeout
    local attack_input_start_seconds
    local attack_input_outcome
    attack_pattern="${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_PATTERN:-enemy_attack_call selected=${chaser_index} a=${target_index} b=${target_x} c=${target_y}}"
    attack_move_pattern="${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_MOVE_PATTERN:-unit_move_after_path_state selected=${chaser_index}}"
    attack_input_timeout="${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_TIMEOUT:-20}"
    attack_input_start_seconds="$SECONDS"
    attack_input_outcome=""

    echo "[smoke] wait-for-log-since: ${chase_label} blocker attack-or-move timeout=${attack_input_timeout}s start=${attack_start}" >>"$log_path"
    while [ $((SECONDS - attack_input_start_seconds)) -lt "$attack_input_timeout" ]; do
      if log_has_fixed_pattern_since "$objective_pattern" "$attack_start"; then
        attack_input_outcome="objective"
        break
      fi
      if log_has_fixed_pattern_since "$attack_pattern" "$attack_start"; then
        attack_input_outcome="attack"
        break
      fi
      if log_has_fixed_pattern_since "$attack_move_pattern" "$attack_start"; then
        attack_input_outcome="move"
        break
      fi
      if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
        fail_smoke "first-mission real-input smoke process exited while waiting for fresh log pattern ${chase_label} blocker attack-or-move"
      fi
      sleep 0.1
    done
    if [ "$attack_input_outcome" = "objective" ]; then
      echo "[smoke] ${chase_label}: blocker ${target_index} defeated and objective advanced during target input" >>"$log_path"
      return 0
    fi
    if [ "$attack_input_outcome" = "move" ]; then
      echo "[smoke] wait-for-log-since-done: ${chase_label} target input moved stack ${chaser_index}; continuing chase next turn" >>"$log_path"
      chase_index=$((chase_index + 1))
      continue
    fi
    if [ "$attack_input_outcome" != "attack" ]; then
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${chase_label} blocker attack-or-move: ${attack_pattern} or ${attack_move_pattern}"
    fi
    echo "[smoke] wait-for-log-since-done: ${chase_label} blocker attack" >>"$log_path"

    local battle_prompt_pattern="${CLASH95_STACK10_BLOCKER_CHASE_BATTLE_PROMPT_PATTERN:-battle_prompt_layout_secondary}"
    local attack_return_pattern="${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_RETURN_PATTERN:-enemy_attack_return selected=${chaser_index} a=${target_index} b=${target_x} c=${target_y}}"
    local attack_outcome_timeout="${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_OUTCOME_TIMEOUT:-${CLASH95_STACK10_BLOCKER_CHASE_ATTACK_RETURN_TIMEOUT:-30}}"
    local attack_outcome_start_seconds="$SECONDS"
    local attack_outcome=""

    echo "[smoke] wait-for-log-since: ${chase_label} attack outcome timeout=${attack_outcome_timeout}s start=${attack_start}" >>"$log_path"
    while [ $((SECONDS - attack_outcome_start_seconds)) -lt "$attack_outcome_timeout" ]; do
      if log_has_fixed_pattern_since "$battle_prompt_pattern" "$attack_start"; then
        attack_outcome="battle-prompt"
        break
      fi
      if log_has_fixed_pattern_since "$attack_return_pattern" "$attack_start"; then
        attack_outcome="attack-return"
        break
      fi
      if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
        fail_smoke "first-mission real-input smoke process exited while waiting for fresh log pattern ${chase_label} attack outcome"
      fi
      sleep 0.1
    done
    if [ "$attack_outcome" = "attack-return" ] \
      && try_wait_for_fixed_log_pattern_since \
        "$battle_prompt_pattern" \
        "${CLASH95_STACK10_BLOCKER_CHASE_BATTLE_PROMPT_AFTER_RETURN_WAIT_SLICE:-2}" \
        "$attack_start"; then
      attack_outcome="battle-prompt"
    fi

    if [ "$attack_outcome" = "battle-prompt" ]; then
      echo "[smoke] wait-for-log-since-done: ${chase_label} battle prompt" >>"$log_path"
      local manual_battle_milestone
      local battle_prompt_x
      local battle_prompt_y
      manual_battle_milestone="$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_MILESTONE" "0")"
      if [ "$manual_battle_milestone" = "1" ]; then
        battle_prompt_x="$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_X" "$(blocker_chase_click_env_value "$target_index" "MANUAL_BATTLE_PROMPT_X" "276")")"
        battle_prompt_y="$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_Y" "$(blocker_chase_click_env_value "$target_index" "MANUAL_BATTLE_PROMPT_Y" "158")")"
      else
        battle_prompt_x="$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_X" "354")"
        battle_prompt_y="$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_Y" "158")"
      fi
      click_at \
        "$window" \
        "$battle_prompt_x" \
        "$battle_prompt_y" \
        "$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_HOLD" "0.22")" \
        "$(blocker_chase_click_env_value "$target_index" "BATTLE_PROMPT_GAP" "4.0")" \
        "${chase_label}-battle-prompt"
      if [ "$manual_battle_milestone" = "1" ]; then
        wait_for_fixed_log_pattern_since \
          "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_PATTERN" "battle_turn_loop_after_input_widgets")" \
          "${chase_label} manual battle input loop" \
          "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_TIMEOUT" "35")" \
          "$attack_start"
        echo "[smoke] ${chase_label}: manual battle input loop reached" >>"$log_path"

        local manual_battle_script_file
        local manual_battle_script
        manual_battle_script_file="$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_SCRIPT_FILE" "")"
        manual_battle_script="$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_SCRIPT" "")"
        if [ -n "$manual_battle_script_file" ]; then
          if [ ! -f "$manual_battle_script_file" ]; then
            fail_smoke "first-mission real-input smoke ${chase_label} manual battle script file does not exist: $manual_battle_script_file"
          fi
          echo "[smoke] ${chase_label}: append manual battle script file ${manual_battle_script_file}" >>"$log_path"
          : >"$battle_input_script"
          cat "$manual_battle_script_file" >>"$battle_input_script"
          sleep "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_SCRIPT_GAP" "1.0")"
        fi
        if [ -n "$manual_battle_script" ]; then
          echo "[smoke] ${chase_label}: append manual battle script from env" >>"$log_path"
          : >"$battle_input_script"
          printf '%b\n' "$manual_battle_script" >>"$battle_input_script"
          sleep "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_SCRIPT_GAP" "1.0")"
        fi
        wait_for_fixed_log_pattern_since \
          "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_EXPECT_PATTERN" "unit_attack_battle_return selected=${chaser_index} a=${target_index}")" \
          "${chase_label} manual battle result" \
          "$(blocker_chase_env_value "$target_index" "MANUAL_BATTLE_EXPECT_TIMEOUT" "180")" \
          "$attack_start"
      else
        wait_for_fixed_log_pattern_since \
          "$(blocker_chase_env_value "$target_index" "BATTLE_RETURN_PATTERN" "unit_attack_autoresolve_return selected=${chaser_index} a=${target_index}")" \
          "${chase_label} battle return" \
          "$(blocker_chase_env_value "$target_index" "BATTLE_RETURN_TIMEOUT" "30")" \
          "$attack_start"
      fi
    elif [ "$attack_outcome" = "attack-return" ]; then
      echo "[smoke] wait-for-log-since-done: ${chase_label} attack return" >>"$log_path"
    else
      fail_smoke "first-mission real-input smoke timed out waiting for fresh log pattern ${chase_label} attack outcome: ${battle_prompt_pattern} or ${attack_return_pattern}"
    fi

    if try_wait_for_fixed_log_pattern_since \
      "$objective_pattern" \
      "${CLASH95_STACK10_BLOCKER_CHASE_OBJECTIVE_WAIT_SLICE:-3}" \
      "$attack_start"; then
      echo "[smoke] ${chase_label}: blocker ${target_index} defeated and objective advanced" >>"$log_path"
      return 0
    fi

    chase_index=$((chase_index + 1))
  done
  return 1
}

if [ "${CLASH95_FIRST_MISSION_STACK7_CHASE_REPEATS:-0}" -gt 0 ]; then
  run_stack10_world_blocker_chase \
    "stack7-chase" \
    7 \
    49 \
    39 \
    "${CLASH95_CLICK_STACK7_CHASE_MINIMAP_X:-569}" \
    "${CLASH95_CLICK_STACK7_CHASE_MINIMAP_Y:-159}" \
    "${CLASH95_CLICK_STACK7_CHASE_ATTACK_X:-491}" \
    "${CLASH95_CLICK_STACK7_CHASE_ATTACK_Y:-363}" \
    "${CLASH95_STACK7_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=8 a=40 b=3 c=1}" \
    "${CLASH95_FIRST_MISSION_STACK7_CHASE_REPEATS:-0}" \
    "${CLASH95_FIRST_MISSION_STACK7_DIRECT_SELECT_FIRST:-1}" \
    "${CLASH95_FIRST_MISSION_STACK7_CHASER_INDEX:-10}" || fail_smoke "first-mission real-input smoke failed to clear stack7"
fi

if [ "${CLASH95_FIRST_MISSION_STACK8_CHASE_REPEATS:-0}" -gt 0 ]; then
  run_stack10_world_blocker_chase \
    "stack8-chase" \
    8 \
    40 \
    3 \
    "${CLASH95_CLICK_STACK8_CHASE_MINIMAP_X:-533}" \
    "${CLASH95_CLICK_STACK8_CHASE_MINIMAP_Y:-15}" \
    "${CLASH95_CLICK_STACK8_CHASE_ATTACK_X:-491}" \
    "${CLASH95_CLICK_STACK8_CHASE_ATTACK_Y:-240}" \
    "${CLASH95_STACK8_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_blocked selected=9 a=19 b=12 c=1}" \
    "${CLASH95_FIRST_MISSION_STACK8_CHASE_REPEATS:-0}" \
    0 \
    "${CLASH95_FIRST_MISSION_STACK8_CHASER_INDEX:-10}" || fail_smoke "first-mission real-input smoke failed to clear stack8"
fi

if [ "${CLASH95_FIRST_MISSION_STACK9_CHASE_REPEATS:-0}" -gt 0 ]; then
  run_stack10_world_blocker_chase \
    "stack9-chase" \
    9 \
    19 \
    12 \
    "${CLASH95_CLICK_STACK9_CHASE_MINIMAP_X:-449}" \
    "${CLASH95_CLICK_STACK9_CHASE_MINIMAP_Y:-51}" \
    "${CLASH95_CLICK_STACK9_CHASE_ATTACK_X:-491}" \
    "${CLASH95_CLICK_STACK9_CHASE_ATTACK_Y:-363}" \
    "${CLASH95_STACK9_CHASE_OBJECTIVE_ADVANCE_PATTERN:-mission_objective_complete}" \
    "${CLASH95_FIRST_MISSION_STACK9_CHASE_REPEATS:-0}" \
    0 \
    "${CLASH95_FIRST_MISSION_STACK9_CHASER_INDEX:-10}" || fail_smoke "first-mission real-input smoke failed to clear stack9"
fi

if ! kill -0 "$pid" 2>/dev/null; then
  set +e
  wait "$pid"
  status=$?
  set -e
  fail_smoke "first-mission real-input smoke exited after route with status $status"
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING:-0}" = "1" ]; then
  if [ "${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_PATTERN:-}" ]; then
    wait_for_fixed_log_pattern_since \
      "$CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_PATTERN" \
      "leave-running expected pattern" \
      "${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_TIMEOUT:-20}" \
      1
  fi
  echo "[smoke] leaving process running pid=${pid} artifacts=${smoke_root}" >>"$log_path"
  echo "first-mission real-input smoke left process running: pid=${pid} artifacts=${smoke_root}" >&2
  if [ "${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_HOLD:-0}" = "1" ]; then
    echo "[smoke] leave-running hold active; keeping driver and Xvfb alive" >>"$log_path"
    while kill -0 "$pid" 2>/dev/null; do
      sleep "${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_HOLD_POLL_SECONDS:-60}"
    done
  fi
  trap - EXIT INT TERM
  exit 0
fi

kill -TERM "-$pid" 2>/dev/null || true
sleep 1
if kill -0 "$pid" 2>/dev/null; then
  kill -KILL "-$pid" 2>/dev/null || true
fi
wait "$pid" 2>/dev/null || true

if pgrep -g "$pid" >/dev/null 2>&1; then
  pgrep -ag "$pid" >&2 || true
  fail_smoke "first-mission real-input smoke left processes in the bootstrap process group"
fi
pid=""

if grep -q "Segmentation fault" "$log_path" || grep -q "Aborted" "$log_path"; then
  fail_smoke "first-mission real-input smoke reported a crash"
fi

frame_count=0
last_frame=""
for captured_frame in "$frame_prefix"-*.bmp; do
  if [ -f "$captured_frame" ]; then
    frame_count=$((frame_count + 1))
    last_frame="$captured_frame"
  fi
done
echo "[smoke] captured_frames=$frame_count" >>"$log_path"

if [ "${CLASH95_FIRST_MISSION_MOVE_REQUIRE_FRAMES:-0}" = "1" ] && [ "$frame_count" -eq 0 ]; then
  fail_smoke "first-mission real-input smoke did not capture any presented frames"
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_REJECT_BLANK_FRAMES:-0}" = "1" ] && [ "$frame_count" -gt 0 ]; then
  frame_mean=""
  if command -v identify >/dev/null 2>&1; then
    frame_mean="$(identify -format '%[mean]' "$last_frame" 2>/dev/null || true)"
  elif command -v magick >/dev/null 2>&1; then
    frame_mean="$(magick identify -format '%[mean]' "$last_frame" 2>/dev/null || true)"
  else
    echo "[smoke] blank-frame check skipped; ImageMagick identify is unavailable" >>"$log_path"
  fi
  echo "[smoke] last_frame=${last_frame:-none} mean=${frame_mean:-unavailable}" >>"$log_path"
  if [ "$frame_mean" = "0" ] || [ "$frame_mean" = "0.0" ]; then
    fail_smoke "first-mission real-input smoke captured an all-black final frame: $last_frame"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET:-}" ]; then
  for expected_preset in ${CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET//,/ }; do
    case "$expected_preset" in
      route)
        require_fixed_log_pattern "[smoke] campaign:" "preset route/campaign"
        require_fixed_log_pattern "[smoke] campaign-first:" "preset route/campaign-first"
        require_fixed_log_pattern "[smoke] next-unit:" "preset route/next-unit"
        require_fixed_log_pattern "[smoke] unit-slot:" "preset route/unit-slot"
        require_fixed_log_pattern "[smoke] move-target:" "preset route/move-target"
        ;;
      world-click)
        require_fixed_log_pattern "world_click" "preset world-click"
        ;;
      playable-turn)
        require_fixed_log_pattern "next_unit_selected selected=1 a=31 b=44" "preset playable-turn/next-unit-selected"
        require_fixed_log_pattern "selection_slot_toggle selected=1 a=0 b=1" "preset playable-turn/slot-toggle"
        require_fixed_log_pattern "selection_split_attempt selected=1 a=31 b=45" "preset playable-turn/split-attempt"
        require_fixed_log_pattern "selection_split_done selected=1 a=31 b=45" "preset playable-turn/split-done"
        ;;
      turn-advance)
        require_fixed_log_pattern "playgame_after_human_turn" "preset turn-advance/human-turn-exit"
        require_fixed_log_pattern "turn_advance_enter" "preset turn-advance/enter"
        ;;
      mission-complete)
        require_fixed_log_pattern "mission_objective_complete" "preset mission-complete/objective"
        ;;
      stack6-manual)
        require_fixed_log_pattern "manual battle input loop reached" "preset stack6-manual/loop"
        require_fixed_log_pattern "battle_turn_loop_after_input_widgets" "preset stack6-manual/input-loop"
        ;;
      stack6-manual-actions)
        require_fixed_log_pattern "manual battle input loop reached" "preset stack6-manual-actions/loop"
        require_fixed_log_pattern "battle_action_next_unit_selected" "preset stack6-manual-actions/next-unit"
        require_fixed_log_pattern "battle_action_prepare_defence_done" "preset stack6-manual-actions/defence"
        ;;
      enemy-attack)
        require_fixed_log_pattern "enemy_attack_call selected=10 a=3 b=46 c=45" "preset enemy-attack/call"
        require_fixed_log_pattern "unit_attack_enter selected=10 a=3 b=46 c=45" "preset enemy-attack/enter"
        require_fixed_log_pattern "unit_attack_track selected=10 a=3 b=46 c=45" "preset enemy-attack/track"
        require_fixed_log_pattern "unit_attack_after_track selected=10 a=3 b=36 c=45" "preset enemy-attack/after-track"
        require_fixed_log_pattern "enemy_attack_return selected=10 a=3 b=46 c=45" "preset enemy-attack/return"
        ;;
      end-turn)
        require_fixed_log_pattern "[smoke] end-turn:" "preset end-turn"
        ;;
      post-end-turn)
        require_fixed_log_pattern "[smoke] post-end-turn-skip-" "preset post-end-turn"
        ;;
      *)
        fail_smoke "first-mission real-input smoke unknown expected-log preset: $expected_preset"
        ;;
    esac
  done
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_EXPECT_LOG:-}" ]; then
  if ! grep -Fq "$CLASH95_FIRST_MISSION_MOVE_EXPECT_LOG" "$log_path"; then
    fail_smoke "first-mission real-input smoke did not find expected log pattern: $CLASH95_FIRST_MISSION_MOVE_EXPECT_LOG"
  fi
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS:-}" ]; then
  while IFS= read -r expected_pattern; do
    if [ -z "$expected_pattern" ]; then
      continue
    fi
    if ! grep -Fq "$expected_pattern" "$log_path"; then
      fail_smoke "first-mission real-input smoke did not find expected log pattern: $expected_pattern"
    fi
  done <<<"$CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS"
fi

if [ "${CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE:-}" ]; then
  if [ ! -f "$CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE" ]; then
    fail_smoke "first-mission real-input smoke expected-log file does not exist: $CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE"
  fi
  while IFS= read -r expected_pattern; do
    case "$expected_pattern" in
      ""|\#*) continue ;;
    esac
    if ! grep -Fq "$expected_pattern" "$log_path"; then
      fail_smoke "first-mission real-input smoke did not find expected log pattern from file: $expected_pattern"
    fi
  done <"$CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE"
fi
