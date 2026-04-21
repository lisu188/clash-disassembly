# Executable link blockers

This note records the current executable-regeneration gap on the clean `codex/cpp-executable-regen` branch.

## Current build reality

- `clash95_recovered` still builds cleanly as the recovered C static library baseline.
- `clash95_bootstrap` already exists as a narrower executable harness around the same recovered sources.
- `clash95_cpp_core` now builds as a parallel conservative C++ class library.
- `clash95_cpp_regen` now links as a parallel executable by reusing the existing bootstrap wedge and adding the C++ core.
- A direct `gcc` link of `clash95.c`, `platform_sdl_runtime.c`, and `compat/decomp_runtime_stubs.c` does not yet produce a runnable executable.

## Latest authentic runtime frontier - 2026-04-13

- The live executable blocker is no longer row-resource preload, row draws, or save-path formatting.
- The contained SDL-backed executable still keeps the authentic pre-confirm load-menu corridor alive:
  - real row resources load
  - all ten contained `sub_44A140` row draws complete
  - authentic slot-strip selection and bottom-row load confirm both complete
- The live post-confirm split is now explicit:
  - with the current broader-rules bootstrap, the contained probe reaches `parse-make-instance-before-class-lookup` and then logs `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, the same probe dies earlier with `symbol-lookup-missing-table MAIN`
- The next honest contained runtime blocker is therefore not local save I/O or SDL. It is the missing authentic class/bload prelude needed before the save replay can instantiate `oddzial`.
- A direct contained `PlayGame` handoff remains deferred because rooting `PlayGame` from `bootstrap_main.c` immediately reopens the much wider gameplay/session unresolved link surface.

## Latest startup-prelude narrowing - 2026-04-13

- The retained `CLIPS`/startup-prelude surface moved again this batch:
  - direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` still link successfully
  - the standalone retained `sub_451E46` probe still stays alive under `timeout 1s`
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit and returns into `PlayGame` without the old fabricated `v5` / `v7` temporaries
  - the `PlayGame` prologue now restores the asm-backed `backgr1.s32` / `backgr2.s32` / `backgr3.s32` and `treemas1.s32` / `treemas2.s32` / `treemas3.s32` loads, and its first player scan no longer depends on uninitialized counters
  - `WorldMap_RunHumanTurnLoop` now restores the asm-backed zero-init entry flags and the `sub_4623C0("arama1", "kon_por1")` mission-success tail in recovered C
  - the first retained `PlayGame_Dispatch` UI/data/runtime band is now reduced in recovered C: `UI_CheckConfirmQuit`, `UI_CheckDialogAccepted`, the reached `unit_stats` byte lane, the queen departure-event tables/buffer slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are no longer live retained blockers
- A direct-object retained probe for `sub_4996D0` still links successfully.
- The retained mission-loader surface moved again this batch:
  - `Scenario_LoadMissionByIndexAndPlay` now passes the real selector into `Scenario_LoadMissionByIndex`
  - `createUnit` and `createCastle` now match the original sentinel-terminated unit-list contract closely enough to transcribe real mission setup calls
  - the menu-reachable `sub_460360` cases now recovered or corroborated in `clash95.c` are the full 20-arm switch, cases `0` through `19`
  - the first recovered cases now call the already-recovered local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly, so the old retained `sub_40D330` / `sub_44C2A0` helper-name gap is gone
- The next retained blocker is no longer the parser-export layer, the low-risk file/runtime wrapper band, the x87-heavy math band, the broader `PlayGame_Dispatch` UI/data/runtime scatter, the bare mission-loader `JUMPOUT`, the `sub_40D330` / `sub_44C2A0` helper gap, or any remaining mission-loader case arm. The full 20-case `Scenario_LoadMissionByIndex` switch is now covered in recovered C: case `18` / `p_mapa9j.map` is newly materialized with its `Stone Bell` cut, `Fhur Tao` boost, and raw `+28` slot-state mutations still explicit, and the already-present case `19` / `p_map10z.map` now corroborates against `mapP10` closely enough to keep its `Gorendberg`, `Ghettan`, `Stormus`, and `Guluali` treasury writes plus the absence of any post-init camera override intact. The next retained widening is therefore the broader gameplay/session surface after `Scenario_LoadMissionByIndexAndPlay` / `PlayGame`, still centered on `WorldMap_RunHumanTurnLoop` but now past its entry/tail repairs and into the deeper register-loss/usercall surface, not another mission-switch arm.
- Additional retained reduction notes from the latest pass:
  - `UI_CheckConfirmQuit` and `UI_CheckDialogAccepted` are now rebound onto their already-recovered local bodies instead of standing as duplicate retained export holes
  - the `sub_451E46` probe is still green, and the direct retained `PlayGame_Dispatch` probe now links and stays alive under `timeout 1s`
  - the direct retained `PlayGame` probe now also links and stays alive under `timeout 1s`
  - the first retained `WorldMap_RunHumanTurnLoop` pass is now reduced in recovered C at its zero-init prologue and its `arama1` / `kon_por1` mission-success exit
  - `mapK2` now carries its distinct post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff and the case-local camera override directly in recovered C
- Do not use `Rules_ShowBanner_StrategicClash` or bare `sub_499990` as a local fix for the contained post-save `oddzial` miss. That runtime belongs to the broader startup-prelude slice, not the stable `sub_444490` wedge.

## Why the direct link fails

The raw link probe fails immediately on the missing process entrypoint and then fans out into the unresolved startup/runtime surface.

Representative failures from the probe:

- `undefined reference to 'main'`
- `_wcpp_4_static_init__`
- `_wcpp_4_copy_array__`
- `Compat_WcppCtorArrayStorage1m`
- `Compat_WcppCtorArrayStorage1s`
- `CRT_GetBootstrapThreadData`
- `CRT_RegisterFinalizableObject`
- `JUMPOUT`

The object-file unresolved lists show the same shape:

- `build/clash95_unresolved.txt`: 520 unresolved references
- `build/platform_unresolved.txt`: 10 unresolved references
- `build/stubs_unresolved.txt`: 44 unresolved references

## How `clash95_bootstrap` changes the picture

`bootstrap_main.c` provides an honest but limited executable front end:

- `main()` builds a command line and chooses between a default platform loop and an explicit startup prelude.
- The startup prelude routes through `Platform_CreateMainWindow`, `Input_MousePresent`, `Input_MouseAcquire`, `CSS_SetDirectSoundHWnd`, `DetectGameCDPath`, `sub_442AD0`, and `Game_Init`.
- The runtime/render path is still recovered in slices, not as a full executable regrowth.
- Section GC and the object-library split keep the initial executable surface narrower than the raw linker probe.

That means the repo already has a valid bootstrap wedge and now a first parallel `clash95_cpp_regen` target, but the deeper raw executable surface is still unresolved.

## Unresolved categories

The current unresolved surface is not random. It falls into a few stable buckets:

- `startup` and entrypoint glue
- `CRT` / WCpp runtime support
- `platform` Win32-to-SDL seam calls
- `AVI` / DirectDraw / DirectInput / DirectSound integration
- parser / AST / compiler helpers
- memory and allocation wrappers
- control-flow scars such as `JUMPOUT`
- unknown data and helper globals

Representative symbols from `build/clash95_unresolved.txt`:

- startup/runtime: `AST_AllocNode`, `AST_FreeNode`, `CRT_GetBootstrapThreadData`, `CRT_RegisterFinalizableObject`, `CSyncObject_Unlock`
- platform: `CreateWindowExA`, `GetMessageA`, `DispatchMessageA`, `DirectDrawCreate`, `DirectInputCreateA`, `DirectSoundCreate`
- media: `AVIFileInit`, `AVIFileOpenA`, `AVIStreamRead`, `AVIStreamRelease`
- compiler/runtime object model: `IO_OutWriteToken`, `IO_OutNewline`
- control-flow and unknowns: `JUMPOUT`, `unknown_libname_2`, `unknown_libname_5`, `unknown_libname_10`

The small `platform_unresolved.txt` set is mostly the expected host seam:

- `Platform_MainWindowProc`
- `calloc`, `free`, `memset`, `fprintf`, `gettimeofday`, `usleep`

The quarantine file still carries a broader runtime wrapper surface:

- filesystem and CRT wrappers such as `fopen`-style, `fread`, `fwrite`, `strcmp`, `strlen`, `strrchr`
- Windows-style process/thread helpers such as `CreateProcessA`, `CreateThread`, `WaitForSingleObject`, `ExitThread`
- WCpp helpers such as `Compat_WcppCtorArrayStorage1m` / `1s`

## Entry point chain

Canonical map evidence shows the original binary entry chain as:

- `start`
- `sub_486369`
- `_WinMain@16`

The current bootstrap chain is the recoverable host-side approximation:

- `main()` in `bootstrap_main.c`
- `App_WinMain()`
- `Bootstrap_RunRecoveredEarlyStartupPrelude()`
- `Bootstrap_RunRecoveredRuntimeAndRenderInit()`
- `Bootstrap_RunRecoveredGameEntry()`
- `Bootstrap_RunMessageLoop()`

The key point is that the bootstrap path is rooted in recovered behavior, not a dummy demo loop.

## Minimal honest plan for `clash95_cpp_regen`

1. Keep `clash95_recovered` green.
2. Keep the current bootstrap executable as the short-term entrypoint wedge.
3. Move the first stable class seams into `clash95_cpp_core`:
   - `DLXSpriteSet`
   - `CAviDecompressor`
   - `CSyncObject`
4. Classify the unresolved surface into:
   - true startup/runtime reconstruction
   - low-risk wrappers
   - SDL/platform seam work
   - quarantine-only stubs
   - unknowns that require new evidence
5. Keep `clash95_cpp_regen` pinned to the narrow startup harness until more of the raw runtime surface is proven safe to pull in.
6. Reduce `JUMPOUT` scars and the `_wcpp_*` runtime band only when the replacement is evidence-backed.

This is a staged executable-regeneration path, not a claim that the full native executable is already recovered.

## Live runtime blocker adjacent to the current link wedge

- The current executable problem is no longer primarily link-shaped.
- `clash95_bootstrap` and `clash95_cpp_regen` both stay green, while the last directly traced contained milestone remains the post-confirm save-replay entry that fails in the missing class/bload prelude.
- There are now two adjacent widening fronts:
  - the explicit broader contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - the retained startup-prelude slice now links through `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame`, and the next retained widening stays in the deeper `WorldMap_RunHumanTurnLoop` surface after the now-complete `Scenario_LoadMissionByIndex` switch
- Treat those as the next executable-regeneration blockers beside the current raw link surface. They are runtime/startup fidelity problems, not missing SDL shims.

## Latest retained runtime blocker update
- The retained startup-prelude slice now links through `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, `PlayGame`, and a direct `WorldMap_RunHumanTurnLoop` probe.
- The next retained widening stays in the deeper `WorldMap_RunHumanTurnLoop` surface after the now-complete `Scenario_LoadMissionByIndex` switch and after the repaired zero-init entry, `arama1` / `kon_por1` mission-success tail, zero-arg loop-entry helpers, held-key `DD_Pump` loops, queued-path AP compare, saved render-hook/resource-handle debug block, the repaired `WorldMap_HandleTopMenuBar` helper band, and the repaired `UnitStackSelection_HandleInput` helper band; the next local center is `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`.
- This remains a gameplay/session runtime-fidelity problem, not an SDL seam or raw-link inventory problem.
- `WorldMap_HandleTileHoverAndClick` is narrower now: its wrapper lane no longer forwards undefined coordinates, its lost-surface stack-selection path now preserves `UnitStack_ShowSelectionDialog(..., 1)`, its temple/building/self-move execute tails now use the zero-arg `UnitStack_ExecuteQueuedPath` shape from asm, and its own-stack merge/reselection lane now reloads resources with `Render_LoadResourceSprite_v2`.
- `WorldMap_HandleTileHoverAndClick` is narrower again: the own-stack merge/add-to-group lane and the visible enemy-stack attack lane now read the hovered stack id directly from `TILE_INDEX(v1, v78)` instead of carrying decompiler-only `v50` / `v58` / `v67` tile-offset ghosts.
- `WorldMap_HandleTileHoverAndClick` is narrower once more: its own-stack reselection branch no longer threads `v52` into `UnitStackSelection_ClearMask`, and `UnitStackSelection_ClearMask` itself now matches asm on its hardcoded `dword_526F78` clear.
- `WorldMap_HandleTileHoverAndClick` is narrower yet again: the enemy-building attack predicate and own-building approach branch now share the same hovered building id instead of re-reading raw tile offsets.
- `WorldMap_HandleTileHoverAndClick` is narrower again: `Building_GenerateApproachTrack` now anchors the selected stack from `a1`, and `Unit_AttackBuilding` now keeps that same selected stack index live through its opening sprite-draw and move-to-building prelude instead of relying on lost-register locals.
- The next live retained blocker inside `sub_4084A0` is therefore the deeper mid-body `Unit_AttackBuilding` garrison/combat-resolution lane, not the already-reduced wrapper, execute-tail, hovered stack-id, clear-mask, building-id read, and selected-stack-forwarding tranches.

## Latest front-end runtime blocker update
- The bootstrap executable now has one default route: `main()` builds the recovered command-line buffer from argv and always enters `App_WinMain`.
- Host-side bootstrap modes are gone. Old probe switches such as `--authentic-startup-prelude`, `--authentic-video-init`, `--authentic-menu-probe`, and `--platform-window-only` are no longer interpreted by the wrapper.
- The menu-probe env surface is collapsed to fixed behavior; the tracked runtime code only keeps SDL presented-frame dump diagnostic env reads.
- The retained log-file creation slice is now restored in the full route: `createLogFiles` matches the asm-observed create/truncate/close side effect for `clash.log` and `battle.log` and no longer depends on the malformed decompiler-local `sub_4762AE` corridor.
- CTest now validates the current full route with `clash95_full_route_smoke` instead of the removed menu-capture probe path; it checks that `clash95_bootstrap` stays alive under dummy SDL/audio and then performs external process-group shutdown.
- The remaining front-end blockers are after this full route: clean finite live-loop shutdown, the still-skipped DirectSound-era `CSS_Init` table, and the broader playable `App_WinMain` / `PlayGame` session milestone.

## Latest finite-route blocker update
- Lowercase `r` is now a finite recovered `App_WinMain` route:
  - `main()` still compacts argv into the recovered command-line buffer
  - `App_WinMain` enters the recovered early startup and runtime/render init prelude
  - command mode `r` skips `Bootstrap_RunRecoveredGameEntry`
  - shutdown runs and the process exits `0`
- The new `clash95_r_command_shutdown_smoke` CTest captures that route and passes for the current bootstrap binary; the same shell smoke also passes against `clash95_cpp_regen`.
- The active front-end runtime blocker has shifted:
  - the default no-arg route now exits early in the intro AVI/CD check, with the traced stack `App_RequestQuit -> Win_BeginModeChange -> Video_Avi_playIn -> UI_StartAnims -> PlayGame_Dispatch -> Bootstrap_RunRecoveredGameEntry -> App_WinMain -> main`
  - direct no-arg smoke prints `[platform_sdl] Clash: Clash CD not found!`
  - the next honest blocker is therefore intro AVI/CD/resource-path recovery under SDL, not link failure or finite shutdown
- `CSS_Init` is still deferred independently because the DirectSound-era table is not safe enough for x86-64 SDL execution yet.

## Latest default-route blocker update
- The default no-arg full route no longer exits at the intro AVI/CD availability check.
- `Win_BeginModeChange` now verifies direct loose AVI paths after the recovered resource query fails, so the local installed game data can satisfy `Video_Avi_playIn` without faking the boot path.
- The reached runtime blockers after that point were reduced in the live recovered path:
  - AVI wrapper argument recovery and partial-init cleanup guards
  - shared byte-offset `CAviDecompressor` object initialization, replacing duplicated pointer-scaled event-handle setup in the reached constructors
  - compact public event handles for recovered 32-bit `HANDLE` fields
  - SDL DirectDraw palette creation/attachment for 8bpp mode switches
  - first main-menu sprite/resource load and compact render-surface calls
  - pointer-width-safe widget table walking for copied stack-local menu records
  - deterministic asm-backed main-menu widget-table copy and wait-loop sentinel
  - compact render-surface slot-64 dispatch in `Render_UnlockBackbuffer`
- `ctest --test-dir build --output-on-failure` is green again, and `ctest --test-dir build --output-on-failure --repeat until-fail:3` also passes: `clash95_full_route_smoke` observes the no-arg bootstrap alive in the recovered main-menu loop, and `clash95_r_command_shutdown_smoke` still covers the finite lowercase `r` shutdown route.
- Remaining front-end blockers:
  - deeper menu/session interactions beyond passive main-menu liveness
  - clean finite default-route quit from the recovered game loop
  - the still-deferred `CSS_Init` DirectSound-era table
  - the broader playable-turn milestone

## Latest direct-game blocker update
- The direct `a` route now gets through the reached world-map redraw/control scars and remains covered by CTest liveness smokes for both `clash95_bootstrap` and `clash95_cpp_regen`.
- The current direct `a` frontier is no longer a link failure or immediate renderer crash:
  - the original branch tries to load `save\\10.dat` through `sub_44C400`
  - that file is absent in the local data set, so the loaded roster is empty
  - live sampling therefore stops in `Game_AdvanceToNextPlayerTurn` waiting for a nonzero `PLAYER_IS_ACTIVE` slot
- A small link quarantine remains inside the newly reified world-map action widget table:
  - the authentic building-button action is `sub_40A0E0`
  - enabling it today pulls unresolved building/treasure placement helpers into the executable link
  - the record is present, but its live callback is temporarily `WorldMap_DeferBuildingActionCallback`
- The next executable blockers are:
  - acquire or reconstruct the direct-route autosave/session initialization data path honestly
  - recover the `sub_40A0E0` building/treasure placement link surface
  - continue the `/A0` scenario-start route past the current liveness milestone toward finite/session-playability checks

## Latest direct-scenario blocker update
- The `/A0` scenario-start route is no longer blocked in the intro AVI/mode-switch surface.
- It now stays alive under dummy SDL/audio for both `clash95_bootstrap /A0` and `clash95_cpp_regen /A0` after reaching map load, player setup, unit creation, minimap creation, and vision propagation.
- The removed blockers were not raw-link gaps:
  - recovered command-branch AVI argument order
  - pointer-width and low32-buffer bugs in scenario/map setup
  - compact parser/evaluator/fact/multifield hazards in the reached rules setup lane
  - minimap color-table storage and fill-size reconstruction
  - compact 32-bit render-surface vtable reads in minimap tile drawing
- Remaining blockers:
  - the minimap frame sprite blit through `sub_402E80` is still deferred because that blitter has unreduced compact-vtable callsites
  - `/A0` liveness does not yet prove a clean finite shutdown, responsive UI, or a playable turn
  - direct `a` still has its separate absent-autosave/session-data frontier

## Latest direct-scenario unit-stack blocker update
- The direct `/A0` route no longer crashes in the reached unit-stack merge/delete corridor.
- Removed blockers:
  - army-fact assertion failure causing recursive `Rules_CreateArmyFact -> Rules_LinkArmyFact -> Rules_EnsureArmyFactForStack` reentry
  - `Unit_AddToGroup` using undefined source/target stack locals before `Unit_GetSquadCount`
  - `Rules_RetractArmyFact` and `Unit_Kill` using undefined stack locals before fact cleanup, diagnostic dumping, tile clearing, and minimap redraw
- These were runtime fidelity blockers in recovered C, not raw unresolved link symbols.
- Remaining blockers:
  - underlying rules/class setup still needs recovery so army fact assertion succeeds instead of returning null
  - `/A0` liveness is still external-timeout liveness, not clean finite shutdown or playable-turn proof
  - the `sub_402E80` minimap frame blit compact-vtable path remains deferred

## Latest direct-scenario coverage update
- The direct `/A0` route is now a formal CTest liveness surface for both executables:
  - `clash95_direct_a0_route_smoke`
  - `clash95_cpp_regen_direct_a0_route_smoke`
- This does not remove a new link blocker; it prevents regressions in the scenario-start corridor that now reaches map/player/unit/minimap setup plus the reached stack merge/delete path.
- The remaining direct-scenario blockers are unchanged: rules/class fact health, finite shutdown or playable-turn proof, and the deferred minimap frame blit.

## Latest direct-scenario new-turn blocker update
- The direct `/A0` route no longer hits the reached new-turn crashes in parser/fact queue coalescing, building population/plague, garrison morale recovery, prisoner castle placement, unit fatigue/morale, queen relationship processing, building technology scanning, or the recovered allocator free-list walker under gdb.
- This still does not remove a raw unresolved link symbol; it removes runtime fidelity blockers that appeared after the scenario-start route reached player-turn/new-turn work.
- The only wrapper-surface change is the low32 small-allocation arena needed after the route reached sprite/resource allocation pressure.
- Remaining blockers:
  - underlying rules/class setup still needs recovery so army fact assertion and downstream session state are healthy
  - `/A0` liveness is still timeout-based and not a clean finite shutdown, responsive UI, or playable-turn proof
  - the `sub_402E80` minimap frame blit compact-vtable path remains deferred

## Latest direct-scenario render companion blocker update
- The direct `/A0` route no longer stops at the reached `sub_473320` null/host-width DirectDraw companion-surface creation crash.
- This was not a raw unresolved link symbol; it was a recovered render-wrapper fidelity issue:
  - `sub_4041D0` was forwarding an undefined height local into the companion constructor
  - `sub_473320` was still using a raw decompiler vtable call with undefined locals instead of the existing SDL DirectDraw wrapper
  - mode-switch gaps can legitimately leave `dword_51D584` zero, so the wrapper now remains software-only instead of storing a partially constructed companion
- Remaining blockers:
  - clean SIGTERM/finite shutdown still exposes a separate teardown fault and needs its own recovery
  - rules/class fact health remains below the current liveness route
  - `/A0` is still liveness-only, not responsive UI or playable-turn proof
  - the `sub_402E80` minimap frame blit compact-vtable path remains deferred

## Latest direct-scenario all-AI turn blocker update
- The direct `/A0` route is now classified from code and GDB evidence as an all-AI/autoplay turn-advance route, not a human-turn route.
- This was not a raw unresolved link symbol; it was a recovered-flow clarification plus a reached decompiler-scar cleanup:
  - `Scenario_LoadAllAiMultiplayerMapAndInitView` seeds all five players active and all five human-controller flags clear before loading `multi%d.map`
  - `Game_AdvanceToNextPlayerTurn` now keeps the previous-player index, human flag, active mission, cache-count returns, and final `0x140 x 0xF0` present dimensions explicit instead of reading undefined locals
- Remaining blockers:
  - a human-turn milestone must come from a route that actually seeds a human-controlled player, not direct `/A0`
  - clean finite shutdown and SIGTERM teardown remain separate runtime frontiers
  - rules/class fact health and the deferred `sub_402E80` minimap frame blit remain below the current all-AI liveness milestone

## Latest `PlayGame` loop blocker update
- The central `PlayGame` setup/loop/teardown body no longer forwards the reached band of undefined decompiler locals through the direct `/A0` route.
- This was not a raw unresolved link symbol; it removes runtime fidelity hazards in the recovered C body every in-game route crosses:
  - non-human reveal, theme resource selection, current-player info loading, AI dispatch, and turn advance now use explicit operands
  - the `RedrawMainMap` hook window now saves/restores the previous render hook and resource handle explicitly
  - teardown calls now use the asm-backed resource handle `20`, zero placeholders for no-argument cleanup helpers, and `sub_472860(-1, 0, 0)`
- Remaining blockers:
  - `WorldMap_RunHumanTurnLoop` still needs a route with a real human-controlled player before deeper cleanup can be validated
  - direct `/A0` is still all-AI liveness only, not clean finite shutdown or playable-turn proof
  - rules/class fact health and the deferred `sub_402E80` minimap frame blit remain below this cleanup

## Latest minimap frame blocker update
- The specific `MiniMap_CreateSurface` frame-sprite gap is no longer deferred.
- This was a contained runtime fidelity blocker rather than a raw unresolved link symbol:
  - asm fetches `DLX_GetSpriteForChar(dword_5202BC, 4)` after allocating the minimap surface
  - asm draws it at `(0, 0)` with draw mode `1` and unclipped `-1` bounds through the surface draw-sprite slot
  - GDB confirms the reached frame sprite is a `214 x 213` format-0 stream, so the existing bounded format-0 software decoder can carry this call without invoking the unsafe generic compact ABI
- Remaining blockers:
  - the broad generic `sub_402E80` decoder is still not generally recovered for other sprite formats, masks, or clipped call shapes
  - `WorldMap_RunHumanTurnLoop` still needs a real human-controlled route before deeper cleanup can be validated
  - direct `/A0` is still all-AI liveness only, not clean finite shutdown or playable-turn proof
  - rules/class fact health remains below the current liveness milestone
