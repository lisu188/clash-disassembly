# Milestone Index

This index points to current route evidence without duplicating the full
progress logs.

## Current Validation Commands

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
bash tests/summarize_campaign_arc_routes.sh
CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 bash tests/prune_artifacts.sh --dry-run
git diff --check
```

Opt-in route regression:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure
```

## Route Milestones

| Milestone | Primary command or test | Evidence location |
| --- | --- | --- |
| Default main menu liveness | `ctest --test-dir build -R clash95_full_route_smoke --output-on-failure` | `tests/verify_full_route_smoke.sh`, `COMPILATION_PROGRESS.md` |
| Visible main menu plus Exit | `ctest --test-dir build -R clash95_main_menu_exit_probe --output-on-failure` | `tests/run_main_menu_exit_probe.sh`, frame nonblank metrics |
| Lowercase `r` startup/shutdown | `ctest --test-dir build -R clash95_r_command_shutdown_smoke --output-on-failure` | `tests/verify_r_command_shutdown.sh` |
| Direct Campaign route smoke | `ctest --test-dir build -R clash95_direct_a_route_smoke --output-on-failure` | `tests/verify_direct_a_route_smoke.sh` |
| Direct first mission route smoke | `ctest --test-dir build -R clash95_direct_a0_route_smoke --output-on-failure` | `tests/verify_direct_a0_route_smoke.sh` |
| First mission playability probe | `ctest --test-dir build -R clash95_first_mission_playability_probe --output-on-failure` | `tests/run_first_mission_playability_probe.sh`, stack selection plus split-move markers |
| First mission attack probe | `ctest --test-dir build -R clash95_first_mission_attack_probe --output-on-failure` | `tests/run_first_mission_attack_probe.sh` |
| Starting castle economy dialog | `CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION=1 ctest --test-dir build -R clash95_castle_economy_regression --output-on-failure` | `tests/run_castle_economy_probe.sh`, castle hotspot and economy frame metrics |
| Campaign mission route scripts | `tests/run_campaign_route_script_smoke.sh` via CTest wrappers | `tests/first_campaign_arc_routes/`, `tests/frame_metrics.py` |
| Mission 04 first gate-wall attack | `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure` | `artifacts/campaign-routes/mission-04/20260615T180944Z-78503`, trace-gated `wall_attack` marker |

## Known Route Status

Run this for the current campaign route table:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

At the time this index was added, missions `00` through `03` were marked
complete, mission `04` had a partial gate-attack route, and missions `05`
through `19` had partial direct probes. The route env files are the canonical
machine-readable status source.

## Artifact Policy

Route runs write logs, screenshots, frame dumps, and failure montages under
temporary directories or `artifacts/`. These outputs are ignored unless a future
change intentionally promotes a small, documented evidence artifact. Durable
mission/campaign route writers cap copied logs and frames, prune old per-mission
runs, and default to a 768 MiB repo-wide artifacts cap after high-volume runs.
Use `tests/prune_artifacts.sh --dry-run` before manual cleanup, and
`CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` to opt out during deep investigations.
