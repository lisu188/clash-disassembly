# Rename Progress Log

## Batch 1

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| function | other | clash95.c | sub_4020A0 | Render_LoadPCXImage | high | Loads PCX graphics and optional palette data into render surfaces. |
| function | other | clash95.c | sub_407B90 | Render_RestoreLostSurfaces | high | Handles DirectDraw loss recovery and camera recentering before presenting. |
| function | other | clash95.c | sub_4190B0 | BattleLog_Disable | high | Simply clears the battle log enabled flag. |
| function | other | clash95.c | sub_4190C0 | BattleLog_Enable | high | Sets the battle log enabled flag. |
| local | other | clash95.c:Render_RestoreLostSurfaces | v1 | startScreenTileX | high | Tracks the viewport tile-x origin used during lost-surface recovery. |
| local | other | clash95.c:Render_RestoreLostSurfaces | v2 | startScreenTileY | high | Tracks the viewport tile-y origin used during lost-surface recovery. |
| local | other | clash95.c:Render_RestoreLostSurfaces | v4 | tileDeltaX | high | Represents the absolute movement in tiles between camera updates. |
| local | other | clash95.c:Render_RestoreLostSurfaces | v5 | mapWidthTiles | high | Holds the world width bound while clamping camera X. |
| local | other | clash95.c:Render_RestoreLostSurfaces | v6 | mapHeightTiles | high | Holds the world height bound while clamping camera Y. |

**Deferred / Ambiguous (Batch 1):**
- dword_526A20 (log routing flag) – semantics unclear without deeper IO tracing.
- dword_520308 (menu selection state) – interacts with multiple UI states; needs more context.

## Batch 2

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| function | other | clash95.c | sub_488514 | Process_GetCurrentId | high | Thin wrapper that directly returns GetCurrentProcessId, making semantics explicit. |
| parameter | other | clash95.c:DLX_GetSpriteForChar | a1 | spriteSetPtr | high | Clearly a sprite-set pointer used to fetch glyph entries. |
| parameter | other | clash95.c:DLX_GetSpriteForChar | a2 | spriteIndex | high | Represents the glyph index within the sprite set. |
| parameter | other | clash95.c:DLX_GetSpriteWidth | a1 | spriteSetPtr | high | Pass-through pointer to DLX_GetSpriteForChar. |
| parameter | other | clash95.c:DLX_GetSpriteWidth | a2 | spriteIndex | high | Index of the glyph whose width is returned. |
| parameter | other | clash95.c:DLX_GetSpriteHeight | a1 | spriteSetPtr | high | Pointer to the sprite set passed to DLX_GetSpriteForChar. |
| parameter | other | clash95.c:DLX_GetSpriteHeight | a2 | spriteIndex | high | Index of the glyph whose height is returned. |
| parameter | other | clash95.c:DLXSpriteSet_DrawText | a2 | glyphIndex | medium | Controls which glyph index to render; accepts -1 sentinel as seen at call sites. |
| parameter | other | clash95.c:DLXSpriteSet_DrawText | a3 | glyphBuffer | medium | Passed through to Time_Now and sub_4064A0 as glyph buffer identifier. |
| parameter | other | clash95.c:DLXSpriteSet_DrawText | a4 | samplePixels | medium | Pointer to the sampled pixel matrix compared against sprite data. |

## Batch 3

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| global | unit | clash95.c | dword_511B58 | g_SelectedUnitIndex | high | Tracks which unit slot is currently selected throughout unit UI and logic; used everywhere as the active unit index. |
| function | unit | clash95.c | sub_42D3A0 | Unit_SelectNextOwnedUnit | high | Cycles to the next unit owned by the active player, updating selection and camera state. |
| function | unit | clash95.c | sub_42D2C0 | Unit_UpdateSelectionDisplay | medium | Refreshes the render/UI elements that highlight the currently selected unit. |
| function | unit | clash95.c | sub_4287E0 | Unit_IsTileWithinRange | high | Checks whether a tile falls within the annular action range defined by the unit template. |
| function | unit | clash95.c | sub_428850 | Unit_IsTargetUnitInRange | high | Convenience wrapper that tests if another unit’s tile lies inside the caller’s action range. |
| parameter | unit | clash95.c:Unit_SelectNextOwnedUnit | a1 | uiContext | medium | Pointer passed into sub_419E60 before selection logic; represents the UI context initiating the cycle. |
| parameter | unit | clash95.c:Unit_SelectNextOwnedUnit | a2 | eventArg | medium | Forwarded to sub_419E60 alongside the UI context as the event argument. |
| parameter | unit | clash95.c:Unit_SelectNextOwnedUnit | a3 | triggerReason | medium | Passed to sub_430F80 to note why the selection change occurred (e.g., keyboard navigation). |
| parameter | unit | clash95.c:Unit_IsTileWithinRange | a1 | unitIndex | high | Index into the unit roster used to access the origin tile. |
| parameter | unit | clash95.c:Unit_IsTileWithinRange | a2 | targetTileX | high | Target tile X coordinate compared against the unit’s footprint. |
| parameter | unit | clash95.c:Unit_IsTileWithinRange | a3 | targetTileY | high | Target tile Y coordinate compared against the unit’s footprint. |
| parameter | unit | clash95.c:Unit_IsTargetUnitInRange | a1 | unitIndex | high | Source unit whose template supplies range data. |
| parameter | unit | clash95.c:Unit_IsTargetUnitInRange | a2 | targetUnitIndex | high | Destination unit index used to pull tile coordinates for the range check. |

**Deferred / Ambiguous (Batch 3):**
- dword_53205C – flag toggled during selection display updates; need deeper rendering context to name accurately.
- sub_42D4E0 – appears to toggle selection overlay visibility but ties into multiple render flags; revisit after clarifying overlay flow.

## Batch 4

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| global | castle | clash95.c | dword_526A64 | g_ActiveCastlePtr | high | Holds the active castle data block while the castle screen is open; used across castle UI actions. |
| function | castle | clash95.c | Debug_LogRenderHookChange | Castle_ShowScreen | high | Initializes and drives the castle interface, not a generic debug helper as the old name suggested. |
| function | castle | clash95.c | sub_422020 | Castle_RenderHook | high | Acts as the castle screen render hook that rebuilds the scene each frame. |
| global | castle | clash95.c | dword_526E74 | g_CastleIconSprites | high | Sprite set loaded from z_iko.s32 for castle UI icons; used throughout castle HUD drawing. |
| global | castle | clash95.c | dword_526E78 | g_CastleDecorSprites | medium | Sprite set used by the castle layout helper when composing decorative elements. |
| global | castle | clash95.c | dword_526E7C | g_CastleFontSprites | high | Font sprite atlas used whenever castle UI text is rendered. |
| parameter | castle | clash95.c:Castle_ShowScreen | a1 | castleIndex | high | Always passed as the castle index whose UI is being shown. |
| parameter | castle | clash95.c:Castle_RenderHook | a1 | renderSurface | medium | Handle to the surface receiving the castle screen rendering. |
| parameter | castle | clash95.c:Castle_RenderHook | a2 | castleDataOffset | medium | Offset into castle data used while rebuilding sprites/text each frame. |

**Deferred / Ambiguous (Batch 4):**
- dword_526E70 – appears to cache the current castle’s resource income; naming needs verification alongside economy logic.
- sub_422100 – toggles castle UI widgets but unclear if it strictly controls gate animation or availability indicators.

## Batch 5

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| global | tile | clash95.c | dword_532048 | g_MapData | high | Central map data block used for tiles, unit slots, occupancy grids, and structure metadata throughout tile and pathing routines. |
| function | tile | clash95.c | sub_425850 | Tile_UpdatePassabilityMask | high | Recomputes the per-tile passability mask based on terrain IDs whenever a battle map loads. |
| global | tile | clash95.c | byte_531890 | g_TilePassabilityMask | high | Stores the cached passability values generated by `Tile_UpdatePassabilityMask` and used by placement checks. |
| global | castle | clash95.c | dword_526A68 | g_CastleScreenSurface | high | Offscreen surface used exclusively for rendering the castle UI before presenting. |
| function | castle | clash95.c | sub_420FB0 | Castle_PromptDestroyBuilding | high | Presents a confirmation dialog for destroying a castle structure and flags the screen for refresh when accepted. |
| function | castle | clash95.c | sub_420FB0 | Castle_PromptDestroyBuilding | high | Presents the castle structure destruction confirmation and triggers building removal, forcing a UI refresh. |
| global | castle | clash95.c | dword_526E84 | g_CastleBuildingDestroyed | high | Set when a building is demolished so the castle UI can display the destruction notification. |
| global | tile | clash95.c | dword_531CB8 | g_MapIgnoreUnitOccupancy | high | Flag used to bypass unit-occupancy checks when temporarily manipulating tile data. |
| function | castle | clash95.c | sub_420CD0 | Castle_BuildSchool | high | Handles the UI event for constructing the school building and triggers the castle screen refresh. |
| function | castle | clash95.c | sub_420D50 | Castle_BuildWorkshop | high | Same pattern as BuildSchool but for the workshop upgrade. |
| function | castle | clash95.c | sub_420DD0 | Castle_BuildBarracks | high | Invokes barracks construction, clearing the corresponding build flag. |
| function | castle | clash95.c | sub_420EF0 | Castle_BuildForge | high | Executes the forge/smithy build action and updates the UI. |
| function | tile | clash95.c | sub_425970 | Tile_CheckPassability | high | Central helper that enforces unit occupancy, structure blockers, and tile mask results when determining if a tile can be used. |
| function | castle | clash95.c | sub_420E50 | Castle_BuildTemple | medium | Handles the religious building (Christian/Pagan variant) construction; naming reflects its role. |
| function | castle | clash95.c | sub_422100 | Castle_UpdateConstructionButtons | medium | Updates castle build button state flags after building availability changes. |
| function | castle | clash95.c | sub_420870 | Castle_UpdateBuildAvailability | medium | Reads castle build-state bits to populate UI availability flags before rendering. |

## Batch 6 – Queen Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 1 | 1 | Global | clash95.c | off_519010 | g_QueenMoodTexts | High | Text array controls the queen status descriptions shown in the UI panel; new name reflects content. |
| 2 | 2 | Function | clash95.c | sub_44FD90 | Queen_DrawMoodPanel | High | Function renders the queen portrait/mood text on the turn summary screen; rename clarifies intent. |
| 3 | 3 | Function | clash95.c | sub_446480 | Queen_ShowWhimDialog | High | Function displays the "QueenWhimMessage" window asking the player to fulfill a whim; name now mirrors behaviour. |
| 4 | 4 | Function | clash95.c | UI_NotifyText | Queen_ShowNotification | High | Function exclusively shows queen messages with her sprite; renamed to stress that it’s a queen-specific notification window. |

## Batch 7 – Queen Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 5 | 5 | Function | clash95.c | sub_446F40 | Queen_ShowProposalDialog | High | Presents the marriage proposal prompt ("NewQueenWindow") where the player accepts or rejects the princess envoy; new name captures the interaction. |
| 6 | 6 | Global | clash95.c | off_518010 | g_QueenProposalPrompt | High | String set used to ask the player whether to marry the princess envoy, so renamed to describe the prompt content. |

## Batch 8 – Port Wave
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

## Batch 9 – Unit Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 17 | 17 | Global | clash95.c | dword_511B54 | g_UnitSearchCursor | High | Tracks the rotating cursor used when scanning unit slots, so renaming exposes its search-role. |
| 18 | 18 | Global | clash95.c | dword_511B58 | g_SelectedUnitIndex | High | Widely used global storing the currently selected unit; descriptive name removes guesswork across the UI/logic. |
| 19 | 19 | Global | clash95.c | dword_511B5C | g_LastSelectedUnitIndex | High | Keeps the prior selection to restore focus after temporary actions; name captures that behaviour. |
| 20 | 20 | Global | clash95.c | gameData + 509674 + 467 * idx | UNIT_RECORD(idx) | High | Introduced a macro for the per-unit record base, eliminating repeated magic offsets for unit data access. |

## Batch 10 – Castle Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 21 | 21 | Global | clash95.c | dword_526A64 | g_CastleUnitRecord | High | Holds the currently highlighted castle unit record throughout the castle UI; new name shows its purpose. |
| 22 | 22 | Function | clash95.c | sub_422100 | Castle_UpdateGateToggles | Medium | Function only flips gate-related UI buttons based on castle flags, so the name describes that behaviour. |

## Batch 11 – Tile Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 23 | 23 | Global | clash95.c | gameData + 200 * row + 2 * column + 556374 | TILE_INDEX(row, column) | High | Created a macro for tile lookups so that terrain reads no longer rely on raw offsets into the world map buffer. |

## Batch 12 – Queen Wave (offset macros)
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 24 | 24 | Global | clash95.c | gameData + 1423 * dword_5202EC | PLAYER_DATA(dword_5202EC) | High | Introduced a helper for the active player’s data block instead of repeating the 1423-byte stride arithmetic. |
| 25 | 25 | Global | clash95.c | *(_BYTE *)(PLAYER_DATA(...) + 141443) | PLAYER_QUEEN_MOOD(playerIndex) | High | Named the queen mood field so comparisons no longer reference the raw offset 141443. |
| 26 | 26 | Global | clash95.c | *(_BYTE *)(PLAYER_DATA(...) + 141444) | PLAYER_QUEEN_WHIM(playerIndex) | High | This byte stores the current queen whim sprite/choice; macro makes that explicit. |
| 27 | 27 | Global | clash95.c | *(_WORD *)(PLAYER_DATA(...) + 141445) | PLAYER_QUEEN_NEXT_REVIEW(playerIndex) | High | Added a descriptive alias for the next-turn counter that schedules queen events. |
| 28 | 28 | Global | clash95.c | *(_DWORD *)(PLAYER_DATA(...) + 140051) | PLAYER_HAS_HUMAN_CONTROLLER(playerIndex) | Medium | New macro explains that the flag at offset 140051 reflects whether a human is controlling the player. |
| 29 | 29 | Global | clash95.c | *(_WORD *)(gameData + 140022) | GAME_TURN_COUNTER | High | The global turn counter offset now has a name, avoiding raw reads of address 140022. |

## Batch 13 – Unit Stack Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 30 | 30 | Function | clash95.c | sub_40F3C0 | UnitStack_IsIndexOnMap | High | Function scans the tile occupancy buffer at `gameData + 556374` to see whether the given stack id is still on the board; rename clarifies it’s a stack-level map membership test. |
| 31 | 31 | Function | clash95.c | sub_40F440 | UnitSlot_InitFromType | High | Routine seeds the 31-byte slot entry with type id, owner, morale, and veterancy from the per-unit tables, so it clearly seeds an individual unit slot. |
| 32 | 32 | Function | clash95.c | sub_40F4D0 | UnitStack_ResetRecord | High | Wrapper around `UnitSlot_InitFromType` that clears the remaining slots, path buffer, and owner byte for a stack record; rename documents that it resets the entire stack entry. |
| 33 | 33 | Function | clash95.c | sub_40F7C0 | UnitStack_KillByIndex | High | Thin wrapper that converts a stack index to its record pointer and forwards to `Unit_Kill`, so the rename documents that it kills stacks by index. |
| 34 | 34 | Function | clash95.c | sub_40F800 | UnitStack_RemoveFromTile | High | Validates row/column bounds, retracts army intel, zeros the tile entry, and updates fog-of-war, which is exactly the logic to remove a stack from its occupied tile. |
| 35 | 35 | Function | clash95.c | sub_40F890 | UnitStack_UnlinkIfEmpty | High | Checks whether the first slot’s unit type is -1 and, if so, calls `Rules_UnlinkArmyFact`; it only unlinks empty stacks. |
| 36 | 36 | Function | clash95.c | sub_40F8B0 | UnitStack_GetVisionRadius | Medium | Iterates slot contents and looks up `byte_5125AE` to choose the maximal sight radius, clearly reflecting a vision-radius getter for stacks. |
| 37 | 37 | Function | clash95.c | sub_40F900 | UnitStack_UpdateVision | High | Uses the owning player id, stack tile, and `UnitStack_GetVisionRadius` to stamp fog-of-war via `sub_40EDE0`, so the rename reflects its vision-update role. |
| 38 | 38 | Function | clash95.c | sub_40F9F0 | UnitStack_HasReadyUnits | Medium | Scans up to 10 slots looking for bit0 set in the slot flag byte, returning 1 only if at least one squad member is marked ready — a readiness probe used in `Unit_NewTurn`. |
| 39 | 39 | Function | clash95.c | sub_40FA20 | UnitStack_ClearReadyFlags | Medium | Iterates every occupied slot and clears bit0 of the flag byte, which resets the per-turn “ready” state for the entire stack. |
| 40 | 40 | Function | clash95.c | sub_40FA50 | UnitStack_SetReadyFlags | Medium | Complement to the above that sets bit0 for each slot once the UI or turn logic re-enables the stack. |
| 41 | 41 | Recovered Struct | clash95.c | gameData + 147174 + 725 * index | UNIT_STACK(index) / UnitStackRecord | High | Introduced macros for the stack table stride plus field helpers (row, column, owner, facing, slot array, path buffer) to replace magic offsets and expose the recovered UnitStack record layout. |

## Batch 14 – Army Fact Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 42 | 42 | Function | clash95.c | sub_40F6E0 | UnitStack_LinkArmyFact | High | Called immediately after spawning or moving stacks so their tile occupancy is synchronized with the rules/AI fact system via `Rules_CreateArmyFact`. |
| 43 | 43 | Function | clash95.c | sub_4521D0 | Rules_CreateArmyFact | High | Formats the "ODDZIAL" fact string, asserts it in the rules database, caches the returned handle at offset +721 within the stack, and then chains into `Rules_LinkArmyFact`, so the new name reflects that behavior. |

## Batch 15 – Unit Stat Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 44 | 44 | Function | clash95.c | sub_411120 | UnitStats_CalcMeleeAttack | High | Reads the melee base table (`byte_51257E`), adds stance and veterancy bonuses, and scales by morale, matching the effective melee strength used in combat and UI. |
| 45 | 45 | Function | clash95.c | sub_4111C0 | UnitStats_CalcRangedAttack | High | Uses the ranged base table (`byte_51257F`), applies missile-cover penalties and stance bonuses, then scales by morale, so it clearly computes live ranged attack power. |
| 46 | 46 | Function | clash95.c | sub_411240 | UnitStats_GetRangedIconIndex | Medium | Same inputs as the ranged attack calculation but without morale, providing the UI-ready index for ranged power icons analogous to `UI_IconIndexFromStats`. |
| 47 | 47 | Function | clash95.c | sub_411280 | UnitStats_CalcDamagePerHit | High | Combines the damage scalar table (`byte_512581`) with veterancy and morale to determine actual hit damage. |
| 48 | 48 | Function | clash95.c | sub_4112C0 | UnitStats_GetBaseDamage | High | Returns the base damage scalar plus veterancy, i.e., the UI-facing damage stat before morale modifiers. |
| 49 | 49 | Function | clash95.c | sub_4112F0 | UnitStats_CalcSiegeAttack | Medium | Mirrors the melee/ranged formulas using the structure-damage table (`byte_512584`), so it computes vs-building attack power. |

## Batch 16 – Unit Naming Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 50 | 50 | Global | clash95.c | off_51256C | g_UnitSpriteFolders | High | This pointer array feeds every unit sprite load by appending folder names like `peon` to `units_go\` paths; renaming it exposes that it stores per-unit sprite folders. |
| 51 | 51 | Helper | clash95.c | (implicit type 0) | UNIT_TYPE_PEASANT | High | The first sprite folder entry is `"peon"` and scripting hooks `IloscChlopow` / `WyprowadzChlopow` operate on that archetype, so naming type id 0 as `UNIT_TYPE_PEASANT` documents the unit taxonomy. |

## Batch 17 – Unit Morale Wave
| # | Cumulative | Kind | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|------|----------|----------|------------|-----------|
| 52 | 52 | Function | clash95.c | sub_4114B0 | Unit_CompactSquad | High | Core helper that removes `type == -1` slots by shifting subsequent entries and relinking army facts, used whenever units desert or are killed. |
| 53 | 53 | Function | clash95.c | sub_411560 | UnitSlots_RemoveGaps | Medium | Secondary slot-compaction helper invoked with an explicit slot count after battle resolution to close gaps without touching the entire squad record. |
| 54 | 54 | Function | clash95.c | sub_4115E0 | Unit_CheckLowMorale | High | Implements the low-morale deserter check: rolls RNG, logs via `Unit_CheckLowMorale` strings, shows the disband message, and compacts the squad when troops flee. |

---

## Addendum: branch `refactor-function-renames` (March 2026, merged 2026-07-12)

> Historical log recovered during the merge of `refactor-function-renames`. The
> function names and several global names below are the branch's original
> proposals; many were later superseded by evidence-based names on main
> (e.g. Battle_RunLoop -> UnitBattle_RunTurnLoop, Tile_CheckPassability ->
> UnitBattle_GetTileMoveCostOrZero, Castle_BuildTemple/Forge ->
> Castle_BuildHospitalWithAnimation/Castle_BuildSmithsWithAnimation,
> dword_532060/dword_532074 -> g_UnitBattleChargeModeActive/StartTick,
> dword_532068 -> g_UnitBattleActionLoopExitRequested). The globals actually
> ported to main in that merge were: g_MapData, g_BattleLoopExitCode,
> g_AttackerStartsOnLeft, g_DefenderStartsOnLeft, g_BattleHudSprites,
> g_MapIgnoreUnitOccupancy, g_TilePassabilityMask,
> g_ActiveCastleOwnerIsChristian.

### Batch 5 tail (branch-only rows)

| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| global | castle | clash95.c | dword_526E80 | g_CastleScreenShouldClose | high | Boolean flag that forces the castle screen loop to exit (set by close events and destruction prompt). |
| parameter | tile | clash95.c:Tile_CheckPassability | a1 | unitIndex | high | Explicitly denotes the unit index used when evaluating tile occupancy rules. |
| parameter | tile | clash95.c:Tile_CheckPassability | a2 | tileX | high | Makes clear this argument is the map X coordinate. |
| parameter | tile | clash95.c:Tile_CheckPassability | a3 | tileY | high | Makes clear this argument is the map Y coordinate. |
| function | castle | clash95.c | sub_42C4E0 | Battle_BothPlayersActive | high | Checks the map grid to confirm both players still have at least one unit alive during castle battles. |
| function | castle | clash95.c | sub_42C4C0 | Battle_HandleNewTurn | medium | Logs the "battle new turn" event and forwards to the routine that rebuilds state at the start of each round. |
| global | unit | clash95.c | dword_53205C | g_SelectionHighlightActive | medium | Tracks whether the selected unit's highlight overlay is currently shown during blinking animations. |
| function | unit | clash95.c | sub_42D4E0 | Unit_ToggleSelectionBlink | medium | Toggles the blinking highlight state for the currently selected unit. |
| global | castle | clash95.c | dword_513E22 | g_CastleHasBuildOptions | medium | Tracks whether any build buttons remain available after refreshing castle construction states. |
| global | castle | clash95.c | dword_513FC2 | g_CastleBuildCategoryOpen | medium | Array storing per-category availability bits used while scanning castle construction options. |
| global | unit | clash95.c | dword_5202EC | g_CurrentPlayerIndex | high | Used across combat/castle/map routines as the active player index, so renaming clarifies its role everywhere. |

### Batch 6 (branch cumulative: 100)


| Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
| --- | --- | --- | --- | --- | --- | --- |
| global | unit | clash95.c | dword_532060 | g_SelectionBlinkActive | high | Flag toggled while the selected unit’s highlight is blinking during combat targeting. |
| global | unit | clash95.c | dword_532074 | g_SelectionBlinkStartTime | high | Timestamp used to animate the blinking intensity for the selected unit. |
| global | castle | clash95.c | dword_526E70 | g_ActiveCastleOwnerIsChristian | high | Cached owner religion flag read from the player block when opening the castle UI. |
| global | unit | clash95.c | dword_532064 | g_BattleLoopExitCode | medium | Stores the exit code returned by battle loop dialogs and win/lose checks. |
| global | unit | clash95.c | dword_532068 | g_BattleDialogDismissed | medium | Set when modal battle dialogs have been acknowledged, allowing the loop to continue. |
| global | unit | clash95.c | dword_514E28 | g_BattleHintIndex | medium | Remembers which battle status hint is currently displayed to prevent redundant popups. |
| global | unit | clash95.c | byte_514C89 | g_BattleHintFlags | medium | Bitfield controlling whether battle hints may be shown again. |
| global | unit | clash95.c | dword_53204C | g_BattleHudSprites | high | Holds the sprite set used to draw battle HUD elements and overlays. |
| global | unit | clash95.c | dword_53206C | g_AttackerStartsOnLeft | medium | Indicates whether the attacking army should be positioned on the left side of the battle map. |
| global | unit | clash95.c | dword_532070 | g_DefenderStartsOnLeft | medium | Complementary flag indicating the defender’s starting side on the battle grid. |
| global | castle | clash95.c | dword_513FEA | g_CastleTempleAvailable | high | Tracks whether the temple/faith building is still constructable. |
| global | castle | clash95.c | dword_514012 | g_CastleBarracksAvailable | high | Tracks whether the barracks building can still be constructed. |
| global | castle | clash95.c | dword_51403A | g_CastleWorkshopAvailable | high | Availability flag for the workshop upgrade. |
| global | castle | clash95.c | dword_514062 | g_CastleForgeAvailable | high | Indicates whether the forge/smithy is still buildable. |
| function | unit | clash95.c | sub_42C180 | Battle_LogAllUnits | high | Emits log entries for every unit slot by iterating the battle roster. |
| function | unit | clash95.c | sub_42C130 | Battle_LogUnitEntry | high | Logs a single unit entry via the off_512568 descriptor table. |
| function | unit | clash95.c | sub_42C0F0 | Battle_IsTileInViewport | high | Checks whether a tile coordinate lies inside the 7x7 combat viewport. |
| function | unit | clash95.c | sub_42E3C0 | Battle_RunLoop | medium | Main per-frame battle loop that processes input/events until an exit code is set. |
| function | unit | clash95.c | sub_4327B0 | Battle_PlaceUnit | high | Handles placing a unit record onto the battle grid and updates selection indices. |
| function | unit | clash95.c | sub_432770 | Battle_ResetUnitColors | medium | Resets each unit’s highlight color from the default palette at the start of combat. |
| function | unit | clash95.c | sub_42D6F0 | Battle_DismissDialog | medium | Marks modal battle dialogs as closed and restores the render state. |
| function | unit | clash95.c | sub_4321D0 | Battle_ClearPlacementPreview | medium | Removes the currently previewed unit placement and restores the previous selection tile. |
| parameter | unit | clash95.c:Battle_IsTileInViewport | a1 | tileX | high | Makes the first coordinate parameter explicit as the map X coordinate. |
| parameter | unit | clash95.c:Battle_IsTileInViewport | a2 | tileY | high | Clarifies the second coordinate as the map Y value. |
| parameter | unit | clash95.c:Battle_LogUnitEntry | a1 | unitEntry | high | Shows the pointer is a unit roster entry. |
| parameter | unit | clash95.c:Battle_LogUnitEntry | a2 | logHandle | medium | Indicates the DWORD argument is the active log handle. |
| parameter | unit | clash95.c:Battle_LogAllUnits | a1 | logContext | medium | Makes the logging context parameter explicit. |
| parameter | unit | clash95.c:Battle_LogAllUnits | a2 | logCategory | medium | Clarifies the category byte forwarded to the logger. |
| parameter | unit | clash95.c:Battle_LogAllUnits | a3 | logHandle | medium | Documents the DWORD passed to `Battle_LogUnitEntry`. |
| parameter | unit | clash95.c:Battle_PlaceUnit | a1 | unitData | high | Highlights that the first argument is the unit record being placed. |
| parameter | unit | clash95.c:Battle_PlaceUnit | a2 | tileX | high | Explicitly names the destination X tile. |
| parameter | unit | clash95.c:Battle_PlaceUnit | a3 | facing | medium | Captures that the byte controls the unit’s battlefield facing. |
| parameter | unit | clash95.c:Battle_PlaceUnit | a4 | tileY | high | Explicitly names the destination Y tile. |

### Final Summary (branch)

- **Total renames completed:** 100
- **Target met:** yes (100 high-confidence renames logged)
- **Remaining ambiguous identifiers:** `dword_526A20` (logging router), `dword_514BEA` (selection blink helper) still lack clear semantics.
- **Patterns noticed:** battle-related helpers often log with descriptive string constants that can be promoted to stable names; castle build availability uses bitmasks in `g_ActiveCastlePtr + 416` where each bit maps cleanly to a specific building; tile/battle data lives in `g_MapData` with fixed 31-byte unit slots.
- **Suggested next targets:** clarify remaining battle dialog globals (`dword_514E48`, `dword_514E4C`) and castle economy fields (e.g., income arrays around `gameData + 140063`) once more context is recovered.
