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
