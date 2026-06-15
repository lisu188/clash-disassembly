#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <path-to-clash95_bootstrap> [mission-id ...]" >&2
  echo "mission ids default to: 00 01 02 03 04 05 06 07 08 09" >&2
  exit 2
fi

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
bootstrap_bin="$1"
shift

if [ "$#" -gt 0 ]; then
  exec bash "$script_dir/run_campaign_arc_probe.sh" "$bootstrap_bin" "$@"
fi

export CLASH95_CAMPAIGN_ARC_MISSIONS="${CLASH95_FIRST_CAMPAIGN_ARC_MISSIONS:-00 01 02 03 04 05 06 07 08 09}"
exec bash "$script_dir/run_campaign_arc_probe.sh" "$bootstrap_bin"
