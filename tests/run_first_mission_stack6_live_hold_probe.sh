#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <path-to-clash95_bootstrap> [verify-args...]" >&2
  exit 2
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

set -a
. "$repo_root/tests/first_campaign_arc_routes/mission_00.env"
set +a

export CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING=1
export CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_HOLD=1
export CLASH95_FIRST_MISSION_MOVE_TIMEOUT_SECONDS="${CLASH95_FIRST_MISSION_MOVE_TIMEOUT_SECONDS:-1200}"
export CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_PATTERN="${CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_PATTERN:-manual battle input loop reached}"

export CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE=
export CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT=
export CLASH95_STACK6_CHASE_MANUAL_BATTLE_EXPECT_PATTERN=
export CLASH95_STACK6_CHASE_CONTINUE_AFTER_MANUAL_BATTLE=0

export CLASH95_FIRST_MISSION_STACK7_CHASE_REPEATS=0
export CLASH95_FIRST_MISSION_STACK8_CHASE_REPEATS=0
export CLASH95_FIRST_MISSION_STACK9_CHASE_REPEATS=0

exec bash "$repo_root/tests/run_first_mission_stack6_manual_probe.sh" "$@"
