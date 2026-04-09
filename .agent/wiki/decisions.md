# Decisions

- Keep cache reuse conservative inside `Render_LoadResourceSprite_v4`.
  - Reason: repo-local `gfx\\cache\\...` files can exist even when the mounted-query layer cannot reopen them.
- Keep the `.pfn` palette load in the quarantine helper instead of broadening the SDL seam.
  - Reason: the original x86 contract keeps this entirely inside the text-resource/runtime helpers.
- Patch `sub_40BC00` in `clash95.c` directly instead of shadowing it from `compat/decomp_runtime_stubs.c`.
  - Reason: `clash95_bootstrap` links `clash95.c.o` directly, so a compat duplicate causes a multiple-definition link error.
- Keep the next contained frontier on slot-click/confirm and save-slot repaint, not on unrelated runtime wrappers.
  - Reason: the contained menu wedge is now beyond the row-resource and first row-draw helpers.
- Make the contained confirm probe click the save-slot strip before the bottom-row load button.
  - Reason: the authentic load-menu loop latches `dword_5441E0` and routes through `sub_44A110` from the in-strip click corridor, not from hover alone.
- Do not land a direct contained `sub_444490` call in the green bootstrap surface yet.
  - Reason: the experimental widening immediately reopens a deeper unresolved runtime/parser link band and would regress `clash95_bootstrap` and `clash95_cpp_regen`.
- Patch `sub_4163F0` in recovered C instead of tracing around it indefinitely.
  - Reason: the asm proves it is a short deterministic loop, and the decompiled body was using uninitialized indices on the live post-confirm path.
- Widen `sub_4443C0` / `sub_4443D0` to `char *` buffers in recovered C.
  - Reason: the asm passes a live destination buffer in `edx`, and the low32 `int` signature was truncating stack addresses on x86_64 during the authentic save-load path.
- Keep the next frontier on the post-save `PlayGame` handoff, not on `sub_444490`.
  - Reason: the contained authentic load-game lane now survives both `WorldMap_Initialize` and the `.dat` / `.fac` load and returns to `main-after-menu-probe`.
