#!/usr/bin/env bash
set -euo pipefail

binary="${1:-build/bin/clash95_bootstrap}"

bash -n tests/validate_stack6_probe_suite.sh
bash -n tests/verify_first_mission_real_input_move_smoke.sh
bash -n tests/run_first_mission_stack6_manual_probe.sh
bash -n tests/run_first_mission_stack6_sequence_matrix.sh
bash -n tests/run_first_mission_stack6_battle_script_matrix.sh
bash -n tests/summarize_stack6_probe_artifact.sh
bash -n tests/generate_stack6_battlefield_click_sequences.sh

if [ "${CLASH95_VALIDATE_STACK6_DRY_RUN:-0}" = "1" ]; then
  CLASH95_STACK6_SEQUENCE_MATRIX_DRY_RUN=1 \
    bash tests/run_first_mission_stack6_sequence_matrix.sh "$binary" tests/stack6_sequences
  CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_DRY_RUN=1 \
    bash tests/run_first_mission_stack6_battle_script_matrix.sh "$binary" tests/stack6_battle_scripts
  exit 0
fi

CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET="${CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET:-route,world-click,playable-turn,end-turn,post-end-turn,turn-advance,stack6-manual-actions}" \
  bash tests/run_first_mission_stack6_manual_probe.sh "$binary"

if [ "${CLASH95_VALIDATE_STACK6_MATRICES:-0}" = "1" ]; then
  bash tests/run_first_mission_stack6_sequence_matrix.sh "$binary" tests/stack6_sequences
  bash tests/run_first_mission_stack6_battle_script_matrix.sh "$binary" tests/stack6_battle_scripts
fi
