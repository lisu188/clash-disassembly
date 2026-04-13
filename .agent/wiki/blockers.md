# Current Blockers

- The contained authentic `Load Game` lane is still green through the slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state still dies at a precisely identified startup-prelude gap:
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
- The retained broader executable-regeneration slice is now blocked separately at a later front:
  - `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame` all link and stay alive under `timeout 1s`
  - the mission-loader helper-name gap `sub_40D330` / `sub_44C2A0` is gone
  - the next honest retained blocker is the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface after the now-complete `Scenario_LoadMissionByIndex` switch, with the adjacent AI branch `sub_451F70` still secondary
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.

## Latest Update
- `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, `PlayGame`, and `WorldMap_RunHumanTurnLoop` all link and stay alive under `timeout 1s`.
- The next honest retained blocker is still the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface after the repaired zero-init entry, `arama1` / `kon_por1` mission-success tail, zero-arg loop-entry helpers, held-key `DD_Pump` loops, queued-path AP compare, and saved render-hook/resource-handle debug block.

- `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` are no longer the live retained blocker band.
- The next honest retained blocker inside `WorldMap_RunHumanTurnLoop` is now the deeper `WorldMap_HandleTileHoverAndClick` / `sub_4084A0` surface, with `sub_451F70` still secondary.
