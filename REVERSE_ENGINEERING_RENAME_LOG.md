# Reverse Engineering Rename Log

## Batch 8 – Unit Stack Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_40F3C0 | UnitStack_IsIndexOnMap | Function | Unit Lifecycle | High | Walks the 200-column tile occupancy buffer at `gameData + 556374` to locate the stack id before reuse, proving it tests whether the stack id is already on the map. |
| sub_40F440 | UnitSlot_InitFromType | Function | Unit Lifecycle | High | Initializes a 31-byte slot entry with type id, owner, morale, action points, and veterancy from the per-unit tables, so it clearly seeds an individual unit slot. |
| sub_40F4D0 | UnitStack_ResetRecord | Function | Unit Lifecycle | High | Calls `UnitSlot_InitFromType` for the first slot, clears the remaining slots/path buffer, and stores the owner byte, matching a full reset of a stack record. |
| sub_40F7C0 | UnitStack_KillByIndex | Function | Unit Lifecycle | High | Thin wrapper that converts a stack index to its record pointer and forwards to `Unit_Kill`, so the rename documents that it kills stacks by index. |
| sub_40F800 | UnitStack_RemoveFromTile | Function | Unit Lifecycle | High | Validates row/column bounds, retracts army intel, zeros the tile entry, and updates fog-of-war, which is exactly the logic to remove a stack from its occupied tile. |
| sub_40F890 | UnitStack_UnlinkIfEmpty | Function | Unit Lifecycle | High | Checks whether the first slot’s unit type is -1 and, if so, calls `Rules_UnlinkArmyFact`; it only unlinks empty stacks. |
| sub_40F8B0 | UnitStack_GetVisionRadius | Function | Unit Lifecycle | Medium | Iterates every occupied slot, reads `byte_5125AE` for each unit type, and tracks the max value, yielding the stack’s vision range. |
| sub_40F900 | UnitStack_UpdateVision | Function | Unit Lifecycle | High | Uses the owning player id, stack tile, and `UnitStack_GetVisionRadius` to stamp fog-of-war via `PlayerExploration_RevealTile`, so the rename reflects its vision-update role. |
| sub_40F9F0 | UnitStack_HasReadyUnits | Function | Unit Lifecycle | Medium | Scans up to 10 slots looking for bit0 set in the slot flag byte, returning 1 only if at least one squad member is marked ready — a readiness probe used in `Unit_NewTurn`. |
| sub_40FA20 | UnitStack_ClearReadyFlags | Function | Unit Lifecycle | Medium | Iterates every occupied slot and clears bit0 of the flag byte, which resets the per-turn “ready” state for the entire stack. |
| sub_40FA50 | UnitStack_SetReadyFlags | Function | Unit Lifecycle | Medium | Complement to the above that sets bit0 for each slot once the UI or turn logic re-enables the stack. |
| gameData + 147174 + 725 * index | UNIT_STACK(index) / UnitStackRecord | Recovered Struct | Unit Lifecycle | High | The code constantly adds 147174 + 725*index to reach stack entries (row, column, owner, slot array, path buffer). Exposing this as `UnitStackRecord` aligns with the per-stack macros and clarifies the recovered layout. |

## Deferred / Ambiguous
- Remaining entries of `g_UnitSpriteFolders` (e.g., the sprite folders for Górale, Smoki, etc.) are not emitted in `clash95.c`; resolving those unit names requires dumping the data segment or external resource files.

## Batch 9 – Army Fact Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_40F6E0 | UnitStack_LinkArmyFact | Function | Unit Lifecycle | High | Wrapper invoked after stack creation and whenever an existing stack tile is re-linked; it passes the stack pointer and tile occupant id into the rules engine (`Rules_CreateArmyFact`) to register the squad in the fact database. |
| sub_4521D0 | Rules_CreateArmyFact | Function | Rules/Meta | High | Builds the "ODDZIAL" fact string, calls `Rules_AssertFact`, stores the returned handle at stack+721, and then calls `Rules_LinkArmyFact`; behavior matches an army-fact creation helper rather than an anonymous subroutine. |

## Batch 10 – Unit Stat Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_411120 | UnitStats_CalcMeleeAttack | Function | Unit Stats | High | Pulls `byte_51257E` (melee table) plus formation bits and veterancy, then multiplies by morale (`a1[9] / 100`), matching the effective melee attack strength used in combat. |
| sub_4111C0 | UnitStats_CalcRangedAttack | Function | Unit Stats | High | Uses `byte_51257F` (ranged table) with the missile-cover flag at `a1[22]`, adds formation/stance bonus, and scales via morale just like projectile attack code. |
| sub_411240 | UnitStats_GetRangedIconIndex | Function | Unit Stats | Medium | Shares the same inputs as the ranged attack function but omits morale scaling, mirroring `UI_IconIndexFromStats` for melee; used by UI to pick ranged-strength icons. |
| sub_411280 | UnitStats_CalcDamagePerHit | Function | Unit Stats | High | Combines `byte_512581` (damage scalar) with veterancy and morale to compute actual damage inflicted by an attack volley. |
| sub_4112C0 | UnitStats_GetBaseDamage | Function | Unit Stats | High | Returns the base damage scalar plus veterancy without morale scaling, i.e., the raw stat shown in UI. |
| sub_4112F0 | UnitStats_CalcSiegeAttack | Function | Unit Stats | Medium | Reads `byte_512584` (structure damage) and mirrors the melee/ranged calculations, indicating it computes vs-building attack strength. |

## Batch 11 – Unit Naming Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| off_51256C | g_UnitSpriteFolders | Global | Unit Lifecycle | High | Sprite loader helpers (e.g., `clash95.c:25320-25480`) index this array to build animation paths such as `units_go\peon?.s32`; the base entry is the literal "peon", revealing that the table stores per-unit sprite folder names. |
| *(new constant)* | UNIT_TYPE_PEASANT | Helper | Unit Lifecycle | High | Codifies type id 0 as the Peasant/Chłopi stack, supported by the base sprite folder "peon" and the scripting APIs `IloscChlopow` / `WyprowadzChlopow` that manipulate the same unit. |

## Batch 12 – Unit Morale Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_4114B0 | Unit_CompactSquad | Function | Unit Lifecycle | High | Iterates through the 10 squad slots, shifts data down whenever it finds `type == -1`, clears the tail slot, and re-links the CLIPS army fact; this matches the compact/cleanup helper invoked after casualties. |
| sub_411560 | UnitSlots_RemoveGaps | Function | Unit Lifecycle | Medium | Helper that scans the first `count` slots and shifts subsequent entries down whenever it encounters an empty slot; combat cleanup code calls it after zeroing hitpoints to remove gaps without touching the full squad. |
| sub_4115E0 | Unit_CheckLowMorale | Function | Unit Lifecycle | High | Copies the unit record, rolls random morale checks per slot, logs via `aUnit_checklowm` strings, shows the morale-break window (`off_512368`), and if deserters appear it compacts the squad and finalizes the army fact—exactly the low-morale check the logs reference. |

## Batch 13 – Turn, Terrain, and Trap State Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| nextPlayer | Game_AdvanceToNextPlayerTurn | Function | Turn Flow | High | Saves the outgoing player camera, rotates to the next active player, increments `GAME_TURN_COUNTER` when the cycle wraps, runs village/port/queen/building/unit per-turn handlers, and then reinitializes either human UI or AI control for the new player. |
| dword_5202EC | g_CurrentPlayerIndex | Global | Turn Flow | High | The symbol always indexes `PLAYER_DATA`, drives UI ownership checks, is saved/restored around stack-vision stamping, and selects the acting faction for AI and end-turn logic, so it is the current turn player id rather than an anonymous integer. |
| sub_413B10 | Map_InitTerrainMoveTableOffsets | Function | Movement/Map | High | Builds the 1024-entry lookup that converts terrain tile ids into offsets inside `byte_512586`, which is exactly the initialization step for terrain-specific move-cost columns. |
| dword_524568 | g_TerrainMoveTableOffsets | Table | Movement/Map | High | `Map_GetUnitTileMoveCostOrZero` and `UnitStack_GetTileMoveCostOrZero` index this array with the tile terrain id and then add the result to `byte_512586`, proving it is a terrain-to-move-table offset map. |
| sub_413DD0 | Map_GetUnitTileMoveCostOrZero | Function | Movement/Map | High | Rejects occupied, trapped, or blocked tiles, then returns either `byte_512585` road movement cost or a terrain-adjusted `byte_512586` cost for the requested unit template. |
| sub_414150 | UnitStack_GetTileMoveCostOrZero | Function | Movement/Map | High | Copies a stack-derived movement profile with `sub_413920`, applies the same occupancy/trap checks as the unit-template helper, and returns the resulting cost for a concrete stack. |
| gameData + 14 * column + 1400 * row | TILE_TERRAIN_RECORD(row, column) / MapTileRecord | Recovered Struct | Map/Tile | High | Movement code treats word 0 as the terrain id, word 2 as a road/bridge override that switches to road costs, and bridge placement temporarily writes overlay ids like `872` at offset `+4`, exposing a stable 14-byte tile record. |
| gameData + 576374 + column + 100 * row | TILE_TRAP_OWNER_MASK(row, column) / TileTrapOwnerMaskLayer | Recovered Struct | Trap/Map | High | `Trap_New` writes `1 << owner`, `Trap_GetTileOwnerMask` reads and masks the byte, the renderer overlays the trap marker only when the current player bit is set, and `Trap_TriggerAtStackTile` clears the byte after activation. |
| sub_42B3F0 | Trap_CanPlaceAtTile | Function | Trap/Map | High | Validates that the target tile has no trap bit for the acting player, is not occupied, is not blocked by coast/building rules, and is not on one of the disallowed terrain ids before trap placement proceeds. |
| sub_42B680 | Trap_ClearTileOwnerMask | Function | Trap/Map | High | Single-purpose helper that zeros the trap-owner byte at `gameData + 576374 + 100 * row + column`. |
| sub_42B730 | Trap_GetTileOwnerMask | Function | Trap/Map | High | Returns either the raw one-byte trap owner mask for a tile or the bit corresponding to a specific player, matching every placement, rendering, and trigger caller. |
| sub_42B770 | Trap_TriggerAtStackTile | Function | Trap/Combat | High | Reveals nearby trap bits for detector-capable stacks, checks the triggered tile mask under the moving stack, shows the `aWpad_pul` trap message for players with detection, applies `Trap_HurtUnit`, and then clears the trap tile. |

## Deferred / Ambiguous
- `gameData + 147139` vs `gameData + 147143` are now clearly two different player-index slots, but the exact naming split is still deferred: one tracks the active turn owner while the other tracks the player whose camera/UI view should be restored.
- `MapTileRecord` offset `+2` is definitely a secondary overlay word used by terrain-edge rendering, but its exact semantic split between coast edge, decorative overlay, and passability metadata remains ambiguous.
- The `sub_4100B0(...) >= 3` gate inside `Trap_TriggerAtStackTile` almost certainly means trap detection capability, but the underlying slot-state scale returned by `sub_4100B0` is not yet named safely enough to promote.

## Batch 14 – Shared View-State Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| `gameData + 140000` / `+140004` | `MAP_WIDTH_TILES` / `MAP_HEIGHT_TILES` | Helper | Shared State | High | Map load derives these values by scanning the 14-byte tile grid until `0xFFFF`, while scrolling and rendering clamp viewport coordinates against them as world bounds. |
| `gameData + 140008` / `+140012` | `MAP_VIEW_LEFT` / `MAP_VIEW_TOP` | Helper | Shared State | High | Keyboard scrolling, recentering, and turn handoff all treat these dwords as the current top-left map camera tile. |
| `PLAYER_DATA(player) + 140039` / `+140043` | `PLAYER_CAMERA_LEFT(player)` / `PLAYER_CAMERA_TOP(player)` | Helper | Shared State | High | The end-turn flow stores the outgoing camera here, save/load persists the same values, and the per-player setup routine seeds them from each faction's first building position. |
| `gameData + 147139` / `+147143` | `TURN_OWNER_PLAYER_INDEX` / `VIEWED_PLAYER_INDEX` | Helper | Turn Flow | High | `Game_AdvanceToNextPlayerTurn` writes the acting player into `+147139`, switches `+147143` only for human-controlled turns, and restores the camera from `PLAYER_CAMERA_*` using the viewed-player slot. |
| `gameData + 140000 .. +140012`, `+147139`, `+147143` | `WorldViewState` | Recovered Struct | Shared State | High | These offsets travel together through map-load initialization, save/load persistence, scrolling, and turn rotation, forming a stable shared-state region for world dimensions, camera origin, and active/viewed player ownership. |

## Batch 15 – Spawn and Trap Helper Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_41F0C0 | Building_FindFreeAdjacentSpawnTile | Function | Building/Garrison | High | The routine logs `Building_FindFreePlaceNear()`, scans the 12 neighboring offsets around a building, rejects occupied tiles, and returns the first tile whose movement helper accepts the building owner's spawn template. |
| sub_42B6A0 | Trap_HurtStack | Function | Trap/Combat | High | The helper logs `Trap_HurtUnit`, iterates the occupied stack slots, applies a randomized damage roll derived from `Unit_CalcEffectivenessB`, removes dead slots, and compacts/finalizes the stack afterward. |
| sub_44C2A0 | Game_InitPlayerViewState | Function | Shared State | High | Seeds each active player's saved camera from the first owned building, picks the first human player as `VIEWED_PLAYER_INDEX`, picks the first active player as both `g_CurrentPlayerIndex` and `TURN_OWNER_PLAYER_INDEX`, and is reused after map setup and scenario load. |

## Batch 16 – Building Transfer and Garrison Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_412520 | Unit_CreateNearbyUnitGroup | Function | Unit Lifecycle | High | The debug string already names the routine, and the body finds a free neighboring tile, calls `Unit_Create`, copies a supplied squad fragment into the new stack, and links the resulting army fact. |
| sub_41F1A0 | Building_Transfer | Function | Building/Garrison | High | The function logs `Building_Transfer`, temporarily clears the source building footprint from tile occupancy, creates a temporary transport stack (`31` or `32`), copies a percentage of the stored resource or occupants into it, and either moves it near the target building or spawns it on an adjacent tile. |
| sub_43E0C0 | Building_HasFreeAdjacentExitTile | Function | Building/Garrison | High | The helper only scans the building's legal neighbor pattern and returns true when it finds an in-bounds empty tile whose terrain is traversable by the building owner's unit template; it is a pure exit-tile availability probe. |
| sub_43E160 | Building_UnitsLeave | Function | Building/Garrison | High | The debug string names the routine, and the body selects a free adjacent exit tile, creates a new stack there, copies the requested garrison slots out of the building record, updates garrison-change state, and refreshes vision. |
| sub_43E4B0 | Building_CountFreeGarrisonSlots | Function | Building/Garrison | High | The function iterates the 12 building garrison slots (or 10 for smaller buildings) and counts entries whose unit type at offset `+18` is `-1`, so it clearly returns the number of free garrison slots. |
| aUnit_createnea | aUnitCreateNearbyUnitGroup | Helper | Unit Lifecycle | High | String variable rename follows the confirmed `Unit_CreateNearbyUnitGroup` debug label and keeps logging identifiers aligned with the recovered function name. |
| aBuilding_findf | aBuildingFindFreePlaceNear | Helper | Building/Garrison | High | The string literal is the exact log text used by `Building_FindFreeAdjacentSpawnTile`, so the helper name now describes the emitted trace rather than a truncated decompiler token. |
| aBuilding_trans | aBuildingTransfer | Helper | Building/Garrison | High | String helper backing the `Building_Transfer` debug log. |
| aBuilding_units | aBuildingUnitsLeave | Helper | Building/Garrison | High | String helper backing the `Building_UnitsLeave` debug log. |
| gameData + 509674 + 467 * buildingIndex | BuildingRecord | Recovered Struct | Building/Garrison | Medium | Building helpers repeatedly treat this 467-byte region as a stable per-building record with tile/owner header bytes, 12 garrison slots at `+18`, addon ids at `+402`, upgrade/resource state at `+421/+429/+438/+444`, and garrison-change bookkeeping near `+463`. |

## Deferred / Ambiguous
- `BuildingRecord` offset `+4` clearly switches neighbor masks, addon rules, and capture/build handling, but the exact enum behind values `0/1/2` is still not named safely enough.
- `BuildingRecord` offsets `+421` and `+429` behave like a staged castle or fortification upgrade level plus cooldown timer, but the exact feature being upgraded is still UI- and rules-coupled, so those fields remain descriptively unnamed.
- `BuildingRecord` offset `+438` is a stored spendable pool used by transfer, addon purchase, and per-turn accrual logic; it is likely a building-local treasury or stockpile, but the economy resource name remains deferred.

## Batch 17 – Building Production Licence Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_43E850 | Building_BuyUnitLicence | Function | Building/Garrison | High | The debug string names the routine, and the body spends from the building-local pool at `+438`, then appends a unit-type id into the installed licence/add-on array at `+402`. |
| sub_43E940 | Building_RemoveUnitLicence | Function | Building/Garrison | High | The function logs `Building_RemoveUnitLicence`, stops current production when the selected licence matches, and then removes the target type id from the `+402` licence array. |
| sub_43E9A0 | Building_SetUnitProduction | Function | Building/Garrison | High | The debug string names the routine, and the body stores a selected licence slot at `+414` plus the corresponding production duration at `+415`. |
| sub_43EA10 | Building_StopUnitProduction | Function | Building/Garrison | High | Single-purpose helper named by its debug string; it clears the selected production slot at `+414`. |
| sub_43EA30 | Building_TrainUnit | Function | Building/Garrison | High | The debug string names the function, and it writes per-slot task bits into `BuildingRecord + 390 + slotIndex`, starting a training task for the chosen garrison slot. |
| sub_43EAD0 | Building_RepairUnit | Function | Building/Garrison | High | The debug string names the function, and it writes the complementary repair task bits into the same per-slot task byte used by training. |
| aBuilding_buyun | aBuildingBuyUnitLicence | Helper | Building/Garrison | High | String helper backing the `Building_BuyUnitLicence` debug log. |
| aBuilding_remov | aBuildingRemoveUnitLicence | Helper | Building/Garrison | High | String helper backing the `Building_RemoveUnitLicence` debug log. |
| aBuilding_setun | aBuildingSetUnitProduction | Helper | Building/Garrison | High | String helper backing the `Building_SetUnitProduction` debug log. |
| aBuilding_stopu | aBuildingStopUnitProduction | Helper | Building/Garrison | High | String helper backing the `Building_StopUnitProduction` debug log. |
| aBuilding_train | aBuildingTrainUnit | Helper | Building/Garrison | High | String helper backing the `Building_TrainUnit` debug log. |
| aBuilding_repai | aBuildingRepairUnit | Helper | Building/Garrison | High | String helper backing the `Building_RepairUnit` debug log. |

## Batch 18 – Building Garrison Task Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_4558D0 | Building_UnitsLeaveReadyGarrisonSlots | Function | Building/Garrison | Medium | Collects up to five occupied garrison slots whose morale/condition byte is `100` and whose task bits are idle, then forwards that slot list into `Building_UnitsLeave` if the building has a legal exit tile. |
| sub_4559D0 | Building_HasTrainableIdleGarrisonUnit | Function | Building/Garrison | Medium | Returns true when the building contains at least one occupied garrison slot with `status & 3 < 2` and no active task bits, which matches the eligibility check later used before starting training. |
| sub_455A50 | Building_HasRepairableIdleGarrisonUnit | Function | Building/Garrison | Medium | Returns true when the building contains at least one occupied garrison slot below 50 condition with no active high task bits, matching the later repair starter. |
| sub_455AD0 | Building_StartTrainingIdleGarrisonUnits | Function | Building/Garrison | Medium | Walks every occupied garrison slot and starts `Building_TrainUnit` on those whose trainability and idle-task predicates pass, so it is an AI or bulk helper for launching training jobs. |
| sub_455B50 | Building_StartRepairIdleGarrisonUnits | Function | Building/Garrison | Medium | Bulk counterpart to the above that starts `Building_RepairUnit` on occupied, damaged, idle garrison slots. |
| sub_455BD0 | Building_UnitsLeaveByUnitType | Function | Building/Garrison | High | Finds the first garrison slot whose unit type id matches `a2`, builds a one-element leave list, and passes it to `Building_UnitsLeave` when an exit tile is available. |

## Batch 19 – Unit Type Metadata Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| off_512568 | g_UnitTypeMetadataRecords | Global | Unit Types/Stats | High | The base is indexed as `22 * unitType` (88 bytes per type) and serves as more than a name table: field 0 is a localized-name pointer array, field `+4` is the sprite-folder pointer, and bytes `+29..+37` store the per-terrain movement profile merged by stack movement code. |
| dword_51257A | g_UnitTypeFlags | Global | Unit Types/Stats | High | This overlapping dword field lives inside the recovered 88-byte metadata record. Bit0 consistently marks airborne units across render order, movement sounds, death handling, and the “all units flying” predicate; another bit still controls the 6-vs-10 seed at slot `+11`. |
| sub_413920 | UnitStack_BuildMergedTerrainMoveProfile | Function | Unit Types/Stats | High | Iterates every occupied slot, loads the owning unit type's metadata record, and merges bytes `+29..+37` into a temporary profile consumed by world-movement helpers. |
| sub_422BA0 | UnitStack_HasOnlyFlyingUnits | Function | Unit Types/Stats | High | Walks the occupied slots and returns true only when every unit type has `g_UnitTypeFlags bit0` set, matching the airborne-only predicate used by pathing/UI helpers. |
| data segment @ 0x512568 stride 88 | UnitTypeMetadataRecord | Recovered Struct | Unit Types/Stats | High | The decompiler emitted several overlapping globals (`g_UnitTypeMetadataRecords`, `g_UnitSpriteFolders`, `g_UnitTypeFlags`, `byte_512570`+) from one record family. Code evidence proves a stable 88-byte per-type layout with localized names, sprite folders, flags, animation timing, and terrain move costs. |

## Batch 20 – Unit Roster Correlation Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| *(new constant)* | UNIT_TYPE_RAM | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_512468` (`Taran / Rammbock`) with folder `taran`, and ordinary melee code explicitly excludes type `13`, proving the earlier cannon-at-13 guess was wrong. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_CANNON | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_512444` (`Armata / Cannon`) with folder `armat`, fixing cannon at type `14`. | asm, exe |
| *(new constant)* | UNIT_TYPE_FORESTER | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_512450` (`Leśnik / Forester`) with folder `lesn`, and the type is created directly by three nearby `Unit_Create(0xFu, ...)` call sites. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_GORAL | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_5123E4` (`Góral / Highlander`) with folder `goral`, placing it at type `16` rather than the earlier folder-order-only guess. | asm, exe |
| *(new constant)* | UNIT_TYPE_ELEPHANT | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_5124C8` (`Słoń / Elephant`) with folder `slon`, placing it at type `19`. | asm, exe |
| *(new constant)* | UNIT_TYPE_FLY | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_512534` (`Ważka / Fly / Riesenlibelle`) with folder `wazka`, and movement audio groups type `29` with other looped movers. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_DRAGON | Helper | Unit Types/Stats | High | The asm record xrefs pair `off_512480` (`Smok / Dragon / Drachen`) with folder `smok`, moving the dragon id from the earlier speculative `29` to confirmed `30`. | asm, exe |

## Batch 21 – Unit Move Sound Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| off_5125B9 | g_UnitMoveSoundStems | Global | Unit Audio / Unit Types | High | Both movement-sound helpers index this overlapping record field by `22 * type` and build `sfx\\ruchy\\<stem>...` paths from it; `clash95.asm` shows the first entry as `b_lekkie\\krokb`. | c, asm |
| byte_5125BD | g_UnitMoveSoundVariantCounts | Table | Unit Audio / Unit Types | High | Step-based movement audio wraps `g_CurrentUnitMoveSoundVariant` modulo this overlapping per-type byte field. | c, asm |
| byte_5125BE | g_UnitMoveSoundBaseVolumes | Table | Unit Audio / Unit Types | High | Both world and battle movement-audio paths pass this overlapping per-type byte into `CSS_PlaySound` as the playback volume. | c, asm |
| dword_543CA8 | g_CurrentUnitMoveSoundHandle | Global | Unit Audio | High | Only the movement-audio start/stop helpers read and write this symbol, always as the active sound handle passed to `CSS_StopSound` / `CSS_SetSoundLoop`. | c |
| dword_543CAC | g_CurrentUnitMoveSoundVariant | Global | Unit Audio | High | The same helpers use this value as the current alternating step index and reset it whenever the moving unit type changes. | c |
| dword_543CB0 | g_CurrentUnitMoveSoundTypeId | Global | Unit Audio | High | The movement-audio helpers cache the currently sounding unit type here to avoid restarting looped sounds or to reset the step variant when the type changes. | c |
| sub_4415A0 | BattleMap_GetMoveSoundSurfaceClass | Function | Unit Audio / Battle Map | Medium | The function maps a battle-map tile id through `byte_517318` and is only used to choose the `p/t/d`-style movement-sound suffix in battle movement audio. | c, asm |
| sub_441F00 | Audio_PlayWorldMapUnitMoveSound | Function | Unit Audio / World Map | High | Called from the world movement animation loop; it builds `sfx\\ruchy\\...` paths, chooses airborne vs terrain-dependent suffixes, and loops siege-like movers. | c, asm |
| sub_442290 | Audio_PlayBattleMapUnitMoveSound | Function | Unit Audio / Battle Map | High | Battle-only counterpart to the world helper; it uses `BattleMap_GetMoveSoundSurfaceClass` instead of `Map_DestroyTile` when selecting footstep suffixes. | c, asm |
| sub_4425B0 | Audio_StopUnitMoveSound | Function | Unit Audio | High | Thin helper that stops the active movement sound and clears the cached active unit type. | c |

## Batch 22 – Unit Action Sound Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_441A30 | Audio_PlayUnitActivateSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\activ1.wav?`, is called when selecting a new unit on both world and battle maps, and stores the handle later faded by the move-order helper. | c, asm |
| sub_441B00 | Audio_PlayUnitMoveOrderSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\go1.wav?`, fades the last activation sound, and is called immediately before unit movement execution on both world and battle maps. | c, asm |
| sub_441BE0 | Audio_PlayUnitRangedAttackSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\strzal.wav` and is triggered on ranged-attack animation frames. | c, asm |
| sub_441C80 | Audio_PlayUnitHitSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\dostal.wav` and is triggered when the target takes a hit. | c, asm |
| sub_441D20 | Audio_PlayUnitDeathSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\dead.wav` and is called at the start of the battle death animation path. | c, asm |
| sub_441DC0 | Audio_PlayUnitMeleeAttackSound | Function | Unit Audio | High | The helper builds `sfx\\oddzialy\\<unit>\\walka.wav` and is triggered on the designated combat-impact frame during melee attack resolution. | c, asm |

## Batch 23 – Unit Audio Toggle State Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| dword_5174D4 | g_UnitSoundsEnabled | Global | Unit Audio | High | Every per-unit sound helper gates on this flag, and the toggle helpers plus the settings-apply path only set it to `0` or `1`. | c, asm |
| dword_543CA4 | g_LastUnitActivateSoundHandle | Global | Unit Audio | High | `Audio_PlayUnitActivateSound` stores the returned handle here, and `Audio_PlayUnitMoveOrderSound` immediately fades that same handle out before playing the move-order cue. | c, asm |
| sub_441A10 | Audio_EnableUnitSounds | Function | Unit Audio | High | Single-purpose helper that sets `g_UnitSoundsEnabled = 1`. | c, asm |
| sub_441A20 | Audio_DisableUnitSounds | Function | Unit Audio | High | Single-purpose helper that sets `g_UnitSoundsEnabled = 0`. | c, asm |

## Batch 24 – Special Cargo And Prisoner Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| *(new constant)* | UNIT_TYPE_GOLD_CARGO | Helper | Unit Types / Special Entries | High | Type `31` resolves to `gold`, is excluded from `UnitStack_HasNormalCombatUnits`, and is checked by dedicated stack helpers rather than ordinary battle code. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_PEASANT_CARGO | Helper | Unit Types / Special Entries | High | Type `32` resolves to `peas`, is excluded from normal-combat checks, and `UnitStack_NormalizePeasantCargo` rebuilds it as stack payload. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_PRISONER_FOOT | Helper | Unit Types / Prisoners | Medium | Type `33` uses `specm`, shares the `Dowódca / Tactician / Soldat` label triplet, and is extracted into the prisoner pipeline on capture. | c, asm, exe |
| *(new constant)* | UNIT_TYPE_PRISONER_MOUNTED | Helper | Unit Types / Prisoners | Medium | Type `34` uses `speck`, shares the same localized-name triplet, and follows the same prisoner-only flow with cavalry-like movement assets. | c, asm, exe |
| sub_412000 | UnitSlots_ExtractSpecialEntries | Function | Unit Lifecycle / Special Entries | High | Copies only types `31..34` into a side buffer while compacting the source slot array, matching the pre-capture special-entry extraction step. | c |
| sub_4120B0 | UnitSlots_AppendEntries | Function | Unit Lifecycle / Special Entries | High | Finds the first empty slot and appends all entries from a temporary 31-byte slot buffer back into the squad. | c |
| sub_412100 | UnitStack_HasNormalCombatUnits | Function | Unit Lifecycle / Special Entries | High | Returns true only if the stack contains at least one slot whose type is not `31..34`, which is exactly the “has ordinary combatants” predicate used by movement, capture, and UI code. | c |
| sub_412170 | UnitStack_HasGoldCargo | Function | Unit Lifecycle / Special Entries | High | Scans squad slots for type `31` only. | c |
| sub_4121A0 | UnitStack_HasPeasantCargo | Function | Unit Lifecycle / Special Entries | High | Scans squad slots for type `32` only. | c |
| sub_4121D0 | UnitStack_NormalizePeasantCargo | Function | Unit Lifecycle / Special Entries | High | Sums all type-`32` slot payloads, removes the old entries, and recreates normalized peasant-cargo slots in capped chunks. | c |
| sub_412300 | UnitStack_CaptureDefeatedStack | Function | Unit Lifecycle / Capture | High | Logs capture, strips prisoner entries into the prisoner queue, flips ownership of captured slots, normalizes peasant cargo, and merges or preserves the defeated stack under the winner. | c |
| sub_412B60 | UnitStack_HasPrisonerUnits | Function | Unit Lifecycle / Prisoners | High | Returns true only when a squad contains type `33` or `34`. | c |
| sub_41A960 | UI_DrawSpecialUnitInfoPane | Function | UI / Unit Info | High | Dedicated info window path for types `31..34`, with alternate icon mapping and the localized-name lookup from the unit-type metadata table. | c |
| sub_44E7A0 | Prisoner_QueueCapturedUnit | Function | Prisoners | High | Debug log string is `Prisoner_AddToInWay`, and the function appends captured type `33/34` entries into the per-player queue later drained by `Prisoner_SetInCastles`. | c, asm |
| sub_44E850 | Building_FindFreePrisonerSlot | Function | Prisoners / Buildings | High | Scans the three 6-byte prison cells at `building + 445` and returns the first free index or `-1` if full. | c |
| sub_44EB70 | BuildingPrisoner_SetAction | Function | Prisoners / Buildings | High | `clash95.asm` exposes the debug string `Building_SetPrisonerAction(0x%08x,%d,%d)`, and the function writes the pending action byte at `building + 445 + 6 * slot + 3`. | c, asm |
| sub_44EBA0 | BuildingPrisoner_GetAction | Function | Prisoners / Buildings | High | Reads back the pending action byte from the same prison-cell field. | c |
| sub_44F1E0 | Building_CreatePrisonerUnit | Function | Prisoners / Buildings | High | Debug log string is `Building_CreateSpecial`, and every recovered caller uses it to insert a type `33/34` prisoner unit into a building garrison slot. | c, asm |
| sub_44F350 | Prisoner_NewTurn | Function | Prisoners | High | Debug log string is `Prisoner_NewTurn`, and the function advances held-prisoner timers, auto-assigns late orders, then dispatches behead/torture/pay behavior for each prison cell. | c |
| sub_44F4E0 | Building_CountPrisoners | Function | Prisoners / Buildings | High | Counts occupied prison cells by scanning the three 6-byte entries starting at `building + 445`. | c |
| sub_43EB80 | Building_CountPrisonerGarrisonEntries | Function | Buildings / Prisoners | High | Counts only type `33/34` entries inside the building garrison array, i.e. the prisoner-class special garrison occupants. | c |
| sub_43EBC0 | Building_CountSpecialGarrisonEntries | Function | Buildings / Special Entries | High | Counts all type `31..34` entries inside the 12-slot building garrison. | c |
| sub_43EC10 | Building_HasPrisonerGarrisonEntries | Function | Buildings / Prisoners | High | Returns true when the building garrison contains at least one type `33` or `34` entry. | c |
| PLAYER_DATA(player) + 141381 + 6 * slot | PlayerPrisonerTransferQueue | Recovered Struct | Prisoners | High | `Prisoner_QueueCapturedUnit` appends 10 fixed-size entries here, and `Prisoner_SetInCastles` drains them into nearby castles using the stored capture coordinates. | c |
| BuildingRecord + 445 + 6 * slot | BuildingPrisonerSlot | Recovered Struct | Prisoners / Buildings | High | Execution, torture, ransom, and prisoner-new-turn helpers all operate on the same three 6-byte cells embedded in the building record. | c |

## Batch 25 – Prisoner Action And Targeting Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_43F240 | Building_GetTotalValue | Function | Buildings / Economy | High | Sums stored resources, level bits, flag-based flat values, and add-on costs, then feeds both `AI_TickNationPostTurn` and the “richest hidden castle” torture outcome. | c, asm |
| sub_44E880 | BuildingPrisoner_RecalculateRansomValue | Function | Prisoners / Buildings | High | Recomputes prison-cell word `+4` from a nation-strength-derived random value, rounds it to tens, and `Prisoner_Pay` later spends that exact field. | c |
| sub_44EC80 | Building_IsVisibleToPlayer | Function | Buildings / Visibility | High | Tests all four tiles of the building footprint with the player-visibility helper, so it is a building-level visibility predicate rather than a generic boolean. | c |
| sub_44ECF0 | Prisoner_FindRichestHiddenEnemyCastle | Function | Prisoners / Torture | High | Searches enemy-owned castles that are not visible to the interrogating player and selects the one with the highest `Building_GetTotalValue`, matching the torture text about revealing the richest castle. | c |
| sub_44EDB0 | Prisoner_FindAnyHiddenEnemyCastle | Function | Prisoners / Torture | High | Returns the first enemy-owned castle that is hidden from the interrogating player, matching the torture text about revealing one of the king's castles. | c |
| sub_44EE20 | Prisoner_FindAnyHiddenEnemyUnitStack | Function | Prisoners / Torture | High | Returns the first enemy-owned hidden field stack, matching the torture outcome that reveals one enemy unit. | c |
| sub_44EEE0 | Map_RevealTilesInRadius2ForPlayer | Function | Map / Visibility | High | Stamps visibility around a center point in a radius-2 disk and is used immediately after torture-target discovery to reveal the selected target area. | c |
| sub_44EFA0 | Prisoner_Torture | Function | Prisoners | High | The asm log string is `Prisoner_Torture(0x%08x,%d)`, and the function dispatches the five torture outcomes: richest hidden castle, hidden castle, hidden unit, death without intel, or resistance. | c, asm |
| sub_44F260 | Prisoner_Pay | Function | Prisoners | High | The asm log string is `Prisoner_Pay(0x%08x,%d)`, and the function spends the prison cell's ransom value, converts the prisoner into a friendly special garrison unit, and removes the prison entry. | c, asm |

## Batch 26 – Map Loading And gameData State Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_44AD60 | PlayerRuntimeState_ResetDefaults | Function | gameData / Player Runtime | High | Resets one 1423-byte player block, restores the default ruler name at `+4`, zeros camera/controller fields, and clears the head byte of each embedded 6-byte prisoner queue entry. | c, asm |
| sub_44AE10 | Game_ResetPlayerRuntimeStateByIndex | Function | gameData / Player Runtime | High | Thin wrapper that applies `PlayerRuntimeState_ResetDefaults` to `gameData + 140024 + 1423 * playerIndex`. | c |
| loadMap | Map_LoadFromFile | Function | Map Loading | High | Loads `maps\\<name>.map`, copies three tile layers into the 14-byte tile record, stamps buildings, derives map dimensions, resets mission/view state, and clears unit/building occupancy tables. | c, asm, map |
| loadMultiplayerMaps | Scenario_LoadMultiplayerMapAndSeedPlayers | Function | Map Loading / Multiplayer | High | Formats `multi%d.map`, calls the raw map loader, copies five player runtime records into gameData, then seeds castles/units from fixed per-map starting-coordinate tables. | c, asm, map |
| sub_460360 | Scenario_LoadMissionByIndex | Function | Map Loading / Campaign | High | Jump-table dispatcher keyed by the active mission index register that loads `k_mapa*.map` / `p_mapa*.map` files and applies the mission-specific scripted setup. | c, asm |
| sub_460370 | Scenario_LoadMissionByIndexAndPlay | Function | Map Loading / Campaign | Medium | Preserves view-state bytes, optionally plays the mission-complete interlude, invokes `Scenario_LoadMissionByIndex`, then starts `PlayGame` on the selected mission. | c, asm |
| off_5180C0 | g_MissionStatusTextsByLanguage | Table | Map Loading / Campaign | High | Indexed as `3 * ACTIVE_MISSION_INDEX + language` by `UI_ShowMissionStatusPanel`, so it is the localized mission objective text table. | c |
| off_5181B0 | g_MissionStatusFormatsByLanguage | Table | Map Loading / Campaign | High | Three-entry localized format table used to render `Mission %d` status popups. | c |
| aMaps_1 | aMapsDirectory | Helper | Map Loading | High | Constant prefix copied before every `.map` filename in `Map_LoadFromFile`. | c, asm |
| dword_518938 | g_MultiplayerStartRows | Table | Map Loading / Multiplayer | High | `Scenario_LoadMultiplayerMapAndSeedPlayers` indexes this table alongside the companion column table to position each seeded player/castle pair. | c, asm |
| dword_51893C | g_MultiplayerStartColumns | Table | Map Loading / Multiplayer | High | Companion start-column table paired with `g_MultiplayerStartRows` during multiplayer map seeding. | c, asm |
| gameData + 140024 + 1423 * player | PlayerRuntimeState | Recovered Struct | gameData / Player Runtime | High | Campaign and skirmish code consistently treat this as a per-player runtime block containing enable/name/controller/camera state plus the embedded prisoner transfer queue and queen bytes. | c, asm |
| gameData + 140017 | active_mission_index | Recovered Struct Field | gameData / World Session | High | Mission status UI, mission advancement, and the campaign mission jump table all use this dword as the current scripted mission id, with `-1` meaning free/skirmish map. | c, asm |

## Batch 27 – Unit Slot Runtime And Effective Stat Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40FDB0 | UnitSlot_CalcActionPointsFromFatigue | Function | Unit Stats / Runtime Slot | High | Reads the per-type base AP table, then applies the 80/90/100 fatigue thresholds from slot `+10` to derive the runtime action-point budget used at the start of each turn. | c, asm |
| sub_40FE60 | UnitSlot_GetBaseActionPoints | Function | Unit Stats / Runtime Slot | High | Thin helper that returns the unmodified base AP entry from the per-type table for the slot's unit type. | c, asm |
| sub_4118A0 | UnitSlot_ShouldGainFatigueFromLowActionPoints | Function | Unit Stats / Runtime Slot | Medium | Predicate returns true only for slots with AP `<= 3` and no low-morale refusal flag, matching the new-turn path that adds fatigue to overextended units. | c |
| sub_4118C0 | UnitSlot_CanRecoverFatigue | Function | Unit Stats / Runtime Slot | High | Predicate returns true only when the spent-turn flag bit is clear, and the new-turn handler uses it to decide which slots recover fatigue. | c, asm |
| sub_4118D0 | UnitSlot_HasSevereFatigue | Function | Unit Stats / Runtime Slot | High | Predicate checks `fatigue >= 80`, exactly matching the threshold used by the new-turn morale-loss path. | c, asm |
| sub_4127F0 | UnitStack_AdjustFatigueByPredicate | Function | Unit Stats / Runtime Slot | High | Iterates stack slots, filters through a predicate, skips cargo/prisoner entries, adjusts slot `+10`, clamps to `0..100`, and relinks the army fact. | c, asm |
| sub_4128E0 | UnitStack_AdjustMoraleByPredicate | Function | Unit Stats / Runtime Slot | High | Iterates stack slots, filters through a predicate, skips cargo/prisoner entries, adjusts slot `+11`, clears the refusal bit on morale gains, clamps to `0..20`, and relinks the army fact. | c, asm |
| sub_412A30 | UnitStack_SetSpentTurnFlag | Function | Unit Stats / Runtime Slot | High | Sets bit `0x2` in each occupied slot's state-flags byte, and combat/new-turn code uses that bit to suppress fatigue recovery after a spent turn. | c, asm |
| sub_412A60 | UnitStack_ClearSpentTurnFlag | Function | Unit Stats / Runtime Slot | High | Clears bit `0x2` in each occupied slot's state-flags byte during the new-turn refresh pass. | c, asm |
| sub_412AF0 | UnitStack_HasLowMoraleUnit | Function | Unit Stats / Runtime Slot | High | Scans occupied slots for state-flags bit `0x4`, which is set by `Unit_CheckLowMorale` when a unit refuses orders. | c, asm |
| UnitStats_CalcMeleeAttack | UnitStats_CalcEffectiveMeleeAttack | Function | Unit Stats | High | The helper combines stance bits, base melee attack, morale, and current health percent, so `effective` is more accurate than the generic `Calc`. | c, asm |
| UI_IconIndexFromStats | UnitStats_GetMeleeIconIndex | Function | Unit Stats / UI | High | Uses the same melee inputs as the effective melee helper but omits health scaling, matching a UI icon-strength index rather than a generic UI helper. | c, asm |
| UnitStats_CalcRangedAttack | UnitStats_CalcEffectiveRangedAttack | Function | Unit Stats | High | Combines stance bits, base ranged attack, morale, current health percent, and the slot `+22` ranged-state bit, making it the effective ranged-attack helper. | c, asm |
| UnitStats_CalcDamagePerHit | UnitStats_CalcEffectiveDamagePerHit | Function | Unit Stats | High | Uses base damage, morale, and current health percent to produce the effective per-hit damage value. | c, asm |
| UnitStats_CalcSiegeAttack | UnitStats_CalcEffectiveSiegeAttack | Function | Unit Stats | Medium | Mirrors the melee helper but swaps in the alternate siege/building attack table. | c, asm |
| byte_51257E | g_UnitTypeBaseMeleeAttack | Table | Unit Stats | High | Indexed by `88 * unitType` wherever standard melee capability or melee strength is needed. | c, asm |
| byte_51257F | g_UnitTypeBaseRangedAttack | Table | Unit Stats | Medium | Indexed by `88 * unitType` in ranged/projectile attack math and battle-targeting logic. | c, asm |
| byte_512580 | g_UnitTypeBaseActionPoints | Table | Unit Stats | High | Indexed by `88 * unitType` for slot initialization, AP refresh, and battle-map unit seeding. | c, asm |
| byte_512581 | g_UnitTypeBaseDamage | Table | Unit Stats | High | Indexed by `88 * unitType` in the direct damage-per-hit helpers. | c, asm |
| byte_512582 | g_UnitTypeMaxRange | Table | Unit Stats | High | Projectile distance checks compare against this table as the upper range limit. | c, asm |
| byte_512583 | g_UnitTypeMinRange | Table | Unit Stats | Medium | Projectile distance checks compare against this table as the lower dead-zone limit. | c, asm |
| byte_512584 | g_UnitTypeBaseSiegeAttack | Table | Unit Stats | Medium | Alternate attack helper indexes this table for siege/structure contexts. | c, asm |
| gameData + 147174 + 6 + 31 * slot | UnitSlotRecord | Recovered Struct | Unit Stats / Runtime Slot | High | Repeated stable accesses recover a 31-byte per-slot record with type, owner, AP, health, fatigue, morale, stance bits, flags, and auxiliary state. | c, asm |
| UnitStackRecord.unit_slot_fields (old interpretation) | UnitSlotRecord.current_health_percent / fatigue / morale | Recovered Struct Field | Unit Stats / Runtime Slot | High | Cross-checking `UnitSlot_InitFromType`, `Unit_NewTurn`, combat formulas, and UI drawing overturned the earlier `morale_percent`/`veterancy` reading and established the true health/fatigue/morale split. | c, asm |

## Batch 28 – Technology Advancement And Building Tier Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| Building_CheckTechnology | Player_UpdateTechnologyLevelFromSettlements | Function | gameData / Buildings / Tech | High | Scans all owned type-1/type-2 settlements, counts how many have the five core add-on bits set, promotes player tech from 1 to 2 or 3 accordingly, then raises owned building low-tier bits to match. | c, asm |
| sub_41EF10 | Building_BuildBarracks | Function | Buildings / Tech | High | The debug string is `Building_BuildBarracks`, and the helper spends local building resources before setting add-on bit `0x02`. | c |
| sub_41EF80 | Building_BuildHospital | Function | Buildings / Tech | High | The debug string is `Building_BuildHospital`, and the helper spends local building resources before setting add-on bit `0x01`. | c |
| sub_41F020 | Building_BuildSmiths | Function | Buildings / Tech | High | The debug string is `Building_BuildSmiths`, and the helper spends local building resources before setting add-on bit `0x10`. | c |
| sub_41F850 | Building_CanUpgradeWall | Function | Buildings / Tech | High | Script host `CanUpgradeWall` points here, and the predicate checks upgrade stage, tier cap, and zero upgrade timer before allowing another wall tier step. | c, asm |
| sub_41F890 | Building_StartWallUpgrade | Function | Buildings / Tech | High | Paired with `Building_CanUpgradeWall`; it starts the timed wall-upgrade step by loading the stage-specific timer and deducting the corresponding stored-resource cost. | c |
| sub_4459A0 | UI_ShowTechnologyLevelUpIfChanged | Function | UI / Tech | High | Shows the localized technology-advance info window only when the player's current tech byte differs from the latched display byte, then copies the new value into the latch. | c |
| sub_455450 | Building_StartWallUpgradeByIndex | Function | Rules Host / Buildings | High | Thin index-based rules-host wrapper that forwards a building id into `Building_StartWallUpgrade`. | c |
| sub_4554B0 | Building_BuildSmithsByIndex | Function | Rules Host / Buildings | High | Thin rules-host wrapper that forwards the selected building into `Building_BuildSmiths`. | c |
| sub_455530 | Building_BuildBarracksByIndex | Function | Rules Host / Buildings | High | Thin rules-host wrapper that forwards the selected building into `Building_BuildBarracks`. | c |
| sub_455550 | Building_BuildHospitalByIndex | Function | Rules Host / Buildings | High | Thin rules-host wrapper that forwards the selected building into `Building_BuildHospital`. | c |
| sub_455580 | Building_GetTechnologyLevel | Function | Rules Host / Buildings | High | Rules host `PoziomTech` lands here, and the helper returns the low three technology bits from building offset `+444`. | c, asm |
| sub_4555A0 | Building_GetTypeId | Function | Rules Host / Buildings | High | Rules host `TypBudowli` lands here, and the helper returns building byte `+4`, the stable script-visible building type/class id. | c, asm |
| sub_455620 | Building_HasUnitProduction | Function | Rules Host / Buildings | High | Returns whether building offset `+414` is not `-1`, matching the `IsProduction` host predicate. | c, asm |
| sub_455650 | Building_CanUpgradeWallByIndex | Function | Rules Host / Buildings | High | Index-based rules-host wrapper for `Building_CanUpgradeWall`, corroborated by the `CanUpgradeWall` host-function registration. | c, asm |
| sub_455E80 | Building_IsProducingUnitType | Function | Rules Host / Buildings | High | Host function `IsProductionAny` lands here, and the helper checks whether the selected production slot exists and currently points at the requested unit licence/type id. | c, asm |
| PlayerRuntimeState + 47 | technology_level | Recovered Struct Field | gameData / Player Runtime | High | Absolute uses at `gameData + 140071 + 1423 * player` resolve to byte `+47` inside the 1423-byte player block; the field stores the player's current technology tier. | c, asm |
| PlayerRuntimeState + 48 | last_shown_technology_level | Recovered Struct Field | gameData / Player Runtime | High | The tech-advance popup helper compares byte `+48` against `+47`, then latches the new value after showing the message. | c |
| BuildingRecord + 4 | building_type_id | Recovered Struct Field | Buildings / Tech | High | Script host `TypBudowli` returns this byte, and value classes `1`/`2` are the settlement types used by technology-advancement rules. | c, asm |
| BuildingRecord + 416 | addon_flags | Recovered Struct Field | Buildings / Tech | High | Add-on builders set bits `0x01`, `0x02`, `0x04`, `0x08`, and `0x10`, and `Player_UpdateTechnologyLevelFromSettlements` requires all five bits for a fully developed settlement. | c |
| BuildingRecord + 444 | technology_level_bits | Recovered Struct Field | Buildings / Tech | High | Rules host `PoziomTech` returns the low three bits here, and settlement-tech advancement raises those bits across owned buildings when the player's tech increases. | c, asm |

## Batch 29 – Building Production Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_43E820 | Building_HasUnitLicence | Function | Buildings / Production | High | Scans the 12 entries at building offset `+402` for a matching unit type id, matching the purchased-licence roster used by buy/remove/select-production helpers. | c |
| Building_CanEquipAddon | Building_CanBuyUnitLicence | Function | Buildings / Production | High | The predicate gates unit-type purchase by building type, required technology tier, and add-on flags; the castle UI iterates candidate unit types through it, and rules host `Can-Buy-Licence` lands on the wrapper that forwards here. | c, asm |
| sub_455800 | Building_CanBuyUnitLicenceByIndex | Function | Rules Host / Buildings | High | Thin index-based rules-host wrapper that applies `Building_CanBuyUnitLicence` to a building id. | c, asm |
| sub_455850 | Building_FindUnitLicenceSlotIndex | Function | Rules Host / Buildings | High | Rules host `LicencjaIndex` lands here, and the helper returns the slot index inside the building's 12-entry licence roster for the requested unit type id. | c, asm |
| byte_5125AF | g_UnitTypeProductionTurns | Table | Unit Stats / Production | High | `Building_SetUnitProduction` seeds building byte `+415` from this per-type table, and the per-turn production resolver reloads the same value when production loops for AI-controlled buildings. | c |
| byte_5125B0 | g_UnitTypeProductionCost | Table | Unit Stats / Production | High | The per-turn production resolver checks and subtracts this per-type value from the building-local resource pool when a produced unit is inserted into the garrison. | c |
| BuildingRecord + 402 | unit_licence_type_ids[12] | Recovered Struct Field | Buildings / Production | High | `Building_BuyUnitLicence`, `Building_RemoveUnitLicence`, the production UI, and `Building_FindUnitLicenceSlotIndex` all treat this as a 12-entry roster of purchased unit-type licences. | c, asm |
| BuildingRecord + 414 | selected_unit_licence_slot_index | Recovered Struct Field | Buildings / Production | High | `Building_SetUnitProduction` stores the selected licence slot here, `Building_StopUnitProduction` clears it to `-1`, and per-turn production resolves the active unit type through this index. | c |
| BuildingRecord + 415 | production_turns_remaining | Recovered Struct Field | Buildings / Production | High | `Building_SetUnitProduction` seeds this countdown from `g_UnitTypeProductionTurns`, UI status panels display it, and the per-turn production resolver decrements it until unit creation. | c |

## Batch 30 – Player Faction And Port Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| PlayerRuntimeState + 27 | has_human_controller | Recovered Struct Field | gameData / Player Runtime | High | Rules logging prints `komputer` as `1 - value`, and UI/gameplay paths treat nonzero here as locally controlled/human-visible. | c |
| PlayerRuntimeState + 31 | ai_intelligence_level | Recovered Struct Field | gameData / Player Runtime | High | Rules logging prints this field as `inteligencja`, the player-stats UI chooses the head icon from it, and building production discounts use threshold checks on the same dword. | c |
| PlayerRuntimeState + 39 | is_christian_faction | Recovered Struct Field | gameData / Player Runtime | High | Rules logging prints `chrzesc` from this field, and many castle UI/resource paths switch between christian and pagan assets based on it. | c |
| PlayerRuntimeState + 43 | primary_castle_building_index | Recovered Struct Field | gameData / Player Runtime | Medium | Set when the player first creates or receives a type-2 castle while the field is `-1`, and cleared when that same building is captured. | c |
| gameData + 586374 .. +586394 | PortSupplyState | Recovered Struct | Port / Coastal | High | Port load, per-turn refresh, supply pickup, and UI rendering all operate on one contiguous six-dword state block holding port coordinates, arrival timing, ready state, shipment size, and shoreline refresh mode. | c |

## Batch 31 – Player Queen Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| Queen_DrawMoodPanel | Queen_DrawFavorPanel | Function | Queen / UI | High | The panel does not render a transient animation state; it renders the persistent `+1419` player field through the favor-text table, while separately overlaying the current whim icon from `+1420`. | c |
| g_QueenMoodTexts | g_QueenFavorTexts | Table | Queen / UI | Medium | The 10-state localized text table is indexed by the persistent queen relation byte at `PlayerRuntimeState + 1419`, including the `-1 -> 0` fallback, so `favor` matches the underlying progression better than a generic mood label. | c, exe |
| PlayerRuntimeState + 1419 | queen_favor_level | Recovered Struct Field | gameData / Player Runtime / Queen | High | `Queen_NewTurn` treats this byte as a persistent approval ladder: successful proposal or reward events set it to `5`, accepted whims raise it toward `9`, rejected whims lower it, value `1` triggers the queen-leaves path, and missing-castle cleanup forces it to `-1`. | c, exe |
| PlayerRuntimeState + 1420 | queen_whim_type | Recovered Struct Field | gameData / Player Runtime / Queen | High | `Queen_NewTurn` rolls this byte from `0..8`, and all three queen dialog helpers use it to select the whim/proposal sprite and localized request text. | c |
| PlayerRuntimeState + 1421 | next_review_turn | Recovered Struct Field | gameData / Player Runtime / Queen | High | `Queen_NewTurn` stores `GAME_TURN_COUNTER + rand(5..8)` here after each review/proposal outcome, and later gates the next queen event by comparing the current turn against this word. | c |
| PlayerRuntimeState + 1419 .. + 1422 | PlayerQueenState | Recovered Struct | gameData / Player Runtime / Queen | High | The final four bytes of each 1423-byte player block behave as one compact subrecord containing the persistent queen favor level, the current whim/request id, and the next review turn. | c |

## Batch 32 – Map Tile Animation Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40C5E0 | Map_InitAnimatedTileTransitionTables | Function | Map / Tile | High | Clears and repopulates the terrain/overlay transition tables that the world-map update loop uses to animate terrain, shoreline, and overlay tiles. The selected transition family depends on the unresolved shared byte at `gameData + 140016`, but the function's responsibility is still clear. | c |
| MapTileRecord + 6 | terrain_anim_next_tick | Recovered Struct Field | Map / Tile | High | The world-map update loop compares `Time_Now()` against this dword before advancing `terrain_tile_id` through `word_520738`, then stores the next deadline back into the same field. | c |
| MapTileRecord + 10 | overlay_anim_next_tick | Recovered Struct Field | Map / Tile | High | The same loop separately compares and rewrites this dword when advancing `overlay_tile_id` through its own transition table, proving an independent overlay-animation timer. | c |

## Batch 33 – Player Battle History Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| PlayerRuntimeState + 49 | had_battle_this_turn | Recovered Struct Field | gameData / Player Runtime / Combat | High | Set by multiple battle-resolution exits and then consumed by the end-of-turn flow to decide whether the battle-free-turn counter should reset. | c |
| PlayerRuntimeState + 53 | turns_without_battle | Recovered Struct Field | gameData / Player Runtime / Combat | High | Incremented once per turn when no battle occurred, reset after combat, and compared against the `GodAnger` trigger threshold. | c |
| PlayerRuntimeState + 1417 | battle_record_score | Recovered Struct Field | gameData / Player Runtime / Combat | High | Army and castle battle outcomes increment the winner and decrement the loser through this word, and the player-statistics screen later graphs the same value as its third nation metric. | c |

## Batch 34 – World Theme Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_441720 | Audio_PlayWorldMapMusicByTheme | Function | Audio / World Map | High | Builds `data\\mainmap%d.wav` and `sfx\\music\\mainmap%d.wav` from the incoming theme id, then starts the looping strategic-map music track. | c, asm, exe |
| sub_4419A0 | Audio_EnableWorldMapMusic | Function | Audio / World Map | High | If world-map music is currently disabled, flips the enable flag on and immediately restarts the strategic-map loop using the packed world-theme byte from `gameData + 140016`. | c |
| sub_4419D0 | Audio_DisableWorldMapMusic | Function | Audio / World Map | High | Stops the active strategic-map music loop and clears the world-map music enable state. | c |
| sub_4419F0 | Audio_SetMusicEnabled | Function | Audio / Options | Medium | Pure setter that flips the shared music-enabled flag on without starting playback; used by options/menu code before a separate playback path runs. | c |
| sub_441A00 | Audio_SetMusicDisabled | Function | Audio / Options | Medium | Pure setter that flips the shared music-enabled flag off without stopping an already-playing loop; used by options/menu code as a state latch. | c |
| WorldViewState + 16 | world_theme_index | Recovered Struct Field | gameData / World View | High | One packed byte fans out into strategic-map music selection, `buildin1/2/3.s32` atlas choice, and three tile-transition/ambient visual families; debug/test setup writes values `0`, `1`, and `2` directly. | c, asm, exe |

## Batch 35 – Player Exploration Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40ED70 | PlayerExploration_RevealAllTiles | Function | Map / Exploration | High | Iterates 100 rows by 100 columns and OR-sets every bit in the player's 13-byte-per-row exploration slice, matching a full-map reveal helper. | c, asm |
| sub_40EDE0 | PlayerExploration_RevealTile | Function | Map / Exploration | High | Reveals one previously unexplored tile in the player's packed bitmap, repaints it immediately, and recursively fills one-tile gaps toward already explored neighbors so newly revealed circles stay connected. | c, asm |
| sub_40F060 | PlayerExploration_IsTileExplored | Function | Map / Exploration | High | Bounds-checks row/column, then tests one bit from the player's 13-byte-per-row bitmap at `PlayerRuntimeState + 57`; many gameplay paths use it as the canonical explored-vs-unexplored predicate. | c, asm |
| sub_40F0C0 | PlayerExploration_GetFogBorderVariant | Function | Map / Exploration | High | Returns `-1` for already explored tiles, `0` for fully hidden tiles, and otherwise computes a 1..14 fog-border shape index from the eight neighboring exploration bits. | c |
| Building_IsVisibleToPlayer | Building_IsExploredByPlayer | Function | Buildings / Exploration | High | The helper only checks whether any building-footprint tile is marked explored in the player's bitmap; prisoner search code uses it to distinguish hidden versus discovered castles. | c |
| PlayerRuntimeState + 57 | explored_tile_bits[100][13] | Recovered Struct Field | gameData / Player Runtime / Exploration | High | A stable 1300-byte slice inside each 1423-byte player record is accessed as `13 * row + (column >> 3)`, revealing and testing one bit per map tile across a fixed 100x100 grid. | c, asm |

## Batch 36 – Map Mode Struct Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40DC10 | MapMode_UpdateCameraFromCursor | Function | Map / UI | High | Runs in the main world loop, maps the cursor position inside the map-mode panel back onto strategic tile coordinates, clamps them against map bounds, and updates `MAP_VIEW_LEFT/TOP`. | c |
| sub_40DD30 | MapMode_ToggleEnabled | Function | Map / UI | High | Keyboard handler toggles the viewed/current player's map-mode latch through this helper, and the only state mutation is XOR of `PlayerRuntimeState + 23` followed by a redraw. | c, asm |
| sub_40DD60 | MapMode_IsCursorInsidePanel | Function | Map / UI | High | Returns true only when the viewed player's map-mode latch is enabled and the scaled cursor lies within the panel bounds defined by `word_523344..34A`. | c, asm |
| sub_40DDE0 | MapMode_EnableTerrainUnitsAndBuildings | Function | Map / UI | High | Enables map mode and loads overlay mask `7`, which the panel renderer interprets as terrain coloring plus unit and building owner overlays (`1|2|4`). | c, asm |
| sub_40DE20 | MapMode_EnableUnitsOnly | Function | Map / UI | High | Enables map mode and loads overlay mask `2`, the units-only layer used by the panel renderer. | c, asm |
| sub_40DE60 | MapMode_EnableBuildingsOnly | Function | Map / UI | High | Enables map mode and loads overlay mask `4`, the buildings-only layer used by the panel renderer. | c, asm |
| sub_40DEA0 | MapMode_Disable | Function | Map / UI | High | Clears the per-player map-mode latch and redraws, leaving the overlay mask untouched. | c, asm |
| dword_511FF0 | g_MapModeOverlayMask | Global | Map / UI | High | Three panel-render branches test bits `1`, `2`, and `4` to decide whether to draw terrain colors, unit ownership marks, and building ownership marks respectively. | c |
| PlayerRuntimeState + 23 | map_mode_enabled | Recovered Struct Field | gameData / Player Runtime / UI | High | The `Map mode` panel toggle and the preset helpers all write this per-player slot, and panel hit-testing only succeeds while the viewed player's copy is nonzero. | c, asm, exe |

## Batch 37 – Map Mode Render Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40D560 | MapMode_BlitRectWithViewportFrame | Function | Map / UI | High | Copies a clipped rectangle from the offscreen map-mode surface to the main render device, then redraws the current strategic viewport frame over that panel region. | c |
| sub_40D6D0 | MapMode_RedrawTileRect | Function | Map / UI | High | Redraws every map-mode tile in a bounded row/column rectangle onto the offscreen panel surface, then blits the corresponding screen rectangle back through `MapMode_BlitRectWithViewportFrame`. | c |
| sub_40D890 | MapMode_DrawTile | Function | Map / UI | High | Draws one strategic tile into the offscreen map-mode surface, combining terrain tint, optional unit/building owner overlays from `g_MapModeOverlayMask`, and the unexplored fallback color. | c |
| dword_52334C | g_MapModeSurface | Global | Map / UI | High | Created as a dedicated render surface during map-mode initialization, used as the target for `MapMode_DrawTile`, and later blitted to the main device by `MapMode_BlitRectWithViewportFrame`. | c, asm |

## Batch 38 – Map Mode Surface And Camera Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_40D330 | MapMode_InitSurface | Function | Map / UI | High | Initializes the offscreen map-mode panel surface, computes its scaled geometry from the current world dimensions, paints the panel background, and then rebuilds the full map-mode view for the current world theme. | c, asm |
| sub_40D430 | MapMode_DestroySurface | Function | Map / UI | High | Releases the dedicated offscreen map-mode surface when strategic play shuts down or the surface set is rebuilt. | c, asm |
| sub_40D800 | MapMode_IsScreenTileCoveredByPanel | Function | Map / UI | High | Pure geometry predicate that returns true only when map mode is enabled and the tested screen-space tile lies underneath the panel's covered corner. | c, asm |
| sub_40D850 | MapMode_RedrawAllTiles | Function | Map / UI | High | Iterates the full strategic map dimensions, targets `g_MapModeSurface`, and redraws every tile through `MapMode_DrawTile`; the decompiler's jumpout lands in the same init helper epilogue visible in asm. | c, asm |
| sub_40FAD0 | Map_CenterViewOnUnitStack | Function | Map / Camera | High | Recenters the strategic camera around the selected stack's tile coordinates, clamps the view against world bounds, and triggers a redraw. | c, asm |
| sub_40FEF0 | Map_HandleKeyboardScroll | Function | Map / Camera | High | Handles arrow-key strategic scrolling, mutates `MAP_VIEW_LEFT/TOP` one tile at a time within world bounds, and marks the world view dirty when movement occurs. | c, asm |
| sub_418C00 | Map_CenterViewOnTileRect | Function | Map / Camera | Medium | If a tile rectangle fits inside the current 9x7 strategic viewport, recenters the camera on that rectangle's midpoint, clamps to world bounds, and redraws. | c, asm |
| sub_418CE0 | Map_CenterViewOnTile | Function | Map / Camera | High | Recenters the strategic camera on one target tile, clamps to world bounds, and redraws. | c, asm |

## Batch 39 – Map Highlight And Effect Animation Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_418D90 | Map_StartUnitStackHighlight | Function | Map / Camera / FX | Medium | Seeds a temporary highlighted stack id and start tick. Render paths pulse that stack sprite with alpha, while the paired update helper keeps the camera centered on the same stack until the timed highlight expires. | c, asm |
| sub_418DA0 | Map_UpdateUnitStackHighlight | Function | Map / Camera / FX | Medium | Per-frame updater for the temporary highlighted stack: recenters the camera on the tracked stack, expires the effect after a fixed duration, and redraws the stack tile when the highlight ends. | c, asm |
| sub_418E20 | Map_IsUnitStackHighlightActive | Function | Map / Camera / FX | High | Pure predicate that reports whether the temporary highlighted stack id is still active. | c, asm |
| sub_418E30 | Map_StartUnitStackEffectAnimation | Function | Map / FX | Medium | Starts a 12-frame animated overlay on one stack id. Temple gift/result handlers use it immediately after changing fatigue, morale, or related stack state, and the renderer draws frames `0..11` on that stack while active. | c, asm |
| sub_418E50 | Map_UpdateUnitStackEffectAnimation | Function | Map / FX | Medium | Advances the timed 12-frame overlay started by `Map_StartUnitStackEffectAnimation` and redraws the affected stack tile each step until the sequence completes. | c, asm |
| sub_418EC0 | Map_StartTileEffectAnimation | Function | Map / FX | High | Starts an 8-frame tile-centered effect at an explicit row/column. Kill/execution paths use it before removing units, and the world renderer draws frames `12..19` on that tile while active. | c, asm |
| sub_418EE0 | Map_UpdateTileEffectAnimation | Function | Map / FX | High | Advances the timed tile-centered effect started by `Map_StartTileEffectAnimation`, redrawing the affected map tile each step until the 8-frame sequence finishes. | c, asm |

## Deferred / Ambiguous
- `PlayerRuntimeState.has_human_controller` at `+27` is secure as a human/computer flag in campaign/skirmish runtime code, but multiplayer setup may still use more than a pure boolean there; the exact enum extension for values above `1` needs a focused pass.
- `clash95.asm` still contains an older stale comment at `0x40D850` that labels the proc as `Locale_DrawInteger`; code and control-flow evidence now show that address is the full map-mode surface redraw loop, so the asm artifact should be reconciled in a later cleanup pass rather than trusted literally.
- `Map_StartUnitStackHighlight` / `Map_UpdateUnitStackHighlight` are behaviorally secure as a temporary camera-following highlight on one stack id, but the original feature name may have been closer to focus, tracking, or emphasis rather than generic highlight.
- `PlayerQueenState.queen_favor_level` is secure as a persistent queen approval/favor ladder, but the original designer-facing label behind the localized state texts may have been framed as mood, affection, loyalty, or prestige rather than literal “favor”.
- `WorldViewState.world_theme_index` is now secure as a packed strategic/world theme selector, but the exact designer-facing enum labels for concrete values `0`, `1`, and `2` remain unresolved.
- `Building_BuyAddon` and `Building_HasAddonInGarrison` still need a focused pass. The production/licence subrecord at `+402/+414/+415` is now clear, but the remaining “addon” names may still mix genuine building add-ons with licence-specific flows.
- `Building_GetTypeId` exposes building byte `+4` cleanly, but only the settlement/castle-bearing values `1` and `2` are behaviorally secure so far; the full building-type enum remains unresolved.
- `specm` and `speck` now resolve behaviorally as prisoner-only special entries, but their exact designer-facing label is still only medium-confidence as `UnitType33_PrisonerOfficerFoot` and `UnitType34_PrisonerOfficerMounted`. The prisoner flow is clear; the cross-language name triplet is not.
- `gold` and `peas` are now mapped as cargo-style special entries (`UnitType31_GoldCargo` and `UnitType32_PeasantCargo`), but the exact relationship between type `32` and ordinary recruitable peasants (type `0`) is still not fully explained by the recovered gameplay rules.
- `g_UnitTypeFlags` bit1 now aligns with a light-unit category through the 6-vs-10 morale seed at slot `+11`, but its broader gameplay consequences are still only partially recovered.
- `UnitSlotRecord.stance_bits` at `+12` is clearly a stance/formation byte, but the exact meaning of the upper subfields remains unresolved.
- `UnitSlotRecord.state_flags` bit `0x8` appears in both special-entry and cargo-related flows, but its full gameplay meaning is still unresolved.
- `BattleMap_GetMoveSoundSurfaceClass` is only medium-confidence. The implementation clearly returns a small sound-surface class used by movement audio, but the original designer-facing labels for values `0/1/2` remain inferred from suffix behavior rather than explicit text.
- `sub_441E60` still appends `gothim.wav`, but the exact gameplay role is not locked down safely enough. It is used in a late attack-resolution path for certain projectile or special-attack unit types, so it remains deferred rather than being mislabeled as a generic kill or victory sound.
