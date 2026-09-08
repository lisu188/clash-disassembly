// Relocated recovered methods; ABI adapters and storage remain in their original translation units.
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "units_shared_state.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../units/UnitStack.hpp"
#include "../units/UnitTurn.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

_BYTE * clash95::UnitTurn::Unit_NewTurnRegen(_BYTE *result)
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

int clash95::UnitTurn::Unit_UpdatePerTurn(int buildingPtr, int a2)
{
  typedef _WORD PackedWord __attribute__((aligned(1), may_alias));
  __int16 currentHitPoints; // dx
  unsigned __int16 maxHitPoints; // cx
  int damagePercent; // eax
  int damageUpper; // esi
  int damageLower; // ebx
  int result; // eax
  int slotWalker; // ecx
  char rolledDamage; // dl

  (void)a2;
  currentHitPoints = *(PackedWord *)(uintptr_t)(buildingPtr + 16);
  if ( !currentHitPoints )
  {
    memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 100, 7);
    return buildingPtr + 422;
  }
  maxHitPoints = this->state_field_1_[*(char *)(uintptr_t)(buildingPtr + 4)];
  damagePercent = 100 * (maxHitPoints - currentHitPoints) / maxHitPoints;
  damageUpper = damagePercent + 10;
  damageLower = damagePercent - 10;
  slotWalker = buildingPtr;
  do
  {
    result = ::Rng_RandRange(damageLower, damageUpper);
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

signed int clash95::UnitTurn::Unit_NewTurn(int a1, char a2, DWORD a3, double a4)
{
  typedef __int16 PackedInt16 __attribute__((aligned(1), may_alias));
  typedef _WORD PackedWord __attribute__((aligned(1), may_alias));
  typedef _DWORD PackedDword __attribute__((aligned(1), may_alias));
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

  ::Debug_Log(a1, a2, a3, (int)(intptr_t)this->state_field_0_);
  ::Diagnostics_TraceWorldMapActionEvent("unit_new_turn_enter", this->state_field_3_, this->state_field_2_, (*(PackedWord *)(uintptr_t)(this->state_field_4_ + 140022)), (unsigned __int8)a2);
  stackIndex = 0;
  for ( i = 0; ; i += UNIT_STACK_STRIDE )
  {
    if ( *(PackedInt16 *)(uintptr_t)(this->state_field_4_ + i + UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET) == -1 || *(unsigned __int8 *)(uintptr_t)(this->state_field_4_ + i + UNIT_STACK_OWNER_PLAYER_INDEX_TABLE_OFFSET) != this->state_field_2_ )
      goto LABEL_16;
    stackPtr = this->state_field_4_ + UNIT_STACK_TABLE_OFFSET + i;
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_stack",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
    ::UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, -20, ::UnitSlot_CanRecoverFatigue, 0xFFFFFFFF, a4);
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_recover_fatigue",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
    if ( *(PackedDword *)(uintptr_t)(this->state_field_4_ + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(stackPtr + 4) + 140051) )
    {
      ::UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, 10, ::UnitSlot_ShouldGainFatigueFromLowActionPoints, 0xFFFFFFFF, a4);
      ::UnitStack_AdjustMoraleByPredicate((__int16 *)(uintptr_t)stackPtr, -1, ::UnitSlot_HasSevereFatigue, 0xFFFFFFFF, a4);
    }
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_human_fatigue",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
    ::UnitStack_ClearSpentTurnFlag(stackPtr);
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_clear_spent",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
    slotIndex = 0;
    slotCursor = stackPtr;
    do
    {
      slotType = *(PackedInt16 *)(uintptr_t)(slotCursor + 6);
      if ( slotType == -1 )
        break;
      if ( slotType < 0 || slotType >= UNIT_TYPE_COUNT )
      {
        *(PackedWord *)(uintptr_t)(slotCursor + 6) = -1;
        break;
      }
      slotCursor += UNIT_SLOT_RECORD_BYTES;
      actionPoints = ::UnitSlot_CalcActionPointsFromFatigue((__int16 *)(uintptr_t)(stackPtr + 6 + UNIT_SLOT_RECORD_BYTES * slotIndex++));
      *(_BYTE *)(uintptr_t)(slotCursor - 17) = actionPoints;
    }
    while ( slotIndex < UNIT_STACK_SLOT_COUNT );
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ap",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    ::Rules_LinkArmyFact((__int16 *)(uintptr_t)stackPtr, slotCursor, slotType, a4, slotIndex, 0xFFFFFFFF);
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_rules_fact",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    ::Unit_CheckLowMorale((_BYTE *)(uintptr_t)stackPtr, a4);
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_low_morale",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    ::UnitStack_ApplyPlagueAttritionToPeasantCargo((__int16 *)(uintptr_t)stackPtr, 0xFFFFFFFF, a4);
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_plague",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    if ( !clash95::UnitStack(stackPtr).UnitStack_HasReadyUnits() )
      goto LABEL_16;
    ::Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ready_check",
      (int)stackIndex,
      *(PackedInt16 *)(uintptr_t)stackPtr,
      *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    buildingIndex = *(PackedWord *)(uintptr_t)(this->state_field_4_
                             + TILE_ROW_STRIDE * (unsigned __int8)*(PackedDword *)(uintptr_t)(stackPtr + 320)
                             + 2 * (unsigned __int8)BYTE1(*(PackedDword *)(uintptr_t)(stackPtr + 320))
                             + TILE_MAP_OFFSET)
       - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( buildingIndex <= 0x64 )
    {
      slotIndex = BUILDING_RECORD_SIZE * buildingIndex;
      buildingRecord = (this->state_field_4_ + 509674 + 467 * (buildingIndex));
      if ( (unsigned int)*(char *)(uintptr_t)(buildingRecord + 4) < 4
        && *(PackedInt16 *)(uintptr_t)(buildingRecord + 16) != -1
        && *(_BYTE *)(uintptr_t)(slotIndex + this->state_field_4_ + BUILDING_OWNER_PLAYER_INDEX_TABLE_OFFSET) != UNIT_STACK_OWNER_INDEX(stackPtr) )
      {
        break;
      }
    }
    if ( *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET) )
    {
      ::Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_before_path",
        (int)stackIndex,
        *(PackedInt16 *)(uintptr_t)stackPtr,
        *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
        *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
      ::UnitStack_ExecuteQueuedPath(stackIndex, 0, slotIndex, 0xFFFFFFFF, a4);
      ::Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_after_path",
        (int)stackIndex,
        *(PackedInt16 *)(uintptr_t)stackPtr,
        *(PackedInt16 *)(uintptr_t)(stackPtr + 2),
        *(PackedDword *)(uintptr_t)(stackPtr + UNIT_STACK_PATH_OFFSET));
    }
    else
      ::UnitStack_ClearReadyFlags(stackPtr);
LABEL_16:
    nextStackOffset = i + UNIT_STACK_STRIDE;
    slotIndex = stackIndex + 1;
    stackIndex = slotIndex;
    if ( slotIndex >= UNIT_STACK_TABLE_COUNT )
    {
      ::Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done", this->state_field_3_, this->state_field_2_, (*(PackedWord *)(uintptr_t)(this->state_field_4_ + 140022)), (unsigned __int8)a2);
      return ::LogAllUnits(nextStackOffset, slotIndex, 0xFFFFFFFF);
    }
  }
  ::UnitStack_ClearReadyFlags(stackPtr);
  ::Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done_enemy_contact", (int)stackIndex, *(PackedInt16 *)(uintptr_t)stackPtr, *(PackedInt16 *)(uintptr_t)(stackPtr + 2), slotIndex);
  return ::LogAllUnits(0, slotIndex, 0xFFFFFFFF);
}
