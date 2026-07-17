# Headless QEMU rig for original-vs-recovered frame capture

Purpose: run the **original** `clash95.exe` on real Win9x DirectDraw inside a
headless QEMU VM (no host window), capture the same game states the recovered
`clash95_bootstrap` renders, and produce pixel comparisons. The original faults
in its own DirectDraw startup under Wine (see
`../../artifacts/original-captures/COMPARISON_NOTES.md`), so a real Win9x guest
is required.

No retail media lives in the repo. These scripts operate on a local Win98 ISO
and the local `/mnt/c/clash` install only.

## Pieces

- `vm_up.sh install|run` — launch QEMU headless (`-display none`, QMP over a unix
  socket). `install` boots the extracted CDBOOT floppy with the ISO as data;
  `run` boots the installed `hda.qcow2` with the game FAT drive as `hdb`.
- `vm_gamefat.sh` — build `game.img` (FAT32 via mtools) = `D:\clash` + an
  editable `D:\RUN.BAT`. Requires a prior `gamestage/clash` tree.
- `vm_runbat.sh menu|A5|a1|raw '<args>'` — rewrite `D:\RUN.BAT` between boots to
  pick the launch variant, without booting.
- `qmp.py <sock> <op> …` — QMP client: `key`/`combo`/`type` (keystrokes),
  `shot <ppm>` (screendump), `mouse`/`click`, `powerdown`, `quit`, `raw`.
- `vm_shot.py <sock> <out.png> [label]` — screendump → PNG + stats
  (WxH colors mean_lum nonblack); used to gate the installer checkpoint loop.

## VM working files (in `~/clash95-vm/`, NOT committed)

`win98.iso` (ISO staged onto ext4 — QEMU random-reads over `/mnt/c` drvfs stall
in uninterruptible I/O), `bootflop.img` (El Torito 1.44M CDBOOT image extracted
from the ISO at LBA 21), `hda.qcow2` (2 GB Win98 target), `game.img` (FAT32
game drive), `qmp.sock`, `qemu.log`.

## Status (2026-07-17): headless install SOLVED on native QEMU

The "IO.SYS boot hang" was **misdiagnosed** — it was never an emulation bug.
Root cause: the Win98 CD-ROM Startup Menu auto-selects "Boot from Hard Disk"
after a ~3 s timeout, and with an **empty/unbootable hard disk** that jumps into
a blank MBR and executes zeros → the blinking-cursor "hang" (`nonblack` 0↔18).
It reproduced identically on QEMU 8.2.2 (WSL) and 11.0 (native), floppy and CD,
every CPU — because the trigger was the empty disk, not the host.

Fixes that unblocked a full headless install (native QEMU 11.0 / TCG):
1. **Boot the CD, not the empty disk.** Send `2` at the CD-ROM Startup Menu
   ("Boot from CD-ROM"). Do it early after boot/reset so the keystroke buffers
   into the menu; a trailing `ret` cascades through the second menu's default.
2. **Use the authentic MS compilation ISO** `C:\clash95-vm\WINDOWS_98_1.iso`
   (extracted from `C:\WindowsIso\...Collection (v6)\Windows 98 Collection\
   Windows 98 Collection - 1.7z`; Volume WIN98_1, MS CDIMAGE, EL TORITO boot,
   `WIN98\WIN98\SETUP.EXE` + CABs, product key **pre-filled**). Its custom boot
   menu even exposes Run-FDISK / Format-C / Run-Setup options directly.
3. **Durable writethrough cache** (`cache=writethrough` on the hda drive):
   a hard `Stop-Process` on QEMU otherwise drops the writeback cache and loses
   the FDISK partition + FORMAT. Prefer QMP `system_reset` (warm) between the
   FDISK→FORMAT→SETUP steps so one process holds the writes.
4. **Keyboard-drive the GUI wizard.** The `usb-tablet` absolute pointer is NOT
   honoured during setup (pre-USB-driver; setup reads the PS/2 relative mouse),
   so clicks miss. Use Tab/Space/Enter/Esc instead — e.g. License = Tab, Space
   (select "I accept"), Enter (Next); every subsequent page's default is Next
   (Enter); skip the Startup-Disk floppy step with Esc (Cancel) then Enter.

Install recipe (all headless, `qmp_win.ps1` over TCP:4444):
`qemu-img create -f qcow2 hda.qcow2 2G` → `vm_launch.ps1 -Boot d` → cascade `2`
into the boot menu → at DOS: `fdisk` (Enter×… primary max+active), Esc,
`system_reset` → cascade `2` → `format c: /u`, `y` → `d:`, `cd \win98\win98`,
`setup /is` → keyboard through the wizard → let post-copy reboots time out to
"Boot from Hard Disk". Product key pre-filled (W7XTC-…); user name required.

Full narrative + per-screen captures in
`../../artifacts/original-captures/COMPARISON_NOTES.md` and
`../../artifacts/original-captures/qemu-native/`.
