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

## Latest executable note - 2026-04-09

- The current load-menu and post-confirm blockers still sit below SDL.
- The latest contained traces show:
  - with the current broader-rules bootstrap, the post-confirm save replay dies at `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, it dies earlier with `symbol-lookup-missing-table MAIN`
  - neither failure touches `platform_sdl_runtime.c`
- This is useful negative evidence:
  - the SDL seam is still good enough for the contained load-menu row draws, slot-strip selection, bottom-row confirm, post-confirm `WorldMap_Initialize`, and first save-replay entry
  - the active blocker is the missing class/bload startup prelude, not input, timing, window, or present behavior
- The retained startup-prelude slice rooted at `sub_451E46` is likewise still blocked by runtime/class/parser unresolveds, not by SDL.
  - after the latest retained helper pass, that non-SDL blocker list is now led by `unk_508D50`, `sub_496643`, retained `.fn_init` at `sub_49A0E0`, `ftime_`, `system_`, and `JUMPOUT`, not by `unknown_libname_7`, `unknown_libname_8`, or `AST_FreeNode`

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
