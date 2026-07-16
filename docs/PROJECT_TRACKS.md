# Project Tracks

The repository contains two related but independent recovery tracks. Progress in
one track must not be reported as completion of another.

## 1. Win95 reconstruction and SDL runtime

Primary artifacts:

- `clash95.asm`
- `clash95.map`
- `data/recovered_sources.json`
- `src/<recovered-subsystem>/`
- `src/bootstrap/bootstrap_main.c`
- `src/platform/platform_sdl.h`
- `src/platform/platform_sdl_runtime.c`
- `src/compatibility/decomp_runtime_stubs.c`

Current baseline:

- the 3,031-symbol `sub_XXXXXX` rename campaign is complete;
- all 17 `JUMPOUT` control-flow scars are recovered;
- the recovered implementation is split-only: 4,070 functions in 138 GNU C17
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
- `tests/first_campaign_arc_routes/`
- `tests/second_campaign_arc_routes/`
- `artifacts/campaign-routes/`

Current baseline:

- missions `00..04` and `13` are complete through their direct-route gates
  (6/20);
- missions `05..12` and `14..19` remain partial direct-load probes;
- mission `05` is the first active campaign blocker;
- full Campaign-menu entry and automatic mission advancement remain unproven.

Mission `05` requires eliminating every player-3 building and stack without
attacking players `1` or `2`. The next route batch must first add enough turn,
AI, building, stack, and objective observability to measure natural allied
progress. It may then construct the smallest authentic player route that reaches
`mission_objective_complete`.

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
2. Add mission-05 observability and recover its authentic completion route.
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
