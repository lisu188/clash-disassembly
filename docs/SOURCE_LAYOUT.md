# Source layout

This document defines the source-organization rules for the recovered Win95 implementation.

## Invariants

- `clash95.c` remains the sole recovered translation-unit manifest.
- Files under `src/recovered/` are include fragments and are not compiled independently.
- Include order follows original binary address order, even when semantic directories differ.
- Recovered behavior, SDL platform code, instrumentation, and compatibility scaffolding remain separate.
- Source-only moves must preserve preprocessed tokens and existing runtime behavior.

## Recovered fragment naming

Recovered implementation fragments use the first original function address followed by a conservative subsystem description, for example `004084A0_world_map_interaction.inc.c`.

Each fragment header records its original address range and states that the file is included by `clash95.c`.

## Boundaries

- `src/recovered/`: behavior attributable to the original executable.
- `src/platform/`: SDL, X11, POSIX, timing, input, window, rendering, and host filesystem adapters.
- `src/compatibility/`: decompiler support and quarantined runtime or Win32-shaped scaffolding.
- `src/instrumentation/`: route tracing, scripted probes, diagnostics, and state observation.
- `src/bootstrap/`: the host executable entrypoint.

Gameplay semantics must not be moved into platform or compatibility code. Instrumentation must not become an alternative gameplay implementation.

## Change policy

A mechanical organization change must not combine file moves with semantic renames, reformatting, or control-flow changes. Preserve address comments, map-confirmed names, linkage, declaration order, and `static` visibility.

Validation requires the normal build and CTest suite, save-format verification, JSON checks, `git diff --check`, and the preprocessed-token gate for recovered-source moves.
