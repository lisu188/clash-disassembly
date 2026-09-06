signed int  UnitStack_HasBuilder(int stackIndex)
{
  __int16 *slotPtr; // edx
  int slotIndex; // eax
  int slotType; // ecx

  slotPtr = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  slotIndex = 0;
  while ( 1 )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_BUILDER )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}
