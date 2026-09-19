TEST(turn_refresh_ap, fatigue_thresholds_match_new_turn_contract) {
  unsigned char slot[UNIT_SLOT_RECORD_BYTES] = {};
  __int16 *slot_ptr = reinterpret_cast<__int16 *>(slot);
  const int unit_type = 17;
  const int metadata_index = UNIT_TYPE_METADATA_STRIDE * unit_type;
  const int base_ap = g_UnitTypeBaseActionPoints[metadata_index];
  CHECK(base_ap > 3);

  *slot_ptr = static_cast<__int16>(unit_type);

  slot[10] = 0;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), base_ap);
  slot[10] = 79;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), base_ap);
  slot[10] = 80;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 3 * base_ap / 4);
  slot[10] = 89;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 3 * base_ap / 4);
  slot[10] = 90;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), base_ap / 2);
  slot[10] = 99;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), base_ap / 2);
  slot[10] = 100;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);
}

TEST(turn_refresh_ap, invalid_unit_type_cannot_gain_action_points) {
  unsigned char slot[UNIT_SLOT_RECORD_BYTES] = {};
  __int16 *slot_ptr = reinterpret_cast<__int16 *>(slot);

  *slot_ptr = -1;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);
  *slot_ptr = UNIT_TYPE_COUNT;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);
}
