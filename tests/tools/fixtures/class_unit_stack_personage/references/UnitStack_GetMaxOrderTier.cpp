signed int  UnitStack_GetMaxOrderTier(intptr_t stackPtr)
{
  intptr_t slot_record; // eax
  int max_order_tier; // ebx
  int i; // edx

  if ( UnitStack_HasSpecialPersonageUnits(stackPtr) )
    return 3;
  slot_record = stackPtr;
  max_order_tier = 0;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    if ( *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
      break;
    if ( (*(_BYTE *)(slot_record + 18) & 3) > max_order_tier )
      max_order_tier = *(_BYTE *)(slot_record + 18) & 3;
    slot_record += UNIT_STACK_SLOT_STRIDE;
  }
  return max_order_tier;
}
