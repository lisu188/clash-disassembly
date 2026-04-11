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

## Latest executable note - 2026-04-11

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
  - the mission-loader `JUMPOUT` at `Scenario_LoadMissionByIndex` / `sub_460360` is also gone in the recovered menu-reachable cases, again without touching `platform_sdl_runtime.c`
  - the old retained helper-name band `sub_40D330` / `sub_44C2A0` is now gone too, and `mapK2`, `mapK3`, `mapK4`, `mapK5`, `mapK6`, `mapK7`, and `mapK8` are recovered in-place; the next retained blocker is the remaining mission-case recovery itself, starting with `mapK9` / case `8`

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
