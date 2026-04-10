# SDL Seam

- The just-cleared load-menu row-resource and row-draw blockers were not SDL seam failures.
- `platform_sdl_runtime.c` remained unchanged through this batch.
- Current evidence:
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - contained widened load-menu row draws, slot-hover selection, and slot-click/confirm all complete under the existing SDL seam
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` and then logs `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe dies earlier on `symbol-lookup-missing-table MAIN`
  - both post-confirm menu-probe variants still fall into the same timeout/core-dump band under `timeout 2s`
  - the retained broader startup-prelude slice is now reduced past the local runtime/helper band, the parser-export layer, and the low-risk file/runtime wrappers, and is blocked on the remaining x87-heavy math/runtime surface below SDL, not on `platform_sdl_runtime.c`
- Next likely SDL-facing work is still later input/present fidelity, not the contained menu/load wedge or the newly isolated class/bload startup blocker.
