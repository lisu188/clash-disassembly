signed int  UnitStack_SpendActionPointsClamped(__int16 *stackPtr, int spendAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // ecx
  int slotType; // ebx
  char currentActionPoints; // bl

  slotPtr = stackPtr + 3;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    slotType = *(clash95_unaligned_int16 *)slotPtr;
    if ( slotType == -1 )
      break;
    if ( *((unsigned __int8 *)slotPtr + 8) < spendAmount )
      spendAmount = *((unsigned __int8 *)slotPtr + 8);
    currentActionPoints = *((_BYTE *)slotPtr + 8);
    slotPtr = (__int16 *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
    LOBYTE(slotType) = (unsigned int)(unsigned __int8)currentActionPoints - (unsigned int)spendAmount;
    *((_BYTE *)slotPtr - 23) = slotType;
  }
  return Rules_LinkArmyFact(stackPtr, spendAmount, i, a4, slotType, a3);
}
