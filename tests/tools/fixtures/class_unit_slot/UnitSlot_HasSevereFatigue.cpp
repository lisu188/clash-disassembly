BOOL  UnitSlot_HasSevereFatigue(int slotPtr)
{
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return (int8_t)slot->fatigue >= 80;
}
