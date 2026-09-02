/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00414390) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTileIgnoringOccupancy(__int16 *stackPtr, int tileRow, int tileColumn)
{
  int columnByteOffset; // ebp
  int tileSurfacePtr; // edx
  __int16 savedTileOccupant; // di
  signed int result; // eax

  columnByteOffset = 2 * tileColumn;
  tileSurfacePtr = gameData + TILE_ROW_STRIDE * tileRow + columnByteOffset + TILE_MAP_OFFSET;
  savedTileOccupant = *(_WORD *)(uintptr_t)tileSurfacePtr;
  *(_WORD *)(uintptr_t)tileSurfacePtr = -1;
  result = UnitStack_GetTileMoveCostOrZero(stackPtr, tileRow, 2 * tileColumn, tileColumn);
  *(_WORD *)(uintptr_t)tileSurfacePtr = savedTileOccupant;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00414400) --------------------------------------------------------
int * Path_InsertBridgeCornerWaypoints(int stackRecord, char a2, int *pathBuffer)
{
  UnitStackRecord *stack;
  int scratch_path[101];
  int scratch_waypoint;
  int current_waypoint;
  int previous_waypoint;
  int current_row;
  int current_column;
  int previous_row;
  int previous_column;
  int row_delta;
  int column_delta;
  int corner_waypoint;
  int overflow;

  (void)a2;
  stack = (UnitStackRecord *)(uintptr_t)stackRecord;
  if ( !pathBuffer || UnitStack_HasOnlyFlyingUnits(stackRecord) )
    return pathBuffer;
  scratch_path[0] = 0;
  scratch_waypoint = 0;
  LOBYTE(scratch_waypoint) = (unsigned __int8)stack->tile_row;
  BYTE1(scratch_waypoint) = (unsigned __int8)stack->tile_column;
  HIWORD(scratch_waypoint) = 0;
  if ( scratch_path[0] < 100 )
    scratch_path[++scratch_path[0]] = scratch_waypoint;
  while ( *pathBuffer )
  {
    current_waypoint = pathBuffer[*pathBuffer];
    --*pathBuffer;
    if ( scratch_path[0] < 100 )
      scratch_path[++scratch_path[0]] = current_waypoint;
  }
  overflow = 0;
  while ( scratch_path[0] > 1 )
  {
    current_waypoint = scratch_path[scratch_path[0]];
    --scratch_path[0];
    previous_waypoint = scratch_path[scratch_path[0]];
    current_row = (unsigned __int8)current_waypoint;
    current_column = BYTE1(current_waypoint);
    previous_row = (unsigned __int8)previous_waypoint;
    previous_column = BYTE1(previous_waypoint);
    row_delta = previous_row - current_row;
    if ( row_delta < 0 )
      row_delta = -row_delta;
    column_delta = previous_column - current_column;
    if ( column_delta < 0 )
      column_delta = -column_delta;
    if ( row_delta == 1
      && column_delta == 1
      && TILE_TERRAIN_RECORD(previous_row, previous_column)[2] != 0xFFFF
      && TILE_TERRAIN_RECORD(current_row, current_column)[2] != 0xFFFF
      && (TILE_TERRAIN_RECORD(current_row, previous_column)[2] != 0xFFFF
       || TILE_TERRAIN_RECORD(previous_row, current_column)[2] != 0xFFFF)
      && (UnitStack_GetTileMoveCostOrZero((__int16 *)stack, current_row, 0, previous_column)
       || UnitStack_GetTileMoveCostOrZero((__int16 *)stack, previous_row, 0, current_column)) )
    {
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = current_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
      corner_waypoint = current_waypoint;
      if ( TILE_TERRAIN_RECORD(current_row, previous_column)[2] != 0xFFFF
        && UnitStack_GetTileMoveCostOrZero((__int16 *)stack, current_row, 0, previous_column) )
      {
        BYTE1(corner_waypoint) = previous_column;
      }
      else if ( TILE_TERRAIN_RECORD(previous_row, current_column)[2] != 0xFFFF
             && UnitStack_GetTileMoveCostOrZero((__int16 *)stack, previous_row, 0, current_column) )
      {
        LOBYTE(corner_waypoint) = previous_row;
      }
      else
      {
        continue;
      }
      HIWORD(corner_waypoint) = (HIWORD(current_waypoint) + HIWORD(previous_waypoint)) / 2;
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = corner_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
    }
    else
    {
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = current_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
    }
  }
  if ( overflow )
  {
    j__nfree_(pathBuffer);
    return 0;
  }
  return pathBuffer;
}
// 5202E4: using guessed type int gameData;

//----- (004147A0) --------------------------------------------------------
int * Unit_MoveTrack(int stackIndex, int sourceRow, int targetRow, int sourceColumn, DWORD availableActionPoints, int targetColumn)
{
  int targetRowValue; // ecx
  int targetRowIndex; // edx
  int mapWidth; // ecx
  int mapHeight; // esi
  int *result; // eax
  int sourceTileOccupant; // edx
  int sourceTilePtr; // eax
  DWORD stackIndexArg; // ebp
  int v14 CLASH95_UNUSED; // edx
  __int64 v15 CLASH95_UNUSED; // rax
  unsigned int v16 CLASH95_UNUSED; // ecx
  unsigned int v17 CLASH95_UNUSED; // ecx
  int gridInitRow; // ebp
  int gridInitColumn; // esi
  int distColByteOffset; // edi
  char tileMoveCost; // al
  int v22; // ebx
  int rowScanMax; // esi
  int column; // ebp
  int currentDistance; // eax
  int i; // esi
  int neighborRow; // ebx
  int neighborColumn; // ecx
  int stepCost; // eax
  int v30; // ecx
  unsigned __int16 *targetDistancePtr; // eax
  int *pathResult; // ebp
  unsigned __int16 targetDistance; // dx
  int *pathBuffer; // eax
  unsigned __int8 v35 CLASH95_UNUSED; // dl
  int waypointCount; // esi
  int rowDelta; // ebx
  int traceNeighborColumn; // edx
  int traceNeighborRow; // eax
  int traceStepCost; // eax
  _WORD *traceNeighborDistPtr; // edx
  int pathCount; // eax
  char sourceRowByte; // bl
  int traceWaypoint; // ecx
  unsigned __int16 *currentCellDistPtr; // edi
  _WORD *neighborDistPtr; // edx
  __int16 relaxFromDistance; // bx
  int mapWidthLimit; // ecx
  _BYTE mergedProfile[88]; // [esp+0h] [ebp-104h] BYREF
  int stackIndex_l; // [esp+58h] [ebp-ACh]
  int sourceRow_l; // [esp+5Ch] [ebp-A8h]
  int sourceColumn_l; // [esp+60h] [ebp-A4h]
  int targetRow_l; // [esp+64h] [ebp-A0h]
  int savedCursorDescriptor; // [esp+68h] [ebp-9Ch]
  BOOL cursorWasNotBusy; // [esp+6Ch] [ebp-98h]
  int distanceGrid; // [esp+70h] [ebp-94h] BYREF
  int tileCostGrid; // [esp+74h] [ebp-90h] BYREF
  UnitStackRecord *stackRecord; // recovered 725-byte strategic stack record
  int rowWindowMin; // [esp+7Ch] [ebp-88h]
  int rowWindowMax; // [esp+80h] [ebp-84h]
  int colWindowMin; // [esp+84h] [ebp-80h]
  int colWindowMax; // [esp+88h] [ebp-7Ch]
  int anyRelaxed; // [esp+8Ch] [ebp-78h]
  int expansionBudget; // [esp+90h] [ebp-74h]
  int overflowFlag; // [esp+94h] [ebp-70h]
  int v67 CLASH95_UNUSED; // [esp+98h] [ebp-6Ch] BYREF
  int v68 CLASH95_UNUSED; // [esp+9Ch] [ebp-68h] BYREF
  int distGridRowOffset; // [esp+A0h] [ebp-64h]
  int costGridRowOffset; // [esp+A4h] [ebp-60h]
  int row; // [esp+A8h] [ebp-5Ch]
  int currentCellDistance; // [esp+ACh] [ebp-58h]
  int candidateDistance; // [esp+B0h] [ebp-54h]
  int targetRowByteOffset; // [esp+B4h] [ebp-50h]
  int targetColByteOffset; // [esp+B8h] [ebp-4Ch]
  int packedWaypoint; // [esp+BCh] [ebp-48h]
  int stepRowDelta; // [esp+C0h] [ebp-44h]
  int stepColumnDelta; // [esp+C4h] [ebp-40h]
  int traceColIndex; // [esp+C8h] [ebp-3Ch]
  int savedRowByteOffset; // [esp+CCh] [ebp-38h]
  int colByteOffsetSaved; // [esp+D0h] [ebp-34h]
  int distRowByteOffset; // [esp+D4h] [ebp-30h]
  int costGridRowBase; // [esp+D8h] [ebp-2Ch]
  int distGridRowBase; // [esp+DCh] [ebp-28h]
  int colByteOffset; // [esp+E0h] [ebp-24h]
  int currentRowByteOffset; // [esp+E4h] [ebp-20h]
  int savedOccupant; // [esp+E8h] [ebp-1Ch]
  int bestNeighborDistance; // [esp+ECh] [ebp-18h]
  unsigned __int16 *currentTileDistance; // [esp+F0h] [ebp-14h]
  unsigned __int8 traceColumn; // [esp+F4h] [ebp-10h]
  unsigned __int8 traceRow; // [esp+F8h] [ebp-Ch]

  stackIndex_l = stackIndex;
  sourceRow_l = sourceRow;
  sourceColumn_l = sourceColumn;
  targetRow_l = targetRow;
  Debug_Log(targetRow, sourceColumn, availableActionPoints, (int)(intptr_t)aUnit_movetrack);
  targetRowValue = targetRow;
  if ( targetRowValue < 0 )
    return 0;
  targetRowIndex = targetRowValue;
  mapWidth = *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET);
  if ( targetRowIndex >= mapWidth )
    return 0;
  if ( targetColumn < 0 )
    return 0;
  mapHeight = *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( targetColumn >= mapHeight || targetRowIndex >= mapWidth || targetColumn >= mapHeight )
    return 0;
  result = (int *)(uintptr_t)UnitStack_GetMoveCostToTile(stackIndex_l, targetRowIndex, targetColumn);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent(
      result ? "unit_move_target_cost" : "unit_move_target_blocked",
      stackIndex_l,
      targetRowIndex,
      targetColumn,
      (int)(intptr_t)result);
  if ( result )
  {
    savedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    cursorWasNotBusy = g_ActiveCursorDescriptorPtr != (_DWORD)(intptr_t)&g_CursorDesc_Busy;
    if ( g_CursorOverlayPresented )
      RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
    sourceTileOccupant = 2 * sourceColumn_l;
    sourceTilePtr = 2 * sourceColumn_l + gameData + 200 * sourceRow_l;
    LOWORD(sourceTileOccupant) = *(_WORD *)(uintptr_t)(sourceTilePtr + 556374);
    *(_WORD *)(uintptr_t)(sourceTilePtr + 556374) = -1;
    stackIndexArg = stackIndex_l;
    savedOccupant = sourceTileOccupant;
    stackRecord = UNIT_STACK_RECORD(stackIndex_l);
    UnitStack_BuildMergedTerrainMoveProfile((intptr_t)mergedProfile, (intptr_t)stackRecord);
    distanceGrid = nmalloc_(0x4E20, 4);
    if ( !distanceGrid )
    {
      Debug_Log(0, targetColumn, stackIndexArg, (int)(intptr_t)aNotEnoughMem_3);
      App_RequestQuit((int)(intptr_t)aNotEnoughMem_4);
    }
    tileCostGrid = nmalloc_(0x10000, 4);
    if ( !tileCostGrid )
    {
      Debug_Log(0, targetColumn, stackIndexArg, (int)(intptr_t)aNotEnoughMem_5);
      App_RequestQuit((int)(intptr_t)aNotEnoughMem_6);
    }
    gridInitRow = 0;
    costGridRowBase = 0;
    distGridRowBase = 0;
    while ( gridInitRow < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
    {
      gridInitColumn = 0;
      distGridRowOffset = distGridRowBase;
      distColByteOffset = 0;
      costGridRowOffset = costGridRowBase;
      while ( gridInitColumn < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        *(_WORD *)(uintptr_t)(distColByteOffset + distGridRowOffset + distanceGrid) = -2;
        tileMoveCost = UnitStack_GetTileMoveCostFromMergedProfileOrZero((__int16 *)stackRecord, (intptr_t)mergedProfile, gridInitColumn++, gridInitRow);
        distColByteOffset += 2;
        *(_BYTE *)(uintptr_t)(gridInitColumn + costGridRowOffset + tileCostGrid - 1) = tileMoveCost;
      }
      ++gridInitRow;
      costGridRowBase += 256;
      distGridRowBase += 200;
    }
    if ( sourceRow_l >= targetRow_l )
    {
      rowWindowMax = sourceRow_l;
      rowWindowMin = targetRow_l;
    }
    else
    {
      rowWindowMin = sourceRow_l;
      rowWindowMax = targetRow_l;
    }
    v22 = targetColumn;
    if ( sourceColumn_l >= targetColumn )
    {
      colWindowMax = sourceColumn_l;
      colWindowMin = targetColumn;
    }
    else
    {
      colWindowMin = sourceColumn_l;
      colWindowMax = targetColumn;
    }
    *(_WORD *)(uintptr_t)(200 * sourceRow_l + distanceGrid + 2 * sourceColumn_l) = 0;
    targetRowByteOffset = 200 * targetRow_l;
    expansionBudget = 25;
    targetColByteOffset = 2 * targetColumn;
    while ( 1 )
    {
      rowScanMax = rowWindowMax;
      DD_Pump((int)(intptr_t)g_RenderState, v22);
      WorldMap_RedrawFrameForAIWhenEnabled(v22);
      v22 = 0;
      anyRelaxed = 0;
      row = rowWindowMin;
      if ( rowWindowMin <= rowScanMax )
      {
        currentRowByteOffset = 200 * rowWindowMin;
        do
        {
          column = colWindowMin;
          if ( colWindowMin <= colWindowMax )
          {
            savedRowByteOffset = currentRowByteOffset;
            distRowByteOffset = currentRowByteOffset;
            colByteOffset = 2 * colWindowMin;
            do
            {
              currentDistance = *(unsigned __int16 *)(uintptr_t)(colByteOffset + distRowByteOffset + distanceGrid);
              if ( currentDistance != 65534 && currentDistance != 0xFFFF )
              {
                colByteOffsetSaved = colByteOffset;
                for ( i = 0; i != 16; i += 2 )
                {
                  neighborRow = Map_NeighborDX[i] + row;
                  neighborColumn = column + Map_NeighborDY[i];
                  if ( neighborRow >= rowWindowMin && neighborRow <= rowWindowMax && neighborColumn >= colWindowMin && neighborColumn <= colWindowMax )
                  {
                    LOWORD(stepCost) = *(unsigned __int8 *)(uintptr_t)(tileCostGrid + (neighborRow << 8) + neighborColumn);
                    if ( (_BYTE)stepCost )
                    {
                      if ( neighborRow != row && neighborColumn != column )
                        stepCost = (23 * (unsigned __int16)stepCost
                             - (__CFSHL__((23 * (unsigned __int16)stepCost) >> 31, 4)
                              + 16 * ((23 * (unsigned __int16)stepCost) >> 31))) >> 4;
                      currentCellDistPtr = (unsigned __int16 *)(uintptr_t)(colByteOffsetSaved + savedRowByteOffset + distanceGrid);
                      currentCellDistance = *currentCellDistPtr;
                      candidateDistance = (unsigned __int16)stepCost + currentCellDistance;
                      neighborDistPtr = (_WORD *)(uintptr_t)(distanceGrid + 200 * neighborRow + 2 * neighborColumn);
                      if ( (unsigned __int16)*neighborDistPtr > candidateDistance )
                      {
                        relaxFromDistance = *currentCellDistPtr;
                        anyRelaxed = 1;
                        *neighborDistPtr = relaxFromDistance + stepCost;
                      }
                    }
                    else
                    {
                      *(_WORD *)(uintptr_t)(distanceGrid + 200 * neighborRow + 2 * neighborColumn) = -1;
                    }
                  }
                }
              }
              v22 = colWindowMax;
              ++column;
              colByteOffset += 2;
            }
            while ( column <= colWindowMax );
          }
          currentRowByteOffset += 200;
          ++row;
        }
        while ( row <= rowWindowMax );
      }
      v30 = anyRelaxed;
      if ( !anyRelaxed )
      {
        if ( *(unsigned __int16 *)(uintptr_t)(targetColByteOffset + targetRowByteOffset + distanceGrid) != 65534 )
          break;
        if ( --rowWindowMin < 0 )
          rowWindowMin = anyRelaxed;
        mapWidthLimit = *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET);
        if ( ++rowWindowMax >= mapWidthLimit )
          rowWindowMax = mapWidthLimit - 1;
        if ( --colWindowMin < 0 )
          colWindowMin = 0;
        v30 = *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET);
        if ( ++colWindowMax >= v30 )
          colWindowMax = v30 - 1;
        v22 = expansionBudget - 1;
        expansionBudget = v22;
        if ( v22 == -1 )
          break;
      }
    }
    targetDistancePtr = (unsigned __int16 *)(uintptr_t)(2 * targetColumn + distanceGrid + 200 * targetRow_l);
    pathResult = 0;
    targetDistance = *targetDistancePtr;
    overflowFlag = 0;
    if ( targetDistance != 65534 )
    {
      LOWORD(targetDistancePtr) = *targetDistancePtr;
      traceRow = targetRow_l;
      currentTileDistance = targetDistancePtr;
      pathBuffer = (int *)(uintptr_t)Mem_Alloc(404, v30, distanceGrid, 0);
      traceColumn = targetColumn;
      if ( pathBuffer )
        *pathBuffer = 0;
      HIWORD(packedWaypoint) = HIWORD(g_UnitPathfindingScratchDword);
      LOBYTE(packedWaypoint) = traceRow;
      pathResult = pathBuffer;
      BYTE1(packedWaypoint) = traceColumn;
      waypointCount = *pathBuffer;
      HIWORD(packedWaypoint) = (_WORD)(intptr_t)currentTileDistance;
      if ( waypointCount < 100 )
      {
        v30 = 4 * waypointCount;
        *pathBuffer = waypointCount + 1;
        pathBuffer[waypointCount + 1] = packedWaypoint;
      }
      while ( (_WORD)(intptr_t)currentTileDistance )
      {
        rowDelta = -1;
        bestNeighborDistance = (unsigned __int16)(intptr_t)currentTileDistance;
        do
        {
          v30 = -1;
          do
          {
            traceColIndex = traceColumn;
            traceNeighborColumn = traceColumn + v30;
            traceNeighborRow = traceRow + rowDelta;
            if ( traceNeighborRow >= 0
              && traceNeighborRow < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
              && traceNeighborColumn >= 0
              && traceNeighborColumn < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
              && (unsigned __int16)bestNeighborDistance > *(_WORD *)(uintptr_t)(distanceGrid + 200 * traceNeighborRow + 2 * traceNeighborColumn) )
            {
              LOWORD(traceStepCost) = *(unsigned __int8 *)(uintptr_t)(traceColIndex + tileCostGrid + (traceRow << 8));
              if ( rowDelta && v30 )
                traceStepCost = (23 * (unsigned __int16)traceStepCost
                     - (__CFSHL__((23 * (unsigned __int16)traceStepCost) >> 31, 4)
                      + 16 * ((23 * (unsigned __int16)traceStepCost) >> 31))) >> 4;
              traceNeighborDistPtr = (_WORD *)(uintptr_t)(distanceGrid + 200 * (rowDelta + traceRow) + 2 * (v30 + traceColumn));
              traceStepCost = (unsigned __int16)traceStepCost;
              if ( (unsigned __int16)*traceNeighborDistPtr == (unsigned __int16)(intptr_t)currentTileDistance - (unsigned __int16)traceStepCost )
              {
                stepRowDelta = rowDelta;
                LOWORD(traceStepCost) = *traceNeighborDistPtr;
                stepColumnDelta = v30;
                bestNeighborDistance = traceStepCost;
              }
            }
            ++v30;
          }
          while ( v30 <= 1 );
          ++rowDelta;
        }
        while ( rowDelta <= 1 );
        traceRow += stepRowDelta;
        LOBYTE(packedWaypoint) = traceRow;
        traceColumn += stepColumnDelta;
        BYTE1(packedWaypoint) = traceColumn;
        currentTileDistance = (unsigned __int16 *)(uintptr_t)*(unsigned __int16 *)(uintptr_t)(200 * traceRow + distanceGrid + 2 * traceColumn);
        HIWORD(packedWaypoint) = (_WORD)(intptr_t)currentTileDistance;
        pathCount = *pathResult;
        if ( 100 - *pathResult <= 2 )
        {
          overflowFlag = 1;
          break;
        }
        if ( pathCount < 100 )
        {
          *pathResult = pathCount + 1;
          pathResult[pathCount + 1] = packedWaypoint;
        }
      }
      --*pathResult;
    }
    else if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_move_track_unreachable", stackIndex_l, targetRow_l, targetColumn, expansionBudget);
    }
    if ( overflowFlag && pathResult )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_overflow", stackIndex_l, targetRow_l, targetColumn, *pathResult);
      j__nfree_(pathResult);
      pathResult = 0;
    }
    sourceRowByte = sourceRow_l;
    *(_WORD *)(uintptr_t)(TILE_INDEX(sourceRow_l, sourceColumn_l)) = savedOccupant;
    nfree_(distanceGrid);
    distanceGrid = 0;
    nfree_(tileCostGrid);
    tileCostGrid = 0;
    if ( pathResult )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_built", stackIndex_l, targetRow_l, targetColumn, *pathResult);
        if ( *pathResult )
        {
          int raw_count = *pathResult;
          int raw_sample_index;
          int raw_waypoint;

          raw_sample_index = raw_count;
          raw_waypoint = pathResult[raw_sample_index];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            stackIndex_l,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            raw_sample_index);
          raw_sample_index = raw_count * 3 / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 2;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_waypoint = pathResult[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            stackIndex_l,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            1);
        }
      }
      pathResult = Path_InsertBridgeCornerWaypoints((int)(intptr_t)stackRecord, sourceRowByte, pathResult);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_ready", stackIndex_l, targetRow_l, targetColumn, pathResult ? *pathResult : -1);
        if ( pathResult && *pathResult )
        {
          traceWaypoint = pathResult[*pathResult];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_next",
            stackIndex_l,
            (unsigned __int8)traceWaypoint,
            BYTE1(traceWaypoint),
            HIWORD(traceWaypoint));
          traceWaypoint = pathResult[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_first",
            stackIndex_l,
            (unsigned __int8)traceWaypoint,
            BYTE1(traceWaypoint),
            HIWORD(traceWaypoint));
        }
      }
    }
    if ( cursorWasNotBusy && g_CursorOverlayPresented )
      RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, savedCursorDescriptor);
    return pathResult;
  }
  return result;
}
// 414801: conditional instruction was optimized away because edx.4>=0
// 414805: conditional instruction was optimized away because %arg_0.4>=0
// 4147D7: variable 'v6' is possibly undefined
// 4148F7: variable 'v14' is possibly undefined
// 414909: variable 'v16' is possibly undefined
// 414945: variable 'v17' is possibly undefined
// 414D58: variable 'v35' is possibly undefined
// 414FA3: variable 'v30' is possibly undefined
// 414FB0: variable 'v45' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 519808: using guessed type int dword_519808;
// 5202E4: using guessed type int gameData;
// 525570: using guessed type int dword_525570;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;

//----- (00415210) --------------------------------------------------------
_DWORD * Unit_MoveTrackNearTile(int stackIndex, int targetRow, int a3, int targetColumn, DWORD a5)
{
  UnitStackRecord *stack;
  int source_row;
  int source_column;
  int row_delta;
  int column_delta;
  __int16 saved_tile_occupant;
  int *raw_path;
  int *reverse_path;

  (void)a3;
  Debug_Log(stackIndex, targetColumn, a5, (int)(intptr_t)aUnit_movetra_1);
  if ( targetRow < 0 || targetRow >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) || targetColumn < 0 || targetColumn >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    return 0;

  stack = UNIT_STACK_RECORD(stackIndex);
  source_row = stack->tile_row;
  source_column = stack->tile_column;
  row_delta = source_row - targetRow;
  if ( row_delta < 0 )
    row_delta = -row_delta;
  column_delta = source_column - targetColumn;
  if ( column_delta < 0 )
    column_delta = -column_delta;
  if ( row_delta == 0 && column_delta == 0 )
  {
    raw_path = (int *)(uintptr_t)Mem_Alloc(404, gameData, targetColumn, a5);
    if ( raw_path )
      *raw_path = 0;
    return (_DWORD *)raw_path;
  }

  saved_tile_occupant = *(__int16 *)(uintptr_t)(TILE_INDEX(targetRow, targetColumn));
  *(_WORD *)(uintptr_t)(TILE_INDEX(targetRow, targetColumn)) = -1;
  WorldMap_DisableFrameRedraw();
  raw_path = Unit_MoveTrack(stackIndex, source_row, targetRow, source_column, targetColumn, targetColumn);
  if ( raw_path )
  {
    reverse_path = (int *)(uintptr_t)Mem_Alloc(404, (int)(intptr_t)raw_path, source_column, targetColumn);
    if ( reverse_path )
    {
      *reverse_path = 0;
      while ( *raw_path )
      {
        int raw_count = *raw_path - 1;
        int step = raw_path[raw_count + 1];

        *raw_path = raw_count;
        if ( *reverse_path < 100 )
        {
          int reverse_count = *reverse_path;

          *reverse_path = reverse_count + 1;
          reverse_path[reverse_count + 1] = step;
        }
      }
      --*reverse_path;
      while ( *reverse_path > 0 )
      {
        int reverse_count = *reverse_path - 1;
        int step = reverse_path[reverse_count + 1];

        *reverse_path = reverse_count;
        if ( *raw_path < 100 )
        {
          int raw_count = *raw_path;

          *raw_path = raw_count + 1;
          raw_path[raw_count + 1] = step;
        }
      }
      nfree_((int)(intptr_t)reverse_path);
    }
  }
  *(_WORD *)(uintptr_t)(TILE_INDEX(targetRow, targetColumn)) = saved_tile_occupant;
  Render_LoadResourceSprite_v2();
  return (_DWORD *)raw_path;
}
// 415210: could not find valid save-restore pair for ebx
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00415450) --------------------------------------------------------
int * Building_GenerateApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)
{
  int building_record;
  int building_row;
  int building_column;
  int building_kind;
  UnitStackRecord *stack;
  int source_row;
  int source_column;
  __int16 saved_origin_surface;
  unsigned __int16 building_tile;
  int *raw_path;
  int *reverse_path;

  (void)a3;
  (void)a4;
  Debug_Log(stackIndex, (char)buildingIndex, a5, (int)(intptr_t)aUnit_movetra_0);

  building_record = BUILDING_RECORD(buildingIndex);
  building_row = *(unsigned __int8 *)(uintptr_t)building_record;
  building_column = *(unsigned __int8 *)(uintptr_t)(building_record + 1);
  building_kind = *(signed char *)(uintptr_t)(building_record + 4);
  building_tile = (unsigned __int16)(buildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE);

  *(_WORD *)(uintptr_t)(TILE_INDEX(building_row, building_column)) = -1;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row + 1, building_column)) = -1;
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row + 1, building_column + 1)) = -1;
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row, building_column + 1)) = -1;
  }

  saved_origin_surface = *(__int16 *)(uintptr_t)(gameData
                                    + TILE_TERRAIN_ROW_STRIDE * building_row
                                    + TILE_TERRAIN_RECORD_STRIDE * building_column
                                    + 4);
  *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) = 872;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) = 872;
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) = 872;
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) = 872;
  }

  WorldMap_DisableFrameRedraw();
  stack = UNIT_STACK_RECORD(stackIndex);
  source_row = stack->tile_row;
  source_column = stack->tile_column;
  raw_path = Unit_MoveTrack(stackIndex, source_row, building_row, source_column, building_kind, building_column);
  if ( raw_path )
  {
    reverse_path = (int *)(uintptr_t)(unsigned int)Mem_Alloc(404, (int)(uintptr_t)raw_path, source_column, building_kind);
    if ( reverse_path )
    {
      *reverse_path = 0;
      while ( *raw_path )
      {
        int raw_count = *raw_path - 1;
        int step = raw_path[raw_count + 1];

        *raw_path = raw_count;
        if ( *reverse_path < 100 )
        {
          int reverse_count = *reverse_path;

          *reverse_path = reverse_count + 1;
          reverse_path[reverse_count + 1] = step;
        }
      }
      while ( *reverse_path > 1 )
      {
        int step = reverse_path[*reverse_path - 1];
        int step_row = (unsigned __int8)step;
        int step_column = BYTE1(step);

        if ( step_row == building_row && step_column == building_column )
        {
          --*reverse_path;
          continue;
        }
        if ( (building_kind == 1 || building_kind == 2)
          && step_row >= building_row
          && step_row <= building_row + 1
          && step_column >= building_column
          && step_column <= building_column + 1 )
        {
          --*reverse_path;
          continue;
        }
        break;
      }
      while ( *reverse_path )
      {
        int reverse_count = *reverse_path - 1;
        int step = reverse_path[reverse_count + 1];

        *reverse_path = reverse_count;
        if ( *raw_path < 100 )
        {
          int raw_count = *raw_path;

          *raw_path = raw_count + 1;
          raw_path[raw_count + 1] = step;
        }
      }
      nfree_((int)(uintptr_t)reverse_path);
    }
  }

  Render_LoadResourceSprite_v2();
  *(_WORD *)(uintptr_t)(TILE_INDEX(building_row, building_column)) = building_tile;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row + 1, building_column)) = building_tile;
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row + 1, building_column + 1)) = building_tile;
    *(_WORD *)(uintptr_t)(TILE_INDEX(building_row, building_column + 1)) = building_tile;
  }
  *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) =
    saved_origin_surface;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) =
      -1;
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) =
      -1;
    *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) =
      -1;
  }

  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent(
      "building_path_ready",
      stackIndex,
      building_row,
      building_column,
      raw_path ? *raw_path : -1);
  return raw_path;
}
// 415450: asm-backed rewrite; clears/restores building footprint around Unit_MoveTrack.
// 5202E4: using guessed type int gameData;

//----- (00415970) --------------------------------------------------------
int  Building_GenerateNearApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)
{
  int buildingRecordOffset; // edi
  DWORD buildingKind; // ebp
  __int64 buildingRowCol; // rdi
  int nextRowByteOffset; // eax
  UnitStackRecord *stack;
  int sourceColumn; // ebx
  int *rawPath; // ecx
  int *reverseBuffer; // eax
  int *forwardPath; // ecx
  int *reversePath; // edx
  int poppedCount; // ebx
  int occupantNextRowByteOffset; // eax
  int forwardRawCount; // eax
  int reverseCount; // ebx
  int candidateStep; // eax
  int candidateColumn; // eax
  int poppedStep; // eax
  int destCount; // ebx
  __int16 buildingIndexWord; // [esp+8h] [ebp-28h]
  int stepForward; // [esp+18h] [ebp-18h]

  buildingIndexWord = buildingIndex;
  buildingRecordOffset = BUILDING_RECORD_SIZE * buildingIndex;
  Debug_Log(a3, a4, a5, (int)(intptr_t)aUnit_movetra_3);
  HIDWORD(buildingRowCol) = *(unsigned __int8 *)(uintptr_t)(gameData + buildingRecordOffset + BUILDING_TABLE_OFFSET);
  buildingKind = *(char *)(uintptr_t)(gameData + buildingRecordOffset + 509678);
  LODWORD(buildingRowCol) = *(unsigned __int8 *)(uintptr_t)(gameData + buildingRecordOffset + 509675);
  /* buildingRowCol is a register PAIR: HIDWORD = row, LODWORD = column.
     Using the whole 64-bit value as the column made the tile address explode. */
  *(_WORD *)(TILE_INDEX(HIDWORD(buildingRowCol), (unsigned int)buildingRowCol)) = -1;
  if ( buildingKind == 1 || buildingKind == 2 )
  {
    nextRowByteOffset = 200 * (HIDWORD(buildingRowCol) + 1);
    *(_WORD *)(nextRowByteOffset + gameData + 2 * (unsigned int)buildingRowCol + TILE_MAP_OFFSET) = -1;
    *(_WORD *)(gameData + nextRowByteOffset + 2 * (unsigned int)buildingRowCol + 556376) = -1;
    *(_WORD *)(gameData + 200 * HIDWORD(buildingRowCol) + 2 * (unsigned int)buildingRowCol + 556376) = -1;
  }
  /* 00415A4D computes gameData + 725 * stackIndex before reading
     the stack row and column. The typed overlay expresses that recovered layout
     directly while preserving the original call sequence. */
  WorldMap_DisableFrameRedraw();
  stack = UNIT_STACK_RECORD(stackIndex);
  sourceColumn = stack->tile_column;
  rawPath = Unit_MoveTrack(
              stackIndex,
              stack->tile_row,
              SHIDWORD(buildingRowCol),
              sourceColumn,
              buildingKind,
              (int)buildingRowCol);
  /*
   * asm 00415A97: `mov ecx, eax` right after the Unit_MoveTrack call -- ecx
   * holds the returned path for the rest of the routine (Mem_Alloc and every
   * other callee preserve ecx) and is what the epilogue returns
   * (loc_415B9B: `mov eax, ecx`). The decompiler split that single register
   * into rawPath / forwardPath / result and left the latter two unassigned, so
   * the path array was walked and returned through wild pointers.
   */
  forwardPath = rawPath;
  if ( rawPath )
  {
    reverseBuffer = (int *)(uintptr_t)Mem_Alloc(404, (int)(intptr_t)rawPath, sourceColumn, buildingKind);
    reversePath = reverseBuffer;
    /* 415A96: `mov ecx, eax` after Unit_MoveTrack - the forward cursor is the
       raw path that was just returned. */
    forwardPath = rawPath;
    if ( reverseBuffer )
      *reverseBuffer = 0;
    for ( ; *forwardPath; reversePath[reverseCount + 1] = stepForward )
    {
      while ( 1 )
      {
        forwardRawCount = *forwardPath - 1;
        *forwardPath = forwardRawCount;
        reverseCount = *reversePath;
        stepForward = forwardPath[forwardRawCount + 1];
        if ( *reversePath < 100 )
          break;
        if ( !*forwardPath )
          goto LABEL_8;
      }
      *reversePath = reverseCount + 1;
    }
LABEL_8:
    while ( *reversePath > 1 )
    {
      candidateStep = reversePath[*reversePath - 1];
      if ( buildingRowCol != __PAIR64__((unsigned __int8)candidateStep, BYTE1(candidateStep)) )
      {
        if ( buildingKind != 1 && buildingKind != 2 )
          break;
        if ( SHIDWORD(buildingRowCol) > (unsigned __int8)candidateStep )
          break;
        if ( (unsigned __int8)candidateStep > HIDWORD(buildingRowCol) + 1 )
          break;
        candidateColumn = BYTE1(candidateStep);
        if ( (int)buildingRowCol > candidateColumn || candidateColumn > (int)buildingRowCol + 1 )
          break;
      }
      --*reversePath;
    }
    if ( *reversePath )
      --*reversePath;
    while ( 1 )
    {
      poppedCount = *reversePath;
      if ( !*reversePath )
        break;
      *reversePath = poppedCount - 1;
      poppedStep = reversePath[poppedCount];
      destCount = *forwardPath;
      if ( *forwardPath < 100 )
      {
        *forwardPath = destCount + 1;
        forwardPath[destCount + 1] = poppedStep;
      }
    }
    j__nfree_();
  }
  *(_WORD *)(2 * (unsigned int)buildingRowCol + gameData + TILE_ROW_STRIDE * HIDWORD(buildingRowCol) + TILE_MAP_OFFSET) = buildingIndexWord + TILE_OCCUPANT_BUILDING_INDEX_BASE;
  if ( buildingKind == 1 || buildingKind == 2 )
  {
    occupantNextRowByteOffset = 200 * (HIDWORD(buildingRowCol) + 1);
    *(_WORD *)(occupantNextRowByteOffset + gameData + 2 * (unsigned int)buildingRowCol + TILE_MAP_OFFSET) = buildingIndexWord + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(gameData + occupantNextRowByteOffset + 2 * (unsigned int)buildingRowCol + 556376) = buildingIndexWord + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(gameData + 200 * HIDWORD(buildingRowCol) + 2 * (unsigned int)buildingRowCol + 556376) = buildingIndexWord + TILE_OCCUPANT_BUILDING_INDEX_BASE;
  }
  Render_LoadResourceSprite_v2();
  /* 415B9B: 'call Render_LoadResourceSprite_v2; mov eax, ecx; ... retn' - the
     return value is ECX, and ECX was loaded at 415A94 ('mov ecx, eax')
     immediately after 'call Unit_MoveTrack', i.e. it is the raw forward track
     the pathfinder returned (0 when Unit_MoveTrack failed - loc_415AEA is
     reached with ecx = eax = 0).  Nothing between 415A94 and 415BA0 writes ecx.
     The decompiler dropped that assignment and emitted a never-initialised
     'result' (IDA flags it at 415BA0), so this routine returned a stale
     register.  Its callers memcpy 0x194 bytes FROM that value straight into the
     unit stack's queued-path buffer, which is why the queued path's step count
     came back as a heap pointer and UnitStack_ExecuteQueuedPath segfaulted on
     'pathBuffer[*pathBuffer]'. */
  return (int)(intptr_t)rawPath;
}
// 415A64/415AAD/415BA0: decompiler 'possibly undefined' notes for v9/v13/v17 --
//   v9 is edx = stackIndex across the WorldMap_DisableFrameRedraw call, and
//   v13/v17 are ecx = the Unit_MoveTrack result; repaired above.
// 5202E4: using guessed type int gameData;

//----- (00415C90) --------------------------------------------------------
void  Pathing_EnableBridgeCrossings(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)(intptr_t)aTrack_bridgeso);
  g_PathingAllowBridgeCrossings = 1;
}
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00415CB0) --------------------------------------------------------
void  Pathing_DisableBridgeCrossings(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)(intptr_t)aTrack_bridge_0);
  g_PathingAllowBridgeCrossings = 0;
}
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00415CD0) --------------------------------------------------------
BOOL  QueuedPath_StartsAtTile(_DWORD *pathBuffer, int tileRow, int tileColumn)
{
  int firstStep; // eax

  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  return (unsigned __int8)firstStep == tileRow && BYTE1(firstStep) == tileColumn;
}

//----- (00415D00) --------------------------------------------------------
BOOL  QueuedPath_StartsInBuildingFootprint(_DWORD *pathBuffer, int buildingIndex)
{
  unsigned __int8 *buildingRecord; // eax
  int firstStep; // edx
  BOOL result; // eax
  unsigned __int8 buildingColumn; // bh

  buildingRecord = (unsigned __int8 *)(uintptr_t)(UNIT_RECORD(buildingIndex));
  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  if ( !buildingRecord[4] )
    return (_WORD)firstStep == *(_WORD *)buildingRecord;
  result = 0;
  if ( (unsigned __int8)firstStep >= *buildingRecord && (unsigned __int8)firstStep <= *buildingRecord + 1 )
  {
    buildingColumn = buildingRecord[1];
    if ( BYTE1(firstStep) >= buildingColumn && BYTE1(firstStep) <= buildingColumn + 1 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00415D80) --------------------------------------------------------
int  Math_SinDegreesQ16(signed int degrees)
{
  int angle; // edx
  int absAngle; // edx

  angle = degrees;
  if ( degrees < 0 )
  {
    absAngle = -degrees;
    if ( -degrees >= 360 )
      absAngle %= 360;
    return -g_MathSinTableQ16[absAngle];
  }
  else
  {
    if ( degrees >= 360 )
      angle = degrees % 360;
    return g_MathSinTableQ16[angle];
  }
}
// 513434: using guessed type int dword_513434[363];

//----- (00415DD0) --------------------------------------------------------
void  initRandomSeed(char a1, DWORD a2)
{
  int v2; // ecx

  g_RngState = time_();
  Debug_Log(v2, a1, a2, (int)(intptr_t)aRandom_initSee);
}
// 415DE2: variable 'v2' is possibly undefined
// 47627F: using guessed type int time_(void);
// 525578: using guessed type int dword_525578;

//----- (00415DF0) --------------------------------------------------------
unsigned int  Rng_RandRange(int minValue, int maxValue)
{
  unsigned int range;
  unsigned int seed;
  int result;

  g_RngState ^= Time_Now(0, 0) + 0x34523471u;
  seed = (unsigned int)g_RngState + 0x83356532u * (unsigned int)Time_Now(0, 0);
  g_RngState = (int)seed;
  range = (unsigned int)((__int64)maxValue + 1 - minValue);
  if ( !range )
    return (unsigned int)minValue;
  result = (int)(seed % range) + minValue;
  return (unsigned int)result;
}
// 525578: using guessed type int dword_525578;

//----- (00415E40) --------------------------------------------------------
signed int  Math_CeilSqrt(signed int value)
{
  int quotient; // eax
  int estimate; // ecx

  if ( value < 4 )
    return 1;
  quotient = value / 20 + 2;
  estimate = quotient;
  do
  {
    while ( 1 )
    {
      estimate = (estimate + quotient) / 2;
      quotient = value / estimate;
      if ( estimate - value / estimate <= 0 )
        break;
      if ( estimate - value / estimate <= 1 )
        return estimate;
    }
  }
  while ( value / estimate - estimate > 1 );
  return estimate;
}

//----- (00415EA0) --------------------------------------------------------
__int16  WorldMap_DrawUnitStackOverlayGlyph(int screenX, int screenY, unsigned __int16 *tilePtr)
{
  unsigned int glyphCode; // eax
  int sprite; // eax

  glyphCode = *tilePtr;
  if ( glyphCode >= 0x2D && *tilePtr <= 0x58u )
  {
    LOWORD(glyphCode) = tilePtr[2];
    if ( (unsigned __int16)glyphCode == 0xFFFF )
    {
      TextSprite_SetStyleFlag(1);
      sprite = DLX_GetSpriteForChar(g_TreeSpriteSet, *tilePtr - 45);
      LOWORD(glyphCode) = Compat_RenderDeviceDrawMenuSprite(screenX, screenY, sprite, 1);
    }
  }
  return glyphCode;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202D8: using guessed type int dword_5202D8;

//----- (00415F20) --------------------------------------------------------
int  WorldMap_DrawUnitStackWithOverlays(int result, int screenX, int screenY, int animOffsetY, unsigned __int16 *tilePtr)
{
  int stackRecord; // eax
  int spriteVerticalOffset; // ebp
  int SpriteForChar; // eax
  int drawY; // ebx
  int nowTick; // eax
  int flashSin; // eax
  DWORD v13; // ebp
  int v14; // ecx
  signed int squadCount; // eax
  int squadCountSprite; // eax
  int v17 CLASH95_UNUSED; // ecx
  int moraleSprite; // eax
  int v19 CLASH95_UNUSED; // ecx
  int overlaySprite; // eax
  int v21 CLASH95_UNUSED; // ecx
  int tileRightX; // [esp+64h] [ebp-20h]
  int unitSpriteCopy; // [esp+6Ch] [ebp-18h]
  int stackIndex; // [esp+74h] [ebp-10h]

  stackIndex = result;
  if ( result < 0x8000 )
  {
    result = gameData + UNIT_STACK_STRIDE * result;
    if ( *(__int16 *)(uintptr_t)(result + 147180) != -1 )
    {
      if ( !*(_BYTE *)(uintptr_t)(result + 147894) || (result = *(unsigned __int8 *)(uintptr_t)(result + 147178), result == g_CurrentPlayerIndex) )
      {
        stackRecord = gameData + UNIT_STACK_STRIDE * stackIndex;
        spriteVerticalOffset = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(uintptr_t)(stackRecord + 147180)];
        if ( g_ActiveUnitMoveTileIndex == -1 || g_ActiveUnitMoveTileIndex != stackIndex )
          SpriteForChar = UnitSpriteCache_FindEntryOrLoad(
                            *(unsigned __int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180),
                            *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178),
                            *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147197) & 7,
                            *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147179));
        else
          SpriteForChar = DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, 8 * *(unsigned __int8 *)(uintptr_t)(stackRecord + 147179) + g_UnitAnimFrameIndex);
        unitSpriteCopy = SpriteForChar;
        tileRightX = screenX + 63;
        drawY = screenY + animOffsetY - spriteVerticalOffset;
        if ( stackIndex == g_WorldMapAttentionFlashUnitIndex )
        {
          nowTick = Time_Now(screenY + 63, spriteVerticalOffset);
          flashSin = Math_SinDegreesQ16(30 * (g_WorldMapAttentionFlashStartTick - nowTick));
          v13 = screenX + 63;
          Sprite_DrawSimpleTrackingOffset(
            unitSpriteCopy,
            screenX,
            drawY,
            screenY,
            tileRightX,
            v14,
            ((126 * flashSin - (__CFSHL__((126 * flashSin) >> 31, 16) + ((126 * flashSin) >> 31 << 16))) >> 16) + 128,
            1u);
        }
        else
        {
          v13 = gameData;
          if ( *(_BYTE *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + 147894) )
          {
            Sprite_DrawSimpleTrackingOffset(SpriteForChar, screenX, drawY, screenY, tileRightX, screenY + 63, 128, 1u);
          }
          else
          {
            Compat_RenderDeviceDrawMenuSprite(screenX, drawY, SpriteForChar, 1);
          }
        }
        if ( (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180)] & 1) == 0 )
          WorldMap_DrawUnitStackOverlayGlyph(screenX, screenY, tilePtr);
        squadCount = Unit_GetSquadCount(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( squadCount > 1 )
        {
          squadCountSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, squadCount + 5);
          Compat_RenderDeviceDrawMenuSprite(screenX + 12, drawY + 48, squadCountSprite, 1);
        }
        if ( UnitStack_HasLowMoraleUnit(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
        {
          moraleSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, 33);
          Compat_RenderDeviceDrawMenuSprite(screenX + 30, drawY + 48, moraleSprite, 1);
        }
        if ( *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147894) )
        {
          overlaySprite = DLX_GetSpriteForChar(g_MarksSpriteSet, 39);
          Compat_RenderDeviceDrawMenuSprite(screenX + 10, drawY + 5, overlaySprite, 1);
        }
        if ( stackIndex == g_UnitBlinkFlashUnitIndex )
        {
          overlaySprite = DLX_GetSpriteForChar(g_WhirlSpriteSet, g_UnitBlinkFlashFrame);
          Compat_RenderDeviceDrawMenuSprite(screenX, screenY, overlaySprite, 1);
        }
        result = gameData;
        if ( *(_DWORD *)(uintptr_t)(gameData + 147155) )
        {
          TextSprite_ActivateResourceSlot(3, 76, v13);
          return UI_DrawText(screenX + 20, screenY + 25, (int)(intptr_t)aD_0);
        }
      }
    }
  }
  return result;
}
// 415F37: simplified comparisons for 'eax.4': ==FFFF || >=8000 became >=8000
// 416096: variable 'v14' is possibly undefined
// 41615F: variable 'v17' is possibly undefined
// 4161ED: variable 'v19' is possibly undefined
// 416268: variable 'v21' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 5139F8: using guessed type int dword_5139F8;
// 5202C8: using guessed type int dword_5202C8;
// 5202D0: using guessed type int dword_5202D0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;
// 5269A4: using guessed type int dword_5269A4;

//----- (004163F0) --------------------------------------------------------
unsigned int __thiscall Map_InitBuildingSwayJitterOffsets(void *this)
{
  int offset;
  unsigned int result;

  (void)this;
  offset = 0;
  do
  {
    g_BuildingSwayJitterOffsetsX[offset] = Rng_RandRange(-20, 20);
    offset += 2;
    result = Rng_RandRange(-20, 20);
    g_BuildingSwayJitterOffsetsOdd[offset] = result;
  }
  while ( offset != 30 );
  return result;
}

//----- (00416430) --------------------------------------------------------
unsigned __int8 *__thiscall Map_UpdateConstructionSiteSwayAnimation(void *this)
{
  unsigned __int8 *result; // eax
  unsigned int now; // eax
  int offset; // ecx
  int building_offset; // ecx
  unsigned __int8 *building_record; // eax
  char jitterDeltaX; // al
  char jitterDeltaY; // al

  (void)this;
  now = Time_Now(0, 0);
  result = (unsigned __int8 *)(uintptr_t)now;
  if ( (unsigned int)(g_MapConstructionSwayAnimLastTick + 20) <= now )
  {
    g_MapConstructionSwayAnimLastTick = Time_Now(0, 0);
    for ( offset = 0; offset != 30; offset += 2 )
    {
      if ( Rng_RandRange(0, 20) > 0x11 )
      {
        if ( g_BuildingSwayJitterOffsetsX[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( g_BuildingSwayJitterOffsetsX[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            jitterDeltaX = Rng_RandRange(-1, 1);
            g_BuildingSwayJitterOffsetsX[offset] += jitterDeltaX;
          }
          else
          {
            ++g_BuildingSwayJitterOffsetsX[offset];
          }
        }
        else
        {
          --g_BuildingSwayJitterOffsetsX[offset];
        }
        if ( g_BuildingSwayJitterOffsetsY[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( g_BuildingSwayJitterOffsetsY[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            jitterDeltaY = Rng_RandRange(-1, 1);
            g_BuildingSwayJitterOffsetsY[offset] += jitterDeltaY;
          }
          else
          {
            ++g_BuildingSwayJitterOffsetsY[offset];
          }
        }
        else
        {
          --g_BuildingSwayJitterOffsetsY[offset];
        }
      }
    }
    for ( building_offset = 0; building_offset != 46700; building_offset += 467 )
    {
      building_record = (unsigned __int8 *)(uintptr_t)(building_offset + gameData + BUILDING_TABLE_OFFSET);
      result = building_record;
      if ( *(__int16 *)(building_record + 16) == -1 )
      {
        if ( building_record[4] )
        {
          WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1]);
          WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
          WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1] + 1);
          result = (unsigned __int8 *)(uintptr_t)WorldMap_RedrawTileIfVisible(
                                        building_record[0],
                                        building_record[1] + 1);
        }
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 526980: using guessed type int dword_526980;

//----- (00416610) --------------------------------------------------------
unsigned int __thiscall Map_UpdateIdleAnimatedBuildings(void *this)
{
  unsigned int result; // eax
  int building_offset; // ecx
  unsigned __int8 *building_record; // eax
  unsigned __int8 building_kind; // dl

  (void)this;
  result = Time_Now(0, 0);
  if ( (unsigned int)(g_MapIdleBuildingAnimLastTick + 10) <= result )
  {
    g_MapIdleBuildingAnimLastTick = Time_Now(0, 0);
    g_MapFlagAnimationFrame = ((_BYTE)g_MapFlagAnimationFrame + 1) & 0xF;
    for ( building_offset = 0; building_offset != 46700; building_offset += 467 )
    {
      building_record = (unsigned __int8 *)(uintptr_t)(building_offset + gameData + BUILDING_TABLE_OFFSET);
      result = (unsigned int)(intptr_t)building_record;
      if ( *(char *)(building_record + 4) != -1 && !*(_WORD *)(building_record + 16) )
      {
        building_kind = building_record[4];
        if ( building_kind )
        {
          if ( building_kind <= 2u )
          {
            WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
            WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1]);
            WorldMap_RedrawTileIfVisible(building_record[0], building_record[1] + 1);
            result = WorldMap_RedrawTileIfVisible(
                       building_record[0] + 1,
                       building_record[1] + 1);
          }
        }
        else
        {
          result = WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
        }
      }
    }
  }
  return result;
}
// 416738: simplified comparisons for 'dl.1': <2u || ==2 became <3u
// 5202E4: using guessed type int gameData;
// 526984: using guessed type int dword_526984;
// 526998: using guessed type int dword_526998;

//----- (00416750) --------------------------------------------------------
int  WorldMap_DrawUnitAttentionFlashGlow(int screenX, int screenY, unsigned int buildingPhase)
{
  int i; // esi
  int jitterX; // eax
  int drawY; // ebx
  int jitterY; // edx
  int SpriteForChar; // eax
  int result; // eax
  int raisedY; // edx
  int alpha; // [esp-8h] [ebp-20h]
  int baseY; // [esp+8h] [ebp-10h]

  baseY = screenY;
  if ( buildingPhase >= 2 )
  {
    raisedY = screenY - 64;
    if ( buildingPhase <= 2 )
    {
      baseY = raisedY;
    }
    else if ( buildingPhase == 3 )
    {
      baseY = raisedY;
    }
  }
  for ( i = 0; i != 30; i += 2 )
  {
    jitterX = g_BuildingSwayJitterOffsetsX[i];
    drawY = baseY + g_BuildingSwayJitterOffsetsY[i] + 52;
    if ( jitterX <= 0 )
      jitterX = -jitterX;
    jitterY = g_BuildingSwayJitterOffsetsY[i];
    if ( jitterY <= 0 )
      jitterY = -jitterY;
    alpha = 50 - (jitterX + jitterY) / 3;
    SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 36);
    result = Sprite_DrawSimpleTrackingOffset(SpriteForChar, screenX, drawY, screenY, screenX + 63, screenY + 63, alpha, 1u);
  }
  return result;
}
// 5202C8: using guessed type int dword_5202C8;
