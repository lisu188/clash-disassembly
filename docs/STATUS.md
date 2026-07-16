# Current Status

Last consolidated: 2026-07-16.

## Disassembly Control-Flow Recovery: Complete

All 17 `JUMPOUT(...)` "control flows out of bounds" decompiler scars in
the manifest-backed recovered subsystem sources directly under `src/` are recovered into
authentic structured C backed by `clash95.asm`. The canonical recovered C has
zero `JUMPOUT` code markers and no remaining out-of-bounds control-flow
artifacts. The full per-address table (register-restore epilogues and voice-mix
format-select thunks) is in
`docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`.

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
- The recovered implementation behind `clash95_recovered` and
  `clash95_bootstrap` now compiles as 138 GNU C17 translation units: 136
  address-ordered function-family files plus prelude/helper and quarantined
  state files. `data/recovered_sources.json` accounts for 4070 functions, and
  the split audit accounts for 3920 original address-marker chunks across 12
  subsystem object libraries. The split-only cutover removed the unified GNU89
  source, oracle targets, recovered include-C fragments, and compatibility
  symlinks; their old-to-new identities remain in `docs/SOURCE_PATH_MAP.csv`
  (see `docs/SOURCE_SPLIT.md`).
- The unit harness now compiles every case independently against instrumented
  split objects, with runner and compatibility stubs in dedicated files. Its
  manifest-backed, per-worker shard measurement currently covers 5963/6636
  executable lines (89.86%) across all 718 frozen pure functions, with zero
  functions uncovered (see `docs/UNIT_TESTING.md`).
- Before cutover, the final GCC split/oracle object gate resolved all 4070
  manifest functions and the complete default-visible symbol surface. It
  reported 4051 normalized-identical functions and 19 exact-hash reviewed
  cross-TU code-generation exceptions, with no missing, unexpected, or
  symbol-only entries. The recovered warning ratchet was originally seeded at
  146171 GCC / 147027 Clang 18 diagnostics; the P2 `(void)`-prototype wave and
  the P3 per-subsystem header narrowing reduced the reviewed baseline to 60143
  GCC diagnostics in 25 categories and 60455 Clang 18 diagnostics in 35
  categories (`data/recovered_warning_baseline.json` is authoritative). This is
  explicit cleanup debt, not a zero-warning result. Both compiler profiles
  reject category increases. Support code is compiled separately with warnings
  as errors.
- The first post-cutover Clang 18 cleanup wave now uses explicit 32-bit
  pointer-storage casts, standard no-argument `rand` calls, and assembly-backed
  source-pointer contracts for the CRT ANSI/wide string-copy helpers. The call
  sequences at `0x485453..0x485480`, `0x4854D5..0x485548`, and
  `0x485570..0x485598` preserve the EAX source plus EDX/EBX wide-buffer inputs
  shown in `clash95.asm`. Recovered byte
  strings now terminate two-digit `\xHH` escapes before following hexadecimal
  text, preventing the C lexer from consuming original character bytes. Clean
  GCC 13 and Clang 18 builds and the four asset-free CI CTest gates pass.
- Startup now initializes the assembly-backed 100 Hz performance-counter
  timebase; UI animation and timeout helpers run in recovered centiseconds.
- `UnitStack_ExecuteQueuedPath` now compares elapsed animation time against the
  unit-type interval byte preserved at `0x410DF5..0x410E0F`, rather than an
  uninitialized decompiler temporary. Repeated-turn queued marches no longer
  stall in the reached Mission `00` attack route.
- The executable-backed core of all 35 `UnitTypeMetadataRecord` entries now
  restores offsets `+8..+37` at the original 88-byte stride. This replaces the
  false one-element animation/combat/AP globals that made nonzero unit types
  read unrelated host memory; the later `+38..+87` tail remains unrecovered.
- Default CTest smoke routes cover menu liveness, direct route startup, save DAT
  format checks, and opt-in real-input probes.
- Campaign route env files are the canonical machine-readable status source.
  `tests/summarize_campaign_arc_routes.sh` currently reports:
  - missions `00..04` and `13`: `complete` (6/20)
  - missions `05..12` and `14..19`: `partial` direct-load evidence probes

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
completion through route gates. Mission `13` (second campaign) is also
route-complete via authentic top-menu turn advancement to its recovered
survival objective (`GAME_TURN_COUNTER > 10`, case `0xD`).

## Environment Requirement (runtime work)

Any runtime, boot, menu, or gameplay-route work requires the installed retail
Clash game data. The SDL platform layer (`src/platform/platform_sdl_runtime.c`
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
   found, `ResourceArchives_MountStartupArchives` calls `App_RequestQuit` with
   "Clash CD not found!"
   (`src/persistence/00441DC0_00443B60_persistence_001.c`).
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
`2`. With authentic metadata, player-0 stack `4` has a 20-point mixed-stack AP
floor rather than the former host-memory artifact `255`. The retained route
now advances its 33-node, 156-point path from `(71,44)` to `(47,58)` across
nine player-0 turns, manually reselecting and resuming the queued path exactly
where the original new-turn readiness logic requires it. The passing replay
records the final zero-length path, no friendly-attack failure marker, and a
fresh nonblank checkpoint at
`artifacts/campaign-routes/mission-05/20260714T155159Z-98803/summary.txt`.
The earlier one-turn tactical entry depended on the invalid 255-AP state and
is quarantined; tactical entry and the first exchange must now be revalidated
from the corrected arrival. Clearing that battle and the remaining owner-3
targets is still unproven. Full-menu campaign auto-advance across the completed
route gates also remains unproven.

## Next Target

Continue the retained mission `05` route from stack `4`'s authentic arrival at
`(47,58)`: attack stack `19`, revalidate stable manual tactical entry and the
first exchange with the restored frame counts, then clear and measure the
surviving Agordeh building/stacks without striking players `1` or `2`.
The next broader startup debt remains `CSS_Init` and its quarantined legacy
audio/device table.

## Evidence Trail

- Current milestone table: `docs/RUNTIME_MILESTONES.md`
- Full historical progress: `docs/archive/COMPILATION_PROGRESS.md`
- Rename/recovery log: `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- Pre-cutover normalized-disassembly exceptions:
  `docs/archive/SPLIT_DISASSEMBLY_EXCEPTIONS.json`
- CLIPS engine provenance + source cross-reference:
  `docs/archive/CLIPS_SOURCE_CROSSREF.md`
- Strategic-AI host-function API: `docs/AI_SCRIPTING_API.md`
- Route/probe notes: `docs/probes/`
