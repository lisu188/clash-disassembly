#!/usr/bin/env bash
# Launch the headless clash95 Win98 QEMU rig. No host window: -display none, QMP
# over a unix socket. Two modes:
#   vm_up.sh install   -> boot the Win98 SE ISO (CD first) to install onto hda
#   vm_up.sh run       -> boot the installed system (hda) with the game drive hdb
# Runs in the foreground; put it in the background from the caller and drive it
# via tools/vm/qmp.py $VM/qmp.sock.
set -euo pipefail
VM="${VM:-$HOME/clash95-vm}"
MODE="${1:-run}"
# Prefer a locally-staged ISO on ext4 — QEMU's random reads over drvfs (/mnt/c)
# stall in uninterruptible I/O and never open the QMP socket.
if [ -f "$VM/win98.iso" ]; then
  ISO="${ISO:-$VM/win98.iso}"
else
  ISO="${ISO:-/mnt/c/WindowsIso/Windows 98 SE/faXcooL_win_98_se_bootable.iso}"
fi
HDA="$VM/hda.qcow2"
GAME="$VM/game.img"
SOCK="$VM/qmp.sock"
FLOP="$VM/bootflop.img"
mkdir -p "$VM"
rm -f "$SOCK"

common=(
  -machine pc -cpu pentium2 -m 256 -vga cirrus
  -display none -audiodev id=snd0,driver=none
  -device sb16,audiodev=snd0
  -qmp "unix:$SOCK,server,nowait"
  -rtc base=2000-01-01
)

case "$MODE" in
  install)
    [ -f "$HDA" ] || qemu-img create -f qcow2 "$HDA" 2G >/dev/null
    # Boot the extracted CDBOOT floppy directly (order=a): the ISO's El Torito
    # 1.44M image is the standard Win98 CD boot disk; direct floppy boot is more
    # reliable under SeaBIOS than El Torito, and the ISO stays mounted as data.
    exec qemu-system-i386 "${common[@]}" \
      -drive file="$HDA",format=qcow2,if=ide,index=0,media=disk \
      -drive file="$ISO",format=raw,if=ide,index=2,media=cdrom \
      -fda "$FLOP" -boot order=a,menu=off
    ;;
  run)
    [ -f "$HDA" ] || { echo "no $HDA - run install first" >&2; exit 1; }
    exec qemu-system-i386 "${common[@]}" \
      -drive file="$HDA",format=qcow2,if=ide,index=0,media=disk \
      -drive file="$GAME",format=raw,if=ide,index=1,media=disk \
      -boot order=c,menu=off
    ;;
  *) echo "usage: vm_up.sh install|run" >&2; exit 2 ;;
esac
