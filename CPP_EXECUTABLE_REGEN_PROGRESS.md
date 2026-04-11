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

## Latest runtime update - 2026-04-11

- `clash95_recovered`, `clash95_bootstrap`, and `clash95_cpp_regen` are still green together after the latest diagnostic and retained-link reduction pass.
- The durable memory was corrected against the live tree:
  - the pre-confirm contained load-menu corridor is still green through authentic slot-strip selection and bottom-row load confirm
  - the live post-confirm probe no longer reaches `load-menu-post-confirm-after-save`; with the current broader-rules bootstrap it dies during save replay at `parse-make-instance-before-class-lookup`
  - the retained broader startup-prelude executable-regeneration slice is no longer blocked on the local x87-heavy math/runtime band
- The last directly traced contained runtime split remains explicit:
  - the exact post-confirm probe lane must now set `CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm` alongside `CLASH95_MENU_PROBE_AUTO_CLICK=load`; the older duplicated `CLASH95_MENU_PROBE_AUTO_CLICK=load` sidecar command was stale and stopped before confirm
  - with the corrected broader-rules bootstrap, the probe reaches `load-menu-post-confirm-load-save`, seeds `MAIN` and `make-instance`, then fails at `sub_4B0480` with `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, the same corrected probe dies earlier with `symbol-lookup-missing-table MAIN`
  - this proves `sub_4725B0` / `sub_482260` / `sub_491B10` seed parser/symbol state but do not yet provide the authentic defclass/bload registry needed by the save replay
- The retained executable-regeneration slice also moved this batch:
  - the retained rules math builtin band under `sub_4A3790` is still recovered in place in `clash95.c`, and the direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` remain green
  - the retained `PlayGame_Dispatch` probe no longer stops on the mission-loader helper-name gap: the first recovered cases now call the existing recovered helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly, and the standalone retained `PlayGame_Dispatch` probe now links and stays alive under `timeout 1s`
  - the port reinforcement ring offsets and unit-type pool are now materialized directly from `clash95.asm`
  - the former `PlayGame_Dispatch` UI/data/runtime band is already reduced in recovered C: `UI_CheckDialogAccepted`, `UI_CheckConfirmQuit`, the reached `unit_stats` byte lane, the queen departure-event tables/buffer slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are no longer live retained blockers
  - the retained mission-loader lane also moved in recovered C:
    - `Scenario_LoadMissionByIndexAndPlay` now threads the real selector into `Scenario_LoadMissionByIndex`
    - `createUnit` / `createCastle` now carry the original sentinel-terminated unit lists through real varargs instead of depending on x86 stack accidents
    - the menu-reachable `sub_460360` cases `0`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `10`, and `11` are now materialized from asm as campaign-entry map loaders (`k_mapa1l.map`, `k_mapa2l.map`, `k_mapa3l.map`, `k_mapa4j.map`, `k_mapa5j.map`, `k_mapa6j.map`, `k_mapa7z.map`, `k_mapa8z.map`, `p_mapa1z.map`, and `p_mapa2z.map`) with the corroborated player-state, name, unit, and castle setup
    - `mapK2` / case `1` now also preserves its case-local post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff and its manual camera override after `Game_InitPlayerViewState`
    - `mapK3` / case `2` now also preserves its case-local player-2 intelligence write, the `Treg Rock` post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff, and the same post-initializer camera override in recovered C
    - `mapK4` / case `3` now also preserves its four-player setup, the `Ughuata` post-castle `BUILDING_RECORD(castle_index) + 18 = -1`, `BUILDING_RECORD(castle_index) + 438 = 300`, the explicit `Building_OnGarrisonChange` handoff, and the three case-local raw stack mutation bands in recovered C, with no copied camera override after `Game_InitPlayerViewState`
    - `mapK5` / case `4` now also preserves its three-player setup, the absence of minimap writes, the exact `Totaweon` / `Hopenberg` spawn lists, the `BUILDING_RECORD(castle_index) + 18 = 9` garrison preseed, the `Building_UnitGetInto` handoff, the 12-slot raw stance/status OR loop, the prisoner-slot writes, and the final `Rules_LogAssignedCastleFact(..., 4)` tail in recovered C
    - `mapK6` / case `5` now also preserves its mission-local byte flag clear, the `Furd` / `Dulimam` versus `Wetus` / `Riludius` name fork, the player-2 religion flag clear, the player-1 minimap reveal, the player-1..3 intelligence writes, the `Defambrion` `BUILDING_RECORD(+438) += 200`, `Katha Gha` `BUILDING_RECORD(+438) = 1000`, `Ghih Up` `BUILDING_RECORD(+18) = -1`, the raw 10-slot stack-status OR loop, and the final `Rules_LogAssignedPlayerFact(3, 5)` tail in recovered C
    - `mapK7` / case `6` now also preserves its three-player `Alan` / `Walter` / `Drebegen` setup, the player-2 intelligence write, the player-1 and player-2 religion clears, the exact `Dragmounth` / `Akserion` / `Ghettan` / `Bhua Rock` / `Jolarion` castle lane, the single-stack raw byte OR, the 10-slot raw status OR loop, the two `Rules_SyncArmyFactStrength` handoffs, the `Ghettan` prisoner-slot write, the `Bhua Rock` / `Jolarion` `BUILDING_RECORD(+438)` writes, and the post-`Game_InitPlayerViewState` camera override in recovered C
    - `mapK8` / case `7` now also preserves its four `Rules_RetractTreasureFact` calls, the four-player `Alan` / `Uraken` / `Wodar` / `Richard V` setup, the `Weghetown` / `Henrion` / `Moon Town` / `Gate Stone` / `Canoowar` / `Trungeon` / `Leweburg` / `Defambrion` castle lane, the three case-local raw slot-byte OR loops, the final `& 0xFC | 2` slot-byte carry loop, and the absence of any post-castle `BUILDING_RECORD(...)` patchup or post-init camera override in recovered C
    - `mapK9` / case `8` now also preserves its player-0 queen relationship writes, the `Alan` / `Sir James` / `Ruryk` / `Riludius` setup, the `Totaweon` / `Gordmouth` / `Timbran` / `Ghettan` / `Hopenberg` / `Katha Gha` / `Werneom` castle lane, the `Gordmouth` `BUILDING_RECORD(+438) -= 100` cut, the three case-local raw slot-byte OR loops, the two direct `& 0xFC | 2` slot-byte rewrites, and the absence of any post-init camera override in recovered C
    - `mapK10` / case `9` now also preserves its five-player `Alan` / `Twogor` / `Drebegen` / `Mieszko` / `Chester` setup, the `Gorendberg` / `Timbran` / `Ghettan` / `Bhua Rock` / `Katha Gha` / `Stormus` / `Guluali` castle lane, the case-local `BUILDING_RECORD(+438)` cuts/assignments/addition, the direct `BUILDING_RECORD(+444)` masked writes for `Gorendberg`, `Timbran`, and `Guluali`, and the absence of any raw stack loops or post-init camera override in recovered C
  - the surviving retained blocker is no longer the old `sub_40D330` / `sub_44C2A0` helper band, `mapK2`, `mapK3`, `mapK4`, `mapK5`, `mapK6`, `mapK7`, `mapK8`, `mapK9`, or `mapK10`; it is the remaining `Scenario_LoadMissionByIndex` case recovery itself, starting with `mapP3` / case `12`
- The next executable-regeneration frontier remains split, not singular:
  - keep the contained load-menu wedge green while pursuing the missing authentic class/bload prelude, not a local save-load hack
  - separately continue the broader retained front-end widening now that the startup-prelude math/runtime band is green enough to probe through `sub_451E46 -> sub_460490 -> UI_StartAnims -> PlayGame_Dispatch`
  - the next retained class/runtime target is no longer the slot/parser export band, the low-risk file/runtime wrapper band, the x87 math band, the earlier `PlayGame_Dispatch` UI/data/runtime band, the bare mission-loader `JUMPOUT`, the `sub_40D330` / `sub_44C2A0` helper gap, `mapK2`, `mapK3`, `mapK4`, `mapK5`, `mapK6`, `mapK7`, `mapK8`, `mapK9`, or `mapK10`; it is the next remaining `Scenario_LoadMissionByIndex` case slice, starting with `mapP3`
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
