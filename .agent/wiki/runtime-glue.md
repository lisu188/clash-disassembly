# Runtime Glue

- Active repaired glue on the live frontier:
  - `Render_LoadResourceSprite_v4`, `Render_LoadResourceSprite_v3`, and `sub_40BC00` still carry the contained row-resource / row-draw lane
  - `sub_4163F0`, `sub_4443C0`, and `sub_4443D0` still carry the world-map-init and save-path corridor
  - the retained parser/export, math, and low-risk file/runtime bands remain settled
  - no new compat wrappers were added this batch
- Current batch result:
  - the old retained helper-name gap `sub_40D330` / `sub_44C2A0` is gone from the mission-loader slice
  - the first recovered mission cases now call the existing local helpers `MiniMap_CreateSurface` and `Game_InitPlayerViewState` directly
  - `mapP2` / case `11`, `mapK2` / case `1`, `mapK3` / case `2`, and `mapK4` / case `3` are now materialized in recovered C without broadening `compat/decomp_runtime_stubs.c`
  - `mapK2` keeps its explicit post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff and manual camera override in recovered C rather than wrapper glue
  - `mapK3` keeps its player-2 intelligence write, its `Treg Rock` post-castle `BUILDING_RECORD(castle_index) + 18 = -1` plus `Building_OnGarrisonChange` handoff, and the same manual camera override in recovered C rather than wrapper glue
  - `mapK4` keeps its `Ughuata` post-castle `BUILDING_RECORD(castle_index) + 18 = -1`, `BUILDING_RECORD(castle_index) + 438 = 300`, and its three raw stack/status mutation bands in recovered C rather than wrapper glue
- Still quarantined / unresolved:
  - deeper `_wcpp_*` runtime families
  - thread/process helpers
  - the missing authentic class/bload prelude before `oddzial`
  - the remaining `Scenario_LoadMissionByIndex` cases, starting with `mapK5`
