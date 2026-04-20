# Runtime wrapper status

This file classifies the current runtime/quarantine surface for executable regeneration.

## Status classes

- `forwarding_wrapper`: low-risk adapter around host libc or already-isolated compatibility behavior
- `behavioral_stub`: placeholder behavior that keeps the code moving but does not yet prove original semantics
- `recovered_impl`: good-enough recovered implementation rooted in code evidence
- `unknown_runtime`: still needs tighter binary corroboration before it should move out of quarantine

## Current classification

| Symbol or family | Status | Evidence | Notes |
|---|---|---|---|
| `Compat_WcppCtorArrayStorage1m` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c` callers | Already isolated behind a named compatibility helper rather than pretending to be the original runtime entry. |
| `Compat_WcppCtorArrayStorage1s` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c` callers | Same family as above; safe to keep quarantined until the deeper WCpp startup band is re-emitted. |
| `CRT_GetBootstrapThreadData` | `behavioral_stub` | `compat/decomp_runtime_stubs.c`, `bootstrap_main.c`, `clash95.c` weak accessor | Good enough for the bootstrap wedge, not yet a faithful final CRT thread-data recovery. |
| `CRT_RegisterFinalizableObject` | `behavioral_stub` | `compat/decomp_runtime_stubs.c`, broad `clash95.c` call surface | Used widely enough that it needs a documented quarantine label rather than a semantic upgrade. |
| `unknown_libname_4` | `recovered_impl` | `clash95.asm` use under `sub_47CBF0`, `clash95.c` | Recovered as the allocator-failure callback swap used by the binary-loader retry helper. |
| `unknown_libname_7` / `unknown_libname_8` | `recovered_impl` | `clash95.exe` objdump at `0x47E7B0` / `0x48AC80`, `clash95.map`, `clash95.c` | Exact setter-swaps for `dword_51A1EC` / `dword_51A928`; these are runtime helpers, not startup `.fn_init` bodies. |
| `AST_FreeNode` | `recovered_impl` | `clash95.asm:303859`, `clash95.c` | Exact recursive free-list unwind recovered in-tree; no longer a retained startup blocker. |
| `mblen_` / `mblen__0` / `sub_4D88F0` | `recovered_impl` | `clash95.exe` objdump, `clash95.c` callers | Narrow object-pattern trampolines and token-table registration slice recovered directly from the binary. |
| `sub_496643` | `recovered_impl` | `clash95.exe` objdump at `0x496643`, `clash95.map`, `compat/decomp_runtime_stubs.c` | Kept quarantined in the compat seam, but the signal-table update and ctrl-handler gating now match the original helper closely enough to remove it from the retained startup-prelude blocker list. |
| `ftime_` / `system_` | `forwarding_wrapper` | `clash95.exe` objdump at `0x47D360` / `0x47D3D0`, `clash95.c`, `compat/decomp_runtime_stubs.c` | The callsites are now reconstructed with the correct arguments; the host-backed implementations remain deliberately quarantined as CRT wrappers. |
| `fread_` / `fwrite_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c` | Host libc forwarding wrappers around the current file-handle translation layer. |
| `MoveFileA` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c:130558`, retained `sub_451E46` probe | Narrow host wrapper over translated WSL paths plus `rename()`; intentionally quarantined as compatibility glue rather than gameplay semantics. |
| `sscanf_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.asm` callsites at `0x459272`, `0x4720F8`, `0x4A5657` | Host `vsscanf` bridge matching the currently reached text-parse callsites. |
| `fgets_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.asm` callsites at `0x459265`, `0x4A50A0`, `0x4A545A` | Narrow registered-stream line reader; the active recovered callsites now pass the real buffer/size/stream arguments. |
| `rand_` / `srand_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, retained `PlayGame_Dispatch` link surface | Narrow host-libc RNG bridges kept in the compat seam; good enough to remove the current retained link hole without claiming original CRT fidelity. |
| `strlwr_` / `memmove_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, retained `PlayGame_Dispatch` link surface | Simple libc-backed wrappers kept quarantined as runtime glue rather than pulled into recovered gameplay code. |
| `unknown_libname_2` | `recovered_impl` | `clash95.exe`/asm at `0x48523F`, `compat/decomp_runtime_stubs.c`, `clash95.c` callsites | Exact signed decimal parser recovered from the binary; no longer an `atoi` placeholder. |
| filesystem/string CRT wrappers (`strcmp`, `strlen`, `strrchr`, etc.) | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, unresolved audit, lowercase `r` startup/shutdown route | Broad but understandable compatibility wrappers; `strcmp_` now uses a cached readable-range check invalidated on low32 alloc/free so malformed recovered pointers do not crash startup comparisons. |
| `Render_LoadResourceSprite_v4` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:18215-18324`, live contained row-draw probes | Now matches the cache-query gate, companion `.pfn` palette load, and recolor contract closely enough to carry the authentic load-menu row-resource lane. |
| `Render_LoadResourceSprite_v3` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:17529-17576`, gdb SIGINT in contained row draw | The missing non-newline cursor advance was restored from asm, removing the row-draw hang. |
| `CSyncObject_Unlock` | `recovered_impl` | `src_cpp/csync_object.cpp`, `clash95.c` retained probes | Published through the conservative C++ seam as the original lock ABI rather than a new compat stub. |
| `_wcpp_4_static_init__` | `behavioral_stub` | `compat/decomp_runtime_stubs.c`, retained `PlayGame_Dispatch` link surface | One-byte guard implementation kept in the compat seam to remove the current retained link hole; still not proof of the original Watcom static-init runtime. |
| `CreateProcessA` / `CreateThread` / `WaitForSingleObject` family | `unknown_runtime` | unresolved audit, `clash95.c` thread/process call sites | These are deeper runtime/process helpers and should not be silently normalized into the SDL seam. |
| `_wcpp_4_copy_array__` | `unknown_runtime` | raw link failures, `clash95.map`, `clash95.c` | Still part of the true startup/runtime reconstruction frontier. |
| `JUMPOUT` sites | `unknown_runtime` | `clash95.c` control-flow scars | These remain explicit recovery blockers, not wrappers. |

## What moved this batch

- The wrapper surface is now explicit in the executable-regeneration docs.
- The first C++ executable target is being built around the current bootstrap wedge instead of pretending the deeper WCpp/runtime layer is already solved.
- The text-resource/runtime quarantine layer still carries the contained pre-confirm load-menu wedge cleanly through row-resource load, row draws, slot-strip selection, and bottom-row confirm.
- The latest guarded traces show the next blocker is still below the quarantine seam:
  - the real post-confirm probe lane now needs `CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm`; the older duplicate `CLASH95_MENU_PROBE_AUTO_CLICK=load` command shape was stale
  - with the current broader-rules bootstrap, the post-confirm save replay reaches `parse-make-instance-before-class-lookup` and then dies because `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, it dies earlier on `symbol-lookup-missing-table MAIN`
  - the live evidence still points at missing startup-prelude class/bload recovery, not an SDL or wrapper seam change
- The retained executable-regeneration surface was also reduced without changing wrapper policy:
  - the latest retained pass stayed in recovered C: `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit and no longer forwards decompiler garbage into `PlayGame`
  - the `PlayGame` prologue now restores the asm-backed `backgr1.s32` / `backgr2.s32` / `backgr3.s32` and `treemas1.s32` / `treemas2.s32` / `treemas3.s32` loads, and its first player scan no longer depends on uninitialized counters
  - `WorldMap_RunHumanTurnLoop` now restores the asm-backed zero-init entry flags and the `sub_4623C0("arama1", "kon_por1")` mission-success tail in recovered C
  - the direct retained `PlayGame` probe now links and stays alive under `timeout 1s`, so the first retained gameplay/session blocker is now explicit inside the deeper `WorldMap_RunHumanTurnLoop` surface rather than a wrapper gap
  - the exact retained data/helper slice `aJ_0`, `unknown_libname_13`, `ismbdprint_`, `sub_4B6DD0`, and `sub_4BDD40` now exists in recovered C
  - the exported parser names `Lexer_ParseSlotConstraint`, `Lexer_ParseFieldSpec`, `Lexer_ValidateMessageHandler`, `Lexer_ParseDefglobal`, `Lexer_ParseRuleRHS`, `Lexer_ParseDeclareOptions`, `Lexer_EmitSlotBinding`, `Lexer_BuildSlotNode`, and `Lexer_FindSymbolIndex` are now rebound onto their already-recovered bodies
  - the low-risk file/runtime wrapper band (`unknown_libname_2`, `MoveFileA`, `sscanf_`, `fgets_`) remains settled
  - the retained x87-heavy rules math band was recovered in `clash95.c` directly, not in the wrapper seam
  - retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` now link cleanly
  - the early retained `PlayGame_Dispatch` alias/data band was then reduced in `clash95.c` directly: front-end cursor/overlay descriptor records, the first world-map/UI export aliases, the unit-slot and placement helpers, the garrison/UI aliases, the battle/port/queen debug string slab, and the port reinforcement tables are all now local recovered data/bodies rather than live retained blockers
  - the compat seam also now carries the narrow `rand_`, `srand_`, `strlwr_`, `memmove_`, and `_wcpp_4_static_init__` bridges that were already in flight on this branch, which is why those names are no longer present in the retained `PlayGame_Dispatch` probe
  - the next retained reduction pass stayed in recovered C as well: `UI_CheckConfirmQuit` and `UI_CheckDialogAccepted` are now rebound onto their local bodies, the queen departure-event slab is materialized locally, and the remaining `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0` `JUMPOUT` scars were repaired in place
  - the mission-loader front was then reduced in recovered C too:
    - `createUnit` and `createCastle` now use real varargs so the original sentinel-terminated unit lists no longer depend on x86 stack accidents
    - `Scenario_LoadMissionByIndexAndPlay` now threads the selector into `Scenario_LoadMissionByIndex`
    - the menu-reachable mission-loader cases (`0`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `10`, `11`, `12`, `13`, and `14`) are materialized directly from asm
    - the first recovered cases now call the existing recovered helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly, so the old retained `sub_40D330` / `sub_44C2A0` helper-name gap is gone
    - `mapK2` / case `1` also preserves its case-local post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff and the manual camera override after `Game_InitPlayerViewState`
    - `mapK3` / case `2` now also preserves its case-local player-2 intelligence write, the `Treg Rock` post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff, and the same manual camera override after `Game_InitPlayerViewState`
    - `mapK4` / case `3` now also preserves its `Ughuata` post-castle `BUILDING_RECORD(castle_index) + 18 = -1`, `BUILDING_RECORD(castle_index) + 438 = 300`, and its three case-local raw stack/status mutation bands in recovered C instead of wrapper glue
    - `mapK8` / case `7` now also preserves its four `Rules_RetractTreasureFact` calls, its `Alan` / `Uraken` / `Wodar` / `Richard V` setup, the eight-castle lane, and its raw slot-byte mutation loops in recovered C instead of wrapper glue
    - `mapK9` / case `8` now also preserves its player-0 queen relationship writes, its `Alan` / `Sir James` / `Ruryk` / `Riludius` setup, the `Totaweon` / `Gordmouth` / `Timbran` / `Ghettan` / `Hopenberg` / `Katha Gha` / `Werneom` castle lane, the `Gordmouth` `BUILDING_RECORD(+438) -= 100` cut, the three raw slot-byte OR loops, and the two direct `& 0xFC | 2` slot-byte rewrites in recovered C instead of wrapper glue
    - `mapK10` / case `9` now also preserves its five-player `Alan` / `Twogor` / `Drebegen` / `Mieszko` / `Chester` setup, the `Gorendberg` / `Timbran` / `Ghettan` / `Bhua Rock` / `Katha Gha` / `Stormus` / `Guluali` castle lane, the case-local `BUILDING_RECORD(+438)` cuts/assignments/addition, and the direct `BUILDING_RECORD(+444)` masked writes in recovered C instead of wrapper glue
    - `mapP3` / case `12` now also preserves its `Raylin` / `Gaalaad` setup, the player-1 human/minimap/religion writes, the player-1 no-castle unit lane, the `Sarturia` `BUILDING_RECORD(+438) = 5000` write, and the post-`Game_InitPlayerViewState` camera override back onto player `1` in recovered C instead of wrapper glue
    - case `13` / `p_mapa4l.map` now also preserves its `Raylin` / `Leryks X` / `Glazur` / `Sir John` setup, the single `Ungught` castle lane, the random per-slot `Rng_RandRange(5, 20)` loop on the stack at `TILE_INDEX(25, 28)`, and the absence of post-castle building writes or a post-init camera override in recovered C instead of wrapper glue
    - case `14` / `p_mapa5l.map` now also preserves its `Raylin` / `Uraken` / `Wodar` setup, the `Weghetown` post-castle `BUILDING_RECORD(+430)` low-word clear, the `Timbran` forced-garrison and prisoner lane, the `Fraggmeon` / `Eufurhon` `BUILDING_RECORD(+438) += 200` boosts, and the final `Rules_LogAssignedCastleFact(..., 14)` tail in recovered C instead of wrapper glue
    - case `15` / `p_mapa6l.map` now also preserves its mission-local byte clear, the four-player `Raylin` / `Frederic` / `Sir James` / `Agordeh` setup, the player-4 intelligence write, the `Defambrion` `BUILDING_RECORD(+438) += 200` boost, the `Ghih Up` `BUILDING_RECORD(+438) = 1000` and `BUILDING_RECORD(+18) = -1` writes, the `Guluali` `BUILDING_RECORD(+438) = 2000` write, and the final `Rules_LogAssignedPlayerFact(4, 15)` tail in recovered C instead of wrapper glue
    - case `16` / `p_mapa7j.map` now also preserves its mission-local byte clear, the three-player `Raylin` / `Kalev` / `Ianos` setup, the `Gwadat` `BUILDING_RECORD(+444)` masked write, the four raw slot-state mutation bands, the post-`Game_InitPlayerViewState` player-1 camera override, and the absence of any `Rules_LogAssigned*` tail in recovered C instead of wrapper glue
    - case `17` / `p_mapa8j.map` now also preserves its mission-local byte clear, the four `Rules_RetractTreasureFact` calls, the four-player `Raylin` / `Lord Ruwe` / `McGregor` / `Crowley` setup, the `Dark Town` `BUILDING_RECORD(+438) -= 100` cut, the four raw slot-state mutation bands, and the absence of any post-`Game_InitPlayerViewState` camera override or `Rules_LogAssigned*` tail in recovered C instead of wrapper glue
    - case `18` / `p_mapa9j.map` now also preserves its five-player `Raylin` / `Tubius` / `Lord Gorio` / `McDan` / `Drebegen` setup, the `Stone Bell` `BUILDING_RECORD(+438) -= 100` cut, the `Fhur Tao` `BUILDING_RECORD(+438) += 200` boost, the direct raw slot-state writes on the `+28` lane, and the absence of any post-`Game_InitPlayerViewState` camera override or `Rules_LogAssigned*` tail in recovered C instead of wrapper glue
    - case `19` / `p_map10z.map` was already present and is now corroborated against asm, so the full 20-case mission-loader switch remains recovered C rather than wrapper glue
  - the next retained executable-regeneration blocker is now the deeper gameplay/session surface inside `WorldMap_RunHumanTurnLoop` after the repaired entry/tail slice, not a runtime-wrapper, parser-export, SDL, or C++ seam problem

## What should not move yet

- `_wcpp_*` startup helpers
- thread/process runtime helpers
- control-flow scars
- the broader gameplay/session surface beyond the now-covered 20-case `Scenario_LoadMissionByIndex` / `sub_460360` switch
- the parser/output/runtime helpers newly exposed by a direct `sub_444490` pull (`Lexer_OutputFieldRange`, `IO_OutWriteToken`, `IO_OutNewline`, `Module_AllocList`, `strtod_`)
- any helper whose only current proof is “the code links if we stub it”

## Latest retained runtime note
- No new compat wrappers were added in the latest human-turn-loop batch.
- The latest retained widening stayed in recovered C: `WorldMap_RunHumanTurnLoop` now restores the zero-arg loop-entry helper lane, the held-key `DD_Pump` loops, the queued-path AP compare, and the saved render-hook/resource-handle debug block.
- The direct retained `WorldMap_RunHumanTurnLoop` probe now links and stays alive under `timeout 1s`.
- The next retained executable-regeneration blocker is still the deeper gameplay/session surface inside `WorldMap_RunHumanTurnLoop`, not a wrapper, SDL, or `src_cpp` seam problem.
- The latest retained widening also stayed in recovered C: `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` now restore their asm-backed helper bands without adding new compat wrappers.

## Latest finite shutdown note
- The lowercase `r` startup/shutdown route required no new speculative runtime stubs.
- The reached wrapper changes are containment fixes:
  - `strcmp_` now validates candidate low32 strings against cached readable host ranges instead of blindly dereferencing malformed recovered pointers.
  - recovered compact software-surface destructors are invoked through an explicit 32-bit vtable helper.
  - native SDL DirectDraw-compat COM methods are invoked through an explicit native pointer-size helper.
- The next default-route blocker is outside those wrappers: the no-arg route exits through the intro AVI/CD check before the old full-route liveness smoke can pass.

## Latest default-route liveness note
- The default route no longer needs a new host probe or fake loop to pass liveness.
- Wrapper/seam changes in this batch stayed narrow:
  - event `HANDLE`s created by `CreateEventA` are now compact public tokens backed by a private registry, so recovered 32-bit event fields can be waited, pulsed, and closed safely on the 64-bit host
  - `Compat_DirectDraw_CreatePalette` exposes the existing SDL DirectDraw palette implementation through the same low32 handle style used by the recovered render context
- The remaining fixes stayed in recovered C rather than the wrapper seam:
  - AVI entrypoint argument recovery
  - AVI constructor initialization through the shared byte-offset `sub_464CE0` path
  - main-menu widget table copy/walk repair
  - compact render-surface slot dispatch
  - the main-menu wait-loop sentinel
- The next runtime-wrapper candidate is still `CSS_Init` / DirectSound-era device table recovery, but it remains deferred until the original table semantics are safe enough for the SDL runtime seam.

## Latest direct-game route note
- No new broad compat wrapper was added for the direct `a` route.
- The reached fixes stayed in recovered C:
  - direct-game startup now uses the original `0x10` resource context carried in BL
  - the building sprite cache is represented as one recovered 650-byte slab instead of relying on adjacent weak globals
  - the reached `Render_DrawSprite` compact-vtable dispatch is replaced with an asm-backed call sequence into the existing recovered format-0 linear sprite decoder
- The next runtime-wrapper-adjacent hazard is narrower and concrete: `sub_416850` still contains compact render-surface vtable calls that combine adjacent 32-bit entries on the 64-bit host when the direct game route reaches visible-tile rendering.

## Latest direct-game liveness note
- No SDL or broad compat wrapper was added for the latest direct `a` route step.
- The reached `sub_416850` hidden-tile fill is handled in recovered C by writing the original solid rectangle into the resolved linear software surface.
- This removes the first visible-tile compact-vtable crash and makes direct `a` route liveness testable for both `clash95_bootstrap` and `clash95_cpp_regen`.
- Remaining compact render callsites in `sub_416850` stay deferred until validation reaches them.

## Latest direct-game control-path note
- No new broad runtime wrapper or SDL shim was added for the latest direct `a` route step.
- The active changes stayed in recovered C:
  - direct tile redraw and fade loops now advance their asm-backed counters
  - the world-map action-button sprite/table path is recovered as packed 0x35-byte records
  - the reached widget draw helper reads original low32 fields explicitly instead of relying on host pointer width
  - turn advance now checks the recovered player-active slot rather than a double-applied player-data offset
- The only deliberate containment is the world-map building button action: record 4 is present, but its callback is temporarily routed to `WorldMap_DeferBuildingActionCallback` because the authentic `sub_40A0E0` callback still pulls unresolved building/treasure-placement symbols into the current executable surface.
- `CSS_Init` and the intro AVI mode-switch surface remain separate wrapper/runtime frontiers.

## Latest direct-scenario note
- No broad runtime wrapper, SDL shim, or host-side scenario mode was added for the `/A0` route.
- The active fixes stayed in recovered C and the existing bootstrap entry:
  - logo AVI argument recovery in the recovered command branch
  - pointer-width and low32-buffer repairs in player-state and map-load setup
  - compact parser/evaluator/fact/multifield repairs in the reached rules setup lane
  - asm-backed minimap color-table allocation/fill ranges
  - direct bounded software-surface writes for the reached minimap tile draw path
- The remaining containment is explicit and narrow: `MiniMap_CreateSurface` still defers the minimap frame sprite blit because the authentic `sub_402E80` blitter still contains deeper compact-vtable scars.
- The direct `/A0` route is now a timeout liveness route for both executable targets, not a wrapper success or a proved playable turn.

## Latest direct-scenario unit-stack note
- No broad runtime wrapper or SDL shim was added for the reached `/A0` unit-stack crashes.
- The active fixes stayed in recovered C:
  - a null army-fact assertion no longer re-enters fact creation recursively through `Rules_LinkArmyFact`
  - `Unit_AddToGroup` no longer forwards undefined source/target/count/copy-length locals into stack diagnostics and slot merging
  - `Rules_RetractArmyFact` and `Unit_Kill` no longer forward undefined locals into fact cleanup, stack diagnostics, tile clearing, or minimap redraw
- This reinforces the current runtime-wrapper boundary: the SDL and compat seams are sufficient for this milestone, while the remaining failures are recovered gameplay/rules/session fidelity below the wrapper layer.

## Latest direct-scenario CTest note
- No wrapper change was needed to add direct `/A0` regression coverage.
- `tests/verify_direct_a0_route_smoke.sh` starts the current executable under dummy SDL/audio and checks liveness/crash behavior from the outside, matching the already-established direct `a` smoke pattern.
- The test formalizes the current wrapper boundary: the host seam can carry this route far enough for liveness, while the next blockers remain in recovered rules/session code.

## Latest direct-scenario allocator/new-turn note
- One narrow compat-wrapper change was needed for the latest direct `/A0` step: `CompatAllocLow32` now serves small requests from process-lifetime low32 arenas before falling back to per-allocation low32 mappings.
- The allocator change addresses reached sprite/resource allocation pressure after recovered C new-turn crashes were removed; it is not a gameplay shortcut or a scenario harness.
- The follow-on free-list crash stayed in recovered C: `sub_472860` now reads the original 32-bit low-address free-list links from `dword_54DBA8` instead of reading host-width pointers out of the table.
- The remaining new-turn fixes stayed below the wrapper layer in recovered C. SDL/window/audio handling did not need a change for this milestone.

## Latest direct-scenario render companion note
- No new broad runtime wrapper or SDL shim was added for the latest direct `/A0` step.
- The reached DirectDraw companion-surface creation now reuses the existing `Compat_DirectDraw_CreateSurface` wrapper instead of calling through a raw recovered vtable from `sub_473320`.
- The recovered C path now treats a missing `dword_51D584` render context as a software-only wrapper state during mode-switch gaps, avoiding a dead companion handle while preserving the existing SDL DirectDraw seam.
- The remaining teardown fault observed under SIGTERM is separate from route liveness and remains a clean-shutdown/runtime frontier, not a new SDL capability requirement.
