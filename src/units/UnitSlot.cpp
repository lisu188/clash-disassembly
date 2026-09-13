/* Canonical class implementations; original identities are mapped in recovered_sources.json. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../units/UnitSlot.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

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
