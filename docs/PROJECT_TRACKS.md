# Project Tracks

The repository contains three related but independent recovery tracks. Progress in
one track must not be reported as completion of another.

## 1. DOS disassembly and semantic recovery

Primary artifacts:

- `clash.c`
- `DISASSEMBLY_STATUS.md`
- `MODULES.md`
- `tools/dos/`
- `tools/ida/`

Current baseline:

- 4,219 function markers are preserved.
- 4,218 functions decompile successfully.
- `0xFDF26` is the only failed function.
- 886 addresses have evidence-backed names.
- 704 of 2,015 functions in the embedded CLIPS region are named.

The next DOS milestone is not another text-level rename sweep. It is a fresh,
reviewed `clash95`-to-DOS cross-build transfer using disposable IDA databases,
complete calibration reviews, independent game-candidate reviews, master-map
rebuilding, and full regeneration verification.

A DOS batch is accepted only when generated `clash.c` preserves every marker,
prior name, collision invariant, and the expected failed-function set. Never edit
generated DOS C manually.

Longer-term DOS completion requires both:

1. all functions decompiled, including `0xFDF26`;
2. substantially broader evidence-backed semantic naming outside the CLIPS region.

## 2. Win95 reconstruction and SDL runtime

Primary artifacts:

- `clash95.asm`
- `clash95.map`
- `clash95.c`
- `bootstrap_main.c`
- `platform_sdl.h`
- `platform_sdl_runtime.c`
- `compat/decomp_runtime_stubs.c`

Current baseline:

- the 3,031-symbol `sub_XXXXXX` rename campaign is complete;
- all 17 `JUMPOUT` control-flow scars are recovered;
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

## 3. Campaign-route validation

Primary artifacts:

- `docs/STATUS.md`
- `docs/RUNTIME_MILESTONES.md`
- `tests/first_campaign_arc_routes/`
- `tests/second_campaign_arc_routes/`
- `artifacts/campaign-routes/`

Current baseline:

- missions `00..04` are complete through their direct-route gates;
- missions `05..19` remain partial direct-load probes;
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

1. Keep public CI, DOS regeneration checks, and the current SDL build green.
2. Run the first reviewed fresh cross-build transfer into the DOS name map.
3. Add mission-05 observability and recover its authentic completion route.
4. Prove Campaign-menu entry and at least one natural automatic mission advance.
5. Recover DOS function `0xFDF26` without manually patching generated C.
6. Recover `CSS_Init` and replace reached compatibility stubs behind the SDL seam.
7. Continue structure and semantic recovery only where it supports these active
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
