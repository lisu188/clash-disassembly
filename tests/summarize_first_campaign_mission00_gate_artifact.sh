#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
artifact_root="${CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR:-$repo_root/artifacts/first-campaign/mission-00}"
latest_file="${1:-$artifact_root/latest.txt}"
require_complete="${CLASH95_MISSION00_SUMMARY_REQUIRE_COMPLETE:-0}"
require_frames="${CLASH95_MISSION00_SUMMARY_REQUIRE_FRAMES:-0}"
require_nonblank="${CLASH95_MISSION00_SUMMARY_REQUIRE_NONBLANK:-0}"
require_route_inputs="${CLASH95_MISSION00_SUMMARY_REQUIRE_ROUTE_INPUTS:-0}"

is_positive_integer() {
  case "${1:-}" in
    ''|*[!0-9]*|0) return 1 ;;
    *) return 0 ;;
  esac
}

frame_mean_nonblank_status() {
  case "${1:-}" in
    ''|unknown|unavailable)
      echo "unknown"
      ;;
    0|0.0|0.00|0.000|0.0000|0.00000|0.000000)
      echo "no"
      ;;
    *)
      echo "yes"
      ;;
  esac
}

if [ ! -f "$latest_file" ]; then
  echo "mission-00 artifact summary missing latest file: $latest_file" >&2
  exit 2
fi

latest_run=""
summary_path=""
copied_frames=""
copied_xvfb_logs=""
complete_count=""
blocked_count=""
route_input_step_count=""
last_frame_mean=""
last_frame_mean_tool=""
objective_complete="no"
frames_retained="no"
route_inputs_recorded="no"
last_frame_nonblank="unknown"
mission00_gate_verdict="fail"

while IFS= read -r latest_line || [ -n "$latest_line" ]; do
  case "$latest_line" in
    *=*)
      key="${latest_line%%=*}"
      value="${latest_line#*=}"
      ;;
    *)
      continue
      ;;
  esac
  case "$key" in
    latest_run) latest_run="$value" ;;
    summary) summary_path="$value" ;;
    copied_frames) copied_frames="$value" ;;
    copied_xvfb_logs) copied_xvfb_logs="$value" ;;
    mission_objective_complete_count) complete_count="$value" ;;
    mission_objective_blocked_count) blocked_count="$value" ;;
    route_input_step_count) route_input_step_count="$value" ;;
    last_frame_mean) last_frame_mean="$value" ;;
    last_frame_mean_tool) last_frame_mean_tool="$value" ;;
  esac
done <"$latest_file"

if is_positive_integer "$complete_count"; then
  objective_complete="yes"
fi
if is_positive_integer "$copied_frames"; then
  frames_retained="yes"
fi
if is_positive_integer "$route_input_step_count"; then
  route_inputs_recorded="yes"
fi
last_frame_nonblank="$(frame_mean_nonblank_status "$last_frame_mean")"
if [ "$objective_complete" = "yes" ] && [ "$frames_retained" = "yes" ] && [ "$last_frame_nonblank" = "yes" ]; then
  mission00_gate_verdict="pass"
fi

echo "latest_file=$latest_file"
echo "latest_run=${latest_run:-unknown}"
echo "summary=${summary_path:-unknown}"
echo "copied_frames=${copied_frames:-unknown}"
echo "copied_xvfb_logs=${copied_xvfb_logs:-unknown}"
echo "mission_objective_complete_count=${complete_count:-unknown}"
echo "mission_objective_blocked_count=${blocked_count:-unknown}"
echo "route_input_step_count=${route_input_step_count:-unknown}"
echo "last_frame_mean=${last_frame_mean:-unknown}"
echo "last_frame_mean_tool=${last_frame_mean_tool:-unknown}"
echo "objective_complete=$objective_complete"
echo "frames_retained=$frames_retained"
echo "route_inputs_recorded=$route_inputs_recorded"
echo "last_frame_nonblank=$last_frame_nonblank"
echo "mission00_gate_verdict=$mission00_gate_verdict"

if [ -n "$summary_path" ] && [ -f "$summary_path" ]; then
  echo
  echo "mission markers:"
  sed -n '/^mission markers:/,/^$/p' "$summary_path" | sed '1d;$d' || true
  echo
  echo "route input timeline:"
  sed -n '/^route input timeline:/,/^$/p' "$summary_path" | sed '1d;$d' || true
  echo
  echo "recent smoke tail:"
  sed -n '/^recent smoke log:/,$p' "$summary_path" | tail -n 80 || true
fi

if [ "$require_complete" = "1" ]; then
  if [ "$objective_complete" != "yes" ]; then
    echo "mission-00 artifact summary did not find mission_objective_complete in latest run" >&2
    exit 1
  fi
fi

if [ "$require_frames" = "1" ]; then
  if [ "$frames_retained" != "yes" ]; then
    echo "mission-00 artifact summary did not find retained frame captures in latest run" >&2
    exit 1
  fi
fi

if [ "$require_nonblank" = "1" ]; then
  if [ "$last_frame_nonblank" != "yes" ]; then
    echo "mission-00 artifact summary did not find nonblank final-frame evidence in latest run" >&2
    exit 1
  fi
fi

if [ "$require_route_inputs" = "1" ]; then
  if [ "$route_inputs_recorded" != "yes" ]; then
    echo "mission-00 artifact summary did not find recorded route input steps in latest run" >&2
    exit 1
  fi
fi
