# Current Blockers

- The contained authentic `Load Game` lane is still green through the pre-confirm slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state now dies at a precisely identified startup-prelude gap:
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
  - both post-confirm menu-probe variants still fall into the same timeout/core-dump band under `timeout 2s`
- The retained broader startup-prelude executable-regeneration slice is still blocked separately:
  - `sub_451E46` now narrows past the local helper/runtime band, the parser-export layer, and the low-risk file/runtime wrapper band, but it still fails on the remaining x87-heavy math/runtime helpers `IF_DACOS`, `IF_ASIN`, `IF_DCOSH`, `IF_DSINH`, `IF_DTANH`, `__FYL2X__`, `__FPREM__`, `__F2XM1__`, `__FSCALE__`, `floor_`, `ceil_`, and `IF_DPOW`
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.
- Full uncontained load-game flow remains behind the missing authentic class/bload prelude and the later post-save `PlayGame` handoff.
