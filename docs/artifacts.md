# Artifact Retention

Generated artifacts are intentionally not tracked by default:

- build trees and local binaries
- route logs and frame dumps
- screenshots and visual failure montages
- crash dumps, profiler output, debugger scratch, and local agent scratch

The repo keeps durable evidence in source form instead: assembly, original
binary/map corroboration, route scripts, JSON metadata, historical logs, and
documented milestone notes.

## Pruning

Dry-run before manual cleanup:

```sh
bash tests/prune_artifacts.sh --dry-run
```

Apply recognized repo-owned artifact cleanup:

```sh
bash tests/prune_artifacts.sh --apply
```

Add a repo-wide cap:

```sh
CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 bash tests/prune_artifacts.sh --dry-run
```

The 768 MiB cap is a ceiling, not a compactor. If `artifacts/` is under the cap
or the only remaining runs are protected by `--min-keep`, a dry-run can
correctly report no prune candidates.

Use smaller retained sets when repeated route work is more important than
keeping many nearby failed runs:

```sh
bash tests/prune_artifacts.sh --dry-run --keep 4
bash tests/prune_artifacts.sh --dry-run --keep 2
bash tests/prune_artifacts.sh --dry-run --keep 1 --max-bytes 600000000
```

The route and mission artifact writers keep a small retained set by default and
honor `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` for deep investigations.
Multiplayer map probes use the same policy under
`artifacts/multiplayer-maps/map-NN`: capped logs, sampled frames, per-map
retention, and repo-wide pruning through `tests/prune_artifacts.sh`.

Campaign route probes also cap retained evidence per run. The default
regression wrapper keeps sampled head/tail frame dumps, sampled checkpoint
frames, and a head/tail log excerpt while recording both original and retained
log sizes in `summary.txt`. Increase these only for focused debugging:

```sh
CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=96 \
CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=96 \
CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=50000000 \
bash tests/run_campaign_route_regression.sh build/bin/clash95_bootstrap 04
```

Use lower values when running long arcs repeatedly:

```sh
CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_FRAMES=8 \
CLASH95_CAMPAIGN_ROUTE_MAX_COPIED_CHECKPOINTS=12 \
CLASH95_CAMPAIGN_ROUTE_MAX_LOG_BYTES=2000000 \
bash tests/run_campaign_route_regression.sh build/bin/clash95_bootstrap 04
```

Dry-run pruning reports unrecognized top-level children under `artifacts/` so
manual screenshot folders or ad hoc captures are visible without being removed
by the automated pruner.

## Promotion Rule

Promote an artifact into git only when it is small, durable evidence and the doc
or progress log explains why it matters. Never commit raw frame floods, crash
dumps, local scratch, generated binaries, or transient build products.
