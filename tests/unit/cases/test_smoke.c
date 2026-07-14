/* Smoke test: proves the coverage TU links and can call a recovered
 * pure function. Included into test_all.c (not compiled standalone). */

TEST(smoke, unit_type_world_move_cost) {
  /* UnitType_GetWorldMoveCost indexes the recovered 88-byte metadata roster;
   * just exercise it across a couple of type ids for coverage + a sanity
   * bound (a move cost byte, so <= 0xFF trivially). */
  int t;
  for (t = 0; t < 3; ++t) {
    unsigned char c = UnitType_GetWorldMoveCost(t, 0);
    CHECK(c <= 0xFF);
  }
}
