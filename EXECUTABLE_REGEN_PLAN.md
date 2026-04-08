# Executable regeneration plan

This is the minimal honest plan for the next `clash95_cpp_regen` step.

## Current position

- The recovered C baseline is green as `clash95_recovered`.
- `clash95_bootstrap` already demonstrates a narrow executable wedge rooted in recovered startup behavior.
- `clash95_cpp_core` already builds as the first conservative C++ seam library.
- `clash95_cpp_regen` already links by reusing `bootstrap_main.c`, the bootstrap object library, and the new C++ core.
- A direct raw link still fails on missing `main` and a large unresolved startup/runtime surface.

## What is already stable enough to build on

- Canonical entry chain in the binary map: `start -> sub_486369 -> _WinMain@16`
- Host-side bootstrap chain in repo: `main -> App_WinMain -> Bootstrap_RunRecoveredStartupPrelude -> Bootstrap_RunRecoveredRuntimeAndRenderInit -> Bootstrap_RunRecoveredGameEntry`
- High-confidence class seams already visible in the map and decompilation:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`

## Current target shape

1. Keep `clash95_recovered` untouched and green.
2. Keep `clash95_cpp_core` as the conservative C++ library for recovered class seams and typed layouts.
3. Keep `clash95_cpp_regen` as the executable that links:
   - the recovered C baseline
   - the C++ core
   - a narrow startup harness
4. Keep `clash95_bootstrap` as the current reference for the surviving executable path until the C++ executable can replace it honestly.

## What must be classified before the executable can grow

The unresolved surface should be split into these buckets:

- `startup` and entrypoint glue
- `CRT` / WCpp runtime helpers
- `platform` Win32-to-SDL seam
- `media` and device initialization
- `compiler` / AST / object-model helpers
- `memory` and string-copy wrappers
- `control_flow` scars such as `JUMPOUT`
- `unknown` symbols that still need binary corroboration

## Immediate recovery priorities

1. Lift the first true class seams into C++ wrappers:
   - `DLXSpriteSet`
   - `CAviDecompressor`
   - `CSyncObject`
2. Keep the startup harness narrow and honest while preserving link parity between `clash95_bootstrap` and `clash95_cpp_regen`.
3. Replace only low-risk wrappers in the runtime quarantine layer.
4. Use the SDL platform seam for host behavior, not for original game semantics.
5. Revisit the raw link probe only after the startup/runtime band has been narrowed.

## Exit criteria for the next batch

The next batch is successful when it can say, with evidence:

- which unresolveds are true startup blockers
- which unresolveds belong in C++ class extraction
- which wrappers can remain quarantined
- which symbols are still unknown

At that point `clash95_cpp_regen` can grow beyond the current bootstrap-equivalent wedge without pretending the full executable path is already recovered.
