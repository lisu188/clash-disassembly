# Runtime Glue

- Active repaired glue on the live frontier:
  - `Render_LoadResourceSprite_v4`, `Render_LoadResourceSprite_v3`, and `sub_40BC00` still carry the contained row-resource / row-draw lane
  - `sub_4163F0`, `sub_4443C0`, and `sub_4443D0` still carry the world-map-init and save-path corridor
  - the retained parser/export, math, and low-risk file/runtime bands remain settled
  - no new compat wrappers were added in the latest mission-loader batch
- Mission-loader note:
  - the old retained helper-name gap `sub_40D330` / `sub_44C2A0` is gone from the mission-loader slice
  - the recovered cases now call the existing local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly
  - case `17` / `p_mapa8j.map` stays entirely in recovered C: mission-local byte clear, four `Rules_RetractTreasureFact` calls, `Raylin` / `Lord Ruwe` / `McGregor` / `Crowley`, the `Dark Town` `BUILDING_RECORD(+438) -= 100` cut, the four raw slot-state mutation bands, and no post-init camera override or `Rules_LogAssigned*` tail
- Still quarantined / unresolved:
  - deeper `_wcpp_*` runtime families
  - thread/process helpers
  - the missing authentic class/bload prelude before `oddzial`
  - the remaining `Scenario_LoadMissionByIndex` cases, starting with case `18` / `p_mapa9j.map`
