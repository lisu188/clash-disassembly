#!/usr/bin/env bash
# Rewrite D:\RUN.BAT inside game.img to select a launch variant, without booting.
# The guest's StartUp runs D:\RUN.BAT; changing it here changes what auto-launches.
#   vm_runbat.sh menu      -> title/main menu (no args)
#   vm_runbat.sh A5        -> direct campaign mission 5  (/A5)
#   vm_runbat.sh a1        -> direct campaign mission 11 (/a1, second campaign #1)
#   vm_runbat.sh raw '...' -> arbitrary trailing args after clash95.exe
set -euo pipefail
VM="${VM:-$HOME/clash95-vm}"
IMG="$VM/game.img"
variant="${1:-menu}"
case "$variant" in
  menu) args="" ;;
  A5)   args=" /A5" ;;
  a1)   args=" /a1" ;;
  raw)  args=" ${2:-}" ;;
  *)    args=" $variant" ;;
esac
# game.img built by vm_gamefat.sh is a PARTITIONED disk (MBR + one FAT32-LBA
# partition), not a bare FAT volume, so mtools must be pointed at the partition's
# byte offset. Without it mcopy fails with "init :: non DOS media" -- and because
# mcopy's exit status is swallowed by the pipeline, the script would otherwise
# report success while writing nothing. Derive the offset from MBR partition
# entry 1 (LBA start = little-endian u32 at 0x1BE+8) instead of hardcoding it, so
# this keeps working if the image is ever rebuilt with a different layout.
image_spec() {
  local img="$1" lba=""
  if [ "$(od -An -tx1 -j 510 -N 2 "$img" | tr -d ' ')" = "55aa" ]; then
    lba="$(od -An -tu4 -j 454 -N 4 "$img" | tr -d ' ')"
  fi
  if [ -n "$lba" ] && [ "$lba" -gt 0 ] 2>/dev/null; then
    printf '%s@@%s\n' "$img" "$((lba * 512))"
  else
    printf '%s\n' "$img"
  fi
}

spec="$(image_spec "$IMG")"
tmp="$(mktemp)"
# CRLF line endings for DOS; run from D:\clash so relative asset paths resolve.
printf '@echo off\r\nD:\r\ncd \\clash\r\nclash95.exe%s\r\n' "$args" > "$tmp"
mcopy -i "$spec" -o "$tmp" ::/RUN.BAT
rm -f "$tmp"
# Read it back: mcopy can fail in ways that still exit 0, so prove the write.
written="$(mtype -i "$spec" ::/RUN.BAT | tr -d '\r')"
case "$written" in
  *"clash95.exe${args}"*) ;;
  *) echo "RUN.BAT write did not take (read back: $written)" >&2; exit 1 ;;
esac
echo "RUN.BAT -> variant=$variant args='${args# }' (image=$spec)"
