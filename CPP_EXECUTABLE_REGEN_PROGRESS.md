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

## Latest runtime update - 2026-04-09

- `clash95_recovered`, `clash95_bootstrap`, and `clash95_cpp_regen` are still green together after the latest loader/runtime repair pass.
- The durable memory had drifted behind the live tree:
  - the stable contained runtime milestone is still `load-menu-post-confirm-after-save`
  - the current broader contained probe now reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - the retained broader startup-prelude executable-regeneration slice is no longer blocked on the local bload header/data or allocator-callback gaps beneath `sub_47C850`
- The bootstrap/reference executable no longer stalls or crashes in the contained load-menu row-resource band or the first post-confirm save-load band:
  - repo-local `gfx\\cache\\...` false positives are filtered through the mounted-query layer before reuse
  - companion `*.pfn` font palettes are now loaded for `Render_LoadResourceSprite_v4(18/21)`
  - the first row-draw helper scars in `Render_LoadResourceSprite_v3`, `sub_40BC00`, and `sub_40BD40` are repaired closely enough for contained submenu row draws
  - `sub_4163F0` now matches the finite asm loop in `WorldMap_Initialize`
  - `sub_4443C0` / `sub_4443D0` no longer truncate stack buffers while formatting `save\\%d.dat` / `save\\%d.fac`
  - `unk_50293C` plus the adjacent `bload` loader strings are now materialized in `clash95.c`
  - `unknown_libname_4` is now recovered as the allocator callback swap beneath `sub_47CBF0`
  - `CSyncObject_Unlock` is now exported through `src_cpp/csync_object.cpp`
- The highest contained runtime milestone is now:
  - authentic load-menu row resources load
  - all ten `sub_44A140` row draws complete
  - contained slot-hover selection exits with `selected_slot = 0`, `confirm = 0`, and `screen = 5`
  - contained authentic slot-strip click plus bottom-row load confirm exits with `selected_slot = 0`, `confirm = 1`, and `screen = 5`
  - contained post-confirm `WorldMap_Initialize` returns
  - contained `.dat` / `.fac` session-load in `sub_444490` returns
  - the probe reaches `load-menu-post-confirm-after-save` and returns to `main-after-menu-probe`
- The explicit broader contained probe is now characterized as:
  - `load-menu-post-confirm-rules-slab-init`
  - `load-menu-post-confirm-rules-index-init`
  - `load-menu-post-confirm-parser-bootstrap`
  - `load-menu-post-confirm-load-save`
  - `parse-make-instance-before-class-lookup`
  - then a crash on `oddzial`
- The retained broader startup-prelude executable-regeneration slice also moved this batch:
  - a direct-object retained probe for `Rules_ShowBanner_StrategicClash` now links successfully
  - the archive-backed retained probe for `Rules_ShowBanner_StrategicClash` now links successfully too
  - the next blocker is the wider `sub_451E46` unresolved set (`unk_508D50`, `unknown_libname_7`, `unknown_libname_8`, `sub_496643`, `ftime_`, `system_`, `dbl_502FDC`, `JUMPOUT`, `AST_FreeNode`, and parser helpers)
- The next executable-regeneration frontier is split, not singular:
  - keep the stable contained lane green and eventually continue toward the post-save `PlayGame` handoff
  - separately continue the broader authentic startup-prelude slice `sub_451E46 -> sub_47D0E0 -> sub_47C850`
  - do not treat `Rules_ShowBanner_StrategicClash` or bare `sub_499990` as a local fix for the contained post-save `oddzial` miss

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
