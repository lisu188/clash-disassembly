/* Canonical class implementations; original identities are mapped in recovered_sources.json. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "units_shared_state.h"
#include "../strategic/strategic_api.h"
#include "../recovered_legacy_imports.h"
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

signed int clash95::UnitStack::UnitStack_NormalizePeasantCargo(DWORD a2, double a3) const
{
  __int16 *stackPtr = (__int16 *)(uintptr_t)address_;
  typedef __int16 SlotTypeWord __attribute__((aligned(1), may_alias));
  SlotTypeWord *slotPtr; // ecx
  int totalPeasantQuantity; // esi
  int peasantSlotCount; // edx
  int i; // ebx
  int slotType; // eax
  int consolidationThreshold;
  int j; // ecx
  SlotTypeWord *clearCursor; // ecx
  int clearIndex; // eax
  SlotTypeWord *clearSlotPtr; // ebx
  signed int squadCount; // edi
  int fullCargoUnits; // eax
  int addedIndex; // ebx
  int v18; // ebp
  char minActionPoints; // [esp+4h] [ebp-18h]

  slotPtr = (SlotTypeWord *)((char *)stackPtr + 6);
  totalPeasantQuantity = 0;
  peasantSlotCount = 0;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++peasantSlotCount;
      totalPeasantQuantity += *((int8_t *)slotPtr + 9);
    }
    slotPtr = (SlotTypeWord *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
  }
  // 0x412201 preserves this EDX threshold across the AP query.
  consolidationThreshold = (peasantSlotCount - 1) * 100;
  minActionPoints = this->UnitStack_GetMinCurrentActionPoints();
  if ( consolidationThreshold > totalPeasantQuantity )
  {
    clearCursor = (SlotTypeWord *)stackPtr;
    clearIndex = 0;
    clearSlotPtr = (SlotTypeWord *)((char *)stackPtr + 6);
    do
    {
      if ( *clearSlotPtr == -1 )
        break;
      if ( clearCursor[3] == UNIT_TYPE_PEASANT_CARGO )
        clearCursor[3] = -1;
      clearCursor = (SlotTypeWord *)((char *)clearCursor + UNIT_SLOT_RECORD_BYTES);
      ++clearIndex;
      clearSlotPtr = (SlotTypeWord *)((char *)clearSlotPtr + UNIT_SLOT_RECORD_BYTES);
    }
    while ( clearIndex < UNIT_STACK_SLOT_COUNT );
    Unit_CompactSquad(stackPtr, (int)(intptr_t)clearCursor, a3);
    squadCount = Unit_GetSquadCount((int)(intptr_t)stackPtr);
    fullCargoUnits = totalPeasantQuantity / 100;
    addedIndex = 0;
    for ( j = (int)(intptr_t)stackPtr + UNIT_SLOT_RECORD_BYTES * squadCount; ; *(_BYTE *)(uintptr_t)(j - 17) = minActionPoints )
    {
      v18 = addedIndex + squadCount;
      if ( addedIndex >= fullCargoUnits )
        break;
      j += UNIT_SLOT_RECORD_BYTES;
      *(SlotTypeWord *)(uintptr_t)(j - 25) = UNIT_TYPE_PEASANT_CARGO;
      *(_BYTE *)(uintptr_t)(j - 16) = 100;
      *(_BYTE *)(uintptr_t)(j - 15) = 0;
      *(_BYTE *)(uintptr_t)(j - 14) = 10;
      ++addedIndex;
    }
    LOBYTE(i) = 100;
    *(_BYTE *)(uintptr_t)(j + 14) = minActionPoints;
    *(SlotTypeWord *)(uintptr_t)(j + 6) = UNIT_TYPE_PEASANT_CARGO;
    *(_BYTE *)(uintptr_t)(j + 15) = totalPeasantQuantity % 100;
    *(_BYTE *)(uintptr_t)(j + 16) = 0;
    a2 = (DWORD)(intptr_t)stackPtr + UNIT_SLOT_RECORD_BYTES * v18 + UNIT_SLOT_RECORD_BYTES;
    *(_BYTE *)(uintptr_t)(j + 17) = 10;
    *(SlotTypeWord *)(uintptr_t)(a2 + 6) = -1;
  }
  // The reviewed ensure/retract path ignores these incoming EDX/ECX slots.
  return Rules_SyncArmyFactStrength(stackPtr, 0, 0, i, a2, a3);
}

signed int clash95::UnitStack::UnitStack_HasPlague() const
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
    if ( (slot->state_flags & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      return 1;
  }
  return 0;
}

signed int clash95::UnitStack::UnitStack_HasLowMoraleUnit() const
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
    if ( (slot->state_flags & UNIT_SLOT_FLAG_LOW_MORALE) != 0 )
      return 1;
  }
  return 0;
}

int clash95::UnitStack::UnitStack_CalcMilitaryStrength() const
{
  int stackPtr = (int)address_;
  signed int squadCount; // eax

  squadCount = Unit_GetSquadCount(stackPtr);
  // 0x412BE3 retains the input in EDX; the LEA at 0x412BEA wraps at 32 bits.
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)(uintptr_t)((uint32_t)stackPtr + 6u), squadCount, 0);
}
