/* Buildings, construction, economy, garrisons, and production.
 * Original function-marker range: 0x0041D030..0x0042C840.
 * Included by clash95.c; not a standalone translation unit. */

//----- (0041D030) --------------------------------------------------------
BOOL  Building_New(buildingType, stackIndex, st7_0, name, force)
int buildingType;
DWORD stackIndex;
double st7_0;
char *name;
int force;
{
  int v8; // ecx
  int stackByteOffset; // ecx
  int v10; // edx
  int foundFreeSlot; // ecx
  int scanByteOffset; // eax
  int v13; // eax
  char ownerByte; // al
  __int16 v15; // ax
  char v16; // dl
  char v17; // bl
  char v18; // dh
  char v19; // bh
  __int16 v20; // dx
  int v21; // eax
  _WORD *v22; // eax
  __int16 v23; // cx
  __int16 v24; // bx
  char *nameDest; // edi
  char v26; // dh
  char nameChar; // al
  char nameNextChar; // al
  int v29; // ecx
  int slotInitPtr; // eax
  int recordInitPtr; // eax
  int byteInitPtr; // eax
  int v33; // ecx
  int tileRowOffsetBelow; // edi
  int revealRow; // edi
  int revealColEnd; // ebp
  int revealColDelta; // esi
  signed int revealCol; // ecx
  int playerData; // eax
  signed int minimapColumn; // edx
  void *minimapRowPtr; // eax
  BOOL result; // eax
  int occupantAtTile; // eax
  int v44; // ecx
  signed int v45; // ecx
  int occupantBelow; // eax
  int occupantBelowLayer2; // eax
  int occupantLayer2; // eax
  __int16 v49; // dx
  int terrainTileId; // eax
  int castleTerrainTileId; // eax
  int terrainRowOffsetBelow; // ebx
  int terrainColOffset; // esi
  int v54; // ecx
  void *v55; // ecx
  signed int column; // [esp+4h] [ebp-34h]
  int buildingIndexCopy; // [esp+8h] [ebp-30h]
  int row; // [esp+14h] [ebp-24h]
  int buildingPtr; // [esp+18h] [ebp-20h]
  int scanIndex; // [esp+1Ch] [ebp-1Ch]
  int buildingIndex; // [esp+1Ch] [ebp-1Ch]
  int revealRowDelta; // [esp+24h] [ebp-14h]

  Diagnostics_TraceBootstrapEvent("Building_New-enter");
  Debug_Log(buildingType, stackIndex, force, (int)aBuilding_newDD);
  stackByteOffset = UNIT_STACK_STRIDE * stackIndex;
  g_CurrentPlayerIndex = *(unsigned __int8 *)(gameData + stackByteOffset + 147178);
  if ( g_BuildingNewOverrideActive )
  {
    row = g_BuildingNewOverrideRow;
    column = g_BuildingNewOverrideColumn;
  }
  else
  {
    row = *(__int16 *)(gameData + stackByteOffset + UNIT_STACK_TABLE_OFFSET);
    column = *(__int16 *)(gameData + stackByteOffset + 147176);
  }
  if ( buildingType == 1 && UnitStack_HasPeasantCargo(stackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET) )
    return 0;
  if ( !force )
  {
    result = MapTile_IsCastleFoundationTile(row, column, buildingType);
    if ( !result )
      return result;
    if ( buildingType )
    {
      if ( MapTile_IsCastleFoundationTile(row - 1, column, buildingType) )
        --row;
      if ( MapTile_IsCastleFoundationTile(row, column - 1, buildingType) )
        --column;
      occupantBelow = *(unsigned __int16 *)(TILE_ROW_STRIDE * (row + 1) + gameData + 2 * column + TILE_MAP_OFFSET);
      if ( occupantBelow != 0xFFFF && occupantBelow != stackIndex )
        return 0;
      occupantBelowLayer2 = *(unsigned __int16 *)(200 * (row + 1) + gameData + 2 * column + 556376);
      if ( occupantBelowLayer2 != 0xFFFF && occupantBelowLayer2 != stackIndex )
        return 0;
      occupantLayer2 = *(unsigned __int16 *)(gameData + 200 * row + 2 * column + 556376);
      if ( occupantLayer2 != 0xFFFF && occupantLayer2 != stackIndex )
        return 0;
    }
    occupantAtTile = *(unsigned __int16 *)(TILE_INDEX(row, column));
    if ( occupantAtTile != 0xFFFF && occupantAtTile != stackIndex )
      return 0;
  }
  foundFreeSlot = 0;
  scanByteOffset = 0;
  scanIndex = 0;
  do
  {
    if ( *(char *)(gameData + scanByteOffset + 509678) == -1 )
      foundFreeSlot = 1;
    scanByteOffset += 467;
    ++scanIndex;
  }
  while ( scanByteOffset < 46700 && !foundFreeSlot );
  v13 = scanIndex - 1;
  buildingIndex = scanIndex - 1;
  if ( !foundFreeSlot )
    return 0;
  buildingIndexCopy = v13;
  buildingPtr = UNIT_RECORD(buildingIndex);
  *(_BYTE *)buildingPtr = row;
  *(_BYTE *)(buildingPtr + 1) = column;
  ownerByte = g_CurrentPlayerIndex;
  *(_BYTE *)(buildingPtr + 3) = g_CurrentPlayerIndex;
  *(_BYTE *)(buildingPtr + 2) = ownerByte;
  *(_BYTE *)(buildingPtr + 4) = buildingType;
  v15 = g_BuildingTypeMaxHitPoints[buildingType];
  *(_BYTE *)(buildingPtr + 421) = 0;
  *(_BYTE *)(buildingPtr + 434) = 50;
  v16 = *(_BYTE *)(buildingPtr + 416);
  *(_WORD *)(buildingPtr + 16) = v15;
  v17 = *(_BYTE *)(buildingPtr + 435);
  *(_BYTE *)(buildingPtr + 416) = v16 & 0xE0;
  v18 = *(_BYTE *)(buildingPtr + 420);
  *(_BYTE *)(buildingPtr + 435) = v17 & 0xF8;
  v19 = *(_BYTE *)(buildingPtr + 436);
  *(_BYTE *)(buildingPtr + 420) = v18 & 0xFE;
  v20 = *(_WORD *)(buildingPtr + 432);
  *(_BYTE *)(buildingPtr + 436) = v19 & 0xC0;
  *(_WORD *)(buildingPtr + 432) = v20 & 0xF000;
  LOBYTE(v15) = *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) & 7;
  HIBYTE(v15) = *(_BYTE *)(buildingPtr + 444) & 0xF8;
  *(_BYTE *)(buildingPtr + 444) = HIBYTE(v15);
  *(_BYTE *)(buildingPtr + 444) = v15 | HIBYTE(v15);
  if ( buildingType )
  {
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      v21 = 200;
    else
      v21 = 300;
    *(_DWORD *)(buildingPtr + 438) = v21;
    v22 = (_WORD *)(buildingPtr + 430);
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      v23 = 100;
    else
      v23 = 250;
    v24 = *v22 & 0xF000;
    HIBYTE(v23) &= 0xFu;
    *v22 = v24;
    *v22 = v23 | v24;
  }
  nameDest = (char *)(buildingPtr + 5);
  v26 = *(_BYTE *)(buildingPtr + 437) & 0xC0;
  *(_WORD *)(buildingPtr + 442) = 0;
  *(_BYTE *)(buildingPtr + 437) = v26;
  *(_BYTE *)(buildingPtr + 437) = v26 | 0x32;
  do
  {
    nameChar = *name;
    *nameDest = *name;
    if ( !nameChar )
      break;
    nameNextChar = name[1];
    name += 2;
    nameDest[1] = nameNextChar;
    nameDest += 2;
  }
  while ( nameNextChar );
  memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 0, 7);
  if ( buildingType == 1 )
  {
    *(_BYTE *)(buildingPtr + 421) = 1;
    v49 = *(_WORD *)(buildingPtr + 430) & 0xF000;
    *(_BYTE *)(buildingPtr + 416) |= BUILDING_ADDON_FLAG_BARRACKS;
    *(_WORD *)(buildingPtr + 430) = v49;
  }
  slotInitPtr = buildingPtr;
  do
  {
    slotInitPtr += 6;
    *(_BYTE *)(slotInitPtr + 439) = -1;
  }
  while ( slotInitPtr != buildingPtr + 18 );
  recordInitPtr = buildingPtr;
  do
  {
    recordInitPtr += 31;
    *(_WORD *)(recordInitPtr - 13) = -1;
  }
  while ( recordInitPtr != buildingPtr + 372 );
  byteInitPtr = buildingPtr + 1;
  *(_BYTE *)(buildingPtr + 402) = 0;
  do
    *(_BYTE *)(++byteInitPtr + 401) = -1;
  while ( byteInitPtr != buildingPtr + 12 );
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = -1;
  Diagnostics_TraceBootstrapEvent("Building_New-before-unit-get-into");
  Building_UnitGetInto(stackIndex, buildingIndexCopy, 7, stackIndex, st7_0);
  Diagnostics_TraceBootstrapEvent("Building_New-after-unit-get-into");
  *(_WORD *)(TILE_INDEX(row, column)) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
  if ( buildingType == 1 || buildingType == 2 )
  {
    tileRowOffsetBelow = 200 * (row + 1);
    *(_WORD *)(tileRowOffsetBelow + gameData + 2 * column + TILE_MAP_OFFSET) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(gameData + 200 * row + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(tileRowOffsetBelow + gameData + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( !force )
    {
      castleTerrainTileId = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
      if ( castleTerrainTileId == 707 )
      {
        LOWORD(castleTerrainTileId) = 0;
      }
      else if ( castleTerrainTileId == 711 )
      {
        LOWORD(castleTerrainTileId) = 4;
      }
      terrainRowOffsetBelow = TILE_TERRAIN_ROW_STRIDE * (row + 1);
      terrainColOffset = 14 * (column + 1);
      *(_WORD *)(terrainColOffset + terrainRowOffsetBelow + gameData) = castleTerrainTileId;
      *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * row + gameData + terrainColOffset) = castleTerrainTileId;
      *(_WORD *)(gameData + terrainRowOffsetBelow + 14 * column) = castleTerrainTileId;
      *(_WORD *)(TILE_TERRAIN_RECORD_STRIDE * column + gameData + TILE_TERRAIN_ROW_STRIDE * row) = castleTerrainTileId;
    }
  }
  else if ( !force )
  {
    terrainTileId = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
    if ( terrainTileId == 707 )
    {
      LOWORD(terrainTileId) = 0;
    }
    else if ( terrainTileId == 711 )
    {
      LOWORD(terrainTileId) = 4;
    }
    *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * row + gameData + TILE_TERRAIN_RECORD_STRIDE * column) = terrainTileId;
  }
  Diagnostics_TraceBootstrapEvent("Building_New-after-tile-markers");
  if ( buildingType )
  {
    revealRow = row - 4;
    revealRowDelta = -4;
    while ( revealRow < row + 4 )
    {
      revealColEnd = column + 4;
      revealColDelta = -4;
      revealCol = column - 4;
      while ( revealCol < revealColEnd )
      {
        if ( Math_CeilSqrt(revealRowDelta * revealRowDelta + revealColDelta * revealColDelta) <= 4 )
          Map_RevealTileWithPropagation(revealRow, revealCol, g_CurrentPlayerIndex);
        ++revealCol;
        ++revealColDelta;
      }
      ++revealRow;
      ++revealRowDelta;
    }
  }
  Diagnostics_TraceBootstrapEvent("Building_New-after-reveal");
  playerData = PLAYER_DATA(g_CurrentPlayerIndex);
  if ( *(_DWORD *)(playerData + 140067) == -1 && buildingType == 2 )
    *(_DWORD *)(playerData + 140067) = buildingIndex;
  if ( ACTIVE_MISSION_INDEX == -1 || GAME_TURN_COUNTER != 1 )
    Building_AssignUniqueGeneratedName(buildingPtr);
  Diagnostics_TraceBootstrapEvent("Building_New-before-minimap");
  if ( buildingType )
  {
    MiniMap_DrawTileCell((void *)row, column);
    MiniMap_DrawTileCell((void *)(row + 1), column);
    MiniMap_DrawTileCell((void *)row, column + 1);
    minimapColumn = column + 1;
    minimapRowPtr = (void *)(row + 1);
  }
  else
  {
    minimapColumn = column;
    minimapRowPtr = (void *)row;
  }
  MiniMap_DrawTileCell(minimapRowPtr, minimapColumn);
  Diagnostics_TraceBootstrapEvent("Building_New-before-rules-assert");
  Rules_AssertCastleFact((unsigned __int8 *)buildingPtr, buildingIndex);
  Diagnostics_TraceBootstrapEvent("Building_New-before-under-construction-fact");
  Rules_LogCastleUnderConstructionFact(buildingIndex);
  Diagnostics_TraceBootstrapEvent("Building_New-done");
  return 1;
}
// 41D07B: variable 'v8' is possibly undefined
// 41D0AB: variable 'v10' is possibly undefined
// 41D2BE: variable 'v29' is possibly undefined
// 41D34E: variable 'v33' is possibly undefined
// 41D479: variable 'v38' is possibly undefined
// 41D5BC: variable 'v44' is possibly undefined
// 41D5D7: variable 'v45' is possibly undefined
// 41D905: variable 'v54' is possibly undefined
// 41D91A: variable 'v55' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 513A70: using guessed type __int16 word_513A70[4];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

static BOOL Building_NewAt(int row, int column, int building_type, DWORD stack_index, double st7_0, char *name, int force)
{
  BOOL result;

  g_BuildingNewOverrideActive = 1;
  g_BuildingNewOverrideRow = row;
  g_BuildingNewOverrideColumn = column;
  result = Building_New(building_type, stack_index, st7_0, name, force);
  g_BuildingNewOverrideActive = 0;
  return result;
}

//----- (0041D930) --------------------------------------------------------
_DWORD * Building_LogBuiltCastleFacts(unsigned __int8 *buildingPtr)
{
  int castleIndex; // edx

  castleIndex = *(unsigned __int16 *)(2 * buildingPtr[1] + gameData + TILE_ROW_STRIDE * *buildingPtr + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  return Rules_LogCastleBuiltFactAndScheme(castleIndex, castleIndex);
}
// 5202E4: using guessed type int gameData;

//----- (0041D980) --------------------------------------------------------
BOOL  MapTile_IsCastleFoundationTile(int row, signed int column, int checkMode)
{
  signed int surfaceClass; // eax
  int v5; // ecx
  int v6; // esi
  int rowBase; // ecx

  surfaceClass = Map_GetTileSurfaceClassOrUnexplored(row, column);
  if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 207 || surfaceClass == 1 )
    return 0;
  if ( checkMode )
  {
    v6 = 2 * column;
    rowBase = TILE_TERRAIN_ROW_STRIDE * row + gameData;
    return *(unsigned __int16 *)(rowBase + 7 * v6) >= 0x2C3u && *(unsigned __int16 *)(rowBase + 7 * v6) <= 0x2CAu;
  }
  return MapTile_IsCastleFoundationTile(row, column, 2) == 0;
}
// 41D9F0: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041DA50) --------------------------------------------------------
BOOL  MapTile_IsCastleFoundationAnchorTile(int row, signed int column, int checkMode)
{
  signed int surfaceClass; // eax
  int v5; // ecx
  int tileId; // eax

  surfaceClass = Map_GetTileSurfaceClassOrUnexplored(row, column);
  if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 207 || surfaceClass == 1 )
    return 0;
  if ( checkMode )
  {
    tileId = *(unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * row + gameData + TILE_TERRAIN_RECORD_STRIDE * column);
    return tileId == 707 || tileId == 711;
  }
  return !MapTile_IsCastleFoundationTile(row, column, 2);
}
// 41DAC0: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041DB20) --------------------------------------------------------
int Rules_RebuildCastleSiteFacts()
{
  int row; // esi
  int i; // ebp
  int result; // eax
  int column; // ecx
  int colByteOffset; // ebx
  int tileId; // eax

  row = 0;
  for ( i = 0; ; i += 1400 )
  {
    result = gameData;
    if ( row >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    column = 0;
    colByteOffset = 0;
    while ( column < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      tileId = *(unsigned __int16 *)(colByteOffset + i + gameData);
      if ( tileId == 707 || tileId == 711 )
        Rules_LogCastleSiteFact(row, column);
      colByteOffset += 14;
      ++column;
    }
    ++row;
  }
  return result;
}
// 41DB78: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041DBA0) --------------------------------------------------------
signed int  BuildCursor_IsPlacementValid(int row, int column, int buildingType, int stackIndex)
{
  int rowDelta; // edx
  int rowDeltaAbs; // eax
  signed int scanColumn; // ecx
  int scanColByteOffset; // ebp
  signed int surfaceClass; // eax
  int tileOwner; // eax
  int scanRow; // ebp
  int colScanEnd; // ebx
  int scanRowByteOffset; // esi
  int colScanByteEnd; // ebx
  int i; // eax
  int v18; // ecx
  int savedPlayerIndex; // [esp+0h] [ebp-40h]
  int footprintRadius; // [esp+4h] [ebp-3Ch]
  int colScanStart; // [esp+8h] [ebp-38h]
  int scanRowByteOffsetEnd; // [esp+10h] [ebp-30h]
  int rowByteBase; // [esp+18h] [ebp-28h]
  int colEnd; // [esp+28h] [ebp-18h]
  int currentRow; // [esp+2Ch] [ebp-14h]
  int isValid; // [esp+30h] [ebp-10h]

  switch ( buildingType )
  {
    case 0:
    case 3:
      footprintRadius = 1;
      break;
    case 1:
    case 2:
      footprintRadius = 2;
      break;
    default:
      break;
  }
  savedPlayerIndex = g_CurrentPlayerIndex;
  g_CurrentPlayerIndex = *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178);
  rowDelta = row - *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + UNIT_STACK_TABLE_OFFSET);
  isValid = 1;
  rowDeltaAbs = rowDelta;
  if ( rowDelta <= 0 )
    rowDeltaAbs = -rowDelta;
  if ( rowDeltaAbs > footprintRadius )
    goto LABEL_6;
  if ( column - *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) > 0 )
  {
    if ( column - *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) <= footprintRadius )
      goto LABEL_7;
LABEL_6:
    isValid = 0;
    goto LABEL_7;
  }
  if ( *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) - column > footprintRadius )
    goto LABEL_6;
LABEL_7:
  colEnd = column + footprintRadius;
  currentRow = row;
  rowByteBase = 200 * row;
  if ( row >= row + footprintRadius )
  {
LABEL_24:
    if ( buildingType != 3 )
    {
      scanRow = row - 1;
      colScanEnd = column + footprintRadius + 1;
      colScanStart = column - 1;
      scanRowByteOffset = 200 * (row - 1);
      scanRowByteOffsetEnd = 200 * (footprintRadius + row + 1);
      if ( scanRowByteOffset < scanRowByteOffsetEnd )
      {
        colScanByteEnd = 2 * colScanEnd;
        do
        {
          for ( i = 2 * colScanStart; i < colScanByteEnd; i += 2 )
          {
            if ( *(unsigned __int16 *)(scanRowByteOffset + gameData + i + TILE_MAP_OFFSET) >= 0x8000u
              && *(unsigned __int16 *)(scanRowByteOffset + gameData + i + TILE_MAP_OFFSET) != 0xFFFF )
            {
              isValid = 0;
            }
          }
          scanRowByteOffset += 200;
          ++scanRow;
        }
        while ( scanRowByteOffset < scanRowByteOffsetEnd );
      }
    }
    g_CurrentPlayerIndex = savedPlayerIndex;
    return isValid;
  }
  else
  {
    while ( 1 )
    {
      scanColumn = column;
      scanColByteOffset = 2 * column;
      if ( column < colEnd )
        break;
LABEL_23:
      rowByteBase += 200;
      if ( ++currentRow >= row + footprintRadius )
        goto LABEL_24;
    }
    while ( 1 )
    {
      surfaceClass = Map_GetTileSurfaceClassOrUnexplored(currentRow, scanColumn);
      if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 1 )
        isValid = 0;
      tileOwner = *(unsigned __int16 *)(rowByteBase + gameData + scanColByteOffset + TILE_MAP_OFFSET);
      if ( tileOwner != 0xFFFF && tileOwner != stackIndex )
        isValid = 0;
      if ( Trap_GetTileOwnerMask(row, column, g_CurrentPlayerIndex) || MapTile_GetReligiousSiteCategory(row, column) || MapTile_HasHiddenTreasure(row, column) )
        return 0;
      if ( buildingType == 3 && MapTile_IsCastleFoundationTile(row, column, 2) )
        return 0;
      scanColumn = v18 + 1;
      scanColByteOffset += 2;
      if ( scanColumn >= colEnd )
        goto LABEL_23;
    }
  }
}
// 41DC25: variable 'v20' is possibly undefined
// 41DD63: variable 'v18' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0041E050) --------------------------------------------------------
signed int  Building_Stop(DWORD buildingPtr, int a2, char a3, DWORD a4, double a5)
{
  DWORD slotPtr; // edx
  int slotIndex; // eax
  int occupiedCount; // ebx
  int outIndex; // ecx
  DWORD buildingPtrCopy; // [esp+0h] [ebp-34h]
  int occupiedSlots[12]; // [esp+4h] [ebp-30h] BYREF

  buildingPtrCopy = buildingPtr;
  Debug_Log(a2, a3, a4, (int)aBuilding_stop0);
  if ( !*(_WORD *)(buildingPtr + 16) )
    return 0;
  slotPtr = buildingPtr;
  slotIndex = 0;
  occupiedCount = 0;
  outIndex = 0;
  do
  {
    if ( *(__int16 *)(slotPtr + 18) != -1 )
    {
      ++outIndex;
      ++occupiedCount;
      occupiedSlots[outIndex - 1] = slotIndex;
    }
    ++slotIndex;
    slotPtr += 31;
  }
  while ( slotIndex < 12 );
  if ( occupiedCount < 10 )
    occupiedSlots[occupiedCount] = -1;
  Building_UnitsLeave((unsigned __int8 *)buildingPtr, occupiedSlots, a5);
  *(_WORD *)(buildingPtr + 16) = -1;
  Rules_RetractCastleFact((unsigned __int8 *)buildingPtr, a5);
  return 1;
}

//----- (0041E0E0) --------------------------------------------------------
char  Building_AssignUniqueGeneratedName(int buildingPtr)
{
  char *namePtr; // ebp
  int duplicate_count; // [esp+10h] [ebp-20h]
  unsigned int name_index; // [esp+Ch] [ebp-24h]
  char lower_name[24]; // [esp+0h] [ebp-30h] BYREF

  namePtr = (char *)(buildingPtr + 5);
  duplicate_count = 0;
  while ( 1 )
  {
    name_index = Rng_RandRange(0, 47);
    strncpy(lower_name, namePtr, sizeof(lower_name) - 1);
    lower_name[sizeof(lower_name) - 1] = 0;
    strlwr_(lower_name);
    if ( strcmp(lower_name, g_BuildingRandomNamePool[name_index]) )
      break;
    if ( ++duplicate_count >= 48 )
    {
      strcpy(namePtr, g_BuildingRandomNamePool[Rng_RandRange(0, 47)]);
      return *namePtr;
    }
  }
  strcpy(namePtr, g_BuildingRandomNamePool[name_index]);
  return Str_TitleCase((_BYTE *)namePtr, 0, 0);
}
// 476253: using guessed type int __fastcall strlwr_(_DWORD, _DWORD);
// 513A84: using guessed type char *off_513A84[50];

//----- (0041E1E0) --------------------------------------------------------
char  Building_FinishConstruction(unsigned __int8 *buildingPtr, int a2, char a3, double a4)
{
  int tileRow; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int buildingType; // eax
  int v10; // eax
  int tileColumn; // edx
  int revealRow; // edi
  int i; // esi
  signed int revealColumn; // ecx
  char result; // al
  int row; // ebx
  int v17; // ecx
  int buildingColumn; // [esp+0h] [ebp-30h]
  int revealRowEnd; // [esp+4h] [ebp-2Ch]
  int revealColStart; // [esp+8h] [ebp-28h]
  int revealRowDelta; // [esp+Ch] [ebp-24h]
  int revealColEnd; // [esp+14h] [ebp-1Ch]

  Debug_Log(a2, a3, (DWORD)buildingPtr, (int)aBuilding_build);
  LOBYTE(tileRow) = *buildingPtr;
  Rules_LogCastleBuiltFactAndScheme(v6, *(unsigned __int16 *)(2 * buildingPtr[1] + gameData + TILE_ROW_STRIDE * tileRow + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Rules_LogNewCastleFact(buildingPtr[2], *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Building_OnGarrisonChange(*(unsigned __int16 *)(2 * buildingPtr[1] + TILE_ROW_STRIDE * *buildingPtr + gameData + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v7, a4);
  buildingType = (char)buildingPtr[4];
  if ( buildingType == 2 || buildingType == 1 )
    Map_RebuildRoadOverlayAtTile(*buildingPtr, buildingPtr[1] + 2);
  v10 = (char)buildingPtr[4];
  if ( !buildingPtr[4] )
  {
    tileColumn = buildingPtr[1];
    LOBYTE(v10) = *buildingPtr;
    revealColEnd = tileColumn + 15;
    revealRow = v10 - 15;
    revealColStart = tileColumn - 15;
    v8 = v10 + 15;
    revealRowEnd = v10 + 15;
    revealRowDelta = -15;
    if ( v10 - 15 < v10 + 15 )
    {
      buildingColumn = buildingPtr[1];
      do
      {
        v8 = revealColStart;
        for ( i = revealColStart - buildingColumn; v8 < revealColEnd; ++i )
        {
          if ( Math_CeilSqrt(revealRowDelta * revealRowDelta + i * i) <= 15 )
    Map_RevealTileWithPropagation(revealRow, revealColumn, buildingPtr[2]);
          v8 = revealColumn + 1;
        }
        ++revealRow;
        ++revealRowDelta;
      }
      while ( revealRow < revealRowEnd );
    }
  }
  Unit_UpdatePerTurn((int)buildingPtr, v8);
  result = buildingPtr[4];
  if ( result )
  {
    result = gameData;
    if ( *(_DWORD *)(PLAYER_DATA_STRIDE * buildingPtr[2] + gameData + 140051) )
    {
      row = *buildingPtr;
      UI_CenterWorldMapViewportOnRectIfFit(row, buildingPtr[1], buildingPtr[1] - 5, row);
      return Building_ShowConstructionFinishedDialog((int)buildingPtr, v17, row, (DWORD)buildingPtr);
    }
  }
  return result;
}
// 41E247: variable 'v6' is possibly undefined
// 41E21E: variable 'v5' is possibly undefined
// 41E2D1: variable 'v7' is possibly undefined
// 41E36B: variable 'v14' is possibly undefined
// 41E38E: variable 'v8' is possibly undefined
// 41E3D5: variable 'v17' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041E3F0) --------------------------------------------------------
int  Building_ProcessUnitProductionTurn(int result, int a2, char a3, DWORD a4, double a5)
{
  unsigned __int8 *buildingPtr; // esi
  unsigned __int8 turnsRemaining; // dl
  int garrisonSlotPtr; // edx
  int remainingGold; // ecx
  int playerDataOffset; // eax

  buildingPtr = (unsigned __int8 *)result;
  if ( (*(_BYTE *)(result + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    result = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(result);
    if ( result != -1 )
    {
      turnsRemaining = BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) - 1;
      BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = turnsRemaining;
      if ( !turnsRemaining )
      {
        result = (unsigned __int8)g_UnitTypeProductionCost[88 * (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402]];
        if ( (unsigned int)result <= *(_DWORD *)(buildingPtr + 438) )
        {
          Debug_Log(a2, a3, a4, (int)aBuilding_produ);
          result = 0;
          while ( *(__int16 *)(garrisonSlotPtr + 18) != -1 )
          {
            ++result;
            garrisonSlotPtr += 31;
            if ( result >= 12 )
            {
              BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = 1;
              return result;
            }
          }
          UnitSlot_InitFromType((int)&buildingPtr[31 * result + 18], (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402], buildingPtr[2]);
          remainingGold = *(_DWORD *)(buildingPtr + 438) - (unsigned __int8)g_UnitTypeProductionCost[88 * (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402]];
          playerDataOffset = PLAYER_DATA_STRIDE * buildingPtr[2];
          *(_DWORD *)(buildingPtr + 438) = remainingGold;
          if ( *(_DWORD *)(gameData + playerDataOffset + 140051) )
          {
            BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = g_UnitTypeProductionTime[88 * (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402]];
          }
          else
          {
            BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = 0;
            BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = -1;
          }
          return Building_OnGarrisonChange(
                   *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
                   remainingGold,
                   a5);
        }
        else
        {
          BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = 1;
        }
      }
    }
  }
  return result;
}
// 41E468: conditional instruction was optimized away because eax.4<C
// 41E45C: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041E570) --------------------------------------------------------
char  Building_UpdateGarrisonTrainRepairTimers(unsigned __int8 *buildingPtr, double a2)
{
  unsigned __int8 *slotPtr; // ecx
  int garrisonChanged; // esi
  int slotIndex; // ebx
  unsigned __int8 *garrisonBytePtr; // edx
  int v6; // eax
  unsigned __int8 serviceState; // ah
  char v8; // al
  unsigned __int8 v9; // ah
  unsigned __int8 *firstSlotPtr; // [esp+0h] [ebp-20h]

  slotPtr = buildingPtr;
  garrisonChanged = 0;
  slotIndex = 0;
  firstSlotPtr = buildingPtr + 18;
  garrisonBytePtr = buildingPtr;
  do
  {
    v6 = *((__int16 *)slotPtr + 9);
    if ( v6 != -1 )
    {
      serviceState = BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0);
      if ( (serviceState & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
      {
        v8 = (((unsigned __int8)(4 * serviceState) >> 5) - 1) & 7;
        v9 = serviceState & 0xC7;
        BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0) = v9;
        LOBYTE(v6) = 8 * v8;
        BYTE1(v6) = v6 | v9;
        BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0) = BYTE1(v6);
        if ( (v6 & 0x3800) == 0 )
        {
          garrisonChanged = 1;
          slotPtr[27] = 100;
        }
      }
      else if ( (serviceState & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
      {
        LOBYTE(v6) = ((serviceState & BUILDING_GARRISON_TRAINING_TURNS_MASK) - 1) & 7;
        BYTE1(v6) = serviceState & 0xF8;
        BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0) = BYTE1(v6);
        BYTE1(v6) |= v6;
        BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0) = BYTE1(v6);
        if ( (v6 & 0x700) == 0 )
        {
          if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * buildingPtr[2] + 140051) )
          {
            LOBYTE(v6) = UnitSlot_CycleOrderState((int)&firstSlotPtr[31 * slotIndex]);
          }
          else
          {
            LOBYTE(v6) = slotPtr[30] & 3;
            if ( (unsigned __int8)v6 < 3u )
            {
              BYTE1(v6) = slotPtr[30] & 0xFC;
              slotPtr[30] = BYTE1(v6);
              BYTE1(v6) |= (v6 + 1) & 3;
              slotPtr[30] = BYTE1(v6);
              LOBYTE(v6) = BYTE1(v6) & 0xF3;
              garrisonChanged = 1;
              slotPtr[30] = BYTE1(v6) & 0xF3;
            }
          }
        }
      }
    }
    slotPtr += 31;
    ++slotIndex;
    ++garrisonBytePtr;
  }
  while ( slotIndex < 12 );
  if ( garrisonChanged )
    LOBYTE(v6) = Building_OnGarrisonChange(
                   *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
                   (int)buildingPtr,
                   a2);
  return v6;
}

char  Building_AutoFillOrUseGarrison(unsigned __int8 *buildingPtr, double a2)
{
  return Building_UpdateGarrisonTrainRepairTimers(buildingPtr, a2);
}
// 41E5CC: variable 'v2' is possibly undefined
// 41E5D0: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041E6D0) --------------------------------------------------------
_BYTE * Unit_NewTurnRegen(_BYTE *result)
{
  _BYTE *slotsEnd; // ecx
  unsigned __int8 v2; // dl
  char countdown; // dl

  if ( result[429] )
  {
    countdown = result[429] - 1;
    result[429] = countdown;
    if ( !countdown )
      ++result[421];
  }
  slotsEnd = result + 7;
  do
  {
    v2 = result[422];
    if ( v2 < 0x64u )
    {
      result[422] = v2 + 10;
      if ( (unsigned __int8)(v2 + 10) > 0x64u )
        result[422] = 100;
    }
    ++result;
  }
  while ( result != slotsEnd );
  return result;
}

//----- (0041E730) --------------------------------------------------------
int  Unit_UpdatePerTurn(int buildingPtr, int a2)
{
  __int16 currentHitPoints; // dx
  unsigned __int16 maxHitPoints; // cx
  int damagePercent; // eax
  int damageUpper; // esi
  int damageLower; // ebx
  int result; // eax
  int slotWalker; // ecx
  char rolledDamage; // dl

  (void)a2;
  currentHitPoints = *(_WORD *)(buildingPtr + 16);
  if ( !currentHitPoints )
  {
    memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 100, 7);
    return buildingPtr + 422;
  }
  maxHitPoints = g_BuildingTypeMaxHitPoints[*(char *)(buildingPtr + 4)];
  damagePercent = 100 * (maxHitPoints - currentHitPoints) / maxHitPoints;
  damageUpper = damagePercent + 10;
  damageLower = damagePercent - 10;
  slotWalker = buildingPtr;
  do
  {
    result = Rng_RandRange(damageLower, damageUpper);
    rolledDamage = result;
    if ( result < 0 )
    {
      rolledDamage = 0;
    }
    else if ( result > 100 )
    {
      rolledDamage = 100;
    }
    ++slotWalker;
    *(_BYTE *)(slotWalker + 421) = rolledDamage;
  }
  while ( slotWalker != buildingPtr + 7 );
  return result;
}
// 513A70: using guessed type __int16 word_513A70[4];

//----- (0041E7B0) --------------------------------------------------------
BOOL  UnitSlot_NeedsMoraleRecovery(__int16 *unitSlotPtr)
{
  if ( (g_UnitTypeFlags[22 * *unitSlotPtr] & 2) != 0 )
    return *((char *)unitSlotPtr + 11) < 6;
  else
    return *((char *)unitSlotPtr + 11) < 10;
}
// 51257A: using guessed type int g_UnitTypeFlags[];

//----- (0041E7F0) --------------------------------------------------------
int  Building_RecoverGarrisonFatigueAndMorale(unsigned __int8 *buildingPtr, double a2)
{
  CSyncObject *slotPtr; // ecx
  int garrisonChanged; // edx
  int i; // esi
  int result; // eax
  int v7; // ecx

  slotPtr = (CSyncObject *)(buildingPtr + 18);
  garrisonChanged = 0;
  for ( i = 0; i < 12; ++i )
  {
    result = *(__int16 *)slotPtr;
    if ( result != -1 )
    {
      UnitSlot_AdjustFatigueByPredicate((int)slotPtr, -50, UnitSlot_PredicateAlways);
      result = UnitSlot_AdjustMoraleByPredicate((int)slotPtr, 1, (BOOL ( *)(int))UnitSlot_NeedsMoraleRecovery);
      garrisonChanged = 1;
    }
    slotPtr = (CSyncObject *)((char *)slotPtr + 31);
  }
  if ( garrisonChanged )
    return Building_OnGarrisonChange(
             *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
             (int)slotPtr,
             a2);
  return result;
}
// 41E838: variable 'v7' is possibly undefined
// 41E809: variable 'v3' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041E890) --------------------------------------------------------
unsigned __int8 * Player_UpdateTechnologyLevelFromSettlements(int playerIndex, int a2, DWORD a3)
{
  int fullyUpgradedCount; // esi
  int settlementCount; // edi
  int buildingIndex; // edx
  _BYTE *buildingPtr; // eax
  int buildingType; // ecx
  char addonFlags; // cl
  unsigned __int8 *result; // eax
  int updateIndex; // edx
  unsigned __int8 clearedTechBits; // ch
  int newTechLevel; // [esp+0h] [ebp-20h]

  fullyUpgradedCount = 0;
  settlementCount = 0;
  buildingIndex = 0;
  Debug_Log(a2, playerIndex, a3, (int)aBuilding_check);
  buildingPtr = (_BYTE *)(gameData + BUILDING_TABLE_OFFSET);
  do
  {
    if ( (unsigned __int8)buildingPtr[3] == playerIndex )
    {
      buildingType = (char)buildingPtr[4];
      if ( buildingType == 2 || buildingType == 1 )
      {
        addonFlags = buildingPtr[416];
        ++settlementCount;
        if ( (addonFlags & 1) != 0 && (addonFlags & 2) != 0 && (addonFlags & 0x10) != 0 && (addonFlags & 4) != 0 && (addonFlags & 8) != 0 )
          ++fullyUpgradedCount;
      }
    }
    ++buildingIndex;
    buildingPtr += 467;
  }
  while ( buildingIndex < 100 );
  if ( settlementCount >= 2 && fullyUpgradedCount )
  {
    if ( fullyUpgradedCount == 1 )
      newTechLevel = 2;
    else
      newTechLevel = 3;
  }
  else
  {
    newTechLevel = 1;
  }
  result = (unsigned __int8 *)(PLAYER_DATA_STRIDE * playerIndex + gameData);
  if ( result[140071] < newTechLevel )
  {
    result[140071] = newTechLevel;
    updateIndex = 0;
    result = (unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET);
    do
    {
      if ( result[2] == playerIndex && (result[444] & 7) < newTechLevel )
      {
        clearedTechBits = result[444] & 0xF8;
        result[444] = clearedTechBits;
        result[444] = newTechLevel & 7 | clearedTechBits;
      }
      ++updateIndex;
      result += 467;
    }
    while ( updateIndex < 100 );
  }
  return result;
}
// 41E8F7: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041E9E0) --------------------------------------------------------
void  Building_DebugDump(unsigned __int8 *buildingPtr, char a2, DWORD a3)
{
  Debug_Log(
    *buildingPtr,
    a2,
    a3,
    (int)aD0x08xDDTDPDGD,
    a2,
    buildingPtr,
    buildingPtr[0],
    buildingPtr[1],
    (signed __int8)buildingPtr[4],
    buildingPtr[2],
    *(_DWORD *)(buildingPtr + 438),
    *(_WORD *)(buildingPtr + 430) & 0xFFF,
    *(__int16 *)(buildingPtr + 16));
  Debug_Log(
    *(__int16 *)(buildingPtr + 18),
    a2,
    a3,
    (int)aUDDDDDDDDDD,
    *(__int16 *)(buildingPtr + 18),
    *(__int16 *)(buildingPtr + 49),
    *(__int16 *)(buildingPtr + 80),
    *(__int16 *)(buildingPtr + 111),
    *(__int16 *)(buildingPtr + 142),
    *(__int16 *)(buildingPtr + 173),
    *(__int16 *)(buildingPtr + 204),
    *(__int16 *)(buildingPtr + 235),
    *(__int16 *)(buildingPtr + 266),
    *(__int16 *)(buildingPtr + 297),
    *(__int16 *)(buildingPtr + 328),
    *(__int16 *)(buildingPtr + 359));
}

//----- (0041EA90) --------------------------------------------------------
void  LogAllBuildings(int a1, char a2, DWORD a3)
{
  int buildingIndex; // ebx
  int buildingPtr; // ecx

  Debug_Log(a1, a2, a3, (int)aLogallbuilding);
  buildingIndex = 0;
  buildingPtr = gameData + BUILDING_TABLE_OFFSET;
  do
  {
    while ( *(char *)(buildingPtr + 4) == -1 )
    {
      ++buildingIndex;
      buildingPtr += 467;
      if ( buildingIndex >= 100 )
        return;
    }
    Building_DebugDump((unsigned __int8 *)buildingPtr, buildingIndex++, a3);
    buildingPtr += 467;
  }
  while ( buildingIndex < 100 );
}
// 5202E4: using guessed type int gameData;

//----- (0041EAF0) --------------------------------------------------------
unsigned __int8 * Building_NewTurn(
        int a1,
        unsigned __int8 *buildingPtr,
        DWORD a3,
        double a4)
{
  int i; // edi
  int v6; // ecx
  int v7; // ecx
  __int16 constructionDelta; // dx
  int j; // eax
  int slotUnitType; // ecx
  int v12; // ecx
  int buildingType; // eax

  Debug_Log(a1, (char)buildingPtr, a3, (int)aBuilding_newtu);
  for ( i = 0; i != 46700; i += 467 )
  {
    v6 = *(char *)(gameData + i + 509678);
    if ( v6 != -1 )
    {
      v6 = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(gameData + i + 509676) == g_CurrentPlayerIndex )
      {
        buildingPtr = (unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET + i);
        buildingPtr[420] &= ~1u;
        if ( *(__int16 *)(i + gameData + 509690) != -1 )
        {
          if ( *(_WORD *)(i + gameData + 509690) )
          {
            constructionDelta = 0;
            for ( j = 0; j != 372; j += 31 )
            {
              slotUnitType = *(__int16 *)(i + gameData + j + 509692);
              if ( slotUnitType == 17 )
              {
                slotUnitType = (unsigned __int8)g_BuilderConstructionProgressPerTurn;
                constructionDelta += (unsigned __int8)g_BuilderConstructionProgressPerTurn;
              }
            }
            *(_WORD *)(i + gameData + 509690) -= constructionDelta;
            if ( *(__int16 *)(i + gameData + 509690) < 0 )
            {
              *(_WORD *)(i + gameData + 509690) = 0;
              Building_FinishConstruction(buildingPtr, slotUnitType, (char)buildingPtr, a4);
            }
            else
            {
              Unit_UpdatePerTurn((int)buildingPtr, slotUnitType);
            }
          }
          else
          {
            if ( buildingPtr[4] == 2 )
            {
              Building_CollectGoldIncome((int)buildingPtr);
              Building_UpdatePopulationGrowth((int)buildingPtr);
              Building_UpdatePlagueState((unsigned int)buildingPtr);
              Prisoner_NewTurn((DWORD)buildingPtr, v12, (char)buildingPtr, a4);
            }
            buildingType = (char)buildingPtr[4];
            if ( buildingType == 2 || buildingType == 1 )
            {
              Building_ProcessUnitProductionTurn((int)buildingPtr, v6, (char)buildingPtr, a3, a4);
              Building_AutoFillOrUseGarrison(buildingPtr, a4);
              Unit_NewTurnRegen(buildingPtr);
              Building_RecoverGarrisonFatigueAndMorale(buildingPtr, a4);
            }
            else
            {
              Building_RecoverGarrisonFatigueAndMorale(buildingPtr, a4);
            }
          }
        }
      }
    }
  }
  LogAllBuildings(v6, (char)buildingPtr, a3);
  return Player_UpdateTechnologyLevelFromSettlements(g_CurrentPlayerIndex, v7, a3);
}
// 41EB6A: variable 'v6' is possibly undefined
// 41EB74: variable 'v7' is possibly undefined
// 41EBFF: variable 'a4' is possibly undefined
// 41EC2E: variable 'v12' is possibly undefined
// 512B58: using guessed type char g_BuilderConstructionProgressPerTurn;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0041EC70) --------------------------------------------------------
char  Building_GetInto(int buildingIndex, char a2, DWORD a3)
{
  int buildingPtr; // eax
  int previousResourceHandle; // edx
  int (*previousRenderHook)(); // ebx

  Debug_Log(buildingIndex, a2, a3, (int)aBuilding_getin);
  buildingPtr = UNIT_RECORD(buildingIndex);
  if ( !*(_WORD *)(buildingPtr + 16) )
  {
    if ( !*(_BYTE *)(buildingPtr + 4) )
    {
      previousResourceHandle = Render_SetResourceHandle(
                                 (int)&g_MainRenderDevice,
                                 (char *)RenderHook_DemoText == (char *)Render_DefaultRH);
      previousRenderHook = g_RenderHook;
      g_RenderHook = (int (*)())RenderHook_DemoText;
      Debug_Log(buildingIndex, (char)previousRenderHook, (DWORD)RenderHook_DemoText, (int)aSetrhS08x_4, aKeep_redraw, RenderHook_DemoText);
      UI_DemoTextPresent(buildingIndex, buildingIndex, (char)previousRenderHook, (DWORD)RenderHook_DemoText);
      Debug_Log(buildingIndex, (char)previousRenderHook, (DWORD)RenderHook_DemoText, (int)aUnsetrh08x_4, previousRenderHook);
      g_RenderHook = previousRenderHook;
      return Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
    }
    if ( (unsigned __int8)*(_BYTE *)(buildingPtr + 4) <= 2u )
    {
      previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
      previousRenderHook = g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(buildingIndex, (char)previousRenderHook, a3, (int)aSetrhS08x_5, aStdrh_3, Render_DefaultRH);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[castle] building_getinto_open building_idx=%d kind=%d owner=%d construction=%d\n",
          buildingIndex,
          *(unsigned __int8 *)(buildingPtr + 4),
          *(unsigned __int8 *)(buildingPtr + 2),
          *(__int16 *)(buildingPtr + 16));
      Castle_OpenManagementScreen(buildingIndex, (char)previousRenderHook);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[castle] building_getinto_return building_idx=%d\n", buildingIndex);
      Debug_Log(buildingIndex, (char)previousRenderHook, a3, (int)aUnsetrh08x_5, previousRenderHook);
      g_RenderHook = previousRenderHook;
      return Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
    }
  }
  return buildingPtr;
}
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;

//----- (0041EDD0) --------------------------------------------------------
signed int  Building_BuildSchool(char *a1, char a2, DWORD a3)
{
  int buildingPtr; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a2, a3, (int)aBuilding_bui_0, *a1);
  LOBYTE(ownerPlayer) = *(_BYTE *)(buildingPtr + 2);
  goldCost = 400;
  if ( !*(_DWORD *)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 300;
  if ( (*(_BYTE *)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(buildingPtr + 416) | BUILDING_ADDON_FLAG_SCHOOL;
  *(_DWORD *)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 41EDEF: variable 'v3' is possibly undefined
// 41EDF2: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041EE70) --------------------------------------------------------
signed int  Building_BuildWorkshop(char a1, DWORD a2)
{
  int buildingPtr; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a1, a2, (int)aBuilding_bui_4);
  LOBYTE(ownerPlayer) = *(_BYTE *)(buildingPtr + 2);
  goldCost = 190;
  if ( !*(_DWORD *)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 90;
  if ( (*(_BYTE *)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(buildingPtr + 416) | BUILDING_ADDON_FLAG_WORKSHOP;
  *(_DWORD *)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 41EE8F: variable 'v3' is possibly undefined
// 41EE92: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041EF10) --------------------------------------------------------
signed int  Building_BuildBarracks(int a1, char a2, DWORD a3)
{
  int buildingPtr; // edx
  unsigned int availableGold; // ecx
  signed int result; // eax

  Debug_Log(a1, a2, a3, (int)aBuilding_bui_2);
  if ( (*(_BYTE *)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(buildingPtr + 438);
  if ( availableGold < 0xC8 )
    return 0;
  *(_DWORD *)(buildingPtr + 438) = availableGold - 200;
  *(_BYTE *)(buildingPtr + 416) |= BUILDING_ADDON_FLAG_BARRACKS;
  result = 1;
  *(_BYTE *)(buildingPtr + 420) |= 1u;
  return result;
}
// 41EF29: variable 'v4' is possibly undefined

//----- (0041EF80) --------------------------------------------------------
signed int  Building_BuildHospital(char a1, DWORD a2)
{
  int buildingPtr; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a1, a2, (int)aBuilding_bui_3);
  LOBYTE(ownerPlayer) = *(_BYTE *)(buildingPtr + 2);
  goldCost = 200;
  if ( !*(_DWORD *)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 100;
  if ( (*(_BYTE *)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(buildingPtr + 416) | BUILDING_ADDON_FLAG_HOSPITAL;
  *(_DWORD *)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 41EF9F: variable 'v3' is possibly undefined
// 41EFA2: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041F020) --------------------------------------------------------
signed int  Building_BuildSmiths(char a1, DWORD a2)
{
  int buildingPtr; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a1, a2, (int)aBuilding_bui_1);
  LOBYTE(ownerPlayer) = *(_BYTE *)(buildingPtr + 2);
  goldCost = 230;
  if ( !*(_DWORD *)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 130;
  if ( (*(_BYTE *)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(buildingPtr + 416) | BUILDING_ADDON_FLAG_SMITHS;
  *(_DWORD *)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 41F03F: variable 'v3' is possibly undefined
// 41F042: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041F0C0) --------------------------------------------------------
signed int  Building_FindFreeAdjacentSpawnTile(unsigned __int8 *buildingPtr, _DWORD *outRow, int a3, _DWORD *outColumn)
{
  int attemptCount; // ebp
  int offsetTableIndex; // esi
  int candidateRow; // ebx
  int candidateColumn; // ecx

  attemptCount = 0;
  offsetTableIndex = 0;
  Debug_Log(a3, (char)outColumn, 0, (int)aBuildingFindFreePlaceNear);
  do
  {
    candidateRow = g_BuildingSpawnTileSearchOffsetsX[offsetTableIndex] + *buildingPtr;
    candidateColumn = g_BuildingSpawnTileSearchOffsetsY[offsetTableIndex] + buildingPtr[1];
    if ( *(unsigned __int16 *)(TILE_INDEX(candidateRow, candidateColumn)) == 0xFFFF && Map_GetUnitTileMoveCostOrZero(buildingPtr[2], 31, candidateColumn, candidateRow) )
      break;
    offsetTableIndex += 2;
    ++attemptCount;
  }
  while ( offsetTableIndex < 24 );
  if ( attemptCount == 12 )
    return 0;
  *outRow = g_BuildingSpawnTileSearchOffsetsX[2 * attemptCount] + *buildingPtr;
  *outColumn = g_BuildingSpawnTileSearchOffsetsY[2 * attemptCount] + buildingPtr[1];
  return 1;
}
// 513A10: using guessed type int dword_513A10[];
// 513A14: using guessed type int dword_513A14[23];
// 5202E4: using guessed type int gameData;

//----- (0041F1A0) --------------------------------------------------------
signed int  Building_Transfer(int buildingIndex, int targetStackIndex, int transferGold, int transferAmount, double a5)
{
  int buildingByteOffset; // edx
  unsigned __int16 populationField; // ax
  signed int result; // eax
  unsigned __int8 *v9; // ecx
  int v10; // ecx
  unsigned int v11; // ebx
  int v12; // ecx
  int squadCount; // eax
  __int16 *squadTemplatePtr; // esi
  int v15; // eax
  __int16 *partialSquadTemplatePtr; // esi
  int v17; // edx
  __int64 v18; // rtt
  int *pathTrack; // esi
  int pathNode; // edx
  int currentPopulation; // eax
  int newPopulation; // eax
  unsigned __int8 *v23; // edx
  int buildingType; // ebx
  int newPathLen; // eax
  int pathStartTile; // edx
  __int16 *v27; // ecx
  __int16 *pathDest; // edi
  __int16 *v29; // eax
  __int16 tileOccupantValue; // dx
  unsigned __int8 *v31; // ebx
  unsigned __int8 *v32; // ebx
  int v33; // ecx
  __int16 *v34; // edx
  __int16 *v35; // edx
  int spawnRow; // [esp+0h] [ebp-2Ch] BYREF
  int spawnColumn; // [esp+4h] [ebp-28h] BYREF
  __int16 *newStackPtr; // [esp+8h] [ebp-24h]
  int buildingTileByteOffset; // [esp+Ch] [ebp-20h]
  int targetUnitRecord; // [esp+10h] [ebp-1Ch]
  int savedBuildingIndex; // [esp+14h] [ebp-18h]
  int savedTargetStack; // [esp+18h] [ebp-14h]
  int transferGoldFlag; // [esp+1Ch] [ebp-10h]
  int amount; // [esp+20h] [ebp-Ch]
  int i; // [esp+24h] [ebp-8h]
  unsigned __int8 *buildingPtr; // [esp+28h] [ebp-4h]
  _DWORD savedregs[3]; // [esp+2Ch] [ebp+0h] BYREF

  savedBuildingIndex = buildingIndex;
  savedTargetStack = targetStackIndex;
  amount = transferAmount;
  transferGoldFlag = transferGold;
  Debug_Log(transferGold, targetStackIndex, (DWORD)savedregs, (int)aBuildingTransfer);
  buildingPtr = (unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET + buildingByteOffset);
  targetUnitRecord = 0;
  if ( targetStackIndex != -1 )
    targetUnitRecord = UNIT_RECORD(targetStackIndex);
  if ( transferGoldFlag && (unsigned int)amount > *(_DWORD *)(buildingPtr + 438) )
    return 0;
  if ( !transferGoldFlag )
  {
    populationField = *((_WORD *)buildingPtr + 215);
    HIBYTE(populationField) &= 0xFu;
    if ( populationField < amount )
      return 0;
  }
  if ( Building_FindFreeAdjacentSpawnTile(buildingPtr, &spawnRow, gameData + BUILDING_TABLE_OFFSET + buildingByteOffset, &spawnColumn) != 1 )
    return 0;
  WorldMap_DisableFrameRedraw();
  *(_WORD *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) = -1;
  v9 = buildingPtr;
  *(_WORD *)(gameData + TILE_ROW_STRIDE * (*buildingPtr + 1) + 2 * buildingPtr[1] + TILE_MAP_OFFSET) = -1;
  *(_WORD *)(200 * (*v9 + 1) + gameData + 2 * v9[1] + 556376) = -1;
  *(_WORD *)(200 * *v9 + gameData + 2 * v9[1] + 556376) = -1;
  result = Unit_Create((char)((transferGoldFlag == 0) + 31), v9[2], *v9, 0, v9[1]);
  if ( result )
  {
    newStackPtr = (__int16 *)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) + gameData + UNIT_STACK_TABLE_OFFSET);
    UnitStack_ClearRemainingActionPoints(newStackPtr, (DWORD)savedregs, a5);
    v11 = v10 + 6;
    v12 = 100;
    squadCount = amount / 100;
    for ( i = 1; squadCount >= i; ++i )
    {
      squadTemplatePtr = newStackPtr + 3;
      qmemcpy((void *)v11, newStackPtr + 3, 0x1Cu);
      squadTemplatePtr += 14;
      v12 = 0;
      *(_WORD *)(v11 + 28) = *squadTemplatePtr;
      *(_BYTE *)(v11 + 30) = *((_BYTE *)squadTemplatePtr + 2);
      v11 += 31;
    }
    if ( i <= 10 )
    {
      v15 = amount;
      partialSquadTemplatePtr = newStackPtr + 3;
      v17 = amount;
      qmemcpy((void *)v11, newStackPtr + 3, 0x1Cu);
      partialSquadTemplatePtr += 14;
      *(_WORD *)(v11 + 28) = *partialSquadTemplatePtr;
      *(_BYTE *)(v11 + 30) = *((_BYTE *)partialSquadTemplatePtr + 2);
      v12 = 100;
      LODWORD(v18) = v15;
      HIDWORD(v18) = v17 >> 31;
      LOBYTE(v15) = (int)(100 * (v18 % 100)) / 100;
      *(_BYTE *)(v11 + 9) = v15;
      if ( !(_BYTE)v15 )
        *(_WORD *)v11 = -1;
    }
    if ( transferGoldFlag )
    {
      *(_DWORD *)(buildingPtr + 438) -= amount;
    }
    else
    {
      HIWORD(currentPopulation) = HIWORD(buildingPtr);
      LOWORD(currentPopulation) = *((_WORD *)buildingPtr + 215);
      BYTE1(currentPopulation) &= 0xFu;
      newPopulation = currentPopulation - amount;
      v23 = buildingPtr;
      LOWORD(v11) = *((_WORD *)buildingPtr + 215);
      v11 &= 0xFFFFF000;
      BYTE1(newPopulation) &= 0xFu;
      *((_WORD *)buildingPtr + 215) = v11;
      v12 = newPopulation | v11;
      *((_WORD *)v23 + 215) = newPopulation | v11;
    }
    if ( targetUnitRecord
      && (pathTrack = (int *)Building_GenerateApproachTrack(
                         *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])),
                         savedTargetStack,
                         (int)buildingPtr,
                         v11,
                         (DWORD)savedregs)) != 0 )
    {
      while ( 1 )
      {
        pathNode = pathTrack[*pathTrack];
        if ( (_WORD)pathNode != *(_WORD *)buildingPtr )
        {
          buildingType = (char)buildingPtr[4];
          if ( buildingType != 1 && buildingType != 2 )
            break;
          if ( (unsigned __int8)pathNode < *buildingPtr
            || (unsigned __int8)pathNode > *buildingPtr + 1
            || BYTE1(pathNode) < buildingPtr[1]
            || BYTE1(pathNode) > buildingPtr[1] + 1 )
          {
            break;
          }
        }
        --*pathTrack;
      }
      newPathLen = *pathTrack - 1;
      *pathTrack = newPathLen;
      pathStartTile = pathTrack[newPathLen + 1];
      v27 = newStackPtr;
      *newStackPtr = (unsigned __int8)pathStartTile;
      v27[1] = BYTE1(pathStartTile);
      buildingTileByteOffset = 2 * buildingPtr[1] + gameData + 200 * *buildingPtr;
      pathDest = newStackPtr + 158;
      *(_WORD *)(2 * BYTE1(pathStartTile) + TILE_ROW_STRIDE * (unsigned __int8)pathStartTile + gameData + TILE_MAP_OFFSET) = *(_WORD *)(buildingTileByteOffset + 556374);
      v29 = newStackPtr;
      qmemcpy(pathDest, pathTrack, UNIT_STACK_PATH_BYTES);
      UnitStack_SetReadyFlags((int)v29);
    }
    else
    {
      Building_FindFreeAdjacentSpawnTile(buildingPtr, &spawnRow, v12, &spawnColumn);
      v35 = newStackPtr;
      *newStackPtr = spawnRow;
      v35[1] = spawnColumn;
      *(_WORD *)(2 * spawnColumn + TILE_ROW_STRIDE * spawnRow + gameData + TILE_MAP_OFFSET) = *(_WORD *)(TILE_INDEX(*buildingPtr, buildingPtr[1]));
    }
    tileOccupantValue = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    v31 = buildingPtr;
    *(_WORD *)(TILE_ROW_STRIDE * (*buildingPtr + 1) + gameData + 2 * buildingPtr[1] + TILE_MAP_OFFSET) = tileOccupantValue;
    *(_WORD *)(200 * (*v31 + 1) + gameData + 2 * buildingPtr[1] + 556376) = tileOccupantValue;
    v32 = buildingPtr;
    *(_WORD *)(200 * *buildingPtr + gameData + 2 * buildingPtr[1] + 556376) = tileOccupantValue;
    Render_LoadResourceSprite_v2();
    if ( (v32[435] & 7) != 0 && !transferGoldFlag )
      UnitStack_SetPlagueFlag((int)newStackPtr);
    Rules_LinkArmyFact(newStackPtr, (int)newStackPtr, v33, a5, (char)v32, (DWORD)savedregs);
    if ( !*(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)v34 + 4) + 140051) )
      Rules_LogBuildingTransferFact(*(unsigned __int16 *)(TILE_INDEX(*v34, newStackPtr[1])), savedBuildingIndex, savedTargetStack);
    return 1;
  }
  return result;
}
// 41F1E0: variable 'v6' is possibly undefined
// 41F3C8: variable 'v10' is possibly undefined
// 41F6FE: variable 'v33' is possibly undefined
// 41F705: variable 'v34' is possibly undefined
// 41F77D: variable 'v12' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041F810) --------------------------------------------------------
int  Building_CalcGarrisonAverageHealthPercent(int buildingPtr)
{
  int slotsEnd; // ebx
  int damageSum; // edx
  int slotDamage; // ecx

  slotsEnd = buildingPtr + 7;
  damageSum = 0;
  do
  {
    slotDamage = *(unsigned __int8 *)(buildingPtr + 422);
    ++buildingPtr;
    damageSum += slotDamage;
  }
  while ( buildingPtr != slotsEnd );
  return 100 - damageSum / 7;
}

int  UI_DrawUnitStatsValues(int a1)
{
  return Building_CalcGarrisonAverageHealthPercent(a1);
}

//----- (0041F850) --------------------------------------------------------
BOOL  Building_CanStartUpgrade(unsigned __int8 *buildingPtr)
{
  return buildingPtr[421] < 2u && buildingPtr[421] < (buildingPtr[444] & 7) - 1 && !buildingPtr[429];
}

//----- (0041F890) --------------------------------------------------------
BOOL  Building_TryStartUpgrade(unsigned __int8 *buildingPtr)
{
  BOOL result; // eax
  int buildingRecord; // edx

  result = Building_CanStartUpgrade(buildingPtr);
  if ( result )
  {
    if ( (unsigned int)(unsigned __int8)g_BuildingUpgradeCostByLevel[4 * *(unsigned __int8 *)(buildingRecord + 421)] <= *(_DWORD *)(buildingRecord + 438) )
    {
      *(_BYTE *)(buildingRecord + 429) = g_BuildingUpgradeDurationByLevel[4 * *(unsigned __int8 *)(buildingRecord + 421)];
      result = 1;
      *(_DWORD *)(buildingRecord + 438) -= (unsigned __int8)g_BuildingUpgradeCostByLevel[4 * *(unsigned __int8 *)(buildingRecord + 421)];
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 41F8A0: variable 'v2' is possibly undefined

//----- (0041F900) --------------------------------------------------------
_DWORD * Unit_CaptureBuilding(int capturingStackIndex, DWORD buildingIndex, int a3, signed int j, double a5)
{
  DWORD buildingByteOffset; // ebx
  int buildingPtr; // ecx
  DWORD buildingBase; // eax
  unsigned __int8 buildingTechLevel; // bl
  unsigned __int8 playerTechLevel; // bh
  char v12; // dh
  int v13; // edx
  int turnCounter; // ebx
  int ownerPlayerDataOffset; // eax
  DWORD buildingRecordPtr; // ecx
  DWORD personageSlotPtr; // ebx
  int i; // edi
  int personageType; // edx
  int v20; // ecx
  int k; // edi
  int v22; // edx
  int v23; // ecx
  DWORD v24; // ebx
  DWORD v25; // ecx
  int m; // edi
  int savedBuildingOffset; // [esp+4h] [ebp-24h]

  buildingByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
  v13 = buildingByteOffset;
  Debug_Log(a3, -45 * buildingIndex, buildingIndex, (int)aUnit_capturebu);
  buildingPtr = buildingByteOffset + gameData + BUILDING_TABLE_OFFSET;
  if ( *(_WORD *)(buildingByteOffset + gameData + 509690) )
    return Building_Destroy(buildingByteOffset + gameData + BUILDING_TABLE_OFFSET, buildingByteOffset, buildingIndex, a5);
  *(_BYTE *)(buildingByteOffset + gameData + 509676) = *(_BYTE *)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + 147178);
  buildingBase = buildingByteOffset + gameData;
  buildingTechLevel = *(_BYTE *)(buildingByteOffset + gameData + 510118) & 7;
  playerTechLevel = *(_BYTE *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + 147178) + gameData + 140071);
  if ( buildingTechLevel < playerTechLevel )
  {
    v12 = *(_BYTE *)(buildingBase + 510118) & 0xF8;
    *(_BYTE *)(buildingBase + 510118) = v12;
    *(_BYTE *)(buildingBase + 510118) = playerTechLevel & 7 | v12;
  }
  Rules_SyncCastleFactOwner(UNIT_RECORD(buildingIndex), buildingPtr, a5);
  savedBuildingOffset = v13;
  turnCounter = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
  Rules_LogBuildingCapturedFact(*(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * capturingStackIndex + 147178), buildingIndex, turnCounter);
  ownerPlayerDataOffset = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(savedBuildingOffset + gameData + 509676) + gameData;
  if ( buildingIndex == *(_DWORD *)(ownerPlayerDataOffset + 140067) )
    *(_DWORD *)(ownerPlayerDataOffset + 140067) = -1;
  Building_UnitGetInto(capturingStackIndex, buildingIndex, turnCounter, buildingIndex, a5);
  buildingRecordPtr = buildingPtr;
  personageSlotPtr = buildingRecordPtr;
  for ( i = 0; i < 3; ++i )
  {
    personageType = *(char *)(personageSlotPtr + 445);
    if ( personageType != -1 && *(_BYTE *)(personageSlotPtr + 446) == *(_BYTE *)(buildingRecordPtr + 2) )
    {
      Building_CreateSpecialPersonageGarrisonUnit(buildingRecordPtr, personageType, buildingRecordPtr, (char)i, a5);
      Prisoner_Kill(buildingRecordPtr, (char)i, buildingIndex);
    }
    personageSlotPtr += 6;
  }
  for ( k = 0; k < 12; ++k )
  {
    Building_ClearGarrisonTrainingTimer(buildingRecordPtr, k);
    v22 = k;
    Building_ClearGarrisonRepairTimer(buildingRecordPtr, v22);
  }
  v24 = BUILDING_RECORD_SIZE * buildingIndex;
  v25 = BUILDING_RECORD_SIZE * buildingIndex;
  for ( m = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * buildingIndex + BUILDING_TABLE_OFFSET); m <= *(unsigned __int8 *)(v24 + gameData + BUILDING_TABLE_OFFSET) + 1; ++m )
  {
    for ( j = *(unsigned __int8 *)(v24 + gameData + 509675); j <= *(unsigned __int8 *)(v25 + gameData + 509675) + 1; ++j )
      MiniMap_DrawTileCell((void *)m, j);
  }
  return (_DWORD *)MiniMap_RedrawTileRect(m, j, j + 1, m + 1);
}
// 41FA10: variable 'v13' is possibly undefined
// 41FA69: variable 'v16' is possibly undefined
// 41FA8F: variable 'v20' is possibly undefined
// 41FAAE: variable 'v23' is possibly undefined
// 41FAEF: variable 'v25' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041FB50) --------------------------------------------------------
_DWORD * Building_Destroy(int a1, char a2, DWORD a3, double a4)
{
  int buildingPtr; // ecx
  int scanIndex; // eax
  int recordPtr; // ebx
  int recordOffset; // edx
  int writeIndex; // edx
  int writeIndex2; // eax
  int occupiedSlots[11]; // [esp+0h] [ebp-48h] BYREF
  int slotIndex; // [esp+2Ch] [ebp-1Ch]
  int outCount; // [esp+30h] [ebp-18h]

  Debug_Log(a1, a2, a3, (int)aBuilding_destr);
  if ( *(__int16 *)(buildingPtr + 18) != -1 )
  {
    slotIndex = 0;
    outCount = 0;
    while ( slotIndex < 12 && outCount < 10 )
    {
      if ( *(__int16 *)(buildingPtr + 31 * slotIndex + 18) != -1 )
      {
        writeIndex = outCount++;
        occupiedSlots[writeIndex] = slotIndex;
      }
      ++slotIndex;
    }
    if ( outCount < 10 )
      occupiedSlots[outCount] = -1;
    Building_UnitsLeave((unsigned __int8 *)buildingPtr, occupiedSlots, a4);
    if ( slotIndex < 12 && *(__int16 *)(buildingPtr + 31 * slotIndex + 18) != -1 )
    {
      outCount = 0;
      while ( slotIndex < 12 )
      {
        if ( *(__int16 *)(buildingPtr + 31 * slotIndex + 18) != -1 )
        {
          writeIndex2 = outCount++;
          occupiedSlots[writeIndex2] = slotIndex;
        }
        ++slotIndex;
      }
      occupiedSlots[outCount] = -1;
      Building_UnitsLeave((unsigned __int8 *)buildingPtr, occupiedSlots, a4);
    }
  }
  *(_WORD *)(buildingPtr + 16) = -1;
  scanIndex = 0;
LABEL_3:
  recordPtr = UNIT_RECORD(scanIndex);
  if ( (unsigned int)*(char *)(recordPtr + 4) >= 4
    || *(__int16 *)(recordPtr + 16) == -1
    || (recordOffset = gameData + BUILDING_RECORD_SIZE * scanIndex, !*(_BYTE *)(recordOffset + 509678))
    || *(_BYTE *)(recordOffset + 509676) != *(_BYTE *)(buildingPtr + 2) )
  {
    while ( ++scanIndex < 100 )
    {
      if ( scanIndex >= 0 )
        goto LABEL_3;
    }
  }
  if ( scanIndex == 100 )
    *(_BYTE *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + 141443) = -1;
  return Rules_RetractCastleFact((unsigned __int8 *)buildingPtr, a4);
}
// 41FCFF: conditional instruction was optimized away because eax.4<64u
// 41FB97: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 41FB65: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041FD10) --------------------------------------------------------
int  Building_CalcRemainingConstructionTurns(int buildingPtr)
{
  int buildingBase; // esi
  int slotsEnd; // ebx
  int progressPerTurn; // ecx

  buildingBase = buildingPtr;
  if ( !*(_WORD *)(buildingPtr + 16) )
    return 0;
  slotsEnd = buildingPtr + 372;
  progressPerTurn = 0;
  do
  {
    if ( *(_WORD *)(buildingPtr + 18) == UNIT_TYPE_BUILDER )
      progressPerTurn += (unsigned __int8)g_BuilderConstructionProgressPerTurn;
    buildingPtr += 31;
  }
  while ( buildingPtr != slotsEnd );
  if ( progressPerTurn )
    return *(__int16 *)(buildingBase + 16) / progressPerTurn + 1;
  else
    return 50;
}
// 512B58: using guessed type char g_BuilderConstructionProgressPerTurn;

//----- (0041FD70) --------------------------------------------------------
signed int  Building_FindRandomOwnedCompletedCastle(ownerPlayer, a2)
int ownerPlayer;
int a2;
{
  int matchCount; // ecx
  int buildingIndex; // eax
  int buildingByteOffset; // ebx
  int recordBase; // edx
  char matchList[113]; // [esp+1h] [ebp-79h]
  int v10; // [esp+72h] [ebp-8h]

  v10 = a2;
  matchCount = 0;
  buildingIndex = 0;
  buildingByteOffset = 0;
  do
  {
    recordBase = buildingByteOffset + gameData;
    if ( *(unsigned __int8 *)(buildingByteOffset + gameData + 509676) == ownerPlayer && *(_BYTE *)(recordBase + 509678) == 2 && !*(_WORD *)(recordBase + 509690) )
      matchList[++matchCount] = buildingIndex;
    ++buildingIndex;
    buildingByteOffset += 467;
  }
  while ( buildingIndex < 100 );
  if ( matchCount )
    return (unsigned __int8)matchList[Rng_RandRange(0, matchCount - 1) + 1];
  else
    return -1;
}

signed int  Unit_FindById(int a1)
{
  return Building_FindRandomOwnedCompletedCastle(a1, 0);
}
// 5202E4: using guessed type int gameData;

//----- (0041FDF0) --------------------------------------------------------
void * Building_ShowHoverInfoPopup(unsigned __int8 *buildingPtr, char spriteSetId, int a3)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9; // ecx
  __int16 v10; // ax
  int SpriteForChar; // eax
  int languageIndex; // ecx
  int addonSpriteId; // eax
  int textBaseY; // esi
  int v15; // ecx
  int v16; // ecx
  int prisonerRowY; // edi
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx
  int spriteCharIndex; // edx
  int spriteRenderer; // edi
  __int16 v24; // ax
  _DWORD *v25; // edi
  void *result; // eax
  int spriteId; // eax
  int localizedName; // edi
  int v29; // edx
  unsigned __int16 popupRight; // [esp+3Ch] [ebp-48h]
  unsigned __int16 v31; // [esp+3Ch] [ebp-48h]
  unsigned __int16 v32; // [esp+40h] [ebp-44h]
  unsigned __int16 v33; // [esp+44h] [ebp-40h]
  int buildingNamesByLang[3]; // [esp+48h] [ebp-3Ch]
  _DWORD *spriteSet; // [esp+54h] [ebp-30h] BYREF
  int panelY; // [esp+58h] [ebp-2Ch]
  int v37; // [esp+5Ch] [ebp-28h]
  _DWORD *surface; // [esp+60h] [ebp-24h]
  void *savedRenderDevice; // [esp+64h] [ebp-20h]
  int panelX; // [esp+68h] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  loadedSpriteSet = (_DWORD *)Mem_Alloc(4112, v4, spriteSetId, (DWORD)buildingPtr);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, spriteSetId);
  spriteSet = loadedSpriteSet;
  panelY = 100;
  panelX = 100;
  Surface = (_DWORD *)Mem_Alloc(188, 100, spriteSetId, (DWORD)buildingPtr);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)spriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)spriteSet, 0);
    Surface = Render_CreateSurface(v9, SpriteHeight, SpriteWidth);
  }
  surface = Surface;
  popupRight = panelX + DLX_GetSpriteWidth((int)spriteSet, 0) - 1;
  v10 = DLX_GetSpriteHeight((int)spriteSet, 0);
  Render_FillRect(0, surface, (unsigned __int16)panelX, (unsigned __int16)panelY, panelY + v10 - 1, popupRight, 0, 0);
  Render_ReleaseSurface(7, (DWORD)buildingPtr);
  if ( buildingPtr[4] )
  {
    SpriteForChar = DLX_GetSpriteForChar((int)spriteSet, buildingPtr[2] != g_CurrentPlayerIndex);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      panelX,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  else
  {
    spriteId = DLX_GetSpriteForChar((int)spriteSet, 6);
    a3 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(a3 + 52))(
      panelX,
      spriteId,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  languageIndex = (char)buildingPtr[4];
  if ( buildingPtr[4] )
  {
    UI_DrawTextFmt(a3, panelY + 10, panelY + 235, panelX + 5, 3, (int)(buildingPtr + 5));
    if ( buildingPtr[2] == g_CurrentPlayerIndex )
    {
      if ( (buildingPtr[435] & 7) != 0 )
      {
        addonSpriteId = DLX_GetSpriteForChar((int)spriteSet, 2);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          panelX + 37,
          addonSpriteId,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      textBaseY = panelY;
      UI_DrawTextFmt(a3, panelY, panelY + 89, panelX + 25, 2, (int)aD_21);
      UI_DrawTextFmt(a3, textBaseY, textBaseY + 150, v15, 2, (int)aD_22);
      UI_DrawTextFmt(a3, textBaseY, textBaseY + 210, v16, 2, (int)aD_23);
    }
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(a3, panelY, panelY + 89, panelX + 62, 2, (int)aD_24);
    Building_CountGarrison((int)buildingPtr);
    Building_DrawGarrisonRow((int)buildingPtr);
    prisonerRowY = panelY;
    v37 = panelY + 150;
    UI_DrawTextFmt(panelY, panelY, panelY + 150, v18, 2, (int)aD_25);
    Building_CountPrisoners((int)buildingPtr);
    UI_DrawTextFmt(prisonerRowY, prisonerRowY, prisonerRowY + 208, v19, 2, (int)aD_26);
    UI_DrawTextFmt(prisonerRowY, prisonerRowY, v20, panelX + 99, 2, (int)aD_27);
    spriteCharIndex = panelY ^ v21;
    LOBYTE(spriteCharIndex) = buildingPtr[421];
    DLX_GetSpriteForChar((int)spriteSet, spriteCharIndex + 3);
    spriteRenderer = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(spriteRenderer + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(spriteRenderer, panelY, panelY + 150, panelX + 99, 2, (int)aD_28);
    UI_DrawUnitStatsValues((int)buildingPtr);
    UI_DrawTextFmt(spriteRenderer, panelY, panelY + 205, panelX + 99, 2, (int)aD_29);
  }
  else
  {
    buildingNamesByLang[0] = (int)UI_Locale_BuildingNames_A[0];
    buildingNamesByLang[1] = (int)UI_Locale_BuildingNames_A[1];
    buildingNamesByLang[2] = (int)UI_Locale_BuildingNames_A[2];
    LOBYTE(languageIndex) = g_LanguageIndex;
    localizedName = buildingNamesByLang[languageIndex];
    UI_DrawTextFmt(localizedName, panelY + 10, panelY + 175, panelX + 5, 3, localizedName);
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(localizedName, panelY, panelY + 87, panelX + 25, 2, (int)aD_30);
    Building_CountGarrison((int)buildingPtr);
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(localizedName, panelY, panelY + 150, v29, 2, (int)aD_31);
  }
  Render_Begin((int)g_RenderState, 0);
  v33 = panelX;
  v32 = panelY;
  v31 = DLX_GetSpriteWidth((int)spriteSet, 0) - 1;
  v24 = DLX_GetSpriteHeight((int)spriteSet, 0);
  v25 = surface;
  Render_FillRect(surface, 0, 0, 0, v24 - 1, v31, v32, v33);
  if ( v25 )
    (*(void (**)(void))v25[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  Render_Present((int)g_RenderState);
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 41FE1E: variable 'v4' is possibly undefined
// 41FE6E: variable 'v9' is possibly undefined
// 41FFF0: variable 'v15' is possibly undefined
// 420012: variable 'v16' is possibly undefined
// 420074: variable 'v18' is possibly undefined
// 420094: variable 'v19' is possibly undefined
// 4200BD: variable 'v20' is possibly undefined
// 4200C5: variable 'v21' is possibly undefined
// 42029B: variable 'v29' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513B44: using guessed type char *off_513B44[2];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004202C0) --------------------------------------------------------
int  Building_ShowConstructionProgressDialog(DWORD buildingRecord, char spriteSetId, DWORD a3, double a4)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 v11; // ax
  int SpriteForChar; // eax
  int textY; // ebx
  int v14; // edx
  int buildingNameStr; // edi
  int v16; // edx
  int v17; // edx
  int remainingTurns; // eax
  int v19; // ecx
  int turnsTextX; // ecx
  int stopBtnXMin; // edi
  int okBtnYMin; // ebx
  signed int okBtnXMax; // ebp
  int okBtnYMax; // esi
  int v25; // ecx
  __int16 v26; // ax
  unsigned __int16 spriteRightX; // [esp+10h] [ebp-C4h]
  unsigned __int16 spriteWidthMinus1; // [esp+10h] [ebp-C4h]
  unsigned __int16 spriteTopY; // [esp+14h] [ebp-C0h]
  unsigned __int16 spriteLeftX; // [esp+18h] [ebp-BCh]
  int namesTableE[12]; // [esp+1Ch] [ebp-B8h] BYREF
  int namesTableG[3]; // [esp+4Ch] [ebp-88h]
  int namesTableH[3]; // [esp+58h] [ebp-7Ch]
  int namesTableB[3]; // [esp+64h] [ebp-70h] BYREF
  int namesTableC[3]; // [esp+70h] [ebp-64h]
  int namesTableD[3]; // [esp+7Ch] [ebp-58h]
  int namesTableF[3]; // [esp+88h] [ebp-4Ch]
  _DWORD *spriteSet; // [esp+94h] [ebp-40h] BYREF
  _DWORD *surface; // [esp+98h] [ebp-3Ch]
  int centeredY; // [esp+9Ch] [ebp-38h]
  int stopBtnYMin; // [esp+A0h] [ebp-34h]
  int stopBtnXMax; // [esp+A4h] [ebp-30h]
  int okBtnXMin; // [esp+A8h] [ebp-2Ch]
  int stopBtnYMax; // [esp+ACh] [ebp-28h]
  void *savedRenderDevice; // [esp+B0h] [ebp-24h]
  DWORD buildingPtr; // [esp+B4h] [ebp-20h]
  int centeredX; // [esp+B8h] [ebp-1Ch]

  buildingPtr = buildingRecord;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  loadedSpriteSet = (_DWORD *)Mem_Alloc(4112, v4, spriteSetId, a3);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, spriteSetId);
  spriteSet = loadedSpriteSet;
  centeredY = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)loadedSpriteSet, 0)) / 2;
  centeredX = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)spriteSet, 0)) / 2;
  Surface = (_DWORD *)Mem_Alloc(188, v6, spriteSetId, a3);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)spriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)spriteSet, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  surface = Surface;
  spriteRightX = centeredX + DLX_GetSpriteWidth((int)spriteSet, 0) - 1;
  v11 = DLX_GetSpriteHeight((int)spriteSet, 0);
  Render_FillRect(0, surface, (unsigned __int16)centeredX, (unsigned __int16)centeredY, centeredY + v11 - 1, spriteRightX, 0, 0);
  Render_ReleaseSurface(17, a3);
  SpriteForChar = DLX_GetSpriteForChar((int)spriteSet, 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    centeredX,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  namesTableB[0] = (int)UI_Locale_BuildingNames_B[0];
  namesTableB[1] = (int)UI_Locale_BuildingNames_B[1];
  namesTableB[2] = (int)UI_Locale_BuildingNames_B[2];
  namesTableC[0] = (int)UI_Locale_BuildingNames_C[0];
  namesTableC[1] = (int)UI_Locale_BuildingNames_C[1];
  namesTableC[2] = (int)UI_Locale_BuildingNames_C[2];
  namesTableD[0] = (int)UI_Locale_BuildingNames_D[0];
  namesTableD[1] = (int)UI_Locale_BuildingNames_D[1];
  namesTableD[2] = (int)UI_Locale_BuildingNames_D[2];
  qmemcpy(namesTableE, UI_Locale_BuildingNames_E, sizeof(namesTableE));
  namesTableF[0] = (int)UI_Locale_BuildingNames_F[0];
  namesTableF[1] = (int)UI_Locale_BuildingNames_F[1];
  namesTableF[2] = (int)UI_Locale_BuildingNames_F[2];
  namesTableG[0] = (int)UI_Locale_BuildingNames_G[0];
  namesTableG[1] = (int)UI_Locale_BuildingNames_G[1];
  namesTableG[2] = (int)UI_Locale_BuildingNames_G[2];
  namesTableH[0] = (int)UI_Locale_BuildingNames_H[0];
  namesTableH[1] = (int)UI_Locale_BuildingNames_H[1];
  namesTableH[2] = (int)UI_Locale_BuildingNames_H[2];
  textY = centeredY + 30;
  UI_DrawTextFmt((int)namesTableB, centeredY + 30, centeredY + 250, centeredX + 12, 3, namesTableB[(unsigned __int8)g_LanguageIndex]);
  UI_DrawTextFmt((int)namesTableB, textY, v14, centeredX + 32, 3, namesTableC[(unsigned __int8)g_LanguageIndex]);
  buildingNameStr = namesTableE[4 * *(char *)(buildingPtr + 4) + (unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(buildingNameStr, textY, v16, centeredX + 52, 3, namesTableD[(unsigned __int8)g_LanguageIndex]);
  remainingTurns = Building_CalcRemainingConstructionTurns(buildingPtr);
  turnsTextX = v19 + 77;
  if ( remainingTurns == 1 )
  {
    UI_DrawTextFmt(buildingNameStr, textY, v17, turnsTextX, 3, namesTableF[(unsigned __int8)g_LanguageIndex]);
  }
  else if ( remainingTurns > 4 )
  {
    UI_DrawTextFmt(buildingNameStr, textY, v17, turnsTextX, 3, namesTableH[(unsigned __int8)g_LanguageIndex]);
  }
  else
  {
    UI_DrawTextFmt(namesTableG[(unsigned __int8)g_LanguageIndex], textY, v17, turnsTextX, 3, namesTableG[(unsigned __int8)g_LanguageIndex]);
  }
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  stopBtnYMin = centeredX + 103;
  stopBtnXMax = centeredY + 220;
  stopBtnXMin = centeredY + 175;
  okBtnYMin = centeredX + 100;
  stopBtnYMax = centeredX + 117;
  okBtnXMax = centeredY + 92;
  okBtnYMax = centeredX + 113;
  okBtnXMin = centeredY + 60;
  while ( 1 )
  {
    do
      DD_Pump((int)g_RenderState, okBtnYMin);
    while ( !DD_IsFlipping((int)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= okBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= okBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= okBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= okBtnYMax )
    {
      break;
    }
    LOBYTE(v25) = g_CursorCoordShift;
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= stopBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= stopBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= stopBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= stopBtnYMax )
    {
      Building_Stop(buildingPtr, v25, okBtnYMin, okBtnXMax, a4);
      break;
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  spriteLeftX = centeredX;
  spriteTopY = centeredY;
  spriteWidthMinus1 = DLX_GetSpriteWidth((int)spriteSet, 0) - 1;
  v26 = DLX_GetSpriteHeight((int)spriteSet, 0);
  Render_FillRect(surface, 0, 0, 0, v26 - 1, spriteWidthMinus1, spriteTopY, spriteLeftX);
  if ( surface )
    (*(void (**)(void))surface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  Render_Present((int)g_RenderState);
  g_RenderDevice = savedRenderDevice;
  return WorldMap_RedrawViewport(1);
}
// 4202F9: variable 'v4' is possibly undefined
// 420359: variable 'v6' is possibly undefined
// 420386: variable 'v10' is possibly undefined
// 4204DE: variable 'v14' is possibly undefined
// 42051C: variable 'v16' is possibly undefined
// 420537: variable 'v19' is possibly undefined
// 420555: variable 'v17' is possibly undefined
// 420675: variable 'v25' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513B50: using guessed type char *off_513B50[12];
// 513B5C: using guessed type char *off_513B5C[9];
// 513B68: using guessed type char *off_513B68[6];
// 513B74: using guessed type char *off_513B74[3];
// 513BA4: using guessed type char *off_513BA4[9];
// 513BB0: using guessed type char *off_513BB0[6];
// 513BBC: using guessed type char *off_513BBC[3];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00420770) --------------------------------------------------------
DWORD Timer_InitPerfCounterFrequency()
{
  QueryPerformanceFrequency(&Frequency);
  Frequency.QuadPart /= 100;
  return Frequency.LowPart;
}

//----- (004207B0) --------------------------------------------------------
int __fastcall Time_Now(int a1, int a2)
{
  LARGE_INTEGER v3; // [esp+0h] [ebp-18h] BYREF
  (void)a1;
  (void)a2;
  QueryPerformanceCounter(&v3);
  if ( !Frequency.QuadPart )
    return v3.LowPart;
  return (int)(v3.QuadPart / Frequency.QuadPart);
}

//----- (00420800) --------------------------------------------------------
unsigned int  Timer_BusyWaitWithCallback(int durationTicks, int callbackAddr, int a3)
{
  void (__cdecl *callback)(void);
  unsigned int deadline;
  unsigned int result; // eax

  (void)a3;
  callback = (void (__cdecl *)(void))(uintptr_t)callbackAddr;
  deadline = Time_Now(0, 0) + (unsigned int)durationTicks;
  while ( 1 )
  {
    result = Time_Now(0, 0);
    if ( result >= deadline )
      break;
    if ( callback )
      callback();
  }
  return result;
}

//----- (00420820) --------------------------------------------------------
int __thiscall Mem_ConstructObjectArray256(void *this)
{
  return _wcpp_4_ctor_array__(this, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00420840) --------------------------------------------------------
int  Castle_RequestManagementScreenExit(uintptr_t widgetRecord, int animationDelay)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widgetRecord, animationDelay);
  g_CastleScreenExitRequested = 1;
  return result;
}
// 526E80: using guessed type int g_CastleScreenExitRequested;

//----- (00420870) --------------------------------------------------------
int Castle_RebuildMissingAddonFlags()
{
  int anyAddonMissing; // edx
  int result; // eax

  g_CastleAddonSchoolMissingFlags[0] = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) == 0;
  g_CastleAddonHospitalMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) == 0;
  g_CastleAddonBarracksMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) == 0;
  g_CastleAddonWorkshopMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) == 0;
  anyAddonMissing = 0;
  g_CastleAddonSmithsMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) == 0;
  for ( result = 0; result != 50; result += 10 )
  {
    if ( g_CastleAddonSchoolMissingFlags[result] )
      anyAddonMissing = 1;
  }
  if ( !anyAddonMissing )
    g_CastleAnyAddonMissingFlag = 0;
  return result * 4;
}
// 513E22: using guessed type int dword_513E22;
// 513FC2: using guessed type int dword_513FC2[];
// 513FEA: using guessed type int dword_513FEA;
// 514012: using guessed type int dword_514012;
// 51403A: using guessed type int dword_51403A;
// 514062: using guessed type int dword_514062;
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420910) --------------------------------------------------------
void *Castle_ShowNewBuildingMenu()
{
  void *result; // eax
  int v1; // ecx
  void *v2; // edx
  int frameOffset; // esi
  int delayAccum; // edi
  int nowTicks; // eax
  int v6; // ecx
  unsigned int deadline; // edx
  unsigned int now; // eax
  int absFrame; // eax
  int SpriteForChar; // eax
  DWORD renderContext; // ebp
  void (*menuAction)(void); // eax
  void *savedRenderDevice; // [esp+1Ch] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  if ( !DD_IsFlipping((int)g_RenderState) || g_MouseCursorRawX >> g_CursorCoordShift <= 509 || g_MouseCursorRawY >> g_CursorCoordShift >= 66 )
    goto LABEL_4;
  Castle_RebuildMissingAddonFlags();
  v2 = &g_MainRenderDevice;
  frameOffset = -5;
  delayAccum = 0;
  g_RenderDevice = &g_MainRenderDevice;
  do
  {
    nowTicks = Time_Now(v1, (int)v2);
    v6 = 3;
    deadline = delayAccum / 3 + nowTicks;
    do
      now = Time_Now(v6, deadline);
    while ( now < deadline );
    Render_Pump();
    if ( frameOffset <= 0 )
      absFrame = -frameOffset;
    else
      absFrame = frameOffset;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 5 - absFrame);
    renderContext = *((_DWORD *)g_RenderDevice + 46);
    delayAccum += 2;
    (*(void (__fastcall **)(_DWORD, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(renderContext + 52))(
      0,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      0,
      0,
      0);
    ++frameOffset;
    Render_Present((int)g_RenderState);
  }
  while ( frameOffset <= 5 );
  Render_Pump();
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 300, SCREEN_MAX_X, 0x12Cu, 0x12Cu, 0);
  Render_Present((int)g_RenderState);
  g_WorldMapTargetSurface = g_PrimaryRenderSurface;
  menuAction = (void (*)(void))UI_RunMenu(g_CastleNewBuildingMenu, renderContext);
  if ( menuAction )
  {
    menuAction();
    result = savedRenderDevice;
    g_RenderDevice = savedRenderDevice;
  }
  else
  {
LABEL_4:
    result = savedRenderDevice;
    g_RenderDevice = savedRenderDevice;
  }
  return result;
}
// 420980: variable 'v1' is possibly undefined
// 420980: variable 'v2' is possibly undefined
// 420998: variable 'v6' is possibly undefined
// 420998: variable 'v7' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513E08: using guessed type _WORD word_513E08[5];
// 5202E0: using guessed type int dword_5202E0;
// 523F60: using guessed type int dword_523F60;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00420A90) --------------------------------------------------------
int  Castle_PlayAddonConstructionReveal(int addonTileMarker, int buildingRecord)
{
  int minX; // edi
  int scanY; // esi
  int v4; // ecx
  int i; // ebx
  int v6; // ecx
  int revealLeftX; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // edx
  int v14; // eax
  int v15; // ecx
  int savedBuildingRecord; // [esp+4h] [ebp-30h]
  int startTime; // [esp+Ch] [ebp-28h]
  int maxX; // [esp+14h] [ebp-20h]
  int minY; // [esp+18h] [ebp-1Ch]
  int maxY; // [esp+1Ch] [ebp-18h]

  minX = 639;
  Render_Pump();
  scanY = 0;
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  g_RenderDevice = (_UNKNOWN *)g_CastleScreenSurface;
  minY = 479;
  maxX = 0;
  maxY = 0;
  do
  {
    v4 = (*(int (**)(void))(*(_DWORD *)(g_CastleScreenSurface + 184) + 4))();
    for ( i = 0; i < 640; ++i )
    {
      if ( *(unsigned __int8 *)(*(int (**)(void))(*(_DWORD *)v4 + 16))() == addonTileMarker )
      {
        if ( i < minX )
          minX = i;
        if ( i > maxX )
          maxX = i;
        if ( scanY < minY )
          minY = scanY;
        if ( scanY > maxY )
          maxY = scanY;
      }
      (*(void (__fastcall **)(int, int))(*(_DWORD *)v6 + 12))(v6, 1);
    }
    ++scanY;
    (**(void (__fastcall ***)(int, int))v4)(v4, 2);
  }
  while ( scanY < 480 );
  revealLeftX = minX - 50;
  if ( revealLeftX < 0 )
    LOWORD(revealLeftX) = 0;
  if ( addonTileMarker == 254 || addonTileMarker == 250 )
    LOWORD(revealLeftX) = 0;
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 0, buildingRecord, 0);
  startTime = Time_Now(v9, v8);
  savedBuildingRecord = g_SelectedBuildingRecord;
  v11 = buildingRecord;
  g_SelectedBuildingRecord = buildingRecord;
  while ( Time_Now(v10, v11) < (unsigned int)(startTime + 200) )
  {
    v14 = Time_Now(startTime, v12);
    Render_BlendSurfaceRect(
      0,
      g_PrimaryRenderSurface,
      (unsigned __int16)revealLeftX,
      g_CastleScreenSurface,
      minY,
      maxX,
      maxY,
      revealLeftX,
      minY,
      255 * (v14 - v15) / 0xC8u);
    Castle_UpdateAmbientAnimationLayers();
  }
  g_SelectedBuildingRecord = savedBuildingRecord;
  Render_FillRect(
    (_DWORD *)g_CastleScreenSurface,
    (_DWORD *)g_PrimaryRenderSurface,
    (unsigned __int16)minY,
    (unsigned __int16)revealLeftX,
    maxX,
    maxY,
    revealLeftX,
    minY);
  Render_FillRect((_DWORD *)g_CastleScreenSurface, 0, (unsigned __int16)minY, (unsigned __int16)revealLeftX, maxX, maxY, revealLeftX, minY);
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  g_RenderDevice = &g_MainRenderDevice;
  Castle_DrawStatusPanel();
  return Render_Present((int)g_RenderState);
}
// 420B10: variable 'v4' is possibly undefined
// 420B4F: variable 'v6' is possibly undefined
// 420BA5: variable 'v9' is possibly undefined
// 420BA5: variable 'v8' is possibly undefined
// 420BCC: variable 'v10' is possibly undefined
// 420BCC: variable 'v11' is possibly undefined
// 420C82: variable 'v12' is possibly undefined
// 420C87: variable 'v15' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00420CD0) --------------------------------------------------------
int  Castle_BuildSchoolWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildSchool((char *)g_SelectedBuildingRecord, a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)tailSrc;
    tailDst[2] = *(_BYTE *)(tailSrc + 2);
    recordCopyPtr = (int)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_SCHOOL;
    Audio_PlaySoundEffectByName(aBudowaSzkola, 64);
    Castle_PlayAddonConstructionReveal(251, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420D05: variable 'v5' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420D50) --------------------------------------------------------
int  Castle_BuildWorkshopWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildWorkshop(a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)tailSrc;
    tailDst[2] = *(_BYTE *)(tailSrc + 2);
    recordCopyPtr = (int)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_WORKSHOP;
    Audio_PlaySoundEffectByName(aBudowaWarszt_0, 64);
    Castle_PlayAddonConstructionReveal(252, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420D85: variable 'v5' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420DD0) --------------------------------------------------------
int  Castle_BuildBarracksWithAnimation(int a1, char a2, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildBarracks(a1, a2, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a2, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)tailSrc;
    tailDst[2] = *(_BYTE *)(tailSrc + 2);
    recordCopyPtr = (int)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_BARRACKS;
    Audio_PlaySoundEffectByName(aBudowaBaraki, 64);
    Castle_PlayAddonConstructionReveal(254, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420E05: variable 'v6' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420E50) --------------------------------------------------------
int  Castle_BuildHospitalWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx
  char *soundName; // eax

  Building_BuildHospital(a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)tailSrc;
    tailDst[2] = *(_BYTE *)(tailSrc + 2);
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_HOSPITAL;
    recordCopyPtr = (int)recordCopy;
    if ( PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(g_SelectedBuildingRecord + 2)) )
      soundName = aBudowaChrzesci;
    else
      soundName = aBudowaPoganie;
    Audio_PlaySoundEffectByName(soundName, 64);
    Castle_PlayAddonConstructionReveal(250, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420E85: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420EF0) --------------------------------------------------------
int  Castle_BuildSmithsWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildSmiths(a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)tailSrc;
    tailDst[2] = *(_BYTE *)(tailSrc + 2);
    recordCopyPtr = (int)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_SMITHS;
    Audio_PlaySoundEffectByName(aBudowaKuznia, 64);
    Castle_PlayAddonConstructionReveal(253, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420F25: variable 'v5' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420F70) --------------------------------------------------------
BOOL Building_HandleUpgradeButtonAction()
{
  BOOL result; // eax

  result = Building_TryStartUpgrade((unsigned __int8 *)g_SelectedBuildingRecord);
  if ( result )
    return CRT_RunGuardedStaticLocalInit();
  return result;
}
// 420F80: using guessed type int sub_41FF80(void);
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420FB0) --------------------------------------------------------
int  Castle_ConfirmDestroyCurrentBuilding(int a1, char a2, DWORD a3, double a4)
{
  int result; // eax
  int v5; // edx
  int promptStrings[6]; // [esp+0h] [ebp-18h]

  promptStrings[0] = (int)g_CastleConfirmDestroyPrompt[0];
  promptStrings[1] = (int)g_CastleConfirmDestroyPrompt[1];
  promptStrings[2] = (int)g_CastleConfirmDestroyPrompt[2];
  result = YesNoWindow(promptStrings[(unsigned __int8)g_LanguageIndex], g_CastleScreenPaletteBuffer, a1, a2, a3);
  if ( result )
  {
    Building_Destroy(g_SelectedBuildingRecord, a2, a3, a4);
    result = Audio_PlaySoundEffectByName(aNiszcz, v5);
    g_CastleDestroyConfirmed = 1;
    g_CastleScreenExitRequested = 1;
  }
  return result;
}
// 420FF3: variable 'v5' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 514144: using guessed type char *off_514144[3];
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 526E80: using guessed type int g_CastleScreenExitRequested;
// 526E84: using guessed type int g_CastleDestroyConfirmed;

//----- (00421010) --------------------------------------------------------
int Castle_DrawStatusPanel()
{
  int SpriteForChar; // eax
  int buildingSprite; // eax
  int result; // eax
  int overlaySprite; // eax

  SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(5, 5, SpriteForChar, 0);
  if ( PLAYER_RELIGION_FLAG(g_CurrentPlayerIndex) )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex + 5);
    Compat_RenderDeviceDrawMenuSprite(9, 9, SpriteForChar, 1);
  }
  Render_ReleaseSurface(7, 0);
  buildingSprite = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, *(unsigned __int8 *)(g_SelectedBuildingRecord + 421) + 3 * g_CurrentPlayerIndex + 11);
  Compat_RenderDeviceDrawMenuSprite(26, 156, buildingSprite, 1);
  UI_DrawTextFmt(5, 41, 275, 10, 3, g_SelectedBuildingRecord + 5);
  UI_DrawTextFmt(5, 58, 87, 30, 2, (int)aD_42);
  UI_DrawTextFmt(5, 58, 149, 30, 2, (int)aD_43);
  UI_DrawUnitStatsValues(g_SelectedBuildingRecord);
  UI_DrawTextFmt(5, 58, 211, 30, 2, (int)aD_44);
  UI_DrawTextFmt(5, 58, 273, 30, 2, (int)aD_45);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 435) & 7) != 0 )
  {
    overlaySprite = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, 10);
    return Compat_RenderDeviceDrawMenuSprite(43, 127, overlaySprite, 1);
  }
  return result;
}
// 421142: variable 'v3' is possibly undefined
// 421142: variable 'v4' is possibly undefined
// 42116C: variable 'v5' is possibly undefined
// 42116C: variable 'v6' is possibly undefined
// 421197: variable 'v7' is possibly undefined
// 421197: variable 'v8' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E7C: using guessed type int g_CastleStatusSpriteSet;

static void Castle_EnsureCompositeStatusWidget(void)
{
  static const char castle_status_button_sound[] = "duze";

  if ( g_CastleCompositeStatusWidgetInitialized )
    return;

  memset(g_CastleStatusWidgetRecord, 0, sizeof(g_CastleStatusWidgetRecord));
  *(_DWORD *)(g_CastleStatusWidgetRecord + 0) = 31;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 4) = 432;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 8) = 1;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 12) = (int)(uintptr_t)&g_CastleSceneIconSpriteSet;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 16) = 6;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 20) = 7;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 24) = -1;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 32) = (int)(uintptr_t)&Castle_RequestManagementScreenExit;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 49) = (int)(uintptr_t)castle_status_button_sound;
  *(_DWORD *)(g_CastleStatusWidgetRecord + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE) = -1;
  g_CastleCompositeStatusWidgetInitialized = 1;
}

//----- (00421240) --------------------------------------------------------
char  Castle_RenderCompositeSceneLayers(int surface, int drawModeArg, int buildingRecordArg, int variantArg)
{
  int surface2; // ebp
  char addonFlags; // dl
  char v6; // bh
  char v7; // dl
  char v8; // bh
  char v9; // dl
  char *addonLayerName; // edx
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  char *v19; // esi
  char *v20; // edi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char addonFlags2; // bh
  char v28; // ch
  char v29; // dh
  char *addonLayer2Name; // edx
  char *v31; // esi
  char *v32; // edi
  char v33; // al
  char v34; // al
  char *v35; // esi
  char *v36; // edi
  char v37; // al
  char v38; // al
  char *v39; // esi
  char *v40; // edi
  char v41; // al
  char v42; // al
  char *v43; // esi
  char *v44; // edi
  char v45; // al
  char v46; // al
  char *v47; // esi
  char *v48; // edi
  char v49; // al
  char v50; // al
  char *v51; // esi
  char *v52; // edi
  char v53; // al
  char v54; // al
  char v55; // bh
  char v56; // dl
  int SpriteForChar; // eax
  int castle_icon_owner; // eax
  void *v58; // ecx
  int savedBuildingRecord; // edx
  char pathBuffer[256]; // [esp+0h] [ebp-138h] BYREF
  __int16 ownerIconPositions[10]; // [esp+100h] [ebp-38h] BYREF
  char castleSpriteName[8]; // [esp+114h] [ebp-24h] BYREF
  void *savedRenderDevice; // [esp+11Ch] [ebp-1Ch]
  int buildingRecord; // [esp+120h] [ebp-18h]
  int variant; // [esp+124h] [ebp-14h]
  int drawMode; // [esp+128h] [ebp-10h]
  int load_result;

  surface2 = surface;
  drawMode = drawModeArg;
  variant = variantArg;
  buildingRecord = buildingRecordArg;
  strcpy(castleSpriteName, "zamek_1");
  LOBYTE(surface) = g_CurrentPlayerIndex + 49;
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  if ( variantArg != 2 )
  {
    addonFlags = *(_BYTE *)(g_SelectedBuildingRecord + 416);
    if ( (addonFlags & 1) == 0 || (addonFlags & 2) != 0 || (addonFlags & 4) != 0 )
    {
      v6 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (v6 & 1) != 0 || (v6 & 2) != 0 || (v6 & 4) == 0 )
      {
        v7 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
        if ( (v7 & 1) != 0 || (v7 & 2) == 0 || (v7 & 4) != 0 )
        {
          v8 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
          if ( (v8 & 1) == 0 && (v8 & 2) != 0 && (v8 & 4) != 0 )
          {
            addonLayerName = a11_7;
          }
          else
          {
            v9 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
            if ( (v9 & 1) != 0 && (v9 & 2) != 0 && (v9 & 4) != 0 )
            {
              addonLayerName = a12;
            }
            else
            {
              v55 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
              if ( (v55 & 1) != 0 && (v55 & 2) != 0 && (v55 & 4) == 0 )
              {
                addonLayerName = a10;
              }
              else
              {
                v56 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
                if ( (v56 & 1) != 0 && (v56 & 2) == 0 && (v56 & 4) != 0 )
                  addonLayerName = a07;
                else
                  addonLayerName = a01_3;
              }
            }
          }
        }
        else
        {
          addonLayerName = a09;
        }
      }
      else
      {
        addonLayerName = a05;
      }
    }
    else
    {
      addonLayerName = a03;
    }
    v11 = castleSpriteName;
    v12 = pathBuffer;
    do
    {
      v13 = *v11;
      *v12 = *v11;
      if ( !v13 )
        break;
      v14 = v11[1];
      v11 += 2;
      v12[1] = v14;
      v12 += 2;
    }
    while ( v14 );
    v15 = aZ_;
    v16 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v17 = *v15;
      *v16 = *v15;
      if ( !v17 )
        break;
      v18 = v15[1];
      v15 += 2;
      v16[1] = v18;
      v16 += 2;
    }
    while ( v18 );
    v19 = addonLayerName;
    v20 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v21 = *v19;
      *v20 = *v19;
      if ( !v21 )
        break;
      v22 = v19[1];
      v19 += 2;
      v20[1] = v22;
      v20 += 2;
    }
    while ( v22 );
    if ( drawMode )
      v23 = aM_gfx;
    else
      v23 = a_gfx;
    v24 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v25 = *v23;
      *v24 = *v23;
      if ( !v25 )
        break;
      v26 = v23[1];
      v23 += 2;
      v24[1] = v26;
      v24 += 2;
    }
    while ( v26 );
    load_result = RenderSurface_InvokeSlot48LoadPCX(
                    (_DWORD *)(uintptr_t)(unsigned int)surface2,
                    pathBuffer,
                    0,
                    (uintptr_t)g_CastleScreenPaletteBuffer);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=0 result=%d target=%08x\n", pathBuffer, load_result, surface2);
    LOBYTE(surface) = load_result;
  }
  if ( variant != 1 )
  {
    addonFlags2 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
    if ( (addonFlags2 & 8) != 0 && (addonFlags2 & 0x10) == 0 )
    {
      addonLayer2Name = a04;
    }
    else
    {
      v28 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (v28 & 8) != 0 || (v28 & 0x10) == 0 )
      {
        v29 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
        if ( (v29 & 8) != 0 && (v29 & 0x10) != 0 )
          addonLayer2Name = a08;
        else
          addonLayer2Name = a02;
      }
      else
      {
        addonLayer2Name = a06;
      }
    }
    v31 = castleSpriteName;
    v32 = pathBuffer;
    do
    {
      v33 = *v31;
      *v32 = *v31;
      if ( !v33 )
        break;
      v34 = v31[1];
      v31 += 2;
      v32[1] = v34;
      v32 += 2;
    }
    while ( v34 );
    v35 = aZ__0;
    v36 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v37 = *v35;
      *v36 = *v35;
      if ( !v37 )
        break;
      v38 = v35[1];
      v35 += 2;
      v36[1] = v38;
      v36 += 2;
    }
    while ( v38 );
    v39 = addonLayer2Name;
    v40 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v41 = *v39;
      *v40 = *v39;
      if ( !v41 )
        break;
      v42 = v39[1];
      v39 += 2;
      v40[1] = v42;
      v40 += 2;
    }
    while ( v42 );
    v43 = drawMode ? aM_gfx_0 : a_gfx_0;
    v44 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v45 = *v43;
      *v44 = *v43;
      if ( !v45 )
        break;
      v46 = v43[1];
      v43 += 2;
      v44[1] = v46;
      v44 += 2;
    }
    while ( v46 );
    load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, pathBuffer, 1, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", pathBuffer, load_result, surface2);
    surface = *(char *)(g_SelectedBuildingRecord + 4);
    if ( surface == 1 )
    {
      v47 = castleSpriteName;
      v48 = pathBuffer;
      do
      {
        v49 = *v47;
        *v48 = *v47;
        if ( !v49 )
          break;
        v50 = v47[1];
        v47 += 2;
        v48[1] = v50;
        v48 += 2;
      }
      while ( v50 );
      v51 = aZ_13_tw_gfx;
      v52 = &pathBuffer[strlen(pathBuffer)];
      do
      {
        v53 = *v51;
        *v52 = *v51;
        if ( !v53 )
          break;
        v54 = v51[1];
        v51 += 2;
        v52[1] = v54;
        v52 += 2;
      }
      while ( v54 );
      load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, pathBuffer, 1, 0);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", pathBuffer, load_result, surface2);
      LOBYTE(surface) = load_result;
    }
  }
  if ( !drawMode )
  {
    savedRenderDevice = g_RenderDevice;
    g_RenderDevice = (_UNKNOWN *)surface2;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 0);
    Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 0);
    qmemcpy(ownerIconPositions, &g_CastleOwnerIconPositions, sizeof(ownerIconPositions));
    castle_icon_owner = *(unsigned __int8 *)(g_SelectedBuildingRecord + 2);
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 8);
    Compat_RenderDeviceDrawMenuSprite(ownerIconPositions[2 * castle_icon_owner + 1], ownerIconPositions[2 * castle_icon_owner], SpriteForChar, 1);
    savedBuildingRecord = g_SelectedBuildingRecord;
    g_SelectedBuildingRecord = buildingRecord;
    Castle_DrawAllAmbientAnimationLayers(v58);
    g_SelectedBuildingRecord = savedBuildingRecord;
    Castle_EnsureCompositeStatusWidget();
    UIWidgetTable_InitDrawStates((_DWORD *)g_CastleStatusWidgetRecord);
    LOBYTE(surface) = (_BYTE)savedRenderDevice;
    g_RenderDevice = savedRenderDevice;
  }
  return surface;
}
// 42170D: variable 'v58' is possibly undefined
// 421717: variable 'v59' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513D98: using guessed type _DWORD dword_513D98[3];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;

//----- (00421740) --------------------------------------------------------
int  Castle_DrawAmbientAnimationSprite(
        unsigned __int16 top,
        int left,
        int spriteChar,
        int spriteSet,
        unsigned __int8 drawFlags)
{
  int overlayWasPresented; // ebp
  __int16 SpriteHeight; // ax
  int SpriteForChar; // eax
  int result; // eax
  unsigned __int16 rightX; // [esp-4h] [ebp-1Ch]

  overlayWasPresented = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    rightX = left + DLX_GetSpriteWidth(spriteSet, spriteChar);
    SpriteHeight = DLX_GetSpriteHeight(spriteSet, spriteChar);
    RenderState_PumpIfRectInViewBounds(g_RenderState, top, top + SpriteHeight, left, rightX);
  }
  SpriteForChar = DLX_GetSpriteForChar(spriteSet, spriteChar);
  result = Compat_RenderDeviceDrawMenuSprite(left, top, SpriteForChar, drawFlags);
  if ( overlayWasPresented )
    return Render_Present((int)g_RenderState);
  return result;
}
// 42177B: variable 'v7' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00421830) --------------------------------------------------------
int  Castle_DrawAmbientAnimationLayer(int layerIndex)
{
  int result; // eax
  char addonFlagsLayer1; // dh
  char addonFlagsLayer2; // ch

  switch ( layerIndex )
  {
    case 1:
      result = g_SelectedBuildingRecord;
      addonFlagsLayer1 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (addonFlagsLayer1 & 4) != 0 && (addonFlagsLayer1 & 1) != 0 )
      {
        result = g_CastleAmbientLayer1_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(
                     g_CastleAmbientLayer1_SpriteIds[20 * g_CurrentPlayerIndex],
                     g_CastleAmbientLayer1_XOffsets[20 * g_CurrentPlayerIndex],
                     g_CastleAmbientLayer1_Frame,
                     g_CastleAmbientSpriteSet,
                     1u);
      }
      break;
    case 2:
      result = g_SelectedBuildingRecord;
      addonFlagsLayer2 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (addonFlagsLayer2 & 0x10) != 0 && (addonFlagsLayer2 & 8) != 0 )
      {
        result = g_CastleAmbientLayer2_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer2_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer2_Frame + 12, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 3:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) != 0 )
      {
        result = g_CastleAmbientLayer3_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer3_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer3AnimFrame + 24, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 4:
      if ( g_CurrentPlayerIndex != 1 && g_CurrentPlayerIndex != 4
        || (result = *(_DWORD *)(g_SelectedBuildingRecord + 416) << 28 >> 31, (*(_DWORD *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0) )
      {
        if ( g_CurrentPlayerIndex != 3
          || (result = *(_DWORD *)(g_SelectedBuildingRecord + 416) << 30 >> 31, (*(_DWORD *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0) )
        {
          result = g_CastleAmbientLayer4_SpriteIds[20 * g_CurrentPlayerIndex];
          if ( result != -1 )
            result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer4_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer4_Frame + 36, g_CastleAmbientSpriteSet, 1u);
        }
      }
      break;
    case 5:
      result = g_CastleAmbientLayer5_SpriteIds[20 * g_CurrentPlayerIndex];
      if ( result != -1 )
        result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer5_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer5_Frame + 48, g_CastleAmbientSpriteSet, 0);
      break;
    case 6:
      result = *(char *)(g_SelectedBuildingRecord + 4);
      if ( result != 1 )
      {
        result = g_CastleAmbientLayer6_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer6_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer6_Frame + 71, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 7:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
      {
        result = g_CastleAmbientLayer7_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer7_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer7_Frame + 83, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 8:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
      {
        result = g_CastleAmbientLayer8_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer8_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer8_Frame + 95, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 9:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
      {
        result = g_CastleAmbientLayer9_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer9_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer9_Frame + 136, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 10:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
      {
        result = g_CastleAmbientLayer10_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer10_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer10AnimFrame + 167, g_CastleAmbientSpriteSet, 0);
      }
      break;
    default:
      App_RequestQuit((int)asc_4EE6D4);
  }
  return result;
}
// 513C3C: using guessed type __int16 word_513C3C[];
// 513C3E: using guessed type __int16 word_513C3E[];
// 513C40: using guessed type __int16 word_513C40[];
// 513C42: using guessed type __int16 word_513C42[];
// 513C44: using guessed type __int16 word_513C44[];
// 513C46: using guessed type __int16 word_513C46[];
// 513C48: using guessed type __int16 word_513C48[];
// 513C4A: using guessed type __int16 word_513C4A[];
// 513C4C: using guessed type __int16 word_513C4C[];
// 513C4E: using guessed type __int16 word_513C4E[];
// 513C50: using guessed type __int16 word_513C50[];
// 513C52: using guessed type __int16 word_513C52[];
// 513C54: using guessed type __int16 word_513C54[];
// 513C56: using guessed type __int16 word_513C56[];
// 513C58: using guessed type __int16 word_513C58[];
// 513C5A: using guessed type __int16 word_513C5A[];
// 513C5C: using guessed type __int16 word_513C5C[];
// 513C5E: using guessed type __int16 word_513C5E[];
// 513C60: using guessed type __int16 word_513C60[];
// 513C62: using guessed type __int16 word_513C62[83];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E78: using guessed type int g_CastleAmbientSpriteSet;
// 526E8C: using guessed type int dword_526E8C;
// 526E94: using guessed type int dword_526E94;
// 526E9C: using guessed type int dword_526E9C;
// 526EA8: using guessed type int dword_526EA8;
// 526EB4: using guessed type int dword_526EB4;
// 526EBC: using guessed type int dword_526EBC;
// 526EC4: using guessed type int dword_526EC4;
// 526ED0: using guessed type int dword_526ED0;
// 526EDC: using guessed type int dword_526EDC;
// 526EE8: using guessed type int dword_526EE8;

//----- (00421C20) --------------------------------------------------------
int __thiscall Castle_DrawAllAmbientAnimationLayers(void *this)
{
  int i; // edx
  int layerIndex; // eax
  int result; // eax

  for ( i = 1; i <= 10; ++i )
  {
    layerIndex = i;
    result = Castle_DrawAmbientAnimationLayer(layerIndex);
  }
  return result;
}

//----- (00421C40) --------------------------------------------------------
unsigned int Castle_UpdateAmbientAnimationLayers()
{
  void *savedRenderDevice; // ebx
  unsigned int v2; // eax
  unsigned int v3; // edx
  unsigned int v4; // ecx
  unsigned int v5; // eax
  unsigned int v6; // edx
  unsigned int v7; // ecx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // ecx
  int v11; // edx
  unsigned int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  int v15; // edx
  unsigned int layer3RandomDelay; // eax
  int v17; // ecx
  int v18; // edx
  unsigned int v19; // eax
  unsigned int v20; // ecx
  int v21; // ecx
  unsigned int layer5RandomDelay; // eax
  int v23; // ecx
  unsigned int v24; // eax
  int v25; // edx
  unsigned int v26; // ecx
  unsigned int v27; // eax
  unsigned int v28; // edx
  unsigned int v29; // ecx
  int v30; // edx
  unsigned int v31; // ecx
  unsigned int v32; // eax
  int v33; // edx
  unsigned int layer8RandomDelay; // eax
  int v35; // ecx
  int v36; // edx
  unsigned int v37; // ecx
  unsigned int v38; // eax
  int v39; // edx
  unsigned int layer9RandomDelay; // eax
  int v41; // ecx
  unsigned int result; // eax
  int v43; // edx
  int v44; // edx
  unsigned int v45; // ecx
  int v46; // edx
  int v47; // ecx

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  v2 = Time_Now(g_CastleAmbientLayer1_LastTick + 10, (int)&g_MainRenderDevice);
  if ( v4 < v2 )
  {
    g_CastleAmbientLayer1_LastTick = Time_Now(v4, v3);
    v3 = ++g_CastleAmbientLayer1_Frame % 0xCu;
    g_CastleAmbientLayer1_Frame %= 0xCu;
    Castle_DrawAmbientAnimationLayer(1);
  }
  v5 = Time_Now(g_CastleAmbientLayer2_LastTick + 10, v3);
  if ( v7 < v5 )
  {
    g_CastleAmbientLayer2_LastTick = Time_Now(v7, v6);
    v6 = (g_CastleAmbientLayer2_Frame + 1) % 0xCu;
    g_CastleAmbientLayer2_Frame = v6;
    Castle_DrawAmbientAnimationLayer(2);
  }
  v8 = Time_Now(g_CastleAmbientLayer4_LastTick + 10, v6);
  if ( v10 < v8 )
  {
    g_CastleAmbientLayer4_LastTick = Time_Now(v10, v9);
    v9 = (g_CastleAmbientLayer4_Frame + 1) % 0xCu;
    g_CastleAmbientLayer4_Frame = v9;
    Castle_DrawAmbientAnimationLayer(4);
  }
  if ( Time_Now(v10, v9) >= (unsigned int)g_CastleAmbientLayer3_NextDueTick )
  {
    v13 = Time_Now(g_CastleAmbientLayer3_DelayJitter + g_CastleAmbientLayer3_LastTick, v11);
    if ( v12 < v13 )
    {
      g_CastleAmbientLayer3_LastTick = Time_Now(v12, v11);
      Castle_DrawAmbientAnimationLayer(3);
      v12 = g_CastleAmbientLayer3AnimFrame + 1;
      g_CastleAmbientLayer3AnimFrame = v12;
      if ( v12 == 12 )
      {
        g_CastleAmbientLayer3AnimFrame = Rng_RandRange(0, 10);
        Time_Now(v14, 500);
        layer3RandomDelay = Rng_RandRange(0, v15);
        g_CastleAmbientLayer3_NextDueTick = layer3RandomDelay + v17;
        g_CastleAmbientLayer3_DelayJitter = Rng_RandRange(2, 10);
      }
    }
  }
  if ( Time_Now(v12, v11) >= (unsigned int)g_CastleAmbientLayer5_NextDueTick )
  {
    v19 = Time_Now(g_CastleAmbientLayer5_LastTick + 10, v18);
    if ( v20 < v19 )
    {
      g_CastleAmbientLayer5_LastTick = Time_Now(v20, v18);
      Castle_DrawAmbientAnimationLayer(5);
      if ( ++g_CastleAmbientLayer5_Frame == 23 )
      {
        g_CastleAmbientLayer5_Frame = 0;
        Time_Now(v21, 0);
        layer5RandomDelay = Rng_RandRange(500, 2000);
        g_CastleAmbientLayer5_NextDueTick = layer5RandomDelay + v23;
      }
    }
  }
  v24 = Time_Now(g_CastleAmbientLayer6_LastTick + g_CastleAmbientLayer6_DelayJitter, v18);
  if ( v26 < v24 )
  {
    g_CastleAmbientLayer6_LastTick = Time_Now(v26, v25);
    g_CastleAmbientLayer6_Frame = (g_CastleAmbientLayer6_Frame + 1) % 0xCu;
    g_CastleAmbientLayer6_DelayJitter = Rng_RandRange(5, 15);
    Castle_DrawAmbientAnimationLayer(6);
  }
  v27 = Time_Now(g_CastleAmbientLayer7_LastTick + 10, v25);
  if ( v29 < v27 )
  {
    g_CastleAmbientLayer7_LastTick = Time_Now(v29, v28);
    v28 = (g_CastleAmbientLayer7_Frame + 1) % 0xCu;
    g_CastleAmbientLayer7_Frame = v28;
    Castle_DrawAmbientAnimationLayer(7);
  }
  if ( Time_Now(v29, v28) >= (unsigned int)g_CastleAmbientLayer8_NextDueTick )
  {
    v32 = Time_Now(g_CastleAmbientLayer8_LastFrameTimeMs + 10, v30);
    if ( v31 < v32 )
    {
      g_CastleAmbientLayer8_LastFrameTimeMs = Time_Now(v31, v30);
      Castle_DrawAmbientAnimationLayer(8);
      if ( ++g_CastleAmbientLayer8_Frame == 41 )
      {
        g_CastleAmbientLayer8_Frame = 0;
        Time_Now(0, 2000);
        layer8RandomDelay = Rng_RandRange(500, v33);
        v31 = layer8RandomDelay + v35;
        g_CastleAmbientLayer8_NextDueTick = v31;
      }
    }
  }
  if ( Time_Now(v31, v30) >= (unsigned int)g_CastleAmbientLayer9_NextPlayTimeMs )
  {
    v38 = Time_Now(g_CastleAmbientLayer9_LastFrameTimeMs + 10, v36);
    if ( v37 < v38 )
    {
      g_CastleAmbientLayer9_LastFrameTimeMs = Time_Now(v37, v36);
      Castle_DrawAmbientAnimationLayer(9);
      if ( ++g_CastleAmbientLayer9_Frame == 31 )
      {
        g_CastleAmbientLayer9_Frame = 0;
        Time_Now(v37, 2000);
        layer9RandomDelay = Rng_RandRange(500, v39);
        v37 = layer9RandomDelay + v41;
        g_CastleAmbientLayer9_NextPlayTimeMs = v37;
      }
    }
  }
  result = Time_Now(v37, v36);
  if ( result >= g_CastleAmbientLayer10_NextPlayTimeMs
    && (result = Time_Now(g_CastleAmbientLayer10_LastFrameTimeMs + 10, v43), v45 < result)
    && (g_CastleAmbientLayer10_LastFrameTimeMs = Time_Now(v45, v44), result = Castle_DrawAmbientAnimationLayer(10), ++g_CastleAmbientLayer10AnimFrame, g_CastleAmbientLayer10AnimFrame == 31) )
  {
    g_CastleAmbientLayer10AnimFrame = 0;
    Time_Now(31, 2000);
    result = Rng_RandRange(500, v46);
    g_CastleAmbientLayer10_NextPlayTimeMs = result + v47;
    g_RenderDevice = savedRenderDevice;
  }
  else
  {
    g_RenderDevice = savedRenderDevice;
  }
  return result;
}
// 421C67: variable 'v4' is possibly undefined
// 421F79: variable 'v3' is possibly undefined
// 421C7D: variable 'v7' is possibly undefined
// 421C7F: variable 'v6' is possibly undefined
// 421CC1: variable 'v10' is possibly undefined
// 421CC3: variable 'v9' is possibly undefined
// 421D12: variable 'v11' is possibly undefined
// 421D19: variable 'v12' is possibly undefined
// 421D57: variable 'v14' is possibly undefined
// 421D60: variable 'v15' is possibly undefined
// 421D71: variable 'v17' is possibly undefined
// 421D97: variable 'v18' is possibly undefined
// 421D9E: variable 'v20' is possibly undefined
// 421DCE: variable 'v21' is possibly undefined
// 421DE6: variable 'v23' is possibly undefined
// 421E00: variable 'v26' is possibly undefined
// 421E02: variable 'v25' is possibly undefined
// 421E58: variable 'v29' is possibly undefined
// 421E5A: variable 'v28' is possibly undefined
// 421EA2: variable 'v30' is possibly undefined
// 421EA9: variable 'v31' is possibly undefined
// 421EE8: variable 'v33' is possibly undefined
// 421EED: variable 'v35' is possibly undefined
// 421F0B: variable 'v36' is possibly undefined
// 421F12: variable 'v37' is possibly undefined
// 421F52: variable 'v39' is possibly undefined
// 421F57: variable 'v41' is possibly undefined
// 421FBC: variable 'v43' is possibly undefined
// 421FC3: variable 'v45' is possibly undefined
// 421FC5: variable 'v44' is possibly undefined
// 422004: variable 'v46' is possibly undefined
// 42200B: variable 'v47' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 51416C: using guessed type int dword_51416C;
// 514170: using guessed type int dword_514170;
// 526E88: using guessed type int dword_526E88;
// 526E8C: using guessed type int dword_526E8C;
// 526E90: using guessed type int dword_526E90;
// 526E94: using guessed type int dword_526E94;
// 526E98: using guessed type int dword_526E98;
// 526E9C: using guessed type int dword_526E9C;
// 526EA0: using guessed type int dword_526EA0;
// 526EA4: using guessed type int dword_526EA4;
// 526EA8: using guessed type int dword_526EA8;
// 526EAC: using guessed type int dword_526EAC;
// 526EB0: using guessed type int dword_526EB0;
// 526EB4: using guessed type int dword_526EB4;
// 526EB8: using guessed type int dword_526EB8;
// 526EBC: using guessed type int dword_526EBC;
// 526EC0: using guessed type int dword_526EC0;
// 526EC4: using guessed type int dword_526EC4;
// 526EC8: using guessed type int dword_526EC8;
// 526ECC: using guessed type int dword_526ECC;
// 526ED0: using guessed type int dword_526ED0;
// 526ED4: using guessed type int dword_526ED4;
// 526ED8: using guessed type int dword_526ED8;
// 526EDC: using guessed type int dword_526EDC;
// 526EE0: using guessed type int dword_526EE0;
// 526EE4: using guessed type int dword_526EE4;
// 526EE8: using guessed type int dword_526EE8;

//----- (00422020) --------------------------------------------------------
int * Castle_RebuildSceneBuffers(int paletteBuffer, DWORD runtime_context)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char castleSpriteName[20]; // [esp-6h] [ebp-1Ch] BYREF
  int savedArg; // [esp+Eh] [ebp-8h]
  unsigned int primary_surface_handle;

  savedArg = paletteBuffer;
  Castle_RenderCompositeSceneLayers(g_PrimaryRenderSurface, 0, g_SelectedBuildingRecord, 0);
  strcpy(castleSpriteName, "zamek_1");
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  Palette_LoadOrBuildBlendLookupTable(castleSpriteName, (int)g_CastleScreenPaletteBuffer, v3, runtime_context);
  Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v4, 0, runtime_context);
  Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v5, 0, runtime_context);
  Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v6, 0, runtime_context);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Castle_DrawStatusPanel();
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_CastleScreenPaletteBuffer, 0, runtime_context);
  RenderState_DrawCursorSpriteToPrimarySurface((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
    fprintf(
      stderr,
      "[castle] before_surface_copy map_surface=%08x primary_surface=%08x map_sum=%08x primary_sum=%08x\n",
      (unsigned int)g_PrimaryRenderSurface,
      primary_surface_handle,
      Diagnostics_SurfaceByteChecksum(g_PrimaryRenderSurface),
      Diagnostics_SurfaceByteChecksum(primary_surface_handle));
  }
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
    fprintf(
      stderr,
      "[castle] after_surface_copy map_surface=%08x primary_surface=%08x map_sum=%08x primary_sum=%08x\n",
      (unsigned int)g_PrimaryRenderSurface,
      primary_surface_handle,
      Diagnostics_SurfaceByteChecksum(g_PrimaryRenderSurface),
      Diagnostics_SurfaceByteChecksum(primary_surface_handle));
  }
  Castle_UpdateAmbientAnimationLayers();
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  return Palette_FadeInFromBlack((int *)&g_MainRenderDevice, g_CastleScreenPaletteBuffer, 20);
}
// 422057: variable 'v3' is possibly undefined
// 422066: variable 'v4' is possibly undefined
// 422075: variable 'v5' is possibly undefined
// 422084: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00422100) --------------------------------------------------------
int Castle_UpdateGateToggles()
{
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 420) & 1) != 0 )
    UI_MenuEntry_Disable((int)&g_CastleNewBuildingMenu, 0);
  else
    UI_MenuEntry_Enable((int)&g_CastleNewBuildingMenu, 0);
  if ( Building_CanStartUpgrade((unsigned __int8 *)g_SelectedBuildingRecord) )
    return UI_MenuEntry_Enable((int)&g_CastleNewBuildingMenu, 2);
  else
    return UI_MenuEntry_Disable((int)&g_CastleNewBuildingMenu, 2);
}
// 526A64: using guessed type int g_SelectedBuildingRecord;

typedef int (*CastleManagementPanelCallback)(int building_record, int callback_context, DWORD runtime_context);

static int Castle_InvokePrisonerPanel(int building_record, int callback_context, DWORD runtime_context)
{
  (void)callback_context;
  return Building_ShowPrisonerManagementPanel(building_record, NULL, runtime_context);
}

static int Castle_InvokeEconomyPanel(int building_record, int callback_context, DWORD runtime_context)
{
  (void)callback_context;
  (void)runtime_context;
  return BuildingEconomyDialog_Run(building_record);
}

static void BuildingGarrisonDialog_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        void *action_callback,
        const char *text_pl,
        const char *text_en,
        const char *text_de,
        const char *sound)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BuildingGarrisonDialogUiSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
  *(_DWORD *)(record + 32) = (int)(uintptr_t)action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)text_pl;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)text_en;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)text_de;
  record[48] = 2;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound;
}

static void BuildingGarrisonDialog_EnsureActionWidgets(int building_record)
{
  static const char sound_large[] = "duze";
  static const char text_back_pl[] = "Koniec";
  static const char text_back_en[] = "Back";
  static const char text_back_de[] = "Zuruck";
  static const char text_production_pl[] = "Produkcja";
  static const char text_production_en[] = "Production";
  static const char text_production_de[] = "Produzieren";
  static const char text_cure_pl[] = "Leczenie";
  static const char text_cure_en[] = "Cure";
  static const char text_cure_de[] = "Heilung";
  static const char text_training_pl[] = "Trening";
  static const char text_training_en[] = "Training";
  static const char text_training_de[] = "Training";
  static const char text_leave_pl[] = "Opusc koszary";
  static const char text_leave_en[] = "Leave barracks";
  static const char text_leave_de[] = "Kaserne verlassen";
  int addon_flags;

  addon_flags = *(unsigned char *)(building_record + 416);
  memset(BuildingGarrisonDialogActions, 0, sizeof(BuildingGarrisonDialogActions));
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    39,
    426,
    1,
    0,
    1,
    BuildingGarrisonDialog_RequestClose,
    text_back_pl,
    text_back_en,
    text_back_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    (addon_flags & 2) ? 155 : 1000,
    426,
    1,
    2,
    3,
    BuildingGarrisonDialog_ShowProductionDialog,
    text_production_pl,
    text_production_en,
    text_production_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    (addon_flags & 1) ? 272 : 1000,
    426,
    1,
    4,
    5,
    BuildingGarrisonDialog_ToggleRepairSelectedUnits,
    text_cure_pl,
    text_cure_en,
    text_cure_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    (addon_flags & 8) ? 385 : 1000,
    426,
    1,
    6,
    7,
    BuildingGarrisonDialog_ToggleTrainingSelectedUnits,
    text_training_pl,
    text_training_en,
    text_training_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    503,
    426,
    1,
    8,
    9,
    BuildingGarrisonDialog_BeginSelectedUnitsExit,
    text_leave_pl,
    text_leave_en,
    text_leave_de,
    sound_large);
  *(_DWORD *)(BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT) = -1;
}

static int BuildingGarrisonDialog_Run(int building_record, int callback_context, DWORD runtime_context)
{
  static const char castle_chr_dw12_s32[] = "castle.chr\\dw_12.s32";
  static const char castle_pog_dw12_s32[] = "castle.pog\\dw_12.s32";
  int (*saved_tick_callback)(void);
  int saved_resource_handle;
  int slot_index;
  int slot_record;
  int old_selected_slot;
  int resource_handle;
  _DWORD *surface;
  _DWORD *scratch_surface;
  _DWORD *sprite_set;
  const char *gfx_path;
  const char *sprite_path;
  const char *resource_base;
  int owner_index;
  int handled_widget;
  int selected_count;
  int primary_down;
  int secondary_down;

  (void)callback_context;
  Diagnostics_ResetFrameDumpOnBarracksEnter();
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] enter building=%08x runtime=%u\n", building_record, (unsigned int)runtime_context);
  g_BuildingGarrisonDialogActiveBuilding = building_record;
  owner_index = *(unsigned char *)(building_record + 2);
  g_BuildingGarrisonDialogUseChrTheme = PLAYER_RELIGION_FLAG(owner_index);
  g_BuildingGarrisonDialogSelectedUnitSpriteSet = 0;
  memset(g_BuildingGarrisonDialogSlotSpriteSets, 0, 12 * sizeof(g_BuildingGarrisonDialogSlotSpriteSets[0]));
  memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
  for ( slot_index = 0; slot_index < 12; ++slot_index )
    g_BuildingGarrisonDialogSlotAnimFrames[slot_index] = Rng_RandRange(0, 7);
  g_BuildingGarrisonDialogPendingExitCountdown = 0;
  g_BuildingGarrisonDialogSelectedSlotIndex = -1;

  surface = (_DWORD *)Mem_Alloc(188, 0, 0, runtime_context);
  if ( surface )
    surface = Render_CreateSurface((int)surface, 33, 64);
  g_GarrisonUnitCellSurface = (int)(uintptr_t)surface;
  scratch_surface = (_DWORD *)Mem_Alloc(188, 0, 0, runtime_context);
  if ( scratch_surface )
    scratch_surface = Render_CreateSurface((int)scratch_surface, 33, 64);

  resource_handle = Mem_Alloc(1024, 0, -1, runtime_context);
  if ( resource_handle )
    resource_handle = _wcpp_4_ctor_array__(resource_handle, 256);
  g_BuildingGarrisonDialogResourceHandle = resource_handle;

  gfx_path = g_BuildingGarrisonDialogUseChrTheme ? aCastle_chrD_15 : aCastle_pogD_15;
  sprite_path = g_BuildingGarrisonDialogUseChrTheme ? castle_chr_dw12_s32 : castle_pog_dw12_s32;
  resource_base = g_BuildingGarrisonDialogUseChrTheme ? aCastle_chrD_16 : aCastle_pogD_16;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    (char *)gfx_path,
    0,
    (uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] background_loaded gfx=%s palette=%08x\n", gfx_path, g_BuildingGarrisonDialogResourceHandle);
  sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, runtime_context);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, sprite_path);
  g_BuildingGarrisonDialogUiSpriteSet = (int)(uintptr_t)sprite_set;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] ui_sprites_loaded path=%s sprite_set=%08x\n", sprite_path, g_BuildingGarrisonDialogUiSpriteSet);
  Palette_LoadOrBuildBlendLookupTable((CHAR *)resource_base, g_BuildingGarrisonDialogResourceHandle, g_BuildingGarrisonDialogUseChrTheme, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] palette_loaded base=%s\n", resource_base);
  Render_LoadResourceSprite_v4(5, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  Render_LoadResourceSprite_v4(7, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] resource_sprites_loaded cursor_base=%d\n", g_ActiveWidgetSpriteTableIndex);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_BuildingGarrisonDialogResourceHandle, 0, runtime_context);
  UI_SetActiveWidgetTable(8);
  BuildingGarrisonDialog_EnsureActionWidgets(building_record);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] action_widgets_ready\n");
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates((_DWORD *)BuildingGarrisonDialogActions);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] action_widgets_drawn\n");
  BuildingGarrisonDialog_RebuildSlotSprites(20, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] slot_sprites_rebuilt\n");
  BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_panel_assets_rebuilt\n");
  BuildingGarrisonDialog_DrawSelectedUnitPanel();
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_panel_drawn\n");
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_BuildingGarrisonDialogResourceHandle, 20);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  Render_Pump();
  Render_Present((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] initial_present_done\n");

  g_BuildingGarrisonDialogCloseRequested = 0;
  saved_tick_callback = g_ActiveDialogAnimationTickHook;
  g_ActiveDialogAnimationTickHook = (int (*)(void))BuildingGarrisonDialog_TickAnimations;
  while ( !g_BuildingGarrisonDialogCloseRequested && !Input_IsKeyPressed(1) )
  {
    BuildingGarrisonDialog_TickAnimations((double)runtime_context);
    DD_Pump((int)g_RenderState, 0);
    g_RenderDevice = &g_MainRenderDevice;
    handled_widget = UIWidgetTable_PollHoverAndActions((_DWORD *)BuildingGarrisonDialogActions, runtime_context);
    if ( handled_widget )
      continue;

    slot_index = BuildingGarrisonDialog_HitTestSlotGrid();
    if ( slot_index == -1 )
      continue;
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * slot_index;
    primary_down = DD_IsFlipping((int)g_RenderState);
    secondary_down = DD_IsLost((int)g_RenderState);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(
        stderr,
        "[barracks] slot_hit idx=%d primary=%d secondary=%d type=%d selected=%d\n",
        slot_index,
        primary_down,
        secondary_down,
        *(__int16 *)(slot_record + 18),
        g_BuildingGarrisonDialogSelectedSlots[slot_index]);
    if ( primary_down && *(__int16 *)(slot_record + 18) != -1 )
    {
      selected_count = BuildingGarrisonDialog_CountSelectedSlots();
      if ( selected_count < 10 || g_BuildingGarrisonDialogSelectedSlots[slot_index] )
      {
        g_BuildingGarrisonDialogSelectedSlots[slot_index] = !g_BuildingGarrisonDialogSelectedSlots[slot_index];
        if ( Diagnostics_IsWorldMapClickTraceEnabled() )
          fprintf(
            stderr,
            "[barracks] slot_toggle idx=%d selected=%d selected_count_before=%d\n",
            slot_index,
            g_BuildingGarrisonDialogSelectedSlots[slot_index],
            selected_count);
        Audio_PlaySoundEffectByName("marker", 64);
        BuildingGarrisonDialog_DrawSlotGrid(slot_index);
        Render_Present((int)g_RenderState);
      }
      while ( DD_IsFlipping((int)g_RenderState) )
      {
        DD_Pump((int)g_RenderState, 0);
        BuildingGarrisonDialog_TickAnimations((double)runtime_context);
      }
    }
    else if ( secondary_down && *(__int16 *)(slot_record + 18) != -1 )
    {
      old_selected_slot = g_BuildingGarrisonDialogSelectedSlotIndex;
      if ( old_selected_slot != -1 )
      {
        g_BuildingGarrisonDialogSelectedSlotIndex = -1;
        BuildingGarrisonDialog_ReloadSlotSprite(old_selected_slot, old_selected_slot + 1, 20, runtime_context);
        BuildingGarrisonDialog_DrawSlotGrid(old_selected_slot);
      }
      g_BuildingGarrisonDialogSelectedSlotIndex = slot_index;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_begin idx=%d\n", slot_index);
      Diagnostics_ResetFrameDumpOnBarracksDetail();
      BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
      Render_Present((int)g_RenderState);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_present idx=%d\n", slot_index);
      Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
      while ( DD_IsLost((int)g_RenderState) )
      {
        DD_Pump((int)g_RenderState, 0);
        BuildingGarrisonDialog_TickAnimations((double)runtime_context);
      }
      g_BuildingGarrisonDialogSelectedSlotIndex = -1;
      BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
      Render_Present((int)g_RenderState);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_end idx=%d\n", slot_index);
    }
  }

  g_ActiveDialogAnimationTickHook = saved_tick_callback;
  DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogUiSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( g_BuildingGarrisonDialogSlotSpriteSets[slot_index] )
    {
      nfree_(g_BuildingGarrisonDialogSlotSpriteSets[slot_index]);
      g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = 0;
    }
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  if ( g_BuildingGarrisonDialogResourceHandle )
    nfree_(g_BuildingGarrisonDialogResourceHandle);
  g_BuildingGarrisonDialogResourceHandle = 0;
  if ( g_GarrisonUnitCellSurface )
  {
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_GarrisonUnitCellSurface, 2);
    g_GarrisonUnitCellSurface = 0;
  }
  if ( scratch_surface )
    RenderSurface_InvokeSlot0(scratch_surface, 2);
  saved_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  Render_SetResourceHandle((int)&g_MainRenderDevice, saved_resource_handle);
  return 0;
}

static void Diagnostics_ResetFrameDumpOnCastleReturn(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_CASTLE_RETURN");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_ResetFrameDumpOnCastleEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_CASTLE_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_ResetFrameDumpOnEconomyEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_ResetFrameDumpOnBarracksEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_ResetFrameDumpOnBarracksDetail(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_DETAIL");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_ResetFrameDumpOnBattleEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BATTLE_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

static void Diagnostics_PrimeBattleSafeCursorOnTurnLoop(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_BATTLE_SAFE_CURSOR_ON_TURN_LOOP");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_DebugPrimeInputFallbackMouseState(560, 370, 0, 0);
}

static int Diagnostics_CountBattleUnitsForOwner(int owner)
{
  int count;
  int offset;

  if ( !g_MapData )
    return 0;
  count = 0;
  for ( offset = 0; offset != 682; offset += 31 )
  {
    if ( *(__int16 *)(g_MapData + offset + 852) != -1
      && *(unsigned __int8 *)(g_MapData + offset + 854) == owner )
    {
      ++count;
    }
  }
  return count;
}

static int Diagnostics_CountBattleUnitsTotal(void)
{
  int count;
  int offset;

  if ( !g_MapData )
    return 0;
  count = 0;
  for ( offset = 0; offset != 682; offset += 31 )
  {
    if ( *(__int16 *)(g_MapData + offset + 852) != -1 )
      ++count;
  }
  return count;
}

static void Diagnostics_TraceBattleUnitSnapshot(const char *stage)
{
  int slot_index;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() || !g_MapData )
    return;
  for ( slot_index = 0; slot_index < 22; ++slot_index )
  {
    int unit_record = g_MapData + 852 + 31 * slot_index;
    int unit_type = *(__int16 *)unit_record;

    if ( unit_type == -1 )
      continue;
    fprintf(
      stderr,
      "[battle_units] %s idx=%d owner=%u type=%d tile=%u,%u ap=%u count=%u flags=0x%02x selected=%d current_player=%d viewport=%d,%d\n",
      stage,
      slot_index,
      (unsigned)*(unsigned char *)(unit_record + 2),
      unit_type,
      (unsigned)*(unsigned __int16 *)(unit_record + 4),
      (unsigned)*(unsigned __int16 *)(unit_record + 6),
      (unsigned)*(unsigned char *)(unit_record + 8),
      (unsigned)*(unsigned char *)(unit_record + 9),
      (unsigned)*(unsigned char *)(unit_record + 12),
      g_SelectedUnitIndex,
      g_CurrentPlayerIndex,
      *(_DWORD *)(g_MapData + 808),
      *(_DWORD *)(g_MapData + 812));
  }
  fflush(stderr);
}

static int Diagnostics_CountBattleDeploymentBucketEntries(void)
{
  int count;
  int index;

  count = 0;
  for ( index = 0; index < 48; ++index )
  {
    if ( g_BattleDeploymentBucketStorage_5437DC[index] )
      ++count;
  }
  return count;
}

static unsigned __int8 *BattleDeploymentBucketReadPointer(int byte_offset)
{
  return (unsigned __int8 *)(uintptr_t)(unsigned int)*(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + byte_offset);
}

static int Diagnostics_IsBattleTileDrawTraceEnabled(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_BATTLE_TILE_DRAW");
    enabled = value && *value;
    checked = 1;
  }
  return enabled;
}

static int Diagnostics_IsWorldMapClickTraceEnabled(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_WORLD_CLICK");
    enabled = value && *value && strcmp(value, "0");
    checked = 1;
  }
  return enabled;
}

static int Diagnostics_IsWorldMapActionVerbose(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_WORLD_ACTION_VERBOSE");
    enabled = value && *value && strcmp(value, "0");
    checked = 1;
  }
  return enabled;
}

static int Diagnostics_ShouldTraceWorldMapActionStage(const char *stage)
{
  static unsigned int battle_input_loop_count;
  static unsigned int battle_move_preview_count;

  if ( !stage )
    return 0;
  if ( Diagnostics_IsWorldMapActionVerbose() )
    return 1;
  if ( !strncmp(stage, "action_widgets_after_", 21) )
    return 0;
  if ( !strncmp(stage, "selection_after_", 16) )
    return 0;
  if ( !strncmp(stage, "status_panel_", 13) && strcmp(stage, "status_panel_refresh_done") )
    return 0;
  if ( !strcmp(stage, "playgame_loop_top") )
    return 0;
  if ( !strcmp(stage, "playgame_after_player_info") )
    return 0;
  if ( !strcmp(stage, "battle_turn_loop_iter_top") )
    return 0;
  if ( !strcmp(stage, "battle_turn_loop_after_input_widgets") )
  {
    ++battle_input_loop_count;
    return battle_input_loop_count <= 32 || !(battle_input_loop_count & 0xFF);
  }
  if ( !strcmp(stage, "battle_move_track_enter")
    || !strcmp(stage, "battle_move_track_return")
    || !strcmp(stage, "battle_move_track_cost")
    || !strcmp(stage, "battle_move_execute_no_flip") )
  {
    ++battle_move_preview_count;
    return battle_move_preview_count <= 64 || !(battle_move_preview_count & 0xFF);
  }
  if ( !strncmp(stage, "battle_turn_loop_after_", 23)
    && strcmp(stage, "battle_turn_loop_after_input_widgets") )
  {
    return 0;
  }
  return 1;
}

static unsigned int Diagnostics_SurfaceByteChecksum(int surface_handle)
{
  _DWORD *surface;
  unsigned char *pixels;
  unsigned int width;
  unsigned int height;
  unsigned int pixel_count;
  unsigned int step;
  unsigned int index;
  unsigned int checksum;

  surface = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
  if ( !surface )
    return 0;
  pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !pixels )
    return 0;
  width = *(unsigned __int16 *)surface;
  height = *((unsigned __int16 *)surface + 1);
  pixel_count = width * height;
  if ( !pixel_count )
    return 0;
  step = pixel_count / 1024;
  if ( !step )
    step = 1;
  checksum = 2166136261u;
  for ( index = 0; index < pixel_count; index += step )
    checksum = (checksum ^ pixels[index]) * 16777619u;
  return checksum;
}

static void Diagnostics_TraceCastleHotspots(int surface_handle)
{
  _DWORD *surface;
  int hotspot;
  int x;
  int y;
  int pixel;
  int index;
  int count[8];
  int min_x[8];
  int min_y[8];
  int max_x[8];
  int max_y[8];

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  surface = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
  if ( !surface )
    return;
  for ( index = 0; index < 8; ++index )
  {
    count[index] = 0;
    min_x[index] = 640;
    min_y[index] = 480;
    max_x[index] = -1;
    max_y[index] = -1;
  }
  for ( y = 0; y < 480; ++y )
  {
    for ( x = 0; x < 640; ++x )
    {
      pixel = RenderSurface_InvokeSlot16ReadPixel(surface, x, y);
      if ( pixel < 248 || pixel > 255 )
        continue;
      index = pixel - 248;
      ++count[index];
      if ( x < min_x[index] )
        min_x[index] = x;
      if ( y < min_y[index] )
        min_y[index] = y;
      if ( x > max_x[index] )
        max_x[index] = x;
      if ( y > max_y[index] )
        max_y[index] = y;
    }
  }
  for ( hotspot = 248; hotspot <= 255; ++hotspot )
  {
    index = hotspot - 248;
    if ( !count[index] )
      continue;
    fprintf(
      stderr,
      "[castle] hotspot pixel=%d count=%d bounds=%d,%d..%d,%d center=%d,%d\n",
      hotspot,
      count[index],
      min_x[index],
      min_y[index],
      max_x[index],
      max_y[index],
      (min_x[index] + max_x[index]) / 2,
      (min_y[index] + max_y[index]) / 2);
  }
}

static void Diagnostics_TraceWorldMapClickEvent(
        const char *stage,
        int tile_x,
        int tile_y,
        int left,
        int top,
        int selected_unit_index)
{
  int in_bounds;
  int building_index = -1;
  int building_owner = -1;
  int building_kind = -1;
  int building_construction = -1;
  int building_row = -1;
  int building_column = -1;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  in_bounds = tile_x >= 0
           && tile_x < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
           && tile_y >= 0
           && tile_y < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( in_bounds && MapTile_HasBuilding(tile_x, tile_y) )
  {
    building_index = *(unsigned __int16 *)TILE_INDEX(tile_x, tile_y) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( building_index >= 0 && building_index <= 100 )
    {
      int building_record = BUILDING_RECORD(building_index);

      building_row = *(unsigned __int8 *)(building_record + 0);
      building_column = *(unsigned __int8 *)(building_record + 1);
      building_owner = *(unsigned __int8 *)(building_record + 2);
      building_kind = *(unsigned __int8 *)(building_record + 4);
      building_construction = *(__int16 *)(building_record + 16);
    }
  }
  fprintf(
    stderr,
    "[world_click] %s cursor=%d,%d tile=%d,%d left=%d top=%d selected=%d current_player=%d viewed_player=%d turn_owner=%d flipping=%d lost=%d own_stack=%d enemy_stack=%d building=%d own_building=%d enemy_building=%d building_idx=%d building_owner=%d building_kind=%d building_construction=%d building_origin=%d,%d port=%d site=%d in_bounds=%d\n",
    stage,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    tile_x,
    tile_y,
    left,
    top,
    selected_unit_index,
    g_CurrentPlayerIndex,
    VIEWED_PLAYER_INDEX,
    TURN_OWNER_PLAYER_INDEX,
    DD_IsFlipping((int)&g_RenderState),
    DD_IsLost((int)&g_RenderState),
    in_bounds ? MapTile_HasOwnUnitStack(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasVisibleEnemyUnitStack(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasBuilding(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasOwnBuilding(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasEnemyBuilding(tile_x, tile_y) : 0,
    building_index,
    building_owner,
    building_kind,
    building_construction,
    building_row,
    building_column,
    in_bounds ? Port_IsInsideFootprint(tile_x, tile_y) : 0,
    in_bounds ? MapTile_GetReligiousSiteCategory(tile_x, tile_y) : 0,
    in_bounds);
}

static void Diagnostics_TraceBattlefieldClickEvent(
        const char *stage,
        int local_x,
        int local_y,
        int tile_x,
        int tile_y,
        int occupant_slot)
{
  int selected_type = -1;
  int occupant_type = -1;
  int occupant_owner = -1;
  int occupant_ap = -1;
  int occupant_flags = -1;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() || !g_MapData )
    return;
  if ( g_SelectedUnitIndex >= 0 && g_SelectedUnitIndex < 22 )
    selected_type = *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  if ( occupant_slot >= 0 && occupant_slot < 22 )
  {
    int occupant_record = g_MapData + 31 * occupant_slot;

    occupant_type = *(__int16 *)(occupant_record + 852);
    occupant_owner = *(unsigned __int8 *)(occupant_record + 854);
    occupant_ap = *(unsigned __int8 *)(occupant_record + 860);
    occupant_flags = *(unsigned __int8 *)(occupant_record + 864);
  }
  fprintf(
    stderr,
    "[battle_click] %s cursor=%d,%d local=%d,%d tile=%d,%d viewport=%d,%d selected=%d selected_type=%d current_player=%d occupant=%d occupant_type=%d occupant_owner=%d occupant_ap=%d occupant_flags=0x%02x shoot=%d charge=%d flipping=%d lost=%d\n",
    stage,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    local_x,
    local_y,
    tile_x,
    tile_y,
    *(_DWORD *)(g_MapData + 808),
    *(_DWORD *)(g_MapData + 812),
    g_SelectedUnitIndex,
    selected_type,
    g_CurrentPlayerIndex,
    occupant_slot,
    occupant_type,
    occupant_owner,
    occupant_ap,
    occupant_flags,
    g_Battle_ShootModeEnabled,
    g_UnitBattleChargeModeActive_532060,
    DD_IsFlipping((int)&g_RenderState),
    DD_IsLost((int)&g_RenderState));
}

static void Diagnostics_TraceWorldMapActionEvent(
        const char *stage,
        int selected_unit_index,
        int detail_a,
        int detail_b,
        int detail_c)
{
  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  if ( !Diagnostics_ShouldTraceWorldMapActionStage(stage) )
    return;
  fprintf(
    stderr,
    "[world_action] %s selected=%d a=%d b=%d c=%d cursor=%d,%d flipping=%d lost=%d\n",
    stage,
    selected_unit_index,
    detail_a,
    detail_b,
    detail_c,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    DD_IsFlipping((int)&g_RenderState),
    DD_IsLost((int)&g_RenderState));
  fflush(stderr);
}

static int Diagnostics_UnitStackIndexFromRecord(int stack_record)
{
  int stack_table_base;
  int stack_table_delta;

  if ( !gameData || !stack_record )
    return -1;
  stack_table_base = gameData + UNIT_STACK_TABLE_OFFSET;
  stack_table_delta = stack_record - stack_table_base;
  if ( stack_table_delta < 0 || stack_table_delta % UNIT_STACK_STRIDE != 0 )
    return -1;
  stack_table_delta /= 725;
  if ( stack_table_delta < 0 || stack_table_delta >= UNIT_STACK_TABLE_COUNT )
    return -1;
  return stack_table_delta;
}

static void Diagnostics_TraceBootstrapEvent(const char *stage)
{
  if ( !getenv("CLASH95_TRACE_BOOTSTRAP") )
    return;
  fprintf(stderr, "[bootstrap] %s\n", stage);
  fflush(stderr);
}

static void Diagnostics_TraceWorldMapUnitSnapshot(const char *stage)
{
  int stack_index;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  for ( stack_index = 0; stack_index < UNIT_STACK_TABLE_COUNT; ++stack_index )
  {
    int stack_record = UNIT_STACK(stack_index);
    int first_unit_type = *(__int16 *)UNIT_STACK_SLOT(stack_record, 0);
    if ( first_unit_type != -1 && first_unit_type <= 0x28 )
    {
      int first_slot_record = UNIT_STACK_SLOT(stack_record, 0);

      fprintf(
        stderr,
        "[world_units] %s idx=%d owner=%u tile=%d,%d first=%d slots=%d first_ap=%u first_count=%u first_morale=%u first_fatigue=%u ap=%d path=%d hidden=%u\n",
        stage,
        stack_index,
        (unsigned)UNIT_STACK_OWNER_INDEX(stack_record),
        (int)UNIT_STACK_TILE_ROW(stack_record),
        (int)UNIT_STACK_TILE_COLUMN(stack_record),
        first_unit_type,
        Unit_GetSquadCount(stack_record),
        (unsigned)*(unsigned char *)(first_slot_record + 8),
        (unsigned)*(unsigned char *)(first_slot_record + 9),
        (unsigned)*(unsigned char *)(first_slot_record + 11),
        (unsigned)*(unsigned char *)(first_slot_record + 10),
        UnitStack_GetMinCurrentActionPoints(stack_record),
        *(_DWORD *)UNIT_STACK_PATH_BUFFER(stack_record),
        (unsigned)*(unsigned char *)(stack_record + 720));
      if ( getenv("CLASH95_TRACE_WORLD_UNIT_SLOTS") )
      {
        int slot_index;

        for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        {
          int slot_record = UNIT_STACK_SLOT(stack_record, slot_index);
          int unit_type = *(__int16 *)slot_record;

          if ( unit_type == -1 )
            break;
          fprintf(
            stderr,
            "[world_unit_slot] %s idx=%d slot=%d type=%d ap=%u count=%u morale=%u fatigue=%u order=%u flags=0x%02x\n",
            stage,
            stack_index,
            slot_index,
            unit_type,
            (unsigned)*(unsigned char *)(slot_record + 8),
            (unsigned)*(unsigned char *)(slot_record + 9),
            (unsigned)*(unsigned char *)(slot_record + 11),
            (unsigned)*(unsigned char *)(slot_record + 10),
            (unsigned)*(unsigned char *)(slot_record + 12),
            (unsigned)*(unsigned char *)(slot_record + 13));
        }
      }
    }
  }
}

static void Diagnostics_TraceWorldMapCursorSample(
        int tile_x,
        int tile_y,
        int left,
        int top,
        int selected_unit_index)
{
  static int initialized;
  static int last_cursor_x;
  static int last_cursor_y;
  static int last_flipping;
  static int last_lost;
  int cursor_x;
  int cursor_y;
  int flipping;
  int lost;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
  cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
  flipping = DD_IsFlipping((int)&g_RenderState);
  lost = DD_IsLost((int)&g_RenderState);
  if ( initialized
    && cursor_x == last_cursor_x
    && cursor_y == last_cursor_y
    && flipping == last_flipping
    && lost == last_lost )
  {
    return;
  }
  initialized = 1;
  last_cursor_x = cursor_x;
  last_cursor_y = cursor_y;
  last_flipping = flipping;
  last_lost = lost;
  fprintf(
    stderr,
    "[world_cursor] cursor=%d,%d tile=%d,%d left=%d top=%d selected=%d flipping=%d lost=%d\n",
    cursor_x,
    cursor_y,
    tile_x,
    tile_y,
    left,
    top,
    selected_unit_index,
    flipping,
    lost);
}

//----- (00422180) --------------------------------------------------------
int * Castle_OpenManagementScreen(DWORD buildingIndex, char a2)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  _DWORD *iconSpriteSet; // eax
  int v9; // ecx
  char *animPathSrc; // esi
  char *pathDst; // edi
  char srcChar; // al
  char nextChar; // al
  _DWORD *ambientSpriteSet; // eax
  int v15; // ecx
  _DWORD *statusSpriteSet; // eax
  int v17; // ecx
  _DWORD *Surface; // eax
  DWORD buildingRecordByteOffset; // ebp
  int v20; // edx
  int v21; // ecx
  char *v22; // ebx
  int activeTooltipId; // esi
  int v24; // edx
  int v25; // ecx
  _DWORD *menuSpriteSet; // eax
  char v27; // bl
  int v28; // ecx
  int v29; // ecx
  int *result; // eax
  int v31; // ecx
  int v32; // ecx
  int v34; // ecx
  int savedCallbackResourceHandle; // edx
  int v37; // ecx
  _DWORD *newScreenSurface; // eax
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int tooltipNameIndex; // eax
  char spritePath[20]; // [esp+0h] [ebp-38h] BYREF
  int savedMusicState; // [esp+14h] [ebp-24h]
  int (*savedRenderHook)(); // [esp+18h] [ebp-20h]
  int savedResourceHandle; // [esp+1Ch] [ebp-1Ch]
  CastleManagementPanelCallback castle_panel_callback;
  int castle_loop_iterations;

  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] open_enter building_idx=%u current_player=%d\n", (unsigned int)buildingIndex, g_CurrentPlayerIndex);
  Diagnostics_ResetFrameDumpOnCastleEnter();
  savedResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, (char *)Castle_RebuildSceneBuffers == (char *)Render_DefaultRH);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Castle_RebuildSceneBuffers;
  Debug_Log(v4, a2, buildingIndex, (int)aSetrhS08x_6);
  TextSprite_ReleaseAllResourceSlots();
  BuildingSpriteCache_Clear();
  UnitSpriteCache_FreeAllEntries(v5, buildingIndex);
  CSS_EmptySampleCache();
  Debug_Log(BUILDING_RECORD_SIZE * buildingIndex, a2, buildingIndex, (int)aCastleD);
  g_SelectedBuildingRecord = BUILDING_RECORD(buildingIndex);
  g_ActiveCastleOwnerIsChristian = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(g_SelectedBuildingRecord + 2));
  savedMusicState = Audio_PauseMusicAndPlayLoopedSound(aCastle, *(unsigned __int8 *)(g_SelectedBuildingRecord + 2) + 1);
  CSS_PauseStreamReading();
  Castle_UpdateGateToggles();
  strcpy(spritePath, "zamek_1\\z_iko.s32");
  spritePath[6] = g_CurrentPlayerIndex + 49;
  iconSpriteSet = (_DWORD *)Mem_Alloc(4112, v7, a2, buildingIndex);
  if ( iconSpriteSet )
    iconSpriteSet = DLXSpriteSet_Load(iconSpriteSet, spritePath);
  animPathSrc = aZamek_1Anim_s3;
  pathDst = spritePath;
  g_CastleSceneIconSpriteSet = (int)iconSpriteSet;
  do
  {
    srcChar = *animPathSrc;
    *pathDst = *animPathSrc;
    if ( !srcChar )
      break;
    nextChar = animPathSrc[1];
    animPathSrc += 2;
    pathDst[1] = nextChar;
    pathDst += 2;
  }
  while ( nextChar );
  spritePath[6] = g_CurrentPlayerIndex + 49;
  ambientSpriteSet = (_DWORD *)Mem_Alloc(4112, v9, a2, buildingIndex);
  if ( ambientSpriteSet )
    ambientSpriteSet = DLXSpriteSet_Load(ambientSpriteSet, spritePath);
  g_CastleAmbientSpriteSet = (int)ambientSpriteSet;
  statusSpriteSet = (_DWORD *)Mem_Alloc(4112, v15, a2, buildingIndex);
  if ( statusSpriteSet )
    statusSpriteSet = DLXSpriteSet_Load(statusSpriteSet, aDz_info_s32);
  g_CastleStatusSpriteSet = (int)statusSpriteSet;
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v17, a2, buildingIndex);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  buildingRecordByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
  g_CastleScreenSurface = (int)Surface;
  Castle_RebuildSceneBuffers((int)g_CastleScreenPaletteBuffer, buildingRecordByteOffset);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 3, (int)g_CastleScreenPaletteBuffer, aMap_pal_0);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 4, (int)g_CastleScreenPaletteBuffer, aMap_pal_1);
  DLXSpriteSet_DrawText(g_CastleStatusSpriteSet, 10, (int)g_CastleScreenPaletteBuffer, (unsigned __int8 *)g_MapPalettePtr);
  CSS_ResumeStreamReading();
  LOBYTE(v22) = -57;
  Tooltip_CaptureBackdrop(190, 455, 7, 455, 248);
  Render_Present((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] first_present building_idx=%u\n", (unsigned int)buildingIndex);
  Diagnostics_TraceCastleHotspots(g_CastleScreenSurface);
  g_CastleDestroyConfirmed = 0;
  g_CastleScreenExitRequested = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  activeTooltipId = 0;
  castle_loop_iterations = 0;
  while ( !Input_IsKeyPressed(1) && !g_CastleScreenExitRequested )
  {
    ++castle_loop_iterations;
    DD_Pump((int)g_RenderState, (char)v22);
    Castle_UpdateAmbientAnimationLayers();
    Castle_ShowNewBuildingMenu();
    UI_RunHoverTooltipZones(g_CastleHoverTooltipZones);
    g_RenderDevice = &g_MainRenderDevice;
    Castle_EnsureCompositeStatusWidget();
    UIWidgetTable_PollHoverAndActions((_DWORD *)g_CastleStatusWidgetRecord, buildingRecordByteOffset);
    LOBYTE(v32) = g_CursorCoordShift;
    g_RenderDevice = (_UNKNOWN *)g_CastleScreenSurface;
    v22 = (char *)(g_MouseCursorRawY >> g_CursorCoordShift);
    castle_panel_callback = NULL;
    switch ( RenderSurface_InvokeSlot16ReadPixel(
               (_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface,
               g_MouseCursorRawX >> g_CursorCoordShift,
               g_MouseCursorRawY >> g_CursorCoordShift) )
    {
      case 248:
        castle_panel_callback = Castle_InvokePrisonerPanel;
        if ( activeTooltipId != 134 )
        {
          activeTooltipId = 134;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 250:
        castle_panel_callback = Building_ShowGateDoorDialog_v3;
        if ( activeTooltipId != 153 )
        {
          v22 = UI_Locale_BuildingNames_J[(unsigned __int8)g_LanguageIndex];
          activeTooltipId = 153;
          Tooltip_ShowText(3, v22, spritePath[0]);
        }
        break;
      case 251:
        castle_panel_callback = Building_ShowGateDoorDialog_v1;
        if ( activeTooltipId != 156 )
        {
          activeTooltipId = 156;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_L[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 252:
        castle_panel_callback = Building_ShowGateDoorDialog_v4;
        if ( activeTooltipId != 159 )
        {
          activeTooltipId = 159;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_K[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 253:
        castle_panel_callback = Building_ShowGateDoorDialog_v2;
        if ( activeTooltipId != 166 )
        {
          activeTooltipId = 166;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_M[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 254:
        castle_panel_callback = BuildingGarrisonDialog_Run;
        if ( activeTooltipId != 99 )
        {
          if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
            tooltipNameIndex = 3;
          else
            tooltipNameIndex = 8;
          v22 = (&g_CastleBuildingIconTooltipNames[3 * tooltipNameIndex])[(unsigned __int8)g_LanguageIndex];
          activeTooltipId = 99;
          Tooltip_ShowText(3, v22, spritePath[0]);
        }
        break;
      case 255:
        castle_panel_callback = Castle_InvokeEconomyPanel;
        if ( activeTooltipId != 135 )
        {
          activeTooltipId = 135;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames_FromPeasants[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      default:
        if ( activeTooltipId )
          Tooltip_RestoreBackdrop();
        activeTooltipId = 0;
        break;
    }
    if ( DD_IsFlipping((int)g_RenderState) && castle_panel_callback )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[castle] callback_trigger pixel=%d cursor=%d,%d loop=%d\n",
          RenderSurface_InvokeSlot16ReadPixel(
             (_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface,
             g_MouseCursorRawX >> g_CursorCoordShift,
             g_MouseCursorRawY >> g_CursorCoordShift),
          g_MouseCursorRawX >> g_CursorCoordShift,
          g_MouseCursorRawY >> g_CursorCoordShift,
          castle_loop_iterations);
      UI_SetActiveWidgetTable(8);
      Render_Pump();
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
      if ( g_CastleScreenSurface )
        RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface, 2);
      savedCallbackResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
      v22 = (char *)g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(v34, (char)v22, buildingRecordByteOffset, (int)aSetrhS08x_7);
      castle_panel_callback(g_SelectedBuildingRecord, 0, buildingRecordByteOffset);
      Debug_Log((int)g_RenderHook, (char)v22, buildingRecordByteOffset, (int)aUnsetrh08x_7);
      g_RenderHook = (int (*)())v22;
      Render_SetResourceHandle((int)&g_MainRenderDevice, savedCallbackResourceHandle);
      newScreenSurface = (_DWORD *)Mem_Alloc(188, v37, (char)v22, buildingRecordByteOffset);
      if ( newScreenSurface )
      {
        LOBYTE(v22) = -32;
        newScreenSurface = Render_CreateSurface((int)newScreenSurface, SCREEN_WIDTH, SCREEN_HEIGHT);
      }
      g_CastleScreenSurface = (int)newScreenSurface;
      Castle_RebuildSceneBuffers(v39, buildingRecordByteOffset);
      g_RenderDevice = (_UNKNOWN *)g_CastleScreenSurface;
      RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_CastleScreenPaletteBuffer, v40, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v41, (char)v22, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v42, (char)v22, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v43, (char)v22, buildingRecordByteOffset);
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
      Render_Present((int)g_RenderState);
    }
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[castle] open_exit building_idx=%u loops=%d esc=%d exit_requested=%d\n",
      (unsigned int)buildingIndex,
      castle_loop_iterations,
      Input_IsKeyPressed(1),
      g_CastleScreenExitRequested);
  Render_Pump();
  RenderState_LoadDefaultCursorSprite((int)g_RenderState);
  Audio_SetMusicVolume(v24, 400);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  DLXSpriteSet_ReleaseAndClear(&g_MapPanelSpriteSet);
  menuSpriteSet = (_DWORD *)Mem_Alloc(4112, v25, 144, buildingRecordByteOffset);
  if ( menuSpriteSet )
    menuSpriteSet = DLXSpriteSet_Load(menuSpriteSet, "menu.s32");
  v27 = g_CastleScreenSurface;
  g_MapPanelSpriteSet = (int)menuSpriteSet;
  if ( g_CastleScreenSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface, 2);
  DLXSpriteSet_ReleaseAndClear(&g_CastleSceneIconSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleAmbientSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleStatusSpriteSet);
  TextSprite_ReleaseAllResourceSlots();
  CSS_EmptySampleCache();
  Palette_LoadOrBuildBlendLookupTable(aMainmap_2, g_MapPalettePtr, v28, buildingRecordByteOffset);
  Audio_ResumeMusicAndStopLoopedSound(savedMusicState);
  Debug_Log(v29, v27, buildingRecordByteOffset, (int)aUnsetrh08x_6);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, savedResourceHandle);
  Diagnostics_ResetFrameDumpOnCastleReturn();
  result = WorldMap_RenderHook(buildingRecordByteOffset);
  if ( g_CastleDestroyConfirmed )
    return (int *)Win_PlayModeChangeFrameTransition(aZniszcze, 1, v31, v27, buildingRecordByteOffset);
  return result;
}
// 4225A0: conditional instruction was optimized away because ecx.4!=0
// 4221CD: variable 'v4' is possibly undefined
// 4221DF: variable 'v5' is possibly undefined
// 422207: variable 'v6' is possibly undefined
// 422266: variable 'v7' is possibly undefined
// 4222AC: variable 'v9' is possibly undefined
// 4222C6: variable 'v15' is possibly undefined
// 4222FC: variable 'v17' is possibly undefined
// 422338: variable 'v20' is possibly undefined
// 422338: variable 'v21' is possibly undefined
// 4223F2: variable 'v24' is possibly undefined
// 422415: variable 'v25' is possibly undefined
// 422479: variable 'v28' is possibly undefined
// 422493: variable 'v29' is possibly undefined
// 422541: variable 'v32' is possibly undefined
// 42259A: variable 'v33' is possibly undefined
// 422618: variable 'v34' is possibly undefined
// 42262C: variable 'v35' is possibly undefined
// 42264D: variable 'v36' is possibly undefined
// 422657: variable 'v37' is possibly undefined
// 422674: variable 'v39' is possibly undefined
// 42268D: variable 'v40' is possibly undefined
// 42269C: variable 'v41' is possibly undefined
// 4226AB: variable 'v42' is possibly undefined
// 4226BA: variable 'v43' is possibly undefined
// 422866: variable 'v31' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513BD0: using guessed type char *off_513BD0[27];
// 513BE8: using guessed type char *off_513BE8[21];
// 513C00: using guessed type char *off_513C00[15];
// 513C0C: using guessed type char *off_513C0C[12];
// 513C18: using guessed type char *off_513C18[9];
// 513C24: using guessed type char *off_513C24[6];
// 513D08: using guessed type __int16 word_513D08[4];
// 513D98: using guessed type _DWORD dword_513D98[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 523F5C: using guessed type int dword_523F5C;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 526E70: using guessed type int g_ActiveCastleOwnerIsChristian;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;
// 526E78: using guessed type int g_CastleAmbientSpriteSet;
// 526E7C: using guessed type int g_CastleStatusSpriteSet;
// 526E80: using guessed type int g_CastleScreenExitRequested;
// 526E84: using guessed type int g_CastleDestroyConfirmed;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00422880) --------------------------------------------------------
int  Tooltip_CaptureBackdrop(int top, int bottom, int resourceHandle, int rightX, int regionMarkerId)
{
  int left; // edi
  int i; // esi
  _DWORD *Surface; // eax
  int result; // eax

  left = rightX;
  Render_ReleaseSurface(resourceHandle, resourceHandle);
  for ( i = rightX + UI_GetTextXOffset(resourceHandle); i >= (unsigned __int16)g_RenderDeviceClipRightX; --i )
    --left;
  if ( g_TooltipBackdropSurface )
    Compat_InvokeCompactSurfaceDestructor(g_TooltipBackdropSurface, 2);
  Surface = (_DWORD *)Mem_Alloc(188, 0, (char)rightX, resourceHandle);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, bottom - top + 1, i - left + 1);
  g_TooltipBackdropSurface = (int)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)left, (unsigned __int16)top, bottom, i, 0, 0);
  g_TooltipLeft = left;
  g_TooltipTop = top;
  g_TooltipRight = i;
  g_TooltipBottom = bottom;
  result = regionMarkerId;
  g_TooltipResourceHandle = resourceHandle;
  g_TooltipCaptureArg5 = regionMarkerId;
  return result;
}
// 42289A: variable 'v7' is possibly undefined
// 4228D2: variable 'v8' is possibly undefined
// 51D4C2: using guessed type __int16 word_51D4C2;
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 526F08: using guessed type int g_TooltipResourceHandle;
// 526F0C: using guessed type int dword_526F0C;

//----- (00422960) --------------------------------------------------------
int Tooltip_ReleaseBackdropSurface()
{
  int result; // eax

  result = 0;
  if ( g_TooltipBackdropSurface )
    Compat_InvokeCompactSurfaceDestructor(g_TooltipBackdropSurface, 2);
  g_TooltipBackdropSurface = 0;
  return result;
}
// 526EF4: using guessed type int g_TooltipBackdropSurface;

//----- (004229A0) --------------------------------------------------------
void * Tooltip_ShowText(int a1, char *format, ...)
{
  int textSpriteSlot; // ebp
  char *bufferDst; // edi
  char *textSrc; // esi
  char v6; // al
  char v7; // al
  void *result; // eax
  void *savedRenderDevice; // [esp+0h] [ebp-20h]
  va_list args;

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  textSpriteSlot = g_ActiveTextSpriteSlot;
  RenderState_PumpIfRectInViewBounds(g_RenderState, g_TooltipTop, g_TooltipBottom, g_TooltipLeft, g_TooltipRight);
  Render_FillRect(
    (_DWORD *)g_TooltipBackdropSurface,
    0,
    0,
    0,
    g_TooltipBottom - g_TooltipTop,
    g_TooltipRight - g_TooltipLeft,
    g_TooltipTop,
    g_TooltipLeft);
  Render_ReleaseSurface(g_TooltipResourceHandle, textSpriteSlot);
  va_start(args, format);
  UI_DrawTextFmtV(g_TooltipTop, g_TooltipBottom, a1, g_TooltipLeft, format, args);
  va_end(args);
  bufferDst = (char *)&g_TooltipTextBuffer;
  Render_Present((int)g_RenderState);
  textSrc = format;
  do
  {
    v6 = *textSrc;
    *bufferDst = *textSrc;
    if ( !v6 )
      break;
    v7 = textSrc[1];
    textSrc += 2;
    bufferDst[1] = v7;
    bufferDst += 2;
  }
  while ( v7 );
  Render_ReleaseSurface(textSpriteSlot, textSpriteSlot);
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 526F08: using guessed type int g_TooltipResourceHandle;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00422AC0) --------------------------------------------------------
int Tooltip_RestoreBackdrop()
{
  RenderState_PumpIfRectInViewBounds(g_RenderState, g_TooltipTop, g_TooltipBottom, g_TooltipLeft, g_TooltipRight);
  Render_FillRect(
    (_DWORD *)g_TooltipBackdropSurface,
    0,
    0,
    0,
    g_TooltipBottom - g_TooltipTop,
    g_TooltipRight - g_TooltipLeft,
    g_TooltipTop,
    g_TooltipLeft);
  return Render_Present((int)g_RenderState);
}
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00422B50) --------------------------------------------------------
int  Tooltip_RestoreIfTextMatches(int a1, int a2)
{
  int result; // eax

  result = strcmp_(a2, a1);
  if ( !result )
    return Tooltip_RestoreBackdrop();
  return result;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (00422B70) --------------------------------------------------------
int  Tooltip_SetResourceHandle(int result)
{
  g_TooltipResourceHandle = result;
  return result;
}
// 526F08: using guessed type int g_TooltipResourceHandle;

//----- (00422B80) --------------------------------------------------------
signed int  Unit_CountSelectedGroupMembers(int stackPtr)
{
  __int16 *slotPtr; // edx
  signed int result; // eax

  slotPtr = (__int16 *)(stackPtr + 6);
  for ( result = 0; result < 10; ++result )
  {
    if ( *slotPtr == -1 )
      break;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  return result;
}

//----- (00422BA0) --------------------------------------------------------
signed int  UnitStack_HasOnlyFlyingUnits(int stackPtr)
{
  __int16 *slotPtr; // edx
  int slotIndex; // eax
  int unitType; // ecx

  slotPtr = (__int16 *)(stackPtr + 6);
  slotIndex = 0;
  while ( 1 )
  {
    unitType = *slotPtr;
    if ( unitType == -1 )
      return 1;
    if ( (g_UnitTypeFlags[22 * unitType] & 1) == 0 )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 1;
  }
  return 0;
}
// 51257A: using guessed type int g_UnitTypeFlags[];

//----- (00422BE0) --------------------------------------------------------
int  Unit_AddToGroup(unsigned int a1, int a2, int a3, DWORD a4, double a5)
{
  int source_stack;
  int target_stack;
  signed int source_count;
  signed int target_count;
  int row_delta;
  int column_delta;
  int result; // eax

  Debug_Log(a1, a3, a4, (int)aUnit_addtogrou);
  Render_DrawSprite_v3(a1, a4);
  Render_DrawSprite_v3(a2, a4);
  source_stack = UNIT_STACK(a1);
  target_stack = UNIT_STACK(a2);
  source_count = Unit_GetSquadCount(source_stack);
  target_count = Unit_GetSquadCount(target_stack);
  if ( source_count + target_count <= UNIT_STACK_SLOT_COUNT )
  {
    if ( a3 )
      goto LABEL_11;
    row_delta = UNIT_STACK_TILE_ROW(source_stack) - UNIT_STACK_TILE_ROW(target_stack);
    if ( row_delta < 0 )
      row_delta = -row_delta;
    if ( row_delta <= 1 )
    {
      column_delta = UNIT_STACK_TILE_COLUMN(source_stack) - UNIT_STACK_TILE_COLUMN(target_stack);
      if ( column_delta < 0 )
        column_delta = -column_delta;
      if ( column_delta <= 1 )
        goto LABEL_11;
    }
    result = (int)Unit_MoveTrackNearTile(a1, UNIT_STACK_TILE_ROW(target_stack), source_stack, UNIT_STACK_TILE_COLUMN(target_stack), (DWORD)target_stack);
    if ( !result )
      return result;
    qmemcpy((void *)UNIT_STACK_PATH_BUFFER(source_stack), (const void *)result, UNIT_STACK_PATH_BYTES);
    UnitStack_ExecuteQueuedPath(a1, 1, UNIT_STACK_TILE_COLUMN(target_stack), (DWORD)target_stack, a5);
    if ( !*(_DWORD *)UNIT_STACK_PATH_BUFFER(source_stack) )
    {
LABEL_11:
      if ( UnitStack_GetMinCurrentActionPoints(source_stack) >= 4 )
      {
        UnitStack_SpendActionPointsClamped((__int16 *)source_stack, 4, (DWORD)target_stack, a5);
        source_count = Unit_GetSquadCount(source_stack);
        target_count = Unit_GetSquadCount(target_stack);
        qmemcpy(
          (void *)UNIT_STACK_SLOT(target_stack, target_count),
          (const void *)UNIT_STACK_SLOT(source_stack, 0),
          UNIT_STACK_SLOT_STRIDE * source_count);
        UnitStack_KillByIndex(a1, a3, (DWORD)target_stack, a5);
        *(_BYTE *)(target_stack + 720) = 0;
        g_SelectedUnitIndex = a2;
        Rules_LinkArmyFact((__int16 *)target_stack, 0, 0, a5, a3, (DWORD)target_stack);
        Rules_SyncArmyFactStrength((__int16 *)target_stack, 0, 0, a3, (DWORD)target_stack, a5);
        return 1;
      }
    }
  }
  return 0;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00422DC0) --------------------------------------------------------
BOOL  Unit_CanMoveSelectionFromGroupToTile(int a1, _DWORD *a2, int a3, int a4)
{
  int current_stack;
  int selected_slot_count;
  int slot_list_index;
  unsigned char temp_stack[UNIT_STACK_STRIDE];
  int target_stack_index;
  int target_stack;
  int dest_slot_type;

  if ( a4 < 0 || a4 >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) || a3 < 0 || a3 >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    return 0;
  current_stack = UNIT_STACK(a1);
  selected_slot_count = 0;
  if ( *a2 != -1 )
  {
    do
    {
      if ( selected_slot_count >= UNIT_STACK_SLOT_COUNT )
        break;
      ++selected_slot_count;
    }
    while ( a2[selected_slot_count] != -1 );
  }
  if ( selected_slot_count == 0 || selected_slot_count == Unit_GetSquadCount(current_stack) )
    return 0;
  qmemcpy(temp_stack, (const void *)current_stack, UNIT_STACK_STRIDE);
  for ( slot_list_index = 0; slot_list_index < selected_slot_count; ++slot_list_index )
  {
    qmemcpy(
      temp_stack + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * slot_list_index,
      (const void *)UNIT_STACK_SLOT(current_stack, a2[slot_list_index]),
      UNIT_STACK_SLOT_STRIDE);
  }
  *(__int16 *)(temp_stack + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * selected_slot_count) = -1;
  target_stack_index = *(unsigned __int16 *)(TILE_INDEX(a4, a3));
  if ( target_stack_index > 0x1F4u )
  {
    return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
        && UnitStack_GetTileMoveCostOrZero((__int16 *)temp_stack, a4, 0, a3) != 0;
  }
  target_stack = UNIT_STACK(target_stack_index);
  dest_slot_type = *(__int16 *)(target_stack + UNIT_STACK_SLOT_BASE_OFFSET);
  if ( dest_slot_type < 0 || dest_slot_type > 0x28 )
  {
    return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
        && UnitStack_GetTileMoveCostOrZero((__int16 *)temp_stack, a4, 0, a3) != 0;
  }
  return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
      && UNIT_STACK_OWNER_INDEX(target_stack) == UNIT_STACK_OWNER_INDEX(current_stack);
}

BOOL  Map_IsTilePlacable(int a1, _DWORD *a2, int a3, int a4)
{
  return Unit_CanMoveSelectionFromGroupToTile(a1, a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00423050) --------------------------------------------------------
BOOL  Unit_MoveSelectionFromGroupToTile(int a1, _DWORD *a2, int a3, int a4, double a5, int a6)
{
  int current_stack;
  int selected_slot_count;
  int target_stack_index;
  int target_stack;
  int slot_list_index;
  int target_count;
  unsigned char *dest_slot;
  unsigned char *source_slot;
  char facing;

  Debug_Log(a2[1], *a2, a2[4], (int)aUnit_movefromg);
  Render_DrawSprite_v3(a1, a1);
  current_stack = UNIT_STACK(a1);
  selected_slot_count = 0;
  if ( *a2 != -1 )
  {
    do
    {
      if ( selected_slot_count >= UNIT_STACK_SLOT_COUNT )
        break;
      ++selected_slot_count;
    }
    while ( a2[selected_slot_count] != -1 );
  }
  if ( selected_slot_count == 0 || selected_slot_count == Unit_GetSquadCount(current_stack) )
    return 0;
  target_stack = 0;
  target_stack_index = *(unsigned __int16 *)(TILE_INDEX(a4, a3));
  if ( target_stack_index < 0x8000 )
  {
    target_stack = UNIT_STACK(target_stack_index);
    if ( selected_slot_count + Unit_GetSquadCount(target_stack) > UNIT_STACK_SLOT_COUNT )
      return 0;
    if ( !Map_IsTilePlacable(a1, a2, a3, a4) )
      return 0;
  }
  else if ( !a6 )
  {
    if ( !Map_IsTilePlacable(a1, a2, a3, a4) )
      return 0;
  }
  if ( !target_stack )
  {
    facing = Facing_DirectionFromDelta8(a4 - UNIT_STACK_TILE_ROW(current_stack), a3 - UNIT_STACK_TILE_COLUMN(current_stack));
    Unit_Create(0xFFFFFFFF, UNIT_STACK_OWNER_INDEX(current_stack), a4, facing, a3);
  }
  target_stack_index = *(unsigned __int16 *)(TILE_INDEX(a4, a3));
  target_stack = UNIT_STACK(target_stack_index);
  target_count = Unit_GetSquadCount(target_stack);
  dest_slot = (unsigned char *)UNIT_STACK_SLOT(target_stack, target_count);
  for ( slot_list_index = 0; slot_list_index < selected_slot_count; ++slot_list_index )
  {
    source_slot = (unsigned char *)UNIT_STACK_SLOT(current_stack, a2[slot_list_index]);
    qmemcpy(dest_slot, source_slot, UNIT_STACK_SLOT_STRIDE);
    dest_slot[8] -= 4;
    *(__int16 *)source_slot = -1;
    dest_slot += UNIT_STACK_SLOT_STRIDE;
  }
  Unit_CompactSquad((__int16 *)current_stack, a4, a5);
  *(_BYTE *)(current_stack + 720) = 0;
  Rules_LinkArmyFact((__int16 *)current_stack, 0, 0, a5, 0, (DWORD)current_stack);
  Rules_SyncArmyFactStrength((__int16 *)current_stack, 0, 0, 0, (DWORD)current_stack, a5);
  Rules_LinkArmyFact((__int16 *)target_stack, 0, 0, a5, 0, (DWORD)target_stack);
  Rules_SyncArmyFactStrength((__int16 *)target_stack, 0, 0, 0, (DWORD)target_stack, a5);
  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(target_stack_index, a5);
  Trap_TriggerAtStackTile(target_stack_index, (DWORD)current_stack, a5);
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00423370) --------------------------------------------------------
_DWORD * UI_LoadCurrentPlayerInfoSpriteSet(int playerIndex, int a2, char a3, DWORD a4)
{
  int playerIndexCopy; // edx
  int v5; // ecx
  _DWORD *result; // eax
  _BYTE fileName[24]; // [esp+0h] [ebp-1Ch] BYREF
  int v8; // [esp+18h] [ebp-4h]

  v8 = a2;
  playerIndexCopy = playerIndex;
  if ( g_CurrentPlayerInfoSpriteSet )
  {
    nfree_(g_CurrentPlayerInfoSpriteSet);
    g_CurrentPlayerInfoSpriteSet = 0;
  }
  sprintf_(fileName, "info%d.s32", playerIndexCopy + 1);
  result = (_DWORD *)Mem_Alloc(4112, v5, a3, a4);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, fileName);
    g_CurrentPlayerInfoSpriteSet = (int)result;
  }
  else
  {
    g_CurrentPlayerInfoSpriteSet = 0;
  }
  return result;
}
// 423393: variable 'v4' is possibly undefined
// 4233AB: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 527C24: using guessed type int dword_527C24;

//----- (004233E0) --------------------------------------------------------
int UI_FreeCurrentPlayerInfoSpriteSet()
{
  int result; // eax

  if ( g_CurrentPlayerInfoSpriteSet )
    result = nfree_(g_CurrentPlayerInfoSpriteSet);
  g_CurrentPlayerInfoSpriteSet = 0;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 527C24: using guessed type int dword_527C24;

//----- (00423420) --------------------------------------------------------
int  UnitStackSelection_RedrawPanel(int result, DWORD a2)
{
  int chosenUnitIndex; // edx
  int chosenUnitIndexScaled; // eax
  int *slotListPtr; // ebx
  void *v5; // ecx
  int v6; // ecx
  int ownerIndex; // eax
  int SpriteForChar; // eax
  int v9; // ecx
  int unitSpriteId; // eax
  int statusMarkSpriteId; // eax
  int selectionMarkSpriteId; // eax
  int neighbor_row; // eax
  int neighbor_column; // ebp
  int selectedSlotList[11]; // [esp+44h] [ebp-4Ch] BYREF
  int j; // [esp+70h] [ebp-20h]
  int i; // [esp+74h] [ebp-1Ch]

  if ( g_UnitStackSelectionActiveUnitIndex != -1 )
  {
    if ( result == -1 )
    {
      chosenUnitIndex = g_SelectedUnitIndex;
      chosenUnitIndexScaled = 8 * g_SelectedUnitIndex;
    }
    else
    {
      chosenUnitIndex = result;
      chosenUnitIndexScaled = 8 * result;
    }
    g_SelectedUnitStackRecordPtr = 5 * (chosenUnitIndex + 16 * (chosenUnitIndex + chosenUnitIndexScaled)) + gameData + UNIT_STACK_TABLE_OFFSET;
    memset(selectedSlotList, 0, sizeof(selectedSlotList));
    slotListPtr = selectedSlotList;
    UnitStackSelection_BuildSelectedSlotIndexList((int)g_UnitStackSlotSelectedFlags, 10, selectedSlotList);
    UI_ClearTileHighlight(0);
    if ( (unsigned int)*(__int16 *)(g_SelectedUnitStackRecordPtr + 6) <= 0x28 && UnitStackSelection_HasSelectedSlots() )
    {
      for ( i = 0; i < 12; ++i )
      {
        neighbor_column = Map_NeighborDY[2 * i] + *(__int16 *)(g_SelectedUnitStackRecordPtr + 2);
        neighbor_row = Map_NeighborDX[2 * i] + *(__int16 *)g_SelectedUnitStackRecordPtr;
        if ( Map_IsTilePlacable(g_SelectedUnitIndex, selectedSlotList, neighbor_column, neighbor_row) )
          UI_HighlightTile(neighbor_row, neighbor_column);
      }
    }
    g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
    ownerIndex = *(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 4);
    if ( ownerIndex != g_CurrentPlayerIndex )
      UI_LoadCurrentPlayerInfoSpriteSet(ownerIndex, v6, (char)slotListPtr, a2);
    SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 35);
    Compat_RenderDeviceDrawMenuSprite(400, 29, SpriteForChar, 1);
    for ( j = 0; j < 10; ++j )
    {
      if ( *(__int16 *)(31 * j + g_SelectedUnitStackRecordPtr + 6) == -1 )
        break;
      unitSpriteId = DLX_GetSpriteForChar(g_CurrentPlayerInfoSpriteSet, *(__int16 *)(31 * j + g_SelectedUnitStackRecordPtr + 6));
      Compat_RenderDeviceDrawMenuSprite(401, 38 * j + 35, unitSpriteId, 1);
      if ( (*(_BYTE *)(g_SelectedUnitStackRecordPtr + 31 * j + 19) & 4) != 0 )
      {
        statusMarkSpriteId = DLX_GetSpriteForChar(g_MarksSpriteSet, 33);
        Compat_RenderDeviceDrawMenuSprite(405, 38 * j + 40, statusMarkSpriteId, 1);
      }
      Render_ReleaseSurface(7, a2);
      v9 = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 4) == g_CurrentPlayerIndex )
        UI_DrawTextFmt(j, 38 * j + 32, 38 * j + 70, 450, 3, (int)aD_5);
      if ( g_UnitStackSlotSelectedFlags[j] )
      {
        selectionMarkSpriteId = DLX_GetSpriteForChar(g_MarksSpriteSet, (*(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 31 * j + 14) >= 4u) + 4);
        Compat_RenderDeviceDrawMenuSprite(402, 38 * j + 58, selectionMarkSpriteId, 1);
      }
    }
    result = *(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 4);
    if ( result != g_CurrentPlayerIndex )
      return (int)UI_LoadCurrentPlayerInfoSpriteSet(g_CurrentPlayerIndex, v9, g_CurrentPlayerIndex, a2);
  }
  return result;
}
// 42349D: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 42348D: variable 'v5' is possibly undefined
// 423555: variable 'v6' is possibly undefined
// 42374A: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 514194: using guessed type int dword_514194;
// 5202C8: using guessed type int dword_5202C8;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 527C24: using guessed type int dword_527C24;

//----- (00423760) --------------------------------------------------------
int  UnitStack_ShowSelectionDialog(int unitIndex, int a2)
{
  _BYTE savedSlotFlags[40]; // [esp+0h] [ebp-48h] BYREF
  int savedStackRecordPtr; // [esp+28h] [ebp-20h]
  int savedSelectionModeActive; // [esp+2Ch] [ebp-1Ch]
  int savedActiveUnitIndex; // [esp+30h] [ebp-18h]

  savedActiveUnitIndex = g_UnitStackSelectionActiveUnitIndex;
  savedSelectionModeActive = g_UnitStackSelectionModeActive;
  savedStackRecordPtr = g_SelectedUnitStackRecordPtr;
  qmemcpy(savedSlotFlags, g_UnitStackSlotSelectedFlags, sizeof(savedSlotFlags));
  g_UnitStackSelectionModeActive = 1;
  g_UnitStackSelectionActiveUnitIndex = unitIndex;
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(unitIndex, unitIndex);
  WorldMap_RedrawViewport(1);
  while ( DD_IsLost((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, a2);
    WorldMap_HandleScrollKeysAndIdle(unitIndex);
    WorldMap_RedrawFrame(a2);
  }
  g_UnitStackSelectionModeActive = savedSelectionModeActive;
  g_UnitStackSelectionActiveUnitIndex = savedActiveUnitIndex;
  g_SelectedUnitStackRecordPtr = savedStackRecordPtr;
  qmemcpy(g_UnitStackSlotSelectedFlags, savedSlotFlags, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(-1, unitIndex);
  return WorldMap_RedrawViewport(1);
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00423860) --------------------------------------------------------
signed int  UnitStackSelection_HandleInput(DWORD a1, double a2)
{
  int slot_index; // esi
  signed int handled_panel_input; // edi
  signed int special_unit_info; // eax
  int target_tile_x; // esi
  int target_tile_y; // ecx
  int distance_x; // eax
  int distance_y; // eax
  int selected_slot_indices[12]; // [esp+0h] [ebp-30h] BYREF

  if ( g_UnitStackSelectionActiveUnitIndex == -1 )
    return 0;
  slot_index = ((g_MouseCursorRawX >> g_CursorCoordShift) - 35) / 38;
  handled_panel_input = 0;
  if ( g_MouseCursorRawY >> g_CursorCoordShift >= 400
    && g_MouseCursorRawY >> g_CursorCoordShift < 464
    && slot_index >= 0
    && slot_index <= 9 )
  {
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
    if ( DD_IsLost((int)g_RenderState) && *(__int16 *)(g_SelectedUnitStackRecordPtr + 31 * slot_index + 6) != -1 )
    {
      special_unit_info = UnitStack_HasSpecialPersonageUnits(g_SelectedUnitStackRecordPtr);
      Unit_Info(100, 100, special_unit_info, (unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 31 * slot_index + 6), a1, 0);
      WorldMap_RedrawViewport(1);
    }
    if ( DD_IsFlipping((int)g_RenderState) && *(__int16 *)(g_SelectedUnitStackRecordPtr + 31 * slot_index + 6) != -1 )
    {
      LOBYTE(g_UnitStackSlotSelectedFlags[slot_index]) ^= 1u;
      Diagnostics_TraceWorldMapActionEvent(
        "selection_slot_toggle",
        g_SelectedUnitIndex,
        slot_index,
        g_UnitStackSlotSelectedFlags[slot_index],
        g_UnitStackSelectionActiveUnitIndex);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_toggle_set",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      UnitStackSelection_RedrawPanel(-1, a1);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_redraw",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      WorldMap_RedrawViewport(1);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_refresh",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      Render_Begin((int)g_RenderState, 0);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_render_begin",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
    }
    handled_panel_input = 1;
  }
  if ( DD_IsFlipping((int)g_RenderState) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "selection_split_probe",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      UnitStackSelection_HasSelectedSlots());
  }
  if ( DD_IsFlipping((int)g_RenderState) && UnitStackSelection_HasSelectedSlots() )
  {
    target_tile_x = ((g_MouseCursorRawX >> g_CursorCoordShift) - 32) / 64 + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    target_tile_y = ((g_MouseCursorRawY >> g_CursorCoordShift) - 16) / 64 + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
    distance_x = *(__int16 *)g_SelectedUnitStackRecordPtr - target_tile_x;
    if ( distance_x < 0 )
      distance_x = -distance_x;
    if ( distance_x <= 1 )
    {
      distance_y = *(__int16 *)(g_SelectedUnitStackRecordPtr + 2) - target_tile_y;
      if ( distance_y < 0 )
        distance_y = -distance_y;
      if ( distance_y <= 1 )
      {
        Render_Begin((int)g_RenderState, 0);
        memset(selected_slot_indices, 0, sizeof(selected_slot_indices));
        UnitStackSelection_BuildSelectedSlotIndexList((int)g_UnitStackSlotSelectedFlags, 10, selected_slot_indices);
        Diagnostics_TraceWorldMapActionEvent(
          "selection_split_attempt",
          g_SelectedUnitIndex,
          target_tile_x,
          target_tile_y,
          selected_slot_indices[0]);
        if ( Unit_MoveSelectionFromGroupToTile(
               g_SelectedUnitIndex,
               (_DWORD *)selected_slot_indices,
               target_tile_y,
               target_tile_x,
               a2,
               0) )
        {
          Diagnostics_TraceWorldMapActionEvent(
            "selection_split_done",
            g_SelectedUnitIndex,
            target_tile_x,
            target_tile_y,
            selected_slot_indices[0]);
          memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
        }
        Render_LoadResourceSprite_v2();
        UnitStackSelection_RedrawPanel(-1, a1);
        WorldMap_RedrawViewport(1);
      }
    }
  }
  return handled_panel_input;
}
// 4238BB: simplified comparisons for 'esi.4': <0 || >=A became >=Au
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 5202E4: using guessed type int gameData;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00423AC0) --------------------------------------------------------
signed int UnitStackSelection_HasSelectedSlots()
{
  int byte_offset; // eax

  if ( g_UnitStackSelectionActiveUnitIndex != -1 )
  {
    byte_offset = 0;
    if ( *(_DWORD *)g_UnitStackSlotSelectedFlags )
      return 1;
    while ( 1 )
    {
      byte_offset += 4;
      if ( byte_offset >= 40 )
        break;
      if ( *(_DWORD *)((char *)g_UnitStackSlotSelectedFlags + byte_offset) )
        return 1;
    }
  }
  return 0;
}
// 514194: using guessed type int dword_514194;

//----- (00423B00) --------------------------------------------------------
int  UnitStackSelection_BeginForSelectedStack(DWORD a1)
{
  g_UnitStackSelectionModeActive = 1;
  g_UnitStackSelectionActiveUnitIndex = g_SelectedUnitIndex;
  Diagnostics_TraceWorldMapActionEvent(
    "selection_begin_clear",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(-1, a1);
  return WorldMap_RedrawViewport(1);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;

//----- (00423B40) --------------------------------------------------------
int __thiscall UnitStackSelection_End(void *this)
{
  UI_ClearTileHighlight(this);
  g_UnitStackSelectionModeActive = 0;
  g_UnitStackSelectionActiveUnitIndex = -1;
  return WorldMap_RedrawViewport(1);
}
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;

//----- (00423B70) --------------------------------------------------------
int __thiscall UnitStackSelection_ClearMask(void *this)
{
  (void)this;
  Diagnostics_TraceWorldMapActionEvent(
    "selection_mask_clear",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  return (int)(uintptr_t)g_UnitStackSlotSelectedFlags;
}

//----- (00423B90) --------------------------------------------------------
int  UnitStackSelection_RefreshForSelectedStack(DWORD a1)
{
  g_UnitStackSelectionActiveUnitIndex = g_SelectedUnitIndex;
  UnitStackSelection_RedrawPanel(-1, a1);
  return WorldMap_RedrawViewport(1);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;

//----- (00423BB0) --------------------------------------------------------
BOOL  MapTile_HasNorthRoadConnection(int row, int column)
{
  int roadTileId; // eax

  roadTileId = Map_NormalizeRoadOverlayTileId(*(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4));
  return roadTileId == 867 || roadTileId == 869 || roadTileId == 871 || roadTileId == 872 || roadTileId == 874 || roadTileId == 875 || roadTileId == 868 || roadTileId == 952;
}
// 5202E4: using guessed type int gameData;

//----- (00423C50) --------------------------------------------------------
BOOL  MapTile_HasSouthRoadConnection(int row, int column)
{
  int roadTileId; // eax

  roadTileId = Map_NormalizeRoadOverlayTileId(*(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4));
  return roadTileId == 867 || roadTileId == 869 || roadTileId == 870 || roadTileId == 872 || roadTileId == 873 || roadTileId == 875 || roadTileId == 876 || roadTileId == 951;
}
// 5202E4: using guessed type int gameData;

//----- (00423CF0) --------------------------------------------------------
BOOL  MapTile_HasWestRoadConnection(int row, int column)
{
  int neighborBuildingMarker; // eax
  unsigned __int8 *neighborBuildingPtr; // eax
  int buildingType; // edx
  int buildingRow; // edx
  int buildingColumn; // edx
  int roadTileId; // eax
  BOOL result; // eax

  neighborBuildingMarker = *(unsigned __int16 *)(gameData + 200 * row + 2 * column + 556370);
  result = 1;
  if ( neighborBuildingMarker < 0x8000
    || neighborBuildingMarker > 65534
    || (neighborBuildingPtr = (unsigned __int8 *)(BUILDING_RECORD_SIZE * (neighborBuildingMarker - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET), buildingType = (char)neighborBuildingPtr[4], buildingType != 2) && buildingType != 1
    || (buildingRow = *neighborBuildingPtr, buildingRow != row)
    || (buildingColumn = row ^ buildingRow, LOBYTE(buildingColumn) = neighborBuildingPtr[1], buildingColumn != column - 2) )
  {
    roadTileId = Map_NormalizeRoadOverlayTileId(*(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * (column - 1) + 4));
    if ( roadTileId != 866 && roadTileId != 868 && roadTileId != 869 && roadTileId != 870 && roadTileId != 871 && roadTileId != 872 && roadTileId != 873 && roadTileId != 949 )
      return 0;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00423E10) --------------------------------------------------------
BOOL  MapTile_HasEastRoadConnection(int row, int column)
{
  int roadTileId; // eax

  roadTileId = Map_NormalizeRoadOverlayTileId(*(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * (column + 1) + 4));
  return roadTileId == 866 || roadTileId >= 871 && roadTileId <= 876 || roadTileId == 950;
}
// 5202E4: using guessed type int gameData;

//----- (00423E90) --------------------------------------------------------
int  Map_RebuildRoadOverlayAtTile(int row, int column)
{
  int maskWest; // esi
  int v4; // ecx
  int maskWestSouth; // esi
  int v6; // ecx
  int maskWestSouthEast; // esi
  int v8; // ecx
  int overlaySprite; // edx
  int v10; // ecx
  int columnByteOffset; // ecx
  int result; // eax

  maskWest = 8 * MapTile_HasWestRoadConnection(row, column);
  maskWestSouth = (4 * MapTile_HasSouthRoadConnection(row, v4)) | maskWest;
  maskWestSouthEast = (2 * MapTile_HasEastRoadConnection(row, v6)) | maskWestSouth;
  overlaySprite = g_RoadOverlaySpriteByConnectionMask[maskWestSouthEast | MapTile_HasNorthRoadConnection(row, v8)];
  columnByteOffset = 14 * v10;
  result = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  if ( overlaySprite )
    *(_WORD *)(columnByteOffset + result + 4) = overlaySprite;
  else
    *(_WORD *)(columnByteOffset + result + 4) = -1;
  return result;
}
// 423EA7: variable 'v4' is possibly undefined
// 423EB9: variable 'v6' is possibly undefined
// 423EC6: variable 'v8' is possibly undefined
// 423EDF: variable 'v10' is possibly undefined
// 5141A0: using guessed type int dword_5141A0[27];
// 5202E4: using guessed type int gameData;

//----- (00423FC0) --------------------------------------------------------
int  Map_NormalizeRoadOverlayTileId(int result)
{
  if ( result >= 819 && result <= 861 )
    return *((unsigned __int16 *)UI_Locale_BuildingNames_I + result + 1);
  if ( result >= 877 && result <= 949 )
    return ((result - 877) % 6 / 3 == 0) + 866;
  return result;
}
// 513BD4: using guessed type char *off_513BD4[26];

//----- (00424020) --------------------------------------------------------
signed int  MapTile_HasAlignedBridgeApproachRoadOverlay(int refRow, int refColumn, int column, int row)
{
  int v6; // edx
  int v7; // ebx
  int matchedApproachIndex; // ecx
  int overlayTileId; // ebx
  unsigned int v10; // eax
  int approachIndex; // edx
  int colOffset; // edi

  v6 = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  v7 = 14 * column;
  matchedApproachIndex = -1;
  overlayTileId = *(unsigned __int16 *)(v6 + v7 + 2);
  v10 = 0;
  approachIndex = 0;
  do
  {
    if ( overlayTileId == g_BridgeApproachRoadOverlayTileIds[approachIndex] )
      matchedApproachIndex = v10;
    ++v10;
    ++approachIndex;
  }
  while ( v10 < 0x30 && matchedApproachIndex == -1 );
  if ( matchedApproachIndex >= 6 )
  {
    if ( column != refColumn )
      return 0;
  }
  else if ( row != refRow )
  {
    return 0;
  }
  if ( matchedApproachIndex != -1 )
  {
    colOffset = 2 * column;
    if ( *(unsigned __int16 *)(7 * colOffset + TILE_TERRAIN_ROW_STRIDE * row + gameData) >= 0x25Bu
      && *(unsigned __int16 *)(7 * colOffset + TILE_TERRAIN_ROW_STRIDE * row + gameData) <= 0x262u )
    {
      return 1;
    }
  }
  return 0;
}
// 51420C: using guessed type int g_BridgeApproachRoadOverlayTileIds[];
// 5202E4: using guessed type int gameData;

//----- (00424120) --------------------------------------------------------
BOOL  MapTile_IsBareBridgeCrossingRoadOverlayCandidate(int row, int column)
{
  int southOverlay; // ebp
  int v3; // eax
  int westOverlay; // ecx
  unsigned int northOverlay; // edi
  int eastOverlay; // ebx
  unsigned __int16 *tilePtr; // eax
  int baseTileId; // eax
  BOOL result; // eax

  if ( !row || *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 == row || !column || column == *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 )
    return 0;
  southOverlay = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4);
  v3 = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  westOverlay = *(unsigned __int16 *)(14 * (column - 1) + v3 + 4);
  northOverlay = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4);
  eastOverlay = *(unsigned __int16 *)(14 * (column + 1) + v3 + 4);
  if ( northOverlay >= 0x36D && *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) <= 0x3B4u )
    northOverlay = (int)(northOverlay - 877) % 6;
  if ( *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) >= 0x36Du
    && *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) <= 0x3B4u )
  {
    southOverlay = (southOverlay - 877) % 6;
  }
  if ( *(unsigned __int16 *)(14 * (column - 1) + v3 + 4) >= 0x36Du
    && *(unsigned __int16 *)(14 * (column - 1) + v3 + 4) <= 0x3B4u )
  {
    westOverlay = (westOverlay - 877) % 6;
  }
  if ( *(unsigned __int16 *)(14 * (column + 1) + v3 + 4) >= 0x36Du
    && *(unsigned __int16 *)(14 * (column + 1) + v3 + 4) <= 0x3B4u )
  {
    eastOverlay = (eastOverlay - 877) % 6;
  }
  tilePtr = (unsigned __int16 *)(TILE_TERRAIN_RECORD_STRIDE * column + TILE_TERRAIN_ROW_STRIDE * row + gameData);
  result = 0;
  if ( tilePtr[1] == 0xFFFF )
  {
    baseTileId = *tilePtr;
    if ( baseTileId >= 603 && baseTileId <= 610 && (northOverlay <= 1 || southOverlay == 1 || southOverlay == 2 || westOverlay == 3 || westOverlay == 4 || eastOverlay == 4 || eastOverlay == 5) )
      return 1;
  }
  return result;
}
// 424328: simplified comparisons for 'edi.4': !=0 && !=1 became >=2u
// 5202E4: using guessed type int gameData;

//----- (00424370) --------------------------------------------------------
signed int  Map_GetBridgeCrossingCostOrZero(int row, int column)
{
  int rowBase; // ebx
  int colOffset; // edx

  rowBase = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  colOffset = 2 * column;
  if ( *(unsigned __int16 *)(rowBase + 7 * colOffset) < 0x25Bu || *(unsigned __int16 *)(rowBase + 7 * colOffset) > 0x262u )
    return 0;
  else
    return 5;
}
// 5202E4: using guessed type int gameData;

//----- (00424400) --------------------------------------------------------
signed int  Road_Build(int unitIndex, int direction, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int unitStackRecordBase; // eax
  BOOL hasNorthRoad; // ebx
  BOOL hasSouthRoad; // edi
  BOOL hasEastRoad; // eax
  int hasWestRoad; // ecx
  int targetRow; // esi
  int targetColumn; // ebp
  __int16 roadOverlayTileId; // di
  unsigned __int16 *originTilePtr; // edx
  int v15; // eax
  unsigned __int16 neighborBaseTileId; // ax
  int v17; // eax
  int v18; // eax
  signed int result; // eax
  signed int minActionPoints; // eax
  signed int v21; // edx
  unsigned __int16 neighborPrevOverlay; // di
  int v23; // ecx
  int v24; // ebx
  DWORD unitStackByteOffset; // ebp
  int v26; // ebx
  int v27; // edx
  int v28; // [esp-4h] [ebp-44h]
  int originRow; // [esp+8h] [ebp-38h]
  int bridgeCrossOverlayId; // [esp+Ch] [ebp-34h]
  signed int moveCost; // [esp+10h] [ebp-30h]
  int savedTargetOverlay; // [esp+14h] [ebp-2Ch]
  int appliedTargetOverlay; // [esp+1Ch] [ebp-24h]
  int bridgeApproachOverlayId; // [esp+24h] [ebp-1Ch]
  int originColumn; // [esp+28h] [ebp-18h]

  Debug_Log(unitIndex, a3, a4, (int)aRoad_buildDD);
  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * v5;
  originRow = *(__int16 *)(unitStackRecordBase + 147174);
  originColumn = *(__int16 *)(unitStackRecordBase + 147176);
  hasNorthRoad = MapTile_HasNorthRoadConnection(originRow, originColumn);
  hasSouthRoad = MapTile_HasSouthRoadConnection(originRow, originColumn);
  MapTile_HasWestRoadConnection(originRow, originColumn);
  hasEastRoad = MapTile_HasEastRoadConnection(originRow, originColumn);
  switch ( direction )
  {
    case 0:
      targetRow = originRow;
      targetColumn = originColumn - 1;
      if ( !hasEastRoad && hasNorthRoad && !hasSouthRoad )
      {
        roadOverlayTileId = 876;
        goto LABEL_14;
      }
      if ( !hasEastRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 874;
        goto LABEL_14;
      }
      if ( !hasEastRoad && hasNorthRoad && hasSouthRoad )
        goto LABEL_40;
      if ( hasEastRoad && hasNorthRoad && !hasSouthRoad )
        goto LABEL_41;
      if ( hasEastRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( !hasEastRoad || !hasNorthRoad || !hasSouthRoad )
        goto LABEL_44;
      goto LABEL_13;
    case 2:
      targetColumn = originColumn;
      targetRow = originRow + 1;
      if ( !hasNorthRoad && hasWestRoad && !hasEastRoad )
      {
        roadOverlayTileId = 874;
        goto LABEL_14;
      }
      if ( !hasNorthRoad && !hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 868;
        goto LABEL_14;
      }
      if ( !hasNorthRoad && hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( hasNorthRoad && hasWestRoad && !hasEastRoad )
        goto LABEL_40;
      if ( hasNorthRoad && !hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 869;
        goto LABEL_14;
      }
      if ( hasNorthRoad && hasWestRoad && hasEastRoad )
        goto LABEL_13;
      goto LABEL_68;
    case 4:
      targetRow = originRow;
      targetColumn = originColumn + 1;
      if ( !hasWestRoad && hasNorthRoad && !hasSouthRoad )
      {
        roadOverlayTileId = 870;
        goto LABEL_14;
      }
      if ( !hasWestRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 868;
        goto LABEL_14;
      }
      if ( !hasWestRoad && hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 869;
        goto LABEL_14;
      }
      if ( hasWestRoad && hasNorthRoad && !hasSouthRoad )
      {
LABEL_41:
        roadOverlayTileId = 873;
        goto LABEL_14;
      }
      if ( hasWestRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( !hasWestRoad || !hasNorthRoad || !hasSouthRoad )
      {
LABEL_44:
        roadOverlayTileId = 866;
        goto LABEL_14;
      }
      goto LABEL_13;
    case 6:
      targetColumn = originColumn;
      targetRow = originRow - 1;
      if ( hasSouthRoad || !hasWestRoad || hasEastRoad )
      {
        if ( hasSouthRoad || hasWestRoad || !hasEastRoad )
        {
          if ( !hasSouthRoad && hasWestRoad && hasEastRoad )
          {
            roadOverlayTileId = 873;
          }
          else if ( hasSouthRoad && hasWestRoad && !hasEastRoad )
          {
LABEL_40:
            roadOverlayTileId = 875;
          }
          else if ( hasSouthRoad && !hasWestRoad && hasEastRoad )
          {
            roadOverlayTileId = 869;
          }
          else if ( hasSouthRoad && hasWestRoad && hasEastRoad )
          {
LABEL_13:
            roadOverlayTileId = 872;
          }
          else
          {
LABEL_68:
            roadOverlayTileId = 867;
          }
        }
        else
        {
          roadOverlayTileId = 870;
        }
      }
      else
      {
        roadOverlayTileId = 876;
      }
LABEL_14:
      originTilePtr = (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * originRow + TILE_TERRAIN_RECORD_STRIDE * originColumn);
      HIWORD(v15) = 0;
      if ( *originTilePtr >= 0x25Bu )
      {
        LOWORD(v15) = *originTilePtr;
        if ( v15 <= 642 )
          roadOverlayTileId = originTilePtr[2];
      }
      appliedTargetOverlay = 0;
      savedTargetOverlay = 0;
      if ( MapTile_HasAlignedBridgeApproachRoadOverlay(originRow, originColumn, targetColumn, targetRow) )
      {
        neighborBaseTileId = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 2);
        if ( neighborBaseTileId >= 0x236u )
        {
          if ( neighborBaseTileId <= 0x236u )
          {
            bridgeApproachOverlayId = 877;
          }
          else if ( neighborBaseTileId >= 0x240u )
          {
            if ( neighborBaseTileId <= 0x240u )
            {
              bridgeApproachOverlayId = 904;
            }
            else if ( neighborBaseTileId >= 0x243u )
            {
              if ( neighborBaseTileId <= 0x243u )
              {
                bridgeApproachOverlayId = 903;
              }
              else if ( neighborBaseTileId == 581 )
              {
                bridgeApproachOverlayId = 906;
              }
            }
            else if ( neighborBaseTileId == 578 )
            {
              bridgeApproachOverlayId = 901;
            }
          }
          else if ( neighborBaseTileId <= 0x237u )
          {
            bridgeApproachOverlayId = 879;
          }
          else if ( neighborBaseTileId == 569 )
          {
            bridgeApproachOverlayId = 882;
          }
        }
        else if ( neighborBaseTileId >= 0x223u )
        {
          if ( neighborBaseTileId <= 0x223u )
          {
            bridgeApproachOverlayId = 927;
          }
          else if ( neighborBaseTileId >= 0x225u )
          {
            if ( neighborBaseTileId <= 0x225u )
            {
              bridgeApproachOverlayId = 930;
            }
            else if ( neighborBaseTileId == 564 )
            {
              bridgeApproachOverlayId = 880;
            }
          }
        }
        else if ( neighborBaseTileId >= 0x220u )
        {
          if ( neighborBaseTileId <= 0x220u )
          {
            bridgeApproachOverlayId = 928;
          }
          else if ( neighborBaseTileId == 546 )
          {
            bridgeApproachOverlayId = 925;
          }
        }
        v17 = gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn;
        savedTargetOverlay = *(unsigned __int16 *)(v17 + 4);
        appliedTargetOverlay = bridgeApproachOverlayId;
        *(_WORD *)(v17 + 4) = bridgeApproachOverlayId;
        *(_DWORD *)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
      }
      if ( MapTile_IsBareBridgeCrossingRoadOverlayCandidate(targetRow, targetColumn) )
      {
        if ( !direction || direction == 4 )
        {
          bridgeCrossOverlayId = 881;
        }
        else if ( direction == 6 || direction == 2 )
        {
          bridgeCrossOverlayId = 878;
        }
        v18 = gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn;
        savedTargetOverlay = *(unsigned __int16 *)(v18 + 4);
        appliedTargetOverlay = bridgeCrossOverlayId;
        *(_WORD *)(v18 + 4) = bridgeCrossOverlayId;
        *(_DWORD *)(TILE_TERRAIN_RECORD_STRIDE * targetColumn + TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
        roadOverlayTileId = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * originRow + gameData + TILE_TERRAIN_RECORD_STRIDE * originColumn + 4);
      }
      moveCost = UnitStack_GetTileMoveCostOrZero((__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * unitIndex), targetRow, 145 * unitIndex, targetColumn);
      if ( MapTile_IsCastleFoundationTile(targetRow, targetColumn, 2) )
        moveCost = 0;
      if ( savedTargetOverlay )
        *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4) = savedTargetOverlay;
      result = moveCost;
      if ( moveCost )
      {
        minActionPoints = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * unitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( minActionPoints >= v21 )
        {
          if ( Map_GetTileSurfaceClassOrUnexplored(originRow, originColumn) == 185
            || Map_GetTileSurfaceClassOrUnexplored(targetRow, targetColumn) == 185 )
          {
            return 0;
          }
          else
          {
            *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * originRow + TILE_TERRAIN_RECORD_STRIDE * originColumn + 4) = roadOverlayTileId;
            neighborPrevOverlay = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4);
            Map_RebuildRoadOverlayAtTile(targetRow, targetColumn);
            if ( neighborPrevOverlay != 0xFFFF )
            {
              v24 = v23 + gameData + 14 * targetColumn;
              if ( *(unsigned __int16 *)(v24 + 4) == 0xFFFF )
                *(_WORD *)(v24 + 4) = neighborPrevOverlay;
            }
            if ( appliedTargetOverlay )
            {
              *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4) = appliedTargetOverlay;
            }
            else
            {
              MapTile_HasNorthRoadConnection(targetRow, targetColumn);
              MapTile_HasSouthRoadConnection(targetRow, targetColumn);
              MapTile_HasWestRoadConnection(targetRow, targetColumn);
              MapTile_HasEastRoadConnection(targetRow, targetColumn);
            }
            g_SelectedUnitIndex = unitIndex;
            v28 = targetColumn;
            unitStackByteOffset = UNIT_STACK_STRIDE * unitIndex;
            v26 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * unitIndex + 147176);
            result = (signed int)Unit_MoveTrack(unitIndex, *(__int16 *)(gameData + UNIT_STACK_STRIDE * unitIndex + UNIT_STACK_TABLE_OFFSET), targetRow, v26, UNIT_STACK_STRIDE * unitIndex, v28);
            if ( result )
            {
              qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + unitStackByteOffset + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
              j__nfree_();
              UnitStack_ExecuteQueuedPath(unitIndex, v27, v26, unitStackByteOffset, a5);
              UnitStack_SpendActionPointsClamped((__int16 *)(unitStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET), 1, unitStackByteOffset, a5);
              WorldMap_RefreshUnitStatusPanel(unitStackByteOffset);
              return 1;
            }
          }
        }
        else
        {
          return 0;
        }
      }
      return result;
    default:
      return 0;
  }
}
// 42443D: variable 'v5' is possibly undefined
// 42462D: variable 'v36' is possibly undefined
// 4246C2: variable 'v30' is possibly undefined
// 42486C: variable 'v10' is possibly undefined
// 424B6F: variable 'v21' is possibly undefined
// 424C4C: variable 'v23' is possibly undefined
// 424E8E: variable 'v27' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00424EC0) --------------------------------------------------------
signed int  UnitStack_MoveOneTileInDirection(int unitIndex, int direction, double a3)
{
  int unitStackByteOffset; // esi
  int unitStackRecordBase; // edx
  int originColumn; // ebx
  signed int result; // eax
  int v9; // edx

  g_SelectedUnitIndex = unitIndex;
  unitStackByteOffset = UNIT_STACK_STRIDE * unitIndex;
  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * unitIndex;
  originColumn = *(__int16 *)(unitStackRecordBase + 147176);
  result = (signed int)Unit_MoveTrack(
                         unitIndex,
                         *(__int16 *)(unitStackRecordBase + 147174),
                         *(__int16 *)(unitStackRecordBase + 147174) + Map_NeighborDX[2 * direction],
                         originColumn,
                         unitIndex,
                         originColumn + Map_NeighborDY[2 * direction]);
  if ( result )
  {
    qmemcpy((void *)(unitStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(unitIndex, v9, originColumn, unitIndex, a3);
    WorldMap_RefreshUnitStatusPanel(unitIndex);
    return 1;
  }
  return result;
}
// 424F4D: variable 'v9' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (00424F70) --------------------------------------------------------
BOOL  Map_TileHasOwner(int row, int column)
{
  return *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column + 4) != 0xFFFF;
}
// 5202E4: using guessed type int gameData;

//----- (00424FD0) --------------------------------------------------------
int Map_AutoUpgradeVillages()
{
  int result; // eax
  int columnIndex; // esi
  int columnTerrainOffset; // edx
  int columnTileMapOffset; // ebx
  int tileRecordPtr; // ecx
  int rowIndex; // [esp+4h] [ebp-2Ch]
  int i; // [esp+8h] [ebp-28h]
  int rowTerrainOffset; // [esp+Ch] [ebp-24h]

  rowIndex = 0;
  rowTerrainOffset = 0;
  for ( i = 0; ; i += 200 )
  {
    result = gameData;
    if ( rowIndex >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    columnIndex = 0;
    columnTerrainOffset = 0;
    columnTileMapOffset = 0;
    while ( columnIndex < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      if ( *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x36Du
        && *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x37Eu
        || *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x385u
        && *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x396u
        || *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x39Du
        && *(unsigned __int16 *)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x3AEu )
      {
        tileRecordPtr = columnTerrainOffset + gameData + rowTerrainOffset;
        if ( *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) >= (unsigned int)(*(_DWORD *)(tileRecordPtr + 10) + 30)
          && *(unsigned __int16 *)(columnTileMapOffset + i + gameData + TILE_MAP_OFFSET) == 0xFFFF )
        {
          *(_WORD *)(tileRecordPtr + 4) += 6;
          *(_DWORD *)(columnTerrainOffset + rowTerrainOffset + gameData + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
        }
      }
      columnTerrainOffset += 14;
      columnTileMapOffset += 2;
      ++columnIndex;
    }
    rowTerrainOffset += 1400;
    ++rowIndex;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004250F0) --------------------------------------------------------
int  RoadBuildMode_RequestExitAfterWidgetPress(int a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_RoadBuildModeExitRequested = 1;
  return result;
}
// 527C30: using guessed type int g_RoadBuildModeExitRequested;

//----- (00425110) --------------------------------------------------------
void RoadBuildMode_RequestExit()
{
  g_RoadBuildModeExitRequested = 1;
}
// 527C30: using guessed type int g_RoadBuildModeExitRequested;

//----- (00425120) --------------------------------------------------------
int  RoadBuildMode_HighlightBuildableAdjacentTile(int tileRow, int tileColumn)
{
  int unitStackRecordBase; // eax
  int v5; // eax
  int directionIndex; // ebp
  int v7; // ecx
  int result; // eax
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx

  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
  if ( tileRow == *(__int16 *)(unitStackRecordBase + 147174) && tileColumn - *(__int16 *)(unitStackRecordBase + 147176) == -1 )
  {
    v5 = (tileColumn - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
    g_RoadBuildModeNorthMarkerX = ((tileRow - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
    directionIndex = 0;
    g_RoadBuildModeNorthMarkerY = v5 + 59 - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
  }
  else
  {
    v9 = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
    if ( tileRow - *(__int16 *)(v9 + 147174) == 1 && tileColumn == *(__int16 *)(v9 + 147176) )
    {
      directionIndex = 1;
      v10 = ((tileRow - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
          + 42
          - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
      g_RoadBuildModeEastMarkerY = ((tileColumn - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 41;
      g_RoadBuildModeEastMarkerX = v10;
    }
    else
    {
      v11 = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
      if ( tileRow == *(__int16 *)(v11 + 147174) && tileColumn - *(__int16 *)(v11 + 147176) == 1 )
      {
        v12 = (tileColumn - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeSouthMarkerX = ((tileRow - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
        directionIndex = 2;
        g_RoadBuildModeSouthMarkerY = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex] + v12 + 26;
      }
      else
      {
        result = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
        if ( tileRow - *(__int16 *)(result + 147174) != -1 )
          return result;
        result = *(__int16 *)(result + 147176);
        if ( tileColumn != result )
          return result;
        directionIndex = 3;
        v13 = (tileColumn - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeWestMarkerX = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex]
                     + ((tileRow - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
                     + 75;
        g_RoadBuildModeWestMarkerY = v13 + 41;
      }
    }
  }
  if ( (MapTile_HasAlignedBridgeApproachRoadOverlay(
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
          tileColumn,
          tileRow)
     || MapTile_IsBareBridgeCrossingRoadOverlayCandidate(tileRow, tileColumn))
    && UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) >= 6
    || (result = UnitStack_GetTileMoveCostOrZero((__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), tileRow, gameData, tileColumn)) != 0
    && (result = MapTile_IsCastleFoundationTile(tileRow, tileColumn, 2)) == 0
    && (result = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), result >= v14)
    && (result = Map_GetTileSurfaceClassOrUnexplored(tileRow, tileColumn), result != 185) )
  {
    g_RoadBuildModeHasBuildTarget = 1;
    return UIWidget_RefreshActionButtonState((int)&g_RoadBuildModeNorthMarkerX + 53 * directionIndex, v7);
  }
  return result;
}
// 425490: variable 'v14' is possibly undefined
// 4254BF: variable 'v7' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514294: using guessed type int g_RoadBuildModeMarkerBounceOffsets[9];
// 5142B8: using guessed type int dword_5142B8;
// 5142BC: using guessed type int dword_5142BC;
// 5142ED: using guessed type int dword_5142ED;
// 5142F1: using guessed type int dword_5142F1;
// 514322: using guessed type int dword_514322;
// 514326: using guessed type int dword_514326;
// 514357: using guessed type int dword_514357;
// 51435B: using guessed type int dword_51435B;
// 5202E4: using guessed type int gameData;
// 527C34: using guessed type int dword_527C34;
// 527C38: using guessed type int g_RoadBuildModeAnimationFrameIndex;

//----- (004254E0) --------------------------------------------------------
int  RoadBuildMode_BuildInSelectedDirection(int widget, DWORD a2, double a3)
{
  int direction; // edx
  int widgetRecord; // ecx

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, widget);
  switch ( *(_DWORD *)(widgetRecord + 16) )
  {
    case 0x1B:
      direction = 0;
      break;
    case 0x1C:
      direction = 2;
      break;
    case 0x1D:
      direction = 4;
      break;
    case 0x1E:
      direction = 6;
      break;
    default:
      break;
  }
  g_WorldMapTileOverlayDrawHook = 0;
  Road_Build(g_SelectedUnitIndex, direction, (char)RoadBuildMode_HighlightBuildableAdjacentTile, a2, a3);
  g_WorldMapTileOverlayDrawHook = (int (__fastcall *)(_DWORD, _DWORD))RoadBuildMode_HighlightBuildableAdjacentTile;
  return WorldMap_RedrawViewport(1);
}
// 4254EA: variable 'v5' is possibly undefined
// 425510: variable 'v4' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);

//----- (00425540) --------------------------------------------------------
signed int  Builder_StartRoadBuildMode(DWORD a1, double a2)
{
  signed int result; // eax
  int v4; // ebx
  int (__fastcall *v5)(_DWORD, _DWORD); // ecx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int unitStackRecordBase; // esi
  int v11; // eax
  int *selectedDirectionMarker; // edx

  result = Map_GetTileSurfaceClassOrUnexplored(
             *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
             *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176));
  if ( result != 185 )
  {
    v4 = 0;
    g_ActiveCursorDescriptor = (int)&g_CursorDesc_ActionBusy;
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
    g_WorldMapTileOverlayDrawHook = v5;
    g_RoadBuildModeExitRequested = 0;
    g_RoadBuildModeControlWidgetState = 2;
    WorldMap_RedrawViewport(1);
    if ( !g_RoadBuildModeExitRequested )
    {
      while ( 1 )
      {
        DD_Pump((int)g_RenderState, v4);
        WorldMap_HandleScrollKeysAndIdle(a1);
        WorldMap_RedrawFrame(v4);
        if ( Time_Now(v8, v7) - 10 > (unsigned int)g_RoadBuildModeLastAnimationTick )
        {
          g_RoadBuildModeLastAnimationTick = Time_Now(v9, g_RoadBuildModeLastAnimationTick);
          v4 = ((_BYTE)g_RoadBuildModeAnimationFrameIndex + 1) & 7;
          g_RoadBuildModeAnimationFrameIndex = v4;
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) - 1,
            *(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176));
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176) - 1);
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET) + 1,
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176));
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176) + 1);
        }
        if ( !UIWidgetTable_PollHoverAndActions(g_RoadBuildModeControlWidgets, a1) )
        {
          RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
          if ( UI_TrySelectFriendlyStackUnderCursor() )
          {
            Render_Begin((int)g_RenderState, 0);
            goto LABEL_13;
          }
        }
        if ( DD_IsFlipping((int)g_RenderState) )
        {
          LOBYTE(v6) = g_CursorCoordShift;
          unitStackRecordBase = UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData;
          v4 = (((g_MouseCursorRawX >> g_CursorCoordShift)
               - 32
               - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
                + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
             + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)
             - *(__int16 *)(unitStackRecordBase + 147174);
          v11 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
              + (((g_MouseCursorRawY >> g_CursorCoordShift)
                - 16
                - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                 + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
              - *(__int16 *)(unitStackRecordBase + 147176);
          selectedDirectionMarker = 0;
          if ( v4 || v11 != -1 )
          {
            if ( v4 != 1 || v11 )
            {
              if ( v4 || v11 != 1 )
              {
                if ( v4 == -1 && !v11 )
                  selectedDirectionMarker = &g_RoadBuildModeWestMarkerX;
              }
              else
              {
                selectedDirectionMarker = &g_RoadBuildModeSouthMarkerX;
              }
            }
            else
            {
              selectedDirectionMarker = &g_RoadBuildModeEastMarkerX;
            }
          }
          else
          {
            selectedDirectionMarker = &g_RoadBuildModeNorthMarkerX;
          }
          if ( selectedDirectionMarker )
          {
            selectedDirectionMarker[2] = 2;
            RoadBuildMode_BuildInSelectedDirection((int)selectedDirectionMarker, a1, a2);
            g_RoadBuildModeHasBuildTarget = 0;
            WorldMap_RedrawViewport(1);
            if ( !g_RoadBuildModeHasBuildTarget )
              break;
          }
        }
        if ( g_RoadBuildModeExitRequested )
          goto LABEL_13;
      }
      g_RoadBuildModeExitRequested = 1;
    }
LABEL_13:
    g_WorldMapTileOverlayDrawHook = 0;
    g_RoadBuildModeControlWidgetState = 1;
    UIWidget_RefreshActionButtonState((int)g_RoadBuildModeControlWidgets, v6);
    result = WorldMap_RedrawViewport(1);
    g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  }
  return result;
}
// 4255AF: variable 'v5' is possibly undefined
// 4255E9: variable 'v8' is possibly undefined
// 4255E9: variable 'v7' is possibly undefined
// 4255FF: variable 'v9' is possibly undefined
// 4257B4: variable 'v6' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5142B8: using guessed type int dword_5142B8;
// 5142ED: using guessed type int dword_5142ED;
// 514322: using guessed type int dword_514322;
// 514357: using guessed type int dword_514357;
// 51438C: using guessed type _DWORD g_RoadBuildModeControlWidgets[2];
// 514394: using guessed type int dword_514394;
// 5202E4: using guessed type int gameData;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
// 527C28: using guessed type int g_RoadBuildModeLastAnimationTick;
// 527C30: using guessed type int g_RoadBuildModeExitRequested;
// 527C34: using guessed type int dword_527C34;
// 527C38: using guessed type int g_RoadBuildModeAnimationFrameIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00425850) --------------------------------------------------------
int UnitBattle_InitPathingTables()
{
  int cellIndex; // edx
  int columnIndex; // ecx
  int columnByteOffset; // esi
  int blockedCellIndex; // ebx
  int terrainTileId; // eax
  int unitTypeIndex; // edx
  int unitTypeFlagsOffset; // ecx
  int result; // eax
  int rowByteOffset; // [esp+0h] [ebp-14h]
  int rowIndex; // [esp+4h] [ebp-10h]
  int rowCellBase; // [esp+8h] [ebp-Ch]

  rowIndex = 0;
  rowByteOffset = 0;
  rowCellBase = 0;
  while ( rowIndex < *(_DWORD *)(g_MapData + 804) )
  {
    cellIndex = rowCellBase;
    columnIndex = 0;
    columnByteOffset = 0;
    blockedCellIndex = rowCellBase;
    while ( columnIndex < *(_DWORD *)(g_MapData + 800) )
    {
      terrainTileId = *(__int16 *)(columnByteOffset + rowByteOffset + g_MapData);
      if ( terrainTileId == 313
        || terrainTileId >= 315 && terrainTileId <= 320
        || terrainTileId == 322
        || terrainTileId == 325
        || terrainTileId >= 328 && terrainTileId <= 329
        || terrainTileId >= 338 && terrainTileId <= 341
        || terrainTileId >= 344 && terrainTileId <= 352
        || terrainTileId == 356 )
      {
        g_TilePassabilityMask[blockedCellIndex] = 0;
      }
      else
      {
        g_TilePassabilityMask[cellIndex] = *(_BYTE *)(g_MapData + 816);
      }
      columnByteOffset += 2;
      ++cellIndex;
      ++blockedCellIndex;
      ++columnIndex;
    }
    rowByteOffset += 40;
    rowCellBase += 32;
    ++rowIndex;
  }
  unitTypeIndex = 0;
  unitTypeFlagsOffset = 0;
  do
  {
    ++unitTypeIndex;
    result = g_UnitTypeFlags[unitTypeFlagsOffset] & 1;
    unitTypeFlagsOffset += 22;
    g_UnitTypeBattleMoveFlagsMinus1[unitTypeIndex] = result;
  }
  while ( unitTypeIndex < 40 );
  return result;
}
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;

//----- (00425970) --------------------------------------------------------
signed int  UnitBattle_GetTileMoveCostOrZero(int unitTypeIndex, int row, int column)
{
  if ( !g_MapIgnoreUnitOccupancy && *(__int16 *)(40 * row + g_MapData + 2 * column + 1534) != -1 )
    return 0;
  if ( g_UnitTypeFlatMoveCostFlags[unitTypeIndex] )
    return 5;
  if ( *(_BYTE *)(g_MapData + 20 * row + column + 3134) )
    return 0;
  return (unsigned __int8)g_TilePassabilityMask[32 * row + column];
}
// 531CB8: using guessed type int g_MapIgnoreUnitOccupancy;
// 532048: using guessed type int g_MapData;

//----- (00425A00) --------------------------------------------------------
int * UnitBattle_MoveTrack(int unitIndex, int targetRow, int a3, int targetColumn, DWORD a5)
{
  int rowEndOffset; // ebx
  int i; // ecx
  unsigned int initOffset; // eax
  int v10; // edx
  int startCellPtr; // eax
  char v12; // bl
  int scanRow; // ebp
  int scanColumn; // edi
  int currentCost; // eax
  int neighborRow; // esi
  int neighborCost; // edx
  int neighborOffset; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int goalOffset; // eax
  unsigned __int16 goalCost; // dx
  int *allocatedPath; // eax
  unsigned __int8 v30; // dl
  int pathCount; // ecx
  int rowDelta; // ebp
  int colDelta; // ecx
  int curTraceRow; // edi
  int candRow; // esi
  int candColumn; // edx
  unsigned __int16 tileCost; // ax
  int stepCost; // ebx
  int v39; // eax
  int nextCellCost; // eax
  int stepCount; // ecx
  int v42; // edx
  int v43; // eax
  int *v44; // ecx
  int v45; // eax
  int v46; // esi
  int v47; // eax
  int v48; // edx
  int v49; // esi
  int v50; // eax
  int v51; // esi
  int v52; // eax
  int v53; // edx
  int v54; // esi
  __int16 costGrid[401]; // [esp+2h] [ebp-396h]
  unsigned int neighborDirOffset; // [esp+324h] [ebp-74h]
  int currentOffset; // [esp+328h] [ebp-70h]
  int unitIndexLocal; // [esp+32Ch] [ebp-6Ch]
  int goalRow; // [esp+330h] [ebp-68h]
  int goalColumn; // [esp+334h] [ebp-64h]
  int unitTypeIndex; // [esp+338h] [ebp-60h]
  int startRow; // [esp+33Ch] [ebp-5Ch]
  int startColumn; // [esp+340h] [ebp-58h]
  int gridChanged; // [esp+344h] [ebp-54h]
  int *pathBuffer; // [esp+348h] [ebp-50h]
  int v66; // [esp+34Ch] [ebp-4Ch]
  int v67; // [esp+350h] [ebp-48h]
  int v68; // [esp+354h] [ebp-44h]
  int v69; // [esp+358h] [ebp-40h]
  int packedStep; // [esp+35Ch] [ebp-3Ch]
  int bestRowDelta; // [esp+360h] [ebp-38h]
  int bestColDelta; // [esp+364h] [ebp-34h]
  int v73; // [esp+368h] [ebp-30h]
  int rowByteOffset; // [esp+36Ch] [ebp-2Ch]
  unsigned int cellByteOffset; // [esp+370h] [ebp-28h]
  int traceCost; // [esp+374h] [ebp-24h]
  int savedBlockerCell; // [esp+378h] [ebp-20h]
  int bestCost; // [esp+37Ch] [ebp-1Ch]
  unsigned __int8 traceRow; // [esp+380h] [ebp-18h]
  unsigned __int8 traceColumn; // [esp+384h] [ebp-14h]

  unitIndexLocal = unitIndex;
  goalRow = targetRow;
  goalColumn = targetColumn;
  Debug_Log(a3, unitIndex, a5, (int)aUnitbattle_m_0);
  unitTypeIndex = *(__int16 *)(g_MapData + 31 * unitIndex + 852);
  startRow = *(unsigned __int16 *)(g_MapData + 31 * unitIndex + 856);
  startColumn = *(unsigned __int16 *)(g_MapData + 31 * unitIndex + 858);
  if ( goalRow < 0
    || goalColumn < 0
    || goalRow >= *(_DWORD *)(g_MapData + 804)
    || goalColumn >= *(_DWORD *)(g_MapData + 800)
    || !UnitBattle_GetTileMoveCostOrZero(unitTypeIndex, goalRow, goalColumn) )
  {
    return 0;
  }
  rowEndOffset = 40;
  for ( i = 0; i < 20; ++i )
  {
    initOffset = 40 * i;
    do
    {
      initOffset += 2;
      costGrid[initOffset / 2] = -2;
    }
    while ( initOffset != rowEndOffset );
    rowEndOffset += 40;
  }
  v10 = 40 * startRow + g_MapData;
  startCellPtr = v10 + 2 * startColumn;
  LOWORD(v10) = *(_WORD *)(startCellPtr + 1534);
  *(_WORD *)(startCellPtr + 1534) = -1;
  savedBlockerCell = v10;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836)
    && *(unsigned __int8 *)(31 * unitIndexLocal + g_MapData + 854) == *(_DWORD *)(g_MapData + 840) )
  {
    UnitBattle_TemporarilyClearGateBlocker();
  }
  v12 = startRow;
  costGrid[20 * startRow + 1 + startColumn] = 0;
  do
  {
    scanRow = 0;
    gridChanged = 0;
    while ( scanRow < *(_DWORD *)(g_MapData + 804) )
    {
      scanColumn = 0;
      rowByteOffset = 40 * scanRow;
      cellByteOffset = 40 * scanRow;
      while ( scanColumn < *(_DWORD *)(g_MapData + 800) )
      {
        i = cellByteOffset;
        currentCost = (unsigned __int16)costGrid[cellByteOffset / 2 + 1];
        if ( (unsigned __int16)currentCost != 65534 && currentCost != 0xFFFF )
        {
          neighborDirOffset = 0;
          currentOffset = 2 * scanColumn + rowByteOffset;
          do
          {
            neighborRow = scanRow + Map_NeighborDX[neighborDirOffset / 4];
            i = scanColumn + Map_NeighborDY[neighborDirOffset / 4];
            if ( neighborRow >= 0 && neighborRow < *(_DWORD *)(g_MapData + 804) && i >= 0 && i < *(_DWORD *)(g_MapData + 800) )
            {
              LOWORD(neighborCost) = UnitBattle_GetTileMoveCostOrZero(unitTypeIndex, scanRow + Map_NeighborDX[neighborDirOffset / 4], scanColumn + Map_NeighborDY[neighborDirOffset / 4]);
              if ( (_WORD)neighborCost )
              {
                if ( neighborRow != scanRow && i != scanColumn )
                {
                  neighborCost = (23 * (unsigned __int16)neighborCost
                       - (__CFSHL__((23 * (unsigned __int16)neighborCost) >> 31, 4)
                        + 16 * ((23 * (unsigned __int16)neighborCost) >> 31))) >> 4;
                  if ( neighborRow - scanRow == i - scanColumn )
                  {
                    if ( neighborRow <= scanRow )
                      v19 = scanRow;
                    else
                      v19 = neighborRow;
                    v66 = g_MapData + 20 * (v19 - 1) + 3134;
                    if ( i <= scanColumn )
                      v20 = scanColumn;
                    else
                      v20 = i;
                    if ( *(_BYTE *)(v66 + v20) )
                      goto LABEL_30;
                    v21 = neighborRow <= scanRow ? scanRow : neighborRow;
                    v73 = 20 * v21;
                    v67 = 20 * v21 + g_MapData + 3134;
                    v22 = i <= scanColumn ? scanColumn : i;
                    if ( *(_BYTE *)(v67 + v22 - 1) )
                      goto LABEL_30;
                  }
                  else
                  {
                    if ( neighborRow <= scanRow )
                      v23 = scanRow;
                    else
                      v23 = neighborRow;
                    v68 = g_MapData + 20 * (v23 - 1) + 3134;
                    if ( i <= scanColumn )
                      v24 = scanColumn;
                    else
                      v24 = i;
                    if ( *(_BYTE *)(v68 + v24 - 1) )
                      goto LABEL_30;
                    v25 = neighborRow <= scanRow ? scanRow : neighborRow;
                    v73 = 20 * v25;
                    v69 = 20 * v25 + g_MapData + 3134;
                    v26 = i <= scanColumn ? scanColumn : i;
                    if ( *(_BYTE *)(v69 + v26) )
                      goto LABEL_30;
                  }
                }
                v73 = *(unsigned __int16 *)((char *)&costGrid[1] + currentOffset);
                neighborOffset = 40 * neighborRow + 2 * i;
                i = *(unsigned __int16 *)((char *)&costGrid[1] + neighborOffset);
                if ( (unsigned __int16)i > (unsigned __int16)neighborCost + v73 )
                {
                  i = currentOffset;
                  *(__int16 *)((char *)&costGrid[1] + neighborOffset) = *(__int16 *)((char *)&costGrid[1] + currentOffset) + neighborCost;
                  gridChanged = 1;
                }
              }
              else
              {
                i = 40 * neighborRow + 2 * i;
                *(__int16 *)((char *)&costGrid[1] + i) = -1;
              }
            }
LABEL_30:
            neighborDirOffset += 8;
          }
          while ( neighborDirOffset != 64 );
        }
        v12 = cellByteOffset + 2;
        ++scanColumn;
        cellByteOffset += 2;
      }
      ++scanRow;
    }
  }
  while ( gridChanged );
  goalOffset = 2 * goalColumn + 40 * goalRow;
  goalCost = *(__int16 *)((char *)&costGrid[1] + goalOffset);
  pathBuffer = 0;
  if ( goalCost != 65534 )
  {
    LOWORD(goalOffset) = *(__int16 *)((char *)&costGrid[1] + goalOffset);
    traceRow = goalRow;
    traceCost = goalOffset;
    allocatedPath = (int *)Mem_Alloc(404, i, v12, 0);
    traceColumn = goalColumn;
    if ( allocatedPath )
      *allocatedPath = 0;
    HIWORD(packedStep) = HIWORD(g_UnitMoveTrackPackedNodeScratch);
    LOBYTE(packedStep) = traceRow;
    pathBuffer = allocatedPath;
    BYTE1(packedStep) = traceColumn;
    pathCount = *allocatedPath;
    HIWORD(packedStep) = traceCost;
    if ( pathCount < 100 )
    {
      *allocatedPath = pathCount + 1;
      allocatedPath[pathCount + 1] = packedStep;
    }
LABEL_73:
    if ( (_WORD)traceCost )
    {
      rowDelta = -1;
      bestCost = (unsigned __int16)traceCost;
      while ( 1 )
      {
        colDelta = -1;
        do
        {
          curTraceRow = traceRow;
          candRow = traceRow + rowDelta;
          if ( candRow < 0 )
            goto LABEL_84;
          if ( candRow >= *(_DWORD *)(g_MapData + 804) )
            goto LABEL_84;
          candColumn = traceColumn + colDelta;
          if ( candColumn < 0 )
            goto LABEL_84;
          if ( candColumn >= *(_DWORD *)(g_MapData + 800) )
            goto LABEL_84;
          v73 = 40 * candRow;
          if ( (unsigned __int16)bestCost <= (unsigned __int16)costGrid[20 * candRow + 1 + candColumn] )
            goto LABEL_84;
          tileCost = UnitBattle_GetTileMoveCostOrZero(unitTypeIndex, traceRow, traceColumn);
          LOWORD(stepCost) = tileCost;
          if ( !rowDelta || !colDelta )
            goto LABEL_82;
          stepCost = (23 * tileCost - (__CFSHL__((23 * tileCost) >> 31, 4) + 16 * ((23 * tileCost) >> 31))) >> 4;
          if ( rowDelta == colDelta )
          {
            if ( curTraceRow > candRow )
              candRow = curTraceRow;
            v45 = traceColumn;
            v46 = g_MapData + 20 * (candRow - 1) + 3134;
            if ( traceColumn <= traceColumn + colDelta )
              v45 = traceColumn + colDelta;
            if ( !*(_BYTE *)(v46 + v45) )
            {
              v47 = traceRow;
              if ( traceRow <= traceRow + rowDelta )
                v47 = traceRow + rowDelta;
              v48 = traceColumn + colDelta;
              v49 = 20 * v47 + g_MapData + 3134;
              if ( traceColumn <= v48 )
              {
                if ( *(_BYTE *)(v49 + v48 - 1) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(v49 + traceColumn - 1) )
              {
                goto LABEL_84;
              }
LABEL_82:
              v39 = 40 * (rowDelta + traceRow) + 2 * (colDelta + traceColumn);
              if ( *(unsigned __int16 *)((char *)&costGrid[1] + v39) == (unsigned __int16)traceCost - (unsigned __int16)stepCost )
              {
                bestRowDelta = rowDelta;
                LOWORD(v39) = *(__int16 *)((char *)&costGrid[1] + v39);
                bestColDelta = colDelta;
                bestCost = v39;
              }
            }
          }
          else
          {
            if ( curTraceRow > candRow )
              candRow = curTraceRow;
            v50 = traceColumn;
            v51 = g_MapData + 20 * (candRow - 1) + 3134;
            if ( traceColumn <= traceColumn + colDelta )
              v50 = traceColumn + colDelta;
            if ( !*(_BYTE *)(v51 + v50 - 1) )
            {
              v52 = traceRow;
              if ( traceRow <= traceRow + rowDelta )
                v52 = traceRow + rowDelta;
              v53 = traceColumn + colDelta;
              v54 = 20 * v52 + g_MapData + 3134;
              if ( traceColumn <= v53 )
              {
                if ( *(_BYTE *)(v54 + v53) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(v54 + traceColumn) )
              {
                goto LABEL_84;
              }
              goto LABEL_82;
            }
          }
LABEL_84:
          ++colDelta;
        }
        while ( colDelta <= 1 );
        if ( ++rowDelta > 1 )
        {
          traceRow += bestRowDelta;
          LOBYTE(packedStep) = traceRow;
          nextCellCost = 2 * (unsigned __int8)(bestColDelta + traceColumn) + 40 * traceRow;
          LOWORD(nextCellCost) = *(__int16 *)((char *)&costGrid[1] + nextCellCost);
          traceCost = nextCellCost;
          HIWORD(packedStep) = nextCellCost;
          traceColumn += bestColDelta;
          stepCount = *pathBuffer;
          BYTE1(packedStep) = traceColumn;
          if ( stepCount < 100 )
          {
            v42 = stepCount;
            v43 = stepCount + 1;
            v44 = pathBuffer;
            *pathBuffer = v43;
            v44[v42 + 1] = packedStep;
          }
          goto LABEL_73;
        }
      }
    }
    --*pathBuffer;
  }
  *(_WORD *)(2 * startColumn + g_MapData + 40 * startRow + 1534) = savedBlockerCell;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836)
    && *(unsigned __int8 *)(31 * unitIndexLocal + g_MapData + 854) == *(_DWORD *)(g_MapData + 840) )
  {
    UnitBattle_RestoreGateBlocker();
  }
  return pathBuffer;
}
// 425C9A: variable 'i' is possibly undefined
// 425ED7: variable 'v30' is possibly undefined
// 425FE5: variable 'v33' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 531CBC: using guessed type int dword_531CBC;
// 532048: using guessed type int g_MapData;

//----- (004262D0) --------------------------------------------------------
int * UnitBattle_MoveTrackNear(int unit_index, int row, int col, DWORD a4)
{
  int target_row;
  int target_col;
  int target_grid_row_offset;
  int target_cost_row_offset;
  int target_grid_offset;
  int target_cost_offset;
  __int16 saved_occupant;
  char saved_cost;
  int *path;
  int *reversed_path;
  int packed_step;
  int path_count;

  target_row = row;
  target_col = col;
  Debug_Log(row, col, a4, (int)aUnitbattle_mov);
  if ( target_row < 0
    || target_col < 0
    || target_row >= *(_DWORD *)(g_MapData + 804)
    || target_col >= *(_DWORD *)(g_MapData + 800) )
  {
    return 0;
  }
  target_grid_row_offset = 40 * target_row;
  target_cost_row_offset = 20 * target_row;
  target_grid_offset = g_MapData + target_grid_row_offset + 2 * target_col + 1534;
  target_cost_offset = g_MapData + target_cost_row_offset + target_col + 3134;
  saved_occupant = *(_WORD *)target_grid_offset;
  saved_cost = *(_BYTE *)target_cost_offset;
  *(_WORD *)target_grid_offset = -1;
  *(_BYTE *)target_cost_offset = 0;
  path = UnitBattle_MoveTrack(unit_index, target_row, target_row, target_col, a4);
  if ( !path )
  {
    *(_WORD *)target_grid_offset = saved_occupant;
    *(_BYTE *)target_cost_offset = saved_cost;
    return 0;
  }
  if ( !*path )
  {
    *(_WORD *)target_grid_offset = saved_occupant;
    *(_BYTE *)target_cost_offset = saved_cost;
    nfree_((int)(uintptr_t)path);
    return 0;
  }
  reversed_path = (int *)Mem_Alloc(404, 0, target_col, a4);
  if ( reversed_path )
    *reversed_path = 0;
  if ( reversed_path )
  {
    while ( *path )
    {
      path_count = *path - 1;
      *path = path_count;
      packed_step = path[path_count + 1];
      if ( *reversed_path < 100 )
      {
        path_count = *reversed_path;
        *reversed_path = path_count + 1;
        reversed_path[path_count + 1] = packed_step;
      }
    }
    if ( (*reversed_path)-- != 1 )
    {
      while ( *reversed_path )
      {
        path_count = *reversed_path - 1;
        *reversed_path = path_count;
        packed_step = reversed_path[path_count + 1];
        if ( *path < 100 )
        {
          path_count = *path;
          *path = path_count + 1;
          path[path_count + 1] = packed_step;
        }
      }
    }
    nfree_((int)(uintptr_t)reversed_path);
  }
  *(_WORD *)target_grid_offset = saved_occupant;
  *(_BYTE *)target_cost_offset = saved_cost;
  return path;
}
// 42630A: variable 'v7' is possibly undefined
// 426380: variable 'v11' is possibly undefined
// 42638F: variable 'v13' is possibly undefined
// 4263E7: variable 'v21' is possibly undefined
// 426420: variable 'v22' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (004264D0) --------------------------------------------------------
int * UnitBattle_MoveTrackNearWall(int unit_index, int row, int col, DWORD a4)
{
  int target_row;
  int target_col;
  int current_row;
  int current_col;
  int row_delta;
  int col_delta;
  int *path_before_wall;
  int *path_after_wall;
  int *result;
  int packed_step;
  int path_count;

  target_row = row;
  target_col = col;
  Debug_Log(unit_index, row, a4, (int)aUnitbattle_m_2);
  if ( target_col < 0 || target_col >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  current_row = *(unsigned __int16 *)(31 * unit_index + g_MapData + 856);
  current_col = *(unsigned __int16 *)(31 * unit_index + g_MapData + 858);
  row_delta = current_row - target_row;
  if ( row_delta < 0 )
    row_delta = -row_delta;
  col_delta = current_col - target_col;
  if ( col_delta < 0 )
    col_delta = -col_delta;
  if ( row_delta > 1 || col_delta )
  {
    path_before_wall = 0;
    path_after_wall = 0;
    if ( target_row > 0 )
      path_before_wall = UnitBattle_MoveTrack(unit_index, target_row - 1, target_row - 1, target_col, a4);
    if ( target_row + 1 < *(_DWORD *)(g_MapData + 804) )
      path_after_wall = UnitBattle_MoveTrack(unit_index, target_row + 1, target_row + 1, target_col, a4);
    if ( path_before_wall && (!path_after_wall || HIWORD(path_before_wall[1]) <= HIWORD(path_after_wall[1])) )
      result = path_before_wall;
    else
      result = path_after_wall;
    if ( result != path_before_wall && path_before_wall )
      nfree_((int)(uintptr_t)path_before_wall);
    if ( result != path_after_wall && path_after_wall )
      nfree_((int)(uintptr_t)path_after_wall);
    return result;
  }
  result = (int *)Mem_Alloc(404, 0, target_row, a4);
  if ( result )
  {
    *result = 0;
    LOBYTE(packed_step) = target_row;
    BYTE1(packed_step) = target_col;
    HIWORD(packed_step) = 0;
    path_count = *result;
    if ( path_count < 100 )
    {
      *result = path_count + 1;
      result[path_count + 1] = packed_step;
    }
  }
  return result;
}
// 4264F4: variable 'v7' is possibly undefined
// 42652A: variable 'v6' is possibly undefined
// 42656F: variable 'v11' is possibly undefined
// 4265A6: variable 'v18' is possibly undefined
// 4265A6: variable 'v17' is possibly undefined
// 4265BF: variable 'v14' is possibly undefined
// 4265BF: variable 'v13' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00426650) --------------------------------------------------------
int * UnitBattle_MoveTrackForce(int unit_index, int col, DWORD row)
{
  int target_row;
  int target_col;
  int *result; // eax

  Debug_Log(unit_index, col, row, (int)aUnitbattle_m_3);
  target_col = col;
  target_row = (int)row;
  if ( target_row < 0 || target_row >= *(_DWORD *)(g_MapData + 804) || target_col < 0 || target_col >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  g_MapIgnoreUnitOccupancy = 1;
  if ( *(char *)(target_col + g_MapData + 20 * target_row + 3134) <= 0 )
    goto LABEL_4;
  if ( *(unsigned __int16 *)(g_MapData + 31 * unit_index + 856) < target_row )
  {
    --target_row;
LABEL_4:
    result = UnitBattle_MoveTrack(unit_index, target_row, target_row, target_col, row);
    g_MapIgnoreUnitOccupancy = 0;
    return result;
  }
  result = UnitBattle_MoveTrack(unit_index, target_row + 1, target_row + 1, target_col, row);
  g_MapIgnoreUnitOccupancy = 0;
  return result;
}
// 42667C: variable 'v3' is possibly undefined
// 42669B: variable 'v4' is possibly undefined
// 531CB8: using guessed type int g_MapIgnoreUnitOccupancy;
// 532048: using guessed type int g_MapData;

//----- (004266E0) --------------------------------------------------------
__int16  UnitBattle_Move(int a1, int a2, __int16 a3, DWORD a4)
{
  int unit_index_copy; // edx
  __int16 *unit_ptr; // esi
  _DWORD *v6; // eax
  int direction; // edi
  unsigned __int16 unit_col; // dx
  int unit_row; // eax
  int unit_record_addr; // edx
  int v11; // ebx
  int v12; // ecx
  _DWORD *sprite_set; // eax
  int unit_type; // eax
  int init_frame_index; // eax
  int *track_list; // eax
  int path_count; // edx
  int popped_step; // eax
  int *v19; // edx
  int new_count; // ecx
  int player_data_offset; // eax
  int v22; // edx
  int dest_row; // ebp
  int v24; // ecx
  int col_delta; // edx
  int row_delta; // eax
  unsigned __int8 facing_dir; // al
  int v28; // ecx
  unsigned __int16 current_col; // ax
  int is_first_frame; // ebp
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // ecx
  int current_tick; // eax
  int last_tick; // ecx
  unsigned int tick_interval; // edx
  char step_parity; // al
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // eax
  char sprite_path[100]; // [esp+0h] [ebp-9Ch] BYREF
  int step_px; // [esp+64h] [ebp-38h]
  int unit_index; // [esp+68h] [ebp-34h]
  int unit_record_offset; // [esp+6Ch] [ebp-30h]
  int move_cost; // [esp+70h] [ebp-2Ch]
  _DWORD *move_track; // [esp+74h] [ebp-28h]
  int packed_step; // [esp+78h] [ebp-24h]
  unsigned int dir_step_index; // [esp+7Ch] [ebp-20h]
  int target_offset_y; // [esp+80h] [ebp-1Ch]
  int target_offset_x; // [esp+84h] [ebp-18h]

  unit_index = a1;
  unit_index_copy = a1;
  Debug_Log(a2, a3, a4, (int)aUnitbattle_m_1);
  unit_ptr = (__int16 *)(g_MapData + 852 + 31 * unit_index_copy);
  v6 = *(_DWORD **)((char *)unit_ptr + 23);
  move_track = v6;
  if ( v6 && *v6 )
  {
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    g_SelectedUnitIndex = unit_index;
    direction = 0;
    UnitBattle_DrawSelectedUnitPanel(0, 1, a3, 0);
    unit_col = unit_ptr[3];
    unit_row = (unsigned __int16)unit_ptr[2];
    move_cost = 0;
    if ( !UnitBattle_IsTileInViewport(unit_row, unit_col) )
      UnitBattle_CenterViewOnUnit(unit_index);
    UnitBattle_RedrawVisibleGrid();
    *((_BYTE *)unit_ptr + 22) &= ~1u;
    g_ActiveUnitMoveTileIndex = unit_index;
    unit_record_addr = g_MapData + 31 * unit_index;
    LOWORD(v11) = *(unsigned __int8 *)(unit_record_addr + 854);
    Unit_BuildGoSpriteFilePath(sprite_path, *(_BYTE *)(unit_record_addr + 852), v11);
    sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, sprite_path);
    g_ActiveUnitAnimSpriteSet = (int)sprite_set;
    unit_type = *unit_ptr;
    if ( unit_type == 27 || unit_type == 30 )
      init_frame_index = *((_BYTE *)unit_ptr + 17) & 7;
    else
      init_frame_index = 0;
    g_UnitAnimFrameIndex = init_frame_index;
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    g_UnitBattleAnimFrameCount = 8;
    if ( *move_track )
    {
      unit_record_offset = 31 * unit_index;
      while ( 1 )
      {
        track_list = *(int **)((char *)unit_ptr + 23);
        path_count = *track_list - 1;
        *track_list = path_count;
        popped_step = track_list[path_count + 1];
        packed_step = popped_step;
        direction = HIWORD(popped_step);
        if ( HIWORD(popped_step) > (int)*((unsigned __int8 *)unit_ptr + 8) )
          break;
        dest_row = (unsigned __int8)packed_step;
        LOWORD(v11) = BYTE1(packed_step);
        if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(unit_record_offset + g_MapData + 852), (unsigned __int8)packed_step, BYTE1(packed_step)) )
        {
          col_delta = BYTE1(packed_step) - (unsigned __int16)unit_ptr[3];
          LOWORD(v11) = dest_row - unit_ptr[2];
          row_delta = dest_row - (unsigned __int16)unit_ptr[2];
          move_cost = direction;
          facing_dir = Facing_DirectionFromDelta8(row_delta, col_delta);
          direction = facing_dir;
          *((_BYTE *)unit_ptr + 3) = facing_dir;
          if ( !UnitBattle_IsTileInViewport(dest_row, BYTE1(packed_step)) )
          {
            UnitBattle_CenterViewOnUnit(unit_index);
            UnitBattle_RedrawVisibleGrid();
          }
          g_UnitMoveAnimOffsetX %= 64;
          g_UnitMoveAnimOffsetY %= 64;
          current_col = *(_WORD *)(unit_record_offset + g_MapData + 858);
          target_offset_x = ((unsigned __int8)packed_step - *(unsigned __int16 *)(unit_record_offset + g_MapData + 856)) << 6;
          target_offset_y = (BYTE1(packed_step) - current_col) << 6;
          last_tick = Time_Now(0, 0);
          tick_interval = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *(__int16 *)(unit_record_offset + g_MapData + 852)];
          is_first_frame = 1;
          dir_step_index = 8 * direction;
          while ( 1 )
          {
            v31 = g_UnitMoveAnimOffsetX;
            if ( g_UnitMoveAnimOffsetX <= 0 )
              v31 = -g_UnitMoveAnimOffsetX;
            v32 = v31;
            v33 = target_offset_x;
            if ( target_offset_x <= 0 )
              v33 = -target_offset_x;
            if ( v32 >= v33 )
            {
              v43 = g_UnitMoveAnimOffsetY;
              if ( g_UnitMoveAnimOffsetY <= 0 )
                v43 = -g_UnitMoveAnimOffsetY;
              LOWORD(v11) = target_offset_y;
              v44 = v43;
              v45 = target_offset_y <= 0 ? -target_offset_y : target_offset_y;
              if ( v44 >= v45 )
                break;
            }
            DD_Pump((int)g_RenderState, v11);
            UnitBattle_UpdateIdleAnimatedUnits();
            if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
              UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(v34);
            current_tick = Time_Now(0, 0);
            if ( current_tick - last_tick >= tick_interval )
            {
              step_parity = g_BattleUnitMoveAnimStepCounter;
              v39 = ++g_BattleUnitMoveAnimStepCounter;
              if ( (step_parity & 1) != 0 )
              {
                g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
                Audio_PlayBattleMapUnitMoveSound((unsigned __int16)unit_ptr[2], (unsigned __int16)unit_ptr[3], g_UnitAnimFrameIndex, *unit_ptr);
              }
              last_tick = Time_Now(0, 0);
              v40 = g_UnitMoveAnimOffsetX;
              if ( g_UnitMoveAnimOffsetX <= 0 )
                v40 = -g_UnitMoveAnimOffsetX;
              v41 = v40;
              v42 = target_offset_x;
              if ( target_offset_x <= 0 )
                v42 = -target_offset_x;
              if ( v41 >= v42 )
              {
                v46 = g_UnitMoveAnimOffsetY;
                if ( g_UnitMoveAnimOffsetY <= 0 )
                  v46 = -g_UnitMoveAnimOffsetY;
                LOWORD(v11) = target_offset_y;
                if ( target_offset_y <= 0 )
                {
                  if ( v46 >= -target_offset_y )
                    break;
                }
                else if ( v46 >= target_offset_y )
                {
                  break;
                }
              }
              if ( UnitBattle_GetSpriteVerticalOffsetPx(unit_index) )
              {
                UnitBattle_RedrawUnitNeighborhood(unit_index);
              }
              else
              {
                UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2], (unsigned __int16)unit_ptr[3]);
                if ( is_first_frame || direction == 4 || direction == 5 || direction == 3 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2], (unsigned __int16)unit_ptr[3] + 1);
                if ( is_first_frame || !direction || direction == 7 || direction == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2], (unsigned __int16)unit_ptr[3] - 1);
                if ( is_first_frame || direction == 2 || direction == 3 || direction == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] + 1, (unsigned __int16)unit_ptr[3]);
                if ( is_first_frame || direction == 6 || direction == 5 || direction == 7 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] - 1, (unsigned __int16)unit_ptr[3]);
                if ( is_first_frame || direction == 3 || direction == 7 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] + 1, (unsigned __int16)unit_ptr[3] + 1);
                if ( is_first_frame || direction == 1 || direction == 5 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] + 1, (unsigned __int16)unit_ptr[3] - 1);
                if ( is_first_frame || direction == 5 || direction == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] - 1, (unsigned __int16)unit_ptr[3] + 1);
                if ( is_first_frame || direction == 7 || direction == 3 )
                  UnitBattle_RedrawTile((unsigned __int16)unit_ptr[2] - 1, (unsigned __int16)unit_ptr[3] - 1);
              }
              is_first_frame = 0;
              step_px = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(unit_record_offset + g_MapData + 852)];
              LOBYTE(v11) = step_px;
              g_UnitMoveAnimOffsetX += step_px * Map_NeighborDX[dir_step_index / 4];
              g_UnitMoveAnimOffsetY += Map_NeighborDY[dir_step_index / 4]
                            * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(unit_record_offset + g_MapData + 852)];
            }
          }
          *(_WORD *)(g_MapData + 40 * (unsigned __int16)unit_ptr[2] + 2 * (unsigned __int16)unit_ptr[3] + 1534) = -1;
          unit_ptr[2] = (unsigned __int8)packed_step;
          unit_ptr[3] = BYTE1(packed_step);
          *(_WORD *)(2 * BYTE1(packed_step) + 40 * (unsigned __int16)unit_ptr[2] + g_MapData + 1534) = unit_index;
          if ( *move_track )
            continue;
        }
        goto LABEL_15;
      }
      v19 = *(int **)((char *)unit_ptr + 23);
      v11 = *v19;
      if ( *v19 < 100 )
      {
        new_count = v11 + 1;
        v11 *= 4;
        *v19 = new_count;
        *(int *)((char *)v19 + v11 + 4) = popped_step;
      }
    }
LABEL_15:
    *((_BYTE *)unit_ptr + 8) -= move_cost;
    nfree_((int)(uintptr_t)move_track);
    player_data_offset = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unit_ptr + 2);
    *(_DWORD *)((char *)unit_ptr + 23) = 0;
    *(_DWORD *)(gameData + player_data_offset + 140073) = 1;
    Audio_StopUnitMoveSound();
    DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
    g_ActiveUnitMoveTileIndex = -1;
    UnitBattle_RedrawVisibleGrid();
    Diagnostics_TraceWorldMapActionEvent(
      "battle_move_cleanup_skip_panel_redraw",
      unit_index,
      *((unsigned __int8 *)unit_ptr + 8),
      0,
      0);
    LOWORD(v6) = RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  }
  return (__int16)v6;
}
// 42670D: variable 'v4' is possibly undefined
// 4267B9: variable 'v12' is possibly undefined
// 4268B8: variable 'v22' is possibly undefined
// 42692F: variable 'v24' is possibly undefined
// 426950: variable 'v28' is possibly undefined
// 426A36: variable 'v34' is possibly undefined
// 426A5D: variable 'v36' is possibly undefined
// 426A61: variable 'v37' is possibly undefined
// 426AA3: variable 'v39' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 519808: using guessed type int dword_519808;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 527C40: using guessed type int dword_527C40;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00426E20) --------------------------------------------------------
int  UnitBattle_CenterViewOnUnit(int unit_index)
{
  int unit_record_offset; // eax
  int map_row_count; // ecx
  int result; // eax
  int map_col_count; // esi

  unit_record_offset = 31 * unit_index;
  *(_DWORD *)(g_MapData + 808) = *(unsigned __int16 *)(g_MapData + unit_record_offset + 856) - 3;
  *(_DWORD *)(g_MapData + 812) = *(unsigned __int16 *)(g_MapData + unit_record_offset + 858) - 3;
  if ( *(int *)(g_MapData + 808) < 0 )
    *(_DWORD *)(g_MapData + 808) = 0;
  map_row_count = *(_DWORD *)(g_MapData + 804);
  if ( *(_DWORD *)(g_MapData + 808) + 7 > map_row_count )
    *(_DWORD *)(g_MapData + 808) = map_row_count - 7;
  if ( *(int *)(g_MapData + 812) < 0 )
    *(_DWORD *)(g_MapData + 812) = 0;
  result = g_MapData;
  map_col_count = *(_DWORD *)(g_MapData + 800);
  if ( *(_DWORD *)(g_MapData + 812) + 7 > map_col_count )
    *(_DWORD *)(g_MapData + 812) = map_col_count - 7;
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (00426EF0) --------------------------------------------------------
int  UnitBattle_CountAdjacentEnemies(int unit_record)
{
  int enemy_count; // esi
  int i; // eax
  int neighbor_row; // ecx
  int neighbor_col; // ebx
  int occupant_index; // ecx
  int unit_row; // [esp+0h] [ebp-1Ch]

  enemy_count = 0;
  unit_row = *(unsigned __int16 *)(unit_record + 4);
  for ( i = 0; i != 16; i += 2 )
  {
    neighbor_row = unit_row + g_UnitBattleAdjacentTileDeltaX[i];
    if ( neighbor_row >= 0 && neighbor_row < *(_DWORD *)(g_MapData + 804) )
    {
      neighbor_col = g_UnitBattleAdjacentTileDeltaY[i] + *(unsigned __int16 *)(unit_record + 6);
      if ( neighbor_col >= 0 && neighbor_col < *(_DWORD *)(g_MapData + 800) )
      {
        occupant_index = *(__int16 *)(g_MapData + 40 * neighbor_row + 2 * neighbor_col + 1534);
        if ( occupant_index != -1 && *(_BYTE *)(31 * occupant_index + g_MapData + 854) != *(_BYTE *)(unit_record + 2) )
          ++enemy_count;
      }
    }
  }
  return enemy_count;
}
// 514500: using guessed type int dword_514500[];
// 514504: using guessed type int dword_514504[];
// 532048: using guessed type int g_MapData;

//----- (00426F90) --------------------------------------------------------
signed int  UnitBattle_GetTargetCrowdingScale(int unit_record)
{
  signed int result; // eax

  switch ( UnitBattle_CountAdjacentEnemies(unit_record) )
  {
    case 0:
    case 1:
    case 2:
      result = 256;
      break;
    case 3:
      result = 230;
      break;
    case 4:
      result = 204;
      break;
    case 5:
      result = 179;
      break;
    default:
      result = 128;
      break;
  }
  return result;
}

//----- (00426FC0) --------------------------------------------------------
int  UnitBattle_CalcMeleeExchange(int attacker_index, int defender_index, int *defender_health, _DWORD *attacker_health, int charge_mode)
{
  char *attacker_unit; // ebx
  char *defender_unit; // esi
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int attacker_power; // ebx
  int damage_ratio; // edx
  int v16; // edx
  int result; // eax
  int attacker_damage; // edx
  int defender_remaining; // esi
  int attacker_remaining; // ecx
  signed int attacker_crowd_scale; // [esp+0h] [ebp-14h]
  signed int defender_crowd_scale; // [esp+0h] [ebp-14h]

  attacker_unit = (char *)(g_MapData + 852 + 31 * attacker_index);
  defender_unit = (char *)(31 * defender_index + g_MapData + 852);
  *attacker_health = attacker_unit[9];
  *defender_health = defender_unit[9];
  UnitBattle_GetTargetCrowdingScale((int)defender_unit);
  v10 = Unit_CalcEffectivenessB(defender_unit, v9);
  if ( (v10 * v11 - (__CFSHL__((v10 * v11) >> 31, 8) + ((v10 * v11) >> 31 << 8))) >> 8 )
  {
    UnitBattle_GetTargetCrowdingScale((int)attacker_unit);
    Unit_CalcEffectivenessA(attacker_unit, 0);
  }
  attacker_crowd_scale = UnitBattle_GetTargetCrowdingScale((int)attacker_unit);
  v12 = Unit_CalcEffectivenessB(attacker_unit, 0);
  attacker_power = (v12 * attacker_crowd_scale - (__CFSHL__((v12 * attacker_crowd_scale) >> 31, 8) + ((v12 * attacker_crowd_scale) >> 31 << 8))) >> 8;
  if ( attacker_power )
  {
    defender_crowd_scale = UnitBattle_GetTargetCrowdingScale((int)defender_unit);
    damage_ratio = Unit_CalcEffectivenessB(defender_unit, 0) * defender_crowd_scale / attacker_power;
  }
  else
  {
    damage_ratio = 1024;
  }
  if ( charge_mode )
    damage_ratio = (192 * damage_ratio - (__CFSHL__((192 * damage_ratio) >> 31, 8) + ((192 * damage_ratio) >> 31 << 8))) >> 8;
  if ( damage_ratio >= 384 )
  {
    if ( damage_ratio >= 512 )
    {
      if ( damage_ratio >= 640 )
      {
        if ( damage_ratio >= 768 )
          v16 = 15 * damage_ratio;
        else
          v16 = 12 * damage_ratio;
      }
      else
      {
        v16 = 10 * damage_ratio;
      }
    }
    else
    {
      v16 = 7 * damage_ratio;
    }
  }
  else
  {
    v16 = 5 * damage_ratio;
  }
  result = (v16 - (__CFSHL__(v16 >> 31, 8) + (v16 >> 31 << 8))) >> 8;
  attacker_damage = result;
  if ( result > 100 )
    attacker_damage = 100;
  defender_remaining = *defender_health - v13;
  *defender_health = defender_remaining;
  if ( defender_remaining <= 0 )
    *defender_health = 0;
  attacker_remaining = *attacker_health - attacker_damage;
  *attacker_health = attacker_remaining;
  if ( attacker_remaining <= 0 )
    *attacker_health = 0;
  return result;
}
// 42717E: simplified comparisons for 'ecx.4': >=180 && >=200 became >=200
// 42717E: simplified comparisons for 'ecx.4': >=200 && >=280 became >=280
// 42700A: variable 'v9' is possibly undefined
// 427014: variable 'v11' is possibly undefined
// 42712D: variable 'v13' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (004272A0) --------------------------------------------------------
int  UnitBattle_PlayAttackAnimation(int a1, int a2, int a3, int a4, unsigned __int16 *a5)
{
  __int16 *attacker_unit; // esi
  char attacker_owner; // bl
  int v7; // ecx
  _DWORD *attacker_sprite_set; // eax
  char defender_owner; // bl
  int v10; // ecx
  _DWORD *defender_sprite_set; // eax
  signed int impact_offset_x; // ebp
  unsigned int direction; // edi
  int dir_index; // ebx
  unsigned __int16 *SpriteForChar; // eax
  int v16; // eax
  unsigned __int16 *v17; // ecx
  unsigned __int16 *v18; // eax
  unsigned __int16 *v19; // ecx
  int v20; // eax
  int v21; // edx
  int vertical_offset; // edx
  int v23; // edx
  int v24; // ecx
  int v25; // ecx
  int anim_start_time; // ebx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int move_tick_interval_ms; // edx
  int v31; // ecx
  int v32; // eax
  unsigned __int8 v33; // dl
  char tick_parity; // al
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int attacker_type_move; // eax
  int step_dir_x; // eax
  unsigned __int16 *v40; // eax
  signed int v41; // ebp
  unsigned __int16 *v42; // ecx
  int v43; // eax
  unsigned __int16 *v44; // eax
  unsigned __int16 *v45; // ecx
  int v46; // eax
  int v47; // edx
  unsigned __int16 *attacker_sprite_alone; // eax
  int v49; // eax
  int v50; // eax
  int sign_x; // edx
  int v52; // eax
  int v53; // eax
  int sign_y; // ecx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // eax
  char attacker_owner_attack; // bl
  int v60; // ecx
  _DWORD *attack_sprite_set; // eax
  int v62; // ecx
  int v63; // eax
  int v64; // ecx
  int v65; // ebx
  int v66; // ecx
  int v67; // eax
  unsigned int v68; // edx
  int attacker_unit_type; // eax
  int v70; // edx
  int v71; // edx
  int v73; // eax
  int v74; // edx
  int v75; // ecx
  int v76; // edx
  int v77; // edx
  int v78; // ecx
  int v79; // eax
  int v80; // edx
  char attacker_owner_return; // bl
  int v82; // ecx
  _DWORD *return_sprite_set; // eax
  int v84; // edx
  int v85; // ebx
  int v86; // ecx
  int v87; // eax
  int v88; // ecx
  unsigned int arrival_tick_interval_ms; // edx
  char arrival_parity; // al
  int attacker_type_arrival; // eax
  int v92; // edx
  int arrival_step_dir_x; // eax
  int arrival_step_dir_y; // eax
  int v95; // ecx
  int v96; // edx
  char v97[100]; // [esp+0h] [ebp-88h] BYREF
  int defender_dead; // [esp+64h] [ebp-24h]
  int attacker_dead; // [esp+68h] [ebp-20h]
  unsigned __int16 *defender_unit; // [esp+6Ch] [ebp-1Ch]
  int defender_index; // [esp+70h] [ebp-18h]
  int attacker_index; // [esp+74h] [ebp-14h]
  int impact_offset_y; // [esp+78h] [ebp-10h]

  attacker_index = a1;
  defender_index = a2;
  attacker_dead = a4;
  defender_dead = a3;
  Debug_Log(a3, a4, (DWORD)a5, (int)aAttackanimDD);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  attacker_unit = (__int16 *)(g_MapData + 852 + 31 * attacker_index);
  if ( defender_index == -1 )
    defender_unit = 0;
  else
    defender_unit = (unsigned __int16 *)(31 * defender_index + g_MapData + 852);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3])
    || (a5 = defender_unit) != 0 && !UnitBattle_IsTileInViewport(defender_unit[2], defender_unit[3]) )
  {
    UnitBattle_CenterViewOnUnit(attacker_index);
    UnitBattle_RedrawVisibleGrid();
  }
  if ( defender_unit )
    *((_BYTE *)attacker_unit + 3) = Facing_DirectionFromDelta8(defender_unit[2] - (unsigned __int16)attacker_unit[2], defender_unit[3] - (unsigned __int16)attacker_unit[3]);
  attacker_owner = *((_BYTE *)attacker_unit + 2);
  Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)attacker_unit, attacker_owner);
  attacker_sprite_set = (_DWORD *)Mem_Alloc(4112, v7, attacker_owner, (DWORD)a5);
  if ( attacker_sprite_set )
    attacker_sprite_set = DLXSpriteSet_Load(attacker_sprite_set, v97);
  g_ActiveUnitAnimSpriteSet = (int)attacker_sprite_set;
  if ( defender_index != -1 )
  {
    defender_owner = *((_BYTE *)defender_unit + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)defender_unit, defender_owner);
    defender_sprite_set = (_DWORD *)Mem_Alloc(4112, v10, defender_owner, (DWORD)a5);
    if ( defender_sprite_set )
      defender_sprite_set = DLXSpriteSet_Load(defender_sprite_set, v97);
    g_UnitBattleAnimatingUnitSpriteSet = (int)defender_sprite_set;
  }
  impact_offset_x = 0;
  direction = *((unsigned __int8 *)attacker_unit + 3);
  impact_offset_y = 0;
  if ( defender_unit )
  {
    unsigned __int16 *defender_sprite;
    unsigned __int16 *attacker_sprite;

    defender_sprite = (unsigned __int16 *)UnitSpriteCache_FindEntryOrLoad(*defender_unit, *((_BYTE *)defender_unit + 2), 0, *((_BYTE *)defender_unit + 3));
    dir_index = 8 * *((unsigned __int8 *)attacker_unit + 3);
    if ( direction == 7 || direction == 6 || direction == 5 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      impact_offset_x = -UnitBattle_ScanSpriteFirstOpaqueRunLength(attacker_sprite) - UnitBattle_ScanSpriteMinOpaqueRunLength(defender_sprite);
    }
    else if ( direction == 1 || direction == 2 || direction == 3 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      impact_offset_x = UnitBattle_ScanSpriteMinOpaqueRunLength(attacker_sprite) + UnitBattle_ScanSpriteFirstOpaqueRunLength(defender_sprite);
    }
    if ( direction == 7 || direction < 2 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      vertical_offset = -UnitBattle_CountLeadingBlankSpriteRows(attacker_sprite) - UnitBattle_CountTrailingBlankSpriteRows(defender_sprite);
    }
    else
    {
      if ( direction != 5 && direction != 4 && direction != 3 )
        goto LABEL_20;
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      vertical_offset = UnitBattle_CountTrailingBlankSpriteRows(attacker_sprite) + UnitBattle_CountLeadingBlankSpriteRows(defender_sprite);
    }
    impact_offset_y = vertical_offset;
    goto LABEL_20;
  }
  attacker_sprite_alone = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, 8 * direction);
  if ( direction == 6 )
  {
    impact_offset_x = -UnitBattle_ScanSpriteFirstOpaqueRunLength(attacker_sprite_alone);
  }
  else
  {
    impact_offset_x = UnitBattle_ScanSpriteMinOpaqueRunLength(attacker_sprite_alone);
  }
LABEL_20:
  if ( !impact_offset_x || !impact_offset_y )
    goto LABEL_21;
  if ( impact_offset_x <= 0 )
    v50 = -1;
  else
    v50 = 1;
  sign_x = v50;
  if ( impact_offset_y <= 0 )
    v52 = -impact_offset_y;
  else
    v52 = impact_offset_y;
  if ( impact_offset_x <= 0 )
    impact_offset_x = -impact_offset_x;
  if ( impact_offset_x <= v52 )
    impact_offset_x = v52;
  impact_offset_x *= sign_x;
  if ( impact_offset_y <= 0 )
    v53 = -1;
  else
    v53 = 1;
  sign_y = v53;
  if ( impact_offset_y <= 0 )
    v55 = -impact_offset_y;
  else
    v55 = impact_offset_y;
  if ( impact_offset_x <= 0 )
  {
    if ( -impact_offset_x > v55 )
    {
      impact_offset_y = -impact_offset_x * sign_y;
      goto LABEL_21;
    }
LABEL_82:
    impact_offset_y = v55 * sign_y;
    goto LABEL_21;
  }
  if ( impact_offset_x <= v55 )
    goto LABEL_82;
  impact_offset_y = impact_offset_x * sign_y;
LABEL_21:
  v23 = 8;
  v24 = 0;
  g_ActiveUnitMoveTileIndex = attacker_index;
  g_UnitMoveAnimOffsetX = 0;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = 8;
LABEL_22:
  anim_start_time = Time_Now(v24, v23);
  while ( 1 )
  {
    v27 = g_UnitMoveAnimOffsetX;
    if ( g_UnitMoveAnimOffsetX <= 0 )
      v27 = -g_UnitMoveAnimOffsetX;
    v28 = v27;
    v29 = impact_offset_x <= 0 ? -impact_offset_x : impact_offset_x;
    if ( v28 >= v29 )
    {
      v56 = g_UnitMoveAnimOffsetY;
      if ( g_UnitMoveAnimOffsetY <= 0 )
        v56 = -g_UnitMoveAnimOffsetY;
      v57 = v56;
      v58 = impact_offset_y;
      if ( impact_offset_y <= 0 )
        v58 = -impact_offset_y;
      if ( v57 >= v58 )
        break;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)g_RenderState, anim_start_time);
    move_tick_interval_ms = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *attacker_unit];
    v32 = Time_Now(v31, move_tick_interval_ms);
    if ( v32 - anim_start_time >= (unsigned int)move_tick_interval_ms )
    {
      tick_parity = g_UnitMoveAnimTickParityCounter++;
      if ( (tick_parity & 1) != 0 )
        g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
      v35 = g_UnitMoveAnimOffsetX;
      if ( g_UnitMoveAnimOffsetX <= 0 )
        v35 = -g_UnitMoveAnimOffsetX;
      v36 = v35;
      if ( impact_offset_x <= 0 )
        v37 = -impact_offset_x;
      else
        v37 = impact_offset_x;
      if ( v36 >= v37 )
      {
        v73 = g_UnitMoveAnimOffsetY;
        if ( g_UnitMoveAnimOffsetY <= 0 )
          v73 = -g_UnitMoveAnimOffsetY;
        if ( impact_offset_y <= 0 )
        {
          if ( v73 >= -impact_offset_y )
            break;
        }
        else if ( v73 >= impact_offset_y )
        {
          break;
        }
      }
      attacker_type_move = *attacker_unit;
      if ( attacker_type_move == 27 || attacker_type_move == 30 )
      {
        UnitBattle_RedrawUnitNeighborhood(attacker_index);
      }
      else
      {
        UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
        if ( direction == 4 || direction == 5 || direction == 3 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
        if ( !direction || direction == 7 || direction == 1 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
        if ( direction == 2 || direction == 3 || direction == 1 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
        if ( direction == 6 || direction == 5 || direction == 7 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
        switch ( direction )
        {
          case 3u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
            break;
          case 1u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
            break;
          case 5u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
            break;
          case 7u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
            break;
        }
      }
      if ( impact_offset_x - g_UnitMoveAnimOffsetX <= 0 )
      {
        if ( impact_offset_x == g_UnitMoveAnimOffsetX )
          step_dir_x = v24;
        else
          step_dir_x = -1;
      }
      else
      {
        step_dir_x = 1;
      }
      g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * step_dir_x;
      v23 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit];
      if ( impact_offset_y - g_UnitMoveAnimOffsetY <= 0 )
      {
        if ( impact_offset_y == g_UnitMoveAnimOffsetY )
          g_UnitMoveAnimOffsetY += v23 * v24;
        else
          g_UnitMoveAnimOffsetY -= v23;
      }
      else
      {
        g_UnitMoveAnimOffsetY += v23;
      }
      goto LABEL_22;
    }
  }
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  attacker_owner_attack = *((_BYTE *)attacker_unit + 2);
  Unit_BuildAttackAnimSpritePath(v97, *(_BYTE *)attacker_unit, attacker_owner_attack);
  attack_sprite_set = (_DWORD *)Mem_Alloc(4112, v60, attacker_owner_attack, impact_offset_x);
  if ( attack_sprite_set )
    attack_sprite_set = DLXSpriteSet_Load(attack_sprite_set, v97);
  g_ActiveUnitAnimSpriteSet = (int)attack_sprite_set;
  g_UnitMoveAnimOffsetX = impact_offset_x;
  g_UnitAnimFrameIndex = 0;
  g_UnitMoveAnimOffsetY = impact_offset_y;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeAttackAnimationFrameCount[88 * *attacker_unit];
  v63 = Time_Now(v62, 0);
  v64 = 31 * attacker_index;
  v65 = v63;
  while ( g_UnitAnimFrameIndex < g_UnitBattleAnimFrameCount )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)g_RenderState, v65);
    attacker_unit_type = *(__int16 *)(v64 + g_MapData + 852);
    v70 = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * attacker_unit_type];
    v67 = Time_Now(v66, v70);
    if ( v67 - v65 >= (unsigned int)v70 )
    {
      attacker_unit_type = *(__int16 *)(v64 + g_MapData + 852);
      v70 = (unsigned __int8)g_UnitTypeAttackSoundFrameIndex[88 * attacker_unit_type];
      if ( v70 == g_UnitAnimFrameIndex )
        Audio_PlayUnitMeleeAttackSound(attacker_unit_type);
      v65 = Time_Now(v64, v70);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
      ++g_UnitAnimFrameIndex;
    }
  }
  g_UnitAnimFrameIndex = 0;
  if ( defender_index != -1 )
  {
    if ( defender_dead )
    {
      UnitBattle_PlayDeathAnimation(defender_index, v64, v65, impact_offset_x);
    }
    else
    {
      Audio_PlayUnitHitSound((__int16)*defender_unit);
      g_UnitBattleAnimatingUnitIndex = defender_index;
      g_UnitBattleHitAnimFrame = Rng_RandRange(0, 7);
      v64 = Time_Now(0, 3);
      impact_offset_x = Rng_RandRange(1, 3);
      while ( impact_offset_x >= 0 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, 0);
        v79 = Time_Now(0, 0);
        if ( (unsigned int)(v79 - v64) >= 3 )
        {
          v64 = Time_Now(0, 0);
          UnitBattle_RedrawUnitNeighborhood(defender_index);
          LOBYTE(v65) = (g_UnitBattleHitAnimFrame + 1) & 7;
          --impact_offset_x;
          g_UnitBattleHitAnimFrame = (unsigned __int8)v65;
        }
      }
      g_UnitBattleAnimatingUnitIndex = -1;
    }
  }
  if ( attacker_dead )
  {
    if ( g_UnitBattleChargeModeActive_532060 )
      UnitBattle_RefreshSelectedUnitUI();
    UnitBattle_PlayDeathAnimation(attacker_index, v64, v65, impact_offset_x);
  }
  v71 = attacker_dead;
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  if ( !v71 )
  {
    attacker_owner_return = *((_BYTE *)attacker_unit + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)attacker_unit, attacker_owner_return);
    return_sprite_set = (_DWORD *)Mem_Alloc(4112, v82, attacker_owner_return, impact_offset_x);
    if ( return_sprite_set )
      return_sprite_set = DLXSpriteSet_Load(return_sprite_set, v97);
    LOBYTE(v85) = 8;
    g_ActiveUnitAnimSpriteSet = (int)return_sprite_set;
    g_UnitAnimFrameIndex = 0;
    g_UnitBattleAnimFrameCount = 8;
    v88 = Time_Now(0, v84);
    while ( g_UnitMoveAnimOffsetX || g_UnitMoveAnimOffsetY )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, 0);
      arrival_tick_interval_ms = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *attacker_unit];
      v87 = Time_Now(v86, arrival_tick_interval_ms);
      if ( v87 - v88 >= arrival_tick_interval_ms )
      {
        arrival_parity = g_UnitArrivalAnimTickParityCounter++;
        if ( (arrival_parity & 1) != 0 )
          g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
        if ( !g_UnitMoveAnimOffsetX && !g_UnitMoveAnimOffsetY )
          break;
        attacker_type_arrival = *attacker_unit;
        if ( attacker_type_arrival == 27 || attacker_type_arrival == 30 )
        {
          UnitBattle_RedrawUnitNeighborhood(attacker_index);
        }
        else
        {
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
          if ( direction == 4 || direction == 5 || direction == 3 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
          if ( !direction || direction == 7 || direction == 1 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
          if ( direction == 2 || direction == 3 || direction == 1 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
          if ( direction == 6 || direction == 5 || direction == 7 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
          switch ( direction )
          {
            case 3u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
              break;
            case 1u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
              break;
            case 5u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
              break;
            case 7u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
              break;
          }
        }
        v92 = g_UnitMoveAnimOffsetX;
        v85 = g_UnitMoveAnimOffsetY;
        if ( -g_UnitMoveAnimOffsetX < 0 || g_UnitMoveAnimOffsetX == 0 )
        {
          if ( g_UnitMoveAnimOffsetX )
            arrival_step_dir_x = -1;
          else
            arrival_step_dir_x = 0;
        }
        else
        {
          arrival_step_dir_x = 1;
        }
        g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * arrival_step_dir_x;
        if ( -g_UnitMoveAnimOffsetY < 0 || g_UnitMoveAnimOffsetY == 0 )
        {
          if ( g_UnitMoveAnimOffsetY )
            arrival_step_dir_y = -1;
          else
            arrival_step_dir_y = 0;
        }
        else
        {
          arrival_step_dir_y = 1;
        }
        v95 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * arrival_step_dir_y + g_UnitMoveAnimOffsetY;
        v96 = g_UnitMoveAnimOffsetX * v92;
        g_UnitMoveAnimOffsetY = v95;
        if ( v96 < 0 )
          g_UnitMoveAnimOffsetX = 0;
        if ( v85 * g_UnitMoveAnimOffsetY < 0 )
          g_UnitMoveAnimOffsetY = 0;
        v88 = Time_Now(v95, v96);
      }
    }
    DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  }
  if ( g_UnitBattleAnimatingUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleAnimatingUnitSpriteSet);
  g_UnitBattleAnimatingUnitSpriteSet = 0;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  g_ActiveUnitMoveTileIndex = -1;
  return UnitBattle_RedrawVisibleGrid();
}
// 427704: conditional instruction was optimized away because ebp.4<0
// 42771F: conditional instruction was optimized away because %var_10.4<0
// 427620: simplified comparisons for 'edi.4': ==0 || ==1 became <2u
// 427389: variable 'v7' is possibly undefined
// 4273C0: variable 'v10' is possibly undefined
// 427435: variable 'v16' is possibly undefined
// 427437: variable 'v17' is possibly undefined
// 42745E: variable 'v19' is possibly undefined
// 427463: variable 'v21' is possibly undefined
// 427499: variable 'v24' is possibly undefined
// 4274DE: variable 'v31' is possibly undefined
// 4274E3: variable 'v33' is possibly undefined
// 427603: variable 'v42' is possibly undefined
// 427608: variable 'v43' is possibly undefined
// 427649: variable 'v45' is possibly undefined
// 42764E: variable 'v46' is possibly undefined
// 42764E: variable 'v47' is possibly undefined
// 427686: variable 'v49' is possibly undefined
// 427779: variable 'v25' is possibly undefined
// 4277A6: variable 'v60' is possibly undefined
// 4277E8: variable 'v62' is possibly undefined
// 427835: variable 'v66' is possibly undefined
// 42783E: variable 'v68' is possibly undefined
// 427849: variable 'v64' is possibly undefined
// 42786F: variable 'v70' is possibly undefined
// 427BBF: variable 'v74' is possibly undefined
// 427BDB: variable 'v75' is possibly undefined
// 427BE7: variable 'v76' is possibly undefined
// 427C03: variable 'v78' is possibly undefined
// 427C03: variable 'v77' is possibly undefined
// 427C0F: variable 'v80' is possibly undefined
// 427C5E: variable 'v82' is possibly undefined
// 427C86: variable 'v84' is possibly undefined
// 427CBB: variable 'v86' is possibly undefined
// 427CC0: variable 'v88' is possibly undefined
// 427CC4: variable 'v89' is possibly undefined
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 514E44: using guessed type int dword_514E44;
// 519808: using guessed type int dword_519808;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 531CC0: using guessed type int dword_531CC0;
// 531CC4: using guessed type int dword_531CC4;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00427FA0) --------------------------------------------------------
int  UnitBattle_PlayDeathAnimation(int unit_index, int a2, char a3, DWORD a4)
{
  int v5; // edx
  int unit_record_offset; // esi
  __int16 *unit_ptr; // ebp
  int v8; // ecx
  int v9; // eax
  int direction; // ecx
  int v11; // edx
  int corpse_tile_offset; // eax
  unsigned int frame_deadline; // edx
  unsigned int v14; // eax
  int v15; // ecx
  int fade_direction; // ecx
  int fade_unit_row; // ebx
  int fade_unit_col; // esi
  int final_record_offset; // edi
  int result; // eax
  int unit_row; // ebx
  int unit_col; // esi
  int v23; // edx
  int fade_record_offset; // [esp+0h] [ebp-24h]
  int corpse_record_offset; // [esp+4h] [ebp-20h]
  int last_tick; // [esp+8h] [ebp-1Ch]

  Debug_Log(a2, a3, a4, (int)aDeathanimD);
  v5 = unit_index;
  unit_record_offset = 31 * v5;
  unit_ptr = (__int16 *)(g_MapData + 852 + 31 * v5);
  Audio_PlayUnitDeathSound(*unit_ptr);
  if ( (g_UnitTypeFlags[22 * *unit_ptr] & 1) != 0 )
  {
    *(_BYTE *)(40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3] + 2334) = 48;
    UnitBattle_InitUnitFadeAnimation(unit_index, 255, -4, 255);
    v9 = Time_Now(v8, 0);
    LOWORD(v11) = unit_ptr[2];
    last_tick = v9;
    corpse_record_offset = unit_record_offset;
    *(_BYTE *)(g_MapData + 40 * v11 + 2 * (unsigned __int16)unit_ptr[3] + 2335) = -1;
    while ( 1 )
    {
      corpse_tile_offset = 40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3];
      if ( *(char *)(corpse_tile_offset + 2334) >= 56 )
        break;
      frame_deadline = last_tick + 10;
      while ( 1 )
      {
        v14 = Time_Now(direction, frame_deadline);
        if ( v14 >= frame_deadline )
          break;
        UnitBattle_UpdateIdleAnimatedUnits();
      }
      last_tick = Time_Now(v15, frame_deadline);
      UnitBattle_RedrawUnitNeighborhood(unit_index);
      UnitBattle_RedrawUnitNeighborhood(unit_index);
      direction = *(unsigned __int8 *)(corpse_record_offset + g_MapData + 855);
      unit_row = *(unsigned __int16 *)(corpse_record_offset + g_MapData + 856);
      unit_col = *(unsigned __int16 *)(corpse_record_offset + g_MapData + 858);
      if ( !*(_BYTE *)(corpse_record_offset + g_MapData + 855) || direction == 7 || direction == 1 )
        UnitBattle_RedrawTile(unit_row, unit_col - 1);
      if ( direction == 1 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col - 1);
      if ( direction == 2 || direction == 1 || direction == 3 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col);
      if ( direction == 3 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col + 1);
      if ( direction == 4 || direction == 3 || direction == 5 )
        UnitBattle_RedrawTile(unit_row, unit_col + 1);
      if ( direction == 5 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col + 1);
      if ( direction == 6 || direction == 7 || direction == 5 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col);
      if ( direction == 7 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col - 1);
      v23 = 40 * (unsigned __int16)unit_ptr[2] + g_MapData;
      ++*(_BYTE *)(v23 + 2 * (unsigned __int16)unit_ptr[3] + 2334);
    }
    *(_BYTE *)(corpse_tile_offset + 2334) = -1;
  }
  else
  {
    UnitBattle_InitUnitFadeAnimation(unit_index, 255, -8, 255);
    if ( g_UnitFadeAnimCurrentOffset )
    {
      fade_record_offset = unit_record_offset;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        UnitBattle_RedrawUnitNeighborhood(unit_index);
        fade_direction = *(unsigned __int8 *)(fade_record_offset + g_MapData + 855);
        fade_unit_row = *(unsigned __int16 *)(fade_record_offset + g_MapData + 856);
        fade_unit_col = *(unsigned __int16 *)(fade_record_offset + g_MapData + 858);
        if ( !*(_BYTE *)(fade_record_offset + g_MapData + 855) || fade_direction == 7 || fade_direction == 1 )
          UnitBattle_RedrawTile(fade_unit_row, fade_unit_col - 1);
        if ( fade_direction == 1 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col - 1);
        if ( fade_direction == 2 || fade_direction == 1 || fade_direction == 3 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col);
        if ( fade_direction == 3 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col + 1);
        if ( fade_direction == 4 || fade_direction == 3 || fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row, fade_unit_col + 1);
        if ( fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col + 1);
        if ( fade_direction == 6 || fade_direction == 7 || fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col);
        if ( fade_direction == 7 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col - 1);
        *(_BYTE *)(40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3] + 2335) = -1 - g_UnitFadeAnimCurrentOffset;
      }
      while ( g_UnitFadeAnimCurrentOffset );
    }
  }
  final_record_offset = 31 * unit_index;
  *(_WORD *)(g_MapData + final_record_offset + 852) = -1;
  result = *(unsigned __int16 *)(g_MapData + final_record_offset + 858);
  *(_WORD *)(40 * *(unsigned __int16 *)(g_MapData + final_record_offset + 856) + g_MapData + 2 * result + 1534) = -1;
  return result;
}
// 427FC9: variable 'v5' is possibly undefined
// 42802E: variable 'v8' is possibly undefined
// 42804A: variable 'v11' is possibly undefined
// 428097: variable 'v10' is possibly undefined
// 428097: variable 'v13' is possibly undefined
// 42811D: variable 'v16' is possibly undefined
// 428273: variable 'v15' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 5320F4: using guessed type int dword_5320F4;

//----- (004283D0) --------------------------------------------------------
int  UnitBattle_GetCorpseSpriteIndex(__int16 *unit_ptr)
{
  return (unsigned __int8)g_UnitTypeCorpseSpriteBaseIndex[88 * *unit_ptr] + (*((unsigned __int8 *)unit_ptr + 3) + 4) % 8;
}

//----- (00428400) --------------------------------------------------------
signed int  UnitBattle_Attack(int attacker_index, int defender_index, int charge_mode)
{
  __int16 *attacker_unit;
  __int16 *defender_unit;
  int attacker_type;
  int delta_x;
  int delta_y;
  int *move_track;
  int track_cost;
  int defender_remaining;
  int attacker_remaining;
  int defender_dead;
  int attacker_dead;
  int corpse_sprite;
  int owner_index;

  Debug_Log(charge_mode, charge_mode, attacker_index, (int)aUnitbattle_att);
  Diagnostics_TraceWorldMapActionEvent("battle_attack_enter", attacker_index, defender_index, charge_mode, 0);
  if ( !g_MapData || attacker_index < 0 || attacker_index >= 22 || defender_index < 0 || defender_index >= 22 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_attack_invalid_index", attacker_index, defender_index, charge_mode, 0);
    return 0;
  }
  attacker_unit = (__int16 *)(g_MapData + 852 + 31 * attacker_index);
  defender_unit = (__int16 *)(g_MapData + 852 + 31 * defender_index);
  attacker_type = *attacker_unit;
  if ( attacker_type == -1
    || !g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * attacker_type]
    || attacker_type == UNIT_TYPE_RAM
    || *defender_unit == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_attack_invalid_unit", attacker_index, defender_index, attacker_type, *defender_unit);
    return 0;
  }
  if ( charge_mode )
    UnitBattle_EnableSelectedChargeMode();
  UnitBattle_DrawSelectedUnitPanel(0, 1, charge_mode, (int)defender_unit);
  UnitBattle_RedrawVisibleGrid();
  delta_x = (unsigned __int16)attacker_unit[2] - (unsigned __int16)defender_unit[2];
  if ( delta_x < 0 )
    delta_x = -delta_x;
  delta_y = (unsigned __int16)attacker_unit[3] - (unsigned __int16)defender_unit[3];
  if ( delta_y < 0 )
    delta_y = -delta_y;
  if ( delta_x > 1 || delta_y > 1 )
  {
    move_track = UnitBattle_MoveTrackNear(
                   attacker_index,
                   (unsigned __int16)defender_unit[2],
                   (unsigned __int16)defender_unit[3],
                   attacker_index);
    if ( !move_track )
      goto attack_failed;
    track_cost = move_track[1];
    if ( HIWORD(track_cost) + 5 > (int)*(unsigned __int8 *)((char *)attacker_unit + 8) )
    {
      nfree_((int)(uintptr_t)move_track);
      goto attack_failed;
    }
    *(_DWORD *)((char *)attacker_unit + 23) = move_track;
    UnitBattle_Move(attacker_index, 0, 0, 0);
    if ( *(_DWORD *)((char *)attacker_unit + 23) )
    {
      nfree_(*(_DWORD *)((char *)attacker_unit + 23));
      *(_DWORD *)((char *)attacker_unit + 23) = 0;
      goto attack_failed;
    }
  }
  if ( *(unsigned __int8 *)((char *)attacker_unit + 8) < 5u )
    goto attack_failed;
  *(unsigned char *)((char *)attacker_unit + 8) -= 5;
  *(unsigned char *)((char *)attacker_unit + 22) &= 0xFEu;
  g_SelectedUnitIndex = attacker_index;
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3])
    || !UnitBattle_IsTileInViewport((unsigned __int16)defender_unit[2], (unsigned __int16)defender_unit[3]) )
  {
    UnitBattle_CenterViewOnUnit(attacker_index);
    UnitBattle_RedrawVisibleGrid();
  }
  UnitBattle_CalcMeleeExchange(attacker_index, defender_index, &defender_remaining, &attacker_remaining, charge_mode);
  *(unsigned char *)((char *)attacker_unit + 9) = (unsigned char)attacker_remaining;
  *(unsigned char *)((char *)defender_unit + 9) = (unsigned char)defender_remaining;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_attack_after_exchange",
    attacker_index,
    defender_index,
    attacker_remaining,
    defender_remaining);
  *(unsigned char *)((char *)attacker_unit + 3) = Facing_DirectionFromDelta8(
                                                     (unsigned __int16)defender_unit[2]
                                                   - (unsigned __int16)attacker_unit[2],
                                                     (unsigned __int16)defender_unit[3]
                                                   - (unsigned __int16)attacker_unit[3]);
  if ( !*(unsigned char *)((char *)defender_unit + 9) )
  {
    corpse_sprite = UnitBattle_GetCorpseSpriteIndex(defender_unit);
    *(_BYTE *)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 2334) = corpse_sprite;
    *(_BYTE *)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 2335) = 0;
  }
  if ( !*(unsigned char *)((char *)attacker_unit + 9) )
  {
    corpse_sprite = UnitBattle_GetCorpseSpriteIndex(attacker_unit);
    *(_BYTE *)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 2334) = corpse_sprite;
    *(_BYTE *)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 2335) = 0;
  }
  defender_dead = *(unsigned char *)((char *)defender_unit + 9) == 0;
  attacker_dead = *(unsigned char *)((char *)attacker_unit + 9) == 0;
  UnitBattle_PlayAttackAnimation(attacker_index, defender_index, defender_dead, attacker_dead, (unsigned __int16 *)attacker_index);
  if ( defender_dead )
  {
    *defender_unit = -1;
    *(_WORD *)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 1534) = -1;
  }
  owner_index = *(unsigned __int8 *)((char *)attacker_unit + 2);
  if ( attacker_dead )
  {
    UnitBattle_RefreshSelectedUnitUI();
    *attacker_unit = -1;
    *(_WORD *)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 1534) = -1;
    if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * owner_index + 140051) )
      UnitBattle_SelectNextControllableUnit(0, 0, (char)defender_unit);
  }
  *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * owner_index + 140073) = 1;
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, attacker_dead, (int)defender_unit);
  UnitBattle_RefreshSelectedUnitUI();
  Diagnostics_TraceWorldMapActionEvent("battle_attack_return", attacker_index, defender_index, attacker_dead, defender_dead);
  return 1;

attack_failed:
  UnitBattle_RefreshSelectedUnitUI();
  Diagnostics_TraceWorldMapActionEvent("battle_attack_failed", attacker_index, defender_index, charge_mode, 0);
  return 0;
}
// 428432: variable 'v5' is possibly undefined
// 42846E: variable 'v4' is possibly undefined
// 42852A: variable 'v13' is possibly undefined
// 42858A: variable 'v15' is possibly undefined
// 4285F0: variable 'v17' is possibly undefined
// 4286B9: variable 'v21' is possibly undefined
// 4286EF: variable 'v20' is possibly undefined
// 428763: variable 'v9' is possibly undefined
// 42878E: variable 'v24' is possibly undefined
// 42879E: variable 'v26' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;

//----- (004287E0) --------------------------------------------------------
BOOL  UnitBattle_IsTileWithinRange(int unit_index, int target_row, int target_col)
{
  int unit_record;
  int unit_type_offset;
  signed int distance; // eax

  if ( !g_MapData || unit_index < 0 || unit_index >= 22 )
    return 0;
  unit_record = g_MapData + 31 * unit_index + 852;
  if ( *(__int16 *)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(31 * unit_index + g_MapData + 852 + 4) - target_row)
       * (*(unsigned __int16 *)(31 * unit_index + g_MapData + 852 + 4) - target_row)
       + (*(unsigned __int16 *)(31 * unit_index + g_MapData + 852 + 6) - target_col)
       * (*(unsigned __int16 *)(31 * unit_index + g_MapData + 852 + 6) - target_col));
  unit_type_offset = 88 * *(__int16 *)unit_record;
  return distance <= (unsigned __int8)g_UnitTypeMaxRange[unit_type_offset]
      && distance > (unsigned __int8)g_UnitTypeMinRange[unit_type_offset];
}
// 532048: using guessed type int g_MapData;

//----- (00428850) --------------------------------------------------------
BOOL  UnitBattle_IsUnitWithinRange(int unit_index, int target_unit_index)
{
  return UnitBattle_IsTileWithinRange(
           unit_index,
           *(unsigned __int16 *)(g_MapData + 31 * target_unit_index + 856),
           *(unsigned __int16 *)(g_MapData + 31 * target_unit_index + 858));
}
// 532048: using guessed type int g_MapData;

//----- (00428880) --------------------------------------------------------
__int16  UnitBattle_PlayShotAnimation(
        int shooter_index,
        int target_unit_index,
        int target_col,
        int a4,
        int a5,
        int a6,
        __int128 a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        __int64 a16)
{
  char shooter_owner; // bl
  int v17; // ecx
  _DWORD *shooterSpriteSet; // eax
  char target_owner; // bl
  int v20; // ecx
  _DWORD *targetSpriteSet; // eax
  int v22; // ecx
  int v23; // ecx
  _DWORD *projPaletteSpriteSet; // eax
  char v25; // bl
  int v26; // edx
  int v27; // ecx
  int v28; // ecx
  unsigned __int16 shooterUnitType; // ax
  char *v30; // esi
  int v31; // ecx
  int shooter_record_offset; // edi
  int v33; // ecx
  int now; // eax
  int v35; // ecx
  unsigned int v36; // edx
  int soundUnitType; // eax
  int soundFrameIndex; // edx
  int projHalfHeight; // ebx
  unsigned __int16 v40; // cx
  unsigned __int16 SpriteWidth; // ax
  int spriteVerticalOffset; // edx
  int proj_px_y; // esi
  int v44; // ebx
  int v45; // ecx
  int v46; // ecx
  int v47; // edx
  int frameCount; // ecx
  unsigned int frameIndex; // edx
  int frameNow; // eax
  int v51; // eax
  int v52; // ecx
  int v53; // edx
  unsigned int arcPhase; // eax
  unsigned int arcOffset; // edx
  int v56; // edi
  unsigned __int16 v57; // dx
  __int16 SpriteHeight; // dx
  __int16 v59; // ax
  int v60; // eax
  __int16 v61; // ax
  int v62; // ecx
  int v63; // edx
  int v64; // ecx
  int v65; // eax
  int v66; // eax
  int v67; // edx
  int v68; // ecx
  int v69; // eax
  int v70; // edx
  int v71; // eax
  int v72; // eax
  BOOL isProjectileUnit; // eax
  int v74; // ecx
  int v75; // eax
  _DWORD *battleProjectileSpriteSet; // eax
  int v77; // eax
  _DWORD *v78; // eax
  char targetFacing; // bl
  char newTargetFacing; // al
  unsigned __int8 facingHighBits; // bl
  int v82; // edx
  int v83; // ecx
  int hitAnimTime; // ebx
  int v85; // edx
  int v86; // ecx
  int v87; // ecx
  int projAnimStartTime; // esi
  int v89; // ecx
  unsigned int hitNow; // eax
  unsigned int v91; // edx
  int v92; // ecx
  int hitAnimFrame; // edx
  int v94; // ecx
  int v95; // ecx
  int mapRowCount; // edi
  int mapColCount; // ecx
  char *v98; // esi
  char *v99; // esi
  char *v100; // esi
  int v101; // eax
  int v102; // edx
  int v103; // eax
  int SpriteForChar; // eax
  int v105; // ecx
  __int16 result; // ax
  unsigned __int16 v107; // [esp-Ch] [ebp-2BCh]
  unsigned __int16 v108; // [esp-4h] [ebp-2B4h]
  char v109[384]; // [esp+82h] [ebp-22Eh] BYREF
  char v110[44]; // [esp+202h] [ebp-AEh] BYREF
  _BYTE v111[56]; // [esp+22Eh] [ebp-82h] BYREF
  char v112[74]; // [esp+266h] [ebp-4Ah] BYREF
  unsigned __int8 *target_unit; // [esp+2D6h] [ebp+26h]
  int target_px_y; // [esp+2E2h] [ebp+32h]
  int travelDeltaX; // [esp+2E6h] [ebp+36h]
  int travelDeltaY; // [esp+2EAh] [ebp+3Ah]
  int source_px_x; // [esp+2EEh] [ebp+3Eh]
  int source_px_y; // [esp+2F2h] [ebp+42h]
  int target_row; // [esp+302h] [ebp+52h]
  int target_px_x; // [esp+306h] [ebp+56h]
  int last_tick; // [esp+30Ah] [ebp+5Ah]
  __int16 *shooter_unit; // [esp+30Eh] [ebp+5Eh]
  unsigned int projectile_frame; // [esp+312h] [ebp+62h]
  int travel_steps; // [esp+316h] [ebp+66h]
  int unitRecordOffset; // [esp+31Ah] [ebp+6Ah]
  int prevProjX; // [esp+31Eh] [ebp+6Eh]
  int shot_start_time; // [esp+322h] [ebp+72h]
  int projectile_sprite_set; // [esp+326h] [ebp+76h]
  int sprite_frame_base; // [esp+32Ah] [ebp+7Ah]
  int proj_px_x; // [esp+32Eh] [ebp+7Eh]

  target_row = a4;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  shooter_unit = (__int16 *)(g_MapData + 852 + 31 * shooter_index);
  if ( target_unit_index == -1 )
  {
    LOBYTE(a4) = 0;
    target_unit = 0;
  }
  else
  {
    target_unit = (unsigned __int8 *)(31 * target_unit_index + g_MapData + 852);
  }
  Debug_Log(target_unit_index, a4, (DWORD)v111, (int)a_shotanimDDDDD);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)shooter_unit[2], (unsigned __int16)shooter_unit[3]) || !UnitBattle_IsTileInViewport(target_row, target_col) )
  {
    *(_DWORD *)(g_MapData + 808) = (target_row + (unsigned __int16)shooter_unit[2]) / 2 - 3;
    *(_DWORD *)(g_MapData + 812) = (target_col + (unsigned __int16)shooter_unit[3]) / 2 - 3;
    if ( *(int *)(g_MapData + 808) < 0 )
      *(_DWORD *)(g_MapData + 808) = 0;
    mapRowCount = *(_DWORD *)(g_MapData + 804);
    if ( *(_DWORD *)(g_MapData + 808) + 7 > mapRowCount )
      *(_DWORD *)(g_MapData + 808) = mapRowCount - 7;
    if ( *(int *)(g_MapData + 812) < 0 )
      *(_DWORD *)(g_MapData + 812) = 0;
    mapColCount = *(_DWORD *)(g_MapData + 800);
    if ( *(_DWORD *)(g_MapData + 812) + 7 > mapColCount )
      *(_DWORD *)(g_MapData + 812) = mapColCount - 7;
    UnitBattle_RedrawVisibleGrid();
  }
  *((_BYTE *)shooter_unit + 3) = Facing_DirectionFromDelta8(target_row - (unsigned __int16)shooter_unit[2], target_col - (unsigned __int16)shooter_unit[3]);
  shooter_owner = *((_BYTE *)shooter_unit + 2);
  Unit_BuildShotAnimSpritePath(v110, *(_BYTE *)shooter_unit, shooter_owner);
  shooterSpriteSet = (_DWORD *)Mem_Alloc(4112, v17, shooter_owner, (DWORD)v111);
  if ( shooterSpriteSet )
    shooterSpriteSet = DLXSpriteSet_Load(shooterSpriteSet, shooter_owner);
  g_ActiveUnitAnimSpriteSet = (int)shooterSpriteSet;
  target_owner = 0;
  g_UnitMoveAnimOffsetX = 0;
  g_ActiveUnitMoveTileIndex = shooter_index;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeShotAnimationFrameCount[88 * *shooter_unit];
  if ( target_unit_index != -1 )
  {
    target_owner = target_unit[2];
    Unit_BuildGoSpriteFilePath(v110, *target_unit, target_owner);
    targetSpriteSet = (_DWORD *)Mem_Alloc(4112, v20, target_owner, (DWORD)v111);
    if ( targetSpriteSet )
      targetSpriteSet = DLXSpriteSet_Load(targetSpriteSet, target_owner);
    g_UnitBattleAnimatingUnitSpriteSet = (int)targetSpriteSet;
  }
  qmemcpy(v109, &g_UnitBattleShotAnimTemplate, sizeof(v109));
  Unit_BuildShotAnimPaletteSpritePath(v112, *(_BYTE *)shooter_unit);
  projectile_sprite_set = 0;
  if ( DLX_OpenArchive(v112, v22) )
  {
    projPaletteSpriteSet = (_DWORD *)Mem_Alloc(4112, v23, target_owner, (DWORD)v111);
    if ( projPaletteSpriteSet )
      projPaletteSpriteSet = DLXSpriteSet_Load(projPaletteSpriteSet, target_owner);
    projectile_sprite_set = (int)projPaletteSpriteSet;
  }
  v25 = projectile_sprite_set;
  Debug_Log(-1, projectile_sprite_set, (DWORD)v111, (int)aLoaded);
  sprite_frame_base = v27;
  v28 = g_UnitBattleAnimFrameCount - 1;
  if ( projectile_sprite_set )
  {
    *(_DWORD *)((char *)&a7 + 2) = 32 - (unsigned __int16)DLX_GetSpriteHeight(projectile_sprite_set, 0) / 2;
    v26 = 32 - (unsigned __int16)DLX_GetSpriteWidth(projectile_sprite_set, 0) / 2;
    *(_DWORD *)((char *)&a7 + 6) = v26;
  }
  shooterUnitType = *shooter_unit;
  if ( (unsigned __int16)*shooter_unit >= 0xFu )
  {
    if ( (unsigned __int16)*shooter_unit <= 0xFu )
    {
      v28 = 26;
      v26 = *((unsigned __int8 *)shooter_unit + 3);
      *(_DWORD *)((char *)&a16 + 2) = 5;
      v99 = &v109[8 * v26 + 256];
      sprite_frame_base = 5 * v26;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v99;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v99 + 1);
      *(_DWORD *)((char *)&a7 + 10) = 6;
    }
    else if ( shooterUnitType >= 0x1Cu )
    {
      if ( shooterUnitType <= 0x1Cu )
      {
        v28 = 3;
        sprite_frame_base = 8 * *((unsigned __int8 *)shooter_unit + 3);
        v26 = 6;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[sprite_frame_base + 192];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[sprite_frame_base + 196];
      }
      else if ( shooterUnitType == 30 )
      {
        v26 = (int)shooter_unit;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        v28 = 8;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        sprite_frame_base = 8 * *((unsigned __int8 *)shooter_unit + 3);
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[sprite_frame_base];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[sprite_frame_base + 4];
      }
    }
    else if ( shooterUnitType == 20 )
    {
      v25 = 1;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      sprite_frame_base = 0;
      v100 = &v109[8 * *((unsigned __int8 *)shooter_unit + 3) + 320];
      *(_DWORD *)((char *)&a16 + 2) = 1;
      v28 = 6;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v100;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v100 + 1);
    }
  }
  else if ( shooterUnitType >= 0xAu )
  {
    if ( shooterUnitType <= 0xAu )
    {
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      v26 = *((unsigned __int8 *)shooter_unit + 3);
      v98 = &v109[8 * v26 + 128];
      v28 = 4;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v98;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v98 + 1);
      sprite_frame_base = 5 * v26;
    }
    else if ( shooterUnitType == 12 )
    {
      v26 = 0;
      v25 = 2;
      sprite_frame_base = 0;
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 2;
      v28 = 1;
    }
  }
  else if ( shooterUnitType == 9 )
  {
    v28 = 6;
    v26 = *((unsigned __int8 *)shooter_unit + 3);
    *(_DWORD *)((char *)&a7 + 10) = 6;
    v30 = &v109[8 * v26 + 64];
    sprite_frame_base = 5 * v26;
    *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v30;
    *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v30 + 1);
    *(_DWORD *)((char *)&a16 + 2) = 5;
  }
  last_tick = Time_Now(v28, v26);
  if ( v31 >= g_UnitAnimFrameIndex )
  {
    shooter_record_offset = 31 * shooter_index;
    do
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v25);
      v25 = last_tick;
      now = Time_Now(v33, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(shooter_record_offset + g_MapData + 852)]);
      if ( now - last_tick >= v36 )
      {
        soundUnitType = *(__int16 *)(shooter_record_offset + g_MapData + 852);
        soundFrameIndex = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * soundUnitType];
        if ( soundFrameIndex == g_UnitAnimFrameIndex )
          Audio_PlayUnitRangedAttackSound(soundUnitType);
        last_tick = Time_Now(v35, soundFrameIndex);
        UnitBattle_RedrawTile(*(unsigned __int16 *)(shooter_record_offset + g_MapData + 856), *(unsigned __int16 *)(shooter_record_offset + g_MapData + 858));
        ++g_UnitAnimFrameIndex;
      }
    }
    while ( v35 >= g_UnitAnimFrameIndex );
  }
  if ( sprite_frame_base != -1 )
  {
    projHalfHeight = (unsigned __int16)DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base) / 2;
    SpriteWidth = DLX_GetSpriteWidth(projectile_sprite_set, v40);
    spriteVerticalOffset = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *shooter_unit];
    source_px_x = (((unsigned __int16)shooter_unit[2] - *(_DWORD *)(g_MapData + 808)) << 6)
         + 32
         + *(_DWORD *)((char *)&a7 + 2)
         - spriteVerticalOffset;
    proj_px_y = *(_DWORD *)((char *)&a7 + 6) + (((unsigned __int16)shooter_unit[3] - *(_DWORD *)(g_MapData + 812)) << 6) + 16 - spriteVerticalOffset;
    source_px_y = proj_px_y;
    target_px_x = ((target_row - *(_DWORD *)(g_MapData + 808)) << 6) + 64 - projHalfHeight;
    target_px_y = ((target_col - *(_DWORD *)(g_MapData + 812)) << 6) + 48 - SpriteWidth / 2;
    proj_px_x = source_px_x;
    v44 = target_px_y - proj_px_y;
    travel_steps = Math_CeilSqrt(v44 * v44 + (target_px_x - source_px_x) * (target_px_x - source_px_x)) / *(_DWORD *)((char *)&a7 + 10);
    shot_start_time = Time_Now(v45, shooter_index);
    travelDeltaX = v46;
    travelDeltaY = target_px_y - proj_px_y;
    unitRecordOffset = 31 * v47;
    while ( 1 )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v44);
      frameCount = g_UnitBattleAnimFrameCount;
      frameIndex = g_UnitAnimFrameIndex % g_UnitBattleAnimFrameCount;
      g_UnitAnimFrameIndex = frameIndex;
      if ( frameIndex )
      {
        frameNow = Time_Now(unitRecordOffset, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)]);
        if ( frameNow - last_tick >= frameIndex )
        {
          v51 = *(__int16 *)(frameCount + g_MapData + 852);
          v52 = g_UnitAnimFrameIndex;
          v53 = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * v51];
          if ( v53 == g_UnitAnimFrameIndex )
            Audio_PlayUnitRangedAttackSound(v51);
          last_tick = Time_Now(v52, v53);
          UnitBattle_RedrawTile(*(unsigned __int16 *)(unitRecordOffset + g_MapData + 856), *(unsigned __int16 *)(unitRecordOffset + g_MapData + 858));
          frameCount = g_UnitBattleAnimFrameCount;
          frameIndex = (g_UnitAnimFrameIndex + 1) % g_UnitBattleAnimFrameCount;
          g_UnitAnimFrameIndex = frameIndex;
        }
      }
      g_RenderDevice = &g_MainRenderDevice;
      if ( *shooter_unit == UNIT_TYPE_CATAPULT )
      {
        arcPhase = 8 * (Time_Now(frameCount, frameIndex) - shot_start_time) / (unsigned int)travel_steps;
        arcOffset = arcPhase - 4;
        if ( (int)(arcPhase - 4) <= 0 )
          arcOffset = 4 - arcPhase;
        projectile_frame = 4 - arcOffset;
      }
      else
      {
        projectile_frame = (Time_Now(frameCount, frameIndex) - shot_start_time) / 0xAu % *(_DWORD *)((char *)&a16 + 2);
      }
      prevProjX = proj_px_x;
      Render_SaveBackbuffer((int)&g_MainRenderDevice);
      v56 = proj_px_y;
      v108 = proj_px_y + DLX_GetSpriteWidth(projectile_sprite_set, v57);
      SpriteHeight = DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base);
      v59 = proj_px_x;
      if ( proj_px_y >= proj_px_x )
        v59 = proj_px_y;
      RenderState_PumpIfRectInViewBounds(g_RenderState, proj_px_x, v59 + SpriteHeight, proj_px_y, v108);
      v60 = proj_px_y + (unsigned __int16)DLX_GetSpriteWidth(projectile_sprite_set, sprite_frame_base) + 1;
      if ( v60 > 464 )
        LOWORD(v60) = 464;
      if ( proj_px_y < 16 )
        LOWORD(proj_px_y) = 16;
      v107 = v60;
      v61 = DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base);
      Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, v62, (unsigned __int16)proj_px_x, proj_px_x + v61 + 1, v107, proj_px_x, proj_px_y);
      v65 = Time_Now(v64, v63);
      v66 = Time_Now(shot_start_time, (v65 - shot_start_time) * travelDeltaX / travel_steps + source_px_x);
      proj_px_x = v67;
      v25 = v67;
      proj_px_y = (v66 - v68) * travelDeltaY / travel_steps + source_px_y;
      v69 = target_px_x - v67;
      if ( target_px_x - v67 <= 0 )
      {
        if ( target_px_x != v67 )
          v69 = -1;
      }
      else
      {
        v69 = 1;
      }
      v70 = v69;
      v71 = target_px_x - prevProjX;
      if ( target_px_x - prevProjX <= 0 )
      {
        if ( target_px_x != prevProjX )
          v71 = -1;
      }
      else
      {
        v71 = 1;
      }
      if ( v70 != v71 )
        break;
      v101 = target_px_y - proj_px_y;
      if ( target_px_y - proj_px_y <= 0 )
      {
        if ( target_px_y != proj_px_y )
          v101 = -1;
      }
      else
      {
        v101 = 1;
      }
      v102 = v101;
      v103 = target_px_y - v56;
      if ( target_px_y - v56 <= 0 )
      {
        if ( target_px_y != v56 )
          v103 = -1;
      }
      else
      {
        v103 = 1;
      }
      if ( v102 != v103 )
        break;
      SpriteForChar = DLX_GetSpriteForChar(projectile_sprite_set, projectile_frame + sprite_frame_base);
      LOBYTE(v44) = proj_px_x;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        proj_px_y,
        SpriteForChar,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      Render_Present((int)g_RenderState);
    }
  }
  g_UnitAnimFrameIndex %= g_UnitBattleAnimFrameCount;
  UnitBattle_RedrawTile(*(unsigned __int16 *)(g_MapData + 31 * shooter_index + 856), *(unsigned __int16 *)(g_MapData + 31 * shooter_index + 858));
  v72 = *shooter_unit;
  isProjectileUnit = v72 == UNIT_TYPE_CATAPULT
     || v72 == UNIT_TYPE_CANNON
     || v72 == UNIT_TYPE_DRAGON
     || v72 == UNIT_TYPE_WINGER
     || v72 == UNIT_TYPE_WIZARD;
  v74 = isProjectileUnit;
  if ( isProjectileUnit )
  {
    v75 = *shooter_unit;
    if ( v75 == UNIT_TYPE_CATAPULT || v75 == UNIT_TYPE_CANNON )
    {
      battleProjectileSpriteSet = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( battleProjectileSpriteSet )
LABEL_55:
        battleProjectileSpriteSet = DLXSpriteSet_Load(battleProjectileSpriteSet, v25);
    }
    else
    {
      if ( v75 != 24 )
      {
LABEL_57:
        v77 = *shooter_unit;
        if ( v77 == UNIT_TYPE_DRAGON || v77 == UNIT_TYPE_WINGER )
        {
          v78 = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
          if ( v78 )
            v78 = DLXSpriteSet_Load(v78, v25);
          g_UnitBattleProjectileSpriteSet = (int)v78;
        }
        g_UnitBattleShotProjectileTileX = target_row;
        g_UnitBattleShotProjectileTileY = target_col;
        g_BattleShotAnimFrameIndex = 0;
        Audio_PlayUnitShotSound(*(__int16 *)(g_MapData + 31 * shooter_index + 852));
        goto LABEL_62;
      }
      battleProjectileSpriteSet = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( battleProjectileSpriteSet )
        goto LABEL_55;
    }
    g_UnitBattleProjectileSpriteSet = (int)battleProjectileSpriteSet;
    goto LABEL_57;
  }
LABEL_62:
  if ( target_unit )
  {
    if ( (g_UnitTypeFlags[22 * *(__int16 *)target_unit] & 1) != 0 )
    {
      targetFacing = target_unit[17] & 7;
      newTargetFacing = (targetFacing + Rng_RandRange(2, 5)) & 7;
      facingHighBits = target_unit[17] & 0xF8;
      target_unit[17] = facingHighBits;
      target_unit[17] = newTargetFacing & 7 | facingHighBits;
    }
    else
    {
      g_UnitBattleAnimatingUnitIndex = target_unit_index;
    }
  }
  g_UnitBattleHitAnimFrame = Rng_RandRange(3, 7);
  if ( target_unit )
    Audio_PlayUnitHitSound(*(__int16 *)target_unit);
  hitAnimTime = Time_Now(v83, v82);
  projAnimStartTime = Time_Now(v86, v85);
  while ( v87 && (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) >= g_BattleShotAnimFrameIndex || target_unit && g_UnitBattleHitAnimFrame )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    hitNow = Time_Now(v89, hitAnimTime + 5);
    if ( hitNow >= v91 && target_unit )
    {
      hitAnimFrame = g_UnitBattleHitAnimFrame;
      if ( g_UnitBattleHitAnimFrame )
        g_UnitBattleHitAnimFrame = ((_BYTE)g_UnitBattleHitAnimFrame + 1) & 7;
      UnitBattle_RedrawUnitNeighborhood(target_unit_index);
      hitAnimTime = Time_Now(v94, hitAnimFrame);
    }
    g_BattleShotAnimFrameIndex = (unsigned int)(Time_Now(v92, v91) - projAnimStartTime) >> 1;
    if ( v95 )
    {
      if ( (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) <= g_BattleShotAnimFrameIndex )
        break;
    }
    UnitBattle_RedrawTile(target_row, target_col);
  }
  g_UnitBattleShotProjectileTileY = -1;
  g_UnitBattleShotProjectileTileX = -1;
  UnitBattle_RedrawTile(target_row, target_col);
  if ( g_UnitBattleProjectileSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleProjectileSpriteSet);
  g_UnitBattleAnimatingUnitIndex = -1;
  if ( g_UnitBattleAnimatingUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleAnimatingUnitSpriteSet);
  g_UnitBattleAnimatingUnitSpriteSet = 0;
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  if ( v105 )
    nfree_(v105);
  result = RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  g_ActiveUnitMoveTileIndex = -1;
  g_UnitBattleAnimFrameCount = 8;
  return result;
}
// 42897D: variable 'v17' is possibly undefined
// 4289EB: variable 'v20' is possibly undefined
// 428A2A: variable 'v22' is possibly undefined
// 428A3B: variable 'v23' is possibly undefined
// 428A61: variable 'v27' is possibly undefined
// 428B04: variable 'v28' is possibly undefined
// 428B04: variable 'v26' is possibly undefined
// 428B14: variable 'v31' is possibly undefined
// 428B50: variable 'v33' is possibly undefined
// 428B59: variable 'v36' is possibly undefined
// 428B86: variable 'v35' is possibly undefined
// 428B86: variable 'v38' is possibly undefined
// 428BF0: variable 'v40' is possibly undefined
// 428CBF: variable 'v45' is possibly undefined
// 428CCC: variable 'v46' is possibly undefined
// 428CD4: variable 'v47' is possibly undefined
// 428D30: variable 'v49' is possibly undefined
// 428D3B: variable 'v48' is possibly undefined
// 428D62: variable 'v52' is possibly undefined
// 428D62: variable 'v53' is possibly undefined
// 428E11: variable 'v57' is possibly undefined
// 428ECD: variable 'v62' is possibly undefined
// 428ED2: variable 'v64' is possibly undefined
// 428ED2: variable 'v63' is possibly undefined
// 428EF6: variable 'v67' is possibly undefined
// 428EF9: variable 'v68' is possibly undefined
// 428FE3: variable 'v74' is possibly undefined
// 429098: variable 'v83' is possibly undefined
// 429098: variable 'v82' is possibly undefined
// 42909F: variable 'v86' is possibly undefined
// 42909F: variable 'v85' is possibly undefined
// 4290AA: variable 'v87' is possibly undefined
// 4290D5: variable 'v89' is possibly undefined
// 4290DC: variable 'v91' is possibly undefined
// 429108: variable 'v94' is possibly undefined
// 42910F: variable 'v92' is possibly undefined
// 42911F: variable 'v95' is possibly undefined
// 429561: variable 'v105' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 514E44: using guessed type int dword_514E44;
// 514E54: using guessed type int dword_514E54;
// 514E58: using guessed type int dword_514E58;
// 519808: using guessed type int dword_519808;
// 5202E0: using guessed type int dword_5202E0;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 532048: using guessed type int g_MapData;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 5320FC: using guessed type int dword_5320FC;
// 532100: using guessed type int dword_532100;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004295D0) --------------------------------------------------------
int  UnitBattle_CalcShotTargetHealthAfterHit(int shooter_index, int target_index)
{
  int shooter_record; // ebx
  __int16 *target_unit; // esi
  signed int crowd_scale; // eax
  int base_damage; // ecx
  int v7; // edx
  int defense_scaled; // eax
  int damage_tier; // eax
  int damage; // ecx
  int result; // eax

  shooter_record = g_MapData + 852 + 31 * shooter_index;
  target_unit = (__int16 *)(31 * target_index + g_MapData + 852);
  Unit_CalcEffectivenessC((__int16 *)shooter_record);
  Math_CeilSqrt(
    (*(unsigned __int16 *)(shooter_record + 4) - (unsigned __int16)target_unit[2])
  * (*(unsigned __int16 *)(shooter_record + 4) - (unsigned __int16)target_unit[2])
  + (*(unsigned __int16 *)(shooter_record + 6) - (unsigned __int16)target_unit[3])
  * (*(unsigned __int16 *)(shooter_record + 6) - (unsigned __int16)target_unit[3]));
  crowd_scale = UnitBattle_GetTargetCrowdingScale((int)target_unit);
  defense_scaled = v7 / crowd_scale * (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *target_unit];
  damage_tier = (defense_scaled - (__CFSHL__(defense_scaled >> 31, 8) + (defense_scaled >> 31 << 8))) >> 8;
  if ( damage_tier < 1 )
    goto LABEL_2;
  if ( damage_tier >= 2 )
  {
    base_damage *= 3;
LABEL_2:
    damage = 2 * base_damage;
    goto LABEL_3;
  }
  damage = 4 * base_damage;
LABEL_3:
  result = *(char *)(g_MapData + 31 * target_index + 861) - damage;
  if ( result < 0 )
    return 0;
  return result;
}
// 4296BD: variable 'v7' is possibly undefined
// 4296E6: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00429740) --------------------------------------------------------
int  UnitBattle_Shot(int shooter_index, int target_index)
{
  char *shooter_unit; // edi
  char *target_unit; // esi
  int volleys_used; // eax
  int v6; // ecx
  unsigned __int16 target_row; // dx
  unsigned __int16 target_col; // ax

  Debug_Log(shooter_index, target_index, 0, (int)aUnitbattle_sho, shooter_index, target_index);
  shooter_unit = (char *)(g_MapData + 852 + 31 * shooter_index);
  target_unit = (char *)(g_MapData + 852 + 31 * target_index);
  if ( !UnitBattle_IsUnitWithinRange(shooter_index, target_index) )
    return 0;
  volleys_used = UNIT_SLOT_VOLLEYS_USED(shooter_unit);
  if ( volleys_used >= UNIT_SLOT_STATUS_LEVEL(shooter_unit) + 1 )
    return 0;
  if ( (unsigned __int8)shooter_unit[8] < 5u )
    return 0;
  shooter_unit[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(shooter_unit, volleys_used + 1);
  g_SelectedUnitIndex = shooter_index;
  UnitBattle_DrawSelectedUnitPanel(0, 1, target_index, 0);
  UnitBattle_RedrawVisibleGrid();
  target_unit[9] = UnitBattle_CalcShotTargetHealthAfterHit(shooter_index, target_index);
  UnitBattle_PlayShotAnimation(
    shooter_index,
    target_index,
    *(unsigned __int16 *)(target_unit + 6),
    *(unsigned __int16 *)(target_unit + 4),
    (signed __int8)target_unit[9] <= 0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0);
  if ( (signed __int8)target_unit[9] <= 0 )
  {
    target_row = *(unsigned __int16 *)(target_unit + 4);
    target_col = *(unsigned __int16 *)(target_unit + 6);
    *(_BYTE *)(40 * target_row + g_MapData + 2 * target_col + 2334) = UnitBattle_GetCorpseSpriteIndex((__int16 *)target_unit);
    UnitBattle_PlayDeathAnimation(target_index, 0, 0, 0);
    *(_WORD *)target_unit = -1;
    *(_WORD *)(40 * target_row + g_MapData + 2 * target_col + 1534) = -1;
  }
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(shooter_unit + 2) + gameData + 140073) = 1;
  UnitBattle_RedrawVisibleGrid();
  return UnitBattle_DrawSelectedUnitPanel(0, 1, target_index, 0), 1;
}

//----- (004298E0) --------------------------------------------------------
int  UnitBattle_AttackWall(int unitSlot, DWORD wallRow, int a3, int wallCol)
{
  int result; // eax
  int unitRecord; // esi
  int v8; // eax
  int v9; // eax
  unsigned __int16 unitCol; // dx
  unsigned __int16 unitRow; // ax
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  DWORD wallTileBase; // [esp+4h] [ebp-1Ch]
  int gateSpriteBefore; // [esp+8h] [ebp-18h]
  int wall_hp_before;
  int wall_hp_after;
  int unit_ap_before;
  int wall_kind;
  int wall_factor;
  int effective_wall_attack;
  int wall_damage;

  Debug_Log(a3, wallCol, wallRow, (int)aUnitbattle_a_0);
  if ( !g_UnitTypeBaseMeleeAttack_51257E[88 * *(__int16 *)(g_MapData + 31 * unitSlot + 852)] || !*(_BYTE *)(wallCol + g_MapData + 20 * wallRow + 3134) )
    return 0;
  g_SelectedUnitIndex = unitSlot;
  unitRecord = g_MapData + 852 + 31 * unitSlot;
  UnitBattle_RefreshSelectedUnitUI();
  v8 = *(unsigned __int16 *)(unitRecord + 4) - wallRow;
  if ( v8 <= 0 )
    v8 = wallRow - *(unsigned __int16 *)(unitRecord + 4);
  if ( v8 > 1 )
    goto LABEL_18;
  v9 = *(unsigned __int16 *)(unitRecord + 6) - wallCol;
  if ( v9 <= 0 )
    v9 = wallCol - *(unsigned __int16 *)(unitRecord + 6);
  if ( v9 )
  {
LABEL_18:
    result = (int)UnitBattle_MoveTrackNearWall(unitSlot, wallRow, wallCol, wallRow);
    if ( !result )
      return result;
    *(_DWORD *)(unitRecord + 23) = result;
    UnitBattle_Move(unitSlot, 0, 0, 0);
    v17 = *(_DWORD *)(unitRecord + 23);
    if ( v17 )
    {
      nfree_(v17);
      *(_DWORD *)(unitRecord + 23) = 0;
      return 0;
    }
    v18 = *(unsigned __int16 *)(unitRecord + 4) - wallRow;
    if ( v18 <= 0 )
      v18 = wallRow - *(unsigned __int16 *)(unitRecord + 4);
    if ( v18 > 1 )
      return 0;
    if ( *(unsigned __int16 *)(unitRecord + 6) - wallCol > 0 )
      return 0;
    if ( wallCol != *(unsigned __int16 *)(unitRecord + 6) )
      return 0;
  }
  unit_ap_before = *(unsigned __int8 *)(unitRecord + 8);
  if ( unit_ap_before < 5u )
    return 0;
  *(_BYTE *)(unitRecord + 8) -= 5;
  unitCol = *(_WORD *)(unitRecord + 6);
  unitRow = *(_WORD *)(unitRecord + 4);
  *(_BYTE *)(unitRecord + 22) &= ~1u;
  if ( !UnitBattle_IsTileInViewport(unitRow, unitCol) || !UnitBattle_IsTileInViewport(wallRow, wallCol) )
  {
    UnitBattle_CenterViewOnUnit(unitSlot);
    UnitBattle_RedrawVisibleGrid();
  }
  HIWORD(v12) = 0;
  *(_BYTE *)(unitRecord + 3) = Facing_DirectionFromDelta8(wallRow - *(unsigned __int16 *)(unitRecord + 4), wallCol - *(unsigned __int16 *)(unitRecord + 6));
  UnitBattle_PlayAttackAnimation(unitSlot, -1, 0, 0, (unsigned __int16 *)wallRow);
  UnitBattle_RedrawTile(wallRow, wallCol);
  gateSpriteBefore = g_BattleWallGateLastSpriteChar;
  wallTileBase = wallCol + g_MapData + 20 * wallRow;
  wall_hp_before = *(unsigned __int8 *)(wallTileBase + 3134);
  wall_kind = *(_DWORD *)(g_MapData + 820);
  wall_factor = (unsigned __int16)g_WallKindDefenseFactor[2 * wall_kind];
  effective_wall_attack = Unit_CalcEffectivenessD((char *)unitRecord, 0);
  wall_damage = wall_factor * effective_wall_attack / 256;
  *(_BYTE *)(wallTileBase + 3134) -= wall_damage;
  wall_hp_after = *(unsigned __int8 *)(wallTileBase + 3134);
  v15 = wallTileBase;
  if ( *(char *)(v15 + 3134) <= 0 )
  {
    *(_BYTE *)(v15 + 3134) = 0;
    if ( wallCol == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
    wall_hp_after = *(unsigned __int8 *)(v15 + 3134);
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[battle] wall_attack unit=%d type=%d tile=%lu,%d ap_before=%d ap_after=%d wall_before=%d wall_after=%d wall_kind=%d wall_factor=%d effective_wall_attack=%d wall_damage=%d gate_column=%d gate_state=%d battle_result=%d\n",
      unitSlot,
      *(__int16 *)unitRecord,
      (unsigned long)wallRow,
      wallCol,
      unit_ap_before,
      *(unsigned __int8 *)(unitRecord + 8),
      wall_hp_before,
      wall_hp_after,
      wall_kind,
      wall_factor,
      effective_wall_attack,
      wall_damage,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 832),
      g_BattleWallGateLastSpriteChar);
  UnitBattle_RedrawTile(wallRow, wallCol);
  if ( gateSpriteBefore != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName(aBattleMurek, 64);
  UnitBattle_RedrawTile(wallRow + 1, wallCol);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(unitRecord + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, v12, wallCol);
  return 1;
}
// 429B53: conditional instruction was optimized away because eax.4>=1
// 429A85: variable 'v14' is possibly undefined
// 429B24: variable 'v16' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513A78: using guessed type __int16 word_513A78[];
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 532104: using guessed type int dword_532104;

//----- (00429BD0) --------------------------------------------------------
int  UnitBattle_ShotWall(int unitSlot, int targetRow)
{
  char *unitRecord; // esi
  int targetCol; // ebx
  int volleysUsed; // eax
  int effectiveDamage; // eax
  int rowDist; // edx
  int colDist; // eax
  int distance; // eax
  int gateSpriteBefore; // ecx
  int wallRowBase; // eax
  int v12; // edx
  int wallHpAfter; // eax
  int v14; // eax

  targetCol = g_BattleTargetTileCol;
  Debug_Log(unitSlot, targetRow, targetCol, (int)aUnitbattle_s_0, unitSlot, targetRow, targetCol);
  unitRecord = (char *)(g_MapData + 852 + 31 * unitSlot);
  if ( !UnitBattle_IsTileWithinRange(unitSlot, targetRow, targetCol) )
    return 0;
  volleysUsed = UNIT_SLOT_VOLLEYS_USED(unitRecord);
  if ( volleysUsed >= UNIT_SLOT_STATUS_LEVEL(unitRecord) + 1 )
    return 0;
  if ( (unsigned __int8)unitRecord[8] < 5u )
    return 0;
  unitRecord[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(unitRecord, volleysUsed + 1);
  g_SelectedUnitIndex = unitSlot;
  UnitBattle_PlayShotAnimation(unitSlot, -1, targetCol, targetRow, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  UnitBattle_RedrawTile(targetRow, targetCol);
  gateSpriteBefore = g_BattleWallGateLastSpriteChar;
  effectiveDamage = Unit_CalcEffectivenessC((__int16 *)unitRecord);
  rowDist = (unsigned __int16)*(unsigned __int16 *)(unitRecord + 4) - targetRow;
  if ( rowDist < 0 )
    rowDist = targetRow - *(unsigned __int16 *)(unitRecord + 4);
  colDist = *(unsigned __int16 *)(unitRecord + 6) - targetCol;
  if ( colDist < 0 )
    colDist = targetCol - *(unsigned __int16 *)(unitRecord + 6);
  distance = Math_CeilSqrt(rowDist * rowDist + colDist * colDist);
  if ( *(__int16 *)unitRecord == UNIT_TYPE_CANNON && distance > 4 )
    effectiveDamage = 9 * effectiveDamage / 10;
  if ( *(__int16 *)unitRecord == UNIT_TYPE_CATAPULT && distance > 3 )
    effectiveDamage = 9 * effectiveDamage / 10;
  wallRowBase = g_MapData + 40 * targetRow;
  LOWORD(v12) = g_WallKindDefenseFactor[2 * *(_DWORD *)(g_MapData + 820)];
  wallHpAfter = *(signed __int8 *)(wallRowBase + targetCol + 3134) - ((effectiveDamage * (unsigned __int16)v12) >> 8);
  *(_BYTE *)(wallRowBase + targetCol + 3134) = wallHpAfter;
  if ( wallHpAfter <= 0 )
  {
    *(_BYTE *)(wallRowBase + targetCol + 3134) = 0;
    if ( targetCol == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
  }
  UnitBattle_RedrawTile(targetRow, targetCol);
  if ( gateSpriteBefore != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName((int)aBattleMurek_0, 64);
  UnitBattle_RedrawTile(targetRow + 1, targetCol);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(unitRecord + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, targetRow, targetCol);
  UnitBattle_RedrawUnitFootprint(unitSlot);
  return 1;
}

//----- (00429E30) --------------------------------------------------------
signed int  UnitBattle_Defence(int unitSlot, char a2, DWORD a3)
{
  int recordOffset; // edx

  Debug_Log(unitSlot, a2, a3, (int)aUnitbattle_def);
  recordOffset = 31 * unitSlot;
  if ( *(unsigned __int8 *)(g_MapData + recordOffset + 860) < 5u )
    return 0;
  *(_BYTE *)(g_MapData + recordOffset + 860) = 0;
  *(_BYTE *)(recordOffset + g_MapData + 874) |= 1u;
  return 1;
}
// 532048: using guessed type int g_MapData;

//----- (00429E90) --------------------------------------------------------
int  BuildCursor_HandleCancelButtonPress(int widget, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  g_BuildPlacementLoopDone = 1;
  return result;
}
// 531CD0: using guessed type int dword_531CD0;

//----- (00429EB0) --------------------------------------------------------
void BuildCursor_RequestExit()
{
  g_BuildPlacementLoopDone = 1;
}
// 531CD0: using guessed type int dword_531CD0;

//----- (00429EC0) --------------------------------------------------------
int  BuildCursor_DrawPlacementOverlay(__int64 result)
{
  __int64 tilePos64; // kr00_8
  int screenX; // edi
  int screenY; // esi
  int v4; // ebp
  int v5; // ebp
  int SpriteForChar; // eax
  unsigned __int16 overlayColor; // [esp+4h] [ebp-2Ch]

  tilePos64 = result;
  screenX = (((_DWORD)result - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 32;
  screenY = ((HIDWORD(result) - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 16;
  if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) == 1 )
    overlayColor = 215;
  else
    overlayColor = 76;
  if ( !g_BuildCursorBuildingType || g_BuildCursorBuildingType == 3 )
  {
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY);
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) )
      {
        if ( BuildCursor_IsPlacementValid(tilePos64, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex)
          && tilePos64 != __PAIR64__(
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)) )
        {
          LODWORD(result) = (*(int (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 24))(
                              (unsigned __int16)(screenX + 63),
                              (unsigned __int16)screenX,
                              (unsigned __int16)(screenY + 63),
                              (unsigned __int8)overlayColor);
          return result;
        }
        goto LABEL_26;
      }
    }
  }
  else
  {
    if ( result == g_BuildPlacementTileXY )
    {
      if ( BuildCursor_IsPlacementValid(result, SHIDWORD(result), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        screenX = (unsigned __int16)screenX;
        (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          (unsigned __int16)(screenX + 63),
          (unsigned __int16)screenX,
          (unsigned __int16)screenY,
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            screenX,
                            screenX,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY), (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(result), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v4 = (unsigned __int16)(screenX + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v4,
          (unsigned __int16)screenX,
          (unsigned __int16)screenY,
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v4,
                            v4,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY) + 1, (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v5 = (unsigned __int16)(screenX + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v5,
          (unsigned __int16)screenX,
          (unsigned __int16)(screenY + 63),
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v5,
                            v5,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY) + 1;
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) + 1 )
      {
        if ( BuildCursor_IsPlacementValid(tilePos64, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
        {
          screenX = (unsigned __int16)screenX;
          (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
            (unsigned __int16)(screenX + 63),
            (unsigned __int16)screenX,
            (unsigned __int16)(screenY + 63),
            overlayColor);
          LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                              screenX,
                              screenX,
                              (unsigned __int16)(screenY + 63),
                              overlayColor);
          return result;
        }
LABEL_26:
        SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
                            screenY,
                            SpriteForChar,
                            -1,
                            -1,
                            -1,
                            -1,
                            1,
                            0,
                            0);
      }
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202BC: using guessed type int dword_5202BC;
// 5202E4: using guessed type int gameData;
// 531CD4: using guessed type int dword_531CD4;
// 531CD8: using guessed type __int64 qword_531CD8;

//----- (0042A340) --------------------------------------------------------
int  BuildBuilding(int buildingType, int a2, char a3, double a4)
{
  DWORD widgetSlotOffset; // eax
  char coordShift; // cl
  int cursorPixelX; // edx
  int v8; // ebx
  unsigned int v9; // edx
  int cursorTileCol; // esi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  DWORD widgetSlotOffsetEnd; // eax
  int v18; // ecx
  int v20; // ecx
  int v21; // ecx
  int completionStrings[9]; // [esp+0h] [ebp-24h] BYREF

  Debug_Log(a2, a3, buildingType, (int)aBuildbuildingD, buildingType);
  g_BuildCursorBuildingType = buildingType;
  widgetSlotOffset = 53 * (buildingType + 2);
  g_BuildPlacementLoopDone = 0;
  coordShift = g_CursorCoordShift;
  cursorPixelX = g_MouseCursorRawX >> g_CursorCoordShift;
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + widgetSlotOffset) = 2;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + widgetSlotOffset) = BuildCursor_HandleCancelButtonPress;
  v8 = gameData;
  g_WorldMapTileOverlayDrawHook = (int (__fastcall *)(_DWORD, _DWORD))BuildCursor_DrawPlacementOverlay;
  LODWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)
                        + ((cursorPixelX - 32 - (__CFSHL__((cursorPixelX - 32) >> 31, 6) + ((cursorPixelX - 32) >> 31 << 6))) >> 6);
  HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                        + (((g_MouseCursorRawY >> coordShift)
                          - 16
                          - (__CFSHL__(((g_MouseCursorRawY >> coordShift) - 16) >> 31, 6)
                           + (((g_MouseCursorRawY >> coordShift) - 16) >> 31 << 6))) >> 6);
  WorldMap_RedrawViewport(1);
  while ( !g_BuildPlacementLoopDone )
  {
    DD_Pump((int)&g_RenderState, v8, (char)BuildCursor_DrawPlacementOverlay);
    WorldMap_RedrawFrame(v8);
    if ( !UIWidgetTable_PollHoverAndActions((int)&g_BuildBuildingActionWidgetTable, buildingType) && UI_TrySelectFriendlyStackUnderCursor() )
    {
      Render_Begin((int)&g_RenderState, 0, (char)BuildCursor_DrawPlacementOverlay);
      break;
    }
    WorldMap_HandleScrollKeysAndIdle(v9);
    cursorTileCol = (((g_MouseCursorRawX >> g_CursorCoordShift)
          - 32
          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
           + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
        + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    v8 = g_BuildPlacementTileXY;
    if ( __PAIR64__(
           *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
         + (((g_MouseCursorRawY >> g_CursorCoordShift)
           - 16
           - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
            + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6),
           cursorTileCol) != g_BuildPlacementTileXY )
    {
      v8 = HIDWORD(g_BuildPlacementTileXY);
      HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                            + (((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6);
      v11 = g_BuildPlacementTileXY;
      LODWORD(g_BuildPlacementTileXY) = cursorTileCol;
      WorldMap_RedrawTileIfVisible(v11, v8);
      if ( buildingType == 2 || buildingType == 1 )
      {
        v13 = v12 + 1;
        v14 = v8++;
        WorldMap_RedrawTileIfVisible(v12 + 1, v14);
        WorldMap_RedrawTileIfVisible(v15, v8);
        WorldMap_RedrawTileIfVisible(v13, v8);
      }
      WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY));
      if ( buildingType == 2 || buildingType == 1 )
      {
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, SHIDWORD(g_BuildPlacementTileXY));
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, HIDWORD(g_BuildPlacementTileXY) + 1);
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, HIDWORD(g_BuildPlacementTileXY) + 1);
      }
    }
    if ( DD_IsFlipping((int)&g_RenderState) )
    {
      if ( buildingType == 3 )
      {
        v8 = g_SelectedUnitIndex;
        if ( Trap_New(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY), v16, g_SelectedUnitIndex, a4) == 1 )
        {
          Win_PlayModeChangeFrameTransition(aZakl_pul, 1, v20, v8, 3u);
          completionStrings[0] = (int)g_BuildBuildingCompletionMessageStrings[0];
          completionStrings[1] = (int)g_BuildBuildingCompletionMessageStrings[1];
          completionStrings[2] = (int)g_BuildBuildingCompletionMessageStrings[2];
          UI_ShowInfoWindow(completionStrings[(unsigned __int8)g_LanguageIndex], 0, v21, 3u, (int)&completionStrings[3], (int)&g_BuildBuildingCompletionMessageStrings[3]);
          Render_Begin((int)&g_RenderState, 0, (char)&completionStrings[3]);
          g_BuildPlacementLoopDone = 1;
          break;
        }
      }
      else
      {
        v8 = g_SelectedUnitIndex;
        if ( ((BOOL (__cdecl *)(__int64, int, int, double, char *, int))Building_New)(
               g_BuildPlacementTileXY,
               buildingType,
               g_SelectedUnitIndex,
               a4,
               aZam,
               0) == 1 )
        {
          Audio_PlaySoundEffectByName((int)aStruktur_2, 64);
          Render_Begin((int)&g_RenderState, 0, (char)BuildCursor_DrawPlacementOverlay);
          g_BuildPlacementLoopDone = 1;
          break;
        }
      }
    }
  }
  widgetSlotOffsetEnd = 53 * (buildingType + 2);
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + widgetSlotOffsetEnd) = 1;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + widgetSlotOffsetEnd) = (int (*)())BuildCursor_RequestExit;
  UIWidget_RefreshActionButtonState((int)&g_BuildBuildingActionWidgetTable + widgetSlotOffsetEnd, 1);
  g_WorldMapTileOverlayDrawHook = 0;
  return WorldMap_RedrawViewport(v18);
}
// 42A425: variable 'v9' is possibly undefined
// 42A4AD: variable 'v12' is possibly undefined
// 42A4BE: variable 'v15' is possibly undefined
// 42A597: variable 'v18' is possibly undefined
// 42A629: variable 'v16' is possibly undefined
// 42A645: variable 'v20' is possibly undefined
// 42A659: variable 'v21' is possibly undefined
// 429E90: using guessed type int sub_429E90();
// 511130: using guessed type char byte_511130;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5146C8: using guessed type int dword_5146C8;
// 5146E0: using guessed type int (*off_5146E0)();
// 514834: using guessed type char *off_514834[3];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
// 531CD0: using guessed type int dword_531CD0;
// 531CD4: using guessed type int dword_531CD4;
// 531CD8: using guessed type __int64 qword_531CD8;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0042A760) --------------------------------------------------------
int  UI_DrawNoticeBoxSmall(DWORD renderState, int a2)
{
  int spriteIndex; // edx
  int SpriteForChar; // eax
  int tax_rate; // ecx

  g_RenderDevice = &g_MainRenderDevice;
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 198, 208, 0x104u, 0xDAu, 0xD0u, 0xC6u);
  Render_ReleaseSurface(5, renderState);
  tax_rate = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  UI_DrawTextFmt(208, 208, 260, 198, 3, aD_D, tax_rate / 10, tax_rate % 10);
  if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4 <= 0
    || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
  {
    if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4
      || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
      spriteIndex = 4;
    else
      spriteIndex = 3;
  }
  else
  {
    spriteIndex = 5;
  }
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingEconomyDialogSpriteSet, spriteIndex);
  return Compat_RenderDeviceDrawMenuSprite(383, 19, SpriteForChar, 0);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CE4: using guessed type int g_BuildingEconomyDialogSpriteSet;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;

//----- (0042A890) --------------------------------------------------------
int  UI_DrawConfirmTop(DWORD renderState, int a2)
{
  void *savedRenderDevice; // esi
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderState);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 360, 548, 0x259u, 0x17Cu, 0x224u, 0x168u);
  result = UI_DrawTextFmt(548, 548, 601, 360, 3, aD_8, g_BuildingEconomyDialogPendingPeasantTransfer);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;

//----- (0042A910) --------------------------------------------------------
int  UI_DrawConfirmBottom(DWORD renderState, int a2)
{
  void *savedRenderDevice; // esi
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderState);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x124u, 0x224u, 0x110u);
  result = UI_DrawTextFmt(548, 548, 601, 272, 3, aD_9, g_BuildingEconomyDialogPendingGoldTransfer);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;

static void BuildingEconomyDialog_InitWidget(
        unsigned char *record,
        int left,
        int top,
        int normal_sprite,
        int hover_sprite,
        int (*transition_callback)(unsigned __int16 *, int, DWORD),
        void *action_callback,
        const char *text_pl,
        const char *text_en,
        const char *text_de,
        unsigned char tooltip_mode,
        const char *sound)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BuildingEconomyDialogSpriteSet;
  *(_DWORD *)(record + 16) = normal_sprite;
  *(_DWORD *)(record + 20) = hover_sprite;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)transition_callback;
  *(_DWORD *)(record + 32) = (int)(uintptr_t)action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)text_pl;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)text_en;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)text_de;
  *(_BYTE *)(record + 48) = tooltip_mode;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound;
}

static void BuildingEconomyDialog_EnsureWidgets(void)
{
  static const char sound_cash[] = "kasa";
  static const char sound_small[] = "male";
  static const char sound_large[] = "duze";
  static const char text_back_pl[] = "Koniec";
  static const char text_back_en[] = "Back";
  static const char text_back_de[] = "Zuruck";
  static const char text_transfer_pl[] = "Transferuj";
  static const char text_transfer_en[] = "Transfer";
  static const char text_transfer_de[] = "Uberfuhrung";

  if ( g_BuildingEconomyDialogWidgetsInitialized )
    return;

  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    174,
    173,
    6,
    7,
    UI_DrawWidgetIconTransitionFast,
    BuildingEconomyDialog_IncreaseTaxRate,
    NULL,
    NULL,
    NULL,
    0,
    sound_cash);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    174,
    206,
    8,
    9,
    UI_DrawWidgetIconTransitionFast,
    BuildingEconomyDialog_DecreaseTaxRate,
    NULL,
    NULL,
    NULL,
    0,
    sound_cash);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    459,
    270,
    10,
    11,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferTargetList_SelectPrevious,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    459,
    323,
    12,
    13,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferTargetList_SelectNext,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    513,
    331,
    18,
    19,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferDialog_IncreasePeasantTransferAmount,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    513,
    365,
    20,
    21,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferDialog_DecreasePeasantTransferAmount,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 6,
    513,
    247,
    14,
    15,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferDialog_IncreaseGoldTransferAmount,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 7,
    513,
    281,
    16,
    17,
    UI_DrawWidgetIconTransitionFast,
    BuildingTransferDialog_DecreaseGoldTransferAmount,
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 8,
    42,
    426,
    22,
    23,
    UI_DrawWidgetIconTransitionSlow,
    BuildingEconomyDialog_SetExitSignal,
    text_back_pl,
    text_back_en,
    text_back_de,
    2,
    sound_large);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 9,
    505,
    426,
    24,
    25,
    UI_DrawWidgetIconTransitionSlow,
    BuildingEconomyDialog_CommitTransfers,
    text_transfer_pl,
    text_transfer_en,
    text_transfer_de,
    2,
    sound_large);
  *(_DWORD *)(g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_ECONOMY_DIALOG_WIDGET_COUNT) = -1;
  g_BuildingEconomyDialogWidgetsInitialized = 1;
}

//----- (0042A990) --------------------------------------------------------
int  BuildingEconomyDialog_SetExitSignal(int widget, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay((uintptr_t)widget, 1);
  g_BuildingEconomyDialogExitSignal = 1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[economy] back exit_signal=%d\n", g_BuildingEconomyDialogExitSignal);
  return result;
}
// 531CE8: using guessed type int g_BuildingEconomyDialogExitSignal;

//----- (0042A9B0) --------------------------------------------------------
int  BuildingEconomyDialog_CommitTransfers(
        int widget,
        int a2,
        DWORD renderState,
        char a4,
        double a5)
{
  int targetBuildingId; // eax
  int peasantTargetId; // esi
  int goldTargetId; // esi

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  if ( g_BuildingEconomyDialogPendingPeasantTransfer )
  {
    targetBuildingId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( targetBuildingId == -2 || *(_BYTE *)(BUILDING_RECORD_SIZE * targetBuildingId + gameData + 509678) != 1 )
    {
      peasantTargetId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
      if ( peasantTargetId == -2 )
        peasantTargetId = -1;
      a4 = -45;
      Building_Transfer(
        (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
        peasantTargetId,
        0,
        g_BuildingEconomyDialogPendingPeasantTransfer,
        a5);
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    }
  }
  if ( g_BuildingEconomyDialogPendingGoldTransfer )
  {
    goldTargetId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( goldTargetId == -2 )
      goldTargetId = -1;
    a4 = -45;
    Building_Transfer(
      (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
      goldTargetId,
      1,
      g_BuildingEconomyDialogPendingGoldTransfer,
      a5);
    g_BuildingEconomyDialogPendingGoldTransfer = 0;
  }
  UI_DrawConfirmTop(renderState, a4);
  UI_DrawConfirmBottom(renderState, a4);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 20, 200, 0x17Cu, 0x41u, 0xC8u, 0x14u);
  Render_ReleaseSurface(16, renderState);
  UI_DrawTextFmt((int)&g_MainRenderDevice, 0, 370, 20, 2, (int)aD_47);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 30, 545, 0x25Au, 0x32u, 0x221u, 0x1Eu);
  Render_ReleaseSurface(5, renderState);
  return UI_DrawTextFmt((int)&g_MainRenderDevice, 545, 602, 30, 3, (int)aD_46);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];

//----- (0042AB80) --------------------------------------------------------
int  BuildingEconomyDialog_DecreaseTaxRate(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int buildingRecord; // eax
  char taxByte; // dl
  int currentTaxRate; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  unsigned int taxDecrement; // eax
  char newTaxRate; // dl
  int buildingRecord2; // eax
  char taxHighBits; // dh
  int v20; // ecx
  char taxHighBits0; // dh

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  buildingRecord = g_BuildingEconomyDialogBuilding;
  taxByte = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436);
  if ( (taxByte & 0x3F) != 0 )
  {
    taxHighBits0 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits0;
    *(_BYTE *)(buildingRecord + 436) = ((taxByte & 0x3F) - 1) & 0x3F | taxHighBits0;
  }
  currentTaxRate = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)g_RenderState, currentTaxRate);
    v11 = Time_Now(v10, v9);
    v13 = Time_Now(v12, v11);
    taxDecrement = (v14 - v15) * (v13 - v15) / 0x15Eu;
    newTaxRate = currentTaxRate - taxDecrement;
    if ( (int)(currentTaxRate - taxDecrement) < 0 )
      newTaxRate = 0;
    buildingRecord2 = g_BuildingEconomyDialogBuilding;
    taxHighBits = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits;
    *(_BYTE *)(buildingRecord2 + 436) = newTaxRate & 0x3F | taxHighBits;
    UI_DrawNoticeBoxSmall((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v20);
}
// 42ABA6: variable 'v5' is possibly undefined
// 42ABA6: variable 'v4' is possibly undefined
// 42ABE2: variable 'v10' is possibly undefined
// 42ABE2: variable 'v9' is possibly undefined
// 42ABE9: variable 'v12' is possibly undefined
// 42ABEE: variable 'v14' is possibly undefined
// 42ABEE: variable 'v15' is possibly undefined
// 42AC46: variable 'v20' is possibly undefined
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AC80) --------------------------------------------------------
int  BuildingEconomyDialog_IncreaseTaxRate(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int buildingRecord; // eax
  char newTaxRate; // dl
  char taxHighBits; // dh
  int currentTaxRate; // ebx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int taxRateAnim; // edx
  int buildingRecord2; // eax
  int v19; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  buildingRecord = g_BuildingEconomyDialogBuilding;
  newTaxRate = ((*(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F) + 1) & 0x3F;
  taxHighBits = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
  *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits;
  *(_BYTE *)(buildingRecord + 436) = newTaxRate | taxHighBits;
  currentTaxRate = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)g_RenderState, currentTaxRate);
    v12 = Time_Now(v11, v10);
    v14 = Time_Now(v13, v12);
    taxRateAnim = currentTaxRate + (v15 - v16) * (v14 - v16) / 0x15Eu;
    if ( taxRateAnim > 40 )
      LOBYTE(taxRateAnim) = 40;
    buildingRecord2 = g_BuildingEconomyDialogBuilding;
    BYTE1(taxRateAnim) = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = BYTE1(taxRateAnim);
    *(_BYTE *)(buildingRecord2 + 436) = taxRateAnim & 0x3F | BYTE1(taxRateAnim);
    UI_DrawNoticeBoxSmall(0x15Eu, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v19);
}
// 42ACA3: variable 'v5' is possibly undefined
// 42ACA3: variable 'v4' is possibly undefined
// 42ACFA: variable 'v11' is possibly undefined
// 42ACFA: variable 'v10' is possibly undefined
// 42AD01: variable 'v13' is possibly undefined
// 42AD06: variable 'v15' is possibly undefined
// 42AD06: variable 'v16' is possibly undefined
// 42AD59: variable 'v19' is possibly undefined
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AD70) --------------------------------------------------------
int  BuildingTransferDialog_DecreasePeasantTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int peasantAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer -= 10;
  peasantAmount = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)g_RenderState, peasantAmount);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((peasantAmount - (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer < 0 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    UI_DrawConfirmTop((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v14);
}
// 42AD96: variable 'v5' is possibly undefined
// 42AD96: variable 'v4' is possibly undefined
// 42ADBE: variable 'v8' is possibly undefined
// 42ADBE: variable 'v7' is possibly undefined
// 42ADC5: variable 'v10' is possibly undefined
// 42ADCA: variable 'v12' is possibly undefined
// 42ADCA: variable 'v13' is possibly undefined
// 42AE1D: variable 'v14' is possibly undefined
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AE30) --------------------------------------------------------
int  BuildingTransferDialog_IncreasePeasantTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int peasantAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  unsigned __int16 maxPeasants; // ax
  int v15; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer += 10;
  peasantAmount = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)g_RenderState, peasantAmount);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((peasantAmount + (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer > 1000 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 1000;
    maxPeasants = *(_WORD *)(g_BuildingEconomyDialogBuilding + 430);
    HIBYTE(maxPeasants) &= 0xFu;
    if ( maxPeasants < g_BuildingEconomyDialogPendingPeasantTransfer )
      g_BuildingEconomyDialogPendingPeasantTransfer = maxPeasants;
    UI_DrawConfirmTop(0xAu, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v15);
}
// 42AE53: variable 'v5' is possibly undefined
// 42AE53: variable 'v4' is possibly undefined
// 42AE79: variable 'v8' is possibly undefined
// 42AE79: variable 'v7' is possibly undefined
// 42AE80: variable 'v10' is possibly undefined
// 42AE85: variable 'v12' is possibly undefined
// 42AE85: variable 'v13' is possibly undefined
// 42AEEE: variable 'v15' is possibly undefined
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AF10) --------------------------------------------------------
int  BuildingTransferDialog_DecreaseGoldTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int goldAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer -= 10;
  goldAmount = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)g_RenderState, goldAmount);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((goldAmount - (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer < 0 )
      g_BuildingEconomyDialogPendingGoldTransfer = 0;
    UI_DrawConfirmBottom((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v14);
}
// 42AF36: variable 'v5' is possibly undefined
// 42AF36: variable 'v4' is possibly undefined
// 42AF5E: variable 'v8' is possibly undefined
// 42AF5E: variable 'v7' is possibly undefined
// 42AF65: variable 'v10' is possibly undefined
// 42AF6A: variable 'v12' is possibly undefined
// 42AF6A: variable 'v13' is possibly undefined
// 42AFBD: variable 'v14' is possibly undefined
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AFD0) --------------------------------------------------------
int  BuildingTransferDialog_IncreaseGoldTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int goldAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  DWORD maxGold; // ebp
  int v15; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer += 10;
  goldAmount = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)g_RenderState, goldAmount);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((goldAmount + (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > 1000 )
      g_BuildingEconomyDialogPendingGoldTransfer = 1000;
    maxGold = *(_DWORD *)(g_BuildingEconomyDialogBuilding + 438);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > maxGold )
      g_BuildingEconomyDialogPendingGoldTransfer = *(_DWORD *)(g_BuildingEconomyDialogBuilding + 438);
    UI_DrawConfirmBottom(maxGold, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v15);
}
// 42AFF3: variable 'v5' is possibly undefined
// 42AFF3: variable 'v4' is possibly undefined
// 42B019: variable 'v8' is possibly undefined
// 42B019: variable 'v7' is possibly undefined
// 42B020: variable 'v10' is possibly undefined
// 42B025: variable 'v12' is possibly undefined
// 42B025: variable 'v13' is possibly undefined
// 42B086: variable 'v15' is possibly undefined
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042B0A0) --------------------------------------------------------
int  BuildingEconomyDialog_Run(int buildingRecord)
{
  int player_has_religion; // edi
  int building_index;
  char *background_path; // edx
  char *sprite_path; // edx
  char *resource_base_path; // eax
  _DWORD *dialog_sprite_set; // eax
  int SpriteForChar; // eax
  int exit_signal_snapshot; // ecx
  unsigned __int8 *palette_buffer; // [esp+0h] [ebp-418h]

  g_BuildingEconomyDialogBuilding = buildingRecord;
  building_index = (buildingRecord - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] enter building_idx=%d owner=%d\n",
      building_index,
      *(unsigned __int8 *)(buildingRecord + 2));
  Diagnostics_ResetFrameDumpOnEconomyEnter();
  player_has_religion = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(buildingRecord + 2));
  BuildingTransferTargetList_Rebuild(buildingRecord, 1);
  g_BuildingEconomyDialogPendingPeasantTransfer = 0;
  g_BuildingEconomyDialogPendingGoldTransfer = 0;
  palette_buffer = g_CastleScreenPaletteBuffer;
  memset(palette_buffer, 0, 0x400u);
  if ( player_has_religion )
    background_path = aCastle_chrDw_1;
  else
    background_path = aCastle_pogDw_1;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    background_path,
    0,
    (uintptr_t)palette_buffer);
  dialog_sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( player_has_religion )
    sprite_path = aCastle_chrDw_0;
  else
    sprite_path = aCastle_pogDw_0;
  if ( dialog_sprite_set )
    dialog_sprite_set = DLXSpriteSet_Load(dialog_sprite_set, sprite_path);
  g_BuildingEconomyDialogSpriteSet = (int)dialog_sprite_set;
  if ( player_has_religion )
    resource_base_path = aCastle_chrDw_2;
  else
    resource_base_path = aCastle_pogDw_2;
  Palette_LoadOrBuildBlendLookupTable(resource_base_path, (int)(uintptr_t)palette_buffer, (int)dialog_sprite_set, 0);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingEconomyDialogSpriteSet, (unsigned __int8)g_LanguageIndex);
  Compat_RenderDeviceDrawMenuSprite(267, 149, SpriteForChar, 0);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, 0);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, palette_buffer, 0, (char)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(5, palette_buffer, 0, (char)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(9, palette_buffer, 0, (char)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(16, palette_buffer, 0, (char)&g_MainRenderDevice, 0);
  UI_DrawTextFmt(267, 267, 343, 90, 2, aD_32, *(signed char *)(buildingRecord + 434));
  UI_DrawTextFmt(444, 444, 503, 198, 3, aD_33, *(unsigned __int16 *)(buildingRecord + 442));
  UI_DrawNoticeBoxSmall(0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 20, 200, 0x17Cu, 0x41u, 0xC8u, 0x14u);
  Render_ReleaseSurface(16, 0);
  UI_DrawTextFmt(0, 0, 370, 20, 2, aD_47, *(unsigned __int16 *)(g_BuildingEconomyDialogBuilding + 430));
  BuildingEconomyDialog_EnsureWidgets();
  UIWidgetTable_InitDrawStates(g_BuildingEconomyDialogActionWidgets);
  BuildingTransferTargetList_SetDrawOrigin(184, 279);
  BuildingTransferTargetList_Draw((int)(uintptr_t)palette_buffer, 0);
  UI_DrawConfirmTop(0, 0);
  UI_DrawConfirmBottom(0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 30, 545, 0x25Au, 0x32u, 0x221u, 0x1Eu);
  Render_ReleaseSurface(5, 0);
  UI_DrawTextFmt(545, 545, 602, 30, 3, aD_46, *(_DWORD *)(g_BuildingEconomyDialogBuilding + 438));
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, palette_buffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)(uintptr_t)palette_buffer, 0, 0);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] first_present building_idx=%d list_index=%d target=%d\n",
      building_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  g_BuildingEconomyDialogExitSignal = 0;
  exit_signal_snapshot = 0;
  do
  {
    DD_Pump((int)g_RenderState, (char)g_RenderState);
    BuildingTransferTargetList_HandleClick(0);
    UIWidgetTable_PollHoverAndActions(g_BuildingEconomyDialogActionWidgets, 0);
    UI_RunHoverTooltipZones(g_BuildingEconomyDialogTooltipZoneRect);
  }
  while ( exit_signal_snapshot == g_BuildingEconomyDialogExitSignal );
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] exit building_idx=%d list_index=%d exit_signal=%d\n",
      building_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingEconomyDialogExitSignal);
  BuildingTransferTargetList_FreeSpriteSet();
  DLXSpriteSet_ReleaseAndClear(&g_BuildingEconomyDialogSpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514840: using guessed type _DWORD dword_514840[3];
// 514A88: using guessed type __int16 word_514A88[4];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526A2C: using guessed type int dword_526A2C;
// 531CE4: using guessed type int g_BuildingEconomyDialogSpriteSet;
// 531CE8: using guessed type int g_BuildingEconomyDialogExitSignal;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042B3F0) --------------------------------------------------------
BOOL  Trap_CanPlaceAtTile(int tileX, int tileY)
{
  int v3; // ecx
  BOOL result; // eax
  signed int surfaceClass; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  result = 0;
  if ( !Trap_GetTileOwnerMask(tileX, tileY, g_CurrentPlayerIndex) )
  {
    surfaceClass = Map_GetTileSurfaceClassOrUnexplored(v3, tileY);
    if ( surfaceClass != 185
      && surfaceClass != 39
      && surfaceClass != 204
      && surfaceClass != 202
      && surfaceClass != 147
      && surfaceClass != 1
      && !MapTile_IsCastleFoundationTile(v6, tileY, 2)
      && *(unsigned __int16 *)(TILE_INDEX(v7, tileY)) == 0xFFFF
      && !MapTile_GetReligiousSiteCategory(v7, tileY)
      && !MapTile_HasHiddenTreasure(v8, tileY) )
    {
      return 1;
    }
  }
  return result;
}
// 42B410: variable 'v3' is possibly undefined
// 42B444: variable 'v6' is possibly undefined
// 42B467: variable 'v7' is possibly undefined
// 42B499: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0042B4B0) --------------------------------------------------------
signed int  Trap_New(DWORD tileX, int tileY, int a3, int stackIndex, double a5)
{
  signed int result; // eax
  int v9; // ecx
  int dxTile; // eax
  int dyTile; // eax
  int stackByteOffset; // ebx
  DWORD tileDataPtr; // ebp
  signed int squadCount; // eax
  _WORD *squadSlot; // edx
  signed int squadIndex; // ecx
  double v17; // st7
  int v18; // ecx
  int v19; // edx

  Debug_Log(a3, stackIndex, tileX, (int)aTrap_newDDD, tileX);
  result = UnitStack_HasBuilder(stackIndex);
  if ( result )
  {
    if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET) < 0 || !Trap_CanPlaceAtTile(tileX, tileY) )
      return 0;
    dxTile = tileX - *(__int16 *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( dxTile <= 0 )
      dxTile = *(__int16 *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET) - tileX;
    if ( dxTile > 1 )
      return 0;
    dyTile = tileY - *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176);
    if ( dyTile <= 0 )
      dyTile = *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) - tileY;
    if ( dyTile <= 1 )
    {
      stackByteOffset = UNIT_STACK_STRIDE * stackIndex;
      tileDataPtr = gameData + 100 * tileX;
      TILE_TRAP_OWNER_MASK(tileX, tileY) = 1 << *(_BYTE *)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178);
      UnitStack_SpendActionPointsByIndexClamped(stackIndex, 0, tileDataPtr, a5);
      while ( 1 )
      {
        squadCount = Unit_GetSquadCount(stackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( squadIndex >= squadCount )
          break;
        if ( *squadSlot == UNIT_TYPE_BUILDER )
        {
          *squadSlot = -1;
          break;
        }
      }
      Rules_SyncArmyFactStrength(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET, UNIT_STACK_STRIDE * stackIndex, gameData, stackByteOffset, tileDataPtr, a5);
      Unit_CompactSquad(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET, v18, v17);
      if ( *(__int16 *)(gameData + v19 + 147180) == -1 )
      {
        Rules_UnlinkArmyFact(v19 + gameData + UNIT_STACK_TABLE_OFFSET, v17);
        WorldMap_SyncSelectionForHumanPlayer(tileDataPtr);
      }
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 42B52E: variable 'v9' is possibly undefined
// 42B5EA: variable 'v16' is possibly undefined
// 42B5EC: variable 'v15' is possibly undefined
// 42B643: variable 'v18' is possibly undefined
// 42B643: variable 'v17' is possibly undefined
// 42B64D: variable 'v19' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0042B680) --------------------------------------------------------
int  Trap_ClearTileOwnerMask(int tileX, int tileY)
{
  int result; // eax

  result = gameData + TILE_TRAP_OWNER_MASK_ROW_STRIDE * tileX;
  TILE_TRAP_OWNER_MASK(tileX, tileY) = 0;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0042B6A0) --------------------------------------------------------
__int16 * Trap_HurtStack(__int16 *stack, char a2, DWORD a3, double a4)
{
  int unitIndex; // esi
  char *unitPtr; // ecx
  int unitRecord; // ecx
  unsigned int effectiveness; // ebx
  unsigned int damageRoll; // eax

  unitIndex = 0;
  Debug_Log((int)(stack + 3), a2, a3, (int)Trap_HurtUnit);
  do
  {
    if ( *(__int16 *)unitPtr == -1 )
      break;
    effectiveness = Unit_CalcEffectivenessB(unitPtr, 0);
    if ( effectiveness )
    {
      damageRoll = Rng_RandRange(270, 340);
      *(_BYTE *)(unitRecord + 9) -= damageRoll / effectiveness;
    }
    else
    {
      *(_BYTE *)(unitRecord + 9) = 0;
    }
    if ( *(char *)(unitRecord + 9) <= 0 )
      *(_WORD *)unitRecord = -1;
    unitPtr = (char *)(unitRecord + 31);
    ++unitIndex;
    *(unitPtr - 23) = 0;
  }
  while ( unitIndex < 10 );
  Unit_CompactSquad(stack, (int)unitPtr, a4);
  return Rules_LinkArmyFinalize(stack, a4);
}
// 42B6BA: variable 'v6' is possibly undefined
// 42B6FA: variable 'v8' is possibly undefined

//----- (0042B730) --------------------------------------------------------
int  Trap_GetTileOwnerMask(int tileX, int tileY, int playerIndex)
{
  if ( playerIndex == -1 )
    return TILE_TRAP_OWNER_MASK(tileX, tileY);
  else
    return TILE_TRAP_OWNER_MASK(tileX, tileY) & (1 << playerIndex);
}
// 5202E4: using guessed type int gameData;

//----- (0042B770) --------------------------------------------------------
signed int  Trap_TriggerAtStackTile(int stackIndex, DWORD a2, double a3)
{
  __int16 *stackRecord; // ebx
  int stackBase; // eax
  int tileDataPtr; // ebx
  int ownerIndex; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  unsigned int v15; // edx
  int visionRadius; // eax
  int scanRow; // esi
  int i; // edx
  int stackCol; // edi
  int v20; // eax
  char owner; // cl
  int v22; // eax
  int v23; // ebx
  int v24; // ecx
  int scanRowTileBase; // [esp+4h] [ebp-24h]
  signed int radius; // [esp+Ch] [ebp-1Ch]

  stackRecord = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex);
  if ( UnitStack_GetMaxOrderTier((intptr_t)stackRecord) >= 3 )
  {
    visionRadius = UnitStack_GetVisionRadius((int)stackRecord);
    scanRow = *stackRecord - visionRadius;
    radius = visionRadius;
    scanRowTileBase = 100 * scanRow;
    while ( scanRow < radius + *stackRecord )
    {
      for ( i = stackRecord[1] - radius; ; ++i )
      {
        stackCol = stackRecord[1];
        if ( i >= stackCol + radius )
          break;
        if ( scanRow >= 0
          && scanRow < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && i >= 0
          && i < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Math_CeilSqrt((i - stackCol) * (i - stackCol) + (scanRow - *stackRecord) * (scanRow - *stackRecord)) <= radius )
        {
          a2 = scanRowTileBase;
          if ( TILE_TRAP_OWNER_MASK(scanRow, i) )
          {
            owner = *((_BYTE *)stackRecord + 4);
            a2 = 1 << owner;
            if ( ((1 << owner) & TILE_TRAP_OWNER_MASK(scanRow, i)) == 0 )
            {
              TILE_TRAP_OWNER_MASK(scanRow, i) |= 1 << owner;
              WorldMap_RedrawViewport(1);
            }
          }
        }
      }
      ++scanRow;
      scanRowTileBase += 100;
    }
  }
  stackBase = gameData + UNIT_STACK_STRIDE * stackIndex;
  tileDataPtr = gameData + 100 * *(__int16 *)(stackBase + 147174) + *(__int16 *)(stackBase + 147176);
  if ( !TILE_TRAP_OWNER_MASK(*(__int16 *)(stackBase + 147174), *(__int16 *)(stackBase + 147176)) )
    return 0;
  ownerIndex = *(unsigned __int8 *)(stackBase + 147178);
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * ownerIndex + 140059) )
  {
    TILE_TRAP_OWNER_MASK(*(__int16 *)(stackBase + 147174), *(__int16 *)(stackBase + 147176)) |= 1 << ownerIndex;
    WorldMap_RedrawViewport(1);
    WorldMap_RedrawViewport(1);
    v11 = Time_Now(v10, v9) + 200;
    while ( 1 )
    {
      v13 = Time_Now(v12, v11);
      if ( v13 >= v15 )
        break;
      WorldMap_RedrawFrame(tileDataPtr);
    }
    Win_PlayModeChangeFrameTransition(aWpad_pul, 1, v14, tileDataPtr, a2);
  }
  v22 = gameData + UNIT_STACK_STRIDE * stackIndex;
  v23 = TILE_TRAP_OWNER_MASK_ROW_STRIDE * *(__int16 *)(v22 + 147174);
  TILE_TRAP_OWNER_MASK(*(__int16 *)(v22 + 147174), *(__int16 *)(v22 + 147176)) = 0;
  Rules_RetractTrapFact(*(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + 147176));
  Trap_HurtStack((__int16 *)(v24 + gameData + UNIT_STACK_TABLE_OFFSET), v23, a2, a3);
  return 1;
}
// 42B839: variable 'v10' is possibly undefined
// 42B839: variable 'v9' is possibly undefined
// 42B844: variable 'v12' is possibly undefined
// 42B844: variable 'v11' is possibly undefined
// 42B84B: variable 'v15' is possibly undefined
// 42B900: variable 'i' is possibly undefined
// 42B941: variable 'v14' is possibly undefined
// 42B9AA: variable 'v24' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0042B9D0) --------------------------------------------------------
int  Trap_ShowPitfallDiscoveryDialog(int tileX, int tileY, char spritePath, DWORD a4)
{
  int v4; // ecx
  _DWORD *spriteSetAlloc; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 spriteHeight; // ax
  int glyphIndex; // edx
  int SpriteForChar; // eax
  int confirmBtnYMin; // esi
  int cancelBtnXMin; // ebx
  int cancelBtnYMin; // ebp
  int cancelBtnYMax; // edi
  __int16 eraseHeight; // ax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int secondLineY; // ebx
  unsigned __int16 fillRectYMax; // [esp+10h] [ebp-58h]
  unsigned __int16 eraseWidth; // [esp+10h] [ebp-58h]
  unsigned __int16 eraseX; // [esp+14h] [ebp-54h]
  unsigned __int16 eraseY; // [esp+18h] [ebp-50h]
  int messageStrings[3]; // [esp+1Ch] [ebp-4Ch]
  _DWORD *dialogSpriteSet; // [esp+28h] [ebp-40h] BYREF
  _DWORD *dialogSurface; // [esp+2Ch] [ebp-3Ch]
  int dialogY; // [esp+30h] [ebp-38h]
  int confirmBtnYMax; // [esp+34h] [ebp-34h]
  int confirmBtnXMax; // [esp+38h] [ebp-30h]
  int tileX2; // [esp+3Ch] [ebp-2Ch]
  int tileY2; // [esp+40h] [ebp-28h]
  void *savedRenderDevice; // [esp+44h] [ebp-24h]
  int dialogX; // [esp+48h] [ebp-20h]
  int confirmBtnXMin; // [esp+4Ch] [ebp-1Ch]
  int cancelBtnXMax; // [esp+50h] [ebp-18h]

  tileX2 = tileX;
  tileY2 = tileY;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  spriteSetAlloc = (_DWORD *)Mem_Alloc(4112, v4, spritePath, a4);
  if ( spriteSetAlloc )
    spriteSetAlloc = DLXSpriteSet_Load(spriteSetAlloc, spritePath);
  dialogSpriteSet = spriteSetAlloc;
  dialogX = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)spriteSetAlloc, 0)) / 2;
  dialogY = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)dialogSpriteSet, 0)) / 2;
  Surface = (_DWORD *)Mem_Alloc(188, v6, spritePath, a4);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)dialogSpriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)dialogSpriteSet, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  dialogSurface = Surface;
  fillRectYMax = dialogY + DLX_GetSpriteWidth((int)dialogSpriteSet, 0) - 1;
  spriteHeight = DLX_GetSpriteHeight((int)dialogSpriteSet, 0);
  Render_FillRect(0, dialogSurface, (unsigned __int16)dialogY, (unsigned __int16)dialogX, dialogX + spriteHeight - 1, fillRectYMax, 0, 0);
  Render_ReleaseSurface(17, a4);
  if ( g_LanguageIndex == 2 )
    glyphIndex = 10;
  else
    glyphIndex = 0;
  SpriteForChar = DLX_GetSpriteForChar((int)dialogSpriteSet, glyphIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    dialogY,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  messageStrings[0] = (int)g_TrapPitfallDiscoveryMessageStrings[0];
  messageStrings[1] = (int)g_TrapPitfallDiscoveryMessageStrings[1];
  messageStrings[2] = (int)g_TrapPitfallDiscoveryMessageStrings[2];
  if ( g_LanguageIndex )
  {
    secondLineY = dialogY + 52;
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      UI_DrawTextFmt((int)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 32, 3, (int)aThisIsAPitfall);
      UI_DrawTextFmt((int)&dialogSpriteSet, v20, v21, secondLineY, 3, (int)aDoYouWantToCov);
      goto LABEL_9;
    }
    if ( g_LanguageIndex == 2 )
    {
      UI_DrawTextFmt((int)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 32, 3, (int)aDasIstDieWolfs);
      UI_DrawTextFmt((int)&dialogSpriteSet, v22, v23, secondLineY, 3, (int)aWillstDuSieZus);
      goto LABEL_9;
    }
  }
  UI_DrawTextFmt((int)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 42, 3, messageStrings[(unsigned __int8)g_LanguageIndex]);
LABEL_9:
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)g_RenderState);
  confirmBtnXMin = dialogX + 175;
  confirmBtnXMax = dialogX + 220;
  confirmBtnYMin = dialogY + 103;
  cancelBtnXMin = dialogX + 60;
  confirmBtnYMax = dialogY + 117;
  cancelBtnYMin = dialogY + 100;
  cancelBtnYMax = dialogY + 113;
  cancelBtnXMax = dialogX + 92;
  while ( 1 )
  {
    do
      DD_Pump((int)g_RenderState, cancelBtnXMin);
    while ( !DD_IsFlipping((int)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= cancelBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= cancelBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= cancelBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= cancelBtnYMax )
    {
      break;
    }
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= confirmBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= confirmBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= confirmBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= confirmBtnYMax )
    {
      Trap_ClearTileOwnerMask(tileX2, tileY2);
      break;
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  eraseY = dialogY;
  eraseX = dialogX;
  eraseWidth = DLX_GetSpriteWidth((int)dialogSpriteSet, 0) - 1;
  eraseHeight = DLX_GetSpriteHeight((int)dialogSpriteSet, 0);
  Render_FillRect(dialogSurface, 0, 0, 0, eraseHeight - 1, eraseWidth, eraseX, eraseY);
  if ( dialogSurface )
    (*(void (__cdecl **)(int, int, int))dialogSurface[46])(messageStrings[0], messageStrings[1], messageStrings[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&dialogSpriteSet);
  Render_Present((int)g_RenderState);
  g_RenderDevice = savedRenderDevice;
  return WorldMap_RedrawViewport(1);
}
// 42BA03: variable 'v4' is possibly undefined
// 42BA5D: variable 'v6' is possibly undefined
// 42BA8A: variable 'v10' is possibly undefined
// 42BD1C: variable 'v20' is possibly undefined
// 42BD1C: variable 'v21' is possibly undefined
// 42BD3D: variable 'v22' is possibly undefined
// 42BD3D: variable 'v23' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B3C: using guessed type char *off_514B3C[2];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (0042BF00) --------------------------------------------------------
int  Battle_LoadWallSegmentsFromBuildingRecord(int buildingRecord)
{
  int buildingCellPtr; // ebx
  int col; // eax
  int colByteOffset; // edx
  int tileValue; // esi
  int aboveTileValue; // esi
  int belowTileValue; // ecx
  int result; // eax
  int wallRowBase; // [esp+4h] [ebp-30h]
  int prevRowIndex; // [esp+8h] [ebp-2Ch]
  int rowByteOffset; // [esp+Ch] [ebp-28h]
  int row; // [esp+10h] [ebp-24h]

  row = 1;
  rowByteOffset = 40;
  prevRowIndex = 0;
  wallRowBase = 20;
  while ( *(_DWORD *)(g_MapData + 804) - 1 > row )
  {
    buildingCellPtr = buildingRecord;
    col = 0;
    colByteOffset = 0;
    while ( col < *(_DWORD *)(g_MapData + 800) )
    {
      tileValue = *(__int16 *)(colByteOffset + g_MapData + rowByteOffset);
      if ( tileValue >= 388 && tileValue <= 403 )
      {
        aboveTileValue = *(__int16 *)(colByteOffset + g_MapData + 40 * prevRowIndex);
        if ( aboveTileValue < 388 || aboveTileValue > 403 || (belowTileValue = *(__int16 *)(40 * (row + 1) + g_MapData + colByteOffset), belowTileValue < 388) || belowTileValue > 403 )
        {
          *(_BYTE *)(wallRowBase + g_MapData + col + 3134) = *(_BYTE *)(buildingCellPtr + 422);
          *(_BYTE *)(wallRowBase + g_MapData + col + 3534) = 100;
        }
      }
      colByteOffset += 2;
      ++buildingCellPtr;
      ++col;
    }
    rowByteOffset += 40;
    ++prevRowIndex;
    wallRowBase += 20;
    ++row;
  }
  *(_DWORD *)(g_MapData + 828) = *(_DWORD *)(g_MapData + 800) / 2;
  result = *(unsigned __int8 *)(buildingRecord + 421);
  *(_DWORD *)(g_MapData + 820) = result;
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C060) --------------------------------------------------------
char  Battle_SaveWallSegmentsToBuildingRecord(int buildingRecord)
{
  int wallRow; // edx
  int i; // eax
  int buildingCellPtr; // ecx
  int col; // eax
  int wallRowBase; // ebx
  char wallHp; // dl
  char result; // al

  wallRow = 0;
  for ( i = 0; wallRow < *(_DWORD *)(g_MapData + 804) && !*(_BYTE *)(g_MapData + i + 3534); i += 20 )
    ++wallRow;
  buildingCellPtr = buildingRecord;
  col = 0;
  wallRowBase = 20 * wallRow;
  while ( col < *(_DWORD *)(g_MapData + 800) )
  {
    ++buildingCellPtr;
    wallHp = *(_BYTE *)(wallRowBase + g_MapData + col++ + 3134);
    *(_BYTE *)(buildingCellPtr + 421) = wallHp;
  }
  result = g_CurrentPlayerIndex;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
  {
    result = *(_BYTE *)(g_MapData + 832);
    *(_BYTE *)(*(_DWORD *)(g_MapData + 828) + buildingRecord + 422) = result;
  }
  return result;
}
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;

//----- (0042C0F0) --------------------------------------------------------
BOOL  UnitBattle_IsTileInViewport(int tileRow, int tileCol)
{
  int rowOrigin; // ebx
  int colOrigin; // esi
  BOOL result; // eax

  rowOrigin = *(_DWORD *)(g_MapData + 808);
  result = 0;
  if ( tileRow >= rowOrigin && tileRow < rowOrigin + 7 )
  {
    colOrigin = *(_DWORD *)(g_MapData + 812);
    if ( tileCol >= colOrigin && tileCol < colOrigin + 7 )
      return 1;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C130) --------------------------------------------------------
void  Battle_LogUnitEntry(__int16 *unitRecord, DWORD a2, ...)
{
  char *unit_name;

  if ( !unitRecord )
    return;
  unit_name = UnitType_GetLocalizedName((unit_type)*unitRecord);
  Debug_Log((int)(uintptr_t)unitRecord, 0, a2, (int)aD0x08x15sPl1dP, unit_name);
}
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0042C180) --------------------------------------------------------
void  Battle_LogAllUnits(int a1, char a2, DWORD a3)
{
  int slotIndex; // ebx
  __int16 *unitRecord; // ecx
  int v6; // ecx

  Debug_Log(a1, a2, a3, (int)aBattle_logallu);
  slotIndex = 0;
  unitRecord = (__int16 *)(g_MapData + 852);
  do
  {
    while ( *unitRecord == -1 )
    {
      ++slotIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
      if ( slotIndex >= 22 )
        return;
    }
    Battle_LogUnitEntry(unitRecord, a3);
    ++slotIndex;
    unitRecord = (__int16 *)((char *)unitRecord + 31);
  }
  while ( slotIndex < 22 );
}
// 42C1BF: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042C1D0) --------------------------------------------------------
int  GodAnger(DWORD playerIndex, int a2, char a3)
{
  int k; // ecx
  int unitRecord; // esi
  int result; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD *v10; // eax
  int i; // esi
  __lock *v12; // ecx
  int SpriteForChar; // eax
  unsigned __int8 *v14; // edx
  __lock *v15; // ecx
  int v16; // ecx
  __int16 SpriteHeight; // ax
  int flashLevel; // esi
  __lock *v19; // ecx
  int j; // esi
  __lock *v21; // ecx
  unsigned __int16 lightningWidth; // [esp+Ch] [ebp-838h]
  unsigned __int8 v23[1024]; // [esp+1Ch] [ebp-828h] BYREF
  unsigned __int8 v24[1024]; // [esp+41Ch] [ebp-428h] BYREF
  int messageStrings[3]; // [esp+81Ch] [ebp-28h]
  _DWORD *lightningSpriteSet; // [esp+828h] [ebp-1Ch] BYREF
  void *v27; // [esp+82Ch] [ebp-18h]

  Debug_Log(a2, a3, playerIndex, (int)aGodanger);
  messageStrings[0] = (int)g_GodAngerMessageStrings[0];
  messageStrings[1] = (int)g_GodAngerMessageStrings[1];
  messageStrings[2] = (int)g_GodAngerMessageStrings[2];
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * playerIndex + 140059) )
  {
    UnitBattle_ShowPlayerMessageBanner(messageStrings[(unsigned __int8)g_LanguageIndex], playerIndex, 0, playerIndex);
    Render_Pump();
    v27 = g_RenderDevice;
    memset(v23, 0, sizeof(v23));
    Palette_LoadFromQueryHandle((intptr_t)v24, (intptr_t)"white.pal");
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_white_palette", (int)playerIndex, 0, 0, 0);
    v10 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( v10 )
      v10 = DLXSpriteSet_Load(v10, "lightn.s32");
    lightningSpriteSet = v10;
    for ( i = 0; i < 300; ++i )
    {
      v12 = (__lock *)i;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, v23, v12, 450);
    }
    g_RenderDevice = &g_MainRenderDevice;
    SpriteForChar = DLX_GetSpriteForChar((int)lightningSpriteSet, 0);
    Compat_RenderDeviceDrawMenuSprite(16, 100, SpriteForChar, 1);
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_lightning_draw", (int)playerIndex, (int)(uintptr_t)lightningSpriteSet, SpriteForChar, 0);
    Audio_PlayArtifactSound(0);
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, v24, 150, 200);
    Timer_BusyWaitWithCallback(10, 0, 0);
    lightningWidth = DLX_GetSpriteWidth((int)lightningSpriteSet, 0) + 16;
    SpriteHeight = DLX_GetSpriteHeight((int)lightningSpriteSet, 0);
    flashLevel = 150;
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 50, SpriteHeight + 200, lightningWidth, 0x32u, 0x10u);
    do
    {
      v19 = (__lock *)flashLevel;
      flashLevel -= 60;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, v24, v19, 200);
    }
    while ( flashLevel > 0 );
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, v23, (__lock *)0x96, 200);
    for ( j = 0; j < 150; ++j )
    {
      v21 = (__lock *)j;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, v21, 150);
    }
    Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_MapPalettePtr);
    DLXSpriteSet_ReleaseAndClear((int *)&lightningSpriteSet);
    g_RenderDevice = v27;
    Render_Present((int)g_RenderState);
    UnitBattle_RedrawVisibleGrid();
  }
  for ( k = 0; k != 682; k += 31 )
  {
    unitRecord = k + g_MapData;
    result = *(__int16 *)(k + g_MapData + 852);
    if ( result != -1 )
    {
      result = *(unsigned __int8 *)(unitRecord + 854);
      if ( result == playerIndex )
      {
        *(_BYTE *)(unitRecord + 861) -= Rng_RandRange(20, 30);
        result = *(char *)(k + g_MapData + 861);
        if ( result <= 0 )
        {
          *(_WORD *)(k + g_MapData + 852) = -1;
          result = *(unsigned __int16 *)(k + g_MapData + 858);
          *(_WORD *)(g_MapData + 40 * *(unsigned __int16 *)(k + g_MapData + 856) + 2 * result + 1534) = -1;
        }
      }
    }
  }
  return result;
}
// 42C25B: variable 'k' is possibly undefined
// 42C2BF: variable 'v7' is possibly undefined
// 42C2D0: variable 'v8' is possibly undefined
// 42C2DA: variable 'v9' is possibly undefined
// 42C37C: variable 'v14' is possibly undefined
// 42C37C: variable 'v15' is possibly undefined
// 42C388: variable 'v16' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B50: using guessed type char *off_514B50[9];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042C4C0) --------------------------------------------------------
int  Battle_NewTurn(int a1, char a2, DWORD a3)
{
  int v3; // ecx
  int result; // eax

  Debug_Log(a1, a2, a3, (int)aBattle_newturn);
  Battle_LogAllUnits(v3, a2, a3);
  for ( result = 0; result < 2; ++result )
    ;
  return result;
}
// 42C4CD: variable 'v3' is possibly undefined

//----- (0042C4E0) --------------------------------------------------------
BOOL Battle_HasUnitsForBothSides()
{
  int attackerPresent; // esi
  int defenderPresent; // edi
  int i; // eax
  int owner; // ecx

  attackerPresent = 0;
  defenderPresent = 0;
  for ( i = 0; i != 682; i += 31 )
  {
    if ( *(__int16 *)(i + g_MapData + 852) != -1 )
    {
      owner = *(unsigned __int8 *)(i + g_MapData + 854);
      if ( owner == *(_DWORD *)(g_MapData + 836) )
      {
        attackerPresent = 1;
      }
      else if ( owner == *(_DWORD *)(g_MapData + 840) )
      {
        defenderPresent = 1;
      }
    }
  }
  return attackerPresent && defenderPresent;
}
// 532048: using guessed type int g_MapData;

//----- (0042C560) --------------------------------------------------------
int  Battle_ApplyPeriodicDamageToSideUnits(int sideOwner)
{
  int slotIndex; // ebx
  __int16 *unitRecord; // ecx
  int result; // eax
  int apResilience; // esi
  int damage; // eax
  char newHealth; // ah

  slotIndex = 0;
  unitRecord = (__int16 *)(g_MapData + 852);
  do
  {
    while ( 1 )
    {
      result = *unitRecord;
      if ( result != -1 && *((unsigned __int8 *)unitRecord + 2) == sideOwner )
      {
        apResilience = (unsigned __int8)g_UnitTypeBaseActionPoints_512580[88 * result] - 15;
        damage = Rng_RandRange(25, 35) - apResilience;
        if ( damage < 0 )
          damage = 0;
        if ( damage > *((char *)unitRecord + 9) )
          LOBYTE(damage) = *((_BYTE *)unitRecord + 9);
        newHealth = *((_BYTE *)unitRecord + 9) - damage;
        *((_BYTE *)unitRecord + 9) = newHealth;
        result = newHealth;
        if ( result <= 0 )
          break;
      }
      ++slotIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
      if ( slotIndex >= 22 )
        return result;
    }
    *unitRecord = -1;
    ++slotIndex;
    unitRecord = (__int16 *)((char *)unitRecord + 31);
  }
  while ( slotIndex < 22 );
  return result;
}
// 42C5B3: variable 'v3' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042C600) --------------------------------------------------------
_BOOL2 UnitBattle_HandleManualRotateAndMoveInput()
{
  int IsKeyPressed; // eax
  int v2; // ecx
  int v3; // eax
  char facingCW; // dl
  int v5; // ecx
  int v6; // eax
  char facingCCW; // bl
  int unitRecord; // ecx
  int facing; // eax
  DWORD deltaY; // ebp
  int v11; // ecx
  int *movePath; // ebx
  unsigned __int16 requiredAp; // bx
  int v14; // ecx
  int v15; // ecx

  if ( Input_IsKeyPressed(34) )
  {
    if ( *(_DWORD *)(gameData + 147151) )
      goto LABEL_5;
    *(_DWORD *)(gameData + 147151) = 1;
    goto LABEL_4;
  }
  if ( *(_DWORD *)(gameData + 147151) )
  {
    *(_DWORD *)(gameData + 147151) = 0;
LABEL_4:
    UnitBattle_RedrawVisibleGrid();
  }
LABEL_5:
  IsKeyPressed = Input_IsKeyPressed(56);
  if ( IsKeyPressed )
  {
    if ( Input_IsKeyPressed(205) && g_SelectedUnitIndex != -1 )
    {
      v2 = g_MapData;
      v3 = 31 * g_SelectedUnitIndex;
      facingCW = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) + 1;
      *(_BYTE *)(g_MapData + v3 + 855) = facingCW;
      *(_BYTE *)(v2 + v3 + 855) = facingCW & 7;
      UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
      while ( Input_IsKeyPressed(205) )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, (char)g_RenderState);
      }
    }
    if ( Input_IsKeyPressed(203) && g_SelectedUnitIndex != -1 )
    {
      v5 = g_MapData;
      v6 = 31 * g_SelectedUnitIndex;
      facingCCW = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) - 1;
      *(_BYTE *)(g_MapData + v6 + 855) = facingCCW;
      *(_BYTE *)(v5 + v6 + 855) = facingCCW & 7;
      UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
      while ( Input_IsKeyPressed(203) )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, (char)g_RenderState);
      }
    }
    IsKeyPressed = Input_IsKeyPressed(200);
    if ( IsKeyPressed )
    {
      if ( g_SelectedUnitIndex != -1 )
      {
        unitRecord = 31 * g_SelectedUnitIndex + g_MapData + 852;
        facing = *(unsigned __int8 *)(unitRecord + 3);
        deltaY = Map_NeighborDY[2 * facing];
        movePath = UnitBattle_MoveTrack(
                g_SelectedUnitIndex,
                Map_NeighborDX[2 * facing] + *(unsigned __int16 *)(unitRecord + 4),
                unitRecord,
                deltaY + *(unsigned __int16 *)(unitRecord + 6),
                deltaY);
        LOWORD(IsKeyPressed) = 31 * g_SelectedUnitIndex;
        *(_DWORD *)(g_MapData + 31 * g_SelectedUnitIndex + 875) = movePath;
        if ( movePath )
        {
          requiredAp = HIWORD(*(_DWORD *)(*(_DWORD *)(v11 + 23) + 4));
          if ( *(unsigned __int8 *)(v11 + 8) < (int)requiredAp )
          {
            LOWORD(IsKeyPressed) = j__nfree_();
            *(_DWORD *)(v15 + 23) = 0;
          }
          else
          {
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
            LOWORD(IsKeyPressed) = UnitBattle_Move(g_SelectedUnitIndex, v14, requiredAp, deltaY);
          }
        }
      }
    }
  }
  return IsKeyPressed;
}
// 42C7D4: variable 'v11' is possibly undefined
// 42C815: variable 'v14' is possibly undefined
// 42C829: variable 'v15' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042C840) --------------------------------------------------------
int __thiscall UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(int this)
{
  unsigned int v3; // eax
  unsigned int scroll_deadline; // edx
  int result; // eax
  int v6; // edx
  int v7; // edi
  int v8; // esi
  int v9; // ebx
  int v10; // eax
  int v11; // esi
  int v12; // ecx
  int v13; // eax

  (void)this;
  scroll_deadline = 16 - *(unsigned __int8 *)(gameData + 147171) + g_BattleViewportScrollRepeatDelayBias;
  v3 = Time_Now(0, 0);
  if ( v3 > scroll_deadline && !Input_IsKeyPressed(56) )
  {
    if ( Input_IsKeyPressed(203) )
    {
      v6 = *(_DWORD *)(g_MapData + 808);
      if ( v6 )
      {
        *(_DWORD *)(g_MapData + 808) = v6 - 1;
        UnitBattle_RedrawVisibleGrid();
      }
    }
    if ( Input_IsKeyPressed(205) && *(_DWORD *)(g_MapData + 808) + 7 < *(_DWORD *)(g_MapData + 804) )
    {
      ++*(_DWORD *)(g_MapData + 808);
      UnitBattle_RedrawVisibleGrid();
    }
    if ( Input_IsKeyPressed(200) )
    {
      v7 = *(_DWORD *)(g_MapData + 812);
      if ( v7 )
      {
        *(_DWORD *)(g_MapData + 812) = v7 - 1;
        UnitBattle_RedrawVisibleGrid();
      }
    }
    if ( Input_IsKeyPressed(208) && *(_DWORD *)(g_MapData + 812) + 7 < *(_DWORD *)(g_MapData + 800) )
    {
      ++*(_DWORD *)(g_MapData + 812);
      UnitBattle_RedrawVisibleGrid();
    }
  }
  result = *(__int16 *)(40
                      * (*(_DWORD *)(g_MapData + 808)
                       + (((g_MouseCursorRawX >> g_CursorCoordShift)
                         - 32
                         - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
                          + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6))
                      + g_MapData
                      + 2
                      * ((((g_MouseCursorRawY >> g_CursorCoordShift)
                         - 16
                         - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                          + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
                       + *(_DWORD *)(g_MapData + 812))
                      + 1534);
  if ( result == -1 )
  {
    result = DD_IsLost((int)g_RenderState);
    if ( result )
    {
      Render_Pump();
      v8 = g_MouseCursorRawX >> g_CursorCoordShift;
      v9 = g_MouseCursorRawY >> g_CursorCoordShift;
      while ( DD_IsLost((int)g_RenderState) )
      {
        DD_Pump((int)g_RenderState, v9);
        v10 = (g_MouseCursorRawX >> g_CursorCoordShift) - v8;
        if ( v10 <= 0 )
          v10 = v8 - (g_MouseCursorRawX >> g_CursorCoordShift);
        if ( v10 < 8 )
        {
          v13 = (g_MouseCursorRawY >> g_CursorCoordShift) - v9;
          if ( v13 <= 0 )
            v13 = v9 - (g_MouseCursorRawY >> g_CursorCoordShift);
          if ( v13 < 8 )
            continue;
        }
        *(_DWORD *)(g_MapData + 808) += ((g_MouseCursorRawX >> g_CursorCoordShift)
                                          - v8
                                          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - v8) >> 31, 3)
                                           + 8 * (((g_MouseCursorRawX >> g_CursorCoordShift) - v8) >> 31))) >> 3;
        *(_DWORD *)(g_MapData + 812) += ((g_MouseCursorRawY >> g_CursorCoordShift)
                                          - v9
                                          - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - v9) >> 31, 3)
                                           + 8 * (((g_MouseCursorRawY >> g_CursorCoordShift) - v9) >> 31))) >> 3;
        if ( *(int *)(g_MapData + 808) < 0 )
          *(_DWORD *)(g_MapData + 808) = 0;
        v11 = *(_DWORD *)(g_MapData + 804);
        if ( *(_DWORD *)(g_MapData + 808) + 7 > v11 )
          *(_DWORD *)(g_MapData + 808) = v11 - 7;
        if ( *(int *)(g_MapData + 812) < 0 )
          *(_DWORD *)(g_MapData + 812) = 0;
        v12 = *(_DWORD *)(g_MapData + 800);
        if ( *(_DWORD *)(g_MapData + 812) + 7 > v12 )
          *(_DWORD *)(g_MapData + 812) = v12 - 7;
        UnitBattle_RedrawVisibleGrid();
        v8 = g_MouseCursorRawX >> g_CursorCoordShift;
        v9 = g_MouseCursorRawY >> g_CursorCoordShift;
      }
      UnitBattle_RedrawVisibleGrid();
      return Render_Present((int)g_RenderState);
    }
  }
  return result;
}
// 42C86E: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;
// 532040: using guessed type int dword_532040;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

