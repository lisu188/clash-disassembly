# Multiplayer Map Probe

`tests/run_multiplayer_map_probe.sh` is an opt-in visual/liveness probe for the
recovered direct all-AI multiplayer map path.

The probe uses the existing `/A#` command-line route. In recovered runtime flow
that route initializes the world map, calls
`Scenario_LoadAllAiMultiplayerMapAndInitView(index)`, loads `multi%d.map`, and
enters `PlayGame`. The probe does not add a gameplay shortcut and does not mark
objectives or route state.

Run one map after building:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
  ctest --test-dir build -R clash95_multiplayer_map_probe --output-on-failure
```

Run several maps in one probe:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
CLASH95_MULTIPLAYER_MAP_IDS="0 1 2 3" \
  ctest --test-dir build -R clash95_multiplayer_map_probe --output-on-failure
```

Map IDs are zero-based and currently limited to the recovered menu range
`0..10`, corresponding to `multi1.map` through `multi11.map`.

## Evidence

Each successful map run requires:

- `[bootstrap] direct-mission-load`
- `[bootstrap] direct-mission-playgame`
- process liveness through the configured probe window
- at least one presented SDL frame
- a nonblank/latest-frame check via `tests/frame_metrics.py`

The 2026-06-16 sweep passed map IDs `0..10` with
`CLASH95_MULTIPLAYER_MAP_PROBE_SECONDS=5`, capped artifacts, and nonblank frame
checks for each map. A focused no-trace soak also held map ID `0` for
30 seconds through the `multiplayer-map` soak scenario.

Artifacts are written under:

```text
artifacts/multiplayer-maps/map-NN/<timestamp>-<pid>/
```

Each run keeps a capped `multiplayer-map.log`, sampled frame BMPs in `frames/`,
and `summary.txt`. The per-map `latest.txt` file points at the latest summary.

## Controls

- `CLASH95_MULTIPLAYER_MAP_IDS`: space, comma, or colon separated map IDs.
  Defaults to `0`.
- `CLASH95_MULTIPLAYER_MAP_PROBE_SECONDS`: post-PlayGame liveness window.
  Defaults to `6`.
- `CLASH95_MULTIPLAYER_MAP_SAMPLE_INTERVAL_SECONDS`: runtime frame/RSS sample
  interval. Defaults to `5`.
- `CLASH95_MULTIPLAYER_MAP_FRAME_DUMP_LIMIT`: presented-frame dump cap.
  Defaults to `96`.
- `CLASH95_MULTIPLAYER_MAP_MAX_COPIED_FRAMES`: retained frame sample cap.
  Defaults to `24`.
- `CLASH95_MULTIPLAYER_MAP_MAX_LOG_BYTES`: retained log cap. Defaults to
  `4000000`; set `0` to retain full logs.
- `CLASH95_MULTIPLAYER_MAP_REQUIRE_FRAME_PROGRESSION=1`: optionally require a
  loose frame-difference check between the first and latest captured frames.
- `CLASH95_MULTIPLAYER_MAP_KEEP_RUNS`: retained durable runs per map when the
  artifact pruner is enabled. Defaults to `8`.
- `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0`: disable post-run artifact pruning for
  deep investigations.
