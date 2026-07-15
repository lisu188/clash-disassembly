# Source layout

This document defines the source-organization rules for the recovered Win95 implementation.

## Invariants

- `data/recovered_sources.json` is the exhaustive recovered-function manifest.
- The 138 C files under `src/` are canonical, independently
  compiled GNU C17 translation units.
- Function order within each family follows original binary address order, even
  when semantic subsystem boundaries differ.
- Recovered behavior, SDL platform code, instrumentation, and compatibility scaffolding remain separate.
- Source-only moves must preserve preprocessed tokens and existing runtime behavior.

## Recovered source naming

Function-family files encode the first and last original address, subsystem,
and family sequence, for example
`src/world/00408030_0040A0A0_world_001.c`.

Address comments and historical provenance remain in each file. The removed
unified/fragments/symlink paths are preserved in `docs/SOURCE_PATH_MAP.csv`.

## Boundaries

- `src/`: behavior attributable to the original executable,
  private recovered headers, and the CMake source list.
- `src/platform/`: SDL, X11, POSIX, timing, input, window, rendering, and host filesystem adapters.
- `src/compatibility/`: decompiler support and quarantined runtime or Win32-shaped scaffolding.
- `src/instrumentation/`: route tracing, scripted probes, diagnostics, and state observation.
- `src/bootstrap/`: the host executable entrypoint.

Gameplay semantics must not be moved into platform or compatibility code. Instrumentation must not become an alternative gameplay implementation.

## Change policy

A mechanical organization change must not combine file moves with semantic renames, reformatting, or control-flow changes. Preserve address comments, map-confirmed names, linkage, declaration order, and `static` visibility. Update the manifest and old-to-new path map whenever an identity moves.

Validation requires the split-source audit, normal build and CTest suite,
save-format verification, JSON checks, `git diff --check`, and the
preprocessed-token/object snapshot gates for recovered-source changes.
