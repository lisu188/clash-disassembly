BOOL  UnitSlot_ShouldGainFatigueFromLowActionPoints(int slotPtr)
{
  UnitSlotRecord *slot = (UnitSlotRecord *)(uintptr_t)slotPtr;
  return slot->current_action_points <= 3u && (slot->state_flags & UNIT_SLOT_FLAG_LOW_MORALE) == 0;
}
