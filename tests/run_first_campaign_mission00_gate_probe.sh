#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <path-to-clash95_bootstrap> [mission-id]" >&2
  echo "mission-id defaults to 00; this wrapper is for the current mission-0 repair gate." >&2
  exit 2
fi

bootstrap_bin="$1"
shift

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
mission_id="${1:-00}"

if [ "$mission_id" != "00" ]; then
  echo "mission-00 gate probe only supports mission id 00, got: $mission_id" >&2
  exit 2
fi

export CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_PARTIAL=1
export CLASH95_FIRST_CAMPAIGN_ARC_REQUIRE_OBJECTIVE=1
export CLASH95_FIRST_MISSION_DURABLE_ARTIFACTS=1
export CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR="${CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR:-$repo_root/artifacts/first-campaign/mission-00}"
export CLASH95_FIRST_MISSION_MOVE_REQUIRE_FRAMES=1
export CLASH95_FIRST_MISSION_MOVE_REJECT_BLANK_FRAMES=1

set +e
bash "$script_dir/run_first_campaign_arc_probe.sh" "$bootstrap_bin" "$mission_id"
status=$?
set -e

latest_file="$CLASH95_FIRST_MISSION_DURABLE_ARTIFACT_DIR/latest.txt"
if [ -f "$latest_file" ]; then
  if [ "$status" -eq 0 ]; then
    CLASH95_MISSION00_SUMMARY_REQUIRE_COMPLETE=1 \
      CLASH95_MISSION00_SUMMARY_REQUIRE_FRAMES=1 \
      CLASH95_MISSION00_SUMMARY_REQUIRE_NONBLANK=1 \
      bash "$script_dir/summarize_first_campaign_mission00_gate_artifact.sh" "$latest_file" || status=$?
  else
    bash "$script_dir/summarize_first_campaign_mission00_gate_artifact.sh" "$latest_file" || true
  fi
fi

exit "$status"
