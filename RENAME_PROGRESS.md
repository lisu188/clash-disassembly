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
