# Runtime Glue

> "Live frontier" below is the 2026-04 state; the current frontier is mission 05
> (`docs/STATUS.md`). The repaired-band and quarantine records remain valid
> recovery context.

- Repaired glue on the 2026-04 frontier:
  - `Render_LoadResourceSprite_v4`, `Render_LoadResourceSprite_v3`, and `sub_40BC00` still carry the contained row-resource / row-draw lane
  - `sub_4163F0`, `sub_4443C0`, and `sub_4443D0` still carry the world-map-init and save-path corridor
  - `Scenario_LoadMissionByIndexAndPlay` now keeps its real 27-byte campaign-state save/restore explicit instead of forwarding decompiler garbage into `PlayGame`
  - the `PlayGame` prologue now restores the real `backgr1/2/3.s32` and `treemas1/2/3.s32` loads and initializes the player-reveal scan counters from asm
  - `WorldMap_RunHumanTurnLoop` now restores the asm-backed zero-init entry flags and the `sub_4623C0("arama1", "kon_por1")` mission-success tail in recovered C
  - the retained parser/export, math, and low-risk file/runtime bands remain settled
  - no new compat wrappers were added in the latest human-turn-loop batch
- Mission-loader note:
  - the old retained helper-name gap `sub_40D330` / `sub_44C2A0` is gone from the mission-loader slice
  - the recovered cases now call the existing local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly
  - the full 20-case `Scenario_LoadMissionByIndex` switch stays in recovered C: case `18` adds the `Stone Bell` cut, `Fhur Tao` boost, and raw `+28` slot-state bands, while the already-present case `19` corroborates cleanly against `mapP10`
- Still quarantined / unresolved:
  - deeper `_wcpp_*` runtime families
  - thread/process helpers
  - the missing authentic class/bload prelude before `oddzial`
  - the deeper gameplay/session surface inside `WorldMap_RunHumanTurnLoop` after the repaired entry and mission-success tail

## Latest Update
- `WorldMap_RunHumanTurnLoop` now also restores the zero-arg loop-entry helper lane, the held-key `DD_Pump` loops, the queued-path AP compare, and the saved render-hook/resource-handle debug block in recovered C.
- No new compat wrappers were added in this batch.
- The live retained blocker is still the deeper gameplay/session surface inside `WorldMap_RunHumanTurnLoop` after the repaired call-shape band.

- `WorldMap_HandleTopMenuBar` now also restores the menu-sprite draw, mission turn-counter text, menu-surface destroy, and saved render-hook/resource-handle restore block directly in recovered C.
- `UnitStackSelection_HandleInput` now also restores the zero-arg `Render_Begin` calls, real move coordinates, `dword_526F78` zero-on-success, and `Render_LoadResourceSprite_v2` plus redraw tail directly in recovered C.
- No new compat wrappers were added in this batch either.
