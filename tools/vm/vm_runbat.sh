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
tmp="$(mktemp)"
# CRLF line endings for DOS; run from D:\clash so relative asset paths resolve.
printf '@echo off\r\nD:\r\ncd \\clash\r\nclash95.exe%s\r\n' "$args" > "$tmp"
mcopy -i "$IMG" -o "$tmp" ::/RUN.BAT
rm -f "$tmp"
echo "RUN.BAT -> variant=$variant args='${args# }'"
