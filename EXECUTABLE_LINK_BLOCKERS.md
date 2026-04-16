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
- The remaining front-end blockers are after this full route: clean finite live-loop shutdown, the still-skipped DirectSound-era `CSS_Init` table, and the broader playable `App_WinMain` / `PlayGame` session milestone.
