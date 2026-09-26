signed int  UnitStack_HasSpecialPersonageUnits(intptr_t stackPtr)
{
  UnitStackRecord *stack;
  int slotIndex;

  stack = (UnitStackRecord *)stackPtr;
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    int slotType = stack->unit_slots[slotIndex].unit_type_id;
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      return 1;
  }
  return 0;
}
