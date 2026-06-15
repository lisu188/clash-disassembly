# Build And Test

Run commands from the repository root.

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
```

`make clash95_bootstrap` may also be used in an already-configured build setup
when that target is available.

## Default Tests

```sh
ctest --test-dir build --output-on-failure
```

Default CTest intentionally skips opt-in real-input probes when their enabling
environment variables are absent.

## Metadata And Formatting Checks

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
python3 tests/check_markdown_links.py
git diff --check
```

Shell syntax checks for common route/probe scripts:

```sh
bash -n tests/run_campaign_route_script_smoke.sh \
  tests/run_campaign_route_regression.sh \
  tests/run_clash95_soak_probe.sh \
  tests/prune_artifacts.sh
```

## Campaign Route Probes

Summarize route readiness without launching the game:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

Run one opt-in route regression:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure
```

Run the full campaign arc wrapper only after every required route is marked
`complete`:

```sh
bash tests/run_campaign_arc_build_probe.sh
```

Run an already-built binary through the campaign arc runner:

```sh
bash tests/run_campaign_arc_probe.sh build/bin/clash95_bootstrap
```

## Soak Probes

```sh
CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_DURATION_SECONDS=120 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure
```

Useful `CLASH95_SOAK_SCENARIO` values include `world-map-pan`,
`castle-economy`, `first-mission-attack`, and `campaign-route`.

## Important Environment Variables

- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1` enables route CTest probes.
- `CLASH95_ENABLE_SOAK_PROBE=1` enables soak probes.
- `CLASH95_SCREENSHOT_PREFIX` and `CLASH95_DUMP_PRESENTED_FRAMES_PREFIX`
  capture frame evidence for visual validation.
- `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` disables automatic artifact pruning for
  deep investigations.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES` sets the repo-wide `artifacts/` cap used by
  the pruning helper.

Focused probe documentation lives in `docs/probes/`.
