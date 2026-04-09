# Runtime Glue

- Active repaired glue on the current frontier:
  - `Render_LoadResourceSprite_v4` compat export
    - skips repo-local cache false positives unless the mounted-query layer can reopen them
    - loads companion `*.pfn` palettes and remaps into the live palette
  - `Render_LoadResourceSprite_v3` compat export
    - restored the missing non-newline cursor advance
  - `sub_40BC00` in `clash95.c`
    - restored the active-slot glyph step and render-device call contract
  - `sub_4163F0` in `clash95.c`
    - restored the finite asm-backed world-map-init seeding loop
  - `sub_4443C0` / `sub_4443D0` in `clash95.c`
    - widened the save-path builders to real `char *` buffers so `.dat` / `.fac` stack paths are no longer truncated
- Still quarantined / unresolved:
  - deeper `_wcpp_*` runtime families
  - thread/process helpers
  - broader loaded-session runtime reconstruction beyond the contained save-load wedge
  - the next honest frontier is the post-save `PlayGame` handoff rather than the just-cleared `.dat` / `.fac` load path
