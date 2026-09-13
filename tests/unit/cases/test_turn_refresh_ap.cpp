TEST(turn_refresh_ap, fatigue_thresholds_match_new_turn_contract) {
  unsigned char slot[UNIT_SLOT_RECORD_BYTES] = {};
  __int16 *slot_ptr = reinterpret_cast<__int16 *>(slot);
  const int unit_type = 17;
  const int metadata_index = UNIT_TYPE_METADATA_STRIDE * unit_type;
  const unsigned char saved_base_ap =
      static_cast<unsigned char>(g_UnitTypeBaseActionPoints[metadata_index]);

  *slot_ptr = static_cast<__int16>(unit_type);
  g_UnitTypeBaseActionPoints[metadata_index] = 20;

  slot[10] = 0;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 20);
  slot[10] = 79;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 20);
  slot[10] = 80;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 15);
  slot[10] = 89;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 15);
  slot[10] = 90;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 10);
  slot[10] = 99;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 10);
  slot[10] = 100;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);

  g_UnitTypeBaseActionPoints[metadata_index] = saved_base_ap;
}

TEST(turn_refresh_ap, invalid_unit_type_cannot_gain_action_points) {
  unsigned char slot[UNIT_SLOT_RECORD_BYTES] = {};
  __int16 *slot_ptr = reinterpret_cast<__int16 *>(slot);

  *slot_ptr = -1;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);
  *slot_ptr = UNIT_TYPE_COUNT;
  CHECK_EQ(UnitSlot_CalcActionPointsFromFatigue(slot_ptr), 0);
}
