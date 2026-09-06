signed int  UnitStack_GetMinCurrentActionPoints(intptr_t stackPtr)
{
  __int16 *slotPtr; // eax
  int slotIndex; // edx
  int minActionPoints; // ebx

  slotPtr = (__int16 *)(stackPtr + 37);
  slotIndex = 1;
  minActionPoints = *((unsigned __int8 *)slotPtr - 23);
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( minActionPoints > *((unsigned __int8 *)slotPtr + 8) )
      minActionPoints = *((unsigned __int8 *)slotPtr + 8);
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  while ( slotIndex < 10 );
  return minActionPoints;
}
