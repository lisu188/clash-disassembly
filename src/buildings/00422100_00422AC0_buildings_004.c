/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE int Castle_InvokePrisonerPanel (int building_record, int callback_context, DWORD runtime_context);
CLASH95_TEST_VISIBLE int Castle_InvokeEconomyPanel (int building_record, int callback_context, DWORD runtime_context);
CLASH95_TEST_VISIBLE void BuildingGarrisonDialog_WriteActionWidgetRecord (unsigned char *record, int left, int top, int flags, int sprite_index_base, int sprite_index_selected_base, void *action_callback, const char *text_pl, const char *text_en, const char *text_de, const char *sound);
CLASH95_LOCAL int BuildingGarrisonDialog_Run (int building_record, int callback_context, DWORD runtime_context);
CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnCastleReturn (void);
CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnCastleEnter (void);
CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnBarracksEnter (void);
CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnBarracksDetail (void);
CLASH95_TEST_VISIBLE int Diagnostics_IsWorldMapActionVerbose (void);
CLASH95_TEST_VISIBLE int Diagnostics_ShouldTraceWorldMapActionStage (const char *stage);
CLASH95_TEST_VISIBLE void Diagnostics_TraceCastleHotspots (int surface_handle);

//----- (00422100) --------------------------------------------------------
int Castle_UpdateGateToggles(void)
{
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 420) & 1) != 0 )
    UI_MenuEntry_Disable((int)(intptr_t)&g_CastleNewBuildingMenu, 0);
  else
    UI_MenuEntry_Enable((int)(intptr_t)&g_CastleNewBuildingMenu, 0);
  if ( Building_CanStartUpgrade((unsigned __int8 *)(uintptr_t)g_SelectedBuildingRecord) )
    return UI_MenuEntry_Enable((int)(intptr_t)&g_CastleNewBuildingMenu, 2);
  else
    return UI_MenuEntry_Disable((int)(intptr_t)&g_CastleNewBuildingMenu, 2);
}
// 526A64: using guessed type int g_SelectedBuildingRecord;

typedef int (*CastleManagementPanelCallback)(int building_record, int callback_context, DWORD runtime_context);

CLASH95_TEST_VISIBLE int Castle_InvokePrisonerPanel(int building_record, int callback_context, DWORD runtime_context)
{
  (void)callback_context;
  return Building_ShowPrisonerManagementPanel(building_record, NULL, runtime_context);
}

CLASH95_TEST_VISIBLE int Castle_InvokeEconomyPanel(int building_record, int callback_context, DWORD runtime_context)
{
  (void)callback_context;
  (void)runtime_context;
  return BuildingEconomyDialog_Run(building_record);
}

CLASH95_TEST_VISIBLE void BuildingGarrisonDialog_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        void *action_callback,
        const char *text_pl,
        const char *text_en,
        const char *text_de,
        const char *sound)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BuildingGarrisonDialogUiSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
  *(_DWORD *)(record + 32) = (int)(uintptr_t)action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)text_pl;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)text_en;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)text_de;
  record[48] = 2;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound;
}

CLASH95_INTERNAL void BuildingGarrisonDialog_EnsureActionWidgets(int building_record)
{
  static const char sound_large[] = "duze";
  static const char text_back_pl[] = "Koniec";
  static const char text_back_en[] = "Back";
  static const char text_back_de[] = "Zuruck";
  static const char text_production_pl[] = "Produkcja";
  static const char text_production_en[] = "Production";
  static const char text_production_de[] = "Produzieren";
  static const char text_cure_pl[] = "Leczenie";
  static const char text_cure_en[] = "Cure";
  static const char text_cure_de[] = "Heilung";
  static const char text_training_pl[] = "Trening";
  static const char text_training_en[] = "Training";
  static const char text_training_de[] = "Training";
  static const char text_leave_pl[] = "Opusc koszary";
  static const char text_leave_en[] = "Leave barracks";
  static const char text_leave_de[] = "Kaserne verlassen";
  int addon_flags;

  addon_flags = *(unsigned char *)(uintptr_t)(building_record + 416);
  memset(BuildingGarrisonDialogActions, 0, sizeof(BuildingGarrisonDialogActions));
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    39,
    426,
    1,
    0,
    1,
    BuildingGarrisonDialog_RequestClose,
    text_back_pl,
    text_back_en,
    text_back_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    (addon_flags & 2) ? 155 : 1000,
    426,
    1,
    2,
    3,
    BuildingGarrisonDialog_ShowProductionDialog,
    text_production_pl,
    text_production_en,
    text_production_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    (addon_flags & 1) ? 272 : 1000,
    426,
    1,
    4,
    5,
    BuildingGarrisonDialog_ToggleRepairSelectedUnits,
    text_cure_pl,
    text_cure_en,
    text_cure_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    (addon_flags & 8) ? 385 : 1000,
    426,
    1,
    6,
    7,
    BuildingGarrisonDialog_ToggleTrainingSelectedUnits,
    text_training_pl,
    text_training_en,
    text_training_de,
    sound_large);
  BuildingGarrisonDialog_WriteActionWidgetRecord(
    BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    503,
    426,
    1,
    8,
    9,
    BuildingGarrisonDialog_BeginSelectedUnitsExit,
    text_leave_pl,
    text_leave_en,
    text_leave_de,
    sound_large);
  *(_DWORD *)(BuildingGarrisonDialogActions + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT) = -1;
}

CLASH95_LOCAL int BuildingGarrisonDialog_Run(int building_record, int callback_context, DWORD runtime_context)
{
  static const char castle_chr_dw12_s32[] = "castle.chr\\dw_12.s32";
  static const char castle_pog_dw12_s32[] = "castle.pog\\dw_12.s32";
  int (*saved_tick_callback)(void);
  int saved_resource_handle;
  int slot_index;
  int slot_record;
  int old_selected_slot;
  int resource_handle;
  _DWORD *surface;
  _DWORD *scratch_surface;
  _DWORD *sprite_set;
  const char *gfx_path;
  const char *sprite_path;
  const char *resource_base;
  int owner_index;
  int handled_widget;
  int selected_count;
  int primary_down;
  int secondary_down;

  (void)callback_context;
  Diagnostics_ResetFrameDumpOnBarracksEnter();
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] enter building=%08x runtime=%u\n", building_record, (unsigned int)runtime_context);
  g_BuildingGarrisonDialogActiveBuilding = building_record;
  owner_index = *(unsigned char *)(uintptr_t)(building_record + 2);
  g_BuildingGarrisonDialogUseChrTheme = PLAYER_RELIGION_FLAG(owner_index);
  g_BuildingGarrisonDialogSelectedUnitSpriteSet = 0;
  memset(g_BuildingGarrisonDialogSlotSpriteSets, 0, 12 * sizeof(g_BuildingGarrisonDialogSlotSpriteSets[0]));
  memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
  for ( slot_index = 0; slot_index < 12; ++slot_index )
    g_BuildingGarrisonDialogSlotAnimFrames[slot_index] = Rng_RandRange(0, 7);
  g_BuildingGarrisonDialogPendingExitCountdown = 0;
  g_BuildingGarrisonDialogSelectedSlotIndex = -1;

  surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, runtime_context);
  if ( surface )
    surface = Render_CreateSurface((int)(intptr_t)surface, 33, 64);
  g_GarrisonUnitCellSurface = (int)(uintptr_t)surface;
  scratch_surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, runtime_context);
  if ( scratch_surface )
    scratch_surface = Render_CreateSurface((int)(intptr_t)scratch_surface, 33, 64);

  resource_handle = Mem_Alloc(1024, 0, -1, runtime_context);
  if ( resource_handle )
    resource_handle = _wcpp_4_ctor_array__(resource_handle, 256);
  g_BuildingGarrisonDialogResourceHandle = resource_handle;

  gfx_path = g_BuildingGarrisonDialogUseChrTheme ? aCastle_chrD_15 : aCastle_pogD_15;
  sprite_path = g_BuildingGarrisonDialogUseChrTheme ? castle_chr_dw12_s32 : castle_pog_dw12_s32;
  resource_base = g_BuildingGarrisonDialogUseChrTheme ? aCastle_chrD_16 : aCastle_pogD_16;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    (char *)gfx_path,
    0,
    (uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] background_loaded gfx=%s palette=%08x\n", gfx_path, g_BuildingGarrisonDialogResourceHandle);
  sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, runtime_context);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, sprite_path);
  g_BuildingGarrisonDialogUiSpriteSet = (int)(uintptr_t)sprite_set;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] ui_sprites_loaded path=%s sprite_set=%08x\n", sprite_path, g_BuildingGarrisonDialogUiSpriteSet);
  Palette_LoadOrBuildBlendLookupTable((CHAR *)resource_base, g_BuildingGarrisonDialogResourceHandle, g_BuildingGarrisonDialogUseChrTheme, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] palette_loaded base=%s\n", resource_base);
  Render_LoadResourceSprite_v4(5, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  Render_LoadResourceSprite_v4(7, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, 0, 0, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] resource_sprites_loaded cursor_base=%d\n", g_ActiveWidgetSpriteTableIndex);
  RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, g_BuildingGarrisonDialogResourceHandle, 0, runtime_context);
  UI_SetActiveWidgetTable(8);
  BuildingGarrisonDialog_EnsureActionWidgets(building_record);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] action_widgets_ready\n");
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates((_DWORD *)BuildingGarrisonDialogActions);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] action_widgets_drawn\n");
  BuildingGarrisonDialog_RebuildSlotSprites(20, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] slot_sprites_rebuilt\n");
  BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_panel_assets_rebuilt\n");
  BuildingGarrisonDialog_DrawSelectedUnitPanel();
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_panel_drawn\n");
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, 20);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  Render_Present((int)(intptr_t)g_RenderState);
  Render_Pump();
  Render_Present((int)(intptr_t)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] initial_present_done\n");

  g_BuildingGarrisonDialogCloseRequested = 0;
  saved_tick_callback = g_ActiveDialogAnimationTickHook;
  g_ActiveDialogAnimationTickHook = (int (*)(void))BuildingGarrisonDialog_TickAnimations;
  while ( !g_BuildingGarrisonDialogCloseRequested && !Input_IsKeyPressed(1) )
  {
    BuildingGarrisonDialog_TickAnimations((double)runtime_context);
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    g_RenderDevice = &g_MainRenderDevice;
    handled_widget = UIWidgetTable_PollHoverAndActions((_DWORD *)BuildingGarrisonDialogActions, runtime_context);
    if ( handled_widget )
      continue;

    slot_index = BuildingGarrisonDialog_HitTestSlotGrid();
    if ( slot_index == -1 )
      continue;
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * slot_index;
    primary_down = DD_IsFlipping((int)(intptr_t)g_RenderState);
    secondary_down = DD_IsLost((int)(intptr_t)g_RenderState);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(
        stderr,
        "[barracks] slot_hit idx=%d primary=%d secondary=%d type=%d selected=%d\n",
        slot_index,
        primary_down,
        secondary_down,
        *(__int16 *)(uintptr_t)(slot_record + 18),
        g_BuildingGarrisonDialogSelectedSlots[slot_index]);
    if ( primary_down && *(__int16 *)(uintptr_t)(slot_record + 18) != -1 )
    {
      selected_count = BuildingGarrisonDialog_CountSelectedSlots();
      if ( selected_count < 10 || g_BuildingGarrisonDialogSelectedSlots[slot_index] )
      {
        g_BuildingGarrisonDialogSelectedSlots[slot_index] = !g_BuildingGarrisonDialogSelectedSlots[slot_index];
        if ( Diagnostics_IsWorldMapClickTraceEnabled() )
          fprintf(
            stderr,
            "[barracks] slot_toggle idx=%d selected=%d selected_count_before=%d\n",
            slot_index,
            g_BuildingGarrisonDialogSelectedSlots[slot_index],
            selected_count);
        Audio_PlaySoundEffectByName("marker", 64);
        BuildingGarrisonDialog_DrawSlotGrid(slot_index);
        Render_Present((int)(intptr_t)g_RenderState);
      }
      while ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
      {
        DD_Pump((int)(intptr_t)g_RenderState, 0);
        BuildingGarrisonDialog_TickAnimations((double)runtime_context);
      }
    }
    else if ( secondary_down && *(__int16 *)(uintptr_t)(slot_record + 18) != -1 )
    {
      old_selected_slot = g_BuildingGarrisonDialogSelectedSlotIndex;
      if ( old_selected_slot != -1 )
      {
        g_BuildingGarrisonDialogSelectedSlotIndex = -1;
        BuildingGarrisonDialog_ReloadSlotSprite(old_selected_slot, old_selected_slot + 1, 20, runtime_context);
        BuildingGarrisonDialog_DrawSlotGrid(old_selected_slot);
      }
      g_BuildingGarrisonDialogSelectedSlotIndex = slot_index;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_begin idx=%d\n", slot_index);
      Diagnostics_ResetFrameDumpOnBarracksDetail();
      BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
      Render_Present((int)(intptr_t)g_RenderState);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_present idx=%d\n", slot_index);
      Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
      while ( DD_IsLost((int)(intptr_t)g_RenderState) )
      {
        DD_Pump((int)(intptr_t)g_RenderState, 0);
        BuildingGarrisonDialog_TickAnimations((double)runtime_context);
      }
      g_BuildingGarrisonDialogSelectedSlotIndex = -1;
      BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(0, 20, runtime_context);
      Render_Present((int)(intptr_t)g_RenderState);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] slot_detail_end idx=%d\n", slot_index);
    }
  }

  g_ActiveDialogAnimationTickHook = saved_tick_callback;
  DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogUiSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( g_BuildingGarrisonDialogSlotSpriteSets[slot_index] )
    {
      nfree_(g_BuildingGarrisonDialogSlotSpriteSets[slot_index]);
      g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = 0;
    }
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  if ( g_BuildingGarrisonDialogResourceHandle )
    nfree_(g_BuildingGarrisonDialogResourceHandle);
  g_BuildingGarrisonDialogResourceHandle = 0;
  if ( g_GarrisonUnitCellSurface )
  {
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_GarrisonUnitCellSurface, 2);
    g_GarrisonUnitCellSurface = 0;
  }
  if ( scratch_surface )
    RenderSurface_InvokeSlot0(scratch_surface, 2);
  saved_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, saved_resource_handle);
  return 0;
}

CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnCastleReturn(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_CASTLE_RETURN");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnCastleEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_CASTLE_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_INTERNAL void Diagnostics_ResetFrameDumpOnEconomyEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_ECONOMY_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnBarracksEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_LOCAL void Diagnostics_ResetFrameDumpOnBarracksDetail(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BARRACKS_DETAIL");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_INTERNAL void Diagnostics_ResetFrameDumpOnBattleEnter(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_DUMP_PRESENTED_FRAMES_RESET_ON_BATTLE_ENTER");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_ResetPresentedFrameDump();
}

CLASH95_INTERNAL void Diagnostics_PrimeBattleSafeCursorOnTurnLoop(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_BATTLE_SAFE_CURSOR_ON_TURN_LOOP");
    enabled = value && *value;
    checked = 1;
  }
  if ( enabled )
    Platform_DebugPrimeInputFallbackMouseState(560, 370, 0, 0);
}

CLASH95_INTERNAL int Diagnostics_CountBattleUnitsForOwner(int owner)
{
  int count;
  int offset;

  if ( !g_MapData )
    return 0;
  count = 0;
  for ( offset = 0; offset != 682; offset += 31 )
  {
    if ( *(__int16 *)(uintptr_t)(g_MapData + offset + 852) != -1
      && *(unsigned __int8 *)(uintptr_t)(g_MapData + offset + 854) == owner )
    {
      ++count;
    }
  }
  return count;
}

CLASH95_INTERNAL int Diagnostics_CountBattleUnitsTotal(void)
{
  int count;
  int offset;

  if ( !g_MapData )
    return 0;
  count = 0;
  for ( offset = 0; offset != 682; offset += 31 )
  {
    if ( *(__int16 *)(uintptr_t)(g_MapData + offset + 852) != -1 )
      ++count;
  }
  return count;
}

CLASH95_INTERNAL void Diagnostics_TraceBattleUnitSnapshot(const char *stage)
{
  int slot_index;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() || !g_MapData )
    return;
  for ( slot_index = 0; slot_index < 22; ++slot_index )
  {
    int unit_record = g_MapData + 852 + 31 * slot_index;
    int unit_type = *(__int16 *)(uintptr_t)unit_record;

    if ( unit_type == -1 )
      continue;
    fprintf(
      stderr,
      "[battle_units] %s idx=%d owner=%u type=%d tile=%u,%u ap=%u count=%u flags=0x%02x selected=%d current_player=%d viewport=%d,%d\n",
      stage,
      slot_index,
      (unsigned)*(unsigned char *)(uintptr_t)(unit_record + 2),
      unit_type,
      (unsigned)*(unsigned __int16 *)(uintptr_t)(unit_record + 4),
      (unsigned)*(unsigned __int16 *)(uintptr_t)(unit_record + 6),
      (unsigned)*(unsigned char *)(uintptr_t)(unit_record + 8),
      (unsigned)*(unsigned char *)(uintptr_t)(unit_record + 9),
      (unsigned)*(unsigned char *)(uintptr_t)(unit_record + 12),
      g_SelectedUnitIndex,
      g_CurrentPlayerIndex,
      *(_DWORD *)(uintptr_t)(g_MapData + 808),
      *(_DWORD *)(uintptr_t)(g_MapData + 812));
  }
  fflush(stderr);
}

CLASH95_INTERNAL int Diagnostics_CountBattleDeploymentBucketEntries(void)
{
  int count;
  int index;

  count = 0;
  for ( index = 0; index < 48; ++index )
  {
    if ( g_BattleDeploymentBucketStorage_5437DC[index] )
      ++count;
  }
  return count;
}

CLASH95_INTERNAL unsigned __int8 *BattleDeploymentBucketReadPointer(int byte_offset)
{
  return (unsigned __int8 *)(uintptr_t)(unsigned int)*(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + byte_offset);
}

CLASH95_INTERNAL int Diagnostics_IsBattleTileDrawTraceEnabled(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_BATTLE_TILE_DRAW");
    enabled = value && *value;
    checked = 1;
  }
  return enabled;
}

CLASH95_INTERNAL int Diagnostics_IsWorldMapClickTraceEnabled(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_WORLD_CLICK");
    enabled = value && *value && strcmp(value, "0");
    checked = 1;
  }
  return enabled;
}

CLASH95_TEST_VISIBLE int Diagnostics_IsWorldMapActionVerbose(void)
{
  static int checked;
  static int enabled;
  const char *value;

  if ( !checked )
  {
    value = getenv("CLASH95_TRACE_WORLD_ACTION_VERBOSE");
    enabled = value && *value && strcmp(value, "0");
    checked = 1;
  }
  return enabled;
}

CLASH95_TEST_VISIBLE int Diagnostics_ShouldTraceWorldMapActionStage(const char *stage)
{
  static unsigned int battle_input_loop_count;
  static unsigned int battle_move_preview_count;

  if ( !stage )
    return 0;
  if ( Diagnostics_IsWorldMapActionVerbose() )
    return 1;
  if ( !strncmp(stage, "action_widgets_after_", 21) )
    return 0;
  if ( !strncmp(stage, "selection_after_", 16) )
    return 0;
  if ( !strncmp(stage, "status_panel_", 13) && strcmp(stage, "status_panel_refresh_done") )
    return 0;
  if ( !strcmp(stage, "playgame_loop_top") )
    return 0;
  if ( !strcmp(stage, "playgame_after_player_info") )
    return 0;
  if ( !strcmp(stage, "battle_turn_loop_iter_top") )
    return 0;
  if ( !strcmp(stage, "battle_turn_loop_after_input_widgets") )
  {
    ++battle_input_loop_count;
    return battle_input_loop_count <= 32 || !(battle_input_loop_count & 0xFF);
  }
  if ( !strcmp(stage, "battle_move_track_enter")
    || !strcmp(stage, "battle_move_track_return")
    || !strcmp(stage, "battle_move_track_cost")
    || !strcmp(stage, "battle_move_execute_no_flip") )
  {
    ++battle_move_preview_count;
    return battle_move_preview_count <= 64 || !(battle_move_preview_count & 0xFF);
  }
  if ( !strncmp(stage, "battle_turn_loop_after_", 23)
    && strcmp(stage, "battle_turn_loop_after_input_widgets") )
  {
    return 0;
  }
  return 1;
}

CLASH95_INTERNAL unsigned int Diagnostics_SurfaceByteChecksum(int surface_handle)
{
  _DWORD *surface;
  unsigned char *pixels;
  unsigned int width;
  unsigned int height;
  unsigned int pixel_count;
  unsigned int step;
  unsigned int index;
  unsigned int checksum;

  surface = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
  if ( !surface )
    return 0;
  pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !pixels )
    return 0;
  width = *(unsigned __int16 *)surface;
  height = *((unsigned __int16 *)surface + 1);
  pixel_count = width * height;
  if ( !pixel_count )
    return 0;
  step = pixel_count / 1024;
  if ( !step )
    step = 1;
  checksum = 2166136261u;
  for ( index = 0; index < pixel_count; index += step )
    checksum = (checksum ^ pixels[index]) * 16777619u;
  return checksum;
}

CLASH95_TEST_VISIBLE void Diagnostics_TraceCastleHotspots(int surface_handle)
{
  _DWORD *surface;
  int hotspot;
  int x;
  int y;
  int pixel;
  int index;
  int count[8];
  int min_x[8];
  int min_y[8];
  int max_x[8];
  int max_y[8];

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  surface = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
  if ( !surface )
    return;
  for ( index = 0; index < 8; ++index )
  {
    count[index] = 0;
    min_x[index] = 640;
    min_y[index] = 480;
    max_x[index] = -1;
    max_y[index] = -1;
  }
  for ( y = 0; y < 480; ++y )
  {
    for ( x = 0; x < 640; ++x )
    {
      pixel = RenderSurface_InvokeSlot16ReadPixel(surface, x, y);
      if ( pixel < 248 || pixel > 255 )
        continue;
      index = pixel - 248;
      ++count[index];
      if ( x < min_x[index] )
        min_x[index] = x;
      if ( y < min_y[index] )
        min_y[index] = y;
      if ( x > max_x[index] )
        max_x[index] = x;
      if ( y > max_y[index] )
        max_y[index] = y;
    }
  }
  for ( hotspot = 248; hotspot <= 255; ++hotspot )
  {
    index = hotspot - 248;
    if ( !count[index] )
      continue;
    fprintf(
      stderr,
      "[castle] hotspot pixel=%d count=%d bounds=%d,%d..%d,%d center=%d,%d\n",
      hotspot,
      count[index],
      min_x[index],
      min_y[index],
      max_x[index],
      max_y[index],
      (min_x[index] + max_x[index]) / 2,
      (min_y[index] + max_y[index]) / 2);
  }
}

CLASH95_INTERNAL void Diagnostics_TraceWorldMapClickEvent(
        const char *stage,
        int tile_x,
        int tile_y,
        int left,
        int top,
        int selected_unit_index)
{
  int in_bounds;
  int building_index = -1;
  int building_owner = -1;
  int building_kind = -1;
  int building_construction = -1;
  int building_row = -1;
  int building_column = -1;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  in_bounds = tile_x >= 0
           && tile_x < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
           && tile_y >= 0
           && tile_y < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( in_bounds && MapTile_HasBuilding(tile_x, tile_y) )
  {
    building_index = *(unsigned __int16 *)(uintptr_t)TILE_INDEX(tile_x, tile_y) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( building_index >= 0 && building_index <= 100 )
    {
      int building_record = BUILDING_RECORD(building_index);

      building_row = *(unsigned __int8 *)(uintptr_t)(building_record + 0);
      building_column = *(unsigned __int8 *)(uintptr_t)(building_record + 1);
      building_owner = *(unsigned __int8 *)(uintptr_t)(building_record + 2);
      building_kind = *(unsigned __int8 *)(uintptr_t)(building_record + 4);
      building_construction = *(__int16 *)(uintptr_t)(building_record + 16);
    }
  }
  fprintf(
    stderr,
    "[world_click] %s cursor=%d,%d tile=%d,%d left=%d top=%d selected=%d current_player=%d viewed_player=%d turn_owner=%d flipping=%d lost=%d own_stack=%d enemy_stack=%d building=%d own_building=%d enemy_building=%d building_idx=%d building_owner=%d building_kind=%d building_construction=%d building_origin=%d,%d port=%d site=%d in_bounds=%d\n",
    stage,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    tile_x,
    tile_y,
    left,
    top,
    selected_unit_index,
    g_CurrentPlayerIndex,
    VIEWED_PLAYER_INDEX,
    TURN_OWNER_PLAYER_INDEX,
    DD_IsFlipping((int)(intptr_t)&g_RenderState),
    DD_IsLost((int)(intptr_t)&g_RenderState),
    in_bounds ? MapTile_HasOwnUnitStack(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasVisibleEnemyUnitStack(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasBuilding(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasOwnBuilding(tile_x, tile_y) : 0,
    in_bounds ? MapTile_HasEnemyBuilding(tile_x, tile_y) : 0,
    building_index,
    building_owner,
    building_kind,
    building_construction,
    building_row,
    building_column,
    in_bounds ? Port_IsInsideFootprint(tile_x, tile_y) : 0,
    in_bounds ? MapTile_GetReligiousSiteCategory(tile_x, tile_y) : 0,
    in_bounds);
}

CLASH95_INTERNAL void Diagnostics_TraceBattlefieldClickEvent(
        const char *stage,
        int local_x,
        int local_y,
        int tile_x,
        int tile_y,
        int occupant_slot)
{
  int selected_type = -1;
  int occupant_type = -1;
  int occupant_owner = -1;
  int occupant_ap = -1;
  int occupant_flags = -1;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() || !g_MapData )
    return;
  if ( g_SelectedUnitIndex >= 0 && g_SelectedUnitIndex < 22 )
    selected_type = *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  if ( occupant_slot >= 0 && occupant_slot < 22 )
  {
    int occupant_record = g_MapData + 31 * occupant_slot;

    occupant_type = *(__int16 *)(uintptr_t)(occupant_record + 852);
    occupant_owner = *(unsigned __int8 *)(uintptr_t)(occupant_record + 854);
    occupant_ap = *(unsigned __int8 *)(uintptr_t)(occupant_record + 860);
    occupant_flags = *(unsigned __int8 *)(uintptr_t)(occupant_record + 864);
  }
  fprintf(
    stderr,
    "[battle_click] %s cursor=%d,%d local=%d,%d tile=%d,%d viewport=%d,%d selected=%d selected_type=%d current_player=%d occupant=%d occupant_type=%d occupant_owner=%d occupant_ap=%d occupant_flags=0x%02x shoot=%d charge=%d flipping=%d lost=%d\n",
    stage,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    local_x,
    local_y,
    tile_x,
    tile_y,
    *(_DWORD *)(uintptr_t)(g_MapData + 808),
    *(_DWORD *)(uintptr_t)(g_MapData + 812),
    g_SelectedUnitIndex,
    selected_type,
    g_CurrentPlayerIndex,
    occupant_slot,
    occupant_type,
    occupant_owner,
    occupant_ap,
    occupant_flags,
    g_Battle_ShootModeEnabled,
    g_UnitBattleChargeModeActive_532060,
    DD_IsFlipping((int)(intptr_t)&g_RenderState),
    DD_IsLost((int)(intptr_t)&g_RenderState));
}

CLASH95_INTERNAL void Diagnostics_TraceWorldMapActionEvent(
        const char *stage,
        int selected_unit_index,
        int detail_a,
        int detail_b,
        int detail_c)
{
  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  if ( !Diagnostics_ShouldTraceWorldMapActionStage(stage) )
    return;
  fprintf(
    stderr,
    "[world_action] %s selected=%d a=%d b=%d c=%d cursor=%d,%d flipping=%d lost=%d\n",
    stage,
    selected_unit_index,
    detail_a,
    detail_b,
    detail_c,
    g_MouseCursorRawX >> g_CursorCoordShift,
    g_MouseCursorRawY >> g_CursorCoordShift,
    DD_IsFlipping((int)(intptr_t)&g_RenderState),
    DD_IsLost((int)(intptr_t)&g_RenderState));
  fflush(stderr);
}

CLASH95_INTERNAL int Diagnostics_UnitStackIndexFromRecord(int stack_record)
{
  int stack_table_base;
  int stack_table_delta;

  if ( !gameData || !stack_record )
    return -1;
  stack_table_base = gameData + UNIT_STACK_TABLE_OFFSET;
  stack_table_delta = stack_record - stack_table_base;
  if ( stack_table_delta < 0 || stack_table_delta % UNIT_STACK_STRIDE != 0 )
    return -1;
  stack_table_delta /= 725;
  if ( stack_table_delta < 0 || stack_table_delta >= UNIT_STACK_TABLE_COUNT )
    return -1;
  return stack_table_delta;
}

CLASH95_INTERNAL void Diagnostics_TraceBootstrapEvent(const char *stage)
{
  if ( !getenv("CLASH95_TRACE_BOOTSTRAP") )
    return;
  fprintf(stderr, "[bootstrap] %s\n", stage);
  fflush(stderr);
}

CLASH95_INTERNAL void Diagnostics_TraceWorldMapUnitSnapshot(const char *stage)
{
  int stack_index;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  for ( stack_index = 0; stack_index < UNIT_STACK_TABLE_COUNT; ++stack_index )
  {
    int stack_record = UNIT_STACK(stack_index);
    int first_unit_type = *(__int16 *)(uintptr_t)UNIT_STACK_SLOT(stack_record, 0);
    if ( first_unit_type != -1 && first_unit_type <= 0x28 )
    {
      int first_slot_record = UNIT_STACK_SLOT(stack_record, 0);

      fprintf(
        stderr,
        "[world_units] %s idx=%d owner=%u tile=%d,%d first=%d slots=%d first_ap=%u first_count=%u first_morale=%u first_fatigue=%u ap=%d path=%d hidden=%u\n",
        stage,
        stack_index,
        (unsigned)UNIT_STACK_OWNER_INDEX(stack_record),
        (int)UNIT_STACK_TILE_ROW(stack_record),
        (int)UNIT_STACK_TILE_COLUMN(stack_record),
        first_unit_type,
        Unit_GetSquadCount(stack_record),
        (unsigned)*(unsigned char *)(uintptr_t)(first_slot_record + 8),
        (unsigned)*(unsigned char *)(uintptr_t)(first_slot_record + 9),
        (unsigned)*(unsigned char *)(uintptr_t)(first_slot_record + 11),
        (unsigned)*(unsigned char *)(uintptr_t)(first_slot_record + 10),
        UnitStack_GetMinCurrentActionPoints(stack_record),
        *(_DWORD *)(uintptr_t)UNIT_STACK_PATH_BUFFER(stack_record),
        (unsigned)*(unsigned char *)(uintptr_t)(stack_record + 720));
      if ( getenv("CLASH95_TRACE_WORLD_UNIT_SLOTS") )
      {
        int slot_index;

        for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        {
          int slot_record = UNIT_STACK_SLOT(stack_record, slot_index);
          int unit_type = *(__int16 *)(uintptr_t)slot_record;

          if ( unit_type == -1 )
            break;
          fprintf(
            stderr,
            "[world_unit_slot] %s idx=%d slot=%d type=%d ap=%u count=%u morale=%u fatigue=%u order=%u flags=0x%02x\n",
            stage,
            stack_index,
            slot_index,
            unit_type,
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 8),
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 9),
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 11),
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 10),
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 12),
            (unsigned)*(unsigned char *)(uintptr_t)(slot_record + 13));
        }
      }
    }
  }
}

CLASH95_INTERNAL void Diagnostics_TraceWorldMapCursorSample(
        int tile_x,
        int tile_y,
        int left,
        int top,
        int selected_unit_index)
{
  static int initialized;
  static int last_cursor_x;
  static int last_cursor_y;
  static int last_flipping;
  static int last_lost;
  int cursor_x;
  int cursor_y;
  int flipping;
  int lost;

  if ( !Diagnostics_IsWorldMapClickTraceEnabled() )
    return;
  cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
  cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
  flipping = DD_IsFlipping((int)(intptr_t)&g_RenderState);
  lost = DD_IsLost((int)(intptr_t)&g_RenderState);
  if ( initialized
    && cursor_x == last_cursor_x
    && cursor_y == last_cursor_y
    && flipping == last_flipping
    && lost == last_lost )
  {
    return;
  }
  initialized = 1;
  last_cursor_x = cursor_x;
  last_cursor_y = cursor_y;
  last_flipping = flipping;
  last_lost = lost;
  fprintf(
    stderr,
    "[world_cursor] cursor=%d,%d tile=%d,%d left=%d top=%d selected=%d flipping=%d lost=%d\n",
    cursor_x,
    cursor_y,
    tile_x,
    tile_y,
    left,
    top,
    selected_unit_index,
    flipping,
    lost);
}

//----- (00422180) --------------------------------------------------------
int * Castle_OpenManagementScreen(DWORD buildingIndex, char a2)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  _DWORD *iconSpriteSet; // eax
  int v9; // ecx
  char *animPathSrc; // esi
  char *pathDst; // edi
  char srcChar; // al
  char nextChar; // al
  _DWORD *ambientSpriteSet; // eax
  int v15; // ecx
  _DWORD *statusSpriteSet; // eax
  int v17; // ecx
  _DWORD *Surface; // eax
  DWORD buildingRecordByteOffset; // ebp
  int v20; // edx
  int v21; // ecx
  char *v22; // ebx
  int activeTooltipId; // esi
  int v24; // edx
  int v25; // ecx
  _DWORD *menuSpriteSet; // eax
  char savedScreenSurfaceByte; // bl
  int v28; // ecx
  int v29; // ecx
  int *result; // eax
  int v31; // ecx
  int v32; // ecx
  int v34; // ecx
  int savedCallbackResourceHandle; // edx
  int v37; // ecx
  _DWORD *newScreenSurface; // eax
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int tooltipNameIndex; // eax
  char spritePath[20]; // [esp+0h] [ebp-38h] BYREF
  int savedMusicState; // [esp+14h] [ebp-24h]
  int (*savedRenderHook)(); // [esp+18h] [ebp-20h]
  int savedResourceHandle; // [esp+1Ch] [ebp-1Ch]
  CastleManagementPanelCallback castle_panel_callback;
  int castle_loop_iterations;

  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] open_enter building_idx=%u current_player=%d\n", (unsigned int)buildingIndex, g_CurrentPlayerIndex);
  Diagnostics_ResetFrameDumpOnCastleEnter();
  savedResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, (char *)Castle_RebuildSceneBuffers == (char *)Render_DefaultRH);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Castle_RebuildSceneBuffers;
  Debug_Log(v4, a2, buildingIndex, (int)(intptr_t)aSetrhS08x_6);
  TextSprite_ReleaseAllResourceSlots();
  BuildingSpriteCache_Clear();
  UnitSpriteCache_FreeAllEntries(v5, buildingIndex);
  CSS_EmptySampleCache();
  Debug_Log(BUILDING_RECORD_SIZE * buildingIndex, a2, buildingIndex, (int)(intptr_t)aCastleD);
  g_SelectedBuildingRecord = BUILDING_RECORD(buildingIndex);
  g_ActiveCastleOwnerIsChristian = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(uintptr_t)(g_SelectedBuildingRecord + 2));
  savedMusicState = Audio_PauseMusicAndPlayLoopedSound(aCastle, *(unsigned __int8 *)(uintptr_t)(g_SelectedBuildingRecord + 2) + 1);
  CSS_PauseStreamReading();
  Castle_UpdateGateToggles();
  strcpy(spritePath, "zamek_1\\z_iko.s32");
  spritePath[6] = g_CurrentPlayerIndex + 49;
  iconSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v7, a2, buildingIndex);
  if ( iconSpriteSet )
    iconSpriteSet = DLXSpriteSet_Load(iconSpriteSet, spritePath);
  animPathSrc = aZamek_1Anim_s3;
  pathDst = spritePath;
  g_CastleSceneIconSpriteSet = (int)(intptr_t)iconSpriteSet;
  do
  {
    srcChar = *animPathSrc;
    *pathDst = *animPathSrc;
    if ( !srcChar )
      break;
    nextChar = animPathSrc[1];
    animPathSrc += 2;
    pathDst[1] = nextChar;
    pathDst += 2;
  }
  while ( nextChar );
  spritePath[6] = g_CurrentPlayerIndex + 49;
  ambientSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v9, a2, buildingIndex);
  if ( ambientSpriteSet )
    ambientSpriteSet = DLXSpriteSet_Load(ambientSpriteSet, spritePath);
  g_CastleAmbientSpriteSet = (int)(intptr_t)ambientSpriteSet;
  statusSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v15, a2, buildingIndex);
  if ( statusSpriteSet )
    statusSpriteSet = DLXSpriteSet_Load(statusSpriteSet, aDz_info_s32);
  g_CastleStatusSpriteSet = (int)(intptr_t)statusSpriteSet;
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_Pump();
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v17, a2, buildingIndex);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  buildingRecordByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
  g_CastleScreenSurface = (int)(intptr_t)Surface;
  Castle_RebuildSceneBuffers((int)(intptr_t)g_CastleScreenPaletteBuffer, buildingRecordByteOffset);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 3, (int)(intptr_t)g_CastleScreenPaletteBuffer, aMap_pal_0);
  DLXSpriteSet_DrawFormattedText(g_MapPanelSpriteSet, 4, (int)(intptr_t)g_CastleScreenPaletteBuffer, aMap_pal_1);
  DLXSpriteSet_DrawText(g_CastleStatusSpriteSet, 10, (int)(intptr_t)g_CastleScreenPaletteBuffer, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
  CSS_ResumeStreamReading();
  LOBYTE(v22) = -57;
  Tooltip_CaptureBackdrop(190, 455, 7, 455, 248);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[castle] first_present building_idx=%u\n", (unsigned int)buildingIndex);
  Diagnostics_TraceCastleHotspots(g_CastleScreenSurface);
  g_CastleDestroyConfirmed = 0;
  g_CastleScreenExitRequested = 0;
  g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  activeTooltipId = 0;
  castle_loop_iterations = 0;
  while ( !Input_IsKeyPressed(1) && !g_CastleScreenExitRequested )
  {
    ++castle_loop_iterations;
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)v22);
    Castle_UpdateAmbientAnimationLayers();
    Castle_ShowNewBuildingMenu();
    UI_RunHoverTooltipZones(g_CastleHoverTooltipZones);
    g_RenderDevice = &g_MainRenderDevice;
    Castle_EnsureCompositeStatusWidget();
    UIWidgetTable_PollHoverAndActions((_DWORD *)g_CastleStatusWidgetRecord, buildingRecordByteOffset);
    LOBYTE(v32) = g_CursorCoordShift;
    g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_CastleScreenSurface;
    v22 = (char *)(uintptr_t)(g_MouseCursorRawY >> g_CursorCoordShift);
    castle_panel_callback = NULL;
    switch ( RenderSurface_InvokeSlot16ReadPixel(
               (_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface,
               g_MouseCursorRawX >> g_CursorCoordShift,
               g_MouseCursorRawY >> g_CursorCoordShift) )
    {
      case 248:
        castle_panel_callback = Castle_InvokePrisonerPanel;
        if ( activeTooltipId != 134 )
        {
          activeTooltipId = 134;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 250:
        castle_panel_callback = Building_ShowGateDoorDialog_v3;
        if ( activeTooltipId != 153 )
        {
          v22 = UI_Locale_BuildingNames_J[(unsigned __int8)g_LanguageIndex];
          activeTooltipId = 153;
          Tooltip_ShowText(3, v22, spritePath[0]);
        }
        break;
      case 251:
        castle_panel_callback = Building_ShowGateDoorDialog_v1;
        if ( activeTooltipId != 156 )
        {
          activeTooltipId = 156;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_L[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 252:
        castle_panel_callback = Building_ShowGateDoorDialog_v4;
        if ( activeTooltipId != 159 )
        {
          activeTooltipId = 159;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_K[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 253:
        castle_panel_callback = Building_ShowGateDoorDialog_v2;
        if ( activeTooltipId != 166 )
        {
          activeTooltipId = 166;
          Tooltip_ShowText(3, UI_Locale_BuildingNames_M[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      case 254:
        castle_panel_callback = BuildingGarrisonDialog_Run;
        if ( activeTooltipId != 99 )
        {
          if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
            tooltipNameIndex = 3;
          else
            tooltipNameIndex = 8;
          v22 = (&g_CastleBuildingIconTooltipNames[3 * tooltipNameIndex])[(unsigned __int8)g_LanguageIndex];
          activeTooltipId = 99;
          Tooltip_ShowText(3, v22, spritePath[0]);
        }
        break;
      case 255:
        castle_panel_callback = Castle_InvokeEconomyPanel;
        if ( activeTooltipId != 135 )
        {
          activeTooltipId = 135;
          Tooltip_ShowText(3, g_CastleBuildingIconTooltipNames_FromPeasants[(unsigned __int8)g_LanguageIndex], spritePath[0]);
        }
        break;
      default:
        if ( activeTooltipId )
          Tooltip_RestoreBackdrop();
        activeTooltipId = 0;
        break;
    }
    if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && castle_panel_callback )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[castle] callback_trigger pixel=%d cursor=%d,%d loop=%d\n",
          RenderSurface_InvokeSlot16ReadPixel(
             (_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface,
             g_MouseCursorRawX >> g_CursorCoordShift,
             g_MouseCursorRawY >> g_CursorCoordShift),
          g_MouseCursorRawX >> g_CursorCoordShift,
          g_MouseCursorRawY >> g_CursorCoordShift,
          castle_loop_iterations);
      UI_SetActiveWidgetTable(8);
      Render_Pump();
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
      if ( g_CastleScreenSurface )
        RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface, 2);
      savedCallbackResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
      v22 = (char *)g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(v34, (char)(intptr_t)v22, buildingRecordByteOffset, (int)(intptr_t)aSetrhS08x_7);
      castle_panel_callback(g_SelectedBuildingRecord, 0, buildingRecordByteOffset);
      Debug_Log((int)(intptr_t)g_RenderHook, (char)(intptr_t)v22, buildingRecordByteOffset, (int)(intptr_t)aUnsetrh08x_7);
      g_RenderHook = (int (*)())v22;
      Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedCallbackResourceHandle);
      newScreenSurface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v37, (char)(intptr_t)v22, buildingRecordByteOffset);
      if ( newScreenSurface )
      {
        LOBYTE(v22) = -32;
        newScreenSurface = Render_CreateSurface((int)(intptr_t)newScreenSurface, SCREEN_WIDTH, SCREEN_HEIGHT);
      }
      g_CastleScreenSurface = (int)(intptr_t)newScreenSurface;
      Castle_RebuildSceneBuffers(v39, buildingRecordByteOffset);
      g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_CastleScreenSurface;
      RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_CastleScreenPaletteBuffer, v40, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v41, (char)(intptr_t)v22, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v42, (char)(intptr_t)v22, buildingRecordByteOffset);
      Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v43, (char)(intptr_t)v22, buildingRecordByteOffset);
      RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
      Render_Present((int)(intptr_t)g_RenderState);
    }
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[castle] open_exit building_idx=%u loops=%d esc=%d exit_requested=%d\n",
      (unsigned int)buildingIndex,
      castle_loop_iterations,
      Input_IsKeyPressed(1),
      g_CastleScreenExitRequested);
  Render_Pump();
  RenderState_LoadDefaultCursorSprite((int)(intptr_t)g_RenderState);
  Audio_SetMusicVolume(v24, 400);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  DLXSpriteSet_ReleaseAndClear(&g_MapPanelSpriteSet);
  menuSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v25, 144, buildingRecordByteOffset);
  if ( menuSpriteSet )
    menuSpriteSet = DLXSpriteSet_Load(menuSpriteSet, "menu.s32");
  savedScreenSurfaceByte = g_CastleScreenSurface;
  g_MapPanelSpriteSet = (int)(intptr_t)menuSpriteSet;
  if ( g_CastleScreenSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)g_CastleScreenSurface, 2);
  DLXSpriteSet_ReleaseAndClear(&g_CastleSceneIconSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleAmbientSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_CastleStatusSpriteSet);
  TextSprite_ReleaseAllResourceSlots();
  CSS_EmptySampleCache();
  Palette_LoadOrBuildBlendLookupTable(aMainmap_2, g_MapPalettePtr, v28, buildingRecordByteOffset);
  Audio_ResumeMusicAndStopLoopedSound(savedMusicState);
  Debug_Log(v29, savedScreenSurfaceByte, buildingRecordByteOffset, (int)(intptr_t)aUnsetrh08x_6);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedResourceHandle);
  Diagnostics_ResetFrameDumpOnCastleReturn();
  result = WorldMap_RenderHook(buildingRecordByteOffset);
  if ( g_CastleDestroyConfirmed )
    return (int *)(uintptr_t)Win_PlayModeChangeFrameTransition(aZniszcze, 1, v31, savedScreenSurfaceByte, buildingRecordByteOffset);
  return result;
}
// 4225A0: conditional instruction was optimized away because ecx.4!=0
// 4221CD: variable 'v4' is possibly undefined
// 4221DF: variable 'v5' is possibly undefined
// 422207: variable 'v6' is possibly undefined
// 422266: variable 'v7' is possibly undefined
// 4222AC: variable 'v9' is possibly undefined
// 4222C6: variable 'v15' is possibly undefined
// 4222FC: variable 'v17' is possibly undefined
// 422338: variable 'v20' is possibly undefined
// 422338: variable 'v21' is possibly undefined
// 4223F2: variable 'v24' is possibly undefined
// 422415: variable 'v25' is possibly undefined
// 422479: variable 'v28' is possibly undefined
// 422493: variable 'v29' is possibly undefined
// 422541: variable 'v32' is possibly undefined
// 42259A: variable 'v33' is possibly undefined
// 422618: variable 'v34' is possibly undefined
// 42262C: variable 'v35' is possibly undefined
// 42264D: variable 'v36' is possibly undefined
// 422657: variable 'v37' is possibly undefined
// 422674: variable 'v39' is possibly undefined
// 42268D: variable 'v40' is possibly undefined
// 42269C: variable 'v41' is possibly undefined
// 4226AB: variable 'v42' is possibly undefined
// 4226BA: variable 'v43' is possibly undefined
// 422866: variable 'v31' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513BD0: using guessed type char *off_513BD0[27];
// 513BE8: using guessed type char *off_513BE8[21];
// 513C00: using guessed type char *off_513C00[15];
// 513C0C: using guessed type char *off_513C0C[12];
// 513C18: using guessed type char *off_513C18[9];
// 513C24: using guessed type char *off_513C24[6];
// 513D08: using guessed type __int16 word_513D08[4];
// 513D98: using guessed type _DWORD dword_513D98[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 523F5C: using guessed type int dword_523F5C;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 526E70: using guessed type int g_ActiveCastleOwnerIsChristian;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;
// 526E78: using guessed type int g_CastleAmbientSpriteSet;
// 526E7C: using guessed type int g_CastleStatusSpriteSet;
// 526E80: using guessed type int g_CastleScreenExitRequested;
// 526E84: using guessed type int g_CastleDestroyConfirmed;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00422880) --------------------------------------------------------
int  Tooltip_CaptureBackdrop(int top, int bottom, int resourceHandle, int rightX, int regionMarkerId)
{
  int left; // edi
  int i; // esi
  _DWORD *Surface; // eax
  int result; // eax

  left = rightX;
  Render_ReleaseSurface(resourceHandle, resourceHandle);
  for ( i = rightX + UI_GetTextXOffset(resourceHandle); i >= (unsigned __int16)g_RenderDeviceClipRightX; --i )
    --left;
  if ( g_TooltipBackdropSurface )
    Compat_InvokeCompactSurfaceDestructor(g_TooltipBackdropSurface, 2);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, (char)rightX, resourceHandle);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, bottom - top + 1, i - left + 1);
  g_TooltipBackdropSurface = (int)(intptr_t)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)left, (unsigned __int16)top, bottom, i, 0, 0);
  g_TooltipLeft = left;
  g_TooltipTop = top;
  g_TooltipRight = i;
  g_TooltipBottom = bottom;
  result = regionMarkerId;
  g_TooltipResourceHandle = resourceHandle;
  g_TooltipCaptureArg5 = regionMarkerId;
  return result;
}
// 42289A: variable 'v7' is possibly undefined
// 4228D2: variable 'v8' is possibly undefined
// 51D4C2: using guessed type __int16 word_51D4C2;
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 526F08: using guessed type int g_TooltipResourceHandle;
// 526F0C: using guessed type int dword_526F0C;

//----- (00422960) --------------------------------------------------------
int Tooltip_ReleaseBackdropSurface(void)
{
  int result; // eax

  result = 0;
  if ( g_TooltipBackdropSurface )
    Compat_InvokeCompactSurfaceDestructor(g_TooltipBackdropSurface, 2);
  g_TooltipBackdropSurface = 0;
  return result;
}
// 526EF4: using guessed type int g_TooltipBackdropSurface;

//----- (004229A0) --------------------------------------------------------
void * Tooltip_ShowText(int a1, char *format, ...)
{
  int textSpriteSlot; // ebp
  char *bufferDst; // edi
  char *textSrc; // esi
  char v6; // al
  char v7; // al
  void *result; // eax
  void *savedRenderDevice; // [esp+0h] [ebp-20h]
  va_list args;

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  textSpriteSlot = g_ActiveTextSpriteSlot;
  RenderState_PumpIfRectInViewBounds(g_RenderState, g_TooltipTop, g_TooltipBottom, g_TooltipLeft, g_TooltipRight);
  Render_FillRect(
    (_DWORD *)(uintptr_t)g_TooltipBackdropSurface,
    0,
    0,
    0,
    g_TooltipBottom - g_TooltipTop,
    g_TooltipRight - g_TooltipLeft,
    g_TooltipTop,
    g_TooltipLeft);
  Render_ReleaseSurface(g_TooltipResourceHandle, textSpriteSlot);
  va_start(args, format);
  UI_DrawTextFmtV(g_TooltipTop, g_TooltipBottom, a1, g_TooltipLeft, format, args);
  va_end(args);
  bufferDst = (char *)&g_TooltipTextBuffer;
  Render_Present((int)(intptr_t)g_RenderState);
  textSrc = format;
  do
  {
    v6 = *textSrc;
    *bufferDst = *textSrc;
    if ( !v6 )
      break;
    v7 = textSrc[1];
    textSrc += 2;
    bufferDst[1] = v7;
    bufferDst += 2;
  }
  while ( v7 );
  Render_ReleaseSurface(textSpriteSlot, textSpriteSlot);
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 526F08: using guessed type int g_TooltipResourceHandle;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00422AC0) --------------------------------------------------------
int Tooltip_RestoreBackdrop(void)
{
  RenderState_PumpIfRectInViewBounds(g_RenderState, g_TooltipTop, g_TooltipBottom, g_TooltipLeft, g_TooltipRight);
  Render_FillRect(
    (_DWORD *)(uintptr_t)g_TooltipBackdropSurface,
    0,
    0,
    0,
    g_TooltipBottom - g_TooltipTop,
    g_TooltipRight - g_TooltipLeft,
    g_TooltipTop,
    g_TooltipLeft);
  return Render_Present((int)(intptr_t)g_RenderState);
}
// 526EF4: using guessed type int g_TooltipBackdropSurface;
// 526EF8: using guessed type int g_TooltipTop;
// 526EFC: using guessed type int g_TooltipLeft;
// 526F00: using guessed type int g_TooltipBottom;
// 526F04: using guessed type int g_TooltipRight;
// 544CD8: using guessed type _DWORD g_RenderState[9];
