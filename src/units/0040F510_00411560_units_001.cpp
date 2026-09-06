/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "units_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0040F510) --------------------------------------------------------
signed int  Unit_Create(unit_type unitType, int ownerIndex, int tileRow, int facing_promoted, int tileColumn)
{
  char facing = (char)facing_promoted;
  int stackScanCount;
  int foundFreeStack;
  int stackScanOffset;
  int stackTypeWord;
  int stackIndex;
  int v12;
  UnitStackRecord *candidateStack;
  UnitStackRecord *stack;
  int tileRowBase;
  int v15;
  int v16;
  int v17;

  stackScanCount = 0;
  Debug_Log(tileRow, facing, unitType, (int)(intptr_t)aUnit_createDDD);
  foundFreeStack = 0;
  stackScanOffset = 0;
  do
  {
    candidateStack = (UnitStackRecord *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + stackScanOffset);
    stackTypeWord = candidateStack->unit_slots[0].unit_type_id;
    if ( stackTypeWord == -1 )
      foundFreeStack = 1;
    stackScanOffset += UNIT_STACK_STRIDE;
    ++stackScanCount;
  }
  while ( stackScanOffset < UNIT_STACK_STRIDE * UNIT_STACK_TABLE_COUNT && !foundFreeStack );
  stackIndex = stackScanCount - 1;
  if ( foundFreeStack )
  {
    if ( UnitStack_IsIndexOnMap(stackIndex) )
      Debug_Log(v12, facing, unitType, (int)(intptr_t)aUnit_createErr);
    stack = UNIT_STACK_RECORD(stackIndex);
    tileRowBase = TILE_ROW_STRIDE * tileRow + gameData;
    if ( *(unsigned __int16 *)(uintptr_t)(tileRowBase + 2 * tileColumn + TILE_MAP_OFFSET) == 0xFFFF )
    {
      if ( unitType == -1 || Map_GetUnitTileMoveCostOrZero(unitType, ownerIndex, tileColumn, tileRow) )
      {
        UnitStack_ResetRecord((int)(intptr_t)stack, unitType, ownerIndex);
        stack->tile_row = tileRow;
        stack->tile_column = tileColumn;
        stack->facing_direction = facing;
        v16 = gameData;
        *(_WORD *)(uintptr_t)(TILE_INDEX(tileRow, tileColumn)) = stackIndex;
        UnitStack_UpdateVision(stackIndex);
        Rules_CreateArmyFact((clash95_unaligned_int16 *)stack, stackIndex, v16, ownerIndex, unitType);
        Debug_Log(v17, ownerIndex, unitType, (int)(intptr_t)aUnit_createOk0);
        return 1;
      }
      Debug_Log(v15, tileRow, unitType, (int)(intptr_t)aUnit_createE_2);
      return 0;
    }
    Debug_Log(tileRowBase, facing, unitType, (int)(intptr_t)aUnit_createE_1);
    return 0;
  }
  Debug_Log(stackTypeWord, facing, unitType, (int)(intptr_t)aUnit_createE_0);
  return 0;
}

//----- (0040F6E0) --------------------------------------------------------
unsigned int  UnitStack_LinkArmyFact(__int16 *stackPtr, char a2, DWORD a3)
{
  UnitStackRecord *stack = (UnitStackRecord *)stackPtr;
  return Rules_CreateArmyFact(
    stackPtr,
    *(unsigned __int16 *)(uintptr_t)TILE_INDEX(stack->tile_row, stack->tile_column),
    (int)(intptr_t)stackPtr,
    a2,
    a3);
}

//----- (0040F730) --------------------------------------------------------
int  Unit_Kill(int stackRecord, char killReason, DWORD a3, double a4)
{
  UnitStackRecord *stack;
  UnitSlotRecord *slot;
  int row;
  int column;
  int slot_ordinal;

  stack = (UnitStackRecord *)(uintptr_t)stackRecord;
  Debug_Log(stackRecord, killReason, a3, (int)(intptr_t)aUnit_kill0x08x);
  Unit_DebugDumpFormationSizes(stackRecord, a3);
  Rules_RetractArmyFact((_DWORD *)(uintptr_t)stackRecord, 0, stackRecord, a4);
  row = stack->tile_row;
  column = stack->tile_column;
  Diagnostics_TraceWorldMapActionEvent(
    "unit_kill",
    Diagnostics_UnitStackIndexFromRecord(stackRecord),
    row,
    column,
    Unit_GetSquadCount(stackRecord));
  *(_WORD *)(uintptr_t)(TILE_INDEX(row, column)) = -1;
  slot_ordinal = 1;
  slot = &stack->unit_slots[0];
  do
  {
    ++slot_ordinal;
    slot->unit_type_id = -1;
    ++slot;
  }
  while ( slot_ordinal < UNIT_STACK_SLOT_COUNT );
  MiniMap_DrawTileCell((void *)(uintptr_t)row, column);
  return MiniMap_RedrawTileRect(row, column, column, row);
}

//----- (0040F7C0) --------------------------------------------------------
int  UnitStack_KillByIndex(int stackIndex, char killReason, DWORD a3, double a4)
{
  return Unit_Kill((int)(intptr_t)UNIT_STACK_RECORD(stackIndex), killReason, a3, a4);
}

//----- (0040F800) --------------------------------------------------------
__int16 * UnitStack_RemoveFromTile(__int16 *stack, double a2)
{
  UnitStackRecord *stackRecord;
  int stackPtr;
  int row;
  int column;

  stackRecord = (UnitStackRecord *)stack;
  stackPtr = (int)(intptr_t)stack;
  row = stackRecord->tile_row;
  if ( row >= 0 && row <= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 )
  {
    column = stackRecord->tile_column;
    if ( column >= 0 && column <= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 )
    {
      Rules_RetractArmyFact((_DWORD *)(uintptr_t)stackPtr, column, stackPtr, a2);
      *(_WORD *)(uintptr_t)(TILE_INDEX(row, column)) = -1;
      MiniMap_DrawTileCell((void *)(uintptr_t)row, column);
      return (__int16 *)(uintptr_t)MiniMap_RedrawTileRect(row, column, column, row);
    }
  }
  return stack;
}

__int16 * Rules_UnlinkArmyFact(__int16 *result, double a2)
{
  return UnitStack_RemoveFromTile(result, a2);
}

//----- (0040F890) --------------------------------------------------------
__int16 * UnitStack_UnlinkIfEmpty(__int16 *result, double a2)
{
  UnitStackRecord *stack = (UnitStackRecord *)result;
  if ( stack->unit_slots[0].unit_type_id == -1 )
    return Rules_UnlinkArmyFact(result, a2);
  return result;
}

__int16 * Rules_LinkArmyFinalize(__int16 *result, double a2)
{
  return UnitStack_UnlinkIfEmpty(result, a2);
}

//----- (0040F8B0) --------------------------------------------------------
int  UnitStack_GetVisionRadius(int stackPtr)
{
  UnitStackRecord *stack;
  int maxRadius;
  int slotIndex;
  int unitType;
  int slotRadius;

  stack = (UnitStackRecord *)(uintptr_t)stackPtr;
  unitType = stack->unit_slots[0].unit_type_id;
  maxRadius = g_UnitTypeRuntimeCoreMetadata[unitType].vision_radius;
  for ( slotIndex = 1; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    unitType = stack->unit_slots[slotIndex].unit_type_id;
    if ( unitType == -1 )
      break;
    slotRadius = g_UnitTypeRuntimeCoreMetadata[unitType].vision_radius;
    if ( slotRadius > maxRadius )
      maxRadius = slotRadius;
  }
  return maxRadius;
}

//----- (0040F900) --------------------------------------------------------
signed int  UnitStack_UpdateVision(int stackIndex)
{
  UnitStackRecord *stack;
  int originRow;
  int originColumn;
  int radius;
  int previousPlayer;
  int updated;
  int row;
  int column;

  stack = UNIT_STACK_RECORD(stackIndex);
  if ( stack->unit_slots[0].unit_type_id == -1 )
    return 0;
  originRow = stack->tile_row;
  originColumn = stack->tile_column;
  radius = UnitStack_GetVisionRadius((int)(intptr_t)stack);
  previousPlayer = g_CurrentPlayerIndex;
  g_CurrentPlayerIndex = stack->owner_player_index;
  updated = 0;
  for ( row = originRow - radius; row < originRow + radius; ++row )
  {
    for ( column = originColumn - radius; column < originColumn + radius; ++column )
    {
      int distance = (column - originColumn) * (column - originColumn)
                   + (row - originRow) * (row - originRow);
      if ( Math_CeilSqrt(distance) <= radius && Map_RevealTileWithPropagation(row, column, g_CurrentPlayerIndex) )
        updated = 1;
    }
  }
  g_CurrentPlayerIndex = previousPlayer;
  return updated;
}

//----- (0040F9F0) --------------------------------------------------------
signed int  UnitStack_HasReadyUnits(int stackPtr)
{
  UnitStackRecord *stack;
  int slotIndex;

  stack = (UnitStackRecord *)(uintptr_t)stackPtr;
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    UnitSlotRecord *slot = &stack->unit_slots[slotIndex];
    if ( slot->unit_type_id == -1 )
      return 0;
    if ( (slot->state_flags & UNIT_SLOT_FLAG_READY) != 0 )
      return 1;
  }
  return 0;
}

//----- (0040FA20) --------------------------------------------------------
__int16 * UnitStack_ClearReadyFlags(int stackPtr)
{
  UnitStackRecord *stack;
  int slotIndex;

  stack = (UnitStackRecord *)(uintptr_t)stackPtr;
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    UnitSlotRecord *slot = &stack->unit_slots[slotIndex];
    if ( slot->unit_type_id == -1 )
      break;
    slot->state_flags &= (uint8_t)~UNIT_SLOT_FLAG_READY;
  }
  return (__int16 *)(uintptr_t)stackPtr;
}

//----- (0040FA50) --------------------------------------------------------
__int16 * UnitStack_SetReadyFlags(int stackPtr)
{
  UnitStackRecord *stack;
  int slotIndex;

  stack = (UnitStackRecord *)(uintptr_t)stackPtr;
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    UnitSlotRecord *slot = &stack->unit_slots[slotIndex];
    if ( slot->unit_type_id == -1 )
      break;
    slot->state_flags |= UNIT_SLOT_FLAG_READY;
  }
  return (__int16 *)(uintptr_t)stackPtr;
}

//----- (0040FA80) --------------------------------------------------------
signed int  Facing_DirectionFromDelta8(int deltaRow, int deltaColumn)
{
  if ( deltaRow <= 0 )
  {
    if ( deltaRow < 0 )
    {
      if ( deltaColumn < 0 )
      {
        return DIRECTION8_NORTHWEST;
      }
      else if ( deltaColumn )
      {
        return DIRECTION8_NORTHEAST;
      }
      else
      {
        return DIRECTION8_NORTH;
      }
    }
    else if ( deltaColumn < 0 )
    {
      return DIRECTION8_WEST;
    }
    else
    {
      return DIRECTION8_EAST;
    }
  }
  else if ( deltaColumn < 0 )
  {
    return DIRECTION8_SOUTHWEST;
  }
  else if ( deltaColumn )
  {
    return DIRECTION8_SOUTHEAST;
  }
  else
  {
    return DIRECTION8_SOUTH;
  }
}

//----- (0040FAD0) --------------------------------------------------------
int  Camera_CenterOnUnit(int stackIndex)
{
  UnitStackRecord *stack;
  int mapWidthTiles;
  int mapHeightTiles;

  stack = UNIT_STACK_RECORD(stackIndex);
  *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = stack->tile_row - 4;
  *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = stack->tile_column - 3;
  if ( *(int *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) < 0 )
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = 0;
  if ( *(int *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) < 0 )
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = 0;
  mapWidthTiles = *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET);
  if ( *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 > mapWidthTiles )
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = mapWidthTiles - 9;
  mapHeightTiles = *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) + 7 > mapHeightTiles )
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = mapHeightTiles - 7;
  return WorldMap_RedrawViewport(1);
}

//----- (0040FDB0) --------------------------------------------------------
int  UnitSlot_CalcActionPointsFromFatigue(__int16 *slotPtr)
{
  UnitSlotRecord *slot;
  int unitType;
  int fatigueLevel;
  int result;

  slot = (UnitSlotRecord *)slotPtr;
  unitType = slot->unit_type_id;
  if ( unitType < 0 || unitType >= UNIT_TYPE_COUNT )
    return 0;
  fatigueLevel = slot->fatigue;
  result = (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unitType];
  if ( fatigueLevel >= 80 && fatigueLevel <= 89 )
    return (192 * result - (__CFSHL__((192 * result) >> 31, 8) + ((192 * result) >> 31 << 8))) >> 8;
  if ( fatigueLevel >= 90 && fatigueLevel <= 99 )
    return ((result << 7) - (__CFSHL__(result << 7 >> 31, 8) + (result << 7 >> 31 << 8))) >> 8;
  if ( fatigueLevel == 100 )
    return 0;
  return result;
}

//----- (0040FE60) --------------------------------------------------------
int  UnitSlot_GetBaseActionPoints(__int16 *slotPtr)
{
  return (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * *slotPtr];
}

//----- (0040FE80) --------------------------------------------------------
int  UnitStack_GetMinBaseActionPoints(int stackPtr)
{
  __int16 *slot_record; // edx
  int min_base_action_points; // ebx
  int slot_base_action_points; // eax
  int slot_index; // ecx

  min_base_action_points = UnitSlot_GetBaseActionPoints((__int16 *)(uintptr_t)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET));
  slot_record = (__int16 *)(uintptr_t)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE);
  slot_index = 1;
  while ( slot_index < UNIT_STACK_SLOT_COUNT )
  {
    if ( *slot_record == -1 )
      break;
    slot_base_action_points = UnitSlot_GetBaseActionPoints(slot_record);
    if ( slot_base_action_points < min_base_action_points )
      min_base_action_points = slot_base_action_points;
    slot_record = (__int16 *)((char *)slot_record + UNIT_STACK_SLOT_STRIDE);
    ++slot_index;
  }
  return min_base_action_points;
}

//----- (0040FEC0) --------------------------------------------------------
__int16 * UnitStack_ClearRemainingActionPoints(__int16 *result, DWORD a2, double a3)
{
  __int16 *stackPtr; // ebx
  __int16 *slotPtr; // eax
  int i; // edx
  int slotType; // ecx

  stackPtr = result;
  if ( result )
  {
    slotPtr = result + 3;
    for ( i = 0; i < 10; ++i )
    {
      slotType = *slotPtr;
      if ( slotType == -1 )
        break;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
      *((_BYTE *)slotPtr - 23) = 0;
    }
    return (__int16 *)(uintptr_t)Rules_LinkArmyFact(stackPtr, i, slotType, a3, (char)(intptr_t)stackPtr, a2);
  }
  return result;
}

//----- (0040FEF0) --------------------------------------------------------
signed int WorldMap_HandleViewportScrollKeys(void)
{
  int viewportXLeft; // edx
  int viewportXRight; // ecx
  int viewportYUp; // ebx
  int viewportYDown; // esi
  int v5; // ecx

  if ( Input_IsKeyPressed(203) )
  {
    viewportXLeft = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
    if ( viewportXLeft > 0 )
    {
      *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = viewportXLeft - 1;
LABEL_4:
      WorldMap_RedrawViewport(1);
      g_WorldMapViewportScrolledFlag = 1;
      return 1;
    }
  }
  if ( Input_IsKeyPressed(205) && (viewportXRight = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET), *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) - 9 > viewportXRight) )
  {
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = viewportXRight + 1;
    WorldMap_RedrawViewport(1);
    g_WorldMapViewportScrolledFlag = 1;
    return 1;
  }
  else if ( Input_IsKeyPressed(200) && (viewportYUp = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET), viewportYUp > 0) )
  {
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = viewportYUp - 1;
    WorldMap_RedrawViewport(1);
    g_WorldMapViewportScrolledFlag = v5;
    return v5;
  }
  else
  {
    if ( Input_IsKeyPressed(208) )
    {
      viewportYDown = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
      if ( *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) - 7 > viewportYDown )
      {
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = viewportYDown + 1;
        goto LABEL_4;
      }
    }
    return 0;
  }
}
// 40FFEB: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202F0: using guessed type int dword_5202F0;

//----- (00410010) --------------------------------------------------------
signed int  UnitStack_GetMinCurrentActionPoints(intptr_t stackPtr)
{
  __int16 *slotPtr; // eax
  int slotIndex; // edx
  int minActionPoints; // ebx

  slotPtr = (__int16 *)(stackPtr + 37);
  slotIndex = 1;
  minActionPoints = *((unsigned __int8 *)slotPtr - 23);
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( minActionPoints > *((unsigned __int8 *)slotPtr + 8) )
      minActionPoints = *((unsigned __int8 *)slotPtr + 8);
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  while ( slotIndex < 10 );
  return minActionPoints;
}

//----- (004100B0) --------------------------------------------------------
signed int  UnitStack_GetMaxOrderTier(intptr_t stackPtr)
{
  intptr_t slot_record; // eax
  int max_order_tier; // ebx
  int i; // edx

  if ( UnitStack_HasSpecialPersonageUnits(stackPtr) )
    return 3;
  slot_record = stackPtr;
  max_order_tier = 0;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    if ( *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
      break;
    if ( (*(_BYTE *)(slot_record + 18) & 3) > max_order_tier )
      max_order_tier = *(_BYTE *)(slot_record + 18) & 3;
    slot_record += UNIT_STACK_SLOT_STRIDE;
  }
  return max_order_tier;
}

//----- (00410100) --------------------------------------------------------
signed int  UnitStack_HasPlagueFlag(int stackPtr)
{
  int slotIndex; // edx

  slotIndex = 0;
  while ( 1 )
  {
    if ( *(__int16 *)(uintptr_t)(stackPtr + 6) == -1 )
      return 0;
    if ( (*(_BYTE *)(uintptr_t)(stackPtr + 19) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00410130) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsClamped(__int16 *stackPtr, int spendAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // ecx
  int slotType; // ebx
  char currentActionPoints; // bl

  slotPtr = stackPtr + 3;
  for ( i = 0; i < 10; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( *((unsigned __int8 *)slotPtr + 8) < spendAmount )
      spendAmount = *((unsigned __int8 *)slotPtr + 8);
    currentActionPoints = *((_BYTE *)slotPtr + 8);
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    LOBYTE(slotType) = currentActionPoints - spendAmount;
    *((_BYTE *)slotPtr - 23) = slotType;
  }
  return Rules_LinkArmyFact(stackPtr, spendAmount, i, a4, slotType, a3);
}

//----- (00410170) --------------------------------------------------------
int  UnitStack_SpendActionPointsUnchecked(int stackPtr, char spendAmount)
{
  int slotPtr; // eax
  int slotIndex; // edx

  slotPtr = stackPtr + 6;
  slotIndex = 0;
  while ( slotIndex < 10 )
  {
    if ( *(__int16 *)(uintptr_t)slotPtr == -1 )
      break;
    UNIT_SLOT_ACTION_POINTS(slotPtr) -= spendAmount;
    slotPtr += 31;
    ++slotIndex;
  }
  return slotPtr;
}

//----- (004101A0) --------------------------------------------------------
signed int  UnitStack_SubtractActionPointsFloorZero(__int16 *stackPtr, int subtractAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // edx
  int currentActionPoints; // ebx

  slotPtr = stackPtr + 3;
  for ( i = 0; i < 10; ++i )
  {
    currentActionPoints = *slotPtr;
    if ( currentActionPoints == -1 )
      break;
    currentActionPoints = *((unsigned __int8 *)slotPtr + 8);
    if ( currentActionPoints <= subtractAmount )
    {
      *((_BYTE *)slotPtr + 8) = 0;
    }
    else
    {
      LOBYTE(currentActionPoints) = currentActionPoints - subtractAmount;
      *((_BYTE *)slotPtr + 8) = currentActionPoints;
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  return Rules_LinkArmyFact(stackPtr, i, subtractAmount, a4, currentActionPoints, a3);
}

//----- (004101E0) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsByIndexClamped(int stackIndex, int spendAmount, DWORD a3, double a4)
{
  return UnitStack_SpendActionPointsClamped((__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET), spendAmount, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00410260) --------------------------------------------------------
signed int  UnitStack_CanReachQueuedPathTileWithFogOverlay(__int16 *stackPtr, int animate)
{
  signed int minActionPoints; // esi
  int pathLength; // [esp+0h] [ebp-1A8h]
  int pathSteps[100]; // [esp+4h] [ebp-1A4h]
  int pathStep; // [esp+194h] [ebp-14h]
  int v10; // [esp+1A0h] [ebp-8h]

  v10 = animate;
  (void)v10;
  if ( Map_ClassifyFogOfWarOverlayForPlayer(*stackPtr, stackPtr[1], VIEWED_PLAYER_INDEX) )
    return 1;
  minActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
  pathLength = *(_DWORD *)((char *)stackPtr + UNIT_STACK_PATH_OFFSET);
  qmemcpy(pathSteps, (char *)stackPtr + UNIT_STACK_PATH_OFFSET + 4, sizeof(pathSteps));
  do
  {
    if ( pathLength )
    {
      pathStep = pathSteps[--pathLength];
      if ( minActionPoints >= HIWORD(pathStep) )
        continue;
    }
    return 0;
  }
  while ( !Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)pathStep, BYTE1(pathStep), VIEWED_PLAYER_INDEX) );
  return 1;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00410330) --------------------------------------------------------
void  UnitStack_ExecuteQueuedPath(unsigned int stackIndexArg, int animateArg, char a3, DWORD a4, double a5)
{
  int v5 CLASH95_UNUSED; // ecx
  int v6 CLASH95_UNUSED; // ecx
  __int16 *stackPtr; // esi
  int pathLength; // ebx
  signed int v9; // ebp
  signed int viewportLeft; // edi
  int v11; // eax
  int v12 CLASH95_UNUSED; // ecx
  int v13; // ebx
  int stackRecordBase; // eax
  DWORD v15; // ebp
  int v16; // edx
  int v17 CLASH95_UNUSED; // ecx
  _DWORD *v18; // ecx
  int remainingPathLen; // edi
  char unitOwner; // bl
  int v21 CLASH95_UNUSED; // ecx
  _DWORD *spriteSet; // eax
  signed int currentActionPoints; // eax
  int stepCost; // edx
  unsigned int tileOccupantIndex; // eax
  int occupantUnitRecord; // eax
  int remainingSteps; // edi
  int *v28; // ebp
  int viewLeft; // ebx
  int viewTop; // edi
  signed int destColByteOffset; // ebp
  unsigned int destOccupantIndex; // eax
  int destUnitRecord; // eax
  DWORD destCol; // ebp
  int destRow; // edi
  int moveCost; // ecx
  int v37 CLASH95_UNUSED; // ecx
  int v38; // eax
  DWORD v39; // ebp
  __int16 *stackTilePtr; // edi
  int colDelta; // edx
  int destRowMapBase; // edx
  int v43; // ecx
  int v44; // edx
  unsigned int v45; // ecx
  char *v46; // ebp
  void *v47; // ebp
  signed int v48; // edi
  signed int v49; // ecx
  signed int v50; // ecx
  signed int v51; // ecx
  signed int v52; // edx
  signed int v53; // edi
  int v54; // edx
  int v55; // ecx
  int v56; // ecx
  unsigned int v57; // eax
  unsigned int v58; // ecx
  int bridgeQueueCount; // edi
  int *v60; // ecx
  int v61; // ebp
  int v62; // ecx
  int curRow; // edx
  int targetOffsetX; // edi
  int targetOffsetY; // ebp
  int now; // ebx
  int v67; // eax
  int v68; // edx
  int v69; // eax
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int moveAnimInterval; // edx
  int v74; // ecx
  int v75; // eax
  char walkStep; // al
  int v78; // ecx
  int v79; // ebx
  int v80; // edx
  int v81; // edx
  int v82; // ebx
  int remainingPathSteps; // ebp
  int v84; // eax
  __int16 i; // si
  int v86; // edx
  char spriteFilePath[100]; // [esp+0h] [ebp-CCh] BYREF
  int oldRow; // [esp+64h] [ebp-68h]
  int v89; // [esp+68h] [ebp-64h]
  int v90; // [esp+6Ch] [ebp-60h]
  int stackByteOffset; // [esp+70h] [ebp-5Ch]
  int savedCursorDescriptor; // [esp+74h] [ebp-58h]
  signed int originColumn; // [esp+78h] [ebp-54h]
  signed int originRow; // [esp+7Ch] [ebp-50h]
  int *v95; // [esp+80h] [ebp-4Ch]
  int v96; // [esp+84h] [ebp-48h]
  signed int visionChanged; // [esp+88h] [ebp-44h]
  int v98; // [esp+8Ch] [ebp-40h]
  int buildingRecordOffset; // [esp+90h] [ebp-3Ch]
  int prevCumulativeCost; // [esp+94h] [ebp-38h]
  int animate; // [esp+98h] [ebp-34h]
  char *v102; // [esp+9Ch] [ebp-30h]
  char *v103; // [esp+A0h] [ebp-2Ch]
  int *pathBuffer; // [esp+A4h] [ebp-28h]
  int pathStep; // [esp+A8h] [ebp-24h]
  int isFirstAnimStep; // [esp+ACh] [ebp-20h]
  unsigned int stackIndex; // [esp+B0h] [ebp-1Ch]
  int moveDirection; // [esp+B4h] [ebp-18h]
  BOOL followInViewport; // [esp+B8h] [ebp-14h]

  stackIndex = stackIndexArg;
  animate = animateArg;
  Debug_Log(stackIndexArg, a3, a4, (int)(intptr_t)aUnit_moveDD);
  Render_DrawSprite_v3(stackIndex, a4);
  stackPtr = (__int16 *)(uintptr_t)UNIT_STACK(stackIndex);
  pathLength = *((_DWORD *)stackPtr + 79);
  pathBuffer = (int *)(stackPtr + 158);
  if ( pathLength )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      pathStep = pathBuffer[pathLength];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_next",
        stackIndex,
        (unsigned __int8)pathStep,
        BYTE1(pathStep),
        HIWORD(pathStep));
      pathStep = pathBuffer[1];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_first",
        stackIndex,
        (unsigned __int8)pathStep,
        BYTE1(pathStep),
        HIWORD(pathStep));
    }
    v9 = (signed int)(intptr_t)pathBuffer;
    v96 = 0;
    v89 = pathBuffer[1];
    originRow = *stackPtr;
    viewportLeft = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
    originColumn = stackPtr[1];
    followInViewport = 1;
    if ( originRow >= viewportLeft )
    {
      v9 = originRow;
      if ( viewportLeft + 9 > originRow )
      {
        v9 = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
        if ( originColumn >= v9
          && v9 + 7 > originColumn
          && (unsigned __int8)v89 >= *(int *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)
          && (unsigned __int8)v89 < viewportLeft + 9
          && BYTE1(v89) >= *(int *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) )
        {
          followInViewport = BYTE1(v89) >= v9 + 7;
        }
      }
    }
    if ( animate )
    {
      if ( !UnitStack_CanReachQueuedPathTileWithFogOverlay(stackPtr, animate) )
        animate = 0;
    }
    else
    {
      followInViewport = 0;
    }
    g_ActiveUnitAnimSpriteSet = 0;
    if ( animate && !*(_DWORD *)(uintptr_t)(gameData + 147159) )
    {
      unitOwner = *((_BYTE *)stackPtr + 4);
      Unit_BuildGoSpriteFilePath(spriteFilePath, *((_BYTE *)stackPtr + 6), unitOwner);
      spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
      if ( spriteSet )
        spriteSet = DLXSpriteSet_Load(spriteSet, spriteFilePath);
      g_ActiveUnitAnimSpriteSet = (int)(intptr_t)spriteSet;
      g_UnitAnimFrameIndex = 0;
      g_ActiveUnitMoveTileIndex = stackIndex;
    }
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    if ( animate )
      WorldMap_RedrawViewport(1);
    savedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
    v11 = stackIndex;
    *((_BYTE *)stackPtr + 720) = 0;
    UnitStack_RevealHiddenEnemiesAndAttackAdjacent(v11, a5);
    Trap_TriggerAtStackTile(stackIndex, a4, a5);
    isFirstAnimStep = 1;
    v13 = *pathBuffer;
    prevCumulativeCost = 0;
    if ( v13 )
    {
      stackByteOffset = UNIT_STACK_STRIDE * stackIndex;
      v95 = (int *)(stackPtr + 158);
      while ( 1 )
      {
        if ( v96 )
          goto LABEL_21;
        pathStep = pathBuffer[*pathBuffer];
        currentActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
        stepCost = HIWORD(pathStep) - prevCumulativeCost;
        if ( currentActionPoints - stepCost < 0 )
        {
          Diagnostics_TraceWorldMapActionEvent("unit_move_stop_ap", stackIndex, currentActionPoints, stepCost, *pathBuffer);
          goto LABEL_21;
        }
        tileOccupantIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX((unsigned __int8)pathStep, BYTE1(pathStep))) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
        if ( tileOccupantIndex > 0x64
          || (occupantUnitRecord = UNIT_RECORD(tileOccupantIndex), (unsigned int)*(char *)(uintptr_t)(occupantUnitRecord + 4) >= 4)
          || *(__int16 *)(uintptr_t)(occupantUnitRecord + 16) == -1 )
        {
          UnitStack_SpendActionPointsUnchecked((int)(intptr_t)stackPtr, BYTE2(pathStep) - prevCumulativeCost);
          UnitStack_SetSpentTurnFlag((int)(intptr_t)stackPtr);
        }
        remainingSteps = *pathBuffer - 1;
        v28 = pathBuffer;
        *pathBuffer = remainingSteps;
        pathStep = v28[remainingSteps + 1];
        prevCumulativeCost = HIWORD(pathStep);
        if ( followInViewport )
        {
          viewLeft = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
          if ( (unsigned __int8)pathStep < viewLeft
            || (unsigned __int8)pathStep >= viewLeft + 9
            || (viewTop = *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET), BYTE1(pathStep) < viewTop)
            || BYTE1(pathStep) >= viewTop + 7 )
          {
            if ( Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)pathStep, BYTE1(pathStep), VIEWED_PLAYER_INDEX) )
              Camera_CenterOnUnit(stackIndex);
          }
        }
        v13 = 200 * (unsigned __int8)pathStep;
        destColByteOffset = 2 * BYTE1(pathStep);
        destOccupantIndex = *(unsigned __int16 *)(uintptr_t)(gameData + v13 + destColByteOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
        if ( destOccupantIndex <= 0x64 )
        {
          buildingRecordOffset = BUILDING_RECORD_SIZE * destOccupantIndex;
          destUnitRecord = UNIT_RECORD(destOccupantIndex);
          if ( (unsigned int)*(char *)(uintptr_t)(destUnitRecord + 4) < 4 && *(__int16 *)(uintptr_t)(destUnitRecord + 16) != -1 )
            break;
        }
        destCol = BYTE1(pathStep);
        destRow = (unsigned __int8)pathStep;
        if ( MapTile_GetReligiousSiteCategory((unsigned __int8)pathStep, BYTE1(pathStep)) )
        {
          Audio_StopUnitMoveSound();
          LOBYTE(v13) = destCol;
          Temple_UnitGetInto(stackIndex, destRow, destCol, destCol, a5);
          *v95 = 0;
          goto LABEL_21;
        }
        LOBYTE(v13) = destCol;
        moveCost = UnitStack_GetTileMoveCostOrZero(stackPtr, destRow, 0, destCol);
        if ( !moveCost )
        {
          if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackPtr + 4) + gameData + 140051) || !Map_GetBridgeCrossingCostOrZero(destRow, destCol) )
          {
            *((_DWORD *)stackPtr + 79) = 0;
          }
          else
          {
            bridgeQueueCount = *v95;
            if ( *v95 < 100 )
            {
              v60 = v95;
              *v95 = bridgeQueueCount + 1;
              v60[bridgeQueueCount + 1] = pathStep;
              UnitStack_ClearReadyFlags((int)(intptr_t)stackPtr);
              goto LABEL_21;
            }
          }
          UnitStack_ClearReadyFlags((int)(intptr_t)stackPtr);
          goto LABEL_21;
        }
        *((_BYTE *)stackPtr + 5) = Facing_DirectionFromDelta8(destRow - *stackPtr, destCol - stackPtr[1]);
        v38 = *((unsigned __int8 *)stackPtr + 5);
        moveDirection = v38;
        if ( v38 == 6 || v38 == 2 )
          g_UnitMoveAnimOffsetY = 0;
        if ( !moveDirection || moveDirection == 4 )
          g_UnitMoveAnimOffsetX = 0;
        if ( !*(_DWORD *)(uintptr_t)(gameData + 147159) )
        {
          if ( animate )
          {
            v61 = BYTE1(pathStep);
            if ( Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)pathStep, BYTE1(pathStep), VIEWED_PLAYER_INDEX) )
            {
              v62 = (unsigned __int8)pathStep;
              curRow = *(__int16 *)(uintptr_t)(stackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET);
              targetOffsetX = (v62 - curRow) << 6;
              targetOffsetY = (v61 - *(__int16 *)(uintptr_t)(stackByteOffset + gameData + 147176)) << 6;
              now = Time_Now(v62, curRow);
              while ( 1 )
              {
                v67 = g_UnitMoveAnimOffsetX;
                if ( g_UnitMoveAnimOffsetX <= 0 )
                  v67 = -g_UnitMoveAnimOffsetX;
                v68 = v67;
                v69 = targetOffsetX <= 0 ? -targetOffsetX : targetOffsetX;
                if ( v68 >= v69 )
                {
                  v70 = g_UnitMoveAnimOffsetY;
                  if ( g_UnitMoveAnimOffsetY <= 0 )
                    v70 = -g_UnitMoveAnimOffsetY;
                  v71 = v70;
                  v72 = targetOffsetY <= 0 ? -targetOffsetY : targetOffsetY;
                  if ( v71 >= v72 )
                    break;
                }
                DD_Pump((int)(intptr_t)g_RenderState, now);
                if ( WorldMap_HandleViewportScrollKeys() )
                {
                  followInViewport = 0;
                }
                else
                {
                  WorldMap_RedrawFrame(now);
                  moveAnimInterval = 88 * stackPtr[3];
                  LOBYTE(moveAnimInterval) = g_UnitTypeMoveAnimationTickIntervalMs[moveAnimInterval];
                  v75 = Time_Now(v74, moveAnimInterval);
                  if ( v75 - now >= (unsigned int)(unsigned __int8)moveAnimInterval )
                  {
                    walkStep = g_WorldMapUnitWalkStepCounter++;
                    if ( (walkStep & 1) != 0 )
                    {
                      g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
                      Audio_PlayWorldMapUnitMoveSound(*stackPtr, stackPtr[1], g_UnitAnimFrameIndex, stackPtr[3]);
                    }
                    if ( isFirstAnimStep )
                    {
                      v78 = -1;
                      do
                      {
                        v79 = -1;
                        do
                        {
                          v80 = v79 + stackPtr[1];
                          ++v79;
                          WorldMap_RedrawTileIfVisible(v78 + *stackPtr, v80);
                        }
                        while ( v79 <= 1 );
                        ++v78;
                      }
                      while ( v78 <= 1 );
                    }
                    else if ( Unit_GetSpriteVerticalOffsetPx(stackIndex) )
                    {
                      Map_RedrawUnitNeighborhoodByIndex(stackIndex);
                    }
                    else
                    {
                      v82 = moveDirection;
                      WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1]);
                      if ( v82 == 4 || v82 == 5 || v82 == 3 || v82 == 6 || v82 == 2 )
                        WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1] + 1);
                      if ( !moveDirection || moveDirection == 7 || moveDirection == 1 )
                        WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1] - 1);
                      if ( moveDirection == 2 || moveDirection == 3 || moveDirection == 1 || moveDirection == 4 )
                        WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1]);
                      if ( moveDirection == 6 || moveDirection == 5 || moveDirection == 7 )
                        WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1]);
                      v78 = moveDirection;
                      switch ( moveDirection )
                      {
                        case 3:
                          WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1] + 1);
                          break;
                        case 1:
                          WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1] - 1);
                          break;
                        case 5:
                          WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1] + 1);
                          break;
                        case 7:
                          WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1] - 1);
                          break;
                      }
                    }
                    g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * stackPtr[3]]
                                  * Map_NeighborDX[2 * *((unsigned __int8 *)stackPtr + 5)];
                    v81 = *((unsigned __int8 *)stackPtr + 5);
                    g_UnitMoveAnimOffsetY += Map_NeighborDY[2 * v81] * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * stackPtr[3]];
                    now = Time_Now(v78, v81);
                    isFirstAnimStep = 0;
                  }
                }
              }
            }
          }
        }
        g_UnitMoveAnimOffsetX %= 64;
        v90 = (unsigned __int8)pathStep;
        v103 = (char *)(uintptr_t)(unsigned __int8)pathStep;
        v98 = animate;
        v39 = BYTE1(pathStep);
        stackTilePtr = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + stackByteOffset);
        g_UnitMoveAnimOffsetY %= 64;
        colDelta = BYTE1(pathStep) - stackTilePtr[1];
        oldRow = *stackTilePtr;
        *((_BYTE *)stackTilePtr + 5) = Facing_DirectionFromDelta8((unsigned __int8)pathStep - oldRow, colDelta);
        destRowMapBase = 200 * v90;
        *(_WORD *)(uintptr_t)(2 * stackTilePtr[1] + gameData + TILE_ROW_STRIDE * *stackTilePtr + TILE_MAP_OFFSET) = -1;
        v43 = stackIndex;
        v13 = v39;
        *(_WORD *)(uintptr_t)(destRowMapBase + gameData + 2 * v39 + TILE_MAP_OFFSET) = stackIndex;
        *stackTilePtr = (__int16)(intptr_t)v103;
        stackTilePtr[1] = v39;
        if ( Trap_TriggerAtStackTile(v43, a4, a5) )
          UnitStack_ClearRemainingActionPoints(stackTilePtr, v39, a5);
        v45 = stackIndex;
        if ( v45 <= 0x1F4 )
        {
          v44 = UNIT_STACK_STRIDE * v45;
          if ( (unsigned int)*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * v45 + gameData + 147180) <= 0x28 )
          {
            UnitStack_RevealHiddenEnemiesAndAttackAdjacent(v45, a5);
            if ( v45 <= 0x1F4 && (unsigned int)*(__int16 *)(uintptr_t)(v44 + gameData + 147180) <= 0x28 )
            {
              v46 = v103;
              visionChanged = UnitStack_UpdateVision(v45);
              v47 = v46 + 1;
              MiniMap_DrawTileCell(v103, v13);
              MiniMap_DrawTileCell(v47, v13);
              v48 = v13 - 1;
              v102 = v103 - 1;
              MiniMap_DrawTileCell(v103 - 1, v13);
              MiniMap_DrawTileCell(v103, v13 - 1);
              MiniMap_DrawTileCell(v47, v13 - 1);
              MiniMap_DrawTileCell(v102, v13 - 1);
              MiniMap_DrawTileCell(v103, v49);
              MiniMap_DrawTileCell(v47, v50);
              v13 = v98;
              MiniMap_DrawTileCell(v102, v51);
              if ( v13 )
              {
                LOBYTE(v13) = (_BYTE)(intptr_t)v47;
                v52 = v48;
                g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
                v53 = visionChanged;
                MiniMap_RedrawTileRect((int)(intptr_t)v102, v52, v45, (int)(intptr_t)v47);
                if ( v53 )
                  WorldMap_RedrawViewport(1);
              }
            }
          }
        }
        if ( animate && *(_DWORD *)(uintptr_t)(gameData + 147159) )
        {
          Time_Now(v45, v44);
          v13 = (int)(intptr_t)g_RenderState;
          WorldMap_RedrawViewport(1);
          v56 = v55 + 10;
          while ( 1 )
          {
            v57 = Time_Now(v56, v54);
            if ( v57 >= v58 )
              break;
            DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)g_RenderState);
            WorldMap_RedrawFrame((int)(intptr_t)g_RenderState);
          }
        }
        if ( stackIndex <= 0x1F4 && (unsigned int)*(__int16 *)(uintptr_t)(stackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28 )
        {
          remainingPathSteps = *pathBuffer;
          isFirstAnimStep = 1;
          if ( remainingPathSteps )
            continue;
        }
        goto LABEL_21;
      }
      if ( *(_BYTE *)(uintptr_t)(buildingRecordOffset + gameData + 509676) != *((_BYTE *)stackPtr + 4) || *pathBuffer )
      {
        *((_DWORD *)stackPtr + 79) = 0;
        UnitStack_ClearReadyFlags((int)(intptr_t)stackPtr);
      }
      else
      {
        Audio_StopUnitMoveSound();
        if ( Building_CanAcceptUnitStack(stackIndex, *(unsigned __int16 *)(uintptr_t)(v13 + gameData + destColByteOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) )
          Building_UnitGetInto(stackIndex, *(unsigned __int16 *)(uintptr_t)(v13 + gameData + destColByteOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v13, destColByteOffset, a5);
        else
          *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147490) = 0;
      }
    }
LABEL_21:
    stackRecordBase = gameData + UNIT_STACK_STRIDE * stackIndex;
    v15 = originRow;
    v16 = *(__int16 *)(uintptr_t)(stackRecordBase + 147174);
    if ( v16 != originRow || (v16 = originColumn, *(__int16 *)(uintptr_t)(stackRecordBase + 147176) != originColumn) )
      Rules_LinkArmyFact(stackPtr, v16, gameData, a5, v13, originRow);
    Audio_StopUnitMoveSound();
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    v18 = (_DWORD*)(stackPtr + 158);
    remainingPathLen = *((_DWORD *)stackPtr + 79);
    if ( remainingPathLen )
    {
      v84 = remainingPathLen - 1;
      for ( i = prevCumulativeCost; v84 >= 0; v18[v86 + 1] = v89 )
      {
        v86 = *v18 - 1 - v84;
        v89 = v18[v86 + 1];
        HIWORD(v89) -= i;
        --v84;
      }
    }
    else
    {
      UnitStack_ClearReadyFlags((int)(intptr_t)stackPtr);
    }
    if ( g_ActiveUnitAnimSpriteSet )
      DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
    g_ActiveUnitMoveTileIndex = -1;
    if ( animate )
    {
      UnitStackSelection_RefreshForSelectedStack(v15);
      WorldMap_RedrawViewport(1);
    }
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, savedCursorDescriptor);
    WorldMap_SyncSelectionForHumanPlayer(v15);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_state",
      stackIndex,
      *stackPtr,
      stackPtr[1],
      *((_DWORD *)stackPtr + 79));
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_ap",
      stackIndex,
      UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr),
      0,
      0);
  }
}
// 4106F5: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 410718: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 4107F4: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 410825: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 410B09: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 410B30: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 410B48: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 410B69: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 411076: simplified comparisons for '%var_1C.4': <0 || >=1F5 became >=1F5u
// 41109E: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41035B: variable 'v5' is possibly undefined
// 410385: variable 'v6' is possibly undefined
// 4104F4: variable 'v12' is possibly undefined
// 410595: variable 'v17' is possibly undefined
// 410646: variable 'v21' is possibly undefined
// 4106B6: variable 'v24' is possibly undefined
// 410999: variable 'v37' is possibly undefined
// 4109B6: variable 'v36' is possibly undefined
// 410B09: variable 'v45' is possibly undefined
// 410B5F: variable 'v44' is possibly undefined
// 410BEF: variable 'v49' is possibly undefined
// 410BF8: variable 'v50' is possibly undefined
// 410C0D: variable 'v51' is possibly undefined
// 410C7D: variable 'v55' is possibly undefined
// 410C80: variable 'v56' is possibly undefined
// 410C80: variable 'v54' is possibly undefined
// 410C87: variable 'v58' is possibly undefined
// 410D7A: variable 'v62' is possibly undefined
// 410E07: variable 'v74' is possibly undefined
// 410E77: variable 'v78' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 519808: using guessed type int dword_519808;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523F68: using guessed type int dword_523F68;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D14: using guessed type int dword_544D14;

//----- (00411120) --------------------------------------------------------
int  UnitStats_CalcEffectiveMeleeAttack(char *slotPtr, int forceMaxLevel)
{
  int level; // ebx

  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + (unsigned __int8)g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * UNIT_SLOT_TYPE(slotPtr)] + slotPtr[11] / 5) * slotPtr[9] / 100;
}

//----- (00411180) --------------------------------------------------------
int  UnitStats_GetMeleeIconIndex(__int16 *slotPtr)
{
  const UnitSlotRecord *slot = (const UnitSlotRecord *)slotPtr;
  return (slot->stance_bits & 0x03) + g_UnitTypeRuntimeCoreMetadata[slot->unit_type_id].base_melee_attack + (signed char)slot->morale / 5;
}

//----- (004111C0) --------------------------------------------------------
int  UnitStats_CalcEffectiveDefensePower(char *slotPtr, int forceMaxLevel)
{
  int baseDefense; // ebx
  int level; // esi

  baseDefense = (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * UNIT_SLOT_TYPE(slotPtr)];
  if ( (slotPtr[22] & 1) != 0 )
    baseDefense = (320 * baseDefense - (__CFSHL__((320 * baseDefense) >> 31, 8) + ((320 * baseDefense) >> 31 << 8))) >> 8;
  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + baseDefense + slotPtr[11] / 5) * slotPtr[9] / 100;
}

//----- (00411240) --------------------------------------------------------
int  UnitStats_GetDefenseIconIndex(__int16 *slotPtr)
{
  const UnitSlotRecord *slot = (const UnitSlotRecord *)slotPtr;
  return (slot->stance_bits & 0x03) + g_UnitTypeRuntimeCoreMetadata[slot->unit_type_id].base_defense_power + (signed char)slot->morale / 5;
}

//----- (00411280) --------------------------------------------------------
int  UnitStats_CalcEffectiveShotPower(__int16 *slotPtr)
{
  return ((unsigned __int8)g_UnitTypeBaseShotPower[UNIT_TYPE_METADATA_STRIDE * *slotPtr] + *((char *)slotPtr + 11) / 10) * *((char *)slotPtr + 9) / 100;
}

//----- (004112C0) --------------------------------------------------------
int  UnitStats_GetBaseShotPower(__int16 *slotPtr)
{
  return (unsigned __int8)g_UnitTypeBaseShotPower[UNIT_TYPE_METADATA_STRIDE * *slotPtr] + *((char *)slotPtr + 11) / 10;
}

//----- (004112F0) --------------------------------------------------------
int  UnitStats_CalcEffectiveWallAttack(char *slotPtr, int forceMaxLevel)
{
  int level; // ebx

  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + (unsigned __int8)g_UnitTypeBaseWallAttack[UNIT_TYPE_METADATA_STRIDE * UNIT_SLOT_TYPE(slotPtr)] + slotPtr[11] / 5) * slotPtr[9] / 100;
}

//----- (00411350) --------------------------------------------------------
signed int  Debug_LogUnitSquadDetails(int stackPtr, DWORD a2)
{
  signed int result; // eax
  signed int squadIndex; // ecx

  Debug_Log(0, stackPtr, a2, (int)(intptr_t)aUnitD0x08x);
  squadIndex = 0;
  for ( result = Unit_GetSquadCount(stackPtr); squadIndex < result; result = Unit_GetSquadCount(stackPtr) )
  {
    Debug_Log(squadIndex + 1, stackPtr, a2, (int)(intptr_t)a15sPl1dP);
    ++squadIndex;
  }
  return result;
}

signed int Unit_DebugDumpFormationSizes(int stackRecord, DWORD a2)
{
  return Debug_LogUnitSquadDetails(stackRecord, a2);
}
// 4113B7: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00411420) --------------------------------------------------------
signed int  Unit_DebugDumpFormationSizesForStackIndex(int stackIndex, DWORD a2)
{
  return Unit_DebugDumpFormationSizes(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET, a2);
}

signed int Render_DrawSprite_v3(int stackIndex, DWORD a2)
{
  return Unit_DebugDumpFormationSizesForStackIndex(stackIndex, a2);
}
// 5202E4: using guessed type int gameData;

//----- (00411460) --------------------------------------------------------
signed int  LogAllUnits(int a1, char a2, DWORD a3)
{
  int stackIndex; // ecx
  int stackPtr; // edx
  signed int result; // eax

  Debug_Log(a1, a2, a3, (int)(intptr_t)aLogallunits);
  stackIndex = 0;
  stackPtr = gameData + UNIT_STACK_TABLE_OFFSET;
  do
  {
    result = *(__int16 *)(uintptr_t)(stackPtr + 6);
    if ( result != -1 )
      result = Unit_DebugDumpFormationSizes(stackPtr, a3);
    ++stackIndex;
    stackPtr += UNIT_STACK_STRIDE;
  }
  while ( stackIndex < UNIT_STACK_TABLE_COUNT );
  return result;
}
// 411489: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004114B0) --------------------------------------------------------
signed int  Unit_CompactSquad(__int16 *stackPtr, int a2, double a3)
{
  int changed;
  int read_index;
  int write_index;

  (void)a2;

  changed = 0;
  write_index = 0;
  for ( read_index = 0; read_index < UNIT_STACK_SLOT_COUNT; ++read_index )
  {
    int source_slot = UNIT_STACK_SLOT((int)(intptr_t)stackPtr, read_index);
    if ( *(__int16 *)(uintptr_t)source_slot == -1 )
      continue;
    if ( write_index != read_index )
    {
      qmemcpy(
        (void *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)stackPtr, write_index),
        (const void *)(uintptr_t)source_slot,
        UNIT_STACK_SLOT_STRIDE);
      changed = 1;
    }
    ++write_index;
  }
  while ( write_index < UNIT_STACK_SLOT_COUNT )
  {
    int slot = UNIT_STACK_SLOT((int)(intptr_t)stackPtr, write_index);
    if ( *(__int16 *)(uintptr_t)slot != -1 )
      changed = 1;
    *(__int16 *)(uintptr_t)slot = -1;
    ++write_index;
  }
  if ( changed )
    Rules_LinkArmyFact(stackPtr, 0, 0, a3, 0, (DWORD)(intptr_t)stackPtr);
  return Rules_SyncArmyFactStrength(stackPtr, 0, 0, 0, (DWORD)(intptr_t)stackPtr, a3);
}

//----- (00411560) --------------------------------------------------------
_WORD * UnitSlots_RemoveGaps(_WORD *result, int slotCount)
{
  int lastIndex; // ebx
  int keptCount; // ebp
  int shiftIndex; // edx
  void *shiftDst; // edi
  int i; // [esp+0h] [ebp-20h]
  _WORD *slotArrayBase; // [esp+4h] [ebp-1Ch]
  __int16 *slotCursor; // [esp+8h] [ebp-18h]

  slotArrayBase = result;
  lastIndex = slotCount - 1;
  keptCount = 0;
  slotCursor = (short int*)(result);
  for ( i = 0; lastIndex > i; ++i )
  {
    if ( *slotCursor == -1 )
    {
      shiftIndex = keptCount;
      result = (_WORD *)((char *)slotArrayBase + 31 * keptCount);
      while ( shiftIndex < lastIndex )
      {
        shiftDst = result;
        ++shiftIndex;
        result = (_WORD *)((char *)result + 31);
        qmemcpy(shiftDst, result, 0x1Fu);
      }
      *result = -1;
    }
    else
    {
      result = (_WORD*)((__int16 *)((char *)slotCursor + 31));
      ++keptCount;
      slotCursor = (__int16 *)((char *)slotCursor + 31);
    }
  }
  return result;
}
