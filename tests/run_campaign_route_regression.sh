#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 2 ] || [ "$#" -gt 3 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap NN [route-env-file]" >&2
  exit 2
fi

if [ "${CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION:-0}" != "1" ]; then
  echo "campaign route regression skipped; set CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 to run" >&2
  exit 77
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
bootstrap_bin="$1"
mission_id="$2"
route_env_path="${3:-$repo_root/tests/first_campaign_arc_routes/mission_${mission_id}.env}"

export CLASH95_CAMPAIGN_ROUTE_REQUIRE_FRAMES="${CLASH95_CAMPAIGN_ROUTE_REQUIRE_FRAMES:-1}"
export CLASH95_CAMPAIGN_ROUTE_REJECT_BLANK_FRAMES="${CLASH95_CAMPAIGN_ROUTE_REJECT_BLANK_FRAMES:-1}"
export CLASH95_CAMPAIGN_ROUTE_REQUIRE_WINDOW="${CLASH95_CAMPAIGN_ROUTE_REQUIRE_WINDOW:-1}"
export CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES="${CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES:-48}"
export CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES="${CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES:-12000000}"

exec bash "$repo_root/tests/run_campaign_route_script_smoke.sh" "$bootstrap_bin" "$mission_id" "$route_env_path"
