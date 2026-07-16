/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../state/state_shared.h"
#include "../world/world_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004115E0) --------------------------------------------------------
void  Unit_CheckLowMorale(_BYTE *stackPtr, double a2)
{
  int anyDisbanded; // esi
  __int16 *slotPtr; // ecx
  int slotIndex; // ebx
  int wasLowMorale; // eax
  int disbandRollMax; // eax
  char slotFlags; // dh
  int stackRow; // ebx
  int disbandedFlag; // ebx
  _BYTE v15[725]; // [esp+0h] [ebp-300h] BYREF
  int v16[3]; // [esp+2D8h] [ebp-28h]
  int v17[7]; // [esp+2E4h] [ebp-1Ch] BYREF

  qmemcpy(v15, stackPtr, UNIT_STACK_STRIDE);
  v17[0] = 0;
  anyDisbanded = 0;
  slotPtr = (__int16 *)&v15[6];
  slotIndex = 0;
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( !*((_BYTE *)slotPtr + 11) )
    {
      wasLowMorale = (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0;
      *((_BYTE *)slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      disbandRollMax = wasLowMorale ? 200 : 100;
      if ( Rng_RandRange(0, disbandRollMax) < 0x32 )
      {
        if ( Rng_RandRange(0, 100) >= 0x32 )
        {
          anyDisbanded = 1;
          Debug_Log(0, slotIndex, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)aUnit_checklo_0);
          *slotPtr = -1;
          v17[0] = 1;
        }
        else
        {
          Debug_Log(0, slotIndex, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)aUnit_checklowm);
          slotFlags = *((_BYTE *)slotPtr + 13);
          *((_BYTE *)slotPtr + 8) = 0;
          *((_BYTE *)slotPtr + 13) = slotFlags | UNIT_SLOT_FLAG_LOW_MORALE;
        }
      }
    }
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  while ( slotIndex < 10 );
  if ( anyDisbanded && *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * (unsigned __int8)stackPtr[4] + 140051) )
  {
    stackRow = *(__int16 *)stackPtr;
    UI_CenterWorldMapViewportOnRectIfFit(stackRow, *((__int16 *)stackPtr + 1), *((__int16 *)stackPtr + 1) - 5, stackRow);
    v16[0] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[0];
    v16[1] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[1];
    v16[2] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[2];
    UI_ShowInfoWindow(v16[(unsigned __int8)g_LanguageIndex], 0, 0, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)v17, (int)(intptr_t)&g_Text_UnitDisbandedLowMoraleMessages[3]);
    UI_StartWorldMapUnitAttentionFlash(
      *(unsigned __int16 *)(uintptr_t)(gameData + TILE_ROW_STRIDE * *(__int16 *)stackPtr + 2 * *((__int16 *)stackPtr + 1) + TILE_MAP_OFFSET),
      *((__int16 *)stackPtr + 1),
      *(__int16 *)stackPtr);
    while ( UI_IsWorldMapUnitAttentionFlashActive() )
      WorldMap_RedrawFrame(stackRow);
  }
  disbandedFlag = v17[0];
  qmemcpy(stackPtr, v15, 0x2D4u);
  stackPtr[724] = v15[724];
  if ( disbandedFlag )
  {
    Unit_CompactSquad((__int16 *)stackPtr, 0, a2);
    Rules_LinkArmyFinalize((__int16 *)stackPtr, a2);
    Rules_LinkArmyFact((__int16 *)stackPtr, 0, 0, a2, 0, (DWORD)(intptr_t)stackPtr);
  }
}
// 4116CD: variable 'v8' is possibly undefined
// 4116D2: variable 'v4' is possibly undefined
// 411743: variable 'v11' is possibly undefined
// 4117F5: variable 'v13' is possibly undefined
// 4117F5: variable 'v14' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 512368: using guessed type char *off_512368[3];
// 5202E4: using guessed type int gameData;

//----- (00411810) --------------------------------------------------------
signed int  UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  __int16 *slotPtr; // ecx
  int anyRemoved; // esi
  int i; // ebx
  signed int result; // eax
  char attritionLoss; // al
  char newQuantity; // dl
  int v10; // edx
  int v11; // ecx

  slotPtr = stackPtr + 3;
  anyRemoved = 0;
  for ( i = 0; i < 10; ++i )
  {
    result = *slotPtr;
    if ( result == -1 )
      break;
    if ( result == UNIT_TYPE_PEASANT_CARGO && (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
    {
      attritionLoss = Rng_RandRange(15, 25);
      newQuantity = *((_BYTE *)slotPtr + 9) - attritionLoss;
      result = newQuantity;
      *((_BYTE *)slotPtr + 9) = newQuantity;
      if ( newQuantity <= 0 )
      {
        anyRemoved = 1;
        *slotPtr = -1;
      }
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  if ( anyRemoved )
  {
    Unit_CompactSquad(stackPtr, (int)(intptr_t)slotPtr, a3);
    Rules_LinkArmyFinalize(stackPtr, a3);
    if ( stackPtr[3] != -1 )
      Rules_LinkArmyFact(stackPtr, v10, v11, a3, i, a2);
    return Rules_SyncArmyFactStrength(stackPtr, v10, v11, i, a2, a3);
  }
  return result;
}
// 411840: variable 'v4' is possibly undefined
// 411887: variable 'v10' is possibly undefined
// 411887: variable 'v11' is possibly undefined

//----- (004118A0) --------------------------------------------------------
BOOL  UnitSlot_ShouldGainFatigueFromLowActionPoints(int slotPtr)
{
  return *(unsigned __int8 *)(uintptr_t)(slotPtr + 8) <= 3u && (*(_BYTE *)(uintptr_t)(slotPtr + 13) & UNIT_SLOT_FLAG_LOW_MORALE) == 0;
}

//----- (004118C0) --------------------------------------------------------
BOOL  UnitSlot_CanRecoverFatigue(int slotPtr)
{
  return (*(_BYTE *)(uintptr_t)(slotPtr + 13) & UNIT_SLOT_FLAG_SPENT_TURN) == 0;
}

//----- (004118D0) --------------------------------------------------------
BOOL  UnitSlot_HasSevereFatigue(int slotPtr)
{
  return *(char *)(uintptr_t)(slotPtr + 10) >= 80;
}

//----- (004118E0) --------------------------------------------------------
signed int  Unit_NewTurn(int a1, char a2, DWORD a3, double a4)
{
  int stackPtr; // esi
  int slotIndex; // ebx
  int slotCursor; // edx
  int slotType; // ecx
  char actionPoints; // al
  unsigned int buildingIndex; // edx
  int buildingRecord; // ecx
  int nextStackOffset; // ecx
  int i; // [esp+0h] [ebp-20h]
  unsigned int stackIndex; // [esp+4h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)(intptr_t)aUnit_newturn);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
  stackIndex = 0;
  for ( i = 0; ; i += 725 )
  {
    if ( *(__int16 *)(uintptr_t)(gameData + i + 147180) == -1 || *(unsigned __int8 *)(uintptr_t)(gameData + i + 147178) != g_CurrentPlayerIndex )
      goto LABEL_16;
    stackPtr = gameData + UNIT_STACK_TABLE_OFFSET + i;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_stack",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, -20, UnitSlot_CanRecoverFatigue, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_recover_fatigue",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(stackPtr + 4) + 140051) )
    {
      UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, 10, UnitSlot_ShouldGainFatigueFromLowActionPoints, 0xFFFFFFFF, a4);
      UnitStack_AdjustMoraleByPredicate((__int16 *)(uintptr_t)stackPtr, -1, UnitSlot_HasSevereFatigue, 0xFFFFFFFF, a4);
    }
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_human_fatigue",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    UnitStack_ClearSpentTurnFlag(stackPtr);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_clear_spent",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    slotIndex = 0;
    slotCursor = stackPtr;
    do
    {
      slotType = *(__int16 *)(uintptr_t)(slotCursor + 6);
      if ( slotType == -1 )
        break;
      if ( slotType < 0 || slotType >= UNIT_TYPE_COUNT )
      {
        *(_WORD *)(uintptr_t)(slotCursor + 6) = -1;
        break;
      }
      slotCursor += 31;
      actionPoints = UnitSlot_CalcActionPointsFromFatigue((__int16 *)(uintptr_t)(stackPtr + 6 + 31 * slotIndex++));
      *(_BYTE *)(uintptr_t)(slotCursor - 17) = actionPoints;
    }
    while ( slotIndex < 10 );
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ap",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    Rules_LinkArmyFact((__int16 *)(uintptr_t)stackPtr, slotCursor, slotType, a4, slotIndex, 0xFFFFFFFF);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_rules_fact",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    Unit_CheckLowMorale((_BYTE *)(uintptr_t)stackPtr, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_low_morale",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    UnitStack_ApplyPlagueAttritionToPeasantCargo((__int16 *)(uintptr_t)stackPtr, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_plague",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    if ( !UnitStack_HasReadyUnits(stackPtr) )
      goto LABEL_16;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ready_check",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    buildingIndex = *(unsigned __int16 *)(uintptr_t)(gameData
                             + TILE_ROW_STRIDE * (unsigned __int8)*(_DWORD *)(uintptr_t)(stackPtr + 320)
                             + 2 * (unsigned __int8)BYTE1(*(_DWORD *)(uintptr_t)(stackPtr + 320))
                             + TILE_MAP_OFFSET)
       - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( buildingIndex <= 0x64 )
    {
      slotIndex = BUILDING_RECORD_SIZE * buildingIndex;
      buildingRecord = UNIT_RECORD(buildingIndex);
      if ( (unsigned int)*(char *)(uintptr_t)(buildingRecord + 4) < 4
        && *(__int16 *)(uintptr_t)(buildingRecord + 16) != -1
        && *(_BYTE *)(uintptr_t)(slotIndex + gameData + 509676) != *(_BYTE *)(uintptr_t)(stackPtr + 4) )
      {
        break;
      }
    }
    if ( *(_DWORD *)(uintptr_t)(stackPtr + 316) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_before_path",
        (int)stackIndex,
        *(__int16 *)(uintptr_t)stackPtr,
        *(__int16 *)(uintptr_t)(stackPtr + 2),
        *(_DWORD *)(uintptr_t)(stackPtr + 316));
      UnitStack_ExecuteQueuedPath(stackIndex, 0, slotIndex, 0xFFFFFFFF, a4);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_after_path",
        (int)stackIndex,
        *(__int16 *)(uintptr_t)stackPtr,
        *(__int16 *)(uintptr_t)(stackPtr + 2),
        *(_DWORD *)(uintptr_t)(stackPtr + 316));
    }
    else
      UnitStack_ClearReadyFlags(stackPtr);
LABEL_16:
    nextStackOffset = i + 725;
    slotIndex = stackIndex + 1;
    stackIndex = slotIndex;
    if ( slotIndex >= 500 )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
      return LogAllUnits(nextStackOffset, slotIndex, 0xFFFFFFFF);
    }
  }
  UnitStack_ClearReadyFlags(stackPtr);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done_enemy_contact", (int)stackIndex, *(__int16 *)(uintptr_t)stackPtr, *(__int16 *)(uintptr_t)(stackPtr + 2), slotIndex);
  return LogAllUnits(nextStackOffset, slotIndex, 0xFFFFFFFF);
}
// 4119FD: simplified comparisons for 'edx.4': <0 || >=65 became >=65u
// 411A18: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 41194F: variable 'a4' is possibly undefined
// 4119A2: variable 'v7' is possibly undefined
// 411A67: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00411AB0) --------------------------------------------------------
signed int  UnitStack_HasBuilder(int stackIndex)
{
  __int16 *slotPtr; // edx
  int slotIndex; // eax
  int slotType; // ecx

  slotPtr = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  slotIndex = 0;
  while ( 1 )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_BUILDER )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00411B30) --------------------------------------------------------
__int16  Map_RedrawUnitFootprintByIndex(int stackIndex)
{
  __int16 *unit_stack; // ecx
  int result; // eax
  int unit_type; // eax
  int unit_metadata_offset; // eax
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex);
  x = unit_stack[0];
  y = unit_stack[1];
  result = WorldMap_RedrawTileIfVisible(x, y);
  unit_type = unit_stack[3];
  unit_metadata_offset = 88 * unit_type;
  if ( g_UnitTypeSpriteVerticalOffsetPx[unit_metadata_offset] )
  {
    if ( (unsigned __int16)unit_type >= 0x1Bu )
    {
      if ( (unsigned __int16)unit_type > 0x1Bu )
      {
        if ( (unsigned __int16)unit_type == 0x1E )
        {
          WorldMap_RedrawTileIfVisible(x + 1, y);
          WorldMap_RedrawTileIfVisible(x, y - 1);
          WorldMap_RedrawTileIfVisible(x - 1, y);
          result = WorldMap_RedrawTileIfVisible(x, y + 1);
        }
      }
      else
      {
        switch ( *((_BYTE *)unit_stack + 5) )
        {
          case 0:
          case 4:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            result = WorldMap_RedrawTileIfVisible(x + 1, y);
            break;
          case 1:
            WorldMap_RedrawTileIfVisible(x + 1, y);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 2:
          case 6:
            WorldMap_RedrawTileIfVisible(x, y - 1);
            result = WorldMap_RedrawTileIfVisible(x, y + 1);
            break;
          case 3:
            WorldMap_RedrawTileIfVisible(x + 1, y);
            WorldMap_RedrawTileIfVisible(x, y + 1);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 5:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            WorldMap_RedrawTileIfVisible(x, y + 1);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 7:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          default:
            return result;
        }
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00411CB0) --------------------------------------------------------
int  Map_RedrawUnitNeighborhoodByIndex(int stackIndex)
{
  int result; // eax
  __int16 *unit_stack; // ecx
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET);
  x = unit_stack[0];
  y = unit_stack[1];
  result = WorldMap_RedrawTileIfVisible(x, y);
  result = Unit_GetSpriteVerticalOffsetPx(stackIndex);
  if ( result )
  {
    WorldMap_RedrawTileIfVisible(x, y - 1);
    WorldMap_RedrawTileIfVisible(x, y + 1);
    WorldMap_RedrawTileIfVisible(x - 1, y);
    WorldMap_RedrawTileIfVisible(x + 1, y);
    WorldMap_RedrawTileIfVisible(x - 1, y - 1);
    WorldMap_RedrawTileIfVisible(x - 1, y + 1);
    WorldMap_RedrawTileIfVisible(x + 1, y - 1);
    return WorldMap_RedrawTileIfVisible(x + 1, y + 1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00411D70) --------------------------------------------------------
void Map_UpdateIdleAnimatedUnits(void)
{
  int stackIndex; // ecx
  int stackPtr; // edx
  int unitType; // eax
  int metadataOffset; // eax
  unsigned int nextAnimTick; // ebx
  int now; // eax
  int v6 CLASH95_UNUSED; // ecx
  int v7 CLASH95_UNUSED; // edx
  int v8 CLASH95_UNUSED; // ecx

  stackIndex = 0;
  stackPtr = gameData + UNIT_STACK_TABLE_OFFSET;
  do
  {
    unitType = *(__int16 *)(uintptr_t)(stackPtr + 6);
    if ( unitType != -1 )
    {
      metadataOffset = 88 * unitType;
      if ( (g_UnitTypeHasIdleAnimationFlags[metadataOffset] & 1) != 0 )
      {
        nextAnimTick = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[metadataOffset] + *(_DWORD *)(uintptr_t)(stackPtr + 24);
        if ( nextAnimTick < Time_Now(stackIndex, stackPtr) )
        {
          now = Time_Now(stackIndex, stackPtr);
          *(_DWORD *)(uintptr_t)(stackPtr + 24) = now;
          LOBYTE(now) = ((*(_BYTE *)(uintptr_t)(stackPtr + 23) & 7) + 1) & 7;
          BYTE1(now) = *(_BYTE *)(uintptr_t)(stackPtr + 23) & 0xF8;
          *(_BYTE *)(uintptr_t)(stackPtr + 23) = BYTE1(now);
          BYTE1(now) |= now;
          *(_BYTE *)(uintptr_t)(stackPtr + 23) = BYTE1(now);
          *(_BYTE *)(uintptr_t)(stackPtr + 23) = BYTE1(now) & 0xF8;
          *(_BYTE *)(uintptr_t)(stackPtr + 23) = BYTE1(now);
          Map_RedrawUnitFootprintByIndex(stackIndex);
        }
      }
    }
    ++stackIndex;
    stackPtr += 725;
  }
  while ( stackIndex < UNIT_STACK_TABLE_COUNT );
  UI_UpdateWorldMapUnitAttentionFlash();
  UI_UpdateUnitBlinkFlash(0, 0);
}
// 5202E4: using guessed type int gameData;

//----- (00411E20) --------------------------------------------------------
int  Unit_GetSpriteVerticalOffsetPx(int stackIndex)
{
  return (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180)];
}
// 5202E4: using guessed type int gameData;

//----- (00411E60) --------------------------------------------------------
signed int  Unit_AttemptNeighborMove(int stackIndex)
{
  int stack_offset; // edx
  signed int available_action_points; // ebp
  int direction_index; // esi
  int neighbor_column; // edx
  int neighbor_row; // ecx
  int *queued_path; // eax
  int last_path_step; // edx
  unsigned __int16 required_action_points; // ax
  int stack_record; // eax

  stack_offset = UNIT_STACK_STRIDE * stackIndex;
  stack_record = gameData + UNIT_STACK_TABLE_OFFSET + stack_offset;
  available_action_points = UnitStack_GetMinCurrentActionPoints(stack_record);
  if ( available_action_points < 3 )
    return 0;
  direction_index = 0;
  while ( direction_index < 16 )
  {
    neighbor_column = Map_NeighborDY[direction_index] + *(__int16 *)(uintptr_t)(stack_record + 2);
    neighbor_row = Map_NeighborDX[direction_index] + *(__int16 *)(uintptr_t)stack_record;
    if ( neighbor_row >= 0 && neighbor_row < MAP_WIDTH_TILES && neighbor_column >= 0 && neighbor_column < MAP_HEIGHT_TILES )
    {
      queued_path = Unit_MoveTrack(
                      stackIndex,
                      *(__int16 *)(uintptr_t)stack_record,
                      *(__int16 *)(uintptr_t)stack_record + Map_NeighborDX[direction_index],
                      *(__int16 *)(uintptr_t)(stack_record + 2),
                      available_action_points,
                      *(__int16 *)(uintptr_t)(stack_record + 2) + Map_NeighborDY[direction_index]);
      if ( queued_path )
      {
        last_path_step = queued_path[*queued_path];
        j__nfree_(queued_path);
        required_action_points = HIWORD(last_path_step);
        if ( available_action_points >= required_action_points )
          return 1;
      }
    }
    direction_index += 2;
  }
  return 0;
}
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (00411F60) --------------------------------------------------------
BOOL  UnitStack_CanExecuteQueuedPathNow(int stackIndex)
{
  int stackPtr; // eax
  int pathLength; // edx
  int pathBufferPtr; // eax
  BOOL result; // eax
  unsigned __int16 lastStepActionPoints; // si

  stackPtr = gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex;
  pathLength = *(_DWORD *)(uintptr_t)(stackPtr + 316);
  pathBufferPtr = stackPtr + 316;
  result = 0;
  if ( pathLength )
  {
    lastStepActionPoints = HIWORD(*(_DWORD *)(uintptr_t)(pathBufferPtr + 4 * (pathLength - 1) + 4));
    if ( UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex) >= lastStepActionPoints )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00412000) --------------------------------------------------------
void * UnitSlots_ExtractSpecialEntries(char *slotArray, int slotCount, char *extractedOut)
{
  int slotIndex; // edx
  int slotType; // eax
  int shiftIndex; // ebx
  _WORD *shiftCursor; // eax
  void *result; // eax
  int remainingCount; // [esp+8h] [ebp-14h]

  remainingCount = slotCount;
  slotIndex = 0;
  while ( slotIndex < remainingCount )
  {
    slotType = *(__int16 *)slotArray;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_GOLD_CARGO
      || slotType == UNIT_TYPE_PEASANT_CARGO
      || slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      shiftIndex = 0;
      qmemcpy(extractedOut, slotArray, 0x1Fu);
      extractedOut += 31;
      shiftCursor = slotArray;
      if ( remainingCount - slotIndex - 1 > 0 )
      {
        do
        {
          qmemcpy(shiftCursor, (char *)shiftCursor + 31, 0x1Fu);
          ++shiftIndex;
          shiftCursor = (_WORD *)((char *)shiftCursor + 31);
        }
        while ( shiftIndex < remainingCount - slotIndex - 1 );
      }
      *shiftCursor = -1;
      --remainingCount;
    }
    else
    {
      slotArray += 31;
      ++slotIndex;
    }
  }
  result = extractedOut;
  *(_WORD *)extractedOut = -1;
  return result;
}

void * UnitSlots_ExtractSpecialEntriesForBuildingAttack(char *slotArray, int slotCount, char *extractedOut)
{
  return UnitSlots_ExtractSpecialEntries(slotArray, slotCount, extractedOut);
}

//----- (004120B0) --------------------------------------------------------
int  UnitSlots_AppendEntries(char *destSlots, char *srcSlots)
{
  char *srcStart; // esi
  int srcCount; // ecx
  char *destAppendPtr; // edi
  int result; // eax

  srcStart = srcSlots;
  while ( *(__int16 *)destSlots != -1 )
    destSlots += 31;
  srcCount = 0;
  while ( *(__int16 *)srcSlots != -1 )
  {
    srcSlots += 31;
    ++srcCount;
  }
  destAppendPtr = destSlots;
  result = 31 * srcCount;
  qmemcpy(destAppendPtr, srcStart, 31 * srcCount);
  return result;
}

int  UnitSlots_AppendEntriesForBuildingAttack(char *destSlots, char *srcSlots)
{
  return UnitSlots_AppendEntries(destSlots, srcSlots);
}

//----- (00412100) --------------------------------------------------------
signed int  UnitStack_HasNormalCombatUnits(intptr_t stackPtr)
{
  signed int result; // eax
  intptr_t slot_record; // edx
  signed int squad_count; // esi
  signed int has_normal_unit; // ebx
  signed int slot_index; // ecx
  int unit_type; // eax

  if ( *(__int16 *)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
    return 0;
  result = Unit_GetSquadCount(stackPtr);
  squad_count = result;
  if ( result )
  {
    slot_record = stackPtr;
    has_normal_unit = 0;
    slot_index = 0;
    if ( result > 0 )
    {
      while ( !has_normal_unit )
      {
        unit_type = *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET);
        if ( unit_type == UNIT_TYPE_GOLD_CARGO
          || unit_type == UNIT_TYPE_PEASANT_CARGO
          || unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          || unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return has_normal_unit;
        }
        else
        {
          has_normal_unit = 1;
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return 1;
        }
      }
    }
    return has_normal_unit;
  }
  return result;
}

//----- (00412170) --------------------------------------------------------
signed int  UnitStack_HasGoldCargo(int stackPtr)
{
  int slotIndex; // edx
  int slotType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(uintptr_t)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_GOLD_CARGO )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121A0) --------------------------------------------------------
signed int  UnitStack_HasPeasantCargo(int stackPtr)
{
  int slotIndex; // edx
  int slotType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(uintptr_t)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121D0) --------------------------------------------------------
signed int  UnitStack_NormalizePeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  __int16 *slotPtr; // ecx
  int totalPeasantQuantity; // esi
  int peasantSlotCount; // edx
  int i; // ebx
  int slotType; // eax
  __int16 *v8; // edx
  int j; // ecx
  __int16 *clearCursor; // ecx
  int clearIndex; // eax
  __int16 *clearSlotPtr; // ebx
  signed int squadCount; // edi
  int v14 CLASH95_UNUSED; // edx
  int fullCargoUnits; // eax
  __int64 v16 CLASH95_UNUSED; // rtt
  int addedIndex; // ebx
  int v18; // ebp
  char minActionPoints; // [esp+4h] [ebp-18h]

  slotPtr = stackPtr + 3;
  totalPeasantQuantity = 0;
  peasantSlotCount = 0;
  for ( i = 0; i < 10; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++peasantSlotCount;
      totalPeasantQuantity += *((char *)slotPtr + 9);
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  minActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
  if ( (int)(intptr_t)v8 > totalPeasantQuantity )
  {
    clearCursor = stackPtr;
    clearIndex = 0;
    clearSlotPtr = stackPtr + 3;
    do
    {
      if ( *clearSlotPtr == -1 )
        break;
      if ( clearCursor[3] == UNIT_TYPE_PEASANT_CARGO )
        clearCursor[3] = -1;
      clearCursor = (__int16 *)((char *)clearCursor + 31);
      ++clearIndex;
      clearSlotPtr = (__int16 *)((char *)clearSlotPtr + 31);
    }
    while ( clearIndex < 10 );
    Unit_CompactSquad(stackPtr, (int)(intptr_t)clearCursor, a3);
    squadCount = Unit_GetSquadCount((int)(intptr_t)stackPtr);
    fullCargoUnits = totalPeasantQuantity / 100;
    addedIndex = 0;
    for ( j = (int)(intptr_t)stackPtr + 31 * squadCount; ; *(_BYTE *)(uintptr_t)(j - 17) = minActionPoints )
    {
      v18 = addedIndex + squadCount;
      if ( addedIndex >= fullCargoUnits )
        break;
      j += 31;
      *(_WORD *)(uintptr_t)(j - 25) = UNIT_TYPE_PEASANT_CARGO;
      *(_BYTE *)(uintptr_t)(j - 16) = 100;
      *(_BYTE *)(uintptr_t)(j - 15) = 0;
      *(_BYTE *)(uintptr_t)(j - 14) = 10;
      ++addedIndex;
    }
    LOBYTE(i) = 100;
    *(_BYTE *)(uintptr_t)(j + 14) = minActionPoints;
    *(_WORD *)(uintptr_t)(j + 6) = UNIT_TYPE_PEASANT_CARGO;
    *(_BYTE *)(uintptr_t)(j + 15) = totalPeasantQuantity % 100;
    v8 = stackPtr;
    *(_BYTE *)(uintptr_t)(j + 16) = 0;
    a2 = (DWORD)(intptr_t)stackPtr + 31 * v18 + 31;
    *(_BYTE *)(uintptr_t)(j + 17) = 10;
    *(_WORD *)(uintptr_t)(a2 + 6) = -1;
  }
  return Rules_SyncArmyFactStrength(stackPtr, (int)(intptr_t)v8, j, i, a2, a3);
}
// 412213: variable 'v8' is possibly undefined
// 41224F: variable 'v14' is possibly undefined
// 4122E3: variable 'j' is possibly undefined

//----- (00412300) --------------------------------------------------------
__int16 * UnitStack_CaptureDefeatedStack(
        __int16 *winnerStack,
        signed int defeatedStackPtr,
        int a3,
        int a4,
        double a5)
{
  __int16 *winner_stack;
  __int16 *defeated_stack;
  unsigned char winner_owner;
  signed int defeated_had_plague;
  int slot_index;
  int unit_type;
  int winner_count;
  int defeated_count;
  __int16 *result;

  Debug_Log(a3, a4, (DWORD)(intptr_t)winnerStack, (int)(intptr_t)aUnit_capture0x);
  winner_stack = winnerStack;
  defeated_stack = (__int16 *)(uintptr_t)defeatedStackPtr;
  if ( !winner_stack || !defeated_stack )
    return winner_stack;

  winner_owner = UNIT_STACK_OWNER_INDEX((int)(intptr_t)winner_stack);
  Diagnostics_TraceWorldMapActionEvent(
    "capture_defeated_stack_enter",
    Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
    Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
    winner_owner,
    Unit_GetSquadCount((int)(intptr_t)defeated_stack));
  defeated_had_plague = UnitStack_HasPlagueFlag((int)(intptr_t)defeated_stack);
  for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
  {
    __int16 *slot = (__int16 *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)defeated_stack, slot_index);
    unit_type = *slot;
    if ( unit_type == -1 )
      break;
    if ( unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      Prisoner_QueueCapturedUnit(
        *slot,
        *((unsigned __int8 *)slot + 2),
        slot[2],
        winner_owner,
        (DWORD)(intptr_t)winner_stack,
        slot[3]);
      *slot = -1;
    }
  }

  Unit_CompactSquad(defeated_stack, 0, a5);
  if ( defeated_stack[3] == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_empty_before_owner",
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
      winner_owner,
      0);
    return Rules_UnlinkArmyFact(defeated_stack, a5);
  }

  defeated_count = Unit_GetSquadCount((int)(intptr_t)defeated_stack);
  for ( slot_index = 0; slot_index < defeated_count; ++slot_index )
  {
    char *slot = (char *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)defeated_stack, slot_index);
    slot[2] = winner_owner;
  }
  UNIT_STACK_OWNER_INDEX((int)(intptr_t)defeated_stack) = winner_owner;
  Diagnostics_TraceWorldMapActionEvent(
    "capture_defeated_stack_owner_changed",
    Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
    Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
    winner_owner,
    defeated_count);
  UnitStack_ClearReadyFlags((int)(intptr_t)defeated_stack);
  Unit_CompactSquad(defeated_stack, 0, a5);
  if ( defeated_stack[3] == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_empty_after_owner",
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
      winner_owner,
      0);
    return Rules_UnlinkArmyFact(defeated_stack, a5);
  }

  UnitStack_NormalizePeasantCargo(defeated_stack, (DWORD)(intptr_t)winner_stack, a5);
  Rules_SyncArmyFactOwner(defeated_stack, winner_owner, (DWORD)(intptr_t)winner_stack, a5);

  winner_count = Unit_GetSquadCount((int)(intptr_t)winner_stack);
  defeated_count = Unit_GetSquadCount((int)(intptr_t)defeated_stack);
  if ( winner_count + defeated_count <= UNIT_STACK_SLOT_COUNT
    && UnitStack_GetMoveCostToTileIgnoringOccupancy(defeated_stack, *winner_stack, winner_stack[1]) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_merge_kill",
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
      winner_count,
      defeated_count);
    qmemcpy(
      (void *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)winner_stack, winner_count),
      (const void *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)defeated_stack, 0),
      UNIT_STACK_SLOT_STRIDE * defeated_count);
    if ( winner_count + defeated_count < UNIT_STACK_SLOT_COUNT )
      *(__int16 *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)winner_stack, winner_count + defeated_count) = -1;
    Unit_Kill((int)(intptr_t)defeated_stack, 0, (DWORD)(intptr_t)winner_stack, a5);
    Rules_LinkArmyFact(winner_stack, 0, 0, a5, 0, (DWORD)(intptr_t)winner_stack);
    result = (__int16 *)(uintptr_t)Rules_SyncArmyFactStrength(winner_stack, 0, 0, 0, (DWORD)(intptr_t)winner_stack, a5);
  }
  else
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      char *slot = (char *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)defeated_stack, slot_index);
      if ( *(__int16 *)slot == -1 )
        break;
      slot[2] = winner_owner;
    }
    UNIT_STACK_OWNER_INDEX((int)(intptr_t)defeated_stack) = winner_owner;
    if ( *(_DWORD *)(uintptr_t)UNIT_STACK_PATH_BUFFER((int)(intptr_t)defeated_stack) )
      *(_DWORD *)(uintptr_t)UNIT_STACK_PATH_BUFFER((int)(intptr_t)defeated_stack) = 0;
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_retained",
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)(intptr_t)defeated_stack),
      winner_owner,
      Unit_GetSquadCount((int)(intptr_t)defeated_stack));
    result = (__int16 *)(uintptr_t)Rules_SyncArmyFactOwner(defeated_stack, winner_owner, (DWORD)(intptr_t)winner_stack, a5);
  }
  if ( defeated_had_plague )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      __int16 *slot = (__int16 *)(uintptr_t)UNIT_STACK_SLOT((int)(intptr_t)winner_stack, slot_index);
      unit_type = *slot;
      if ( unit_type == -1 )
        break;
      if ( unit_type == UNIT_TYPE_PEASANT_CARGO )
        *((_BYTE *)slot + 13) |= UNIT_SLOT_FLAG_PLAGUE;
    }
    return Trap_HurtStack(winner_stack, 0, (DWORD)(intptr_t)winner_stack, a5);
  }
  return result;
}

//----- (00412520) --------------------------------------------------------
int  Unit_CreateNearbyUnitGroup(int originRow, int originColumn, unsigned __int8 *sourceSlots, double a4)
{
  unsigned __int8 *sourceSlotsPtr; // ebp
  signed int createSucceeded; // edi
  int neighborIndex; // esi
  int v7; // ecx
  int neighborColumn; // edx
  int neighborRow; // eax
  int slotCount; // edx
  unsigned __int8 *i; // eax
  int slotByteOffset; // ebx
  int v13; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int neighborColumnArg; // [esp-4h] [ebp-24h]
  int targetStackPtr; // [esp+0h] [ebp-20h]
  int neighborOrdinal; // [esp+4h] [ebp-1Ch]

  sourceSlotsPtr = sourceSlots;
  createSucceeded = 0;
  Debug_Log(originRow, (char)(intptr_t)sourceSlots, (DWORD)(intptr_t)sourceSlots, (int)(intptr_t)aUnitCreateNearbyUnitGroup);
  neighborIndex = 0;
  neighborOrdinal = 0;
  do
  {
    v7 = Map_NeighborDX[neighborIndex];
    neighborColumn = Map_NeighborDY[neighborIndex] + originColumn;
    neighborRow = v7 + originRow;
    if ( v7 + originRow >= 0 )
    {
      v7 = gameData;
      if ( neighborRow < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) && neighborColumn >= 0 && neighborColumn < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        LOBYTE(sourceSlots) = -1;
        if ( !Trap_GetTileOwnerMask(neighborRow, neighborColumn, -1) )
        {
          neighborColumnArg = Map_NeighborDY[neighborIndex] + originColumn;
          LOBYTE(sourceSlots) = Rng_RandRange(0, 7);
          createSucceeded = Unit_Create(*(__int16 *)sourceSlotsPtr, sourceSlotsPtr[2], v13, (char)(intptr_t)sourceSlots, neighborColumnArg);
          if ( createSucceeded )
            break;
        }
      }
    }
    neighborIndex += 2;
    ++neighborOrdinal;
  }
  while ( neighborIndex < 16 );
  if ( createSucceeded )
  {
    slotCount = 0;
    targetStackPtr = UNIT_STACK_STRIDE
        * *(unsigned __int16 *)(uintptr_t)(gameData
                              + TILE_ROW_STRIDE * (Map_NeighborDX[2 * neighborOrdinal] + originRow)
                              + 2 * (Map_NeighborDY[2 * neighborOrdinal] + originColumn)
                              + TILE_MAP_OFFSET)
        + gameData
        + UNIT_STACK_TABLE_OFFSET;
    for ( i = sourceSlotsPtr; ; i += 31 )
    {
      slotByteOffset = 31 * slotCount;
      if ( *(__int16 *)i == -1 )
        break;
      ++slotCount;
    }
    qmemcpy((void *)(uintptr_t)(targetStackPtr + 6), sourceSlotsPtr, 31 * slotCount);
    if ( slotCount < 9 )
    {
      slotByteOffset += targetStackPtr;
      *(_WORD *)(uintptr_t)(slotByteOffset + 6) = -1;
    }
    Rules_LinkArmyFact((__int16 *)(uintptr_t)targetStackPtr, slotCount, 0, a4, slotByteOffset, (DWORD)(intptr_t)sourceSlotsPtr);
    Rules_SyncArmyFactStrength((__int16 *)(uintptr_t)targetStackPtr, v15, v16, slotByteOffset, (DWORD)(intptr_t)sourceSlotsPtr, a4);
    Debug_Log(v17, slotByteOffset, targetStackPtr, (int)(intptr_t)aUnit_createn_1);
    Unit_DebugDumpFormationSizes(targetStackPtr, targetStackPtr);
    return targetStackPtr;
  }
  else
  {
    Debug_Log(v7, (char)(intptr_t)sourceSlots, (DWORD)(intptr_t)sourceSlotsPtr, (int)(intptr_t)aUnit_createn_0);
    return 0;
  }
}
// 4126A1: variable 'v13' is possibly undefined
// 4126BA: variable 'v7' is possibly undefined
// 412704: variable 'v15' is possibly undefined
// 412704: variable 'v16' is possibly undefined
// 412723: variable 'v17' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (004127A0) --------------------------------------------------------
int  UnitSlot_AdjustFatigueByPredicate(int slotPtr, int fatigueDelta, BOOL ( *predicate)(int slotPtr))
{
  int result; // eax
  signed char newFatigue; // cl

  result = predicate(slotPtr);
  if ( result )
  {
    result = *(__int16 *)(uintptr_t)slotPtr;
    if ( result != UNIT_TYPE_GOLD_CARGO
      && result != UNIT_TYPE_PEASANT_CARGO
      && result != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && result != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      newFatigue = fatigueDelta + *(char *)(uintptr_t)(slotPtr + 10);
      *(_BYTE *)(uintptr_t)(slotPtr + 10) = newFatigue;
      if ( newFatigue < 0 )
        *(_BYTE *)(uintptr_t)(slotPtr + 10) = 0;
      if ( *(char *)(uintptr_t)(slotPtr + 10) > 100 )
        *(_BYTE *)(uintptr_t)(slotPtr + 10) = 100;
      return *(char *)(uintptr_t)(slotPtr + 10);
    }
  }
  return result;
}

CLASH95_INTERNAL BOOL UnitSlot_PredicateAlways(int slotPtr)
{
  (void)slotPtr;
  return 1;
}

//----- (004127F0) --------------------------------------------------------
signed int  UnitStack_AdjustFatigueByPredicate(
        __int16 *stackPtr,
        int fatigueDelta,
        BOOL ( *predicate)(int stackPtr),
        DWORD a4,
        double a5)
{
  __int16 *slotPtr; // edx
  int slotIndex; // ecx
  int slotType; // eax
  signed int result; // eax
  char fatigueDeltaByte; // [esp+0h] [ebp-8h]

  fatigueDeltaByte = fatigueDelta;
  if ( fatigueDelta <= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)stackPtr)) == 0 )
  {
    slotPtr = stackPtr + 3;
    slotIndex = 0;
    while ( slotIndex < 10 )
    {
      if ( *slotPtr == -1 )
        break;
      if ( predicate((int)(intptr_t)slotPtr) )
      {
        slotType = *slotPtr;
        if ( slotType != UNIT_TYPE_GOLD_CARGO
          && slotType != UNIT_TYPE_PEASANT_CARGO
          && slotType != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && slotType != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          int fatigue = (signed char)*((char *)slotPtr + 10) + (signed char)fatigueDeltaByte;
          *((_BYTE *)slotPtr + 10) = (unsigned char)fatigue;
          if ( fatigue < 0 )
            *((_BYTE *)slotPtr + 10) = 0;
          if ( *((char *)slotPtr + 10) > 100 )
            *((_BYTE *)slotPtr + 10) = 100;
        }
      }
      ++slotIndex;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
    }
    return Rules_SyncArmyFactStrength(stackPtr, (int)(intptr_t)slotPtr, slotIndex, (char)(intptr_t)predicate, a4, a5);
  }
  return result;
}

//----- (00412880) --------------------------------------------------------
int  UnitSlot_AdjustMoraleByPredicate(int slotPtr, int moraleDelta, BOOL ( *predicate)(int slotPtr))
{
  int result; // eax
  int unit_type; // eax
  int morale; // eax

  result = predicate(slotPtr);
  if ( result )
  {
    unit_type = *(__int16 *)(uintptr_t)slotPtr;
    if ( unit_type != UNIT_TYPE_GOLD_CARGO
      && unit_type != UNIT_TYPE_PEASANT_CARGO
      && unit_type != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && unit_type != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      morale = *(char *)(uintptr_t)(slotPtr + 11) + moraleDelta;
      *(_BYTE *)(uintptr_t)(slotPtr + 11) = morale;
      if ( moraleDelta > 0 )
        *(_BYTE *)(uintptr_t)(slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      if ( *(char *)(uintptr_t)(slotPtr + 11) < 0 )
        *(_BYTE *)(uintptr_t)(slotPtr + 11) = 0;
      if ( *(char *)(uintptr_t)(slotPtr + 11) > 20 )
        *(_BYTE *)(uintptr_t)(slotPtr + 11) = 20;
      return *(char *)(uintptr_t)(slotPtr + 11);
    }
  }
  return result;
}

//----- (004128E0) --------------------------------------------------------
signed int  UnitStack_AdjustMoraleByPredicate(
        __int16 *stackPtr,
        int moraleDelta,
        BOOL ( *predicate)(int stackPtr),
        DWORD a4,
        double a5)
{
  __int16 *slotPtr; // edx
  int slotIndex; // ecx
  int slotType; // eax
  signed int result; // eax

  if ( moraleDelta >= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)stackPtr)) == 0 )
  {
    slotPtr = stackPtr + 3;
    slotIndex = 0;
    while ( slotIndex < 10 )
    {
      if ( *slotPtr == -1 )
        break;
      if ( predicate((int)(intptr_t)slotPtr) )
      {
        slotType = *slotPtr;
        if ( slotType != UNIT_TYPE_GOLD_CARGO
          && slotType != UNIT_TYPE_PEASANT_CARGO
          && slotType != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && slotType != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          *((_BYTE *)slotPtr + 11) += moraleDelta;
          if ( moraleDelta > 0 )
            *((_BYTE *)slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
          if ( *((char *)slotPtr + 11) < 0 )
            *((_BYTE *)slotPtr + 11) = 0;
          if ( *((char *)slotPtr + 11) > 20 )
            *((_BYTE *)slotPtr + 11) = 20;
        }
      }
      ++slotIndex;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
    }
    return Rules_SyncArmyFactStrength(stackPtr, (int)(intptr_t)slotPtr, slotIndex, (char)(intptr_t)predicate, a4, a5);
  }
  return result;
}

//----- (00412970) --------------------------------------------------------
int  UnitSlot_CycleOrderState(int result)
{
  char nextOrderState; // dl
  char clearedFlags; // dh
  char updatedFlags; // bl

  nextOrderState = (UNIT_SLOT_ORDER_STATE(result) + 1) & 3;
  clearedFlags = *(_BYTE *)(uintptr_t)(result + 12) & 0xF3;
  *(_BYTE *)(uintptr_t)(result + 12) = clearedFlags;
  updatedFlags = (4 * nextOrderState) | clearedFlags;
  *(_BYTE *)(uintptr_t)(result + 12) = updatedFlags;
  if ( (unsigned __int8)((unsigned __int8)(16 * updatedFlags) >> 6) > 2u )
  {
    *(_BYTE *)(uintptr_t)(result + 12) = updatedFlags & 0xF3;
    if ( (clearedFlags & 3u) < 3 )
    {
      *(_BYTE *)(uintptr_t)(result + 12) = updatedFlags & 0xF0;
      *(_BYTE *)(uintptr_t)(result + 12) = ((clearedFlags & 3) + 1) & 3 | ((4 * nextOrderState) | clearedFlags) & 0xF0;
    }
  }
  return result;
}

//----- (004129E0) --------------------------------------------------------
signed int  UnitStack_CycleAllSlotOrders(__int16 *stackPtr, DWORD a2, double a3)
{
  int stack_record; // edi
  int slot_index; // edx
  int slot_cursor; // ecx
  int slot_type; // ebx

  stack_record = (int)(uintptr_t)stackPtr;
  slot_index = 0;
  slot_cursor = stack_record;
  do
  {
    slot_type = *(__int16 *)(uintptr_t)(unsigned int)(slot_cursor + UNIT_STACK_SLOT_BASE_OFFSET);
    if ( slot_type == -1 )
      return Rules_SyncArmyFactStrength(stackPtr, slot_index, slot_cursor, -1, a2, a3);
    UnitSlot_CycleOrderState(UNIT_STACK_SLOT(stack_record, slot_index));
    ++slot_index;
    slot_cursor += UNIT_STACK_SLOT_STRIDE;
  }
  while ( slot_index < UNIT_STACK_SLOT_COUNT );
  return Rules_SyncArmyFactStrength(stackPtr, slot_index, slot_cursor, slot_type, a2, a3);
}

//----- (00412A30) --------------------------------------------------------
__int16 * UnitStack_SetSpentTurnFlag(int stackPtr)
{
  __int16 *result; // eax
  int i; // edx
  char slotFlags; // bl

  result = (__int16 *)(uintptr_t)(stackPtr + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    slotFlags = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = slotFlags | UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A60) --------------------------------------------------------
__int16 * UnitStack_ClearSpentTurnFlag(int stackPtr)
{
  __int16 *result; // eax
  int i; // edx
  char slotFlags; // bl

  result = (__int16 *)(uintptr_t)(stackPtr + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    slotFlags = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = slotFlags & ~UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A90) --------------------------------------------------------
int  UnitStack_SetPlagueFlag(int result)
{
  int i; // edx
  char slotFlags; // bl

  for ( i = 0; i < 10; ++i )
  {
    if ( *(__int16 *)(uintptr_t)(result + 6) == -1 )
      break;
    slotFlags = *(_BYTE *)(uintptr_t)(result + 19);
    result += 31;
    *(_BYTE *)(uintptr_t)(result - 12) = slotFlags | 8;
  }
  return result;
}

//----- (00412AC0) --------------------------------------------------------
signed int  UnitStack_HasPlague(int stackPtr)
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

//----- (00412AF0) --------------------------------------------------------
signed int  UnitStack_HasLowMoraleUnit(int stackPtr)
{
  __int16 *slotPtr; // eax
  int slotIndex; // edx

  slotPtr = (__int16 *)(uintptr_t)(stackPtr + 6);
  slotIndex = 0;
  while ( 1 )
  {
    if ( *slotPtr == -1 )
      return 0;
    if ( (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0 )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B20) --------------------------------------------------------
int  UnitStackSelection_BuildSelectedSlotIndexList(int result, int slotCount, int *selectedOut)
{
  int selectionFlags; // esi
  int *outCursor; // edx
  int i; // [esp+0h] [ebp-Ch]

  selectionFlags = result;
  for ( i = 0; slotCount > i; ++i )
  {
    if ( *(_DWORD *)(uintptr_t)(selectionFlags + 4 * i) )
    {
      outCursor = selectedOut++;
      *outCursor = i;
    }
    result = i;
  }
  *selectedOut = -1;
  return result;
}

//----- (00412B60) --------------------------------------------------------
signed int  UnitStack_HasSpecialPersonageUnits(intptr_t stackPtr)
{
  int slotIndex; // ecx
  int slotType; // eax

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B90) --------------------------------------------------------
int  UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(char *slotArray, int slotCount, int wallDefenseBonus)
{
  int hasSpecialPersonage; // ebx
  int slotIndex; // eax
  char *slotCursor; // edx
  int slotType; // ecx

  hasSpecialPersonage = 0;
  slotIndex = 0;
  if ( slotCount > 0 )
  {
    slotCursor = slotArray;
    do
    {
      if ( hasSpecialPersonage )
        break;
      slotType = *(__int16 *)slotCursor;
      if ( slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        hasSpecialPersonage = 1;
      ++slotIndex;
      slotCursor += 31;
    }
    while ( slotIndex < slotCount );
  }
  return UnitSlots_CalcCombatStrengthScore(slotArray, slotCount, hasSpecialPersonage, wallDefenseBonus);
}
// 412B90: could not find valid save-restore pair for ebx

//----- (00412BE0) --------------------------------------------------------
int  UnitStack_CalcMilitaryStrength(int stackPtr)
{
  signed int squadCount; // eax
  int v2; // edx

  squadCount = Unit_GetSquadCount(stackPtr);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)(uintptr_t)(v2 + 6), squadCount, 0);
}
// 412BEA: variable 'v2' is possibly undefined
