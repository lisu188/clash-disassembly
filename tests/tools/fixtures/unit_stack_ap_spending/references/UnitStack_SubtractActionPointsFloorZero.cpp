signed int  UnitStack_SubtractActionPointsFloorZero(__int16 *stackPtr, int subtractAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // edx
  int currentActionPoints; // ebx

  slotPtr = stackPtr + 3;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    currentActionPoints = *(clash95_unaligned_int16 *)slotPtr;
    if ( currentActionPoints == -1 )
      break;
    currentActionPoints = *((unsigned __int8 *)slotPtr + 8);
    if ( currentActionPoints <= subtractAmount )
    {
      *((_BYTE *)slotPtr + 8) = 0;
    }
    else
    {
      LOBYTE(currentActionPoints) = (unsigned int)currentActionPoints - (unsigned int)subtractAmount;
      *((_BYTE *)slotPtr + 8) = currentActionPoints;
    }
    slotPtr = (__int16 *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
  }
  return Rules_LinkArmyFact(stackPtr, i, subtractAmount, a4, currentActionPoints, a3);
}
