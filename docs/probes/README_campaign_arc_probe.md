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
Xvfb, open the SDL window inside that virtual X11 display, and drive authentic
input. The route runner pins child SDL launches to `SDL_VIDEODRIVER=x11`,
clears inherited `WAYLAND_DISPLAY`, and refreshes the matched SDL window id
before host-driven clicks/keys so WSLg does not surface a Windows-visible
window during normal probe runs. The entries currently cover the verified
direct-route milestones for missions `01..04`.

Route scripts support fixed log waits with `wait_log`, fresh-marker waits with
`wait_log_new`, expected final markers with `expect_log`, and alternative
authentic markers with `wait_log_any` / `wait_log_any_new` using
`pattern A || pattern B`. Use the alternative waits only when runtime evidence
shows real route variance, such as AI-turn damage changing a defender's
remaining count before the next player attack. `mark_log_count NAME PATTERN`,
`wait_log_marked [timeout] NAME [PATTERN]`, and
`wait_log_marked_any [timeout] NAME || OTHER_NAME` pin later waits to counts
captured before a route input, which avoids stale matches in long battle logs.
Use `stop` to end a quarantined partial route at a deliberately proven milestone
while preserving later experimental steps in the route file for future repair.
Use `if_env NAME [value]` / `endif` to guard a small branch-specific block, and
`stop_unless_env NAME [value] [label]` when the same route file should stop for
canonical regression but continue through an opt-in environment variable during
debug probes. Use `fail_if_log PATTERN` for branch-specific probe tails where a
known alternate recovered branch must abort before stale input is sent through
the wrong input channel. Use `if_last_wait_log_mark NAME` and
`fail_unless_last_wait_log_mark NAME` for branch-specific continuations selected
by a prior marked-any wait.

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
  the pruner. Campaign route and mission-00 durable artifact writers now default
  `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=1` and
  `CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368` (768 MiB), so high-volume route
  runs prune repo-owned durable artifacts after their normal per-mission
  retention. Set `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` to opt out for deep
  investigations.

Current repair state:

- Missions `00..04` are currently marked `complete` by their route env files.
- Mission `04` has a complete direct-boot route through three authentic
  Hopenberg assaults, empty-garrison capture, natural objective completion, and
  a fresh nonblank final checkpoint. Full Campaign-menu auto-advance remains
  an arc-level acceptance gate.
- Missions `05..19` are partial direct-load evidence probes until authentic
  completion routes are repaired.
