# clash-disassembly

Evidence-driven C/SDL recovery of the original `clash95` game binary.
`clash95.asm` and the original binary/map artifacts remain the source of truth;
`clash95.c` is the buildable recovered implementation under test.

## Current Milestone

The recovered SDL bootstrap builds and the default CTest suite passes. Campaign
missions `00..03` have direct objective-complete route proof; mission `04`
reaches Hopenberg, enters the castle tactical battle, breaches the gate through
authentic wall attacks, and is blocked on post-breach capture/objective
completion.

See [docs/STATUS.md](docs/STATUS.md) for the current validated state and active
blocker.

## Quick Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
```

Metadata sanity checks:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
git diff --check
```

## Documentation

- [docs/STATUS.md](docs/STATUS.md) - current validated state, active blocker,
  and next target.
- [docs/BUILD_AND_TEST.md](docs/BUILD_AND_TEST.md) - build, CTest, route, soak,
  and validation commands.
- [docs/RUNTIME_MILESTONES.md](docs/RUNTIME_MILESTONES.md) - route/runtime
  milestones with commands, evidence, and gaps.
- [docs/ROADMAP.md](docs/ROADMAP.md) - near-term and long-term recovery goals.
- [docs/REVERSE_ENGINEERING.md](docs/REVERSE_ENGINEERING.md) - source-of-truth,
  naming, and patch policy.
- [docs/STRUCTURES.md](docs/STRUCTURES.md) - structure/data recovery policy and
  metadata links.
- [docs/artifacts.md](docs/artifacts.md) - artifact retention and pruning policy.
- [docs/archive/README.md](docs/archive/README.md) - historical progress logs and
  preserved notes.

## Evidence Rules

- Do not edit `clash95.asm`.
- Do not replace recovered runtime behavior with route shortcuts or demo loops.
- Do not delete route scripts, metadata, or historical notes unless they are
  clearly generated/stale duplicates.
- Keep generated build outputs, frame dumps, raw captures, crash dumps, and local
  scratch files out of commits.
