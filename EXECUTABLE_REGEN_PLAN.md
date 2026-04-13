# Executable regeneration plan

This is the minimal honest plan for the next `clash95_cpp_regen` step.

## Current position

- The recovered C baseline is green as `clash95_recovered`.
- `clash95_bootstrap` already demonstrates a narrow executable wedge rooted in recovered startup behavior.
- `clash95_cpp_core` already builds as the first conservative C++ seam library.
- `clash95_cpp_regen` already links by reusing `bootstrap_main.c`, the bootstrap object library, and the new C++ core.
- A direct raw link still fails on missing `main` and a large unresolved startup/runtime surface.

## Immediate frontier update - 2026-04-13

- Keep the current contained executable wedge pointed at the authentic load-menu path.
- Treat the row-resource, row-draw, world-map-init, and save-path formatting/helper bands as repaired enough to focus on the missing class/bload prelude rather than local UI or I/O scars.
- Take the next batch through:
  1. preserving the green pre-confirm contained load-menu wedge
  2. keeping the broader-rules-contained probe reproducible with the real post-confirm command shape so it still distinguishes the last directly traced `class-lookup-no-table name=oddzial` failure from the earlier `symbol-lookup-missing-table MAIN` failure
  3. keeping the now-green retained startup-prelude probes (`sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`) honest while continuing the broader front-end handoff into the remaining mission-loader cases
  4. keeping the recovered retained mission-loader slice honest: thread the selector into `Scenario_LoadMissionByIndex`, use real sentinel-terminated `createUnit` / `createCastle` setup lists, and recover the menu-reachable cases directly from asm/map evidence rather than pushing mission setup into SDL, compat, or `src_cpp`
  5. treat the retained mission-loader widening as complete now that the 20-case `Scenario_LoadMissionByIndex` switch is covered in recovered C and the existing `case 19` / `p_map10z.map` lane is corroborated against asm
  6. widen next into the deeper human-turn gameplay/session surface after `sub_444490`, without collapsing mission-local logic into shared helpers; the next concrete retained symbol remains `WorldMap_RunHumanTurnLoop`, now past the repaired `sub_460370` / `PlayGame` handoff and past the loop's zero-init plus `arama1` / `kon_por1` mission-success tail
  7. keep the deferred save-slot repaint/name lane that still prints `load-menu-skip-save-slot-draw` separate from the retained mission-loader work
- Do not broaden into unrelated runtime wrappers past the already-settled `unknown_libname_2` / `MoveFileA` / `sscanf_` / `fgets_` band until those two adjacent startup fronts are characterized.
- Do not treat `Rules_ShowBanner_StrategicClash` or bare `sub_499990` as a local post-save patch. Keep the startup-prelude widening separate from the contained load-game wedge.
- Do not regress the corrected `sub_47D0E0` call attribution: `unknown_libname_7` is the runtime setter at `0x47E7B0`, while the startup-prelude tail still needs the separate retained `.fn_init` body at `0x49A0E0`.
- Keep the CRT/runtime glue quarantined: `sub_496643`, `ftime_`, and `system_` are now compat-seam repairs, and the x87 math band is already recovered in `clash95.c`, so the next widening step should stay in the retained front-end/gameplay surface rather than backsliding into generic host wrappers.
- The retained `PlayGame_Dispatch` alias/data band is now reduced again:
  - front-end cursor/overlay descriptors, the first world-map/UI export aliases, the unit-slot and placement helpers, the garrison/UI aliases, the battle/port/queen debug string slab, and the port reinforcement tables are no longer live retained blockers
  - `UI_CheckDialogAccepted`, `UI_CheckConfirmQuit`, the reached `unit_stats` byte lane, the queen departure-event slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are now also reduced in recovered C
  - the surviving mission-loader frontier was then narrowed again: `Scenario_LoadMissionByIndexAndPlay` now threads the selector, `createUnit` / `createCastle` now accept the original sentinel-terminated unit lists, and the menu-reachable `sub_460360` cases through case `19` are now corroborated in place
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit, the `PlayGame` prologue now restores the real `backgr*.s32` / `treemas*.s32` loads plus initialized player-scan counters, and `WorldMap_RunHumanTurnLoop` now restores its asm-backed zero-init plus `arama1` / `kon_por1` mission-success tail
  - the next retained widening should stay on the gameplay/session surface after `Scenario_LoadMissionByIndexAndPlay`, still centered on `WorldMap_RunHumanTurnLoop` rather than on a new SDL seam or `src_cpp` abstraction

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

## Immediate retained next step
1. Keep the contained `oddzial` versus `MAIN` split green and separate from the retained gameplay/session widening.
2. Keep the retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, `PlayGame`, and `WorldMap_RunHumanTurnLoop` green.
3. Continue reducing the deeper `WorldMap_RunHumanTurnLoop` loop body after the repaired zero-init entry, `arama1` / `kon_por1` tail, zero-arg loop-entry helper lane, held-key `DD_Pump` loops, queued-path AP compare, saved render-hook/resource-handle debug block, the repaired `WorldMap_HandleTopMenuBar` helper band, and the repaired `UnitStackSelection_HandleInput` helper band; next focus is `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`.
4. Only after that should the adjacent AI branch `sub_451F70` take priority.
