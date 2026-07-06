#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

if [ "${CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE:-0}" != "1" ]; then
  echo "multiplayer map probe skipped; set CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1" >&2
  exit 77
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "multiplayer map probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

for tool in Xvfb timeout grep find sort tail sed awk python3 date du cp mkdir wc ps; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "multiplayer map probe skipped; missing $tool" >&2
    exit 77
  fi
done

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
frame_metrics_tool="$repo_root/tests/frame_metrics.py"
if [ ! -f "$frame_metrics_tool" ]; then
  echo "multiplayer map probe missing frame metrics helper: $frame_metrics_tool" >&2
  exit 2
fi

artifact_root="${CLASH95_MULTIPLAYER_MAP_ARTIFACT_DIR:-$repo_root/artifacts/multiplayer-maps}"
probe_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-multiplayer-map-probe.XXXXXX")"
xvfb_pid=""
xvfb_log="$probe_root/xvfb.log"
pid=""
current_scratch=""
current_log_path=""
current_frame_prefix=""
current_artifact_run=""
current_map_root=""
current_map_id=""
current_map_file=""
current_route_arg=""

is_unsigned_integer() {
  case "${1:-}" in
    ""|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
}

probe_seconds="${CLASH95_MULTIPLAYER_MAP_PROBE_SECONDS:-6}"
startup_timeout="${CLASH95_MULTIPLAYER_MAP_STARTUP_TIMEOUT_SECONDS:-30}"
timeout_padding="${CLASH95_MULTIPLAYER_MAP_TIMEOUT_PADDING_SECONDS:-25}"
frame_dump_limit="${CLASH95_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT:-96}"
max_copied_frames="${CLASH95_MULTIPLAYER_MAP_MAX_COPIED_FRAMES:-24}"
max_log_bytes="${CLASH95_MULTIPLAYER_MAP_MAX_LOG_BYTES:-4000000}"
sample_interval="${CLASH95_MULTIPLAYER_MAP_SAMPLE_INTERVAL_SECONDS:-5}"

for numeric_value in "$probe_seconds" "$startup_timeout" "$timeout_padding" "$frame_dump_limit" "$max_copied_frames" "$max_log_bytes" "$sample_interval"; do
  if ! is_unsigned_integer "$numeric_value"; then
    echo "multiplayer map probe numeric settings must be unsigned integers, got: $numeric_value" >&2
    exit 2
  fi
done
if [ "$sample_interval" = "0" ]; then
  echo "CLASH95_MULTIPLAYER_MAP_SAMPLE_INTERVAL_SECONDS must be positive" >&2
  exit 2
fi

copied_frames=0
captured_frames_total=0
frames_truncated=0
durable_log_original_bytes=0
durable_log_bytes=0
durable_log_truncated=0
latest_metrics_output=""
progression_metrics_output=""
latest_frame_basename=""
runtime_sample_count=0
runtime_frame_count=0
rss_last_kb=0
rss_peak_kb=0

cleanup_processes() {
  if [ -n "${pid:-}" ]; then
    kill -TERM "-$pid" 2>/dev/null || true
    sleep 0.2
    kill -KILL "-$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true
    pid=""
  fi
  if [ -n "${xvfb_pid:-}" ]; then
    kill "$xvfb_pid" 2>/dev/null || true
    wait "$xvfb_pid" 2>/dev/null || true
    xvfb_pid=""
  fi
}

cleanup() {
  cleanup_processes
  if [ "${CLASH95_KEEP_MULTIPLAYER_MAP_SCRATCH:-0}" = "1" ]; then
    echo "multiplayer map probe scratch: $probe_root" >&2
  else
    rm -rf "$probe_root"
  fi
}
trap cleanup EXIT

wait_for_log() {
  local pattern="$1"
  local label="$2"
  local timeout_seconds="$3"
  local start_seconds="$SECONDS"

  echo "[multiplayer-map] wait-for-log label=$label" >>"$current_log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -Fq "$pattern" "$current_log_path"; then
      echo "[multiplayer-map] wait-for-log-done label=$label" >>"$current_log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      return 1
    fi
    sleep 0.1
  done
  return 1
}

latest_frame_path() {
  find "$current_scratch" -maxdepth 1 -type f -name 'frame-*.bmp' -printf '%T@ %p\n' \
    | sort -n \
    | tail -n 1 \
    | sed 's/^[^ ]* //'
}

count_current_frames() {
  local captured_frame
  local count=0

  for captured_frame in "$current_frame_prefix"-*.bmp; do
    if [ -f "$captured_frame" ]; then
      count=$((count + 1))
    fi
  done
  printf '%s' "$count"
}

sample_process_group_rss() {
  local rss_value
  local max_rss=0

  if [ -z "${pid:-}" ]; then
    return 0
  fi
  while IFS= read -r rss_value; do
    if is_unsigned_integer "$rss_value" && [ "$rss_value" -gt "$max_rss" ]; then
      max_rss="$rss_value"
    fi
  done < <(ps -o rss= -g "$pid" 2>/dev/null || true)
  if [ "$max_rss" -gt 0 ]; then
    rss_last_kb="$max_rss"
    if [ "$max_rss" -gt "$rss_peak_kb" ]; then
      rss_peak_kb="$max_rss"
    fi
  fi
}

copy_bounded_log() {
  local destination="$1"
  local tail_bytes

  durable_log_original_bytes="$(wc -c <"$current_log_path" | awk '{ print $1 + 0 }')"
  durable_log_truncated=0
  if [ "$max_log_bytes" = "0" ] || [ "$durable_log_original_bytes" -le "$max_log_bytes" ]; then
    cp "$current_log_path" "$destination"
  else
    durable_log_truncated=1
    tail_bytes=$((max_log_bytes / 2))
    if [ "$tail_bytes" -lt 1 ]; then
      tail_bytes=1
    fi
    {
      echo "[multiplayer-map] log truncated original_bytes=$durable_log_original_bytes max_bytes=$max_log_bytes"
      echo "[multiplayer-map] log head"
      sed -n '1,240p' "$current_log_path"
      echo "[multiplayer-map] log tail"
      tail -c "$tail_bytes" "$current_log_path"
    } >"$destination"
  fi
  durable_log_bytes="$(wc -c <"$destination" | awk '{ print $1 + 0 }')"
}

copy_sampled_frames() {
  local frames_dir="$1"
  local -a frames=()
  local total
  local head_count
  local tail_count
  local index

  mkdir -p "$frames_dir"
  mapfile -t frames < <(find "$current_scratch" -maxdepth 1 -type f -name 'frame-*.bmp' | sort)
  total="${#frames[@]}"
  captured_frames_total="$total"
  copied_frames=0
  frames_truncated=0

  if [ "$total" -eq 0 ] || [ "$max_copied_frames" = "0" ]; then
    return 0
  fi

  if [ "$total" -le "$max_copied_frames" ]; then
    for index in "${!frames[@]}"; do
      cp "${frames[$index]}" "$frames_dir/$(basename "${frames[$index]}")"
      copied_frames=$((copied_frames + 1))
    done
    return 0
  fi

  frames_truncated=1
  head_count=$((max_copied_frames / 2))
  tail_count=$((max_copied_frames - head_count))
  for ((index = 0; index < head_count; ++index)); do
    cp "${frames[$index]}" "$frames_dir/$(basename "${frames[$index]}")"
    copied_frames=$((copied_frames + 1))
  done
  for ((index = total - tail_count; index < total; ++index)); do
    cp "${frames[$index]}" "$frames_dir/$(basename "${frames[$index]}")"
    copied_frames=$((copied_frames + 1))
  done
}

marker_count() {
  local pattern="$1"

  grep -Fc "$pattern" "$current_log_path" 2>/dev/null || true
}

persist_current_artifacts() {
  local status="$1"
  local message="$2"
  local summary_path
  local artifact_bytes

  if [ -z "$current_artifact_run" ] || [ -z "$current_log_path" ]; then
    return 0
  fi

  mkdir -p "$current_artifact_run"
  copy_bounded_log "$current_artifact_run/multiplayer-map.log"
  copy_sampled_frames "$current_artifact_run/frames"
  artifact_bytes="$(du -sb "$current_artifact_run" 2>/dev/null | awk '{ print $1 + 0 }')"
  summary_path="$current_artifact_run/summary.txt"
  {
    echo "status=$status"
    echo "message=$message"
    echo "map_id=$current_map_id"
    echo "map_file=$current_map_file"
    echo "route_arg=$current_route_arg"
    echo "artifact_run=$current_artifact_run"
    echo "artifact_bytes=$artifact_bytes"
    echo "probe_seconds=$probe_seconds"
    echo "startup_timeout_seconds=$startup_timeout"
    echo "frame_dump_limit=$frame_dump_limit"
    echo "sample_interval_seconds=$sample_interval"
    echo "runtime_sample_count=$runtime_sample_count"
    echo "runtime_frame_count=$runtime_frame_count"
    echo "rss_last_kb=$rss_last_kb"
    echo "rss_peak_kb=$rss_peak_kb"
    echo "captured_frames_total=$captured_frames_total"
    echo "copied_frames=$copied_frames"
    echo "frames_truncated=$frames_truncated"
    echo "durable_log_original_bytes=$durable_log_original_bytes"
    echo "durable_log_bytes=$durable_log_bytes"
    echo "durable_log_truncated=$durable_log_truncated"
    echo "direct_load_marker_count=$(marker_count '[bootstrap] direct-mission-load')"
    echo "direct_playgame_marker_count=$(marker_count '[bootstrap] direct-mission-playgame')"
    echo "direct_playgame_return_marker_count=$(marker_count '[bootstrap] direct-mission-playgame-return')"
    echo "segmentation_fault_count=$(marker_count 'Segmentation fault')"
    echo "aborted_count=$(marker_count 'Aborted')"
    echo "latest_frame_basename=$latest_frame_basename"
    if [ -n "$latest_frame_basename" ] && [ "$max_copied_frames" != "0" ]; then
      echo "latest_frame_retained=frames/$latest_frame_basename"
    fi
    echo "latest_metrics_begin"
    printf '%s\n' "$latest_metrics_output"
    echo "latest_metrics_end"
    if [ -n "$progression_metrics_output" ]; then
      echo "progression_metrics_begin"
      printf '%s\n' "$progression_metrics_output"
      echo "progression_metrics_end"
    fi
  } >"$summary_path"
  printf '%s\n' "$summary_path" >"$current_map_root/latest.txt"
}

fail_probe() {
  local message="$1"

  echo "$message" >&2
  if [ -n "${current_log_path:-}" ] && [ -f "$current_log_path" ]; then
    tail -n "${CLASH95_MULTIPLAYER_MAP_FAIL_TAIL_LINES:-240}" "$current_log_path" >&2 || true
  fi
  persist_current_artifacts "fail" "$message"
  if [ -n "$current_artifact_run" ]; then
    echo "multiplayer map probe artifacts: $current_artifact_run" >&2
  fi
  exit 1
}

start_xvfb() {
  local display_number
  local attempt

  for attempt in 1 2 3 4 5; do
    display_number="${CLASH95_XVFB_DISPLAY_NUMBER:-$((240 + RANDOM % 3000))}"
    : >"$xvfb_log"
    Xvfb ":$display_number" -screen 0 "${CLASH95_XVFB_SCREEN:-800x600x24}" >"$xvfb_log" 2>&1 &
    xvfb_pid=$!
    sleep 0.8
    if kill -0 "$xvfb_pid" 2>/dev/null; then
      export DISPLAY=":$display_number"
      return 0
    fi
    wait "$xvfb_pid" 2>/dev/null || true
    xvfb_pid=""
    if [ -n "${CLASH95_XVFB_DISPLAY_NUMBER:-}" ]; then
      break
    fi
  done

  echo "multiplayer map probe skipped; Xvfb did not start" >&2
  cat "$xvfb_log" >&2 || true
  exit 77
}

stop_current_game() {
  if [ -z "${pid:-}" ]; then
    return 0
  fi
  kill -TERM "-$pid" 2>/dev/null || true
  sleep 0.5
  if kill -0 "$pid" 2>/dev/null; then
    kill -KILL "-$pid" 2>/dev/null || true
  fi
  wait "$pid" 2>/dev/null || true
  pid=""
}

check_log_for_crash() {
  if grep -Eq 'Segmentation fault|Aborted|core dumped|Trace/breakpoint trap' "$current_log_path"; then
    fail_probe "multiplayer map probe reported a crash for map $current_map_id"
  fi
}

check_latest_frame_nonblank() {
  local latest_frame

  latest_frame="$(latest_frame_path)"
  if [ -z "$latest_frame" ] || [ ! -f "$latest_frame" ]; then
    fail_probe "multiplayer map probe captured no frames for map $current_map_id"
  fi
  latest_frame_basename="$(basename "$latest_frame")"

  if ! latest_metrics_output="$(python3 "$frame_metrics_tool" \
      --min-mean "${CLASH95_MULTIPLAYER_MAP_MIN_FRAME_MEAN:-1}" \
      --min-nonblack "${CLASH95_MULTIPLAYER_MAP_MIN_NONBLACK_PIXELS:-1000}" \
      --min-colors "${CLASH95_MULTIPLAYER_MAP_MIN_COLORS:-8}" \
      "$latest_frame" 2>&1)"; then
    fail_probe "multiplayer map probe captured a blank/low-detail frame for map $current_map_id: $latest_frame"
  fi
  printf '%s\n' "$latest_metrics_output" >>"$current_log_path"
}

check_optional_frame_progression() {
  local -a frames=()
  local first_frame
  local latest_frame

  if [ "${CLASH95_MULTIPLAYER_MAP_REQUIRE_FRAME_PROGRESSION:-0}" != "1" ]; then
    return 0
  fi

  mapfile -t frames < <(find "$current_scratch" -maxdepth 1 -type f -name 'frame-*.bmp' | sort)
  if [ "${#frames[@]}" -lt 2 ]; then
    fail_probe "multiplayer map probe needs at least two frames for progression check on map $current_map_id"
  fi
  first_frame="${frames[0]}"
  latest_frame="${frames[${#frames[@]} - 1]}"
  if ! progression_metrics_output="$(python3 "$frame_metrics_tool" \
      --min-diff "${CLASH95_MULTIPLAYER_MAP_MIN_FRAME_DIFF:-0.05}" \
      "$first_frame" "$latest_frame" 2>&1)"; then
    fail_probe "multiplayer map probe frame progression check failed for map $current_map_id"
  fi
  printf '%s\n' "$progression_metrics_output" >>"$current_log_path"
}

hold_map_runtime() {
  local end_seconds
  local remaining_seconds

  end_seconds=$((SECONDS + probe_seconds))
  while [ "$SECONDS" -lt "$end_seconds" ]; do
    if ! kill -0 "$pid" 2>/dev/null; then
      fail_probe "multiplayer map probe process exited during liveness window for map $current_map_id"
    fi
    runtime_sample_count=$((runtime_sample_count + 1))
    runtime_frame_count="$(count_current_frames)"
    sample_process_group_rss
    echo "[multiplayer-map] sample map_id=$current_map_id sample=$runtime_sample_count frames=$runtime_frame_count rss_kb=$rss_last_kb" >>"$current_log_path"
    remaining_seconds=$((end_seconds - SECONDS))
    if [ "$remaining_seconds" -le 0 ]; then
      break
    fi
    if [ "$remaining_seconds" -lt "$sample_interval" ]; then
      sleep "$remaining_seconds"
    else
      sleep "$sample_interval"
    fi
  done
}

prune_multiplayer_artifacts() {
  if [ "${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}" != "1" ]; then
    return 0
  fi
  if [ ! -f "$repo_root/tests/prune_artifacts.sh" ]; then
    return 0
  fi

  CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS="$current_map_root${CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS:+:$CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS}" \
  CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP="${CLASH95_MULTIPLAYER_MAP_KEEP_RUNS:-8}" \
  CLASH95_ARTIFACT_PRUNE_MAX_BYTES="${CLASH95_ARTIFACT_PRUNE_MAX_BYTES:-805306368}" \
    bash "$repo_root/tests/prune_artifacts.sh" --apply --quiet >&2 || true
}

run_one_map() {
  local map_id="$1"
  local map_label
  local run_id
  local timeout_seconds

  map_label="$(printf '%02d' "$map_id")"
  run_id="$(date -u +%Y%m%dT%H%M%SZ)-$$"
  current_map_id="$map_id"
  current_map_file="multi$((map_id + 1)).map"
  current_route_arg="/A${map_id}"
  current_map_root="$artifact_root/map-$map_label"
  current_artifact_run="$current_map_root/$run_id"
  current_scratch="$probe_root/map-$map_label"
  current_log_path="$current_scratch/multiplayer-map.log"
  current_frame_prefix="$current_scratch/frame"
  latest_metrics_output=""
  progression_metrics_output=""
  latest_frame_basename=""
  runtime_sample_count=0
  runtime_frame_count=0
  rss_last_kb=0
  rss_peak_kb=0
  mkdir -p "$current_scratch" "$current_map_root"
  : >"$current_log_path"

  {
    echo "[multiplayer-map] map_id=$current_map_id map_file=$current_map_file route=$current_route_arg"
    echo "[multiplayer-map] display=$DISPLAY artifact_run=$current_artifact_run"
  } >>"$current_log_path"

  timeout_seconds=$((probe_seconds + startup_timeout + timeout_padding))
  setsid timeout "${timeout_seconds}s" env \
    SDL_AUDIODRIVER=dummy \
    CLASH95_SKIP_BOOT_AVI=1 \
    CLASH95_TRACE_BOOTSTRAP=1 \
    CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$current_frame_prefix" \
    CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-0}" \
    CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="$frame_dump_limit" \
    "$bootstrap_bin" "$current_route_arg" >>"$current_log_path" 2>&1 &
  pid=$!
  echo "[multiplayer-map] launched pid=$pid timeout=${timeout_seconds}s" >>"$current_log_path"

  if ! wait_for_log "[bootstrap] direct-mission-load" "direct-mission-load" "$startup_timeout"; then
    fail_probe "multiplayer map probe timed out before direct map load for map $current_map_id"
  fi
  if ! wait_for_log "[bootstrap] direct-mission-playgame" "direct-mission-playgame" "$startup_timeout"; then
    fail_probe "multiplayer map probe timed out before PlayGame for map $current_map_id"
  fi

  hold_map_runtime
  if ! kill -0 "$pid" 2>/dev/null; then
    fail_probe "multiplayer map probe process exited before liveness window for map $current_map_id"
  fi
  runtime_frame_count="$(count_current_frames)"

  stop_current_game
  check_log_for_crash
  check_latest_frame_nonblank
  check_optional_frame_progression
  persist_current_artifacts "pass" "loaded $current_map_file through direct all-AI multiplayer route"
  prune_multiplayer_artifacts
  echo "multiplayer map probe passed map_id=$current_map_id artifact=$current_artifact_run"

  rm -rf "$current_scratch"
  current_scratch=""
  current_log_path=""
}

map_ids_raw="${CLASH95_MULTIPLAYER_MAP_IDS:-0}"
map_ids_raw="${map_ids_raw//,/ }"
map_ids_raw="${map_ids_raw//:/ }"
map_ids=()
for map_id in $map_ids_raw; do
  if ! is_unsigned_integer "$map_id"; then
    echo "multiplayer map id must be an unsigned integer, got: $map_id" >&2
    exit 2
  fi
  if [ "$map_id" -gt 10 ]; then
    echo "multiplayer map id out of recovered menu range 0..10: $map_id" >&2
    exit 2
  fi
  map_ids+=( "$map_id" )
done
if [ "${#map_ids[@]}" -eq 0 ]; then
  echo "multiplayer map probe needs at least one map id" >&2
  exit 2
fi

start_xvfb
for map_id in "${map_ids[@]}"; do
  run_one_map "$map_id"
done
