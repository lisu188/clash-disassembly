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

## Latest runtime update - 2026-04-13

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
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit and returns into `PlayGame` without the old fabricated `v5` / `v7` temporaries
  - the `PlayGame` prologue now restores the asm-backed `backgr1.s32` / `backgr2.s32` / `backgr3.s32` and `treemas1.s32` / `treemas2.s32` / `treemas3.s32` loads, and its first player scan no longer depends on uninitialized counters
  - the retained rules math builtin band under `sub_4A3790` is still recovered in place in `clash95.c`, and the direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` remain green
  - the retained `PlayGame_Dispatch` probe no longer stops on the mission-loader helper-name gap: the first recovered cases now call the existing recovered helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly, and the standalone retained `PlayGame_Dispatch` probe now links and stays alive under `timeout 1s`
  - the direct retained `PlayGame` probe now also links and stays alive under `timeout 1s`
  - the first `WorldMap_RunHumanTurnLoop` reduction is now in recovered C too: its zero-init entry flags and its mission-success `sub_4623C0("arama1", "kon_por1")` tail now match asm
  - the port reinforcement ring offsets and unit-type pool are now materialized directly from `clash95.asm`
  - the former `PlayGame_Dispatch` UI/data/runtime band is already reduced in recovered C: `UI_CheckDialogAccepted`, `UI_CheckConfirmQuit`, the reached `unit_stats` byte lane, the queen departure-event tables/buffer slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are no longer live retained blockers
  - the retained mission-loader lane also moved in recovered C:
    - `Scenario_LoadMissionByIndexAndPlay` now threads the real selector into `Scenario_LoadMissionByIndex`
    - `createUnit` / `createCastle` now carry the original sentinel-terminated unit lists through real varargs instead of depending on x86 stack accidents
    - the menu-reachable `sub_460360` cases `0`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `10`, `11`, `12`, `13`, `14`, `15`, `16`, and `17` are now materialized from asm as campaign-entry map loaders (`k_mapa1l.map`, `k_mapa2l.map`, `k_mapa3l.map`, `k_mapa4j.map`, `k_mapa5j.map`, `k_mapa6j.map`, `k_mapa7z.map`, `k_mapa8z.map`, `p_mapa1z.map`, `p_mapa2z.map`, `p_mapa3z.map`, `p_mapa4l.map`, `p_mapa5l.map`, `p_mapa6l.map`, `p_mapa7j.map`, and `p_mapa8j.map`) with the corroborated player-state, name, unit, and castle setup
    - `mapK2` / case `1` now also preserves its case-local post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff and its manual camera override after `Game_InitPlayerViewState`
    - `mapK3` / case `2` now also preserves its case-local player-2 intelligence write, the `Treg Rock` post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff, and the same post-initializer camera override in recovered C
    - `mapK4` / case `3` now also preserves its four-player setup, the `Ughuata` post-castle `BUILDING_RECORD(castle_index) + 18 = -1`, `BUILDING_RECORD(castle_index) + 438 = 300`, the explicit `Building_OnGarrisonChange` handoff, and the three case-local raw stack mutation bands in recovered C, with no copied camera override after `Game_InitPlayerViewState`
    - `mapK5` / case `4` now also preserves its three-player setup, the absence of minimap writes, the exact `Totaweon` / `Hopenberg` spawn lists, the `BUILDING_RECORD(castle_index) + 18 = 9` garrison preseed, the `Building_UnitGetInto` handoff, the 12-slot raw stance/status OR loop, the prisoner-slot writes, and the final `Rules_LogAssignedCastleFact(..., 4)` tail in recovered C
    - `mapK6` / case `5` now also preserves its mission-local byte flag clear, the `Furd` / `Dulimam` versus `Wetus` / `Riludius` name fork, the player-2 religion flag clear, the player-1 minimap reveal, the player-1..3 intelligence writes, the `Defambrion` `BUILDING_RECORD(+438) += 200`, `Katha Gha` `BUILDING_RECORD(+438) = 1000`, `Ghih Up` `BUILDING_RECORD(+18) = -1`, the raw 10-slot stack-status OR loop, and the final `Rules_LogAssignedPlayerFact(3, 5)` tail in recovered C
    - `mapK7` / case `6` now also preserves its three-player `Alan` / `Walter` / `Drebegen` setup, the player-2 intelligence write, the player-1 and player-2 religion clears, the exact `Dragmounth` / `Akserion` / `Ghettan` / `Bhua Rock` / `Jolarion` castle lane, the single-stack raw byte OR, the 10-slot raw status OR loop, the two `Rules_SyncArmyFactStrength` handoffs, the `Ghettan` prisoner-slot write, the `Bhua Rock` / `Jolarion` `BUILDING_RECORD(+438)` writes, and the post-`Game_InitPlayerViewState` camera override in recovered C
    - `mapK8` / case `7` now also preserves its four `Rules_RetractTreasureFact` calls, the four-player `Alan` / `Uraken` / `Wodar` / `Richard V` setup, the `Weghetown` / `Henrion` / `Moon Town` / `Gate Stone` / `Canoowar` / `Trungeon` / `Leweburg` / `Defambrion` castle lane, the three case-local raw slot-byte OR loops, the final `& 0xFC | 2` slot-byte carry loop, and the absence of any post-castle `BUILDING_RECORD(...)` patchup or post-init camera override in recovered C
    - `mapK9` / case `8` now also preserves its player-0 queen relationship writes, the `Alan` / `Sir James` / `Ruryk` / `Riludius` setup, the `Totaweon` / `Gordmouth` / `Timbran` / `Ghettan` / `Hopenberg` / `Katha Gha` / `Werneom` castle lane, the `Gordmouth` `BUILDING_RECORD(+438) -= 100` cut, the three case-local raw slot-byte OR loops, the two direct `& 0xFC | 2` slot-byte rewrites, and the absence of any post-init camera override in recovered C
    - `mapK10` / case `9` now also preserves its five-player `Alan` / `Twogor` / `Drebegen` / `Mieszko` / `Chester` setup, the `Gorendberg` / `Timbran` / `Ghettan` / `Bhua Rock` / `Katha Gha` / `Stormus` / `Guluali` castle lane, the case-local `BUILDING_RECORD(+438)` cuts/assignments/addition, the direct `BUILDING_RECORD(+444)` masked writes for `Gorendberg`, `Timbran`, and `Guluali`, and the absence of any raw stack loops or post-init camera override in recovered C
    - `mapP3` / case `12` now also preserves its `Raylin` / `Gaalaad` setup, the player-1 human/minimap/religion writes, the player-1 no-castle unit lane, the `Sarturia` `BUILDING_RECORD(+438) = 5000` write, and the post-`Game_InitPlayerViewState` camera override back onto player `1` in recovered C
    - case `13` / `p_mapa4l.map` now also preserves its four-player `Raylin` / `Leryks X` / `Glazur` / `Sir John` setup, the single `Ungught` castle lane, the random per-slot `Rng_RandRange(5, 20)` loop on the stack at `TILE_INDEX(25, 28)`, the three no-castle unit lanes for players `2..4`, and the absence of any post-castle building writes or post-init camera override in recovered C
    - case `14` / `p_mapa5l.map` now also preserves its three-player `Raylin` / `Uraken` / `Wodar` setup, the `Weghetown` post-castle `BUILDING_RECORD(+430) & 0xF000` low-word clear, the `Timbran` `BUILDING_RECORD(+18) = 0xF` write, the forced garrison insert at `(52,26)`, the raw 12-slot `& 0xFC | 1` garrison loop, the two `Building_OnGarrisonChange` handoffs, the three prisoner-slot type/owner writes, the `Fraggmeon` / `Eufurhon` `BUILDING_RECORD(+438) += 200` boosts, the final `Rules_LogAssignedCastleFact(..., 14)` tail, and the absence of any post-init camera override in recovered C
    - case `15` / `p_mapa6l.map` now also preserves its mission-local `gameData + 140021` byte clear, the four-player `Raylin` / `Frederic` / `Sir James` / `Agordeh` setup, the player-4 intelligence write, the `Defambrion` `BUILDING_RECORD(+438) += 200` boost, the `Ghih Up` `BUILDING_RECORD(+438) = 1000` and `BUILDING_RECORD(+18) = -1` writes, the `Guluali` `BUILDING_RECORD(+438) = 2000` write, the final `Rules_LogAssignedPlayerFact(4, 15)` tail, and the absence of any post-init camera override in recovered C
    - case `16` / `p_mapa7j.map` now also preserves its mission-local `gameData + 140021` byte clear, the three-player `Raylin` / `Kalev` / `Ianos` setup, the player-2 and player-3 intelligence writes, the `Gwadat` `BUILDING_RECORD(+444)` masked write, the four raw slot-state mutation bands rooted at `TILE_INDEX(26, 40)`, `TILE_INDEX(61, 43)`, `TILE_INDEX(63, 86)`, and `TILE_INDEX(65, 44)`, the post-`Game_InitPlayerViewState` player-1 camera override, and the preserved absence of any `Rules_LogAssigned*` tail in recovered C
    - case `17` / `p_mapa8j.map` now also preserves its mission-local `gameData + 140021` byte clear, the four `Rules_RetractTreasureFact` calls, the four-player `Raylin` / `Lord Ruwe` / `McGregor` / `Crowley` setup, the `Dark Town` `BUILDING_RECORD(+438) -= 100` cut, the four raw slot-state mutation bands rooted at `TILE_INDEX(26, 40)`, `TILE_INDEX(61, 43)`, `TILE_INDEX(63, 86)`, and `TILE_INDEX(65, 44)`, and the preserved absence of any post-`Game_InitPlayerViewState` camera override or `Rules_LogAssigned*` tail in recovered C
    - case `18` / `p_mapa9j.map` now also preserves its five-player `Raylin` / `Tubius` / `Lord Gorio` / `McDan` / `Drebegen` setup, the `Stone Bell` `BUILDING_RECORD(+438) -= 100` cut, the `Fhur Tao` `BUILDING_RECORD(+438) += 200` boost, the direct raw slot-state writes on the `+28` lane rooted at `TILE_INDEX(7, 7)`, `TILE_INDEX(78, 45)`, `TILE_INDEX(10, 51)`, `TILE_INDEX(49, 74)`, `TILE_INDEX(70, 80)`, and `TILE_INDEX(37, 29)`, and the preserved absence of any post-`Game_InitPlayerViewState` camera override or `Rules_LogAssigned*` tail in recovered C
    - case `19` / `p_map10z.map` was already present and is now corroborated against `mapP10` in asm: five-player `Sir Mordus` / `Raylin` / `Galaghan` / `Longhand` / `Riludius`, the `Gorendberg` `BUILDING_RECORD(+438) -= 100` cut, the `Ghettan` `BUILDING_RECORD(+438) = 600` write, the `Stormus` / `Guluali` `BUILDING_RECORD(+438) += 300` boosts, and no post-`Game_InitPlayerViewState` camera override or raw slot-state loop
  - the surviving retained blocker is no longer the old `sub_40D330` / `sub_44C2A0` helper band, the mission-loader `JUMPOUT`, or any of the 20 `Scenario_LoadMissionByIndex` case arms; it is now the deeper post-`PlayGame` human-turn widening inside `WorldMap_RunHumanTurnLoop` after the repaired entry/tail slice
- The next executable-regeneration frontier remains split, not singular:
  - keep the contained load-menu wedge green while pursuing the missing authentic class/bload prelude, not a local save-load hack
  - separately continue the broader retained front-end widening now that the startup-prelude math/runtime band is green enough to probe through `sub_451E46 -> sub_460490 -> UI_StartAnims -> PlayGame_Dispatch`
  - the next retained class/runtime target is no longer the slot/parser export band, the low-risk file/runtime wrapper band, the x87 math band, the earlier `PlayGame_Dispatch` UI/data/runtime band, the bare mission-loader `JUMPOUT`, the `sub_40D330` / `sub_44C2A0` helper gap, or any remaining `Scenario_LoadMissionByIndex` case slice; it is the deeper gameplay/session surface inside `WorldMap_RunHumanTurnLoop` after the repaired entry/tail slice, and only then the adjacent AI branch `sub_451F70`
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

## Latest retained widening update
- `WorldMap_RunHumanTurnLoop` now restores the next asm-backed call-shape band directly in recovered C:
  - zero-arg `UI_ReadCheatString(0)`, `DD_Pump((int)dword_544CD8, 0)`, `sub_407B20(0, 0, 0)`, `WorldMap_RedrawFrame(0)`, and `WorldMap_HandleTopMenuBar(0, 0)` at loop entry
  - held-key turn-left and turn-right loops that keep pumping `DD_Pump((int)dword_544CD8, 0)`
  - the queued-path action-point gate from the high word of the last move-track step
  - the escape/debug render block with explicit save/restore of the previous resource handle and `g_RenderHook`
- The direct retained `WorldMap_RunHumanTurnLoop` probe now links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains the deeper `WorldMap_RunHumanTurnLoop` loop body after the repaired zero-init entry, `arama1` / `kon_por1` mission-success tail, and repaired call-shape band. The adjacent AI branch `sub_451F70` is still secondary.

## Latest retained widening update
- `WorldMap_HandleTopMenuBar` now restores the retained `sub_40E8B0` helper band directly in recovered C: the menu-sprite draw call, the mission `3`/`13` versus `4`/`14` turn-counter text, the temporary menu-surface destroy call, and the saved render-hook/resource-handle restore block are all local recovered behavior now.
- `UnitStackSelection_HandleInput` now also restores the retained `sub_423860` helper band directly in recovered C: zero-arg `Render_Begin` calls, real adjacent-tile move coordinates into `Unit_MoveSelectionFromGroupToTile`, `dword_526F78` zero-on-success, and the `Render_LoadResourceSprite_v2` plus selection-panel redraw success tail are all local recovered behavior now.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker is now the deeper `WorldMap_RunHumanTurnLoop` body after those repaired helper bands, with first focus on `WorldMap_HandleTileHoverAndClick` / `sub_4084A0` rather than SDL, compat, or `src_cpp` seams.

## Latest retained widening update
- `WorldMap_HandleTileHoverAndClick` now restores the next retained `sub_4084A0` call-shape tranche directly in recovered C: the `MapTile_HasOwnOrVisibleEnemyUnitStack` and `MapTile_HasBuilding` wrappers no longer forward undefined coordinates, the lost-surface stack-selection lane now uses `UnitStack_ShowSelectionDialog(..., 1)`, the temple/building/self-move execute tails now use the zero-arg `UnitStack_ExecuteQueuedPath` shape from asm, and the own-stack merge/reselection lane now reloads resources with `Render_LoadResourceSprite_v2`.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper enemy-building / enemy-stack attack band rather than the already-repaired wrapper and execute-tail tranche.

## Latest retained widening update
- `WorldMap_HandleTileHoverAndClick` now also restores the hovered stack-id reads in the next retained `sub_4084A0` tranche directly in recovered C: the own-stack merge/add-to-group branch and the visible enemy-stack attack branch no longer depend on decompiler-only `v50` / `v58` / `v67` tile-offset ghosts, and instead read the hovered stack id directly from `TILE_INDEX(v1, v78)`.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper enemy-building `Unit_AttackBuilding` call-shape plus own-stack reselection clear-mask lane rather than the already-reduced hovered stack-id band.

## Latest retained widening update
- `WorldMap_HandleTileHoverAndClick` now also restores the next retained `sub_4084A0` reselection helper semantics directly in recovered C: the own-stack reselection branch no longer threads `v52` through `UnitStackSelection_ClearMask`, and `UnitStackSelection_ClearMask` itself now matches asm by zeroing the global `dword_526F78` mask rather than a fake caller-provided buffer.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper enemy-building `Unit_AttackBuilding` / building-interaction band rather than the already-reduced hovered stack-id and clear-mask lanes.

## Latest retained widening update
- `WorldMap_HandleTileHoverAndClick` now also restores the shared hovered building-id reads in the next retained `sub_4084A0` tranche directly in recovered C: the enemy-building attack predicate and the own-building approach branch no longer re-read the hovered tile entry through raw offset expressions, and instead share the same `TILE_INDEX(v1, v78)`-derived building id.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper enemy-building `Unit_AttackBuilding` call-shape plus own-building approach-path lane rather than the already-reduced building-id read scars.

## Latest retained widening update
- `WorldMap_HandleTileHoverAndClick` now also restores the next retained selected-stack-forwarding band around the building interaction helpers directly in recovered C: `Building_GenerateApproachTrack` no longer pulls the selected stack record through the bogus `v12`, `Unit_AttackBuilding` no longer loses the selected stack index in its opening sprite draw and record lookup, and its local move-to-building prelude no longer forwards the undefined `v9`.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper mid-body `Unit_AttackBuilding` garrison/combat-resolution lane rather than the already-reduced selected-stack-forwarding prelude.

## Latest retained widening update
- `Unit_AttackBuilding` now restores the next retained mid-body `sub_4084A0` lane directly in recovered C: the human-controller prompt gate now uses the real attacker/building owner records, the `UI_PromptLeadTroopsPersonally` and `CalculateBattleResult` calls now carry the asm-backed 12-slot building-garrison shape, the garrison timer clear loop now walks all 12 slots explicitly, and the capture paths now keep the real building index instead of fabricated locals.
- `clash95.c` now also exposes the recovered roster as a canonical `unit_type` enum sourced from the existing `UNIT_TYPES_AND_STATS.*` artifacts, so the retained gameplay/runtime work and the unit-taxonomy sidecars share one code-level id surface.
- The direct retained `WorldMap_RunHumanTurnLoop` probe still links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker remains inside `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, but it is now the deeper `Unit_AttackBuilding` outcome-resolution tails after the repaired prompt/garrison/capture-index tranche.

## Superseded front-end runtime update
- This front-end foothold has been superseded by the full-game bootstrap update below: host-side probe modes and menu/capture env controls are no longer active bootstrap selectors.

## Latest full-game bootstrap update
- `clash95_bootstrap` no longer has host-side bootstrap modes. `main()` compacts argv into the recovered command-line buffer and always enters `App_WinMain`, so old switches such as `--authentic-startup-prelude`, `--authentic-video-init`, `--authentic-menu-probe`, and `--platform-window-only` are now just forwarded command-line text rather than bootstrap selectors.
- The menu-probe env surface has been collapsed: bootstrap auto-click/capture/broader-rules controls are fixed no-ops/defaults, and the recovered-core `CLASH95_TRACE_MENU_PROBE` gates are disabled constants. The remaining tracked `CLASH95_*` env reads are SDL presented-frame dump diagnostics (`CLASH95_DUMP_PRESENTED_FRAMES_PREFIX` and the compatibility alias `CLASH95_SCREENSHOT_PREFIX`).
- The full route links and stays alive after adding the missing retained runtime helpers and hardening `strcmp_` against malformed retained parser/rules pointers. Validation uses forced-kill live smokes for both `clash95_bootstrap` and `clash95_cpp_regen`.
- The retained log-file creation slice is back in the full route: `createLogFiles` now truncates/creates `clash.log` and `battle.log` from the asm-observed `logEnabled` branch without entering the unsafe Watcom stream-open local-variable scar.
- CTest now tracks the same full route: the superseded menu-capture probe test was replaced by `clash95_full_route_smoke`, which starts `clash95_bootstrap` under dummy SDL/audio, requires the process to stay alive briefly, and then shuts down the process group from the harness.
- The next executable-regeneration blockers are now authentic finite shutdown/verification, the still-skipped DirectSound-era `CSS_Init` table, and the broader playable session milestone after the full default startup route.

## Latest finite shutdown update
- The lowercase `r` command-line route is now the first finite authentic startup/shutdown milestone on the full `App_WinMain` path:
  - `clash95_bootstrap r` enters recovered early startup and runtime/render init, skips `Bootstrap_RunRecoveredGameEntry`, runs shutdown, and exits `0`
  - `clash95_cpp_regen r` follows the same route and exits `0`
- The supporting recovered/runtime fixes in this batch stayed on the executable-regeneration seam:
  - router lookup and missing-logical-name diagnostics now preserve the requested logical name and avoid early recursive `werror` diagnostics
  - shutdown uses explicit compact-surface destructor dispatch for recovered 32-bit software-surface vtables and explicit native COM-method dispatch for SDL DirectDraw-compat vtables
  - `strcmp_` now has cached readable-range validation so malformed recovered pointers do not crash startup comparisons
- CTest now includes `clash95_r_command_shutdown_smoke`; that new finite smoke passes.
- The older default no-arg liveness test is no longer green in this branch: the no-arg path exits early through `UI_StartAnims -> Video_Avi_playIn -> App_RequestQuit` with `[platform_sdl] Clash: Clash CD not found!`. The next front-end runtime blocker is therefore the intro AVI/CD/resource path, not the finite lowercase `r` route.

## Latest default full-route update
- The default no-arg route is live again on the recovered `App_WinMain` path:
  - `Win_BeginModeChange` now accepts directly readable loose AVI files when the recovered resource query misses them, which removes the previous `Clash CD not found!` early quit on the local install
  - the reached AVI, event-handle, DirectDraw palette, compact render-surface, and main-menu widget dispatch scars were reduced in recovered C / SDL compat glue without adding a host-side fake probe mode
  - the reached `CAviDecompressor` constructors now route through the shared byte-offset initializer, removing the pointer-scaled event-handle initialization crash observed on the default intro path
  - `clash95_full_route_smoke` now passes by observing `clash95_bootstrap` alive in the recovered main-menu wait loop before external shutdown
- The finite lowercase `r` route remains the clean recovered startup/shutdown verification for both `clash95_bootstrap` and `clash95_cpp_regen`.
- Validation for this update:
  - `cmake --build build --target clash95_recovered clash95_bootstrap clash95_cpp_core clash95_cpp_regen -j`
  - `tests/verify_r_command_shutdown.sh build/bin/clash95_bootstrap`
  - `tests/verify_r_command_shutdown.sh build/bin/clash95_cpp_regen`
  - `ctest --test-dir build --output-on-failure`
  - `ctest --test-dir build --output-on-failure --repeat until-fail:3`
- The next executable-regeneration blocker is no longer intro AVI/CD availability. It is now deeper menu/session fidelity after the recovered main-menu liveness milestone, with `CSS_Init` still deferred independently.

## Latest direct-game route update
- The direct `a` command-line route now advances substantially farther through the recovered `PlayGame` entry:
  - the direct branch passes resource context `16`, matching the original BL value before `WorldMap_Initialize` and `PlayGame`
  - the building-sprite-cache slab is backed by a single 650-byte host block, so cache reset/load no longer corrupts the filesystem holder
  - `Render_DrawSprite` draws the recovered world-map frame through the existing format-0 linear sprite path instead of reading an eight-byte target from compact 32-bit vtables
- Exploratory `timeout -k 1s 2s build/bin/clash95_bootstrap a` and `clash95_cpp_regen a` now stop later in `PlayGame -> sub_418700 -> sub_416850`.
- The next direct-game blocker is visible-tile rendering and its remaining compact render-surface vtable callsites, not filesystem path handling or the top-level frame draw.

## Latest direct-game liveness update
- The reached `sub_416850` fog-covered-tile fill now uses a recovered linear-surface helper instead of compact render-surface slot `+0x1C`.
- CTest now includes direct `a` route liveness smokes for both executable paths:
  - `clash95_direct_a_route_smoke`
  - `clash95_cpp_regen_direct_a_route_smoke`
- The direct `a` route is no longer a crash-only exploratory path. It now reaches a smoke-testable world-map liveness milestone, with external harness shutdown still required.
- The next executable-regeneration blocker remains deeper direct-game/menu/session fidelity, especially the unreduced compact render callsites still present beyond the first reached hidden-tile fill in `sub_416850`.

## Latest direct-game control-path update
- The direct `a` route now gets past the next reached decompiler scars in the world-map/control corridor:
  - the two `sub_418700` tile-row counters
  - the `map_butt.s32` action-button sprite load
  - the packed `dword_511D40` world-map action widget table
  - the `sub_4191F0` packed-widget draw reads
  - the `sub_405020` fade-loop counter
  - the diagnostic unit-dump loop counter
  - the `Game_AdvanceToNextPlayerTurn` active-player/wraparound check
- The current executable targets still build and CTest remains green for the default full route, lowercase `r`, and both direct `a` liveness smokes.
- The direct `a` route now exposes a data frontier: original `sub_44C400` tries to load `save\\10.dat`; that file is absent locally, so the roster remains all-zero and the route samples in `Game_AdvanceToNextPlayerTurn` waiting for an active player.
- The world-map building-action record is present in the recovered table, but its action callback is quarantined behind `WorldMap_DeferBuildingActionCallback` until the authentic `sub_40A0E0` building/treasure-placement link surface is recovered.

## Latest direct-scenario update
- The separate `/A0` scenario-start route no longer fails in `Video_Avi_playIn -> Win_EndModeChange`.
- The recovered full-game path now carries `/A0` through:
  - intro-logo AVI argument recovery
  - map-file load through compact low32 buffers
  - local five-player runtime-state setup
  - rules/parser fact setup far enough to seed the first scenario units
  - minimap creation, color-table initialization, and vision propagation
- The active fixes stayed in `bootstrap_main.c` and recovered C:
  - no new host-side scenario probe was added
  - no SDL backend change was needed
  - `clash95_cpp_regen /A0` follows the same bootstrap wedge and stays alive under the same dummy SDL/audio timeout smoke as `clash95_bootstrap /A0`
- The next direct-scenario blockers are deeper session/playability fidelity after the liveness milestone, plus the deliberately deferred minimap frame sprite blit through `sub_402E80`.

## Latest direct-scenario unit-stack update
- The `/A0` route now also survives the reached unit-stack merge/delete corridor in both executable paths.
- The active fixes stayed in recovered C:
  - `Rules_CreateArmyFact` skips `Rules_LinkArmyFact` when `Rules_AssertFact` returns null, preventing recursive `Rules_EnsureArmyFactForStack` reentry
  - `Unit_AddToGroup` uses asm-backed source/target stack pointers and the original 31-byte slot merge copy length
  - `Rules_RetractArmyFact` and `Unit_Kill` use their stack-pointer arguments for fact cleanup, diagnostic logging, tile clearing, slot clearing, and minimap redraw
- Wrapped dummy SDL/audio smokes for `clash95_bootstrap /A0` and `clash95_cpp_regen /A0` now run until the external hard timeout instead of dumping core in those reached functions.
- The next direct-scenario blockers remain gameplay/session fidelity, clean shutdown, and the deferred minimap frame sprite blit; no host-side scenario harness or new SDL seam was added.

## Latest direct-scenario CTest update
- Direct `/A0` liveness is now covered by CTest for both executable paths:
  - `clash95_direct_a0_route_smoke`
  - `clash95_cpp_regen_direct_a0_route_smoke`
- The new harness reuses the established process-group smoke shape: start under dummy SDL/audio, require the recovered route to remain alive briefly, shut it down externally, and fail on early exit or crash text.
- This is a validation promotion only. No recovered gameplay path, SDL shim, compat wrapper, or host-side scenario mode was added.

## Latest direct-scenario new-turn update
- The direct `/A0` route now runs through the reached parser/fact queue, building population/plague, prisoner castle-placement, unit fatigue/morale, queen relationship, building technology scan, and sprite-allocation corridor under gdb without a caught fatal signal until the external timeout.
- The active fixes stayed in recovered C plus one narrow compatibility allocator improvement:
  - `Queen_NewTurn` now uses the recovered unit-record pointers and turn-timer ranges for birth, departure, and accepted-marriage scheduling
  - `Building_UpdatePlagueState`, `Building_UpdatePopulationGrowth`, `Building_CheckTechnology`, and the unit-slot morale/fatigue helpers no longer depend on undefined decompiler locals or counters
  - `Building_AdjustAllGarrisonMoraleByDelta` now preserves the caller-supplied asm `edx` morale delta while scanning occupied garrison slots
  - `CompatAllocLow32` now has a small-allocation low32 arena so recovered sprite/resource slabs do not exhaust low-address mappings during scenario startup
  - `sub_472860` follows the recovered free-list table as 32-bit low-address links instead of host pointers
- `clash95_recovered`, `clash95_bootstrap`, `clash95_cpp_core`, and `clash95_cpp_regen` build after these repairs.
- The next frontier is finite direct-scenario behavior: rules/class health, clean shutdown or responsive player-turn evidence, and the still-deferred minimap frame blit through `sub_402E80`.

## Latest direct-scenario render companion update
- The longer direct `/A0` route now gets past the reached `sub_473320` DirectDraw companion-surface creation crash in both executable paths.
- The active fix stayed in recovered C and reused the existing SDL DirectDraw compatibility seam:
  - `sub_4041D0` now passes the asm-backed height/width pair into the companion constructor and leaves the wrapper software-only if `dword_51D584` is absent during a mode-switch gap
  - `sub_473320` now clears and fills the 108-byte descriptor explicitly and calls `Compat_DirectDraw_CreateSurface` instead of reading a raw compact vtable through undefined locals
  - `sub_4732A0` now reports construction failure to its only caller so dead companion handles are not installed
- `clash95_recovered`, `clash95_bootstrap`, `clash95_cpp_core`, and `clash95_cpp_regen` build after the repair, and the full CTest suite remains green.
- Hard-kill 10-second dummy SDL/audio observations confirm `clash95_bootstrap /A0` and `clash95_cpp_regen /A0` remain alive beyond the previous crash window. SIGTERM teardown still has a separate allocator/stack fault, so clean finite shutdown remains a later frontier.

## Latest direct-scenario all-AI turn update
- The direct `/A0` route is now explicitly documented as an all-AI/autoplay scenario path rather than a human-turn entry path:
  - `Scenario_LoadAllAiMultiplayerMapAndInitView` seeds all five player runtime records as active and clears all five human-controller flags before loading `multi%d.map`
  - GDB breakpoint sampling at `Game_AdvanceToNextPlayerTurn` shows the current player cycling through `0,1,2,3...` with all human flags still zero
- The reached turn-advance body now uses explicit saved-player, human-controller, active-mission, cache-count, and present-rectangle values instead of forwarding undefined decompiler locals.
- `clash95_recovered`, `clash95_bootstrap`, `clash95_cpp_core`, and `clash95_cpp_regen` build after the cleanup, the full CTest suite remains green, and both `/A0` executable paths stay alive until the 10-second hard-kill liveness probe.
- The next frontier remains finite/session fidelity below the all-AI liveness milestone: clean shutdown, rules/class fact health, and deferred minimap-frame blitting.

## Latest `PlayGame` loop cleanup update
- The central `PlayGame` setup/loop/teardown body now preserves the same reached runtime milestone with fewer decompiler scars:
  - non-human tile reveal uses explicit five-player iteration and the recovered player human-controller field
  - `MAP_THEME_INDEX` names the shared `gameData + 140016` selector used by background/tree sprite loads, main-map music, and minimap theme tables
  - render hook/resource-handle switching stores and restores explicit locals instead of undefined temporaries
  - AI turn dispatch, setup logs, selection sync, teardown, and `sub_472860(-1, 0, 0)` no longer forward ghost registers
- `WorldMap_Initialize` now calls `sub_4163F0(0)` explicitly because the asm initializer reads no incoming object state.
- `clash95_recovered`, `clash95_bootstrap`, `clash95_cpp_core`, and `clash95_cpp_regen` build after the cleanup; CTest remains green, and both `/A0` executable paths still stay alive until the 10-second hard-kill probe.

## Latest minimap frame restoration update
- `MiniMap_CreateSurface` now restores the decorative minimap frame sprite draw that was previously deferred:
  - the function still allocates the recovered minimap backing surface and sets `g_RenderDevice` to that surface
  - it fetches `DLX_GetSpriteForChar(dword_5202BC, 4)` and draws it at `(0, 0)` with draw mode `1`
  - it seeds the terrain-color table with `MAP_THEME_INDEX`
- This does not claim the broad generic `sub_402E80` decoder is recovered. The restored frame path is the asm-proven unclipped format-0 sprite shape and uses the already-contained bounded software decoder.
- `clash95_recovered`, `clash95_bootstrap`, `clash95_cpp_core`, and `clash95_cpp_regen` build after the frame restoration; CTest remains green, and both `/A0` executable paths still stay alive until the 10-second hard-kill probe.

## Latest SIGTERM teardown update
- The direct `/A0` route no longer dumps core in the reached SIGTERM/mode-switch `Render_FillRect` fallback.
- The active fix stayed in recovered C:
  - GDB showed teardown reaching `Render_FillRect` with destination `&unk_51D4C0`, no resolved companion, no primary compact handle, and repeated temp-to-primary fallback recursion
  - `Render_FillRect` now returns from that no-target state instead of allocating another temporary surface
- `clash95_recovered`, `clash95_bootstrap`, and `clash95_cpp_regen` build after the guard; CTest remains green.
- `timeout -k 2s 5s` probes for both executable paths produce no core-dump message. The kill-after remains required, so the milestone is "no SIGTERM crash", not clean finite shutdown.
