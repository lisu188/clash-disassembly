# clash-disassembly

Evidence-driven GNU++20 reimplementation of the original Win95 Clash, with an
SDL-backed host layer. The target is a complete, maintainable game whose behavior
is validated against the original executable.

The recovered implementation builds, reaches authentic menus and runs validated
gameplay routes. The full reimplementation remains in progress. Both campaigns
from the real menu, automatic advancement, remaining runtime behavior, and
whole-game visual/behavioral parity still require evidence.

## Start here

| Task | Read |
| --- | --- |
| Understand the Clash repositories and their responsibilities | [Clash project overview](docs/CLASH_PROJECTS.md) |
| Find documentation by topic | [Documentation guide](docs/README.md) |
| Resume recovery work | [Current status and next target](docs/STATUS.md), then [project tracks](docs/PROJECT_TRACKS.md) |
| Build or choose validation gates | [Build and test](docs/BUILD_AND_TEST.md) |
| Understand source ownership | [Source layout](docs/SOURCE_LAYOUT.md), [subsystem map](src/README.md) |
| Contribute or run an agent | [Operating instructions and definition of done](AGENTS.md) |

## Implementation and evidence

Production C++ lives in the manifest-backed subsystem sources under `src/`;
SDL host adaptation, compatibility support, instrumentation and bootstrap code
have separate ownership. [The manifest](data/recovered_sources.json) tracks all
4,157 historical function identities and their current canonical implementation.
Class/type/ownership migration continues after the completed GNU++20 cutover.

`clash95.asm`, `clash95.map`, original binaries and retained captures establish
provenance and behavioral evidence. The original executable is a comparison
oracle, not a dependency of the final reimplementation. Retail game data is
required for local runtime work; public build and metadata gates are asset-free.

The direct campaign route baseline is 6/20 complete missions (`00..04` and `13`).
Mission `05` remains the first blocker. Read [current status](docs/STATUS.md)
before using old route or class-migration reports: buildability, direct-route
completion and full campaign acceptance are separate milestones.

## Quick start

Run from the repository root in Linux/WSL with CMake 3.28+, GCC 13, Ninja,
pkg-config, SDL2/X11 development libraries and Python 3. Package setup, Clang 18,
warning/link ratchets and runtime requirements live in the
[build guide](docs/BUILD_AND_TEST.md).

```sh
CXX=g++-13 cmake -S . -B build/gcc-13 -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/gcc-13 --target clash95_recovered clash95_bootstrap \
  runtime_mission_trace_tests clash95_split_audit -j2
ctest --test-dir build/gcc-13 \
  -R '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
  --output-on-failure --no-tests=error
```

These four tests require no retail installation. Use
[documentation-only checks](docs/BUILD_AND_TEST.md#documentation-only-changes)
for navigation and prose changes. Run game probes headlessly in Linux/WSL as
required by [AGENTS.md](AGENTS.md#10a-mandatory-frame-comparison-against-the-original).

Strategic-AI image decoding, recovered CLIPS source and their validation limits
are indexed in the [documentation guide](docs/README.md#strategic-ai-and-clashdat).
Generated artifacts and private captures remain outside Git unless deliberately
promoted with provenance under the [artifact policy](docs/ARTIFACTS.md).
