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

## Live memory inspection of the ORIGINAL (2026-07-19)

The rig can now be used as a **debugger** on the original binary, not just a
frame-capture jig. This settles semantic questions that static analysis of the
recovered C cannot.

**Use HMP-over-QMP, not gdb, and not OllyDbg.**

- `-gdb tcp:0.0.0.0:1234` does work and QEMU listens, but **WSL cannot reach it**
  — the Windows host blocks the inbound connection and opening a firewall rule
  is a system security change. Don't go down this road.
- OllyDbg is the wrong shape for this rig: it is a GUI debugger that would have
  to run *inside* the guest and be driven by relative-mouse clicks over QMP.
- **QMP `human-monitor-command` works from PowerShell on 127.0.0.1:4444** and
  gives `x/` (virtual, current CR3), `xp/` (physical) and `info registers`. That
  is everything needed for memory sampling, with no firewall change.

Worked example, verified 2026-07-19:

```powershell
# read the gameData base pointer, then a player-record field
x/1xw 0x5202E4          # -> 0x00d00030   (gameData, per clash95.map 0004:000032E4)
x/8xb 0x41AD20          # -> 53 51 56 57 55 81 ec 44  (Unit_Attack prologue)
x/1hd 0xd228b1          # -> player 0's +1417 field (gameData + 0x22881)
```

Address arithmetic: player *n*'s field at record delta D is
`gameData + 140024 + n*1423 + D`. Sanity-check any session by reading known
fields first — `+140051` is-human (0 for every player in an all-AI game),
`+140039`/`+140043` camera column/row, `+140022` the turn counter (a **u16**;
reading it as a word picks up the neighbouring field).

Useful anchors: `gameData` at **0x5202E4**, `Unit_Attack` at **0x41AD20**
(clash95.map `0001:00019D20` + 0x401000).

## Guest auto-launch (fixed 2026-07-19)

The claim above that "the guest's StartUp runs `D:\RUN.BAT`" was **not true** of
`hda.qcow2` — `C:\WINDOWS\Start Menu\Programs\StartUp` was empty, so the VM just
booted to a bare desktop and nothing launched.

Fixed by setting the Win9x `WIN.INI` run hook instead of creating a shortcut
(one INI line, no `.lnk` authoring):

```
[windows]
run=D:\RUN.BAT
```

Applied offline. `qemu-nbd` is unusable here (WSL2 has no `/dev/nbd*`), so the
route is convert → mtools → convert back. Note the C: partition starts at LBA
**63** (offset 32256), and the conversion is near-instant because the image is
sparse:

```bash
qemu-img convert -f qcow2 -O raw /mnt/c/clash95-vm/hda.qcow2 /tmp/hda.raw
mtype  -i /tmp/hda.raw@@32256 ::/WINDOWS/WIN.INI > win.ini
#   edit: replace the empty "run=" line with "run=D:\RUN.BAT", keeping CRLF
mcopy  -i /tmp/hda.raw@@32256 -o win.ini ::/WINDOWS/WIN.INI
qemu-img convert -f raw -O qcow2 /tmp/hda.raw /tmp/hda_new.qcow2
qemu-img check /tmp/hda_new.qcow2 && cp /tmp/hda_new.qcow2 /mnt/c/clash95-vm/hda.qcow2
```

Back up `hda.qcow2` before doing this, and shut the VM down first — editing a
disk under a running QEMU corrupts it. Verified: the guest now boots straight
into the game's world map with no interaction.

### Loading an arbitrary save with no menu interaction — `clash95.exe a`

Any command line whose **first character** is `a`/`A` (i.e. `a`, not `/a`) routes
`WinMain` to `WorldMap_Initialize` -> `SaveSlot_LoadGame(10)` -> `PlayGame`: a
direct auto-load of `save\10.dat`, bypassing the menu entirely. This is the only
way to put the original into an arbitrary game state headlessly.

Verified 2026-07-19: dropping a pristine `5.dat` in as `10.dat` (plus its `.fac`)
and launching `clash95.exe a` loads it — `turn=69`, `turn_owner=0` read live.

Distinguish the arg forms carefully:
- `a…`  -> load save slot 10
- `/A<d>` / `/a<d>` -> multiplayer map, **all five players AI**
- `r…`  -> boot/render smoke test, skips the game entirely
- no args -> main menu

So `/A5` is **not** campaign mission 5. `vm_runbat.sh`'s `A5` comment says
"direct campaign mission 5" — that is true only of the recovered bootstrap
harness (gated by `CLASH95_DIRECT_CAMPAIGN_MISSION`), never of the original.

**Timing (measured, and much faster than previously assumed):** with the WIN.INI
auto-launch, `gameData` becomes non-zero at about **t+48 s** for `/A5` and
**t+60 s** for the `a` save-load path, timed from QEMU start. Poll for
`x/1xw 0x5202E4` returning something **other than 0x00000000** — the page is
mapped and reads as zero for tens of seconds before the game initialises, so a
"can I read it" test gives a false positive. Earlier work here waited ~150 s,
which lands *inside* the ~2-minute wedge window rather than before it.

**Editing a save is not free.** A hand-crafted `10.dat` — pristine slot 5 with one
unit stack relocated (record row/col at `147174 + 725*i`, plus the occupancy word
at `556374 + 200*row + 2*col` set to the stack index and the old tile cleared to
`0xFFFF`) — **wedged the guest on load, reproducibly**, while the pristine file
loaded fine from the same image and the same launch path. So the two edits above
are *not* sufficient to keep a save consistent; something else (the `.fac`
sidecar, an army-fact invariant, or a checksum) also has to agree. Do not assume
a save edit is safe because the byte offsets look right — always A/B it against
the pristine file, which is what isolated this.

**Known open issue:** with `/A5` the original loads the multiplayer map and
renders it, but the turn counter stayed at 2 across several minutes of wall
clock, i.e. its turn loop is not advancing unattended. Whatever drives turn
advance in the original's MP path has not been identified. Until that is
understood, the rig is good for *static-state* memory inspection of the original
but not for observing state evolve over turns.

## Comparison results (2026-07-17)

- **Main menu** (same state both sides): `mad=2.17/255`, **0.7% differing
  pixels** — ALL localized to the six button labels (original=English,
  bootstrap=Polish → `g_LanguageIndex` config-read gap, task flagged) and the
  cursor. Dragons/banner/shield/knight/background pixel-identical.
- **All-AI multiplayer map 5** (`/A5` — NOTE: in the ORIGINAL this arg loads a
  multiplayer map, not campaign mission 5; the campaign direct-boot is a
  bootstrap harness addition gated by `CLASH95_DIRECT_CAMPAIGN_MISSION`):
  full frames diverge by AI-game moment, so the viewport-independent oracle is
  the overview-minimap panel (whole map rendered by each engine):
  `mad=2.38/255`, **0.6% differing** — residual is just the two viewport
  rectangles and moving unit dots. Terrain render pixel-identical.
- Noted for later: observer-mode fog display differs (original shows no
  unexplored-black in the all-AI view); campaign direct-boot camera starts at
  the scenario viewport with no selection (original multiplayer path
  auto-selects and follows AI stacks — different code path).

## Tile-by-tile comparison (2026-07-17, `tile_compare.py`)

Per-absolute-tile atlas comparison of the world view (64x64 cells, grid origin
(32,16); exact per-frame viewport recovered from the minimap's white box via
the MiniMap_* formulas — see the tool docstring). Verification: selftest
(recovered run-A vs run-B) = **34/34 tiles identical**; a one-tile shift
negative control collapses matching to 25% (only repeating plain grass
survives); the wedge frame is auto-rejected.

Original (13 frames, viewports (0,20)..(82,32)) vs recovered (481 frames):
16 tiles covered by both. Result — zero unexplained differences; every tile
falls into one of three *root-caused* buckets:

1. **sparse-pixel-mismatch (9 tiles):** ~3% of pixels per tile where the
   ORIGINAL draws a green ramp (95,135,63 / 103,151,71 / 87,127,55 ...) and
   the RECOVERED engine draws BLACK (0,0,0) — isolated speckles inside grass
   textures, consistent across frames. A recovered-engine palette/render bug
   (suspect: terrain sprite-code cycling tables or an uninitialized palette
   ramp), NOT a capture artifact. Follow-up task filed.
2. **fog-black-mismatch (3) + content-mismatch (4):** the recovered all-AI
   game keeps fog-of-war black tiles (and omits multi-tile rock overhangs
   anchored on fogged neighbors) where the original reveals the whole map
   (`Map_RevealAllTilesForPlayer`, world_003.c:254-258). Related: the
   recovered all-AI camera NEVER moves (230 frames at (4,22)) while the
   original's AI-follow camera roams the map — the recovered all-AI game's
   AI/reveal path is not executing as recovered. Follow-up task filed.
   The content-mismatch bucket also contains AI units present in one engine's
   samples only (expected, different game moments).

Terrain pixels outside these buckets match exactly (selftest-grade identity).
Artifacts: `artifacts/tile-compare/m05/` (tiles.csv, heatmap.png,
worst_montage.png, summary.txt, maskaudit.png, frame indexes).

## Fix pass (2026-07-18) — findings from the tile comparison

**Fix A LANDED (commit c3791b1): DLX seam decoder.** The "black speckle" bug
was `Compat_RenderDeviceDrawMenuSprite`
(src/units/004191F0_0041A690_units_006.c) desynchronizing the format-0 sprite
stream (clamped run consumption + a 4-byte back-reference guess + mid-sprite
aborts), so data bytes >=0x80 were misread as transparent runs and black-filled
into terrain. Rewrote it byte-exact vs `Render_BlitCompressedSpriteRLE`
(full-run consumption, 1-byte back-reference per render_002.c:378-381,577-580,
no aborts). Result vs the original: 50k px changed (terrain detail restored),
fully-black fog tiles 3->0, **9/16 shared m05 tiles now pixel-identical**;
grass tiles visually confirmed identical (the residual is 6-bit-DAC + dither
pixel variance, so `tile_compare.py` now uses mean-abs-diff for identity, not
per-pixel max). Tool re-validated: same-binary selftest 34/34 identical,
1-tile-shift negative control collapses to 7%.

**Fix B (all-AI fog + no AI movement) = workstream C-B2, NOT a small bug.**
Diagnostic `/A5` run (CLASH95_TRACE_WORLD_ACTION_VERBOSE + RULES_ASSERT_FACT):
AI turns DO run (138 `ai_turn_*` markers), the CLIPS rulebase IS alive (8220
`oddzial` fact asserts with correct unit positions), no crash, all players
non-human (`c=0`) — but **zero unit moves**. The AI evaluates its agenda and
issues no movement, because the strategic-AI action host functions (`maszeruj`
etc.) are among the 87 unrecovered `Rules_Host*` handlers (`_UNKNOWN` data
placeholders; docs/AI_SCRIPTING_API.md). The parked camera and the 7
content-mismatch tiles (fog/black-strip edges at the frozen viewport) are all
downstream of this. Recovering the handlers is the already-planned C-B2 batch;
until it lands, the all-AI mode renders a static start position and the fog/
coverage tiles stay in the mismatch bucket.

**Fix B RE-VERIFIED post-C-B2 (2026-07-19) — NOT resolved; deeper AI-behaviour
gap.** C-B2 landed (all 87 `Rules_Host*` handlers recovered, `_UNKNOWN` count 0).
Re-ran `/A5` on a fresh HEAD build (120 s, STRIDE=4, 231 frames). The handlers
now DO run — 370 `ai_turn` markers, 185 `ai_turn_before/after_agenda`, 10,280
`ODDZIAL` fact asserts, 10,827 `world_action` — **but the camera is STILL frozen
at viewport (4,22) for all 231/231 frames** (identical to pre-C-B2), while the
original roams (8,25)..(82,32). Root cause is sharper than "no handlers":
every `world_action` is a repeated identical `unit_kill selected=1 a=9 b=25 c=1
cursor=400,300` (≈10 k times) and the march count is **`maszeruj`/`Unit_MoveTrack`
= 0** — the strategic AI issues combat/kill actions in a degenerate loop and
never MARCHES a unit, so nothing relocates and the camera has nothing to follow.
So C-B2 made the handlers callable but did not produce normal all-AI play; the
world-map fidelity comparison stays coverage-limited (post-C-B2 `score` vs the 13
original frames: 18 shared tiles = 0.2% of map, 9 identical-terrain / 9
content-mismatch; **fog-black-mismatch now 0** — Fix A resolved that bucket). The
all-AI camera/movement divergence is a distinct GAMEPLAY-track item (degenerate
strategic-AI agenda: kills-without-marches), NOT a capture-rig or handler-body
issue — hand off to the mission/gameplay track. Artifacts:
`artifacts/tile-compare/m05/cross-postcb2/` (heatmap, worst_montage, summary).

**Fix C (menu language) = deferred, needs asset analysis.** Source + built
binary both have `g_LanguageIndex = 1`, yet the recovered menu renders POLISH
while the original (same-named data, in the VM) renders ENGLISH. Decisive clue:
the middle-right slot is "multi player" (original) vs "misje"/missions
(recovered) — **different menu items, not a translation** — which points to
different retail menu assets (a Polish `menu\main.s32` with a missions button
vs an English one with multiplayer), i.e. an asset/data-provenance question,
not a `+g_LanguageIndex` index bug. Not touched per the "don't fix asset-layout
divergences" rule; needs verifying whether the VM's `menu\main.s32` is byte-
identical to `/mnt/c/clash`'s and whether that s32 is multi-language.

## Tactical-battle comparison (2026-07-19) — comparator built; recovered capture blocked by a striped-terrain artifact

**New comparator `tools/vm/battle_compare.py`** (sibling of `tile_compare.py` for
the battle view). Battle geometry from recovered source: 64x64 cells, origin
(32,16), a 7x7 window, board x[32,479] y[16,463], AXIS-TRANSPOSED vs the world
map (tileRow->screen X, tileCol->screen Y; `battle_002.c:898-899`), camCol always
0 (map width `+800` fixed at 7). No minimap -> camRow supplied via `--cam-row`.
Reuses tile_compare's MAD + 6-bit-DAC identity buckets; masks the right HUD
`x[480,639]` (always) + the conditional selected-unit info panel `x[335,479]`.
Only the RNG-free OPENING battle frame is comparable (combat is time-seeded RNG,
`units_004.c:1062-1064`). Subcommands index/score/exhibit; selftest = score of
two same-engine index sets + `--shift` negative control.

**Recovered opening-battle capture works** — `bash
tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 05
tests/first_campaign_arc_routes/mission_05_stack19_tactical_entry_probe.env`
(with `CLASH95_KEEP_SMOKE_ARTIFACTS=1`) marches player-0 stack 4 through 9 turns,
attacks player-3 stack 19, picks manual battle, and saves the checkpoint
`checkpoint-mission05-stack19-tactical-open.bmp` — a genuine 7x7 tactical board
(units, "Builder" nameplate, per-unit AP "2" row, right HUD).

**BLOCKER (finding, needs classification):** the recovered CAMPAIGN-direct-boot
frames — both the `march-arrival` and the `tactical-open` checkpoints, and the
late frame-000239 (persistent, not mid-draw) — render terrain with **black
horizontal stripes** across grass/water rows (trees/edges clean). The `/A5`
all-AI MULTIPLAYER capture path is CLEAN (its tile_compare score produced
identical-terrain tiles, impossible if striped), so the stripes are specific to
the campaign-route capture path, NOT universal. This must be classified — a
recovered-engine render defect in the campaign/battle terrain blit (candidate:
the same class as the Fix-A DLX decoder, or a scroll/dirty-rect present) vs a
frame-DUMP/present-timing artifact of the route harness — BEFORE an
original-vs-recovered battle pixel-comparison is meaningful (a striped recovered
frame vs a clean original would diff everywhere). Filed as a follow-up.
Recovered artifacts: `artifacts/campaign-routes/mission-05/recbattle-postcb2/`.
Next: resolve the stripes -> capture the ORIGINAL opening battle in the VM (shared
reserved-slot-10 save, two QMP clicks) -> `battle_compare.py score`.

## Fidelity milestone (2026-07-20): stripes fixed, DAC quantized, menus English — re-scored

Three landed fixes (all adversarially verified by worktree agents before commit):

- **Striped terrain RESOLVED (commit d353ad5).** The blocker above was a second
  DLX format-0 decoder defect: the opcode-0 back-reference offset was read as
  ONE byte (advance 1) where the original reads a 32-bit LE DWORD (advance 4;
  asm `sub esi,[ecx]` at 0x403492). Every back-reference sprite (water,
  mountains, textured edges — cross-tile delta compression) desynced into the
  black bands; literal-only grass never did, which is why /A5 grass looked
  clean. Offline decode: 486/959 backgr1.s32 tiles corrupt under 1-byte -> 0
  under 4-byte. Fresh captures confirmed stripe-free.
- **6-bit VGA DAC quantization (commit bde2940).** The SDL present now
  quantizes each palette channel with the VM-verified expansion
  `(c & 0xFC) | (3 * ((c >> 2) & 1))` — the textbook `(c&0xFC)|(c>>6)` was
  REFUTED by the rig (9.11% fixed-points; would worsen the match) while the
  implemented form is a fixed-point for 100.0% of VM-original menu pixels.
  Menu vs original: MAD 2.254 -> 0.835, differing pixels **94.70% -> 0.83%**
  (any-channel metric); art bit-exact except the sub-band.
- **Menu + options language/toggles (commit df32b73).** PlayGame_Dispatch's
  widget tables were qmemcpy'd 371 bytes into tiny arrays while the original's
  same-address stack ALIASES (main: v121=+0x10, v119=-0x21; options:
  var_568/560/55C/533/4FE/4C9/591) were rebuilt as independent locals — the
  `+g_LanguageIndex` column adds and checkbox states missed the tables. Both
  tables are now declared at their real 371-byte extent and indexed directly.
  Main menu renders ENGLISH (load/campain/exit/options/multi player/credits);
  mad vs original 2.17 -> 1.43, pctdiff 0.7 -> 0.1. The Polish render was NOT
  a stale binary and NOT asset-provenance (main.s32 is one multi-language set,
  PL/EN/DE columns) — the earlier "Fix C deferred" conclusion is corrected.

**Post-fix world-map re-score** (tile_compare, --dac-normalize; recovered
captures at d353ad5, STRIDE=4 LIMIT=400):
- m05 selftest (runA vs runB): **34/34 identical-pixel = 100%**; `--shift 1,0`
  negative control collapses to 14.3%.
- m05 original(13f) vs recovered: **matched 15/18 = 83.3%** (1 identical-pixel,
  14 identical-terrain, 3 content-mismatch, fog-black 0) — up from 9/16 =
  56.2% pre-fix. Residual = the frozen all-AI camera/units (degenerate-AI
  follow-up).
- **m11 first-ever comparison** (map 100x100; original 8/9 frames indexed):
  **matched 26/27 = 96.3%** (1 identical-pixel, 25 identical-terrain, 1
  content-mismatch). Artifacts: `artifacts/tile-compare/m05/cross-poststripe/`,
  `artifacts/tile-compare/m11/cross/`.

Remaining to the "100% match, VM-verified" goal: options-screen runtime verify
(in flight), the tactical-battle opening-frame comparison (now unblocked), the
degenerate all-AI march/camera fix, and the residual menu 0.83% (cursor +
animated elements).
