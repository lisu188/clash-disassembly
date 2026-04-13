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
  - the retained startup-prelude order is now corroborated as `sub_451E46 -> sub_460490 -> initRandomSeed -> StartMenu -> UI_StartAnims -> PlayGame_Dispatch -> PlayGame`
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame` now link and stay alive under `timeout 1s`
  - the remaining retained widening is the gameplay/session surface after the now-complete `Scenario_LoadMissionByIndex` switch, still centered on `WorldMap_RunHumanTurnLoop` but now past its zero-init entry and `arama1` / `kon_por1` mission-success tail

## Latest Update
- Retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, `PlayGame`, and `WorldMap_RunHumanTurnLoop` now all stay alive under `timeout 1s`.
- The remaining retained widening is still the gameplay/session surface after the now-complete `Scenario_LoadMissionByIndex` switch, but it is now past the zero-init entry, `arama1` / `kon_por1` mission-success tail, zero-arg loop-entry helper lane, held-key `DD_Pump` loops, queued-path AP compare, and saved render-hook/resource-handle debug block.

- The retained gameplay/session widening is now past the `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` helper bands inside `WorldMap_RunHumanTurnLoop`.
- The next honest retained widening inside the same loop now falls through to `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`, while the contained `oddzial` / `MAIN` split remains unchanged.
