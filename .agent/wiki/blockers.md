# Current Blockers

- The contained authentic `Load Game` lane is still green through the slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state still dies at a precisely identified startup-prelude gap:
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
- The retained broader executable-regeneration slice is now blocked separately at a later front:
  - `sub_451E46`, `sub_460490`, `UI_StartAnims`, and `PlayGame_Dispatch` all link and stay alive under `timeout 1s`
  - the mission-loader helper-name gap `sub_40D330` / `sub_44C2A0` is gone
  - the next honest retained blocker is the remaining `Scenario_LoadMissionByIndex` case recovery, starting with `mapP3` / case `12`
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.
