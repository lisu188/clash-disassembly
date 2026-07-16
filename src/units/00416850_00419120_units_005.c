/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (00416850) --------------------------------------------------------
int  WorldMap_DrawMapTile(unsigned __int16 screenX, unsigned __int16 screenY, unsigned __int16 *tilePtr)
{
  int tileRow; // edi
  signed int tileColumn; // esi
  int overlayGlyph; // eax
  int overlaySprite; // eax
  int missionIndex; // ebx
  int trapMarkSprite; // eax
  int unitTileFgGlyph; // eax
  int unitTileFgSprite; // eax
  int leftMoveOffsetY; // ebx
  __int16 leftNeighborStack; // ax
  int v14; // edx
  int v15; // ebp
  int v16; // ecx
  int v17; // ebp
  __int16 upNeighborStack; // ax
  int v19; // edx
  int upMoveOffsetY; // ecx
  __int16 rightNeighborStack; // ax
  int v22; // edx
  int rightMoveOffsetY; // ebx
  int v24; // ebp
  int v25; // ebp
  int v26; // ecx
  __int16 downNeighborStack; // ax
  int v28; // edx
  int downMoveOffsetY; // ecx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  signed int mapWidthTiles; // eax
  int v38; // eax
  int tileOccupant; // eax
  int buildingIndex; // ebx
  int buildingByteOffset; // edx
  int buildingBaseAddr; // edx
  int v43; // eax
  DWORD buildingKind; // ebp
  signed int damageStage; // edx
  unsigned __int8 *buildingBasePtr; // eax
  int buildingSprite; // eax
  DWORD v48; // ebp
  int unitStackBase; // ecx
  int pathStepCount; // edx
  _DWORD *pathBuffer; // ecx
  int markerSprite; // eax
  int activeMission; // edx
  int v54; // edx
  int fogSprite; // eax
  int v56; // ecx
  char textStyleFlag; // dl
  int bgGlyph; // eax
  int bgSprite; // eax
  int fgSprite; // eax
  int theme2BgGlyph; // eax
  int SpriteForChar; // eax
  int theme2FgGlyph; // eax
  int theme2FgSprite; // eax
  unsigned __int16 leftNeighborTile; // ax
  int edgeSpriteLeft; // eax
  unsigned __int16 rightNeighborTile; // ax
  int edgeSpriteRight; // eax
  unsigned __int16 upNeighborTile; // ax
  int edgeSpriteUp; // eax
  __int16 downNeighborTile; // ax
  int edgeSpriteDown; // eax
  int neighborOccupant; // eax
  unsigned __int8 *neighborBuilding; // eax
  int neighborBuildingState; // edx
  int neighborEdgeSprite; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int flagSprite; // eax
  int deferredFgGlyph; // eax
  int deferredFgSprite; // eax
  unsigned __int16 deferredBgGlyph; // dx
  int deferredBgSprite; // eax
  int pathDirCode; // ebx
  int pathScanIndex; // eax
  _DWORD *pathScanCursor; // edx
  int waypointColumn; // ecx
  int lastPathIndex; // edx
  int pathStepSprite; // eax
  int v92; // ecx
  signed int fogOverlayClass; // [esp+C4h] [ebp-94h]
  int screenBottom; // [esp+C8h] [ebp-90h]
  int screenRight; // [esp+CCh] [ebp-8Ch]
  int screenTop; // [esp+D0h] [ebp-88h]
  int screenLeft; // [esp+D4h] [ebp-84h]
  int drewOverlaySprite; // [esp+D8h] [ebp-80h]
  int stackIndex; // [esp+DCh] [ebp-7Ch]
  int moveAnimOffsetY; // [esp+E4h] [ebp-74h]
  int buildingRecord; // [esp+F0h] [ebp-68h]
  int buildingDrawPhase; // [esp+F4h] [ebp-64h]
  _DWORD *pathBufferCopy; // [esp+100h] [ebp-58h]
  int waypoint; // [esp+104h] [ebp-54h]
  int originWaypoint; // [esp+108h] [ebp-50h]
  int prevWaypoint; // [esp+10Ch] [ebp-4Ch]
  int v108; // [esp+124h] [ebp-34h]
  __int16 leftStackIndex; // [esp+130h] [ebp-28h]
  __int16 rightStackIndex; // [esp+13Ch] [ebp-1Ch]
  __int16 upStackIndex; // [esp+140h] [ebp-18h]
  __int16 downStackIndex; // [esp+144h] [ebp-14h]
  int building_flag_variant;
  int building_flag_x;
  static const unsigned char building_flag_x_offsets[10] = { 0x38, 0x3C, 0x3E, 0x41, 0x41, 0x21, 0x21, 0x21, 0x23, 0x20 };

  tileRow = ((int)tilePtr - gameData) / 14 / 100;
  tileColumn = ((int)tilePtr - gameData) / 14 % 100;
  screenBottom = (unsigned __int16)(screenY + 63);
  screenRight = (unsigned __int16)(screenX + 63);
  screenTop = screenY;
  screenLeft = screenX;
  if ( MiniMap_IsSpanWithinViewportBounds(screenX, screenY + 63) )
    goto LABEL_2;
  fogOverlayClass = Map_ClassifyFogOfWarOverlayForPlayer(tileRow, tileColumn, VIEWED_PLAYER_INDEX);
  if ( !fogOverlayClass )
  {
    Compat_RenderDeviceFillSolidRect(screenLeft, screenTop, screenRight, screenBottom, 1u);
    goto LABEL_2;
  }
  if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) == 2 )
  {
    theme2BgGlyph = *tilePtr;
    if ( theme2BgGlyph != 0xFFFF )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[theme2BgGlyph]);
      Compat_RenderDeviceDrawMenuSprite(screenLeft, screenTop, SpriteForChar, 0);
    }
    theme2FgGlyph = tilePtr[1];
    if ( theme2FgGlyph != 0xFFFF )
    {
      theme2FgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[theme2FgGlyph]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, theme2FgSprite, 1);
    }
  }
  else
  {
    if ( *tilePtr != 0xFFFF && (*tilePtr < 0xCFu || *tilePtr > 0xD2u) )
    {
      HIWORD(bgGlyph) = 0;
      if ( *tilePtr != 187 )
      {
        LOWORD(bgGlyph) = *tilePtr;
        bgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[bgGlyph]);
        Compat_RenderDeviceDrawMenuSprite(screenX, screenY, bgSprite, 0);
      }
    }
    if ( tilePtr[1] != 0xFFFF && (tilePtr[1] < 0xD3u || tilePtr[1] > 0xD7u) )
    {
      fgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[tilePtr[1]]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, fgSprite, 1);
    }
  }
  overlayGlyph = tilePtr[2];
  if ( overlayGlyph != 0xFFFF )
  {
    overlaySprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[overlayGlyph]);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, overlaySprite, 1);
  }
  missionIndex = ACTIVE_MISSION_INDEX;
  if ( missionIndex == 7 )
  {
    WorldMap_DrawMission07TreasureMarker(tileRow, tileColumn);
  }
  else if ( missionIndex == 17 )
  {
    WorldMap_DrawMission17TreasureMarker(tileRow, tileColumn);
  }
  if ( tilePtr[2] < 0x362u || tilePtr[2] > 0x36Cu )
  {
    if ( tileColumn <= 0 )
      leftNeighborTile = -1;
    else
      leftNeighborTile = *(tilePtr - 5);
    if ( leftNeighborTile >= 0x364u && leftNeighborTile <= 0x369u || leftNeighborTile == 866 )
    {
      edgeSpriteLeft = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 863);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, edgeSpriteLeft, 1);
    }
    if ( tileColumn >= 99 )
      rightNeighborTile = -1;
    else
      rightNeighborTile = tilePtr[9];
    if ( rightNeighborTile >= 0x367u && rightNeighborTile <= 0x36Cu || rightNeighborTile == 866 )
    {
      edgeSpriteRight = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 862);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, edgeSpriteRight, 1);
    }
    if ( tileRow <= 0 )
      upNeighborTile = -1;
    else
      upNeighborTile = *(tilePtr - 698);
    if ( upNeighborTile >= 0x363u && upNeighborTile <= 0x365u || upNeighborTile == 871 || upNeighborTile == 872 || upNeighborTile == 874 || upNeighborTile == 875 )
    {
      edgeSpriteUp = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 864);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, edgeSpriteUp, 1);
    }
    if ( tileRow >= 99 )
      downNeighborTile = -1;
    else
      downNeighborTile = tilePtr[702];
    if ( downNeighborTile == 873 || downNeighborTile == 875 || downNeighborTile == 876 || downNeighborTile == 867 || downNeighborTile == 869 || downNeighborTile == 870 || downNeighborTile == 872 )
    {
      edgeSpriteDown = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 865);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, edgeSpriteDown, 1);
    }
    if ( tileColumn >= 2 )
    {
      neighborOccupant = *(unsigned __int16 *)(2 * tileColumn + 200 * tileRow + gameData + 556370);
      if ( (unsigned __int16)neighborOccupant >= 0x8000u && *(unsigned __int16 *)(2 * tileColumn + 200 * tileRow + gameData + 556370) != 0xFFFF )
      {
        neighborBuilding = (unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * (neighborOccupant - TILE_OCCUPANT_BUILDING_INDEX_BASE));
        neighborBuildingState = (char)neighborBuilding[4];
        if ( (neighborBuildingState == 2 || neighborBuildingState == 1) && *neighborBuilding == tileRow && neighborBuilding[1] == tileColumn - 2 && !*((_WORD *)neighborBuilding + 8) )
        {
          neighborEdgeSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 863);
          Compat_RenderDeviceDrawMenuSprite(screenX, screenY, neighborEdgeSprite, 1);
        }
      }
    }
  }
  if ( ((1 << g_CurrentPlayerIndex) & *(unsigned __int8 *)(tileColumn + gameData + TILE_TRAP_OWNER_MASK_ROW_STRIDE * tileRow + TILE_TRAP_OWNER_MASK_OFFSET)) == 1 << g_CurrentPlayerIndex )
  {
    trapMarkSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, 6);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, trapMarkSprite, 1);
  }
  drewOverlaySprite = 0;
  stackIndex = *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn));
  moveAnimOffsetY = 0;
  if ( g_ActiveUnitMoveTileIndex == stackIndex )
    moveAnimOffsetY = g_UnitMoveAnimOffsetY;
  if ( *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn)) <= 0x7FFFu
    && (g_UnitTypeFlags[22 * *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180)] & 1) != 0 )
  {
    drewOverlaySprite = 1;
    unitTileFgGlyph = tilePtr[1];
    if ( unitTileFgGlyph != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      unitTileFgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[unitTileFgGlyph]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, unitTileFgSprite, 1);
    }
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || *tilePtr == 187) )
    {
      v77 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[*tilePtr]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v77, 1);
    }
    WorldMap_DrawUnitStackWithOverlays(stackIndex, screenX, screenY, moveAnimOffsetY, tilePtr);
  }
  else
  {
    WorldMap_DrawUnitStackWithOverlays(stackIndex, screenX, screenY, moveAnimOffsetY, tilePtr);
    v77 = tilePtr[1];
    if ( v77 != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      v78 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v77]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v78, 1);
    }
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || *tilePtr == 187) )
    {
      v79 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[*tilePtr]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v79, 1);
    }
  }
  leftMoveOffsetY = 0;
  if ( tileColumn > 0 )
  {
    leftNeighborStack = *(_WORD *)(200 * tileRow + gameData + 2 * tileColumn + 556372);
    leftStackIndex = leftNeighborStack;
    if ( leftNeighborStack >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(leftNeighborStack) )
      {
        if ( v14 == g_ActiveUnitMoveTileIndex )
          leftMoveOffsetY = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(leftStackIndex, screenX, screenY, leftMoveOffsetY - 64, (unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * tileRow + gameData + TILE_TERRAIN_RECORD_STRIDE * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn > 0 && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v15 = *(__int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556372);
    if ( v15 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v15, screenX, screenY, g_UnitMoveAnimOffsetY - 64, (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * v16 + TILE_TERRAIN_RECORD_STRIDE * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 && tileRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) && g_ActiveUnitMoveTileIndex != -1 )
  {
    v17 = *(__int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556376);
    if ( v17 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v17, screenX, screenY, g_UnitMoveAnimOffsetY + 64, (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (tileRow + 1) + TILE_TERRAIN_RECORD_STRIDE * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileRow > 0 )
  {
    upNeighborStack = *(_WORD *)(TILE_INDEX((tileRow - 1), tileColumn));
    upStackIndex = upNeighborStack;
    if ( upNeighborStack >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(upNeighborStack) )
      {
        upMoveOffsetY = 0;
        if ( v19 == g_ActiveUnitMoveTileIndex )
          upMoveOffsetY = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(upStackIndex, screenX, screenY, upMoveOffsetY, (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (tileRow - 1) + TILE_TERRAIN_RECORD_STRIDE * tileColumn));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 )
  {
    rightNeighborStack = *(_WORD *)(200 * tileRow + gameData + 2 * tileColumn + 556376);
    rightStackIndex = rightNeighborStack;
    if ( rightNeighborStack >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(rightNeighborStack) )
      {
        rightMoveOffsetY = 0;
        if ( v22 == g_ActiveUnitMoveTileIndex )
          rightMoveOffsetY = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(rightStackIndex, screenX, screenY, rightMoveOffsetY + 64, (unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * tileRow + gameData + TILE_TERRAIN_RECORD_STRIDE * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v24 = *(__int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556376);
    if ( v24 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v24, screenX, screenY, g_UnitMoveAnimOffsetY + 64, (unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * (tileRow - 1) + gameData + TILE_TERRAIN_RECORD_STRIDE * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn > 0 && tileRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v25 = *(__int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556372);
    if ( v25 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v25, screenX, screenY, g_UnitMoveAnimOffsetY - 64, (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * v26 + TILE_TERRAIN_RECORD_STRIDE * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 )
  {
    downNeighborStack = *(_WORD *)(TILE_ROW_STRIDE * (tileRow + 1) + gameData + 2 * tileColumn + TILE_MAP_OFFSET);
    downStackIndex = downNeighborStack;
    if ( downNeighborStack >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(downNeighborStack) )
      {
        downMoveOffsetY = 0;
        if ( v28 == g_ActiveUnitMoveTileIndex )
          downMoveOffsetY = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(downStackIndex, screenX, screenY, downMoveOffsetY, (unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * (tileRow + 1) + gameData + TILE_TERRAIN_RECORD_STRIDE * tileColumn));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( g_ActiveUnitMoveTileIndex != -1 )
  {
    if ( tileColumn > 0 )
    {
      v30 = *(unsigned __int16 *)(200 * tileRow + gameData + 2 * tileColumn + 556372);
      if ( v30 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && v30 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v30, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    if ( tileColumn < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 )
    {
      v31 = *(unsigned __int16 *)(200 * tileRow + gameData + 2 * tileColumn + 556376);
      if ( v31 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && v31 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v31, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
    if ( tileRow > 0 )
    {
      v32 = *(unsigned __int16 *)(TILE_INDEX((tileRow - 1), tileColumn));
      if ( v32 != 0xFFFF && g_UnitMoveAnimOffsetX > 0 && v32 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v32, screenX, screenY, g_UnitMoveAnimOffsetY, tilePtr);
    }
    if ( tileRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 )
    {
      v33 = *(unsigned __int16 *)(TILE_ROW_STRIDE * (tileRow + 1) + gameData + 2 * tileColumn + TILE_MAP_OFFSET);
      if ( v33 != 0xFFFF && g_UnitMoveAnimOffsetX < 0 && v33 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v33, screenX, screenY, g_UnitMoveAnimOffsetY, tilePtr);
    }
    if ( tileRow > 0 && tileColumn > 0 )
    {
      v34 = *(unsigned __int16 *)(gameData + 200 * (tileRow - 1) + 2 * tileColumn + 556372);
      if ( v34 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX > 0 && v34 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v34, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    if ( tileRow > 0 && tileColumn < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      v35 = *(unsigned __int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556376);
      if ( v35 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX > 0 && v35 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v35, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
    if ( tileColumn > 0 && tileRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
    {
      v36 = *(unsigned __int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556372);
      if ( v36 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX < 0 && v36 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v36, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    mapWidthTiles = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
    if ( tileColumn < mapWidthTiles && tileRow < mapWidthTiles )
    {
      v38 = *(unsigned __int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556376);
      if ( v38 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX < 0 && v38 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v38, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
  }
  tileOccupant = *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn));
  if ( (unsigned __int16)tileOccupant >= 0x8000u && *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn)) != 0xFFFF )
  {
    buildingIndex = tileOccupant - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    buildingByteOffset = BUILDING_RECORD_SIZE * (tileOccupant - TILE_OCCUPANT_BUILDING_INDEX_BASE);
    buildingRecord = buildingByteOffset + gameData + BUILDING_TABLE_OFFSET;
    buildingBaseAddr = gameData + buildingByteOffset;
    v43 = *(__int16 *)(buildingRecord + 16);
    buildingKind = *(char *)(buildingBaseAddr + 509678);
    if ( v43 != -1 )
      v43 = 3 * ((unsigned __int16)g_BuildingTypeMaxHitPoints[buildingKind] - *(__int16 *)(buildingBaseAddr + 509690)) / (unsigned __int16)g_BuildingTypeMaxHitPoints[buildingKind];
    damageStage = v43;
    buildingBasePtr = (unsigned __int8 *)(BUILDING_RECORD_SIZE * buildingIndex + gameData);
    buildingDrawPhase = tileRow + 2 * (tileColumn - buildingBasePtr[509675]) - buildingBasePtr[509674];
    buildingSprite = BuildingSpriteCache_GetOrLoadEntry(buildingKind, buildingBasePtr[509676], damageStage, buildingBasePtr[509677], buildingDrawPhase);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, buildingSprite, 1);
    if ( *(__int16 *)(buildingRecord + 16) == -1 && *(_BYTE *)(buildingRecord + 4) )
    {
      WorldMap_DrawUnitAttentionFlashGlow(screenX, screenY, buildingDrawPhase);
    }
    else if ( !*(_WORD *)(buildingRecord + 16) )
    {
      if ( *(_BYTE *)(buildingRecord + 4) )
        v79 = 0;
      else
        v79 = 5;
      v108 = (unsigned __int8)g_BuildingFlagYOffsets[2 * *(unsigned __int8 *)(buildingRecord + 3) + 2 * v79]
           + ((*(unsigned __int8 *)(buildingRecord + 1) - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6)
           + 16;
      if ( *(_BYTE *)(buildingRecord + 4) )
        building_flag_variant = 0;
      else
        building_flag_variant = 80;
      building_flag_x = building_flag_x_offsets[*(unsigned __int8 *)(buildingRecord + 3) + (building_flag_variant ? 5 : 0)]
                      + ((*(unsigned __int8 *)buildingRecord - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
                      + 32;
      flagSprite = DLX_GetSpriteForChar(g_FlagSpriteSet, 16 * *(unsigned __int8 *)(buildingRecord + 2) + building_flag_variant + g_MapFlagAnimationFrame);
      Compat_RenderDeviceDrawMenuSprite(building_flag_x, v108, flagSprite, 1);
    }
  }
  if ( !drewOverlaySprite && *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) != 2 )
  {
    deferredFgGlyph = tilePtr[1];
    if ( deferredFgGlyph != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      deferredFgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[deferredFgGlyph]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, deferredFgSprite, 1);
    }
    deferredBgGlyph = *tilePtr;
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || deferredBgGlyph == 187) )
    {
      deferredBgSprite = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[deferredBgGlyph]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, deferredBgSprite, 1);
    }
  }
  v48 = g_ActiveUnitMoveTileIndex;
  if ( g_ActiveUnitMoveTileIndex == -1 && g_SelectedUnitIndex != -1 )
  {
    unitStackBase = UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET;
    pathStepCount = *(_DWORD *)(unitStackBase + 316);
    pathBuffer = (_DWORD *)(unitStackBase + 316);
    if ( pathStepCount )
    {
      if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      {
        pathDirCode = -1;
        pathScanIndex = *pathBuffer - 1;
        pathBufferCopy = pathBuffer;
        if ( pathScanIndex >= 0 )
        {
          v48 = 4 * pathScanIndex;
          pathScanCursor = pathBuffer;
          do
          {
            waypoint = pathScanCursor[1];
            if ( (unsigned __int8)waypoint == tileRow )
            {
              waypointColumn = tileRow ^ (unsigned __int8)waypoint;
              LOBYTE(waypointColumn) = BYTE1(pathScanCursor[1]);
              if ( waypointColumn == tileColumn )
                break;
            }
            --pathScanIndex;
            ++pathScanCursor;
          }
          while ( pathScanIndex >= 0 );
        }
        lastPathIndex = *pathBufferCopy - 1;
        if ( pathScanIndex == lastPathIndex )
        {
          pathDirCode = 64;
        }
        else
        {
          if ( pathScanIndex >= 0 )
          {
            waypoint = pathBufferCopy[lastPathIndex - pathScanIndex + 1];
            prevWaypoint = pathBufferCopy[lastPathIndex - (pathScanIndex + 1) + 1];
            if ( pathScanIndex <= 0 )
            {
              LOBYTE(originWaypoint) = *(_BYTE *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET);
              BYTE1(originWaypoint) = *(_BYTE *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176);
            }
            else
            {
              originWaypoint = pathBufferCopy[*pathBufferCopy - pathScanIndex + 1];
            }
            v48 = 8 * Facing_DirectionFromDelta8((unsigned __int8)originWaypoint - (unsigned __int8)waypoint, BYTE1(originWaypoint) - BYTE1(waypoint));
            pathDirCode = Facing_DirectionFromDelta8((unsigned __int8)prevWaypoint - (unsigned __int8)waypoint, BYTE1(prevWaypoint) - v92) + v48;
          }
          if ( pathDirCode == -1 )
            goto LABEL_133;
        }
        if ( HIWORD(waypoint) > UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
          pathDirCode += 65;
        pathStepSprite = DLX_GetSpriteForChar(g_MovePathStepSpriteSet, pathDirCode);
        Compat_RenderDeviceDrawMenuSprite(screenX, screenY, pathStepSprite, 1);
        if ( !drewOverlaySprite )
          WorldMap_DrawUnitStackOverlayGlyph(screenX, screenY, tilePtr);
      }
    }
  }
LABEL_133:
  if ( stackIndex == g_SelectedUnitIndex && g_ActiveUnitMoveTileIndex == -1 && PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
  {
    markerSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, *(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET) == 1);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, markerSprite, 1);
  }
  if ( tileRow == g_BlinkFlashTileX && tileColumn == g_BlinkFlashTileY )
  {
    markerSprite = DLX_GetSpriteForChar(g_WhirlSpriteSet, g_TileBlinkFlashFrame + 12);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, markerSprite, 1);
  }
  activeMission = ACTIVE_MISSION_INDEX;
  if ( activeMission == 1 )
  {
    WorldMap_DrawMission01ShrineMarker(tileRow, tileColumn, screenY, screenX);
  }
  else if ( activeMission == 11 )
  {
    WorldMap_DrawMission11ShrineMarker(tileRow, tileColumn, screenY, screenX);
  }
  if ( fogOverlayClass != -1 )
  {
    TextSprite_SetStyleFlag(1);
    fogSprite = DLX_GetSpriteForChar(g_FogOverlaySpriteSet, fogOverlayClass);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, fogSprite, 1);
  }
  UI_DrawTileHighlightOverlay(tileRow, tileColumn, screenY, screenX);
  if ( g_WorldMapTileOverlayDrawHook )
    g_WorldMapTileOverlayDrawHook(v56, tileColumn);
  if ( *(_DWORD *)(gameData + 147155) )
  {
    if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) == 1 )
      textStyleFlag = -9;
    else
      textStyleFlag = 76;
    TextSprite_ActivateResourceSlot(3, textStyleFlag, v48);
    UI_DrawText(screenX, screenY, (int)aDD_0);
  }
LABEL_2:
  if ( *(_DWORD *)(gameData + 147151) )
  {
    if ( tileColumn > *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) )
      Compat_RenderDeviceFillSolidRect(screenX, screenY, (unsigned __int16)(screenX + 63), screenY, 1u);
    if ( tileRow > *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) )
      Compat_RenderDeviceFillSolidRect(screenX, screenY, screenX, (unsigned __int16)(screenY + 63), 1u);
  }
  return MiniMap_BlitDirtyRectAndDrawViewportBox(screenX, screenY, screenY + 63, screenX + 63);
}
// 416BC0: conditional instruction was optimized away because %var_7C.4<10000u
// 416D71: variable 'v14' is possibly undefined
// 416E66: variable 'v16' is possibly undefined
// 416FE5: variable 'v19' is possibly undefined
// 4170BC: variable 'v22' is possibly undefined
// 41729A: variable 'v26' is possibly undefined
// 41734F: variable 'v28' is possibly undefined
// 4179CD: variable 'v54' is possibly undefined
// 417A33: variable 'v56' is possibly undefined
// 41854D: variable 'v105' is possibly undefined
// 418668: variable 'v92' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 513A70: using guessed type __int16 word_513A70[4];
// 5202C0: using guessed type int dword_5202C0;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 522B38: using guessed type __int16 word_522B38[223];
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
// 526998: using guessed type int dword_526998;
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418700) --------------------------------------------------------
int  WorldMap_RedrawViewport(int presentCursorOverlay)
{
  int rowIndex; // edi
  int colIndex; // ecx
  int screenX; // esi
  int result; // eax
  int cursorRight; // edi
  unsigned __int16 cursorBottom; // si
  int cursorPresented; // ebp
  int screenX2; // esi
  unsigned __int16 screenY; // [esp+4h] [ebp-2Ch]
  int cursorTop; // [esp+8h] [ebp-28h]
  int cursorLeft; // [esp+10h] [ebp-20h]

  rowIndex = 0;
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  screenY = 16;
  do
  {
    colIndex = 0;
    screenX = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 screenX,
                 screenY,
                 (unsigned __int16 *)(gameData
                                    + TILE_TERRAIN_ROW_STRIDE * (colIndex + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET))
                                    + TILE_TERRAIN_RECORD_STRIDE * (rowIndex + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET))));
      ++colIndex;
      screenX += 64;
    }
    while ( colIndex < 9 );
    ++rowIndex;
    screenY += 64;
  }
  while ( rowIndex < 6 );
  if ( !g_UnitStackSelectionModeActive )
  {
    colIndex = 0;
    screenX2 = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 screenX2,
                 ((_WORD)rowIndex << 6) + 16,
                 (unsigned __int16 *)(TILE_TERRAIN_RECORD_STRIDE * (rowIndex + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET))
                                    + gameData
                                    + TILE_TERRAIN_ROW_STRIDE * (colIndex + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET))));
      ++colIndex;
      screenX2 += 64;
    }
    while ( colIndex < 6 );
  }
  if ( g_WorldMapDrawExtensionHook )
    result = g_WorldMapDrawExtensionHook();
  if ( presentCursorOverlay )
  {
    cursorLeft = g_MouseCursorRawX >> g_CursorCoordShift;
    LOWORD(colIndex) = *(_WORD *)(g_ActiveCursorDescriptorPtr + 12);
    cursorRight = colIndex + (g_MouseCursorRawX >> g_CursorCoordShift);
    cursorTop = g_MouseCursorRawY >> g_CursorCoordShift;
    cursorBottom = *(_WORD *)(g_ActiveCursorDescriptorPtr + 16) + (g_MouseCursorRawY >> g_CursorCoordShift);
    cursorPresented = g_CursorOverlayPresented;
    if ( (unsigned __int16)(g_MouseCursorRawX >> g_CursorCoordShift) < 0x20u )
    {
      LOWORD(cursorLeft) = 32;
      if ( g_CursorOverlayPresented )
        Render_Pump();
    }
    if ( (unsigned __int16)cursorRight <= 0x20u )
    {
      LOWORD(cursorRight) = 33;
      if ( cursorPresented )
        Render_Pump();
    }
    if ( (unsigned __int16)cursorRight > 0x25Fu )
    {
      LOWORD(cursorRight) = 607;
      if ( cursorPresented )
        Render_Pump();
    }
    if ( (unsigned __int16)cursorLeft >= 0x25Fu )
    {
      LOWORD(cursorLeft) = 606;
      if ( cursorPresented )
        Render_Pump();
    }
    if ( (unsigned __int16)cursorTop < 0x10u )
    {
      LOWORD(cursorTop) = 16;
      if ( cursorPresented )
        Render_Pump();
    }
    if ( cursorBottom > 0x1CFu )
    {
      cursorBottom = 463;
      if ( cursorPresented )
        Render_Pump();
    }
    if ( g_MouseCursorRawX >> g_CursorCoordShift < 52 || g_MouseCursorRawY >> g_CursorCoordShift < 36 )
      Render_Pump();
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 32, 0x25Fu, cursorTop, 0x20u, 0x10u);
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)cursorTop, 32, cursorLeft, cursorBottom, 0x20u, cursorTop);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= 52 && g_MouseCursorRawY >> g_CursorCoordShift >= 36 )
      Input_Flush();
    result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)cursorTop, (unsigned __int16)cursorLeft, cursorRight, cursorBottom, cursorLeft, cursorTop);
    if ( cursorPresented )
      result = Render_Present((int)&g_RenderState);
    if ( (unsigned __int16)cursorRight != 607 )
      result = Render_FillRect(
                 (_DWORD *)g_PrimaryRenderSurface,
                 0,
                 (unsigned __int16)cursorTop,
                 (unsigned __int16)cursorRight,
                 0x25Fu,
                 cursorBottom,
                 cursorRight,
                 cursorTop);
    if ( cursorBottom != 463 )
      return Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, cursorBottom, 32, 0x25Fu, 0x1CFu, 0x20u, cursorBottom);
  }
  return result;
}
// 418742: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526990: using guessed type int (*dword_526990)(void);
// 526994: using guessed type int dword_526994;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00418A90) --------------------------------------------------------
int  WorldMap_RedrawTileIfVisible(int result, int tileColumn)
{
  int viewTop; // ebx
  unsigned __int16 screenX; // si
  unsigned __int16 screenY; // di
  int cursorPresented; // ebp

  if ( result < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9
    && tileColumn < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7
    && result >= *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) )
  {
    viewTop = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
    if ( tileColumn >= viewTop
      && (tileColumn != viewTop + 6 || result - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) < 6)
      && (tileColumn != *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 6 || !g_UnitStackSelectionModeActive) )
    {
      screenX = (((_WORD)result - *(_WORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 32;
      screenY = (((_WORD)tileColumn - *(_WORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 16;
      g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
      WorldMap_DrawMapTile(screenX, screenY, (unsigned __int16 *)(TILE_TERRAIN_RECORD_STRIDE * tileColumn + gameData + TILE_TERRAIN_ROW_STRIDE * result));
      cursorPresented = g_CursorOverlayPresented;
      RenderState_PumpIfRectInViewBounds(g_RenderState, screenX, screenX + 64, screenY, screenY + 64);
      result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, screenY, screenX, screenX + 63, screenY + 63, screenX, screenY);
      if ( cursorPresented )
        return Render_Present((int)g_RenderState);
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526994: using guessed type int dword_526994;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00418C00) --------------------------------------------------------
int  UI_CenterWorldMapViewportOnRectIfFit(int result, int rectColMin, int rectColMax, int rectRowMax)
{
  int mapWidthTiles; // ecx
  int mapHeightTiles; // ebx

  if ( rectRowMax - result <= 9 && rectColMax - rectColMin <= 7 )
  {
    *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = (rectRowMax + result) / 2 - 3;
    *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = (rectColMax + rectColMin) / 2 - 3;
    mapWidthTiles = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
    if ( *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 >= mapWidthTiles )
      *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = mapWidthTiles - 10;
    mapHeightTiles = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
    if ( *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 >= mapHeightTiles )
      *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = mapHeightTiles - 8;
    if ( *(int *)(gameData + MAP_VIEW_LEFT_OFFSET) < 0 )
      *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = 0;
    if ( *(int *)(gameData + MAP_VIEW_TOP_OFFSET) < 0 )
      *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = 0;
    return WorldMap_RedrawViewport(1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00418CE0) --------------------------------------------------------
int  UI_CenterWorldMapViewportOnTile(int tileRow, int tileColumn)
{
  int mapWidthTiles; // ecx
  int mapHeightTiles; // ebx

  *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = tileRow - 3;
  *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = tileColumn - 3;
  mapWidthTiles = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
  if ( *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 >= mapWidthTiles )
    *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = mapWidthTiles - 10;
  mapHeightTiles = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 >= mapHeightTiles )
    *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = mapHeightTiles - 8;
  if ( *(int *)(gameData + MAP_VIEW_LEFT_OFFSET) < 0 )
    *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = 0;
  if ( *(int *)(gameData + MAP_VIEW_TOP_OFFSET) < 0 )
    *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = 0;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;

//----- (00418D90) --------------------------------------------------------
int  UI_StartWorldMapUnitAttentionFlash(int unitIndex, int a2, int a3)
{
  int result; // eax

  g_WorldMapAttentionFlashUnitIndex = unitIndex;
  result = Time_Now(a3, a2);
  g_WorldMapAttentionFlashStartTick = result;
  return result;
}
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;

//----- (00418DA0) --------------------------------------------------------
void UI_UpdateWorldMapUnitAttentionFlash()
{
  int v0; // edx
  int v1; // ecx
  int flashUnitIndex; // eax

  if ( g_WorldMapAttentionFlashUnitIndex != -1 )
  {
    WorldMap_RedrawTileIfVisible(
      *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_WorldMapAttentionFlashUnitIndex + UNIT_STACK_TABLE_OFFSET),
      *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_WorldMapAttentionFlashUnitIndex + 147176));
    if ( (unsigned int)(30 * (Time_Now(v1, v0) - g_WorldMapAttentionFlashStartTick)) >= 0x708 )
    {
      flashUnitIndex = g_WorldMapAttentionFlashUnitIndex;
      g_WorldMapAttentionFlashUnitIndex = -1;
      Map_RedrawUnitFootprintByIndex(flashUnitIndex);
    }
  }
}
// 418DE4: variable 'v1' is possibly undefined
// 418DE4: variable 'v0' is possibly undefined
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 5202E4: using guessed type int gameData;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;

//----- (00418E20) --------------------------------------------------------
BOOL UI_IsWorldMapUnitAttentionFlashActive()
{
  return g_WorldMapAttentionFlashUnitIndex != -1;
}
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;

//----- (00418E30) --------------------------------------------------------
int  UI_StartUnitBlinkFlash(int unitIndex, int a2, int a3)
{
  int result; // eax

  g_UnitBlinkFlashUnitIndex = unitIndex;
  result = Time_Now(a3, a2);
  g_UnitBlinkFlashTickTime = result;
  g_UnitBlinkFlashFrame = 0;
  return result;
}
// 5139F8: using guessed type int dword_5139F8;
// 5269A0: using guessed type int dword_5269A0;
// 5269A4: using guessed type int dword_5269A4;

//----- (00418E50) --------------------------------------------------------
void __fastcall UI_UpdateUnitBlinkFlash(int a1, int a2)
{
  int v2; // ecx
  int currentTime; // eax
  int flashUnitIndex; // eax

  if ( g_UnitBlinkFlashUnitIndex != -1 && Time_Now(a1, a2) > (unsigned int)(g_UnitBlinkFlashTickTime + 10) )
  {
    currentTime = Time_Now(v2, g_UnitBlinkFlashTickTime + 10);
    g_UnitBlinkFlashFrame += (currentTime - g_UnitBlinkFlashTickTime) / 0xAu;
    g_UnitBlinkFlashTickTime = Time_Now(10, (currentTime - g_UnitBlinkFlashTickTime) % 0xAu);
    flashUnitIndex = g_UnitBlinkFlashUnitIndex;
    if ( g_UnitBlinkFlashFrame >= 12 )
      g_UnitBlinkFlashUnitIndex = -1;
    Map_RedrawUnitFootprintByIndex(flashUnitIndex);
  }
}
// 418E70: variable 'v2' is possibly undefined
// 5139F8: using guessed type int dword_5139F8;
// 5269A0: using guessed type int dword_5269A0;
// 5269A4: using guessed type int dword_5269A4;

//----- (00418EC0) --------------------------------------------------------
int  UI_StartTileBlinkFlash(int tileX, int tileY, int a3)
{
  int result; // eax

  g_BlinkFlashTileY = tileY;
  g_BlinkFlashTileX = tileX;
  g_TileBlinkFlashFrame = 0;
  result = Time_Now(a3, 0);
  g_TileBlinkFlashTickTime = result;
  return result;
}
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418EE0) --------------------------------------------------------
void __fastcall UI_UpdateTileBlinkFlash(int a1, int a2)
{
  int v2; // ecx
  int currentTime; // eax
  int tileX; // eax

  if ( g_BlinkFlashTileX != -1 && Time_Now(a1, a2) > (unsigned int)(g_TileBlinkFlashTickTime + 10) )
  {
    currentTime = Time_Now(v2, g_TileBlinkFlashTickTime + 10);
    g_TileBlinkFlashFrame += (currentTime - g_TileBlinkFlashTickTime) / 0xAu;
    g_TileBlinkFlashTickTime = Time_Now(10, (currentTime - g_TileBlinkFlashTickTime) % 0xAu);
    tileX = g_BlinkFlashTileX;
    if ( g_TileBlinkFlashFrame >= 8 )
      g_BlinkFlashTileX = -1;
    WorldMap_RedrawTileIfVisible(tileX, g_BlinkFlashTileY);
  }
}
// 418F00: variable 'v2' is possibly undefined
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418F60) --------------------------------------------------------
signed int  UI_HighlightTile(int tileX, int tileY)
{
  signed int slot_index; // eax

  slot_index = 0;
  while ( tileX != g_TileHighlightSlots[slot_index].tile_x || tileY != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
    {
      slot_index = 0;
      if ( g_TileHighlightSlots[0].tile_x == -1 )
      {
LABEL_8:
        g_TileHighlightSlots[slot_index].tile_x = tileX;
        g_TileHighlightSlots[slot_index].tile_y = tileY;
      }
      else
      {
        while ( 1 )
        {
          ++slot_index;
          if ( slot_index >= 8 )
            break;
          if ( g_TileHighlightSlots[slot_index].tile_x == -1 )
            goto LABEL_8;
        }
      }
      return 8 * slot_index;
    }
  }
  return 8 * slot_index;
}

//----- (00418FE0) --------------------------------------------------------
int __thiscall UI_ClearTileHighlight(void *this)
{
  (void)this;
  memset(g_TileHighlightSlots, 0xFF, sizeof(g_TileHighlightSlots));
  return (int)g_TileHighlightSlots;
}

//----- (00419000) --------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int  UI_DrawTileHighlightOverlay(int tileX, int tileY, int screenLeft, int screenTop)
{
  int slot_index; // eax
  unsigned __int16 SpriteWidth; // ax
  unsigned __int16 SpriteHeight; // ax
  int centered_x; // esi
  int centered_y; // edi
  int SpriteForChar; // eax

  if ( g_ActiveUnitMoveTileIndex != -1 )
    return Noop_WorldMapFrameRedrawHook();
  slot_index = 0;
  while ( tileX != g_TileHighlightSlots[slot_index].tile_x || tileY != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
      return Noop_WorldMapFrameRedrawHook();
  }
  SpriteWidth = DLX_GetSpriteWidth(g_MarksSpriteSet, 0x28u);
  centered_x = screenLeft + (64 - SpriteWidth) / 2;
  SpriteHeight = DLX_GetSpriteHeight(g_MarksSpriteSet, 0x28u);
  centered_y = screenTop + (64 - SpriteHeight) / 2;
  SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 40);
  return Sprite_DrawSimpleTrackingOffset(SpriteForChar, centered_y, centered_x, screenLeft, screenTop + 63, screenLeft + 63, 80, 1u);
}
// 4190A8: positive sp value 8 has been found
// 419030: using guessed type int nullsub_1(void);
// 512360: using guessed type int dword_512360;
// 5202C8: using guessed type int dword_5202C8;

//----- (004190B0) --------------------------------------------------------
void BattleLog_Disable()
{
  battleLogEnabled = 0;
}
// 5139FC: using guessed type int battleLogEnabled;

//----- (004190C0) --------------------------------------------------------
void BattleLog_Enable()
{
  battleLogEnabled = 1;
}
// 5139FC: using guessed type int battleLogEnabled;

//----- (004190D0) --------------------------------------------------------
void  createLogFiles(int a1, int a2, DWORD a3)
{
  FILE *log_file;

  (void)a1;
  (void)a2;
  (void)a3;
  if ( logEnabled )
  {
    log_file = fopen(aClash_log, "wb");
    if ( log_file )
      fclose(log_file);
    log_file = fopen(aBattle_log, "wb");
    if ( log_file )
      fclose(log_file);
    g_BattleInProgressFlag = 0;
  }
}
// 526A1C: using guessed type int logEnabled;
// 526A20: using guessed type int dword_526A20;

//----- (00419110) --------------------------------------------------------
int  Battle_StoreLastOutcomeValue(int result)
{
  g_BattleInProgressFlag = result;
  return result;
}
// 526A20: using guessed type int dword_526A20;

CLASH95_INTERNAL int Compat_RenderDeviceDrawMenuSprite(int left, int top, int sprite_for_char, unsigned char draw_mode);

CLASH95_INTERNAL int Compat_CountPrintfArgs32(const char *format)
{
  int count;

  count = 0;
  while ( format && *format )
  {
    if ( *format++ != '%' )
      continue;
    if ( *format == '%' )
    {
      ++format;
      continue;
    }
    while ( *format == '#' || *format == '0' || *format == '-' || *format == ' ' || *format == '+' )
      ++format;
    if ( *format == '*' )
    {
      ++count;
      ++format;
    }
    else
    {
      while ( *format >= '0' && *format <= '9' )
        ++format;
    }
    if ( *format == '.' )
    {
      ++format;
      if ( *format == '*' )
      {
        ++count;
        ++format;
      }
      else
      {
        while ( *format >= '0' && *format <= '9' )
          ++format;
      }
    }
    if ( *format == 'I' && format[1] == '6' && format[2] == '4' )
      format += 3;
    else if ( *format == 'h' || *format == 'l' || *format == 'L' || *format == 'N' || *format == 'F' || *format == 'w' )
    {
      if ( (*format == 'h' && format[1] == 'h') || (*format == 'l' && format[1] == 'l') )
        ++format;
      ++format;
    }
    if ( *format )
    {
      ++count;
      ++format;
    }
  }
  return count;
}

//----- (00419120) --------------------------------------------------------
void  Debug_Log(int a1, char a2, DWORD a3, int a4, ...)
{
  const CHAR *log_path;
  unsigned __int8 *open_mode;
  int output_handle;
  const char *format;
  unsigned int centiseconds;
  unsigned int seconds;
  unsigned int minutes;
  int low32_line_ptr;
  char *line_buffer;
  int line_length;

  if ( !logEnabled || !battleLogEnabled )
    return;

  /*
   * The Watcom-style formatter/stream path under `sub_476301` / `sub_488DF2`
   * is still being re-emitted for x86_64. Keep runtime-side sprite/resource
   * probes alive by neutralizing logging rather than crashing inside that
   * auxiliary path.
   */
  return;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5139FC: using guessed type int battleLogEnabled;
// 526A1C: using guessed type int logEnabled;
// 526A20: using guessed type int dword_526A20;
