/* Canonical class implementations; original identities are mapped in recovered_sources.json. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../units/UnitStack.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

signed int clash95::UnitStack::UnitStack_HasReadyUnits() const
{
  int stackPtr = (int)address_;
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

signed int clash95::UnitStack::UnitStack_GetMinCurrentActionPoints() const
{
  intptr_t stackPtr = address_;
  typedef __int16 SlotTypeWord __attribute__((aligned(1), may_alias));
  SlotTypeWord *slotPtr; // eax
  int slotIndex; // edx
  int minActionPoints; // ebx

  slotPtr = (SlotTypeWord *)(stackPtr + 37);
  slotIndex = 1;
  minActionPoints = *((unsigned __int8 *)slotPtr - 23);
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( minActionPoints > *((unsigned __int8 *)slotPtr + 8) )
      minActionPoints = *((unsigned __int8 *)slotPtr + 8);
    ++slotIndex;
    slotPtr = (SlotTypeWord *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
  }
  while ( slotIndex < UNIT_STACK_SLOT_COUNT );
  return minActionPoints;
}

signed int clash95::UnitStack::UnitStack_HasBuilder() const
{
  typedef __int16 SlotTypeWord __attribute__((aligned(1), may_alias));
  SlotTypeWord *slotPtr; // edx
  int slotIndex; // eax
  int slotType; // ecx

  slotPtr = (SlotTypeWord *)(uintptr_t)(address_ + 6);
  slotIndex = 0;
  while ( 1 )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_BUILDER )
      break;
    ++slotIndex;
    slotPtr = (SlotTypeWord *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
    if ( slotIndex >= UNIT_STACK_SLOT_COUNT )
      return 0;
  }
  return 1;
}
