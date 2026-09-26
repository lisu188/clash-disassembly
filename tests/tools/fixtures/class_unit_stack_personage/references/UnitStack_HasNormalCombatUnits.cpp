signed int  UnitStack_HasNormalCombatUnits(intptr_t stackPtr)
{
  signed int result; // eax
  intptr_t slot_record; // edx
  signed int squad_count; // esi
  signed int has_normal_unit; // ebx
  signed int slot_index; // ecx
  int unit_type; // eax

  if ( *(__int16 *)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
    return 0;
  result = Unit_GetSquadCount(stackPtr);
  squad_count = result;
  if ( result )
  {
    slot_record = stackPtr;
    has_normal_unit = 0;
    slot_index = 0;
    if ( result > 0 )
    {
      while ( !has_normal_unit )
      {
        unit_type = *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET);
        if ( unit_type == UNIT_TYPE_GOLD_CARGO
          || unit_type == UNIT_TYPE_PEASANT_CARGO
          || unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          || unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return has_normal_unit;
        }
        else
        {
          has_normal_unit = 1;
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return 1;
        }
      }
    }
    return has_normal_unit;
  }
  return result;
}
