# Current Status

Last consolidated: 2026-09-05.

## Structure Recovery: Tactical Slot Consumers

Track: Win95 reconstruction, the 31-byte unit record used by mission-05
tactical panels. `BattleUnitEntry` now names fatigue at +10 and morale at +11.
Both 31-byte transfer directions and independent panel assembly loads confirm
these fields. Storage stays unsigned; signed numeric consumers retain explicit
casts. The generated catalog remains 21 structures, now with 181 layout pins.

Typed fields repair five stance-related reads in three functions: the selected
battle panel and the melee/defence icon helpers. The previous short-pointer
arithmetic read byte +24 instead of the original +12. A regression varies the
unrelated tail byte and tests the original signed morale arithmetic. No
function, enum or unit type was renamed; remaining opaque spans are preserved.

The recorded GCC 13 and Clang 18 builds compile/link and pass all four
asset-free gates. Generated structures, metadata, subsystem headers and all
140 TU include blocks passed freshness checks at that gate. A concurrent
consumer shared-state header rollout appeared afterward; these results do not
validate that separate rollout. The unit harness reports 1058 passed, zero assertion failures and 530
isolated crashes; both added cases pass. Coverage is 6144/6649 lines (92.40%)
across all 718 frozen functions, with none uncovered. The crash count matches
the prior run but one existing CRT thread case replaces one timezone case in
the crash set; this is recorded, not treated as unchanged test behavior.
The first test build caught a packed
fixture alignment error, corrected by aligning its backing storage without
changing gameplay code.

An optional `CLASH95_GAME_ROOT` now permits private engine-authored saves.
The initial mission-05 snapshot and a fresh current-binary world probe pass.
The original loads that exact DAT/FAC pair through its real Load menu and
reaches the mission banner. Installed saves, executable bytes, staged work and
all warning/header/link/coverage baselines remain unchanged.

Fresh tactical entry remains unproven: the sparse-capture replay passes the
earlier viewport step but stops on turn 2 after a Next Unit click is missed.
No campaign route or tactical visual milestone is promoted. Evidence, exact
commands, failed attempts and next comparison state are under
`artifacts/structure-recovery/tactical-validation-20260905/`. Continue from
that evidence with observed input acknowledgements and the verified original
save; the popup pointer/render defects and metadata +38..+69 remain deferred.
Three attempts to capture the reconstruction's matching opening banner
produced no presented frames within their checkpoints, including after the
later cursor-bounds marker. A matching original/reconstruction pair remains
unavailable; the initial world frames must not be substituted for the modal.
That batch's final Markdown path check flagged a placeholder header filename
in the concurrently edited `docs/SOURCE_LAYOUT.md`; the shared-state rollout
below subsequently replaced it with an existing example path.

## Shared-State Modularization: Consumer Headers Active

Track: Win95 reconstruction, generated shared-state interface boundaries.
Eleven generated consumer headers now expose only each subsystem's referenced
shared declarations. Across 136 consumer TUs, declaration exposure fell from
32,776 to 11,994 (63.41%); the same 241 shared globals remain. The state
definition group and unit-test aggregate retain the complete shared header.
The measured surface records referenced versus visible DB identities, and the
audit checks slice ownership and consistency. The generator validates every
selected include block before writing and preserves surrounding source bytes.

After Ubuntu became available, all 45 tooling tests passed and regenerated
headers plus all 140 TU include blocks passed freshness checks. GCC 13 and
Clang 18 clean builds and all four asset-free gates pass. All 140 normalized
recovered object disassemblies and linked symbol addresses, sizes and order
match each compiler's pre-rollout baseline. All 1,180,500 preprocessed body
tokens match. Full-stream differences are limited to unchanged shared
declarations and their balanced generated strict-prototype warning wrappers.

The default headless GCC suite reports 10 passed, 3 failed and 8 skipped.
Main-menu Exit, boot/direct routes, shutdown and save-DAT checks pass. The
playability, attack and castle-economy probes time out on the same markers
with both the new and preserved pre-rollout executables. These existing probe
blockers keep the full default suite red; opt-in skips are not passes.

Coverage passes at 6144/6649 lines (92.40%) across all 718 frozen functions,
with zero uncovered functions. The unit harness reports 1056 passed, zero
assertion failures and 532 isolated crashes. All 530 prior crash names remain;
two additional cases crash in this run. The CTest wrapper tolerates isolated
crashes, so its pass is not a claim that every unit case succeeds.
Focused probes show the timezone case already varies in the earlier binary.
The padded-hex case reproducibly differs between the two coverage binaries
even with matched paths and environment, despite identical instructions in
the relevant helpers. Its fault reaches an existing one-byte formatter buffer
overrun. This difference remains explicit validation debt; the unit comparison
uses the preceding tactical batch, not a dedicated pre-rollout coverage build.
CRT recovery is deferred, and unchanged unit-harness behavior is not claimed.

Confidence is high in mechanical preservation: recovered source bytes outside
the generated blocks, storage, old headers, manifest and staged work match the
refreshed dirty baseline. Concurrent tactical-structure edits were preserved
and incorporated into that baseline before cutover. No functions, globals,
structures or fields were renamed. The two API and seven peer-edge ratchet
failures, plus each compiler's warning/link ratchet failures, are unchanged;
no saved limit was raised. Campaign status and visual-fidelity claims do not
advance in this header-only batch.

Evidence, failed attempts and exact commands are under
`artifacts/modularization/shared-state-20260905/rollout/`; the earlier WSL
access failure remains recorded in its parent directory. See the
[shared-state validation procedure](BUILD_AND_TEST.md#shared-state-header-rollout).

## Structure Recovery: Linux Validation

Track: Win95 reconstruction, validation of the recovered unit metadata and
its consumers. WSL execution returned for this batch. Fresh GCC 13 and Clang 18
builds compile and link, and both pass all four asset-free CTest gates. Full
subsystem header regeneration and TU include checks now pass. The earlier
WSL/header-pending notes below describe the preceding batches.

Regeneration exposed three false slider globals. Their values now alias the
original 112-byte backing at +12/+48/+84, preserving three 36-byte records and
the final sentinel. Assembly corroborates the layout. Four metadata indices
now explicitly retain the original signed-byte extension, removing the four
warnings introduced by this recovery. No unrelated function names changed.

The corrected unit harness reports 1056 passed, zero assertion failures, and
530 isolated crashes; the crash names exactly match the prior readiness run.
All nine added cases pass. Coverage is 6144/6647 lines (92.43%) across all 718
frozen functions, with zero uncovered functions. Both original PE copies still
match the recovered metadata; generated structs/constants and the split audit
pass. There are 21 generated packed structures and 179 size/offset assertions.

The headless reconstruction reaches a nonblank main menu and exits through
the real button. Original Wine debugging proved that the sampled entry code
mapped as zeros from the Windows-backed filesystem. A byte-identical copy on
Linux-native storage executes the correct startup jump. A Wine virtual desktop
then resolves the observed `DDERR_UNSUPPORTED` display-mode failure and reaches
the original English main menu. The fresh 640x480 comparison has mean absolute
RGB difference 1.560641/255 and 290923 nonmatching pixels (94.70%), including
widespread small color differences outside the cursor positions. No full
visual-equivalence claim is made. Tactical panels and gameplay fidelity are
not established by this menu checkpoint.
The existing `PlatformDac6Channel` conversion explains every sampled non-cursor
color difference; its QEMU Win98 reference and the current Wine palette output
remain distinct comparison environments. No platform palette code was changed.

Header-surface limits still reject two API count increases and seven dependency
edge increases. Warning-category and linked-layout ratchets also remain red;
the four newly introduced warnings were repaired, while the other increases
already existed in readiness evidence. No warning/header/link/coverage baseline
or staged work was changed. No campaign route was promoted. Exact commands,
failed attempts, final results, and captures are retained under
`artifacts/structure-recovery/linux-validation-20260905/`.

Next structure/runtime frontier: validate mission-05 tactical panels against
the now-running headless original, while keeping the
opaque metadata +38..+69 and type-40 scoring boundary explicitly unresolved.

## Unit Metadata Pointer Recovery

Track: Win95 reconstruction, unit metadata for mission-05 tactical panels.
Recovered the 12-byte localized-name triplet structure: 34 triplets contain
102 original strings, with types 33/34 sharing one triplet. Both PE copies
agree on every pointer target. A native pointer companion now resolves all
name, resource-key and movement-stem targets; original 88-byte records remain
unchanged. All 35 unit types use the selected language and exact original font
bytes. Four English helper labels were corrected: Taran, Highlander, Cyklop,
and Pegaz.

Sixteen functions changed in this batch. Four obsolete pointer globals were
removed, 28 missing panel format arguments were recovered from assembly, and
the unit-info morale branch's lost slot pointer was repaired. Generated struct
overlays now contain 21 structures and 179 size/offset assertions. Regression
assertions cover language selection, byte encoding, shared names, distinct
keys, and reserved null pointers.

Static checks pass: both original pointer sets and independently decoded C
strings agree, the split-source audit passes, and only the 16 reviewed function
hashes changed. The 28 repaired format calls now contain their numeric argument.

At the end of this pointer batch, WSL returned `E_ACCESSDENIED`, leaving
compilation, tests and subsystem regeneration pending. The later Linux
validation above resolves those execution items; fresh matching original
frames remain required. No campaign route or visual milestone is promoted. Evidence and
commands are under `artifacts/structure-recovery/unit-metadata-pointers-20260905/`.

Next: validate the retained mission-05 tactical entry and panel output.
Existing panel coordinates/render calls and the
battle blend omission still need original-frame evidence. The opaque +38..+69
metadata span and type-40 combat-score boundary remain unresolved.

## Unit Metadata Structure Recovery

Track: Win95 reconstruction, unit metadata used by the mission-05 tactical path.
The backing now preserves all 40 physical 88-byte records: 35 initialized unit
types and five zero reserved records. Both original PE copies agree on all
3,520 bytes. The C layout now names vision radius (+70), corpse sprite base
(+78), and auto-resolve casualty weight (+87), and retains +38..+69 as opaque
initialized bytes. The public map symbol `unit_stats` identifies +87; the old
alias to the corpse byte was incorrect. The tactical-role parser claim was
also rejected because its evidence belonged to CLIPS class parsing.

Twenty-two functions now use the typed backing for tail scalars, movement
stems, combat-strength scoring and production roster presence. Thirteen false
standalone globals and the obsolete `unit_stats` declaration were removed.
The original 35-type roster and five reserved slots remain distinct.

Static verification reconstructs the C initializer bytes and matches both
originals; struct/constant headers are current, the split-source audit passes,
and only the 22 reviewed function body hashes changed. New regression assertions
cover original values, reserved roster slots, vision, corpse frames and
production gates. Linux builds,
tests and frame/route verification have not run: WSL still returns
`E_ACCESSDENIED`. Full subsystem usage/header generation is also pending;
only the required declaration text was synchronized. No ratchet was relaxed.

The localized-name/resource-key pointer frontier left by this batch is resolved
above. Fresh mission-05 tactical evidence is still needed. The combat-score
predicate's acceptance of type 40 remains
unresolved; the physical table ends at index 39. See
[the unit/stat recovery report](archive/UNIT_TYPES_AND_STATS_REPORT.md) and
`artifacts/structure-recovery/unit-metadata-20260905/` for evidence and commands.

## Astra Readiness Audit

The repository now has a tracked Astra configuration and Linux/WSL onboarding.
The failed autostash reapplication is repaired: 77 line-ending-only conflicts
and 58 staged line-ending-only changes were removed. All four mission-11 work
files retain their original SHA256 hashes; all stashes and worktree references
are unchanged. Production source and canonical metadata remain identical to
the starting HEAD after the conflict repair.

Fresh GCC 13 and Clang 18 builds compile and link; both pass the four explicit
asset-free CTest gates. The recovered main-menu exit probe passes, and the
existing mission-13 direct route passed twice, including a replay with fresh
late-route frames. Campaign completion remains 6/20; no route was promoted.
The repaired unit-test callers build and pass; measured coverage is 92.36%
across all 718 frozen functions, with zero uncovered functions.

The continuation synchronized 31 stale declaration records with the existing
source/header contracts and represented two existing initialization helpers
with explicit source ownership. The generator now retains those helpers;
nine focused tests were added to CI. This follow-up initially had only static
checks because WSL returned `Wsl/Service/CreateInstance/E_ACCESSDENIED`.
The later structure-validation batch above runs the new tests, regeneration
and Linux build gates. The declaration-only step had left production C and
generated headers unchanged; later structure recovery is recorded above.

Full readiness remains blocked by header-surface/link ratchets,
per-category warning increases and two mission-00 probe expectation failures.
The original Wine startup and display-mode blockers were subsequently resolved
for the fresh menu capture above. No warning, link, header, or coverage baseline
has been relaxed; the menu evidence does not establish gameplay fidelity.
See [the readiness record](ASTRA_READINESS.md) for commands, evidence,
coverage results, the declaration follow-up, and deferred repairs.

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
  `clash95_bootstrap` now compiles as 140 GNU C17 translation units: 138
  address-ordered function-family files plus prelude/helper and quarantined
  state files. `data/recovered_sources.json` accounts for 4157 functions, and
  the split audit accounts for 4007 original address-marker chunks across 12
  subsystem object libraries. The split-only cutover removed the unified GNU89
  source, oracle targets, recovered include-C fragments, and compatibility
  symlinks; their old-to-new identities remain in `docs/SOURCE_PATH_MAP.csv`
  (see `docs/SOURCE_SPLIT.md`).
- The unit harness now compiles every case independently against instrumented
  split objects, with runner and compatibility stubs in dedicated files. Its
  manifest-backed, per-worker shard measurement currently covers 6144/6647
  executable lines (92.43%) across all 718 frozen pure functions, with zero
  functions uncovered (see `docs/UNIT_TESTING.md`).
- Before cutover, the final GCC split/oracle object gate resolved all 4070
  manifest functions and the complete default-visible symbol surface. It
  reported 4051 normalized-identical functions and 19 exact-hash reviewed
  cross-TU code-generation exceptions, with no missing, unexpected, or
  symbol-only entries. The recovered warning ratchet was originally seeded at
  146171 GCC / 147027 Clang 18 diagnostics; the P2 `(void)`-prototype wave and
  later reviewed cleanups reduced the saved baseline to 9763 GCC diagnostics
  and 9809 Clang 18 diagnostics (`data/recovered_warning_baseline.json` is
  authoritative). The fresh readiness audit above still fails category limits
  despite lower total warning counts. This is
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
- The validated executable-backed core of all 35 `UnitTypeMetadataRecord` entries
  restored offsets `+8..+37` at the original 88-byte stride. This replaced the
  false one-element animation/combat/AP globals that made nonzero unit types
  read unrelated host memory. The new full-table/tail recovery above now has
  compiler and unit evidence; tactical panel/frame validation remains pending.
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
