---
name: regenerate-cpp-executable
description: Use this skill when the task is to preserve the recovered C baseline while building a parallel evidence-backed C++ executable regeneration path from clash95.c, clash95.asm, clash95.map, and the current runtime/platform seam.
---

- Work in two tracks at once: keep `clash95.c` and the current recovered build targets green, then add a parallel C++ executable path rather than replacing the C baseline.
- Ground startup, runtime, and class recovery in this evidence order: `clash95.asm` and `clash95.map`, then `clash95.c`, then `clash95.exe` / resource strings, then canonical repo artifacts and build probes.
- Treat `bootstrap_main.c` and the existing `clash95_bootstrap` target as the current executable foothold. Extend that path honestly before inventing a fresh entrypoint.
- Keep compatibility glue in `platform_sdl.h`, `platform_sdl_runtime.c`, and `compat/decomp_runtime_stubs.c`; do not hide recovered gameplay or compiler semantics there.
- Add and maintain the executable-regeneration sidecars when relevant:
  - `CPP_EXECUTABLE_REGEN_PROGRESS.md`
  - `EXECUTABLE_REGEN_PLAN.md`
  - `EXECUTABLE_LINK_BLOCKERS.md`
  - `LINK_SURFACE_AUDIT.csv`
  - `CPP_CLASS_CROSSWALK.csv`
  - `CPP_SUBSYSTEM_NOTES.md`
  - `SDL_BACKEND_GAP_AUDIT.md`
  - `RUNTIME_WRAPPER_STATUS.md`
  - `STRUCT_RECOVERY_NOTES.md`
- Prefer conservative C++ class surfaces for high-confidence seams such as `DLXSpriteSet`, `CAviDecompressor`, and `CSyncObject`. Use wrapper/layout/view/controller naming when ownership or ABI is still ambiguous.
- After each batch, rebuild the recovered C target, rebuild any new C++ targets, rerun unresolved-symbol audits, and record what moved the repo closer to a real executable instead of a rename-only cleanup.
