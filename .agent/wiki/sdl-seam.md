# SDL Seam

- The just-cleared retained startup math band was not an SDL seam problem.
- `platform_sdl_runtime.c` remained unchanged through this batch.
- Current evidence:
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - contained widened load-menu row draws, slot-hover selection, and slot-click/confirm all complete under the existing SDL seam
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` and then logs `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe dies earlier on `symbol-lookup-missing-table MAIN`
  - both post-confirm menu-probe variants still fall into the same timeout/core-dump band under `timeout 2s`
  - retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` now link and stay alive under `timeout 1s`
  - the next retained blocker is the broader `PlayGame_Dispatch` link surface, and its first unresolveds are `_wcpp_4_static_init__`, front-end/world-map data tables, `rand_`, `memmove_`, `strlwr_`, `Locale_DrawInteger`, `Rules_*`, `Render_DrawSprite_v3`, `WCIsvListBase_*`, and `JUMPOUT`, not SDL seam exports
- Next likely SDL-facing work is still later input/present fidelity, not the contained menu/load wedge or the newly isolated `PlayGame_Dispatch` front-end/gameplay link band.
