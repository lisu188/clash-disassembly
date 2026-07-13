# SDL Seam

> Evidence below is the 2026-04 state; the current frontier is mission 05
> (`docs/STATUS.md`). The `--authentic-*` switches and the load-menu-probe env
> controls cited as evidence were **later removed** as active selectors (see
> `boot-path.md` "Removed Selectors") — do not treat those commands as runnable
> today. The seam conclusion itself (gameplay blockers sit below SDL, not in
> `platform_sdl_runtime.c`) still holds.

- The contained and retained 2026-04 frontiers were below SDL.
- Evidence (2026-04; probe switches since removed):
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - the corrected post-confirm contained probes (`CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm`) still reproduce `oddzial` with broader rules and `MAIN` without them
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame` now link and stay alive under `timeout 1s`
  - the old retained `sub_40D330` / `sub_44C2A0` gap plus the full 20-case mission-loader switch were resolved entirely in recovered C without touching `platform_sdl_runtime.c`
  - the latest `WorldMap_RunHumanTurnLoop` zero-init and `arama1` / `kon_por1` mission-success repairs also stayed entirely in recovered C without touching `platform_sdl_runtime.c`
- Next likely SDL-facing work is still later input/present fidelity, not the current gameplay/session or class/bload blocker; the next retained blocker stays below SDL inside the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface.

## Latest Update
- The latest `WorldMap_RunHumanTurnLoop` call-shape repairs stayed entirely in recovered C without touching `platform_sdl_runtime.c`.
- The direct retained `WorldMap_RunHumanTurnLoop` probe now links and stays alive under `timeout 1s`.
- The next retained blocker stays below SDL inside the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface after the repaired call-shape band.

- The latest `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` repairs stayed entirely below SDL in recovered C.
- The next retained blocker still stays below SDL and is now centered on `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`.
