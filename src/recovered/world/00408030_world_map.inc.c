/* Strategic world map, minimap, camera, fog, roads, and map UI.
 * Original function-marker range: 0x00408030..0x0040F4D0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00408030) --------------------------------------------------------
BOOL UI_TrySelectFriendlyStackUnderCursor()
{
  BOOL result; // eax
  int tileX; // esi
  int tileY; // ecx
  unsigned int stackIndex; // edx

  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    tileY = (((g_MouseCursorRawY >> g_CursorCoordShift)
         - 16
         - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
          + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
       + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
    if ( tileY == *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 6
      && ((g_MouseCursorRawX >> g_CursorCoordShift)
        - 32
        - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
         + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6 >= 6 )
    {
      return 0;
    }
    tileX = (((g_MouseCursorRawX >> g_CursorCoordShift)
         - 32
         - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
          + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
       + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    stackIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY));
    if ( stackIndex > 0x7FFF || stackIndex == g_SelectedUnitIndex || *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178) != g_CurrentPlayerIndex )
    {
      return 0;
    }
    else
    {
      result = 1;
      g_SelectedUnitIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY));
      Diagnostics_TraceWorldMapActionEvent("selected_stack_changed", g_SelectedUnitIndex, tileX, tileY, 0);
    }
  }
  return result;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00408140) --------------------------------------------------------
BOOL  MapTile_HasOwnUnitStack(int tileX, int tileY)
{
  unsigned __int16 stackIndex; // bx
  int stackIndexDword; // edx

  HIWORD(stackIndexDword) = 0;
  stackIndex = *(_WORD *)(TILE_INDEX(tileX, tileY));
  LOWORD(stackIndexDword) = stackIndex;
  return stackIndex <= 0x1F4u
      && (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndexDword + 147180) <= 0x28
      && *(unsigned __int8 *)(UNIT_STACK_STRIDE * stackIndex + gameData + 147178) == g_CurrentPlayerIndex;
}
// 4081A7: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408200) --------------------------------------------------------
BOOL  MapTile_HasVisibleEnemyUnitStack(int tileX, int tileY)
{
  int stackIndex; // edx
  int stackRecord; // eax
  BOOL result; // eax

  stackIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY));
  result = 0;
  if ( (unsigned __int16)stackIndex <= 0x1F4u && (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180) <= 0x28 )
  {
    stackRecord = gameData + UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(tileX, tileY));
    if ( *(unsigned __int8 *)(stackRecord + 147178) != g_CurrentPlayerIndex && !*(_BYTE *)(stackRecord + 147894) )
      return 1;
  }
  return result;
}
// 408268: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004082C0) --------------------------------------------------------
BOOL  MapTile_HasOwnOrVisibleEnemyUnitStack(int tileX, int tileY)
{
  BOOL result; // eax

  if ( MapTile_HasOwnUnitStack(tileX, tileY) )
    return 1;
  result = MapTile_HasVisibleEnemyUnitStack(tileX, tileY);
  if ( result )
    return 1;
  return result;
}

//----- (004082F0) --------------------------------------------------------
BOOL  MapTile_HasOwnBuilding(int tileX, int tileY)
{
  unsigned int buildingIndex; // eax
  int buildingTableRecord; // edx
  int buildingRecord; // eax
  BOOL result; // eax

  buildingIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  result = 0;
  if ( buildingIndex <= 0x64 )
  {
    buildingTableRecord = UNIT_RECORD(buildingIndex);
    if ( (unsigned int)*(char *)(buildingTableRecord + 4) < 4 && *(__int16 *)(buildingTableRecord + 16) != -1 )
    {
      buildingRecord = gameData + BUILDING_RECORD_SIZE * buildingIndex;
      if ( *(unsigned __int8 *)(buildingRecord + 509676) == g_CurrentPlayerIndex && *(__int16 *)(buildingRecord + 509690) != -1 )
        return 1;
    }
  }
  return result;
}
// 40832B: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 408346: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408390) --------------------------------------------------------
BOOL  MapTile_HasEnemyBuilding(int tileX, int tileY)
{
  unsigned int buildingIndex; // eax
  int buildingTableRecord; // edx
  int buildingRecord; // eax
  BOOL result; // eax

  buildingIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  result = 0;
  if ( buildingIndex <= 0x64 )
  {
    buildingTableRecord = UNIT_RECORD(buildingIndex);
    if ( (unsigned int)*(char *)(buildingTableRecord + 4) < 4 && *(__int16 *)(buildingTableRecord + 16) != -1 )
    {
      buildingRecord = gameData + BUILDING_RECORD_SIZE * buildingIndex;
      if ( *(unsigned __int8 *)(buildingRecord + 509676) != g_CurrentPlayerIndex && *(__int16 *)(buildingRecord + 509690) != -1 )
        return 1;
    }
  }
  return result;
}
// 4083CB: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 4083E6: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408430) --------------------------------------------------------
BOOL  MapTile_HasBuilding(int tileX, int tileY)
{
  BOOL result; // eax

  if ( MapTile_HasOwnBuilding(tileX, tileY) )
    return 1;
  result = MapTile_HasEnemyBuilding(tileX, tileY);
  if ( result )
    return 1;
  return result;
}

//----- (00408460) --------------------------------------------------------
BOOL  Port_IsInsideFootprint(int tileX, int tileY)
{
  int portRow; // ebx
  int portColumn; // edi
  BOOL result; // eax

  portRow = PORT_ROW;
  result = 0;
  if ( portRow != -1 && tileX >= portRow && tileX <= portRow + 1 )
  {
    portColumn = PORT_COLUMN;
    if ( tileY >= portColumn && tileY <= portColumn + 1 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004084A0) --------------------------------------------------------
void  WorldMap_HandleTileHoverAndClick(double a1)
{
  int tileX; // ebp
  int v2; // edx
  int v3; // ecx
  unsigned __int16 *tileColumnBase; // ecx
  int v5; // ebx
  int v6; // ecx
  void *cursorDescriptor; // edx
  int tileYByteOffset; // edi
  int tileXByteOffset; // esi
  int v10; // ecx
  unsigned int terrainClass; // ecx
  char *terrainNamePl; // eax
  char *terrainNameEn; // edx
  char *terrainNameDe; // ecx
  void *attackCursorDesc; // edx
  void *v16; // ecx
  int buildingTileYOffset; // esi
  int buildingRecordByteOffset; // ecx
  int buildingRecord; // edx
  DWORD buildingTableRecord; // eax
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  char v27; // bl
  char v28; // di
  const void *portApproachTrack; // ebp
  int v30; // ebx
  int v31; // ecx
  const void *approachTrack; // ebp
  void *pathBufferDest; // edi
  void (*v34)(void); // edx
  _DWORD *portTrack; // ebp
  int v36; // edx
  char v37; // bl
  __int16 *Supply; // eax
  __int16 *shipment; // eax
  int v40; // esi
  int v41; // ecx
  int buildingIndex; // eax
  int buildingRecordOffset; // ebx
  __int16 constructionState; // si
  int hasOwnBuilding; // edi
  int buildingTileXOffset; // esi
  int ownBuildingTileYOffset; // ecx
  int targetBuildingIndex; // edx
  int v49; // ecx
  int v50; // ecx
  char v51; // bl
  int v52; // ecx
  int tileStackPtr; // eax
  char v54; // di
  void *v55; // ecx
  DWORD prevSelectedIndex; // ebp
  void *v57; // ecx
  int v58; // ecx
  void *v59; // ecx
  void *v60; // ecx
  DWORD v61; // ebp
  int v62; // edx
  int unitTileY; // ebx
  const void *moveTrack; // eax
  DWORD selectedStackByteOffset; // ebp
  DWORD selectedStackRecord; // edx
  int v67; // ecx
  int stackPosPacked; // eax
  char *tooltipTextPl; // [esp+0h] [ebp-70h]
  char *tooltipTextEn; // [esp+4h] [ebp-6Ch]
  char *tooltipTextDe; // [esp+8h] [ebp-68h]
  int shrineTextPtrs[3]; // [esp+Ch] [ebp-64h]
  int cultPlaceTextPtrs[3]; // [esp+18h] [ebp-58h]
  int emptyShrineTextPtrs[3]; // [esp+24h] [ebp-4Ch]
  int emptyCultPlaceTextPtrs[3]; // [esp+30h] [ebp-40h]
  int hiddenTreasureTextPtrs[3]; // [esp+3Ch] [ebp-34h]
  int castleFoundationTextPtrs[3]; // [esp+48h] [ebp-28h]
  int tileY; // [esp+54h] [ebp-1Ch]
  int bridge_crossings_enabled;

  if ( MiniMap_IsCursorInside() )
    goto LABEL_35;
  if ( g_MouseCursorRawX >> g_CursorCoordShift < 32 )
    return;
  if ( g_MouseCursorRawY >> g_CursorCoordShift < 16 )
    return;
  tileX = (((g_MouseCursorRawX >> g_CursorCoordShift)
       - 32
       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
        + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
     + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
  tileY = (((g_MouseCursorRawY >> g_CursorCoordShift)
        - 16
        - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
         + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
      + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
  if ( tileX < 0
    || tileX >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
    || tileY < 0
    || tileY >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
    || *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 6 == tileY && tileX - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) >= 6 )
  {
    if ( DD_IsLost((int)&g_RenderState) || DD_IsFlipping((int)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "reject_out_of_bounds",
        tileX,
        tileY,
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    return;
  }
  Diagnostics_TraceWorldMapCursorSample(
    tileX,
    tileY,
    *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
    *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
    g_SelectedUnitIndex);
  if ( DD_IsLost((int)&g_RenderState) || DD_IsFlipping((int)&g_RenderState) )
    Diagnostics_TraceWorldMapClickEvent(
      "tile_input",
      tileX,
      tileY,
      *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
      *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
      g_SelectedUnitIndex);
  if ( DD_IsFlipping((int)&g_RenderState) || DD_IsLost((int)&g_RenderState) )
    goto LABEL_12;
  LOBYTE(v3) = g_CursorCoordShift;
  if ( g_MouseCursorRawX >> g_CursorCoordShift == g_WorldMap_LastCursorTileX && g_MouseCursorRawY >> g_CursorCoordShift == g_WorldMap_LastCursorTileY )
  {
    if ( g_WorldMap_HoverTooltipActiveFlag )
      goto LABEL_12;
  }
  else
  {
    LOBYTE(v3) = g_CursorCoordShift;
    g_WorldMap_LastCursorTileX = g_MouseCursorRawX >> g_CursorCoordShift;
    g_WorldMap_LastCursorTileY = g_MouseCursorRawY >> g_CursorCoordShift;
    g_WorldMap_CursorTileEnterTime = Time_Now(v3, v2);
    if ( g_WorldMap_HoverTooltipActiveFlag )
      WorldMap_RefreshUnitStatusPanel(tileX);
    v2 = 0;
    g_WorldMap_HoverTooltipActiveFlag = 0;
  }
  if ( (unsigned int)(Time_Now(v3, v2) - g_WorldMap_CursorTileEnterTime) > 0xC8
    && *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) == 0xFFFF )
  {
    Map_GetTileSurfaceClassOrUnexplored(tileX, tileY);
    if ( !Map_IsTileVisibleToPlayer(tileX, tileY, g_CurrentPlayerIndex) )
    {
      tooltipTextPl = aTerenNieodkryt;
      tooltipTextEn = aUnexploredTerr;
      tooltipTextDe = aUnerforschtesT;
      goto LABEL_48;
    }
    if ( terrainClass >= 0xB7 )
    {
      if ( terrainClass <= 0xB7 )
      {
        terrainNamePl = aRvwnina4pa;
        terrainNameEn = aPlain4ap;
        terrainNameDe = aEbene;
        goto LABEL_47;
      }
      if ( terrainClass >= 0xCA )
      {
        if ( terrainClass <= 0xCA )
        {
          terrainNamePl = aGvryWysokie;
          terrainNameEn = aMountains;
          terrainNameDe = aBerge;
          goto LABEL_47;
        }
        if ( terrainClass >= 0xCC )
        {
          if ( terrainClass <= 0xCC )
          {
            tooltipTextPl = aGvryNiskie8pa;
            tooltipTextEn = aHills8ap;
            tooltipTextDe = aHbgel;
            goto LABEL_48;
          }
          if ( terrainClass == 207 )
          {
            terrainNamePl = aDroga3pa;
            terrainNameEn = aRoad3ap;
            terrainNameDe = aStrase;
            goto LABEL_47;
          }
        }
      }
      else if ( terrainClass == 185 )
      {
        tooltipTextPl = aLas6pa;
        tooltipTextEn = aForest6ap;
        tooltipTextDe = aBaum;
        goto LABEL_48;
      }
    }
    else if ( terrainClass >= 0x93 )
    {
      if ( terrainClass <= 0x93 )
      {
        terrainNamePl = aWoda;
        terrainNameEn = aWater;
        terrainNameDe = aWasser;
        goto LABEL_47;
      }
      if ( terrainClass == 151 )
      {
        tooltipTextPl = aPustynia5pa;
        tooltipTextEn = aDesert5ap;
        tooltipTextDe = aWbste;
        goto LABEL_48;
      }
    }
    else if ( terrainClass == 39 )
    {
      terrainNamePl = aBagno7pa;
      terrainNameEn = aSwamp7ap;
      terrainNameDe = aSumpf;
LABEL_47:
      tooltipTextPl = terrainNamePl;
      tooltipTextEn = terrainNameEn;
      tooltipTextDe = terrainNameDe;
LABEL_48:
      if ( (unsigned __int8)g_LanguageIndex == 0 )
        Tooltip_ShowText(3, tooltipTextPl);
      else if ( (unsigned __int8)g_LanguageIndex == 2 )
        Tooltip_ShowText(3, tooltipTextDe);
      else
        Tooltip_ShowText(3, tooltipTextEn);
      g_WorldMap_HoverTooltipActiveFlag = 1;
      goto LABEL_12;
    }
    tooltipTextPl = aBlad;
    tooltipTextEn = aError;
    tooltipTextDe = aError_0;
    goto LABEL_48;
  }
LABEL_12:
  if ( !Map_ClassifyFogOfWarOverlayForPlayer(tileX, tileY, g_CurrentPlayerIndex) )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      Diagnostics_TraceWorldMapClickEvent(
        "reject_fog",
        tileX,
        tileY,
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
LABEL_35:
    RenderState_SelectCursorDescriptor((int)&g_RenderState, (int)&g_CursorDesc_Default);
    return;
  }
  v5 = 0;
  if ( g_SelectedUnitIndex != -1 && MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) )
  {
    if ( MapTile_HasOwnUnitStack(tileX, tileY) )
    {
      if ( *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) == g_SelectedUnitIndex
        && *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
      {
        v5 = 1;
        RenderState_SelectCursorDescriptor((int)&g_RenderState, (int)&g_CursorDesc_SelectedUnitHover);
        g_WorldMapActionHoverActive = 1;
        goto LABEL_21;
      }
      tileColumnBase = (unsigned __int16 *)(200 * tileX + gameData);
      if ( tileColumnBase[tileY + 278187] != g_SelectedUnitIndex && g_WorldMapJoinUnitsModeActive )
      {
        RenderState_SelectCursorDescriptor((int)&g_RenderState, (int)&g_CursorDesc_CannotSelect);
        g_WorldMapActionHoverActive = v6;
        goto LABEL_21;
      }
    }
    else if ( MapTile_HasVisibleEnemyUnitStack(tileX, tileY) )
    {
      if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
        attackCursorDesc = &g_CursorDesc_Attack;
      else
        attackCursorDesc = &g_CursorDesc_CannotAttack;
      RenderState_SelectCursorDescriptor((int)&g_RenderState, (int)attackCursorDesc);
      g_WorldMapActionHoverActive = 1;
      goto LABEL_21;
    }
  }
  if ( g_WorldMapActionHoverActive )
  {
    WorldMap_RefreshActionButtonBarState(tileColumnBase);
    g_WorldMapActionHoverActive = 0;
  }
LABEL_21:
  if ( g_SelectedUnitIndex != -1 && MapTile_GetReligiousSiteCategory(tileX, tileY) )
  {
    if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
    {
LABEL_24:
      cursorDescriptor = &g_CursorDesc_EnterSite;
LABEL_25:
      RenderState_SelectCursorDescriptor((int)&g_RenderState, (int)cursorDescriptor);
      goto LABEL_26;
    }
LABEL_80:
    cursorDescriptor = &g_CursorDesc_CannotEnter;
    goto LABEL_25;
  }
  if ( Port_IsInsideFootprint(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 )
    {
      cursorDescriptor = &g_CursorDesc_GoTo;
      goto LABEL_25;
    }
    if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
      goto LABEL_24;
    goto LABEL_80;
  }
  if ( MapTile_HasBuilding(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 )
    {
      cursorDescriptor = &g_CursorDesc_GoTo;
      goto LABEL_25;
    }
    buildingTileYOffset = 2 * tileY;
    v5 = 200 * tileX;
    if ( !MapTile_HasOwnBuilding(tileX, tileY) )
    {
      if ( !UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
        || (v5 += gameData,
            *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(buildingTileYOffset + v5 + 556374) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + 509678) == 1)
        && UnitStack_HasPeasantCargo(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
      {
        cursorDescriptor = &g_CursorDesc_DeliverCargo;
      }
      else
      {
        cursorDescriptor = &g_CursorDesc_VisitBuilding;
      }
      goto LABEL_25;
    }
    v5 += gameData;
    if ( !Building_CanAcceptUnitStack(g_SelectedUnitIndex, *(unsigned __int16 *)(buildingTileYOffset + v5 + 556374) - TILE_OCCUPANT_BUILDING_INDEX_BASE) )
    {
      cursorDescriptor = &g_CursorDesc_CannotEnter;
      goto LABEL_25;
    }
    goto LABEL_24;
  }
  if ( (_UNKNOWN *)g_ActiveCursorDescriptorPtr == &g_CursorDesc_GoTo
    || (_UNKNOWN *)g_ActiveCursorDescriptorPtr == &g_CursorDesc_EnterSite
    || (_UNKNOWN *)g_ActiveCursorDescriptorPtr == &g_CursorDesc_VisitBuilding
    || (_UNKNOWN *)g_ActiveCursorDescriptorPtr == &g_CursorDesc_DeliverCargo
    || (_UNKNOWN *)g_ActiveCursorDescriptorPtr == &g_CursorDesc_CannotEnter )
  {
    WorldMap_RefreshActionButtonBarState(v16);
  }
LABEL_26:
  if ( DD_IsLost((int)&g_RenderState) && Port_IsInsideFootprint(tileX, tileY) )
    UI_DrawPortStatusPanel(v5, tileX);
  if ( DD_IsLost((int)&g_RenderState) )
  {
    tileYByteOffset = 2 * tileY;
    tileXByteOffset = 200 * tileX;
    if ( MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) )
    {
      if ( Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET)) <= 1 )
      {
        Unit_Info(100, 100, 0, UNIT_STACK_STRIDE * *(unsigned __int16 *)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET) + gameData + UNIT_STACK_TABLE_OFFSET + 6, tileX, 0);
      }
      else
      {
        UnitStack_ShowSelectionDialog(*(unsigned __int16 *)(tileYByteOffset + tileXByteOffset + gameData + TILE_MAP_OFFSET), v5);
        UIWidget_RefreshActionButtonState((int)&g_WorldMapJoinUnitsWidgetRecord, v10);
      }
    }
    else if ( MapTile_HasBuilding(tileX, tileY) )
    {
      buildingRecordByteOffset = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
      buildingRecord = gameData + buildingRecordByteOffset;
      buildingTableRecord = buildingRecordByteOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( *(_WORD *)(gameData + buildingRecordByteOffset + 509690) )
      {
        if ( *(unsigned __int8 *)(buildingRecord + 509676) == g_CurrentPlayerIndex && *(__int16 *)(buildingRecord + 509690) != -1 )
          Building_ShowConstructionProgressDialog(buildingTableRecord, g_CurrentPlayerIndex, tileX, a1);
      }
      else
      {
        Building_ShowHoverInfoPopup(buildingTableRecord, 0, tileYByteOffset);
      }
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_SHRINE )
    {
      shrineTextPtrs[0] = (int)g_ShrineTexts[0];
      shrineTextPtrs[1] = (int)g_ShrineTexts[1];
      shrineTextPtrs[2] = (int)g_ShrineTexts[2];
      UI_ShowSimpleTextInfoWindow(shrineTextPtrs[(unsigned __int8)g_LanguageIndex], v21, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE )
    {
      emptyShrineTextPtrs[0] = (int)g_EmptyShrineTexts[0];
      emptyShrineTextPtrs[1] = (int)g_EmptyShrineTexts[1];
      emptyShrineTextPtrs[2] = (int)g_EmptyShrineTexts[2];
      UI_ShowSimpleTextInfoWindow(emptyShrineTextPtrs[(unsigned __int8)g_LanguageIndex], v22, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_CULT_PLACE )
    {
      cultPlaceTextPtrs[0] = (int)g_CultPlaceTexts[0];
      cultPlaceTextPtrs[1] = (int)g_CultPlaceTexts[1];
      cultPlaceTextPtrs[2] = (int)g_CultPlaceTexts[2];
      UI_ShowSimpleTextInfoWindow(cultPlaceTextPtrs[(unsigned __int8)g_LanguageIndex], v23, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE )
    {
      emptyCultPlaceTextPtrs[0] = (int)g_EmptyCultPlaceTexts[0];
      emptyCultPlaceTextPtrs[1] = (int)g_EmptyCultPlaceTexts[1];
      emptyCultPlaceTextPtrs[2] = (int)g_EmptyCultPlaceTexts[2];
      UI_ShowSimpleTextInfoWindow(emptyCultPlaceTextPtrs[(unsigned __int8)g_LanguageIndex], v24, v5, tileX);
    }
    else if ( MapTile_IsCastleFoundationTile(tileX, tileY, 2) )
    {
      castleFoundationTextPtrs[0] = (int)g_CastleFoundationTexts[0];
      castleFoundationTextPtrs[1] = (int)g_CastleFoundationTexts[1];
      castleFoundationTextPtrs[2] = (int)g_CastleFoundationTexts[2];
      UI_ShowSimpleTextInfoWindow(castleFoundationTextPtrs[(unsigned __int8)g_LanguageIndex], v25, 2, tileX);
    }
    else if ( MapTile_HasHiddenTreasure(tileX, tileY) )
    {
      hiddenTreasureTextPtrs[0] = (int)g_HiddenTreasureTexts[0];
      hiddenTreasureTextPtrs[1] = (int)g_HiddenTreasureTexts[1];
      hiddenTreasureTextPtrs[2] = (int)g_HiddenTreasureTexts[2];
      UI_ShowSimpleTextInfoWindow(hiddenTreasureTextPtrs[(unsigned __int8)g_LanguageIndex], v26, 2, tileX);
    }
  }
  if ( !DD_IsFlipping((int)&g_RenderState) )
    return;
  v27 = g_CurrentPlayerIndex;
  if ( Trap_GetTileOwnerMask(tileX, tileY, g_CurrentPlayerIndex) )
    Trap_ShowPitfallDiscoveryDialog(tileX, tileY, v27, tileX);
    if ( g_SelectedUnitIndex != -1
      && UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
      && MapTile_GetReligiousSiteCategory(tileX, tileY) )
  {
    LOBYTE(v30) = tileY;
    if ( !QueuedPath_StartsAtTile(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET, tileX, tileY) )
    {
      LOBYTE(v30) = tileY;
      bridge_crossings_enabled = UnitStack_HasBuilder(g_SelectedUnitIndex);
      if ( bridge_crossings_enabled )
      {
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_enable_temple", g_SelectedUnitIndex, tileX, tileY, 0);
        Pathing_EnableBridgeCrossings(g_SelectedUnitIndex, (char)tileY, 0);
      }
      approachTrack = (const void *)Temple_GenerateApproachTrack(g_SelectedUnitIndex, tileX, v31, tileY);
      if ( bridge_crossings_enabled )
      {
        Pathing_DisableBridgeCrossings(g_SelectedUnitIndex, (char)(uintptr_t)approachTrack, 0);
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_disable_temple", g_SelectedUnitIndex, tileX, tileY, approachTrack != 0);
      }
      if ( approachTrack )
      {
        pathBufferDest = (void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET);
        qmemcpy(pathBufferDest, approachTrack, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        Diagnostics_TraceWorldMapActionEvent("temple_path_queued", g_SelectedUnitIndex, tileX, tileY, 1);
        WorldMap_RedrawViewport(1);
        Render_Begin((int)&g_RenderState, 0);
      }
      if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) != 1 )
        return;
      goto LABEL_138;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
    goto LABEL_205;
  }
  v28 = g_SelectedUnitIndex;
    if ( g_SelectedUnitIndex != -1
      && UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
      && Port_IsInsideFootprint(tileX, tileY) )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
    {
      portTrack = (_DWORD *)Port_GenerateApproachTrack(g_SelectedUnitIndex);
      v27 = gameData - 26;
      if ( *portTrack )
        v36 = portTrack[1];
      else
        v36 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 320);
      if ( (unsigned __int16)*(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 320) == (_WORD)v36 )
      {
        v37 = gameData;
        qmemcpy((void *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), portTrack, UNIT_STACK_PATH_BYTES);
        if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) || !*portTrack )
        {
          if ( *portTrack )
          {
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
            UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v37, (DWORD)portTrack, a1);
            WorldMap_RefreshUnitStatusPanel((DWORD)portTrack);
          }
          if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
          {
            Supply = (__int16 *)Port_CollectReinforcementShipment(145 * g_SelectedUnitIndex, v37, (DWORD)portTrack, a1);
            if ( Supply )
              UI_CenterWorldMapViewportOnRectIfFit(
                *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
                *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
                Supply[1],
                *Supply);
          }
        }
        j__nfree_();
        return;
      }
      j__nfree_();
    }
    portApproachTrack = (const void *)Port_GenerateApproachTrack(g_SelectedUnitIndex);
    if ( portApproachTrack )
    {
      qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET), portApproachTrack, UNIT_STACK_PATH_BYTES);
      j__nfree_();
      WorldMap_RedrawViewport(1);
      if ( !*(_DWORD *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) )
      {
        shipment = (__int16 *)Port_CollectReinforcementShipment(UNIT_STACK_STRIDE * g_SelectedUnitIndex, v27, (DWORD)portApproachTrack, a1);
        if ( shipment )
          UI_CenterWorldMapViewportOnRectIfFit(
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
            shipment[1],
            *shipment);
      }
    }
    return;
  }
  if ( Port_IsInsideFootprint(tileX, tileY) )
  {
    UI_DrawPortStatusPanel(v27, tileX);
    return;
  }
  v40 = 2 * tileY;
  if ( MapTile_HasBuilding(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 && MapTile_HasOwnBuilding(tileX, tileY) )
    {
      buildingIndex = *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
      buildingRecordOffset = BUILDING_RECORD_SIZE * buildingIndex;
      constructionState = *(_WORD *)(gameData + BUILDING_RECORD_SIZE * buildingIndex + 509690);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[world_click] own_building_enter_branch tile=%d,%d building_idx=%d construction=%d current_player=%d flipping=%d lost=%d\n",
          tileX,
          tileY,
          buildingIndex,
          constructionState,
          g_CurrentPlayerIndex,
          DD_IsFlipping((int)&g_RenderState),
          DD_IsLost((int)&g_RenderState));
      if ( constructionState )
      {
        if ( constructionState != -1 )
          Building_ShowConstructionProgressDialog(buildingRecordOffset + gameData + BUILDING_TABLE_OFFSET, buildingRecordOffset, tileX, a1);
      }
      else
      {
        Building_GetInto(buildingIndex, buildingRecordOffset, tileX);
      }
      return;
    }
    hasOwnBuilding = MapTile_HasOwnBuilding(tileX, tileY);
    buildingTileXOffset = 200 * tileX;
    v30 = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
    ownBuildingTileYOffset = 2 * tileY;
    if ( !hasOwnBuilding )
    {
      if ( g_SelectedUnitIndex != -1
        && (*(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(ownBuildingTileYOffset + gameData + buildingTileXOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509678) != 1
         || !UnitStack_HasPeasantCargo(v30 + gameData + UNIT_STACK_TABLE_OFFSET)) )
      {
        Unit_AttackBuilding(
          g_SelectedUnitIndex,
          *(unsigned __int16 *)(2 * tileY + gameData + TILE_ROW_STRIDE * tileX + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
          v30,
          200 * tileX,
          a1);
      }
      return;
    }
    targetBuildingIndex = *(unsigned __int16 *)(ownBuildingTileYOffset + gameData + buildingTileXOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( *(_WORD *)(BUILDING_RECORD_SIZE * targetBuildingIndex + gameData + 509690) )
      return;
    if ( !QueuedPath_StartsInBuildingFootprint(v30 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET, targetBuildingIndex) )
    {
      approachTrack = (const void *)Building_GenerateApproachTrack(
                            g_SelectedUnitIndex,
                            targetBuildingIndex,
                            ownBuildingTileYOffset,
                            v30,
                            tileX);
      if ( approachTrack )
      {
        qmemcpy((void *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), approachTrack, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        WorldMap_RedrawViewport(1);
      }
      if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) != 1 )
        return;
LABEL_138:
      UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v30, (DWORD)approachTrack, a1);
      WorldMap_RefreshUnitStatusPanel((DWORD)approachTrack);
      return;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
LABEL_205:
    Audio_PlayUnitMoveOrderSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
    UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v30, tileX, a1);
    WorldMap_RefreshUnitStatusPanel(tileX);
    return;
  }
  if ( MapTile_HasOwnUnitStack(tileX, tileY) )
  {
    if ( DD_IsLost((int)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "own_stack",
        tileX,
        tileY,
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    if ( g_WorldMapJoinUnitsModeActive && *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) != g_SelectedUnitIndex )
    {
      Render_Begin((int)&g_RenderState, 0, v28);
      Unit_AddToGroup(g_SelectedUnitIndex, *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)), 0, tileX, a1);
      g_WorldMapJoinUnitsModeActive = 0;
      WorldMap_RefreshActionButtonBarState(v59);
      WorldMap_RefreshUnitStatusPanel(tileX);
      UnitStackSelection_SyncForCurrentSelection(v60, tileX);
      WorldMap_RedrawViewport(1);
    }
    else
    {
      v51 = gameData;
      v52 = g_SelectedUnitIndex;
      if ( *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)) == g_SelectedUnitIndex
        && (v52 = 145 * g_SelectedUnitIndex, *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490)) )
      {
        Render_Begin((int)&g_RenderState, 0, v28);
        if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
        {
          v61 = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
          Audio_PlayUnitMoveOrderSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, v62, v51, v61, a1);
          WorldMap_RefreshUnitStatusPanel(v61);
        }
      }
      else
      {
        tileStackPtr = TILE_INDEX(tileX, tileY);
        v54 = g_SelectedUnitIndex;
        if ( *(unsigned __int16 *)tileStackPtr != g_SelectedUnitIndex )
        {
          g_LastSelectedUnitIndex = g_SelectedUnitIndex;
          g_SelectedUnitIndex = *(unsigned __int16 *)tileStackPtr;
          Diagnostics_TraceWorldMapActionEvent(
            "selected_stack_changed",
            g_SelectedUnitIndex,
            tileX,
            tileY,
            g_LastSelectedUnitIndex);
          UnitStackSelection_ClearMask((void *)v52);
          WorldMap_RefreshActionButtonBarState(v55);
          WorldMap_RedrawViewport(1);
          prevSelectedIndex = g_LastSelectedUnitIndex;
          if ( g_LastSelectedUnitIndex != -1 )
            WorldMap_RedrawTileIfVisible(
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_LastSelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_LastSelectedUnitIndex + 147176));
          WorldMap_RefreshUnitStatusPanel(prevSelectedIndex);
          UnitStackSelection_SyncForCurrentSelection(v57, prevSelectedIndex);
          Audio_PlayUnitActivateSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          Render_Begin((int)&g_RenderState, 0, v54);
        }
      }
    }
    return;
  }
  if ( g_SelectedUnitIndex != -1 && MapTile_HasVisibleEnemyUnitStack(tileX, tileY) )
  {
    if ( DD_IsLost((int)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "enemy_stack",
        tileX,
        tileY,
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    Render_Begin((int)&g_RenderState, 0, v28);
    Diagnostics_TraceWorldMapActionEvent(
      "enemy_attack_call",
      g_SelectedUnitIndex,
      *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)),
      tileX,
      tileY);
    Unit_Attack(g_SelectedUnitIndex, *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)), v27, tileX, a1);
    Diagnostics_TraceWorldMapActionEvent(
      "enemy_attack_return",
      g_SelectedUnitIndex,
      *(unsigned __int16 *)(TILE_INDEX(tileX, tileY)),
      tileX,
      tileY);
    Diagnostics_TraceWorldMapUnitSnapshot("after_enemy_attack");
    return;
  }
  if ( !MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) && g_SelectedUnitIndex != -1 )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      Diagnostics_TraceWorldMapClickEvent(
        "empty_tile_with_selection",
        tileX,
        tileY,
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490)
      || (stackPosPacked = *(_DWORD *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + 320), (unsigned __int8)stackPosPacked != tileX)
      || (LOBYTE(v30) = tileY, BYTE1(stackPosPacked) != tileY) )
    {
      unitTileY = *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176);
      bridge_crossings_enabled = UnitStack_HasBuilder(g_SelectedUnitIndex);
      if ( bridge_crossings_enabled )
      {
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_enable_move", g_SelectedUnitIndex, tileX, tileY, 0);
        Pathing_EnableBridgeCrossings(g_SelectedUnitIndex, (char)tileY, 0);
      }
      moveTrack = (const void *)Unit_MoveTrack(
                            g_SelectedUnitIndex,
                            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
                            tileX,
                            unitTileY,
                            tileX,
                            tileY);
      if ( bridge_crossings_enabled )
      {
        Pathing_DisableBridgeCrossings(g_SelectedUnitIndex, (char)(uintptr_t)moveTrack, 0);
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_disable_move", g_SelectedUnitIndex, tileX, tileY, moveTrack != 0);
      }
      selectedStackByteOffset = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "move_order_track_result",
          g_SelectedUnitIndex,
          tileX,
          tileY,
          moveTrack ? *(_DWORD *)moveTrack : -1);
      if ( moveTrack )
      {
        selectedStackRecord = selectedStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET;
        qmemcpy((void *)(selectedStackRecord + 316), moveTrack, UNIT_STACK_PATH_BYTES);
        v28 = selectedStackRecord - 48;
        j__nfree_();
      }
      else
      {
        *(_DWORD *)(gameData + selectedStackByteOffset + 147490) = 0;
      }
      if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) == 1 )
      {
        if ( UnitStackSelection_HasSelectedSlots() )
        {
          *(_DWORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) = 0;
          WorldMap_RedrawViewport(1);
        }
        else
        {
          if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, unitTileY, selectedStackByteOffset, a1);
          WorldMap_RefreshUnitStatusPanel(selectedStackByteOffset);
          WorldMap_RedrawViewport(1);
        }
      }
      else
      {
        Render_Begin((int)&g_RenderState, 0, v28);
        WorldMap_RedrawViewport(1);
      }
      return;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
    goto LABEL_205;
  }
}
// 408698: variable 'v6' is possibly undefined
// 4087D2: variable 'v10' is possibly undefined
// 408845: variable 'v3' is possibly undefined
// 408845: variable 'v2' is possibly undefined
// 4088E4: variable 'v11' is possibly undefined
// 408B2B: variable 'v4' is possibly undefined
// 408CF5: variable 'v16' is possibly undefined
// 408E41: variable 'v25' is possibly undefined
// 408E62: variable 'v21' is possibly undefined
// 408E83: variable 'v22' is possibly undefined
// 408EA4: variable 'v23' is possibly undefined
// 408EC5: variable 'v24' is possibly undefined
// 408EF9: variable 'v26' is possibly undefined
// 4090F6: variable 'v31' is possibly undefined
// 409156: variable 'v34' is possibly undefined
// 409493: variable 'v41' is possibly undefined
// 40959E: variable 'v49' is possibly undefined
// 409779: variable 'v50' is possibly undefined
// 409859: variable 'v55' is possibly undefined
// 4098AC: variable 'v57' is possibly undefined
// 40990B: variable 'v58' is possibly undefined
// 40992A: variable 'v59' is possibly undefined
// 409934: variable 'v60' is possibly undefined
// 4099A8: variable 'v62' is possibly undefined
// 409B51: variable 'v67' is possibly undefined
// 511130: using guessed type char byte_511130;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 511B68: using guessed type char *off_511B68[21];
// 511B74: using guessed type char *off_511B74[18];
// 511B80: using guessed type char *off_511B80[15];
// 511B8C: using guessed type char *off_511B8C[12];
// 511B98: using guessed type char *g_CastleFoundationTexts[9];
// 511BA4: using guessed type char *off_511BA4[6];
// 5202A4: using guessed type int dword_5202A4;
// 5202A8: using guessed type int dword_5202A8;
// 5202AC: using guessed type int dword_5202AC;
// 5202B0: using guessed type int dword_5202B0;
// 5202B4: using guessed type int dword_5202B4;
// 5202E4: using guessed type int gameData;
// 5202E8: using guessed type int dword_5202E8;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00409CC0) --------------------------------------------------------
int  WorldMap_ShowQuitConfirmDialog(int a1, char a2, DWORD a3)
{
  int result; // eax

  result = YesNoWindow((int)g_Text_QuitConfirm[(unsigned __int8)g_LanguageIndex], 0, a1, a2, a3);
  g_WorldMapTurnLoopExitFlag = result;
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 511B48: using guessed type char *g_Text_QuitConfirm[3];
// 5202F8: using guessed type int dword_5202F8;

//----- (00409CE0) --------------------------------------------------------
int  WorldMap_HandleSaveGameAction(char a1, DWORD a2, double a3)
{
  SaveSlotDialog_Run(1, a1, a2, a3);
  UnitStackSelection_RefreshForSelectedStack(a2);
  return WorldMap_RedrawViewport(1);
}

//----- (00409D00) --------------------------------------------------------
int  WorldMap_HandleLoadGameAction(DWORD a1, char a2, double a3)
{
  int result; // eax

  result = SaveSlotDialog_Run(0, a2, a1, a3);
  g_PendingLoadGameSlotIndex = result;
  if ( result == -1 )
  {
    WorldMap_RedrawViewport(1);
    return UnitStackSelection_RefreshForSelectedStack(a1);
  }
  else
  {
    g_WorldMapTurnLoopExitFlag = 1;
  }
  return result;
}
// 511B64: using guessed type int dword_511B64;
// 5202F8: using guessed type int dword_5202F8;

//----- (00409D30) --------------------------------------------------------
int  WorldMap_HandleSurrenderAction(int a1, char a2, DWORD a3, double a4)
{
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int surrenderConfirmTexts[6]; // [esp+0h] [ebp-18h]

  surrenderConfirmTexts[0] = (int)g_Text_SurrenderConfirm[0];
  surrenderConfirmTexts[1] = (int)g_Text_SurrenderConfirm[1];
  surrenderConfirmTexts[2] = (int)g_Text_SurrenderConfirm[2];
  result = YesNoWindow(surrenderConfirmTexts[(unsigned __int8)g_LanguageIndex], 0, a1, a2, a3);
  if ( result )
  {
    result = Player_Surrender(g_CurrentPlayerIndex, v5, a3, a4);
    g_AdvanceToNextPlayerFlag = v6;
  }
  return result;
}
// 409D66: variable 'v5' is possibly undefined
// 409D6B: variable 'v6' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511BB0: using guessed type char *g_Text_SurrenderConfirm[3];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202FC: using guessed type int dword_5202FC;

//----- (00409D80) --------------------------------------------------------
int  WorldMap_HandleDeselectUnitAction(uintptr_t widget, DWORD a2)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_2);
    return Render_Begin((int)g_RenderState, 0);
  }
  else
  {
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(widget, 49));
    g_LastSelectedUnitIndex = g_SelectedUnitIndex;
    g_SelectedUnitIndex = -1;
    UnitStackSelection_SyncForCurrentSelection(NULL, a2);
    WorldMap_RefreshActionButtonBarState(NULL);
    g_SavedCursorDescriptor = (int)&g_CursorDesc_Default;
    return WorldMap_RedrawViewport(1);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 526A34: using guessed type int dword_526A34;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00409DF0) --------------------------------------------------------
void  WorldMap_SelectNextActiveUnitStack(uintptr_t widget, int a2, DWORD statusPanelContext)
{
  int scan_index; // edx
  int found; // ebx
  int checked_count; // ecx
  int unit_record; // eax

  Diagnostics_TraceWorldMapActionEvent("next_unit_enter", g_SelectedUnitIndex, g_LastSelectedUnitIndex, g_CurrentPlayerIndex, 0);
  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  if ( g_SelectedUnitIndex == -1 )
  {
    if ( g_LastSelectedUnitIndex == -1 )
      scan_index = 0;
    else
      scan_index = g_LastSelectedUnitIndex;
  }
  else
  {
    scan_index = g_SelectedUnitIndex + 1;
  }
  scan_index %= 500;
  found = 0;
  checked_count = 0;
  do
  {
    unit_record = UNIT_STACK_STRIDE * scan_index + gameData;
    if ( *(__int16 *)(unit_record + 147180) != -1
      && *(unsigned __int8 *)(unit_record + 147178) == g_CurrentPlayerIndex
      && Unit_AttemptNeighborMove(scan_index) )
    {
      found = 1;
    }
    else
    {
      scan_index = (scan_index + 1) % 500;
    }
    ++checked_count;
  }
  while ( checked_count < 500 && !found );
  Diagnostics_TraceWorldMapActionEvent("next_unit_scan_done", g_SelectedUnitIndex, scan_index, found, checked_count);
  if ( found )
  {
    g_LastSelectedUnitIndex = g_SelectedUnitIndex;
    g_SelectedUnitIndex = scan_index;
    UnitStackSelection_ClearMask(NULL);
    WorldMap_RefreshActionButtonBarState(NULL);
    Camera_CenterOnUnit(scan_index);
    Audio_PlayUnitActivateSound(*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
    WorldMap_RedrawViewport(1);
    WorldMap_RefreshUnitStatusPanel(statusPanelContext);
    UnitStackSelection_SyncForCurrentSelection(NULL, statusPanelContext);
    Diagnostics_TraceWorldMapActionEvent(
      "next_unit_selected",
      g_SelectedUnitIndex,
      *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
      *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
      Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex));
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00409F00) --------------------------------------------------------
int  WorldMap_CenterViewOnNextOwnedBuildingWithUnit(int widget, int a2)
{
  int i; // ecx
  int buildingRecord; // eax
  void *v5; // ecx

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  g_UnitSearchCursor = (g_UnitSearchCursor + 1) % 100;
  for ( i = 0; i < 100; ++i )
  {
    if ( (unsigned int)g_UnitSearchCursor <= 0x64 )
    {
      buildingRecord = UNIT_RECORD(g_UnitSearchCursor);
      if ( (unsigned int)*(char *)(buildingRecord + 4) < 4
        && *(__int16 *)(buildingRecord + 16) != -1
        && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * g_UnitSearchCursor + 509676) == g_CurrentPlayerIndex )
      {
        break;
      }
    }
    g_UnitSearchCursor = (g_UnitSearchCursor + 1) % 100;
  }
  UI_CenterWorldMapViewportOnTile(
    *(unsigned __int8 *)(UNIT_RECORD(g_UnitSearchCursor)),
    *(unsigned __int8 *)(BUILDING_RECORD_SIZE * g_UnitSearchCursor + gameData + 509675));
  g_SelectedUnitIndex = -1;
  WorldMap_RefreshActionButtonBarState(v5);
  return WorldMap_RedrawViewport(1);
}
// 409F38: simplified comparisons for '$g_UnitSearchCursor.4': <0 || >=65 became >=65u
// 409F59: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 409FE2: variable 'v5' is possibly undefined
// 511B54: using guessed type int g_UnitSearchCursor;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A000) --------------------------------------------------------
int  WorldMap_HandleHideUnitAction(int widget, int a2, unsigned __int16 a3, DWORD a4, double a5)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_3);
    return Render_Begin((int)g_RenderState, 0);
  }
  else
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
    return UnitStack_TryHide(g_SelectedUnitIndex, a3, a4, a5);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A040) --------------------------------------------------------
char *WorldMap_ToggleSelectedUnitModeFlag()
{
  int v1; // ecx
  char *result; // eax
  int v3; // ecx

  Render_Begin((int)g_RenderState, 0);
  if ( g_SelectedUnitIndex == -1 )
    return Audio_PlayButtonSound(aWrong_4);
  result = Audio_PlayButtonSound(*(char **)(v1 + 49));
  if ( g_WorldMapJoinUnitsModeActive )
  {
    g_WorldMapJoinUnitsModeActive = 0;
    *(_DWORD *)(v3 + 8) = 1;
  }
  else
  {
    g_WorldMapJoinUnitsModeActive = 1;
    *(_DWORD *)(v3 + 8) = 2;
  }
  return result;
}
// 40A059: variable 'v1' is possibly undefined
// 40A073: variable 'v3' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E8: using guessed type int dword_5202E8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A0A0) --------------------------------------------------------
int  WorldMap_ComputeBuildMenuActionFromCursor(int widget, int a2)
{
  int v3; // edx
  int result; // eax

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  result = (*(_DWORD *)(v3 + 16) - 15) / 2;
  g_WorldMapBuilderMenuAction = result;
  return result;
}
// 40A0A8: variable 'v3' is possibly undefined
// 520308: using guessed type int dword_520308;

static void WorldMap_EnsureActionButtonWidgetTable(void);

//----- (0040A0E0) --------------------------------------------------------
int  WorldMap_HandleBuilderActionMenu(int widget, int delayTicks, int a3, DWORD a4, double st7_0)
{
  int v6; // ecx
  int v7; // ecx
  int v9; // ecx
  int noBuilderTexts[7]; // [esp+0h] [ebp-1Ch] BYREF

  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_5);
    return Render_Begin((int)g_RenderState, 0);
  }
  else
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
    if ( UnitStack_HasBuilder(g_SelectedUnitIndex) )
    {
      UIWidgetTable_InitDrawStates(g_UI_YesNoDims);
      WorldMap_RedrawViewport(1);
      g_WorldMapBuilderMenuAction = v6;
      while ( 1 )
      {
        DD_Pump((int)g_RenderState, a3);
        WorldMap_RedrawFrame(a3);
        if ( UI_TrySelectFriendlyStackUnderCursor() || !UIWidgetTable_PollHoverAndActions(g_UI_YesNoDims, 0x40u) && DD_IsFlipping((int)g_RenderState) )
          break;
        a3 = g_WorldMapBuilderMenuAction;
        if ( g_WorldMapBuilderMenuAction == -1 )
          goto LABEL_13;
        switch ( g_WorldMapBuilderMenuAction )
        {
          case 0:
            Builder_StartRoadBuildMode(0x40u, st7_0);
            break;
          case 1:
            Treasure_TryDigHere(g_SelectedUnitIndex, g_WorldMapBuilderMenuAction, 0x40u, (char)g_RenderState, 0, st7_0);
            break;
          case 2:
            BuildBuilding(3, v7, g_WorldMapBuilderMenuAction, st7_0);
            break;
          case 3:
            if ( UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
            {
              a3 = g_SelectedUnitIndex;
              if ( Building_New(0, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type0, 0) )
              {
                MiniMap_DrawTileCell(
                  (void *)*(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET),
                  *(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176));
                Audio_PlaySoundEffectByName(aStruktur, 64);
              }
            }
            break;
          case 4:
            if ( !UnitStack_HasPeasantCargo(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
            {
              a3 = g_SelectedUnitIndex;
              if ( Building_New(1, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type1, 0) )
                Audio_PlaySoundEffectByName(aStruktur_0, 64);
            }
            break;
          case 5:
            a3 = g_SelectedUnitIndex;
            if ( Building_New(2, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type2, 0) )
              Audio_PlaySoundEffectByName(aStruktur_1, 64);
            break;
          default:
            break;
        }
        if ( !DD_IsFlipping((int)g_RenderState) )
        {
LABEL_13:
          if ( g_WorldMapBuilderMenuAction != -1 )
            break;
        }
        else
        {
          g_WorldMapBuilderMenuAction = -1;
        }
      }
      g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
      WorldMap_EnsureActionButtonWidgetTable();
      UIWidgetTable_InitDrawStates(g_WorldMapActionButtonWidgetTable);
      WorldMap_SyncSelectionForHumanPlayer(0x40u);
      WorldMap_RedrawViewport(1);
      WorldMap_RefreshUnitStatusPanel(0x40u);
      return UnitStackSelection_RefreshForSelectedStack(0x40u);
    }
    else
    {
      Audio_PlayButtonSound(aWrong_6);
      noBuilderTexts[0] = (int)g_Text_NoBuilder[0];
      noBuilderTexts[1] = (int)g_Text_NoBuilder[1];
      noBuilderTexts[2] = (int)g_Text_NoBuilder[2];
      return UI_ShowInfoWindow(
               noBuilderTexts[(unsigned __int8)g_LanguageIndex],
               1u,
               v9,
               a4,
               (int)&noBuilderTexts[3],
               (int)&g_Text_NoBuilder[3]);
    }
  }
}
// 40A126: variable 'v6' is possibly undefined
// 40A182: variable 'a5' is possibly undefined
// 40A1DF: variable 'v9' is possibly undefined
// 40A24E: variable 'v7' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511BC0: using guessed type int g_UI_YesNoDims[3];
// 511D34: using guessed type char *g_Text_NoBuilder[3];
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 520308: using guessed type int dword_520308;
// 544CD8: using guessed type _DWORD g_RenderState[9];

static void WorldMap_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *polish_label,
        const char *english_label,
        const char *german_label,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_ActionButtonSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = 14;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)polish_label;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)english_label;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)german_label;
  record[48] = 1;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

static int WorldMap_DeferBuildingActionCallback(uintptr_t widget)
{
  /* The authentic sub_40A0E0 callback still reopens the unresolved building-placement link surface. */
  (void)widget;
  return 0;
}

static void WorldMap_EnsureActionButtonWidgetTable(void)
{
  static const char action_sound[] = "male";
  static const char label_map_mode_pl[] = "Tryb mapy";
  static const char label_map_mode_en[] = "Map mode";
  static const char label_map_mode_de[] = "Kartenmodus";
  static const char label_next_unit_pl[] = "Nast\x91" "pna jednostka";
  static const char label_next_unit_en[] = "Next unit";
  static const char label_next_unit_de[] = "N\x84" "chste Einheit";
  static const char label_next_building_pl[] = "Nast\x91" "pna budowla";
  static const char label_next_building_en[] = "Next building";
  static const char label_next_building_de[] = "N\x84" "chstes Geb\x84" "ude";
  static const char label_join_units_pl[] = "\x9C\x86" "czenie oddzia\x92\xA2" "w";
  static const char label_join_units_en[] = "Join units";
  static const char label_join_units_de[] = "Einheiten verbinden";
  static const char label_building_pl[] = "Budowanie";
  static const char label_building_en[] = "Building";
  static const char label_building_de[] = "Geb\x84" "ude";
  static const char label_ambush_pl[] = "Zasadzka";
  static const char label_ambush_en[] = "Ambush";
  static const char label_ambush_de[] = "Hinterhalt";
  int map_mode_flags;
  int join_units_flags;

  if ( g_WorldMapActionWidgetsInitialized )
    return;
  map_mode_flags = g_WorldMapMapModeWidgetFlags ? g_WorldMapMapModeWidgetFlags : 1;
  join_units_flags = g_WorldMapJoinUnitsWidgetFlags ? g_WorldMapJoinUnitsWidgetFlags : 1;
  memset(g_WorldMapActionButtonWidgetTable, 0, sizeof(g_WorldMapActionButtonWidgetTable));
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    416,
    400,
    map_mode_flags,
    0,
    1,
    (int)(uintptr_t)&WorldMap_HandleDeselectUnitAction,
    label_map_mode_pl,
    label_map_mode_en,
    label_map_mode_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    480,
    400,
    1,
    2,
    3,
    (int)(uintptr_t)&WorldMap_SelectNextActiveUnitStack,
    label_next_unit_pl,
    label_next_unit_en,
    label_next_unit_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    544,
    400,
    1,
    4,
    5,
    (int)(uintptr_t)&WorldMap_CenterViewOnNextOwnedBuildingWithUnit,
    label_next_building_pl,
    label_next_building_en,
    label_next_building_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    416,
    432,
    join_units_flags,
    6,
    7,
    (int)(uintptr_t)&WorldMap_ToggleSelectedUnitModeFlag,
    label_join_units_pl,
    label_join_units_en,
    label_join_units_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    480,
    432,
    1,
    8,
    9,
    (int)(uintptr_t)&WorldMap_DeferBuildingActionCallback,
    label_building_pl,
    label_building_en,
    label_building_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    544,
    432,
    1,
    10,
    11,
    (int)(uintptr_t)&WorldMap_HandleHideUnitAction,
    label_ambush_pl,
    label_ambush_en,
    label_ambush_de,
    action_sound);
  *(_DWORD *)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * WORLD_MAP_ACTION_WIDGET_COUNT) = -1;
  g_WorldMapActionWidgetsInitialized = 1;
}

static void UnitBattle_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        int overlay_sprite_index,
        int action_callback,
        const char *polish_label,
        const char *english_label,
        const char *german_label,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BattleButtonsSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = overlay_sprite_index;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)polish_label;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)english_label;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)german_label;
  record[48] = 1;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

static int UnitBattle_IsActionButtonWidgetAddress(uintptr_t widget)
{
  return widget >= (uintptr_t)g_UnitBattleActionWidgetTable
      && widget < (uintptr_t)(g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * UNIT_BATTLE_ACTION_WIDGET_COUNT);
}

static void UnitBattle_EnsureActionButtonWidgetTable(void)
{
  static int initialized;
  static const char action_sound[] = "male";
  static const char label_shoot_pl[] = "Ostrzal";
  static const char label_shoot_en[] = "Shooting";
  static const char label_shoot_de[] = "Schiesen";
  static const char label_next_pl[] = "Nastepna jednostka";
  static const char label_next_en[] = "Next unit";
  static const char label_next_de[] = "Nachste Einheit";
  static const char label_charge_pl[] = "Szarza";
  static const char label_charge_en[] = "Ride";
  static const char label_charge_de[] = "Reiten";
  static const char label_defence_pl[] = "Okopanie sie";
  static const char label_defence_en[] = "Prepare to defence";
  static const char label_defence_de[] = "Verteidigung vorbereiten";
  static const char label_retreat_pl[] = "Odwrot z pola bitwy";
  static const char label_retreat_en[] = "Retreat from the battlefield";
  static const char label_retreat_de[] = "Ruckzug vom Schlachtfeld";
  int shoot_flags;
  int charge_flags;
  int retreat_flags;
  int exit_overlay_sprite;

  if ( initialized )
    return;
  shoot_flags = g_UnitBattleShootButtonState ? g_UnitBattleShootButtonState : 1;
  charge_flags = g_UnitBattleChargeButtonState ? g_UnitBattleChargeButtonState : 1;
  retreat_flags = g_UnitBattleExitButtonState ? g_UnitBattleExitButtonState : 1;
  exit_overlay_sprite = g_UnitBattleExitButtonOverlaySpriteIndex ? g_UnitBattleExitButtonOverlaySpriteIndex : 13;
  memset(g_UnitBattleActionWidgetTable, 0, sizeof(g_UnitBattleActionWidgetTable));
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    498,
    370,
    shoot_flags,
    7,
    8,
    0,
    (int)(uintptr_t)&UnitBattle_ToggleSelectedShootingMode,
    label_shoot_pl,
    label_shoot_en,
    label_shoot_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    561,
    370,
    1,
    1,
    2,
    0,
    (int)(uintptr_t)&UnitBattle_SelectNextControllableUnit,
    label_next_pl,
    label_next_en,
    label_next_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    498,
    401,
    charge_flags,
    3,
    4,
    0,
    (int)(uintptr_t)&UnitBattle_ToggleSelectedChargeMode,
    label_charge_pl,
    label_charge_en,
    label_charge_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    498,
    432,
    1,
    5,
    6,
    0,
    (int)(uintptr_t)&UnitBattle_HandlePrepareDefenceAction,
    label_defence_pl,
    label_defence_en,
    label_defence_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    561,
    401,
    1,
    9,
    10,
    11,
    (int)(uintptr_t)&UnitBattle_HandleRetreatAction,
    label_retreat_pl,
    label_retreat_en,
    label_retreat_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    505,
    0,
    retreat_flags,
    12,
    12,
    exit_overlay_sprite,
    (int)(uintptr_t)&UnitBattle_RequestActionLoopExit,
    0,
    0,
    0,
    action_sound);
  *(_DWORD *)(g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * UNIT_BATTLE_ACTION_WIDGET_COUNT) = -1;
  initialized = 1;
}

//----- (0040A360) --------------------------------------------------------
int __thiscall WorldMap_RefreshActionButtonBarState(void *this)
{
  (void)this;

  WorldMap_EnsureActionButtonWidgetTable();
  if ( g_SelectedUnitIndex == -1 )
  {
    g_WorldMapMapModeWidgetFlags = 1;
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
    g_WorldMapJoinUnitsModeActive = 0;
    g_WorldMapJoinUnitsWidgetFlags = 1;
  }
  else
  {
    g_WorldMapMapModeWidgetFlags = 2;
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
    if ( g_WorldMapJoinUnitsModeActive )
    {
      g_WorldMapJoinUnitsWidgetFlags = 2;
      goto LABEL_4;
    }
  }
  g_WorldMapJoinUnitsWidgetFlags = 1;
LABEL_4:
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidget_RefreshActionButtonState((uintptr_t)g_WorldMapActionButtonWidgetTable, 1);
  return UIWidget_RefreshActionButtonState((uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3), 1);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511D48: using guessed type int dword_511D48;
// 511DE7: using guessed type int dword_511DE7;
// 5202E0: using guessed type int dword_5202E0;
// 5202E8: using guessed type int dword_5202E8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A400) --------------------------------------------------------
int  WorldMap_LoadActionButtonSprites(int a1, char a2, DWORD a3)
{
  _DWORD *spriteSet; // eax
  int v5; // ecx

  spriteSet = (_DWORD *)Mem_Alloc(4112, a1, a2, a3);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, "map_butt.s32");
  g_ActionButtonSpriteSet = (int)spriteSet;
  WorldMap_EnsureActionButtonWidgetTable();
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_WorldMapActionButtonWidgetTable);
  WorldMap_RedrawViewport(1);
  return v5;
}
// 40A431: variable 'v5' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 52030C: using guessed type int dword_52030C;

//----- (0040A450) --------------------------------------------------------
int __fastcall WorldMap_UnloadActionButtonSprites(int a1, int a2)
{
  DLXSpriteSet_ReleaseAndClear(&g_ActionButtonSpriteSet);
  return a2;
}
// 52030C: using guessed type int dword_52030C;

//----- (0040A460) --------------------------------------------------------
int  WorldMap_PollActionButtonWidgets(DWORD a1)
{
  int v1; // edx
  signed int widget_result;

  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  WorldMap_EnsureActionButtonWidgetTable();
  widget_result = UIWidgetTable_PollHoverAndActions(g_WorldMapActionButtonWidgetTable, a1);
  Diagnostics_TraceWorldMapActionEvent(
    "action_widgets_after_poll",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    widget_result);
  if ( widget_result == 1 )
    WorldMap_RefreshUnitStatusPanel(a1);
  Diagnostics_TraceWorldMapActionEvent(
    "action_widgets_after_refresh",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    widget_result);
  return v1;
}
// 40A479: variable 'v1' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;

//----- (0040A490) --------------------------------------------------------
void  WorldMap_SyncSelectionForHumanPlayer(DWORD a1)
{
  void *gameDataPtr; // ecx

  gameDataPtr = (void *)gameData;
  if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
  {
    if ( g_SelectedUnitIndex == -1 || *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180) == -1 )
    {
      g_SelectedUnitIndex = -1;
      WorldMap_RefreshActionButtonBarState((void *)gameData);
    }
    UnitStackSelection_SyncForCurrentSelection(gameDataPtr, a1);
  }
}
// 40A4ED: variable 'v1' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A500) --------------------------------------------------------
void  UnitStackSelection_SyncForCurrentSelection(void *a1, DWORD a2)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    if ( g_UnitStackSelectionActiveUnitIndex == -1 )
      return;
LABEL_4:
    UnitStackSelection_End(a1);
    return;
  }
  if ( Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) == 1 && g_UnitStackSelectionActiveUnitIndex != -1 )
    goto LABEL_4;
  if ( Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) > 1 && g_UnitStackSelectionActiveUnitIndex == -1 )
  {
    UnitStackSelection_BeginForSelectedStack(a2);
  }
  else if ( g_UnitStackSelectionActiveUnitIndex != g_SelectedUnitIndex && Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) > 1 )
  {
    UnitStackSelection_RefreshForSelectedStack(a2);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 5202E4: using guessed type int gameData;

//----- (0040A600) --------------------------------------------------------
void * WorldMap_DrawTurnBannerReveal(int animate)
{
  int SpriteForChar; // eax
  int aiSpriteForChar; // eax
  void *renderDevice; // edi
  DWORD renderSurfaceHandle; // ebp
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int startTime; // edi
  unsigned __int16 SpriteWidth; // ax
  int v12; // ecx
  __int16 bannerSpriteWidth; // ax
  __int16 v14; // cx
  __int16 SpriteHeight; // ax
  __int16 bannerSpriteHeight; // ax
  void *result; // eax
  unsigned __int16 revealRightEdge; // [esp+2Ch] [ebp-28h]
  unsigned __int16 bannerSpriteRight; // [esp+2Ch] [ebp-28h]
  unsigned __int16 revealLeftEdge; // [esp+34h] [ebp-20h]
  void *savedRenderDevice; // [esp+38h] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_WorldMapTurnBannerSpriteSet, g_CurrentPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(416, 400, SpriteForChar, 0);
  aiSpriteForChar = DLX_GetSpriteForChar(g_WorldMapTurnBannerSpriteSet, PLAYER_AI_INTELLIGENCE(g_CurrentPlayerIndex) + 5);
  renderDevice = g_RenderDevice;
  renderSurfaceHandle = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(568, 404, aiSpriteForChar, 1);
  Render_ReleaseSurface(7, renderSurfaceHandle);
  UI_DrawTextFmt((int)renderDevice, 416, 608, 436, 3, PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_DISPLAY_NAME_OFFSET);
  if ( *(_DWORD *)(gameData + 147155) )
  {
    TextSprite_ActivateResourceSlot(3, 76, renderSurfaceHandle);
    UI_DrawText(421, 405, (int)aTuraD);
  }
  startTime = Time_Now(0, 0);
  if ( animate )
  {
    while ( 1 )
    {
      int elapsed = Time_Now(0, 0) - startTime;
      SpriteWidth = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0);
      if ( elapsed >= SpriteWidth )
        break;
      bannerSpriteWidth = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0);
      revealLeftEdge = bannerSpriteWidth + 400 - elapsed;
      revealRightEdge = elapsed + 400;
      SpriteHeight = DLX_GetSpriteHeight(g_WorldMapTurnBannerSpriteSet, 0);
      Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 400, 416, SpriteHeight + 416, revealRightEdge, 0x1A0u, revealLeftEdge);
    }
  }
  bannerSpriteRight = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0) + 399;
  bannerSpriteHeight = DLX_GetSpriteHeight(g_WorldMapTurnBannerSpriteSet, 0);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 400, 416, bannerSpriteHeight + 416, bannerSpriteRight, 0x1A0u, 0x190u);
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 40A7B1: conditional instruction was optimized away because esi.4!=0
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202DC: using guessed type int dword_5202DC;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A820) --------------------------------------------------------
int  WorldMap_RenderPlayerTurnIntroScreen(char a1, DWORD a2)
{
  _DWORD *saved_primary_surface; // esi
  _DWORD *saved_map_surface; // edi
  int drawBufferRaw; // eax
  unsigned __int8 *drawBuffer; // esi
  unsigned int bannerVariant; // eax
  DWORD surfaceHandle; // ebp
  _BYTE gfxFilename[16]; // [esp+0h] [ebp-2Ch] BYREF
  int (*savedRenderHook)(); // [esp+10h] [ebp-1Ch]
  int savedResourceHandle; // [esp+14h] [ebp-18h]

  savedResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, a1, a2, (int)aSetrhS08x_1);
  // The turn banner reuses the world-map surface; preserve both pixel buffers
  // so the next map palette fade does not present stale banner pixels.
  saved_primary_surface = (_DWORD *)Mem_Alloc(188, 0, a1, a2);
  if ( saved_primary_surface )
    saved_primary_surface = Render_CreateSurface((int)saved_primary_surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  saved_map_surface = (_DWORD *)Mem_Alloc(188, 0, a1, a2);
  if ( saved_map_surface )
    saved_map_surface = Render_CreateSurface((int)saved_map_surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  if ( saved_primary_surface )
    Render_FillRect(0, saved_primary_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_map_surface )
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, saved_map_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  drawBufferRaw = Mem_Alloc(1024, 0, a1, a2);
  if ( drawBufferRaw )
    drawBufferRaw = _wcpp_4_ctor_array__(drawBufferRaw, 256);
  drawBuffer = (unsigned __int8 *)drawBufferRaw;
  bannerVariant = Rng_RandRange(1, 7);
  sprintf_(gfxFilename, "tura%d.gfx", bannerVariant);
  surfaceHandle = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    (char *)gfxFilename,
    0,
    (uintptr_t)drawBuffer);
  Render_ReleaseSurface(6, surfaceHandle);
  Render_LoadResourceSprite_v4(6, drawBuffer, 0, (char)drawBuffer, surfaceHandle);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  if ( g_LanguageIndex )
  {
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      UI_DrawTextFmt((int)drawBuffer, 0, 639, 370, 3, (int)aPlayerSYourTur, PLAYER_DATA(g_CurrentPlayerIndex) + 4);
    }
    else if ( g_LanguageIndex == 2 )
    {
      UI_DrawTextFmt((int)drawBuffer, 0, 639, 370, 3, (int)aSpielerS, PLAYER_DATA(g_CurrentPlayerIndex) + 4);
    }
  }
  else
  {
    UI_DrawTextFmt((int)drawBuffer, 0, 639, 370, 3, (int)aGraczSTwojaTur, PLAYER_DATA(g_CurrentPlayerIndex) + 4);
  }
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, drawBuffer, 20);
  while ( !DD_IsFlipping((int)g_RenderState) )
  {
    WorldMap_RunInputScriptStep();
    DD_Pump((int)g_RenderState, 20);
  }
  Render_Begin((int)g_RenderState, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  UI_EndDraw(6);
  if ( saved_map_surface )
    Render_FillRect(saved_map_surface, (_DWORD *)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_primary_surface )
    Render_FillRect(saved_primary_surface, (_DWORD *)&g_MainRenderDevice, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_map_surface )
    RenderSurface_InvokeSlot0(saved_map_surface, 2);
  if ( saved_primary_surface )
    RenderSurface_InvokeSlot0(saved_primary_surface, 2);
  j__nfree_();
  Debug_Log(0, (char)g_RenderHook, 0, (int)aUnsetrh08x_0);
  g_RenderHook = savedRenderHook;
  return Render_SetResourceHandle((int)&g_MainRenderDevice, savedResourceHandle);
}

int UI_LoadTurnBannerGfx(char a1, DWORD a2)
{
  return WorldMap_RenderPlayerTurnIntroScreen(a1, a2);
}
// 40A867: variable 'v2' is possibly undefined
// 40A883: variable 'v3' is possibly undefined
// 40A896: variable 'v5' is possibly undefined
// 40A8E7: variable 'v9' is possibly undefined
// 40AA32: variable 'v10' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AA60) --------------------------------------------------------
int  Game_AdvanceToNextPlayerTurn(int a1, char a2, DWORD loadContext, double gameTime)
{
  int previous_player_index;
  int current_player_is_human;
  int active_mission_index;
  int clips_memory;
  int used_memory;
  int unit_cache_entries;
  int building_cache_entries;

  (void)a1;
  (void)a2;

  Diagnostics_TraceWorldMapActionEvent("turn_advance_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
  Debug_Log(0, 0, loadContext, (int)aNextPlayer);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  PLAYER_CAMERA_LEFT(g_CurrentPlayerIndex) = MAP_VIEW_LEFT;
  PLAYER_CAMERA_TOP(g_CurrentPlayerIndex) = MAP_VIEW_TOP;
  previous_player_index = g_CurrentPlayerIndex;
  do
    g_CurrentPlayerIndex = (g_CurrentPlayerIndex + 1) % 5;
  while ( !PLAYER_IS_ACTIVE(g_CurrentPlayerIndex) );
  TURN_OWNER_PLAYER_INDEX = g_CurrentPlayerIndex;
  Debug_Log(0, 0, loadContext, (int)aPlayerD, g_CurrentPlayerIndex);
  current_player_is_human = PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_player_select",
    g_SelectedUnitIndex,
    previous_player_index,
    g_CurrentPlayerIndex,
    current_player_is_human);
  if ( current_player_is_human )
    VIEWED_PLAYER_INDEX = g_CurrentPlayerIndex;
  if ( previous_player_index > g_CurrentPlayerIndex )
  {
    ++GAME_TURN_COUNTER;
    Debug_Log(0, 0, loadContext, (int)aNextTurnD, GAME_TURN_COUNTER);
    Map_AutoUpgradeVillages();
    Port_NewTurn(loadContext);
    clips_memory = Mem_GetTotalAllocatedBytes();
    Debug_Log(0, 0, loadContext, (int)aClipsMemoryD, clips_memory);
    used_memory = Debug_GetUsedMemoryCount();
    Debug_Log(0, 0, loadContext, (int)aUsedmemD_3, used_memory);
    unit_cache_entries = UnitSpriteCache_CountActiveEntries();
    Debug_Log(0, 0, loadContext, (int)aUnitsCacheEntr, unit_cache_entries);
    building_cache_entries = BuildingSpriteCache_CountEntries();
    Debug_Log(0, 0, loadContext, (int)aBuildingsCache, building_cache_entries);
  }
  MAP_VIEW_LEFT = PLAYER_CAMERA_LEFT(VIEWED_PLAYER_INDEX);
  MAP_VIEW_TOP = PLAYER_CAMERA_TOP(VIEWED_PLAYER_INDEX);
  Render_Pump();
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_render_pump",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  if ( current_player_is_human )
  {
    UI_LoadTurnBannerGfx((char)g_CurrentPlayerIndex, loadContext);
    g_SelectedUnitIndex = -1;
    Locale_DrawInteger();
    WorldMap_RenderHook(loadContext);
    Diagnostics_TraceWorldMapActionEvent(
      "turn_advance_after_human_banner",
      g_SelectedUnitIndex,
      g_CurrentPlayerIndex,
      current_player_is_human,
      GAME_TURN_COUNTER);
  }
  g_SelectedUnitIndex = -1;
  g_LastSelectedUnitIndex = -1;
  if ( current_player_is_human )
    WorldMap_RefreshActionButtonBarState((void *)(uintptr_t)(unsigned int)gameData);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_selection_reset",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  UnitStackSelection_SyncForCurrentSelection((void *)(uintptr_t)(unsigned int)gameData, 0xFFFFFFFF);
  WorldMap_RedrawViewport(1);
  if ( !current_player_is_human )
  {
    WorldMap_DrawTurnBannerReveal(1);
    Tooltip_RestoreBackdrop();
  }
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_side_ui",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  active_mission_index = ACTIVE_MISSION_INDEX;
  if ( !current_player_is_human )
  {
    if ( active_mission_index == -1 || active_mission_index == 19 || active_mission_index == 9 )
      AI_ComputeNationStrengthPercent(g_CurrentPlayerIndex, 0, 0xFFFFFFFF, gameTime);
  }
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_before_unit_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Debug_Log(0, 0, 0xFFFFFFFF, (int)aAutoMovesBegin);
  Unit_NewTurn(0, (char)active_mission_index, 0xFFFFFFFF, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_unit_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Building_NewTurn(0, (unsigned __int8 *)(uintptr_t)(unsigned int)active_mission_index, 0xFFFFFFFF, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_building_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Prisoner_SetInCastles(0, (char)active_mission_index, 0xFFFFFFFF);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_prisoners",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Queen_NewTurn(0, active_mission_index, current_player_is_human != 0, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_queen",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Debug_Log(0, 0, 0xFFFFFFFF, (int)aAutoMovesEnd);
  WorldMap_RedrawViewport(1);
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_before_present",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  return Render_Present((int)g_RenderState);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AD40) --------------------------------------------------------
int * WorldMap_RenderHook(DWORD a1)
{
  int v1; // ecx
  void *v2; // ecx
  int *result; // eax

  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  Render_DrawSprite();
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  WorldMap_EnsureActionButtonWidgetTable();
  if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    UIWidgetTable_InitDrawStates(g_WorldMapActionButtonWidgetTable);
  else
    WorldMap_DrawTurnBannerReveal(0);
  WorldMap_RedrawViewport(1);
  UI_EndDraw(7);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  WorldMap_RefreshUnitStatusPanel(a1);
  UnitStackSelection_SyncForCurrentSelection(v2, a1);
  result = Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  return result;
}
// 40ADAD: variable 'v1' is possibly undefined
// 40ADB7: variable 'v2' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;

//----- (0040ADF0) --------------------------------------------------------
int  WorldMap_RedrawFrame(int a1, ...)
{
  int previous_resource_handle; // ecx
  int mission_index; // edx

  DD_Pump((int)g_RenderState, 0);
  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  Map_UpdateIdleAnimatedUnits();
  WorldMap_TickAmbientMapAnimations(a1);
  Map_UpdateConstructionSiteSwayAnimation(0);
  Map_UpdateIdleAnimatedBuildings(0);
  UI_UpdateTileBlinkFlash(0, 0);
  Noop_WorldMapFrameRedrawHook();
  mission_index = ACTIVE_MISSION_INDEX;
  if ( mission_index == 1 )
  {
    WorldMap_RedrawTileIfVisible(16, 11);
    return Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  }
  if ( mission_index != 11 )
    return Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  WorldMap_RedrawTileIfVisible(2, 44);
  return Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
}
// 419030: using guessed type int nullsub_1(void);
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AE80) --------------------------------------------------------
int  WorldMap_RedrawFrameForAIWhenEnabled(int a1)
{
  int result; // eax

  if ( !g_WorldMapFrameRedrawDisabled )
  {
    result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      return WorldMap_RedrawFrame(a1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 520310: using guessed type int dword_520310;

//----- (0040AEB0) --------------------------------------------------------
void WorldMap_DisableFrameRedraw()
{
  g_WorldMapFrameRedrawDisabled = 1;
}
// 520310: using guessed type int dword_520310;

//----- (0040AEC0) --------------------------------------------------------
void WorldMap_EnableFrameRedraw()
{
  g_WorldMapFrameRedrawDisabled = 0;
}
// 520310: using guessed type int dword_520310;

//----- (0040AED0) --------------------------------------------------------
_DWORD * WorldMap_LoadResources(char a1, DWORD loadContext)
{
  _DWORD *frameSpriteSet; // eax
  _DWORD *marksSpriteSet; // eax
  _DWORD *stepSpriteSet; // eax
  _DWORD *fogSpriteSet; // eax
  _DWORD *flagSpriteSet; // eax
  _DWORD *whirlSpriteSet; // eax
  _DWORD *turnBannerSpriteSet; // eax
  _DWORD *Surface; // eax
  int mapPalette; // eax

  TextSprite_ReleaseAllResourceSlots();
  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  frameSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( frameSpriteSet )
    frameSpriteSet = DLXSpriteSet_Load(frameSpriteSet, "frame.s32");
  g_ActiveUiSpriteSet = (int)frameSpriteSet;
  marksSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( marksSpriteSet )
    marksSpriteSet = DLXSpriteSet_Load(marksSpriteSet, "marks.s32");
  g_MarksSpriteSet = (int)marksSpriteSet;
  stepSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( stepSpriteSet )
    stepSpriteSet = DLXSpriteSet_Load(stepSpriteSet, "step.s32");
  g_MovePathStepSpriteSet = (int)stepSpriteSet;
  fogSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( fogSpriteSet )
    fogSpriteSet = DLXSpriteSet_Load(fogSpriteSet, "fog.s32");
  g_FogOverlaySpriteSet = (int)fogSpriteSet;
  flagSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( flagSpriteSet )
    flagSpriteSet = DLXSpriteSet_Load(flagSpriteSet, "flag.s32");
  g_FlagSpriteSet = (int)flagSpriteSet;
  whirlSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( whirlSpriteSet )
    whirlSpriteSet = DLXSpriteSet_Load(whirlSpriteSet, "whirl.s32");
  g_WhirlSpriteSet = (int)whirlSpriteSet;
  turnBannerSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( turnBannerSpriteSet )
    turnBannerSpriteSet = DLXSpriteSet_Load(turnBannerSpriteSet, "turakomp.s32");
  g_WorldMapTurnBannerSpriteSet = (int)turnBannerSpriteSet;
  if ( !g_PrimaryRenderSurface )
  {
    Surface = (_DWORD *)Mem_Alloc(188, 0, 0, 0);
    if ( Surface )
      Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_PrimaryRenderSurface = (int)Surface;
  }
  mapPalette = Mem_Alloc(1024, 0, 0, 0);
  if ( mapPalette )
    mapPalette = Palette_LoadFromQueryHandle(mapPalette, (intptr_t)"map.pal");
  g_MapPalettePtr = mapPalette;
  Palette_LoadOrBuildBlendLookupTable(aMainmap, mapPalette, 0, loadContext);
  RenderState_LoadDefaultCursorSprite((int)g_RenderState);
  return WorldMapTopMenu_LoadSpriteSet();
}
// 5202BC: using guessed type int dword_5202BC;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202DC: using guessed type int dword_5202DC;
// 5202E0: using guessed type int dword_5202E0;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040B020) --------------------------------------------------------
int  WorldMap_UnloadResources(DWORD allocContext)
{
  int v2; // ecx

  TextSprite_ReleaseAllResourceSlots();
  UnitSpriteCache_FreeAllEntries(v2, allocContext);
  BuildingSpriteCache_Clear();
  CSS_EmptySampleCache();
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_MarksSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_MovePathStepSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_FogOverlaySpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_TreeSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_FlagSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_WhirlSpriteSet);
  UI_FreeCurrentPlayerInfoSpriteSet();
  DLXSpriteSet_ReleaseAndClear(&g_WorldMapTurnBannerSpriteSet);
  j__nfree_();
  return WorldMapTopMenu_FreeSpriteSet();
}
// 40B027: variable 'v2' is possibly undefined
// 5202BC: using guessed type int dword_5202BC;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202D8: using guessed type int dword_5202D8;
// 5202DC: using guessed type int dword_5202DC;
// 5202F4: using guessed type int dword_5202F4;

static void WorldMap_RunInputScriptStep(void)
{
  static int initialized;
  static int trace_checked;
  static int trace_enabled;
  static int wait_reads;
  static FILE *script_file;
  char line[256];
  const char *script_path;

  if ( !trace_checked )
  {
    const char *trace_value = getenv("CLASH95_TRACE_WORLD_INPUT_SCRIPT");
    trace_enabled = trace_value && *trace_value;
    trace_checked = 1;
  }
  if ( !initialized )
  {
    initialized = 1;
    script_path = getenv("CLASH95_WORLD_INPUT_SCRIPT");
    if ( script_path && *script_path )
    {
      script_file = fopen(script_path, "r");
      if ( trace_enabled )
        fprintf(stderr, "[world_input] open path=%s ok=%d\n", script_path, script_file != NULL);
    }
  }
  if ( wait_reads > 0 )
  {
    if ( trace_enabled )
      fprintf(
        stderr,
        "[world_input] wait remaining=%d cursor=%d,%d selected=%d mask0=%d panel=%d\n",
        wait_reads,
        g_MouseCursorRawX >> g_CursorCoordShift,
        g_MouseCursorRawY >> g_CursorCoordShift,
        g_SelectedUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSelectionActiveUnitIndex);
    --wait_reads;
    return;
  }
  while ( script_file && fgets(line, sizeof(line), script_file) )
  {
    char command[32];
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int fields;
    int cursor_x;
    int cursor_y;

    fields = sscanf(line, " %31s %d %d %d %d %d", command, &a, &b, &c, &d, &e);
    if ( fields <= 0 || command[0] == '#' )
      continue;
    if ( strcmp(command, "wait") == 0 )
    {
      if ( fields >= 2 && a > 0 )
        wait_reads = a - 1;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=wait reads=%d cursor=%d,%d\n", a, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
      return;
    }
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( strcmp(command, "move") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=move target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "down") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=down target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 1, 0);
      return;
    }
    if ( strcmp(command, "up") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=up target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "click") == 0 && fields >= 3 )
    {
      int reads = fields >= 4 && c > 0 ? c : 2;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=click target=%d,%d cursor=%d,%d delta=%d,%d reads=%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y, reads);
      Platform_DebugPrimeInputFallbackMousePulse(a - cursor_x, b - cursor_y, 1, 0, reads);
      return;
    }
    if ( strcmp(command, "key") == 0 && fields >= 2 )
    {
      int reads = fields >= 3 && b > 0 ? b : 2;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=key scan=%d reads=%d cursor=%d,%d\n", a, reads, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackKeyPulse(a, reads);
      return;
    }
    if ( strcmp(command, "delta") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=delta delta=%d,%d buttons=%d,%d cursor=%d,%d\n", a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0);
      return;
    }
    if ( strcmp(command, "pulse") == 0 && fields >= 6 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=pulse delta=%d,%d buttons=%d,%d reads=%d cursor=%d,%d\n", a, b, c, d, e, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMousePulse(a, b, c, d, e);
      return;
    }
  }
  if ( script_file && feof(script_file) )
    clearerr(script_file);
}

static int g_BattleInputScriptInitialized;
static int g_BattleInputScriptTraceChecked;
static int g_BattleInputScriptTraceEnabled;
static int g_BattleInputScriptWaitReads;
static FILE *g_BattleInputScriptFile;

static void Battle_ResetInputScriptReader(void)
{
  if ( g_BattleInputScriptFile )
  {
    fclose(g_BattleInputScriptFile);
    g_BattleInputScriptFile = NULL;
  }
  g_BattleInputScriptInitialized = 0;
  g_BattleInputScriptWaitReads = 0;
}

static void Battle_RunInputScriptStep(void)
{
  char line[256];
  const char *script_path;

  if ( !g_BattleInputScriptTraceChecked )
  {
    const char *trace_value = getenv("CLASH95_TRACE_BATTLE_INPUT_SCRIPT");
    g_BattleInputScriptTraceEnabled = trace_value && *trace_value;
    g_BattleInputScriptTraceChecked = 1;
  }
  if ( !g_BattleInputScriptInitialized )
  {
    g_BattleInputScriptInitialized = 1;
    script_path = getenv("CLASH95_BATTLE_INPUT_SCRIPT");
    if ( script_path && *script_path )
    {
      g_BattleInputScriptFile = fopen(script_path, "r");
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] open path=%s ok=%d\n", script_path, g_BattleInputScriptFile != NULL);
    }
  }
  if ( g_BattleInputScriptWaitReads > 0 )
  {
    if ( g_BattleInputScriptTraceEnabled )
      fprintf(
        stderr,
        "[battle_input] wait remaining=%d cursor=%d,%d selected=%d\n",
        g_BattleInputScriptWaitReads,
        g_MouseCursorRawX >> g_CursorCoordShift,
        g_MouseCursorRawY >> g_CursorCoordShift,
        g_SelectedUnitIndex);
    --g_BattleInputScriptWaitReads;
    return;
  }
  while ( g_BattleInputScriptFile && fgets(line, sizeof(line), g_BattleInputScriptFile) )
  {
    char command[32];
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int fields;
    int cursor_x;
    int cursor_y;

    fields = sscanf(line, " %31s %d %d %d %d %d", command, &a, &b, &c, &d, &e);
    if ( fields <= 0 || command[0] == '#' )
      continue;
    if ( strcmp(command, "wait") == 0 )
    {
      if ( fields >= 2 && a > 0 )
        g_BattleInputScriptWaitReads = a - 1;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=wait reads=%d cursor=%d,%d\n", a, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
      return;
    }
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( strcmp(command, "move") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=move target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "down") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=down target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 1, 0);
      return;
    }
    if ( strcmp(command, "up") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=up target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "click") == 0 && fields >= 3 )
    {
      int reads = fields >= 4 && c > 0 ? c : 2;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=click target=%d,%d cursor=%d,%d delta=%d,%d reads=%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y, reads);
      Platform_DebugPrimeInputFallbackMousePulse(a - cursor_x, b - cursor_y, 1, 0, reads);
      return;
    }
    if ( strcmp(command, "key") == 0 && fields >= 2 )
    {
      int reads = fields >= 3 && b > 0 ? b : 2;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=key scan=%d reads=%d cursor=%d,%d\n", a, reads, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackKeyPulse(a, reads);
      return;
    }
    if ( strcmp(command, "delta") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=delta delta=%d,%d buttons=%d,%d cursor=%d,%d\n", a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0);
      return;
    }
    if ( strcmp(command, "pulse") == 0 && fields >= 6 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=pulse delta=%d,%d buttons=%d,%d reads=%d cursor=%d,%d\n", a, b, c, d, e, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMousePulse(a, b, c, d, e);
      return;
    }
  }
  if ( g_BattleInputScriptFile && feof(g_BattleInputScriptFile) )
    clearerr(g_BattleInputScriptFile);
}

//----- (0040B0A0) --------------------------------------------------------
void  WorldMap_RunHumanTurnLoop(
        int entry_resource_handle,
        int ( *entry_render_hook)(int a1, char a2, DWORD a3),
        DWORD runtime_context,
        double st0_runtime)
{
  int selected_stack_record;
  unsigned char new_facing;
  int *queued_path;
  signed int available_action_points;
  unsigned __int16 required_action_points;
  int last_path_step;
  int saved_resource_handle;
  int (*saved_render_hook)();

  Diagnostics_TraceWorldMapActionEvent("human_turn_before_plague_notices", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  WorldMap_NotifyPlagueOutbreak(entry_resource_handle, (const char *)entry_render_hook, runtime_context);
  Diagnostics_TraceWorldMapActionEvent("human_turn_after_plague_notices", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  Diagnostics_TraceWorldMapActionEvent("human_turn_before_color_notice", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  UI_ShowTechnologyLevelUpIfChanged(0, runtime_context);
  g_CursorDesc_Default[5] = 0;
  g_CursorDesc_Default[6] = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)(unsigned int)g_RenderState, 0, 640, 0, 480);
  Diagnostics_TraceWorldMapActionEvent("human_turn_cursor_restored", g_SelectedUnitIndex, g_ActiveCursorDescriptorPtr, g_ActiveCursorDescriptor, 0);
  {
    _DWORD *render_state = (_DWORD *)(uintptr_t)(unsigned int)g_RenderState;
    Diagnostics_TraceWorldMapActionEvent(
      "human_turn_cursor_bounds",
      g_SelectedUnitIndex,
      render_state[4] >> render_state[277],
      render_state[5] >> render_state[277],
      g_CursorDesc_Default[6]);
  }
  Diagnostics_TraceWorldMapActionEvent("human_turn_after_color_notice", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  g_AdvanceToNextPlayerFlag = 0;
  g_WorldMapTurnLoopExitFlag = 0;
  Diagnostics_TraceWorldMapUnitSnapshot("human_turn_enter");
  do
  {
    UI_ReadCheatString(0);
    WorldMap_RunInputScriptStep();
    DD_Pump((int)g_RenderState, 0);
    WorldMap_TickPaletteFlashEffect(0, 0, 0);
    WorldMap_RedrawFrame(0);
    MiniMap_UpdateViewportFromCursor();
    if ( !WorldMap_HandleTopMenuBar(0, 0) )
    {
      Diagnostics_TraceWorldMapActionEvent("human_turn_break_top_menu", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
      break;
    }
    if ( !UnitStackSelection_HandleInput(0, st0_runtime) )
      WorldMap_HandleTileHoverAndClick(st0_runtime);
    if ( !g_WorldMap_KeyboardInputDisabled )
    {
      if ( !Input_IsKeyPressed(56) )
      {
        if ( Input_IsKeyPressed(34) )
        {
          if ( !*(_DWORD *)(gameData + 147151) )
          {
            *(_DWORD *)(gameData + 147151) = 1;
            goto LABEL_24;
          }
        }
        else if ( *(_DWORD *)(gameData + 147151) )
        {
          *(_DWORD *)(gameData + 147151) = 0;
LABEL_24:
          WorldMap_RedrawViewport(1);
        }
      }
      if ( Input_IsKeyPressed(56) )
      {
        if ( Input_IsKeyPressed(205) && g_SelectedUnitIndex != -1 )
        {
          selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
          new_facing = UNIT_STACK_FACING(selected_stack_record) + 1;
          UNIT_STACK_FACING(selected_stack_record) = new_facing & 7;
          Map_RedrawUnitNeighborhoodByIndex(g_SelectedUnitIndex);
          while ( Input_IsKeyPressed(205) )
            DD_Pump((int)g_RenderState, 0);
        }
        if ( Input_IsKeyPressed(203) )
        {
          if ( g_SelectedUnitIndex != -1 )
          {
            selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
            new_facing = UNIT_STACK_FACING(selected_stack_record) - 1;
            UNIT_STACK_FACING(selected_stack_record) = new_facing & 7;
            Map_RedrawUnitNeighborhoodByIndex(g_SelectedUnitIndex);
            while ( Input_IsKeyPressed(203) )
              DD_Pump((int)g_RenderState, 0);
          }
        }
        if ( Input_IsKeyPressed(200) )
        {
          if ( g_SelectedUnitIndex != -1 )
          {
            selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
            queued_path = Unit_MoveTrack(
                    g_SelectedUnitIndex,
                    UNIT_STACK_TILE_ROW(selected_stack_record),
                    UNIT_STACK_TILE_ROW(selected_stack_record)
                      + Map_NeighborDX[2 * (unsigned __int8)UNIT_STACK_FACING(selected_stack_record)],
                    UNIT_STACK_TILE_COLUMN(selected_stack_record),
                    0,
                    UNIT_STACK_TILE_COLUMN(selected_stack_record)
                      + Map_NeighborDY[2 * (unsigned __int8)UNIT_STACK_FACING(selected_stack_record)]);
            if ( queued_path )
            {
              last_path_step = queued_path[*queued_path];
              required_action_points = HIWORD(last_path_step);
              available_action_points = UnitStack_GetMinCurrentActionPoints(selected_stack_record);
              if ( available_action_points >= required_action_points )
              {
                qmemcpy((void *)UNIT_STACK_PATH_BUFFER(selected_stack_record), queued_path, UNIT_STACK_PATH_BYTES);
                if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
                  Audio_PlayUnitMoveOrderSound(*(__int16 *)UNIT_STACK_SLOT(selected_stack_record, 0));
                UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, 0, 0, st0_runtime);
              }
              j__nfree_();
              WorldMap_RedrawViewport(1);
              WorldMap_RefreshUnitStatusPanel(0);
            }
          }
        }
      }
    }
    WorldMap_HandleScrollKeysAndIdle(0);
    Diagnostics_TraceWorldMapActionEvent(
      "selection_after_sub407d20",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    WorldMap_PollActionButtonWidgets(0);
    Diagnostics_TraceWorldMapActionEvent(
      "selection_after_action_widgets",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    if ( Input_IsKeyPressed(1) )
    {
      saved_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
      saved_render_hook = g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(saved_resource_handle, 0, 0, (int)aSetrhS08x_0);
      WorldMap_ShowQuitConfirmDialog(0, 0, 0);
      Debug_Log((int)g_RenderHook, 0, 0, (int)aUnsetrh08x);
      g_RenderHook = saved_render_hook;
      Render_SetResourceHandle((int)&g_MainRenderDevice, saved_resource_handle);
    }
    if ( Player_CheckForDefeatAndHandleElimination(g_CurrentPlayerIndex, 0) )
    {
      g_WorldMapGameLostExitFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
    }
    if ( ACTIVE_MISSION_INDEX != -1 && Mission_CheckFailureCondition() )
    {
      g_WorldMapGameLostExitFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
      Video_PlayAviWithModeGuard((int)aArama1, aKon_por1);
      return;
    }
    if ( !PLAYER_IS_ACTIVE(g_CurrentPlayerIndex) )
    {
      Diagnostics_TraceWorldMapActionEvent("human_turn_player_inactive", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
      g_AdvanceToNextPlayerFlag = 1;
    }
    if ( ACTIVE_MISSION_INDEX == -1 )
    {
      if ( UI_CheckEndTurnHotkey(g_CurrentPlayerIndex) )
      {
        g_TurnEndedByCompletionFlag = 1;
        g_WorldMapTurnLoopExitFlag = 1;
        return;
      }
    }
    else if ( Mission_CheckObjectiveComplete(0, st0_runtime) )
    {
      Diagnostics_TraceWorldMapActionEvent("mission_objective_complete", g_SelectedUnitIndex, ACTIVE_MISSION_INDEX, g_CurrentPlayerIndex, 0);
      g_TurnEndedByCompletionFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
      return;
    }
  }
  while ( !g_WorldMapTurnLoopExitFlag && !g_AdvanceToNextPlayerFlag );
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F8: using guessed type int dword_5202F8;
// 5202FC: using guessed type int dword_5202FC;
// 520300: using guessed type int dword_520300;
// 520304: using guessed type int dword_520304;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545140: using guessed type int dword_545140;

//----- (0040B640) --------------------------------------------------------
unsigned int  WorldMap_Initialize(char a1, DWORD loadContext)
{
  WorldMap_LoadResources(a1, loadContext);
  Map_InitTerrainMoveTableOffsets();
  UnitSpriteCache_ClearAllEntries();
  BuildingSpriteCache_Reset();
  return Map_InitBuildingSwayJitterOffsets(0);
}

//----- (0040B660) --------------------------------------------------------
int  PlayGame(int a1, char a2, DWORD allocContext, char a4, double st0_runtime, ...)
{
  int player_index;
  _DWORD *background_sprite_set;
  _DWORD *tree_sprite_set;
  int previous_resource_handle;
  int (*previous_render_hook)(int, char, DWORD);
  int active_mission_index;
  const char *background_resource_name;
  const char *tree_resource_name;

  (void)a1;
  (void)a2;

  g_MissionDefeatVideoPlayedGuard = 0;
  Debug_Log(0, 0, allocContext, (int)aPlaygame);
  Noop_PlayGameSessionBoundaryHook(0);
  for ( player_index = 0; player_index < 5; ++player_index )
  {
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(player_index) )
      Map_RevealAllTilesForPlayer(player_index);
  }
  background_resource_name = 0;
  tree_resource_name = 0;
  if ( MAP_THEME_INDEX == MAP_THEME_A )
  {
    background_resource_name = "backgr1.s32";
    tree_resource_name = "treemas1.s32";
  }
  else if ( MAP_THEME_INDEX == MAP_THEME_B )
  {
    background_resource_name = "backgr2.s32";
    tree_resource_name = "treemas2.s32";
  }
  else if ( MAP_THEME_INDEX == MAP_THEME_C )
  {
    background_resource_name = "backgr3.s32";
    tree_resource_name = "treemas3.s32";
  }
  if ( background_resource_name )
  {
    if ( g_WorldMapBackgroundSpriteSet )
      DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
    background_sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, allocContext);
    if ( background_sprite_set )
      background_sprite_set = DLXSpriteSet_Load(background_sprite_set, background_resource_name);
    g_WorldMapBackgroundSpriteSet = (int)background_sprite_set;
    tree_sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, allocContext);
    if ( tree_sprite_set )
      tree_sprite_set = DLXSpriteSet_Load(tree_sprite_set, tree_resource_name);
    g_TreeSpriteSet = (int)tree_sprite_set;
  }
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  g_SelectedUnitIndex = -1;
  Locale_DrawInteger();
  UI_SetActiveWidgetTable(8);
  *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(gameData + VIEWED_PLAYER_INDEX_OFFSET) + gameData + 140039);
  *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(gameData + VIEWED_PLAYER_INDEX_OFFSET) + gameData + 140043);
  Locale_DrawInteger();
  Music_PlayMainMapTrack(MAP_THEME_INDEX, 0, 7, allocContext);
  Render_DrawSprite();
  WorldMap_RedrawViewport(1);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  WorldMap_LoadActionButtonSprites(0, 0, allocContext);
  g_CursorDesc_Default[5] = 0;
  g_CursorDesc_Default[6] = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)(unsigned int)g_RenderState, 0, 640, 0, 480);
  {
    _DWORD *render_state = (_DWORD *)(uintptr_t)(unsigned int)g_RenderState;
    Diagnostics_TraceWorldMapActionEvent(
      "playgame_cursor_bounds_restored",
      g_SelectedUnitIndex,
      render_state[4] >> render_state[277],
      render_state[5] >> render_state[277],
      g_CursorDesc_Default[6]);
  }
  UnitStackSelection_SyncForCurrentSelection((void *)(uintptr_t)(unsigned int)gameData, allocContext);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  Render_Present((int)g_RenderState);
  WorldMap_RedrawViewport(1);
  Debug_Log(0, 20, allocContext, (int)aStart);
  LogAllUnits(0, 20, allocContext);
  LogAllBuildings(0, 20, allocContext);
  if ( ACTIVE_MISSION_INDEX != -1 && GAME_TURN_COUNTER == 1 && !getenv("CLASH95_SKIP_MISSION_STATUS_PANEL") )
    UI_ShowMissionStatusPanel(0, allocContext);
  g_WorldMapGameLostExitFlag = 0;
  g_TurnEndedByCompletionFlag = 0;
  g_AdvanceToNextPlayerFlag = 0;
  g_WorldMapTurnLoopExitFlag = 0;
  g_PendingLoadGameSlotIndex = -1;
  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  previous_render_hook = (int (*)(int, char, DWORD))g_RenderHook;
  g_RenderHook = (int (*)())WorldMap_RenderHook;
  Debug_Log(previous_resource_handle, 0, allocContext, (int)aSetrhS08x, "RedrawMainMap", WorldMap_RenderHook);
  while ( 1 )
  {
    Diagnostics_TraceWorldMapActionEvent("playgame_loop_top", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    UI_LoadCurrentPlayerInfoSpriteSet(g_CurrentPlayerIndex, 0, 0, allocContext);
    Diagnostics_TraceWorldMapActionEvent("playgame_after_player_info", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex));
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    {
      Diagnostics_TraceWorldMapActionEvent("playgame_before_human_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
      WorldMap_RunHumanTurnLoop(previous_resource_handle, previous_render_hook, allocContext, st0_runtime);
      Diagnostics_TraceWorldMapActionEvent("playgame_after_human_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, g_WorldMapTurnLoopExitFlag);
    }
    else if ( GAME_TURN_COUNTER )
    {
      Diagnostics_TraceWorldMapActionEvent("playgame_before_ai_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
      Debug_Log(0, 0, allocContext, (int)aComputerplay);
      Rules_ExecuteAITurn();
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
      Diagnostics_TraceWorldMapActionEvent("playgame_after_ai_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, g_WorldMapTurnLoopExitFlag);
    }
    if ( g_WorldMapTurnLoopExitFlag )
      break;
    Diagnostics_TraceWorldMapActionEvent("advance_turn_call", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    Game_AdvanceToNextPlayerTurn(0, 0, allocContext, st0_runtime);
    Diagnostics_TraceWorldMapActionEvent("advance_turn_return", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    Diagnostics_TraceWorldMapUnitSnapshot("after_turn_advance");
  }
  Render_Pump();
  Debug_Log(0, 0, allocContext, (int)aUnsetrh08x_1, g_RenderHook);
  g_RenderHook = (int (*)())previous_render_hook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, allocContext, (int)aKoniecGryPoDTu, GAME_TURN_COUNTER);
  LogAllUnits(0, 20, allocContext);
  LogAllBuildings(0, 20, allocContext);
  Audio_StopMainMusic();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  MiniMap_DestroySurface(0);
  WorldMap_UnloadActionButtonSprites(0, 0);
  WorldMap_UnloadResources(allocContext);
  Tooltip_ReleaseBackdropSurface();
  Rules_ShowBanner_StrategicClash();
  Mem_PurgeFreeListsForSpace(-1, 0, 0);
  Debug_Log(0, 0, allocContext, (int)aPlaygameEnd);
  Noop_PlayGameSessionBoundaryHook(0);
  if ( g_PendingLoadGameSlotIndex != -1 )
  {
    WorldMap_Initialize(0, allocContext);
    SaveSlot_LoadGame(g_PendingLoadGameSlotIndex, allocContext, st0_runtime);
    PlayGame(0, 0, allocContext, a4, st0_runtime);
    return 0;
  }
  active_mission_index = ACTIVE_MISSION_INDEX;
  Diagnostics_TraceWorldMapActionEvent(
    "mission_playgame_return",
    g_SelectedUnitIndex,
    active_mission_index,
    g_TurnEndedByCompletionFlag,
    g_CurrentPlayerIndex);
  if ( active_mission_index == -1 || !g_TurnEndedByCompletionFlag )
    return 0;
  if ( active_mission_index == 9 || active_mission_index == 19 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      active_mission_index == 9 ? "campaign_first_victory_branch" : "campaign_second_victory_branch",
      g_SelectedUnitIndex,
      active_mission_index,
      g_CurrentPlayerIndex,
      0);
    Video_PlayAviWithModeGuard(-1, aZwy02);
    return 0;
  }
  Diagnostics_TraceWorldMapActionEvent(
    "mission_auto_advance",
    g_SelectedUnitIndex,
    active_mission_index,
    active_mission_index + 1,
    g_CurrentPlayerIndex);
  Scenario_LoadMissionByIndexAndPlay((char *)(uintptr_t)(unsigned int)(active_mission_index + 1), -1, allocContext, st0_runtime);
  return 0;
}
// 4476A0: using guessed type int __thiscall nullsub_3(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B64: using guessed type int dword_511B64;
// 519808: using guessed type int dword_519808;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202C0: using guessed type int dword_5202C0;
// 5202D8: using guessed type int dword_5202D8;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 5202F8: using guessed type int dword_5202F8;
// 5202FC: using guessed type int dword_5202FC;
// 520300: using guessed type int dword_520300;
// 520304: using guessed type int dword_520304;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;
// 5452E8: using guessed type int dword_5452E8;

TextSpriteResourceSlotRecord *TextSprite_GetResourceSlot(int slot_index)
{
  if ( slot_index < 0 || slot_index >= TEXT_SPRITE_RESOURCE_SLOT_COUNT )
    return 0;
  return &g_TextSpriteResourceSlots[slot_index];
}

static TextSpriteResourceSlotRecord *TextSprite_GetActiveResourceSlot(void)
{
  return TextSprite_GetResourceSlot(g_ActiveTextSpriteSlot);
}

//----- (0040BAE0) --------------------------------------------------------
int  Render_ReleaseSurface(int slotIndex, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  _DWORD *sprite_set;
  int result; // eax

  slot = TextSprite_GetResourceSlot(slotIndex);
  g_ActiveTextSpriteSlot = slotIndex;
  if ( !slot )
    return 0;
  sprite_set = (_DWORD *)(uintptr_t)(unsigned int)slot->cached_sprite_set;
  if ( !sprite_set )
  {
    sprite_set = (_DWORD *)Mem_Alloc(4112, slotIndex, 0, allocContext);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, slot->source_stem);
    slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
  }
  result = 12 * slotIndex;
  g_TextSpriteLastActivatedSlotIndex = slotIndex;
  return result;
}
// 520724: using guessed type int dword_520724;
// 520728: using guessed type int dword_520728;

//----- (0040BB60) --------------------------------------------------------
char  TextSprite_ActivateResourceSlot(int slotIndex, char styleFlag, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  _DWORD *sprite_set;
  char result; // al

  slot = TextSprite_GetResourceSlot(slotIndex);
  g_ActiveTextSpriteSlot = slotIndex;
  if ( !slot )
    return styleFlag;
  sprite_set = (_DWORD *)(uintptr_t)(unsigned int)slot->cached_sprite_set;
  if ( !sprite_set )
  {
    sprite_set = (_DWORD *)Mem_Alloc(4112, slotIndex, 0, allocContext);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, slot->source_stem);
    slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
  }
  result = styleFlag;
  g_TextSpriteLastActivatedSlotIndex = slotIndex;
  g_TextSprite_StyleFlag = styleFlag;
  return result;
}
// 51F28C: using guessed type char byte_51F28C;
// 520724: using guessed type int dword_520724;
// 520728: using guessed type int dword_520728;

//----- (0040BBF0) --------------------------------------------------------
char  TextSprite_SetStyleFlag(char result)
{
  g_TextSprite_StyleFlag = result;
  return result;
}
// 51F28C: using guessed type char byte_51F28C;

//----- (0040BC00) --------------------------------------------------------
int  TextSprite_DrawGlyphAndAdvance(int penX, int penY, unsigned __int8 charCode)
{
  TextSpriteResourceSlotRecord *slot;
  unsigned __int16 sprite_index;
  int sprite_for_char;

  slot = TextSprite_GetActiveResourceSlot();
  if ( !slot || !slot->cached_sprite_set )
    return penX;
  sprite_index = (unsigned __int16)(charCode - 32);
  sprite_for_char = DLX_GetSpriteForChar(slot->cached_sprite_set, sprite_index);
  Compat_RenderDeviceDrawMenuSprite((unsigned __int16)penX, (unsigned __int16)penY, sprite_for_char, 1);
  DLX_GetSpriteWidth(slot->cached_sprite_set, sprite_index);
  return penX + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, sprite_index) + slot->glyph_spacing_word;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520724: using guessed type int dword_520724;

//----- (0040BC90) --------------------------------------------------------
int  TextSprite_DrawStringWithOrientation(int penX, int penY, char vertical, unsigned __int8 *text)
{
  TextSpriteResourceSlotRecord *slot;
  int lineStep; // edx
  unsigned __int8 glyph; // bl

  slot = TextSprite_GetActiveResourceSlot();
  if ( vertical == 1 )
  {
    while ( *text )
    {
      TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, *text);
      LOWORD(lineStep) = slot ? slot->line_step_word : 0;
      ++text;
      penY += lineStep;
    }
  }
  else
  {
    while ( *text )
    {
      glyph = *text++;
      penX = TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, glyph);
    }
  }
  return penX;
}
// 40BCD2: variable 'v7' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BD40) --------------------------------------------------------
int  TextSprite_MeasureStringExtent(_BYTE *text)
{
  TextSpriteResourceSlotRecord *slot;
  _BYTE *cursor; // ecx
  int extent; // ebx
  unsigned __int16 glyphSpacing; // si

  slot = TextSprite_GetActiveResourceSlot();
  cursor = text;
  extent = 0;
  if ( !slot || !slot->cached_sprite_set || !*text )
    return extent;
  do
  {
    while ( *cursor == 10 )
    {
      if ( !*++cursor )
        return extent;
    }
    glyphSpacing = slot->glyph_spacing_word;
    extent += glyphSpacing + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, (unsigned __int8)*cursor - 32);
  }
  while ( *cursor );
  return extent;
}
// 40BD4E: variable 'v1' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BDA0) --------------------------------------------------------
_BYTE * TextSprite_FindWordWrapBreak(_BYTE *text, int maxWidth)
{
  TextSpriteResourceSlotRecord *slot;
  _BYTE *cursor; // ecx
  _BYTE *lastSpaceBreak; // ebp
  int accumWidth; // ebx
  unsigned __int16 glyphSpacing; // si

  slot = TextSprite_GetActiveResourceSlot();
  cursor = text;
  lastSpaceBreak = text;
  accumWidth = 0;
  if ( !slot || !slot->cached_sprite_set || !*text )
    return 0;
  while ( 1 )
  {
    if ( *cursor == 10 )
      return cursor;
    if ( *cursor == 32 )
      lastSpaceBreak = cursor;
    glyphSpacing = slot->glyph_spacing_word;
    accumWidth += glyphSpacing + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, (unsigned __int8)*cursor - 32);
    if ( accumWidth > maxWidth )
      break;
    if ( !*cursor )
      return 0;
  }
  return lastSpaceBreak;
}
// 40BDB6: variable 'v2' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BE20) --------------------------------------------------------
int  Str_CountSpaces(char *text)
{
  int spaceCount; // edx
  char ch; // bl

  spaceCount = 0;
  while ( *text )
  {
    ch = *text++;
    if ( ch == 32 )
      ++spaceCount;
  }
  return spaceCount;
}

//----- (0040BE50) --------------------------------------------------------
int __cdecl UI_DrawText(int penX, int penY, int format, ...)
{
  unsigned __int8 *text;
  va_list args;

  if ( !format )
    g_UiDrawTextBuffer[0] = 0;
  else
  {
    va_start(args, format);
    vsnprintf((char *)g_UiDrawTextBuffer, sizeof(g_UiDrawTextBuffer), (const char *)(uintptr_t)(unsigned int)format, args);
    va_end(args);
  }
  text = g_UiDrawTextBuffer;
  while ( *text )
    penX = (unsigned __int16)TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, *text++);
  return penX;
}
// 520320: using guessed type unsigned __int8 byte_520320[512];

//----- (0040BEE0) --------------------------------------------------------
int  UI_RenderAlignedTextWithCursor(
        int left,
        int right,
        int alignMode,
        int y,
        int penX,
        unsigned __int8 *text)
{
  unsigned __int8 *cursor;
  unsigned __int8 *line_start;
  _BYTE *line_break;
  int text_width;
  int extra_space_width;
  int glyph_index;
  int saved_x;
  int line_step;
  int wrap_width;
  char saved_break_char;

  cursor = text;
  text_width = Render_LoadResourceSprite_v3(text);
  extra_space_width = 0;
  glyph_index = 0;

  switch ( alignMode )
  {
    case 1:
      penX = left;
      break;
    case 2:
      penX = right - text_width;
      break;
    case 3:
      penX = (right - left - text_width) / 2 + left;
      break;
    case 4:
    {
      int space_count;

      penX = left;
      space_count = Str_CountSpaces((char *)text);
      if ( space_count > 0 )
        extra_space_width = (right - left - text_width) / space_count;
      break;
    }
    case 5:
    case 6:
      wrap_width = right - left;
      line_start = text;
      while ( line_start && *line_start )
      {
        int line_width;
        unsigned __int8 *newline;

        line_width = (unsigned __int16)Render_LoadResourceSprite_v3(line_start);
        newline = line_start;
        while ( *newline && *newline != 10 )
          ++newline;
        if ( line_width <= wrap_width && !*newline )
        {
          UI_DrawTextFmt(penX, left, right, y, alignMode == 5 ? 1 : 3, (const char *)line_start);
          return penX;
        }

        line_break = TextSprite_FindWordWrapBreak(line_start, wrap_width);
        if ( !line_break )
          line_break = (_BYTE *)newline;
        if ( !line_break || !*line_break )
        {
          UI_DrawTextFmt(penX, left, right, y, alignMode == 5 ? 1 : 3, (const char *)line_start);
          return penX;
        }

        saved_break_char = *line_break;
        *line_break = 0;
        UI_DrawTextFmt(penX, left, right, y, (alignMode == 5) + 3, (const char *)line_start);
        *line_break = saved_break_char;
        line_step = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
        y += line_step;
        line_start = (unsigned __int8 *)line_break + 1;
      }
      return penX;
    default:
      break;
  }

  while ( cursor && *cursor )
  {
    unsigned __int8 glyph;

    if ( *cursor == 32 )
      penX += extra_space_width;
    saved_x = penX;
    glyph = *cursor++;
    if ( glyph != 10 )
      penX = (unsigned __int16)TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, y, glyph);
    if ( glyph_index == g_UITextCursorGlyphIndex )
      TextSprite_DrawGlyphAndAdvance(saved_x, y, 0x5Fu);
    ++glyph_index;
  }
  if ( glyph_index == g_UITextCursorGlyphIndex )
    TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, y, 0x5Fu);
  return penX;
}
// 511EC0: using guessed type int dword_511EC0;
// 520728: using guessed type int dword_520728;

//----- (0040C150) --------------------------------------------------------
int  UI_DrawTextFmt(int penX, int left, int right, int y, int alignMode, const char *format, ...)
{
  va_list args;

  if ( !format )
    g_UiDrawTextFmtBuffer[0] = 0;
  else
  {
    va_start(args, format);
    vsnprintf((char *)g_UiDrawTextFmtBuffer, sizeof(g_UiDrawTextFmtBuffer), format, args);
    va_end(args);
  }
  return UI_RenderAlignedTextWithCursor(left, right, alignMode, y, penX, g_UiDrawTextFmtBuffer);
}
// 520520: using guessed type unsigned __int8 byte_520520[516];

//----- (0040C190) --------------------------------------------------------
int  UI_DrawTextFmtV(int left, int right, int alignMode, int y, const char *format, va_list args)
{
  unsigned __int8 textBuffer[524]; // [esp+0h] [ebp-20Ch] BYREF

  if ( !format )
    textBuffer[0] = 0;
  else
    vsnprintf((char *)textBuffer, sizeof(textBuffer), format, args);
  return UI_RenderAlignedTextWithCursor(left, right, alignMode, y, y, textBuffer);
}
// 473FC3: using guessed type int __fastcall vsprintf_(_DWORD, _DWORD);

//----- (0040C1D0) --------------------------------------------------------
int  UI_GetTextXOffset(int slotIndex)
{
  TextSpriteResourceSlotRecord *slot;

  slot = TextSprite_GetResourceSlot(slotIndex);
  if ( !slot )
    return 0;
  return slot->line_step_word;
}

//----- (0040C1F0) --------------------------------------------------------
void  TextSprite_BuildOrLoadCachedFont(int slotIndex, _BYTE *fontData, int a3, char a4, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  int v6; // edx
  int existingSpriteSet; // ecx
  _BYTE *fontCursor; // eax
  unsigned __int8 *checksum; // ebx
  unsigned __int16 checksumSum; // cx
  int i; // edx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int cacheFileExists; // eax
  _DWORD *spriteSet; // eax
  _DWORD *loadedSpriteSet; // ecx
  char *destCursor; // edi
  char *srcCursor; // esi
  char firstChar; // al
  char secondChar; // al
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  _DWORD *cachedSpriteSet; // eax
  unsigned __int8 v26[1024]; // [esp+0h] [ebp-4E0h] BYREF
  CHAR cacheFilename[100]; // [esp+400h] [ebp-E0h] BYREF
  char sourceStemCopy[100]; // [esp+464h] [ebp-7Ch] BYREF
  _BYTE *fontBytes; // [esp+4C8h] [ebp-18h]

  fontBytes = fontData;
  slot = TextSprite_GetResourceSlot(slotIndex);
  Debug_Log(a3, a4, allocContext, (int)a_conformfont2p);
  if ( !slot )
    return;
  existingSpriteSet = slot->cached_sprite_set;
  if ( existingSpriteSet )
  {
    nfree_(existingSpriteSet);
    slot->cached_sprite_set = 0;
  }
  fontCursor = fontBytes;
  LOBYTE(checksum) = 0;
  checksumSum = 0;
  for ( i = 0; i < 768; ++i )
  {
    BYTE1(checksum) = *fontCursor;
    LOBYTE(checksum) = *fontCursor++ ^ (unsigned __int8)checksum;
    checksumSum += BYTE1(checksum);
  }
  sprintf_(cacheFilename, "cache\\%02x%02x%04x.s32", slotIndex, (unsigned __int8)checksum, checksumSum);
  Res_ProbeGfxFileExists(cacheFilename, v13, allocContext, v12);
  if ( cacheFileExists )
  {
    cachedSpriteSet = (_DWORD *)Mem_Alloc(4112, v14, (char)checksum, allocContext);
    if ( cachedSpriteSet )
      cachedSpriteSet = DLXSpriteSet_Load(cachedSpriteSet, (char)checksum);
    slot->cached_sprite_set = (int)(uintptr_t)cachedSpriteSet;
  }
  else
  {
    spriteSet = (_DWORD *)Mem_Alloc(4112, v14, (char)checksum, allocContext);
    loadedSpriteSet = spriteSet;
    if ( spriteSet )
      loadedSpriteSet = DLXSpriteSet_Load(spriteSet, (char)checksum);
    destCursor = sourceStemCopy;
    srcCursor = (char *)slot->source_stem;
    slot->cached_sprite_set = (int)(uintptr_t)loadedSpriteSet;
    do
    {
      firstChar = *srcCursor;
      *destCursor = *srcCursor;
      if ( !firstChar )
        break;
      secondChar = srcCursor[1];
      srcCursor += 2;
      destCursor[1] = secondChar;
      destCursor += 2;
    }
    while ( secondChar );
    checksum = v26;
    cacheFilename[strlen(sourceStemCopy) + 97] = 'p';
    Palette_LoadFromQueryHandle((int)fontBytes, 12 * slotIndex);
    DLXSpriteSet_DrawText(slot->cached_sprite_set, -1, v22, v26);
    DLXSpriteSet_Save((int *)(uintptr_t)(unsigned int)slot->cached_sprite_set, (int)cacheFilename, (char)v26);
  }
  Debug_Log(v23, (char)checksum, allocContext, (int)a_end);
}
// 40C21A: variable 'v6' is possibly undefined
// 40C364: variable 'v24' is possibly undefined
// 40C27C: variable 'v13' is possibly undefined
// 40C27C: variable 'v12' is possibly undefined
// 40C283: variable 'v15' is possibly undefined
// 40C28E: variable 'v14' is possibly undefined
// 40C32B: variable 'v22' is possibly undefined
// 40C347: variable 'v23' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 511EC8: using guessed type char *off_511EC8;
// 511ECC: using guessed type int dword_511ECC[];

//----- (0040C3A0) --------------------------------------------------------
int  UI_EndDraw(int slotIndex)
{
  TextSpriteResourceSlotRecord *slot;
  int result; // eax

  slot = TextSprite_GetResourceSlot(slotIndex);
  if ( slot && slot->cached_sprite_set )
  {
    nfree_(slot->cached_sprite_set);
    slot->cached_sprite_set = 0;
  }
  result = 3 * slotIndex;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);

//----- (0040C3F0) --------------------------------------------------------
int TextSprite_ReleaseAllResourceSlots()
{
  int slot_index;
  int result; // eax

  result = 0;
  for ( slot_index = 0; slot_index < TEXT_SPRITE_RESOURCE_SLOT_COUNT; ++slot_index )
  {
    result = UI_EndDraw(slot_index);
  }
  return result;
}

//----- (0040C430) --------------------------------------------------------
int  UI_SetTextCursorPosition(int result)
{
  g_UITextCursorGlyphIndex = result;
  return result;
}
// 511EC0: using guessed type int dword_511EC0;

//----- (0040C450) --------------------------------------------------------
char  Str_TitleCase(_BYTE *result, int a2, int a3)
{
  _BYTE *cursor; // esi

  (void)a2;
  (void)a3;
  cursor = result;
  if ( !cursor || !*cursor )
    return (char)(uintptr_t)result;
  strlwr_((char *)cursor);
  while ( cursor && *cursor )
  {
    *cursor = toupper_(*cursor);
    while ( *cursor && *cursor != ' ' )
      ++cursor;
    if ( !*cursor )
      break;
    while ( *cursor == ' ' )
      ++cursor;
  }
  return (char)(uintptr_t)result;
}
// 476253: using guessed type int __fastcall strlwr_(_DWORD, _DWORD);
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (0040C4C0) --------------------------------------------------------
_WORD * Font_ResetGlyphFallbackTable(_WORD *result)
{
  _WORD *tableEnd; // edx

  tableEnd = result + 1536;
  do
  {
    *result = -1;
    result = (_WORD *)((char *)result + 3);
    *((_BYTE *)result - 1) = 0;
  }
  while ( result != tableEnd );
  return result;
}

//----- (0040C4F0) --------------------------------------------------------
int  Font_SetGlyphFallbackEntry(int tableBase, unsigned __int16 glyphId, char flagByte, __int16 fallbackValue)
{
  int result; // eax

  result = 3 * glyphId;
  *(_WORD *)(tableBase + result) = fallbackValue;
  *(_BYTE *)(tableBase + result + 2) = flagByte;
  return result;
}

//----- (0040C510) --------------------------------------------------------
int __cdecl Font_BuildGlyphFallbackChain(int tableBase, char flagByte, unsigned __int16 firstGlyphId, ...)
{
  unsigned __int16 current_id;
  unsigned __int16 fallback_id;
  int result; // eax
  va_list args;

  result = 0;
  current_id = firstGlyphId;
  va_start(args, firstGlyphId);
  while ( 1 )
  {
    if ( current_id == 0xFFFF || current_id == 0xFFFE || *(unsigned __int16 *)(3 * (unsigned int)current_id + tableBase) != 0xFFFF )
      break;
    fallback_id = (unsigned __int16)va_arg(args, unsigned int);
    result = Font_SetGlyphFallbackEntry(tableBase, current_id, flagByte, fallback_id);
    current_id = fallback_id;
  }
  va_end(args);
  return result;
}

//----- (0040C5E0) --------------------------------------------------------
int Font_InitGlyphFallbackTablesForLanguage()
{
  unsigned int i;
  unsigned int base;
  unsigned char language;

  Font_ResetGlyphFallbackTable(&g_TerrainAnimationRemapTable);
  Font_ResetGlyphFallbackTable(&g_SpriteCodeRemapTable);
  Font_ResetGlyphFallbackTable(g_FontGlyphFallbackTable3);
  for ( i = 0; i < 0x400u; ++i )
    g_Font_GlyphRemapTable[i] = i;
  Font_BuildGlyphFallbackChain((int)&g_SpriteCodeRemapTable, 15, 0x24Bu, 0x24Cu, 0x24Du, 0x24Eu, 0x24Fu, 0x250u, 0x251u, 0x252u, 0x24Bu);
  for ( base = 0xDF; base <= 0xEA; ++base )
  {
    Font_BuildGlyphFallbackChain(
      (int)&g_SpriteCodeRemapTable,
      15,
      (unsigned __int16)base,
      (unsigned __int16)(base + 0x0C),
      (unsigned __int16)(base + 0x18),
      (unsigned __int16)(base + 0x24),
      (unsigned __int16)(base + 0x30),
      (unsigned __int16)(base + 0x3C),
      (unsigned __int16)(base + 0x48),
      (unsigned __int16)(base + 0x54),
      (unsigned __int16)(base + 0x60),
      (unsigned __int16)(base + 0x6C),
      (unsigned __int16)(base + 0x78),
      (unsigned __int16)(base + 0x84),
      (unsigned __int16)(base + 0x90),
      (unsigned __int16)(base + 0x9C),
      (unsigned __int16)(base + 0xA8),
      (unsigned __int16)(base + 0xB4),
      (unsigned __int16)base);
  }
  for ( i = 6; i <= 9; ++i )
  {
    base = 0x253 + 8 * i;
    Font_BuildGlyphFallbackChain(
      (int)&g_SpriteCodeRemapTable,
      15,
      (unsigned __int16)base,
      (unsigned __int16)(base + 1),
      (unsigned __int16)(base + 2),
      (unsigned __int16)(base + 3),
      (unsigned __int16)(base + 4),
      (unsigned __int16)(base + 5),
      (unsigned __int16)(base + 6),
      (unsigned __int16)(base + 7),
      (unsigned __int16)base);
  }

  language = *(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET);
  switch ( language )
  {
    case 0:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          15,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)(base + 0x40),
          (unsigned __int16)(base + 0x48),
          (unsigned __int16)(base + 0x50),
          (unsigned __int16)(base + 0x58),
          (unsigned __int16)(base + 0x60),
          (unsigned __int16)(base + 0x68),
          (unsigned __int16)(base + 0x70),
          (unsigned __int16)(base + 0x78),
          (unsigned __int16)base);
      }
      break;
    case 1:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          15,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)base);
      }
      break;
    case 2:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          10,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)(base + 0x40),
          (unsigned __int16)(base + 0x48),
          (unsigned __int16)(base + 0x50),
          (unsigned __int16)(base + 0x58),
          (unsigned __int16)(base + 0x60),
          (unsigned __int16)(base + 0x68),
          (unsigned __int16)(base + 0x70),
          (unsigned __int16)(base + 0x78),
          (unsigned __int16)base);
      }
      break;
    default:
      break;
  }

  for ( i = 0; i <= 5; ++i )
  {
    base = 0x253 + 8 * i;
    Font_BuildGlyphFallbackChain(
      (int)&g_TerrainAnimationRemapTable,
      10,
      (unsigned __int16)base,
      (unsigned __int16)(base + 1),
      (unsigned __int16)(base + 2),
      (unsigned __int16)(base + 3),
      (unsigned __int16)(base + 4),
      (unsigned __int16)(base + 5),
      (unsigned __int16)(base + 6),
      (unsigned __int16)(base + 7),
      (unsigned __int16)base);
  }
  if ( language == 2 )
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0xBBu, 0x2BDu, 0x2BEu, 0x2BFu, 0x2C0u, 0x2C1u, 0x2C2u, 0xBBu);
  if ( language )
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 15, 0x304u, 0x305u, 0x306u, 0x307u, 0x308u, 0x309u, 0x30Au, 0x303u, 0xFFFFu);
  else
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 5, 0x303u, 0x304u, 0x305u, 0x306u, 0x307u, 0x308u, 0x309u, 0x30Au, 0x24u, 0xFFFFu);

  if ( language == 0 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x313u, 0x314u, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x31Bu, 0x31Cu, 0x31Du, 0x31Eu, 0x31Fu, 0x320u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x321u, 0x322u, 0x323u, 0x324u, 0x325u, 0x326u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x327u, 0x328u, 0x329u, 0x32Au, 0x32Bu, 0x32Cu, 0x32Du, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x32Eu, 0x32Fu, 0x330u, 0x331u, 0x332u, 0xFFFEu);
  }
  else if ( language == 1 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0x313u, 0x314u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0x31Bu, 0x31Cu, 0x31Du, 0x31Eu, 0xFFFEu);
  }
  else if ( language == 2 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x313u, 0x314u, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0x31Bu, 0x31Cu, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x31Du, 0x31Eu, 0x31Fu, 0x320u, 0x321u, 0x322u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x323u, 0x324u, 0x325u, 0x326u, 0x327u, 0x328u, 0x329u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x32Au, 0x32Bu, 0x32Cu, 0x32Du, 0x32Eu, 0x32Fu, 0x330u, 0x331u, 0x332u, 0x333u, 0xFFFEu);
  }

  return language;
}
// 5202E4: using guessed type int gameData;
// 520738: using guessed type __int16 word_520738;
// 521338: using guessed type __int16 word_521338;
// 521F38: using guessed type _WORD word_521F38[1528];
// 522B38: using guessed type __int16 word_522B38[223];

//----- (0040CE70) --------------------------------------------------------
int  MiniMap_BuildTileColorTables(unsigned int themeIndex, int a2)
{
  unsigned char *base0;
  unsigned char *base1;
  unsigned char *base2;

  (void)a2;

  if ( themeIndex )
  {
    if ( themeIndex <= 1 )
    {
      g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTerrainColorTableVariant1;
    }
    else if ( themeIndex == 2 )
    {
      g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTerrainColorTableVariant2;
    }
  }
  else
  {
    g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTileColorTableTheme0;
  }
  base0 = (unsigned char *)g_MiniMapTileColorTableTheme0;
  base1 = (unsigned char *)g_MiniMapTerrainColorTableVariant1;
  base2 = (unsigned char *)g_MiniMapTerrainColorTableVariant2;

#define MINIMAP_FILL(base, offset, count, value) memset((base) + (offset), (value), (count))
  MINIMAP_FILL(base0, 0x000, 0x004, 0xB7);
  MINIMAP_FILL(base0, 0x004, 0x003, 0x97);
  MINIMAP_FILL(base0, 0x007, 0x001, 0x27);
  MINIMAP_FILL(base0, 0x008, 0x008, 0x97);
  MINIMAP_FILL(base0, 0x010, 0x010, 0xB7);
  MINIMAP_FILL(base0, 0x020, 0x00D, 0x97);
  MINIMAP_FILL(base0, 0x02D, 0x074, 0xB9);
  MINIMAP_FILL(base0, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base0, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base0, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base0, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base0, 0x2C3, 0x004, 0xB7);
  MINIMAP_FILL(base0, 0x2C7, 0x005, 0x97);
  MINIMAP_FILL(base0, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base0, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base0, 0x2EF, 0x003, 0xB7);
  MINIMAP_FILL(base0, 0x2F2, 0x003, 0x97);
  MINIMAP_FILL(base0, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base0, 0x303, 0x008, 0x97);

  MINIMAP_FILL(base1, 0x000, 0x004, 0x4C);
  MINIMAP_FILL(base1, 0x004, 0x003, 0x97);
  MINIMAP_FILL(base1, 0x007, 0x001, 0x27);
  MINIMAP_FILL(base1, 0x008, 0x008, 0x97);
  MINIMAP_FILL(base1, 0x010, 0x010, 0x4C);
  MINIMAP_FILL(base1, 0x020, 0x00D, 0x97);
  MINIMAP_FILL(base1, 0x02D, 0x074, 0xB9);
  MINIMAP_FILL(base1, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base1, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base1, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base1, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base1, 0x2C3, 0x004, 0x4C);
  MINIMAP_FILL(base1, 0x2C7, 0x005, 0x97);
  MINIMAP_FILL(base1, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base1, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base1, 0x2EF, 0x003, 0x4C);
  MINIMAP_FILL(base1, 0x2F2, 0x003, 0x97);
  MINIMAP_FILL(base1, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base1, 0x303, 0x008, 0x97);

  MINIMAP_FILL(base2, 0x000, 0x004, 0x7F);
  MINIMAP_FILL(base2, 0x004, 0x003, 0xC0);
  MINIMAP_FILL(base2, 0x007, 0x001, 0xC4);
  MINIMAP_FILL(base2, 0x008, 0x008, 0xC0);
  MINIMAP_FILL(base2, 0x010, 0x010, 0x7F);
  MINIMAP_FILL(base2, 0x020, 0x00D, 0xC0);
  MINIMAP_FILL(base2, 0x02D, 0x074, 0x80);
  MINIMAP_FILL(base2, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base2, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base2, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base2, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base2, 0x2C3, 0x004, 0x7F);
  MINIMAP_FILL(base2, 0x2C7, 0x005, 0xC0);
  MINIMAP_FILL(base2, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base2, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base2, 0x2EF, 0x003, 0x7F);
  MINIMAP_FILL(base2, 0x2F2, 0x003, 0xC0);
  MINIMAP_FILL(base2, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base2, 0x303, 0x008, 0xC0);
#undef MINIMAP_FILL

  return 0;
}
// 40CEAC: variable 'v2' is possibly undefined
// 40CEC0: variable 'v3' is possibly undefined
// 40CED4: variable 'v4' is possibly undefined
// 40CEE8: variable 'v5' is possibly undefined
// 40CEFC: variable 'v6' is possibly undefined
// 40CF10: variable 'v7' is possibly undefined
// 40CF24: variable 'v8' is possibly undefined
// 40CF38: variable 'v9' is possibly undefined
// 40CF4C: variable 'v10' is possibly undefined
// 40CF60: variable 'v11' is possibly undefined
// 40CF74: variable 'v12' is possibly undefined
// 40CF88: variable 'v13' is possibly undefined
// 40CF9C: variable 'v14' is possibly undefined
// 40CFB0: variable 'v15' is possibly undefined
// 40CFC4: variable 'v16' is possibly undefined
// 40CFD8: variable 'v17' is possibly undefined
// 40CFEC: variable 'v18' is possibly undefined
// 40D000: variable 'v19' is possibly undefined
// 40D014: variable 'v20' is possibly undefined
// 40D028: variable 'v21' is possibly undefined
// 40D03C: variable 'v22' is possibly undefined
// 40D050: variable 'v23' is possibly undefined
// 40D064: variable 'v24' is possibly undefined
// 40D078: variable 'v25' is possibly undefined
// 40D08C: variable 'v26' is possibly undefined
// 40D0A0: variable 'v27' is possibly undefined
// 40D0B4: variable 'v28' is possibly undefined
// 40D0C8: variable 'v29' is possibly undefined
// 40D0DC: variable 'v30' is possibly undefined
// 40D0F0: variable 'v31' is possibly undefined
// 40D104: variable 'v32' is possibly undefined
// 40D118: variable 'v33' is possibly undefined
// 40D12C: variable 'v34' is possibly undefined
// 40D140: variable 'v35' is possibly undefined
// 40D154: variable 'v36' is possibly undefined
// 40D168: variable 'v37' is possibly undefined
// 40D17C: variable 'v38' is possibly undefined
// 40D190: variable 'v39' is possibly undefined
// 40D1A4: variable 'v40' is possibly undefined
// 40D1B8: variable 'v41' is possibly undefined
// 40D1CC: variable 'v42' is possibly undefined
// 40D1E0: variable 'v43' is possibly undefined
// 40D1F4: variable 'v44' is possibly undefined
// 40D208: variable 'v45' is possibly undefined
// 40D21C: variable 'v46' is possibly undefined
// 40D230: variable 'v47' is possibly undefined
// 40D244: variable 'v48' is possibly undefined
// 40D258: variable 'v49' is possibly undefined
// 40D26C: variable 'v50' is possibly undefined
// 40D280: variable 'v51' is possibly undefined
// 40D294: variable 'v52' is possibly undefined
// 40D2A8: variable 'v53' is possibly undefined
// 40D2BC: variable 'v54' is possibly undefined
// 40D2D0: variable 'v55' is possibly undefined
// 40D2E4: variable 'v56' is possibly undefined
// 40D2F8: variable 'v57' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 523F50: using guessed type int dword_523F50;

//----- (0040D330) --------------------------------------------------------
int  MiniMap_CreateSurface(DWORD allocContext)
{
  _DWORD *Surface; // eax
  int minimap_frame_sprite; // eax

  g_MiniMapPixelsPerTile_523F54 = 2;
  if ( *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) * *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) <= 2500 )
    g_MiniMapPixelsPerTile_523F54 = 4;
  g_MiniMapRectWidth_523348 = (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_WIDTH_TILES_OFFSET) + 14;
  g_MiniMapRectHeight_52334A = *(_WORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) * (unsigned __int8)g_MiniMapPixelsPerTile_523F54 + 14;
  g_MiniMapRectTop_523346 = 16;
  g_MiniMapRectLeft_523344 = 608 - g_MiniMapRectWidth_523348;
  Surface = (_DWORD *)Mem_Alloc(188, 16, g_MiniMapRectWidth_523348, allocContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, g_MiniMapRectWidth_523348, g_MiniMapRectHeight_52334A);
  g_MiniMapSurface_52334C = (int)Surface;
  g_RenderDevice = Surface;
  minimap_frame_sprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 4);
  Compat_RenderDeviceDrawMenuSprite(0, 0, minimap_frame_sprite, 1u);
  return MiniMap_BuildTileColorTables(MAP_THEME_INDEX, 0);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202BC: using guessed type int dword_5202BC;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523348: using guessed type __int16 word_523348;
// 52334A: using guessed type __int16 word_52334A;
// 52334C: using guessed type int dword_52334C;
// 523F54: using guessed type char byte_523F54;

//----- (0040D430) --------------------------------------------------------
int __thiscall MiniMap_DestroySurface(void *this)
{
  int result; // eax

  (void)this;
  result = 0;
  if ( g_MiniMapSurface_52334C )
    Compat_InvokeCompactSurfaceDestructor(g_MiniMapSurface_52334C, 2);
  return result;
}
// 52334C: using guessed type int dword_52334C;

//----- (0040D560) --------------------------------------------------------
int  MiniMap_BlitDirtyRectAndDrawViewportBox(
        int result,
        unsigned __int16 top,
        unsigned __int16 bottom,
        unsigned __int16 right)
{
  if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX)
    && right >= (unsigned __int16)g_MiniMapRectLeft_523344
    && top <= (unsigned __int16)g_MiniMapRectTop_523346 + (unsigned __int16)g_MiniMapRectHeight_52334A )
  {
    if ( (unsigned __int16)result < (unsigned __int16)g_MiniMapRectLeft_523344 )
      LOWORD(result) = g_MiniMapRectLeft_523344;
    if ( bottom > (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346 )
      bottom = g_MiniMapRectHeight_52334A + g_MiniMapRectTop_523346 - 1;
    Render_FillRect(
      (_DWORD *)g_MiniMapSurface_52334C,
      g_RenderDevice,
      (unsigned __int16)(top - g_MiniMapRectTop_523346),
      (unsigned __int16)(result - g_MiniMapRectLeft_523344),
      right - g_MiniMapRectLeft_523344,
      bottom - g_MiniMapRectTop_523346,
      result,
      top);
    {
      _DWORD *surface; // esi
      unsigned __int16 right; // cx
      unsigned __int16 top; // bx
      unsigned __int16 left; // dx
      unsigned __int16 bottom; // stack

      surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
      if ( !surface )
        return result;
      right = (unsigned __int16)(g_MiniMapRectLeft_523344 + 7 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (*(_WORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9));
      top = (unsigned __int16)(g_MiniMapRectTop_523346 + 6 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_VIEW_TOP_OFFSET));
      left = (unsigned __int16)(g_MiniMapRectLeft_523344 + 6 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_VIEW_LEFT_OFFSET));
      bottom = (unsigned __int16)(g_MiniMapRectTop_523346 + 7 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (*(_WORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7));
      Surface_DrawRectOutline((unsigned __int16 *)surface, left, right, top, bottom, 0x4Cu);
      return result;
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 52334A: using guessed type __int16 word_52334A;
// 52334C: using guessed type int dword_52334C;
// 523F54: using guessed type char byte_523F54;

//----- (0040D6D0) --------------------------------------------------------
int  MiniMap_RedrawTileRect(int x0, signed int y0, int y1, int x1)
{
  signed int clampedY0; // edi
  int clampedY1; // esi
  int mapWidth; // ebx
  int mapHeight; // eax
  int result; // eax
  char *i; // ebx
  signed int j; // ecx
  __int16 boxHeight; // cx
  unsigned __int16 boxLeft; // si
  unsigned __int16 boxRight; // bx
  unsigned __int16 boxBottom; // bp
  unsigned __int16 boxTop; // di
  int clampedX0; // [esp+8h] [ebp-10h]

  clampedX0 = x0;
  clampedY0 = y0;
  clampedY1 = y1;
  if ( x0 < 0 )
    clampedX0 = 0;
  if ( y0 < 0 )
    clampedY0 = 0;
  mapWidth = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
  if ( x1 >= mapWidth )
    x1 = mapWidth - 1;
  mapHeight = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( y1 >= mapHeight )
    clampedY1 = mapHeight - 1;
  result = PLAYER_DATA_STRIDE * VIEWED_PLAYER_INDEX;
  if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
  {
    for ( i = (char *)clampedX0; (int)i <= x1; ++i )
    {
      for ( j = clampedY0; j <= clampedY1; ++j )
        MiniMap_DrawTileCell(i, j);
    }
    boxHeight = (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedY1 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 - 1;
    boxLeft = g_MiniMapRectLeft_523344 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedX0 + 7;
    boxRight = g_MiniMapRectLeft_523344 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)x1 - 1 + 7;
    boxBottom = g_MiniMapRectTop_523346 + boxHeight + 7;
    boxTop = g_MiniMapRectTop_523346 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedY0 + 7;
    g_RenderDevice = &g_MainRenderDevice;
    MiniMap_BlitDirtyRectAndDrawViewportBox(boxLeft, boxTop, boxBottom, boxRight);
    return Render_FillRect(g_RenderDevice, 0, boxTop, boxLeft, boxRight, boxBottom, boxLeft, boxTop);
  }
  return result;
}
// 40D747: variable 'j' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523F54: using guessed type char byte_523F54;

//----- (0040D800) --------------------------------------------------------
BOOL  MiniMap_IsSpanWithinViewportBounds(unsigned __int16 left, unsigned __int16 bottom)
{
  return PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX)
      && left >= (unsigned __int16)g_MiniMapRectLeft_523344
      && bottom <= (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 52334A: using guessed type __int16 word_52334A;

//----- (0040D850) --------------------------------------------------------
void MiniMap_RedrawAllTiles()
{
  char *tileX; // ebx
  signed int i; // ecx

  tileX = 0;
  g_RenderDevice = (_UNKNOWN *)g_MiniMapSurface_52334C;
  while ( (int)tileX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
  {
    for ( i = 0; i < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); ++i )
      MiniMap_DrawTileCell(tileX, i);
    ++tileX;
  }
  return;
}
// 40D86A: control flows out of bounds to 40D410

void Locale_DrawInteger()
{
  MiniMap_RedrawAllTiles();
}
// 40D88B: variable 'v2' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 52334C: using guessed type int dword_52334C;

//----- (0040D890) --------------------------------------------------------
void * MiniMap_DrawTileCell(void *result, signed int tileColumn)
{
  int row; // esi
  int column; // ecx
  unsigned __int16 *terrain_tile; // eax
  unsigned int tile_index; // eax
  int stack_record; // eax
  void *previous_render_device; // [esp+8h] [ebp-14h]
  unsigned __int8 color; // [esp+Ch] [ebp-10h]
  unsigned int scale;
  _DWORD *surface;

  row = (int)(intptr_t)result;
  column = tileColumn;
  if ( row < 0 || row >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) || column < 0 || column >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    return result;

  previous_render_device = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)(unsigned int)g_MiniMapSurface_52334C;
  color = 0xCFu;
  if ( (g_MiniMapDrawMask_511FF0 & 1) != 0 )
  {
    terrain_tile = TILE_TERRAIN_RECORD(row, column);
    if ( terrain_tile[2] == 0xFFFF )
      color = *(_BYTE *)((uintptr_t)(unsigned int)g_MiniMapTerrainColorTable_523F50 + *terrain_tile);
  }
  if ( (g_MiniMapDrawMask_511FF0 & 2) != 0 )
  {
    tile_index = *(unsigned __int16 *)(TILE_INDEX(row, column));
    if ( tile_index <= 0x1F4u
      && (unsigned int)*(__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * tile_index + 6) <= 0x28 )
    {
      stack_record = gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * tile_index;
      if ( !*(_BYTE *)(stack_record + 720) )
        color = g_MiniMapBuildingOwnerColorTable[*(unsigned __int8 *)(stack_record + 4)];
    }
  }
  if ( (g_MiniMapDrawMask_511FF0 & 4) != 0 )
  {
    tile_index = *(unsigned __int16 *)(TILE_INDEX(row, column));
    if ( tile_index >= 0x8000 && tile_index != 0xFFFF )
      color = g_MiniMapBuildingOwnerColorTable[*(unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * (tile_index - TILE_OCCUPANT_BUILDING_INDEX_BASE) + 2)];
  }
  if ( !Map_IsTileVisibleToPlayer(row, column, *(_DWORD *)(gameData + VIEWED_PLAYER_INDEX_OFFSET)) )
    color = 1;

  surface = (_DWORD *)(uintptr_t)(unsigned int)g_MiniMapSurface_52334C;
  scale = (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
  if ( scale == 1 )
  {
    RenderSurface_WriteSoftwarePixel(surface, row + 7, column + 7, color);
  }
  else
  {
    RenderSurface_FillSoftwareRect(
      surface,
      scale * row + 7,
      scale * column + 7,
      scale * (row + 1) + 6,
      scale * (column + 1) + 6,
      color);
  }
  result = previous_render_device;
  g_RenderDevice = previous_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 52334C: using guessed type int dword_52334C;
// 523F50: using guessed type int dword_523F50;
// 523F54: using guessed type char byte_523F54;

//----- (0040DB80) --------------------------------------------------------
signed int  Map_GetTileSurfaceClassOrUnexplored(int tileX, signed int tileY)
{
  unsigned __int16 *terrainRecord; // eax
  int surfaceClass; // edi

  terrainRecord = (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY);
  if ( terrainRecord[2] == 0xFFFF )
    surfaceClass = (unsigned __int8)g_MiniMapTileColorTableTheme0[*terrainRecord];
  else
    surfaceClass = 207;
  if ( Map_IsTileVisibleToPlayer(tileX, tileY, g_CurrentPlayerIndex) )
    return surfaceClass;
  else
    return 1;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DC10) --------------------------------------------------------
int MiniMap_UpdateViewportFromCursor()
{
  int result; // eax
  int tileX; // ebx
  int maxViewLeft; // esi
  int maxViewTop; // edx
  int cursor_x;
  int cursor_y;
  int is_flipping;
  int allow_scripted_update;
  int trace_minimap;
  int trace_minimap_verbose;
  int trace_cursor_on_minimap;

  result = DD_IsFlipping((int)g_RenderState);
  allow_scripted_update = !result && getenv("CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP");
  if ( result || allow_scripted_update )
  {
    is_flipping = result;
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    trace_minimap = getenv("CLASH95_TRACE_MINIMAP_CLICK") != 0;
    trace_minimap_verbose = getenv("CLASH95_TRACE_MINIMAP_VERBOSE") != 0;
    trace_cursor_on_minimap = cursor_x >= g_MiniMapRectLeft_523344
                           && cursor_x <= g_MiniMapRectLeft_523344 + 220
                           && cursor_y >= g_MiniMapRectTop_523346
                           && cursor_y <= g_MiniMapRectTop_523346 + 220;
    if ( trace_minimap_verbose && trace_cursor_on_minimap )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "minimap_sample",
        g_SelectedUnitIndex,
        g_MiniMapRectLeft_523344,
        g_MiniMapRectTop_523346,
        (unsigned __int8)g_MiniMapPixelsPerTile_523F54);
      Diagnostics_TraceWorldMapActionEvent(
        "minimap_cursor",
        g_SelectedUnitIndex,
        cursor_x,
        cursor_y,
        PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX));
    }
    result = PLAYER_DATA_STRIDE * VIEWED_PLAYER_INDEX;
    if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
    {
      tileX = (cursor_x - (unsigned __int16)g_MiniMapRectLeft_523344 - 7) / (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
      result = (cursor_y - (unsigned __int16)g_MiniMapRectTop_523346 - 7) / (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
      if ( trace_minimap_verbose && trace_cursor_on_minimap )
      {
        Diagnostics_TraceWorldMapActionEvent(
          "minimap_calc",
          g_SelectedUnitIndex,
          tileX,
          result,
          *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET));
      }
      if ( tileX >= 0
        && result >= 0
        && (tileX != *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) || result != *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET))
        && result <= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        maxViewLeft = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 9;
        if ( tileX <= maxViewLeft )
          *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = tileX;
        else
          *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = maxViewLeft;
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = result;
        maxViewTop = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 7;
        if ( maxViewTop < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) )
          *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = maxViewTop;
        if ( trace_minimap )
        {
          Diagnostics_TraceWorldMapActionEvent(
            "minimap_update",
            g_SelectedUnitIndex,
            *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET),
            *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET),
            is_flipping);
        }
        return WorldMap_RedrawViewport(1);
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523F54: using guessed type char byte_523F54;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DD30) --------------------------------------------------------
int MiniMap_ToggleVisibility()
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) ^= 1u;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DD60) --------------------------------------------------------
BOOL MiniMap_IsCursorInside()
{
  if ( !PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
    return 0;
  return g_MouseCursorRawX >> g_CursorCoordShift > (unsigned __int16)g_MiniMapRectLeft_523344
      && g_MouseCursorRawX >> g_CursorCoordShift < (unsigned __int16)g_MiniMapRectWidth_523348 + (unsigned __int16)g_MiniMapRectLeft_523344
      && g_MouseCursorRawY >> g_CursorCoordShift > (unsigned __int16)g_MiniMapRectTop_523346
      && g_MouseCursorRawY >> g_CursorCoordShift < (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523348: using guessed type __int16 word_523348;
// 52334A: using guessed type __int16 word_52334A;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DDE0) --------------------------------------------------------
int MiniMap_ShowAllLayers()
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 7;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DE20) --------------------------------------------------------
int MiniMap_ShowUnitsOnly()
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 2;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DE60) --------------------------------------------------------
int MiniMap_ShowBuildingsOnly()
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 4;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DEA0) --------------------------------------------------------
int MiniMap_Hide()
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 0;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DED0) --------------------------------------------------------
signed int  UI_MenuHitTestEntry(_WORD *menu)
{
  int centerOffset; // edi
  _WORD *measureEntryPtr; // esi
  int i; // ebx
  _WORD *hitEntryPtr; // esi
  int hitIndex; // ebx
  int rowOffset; // edi
  int SpriteHeight; // ebp
  int textWidth; // edx
  int centerGap; // ebp
  int rowTop; // ebp
  int rightX; // [esp+4h] [ebp-2Ch]
  unsigned __int16 topBaseY; // [esp+10h] [ebp-20h]
  unsigned __int16 leftX; // [esp+14h] [ebp-1Ch]

  LOWORD(centerOffset) = -1;
  measureEntryPtr = menu;
  for ( i = 0; i < (unsigned __int16)menu[4]; ++i )
  {
    SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    LOWORD(textWidth) = Render_LoadResourceSprite_v3(*(_BYTE **)&measureEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    centerGap = SpriteHeight - textWidth;
    if ( (unsigned __int16)(centerGap / 2) < (unsigned __int16)centerOffset )
      centerOffset = centerGap / 2;
    measureEntryPtr += 20;
  }
  hitEntryPtr = menu;
  leftX = centerOffset + *menu;
  hitIndex = 0;
  rowOffset = 0;
  topBaseY = menu[1] + 25;
  while ( 1 )
  {
    if ( hitIndex >= (unsigned __int16)menu[4] )
      return -1;
    rowTop = rowOffset + topBaseY;
    rightX = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]) + leftX;
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= leftX
      && g_MouseCursorRawY >> g_CursorCoordShift >= rowTop
      && g_MouseCursorRawX >> g_CursorCoordShift <= rightX
      && g_MouseCursorRawY >> g_CursorCoordShift <= rowTop + 22 )
    {
      break;
    }
    hitEntryPtr += 20;
    rowOffset += 22;
    ++hitIndex;
  }
  return hitIndex;
}
// 40DF54: variable 'v9' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 523F5C: using guessed type int dword_523F5C;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DFF0) --------------------------------------------------------
int  UI_RunMenu(_WORD *menu, DWORD a2)
{
  int menuTopY; // eax
  int sprite3Height; // eax
  int sprite3Width; // eax
  int panelSpriteWidth; // ebx
  int sprite4Width; // eax
  int v7; // ecx
  _DWORD *Surface; // eax
  __int16 menuTop; // dx
  int SpriteForChar; // eax
  DWORD deviceVTable; // ebp
  int v12; // edi
  int v13; // ecx
  int measureIndex; // esi
  _WORD *measureEntryPtr; // edi
  int v16; // ecx
  int drawIndex; // esi
  _WORD *drawEntryPtr; // edi
  unsigned __int16 *v19; // edx
  __int16 SpriteHeight; // ax
  int v21; // esi
  int v22; // ebx
  int mouseY; // edx
  int mouseX; // ecx
  int i; // eax
  int v26; // edi
  int v27; // esi
  signed int submenuHitIndex; // eax
  _WORD *v29; // ebx
  __int16 v30; // ax
  int renderDeviceMethods; // esi
  _WORD *v32; // ebx
  __int16 v33; // ax
  _WORD *resultEntryPtr; // eax
  int measureTextWidth; // edx
  int v37; // ecx
  int measureGap; // ecx
  char colorIndex; // cl
  DWORD prevHoveredIndex; // ebp
  signed int hitIndex; // esi
  int *colorPrevPtr; // edx
  char prevColorIndex; // al
  int v44; // edi
  __int16 prevTextWidth; // ax
  int entryEnabled; // ecx
  char highlightColorIndex; // al
  unsigned __int16 hitTextX; // di
  int hitEntryY; // ebp
  __int16 hitTextWidth; // ax
  _WORD *hitEntryLangBase; // eax
  _WORD *hitEntry; // eax
  unsigned __int16 menuBottomY; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v54; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v55; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v56; // [esp+3Ch] [ebp-78h]
  int v57; // [esp+40h] [ebp-74h]
  unsigned __int16 menuX; // [esp+40h] [ebp-74h]
  unsigned __int16 v59; // [esp+40h] [ebp-74h]
  int v60; // [esp+40h] [ebp-74h]
  unsigned __int16 menuY; // [esp+44h] [ebp-70h]
  unsigned __int16 v62; // [esp+44h] [ebp-70h]
  int v63; // [esp+48h] [ebp-6Ch]
  int colorActive; // [esp+4Ch] [ebp-68h] BYREF
  int colorInactive; // [esp+50h] [ebp-64h] BYREF
  int colorPrevActive; // [esp+54h] [ebp-60h] BYREF
  int colorPrevInactive; // [esp+58h] [ebp-5Ch] BYREF
  _WORD *prevEntryPtr; // [esp+5Ch] [ebp-58h]
  int colorHighlight; // [esp+60h] [ebp-54h] BYREF
  int hoveredIndex; // [esp+64h] [ebp-50h]
  _WORD *menuPtr; // [esp+68h] [ebp-4Ch]
  _WORD *hitEntryPtr; // [esp+6Ch] [ebp-48h]
  _DWORD *menuSurface; // [esp+70h] [ebp-44h]
  int exitFlag; // [esp+74h] [ebp-40h]
  int centerOffset; // [esp+78h] [ebp-3Ch]
  _WORD *menuLeft; // [esp+7Ch] [ebp-38h]
  char *textX; // [esp+80h] [ebp-34h]
  int textBaseY; // [esp+84h] [ebp-30h]
  int textY; // [esp+88h] [ebp-2Ch]
  char *hoverTextX; // [esp+8Ch] [ebp-28h]
  int entryY; // [esp+90h] [ebp-24h]
  int surfaceWidth; // [esp+94h] [ebp-20h]
  int surfaceHeight; // [esp+98h] [ebp-1Ch]
  const WorldMapTopMenuHitRecord *top_menu_record;

  menuPtr = menu;
  LOWORD(menu) = *menu;
  menuLeft = menu;
  HIWORD(menuTopY) = HIWORD(menuPtr);
  v63 = 0;
  LOWORD(menuTopY) = menuPtr[1];
  textBaseY = menuTopY;
  LOWORD(sprite3Height) = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  surfaceWidth = sprite3Height + 1;
  LOWORD(sprite3Width) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u);
  panelSpriteWidth = sprite3Width;
  LOWORD(sprite4Width) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
  surfaceHeight = panelSpriteWidth + sprite4Width + 1;
  Surface = (_DWORD *)Mem_Alloc(188, v7, panelSpriteWidth, a2);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, surfaceWidth, surfaceHeight);
  menuTop = menuPtr[1];
  menuSurface = Surface;
  Render_FillRect(
    (_DWORD *)g_WorldMapTargetSurface,
    Surface,
    (unsigned __int16)menuPtr[1],
    (unsigned __int16)*menuPtr,
    surfaceWidth + *menuPtr - 1,
    surfaceHeight + menuTop - 1,
    0,
    0);
  g_RenderDevice = (_UNKNOWN *)g_WorldMapTargetSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_MapPanelSpriteSet, 3);
  deviceVTable = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(deviceVTable + 52))(
    (unsigned __int16)textBaseY,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v12 = *((_DWORD *)g_RenderDevice + 46);
  textBaseY += 25;
  v57 = (unsigned __int16)(textBaseY + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u));
  LOWORD(v13) = (_WORD)menuLeft + DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  measureIndex = 0;
  (*(void (__fastcall **)(int, _DWORD, int, _DWORD))(v12 + 28))(v13, (unsigned __int16)menuLeft, v57, 0);
  measureEntryPtr = menuPtr;
  Render_ReleaseSurface(19, deviceVTable);
  centerOffset = v16;
  while ( measureIndex < (unsigned __int16)menuPtr[4] )
  {
    DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    LOWORD(measureTextWidth) = Render_LoadResourceSprite_v3(*(_BYTE **)&measureEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    measureGap = v37 - measureTextWidth;
    if ( (unsigned __int16)(measureGap / 2) < (unsigned __int16)centerOffset )
      centerOffset = measureGap / 2;
    measureEntryPtr += 20;
    ++measureIndex;
  }
  drawIndex = 0;
  textX = (char *)menuLeft + centerOffset;
  drawEntryPtr = menuPtr;
  textY = textBaseY;
  while ( drawIndex < (unsigned __int16)menuPtr[4] )
  {
    if ( *(_DWORD *)(drawEntryPtr + 13) )
    {
      colorActive = 0xFFFFFF;
      colorIndex = Render_ApplyColorTripletBytes((int)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorActive);
    }
    else
    {
      colorInactive = 10395294;
      colorIndex = Render_ApplyColorTripletBytes((int)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorInactive);
    }
    TextSprite_SetStyleFlag(colorIndex);
    TextSprite_DrawStringWithOrientation(
      (unsigned __int16)textX,
      (unsigned __int16)textY,
      0,
      *(unsigned __int8 **)&drawEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    drawEntryPtr += 20;
    ++drawIndex;
    textY += 22;
  }
  DLX_GetSpriteForChar(g_MapPanelSpriteSet, 4);
  (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v19 = menuPtr;
  Render_Pump();
  menuY = v19[1];
  menuX = *v19;
  v22 = (int)menuPtr;
  LOWORD(v22) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + *(_WORD *)(v22 + 2);
  menuBottomY = v22 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
  SpriteHeight = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  v21 = centerOffset;
  Render_BlitSurfaceRect(
    (_DWORD *)g_WorldMapTargetSurface,
    0,
    (unsigned __int16)menuPtr[1],
    (unsigned __int16)*menuPtr,
    *menuPtr + SpriteHeight,
    menuBottomY,
    menuX,
    menuY);
  LOBYTE(v22) = -1;
  Render_Present((int)g_RenderState);
  exitFlag = 0;
  hoveredIndex = -1;
  hoverTextX = (char *)menuLeft + v21;
  while ( DD_IsFlipping((int)g_RenderState) && !exitFlag )
  {
    DD_Pump((int)g_RenderState, v22);
    mouseY = g_MouseCursorRawY >> g_CursorCoordShift;
    mouseX = g_MouseCursorRawX >> g_CursorCoordShift;
    for ( i = 0; i < WORLD_MAP_TOP_MENU_HIT_RECORD_COUNT; ++i )
    {
      top_menu_record = &g_WorldMapTopMenuHitRecords[i];
      if ( menuPtr != top_menu_record->menu )
      {
        if ( mouseX >= (unsigned __int16)top_menu_record->left
          && mouseY >= (unsigned __int16)top_menu_record->top
          && mouseX <= (unsigned __int16)top_menu_record->right
          && mouseY <= (unsigned __int16)top_menu_record->bottom )
        {
          exitFlag = 1;
        }
      }
    }
    if ( *((_DWORD *)menuPtr + 1) )
    {
      submenuHitIndex = UI_MenuHitTestEntry(*((_WORD **)menuPtr + 1));
      if ( submenuHitIndex != -1 && menuPtr != *(_WORD **)(*((_DWORD *)menuPtr + 1) + 40 * submenuHitIndex + 30) )
        break;
    }
    prevHoveredIndex = hoveredIndex;
    hitIndex = UI_MenuHitTestEntry(menuPtr);
    if ( hitIndex != prevHoveredIndex )
    {
      Render_Pump();
      if ( prevHoveredIndex != -1 )
      {
        if ( *(_DWORD *)&menuPtr[20 * prevHoveredIndex + 13] )
        {
          colorPrevPtr = &colorPrevActive;
          colorPrevActive = 0xFFFFFF;
        }
        else
        {
          colorPrevPtr = &colorPrevInactive;
          colorPrevInactive = 10395294;
        }
        prevColorIndex = Render_ApplyColorTripletBytes((int)&g_RenderEnvPaletteContext, (unsigned __int8 *)colorPrevPtr);
        v44 = hoveredIndex;
        TextSprite_SetStyleFlag(prevColorIndex);
        prevEntryPtr = &menuPtr[20 * v44];
        LOWORD(v44) = (_WORD)hoverTextX;
        v22 = *(_DWORD *)&prevEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5];
        entryY = 22 * hoveredIndex + textBaseY;
        prevHoveredIndex = (unsigned __int16)entryY;
        TextSprite_DrawStringWithOrientation((unsigned __int16)hoverTextX, (unsigned __int16)entryY, 0, (unsigned __int8 *)v22);
        v55 = entryY + 22;
        prevTextWidth = Render_LoadResourceSprite_v3(*(_BYTE **)&prevEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
        LOBYTE(v22) = v44;
        Render_FillRect((_DWORD *)g_WorldMapTargetSurface, 0, prevHoveredIndex, (unsigned __int16)v44, v44 + prevTextWidth, v55, v44, prevHoveredIndex);
      }
      if ( hitIndex == -1 )
        goto LABEL_52;
      entryEnabled = *(_DWORD *)&menuPtr[20 * hitIndex + 13];
      hitEntryPtr = &menuPtr[20 * hitIndex];
      if ( !entryEnabled )
        goto LABEL_52;
      colorHighlight = 3342130;
      highlightColorIndex = Render_ApplyColorTripletBytes((int)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorHighlight);
      TextSprite_SetStyleFlag(highlightColorIndex);
      v22 = *(_DWORD *)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5];
      hitTextX = (unsigned __int16)hoverTextX;
      entryY = 22 * hitIndex + textBaseY;
      hitEntryY = (unsigned __int16)entryY;
      TextSprite_DrawStringWithOrientation((unsigned __int16)hoverTextX, (unsigned __int16)entryY, 0, (unsigned __int8 *)v22);
      v56 = entryY + 22;
      hitTextWidth = Render_LoadResourceSprite_v3(*(_BYTE **)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
      LOBYTE(v22) = hitTextX;
      Render_FillRect((_DWORD *)g_WorldMapTargetSurface, 0, hitEntryY, hitTextX, hitTextX + hitTextWidth, v56, hitTextX, hitEntryY);
      hitEntryLangBase = &hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex];
      prevHoveredIndex = *(_DWORD *)(hitEntryLangBase + 19);
      if ( prevHoveredIndex )
        Tooltip_ShowText(3, *(char **)(hitEntryLangBase + 19), v63);
      else
LABEL_52:
        Tooltip_RestoreBackdrop();
      hoveredIndex = hitIndex;
      Render_Present((int)g_RenderState);
      if ( hitIndex != -1 )
      {
        hitEntry = &menuPtr[20 * hitIndex];
        v22 = *(_DWORD *)(hitEntry + 15);
        if ( v22 )
        {
          if ( *(_DWORD *)(hitEntry + 13) )
          {
            v63 = UI_RunMenu(*(_DWORD *)(hitEntry + 15), prevHoveredIndex);
            if ( v63 )
              hoveredIndex = -1;
          }
        }
      }
    }
  }
  Render_Pump();
  if ( g_WorldMapTargetSurface != g_PrimaryRenderSurface )
  {
    v62 = menuPtr[1];
    v59 = *menuPtr;
    v29 = menuPtr;
    LOWORD(v29) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + v29[1];
    v54 = (_WORD)v29 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
    v30 = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    Render_FillRect(
      (_DWORD *)g_PrimaryRenderSurface,
      0,
      (unsigned __int16)menuPtr[1],
      (unsigned __int16)*menuPtr,
      *menuPtr + v30,
      v54,
      v59,
      v62);
  }
  Render_BlitSurfaceRect(menuSurface, 0, 0, 0, surfaceWidth - 1, surfaceHeight - 1, *menuPtr, menuPtr[1]);
  Render_Present((int)g_RenderState);
  if ( g_WorldMapTargetSurface != g_PrimaryRenderSurface )
  {
    renderDeviceMethods = *((_DWORD *)g_RenderDevice + 46);
    v32 = menuPtr;
    LOWORD(v32) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + v32[1];
    v60 = (unsigned __int16)((_WORD)v32 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u));
    v33 = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    (*(void (__fastcall **)(_DWORD, _DWORD, int, _DWORD))(renderDeviceMethods + 28))(
      (unsigned __int16)(*menuPtr + v33),
      (unsigned __int16)*menuPtr,
      v60,
      0);
  }
  Render_BlitSurfaceRect(menuSurface, (_DWORD *)g_WorldMapTargetSurface, 0, 0, surfaceWidth - 1, surfaceHeight - 1, *menuPtr, menuPtr[1]);
  if ( menuSurface )
    (*(void (**)(void))menuSurface[46])();
  if ( hoveredIndex != -1 && (resultEntryPtr = &menuPtr[20 * hoveredIndex], *(_DWORD *)(resultEntryPtr + 13)) )
    return *(_DWORD *)(resultEntryPtr + 17);
  else
    return v63;
}
// 40E02A: variable 'v3' is possibly undefined
// 40E03D: variable 'v4' is possibly undefined
// 40E049: variable 'v6' is possibly undefined
// 40E055: variable 'v7' is possibly undefined
// 40E160: variable 'v13' is possibly undefined
// 40E176: variable 'v16' is possibly undefined
// 40E53B: variable 'v63' is possibly undefined
// 40E586: variable 'v37' is possibly undefined
// 40E586: variable 'v36' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512348: using guessed type __int16 word_512348[];
// 51234A: using guessed type __int16 word_51234A[];
// 51234C: using guessed type __int16 word_51234C[];
// 51234E: using guessed type __int16 word_51234E[];
// 512350: using guessed type void *off_512350;
// 5202E0: using guessed type int dword_5202E0;
// 523F5C: using guessed type int dword_523F5C;
// 523F60: using guessed type int dword_523F60;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040E8B0) --------------------------------------------------------
BOOL  WorldMap_HandleTopMenuBar(char a1, int a2)
{
  _DWORD *surface; // eax
  int menu_sprite; // edx
  int mission_index; // edx
  int mouse_x; // ebx
  int mouse_y; // eax
  int i; // edx
  int close_button_left; // ebx
  int previous_screen_handle; // [esp+1Ch] [ebp-28h]
  int should_hide_menu; // [esp+20h] [ebp-24h]
  void (*menu_callback)(void); // [esp+24h] [ebp-20h]
  int previous_resource_handle; // [esp+28h] [ebp-1Ch]
  int (*previous_render_hook)(); // [esp+2Ch] [ebp-18h]
  const WorldMapTopMenuHitRecord *top_menu_record;

  if ( g_MouseCursorRawX >> g_CursorCoordShift < 0
    || g_MouseCursorRawY >> g_CursorCoordShift < 0
    || g_MouseCursorRawX >> g_CursorCoordShift > 640
    || g_MouseCursorRawY >> g_CursorCoordShift > 5
    || DD_IsFlipping((int)g_RenderState) )
  {
    return 1;
  }
  Diagnostics_TraceWorldMapActionEvent("top_menu_enter", g_SelectedUnitIndex, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift, 0);
  Debug_Log(0, a1, a2, (int)aMenuDraw);
  Render_Pump();
  previous_screen_handle = g_ActiveCursorDescriptorPtr;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, 0x18Fu, 0, 0);
  Render_Present((int)g_RenderState);
  surface = (_DWORD *)Mem_Alloc(188, 0, 0, a2);
  if ( surface )
    surface = Render_CreateSurface((int)surface, SCREEN_WIDTH, 400);
  g_WorldMapTargetSurface = (int)surface;
  g_RenderDevice = surface;
  RenderSurface_InvokeSlot56(surface);
  menu_sprite = DLX_GetSpriteForChar(g_MapPanelSpriteSet, (unsigned __int8)g_LanguageIndex % 3);
  (void)menu_sprite;
  Render_ReleaseSurface(2, 0);
  TextSprite_SetStyleFlag(76);
  mission_index = ACTIVE_MISSION_INDEX;
  if ( mission_index == 3 || mission_index == 13 )
    UI_DrawTextFmt(0, 585, 11, 0, 2, (const char *)aDD, GAME_TURN_COUNTER, 10);
  else if ( mission_index == 4 || mission_index == 14 )
    UI_DrawTextFmt(0, 585, 11, 0, 2, (const char *)aDD, GAME_TURN_COUNTER, 20);
  else
    UI_DrawTextFmt(0, 570, 11, 0, 2, (const char *)aD, GAME_TURN_COUNTER);
  Render_Pump();
  Render_Present((int)g_RenderState);
  should_hide_menu = 0;
  menu_callback = 0;
  while ( g_MouseCursorRawX >> g_CursorCoordShift >= 0
       && g_MouseCursorRawY >> g_CursorCoordShift >= 0
       && g_MouseCursorRawX >> g_CursorCoordShift <= 640
       && g_MouseCursorRawY >> g_CursorCoordShift <= 25 )
  {
    WorldMap_RunInputScriptStep();
    DD_Pump((int)g_RenderState, 0);
    for ( i = 0; i < WORLD_MAP_TOP_MENU_HIT_RECORD_COUNT; ++i )
    {
      top_menu_record = &g_WorldMapTopMenuHitRecords[i];
      mouse_x = g_MouseCursorRawX >> g_CursorCoordShift;
      if ( mouse_x >= (unsigned __int16)top_menu_record->left )
      {
        mouse_y = g_MouseCursorRawY >> g_CursorCoordShift;
        if ( mouse_y >= (unsigned __int16)top_menu_record->top
          && mouse_x <= (unsigned __int16)top_menu_record->right
          && mouse_y <= (unsigned __int16)top_menu_record->bottom
          && DD_IsFlipping((int)g_RenderState) )
        {
          menu_callback = (void (*)(void))UI_RunMenu(
                                         top_menu_record->menu,
                                         (unsigned __int16)top_menu_record->bottom);
        }
      }
    }
    if ( DD_IsFlipping((int)g_RenderState) )
    {
      close_button_left = g_LanguageIndex == 2 ? 430 : 470;
      if ( g_MouseCursorRawX >> g_CursorCoordShift >= close_button_left
        && g_MouseCursorRawY >> g_CursorCoordShift >= 0
        && g_MouseCursorRawX >> g_CursorCoordShift <= 590
        && g_MouseCursorRawY >> g_CursorCoordShift <= 25 )
      {
        Render_Begin((int)g_RenderState, 0);
        should_hide_menu = 1;
        Diagnostics_TraceWorldMapActionEvent("top_menu_close", g_SelectedUnitIndex, close_button_left, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
        break;
      }
    }
  }
  surface = (_DWORD *)g_WorldMapTargetSurface;
  if ( surface )
    RenderSurface_InvokeSlot0(surface, 2);
  Render_Pump();
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 0, 0, SCREEN_MAX_X, 0x18Fu, 0, 0);
  RenderState_SelectCursorDescriptor((int)g_RenderState, previous_screen_handle);
  Render_Present((int)g_RenderState);
  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previous_render_hook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, 0, a2, (int)aSetrhS08x_2, aStdrh_3, Render_DefaultRH);
  if ( menu_callback )
    menu_callback();
  Debug_Log((int)g_RenderHook, 0, a2, (int)aUnsetrh08x_2, g_RenderHook);
  g_RenderHook = previous_render_hook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, a2, (int)aMenuHide);
  Diagnostics_TraceWorldMapActionEvent("top_menu_return", g_SelectedUnitIndex, should_hide_menu, menu_callback != 0, 0);
  return !should_hide_menu;
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512348: using guessed type __int16 word_512348[];
// 51234A: using guessed type __int16 word_51234A[];
// 51234C: using guessed type __int16 word_51234C[];
// 51234E: using guessed type __int16 word_51234E[];
// 512350: using guessed type void *off_512350;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523F5C: using guessed type int dword_523F5C;
// 523F60: using guessed type int dword_523F60;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (0040ECF0) --------------------------------------------------------
_DWORD * WorldMapTopMenu_LoadSpriteSet()
{
  _DWORD *result; // eax

  result = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, "menu.s32");
    g_MapPanelSpriteSet = (int)result;
  }
  else
  {
    g_MapPanelSpriteSet = 0;
  }
  return result;
}
// 512000: using guessed type char *off_512000;
// 523F5C: using guessed type int dword_523F5C;

//----- (0040ED20) --------------------------------------------------------
int WorldMapTopMenu_FreeSpriteSet()
{
  return DLXSpriteSet_ReleaseAndClear(&g_MapPanelSpriteSet);
}
// 523F5C: using guessed type int dword_523F5C;

//----- (0040ED30) --------------------------------------------------------
int  UI_MenuEntry_Enable(int menuBase, int entryIndex)
{
  int result; // eax

  result = entryIndex;
  *(_DWORD *)(menuBase + 40 * entryIndex + 26) = 1;
  return result;
}

//----- (0040ED50) --------------------------------------------------------
int  UI_MenuEntry_Disable(int menuBase, int entryIndex)
{
  int result; // eax

  result = entryIndex;
  *(_DWORD *)(menuBase + 40 * entryIndex + 26) = 0;
  return result;
}

//----- (0040ED70) --------------------------------------------------------
void  Map_RevealAllTilesForPlayer(int playerIndex)
{
  int rowOffset; // ebp
  int playerBase; // edi
  int i; // ebx
  int byteAddr; // eax
  char maskedByte; // dl

  rowOffset = 0;
  playerBase = PLAYER_DATA_STRIDE * playerIndex;
  do
  {
    for ( i = 0; i < 100; ++i )
    {
      byteAddr = playerBase + gameData + rowOffset + ((i - (__CFSHL__(i >> 31, 3) + 8 * (i >> 31))) >> 3);
      maskedByte = (1 << (i & 7)) | *(_BYTE *)(byteAddr + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_REVEALED_TILES_OFFSET);
      *(_BYTE *)(byteAddr + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_REVEALED_TILES_OFFSET) = maskedByte;
    }
    rowOffset += 13;
  }
  while ( rowOffset != 1300 );
  Locale_DrawInteger();
}
// 5202E4: using guessed type int gameData;

//----- (0040EDE0) --------------------------------------------------------
signed int  Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex)
{
  int revealByteAddr; // eax
  int leftTileX; // ecx
  int rightTileX; // ecx
  signed int upTileY; // ecx
  signed int downTileY; // ecx
  int diagLeftTileX; // ecx
  int diagRightTileX; // ecx
  signed int diagDownTileY; // ecx
  int diagRightTileX2; // edi
  signed int diagDownTileY2; // ecx

  if ( tileX < 0
    || tileY < 0
    || tileX >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
    || tileY >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
    || Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
  {
    return 0;
  }
  revealByteAddr = PLAYER_DATA(playerIndex) + PLAYER_REVEALED_TILE_ROW_BYTES * tileX + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3);
  *(_BYTE *)(revealByteAddr + PLAYER_REVEALED_TILES_OFFSET) |= 1 << (tileY & 7);
  MiniMap_DrawTileCell((void *)tileX, tileY);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(leftTileX, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(rightTileX, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, upTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, downTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(diagLeftTileX, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(diagRightTileX, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX - 1, diagDownTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY + 2, playerIndex) )
  {
    diagRightTileX2 = tileX + 1;
    if ( !Map_IsTileVisibleToPlayer(diagRightTileX2, tileY + 1, playerIndex) )
      Map_RevealTileWithPropagation(diagRightTileX2, diagDownTileY2, playerIndex);
  }
  return 1;
}
// 40EFE9: variable 'v6' is possibly undefined
// 40EFFB: variable 'v7' is possibly undefined
// 40F00B: variable 'v8' is possibly undefined
// 40F01B: variable 'v9' is possibly undefined
// 40F02B: variable 'v10' is possibly undefined
// 40F03B: variable 'v11' is possibly undefined
// 40F04B: variable 'v12' is possibly undefined
// 40EFCF: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0040F060) --------------------------------------------------------
BOOL  Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex)
{
  return tileX >= 0
      && tileY >= 0
      && tileX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
      && tileY < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && ((1 << (tileY & 7)) & *(unsigned __int8 *)(PLAYER_DATA(playerIndex)
                                               + PLAYER_REVEALED_TILE_ROW_BYTES * tileX
                                               + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3)
                                               + PLAYER_REVEALED_TILES_OFFSET)) != 0;
}
// 5202E4: using guessed type int gameData;

//----- (0040F0C0) --------------------------------------------------------
signed int  Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex)
{
  signed int tileYBelow; // ebp
  bool belowRightVisible; // al
  char neighborAccum; // cl
  char neighborMask; // si
  char neighborMaskFull; // cl

  if ( Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
    return -1;
  Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex);
  Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex);
  tileYBelow = tileY + 1;
  Map_IsTileVisibleToPlayer(tileX - 1, tileYBelow, playerIndex);
  Map_IsTileVisibleToPlayer(tileX, tileYBelow, playerIndex);
  belowRightVisible = Map_IsTileVisibleToPlayer(tileX + 1, tileYBelow, playerIndex);
  neighborMask = belowRightVisible | neighborAccum & 0xFE;
  if ( !neighborMask )
    return 0;
  TextSprite_SetStyleFlag(1);
  if ( (~neighborMask & 0x5A) == 0x5A && (neighborMaskFull & 1) == 1 )
    return 12;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && neighborMaskFull < 0 )
    return 9;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && (neighborMaskFull & 4) != 0 )
    return 11;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && (neighborMaskFull & 0x20) != 0 )
    return 10;
  if ( (~neighborMaskFull & 0x58) == 0x58 && (neighborMaskFull & 2) != 0 )
    return 7;
  if ( (~neighborMaskFull & 0x4A) == 0x4A && (neighborMaskFull & 0x10) != 0 )
    return 4;
  if ( (~neighborMaskFull & 0x52) == 0x52 && (neighborMaskFull & 8) != 0 )
    return 5;
  if ( (~neighborMaskFull & 0x1A) == 0x1A && (neighborMaskFull & 0x40) != 0 )
    return 2;
  if ( (~neighborMaskFull & 0xA) == 0xA && (neighborMaskFull & 0x50) == 0x50 )
    return 1;
  if ( (~neighborMaskFull & 0x12) == 0x12 && (neighborMaskFull & 0x48) == 0x48 )
    return 3;
  if ( (~neighborMaskFull & 0x48) == 0x48 && (neighborMaskFull & 0x12) == 0x12 )
    return 6;
  if ( (~neighborMaskFull & 0x50) == 0x50 && (neighborMaskFull & 0xA) == 0xA )
    return 8;
  if ( (neighborMaskFull & 0x18) == 0x18 || (neighborMaskFull & 0x42) == 0x42 )
    return -1;
  if ( (unsigned __int8)neighborMaskFull == 255 )
    return 13;
  else
    return 14;
}
// 40F19C: variable 'v8' is possibly undefined
// 40F1CA: variable 'v10' is possibly undefined

//----- (0040F3C0) --------------------------------------------------------
signed int  UnitStack_IsIndexOnMap(int stackIndex)
{
  int rowBase; // edi
  int tileY; // edx
  int i; // eax
  int tileX; // [esp+0h] [ebp-18h]

  rowBase = 0;
  tileX = 0;
LABEL_2:
  if ( tileX >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
    return 0;
  tileY = 0;
  for ( i = 0; ; i += 2 )
  {
    if ( tileY >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      rowBase += 200;
      ++tileX;
      goto LABEL_2;
    }
    if ( *(unsigned __int16 *)(rowBase + gameData + i + TILE_MAP_OFFSET) == stackIndex )
      break;
    ++tileY;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (0040F440) --------------------------------------------------------
int  UnitSlot_InitFromType(int result, unit_type unitType, char ownerIndex)
{
  char moraleValue; // dl
  char stanceBits; // bh
  char auxFlagsByte; // cl
  char stateBitsByte; // dl
  char flagsByte; // ch

  *(_WORD *)(result + 4) = 0;
  *(_WORD *)(result + 6) = 0;
  *(_BYTE *)(result + 3) = 0;
  *(_DWORD *)(result + 23) = 0;
  UNIT_SLOT_TYPE(result) = unitType;
  UNIT_SLOT_OWNER(result) = ownerIndex;
  if ( unitType != -1 )
    UNIT_SLOT_ACTION_POINTS(result) = g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unitType];
  UNIT_SLOT_HEALTH_PERCENT(result) = 100;
  if ( unitType != -1 )
  {
    if ( (g_UnitTypeFlags[22 * unitType] & 2) != 0 )
      moraleValue = 6;
    else
      moraleValue = 10;
    UNIT_SLOT_MORALE(result) = moraleValue;
  }
  UNIT_SLOT_FATIGUE(result) = 0;
  stanceBits = UNIT_SLOT_STANCE_BITS(result);
  UNIT_SLOT_AUX_STATE(result) = 0;
  auxFlagsByte = *(_BYTE *)(result + 17);
  UNIT_SLOT_STANCE_BITS(result) = stanceBits & 0x80;
  stateBitsByte = *(_BYTE *)(result + 22);
  *(_BYTE *)(result + 17) = auxFlagsByte & 0xF8;
  flagsByte = *(_BYTE *)(result + 13);
  UNIT_SLOT_STATE_BITS(result) = stateBitsByte & 0xFE;
  UNIT_SLOT_FLAGS(result) = flagsByte & 0xF0;
  return result;
}
// 51257A: using guessed type int g_UnitTypeFlags[];

//----- (0040F4D0) --------------------------------------------------------
char  UnitStack_ResetRecord(int stackPtr, unit_type unitType, char ownerIndex)
{
  int slotIndex; // edx

  UnitSlot_InitFromType(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET, unitType, ownerIndex);
  for ( slotIndex = 1; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
    *(_WORD *)UNIT_STACK_SLOT(stackPtr, slotIndex) = -1;
  *(_DWORD *)UNIT_STACK_PATH_BUFFER(stackPtr) = 0;
  UNIT_STACK_OWNER_INDEX(stackPtr) = ownerIndex;
  return ownerIndex;
}

