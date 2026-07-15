# clash-disassembly

Evidence-driven recovery of the original Win95 Clash binary.

- `clash95.asm` is the protected Win95 behavioral source of truth.
- `src/` is the canonical recovered GNU C17 implementation
  under SDL build, runtime, and campaign-route validation.
- `data/recovered_sources.json` maps all 4,070 recovered functions to 138
  independently compiled translation units.

The repository tracks Win95 runtime reconstruction and campaign validation separately. See `docs/PROJECT_TRACKS.md` before interpreting or reporting completion percentages.

Current validated campaign-route state: missions `00..04` are complete through their route gates. Mission `04` clears Hopenberg through three authentic tactical assaults, transfers the empty-garrison castle, and reaches `mission_objective_complete`; missions `05..19` remain direct-load evidence probes. See `docs/STATUS.md` for the active blocker and latest milestone.

## Quick Start

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
```

Metadata and documentation checks:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
python3 tools/audit_split_sources.py
python3 tests/check_markdown_links.py
git diff --check
```

## Source organization

The recovered implementation is compiled as 12 subsystem object libraries from
the C files under `src/`. SDL, compatibility, instrumentation,
and bootstrap code remain in their own `src/` areas. The former unified source,
recovered include-C fragments, and compatibility symlinks were removed at the
split-only cutover; [docs/SOURCE_PATH_MAP.csv](docs/SOURCE_PATH_MAP.csv)
preserves their old-to-new identities.

See `src/README.md` for the subsystem map and `docs/SOURCE_LAYOUT.md` for
source-boundary and validation rules.

## Documentation

- [docs/PROJECT_TRACKS.md](docs/PROJECT_TRACKS.md) - boundaries, current baselines, completion language, and immediate priorities for each recovery track.
- [docs/STATUS.md](docs/STATUS.md) - current validated Win95 runtime state, active blocker, and next target.
- [docs/BUILD_AND_TEST.md](docs/BUILD_AND_TEST.md) - build, CTest, route, and validation commands.
- [docs/SOURCE_LAYOUT.md](docs/SOURCE_LAYOUT.md) - canonical source areas, compatibility aliases, and behavior-preserving move policy.
- [docs/RUNTIME_MILESTONES.md](docs/RUNTIME_MILESTONES.md) - route/milestone table with commands, evidence, and remaining gaps.
- [docs/ROADMAP.md](docs/ROADMAP.md) - near-term and long-term recovery goals.
- [docs/REVERSE_ENGINEERING.md](docs/REVERSE_ENGINEERING.md) - source-of-truth, naming, and patch policy.
- [docs/STRUCTURES.md](docs/STRUCTURES.md) - structure/data recovery policy and metadata links.
- [docs/AI_SCRIPTING_API.md](docs/AI_SCRIPTING_API.md) - the strategic-AI CLIPS host-function API used by `strateg\\clash.dat`.
- [docs/ARTIFACTS.md](docs/ARTIFACTS.md) - artifact retention and pruning policy.
- [docs/archive/](docs/archive/) - preserved historical logs, reports, and old navigation notes.
- [docs/probes/](docs/probes/) - focused probe and route-runner notes.

Generated build trees, frame dumps, route artifacts, screenshots, crash dumps, and local scratch are ignored by default. Promote durable evidence only when it has reverse-engineering value and is documented.
