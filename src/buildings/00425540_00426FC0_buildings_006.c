/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00425540) --------------------------------------------------------
signed int  Builder_StartRoadBuildMode(DWORD a1, double a2)
{
  signed int result; // eax
  int v4; // ebx
  int (__fastcall *overlayDrawHook)(_DWORD, _DWORD); // ecx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int unitStackRecordBase; // esi
  int tileDeltaY; // eax
  int *selectedDirectionMarker; // edx

  result = Map_GetTileSurfaceClassOrUnexplored(
             *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
             *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176));
  if ( result != 185 )
  {
    v4 = 0;
    g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_ActionBusy;
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_ActionBusy);
    g_WorldMapTileOverlayDrawHook = overlayDrawHook;
    g_RoadBuildModeExitRequested = 0;
    g_RoadBuildModeControlWidgetState = 2;
    WorldMap_RedrawViewport(1);
    if ( !g_RoadBuildModeExitRequested )
    {
      while ( 1 )
      {
        DD_Pump((int)(intptr_t)g_RenderState, v4);
        WorldMap_HandleScrollKeysAndIdle(a1);
        WorldMap_RedrawFrame(v4);
        if ( Time_Now(v8, v7) - 10 > (unsigned int)g_RoadBuildModeLastAnimationTick )
        {
          g_RoadBuildModeLastAnimationTick = Time_Now(v9, g_RoadBuildModeLastAnimationTick);
          v4 = ((_BYTE)g_RoadBuildModeAnimationFrameIndex + 1) & 7;
          g_RoadBuildModeAnimationFrameIndex = v4;
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) - 1,
            *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176));
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176) - 1);
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET) + 1,
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176));
          WorldMap_RedrawTileIfVisible(
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176) + 1);
        }
        if ( !UIWidgetTable_PollHoverAndActions(g_RoadBuildModeControlWidgets, a1) )
        {
          RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
          if ( UI_TrySelectFriendlyStackUnderCursor() )
          {
            Render_Begin((int)(intptr_t)g_RenderState, 0);
            goto LABEL_13;
          }
        }
        if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
        {
          LOBYTE(v6) = g_CursorCoordShift;
          unitStackRecordBase = UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData;
          v4 = (((g_MouseCursorRawX >> g_CursorCoordShift)
               - 32
               - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
                + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
             + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)
             - *(__int16 *)(uintptr_t)(unitStackRecordBase + 147174);
          tileDeltaY = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET)
              + (((g_MouseCursorRawY >> g_CursorCoordShift)
                - 16
                - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                 + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
              - *(__int16 *)(uintptr_t)(unitStackRecordBase + 147176);
          selectedDirectionMarker = 0;
          if ( v4 || tileDeltaY != -1 )
          {
            if ( v4 != 1 || tileDeltaY )
            {
              if ( v4 || tileDeltaY != 1 )
              {
                if ( v4 == -1 && !tileDeltaY )
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
            RoadBuildMode_BuildInSelectedDirection((int)(intptr_t)selectedDirectionMarker, a1, a2);
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
    UIWidget_RefreshActionButtonState((int)(intptr_t)g_RoadBuildModeControlWidgets, v6);
    result = WorldMap_RedrawViewport(1);
    g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
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
int UnitBattle_InitPathingTables(void)
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
  while ( rowIndex < *(_DWORD *)(uintptr_t)(g_MapData + 804) )
  {
    cellIndex = rowCellBase;
    columnIndex = 0;
    columnByteOffset = 0;
    blockedCellIndex = rowCellBase;
    while ( columnIndex < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
    {
      terrainTileId = *(__int16 *)(uintptr_t)(columnByteOffset + rowByteOffset + g_MapData);
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
        g_TilePassabilityMask[cellIndex] = *(_BYTE *)(uintptr_t)(g_MapData + 816);
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
  if ( !g_MapIgnoreUnitOccupancy && *(__int16 *)(uintptr_t)(40 * row + g_MapData + 2 * column + 1534) != -1 )
    return 0;
  if ( g_UnitTypeFlatMoveCostFlags[unitTypeIndex] )
    return 5;
  if ( *(_BYTE *)(uintptr_t)(g_MapData + 20 * row + column + 3134) )
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
  unsigned __int8 v30 CLASH95_UNUSED; // dl
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
  Debug_Log(a3, unitIndex, a5, (int)(intptr_t)aUnitbattle_m_0);
  unitTypeIndex = *(__int16 *)(uintptr_t)(g_MapData + 31 * unitIndex + 852);
  startRow = *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * unitIndex + 856);
  startColumn = *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * unitIndex + 858);
  if ( goalRow < 0
    || goalColumn < 0
    || goalRow >= *(_DWORD *)(uintptr_t)(g_MapData + 804)
    || goalColumn >= *(_DWORD *)(uintptr_t)(g_MapData + 800)
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
  LOWORD(v10) = *(_WORD *)(uintptr_t)(startCellPtr + 1534);
  *(_WORD *)(uintptr_t)(startCellPtr + 1534) = -1;
  savedBlockerCell = v10;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(uintptr_t)(g_MapData + 836)
    && *(unsigned __int8 *)(uintptr_t)(31 * unitIndexLocal + g_MapData + 854) == *(_DWORD *)(uintptr_t)(g_MapData + 840) )
  {
    UnitBattle_TemporarilyClearGateBlocker();
  }
  v12 = startRow;
  costGrid[20 * startRow + 1 + startColumn] = 0;
  do
  {
    scanRow = 0;
    gridChanged = 0;
    while ( scanRow < *(_DWORD *)(uintptr_t)(g_MapData + 804) )
    {
      scanColumn = 0;
      rowByteOffset = 40 * scanRow;
      cellByteOffset = 40 * scanRow;
      while ( scanColumn < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
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
            if ( neighborRow >= 0 && neighborRow < *(_DWORD *)(uintptr_t)(g_MapData + 804) && i >= 0 && i < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
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
                    if ( *(_BYTE *)(uintptr_t)(v66 + v20) )
                      goto LABEL_30;
                    v21 = neighborRow <= scanRow ? scanRow : neighborRow;
                    v73 = 20 * v21;
                    v67 = 20 * v21 + g_MapData + 3134;
                    v22 = i <= scanColumn ? scanColumn : i;
                    if ( *(_BYTE *)(uintptr_t)(v67 + v22 - 1) )
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
                    if ( *(_BYTE *)(uintptr_t)(v68 + v24 - 1) )
                      goto LABEL_30;
                    v25 = neighborRow <= scanRow ? scanRow : neighborRow;
                    v73 = 20 * v25;
                    v69 = 20 * v25 + g_MapData + 3134;
                    v26 = i <= scanColumn ? scanColumn : i;
                    if ( *(_BYTE *)(uintptr_t)(v69 + v26) )
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
    allocatedPath = (int *)(uintptr_t)Mem_Alloc(404, i, v12, 0);
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
          if ( candRow >= *(_DWORD *)(uintptr_t)(g_MapData + 804) )
            goto LABEL_84;
          candColumn = traceColumn + colDelta;
          if ( candColumn < 0 )
            goto LABEL_84;
          if ( candColumn >= *(_DWORD *)(uintptr_t)(g_MapData + 800) )
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
            if ( !*(_BYTE *)(uintptr_t)(v46 + v45) )
            {
              v47 = traceRow;
              if ( traceRow <= traceRow + rowDelta )
                v47 = traceRow + rowDelta;
              v48 = traceColumn + colDelta;
              v49 = 20 * v47 + g_MapData + 3134;
              if ( traceColumn <= v48 )
              {
                if ( *(_BYTE *)(uintptr_t)(v49 + v48 - 1) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(uintptr_t)(v49 + traceColumn - 1) )
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
            if ( !*(_BYTE *)(uintptr_t)(v51 + v50 - 1) )
            {
              v52 = traceRow;
              if ( traceRow <= traceRow + rowDelta )
                v52 = traceRow + rowDelta;
              v53 = traceColumn + colDelta;
              v54 = 20 * v52 + g_MapData + 3134;
              if ( traceColumn <= v53 )
              {
                if ( *(_BYTE *)(uintptr_t)(v54 + v53) )
                  goto LABEL_84;
              }
              else if ( *(_BYTE *)(uintptr_t)(v54 + traceColumn) )
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
  *(_WORD *)(uintptr_t)(2 * startColumn + g_MapData + 40 * startRow + 1534) = savedBlockerCell;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(uintptr_t)(g_MapData + 836)
    && *(unsigned __int8 *)(uintptr_t)(31 * unitIndexLocal + g_MapData + 854) == *(_DWORD *)(uintptr_t)(g_MapData + 840) )
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
  Debug_Log(row, col, a4, (int)(intptr_t)aUnitbattle_mov);
  if ( target_row < 0
    || target_col < 0
    || target_row >= *(_DWORD *)(uintptr_t)(g_MapData + 804)
    || target_col >= *(_DWORD *)(uintptr_t)(g_MapData + 800) )
  {
    return 0;
  }
  target_grid_row_offset = 40 * target_row;
  target_cost_row_offset = 20 * target_row;
  target_grid_offset = g_MapData + target_grid_row_offset + 2 * target_col + 1534;
  target_cost_offset = g_MapData + target_cost_row_offset + target_col + 3134;
  saved_occupant = *(_WORD *)(uintptr_t)target_grid_offset;
  saved_cost = *(_BYTE *)(uintptr_t)target_cost_offset;
  *(_WORD *)(uintptr_t)target_grid_offset = -1;
  *(_BYTE *)(uintptr_t)target_cost_offset = 0;
  path = UnitBattle_MoveTrack(unit_index, target_row, target_row, target_col, a4);
  if ( !path )
  {
    *(_WORD *)(uintptr_t)target_grid_offset = saved_occupant;
    *(_BYTE *)(uintptr_t)target_cost_offset = saved_cost;
    return 0;
  }
  if ( !*path )
  {
    *(_WORD *)(uintptr_t)target_grid_offset = saved_occupant;
    *(_BYTE *)(uintptr_t)target_cost_offset = saved_cost;
    nfree_((int)(uintptr_t)path);
    return 0;
  }
  reversed_path = (int *)(uintptr_t)Mem_Alloc(404, 0, target_col, a4);
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
  *(_WORD *)(uintptr_t)target_grid_offset = saved_occupant;
  *(_BYTE *)(uintptr_t)target_cost_offset = saved_cost;
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
  Debug_Log(unit_index, row, a4, (int)(intptr_t)aUnitbattle_m_2);
  if ( target_col < 0 || target_col >= *(_DWORD *)(uintptr_t)(g_MapData + 800) )
    return 0;
  current_row = *(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 856);
  current_col = *(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 858);
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
    if ( target_row + 1 < *(_DWORD *)(uintptr_t)(g_MapData + 804) )
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
  result = (int *)(uintptr_t)Mem_Alloc(404, 0, target_row, a4);
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

  Debug_Log(unit_index, col, row, (int)(intptr_t)aUnitbattle_m_3);
  target_col = col;
  target_row = (int)row;
  if ( target_row < 0 || target_row >= *(_DWORD *)(uintptr_t)(g_MapData + 804) || target_col < 0 || target_col >= *(_DWORD *)(uintptr_t)(g_MapData + 800) )
    return 0;
  g_MapIgnoreUnitOccupancy = 1;
  if ( *(char *)(uintptr_t)(target_col + g_MapData + 20 * target_row + 3134) <= 0 )
    goto LABEL_4;
  if ( *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * unit_index + 856) < target_row )
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
  int v12 CLASH95_UNUSED; // ecx
  _DWORD *sprite_set; // eax
  int unit_type; // eax
  int init_frame_index; // eax
  int *track_list; // eax
  int path_count; // edx
  int popped_step; // eax
  int *v19; // edx
  int new_count; // ecx
  int player_data_offset; // eax
  int v22 CLASH95_UNUSED; // edx
  int dest_row; // ebp
  int v24 CLASH95_UNUSED; // ecx
  int col_delta; // edx
  int row_delta; // eax
  unsigned __int8 facing_dir; // al
  int v28 CLASH95_UNUSED; // ecx
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
  int v39 CLASH95_UNUSED; // edx
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
  Debug_Log(a2, a3, a4, (int)(intptr_t)aUnitbattle_m_1);
  unit_ptr = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * unit_index_copy);
  v6 = *(_DWORD **)((char *)unit_ptr + 23);
  move_track = v6;
  if ( v6 && *v6 )
  {
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
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
    LOWORD(v11) = *(unsigned __int8 *)(uintptr_t)(unit_record_addr + 854);
    Unit_BuildGoSpriteFilePath(sprite_path, *(_BYTE *)(uintptr_t)(unit_record_addr + 852), v11);
    sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, sprite_path);
    g_ActiveUnitAnimSpriteSet = (int)(intptr_t)sprite_set;
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
        if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(uintptr_t)(unit_record_offset + g_MapData + 852), (unsigned __int8)packed_step, BYTE1(packed_step)) )
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
          current_col = *(_WORD *)(uintptr_t)(unit_record_offset + g_MapData + 858);
          target_offset_x = ((unsigned __int8)packed_step - *(unsigned __int16 *)(uintptr_t)(unit_record_offset + g_MapData + 856)) << 6;
          target_offset_y = (BYTE1(packed_step) - current_col) << 6;
          last_tick = Time_Now(0, 0);
          tick_interval = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *(__int16 *)(uintptr_t)(unit_record_offset + g_MapData + 852)];
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
            DD_Pump((int)(intptr_t)g_RenderState, v11);
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
              step_px = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(uintptr_t)(unit_record_offset + g_MapData + 852)];
              LOBYTE(v11) = step_px;
              g_UnitMoveAnimOffsetX += step_px * Map_NeighborDX[dir_step_index / 4];
              g_UnitMoveAnimOffsetY += Map_NeighborDY[dir_step_index / 4]
                            * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *(__int16 *)(uintptr_t)(unit_record_offset + g_MapData + 852)];
            }
          }
          *(_WORD *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)unit_ptr[2] + 2 * (unsigned __int16)unit_ptr[3] + 1534) = -1;
          unit_ptr[2] = (unsigned __int8)packed_step;
          unit_ptr[3] = BYTE1(packed_step);
          *(_WORD *)(uintptr_t)(2 * BYTE1(packed_step) + 40 * (unsigned __int16)unit_ptr[2] + g_MapData + 1534) = unit_index;
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
    *(_DWORD *)(uintptr_t)(gameData + player_data_offset + 140073) = 1;
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
    LOWORD(v6) = RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_ActionBusy);
  }
  return (__int16)(intptr_t)v6;
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
  *(_DWORD *)(uintptr_t)(g_MapData + 808) = *(unsigned __int16 *)(uintptr_t)(g_MapData + unit_record_offset + 856) - 3;
  *(_DWORD *)(uintptr_t)(g_MapData + 812) = *(unsigned __int16 *)(uintptr_t)(g_MapData + unit_record_offset + 858) - 3;
  if ( *(int *)(uintptr_t)(g_MapData + 808) < 0 )
    *(_DWORD *)(uintptr_t)(g_MapData + 808) = 0;
  map_row_count = *(_DWORD *)(uintptr_t)(g_MapData + 804);
  if ( *(_DWORD *)(uintptr_t)(g_MapData + 808) + 7 > map_row_count )
    *(_DWORD *)(uintptr_t)(g_MapData + 808) = map_row_count - 7;
  if ( *(int *)(uintptr_t)(g_MapData + 812) < 0 )
    *(_DWORD *)(uintptr_t)(g_MapData + 812) = 0;
  result = g_MapData;
  map_col_count = *(_DWORD *)(uintptr_t)(g_MapData + 800);
  if ( *(_DWORD *)(uintptr_t)(g_MapData + 812) + 7 > map_col_count )
    *(_DWORD *)(uintptr_t)(g_MapData + 812) = map_col_count - 7;
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
  unit_row = *(unsigned __int16 *)(uintptr_t)(unit_record + 4);
  for ( i = 0; i != 16; i += 2 )
  {
    neighbor_row = unit_row + g_UnitBattleAdjacentTileDeltaX[i];
    if ( neighbor_row >= 0 && neighbor_row < *(_DWORD *)(uintptr_t)(g_MapData + 804) )
    {
      neighbor_col = g_UnitBattleAdjacentTileDeltaY[i] + *(unsigned __int16 *)(uintptr_t)(unit_record + 6);
      if ( neighbor_col >= 0 && neighbor_col < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
      {
        occupant_index = *(__int16 *)(uintptr_t)(g_MapData + 40 * neighbor_row + 2 * neighbor_col + 1534);
        if ( occupant_index != -1 && *(_BYTE *)(uintptr_t)(31 * occupant_index + g_MapData + 854) != *(_BYTE *)(uintptr_t)(unit_record + 2) )
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
  int defender_effectiveness; // eax
  int v11; // ecx
  int attacker_effectiveness; // eax
  int defender_damage; // ecx
  int attacker_power; // ebx
  int damage_ratio; // edx
  int scaled_damage; // edx
  int result; // eax
  int attacker_damage; // edx
  int defender_remaining; // esi
  int attacker_remaining; // ecx
  signed int attacker_crowd_scale; // [esp+0h] [ebp-14h]
  signed int defender_crowd_scale; // [esp+0h] [ebp-14h]

  attacker_unit = (char *)(uintptr_t)(g_MapData + 852 + 31 * attacker_index);
  defender_unit = (char *)(uintptr_t)(31 * defender_index + g_MapData + 852);
  *attacker_health = attacker_unit[9];
  *defender_health = defender_unit[9];
  UnitBattle_GetTargetCrowdingScale((int)(intptr_t)defender_unit);
  defender_effectiveness = Unit_CalcEffectivenessB(defender_unit, v9);
  if ( (defender_effectiveness * v11 - (__CFSHL__((defender_effectiveness * v11) >> 31, 8) + ((defender_effectiveness * v11) >> 31 << 8))) >> 8 )
  {
    UnitBattle_GetTargetCrowdingScale((int)(intptr_t)attacker_unit);
    Unit_CalcEffectivenessA(attacker_unit, 0);
  }
  attacker_crowd_scale = UnitBattle_GetTargetCrowdingScale((int)(intptr_t)attacker_unit);
  attacker_effectiveness = Unit_CalcEffectivenessB(attacker_unit, 0);
  attacker_power = (attacker_effectiveness * attacker_crowd_scale - (__CFSHL__((attacker_effectiveness * attacker_crowd_scale) >> 31, 8) + ((attacker_effectiveness * attacker_crowd_scale) >> 31 << 8))) >> 8;
  if ( attacker_power )
  {
    defender_crowd_scale = UnitBattle_GetTargetCrowdingScale((int)(intptr_t)defender_unit);
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
          scaled_damage = 15 * damage_ratio;
        else
          scaled_damage = 12 * damage_ratio;
      }
      else
      {
        scaled_damage = 10 * damage_ratio;
      }
    }
    else
    {
      scaled_damage = 7 * damage_ratio;
    }
  }
  else
  {
    scaled_damage = 5 * damage_ratio;
  }
  result = (scaled_damage - (__CFSHL__(scaled_damage >> 31, 8) + (scaled_damage >> 31 << 8))) >> 8;
  attacker_damage = result;
  if ( result > 100 )
    attacker_damage = 100;
  defender_remaining = *defender_health - defender_damage;
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
