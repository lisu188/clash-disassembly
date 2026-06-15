#!/usr/bin/env bash
set -euo pipefail

out_dir="${1:-tests/stack6_sequences_generated}"
pattern="${CLASH95_STACK6_GENERATE_EXPECT_PATTERN:-battle_turn_loop_after_input_widgets}"
timeout="${CLASH95_STACK6_GENERATE_EXPECT_TIMEOUT:-8}"
reads="${CLASH95_STACK6_GENERATE_CLICK_READS:-6}"
gap="${CLASH95_STACK6_GENERATE_CLICK_GAP:-0.8}"
prelude="${CLASH95_STACK6_GENERATE_PRELUDE:-wait,20,0.4}"

mkdir -p "$out_dir"

index=1
for y in ${CLASH95_STACK6_GENERATE_Y_VALUES:-160 192 224 256 288 320 352}; do
  for x in ${CLASH95_STACK6_GENERATE_X_VALUES:-160 192 224 256 288 320 352 384 416 448}; do
    file="$out_dir/$(printf '%03d' "$index")_click_${x}_${y}.seq"
    {
      echo "# Generated stack6 battlefield click candidate at ${x},${y}."
      echo "# This per-step pattern should stay a single shell word."
      echo "# Override CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_PATTERN for stricter run-level success."
      for step in $prelude; do
        echo "$step"
      done
      echo "battle-click,${x},${y},${pattern},${timeout},${reads},${gap}"
    } >"$file"
    index=$((index + 1))
  done
done

echo "generated $((index - 1)) stack6 battlefield click sequence(s) in $out_dir" >&2
