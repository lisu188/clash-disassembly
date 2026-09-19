BOOL  UnitSlot_CanRecoverFatigue(int slotPtr)
{
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return (slot->state_flags & UNIT_SLOT_FLAG_SPENT_TURN) == 0;
}
