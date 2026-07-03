# Current Status

Last consolidated: 2026-07-03.

## Validated State

- The `sub_XXXXXX` placeholder-rename campaign is complete: all 3031 distinct
  `sub_` symbols carry evidence-based semantic names. Zero `sub_` identifiers
  remain as code symbols; the surviving `sub_` spellings are IDA address-anchor
  comments and trace strings only (per `docs/REVERSE_ENGINEERING.md` 3.1). The
  full old->new mapping lives in `docs/archive/SUB_RENAME_INDEX.md`.
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

2026-07-03 post-rename-campaign re-validation:

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
