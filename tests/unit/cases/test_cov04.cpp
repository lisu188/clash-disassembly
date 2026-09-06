/* cov04: Castle/Garrison/Economy dialog helpers, Diagnostics tracing helpers,
 * Tooltip helpers, RoadBuildMode/UnitBattle/WCIsvListBase small helpers. */

/* NOTE on Castle_InvokePrisonerPanel / Castle_InvokeEconomyPanel: both are
 * thin wrappers that unconditionally enter a full modal dialog ("Run"/"Show*
 * Panel") that contains a do/while loop polling DD_Pump while waiting for an
 * exit-signal global to change value (e.g. BuildingEconomyDialog_Run's
 * `while (exit_signal_snapshot == g_BuildingEconomyDialogExitSignal);`). With
 * no real input source in this headless harness that signal never flips, so
 * calling these would hang the whole coverage binary (not just crash it,
 * which the harness could catch) -- deliberately left untested here.
 *
 * NOTE on CastleProduction_ReloadLicenceSlotSprites: its `for` loop's
 * "increment" clause is itself the whole-body call
 * `CastleProduction_ReloadLicenceSlotSprite(i, a1)` and `i` is never
 * incremented anywhere -- a genuine decompiler-artifact infinite loop unless
 * that inner call happens to fault first. With the default (zeroed)
 * dword_532218 it does fault immediately (dereferences near address 402), so
 * we deliberately do NOT initialize dword_532218 here: that keeps the crash
 * (caught by the harness) instead of unmasking the infinite loop. */

/* ---- BuildingGarrisonDialog_WriteActionWidgetRecord ---------------- */
TEST(cov04_garrison, write_action_widget_record) {
  static unsigned char record[128];
  memset(record, 0, sizeof record);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
      record, 10, 20, 1, 2, 3, NULL, "pl", "en",
      "de", "snd");
  CHECK_EQ(*(_DWORD *)(record + 0), 10);
  CHECK_EQ(*(_DWORD *)(record + 4), 20);
  CHECK_EQ(record[48], 2);
}

/* ---- BuildingGarrisonDialog_EnsureActionWidgets --------------------- */
TEST(cov04_garrison, ensure_action_widgets_all_flag_combos) {
  static unsigned char building[512];
  memset(building, 0, sizeof building);

  building[416] = 0; /* addon_flags == 0 -> all ternaries take false branch */
  TOUCH((BuildingGarrisonDialog_EnsureActionWidgets((int)(intptr_t)building), 0));

  building[416] = 0x0B; /* bits 1,2,8 set -> all ternaries take true branch */
  TOUCH((BuildingGarrisonDialog_EnsureActionWidgets((int)(intptr_t)building), 0));
}

/* ---- Diagnostics_Is*Enabled (cached-flag helpers) ------------------- */
TEST(cov04_diag, is_battle_tile_draw_trace_enabled) {
  /* First call decides+caches; second call takes the "already checked"
   * branch regardless of outcome -- both branches of the `if (!checked)`
   * guard get exercised across the two calls. */
  TOUCH(Diagnostics_IsBattleTileDrawTraceEnabled());
  TOUCH(Diagnostics_IsBattleTileDrawTraceEnabled());
}

TEST(cov04_diag, is_world_map_click_trace_enabled) {
  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 0);
  TOUCH(Diagnostics_IsWorldMapClickTraceEnabled());
  TOUCH(Diagnostics_IsWorldMapClickTraceEnabled());
}

TEST(cov04_diag, is_world_map_action_verbose) {
  TOUCH(Diagnostics_IsWorldMapActionVerbose());
  TOUCH(Diagnostics_IsWorldMapActionVerbose());
}

/* ---- Diagnostics_ShouldTraceWorldMapActionStage --------------------- */
TEST(cov04_diag, should_trace_world_map_action_stage_branches) {
  int i;

  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage(NULL));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("action_widgets_after_click"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("selection_after_click"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("status_panel_refresh_done"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("status_panel_other_thing"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("playgame_loop_top"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("playgame_after_player_info"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_turn_loop_iter_top"));
  for (i = 0; i < 3; ++i)
    TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_turn_loop_after_input_widgets"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_move_track_enter"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_move_track_return"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_move_track_cost"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_move_execute_no_flip"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("battle_turn_loop_after_something_else"));
  TOUCH(Diagnostics_ShouldTraceWorldMapActionStage("some_other_random_stage"));
}

/* ---- Diagnostics_SurfaceByteChecksum --------------------------------- */
TEST(cov04_diag, surface_byte_checksum) {
  static _DWORD surfaceNull_dummy;
  static _DWORD surface[64];
  static unsigned char pixelsSmall[64];
  static _DWORD bigSurface[64];
  static unsigned char pixelsBig[2048];
  unsigned i;

  (void)surfaceNull_dummy;
  CHECK_EQ(Diagnostics_SurfaceByteChecksum(0), 0);

  /* pixels == NULL */
  memset(surface, 0, sizeof surface);
  surface[0] = 8 | (8 << 16);
  CHECK_EQ(Diagnostics_SurfaceByteChecksum((int)(intptr_t)surface), 0);

  /* width*height == 0 */
  memset(pixelsSmall, 0xAB, sizeof pixelsSmall);
  surface[0] = 0; /* width=0, height=0 */
  surface[1] = (unsigned int)(uintptr_t)pixelsSmall;
  CHECK_EQ(Diagnostics_SurfaceByteChecksum((int)(intptr_t)surface), 0);

  /* small surface: pixel_count < 1024 -> step forced to 1 */
  surface[0] = 8 | (8 << 16);
  for (i = 0; i < sizeof pixelsSmall; ++i) pixelsSmall[i] = (unsigned char)(i * 7);
  TOUCH(Diagnostics_SurfaceByteChecksum((int)(intptr_t)surface));

  /* bigger surface: pixel_count >= 1024 -> step != 1 */
  memset(bigSurface, 0, sizeof bigSurface);
  bigSurface[0] = 64 | (32 << 16); /* 2048 pixels */
  for (i = 0; i < sizeof pixelsBig; ++i) pixelsBig[i] = (unsigned char)(i * 3 + 1);
  bigSurface[1] = (unsigned int)(uintptr_t)pixelsBig;
  TOUCH(Diagnostics_SurfaceByteChecksum((int)(intptr_t)bigSurface));
}

/* ---- Diagnostics_TraceCastleHotspots --------------------------------- */
TEST(cov04_diag, trace_castle_hotspots) {
  static _DWORD surface[64];
  static unsigned char pixels[64];
  int i;

  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 0);

  /* surface == NULL -> early return */
  TOUCH((Diagnostics_TraceCastleHotspots(0), 0));

  memset(surface, 0, sizeof surface);
  memset(pixels, 0, sizeof pixels);
  /* mark surface as "linear software" via a real global vtable table (as in
   * test_cov00.c) so InvokeSlot16ReadPixel takes the safe direct-read path
   * instead of calling through an unpopulated method-table slot. */
  surface[46] = (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable;
  surface[0] = 8 | (8 << 16); /* width=8 height=8 */
  surface[1] = (unsigned int)(uintptr_t)pixels;
  for (i = 0; i < 8; ++i)
    pixels[i * 8 + i] = (unsigned char)(248 + i); /* one hit per hotspot id 248..255 */
  TOUCH((Diagnostics_TraceCastleHotspots((int)(intptr_t)surface), 0));
}

/* ---- Diagnostics_TraceBootstrapEvent (uncached, re-reads getenv) ----- */
TEST(cov04_diag, trace_bootstrap_event) {
  unsetenv("CLASH95_TRACE_BOOTSTRAP");
  TOUCH((Diagnostics_TraceBootstrapEvent("stage-disabled"), 0));

  setenv("CLASH95_TRACE_BOOTSTRAP", "1", 1);
  TOUCH((Diagnostics_TraceBootstrapEvent("stage-enabled"), 0));
  unsetenv("CLASH95_TRACE_BOOTSTRAP");
}

/* ---- Diagnostics_TraceWorldMapUnitSnapshot --------------------------- */
TEST(cov04_diag, trace_world_map_unit_snapshot) {
  /* Depends on the same cached Diagnostics_IsWorldMapClickTraceEnabled()
   * flag as trace_castle_hotspots above; whichever branch is cached, this
   * call is safe: enabled==false just early-returns, and enabled==true walks
   * a bounded (500 iteration) loop over the real gameData-relative globals
   * (harness-caught crash at worst, no hang). */
  TOUCH((Diagnostics_TraceWorldMapUnitSnapshot("probe-stage"), 0));
}

/* ---- Tooltip_ReleaseBackdropSurface ----------------------------------- */
TEST(cov04_tooltip, release_backdrop_surface_null) {
  g_TooltipBackdropSurface = 0;
  CHECK_EQ(Tooltip_ReleaseBackdropSurface(), 0);
  CHECK_EQ(g_TooltipBackdropSurface, 0);
}

TEST(cov04_tooltip, release_backdrop_surface_valid) {
  static _DWORD fakeVtable[4];
  static _DWORD fakeSurface[64];

  memset(fakeVtable, 0, sizeof fakeVtable);
  memset(fakeSurface, 0, sizeof fakeSurface);
  fakeVtable[0] = (unsigned int)(uintptr_t)Runtime_DescriptorNoop; /* destructor slot */
  fakeSurface[46] = (unsigned int)(uintptr_t)fakeVtable; /* offset 184 == index 46 */

  g_TooltipBackdropSurface = (int)(intptr_t)fakeSurface;
  CHECK_EQ(Tooltip_ReleaseBackdropSurface(), 0);
  CHECK_EQ(g_TooltipBackdropSurface, 0);
}

/* ---- Tooltip_RestoreIfTextMatches -------------------------------------
 * Only the "strings differ" branch is exercised: the "strings match" branch
 * would fall into Tooltip_RestoreBackdrop(), which unconditionally drives the
 * real render pipeline (RenderState_PumpIfRectInViewBounds/Render_FillRect/
 * Render_Present against g_RenderState) -- too deep/unsafe to fake here. */
TEST(cov04_tooltip, restore_if_text_matches_mismatch) {
  int result = Tooltip_RestoreIfTextMatches((int)(intptr_t)"alpha",
                                             (int)(intptr_t)"beta");
  CHECK(result != 0);
}

/* ---- Tooltip_SetResourceHandle ---------------------------------------- */
TEST(cov04_tooltip, set_resource_handle) {
  CHECK_EQ(Tooltip_SetResourceHandle(42), 42);
  CHECK_EQ(g_TooltipResourceHandle, 42);
  CHECK_EQ(Tooltip_SetResourceHandle(0), 0);
}

/* ---- UnitStack_HasOnlyFlyingUnits ----------------------------------- */
TEST(cov04_unitstack, has_only_flying_units_all_branches) {
  static unsigned char stack[512];
  int i;

  /* immediate terminator -> returns 1 without looking at g_UnitTypeFlags */
  memset(stack, 0, sizeof stack);
  *(__int16 *)(stack + 6) = -1;
  CHECK_EQ(UnitStack_HasOnlyFlyingUnits((int)(intptr_t)stack), 1);

  /* type 0 present, flag bit0 clear -> break out of loop -> return 0 */
  memset(stack, 0, sizeof stack);
  *(__int16 *)(stack + 6) = 0;
  CHECK_EQ(UnitStack_HasOnlyFlyingUnits((int)(intptr_t)stack), 0);

  /* Executable-backed type 26 has flag bit0 set. Ten such slots reach the
   * cap and return 1. */
  memset(stack, 0, sizeof stack);
  for (i = 0; i < 10; ++i)
    *(__int16 *)(stack + 6 + 31 * i) = 26;
  CHECK_EQ(UnitStack_HasOnlyFlyingUnits((int)(intptr_t)stack), 1);
}

/* ---- RoadBuildMode_RequestExitAfterWidgetPress / _RequestExit --------- */
TEST(cov04_roadbuild, request_exit_after_widget_press) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000; /* >=640 -> UIWidget_RefreshActionButtonState
                                     takes its safe early-return path */
  g_RoadBuildModeExitRequested = 0;
  TOUCH(RoadBuildMode_RequestExitAfterWidgetPress((int)(intptr_t)widget, 0));
  CHECK_EQ(g_RoadBuildModeExitRequested, 1);
}

TEST(cov04_roadbuild, request_exit) {
  g_RoadBuildModeExitRequested = 0;
  RoadBuildMode_RequestExit();
  CHECK_EQ(g_RoadBuildModeExitRequested, 1);
}

/* ---- UnitBattle_GetTargetCrowdingScale --------------------------------- */
TEST(cov04_unitbattle, get_target_crowding_scale_zero_enemies) {
  static unsigned char unit[64];
  static unsigned char battleCtx[2048];
  int saved_ctx = g_MapData;

  memset(unit, 0, sizeof unit);
  memset(battleCtx, 0, sizeof battleCtx);
  /* g_MapData (battle-context base) defaults to 0, which would make
   * UnitBattle_CountAdjacentEnemies dereference near-null memory. Point it at
   * a zeroed buffer instead: the width field it reads (offset 804) is then 0,
   * so every neighbor check fails its bounds test and the enemy count stays
   * a deterministic 0 without ever touching the (unmodeled) battlefield grid
   * further into the buffer. */
  g_MapData = (int)(intptr_t)battleCtx;
  CHECK_EQ(UnitBattle_GetTargetCrowdingScale((int)(intptr_t)unit), 256);
  g_MapData = saved_ctx;
}

/* ---- BuildingEconomyDialog_SetExitSignal ------------------------------- */
TEST(cov04_economy, set_exit_signal) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  g_BuildingEconomyDialogExitSignal = 0;
  TOUCH(BuildingEconomyDialog_SetExitSignal((int)(intptr_t)widget, 1));
  CHECK_EQ(g_BuildingEconomyDialogExitSignal, 1);
}

/* ---- UnitBattleDialog_SelectAffirmativeResponse / NegativeResponse ----- */
TEST(cov04_unitbattledlg, select_affirmative_response) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  TOUCH(UnitBattleDialog_SelectAffirmativeResponse((int)(intptr_t)widget, 0));
}

TEST(cov04_unitbattledlg, select_negative_response) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  TOUCH(UnitBattleDialog_SelectNegativeResponse((int)(intptr_t)widget, 0));
}

/* ---- BuildingGarrisonDialog_CountSelectedSlots ------------------------- */
TEST(cov04_garrison, count_selected_slots) {
  int i;

  memset(g_BuildingGarrisonDialogSelectedSlots, 0,
         sizeof g_BuildingGarrisonDialogSelectedSlots);
  CHECK_EQ(BuildingGarrisonDialog_CountSelectedSlots(), 0);

  for (i = 0; i < 12; ++i)
    g_BuildingGarrisonDialogSelectedSlots[i] = 1;
  CHECK_EQ(BuildingGarrisonDialog_CountSelectedSlots(), 12);

  for (i = 0; i < 12; i += 2)
    g_BuildingGarrisonDialogSelectedSlots[i] = 0;
  CHECK_EQ(BuildingGarrisonDialog_CountSelectedSlots(), 6);

  memset(g_BuildingGarrisonDialogSelectedSlots, 0,
         sizeof g_BuildingGarrisonDialogSelectedSlots);
}

/* ---- BuildingGarrisonDialog_RebuildSlotSprites ------------------------- */
TEST(cov04_garrison, rebuild_slot_sprites) {
  static unsigned char building[512];
  int saved_active = g_BuildingGarrisonDialogActiveBuilding;
  int i;

  memset(building, 0, sizeof building);
  /* every slot's unit-type-in-slot field (offset 18 relative to each 31-byte
   * slot record) == -1 makes BuildingGarrisonDialog_ReloadSlotSprite return
   * immediately for all 12 slots, so the loop itself is fully exercised
   * safely. The trailing BuildingGarrisonDialog_DrawSlotGrid(-1) call
   * unconditionally dereferences the (unmodeled, zero-by-default)
   * dword_5321F8 render-surface global and will fault -- that happens after
   * every line of *this* function has already run, so it costs us nothing
   * and the harness catches it. */
  for (i = 0; i < 12; ++i)
    *(__int16 *)(building + 31 * i + 18) = -1;
  g_BuildingGarrisonDialogActiveBuilding = (int)(intptr_t)building;

  TOUCH(BuildingGarrisonDialog_RebuildSlotSprites(0, 0));

  g_BuildingGarrisonDialogActiveBuilding = saved_active;
}

/* ---- CastleProduction_ReloadLicenceSlotSprites -------------------------
 * See file-level note at the top: deliberately left with dword_532218 at its
 * default 0 so the very first inner call faults (near address 402) instead
 * of spinning in the miscompiled infinite `for` loop. */
TEST(cov04_castleprod, reload_licence_slot_sprites) {
  TOUCH(CastleProduction_ReloadLicenceSlotSprites(0));
}

/* ---- CastleProduction_SetExitSignal ------------------------------------ */
TEST(cov04_castleprod, set_exit_signal) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  TOUCH(CastleProduction_SetExitSignal((int)(intptr_t)widget));
}

/* ---- BuildingTransferTargetList_SetDrawOrigin -------------------------- */
TEST(cov04_transferlist, set_draw_origin) {
  CHECK_EQ(BuildingTransferTargetList_SetDrawOrigin(11, 22), 11);
  CHECK_EQ(g_BuildingTransferTargetListDrawX, 11);
  CHECK_EQ(g_BuildingTransferTargetListDrawY, 22);
}

/* ---- WCIsvListBase_PopUntilMatchOrEmpty --------------------------------
 * Only the immediate-empty branch is safe: making the loop body actually run
 * requires a real populated WCIsvListBase linked-list (handles/link nodes)
 * whose plumbing (WCIsvListBase_base_sget / WCCompat_LinkFromHandle /
 * WCIsvListBase_ReleaseLinkNode) is out of scope to fake correctly, and a
 * wrong fake risks an infinite loop (the front-pop keeps returning the same
 * "not found" sentinel forever without ever clearing the count field). */
TEST(cov04_wcisv, pop_until_match_or_empty_immediately_empty) {
  static _DWORD list[16];
  memset(list, 0, sizeof list);
  CHECK_EQ(WCIsvListBase_PopUntilMatchOrEmpty(0, (int)(intptr_t)list), 0);
}

/* ---- WCIsvListBase_dtorFreeOnly ----------------------------------------- */
TEST(cov04_wcisv, dtor_free_only) {
  TOUCH(WCIsvListBase_vtblFree());
}

/* ---- WCIsvListBase_ValuesEqual ------------------------------------------ */
TEST(cov04_wcisv, values_equal) {
  _DWORD a = 5, b = 5, c = 9;
  CHECK(WCIsvListBase_ValuesEqual(&a, &b) != 0);
  CHECK(WCIsvListBase_ValuesEqual(&a, &c) == 0);
}
