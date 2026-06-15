#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 2 ]; then
  echo "usage: $0 <path-to-clash95_bootstrap> <sequence-dir> [verify-args...]" >&2
  exit 2
fi

binary="$1"
sequence_dir="$2"
shift 2

if [ ! -d "$sequence_dir" ]; then
  echo "stack6 sequence directory does not exist: $sequence_dir" >&2
  exit 2
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
runner="$repo_root/tests/run_first_mission_stack6_manual_probe.sh"

found=0
passed=0
failed=0

for sequence_file in "$sequence_dir"/*; do
  if [ ! -f "$sequence_file" ]; then
    continue
  fi
  case "$(basename "$sequence_file")" in
    .*|README*|*.md) continue ;;
  esac

  found=$((found + 1))
  echo "[matrix] stack6 sequence ${found}: ${sequence_file}" >&2
  if [ "${CLASH95_STACK6_SEQUENCE_MATRIX_DRY_RUN:-0}" = "1" ]; then
    echo "[matrix] DRY-RUN ${sequence_file}" >&2
    continue
  fi
  if CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE="$sequence_file" \
    CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET="${CLASH95_FIRST_MISSION_MOVE_EXPECT_PRESET:-route,world-click,playable-turn,end-turn,post-end-turn,turn-advance,stack6-manual}" \
    CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_PATTERN="${CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_PATTERN:-${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_PATTERN:-}}" \
    CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_TIMEOUT="${CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_TIMEOUT:-${CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_EXPECT_TIMEOUT:-20}}" \
    CLASH95_KEEP_SMOKE_ARTIFACTS="${CLASH95_KEEP_SMOKE_ARTIFACTS:-1}" \
    bash "$runner" "$binary" "$@"; then
    passed=$((passed + 1))
    echo "[matrix] PASS ${sequence_file}" >&2
    if [ "${CLASH95_STACK6_SEQUENCE_MATRIX_STOP_ON_PASS:-0}" = "1" ]; then
      echo "[matrix] stop-on-pass enabled" >&2
      break
    fi
  else
    failed=$((failed + 1))
    echo "[matrix] FAIL ${sequence_file}" >&2
    if [ "${CLASH95_STACK6_SEQUENCE_MATRIX_STOP_ON_FAIL:-0}" = "1" ]; then
      exit 1
    fi
  fi
done

if [ "$found" -eq 0 ]; then
  echo "stack6 sequence directory contains no regular files: $sequence_dir" >&2
  exit 2
fi

if [ "${CLASH95_STACK6_SEQUENCE_MATRIX_DRY_RUN:-0}" = "1" ]; then
  echo "[matrix] dry-run complete: found=${found}" >&2
  exit 0
fi

echo "[matrix] complete: found=${found} passed=${passed} failed=${failed}" >&2
if [ "$failed" -ne 0 ]; then
  exit 1
fi
