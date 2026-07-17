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

## Status / known blocker (2026-07-17, native QEMU path exhausted)

Rig fully built; recovered reference frames captured under
`artifacts/original-captures/recovered-ref/`. The Win98 **guest boot** hangs in
real-mode IO.SYS before the installer menu, on **every** configuration tried.

Native-Windows QEMU (`qemu-w64` 11.0, driven by `qmp_win.ps1` over TCP:4444)
was installed to escape the WSL process-lifecycle issues — it runs stably, but
reproduces the WSL hang exactly, because no WHPX is available on this host so
both are **TCG-only** (same interpreter core).

Definitive diagnosis from a SeaBIOS debug console (`-debugcon file:...
-global isa-debugcon.iobase=0x402`):
- Clean BIOS hand-off — `Booting from Floppy/DVDCD... Booting from 0000:7c00`.
- Guest runs: `set VGA mode 3` ×2 (IO.SYS starts, re-inits text mode), then a
  black screen with a lone blinking cursor at (0,0): screendumps oscillate
  `nonblack=0` ↔ `nonblack=18` forever, no menu text. Timer IRQ alive, boot
  thread wedged on an early hardware probe (A20 / device detect) under TCG.
- Same signature across QEMU 8.2.2 (WSL) **and** 11.0 (native); floppy
  (`-boot a`) **and** CD El-Torito (`-boot d`); default CPU **and**
  `-cpu pentium2`.

Full evidence in `../../artifacts/original-captures/COMPARISON_NOTES.md`.

Remaining options (each needs a decision/input, so parked pending the user):
1. A one-off **visible** VM console to watch/steer the boot — precluded by the
   headless/no-popup constraint unless the user relaxes it.
2. A **different guest image** — a stock Microsoft Win9x boot disk (this ISO is
   a custom repack whose boot image is the finicky element) or a pre-installed
   Win9x `qcow2` to skip the install boot entirely.
3. Hardware acceleration (WHPX/KVM) — unavailable on this host.

The rig will drive capture unchanged the moment a guest reaches a desktop.
