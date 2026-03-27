# Rename Progress Log

## Totals
- Queen renames: 12
- Port renames: 10
- Unit renames: 16
- Castle renames: 2
- Tile renames: 1
- Other renames: 0

### By Identifier Kind
- Functions: 18
- Globals: 23
- Static file-scope: 0
- Parameters: 0
- Locals: 0

## Batches

### Batch 1 – Queen Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 1 | 1 | Global | clash95.c | off_519010 | g_QueenMoodTexts | High | Text array controls the queen status descriptions shown in the UI panel; new name reflects content. |
| 2 | 2 | Function | clash95.c | sub_44FD90 | Queen_DrawMoodPanel | High | Function renders the queen portrait/mood text on the turn summary screen; rename clarifies intent. |
| 3 | 3 | Function | clash95.c | sub_446480 | Queen_ShowWhimDialog | High | Function displays the "QueenWhimMessage" window asking the player to fulfill a whim; name now mirrors behaviour. |
| 4 | 4 | Function | clash95.c | UI_NotifyText | Queen_ShowNotification | High | Function exclusively shows queen messages with her sprite; renamed to stress that it’s a queen-specific notification window. |

### Batch 2 – Queen Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 5 | 5 | Function | clash95.c | sub_446F40 | Queen_ShowProposalDialog | High | Presents the marriage proposal prompt ("NewQueenWindow") where the player accepts or rejects the princess envoy; new name captures the interaction. |
| 6 | 6 | Global | clash95.c | off_518010 | g_QueenProposalPrompt | High | String set used to ask the player whether to marry the princess envoy, so renamed to describe the prompt content. |

### Batch 3 – Port Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 7 | 7 | Global | clash95.c | *(_DWORD *)(gameData + 586374) | PORT_ROW | High | This offset stores the map row of the discovered port; naming it clarifies all shoreline math. |
| 8 | 8 | Global | clash95.c | *(_DWORD *)(gameData + 586378) | PORT_COLUMN | High | Companion offset holding the port column; explicit name improves tile indexing code. |
| 9 | 9 | Global | clash95.c | *(_DWORD *)(gameData + 586382) | PORT_NEXT_SUPPLY_TURN | High | Field tracks when the next ship arrives, so the new name documents its scheduling role. |
| 10 | 10 | Global | clash95.c | *(_DWORD *)(gameData + 586386) | PORT_SUPPLY_READY_FLAG | High | Boolean gate that enables troop spawning/UI when ships dock; renamed to show it reflects ready supplies. |
| 11 | 11 | Global | clash95.c | *(_DWORD *)(gameData + 586390) | PORT_SUPPLY_UNIT_COUNT | High | Holds the number of reinforcement units generated with each shipment, warranting a count-based name. |
| 12 | 12 | Global | clash95.c | *(_DWORD *)(gameData + 586394) | PORT_NEEDS_SHORE_REFRESH | High | Flag toggles the shoreline tiles when a ship docks, so the name documents that refresh behaviour. |
| 13 | 13 | Function | clash95.c | sub_443230 | Port_HasSupplyReady | High | Function simply returned the port’s supply-ready flag; the new name exposes that check directly. |
| 14 | 14 | Function | clash95.c | sub_443240 | Port_BuildDockingTrack | Medium | Builds/returns the move track leading units through the dock; name reflects the generated docking path. |
| 15 | 15 | Global | clash95.c | off_517BD8 | g_PortArrivalTexts | High | String array provides multilingual "reinforcements arrived" text, so the name highlights the arrival message. |
| 16 | 16 | Global | clash95.c | off_517BE4 | g_PortEmptyTexts | High | These entries are the "Port is empty" lines shown when no supplies are ready; new name states that role. |

### Batch 4 – Unit Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 17 | 17 | Global | clash95.c | dword_511B54 | g_UnitSearchCursor | High | Tracks the rotating cursor used when scanning unit slots, so renaming exposes its search-role. |
| 18 | 18 | Global | clash95.c | dword_511B58 | g_SelectedUnitIndex | High | Widely used global storing the currently selected unit; descriptive name removes guesswork across the UI/logic. |
| 19 | 19 | Global | clash95.c | dword_511B5C | g_LastSelectedUnitIndex | High | Keeps the prior selection to restore focus after temporary actions; name captures that behaviour. |
| 20 | 20 | Global | clash95.c | gameData + 509674 + 467 * idx | UNIT_RECORD(idx) | High | Introduced a macro for the per-unit record base, eliminating repeated magic offsets for unit data access. |

### Batch 5 – Castle Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 21 | 21 | Global | clash95.c | dword_526A64 | g_CastleUnitRecord | High | Holds the currently highlighted castle unit record throughout the castle UI; new name shows its purpose. |
| 22 | 22 | Function | clash95.c | sub_422100 | Castle_UpdateGateToggles | Medium | Function only flips gate-related UI buttons based on castle flags, so the name describes that behaviour. |

### Batch 6 – Tile Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 23 | 23 | Global | clash95.c | gameData + 200 * row + 2 * column + 556374 | TILE_INDEX(row, column) | High | Created a macro for tile lookups so that terrain reads no longer rely on raw offsets into the world map buffer. |

### Batch 7 – Queen Wave (offset macros)
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 24 | 24 | Global | clash95.c | gameData + 1423 * dword_5202EC | PLAYER_DATA(dword_5202EC) | High | Introduced a helper for the active player’s data block instead of repeating the 1423-byte stride arithmetic. |
| 25 | 25 | Global | clash95.c | *(_BYTE *)(PLAYER_DATA(...) + 141443) | PLAYER_QUEEN_MOOD(playerIndex) | High | Named the queen mood field so comparisons no longer reference the raw offset 141443. |
| 26 | 26 | Global | clash95.c | *(_BYTE *)(PLAYER_DATA(...) + 141444) | PLAYER_QUEEN_WHIM(playerIndex) | High | This byte stores the current queen whim sprite/choice; macro makes that explicit. |
| 27 | 27 | Global | clash95.c | *(_WORD *)(PLAYER_DATA(...) + 141445) | PLAYER_QUEEN_NEXT_REVIEW(playerIndex) | High | Added a descriptive alias for the next-turn counter that schedules queen events. |
| 28 | 28 | Global | clash95.c | *(_DWORD *)(PLAYER_DATA(...) + 140051) | PLAYER_HAS_HUMAN_CONTROLLER(playerIndex) | Medium | New macro explains that the flag at offset 140051 reflects whether a human is controlling the player. |
| 29 | 29 | Global | clash95.c | *(_WORD *)(gameData + 140022) | GAME_TURN_COUNTER | High | The global turn counter offset now has a name, avoiding raw reads of address 140022. |

### Batch 8 – Unit Stack Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 30 | 30 | Function | clash95.c | sub_40F3C0 | UnitStack_IsIndexOnMap | High | Function scans the 200×N map occupancy grid at `gameData + 556374` to see whether the given stack id is still on the board; rename clarifies it’s a stack-level map membership test. |
| 31 | 31 | Function | clash95.c | sub_40F440 | UnitSlot_InitFromType | High | Routine seeds the 31-byte unit slot record with base stats, morale, and owner flags based on the requested unit type and player, so the name reflects that initialization behavior. |
| 32 | 32 | Function | clash95.c | sub_40F4D0 | UnitStack_ResetRecord | High | Wrapper around `UnitSlot_InitFromType` that clears the remaining slots, path buffer, and owner byte for a stack record; rename documents that it resets the entire stack entry. |
| 33 | 33 | Function | clash95.c | sub_40F7C0 | UnitStack_KillByIndex | High | Thin wrapper that forwards a stack index to `Unit_Kill` after converting it to the record pointer; name explains it kills stacks by their roster index. |
| 34 | 34 | Function | clash95.c | sub_40F800 | UnitStack_RemoveFromTile | High | Performs bounds checks, retracts army intel, and clears the tile occupancy entry at the stack’s row/column; rename captures that it removes the stack from its tile. |
| 35 | 35 | Function | clash95.c | sub_40F890 | UnitStack_UnlinkIfEmpty | High | Simply calls `Rules_UnlinkArmyFact` when the first slot is empty (-1 type), so the rename states it unlinks empty stacks. |
| 36 | 36 | Function | clash95.c | sub_40F8B0 | UnitStack_GetVisionRadius | Medium | Iterates slot contents and looks up `byte_5125AE` to choose the maximal sight radius, clearly reflecting a vision-radius getter for stacks. |
| 37 | 37 | Function | clash95.c | sub_40F900 | UnitStack_UpdateVision | High | Uses the owning player id and per-unit sight radius to stamp fog-of-war via `sub_40EDE0`, so the rename announces its vision refresh role. |
| 38 | 38 | Function | clash95.c | sub_40F9F0 | UnitStack_HasReadyUnits | Medium | Scans slot flag byte bit0 to see if any squad member is marked ready; new name describes this readiness check used inside `Unit_NewTurn`. |
| 39 | 39 | Function | clash95.c | sub_40FA20 | UnitStack_ClearReadyFlags | Medium | Clears bit0 of the slot flag byte for each occupied slot, which resets the per-turn readiness state; rename reflects the bit-clearing behavior. |
| 40 | 40 | Function | clash95.c | sub_40FA50 | UnitStack_SetReadyFlags | Medium | Complement to the above that sets bit0 for every populated slot, so the new name explains the flag-setting intent. |
| 41 | 41 | Recovered Struct | clash95.c | gameData + 147174 + 725 * index | UNIT_STACK(index) / UnitStackRecord | High | Introduced macros for the stack table stride plus field helpers (row, column, owner, facing, slot array, path buffer) to replace magic offsets and expose the recovered UnitStack record layout. |

## Deferred / Ambiguous
- *(none yet)*

## Notes
- Added macros for queen-related player offsets (mood, whim id, review timer) to replace anonymous pointer arithmetic and prepare for further queen renames.
- Added macros for port state offsets (row/column, supply timing, shore-refresh flags) so the docking logic no longer relies on magic numbers.
- Added UNIT_RECORD(index) to centralize access to the core unit table stride (509674 + 467 * index).
- Added TILE_INDEX(row, column) to describe world-map tile lookups instead of repeating 556374-based pointer math.
