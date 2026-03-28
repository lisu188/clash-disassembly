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
| sub_40F900 | UnitStack_UpdateVision | Function | Unit Lifecycle | High | Uses the owning player id, stack tile, and `UnitStack_GetVisionRadius` to stamp fog-of-war via `sub_40EDE0`, so the rename reflects its vision-update role. |
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

## Deferred / Ambiguous
- `PlayerRuntimeState.controller_mode` at `+27` is clearly a multiplayer/campaign controller-selection field, but the exact original enum semantics for values `1` and `2` still need a focused pass through UI and AI setup code.
- The earlier prisoner-only interpretation for `specm` and `speck` is superseded: later evidence from `Queen_NewTurn` shows the same ids are also created during the royal birth event. The cross-language label triplet is still unresolved.
- `gold` and `peas` are now mapped as cargo-style special entries (`UnitType31_GoldCargo` and `UnitType32_PeasantCargo`), but the exact relationship between type `32` and ordinary recruitable peasants (type `0`) is still not fully explained by the recovered gameplay rules.
- `g_UnitTypeFlags` bit1 now aligns with a light-unit category through the 6-vs-10 morale seed at slot `+11`, but its broader gameplay consequences are still only partially recovered.
- `UnitSlotRecord.stance_bits` at `+12` is clearly a stance/formation byte, but the exact meaning of the upper subfields remains unresolved.
- `UnitSlotRecord.state_flags` bit `0x8` appears in both special-entry and cargo-related flows, but its full gameplay meaning is still unresolved.
- `BattleMap_GetMoveSoundSurfaceClass` is only medium-confidence. The implementation clearly returns a small sound-surface class used by movement audio, but the original designer-facing labels for values `0/1/2` remain inferred from suffix behavior rather than explicit text.
- `sub_441E60` still appends `gothim.wav`, but the exact gameplay role is not locked down safely enough. It is used in a late attack-resolution path for certain projectile or special-attack unit types, so it remains deferred rather than being mislabeled as a generic kill or victory sound.

## Batch 28 – Building, Port, And Queen Special-Entry Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources |
|---|---|---|---|---|---|---|
| sub_41E1E0 | Building_FinishConstruction | Function | Buildings / Construction | High | Debug log string is `Building_BuildFinished() - %d,%d`; the helper finalizes the build, refreshes nearby map state, and triggers the post-build naming/UI path. | c, asm |
| sub_41E3F0 | Building_ProcessUnitProductionTurn | Function | Buildings / Production | High | Debug log string is `Building_Production(0x%08x) - nowa jednostka`; the function decrements the selected licence timer, spends local resources, and inserts the finished unit into the building garrison. | c, asm |
| sub_43E770 | Building_CanAcceptUnitStack | Function | Buildings / Garrison | High | Called both from movement/UI hover checks and the actual enter-building path; it gates entry by building mode and by whether the stack contains normal units, gold cargo, peasant cargo, or special entries. | c |
| sub_43E820 | Building_HasAddonInGarrison | Function | Buildings / Garrison | High | Scans the 12 add-on/licence bytes at `building + 402` for the requested add-on id, matching every buy/remove add-on caller. | c |
| sub_43EB50 | Building_CountGarrison | Function | Buildings / Garrison | High | Counts occupied 31-byte garrison slots across the 12-slot array starting at `building + 18`. | c |
| sub_43EC40 | Building_CompactGarrison | Function | Buildings / Garrison | High | Shifts occupied 31-byte garrison entries down over empty slots and then calls `Building_OnGarrisonChange`, exactly matching garrison compaction after casualties or transfers. | c |
| sub_43ED20 | Building_CanEquipAddon | Function | Buildings / Add-ons | High | Uses the building footprint class, technology bits, add-on flags, whitelist, and blacklist tables to decide whether an add-on type can be installed. | c, asm |
| sub_43EE50 | Building_GetTaxPressureTier | Function | Buildings / Settlement Economy | High | Converts population bands plus the tax-rate byte into a 0..3 pressure tier by comparing against the 4x4 threshold table later consumed by the population-growth helper. | c |
| sub_43EED0 | Building_UpdatePopulationGrowth | Function | Buildings / Settlement Economy | High | Updates settlement condition from the previous growth delta, derives a new growth percentage from tax pressure, add-ons, tech, and condition, then writes both the new delta and the updated peasant population. | c |
| sub_43F0C0 | Building_CollectGoldIncome | Function | Buildings / Settlement Economy | High | Converts population and tax rate into `gold_income_last_turn`, zeros income during crises, and adds the result into `stored_gold`. | c |
| sub_43F160 | Building_UpdateCrisisState | Function | Buildings / Settlement Economy | Medium | Advances the low 3-bit crisis timer at `building + 435`, applies plague-style population loss while active, and can start a new crisis when the settlement grows large enough. | c |
| sub_44F1E0 / Building_CreatePrisonerUnit | Building_CreateSpecialGarrisonUnit | Function | Buildings / Special Entries | High | The asm/exe log string is `Building_CreateSpecial`; besides prisoner payment and transfer callers, `Queen_NewTurn` also uses it to place the royal birth special entry into a building garrison, proving the older prisoner-specific rename was too narrow. | c, asm, exe |
| sub_44FE70 | Building_ShowPrisonerManagementPanel | Function | Buildings / Prisoners / UI | High | Renders a three-prisoner action panel, nation-strength bars, and queen mood state, then writes the selected behead/torture/pay actions back through `BuildingPrisoner_SetAction`. | c |
| sub_450CE0 | Player_Surrender | Function | Turn Flow / Player State | High | Called directly from the surrender-confirm dialog; destroys all owned buildings and unit stacks, then clears the player's active runtime flag. | c |
| sub_450FD0 | Player_CheckForDefeatAndHandleElimination | Function | Turn Flow / Player State | High | Scans all owned field stacks and buildings; when none remain it deactivates the player, refreshes the UI/music state, and returns the defeat/continue result used by the main turn loop. | c |
| byte_515D00 | g_SettlementTaxPressureThresholds | Table | Buildings / Settlement Economy | High | `Building_GetTaxPressureTier` reads this as a 4x4 threshold grid keyed first by population band and then by tax-rate band. | c |
| dword_517B48 | g_PortSupplySpawnRowOffsets | Table | Port / Reinforcements | High | `Port_GetSupply` walks these offsets in lockstep with the companion column table to find the first free tile around the dock for the spawned reinforcement stack. | c, asm |
| dword_517B4C | g_PortSupplySpawnColumnOffsets | Table | Port / Reinforcements | High | Companion column-offset table paired with `g_PortSupplySpawnRowOffsets` during port reinforcement spawning. | c, asm |
| dword_517BA8 | g_PortSupplyUnitTypePool | Table | Port / Reinforcements | High | `Port_GetSupply` chooses random entries from this 12-element pool when seeding the arriving reinforcement stack. | c, asm |
| off_518D98 | g_PrisonerDeathByExhaustionTexts | Table | Prisoners / UI Text | High | `Prisoner_NewTurn` formats these three localized strings exactly when a held prisoner reaches the terminal exhaustion turn. | c, asm |
| off_519350 | g_QueenSonBirthTexts | Table | Queen / UI Text | High | `Queen_NewTurn` selects this localized triplet only when the birth-event special type is `33`, and the strings explicitly say the queen gave birth to a son. | c, asm, exe |
| off_51935C | g_QueenDaughterBirthTexts | Table | Queen / UI Text | High | Companion localized triplet selected when the birth-event special type is `34`, and the strings explicitly say the queen gave birth to a daughter. | c, asm, exe |
| gameData + 586374 | PortRuntimeState | Recovered Struct | gameData / Port Runtime | High | The contiguous six-dword block at offsets `586374..586394` stores the port footprint, next arrival turn, supply-ready state, shipment size, and shore-refresh flag used together by every port helper. | c, asm |

## Deferred / Ambiguous
- Types `33` and `34` are no longer safe to describe as prisoner-only entries: `Queen_NewTurn` creates the same ids through `Building_CreateSpecialGarrisonUnit`. The conservative documentation names are now `UnitType33_SpecialFootPersonage` and `UnitType34_SpecialMountedPersonage`, but the exact original gameplay label behind `Dowódca / Tactician / Soldat` remains unresolved.

## Batch 29 – Garrison Recovery And Queen Whim Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_41E570 | Building_UpdateGarrisonTrainRepairTimers | Function | Buildings / Garrison | High | Iterates the 12 packed garrison task bytes, decrements repair countdown bits `3..5` until slot health returns to `100`, and decrements train/order countdown bits `0..2` until the stance/order completion path fires. | c, asm | yes: Lorentz |
| sub_41E7B0 | UnitSlot_NeedsMoraleRecovery | Function | Unit Runtime / Morale | High | Reads slot morale at `+11` and compares it against the recovered resting floors `6` or `10` depending on the unit-type flag bit, making it a threshold predicate rather than a timer helper. | c, asm | yes: Lorentz |
| sub_41E7F0 | Building_RecoverGarrisonFatigueAndMorale | Function | Buildings / Garrison | High | Completed-building upkeep pass over 12 garrison slots: first reduces slot fatigue (`+10`) by `50`, then increases morale (`+11`) by `1` only when `UnitSlot_NeedsMoraleRecovery` succeeds, before refreshing the building garrison state. | c, asm | yes: Lorentz |
| AI_FindActionCandidate | Queen_FindEligibleBirthHostBuilding | Function | Queen / Birth | Medium | Only gameplay caller is the childbirth branch in `Queen_NewTurn`; it scans active owned building records and returns the host building used by `Building_CreateSpecialGarrisonUnit` for types `33/34`. | c, asm, map | yes: Pauli, Averroes |
| sub_44FC70 | Building_DrawPrisonerRows | Function | Buildings / Prisoners / UI | High | Reads the three prison cells at `building + 445`, draws the prisoner type icon and action icon for each occupied slot, and renders the ransom/count field, so it is the prisoner-row renderer used by the management panel. | c, asm | yes: Averroes |
| PORT_SHORE_REFRESH_FLAG_OFFSET / PORT_NEEDS_SHORE_REFRESH | PORT_SHORE_VARIANT_FLAG_OFFSET / PORT_SHORE_VARIANT_FLAG | Helper | Port / Runtime State | High | The sixth dword in the port sidecar is read by `Port_BuildShorePieces` to choose which shoreline-piece variant to stamp; it is more specific than a generic “refresh needed” flag. | c, asm | yes: Averroes |
| word_5191F0 + off_5191F2 | g_QueenWhimRecords / QueenWhimRecord | Recovered Struct | Queen / Whim Table | High | `Queen_NewTurn` indexes these overlapped symbols with `7 * whimIndex`, reading a uint16 requirement and one localized pointer triplet; the next table starts exactly after 25 such records. | c, asm | yes: Pauli |
| UNIT_TYPE_PRISONER_FOOT | UNIT_TYPE_SPECIAL_FOOT_PERSONAGE | Helper | Unit Types / Special Entries | High | Type `33` is handled by both prisoner capture code and the queen birth path; retaining a prisoner-only constant name was misleading once `Queen_NewTurn` was corroborated against `specm` and the commander-like localized label. | c, asm, exe | yes: Pauli |
| UNIT_TYPE_PRISONER_MOUNTED | UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE | Helper | Unit Types / Special Entries | High | Type `34` is the mounted sibling of the same shared special-entry family, created by the queen birth path as well as the prisoner system, so the older prisoner-only constant name was no longer accurate. | c, asm, exe | yes: Pauli |

## Deferred / Ambiguous
- The internal debug string `NewQueenWindow()` was not promoted because the localized prompt text proves the dialog is specifically a marriage offer, not a generic queen-window controller.
- `QueenWhimRecord.required_frontline_score` is implementation-safe, but the designer-facing resource name behind that score remains unresolved; the code only proves that whims consume the same per-building frontline-pressure pool later updated by `AI_ApplyFrontlineScore`.

## Batch 30 – Marriage Dialog And Prisoner Panel Controls Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_4127A0 | UnitSlot_AdjustFatigueByPredicate | Function | Unit Runtime / Fatigue | High | Single-slot analogue of `UnitStack_AdjustFatigueByPredicate`: applies the caller-supplied delta to slot fatigue at `+10`, skips special-entry types `31..34`, clamps to `0..100`, and gates on the predicate passed in `ebx`. | c, asm | yes: Lorentz |
| sub_412880 | UnitSlot_AdjustMoraleByPredicate | Function | Unit Runtime / Morale | High | Single-slot analogue of `UnitStack_AdjustMoraleByPredicate`: applies the caller-supplied delta to slot morale at `+11`, clears the refusal flag on gains, skips special-entry types, and clamps to `0..20`. | c, asm | yes: Lorentz |
| Building_FindFirstValidAddonSlot | Building_AdjustAllGarrisonMoraleByDelta | Function | Buildings / Garrison | High | The old prototype name was misleading; the wrapper scans every occupied building garrison slot and forwards the caller-supplied morale delta through `UnitSlot_AdjustMoraleByPredicate`, with no add-on search behavior at all. | c, asm | yes: Lorentz |
| sub_43EE10 | Building_CycleAllGarrisonOrdersOnce | Function | Buildings / Garrison | Medium | Scans every occupied building garrison slot and calls `Building_UseGarrisonSlot` once per slot, so it is a bulk order/state cycler rather than a morale or timer helper. | c, asm | yes: Lorentz |
| Queen_ShowProposalDialog | Queen_ShowMarriageProposalDialog | Function | Queen / Marriage | High | The localized prompt explicitly asks whether the ruler wants to marry the princess offered by king Wolfgang's envoy; the weak debug string `NewQueenWindow()` is less semantically accurate than the prompt text and callsite behavior in `Queen_NewTurn`. | c, asm, exe | yes: Pauli, Averroes |
| g_QueenProposalPrompt | g_QueenMarriageProposalTexts | Table | Queen / Marriage | High | Three localized strings describing the envoy-delivered marriage offer, used only by the marriage dialog at `0x446F40`. | c, asm, exe | yes: Pauli |
| g_QueenMoodTexts | g_QueenRelationshipStateTexts | Table | Queen / Relationship State | Medium | The 30-entry localized table covers `No queen`, anger, estrangement, affection, and childbirth intent, so it models broader queen relationship states rather than pure mood text. | c, asm | yes: Pauli |
| sub_44F510 | BuildingPrisonerActionWidget_HasPrisoner | Function | Buildings / Prisoners / UI | High | Converts a prisoner-action widget pointer back into one of the three prison-cell indices and checks whether that slot's prisoner type byte is occupied. | c, asm | yes: Averroes |
| sub_44F580 | BuildingPrisonerActionButton_SelectBehead | Function | Buildings / Prisoners / UI | High | Bound by the widget table to the localized `Behead` labels and only selects that action in the prisoner panel; execution happens later through `BuildingPrisoner_SetAction`. | c, asm, exe | yes: Averroes |
| sub_44F5F0 | BuildingPrisonerActionButton_SelectTorture | Function | Buildings / Prisoners / UI | High | Bound by the widget table to the localized `Torture` labels and acts as the prisoner-panel selector for that action. | c, asm, exe | yes: Averroes |
| sub_44F660 | BuildingPrisonerActionButton_SelectBribery | Function | Buildings / Prisoners / UI | High | Bound by the widget table to the localized `Bribery` labels and selects the ransom/bribery action in the prisoner panel. | c, asm, exe | yes: Averroes |
| sub_44F6D0 | BuildingPrisonerPanel_BackButton | Function | Buildings / Prisoners / UI | Medium | Bound to the localized `Back` button and signals dialog exit by updating `dword_5443F4`, which the prisoner-panel event loop watches. | c, asm, exe | yes: Averroes |

## Deferred / Ambiguous
- `Queen_DrawMoodPanel` is mostly reliable and was left unchanged; `Queen_DrawMoodSummary` would also fit, but the current name is not misleading enough to justify churn.
- `g_QueenRelationshipStateTexts` is a safer name than `g_QueenMoodTexts`, but the exact internal state machine behind each row still mixes queen presence, mood, and childbirth intent.
- `Building_CycleAllGarrisonOrdersOnce` is semantically safe at the implementation level, but the original designer-facing term for the packed order/state byte at slot `+0x0C` is still unresolved.

## Batch 31 – Movement Queue And Building Approach Path Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_410010 | UnitStack_GetMinCurrentActionPoints | Function | Unit Movement / Action Points | High | Scans the ten embedded slot records and returns the minimum live value from slot byte `+8`, which is the shared current action-point budget later compared against path waypoint costs and attack thresholds. | c | yes: Lorentz |
| sub_410130 | UnitStack_SpendActionPointsClamped | Function | Unit Movement / Action Points | High | Iterates occupied slots, clamps the requested spend down to the smallest current action-point value, subtracts that amount from each slot, and relinks the army fact. | c | yes: Lorentz |
| sub_410170 | UnitStack_SpendActionPointsUnchecked | Function | Unit Movement / Action Points | High | Raw per-slot action-point subtraction helper used inside queued-path execution after the step cost has already been validated against the stack minimum. | c | yes: Lorentz |
| sub_4101A0 | UnitStack_SubtractActionPointsFloorZero | Function | Unit Movement / Action Points | Medium | Per-slot subtraction helper that floors each slot's action points at zero instead of clamping the spend amount globally. | c | yes: Lorentz |
| sub_4101E0 | UnitStack_SpendActionPointsByIndexClamped | Function | Unit Movement / Action Points | High | Thin wrapper that applies `UnitStack_SpendActionPointsClamped` to `gameData + 147174 + 725 * stackIndex`. | c | yes: Lorentz |
| sub_410330 | UnitStack_ExecuteQueuedPath | Function | Unit Movement / Path Execution | High | Consumes the queued path at `stack + 316`, validates each waypoint cost against the stack's current action points, advances tile occupancy/vision/traps, and rewrites the remaining waypoint costs after partial movement. | c | yes: Averroes |
| Unit_MoveTrackNear | Building_GenerateApproachTrack | Function | Building / Pathing | High | The embedded string is `Unit_MoveTrackToBuilding(%d,%d)`; the helper temporarily clears the target building footprint, generates a track, trims the tail to stop at the footprint edge, and restores the building tiles. | c, asm, map | yes: Averroes |
| sub_415970 | Building_GenerateNearApproachTrack | Function | Building / Pathing | High | The sibling helper logs `Unit_MoveTrackNearBuilding(%d,%d)`, uses the same temporary footprint clearing, and returns a trimmed approach path that stops one node earlier in the near-building case. | c, asm | yes: Averroes |
| Track_BridgesOn | Pathing_EnableBridgeCrossings | Function | Map / Pathing | High | Pure global mode toggle around path generation; callers wrap only bridge-capable movement cases, and the matching cost readers branch on the same flag to treat bridge overlays as traversable. | c, asm, map | yes: Averroes |
| Track_BridgesOff | Pathing_DisableBridgeCrossings | Function | Map / Pathing | High | Clears the same bridge-crossing mode flag after path generation, restoring normal terrain-cost behavior. | c, asm, map | yes: Averroes |
| sub_415CD0 | QueuedPath_StartsAtTile | Function | Unit Movement / Path Cache | High | Returns false when the queued path count is zero; otherwise compares the first packed waypoint's row and column bytes against the requested tile. | c | yes: Averroes |
| sub_415D00 | QueuedPath_StartsInBuildingFootprint | Function | Building / Path Cache | High | Returns false when the queued path is empty; otherwise checks whether the first packed waypoint already lies on the exact building tile or within its 2x2 footprint. | c | yes: Averroes |
| sub_424370 | Map_GetBridgeCrossingCostOrZero | Function | Map / Pathing | High | Returns cost `5` only for the bridge overlay tile-id range `0x25B..0x262`, and zero otherwise; the terrain-cost readers consult it only while bridge crossing mode is enabled. | c, asm | yes: Averroes |
| Path_GenerateTrack | Temple_GenerateApproachTrack | Function | Temple / Pathing | High | The embedded string is `Unit_MoveTrackToTemple(%d,%d,%d)`; the helper temporarily clears one temple overlay word, runs `Unit_MoveTrack`, then restores the original word. | c, asm, map | yes: Averroes |
| dword_52456C | g_TerrainMoveProfileOffsets | Global | Map / Movement Costs | High | Indexed by terrain tile id to select the correct offset into the byte-based move-cost profiles consumed by world-map and stack-level movement-cost helpers. | c, asm | yes: Averroes |
| dword_52556C | g_PathingAllowBridgeCrossings | Global | Map / Pathing | High | Global bridge-crossing mode bit toggled by the pathing wrappers and consulted by terrain-cost readers when deciding whether bridge overlays should supply a synthetic cost. | c, asm | yes: Averroes |
| gameData + 147174 + 316 | QueuedPathBuffer / queued_path | Recovered Struct | Unit Movement / Path Cache | High | Every planner copies exactly `0x194` bytes into this region, while the queued-path guards and executor treat it as a persistent count-plus-waypoints buffer rather than an anonymous blob. | c, asm | yes: Averroes |
| packed dword at queued_path + 4 | PathWaypoint | Recovered Struct | Unit Movement / Path Cache | High | Low byte is row, next byte is column, and the high word is the cumulative action-point cost; the executor subtracts spent cost from that high word after each partial move. | c, asm | yes: Averroes |

## Deferred / Ambiguous
- `sub_4100B0` clearly derives a stack-wide readiness/order tier from per-slot control bits, but the exact gameplay label behind `(slot + 18) & 3` is still unresolved.
- Resolved in Batch 35: stack state-flags bit `0x8` is the plague marker (`UNIT_SLOT_FLAG_PLAGUE`), so the older cargo-state ambiguity was retired.
- `sub_410260` gates the animated movement path on visibility and reachable waypoints, but the original designer-facing term for that reveal/animation predicate is still unresolved.
- Resolved in Batch 36: `Unit_MoveTrack_1` became `Unit_MoveTrackNearTile` after asm/exe debug-string evidence (`Unit_MoveTrackNear(%d,%d,%d)`) confirmed that the helper intentionally stops adjacent to the target tile.

## Batch 32 – Stack Lifecycle And Combat Utility Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_40FAD0 | Camera_CenterOnUnit | Function | Camera / Turn Flow | High | Centers the strategic-map camera on the stack tile, clamps against map bounds using the world-session width/height fields, and forces a redraw. | c | yes: Pauli |
| sub_40FEC0 | UnitStack_ClearRemainingActionPoints | Function | Unit Lifecycle / Turn State | High | Iterates every occupied slot and zeroes the current action-point byte at `+8`, then relinks the stack fact; used after hide/contact actions that should end the stack's turn immediately. | c | yes: Pauli |
| sub_411810 | UnitStack_ApplyPeasantCargoAttrition | Function | Unit Turn Update / Special Cargo | High | Only damages unit type `32` when slot flag bit `0x8` is set, applies random `15..25` health loss, deletes dead slots, compacts the stack, and refreshes the linked fact. | c | yes: Pauli |
| sub_412BE0 | UnitStack_CalcMilitaryStrength | Function | Combat Evaluation | High | Counts live slots in one stack and feeds the slot block into the shared strength-scoring helper `sub_412B90`. | c | yes: Pauli |
| sub_412C00 | Building_CalcGarrisonStrength | Function | Combat Evaluation / Buildings | High | Computes the building-side factor through `sub_41C410`, counts garrison entries, and scores the garrison with the same shared strength helper used by mobile stacks. | c | yes: Pauli |
| sub_412C30 | Player_CalcMilitaryStrength | Function | Combat Evaluation / Player State | High | Aggregates `Building_CalcGarrisonStrength` over owned buildings and `UnitStack_CalcMilitaryStrength` over owned world-map stacks to produce one per-player military-strength total. | c | yes: Pauli |
| sub_422BE0 | Unit_AddToGroup | Function | Unit Lifecycle / Stack Merge | High | The embedded string is `Unit_AddToGroup(%d,%d,%d)`; the helper optionally approaches the destination stack, spends `4` action points, appends the source slots into the destination stack, and kills the source stack. | c, asm | yes: Pauli |
| sub_422DC0 | Unit_CanMoveSelectionFromGroupToTile | Function | Unit Lifecycle / Stack Split | High | Clones the source stack into a temporary buffer, copies only the selected slot indices, then checks whether the moved subset has at least `4` action points and can either stand on or merge into the destination tile. | c | yes: Pauli |
| sub_423050 | Unit_MoveSelectionFromGroupToTile | Function | Unit Lifecycle / Stack Split | High | The embedded string is `Unit_MoveFromGroup`; the helper moves the selected slots into a new or friendly destination stack, subtracts `4` action points from moved slots, compacts the source stack, and resolves hidden contact/traps at the destination. | c, asm | yes: Pauli |
| sub_444150 | UnitStack_RevealAndEngageHiddenEnemies | Function | Combat / Hidden Contact | Medium | First reveals hidden enemy stacks within vision when the stack's unresolved order tier is at least `3`, then attacks adjacent hidden enemy stacks and clears the acting stack's remaining action points. | c | yes: Pauli |
| unit_stack + 720 | UnitStackRecord.is_hidden_on_world_map | Recovered Struct Field | Unit Lifecycle / Hidden State | High | The hide action sets byte `+720`, merge/split helpers clear it, and `UnitStack_RevealAndEngageHiddenEnemies` clears the same flag on exposed enemy stacks. | c | yes: Pauli |

## Deferred / Ambiguous
- `sub_4100B0` still looks like a stack-wide order/recon tier derived from `(slot + 18) & 3`, but the gameplay label behind that tier is not locked down enough for a factual rename.
- `sub_4129E0` remains deferred because it is a repeated post-combat/post-event slot mutator whose exact designer-facing semantics are still obscured by upstream naming debt.

## Batch 33 – Movement Utility Wrapper Cleanup
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_40FE80 | UnitStack_GetMinBaseActionPoints | Function | Unit Movement / Action Points | High | Scans the embedded slot records and returns the minimum base action-point value derived from `UnitSlot_GetBaseActionPoints`, not the current spent-down value. | c | no |
| sub_414350 | UnitStack_GetMoveCostToTile | Function | Unit Movement / Pathing | High | Thin wrapper that forwards the active stack record to `UnitStack_GetTileMoveCostOrZero` for one destination tile. | c | yes: Averroes |
| sub_414400 | Path_InsertBridgeCornerWaypoints | Function | Unit Movement / Pathing | Medium | Rebuilds a generated waypoint queue, and when two consecutive waypoints are diagonal bridge corners with a legal orthogonal detour, inserts an intermediate packed waypoint with averaged cumulative cost. | c | yes: Averroes |

## Batch 34 – Hidden Orders, Queen State, And Port Footprint Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_443EB0 | UnitStack_TryHide | Function | Unit Hidden State / Orders | High | The helper is the strategic-map hide action: it rejects stacks without enough order tier or with nearby enemies, shows the localized hide-failure string, clears remaining action points on success, sets the hidden byte at `stack + 720`, and logs `ukrycie`. | c, asm, exe | yes: Lorentz |
| sub_4100B0 | UnitStack_GetMaxOrderTier | Function | Unit Hidden State / Orders | Medium | Returns the maximum low-two-bit order tier from slot byte `+12` across occupied slots, with prisoner-bearing stacks forced to tier `3`; that tier gates hiding at `>= 2` and wide reveal behavior at `>= 3`. | c, asm | yes: Lorentz |
| Building_UseGarrisonSlot | UnitSlot_CycleOrderState | Function | Unit Hidden State / Orders | High | The routine only mutates the packed order byte at slot `+12`, cycling the upper two-bit substate and then advancing the lower two-bit tier when the substate wraps. | c, asm | yes: Lorentz |
| sub_4129E0 | UnitStack_CycleAllSlotOrders | Function | Unit Hidden State / Orders | High | Iterates every occupied slot in one stack, applies `UnitSlot_CycleOrderState`, then runs the usual stack refresh notifier; it is a bulk order-cycle helper, not a combat-state mutator. | c, asm | yes: Lorentz |
| UnitStack_RevealAndEngageHiddenEnemies | UnitStack_RevealHiddenEnemiesAndAttackAdjacent | Function | Combat / Hidden Contact | Medium | First reveals hidden enemy stacks inside vision when the acting stack's order tier reaches `3`, then separately auto-attacks adjacent hidden enemy stacks and clears the acting stack's remaining action points. | c, asm | yes: Lorentz |
| Queen_ShowWhimDialog | Queen_ShowWhimDecisionDialog | Function | Queen / Whims | Medium | The dialog displays the whim text, shows the required score versus the current score, and returns a yes/no acceptance decision rather than acting as a passive message window. | c, exe | yes: Pauli |
| Queen_ShowNotification | Queen_ShowMessageDialog | Function | Queen / UI | Medium | The window always draws queen portrait art plus the current whim portrait before presenting the supplied narrative text, so it is a queen-specific message dialog rather than a generic notification primitive. | c, exe | yes: Pauli |
| Queen_DrawMoodPanel | Queen_DrawRelationshipPanel | Function | Queen / UI | Medium | The panel indexes `g_QueenRelationshipStateTexts` by the queen state byte, substitutes `0` for `-1`, and renders the current whim icon only for positive states, so “relationship panel” better fits the displayed content than “mood panel”. | c | yes: Pauli |
| PLAYER_QUEEN_MOOD / PlayerRuntimeState.queen_mood | PLAYER_QUEEN_RELATIONSHIP_STATE / PlayerRuntimeState.queen_relationship_state | Recovered Struct | Queen / Player Runtime State | High | Offset `+1419` does not hold pure mood: the same byte drives no-queen, marriage, departure, relationship, and childbirth branches in `Queen_NewTurn`, and it selects rows in `g_QueenRelationshipStateTexts`. | c | yes: Pauli |
| Port_IsInsideArea | Port_IsInsideFootprint | Function | Port / Footprint | High | Performs an exact `row in [port_row, port_row + 1]` and `column in [port_column, port_column + 1]` bounds check, proving it targets the 2x2 port footprint rather than a broader area. | c, asm | yes: Averroes |
| Port_HasSupplyReady | Port_IsSupplyReady | Function | Port / Runtime State | High | Pure boolean getter for `PortRuntimeState.supply_ready_flag`; the stronger verb matches the actual implementation and calling pattern. | c, asm | yes: Averroes |
| Port_BuildDockingTrack | Port_GenerateApproachTrack | Function | Port / Pathing | Medium | Temporarily clears the 2x2 port footprint, generates a path with `Unit_MoveTrack`, trims path nodes that still lie inside the footprint, and restores the original tiles; it generates an approach path rather than building a persistent track object. | c, asm | yes: Averroes |
| Port_PresentInteger | UI_TrySelectFriendlyStackUnderCursor | Function | UI / Unit Selection | Medium | The map symbol was misleading: the routine converts the current mouse position to a world tile while the frame is active, checks for a friendly loose stack there, rejects the already-selected stack, and writes `g_SelectedUnitIndex`. | c, asm, map | yes: Averroes |
| g_PortSupplySpawnRowOffsets / g_PortSupplySpawnColumnOffsets | PortSpawnOffset[12] | Recovered Struct | Port / Reinforcements | High | `Port_GetSupply` advances the row and column arrays in lockstep for the same candidate tile, and the asm data layout advances by 8 bytes per pair, proving the decompiler split one interleaved `{ row_delta, column_delta }` table into two parallel arrays. | c, asm | yes: Averroes |

## Deferred / Ambiguous
- Resolved in Batch 35: `sub_410100` / `sub_412AC0` became `UnitStack_HasPlagueFlag` / `UnitStack_HasPlague` after the plague-transfer and plague-attrition evidence converged.
- `sub_410260` still depends on the unresolved viewer-exposure naming split around `Map_ClassifyFogOfWarOverlayForPlayer`, so it was not promoted into a factual visibility/reachability rename.
- `Port_GetSupply` clearly spawns a reinforcement stack rather than returning passive data, but the exact public-facing name is still split between the embedded debug string and the higher-level behavior, so it was left unchanged for now.

## Batch 35 – Fog Of War, Plague, And Religious Site Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_40F060 | Map_IsTileVisibleToPlayer | Function | Map / Visibility | High | Directly indexes the per-player revealed-tile bitset at `PlayerRuntimeState + 57` using `13 * row + (column >> 3)` and returns whether the bit for the target tile is set. | c | no |
| sub_40F0C0 | Map_ClassifyFogOfWarOverlayForPlayer | Function | Map / Fog Of War | High | Returns `-1` for directly revealed tiles, `0` for fully black interior tiles, and otherwise classifies neighbor-reveal masks into fog overlay sprite codes later drawn from the dedicated overlay sprite set. | c, asm | yes: Parfit |
| sub_408140 | MapTile_HasOwnUnitStack | Function | Map / Tile Occupancy | High | Used by world-map hover/selection logic as the current-player stack predicate, separate from enemy-visible stack checks. | c | yes: Zeno |
| sub_408200 | MapTile_HasVisibleEnemyUnitStack | Function | Map / Tile Occupancy | High | Matches the enemy-stack branch in the same world-map hover flow and excludes hidden stacks before exposing combat/inspection UI. | c | yes: Zeno |
| sub_4082C0 | MapTile_HasOwnOrVisibleEnemyUnitStack | Function | Map / Tile Occupancy | High | Combined tile-occupancy predicate used by hover, info, and selection code after splitting the own-stack and visible-enemy cases. | c | yes: Zeno |
| sub_4082F0 | MapTile_HasOwnBuilding | Function | Map / Tile Occupancy | High | Building-hover logic branches on this helper before garrison-entry validation, proving it is the current-player building test. | c | yes: Zeno |
| sub_408390 | MapTile_HasEnemyBuilding | Function | Map / Tile Occupancy | High | Complementary occupied-building test used when the selected stack is hovering an enemy building. | c | yes: Zeno |
| sub_408430 | MapTile_HasBuilding | Function | Map / Tile Occupancy | High | General occupied-building predicate shared by building info and movement UI branches. | c | yes: Zeno |
| sub_411AB0 | UnitStack_HasBuilder | Function | Unit Lifecycle / Utility Units | High | Scans the ten embedded slots and returns true only when type id `17` is present; separate digging/building actions gate on this exact helper. | c | no |
| UnitStack_ApplyPeasantCargoAttrition | UnitStack_ApplyPlagueAttritionToPeasantCargo | Function | Unit Turn Update / Plague | High | The helper only damages type-`32` peasant cargo when slot flag bit `0x8` is set, matching plague spread/attrition rather than generic cargo decay. | c | yes: Hilbert |
| sub_410100 | UnitStack_HasPlagueFlag | Function | Unit Turn Update / Plague | High | Duplicate stack predicate that returns true when any occupied slot has state-flag bit `0x8` set. | c | yes: Hilbert |
| sub_412A90 | UnitStack_SetPlagueFlag | Function | Unit Turn Update / Plague | High | Iterates occupied slots and ORs state-flag bit `0x8` into each one when plague spreads to the stack. | c | yes: Hilbert |
| sub_412AC0 | UnitStack_HasPlague | Function | Unit Turn Update / Plague | High | Canonical stack plague predicate wrapped by the higher-level `JestZarazaWOddziale` rules helper and used by building infection transfer. | c | yes: Hilbert |
| sub_43FB10 | MapTile_GetReligiousSiteCategory | Function | Map / Religious Sites | High | Distinguishes shrine, empty shrine, cult place, and empty cult place tile families, and the adjacent text tables plus entry rules agree with those four categories. | c, asm | yes: Zeno |
| sub_443BB0 | MapTile_HasHiddenTreasure | Function | Map / Treasure | High | Checks for the hidden-treasure tile ids and is paired with the localized `Zakopany skarb` strings and `Treasure_DigHere(%d)` action. | c, asm | yes: Zeno |
| sub_443C20 | Treasure_TryDigHere | Function | Map / Treasure | High | Requires a hidden-treasure tile plus a builder-capable stack, logs `Treasure_DigHere(%d)`, consumes the treasure tile, and dispatches the dig outcome. | c, asm | yes: Zeno |
| Move_CanEnterTile | Player_CanEnterReligiousSiteTile | Function | Map / Religious Sites | Medium | The helper allows entry into shrine tiles only when the player religion flag is set and into cult-place tiles only when it is clear, so it is a player-versus-religious-site compatibility gate rather than a generic move validator. | c | yes: Zeno |
| Building_UpdateCrisisState | Building_UpdatePlagueState | Function | Buildings / Plague | High | Only the low three bits at building byte `+435` are updated, the function drains building population while active, and gold income is separately suppressed while those bits are non-zero. | c | yes: Hilbert |
| sub_457DA0 | Building_GetPlagueState | Function | Buildings / Plague | High | Thin accessor that returns `BuildingRecord + 435 & 7`, exactly the plague countdown/state field consumed by UI and turn-update logic. | c | yes: Hilbert |
| sub_457DC0 | UnitStack_HasPlagueByIndex | Function | Unit Turn Update / Plague | High | Index wrapper around `UnitStack_HasPlague` for callers that hold only a stack id. | c | yes: Hilbert |
| dword_5202C4 | g_FogOverlaySpriteSet | Global | Map / Fog Of War | High | The map UI loader allocates and loads this sprite set alongside other world-map sets, and render code indexes it with the fog overlay classifier’s return code before drawing unexplored-edge tiles. | c, asm | yes: Parfit |
| off_511B68 | g_ShrineTexts | Table | Map / Religious Sites | High | `clash95.asm` exposes the localized base text as `Świątynia`, and hover/info logic uses this table when `MapTile_GetReligiousSiteCategory(...) == 1`. | c, asm | yes: Zeno |
| off_511B74 | g_EmptyShrineTexts | Table | Map / Religious Sites | High | Same category family as above, but the asm strings show the empty-site wording (`Pusta świątynia`). | c, asm | yes: Zeno |
| off_511B80 | g_CultPlaceTexts | Table | Map / Religious Sites | High | `clash95.asm` exposes the localized text as `Miejsce kultu`, and the world-map info panel uses it for category `3`. | c, asm | yes: Zeno |
| off_511B8C | g_EmptyCultPlaceTexts | Table | Map / Religious Sites | High | Localized empty-site counterpart for the cult-place family. | c, asm | yes: Zeno |
| off_511BA4 | g_HiddenTreasureTexts | Table | Map / Treasure | High | Localized table headed by `Zakopany skarb`, shown when the hover/info logic detects a hidden-treasure tile. | c, asm | yes: Zeno |
| *(new constants)* categories `1..4` | RELIGIOUS_SITE_CATEGORY_SHRINE / EMPTY_SHRINE / CULT_PLACE / EMPTY_CULT_PLACE | Helper | Map / Religious Sites | High | `MapTile_GetReligiousSiteCategory` is now corroborated by the matching shrine/cult text tables and by `Player_CanEnterReligiousSiteTile`, which only accepts category `1` for one religion flag state and category `3` for the other. | c, asm | yes: Zeno |
| *(new constant)* slot flag bit `0x8` | UNIT_SLOT_FLAG_PLAGUE | Helper | Unit Turn Update / Plague | High | Both plague predicates, plague propagation, and plague attrition target the same slot-flag bit `0x8`, making the plague interpretation stable. | c | yes: Hilbert |
| PlayerRuntimeState + 39 | PlayerRuntimeState.religion_flag | Recovered Struct Field | Player Runtime State / Religion | High | Religious-site entry checks and castle-construction labels branch on this dword to choose shrine-vs-cult / Christian-vs-pagan behavior. | c | yes: Zeno |
| PlayerRuntimeState + 57 | PlayerRuntimeState.revealed_tiles_bitset[1300] | Recovered Struct Field | Player Runtime State / Visibility | High | Visibility stamping and lookup helpers address this exact 1300-byte gap as a 13-bytes-per-row bitset, and fog overlay classification consumes the same data. | c | yes: Parfit |
| BuildingRecord + 435 | BuildingRecord.plague_state | Recovered Struct Field | Buildings / Plague | High | The low three bits at this byte control plague countdown, block income, trigger plague messages, and are seeded when a plagued stack enters the building. | c | yes: Hilbert |

## Deferred / Ambiguous
- `sub_410260` still looks like a “current or reachable queued path step is drawable for the viewed player” predicate, but the shortest non-misleading public name is not locked down enough yet.
- `Map_ClassifyFogOfWarOverlayForPlayer` is stable at the behavior level, but the exact orientation mapping of overlay codes `1..12` remains intentionally undocumented until the sprite sheet is fully cross-labeled.
- `PlayerRuntimeState.religion_flag` is semantically stable as a two-way religion/alignment switch, but the code alone does not justify a stronger lore-facing enum name than “religion flag.”
- Hidden treasure tile ids `752` and `755` are both provably treasure-bearing, but their exact designer-facing distinction is still deferred.

## Batch 36 – Rules Fact And Upgrade Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| Unit_MoveTrack_1 | Unit_MoveTrackNearTile | Function | Movement / Path Planning | High | The original debug string survives in the binary as `Unit_MoveTrackNear(%d,%d,%d)`, and the implementation temporarily clears the destination occupancy, calls the normal track planner, then trims the final step so the path stops adjacent to the target tile instead of entering it. | c, asm, exe | yes: Lorentz |
| sub_41DB20 | Rules_RebuildCastleSiteFacts | Function | Rules / Castle Sites | High | Full-map rebuild pass that scans every tile and re-logs tiles `707` and `711` via the `(zamek_place %d %d)` rules fact emitter. | c | no |
| sub_41F850 | Building_CanStartUpgrade | Function | Buildings / Upgrades | High | Pure predicate that allows an upgrade only when the current stage is below both the hard cap and the building tier cap and no upgrade timer is already running. | c | no |
| sub_41F890 | Building_TryStartUpgrade | Function | Buildings / Upgrades | High | Calls `Building_CanStartUpgrade`, checks the per-stage resource cost table against the building-local stored pool, seeds the upgrade timer, and deducts the cost on success. | c | no |
| sub_43F9B0 | Rules_RebuildTempleFacts | Function | Rules / Religious Sites | High | Full-map rebuild pass that re-logs every non-zero `MapTile_GetReligiousSiteCategory` tile through the `(swiatynia %d %d)` fact logger. | c | no |
| sub_443B60 | Rules_RebuildTreasureFacts | Function | Rules / Treasure | High | Full-map rebuild pass that re-logs every `MapTile_HasHiddenTreasure` tile through the `(skarb %d %d)` fact logger. | c | no |
| sub_455200 | Rules_LogTempleFact | Function | Rules / Religious Sites | High | Emits the exact rules payload `(swiatynia row col)`, making it the temple-fact logger rather than a generic map note helper. | c | no |
| sub_455230 | Rules_LogTreasureFact | Function | Rules / Treasure | High | Emits the exact rules payload `(skarb row col)` for hidden-treasure tiles. | c | no |
| sub_455260 | Rules_RetractTreasureFact | Function | Rules / Treasure | High | Emits the exact rules payload `(kasuj skarb row col)` to retract a previously logged treasure fact after digging. | c | no |
| sub_455290 | Rules_RetractTempleFact | Function | Rules / Religious Sites | High | Emits the exact rules payload `(kasuj swiatynie row col)` after temple-state changes consume or clear the prior fact. | c | no |
| sub_455C90 | Rules_LogCastleSiteFact | Function | Rules / Castle Sites | High | Emits the exact rules payload `(zamek_place row col)`, which is used by the castle-site rebuild scan. | c | no |
| sub_457E00 | Unit_ExecuteQueuedPathAndCheckFinished | Function | Movement / Path Execution | High | Thin wrapper that executes one queued-path step batch and immediately tests whether the embedded `QueuedPathBuffer.waypoint_count` dropped to zero. | c | yes: Lorentz |
| sub_455450 | Building_TryStartUpgradeByIndex | Function | Buildings / Upgrades | High | Thin index wrapper that forwards `UNIT_RECORD(buildingIndex)` into `Building_TryStartUpgrade`, preserving the same upgrade-start side effects for callers that only hold a building id. | c | no |
| sub_455650 | Building_CanStartUpgradeByIndex | Function | Buildings / Upgrades | High | Thin index wrapper that forwards `UNIT_RECORD(buildingIndex)` into `Building_CanStartUpgrade` for id-based UI or rules callers. | c | no |

## Deferred / Ambiguous
- `sub_410260` still looks like a “current or reachable queued path step is drawable for the viewed player” predicate, but the shortest non-misleading public name is not locked down enough yet.
- `sub_41D980` / `sub_41DA50` clearly belong to the castle-site placement cluster, but their mode parameter inverts or narrows the terrain predicate in a way that is still too easy to overstate.
- `sub_41EF10` / `sub_41EF80` / `sub_41F020` still line up with barracks / hospital / smithy-style castle add-on builders by debug-string evidence, but the add-on-bit mapping is not settled cleanly enough for a safe public rename.
- `sub_457E50` is only a wrapper around `Unit_AddToGroup(..., 0)`; it likely wants a group-merge wrapper name, but the narrow behavioral distinction is not yet corroborated well enough.

## Batch 37 – Castle Foundations And Addons Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_410260 | UnitStack_CanReachQueuedPathTileWithFogOverlay | Function | Movement / Fog Of War | Medium | Checks the current tile plus all queued-path waypoints whose cumulative cost does not exceed the stack's current action points, and returns true if any such tile yields a non-zero `Map_ClassifyFogOfWarOverlayForPlayer` result. The implementation is stable, but the name stays implementation-shaped to avoid overstating it as a pure visibility predicate. | c, asm | yes: Lorentz |
| sub_41D980 | MapTile_IsCastleFoundationTile | Function | Map / Castle Sites | High | The raw terrain test accepts tile ids `707..714`, hover/info uses the matching text table headed by `Fundamenty`, and building/trap placement logic treats the same family as a special blocked castle-foundation terrain cluster. | c, asm | yes: Hilbert |
| sub_41DA50 | MapTile_IsCastleFoundationAnchorTile | Function | Map / Castle Sites | High | Narrower castle-foundation subset predicate that accepts only tile ids `707` and `711`; map rebuild code uses this exact subset when caching and logging castle-site anchors. | c, asm | yes: Hilbert |
| sub_41DBA0 | BuildCursor_IsPlacementValid | Function | UI / Build Placement | Medium | Build-preview validator used by the placement cursor. It checks mode-specific range from the acting stack, terrain blockers, occupancy, traps, religious sites, hidden treasure, and, in one mode, excludes castle foundation tiles. | c | yes: Hilbert |
| sub_41EF10 | Building_BuildBarracks | Function | Buildings / Castle Addons | High | The debug string is literally `Building_BuildBarracks()`, the castle UI wrapper uses `budowa\\baraki`, and `Rules_AssertCastleFact` maps bit `0x02` to `koszary` for the same add-on. | c, asm, exe | yes: Zeno |
| sub_41EF80 | Building_BuildHospital | Function | Buildings / Castle Addons | High | The debug string is literally `Building_BuildHospital()`, the host command is `KupSzpital`, and `Rules_AssertCastleFact` maps bit `0x01` to `szpital`. | c, asm | yes: Zeno |
| sub_41F020 | Building_BuildSmiths | Function | Buildings / Castle Addons | High | The original debug string is literally `Building_BuildSmiths()`, the castle UI wrapper uses `budowa\\kuznia`, and `Rules_AssertCastleFact` maps bit `0x10` to `kuznia`, so the binary's own internal wording is the safest recovered symbol. | c, asm | yes: Zeno |
| sub_420CD0 | Castle_BuildSchoolWithAnimation | Function | Castle UI / Addon Construction | High | Calls `Building_BuildSchool`, verifies bit `0x08`, clones the building record, clears the just-built bit on the clone, and plays the `budowa\\szkola` construction resource through the castle-build animation path. | c, asm | yes: Zeno |
| sub_420D50 | Castle_BuildWorkshopWithAnimation | Function | Castle UI / Addon Construction | High | Same castle-build animation wrapper pattern for the workshop add-on, keyed by bit `0x04` and the `budowa\\warsztat` resource. | c, asm | yes: Zeno |
| sub_420DD0 | Castle_BuildBarracksWithAnimation | Function | Castle UI / Addon Construction | High | Same wrapper pattern for the barracks add-on, keyed by bit `0x02` and the `budowa\\baraki` resource. | c, asm | yes: Zeno |
| sub_420E50 | Castle_BuildHospitalWithAnimation | Function | Castle UI / Addon Construction | High | Same wrapper pattern for the hospital add-on, keyed by bit `0x01` and a religion-specific hospital construction resource. | c, asm | yes: Zeno |
| sub_420EF0 | Castle_BuildSmithsWithAnimation | Function | Castle UI / Addon Construction | High | Same wrapper pattern for the smiths add-on, keyed by bit `0x10` and the `budowa\\kuznia` construction resource. | c, asm | yes: Zeno |
| sub_455490 | Building_BuildSchoolByIndex | Function | Buildings / Castle Addons | High | Thin building-index wrapper over `Building_BuildSchool`. | c | yes: Zeno |
| sub_4554B0 | Building_BuildSmithsByIndex | Function | Buildings / Castle Addons | High | Thin building-index wrapper over `Building_BuildSmiths`. | c | yes: Zeno |
| sub_455530 | Building_BuildBarracksByIndex | Function | Buildings / Castle Addons | High | Thin building-index wrapper over `Building_BuildBarracks`. | c | yes: Zeno |
| sub_455550 | Building_BuildHospitalByIndex | Function | Buildings / Castle Addons | High | Thin building-index wrapper over `Building_BuildHospital`. | c | yes: Zeno |
| sub_4555C0 | Building_BuildWorkshopByIndex | Function | Buildings / Castle Addons | High | Thin building-index wrapper over `Building_BuildWorkshop`. | c | yes: Zeno |
| sub_455D50 | Rules_LogCastleSchemeFact | Function | Rules / Castle Sites | High | Emits the exact rules payload `(schemat %d %d %d)` and is called immediately after castle construction logging, making it the castle-scheme fact logger. | c | no |
| sub_455DC0 | Rules_LogCastleUnderConstructionFact | Function | Rules / Castle Sites | High | Emits the exact rules payload `(zamek w budowie %d)` when a new castle site is claimed for construction. | c, asm | no |
| sub_455DF0 | Rules_LogCastleBuiltFactAndScheme | Function | Rules / Castle Sites | High | Emits `(zbudowano zamek %d)` and then immediately logs a scheme fact through `Rules_LogCastleSchemeFact`, so the paired behavior is stable. | c | no |
| sub_455E20 | Rules_LogAssignedCastleFact | Function | Rules / Castle Sites | High | Emits the exact rules payload `(wyznaczony zamek %d %d)`. | c | no |
| sub_455E50 | Rules_LogAssignedPlayerFact | Function | Rules / Castle Sites | High | Emits the exact rules payload `(wyznaczony gracz %d %d)`. | c | no |
| sub_455E80 | Building_SelectedAddonMatchesTypeByIndex | Function | Buildings / Production Licences | High | Reads `BuildingRecord.selected_addon_slot_index` and compares the indexed `addon_type_ids` entry against the requested type id. | c | no |
| sub_455F20 | Building_HasGarrisonUnitTypeByIndex | Function | Buildings / Garrison | High | Scans the 12 embedded 31-byte garrison entries in `BuildingRecord` and returns true when any slot holds the requested unit type id. | c | no |
| sub_455FF0 | Map_RebuildCastleSiteAnchorCache | Function | Map / Castle Sites | Medium | Rebuilds the global castle-site anchor coordinate arrays by scanning the full map for `MapTile_IsCastleFoundationAnchorTile`; the exact consumer cluster is rules/AI-facing, but the cache behavior itself is explicit. | c, asm | yes: Hilbert |
| sub_457E50 | Script_UnitAddToGroup | Function | Script / Unit Grouping | High | Pure script-layer wrapper around `Unit_AddToGroup(a1, a2, 0, ...)`, sitting inside the script dispatch cluster and adding no distinct gameplay logic beyond the hardcoded mode `0`. | c, asm | yes: Lorentz |
| off_511B98 | g_CastleFoundationTexts | Table | Map / Castle Sites | High | Hover/info code selects this table when `MapTile_IsCastleFoundationTile` is true, and the asm data headed by `Fundamenty` confirms it is the castle-foundation text family. | c, asm | yes: Hilbert |
| dword_544570 | g_CastleSiteAnchorRows | Global | Map / Castle Sites | Medium | Filled exclusively by `Map_RebuildCastleSiteAnchorCache` with the row component of each `707` / `711` anchor tile. | c, asm | yes: Hilbert |
| dword_544574 | g_CastleSiteAnchorColumns | Global | Map / Castle Sites | Medium | Filled exclusively by `Map_RebuildCastleSiteAnchorCache` with the column component of each `707` / `711` anchor tile. | c, asm | yes: Hilbert |
| BuildingRecord + 416 / building_flags | BuildingRecord.castle_addon_flags | Recovered Struct Field | Buildings / Castle Addons | High | Castle add-on builders and `Rules_AssertCastleFact` converge on the exact bit mapping: `0x01` hospital, `0x02` barracks, `0x04` workshop, `0x08` school, `0x10` smiths. | c, asm | yes: Zeno |

## Deferred / Ambiguous
- `MapTile_IsCastleFoundationTile` is stable for the `707..714` family and `MapTile_IsCastleFoundationAnchorTile` is stable for `707` / `711`, but the exact semantic split among the non-anchor variants remains unresolved.
- `sub_455D90` logs `(zdobyty %d %d %d)`, but this pass did not pin down whether the fact is castle-specific, faction-specific, or a broader conquest record.

## Batch 37 – Trap Facts And Castle Fact Handles
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_4551A0 | Rules_LogTrapFact | Function | Rules / Traps | High | Emits the exact rules payload `(pulapka row col)` and is called when map-load reconstruction finds armed trap tiles. | c, asm | no |
| sub_4551D0 | Rules_RetractTrapFact | Function | Rules / Traps | High | Emits the exact rules payload `(kasuj pulapke row col)` immediately after a trap fires and the owner mask is cleared from the tile. | c, asm | no |
| BuildingRecord + 463 | BuildingRecord.castle_fact_id | Recovered Struct Field | Buildings / Castle Facts | High | `Rules_AssertCastleFact` stores its returned fact handle at `+463`, `Rules_RetractCastleFact` retracts and zeroes the same dword, and `Building_OnGarrisonChange` plus `Unit_CaptureBuilding` update its `moc` and `gracz` attributes. | c, exe | yes: Bacon |

## Deferred / Ambiguous
- `sub_455150` updates the `gracz` attribute on `BuildingRecord.castle_fact_id`, but this pass stopped short of renaming it until the non-castle call envelope is ruled out more rigorously.

## Batch 40 – Building Rules Host Stat Wrappers
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_455470 | Building_GetTaxPressureByIndex | Function | Buildings / Rules Host Stats | High | The `Podatek` rules host stub at `loc_4568F6` dispatches directly to this getter, which returns `BuildingRecord + 436 & 0x3F`, the same tax-pressure value consumed by `Building_GetTaxPressureTier`. | c, asm | no |
| sub_4554D0 | Building_GetWallStrengthByIndex | Function | Buildings / Rules Host Stats | High | The `SilaMurow` rules host stub at `loc_456A10` dispatches directly to this getter, which returns byte `+421`, the per-building wall-upgrade strength/stage field. | c, asm | no |
| sub_4554F0 | Building_GetMoneyByIndex | Function | Buildings / Rules Host Stats | High | The `Pieniadze` rules host stub at `loc_4569DA` dispatches directly to this getter, which returns the building-local stored money pool at `+438`. | c, asm | no |
| sub_455510 | Building_GetCastleStrengthByIndex | Function | Buildings / Rules Host Stats | High | The `SilaZamku` rules host stub at `loc_456A46` dispatches directly to this wrapper around `Building_GetTotalValue`, exposing the building's aggregate strength/value to the rules layer. | c, asm | no |
| sub_455580 | Building_GetTechLevelByIndex | Function | Buildings / Rules Host Stats | High | The `PoziomTech` rules host stub at `loc_456BBB` dispatches directly to this getter, which returns the low three bits at `+444`. | c, asm | no |
| sub_4555A0 | Building_GetTypeByIndex | Function | Buildings / Rules Host Stats | High | The `TypBudowli` rules host stub at `loc_456BF1` dispatches directly to this getter, which returns the raw building type byte at offset `+4`. | c, asm | no |
| sub_4555E0 | Building_GetSatisfactionByIndex | Function | Buildings / Rules Host Stats | High | The `Zadowolenie` rules host stub at `loc_456C93` dispatches directly to this getter, which returns byte `+434`, the clamped satisfaction value used by population growth. | c, asm | no |
| sub_455600 | Building_GetPeasantCountByIndex | Function | Buildings / Rules Host Stats | High | The `IloscChlopow` rules host stub at `loc_456CFF` dispatches directly to this getter, which returns the low 12 bits at `+430`, the same population value updated by `Building_UpdatePopulationGrowth`. | c, asm | no |
| sub_455670 | Building_GetGarrisonCountByIndex | Function | Buildings / Rules Host Stats | High | The `IloscOddzialow` rules host stub at `loc_456E7F` dispatches directly to this wrapper around `Building_CountGarrison`. | c, asm | no |
| sub_455690 | Building_IsGarrisonFullByIndex | Function | Buildings / Rules Host Stats | High | The `MaxIloscOddzialow` rules host stub at `loc_456F87` dispatches directly to this predicate, which returns true exactly when the garrison count reached the 12-slot limit. | c, asm | no |
| BuildingRecord + 421 | BuildingRecord.wall_strength | Recovered Struct Field | Buildings / Walls | High | The `SilaMurow` rules host getter returns byte `+421`, and wall-upgrade logic reads and advances the same byte as the staged wall-strength field. | c, asm | no |
| BuildingRecord + 430 | BuildingRecord.peasant_count | Recovered Struct Field | Buildings / Population | High | The `IloscChlopow` rules host getter returns the low 12 bits at `+430`, and `Building_UpdatePopulationGrowth` mutates the same value as the building's peasant population. | c, asm | no |
| BuildingRecord + 434 | BuildingRecord.satisfaction | Recovered Struct Field | Buildings / Population | High | The `Zadowolenie` rules host getter returns byte `+434`, and `Building_UpdatePopulationGrowth` clamps it between `0` and `100` as a settlement satisfaction/happiness meter. | c, asm | no |
| BuildingRecord + 438 / stored_resource_pool | BuildingRecord.stored_money | Recovered Struct Field | Buildings / Economy | High | The `Pieniadze` rules host getter returns dword `+438`, while add-on purchase and income logic spend and replenish the same pool as money. | c, asm | no |
| BuildingRecord + 444 / level_bits | BuildingRecord.tech_level_bits | Recovered Struct Field | Buildings / Technology | High | The `PoziomTech` rules host getter returns the low three bits at `+444`, and upgrade/add-on requirement checks treat those bits as the building's tech level cap. | c, asm | no |

## Batch 41 – Building Production And Licence Wrappers
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_455620 | Building_HasProductionByIndex | Function | Buildings / Production Wrappers | High | The `IsProduction` rules host stub at `loc_456CC9` dispatches directly to this predicate, which returns true when the selected production/licence slot byte at `+414` is not `-1`. | c, asm | no |
| sub_4556C0 | Building_RepairUnitByIndex | Function | Buildings / Production Wrappers | High | Thin building-id wrapper that forwards directly into `Building_RepairUnit`. | c | no |
| sub_4556E0 | Building_TrainUnitByIndex | Function | Buildings / Production Wrappers | High | Thin building-id wrapper that forwards directly into `Building_TrainUnit`. | c | no |
| sub_455700 | Building_SetUnitProductionByIndex | Function | Buildings / Production Wrappers | High | Thin building-id wrapper that forwards directly into `Building_SetUnitProduction`. | c | no |
| sub_455720 | Building_RemoveUnitLicenceByIndex | Function | Buildings / Production Wrappers | High | Thin building-id wrapper that forwards directly into `Building_RemoveUnitLicence`. | c | no |
| sub_4557C0 | Building_HasUnitLicenceByIndex | Function | Buildings / Licence Wrappers | High | The `IsLicence` rules host stub at `loc_45692C` dispatches directly to this wrapper around `Building_HasAddonInGarrison`, exposing whether the castle currently owns the requested production licence. | c, asm | no |
| sub_4557E0 | Building_BuyUnitLicenceByIndex | Function | Buildings / Licence Wrappers | High | The `BuyLicence` rules host stub at `loc_456B0D` dispatches directly to this building-id wrapper over the licence-purchase path. | c, asm | no |
| sub_455800 | Building_CanBuyUnitLicenceByIndex | Function | Buildings / Licence Wrappers | High | The `CanBuyLicence` rules host stub at `loc_456D8F` dispatches directly to this predicate, which forwards into `Building_CanEquipAddon` for the requested licence type. | c, asm | no |

## Batch 38 – Castle Lifecycle Logging Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_41D930 | Building_LogBuiltCastleFacts | Function | Buildings / Castle Lifecycle | High | Pure wrapper that derives the building id from the record's footprint tile and forwards it twice into `Rules_LogCastleBuiltFactAndScheme`; scenario/setup paths call it after `Building_New` to seed rules facts for pre-existing castles. | c | no |
| sub_41E050 | Building_Stop | Function | Buildings / Castle Lifecycle | High | Embedded debug string is `Building_Stop(0x%08x)`, and the implementation ejects all occupied garrison slots, clears the active-building state word, and retracts the castle fact. | c, asm | no |
| sub_41F900 | Unit_CaptureBuilding | Function | Unit Lifecycle / Building Capture | High | Embedded debug string is `Unit_CaptureBuilding(%d,%d)`, and the implementation transfers building ownership to the acting stack's player, updates building tech tier, logs a capture fact, moves the unit inside, handles special prisoner slots, and refreshes nearby tiles. | c, asm | no |
| sub_455CF0 | Rules_LogNewCastleFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for the payload `(powstal-nowy-zamek %d %d)`, called from `Building_FinishConstruction` after `Rules_LogCastleBuiltFactAndScheme`. | c, asm | no |
| sub_455D20 | Rules_LogCastleDestroyedFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for `(zginal-zamek %d %d)`, reached from `Rules_RetractCastleFact` when a castle/building record is removed. | c, asm | no |
| sub_455D90 | Rules_LogBuildingCapturedFact | Function | Rules / Building Capture | Medium | Literal rules logger for `(zdobyty %d %d %d)` called only from `Unit_CaptureBuilding`; the three arguments are the capturing player id, building id, and current turn number. The capture path is generic building capture, not castle-only capture. | c, asm | no |

## Batch 39 – Castle Transfer And Addon Field Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_4554B0 | Building_BuildSmithsByIndex | Function | Buildings / Castle Addons | High | Thin id-based wrapper that forwards directly into `Building_BuildSmiths`, preserving the same add-on build side effects for callers that only hold a building id. | c | no |
| sub_455530 | Building_BuildBarracksByIndex | Function | Buildings / Castle Addons | High | Thin id-based wrapper that forwards directly into `Building_BuildBarracks`. | c | no |
| sub_455550 | Building_BuildHospitalByIndex | Function | Buildings / Castle Addons | High | Thin id-based wrapper that forwards directly into `Building_BuildHospital`. | c | no |
| sub_455CC0 | Rules_LogBuildingTransferFact | Function | Rules / Building Transfer | Medium | Literal rules logger for `(budowanie transfer 0 0 %d %d %d)`, reached from `Building_Transfer` after army-fact relinking in the no-human-controller branch. The name stays implementation-shaped to avoid over-claiming the designer-facing semantics of the three payload numbers. | c, asm | no |
| sub_455D50 | Rules_LogCastleSchemeFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for `(schemat %d %d %d)` with a randomized scheme value `1..3`; `Rules_LogCastleBuiltFactAndScheme` delegates to it immediately after logging castle construction. | c, asm | no |
| sub_455DC0 | Rules_LogCastleUnderConstructionFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for `(zamek w budowie %d)`, emitted immediately after a castle site is claimed for construction. | c, asm | no |
| sub_455DF0 | Rules_LogCastleBuiltFactAndScheme | Function | Rules / Castle Lifecycle | High | Logs `(zbudowano zamek %d)` and then immediately logs a scheme fact through `Rules_LogCastleSchemeFact`, so the paired behavior is explicit. | c, asm | no |
| sub_455E20 | Rules_LogAssignedCastleFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for `(wyznaczony zamek %d %d)`. | c, asm | no |
| sub_455E50 | Rules_LogAssignedPlayerFact | Function | Rules / Castle Lifecycle | High | Literal rules logger for `(wyznaczony gracz %d %d)`. | c, asm | no |
| sub_455FF0 | Map_RebuildCastleSiteAnchorCache | Function | Map / Castle Sites | Medium | Rebuilds the global castle-site anchor coordinate arrays by scanning the map for `MapTile_IsCastleFoundationAnchorTile`; consumers are rules/AI-facing, but the cache behavior itself is explicit. | c, asm | no |
| dword_544570 | g_CastleSiteAnchorRows | Global | Map / Castle Sites | Medium | Filled exclusively by `Map_RebuildCastleSiteAnchorCache` with the row component of each castle-foundation anchor tile. | c, asm | no |
| dword_544574 | g_CastleSiteAnchorColumns | Global | Map / Castle Sites | Medium | Filled exclusively by `Map_RebuildCastleSiteAnchorCache` with the column component of each castle-foundation anchor tile. | c, asm | no |
| BuildingRecord + 416 / building_flags | BuildingRecord.castle_addon_flags | Recovered Struct Field | Buildings / Castle Addons | High | Castle add-on builders and `Rules_AssertCastleFact` converge on the exact bit mapping: `0x01` hospital, `0x02` barracks, `0x04` workshop, `0x08` school, `0x10` smiths. | c, asm | no |

## Deferred / Ambiguous
- No additional medium/high-confidence candidates remained in the castle transfer and castle-fact neighborhood after this batch. The next unresolved local target is the exact gameplay meaning of the `sub_455F60` distance/cache predicate and its paired `dword_544578` / `dword_54457C` arrays.

## Batch 39 – Castle Foundations And Addon Flags Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary | Sources | Subagent Evidence |
|---|---|---|---|---|---|---|---|
| sub_41D980 | MapTile_IsCastleFoundationTile | Function | Map / Castle Sites | High | The predicate accepts tile ids `707..714`, the hover/info path selects the `Fundamenty` text table only when it passes, and castle placement logic treats the same family as special blocked terrain. | c, asm, map | no |
| sub_41DA50 | MapTile_IsCastleFoundationAnchorTile | Function | Map / Castle Sites | High | Narrower subset predicate that accepts only tile ids `707` and `711`; the anchor-cache rebuild records exactly this subset as castle-site anchors. | c | no |
| sub_41DBA0 | BuildCursor_IsPlacementValid | Function | UI / Building Placement | Medium | Build-preview validation enforces cursor radius, blocked tiles, occupant checks, trap/religious-site/treasure exclusions, and extra castle-foundation restrictions before construction is allowed. | c | no |
| sub_41EF10 | Building_BuildBarracks | Function | Buildings / Castle Addons | High | The debug string is `Building_BuildBarracks() - %d,%d`, and the helper spends resources, sets add-on bit `0x02`, and arms the construction-in-progress flag. | c, asm | no |
| sub_41EF80 | Building_BuildHospital | Function | Buildings / Castle Addons | High | The debug string is `Building_BuildHospital() - %d,%d`, and the helper spends resources, sets add-on bit `0x01`, and arms the construction-in-progress flag. | c, asm | no |
| sub_41F020 | Building_BuildSmiths | Function | Buildings / Castle Addons | High | The debug string is `Building_BuildSmiths() - %d,%d`, and the helper spends resources, sets add-on bit `0x10`, and arms the construction-in-progress flag. | c, asm | no |
| sub_4554B0 | Building_BuildSmithsByIndex | Function | Buildings / Castle Addons | High | Thin building-id wrapper that forwards directly into `Building_BuildSmiths`. | c | no |
| sub_455530 | Building_BuildBarracksByIndex | Function | Buildings / Castle Addons | High | Thin building-id wrapper that forwards directly into `Building_BuildBarracks`. | c | no |
| sub_455550 | Building_BuildHospitalByIndex | Function | Buildings / Castle Addons | High | Thin building-id wrapper that forwards directly into `Building_BuildHospital`. | c | no |
| sub_455CC0 | Rules_LogBuildingTransferFact | Function | Rules / Buildings | High | Emits the exact rules payload `(budowanie transfer 0 0 %d %d %d)` from the building-transfer path after a transfer stack is linked into the rules system. | c, asm | no |
| sub_455D50 | Rules_LogCastleSchemeFact | Function | Rules / Castle Lifecycle | High | Emits the exact rules payload `(schemat %d %d %d)` after `Rng_RandRange(1, 3)`, and the castle-built logger calls it immediately after the built fact. | c, asm | no |
| sub_455DC0 | Rules_LogCastleUnderConstructionFact | Function | Rules / Castle Lifecycle | High | Emits the exact rules payload `(zamek w budowie %d)` directly after `Rules_AssertCastleFact` during `Building_New`. | c, asm | no |
| sub_455DF0 | Rules_LogCastleBuiltFactAndScheme | Function | Rules / Castle Lifecycle | High | Emits `(zbudowano zamek %d)` and then immediately calls `Rules_LogCastleSchemeFact`, making the paired behavior explicit. | c, asm | no |
| sub_455E20 | Rules_LogAssignedCastleFact | Function | Rules / Castle Lifecycle | High | Emits the exact rules payload `(wyznaczony zamek %d %d)`. | c, asm | no |
| sub_455E50 | Rules_LogAssignedPlayerFact | Function | Rules / Castle Lifecycle | High | Emits the exact rules payload `(wyznaczony gracz %d %d)`. | c, asm | no |
| sub_455FF0 | Map_RebuildCastleSiteAnchorCache | Function | Map / Castle Sites | Medium | Rebuilds the cached row/column arrays by scanning the full map and recording every `MapTile_IsCastleFoundationAnchorTile` tile. | c | no |
| off_511B98 | g_CastleFoundationTexts | Table | Map / Castle Sites | High | The hover/info path selects this multilingual table only for castle-foundation terrain, and the asm/map data label it with `Fundamenty`. | c, asm, map | no |
| dword_544570 | g_CastleSiteAnchorRows | Global | Map / Castle Sites | Medium | Filled only by `Map_RebuildCastleSiteAnchorCache` with the row component of each cached castle-site anchor tile. | c | no |
| dword_544574 | g_CastleSiteAnchorColumns | Global | Map / Castle Sites | Medium | Filled only by `Map_RebuildCastleSiteAnchorCache` with the column component of each cached castle-site anchor tile. | c | no |
| BuildingRecord + 416 / building_flags | BuildingRecord.castle_addon_flags | Recovered Struct Field | Buildings / Castle Addons | High | The castle add-on builders and `Rules_AssertCastleFact` converge on the exact bit mapping: `0x01` hospital, `0x02` barracks, `0x04` workshop, `0x08` school, `0x10` smiths. | c, asm | no |

## Deferred / Ambiguous
- `sub_410260` still looks like a “current or reachable queued path step is drawable for the viewed player” predicate, but the shortest non-misleading public name is not locked down enough yet.
- Non-anchor castle-foundation tile ids `708, 709, 710, 712, 713, 714` still behave as foundation variants, but their exact piece/orientation mapping remains deferred.
- `sub_457E50` is only a wrapper around `Unit_AddToGroup(..., 0)`; it likely wants a group-merge wrapper name, but the narrow behavioral distinction is not yet corroborated well enough.
