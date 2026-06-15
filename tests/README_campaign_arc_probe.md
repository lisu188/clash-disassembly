# Full Campaign Arc Probe

This is the final acceptance entrypoint for both recovered campaign paths once
all routes are complete.

Build and run both campaigns:

```sh
bash tests/run_campaign_arc_build_probe.sh
```

The build wrapper first requires every route `00..19` to be marked `complete`.
For route-runner debugging only, that preflight can be bypassed:

```sh
CLASH95_CAMPAIGN_ARC_SKIP_ROUTE_PREFLIGHT=1 bash tests/run_campaign_arc_build_probe.sh
```

Run an already-built binary:

```sh
bash tests/run_campaign_arc_probe.sh bin/clash95_bootstrap
```

Run only the second campaign route set:

```sh
bash tests/run_campaign_arc_probe.sh bin/clash95_bootstrap 10 11 12 13 14 15 16 17 18 19
```

Summarize route readiness without launching the game:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

Run an opt-in route regression for one recovered direct mission route:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest -R clash95_campaign_route_04_regression --output-on-failure
```

The route-regression CTest entries are skipped by default because they launch
Xvfb, open the SDL window, and drive authentic input. They currently cover the
verified direct-route milestones for missions `01..04`.

Acceptance requirements:

- Starts from the authentic Campaign menu path for final proof.
- Completes missions `00..19` in order.
- Does not set `CLASH95_CAMPAIGN_ARC_ALLOW_PARTIAL=1`.
- Does not set `CLASH95_CAMPAIGN_ARC_ALLOW_INCOMPLETE=1`.
- Requires natural objective completion markers from recovered game flow.
- Retains nonblank frame evidence through mission artifact hooks.
- Uses loose visual frame checks for route artifacts: mean luminance, nonblack
  pixel count, color diversity, and optional frame progression. The checks are
  intentionally not byte-exact while route timing is still being stabilized.
- Uses direct campaign mission boot only for isolated route repair.

Visual assertion controls:

- `CLASH95_CAMPAIGN_ROUTE_BLANK_MEAN_THRESHOLD` sets the minimum final-frame
  mean luminance; defaults to `1`.
- `CLASH95_CAMPAIGN_ROUTE_MIN_NONBLACK_PIXELS` sets the minimum nonblack pixel
  count for `nonblank` route assertions; defaults to `1000`.
- `CLASH95_CAMPAIGN_ROUTE_MIN_UNIQUE_COLORS` sets the minimum color diversity
  for `nonblank` route assertions; defaults to `16`.
- `CLASH95_CAMPAIGN_ROUTE_REQUIRE_FRAME_PROGRESSION=1` enables loose
  frame-to-frame progression checks, controlled by
  `CLASH95_CAMPAIGN_ROUTE_MIN_FRAME_DIFF` and
  `CLASH95_CAMPAIGN_ROUTE_MIN_CHANGED_FRAME_PAIRS`.
- Failed visual route checks retain `visual-failure-montage.ppm` in the smoke
  artifact directory when any frames were captured.

Artifact size controls:

- `CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES` caps retained presented-frame
  BMPs per run; defaults to `160`. The runner keeps a small head sample and the
  latest tail frames. Set to `0` to skip presented-frame copies while still
  keeping checkpoint screenshots.
- `CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES` caps the retained full log; defaults
  to `12000000`. Larger logs are saved as head/tail diagnostics with truncation
  metadata in `summary.txt`. Set to `0` to retain full logs.
- `CLASH95_CAMPAIGN_ROUTE_KEEP_RUNS_PER_MISSION` prunes old durable run
  directories under `artifacts/campaign-routes/mission-NN`; defaults to `12`.
  Set to `0` to disable pruning for deep investigations.
- Repo-wide artifact cleanup is available as a dry-run first:
  `bash tests/prune_artifacts.sh --dry-run`. Apply it explicitly with
  `bash tests/prune_artifacts.sh --apply`. The pruner only removes recognized
  durable run directories under repo-owned `artifacts/` roots.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES` can add a whole-`artifacts/` size cap to
  the pruner. `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=1` opts campaign/mission-00
  probes into a repo-wide prune sweep after their normal per-mission retention.

Current repair state:

- Mission `00` remains `partial` until the mission-00 gate logs
  `mission_objective_complete`.
- Missions `01..19` remain blocked on route recovery after prior mission
  completion is proven.
