int  UnitStack_SpendActionPointsUnchecked(int stackPtr, char spendAmount)
{
  unsigned int slotPtr; // eax
  int slotIndex; // edx

  slotPtr = (unsigned int)stackPtr + 6u;
  slotIndex = 0;
  while ( slotIndex < UNIT_STACK_SLOT_COUNT )
  {
    if ( *(clash95_unaligned_int16 *)(uintptr_t)slotPtr == -1 )
      break;
    UNIT_SLOT_ACTION_POINTS(slotPtr) -= spendAmount;
    slotPtr += UNIT_SLOT_RECORD_BYTES;
    ++slotIndex;
  }
  return (int)slotPtr;
}
