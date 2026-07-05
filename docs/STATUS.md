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

The validated multiplayer-map frontier now covers direct all-AI map loading for
map IDs `0..10` (`multi1.map` through `multi11.map`) via the recovered `/A#`
route. Each map reaches the bootstrap load marker, enters `PlayGame`, remains
live through the 5-second probe window, and captures nonblank SDL frame
evidence. Map ID `0` also passed a 30-second no-trace `multiplayer-map` soak.

The validated campaign-route frontier is mission `04`: the canonical regression
route reaches the castle tactical battle, breaches the gate with authentic wall
attacks, moves inside, defeats chained courtyard defenders through the first
assault's `15,4`/`15,5` boundary, and hands off to defender AI after authentic
tactical input. Quarantined opt-in continuations have now observed both
post-AI outcomes: a recovered world-return branch via
`unit_attack_building_battle_return selected=0 a=1 b=2 c=9`, and an earlier
attacker tactical-control branch at selected unit `2`. The tactical-control
branch now proves fresh counted authentic post-AI attacks through defender
`15,5` defeat after the branch marker, then moves selected unit `2` into the
cleared `15,5` battle tile, and ends that tactical turn through recovered
input. The post-occupy AI handoff returns to tactical control without crashing.
The next focused continuation also attacks defender `14,5` and logs
`battle_attack_after_exchange selected=2 a=12 b=100 c=43`. Remaining defender
cleanup, castle capture, objective completion, and full mission promotion are
still unproven.

Earlier validated milestones include first-mission completion, mission `01`
shrine completion, mission `02` Treg Rock capture, and mission `03` survival
completion through route gates.

## Active Blocker

Mission `04` still needs branch-specific continuation after the first-assault
defender-AI handoff. The tactical branch can now defeat defender `15,5`, occupy
the cleared tile, end the tactical turn, and attack defender `14,5`; the next
proof must continue that defender cleanup through capture. The world-return
branch still needs a stable castle reentry proof from the returned world state.
Both paths must continue without mutating objective state or skipping recovered
mission logic.

## Next Target

Short-term focus is expanding multiplayer-map probe coverage with opt-in
visual/liveness evidence beyond direct all-AI map loading, toward human-usable
multiplayer setup/input proof. The campaign repair target remains mission `04`
route fidelity through natural castle capture and objective completion.

## Evidence Trail

- Current milestone table: `docs/RUNTIME_MILESTONES.md`
- Full historical progress: `docs/archive/COMPILATION_PROGRESS.md`
- Rename/recovery log: `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- Route/probe notes: `docs/probes/`

## Latest Validation

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
- `bash tests/summarize_campaign_arc_routes.sh`: `complete_count=4`,
  `partial_count=16`, `incomplete_count=0`, `missing_count=0`.

## Carried-Forward Focused Route Evidence

The latest focused mission `04` route regression evidence remains:

- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=4
  CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=12
  CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2000000
  tests/run_campaign_route_regression.sh build/bin/clash95_bootstrap 04
  tests/first_campaign_arc_routes/mission_04.env`: passed for
  `artifacts/campaign-routes/mission-04/20260616T154441Z-570279`, with 240
  captured frames capped to 4 retained frames, 17 checkpoint frames capped to 12
  retained checkpoints, capped retained logs/frames, and
  `battle_ai_turn_enter selected=1`.

The latest quarantined post-AI tactical continuation evidence is
`artifacts/campaign-routes/mission-04/20260616T203419Z-692412/summary.txt`.
It observes the tactical-control branch, executes fresh counted authentic
attacks through defender `15,5` defeat, moves selected unit `2` into the cleared
`15,5` battle tile, captures hover diagnostics, ends the tactical turn, and
attacks defender `14,5`. Earlier post-occupy end-turn evidence remains at
`artifacts/campaign-routes/mission-04/20260616T202028Z-688394/summary.txt`;
earlier occupy-only evidence remains at
`artifacts/campaign-routes/mission-04/20260616T165526Z-619297/summary.txt`;
earlier defeat-only evidence remains at
`artifacts/campaign-routes/mission-04/20260616T161142Z-587899/summary.txt`.
The latest world-return branch observation remains
`artifacts/campaign-routes/mission-04/20260616T142830Z-516601/summary.txt`.
It observes `battle_ai_turn_exit selected=1 a=1 b=0` followed by
`unit_attack_building_battle_return selected=0 a=1 b=2 c=9` and retains a
nonblank `checkpoint-mission04-post-ai-branch-observed.bmp` checkpoint. Earlier
evidence at `artifacts/campaign-routes/mission-04/20260616T135453Z-487823/`
observed the alternate attacker tactical-control branch.
