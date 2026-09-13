signed int  UnitStack_HasPlague(int stackPtr)
{
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
