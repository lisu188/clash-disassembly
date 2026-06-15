# Runtime Milestones

This file indexes current runtime and route evidence without duplicating the
large historical logs in [docs/archive/](archive/).

## Current Validation Commands

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
bash tests/summarize_campaign_arc_routes.sh
git diff --check
```

Opt-in mission-route check:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure
```

## Milestone Table

| Milestone | Command | Evidence | Gap |
| --- | --- | --- | --- |
| Default main menu liveness | `ctest --test-dir build -R clash95_full_route_smoke --output-on-failure` | `tests/verify_full_route_smoke.sh`, archive progress log | Wider interaction still covered by focused probes |
| Visible main menu plus Exit | `ctest --test-dir build -R clash95_main_menu_exit_probe --output-on-failure` | `tests/run_main_menu_exit_probe.sh`, nonblank frame metrics | Menu subtree coverage remains incremental |
| Lowercase `r` startup/shutdown | `ctest --test-dir build -R clash95_r_command_shutdown_smoke --output-on-failure` | `tests/verify_r_command_shutdown.sh` | Smoke-only path |
| Direct Campaign route smoke | `ctest --test-dir build -R clash95_direct_a_route_smoke --output-on-failure` | `tests/verify_direct_a_route_smoke.sh` | Direct route only |
| Direct first mission smoke | `ctest --test-dir build -R clash95_direct_a0_route_smoke --output-on-failure` | `tests/verify_direct_a0_route_smoke.sh` | Direct route only |
| First mission playability | `ctest --test-dir build -R clash95_first_mission_playability_probe --output-on-failure` | `tests/run_first_mission_playability_probe.sh` | Narrow split-move proof |
| First mission attack/autoresolve | `ctest --test-dir build -R clash95_first_mission_attack_probe --output-on-failure` | `tests/run_first_mission_attack_probe.sh` | Does not prove whole campaign arc |
| Starting castle economy dialog | `CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION=1 ctest --test-dir build -R clash95_castle_economy_regression --output-on-failure` | `tests/run_castle_economy_probe.sh`, frame metrics | Narrow economy-panel interaction |
| Main-menu endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/main-menu-idle/latest.txt` | Opt-in, short tier |
| World-map endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=world-map-pan CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/world-map-pan/latest.txt` | Opt-in, short tier |
| Castle/economy endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=castle-economy CLASH95_SOAK_DURATION_SECONDS=120 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/castle-economy/latest.txt` | Opt-in, short tier |
| First-mission attack endurance smoke | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=first-mission-attack CLASH95_SOAK_DURATION_SECONDS=20 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/first-mission-attack/latest.txt` | Opt-in, short tier |
| Mission 04 route replay endurance | `CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=campaign-route CLASH95_SOAK_ROUTE_MISSION_ID=04 CLASH95_SOAK_DURATION_SECONDS=20 ctest --test-dir build -R clash95_soak_probe --output-on-failure` | `tests/run_clash95_soak_probe.sh`, `artifacts/soak/campaign-route/latest.txt` | Opt-in, replay only |
| Campaign mission route scripts | `tests/run_campaign_route_script_smoke.sh` through CTest wrappers | `tests/first_campaign_arc_routes/`, `tests/frame_metrics.py` | Direct debug routes are not final campaign proof |
| Mission 04 gate breach | `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure` | Retained mission-04 route artifact with wall attacks ending `wall_after=0` | Castle capture and objective completion pending |

## Campaign Route Status

`tests/summarize_campaign_arc_routes.sh` is the canonical route status summary.
As of this documentation pass:

- `complete`: missions `00..03`
- `partial`: missions `04..19`
- `incomplete`, `missing`, `unknown`: none

Mission `04` remains the active route frontier. Direct debug routes are useful
repair probes, but final campaign acceptance requires real Campaign menu entry
and natural mission progression.

## Focused Probe Docs

Focused route/probe notes moved from `tests/README_*.md` to
[docs/probes/](probes/). The scripts remain under `tests/`.
