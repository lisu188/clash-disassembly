#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

if [ "${CLASH95_ENABLE_SOAK_PROBE:-0}" != "1" ]; then
  echo "clash95 soak probe skipped; set CLASH95_ENABLE_SOAK_PROBE=1 to run" >&2
  exit 77
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "clash95 soak probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
frame_metrics_tool="$repo_root/tests/frame_metrics.py"
bootstrap_real="$(readlink -f "$bootstrap_bin" 2>/dev/null || printf '%s' "$bootstrap_bin")"
scenario="${CLASH95_SOAK_SCENARIO:-main-menu-idle}"
duration_seconds="${CLASH95_SOAK_DURATION_SECONDS:-120}"
sample_interval="${CLASH95_SOAK_SAMPLE_INTERVAL_SECONDS:-5}"
run_id="${CLASH95_SOAK_RUN_ID:-$(date -u +%Y%m%dT%H%M%SZ)-$$}"
artifact_root="${CLASH95_SOAK_ARTIFACT_DIR:-$repo_root/artifacts/soak/$scenario}"
artifact_run="$artifact_root/$run_id"
soak_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-soak-${scenario}.XXXXXX")"
log_path="$soak_root/soak.log"
frame_prefix="$soak_root/frame"
world_input_script="$soak_root/world-input.txt"
platform_input_script="$soak_root/platform-input.txt"
battle_input_script="$soak_root/battle-input.txt"
pid=""
xvfb_pid=""
window=""
game_pid=""
preserve_artifacts=0
soak_result="interrupted"
soak_reason=""
input_pulses=0
input_failures=0
rss_peak_kb=0
rss_last_kb=0
frame_count=0
route_replay_iterations=0
route_replay_mission_id=""
route_replay_latest_run=""
route_replay_summary=""
route_replay_captured_frames=0
route_replay_copied_frames=0
route_replay_last_frame_mean=""
route_replay_log_truncated=""
route_replay_objective_complete_count=0
route_replay_objective_blocked_count=0
route_replay_input_step_count=0
first_mission_probe_iterations=0
first_mission_probe_latest_run=""
first_mission_probe_summary=""
first_mission_probe_captured_frames=0
first_mission_probe_copied_frames=0
first_mission_probe_last_frame_mean=""
first_mission_probe_log_truncated=""
first_mission_probe_objective_complete_count=0
first_mission_probe_objective_blocked_count=0
first_mission_probe_input_step_count=0
first_mission_probe_enemy_attack_return_count=0
first_mission_probe_unit_attack_enter_count=0
: >"$log_path"
: >"$world_input_script"
: >"$platform_input_script"
: >"$battle_input_script"

is_unsigned_integer() {
  case "${1:-}" in
    ""|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
}

if ! is_unsigned_integer "$duration_seconds" || [ "$duration_seconds" = "0" ]; then
  echo "CLASH95_SOAK_DURATION_SECONDS must be a positive integer, got: $duration_seconds" >&2
  exit 2
fi

for tool in timeout grep head tail find sort awk wc cp mkdir date du python3; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "clash95 soak probe skipped; missing $tool" >&2
    exit 77
  fi
done
if [ ! -f "$frame_metrics_tool" ]; then
  echo "clash95 soak probe skipped; missing frame metrics tool" >&2
  exit 77
fi

append_unique_frame_path() {
  local -n destination_ref="$1"
  local frame_path="$2"
  local existing

  if [ ! -f "$frame_path" ]; then
    return 0
  fi
  for existing in "${destination_ref[@]}"; do
    if [ "$existing" = "$frame_path" ]; then
      return 0
    fi
  done
  destination_ref+=( "$frame_path" )
}

sample_frame_array() {
  local source_name="$1"
  local destination_name="$2"
  local -n source_ref="$source_name"
  local -n destination_ref="$destination_name"
  local max_frames="$3"
  local head_count="$4"
  local total
  local tail_count
  local start_index
  local index

  if ! is_unsigned_integer "$max_frames" || [ "$max_frames" = "0" ]; then
    return 0
  fi
  if ! is_unsigned_integer "$head_count"; then
    head_count=8
  fi
  total="${#source_ref[@]}"
  if [ "$total" -eq 0 ]; then
    return 0
  fi
  if [ "$total" -le "$max_frames" ]; then
    for index in "${!source_ref[@]}"; do
      append_unique_frame_path "$destination_name" "${source_ref[$index]}"
    done
    return 0
  fi

  if [ "$head_count" -ge "$max_frames" ]; then
    head_count=$((max_frames - 1))
  fi
  if [ "$head_count" -lt 0 ]; then
    head_count=0
  fi
  tail_count=$((max_frames - head_count))

  index=0
  while [ "$index" -lt "$head_count" ] && [ "$index" -lt "$total" ]; do
    append_unique_frame_path "$destination_name" "${source_ref[$index]}"
    index=$((index + 1))
  done

  start_index=$((total - tail_count))
  if [ "$start_index" -lt 0 ]; then
    start_index=0
  fi
  index="$start_index"
  while [ "$index" -lt "$total" ]; do
    append_unique_frame_path "$destination_name" "${source_ref[$index]}"
    index=$((index + 1))
  done
}

count_frames() {
  local captured_frame
  local count=0

  for captured_frame in "$frame_prefix"-*.bmp; do
    if [ -f "$captured_frame" ]; then
      count=$((count + 1))
    fi
  done
  printf '%s' "$count"
}

latest_frame_path() {
  find "$soak_root" -maxdepth 1 -type f -name 'frame-*.bmp' -printf '%T@ %p\n' 2>/dev/null \
    | sort -n \
    | tail -n 1 \
    | sed 's/^[^ ]* //'
}

copy_capped_log() {
  local source_path="$1"
  local target_path="$2"
  local max_bytes="${CLASH95_SOAK_MAX_LOG_BYTES:-12000000}"
  local head_lines="${CLASH95_SOAK_LOG_HEAD_LINES:-1200}"
  local tail_lines="${CLASH95_SOAK_LOG_TAIL_LINES:-2400}"
  local source_bytes

  source_bytes="$(wc -c <"$source_path" 2>/dev/null || echo 0)"
  source_bytes="${source_bytes//[[:space:]]/}"
  if ! is_unsigned_integer "$max_bytes" || [ "$max_bytes" = "0" ] || [ "${source_bytes:-0}" -le "$max_bytes" ]; then
    cp -f "$source_path" "$target_path" 2>/dev/null || true
    return 0
  fi
  if ! is_unsigned_integer "$head_lines"; then
    head_lines=1200
  fi
  if ! is_unsigned_integer "$tail_lines"; then
    tail_lines=2400
  fi
  {
    echo "[soak] durable log truncated"
    echo "original_bytes=${source_bytes:-0}"
    echo "max_bytes=$max_bytes"
    echo
    echo "--- log head ---"
    head -n "$head_lines" "$source_path" || true
    echo
    echo "--- log tail ---"
    tail -n "$tail_lines" "$source_path" || true
  } >"$target_path" 2>/dev/null || true
}

copy_capped_frames() {
  local target_dir="$1"
  local max_frames="${CLASH95_SOAK_MAX_COPIED_FRAMES:-120}"
  local head_count="${CLASH95_SOAK_COPIED_FRAME_HEAD_COUNT:-8}"
  local captured_frame
  local -a captured_frames=()
  local -a sampled_frames=()

  shopt -s nullglob
  captured_frames=( "$frame_prefix"-*.bmp )
  shopt -u nullglob
  sample_frame_array captured_frames sampled_frames "$max_frames" "$head_count"
  for captured_frame in "${sampled_frames[@]}"; do
    cp -f "$captured_frame" "$target_dir/" 2>/dev/null || true
  done
}

update_game_pid() {
  local candidate
  local candidate_exe

  if [ -n "${game_pid:-}" ] && kill -0 "$game_pid" 2>/dev/null; then
    return 0
  fi
  game_pid=""
  if ! command -v pgrep >/dev/null 2>&1 || [ -z "${pid:-}" ]; then
    return 0
  fi
  while IFS= read -r candidate; do
    if [ -z "$candidate" ] || [ "$candidate" = "$pid" ]; then
      continue
    fi
    candidate_exe="$(readlink -f "/proc/$candidate/exe" 2>/dev/null || true)"
    if [ "$candidate_exe" = "$bootstrap_real" ]; then
      game_pid="$candidate"
      return 0
    fi
  done < <(pgrep -g "$pid" 2>/dev/null || true)
}

sample_rss() {
  local target_pid
  local value

  update_game_pid
  target_pid="${game_pid:-$pid}"
  if [ -z "${target_pid:-}" ] || [ ! -r "/proc/$target_pid/status" ]; then
    return 0
  fi
  value="$(awk '/^VmRSS:/ { print $2 + 0 }' "/proc/$target_pid/status" 2>/dev/null || true)"
  if is_unsigned_integer "${value:-}"; then
    rss_last_kb="$value"
    if [ "$value" -gt "$rss_peak_kb" ]; then
      rss_peak_kb="$value"
    fi
  fi
}

summary_value() {
  local summary_path="$1"
  local key="$2"

  if [ ! -f "$summary_path" ]; then
    return 0
  fi
  awk -F= -v key="$key" '$1 == key { sub(/^[^=]*=/, ""); print; exit }' "$summary_path" 2>/dev/null || true
}

game_log_count() {
  local pattern="$1"

  awk -v pattern="$pattern" '
    index($0, pattern) && index($0, "[soak]") == 0 { count++ }
    END { print count + 0 }
  ' "$log_path" 2>/dev/null || true
}

update_route_replay_summary() {
  local latest_path="$artifact_run/route-runs/mission-$route_replay_mission_id/latest.txt"

  route_replay_latest_run=""
  route_replay_summary=""
  route_replay_captured_frames=0
  route_replay_copied_frames=0
  route_replay_last_frame_mean=""
  route_replay_log_truncated=""
  route_replay_objective_complete_count=0
  route_replay_objective_blocked_count=0
  route_replay_input_step_count=0

  if [ ! -f "$latest_path" ]; then
    return 0
  fi
  route_replay_latest_run="$(summary_value "$latest_path" "latest_run")"
  route_replay_summary="$(summary_value "$latest_path" "summary")"
  if [ -z "$route_replay_summary" ] && [ -n "$route_replay_latest_run" ]; then
    route_replay_summary="$route_replay_latest_run/summary.txt"
  fi
  if [ ! -f "$route_replay_summary" ]; then
    return 0
  fi
  route_replay_captured_frames="$(summary_value "$route_replay_summary" "captured_frames_total")"
  route_replay_copied_frames="$(summary_value "$route_replay_summary" "copied_frames")"
  route_replay_last_frame_mean="$(summary_value "$route_replay_summary" "last_frame_mean")"
  route_replay_log_truncated="$(summary_value "$route_replay_summary" "durable_log_truncated")"
  route_replay_objective_complete_count="$(summary_value "$route_replay_summary" "mission_objective_complete_count")"
  route_replay_objective_blocked_count="$(summary_value "$route_replay_summary" "mission_objective_blocked_count")"
  route_replay_input_step_count="$(summary_value "$route_replay_summary" "route_input_step_count")"
}

update_first_mission_probe_summary() {
  local probe_dir="$artifact_run/first-mission-attack"
  local latest_path="$probe_dir/latest.txt"

  first_mission_probe_latest_run=""
  first_mission_probe_summary=""
  first_mission_probe_captured_frames=0
  first_mission_probe_copied_frames=0
  first_mission_probe_last_frame_mean=""
  first_mission_probe_log_truncated=""
  first_mission_probe_objective_complete_count=0
  first_mission_probe_objective_blocked_count=0
  first_mission_probe_input_step_count=0
  first_mission_probe_enemy_attack_return_count=0
  first_mission_probe_unit_attack_enter_count=0

  if [ ! -f "$latest_path" ]; then
    return 0
  fi
  first_mission_probe_latest_run="$(summary_value "$latest_path" "latest_run")"
  first_mission_probe_summary="$(summary_value "$latest_path" "summary")"
  if [ -z "$first_mission_probe_summary" ] && [ -n "$first_mission_probe_latest_run" ]; then
    first_mission_probe_summary="$first_mission_probe_latest_run/summary.txt"
  fi
  if [ ! -f "$first_mission_probe_summary" ]; then
    return 0
  fi
  first_mission_probe_captured_frames="$(summary_value "$first_mission_probe_summary" "captured_frames_total")"
  first_mission_probe_copied_frames="$(summary_value "$first_mission_probe_summary" "copied_frames")"
  first_mission_probe_last_frame_mean="$(summary_value "$first_mission_probe_summary" "last_frame_mean")"
  first_mission_probe_log_truncated="$(summary_value "$first_mission_probe_summary" "durable_log_truncated")"
  first_mission_probe_objective_complete_count="$(summary_value "$first_mission_probe_summary" "mission_objective_complete_count")"
  first_mission_probe_objective_blocked_count="$(summary_value "$first_mission_probe_summary" "mission_objective_blocked_count")"
  first_mission_probe_input_step_count="$(summary_value "$first_mission_probe_summary" "route_input_step_count")"
  first_mission_probe_enemy_attack_return_count="$(grep -Fc "enemy_attack_return" "$first_mission_probe_summary" 2>/dev/null || true)"
  first_mission_probe_unit_attack_enter_count="$(grep -Fc "unit_attack_enter" "$first_mission_probe_summary" 2>/dev/null || true)"
}

prune_soak_artifacts() {
  if [ "${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}" != "1" ]; then
    return 0
  fi
  if [ ! -f "$repo_root/tests/prune_artifacts.sh" ]; then
    return 0
  fi

  CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS="$artifact_root${CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS:+:$CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS}" \
  CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP="${CLASH95_SOAK_KEEP_RUNS:-8}" \
  CLASH95_ARTIFACT_PRUNE_MAX_BYTES="${CLASH95_ARTIFACT_PRUNE_MAX_BYTES:-805306368}" \
    bash "$repo_root/tests/prune_artifacts.sh" --apply --quiet >&2 || true
}

persist_soak_artifacts() {
  local latest_frame
  local durable_latest_frame=""
  local latest_metrics=""
  local progression_metrics=""
  local artifact_bytes=""
  local summary_path
  local -a captured_frames=()
  local -a sampled_frames=()

  if [ "${CLASH95_SOAK_DURABLE_ARTIFACTS:-1}" != "1" ]; then
    return 0
  fi
  mkdir -p "$artifact_run"
  copy_capped_log "$log_path" "$artifact_run/soak.log"
  cp -f "$world_input_script" "$artifact_run/world-input.txt" 2>/dev/null || true
  cp -f "$platform_input_script" "$artifact_run/platform-input.txt" 2>/dev/null || true
  cp -f "$battle_input_script" "$artifact_run/battle-input.txt" 2>/dev/null || true
  cp -f "$soak_root"/xvfb-*.log "$artifact_run/" 2>/dev/null || true
  env | grep '^CLASH95_' | sort >"$artifact_run/clash95-env.txt" 2>/dev/null || true
  copy_capped_frames "$artifact_run"

  frame_count="$(count_frames)"
  latest_frame="$(latest_frame_path)"
  if [ -n "$latest_frame" ] && [ -f "$latest_frame" ]; then
    latest_metrics="$(python3 "$frame_metrics_tool" "$latest_frame" 2>/dev/null | tr '\n' ';' || true)"
    if [ -f "$artifact_run/$(basename "$latest_frame")" ]; then
      durable_latest_frame="$artifact_run/$(basename "$latest_frame")"
    fi
  fi
  shopt -s nullglob
  captured_frames=( "$frame_prefix"-*.bmp )
  shopt -u nullglob
  sample_frame_array captured_frames sampled_frames "${CLASH95_SOAK_PROGRESS_METRICS_MAX_FRAMES:-96}" "${CLASH95_SOAK_PROGRESS_METRICS_HEAD_COUNT:-8}"
  if [ "${#sampled_frames[@]}" -ge 2 ]; then
    progression_metrics="$(python3 "$frame_metrics_tool" \
      --min-diff "${CLASH95_SOAK_MIN_FRAME_DIFF:-0.25}" \
      "${sampled_frames[@]}" 2>/dev/null | tail -n 1 || true)"
  fi
  artifact_bytes="$(du -sb "$artifact_run" 2>/dev/null | awk '{ print $1 + 0 }' || true)"

  summary_path="$artifact_run/summary.txt"
  {
    echo "durable_run=$artifact_run"
    echo "scenario=$scenario"
    echo "result=$soak_result"
    echo "reason=${soak_reason:-none}"
    echo "duration_seconds=$duration_seconds"
    echo "sample_interval_seconds=$sample_interval"
    echo "input_pulses=$input_pulses"
    echo "input_failures=$input_failures"
    echo "captured_frames_total=$frame_count"
    echo "copied_frame_cap=${CLASH95_SOAK_MAX_COPIED_FRAMES:-120}"
    echo "latest_frame=${latest_frame:-none}"
    echo "latest_frame_durable=${durable_latest_frame:-none}"
    echo "latest_frame_visual_metrics=${latest_metrics:-unavailable}"
    echo "frame_progression_metrics=${progression_metrics:-unavailable}"
    echo "rss_last_kb=$rss_last_kb"
    echo "rss_peak_kb=$rss_peak_kb"
    echo "artifact_bytes=${artifact_bytes:-unavailable}"
    echo "route_replay_iterations=$route_replay_iterations"
    echo "route_replay_mission_id=${route_replay_mission_id:-none}"
    echo "route_replay_latest_run=${route_replay_latest_run:-none}"
    echo "route_replay_summary=${route_replay_summary:-none}"
    echo "route_replay_captured_frames=${route_replay_captured_frames:-0}"
    echo "route_replay_copied_frames=${route_replay_copied_frames:-0}"
    echo "route_replay_last_frame_mean=${route_replay_last_frame_mean:-unavailable}"
    echo "route_replay_log_truncated=${route_replay_log_truncated:-unavailable}"
    echo "route_replay_objective_complete_count=${route_replay_objective_complete_count:-0}"
    echo "route_replay_objective_blocked_count=${route_replay_objective_blocked_count:-0}"
    echo "route_replay_input_step_count=${route_replay_input_step_count:-0}"
    echo "first_mission_probe_iterations=$first_mission_probe_iterations"
    echo "first_mission_probe_latest_run=${first_mission_probe_latest_run:-none}"
    echo "first_mission_probe_summary=${first_mission_probe_summary:-none}"
    echo "first_mission_probe_captured_frames=${first_mission_probe_captured_frames:-0}"
    echo "first_mission_probe_copied_frames=${first_mission_probe_copied_frames:-0}"
    echo "first_mission_probe_last_frame_mean=${first_mission_probe_last_frame_mean:-unavailable}"
    echo "first_mission_probe_log_truncated=${first_mission_probe_log_truncated:-unavailable}"
    echo "first_mission_probe_objective_complete_count=${first_mission_probe_objective_complete_count:-0}"
    echo "first_mission_probe_objective_blocked_count=${first_mission_probe_objective_blocked_count:-0}"
    echo "first_mission_probe_input_step_count=${first_mission_probe_input_step_count:-0}"
    echo "first_mission_probe_enemy_attack_return_count=${first_mission_probe_enemy_attack_return_count:-0}"
    echo "first_mission_probe_unit_attack_enter_count=${first_mission_probe_unit_attack_enter_count:-0}"
    echo "castle_first_present_count=$(game_log_count "[castle] first_present")"
    echo "economy_first_present_count=$(game_log_count "[economy] first_present")"
    echo "economy_list_next_count=$(game_log_count "[economy] list_next")"
    echo "economy_exit_count=$(game_log_count "[economy] exit")"
    echo
    echo "recent log:"
    tail -n 220 "$log_path" || true
  } >"$summary_path" 2>/dev/null || true
  {
    echo "latest_run=$artifact_run"
    echo "scenario=$scenario"
    echo "result=$soak_result"
    echo "summary=$summary_path"
    echo "captured_frames_total=$frame_count"
    echo "rss_peak_kb=$rss_peak_kb"
    echo "route_replay_iterations=$route_replay_iterations"
    echo "route_replay_summary=${route_replay_summary:-none}"
    echo "route_replay_captured_frames=${route_replay_captured_frames:-0}"
    echo "first_mission_probe_iterations=$first_mission_probe_iterations"
    echo "first_mission_probe_summary=${first_mission_probe_summary:-none}"
    echo "first_mission_probe_captured_frames=${first_mission_probe_captured_frames:-0}"
    echo "first_mission_probe_enemy_attack_return_count=${first_mission_probe_enemy_attack_return_count:-0}"
  } >"$artifact_root/latest.txt" 2>/dev/null || true
  prune_soak_artifacts
  echo "[soak] durable artifacts: $artifact_run" >&2
  echo "[soak] durable summary: $summary_path" >&2
}

fail_probe() {
  soak_result="fail"
  soak_reason="$1"
  preserve_artifacts=1
  echo "$1" >&2
  tail -n "${CLASH95_SOAK_FAIL_TAIL_LINES:-260}" "$log_path" >&2 || true
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
  persist_soak_artifacts
  if [ "${CLASH95_KEEP_SMOKE_ARTIFACTS:-0}" = "1" ] || [ "$preserve_artifacts" = "1" ]; then
    echo "clash95 soak probe scratch artifacts: $soak_root" >&2
  else
    rm -rf "$soak_root"
  fi
}
trap cleanup EXIT

wait_for_log() {
  local pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_seconds="$SECONDS"

  echo "[soak] wait-log label=${label} timeout=${timeout_seconds}s pattern=${pattern}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$pattern" "$log_path"; then
      echo "[soak] wait-log-done label=${label}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "clash95 soak process exited while waiting for ${label}: $pattern"
    fi
    sleep 0.1
  done
  fail_probe "clash95 soak timed out waiting for ${label}: $pattern"
}

try_wait_for_log() {
  local pattern="$1"
  local timeout_seconds="${2:-2}"
  local start_seconds="$SECONDS"

  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$pattern" "$log_path"; then
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "clash95 soak process exited while waiting briefly for: $pattern"
    fi
    sleep 0.1
  done
  return 1
}

start_xvfb() {
  local display_number
  local xvfb_candidates

  for tool in Xvfb xdotool; do
    if ! command -v "$tool" >/dev/null 2>&1; then
      echo "clash95 soak probe skipped; missing $tool" >&2
      exit 77
    fi
  done

  if [ "${CLASH95_XVFB_DISPLAY_NUMBER:-}" ]; then
    xvfb_candidates="$CLASH95_XVFB_DISPLAY_NUMBER"
  else
    xvfb_candidates="$((1200 + RANDOM % 1200)) $((1200 + RANDOM % 1200)) $((1200 + RANDOM % 1200))"
  fi
  for display_number in $xvfb_candidates; do
    echo "[soak] trying Xvfb display :$display_number" >>"$log_path"
    Xvfb ":$display_number" -screen 0 "${CLASH95_XVFB_SCREEN:-800x600x24}" >"$soak_root/xvfb-$display_number.log" 2>&1 &
    xvfb_pid=$!
    sleep 1
    if kill -0 "$xvfb_pid" 2>/dev/null; then
      export DISPLAY=":$display_number"
      echo "[soak] using DISPLAY=$DISPLAY" >>"$log_path"
      return 0
    fi
    cat "$soak_root/xvfb-$display_number.log" >>"$log_path" 2>/dev/null || true
    xvfb_pid=""
  done
  echo "clash95 soak probe skipped; Xvfb did not start" >&2
  exit 77
}

find_window() {
  window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
  if [ -z "$window" ]; then
    fail_probe "clash95 soak could not find the SDL window"
  fi
  echo "[soak] found window: $window" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
}

host_click_at() {
  local x="$1"
  local y="$2"
  local hold="${3:-0.18}"
  local gap="${4:-0.40}"
  local label="${5:-click}"

  echo "[soak] host-click label=${label} at=${x},${y} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep 0.08
  xdotool mousedown 1
  sleep "$hold"
  xdotool mouseup 1
  input_pulses=$((input_pulses + 1))
  sleep "$gap"
}

check_latest_frame_nonblank() {
  local latest_frame
  local metrics_output

  latest_frame="$(latest_frame_path)"
  if [ -z "$latest_frame" ] || [ ! -f "$latest_frame" ]; then
    fail_probe "clash95 soak did not capture any frames"
  fi
  if ! metrics_output="$(python3 "$frame_metrics_tool" \
      --min-mean "${CLASH95_SOAK_MIN_FRAME_MEAN:-1}" \
      --min-nonblack "${CLASH95_SOAK_MIN_NONBLACK_PIXELS:-1000}" \
      --min-colors "${CLASH95_SOAK_MIN_UNIQUE_COLORS:-8}" \
      "$latest_frame" 2>&1)"; then
    {
      echo "[soak] final-frame-check frame=$latest_frame"
      printf '%s\n' "$metrics_output"
    } >>"$log_path"
    fail_probe "clash95 soak final frame failed nonblank visual check: $latest_frame"
  fi
  {
    echo "[soak] final-frame-check frame=$latest_frame"
    printf '%s\n' "$metrics_output"
  } >>"$log_path"
}

launch_bootstrap_with_world_scripts() {
  local timeout_seconds="$1"

  setsid timeout "${timeout_seconds}s" env \
    SDL_AUDIODRIVER=dummy \
    CLASH95_SKIP_BOOT_AVI=1 \
    CLASH95_HOST_CLICK_PULSE_READS="${CLASH95_HOST_CLICK_PULSE_READS:-4}" \
    CLASH95_TRACE_WORLD_CLICK="${CLASH95_TRACE_WORLD_CLICK:-1}" \
    CLASH95_TRACE_WORLD_INPUT_SCRIPT="${CLASH95_TRACE_WORLD_INPUT_SCRIPT:-1}" \
    CLASH95_WORLD_INPUT_SCRIPT="$world_input_script" \
    CLASH95_TRACE_BATTLE_INPUT_SCRIPT="${CLASH95_TRACE_BATTLE_INPUT_SCRIPT:-1}" \
    CLASH95_BATTLE_INPUT_SCRIPT="$battle_input_script" \
    CLASH95_INPUT_SCRIPT="$platform_input_script" \
    CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP="${CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP:-1}" \
    CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
    CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-0}" \
    CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_SOAK_FRAME_DUMP_LIMIT:-240}" \
    CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER="${CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER:-0}" \
    "$bootstrap_bin" >>"$log_path" 2>&1 &
  pid=$!
  echo "[soak] launched bootstrap pid=$pid scenario=$scenario duration=${duration_seconds}s" >>"$log_path"
}

run_main_menu_idle() {
  local end_seconds
  local pulse_index=0
  local x
  local y
  local timeout_seconds

  start_xvfb
  timeout_seconds=$((duration_seconds + ${CLASH95_SOAK_TIMEOUT_PADDING_SECONDS:-30}))
  launch_bootstrap_with_world_scripts "$timeout_seconds"

  sleep "${CLASH95_SOAK_POST_LAUNCH_WAIT:-2}"
  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 soak process exited during startup"
  fi

  find_window
  wait_for_log "${CLASH95_SOAK_MAIN_MENU_PATTERN:-[pcx] load path=gfx\\menu\\main.gfx}" "main-menu-load" 20

  end_seconds=$((SECONDS + duration_seconds))
  while [ "$SECONDS" -lt "$end_seconds" ]; do
    if ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "clash95 soak process exited before duration completed"
    fi
    pulse_index=$((pulse_index + 1))
    x=$((180 + (pulse_index % 5) * 70))
    y=$((150 + (pulse_index % 3) * 45))
    if xdotool mousemove --window "$window" "$x" "$y" >/dev/null 2>&1; then
      input_pulses=$((input_pulses + 1))
    else
      input_failures=$((input_failures + 1))
      echo "[soak] input-pulse-failed index=$pulse_index x=$x y=$y" >>"$log_path"
    fi
    frame_count="$(count_frames)"
    sample_rss
    echo "[soak] sample elapsed=$((duration_seconds - (end_seconds - SECONDS)))s frames=$frame_count rss_kb=$rss_last_kb input_pulses=$input_pulses input_failures=$input_failures" >>"$log_path"
    sleep "$sample_interval"
  done

  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 soak process exited at duration boundary"
  fi
  frame_count="$(count_frames)"
  if [ "$frame_count" -eq 0 ]; then
    fail_probe "clash95 soak captured no frames"
  fi
  check_latest_frame_nonblank
}

enter_first_mission_world_map() {
  local human_turn_pattern="${CLASH95_SOAK_FIRST_MISSION_HUMAN_TURN_PATTERN:-human_turn_enter idx=1 owner=0 tile=31,44}"
  local skip_count="${CLASH95_SOAK_FIRST_MISSION_SKIP_COUNT:-6}"
  local skip_index=1

  wait_for_log "${CLASH95_SOAK_MAIN_MENU_PATTERN:-[pcx] load path=gfx\\menu\\main.gfx}" "main-menu-load" 20
  sleep "${CLASH95_SOAK_MAIN_MENU_SETTLE_WAIT:-0.2}"
  host_click_at "${CLASH95_CLICK_CAMPAIGN_X:-245}" "${CLASH95_CLICK_CAMPAIGN_Y:-186}" 0.18 0.45 "campaign"
  host_click_at "${CLASH95_CLICK_CAMPAIGN_FIRST_X:-220}" "${CLASH95_CLICK_CAMPAIGN_FIRST_Y:-298}" 0.18 0.45 "campaign-first"

  while [ "$skip_index" -le "$skip_count" ]; do
    host_click_at "${CLASH95_CLICK_SKIP_X:-320}" "${CLASH95_CLICK_SKIP_Y:-240}" 0.12 0.45 "mission-skip-${skip_index}"
    if try_wait_for_log "$human_turn_pattern" "${CLASH95_SOAK_FIRST_MISSION_SKIP_WAIT_SLICE:-2}"; then
      echo "[soak] human-turn-detected-after-skip=$skip_index" >>"$log_path"
      break
    fi
    skip_index=$((skip_index + 1))
  done

  wait_for_log "$human_turn_pattern" "first-mission-human-turn" "${CLASH95_SOAK_FIRST_MISSION_HUMAN_TURN_TIMEOUT:-25}"
  sleep "${CLASH95_SOAK_WORLD_SETTLE_WAIT:-0.5}"
  check_latest_frame_nonblank
}

append_world_input_pulse() {
  local dx="$1"
  local dy="$2"
  local left="${3:-0}"
  local right="${4:-0}"
  local reads="${5:-12}"
  local label="${6:-world-pulse}"

  printf 'pulse %s %s %s %s %s\n' "$dx" "$dy" "$left" "$right" "$reads" >>"$world_input_script"
  input_pulses=$((input_pulses + 1))
  echo "[soak] world-input-pulse label=${label} delta=${dx},${dy} buttons=${left},${right} reads=${reads}" >>"$log_path"
}

run_world_map_pan() {
  local end_seconds
  local pulse_index=0
  local timeout_seconds
  local reads="${CLASH95_SOAK_WORLD_PULSE_READS:-24}"

  start_xvfb
  timeout_seconds=$((duration_seconds + ${CLASH95_SOAK_TIMEOUT_PADDING_SECONDS:-90}))
  launch_bootstrap_with_world_scripts "$timeout_seconds"

  sleep "${CLASH95_SOAK_POST_LAUNCH_WAIT:-2}"
  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 world-map soak process exited during startup"
  fi
  find_window
  enter_first_mission_world_map

  end_seconds=$((SECONDS + duration_seconds))
  while [ "$SECONDS" -lt "$end_seconds" ]; do
    if ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "clash95 world-map soak process exited before duration completed"
    fi
    pulse_index=$((pulse_index + 1))
    case $((pulse_index % 4)) in
      0) append_world_input_pulse 620 0 0 0 "$reads" "pan-right" ;;
      1) append_world_input_pulse 0 430 0 0 "$reads" "pan-down" ;;
      2) append_world_input_pulse -620 0 0 0 "$reads" "pan-left" ;;
      3) append_world_input_pulse 0 -430 0 0 "$reads" "pan-up" ;;
    esac
    frame_count="$(count_frames)"
    sample_rss
    echo "[soak] sample elapsed=$((duration_seconds - (end_seconds - SECONDS)))s frames=$frame_count rss_kb=$rss_last_kb input_pulses=$input_pulses input_failures=$input_failures" >>"$log_path"
    sleep "$sample_interval"
  done

  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 world-map soak process exited at duration boundary"
  fi
  frame_count="$(count_frames)"
  if [ "$frame_count" -eq 0 ]; then
    fail_probe "clash95 world-map soak captured no frames"
  fi
  check_latest_frame_nonblank
}

run_castle_economy() {
  local end_seconds
  local timeout_seconds

  export CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER="${CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER:-1}"
  start_xvfb
  timeout_seconds=$((duration_seconds + ${CLASH95_SOAK_TIMEOUT_PADDING_SECONDS:-120}))
  launch_bootstrap_with_world_scripts "$timeout_seconds"

  sleep "${CLASH95_SOAK_POST_LAUNCH_WAIT:-2}"
  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 castle/economy soak process exited during startup"
  fi
  find_window
  enter_first_mission_world_map

  host_click_at "${CLASH95_CLICK_NEXT_BUILDING_X:-544}" "${CLASH95_CLICK_NEXT_BUILDING_Y:-400}" 0.22 0.80 "next-building"
  sleep "${CLASH95_SOAK_CASTLE_AFTER_NEXT_BUILDING_WAIT:-1.0}"
  host_click_at "${CLASH95_CLICK_BUILDING_TILE_X:-320}" "${CLASH95_CLICK_BUILDING_TILE_Y:-240}" 0.25 1.50 "building-tile"
  wait_for_log "[castle] first_present building_idx=0" "castle-first-present" 30
  wait_for_log "[castle] hotspot pixel=255" "castle-economy-hotspot" 5
  check_latest_frame_nonblank

  host_click_at "${CLASH95_CLICK_CASTLE_ECONOMY_X:-548}" "${CLASH95_CLICK_CASTLE_ECONOMY_Y:-412}" 0.25 2.0 "castle-economy"
  wait_for_log "[economy] first_present building_idx=0" "economy-first-present" 20
  sleep "${CLASH95_SOAK_CASTLE_ECONOMY_PRESENT_WAIT:-0.8}"
  check_latest_frame_nonblank

  host_click_at \
    "${CLASH95_CLICK_ECONOMY_LIST_NEXT_X:-475}" \
    "${CLASH95_CLICK_ECONOMY_LIST_NEXT_Y:-350}" \
    "${CLASH95_CLICK_ECONOMY_LIST_NEXT_HOLD:-0.08}" \
    "${CLASH95_CLICK_ECONOMY_LIST_NEXT_GAP:-0.90}" \
    "economy-list-next"
  wait_for_log "[economy] list_next" "economy-list-next" 10
  check_latest_frame_nonblank

  host_click_at "${CLASH95_CLICK_ECONOMY_BACK_X:-90}" "${CLASH95_CLICK_ECONOMY_BACK_Y:-451}" 0.22 1.20 "economy-back"
  wait_for_log "[economy] back exit_signal=1" "economy-back-signal" 10
  wait_for_log "[economy] exit building_idx=0" "economy-exit" 10

  end_seconds=$((SECONDS + duration_seconds))
  while [ "$SECONDS" -lt "$end_seconds" ]; do
    if ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "clash95 castle/economy soak process exited before duration completed"
    fi
    frame_count="$(count_frames)"
    sample_rss
    echo "[soak] sample elapsed=$((duration_seconds - (end_seconds - SECONDS)))s frames=$frame_count rss_kb=$rss_last_kb input_pulses=$input_pulses input_failures=$input_failures" >>"$log_path"
    sleep "$sample_interval"
  done

  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "clash95 castle/economy soak process exited at duration boundary"
  fi
  frame_count="$(count_frames)"
  if [ "$frame_count" -eq 0 ]; then
    fail_probe "clash95 castle/economy soak captured no frames"
  fi
  check_latest_frame_nonblank
}

run_campaign_route_replay() {
  local mission_id="${CLASH95_SOAK_ROUTE_MISSION_ID:-04}"
  local route_env_path="${CLASH95_SOAK_ROUTE_ENV_FILE:-$repo_root/tests/first_campaign_arc_routes/mission_${mission_id}.env}"
  local end_seconds

  if [ ! -f "$repo_root/tests/run_campaign_route_regression.sh" ]; then
    fail_probe "campaign route replay soak cannot find run_campaign_route_regression.sh"
  fi
  if [ ! -f "$route_env_path" ]; then
    fail_probe "campaign route replay soak route env does not exist: $route_env_path"
  fi

  route_replay_mission_id="$mission_id"
  mkdir -p "$artifact_run/route-runs/mission-$mission_id"
  end_seconds=$((SECONDS + duration_seconds))
  while [ "$route_replay_iterations" -eq 0 ] || [ "$SECONDS" -lt "$end_seconds" ]; do
    route_replay_iterations=$((route_replay_iterations + 1))
    echo "[soak] route-replay iteration=$route_replay_iterations mission=$mission_id" >>"$log_path"
    CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
    CLASH95_CAMPAIGN_ROUTE_DURABLE_ARTIFACT_DIR="$artifact_run/route-runs/mission-$mission_id" \
    CLASH95_ARTIFACT_PRUNE_AFTER_RUN="${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}" \
      bash "$repo_root/tests/run_campaign_route_regression.sh" "$bootstrap_bin" "$mission_id" "$route_env_path" >>"$log_path" 2>&1 \
      || fail_probe "campaign route replay soak failed on iteration $route_replay_iterations for mission $mission_id"
    update_route_replay_summary
    if [ "${CLASH95_SOAK_ROUTE_REQUIRE_NESTED_SUMMARY:-1}" = "1" ] && [ ! -f "$route_replay_summary" ]; then
      fail_probe "campaign route replay soak did not retain a nested route summary for mission $mission_id"
    fi
    if [ "${CLASH95_SOAK_ROUTE_REQUIRE_NESTED_FRAMES:-1}" = "1" ] && [ "${route_replay_captured_frames:-0}" = "0" ]; then
      fail_probe "campaign route replay soak nested route summary has no captured frames for mission $mission_id"
    fi
    if [ "$SECONDS" -ge "$end_seconds" ]; then
      break
    fi
  done
  echo "[soak] route-replay-complete iterations=$route_replay_iterations mission=$mission_id nested_summary=${route_replay_summary:-none}" >>"$log_path"
}

run_first_mission_attack_replay() {
  local end_seconds

  if [ ! -f "$repo_root/tests/run_first_mission_attack_probe.sh" ]; then
    fail_probe "first-mission attack soak cannot find run_first_mission_attack_probe.sh"
  fi

  mkdir -p "$artifact_run/first-mission-attack"
  end_seconds=$((SECONDS + duration_seconds))
  while [ "$first_mission_probe_iterations" -eq 0 ] || [ "$SECONDS" -lt "$end_seconds" ]; do
    first_mission_probe_iterations=$((first_mission_probe_iterations + 1))
    echo "[soak] first-mission-attack iteration=$first_mission_probe_iterations" >>"$log_path"
    CLASH95_ENABLE_REAL_INPUT_SMOKES=1 \
    CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR="$artifact_run/first-mission-attack" \
    CLASH95_ARTIFACT_PRUNE_AFTER_RUN="${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}" \
      bash "$repo_root/tests/run_first_mission_attack_probe.sh" "$bootstrap_bin" >>"$log_path" 2>&1 \
      || fail_probe "first-mission attack soak failed on iteration $first_mission_probe_iterations"
    update_first_mission_probe_summary
    if [ "${CLASH95_SOAK_FIRST_MISSION_REQUIRE_NESTED_SUMMARY:-1}" = "1" ] && [ ! -f "$first_mission_probe_summary" ]; then
      fail_probe "first-mission attack soak did not retain a nested probe summary"
    fi
    if [ "${CLASH95_SOAK_FIRST_MISSION_REQUIRE_NESTED_FRAMES:-1}" = "1" ] && [ "${first_mission_probe_captured_frames:-0}" = "0" ]; then
      fail_probe "first-mission attack soak nested probe summary has no captured frames"
    fi
    if [ "$SECONDS" -ge "$end_seconds" ]; then
      break
    fi
  done
  echo "[soak] first-mission-attack-complete iterations=$first_mission_probe_iterations nested_summary=${first_mission_probe_summary:-none}" >>"$log_path"
}

case "$scenario" in
  main-menu-idle)
    run_main_menu_idle
    ;;
  world-map-pan)
    run_world_map_pan
    ;;
  castle-economy)
    run_castle_economy
    ;;
  first-mission-attack)
    run_first_mission_attack_replay
    ;;
  campaign-route)
    run_campaign_route_replay
    ;;
  *)
    echo "unknown CLASH95_SOAK_SCENARIO: $scenario" >&2
    echo "supported scenarios: main-menu-idle, world-map-pan, castle-economy, first-mission-attack, campaign-route" >&2
    exit 2
    ;;
esac

soak_result="pass"
soak_reason="none"
echo "[soak] scenario completed: $scenario" >&2
