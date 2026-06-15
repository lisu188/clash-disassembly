#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "$script_dir/.." && pwd)"
bootstrap_bin="${CLASH95_MISSION00_GATE_BOOTSTRAP_BIN:-$repo_root/bin/clash95_bootstrap}"

cd "$repo_root"
make clash95_bootstrap

if [ ! -x "$bootstrap_bin" ]; then
  echo "mission-00 gate build probe expected executable after build: $bootstrap_bin" >&2
  exit 2
fi

exec bash "$script_dir/run_first_campaign_mission00_gate_probe.sh" "$bootstrap_bin" 00
