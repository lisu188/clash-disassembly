signed int  UnitStack_NormalizePeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  typedef __int16 SlotTypeWord __attribute__((aligned(1), may_alias));
  SlotTypeWord *slotPtr; // ecx
  int totalPeasantQuantity; // esi
  int peasantSlotCount; // edx
  int i; // ebx
  int slotType; // eax
  int consolidationThreshold;
  int j; // ecx
  SlotTypeWord *clearCursor; // ecx
  int clearIndex; // eax
  SlotTypeWord *clearSlotPtr; // ebx
  signed int squadCount; // edi
  int fullCargoUnits; // eax
  int addedIndex; // ebx
  int v18; // ebp
  char minActionPoints; // [esp+4h] [ebp-18h]

  slotPtr = (SlotTypeWord *)((char *)stackPtr + 6);
  totalPeasantQuantity = 0;
  peasantSlotCount = 0;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++peasantSlotCount;
      totalPeasantQuantity += *((int8_t *)slotPtr + 9);
    }
    slotPtr = (SlotTypeWord *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
  }
  // 0x412201 preserves this EDX threshold across the AP query.
  consolidationThreshold = (peasantSlotCount - 1) * 100;
  minActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
  if ( consolidationThreshold > totalPeasantQuantity )
  {
    clearCursor = (SlotTypeWord *)stackPtr;
    clearIndex = 0;
    clearSlotPtr = (SlotTypeWord *)((char *)stackPtr + 6);
    do
    {
      if ( *clearSlotPtr == -1 )
        break;
      if ( clearCursor[3] == UNIT_TYPE_PEASANT_CARGO )
        clearCursor[3] = -1;
      clearCursor = (SlotTypeWord *)((char *)clearCursor + UNIT_SLOT_RECORD_BYTES);
      ++clearIndex;
      clearSlotPtr = (SlotTypeWord *)((char *)clearSlotPtr + UNIT_SLOT_RECORD_BYTES);
    }
    while ( clearIndex < UNIT_STACK_SLOT_COUNT );
    Unit_CompactSquad(stackPtr, (int)(intptr_t)clearCursor, a3);
    squadCount = Unit_GetSquadCount((int)(intptr_t)stackPtr);
    fullCargoUnits = totalPeasantQuantity / 100;
    addedIndex = 0;
    for ( j = (int)(intptr_t)stackPtr + UNIT_SLOT_RECORD_BYTES * squadCount; ; *(_BYTE *)(uintptr_t)(j - 17) = minActionPoints )
    {
      v18 = addedIndex + squadCount;
      if ( addedIndex >= fullCargoUnits )
        break;
      j += UNIT_SLOT_RECORD_BYTES;
      *(SlotTypeWord *)(uintptr_t)(j - 25) = UNIT_TYPE_PEASANT_CARGO;
      *(_BYTE *)(uintptr_t)(j - 16) = 100;
      *(_BYTE *)(uintptr_t)(j - 15) = 0;
      *(_BYTE *)(uintptr_t)(j - 14) = 10;
      ++addedIndex;
    }
    LOBYTE(i) = 100;
    *(_BYTE *)(uintptr_t)(j + 14) = minActionPoints;
    *(SlotTypeWord *)(uintptr_t)(j + 6) = UNIT_TYPE_PEASANT_CARGO;
    *(_BYTE *)(uintptr_t)(j + 15) = totalPeasantQuantity % 100;
    *(_BYTE *)(uintptr_t)(j + 16) = 0;
    a2 = (DWORD)(intptr_t)stackPtr + UNIT_SLOT_RECORD_BYTES * v18 + UNIT_SLOT_RECORD_BYTES;
    *(_BYTE *)(uintptr_t)(j + 17) = 10;
    *(SlotTypeWord *)(uintptr_t)(a2 + 6) = -1;
  }
  // The reviewed ensure/retract path ignores these incoming EDX/ECX slots.
  return Rules_SyncArmyFactStrength(stackPtr, 0, 0, i, a2, a3);
}
