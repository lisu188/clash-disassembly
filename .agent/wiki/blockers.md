# Current Blockers

- The contained authentic `Load Game` lane is still green through the pre-confirm slot-strip selection and bottom-row load confirm corridor.
- The first broader contained widening adjacent to that green state still dies at a precisely identified startup-prelude gap:
  - the broader-rules-contained probe reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
  - both post-confirm menu-probe variants still fall into the same timeout/core-dump band under `timeout 2s`
- The retained broader startup-prelude executable-regeneration slice is now blocked separately at a later front:
  - the retained x87 math/runtime band under `sub_451E46` is gone
  - direct retained probes for `sub_451E46`, `sub_460490`, and `UI_StartAnims` all link and stay alive under `timeout 1s`
  - the former `PlayGame_Dispatch` UI/data/runtime band is now reduced in recovered C
  - the mission-loader `JUMPOUT` at `Scenario_LoadMissionByIndex` / `sub_460360` is gone in the first menu-reachable cases
  - the next honest retained blocker is now the deeper mission-loader helper band `sub_40D330` / `sub_44C2A0`
- The contained probe still prints `load-menu-skip-save-slot-draw` after the row draws, so the deeper save-slot repaint/name lane is still deferred.
- Full uncontained load-game flow remains behind the missing authentic class/bload prelude and the later post-save `PlayGame` handoff.
