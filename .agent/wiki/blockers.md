# Current Blockers

- The contained authentic `Load Game` lane is still green through the pre-confirm slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state now dies at a precisely identified startup-prelude gap:
  - the explicit broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` still fails earlier on `symbol-lookup-missing-table MAIN`
- The retained broader startup-prelude executable-regeneration slice is still blocked separately:
  - `sub_451E46` now narrows past the local bload header/data, allocator-callback, `dbl_502FDC`, `unknown_libname_7`, `unknown_libname_8`, `AST_FreeNode`, `mblen_`, `mblen__0`, and `sub_4D88F0`, but it still fails on the wider unresolved runtime band led by `unk_508D50`, `sub_496643`, retained `.fn_init` at `sub_49A0E0`, `ftime_`, `system_`, `JUMPOUT`, and parser helpers such as `Lexer_ParseSlotConstraint`
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.
- Full uncontained load-game flow remains behind the missing authentic class/bload prelude and the later post-save `PlayGame` handoff.
