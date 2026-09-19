int  UnitSlot_GetBaseActionPoints(__int16 *slotPtr)
{
  return (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * *slotPtr];
}
