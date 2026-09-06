# Project Tracks

The repository contains two related but independent recovery tracks. Progress in
one track must not be reported as completion of another.

## 1. Win95 reconstruction and SDL runtime

Primary artifacts:

- `clash95.asm`
- `clash95.map`
- `data/recovered_sources.json`
- `src/<recovered-subsystem>/`
- `src/bootstrap/bootstrap_main.cpp`
- `src/platform/platform_sdl.h`
- `src/platform/platform_sdl_runtime.cpp`
- `src/compatibility/decomp_runtime_stubs.cpp`

Current baseline:

- the 3,031-symbol `sub_XXXXXX` rename campaign is complete;
- all 17 `JUMPOUT` control-flow scars are recovered;
- the recovered implementation is split-only: 4,157 functions in 140 GNU++20
  translation units across 12 subsystem object libraries;
- `clash95_bootstrap` builds and enters the authentic SDL-backed runtime;
- menu, direct campaign, save-format, multiplayer-map, and route probes exist;
- all recovered multiplayer map IDs `0..10` have direct-load visual/liveness
  evidence.

The remaining runtime work is behavioral and architectural rather than broad
placeholder renaming. Prioritize reached decompiler artifacts, compatibility
stubs, structure fields, and platform behavior that block the active runtime
frontier. The next broader startup debt is `CSS_Init` and its legacy audio/device
table.

Do not move original gameplay semantics into the SDL shim. Do not restore Win32
as the final platform target.

## 2. Campaign-route validation

Primary artifacts:

- `docs/STATUS.md`
- `docs/RUNTIME_MILESTONES.md`
- `tests/first_campaign_arc_routes/` (all mission IDs `00..19`, both campaigns)
- `artifacts/campaign-routes/`

Current baseline:

- missions `00..04` and `13` are complete through their direct-route gates
  (6/20);
- missions `05..12` and `14..19` remain partial direct-load probes;
- mission `05` is the first active campaign blocker;
- full Campaign-menu entry and automatic mission advancement remain unproven.

Mission `05` requires eliminating every player-3 building and stack without
attacking players `1` or `2`. Fresh original-backed visibility evidence on
2026-09-06 invalidates the retained march's first waypoint in the verified
turn-1 state: `(47,58)` and its eight neighbors are unrevealed, so the original
rejects that order. The historical nine-turn arrival remains retained but is
not a current validated starting point. The new first two legs `(71,44)` to
`(67,47)` and then `(63,49)` match the original's path, AP and complete
visibility bitmap after the reveal-propagation and route-driver repairs.
The reached `AI_TickNationPostTurn` accumulator is now repaired; original
instructions validate the exact captured scores, and both compiler builds
complete the second leg without the spurious queen proposal. Fresh original
and both compiler runs now extend this prefix through `(59,51)` on turn 3,
the AP-limited stop `(56,52)` on turn 4 and normal queued-path continuation to
`(55,53)` on turn 5, with 15 AP, an empty path and 179 matching visibility tiles.
The new sixth/seventh legs and both repaired compiler builds now reach `(50,50)`
on turn 6 with 6 AP, no path and 222 matching visibility tiles. The original uses
its real Load menu and an unchanged engine-authored turn-5 checkpoint for these
two legs; continuous original turn-1 replay is not claimed for this extension.
Unsupported manual builder-crossing exceptions are removed. The original's
actual Road action now matches both repaired C++ builds: overlays 867/879,
automatic movement to `(49,50)`, 2 AP and 228 matching visibility tiles on turn 6.
The original comparison uses real Load of an unchanged turn-6 checkpoint. Normal
turn refresh and the remaining bridge are the next C++ frontier; the separate
original-only route reaches `(47,58)` on turn 10. Historical builder-transfer
crossings are not proof.
The End Turn fixture waits for menu input readiness before clicking, as required
by the original hover/press order. Continue through original-accepted
destinations and normal AP/turn refresh, then revalidate manual tactical entry
against stack `19`, the first exchange and surviving owner-3 targets. Follow
`docs/STATUS.md` "Next Target". The older one-turn tactical entry also remains
quarantined because it relied on invalid 255-AP state.

A route may become `complete` only when it has:

- natural objective completion;
- no mission-failure marker;
- current nonblank frame evidence;
- deterministic retained checkpoints;
- repeatable regression success.

Direct mission boot remains diagnostic. Final campaign proof requires real menu
entry, natural completion, and automatic advancement.

## Immediate priority sequence

1. Keep public CI, the split-source audit, and the current SDL build green.
2. Rebuild the mission-05 march through destinations accepted by the original
   visibility gate and recover authentic completion, following `docs/STATUS.md`
   "Next Target".
3. Prove Campaign-menu entry and at least one natural automatic mission advance.
4. Recover `CSS_Init` and replace reached compatibility stubs behind the SDL seam.
5. Continue structure and semantic recovery only where it supports these active
   frontiers.

## Completion language

Use precise status terms:

- **decompiled**: Hex-Rays emitted a function body;
- **named**: an address has an evidence-backed semantic name;
- **buildable**: the reconstructed target compiles and links;
- **runnable**: the executable reaches a verified authentic runtime state;
- **route-complete**: one mission reaches its natural objective with visual and
  log evidence;
- **campaign-complete**: the campaign runs from the real menu through natural
  completion and automatic advancement.

Never use one of these milestones as a substitute for another.
