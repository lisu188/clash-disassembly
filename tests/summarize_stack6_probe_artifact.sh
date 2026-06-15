#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 <artifact-dir>" >&2
  exit 2
fi

artifact_dir="$1"
log_path="$artifact_dir/first-mission-move.log"

if [ ! -d "$artifact_dir" ]; then
  echo "artifact directory does not exist: $artifact_dir" >&2
  exit 2
fi

if [ ! -f "$log_path" ]; then
  echo "artifact log does not exist: $log_path" >&2
  exit 2
fi

echo "== Stack6 Smoke Markers =="
grep -n -F "stack6-chase" "$log_path" | tail -n "${CLASH95_STACK6_SUMMARY_LINES:-120}" || true

echo
echo "== Mission Objective Markers =="
grep -n -F "mission_objective" "$log_path" | tail -n "${CLASH95_STACK6_SUMMARY_LINES:-120}" || true

echo
echo "== Stack10 / Stack6 Unit State =="
grep -n -e "after_turn_advance idx=10" -e "after_turn_advance idx=6" "$log_path" | tail -n "${CLASH95_STACK6_SUMMARY_LINES:-120}" || true

echo
echo "== Battle Actions =="
grep -n -e "battle_action_" -e "battle_turn_loop_after_input_widgets" "$log_path" | tail -n "${CLASH95_STACK6_SUMMARY_LINES:-120}" || true

echo
echo "== Attack / Battle Results =="
grep -n -e "enemy_attack_call" -e "enemy_attack_return" -e "unit_attack_autoresolve" -e "unit_attack_battle" "$log_path" | tail -n "${CLASH95_STACK6_SUMMARY_LINES:-120}" || true

echo
echo "== Frame Captures =="
find "$artifact_dir" -maxdepth 1 -type f -name 'frame-*.bmp' | sort | tail -n 5 || true

if command -v python3 >/dev/null 2>&1; then
  python3 - "$artifact_dir" <<'PY'
import glob
import os
import sys

artifact_dir = sys.argv[1]
frames = sorted(glob.glob(os.path.join(artifact_dir, "frame-*.bmp")))
if not frames:
    raise SystemExit(0)

try:
    from PIL import Image, ImageStat
except Exception as exc:
    print(f"frame stats skipped: {exc}")
    raise SystemExit(0)

sample = []
if frames:
    sample.append(frames[0])
if len(frames) > 2:
    sample.append(frames[len(frames) // 2])
if len(frames) > 1:
    sample.append(frames[-1])

for path in sample:
    image = Image.open(path).convert("RGB")
    stat = ImageStat.Stat(image)
    colors = image.getcolors(maxcolors=1000000)
    color_count = len(colors) if colors is not None else "many"
    mean = tuple(round(value, 2) for value in stat.mean)
    print(f"{os.path.basename(path)} size={image.size[0]}x{image.size[1]} mean={mean} colors={color_count}")
PY
fi
