# Current Status

Last consolidated: 2026-06-16.

## Validated State

- `clash95_bootstrap` is the current SDL-backed executable target.
- Default CTest smoke routes cover menu liveness, direct route startup, save DAT
  format checks, and opt-in real-input probes.
- Campaign route env files are the canonical machine-readable status source.
  `tests/summarize_campaign_arc_routes.sh` currently reports:
  - missions `00..03`: `complete`
  - mission `04`: `partial`
  - missions `05..19`: `partial` direct-load evidence probes

## Highest Runtime Milestone

The validated campaign-route frontier is mission `04`: the route reaches the
castle tactical battle and breaches the gate with authentic wall attacks.
Objective completion and castle capture remain unproven.

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

## Active Blocker

Mission `04` still needs a natural route from post-breach tactical battle state
to castle capture/objective completion without mutating objective state or
skipping recovered mission logic.

## Next Target

Repair mission `04` route fidelity one blocker at a time, using direct campaign
mission boot only for quarantined debugging. Final acceptance remains real
Campaign menu entry plus natural mission completion and auto-advance.

## Evidence Trail

- Current milestone table: `docs/RUNTIME_MILESTONES.md`
- Full historical progress: `docs/archive/COMPILATION_PROGRESS.md`
- Rename/recovery log: `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- Route/probe notes: `docs/probes/`

## Latest Validation

2026-06-16 repo-hygiene validation:

- `git diff --check`: passed.
- `python3 -m json.tool RECOVERED_STRUCTURES.json`: passed.
- `python3 -m json.tool UNIT_TYPES_AND_STATS.json`: passed.
- `python3 tests/check_markdown_links.py`: passed.
- `bash -n` on the touched route/probe shell scripts: passed.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 bash tests/prune_artifacts.sh
  --dry-run`: passed; `artifacts/` measured `758379760` bytes with no prune
  candidates.
- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`: passed.
- `cmake --build build --target clash95_bootstrap -j2`: passed.
- `ctest --test-dir build --output-on-failure`: passed 16/16, with opt-in
  real-input, soak, and campaign-route probes skipped by their normal guards.
- `bash tests/summarize_campaign_arc_routes.sh`: `complete_count=4`,
  `partial_count=16`, `incomplete_count=0`, `missing_count=0`.
