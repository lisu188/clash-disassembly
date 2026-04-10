# C++ Executable Regeneration Progress

This file tracks the parallel executable-regeneration path that grows out of the recovered C baseline instead of replacing it.

## Current baseline

- `clash95_recovered` remains the canonical recovered C static-library milestone.
- `clash95_bootstrap` is the current executable foothold. It reconstructs a narrow authentic startup slice through `bootstrap_main.c` and intentionally avoids the full unresolved runtime/link surface.
- The direct one-shot link of `clash95.c + platform_sdl_runtime.c + compat/decomp_runtime_stubs.c` still fails on missing `main`, `_wcpp_*` runtime families, unresolved globals, late CRT helpers, Win32-era platform calls, and control-flow scars such as `JUMPOUT`.

## Regeneration track goals

1. Keep the recovered C baseline green.
2. Make the executable-link surface explicit and categorized.
3. Add a parallel `clash95_cpp_core` library for high-confidence C++ seams.
4. Add a parallel `clash95_cpp_regen` executable that starts from the existing bootstrap foothold and gradually absorbs more authentic startup/runtime responsibility.
5. Keep the sidecar evidence artifacts synchronized with the live code.

## Latest runtime update - 2026-04-10

- `clash95_recovered`, `clash95_bootstrap`, and `clash95_cpp_regen` are still green together after the latest diagnostic and retained-link reduction pass.
- The durable memory was corrected against the live tree:
  - the pre-confirm contained load-menu corridor is still green through authentic slot-strip selection and bottom-row load confirm
  - the live post-confirm probe no longer reaches `load-menu-post-confirm-after-save`; with the current broader-rules bootstrap it dies during save replay at `parse-make-instance-before-class-lookup`
  - the retained broader startup-prelude executable-regeneration slice is no longer blocked on the local x87-heavy math/runtime band
- The last directly traced contained runtime split remains explicit:
  - with the current broader-rules bootstrap, the probe reaches `load-menu-post-confirm-load-save`, seeds `MAIN` and `make-instance`, then fails at `sub_4B0480` with `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, the same probe dies earlier with `symbol-lookup-missing-table MAIN`
  - this proves `sub_4725B0` / `sub_482260` / `sub_491B10` seed parser/symbol state but do not yet provide the authentic defclass/bload registry needed by the save replay
- The retained executable-regeneration slice also moved this batch:
  - the retained rules math builtin band under `sub_4A3790` is still recovered in place in `clash95.c`, and the direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` remain green
  - the first retained `PlayGame_Dispatch` pass is no longer blocked on the front-end descriptor slab, early world-map/UI export aliases, unit-slot and placement helpers, garrison/UI aliases, or the battle/port/queen debug string slab
  - the port reinforcement ring offsets and unit-type pool are now materialized directly from `clash95.asm`
  - the next retained widening is still `PlayGame_Dispatch`, but the former UI/data/runtime band is now reduced in recovered C: `UI_CheckDialogAccepted`, `UI_CheckConfirmQuit`, the reached `unit_stats` byte lane, the queen departure-event tables/buffer slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are no longer live retained blockers
  - the retained mission-loader lane also moved in recovered C:
    - `Scenario_LoadMissionByIndexAndPlay` now threads the real selector into `Scenario_LoadMissionByIndex`
    - `createUnit` / `createCastle` now carry the original sentinel-terminated unit lists through real varargs instead of depending on x86 stack accidents
    - the menu-reachable `sub_460360` cases `0` and `10` are now materialized from asm as the first campaign-entry map loaders (`k_mapa1l.map` and `p_mapa1z.map`) with the corroborated player-state, name, unit, and castle setup
  - the surviving retained blocker is no longer the bare `Scenario_LoadMissionByIndex` / `sub_460360` `JUMPOUT`; it is the next helper band reached from those first recovered cases: `sub_40D330` and `sub_44C2A0`
- The next executable-regeneration frontier remains split, not singular:
  - keep the contained load-menu wedge green while pursuing the missing authentic class/bload prelude, not a local save-load hack
  - separately continue the broader retained front-end widening now that the startup-prelude math/runtime band is green enough to probe through `sub_451E46 -> sub_460490 -> UI_StartAnims`
  - the next retained class/runtime target is no longer the slot/parser export band, the low-risk file/runtime wrapper band, the x87 math band, the earlier `PlayGame_Dispatch` UI/data/runtime band, or the bare mission-loader `JUMPOUT`; it is the next helper band reached inside the partially recovered mission-loader slice at `sub_40D330` and `sub_44C2A0`
  - do not treat `Rules_ShowBanner_StrategicClash` or bare `sub_499990` as a local fix for the contained `oddzial` miss
  - do not land a direct `PlayGame` reference in `bootstrap_main.c` yet; it immediately reopens the wider gameplay/session unresolved surface

## Batch 125 - C++ executable regeneration bootstrap wave

- Current frontier:
  - establish the parallel C++ executable track on top of the already-green recovered C and bootstrap targets
- Active work:
  - baseline `clash95_recovered` on a clean branch and capture the raw unresolved-link surface into canonical artifacts
  - add an executable-regeneration skill instead of broadening the existing unit-type recovery skill
  - introduce initial C++ class wrappers around the highest-confidence seams (`DLXSpriteSet`, `CAviDecompressor`, `CSyncObject`)
  - wire new parallel CMake targets without destabilizing the existing C build
- Expected outputs this wave:
  - `EXECUTABLE_LINK_BLOCKERS.md`
  - `LINK_SURFACE_AUDIT.csv`
  - `EXECUTABLE_REGEN_PLAN.md`
  - `CPP_CLASS_CROSSWALK.csv`
  - `CPP_SUBSYSTEM_NOTES.md`
  - `SDL_BACKEND_GAP_AUDIT.md`
  - `RUNTIME_WRAPPER_STATUS.md`
  - `STRUCT_RECOVERY_NOTES.md`
- Status at batch start:
  - `cmake -S . -B build` succeeds
  - `cmake --build build --target clash95_recovered -j` succeeds
  - direct `gcc` link probe still fails and is being used as the raw blocker inventory rather than as the executable strategy
- Outcomes:
  - added the executable-regeneration canonical docs and the dedicated `.agents/skills/regenerate-cpp-executable/SKILL.md`
  - added `clash95_cpp_core` and `clash95_cpp_regen` alongside the existing `clash95_recovered` and `clash95_bootstrap` targets
  - landed conservative C++ wrappers for `DLXSpriteSet`, `CAviDecompressor`, and `CSyncObject`
  - kept the recovered C baseline and the existing bootstrap executable green
- Validation:
  - `cmake -S . -B build`
  - `cmake --build build --target clash95_recovered -j`
  - `cmake --build build --target clash95_bootstrap -j`
  - `cmake --build build --target clash95_cpp_core -j`
  - `cmake --build build --target clash95_cpp_regen -j`
  - `timeout 1s build/bin/clash95_bootstrap`
  - `timeout 1s build/bin/clash95_cpp_regen`
  - `timeout 2s build/bin/clash95_cpp_regen --authentic-startup-prelude`
  - `python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures_cpp_regen.json`
  - `python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_cpp_regen.json`
  - `git diff --check`
- Resulting milestone:
  - `clash95_cpp_regen` now links and stays alive for the default one-second smoke run, matching the current bootstrap wedge
  - the deeper `--authentic-startup-prelude` path still faults with exit status `139`, so the next frontier remains the existing startup/runtime crash band rather than C++ target creation itself
