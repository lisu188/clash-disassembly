# Class Seams

> Frontier notes below are the 2026-04 state; the current frontier is mission 05
> (`docs/STATUS.md`). Note: "all 20 `Scenario_LoadMissionByIndex` case arms are
> recovered" is a *code-coverage* fact about the mission-loader switch in
> recovered C — it does not mean the missions are route-complete (only `00..04`
> are; see `docs/PROJECT_TRACKS.md` for the completion-language distinction).

- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- Frontier notes (2026-04):
  - the contained authentic load-game lane is still carried by recovered C menu/save helpers, not by a broader class-runtime splice
  - the current broader contained crash is still at `parse-make-instance-before-class-lookup` on `oddzial`
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame` now all link
  - the old retained `sub_40D330` / `sub_44C2A0` gap was confirmed again to be pure recovered-C mission/minimap/view-state work, not `src_cpp`
  - all 20 `Scenario_LoadMissionByIndex` case arms are confirmed and recovered as pure recovered-C mission setup; the latest `WorldMap_RunHumanTurnLoop` zero-init and `arama1` / `kon_por1` mission-success repairs also stayed pure recovered C, and the live retained blocker remains the deeper loop body rather than a reason to move behavior into `src_cpp`

## Latest Update
- Retained probes now include `WorldMap_RunHumanTurnLoop` alongside `sub_451E46`, `sub_460490`, `UI_StartAnims`, `PlayGame_Dispatch`, and `PlayGame`.
- The latest `WorldMap_RunHumanTurnLoop` call-shape repairs stayed pure recovered C, so the live retained blocker is still the deeper loop body rather than a `src_cpp` seam.

- The latest `WorldMap_HandleTopMenuBar` and `UnitStackSelection_HandleInput` repairs stayed pure recovered C, so they are not evidence for widening `src_cpp` class seams.
- The next retained blocker remains deeper gameplay/session control flow, not a class seam.
