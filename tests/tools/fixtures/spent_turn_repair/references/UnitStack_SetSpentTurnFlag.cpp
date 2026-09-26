__int16 * UnitStack_SetSpentTurnFlag(int stackPtr)
{
  UnitStackRecord *stack;
  UnitSlotRecord *slot;
  int slotIndex;

  stack = (UnitStackRecord *)(uintptr_t)stackPtr;
  slot = &stack->unit_slots[0];
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    if ( slot->unit_type_id == -1 )
      break;
    slot->state_flags |= UNIT_SLOT_FLAG_SPENT_TURN;
    ++slot;
  }
  return (__int16 *)(uintptr_t)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * slotIndex);
}
