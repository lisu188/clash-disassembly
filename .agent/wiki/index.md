# Agent Wiki Index

> **Scope note (2026-07-13).** This wiki records executable-regeneration context
> and decisions. For the *current* project state, do not read frontier claims
> here — they drift. Canonical sources:
> - current runtime state, active blocker, next target: `docs/STATUS.md`
> - track boundaries and priority sequence: `docs/PROJECT_TRACKS.md`
> - DOS naming baseline: `DISASSEMBLY_STATUS.md`
>
> As of 2026-07-13 the campaign frontier is **mission 05** (missions `00..04`
> route-complete); the frontier snapshot below is the older 2026-04 state and is
> retained as history.

## Core notes

- [boot-path.md](boot-path.md) — recovered boot route and removed host-side selectors
- [runtime-glue.md](runtime-glue.md) — repaired runtime-glue bands and quarantines
- [sdl-seam.md](sdl-seam.md) — what sits below the SDL seam
- [class-seams.md](class-seams.md) — conservative C++ class-regeneration seams
- [blockers.md](blockers.md) — startup blocker list (historical snapshot)
- [verification.md](verification.md) — dated verification transcripts (historical)
- [decisions.md](decisions.md) — per-decision recovery rationale (timeless)
- [log.md](log.md) — chronological work journal (ends 2026-04-16)

## Historical frontier snapshot (2026-04)

- Current frontier:
  - keep the contained authentic load-menu wedge green while separating it from the broader retained gameplay/session widening that now starts after `sub_451E46 -> sub_460490 -> UI_StartAnims -> PlayGame_Dispatch -> PlayGame`
  - the retained mission-loader slice in `clash95.c` now covers all 20 switch arms, cases `0` through `19`
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its 27-byte campaign-state save/restore explicit, the `PlayGame` prologue now restores the real `backgr*.s32` / `treemas*.s32` loads plus initialized player-scan counters, and `WorldMap_RunHumanTurnLoop` now restores the asm-backed zero-init plus the `sub_4623C0("arama1", "kon_por1")` mission-success tail
  - the next honest retained blocker is the deeper `WorldMap_RunHumanTurnLoop` register-loss/usercall surface after `Scenario_LoadMissionByIndexAndPlay` / `PlayGame`, not another mission-loader case
- Last green targets:
  - `clash95_recovered`
  - `clash95_bootstrap`
  - `clash95_cpp_regen`
  - retained probes `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, `PlayGame`, `WorldMap_RunHumanTurnLoop`
- Highest runtime milestone (of that era):
  - authentic load-menu row resources load; all ten contained `sub_44A140` row draws complete
  - authentic slot-strip click plus bottom-row load confirm exits with `selected_slot = 0`, `confirm = 1`, `screen = 5`
  - the corrected post-confirm probe lane (`CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm` plus `CLASH95_LOAD_MENU_PROBE_POST_CONFIRM=1`) reaches `load-menu-post-confirm-load-save`
  - the traced contained split still reproduces `class-lookup-no-table name=oddzial` with broader rules and `symbol-lookup-missing-table MAIN` without them
  - case `18` / `p_mapa9j.map` materialized in recovered C (five-player setup, `Stone Bell` cut, `Fhur Tao` boost, six raw `+28` slot-state bands); case `19` / `p_map10z.map` corroborated against `mapP10`, completing the 20-case mission switch
- Adjacent blocked widening (of that era):
  - the broader-rules-contained probe still reached `parse-make-instance-before-class-lookup` on `oddzial` and then reported a null defclass registry
  - the `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0` probe still failed earlier on `symbol-lookup-missing-table MAIN`
  - the contained save-slot repaint/name lane after `load-menu-skip-save-slot-draw` was deferred
  - `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` restored their retained helper bands directly in recovered C, pointing the next retained blocker at `WorldMap_HandleTileHoverAndClick` / `sub_4084A0`
