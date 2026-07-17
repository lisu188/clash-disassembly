#!/usr/bin/env bash
# Build (or refresh) the FAT32 "game drive" the Win98 guest sees as D:.
# Contains the clash install under D:\clash plus an editable D:\RUN.BAT the host
# rewrites between boots to pick a launch variant (menu / /A5 / /a1). No retail
# media is committed to the repo; this operates on the local install only.
set -euo pipefail
VM="${VM:-$HOME/clash95-vm}"
STAGE="$VM/gamestage"         # produced by the staging step (D:\clash contents)
IMG="$VM/game.img"
SIZE_MB="${SIZE_MB:-2600}"

[ -d "$STAGE/clash" ] || { echo "missing $STAGE/clash (run staging first)" >&2; exit 1; }

echo "creating $IMG (${SIZE_MB} MB FAT32)"
rm -f "$IMG"
truncate -s "${SIZE_MB}M" "$IMG"
mkfs.vfat -F 32 -n CLASHGAME "$IMG" >/dev/null

echo "copying game tree into D:\\clash (this takes a minute)"
mcopy -i "$IMG" -s -Q "$STAGE/clash" ::/clash

# Default RUN.BAT: main menu (no args). Rewrite with vm_runbat.sh for variants.
tools_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
"$tools_dir/vm_runbat.sh" menu

echo "game.img ready:"
mdir -i "$IMG" :: | head -20
