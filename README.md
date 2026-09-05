# clash-disassembly

Evidence-driven recovery of the original Win95 Clash binary.

- `clash95.asm` is the protected Win95 behavioral source of truth.
- The 12 manifest-backed subsystem directories directly under `src/` are the
  canonical recovered GNU C17 implementation
  under SDL build, runtime, and campaign-route validation.
- `data/recovered_sources.json` maps all 4,157 recovered functions to 140
  independently compiled translation units.
- `CLASH.DAT` is identified and structurally decoded as a CLIPS 6.00 BSAVE
  strategic-AI image. The tooling now recovers atom/expression tables, 95 rule
  records, 295 RETE joins, 64 fact-pattern nodes, 20 object alpha records,
  14 object-pattern nodes, game `defclass`/slot metadata, source-order LHS
  conditions, deffunction bodies, defglobals, and RHS source projections. A
  unified `CLASH_recovered.clp` scaffold can now be generated reproducibly from
  the retail image.

The repository tracks Win95 runtime reconstruction and campaign validation separately. See `docs/PROJECT_TRACKS.md` before interpreting or reporting completion percentages.

Current validated campaign-route state: missions `00..04` and `13` are complete through their route gates (6/20). Mission `04` clears Hopenberg through three authentic tactical assaults, transfers the empty-garrison castle, and reaches `mission_objective_complete`; mission `13` completes its survival objective through authentic turn advancement; the remaining missions are direct-load evidence probes. See `docs/STATUS.md` for the active blocker and latest milestone.

## Quick Start

Run these commands in Linux or WSL with CMake 3.28+, GCC 13, Ninja, pkg-config,
SDL2 and X11 development libraries, and Python 3 installed. See
[build prerequisites and both compiler gates](docs/BUILD_AND_TEST.md).

```sh
CC=gcc-13 cmake -S . -B build/gcc-13 -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/gcc-13 --target clash95_recovered clash95_bootstrap \
  runtime_mission_trace_tests clash95_split_audit -j2
ctest --test-dir build/gcc-13 \
  -R '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
  --output-on-failure
```

These four gates require no retail assets. The full local smoke suite and
campaign routes require the installed game at `/mnt/c/clash`; run them headlessly
as described in [docs/BUILD_AND_TEST.md](docs/BUILD_AND_TEST.md).

Metadata and documentation checks:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
python3 tools/check_clash_dat_bsave.py
python3 tools/check_clash_dat_primitives.py
python3 tools/check_clash_dat_classes.py
python3 tools/check_clash_dat_rete.py
python3 tools/check_clash_dat_lhs.py
python3 tools/check_clash_recovered_clp.py
python3 tools/audit_split_sources.py
python3 tests/check_markdown_links.py
git diff --check
```

Strategic-AI decompilation examples:

```sh
python3 tools/decompile_clash_dat.py CLASH.DAT \
  --clp /tmp/CLASH_decompiled.clp \
  --json /tmp/CLASH_decompiled_ir.json

python3 tools/analyze_clash_dat_rete.py CLASH.DAT \
  --json /tmp/clash-rete.json \
  --dot /tmp/clash-rete.dot

python3 tools/analyze_clash_dat_lhs.py CLASH.DAT \
  --json /tmp/clash-lhs.json \
  --clp /tmp/clash-lhs.clp

python3 tools/generate_clash_recovered_clp.py CLASH.DAT \
  --clp /tmp/CLASH_recovered.clp \
  --manifest /tmp/CLASH_recovered_manifest.json
```

## Working with Astra

The tracked `.codex/config.toml` selects `gpt-6-astra`. Codex loads project
configuration for a trusted repository; see the
[official configuration guidance](https://learn.chatgpt.com/docs/config-file/config-basic).
Reasoning effort is inherited from the user's configuration, including an
existing `ultra` preference. The project does not override authentication or
permissions.

Start with [AGENTS.md](AGENTS.md), inspect the working tree, then read the active
track and next target in [docs/PROJECT_TRACKS.md](docs/PROJECT_TRACKS.md) and
[docs/STATUS.md](docs/STATUS.md). Run builds and headless probes in WSL.
The legacy `.agent/state.json` preserves historical startup evidence and is not
the current resume authority.

## Source organization

The recovered implementation is compiled as 12 subsystem object libraries from
the manifest-backed C files in subsystem directories directly under `src/`.
SDL, compatibility, instrumentation,
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
- [docs/CLASH_DAT_BSAVE.md](docs/CLASH_DAT_BSAVE.md) - decoded CLIPS 6.00 BSAVE layout, strategic-AI rule-image findings, `PRIOR` weights, and base decompilation limits.
- [docs/CLASH_DAT_PRIMITIVES.md](docs/CLASH_DAT_PRIMITIVES.md) - decoded compiled fact/object primitive accessors and predicates.
- [docs/CLASH_DAT_LHS.md](docs/CLASH_DAT_LHS.md) - decoded game classes/slots, class and slot bitmaps, RETE topology, and source-like recovery of all rule LHS paths.
- [docs/CLASH_DAT_RECOVERED_CLP.md](docs/CLASH_DAT_RECOVERED_CLP.md) - unified recovered CLP generator, synthetic binding policy, recompilation boundary, and validation contract.
- [docs/ARTIFACTS.md](docs/ARTIFACTS.md) - artifact retention and pruning policy.
- [docs/archive/](docs/archive/) - preserved historical logs, reports, and old navigation notes.
- [docs/probes/](docs/probes/) - focused probe and route-runner notes.

Generated build trees, frame dumps, route artifacts, screenshots, crash dumps, and local scratch are ignored by default. Promote durable evidence only when it has reverse-engineering value and is documented.
