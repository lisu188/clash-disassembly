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

The route and mission artifact writers keep a small retained set by default and
honor `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` for deep investigations.

## Promotion Rule

Promote an artifact into git only when it is small, durable evidence and the doc
or progress log explains why it matters. Never commit raw frame floods, crash
dumps, local scratch, generated binaries, or transient build products.
