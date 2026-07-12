# First Campaign Arc Probe

This is the final acceptance entrypoint for the first campaign arc once all
routes are complete.

Build and run the full arc:

```sh
bash tests/run_first_campaign_arc_build_probe.sh
```

The build wrapper first requires every route `00..09` to be marked `complete`.
For route-runner debugging only, that preflight can be bypassed:

```sh
CLASH95_FIRST_CAMPAIGN_ARC_SKIP_ROUTE_PREFLIGHT=1 bash tests/run_first_campaign_arc_build_probe.sh
```

Run an already-built binary:

```sh
bash tests/run_first_campaign_arc_probe.sh bin/clash95_bootstrap
```

Summarize route readiness without launching the game:

```sh
bash tests/summarize_first_campaign_arc_routes.sh
```

The full arc runner also prints this route-readiness table automatically when
it refuses a missing, partial, incomplete, unknown, or runnerless route.

Require every first-campaign route to be marked complete:

```sh
CLASH95_FIRST_CAMPAIGN_ROUTE_SUMMARY_REQUIRE_COMPLETE=1 bash tests/summarize_first_campaign_arc_routes.sh
```

Acceptance requirements:

- Starts from the authentic Campaign menu path.
- Completes missions `00..09` in order.
- Does not set `CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_PARTIAL=1`.
- Does not set `CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_INCOMPLETE=1`.
- Requires natural objective completion markers from the recovered game flow.
- Retains nonblank frame evidence through the mission artifact hooks.

Current repair state:

- Missions `00..04` are currently marked `complete` by their route env files.
- Mission `04` now clears Hopenberg over three authentic assaults, captures
  the empty-garrison castle, and logs natural objective completion. Full-menu
  sequential auto-advance remains a separate first-arc acceptance gate.
- Missions `05..09` are partial direct-load evidence probes until authentic
  completion routes are repaired.
- Use `tests/run_first_campaign_mission00_gate_build_probe.sh` only for the
  mission-0 regression/repair gate; it is not full-campaign acceptance.
