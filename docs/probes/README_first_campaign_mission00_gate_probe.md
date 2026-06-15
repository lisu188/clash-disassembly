# First Campaign Mission 00 Gate Probe

This is a repair/proof entrypoint for the first-campaign mission 0 route. It is
kept as a focused regression gate even though the campaign route table now marks
mission `00` complete. The wrapper still requires the real objective marker
before passing.

Run from the repo root:

```sh
bash tests/run_first_campaign_mission00_gate_probe.sh bin/clash95_bootstrap
```

Or build first and then run the same gate:

```sh
bash tests/run_first_campaign_mission00_gate_build_probe.sh
```

The gate wrapper prints a summary of the latest retained mission-00 artifact when
one exists. If the arc runner exits successfully, the wrapper also requires the
retained artifact summary to prove objective completion, retained frames, and
nonblank final-frame evidence before returning success.

Required pass evidence:

- `mission_objective_complete` appears in the first-mission smoke log.
- Presented frames are captured.
- The final captured frame is not blank when ImageMagick is available.
- Durable artifacts are written under `artifacts/first-campaign/mission-00/`.

Summarize the latest retained run:

```sh
bash tests/summarize_first_campaign_mission00_gate_artifact.sh
```

Require the latest retained run to contain `mission_objective_complete`:

```sh
CLASH95_MISSION00_SUMMARY_REQUIRE_COMPLETE=1 bash tests/summarize_first_campaign_mission00_gate_artifact.sh
```

Require both objective completion and retained frame captures:

```sh
CLASH95_MISSION00_SUMMARY_REQUIRE_COMPLETE=1 CLASH95_MISSION00_SUMMARY_REQUIRE_FRAMES=1 bash tests/summarize_first_campaign_mission00_gate_artifact.sh
```

Require the full retained-artifact verdict:

```sh
CLASH95_MISSION00_SUMMARY_REQUIRE_COMPLETE=1 CLASH95_MISSION00_SUMMARY_REQUIRE_FRAMES=1 CLASH95_MISSION00_SUMMARY_REQUIRE_NONBLANK=1 bash tests/summarize_first_campaign_mission00_gate_artifact.sh
```

Require that the retained artifact also recorded route input steps:

```sh
CLASH95_MISSION00_SUMMARY_REQUIRE_ROUTE_INPUTS=1 bash tests/summarize_first_campaign_mission00_gate_artifact.sh
```

The summary prints `mission00_gate_verdict=pass` only when the latest retained
artifact has objective completion, retained frames, and nonblank final-frame
evidence.

The summary also prints `route_input_step_count` and the retained route-input
timeline. These are diagnostics only: they sequence direct xdotool actions and
queued world/platform/battle script inputs so a timeout can be matched to the
last authentic input sent. Each route input step also records the latest
objective, selected-stack, and battle marker already present in the log before
that input is queued, then records the same context again after the input's
settle delay.

The wrapper sets:

- `CLASH95_FIRST_CAMPAIGN_ARC_ALLOW_PARTIAL=1`
- `CLASH95_FIRST_CAMPAIGN_ARC_REQUIRE_OBJECTIVE=1`
- `CLASH95_FIRST_MISSION_DURABLE_ARTIFACTS=1`
- `CLASH95_FIRST_MISSION_MOVE_REQUIRE_FRAMES=1`
- `CLASH95_FIRST_MISSION_MOVE_REJECT_BLANK_FRAMES=1`

Artifact size controls:

- `CLASH95_FIRST_MISSION_MAX_COPIED_FRAMES` caps retained presented-frame BMPs
  per mission-00 smoke run; defaults to `160`. The runner keeps a small head
  sample and the latest tail frames.
- `CLASH95_FIRST_MISSION_MAX_LOG_BYTES` caps the retained smoke log; defaults
  to `12000000`. Larger logs are saved as head/tail diagnostics with truncation
  metadata in `summary.txt`.
- `CLASH95_FIRST_MISSION_KEEP_RUNS` prunes old durable run directories under
  `artifacts/first-campaign/mission-00`; defaults to `12`.
- Repo-wide cleanup is available through
  `bash tests/prune_artifacts.sh --dry-run` and explicit
  `bash tests/prune_artifacts.sh --apply`. Mission-00 durable artifact runs now
  default `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=1` and
  `CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368` (768 MiB), so the pruner runs
  after the per-mission retention pass. Set
  `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` to opt out for deep investigations.

This wrapper is not final first-campaign acceptance. Final acceptance still runs
`tests/run_first_campaign_arc_probe.sh bin/clash95_bootstrap` from the authentic
Campaign menu and requires missions `00..09` to complete in order.
