# Current Blockers

- The contained authentic `Load Game` lane is still green through the pre-confirm slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state now dies at a precisely identified startup-prelude gap:
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
  - both post-confirm menu-probe variants still fall into the same timeout/core-dump band under `timeout 2s`
- The retained broader startup-prelude executable-regeneration slice is still blocked separately:
  - `sub_451E46` now narrows past the local helper/runtime band and the parser-export layer, but it still fails on the deeper slot/parser/math/runtime band led by `Lexer_BuildSlotNode`, `Lexer_FindSymbolIndex`, `Lexer_CheckValueList`, `Lexer_EmitSlotBinding`, `Lexer_FindTemplateSlot`, `Lexer_OutputFieldRange`, `Lexer_ParseModifyOrDuplicate`, `Lexer_WarnImpliedTemplate`, `unknown_libname_2`, `MoveFileA`, `fgets_`, `sscanf_`, `ceil_`, `floor_`, the `IF_*` / `__FYL2X__` helpers, and `JUMPOUT`
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.
- Full uncontained load-game flow remains behind the missing authentic class/bload prelude and the later post-save `PlayGame` handoff.
