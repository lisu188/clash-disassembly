# clash-disassembly

Evidence-driven C/SDL reconstruction of the original `clash95` game binary.
`clash95.asm` is the protected behavioral source of truth; `clash95.c` is the
recovered implementation under build and route validation.

Current validated campaign-route state: missions `00..03` are complete through
their route gates, mission `04` is partial at the castle gate/capture route, and
missions `05..19` are direct-load evidence probes. See `docs/STATUS.md` for the
active blocker and latest milestone.

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
python3 tests/check_markdown_links.py
git diff --check
```

## Documentation

- `docs/STATUS.md` - current validated state, active blocker, next target.
- `docs/BUILD_AND_TEST.md` - build, CTest, route, and validation commands.
- `docs/RUNTIME_MILESTONES.md` - route/milestone table with commands, evidence,
  and remaining gaps.
- `docs/ROADMAP.md` - near-term and long-term recovery goals.
- `docs/REVERSE_ENGINEERING.md` - source-of-truth, naming, and patch policy.
- `docs/STRUCTURES.md` - structure/data recovery policy and metadata links.
- `docs/artifacts.md` - artifact retention and pruning policy.
- `docs/archive/` - preserved historical logs, reports, and old navigation
  notes.
- `docs/probes/` - focused probe and route-runner notes.

Generated build trees, frame dumps, route artifacts, screenshots, crash dumps,
and local scratch are ignored by default. Promote durable evidence only when it
has reverse-engineering value and is documented.
