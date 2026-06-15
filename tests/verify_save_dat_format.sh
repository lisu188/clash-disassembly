#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
save_dir="${1:-/mnt/c/clash/save}"

if ! command -v python3 >/dev/null 2>&1; then
  echo "[save-dat] python3 is unavailable; skipping"
  exit 77
fi

if [[ ! -d "$save_dir" ]]; then
  echo "[save-dat] save directory is unavailable: $save_dir"
  exit 77
fi

tmp_dir="$(mktemp -d)"
trap 'rm -rf "$tmp_dir"' EXIT

for slot in 0 1 2 3 4 5; do
  dat_path="$save_dir/$slot.dat"
  fac_path="$save_dir/$slot.fac"
  if [[ ! -r "$dat_path" || ! -r "$fac_path" ]]; then
    echo "[save-dat] required save slot files are unavailable for slot $slot"
    exit 77
  fi
  python3 "$repo_root/tools/dump_save_dat.py" "$dat_path" --fac "$fac_path" --json > "$tmp_dir/$slot.json"
done

python3 "$repo_root/tools/dump_save_dat.py" --diff "$save_dir/0.dat" "$save_dir/1.dat" --json > "$tmp_dir/diff-0-1.json"

python3 - "$save_dir" "$tmp_dir" <<'PY'
import json
import os
import struct
import sys

save_dir = sys.argv[1]
tmp_dir = sys.argv[2]

expected_labels = {
    0: "asd",
    1: "asd",
    2: "cam",
    3: "cam",
    4: "xd",
    5: "xd",
}

dat_size = 586414
game_data_base = 0x10
map_width_offset = 140000
map_height_offset = 140004
view_left_offset = 140008
view_top_offset = 140012

for slot, label in expected_labels.items():
    dat_path = os.path.join(save_dir, f"{slot}.dat")
    fac_path = os.path.join(save_dir, f"{slot}.fac")
    with open(dat_path, "rb") as handle:
        raw = handle.read()
    with open(os.path.join(tmp_dir, f"{slot}.json"), "r", encoding="utf-8") as handle:
        decoded = json.load(handle)
    assert len(raw) == dat_size, (slot, len(raw))
    assert decoded["size"] == dat_size, (slot, decoded["size"])
    assert decoded["label"]["raw_hex"] == raw[:16].hex(), slot
    assert decoded["label"]["best_effort_text"] == label, (slot, decoded["label"])
    assert decoded["world"]["map_width_tiles"] == struct.unpack_from("<i", raw, game_data_base + map_width_offset)[0], slot
    assert decoded["world"]["map_height_tiles"] == struct.unpack_from("<i", raw, game_data_base + map_height_offset)[0], slot
    assert decoded["world"]["map_view_left"] == struct.unpack_from("<i", raw, game_data_base + view_left_offset)[0], slot
    assert decoded["world"]["map_view_top"] == struct.unpack_from("<i", raw, game_data_base + view_top_offset)[0], slot
    if os.path.getsize(fac_path) > 0:
        assert decoded["fac"]["starts_with_initial_fact"], (slot, decoded["fac"])

with open(os.path.join(tmp_dir, "diff-0-1.json"), "r", encoding="utf-8") as handle:
    diff = json.load(handle)
assert diff["size"] == dat_size
assert "regions" in diff

print("save-dat-format-ok")
PY
