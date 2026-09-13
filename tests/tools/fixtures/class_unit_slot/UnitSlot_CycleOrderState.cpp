int  UnitSlot_CycleOrderState(int result)
{
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
