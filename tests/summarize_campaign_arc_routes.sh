#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
route_dir="${CLASH95_CAMPAIGN_ARC_ROUTE_DIR:-${CLASH95_FIRST_CAMPAIGN_ARC_ROUTE_DIR:-$repo_root/tests/first_campaign_arc_routes}}"
missions="${CLASH95_CAMPAIGN_ARC_MISSIONS:-00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19}"
require_complete="${CLASH95_CAMPAIGN_ROUTE_SUMMARY_REQUIRE_COMPLETE:-0}"

complete_count=0
partial_count=0
incomplete_count=0
missing_count=0
unknown_count=0

printf '%s\t%s\t%s\t%s\n' "mission" "status" "runner" "reason"

for mission_id in $missions; do
  route_file="$route_dir/mission_${mission_id}.env"
  status="missing"
  runner="missing"
  reason="route file is missing"

  if [ -f "$route_file" ]; then
    unset CLASH95_CAMPAIGN_ROUTE_STATUS
    unset CLASH95_CAMPAIGN_ROUTE_REASON
    unset CLASH95_CAMPAIGN_ROUTE_RUNNER
    set -a
    # shellcheck source=/dev/null
    . "$route_file"
    set +a
    status="${CLASH95_CAMPAIGN_ROUTE_STATUS:-incomplete}"
    runner="${CLASH95_CAMPAIGN_ROUTE_RUNNER:-unimplemented}"
    reason="${CLASH95_CAMPAIGN_ROUTE_REASON:-route status is not complete}"
  fi

  case "$status" in
    complete) complete_count=$((complete_count + 1)) ;;
    partial) partial_count=$((partial_count + 1)) ;;
    incomplete) incomplete_count=$((incomplete_count + 1)) ;;
    missing) missing_count=$((missing_count + 1)) ;;
    *) unknown_count=$((unknown_count + 1)) ;;
  esac

  printf '%s\t%s\t%s\t%s\n' "$mission_id" "$status" "$runner" "$reason"
done

echo
echo "complete_count=$complete_count"
echo "partial_count=$partial_count"
echo "incomplete_count=$incomplete_count"
echo "missing_count=$missing_count"
echo "unknown_count=$unknown_count"

if [ "$require_complete" = "1" ]; then
  if [ "$partial_count" -ne 0 ] || [ "$incomplete_count" -ne 0 ] || [ "$missing_count" -ne 0 ] || [ "$unknown_count" -ne 0 ]; then
    echo "campaign route summary is not all-complete" >&2
    exit 1
  fi
fi
