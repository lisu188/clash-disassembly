#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 2 ] || [ "$#" -gt 3 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap NN [route-env-file]" >&2
  exit 2
fi

bootstrap_bin="$1"
mission_id="$2"
route_env_path="${3:-${CLASH95_CAMPAIGN_ROUTE_ENV_FILE:-}}"

case "$mission_id" in
  [0-9][0-9]) ;;
  *)
    echo "campaign route script smoke mission id must be two digits, got: $mission_id" >&2
    exit 2
    ;;
esac
mission_number=$((10#$mission_id))
if [ "$mission_number" -lt 0 ] || [ "$mission_number" -gt 19 ]; then
  echo "campaign route script smoke mission id must be in 00..19, got: $mission_id" >&2
  exit 2
fi

if [ ! -x "$bootstrap_bin" ]; then
  echo "campaign route script smoke binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

if [ -n "$route_env_path" ]; then
  if [ ! -f "$route_env_path" ]; then
    echo "campaign route script smoke route env does not exist: $route_env_path" >&2
    exit 2
  fi
  set -a
  # shellcheck source=/dev/null
  . "$route_env_path"
  set +a
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
export CLASH95_ARTIFACT_PRUNE_AFTER_RUN="${CLASH95_ARTIFACT_PRUNE_AFTER_RUN:-1}"
export CLASH95_ARTIFACT_PRUNE_MAX_BYTES="${CLASH95_ARTIFACT_PRUNE_MAX_BYTES:-805306368}"
frame_metrics_tool="$repo_root/tests/frame_metrics.py"
route_script="${CLASH95_CAMPAIGN_ROUTE_SCRIPT_FILE:-}"
if [ -z "$route_script" ]; then
  echo "campaign route script smoke requires CLASH95_CAMPAIGN_ROUTE_SCRIPT_FILE" >&2
  exit 2
fi
case "$route_script" in
  /*) ;;
  *) route_script="$repo_root/$route_script" ;;
esac
if [ ! -f "$route_script" ]; then
  echo "campaign route script smoke route script does not exist: $route_script" >&2
  exit 2
fi

for tool in Xvfb xdotool timeout grep tail wc awk head cp mkdir find sort; do
  if ! command -v "$tool" >/dev/null 2>&1; then
    echo "campaign route script smoke skipped; missing $tool" >&2
    exit 77
  fi
done

smoke_root="$(mktemp -d "${TMPDIR:-/tmp}/clash95-campaign-route-${mission_id}.XXXXXX")"
log_path="$smoke_root/campaign-route-${mission_id}.log"
frame_prefix="$smoke_root/frame"
world_input_script="$smoke_root/world-input.txt"
platform_input_script="$smoke_root/platform-input.txt"
battle_input_script="$smoke_root/battle-input.txt"
expected_log_file="$smoke_root/expected-logs.txt"
pid=""
xvfb_pid=""
window=""
preserve_artifacts=0
route_input_step=0
last_wait_log_any_pattern=""
last_wait_log_any_mark=""
route_runtime_selected_unit=""
declare -A marked_log_counts=()
declare -A marked_log_patterns=()
: >"$log_path"
: >"$world_input_script"
: >"$platform_input_script"
: >"$battle_input_script"
: >"$expected_log_file"

fail_smoke() {
  local message="$1"

  echo "[campaign-route] failure message=${message}" >>"$log_path" 2>/dev/null || true
  echo "$message" >&2
  write_visual_failure_montage || true
  if [ "${CLASH95_CAMPAIGN_ROUTE_FAIL_FULL_LOG:-0}" = "1" ]; then
    cat "$log_path" >&2 || true
  else
    tail -n "${CLASH95_CAMPAIGN_ROUTE_FAIL_TAIL_LINES:-320}" "$log_path" >&2 || true
  fi
  preserve_artifacts=1
  exit 1
}

collect_presented_frames_by_mtime() {
  local destination_name="$1"
  local -n destination_ref="$destination_name"
  local frame_dir="${frame_prefix%/*}"
  local frame_name="${frame_prefix##*/}"
  local timestamped_path

  destination_ref=()
  while IFS= read -r -d '' timestamped_path; do
    destination_ref+=( "${timestamped_path#* }" )
  done < <(
    find "$frame_dir" -maxdepth 1 -type f -name "${frame_name}-*.bmp" -printf '%T@ %p\0' |
      sort -z -n
  )
}

latest_frame_path() {
  local -a captured_frames=()

  collect_presented_frames_by_mtime captured_frames
  if [ "${#captured_frames[@]}" -gt 0 ]; then
    printf '%s' "${captured_frames[$((${#captured_frames[@]} - 1))]}"
  fi
}

write_visual_failure_montage() {
  local montage_path="$smoke_root/visual-failure-montage.ppm"
  local max_frames="${CLASH95_CAMPAIGN_ROUTE_MONTAGE_MAX_FRAMES:-48}"
  local head_count="${CLASH95_CAMPAIGN_ROUTE_MONTAGE_FRAME_HEAD_COUNT:-8}"
  local checkpoint_budget=0
  local presented_budget=0
  local -a visual_frames=()
  local -a presented_frames=()
  local -a checkpoint_frames=()

  if ! command -v python3 >/dev/null 2>&1 || [ ! -f "$frame_metrics_tool" ]; then
    return 0
  fi
  if ! is_unsigned_integer "$max_frames" || [ "$max_frames" = "0" ]; then
    return 0
  fi
  if ! is_unsigned_integer "$head_count"; then
    head_count=8
  fi
  collect_presented_frames_by_mtime presented_frames
  shopt -s nullglob
  checkpoint_frames=( "$smoke_root"/checkpoint-*.bmp )
  shopt -u nullglob
  if [ "${#checkpoint_frames[@]}" -gt 0 ]; then
    checkpoint_budget=$((max_frames / 4))
    if [ "$checkpoint_budget" -lt 1 ]; then
      checkpoint_budget=1
    fi
    presented_budget=$((max_frames - checkpoint_budget))
  else
    presented_budget="$max_frames"
  fi
  sample_frame_array presented_frames visual_frames "$presented_budget" "$head_count"
  sample_frame_array checkpoint_frames visual_frames "$checkpoint_budget" "$head_count"
  if [ "${#visual_frames[@]}" -eq 0 ]; then
    return 0
  fi
  python3 "$frame_metrics_tool" --quiet --montage-out "$montage_path" "${visual_frames[@]}" >/dev/null 2>&1 || true
  if [ -f "$montage_path" ]; then
    echo "[campaign-route] visual failure montage: $montage_path" >>"$log_path" 2>/dev/null || true
    echo "campaign route visual failure montage: $montage_path" >&2
  fi
}

frame_mean_value() {
  local frame_path="$1"

  if command -v identify >/dev/null 2>&1; then
    identify -format '%[mean]' "$frame_path" 2>/dev/null || true
  elif command -v magick >/dev/null 2>&1; then
    magick identify -format '%[mean]' "$frame_path" 2>/dev/null || true
  elif command -v python3 >/dev/null 2>&1; then
    python3 -c '
import struct
import sys
path = sys.argv[1]
data = open(path, "rb").read()
if len(data) < 54 or data[:2] != b"BM":
    raise SystemExit(1)
pixel_offset = struct.unpack_from("<I", data, 10)[0]
dib_size = struct.unpack_from("<I", data, 14)[0]
if dib_size < 40:
    raise SystemExit(1)
width = abs(struct.unpack_from("<i", data, 18)[0])
height = abs(struct.unpack_from("<i", data, 22)[0])
bpp = struct.unpack_from("<H", data, 28)[0]
compression = struct.unpack_from("<I", data, 30)[0]
if width == 0 or height == 0 or bpp not in (24, 32) or compression not in (0, 3):
    raise SystemExit(1)
bytes_per_pixel = bpp // 8
stride = ((width * bytes_per_pixel + 3) // 4) * 4
total = 0
count = 0
for row in range(height):
    start = pixel_offset + row * stride
    pixels = data[start:start + width * bytes_per_pixel]
    if len(pixels) < width * bytes_per_pixel:
        raise SystemExit(1)
    total += sum(pixels)
    count += len(pixels)
print("{:.6f}".format(total / count if count else 0.0))
' "$frame_path" 2>/dev/null || true
  fi
}

game_log_count() {
  local pattern="$1"

  awk -v pattern="$pattern" '
    index($0, pattern) && index($0, "[campaign-route]") == 0 { count++ }
    END { print count + 0 }
  ' "$log_path" 2>/dev/null || true
}

is_unsigned_integer() {
  case "${1:-}" in
    ""|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
}

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

copy_capped_log() {
  local source_path="$1"
  local target_path="$2"
  local max_bytes="${CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES:-12000000}"
  local head_lines="${CLASH95_CAMPAIGN_ROUTE_LOG_HEAD_LINES:-1200}"
  local tail_lines="${CLASH95_CAMPAIGN_ROUTE_LOG_TAIL_LINES:-2400}"

  durable_log_original_bytes=0
  durable_log_retained_bytes=0
  durable_log_bytes="$(wc -c <"$source_path" 2>/dev/null || echo 0)"
  durable_log_bytes="${durable_log_bytes//[[:space:]]/}"
  durable_log_original_bytes="$durable_log_bytes"
  durable_log_truncated=0

  if ! is_unsigned_integer "$max_bytes" || [ "$max_bytes" = "0" ]; then
    cp -f "$source_path" "$target_path" 2>/dev/null || true
    durable_log_retained_bytes="$(wc -c <"$target_path" 2>/dev/null || echo 0)"
    durable_log_retained_bytes="${durable_log_retained_bytes//[[:space:]]/}"
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
    durable_log_retained_bytes="$(wc -c <"$target_path" 2>/dev/null || echo 0)"
    durable_log_retained_bytes="${durable_log_retained_bytes//[[:space:]]/}"
    return 0
  fi

  durable_log_truncated=1
  {
    echo "[campaign-route] durable log truncated"
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
  durable_log_retained_bytes="$(wc -c <"$target_path" 2>/dev/null || echo 0)"
  durable_log_retained_bytes="${durable_log_retained_bytes//[[:space:]]/}"
}

copy_capped_presented_frames() {
  local target_dir="$1"
  local max_frames="${CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES:-160}"
  local head_count="${CLASH95_CAMPAIGN_ROUTE_COPIED_FRAME_HEAD_COUNT:-8}"
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

  local -a captured_frames=()
  collect_presented_frames_by_mtime captured_frames
  captured_frames_total="${#captured_frames[@]}"
  if [ "$captured_frames_total" -eq 0 ]; then
    return 0
  fi
  last_frame="$(latest_frame_path)"
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

copy_capped_checkpoint_frames() {
  local target_dir="$1"
  local max_checkpoints="${CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS:-32}"
  local head_count="${CLASH95_CAMPAIGN_ROUTE_COPIED_CHECKPOINT_HEAD_COUNT:-8}"
  local checkpoint_frame
  local -a checkpoint_frames=()
  local -a sampled_checkpoint_frames=()
  local -A copied_checkpoint_paths=()

  copied_checkpoints=0
  checkpoint_frames_total=0
  checkpoints_truncated=0
  copied_checkpoint_cap="$max_checkpoints"

  if ! is_unsigned_integer "$max_checkpoints"; then
    max_checkpoints=32
  fi
  copied_checkpoint_cap="$max_checkpoints"
  if ! is_unsigned_integer "$head_count"; then
    head_count=8
  fi

  shopt -s nullglob
  checkpoint_frames=( "$smoke_root"/checkpoint-*.bmp )
  shopt -u nullglob
  checkpoint_frames_total="${#checkpoint_frames[@]}"
  if [ "$checkpoint_frames_total" -eq 0 ]; then
    return 0
  fi
  if [ "$max_checkpoints" -eq 0 ]; then
    checkpoints_truncated=1
    return 0
  fi
  if [ "$checkpoint_frames_total" -gt "$max_checkpoints" ]; then
    checkpoints_truncated=1
  fi

  sample_frame_array checkpoint_frames sampled_checkpoint_frames "$max_checkpoints" "$head_count"
  for checkpoint_frame in "${sampled_checkpoint_frames[@]}"; do
    if [ ! -f "$checkpoint_frame" ]; then
      continue
    fi
    if [ -n "${copied_checkpoint_paths[$checkpoint_frame]+x}" ]; then
      continue
    fi
    cp -f "$checkpoint_frame" "$target_dir/" 2>/dev/null || true
    copied_checkpoint_paths[$checkpoint_frame]=1
    copied_checkpoints=$((copied_checkpoints + 1))
  done
}

prune_old_campaign_route_runs() {
  local durable_root="$1"
  local keep_runs="${CLASH95_CAMPAIGN_ROUTE_KEEP_RUNS_PER_MISSION:-12}"
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
      echo "[campaign-route] skip artifact pruning outside repo artifacts: $root_real" >&2
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
            echo "[campaign-route] pruned old artifact run: $candidate_real" >&2
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

  CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP="${CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP:-${CLASH95_CAMPAIGN_ROUTE_KEEP_RUNS_PER_MISSION:-12}}" \
    bash "$repo_root/tests/prune_artifacts.sh" --apply --quiet >&2 || true
}

persist_route_artifacts() {
  local durable_root
  local run_id
  local durable_run
  local captured_frame
  local copied_frames=0
  local captured_frames_total=0
  local copied_frame_cap=0
  local frames_truncated=0
  local checkpoint_frames_total=0
  local copied_checkpoints=0
  local durable_log_bytes=0
  local durable_log_original_bytes=0
  local durable_log_retained_bytes=0
  local durable_log_truncated=0
  local durable_run_bytes=0
  local last_frame
  local copied_checkpoint_cap=0
  local checkpoints_truncated=0
  local frame_mean
  local last_frame_metrics
  local progression_metrics
  local summary_path
  local -a summary_frames=()
  local -a sampled_summary_frames=()

  if [ "${CLASH95_CAMPAIGN_ROUTE_DURABLE_ARTIFACTS:-1}" != "1" ]; then
    return 0
  fi

  durable_root="${CLASH95_CAMPAIGN_ROUTE_DURABLE_ARTIFACT_DIR:-$repo_root/artifacts/campaign-routes/mission-${mission_id}}"
  run_id="${CLASH95_CAMPAIGN_ROUTE_DURABLE_ARTIFACT_RUN_ID:-$(date -u +%Y%m%dT%H%M%SZ)-$$}"
  durable_run="$durable_root/$run_id"
  mkdir -p "$durable_run"

  copy_capped_log "$log_path" "$durable_run/campaign-route-${mission_id}.log"
  cp -f "$world_input_script" "$durable_run/world-input.txt" 2>/dev/null || true
  cp -f "$platform_input_script" "$durable_run/platform-input.txt" 2>/dev/null || true
  cp -f "$battle_input_script" "$durable_run/battle-input.txt" 2>/dev/null || true
  cp -f "$route_script" "$durable_run/$(basename "$route_script")" 2>/dev/null || true
  if [ -n "$route_env_path" ] && [ -f "$route_env_path" ]; then
    cp -f "$route_env_path" "$durable_run/$(basename "$route_env_path")" 2>/dev/null || true
  fi
  env | grep '^CLASH95_' | sort >"$durable_run/clash95-env.txt" 2>/dev/null || true

  copy_capped_presented_frames "$durable_run"
  copy_capped_checkpoint_frames "$durable_run"
  frame_mean=""
  last_frame_metrics=""
  progression_metrics=""
  if [ -n "$last_frame" ]; then
    frame_mean="$(frame_mean_value "$last_frame")"
    if command -v python3 >/dev/null 2>&1 && [ -f "$frame_metrics_tool" ]; then
      last_frame_metrics="$(python3 "$frame_metrics_tool" "$last_frame" 2>/dev/null | tr '\n' ';' || true)"
    fi
  fi
  if command -v python3 >/dev/null 2>&1 && [ -f "$frame_metrics_tool" ]; then
    collect_presented_frames_by_mtime summary_frames
    sample_frame_array summary_frames sampled_summary_frames "${CLASH95_CAMPAIGN_ROUTE_SUMMARY_METRICS_MAX_FRAMES:-96}" "${CLASH95_CAMPAIGN_ROUTE_SUMMARY_METRICS_HEAD_COUNT:-8}"
    if [ "${#sampled_summary_frames[@]}" -ge 2 ]; then
      progression_metrics="$(python3 "$frame_metrics_tool" \
        --min-diff "${CLASH95_CAMPAIGN_ROUTE_MIN_FRAME_DIFF:-0.25}" \
        "${sampled_summary_frames[@]}" 2>/dev/null | tail -n 1 || true)"
    fi
  fi

  summary_path="$durable_run/summary.txt"
  durable_run_bytes="$(du -sb "$durable_run" 2>/dev/null | awk '{ print $1 + 0 }' || true)"
  {
    echo "durable_run=$durable_run"
    echo "mission_id=$mission_id"
    echo "start_mode=${CLASH95_CAMPAIGN_ROUTE_START_MODE:-menu}"
    echo "route_script=$route_script"
    echo "captured_frames_total=$captured_frames_total"
    echo "copied_frames=$copied_frames"
    echo "copied_frame_cap=$copied_frame_cap"
    echo "frames_truncated=$frames_truncated"
    echo "checkpoint_frames_total=$checkpoint_frames_total"
    echo "copied_checkpoints=$copied_checkpoints"
    echo "copied_checkpoint_cap=$copied_checkpoint_cap"
    echo "checkpoints_truncated=$checkpoints_truncated"
    echo "last_frame=$last_frame"
    echo "last_frame_mean=${frame_mean:-unavailable}"
    echo "last_frame_visual_metrics=${last_frame_metrics:-unavailable}"
    echo "frame_progression_metrics=${progression_metrics:-unavailable}"
    echo "durable_log_bytes=${durable_log_bytes:-0}"
    echo "durable_log_original_bytes=${durable_log_original_bytes:-${durable_log_bytes:-0}}"
    echo "durable_log_retained_bytes=${durable_log_retained_bytes:-0}"
    echo "durable_log_truncated=${durable_log_truncated:-0}"
    echo "durable_run_bytes=${durable_run_bytes:-0}"
    echo "mission_objective_complete_count=$(game_log_count "mission_objective_complete")"
    echo "mission_objective_blocked_count=$(game_log_count "mission_objective_blocked")"
    echo "route_input_step_count=$(grep -Fc "[campaign-route] route-input-step" "$log_path" 2>/dev/null || true)"
    echo
    echo "mission markers:"
    grep -E "mission_load_|mission_objective_|mission_auto_advance|campaign_.*victory_branch" "$log_path" | grep -Fv "[campaign-route]" | tail -n 120 || true
    echo
    echo "battle prompt/outcome markers:"
    grep -E "battle_prompt_layout|unit_attack_|capture_defeated|unit_kill" "$log_path" | grep -Fv "[campaign-route]" | tail -n 160 || true
    echo
    echo "route input timeline:"
    grep -E "route-input-step|wait-log|expect-log|checkpoint|nonblank|visual" "$log_path" | tail -n 260 || true
    echo
    echo "battle/result markers:"
    grep -E "battle_|unit_attack_|enemy_attack_|capture_defeated|unit_kill" "$log_path" | grep -Fv "[campaign-route]" | tail -n 160 || true
    echo
    echo "battle unit snapshots:"
    grep -F "[battle_units]" "$log_path" | tail -n 120 || true
    echo
    echo "recent log:"
    tail -n 180 "$log_path" || true
  } >"$summary_path" 2>/dev/null || true

  {
    echo "latest_run=$durable_run"
    echo "mission_id=$mission_id"
    echo "captured_frames_total=$captured_frames_total"
    echo "copied_frames=$copied_frames"
    echo "frames_truncated=$frames_truncated"
    echo "checkpoint_frames_total=$checkpoint_frames_total"
    echo "copied_checkpoints=$copied_checkpoints"
    echo "checkpoints_truncated=$checkpoints_truncated"
    echo "last_frame_mean=${frame_mean:-unavailable}"
    echo "durable_log_bytes=${durable_log_bytes:-0}"
    echo "durable_log_original_bytes=${durable_log_original_bytes:-${durable_log_bytes:-0}}"
    echo "durable_log_retained_bytes=${durable_log_retained_bytes:-0}"
    echo "durable_log_truncated=${durable_log_truncated:-0}"
    echo "durable_run_bytes=${durable_run_bytes:-0}"
    echo "summary=$summary_path"
  } >"$durable_root/latest.txt" 2>/dev/null || true
  prune_old_campaign_route_runs "$durable_root"
  prune_repo_artifacts_if_requested
  echo "[campaign-route] durable artifacts: $durable_run" >&2
  echo "[campaign-route] durable summary: $summary_path" >&2
}

cleanup() {
  if [ -n "${pid:-}" ]; then
    kill -TERM "-$pid" 2>/dev/null || true
    kill -KILL "-$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true
  fi
  if [ -n "${xvfb_pid:-}" ]; then
    kill "$xvfb_pid" 2>/dev/null || true
    sleep 0.1
    if kill -0 "$xvfb_pid" 2>/dev/null; then
      kill -KILL "$xvfb_pid" 2>/dev/null || true
    fi
    wait "$xvfb_pid" 2>/dev/null || true
  fi
  persist_route_artifacts
  if [ "${CLASH95_KEEP_SMOKE_ARTIFACTS:-0}" = "1" ] || [ "$preserve_artifacts" = "1" ]; then
    echo "campaign route script smoke artifacts: $smoke_root" >&2
  else
    rm -rf "$smoke_root"
  fi
}
trap cleanup EXIT

require_fixed_log_pattern() {
  local expected_pattern="$1"
  local label="${2:-$1}"

  echo "[campaign-route] expect-log label=${label} pattern=${expected_pattern}" >>"$log_path"
  if ! grep -F "$expected_pattern" "$log_path" | grep -Fv "[campaign-route]" >/dev/null 2>&1; then
    fail_smoke "campaign route script smoke did not find expected log pattern for ${label}: $expected_pattern"
  fi
}

wait_for_fixed_log_pattern() {
  local expected_pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_seconds="$SECONDS"

  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  echo "[campaign-route] wait-log label=${label} timeout=${timeout_seconds}s pattern=${expected_pattern}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    if grep -F "$expected_pattern" "$log_path" | grep -Fv "[campaign-route]" >/dev/null 2>&1; then
      echo "[campaign-route] wait-log-done label=${label}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for ${label}: $expected_pattern"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for ${label}: $expected_pattern"
}

wait_for_new_fixed_log_pattern() {
  local expected_pattern="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local start_seconds="$SECONDS"
  local start_count
  local current_count

  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  start_count="$(game_log_count "$expected_pattern")"
  echo "[campaign-route] wait-log-new label=${label} timeout=${timeout_seconds}s baseline=${start_count} pattern=${expected_pattern}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    current_count="$(game_log_count "$expected_pattern")"
    if [ "${current_count:-0}" -gt "${start_count:-0}" ]; then
      echo "[campaign-route] wait-log-new-done label=${label} count=${current_count}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for new ${label}: $expected_pattern"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for new ${label}: $expected_pattern"
}

wait_for_any_fixed_log_pattern() {
  local label="$1"
  local timeout_seconds="$2"
  shift 2
  local start_seconds="$SECONDS"
  local expected_pattern
  local joined_patterns=""

  if [ "$#" -eq 0 ]; then
    fail_smoke "campaign route script smoke wait_log_any requires at least one pattern for ${label}"
  fi
  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  for expected_pattern in "$@"; do
    if [ -z "$joined_patterns" ]; then
      joined_patterns="$expected_pattern"
    else
      joined_patterns="${joined_patterns} || ${expected_pattern}"
    fi
  done

  echo "[campaign-route] wait-log-any label=${label} timeout=${timeout_seconds}s patterns=${joined_patterns}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    for expected_pattern in "$@"; do
      if grep -F "$expected_pattern" "$log_path" | grep -Fv "[campaign-route]" >/dev/null 2>&1; then
        last_wait_log_any_pattern="$expected_pattern"
        echo "[campaign-route] wait-log-any-done label=${label} pattern=${expected_pattern}" >>"$log_path"
        return 0
      fi
    done
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for ${label}: ${joined_patterns}"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for ${label}: ${joined_patterns}"
}

wait_for_new_any_fixed_log_pattern() {
  local label="$1"
  local timeout_seconds="$2"
  shift 2
  local start_seconds="$SECONDS"
  local expected_pattern
  local joined_patterns=""
  local current_count
  local index
  local -a start_counts=()

  if [ "$#" -eq 0 ]; then
    fail_smoke "campaign route script smoke wait_log_any_new requires at least one pattern for ${label}"
  fi
  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  for expected_pattern in "$@"; do
    if [ -z "$joined_patterns" ]; then
      joined_patterns="$expected_pattern"
    else
      joined_patterns="${joined_patterns} || ${expected_pattern}"
    fi
    start_counts+=( "$(game_log_count "$expected_pattern")" )
  done

  echo "[campaign-route] wait-log-any-new label=${label} timeout=${timeout_seconds}s baselines=${start_counts[*]} patterns=${joined_patterns}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    index=0
    for expected_pattern in "$@"; do
      current_count="$(game_log_count "$expected_pattern")"
      if [ "${current_count:-0}" -gt "${start_counts[$index]:-0}" ]; then
        last_wait_log_any_pattern="$expected_pattern"
        echo "[campaign-route] wait-log-any-new-done label=${label} pattern=${expected_pattern} count=${current_count}" >>"$log_path"
        return 0
      fi
      index=$((index + 1))
    done
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for new ${label}: ${joined_patterns}"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for new ${label}: ${joined_patterns}"
}

mark_fixed_log_pattern_count() {
  local mark_name="$1"
  local expected_pattern="$2"
  local baseline

  if [ -z "$mark_name" ] || [ -z "$expected_pattern" ]; then
    fail_smoke "campaign route script smoke cannot mark an empty log pattern"
  fi
  baseline="$(game_log_count "$expected_pattern")"
  marked_log_counts["$mark_name"]="$baseline"
  marked_log_patterns["$mark_name"]="$expected_pattern"
  echo "[campaign-route] mark-log-count mark=${mark_name} baseline=${baseline} pattern=${expected_pattern}" >>"$log_path"
}

wait_for_marked_log_pattern() {
  local mark_name="$1"
  local label="${2:-$1}"
  local timeout_seconds="${3:-20}"
  local expected_pattern="${4:-}"
  local baseline
  local current_count
  local start_seconds="$SECONDS"

  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  if [ -z "$mark_name" ] || [ -z "${marked_log_counts[$mark_name]+x}" ]; then
    fail_smoke "campaign route script smoke wait_log_marked references unknown mark: ${mark_name}"
  fi
  baseline="${marked_log_counts[$mark_name]}"
  if [ -z "$expected_pattern" ]; then
    expected_pattern="${marked_log_patterns[$mark_name]}"
  fi
  if [ -z "$expected_pattern" ]; then
    fail_smoke "campaign route script smoke wait_log_marked has empty pattern for mark: ${mark_name}"
  fi

  echo "[campaign-route] wait-log-marked label=${label} mark=${mark_name} timeout=${timeout_seconds}s baseline=${baseline} pattern=${expected_pattern}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    current_count="$(game_log_count "$expected_pattern")"
    if [ "${current_count:-0}" -gt "${baseline:-0}" ]; then
      echo "[campaign-route] wait-log-marked-done label=${label} mark=${mark_name} count=${current_count}" >>"$log_path"
      return 0
    fi
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for marked ${label}: $expected_pattern"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for marked ${label}: $expected_pattern"
}

wait_for_any_marked_log_pattern() {
  local label="$1"
  local timeout_seconds="$2"
  shift 2
  local start_seconds="$SECONDS"
  local mark_name
  local expected_pattern
  local joined_marks=""
  local joined_patterns=""
  local current_count
  local baseline

  if [ "$#" -eq 0 ]; then
    fail_smoke "campaign route script smoke wait_log_marked_any requires at least one mark for ${label}"
  fi
  last_wait_log_any_pattern=""
  last_wait_log_any_mark=""
  for mark_name in "$@"; do
    if [ -z "${marked_log_counts[$mark_name]+x}" ]; then
      fail_smoke "campaign route script smoke wait_log_marked_any references unknown mark: ${mark_name}"
    fi
    expected_pattern="${marked_log_patterns[$mark_name]}"
    if [ -z "$joined_marks" ]; then
      joined_marks="$mark_name"
      joined_patterns="$expected_pattern"
    else
      joined_marks="${joined_marks} || ${mark_name}"
      joined_patterns="${joined_patterns} || ${expected_pattern}"
    fi
  done

  echo "[campaign-route] wait-log-marked-any label=${label} timeout=${timeout_seconds}s marks=${joined_marks} patterns=${joined_patterns}" >>"$log_path"
  while [ $((SECONDS - start_seconds)) -lt "$timeout_seconds" ]; do
    for mark_name in "$@"; do
      expected_pattern="${marked_log_patterns[$mark_name]}"
      baseline="${marked_log_counts[$mark_name]}"
      current_count="$(game_log_count "$expected_pattern")"
      if [ "${current_count:-0}" -gt "${baseline:-0}" ]; then
        last_wait_log_any_pattern="$expected_pattern"
        last_wait_log_any_mark="$mark_name"
        echo "[campaign-route] wait-log-marked-any-done label=${label} mark=${mark_name} pattern=${expected_pattern} count=${current_count}" >>"$log_path"
        return 0
      fi
    done
    if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
      fail_smoke "campaign route script smoke process exited while waiting for marked ${label}: ${joined_patterns}"
    fi
    sleep 0.1
  done
  fail_smoke "campaign route script smoke timed out waiting for marked ${label}: ${joined_patterns}"
}

log_route_input_step() {
  local channel="$1"
  local action="$2"
  local label="${3:-}"

  route_input_step=$((route_input_step + 1))
  echo "[campaign-route] route-input-step step=${route_input_step} channel=${channel} action=${action} label=${label}" >>"$log_path"
}

refresh_route_window() {
  local refreshed_window

  if [ "${CLASH95_CAMPAIGN_ROUTE_REFRESH_WINDOW_BEFORE_INPUT:-1}" != "1" ]; then
    return 0
  fi
  refreshed_window="$(timeout 2s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
  if [ -n "$refreshed_window" ] && [ "$refreshed_window" != "${window:-}" ]; then
    echo "[campaign-route] refreshed SDL window id old=${window:-none} new=${refreshed_window}" >>"$log_path"
    window="$refreshed_window"
  fi
}

click_at() {
  local x="$1"
  local y="$2"
  local hold="${3:-${CLASH95_REAL_INPUT_CLICK_HOLD:-0.18}}"
  local gap="${4:-${CLASH95_REAL_INPUT_CLICK_GAP:-0.55}}"
  local label="${5:-click}"

  refresh_route_window
  if [ -z "${window:-}" ]; then
    fail_smoke "campaign route script smoke cannot execute host click ${label}; no SDL window was acquired"
  fi
  log_route_input_step "xdotool" "click" "$label"
  echo "[campaign-route] ${label}: click at ${x},${y} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool mousemove --window "$window" "$x" "$y"
  sleep 0.08
  xdotool mousedown 1
  sleep "$hold"
  xdotool mouseup 1
  sleep "$gap"
}

key_at() {
  local key="$1"
  local hold="${2:-0.18}"
  local gap="${3:-0.20}"
  local label="${4:-key}"

  refresh_route_window
  if [ -z "${window:-}" ]; then
    fail_smoke "campaign route script smoke cannot execute host key ${label}; no SDL window was acquired"
  fi
  log_route_input_step "xdotool" "key" "$label"
  echo "[campaign-route] ${label}: key ${key} hold=${hold} gap=${gap}" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
  xdotool keydown --clearmodifiers "$key"
  sleep "$hold"
  xdotool keyup "$key"
  sleep "$gap"
}

write_world_script() {
  log_route_input_step "world" "$1" "${6:-world-$1}"
  printf '%s\n' "$2" >>"$world_input_script"
  sleep "${3:-0.40}"
}

write_platform_script() {
  log_route_input_step "platform" "$1" "${6:-platform-$1}"
  printf '%s\n' "$2" >>"$platform_input_script"
  sleep "${3:-0.40}"
}

write_battle_script() {
  log_route_input_step "battle" "$1" "${6:-battle-$1}"
  printf '%s\n' "$2" >>"$battle_input_script"
  sleep "${3:-0.40}"
}

copy_screenshot_checkpoint() {
  local label="${1:-checkpoint}"
  local latest_frame
  local sanitized_label
  local target

  latest_frame="$(latest_frame_path)"
  if [ -z "$latest_frame" ]; then
    fail_smoke "campaign route script smoke cannot checkpoint ${label}; no frames captured yet"
  fi
  sanitized_label="$(printf '%s' "$label" | tr -c 'A-Za-z0-9_.-' '_')"
  target="$smoke_root/checkpoint-${sanitized_label}.bmp"
  cp -f "$latest_frame" "$target"
  echo "[campaign-route] checkpoint label=${label} frame=${target}" >>"$log_path"
}

check_latest_frame_nonblank() {
  local label="${1:-nonblank}"
  local latest_frame
  local frame_mean
  local threshold="${CLASH95_CAMPAIGN_ROUTE_BLANK_MEAN_THRESHOLD:-1}"
  local min_nonblack="${CLASH95_CAMPAIGN_ROUTE_MIN_NONBLACK_PIXELS:-1000}"
  local min_colors="${CLASH95_CAMPAIGN_ROUTE_MIN_UNIQUE_COLORS:-16}"
  local metrics_output

  latest_frame="$(latest_frame_path)"
  if [ -z "$latest_frame" ]; then
    fail_smoke "campaign route script smoke cannot run nonblank check ${label}; no frames captured yet"
  fi
  if command -v python3 >/dev/null 2>&1 && [ -f "$frame_metrics_tool" ]; then
    if ! metrics_output="$(python3 "$frame_metrics_tool" \
          --min-mean "$threshold" \
          --min-nonblack "$min_nonblack" \
          --min-colors "$min_colors" \
          "$latest_frame" 2>&1)"; then
      {
        echo "[campaign-route] visual label=${label} frame=${latest_frame} threshold=${threshold} min_nonblack=${min_nonblack} min_colors=${min_colors}"
        printf '%s\n' "$metrics_output"
      } >>"$log_path"
      fail_smoke "campaign route script smoke frame failed visual check for ${label}: $latest_frame"
    fi
    {
      echo "[campaign-route] visual label=${label} frame=${latest_frame} threshold=${threshold} min_nonblack=${min_nonblack} min_colors=${min_colors}"
      printf '%s\n' "$metrics_output"
    } >>"$log_path"
    return 0
  fi
  frame_mean="$(frame_mean_value "$latest_frame")"
  echo "[campaign-route] nonblank label=${label} frame=${latest_frame} mean=${frame_mean:-unavailable} threshold=${threshold}" >>"$log_path"
  if [ -z "$frame_mean" ]; then
    fail_smoke "campaign route script smoke cannot determine frame mean for ${label}: $latest_frame"
  fi
  if awk -v mean="$frame_mean" -v threshold="$threshold" 'BEGIN { exit (mean <= threshold ? 0 : 1) }'; then
    fail_smoke "campaign route script smoke frame is blank for ${label}: mean=${frame_mean} frame=${latest_frame}"
  fi
}

check_presented_frame_progression() {
  local label="${1:-presented-frames}"
  local min_diff="${CLASH95_CAMPAIGN_ROUTE_MIN_FRAME_DIFF:-0.25}"
  local min_changed_pairs="${CLASH95_CAMPAIGN_ROUTE_MIN_CHANGED_FRAME_PAIRS:-1}"
  local metrics_output
  local -a visual_frames=()
  local -a sampled_frames=()

  if ! command -v python3 >/dev/null 2>&1 || [ ! -f "$frame_metrics_tool" ]; then
    fail_smoke "campaign route script smoke cannot run frame progression check ${label}; python3 frame metrics are unavailable"
  fi
  collect_presented_frames_by_mtime visual_frames
  if [ "${#visual_frames[@]}" -lt 2 ]; then
    fail_smoke "campaign route script smoke cannot run frame progression check ${label}; fewer than 2 frames captured"
  fi
  sample_frame_array visual_frames sampled_frames "${CLASH95_CAMPAIGN_ROUTE_PROGRESS_METRICS_MAX_FRAMES:-96}" "${CLASH95_CAMPAIGN_ROUTE_PROGRESS_METRICS_HEAD_COUNT:-8}"
  if [ "${#sampled_frames[@]}" -lt 2 ]; then
    fail_smoke "campaign route script smoke cannot run frame progression check ${label}; fewer than 2 sampled frames"
  fi
  if ! metrics_output="$(python3 "$frame_metrics_tool" \
        --min-diff "$min_diff" \
        --min-changed-pairs "$min_changed_pairs" \
        "${sampled_frames[@]}" 2>&1)"; then
    {
      echo "[campaign-route] visual-progression label=${label} min_diff=${min_diff} min_changed_pairs=${min_changed_pairs} sampled_frames=${#sampled_frames[@]} captured_frames=${#visual_frames[@]}"
      printf '%s\n' "$metrics_output"
    } >>"$log_path"
    fail_smoke "campaign route script smoke frame progression failed for ${label}"
  fi
  {
    echo "[campaign-route] visual-progression label=${label} min_diff=${min_diff} min_changed_pairs=${min_changed_pairs} sampled_frames=${#sampled_frames[@]} captured_frames=${#visual_frames[@]}"
    printf '%s\n' "$metrics_output"
  } >>"$log_path"
}

execute_route_script() {
  local script_path="${1:-$route_script}"
  local line
  local line_number=0
  local command
  local args
  local include_path
  local timeout_value
  local pattern
  local pattern_list
  local -a any_patterns
  local skip_depth=0
  local env_name
  local expected_value
  local actual_value
  local click_x
  local click_y
  local click_reads
  local click_gap
  local max_clicks
  local click_label
  local click_attempts
  local terminal_mark
  local completion_mark
  local terminal_count
  local completion_count
  local completion_baseline
  local attempt_timeout
  local attempt_deadline
  local click_completed
  local current_count
  local target_left
  local target_top
  local max_pan_attempts
  local pan_attempts
  local viewport_line
  local current_left
  local current_top
  local scan_code
  local cursor_baseline
  local cursor_count
  local cursor_deadline
  local probe_x=312
  local selected_line
  local selected_value

  while IFS= read -r line || [ -n "$line" ]; do
    line_number=$((line_number + 1))
    case "$line" in
      ""|\#*) continue ;;
    esac
    command="${line%%[[:space:]]*}"
    if [ "$command" = "$line" ]; then
      args=""
    else
      args="${line#"$command"}"
      args="${args#"${args%%[![:space:]]*}"}"
    fi
    args="${args//\{mission_id\}/$mission_id}"
    args="${args//\{mission_number\}/$mission_number}"
    if [ -n "$route_runtime_selected_unit" ]; then
      args="${args//\{selected_unit\}/$route_runtime_selected_unit}"
    fi
    if [ "$skip_depth" -eq 0 ] && [[ "$args" == *"{selected_unit}"* ]]; then
      fail_smoke "campaign route script line ${line_number}: selected_unit placeholder used before capture_battle_selected_unit"
    fi

    case "$command" in
      if_env)
        if [ "$skip_depth" -gt 0 ]; then
          skip_depth=$((skip_depth + 1))
          continue
        fi
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: if_env requires variable name"
        fi
        env_name="$1"
        expected_value="${2:-1}"
        actual_value="${!env_name:-}"
        if [ "$actual_value" != "$expected_value" ]; then
          echo "[campaign-route] if-env-skip line=${line_number} env=${env_name} expected=${expected_value} actual=${actual_value}" >>"$log_path"
          skip_depth=1
        else
          echo "[campaign-route] if-env-enter line=${line_number} env=${env_name} value=${expected_value}" >>"$log_path"
        fi
        continue
        ;;
      if_last_wait_log_any)
        if [ "$skip_depth" -gt 0 ]; then
          skip_depth=$((skip_depth + 1))
          continue
        fi
        pattern="$args"
        if [ -z "$pattern" ]; then
          fail_smoke "campaign route script line ${line_number}: if_last_wait_log_any requires pattern text"
        fi
        if [ "$last_wait_log_any_pattern" != "$pattern" ]; then
          echo "[campaign-route] if-last-wait-log-any-skip line=${line_number} expected=${pattern} actual=${last_wait_log_any_pattern}" >>"$log_path"
          skip_depth=1
        else
          echo "[campaign-route] if-last-wait-log-any-enter line=${line_number} pattern=${pattern}" >>"$log_path"
        fi
        continue
        ;;
      if_last_wait_log_mark)
        if [ "$skip_depth" -gt 0 ]; then
          skip_depth=$((skip_depth + 1))
          continue
        fi
        pattern="$args"
        if [ -z "$pattern" ]; then
          fail_smoke "campaign route script line ${line_number}: if_last_wait_log_mark requires mark name"
        fi
        if [ "$last_wait_log_any_mark" != "$pattern" ]; then
          echo "[campaign-route] if-last-wait-log-mark-skip line=${line_number} expected=${pattern} actual=${last_wait_log_any_mark}" >>"$log_path"
          skip_depth=1
        else
          echo "[campaign-route] if-last-wait-log-mark-enter line=${line_number} mark=${pattern}" >>"$log_path"
        fi
        continue
        ;;
      endif)
        if [ "$skip_depth" -gt 0 ]; then
          skip_depth=$((skip_depth - 1))
          if [ "$skip_depth" -eq 0 ]; then
            echo "[campaign-route] if-env-skip-end line=${line_number}" >>"$log_path"
          fi
        else
          echo "[campaign-route] if-env-end line=${line_number}" >>"$log_path"
        fi
        continue
        ;;
      include_script)
        if [ "$skip_depth" -gt 0 ]; then
          continue
        fi
        include_path="$args"
        if [ -z "$include_path" ]; then
          fail_smoke "campaign route script line ${line_number}: include_script requires a script path"
        fi
        case "$include_path" in
          /*) ;;
          *) include_path="$repo_root/$include_path" ;;
        esac
        if [ ! -f "$include_path" ]; then
          fail_smoke "campaign route script line ${line_number}: include_script path does not exist: $include_path"
        fi
        echo "[campaign-route] include-script line=${line_number} path=${include_path}" >>"$log_path"
        execute_route_script "$include_path"
        continue
        ;;
    esac
    if [ "$skip_depth" -gt 0 ]; then
      continue
    fi

    case "$command" in
      wait)
        set -- $args
        sleep "${1:-1}"
        ;;
      wait_log)
        set -- $args
        if [ "$#" -ge 2 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          shift
          pattern="$*"
        else
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          pattern="$args"
        fi
        wait_for_fixed_log_pattern "$pattern" "script:${line_number}" "$timeout_value"
        ;;
      wait_log_new)
        set -- $args
        if [ "$#" -ge 2 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          shift
          pattern="$*"
        else
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          pattern="$args"
        fi
        wait_for_new_fixed_log_pattern "$pattern" "script:${line_number}" "$timeout_value"
        ;;
      wait_log_any)
        set -- $args
        if [ "$#" -ge 2 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          pattern_list="${args#"$1"}"
          pattern_list="${pattern_list#"${pattern_list%%[![:space:]]*}"}"
        else
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          pattern_list="$args"
        fi
        any_patterns=()
        while [[ "$pattern_list" == *" || "* ]]; do
          any_patterns+=( "${pattern_list%% || *}" )
          pattern_list="${pattern_list#* || }"
        done
        any_patterns+=( "$pattern_list" )
        wait_for_any_fixed_log_pattern "script:${line_number}" "$timeout_value" "${any_patterns[@]}"
        ;;
      wait_log_any_new)
        set -- $args
        if [ "$#" -ge 2 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          pattern_list="${args#"$1"}"
          pattern_list="${pattern_list#"${pattern_list%%[![:space:]]*}"}"
        else
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          pattern_list="$args"
        fi
        any_patterns=()
        while [[ "$pattern_list" == *" || "* ]]; do
          any_patterns+=( "${pattern_list%% || *}" )
          pattern_list="${pattern_list#* || }"
        done
        any_patterns+=( "$pattern_list" )
        wait_for_new_any_fixed_log_pattern "script:${line_number}" "$timeout_value" "${any_patterns[@]}"
        ;;
      mark_log_count)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: mark_log_count requires mark name and pattern"
        fi
        env_name="$1"
        shift
        mark_fixed_log_pattern_count "$env_name" "$*"
        ;;
      wait_log_marked)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: wait_log_marked requires mark name"
        fi
        if printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          shift
          if [ "$#" -lt 1 ]; then
            fail_smoke "campaign route script line ${line_number}: wait_log_marked timeout form requires mark name"
          fi
          env_name="$1"
          shift
        else
          env_name="$1"
          shift
          if [ "$#" -ge 1 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
            timeout_value="$1"
            shift
          else
            timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          fi
        fi
        if [ -z "${timeout_value:-}" ]; then
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
        fi
        pattern="$*"
        wait_for_marked_log_pattern "$env_name" "script:${line_number}" "$timeout_value" "$pattern"
        ;;
      wait_log_marked_any)
        set -- $args
        if [ "$#" -ge 2 ] && printf '%s' "$1" | grep -Eq '^[0-9]+([.][0-9]+)?$'; then
          timeout_value="$1"
          pattern_list="${args#"$1"}"
          pattern_list="${pattern_list#"${pattern_list%%[![:space:]]*}"}"
        else
          timeout_value="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-20}"
          pattern_list="$args"
        fi
        any_patterns=()
        while [[ "$pattern_list" == *" || "* ]]; do
          any_patterns+=( "${pattern_list%% || *}" )
          pattern_list="${pattern_list#* || }"
        done
        any_patterns+=( "$pattern_list" )
        wait_for_any_marked_log_pattern "script:${line_number}" "$timeout_value" "${any_patterns[@]}"
        ;;
      expect_log)
        printf '%s\n' "$args" >>"$expected_log_file"
        echo "[campaign-route] expect-log-queued line=${line_number} pattern=${args}" >>"$log_path"
        ;;
      fail_if_log)
        if grep -F "$args" "$log_path" | grep -Fv "[campaign-route]" >/dev/null 2>&1; then
          fail_smoke "campaign route script line ${line_number}: forbidden log pattern was present: $args"
        fi
        echo "[campaign-route] fail-if-log-clear line=${line_number} pattern=${args}" >>"$log_path"
        ;;
      fail_unless_last_wait_log_any)
        if [ "$last_wait_log_any_pattern" != "$args" ]; then
          fail_smoke "campaign route script line ${line_number}: last wait_log_any pattern was '${last_wait_log_any_pattern}', expected: $args"
        fi
        echo "[campaign-route] fail-unless-last-wait-log-any-clear line=${line_number} pattern=${args}" >>"$log_path"
        ;;
      fail_unless_last_wait_log_mark)
        if [ "$last_wait_log_any_mark" != "$args" ]; then
          fail_smoke "campaign route script line ${line_number}: last wait_log_any mark was '${last_wait_log_any_mark}', expected: $args"
        fi
        echo "[campaign-route] fail-unless-last-wait-log-mark-clear line=${line_number} mark=${args}" >>"$log_path"
        ;;
      click)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: click requires x y"
        fi
        click_at "$1" "$2" "${3:-0.18}" "${4:-0.55}" "${5:-script-click-${line_number}}"
        ;;
      key)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: key requires key name"
        fi
        key_at "$1" "${2:-0.18}" "${3:-0.20}" "${4:-script-key-${line_number}}"
        ;;
      world_click)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: world_click requires x y"
        fi
        write_world_script click "click $1 $2 ${3:-4}" "${4:-0.70}" "" "" "${5:-world-click-${line_number}}"
        ;;
      world_move)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: world_move requires x y"
        fi
        write_world_script move "move $1 $2" "${3:-0.40}" "" "" "${4:-world-move-${line_number}}"
        ;;
      world_down)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: world_down requires x y"
        fi
        write_world_script down "down $1 $2" "${3:-0.40}" "" "" "${4:-world-down-${line_number}}"
        ;;
      world_up)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: world_up requires x y"
        fi
        write_world_script up "up $1 $2" "${3:-0.40}" "" "" "${4:-world-up-${line_number}}"
        ;;
      world_wait)
        set -- $args
        write_world_script wait "wait ${1:-8}" "${2:-0.40}" "" "" "${3:-world-wait-${line_number}}"
        ;;
      world_key)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: world_key requires scan code"
        fi
        write_world_script key "key $1 ${2:-4}" "${3:-0.40}" "" "" "${4:-world-key-${line_number}}"
        ;;
      world_select_stack)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: world_select_stack requires a stack index"
        fi
        write_world_script select_stack "select_stack $1" "${2:-0.40}" "" "" "${3:-world-select-stack-${line_number}}"
        ;;
      world_save_slot)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: world_save_slot requires a slot index"
        fi
        write_world_script save_slot "save_slot $1" "${2:-0.40}" "" "" "${3:-world-save-slot-${line_number}}"
        ;;
      world_pan_viewport)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: world_pan_viewport requires left top"
        fi
        target_left="$1"
        target_top="$2"
        max_pan_attempts="${3:-160}"
        if ! is_unsigned_integer "$target_left" ||
           ! is_unsigned_integer "$target_top" ||
           ! is_unsigned_integer "$max_pan_attempts" ||
           [ "$max_pan_attempts" = "0" ]; then
          fail_smoke "campaign route script line ${line_number}: world_pan_viewport requires nonnegative left/top and positive max-attempts"
        fi
        pan_attempts=0
        while [ "$pan_attempts" -lt "$max_pan_attempts" ]; do
          viewport_line="$(grep -F "[world_cursor]" "$log_path" | grep -Fv "[campaign-route]" | tail -n 1 || true)"
          if [[ "$viewport_line" != *" left="* ]] || [[ "$viewport_line" != *" top="* ]]; then
            fail_smoke "campaign route script line ${line_number}: world_pan_viewport cannot read a world cursor viewport"
          fi
          current_left="${viewport_line#* left=}"
          current_left="${current_left%% *}"
          current_top="${viewport_line#* top=}"
          current_top="${current_top%% *}"
          if ! is_unsigned_integer "$current_left" || ! is_unsigned_integer "$current_top"; then
            fail_smoke "campaign route script line ${line_number}: world_pan_viewport parsed invalid viewport: left=${current_left} top=${current_top}"
          fi
          if [ "$current_left" = "$target_left" ] && [ "$current_top" = "$target_top" ]; then
            echo "[campaign-route] world-pan-viewport-done line=${line_number} left=${current_left} top=${current_top} attempts=${pan_attempts}" >>"$log_path"
            break
          fi
          if [ "$current_left" -lt "$target_left" ]; then
            scan_code=205
          elif [ "$current_left" -gt "$target_left" ]; then
            scan_code=203
          elif [ "$current_top" -lt "$target_top" ]; then
            scan_code=208
          else
            scan_code=200
          fi
          pan_attempts=$((pan_attempts + 1))
          # The runtime consumes key-pulse reads on every input-fallback poll
          # (~10 polls per presented frame measured 2026-07-16), so a pulse
          # must budget several frames of reads for the arrow key to still be
          # held when WorldMap_HandleScrollKeysAndIdle polls it after its
          # 16-centisecond repeat gate.
          write_world_script key "key ${scan_code} ${CLASH95_PAN_KEY_PULSE_READS:-48}" 0.22 "" "" "world-pan-viewport-${line_number}-key-${pan_attempts}"
          cursor_baseline="$(game_log_count "[world_cursor]")"
          # SDL can round adjacent script coordinates back onto the current
          # cursor, yielding a zero-delta move and therefore no world_cursor
          # trace. Keep the probe near screen center, but move far enough that
          # every pan attempt produces a fresh cursor sample.
          if [ "$probe_x" = "312" ]; then
            probe_x=328
          else
            probe_x=312
          fi
          write_world_script move "move ${probe_x} 239" 0.25 "" "" "world-pan-viewport-${line_number}-probe-${pan_attempts}"
          cursor_deadline=$((SECONDS + 5))
          cursor_count="$cursor_baseline"
          while [ "$SECONDS" -lt "$cursor_deadline" ]; do
            cursor_count="$(game_log_count "[world_cursor]")"
            if [ "${cursor_count:-0}" -gt "${cursor_baseline:-0}" ]; then
              break
            fi
            if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
              fail_smoke "campaign route script smoke process exited during world_pan_viewport"
            fi
            sleep 0.1
          done
          if [ "${cursor_count:-0}" -le "${cursor_baseline:-0}" ]; then
            fail_smoke "campaign route script line ${line_number}: world_pan_viewport timed out waiting for cursor probe"
          fi
        done
        if [ "$current_left" != "$target_left" ] || [ "$current_top" != "$target_top" ]; then
          fail_smoke "campaign route script line ${line_number}: world_pan_viewport exhausted ${max_pan_attempts} attempts at left=${current_left} top=${current_top}"
        fi
        ;;
      capture_battle_selected_unit)
        selected_line="$(grep -F "[battle_click] tile_input" "$log_path" |
          grep -F "occupant_type=1 occupant_owner=0" |
          grep -Fv "[campaign-route]" |
          tail -n 1 || true)"
        if [ -z "$selected_line" ]; then
          fail_smoke "campaign route script line ${line_number}: capture_battle_selected_unit found no clicked infantry trace"
        fi
        selected_value="${selected_line#* occupant=}"
        selected_value="${selected_value%% *}"
        if ! is_unsigned_integer "$selected_value" || [ "$selected_value" -gt 21 ]; then
          fail_smoke "campaign route script line ${line_number}: capture_battle_selected_unit parsed invalid index: ${selected_value}"
        fi
        route_runtime_selected_unit="$selected_value"
        echo "[campaign-route] capture-battle-selected-unit line=${line_number} selected=${route_runtime_selected_unit} label=${args:-captured}" >>"$log_path"
        ;;
      battle_click)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_click requires x y"
        fi
        write_battle_script click "click $1 $2 ${3:-4}" "${4:-0.70}" "" "" "${5:-battle-click-${line_number}}"
        ;;
      battle_click_until_marked)
        set -- $args
        if [ "$#" -lt 7 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_click_until_marked requires x y reads gap max-clicks terminal-mark completion-mark"
        fi
        click_x="$1"
        click_y="$2"
        click_reads="$3"
        click_gap="$4"
        max_clicks="$5"
        terminal_mark="$6"
        completion_mark="$7"
        click_label="${8:-battle-click-until-${terminal_mark}}"
        if ! is_unsigned_integer "$max_clicks" || [ "$max_clicks" = "0" ]; then
          fail_smoke "campaign route script line ${line_number}: battle_click_until_marked max-clicks must be a positive integer"
        fi
        if [ -z "${marked_log_counts[$terminal_mark]+x}" ]; then
          fail_smoke "campaign route script line ${line_number}: battle_click_until_marked references unknown terminal mark: ${terminal_mark}"
        fi
        if [ -z "${marked_log_counts[$completion_mark]+x}" ]; then
          fail_smoke "campaign route script line ${line_number}: battle_click_until_marked references unknown completion mark: ${completion_mark}"
        fi
        attempt_timeout="${CLASH95_CAMPAIGN_ROUTE_WAIT_LOG_TIMEOUT:-60}"
        if ! is_unsigned_integer "$attempt_timeout" || [ "$attempt_timeout" = "0" ]; then
          attempt_timeout=60
        fi
        click_attempts=0
        while [ "$click_attempts" -lt "$max_clicks" ]; do
          terminal_count="$(game_log_count "${marked_log_patterns[$terminal_mark]}")"
          if [ "${terminal_count:-0}" -gt "${marked_log_counts[$terminal_mark]:-0}" ]; then
            break
          fi
          completion_baseline="$(game_log_count "${marked_log_patterns[$completion_mark]}")"
          click_attempts=$((click_attempts + 1))
          write_battle_script click "click ${click_x} ${click_y} ${click_reads}" "$click_gap" "" "" "${click_label}-${click_attempts}"
          attempt_deadline=$((SECONDS + attempt_timeout))
          click_completed=0
          while [ "$SECONDS" -lt "$attempt_deadline" ]; do
            terminal_count="$(game_log_count "${marked_log_patterns[$terminal_mark]}")"
            if [ "${terminal_count:-0}" -gt "${marked_log_counts[$terminal_mark]:-0}" ]; then
              click_completed=1
              break
            fi
            completion_count="$(game_log_count "${marked_log_patterns[$completion_mark]}")"
            if [ "${completion_count:-0}" -gt "${completion_baseline:-0}" ]; then
              click_completed=1
              break
            fi
            if [ -n "${pid:-}" ] && ! kill -0 "$pid" 2>/dev/null; then
              fail_smoke "campaign route script smoke process exited during battle_click_until_marked ${terminal_mark}"
            fi
            sleep 0.1
          done
          if [ "$click_completed" != "1" ]; then
            fail_smoke "campaign route script line ${line_number}: battle_click_until_marked timed out waiting for attack completion: ${completion_mark}"
          fi
        done
        echo "[campaign-route] battle-click-until-marked line=${line_number} terminal=${terminal_mark} completion=${completion_mark} attempts=${click_attempts} max=${max_clicks}" >>"$log_path"
        wait_for_marked_log_pattern "$terminal_mark" "script:${line_number}" "$attempt_timeout" ""
        ;;
      battle_move)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_move requires x y"
        fi
        write_battle_script move "move $1 $2" "${3:-0.40}" "" "" "${4:-battle-move-${line_number}}"
        ;;
      battle_down)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_down requires x y"
        fi
        write_battle_script down "down $1 $2" "${3:-0.40}" "" "" "${4:-battle-down-${line_number}}"
        ;;
      battle_up)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_up requires x y"
        fi
        write_battle_script up "up $1 $2" "${3:-0.40}" "" "" "${4:-battle-up-${line_number}}"
        ;;
      battle_wait)
        set -- $args
        write_battle_script wait "wait ${1:-8}" "${2:-0.40}" "" "" "${3:-battle-wait-${line_number}}"
        ;;
      battle_key)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: battle_key requires scan code"
        fi
        write_battle_script key "key $1 ${2:-4}" "${3:-0.40}" "" "" "${4:-battle-key-${line_number}}"
        ;;
      battle_pulse)
        set -- $args
        write_battle_script pulse "pulse ${1:-0} ${2:-0} ${3:-1} ${4:-0} ${5:-4}" "${6:-0.40}" "" "" "${7:-battle-pulse-${line_number}}"
        ;;
      platform_click)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: platform_click requires x y"
        fi
        write_platform_script click "click $1 $2 ${3:-4}" "${4:-0.70}" "" "" "${5:-platform-click-${line_number}}"
        ;;
      platform_down)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: platform_down requires x y"
        fi
        write_platform_script down "down $1 $2" "${3:-0.40}" "" "" "${4:-platform-down-${line_number}}"
        ;;
      platform_up)
        set -- $args
        if [ "$#" -lt 2 ]; then
          fail_smoke "campaign route script line ${line_number}: platform_up requires x y"
        fi
        write_platform_script up "up $1 $2" "${3:-0.40}" "" "" "${4:-platform-up-${line_number}}"
        ;;
      platform_pulse)
        set -- $args
        write_platform_script pulse "pulse ${1:-0} ${2:-0} ${3:-1} ${4:-0} ${5:-4}" "${6:-0.70}" "" "" "${7:-platform-pulse-${line_number}}"
        ;;
      platform_key)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: platform_key requires scan code"
        fi
        write_platform_script key "key $1 ${2:-4}" "${3:-0.40}" "" "" "${4:-platform-key-${line_number}}"
        ;;
      screenshot)
        set -- $args
        copy_screenshot_checkpoint "${1:-checkpoint-${line_number}}"
        ;;
      nonblank)
        set -- $args
        check_latest_frame_nonblank "${1:-nonblank-${line_number}}"
        ;;
      stop)
        echo "[campaign-route] stop line=${line_number} label=${args:-route-stop}" >>"$log_path"
        return 0
        ;;
      stop_unless_env)
        set -- $args
        if [ "$#" -lt 1 ]; then
          fail_smoke "campaign route script line ${line_number}: stop_unless_env requires variable name"
        fi
        env_name="$1"
        expected_value="${2:-1}"
        actual_value="${!env_name:-}"
        if [ "$actual_value" != "$expected_value" ]; then
          echo "[campaign-route] stop-unless-env line=${line_number} env=${env_name} expected=${expected_value} actual=${actual_value} label=${3:-route-stop}" >>"$log_path"
          return 0
        fi
        echo "[campaign-route] continue-after-env line=${line_number} env=${env_name} value=${expected_value} label=${3:-route-continue}" >>"$log_path"
        ;;
      *)
        fail_smoke "campaign route script line ${line_number}: unknown command: $command"
        ;;
    esac
  done <"$script_path"
}

if [ "${CLASH95_XVFB_DISPLAY_NUMBER:-}" ]; then
  xvfb_candidates="$CLASH95_XVFB_DISPLAY_NUMBER"
else
  xvfb_candidates="$((90 + RANDOM % 1000)) $((90 + RANDOM % 1000)) $((90 + RANDOM % 1000)) $((90 + RANDOM % 1000))"
fi

for display_number in $xvfb_candidates; do
  echo "[campaign-route] trying Xvfb display :$display_number" >>"$log_path"
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
  echo "campaign route script smoke skipped; Xvfb did not start" >&2
  cat "$log_path" >&2 || true
  exit 77
fi
export DISPLAY=":$display_number"
echo "[campaign-route] using DISPLAY=$DISPLAY" >>"$log_path"

start_mode="${CLASH95_CAMPAIGN_ROUTE_START_MODE:-menu}"
timeout_seconds="${CLASH95_CAMPAIGN_ROUTE_TIMEOUT_SECONDS:-300}"
run_command=("$bootstrap_bin")
direct_arg=""
case "$start_mode" in
  menu)
    ;;
  direct)
    if [ "$mission_number" -lt 10 ]; then
      direct_arg="/A$mission_number"
    else
      direct_arg="/a$((mission_number - 10))"
    fi
    run_command+=("$direct_arg")
    ;;
  *)
    fail_smoke "campaign route script smoke unknown start mode: $start_mode"
    ;;
esac
if [ "${CLASH95_CAMPAIGN_ROUTE_GDB:-0}" = "1" ]; then
  run_command=(
    gdb -q -batch
    -ex "set pagination off"
    -ex run
    -ex "info registers rip rdi rsi rdx rcx rax"
    -ex "x/8gx \$rdi"
    -ex "bt 40"
    --args "${run_command[@]}"
  )
fi

set +e
if [ "$start_mode" = "direct" ]; then
  setsid timeout "${timeout_seconds}s" env -u WAYLAND_DISPLAY \
    SDL_VIDEODRIVER="${SDL_VIDEODRIVER:-x11}" \
    SDL_AUDIODRIVER=dummy \
    CLASH95_SKIP_BOOT_AVI=1 \
    CLASH95_DIRECT_CAMPAIGN_MISSION=1 \
    CLASH95_SKIP_MISSION_BRIEFING="${CLASH95_SKIP_MISSION_BRIEFING:-1}" \
    CLASH95_TRACE_WORLD_CLICK="${CLASH95_TRACE_WORLD_CLICK:-1}" \
    CLASH95_TRACE_WORLD_INPUT_SCRIPT="${CLASH95_TRACE_WORLD_INPUT_SCRIPT:-1}" \
    CLASH95_TRACE_MINIMAP_CLICK="${CLASH95_TRACE_MINIMAP_CLICK:-1}" \
    CLASH95_WORLD_INPUT_SCRIPT="$world_input_script" \
    CLASH95_TRACE_BATTLE_INPUT_SCRIPT="${CLASH95_TRACE_BATTLE_INPUT_SCRIPT:-1}" \
    CLASH95_BATTLE_INPUT_SCRIPT="$battle_input_script" \
    CLASH95_INPUT_SCRIPT="$platform_input_script" \
    CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP="${CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP:-1}" \
    CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
    CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-220}" \
    CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-72}" \
    "${run_command[@]}" >>"$log_path" 2>&1 &
else
  setsid timeout "${timeout_seconds}s" env -u WAYLAND_DISPLAY \
    SDL_VIDEODRIVER="${SDL_VIDEODRIVER:-x11}" \
    SDL_AUDIODRIVER=dummy \
    CLASH95_SKIP_BOOT_AVI=1 \
    CLASH95_TRACE_WORLD_CLICK="${CLASH95_TRACE_WORLD_CLICK:-1}" \
    CLASH95_TRACE_WORLD_INPUT_SCRIPT="${CLASH95_TRACE_WORLD_INPUT_SCRIPT:-1}" \
    CLASH95_TRACE_MINIMAP_CLICK="${CLASH95_TRACE_MINIMAP_CLICK:-1}" \
    CLASH95_WORLD_INPUT_SCRIPT="$world_input_script" \
    CLASH95_TRACE_BATTLE_INPUT_SCRIPT="${CLASH95_TRACE_BATTLE_INPUT_SCRIPT:-1}" \
    CLASH95_BATTLE_INPUT_SCRIPT="$battle_input_script" \
    CLASH95_INPUT_SCRIPT="$platform_input_script" \
    CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP="${CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP:-1}" \
    CLASH95_DUMP_PRESENTED_FRAMES_PREFIX="$frame_prefix" \
    CLASH95_DUMP_PRESENTED_FRAMES_SKIP="${CLASH95_DUMP_PRESENTED_FRAMES_SKIP:-220}" \
    CLASH95_DUMP_PRESENTED_FRAMES_LIMIT="${CLASH95_DUMP_PRESENTED_FRAMES_LIMIT:-72}" \
    "${run_command[@]}" >>"$log_path" 2>&1 &
fi
pid=$!
set -e
echo "[campaign-route] launched bootstrap pid=$pid start=${start_mode} direct_arg=${direct_arg:-none}" >>"$log_path"

sleep "${CLASH95_CAMPAIGN_ROUTE_POST_LAUNCH_WAIT:-2}"
if ! kill -0 "$pid" 2>/dev/null; then
  set +e
  wait "$pid"
  status=$?
  set -e
  fail_smoke "campaign route script smoke exited early with status $status"
fi

require_window="${CLASH95_CAMPAIGN_ROUTE_REQUIRE_WINDOW:-}"
if [ -z "$require_window" ]; then
  if [ "$start_mode" = "direct" ]; then
    require_window=0
  else
    require_window=1
  fi
fi
if [ "$require_window" = "1" ]; then
  window="$(timeout 20s xdotool search --sync --onlyvisible --name "${CLASH95_WINDOW_NAME:-Clash}" | head -n 1 || true)"
  if [ -z "$window" ]; then
    fail_smoke "campaign route script smoke could not find the SDL window"
  fi
  echo "[campaign-route] found window: $window" >>"$log_path"
  xdotool windowactivate --sync "$window" >/dev/null 2>&1 || true
else
  echo "[campaign-route] window acquisition skipped for start=${start_mode}" >>"$log_path"
fi

pre_script_wait="${CLASH95_CAMPAIGN_ROUTE_PRE_SCRIPT_WAIT:-0}"
if [ "$pre_script_wait" != "0" ] && [ "$pre_script_wait" != "0.0" ]; then
  echo "[campaign-route] pre-script-wait: ${pre_script_wait}s" >>"$log_path"
  sleep "$pre_script_wait"
fi

execute_route_script

if [ "${CLASH95_CAMPAIGN_ROUTE_REQUIRE_OBJECTIVE:-0}" = "1" ]; then
  require_fixed_log_pattern "mission_objective_complete" "objective-complete"
fi

if [ "${CLASH95_CAMPAIGN_ROUTE_EXPECT_LOG:-}" ]; then
  require_fixed_log_pattern "$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOG" "route-env-expected-log"
fi

if [ "${CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS:-}" ]; then
  while IFS= read -r expected_pattern; do
    case "$expected_pattern" in
      ""|\#*) continue ;;
    esac
    require_fixed_log_pattern "$expected_pattern" "route-env-expected-logs"
  done <<<"$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS"
fi

if [ "${CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE:-}" ]; then
  if [ ! -f "$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE" ]; then
    fail_smoke "campaign route script smoke expected-log file does not exist: $CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE"
  fi
  while IFS= read -r expected_pattern; do
    case "$expected_pattern" in
      ""|\#*) continue ;;
    esac
    require_fixed_log_pattern "$expected_pattern" "route-env-expected-logs-file"
  done <"$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE"
fi

while IFS= read -r expected_pattern; do
  case "$expected_pattern" in
    ""|\#*) continue ;;
  esac
  require_fixed_log_pattern "$expected_pattern" "script-expected-log"
done <"$expected_log_file"

if grep -q "Segmentation fault" "$log_path" || grep -q "Aborted" "$log_path"; then
  fail_smoke "campaign route script smoke reported a crash"
fi

frame_count=0
for captured_frame in "$frame_prefix"-*.bmp; do
  if [ -f "$captured_frame" ]; then
    frame_count=$((frame_count + 1))
  fi
done
echo "[campaign-route] captured_frames=$frame_count" >>"$log_path"

if [ "${CLASH95_CAMPAIGN_ROUTE_REQUIRE_FRAMES:-1}" = "1" ] && [ "$frame_count" -eq 0 ]; then
  fail_smoke "campaign route script smoke did not capture any presented frames"
fi

if [ "${CLASH95_CAMPAIGN_ROUTE_REQUIRE_FRAME_PROGRESSION:-0}" = "1" ]; then
  check_presented_frame_progression "presented-frames"
fi

if [ "${CLASH95_CAMPAIGN_ROUTE_REJECT_BLANK_FRAMES:-1}" = "1" ] && [ "$frame_count" -gt 0 ]; then
  check_latest_frame_nonblank "final-frame"
fi

echo "[campaign-route] mission ${mission_id} route script completed" >&2
