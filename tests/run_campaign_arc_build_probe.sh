#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
bootstrap_bin="${CLASH95_CAMPAIGN_ARC_BOOTSTRAP_BIN:-$repo_root/bin/clash95_bootstrap}"

cd "$repo_root"

if [ "${CLASH95_CAMPAIGN_ARC_SKIP_ROUTE_PREFLIGHT:-0}" != "1" ]; then
  CLASH95_CAMPAIGN_ROUTE_SUMMARY_REQUIRE_COMPLETE=1 \
    bash "$script_dir/summarize_campaign_arc_routes.sh"
fi

make clash95_bootstrap

if [ ! -x "$bootstrap_bin" ]; then
  echo "campaign arc build probe expected executable after build: $bootstrap_bin" >&2
  exit 2
fi

exec bash "$script_dir/run_campaign_arc_probe.sh" "$bootstrap_bin"
