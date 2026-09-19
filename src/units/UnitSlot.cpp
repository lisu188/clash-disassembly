/* Canonical class implementations; original identities are mapped in recovered_sources.json. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../state/state_api.h"
#include "../units/UnitSlot.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

int clash95::UnitSlot::UnitSlot_CalcActionPointsFromFatigue() const
{
  __int16 *slotPtr = (__int16 *)address_;
  UnitSlotRecord *slot;
  int unitType;
  int fatigueLevel;
  int result;

  slot = (UnitSlotRecord *)slotPtr;
  unitType = slot->unit_type_id;
  if ( unitType < 0 || unitType >= UNIT_TYPE_COUNT )
    return 0;
  fatigueLevel = slot->fatigue;
  result = (unsigned __int8)UnitSlot_BorrowTypeMetadata()[unitType].base_action_points;
  if ( fatigueLevel >= 80 && fatigueLevel <= 89 )
    return (192 * result - (__CFSHL__((192 * result) >> 31, 8) + ((192 * result) >> 31 << 8))) >> 8;
  if ( fatigueLevel >= 90 && fatigueLevel <= 99 )
    return ((result << 7) - (__CFSHL__(result << 7 >> 31, 8) + (result << 7 >> 31 << 8))) >> 8;
  if ( fatigueLevel == 100 )
    return 0;
  return result;
}

int clash95::UnitSlot::UnitSlot_GetBaseActionPoints() const
{
  typedef __int16 SlotTypeWord __attribute__((aligned(1), may_alias));
  SlotTypeWord *slotPtr = (SlotTypeWord *)address_;
  return (unsigned __int8)UnitSlot_BorrowTypeMetadata()[*slotPtr].base_action_points;
}









BOOL clash95::UnitSlot::UnitSlot_ShouldGainFatigueFromLowActionPoints() const
{
  int slotPtr = (int)address_;
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return slot->current_action_points <= 3u && (slot->state_flags & UNIT_SLOT_FLAG_LOW_MORALE) == 0;
}

BOOL clash95::UnitSlot::UnitSlot_CanRecoverFatigue() const
{
  int slotPtr = (int)address_;
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return (slot->state_flags & UNIT_SLOT_FLAG_SPENT_TURN) == 0;
}

BOOL clash95::UnitSlot::UnitSlot_HasSevereFatigue() const
{
  int slotPtr = (int)address_;
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return (int8_t)slot->fatigue >= 80;
}

int clash95::UnitSlot::UnitSlot_CycleOrderState() const
{
  int result = (int)address_;
  UnitSlotRecord *slot;
  char nextOrderState;
  char clearedFlags;
  char updatedFlags;

  slot = (UnitSlotRecord *)(uintptr_t)result;
  nextOrderState = ((slot->stance_bits >> 2) + 1) & 3;
  clearedFlags = slot->stance_bits & 0xF3;
  slot->stance_bits = clearedFlags;
  updatedFlags = (4 * nextOrderState) | clearedFlags;
  slot->stance_bits = updatedFlags;
  if ( (unsigned __int8)((unsigned __int8)(16 * updatedFlags) >> 6) > 2u )
  {
    slot->stance_bits = updatedFlags & 0xF3;
    if ( (clearedFlags & 3u) < 3 )
    {
      slot->stance_bits = updatedFlags & 0xF0;
      slot->stance_bits = ((clearedFlags & 3) + 1) & 3 | ((4 * nextOrderState) | clearedFlags) & 0xF0;
    }
  }
  return result;
}

int clash95::UnitSlot::UnitSlot_InitFromType(unit_type unitType, char ownerIndex) const
{
  int result = (int)address_;
  char moraleValue; // dl
  char stanceBits; // bh
  char auxFlagsByte; // cl
  char stateBitsByte; // dl
  char flagsByte; // ch

  *(clash95_unaligned_int16 *)(uintptr_t)(result + 4) = 0;
  *(clash95_unaligned_int16 *)(uintptr_t)(result + 6) = 0;
  *(_BYTE *)(uintptr_t)(result + 3) = 0;
  *(clash95_unaligned_uint32 *)(uintptr_t)(result + 23) = 0;
  *(clash95_unaligned_int16 *)(uintptr_t)result = unitType;
  UNIT_SLOT_OWNER(result) = ownerIndex;
  if ( unitType != -1 )
    UNIT_SLOT_ACTION_POINTS(result) = UnitSlot_BorrowTypeMetadata()[unitType].base_action_points;
  UNIT_SLOT_HEALTH_PERCENT(result) = 100;
  if ( unitType != -1 )
  {
    if ( (UnitSlot_BorrowTypeMetadata()[unitType].flags & 2) != 0 )
      moraleValue = 6;
    else
      moraleValue = 10;
    UNIT_SLOT_MORALE(result) = moraleValue;
  }
  UNIT_SLOT_FATIGUE(result) = 0;
  stanceBits = UNIT_SLOT_STANCE_BITS(result);
  *(clash95_unaligned_uint32 *)(uintptr_t)(result + 18) = 0;
  auxFlagsByte = *(_BYTE *)(uintptr_t)(result + 17);
  UNIT_SLOT_STANCE_BITS(result) = stanceBits & 0x80;
  stateBitsByte = UNIT_SLOT_STATE_BITS(result);
  *(_BYTE *)(uintptr_t)(result + 17) = auxFlagsByte & 0xF8;
  flagsByte = UNIT_SLOT_FLAGS(result);
  UNIT_SLOT_STATE_BITS(result) = stateBitsByte & 0xFE;
  UNIT_SLOT_FLAGS(result) = flagsByte & 0xF0;
  return result;
}
