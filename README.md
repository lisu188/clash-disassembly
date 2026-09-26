# clash-disassembly

**Evidence-driven full C++ reimplementation of the original Win95 Clash.**

The repository is not intended to stop at readable decompilation. Its target is a
complete, maintainable GNU++20 implementation of the shipped game whose behavior
is validated against the original executable.

- `clash95.asm` and `clash95.map` are protected behavioral/provenance sources.
- The canonical production implementation lives in the manifest-backed C++ sources
  under `src/` and runs through the SDL-backed host layer.
- The original executable is a validation oracle, not a runtime dependency of the
  final reimplementation.
- `data/recovered_sources.json` maps all 4,157 historical function identities to
  their current recovered source ownership.
- `CLASH.DAT` is identified and structurally decoded as a CLIPS 6.00 BSAVE
  strategic-AI image. The tooling recovers atom/expression tables, 95 rule
  records, 295 RETE joins, 64 fact-pattern nodes, 20 object alpha records,
  14 object-pattern nodes, game `defclass`/slot metadata, source-order LHS
  conditions, deffunction bodies, defglobals, and RHS source projections. A
  unified `CLASH_recovered.clp` scaffold can be generated reproducibly from the
  retail image.

## Project goal

The finished project should behave as the original Clash game while being
implemented and maintainable as C++ rather than as preserved decompiler output.

That means progressively replacing decompiler-shaped control flow, anonymous
state, raw offsets, compatibility approximations, and platform leakage with
evidence-backed C++ functions, methods, types, ownership boundaries, and APIs.
Behavioral fidelity remains mandatory throughout that migration.

Completion requires, at minimum:

- all original function identities accounted for by implemented C++, an
  explicitly documented fold/merge, or proof that the code is dead for the
  shipped game;
- no reachable gameplay/runtime behavior implemented by inert compatibility
  stubs or by the original executable;
- complete startup, menus, strategic world, battles, AI, save/load, rendering,
  input, audio/video, configuration, and other original user-visible flows;
- both campaigns completed from the real Campaign menu with natural mission
  objectives and automatic advancement;
- original-vs-C++ behavioral and visual evidence for relevant milestones;
- supported builds, public asset-free tests, local asset-backed smoke tests, and
  regression routes green.

See [AGENTS.md](AGENTS.md) for the full C++ reimplementation contract and
definition of done.

## Current state

The recovered implementation already builds as independently compiled GNU++20
subsystem sources, boots through the SDL-backed runtime, reaches responsive
menus, and executes validated gameplay routes. The broad `sub_XXXXXX` rename
campaign and known `JUMPOUT` recovery are complete; current work is focused on
behavioral recovery, class/type/ownership migration, compatibility removal, and
whole-game parity.

The repository tracks runtime/C++ reconstruction and campaign validation
separately. Campaign routes are important acceptance tests for the
reimplementation, but route completion alone does not mean the C++ port is
complete.

Current validated campaign-route state: missions `00..04` and `13` are
complete through their route gates (6/20). Mission `04` clears Hopenberg
through three authentic tactical assaults, transfers the empty-garrison castle,
and reaches `mission_objective_complete`; mission `13` completes its survival
objective through authentic turn advancement. The remaining missions are
direct-load evidence probes. See [docs/STATUS.md](docs/STATUS.md) for the active
blocker and latest milestone.

## Quick Start

Run these commands in Linux or WSL with CMake 3.28+, GCC 13 with g++-13, Ninja,
pkg-config, SDL2 and X11 development libraries, and Python 3 installed. See
[build prerequisites and both compiler gates](docs/BUILD_AND_TEST.md).

```sh
CXX=g++-13 cmake -S . -B build/gcc-13 -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/gcc-13 --target clash95_recovered clash95_bootstrap \
  runtime_mission_trace_tests clash95_split_audit -j2
ctest --test-dir build/gcc-13 \
  -R '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
  --output-on-failure
```

These four gates require no retail assets. The full local smoke suite and
campaign routes require the installed game at `/mnt/c/clash`; run them
headlessly as described in
[docs/BUILD_AND_TEST.md](docs/BUILD_AND_TEST.md).

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

## C++ architecture direction

The source tree deliberately separates recovered game semantics from host
adaptation:

- the 12 recovered subsystem directories directly under `src/` own original
  game behavior;
- `src/platform/` owns SDL/X11 host adaptation;
- `src/compatibility/` is temporary/quarantined compatibility support and must
  not become a permanent home for reachable gameplay behavior;
- `src/instrumentation/` owns observation-only tracing;
- `src/bootstrap/` owns the host executable entrypoint.

The intended migration direction is from evidence-backed recovered code toward
coherent C++ classes, state owners, typed records, enums, constants, and APIs.
Exact packed/on-disk/original-memory layouts stay explicit where save/data/ABI
compatibility or validation requires them.

A structural cleanup is accepted only when behavior remains proved. Conversely,
textual resemblance to the decompiler is not a goal once semantics are
understood.

## Working with Astra

The tracked `.codex/config.toml` selects `gpt-6-astra`. Codex loads project
configuration for a trusted repository; see the
[official configuration guidance](https://learn.chatgpt.com/docs/config-file/config-basic).
Reasoning effort is inherited from the user's configuration, including an
existing `ultra` preference. The project does not override authentication or
permissions.

Start with [AGENTS.md](AGENTS.md), inspect the working tree, then read the active
frontier and next target in
[docs/PROJECT_TRACKS.md](docs/PROJECT_TRACKS.md) and
[docs/STATUS.md](docs/STATUS.md). Run builds and headless probes in WSL. The
legacy `.agent/state.json` preserves historical startup evidence and is not the
current resume authority.

Agents should prefer work that removes measurable distance to the full C++
definition of done: authentic behavior recovery, regression evidence,
class/type/ownership migration, removal of compatibility debt, and closure of
whole-game feature gaps.

## Source organization

The recovered implementation is compiled as 12 subsystem object libraries from
the manifest-backed C++ files in subsystem directories directly under `src/`.
SDL, compatibility, instrumentation, and bootstrap code remain in their own
`src/` areas. The former unified source, recovered include-C fragments, and
compatibility symlinks were removed at the split-only cutover;
[docs/SOURCE_PATH_MAP.csv](docs/SOURCE_PATH_MAP.csv) preserves their old-to-new
identities.

See [src/README.md](src/README.md) for the subsystem map and
[docs/SOURCE_LAYOUT.md](docs/SOURCE_LAYOUT.md) for source-boundary and validation
rules.

## Documentation

- [AGENTS.md](AGENTS.md) - full C++ reimplementation mission, definition of done,
  evidence rules, migration rules, and agent workflow.
- [docs/PROJECT_TRACKS.md](docs/PROJECT_TRACKS.md) - current frontiers, validated
  baselines, completion language, and immediate priorities.
- [docs/STATUS.md](docs/STATUS.md) - current validated Win95 runtime state, active
  blocker, and next target.
- [docs/BUILD_AND_TEST.md](docs/BUILD_AND_TEST.md) - build, CTest, route, and
  validation commands.
- [docs/SOURCE_LAYOUT.md](docs/SOURCE_LAYOUT.md) - canonical source areas,
  compatibility aliases, and behavior-preserving move policy.
- [docs/RUNTIME_MILESTONES.md](docs/RUNTIME_MILESTONES.md) - route/milestone
  table with commands, evidence, and remaining gaps.
- [docs/ROADMAP.md](docs/ROADMAP.md) - near-term and long-term recovery goals.
- [docs/REVERSE_ENGINEERING.md](docs/REVERSE_ENGINEERING.md) - source-of-truth,
  naming, and patch policy.
- [docs/STRUCTURES.md](docs/STRUCTURES.md) - structure/data recovery policy and
  metadata links.
- [docs/AI_SCRIPTING_API.md](docs/AI_SCRIPTING_API.md) - the strategic-AI CLIPS
  host-function API used by `strateg\\clash.dat`.
- [docs/CLASH_DAT_BSAVE.md](docs/CLASH_DAT_BSAVE.md) - decoded CLIPS 6.00 BSAVE
  layout, strategic-AI rule-image findings, `PRIOR` weights, and base
  decompilation limits.
- [docs/CLASH_DAT_PRIMITIVES.md](docs/CLASH_DAT_PRIMITIVES.md) - decoded compiled
  fact/object primitive accessors and predicates.
- [docs/CLASH_DAT_LHS.md](docs/CLASH_DAT_LHS.md) - decoded game classes/slots,
  class and slot bitmaps, RETE topology, and source-like recovery of all rule LHS
  paths.
- [docs/CLASH_DAT_RECOVERED_CLP.md](docs/CLASH_DAT_RECOVERED_CLP.md) - unified
  recovered CLP generator, synthetic binding policy, recompilation boundary, and
  validation contract.
- [docs/ARTIFACTS.md](docs/ARTIFACTS.md) - artifact retention and pruning policy.
- [docs/archive/](docs/archive/) - preserved historical logs, reports, and old
  navigation notes.
- [docs/probes/](docs/probes/) - focused probe and route-runner notes.

Generated build trees, frame dumps, route artifacts, screenshots, crash dumps,
and local scratch are ignored by default. Promote durable evidence only when it
has reverse-engineering or parity value and is documented.
