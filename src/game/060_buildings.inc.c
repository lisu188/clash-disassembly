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
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int scanByteOffset; // eax
  int v13; // eax
  char v14; // al
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
  char v27; // al
  char v28; // al
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // ecx
  int v34; // edi
  int revealRow; // edi
  int revealColEnd; // ebp
  int revealColDelta; // esi
  signed int revealCol; // ecx
  int v39; // eax
  signed int v40; // edx
  void *v41; // eax
  BOOL result; // eax
  int v43; // eax
  int v44; // ecx
  signed int v45; // ecx
  int v46; // eax
  int v47; // eax
  int v48; // eax
  __int16 v49; // dx
  int v50; // eax
  int v51; // eax
  int v52; // ebx
  int v53; // esi
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
  v9 = UNIT_STACK_STRIDE * stackIndex;
  g_CurrentPlayerIndex = *(unsigned __int8 *)(gameData + v9 + 147178);
  if ( g_BuildingNewOverrideActive )
  {
    row = g_BuildingNewOverrideRow;
    column = g_BuildingNewOverrideColumn;
  }
  else
  {
    row = *(__int16 *)(gameData + v9 + UNIT_STACK_TABLE_OFFSET);
    column = *(__int16 *)(gameData + v9 + 147176);
  }
  if ( buildingType == 1 && UnitStack_HasPeasantCargo(v9 + gameData + UNIT_STACK_TABLE_OFFSET) )
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
      v46 = *(unsigned __int16 *)(TILE_ROW_STRIDE * (row + 1) + gameData + 2 * column + TILE_MAP_OFFSET);
      if ( v46 != 0xFFFF && v46 != stackIndex )
        return 0;
      v47 = *(unsigned __int16 *)(200 * (row + 1) + gameData + 2 * column + 556376);
      if ( v47 != 0xFFFF && v47 != stackIndex )
        return 0;
      v48 = *(unsigned __int16 *)(gameData + 200 * row + 2 * column + 556376);
      if ( v48 != 0xFFFF && v48 != stackIndex )
        return 0;
    }
    v43 = *(unsigned __int16 *)(TILE_INDEX(row, column));
    if ( v43 != 0xFFFF && v43 != stackIndex )
      return 0;
  }
  v11 = 0;
  scanByteOffset = 0;
  scanIndex = 0;
  do
  {
    if ( *(char *)(gameData + scanByteOffset + 509678) == -1 )
      v11 = 1;
    scanByteOffset += 467;
    ++scanIndex;
  }
  while ( scanByteOffset < 46700 && !v11 );
  v13 = scanIndex - 1;
  buildingIndex = scanIndex - 1;
  if ( !v11 )
    return 0;
  buildingIndexCopy = v13;
  buildingPtr = UNIT_RECORD(buildingIndex);
  *(_BYTE *)buildingPtr = row;
  *(_BYTE *)(buildingPtr + 1) = column;
  v14 = g_CurrentPlayerIndex;
  *(_BYTE *)(buildingPtr + 3) = g_CurrentPlayerIndex;
  *(_BYTE *)(buildingPtr + 2) = v14;
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
    v27 = *name;
    *nameDest = *name;
    if ( !v27 )
      break;
    v28 = name[1];
    name += 2;
    nameDest[1] = v28;
    nameDest += 2;
  }
  while ( v28 );
  memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 0, 7);
  if ( buildingType == 1 )
  {
    *(_BYTE *)(buildingPtr + 421) = 1;
    v49 = *(_WORD *)(buildingPtr + 430) & 0xF000;
    *(_BYTE *)(buildingPtr + 416) |= BUILDING_ADDON_FLAG_BARRACKS;
    *(_WORD *)(buildingPtr + 430) = v49;
  }
  v30 = buildingPtr;
  do
  {
    v30 += 6;
    *(_BYTE *)(v30 + 439) = -1;
  }
  while ( v30 != buildingPtr + 18 );
  v31 = buildingPtr;
  do
  {
    v31 += 31;
    *(_WORD *)(v31 - 13) = -1;
  }
  while ( v31 != buildingPtr + 372 );
  v32 = buildingPtr + 1;
  *(_BYTE *)(buildingPtr + 402) = 0;
  do
    *(_BYTE *)(++v32 + 401) = -1;
  while ( v32 != buildingPtr + 12 );
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = -1;
  Diagnostics_TraceBootstrapEvent("Building_New-before-unit-get-into");
  Building_UnitGetInto(stackIndex, buildingIndexCopy, 7, stackIndex, st7_0);
  Diagnostics_TraceBootstrapEvent("Building_New-after-unit-get-into");
  *(_WORD *)(TILE_INDEX(row, column)) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
  if ( buildingType == 1 || buildingType == 2 )
  {
    v34 = 200 * (row + 1);
    *(_WORD *)(v34 + gameData + 2 * column + TILE_MAP_OFFSET) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(gameData + 200 * row + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(v34 + gameData + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( !force )
    {
      v51 = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
      if ( v51 == 707 )
      {
        LOWORD(v51) = 0;
      }
      else if ( v51 == 711 )
      {
        LOWORD(v51) = 4;
      }
      v52 = TILE_TERRAIN_ROW_STRIDE * (row + 1);
      v53 = 14 * (column + 1);
      *(_WORD *)(v53 + v52 + gameData) = v51;
      *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * row + gameData + v53) = v51;
      *(_WORD *)(gameData + v52 + 14 * column) = v51;
      *(_WORD *)(TILE_TERRAIN_RECORD_STRIDE * column + gameData + TILE_TERRAIN_ROW_STRIDE * row) = v51;
    }
  }
  else if ( !force )
  {
    v50 = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
    if ( v50 == 707 )
    {
      LOWORD(v50) = 0;
    }
    else if ( v50 == 711 )
    {
      LOWORD(v50) = 4;
    }
    *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * row + gameData + TILE_TERRAIN_RECORD_STRIDE * column) = v50;
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
  v39 = PLAYER_DATA(g_CurrentPlayerIndex);
  if ( *(_DWORD *)(v39 + 140067) == -1 && buildingType == 2 )
    *(_DWORD *)(v39 + 140067) = buildingIndex;
  if ( ACTIVE_MISSION_INDEX == -1 || GAME_TURN_COUNTER != 1 )
    Building_AssignUniqueGeneratedName(buildingPtr);
  Diagnostics_TraceBootstrapEvent("Building_New-before-minimap");
  if ( buildingType )
  {
    MiniMap_DrawTileCell((void *)row, column);
    MiniMap_DrawTileCell((void *)(row + 1), column);
    MiniMap_DrawTileCell((void *)row, column + 1);
    v40 = column + 1;
    v41 = (void *)(row + 1);
  }
  else
  {
    v40 = column;
    v41 = (void *)row;
  }
  MiniMap_DrawTileCell(v41, v40);
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
  int v7; // ecx

  surfaceClass = Map_GetTileSurfaceClassOrUnexplored(row, column);
  if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 207 || surfaceClass == 1 )
    return 0;
  if ( checkMode )
  {
    v6 = 2 * column;
    v7 = TILE_TERRAIN_ROW_STRIDE * row + gameData;
    return *(unsigned __int16 *)(v7 + 7 * v6) >= 0x2C3u && *(unsigned __int16 *)(v7 + 7 * v6) <= 0x2CAu;
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
  int v6; // edx
  int v7; // eax
  signed int v8; // ecx
  int v9; // ebp
  signed int surfaceClass; // eax
  int tileOwner; // eax
  int v13; // ebp
  int v14; // ebx
  int v15; // esi
  int v16; // ebx
  int i; // eax
  int v18; // ecx
  int savedPlayerIndex; // [esp+0h] [ebp-40h]
  int footprintRadius; // [esp+4h] [ebp-3Ch]
  int v21; // [esp+8h] [ebp-38h]
  int v22; // [esp+10h] [ebp-30h]
  int v23; // [esp+18h] [ebp-28h]
  int colEnd; // [esp+28h] [ebp-18h]
  int v26; // [esp+2Ch] [ebp-14h]
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
  v6 = row - *(__int16 *)(gameData + UNIT_STACK_STRIDE * stackIndex + UNIT_STACK_TABLE_OFFSET);
  isValid = 1;
  v7 = v6;
  if ( v6 <= 0 )
    v7 = -v6;
  if ( v7 > footprintRadius )
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
  v26 = row;
  v23 = 200 * row;
  if ( row >= row + footprintRadius )
  {
LABEL_24:
    if ( buildingType != 3 )
    {
      v13 = row - 1;
      v14 = column + footprintRadius + 1;
      v21 = column - 1;
      v15 = 200 * (row - 1);
      v22 = 200 * (footprintRadius + row + 1);
      if ( v15 < v22 )
      {
        v16 = 2 * v14;
        do
        {
          for ( i = 2 * v21; i < v16; i += 2 )
          {
            if ( *(unsigned __int16 *)(v15 + gameData + i + TILE_MAP_OFFSET) >= 0x8000u
              && *(unsigned __int16 *)(v15 + gameData + i + TILE_MAP_OFFSET) != 0xFFFF )
            {
              isValid = 0;
            }
          }
          v15 += 200;
          ++v13;
        }
        while ( v15 < v22 );
      }
    }
    g_CurrentPlayerIndex = savedPlayerIndex;
    return isValid;
  }
  else
  {
    while ( 1 )
    {
      v8 = column;
      v9 = 2 * column;
      if ( column < colEnd )
        break;
LABEL_23:
      v23 += 200;
      if ( ++v26 >= row + footprintRadius )
        goto LABEL_24;
    }
    while ( 1 )
    {
      surfaceClass = Map_GetTileSurfaceClassOrUnexplored(v26, v8);
      if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 1 )
        isValid = 0;
      tileOwner = *(unsigned __int16 *)(v23 + gameData + v9 + TILE_MAP_OFFSET);
      if ( tileOwner != 0xFFFF && tileOwner != stackIndex )
        isValid = 0;
      if ( Trap_GetTileOwnerMask(row, column, g_CurrentPlayerIndex) || MapTile_GetReligiousSiteCategory(row, column) || MapTile_HasHiddenTreasure(row, column) )
        return 0;
      if ( buildingType == 3 && MapTile_IsCastleFoundationTile(row, column, 2) )
        return 0;
      v8 = v18 + 1;
      v9 += 2;
      if ( v8 >= colEnd )
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
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int revealRow; // edi
  int i; // esi
  signed int v14; // ecx
  char result; // al
  int row; // ebx
  int v17; // ecx
  int v18; // [esp+0h] [ebp-30h]
  int v19; // [esp+4h] [ebp-2Ch]
  int v20; // [esp+8h] [ebp-28h]
  int revealRowDelta; // [esp+Ch] [ebp-24h]
  int v22; // [esp+14h] [ebp-1Ch]

  Debug_Log(a2, a3, (DWORD)buildingPtr, (int)aBuilding_build);
  LOBYTE(v5) = *buildingPtr;
  Rules_LogCastleBuiltFactAndScheme(v6, *(unsigned __int16 *)(2 * buildingPtr[1] + gameData + TILE_ROW_STRIDE * v5 + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Rules_LogNewCastleFact(buildingPtr[2], *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Building_OnGarrisonChange(*(unsigned __int16 *)(2 * buildingPtr[1] + TILE_ROW_STRIDE * *buildingPtr + gameData + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v7, a4);
  v9 = (char)buildingPtr[4];
  if ( v9 == 2 || v9 == 1 )
    Map_RebuildRoadOverlayAtTile(*buildingPtr, buildingPtr[1] + 2);
  v10 = (char)buildingPtr[4];
  if ( !buildingPtr[4] )
  {
    v11 = buildingPtr[1];
    LOBYTE(v10) = *buildingPtr;
    v22 = v11 + 15;
    revealRow = v10 - 15;
    v20 = v11 - 15;
    v8 = v10 + 15;
    v19 = v10 + 15;
    revealRowDelta = -15;
    if ( v10 - 15 < v10 + 15 )
    {
      v18 = buildingPtr[1];
      do
      {
        v8 = v20;
        for ( i = v20 - v18; v8 < v22; ++i )
        {
          if ( Math_CeilSqrt(revealRowDelta * revealRowDelta + i * i) <= 15 )
    Map_RevealTileWithPropagation(revealRow, v14, buildingPtr[2]);
          v8 = v14 + 1;
        }
        ++revealRow;
        ++revealRowDelta;
      }
      while ( revealRow < v19 );
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
  unsigned __int8 v6; // dl
  int garrisonSlotPtr; // edx
  int remainingGold; // ecx
  int v9; // eax

  buildingPtr = (unsigned __int8 *)result;
  if ( (*(_BYTE *)(result + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    result = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(result);
    if ( result != -1 )
    {
      v6 = BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) - 1;
      BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = v6;
      if ( !v6 )
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
          v9 = PLAYER_DATA_STRIDE * buildingPtr[2];
          *(_DWORD *)(buildingPtr + 438) = remainingGold;
          if ( *(_DWORD *)(gameData + v9 + 140051) )
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
  unsigned __int8 *v5; // edx
  int v6; // eax
  unsigned __int8 v7; // ah
  char v8; // al
  unsigned __int8 v9; // ah
  unsigned __int8 *firstSlotPtr; // [esp+0h] [ebp-20h]

  slotPtr = buildingPtr;
  garrisonChanged = 0;
  slotIndex = 0;
  firstSlotPtr = buildingPtr + 18;
  v5 = buildingPtr;
  do
  {
    v6 = *((__int16 *)slotPtr + 9);
    if ( v6 != -1 )
    {
      v7 = BUILDING_GARRISON_SERVICE_STATE(v5, 0);
      if ( (v7 & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
      {
        v8 = (((unsigned __int8)(4 * v7) >> 5) - 1) & 7;
        v9 = v7 & 0xC7;
        BUILDING_GARRISON_SERVICE_STATE(v5, 0) = v9;
        LOBYTE(v6) = 8 * v8;
        BYTE1(v6) = v6 | v9;
        BUILDING_GARRISON_SERVICE_STATE(v5, 0) = BYTE1(v6);
        if ( (v6 & 0x3800) == 0 )
        {
          garrisonChanged = 1;
          slotPtr[27] = 100;
        }
      }
      else if ( (v7 & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
      {
        LOBYTE(v6) = ((v7 & BUILDING_GARRISON_TRAINING_TURNS_MASK) - 1) & 7;
        BYTE1(v6) = v7 & 0xF8;
        BUILDING_GARRISON_SERVICE_STATE(v5, 0) = BYTE1(v6);
        BYTE1(v6) |= v6;
        BUILDING_GARRISON_SERVICE_STATE(v5, 0) = BYTE1(v6);
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
    ++v5;
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
  _BYTE *v1; // ecx
  unsigned __int8 v2; // dl
  char countdown; // dl

  if ( result[429] )
  {
    countdown = result[429] - 1;
    result[429] = countdown;
    if ( !countdown )
      ++result[421];
  }
  v1 = result + 7;
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
  while ( result != v1 );
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
  unsigned __int8 v12; // ch
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
        v12 = result[444] & 0xF8;
        result[444] = v12;
        result[444] = newTechLevel & 7 | v12;
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
  int v13; // eax

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
            v13 = (char)buildingPtr[4];
            if ( v13 == 2 || v13 == 1 )
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
  int v6; // edx
  unsigned __int16 v7; // ax
  signed int result; // eax
  unsigned __int8 *v9; // ecx
  int v10; // ecx
  unsigned int v11; // ebx
  int v12; // ecx
  int squadCount; // eax
  __int16 *v14; // esi
  int v15; // eax
  __int16 *v16; // esi
  int v17; // edx
  __int64 v18; // rtt
  int *v19; // esi
  int v20; // edx
  int v21; // eax
  int v22; // eax
  unsigned __int8 *v23; // edx
  int v24; // ebx
  int v25; // eax
  int v26; // edx
  __int16 *v27; // ecx
  __int16 *v28; // edi
  __int16 *v29; // eax
  __int16 v30; // dx
  unsigned __int8 *v31; // ebx
  unsigned __int8 *v32; // ebx
  int v33; // ecx
  __int16 *v34; // edx
  __int16 *v35; // edx
  int v36; // [esp+0h] [ebp-2Ch] BYREF
  int v37; // [esp+4h] [ebp-28h] BYREF
  __int16 *newStackPtr; // [esp+8h] [ebp-24h]
  int v39; // [esp+Ch] [ebp-20h]
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
  buildingPtr = (unsigned __int8 *)(gameData + BUILDING_TABLE_OFFSET + v6);
  targetUnitRecord = 0;
  if ( targetStackIndex != -1 )
    targetUnitRecord = UNIT_RECORD(targetStackIndex);
  if ( transferGoldFlag && (unsigned int)amount > *(_DWORD *)(buildingPtr + 438) )
    return 0;
  if ( !transferGoldFlag )
  {
    v7 = *((_WORD *)buildingPtr + 215);
    HIBYTE(v7) &= 0xFu;
    if ( v7 < amount )
      return 0;
  }
  if ( Building_FindFreeAdjacentSpawnTile(buildingPtr, &v36, gameData + BUILDING_TABLE_OFFSET + v6, &v37) != 1 )
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
      v14 = newStackPtr + 3;
      qmemcpy((void *)v11, newStackPtr + 3, 0x1Cu);
      v14 += 14;
      v12 = 0;
      *(_WORD *)(v11 + 28) = *v14;
      *(_BYTE *)(v11 + 30) = *((_BYTE *)v14 + 2);
      v11 += 31;
    }
    if ( i <= 10 )
    {
      v15 = amount;
      v16 = newStackPtr + 3;
      v17 = amount;
      qmemcpy((void *)v11, newStackPtr + 3, 0x1Cu);
      v16 += 14;
      *(_WORD *)(v11 + 28) = *v16;
      *(_BYTE *)(v11 + 30) = *((_BYTE *)v16 + 2);
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
      HIWORD(v21) = HIWORD(buildingPtr);
      LOWORD(v21) = *((_WORD *)buildingPtr + 215);
      BYTE1(v21) &= 0xFu;
      v22 = v21 - amount;
      v23 = buildingPtr;
      LOWORD(v11) = *((_WORD *)buildingPtr + 215);
      v11 &= 0xFFFFF000;
      BYTE1(v22) &= 0xFu;
      *((_WORD *)buildingPtr + 215) = v11;
      v12 = v22 | v11;
      *((_WORD *)v23 + 215) = v22 | v11;
    }
    if ( targetUnitRecord
      && (v19 = (int *)Building_GenerateApproachTrack(
                         *(unsigned __int16 *)(TILE_INDEX(*buildingPtr, buildingPtr[1])),
                         savedTargetStack,
                         (int)buildingPtr,
                         v11,
                         (DWORD)savedregs)) != 0 )
    {
      while ( 1 )
      {
        v20 = v19[*v19];
        if ( (_WORD)v20 != *(_WORD *)buildingPtr )
        {
          v24 = (char)buildingPtr[4];
          if ( v24 != 1 && v24 != 2 )
            break;
          if ( (unsigned __int8)v20 < *buildingPtr
            || (unsigned __int8)v20 > *buildingPtr + 1
            || BYTE1(v20) < buildingPtr[1]
            || BYTE1(v20) > buildingPtr[1] + 1 )
          {
            break;
          }
        }
        --*v19;
      }
      v25 = *v19 - 1;
      *v19 = v25;
      v26 = v19[v25 + 1];
      v27 = newStackPtr;
      *newStackPtr = (unsigned __int8)v26;
      v27[1] = BYTE1(v26);
      v39 = 2 * buildingPtr[1] + gameData + 200 * *buildingPtr;
      v28 = newStackPtr + 158;
      *(_WORD *)(2 * BYTE1(v26) + TILE_ROW_STRIDE * (unsigned __int8)v26 + gameData + TILE_MAP_OFFSET) = *(_WORD *)(v39 + 556374);
      v29 = newStackPtr;
      qmemcpy(v28, v19, UNIT_STACK_PATH_BYTES);
      UnitStack_SetReadyFlags((int)v29);
    }
    else
    {
      Building_FindFreeAdjacentSpawnTile(buildingPtr, &v36, v12, &v37);
      v35 = newStackPtr;
      *newStackPtr = v36;
      v35[1] = v37;
      *(_WORD *)(2 * v37 + TILE_ROW_STRIDE * v36 + gameData + TILE_MAP_OFFSET) = *(_WORD *)(TILE_INDEX(*buildingPtr, buildingPtr[1]));
    }
    v30 = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(TILE_INDEX(*buildingPtr, buildingPtr[1])) = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    v31 = buildingPtr;
    *(_WORD *)(TILE_ROW_STRIDE * (*buildingPtr + 1) + gameData + 2 * buildingPtr[1] + TILE_MAP_OFFSET) = v30;
    *(_WORD *)(200 * (*v31 + 1) + gameData + 2 * buildingPtr[1] + 556376) = v30;
    v32 = buildingPtr;
    *(_WORD *)(200 * *buildingPtr + gameData + 2 * buildingPtr[1] + 556376) = v30;
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
BOOL  Building_CanStartUpgrade(unsigned __int8 *a1)
{
  return a1[421] < 2u && a1[421] < (a1[444] & 7) - 1 && !a1[429];
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
  DWORD v9; // eax
  unsigned __int8 buildingTechLevel; // bl
  unsigned __int8 playerTechLevel; // bh
  char v12; // dh
  int v13; // edx
  int turnCounter; // ebx
  int v15; // eax
  DWORD v16; // ecx
  DWORD v17; // ebx
  int i; // edi
  int v19; // edx
  int v20; // ecx
  int k; // edi
  int v22; // edx
  int v23; // ecx
  DWORD v24; // ebx
  DWORD v25; // ecx
  int m; // edi
  int v28; // [esp+4h] [ebp-24h]

  buildingByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
  v13 = buildingByteOffset;
  Debug_Log(a3, -45 * buildingIndex, buildingIndex, (int)aUnit_capturebu);
  buildingPtr = buildingByteOffset + gameData + BUILDING_TABLE_OFFSET;
  if ( *(_WORD *)(buildingByteOffset + gameData + 509690) )
    return Building_Destroy(buildingByteOffset + gameData + BUILDING_TABLE_OFFSET, buildingByteOffset, buildingIndex, a5);
  *(_BYTE *)(buildingByteOffset + gameData + 509676) = *(_BYTE *)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + 147178);
  v9 = buildingByteOffset + gameData;
  buildingTechLevel = *(_BYTE *)(buildingByteOffset + gameData + 510118) & 7;
  playerTechLevel = *(_BYTE *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + 147178) + gameData + 140071);
  if ( buildingTechLevel < playerTechLevel )
  {
    v12 = *(_BYTE *)(v9 + 510118) & 0xF8;
    *(_BYTE *)(v9 + 510118) = v12;
    *(_BYTE *)(v9 + 510118) = playerTechLevel & 7 | v12;
  }
  Rules_SyncCastleFactOwner(UNIT_RECORD(buildingIndex), buildingPtr, a5);
  v28 = v13;
  turnCounter = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
  Rules_LogBuildingCapturedFact(*(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * capturingStackIndex + 147178), buildingIndex, turnCounter);
  v15 = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v28 + gameData + 509676) + gameData;
  if ( buildingIndex == *(_DWORD *)(v15 + 140067) )
    *(_DWORD *)(v15 + 140067) = -1;
  Building_UnitGetInto(capturingStackIndex, buildingIndex, turnCounter, buildingIndex, a5);
  v16 = buildingPtr;
  v17 = v16;
  for ( i = 0; i < 3; ++i )
  {
    v19 = *(char *)(v17 + 445);
    if ( v19 != -1 && *(_BYTE *)(v17 + 446) == *(_BYTE *)(v16 + 2) )
    {
      Building_CreateSpecialPersonageGarrisonUnit(v16, v19, v16, (char)i, a5);
      Prisoner_Kill(v16, (char)i, buildingIndex);
    }
    v17 += 6;
  }
  for ( k = 0; k < 12; ++k )
  {
    Building_ClearGarrisonTrainingTimer(v16, k);
    v22 = k;
    Building_ClearGarrisonRepairTimer(v16, v22);
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
  int v9; // edx
  int v10; // eax
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
        v9 = outCount++;
        occupiedSlots[v9] = slotIndex;
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
          v10 = outCount++;
          occupiedSlots[v10] = slotIndex;
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
void * Building_ShowHoverInfoPopup(unsigned __int8 *buildingPtr, char a2, int a3)
{
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9; // ecx
  __int16 v10; // ax
  int SpriteForChar; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // esi
  int v15; // ecx
  int v16; // ecx
  int v17; // edi
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edi
  __int16 v24; // ax
  _DWORD *v25; // edi
  void *result; // eax
  int v27; // eax
  int v28; // edi
  int v29; // edx
  unsigned __int16 v30; // [esp+3Ch] [ebp-48h]
  unsigned __int16 v31; // [esp+3Ch] [ebp-48h]
  unsigned __int16 v32; // [esp+40h] [ebp-44h]
  unsigned __int16 v33; // [esp+44h] [ebp-40h]
  int v34[3]; // [esp+48h] [ebp-3Ch]
  _DWORD *spriteSet; // [esp+54h] [ebp-30h] BYREF
  int v36; // [esp+58h] [ebp-2Ch]
  int v37; // [esp+5Ch] [ebp-28h]
  _DWORD *surface; // [esp+60h] [ebp-24h]
  void *savedRenderDevice; // [esp+64h] [ebp-20h]
  int v40; // [esp+68h] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a2, (DWORD)buildingPtr);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a2);
  spriteSet = v5;
  v36 = 100;
  v40 = 100;
  Surface = (_DWORD *)Mem_Alloc(188, 100, a2, (DWORD)buildingPtr);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)spriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)spriteSet, 0);
    Surface = Render_CreateSurface(v9, SpriteHeight, SpriteWidth);
  }
  surface = Surface;
  v30 = v40 + DLX_GetSpriteWidth((int)spriteSet, 0) - 1;
  v10 = DLX_GetSpriteHeight((int)spriteSet, 0);
  Render_FillRect(0, surface, (unsigned __int16)v40, (unsigned __int16)v36, v36 + v10 - 1, v30, 0, 0);
  Render_ReleaseSurface(7, (DWORD)buildingPtr);
  if ( buildingPtr[4] )
  {
    SpriteForChar = DLX_GetSpriteForChar((int)spriteSet, buildingPtr[2] != g_CurrentPlayerIndex);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      v40,
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
    v27 = DLX_GetSpriteForChar((int)spriteSet, 6);
    a3 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(a3 + 52))(
      v40,
      v27,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  v12 = (char)buildingPtr[4];
  if ( buildingPtr[4] )
  {
    UI_DrawTextFmt(a3, v36 + 10, v36 + 235, v40 + 5, 3, (int)(buildingPtr + 5));
    if ( buildingPtr[2] == g_CurrentPlayerIndex )
    {
      if ( (buildingPtr[435] & 7) != 0 )
      {
        v13 = DLX_GetSpriteForChar((int)spriteSet, 2);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          v40 + 37,
          v13,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      v14 = v36;
      UI_DrawTextFmt(a3, v36, v36 + 89, v40 + 25, 2, (int)aD_21);
      UI_DrawTextFmt(a3, v14, v14 + 150, v15, 2, (int)aD_22);
      UI_DrawTextFmt(a3, v14, v14 + 210, v16, 2, (int)aD_23);
    }
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(a3, v36, v36 + 89, v40 + 62, 2, (int)aD_24);
    Building_CountGarrison((int)buildingPtr);
    Building_DrawGarrisonRow((int)buildingPtr);
    v17 = v36;
    v37 = v36 + 150;
    UI_DrawTextFmt(v36, v36, v36 + 150, v18, 2, (int)aD_25);
    Building_CountPrisoners((int)buildingPtr);
    UI_DrawTextFmt(v17, v17, v17 + 208, v19, 2, (int)aD_26);
    UI_DrawTextFmt(v17, v17, v20, v40 + 99, 2, (int)aD_27);
    v22 = v36 ^ v21;
    LOBYTE(v22) = buildingPtr[421];
    DLX_GetSpriteForChar((int)spriteSet, v22 + 3);
    v23 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v23 + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(v23, v36, v36 + 150, v40 + 99, 2, (int)aD_28);
    UI_DrawUnitStatsValues((int)buildingPtr);
    UI_DrawTextFmt(v23, v36, v36 + 205, v40 + 99, 2, (int)aD_29);
  }
  else
  {
    v34[0] = (int)UI_Locale_BuildingNames_A[0];
    v34[1] = (int)UI_Locale_BuildingNames_A[1];
    v34[2] = (int)UI_Locale_BuildingNames_A[2];
    LOBYTE(v12) = g_LanguageIndex;
    v28 = v34[v12];
    UI_DrawTextFmt(v28, v36 + 10, v36 + 175, v40 + 5, 3, v28);
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(v28, v36, v36 + 87, v40 + 25, 2, (int)aD_30);
    Building_CountGarrison((int)buildingPtr);
    Building_DrawGarrisonRow((int)buildingPtr);
    UI_DrawTextFmt(v28, v36, v36 + 150, v29, 2, (int)aD_31);
  }
  Render_Begin((int)g_RenderState, 0);
  v33 = v40;
  v32 = v36;
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
int  Building_ShowConstructionProgressDialog(DWORD a1, char a2, DWORD a3, double a4)
{
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 v11; // ax
  int SpriteForChar; // eax
  int v13; // ebx
  int v14; // edx
  int v15; // edi
  int v16; // edx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // edi
  int v22; // ebx
  signed int v23; // ebp
  int v24; // esi
  int v25; // ecx
  __int16 v26; // ax
  unsigned __int16 v28; // [esp+10h] [ebp-C4h]
  unsigned __int16 v29; // [esp+10h] [ebp-C4h]
  unsigned __int16 v30; // [esp+14h] [ebp-C0h]
  unsigned __int16 v31; // [esp+18h] [ebp-BCh]
  int v32[12]; // [esp+1Ch] [ebp-B8h] BYREF
  int v33[3]; // [esp+4Ch] [ebp-88h]
  int v34[3]; // [esp+58h] [ebp-7Ch]
  int v35[3]; // [esp+64h] [ebp-70h] BYREF
  int v36[3]; // [esp+70h] [ebp-64h]
  int v37[3]; // [esp+7Ch] [ebp-58h]
  int v38[3]; // [esp+88h] [ebp-4Ch]
  _DWORD *v39; // [esp+94h] [ebp-40h] BYREF
  _DWORD *v40; // [esp+98h] [ebp-3Ch]
  int v41; // [esp+9Ch] [ebp-38h]
  int v42; // [esp+A0h] [ebp-34h]
  int v43; // [esp+A4h] [ebp-30h]
  int v44; // [esp+A8h] [ebp-2Ch]
  int v45; // [esp+ACh] [ebp-28h]
  void *v46; // [esp+B0h] [ebp-24h]
  DWORD v47; // [esp+B4h] [ebp-20h]
  int v48; // [esp+B8h] [ebp-1Ch]

  v47 = a1;
  v46 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a2);
  v39 = v5;
  v41 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  v48 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v39, 0)) / 2;
  Surface = (_DWORD *)Mem_Alloc(188, v6, a2, a3);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)v39, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)v39, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  v40 = Surface;
  v28 = v48 + DLX_GetSpriteWidth((int)v39, 0) - 1;
  v11 = DLX_GetSpriteHeight((int)v39, 0);
  Render_FillRect(0, v40, (unsigned __int16)v48, (unsigned __int16)v41, v41 + v11 - 1, v28, 0, 0);
  Render_ReleaseSurface(17, a3);
  SpriteForChar = DLX_GetSpriteForChar((int)v39, 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    v48,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v35[0] = (int)UI_Locale_BuildingNames_B[0];
  v35[1] = (int)UI_Locale_BuildingNames_B[1];
  v35[2] = (int)UI_Locale_BuildingNames_B[2];
  v36[0] = (int)UI_Locale_BuildingNames_C[0];
  v36[1] = (int)UI_Locale_BuildingNames_C[1];
  v36[2] = (int)UI_Locale_BuildingNames_C[2];
  v37[0] = (int)UI_Locale_BuildingNames_D[0];
  v37[1] = (int)UI_Locale_BuildingNames_D[1];
  v37[2] = (int)UI_Locale_BuildingNames_D[2];
  qmemcpy(v32, UI_Locale_BuildingNames_E, sizeof(v32));
  v38[0] = (int)UI_Locale_BuildingNames_F[0];
  v38[1] = (int)UI_Locale_BuildingNames_F[1];
  v38[2] = (int)UI_Locale_BuildingNames_F[2];
  v33[0] = (int)UI_Locale_BuildingNames_G[0];
  v33[1] = (int)UI_Locale_BuildingNames_G[1];
  v33[2] = (int)UI_Locale_BuildingNames_G[2];
  v34[0] = (int)UI_Locale_BuildingNames_H[0];
  v34[1] = (int)UI_Locale_BuildingNames_H[1];
  v34[2] = (int)UI_Locale_BuildingNames_H[2];
  v13 = v41 + 30;
  UI_DrawTextFmt((int)v35, v41 + 30, v41 + 250, v48 + 12, 3, v35[(unsigned __int8)g_LanguageIndex]);
  UI_DrawTextFmt((int)v35, v13, v14, v48 + 32, 3, v36[(unsigned __int8)g_LanguageIndex]);
  v15 = v32[4 * *(char *)(v47 + 4) + (unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(v15, v13, v16, v48 + 52, 3, v37[(unsigned __int8)g_LanguageIndex]);
  v18 = Building_CalcRemainingConstructionTurns(v47);
  v20 = v19 + 77;
  if ( v18 == 1 )
  {
    UI_DrawTextFmt(v15, v13, v17, v20, 3, v38[(unsigned __int8)g_LanguageIndex]);
  }
  else if ( v18 > 4 )
  {
    UI_DrawTextFmt(v15, v13, v17, v20, 3, v34[(unsigned __int8)g_LanguageIndex]);
  }
  else
  {
    UI_DrawTextFmt(v33[(unsigned __int8)g_LanguageIndex], v13, v17, v20, 3, v33[(unsigned __int8)g_LanguageIndex]);
  }
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  v42 = v48 + 103;
  v43 = v41 + 220;
  v21 = v41 + 175;
  v22 = v48 + 100;
  v45 = v48 + 117;
  v23 = v41 + 92;
  v24 = v48 + 113;
  v44 = v41 + 60;
  while ( 1 )
  {
    do
      DD_Pump((int)g_RenderState, v22);
    while ( !DD_IsFlipping((int)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v44
      && g_MouseCursorRawY >> g_CursorCoordShift >= v22
      && g_MouseCursorRawX >> g_CursorCoordShift <= v23
      && g_MouseCursorRawY >> g_CursorCoordShift <= v24 )
    {
      break;
    }
    LOBYTE(v25) = g_CursorCoordShift;
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v21
      && g_MouseCursorRawY >> g_CursorCoordShift >= v42
      && g_MouseCursorRawX >> g_CursorCoordShift <= v43
      && g_MouseCursorRawY >> g_CursorCoordShift <= v45 )
    {
      Building_Stop(v47, v25, v22, v23, a4);
      break;
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  v31 = v48;
  v30 = v41;
  v29 = DLX_GetSpriteWidth((int)v39, 0) - 1;
  v26 = DLX_GetSpriteHeight((int)v39, 0);
  Render_FillRect(v40, 0, 0, 0, v26 - 1, v29, v30, v31);
  if ( v40 )
    (*(void (**)(void))v40[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&v39);
  Render_Present((int)g_RenderState);
  g_RenderDevice = v46;
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
int  Castle_RequestManagementScreenExit(uintptr_t a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_CastleScreenExitRequested = 1;
  return result;
}
// 526E80: using guessed type int g_CastleScreenExitRequested;

//----- (00420870) --------------------------------------------------------
int Castle_RebuildMissingAddonFlags()
{
  int v0; // edx
  int result; // eax

  g_CastleAddonSchoolMissingFlags[0] = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) == 0;
  g_CastleAddonHospitalMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) == 0;
  g_CastleAddonBarracksMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) == 0;
  g_CastleAddonWorkshopMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) == 0;
  v0 = 0;
  g_CastleAddonSmithsMissingFlag = (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) == 0;
  for ( result = 0; result != 50; result += 10 )
  {
    if ( g_CastleAddonSchoolMissingFlags[result] )
      v0 = 1;
  }
  if ( !v0 )
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
  int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // eax
  int v9; // eax
  int SpriteForChar; // eax
  DWORD v11; // ebp
  void (*v12)(void); // eax
  void *v13; // [esp+1Ch] [ebp-1Ch]

  v13 = g_RenderDevice;
  if ( !DD_IsFlipping((int)g_RenderState) || g_MouseCursorRawX >> g_CursorCoordShift <= 509 || g_MouseCursorRawY >> g_CursorCoordShift >= 66 )
    goto LABEL_4;
  Castle_RebuildMissingAddonFlags();
  v2 = &g_MainRenderDevice;
  v3 = -5;
  v4 = 0;
  g_RenderDevice = &g_MainRenderDevice;
  do
  {
    v5 = Time_Now(v1, (int)v2);
    v6 = 3;
    v7 = v4 / 3 + v5;
    do
      v8 = Time_Now(v6, v7);
    while ( v8 < v7 );
    Render_Pump();
    if ( v3 <= 0 )
      v9 = -v3;
    else
      v9 = v3;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 5 - v9);
    v11 = *((_DWORD *)g_RenderDevice + 46);
    v4 += 2;
    (*(void (__fastcall **)(_DWORD, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(v11 + 52))(
      0,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      0,
      0,
      0);
    ++v3;
    Render_Present((int)g_RenderState);
  }
  while ( v3 <= 5 );
  Render_Pump();
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 300, SCREEN_MAX_X, 0x12Cu, 0x12Cu, 0);
  Render_Present((int)g_RenderState);
  g_WorldMapTargetSurface = g_PrimaryRenderSurface;
  v12 = (void (*)(void))UI_RunMenu(g_CastleNewBuildingMenu, v11);
  if ( v12 )
  {
    v12();
    result = v13;
    g_RenderDevice = v13;
  }
  else
  {
LABEL_4:
    result = v13;
    g_RenderDevice = v13;
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
int  Castle_BuildSchoolWithAnimation(char a1, DWORD a2)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int v5; // ecx
  _BYTE *v6; // edi
  int v7; // esi
  int recordCopyPtr; // ebx

  Building_BuildSchool((char *)g_SelectedBuildingRecord, a1, a2);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, a2);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * v5);
    v7 = recordBase + 4 * v5;
    v6 = &recordCopy[4 * v5];
    *(_WORD *)v6 = *(_WORD *)v7;
    v6[2] = *(_BYTE *)(v7 + 2);
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
int  Castle_BuildWorkshopWithAnimation(char a1, DWORD a2)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int v5; // ecx
  _BYTE *v6; // edi
  int v7; // esi
  int recordCopyPtr; // ebx

  Building_BuildWorkshop(a1, a2);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, a2);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * v5);
    v7 = recordBase + 4 * v5;
    v6 = &recordCopy[4 * v5];
    *(_WORD *)v6 = *(_WORD *)v7;
    v6[2] = *(_BYTE *)(v7 + 2);
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
int  Castle_BuildBarracksWithAnimation(int a1, char a2, DWORD a3)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int v6; // ecx
  _BYTE *v7; // edi
  int v8; // esi
  int recordCopyPtr; // ebx

  Building_BuildBarracks(a1, a2, a3);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a2, a3);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * v6);
    v8 = recordBase + 4 * v6;
    v7 = &recordCopy[4 * v6];
    *(_WORD *)v7 = *(_WORD *)v8;
    v7[2] = *(_BYTE *)(v8 + 2);
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
int  Castle_BuildHospitalWithAnimation(char a1, DWORD a2)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int v5; // ecx
  _BYTE *v6; // edi
  int v7; // esi
  int recordCopyPtr; // ebx
  char *soundName; // eax

  Building_BuildHospital(a1, a2);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, a2);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * v5);
    v7 = recordBase + 4 * v5;
    v6 = &recordCopy[4 * v5];
    *(_WORD *)v6 = *(_WORD *)v7;
    v6[2] = *(_BYTE *)(v7 + 2);
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
int  Castle_BuildSmithsWithAnimation(char a1, DWORD a2)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int v5; // ecx
  _BYTE *v6; // edi
  int v7; // esi
  int recordCopyPtr; // ebx

  Building_BuildSmiths(a1, a2);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) != 0 )
  {
    recordCopy = (_BYTE *)Mem_Alloc(467, 116, a1, a2);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)g_SelectedBuildingRecord, 4 * v5);
    v7 = recordBase + 4 * v5;
    v6 = &recordCopy[4 * v5];
    *(_WORD *)v6 = *(_WORD *)v7;
    v6[2] = *(_BYTE *)(v7 + 2);
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
  int v2; // eax
  int result; // eax
  int v10; // eax

  SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(5, 5, SpriteForChar, 0);
  if ( PLAYER_RELIGION_FLAG(g_CurrentPlayerIndex) )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex + 5);
    Compat_RenderDeviceDrawMenuSprite(9, 9, SpriteForChar, 1);
  }
  Render_ReleaseSurface(7, 0);
  v2 = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, *(unsigned __int8 *)(g_SelectedBuildingRecord + 421) + 3 * g_CurrentPlayerIndex + 11);
  Compat_RenderDeviceDrawMenuSprite(26, 156, v2, 1);
  UI_DrawTextFmt(5, 41, 275, 10, 3, g_SelectedBuildingRecord + 5);
  UI_DrawTextFmt(5, 58, 87, 30, 2, (int)aD_42);
  UI_DrawTextFmt(5, 58, 149, 30, 2, (int)aD_43);
  UI_DrawUnitStatsValues(g_SelectedBuildingRecord);
  UI_DrawTextFmt(5, 58, 211, 30, 2, (int)aD_44);
  UI_DrawTextFmt(5, 58, 273, 30, 2, (int)aD_45);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(g_SelectedBuildingRecord + 435) & 7) != 0 )
  {
    v10 = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, 10);
    return Compat_RenderDeviceDrawMenuSprite(43, 127, v10, 1);
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
char  Castle_RenderCompositeSceneLayers(int surface, int a2, int a3, int a4)
{
  int surface2; // ebp
  char v5; // dl
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
  char v27; // bh
  char v28; // ch
  char v29; // dh
  char *v30; // edx
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
  int v59; // edx
  char v61[256]; // [esp+0h] [ebp-138h] BYREF
  __int16 v62[10]; // [esp+100h] [ebp-38h] BYREF
  char castleSpriteName[8]; // [esp+114h] [ebp-24h] BYREF
  void *v64; // [esp+11Ch] [ebp-1Ch]
  int buildingRecord; // [esp+120h] [ebp-18h]
  int variant; // [esp+124h] [ebp-14h]
  int drawMode; // [esp+128h] [ebp-10h]
  int load_result;

  surface2 = surface;
  drawMode = a2;
  variant = a4;
  buildingRecord = a3;
  strcpy(castleSpriteName, "zamek_1");
  LOBYTE(surface) = g_CurrentPlayerIndex + 49;
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  if ( a4 != 2 )
  {
    v5 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
    if ( (v5 & 1) == 0 || (v5 & 2) != 0 || (v5 & 4) != 0 )
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
    v12 = v61;
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
    v16 = &v61[strlen(v61)];
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
    v20 = &v61[strlen(v61)];
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
    v24 = &v61[strlen(v61)];
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
                    v61,
                    0,
                    (uintptr_t)g_CastleScreenPaletteBuffer);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=0 result=%d target=%08x\n", v61, load_result, surface2);
    LOBYTE(surface) = load_result;
  }
  if ( variant != 1 )
  {
    v27 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
    if ( (v27 & 8) != 0 && (v27 & 0x10) == 0 )
    {
      v30 = a04;
    }
    else
    {
      v28 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (v28 & 8) != 0 || (v28 & 0x10) == 0 )
      {
        v29 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
        if ( (v29 & 8) != 0 && (v29 & 0x10) != 0 )
          v30 = a08;
        else
          v30 = a02;
      }
      else
      {
        v30 = a06;
      }
    }
    v31 = castleSpriteName;
    v32 = v61;
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
    v36 = &v61[strlen(v61)];
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
    v39 = v30;
    v40 = &v61[strlen(v61)];
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
    v44 = &v61[strlen(v61)];
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
    load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, v61, 1, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", v61, load_result, surface2);
    surface = *(char *)(g_SelectedBuildingRecord + 4);
    if ( surface == 1 )
    {
      v47 = castleSpriteName;
      v48 = v61;
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
      v52 = &v61[strlen(v61)];
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
      load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, v61, 1, 0);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", v61, load_result, surface2);
      LOBYTE(surface) = load_result;
    }
  }
  if ( !drawMode )
  {
    v64 = g_RenderDevice;
    g_RenderDevice = (_UNKNOWN *)surface2;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 0);
    Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 0);
    qmemcpy(v62, &g_CastleOwnerIconPositions, sizeof(v62));
    castle_icon_owner = *(unsigned __int8 *)(g_SelectedBuildingRecord + 2);
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 8);
    Compat_RenderDeviceDrawMenuSprite(v62[2 * castle_icon_owner + 1], v62[2 * castle_icon_owner], SpriteForChar, 1);
    v59 = g_SelectedBuildingRecord;
    g_SelectedBuildingRecord = buildingRecord;
    Castle_DrawAllAmbientAnimationLayers(v58);
    g_SelectedBuildingRecord = v59;
    Castle_EnsureCompositeStatusWidget();
    UIWidgetTable_InitDrawStates((_DWORD *)g_CastleStatusWidgetRecord);
    LOBYTE(surface) = (_BYTE)v64;
    g_RenderDevice = v64;
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
        unsigned __int16 a1,
        int a2,
        int a3,
        int a4,
        unsigned __int8 a5)
{
  int v6; // ebp
  __int16 SpriteHeight; // ax
  int SpriteForChar; // eax
  int result; // eax
  unsigned __int16 v11; // [esp-4h] [ebp-1Ch]

  v6 = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    v11 = a2 + DLX_GetSpriteWidth(a4, a3);
    SpriteHeight = DLX_GetSpriteHeight(a4, a3);
    RenderState_PumpIfRectInViewBounds(g_RenderState, a1, a1 + SpriteHeight, a2, v11);
  }
  SpriteForChar = DLX_GetSpriteForChar(a4, a3);
  result = Compat_RenderDeviceDrawMenuSprite(a2, a1, SpriteForChar, a5);
  if ( v6 )
    return Render_Present((int)g_RenderState);
  return result;
}
// 42177B: variable 'v7' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00421830) --------------------------------------------------------
int  Castle_DrawAmbientAnimationLayer(int a1)
{
  int result; // eax
  char v4; // dh
  char v5; // ch

  switch ( a1 )
  {
    case 1:
      result = g_SelectedBuildingRecord;
      v4 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (v4 & 4) != 0 && (v4 & 1) != 0 )
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
      v5 = *(_BYTE *)(g_SelectedBuildingRecord + 416);
      if ( (v5 & 0x10) != 0 && (v5 & 8) != 0 )
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
  int v2; // eax
  int result; // eax

  for ( i = 1; i <= 10; ++i )
  {
    v2 = i;
    result = Castle_DrawAmbientAnimationLayer(v2);
  }
  return result;
}

//----- (00421C40) --------------------------------------------------------
unsigned int Castle_UpdateAmbientAnimationLayers()
{
  void *v1; // ebx
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
  unsigned int v16; // eax
  int v17; // ecx
  int v18; // edx
  unsigned int v19; // eax
  unsigned int v20; // ecx
  int v21; // ecx
  unsigned int v22; // eax
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
  unsigned int v34; // eax
  int v35; // ecx
  int v36; // edx
  unsigned int v37; // ecx
  unsigned int v38; // eax
  int v39; // edx
  unsigned int v40; // eax
  int v41; // ecx
  unsigned int result; // eax
  int v43; // edx
  int v44; // edx
  unsigned int v45; // ecx
  int v46; // edx
  int v47; // ecx

  v1 = g_RenderDevice;
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
        v16 = Rng_RandRange(0, v15);
        g_CastleAmbientLayer3_NextDueTick = v16 + v17;
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
        v22 = Rng_RandRange(500, 2000);
        g_CastleAmbientLayer5_NextDueTick = v22 + v23;
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
        v34 = Rng_RandRange(500, v33);
        v31 = v34 + v35;
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
        v40 = Rng_RandRange(500, v39);
        v37 = v40 + v41;
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
    g_RenderDevice = v1;
  }
  else
  {
    g_RenderDevice = v1;
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
int * Castle_RebuildSceneBuffers(int a1, DWORD a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char castleSpriteName[20]; // [esp-6h] [ebp-1Ch] BYREF
  int savedArg; // [esp+Eh] [ebp-8h]
  unsigned int primary_surface_handle;

  savedArg = a1;
  Castle_RenderCompositeSceneLayers(g_PrimaryRenderSurface, 0, g_SelectedBuildingRecord, 0);
  strcpy(castleSpriteName, "zamek_1");
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  Palette_LoadOrBuildBlendLookupTable(castleSpriteName, (int)g_CastleScreenPaletteBuffer, v3, a2);
  Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v4, 0, a2);
  Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v5, 0, a2);
  Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v6, 0, a2);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Castle_DrawStatusPanel();
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_CastleScreenPaletteBuffer, 0, a2);
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
int * Castle_OpenManagementScreen(DWORD a1, char a2)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  _DWORD *v8; // eax
  int v9; // ecx
  char *v10; // esi
  char *v11; // edi
  char v12; // al
  char v13; // al
  _DWORD *v14; // eax
  int v15; // ecx
  _DWORD *v16; // eax
  int v17; // ecx
  _DWORD *Surface; // eax
  DWORD v19; // ebp
  int v20; // edx
  int v21; // ecx
  char *v22; // ebx
  int v23; // esi
  int v24; // edx
  int v25; // ecx
  _DWORD *v26; // eax
  char v27; // bl
  int v28; // ecx
  int v29; // ecx
  int *result; // eax
  int v31; // ecx
  int v32; // ecx
  int v34; // ecx
  int v36; // edx
  int v37; // ecx
  _DWORD *v38; // eax
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int v44; // eax
  char v45[20]; // [esp+0h] [ebp-38h] BYREF
  int v46; // [esp+14h] [ebp-24h]
  int (*v47)(); // [esp+18h] [ebp-20h]
  int v48; // [esp+1Ch] [ebp-1Ch]
  CastleManagementPanelCallback castle_panel_callback;
  int castle_loop_iterations;

  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] open_enter building_idx=%u current_player=%d\n", (unsigned int)a1, g_CurrentPlayerIndex);
  Diagnostics_ResetFrameDumpOnCastleEnter();
  v48 = Render_SetResourceHandle((int)&g_MainRenderDevice, (char *)Castle_RebuildSceneBuffers == (char *)Render_DefaultRH);
  v47 = g_RenderHook;
  g_RenderHook = (int (*)())Castle_RebuildSceneBuffers;
  Debug_Log(v4, a2, a1, (int)aSetrhS08x_6);
  TextSprite_ReleaseAllResourceSlots();
  BuildingSpriteCache_Clear();
  UnitSpriteCache_FreeAllEntries(v5, a1);
  CSS_EmptySampleCache();
  Debug_Log(BUILDING_RECORD_SIZE * a1, a2, a1, (int)aCastleD);
  g_SelectedBuildingRecord = BUILDING_RECORD(a1);
  g_ActiveCastleOwnerIsChristian = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(g_SelectedBuildingRecord + 2));
  v46 = Audio_PauseMusicAndPlayLoopedSound(aCastle, *(unsigned __int8 *)(g_SelectedBuildingRecord + 2) + 1);
  CSS_PauseStreamReading();
  Castle_UpdateGateToggles();
  strcpy(v45, "zamek_1\\z_iko.s32");
  v45[6] = g_CurrentPlayerIndex + 49;
  v8 = (_DWORD *)Mem_Alloc(4112, v7, a2, a1);
  if ( v8 )
    v8 = DLXSpriteSet_Load(v8, v45);
  v10 = aZamek_1Anim_s3;
  v11 = v45;
  g_CastleSceneIconSpriteSet = (int)v8;
  do
  {
    v12 = *v10;
    *v11 = *v10;
    if ( !v12 )
      break;
    v13 = v10[1];
    v10 += 2;
    v11[1] = v13;
    v11 += 2;
  }
  while ( v13 );
  v45[6] = g_CurrentPlayerIndex + 49;
  v14 = (_DWORD *)Mem_Alloc(4112, v9, a2, a1);
  if ( v14 )
    v14 = DLXSpriteSet_Load(v14, v45);
  g_CastleAmbientSpriteSet = (int)v14;
  v16 = (_DWORD *)Mem_Alloc(4112, v15, a2, a1);
  if ( v16 )
    v16 = DLXSpriteSet_Load(v16, aDz_info_s32);
  g_CastleStatusSpriteSet = (int)v16;
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v17, a2, a1);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  v19 = BUILDING_RECORD_SIZE * a1;
  g_CastleScreenSurface = (int)Surface;
  Castle_RebuildSceneBuffers((int)g_CastleScreenPaletteBuffer, v19);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 3, (int)g_CastleScreenPaletteBuffer, aMap_pal_0);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 4, (int)g_CastleScreenPaletteBuffer, aMap_pal_1);
  DLXSpriteSet_DrawText(g_CastleStatusSpriteSet, 10, (int)g_CastleScreenPaletteBuffer, (unsigned __int8 *)g_MapPalettePtr);
  CSS_ResumeStreamReading();
  LOBYTE(v22) = -57;
  Tooltip_CaptureBackdrop(190, 455, 7, 455, 248);
  Render_Present((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] first_present building_idx=%u\n", (unsigned int)a1);
  Diagnostics_TraceCastleHotspots(g_CastleScreenSurface);
  g_CastleDestroyConfirmed = 0;
  g_CastleScreenExitRequested = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  v23 = 0;
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
    UIWidgetTable_PollHoverAndActions((_DWORD *)g_CastleStatusWidgetRecord, v19);
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
        if ( v23 != 134 )
        {
          v23 = 134;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames[(unsigned __int8)g_LanguageIndex], v45[0]);
        }
        break;
      case 250:
        castle_panel_callback = Building_ShowGateDoorDialog_v3;
        if ( v23 != 153 )
        {
          v22 = UI_Locale_BuildingNames_J[(unsigned __int8)g_LanguageIndex];
          v23 = 153;
          Tooltip_ShowText(3, v22, v45[0]);
        }
        break;
      case 251:
        castle_panel_callback = Building_ShowGateDoorDialog_v1;
        if ( v23 != 156 )
        {
          v23 = 156;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_L[(unsigned __int8)g_LanguageIndex], v45[0]);
        }
        break;
      case 252:
        castle_panel_callback = Building_ShowGateDoorDialog_v4;
        if ( v23 != 159 )
        {
          v23 = 159;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_K[(unsigned __int8)g_LanguageIndex], v45[0]);
        }
        break;
      case 253:
        castle_panel_callback = Building_ShowGateDoorDialog_v2;
        if ( v23 != 166 )
        {
          v23 = 166;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_M[(unsigned __int8)g_LanguageIndex], v45[0]);
        }
        break;
      case 254:
        castle_panel_callback = BuildingGarrisonDialog_Run;
        if ( v23 != 99 )
        {
          if ( (*(_BYTE *)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
            v44 = 3;
          else
            v44 = 8;
          v22 = (&g_CastleBuildingIconTooltipNames[3 * v44])[(unsigned __int8)g_LanguageIndex];
          v23 = 99;
          Tooltip_ShowText(3, v22, v45[0]);
        }
        break;
      case 255:
        castle_panel_callback = Castle_InvokeEconomyPanel;
        if ( v23 != 135 )
        {
          v23 = 135;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames_FromPeasants[(unsigned __int8)g_LanguageIndex], v45[0]);
        }
        break;
      default:
        if ( v23 )
          Tooltip_RestoreBackdrop();
        v23 = 0;
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
      v36 = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
      v22 = (char *)g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(v34, (char)v22, v19, (int)aSetrhS08x_7);
      castle_panel_callback(g_SelectedBuildingRecord, 0, v19);
      Debug_Log((int)g_RenderHook, (char)v22, v19, (int)aUnsetrh08x_7);
      g_RenderHook = (int (*)())v22;
      Render_SetResourceHandle((int)&g_MainRenderDevice, v36);
      v38 = (_DWORD *)Mem_Alloc(188, v37, (char)v22, v19);
      if ( v38 )
      {
        LOBYTE(v22) = -32;
        v38 = Render_CreateSurface((int)v38, SCREEN_WIDTH, SCREEN_HEIGHT);
      }
      g_CastleScreenSurface = (int)v38;
      Castle_RebuildSceneBuffers(v39, v19);
      g_RenderDevice = (_UNKNOWN *)g_CastleScreenSurface;
      RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_CastleScreenPaletteBuffer, v40, v19);
      Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v41, (char)v22, v19);
      Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v42, (char)v22, v19);
      Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v43, (char)v22, v19);
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
      Render_Present((int)g_RenderState);
    }
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[castle] open_exit building_idx=%u loops=%d esc=%d exit_requested=%d\n",
      (unsigned int)a1,
      castle_loop_iterations,
      Input_IsKeyPressed(1),
      g_CastleScreenExitRequested);
  Render_Pump();
  RenderState_LoadDefaultCursorSprite((int)g_RenderState);
  Audio_SetMusicVolume(v24, 400);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  DLXSpriteSet_ReleaseAndClear(&g_MapPanelSpriteSet);
  v26 = (_DWORD *)Mem_Alloc(4112, v25, 144, v19);
  if ( v26 )
    v26 = DLXSpriteSet_Load(v26, "menu.s32");
  v27 = g_CastleScreenSurface;
  g_MapPanelSpriteSet = (int)v26;
  if ( g_CastleScreenSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface, 2);
  DLXSpriteSet_ReleaseAndClear(&g_CastleSceneIconSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleAmbientSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleStatusSpriteSet);
  TextSprite_ReleaseAllResourceSlots();
  CSS_EmptySampleCache();
  Palette_LoadOrBuildBlendLookupTable(aMainmap_2, g_MapPalettePtr, v28, v19);
  Audio_ResumeMusicAndStopLoopedSound(v46);
  Debug_Log(v29, v27, v19, (int)aUnsetrh08x_6);
  g_RenderHook = v47;
  Render_SetResourceHandle((int)&g_MainRenderDevice, v48);
  Diagnostics_ResetFrameDumpOnCastleReturn();
  result = WorldMap_RenderHook(v19);
  if ( g_CastleDestroyConfirmed )
    return (int *)Win_PlayModeChangeFrameTransition(aZniszcze, 1, v31, v27, v19);
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
int  Tooltip_CaptureBackdrop(int a1, int a2, int a3, int a4, int a5)
{
  int v5; // edi
  int i; // esi
  _DWORD *Surface; // eax
  int result; // eax

  v5 = a4;
  Render_ReleaseSurface(a3, a3);
  for ( i = a4 + UI_GetTextXOffset(a3); i >= (unsigned __int16)g_RenderDeviceClipRightX; --i )
    --v5;
  if ( g_TooltipBackdropSurface )
    Compat_InvokeCompactSurfaceDestructor(g_TooltipBackdropSurface, 2);
  Surface = (_DWORD *)Mem_Alloc(188, 0, (char)a4, a3);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, a2 - a1 + 1, i - v5 + 1);
  g_TooltipBackdropSurface = (int)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v5, (unsigned __int16)a1, a2, i, 0, 0);
  g_TooltipLeft = v5;
  g_TooltipTop = a1;
  g_TooltipRight = i;
  g_TooltipBottom = a2;
  result = a5;
  g_TooltipResourceHandle = a3;
  g_TooltipCaptureArg5 = a5;
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
void * Tooltip_ShowText(int a1, char *a2, ...)
{
  int v3; // ebp
  char *v4; // edi
  char *v5; // esi
  char v6; // al
  char v7; // al
  void *result; // eax
  void *v9; // [esp+0h] [ebp-20h]
  va_list args;

  v9 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  v3 = g_ActiveTextSpriteSlot;
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
  Render_ReleaseSurface(g_TooltipResourceHandle, v3);
  va_start(args, a2);
  UI_DrawTextFmtV(g_TooltipTop, g_TooltipBottom, a1, g_TooltipLeft, a2, args);
  va_end(args);
  v4 = (char *)&g_TooltipTextBuffer;
  Render_Present((int)g_RenderState);
  v5 = a2;
  do
  {
    v6 = *v5;
    *v4 = *v5;
    if ( !v6 )
      break;
    v7 = v5[1];
    v5 += 2;
    v4[1] = v7;
    v4 += 2;
  }
  while ( v7 );
  Render_ReleaseSurface(v3, v3);
  result = v9;
  g_RenderDevice = v9;
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
  int v2; // edx
  int v3; // eax
  int *slotListPtr; // ebx
  void *v5; // ecx
  int v6; // ecx
  int ownerIndex; // eax
  int SpriteForChar; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int neighbor_row; // eax
  int neighbor_column; // ebp
  int selectedSlotList[11]; // [esp+44h] [ebp-4Ch] BYREF
  int j; // [esp+70h] [ebp-20h]
  int i; // [esp+74h] [ebp-1Ch]

  if ( g_UnitStackSelectionActiveUnitIndex != -1 )
  {
    if ( result == -1 )
    {
      v2 = g_SelectedUnitIndex;
      v3 = 8 * g_SelectedUnitIndex;
    }
    else
    {
      v2 = result;
      v3 = 8 * result;
    }
    g_SelectedUnitStackRecordPtr = 5 * (v2 + 16 * (v2 + v3)) + gameData + UNIT_STACK_TABLE_OFFSET;
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
      v10 = DLX_GetSpriteForChar(g_CurrentPlayerInfoSpriteSet, *(__int16 *)(31 * j + g_SelectedUnitStackRecordPtr + 6));
      Compat_RenderDeviceDrawMenuSprite(401, 38 * j + 35, v10, 1);
      if ( (*(_BYTE *)(g_SelectedUnitStackRecordPtr + 31 * j + 19) & 4) != 0 )
      {
        v11 = DLX_GetSpriteForChar(g_MarksSpriteSet, 33);
        Compat_RenderDeviceDrawMenuSprite(405, 38 * j + 40, v11, 1);
      }
      Render_ReleaseSurface(7, a2);
      v9 = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 4) == g_CurrentPlayerIndex )
        UI_DrawTextFmt(j, 38 * j + 32, 38 * j + 70, 450, 3, (int)aD_5);
      if ( g_UnitStackSlotSelectedFlags[j] )
      {
        v12 = DLX_GetSpriteForChar(g_MarksSpriteSet, (*(unsigned __int8 *)(g_SelectedUnitStackRecordPtr + 31 * j + 14) >= 4u) + 4);
        Compat_RenderDeviceDrawMenuSprite(402, 38 * j + 58, v12, 1);
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
int  UnitStack_ShowSelectionDialog(int a1, int a2)
{
  _BYTE v4[40]; // [esp+0h] [ebp-48h] BYREF
  int v5; // [esp+28h] [ebp-20h]
  int v6; // [esp+2Ch] [ebp-1Ch]
  int v7; // [esp+30h] [ebp-18h]

  v7 = g_UnitStackSelectionActiveUnitIndex;
  v6 = g_UnitStackSelectionModeActive;
  v5 = g_SelectedUnitStackRecordPtr;
  qmemcpy(v4, g_UnitStackSlotSelectedFlags, sizeof(v4));
  g_UnitStackSelectionModeActive = 1;
  g_UnitStackSelectionActiveUnitIndex = a1;
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(a1, a1);
  WorldMap_RedrawViewport(1);
  while ( DD_IsLost((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, a2);
    WorldMap_HandleScrollKeysAndIdle(a1);
    WorldMap_RedrawFrame(a2);
  }
  g_UnitStackSelectionModeActive = v6;
  g_UnitStackSelectionActiveUnitIndex = v7;
  g_SelectedUnitStackRecordPtr = v5;
  qmemcpy(g_UnitStackSlotSelectedFlags, v4, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(-1, a1);
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
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int roadTileId; // eax
  BOOL result; // eax

  neighborBuildingMarker = *(unsigned __int16 *)(gameData + 200 * row + 2 * column + 556370);
  result = 1;
  if ( neighborBuildingMarker < 0x8000
    || neighborBuildingMarker > 65534
    || (neighborBuildingPtr = (unsigned __int8 *)(BUILDING_RECORD_SIZE * (neighborBuildingMarker - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET), v6 = (char)neighborBuildingPtr[4], v6 != 2) && v6 != 1
    || (v7 = *neighborBuildingPtr, v7 != row)
    || (v8 = row ^ v7, LOBYTE(v8) = neighborBuildingPtr[1], v8 != column - 2) )
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
  int v3; // esi
  int v4; // ecx
  int v5; // esi
  int v6; // ecx
  int v7; // esi
  int v8; // ecx
  int overlaySprite; // edx
  int v10; // ecx
  int v11; // ecx
  int result; // eax

  v3 = 8 * MapTile_HasWestRoadConnection(row, column);
  v5 = (4 * MapTile_HasSouthRoadConnection(row, v4)) | v3;
  v7 = (2 * MapTile_HasEastRoadConnection(row, v6)) | v5;
  overlaySprite = g_RoadOverlaySpriteByConnectionMask[v7 | MapTile_HasNorthRoadConnection(row, v8)];
  v11 = 14 * v10;
  result = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  if ( overlaySprite )
    *(_WORD *)(v11 + result + 4) = overlaySprite;
  else
    *(_WORD *)(v11 + result + 4) = -1;
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
signed int  Road_Build(int a1, int a2, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int v6; // eax
  BOOL v7; // ebx
  BOOL v8; // edi
  BOOL v9; // eax
  int v10; // ecx
  int v11; // esi
  int v12; // ebp
  __int16 v13; // di
  unsigned __int16 *v14; // edx
  int v15; // eax
  unsigned __int16 v16; // ax
  int v17; // eax
  int v18; // eax
  signed int result; // eax
  signed int v20; // eax
  signed int v21; // edx
  unsigned __int16 v22; // di
  int v23; // ecx
  int v24; // ebx
  DWORD v25; // ebp
  int v26; // ebx
  int v27; // edx
  int v28; // [esp-4h] [ebp-44h]
  int v29; // [esp+8h] [ebp-38h]
  int v30; // [esp+Ch] [ebp-34h]
  signed int v31; // [esp+10h] [ebp-30h]
  int v32; // [esp+14h] [ebp-2Ch]
  int v34; // [esp+1Ch] [ebp-24h]
  int v36; // [esp+24h] [ebp-1Ch]
  int v37; // [esp+28h] [ebp-18h]

  Debug_Log(a1, a3, a4, (int)aRoad_buildDD);
  v6 = gameData + UNIT_STACK_STRIDE * v5;
  v29 = *(__int16 *)(v6 + 147174);
  v37 = *(__int16 *)(v6 + 147176);
  v7 = MapTile_HasNorthRoadConnection(v29, v37);
  v8 = MapTile_HasSouthRoadConnection(v29, v37);
  MapTile_HasWestRoadConnection(v29, v37);
  v9 = MapTile_HasEastRoadConnection(v29, v37);
  switch ( a2 )
  {
    case 0:
      v11 = v29;
      v12 = v37 - 1;
      if ( !v9 && v7 && !v8 )
      {
        v13 = 876;
        goto LABEL_14;
      }
      if ( !v9 && !v7 && v8 )
      {
        v13 = 874;
        goto LABEL_14;
      }
      if ( !v9 && v7 && v8 )
        goto LABEL_40;
      if ( v9 && v7 && !v8 )
        goto LABEL_41;
      if ( v9 && !v7 && v8 )
      {
        v13 = 871;
        goto LABEL_14;
      }
      if ( !v9 || !v7 || !v8 )
        goto LABEL_44;
      goto LABEL_13;
    case 2:
      v12 = v37;
      v11 = v29 + 1;
      if ( !v7 && v10 && !v9 )
      {
        v13 = 874;
        goto LABEL_14;
      }
      if ( !v7 && !v10 && v9 )
      {
        v13 = 868;
        goto LABEL_14;
      }
      if ( !v7 && v10 && v9 )
      {
        v13 = 871;
        goto LABEL_14;
      }
      if ( v7 && v10 && !v9 )
        goto LABEL_40;
      if ( v7 && !v10 && v9 )
      {
        v13 = 869;
        goto LABEL_14;
      }
      if ( v7 && v10 && v9 )
        goto LABEL_13;
      goto LABEL_68;
    case 4:
      v11 = v29;
      v12 = v37 + 1;
      if ( !v10 && v7 && !v8 )
      {
        v13 = 870;
        goto LABEL_14;
      }
      if ( !v10 && !v7 && v8 )
      {
        v13 = 868;
        goto LABEL_14;
      }
      if ( !v10 && v7 && v8 )
      {
        v13 = 869;
        goto LABEL_14;
      }
      if ( v10 && v7 && !v8 )
      {
LABEL_41:
        v13 = 873;
        goto LABEL_14;
      }
      if ( v10 && !v7 && v8 )
      {
        v13 = 871;
        goto LABEL_14;
      }
      if ( !v10 || !v7 || !v8 )
      {
LABEL_44:
        v13 = 866;
        goto LABEL_14;
      }
      goto LABEL_13;
    case 6:
      v12 = v37;
      v11 = v29 - 1;
      if ( v8 || !v10 || v9 )
      {
        if ( v8 || v10 || !v9 )
        {
          if ( !v8 && v10 && v9 )
          {
            v13 = 873;
          }
          else if ( v8 && v10 && !v9 )
          {
LABEL_40:
            v13 = 875;
          }
          else if ( v8 && !v10 && v9 )
          {
            v13 = 869;
          }
          else if ( v8 && v10 && v9 )
          {
LABEL_13:
            v13 = 872;
          }
          else
          {
LABEL_68:
            v13 = 867;
          }
        }
        else
        {
          v13 = 870;
        }
      }
      else
      {
        v13 = 876;
      }
LABEL_14:
      v14 = (unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * v29 + TILE_TERRAIN_RECORD_STRIDE * v37);
      HIWORD(v15) = 0;
      if ( *v14 >= 0x25Bu )
      {
        LOWORD(v15) = *v14;
        if ( v15 <= 642 )
          v13 = v14[2];
      }
      v34 = 0;
      v32 = 0;
      if ( MapTile_HasAlignedBridgeApproachRoadOverlay(v29, v37, v12, v11) )
      {
        v16 = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * v11 + gameData + TILE_TERRAIN_RECORD_STRIDE * v12 + 2);
        if ( v16 >= 0x236u )
        {
          if ( v16 <= 0x236u )
          {
            v36 = 877;
          }
          else if ( v16 >= 0x240u )
          {
            if ( v16 <= 0x240u )
            {
              v36 = 904;
            }
            else if ( v16 >= 0x243u )
            {
              if ( v16 <= 0x243u )
              {
                v36 = 903;
              }
              else if ( v16 == 581 )
              {
                v36 = 906;
              }
            }
            else if ( v16 == 578 )
            {
              v36 = 901;
            }
          }
          else if ( v16 <= 0x237u )
          {
            v36 = 879;
          }
          else if ( v16 == 569 )
          {
            v36 = 882;
          }
        }
        else if ( v16 >= 0x223u )
        {
          if ( v16 <= 0x223u )
          {
            v36 = 927;
          }
          else if ( v16 >= 0x225u )
          {
            if ( v16 <= 0x225u )
            {
              v36 = 930;
            }
            else if ( v16 == 564 )
            {
              v36 = 880;
            }
          }
        }
        else if ( v16 >= 0x220u )
        {
          if ( v16 <= 0x220u )
          {
            v36 = 928;
          }
          else if ( v16 == 546 )
          {
            v36 = 925;
          }
        }
        v17 = gameData + TILE_TERRAIN_ROW_STRIDE * v11 + TILE_TERRAIN_RECORD_STRIDE * v12;
        v32 = *(unsigned __int16 *)(v17 + 4);
        v34 = v36;
        *(_WORD *)(v17 + 4) = v36;
        *(_DWORD *)(TILE_TERRAIN_ROW_STRIDE * v11 + gameData + TILE_TERRAIN_RECORD_STRIDE * v12 + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
      }
      if ( MapTile_IsBareBridgeCrossingRoadOverlayCandidate(v11, v12) )
      {
        if ( !a2 || a2 == 4 )
        {
          v30 = 881;
        }
        else if ( a2 == 6 || a2 == 2 )
        {
          v30 = 878;
        }
        v18 = gameData + TILE_TERRAIN_ROW_STRIDE * v11 + TILE_TERRAIN_RECORD_STRIDE * v12;
        v32 = *(unsigned __int16 *)(v18 + 4);
        v34 = v30;
        *(_WORD *)(v18 + 4) = v30;
        *(_DWORD *)(TILE_TERRAIN_RECORD_STRIDE * v12 + TILE_TERRAIN_ROW_STRIDE * v11 + gameData + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
        v13 = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * v29 + gameData + TILE_TERRAIN_RECORD_STRIDE * v37 + 4);
      }
      v31 = UnitStack_GetTileMoveCostOrZero((__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1), v11, 145 * a1, v12);
      if ( MapTile_IsCastleFoundationTile(v11, v12, 2) )
        v31 = 0;
      if ( v32 )
        *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * v11 + TILE_TERRAIN_RECORD_STRIDE * v12 + 4) = v32;
      result = v31;
      if ( v31 )
      {
        v20 = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( v20 >= v21 )
        {
          if ( Map_GetTileSurfaceClassOrUnexplored(v29, v37) == 185
            || Map_GetTileSurfaceClassOrUnexplored(v11, v12) == 185 )
          {
            return 0;
          }
          else
          {
            *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * v29 + TILE_TERRAIN_RECORD_STRIDE * v37 + 4) = v13;
            v22 = *(_WORD *)(TILE_TERRAIN_ROW_STRIDE * v11 + gameData + TILE_TERRAIN_RECORD_STRIDE * v12 + 4);
            Map_RebuildRoadOverlayAtTile(v11, v12);
            if ( v22 != 0xFFFF )
            {
              v24 = v23 + gameData + 14 * v12;
              if ( *(unsigned __int16 *)(v24 + 4) == 0xFFFF )
                *(_WORD *)(v24 + 4) = v22;
            }
            if ( v34 )
            {
              *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * v11 + TILE_TERRAIN_RECORD_STRIDE * v12 + 4) = v34;
            }
            else
            {
              MapTile_HasNorthRoadConnection(v11, v12);
              MapTile_HasSouthRoadConnection(v11, v12);
              MapTile_HasWestRoadConnection(v11, v12);
              MapTile_HasEastRoadConnection(v11, v12);
            }
            g_SelectedUnitIndex = a1;
            v28 = v12;
            v25 = UNIT_STACK_STRIDE * a1;
            v26 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + 147176);
            result = (signed int)Unit_MoveTrack(a1, *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + UNIT_STACK_TABLE_OFFSET), v11, v26, UNIT_STACK_STRIDE * a1, v28);
            if ( result )
            {
              qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + v25 + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
              j__nfree_();
              UnitStack_ExecuteQueuedPath(a1, v27, v26, v25, a5);
              UnitStack_SpendActionPointsClamped((__int16 *)(v25 + gameData + UNIT_STACK_TABLE_OFFSET), 1, v25, a5);
              WorldMap_RefreshUnitStatusPanel(v25);
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
signed int  UnitStack_MoveOneTileInDirection(int a1, int a2, double a3)
{
  int v5; // esi
  int v6; // edx
  int v7; // ebx
  signed int result; // eax
  int v9; // edx

  g_SelectedUnitIndex = a1;
  v5 = UNIT_STACK_STRIDE * a1;
  v6 = gameData + UNIT_STACK_STRIDE * a1;
  v7 = *(__int16 *)(v6 + 147176);
  result = (signed int)Unit_MoveTrack(
                         a1,
                         *(__int16 *)(v6 + 147174),
                         *(__int16 *)(v6 + 147174) + Map_NeighborDX[2 * a2],
                         v7,
                         a1,
                         v7 + Map_NeighborDY[2 * a2]);
  if ( result )
  {
    qmemcpy((void *)(v5 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(a1, v9, v7, a1, a3);
    WorldMap_RefreshUnitStatusPanel(a1);
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
BOOL  Map_TileHasOwner(int a1, int a2)
{
  return *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * a1 + TILE_TERRAIN_RECORD_STRIDE * a2 + 4) != 0xFFFF;
}
// 5202E4: using guessed type int gameData;

//----- (00424FD0) --------------------------------------------------------
int Map_AutoUpgradeVillages()
{
  int result; // eax
  int v1; // esi
  int v2; // edx
  int v3; // ebx
  int v4; // ecx
  int v5; // [esp+4h] [ebp-2Ch]
  int i; // [esp+8h] [ebp-28h]
  int v7; // [esp+Ch] [ebp-24h]

  v5 = 0;
  v7 = 0;
  for ( i = 0; ; i += 200 )
  {
    result = gameData;
    if ( v5 >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    v1 = 0;
    v2 = 0;
    v3 = 0;
    while ( v1 < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      if ( *(unsigned __int16 *)(v2 + v7 + gameData + 4) >= 0x36Du
        && *(unsigned __int16 *)(v2 + v7 + gameData + 4) <= 0x37Eu
        || *(unsigned __int16 *)(v2 + v7 + gameData + 4) >= 0x385u
        && *(unsigned __int16 *)(v2 + v7 + gameData + 4) <= 0x396u
        || *(unsigned __int16 *)(v2 + v7 + gameData + 4) >= 0x39Du
        && *(unsigned __int16 *)(v2 + v7 + gameData + 4) <= 0x3AEu )
      {
        v4 = v2 + gameData + v7;
        if ( *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) >= (unsigned int)(*(_DWORD *)(v4 + 10) + 30)
          && *(unsigned __int16 *)(v3 + i + gameData + TILE_MAP_OFFSET) == 0xFFFF )
        {
          *(_WORD *)(v4 + 4) += 6;
          *(_DWORD *)(v2 + v7 + gameData + 10) = *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
        }
      }
      v2 += 14;
      v3 += 2;
      ++v1;
    }
    v7 += 1400;
    ++v5;
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
int  RoadBuildMode_HighlightBuildableAdjacentTile(int a1, int a2)
{
  int v4; // eax
  int v5; // eax
  int v6; // ebp
  int v7; // ecx
  int result; // eax
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx

  v4 = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
  if ( a1 == *(__int16 *)(v4 + 147174) && a2 - *(__int16 *)(v4 + 147176) == -1 )
  {
    v5 = (a2 - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
    g_RoadBuildModeNorthMarkerX = ((a1 - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
    v6 = 0;
    g_RoadBuildModeNorthMarkerY = v5 + 59 - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
  }
  else
  {
    v9 = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
    if ( a1 - *(__int16 *)(v9 + 147174) == 1 && a2 == *(__int16 *)(v9 + 147176) )
    {
      v6 = 1;
      v10 = ((a1 - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
          + 42
          - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
      g_RoadBuildModeEastMarkerY = ((a2 - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 41;
      g_RoadBuildModeEastMarkerX = v10;
    }
    else
    {
      v11 = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
      if ( a1 == *(__int16 *)(v11 + 147174) && a2 - *(__int16 *)(v11 + 147176) == 1 )
      {
        v12 = (a2 - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeSouthMarkerX = ((a1 - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
        v6 = 2;
        g_RoadBuildModeSouthMarkerY = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex] + v12 + 26;
      }
      else
      {
        result = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
        if ( a1 - *(__int16 *)(result + 147174) != -1 )
          return result;
        result = *(__int16 *)(result + 147176);
        if ( a2 != result )
          return result;
        v6 = 3;
        v13 = (a2 - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeWestMarkerX = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex]
                     + ((a1 - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
                     + 75;
        g_RoadBuildModeWestMarkerY = v13 + 41;
      }
    }
  }
  if ( (MapTile_HasAlignedBridgeApproachRoadOverlay(
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
          a2,
          a1)
     || MapTile_IsBareBridgeCrossingRoadOverlayCandidate(a1, a2))
    && UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) >= 6
    || (result = UnitStack_GetTileMoveCostOrZero((__int16 *)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), a1, gameData, a2)) != 0
    && (result = MapTile_IsCastleFoundationTile(a1, a2, 2)) == 0
    && (result = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), result >= v14)
    && (result = Map_GetTileSurfaceClassOrUnexplored(a1, a2), result != 185) )
  {
    g_RoadBuildModeHasBuildTarget = 1;
    return UIWidget_RefreshActionButtonState((int)&g_RoadBuildModeNorthMarkerX + 53 * v6, v7);
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
int  RoadBuildMode_BuildInSelectedDirection(int a1, DWORD a2, double a3)
{
  int v4; // edx
  int v5; // ecx

  UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a1);
  switch ( *(_DWORD *)(v5 + 16) )
  {
    case 0x1B:
      v4 = 0;
      break;
    case 0x1C:
      v4 = 2;
      break;
    case 0x1D:
      v4 = 4;
      break;
    case 0x1E:
      v4 = 6;
      break;
    default:
      break;
  }
  g_WorldMapTileOverlayDrawHook = 0;
  Road_Build(g_SelectedUnitIndex, v4, (char)RoadBuildMode_HighlightBuildableAdjacentTile, a2, a3);
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
  int v10; // esi
  int v11; // eax
  int *v12; // edx

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
          v10 = UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData;
          v4 = (((g_MouseCursorRawX >> g_CursorCoordShift)
               - 32
               - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
                + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
             + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)
             - *(__int16 *)(v10 + 147174);
          v11 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
              + (((g_MouseCursorRawY >> g_CursorCoordShift)
                - 16
                - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                 + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
              - *(__int16 *)(v10 + 147176);
          v12 = 0;
          if ( v4 || v11 != -1 )
          {
            if ( v4 != 1 || v11 )
            {
              if ( v4 || v11 != 1 )
              {
                if ( v4 == -1 && !v11 )
                  v12 = &g_RoadBuildModeWestMarkerX;
              }
              else
              {
                v12 = &g_RoadBuildModeSouthMarkerX;
              }
            }
            else
            {
              v12 = &g_RoadBuildModeEastMarkerX;
            }
          }
          else
          {
            v12 = &g_RoadBuildModeNorthMarkerX;
          }
          if ( v12 )
          {
            v12[2] = 2;
            RoadBuildMode_BuildInSelectedDirection((int)v12, a1, a2);
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
  int v0; // edx
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int result; // eax
  int v8; // [esp+0h] [ebp-14h]
  int v9; // [esp+4h] [ebp-10h]
  int v10; // [esp+8h] [ebp-Ch]

  v9 = 0;
  v8 = 0;
  v10 = 0;
  while ( v9 < *(_DWORD *)(g_MapData + 804) )
  {
    v0 = v10;
    v1 = 0;
    v2 = 0;
    v3 = v10;
    while ( v1 < *(_DWORD *)(g_MapData + 800) )
    {
      v4 = *(__int16 *)(v2 + v8 + g_MapData);
      if ( v4 == 313
        || v4 >= 315 && v4 <= 320
        || v4 == 322
        || v4 == 325
        || v4 >= 328 && v4 <= 329
        || v4 >= 338 && v4 <= 341
        || v4 >= 344 && v4 <= 352
        || v4 == 356 )
      {
        g_TilePassabilityMask[v3] = 0;
      }
      else
      {
        g_TilePassabilityMask[v0] = *(_BYTE *)(g_MapData + 816);
      }
      v2 += 2;
      ++v0;
      ++v3;
      ++v1;
    }
    v8 += 40;
    v10 += 32;
    ++v9;
  }
  v5 = 0;
  v6 = 0;
  do
  {
    ++v5;
    result = g_UnitTypeFlags[v6] & 1;
    v6 += 22;
    g_UnitTypeBattleMoveFlagsMinus1[v5] = result;
  }
  while ( v5 < 40 );
  return result;
}
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;

//----- (00425970) --------------------------------------------------------
signed int  UnitBattle_GetTileMoveCostOrZero(int a1, int a2, int a3)
{
  if ( !g_MapIgnoreUnitOccupancy && *(__int16 *)(40 * a2 + g_MapData + 2 * a3 + 1534) != -1 )
    return 0;
  if ( g_UnitTypeFlatMoveCostFlags[a1] )
    return 5;
  if ( *(_BYTE *)(g_MapData + 20 * a2 + a3 + 3134) )
    return 0;
  return (unsigned __int8)g_TilePassabilityMask[32 * a2 + a3];
}
// 531CB8: using guessed type int g_MapIgnoreUnitOccupancy;
// 532048: using guessed type int g_MapData;

//----- (00425A00) --------------------------------------------------------
int * UnitBattle_MoveTrack(int a1, int a2, int a3, int a4, DWORD a5)
{
  int v7; // ebx
  int i; // ecx
  unsigned int v9; // eax
  int v10; // edx
  int v11; // eax
  char v12; // bl
  int v13; // ebp
  int v14; // edi
  int v15; // eax
  int v16; // esi
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  unsigned __int16 v28; // dx
  int *v29; // eax
  unsigned __int8 v30; // dl
  int v31; // ecx
  int v32; // ebp
  int v33; // ecx
  int v34; // edi
  int v35; // esi
  int v36; // edx
  unsigned __int16 v37; // ax
  int v38; // ebx
  int v39; // eax
  int v40; // eax
  int v41; // ecx
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
  __int16 v55[401]; // [esp+2h] [ebp-396h]
  unsigned int v56; // [esp+324h] [ebp-74h]
  int v57; // [esp+328h] [ebp-70h]
  int v58; // [esp+32Ch] [ebp-6Ch]
  int v59; // [esp+330h] [ebp-68h]
  int v60; // [esp+334h] [ebp-64h]
  int v61; // [esp+338h] [ebp-60h]
  int v62; // [esp+33Ch] [ebp-5Ch]
  int v63; // [esp+340h] [ebp-58h]
  int v64; // [esp+344h] [ebp-54h]
  int *v65; // [esp+348h] [ebp-50h]
  int v66; // [esp+34Ch] [ebp-4Ch]
  int v67; // [esp+350h] [ebp-48h]
  int v68; // [esp+354h] [ebp-44h]
  int v69; // [esp+358h] [ebp-40h]
  int v70; // [esp+35Ch] [ebp-3Ch]
  int v71; // [esp+360h] [ebp-38h]
  int v72; // [esp+364h] [ebp-34h]
  int v73; // [esp+368h] [ebp-30h]
  int v74; // [esp+36Ch] [ebp-2Ch]
  unsigned int v75; // [esp+370h] [ebp-28h]
  int v76; // [esp+374h] [ebp-24h]
  int v77; // [esp+378h] [ebp-20h]
  int v78; // [esp+37Ch] [ebp-1Ch]
  unsigned __int8 v79; // [esp+380h] [ebp-18h]
  unsigned __int8 v80; // [esp+384h] [ebp-14h]

  v58 = a1;
  v59 = a2;
  v60 = a4;
  Debug_Log(a3, a1, a5, (int)aUnitbattle_m_0);
  v61 = *(__int16 *)(g_MapData + 31 * a1 + 852);
  v62 = *(unsigned __int16 *)(g_MapData + 31 * a1 + 856);
  v63 = *(unsigned __int16 *)(g_MapData + 31 * a1 + 858);
  if ( v59 < 0
    || v60 < 0
    || v59 >= *(_DWORD *)(g_MapData + 804)
    || v60 >= *(_DWORD *)(g_MapData + 800)
    || !UnitBattle_GetTileMoveCostOrZero(v61, v59, v60) )
  {
    return 0;
  }
  v7 = 40;
  for ( i = 0; i < 20; ++i )
  {
    v9 = 40 * i;
    do
    {
      v9 += 2;
      v55[v9 / 2] = -2;
    }
    while ( v9 != v7 );
    v7 += 40;
  }
  v10 = 40 * v62 + g_MapData;
  v11 = v10 + 2 * v63;
  LOWORD(v10) = *(_WORD *)(v11 + 1534);
  *(_WORD *)(v11 + 1534) = -1;
  v77 = v10;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836)
    && *(unsigned __int8 *)(31 * v58 + g_MapData + 854) == *(_DWORD *)(g_MapData + 840) )
  {
    UnitBattle_TemporarilyClearGateBlocker();
  }
  v12 = v62;
  v55[20 * v62 + 1 + v63] = 0;
  do
  {
    v13 = 0;
    v64 = 0;
    while ( v13 < *(_DWORD *)(g_MapData + 804) )
    {
      v14 = 0;
      v74 = 40 * v13;
      v75 = 40 * v13;
      while ( v14 < *(_DWORD *)(g_MapData + 800) )
      {
        i = v75;
        v15 = (unsigned __int16)v55[v75 / 2 + 1];
        if ( (unsigned __int16)v15 != 65534 && v15 != 0xFFFF )
        {
          v56 = 0;
          v57 = 2 * v14 + v74;
          do
          {
            v16 = v13 + Map_NeighborDX[v56 / 4];
            i = v14 + Map_NeighborDY[v56 / 4];
            if ( v16 >= 0 && v16 < *(_DWORD *)(g_MapData + 804) && i >= 0 && i < *(_DWORD *)(g_MapData + 800) )
            {
              LOWORD(v17) = UnitBattle_GetTileMoveCostOrZero(v61, v13 + Map_NeighborDX[v56 / 4], v14 + Map_NeighborDY[v56 / 4]);
              if ( (_WORD)v17 )
              {
                if ( v16 != v13 && i != v14 )
                {
                  v17 = (23 * (unsigned __int16)v17
                       - (__CFSHL__((23 * (unsigned __int16)v17) >> 31, 4)
                        + 16 * ((23 * (unsigned __int16)v17) >> 31))) >> 4;
                  if ( v16 - v13 == i - v14 )
                  {
                    if ( v16 <= v13 )
                      v19 = v13;
                    else
                      v19 = v16;
                    v66 = g_MapData + 20 * (v19 - 1) + 3134;
                    if ( i <= v14 )
                      v20 = v14;
                    else
                      v20 = i;
                    if ( *(_BYTE *)(v66 + v20) )
                      goto LABEL_30;
                    v21 = v16 <= v13 ? v13 : v16;
                    v73 = 20 * v21;
                    v67 = 20 * v21 + g_MapData + 3134;
                    v22 = i <= v14 ? v14 : i;
                    if ( *(_BYTE *)(v67 + v22 - 1) )
                      goto LABEL_30;
                  }
                  else
                  {
                    if ( v16 <= v13 )
                      v23 = v13;
                    else
                      v23 = v16;
                    v68 = g_MapData + 20 * (v23 - 1) + 3134;
                    if ( i <= v14 )
                      v24 = v14;
                    else
                      v24 = i;
                    if ( *(_BYTE *)(v68 + v24 - 1) )
                      goto LABEL_30;
                    v25 = v16 <= v13 ? v13 : v16;
                    v73 = 20 * v25;
                    v69 = 20 * v25 + g_MapData + 3134;
                    v26 = i <= v14 ? v14 : i;
                    if ( *(_BYTE *)(v69 + v26) )
                      goto LABEL_30;
                  }
                }
                v73 = *(unsigned __int16 *)((char *)&v55[1] + v57);
                v18 = 40 * v16 + 2 * i;
                i = *(unsigned __int16 *)((char *)&v55[1] + v18);
                if ( (unsigned __int16)i > (unsigned __int16)v17 + v73 )
                {
                  i = v57;
                  *(__int16 *)((char *)&v55[1] + v18) = *(__int16 *)((char *)&v55[1] + v57) + v17;
                  v64 = 1;
                }
              }
              else
              {
                i = 40 * v16 + 2 * i;
                *(__int16 *)((char *)&v55[1] + i) = -1;
              }
            }
LABEL_30:
            v56 += 8;
          }
          while ( v56 != 64 );
        }
        v12 = v75 + 2;
        ++v14;
        v75 += 2;
      }
      ++v13;
    }
  }
  while ( v64 );
  v27 = 2 * v60 + 40 * v59;
  v28 = *(__int16 *)((char *)&v55[1] + v27);
  v65 = 0;
  if ( v28 != 65534 )
  {
    LOWORD(v27) = *(__int16 *)((char *)&v55[1] + v27);
    v79 = v59;
    v76 = v27;
    v29 = (int *)Mem_Alloc(404, i, v12, 0);
    v80 = v60;
    if ( v29 )
      *v29 = 0;
    HIWORD(v70) = HIWORD(g_UnitMoveTrackPackedNodeScratch);
    LOBYTE(v70) = v79;
    v65 = v29;
    BYTE1(v70) = v80;
    v31 = *v29;
    HIWORD(v70) = v76;
    if ( v31 < 100 )
    {
      *v29 = v31 + 1;
      v29[v31 + 1] = v70;
    }
LABEL_73:
    if ( (_WORD)v76 )
    {
      v32 = -1;
      v78 = (unsigned __int16)v76;
      while ( 1 )
      {
        v33 = -1;
        do
        {
          v34 = v79;
          v35 = v79 + v32;
          if ( v35 < 0 )
            goto LABEL_84;
          if ( v35 >= *(_DWORD *)(g_MapData + 804) )
            goto LABEL_84;
          v36 = v80 + v33;
          if ( v36 < 0 )
            goto LABEL_84;
          if ( v36 >= *(_DWORD *)(g_MapData + 800) )
            goto LABEL_84;
          v73 = 40 * v35;
          if ( (unsigned __int16)v78 <= (unsigned __int16)v55[20 * v35 + 1 + v36] )
            goto LABEL_84;
          v37 = UnitBattle_GetTileMoveCostOrZero(v61, v79, v80);
          LOWORD(v38) = v37;
          if ( !v32 || !v33 )
            goto LABEL_82;
          v38 = (23 * v37 - (__CFSHL__((23 * v37) >> 31, 4) + 16 * ((23 * v37) >> 31))) >> 4;
          if ( v32 == v33 )
          {
            if ( v34 > v35 )
              v35 = v34;
            v45 = v80;
            v46 = g_MapData + 20 * (v35 - 1) + 3134;
            if ( v80 <= v80 + v33 )
              v45 = v80 + v33;
            if ( !*(_BYTE *)(v46 + v45) )
            {
              v47 = v79;
              if ( v79 <= v79 + v32 )
                v47 = v79 + v32;
              v48 = v80 + v33;
              v49 = 20 * v47 + g_MapData + 3134;
              if ( v80 <= v48 )
              {
                if ( *(_BYTE *)(v49 + v48 - 1) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(v49 + v80 - 1) )
              {
                goto LABEL_84;
              }
LABEL_82:
              v39 = 40 * (v32 + v79) + 2 * (v33 + v80);
              if ( *(unsigned __int16 *)((char *)&v55[1] + v39) == (unsigned __int16)v76 - (unsigned __int16)v38 )
              {
                v71 = v32;
                LOWORD(v39) = *(__int16 *)((char *)&v55[1] + v39);
                v72 = v33;
                v78 = v39;
              }
            }
          }
          else
          {
            if ( v34 > v35 )
              v35 = v34;
            v50 = v80;
            v51 = g_MapData + 20 * (v35 - 1) + 3134;
            if ( v80 <= v80 + v33 )
              v50 = v80 + v33;
            if ( !*(_BYTE *)(v51 + v50 - 1) )
            {
              v52 = v79;
              if ( v79 <= v79 + v32 )
                v52 = v79 + v32;
              v53 = v80 + v33;
              v54 = 20 * v52 + g_MapData + 3134;
              if ( v80 <= v53 )
              {
                if ( *(_BYTE *)(v54 + v53) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(v54 + v80) )
              {
                goto LABEL_84;
              }
              goto LABEL_82;
            }
          }
LABEL_84:
          ++v33;
        }
        while ( v33 <= 1 );
        if ( ++v32 > 1 )
        {
          v79 += v71;
          LOBYTE(v70) = v79;
          v40 = 2 * (unsigned __int8)(v72 + v80) + 40 * v79;
          LOWORD(v40) = *(__int16 *)((char *)&v55[1] + v40);
          v76 = v40;
          HIWORD(v70) = v40;
          v80 += v72;
          v41 = *v65;
          BYTE1(v70) = v80;
          if ( v41 < 100 )
          {
            v42 = v41;
            v43 = v41 + 1;
            v44 = v65;
            *v65 = v43;
            v44[v42 + 1] = v70;
          }
          goto LABEL_73;
        }
      }
    }
    --*v65;
  }
  *(_WORD *)(2 * v63 + g_MapData + 40 * v62 + 1534) = v77;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836)
    && *(unsigned __int8 *)(31 * v58 + g_MapData + 854) == *(_DWORD *)(g_MapData + 840) )
  {
    UnitBattle_RestoreGateBlocker();
  }
  return v65;
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
int * UnitBattle_MoveTrackNear(int a1, int a2, int a3, DWORD a4)
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

  target_row = a2;
  target_col = a3;
  Debug_Log(a2, a3, a4, (int)aUnitbattle_mov);
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
  path = UnitBattle_MoveTrack(a1, target_row, target_row, target_col, a4);
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
int * UnitBattle_MoveTrackNearWall(int a1, int a2, int a3, DWORD a4)
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

  target_row = a2;
  target_col = a3;
  Debug_Log(a1, a2, a4, (int)aUnitbattle_m_2);
  if ( target_col < 0 || target_col >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  current_row = *(unsigned __int16 *)(31 * a1 + g_MapData + 856);
  current_col = *(unsigned __int16 *)(31 * a1 + g_MapData + 858);
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
      path_before_wall = UnitBattle_MoveTrack(a1, target_row - 1, target_row - 1, target_col, a4);
    if ( target_row + 1 < *(_DWORD *)(g_MapData + 804) )
      path_after_wall = UnitBattle_MoveTrack(a1, target_row + 1, target_row + 1, target_col, a4);
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
int * UnitBattle_MoveTrackForce(int a1, int a2, DWORD a3)
{
  int target_row;
  int target_col;
  int *result; // eax

  Debug_Log(a1, a2, a3, (int)aUnitbattle_m_3);
  target_col = a2;
  target_row = (int)a3;
  if ( target_row < 0 || target_row >= *(_DWORD *)(g_MapData + 804) || target_col < 0 || target_col >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  g_MapIgnoreUnitOccupancy = 1;
  if ( *(char *)(target_col + g_MapData + 20 * target_row + 3134) <= 0 )
    goto LABEL_4;
  if ( *(unsigned __int16 *)(g_MapData + 31 * a1 + 856) < target_row )
  {
    --target_row;
LABEL_4:
    result = UnitBattle_MoveTrack(a1, target_row, target_row, target_col, a3);
    g_MapIgnoreUnitOccupancy = 0;
    return result;
  }
  result = UnitBattle_MoveTrack(a1, target_row + 1, target_row + 1, target_col, a3);
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
  int v4; // edx
  __int16 *v5; // esi
  _DWORD *v6; // eax
  int v7; // edi
  unsigned __int16 v8; // dx
  int v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // ecx
  _DWORD *v13; // eax
  int v14; // eax
  int v15; // eax
  int *v16; // eax
  int v17; // edx
  int v18; // eax
  int *v19; // edx
  int v20; // ecx
  int v21; // eax
  int v22; // edx
  int v23; // ebp
  int v24; // ecx
  int v25; // edx
  int v26; // eax
  unsigned __int8 v27; // al
  int v28; // ecx
  unsigned __int16 v29; // ax
  int v30; // ebp
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // ecx
  int v35; // eax
  int v36; // ecx
  unsigned int v37; // edx
  char v38; // al
  int v39; // edx
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // eax
  int v44; // edx
  int v45; // eax
  int v46; // eax
  char v48[100]; // [esp+0h] [ebp-9Ch] BYREF
  int v49; // [esp+64h] [ebp-38h]
  int v50; // [esp+68h] [ebp-34h]
  int v51; // [esp+6Ch] [ebp-30h]
  int v52; // [esp+70h] [ebp-2Ch]
  _DWORD *v53; // [esp+74h] [ebp-28h]
  int v54; // [esp+78h] [ebp-24h]
  unsigned int v55; // [esp+7Ch] [ebp-20h]
  int v56; // [esp+80h] [ebp-1Ch]
  int v57; // [esp+84h] [ebp-18h]

  v50 = a1;
  v4 = a1;
  Debug_Log(a2, a3, a4, (int)aUnitbattle_m_1);
  v5 = (__int16 *)(g_MapData + 852 + 31 * v4);
  v6 = *(_DWORD **)((char *)v5 + 23);
  v53 = v6;
  if ( v6 && *v6 )
  {
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    g_SelectedUnitIndex = v50;
    v7 = 0;
    UnitBattle_DrawSelectedUnitPanel(0, 1, a3, 0);
    v8 = v5[3];
    v9 = (unsigned __int16)v5[2];
    v52 = 0;
    if ( !UnitBattle_IsTileInViewport(v9, v8) )
      UnitBattle_CenterViewOnUnit(v50);
    UnitBattle_RedrawVisibleGrid();
    *((_BYTE *)v5 + 22) &= ~1u;
    g_ActiveUnitMoveTileIndex = v50;
    v10 = g_MapData + 31 * v50;
    LOWORD(v11) = *(unsigned __int8 *)(v10 + 854);
    Unit_BuildGoSpriteFilePath(v48, *(_BYTE *)(v10 + 852), v11);
    v13 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( v13 )
      v13 = DLXSpriteSet_Load(v13, v48);
    g_ActiveUnitAnimSpriteSet = (int)v13;
    v14 = *v5;
    if ( v14 == 27 || v14 == 30 )
      v15 = *((_BYTE *)v5 + 17) & 7;
    else
      v15 = 0;
    g_UnitAnimFrameIndex = v15;
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    g_UnitBattleAnimFrameCount = 8;
    if ( *v53 )
    {
      v51 = 31 * v50;
      while ( 1 )
      {
        v16 = *(int **)((char *)v5 + 23);
        v17 = *v16 - 1;
        *v16 = v17;
        v18 = v16[v17 + 1];
        v54 = v18;
        v7 = HIWORD(v18);
        if ( HIWORD(v18) > (int)*((unsigned __int8 *)v5 + 8) )
          break;
        v23 = (unsigned __int8)v54;
        LOWORD(v11) = BYTE1(v54);
        if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(v51 + g_MapData + 852), (unsigned __int8)v54, BYTE1(v54)) )
        {
          v25 = BYTE1(v54) - (unsigned __int16)v5[3];
          LOWORD(v11) = v23 - v5[2];
          v26 = v23 - (unsigned __int16)v5[2];
          v52 = v7;
          v27 = Facing_DirectionFromDelta8(v26, v25);
          v7 = v27;
          *((_BYTE *)v5 + 3) = v27;
          if ( !UnitBattle_IsTileInViewport(v23, BYTE1(v54)) )
          {
            UnitBattle_CenterViewOnUnit(v50);
            UnitBattle_RedrawVisibleGrid();
          }
          g_UnitMoveAnimOffsetX %= 64;
          g_UnitMoveAnimOffsetY %= 64;
          v29 = *(_WORD *)(v51 + g_MapData + 858);
          v57 = ((unsigned __int8)v54 - *(unsigned __int16 *)(v51 + g_MapData + 856)) << 6;
          v56 = (BYTE1(v54) - v29) << 6;
          v36 = Time_Now(0, 0);
          v37 = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *(__int16 *)(v51 + g_MapData + 852)];
          v30 = 1;
          v55 = 8 * v7;
          while ( 1 )
          {
            v31 = g_UnitMoveAnimOffsetX;
            if ( g_UnitMoveAnimOffsetX <= 0 )
              v31 = -g_UnitMoveAnimOffsetX;
            v32 = v31;
            v33 = v57;
            if ( v57 <= 0 )
              v33 = -v57;
            if ( v32 >= v33 )
            {
              v43 = g_UnitMoveAnimOffsetY;
              if ( g_UnitMoveAnimOffsetY <= 0 )
                v43 = -g_UnitMoveAnimOffsetY;
              LOWORD(v11) = v56;
              v44 = v43;
              v45 = v56 <= 0 ? -v56 : v56;
              if ( v44 >= v45 )
                break;
            }
            DD_Pump((int)g_RenderState, v11);
            UnitBattle_UpdateIdleAnimatedUnits();
            if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
              UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(v34);
            v35 = Time_Now(0, 0);
            if ( v35 - v36 >= v37 )
            {
              v38 = g_BattleUnitMoveAnimStepCounter;
              v39 = ++g_BattleUnitMoveAnimStepCounter;
              if ( (v38 & 1) != 0 )
              {
                g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
                Audio_PlayBattleMapUnitMoveSound((unsigned __int16)v5[2], (unsigned __int16)v5[3], g_UnitAnimFrameIndex, *v5);
              }
              v36 = Time_Now(0, 0);
              v40 = g_UnitMoveAnimOffsetX;
              if ( g_UnitMoveAnimOffsetX <= 0 )
                v40 = -g_UnitMoveAnimOffsetX;
              v41 = v40;
              v42 = v57;
              if ( v57 <= 0 )
                v42 = -v57;
              if ( v41 >= v42 )
              {
                v46 = g_UnitMoveAnimOffsetY;
                if ( g_UnitMoveAnimOffsetY <= 0 )
                  v46 = -g_UnitMoveAnimOffsetY;
                LOWORD(v11) = v56;
                if ( v56 <= 0 )
                {
                  if ( v46 >= -v56 )
                    break;
                }
                else if ( v46 >= v56 )
                {
                  break;
                }
              }
              if ( UnitBattle_GetSpriteVerticalOffsetPx(v50) )
              {
                UnitBattle_RedrawUnitNeighborhood(v50);
              }
              else
              {
                UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3]);
                if ( v30 || v7 == 4 || v7 == 5 || v7 == 3 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] + 1);
                if ( v30 || !v7 || v7 == 7 || v7 == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] - 1);
                if ( v30 || v7 == 2 || v7 == 3 || v7 == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3]);
                if ( v30 || v7 == 6 || v7 == 5 || v7 == 7 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3]);
                if ( v30 || v7 == 3 || v7 == 7 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] + 1);
                if ( v30 || v7 == 1 || v7 == 5 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] - 1);
                if ( v30 || v7 == 5 || v7 == 1 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] + 1);
                if ( v30 || v7 == 7 || v7 == 3 )
                  UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] - 1);
              }
              v30 = 0;
              v49 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(v51 + g_MapData + 852)];
              LOBYTE(v11) = v49;
              g_UnitMoveAnimOffsetX += v49 * Map_NeighborDX[v55 / 4];
              g_UnitMoveAnimOffsetY += Map_NeighborDY[v55 / 4]
                            * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(v51 + g_MapData + 852)];
            }
          }
          *(_WORD *)(g_MapData + 40 * (unsigned __int16)v5[2] + 2 * (unsigned __int16)v5[3] + 1534) = -1;
          v5[2] = (unsigned __int8)v54;
          v5[3] = BYTE1(v54);
          *(_WORD *)(2 * BYTE1(v54) + 40 * (unsigned __int16)v5[2] + g_MapData + 1534) = v50;
          if ( *v53 )
            continue;
        }
        goto LABEL_15;
      }
      v19 = *(int **)((char *)v5 + 23);
      v11 = *v19;
      if ( *v19 < 100 )
      {
        v20 = v11 + 1;
        v11 *= 4;
        *v19 = v20;
        *(int *)((char *)v19 + v11 + 4) = v18;
      }
    }
LABEL_15:
    *((_BYTE *)v5 + 8) -= v52;
    nfree_((int)(uintptr_t)v53);
    v21 = PLAYER_DATA_STRIDE * *((unsigned __int8 *)v5 + 2);
    *(_DWORD *)((char *)v5 + 23) = 0;
    *(_DWORD *)(gameData + v21 + 140073) = 1;
    Audio_StopUnitMoveSound();
    DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
    g_ActiveUnitMoveTileIndex = -1;
    UnitBattle_RedrawVisibleGrid();
    Diagnostics_TraceWorldMapActionEvent(
      "battle_move_cleanup_skip_panel_redraw",
      v50,
      *((unsigned __int8 *)v5 + 8),
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
int  UnitBattle_CenterViewOnUnit(int a1)
{
  int v1; // eax
  int v2; // ecx
  int result; // eax
  int v4; // esi

  v1 = 31 * a1;
  *(_DWORD *)(g_MapData + 808) = *(unsigned __int16 *)(g_MapData + v1 + 856) - 3;
  *(_DWORD *)(g_MapData + 812) = *(unsigned __int16 *)(g_MapData + v1 + 858) - 3;
  if ( *(int *)(g_MapData + 808) < 0 )
    *(_DWORD *)(g_MapData + 808) = 0;
  v2 = *(_DWORD *)(g_MapData + 804);
  if ( *(_DWORD *)(g_MapData + 808) + 7 > v2 )
    *(_DWORD *)(g_MapData + 808) = v2 - 7;
  if ( *(int *)(g_MapData + 812) < 0 )
    *(_DWORD *)(g_MapData + 812) = 0;
  result = g_MapData;
  v4 = *(_DWORD *)(g_MapData + 800);
  if ( *(_DWORD *)(g_MapData + 812) + 7 > v4 )
    *(_DWORD *)(g_MapData + 812) = v4 - 7;
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (00426EF0) --------------------------------------------------------
int  UnitBattle_CountAdjacentEnemies(int a1)
{
  int v2; // esi
  int i; // eax
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  int v8; // [esp+0h] [ebp-1Ch]

  v2 = 0;
  v8 = *(unsigned __int16 *)(a1 + 4);
  for ( i = 0; i != 16; i += 2 )
  {
    v4 = v8 + g_UnitBattleAdjacentTileDeltaX[i];
    if ( v4 >= 0 && v4 < *(_DWORD *)(g_MapData + 804) )
    {
      v5 = g_UnitBattleAdjacentTileDeltaY[i] + *(unsigned __int16 *)(a1 + 6);
      if ( v5 >= 0 && v5 < *(_DWORD *)(g_MapData + 800) )
      {
        v6 = *(__int16 *)(g_MapData + 40 * v4 + 2 * v5 + 1534);
        if ( v6 != -1 && *(_BYTE *)(31 * v6 + g_MapData + 854) != *(_BYTE *)(a1 + 2) )
          ++v2;
      }
    }
  }
  return v2;
}
// 514500: using guessed type int dword_514500[];
// 514504: using guessed type int dword_514504[];
// 532048: using guessed type int g_MapData;

//----- (00426F90) --------------------------------------------------------
signed int  UnitBattle_GetTargetCrowdingScale(int a1)
{
  signed int result; // eax

  switch ( UnitBattle_CountAdjacentEnemies(a1) )
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
int  UnitBattle_CalcMeleeExchange(int a1, int a2, int *a3, _DWORD *a4, int a5)
{
  char *v7; // ebx
  char *v8; // esi
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // ebx
  int v15; // edx
  int v16; // edx
  int result; // eax
  int v18; // edx
  int v19; // esi
  int v20; // ecx
  signed int v21; // [esp+0h] [ebp-14h]
  signed int v22; // [esp+0h] [ebp-14h]

  v7 = (char *)(g_MapData + 852 + 31 * a1);
  v8 = (char *)(31 * a2 + g_MapData + 852);
  *a4 = v7[9];
  *a3 = v8[9];
  UnitBattle_GetTargetCrowdingScale((int)v8);
  v10 = Unit_CalcEffectivenessB(v8, v9);
  if ( (v10 * v11 - (__CFSHL__((v10 * v11) >> 31, 8) + ((v10 * v11) >> 31 << 8))) >> 8 )
  {
    UnitBattle_GetTargetCrowdingScale((int)v7);
    Unit_CalcEffectivenessA(v7, 0);
  }
  v21 = UnitBattle_GetTargetCrowdingScale((int)v7);
  v12 = Unit_CalcEffectivenessB(v7, 0);
  v14 = (v12 * v21 - (__CFSHL__((v12 * v21) >> 31, 8) + ((v12 * v21) >> 31 << 8))) >> 8;
  if ( v14 )
  {
    v22 = UnitBattle_GetTargetCrowdingScale((int)v8);
    v15 = Unit_CalcEffectivenessB(v8, 0) * v22 / v14;
  }
  else
  {
    v15 = 1024;
  }
  if ( a5 )
    v15 = (192 * v15 - (__CFSHL__((192 * v15) >> 31, 8) + ((192 * v15) >> 31 << 8))) >> 8;
  if ( v15 >= 384 )
  {
    if ( v15 >= 512 )
    {
      if ( v15 >= 640 )
      {
        if ( v15 >= 768 )
          v16 = 15 * v15;
        else
          v16 = 12 * v15;
      }
      else
      {
        v16 = 10 * v15;
      }
    }
    else
    {
      v16 = 7 * v15;
    }
  }
  else
  {
    v16 = 5 * v15;
  }
  result = (v16 - (__CFSHL__(v16 >> 31, 8) + (v16 >> 31 << 8))) >> 8;
  v18 = result;
  if ( result > 100 )
    v18 = 100;
  v19 = *a3 - v13;
  *a3 = v19;
  if ( v19 <= 0 )
    *a3 = 0;
  v20 = *a4 - v18;
  *a4 = v20;
  if ( v20 <= 0 )
    *a4 = 0;
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
  __int16 *v5; // esi
  char v6; // bl
  int v7; // ecx
  _DWORD *v8; // eax
  char v9; // bl
  int v10; // ecx
  _DWORD *v11; // eax
  signed int v12; // ebp
  unsigned int v13; // edi
  int v14; // ebx
  unsigned __int16 *SpriteForChar; // eax
  int v16; // eax
  unsigned __int16 *v17; // ecx
  unsigned __int16 *v18; // eax
  unsigned __int16 *v19; // ecx
  int v20; // eax
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // ecx
  int v25; // ecx
  int v26; // ebx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // ecx
  int v32; // eax
  unsigned __int8 v33; // dl
  char v34; // al
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // eax
  int v39; // eax
  unsigned __int16 *v40; // eax
  signed int v41; // ebp
  unsigned __int16 *v42; // ecx
  int v43; // eax
  unsigned __int16 *v44; // eax
  unsigned __int16 *v45; // ecx
  int v46; // eax
  int v47; // edx
  unsigned __int16 *v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // edx
  int v52; // eax
  int v53; // eax
  int v54; // ecx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // eax
  char v59; // bl
  int v60; // ecx
  _DWORD *v61; // eax
  int v62; // ecx
  int v63; // eax
  int v64; // ecx
  int v65; // ebx
  int v66; // ecx
  int v67; // eax
  unsigned int v68; // edx
  int v69; // eax
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
  char v81; // bl
  int v82; // ecx
  _DWORD *v83; // eax
  int v84; // edx
  int v85; // ebx
  int v86; // ecx
  int v87; // eax
  int v88; // ecx
  unsigned int v89; // edx
  char v90; // al
  int v91; // eax
  int v92; // edx
  int v93; // eax
  int v94; // eax
  int v95; // ecx
  int v96; // edx
  char v97[100]; // [esp+0h] [ebp-88h] BYREF
  int v98; // [esp+64h] [ebp-24h]
  int v99; // [esp+68h] [ebp-20h]
  unsigned __int16 *v100; // [esp+6Ch] [ebp-1Ch]
  int v101; // [esp+70h] [ebp-18h]
  int v102; // [esp+74h] [ebp-14h]
  int v103; // [esp+78h] [ebp-10h]

  v102 = a1;
  v101 = a2;
  v99 = a4;
  v98 = a3;
  Debug_Log(a3, a4, (DWORD)a5, (int)aAttackanimDD);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  v5 = (__int16 *)(g_MapData + 852 + 31 * v102);
  if ( v101 == -1 )
    v100 = 0;
  else
    v100 = (unsigned __int16 *)(31 * v101 + g_MapData + 852);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)v5[2], (unsigned __int16)v5[3])
    || (a5 = v100) != 0 && !UnitBattle_IsTileInViewport(v100[2], v100[3]) )
  {
    UnitBattle_CenterViewOnUnit(v102);
    UnitBattle_RedrawVisibleGrid();
  }
  if ( v100 )
    *((_BYTE *)v5 + 3) = Facing_DirectionFromDelta8(v100[2] - (unsigned __int16)v5[2], v100[3] - (unsigned __int16)v5[3]);
  v6 = *((_BYTE *)v5 + 2);
  Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)v5, v6);
  v8 = (_DWORD *)Mem_Alloc(4112, v7, v6, (DWORD)a5);
  if ( v8 )
    v8 = DLXSpriteSet_Load(v8, v97);
  g_ActiveUnitAnimSpriteSet = (int)v8;
  if ( v101 != -1 )
  {
    v9 = *((_BYTE *)v100 + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)v100, v9);
    v11 = (_DWORD *)Mem_Alloc(4112, v10, v9, (DWORD)a5);
    if ( v11 )
      v11 = DLXSpriteSet_Load(v11, v97);
    g_UnitBattleAnimatingUnitSpriteSet = (int)v11;
  }
  v12 = 0;
  v13 = *((unsigned __int8 *)v5 + 3);
  v103 = 0;
  if ( v100 )
  {
    unsigned __int16 *defender_sprite;
    unsigned __int16 *attacker_sprite;

    defender_sprite = (unsigned __int16 *)UnitSpriteCache_FindEntryOrLoad(*v100, *((_BYTE *)v100 + 2), 0, *((_BYTE *)v100 + 3));
    v14 = 8 * *((unsigned __int8 *)v5 + 3);
    if ( v13 == 7 || v13 == 6 || v13 == 5 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, v14);
      v12 = -UnitBattle_ScanSpriteFirstOpaqueRunLength(attacker_sprite) - UnitBattle_ScanSpriteMinOpaqueRunLength(defender_sprite);
    }
    else if ( v13 == 1 || v13 == 2 || v13 == 3 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, v14);
      v12 = UnitBattle_ScanSpriteMinOpaqueRunLength(attacker_sprite) + UnitBattle_ScanSpriteFirstOpaqueRunLength(defender_sprite);
    }
    if ( v13 == 7 || v13 < 2 )
    {
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, v14);
      v22 = -UnitBattle_CountLeadingBlankSpriteRows(attacker_sprite) - UnitBattle_CountTrailingBlankSpriteRows(defender_sprite);
    }
    else
    {
      if ( v13 != 5 && v13 != 4 && v13 != 3 )
        goto LABEL_20;
      attacker_sprite = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, v14);
      v22 = UnitBattle_CountTrailingBlankSpriteRows(attacker_sprite) + UnitBattle_CountLeadingBlankSpriteRows(defender_sprite);
    }
    v103 = v22;
    goto LABEL_20;
  }
  v48 = (unsigned __int16 *)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, 8 * v13);
  if ( v13 == 6 )
  {
    v12 = -UnitBattle_ScanSpriteFirstOpaqueRunLength(v48);
  }
  else
  {
    v12 = UnitBattle_ScanSpriteMinOpaqueRunLength(v48);
  }
LABEL_20:
  if ( !v12 || !v103 )
    goto LABEL_21;
  if ( v12 <= 0 )
    v50 = -1;
  else
    v50 = 1;
  v51 = v50;
  if ( v103 <= 0 )
    v52 = -v103;
  else
    v52 = v103;
  if ( v12 <= 0 )
    v12 = -v12;
  if ( v12 <= v52 )
    v12 = v52;
  v12 *= v51;
  if ( v103 <= 0 )
    v53 = -1;
  else
    v53 = 1;
  v54 = v53;
  if ( v103 <= 0 )
    v55 = -v103;
  else
    v55 = v103;
  if ( v12 <= 0 )
  {
    if ( -v12 > v55 )
    {
      v103 = -v12 * v54;
      goto LABEL_21;
    }
LABEL_82:
    v103 = v55 * v54;
    goto LABEL_21;
  }
  if ( v12 <= v55 )
    goto LABEL_82;
  v103 = v12 * v54;
LABEL_21:
  v23 = 8;
  v24 = 0;
  g_ActiveUnitMoveTileIndex = v102;
  g_UnitMoveAnimOffsetX = 0;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = 8;
LABEL_22:
  v26 = Time_Now(v24, v23);
  while ( 1 )
  {
    v27 = g_UnitMoveAnimOffsetX;
    if ( g_UnitMoveAnimOffsetX <= 0 )
      v27 = -g_UnitMoveAnimOffsetX;
    v28 = v27;
    v29 = v12 <= 0 ? -v12 : v12;
    if ( v28 >= v29 )
    {
      v56 = g_UnitMoveAnimOffsetY;
      if ( g_UnitMoveAnimOffsetY <= 0 )
        v56 = -g_UnitMoveAnimOffsetY;
      v57 = v56;
      v58 = v103;
      if ( v103 <= 0 )
        v58 = -v103;
      if ( v57 >= v58 )
        break;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)g_RenderState, v26);
    v30 = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *v5];
    v32 = Time_Now(v31, v30);
    if ( v32 - v26 >= (unsigned int)v30 )
    {
      v34 = g_UnitMoveAnimTickParityCounter++;
      if ( (v34 & 1) != 0 )
        g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
      v35 = g_UnitMoveAnimOffsetX;
      if ( g_UnitMoveAnimOffsetX <= 0 )
        v35 = -g_UnitMoveAnimOffsetX;
      v36 = v35;
      if ( v12 <= 0 )
        v37 = -v12;
      else
        v37 = v12;
      if ( v36 >= v37 )
      {
        v73 = g_UnitMoveAnimOffsetY;
        if ( g_UnitMoveAnimOffsetY <= 0 )
          v73 = -g_UnitMoveAnimOffsetY;
        if ( v103 <= 0 )
        {
          if ( v73 >= -v103 )
            break;
        }
        else if ( v73 >= v103 )
        {
          break;
        }
      }
      v38 = *v5;
      if ( v38 == 27 || v38 == 30 )
      {
        UnitBattle_RedrawUnitNeighborhood(v102);
      }
      else
      {
        UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3]);
        if ( v13 == 4 || v13 == 5 || v13 == 3 )
          UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] + 1);
        if ( !v13 || v13 == 7 || v13 == 1 )
          UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] - 1);
        if ( v13 == 2 || v13 == 3 || v13 == 1 )
          UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3]);
        if ( v13 == 6 || v13 == 5 || v13 == 7 )
          UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3]);
        switch ( v13 )
        {
          case 3u:
            UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] + 1);
            break;
          case 1u:
            UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] - 1);
            break;
          case 5u:
            UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] + 1);
            break;
          case 7u:
            UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] - 1);
            break;
        }
      }
      if ( v12 - g_UnitMoveAnimOffsetX <= 0 )
      {
        if ( v12 == g_UnitMoveAnimOffsetX )
          v39 = v24;
        else
          v39 = -1;
      }
      else
      {
        v39 = 1;
      }
      g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *v5] * v39;
      v23 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *v5];
      if ( v103 - g_UnitMoveAnimOffsetY <= 0 )
      {
        if ( v103 == g_UnitMoveAnimOffsetY )
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
  v59 = *((_BYTE *)v5 + 2);
  Unit_BuildAttackAnimSpritePath(v97, *(_BYTE *)v5, v59);
  v61 = (_DWORD *)Mem_Alloc(4112, v60, v59, v12);
  if ( v61 )
    v61 = DLXSpriteSet_Load(v61, v97);
  g_ActiveUnitAnimSpriteSet = (int)v61;
  g_UnitMoveAnimOffsetX = v12;
  g_UnitAnimFrameIndex = 0;
  g_UnitMoveAnimOffsetY = v103;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeAttackAnimationFrameCount[88 * *v5];
  v63 = Time_Now(v62, 0);
  v64 = 31 * v102;
  v65 = v63;
  while ( g_UnitAnimFrameIndex < g_UnitBattleAnimFrameCount )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)g_RenderState, v65);
    v69 = *(__int16 *)(v64 + g_MapData + 852);
    v70 = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * v69];
    v67 = Time_Now(v66, v70);
    if ( v67 - v65 >= (unsigned int)v70 )
    {
      v69 = *(__int16 *)(v64 + g_MapData + 852);
      v70 = (unsigned __int8)g_UnitTypeAttackSoundFrameIndex[88 * v69];
      if ( v70 == g_UnitAnimFrameIndex )
        Audio_PlayUnitMeleeAttackSound(v69);
      v65 = Time_Now(v64, v70);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3]);
      UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3]);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3]);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] + 1);
      ++g_UnitAnimFrameIndex;
    }
  }
  g_UnitAnimFrameIndex = 0;
  if ( v101 != -1 )
  {
    if ( v98 )
    {
      UnitBattle_PlayDeathAnimation(v101, v64, v65, v12);
    }
    else
    {
      Audio_PlayUnitHitSound((__int16)*v100);
      g_UnitBattleAnimatingUnitIndex = v101;
      g_UnitBattleHitAnimFrame = Rng_RandRange(0, 7);
      v64 = Time_Now(0, 3);
      v12 = Rng_RandRange(1, 3);
      while ( v12 >= 0 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, 0);
        v79 = Time_Now(0, 0);
        if ( (unsigned int)(v79 - v64) >= 3 )
        {
          v64 = Time_Now(0, 0);
          UnitBattle_RedrawUnitNeighborhood(v101);
          LOBYTE(v65) = (g_UnitBattleHitAnimFrame + 1) & 7;
          --v12;
          g_UnitBattleHitAnimFrame = (unsigned __int8)v65;
        }
      }
      g_UnitBattleAnimatingUnitIndex = -1;
    }
  }
  if ( v99 )
  {
    if ( g_UnitBattleChargeModeActive_532060 )
      UnitBattle_RefreshSelectedUnitUI();
    UnitBattle_PlayDeathAnimation(v102, v64, v65, v12);
  }
  v71 = v99;
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  if ( !v71 )
  {
    v81 = *((_BYTE *)v5 + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)v5, v81);
    v83 = (_DWORD *)Mem_Alloc(4112, v82, v81, v12);
    if ( v83 )
      v83 = DLXSpriteSet_Load(v83, v97);
    LOBYTE(v85) = 8;
    g_ActiveUnitAnimSpriteSet = (int)v83;
    g_UnitAnimFrameIndex = 0;
    g_UnitBattleAnimFrameCount = 8;
    v88 = Time_Now(0, v84);
    while ( g_UnitMoveAnimOffsetX || g_UnitMoveAnimOffsetY )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, 0);
      v89 = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *v5];
      v87 = Time_Now(v86, v89);
      if ( v87 - v88 >= v89 )
      {
        v90 = g_UnitArrivalAnimTickParityCounter++;
        if ( (v90 & 1) != 0 )
          g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
        if ( !g_UnitMoveAnimOffsetX && !g_UnitMoveAnimOffsetY )
          break;
        v91 = *v5;
        if ( v91 == 27 || v91 == 30 )
        {
          UnitBattle_RedrawUnitNeighborhood(v102);
        }
        else
        {
          UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3]);
          if ( v13 == 4 || v13 == 5 || v13 == 3 )
            UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] + 1);
          if ( !v13 || v13 == 7 || v13 == 1 )
            UnitBattle_RedrawTile((unsigned __int16)v5[2], (unsigned __int16)v5[3] - 1);
          if ( v13 == 2 || v13 == 3 || v13 == 1 )
            UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3]);
          if ( v13 == 6 || v13 == 5 || v13 == 7 )
            UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3]);
          switch ( v13 )
          {
            case 3u:
              UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] + 1);
              break;
            case 1u:
              UnitBattle_RedrawTile((unsigned __int16)v5[2] + 1, (unsigned __int16)v5[3] - 1);
              break;
            case 5u:
              UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] + 1);
              break;
            case 7u:
              UnitBattle_RedrawTile((unsigned __int16)v5[2] - 1, (unsigned __int16)v5[3] - 1);
              break;
          }
        }
        v92 = g_UnitMoveAnimOffsetX;
        v85 = g_UnitMoveAnimOffsetY;
        if ( -g_UnitMoveAnimOffsetX < 0 || g_UnitMoveAnimOffsetX == 0 )
        {
          if ( g_UnitMoveAnimOffsetX )
            v93 = -1;
          else
            v93 = 0;
        }
        else
        {
          v93 = 1;
        }
        g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *v5] * v93;
        if ( -g_UnitMoveAnimOffsetY < 0 || g_UnitMoveAnimOffsetY == 0 )
        {
          if ( g_UnitMoveAnimOffsetY )
            v94 = -1;
          else
            v94 = 0;
        }
        else
        {
          v94 = 1;
        }
        v95 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *v5] * v94 + g_UnitMoveAnimOffsetY;
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
int  UnitBattle_PlayDeathAnimation(int a1, int a2, char a3, DWORD a4)
{
  int v5; // edx
  int v6; // esi
  __int16 *v7; // ebp
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // eax
  unsigned int v13; // edx
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ebx
  int v18; // esi
  int v19; // edi
  int result; // eax
  int v21; // ebx
  int v22; // esi
  int v23; // edx
  int v24; // [esp+0h] [ebp-24h]
  int v25; // [esp+4h] [ebp-20h]
  int v26; // [esp+8h] [ebp-1Ch]

  Debug_Log(a2, a3, a4, (int)aDeathanimD);
  v5 = a1;
  v6 = 31 * v5;
  v7 = (__int16 *)(g_MapData + 852 + 31 * v5);
  Audio_PlayUnitDeathSound(*v7);
  if ( (g_UnitTypeFlags[22 * *v7] & 1) != 0 )
  {
    *(_BYTE *)(40 * (unsigned __int16)v7[2] + g_MapData + 2 * (unsigned __int16)v7[3] + 2334) = 48;
    UnitBattle_InitUnitFadeAnimation(a1, 255, -4, 255);
    v9 = Time_Now(v8, 0);
    LOWORD(v11) = v7[2];
    v26 = v9;
    v25 = v6;
    *(_BYTE *)(g_MapData + 40 * v11 + 2 * (unsigned __int16)v7[3] + 2335) = -1;
    while ( 1 )
    {
      v12 = 40 * (unsigned __int16)v7[2] + g_MapData + 2 * (unsigned __int16)v7[3];
      if ( *(char *)(v12 + 2334) >= 56 )
        break;
      v13 = v26 + 10;
      while ( 1 )
      {
        v14 = Time_Now(v10, v13);
        if ( v14 >= v13 )
          break;
        UnitBattle_UpdateIdleAnimatedUnits();
      }
      v26 = Time_Now(v15, v13);
      UnitBattle_RedrawUnitNeighborhood(a1);
      UnitBattle_RedrawUnitNeighborhood(a1);
      v10 = *(unsigned __int8 *)(v25 + g_MapData + 855);
      v21 = *(unsigned __int16 *)(v25 + g_MapData + 856);
      v22 = *(unsigned __int16 *)(v25 + g_MapData + 858);
      if ( !*(_BYTE *)(v25 + g_MapData + 855) || v10 == 7 || v10 == 1 )
        UnitBattle_RedrawTile(v21, v22 - 1);
      if ( v10 == 1 )
        UnitBattle_RedrawTile(v21 + 1, v22 - 1);
      if ( v10 == 2 || v10 == 1 || v10 == 3 )
        UnitBattle_RedrawTile(v21 + 1, v22);
      if ( v10 == 3 )
        UnitBattle_RedrawTile(v21 + 1, v22 + 1);
      if ( v10 == 4 || v10 == 3 || v10 == 5 )
        UnitBattle_RedrawTile(v21, v22 + 1);
      if ( v10 == 5 )
        UnitBattle_RedrawTile(v21 - 1, v22 + 1);
      if ( v10 == 6 || v10 == 7 || v10 == 5 )
        UnitBattle_RedrawTile(v21 - 1, v22);
      if ( v10 == 7 )
        UnitBattle_RedrawTile(v21 - 1, v22 - 1);
      v23 = 40 * (unsigned __int16)v7[2] + g_MapData;
      ++*(_BYTE *)(v23 + 2 * (unsigned __int16)v7[3] + 2334);
    }
    *(_BYTE *)(v12 + 2334) = -1;
  }
  else
  {
    UnitBattle_InitUnitFadeAnimation(a1, 255, -8, 255);
    if ( g_UnitFadeAnimCurrentOffset )
    {
      v24 = v6;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        UnitBattle_RedrawUnitNeighborhood(a1);
        v16 = *(unsigned __int8 *)(v24 + g_MapData + 855);
        v17 = *(unsigned __int16 *)(v24 + g_MapData + 856);
        v18 = *(unsigned __int16 *)(v24 + g_MapData + 858);
        if ( !*(_BYTE *)(v24 + g_MapData + 855) || v16 == 7 || v16 == 1 )
          UnitBattle_RedrawTile(v17, v18 - 1);
        if ( v16 == 1 )
          UnitBattle_RedrawTile(v17 + 1, v18 - 1);
        if ( v16 == 2 || v16 == 1 || v16 == 3 )
          UnitBattle_RedrawTile(v17 + 1, v18);
        if ( v16 == 3 )
          UnitBattle_RedrawTile(v17 + 1, v18 + 1);
        if ( v16 == 4 || v16 == 3 || v16 == 5 )
          UnitBattle_RedrawTile(v17, v18 + 1);
        if ( v16 == 5 )
          UnitBattle_RedrawTile(v17 - 1, v18 + 1);
        if ( v16 == 6 || v16 == 7 || v16 == 5 )
          UnitBattle_RedrawTile(v17 - 1, v18);
        if ( v16 == 7 )
          UnitBattle_RedrawTile(v17 - 1, v18 - 1);
        *(_BYTE *)(40 * (unsigned __int16)v7[2] + g_MapData + 2 * (unsigned __int16)v7[3] + 2335) = -1 - g_UnitFadeAnimCurrentOffset;
      }
      while ( g_UnitFadeAnimCurrentOffset );
    }
  }
  v19 = 31 * a1;
  *(_WORD *)(g_MapData + v19 + 852) = -1;
  result = *(unsigned __int16 *)(g_MapData + v19 + 858);
  *(_WORD *)(40 * *(unsigned __int16 *)(g_MapData + v19 + 856) + g_MapData + 2 * result + 1534) = -1;
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
int  UnitBattle_GetCorpseSpriteIndex(__int16 *a1)
{
  return (unsigned __int8)g_UnitTypeCorpseSpriteBaseIndex[88 * *a1] + (*((unsigned __int8 *)a1 + 3) + 4) % 8;
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
BOOL  UnitBattle_IsTileWithinRange(int a1, int a2, int a3)
{
  int unit_record;
  int unit_type_offset;
  signed int distance; // eax

  if ( !g_MapData || a1 < 0 || a1 >= 22 )
    return 0;
  unit_record = g_MapData + 31 * a1 + 852;
  if ( *(__int16 *)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 4) - a2)
       * (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 4) - a2)
       + (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 6) - a3)
       * (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 6) - a3));
  unit_type_offset = 88 * *(__int16 *)unit_record;
  return distance <= (unsigned __int8)g_UnitTypeMaxRange[unit_type_offset]
      && distance > (unsigned __int8)g_UnitTypeMinRange[unit_type_offset];
}
// 532048: using guessed type int g_MapData;

//----- (00428850) --------------------------------------------------------
BOOL  UnitBattle_IsUnitWithinRange(int a1, int a2)
{
  return UnitBattle_IsTileWithinRange(
           a1,
           *(unsigned __int16 *)(g_MapData + 31 * a2 + 856),
           *(unsigned __int16 *)(g_MapData + 31 * a2 + 858));
}
// 532048: using guessed type int g_MapData;

//----- (00428880) --------------------------------------------------------
__int16  UnitBattle_PlayShotAnimation(
        int a1,
        int a2,
        int a3,
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
  char v16; // bl
  int v17; // ecx
  _DWORD *v18; // eax
  char v19; // bl
  int v20; // ecx
  _DWORD *v21; // eax
  int v22; // ecx
  int v23; // ecx
  _DWORD *v24; // eax
  char v25; // bl
  int v26; // edx
  int v27; // ecx
  int v28; // ecx
  unsigned __int16 v29; // ax
  char *v30; // esi
  int v31; // ecx
  int v32; // edi
  int v33; // ecx
  int v34; // eax
  int v35; // ecx
  unsigned int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // ebx
  unsigned __int16 v40; // cx
  unsigned __int16 SpriteWidth; // ax
  int v42; // edx
  int v43; // esi
  int v44; // ebx
  int v45; // ecx
  int v46; // ecx
  int v47; // edx
  int v48; // ecx
  unsigned int v49; // edx
  int v50; // eax
  int v51; // eax
  int v52; // ecx
  int v53; // edx
  unsigned int v54; // eax
  unsigned int v55; // edx
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
  BOOL v73; // eax
  int v74; // ecx
  int v75; // eax
  _DWORD *v76; // eax
  int v77; // eax
  _DWORD *v78; // eax
  char v79; // bl
  char v80; // al
  unsigned __int8 v81; // bl
  int v82; // edx
  int v83; // ecx
  int v84; // ebx
  int v85; // edx
  int v86; // ecx
  int v87; // ecx
  int v88; // esi
  int v89; // ecx
  unsigned int v90; // eax
  unsigned int v91; // edx
  int v92; // ecx
  int v93; // edx
  int v94; // ecx
  int v95; // ecx
  int v96; // edi
  int v97; // ecx
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
  unsigned __int8 *v113; // [esp+2D6h] [ebp+26h]
  int v115; // [esp+2E2h] [ebp+32h]
  int v116; // [esp+2E6h] [ebp+36h]
  int v117; // [esp+2EAh] [ebp+3Ah]
  int v118; // [esp+2EEh] [ebp+3Eh]
  int v119; // [esp+2F2h] [ebp+42h]
  int v122; // [esp+302h] [ebp+52h]
  int v123; // [esp+306h] [ebp+56h]
  int v124; // [esp+30Ah] [ebp+5Ah]
  __int16 *v125; // [esp+30Eh] [ebp+5Eh]
  unsigned int v126; // [esp+312h] [ebp+62h]
  int v127; // [esp+316h] [ebp+66h]
  int v128; // [esp+31Ah] [ebp+6Ah]
  int v129; // [esp+31Eh] [ebp+6Eh]
  int v130; // [esp+322h] [ebp+72h]
  int v131; // [esp+326h] [ebp+76h]
  int v132; // [esp+32Ah] [ebp+7Ah]
  int v133; // [esp+32Eh] [ebp+7Eh]

  v122 = a4;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  v125 = (__int16 *)(g_MapData + 852 + 31 * a1);
  if ( a2 == -1 )
  {
    LOBYTE(a4) = 0;
    v113 = 0;
  }
  else
  {
    v113 = (unsigned __int8 *)(31 * a2 + g_MapData + 852);
  }
  Debug_Log(a2, a4, (DWORD)v111, (int)a_shotanimDDDDD);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)v125[2], (unsigned __int16)v125[3]) || !UnitBattle_IsTileInViewport(v122, a3) )
  {
    *(_DWORD *)(g_MapData + 808) = (v122 + (unsigned __int16)v125[2]) / 2 - 3;
    *(_DWORD *)(g_MapData + 812) = (a3 + (unsigned __int16)v125[3]) / 2 - 3;
    if ( *(int *)(g_MapData + 808) < 0 )
      *(_DWORD *)(g_MapData + 808) = 0;
    v96 = *(_DWORD *)(g_MapData + 804);
    if ( *(_DWORD *)(g_MapData + 808) + 7 > v96 )
      *(_DWORD *)(g_MapData + 808) = v96 - 7;
    if ( *(int *)(g_MapData + 812) < 0 )
      *(_DWORD *)(g_MapData + 812) = 0;
    v97 = *(_DWORD *)(g_MapData + 800);
    if ( *(_DWORD *)(g_MapData + 812) + 7 > v97 )
      *(_DWORD *)(g_MapData + 812) = v97 - 7;
    UnitBattle_RedrawVisibleGrid();
  }
  *((_BYTE *)v125 + 3) = Facing_DirectionFromDelta8(v122 - (unsigned __int16)v125[2], a3 - (unsigned __int16)v125[3]);
  v16 = *((_BYTE *)v125 + 2);
  Unit_BuildShotAnimSpritePath(v110, *(_BYTE *)v125, v16);
  v18 = (_DWORD *)Mem_Alloc(4112, v17, v16, (DWORD)v111);
  if ( v18 )
    v18 = DLXSpriteSet_Load(v18, v16);
  g_ActiveUnitAnimSpriteSet = (int)v18;
  v19 = 0;
  g_UnitMoveAnimOffsetX = 0;
  g_ActiveUnitMoveTileIndex = a1;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeShotAnimationFrameCount[88 * *v125];
  if ( a2 != -1 )
  {
    v19 = v113[2];
    Unit_BuildGoSpriteFilePath(v110, *v113, v19);
    v21 = (_DWORD *)Mem_Alloc(4112, v20, v19, (DWORD)v111);
    if ( v21 )
      v21 = DLXSpriteSet_Load(v21, v19);
    g_UnitBattleAnimatingUnitSpriteSet = (int)v21;
  }
  qmemcpy(v109, &g_UnitBattleShotAnimTemplate, sizeof(v109));
  Unit_BuildShotAnimPaletteSpritePath(v112, *(_BYTE *)v125);
  v131 = 0;
  if ( DLX_OpenArchive(v112, v22) )
  {
    v24 = (_DWORD *)Mem_Alloc(4112, v23, v19, (DWORD)v111);
    if ( v24 )
      v24 = DLXSpriteSet_Load(v24, v19);
    v131 = (int)v24;
  }
  v25 = v131;
  Debug_Log(-1, v131, (DWORD)v111, (int)aLoaded);
  v132 = v27;
  v28 = g_UnitBattleAnimFrameCount - 1;
  if ( v131 )
  {
    *(_DWORD *)((char *)&a7 + 2) = 32 - (unsigned __int16)DLX_GetSpriteHeight(v131, 0) / 2;
    v26 = 32 - (unsigned __int16)DLX_GetSpriteWidth(v131, 0) / 2;
    *(_DWORD *)((char *)&a7 + 6) = v26;
  }
  v29 = *v125;
  if ( (unsigned __int16)*v125 >= 0xFu )
  {
    if ( (unsigned __int16)*v125 <= 0xFu )
    {
      v28 = 26;
      v26 = *((unsigned __int8 *)v125 + 3);
      *(_DWORD *)((char *)&a16 + 2) = 5;
      v99 = &v109[8 * v26 + 256];
      v132 = 5 * v26;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v99;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v99 + 1);
      *(_DWORD *)((char *)&a7 + 10) = 6;
    }
    else if ( v29 >= 0x1Cu )
    {
      if ( v29 <= 0x1Cu )
      {
        v28 = 3;
        v132 = 8 * *((unsigned __int8 *)v125 + 3);
        v26 = 6;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[v132 + 192];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[v132 + 196];
      }
      else if ( v29 == 30 )
      {
        v26 = (int)v125;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        v28 = 8;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        v132 = 8 * *((unsigned __int8 *)v125 + 3);
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[v132];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[v132 + 4];
      }
    }
    else if ( v29 == 20 )
    {
      v25 = 1;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      v132 = 0;
      v100 = &v109[8 * *((unsigned __int8 *)v125 + 3) + 320];
      *(_DWORD *)((char *)&a16 + 2) = 1;
      v28 = 6;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v100;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v100 + 1);
    }
  }
  else if ( v29 >= 0xAu )
  {
    if ( v29 <= 0xAu )
    {
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      v26 = *((unsigned __int8 *)v125 + 3);
      v98 = &v109[8 * v26 + 128];
      v28 = 4;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v98;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v98 + 1);
      v132 = 5 * v26;
    }
    else if ( v29 == 12 )
    {
      v26 = 0;
      v25 = 2;
      v132 = 0;
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 2;
      v28 = 1;
    }
  }
  else if ( v29 == 9 )
  {
    v28 = 6;
    v26 = *((unsigned __int8 *)v125 + 3);
    *(_DWORD *)((char *)&a7 + 10) = 6;
    v30 = &v109[8 * v26 + 64];
    v132 = 5 * v26;
    *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v30;
    *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v30 + 1);
    *(_DWORD *)((char *)&a16 + 2) = 5;
  }
  v124 = Time_Now(v28, v26);
  if ( v31 >= g_UnitAnimFrameIndex )
  {
    v32 = 31 * a1;
    do
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v25);
      v25 = v124;
      v34 = Time_Now(v33, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(v32 + g_MapData + 852)]);
      if ( v34 - v124 >= v36 )
      {
        v37 = *(__int16 *)(v32 + g_MapData + 852);
        v38 = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * v37];
        if ( v38 == g_UnitAnimFrameIndex )
          Audio_PlayUnitRangedAttackSound(v37);
        v124 = Time_Now(v35, v38);
        UnitBattle_RedrawTile(*(unsigned __int16 *)(v32 + g_MapData + 856), *(unsigned __int16 *)(v32 + g_MapData + 858));
        ++g_UnitAnimFrameIndex;
      }
    }
    while ( v35 >= g_UnitAnimFrameIndex );
  }
  if ( v132 != -1 )
  {
    v39 = (unsigned __int16)DLX_GetSpriteHeight(v131, v132) / 2;
    SpriteWidth = DLX_GetSpriteWidth(v131, v40);
    v42 = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *v125];
    v118 = (((unsigned __int16)v125[2] - *(_DWORD *)(g_MapData + 808)) << 6)
         + 32
         + *(_DWORD *)((char *)&a7 + 2)
         - v42;
    v43 = *(_DWORD *)((char *)&a7 + 6) + (((unsigned __int16)v125[3] - *(_DWORD *)(g_MapData + 812)) << 6) + 16 - v42;
    v119 = v43;
    v123 = ((v122 - *(_DWORD *)(g_MapData + 808)) << 6) + 64 - v39;
    v115 = ((a3 - *(_DWORD *)(g_MapData + 812)) << 6) + 48 - SpriteWidth / 2;
    v133 = v118;
    v44 = v115 - v43;
    v127 = Math_CeilSqrt(v44 * v44 + (v123 - v118) * (v123 - v118)) / *(_DWORD *)((char *)&a7 + 10);
    v130 = Time_Now(v45, a1);
    v116 = v46;
    v117 = v115 - v43;
    v128 = 31 * v47;
    while ( 1 )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v44);
      v48 = g_UnitBattleAnimFrameCount;
      v49 = g_UnitAnimFrameIndex % g_UnitBattleAnimFrameCount;
      g_UnitAnimFrameIndex = v49;
      if ( v49 )
      {
        v50 = Time_Now(v128, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(v128 + g_MapData + 852)]);
        if ( v50 - v124 >= v49 )
        {
          v51 = *(__int16 *)(v48 + g_MapData + 852);
          v52 = g_UnitAnimFrameIndex;
          v53 = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * v51];
          if ( v53 == g_UnitAnimFrameIndex )
            Audio_PlayUnitRangedAttackSound(v51);
          v124 = Time_Now(v52, v53);
          UnitBattle_RedrawTile(*(unsigned __int16 *)(v128 + g_MapData + 856), *(unsigned __int16 *)(v128 + g_MapData + 858));
          v48 = g_UnitBattleAnimFrameCount;
          v49 = (g_UnitAnimFrameIndex + 1) % g_UnitBattleAnimFrameCount;
          g_UnitAnimFrameIndex = v49;
        }
      }
      g_RenderDevice = &g_MainRenderDevice;
      if ( *v125 == UNIT_TYPE_CATAPULT )
      {
        v54 = 8 * (Time_Now(v48, v49) - v130) / (unsigned int)v127;
        v55 = v54 - 4;
        if ( (int)(v54 - 4) <= 0 )
          v55 = 4 - v54;
        v126 = 4 - v55;
      }
      else
      {
        v126 = (Time_Now(v48, v49) - v130) / 0xAu % *(_DWORD *)((char *)&a16 + 2);
      }
      v129 = v133;
      Render_SaveBackbuffer((int)&g_MainRenderDevice);
      v56 = v43;
      v108 = v43 + DLX_GetSpriteWidth(v131, v57);
      SpriteHeight = DLX_GetSpriteHeight(v131, v132);
      v59 = v133;
      if ( v43 >= v133 )
        v59 = v43;
      RenderState_PumpIfRectInViewBounds(g_RenderState, v133, v59 + SpriteHeight, v43, v108);
      v60 = v43 + (unsigned __int16)DLX_GetSpriteWidth(v131, v132) + 1;
      if ( v60 > 464 )
        LOWORD(v60) = 464;
      if ( v43 < 16 )
        LOWORD(v43) = 16;
      v107 = v60;
      v61 = DLX_GetSpriteHeight(v131, v132);
      Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, v62, (unsigned __int16)v133, v133 + v61 + 1, v107, v133, v43);
      v65 = Time_Now(v64, v63);
      v66 = Time_Now(v130, (v65 - v130) * v116 / v127 + v118);
      v133 = v67;
      v25 = v67;
      v43 = (v66 - v68) * v117 / v127 + v119;
      v69 = v123 - v67;
      if ( v123 - v67 <= 0 )
      {
        if ( v123 != v67 )
          v69 = -1;
      }
      else
      {
        v69 = 1;
      }
      v70 = v69;
      v71 = v123 - v129;
      if ( v123 - v129 <= 0 )
      {
        if ( v123 != v129 )
          v71 = -1;
      }
      else
      {
        v71 = 1;
      }
      if ( v70 != v71 )
        break;
      v101 = v115 - v43;
      if ( v115 - v43 <= 0 )
      {
        if ( v115 != v43 )
          v101 = -1;
      }
      else
      {
        v101 = 1;
      }
      v102 = v101;
      v103 = v115 - v56;
      if ( v115 - v56 <= 0 )
      {
        if ( v115 != v56 )
          v103 = -1;
      }
      else
      {
        v103 = 1;
      }
      if ( v102 != v103 )
        break;
      SpriteForChar = DLX_GetSpriteForChar(v131, v126 + v132);
      LOBYTE(v44) = v133;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        v43,
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
  UnitBattle_RedrawTile(*(unsigned __int16 *)(g_MapData + 31 * a1 + 856), *(unsigned __int16 *)(g_MapData + 31 * a1 + 858));
  v72 = *v125;
  v73 = v72 == UNIT_TYPE_CATAPULT
     || v72 == UNIT_TYPE_CANNON
     || v72 == UNIT_TYPE_DRAGON
     || v72 == UNIT_TYPE_WINGER
     || v72 == UNIT_TYPE_WIZARD;
  v74 = v73;
  if ( v73 )
  {
    v75 = *v125;
    if ( v75 == UNIT_TYPE_CATAPULT || v75 == UNIT_TYPE_CANNON )
    {
      v76 = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( v76 )
LABEL_55:
        v76 = DLXSpriteSet_Load(v76, v25);
    }
    else
    {
      if ( v75 != 24 )
      {
LABEL_57:
        v77 = *v125;
        if ( v77 == UNIT_TYPE_DRAGON || v77 == UNIT_TYPE_WINGER )
        {
          v78 = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
          if ( v78 )
            v78 = DLXSpriteSet_Load(v78, v25);
          g_UnitBattleProjectileSpriteSet = (int)v78;
        }
        g_UnitBattleShotProjectileTileX = v122;
        g_UnitBattleShotProjectileTileY = a3;
        g_BattleShotAnimFrameIndex = 0;
        Audio_PlayUnitShotSound(*(__int16 *)(g_MapData + 31 * a1 + 852));
        goto LABEL_62;
      }
      v76 = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( v76 )
        goto LABEL_55;
    }
    g_UnitBattleProjectileSpriteSet = (int)v76;
    goto LABEL_57;
  }
LABEL_62:
  if ( v113 )
  {
    if ( (g_UnitTypeFlags[22 * *(__int16 *)v113] & 1) != 0 )
    {
      v79 = v113[17] & 7;
      v80 = (v79 + Rng_RandRange(2, 5)) & 7;
      v81 = v113[17] & 0xF8;
      v113[17] = v81;
      v113[17] = v80 & 7 | v81;
    }
    else
    {
      g_UnitBattleAnimatingUnitIndex = a2;
    }
  }
  g_UnitBattleHitAnimFrame = Rng_RandRange(3, 7);
  if ( v113 )
    Audio_PlayUnitHitSound(*(__int16 *)v113);
  v84 = Time_Now(v83, v82);
  v88 = Time_Now(v86, v85);
  while ( v87 && (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) >= g_BattleShotAnimFrameIndex || v113 && g_UnitBattleHitAnimFrame )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    v90 = Time_Now(v89, v84 + 5);
    if ( v90 >= v91 && v113 )
    {
      v93 = g_UnitBattleHitAnimFrame;
      if ( g_UnitBattleHitAnimFrame )
        g_UnitBattleHitAnimFrame = ((_BYTE)g_UnitBattleHitAnimFrame + 1) & 7;
      UnitBattle_RedrawUnitNeighborhood(a2);
      v84 = Time_Now(v94, v93);
    }
    g_BattleShotAnimFrameIndex = (unsigned int)(Time_Now(v92, v91) - v88) >> 1;
    if ( v95 )
    {
      if ( (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) <= g_BattleShotAnimFrameIndex )
        break;
    }
    UnitBattle_RedrawTile(v122, a3);
  }
  g_UnitBattleShotProjectileTileY = -1;
  g_UnitBattleShotProjectileTileX = -1;
  UnitBattle_RedrawTile(v122, a3);
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
int  UnitBattle_CalcShotTargetHealthAfterHit(int a1, int a2)
{
  int v3; // ebx
  __int16 *v4; // esi
  signed int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int result; // eax

  v3 = g_MapData + 852 + 31 * a1;
  v4 = (__int16 *)(31 * a2 + g_MapData + 852);
  Unit_CalcEffectivenessC((__int16 *)v3);
  Math_CeilSqrt(
    (*(unsigned __int16 *)(v3 + 4) - (unsigned __int16)v4[2])
  * (*(unsigned __int16 *)(v3 + 4) - (unsigned __int16)v4[2])
  + (*(unsigned __int16 *)(v3 + 6) - (unsigned __int16)v4[3])
  * (*(unsigned __int16 *)(v3 + 6) - (unsigned __int16)v4[3]));
  v5 = UnitBattle_GetTargetCrowdingScale((int)v4);
  v8 = v7 / v5 * (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *v4];
  v9 = (v8 - (__CFSHL__(v8 >> 31, 8) + (v8 >> 31 << 8))) >> 8;
  if ( v9 < 1 )
    goto LABEL_2;
  if ( v9 >= 2 )
  {
    v6 *= 3;
LABEL_2:
    v10 = 2 * v6;
    goto LABEL_3;
  }
  v10 = 4 * v6;
LABEL_3:
  result = *(char *)(g_MapData + 31 * a2 + 861) - v10;
  if ( result < 0 )
    return 0;
  return result;
}
// 4296BD: variable 'v7' is possibly undefined
// 4296E6: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00429740) --------------------------------------------------------
int  UnitBattle_Shot(int a1, int a2)
{
  char *v3; // edi
  char *v4; // esi
  int v5; // eax
  int v6; // ecx
  unsigned __int16 v7; // dx
  unsigned __int16 v8; // ax

  Debug_Log(a1, a2, 0, (int)aUnitbattle_sho, a1, a2);
  v3 = (char *)(g_MapData + 852 + 31 * a1);
  v4 = (char *)(g_MapData + 852 + 31 * a2);
  if ( !UnitBattle_IsUnitWithinRange(a1, a2) )
    return 0;
  v5 = UNIT_SLOT_VOLLEYS_USED(v3);
  if ( v5 >= UNIT_SLOT_STATUS_LEVEL(v3) + 1 )
    return 0;
  if ( (unsigned __int8)v3[8] < 5u )
    return 0;
  v3[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(v3, v5 + 1);
  g_SelectedUnitIndex = a1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, a2, 0);
  UnitBattle_RedrawVisibleGrid();
  v4[9] = UnitBattle_CalcShotTargetHealthAfterHit(a1, a2);
  UnitBattle_PlayShotAnimation(
    a1,
    a2,
    *(unsigned __int16 *)(v4 + 6),
    *(unsigned __int16 *)(v4 + 4),
    (signed __int8)v4[9] <= 0,
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
  if ( (signed __int8)v4[9] <= 0 )
  {
    v7 = *(unsigned __int16 *)(v4 + 4);
    v8 = *(unsigned __int16 *)(v4 + 6);
    *(_BYTE *)(40 * v7 + g_MapData + 2 * v8 + 2334) = UnitBattle_GetCorpseSpriteIndex((__int16 *)v4);
    UnitBattle_PlayDeathAnimation(a2, 0, 0, 0);
    *(_WORD *)v4 = -1;
    *(_WORD *)(40 * v7 + g_MapData + 2 * v8 + 1534) = -1;
  }
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v3 + 2) + gameData + 140073) = 1;
  UnitBattle_RedrawVisibleGrid();
  return UnitBattle_DrawSelectedUnitPanel(0, 1, a2, 0), 1;
}

//----- (004298E0) --------------------------------------------------------
int  UnitBattle_AttackWall(int a1, DWORD a2, int a3, int a4)
{
  int result; // eax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  unsigned __int16 v10; // dx
  unsigned __int16 v11; // ax
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  DWORD v19; // [esp+4h] [ebp-1Ch]
  int v20; // [esp+8h] [ebp-18h]
  int wall_hp_before;
  int wall_hp_after;
  int unit_ap_before;
  int wall_kind;
  int wall_factor;
  int effective_wall_attack;
  int wall_damage;

  Debug_Log(a3, a4, a2, (int)aUnitbattle_a_0);
  if ( !g_UnitTypeBaseMeleeAttack_51257E[88 * *(__int16 *)(g_MapData + 31 * a1 + 852)] || !*(_BYTE *)(a4 + g_MapData + 20 * a2 + 3134) )
    return 0;
  g_SelectedUnitIndex = a1;
  v7 = g_MapData + 852 + 31 * a1;
  UnitBattle_RefreshSelectedUnitUI();
  v8 = *(unsigned __int16 *)(v7 + 4) - a2;
  if ( v8 <= 0 )
    v8 = a2 - *(unsigned __int16 *)(v7 + 4);
  if ( v8 > 1 )
    goto LABEL_18;
  v9 = *(unsigned __int16 *)(v7 + 6) - a4;
  if ( v9 <= 0 )
    v9 = a4 - *(unsigned __int16 *)(v7 + 6);
  if ( v9 )
  {
LABEL_18:
    result = (int)UnitBattle_MoveTrackNearWall(a1, a2, a4, a2);
    if ( !result )
      return result;
    *(_DWORD *)(v7 + 23) = result;
    UnitBattle_Move(a1, 0, 0, 0);
    v17 = *(_DWORD *)(v7 + 23);
    if ( v17 )
    {
      nfree_(v17);
      *(_DWORD *)(v7 + 23) = 0;
      return 0;
    }
    v18 = *(unsigned __int16 *)(v7 + 4) - a2;
    if ( v18 <= 0 )
      v18 = a2 - *(unsigned __int16 *)(v7 + 4);
    if ( v18 > 1 )
      return 0;
    if ( *(unsigned __int16 *)(v7 + 6) - a4 > 0 )
      return 0;
    if ( a4 != *(unsigned __int16 *)(v7 + 6) )
      return 0;
  }
  unit_ap_before = *(unsigned __int8 *)(v7 + 8);
  if ( unit_ap_before < 5u )
    return 0;
  *(_BYTE *)(v7 + 8) -= 5;
  v10 = *(_WORD *)(v7 + 6);
  v11 = *(_WORD *)(v7 + 4);
  *(_BYTE *)(v7 + 22) &= ~1u;
  if ( !UnitBattle_IsTileInViewport(v11, v10) || !UnitBattle_IsTileInViewport(a2, a4) )
  {
    UnitBattle_CenterViewOnUnit(a1);
    UnitBattle_RedrawVisibleGrid();
  }
  HIWORD(v12) = 0;
  *(_BYTE *)(v7 + 3) = Facing_DirectionFromDelta8(a2 - *(unsigned __int16 *)(v7 + 4), a4 - *(unsigned __int16 *)(v7 + 6));
  UnitBattle_PlayAttackAnimation(a1, -1, 0, 0, (unsigned __int16 *)a2);
  UnitBattle_RedrawTile(a2, a4);
  v20 = g_BattleWallGateLastSpriteChar;
  v19 = a4 + g_MapData + 20 * a2;
  wall_hp_before = *(unsigned __int8 *)(v19 + 3134);
  wall_kind = *(_DWORD *)(g_MapData + 820);
  wall_factor = (unsigned __int16)g_WallKindDefenseFactor[2 * wall_kind];
  effective_wall_attack = Unit_CalcEffectivenessD((char *)v7, 0);
  wall_damage = wall_factor * effective_wall_attack / 256;
  *(_BYTE *)(v19 + 3134) -= wall_damage;
  wall_hp_after = *(unsigned __int8 *)(v19 + 3134);
  v15 = v19;
  if ( *(char *)(v15 + 3134) <= 0 )
  {
    *(_BYTE *)(v15 + 3134) = 0;
    if ( a4 == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
    wall_hp_after = *(unsigned __int8 *)(v15 + 3134);
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[battle] wall_attack unit=%d type=%d tile=%lu,%d ap_before=%d ap_after=%d wall_before=%d wall_after=%d wall_kind=%d wall_factor=%d effective_wall_attack=%d wall_damage=%d gate_column=%d gate_state=%d battle_result=%d\n",
      a1,
      *(__int16 *)v7,
      (unsigned long)a2,
      a4,
      unit_ap_before,
      *(unsigned __int8 *)(v7 + 8),
      wall_hp_before,
      wall_hp_after,
      wall_kind,
      wall_factor,
      effective_wall_attack,
      wall_damage,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 832),
      g_BattleWallGateLastSpriteChar);
  UnitBattle_RedrawTile(a2, a4);
  if ( v20 != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName(aBattleMurek, 64);
  UnitBattle_RedrawTile(a2 + 1, a4);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v7 + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, v12, a4);
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
int  UnitBattle_ShotWall(int a1, int a2)
{
  char *v3; // esi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax

  v4 = g_BattleTargetTileCol;
  Debug_Log(a1, a2, v4, (int)aUnitbattle_s_0, a1, a2, v4);
  v3 = (char *)(g_MapData + 852 + 31 * a1);
  if ( !UnitBattle_IsTileWithinRange(a1, a2, v4) )
    return 0;
  v5 = UNIT_SLOT_VOLLEYS_USED(v3);
  if ( v5 >= UNIT_SLOT_STATUS_LEVEL(v3) + 1 )
    return 0;
  if ( (unsigned __int8)v3[8] < 5u )
    return 0;
  v3[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(v3, v5 + 1);
  g_SelectedUnitIndex = a1;
  UnitBattle_PlayShotAnimation(a1, -1, v4, a2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  UnitBattle_RedrawTile(a2, v4);
  v10 = g_BattleWallGateLastSpriteChar;
  v6 = Unit_CalcEffectivenessC((__int16 *)v3);
  v7 = (unsigned __int16)*(unsigned __int16 *)(v3 + 4) - a2;
  if ( v7 < 0 )
    v7 = a2 - *(unsigned __int16 *)(v3 + 4);
  v8 = *(unsigned __int16 *)(v3 + 6) - v4;
  if ( v8 < 0 )
    v8 = v4 - *(unsigned __int16 *)(v3 + 6);
  v9 = Math_CeilSqrt(v7 * v7 + v8 * v8);
  if ( *(__int16 *)v3 == UNIT_TYPE_CANNON && v9 > 4 )
    v6 = 9 * v6 / 10;
  if ( *(__int16 *)v3 == UNIT_TYPE_CATAPULT && v9 > 3 )
    v6 = 9 * v6 / 10;
  v11 = g_MapData + 40 * a2;
  LOWORD(v12) = g_WallKindDefenseFactor[2 * *(_DWORD *)(g_MapData + 820)];
  v13 = *(signed __int8 *)(v11 + v4 + 3134) - ((v6 * (unsigned __int16)v12) >> 8);
  *(_BYTE *)(v11 + v4 + 3134) = v13;
  if ( v13 <= 0 )
  {
    *(_BYTE *)(v11 + v4 + 3134) = 0;
    if ( v4 == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
  }
  UnitBattle_RedrawTile(a2, v4);
  if ( v10 != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName((int)aBattleMurek_0, 64);
  UnitBattle_RedrawTile(a2 + 1, v4);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v3 + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, a2, v4);
  UnitBattle_RedrawUnitFootprint(a1);
  return 1;
}

//----- (00429E30) --------------------------------------------------------
signed int  UnitBattle_Defence(int a1, char a2, DWORD a3)
{
  int v5; // edx

  Debug_Log(a1, a2, a3, (int)aUnitbattle_def);
  v5 = 31 * a1;
  if ( *(unsigned __int8 *)(g_MapData + v5 + 860) < 5u )
    return 0;
  *(_BYTE *)(g_MapData + v5 + 860) = 0;
  *(_BYTE *)(v5 + g_MapData + 874) |= 1u;
  return 1;
}
// 532048: using guessed type int g_MapData;

//----- (00429E90) --------------------------------------------------------
int  BuildCursor_HandleCancelButtonPress(int a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
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
  __int64 v1; // kr00_8
  int v2; // edi
  int v3; // esi
  int v4; // ebp
  int v5; // ebp
  int SpriteForChar; // eax
  unsigned __int16 v8; // [esp+4h] [ebp-2Ch]

  v1 = result;
  v2 = (((_DWORD)result - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 32;
  v3 = ((HIDWORD(result) - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 16;
  if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) == 1 )
    v8 = 215;
  else
    v8 = 76;
  if ( !g_BuildCursorBuildingType || g_BuildCursorBuildingType == 3 )
  {
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY);
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) )
      {
        if ( BuildCursor_IsPlacementValid(v1, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex)
          && v1 != __PAIR64__(
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)) )
        {
          LODWORD(result) = (*(int (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 24))(
                              (unsigned __int16)(v2 + 63),
                              (unsigned __int16)v2,
                              (unsigned __int16)(v3 + 63),
                              (unsigned __int8)v8);
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
        v2 = (unsigned __int16)v2;
        (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          (unsigned __int16)(v2 + 63),
          (unsigned __int16)v2,
          (unsigned __int16)v3,
          v8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v2,
                            v2,
                            (unsigned __int16)(v3 + 63),
                            v8);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY), (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(result), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v4 = (unsigned __int16)(v2 + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v4,
          (unsigned __int16)v2,
          (unsigned __int16)v3,
          v8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v4,
                            v4,
                            (unsigned __int16)(v3 + 63),
                            v8);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY) + 1, (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v5 = (unsigned __int16)(v2 + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v5,
          (unsigned __int16)v2,
          (unsigned __int16)(v3 + 63),
          v8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v5,
                            v5,
                            (unsigned __int16)(v3 + 63),
                            v8);
        return result;
      }
      goto LABEL_26;
    }
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY) + 1;
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) + 1 )
      {
        if ( BuildCursor_IsPlacementValid(v1, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
        {
          v2 = (unsigned __int16)v2;
          (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
            (unsigned __int16)(v2 + 63),
            (unsigned __int16)v2,
            (unsigned __int16)(v3 + 63),
            v8);
          LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                              v2,
                              v2,
                              (unsigned __int16)(v3 + 63),
                              v8);
          return result;
        }
LABEL_26:
        SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
                            v3,
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
int  BuildBuilding(int a1, int a2, char a3, double a4)
{
  DWORD v5; // eax
  char v6; // cl
  int v7; // edx
  int v8; // ebx
  unsigned int v9; // edx
  int v10; // esi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  DWORD v17; // eax
  int v18; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22[9]; // [esp+0h] [ebp-24h] BYREF

  Debug_Log(a2, a3, a1, (int)aBuildbuildingD, a1);
  g_BuildCursorBuildingType = a1;
  v5 = 53 * (a1 + 2);
  g_BuildPlacementLoopDone = 0;
  v6 = g_CursorCoordShift;
  v7 = g_MouseCursorRawX >> g_CursorCoordShift;
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + v5) = 2;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + v5) = BuildCursor_HandleCancelButtonPress;
  v8 = gameData;
  g_WorldMapTileOverlayDrawHook = (int (__fastcall *)(_DWORD, _DWORD))BuildCursor_DrawPlacementOverlay;
  LODWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)
                        + ((v7 - 32 - (__CFSHL__((v7 - 32) >> 31, 6) + ((v7 - 32) >> 31 << 6))) >> 6);
  HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                        + (((g_MouseCursorRawY >> v6)
                          - 16
                          - (__CFSHL__(((g_MouseCursorRawY >> v6) - 16) >> 31, 6)
                           + (((g_MouseCursorRawY >> v6) - 16) >> 31 << 6))) >> 6);
  WorldMap_RedrawViewport(1);
  while ( !g_BuildPlacementLoopDone )
  {
    DD_Pump((int)&g_RenderState, v8, (char)BuildCursor_DrawPlacementOverlay);
    WorldMap_RedrawFrame(v8);
    if ( !UIWidgetTable_PollHoverAndActions((int)&g_BuildBuildingActionWidgetTable, a1) && UI_TrySelectFriendlyStackUnderCursor() )
    {
      Render_Begin((int)&g_RenderState, 0, (char)BuildCursor_DrawPlacementOverlay);
      break;
    }
    WorldMap_HandleScrollKeysAndIdle(v9);
    v10 = (((g_MouseCursorRawX >> g_CursorCoordShift)
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
           v10) != g_BuildPlacementTileXY )
    {
      v8 = HIDWORD(g_BuildPlacementTileXY);
      HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                            + (((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6);
      v11 = g_BuildPlacementTileXY;
      LODWORD(g_BuildPlacementTileXY) = v10;
      WorldMap_RedrawTileIfVisible(v11, v8);
      if ( a1 == 2 || a1 == 1 )
      {
        v13 = v12 + 1;
        v14 = v8++;
        WorldMap_RedrawTileIfVisible(v12 + 1, v14);
        WorldMap_RedrawTileIfVisible(v15, v8);
        WorldMap_RedrawTileIfVisible(v13, v8);
      }
      WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY));
      if ( a1 == 2 || a1 == 1 )
      {
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, SHIDWORD(g_BuildPlacementTileXY));
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, HIDWORD(g_BuildPlacementTileXY) + 1);
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, HIDWORD(g_BuildPlacementTileXY) + 1);
      }
    }
    if ( DD_IsFlipping((int)&g_RenderState) )
    {
      if ( a1 == 3 )
      {
        v8 = g_SelectedUnitIndex;
        if ( Trap_New(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY), v16, g_SelectedUnitIndex, a4) == 1 )
        {
          Win_PlayModeChangeFrameTransition(aZakl_pul, 1, v20, v8, 3u);
          v22[0] = (int)g_BuildBuildingCompletionMessageStrings[0];
          v22[1] = (int)g_BuildBuildingCompletionMessageStrings[1];
          v22[2] = (int)g_BuildBuildingCompletionMessageStrings[2];
          UI_ShowInfoWindow(v22[(unsigned __int8)g_LanguageIndex], 0, v21, 3u, (int)&v22[3], (int)&g_BuildBuildingCompletionMessageStrings[3]);
          Render_Begin((int)&g_RenderState, 0, (char)&v22[3]);
          g_BuildPlacementLoopDone = 1;
          break;
        }
      }
      else
      {
        v8 = g_SelectedUnitIndex;
        if ( ((BOOL (__cdecl *)(__int64, int, int, double, char *, int))Building_New)(
               g_BuildPlacementTileXY,
               a1,
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
  v17 = 53 * (a1 + 2);
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + v17) = 1;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + v17) = (int (*)())BuildCursor_RequestExit;
  UIWidget_RefreshActionButtonState((int)&g_BuildBuildingActionWidgetTable + v17, 1);
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
int  UI_DrawNoticeBoxSmall(DWORD a1, int a2)
{
  int v2; // edx
  int SpriteForChar; // eax
  int tax_rate; // ecx

  g_RenderDevice = &g_MainRenderDevice;
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 198, 208, 0x104u, 0xDAu, 0xD0u, 0xC6u);
  Render_ReleaseSurface(5, a1);
  tax_rate = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  UI_DrawTextFmt(208, 208, 260, 198, 3, aD_D, tax_rate / 10, tax_rate % 10);
  if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4 <= 0
    || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
  {
    if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4
      || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
      v2 = 4;
    else
      v2 = 3;
  }
  else
  {
    v2 = 5;
  }
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingEconomyDialogSpriteSet, v2);
  return Compat_RenderDeviceDrawMenuSprite(383, 19, SpriteForChar, 0);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CE4: using guessed type int g_BuildingEconomyDialogSpriteSet;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;

//----- (0042A890) --------------------------------------------------------
int  UI_DrawConfirmTop(DWORD a1, int a2)
{
  void *v2; // esi
  int result; // eax

  v2 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, a1);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 360, 548, 0x259u, 0x17Cu, 0x224u, 0x168u);
  result = UI_DrawTextFmt(548, 548, 601, 360, 3, aD_8, g_BuildingEconomyDialogPendingPeasantTransfer);
  g_RenderDevice = v2;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;

//----- (0042A910) --------------------------------------------------------
int  UI_DrawConfirmBottom(DWORD a1, int a2)
{
  void *v2; // esi
  int result; // eax

  v2 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, a1);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x124u, 0x224u, 0x110u);
  result = UI_DrawTextFmt(548, 548, 601, 272, 3, aD_9, g_BuildingEconomyDialogPendingGoldTransfer);
  g_RenderDevice = v2;
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
int  BuildingEconomyDialog_SetExitSignal(int a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay((uintptr_t)a1, 1);
  g_BuildingEconomyDialogExitSignal = 1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[economy] back exit_signal=%d\n", g_BuildingEconomyDialogExitSignal);
  return result;
}
// 531CE8: using guessed type int g_BuildingEconomyDialogExitSignal;

//----- (0042A9B0) --------------------------------------------------------
int  BuildingEconomyDialog_CommitTransfers(
        int a1,
        int a2,
        DWORD a3,
        char a4,
        double a5)
{
  int v5; // eax
  int v6; // esi
  int v7; // esi

  UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  if ( g_BuildingEconomyDialogPendingPeasantTransfer )
  {
    v5 = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( v5 == -2 || *(_BYTE *)(BUILDING_RECORD_SIZE * v5 + gameData + 509678) != 1 )
    {
      v6 = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
      if ( v6 == -2 )
        v6 = -1;
      a4 = -45;
      Building_Transfer(
        (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
        v6,
        0,
        g_BuildingEconomyDialogPendingPeasantTransfer,
        a5);
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    }
  }
  if ( g_BuildingEconomyDialogPendingGoldTransfer )
  {
    v7 = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( v7 == -2 )
      v7 = -1;
    a4 = -45;
    Building_Transfer(
      (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
      v7,
      1,
      g_BuildingEconomyDialogPendingGoldTransfer,
      a5);
    g_BuildingEconomyDialogPendingGoldTransfer = 0;
  }
  UI_DrawConfirmTop(a3, a4);
  UI_DrawConfirmBottom(a3, a4);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 20, 200, 0x17Cu, 0x41u, 0xC8u, 0x14u);
  Render_ReleaseSurface(16, a3);
  UI_DrawTextFmt((int)&g_MainRenderDevice, 0, 370, 20, 2, (int)aD_47);
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 30, 545, 0x25Au, 0x32u, 0x221u, 0x1Eu);
  Render_ReleaseSurface(5, a3);
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
int  BuildingEconomyDialog_DecreaseTaxRate(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // eax
  char v7; // dl
  int v8; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  unsigned int v16; // eax
  char v17; // dl
  int v18; // eax
  char v19; // dh
  int v20; // ecx
  char v22; // dh

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  v6 = g_BuildingEconomyDialogBuilding;
  v7 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436);
  if ( (v7 & 0x3F) != 0 )
  {
    v22 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = v22;
    *(_BYTE *)(v6 + 436) = ((v7 & 0x3F) - 1) & 0x3F | v22;
  }
  v8 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)g_RenderState, v8);
    v11 = Time_Now(v10, v9);
    v13 = Time_Now(v12, v11);
    v16 = (v14 - v15) * (v13 - v15) / 0x15Eu;
    v17 = v8 - v16;
    if ( (int)(v8 - v16) < 0 )
      v17 = 0;
    v18 = g_BuildingEconomyDialogBuilding;
    v19 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = v19;
    *(_BYTE *)(v18 + 436) = v17 & 0x3F | v19;
    UI_DrawNoticeBoxSmall((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v20);
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
int  BuildingEconomyDialog_IncreaseTaxRate(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // eax
  char v7; // dl
  char v8; // dh
  int v9; // ebx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // eax
  int v19; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  v6 = g_BuildingEconomyDialogBuilding;
  v7 = ((*(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F) + 1) & 0x3F;
  v8 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
  *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = v8;
  *(_BYTE *)(v6 + 436) = v7 | v8;
  v9 = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)g_RenderState, v9);
    v12 = Time_Now(v11, v10);
    v14 = Time_Now(v13, v12);
    v17 = v9 + (v15 - v16) * (v14 - v16) / 0x15Eu;
    if ( v17 > 40 )
      LOBYTE(v17) = 40;
    v18 = g_BuildingEconomyDialogBuilding;
    BYTE1(v17) = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) = BYTE1(v17);
    *(_BYTE *)(v18 + 436) = v17 & 0x3F | BYTE1(v17);
    UI_DrawNoticeBoxSmall(0x15Eu, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v19);
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
int  BuildingTransferDialog_DecreasePeasantTransferAmount(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer -= 10;
  v6 = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)g_RenderState, v6);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((v6 - (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer < 0 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    UI_DrawConfirmTop((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v14);
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
int  BuildingTransferDialog_IncreasePeasantTransferAmount(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  unsigned __int16 v14; // ax
  int v15; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer += 10;
  v6 = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)g_RenderState, v6);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((v6 + (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer > 1000 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 1000;
    v14 = *(_WORD *)(g_BuildingEconomyDialogBuilding + 430);
    HIBYTE(v14) &= 0xFu;
    if ( v14 < g_BuildingEconomyDialogPendingPeasantTransfer )
      g_BuildingEconomyDialogPendingPeasantTransfer = v14;
    UI_DrawConfirmTop(0xAu, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v15);
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
int  BuildingTransferDialog_DecreaseGoldTransferAmount(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer -= 10;
  v6 = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)g_RenderState, v6);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((v6 - (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer < 0 )
      g_BuildingEconomyDialogPendingGoldTransfer = 0;
    UI_DrawConfirmBottom((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v14);
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
int  BuildingTransferDialog_IncreaseGoldTransferAmount(int a1, char a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  DWORD v14; // ebp
  int v15; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  DD_Pump((int)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer += 10;
  v6 = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)g_RenderState, v6);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((v6 + (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > 1000 )
      g_BuildingEconomyDialogPendingGoldTransfer = 1000;
    v14 = *(_DWORD *)(g_BuildingEconomyDialogBuilding + 438);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > v14 )
      g_BuildingEconomyDialogPendingGoldTransfer = *(_DWORD *)(g_BuildingEconomyDialogBuilding + 438);
    UI_DrawConfirmBottom(v14, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v15);
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
int  BuildingEconomyDialog_Run(int a1)
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

  g_BuildingEconomyDialogBuilding = a1;
  building_index = (a1 - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] enter building_idx=%d owner=%d\n",
      building_index,
      *(unsigned __int8 *)(a1 + 2));
  Diagnostics_ResetFrameDumpOnEconomyEnter();
  player_has_religion = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(a1 + 2));
  BuildingTransferTargetList_Rebuild(a1, 1);
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
  UI_DrawTextFmt(267, 267, 343, 90, 2, aD_32, *(signed char *)(a1 + 434));
  UI_DrawTextFmt(444, 444, 503, 198, 3, aD_33, *(unsigned __int16 *)(a1 + 442));
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
BOOL  Trap_CanPlaceAtTile(int a1, int a2)
{
  int v3; // ecx
  BOOL result; // eax
  signed int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  result = 0;
  if ( !Trap_GetTileOwnerMask(a1, a2, g_CurrentPlayerIndex) )
  {
    v5 = Map_GetTileSurfaceClassOrUnexplored(v3, a2);
    if ( v5 != 185
      && v5 != 39
      && v5 != 204
      && v5 != 202
      && v5 != 147
      && v5 != 1
      && !MapTile_IsCastleFoundationTile(v6, a2, 2)
      && *(unsigned __int16 *)(TILE_INDEX(v7, a2)) == 0xFFFF
      && !MapTile_GetReligiousSiteCategory(v7, a2)
      && !MapTile_HasHiddenTreasure(v8, a2) )
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
signed int  Trap_New(DWORD a1, int a2, int a3, int a4, double a5)
{
  signed int result; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  DWORD v13; // ebp
  signed int v14; // eax
  _WORD *v15; // edx
  signed int v16; // ecx
  double v17; // st7
  int v18; // ecx
  int v19; // edx

  Debug_Log(a3, a4, a1, (int)aTrap_newDDD, a1);
  result = UnitStack_HasBuilder(a4);
  if ( result )
  {
    if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * a4 + gameData + UNIT_STACK_TABLE_OFFSET) < 0 || !Trap_CanPlaceAtTile(a1, a2) )
      return 0;
    v10 = a1 - *(__int16 *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( v10 <= 0 )
      v10 = *(__int16 *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET) - a1;
    if ( v10 > 1 )
      return 0;
    v11 = a2 - *(__int16 *)(gameData + UNIT_STACK_STRIDE * a4 + 147176);
    if ( v11 <= 0 )
      v11 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * a4 + 147176) - a2;
    if ( v11 <= 1 )
    {
      v12 = UNIT_STACK_STRIDE * a4;
      v13 = gameData + 100 * a1;
      TILE_TRAP_OWNER_MASK(a1, a2) = 1 << *(_BYTE *)(gameData + UNIT_STACK_STRIDE * a4 + 147178);
      UnitStack_SpendActionPointsByIndexClamped(a4, 0, v13, a5);
      while ( 1 )
      {
        v14 = Unit_GetSquadCount(v12 + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( v16 >= v14 )
          break;
        if ( *v15 == UNIT_TYPE_BUILDER )
        {
          *v15 = -1;
          break;
        }
      }
      Rules_SyncArmyFactStrength(UNIT_STACK_STRIDE * a4 + gameData + UNIT_STACK_TABLE_OFFSET, UNIT_STACK_STRIDE * a4, gameData, v12, v13, a5);
      Unit_CompactSquad(UNIT_STACK_STRIDE * a4 + gameData + UNIT_STACK_TABLE_OFFSET, v18, v17);
      if ( *(__int16 *)(gameData + v19 + 147180) == -1 )
      {
        Rules_UnlinkArmyFact(v19 + gameData + UNIT_STACK_TABLE_OFFSET, v17);
        WorldMap_SyncSelectionForHumanPlayer(v13);
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
int  Trap_ClearTileOwnerMask(int a1, int a2)
{
  int result; // eax

  result = gameData + TILE_TRAP_OWNER_MASK_ROW_STRIDE * a1;
  TILE_TRAP_OWNER_MASK(a1, a2) = 0;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0042B6A0) --------------------------------------------------------
__int16 * Trap_HurtStack(__int16 *a1, char a2, DWORD a3, double a4)
{
  int v5; // esi
  char *v6; // ecx
  int v8; // ecx
  unsigned int v9; // ebx
  unsigned int v10; // eax

  v5 = 0;
  Debug_Log((int)(a1 + 3), a2, a3, (int)Trap_HurtUnit);
  do
  {
    if ( *(__int16 *)v6 == -1 )
      break;
    v9 = Unit_CalcEffectivenessB(v6, 0);
    if ( v9 )
    {
      v10 = Rng_RandRange(270, 340);
      *(_BYTE *)(v8 + 9) -= v10 / v9;
    }
    else
    {
      *(_BYTE *)(v8 + 9) = 0;
    }
    if ( *(char *)(v8 + 9) <= 0 )
      *(_WORD *)v8 = -1;
    v6 = (char *)(v8 + 31);
    ++v5;
    *(v6 - 23) = 0;
  }
  while ( v5 < 10 );
  Unit_CompactSquad(a1, (int)v6, a4);
  return Rules_LinkArmyFinalize(a1, a4);
}
// 42B6BA: variable 'v6' is possibly undefined
// 42B6FA: variable 'v8' is possibly undefined

//----- (0042B730) --------------------------------------------------------
int  Trap_GetTileOwnerMask(int a1, int a2, int a3)
{
  if ( a3 == -1 )
    return TILE_TRAP_OWNER_MASK(a1, a2);
  else
    return TILE_TRAP_OWNER_MASK(a1, a2) & (1 << a3);
}
// 5202E4: using guessed type int gameData;

//----- (0042B770) --------------------------------------------------------
signed int  Trap_TriggerAtStackTile(int a1, DWORD a2, double a3)
{
  __int16 *v5; // ebx
  int v6; // eax
  int v7; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  unsigned int v15; // edx
  int v16; // eax
  int v17; // esi
  int i; // edx
  int v19; // edi
  int v20; // eax
  char v21; // cl
  int v22; // eax
  int v23; // ebx
  int v24; // ecx
  int v27; // [esp+4h] [ebp-24h]
  signed int v28; // [esp+Ch] [ebp-1Ch]

  v5 = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1);
  if ( UnitStack_GetMaxOrderTier((intptr_t)v5) >= 3 )
  {
    v16 = UnitStack_GetVisionRadius((int)v5);
    v17 = *v5 - v16;
    v28 = v16;
    v27 = 100 * v17;
    while ( v17 < v28 + *v5 )
    {
      for ( i = v5[1] - v28; ; ++i )
      {
        v19 = v5[1];
        if ( i >= v19 + v28 )
          break;
        if ( v17 >= 0
          && v17 < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && i >= 0
          && i < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Math_CeilSqrt((i - v19) * (i - v19) + (v17 - *v5) * (v17 - *v5)) <= v28 )
        {
          a2 = v27;
          if ( TILE_TRAP_OWNER_MASK(v17, i) )
          {
            v21 = *((_BYTE *)v5 + 4);
            a2 = 1 << v21;
            if ( ((1 << v21) & TILE_TRAP_OWNER_MASK(v17, i)) == 0 )
            {
              TILE_TRAP_OWNER_MASK(v17, i) |= 1 << v21;
              WorldMap_RedrawViewport(1);
            }
          }
        }
      }
      ++v17;
      v27 += 100;
    }
  }
  v6 = gameData + UNIT_STACK_STRIDE * a1;
  v7 = gameData + 100 * *(__int16 *)(v6 + 147174) + *(__int16 *)(v6 + 147176);
  if ( !TILE_TRAP_OWNER_MASK(*(__int16 *)(v6 + 147174), *(__int16 *)(v6 + 147176)) )
    return 0;
  v8 = *(unsigned __int8 *)(v6 + 147178);
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * v8 + 140059) )
  {
    TILE_TRAP_OWNER_MASK(*(__int16 *)(v6 + 147174), *(__int16 *)(v6 + 147176)) |= 1 << v8;
    WorldMap_RedrawViewport(1);
    WorldMap_RedrawViewport(1);
    v11 = Time_Now(v10, v9) + 200;
    while ( 1 )
    {
      v13 = Time_Now(v12, v11);
      if ( v13 >= v15 )
        break;
      WorldMap_RedrawFrame(v7);
    }
    Win_PlayModeChangeFrameTransition(aWpad_pul, 1, v14, v7, a2);
  }
  v22 = gameData + UNIT_STACK_STRIDE * a1;
  v23 = TILE_TRAP_OWNER_MASK_ROW_STRIDE * *(__int16 *)(v22 + 147174);
  TILE_TRAP_OWNER_MASK(*(__int16 *)(v22 + 147174), *(__int16 *)(v22 + 147176)) = 0;
  Rules_RetractTrapFact(*(__int16 *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(UNIT_STACK_STRIDE * a1 + gameData + 147176));
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
int  Trap_ShowPitfallDiscoveryDialog(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 v11; // ax
  int v12; // edx
  int SpriteForChar; // eax
  int v14; // esi
  int v15; // ebx
  int v16; // ebp
  int v17; // edi
  __int16 v18; // ax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // ebx
  unsigned __int16 v25; // [esp+10h] [ebp-58h]
  unsigned __int16 v26; // [esp+10h] [ebp-58h]
  unsigned __int16 v27; // [esp+14h] [ebp-54h]
  unsigned __int16 v28; // [esp+18h] [ebp-50h]
  int v29[3]; // [esp+1Ch] [ebp-4Ch]
  _DWORD *v30; // [esp+28h] [ebp-40h] BYREF
  _DWORD *v31; // [esp+2Ch] [ebp-3Ch]
  int v32; // [esp+30h] [ebp-38h]
  int v33; // [esp+34h] [ebp-34h]
  int v34; // [esp+38h] [ebp-30h]
  int v35; // [esp+3Ch] [ebp-2Ch]
  int v36; // [esp+40h] [ebp-28h]
  void *v37; // [esp+44h] [ebp-24h]
  int v38; // [esp+48h] [ebp-20h]
  int v39; // [esp+4Ch] [ebp-1Ch]
  int v40; // [esp+50h] [ebp-18h]

  v35 = a1;
  v36 = a2;
  v37 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a3, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a3);
  v30 = v5;
  v38 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  v32 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v30, 0)) / 2;
  Surface = (_DWORD *)Mem_Alloc(188, v6, a3, a4);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)v30, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)v30, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  v31 = Surface;
  v25 = v32 + DLX_GetSpriteWidth((int)v30, 0) - 1;
  v11 = DLX_GetSpriteHeight((int)v30, 0);
  Render_FillRect(0, v31, (unsigned __int16)v32, (unsigned __int16)v38, v38 + v11 - 1, v25, 0, 0);
  Render_ReleaseSurface(17, a4);
  if ( g_LanguageIndex == 2 )
    v12 = 10;
  else
    v12 = 0;
  SpriteForChar = DLX_GetSpriteForChar((int)v30, v12);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    v32,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v29[0] = (int)g_TrapPitfallDiscoveryMessageStrings[0];
  v29[1] = (int)g_TrapPitfallDiscoveryMessageStrings[1];
  v29[2] = (int)g_TrapPitfallDiscoveryMessageStrings[2];
  if ( g_LanguageIndex )
  {
    v24 = v32 + 52;
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      UI_DrawTextFmt((int)&v30, v38 + 30, v38 + 250, v32 + 32, 3, (int)aThisIsAPitfall);
      UI_DrawTextFmt((int)&v30, v20, v21, v24, 3, (int)aDoYouWantToCov);
      goto LABEL_9;
    }
    if ( g_LanguageIndex == 2 )
    {
      UI_DrawTextFmt((int)&v30, v38 + 30, v38 + 250, v32 + 32, 3, (int)aDasIstDieWolfs);
      UI_DrawTextFmt((int)&v30, v22, v23, v24, 3, (int)aWillstDuSieZus);
      goto LABEL_9;
    }
  }
  UI_DrawTextFmt((int)&v30, v38 + 30, v38 + 250, v32 + 42, 3, v29[(unsigned __int8)g_LanguageIndex]);
LABEL_9:
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)g_RenderState);
  v39 = v38 + 175;
  v34 = v38 + 220;
  v14 = v32 + 103;
  v15 = v38 + 60;
  v33 = v32 + 117;
  v16 = v32 + 100;
  v17 = v32 + 113;
  v40 = v38 + 92;
  while ( 1 )
  {
    do
      DD_Pump((int)g_RenderState, v15);
    while ( !DD_IsFlipping((int)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v15
      && g_MouseCursorRawY >> g_CursorCoordShift >= v16
      && g_MouseCursorRawX >> g_CursorCoordShift <= v40
      && g_MouseCursorRawY >> g_CursorCoordShift <= v17 )
    {
      break;
    }
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v39
      && g_MouseCursorRawY >> g_CursorCoordShift >= v14
      && g_MouseCursorRawX >> g_CursorCoordShift <= v34
      && g_MouseCursorRawY >> g_CursorCoordShift <= v33 )
    {
      Trap_ClearTileOwnerMask(v35, v36);
      break;
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  v28 = v32;
  v27 = v38;
  v26 = DLX_GetSpriteWidth((int)v30, 0) - 1;
  v18 = DLX_GetSpriteHeight((int)v30, 0);
  Render_FillRect(v31, 0, 0, 0, v18 - 1, v26, v27, v28);
  if ( v31 )
    (*(void (__cdecl **)(int, int, int))v31[46])(v29[0], v29[1], v29[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&v30);
  Render_Present((int)g_RenderState);
  g_RenderDevice = v37;
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
int  Battle_LoadWallSegmentsFromBuildingRecord(int a1)
{
  int v2; // ebx
  int v3; // eax
  int v4; // edx
  int v5; // esi
  int v6; // esi
  int v7; // ecx
  int result; // eax
  int v9; // [esp+4h] [ebp-30h]
  int v10; // [esp+8h] [ebp-2Ch]
  int v11; // [esp+Ch] [ebp-28h]
  int v12; // [esp+10h] [ebp-24h]

  v12 = 1;
  v11 = 40;
  v10 = 0;
  v9 = 20;
  while ( *(_DWORD *)(g_MapData + 804) - 1 > v12 )
  {
    v2 = a1;
    v3 = 0;
    v4 = 0;
    while ( v3 < *(_DWORD *)(g_MapData + 800) )
    {
      v5 = *(__int16 *)(v4 + g_MapData + v11);
      if ( v5 >= 388 && v5 <= 403 )
      {
        v6 = *(__int16 *)(v4 + g_MapData + 40 * v10);
        if ( v6 < 388 || v6 > 403 || (v7 = *(__int16 *)(40 * (v12 + 1) + g_MapData + v4), v7 < 388) || v7 > 403 )
        {
          *(_BYTE *)(v9 + g_MapData + v3 + 3134) = *(_BYTE *)(v2 + 422);
          *(_BYTE *)(v9 + g_MapData + v3 + 3534) = 100;
        }
      }
      v4 += 2;
      ++v2;
      ++v3;
    }
    v11 += 40;
    ++v10;
    v9 += 20;
    ++v12;
  }
  *(_DWORD *)(g_MapData + 828) = *(_DWORD *)(g_MapData + 800) / 2;
  result = *(unsigned __int8 *)(a1 + 421);
  *(_DWORD *)(g_MapData + 820) = result;
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C060) --------------------------------------------------------
char  Battle_SaveWallSegmentsToBuildingRecord(int a1)
{
  int v2; // edx
  int i; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ebx
  char v7; // dl
  char result; // al

  v2 = 0;
  for ( i = 0; v2 < *(_DWORD *)(g_MapData + 804) && !*(_BYTE *)(g_MapData + i + 3534); i += 20 )
    ++v2;
  v4 = a1;
  v5 = 0;
  v6 = 20 * v2;
  while ( v5 < *(_DWORD *)(g_MapData + 800) )
  {
    ++v4;
    v7 = *(_BYTE *)(v6 + g_MapData + v5++ + 3134);
    *(_BYTE *)(v4 + 421) = v7;
  }
  result = g_CurrentPlayerIndex;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
  {
    result = *(_BYTE *)(g_MapData + 832);
    *(_BYTE *)(*(_DWORD *)(g_MapData + 828) + a1 + 422) = result;
  }
  return result;
}
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;

//----- (0042C0F0) --------------------------------------------------------
BOOL  UnitBattle_IsTileInViewport(int a1, int a2)
{
  int v2; // ebx
  int v3; // esi
  BOOL result; // eax

  v2 = *(_DWORD *)(g_MapData + 808);
  result = 0;
  if ( a1 >= v2 && a1 < v2 + 7 )
  {
    v3 = *(_DWORD *)(g_MapData + 812);
    if ( a2 >= v3 && a2 < v3 + 7 )
      return 1;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C130) --------------------------------------------------------
void  Battle_LogUnitEntry(__int16 *a1, DWORD a2, ...)
{
  char *unit_name;

  if ( !a1 )
    return;
  unit_name = UnitType_GetLocalizedName((unit_type)*a1);
  Debug_Log((int)(uintptr_t)a1, 0, a2, (int)aD0x08x15sPl1dP, unit_name);
}
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0042C180) --------------------------------------------------------
void  Battle_LogAllUnits(int a1, char a2, DWORD a3)
{
  int v4; // ebx
  __int16 *v5; // ecx
  int v6; // ecx

  Debug_Log(a1, a2, a3, (int)aBattle_logallu);
  v4 = 0;
  v5 = (__int16 *)(g_MapData + 852);
  do
  {
    while ( *v5 == -1 )
    {
      ++v4;
      v5 = (__int16 *)((char *)v5 + 31);
      if ( v4 >= 22 )
        return;
    }
    Battle_LogUnitEntry(v5, a3);
    ++v4;
    v5 = (__int16 *)((char *)v5 + 31);
  }
  while ( v4 < 22 );
}
// 42C1BF: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042C1D0) --------------------------------------------------------
int  GodAnger(DWORD a1, int a2, char a3)
{
  int k; // ecx
  int v5; // esi
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
  int v18; // esi
  __lock *v19; // ecx
  int j; // esi
  __lock *v21; // ecx
  unsigned __int16 v22; // [esp+Ch] [ebp-838h]
  unsigned __int8 v23[1024]; // [esp+1Ch] [ebp-828h] BYREF
  unsigned __int8 v24[1024]; // [esp+41Ch] [ebp-428h] BYREF
  int v25[3]; // [esp+81Ch] [ebp-28h]
  _DWORD *v26; // [esp+828h] [ebp-1Ch] BYREF
  void *v27; // [esp+82Ch] [ebp-18h]

  Debug_Log(a2, a3, a1, (int)aGodanger);
  v25[0] = (int)g_GodAngerMessageStrings[0];
  v25[1] = (int)g_GodAngerMessageStrings[1];
  v25[2] = (int)g_GodAngerMessageStrings[2];
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * a1 + 140059) )
  {
    UnitBattle_ShowPlayerMessageBanner(v25[(unsigned __int8)g_LanguageIndex], a1, 0, a1);
    Render_Pump();
    v27 = g_RenderDevice;
    memset(v23, 0, sizeof(v23));
    Palette_LoadFromQueryHandle((intptr_t)v24, (intptr_t)"white.pal");
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_white_palette", (int)a1, 0, 0, 0);
    v10 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( v10 )
      v10 = DLXSpriteSet_Load(v10, "lightn.s32");
    v26 = v10;
    for ( i = 0; i < 300; ++i )
    {
      v12 = (__lock *)i;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, v23, v12, 450);
    }
    g_RenderDevice = &g_MainRenderDevice;
    SpriteForChar = DLX_GetSpriteForChar((int)v26, 0);
    Compat_RenderDeviceDrawMenuSprite(16, 100, SpriteForChar, 1);
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_lightning_draw", (int)a1, (int)(uintptr_t)v26, SpriteForChar, 0);
    Audio_PlayArtifactSound(0);
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, v24, 150, 200);
    Timer_BusyWaitWithCallback(10, 0, 0);
    v22 = DLX_GetSpriteWidth((int)v26, 0) + 16;
    SpriteHeight = DLX_GetSpriteHeight((int)v26, 0);
    v18 = 150;
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 50, SpriteHeight + 200, v22, 0x32u, 0x10u);
    do
    {
      v19 = (__lock *)v18;
      v18 -= 60;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, v24, v19, 200);
    }
    while ( v18 > 0 );
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, v23, (__lock *)0x96, 200);
    for ( j = 0; j < 150; ++j )
    {
      v21 = (__lock *)j;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, v21, 150);
    }
    Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_MapPalettePtr);
    DLXSpriteSet_ReleaseAndClear((int *)&v26);
    g_RenderDevice = v27;
    Render_Present((int)g_RenderState);
    UnitBattle_RedrawVisibleGrid();
  }
  for ( k = 0; k != 682; k += 31 )
  {
    v5 = k + g_MapData;
    result = *(__int16 *)(k + g_MapData + 852);
    if ( result != -1 )
    {
      result = *(unsigned __int8 *)(v5 + 854);
      if ( result == a1 )
      {
        *(_BYTE *)(v5 + 861) -= Rng_RandRange(20, 30);
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
  int v0; // esi
  int v1; // edi
  int i; // eax
  int v3; // ecx

  v0 = 0;
  v1 = 0;
  for ( i = 0; i != 682; i += 31 )
  {
    if ( *(__int16 *)(i + g_MapData + 852) != -1 )
    {
      v3 = *(unsigned __int8 *)(i + g_MapData + 854);
      if ( v3 == *(_DWORD *)(g_MapData + 836) )
      {
        v0 = 1;
      }
      else if ( v3 == *(_DWORD *)(g_MapData + 840) )
      {
        v1 = 1;
      }
    }
  }
  return v0 && v1;
}
// 532048: using guessed type int g_MapData;

//----- (0042C560) --------------------------------------------------------
int  Battle_ApplyPeriodicDamageToSideUnits(int a1)
{
  int v2; // ebx
  __int16 *v3; // ecx
  int result; // eax
  int v5; // esi
  int v6; // eax
  char v7; // ah

  v2 = 0;
  v3 = (__int16 *)(g_MapData + 852);
  do
  {
    while ( 1 )
    {
      result = *v3;
      if ( result != -1 && *((unsigned __int8 *)v3 + 2) == a1 )
      {
        v5 = (unsigned __int8)g_UnitTypeBaseActionPoints_512580[88 * result] - 15;
        v6 = Rng_RandRange(25, 35) - v5;
        if ( v6 < 0 )
          v6 = 0;
        if ( v6 > *((char *)v3 + 9) )
          LOBYTE(v6) = *((_BYTE *)v3 + 9);
        v7 = *((_BYTE *)v3 + 9) - v6;
        *((_BYTE *)v3 + 9) = v7;
        result = v7;
        if ( result <= 0 )
          break;
      }
      ++v2;
      v3 = (__int16 *)((char *)v3 + 31);
      if ( v2 >= 22 )
        return result;
    }
    *v3 = -1;
    ++v2;
    v3 = (__int16 *)((char *)v3 + 31);
  }
  while ( v2 < 22 );
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
  char v4; // dl
  int v5; // ecx
  int v6; // eax
  char v7; // bl
  int v8; // ecx
  int v9; // eax
  DWORD v10; // ebp
  int v11; // ecx
  int *v12; // ebx
  unsigned __int16 v13; // bx
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
      v4 = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) + 1;
      *(_BYTE *)(g_MapData + v3 + 855) = v4;
      *(_BYTE *)(v2 + v3 + 855) = v4 & 7;
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
      v7 = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) - 1;
      *(_BYTE *)(g_MapData + v6 + 855) = v7;
      *(_BYTE *)(v5 + v6 + 855) = v7 & 7;
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
        v8 = 31 * g_SelectedUnitIndex + g_MapData + 852;
        v9 = *(unsigned __int8 *)(v8 + 3);
        v10 = Map_NeighborDY[2 * v9];
        v12 = UnitBattle_MoveTrack(
                g_SelectedUnitIndex,
                Map_NeighborDX[2 * v9] + *(unsigned __int16 *)(v8 + 4),
                v8,
                v10 + *(unsigned __int16 *)(v8 + 6),
                v10);
        LOWORD(IsKeyPressed) = 31 * g_SelectedUnitIndex;
        *(_DWORD *)(g_MapData + 31 * g_SelectedUnitIndex + 875) = v12;
        if ( v12 )
        {
          v13 = HIWORD(*(_DWORD *)(*(_DWORD *)(v11 + 23) + 4));
          if ( *(unsigned __int8 *)(v11 + 8) < (int)v13 )
          {
            LOWORD(IsKeyPressed) = j__nfree_();
            *(_DWORD *)(v15 + 23) = 0;
          }
          else
          {
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
            LOWORD(IsKeyPressed) = UnitBattle_Move(g_SelectedUnitIndex, v14, v13, v10);
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

