# Runtime Glue

- Active repaired glue on the live frontier:
  - `Render_LoadResourceSprite_v4`, `Render_LoadResourceSprite_v3`, and `sub_40BC00` still carry the contained row-resource / row-draw lane
  - `sub_4163F0`, `sub_4443C0`, and `sub_4443D0` still carry the world-map-init and save-path corridor
  - the retained parser/export, math, and low-risk file/runtime bands remain settled
  - no new compat wrappers were added in the latest mission-loader batch
- Mission-loader note:
  - the old retained helper-name gap `sub_40D330` / `sub_44C2A0` is gone from the mission-loader slice
  - the recovered cases now call the existing local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly
  - the full 20-case `Scenario_LoadMissionByIndex` switch stays in recovered C: case `18` adds the `Stone Bell` cut, `Fhur Tao` boost, and raw `+28` slot-state bands, while the already-present case `19` corroborates cleanly against `mapP10`
- Still quarantined / unresolved:
  - deeper `_wcpp_*` runtime families
  - thread/process helpers
  - the missing authentic class/bload prelude before `oddzial`
  - the broader gameplay/session surface beyond the now-complete `Scenario_LoadMissionByIndex` switch
