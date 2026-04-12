# Executable link blockers

This note records the current executable-regeneration gap on the clean `codex/cpp-executable-regen` branch.

## Current build reality

- `clash95_recovered` still builds cleanly as the recovered C static library baseline.
- `clash95_bootstrap` already exists as a narrower executable harness around the same recovered sources.
- `clash95_cpp_core` now builds as a parallel conservative C++ class library.
- `clash95_cpp_regen` now links as a parallel executable by reusing the existing bootstrap wedge and adding the C++ core.
- A direct `gcc` link of `clash95.c`, `platform_sdl_runtime.c`, and `compat/decomp_runtime_stubs.c` does not yet produce a runnable executable.

## Latest authentic runtime frontier - 2026-04-12

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

## Latest startup-prelude narrowing - 2026-04-12

- The retained `CLIPS`/startup-prelude surface moved again this batch:
  - direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` still link successfully
  - the standalone retained `sub_451E46` probe still stays alive under `timeout 1s`
  - the first retained `PlayGame_Dispatch` UI/data/runtime band is now reduced in recovered C: `UI_CheckConfirmQuit`, `UI_CheckDialogAccepted`, the reached `unit_stats` byte lane, the queen departure-event tables/buffer slab, and the local `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars are no longer live retained blockers
- A direct-object retained probe for `sub_4996D0` still links successfully.
- The retained mission-loader surface moved again this batch:
  - `Scenario_LoadMissionByIndexAndPlay` now passes the real selector into `Scenario_LoadMissionByIndex`
  - `createUnit` and `createCastle` now match the original sentinel-terminated unit-list contract closely enough to transcribe real mission setup calls
  - the menu-reachable `sub_460360` cases now recovered in `clash95.c` are case `0` (`k_mapa1l.map`), case `1` (`k_mapa2l.map`), case `2` (`k_mapa3l.map`), case `3` (`k_mapa4j.map`), case `4` (`k_mapa5j.map`), case `5` (`k_mapa6j.map`), case `6` (`k_mapa7z.map`), case `7` (`k_mapa8z.map`), case `10` (`p_mapa1z.map`), case `11` (`p_mapa2z.map`), case `12` (`p_mapa3z.map`), case `13` (`p_mapa4l.map`), case `14` (`p_mapa5l.map`), case `15` (`p_mapa6l.map`), case `16` (`p_mapa7j.map`), and case `17` (`p_mapa8j.map`)
  - the first recovered cases now call the already-recovered local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly, so the old retained `sub_40D330` / `sub_44C2A0` helper-name gap is gone
- The next retained blocker is no longer the parser-export layer, the low-risk file/runtime wrapper band, the x87-heavy math band, the broader `PlayGame_Dispatch` UI/data/runtime scatter, the bare mission-loader `JUMPOUT`, the `sub_40D330` / `sub_44C2A0` helper gap, or `mapK2` / case `1`. `mapK3` / `case 2` is now materialized too, including its player-2 intelligence write, explicit `Treg Rock` post-castle garrison refresh, and post-initializer camera override, `mapK4` / `case 3` is now materialized too, including its four-player setup, `Ughuata` post-castle `BUILDING_RECORD(+18) = -1`, `BUILDING_RECORD(+438) = 300`, and its raw stack mutation bands, `mapK5` / `case 4` is now materialized too, including its exact `Totaweon` / `Hopenberg` setup, raw garrison/prisoner writes, and `Rules_LogAssignedCastleFact(..., 4)` tail, `mapK6` / `case 5` is now materialized too, including its localized name fork, mission-local player-runtime writes, `Defambrion` / `Katha Gha` / `Ghih Up` building-field mutations, raw 10-slot status loop, and `Rules_LogAssignedPlayerFact(3, 5)` tail, `mapK7` / `case 6` is now materialized too, including its Walter/Drebegen player setup, raw stack/status writes, `Rules_SyncArmyFactStrength` handoffs, prisoner/fund writes, and camera override, `mapK8` / `case 7` is now materialized too, including its four `Rules_RetractTreasureFact` calls, eight-castle lane, and raw slot-byte mutation loops, `mapK9` / `case 8` is now materialized too, including its player-0 queen relationship writes, the `Gordmouth` `BUILDING_RECORD(+438) -= 100` cut, and its raw slot-byte mutation bands, `mapK10` / `case 9` is now materialized too, including its five-player setup, the case-local `BUILDING_RECORD(+438)` writes, and the direct masked `BUILDING_RECORD(+444)` mutations, `mapP3` / `case 12` is now materialized too, including its `Raylin` / `Gaalaad` setup, the player-1 no-castle lane, the `Sarturia` `BUILDING_RECORD(+438) = 5000` write, and the post-init camera override back onto player `1`, `case 13` / `p_mapa4l.map` is now materialized too, including its `Raylin` / `Leryks X` / `Glazur` / `Sir John` setup, the single `Ungught` castle lane, the random per-slot byte loop, and the absence of post-castle building writes or a post-init camera override, `case 14` / `p_mapa5l.map` is now materialized too, including its `Raylin` / `Uraken` / `Wodar` setup, the `Weghetown` post-castle `BUILDING_RECORD(+430)` low-word clear, the `Timbran` forced-garrison and prisoner lane, the `Fraggmeon` / `Eufurhon` `BUILDING_RECORD(+438) += 200` boosts, and the final `Rules_LogAssignedCastleFact(..., 14)` tail, `case 15` / `p_mapa6l.map` is now materialized too, including its mission-local byte clear, the `Frederic` / `Sir James` / `Agordeh` player setup, the `Defambrion`, `Ghih Up`, and `Guluali` building-field writes, and the final `Rules_LogAssignedPlayerFact(4, 15)` tail, `case 16` / `p_mapa7j.map` is now materialized too, including its mission-local byte clear, the `Raylin` / `Kalev` / `Ianos` setup, the `Gwadat` `BUILDING_RECORD(+444)` masked write, the four raw slot-state mutation bands, and the post-init player-1 camera override without any `Rules_LogAssigned*` tail, and `case 17` / `p_mapa8j.map` is now materialized too, including its four `Rules_RetractTreasureFact` calls, the `Raylin` / `Lord Ruwe` / `McGregor` / `Crowley` setup, the `Dark Town` `BUILDING_RECORD(+438) -= 100` cut, the four raw slot-state mutation bands, and the absence of any post-init camera override or `Rules_LogAssigned*` tail. The next remaining mission-loader case tranche inside `Scenario_LoadMissionByIndex` now starts with case `18` / `p_mapa9j.map`.
- Additional retained reduction notes from the latest pass:
  - `UI_CheckConfirmQuit` and `UI_CheckDialogAccepted` are now rebound onto their already-recovered local bodies instead of standing as duplicate retained export holes
  - the `sub_451E46` probe is still green, and the direct retained `PlayGame_Dispatch` probe now links and stays alive under `timeout 1s`
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
- `Bootstrap_RunRecoveredStartupPrelude()`
- `Bootstrap_RunRecoveredRuntimeAndRenderInit()`
- `Bootstrap_RunRecoveredGameEntry()`
- `Bootstrap_RunMessageLoop()` or `Bootstrap_RunPlatformWindowLoop()`

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
  - the retained startup-prelude slice now links through `sub_451E46`, `sub_460490`, `UI_StartAnims`, and `PlayGame_Dispatch`, and the next retained widening stops in the remaining `Scenario_LoadMissionByIndex` cases led by case `18` / `p_mapa9j.map`
- Treat those as the next executable-regeneration blockers beside the current raw link surface. They are runtime/startup fidelity problems, not missing SDL shims.
