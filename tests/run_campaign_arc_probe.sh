#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <path-to-clash95_bootstrap> [mission-id ...]" >&2
  echo "mission ids default to: 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19" >&2
  exit 2
fi

bootstrap_bin="$1"
shift

if [ ! -x "$bootstrap_bin" ]; then
  echo "campaign arc probe binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
route_dir="${CLASH95_CAMPAIGN_ARC_ROUTE_DIR:-${CLASH95_FIRST_CAMPAIGN_ARC_ROUTE_DIR:-$repo_root/tests/first_campaign_arc_routes}}"
verify_first_mission="$repo_root/tests/verify_first_mission_real_input_move_smoke.sh"
verify_route_script="$repo_root/tests/run_campaign_route_script_smoke.sh"

if [ ! -x "$verify_first_mission" ] && [ ! -f "$verify_first_mission" ]; then
  echo "campaign arc probe missing first-mission verifier: $verify_first_mission" >&2
  exit 2
fi
if [ ! -x "$verify_route_script" ] && [ ! -f "$verify_route_script" ]; then
  echo "campaign arc probe missing generic route script verifier: $verify_route_script" >&2
  exit 2
fi

if [ "$#" -gt 0 ]; then
  missions="$*"
else
  missions="${CLASH95_CAMPAIGN_ARC_MISSIONS:-00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19}"
fi

allow_partial="${CLASH95_CAMPAIGN_ARC_ALLOW_PARTIAL:-${CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_PARTIAL:-0}}"
allow_incomplete="${CLASH95_CAMPAIGN_ARC_ALLOW_INCOMPLETE:-${CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_INCOMPLETE:-0}}"
dry_run="${CLASH95_CAMPAIGN_ARC_DRY_RUN:-${CLASH95_FIRST_CAMPAIGN_ARC_DRY_RUN:-0}}"
start_mode_override="${CLASH95_CAMPAIGN_ARC_START_MODE:-${CLASH95_FIRST_CAMPAIGN_ARC_START_MODE:-}}"
if [ "${CLASH95_CAMPAIGN_ARC_REQUIRE_OBJECTIVE+x}" ]; then
  require_objective="$CLASH95_CAMPAIGN_ARC_REQUIRE_OBJECTIVE"
elif [ "${CLASH95_FIRST_CAMPAIGN_ARC_REQUIRE_OBJECTIVE+x}" ]; then
  require_objective="$CLASH95_FIRST_CAMPAIGN_ARC_REQUIRE_OBJECTIVE"
elif [ "$allow_partial" = "1" ]; then
  require_objective=0
else
  require_objective=1
fi

reset_route_env() {
  unset CLASH95_CAMPAIGN_ROUTE_STATUS
  unset CLASH95_CAMPAIGN_ROUTE_REASON
  unset CLASH95_CAMPAIGN_ROUTE_START_MODE
  unset CLASH95_CAMPAIGN_ROUTE_RUNNER
  unset CLASH95_CAMPAIGN_ROUTE_EXPECT_PRESET
  unset CLASH95_CAMPAIGN_ROUTE_EXPECT_LOG
  unset CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS
  unset CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE
  unset CLASH95_CAMPAIGN_ROUTE_TIMEOUT_SECONDS
  unset CLASH95_CAMPAIGN_ROUTE_SCRIPT_FILE
  unset CLASH95_CAMPAIGN_ROUTE_REQUIRE_OBJECTIVE
  unset CLASH95_CAMPAIGN_ROUTE_ENV_FILE
  unset CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET
  unset CLASH95_FIRST_MISSION_MOVE_EXPECT_LOG
  unset CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE
  unset CLASH95_FIRST_MISSION_MOVE_TIMEOUT_SECONDS
  unset CLASH95_FIRST_MISSION_ROUTE_ENV_FILE
}

validate_mission_id() {
  local mission_id="$1"
  local mission_number

  case "$mission_id" in
    [0-9][0-9]) ;;
    *)
      echo "campaign arc probe mission id must be two digits, got: $mission_id" >&2
      exit 2
      ;;
  esac
  mission_number=$((10#$mission_id))
  if [ "$mission_number" -lt 0 ] || [ "$mission_number" -gt 19 ]; then
    echo "campaign arc probe mission id must be in 00..19, got: $mission_id" >&2
    exit 2
  fi
}

run_first_mission_route() {
  local mission_id="$1"
  local start_mode="$2"
  local route_file_path="${3:-${route_file:-}}"

  if [ "$mission_id" != "00" ]; then
    echo "campaign arc probe first_mission_real_input runner is only valid for mission 00, got: $mission_id" >&2
    exit 2
  fi
  if [ -n "${CLASH95_CAMPAIGN_ROUTE_EXPECT_PRESET:-}" ]; then
    export CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET="$CLASH95_CAMPAIGN_ROUTE_EXPECT_PRESET"
  fi
  export CLASH95_FIRST_MISSION_MOVE_TIMEOUT_SECONDS="${CLASH95_CAMPAIGN_ROUTE_TIMEOUT_SECONDS:-900}"
  if [ "${CLASH95_CAMPAIGN_ROUTE_EXPECT_LOG:-}" ] && [ "$require_objective" = "1" ]; then
    export CLASH95_FIRST_MISSION_MOVE_EXPECT_LOG="$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOG"
  fi
  if [ "${CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE:-}" ]; then
    export CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE="$CLASH95_CAMPAIGN_ROUTE_EXPECT_LOGS_FILE"
  fi
  if [ -n "$route_file_path" ]; then
    export CLASH95_FIRST_MISSION_ROUTE_ENV_FILE="$route_file_path"
  fi

  case "$start_mode" in
    menu)
      echo "[campaign-arc] mission ${mission_id}: launching authentic menu route" >&2
      bash "$verify_first_mission" "$bootstrap_bin"
      ;;
    direct)
      echo "campaign arc probe direct mode is for isolated repair only and is not wired for mission 00 acceptance" >&2
      exit 1
      ;;
    *)
      echo "campaign arc probe unknown start mode for mission ${mission_id}: $start_mode" >&2
      exit 2
      ;;
  esac
}

run_generic_route_script() {
  local mission_id="$1"
  local start_mode="$2"
  local route_file_path="${3:-${route_file:-}}"

  if [ -z "${CLASH95_CAMPAIGN_ROUTE_SCRIPT_FILE:-}" ]; then
    echo "campaign arc probe route ${mission_id} uses generic_route_script but does not set CLASH95_CAMPAIGN_ROUTE_SCRIPT_FILE" >&2
    exit 2
  fi
  if [ "$start_mode" = "direct" ] && [ "${CLASH95_CAMPAIGN_ARC_ALLOW_DIRECT_ACCEPTANCE:-0}" != "1" ]; then
    echo "[campaign-arc] mission ${mission_id}: direct start mode is allowed only for quarantined repair/debugging" >&2
  fi

  export CLASH95_CAMPAIGN_ROUTE_START_MODE="$start_mode"
  export CLASH95_CAMPAIGN_ROUTE_REQUIRE_OBJECTIVE="$require_objective"
  if [ -n "$route_file_path" ]; then
    export CLASH95_CAMPAIGN_ROUTE_ENV_FILE="$route_file_path"
  fi

  echo "[campaign-arc] mission ${mission_id}: launching generic route script start=${start_mode}" >&2
  bash "$verify_route_script" "$bootstrap_bin" "$mission_id" "$route_file_path"
}

print_route_readiness_summary() {
  route_summary="$repo_root/tests/summarize_campaign_arc_routes.sh"
  if [ -f "$route_summary" ]; then
    echo "[campaign-arc] route readiness summary:" >&2
    CLASH95_CAMPAIGN_ARC_ROUTE_DIR="$route_dir" bash "$route_summary" >&2 || true
  fi
}

completed=0
blocked=0

for mission_id in $missions; do
  validate_mission_id "$mission_id"

  route_file="$route_dir/mission_${mission_id}.env"
  if [ ! -f "$route_file" ]; then
    echo "campaign arc probe route file does not exist: $route_file" >&2
    print_route_readiness_summary
    exit 2
  fi

  reset_route_env
  set -a
  # shellcheck source=/dev/null
  . "$route_file"
  set +a

  route_status="${CLASH95_CAMPAIGN_ROUTE_STATUS:-incomplete}"
  route_reason="${CLASH95_CAMPAIGN_ROUTE_REASON:-route status is not complete}"
  route_runner="${CLASH95_CAMPAIGN_ROUTE_RUNNER:-unimplemented}"
  route_start_mode="${start_mode_override:-${CLASH95_CAMPAIGN_ROUTE_START_MODE:-menu}}"

  echo "[campaign-arc] mission ${mission_id}: status=${route_status} runner=${route_runner} start=${route_start_mode}" >&2

  if [ "$dry_run" = "1" ]; then
    continue
  fi

  case "$route_status" in
    complete) ;;
    partial)
      if [ "$allow_partial" != "1" ]; then
        echo "campaign arc probe route ${mission_id} is partial: $route_reason" >&2
        print_route_readiness_summary
        echo "set CLASH95_CAMPAIGN_ARC_ALLOW_PARTIAL=1 to run it as a non-completion probe" >&2
        exit 1
      fi
      if [ "$require_objective" = "1" ]; then
        echo "[campaign-arc] mission ${mission_id}: partial route is running as an objective-required repair probe" >&2
      fi
      ;;
    incomplete)
      blocked=$((blocked + 1))
      if [ "$allow_incomplete" != "1" ]; then
        echo "campaign arc probe route ${mission_id} is incomplete: $route_reason" >&2
        print_route_readiness_summary
        echo "set CLASH95_CAMPAIGN_ARC_ALLOW_INCOMPLETE=1 only to enumerate or debug around incomplete routes" >&2
        exit 1
      fi
      continue
      ;;
    *)
      echo "campaign arc probe route ${mission_id} has unknown status: $route_status" >&2
      print_route_readiness_summary
      exit 2
      ;;
  esac

  case "$route_runner" in
    first_mission_real_input)
      run_first_mission_route "$mission_id" "$route_start_mode" "$route_file"
      ;;
    generic_route_script)
      run_generic_route_script "$mission_id" "$route_start_mode" "$route_file"
      ;;
    unimplemented)
      echo "campaign arc probe route ${mission_id} has no implemented runner: $route_reason" >&2
      print_route_readiness_summary
      exit 1
      ;;
    *)
      echo "campaign arc probe route ${mission_id} has unknown runner: $route_runner" >&2
      exit 2
      ;;
  esac

  completed=$((completed + 1))
done

echo "[campaign-arc] complete: missions=${missions} completed=${completed} blocked=${blocked}" >&2
