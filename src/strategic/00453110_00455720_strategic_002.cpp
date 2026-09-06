/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "strategic_shared_state.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00453110) --------------------------------------------------------
signed int  Rules_QueuePathToTile(int stack_index, int target_x, int target_y, DWORD a4)
{
  int *track; // ebx
  int queued_target_xy; // [esp+0h] [ebp-10h]

  /* Whole-family __usercall loss (sub_453110 / sub_4532A0 / sub_453600 /
     Move_IsAtTargetOrCanStay / Move_TryApproachTarget all open with
     `mov ecx, eax`): ECX carries the stack index for the entire body and
     is callee-saved across the Unit_MoveTrack family, Path_GenerateTrack and
     Port_GenerateApproachTrack (each pushes and pops ECX), while the
     generated track is kept in EBX and tested through the EDX copy made
     by `mov edx, eax; mov ebx, eax`.  IDA dropped every one of those
     registers and emitted never-assigned temps, so the queued path was
     written at a wild stack offset (or not at all). */
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_target_xy) && !abs32(target_y - BYTE1(queued_target_xy)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(stack_index, target_y, a4);
  track = Unit_MoveTrack(
         stack_index,
         *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
         stack_index,
         *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET),
         a4,
         target_y);
  Pathing_DisableBridgeCrossings(stack_index, (char)(intptr_t)track, a4);
  if ( !track )
    return 0;
  if ( *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
    *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
  qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
  j__nfree_();
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (004532A0) --------------------------------------------------------
signed int  Rules_QueuePathNearTile(int stack_index, int target_x, int target_y, DWORD a4)
{
  _DWORD *track; // ebx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  /* Whole-family __usercall loss (sub_453110 / sub_4532A0 / sub_453600 /
     Move_IsAtTargetOrCanStay / Move_TryApproachTarget all open with
     `mov ecx, eax`): ECX carries the stack index for the entire body and
     is callee-saved across the Unit_MoveTrack family, Path_GenerateTrack and
     Port_GenerateApproachTrack (each pushes and pops ECX), while the
     generated track is kept in EBX and tested through the EDX copy made
     by `mov edx, eax; mov ebx, eax`.  IDA dropped every one of those
     registers and emitted never-assigned temps, so the queued path was
     written at a wild stack offset (or not at all). */
  Debug_Log(stack_index, target_y, a4, (int)(intptr_t)aJest_droga_w_3);
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(target_x - (unsigned __int8)queued_target_xy) < 2 )
    {
      a4 = BYTE1(queued_target_xy);
      if ( (int)abs32(target_y - BYTE1(queued_target_xy)) > 2 )
      {
        if ( target_x != (unsigned __int8)queued_target_xy )
          return 1;
        if ( target_y != BYTE1(queued_target_xy) )
          return 1;
      }
    }
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(stack_index, target_y, a4);
  track = Unit_MoveTrackNearTile(stack_index, target_x, stack_index, target_y, a4);
  Pathing_DisableBridgeCrossings(stack_index, (char)(intptr_t)track, a4);
  if ( track )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 5202E4: using guessed type int gameData;

//----- (00453440) --------------------------------------------------------
signed int  Rules_QueuePathNearCastle(int stack_index, int castle_x, int castle_y, DWORD a4)
{
  const void *track; // ebx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    a4 = (unsigned __int8)queued_target_xy;
    if ( (int)abs32(castle_x - (unsigned __int8)queued_target_xy) < 3 && (int)abs32(castle_y - BYTE1(queued_target_xy)) < 3 )
    {
      if ( castle_x != (unsigned __int8)queued_target_xy )
        return 1;
      if ( castle_y != BYTE1(queued_target_xy) )
        return 1;
    }
  }
  /* sub_453440: `mov ecx, eax` - ecx holds stack_index for the whole body, and
     `mov edx, eax; mov ebx, eax` after sub_415970 keeps the returned track. IDA
     lost both and emitted the undefined temps v5/v7/v8/v9. */
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(stack_index, castle_y, a4);
  track = (const void *)(uintptr_t)Building_GenerateNearApproachTrack(stack_index, *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(castle_x, castle_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, stack_index, castle_y, a4);
  Pathing_DisableBridgeCrossings(stack_index, (char)(intptr_t)track, a4);
  if ( track )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 453483: variable 'v5' is possibly undefined
// 4534C4: variable 'v7' is possibly undefined
// 4534CB: variable 'v9' is possibly undefined
// 4534EE: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453600) --------------------------------------------------------
signed int  Rules_QueuePathToPort(int army_index, int target_x, int queued_dest, DWORD a4)
{
  int target_y; // esi
  int *move_track; // ebx
  /* Whole-family __usercall loss (sub_453110 / sub_4532A0 / sub_453600 /
     Move_IsAtTargetOrCanStay / Move_TryApproachTarget all open with
     `mov ecx, eax`): ECX carries the stack index for the entire body and
     is callee-saved across the Unit_MoveTrack family, Path_GenerateTrack and
     Port_GenerateApproachTrack (each pushes and pops ECX), while the
     generated track is kept in EBX and tested through the EDX copy made
     by `mov edx, eax; mov ebx, eax`.  IDA dropped every one of those
     registers and emitted never-assigned temps, so the queued path was
     written at a wild stack offset (or not at all). */

  target_y = queued_dest;
  LOBYTE(queued_dest) = gameData;
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * army_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_dest = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * army_index + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_dest) && !abs32(target_y - BYTE1(queued_dest)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(army_index) )
    Pathing_EnableBridgeCrossings(army_index, queued_dest, a4);
  move_track = Port_GenerateApproachTrack(army_index);
  Pathing_DisableBridgeCrossings(army_index, (char)(intptr_t)move_track, a4);
  if ( !move_track )
    return 0;
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * army_index + UNIT_STACK_PATH_OFFSET) )
    *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * army_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
  qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * army_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), move_track, UNIT_STACK_PATH_BYTES);
  j__nfree_();
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00453770) --------------------------------------------------------
signed int  Rules_QueuePathToCastle(int stack_index, int castle_x, int castle_y, DWORD a4)
{
  const void *track; // ebx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    a4 = (unsigned __int8)queued_target_xy;
    if ( (int)abs32(castle_x - (unsigned __int8)queued_target_xy) < 2 && (int)abs32(castle_y - BYTE1(queued_target_xy)) < 2 )
    {
      if ( castle_x != (unsigned __int8)queued_target_xy )
        return 1;
      if ( castle_y != BYTE1(queued_target_xy) )
        return 1;
    }
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(stack_index, castle_y, a4);
  track = (const void *)Building_GenerateApproachTrack(
                       stack_index,
                       *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(castle_x, castle_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
                       stack_index,
                       castle_y,
                       a4);
  Pathing_DisableBridgeCrossings(stack_index, (char)(intptr_t)track, a4);
  /* sub_453770: same __usercall shape as sub_453440 - ecx keeps stack_index and
     the returned track is tested directly. */
  if ( track )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 4537B3: variable 'v5' is possibly undefined
// 4537F4: variable 'v7' is possibly undefined
// 4537FB: variable 'v9' is possibly undefined
// 45381E: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453930) --------------------------------------------------------
signed int  Move_IsAtTargetOrCanStay(int stack_index, int target_x, int target_y)
{
  signed int result; // eax
  int queued_target_xy; // [esp+0h] [ebp-10h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_target_xy) && !abs32(target_y - BYTE1(queued_target_xy)) )
      return 1;
  }
  result = (signed int)(intptr_t)Temple_GenerateApproachTrack(stack_index, target_x, stack_index, target_y);
  if ( result )
  {
    /* 453977: ECX still holds the stack index - Path_GenerateTrack preserves it. */
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00453A90) --------------------------------------------------------
signed int  Move_TryApproachTarget(int stack_index, DWORD target_x, int target_y)
{
  signed int result; // eax
  const void *track; // ebp
  signed int min_action_points; // eax
  signed int queued_move_cost; // edx
  int stack_offset; // ebx
  unsigned __int16 required_move_cost; // di
  int queued_target_xy; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET)
    && (queued_target_xy = *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320), (int)abs32(target_x - (unsigned __int8)queued_target_xy) <= 2)
    && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 2 )
  {
    /* 453B85: `xor edx,edx; mov dx, word ptr [esp+18h+var_14+2]` - the cost is
       the zero-extended HIWORD of the queued step, which IDA dropped. */
    queued_move_cost = HIWORD(queued_target_xy);
    min_action_points = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
    return min_action_points >= queued_move_cost;
  }
  else
  {
    result = (int)(intptr_t)(Building_GenerateApproachTrack(stack_index, *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(target_x, target_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, stack_index, target_y, target_x));
    track = (const void *)(uintptr_t)result;
    if ( result )
    {
      stack_offset = UNIT_STACK_STRIDE * stack_index;
      required_move_cost = HIWORD(*(_DWORD *)(uintptr_t)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET) < required_move_cost )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
          *(_DWORD *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
        qmemcpy((void *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        return 1;
      }
    }
  }
  return result;
}
// 453B90: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453C90) --------------------------------------------------------
signed int  Rules_QueuePathIntoArmyRange(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  signed int result; // eax
  int v8; // ecx
  const void *track; // ebp
  signed int min_action_points; // eax
  signed int queued_move_cost; // edx
  int stack_offset; // ebx
  unsigned __int16 required_move_cost; // di
  int v14; // ecx
  int queued_target_xy; // [esp+4h] [ebp-14h]

  Debug_Log(stack_index, target_y, a4, (int)(intptr_t)aOddzial_w_za_2);
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v6 + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET)
    && (a4 = UNIT_STACK_STRIDE * v5, queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v5 + 320), (int)abs32(target_x - (unsigned __int8)queued_target_xy) <= 1)
    && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 1 )
  {
    min_action_points = UnitStack_GetMinCurrentActionPoints(a4 + gameData + UNIT_STACK_TABLE_OFFSET);
    return min_action_points >= queued_move_cost;
  }
  else
  {
    result = (signed int)(intptr_t)Unit_MoveTrackNearTile(v5, target_x, v5, target_y, a4);
    track = (const void *)(uintptr_t)result;
    if ( result )
    {
      stack_offset = UNIT_STACK_STRIDE * v8;
      required_move_cost = HIWORD(*(_DWORD *)(uintptr_t)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET) < required_move_cost )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
          *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v14 + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
        qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v14 + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        return 1;
      }
    }
  }
  return result;
}
// 453CC7: variable 'v6' is possibly undefined
// 453CDB: variable 'v5' is possibly undefined
// 453D69: variable 'v11' is possibly undefined
// 453DA8: variable 'v8' is possibly undefined
// 453E38: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453E60) --------------------------------------------------------
signed int  Rules_GetPathDistanceToObject(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int *Track; // eax
  int path_distance; // edx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  Debug_Log(target_x, target_y, a4, (int)(intptr_t)aOdleglosc_od_1);
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v6 + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    a4 = gameData;
    queued_target_xy = *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(v5 - (unsigned __int8)queued_target_xy) <= 1 && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 1 )
      return *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET);
  }
  if ( MapTile_GetReligiousSiteCategory(v5, target_y) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, v7, v7, target_y);
  }
  else if ( MapTile_HasHiddenTreasure(v7, target_y) )
  {
    Track = Unit_MoveTrack(
              stack_index,
              *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
              v8,
              *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET),
              a4,
              target_y);
  }
  else if ( v8 == PORT_ROW && target_y == PORT_COLUMN )
  {
    Track = Port_GenerateApproachTrack(stack_index);
  }
  else
  {
    Track = (int*)(Unit_MoveTrackNearTile(stack_index, v8, v8, target_y, a4));
  }
  if ( !Track )
    return 1000;
  j__nfree_();
  return path_distance;
}
// 453E97: variable 'v6' is possibly undefined
// 453EAB: variable 'v5' is possibly undefined
// 453EBC: variable 'v7' is possibly undefined
// 453EFC: variable 'v8' is possibly undefined
// 453FD0: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453FE0) --------------------------------------------------------
BOOL  Rules_IsTempleWithinArmyRange(int stack_index, int temple_x, int temple_y)
{
  int *Track; // edx
  BOOL result; // eax
  signed int min_action_points; // eax
  signed int required_move_cost; // edx
  int queued_target_xy; // [esp+4h] [ebp-10h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(temple_x - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(temple_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
  }
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, temple_x, temple_x, temple_y);
    if ( Track )
    {
      qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), Track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  result = 0;
  if ( *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) )
  {
    min_action_points = UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index);
    if ( min_action_points >= required_move_cost )
      return 1;
  }
  return result;
}
// 454198: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004541B0) --------------------------------------------------------
BOOL  Player_CanEnterReligiousSiteTile(int player_index, int tile_x, int tile_y)
{
  int v4; // ecx

  return MapTile_GetReligiousSiteCategory(tile_x, tile_y) == RELIGIOUS_SITE_CATEGORY_SHRINE && PLAYER_RELIGION_FLAG(player_index)
      || MapTile_GetReligiousSiteCategory(v4, tile_y) == RELIGIOUS_SITE_CATEGORY_CULT_PLACE && !PLAYER_RELIGION_FLAG(player_index);
}
// 4541E6: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454210) --------------------------------------------------------
signed int  Move_CommitIfWithinCost(
        unsigned int stack_index,
        int a2,
        DWORD a3,
        double a4)
{
  int stack_offset; // ebx
  int stack_record; // eax
  int prev_x; // esi
  int prev_y; // edi
  int stack_record_after; // eax
  _DWORD pa_value[9]; // [esp-4h] [ebp-24h] BYREF

  /* 00454210.  Only EAX (stack_index) is a real parameter: 454216 'mov ecx,eax'
     overwrites the ECX that IDA guessed was arg2, and EBP is never read, so a2
     and a3 are phantoms.  ECX then holds stack_index for the WHOLE body and EBX
     holds stack_index*725; sub_410330 (UnitStack_ExecuteQueuedPath) saves and
     restores both (its prologue is 'push ebx; push ecx; push esi; push ebp'),
     which is why 454284 can range-check ECX right after the call.  The
     decompiler lost every one of those live registers and emitted the
     never-assigned v10/v11/v13/v14 - IDA flags all four at 454284/4542BD/
     454313/45431F.  Recovered verbatim from the asm. */
  pa_value[8] = a2;                                   /* 454210: push ecx */
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
    return 0;
  stack_offset = UNIT_STACK_STRIDE * stack_index;     /* ebx */
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TABLE_OFFSET);
  prev_y = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
  /* 45427D: `mov eax,ecx; call sub_410330` with edx=1, ebx=stack_offset and
     ecx=stack_index still live. */
  UnitStack_ExecuteQueuedPath(stack_index, 1, (char)stack_offset, stack_index, a4);
  /* 454284: `test ecx,ecx; jl` + `cmp ecx,1F4h; jg` - the surviving ECX, i.e.
     the stack index, bounded by the 500-entry stack table. */
  if ( stack_index > 0x1F4 || (unsigned int)*(__int16 *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET) > 0x28 )
    return 1;
  if ( Rules_IsQueuedPathTargetBridgeCrossing(stack_index) )   /* 4542B0: mov eax,ecx */
    Rules_BuildRoadOrStepTowardQueuedPath(stack_index, a3, a4);/* 4542BB: mov eax,ecx */
  stack_record_after = gameData + UNIT_STACK_STRIDE * stack_index;
  if ( prev_x == *(__int16 *)(uintptr_t)(stack_record_after + UNIT_STACK_TABLE_OFFSET)
    && prev_y == *(__int16 *)(uintptr_t)(stack_record_after + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) )
  {
    /* 454303: `mov ecx,1` - that same 1 is stored into the argument block AND
       is the ECX register argument of sub_480160 at 45431F. */
    pa_value[1] = 1;
    pa_value[2] = Rules_AddIntegerValue(0);
    Rules_PutInstanceSlotValue(
      *(_DWORD *)(uintptr_t)(stack_offset + gameData + 147895),
      (_BYTE*)(aPa),
      1,
      pa_value,
      a4);
  }
  return 1;
}
// 454284: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 45429D: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 5202E4: using guessed type int gameData;

//----- (00454330) --------------------------------------------------------
signed int  Rules_MarchToTemple(unsigned int stack_index, int temple_x, int temple_y, double a4)
{
  int *Track; // edx
  int stack_record; // eax
  int prev_x; // edi
  int prev_y; // ebx
  int v10; // ecx
  int stack_offset; // ebp
  int stack_record_after; // eax
  int v13; // ecx
  _DWORD pa_value[6]; // [esp+0h] [ebp-28h] BYREF
  int queued_target_xy; // [esp+18h] [ebp-10h]

  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(temple_x - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(temple_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
  }
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, temple_x, temple_x, temple_y);
    if ( Track )
    {
      qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), Track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
    return 0;
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TABLE_OFFSET);
  prev_y = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
  UnitStack_ExecuteQueuedPath(stack_index, 1, prev_y, stack_index, a4);
  if ( stack_index <= 0x1F4 && (unsigned int)*(__int16 *)(uintptr_t)(v10 + gameData + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET) <= 0x28 )
  {
    stack_offset = UNIT_STACK_STRIDE * stack_index;
    stack_record_after = gameData + stack_offset;
    if ( *(__int16 *)(uintptr_t)(gameData + stack_offset + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET) == -1 )
      return 0;
    if ( prev_x == *(__int16 *)(uintptr_t)(stack_record_after + UNIT_STACK_TABLE_OFFSET) && prev_y == *(__int16 *)(uintptr_t)(stack_record_after + 147176) )
    {
      pa_value[1] = 1;
      pa_value[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(uintptr_t)(gameData + stack_offset + 147895), (_BYTE*)(aPa_0), v13, pa_value, a4);
    }
  }
  return 1;
}
// 4544DF: simplified comparisons for 'ebp.4': <0 || >=1F5 became >=1F5u
// 454500: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 4544F6: variable 'v10' is possibly undefined
// 45457B: variable 'v13' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454590) --------------------------------------------------------
signed int  Rules_MarchNearTile(DWORD stack_index, int target_x, int target_y, double a4)
{
  int v5; // ecx
  int v6; // edx
  _DWORD *track; // edx
  DWORD stack_record; // eax
  int prev_x; // edi
  int prev_y; // ebx
  int v12; // ecx
  DWORD stack_offset; // ebp
  int v14; // ecx
  _DWORD pa_value[6]; // [esp+4h] [ebp-28h] BYREF
  int queued_target_xy; // [esp+1Ch] [ebp-10h]

  Debug_Log(target_x, target_y, stack_index, (int)(intptr_t)aMaszeruj_bli_1);
  if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v6 + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(v5 - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(target_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
  }
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
  {
    track = Unit_MoveTrackNearTile(stack_index, v5, v5, target_y, stack_index);
    if ( track )
    {
      qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
    return 0;
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TABLE_OFFSET);
  prev_y = *(__int16 *)(uintptr_t)(stack_record + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
  UnitStack_ExecuteQueuedPath(stack_index, 1, prev_y, stack_index, a4);
  if ( stack_index <= 0x1F4 && (unsigned int)*(__int16 *)(uintptr_t)(v12 + gameData + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET) <= 0x28 )
  {
    stack_offset = UNIT_STACK_STRIDE * stack_index;
    if ( prev_x == *(__int16 *)(uintptr_t)(gameData + stack_offset + UNIT_STACK_TABLE_OFFSET) && prev_y == *(__int16 *)(uintptr_t)(gameData + stack_offset + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) )
    {
      pa_value[1] = 1;
      pa_value[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(uintptr_t)(gameData + stack_offset + 147895), (_BYTE*)(aPa_1), v14, pa_value, a4);
    }
  }
  return 1;
}
// 45474F: simplified comparisons for 'ebp.4': <0 || >=1F5 became >=1F5u
// 454770: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 4545C6: variable 'v6' is possibly undefined
// 454607: variable 'v5' is possibly undefined
// 454766: variable 'v12' is possibly undefined
// 4547D7: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004547F0) --------------------------------------------------------
signed int  Rules_HostUnitAttack(int army_index, int target_army_index, char a3, DWORD a4, double a5)
{
  Unit_Attack(army_index, target_army_index, a3, a4, a5);
  return 1;
}

//----- (00454800) --------------------------------------------------------
signed int  Rules_HostUnitCaptureDefeatedStack(int capturing_stack_index, int defeated_stack_index, double a3)
{
  UnitStack_CaptureDefeatedStack(
    (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * capturing_stack_index),
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * defeated_stack_index,
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * defeated_stack_index,
    capturing_stack_index,
    a3);
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00454860) --------------------------------------------------------
signed int  Rules_HostUnitMoveAndHide(unsigned int target_x, unsigned int target_y, DWORD stack_index, double a4)
{
  DWORD stack_offset; // esi
  signed int result; // eax
  char move_succeeded; // bl
  int v8; // edx
  unsigned __int64 target_xy_pair; // [esp+4h] [ebp-18h]

  target_xy_pair = __PAIR64__(target_x, target_y);
  stack_offset = UNIT_STACK_STRIDE * stack_index;
  result = (signed int)(intptr_t)Unit_MoveTrack(
                         stack_index,
                         *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
                         target_x,
                         *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET),
                         stack_index,
                         target_y);
  move_succeeded = result;
  if ( result )
  {
    if ( *(_DWORD *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
      *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, v8, move_succeeded, stack_index, a4);
    if ( __PAIR64__(*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET)) == target_xy_pair )
    {
      UnitStack_TryHide(stack_index, target_xy_pair, stack_index, a4);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 454915: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454990) --------------------------------------------------------
signed int  Rules_HostUnitAttackBuilding(int army_index, int building_index, char a3, DWORD a4, double a5)
{
  Unit_AttackBuilding(army_index, building_index, a3, a4, a5);
  return 1;
}

//----- (004549A0) --------------------------------------------------------
BOOL  UnitStack_HasNormalCombatUnitsByIndex(int stack_index)
{
  return UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index) != 0;
}
// 5202E4: using guessed type int gameData;

//----- (004549E0) --------------------------------------------------------
signed int  UnitStack_GetSquadCountByIndex(int stack_index)
{
  return Unit_GetSquadCount(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00454A20) --------------------------------------------------------
signed int  Rules_IsQueuedPathTargetBridgeCrossing(int stack_index)
{
  signed int result; // eax
  int stack_table_base; // ebx

  if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_QUEUED_PATH_TABLE_OFFSET) )
    return 0;
  stack_table_base = gameData + UNIT_STACK_TABLE_OFFSET;
  result = Map_GetBridgeCrossingCostOrZero(
             (unsigned __int8)*(_DWORD *)(uintptr_t)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 4 * (*(_DWORD *)(uintptr_t)(stack_table_base + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) - 1) + 320),
             (unsigned __int8)BYTE1(*(_DWORD *)(uintptr_t)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 4 * (*(_DWORD *)(uintptr_t)(stack_table_base + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) - 1) + 320)));
  if ( result )
    return 1;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00454AE0) --------------------------------------------------------
signed int  Rules_BuildRoadOrStepTowardQueuedPath(int stack_index, DWORD a2, double a3)
{
  int stack_offset; // esi
  int stack_record; // eax
  int path_length; // ebx
  int path_base; // eax
  int next_waypoint_xy; // ebx
  signed int direction; // edi
  int cur_stack_index; // ecx
  int move_stack_index; // eax
  int step_direction; // edx
  signed int move_result; // eax
  int fallback_direction; // edx

  stack_offset = UNIT_STACK_STRIDE * stack_index;
  stack_record = UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET;
  path_length = *(_DWORD *)(uintptr_t)(stack_record + UNIT_STACK_PATH_OFFSET);
  path_base = stack_record + UNIT_STACK_PATH_OFFSET;
  if ( !path_length )
    return 1;
  next_waypoint_xy = *(_DWORD *)(uintptr_t)(path_base + 4 * (path_length - 1) + 4);
  direction = Facing_DirectionFromDelta8(
         (unsigned __int8)next_waypoint_xy - *(__int16 *)(uintptr_t)(gameData + stack_offset + UNIT_STACK_TABLE_OFFSET),
         BYTE1(next_waypoint_xy) - *(__int16 *)(uintptr_t)(gameData + stack_offset + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET));
  if ( Map_TileHasOwner(*(__int16 *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(uintptr_t)(stack_offset + gameData + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET))
    && !Rules_IsQueuedPathTargetBridgeCrossing(cur_stack_index) )
  {
    switch ( direction )
    {
      case DIRECTION8_SOUTHWEST:
        move_result = UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_WEST, a3);
        goto LABEL_10;
      case DIRECTION8_SOUTHEAST:
        move_result = UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_EAST, a3);
LABEL_10:
        if ( move_result )
          goto LABEL_13;
        fallback_direction = DIRECTION8_SOUTH;
        break;
      case DIRECTION8_NORTHEAST:
        if ( UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_EAST, a3) )
          goto LABEL_13;
        fallback_direction = DIRECTION8_NORTH;
        break;
      case DIRECTION8_NORTHWEST:
        if ( UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_WEST, a3) )
          goto LABEL_13;
        fallback_direction = DIRECTION8_NORTH;
        break;
      default:
        fallback_direction = direction;
        break;
    }
LABEL_12:
    UnitStack_MoveOneTileInDirection(cur_stack_index, fallback_direction, a3);
  }
  else
  {
    switch ( direction )
    {
      case DIRECTION8_SOUTHWEST:
        if ( !Road_Build(cur_stack_index, DIRECTION8_WEST, direction, a2, a3) )
        {
          move_stack_index = cur_stack_index;
          step_direction = DIRECTION8_WEST;
          goto LABEL_8;
        }
        break;
      case DIRECTION8_SOUTHEAST:
        if ( !Road_Build(cur_stack_index, DIRECTION8_EAST, direction, a2, a3) )
        {
          step_direction = DIRECTION8_EAST;
          move_stack_index = cur_stack_index;
LABEL_8:
          if ( !UnitStack_MoveOneTileInDirection(move_stack_index, step_direction, a3) )
          {
            move_result = Road_Build(cur_stack_index, DIRECTION8_SOUTH, direction, a2, a3);
            goto LABEL_10;
          }
        }
        break;
      case DIRECTION8_NORTHEAST:
        if ( !Road_Build(cur_stack_index, DIRECTION8_EAST, direction, a2, a3)
          && !UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_EAST, a3)
          && !Road_Build(cur_stack_index, DIRECTION8_NORTH, direction, a2, a3) )
        {
          fallback_direction = DIRECTION8_NORTH;
          goto LABEL_12;
        }
        break;
      case DIRECTION8_NORTHWEST:
        if ( !Road_Build(cur_stack_index, DIRECTION8_WEST, direction, a2, a3)
          && !UnitStack_MoveOneTileInDirection(cur_stack_index, DIRECTION8_WEST, a3)
          && !Road_Build(cur_stack_index, DIRECTION8_NORTH, direction, a2, a3) )
        {
          fallback_direction = DIRECTION8_NORTH;
          goto LABEL_12;
        }
        break;
      default:
        if ( !Road_Build(cur_stack_index, direction, direction, a2, a3) )
        {
          fallback_direction = direction;
          goto LABEL_12;
        }
        break;
    }
  }
LABEL_13:
  *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * cur_stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
  return 0;
}
// 454B74: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454D20) --------------------------------------------------------
int  Rules_BuildTrapNearTile(DWORD target_x, int target_y, DWORD stack_index, double a4)
{
  int v5; // edx
  int v6; // ecx
  int result; // eax
  char move_succeeded; // bl
  int v9; // edx
  __int64 dx; // rax
  __int64 dy; // rax

  Debug_Log(target_x, stack_index, stack_index, (int)(intptr_t)aBuduj_pulapke2);
  result = (int)(intptr_t)Unit_MoveTrackNearTile(stack_index, v6, v6, v5, stack_index);
  move_succeeded = result;
  if ( result )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) )
      *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, v9, move_succeeded, stack_index, a4);
    dx = (int)(*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET) - target_x);
    if ( (int)((HIDWORD(dx) ^ dx) - HIDWORD(dx)) >= 2 )
      return 0;
    dy = *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) - target_y;
    if ( (int)((HIDWORD(dy) ^ dy) - HIDWORD(dy)) >= 2 )
    {
      return 0;
    }
    else
    {
      Trap_New(target_x, target_y, target_x, stack_index, a4);
      return 1;
    }
  }
  return result;
}
// 454D49: variable 'v6' is possibly undefined
// 454D49: variable 'v5' is possibly undefined
// 454DD0: variable 'v9' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454E70) --------------------------------------------------------
int  UnitStack_CalcArmyFactStrength(int stack_record)
{
  int total_strength;
  signed int i;
  char *unit_slot;
  int melee_strength;
  int shot_strength;

  total_strength = 0;
  unit_slot = (char *)(uintptr_t)(unsigned int)(stack_record + 6);
  for ( i = 0; i < Unit_GetSquadCount(stack_record); ++i )
  {
    melee_strength = Unit_CalcEffectivenessA(unit_slot, 0);
    shot_strength = Unit_CalcEffectivenessC((__int16 *)unit_slot);
    if ( melee_strength <= shot_strength )
      total_strength += shot_strength;
    else
      total_strength += melee_strength;
    unit_slot += UNIT_SLOT_RECORD_BYTES;
  }
  return total_strength;
}
//----- (00454ED0) --------------------------------------------------------
signed int  Rules_EnsureArmyFactForStack(clash95_unaligned_int16 *army_stack, int army_id, double a3, char a4, DWORD a5)
{
  if ( (unsigned int)army_stack[3] > 0x28 && * (clash95_unaligned_uint32 *)((char *)army_stack + 721) )
  {
    Rules_RetractArmyFact((clash95_unaligned_uint32 *)army_stack, army_id, (int)(intptr_t)army_stack, a3);
    return 1;
  }
  else if ( * (clash95_unaligned_uint32 *)((char *)army_stack + 721) )
  {
    return 0;
  }
  else
  {
    Rules_CreateArmyFact(army_stack, *(unsigned __int16 *)(uintptr_t)(2 * army_stack[1] + gameData + TILE_ROW_STRIDE * *army_stack + TILE_MAP_OFFSET), (int)(intptr_t)army_stack, a4, a5);
    return 1;
  }
}
// 454ED9: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;

//----- (00454F50) --------------------------------------------------------
signed int  Rules_LinkArmyFact(
        clash95_unaligned_int16 *stack,
        int army_id,
        int a3,
        double a4,
        char a5,
        DWORD a6)
{
  signed int result; // eax
  int stack_record; // ecx
  int fact; // eax
  int value; // ebx
  _DWORD pa_value[6]; // [esp+18h] [ebp-34h] BYREF
  _DWORD x_value[6]; // [esp+0h] [ebp-4Ch] BYREF
  _DWORD y_value[6]; // [esp+30h] [ebp-1Ch] BYREF

  (void)a3;
  stack_record = (int)(uintptr_t)stack;
  result = Rules_EnsureArmyFactForStack(stack, army_id, a4, a5, a6);
  if ( !result )
  {
    result = *(clash95_unaligned_int16 *)((uintptr_t)(unsigned int)stack_record + 6);
    if ( result != -1 )
    {
      fact = *(clash95_unaligned_uint32 *)((uintptr_t)(unsigned int)stack_record + 721);
      Instance_SetModifiedFlag(0);
      pa_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)aPa_2, stack_record, pa_value);
      value = *(_DWORD *)((uintptr_t)(unsigned int)pa_value[2] + 16);
      if ( value != UnitStack_GetMinCurrentActionPoints(stack_record) )
      {
        pa_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(UnitStack_GetMinCurrentActionPoints(stack_record));
        Rules_PutInstanceSlotValue(fact, (_BYTE *)aPa_3, stack_record, pa_value, a4);
      }
      x_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)aXxyy, stack_record, x_value);
      result = *stack;
      if ( *(_DWORD *)((uintptr_t)(unsigned int)x_value[2] + 16) != result )
      {
        x_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(result);
        Rules_PutInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 2), stack_record, x_value, a4);
      }
      y_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 4), stack_record, y_value);
      result = stack[1];
      if ( *(_DWORD *)((uintptr_t)(unsigned int)y_value[2] + 16) != result )
      {
        y_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(result);
        Rules_PutInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 6), stack_record, y_value, a4);
      }
      return Instance_SetModifiedFlag(1);
    }
  }
  return result;
}
// 4FFF84: using guessed type wchar_t aXxyy[4];

//----- (00455070) --------------------------------------------------------
signed int  Rules_SyncArmyFactStrength(
        __int16 *army_stack,
        int army_id,
        int a3,
        char a4,
        DWORD a5,
        double a6)
{
  signed int result; // eax
  int stack_record;
  int fact;
  int previous_strength;
  int current_strength;
  _DWORD moc_value[6];

  (void)a3;
  stack_record = (int)(uintptr_t)army_stack;
  result = Rules_EnsureArmyFactForStack(army_stack, army_id, a6, a4, a5);
  if ( !result )
  {
    result = *(__int16 *)((uintptr_t)(unsigned int)stack_record + 6);
    if ( result != -1 )
    {
      fact = *(_DWORD *)((uintptr_t)(unsigned int)stack_record + 721);
      moc_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE*)(aMoc), stack_record, moc_value);
      previous_strength = *(_DWORD *)((uintptr_t)(unsigned int)moc_value[2] + 16);
      current_strength = UnitStack_CalcArmyFactStrength(stack_record);
      result = current_strength;
      if ( previous_strength != current_strength )
      {
        moc_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(current_strength);
        return Rules_PutInstanceSlotValue(fact, (_BYTE*)(aMoc_0), stack_record, moc_value, a6);
      }
    }
  }
  return result;
}
//----- (004550F0) --------------------------------------------------------
signed int  Rules_SyncArmyFactOwner(
        __int16 *stack_record,
        char a2,
        DWORD a3,
        double a4)
{
  signed int result; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  _DWORD owner_value[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Rules_EnsureArmyFactForStack(stack_record, (int)(intptr_t)stack_record, a4, a2, a3);
  if ( !result )
  {
    result = *(__int16 *)(uintptr_t)(v5 + 6);
    if ( result != -1 )
    {
      owner_value[1] = 1;
      owner_value[2] = Rules_AddIntegerValue(*(unsigned __int8 *)(uintptr_t)(v5 + 4));
      return Rules_PutInstanceSlotValue(*(_DWORD *)(uintptr_t)(v6 + 721), (_BYTE*)(aGracz), v7, owner_value, a4);
    }
  }
  return result;
}
// 4550FF: variable 'v5' is possibly undefined
// 45512A: variable 'v6' is possibly undefined
// 455135: variable 'v7' is possibly undefined

//----- (00455150) --------------------------------------------------------
signed int  Rules_SyncCastleFactOwner(int castle_record, int a2, double a3)
{
  int v5 = 0; // ecx
  int castle_fact; // eax
  int castle_owner; // eax
  int building_table_delta; // edx
  int building_index; // edx
  _DWORD owner_value[9]; // [esp-4h] [ebp-24h] BYREF

  (void)a2;
  owner_value[7] = a2;
  owner_value[1] = 1;
  castle_owner = *(unsigned __int8 *)(uintptr_t)(castle_record + 2);
  owner_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(castle_owner);
  castle_fact = *(_DWORD *)(uintptr_t)(castle_record + 463);
  if ( !castle_fact )
  {
    building_index = -1;
    building_table_delta = castle_record - (gameData + BUILDING_TABLE_OFFSET);
    if ( building_table_delta >= 0 && building_table_delta % BUILDING_RECORD_SIZE == 0 )
    {
      building_index = building_table_delta / BUILDING_RECORD_SIZE;
      if ( (unsigned int)building_index >= 100u )
        building_index = -1;
    }
    Diagnostics_TraceWorldMapActionEvent(
      "rules_sync_castle_fact_missing",
      g_SelectedUnitIndex,
      castle_record,
      building_index,
      castle_owner);
    if ( building_index >= 0 )
    {
      Rules_AssertCastleFact((unsigned __int8 *)(uintptr_t)castle_record, building_index);
      castle_fact = *(_DWORD *)(uintptr_t)(castle_record + 463);
    }
  }
  Diagnostics_TraceWorldMapActionEvent(
    "rules_sync_castle_fact_owner",
    g_SelectedUnitIndex,
    castle_record,
    castle_fact,
    castle_owner);
  if ( !castle_fact )
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  return Rules_PutInstanceSlotValue(castle_fact, (_BYTE*)(aGracz_0), v5, owner_value, a3);
}

//----- (004551A0) --------------------------------------------------------
_DWORD * Rules_LogTrapFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(pulapka %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 4551BC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004551D0) --------------------------------------------------------
_DWORD * Rules_RetractTrapFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(kasuj pulapke %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 4551EC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455200) --------------------------------------------------------
_DWORD * Rules_LogTempleFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(swiatynia %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45521C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455230) --------------------------------------------------------
_DWORD * Rules_LogTreasureFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(skarb %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45524C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455260) --------------------------------------------------------
_DWORD * Rules_RetractTreasureFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(kasuj skarb %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45527C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455290) --------------------------------------------------------
_DWORD * Rules_RetractTempleFact(int tile_x, int tile_y, char a3, DWORD a4)
{
  int v5; // edx
  int v6; // ecx
  double formatted; // st7
  int v8; // ecx
  char fact_text[200]; // [esp+0h] [ebp-CCh] BYREF
  int v11 CLASH95_UNUSED; // [esp+C8h] [ebp-4h]

  v11 = tile_y;
  Debug_Log(tile_x, a3, a4, (int)(intptr_t)aKasuj_swiatyni);
  formatted = sprintf_(fact_text, "(kasuj swiatynie %d %d)", v6, v5);
  return Rules_Log(fact_text, v8, formatted);
}
// 4552B4: variable 'v6' is possibly undefined
// 4552B4: variable 'v5' is possibly undefined
// 4552BE: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004552D0) --------------------------------------------------------
int  Rules_AssertCastleFact(unsigned __int8 *castle_record, int building_index)
{
  char *barracks_text; // eax
  char *smithy_text; // eax
  char *workshop_text; // eax
  char *school_text; // eax
  const char *hospital_text; // eax
  double formatted; // st7
  int v10 = 0; // ecx
  _DWORD *fact; // eax
  const char *school_arg; // [esp-18h] [ebp-400h]
  const char *workshop_arg; // [esp-14h] [ebp-3FCh]
  const char *smithy_arg; // [esp-10h] [ebp-3F8h]
  const char *barracks_arg; // [esp-Ch] [ebp-3F4h]
  int castle_x; // [esp-8h] [ebp-3F0h]
  int castle_y; // [esp-4h] [ebp-3ECh]
  char fact_text[1000]; // [esp+0h] [ebp-3E8h] BYREF

  castle_y = castle_record[1];
  castle_x = *castle_record;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
    barracks_text = aTak;
  else
    barracks_text = aNie;
  barracks_arg = barracks_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_SMITHS) != 0 )
    smithy_text = aTak_0;
  else
    smithy_text = aNie_0;
  smithy_arg = smithy_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
    workshop_text = aTak_1;
  else
    workshop_text = aNie_1;
  workshop_arg = workshop_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
    school_text = aTak_2;
  else
    school_text = aNie_2;
  school_arg = school_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
    hospital_text = aTak_3;
  else
    hospital_text = aNie_3;
  formatted = sprintf_(
         fact_text,
         "( ZAMEK%d of zamek (id %d)(gracz %d)(szpital %s)(szkola %s)(warsztat %s)(kuznia %s)(koszary %s)(x %d)(y %d)(moc 0))",
         building_index,
         building_index,
         castle_record[2],
         hospital_text,
         school_arg,
         workshop_arg,
         smithy_arg,
         barracks_arg,
         castle_x,
         castle_y);
  fact = Rules_AssertFact(fact_text, v10, formatted);
  *(_DWORD *)(castle_record + 463) = (int)(uintptr_t)fact;
  return Building_OnGarrisonChange(building_index, (int)(uintptr_t)castle_record, 0.0);
}
// 455361: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004553A0) --------------------------------------------------------
_DWORD * Rules_RetractCastleFact(unsigned __int8 *castle_record, double a2)
{
  unsigned __int8 *castle_ptr; // edx
  int castle_x; // ecx

  castle_ptr = castle_record;
  if ( *(_DWORD *)(castle_record + 463) )
    Rules_RetractFactById(*(_DWORD *)(castle_record + 463), a2);
  castle_x = *castle_ptr;
  *(_DWORD *)(castle_ptr + 463) = 0;
  return Rules_LogCastleDestroyedFact(castle_ptr[2], *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(castle_x, castle_ptr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
}
// 4553B0: variable 'v2' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455410) --------------------------------------------------------
int Game_GetTurnNumber(void)
{
  return *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00455430) --------------------------------------------------------
_DWORD * Rules_OnCastleUpdate(int building_index, char a2, DWORD a3, double a4)
{
  return Building_Destroy(UNIT_RECORD(building_index), a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00455450) --------------------------------------------------------
BOOL  Building_TryStartUpgradeByIndex(int building_index)
{
  return Building_TryStartUpgrade((unsigned __int8 *)(uintptr_t)(UNIT_RECORD(building_index)));
}
// 5202E4: using guessed type int gameData;

//----- (00455470) --------------------------------------------------------
int  Building_GetTaxRateByIndex(int building_index)
{
  return *(_BYTE *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_TAX_RATE_TABLE_OFFSET) & 0x3F;
}
// 5202E4: using guessed type int gameData;

//----- (00455490) --------------------------------------------------------
signed int  Building_BuildSchoolByIndex(int building_index, char a2, DWORD a3)
{
  return Building_BuildSchool((char *)(uintptr_t)(UNIT_RECORD(building_index)), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004554B0) --------------------------------------------------------
signed int  Building_BuildSmithsByIndex(int building_index, char a2, DWORD a3)
{
  /* 004554B0: `imul eax,1D3h; mov edx,gameData; add edx,7C6EAh; add eax,edx;
     call sub_41F020` - the wrapper turns the building INDEX into the record
     pointer, exactly like Building_BuildSchoolByIndex.  IDA's signature lost
     the index entirely. */
  return Building_BuildSmiths(BUILDING_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004554D0) --------------------------------------------------------
int  Building_GetWallStrengthByIndex(int building_index)
{
  return *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_WALL_STRENGTH_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (004554F0) --------------------------------------------------------
int  Building_GetMoneyByIndex(int building_index)
{
  return *(_DWORD *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_STORED_MONEY_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00455510) --------------------------------------------------------
int  Building_GetCastleStrengthByIndex(int building_index)
{
  return Building_GetTotalValue(UNIT_RECORD(building_index));
}
// 5202E4: using guessed type int gameData;

//----- (00455530) --------------------------------------------------------
signed int  Building_BuildBarracksByIndex(int building_index, char a2, DWORD a3)
{
  /* sub_455530: `imul eax,1D3h; mov edx, gameData; add edx,7C6EAh; add eax,edx`
     - the wrapper converts the index into a building-record pointer before the
     call; the recovery forwarded the raw index. */
  return Building_BuildBarracks(BUILDING_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455550) --------------------------------------------------------
signed int  Building_BuildHospitalByIndex(int building_index, char a1, DWORD a2)
{
  /* sub_455550: same index -> building-record conversion as sub_455530. */
  return Building_BuildHospital(BUILDING_RECORD(building_index), a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (00455580) --------------------------------------------------------
int  Building_GetTechLevelByIndex(int building_index)
{
  return *(_BYTE *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_TECH_LEVEL_BITS_TABLE_OFFSET) & 7;
}
// 5202E4: using guessed type int gameData;

//----- (004555A0) --------------------------------------------------------
int  Building_GetTypeByIndex(int building_index)
{
  return *(char *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_FOOTPRINT_CLASS_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (004555C0) --------------------------------------------------------
signed int  Building_BuildWorkshopByIndex(int building_index, char a1, DWORD a2)
{
  /* sub_4555C0: same index -> building-record conversion as sub_455530. */
  return Building_BuildWorkshop(BUILDING_RECORD(building_index), a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (004555E0) --------------------------------------------------------
int  Building_GetSatisfactionByIndex(int building_index)
{
  return *(char *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_SATISFACTION_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00455600) --------------------------------------------------------
int  Building_GetPeasantCountByIndex(int building_index)
{
  int result; // eax

  LOWORD(result) = *(_WORD *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_PEASANT_COUNT_TABLE_OFFSET);
  BYTE1(result) &= 0xFu;
  return (unsigned __int16)result;
}
// 5202E4: using guessed type int gameData;

//----- (00455620) --------------------------------------------------------
BOOL  Building_HasProductionByIndex(int building_index)
{
  return *(char *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX_TABLE_OFFSET) != -1;
}
// 5202E4: using guessed type int gameData;

//----- (00455650) --------------------------------------------------------
BOOL  Building_CanStartUpgradeByIndex(int building_index)
{
  return Building_CanStartUpgrade((unsigned __int8 *)(uintptr_t)(UNIT_RECORD(building_index)));
}
// 5202E4: using guessed type int gameData;

//----- (00455670) --------------------------------------------------------
int  Building_GetGarrisonCountByIndex(int building_index)
{
  return Building_CountGarrison(UNIT_RECORD(building_index));
}
// 5202E4: using guessed type int gameData;

//----- (00455690) --------------------------------------------------------
BOOL  Building_IsGarrisonFullByIndex(int building_index)
{
  return Building_CountGarrison(UNIT_RECORD(building_index)) == BUILDING_GARRISON_SLOT_COUNT;
}
// 5202E4: using guessed type int gameData;

//----- (004556C0) --------------------------------------------------------
__int16  Building_RepairUnitByIndex(int building_index, int slot_index, DWORD a3)
{
  return Building_RepairUnit(UNIT_RECORD(building_index), slot_index, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004556E0) --------------------------------------------------------
_BYTE * Building_TrainUnitByIndex(int building_index, char a2, DWORD a3)
{
  return Building_TrainUnit(UNIT_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455700) --------------------------------------------------------
int  Building_SetUnitProductionByIndex(int building_index, char a2, DWORD a3)
{
  return Building_SetUnitProduction(UNIT_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455720) --------------------------------------------------------
int  Building_RemoveUnitLicenceByIndex(int building_index, unit_type licence_type, DWORD a3)
{
  return Building_RemoveUnitLicence(UNIT_RECORD(building_index), licence_type, a3);
}
// 5202E4: using guessed type int gameData;
