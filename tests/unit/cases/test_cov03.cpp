/* Batch 03: Math_CeilSqrt, world-map unit-attention-flash, tile highlight
 * slots, battle log toggles, Compat_RenderDeviceFillSolidRect, UI widget
 * transition/action callback helpers, unit-slot/building defense & upgrade
 * helpers, timer/perf-counter helpers, and castle ambient animation layers.
 *
 * Note: Building_HandleUpgradeButtonAction is intentionally NOT exercised
 * here. Its true-branch calls CRT_RunGuardedStaticLocalInit(), which is only
 * declared (never defined) anywhere in this repo; -ffunction-sections /
 * --gc-sections currently strip that undefined reference because nothing
 * calls the function. Calling it here would pull in an unresolved symbol
 * and break the link for the whole shared coverage binary, so it is left
 * uncovered rather than risk that.
 */

static int cov03_transition_cb(uintptr_t widget, int callback_arg, DWORD flag) {
  (void)widget;
  (void)callback_arg;
  (void)flag;
  return 42;
}

static int cov03_action_cb(uintptr_t widget, int a, DWORD b, char c, double d) {
  (void)widget;
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return 7;
}

/* ---- Math_CeilSqrt ---- */
TEST(cov03_math, ceil_sqrt) {
  int i;
  CHECK_EQ(Math_CeilSqrt(0), 1);
  CHECK_EQ(Math_CeilSqrt(3), 1);
  /* a1 >= 4: drive the iterative loop across many magnitudes to exercise
   * both break conditions and the outer do/while repeat. */
  for (i = 4; i < 40; ++i)
    TOUCH(Math_CeilSqrt(i));
  TOUCH(Math_CeilSqrt(100));
  TOUCH(Math_CeilSqrt(10000));
  TOUCH(Math_CeilSqrt(1000000));
  TOUCH(Math_CeilSqrt(2147483647));
}

/* ---- world-map unit attention flash ---- */
TEST(cov03_flash, start_and_query) {
  extern int g_WorldMapAttentionFlashUnitIndex;

  TOUCH(UI_StartWorldMapUnitAttentionFlash(5, 0, 0));
  CHECK(UI_IsWorldMapUnitAttentionFlashActive());

  g_WorldMapAttentionFlashUnitIndex = -1;
  CHECK(!UI_IsWorldMapUnitAttentionFlashActive());
}

/* ---- tile highlight slots ---- */
TEST(cov03_tile, highlight_and_clear) {
  int i;

  /* Fresh state: default-zeroed slots, (0,0) matches slot 0 immediately. */
  TOUCH(UI_ClearTileHighlight(0));

  /* All slots now (-1,-1): no match in the scan loop, slot 0 is free
   * (tile_x == -1) -> LABEL_8 fast path. */
  CHECK_EQ(UI_HighlightTile(5, 5), 0);

  /* Slot 0 now occupied by (5,5); slot 1 is still free -> the "search for
   * a free slot" while loop finds it. */
  CHECK_EQ(UI_HighlightTile(6, 6), 8);

  /* Re-highlighting an existing tile takes the early-match branch. */
  CHECK_EQ(UI_HighlightTile(5, 5), 0);

  /* Fill every remaining slot so the "search for free slot" loop runs to
   * completion without finding one (break at slot_index >= 8). */
  for (i = 2; i < 8; ++i)
    TOUCH(UI_HighlightTile(100 + i, 200 + i));
  TOUCH(UI_HighlightTile(500, 501));

  TOUCH(UI_ClearTileHighlight((void *)0x1));
}

/* ---- battle log toggles ---- */
TEST(cov03_battlelog, enable_disable) {
  extern int battleLogEnabled;

  BattleLog_Enable();
  CHECK_EQ(battleLogEnabled, 1);
  BattleLog_Disable();
  CHECK_EQ(battleLogEnabled, 0);
}

/* ---- Compat_RenderDeviceFillSolidRect ---- */
TEST(cov03_render, fill_solid_rect) {
  extern _UNKNOWN *g_RenderDevice;
  extern int g_Surface_RawBuffer8Vtable[17];
  _UNKNOWN *saved_device = g_RenderDevice;
  static _DWORD fake_surface[64];
  static unsigned char pixels[8192];

  memset(fake_surface, 0, sizeof(fake_surface));
  memset(pixels, 0, sizeof(pixels));

  /* g_RenderDevice == NULL -> immediate 0 return. */
  g_RenderDevice = 0;
  CHECK_EQ(Compat_RenderDeviceFillSolidRect(0, 0, 10, 10, 1), 0);

  /* g_RenderDevice non-null but not a "linear software" surface (default
   * zeroed fake surface) -> 0 return via the second guard. */
  g_RenderDevice = (_UNKNOWN *)fake_surface;
  CHECK_EQ(Compat_RenderDeviceFillSolidRect(0, 0, 10, 10, 1), 0);

  /* Make the fake surface pass RenderSurface_IsLinearSoftware: non-null
   * pixel pointer (slot 1) and a vtable slot (slot 46) matching one of the
   * two recognized linear-software vtables. width/height packed into slot 0
   * as two u16 halves. */
  fake_surface[0] = (50u << 16) | 50u; /* width=50 (lo16), height=50 (hi16) */
  fake_surface[1] = (_DWORD)(uintptr_t)pixels;
  fake_surface[46] = (_DWORD)(uintptr_t)g_Surface_RawBuffer8Vtable;

  /* left > right -> guard returns 0. */
  CHECK_EQ(Compat_RenderDeviceFillSolidRect(20, 0, 10, 10, 1), 0);
  /* top > bottom -> guard returns 0. */
  CHECK_EQ(Compat_RenderDeviceFillSolidRect(0, 20, 10, 10, 1), 0);
  /* left >= surface_width -> guard returns 0. */
  CHECK_EQ(Compat_RenderDeviceFillSolidRect(60, 60, 61, 61, 1), 0);

  /* Fully valid small rect, no clamping needed. */
  TOUCH(Compat_RenderDeviceFillSolidRect(0, 0, 10, 10, 7));

  /* right/bottom past the surface edges -> both clamp branches. */
  TOUCH(Compat_RenderDeviceFillSolidRect(0, 0, 200, 200, 3));

  g_RenderDevice = saved_device;
}

/* ---- UI widget icon transition wrappers (safe a2==0 short path) ---- */
TEST(cov03_widget, icon_transition_wrappers) {
  unsigned char widget[64];
  memset(widget, 0, sizeof(widget));
  /* sprite_set_holder (offset 12) == 0 -> UI_DrawWidgetIconWithTransition
   * takes its earliest "!sprite_set" return, regardless of a3. */
  TOUCH(UI_DrawWidgetIconTransitionSlow((unsigned __int16 *)widget, 0, 0));
  TOUCH(UI_DrawWidgetIconTransitionFast((unsigned __int16 *)widget, 0, 0));
}

/* ---- UI_InvokeWidgetTransitionCallback / UI_InvokeWidgetActionCallback ---- */
TEST(cov03_widget, invoke_transition_callback) {
  unsigned char widget[64];
  memset(widget, 0, sizeof(widget));

  /* callback field (offset 28) == 0 -> return 0. */
  CHECK_EQ(UI_InvokeWidgetTransitionCallback((uintptr_t)widget, 3), 0);

  /* non-null callback -> invoked. */
  *(_DWORD *)(widget + 28) = (_DWORD)(uintptr_t)cov03_transition_cb;
  CHECK_EQ(UI_InvokeWidgetTransitionCallback((uintptr_t)widget, 3), 42);
}

TEST(cov03_widget, invoke_action_callback) {
  unsigned char widget[64];
  memset(widget, 0, sizeof(widget));

  /* callback field (offset 32) == 0 -> return 0. */
  CHECK_EQ(UI_InvokeWidgetActionCallback((uintptr_t)widget), 0);

  *(_DWORD *)(widget + 32) = (_DWORD)(uintptr_t)cov03_action_cb;
  CHECK_EQ(UI_InvokeWidgetActionCallback((uintptr_t)widget), 7);
}

/* ---- Compat_WidgetPackedField / SpriteSetHandle / PackedString ---- */
TEST(cov03_widget, packed_field_and_string) {
  unsigned char widget[64];
  static _DWORD sprite_set_target;
  memset(widget, 0, sizeof(widget));

  *(_DWORD *)(widget + 20) = 0xDEADBEEFu;
  CHECK_EQ(Compat_WidgetPackedField((uintptr_t)widget, 20), (unsigned int)0xDEADBEEFu);

  /* PackedString never dereferences its result; any field value is safe. */
  TOUCH(Compat_WidgetPackedString((uintptr_t)widget, 20));

  /* SpriteSetHandle: null holder field (offset 12) -> 0. */
  CHECK_EQ(Compat_WidgetSpriteSetHandle((uintptr_t)widget), 0);

  /* non-null holder pointing at real memory -> dereferenced value. */
  sprite_set_target = 0x1234;
  *(_DWORD *)(widget + 12) = (_DWORD)(uintptr_t)&sprite_set_target;
  CHECK_EQ(Compat_WidgetSpriteSetHandle((uintptr_t)widget), (unsigned int)0x1234);
}

/* ---- UIWidget_ShowReleasedState ---- */
TEST(cov03_widget, show_released_state) {
  unsigned char widget[64];
  memset(widget, 0, sizeof(widget));

  /* *(int*)widget < 640, callback field (offset 28) == 0 -> the
   * UIWidget_RefreshActionButtonState branch calls
   * UI_InvokeWidgetTransitionCallback which returns 0 safely. */
  *(_DWORD *)(widget + 0) = 100;
  TOUCH(UIWidget_ShowReleasedState((uintptr_t)widget, 1));
  CHECK_EQ(*(_DWORD *)(widget + 8), 5);

  /* *(int*)widget >= 640 -> RefreshActionButtonState's other branch. */
  *(_DWORD *)(widget + 0) = 700;
  TOUCH(UIWidget_ShowReleasedState((uintptr_t)widget, 1));
}

/* ---- UnitSlots_CalcDefenseScore ---- */
TEST(cov03_unit, calc_defense_score) {
  unsigned char records[4 * 31];
  memset(records, 0, sizeof(records));
  /* Every 31-byte record's leading int16 is 0 (<= 0x28), so the inner
   * "skip" while never triggers; the outer loop runs a2 times. */
  TOUCH(UnitSlots_CalcDefenseScore((char *)records, 3, 0));
  TOUCH(UnitSlots_CalcDefenseScore((char *)records, 1, 1));
  TOUCH(UnitSlots_CalcDefenseScore((char *)records, 0, 0));
}

/* ---- Building_ApplySiegeDamageToWallSections ---- */
TEST(cov03_building, siege_damage_top_level) {
  /* a1 is a plain 'int' standing in for a 32-bit pointer; must be `static`
   * so its address survives truncation to a DWORD and back on this 64-bit
   * host (a plain stack local's address would be far outside 32 bits). */
  static unsigned char wall[512];
  memset(wall, 0, sizeof(wall));
  /* a2 < 100 -> a2/100 == 0 -> v5 == 0, so the (buggy, non-decrementing)
   * "while (v5)" loop body never runs; a2 == 0 also skips the trailing
   * "if (v3)" repair block entirely. This is the only combination that is
   * guaranteed not to touch the uninitialized-variable hazards further
   * down in this recovered function. */
  CHECK_EQ(Building_ApplySiegeDamageToWallSections((int)(intptr_t)wall, 0), 0);
}

TEST(cov03_building, siege_damage_repair_block) {
  static unsigned char wall[512];
  memset(wall, 0, sizeof(wall));
  /* Wall-section health bytes (offsets 422..428) must be non-zero: the
   * repair block's inner do/while spins on
   * "!*(byte*)(a1 + v8 + 422) && v7+1 < 6" with an uninitialized 'v7', and
   * with an all-zero buffer every v8 in [0,6] keeps the '!byte' side true
   * forever regardless of v7's garbage value -> real infinite loop
   * (verified empirically). Giving every slot real health makes the loop
   * exit on its very first draw, independent of v7. */
  memset(wall + 422, 50, 7);
  /* a2 in [1,99]: v5 stays 0 (loop skipped) but v3 == a2 != 0, so the
   * trailing repair block executes. That block also reads an uninitialized
   * local ('v10') as a pointer offset per the decompiler's own
   * "possibly undefined" annotation; run it in isolation so a crash here
   * cannot cost coverage recorded by other tests. */
  TOUCH(Building_ApplySiegeDamageToWallSections((int)(intptr_t)wall, 5));
}

/* Building_NewAt is intentionally NOT exercised here: it unconditionally
 * delegates to Building_New, which immediately dereferences
 * `(unsigned __int16 *)(gameData + 1400*a1 + 14*a2)` via
 * Map_GetTileSurfaceClassOrUnexplored. `gameData` is a runtime-allocated
 * base address (set up by Game_Init, itself unsafe/out of scope to invoke
 * here) that stays 0 for the whole coverage binary since nothing in this
 * shared test suite calls Game_Init; with gameData == 0 that dereference
 * reads a small fixed address that is not mapped in this process, so any
 * call into Building_New is a guaranteed segfault. Left uncovered rather
 * than pay for a guaranteed crash for zero net coverage. */

/* ---- Unit_NewTurnRegen ---- */
TEST(cov03_unit, new_turn_regen) {
  unsigned char unit[512];
  memset(unit, 0, sizeof(unit));

  /* result[429] == 0 -> skip the morale-recovery decrement branch. */
  TOUCH(Unit_NewTurnRegen(unit));

  /* result[429] != 0, decrementing to 0 -> ++result[421] branch. */
  unit[429] = 1;
  unit[421] = 0;
  TOUCH(Unit_NewTurnRegen(unit));
  CHECK_EQ(unit[421], 1);

  /* result[429] decrementing but not reaching 0. */
  unit[429] = 5;
  TOUCH(Unit_NewTurnRegen(unit));

  /* Fatigue bytes (offsets 0..6) below 0x64 -> both the +10 branch and the
   * clamp-to-100 branch (start near the ceiling). */
  memset(unit, 0, 7);
  unit[0] = 0;
  unit[1] = 60;
  unit[2] = 100; /* already >= 0x64: skip both inner branches for this byte */
  TOUCH(Unit_NewTurnRegen(unit));
}

/* ---- UnitSlot_NeedsMoraleRecovery ---- */
TEST(cov03_unit, needs_morale_recovery) {
  __int16 slot[8];
  memset(slot, 0, sizeof(slot));

  /* Executable-backed unit type 18 has flags bit 2 set. */
  slot[0] = 18;
  *((char *)slot + 11) = 3;
  CHECK(UnitSlot_NeedsMoraleRecovery(slot));
  *((char *)slot + 11) = 9;
  CHECK(!UnitSlot_NeedsMoraleRecovery(slot));

  slot[0] = 0;
  *((char *)slot + 11) = 5;
  CHECK(UnitSlot_NeedsMoraleRecovery(slot));
  *((char *)slot + 11) = 15;
  CHECK(!UnitSlot_NeedsMoraleRecovery(slot));
}

/* ---- Building_CalcGarrisonAverageHealthPercent / UI_DrawUnitStatsValues ---- */
TEST(cov03_building, garrison_health_percent) {
  /* a1 is a plain 'int' address; use a static buffer so truncating its
   * address to a DWORD and back stays valid on this 64-bit host. */
  static unsigned char building[512];
  memset(building, 0, sizeof(building));
  building[422] = 10;
  building[423] = 20;
  building[424] = 30;
  building[425] = 40;
  building[426] = 50;
  building[427] = 60;
  building[428] = 70;
  TOUCH(Building_CalcGarrisonAverageHealthPercent((int)(intptr_t)building));
  TOUCH(UI_DrawUnitStatsValues((int)(intptr_t)building));
}

/* ---- Building_CanStartUpgrade ---- */
TEST(cov03_building, can_start_upgrade) {
  unsigned char building[512];
  memset(building, 0, sizeof(building));

  /* a1[421] < 2, a1[421] < (a1[444]&7)-1, !a1[429] -> true. */
  building[421] = 0;
  building[444] = 3;
  building[429] = 0;
  CHECK(Building_CanStartUpgrade(building));

  /* a1[421] >= 2 -> short-circuit false. */
  building[421] = 2;
  CHECK(!Building_CanStartUpgrade(building));

  /* a1[421] < 2 but not < (a1[444]&7)-1 -> false. */
  building[421] = 1;
  building[444] = 0;
  CHECK(!Building_CanStartUpgrade(building));

  /* a1[421] < 2, satisfies the level check, but a1[429] != 0 -> false. */
  building[421] = 0;
  building[444] = 7;
  building[429] = 1;
  CHECK(!Building_CanStartUpgrade(building));
}

/* ---- Timer_InitPerfCounterFrequency / Time_Now / Timer_BusyWaitWithCallback ---- */
TEST(cov03_timer, perf_counter_and_time_now) {
  extern LARGE_INTEGER Frequency;
  LARGE_INTEGER saved_frequency = Frequency;

  TOUCH(Timer_InitPerfCounterFrequency());
  CHECK_EQ(Frequency.QuadPart, 10000);
  TOUCH(Time_Now(0, 0));

  /* Keep explicit coverage for Time_Now's pre-initialization fallback. */
  Frequency.QuadPart = 0;
  TOUCH(Time_Now(0, 0));
  Frequency = saved_frequency;

  /* Very small deadline delta, no callback -> loop body without the
   * callback branch, exits promptly. */
  TOUCH(Timer_BusyWaitWithCallback(0, 0, 0));
}

static int cov03_busywait_calls = 0;
static void cov03_busywait_cb(void) { ++cov03_busywait_calls; }

TEST(cov03_timer, busy_wait_with_callback) {
  LARGE_INTEGER saved_frequency = Frequency;

  Timer_InitPerfCounterFrequency();
  /* Two recovered ticks are about 20 ms in the 100 Hz timer domain. */
  TOUCH(Timer_BusyWaitWithCallback(2, (int)(uintptr_t)cov03_busywait_cb, 0));
  CHECK(cov03_busywait_calls > 0);
  Frequency = saved_frequency;
}

/* Castle_RequestManagementScreenExit is intentionally NOT exercised here:
 * it unconditionally calls UIWidget_PlayPressedReleaseAnimationWithDelay,
 * which busy-waits ~200 ms via DD_Pump/Time_Now and drives the
 * full SDL/X11 render-pump + vtable-method-invoke pipeline on g_RenderState.
 * That is both far too slow for a unit test and relies on rendering
 * subsystem state this harness never initializes, so it is left uncovered
 * rather than risk a multi-second hang (or a crash walking uninitialized
 * vtable slots) in the shared coverage binary.
 */

/* Castle_DrawAllAmbientAnimationLayers is intentionally NOT exercised here:
 * it loops over Castle_DrawAmbientAnimationLayer(1..10), whose case 5 is an
 * unconditional (no guard on g_SelectedBuildingRecord) call into
 * Castle_DrawAmbientAnimationSprite -> Compat_RenderDeviceDrawMenuSprite,
 * the real sprite-blit pipeline. That pipeline is not initialized in this
 * coverage harness (no display/vtable setup), so it cannot be reached
 * safely, and there is no input to this thin wrapper that steers around
 * case 5. Left uncovered rather than risk walking an uninitialized
 * render-device vtable. */
