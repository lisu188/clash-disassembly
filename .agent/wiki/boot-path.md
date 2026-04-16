# Boot Path

- Durable boot chain in repo:
  - `main`
  - `App_WinMain`
  - `Bootstrap_RunRecoveredStartupPrelude`
  - `Bootstrap_RunRecoveredRuntimeAndRenderInit`
  - contained probes such as `--authentic-startup-prelude` and `--authentic-menu-probe`
- Current contained menu milestone:
  - top-level `Load Game` click is stable
  - contained load-menu row resources load
  - contained load-menu row draws complete
  - contained slot-strip click plus bottom-row load confirm exits with `selected_slot = 0`, `confirm = 1`, `screen = 5`
  - the real post-confirm probe lane needs `CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm` plus `CLASH95_LOAD_MENU_PROBE_POST_CONFIRM=1` after slot selection
  - the contained post-confirm save replay still reaches `load-menu-post-confirm-load-save`
  - the traced contained split still reproduces `class-lookup-no-table name=oddzial` with broader rules and `symbol-lookup-missing-table MAIN` without them
- Next boot-path frontier:
  - keep the green pre-confirm load-menu wedge intact while supplying the missing authentic class/bload prelude for post-confirm save replay
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial` and then reports a null defclass table
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still dies earlier on `symbol-lookup-missing-table MAIN`
  - the retained startup-prelude order is now corroborated as `sub_451E46 -> sub_460490 -> initRandomSeed -> StartMenu -> UI_StartAnims -> PlayGame_Dispatch`
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, and `PlayGame_Dispatch` now link and stay alive under `timeout 1s`
  - the remaining retained widening is the gameplay/session surface after the now-complete `Scenario_LoadMissionByIndex` switch

## Latest Front-End Update
- `clash95_bootstrap` now defaults to the recovered front-end wedge instead of a bare SDL window: early startup prelude, recovered video init, recovered main-menu first-frame presentation, then the message loop.
- `--platform-window-only` keeps the old host-window smoke path available when isolating the SDL shell.
- `CLASH95_MENU_PROBE_EXIT_AFTER_CAPTURE=main-menu` and `CLASH95_MENU_PROBE_EXIT_AFTER_CAPTURE=load-menu` provide deterministic finite exits after screenshot capture.
- The load-game menu draws save rows by default during the contained probe and repaints the selected-slot row during auto-hover selection.
- The post-confirm save replay remains blocked at the known class/bload frontier (`class-lookup-no-table name=oddzial`); that blocker is after the verified main-menu and load-menu capture wedge.
