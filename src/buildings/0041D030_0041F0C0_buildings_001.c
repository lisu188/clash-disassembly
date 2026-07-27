/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0041D030) --------------------------------------------------------
BOOL  Building_New(buildingType, stackIndex, st7_0, name, force)
int buildingType;
DWORD stackIndex;
double st7_0;
char *name;
int force;
{
  int v8 CLASH95_UNUSED; // ecx
  int stackByteOffset; // ecx
  int v10 CLASH95_UNUSED; // edx
  int foundFreeSlot; // ecx
  int scanByteOffset; // eax
  int foundBuildingIndex; // eax
  char ownerByte; // al
  __int16 v15; // ax
  char addonFlags; // dl
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
  int v29 CLASH95_UNUSED; // ecx
  int slotInitPtr; // eax
  int recordInitPtr; // eax
  int byteInitPtr; // eax
  int v33 CLASH95_UNUSED; // ecx
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
  int v44 CLASH95_UNUSED; // ecx
  signed int v45 CLASH95_UNUSED; // ecx
  int occupantBelow; // eax
  int occupantBelowLayer2; // eax
  int occupantLayer2; // eax
  __int16 v49; // dx
  int terrainTileId; // eax
  int castleTerrainTileId; // eax
  int terrainRowOffsetBelow; // ebx
  int terrainColOffset; // esi
  int v54 CLASH95_UNUSED; // ecx
  void *v55 CLASH95_UNUSED; // ecx
  signed int column; // [esp+4h] [ebp-34h]
  int buildingIndexCopy; // [esp+8h] [ebp-30h]
  int row; // [esp+14h] [ebp-24h]
  int buildingPtr; // [esp+18h] [ebp-20h]
  int scanIndex; // [esp+1Ch] [ebp-1Ch]
  int buildingIndex; // [esp+1Ch] [ebp-1Ch]
  int revealRowDelta; // [esp+24h] [ebp-14h]

  Diagnostics_TraceBootstrapEvent("Building_New-enter");
  Debug_Log(buildingType, stackIndex, force, (int)(intptr_t)aBuilding_newDD);
  stackByteOffset = UNIT_STACK_STRIDE * stackIndex;
  g_CurrentPlayerIndex = *(unsigned __int8 *)(uintptr_t)(gameData + stackByteOffset + 147178);
  if ( g_BuildingNewOverrideActive )
  {
    row = g_BuildingNewOverrideRow;
    column = g_BuildingNewOverrideColumn;
  }
  else
  {
    row = *(__int16 *)(uintptr_t)(gameData + stackByteOffset + UNIT_STACK_TABLE_OFFSET);
    column = *(__int16 *)(uintptr_t)(gameData + stackByteOffset + 147176);
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
      occupantBelow = *(unsigned __int16 *)(uintptr_t)(TILE_ROW_STRIDE * (row + 1) + gameData + 2 * column + TILE_MAP_OFFSET);
      if ( occupantBelow != 0xFFFF && occupantBelow != stackIndex )
        return 0;
      occupantBelowLayer2 = *(unsigned __int16 *)(uintptr_t)(200 * (row + 1) + gameData + 2 * column + 556376);
      if ( occupantBelowLayer2 != 0xFFFF && occupantBelowLayer2 != stackIndex )
        return 0;
      occupantLayer2 = *(unsigned __int16 *)(uintptr_t)(gameData + 200 * row + 2 * column + 556376);
      if ( occupantLayer2 != 0xFFFF && occupantLayer2 != stackIndex )
        return 0;
    }
    occupantAtTile = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(row, column));
    if ( occupantAtTile != 0xFFFF && occupantAtTile != stackIndex )
      return 0;
  }
  foundFreeSlot = 0;
  scanByteOffset = 0;
  scanIndex = 0;
  do
  {
    if ( *(char *)(uintptr_t)(gameData + scanByteOffset + 509678) == -1 )
      foundFreeSlot = 1;
    scanByteOffset += 467;
    ++scanIndex;
  }
  while ( scanByteOffset < 46700 && !foundFreeSlot );
  foundBuildingIndex = scanIndex - 1;
  buildingIndex = scanIndex - 1;
  if ( !foundFreeSlot )
    return 0;
  buildingIndexCopy = foundBuildingIndex;
  buildingPtr = UNIT_RECORD(buildingIndex);
  *(_BYTE *)(uintptr_t)buildingPtr = row;
  *(_BYTE *)(uintptr_t)(buildingPtr + 1) = column;
  ownerByte = g_CurrentPlayerIndex;
  *(_BYTE *)(uintptr_t)(buildingPtr + 3) = g_CurrentPlayerIndex;
  *(_BYTE *)(uintptr_t)(buildingPtr + 2) = ownerByte;
  *(_BYTE *)(uintptr_t)(buildingPtr + 4) = buildingType;
  v15 = g_BuildingTypeMaxHitPoints[buildingType];
  *(_BYTE *)(uintptr_t)(buildingPtr + 421) = 0;
  *(_BYTE *)(uintptr_t)(buildingPtr + 434) = 50;
  addonFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 416);
  *(_WORD *)(uintptr_t)(buildingPtr + 16) = v15;
  v17 = *(_BYTE *)(uintptr_t)(buildingPtr + 435);
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) = addonFlags & 0xE0;
  v18 = *(_BYTE *)(uintptr_t)(buildingPtr + 420);
  *(_BYTE *)(uintptr_t)(buildingPtr + 435) = v17 & 0xF8;
  v19 = *(_BYTE *)(uintptr_t)(buildingPtr + 436);
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) = v18 & 0xFE;
  v20 = *(_WORD *)(uintptr_t)(buildingPtr + 432);
  *(_BYTE *)(uintptr_t)(buildingPtr + 436) = v19 & 0xC0;
  *(_WORD *)(uintptr_t)(buildingPtr + 432) = v20 & 0xF000;
  LOBYTE(v15) = *(_BYTE *)(uintptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) & 7;
  HIBYTE(v15) = *(_BYTE *)(uintptr_t)(buildingPtr + 444) & 0xF8;
  *(_BYTE *)(uintptr_t)(buildingPtr + 444) = HIBYTE(v15);
  *(_BYTE *)(uintptr_t)(buildingPtr + 444) = v15 | HIBYTE(v15);
  if ( buildingType )
  {
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      v21 = 200;
    else
      v21 = 300;
    *(_DWORD *)(uintptr_t)(buildingPtr + 438) = v21;
    v22 = (_WORD *)(uintptr_t)(buildingPtr + 430);
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      v23 = 100;
    else
      v23 = 250;
    v24 = *v22 & 0xF000;
    HIBYTE(v23) &= 0xFu;
    *v22 = v24;
    *v22 = v23 | v24;
  }
  nameDest = (char *)(uintptr_t)(buildingPtr + 5);
  v26 = *(_BYTE *)(uintptr_t)(buildingPtr + 437) & 0xC0;
  *(_WORD *)(uintptr_t)(buildingPtr + 442) = 0;
  *(_BYTE *)(uintptr_t)(buildingPtr + 437) = v26;
  *(_BYTE *)(uintptr_t)(buildingPtr + 437) = v26 | 0x32;
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
    *(_BYTE *)(uintptr_t)(buildingPtr + 421) = 1;
    v49 = *(_WORD *)(uintptr_t)(buildingPtr + 430) & 0xF000;
    *(_BYTE *)(uintptr_t)(buildingPtr + 416) |= BUILDING_ADDON_FLAG_BARRACKS;
    *(_WORD *)(uintptr_t)(buildingPtr + 430) = v49;
  }
  slotInitPtr = buildingPtr;
  do
  {
    slotInitPtr += 6;
    *(_BYTE *)(uintptr_t)(slotInitPtr + 439) = -1;
  }
  while ( slotInitPtr != buildingPtr + 18 );
  recordInitPtr = buildingPtr;
  do
  {
    recordInitPtr += 31;
    *(_WORD *)(uintptr_t)(recordInitPtr - 13) = -1;
  }
  while ( recordInitPtr != buildingPtr + 372 );
  byteInitPtr = buildingPtr + 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 402) = 0;
  do
    *(_BYTE *)(uintptr_t)(++byteInitPtr + 401) = -1;
  while ( byteInitPtr != buildingPtr + 12 );
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = -1;
  Diagnostics_TraceBootstrapEvent("Building_New-before-unit-get-into");
  Building_UnitGetInto(stackIndex, buildingIndexCopy, 7, stackIndex, st7_0);
  Diagnostics_TraceBootstrapEvent("Building_New-after-unit-get-into");
  *(_WORD *)(uintptr_t)(TILE_INDEX(row, column)) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
  if ( buildingType == 1 || buildingType == 2 )
  {
    tileRowOffsetBelow = 200 * (row + 1);
    *(_WORD *)(uintptr_t)(tileRowOffsetBelow + gameData + 2 * column + TILE_MAP_OFFSET) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(uintptr_t)(gameData + 200 * row + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(uintptr_t)(tileRowOffsetBelow + gameData + 2 * column + 556376) = buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( !force )
    {
      castleTerrainTileId = *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
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
      *(_WORD *)(uintptr_t)(terrainColOffset + terrainRowOffsetBelow + gameData) = castleTerrainTileId;
      *(_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * row + gameData + terrainColOffset) = castleTerrainTileId;
      *(_WORD *)(uintptr_t)(gameData + terrainRowOffsetBelow + 14 * column) = castleTerrainTileId;
      *(_WORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * column + gameData + TILE_TERRAIN_ROW_STRIDE * row) = castleTerrainTileId;
    }
  }
  else if ( !force )
  {
    terrainTileId = *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
    if ( terrainTileId == 707 )
    {
      LOWORD(terrainTileId) = 0;
    }
    else if ( terrainTileId == 711 )
    {
      LOWORD(terrainTileId) = 4;
    }
    *(_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * row + gameData + TILE_TERRAIN_RECORD_STRIDE * column) = terrainTileId;
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
  if ( *(_DWORD *)(uintptr_t)(playerData + 140067) == -1 && buildingType == 2 )
    *(_DWORD *)(uintptr_t)(playerData + 140067) = buildingIndex;
  if ( ACTIVE_MISSION_INDEX == -1 || GAME_TURN_COUNTER != 1 )
    Building_AssignUniqueGeneratedName(buildingPtr);
  Diagnostics_TraceBootstrapEvent("Building_New-before-minimap");
  if ( buildingType )
  {
    MiniMap_DrawTileCell((void *)(uintptr_t)row, column);
    MiniMap_DrawTileCell((void *)(uintptr_t)(row + 1), column);
    MiniMap_DrawTileCell((void *)(uintptr_t)row, column + 1);
    minimapColumn = column + 1;
    minimapRowPtr = (void *)(uintptr_t)(row + 1);
  }
  else
  {
    minimapColumn = column;
    minimapRowPtr = (void *)(uintptr_t)row;
  }
  MiniMap_DrawTileCell(minimapRowPtr, minimapColumn);
  Diagnostics_TraceBootstrapEvent("Building_New-before-rules-assert");
  Rules_AssertCastleFact((unsigned __int8 *)(uintptr_t)buildingPtr, buildingIndex);
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

CLASH95_INTERNAL BOOL Building_NewAt(int row, int column, int building_type, DWORD stack_index, double st7_0, char *name, int force)
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

  castleIndex = *(unsigned __int16 *)(uintptr_t)(2 * buildingPtr[1] + gameData + TILE_ROW_STRIDE * *buildingPtr + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  return Rules_LogCastleBuiltFactAndScheme(castleIndex, castleIndex);
}
// 5202E4: using guessed type int gameData;

//----- (0041D980) --------------------------------------------------------
BOOL  MapTile_IsCastleFoundationTile(int row, signed int column, int checkMode)
{
  signed int surfaceClass; // eax
  int v5 CLASH95_UNUSED; // ecx
  int v6; // esi
  int rowBase; // ecx

  surfaceClass = Map_GetTileSurfaceClassOrUnexplored(row, column);
  if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 207 || surfaceClass == 1 )
    return 0;
  if ( checkMode )
  {
    v6 = 2 * column;
    rowBase = TILE_TERRAIN_ROW_STRIDE * row + gameData;
    return *(unsigned __int16 *)(uintptr_t)(rowBase + 7 * v6) >= 0x2C3u && *(unsigned __int16 *)(uintptr_t)(rowBase + 7 * v6) <= 0x2CAu;
  }
  return MapTile_IsCastleFoundationTile(row, column, 2) == 0;
}
// 41D9F0: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041DA50) --------------------------------------------------------
BOOL  MapTile_IsCastleFoundationAnchorTile(int row, signed int column, int checkMode)
{
  signed int surfaceClass; // eax
  int v5 CLASH95_UNUSED; // ecx
  int tileId; // eax

  surfaceClass = Map_GetTileSurfaceClassOrUnexplored(row, column);
  if ( surfaceClass == 185 || surfaceClass == 39 || surfaceClass == 204 || surfaceClass == 202 || surfaceClass == 147 || surfaceClass == 207 || surfaceClass == 1 )
    return 0;
  if ( checkMode )
  {
    tileId = *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * row + gameData + TILE_TERRAIN_RECORD_STRIDE * column);
    return tileId == 707 || tileId == 711;
  }
  return !MapTile_IsCastleFoundationTile(row, column, 2);
}
// 41DAC0: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041DB20) --------------------------------------------------------
int Rules_RebuildCastleSiteFacts(void)
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
    if ( row >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    column = 0;
    colByteOffset = 0;
    while ( column < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      tileId = *(unsigned __int16 *)(uintptr_t)(colByteOffset + i + gameData);
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
  g_CurrentPlayerIndex = *(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178);
  rowDelta = row - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + UNIT_STACK_TABLE_OFFSET);
  isValid = 1;
  rowDeltaAbs = rowDelta;
  if ( rowDelta <= 0 )
    rowDeltaAbs = -rowDelta;
  if ( rowDeltaAbs > footprintRadius )
    goto LABEL_6;
  if ( column - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) > 0 )
  {
    if ( column - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) <= footprintRadius )
      goto LABEL_7;
LABEL_6:
    isValid = 0;
    goto LABEL_7;
  }
  if ( *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) - column > footprintRadius )
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
            if ( *(unsigned __int16 *)(uintptr_t)(scanRowByteOffset + gameData + i + TILE_MAP_OFFSET) >= 0x8000u
              && *(unsigned __int16 *)(uintptr_t)(scanRowByteOffset + gameData + i + TILE_MAP_OFFSET) != 0xFFFF )
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
      tileOwner = *(unsigned __int16 *)(uintptr_t)(rowByteBase + gameData + scanColByteOffset + TILE_MAP_OFFSET);
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
  DWORD buildingPtrCopy CLASH95_UNUSED; // [esp+0h] [ebp-34h]
  int occupiedSlots[12]; // [esp+4h] [ebp-30h] BYREF

  buildingPtrCopy = buildingPtr;
  Debug_Log(a2, a3, a4, (int)(intptr_t)aBuilding_stop0);
  if ( !*(_WORD *)(uintptr_t)(buildingPtr + 16) )
    return 0;
  slotPtr = buildingPtr;
  slotIndex = 0;
  occupiedCount = 0;
  outIndex = 0;
  do
  {
    if ( *(__int16 *)(uintptr_t)(slotPtr + 18) != -1 )
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
  Building_UnitsLeave((unsigned __int8 *)(uintptr_t)buildingPtr, occupiedSlots, a5);
  *(_WORD *)(uintptr_t)(buildingPtr + 16) = -1;
  Rules_RetractCastleFact((unsigned __int8 *)(uintptr_t)buildingPtr, a5);
  return 1;
}

//----- (0041E0E0) --------------------------------------------------------
char  Building_AssignUniqueGeneratedName(int buildingPtr)
{
  char *namePtr; // ebp
  int duplicate_count; // [esp+10h] [ebp-20h]
  unsigned int name_index; // [esp+Ch] [ebp-24h]
  char lower_name[24]; // [esp+0h] [ebp-30h] BYREF

  namePtr = (char *)(uintptr_t)(buildingPtr + 5);
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
char  Building_FinishConstruction(unsigned __int8 *buildingPtr, int a2, char a3, double gameTime)
{
  int tileRow; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int buildingType; // eax
  int centerRow; // eax
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

  Debug_Log(a2, a3, (DWORD)(intptr_t)buildingPtr, (int)(intptr_t)aBuilding_build);
  LOBYTE(tileRow) = *buildingPtr;
  Rules_LogCastleBuiltFactAndScheme(v6, *(unsigned __int16 *)(uintptr_t)(2 * buildingPtr[1] + gameData + TILE_ROW_STRIDE * tileRow + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Rules_LogNewCastleFact(buildingPtr[2], *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  Building_OnGarrisonChange(*(unsigned __int16 *)(uintptr_t)(2 * buildingPtr[1] + TILE_ROW_STRIDE * *buildingPtr + gameData + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v7, gameTime);
  buildingType = (char)buildingPtr[4];
  if ( buildingType == 2 || buildingType == 1 )
    Map_RebuildRoadOverlayAtTile(*buildingPtr, buildingPtr[1] + 2);
  centerRow = (char)buildingPtr[4];
  if ( !buildingPtr[4] )
  {
    tileColumn = buildingPtr[1];
    LOBYTE(centerRow) = *buildingPtr;
    revealColEnd = tileColumn + 15;
    revealRow = centerRow - 15;
    revealColStart = tileColumn - 15;
    v8 = centerRow + 15;
    revealRowEnd = centerRow + 15;
    revealRowDelta = -15;
    if ( centerRow - 15 < centerRow + 15 )
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
  Unit_UpdatePerTurn((int)(intptr_t)buildingPtr, v8);
  result = buildingPtr[4];
  if ( result )
  {
    result = gameData;
    if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * buildingPtr[2] + gameData + 140051) )
    {
      row = *buildingPtr;
      UI_CenterWorldMapViewportOnRectIfFit(row, buildingPtr[1], buildingPtr[1] - 5, row);
      return Building_ShowConstructionFinishedDialog((int)(intptr_t)buildingPtr, v17, row, (DWORD)(intptr_t)buildingPtr);
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

  buildingPtr = (unsigned __int8 *)(uintptr_t)result;
  if ( (*(_BYTE *)(uintptr_t)(result + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
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
          Debug_Log(a2, a3, a4, (int)(intptr_t)aBuilding_produ);
          result = 0;
          /* loc_41E44A: `mov edx, esi` - the garrison scan starts at the building
             record itself; IDA left the cursor (v7) undefined. */
          garrisonSlotPtr = (int)(intptr_t)buildingPtr;
          while ( *(__int16 *)(uintptr_t)(garrisonSlotPtr + 18) != -1 )
          {
            ++result;
            garrisonSlotPtr += 31;
            if ( result >= 12 )
            {
              BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = 1;
              return result;
            }
          }
          UnitSlot_InitFromType((int)(intptr_t)&buildingPtr[31 * result + 18], (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402], buildingPtr[2]);
          remainingGold = *(_DWORD *)(buildingPtr + 438) - (unsigned __int8)g_UnitTypeProductionCost[88 * (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402]];
          playerDataOffset = PLAYER_DATA_STRIDE * buildingPtr[2];
          *(_DWORD *)(buildingPtr + 438) = remainingGold;
          if ( *(_DWORD *)(uintptr_t)(gameData + playerDataOffset + 140051) )
          {
            BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = g_UnitTypeProductionTime[88 * (char)buildingPtr[BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) + 402]];
          }
          else
          {
            BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = 0;
            BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = -1;
          }
          return Building_OnGarrisonChange(
                   *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
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
  char repairTurnsRemaining; // al
  unsigned __int8 serviceStateRepairCleared; // ah
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
        repairTurnsRemaining = (((unsigned __int8)(4 * serviceState) >> 5) - 1) & 7;
        serviceStateRepairCleared = serviceState & 0xC7;
        BUILDING_GARRISON_SERVICE_STATE(garrisonBytePtr, 0) = serviceStateRepairCleared;
        LOBYTE(v6) = 8 * repairTurnsRemaining;
        BYTE1(v6) = v6 | serviceStateRepairCleared;
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
          if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * buildingPtr[2] + 140051) )
          {
            LOBYTE(v6) = UnitSlot_CycleOrderState((int)(intptr_t)&firstSlotPtr[31 * slotIndex]);
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
                   *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
                   (int)(intptr_t)buildingPtr,
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
  currentHitPoints = *(_WORD *)(uintptr_t)(buildingPtr + 16);
  if ( !currentHitPoints )
  {
    memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 100, 7);
    return buildingPtr + 422;
  }
  maxHitPoints = g_BuildingTypeMaxHitPoints[*(char *)(uintptr_t)(buildingPtr + 4)];
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
    *(_BYTE *)(uintptr_t)(slotWalker + 421) = rolledDamage;
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
  int v7 CLASH95_UNUSED; // ecx

  slotPtr = (CSyncObject *)(buildingPtr + 18);
  garrisonChanged = 0;
  for ( i = 0; i < 12; ++i )
  {
    result = UNIT_SLOT_TYPE(slotPtr);
    if ( result != -1 )
    {
      UnitSlot_AdjustFatigueByPredicate((int)(intptr_t)slotPtr, -50, UnitSlot_PredicateAlways);
      result = UnitSlot_AdjustMoraleByPredicate((int)(intptr_t)slotPtr, 1, (BOOL ( *)(int))UnitSlot_NeedsMoraleRecovery);
      garrisonChanged = 1;
    }
    slotPtr = (CSyncObject *)((char *)slotPtr + 31);
  }
  if ( garrisonChanged )
    return Building_OnGarrisonChange(
             *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
             (int)(intptr_t)slotPtr,
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
  Debug_Log(a2, playerIndex, a3, (int)(intptr_t)aBuilding_check);
  buildingPtr = (_BYTE *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET);
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
  result = (unsigned __int8 *)(uintptr_t)(PLAYER_DATA_STRIDE * playerIndex + gameData);
  if ( result[140071] < newTechLevel )
  {
    result[140071] = newTechLevel;
    updateIndex = 0;
    result = (unsigned __int8 *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET);
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
    (int)(intptr_t)aD0x08xDDTDPDGD,
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
    (int)(intptr_t)aUDDDDDDDDDD,
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

  Debug_Log(a1, a2, a3, (int)(intptr_t)aLogallbuilding);
  buildingIndex = 0;
  buildingPtr = gameData + BUILDING_TABLE_OFFSET;
  do
  {
    while ( *(char *)(uintptr_t)(buildingPtr + 4) == -1 )
    {
      ++buildingIndex;
      buildingPtr += 467;
      if ( buildingIndex >= 100 )
        return;
    }
    Building_DebugDump((unsigned __int8 *)(uintptr_t)buildingPtr, buildingIndex++, a3);
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
  int currentPlayerIndex; // ecx
  int v7; // ecx
  __int16 constructionDelta; // dx
  int j; // eax
  int slotUnitType; // ecx
  int v12; // ecx
  int buildingType; // eax

  Debug_Log(a1, (char)(intptr_t)buildingPtr, a3, (int)(intptr_t)aBuilding_newtu);
  for ( i = 0; i != 46700; i += 467 )
  {
    currentPlayerIndex = *(char *)(uintptr_t)(gameData + i + 509678);
    if ( currentPlayerIndex != -1 )
    {
      currentPlayerIndex = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(uintptr_t)(gameData + i + 509676) == g_CurrentPlayerIndex )
      {
        buildingPtr = (unsigned __int8 *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET + i);
        buildingPtr[420] &= ~1u;
        if ( *(__int16 *)(uintptr_t)(i + gameData + 509690) != -1 )
        {
          if ( *(_WORD *)(uintptr_t)(i + gameData + 509690) )
          {
            constructionDelta = 0;
            for ( j = 0; j != 372; j += 31 )
            {
              slotUnitType = *(__int16 *)(uintptr_t)(i + gameData + j + 509692);
              if ( slotUnitType == 17 )
              {
                slotUnitType = (unsigned __int8)g_BuilderConstructionProgressPerTurn;
                constructionDelta += (unsigned __int8)g_BuilderConstructionProgressPerTurn;
              }
            }
            *(_WORD *)(uintptr_t)(i + gameData + 509690) -= constructionDelta;
            if ( *(__int16 *)(uintptr_t)(i + gameData + 509690) < 0 )
            {
              *(_WORD *)(uintptr_t)(i + gameData + 509690) = 0;
              Building_FinishConstruction(buildingPtr, slotUnitType, (char)(intptr_t)buildingPtr, a4);
            }
            else
            {
              Unit_UpdatePerTurn((int)(intptr_t)buildingPtr, slotUnitType);
            }
          }
          else
          {
            if ( buildingPtr[4] == 2 )
            {
              Building_CollectGoldIncome((int)(intptr_t)buildingPtr);
              Building_UpdatePopulationGrowth((int)(intptr_t)buildingPtr);
              Building_UpdatePlagueState((unsigned int)(intptr_t)buildingPtr);
              Prisoner_NewTurn((DWORD)(intptr_t)buildingPtr, v12, (char)(intptr_t)buildingPtr, a4);
            }
            buildingType = (char)buildingPtr[4];
            if ( buildingType == 2 || buildingType == 1 )
            {
              Building_ProcessUnitProductionTurn((int)(intptr_t)buildingPtr, currentPlayerIndex, (char)(intptr_t)buildingPtr, a3, a4);
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
  LogAllBuildings(currentPlayerIndex, (char)(intptr_t)buildingPtr, a3);
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

  Debug_Log(buildingIndex, a2, a3, (int)(intptr_t)aBuilding_getin);
  buildingPtr = UNIT_RECORD(buildingIndex);
  if ( !*(_WORD *)(uintptr_t)(buildingPtr + 16) )
  {
    if ( !*(_BYTE *)(uintptr_t)(buildingPtr + 4) )
    {
      previousResourceHandle = Render_SetResourceHandle(
                                 (int)(intptr_t)&g_MainRenderDevice,
                                 (char *)RenderHook_DemoText == (char *)Render_DefaultRH);
      previousRenderHook = g_RenderHook;
      g_RenderHook = (int (*)())RenderHook_DemoText;
      Debug_Log(buildingIndex, (char)(intptr_t)previousRenderHook, (DWORD)(intptr_t)RenderHook_DemoText, (int)(intptr_t)aSetrhS08x_4, aKeep_redraw, RenderHook_DemoText);
      UI_DemoTextPresent(buildingIndex, buildingIndex, (char)(intptr_t)previousRenderHook, (DWORD)(intptr_t)RenderHook_DemoText);
      Debug_Log(buildingIndex, (char)(intptr_t)previousRenderHook, (DWORD)(intptr_t)RenderHook_DemoText, (int)(intptr_t)aUnsetrh08x_4, previousRenderHook);
      g_RenderHook = previousRenderHook;
      return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
    }
    if ( (unsigned __int8)*(_BYTE *)(uintptr_t)(buildingPtr + 4) <= 2u )
    {
      previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
      previousRenderHook = g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(buildingIndex, (char)(intptr_t)previousRenderHook, a3, (int)(intptr_t)aSetrhS08x_5, aStdrh_3, Render_DefaultRH);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[castle] building_getinto_open building_idx=%d kind=%d owner=%d construction=%d\n",
          buildingIndex,
          *(unsigned __int8 *)(uintptr_t)(buildingPtr + 4),
          *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2),
          *(__int16 *)(uintptr_t)(buildingPtr + 16));
      Castle_OpenManagementScreen(buildingIndex, (char)(intptr_t)previousRenderHook);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[castle] building_getinto_return building_idx=%d\n", buildingIndex);
      Debug_Log(buildingIndex, (char)(intptr_t)previousRenderHook, a3, (int)(intptr_t)aUnsetrh08x_5, previousRenderHook);
      g_RenderHook = previousRenderHook;
      return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
    }
  }
  return buildingPtr;
}
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;

//----- (0041EDD0) --------------------------------------------------------
signed int  Building_BuildSchool(char *a1, char a2, DWORD a3)
{
  /* 0041EDD0: `mov edx, eax` - the building record pointer arrives in EAX (it
     is `a1`); IDA left `buildingPtr` undefined (flagged at 41EDEF). */
  int buildingPtr = (int)(intptr_t)a1; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a2, a3, (int)(intptr_t)aBuilding_bui_0, *a1);
  /* 41EDF2 / 41EEA2 / 41EFA2 / 41F042: `xor ecx,ecx` (issued before the
     `call log`) followed by `mov cl,[edx+2]` - ECX is fully zero-extended,
     so the owner index is a plain unsigned byte.  IDA emitted only the
     partial LOBYTE store and left the top 24 bits of `ownerPlayer`
     undefined, which turned PLAYER_DATA_STRIDE*ownerPlayer into a wild
     offset. */
  ownerPlayer = *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2);
  goldCost = 400;
  if ( !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 300;
  if ( (*(_BYTE *)(uintptr_t)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(uintptr_t)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 416) | BUILDING_ADDON_FLAG_SCHOOL;
  *(_DWORD *)(uintptr_t)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0041EE70) --------------------------------------------------------
signed int  Building_BuildWorkshop(int buildingRecord, char a1, DWORD a2)
{
  /* same __usercall loss as Building_BuildHospital */
  int buildingPtr = buildingRecord; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(0, a1, a2, (int)(intptr_t)aBuilding_bui_4);
  /* 41EDF2 / 41EEA2 / 41EFA2 / 41F042: `xor ecx,ecx` (issued before the
     `call log`) followed by `mov cl,[edx+2]` - ECX is fully zero-extended,
     so the owner index is a plain unsigned byte.  IDA emitted only the
     partial LOBYTE store and left the top 24 bits of `ownerPlayer`
     undefined, which turned PLAYER_DATA_STRIDE*ownerPlayer into a wild
     offset. */
  ownerPlayer = *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2);
  goldCost = 190;
  if ( !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 90;
  if ( (*(_BYTE *)(uintptr_t)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(uintptr_t)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 416) | BUILDING_ADDON_FLAG_WORKSHOP;
  *(_DWORD *)(uintptr_t)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 41EE8F: variable 'v3' is possibly undefined
// 41EE92: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041EF10) --------------------------------------------------------
signed int  Building_BuildBarracks(int a1, char a2, DWORD a3)
{
  /* sub_41EF10: `mov edx, eax` - the first register argument IS the building
     record pointer; IDA left `buildingPtr` undefined. */
  int buildingPtr = a1; // edx
  unsigned int availableGold; // ecx
  signed int result; // eax

  Debug_Log(a1, a2, a3, (int)(intptr_t)aBuilding_bui_2);
  if ( (*(_BYTE *)(uintptr_t)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(uintptr_t)(buildingPtr + 438);
  if ( availableGold < 0xC8 )
    return 0;
  *(_DWORD *)(uintptr_t)(buildingPtr + 438) = availableGold - 200;
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) |= BUILDING_ADDON_FLAG_BARRACKS;
  result = 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) |= 1u;
  return result;
}
// 41EF29: variable 'v4' is possibly undefined

//----- (0041EF80) --------------------------------------------------------
signed int  Building_BuildHospital(int buildingRecord, char a1, DWORD a2)
{
  /* sub_41EF80: `mov edx, eax` - the building record pointer arrives in eax and
     was dropped from IDA's __usercall signature entirely. */
  int buildingPtr = buildingRecord; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(buildingRecord, a1, a2, (int)(intptr_t)aBuilding_bui_3);
  /* 41EDF2 / 41EEA2 / 41EFA2 / 41F042: `xor ecx,ecx` (issued before the
     `call log`) followed by `mov cl,[edx+2]` - ECX is fully zero-extended,
     so the owner index is a plain unsigned byte.  IDA emitted only the
     partial LOBYTE store and left the top 24 bits of `ownerPlayer`
     undefined, which turned PLAYER_DATA_STRIDE*ownerPlayer into a wild
     offset. */
  ownerPlayer = *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2);
  goldCost = 200;
  if ( !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 100;
  if ( (*(_BYTE *)(uintptr_t)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(uintptr_t)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 416) | BUILDING_ADDON_FLAG_HOSPITAL;
  *(_DWORD *)(uintptr_t)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) = buildLockFlags | 1;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0041F020) --------------------------------------------------------
signed int  Building_BuildSmiths(int buildingRecord, char a1, DWORD a2)
{
  /* 0041F020: `mov edx, eax` - exactly the same __usercall loss as
     Building_BuildHospital: the building record pointer is the EAX argument and
     IDA dropped it from the signature, leaving `buildingPtr` never assigned
     (flagged at 41EF9F).  Both call sites do pass it: sub_4554B0 computes
     gameData+7C6EAh+index*1D3h into EAX, and sub_420EF0 loads
     g_SelectedBuildingRecord into EAX. */
  int buildingPtr = buildingRecord; // edx
  int ownerPlayer; // ecx
  unsigned int goldCost; // eax
  unsigned int availableGold; // edi
  signed int result; // eax
  char buildLockFlags; // cl
  char addonFlags; // bh

  Debug_Log(buildingRecord, a1, a2, (int)(intptr_t)aBuilding_bui_1);
  /* 41EDF2 / 41EEA2 / 41EFA2 / 41F042: `xor ecx,ecx` (issued before the
     `call log`) followed by `mov cl,[edx+2]` - ECX is fully zero-extended,
     so the owner index is a plain unsigned byte.  IDA emitted only the
     partial LOBYTE store and left the top 24 bits of `ownerPlayer`
     undefined, which turned PLAYER_DATA_STRIDE*ownerPlayer into a wild
     offset. */
  ownerPlayer = *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2);
  goldCost = 230;
  if ( !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * ownerPlayer + gameData + 140051) )
    goldCost = 130;
  if ( (*(_BYTE *)(uintptr_t)(buildingPtr + 420) & 1) != 0 )
    return 0;
  availableGold = *(_DWORD *)(uintptr_t)(buildingPtr + 438);
  if ( goldCost > availableGold )
    return 0;
  buildLockFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 420);
  addonFlags = *(_BYTE *)(uintptr_t)(buildingPtr + 416) | BUILDING_ADDON_FLAG_SMITHS;
  *(_DWORD *)(uintptr_t)(buildingPtr + 438) = availableGold - goldCost;
  *(_BYTE *)(uintptr_t)(buildingPtr + 416) = addonFlags;
  result = 1;
  *(_BYTE *)(uintptr_t)(buildingPtr + 420) = buildLockFlags | 1;
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
  Debug_Log(a3, (char)(intptr_t)outColumn, 0, (int)(intptr_t)aBuildingFindFreePlaceNear);
  do
  {
    candidateRow = g_BuildingSpawnTileSearchOffsetsX[offsetTableIndex] + *buildingPtr;
    candidateColumn = g_BuildingSpawnTileSearchOffsetsY[offsetTableIndex] + buildingPtr[1];
    if ( *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(candidateRow, candidateColumn)) == 0xFFFF && Map_GetUnitTileMoveCostOrZero(buildingPtr[2], 31, candidateColumn, candidateRow) )
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
