# Agent Wiki Index

- Current frontier:
  - keep the contained authentic load-menu wedge green while separating it from the broader retained gameplay/session widening that now starts after `sub_451E46 -> sub_460490 -> UI_StartAnims -> PlayGame_Dispatch -> PlayGame`
  - the retained mission-loader slice in `clash95.c` now covers all 20 switch arms, cases `0` through `19`
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit, the `PlayGame` prologue now restores the real `backgr*.s32` / `treemas*.s32` loads plus initialized player-scan counters, and `WorldMap_RunHumanTurnLoop` now restores the asm-backed zero-init plus the `sub_4623C0("arama1", "kon_por1")` mission-success tail
  - the next honest retained blocker is the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface after `Scenario_LoadMissionByIndexAndPlay` / `PlayGame`, not another mission-loader case
- Last green targets:
  - `clash95_recovered`
  - `clash95_bootstrap`
  - `clash95_cpp_regen`
  - retained probe `sub_451E46`
  - retained probe `sub_460490`
  - retained probe `UI_StartAnims`
  - retained probe `PlayGame_Dispatch`
  - retained probe `PlayGame`
- Highest runtime milestone:
  - authentic load-menu row resources load
  - all ten contained `sub_44A140` row draws complete
  - authentic slot-strip click plus bottom-row load confirm exits with `selected_slot = 0`, `confirm = 1`, `screen = 5`
  - the corrected post-confirm probe lane (`CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm` plus `CLASH95_LOAD_MENU_PROBE_POST_CONFIRM=1`) reaches `load-menu-post-confirm-load-save`
  - the traced contained split still reproduces `class-lookup-no-table name=oddzial` with broader rules and `symbol-lookup-missing-table MAIN` without them
  - case `18` / `p_mapa9j.map` is now materialized in recovered C with its five-player `Raylin` / `Tubius` / `Lord Gorio` / `McDan` / `Drebegen` setup, the `Stone Bell` `BUILDING_RECORD(+438) -= 100` cut, the `Fhur Tao` `BUILDING_RECORD(+438) += 200` boost, the six raw slot-state mutation bands on the `+28` lane, and the preserved absence of any post-init camera override or `Rules_LogAssigned*` tail
  - case `19` / `p_map10z.map` was already present and is now corroborated against `mapP10`, completing the 20-case mission switch without introducing new SDL, compat, or `src_cpp` glue
  - retained standalone probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame` now link and stay alive under `timeout 1s`
- Adjacent blocked widening:
  - the broader-rules-contained probe still reaches `parse-make-instance-before-class-lookup` on `oddzial` and then reports a null defclass registry
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still fails earlier on `symbol-lookup-missing-table MAIN`
  - the contained save-slot repaint/name lane after `load-menu-skip-save-slot-draw` is still deferred
  - the next retained widening is the gameplay/session surface after the now-complete `Scenario_LoadMissionByIndex` switch, still centered on `WorldMap_RunHumanTurnLoop` but now past its zero-init entry and `arama1` / `kon_por1` mission-success tail
- Core notes:
  - [boot-path.md](/home/andrz/git/clash-disassembly/.agent/wiki/boot-path.md)
  - [runtime-glue.md](/home/andrz/git/clash-disassembly/.agent/wiki/runtime-glue.md)
  - [sdl-seam.md](/home/andrz/git/clash-disassembly/.agent/wiki/sdl-seam.md)
  - [class-seams.md](/home/andrz/git/clash-disassembly/.agent/wiki/class-seams.md)
  - [blockers.md](/home/andrz/git/clash-disassembly/.agent/wiki/blockers.md)
  - [verification.md](/home/andrz/git/clash-disassembly/.agent/wiki/verification.md)
  - [decisions.md](/home/andrz/git/clash-disassembly/.agent/wiki/decisions.md)
  - [log.md](/home/andrz/git/clash-disassembly/.agent/wiki/log.md)

## Latest Update
- `WorldMap_RunHumanTurnLoop` now also restores the zero-arg loop-entry helper lane, held-key `DD_Pump` loops, the queued-path AP compare, and the saved render-hook/resource-handle debug block.
- Last green retained targets now include `WorldMap_RunHumanTurnLoop` alongside `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame`.
- The next honest retained blocker stays in the deeper `WorldMap_RunHumanTurnLoop` loop body after those repaired call-shape slices, not in SDL, compat, or the already-covered mission-loader switch.

- `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` now restore their retained helper bands directly in recovered C, so the next honest retained blocker is deeper in `WorldMap_RunHumanTurnLoop` at `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`.
