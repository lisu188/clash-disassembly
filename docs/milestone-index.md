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
| Lowercase `r` startup/shutdown | `ctest --test-dir build -R clash95_r_command_shutdown_smoke --output-on-failure` | `tests/verify_r_command_shutdown.sh` |
| Direct Campaign route smoke | `ctest --test-dir build -R clash95_direct_a_route_smoke --output-on-failure` | `tests/verify_direct_a_route_smoke.sh` |
| Direct first mission route smoke | `ctest --test-dir build -R clash95_direct_a0_route_smoke --output-on-failure` | `tests/verify_direct_a0_route_smoke.sh` |
| First mission playability probe | `ctest --test-dir build -R clash95_first_mission_playability_probe --output-on-failure` | `tests/run_first_mission_playability_probe.sh` |
| First mission attack probe | `ctest --test-dir build -R clash95_first_mission_attack_probe --output-on-failure` | `tests/run_first_mission_attack_probe.sh` |
| Campaign mission route scripts | `tests/run_campaign_route_script_smoke.sh` via CTest wrappers | `tests/first_campaign_arc_routes/`, `tests/frame_metrics.py` |

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
change intentionally promotes a small, documented evidence artifact.
