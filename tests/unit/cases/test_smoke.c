/* Smoke test: proves an independent case can call split recovered code. */

#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

TEST(smoke, game_root_override_owns_relative_paths) {
  /* The runner executes this case in a child. All filesystem changes stay
   * inside one owned fixture; the default root is only observed, never written. */
  char fixture[] = "/tmp/clash95-game-root-XXXXXX";
  char root_path[128], cwd_path[128], root_marker[160], cwd_marker[160];
  static char configured_cwd[PATH_MAX], unset_cwd[PATH_MAX], invalid_cwd[PATH_MAX];
  const char *original_root = getenv("CLASH95_GAME_ROOT");
  char *saved_root = original_root ? strdup(original_root) : NULL;
  int had_root = original_root != NULL;
  int cwd_fd = -1;
  int file_fd = -1;
  int fixture_created = 0, root_created = 0, cwd_created = 0;
  int root_marker_created = 0, cwd_marker_created = 0;
  int status;
  DWORD attributes, unset_attributes;
  WIN32_FIND_DATAA found;
  HANDLE find_handle = (HANDLE)-1;

  CHECK(!had_root || saved_root != NULL);
  if (had_root && !saved_root)
    return;
  cwd_fd = open(".", O_RDONLY | O_DIRECTORY);
  CHECK(cwd_fd >= 0);
  if (cwd_fd < 0)
    goto cleanup;
  CHECK(mkdtemp(fixture) != NULL);
  if (g_clash_cur_failed)
    goto cleanup;
  fixture_created = 1;
  snprintf(root_path, sizeof root_path, "%s/Runtime Root", fixture);
  snprintf(cwd_path, sizeof cwd_path, "%s/cwd", fixture);
  snprintf(root_marker, sizeof root_marker, "%s/MiXeDMarker", root_path);
  snprintf(cwd_marker, sizeof cwd_marker, "%s/mixedmarker", cwd_path);
  status = mkdir(root_path, 0700);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  root_created = 1;
  status = mkdir(cwd_path, 0700);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  cwd_created = 1;
  status = mkdir(root_marker, 0700);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  root_marker_created = 1;
  file_fd = open(cwd_marker, O_WRONLY | O_CREAT | O_EXCL, 0600);
  CHECK(file_fd >= 0);
  if (file_fd < 0)
    goto cleanup;
  cwd_marker_created = 1;
  CHECK_EQ(close(file_fd), 0);
  file_fd = -1;
  status = chdir(cwd_path);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  status = setenv("CLASH95_GAME_ROOT", root_path, 1);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;

  attributes = GetFileAttributesA("mixedmarker");
  CHECK(attributes != (DWORD)-1);
  CHECK((attributes & 0x10u) != 0); /* root directory, not cwd regular file */
  CHECK((uintptr_t)configured_cwd <= UINT32_MAX);
  CHECK((uintptr_t)unset_cwd <= UINT32_MAX);
  CHECK((uintptr_t)invalid_cwd <= UINT32_MAX);
  if (g_clash_cur_failed)
    goto cleanup;
  CHECK_EQ(getcwd_((_DWORD)(uintptr_t)configured_cwd, sizeof configured_cwd),
           (int)(uintptr_t)configured_cwd);
  CHECK_EQ(strcmp(configured_cwd, root_path), 0);
  memset(&found, 0, sizeof found);
  find_handle = FindFirstFileA("mixed*", &found);
  CHECK(find_handle != (HANDLE)-1);
  if (find_handle != (HANDLE)-1) {
    CHECK_EQ(strcmp(found.cFileName, "MiXeDMarker"), 0);
    CHECK((found.dwFileAttributes & 0x10u) != 0);
    CHECK_EQ(FindClose(find_handle), 1);
    find_handle = (HANDLE)-1;
  }

  status = unsetenv("CLASH95_GAME_ROOT");
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  unset_attributes = GetFileAttributesA("mixedmarker");
  CHECK(unset_attributes != (DWORD)-1);
  CHECK_EQ(unset_attributes & 0x10u, 0); /* existing default cwd precedence */
  CHECK_EQ(getcwd_((_DWORD)(uintptr_t)unset_cwd, sizeof unset_cwd),
           (int)(uintptr_t)unset_cwd);
  status = setenv("CLASH95_GAME_ROOT", ".", 1);
  CHECK_EQ(status, 0);
  if (status != 0)
    goto cleanup;
  CHECK_EQ(GetFileAttributesA("mixedmarker"), unset_attributes);
  CHECK_EQ(getcwd_((_DWORD)(uintptr_t)invalid_cwd, sizeof invalid_cwd),
           (int)(uintptr_t)invalid_cwd);
  CHECK_EQ(strcmp(invalid_cwd, unset_cwd), 0);

cleanup:
  if (find_handle != (HANDLE)-1)
    CHECK_EQ(FindClose(find_handle), 1);
  if (file_fd >= 0)
    CHECK_EQ(close(file_fd), 0);
  if (had_root)
    CHECK_EQ(setenv("CLASH95_GAME_ROOT", saved_root, 1), 0);
  else
    CHECK_EQ(unsetenv("CLASH95_GAME_ROOT"), 0);
  if (cwd_fd >= 0) {
    CHECK_EQ(fchdir(cwd_fd), 0);
    CHECK_EQ(close(cwd_fd), 0);
  }
  if (cwd_marker_created)
    CHECK_EQ(unlink(cwd_marker), 0);
  if (root_marker_created)
    CHECK_EQ(rmdir(root_marker), 0);
  if (cwd_created)
    CHECK_EQ(rmdir(cwd_path), 0);
  if (root_created)
    CHECK_EQ(rmdir(root_path), 0);
  if (fixture_created)
    CHECK_EQ(rmdir(fixture), 0);
  free(saved_root);
}

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
    &g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_DRAGON];
  const UnitTypeRuntimeCoreMetadataRecord *peasant =
    &g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_PEASANT];
  const UnitTypeRuntimeCoreMetadataRecord *catapult =
    &g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_CATAPULT];

  CHECK_EQ(sizeof(UnitTypeRuntimeCoreMetadataRecord), UNIT_TYPE_METADATA_STRIDE);
  CHECK_EQ(UNIT_TYPE_COUNT, 35);
  CHECK_EQ(UNIT_TYPE_METADATA_CAPACITY, 40);
  CHECK_EQ(sizeof(g_UnitTypeRuntimeCoreMetadata) /
             sizeof(g_UnitTypeRuntimeCoreMetadata[0]),
           UNIT_TYPE_METADATA_CAPACITY);

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

  /* Original PE scalars: corpse frames (+78) and autoresolve casualty
   * weights (+87) are distinct, and licence cost (+73) is a full word. */
  CHECK_EQ(peasant->corpse_sprite_base_index, 0);
  CHECK_EQ(peasant->autoresolve_casualty_weight, 50);
  CHECK_EQ(catapult->corpse_sprite_base_index, 32);
  CHECK_EQ(catapult->autoresolve_casualty_weight, 100);
  CHECK_EQ(dragon->corpse_sprite_base_index, 48);
  CHECK_EQ(dragon->autoresolve_casualty_weight, 60);
  CHECK_EQ(dragon->production_licence_cost, 550);
  CHECK_EQ(builder->production_time, 3);
  CHECK_EQ(builder->production_cost, 6);
  CHECK_EQ(g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_FORESTER].ranged_attack_sound_frame, 26);
}

TEST(smoke, unit_names_select_original_language_bytes) {
  static const struct {
    unit_type type;
    const char *names[3];
  } cases[] = {
    { UNIT_TYPE_ARCHER, { "\234ucznik", "Archer", "Bogensch\201tzen" } },
    { UNIT_TYPE_RAM, { "Taran", "Taran", "Rammbock" } },
    { UNIT_TYPE_GORAL, { "G\242ral", "Highlander", "Bergbewohner" } },
    { UNIT_TYPE_CYCLOP, { "Cyklop", "Cyklop", "Zyklop" } },
    { UNIT_TYPE_PEGASUS, { "Pegaz", "Pegaz", "Pegasus" } }
  };
  char saved_language = g_LanguageIndex;
  size_t i;
  int language;

  /* These original spellings and legacy font bytes catch both the old
   * English-only fallback and substitutions inferred from enum names. */
  for (language = 0; language < 3; ++language) {
    g_LanguageIndex = (char)language;
    for (i = 0; i < sizeof cases / sizeof cases[0]; ++i)
      CHECK_EQ(strcmp(UnitType_GetLocalizedName(cases[i].type),
                      cases[i].names[language]), 0);
  }
  g_LanguageIndex = saved_language;
}

TEST(smoke, unit_name_invalid_selectors_keep_fallbacks) {
  char saved_language = g_LanguageIndex;

  g_LanguageIndex = 3;
  CHECK_EQ(strcmp(UnitType_GetLocalizedName(UNIT_TYPE_GORAL), "Highlander"), 0);
  g_LanguageIndex = (char)255;
  CHECK_EQ(strcmp(UnitType_GetLocalizedName(UNIT_TYPE_PEGASUS), "Pegaz"), 0);
  g_LanguageIndex = 0;
  CHECK_EQ(strcmp(UnitType_GetLocalizedName((unit_type)-1), "Unknown unit"), 0);
  CHECK_EQ(strcmp(UnitType_GetLocalizedName((unit_type)UNIT_TYPE_COUNT), "Unknown unit"), 0);
  CHECK_EQ(strcmp(UnitType_GetLocalizedName((unit_type)UNIT_TYPE_METADATA_CAPACITY), "Unknown unit"), 0);
  g_LanguageIndex = saved_language;
}

TEST(smoke, unit_native_pointers_preserve_shared_names_and_distinct_keys) {
  const UnitTypeRuntimePointerRecord *foot =
    &g_UnitTypeRuntimePointers[UNIT_TYPE_SPECIAL_FOOT_PERSONAGE];
  const UnitTypeRuntimePointerRecord *mounted =
    &g_UnitTypeRuntimePointers[UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE];
  int type;

  /* Types 33 and 34 share the original name-triplet pointer at 0x512558,
   * while their independent resource keys select different sprites. */
  CHECK(foot->localized_names != NULL);
  CHECK(foot->localized_names == mounted->localized_names);
  CHECK(foot->resource_key && strcmp(foot->resource_key, "specm") == 0);
  CHECK(mounted->resource_key && strcmp(mounted->resource_key, "speck") == 0);
  CHECK(foot->move_sound_stem && strcmp(foot->move_sound_stem, "lekkie\\kon") == 0);
  CHECK(g_UnitTypeRuntimePointers[UNIT_TYPE_PEGASUS].move_sound_stem &&
        strcmp(g_UnitTypeRuntimePointers[UNIT_TYPE_PEGASUS].move_sound_stem,
               "latajace\\pegaz") == 0);

  for (type = UNIT_TYPE_COUNT; type < UNIT_TYPE_METADATA_CAPACITY; ++type) {
    CHECK(g_UnitTypeRuntimePointers[type].localized_names == NULL);
    CHECK(g_UnitTypeRuntimePointers[type].resource_key == NULL);
    CHECK(g_UnitTypeRuntimePointers[type].move_sound_stem == NULL);
  }
}

TEST(smoke, unit_type_metadata_reserved_slots_are_zero) {
  int type;
  size_t byte;

  /* The original production panel probes all 40 physical records. The
   * five records after the real roster contain 440 zero bytes in the PE. */
  for (type = UNIT_TYPE_COUNT; type < UNIT_TYPE_METADATA_CAPACITY; ++type) {
    const unsigned char *record =
      (const unsigned char *)&g_UnitTypeRuntimeCoreMetadata[type];
    for (byte = 0; byte < UNIT_TYPE_METADATA_STRIDE; ++byte)
      CHECK_EQ(record[byte], 0);
  }
}

TEST(smoke, production_roster_excludes_reserved_metadata_slots) {
  static unsigned char building[512];
  int saved_building = g_CastleProductionBuildingPtr;
  int i;

  memset(building, 0, sizeof building);
  building[4] = 1;
  building[444] = 7;
  building[BUILDING_ADDON_FLAGS_OFFSET] =
    BUILDING_ADDON_FLAG_SMITHS | BUILDING_ADDON_FLAG_WORKSHOP;
  g_CastleProductionBuildingPtr = (int)(intptr_t)building;
  CastleProduction_RebuildAvailableUnitList(NULL);
  for (i = 0; i < UNIT_TYPE_COUNT; ++i)
    CHECK_EQ(g_CastleProduction_AvailableUnitTypes[i], i);
  for (; i < 41; ++i)
    CHECK_EQ(g_CastleProduction_AvailableUnitTypes[i], UINT32_MAX);
  g_CastleProductionBuildingPtr = saved_building;
}

TEST(smoke, options_slider_aliases_share_record_storage) {
  unsigned char saved_sliders[sizeof g_OptionsMenuSliderThumbPositions];
  unsigned char saved_widgets[sizeof g_OptionsMenuWidgetTemplateBlob];
  int value;
  int i;

  memcpy(saved_sliders, g_OptionsMenuSliderThumbPositions, sizeof saved_sliders);
  memcpy(saved_widgets, g_OptionsMenuWidgetTemplateBlob, sizeof saved_widgets);
  Options_RebuildMainMenuWidgetTemplates();
  for (i = 0; i < 3; ++i) {
    memcpy(&value, g_OptionsMenuSliderThumbPositions + 36 * i + 12, sizeof value);
    CHECK_EQ(value, 128);
  }
  memcpy(&value, g_OptionsMenuSliderThumbPositions + 108, sizeof value);
  CHECK_EQ(value, -1);

  g_Options_BrightnessSliderValue = 37;
  memcpy(&value, g_OptionsMenuSliderThumbPositions + 12, sizeof value);
  CHECK_EQ(value, 37);
  CHECK_EQ(g_Options_ScrollSpeedSliderValue, 128);
  CHECK_EQ(g_Options_MouseSpeedSliderValue, 128);
  value = 211;
  memcpy(g_OptionsMenuSliderThumbPositions + 48, &value, sizeof value);
  CHECK_EQ(g_Options_ScrollSpeedSliderValue, 211);
  g_Options_MouseSpeedSliderValue = 92;
  memcpy(&value, g_OptionsMenuSliderThumbPositions + 84, sizeof value);
  CHECK_EQ(value, 92);
  CHECK_EQ(g_Options_BrightnessSliderValue, 37);
  memcpy(&value, g_OptionsMenuSliderThumbPositions + 108, sizeof value);
  CHECK_EQ(value, -1);

  memcpy(g_OptionsMenuSliderThumbPositions, saved_sliders, sizeof saved_sliders);
  memcpy(g_OptionsMenuWidgetTemplateBlob, saved_widgets, sizeof saved_widgets);
}

TEST(smoke, unit_stack_vision_uses_all_occupied_slots) {
  static UnitStackRecord stack;
  int stack_address = (int)(intptr_t)&stack;

  memset(&stack, 0, sizeof stack);
  CHECK_EQ(UnitStack_GetVisionRadius(stack_address), 3);

  /* An eagle in the tenth slot extends an otherwise peasant stack's sight. */
  stack.unit_slots[9].unit_type_id = UNIT_TYPE_EAGLE;
  CHECK_EQ(UnitStack_GetVisionRadius(stack_address), 5);

  /* The empty-slot sentinel ends the roster before that trailing eagle. */
  stack.unit_slots[1].unit_type_id = -1;
  CHECK_EQ(UnitStack_GetVisionRadius(stack_address), 3);

  stack.unit_slots[0].unit_type_id = UNIT_TYPE_EAGLE;
  CHECK_EQ(UnitStack_GetVisionRadius(stack_address), 5);
}

TEST(smoke, unit_corpse_sprite_uses_type_and_reverse_facing) {
  __int16 slot_storage[16] = { 0 };
  BattleUnitEntry *slot = (BattleUnitEntry *)slot_storage;

  slot->unit_type_id = UNIT_TYPE_PEASANT;
  slot->facing_direction = 0;
  CHECK_EQ(UnitBattle_GetCorpseSpriteIndex(slot_storage), 4);

  slot->unit_type_id = UNIT_TYPE_CATAPULT;
  slot->facing_direction = 6;
  CHECK_EQ(UnitBattle_GetCorpseSpriteIndex(slot_storage), 34);

  slot->unit_type_id = UNIT_TYPE_DRAGON;
  slot->facing_direction = 7;
  CHECK_EQ(UnitBattle_GetCorpseSpriteIndex(slot_storage), 51);
}
