# Artifact Policy

Generated artifacts are useful during route recovery, but they must not make the
repository heavy or hide real evidence.

## Do Not Commit

- Build trees and CMake output.
- Frame dumps, screenshots, montages, and raw captures.
- Crash dumps, profiling output, temporary logs, and local scratch files.
- Generated route/soak artifact directories under `artifacts/` unless a small
  item is intentionally curated and documented.

## Durable Evidence

Tracked evidence includes original disassembly/binary/map files, recovered
source, route scripts, metadata JSON, focused documentation, and historical
progress logs. If a file is the only explanation for a recovered behavior or
blocked path, keep it and document why.

## Pruning

Manual dry run:

```sh
CLASH95_ARTIFACT_PRUNE_MAX_BYTES=805306368 \
  bash tests/prune_artifacts.sh --dry-run
```

The route and soak harnesses also support automatic pruning after high-volume
runs. Use `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` when preserving a deep diagnostic
run for investigation.

## Retention Defaults

- Keep at least the newest run for each recognized artifact group.
- Prefer capped logs and sampled frame metrics over full raw frame sets.
- Preserve `latest.txt`, `summary.txt`, route env/script copies, and key frame
  checkpoints when they are needed to diagnose a timeout.
- Do not remove evidence by hand when the documented pruner can classify it.
