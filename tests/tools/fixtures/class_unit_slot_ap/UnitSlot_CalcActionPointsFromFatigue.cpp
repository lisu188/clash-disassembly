int  UnitSlot_CalcActionPointsFromFatigue(__int16 *slotPtr)
{
  UnitSlotRecord *slot;
  int unitType;
  int fatigueLevel;
  int result;

  slot = (UnitSlotRecord *)slotPtr;
  unitType = slot->unit_type_id;
  if ( unitType < 0 || unitType >= UNIT_TYPE_COUNT )
    return 0;
  fatigueLevel = slot->fatigue;
  result = (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unitType];
  if ( fatigueLevel >= 80 && fatigueLevel <= 89 )
    return (192 * result - (__CFSHL__((192 * result) >> 31, 8) + ((192 * result) >> 31 << 8))) >> 8;
  if ( fatigueLevel >= 90 && fatigueLevel <= 99 )
    return ((result << 7) - (__CFSHL__(result << 7 >> 31, 8) + (result << 7 >> 31 << 8))) >> 8;
  if ( fatigueLevel == 100 )
    return 0;
  return result;
}
