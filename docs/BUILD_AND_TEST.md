# Build And Test

Use an out-of-tree build so generated files stay out of the source checkout.

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
```

The compatibility shorthand used by many recovery batches is also valid:

```sh
make clash95_bootstrap
```

## Default Tests

```sh
ctest --test-dir build --output-on-failure
```

Expected default skips include manual/real-input route, campaign-route, and soak
tests that require explicit opt-in environment variables.

## Metadata And Whitespace

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
python3 tools/check_markdown_links.py
git diff --check
```

## Route Summaries

```sh
bash tests/summarize_campaign_arc_routes.sh
```

Focused route/probe notes live under [docs/probes/](probes/).

## Opt-In Campaign Routes

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure
```

Direct mission boot is for quarantined route repair. Final campaign acceptance
must start from the real Campaign menu and advance naturally.

## Opt-In Soak Probes

```sh
CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_DURATION_SECONDS=120 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure

CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=world-map-pan \
  CLASH95_SOAK_DURATION_SECONDS=120 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure

CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=castle-economy \
  CLASH95_SOAK_DURATION_SECONDS=120 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure

CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_SCENARIO=campaign-route \
  CLASH95_SOAK_ROUTE_MISSION_ID=04 CLASH95_SOAK_DURATION_SECONDS=20 \
  ctest --test-dir build -R clash95_soak_probe --output-on-failure
```

## Artifact Pruning

```sh
CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 \
  bash tests/prune_artifacts.sh --dry-run
```

See [docs/artifacts.md](artifacts.md) before deleting retained evidence.
