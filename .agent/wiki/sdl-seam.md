# SDL Seam

- The just-cleared load-menu row-resource and row-draw blockers were not SDL seam failures.
- `platform_sdl_runtime.c` remained unchanged through this batch.
- Current evidence:
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - contained widened load-menu row draws, slot-hover selection, and slot-click/confirm all complete under the existing SDL seam
  - the explicit broader-rules-contained probe now reaches `parse-make-instance-before-class-lookup` and then logs `class-lookup-no-table name=oddzial`
  - `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` dies earlier on `symbol-lookup-missing-table MAIN`
  - the retained broader startup-prelude slice is now reduced past `unknown_libname_7`, `unknown_libname_8`, and `AST_FreeNode`, but it is still blocked on the wider runtime/class/parser surface below SDL, not on `platform_sdl_runtime.c`
- Next likely SDL-facing work is still later input/present fidelity, not the contained menu/load wedge or the newly isolated class/bload startup blocker.
