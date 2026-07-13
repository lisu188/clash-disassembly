# Current Status

Last consolidated: 2026-07-13.

## Disassembly Control-Flow Recovery: Complete

All 17 remaining `JUMPOUT(...)` "control flows out of bounds" decompiler scars in
`clash95.c` are recovered into authentic structured C, each backed by
`clash95.asm`. `grep -c JUMPOUT clash95.c` is `0`. Seven were shared
register-restore epilogues (now plain `return;`); ten were voice-mix
format-select thunks (`Audio_SelectMixFormat{1..5}{Mono,Stereo}`) that set an
inner-loop pointer table (`g_Audio_MixFormatDispatchTable`) and tail-jumped into
the shared span chunks `loc_46BB40` / `loc_46BB9A`, now recovered via the
`Audio_MixVoiceSpanDispatch_46BB40` / `Audio_MixVoiceSpanDispatch_46BB9A`
helpers. See `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md` for the full
per-address table. This removes the "JUMPOUT control-flow scars" blocker family
from AGENTS.md; the recovered C now has no out-of-bounds control-flow artifacts.

## Validated State

- The `sub_XXXXXX` placeholder-rename campaign is complete: all 3031 distinct
  `sub_` symbols carry evidence-based semantic names. Zero `sub_` identifiers
  remain as code symbols; the surviving `sub_` spellings are IDA address-anchor
  comments and trace strings only (per `docs/REVERSE_ENGINEERING.md` 3.1). The
  full old->new mapping lives in `docs/archive/SUB_RENAME_INDEX.md`.
- The embedded rules engine is identified as CLIPS 6.0 (see
  `docs/REVERSE_ENGINEERING.md` Queue F provenance). A CLIPS 6.30-source
  cross-reference of the string-anchored Queue F functions found zero
  mis-namings (`docs/archive/CLIPS_SOURCE_CROSSREF.md`), and the game's
  strategic-AI host-function API - the commands `strateg\clash.dat` rules call
  into the engine - is decoded from the binary's own registration table in
  `docs/AI_SCRIPTING_API.md`.
- `clash95_bootstrap` is the current SDL-backed executable target.
- Startup now initializes the assembly-backed 100 Hz performance-counter
  timebase; UI animation and timeout helpers run in recovered centiseconds.
- Default CTest smoke routes cover menu liveness, direct route startup, save DAT
  format checks, and opt-in real-input probes.
- Campaign route env files are the canonical machine-readable status source.
  `tests/summarize_campaign_arc_routes.sh` currently reports:
  - missions `00..04`: `complete`
  - missions `05..19`: `partial` direct-load evidence probes

## Highest Runtime Milestone

The validated multiplayer-map frontier now covers direct all-AI map loading for
map IDs `0..10` (`multi1.map` through `multi11.map`) via the recovered `/A#`
route. Each map reaches the bootstrap load marker, enters `PlayGame`, remains
live through the 5-second probe window, and captures nonblank SDL frame
evidence. Map ID `0` also passed a 30-second no-trace `multiplayer-map` soak.

The canonical campaign-route frontier is now a complete direct-boot mission
`04` route. It breaches Hopenberg, clears the castle over three authentic
tactical assaults, and records successive battle returns with six, three, and
zero defenders. The empty-garrison return enters `Unit_CaptureBuilding`; the
world loop then logs `mission_objective_complete selected=-1 a=4 b=0 c=0`.
The definitive replay routed 347 inputs, retained all 61 checkpoints, and
recorded one objective completion. Its final objective checkpoint is current,
nonblank (`294268` nonblack pixels, `204` colors), and differs from the last
tactical checkpoint by a mean absolute pixel delta of `68.345217`. Durable
evidence is at
`artifacts/campaign-routes/mission-04/20260711T202215Z-195443/summary.txt`.

Earlier validated milestones include first-mission completion, mission `01`
shrine completion, mission `02` Treg Rock capture, and mission `03` survival
completion through route gates.

## Environment Requirement (runtime work)

Any runtime, boot, menu, or gameplay-route work requires the installed retail
Clash game data. The SDL platform layer (`platform_sdl_runtime.c`
`GetDriveTypeA`) resolves the game's CD/install root to `/mnt/<drive>/clash`
(or `/mnt/<drive>/CLASH`); `DetectGameCDPath` scans drive letters `C..Z` for a
directory there. With no such directory, boot aborts immediately with the
recovered `"Clash CD not found!"` message box and the process exits before any
menu or mission code runs.

Consequently, in an environment without the game data mounted (e.g. a fresh
web/CI container with no `/mnt/c/clash`):

- the `clash95_bootstrap` executable cannot boot, so the three route smokes
  `clash95_r_command_shutdown_smoke`, `clash95_direct_a_route_smoke`, and
  `clash95_direct_a0_route_smoke` fail by design (missing assets, not a
  regression); the rest of the default CTest suite still passes;
- only static work is possible: compilation/link, the unit-test coverage
  target (`-DCLASH95_COVERAGE=ON`, see `docs/UNIT_TESTING.md`), and
  asm-grounded (`clash95.asm`) source-fidelity edits.

To unblock runtime/gameplay work, mount a copy of the installed game at
`/mnt/c/clash` (or symlink a real install there), then the boot path and the
campaign-route probes can run and validate as documented in
`docs/RUNTIME_MILESTONES.md`.

Empirically, boot requires the data at three levels (verified by running
`clash95_bootstrap` headless):
1. `/mnt/<drive>/clash` must exist (else `DetectGameCDPath` -> "Clash CD not
   found!" at once);
2. the startup resource archives must mount from it (`data\music.res`,
   `gfx\*.res`, `sfx\*.res`, ... via `FileSystem_MountArchiveAtIndex`);
3. specific resources must resolve from those archives -- the title path
   `FileSystem_ResolveReadPath("gfx\backgr1.s32")` gates boot: if it is not
   found, `App_RequestQuit` shows "Clash CD not found!" (clash95.c:60756).
An empty `/mnt/c/clash` directory passes level 1 but still fails at level 3, so
a real install (not just the directory) is required.

## Active Blocker

Mission `05` is the first incomplete campaign route. In the active
nonzero-language branch, `Mission_CheckObjectiveComplete` requires every
building and stack owned by player `3` (Agordeh) to be eliminated. The retained
direct-load trace stops on player-3 building index `4`; scenario setup also
creates six player-3 stacks, including one remote stack at `(87,66)`.
`Mission_CheckFailureCondition` reads the mission failure flag set by
`Mission05_MarkFailureOnFriendlyAttack` when player `0` attacks players `1` or
`2`. No authentic sequence through that conquest
objective has yet been recovered, and full-menu campaign auto-advance across
the completed route gates also remains unproven.

## Next Target

Trace mission `05` through several authentic turn advances to measure allied
AI progress against player `3`, then choose the smallest route that removes
the surviving Agordeh castle/stacks without striking players `1` or `2`.
The next broader startup debt remains `CSS_Init` and its quarantined legacy
audio/device table.

## Evidence Trail

- Current milestone table: `docs/RUNTIME_MILESTONES.md`
- Full historical progress: `docs/archive/COMPILATION_PROGRESS.md`
- Rename/recovery log: `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- CLIPS engine provenance + source cross-reference:
  `docs/archive/CLIPS_SOURCE_CROSSREF.md`
- Strategic-AI host-function API: `docs/AI_SCRIPTING_API.md`
- Route/probe notes: `docs/probes/`

## Latest Validation

2026-07-13 mission-05 failure-predicate recovery:

- renamed the misidentified attack helper to `Mission05_MarkFailureOnFriendlyAttack` and the defeat dispatcher to `Mission_CheckFailureCondition`;
- introduced `MISSION_FAILURE_FLAG` for `gameData + 140021` while preserving mission-05 and mission-15 behavior;
- added the trace-gated `mission05_failure_friendly_attack` marker;
- added asset-independent tests for the friendly-attack failure branch and its exclusions;
- repaired four coverage cases that still referenced `dword_532048` instead of `g_MapData`.

2026-07-12 mission-04 completion validation:

- two complete direct route replays reached
  `unit_attack_building_battle_return selected=0 a=1 b=0 c=0` followed by
  `mission_objective_complete selected=-1 a=4 b=0 c=0`.
- the definitive capture-corrected replay completed in 1103.9 seconds with 347
  routed inputs, one objective completion, 61 retained checkpoints, and a
  nonblank current objective frame.
- the route runner now orders presented frames by modification time across
  battle-entry filename resets, resolves dynamic tactical selection from the
  clicked unit's occupant index, and waits for fresh attack completion before
  retrying bounded attacks.
- `bash tests/summarize_campaign_arc_routes.sh` reports
  `complete_count=5`, `partial_count=15`, and no unknown/missing routes.
- `bash -n` for the touched runner/route scripts and `git diff --check`
  passed.

2026-07-10 timing-recovery validation:

- `cmake --build build --target clash95_bootstrap -j2`: passed.
- `ctest --test-dir build --output-on-failure`: completed with zero failures;
  nine tests passed and eight guarded opt-in probes skipped normally.
- `clash95_main_menu_exit_probe`: passed with real input and nonblank frame
  validation under the restored 100 Hz timebase.
- `clash95_first_mission_attack_probe`: passed in 56.51 seconds after its
  battle-prompt harness timeout was recalibrated for authentic movement timing.
- The optional coverage target built, and the new timer assertions did not
  fail. Its full best-effort executable continues to report unrelated known
  decompiler-artifact failures/crashes and is not a clean CTest gate.
- The retained July mission-04 diagnostic remains partial: zero objective
  completions, eight blocker observations, and three defenders at the final
  battle return.

2026-07-03 post-rename-campaign re-validation:

- CLIPS follow-up (this session): identified the rules engine as CLIPS 6.0,
  cross-referenced string-anchored Queue F names against CLIPS 6.30 source
  (zero mis-namings), decoded the strategic-AI host-function registration
  table, and applied 2 name refinements plus 8 low/medium->high confidence
  upgrades. After each change `clash95_bootstrap` still compiled and linked
  clean; the index stayed at 3031 rows with no name collisions; markdown-link
  and whitespace checks passed.
- `sub_` inventory: 0 defined `sub_` functions and 0 non-comment `sub_` code
  references remain in `clash95.c`, `bootstrap_main.c`, or
  `platform_sdl_runtime.c`; all remaining spellings are comment/trace anchors.
- `docs/archive/SUB_RENAME_INDEX.md`: 3031 rows, 3031 distinct recovered names,
  no old->new name collisions; sampled recovered names all resolve to real
  source symbols.
- `git diff --check`: passed.
- `python3 -m json.tool RECOVERED_STRUCTURES.json`: passed.
- `python3 -m json.tool UNIT_TYPES_AND_STATS.json`: passed.
- `python3 tests/check_markdown_links.py`: passed.
- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: passed.
- `cmake --build build --target clash95_bootstrap -j4`: passed (compiles and
  links clean).
- `ctest --test-dir build --output-on-failure`: 12 pass, opt-in probes skipped;
  the 4 default route smokes (`full_route`, `r_command_shutdown`, `direct_a`,
  `direct_a0`) fail only because the retail Clash CD assets are absent in this
  container (`[platform_sdl] Clash: Clash CD not found!`) — environmental, not
  rename-induced.

## Previous Consolidated Validation

2026-06-16 focused validation:

- `git diff --check`: passed.
- `python3 -m json.tool RECOVERED_STRUCTURES.json`: passed.
- `python3 -m json.tool UNIT_TYPES_AND_STATS.json`: passed.
- `python3 tests/check_markdown_links.py`: passed.
- `bash -n` on the touched route/probe shell scripts: passed.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 bash tests/prune_artifacts.sh
  --dry-run`: passed; `artifacts/` measured `801730170` bytes against the
  768 MiB cap, with no recognized prune candidates.
- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: passed.
- `cmake --build build --target clash95_bootstrap -j2`: passed.
- `ctest --test-dir build -R clash95_multiplayer_map_probe
  --output-on-failure`: passed in the default skipped state.
- `ctest --test-dir build -R clash95_direct_a0_route_smoke
  --output-on-failure`: passed after the direct `/A#` parser-allocator reset.
- `CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1
  CLASH95_MULTIPLAYER_MAP_IDS=0,1,2,3,4,5,6,7,8,9,10
  CLASH95_MULTIPLAYER_MAP_PROBE_SECONDS=5
  CLASH95_MULTIPLAYER_MAP_SAMPLE_INTERVAL_SECONDS=2
  CLASH95_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT=24
  CLASH95_MULTIPLAYER_MAP_MAX_COPIED_FRAMES=4
  CLASH95_MULTIPLAYER_MAP_MAX_LOG_BYTES=1000000
  bash tests/run_multiplayer_map_probe.sh build/bin/clash95_bootstrap`: passed
  for all recovered multiplayer map IDs `0..10`.
- `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=multiplayer-map
  CLASH95_SOAK_MULTIPLAYER_MAP_IDS=0 CLASH95_SOAK_DURATION_SECONDS=30
  CLASH95_SOAK_SAMPLE_INTERVAL_SECONDS=5
  CLASH95_SOAK_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT=72
  CLASH95_SOAK_MULTIPLAYER_MAP_MAX_COPIED_FRAMES=8
  CLASH95_SOAK_MULTIPLAYER_MAP_MAX_LOG_BYTES=1000000
  ctest --test-dir build -R clash95_soak_probe --output-on-failure`: passed;
  durable summary
  `artifacts/soak/multiplayer-map/20260616T104558Z-400385/summary.txt`.
- `ctest --test-dir build --output-on-failure`: passed; 17 tests were reported,
  with guarded real-input turn, soak, multiplayer-map, and campaign-route
  regression tests skipped by their normal opt-in controls.
- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2000000
  ctest --test-dir build -R 'clash95_campaign_route_0[1-3]_regression'
  --output-on-failure`: passed for completed missions `01..03`.
- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=12
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  ctest --test-dir build -R clash95_campaign_route_04_regression
  --output-on-failure`: passed for the active mission `04` partial route through
  the first-assault defender-AI handoff; durable summary
  `artifacts/campaign-routes/mission-04/20260616T154441Z-570279/summary.txt`.
- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=12
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  bash tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04_post_breach_probe.env`: passed for
  the quarantined post-AI continuation; durable summary
  `artifacts/campaign-routes/mission-04/20260616T142830Z-516601/summary.txt`.
  This run observed the world-return branch; earlier tactical-control branch
  evidence remains at
  `artifacts/campaign-routes/mission-04/20260616T135453Z-487823/summary.txt`.
- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=24
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  bash tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04_post_ai_attack_probe.env`: passed;
  durable summary
  `artifacts/campaign-routes/mission-04/20260616T161142Z-587899/summary.txt`.
  This run proves the tactical-control branch can execute fresh counted post-AI
  attacks through defender `15,5` defeat.
- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=30
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  bash tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04_post_ai_branch_progress_probe.env`:
  passed; durable summary
  `artifacts/campaign-routes/mission-04/20260616T165526Z-619297/summary.txt`.
  This tactical-branch run defeats defender `15,5`, logs
  `battle_move_execute_return selected=2 a=15 b=5`, and retains
  `checkpoint-mission04-slot2-post-ai-occupy-15-5.bmp`.
- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=36
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  bash tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04_post_ai_branch_end_turn_probe.env`:
  passed; durable summary
  `artifacts/campaign-routes/mission-04/20260616T202028Z-688394/summary.txt`.
  This tactical-branch run defeats and occupies defender `15,5`, captures hover
  diagnostics, sends the recovered end-turn input, logs
  `battle_action_loop_exit_requested selected=2` and `battle_ai_turn_enter
  selected=1`, then observes `post_occupy_tactical_control_after_12`. Its env
  resets the presented-frame dump at battle entry so late checkpoint BMPs show
  actual tactical battle frames.
- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=38
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2500000
  bash tests/run_campaign_route_script_smoke.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04_post_ai_after_end_turn_attack_probe.env`:
  passed; durable summary
  `artifacts/campaign-routes/mission-04/20260616T203419Z-692412/summary.txt`.
  This tactical-branch run continues after the post-occupy end-turn marker,
  attacks defender `14,5`, logs
  `battle_attack_after_exchange selected=2 a=12 b=100 c=43`, and retains
  `checkpoint-mission04-slot2-post-occupy-attack-defender-14-5.bmp`.
- `bash tests/summarize_campaign_arc_routes.sh`: `complete_count=5`,
  `partial_count=15`, `incomplete_count=0`, `missing_count=0`.

## Carried-Forward Focused Route Evidence

The definitive mission `04` route evidence is
`artifacts/campaign-routes/mission-04/20260711T202215Z-195443/summary.txt`.
It records tactical garrison reductions `12 -> 6 -> 3 -> 0`, the final
empty-garrison strategic return, natural mission objective completion, and
current/nonblank frame evidence after that transition. The preceding
`20260711T195933Z-178905` replay independently proves the same gameplay and
objective sequence; its final checkpoint is intentionally not the visual proof
because that run exhausted the denser frame-sampling cap before the last
transition.

Mission `05` now owns the campaign-route frontier. Its canonical env remains a
partial direct-load blocker probe pending objective and actionable-state
recovery.
