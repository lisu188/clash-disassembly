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

## Status / known blocker (2026-07-17)

Rig fully built; recovered reference frames captured under
`artifacts/original-captures/recovered-ref/`. The Win98 **guest boot** under
QEMU 8.2.2 in this WSL2 environment did not reach the installer menu headlessly:
screendumps show only a 720x400 blinking-cursor text screen (18 nonblack px, no
menu text, no `cpu_reset` in `-d cpu_reset` traces), and the QEMU process is
unstable under WSL background supervision (a harness relay respawns it; detached
launches are reaped by WSL session teardown after ~30-70 s).

Next options to break the blocker:
1. Run QEMU on **native Windows** (qemu-w64) instead of WSL — avoids the WSL
   process-lifecycle and drvfs issues entirely; same scripts, Windows paths.
2. `wsl --shutdown` to clear the respawn loop, then a single foreground-logged
   boot with `-vga std -serial file` and a longer settle before the first shot
   (SeaBIOS + CDBOOT driver load can take 30-60 s in TCG).
3. Verify the boot visually with a one-off `-display gtk` run to confirm the
   floppy reaches the Win98 CD-ROM startup menu, then translate the keystrokes
   to the headless QMP loop.
