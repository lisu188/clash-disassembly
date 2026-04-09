# Agent Log

## 2026-04-09

- Reloaded the durable repo memory and corrected the stale assumption that the live frontier was still `gfx\\backgr1.s32`; the latest durable state was already inside the contained load-menu corridor.
- Reproduced the current widened row-resource crash and found the first failure in `DLXSpriteSet_Load("cache\\...")` after a repo-local cache false positive.
- Repaired the compat `Render_LoadResourceSprite_v4` cache gate so cache reuse only happens when the mounted-query layer can reopen the same file.
- Reproduced the next crash in `DLXSpriteSet_DrawText` and matched the original x86 contract: source font colors come from companion `*.pfn` assets, target colors come from the live menu palette.
- Added `Compat_LoadFontPaletteTable` to load `*.pfn` palettes through the mounted-query layer and feed the proper source palette into the text remap.
- Interrupted the first widened row-draw stall in gdb and confirmed `sub_40BD40` had the classic decompiler scar where non-newline characters never advanced the cursor.
- Repaired `Render_LoadResourceSprite_v3` in the quarantine seam with the asm-backed cursor advance.
- Reproduced the next crash in `sub_40BC00` and repaired the recovered C function to match the x86 active-slot record and glyph-step contract.
- Validated that the widened contained probe now loads `Render_LoadResourceSprite_v4(18/21)`, completes all ten row draws, survives the `back` exit, and also survives contained slot-hover selection with `selected_slot = 0`.
- Reworked the contained load-menu probe so a combined slot-and-confirm run clicks the save-slot strip first, which lets the authentic `dword_5441E0` / `sub_44A110` corridor fire on a real occupied save slot.
- Validated that the widened contained confirm probe now exits with `selected_slot = 0`, `confirm = 1`, and `screen = 5`.
- Tried to widen the bootstrap probe directly into `sub_444490`, confirmed that this reopens the deeper unresolved runtime/parser link band, and reverted that direct call to keep the bootstrap surface green.
- Reproduced the new post-confirm world-map-init stop and found a live recovered-C bug in `sub_4163F0`: the decompiler had left an uninitialized-index loop where the asm shows a finite 15-iteration RNG seeding pass.
- Repaired `sub_4163F0` to match the x86 loop and confirmed that the contained authentic load path now reaches `load-menu-post-confirm-load-save`.
- Took an escalated gdb backtrace on the new save-load crash and pinned it to `sub_4443C0 -> sprintf_` while formatting `save\\%d.dat`.
- Repaired `sub_4443C0` and `sub_4443D0` so the save-path builders take real `char *` buffers instead of truncating stack addresses to low 32-bit ints.
- Validated that the contained authentic `Load Game` lane now survives `WorldMap_Initialize`, survives the `.dat` / `.fac` load in `sub_444490`, reaches `load-menu-post-confirm-after-save`, and returns to `main-after-menu-probe`.
