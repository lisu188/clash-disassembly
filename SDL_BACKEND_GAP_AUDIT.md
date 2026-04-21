# SDL backend gap audit

This note covers the current host seam used by the executable-regeneration track.

## Current seam reality

- `platform_sdl.h` already remaps legacy Win32-era handles onto SDL-shaped host types such as `HWND`, `HDC`, `HBITMAP`, and `HPALETTE`.
- `platform_sdl_runtime.c` already provides a narrow translated host layer for:
  - `CreateWindowExA`
  - `GetMessageA`
  - `PeekMessageA`
  - `DispatchMessageA`
  - `TranslateMessage`
  - `timeGetTime`
- The implementation is still intentionally Win32-shaped at the call boundary. It is not yet a body-level SDL-native platform rewrite.

## Latest executable note - 2026-04-13

- The current load-menu and post-confirm blockers still sit below SDL.
- The latest contained traces show:
  - the real post-confirm probe lane now needs `CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm` in addition to `CLASH95_MENU_PROBE_AUTO_CLICK=load`
  - with the current broader-rules bootstrap, the post-confirm save replay dies at `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, it dies earlier with `symbol-lookup-missing-table MAIN`
  - neither failure touches `platform_sdl_runtime.c`
- This is useful negative evidence:
  - the SDL seam is still good enough for the contained load-menu row draws, slot-strip selection, bottom-row confirm, post-confirm `WorldMap_Initialize`, and first save-replay entry
  - the active blocker is the missing class/bload startup prelude, not input, timing, window, or present behavior
- The retained startup-prelude slice rooted at `sub_451E46` is likewise still blocked by runtime/class/front-end unresolveds, not by SDL.
  - the local x87-heavy math/runtime band is now gone
  - retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` now link successfully without touching `platform_sdl_runtime.c`
  - the former `PlayGame_Dispatch` UI/data/runtime band is now reduced in recovered C
  - the direct retained `PlayGame_Dispatch` probe now links and stays alive under `timeout 1s`
  - the direct retained `PlayGame` probe now also links and stays alive under `timeout 1s`
  - the mission-loader `JUMPOUT` at `Scenario_LoadMissionByIndex` / `sub_460360` is also gone in the recovered menu-reachable cases, again without touching `platform_sdl_runtime.c`
  - the first `WorldMap_RunHumanTurnLoop` zero-init and `arama1` / `kon_por1` mission-success repairs also landed entirely in recovered C without touching `platform_sdl_runtime.c`
  - the old retained helper-name band `sub_40D330` / `sub_44C2A0` is now gone too, and the full menu-reachable 20-case `Scenario_LoadMissionByIndex` switch is covered in recovered C without touching `platform_sdl_runtime.c`; the next retained blocker is the deeper `WorldMap_RunHumanTurnLoop` gameplay/session surface after that switch, not SDL

## Stable host behavior already present

- message queue storage and dispatch
- synthetic window allocation
- `timeGetTime()` backed by `gettimeofday()`
- `Sleep()` backed by `usleep()`
- basic surface/DC object allocation and release

These are good enough for the existing `clash95_bootstrap` wedge and for the first `clash95_cpp_regen` target.

## Highest-value gaps

### 1. Window procedure is still supplied by recovered game code

- `platform_sdl_runtime.c` calls back into `Platform_MainWindowProc`.
- The SDL seam does not yet own input translation or higher-level message semantics.
- This is correct for now, but it means the host layer is still only a transporter for the recovered platform loop.

### 2. The queue remains message-loop compatibility, not SDL-native event recovery

- `GetMessageA`, `PeekMessageA`, `TranslateMessage`, and `DispatchMessageA` preserve Win32-era behavior.
- That keeps the current recovered code runnable, but it is still an emulation seam rather than a re-emitted platform layer.

### 3. Timing is host-backed but not semantically lifted

- `timeGetTime()` and `Sleep()` are already portable enough to keep the platform loop alive.
- Frame pacing, timer ownership, and scheduling still belong to the recovered runtime, not to a clean C++ platform subsystem yet.

### 4. Graphics handles are still compatibility placeholders

- `CreateCompatibleDC`, `DeleteDC`, `DeleteObject`, `CreateBitmap`, and related helpers keep the recovered rendering path compiling.
- They are not yet proof that the renderer is SDL-native or layout-clean.

## Immediate implication for `clash95_cpp_regen`

- Keep the public names `Platform_CreateMainWindow`, `Platform_MainWindowProc`, and `Platform_PumpMessagesAndBlitFrame`.
- Reuse the existing seam for the first executable target instead of inventing an SDL-only launcher.
- Treat future SDL work as host-backend tightening, not as a reason to relabel recovered game behavior prematurely.

## Next safe backend tasks

1. Keep message-loop behavior stable while the executable target is first linked.
2. Continue moving only host-only helpers into the seam.
3. Avoid pushing gameplay/runtime semantics into `platform_sdl_runtime.c`.
4. Revisit event translation only after the executable path is stable enough to compare runtime behavior.

## Latest retained non-SDL evidence
- The latest `WorldMap_RunHumanTurnLoop` call-shape repairs also landed entirely in recovered C without touching `platform_sdl_runtime.c`.
- The direct retained `WorldMap_RunHumanTurnLoop` probe now links and stays alive under `timeout 1s`.
- The next retained blocker remains below SDL inside the deeper `WorldMap_RunHumanTurnLoop` gameplay/session surface after the repaired call-shape band.
- The latest retained top-menu and split-panel helper repairs also stayed entirely in recovered C without touching `platform_sdl_runtime.c`.

## Latest direct-scenario non-SDL evidence
- The `/A0` scenario-start route now stays alive under dummy SDL/audio for both executable targets without changing `platform_sdl_runtime.c`.
- The active blockers were recovered-code and host-width issues:
  - direct command-branch AVI arguments
  - scenario player-state and map-load pointer width
  - rules parser/evaluator compact records
  - minimap color tables and compact render-surface dispatch
- This is negative evidence for the current SDL seam: the host window, timing, dummy audio, and message transport are good enough for the direct scenario-start liveness milestone.
- Remaining direct-scenario work should stay below SDL unless validation reaches a concrete input, window, present, or timing failure.

## Latest direct-scenario unit-stack non-SDL evidence
- The follow-on `/A0` crashes were also below SDL:
  - army-fact null assertion reentry
  - `Unit_AddToGroup` undefined register artifacts in source/target stack handling
  - `Rules_RetractArmyFact` and `Unit_Kill` undefined register artifacts in fact cleanup, stack diagnostics, and tile/minimap cleanup
- Repairing those recovered C functions makes both executable paths run until external timeout under dummy SDL/audio, without any `platform_sdl_runtime.c` change.
- The next SDL task remains evidence-driven: do not move gameplay stack merge/delete semantics into the backend seam.

## Latest direct-scenario CTest non-SDL evidence
- The new `/A0` liveness tests did not require SDL backend changes.
- `clash95_direct_a0_route_smoke` and `clash95_cpp_regen_direct_a0_route_smoke` use dummy SDL/audio with the existing message/timing/window seam and pass by observing liveness before external shutdown.
- Future SDL work should still wait for a concrete input, window, present, or timing failure; the current direct-scenario frontier is below SDL.

## Latest direct-scenario allocator/new-turn non-SDL evidence
- The new `/A0` crashes were again below SDL: parser/fact queue coalescing, building population/plague state, garrison morale delta handling, prisoner castle placement, unit fatigue/morale predicates, queen relationship timers, building technology scanning, and recovered allocator free-list traversal.
- `platform_sdl_runtime.c` was not changed.
- The one host-side adjustment was the low32 allocator arena in the compat layer, needed after the authentic route reached sprite/resource allocation pressure. That remains separate from SDL input, window, present, and timing behavior.
- Future SDL work should still be gated by a concrete backend failure; the current frontier is finite scenario/player-turn behavior below SDL.

## Latest SDL signal handling evidence
- A concrete SDL backend behavior did block finite external shutdown: SDL's default signal handlers can absorb WSL/POSIX `SIGTERM` into an `SDL_QUIT` event.
- The existing message queue can translate `SDL_QUIT` when the recovered code pumps messages, but direct `/A0` can remain in all-AI gameplay work long enough that plain `timeout` needed SIGKILL.
- `PlatformEnsureSdlVideo` now sets `SDL_HINT_NO_SIGNAL_HANDLERS` before `SDL_Init`, keeping signal termination at the host boundary instead of depending on gameplay code to pump SDL events.
- This is an SDL seam tightening only; it does not move gameplay semantics into the backend and does not prove recovered in-game quit cleanup.
