# Runtime Milestones

This index points to current route evidence without duplicating the full
progress logs.

## Validation Commands

The canonical build/test/probe command reference is `docs/BUILD_AND_TEST.md`.
The milestone table below maps each route/runtime milestone to the test that
exercises it and the durable evidence it produces.

## Route Milestones

| Milestone | Primary command or test | Evidence location | Gap / next proof |
| --- | --- | --- | --- |
| Default main menu liveness | `ctest --test-dir build -R clash95_full_route_smoke --output-on-failure` | `tests/verify_full_route_smoke.sh`, `docs/archive/COMPILATION_PROGRESS.md` | Keep as smoke coverage while deeper campaign routes advance. |
| Visible main menu plus Exit | `ctest --test-dir build -R clash95_main_menu_exit_probe --output-on-failure` | `tests/run_main_menu_exit_probe.sh`, frame nonblank metrics | Opt-in real-input coverage depends on SDL/X11 availability. |
| Recovered 100 Hz runtime timebase | `ctest --test-dir build --output-on-failure` | `Timer_InitPerfCounterFrequency`, `Time_Now`, and the wait helpers; assembly address `0x420770` | `CSS_Init` and its quarantined legacy audio/device table remain separate startup debt. |
| Lowercase `r` startup/shutdown | `ctest --test-dir build -R clash95_r_command_shutdown_smoke --output-on-failure` | `tests/verify_r_command_shutdown.sh` | Smoke route only, not gameplay completion proof. |
| Direct Campaign route smoke | `ctest --test-dir build -R clash95_direct_a_route_smoke --output-on-failure` | `tests/verify_direct_a_route_smoke.sh` | Direct route remains diagnostic, not final campaign acceptance. |
| Direct first mission route smoke | `ctest --test-dir build -R clash95_direct_a0_route_smoke --output-on-failure` | `tests/verify_direct_a0_route_smoke.sh` | Direct route remains diagnostic, not final campaign acceptance. |
| First mission playability probe | `ctest --test-dir build -R clash95_first_mission_playability_probe --output-on-failure` | `tests/run_first_mission_playability_probe.sh`, stack selection plus split-move markers | Historical probe; route table now tracks mission `00` completion. |
| First mission attack probe | `ctest --test-dir build -R clash95_first_mission_attack_probe --output-on-failure` | `tests/run_first_mission_attack_probe.sh` | Historical first-mission attack coverage. |
| Starting castle economy dialog | `CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION=1 ctest --test-dir build -R clash95_castle_economy_regression --output-on-failure` | `tests/run_castle_economy_probe.sh`, castle hotspot and economy frame metrics | Opt-in real-input coverage depends on SDL/X11 availability. |
| Main-menu endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/main-menu-idle/latest.txt` | Soak probe only; artifacts are ignored unless promoted deliberately. |
| First-mission world-map endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=world-map-pan CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/world-map-pan/latest.txt` | Soak probe only. |
| Starting castle economy endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=castle-economy CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/castle-economy/latest.txt` | Soak probe only. |
| First-mission attack/autoresolve endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=first-mission-attack CLASH95_SOAK_DURATION_SECONDS=20 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/first-mission-attack/latest.txt` | Soak probe only. |
| Mission 04 route-replay endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=campaign-route CLASH95_SOAK_ROUTE_MISSION_ID=04 CLASH95_SOAK_DURATION_SECONDS=20 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/campaign-route/latest.txt` | Replays the now-complete canonical route; full-menu campaign auto-advance remains separate. |
| Direct multiplayer map visual/liveness probe | `CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 ctest --test-dir build -R clash95_multiplayer_map_probe --output-on-failure` | `tests/run_multiplayer_map_probe.sh`, `artifacts/multiplayer-maps/map-NN/latest.txt` | Opt-in diagnostic path using recovered `/A#` all-AI map loading, not campaign acceptance or human multiplayer menu proof. |
| Campaign mission route scripts | `tests/run_campaign_route_script_smoke.sh` via CTest wrappers | `tests/first_campaign_arc_routes/`, `tests/frame_metrics.py` | Route env statuses remain canonical. |
| Mission 04 complete canonical route | `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure` | `tests/first_campaign_arc_routes/mission_04.env`, `tests/first_campaign_arc_routes/mission_04_post_breach_probe.script`, and `artifacts/campaign-routes/mission-04/20260711T202215Z-195443/summary.txt` | Direct-boot route proves three assaults, empty-garrison capture, one objective completion, and a fresh nonblank final frame; full-menu auto-advance remains. |

Latest multiplayer-map sweep:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
CLASH95_MULTIPLAYER_MAP_IDS=0,1,2,3,4,5,6,7,8,9,10 \
CLASH95_MULTIPLAYER_MAP_PROBE_SECONDS=5 \
CLASH95_MULTIPLAYER_MAP_SAMPLE_INTERVAL_SECONDS=2 \
CLASH95_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT=24 \
CLASH95_MULTIPLAYER_MAP_MAX_COPIED_FRAMES=4 \
CLASH95_MULTIPLAYER_MAP_MAX_LOG_BYTES=1000000 \
  bash tests/run_multiplayer_map_probe.sh build/bin/clash95_bootstrap
```

This passed on 2026-06-16 for recovered map IDs `0..10`, corresponding to
`multi1.map` through `multi11.map`. Each map artifact under
`artifacts/multiplayer-maps/map-NN/` records one load marker, one PlayGame
marker, capped frame evidence, and nonblank latest-frame metrics.

Map ID `0` also passed a 30-second no-trace soak:

```sh
CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=multiplayer-map \
CLASH95_SOAK_MULTIPLAYER_MAP_IDS=0 CLASH95_SOAK_DURATION_SECONDS=30 \
CLASH95_SOAK_SAMPLE_INTERVAL_SECONDS=5 \
CLASH95_SOAK_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT=72 \
CLASH95_SOAK_MULTIPLAYER_MAP_MAX_COPIED_FRAMES=8 \
CLASH95_SOAK_MULTIPLAYER_MAP_MAX_LOG_BYTES=1000000 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure
```

Durable evidence:
`artifacts/soak/multiplayer-map/20260616T104558Z-400385/summary.txt`.

## Known Route Status

Run this for the current campaign route table:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

At the time this index was last updated, missions `00` through `04` and `13`
were marked complete (6/20). Mission `04` has a passing three-assault Hopenberg
route: the final tactical return reports an empty garrison, capture transfers
the castle to player `0`, and the world loop logs `mission_objective_complete`.
Mission `13` completes its recovered survival objective through authentic
top-menu turn advancement. The remaining missions have partial direct probes.
The route env files remain the canonical machine-readable status source.

## Artifact Policy

Route and soak runs write logs, screenshots, and frame dumps under temporary
directories or `artifacts/`, ignored unless deliberately promoted. Retention
caps, pruning, and the promotion rule are documented in `docs/ARTIFACTS.md`.
