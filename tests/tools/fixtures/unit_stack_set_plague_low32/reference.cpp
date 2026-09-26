int  UnitStack_SetPlagueFlag(int result)
{
  UnitStackRecord *stack;
  UnitSlotRecord *slot;
  int slotIndex;

  stack = (UnitStackRecord *)(uintptr_t)(uint32_t)result;
  slot = &stack->unit_slots[0];
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    if ( slot->unit_type_id == -1 )
      break;
    slot->state_flags |= UNIT_SLOT_FLAG_PLAGUE;
    ++slot;
  }
  return (int)((uint32_t)(uintptr_t)slot - UNIT_STACK_SLOT_BASE_OFFSET);
}
