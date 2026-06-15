# Status

Last updated: 2026-06-15.

## Validated State

- `clash95_bootstrap` builds from the recovered C/SDL path.
- The default CTest suite passes with the expected opt-in route/soak skips.
- JSON metadata validates for `RECOVERED_STRUCTURES.json` and
  `UNIT_TYPES_AND_STATS.json`.
- Campaign route table status from `tests/summarize_campaign_arc_routes.sh`:
  missions `00..03` are `complete`; missions `04..19` are `partial`.
- Mission `04` has direct route proof through Hopenberg castle battle entry and
  repeated authentic gate attacks ending with `wall_after=0`.

## Highest Runtime Milestone

The current highest mission-04 milestone is direct mission load, stack0 march to
Hopenberg, manual castle battle entry, repeated gate-wall attacks, and active
gate breach with nonblank tactical frames. Castle capture, battle exit, world
reload, and `mission_objective_complete` remain unproven.

## Active Blocker

Mission `04` still needs a behavior-faithful post-breach route: move/attack
inside the castle, defeat or clear the defending garrison as the original logic
requires, exit the tactical battle naturally, transfer/capture the castle, and
reach `Mission_CheckObjectiveComplete`.

## Next Target

Use the quarantined mission-04 post-breach probe to identify the first real
blocker after interior movement through the breached gate. Patch only defects
backed by `clash95.asm`, original binary/map evidence, or runtime traces.

## Documentation Hygiene Batch

This docs layout pass moved root historical Markdown into `docs/archive/`, moved
focused route/probe notes into `docs/probes/`, and replaced duplicated current
status text with this file plus `docs/RUNTIME_MILESTONES.md`.

## Validation Log

Latest docs-hygiene validation on 2026-06-15:

- `make clash95_bootstrap` passed.
- `ctest --output-on-failure` passed with 16 tests, 0 failures, and expected
  opt-in skips.
- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 ctest --output-on-failure -R
  clash95_campaign_route_04_regression` passed.
- `python3 -m json.tool RECOVERED_STRUCTURES.json` passed.
- `python3 -m json.tool UNIT_TYPES_AND_STATS.json` passed.
- `python3 tools/check_markdown_links.py` passed.
- `bash -n tests/run_campaign_route_script_smoke.sh
  tests/run_campaign_route_regression.sh tests/prune_artifacts.sh
  tests/run_clash95_soak_probe.sh` passed.
- `git diff --check` passed.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368
  bash tests/prune_artifacts.sh --dry-run --quiet` passed; `artifacts/`
  measured 761203724 bytes.
