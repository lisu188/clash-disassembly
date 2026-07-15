/* Smoke test: proves an independent case can call split recovered code. */

TEST(smoke, unit_type_world_move_cost) {
  /* UnitType_GetWorldMoveCost indexes the recovered 88-byte metadata roster;
   * the first three executable-backed records all have plain-A cost 4. */
  int t;
  for (t = 0; t < 3; ++t) {
    CHECK_EQ(UnitType_GetWorldMoveCost(t, 0), 4);
  }
}

TEST(smoke, executable_backed_unit_type_runtime_core) {
  const UnitTypeRuntimeCoreMetadataRecord *builder =
    &g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_BUILDER];
  const UnitTypeRuntimeCoreMetadataRecord *dragon =
    &g_UnitTypeRuntimeCoreMetadata[30];

  CHECK_EQ(sizeof(UnitTypeRuntimeCoreMetadataRecord), UNIT_TYPE_METADATA_STRIDE);
  CHECK_EQ(sizeof(g_UnitTypeRuntimeCoreMetadata) /
             sizeof(g_UnitTypeRuntimeCoreMetadata[0]),
           UNIT_TYPE_COUNT);

  CHECK_EQ(builder->battle_move_step_px, 3);
  CHECK_EQ(builder->move_animation_tick_interval_ms, 3);
  CHECK_EQ(builder->animation_frame_interval_ms, 10);
  CHECK_EQ(builder->attack_animation_frame_count, 8);
  CHECK_EQ(builder->base_defense_power, 1);
  CHECK_EQ(builder->base_action_points, 26);
  CHECK_EQ(builder->road_move_cost, 3);
  CHECK_EQ(builder->world_surface_move_costs[0], 4);
  CHECK_EQ(builder->world_surface_move_costs[7], 0);

  CHECK_EQ(dragon->idle_animation_flags[0], 1);
  CHECK_EQ(dragon->sprite_vertical_offset_px, 28);
  CHECK_EQ(dragon->attack_animation_frame_count, 16);
  CHECK_EQ(dragon->shot_animation_frame_count, 16);
  CHECK_EQ(dragon->flags, 3);
  CHECK_EQ(dragon->base_melee_attack, 18);
  CHECK_EQ(dragon->base_defense_power, 15);
  CHECK_EQ(dragon->base_action_points, 36);
  CHECK_EQ(dragon->base_shot_power, 15);
}
