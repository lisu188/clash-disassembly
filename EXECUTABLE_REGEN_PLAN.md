# Executable regeneration plan

This is the minimal honest plan for the next `clash95_cpp_regen` step.

## Current position

- The recovered C baseline is green as `clash95_recovered`.
- `clash95_bootstrap` already demonstrates a narrow executable wedge rooted in recovered startup behavior.
- `clash95_cpp_core` already builds as the first conservative C++ seam library.
- `clash95_cpp_regen` already links by reusing `bootstrap_main.c`, the bootstrap object library, and the new C++ core.
- A direct raw link still fails on missing `main` and a large unresolved startup/runtime surface.

## Immediate frontier update - 2026-04-09

- Keep the current contained executable wedge pointed at the authentic load-menu path.
- Treat the row-resource, row-draw, world-map-init, and save-path formatting/helper bands as repaired enough to focus on the missing class/bload prelude rather than local UI or I/O scars.
- Take the next batch through:
  1. preserving the green pre-confirm contained load-menu wedge
  2. keeping the broader-rules-contained probe reproducible so it still distinguishes `class-lookup-no-table name=oddzial` from the earlier `symbol-lookup-missing-table MAIN` failure
  3. continuing the broader authentic startup-prelude slice `sub_451E46 -> sub_47D0E0 -> sub_47C850("strateg\\clash.dat")` from the newly exposed retained helper band (`sub_49A0E0`, `sub_496643`, `unk_508D50`, and nearby `JUMPOUT` scars) until the missing defclass/bload startup band is narrow enough to root honestly
  4. only then widening further into the post-save `PlayGame` handoff after `sub_444490`
  5. the deferred save-slot repaint/name lane that still prints `load-menu-skip-save-slot-draw`
- Do not broaden into unrelated runtime wrappers until those two adjacent startup fronts are characterized.
- Do not treat `Rules_ShowBanner_StrategicClash` or bare `sub_499990` as a local post-save patch. Keep the startup-prelude widening separate from the contained load-game wedge.
- Do not regress the corrected `sub_47D0E0` call attribution: `unknown_libname_7` is the runtime setter at `0x47E7B0`, while the startup-prelude tail still needs the separate retained `.fn_init` body at `0x49A0E0`.

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
