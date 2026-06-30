# Current Status

Last consolidated: 2026-06-30.

## Disassembly Control-Flow Recovery: Complete

All 17 remaining `JUMPOUT(...)` "control flows out of bounds" decompiler scars in
`clash95.c` are recovered into authentic structured C, each backed by
`clash95.asm`. `grep -c JUMPOUT clash95.c` is `0`. Fifteen were shared
register-restore epilogues (now plain `return;`); ten were sprite-blitter thunks
that set an inner-loop pointer table (`dword_519B94`) and tail-jumped into the
shared span chunks `loc_46BB40` / `loc_46BB9A`, now recovered via the
`Blit_SpanDispatch_46BB40` / `Blit_SpanDispatch_46BB9A` helpers. See
`docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md` (2026-06-30 entry) for the full
per-address table. This removes the "JUMPOUT control-flow scars" blocker family
from AGENTS.md; the recovered C now has no out-of-bounds control-flow artifacts.

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
