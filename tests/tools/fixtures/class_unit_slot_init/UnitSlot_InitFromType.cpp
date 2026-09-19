int  UnitSlot_InitFromType(int result, unit_type unitType, char ownerIndex)
{
  char moraleValue; // dl
  char stanceBits; // bh
  char auxFlagsByte; // cl
  char stateBitsByte; // dl
  char flagsByte; // ch

  *(_WORD *)(uintptr_t)(result + 4) = 0;
  *(_WORD *)(uintptr_t)(result + 6) = 0;
  *(_BYTE *)(uintptr_t)(result + 3) = 0;
  *(_DWORD *)(uintptr_t)(result + 23) = 0;
  UNIT_SLOT_TYPE(result) = unitType;
  UNIT_SLOT_OWNER(result) = ownerIndex;
  if ( unitType != -1 )
    UNIT_SLOT_ACTION_POINTS(result) = g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unitType];
  UNIT_SLOT_HEALTH_PERCENT(result) = 100;
  if ( unitType != -1 )
  {
    if ( (g_UnitTypeFlags[UNIT_TYPE_METADATA_DWORD_STRIDE * unitType] & 2) != 0 )
      moraleValue = 6;
    else
      moraleValue = 10;
    UNIT_SLOT_MORALE(result) = moraleValue;
  }
  UNIT_SLOT_FATIGUE(result) = 0;
  stanceBits = UNIT_SLOT_STANCE_BITS(result);
  UNIT_SLOT_AUX_STATE(result) = 0;
  auxFlagsByte = *(_BYTE *)(uintptr_t)(result + 17);
  UNIT_SLOT_STANCE_BITS(result) = stanceBits & 0x80;
  stateBitsByte = UNIT_SLOT_STATE_BITS(result);
  *(_BYTE *)(uintptr_t)(result + 17) = auxFlagsByte & 0xF8;
  flagsByte = UNIT_SLOT_FLAGS(result);
  UNIT_SLOT_STATE_BITS(result) = stateBitsByte & 0xFE;
  UNIT_SLOT_FLAGS(result) = flagsByte & 0xF0;
  return result;
}
