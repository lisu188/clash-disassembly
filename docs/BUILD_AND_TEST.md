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
  tests/run_multiplayer_map_probe.sh \
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
`castle-economy`, `first-mission-attack`, `campaign-route`, and
`multiplayer-map`.

## Multiplayer Map Probes

Run the default direct all-AI multiplayer map probe for `/A0`:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
  ctest --test-dir build -R clash95_multiplayer_map_probe --output-on-failure
```

Run a wider map set:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
CLASH95_MULTIPLAYER_MAP_IDS="0 1 2 3 4 5 6 7 8 9 10" \
  ctest --test-dir build -R clash95_multiplayer_map_probe --output-on-failure
```

The probe is skipped by default. It launches Xvfb, follows the recovered `/A#`
multiplayer map path, checks bootstrap load/play markers, and validates a
nonblank presented frame. Details live in
`docs/probes/README_multiplayer_map_probe.md`.

## Important Environment Variables

- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1` enables route CTest probes.
- `CLASH95_ENABLE_SOAK_PROBE=1` enables soak probes.
- `CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1` enables direct multiplayer map
  visual/liveness probes.
- `CLASH95_SCREENSHOT_PREFIX` and `CLASH95_DUMP_PRESENTED_FRAMES_PREFIX`
  capture frame evidence for visual validation.
- `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` disables automatic artifact pruning for
  deep investigations.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES` sets the repo-wide `artifacts/` cap used by
  the pruning helper.

Focused probe documentation lives in `docs/probes/`.
