# Executable link blockers

This note records the current executable-regeneration gap on the clean `codex/cpp-executable-regen` branch.

## Current build reality

- `clash95_recovered` still builds cleanly as the recovered C static library baseline.
- `clash95_bootstrap` already exists as a narrower executable harness around the same recovered sources.
- `clash95_cpp_core` now builds as a parallel conservative C++ class library.
- `clash95_cpp_regen` now links as a parallel executable by reusing the existing bootstrap wedge and adding the C++ core.
- A direct `gcc` link of `clash95.c`, `platform_sdl_runtime.c`, and `compat/decomp_runtime_stubs.c` does not yet produce a runnable executable.

## Latest authentic runtime frontier - 2026-04-09

- The live executable blocker is no longer the old load-menu row-resource preload crash or the first post-confirm `.dat` / `.fac` save-load crash.
- The contained SDL-backed executable now:
  - loads the authentic `Render_LoadResourceSprite_v4(18/21)` row text resources
  - completes all ten contained `sub_44A140` row draws
  - survives contained slot-hover selection with `selected_slot = 0` and `confirm = 0`
  - survives contained authentic slot-strip click plus bottom-row load confirm with `selected_slot = 0` and `confirm = 1`
  - survives contained post-confirm `WorldMap_Initialize`
  - survives contained `.dat` / `.fac` session-load in `sub_444490`
  - reaches `load-menu-post-confirm-after-save` and returns to `main-after-menu-probe`
- The next honest runtime blocker is now the post-save `PlayGame` handoff and the first loaded-session runtime fault beyond `sub_444490`.
- The remaining raw link/runtime surface still exists for the broader executable-regeneration track, but it is no longer the blocker for the contained post-confirm save-load wedge.

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
