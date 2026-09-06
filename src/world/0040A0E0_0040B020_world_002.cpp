/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "0040A0E0_0040B020_world_002_local.h"
#include "world_internal.h"
#include "world_state.h"
#include "world_shared_state.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL void WorldMap_WriteActionWidgetRecord (unsigned char *record, int left, int top, int flags, int sprite_index_base, int sprite_index_selected_base, int action_callback, const char *polish_label, const char *english_label, const char *german_label, const char *sound_name);
/* Keep this historical manifest/test identity after the active callback changes. */
__attribute__((used))
CLASH95_TEST_VISIBLE int WorldMap_DeferBuildingActionCallback (uintptr_t widget);
CLASH95_LOCAL void UnitBattle_WriteActionWidgetRecord (unsigned char *record, int left, int top, int flags, int sprite_index_base, int sprite_index_selected_base, int overlay_sprite_index, int action_callback, const char *polish_label, const char *english_label, const char *german_label, const char *sound_name);
/* Recovered save writer (persistence_002.c); intentionally absent from the
   generated persistence_api.h, so declare it here for the route-harness
   save_slot input-script token below. */
signed int  saveGame(int slotIndex, DWORD headerBuffer, double a3);

//----- (0040A0E0) --------------------------------------------------------
int  WorldMap_HandleBuilderActionMenu(int widget, int delayTicks, int a3, DWORD a4, double st7_0)
{
  int v7; // ecx
  int v9; // ecx
  int noBuilderTexts[7]; // [esp+0h] [ebp-1Ch] BYREF

  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_5);
    return Render_Begin((int)(intptr_t)g_RenderState, 0);
  }
  else
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
    if ( UnitStack_HasBuilder(g_SelectedUnitIndex) )
    {
      WorldMap_EnsureBuilderWidgetTables();
      UIWidgetTable_InitDrawStates((_DWORD*)(g_UI_YesNoDims));
      WorldMap_RedrawViewport(1);
      g_WorldMapBuilderMenuAction = -1;
      Diagnostics_TraceWorldMapActionEvent("builder_menu_enter", g_SelectedUnitIndex, -1, 0, 0);
      while ( 1 )
      {
        DD_Pump((int)(intptr_t)g_RenderState, a3);
        WorldMap_RedrawFrame(a3);
        if ( UI_TrySelectFriendlyStackUnderCursor() || !UIWidgetTable_PollHoverAndActions((_DWORD*)(g_UI_YesNoDims), 0x40u) && DD_IsFlipping((int)(intptr_t)g_RenderState) )
          break;
        a3 = g_WorldMapBuilderMenuAction;
        if ( g_WorldMapBuilderMenuAction == -1 )
          goto LABEL_13;
        switch ( g_WorldMapBuilderMenuAction )
        {
          case 0:
            Builder_StartRoadBuildMode(0x40u, st7_0);
            break;
          case 1:
            Treasure_TryDigHere(g_SelectedUnitIndex, g_WorldMapBuilderMenuAction, 0x40u, (char)(intptr_t)g_RenderState, 0, st7_0);
            break;
          case 2:
            BuildBuilding(3, v7, g_WorldMapBuilderMenuAction, st7_0);
            break;
          case 3:
            if ( UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
            {
              a3 = g_SelectedUnitIndex;
              if ( Building_New(0, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type0, 0) )
              {
                MiniMap_DrawTileCell(
                  (void *)(uintptr_t)*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET),
                  *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147176));
                Audio_PlaySoundEffectByName(aStruktur, 64);
              }
            }
            break;
          case 4:
            if ( !UnitStack_HasPeasantCargo(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
            {
              a3 = g_SelectedUnitIndex;
              if ( Building_New(1, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type1, 0) )
                Audio_PlaySoundEffectByName(aStruktur_0, 64);
            }
            break;
          case 5:
            a3 = g_SelectedUnitIndex;
            if ( Building_New(2, g_SelectedUnitIndex, st7_0, (char *)&g_Building_FootprintTemplate_Type2, 0) )
              Audio_PlaySoundEffectByName(aStruktur_1, 64);
            break;
          default:
            break;
        }
        if ( !DD_IsFlipping((int)(intptr_t)g_RenderState) )
        {
LABEL_13:
          if ( g_WorldMapBuilderMenuAction != -1 )
            break;
        }
        else
        {
          g_WorldMapBuilderMenuAction = -1;
        }
      }
      g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
      WorldMap_EnsureActionButtonWidgetTable();
      UIWidgetTable_InitDrawStates((_DWORD*)(g_WorldMapActionButtonWidgetTable));
      WorldMap_SyncSelectionForHumanPlayer(0x40u);
      WorldMap_RedrawViewport(1);
      WorldMap_RefreshUnitStatusPanel(0x40u);
      return UnitStackSelection_RefreshForSelectedStack(0x40u);
    }
    else
    {
      Audio_PlayButtonSound(aWrong_6);
      noBuilderTexts[0] = (int)(intptr_t)g_Text_NoBuilder[0];
      noBuilderTexts[1] = (int)(intptr_t)g_Text_NoBuilder[1];
      noBuilderTexts[2] = (int)(intptr_t)g_Text_NoBuilder[2];
      return UI_ShowInfoWindow(
               (const char*)(uintptr_t)(noBuilderTexts[(unsigned __int8)g_LanguageIndex]),
               1u,
               v9,
               a4,
               (int)(intptr_t)&noBuilderTexts[3],
               (int)(intptr_t)&g_Text_NoBuilder[3]);
    }
  }
}
// 40A182: variable 'a5' is possibly undefined
// 40A1DF: variable 'v9' is possibly undefined
// 40A24E: variable 'v7' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511BC0: using guessed type int g_UI_YesNoDims[3];
// 511D34: using guessed type char *g_Text_NoBuilder[3];
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 520308: using guessed type int dword_520308;
// 544CD8: using guessed type _DWORD g_RenderState[9];

CLASH95_LOCAL void WorldMap_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *polish_label,
        const char *english_label,
        const char *german_label,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_ActionButtonSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = 14;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)polish_label;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)english_label;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)german_label;
  record[48] = 1;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

CLASH95_TEST_VISIBLE int WorldMap_DeferBuildingActionCallback(uintptr_t widget)
{
  /* The authentic sub_40A0E0 callback still reopens the unresolved building-placement link surface. */
  (void)widget;
  return 0;
}

CLASH95_INTERNAL void WorldMap_EnsureActionButtonWidgetTable(void)
{
  static const char action_sound[] CLASH95_LOCAL_DATA_SYMBOL("action_sound.38", "WorldMap_EnsureActionButtonWidgetTable.action_sound") = "male";
  static const char label_map_mode_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_map_mode_pl.41", "WorldMap_EnsureActionButtonWidgetTable.label_map_mode_pl") = "Tryb mapy";
  static const char label_map_mode_en[] CLASH95_LOCAL_DATA_SYMBOL("label_map_mode_en.40", "WorldMap_EnsureActionButtonWidgetTable.label_map_mode_en") = "Map mode";
  static const char label_map_mode_de[] CLASH95_LOCAL_DATA_SYMBOL("label_map_mode_de.39", "WorldMap_EnsureActionButtonWidgetTable.label_map_mode_de") = "Kartenmodus";
  static const char label_next_unit_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_next_unit_pl.37", "WorldMap_EnsureActionButtonWidgetTable.label_next_unit_pl") = "Nast\x91" "pna jednostka";
  static const char label_next_unit_en[] CLASH95_LOCAL_DATA_SYMBOL("label_next_unit_en.36", "WorldMap_EnsureActionButtonWidgetTable.label_next_unit_en") = "Next unit";
  static const char label_next_unit_de[] CLASH95_LOCAL_DATA_SYMBOL("label_next_unit_de.35", "WorldMap_EnsureActionButtonWidgetTable.label_next_unit_de") = "N\x84" "chste Einheit";
  static const char label_next_building_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_next_building_pl.34", "WorldMap_EnsureActionButtonWidgetTable.label_next_building_pl") = "Nast\x91" "pna budowla";
  static const char label_next_building_en[] CLASH95_LOCAL_DATA_SYMBOL("label_next_building_en.33", "WorldMap_EnsureActionButtonWidgetTable.label_next_building_en") = "Next building";
  static const char label_next_building_de[] CLASH95_LOCAL_DATA_SYMBOL("label_next_building_de.32", "WorldMap_EnsureActionButtonWidgetTable.label_next_building_de") = "N\x84" "chstes Geb\x84" "ude";
  static const char label_join_units_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_join_units_pl.31", "WorldMap_EnsureActionButtonWidgetTable.label_join_units_pl") = "\x9C\x86" "czenie oddzia\x92\xA2" "w";
  static const char label_join_units_en[] CLASH95_LOCAL_DATA_SYMBOL("label_join_units_en.30", "WorldMap_EnsureActionButtonWidgetTable.label_join_units_en") = "Join units";
  static const char label_join_units_de[] CLASH95_LOCAL_DATA_SYMBOL("label_join_units_de.29", "WorldMap_EnsureActionButtonWidgetTable.label_join_units_de") = "Einheiten verbinden";
  static const char label_building_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_building_pl.28", "WorldMap_EnsureActionButtonWidgetTable.label_building_pl") = "Budowanie";
  static const char label_building_en[] CLASH95_LOCAL_DATA_SYMBOL("label_building_en.27", "WorldMap_EnsureActionButtonWidgetTable.label_building_en") = "Building";
  static const char label_building_de[] CLASH95_LOCAL_DATA_SYMBOL("label_building_de.26", "WorldMap_EnsureActionButtonWidgetTable.label_building_de") = "Geb\x84" "ude";
  static const char label_ambush_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_ambush_pl.25", "WorldMap_EnsureActionButtonWidgetTable.label_ambush_pl") = "Zasadzka";
  static const char label_ambush_en[] CLASH95_LOCAL_DATA_SYMBOL("label_ambush_en.24", "WorldMap_EnsureActionButtonWidgetTable.label_ambush_en") = "Ambush";
  static const char label_ambush_de[] CLASH95_LOCAL_DATA_SYMBOL("label_ambush_de.23", "WorldMap_EnsureActionButtonWidgetTable.label_ambush_de") = "Hinterhalt";
  int map_mode_flags;
  int join_units_flags;

  if ( g_WorldMapActionWidgetsInitialized )
    return;
  map_mode_flags = g_WorldMapMapModeWidgetFlags ? g_WorldMapMapModeWidgetFlags : 1;
  join_units_flags = g_WorldMapJoinUnitsWidgetFlags ? g_WorldMapJoinUnitsWidgetFlags : 1;
  memset(g_WorldMapActionButtonWidgetTable, 0, sizeof(g_WorldMapActionButtonWidgetTable));
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    416,
    400,
    map_mode_flags,
    0,
    1,
    (int)(uintptr_t)&WorldMap_HandleDeselectUnitAction,
    label_map_mode_pl,
    label_map_mode_en,
    label_map_mode_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    480,
    400,
    1,
    2,
    3,
    (int)(uintptr_t)&WorldMap_SelectNextActiveUnitStack,
    label_next_unit_pl,
    label_next_unit_en,
    label_next_unit_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    544,
    400,
    1,
    4,
    5,
    (int)(uintptr_t)&WorldMap_CenterViewOnNextOwnedBuildingWithUnit,
    label_next_building_pl,
    label_next_building_en,
    label_next_building_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    416,
    432,
    join_units_flags,
    6,
    7,
    (int)(uintptr_t)&WorldMap_ToggleSelectedUnitModeFlag,
    label_join_units_pl,
    label_join_units_en,
    label_join_units_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    480,
    432,
    1,
    8,
    9,
    (int)(uintptr_t)&WorldMap_HandleBuilderActionMenu,
    label_building_pl,
    label_building_en,
    label_building_de,
    action_sound);
  WorldMap_WriteActionWidgetRecord(
    g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    544,
    432,
    1,
    10,
    11,
    (int)(uintptr_t)&WorldMap_HandleHideUnitAction,
    label_ambush_pl,
    label_ambush_en,
    label_ambush_de,
    action_sound);
  *(_DWORD *)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * WORLD_MAP_ACTION_WIDGET_COUNT) = -1;
  g_WorldMapActionWidgetsInitialized = 1;
}

CLASH95_INTERNAL void WorldMap_EnsureBuilderWidgetTables(void)
{
  static const _BYTE builder_initial[322] = {
    0xa0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00,
    0xa0, 0xa0, 0x40, 0x00, 0x65, 0xcb, 0x4e, 0x00, 0x6b, 0xcb, 0x4e, 0x00, 0x70, 0xcb, 0x4e, 0x00,
    0x01, 0x77, 0xcb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x0c, 0x03, 0x52, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
    0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0x7c, 0xcb, 0x4e, 0x00, 0x84, 0xcb, 0x4e,
    0x00, 0x89, 0xcb, 0x4e, 0x00, 0x01, 0x8f, 0xcb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0x94, 0xcb,
    0x4e, 0x00, 0xa4, 0xcb, 0x4e, 0x00, 0xb5, 0xcb, 0x4e, 0x00, 0x01, 0xc1, 0xcb, 0x4e, 0x00, 0xa0,
    0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x15,
    0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0,
    0xa0, 0x40, 0x00, 0xc6, 0xcb, 0x4e, 0x00, 0xcc, 0xcb, 0x4e, 0x00, 0xd1, 0xcb, 0x4e, 0x00, 0x01,
    0xd6, 0xcb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0c, 0x03, 0x52, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0xdb, 0xcb, 0x4e, 0x00, 0xe4, 0xcb, 0x4e, 0x00,
    0xed, 0xcb, 0x4e, 0x00, 0x01, 0xf5, 0xcb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0xb0, 0x01, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0xfa, 0xcb, 0x4e,
    0x00, 0x00, 0xcc, 0x4e, 0x00, 0x07, 0xcc, 0x4e, 0x00, 0x01, 0x0c, 0xcc, 0x4e, 0x00, 0xff, 0xff,
    0xff, 0xff,
  };
  static const _BYTE road_initial[706] = {
    0x20, 0x02, 0x00, 0x00, 0x25, 0x02, 0x00, 0x00, 0x34, 0x02, 0x00, 0x00, 0x39, 0x02, 0x00, 0x00,
    0x40, 0x02, 0x00, 0x00, 0x45, 0x02, 0x00, 0x00, 0x22, 0x02, 0x00, 0x00, 0x23, 0x02, 0x00, 0x00,
    0x36, 0x02, 0x00, 0x00, 0x37, 0x02, 0x00, 0x00, 0x42, 0x02, 0x00, 0x00, 0x43, 0x02, 0x00, 0x00,
    0x64, 0x03, 0x66, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03,
    0x6b, 0x03, 0x65, 0x03, 0x68, 0x03, 0x63, 0x03, 0x63, 0x03, 0x62, 0x03, 0x62, 0x03, 0x64, 0x03,
    0x66, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03, 0x6b, 0x03,
    0x65, 0x03, 0x68, 0x03, 0x62, 0x03, 0x62, 0x03, 0x63, 0x03, 0x63, 0x03, 0x64, 0x03, 0x66, 0x03,
    0x66, 0x03, 0x6a, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03,
    0x6b, 0x03, 0x65, 0x03, 0x68, 0x03, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00,
    0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1b, 0x00, 0x00, 0x00,
    0x1b, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xeb, 0x4e,
    0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41,
    0x00, 0xe0, 0x54, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xdf, 0xeb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xeb, 0x4e, 0x00, 0xa0, 0x01, 0x00, 0x00, 0xb0,
    0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0xeb, 0x4e, 0x00,
    0xa0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00,
    0xf0, 0x50, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xee, 0xeb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x0c, 0x03, 0x52, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
    0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xeb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xeb, 0x4e, 0x00, 0xa0,
    0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x15,
    0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10,
    0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfd, 0xeb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0c, 0x03, 0x52, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xec, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0xb0, 0x01, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xec, 0x4e, 0x00, 0xff, 0xff,
    0xff, 0xff,
  };
  static const char widget_text_0[] = "\x44\x72\x6f\x67\x61";
  static const char widget_text_1[] = "\x52\x6f\x61\x64";
  static const char widget_text_2[] = "\x53\x74\x72\x61\xe1\x65";
  static const char widget_text_3[] = "\x6d\x61\x6c\x65";
  static const char widget_text_4[] = "\x50\x75\x92\x61\x70\x6b\x61";
  static const char widget_text_5[] = "\x54\x72\x61\x70";
  static const char widget_text_6[] = "\x46\x61\x6c\x6c\x65";
  static const char widget_text_7[] = "\x4b\x6f\x70\x61\x6e\x69\x65\x20\x73\x6b\x61\x72\x62\xa2\x77";
  static const char widget_text_8[] = "\x44\x69\x67\x20\x66\x6f\x72\x20\x74\x72\x65\x61\x73\x75\x72\x65";
  static const char widget_text_9[] = "\x53\x63\x68\x61\x74\x7a\x73\x75\x63\x68\x65";
  static const char widget_text_10[] = "\x57\x69\x65\xa7\x61";
  static const char widget_text_11[] = "\x4b\x65\x65\x70";
  static const char widget_text_12[] = "\x54\x75\x72\x6d";
  static const char widget_text_13[] = "\x54\x77\x69\x65\x72\x64\x7a\x61";
  static const char widget_text_14[] = "\x46\x6f\x72\x74\x72\x65\x73\x73";
  static const char widget_text_15[] = "\x46\x65\x73\x74\x75\x6e\x67";
  static const char widget_text_16[] = "\x5a\x61\x6d\x65\x6b";
  static const char widget_text_17[] = "\x43\x61\x73\x74\x6c\x65";
  static const char widget_text_18[] = "\x42\x75\x72\x67";
  _DWORD pointer_value;

  if ( g_BuilderRoadWidgetsInitialized )
    return;
  /* PE data bytes are retained; only actual pointer fields are relocated.
   * The 48-DWORD shore scan intentionally overlaps the live north marker. */
  memcpy(g_UI_YesNoDims, builder_initial, sizeof(builder_initial));
  memcpy(g_RoadBuildData, road_initial, sizeof(road_initial));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 12, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 28, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 32, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_0;
  memcpy(g_UI_YesNoDims + 36, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_1;
  memcpy(g_UI_YesNoDims + 40, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_2;
  memcpy(g_UI_YesNoDims + 44, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 49, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 65, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 81, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 85, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_4;
  memcpy(g_UI_YesNoDims + 89, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_5;
  memcpy(g_UI_YesNoDims + 93, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_6;
  memcpy(g_UI_YesNoDims + 97, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 102, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 118, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 134, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 138, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_7;
  memcpy(g_UI_YesNoDims + 142, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_8;
  memcpy(g_UI_YesNoDims + 146, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_9;
  memcpy(g_UI_YesNoDims + 150, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 155, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 171, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 187, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 191, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_10;
  memcpy(g_UI_YesNoDims + 195, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_11;
  memcpy(g_UI_YesNoDims + 199, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_12;
  memcpy(g_UI_YesNoDims + 203, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 208, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 224, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 240, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 244, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_13;
  memcpy(g_UI_YesNoDims + 248, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_14;
  memcpy(g_UI_YesNoDims + 252, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_15;
  memcpy(g_UI_YesNoDims + 256, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 261, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 277, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 293, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 297, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_16;
  memcpy(g_UI_YesNoDims + 301, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_17;
  memcpy(g_UI_YesNoDims + 305, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_18;
  memcpy(g_UI_YesNoDims + 309, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 314, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 184, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 200, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 204, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 208, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 212, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 216, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 221, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 237, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 253, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 257, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 261, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 265, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 269, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 274, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 290, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 306, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 310, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 314, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 318, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 322, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 327, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 343, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 359, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 363, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 367, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 371, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 375, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 380, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 396, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 412, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExitAfterWidgetPress;
  memcpy(g_RoadBuildData + 416, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 420, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 424, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 428, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 433, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 449, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 465, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 469, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 473, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 477, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 481, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 486, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 502, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 518, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 522, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 526, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 530, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 534, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 539, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 555, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 571, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 575, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 579, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 583, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 587, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 592, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 608, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 624, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 628, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 632, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 636, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 640, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 645, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 661, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 677, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 681, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 685, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 689, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 693, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 698, &pointer_value, sizeof(pointer_value));
  g_BuilderRoadWidgetsInitialized = 1;
}

CLASH95_LOCAL void UnitBattle_WriteActionWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int flags,
        int sprite_index_base,
        int sprite_index_selected_base,
        int overlay_sprite_index,
        int action_callback,
        const char *polish_label,
        const char *english_label,
        const char *german_label,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = flags;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BattleButtonsSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = overlay_sprite_index;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)polish_label;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)english_label;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)german_label;
  record[48] = 1;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

CLASH95_INTERNAL int UnitBattle_IsActionButtonWidgetAddress(uintptr_t widget)
{
  return widget >= (uintptr_t)g_UnitBattleActionWidgetTable
      && widget < (uintptr_t)(g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * UNIT_BATTLE_ACTION_WIDGET_COUNT);
}

CLASH95_INTERNAL void UnitBattle_EnsureActionButtonWidgetTable(void)
{
  static int initialized CLASH95_LOCAL_DATA_SYMBOL("initialized.22", "UnitBattle_EnsureActionButtonWidgetTable.initialized");
  static const char action_sound[] CLASH95_LOCAL_DATA_SYMBOL("action_sound.18", "UnitBattle_EnsureActionButtonWidgetTable.action_sound") = "male";
  static const char label_shoot_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_shoot_pl.21", "UnitBattle_EnsureActionButtonWidgetTable.label_shoot_pl") = "Ostrzal";
  static const char label_shoot_en[] CLASH95_LOCAL_DATA_SYMBOL("label_shoot_en.20", "UnitBattle_EnsureActionButtonWidgetTable.label_shoot_en") = "Shooting";
  static const char label_shoot_de[] CLASH95_LOCAL_DATA_SYMBOL("label_shoot_de.19", "UnitBattle_EnsureActionButtonWidgetTable.label_shoot_de") = "Schiesen";
  static const char label_next_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_next_pl.17", "UnitBattle_EnsureActionButtonWidgetTable.label_next_pl") = "Nastepna jednostka";
  static const char label_next_en[] CLASH95_LOCAL_DATA_SYMBOL("label_next_en.16", "UnitBattle_EnsureActionButtonWidgetTable.label_next_en") = "Next unit";
  static const char label_next_de[] CLASH95_LOCAL_DATA_SYMBOL("label_next_de.15", "UnitBattle_EnsureActionButtonWidgetTable.label_next_de") = "Nachste Einheit";
  static const char label_charge_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_charge_pl.14", "UnitBattle_EnsureActionButtonWidgetTable.label_charge_pl") = "Szarza";
  static const char label_charge_en[] CLASH95_LOCAL_DATA_SYMBOL("label_charge_en.13", "UnitBattle_EnsureActionButtonWidgetTable.label_charge_en") = "Ride";
  static const char label_charge_de[] CLASH95_LOCAL_DATA_SYMBOL("label_charge_de.12", "UnitBattle_EnsureActionButtonWidgetTable.label_charge_de") = "Reiten";
  static const char label_defence_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_defence_pl.11", "UnitBattle_EnsureActionButtonWidgetTable.label_defence_pl") = "Okopanie sie";
  static const char label_defence_en[] CLASH95_LOCAL_DATA_SYMBOL("label_defence_en.10", "UnitBattle_EnsureActionButtonWidgetTable.label_defence_en") = "Prepare to defence";
  static const char label_defence_de[] CLASH95_LOCAL_DATA_SYMBOL("label_defence_de.9", "UnitBattle_EnsureActionButtonWidgetTable.label_defence_de") = "Verteidigung vorbereiten";
  static const char label_retreat_pl[] CLASH95_LOCAL_DATA_SYMBOL("label_retreat_pl.8", "UnitBattle_EnsureActionButtonWidgetTable.label_retreat_pl") = "Odwrot z pola bitwy";
  static const char label_retreat_en[] CLASH95_LOCAL_DATA_SYMBOL("label_retreat_en.7", "UnitBattle_EnsureActionButtonWidgetTable.label_retreat_en") = "Retreat from the battlefield";
  static const char label_retreat_de[] CLASH95_LOCAL_DATA_SYMBOL("label_retreat_de.6", "UnitBattle_EnsureActionButtonWidgetTable.label_retreat_de") = "Ruckzug vom Schlachtfeld";
  int shoot_flags;
  int charge_flags;
  int retreat_flags;
  int exit_overlay_sprite;

  if ( initialized )
    return;
  shoot_flags = g_UnitBattleShootButtonState ? g_UnitBattleShootButtonState : 1;
  charge_flags = g_UnitBattleChargeButtonState ? g_UnitBattleChargeButtonState : 1;
  retreat_flags = g_UnitBattleExitButtonState ? g_UnitBattleExitButtonState : 1;
  exit_overlay_sprite = g_UnitBattleExitButtonOverlaySpriteIndex ? g_UnitBattleExitButtonOverlaySpriteIndex : 13;
  memset(g_UnitBattleActionWidgetTable, 0, sizeof(g_UnitBattleActionWidgetTable));
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    498,
    370,
    shoot_flags,
    7,
    8,
    0,
    (int)(uintptr_t)&UnitBattle_ToggleSelectedShootingMode,
    label_shoot_pl,
    label_shoot_en,
    label_shoot_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    561,
    370,
    1,
    1,
    2,
    0,
    (int)(uintptr_t)&UnitBattle_SelectNextControllableUnit,
    label_next_pl,
    label_next_en,
    label_next_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    498,
    401,
    charge_flags,
    3,
    4,
    0,
    (int)(uintptr_t)&UnitBattle_ToggleSelectedChargeMode,
    label_charge_pl,
    label_charge_en,
    label_charge_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    498,
    432,
    1,
    5,
    6,
    0,
    (int)(uintptr_t)&UnitBattle_HandlePrepareDefenceAction,
    label_defence_pl,
    label_defence_en,
    label_defence_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    561,
    401,
    1,
    9,
    10,
    11,
    (int)(uintptr_t)&UnitBattle_HandleRetreatAction,
    label_retreat_pl,
    label_retreat_en,
    label_retreat_de,
    action_sound);
  UnitBattle_WriteActionWidgetRecord(
    g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    505,
    0,
    retreat_flags,
    12,
    12,
    exit_overlay_sprite,
    (int)(uintptr_t)&UnitBattle_RequestActionLoopExit,
    0,
    0,
    0,
    action_sound);
  *(_DWORD *)(g_UnitBattleActionWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * UNIT_BATTLE_ACTION_WIDGET_COUNT) = -1;
  initialized = 1;
}

//----- (0040A360) --------------------------------------------------------
int __thiscall WorldMap_RefreshActionButtonBarState(void *this_)
{
  (void)this_;

  WorldMap_EnsureActionButtonWidgetTable();
  if ( g_SelectedUnitIndex == -1 )
  {
    g_WorldMapMapModeWidgetFlags = 1;
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
    g_WorldMapJoinUnitsModeActive = 0;
    g_WorldMapJoinUnitsWidgetFlags = 1;
  }
  else
  {
    g_WorldMapMapModeWidgetFlags = 2;
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_ActionBusy);
    if ( g_WorldMapJoinUnitsModeActive )
    {
      g_WorldMapJoinUnitsWidgetFlags = 2;
      goto LABEL_4;
    }
  }
  g_WorldMapJoinUnitsWidgetFlags = 1;
LABEL_4:
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  UIWidget_RefreshActionButtonState((uintptr_t)g_WorldMapActionButtonWidgetTable, 1);
  return UIWidget_RefreshActionButtonState((uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3), 1);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511D48: using guessed type int dword_511D48;
// 511DE7: using guessed type int dword_511DE7;
// 5202E0: using guessed type int dword_5202E0;
// 5202E8: using guessed type int dword_5202E8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A400) --------------------------------------------------------
int  WorldMap_LoadActionButtonSprites(int a1, char a2, DWORD a3)
{
  _DWORD *spriteSet; // eax
  int v5; // ecx

  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a1, a2, a3);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, "map_butt.s32");
  g_ActionButtonSpriteSet = (int)(intptr_t)spriteSet;
  WorldMap_EnsureActionButtonWidgetTable();
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates((_DWORD*)(g_WorldMapActionButtonWidgetTable));
  WorldMap_RedrawViewport(1);
  return v5;
}
// 40A431: variable 'v5' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 52030C: using guessed type int dword_52030C;

//----- (0040A450) --------------------------------------------------------
int __fastcall WorldMap_UnloadActionButtonSprites(int a1 CLASH95_UNUSED, int a2)
{
  DLXSpriteSet_ReleaseAndClear(&g_ActionButtonSpriteSet);
  return a2;
}
// 52030C: using guessed type int dword_52030C;

//----- (0040A460) --------------------------------------------------------
int  WorldMap_PollActionButtonWidgets(DWORD a1)
{
  int v1; // edx
  signed int widget_result;

  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  WorldMap_EnsureActionButtonWidgetTable();
  widget_result = UIWidgetTable_PollHoverAndActions((_DWORD*)(g_WorldMapActionButtonWidgetTable), a1);
  Diagnostics_TraceWorldMapActionEvent(
    "action_widgets_after_poll",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    widget_result);
  if ( widget_result == 1 )
    WorldMap_RefreshUnitStatusPanel(a1);
  Diagnostics_TraceWorldMapActionEvent(
    "action_widgets_after_refresh",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    widget_result);
  return v1;
}
// 40A479: variable 'v1' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;

//----- (0040A490) --------------------------------------------------------
void  WorldMap_SyncSelectionForHumanPlayer(DWORD a1)
{
  void *gameDataPtr; // ecx

  gameDataPtr = (void *)(uintptr_t)gameData;
  if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
  {
    if ( g_SelectedUnitIndex == -1 || *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180) == -1 )
    {
      g_SelectedUnitIndex = -1;
      WorldMap_RefreshActionButtonBarState((void *)(uintptr_t)gameData);
    }
    UnitStackSelection_SyncForCurrentSelection(gameDataPtr, a1);
  }
}
// 40A4ED: variable 'v1' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A500) --------------------------------------------------------
void  UnitStackSelection_SyncForCurrentSelection(void *a1, DWORD a2)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    if ( g_UnitStackSelectionActiveUnitIndex == -1 )
      return;
LABEL_4:
    UnitStackSelection_End(a1);
    return;
  }
  if ( Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) == 1 && g_UnitStackSelectionActiveUnitIndex != -1 )
    goto LABEL_4;
  if ( Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) > 1 && g_UnitStackSelectionActiveUnitIndex == -1 )
  {
    UnitStackSelection_BeginForSelectedStack(a2);
  }
  else if ( g_UnitStackSelectionActiveUnitIndex != g_SelectedUnitIndex && Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) > 1 )
  {
    UnitStackSelection_RefreshForSelectedStack(a2);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 5202E4: using guessed type int gameData;

//----- (0040A600) --------------------------------------------------------
void * WorldMap_DrawTurnBannerReveal(int animate)
{
  int SpriteForChar; // eax
  int aiSpriteForChar; // eax
  void *renderDevice; // edi
  DWORD renderSurfaceHandle; // ebp
  int v6 CLASH95_UNUSED; // edx
  int v7 CLASH95_UNUSED; // ecx
  int v8 CLASH95_UNUSED; // edx
  int v9 CLASH95_UNUSED; // ecx
  int startTime; // edi
  unsigned __int16 SpriteWidth; // ax
  int v12 CLASH95_UNUSED; // ecx
  __int16 bannerSpriteWidth; // ax
  __int16 v14 CLASH95_UNUSED; // cx
  __int16 SpriteHeight; // ax
  __int16 bannerSpriteHeight; // ax
  void *result; // eax
  unsigned __int16 revealRightEdge; // [esp+2Ch] [ebp-28h]
  unsigned __int16 bannerSpriteRight; // [esp+2Ch] [ebp-28h]
  unsigned __int16 revealLeftEdge; // [esp+34h] [ebp-20h]
  void *savedRenderDevice; // [esp+38h] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_WorldMapTurnBannerSpriteSet, g_CurrentPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(416, 400, SpriteForChar, 0);
  aiSpriteForChar = DLX_GetSpriteForChar(g_WorldMapTurnBannerSpriteSet, PLAYER_AI_INTELLIGENCE(g_CurrentPlayerIndex) + 5);
  renderDevice = g_RenderDevice;
  renderSurfaceHandle = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(568, 404, aiSpriteForChar, 1);
  Render_ReleaseSurface(7, renderSurfaceHandle);
  UI_DrawTextFmt((int)(intptr_t)renderDevice, 416, 608, 436, 3, (const char*)(uintptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_DISPLAY_NAME_OFFSET));
  if ( *(_DWORD *)(uintptr_t)(gameData + 147155) )
  {
    TextSprite_ActivateResourceSlot(3, 76, renderSurfaceHandle);
    UI_DrawText(421, 405, (int)(intptr_t)aTuraD);
  }
  startTime = Time_Now(0, 0);
  if ( animate )
  {
    while ( 1 )
    {
      int elapsed = Time_Now(0, 0) - startTime;
      SpriteWidth = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0);
      if ( elapsed >= SpriteWidth )
        break;
      bannerSpriteWidth = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0);
      revealLeftEdge = bannerSpriteWidth + 400 - elapsed;
      revealRightEdge = elapsed + 400;
      SpriteHeight = DLX_GetSpriteHeight(g_WorldMapTurnBannerSpriteSet, 0);
      Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 400, 416, SpriteHeight + 416, revealRightEdge, 0x1A0u, revealLeftEdge);
    }
  }
  bannerSpriteRight = DLX_GetSpriteWidth(g_WorldMapTurnBannerSpriteSet, 0) + 399;
  bannerSpriteHeight = DLX_GetSpriteHeight(g_WorldMapTurnBannerSpriteSet, 0);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 400, 416, bannerSpriteHeight + 416, bannerSpriteRight, 0x1A0u, 0x190u);
  result = savedRenderDevice;
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return result;
}
// 40A7B1: conditional instruction was optimized away because esi.4!=0
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202DC: using guessed type int dword_5202DC;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A820) --------------------------------------------------------
int  WorldMap_RenderPlayerTurnIntroScreen(char a1, DWORD a2)
{
  _DWORD *saved_primary_surface; // esi
  _DWORD *saved_map_surface; // edi
  int drawBufferRaw; // eax
  unsigned __int8 *drawBuffer; // esi
  unsigned int bannerVariant; // eax
  DWORD surfaceHandle; // ebp
  _BYTE gfxFilename[16]; // [esp+0h] [ebp-2Ch] BYREF
  int (*savedRenderHook)(int, char, DWORD); // [esp+10h] [ebp-1Ch]
  int savedResourceHandle; // [esp+14h] [ebp-18h]

  savedResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = Render_DefaultRH;
  Debug_Log(0, a1, a2, (int)(intptr_t)aSetrhS08x_1);
  // The turn banner reuses the world-map surface; preserve both pixel buffers
  // so the next map palette fade does not present stale banner pixels.
  saved_primary_surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, a1, a2);
  if ( saved_primary_surface )
    saved_primary_surface = Render_CreateSurface((int)(intptr_t)saved_primary_surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  saved_map_surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, a1, a2);
  if ( saved_map_surface )
    saved_map_surface = Render_CreateSurface((int)(intptr_t)saved_map_surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  if ( saved_primary_surface )
    Render_FillRect(0, saved_primary_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_map_surface )
    Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, saved_map_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  drawBufferRaw = Mem_Alloc(1024, 0, a1, a2);
  if ( drawBufferRaw )
    drawBufferRaw = _wcpp_4_ctor_array__(drawBufferRaw, 256);
  drawBuffer = (unsigned __int8 *)(uintptr_t)drawBufferRaw;
  bannerVariant = Rng_RandRange(1, 7);
  sprintf_((char*)(gfxFilename), "tura%d.gfx", bannerVariant);
  surfaceHandle = *(_DWORD *)(uintptr_t)(g_PrimaryRenderSurface + 184);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    (char *)gfxFilename,
    0,
    (uintptr_t)drawBuffer);
  Render_ReleaseSurface(6, surfaceHandle);
  Render_LoadResourceSprite_v4(6, drawBuffer, 0, (char)(intptr_t)drawBuffer, surfaceHandle);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  if ( g_LanguageIndex )
  {
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      UI_DrawTextFmt((int)(intptr_t)drawBuffer, 0, 639, 370, 3, (const char*)(uintptr_t)((int)(intptr_t)aPlayerSYourTur), PLAYER_DATA(g_CurrentPlayerIndex) + 4);
    }
    else if ( g_LanguageIndex == 2 )
    {
      UI_DrawTextFmt((int)(intptr_t)drawBuffer, 0, 639, 370, 3, (const char*)(uintptr_t)((int)(intptr_t)aSpielerS), PLAYER_DATA(g_CurrentPlayerIndex) + 4);
    }
  }
  else
  {
    UI_DrawTextFmt((int)(intptr_t)drawBuffer, 0, 639, 370, 3, (const char*)(uintptr_t)((int)(intptr_t)aGraczSTwojaTur), PLAYER_DATA(g_CurrentPlayerIndex) + 4);
  }
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, drawBuffer, 20);
  while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) )
  {
    WorldMap_RunInputScriptStep();
    DD_Pump((int)(intptr_t)g_RenderState, 20);
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  UI_EndDraw(6);
  if ( saved_map_surface )
    Render_FillRect(saved_map_surface, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_primary_surface )
    Render_FillRect(saved_primary_surface, (_DWORD *)&g_MainRenderDevice, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  if ( saved_map_surface )
    RenderSurface_InvokeSlot0(saved_map_surface, 2);
  if ( saved_primary_surface )
    RenderSurface_InvokeSlot0(saved_primary_surface, 2);
  j__nfree_();
  Debug_Log(0, (char)(intptr_t)g_RenderHook, 0, (int)(intptr_t)aUnsetrh08x_0);
  g_RenderHook = savedRenderHook;
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedResourceHandle);
}

int UI_LoadTurnBannerGfx(char a1, DWORD a2)
{
  return WorldMap_RenderPlayerTurnIntroScreen(a1, a2);
}
// 40A867: variable 'v2' is possibly undefined
// 40A883: variable 'v3' is possibly undefined
// 40A896: variable 'v5' is possibly undefined
// 40A8E7: variable 'v9' is possibly undefined
// 40AA32: variable 'v10' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AA60) --------------------------------------------------------
int  Game_AdvanceToNextPlayerTurn(int a1, char a2, DWORD loadContext, double gameTime)
{
  int previous_player_index;
  int current_player_is_human;
  int active_mission_index;
  int clips_memory;
  int used_memory;
  int unit_cache_entries;
  int building_cache_entries;

  (void)a1;
  (void)a2;

  Diagnostics_TraceWorldMapActionEvent("turn_advance_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
  Debug_Log(0, 0, loadContext, (int)(intptr_t)aNextPlayer);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  PLAYER_CAMERA_LEFT(g_CurrentPlayerIndex) = MAP_VIEW_LEFT;
  PLAYER_CAMERA_TOP(g_CurrentPlayerIndex) = MAP_VIEW_TOP;
  previous_player_index = g_CurrentPlayerIndex;
  do
    g_CurrentPlayerIndex = (g_CurrentPlayerIndex + 1) % 5;
  while ( !PLAYER_IS_ACTIVE(g_CurrentPlayerIndex) );
  TURN_OWNER_PLAYER_INDEX = g_CurrentPlayerIndex;
  Debug_Log(0, 0, loadContext, (int)(intptr_t)aPlayerD, g_CurrentPlayerIndex);
  current_player_is_human = PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_player_select",
    g_SelectedUnitIndex,
    previous_player_index,
    g_CurrentPlayerIndex,
    current_player_is_human);
  if ( current_player_is_human )
    VIEWED_PLAYER_INDEX = g_CurrentPlayerIndex;
  if ( previous_player_index > g_CurrentPlayerIndex )
  {
    ++GAME_TURN_COUNTER;
    Debug_Log(0, 0, loadContext, (int)(intptr_t)aNextTurnD, GAME_TURN_COUNTER);
    Map_AutoUpgradeVillages();
    Port_NewTurn(loadContext);
    clips_memory = Mem_GetTotalAllocatedBytes();
    Debug_Log(0, 0, loadContext, (int)(intptr_t)aClipsMemoryD, clips_memory);
    used_memory = Debug_GetUsedMemoryCount();
    Debug_Log(0, 0, loadContext, (int)(intptr_t)aUsedmemD_3, used_memory);
    unit_cache_entries = UnitSpriteCache_CountActiveEntries();
    Debug_Log(0, 0, loadContext, (int)(intptr_t)aUnitsCacheEntr, unit_cache_entries);
    building_cache_entries = BuildingSpriteCache_CountEntries();
    Debug_Log(0, 0, loadContext, (int)(intptr_t)aBuildingsCache, building_cache_entries);
  }
  MAP_VIEW_LEFT = PLAYER_CAMERA_LEFT(VIEWED_PLAYER_INDEX);
  MAP_VIEW_TOP = PLAYER_CAMERA_TOP(VIEWED_PLAYER_INDEX);
  Render_Pump();
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_render_pump",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  if ( current_player_is_human )
  {
    UI_LoadTurnBannerGfx((char)g_CurrentPlayerIndex, loadContext);
    g_SelectedUnitIndex = -1;
    Locale_DrawInteger();
    WorldMap_RenderHook(loadContext);
    Diagnostics_TraceWorldMapActionEvent(
      "turn_advance_after_human_banner",
      g_SelectedUnitIndex,
      g_CurrentPlayerIndex,
      current_player_is_human,
      GAME_TURN_COUNTER);
  }
  g_SelectedUnitIndex = -1;
  g_LastSelectedUnitIndex = -1;
  if ( current_player_is_human )
    WorldMap_RefreshActionButtonBarState((void *)(uintptr_t)(unsigned int)gameData);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_selection_reset",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  UnitStackSelection_SyncForCurrentSelection((void *)(uintptr_t)(unsigned int)gameData, 0xFFFFFFFF);
  WorldMap_RedrawViewport(1);
  if ( !current_player_is_human )
  {
    WorldMap_DrawTurnBannerReveal(1);
    Tooltip_RestoreBackdrop();
  }
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_side_ui",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  active_mission_index = ACTIVE_MISSION_INDEX;
  if ( !current_player_is_human )
  {
    if ( active_mission_index == -1 || active_mission_index == 19 || active_mission_index == 9 )
      AI_ComputeNationStrengthPercent(g_CurrentPlayerIndex, 0, 0xFFFFFFFF, gameTime);
  }
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_before_unit_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Debug_Log(0, 0, 0xFFFFFFFF, (int)(intptr_t)aAutoMovesBegin);
  Unit_NewTurn(0, (char)active_mission_index, 0xFFFFFFFF, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_unit_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Building_NewTurn(0, (unsigned __int8 *)(uintptr_t)(unsigned int)active_mission_index, 0xFFFFFFFF, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_building_new_turn",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Prisoner_SetInCastles(0, (char)active_mission_index, 0xFFFFFFFF);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_prisoners",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Queen_NewTurn(0, active_mission_index, current_player_is_human != 0, gameTime);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_after_queen",
    g_SelectedUnitIndex,
    active_mission_index,
    current_player_is_human,
    GAME_TURN_COUNTER);
  Debug_Log(0, 0, 0xFFFFFFFF, (int)(intptr_t)aAutoMovesEnd);
  WorldMap_RedrawViewport(1);
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Diagnostics_TraceWorldMapActionEvent(
    "turn_advance_before_present",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    current_player_is_human,
    GAME_TURN_COUNTER);
  return Render_Present((int)(intptr_t)g_RenderState);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AD40) --------------------------------------------------------
int * WorldMap_RenderHook(DWORD a1)
{
  int v1 CLASH95_UNUSED; // ecx
  void *v2; // ecx
  int *result; // eax

  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  Render_DrawSprite();
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  WorldMap_EnsureActionButtonWidgetTable();
  if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    UIWidgetTable_InitDrawStates((_DWORD*)(g_WorldMapActionButtonWidgetTable));
  else
    WorldMap_DrawTurnBannerReveal(0);
  WorldMap_RedrawViewport(1);
  UI_EndDraw(7);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  WorldMap_RefreshUnitStatusPanel(a1);
  UnitStackSelection_SyncForCurrentSelection(v2, a1);
  result = Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr, 20);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  return result;
}
// 40ADAD: variable 'v1' is possibly undefined
// 40ADB7: variable 'v2' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511D40: using guessed type _DWORD dword_511D40[2];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;

//----- (0040ADF0) --------------------------------------------------------
int  WorldMap_RedrawFrame(int a1, ...)
{
  int previous_resource_handle; // ecx
  int mission_index; // edx

  DD_Pump((int)(intptr_t)g_RenderState, 0);
  previous_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  Map_UpdateIdleAnimatedUnits();
  WorldMap_TickAmbientMapAnimations(a1);
  Map_UpdateConstructionSiteSwayAnimation(0);
  Map_UpdateIdleAnimatedBuildings(0);
  UI_UpdateTileBlinkFlash(0, 0);
  Noop_WorldMapFrameRedrawHook();
  mission_index = ACTIVE_MISSION_INDEX;
  if ( mission_index == 1 )
  {
    WorldMap_RedrawTileIfVisible(16, 11);
    return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
  }
  if ( mission_index != 11 )
    return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
  WorldMap_RedrawTileIfVisible(2, 44);
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
}
// 419030: using guessed type int nullsub_1(void);
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040AE80) --------------------------------------------------------
int  WorldMap_RedrawFrameForAIWhenEnabled(int a1)
{
  int result; // eax

  if ( !g_WorldMapFrameRedrawDisabled )
  {
    result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      return WorldMap_RedrawFrame(a1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 520310: using guessed type int dword_520310;

//----- (0040AEB0) --------------------------------------------------------
void WorldMap_DisableFrameRedraw(void)
{
  g_WorldMapFrameRedrawDisabled = 1;
}
// 520310: using guessed type int dword_520310;

//----- (0040AEC0) --------------------------------------------------------
void WorldMap_EnableFrameRedraw()
{
  g_WorldMapFrameRedrawDisabled = 0;
}
// 520310: using guessed type int dword_520310;

//----- (0040AED0) --------------------------------------------------------
_DWORD * WorldMap_LoadResources(char a1 CLASH95_UNUSED, DWORD loadContext)
{
  _DWORD *frameSpriteSet; // eax
  _DWORD *marksSpriteSet; // eax
  _DWORD *stepSpriteSet; // eax
  _DWORD *fogSpriteSet; // eax
  _DWORD *flagSpriteSet; // eax
  _DWORD *whirlSpriteSet; // eax
  _DWORD *turnBannerSpriteSet; // eax
  _DWORD *Surface; // eax
  int mapPalette; // eax

  TextSprite_ReleaseAllResourceSlots();
  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  frameSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( frameSpriteSet )
    frameSpriteSet = DLXSpriteSet_Load(frameSpriteSet, "frame.s32");
  g_ActiveUiSpriteSet = (int)(intptr_t)frameSpriteSet;
  marksSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( marksSpriteSet )
    marksSpriteSet = DLXSpriteSet_Load(marksSpriteSet, "marks.s32");
  g_MarksSpriteSet = (int)(intptr_t)marksSpriteSet;
  stepSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( stepSpriteSet )
    stepSpriteSet = DLXSpriteSet_Load(stepSpriteSet, "step.s32");
  g_MovePathStepSpriteSet = (int)(intptr_t)stepSpriteSet;
  fogSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( fogSpriteSet )
    fogSpriteSet = DLXSpriteSet_Load(fogSpriteSet, "fog.s32");
  g_FogOverlaySpriteSet = (int)(intptr_t)fogSpriteSet;
  flagSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( flagSpriteSet )
    flagSpriteSet = DLXSpriteSet_Load(flagSpriteSet, "flag.s32");
  g_FlagSpriteSet = (int)(intptr_t)flagSpriteSet;
  whirlSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( whirlSpriteSet )
    whirlSpriteSet = DLXSpriteSet_Load(whirlSpriteSet, "whirl.s32");
  g_WhirlSpriteSet = (int)(intptr_t)whirlSpriteSet;
  turnBannerSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( turnBannerSpriteSet )
    turnBannerSpriteSet = DLXSpriteSet_Load(turnBannerSpriteSet, "turakomp.s32");
  g_WorldMapTurnBannerSpriteSet = (int)(intptr_t)turnBannerSpriteSet;
  if ( !g_PrimaryRenderSurface )
  {
    Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, 0);
    if ( Surface )
      Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
    g_PrimaryRenderSurface = (int)(intptr_t)Surface;
  }
  mapPalette = Mem_Alloc(1024, 0, 0, 0);
  if ( mapPalette )
    mapPalette = Palette_LoadFromQueryHandle(mapPalette, (intptr_t)"map.pal");
  g_MapPalettePtr = mapPalette;
  Palette_LoadOrBuildBlendLookupTable(aMainmap, mapPalette, 0, loadContext);
  RenderState_LoadDefaultCursorSprite((int)(intptr_t)g_RenderState);
  return WorldMapTopMenu_LoadSpriteSet();
}
// 5202BC: using guessed type int dword_5202BC;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202DC: using guessed type int dword_5202DC;
// 5202E0: using guessed type int dword_5202E0;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040B020) --------------------------------------------------------
int  WorldMap_UnloadResources(DWORD allocContext)
{
  int v2; // ecx

  TextSprite_ReleaseAllResourceSlots();
  UnitSpriteCache_FreeAllEntries(v2, allocContext);
  BuildingSpriteCache_Clear();
  CSS_EmptySampleCache();
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_MarksSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_MovePathStepSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_FogOverlaySpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_TreeSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_FlagSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_WhirlSpriteSet);
  UI_FreeCurrentPlayerInfoSpriteSet();
  DLXSpriteSet_ReleaseAndClear(&g_WorldMapTurnBannerSpriteSet);
  j__nfree_();
  return WorldMapTopMenu_FreeSpriteSet();
}
// 40B027: variable 'v2' is possibly undefined
// 5202BC: using guessed type int dword_5202BC;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202D8: using guessed type int dword_5202D8;
// 5202DC: using guessed type int dword_5202DC;
// 5202F4: using guessed type int dword_5202F4;

CLASH95_INTERNAL void WorldMap_RunInputScriptStep(void)
{
  static int initialized CLASH95_LOCAL_DATA_SYMBOL("initialized.3", "WorldMap_RunInputScriptStep.initialized");
  static int trace_checked CLASH95_LOCAL_DATA_SYMBOL("trace_checked.5", "WorldMap_RunInputScriptStep.trace_checked");
  static int trace_enabled CLASH95_LOCAL_DATA_SYMBOL("trace_enabled.4", "WorldMap_RunInputScriptStep.trace_enabled");
  static int wait_reads CLASH95_LOCAL_DATA_SYMBOL("wait_reads.1", "WorldMap_RunInputScriptStep.wait_reads");
  static FILE *script_file CLASH95_LOCAL_DATA_SYMBOL("script_file.2", "WorldMap_RunInputScriptStep.script_file");
  char line[256];
  const char *script_path;

  if ( !trace_checked )
  {
    const char *trace_value = getenv("CLASH95_TRACE_WORLD_INPUT_SCRIPT");
    trace_enabled = trace_value && *trace_value;
    trace_checked = 1;
  }
  if ( !initialized )
  {
    initialized = 1;
    script_path = getenv("CLASH95_WORLD_INPUT_SCRIPT");
    if ( script_path && *script_path )
    {
      script_file = fopen(script_path, "r");
      if ( trace_enabled )
        fprintf(stderr, "[world_input] open path=%s ok=%d\n", script_path, script_file != NULL);
    }
  }
  if ( wait_reads > 0 )
  {
    if ( trace_enabled )
      fprintf(
        stderr,
        "[world_input] wait remaining=%d cursor=%d,%d selected=%d mask0=%d panel=%d\n",
        wait_reads,
        g_MouseCursorRawX >> g_CursorCoordShift,
        g_MouseCursorRawY >> g_CursorCoordShift,
        g_SelectedUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSelectionActiveUnitIndex);
    --wait_reads;
    return;
  }
  while ( script_file && fgets(line, sizeof(line), script_file) )
  {
    char command[32];
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int fields;
    int cursor_x;
    int cursor_y;

    fields = sscanf(line, " %31s %d %d %d %d %d", command, &a, &b, &c, &d, &e);
    if ( fields <= 0 || command[0] == '#' )
      continue;
    if ( strcmp(command, "wait") == 0 )
    {
      if ( fields >= 2 && a > 0 )
        wait_reads = a - 1;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=wait reads=%d cursor=%d,%d\n", a, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
      return;
    }
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( strcmp(command, "move") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=move target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "down") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=down target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 1, 0);
      return;
    }
    if ( strcmp(command, "up") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=up target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "click") == 0 && fields >= 3 )
    {
      int reads = fields >= 4 && c > 0 ? c : 2;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=click target=%d,%d cursor=%d,%d delta=%d,%d reads=%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y, reads);
      Platform_DebugPrimeInputFallbackMousePulse(a - cursor_x, b - cursor_y, 1, 0, reads);
      return;
    }
    if ( strcmp(command, "key") == 0 && fields >= 2 )
    {
      int reads = fields >= 3 && b > 0 ? b : 2;
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=key scan=%d reads=%d cursor=%d,%d\n", a, reads, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackKeyPulse(a, reads);
      return;
    }
    if ( strcmp(command, "delta") == 0 && fields >= 3 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=delta delta=%d,%d buttons=%d,%d cursor=%d,%d\n", a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0);
      return;
    }
    if ( strcmp(command, "pulse") == 0 && fields >= 6 )
    {
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=pulse delta=%d,%d buttons=%d,%d reads=%d cursor=%d,%d\n", a, b, c, d, e, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMousePulse(a, b, c, d, e);
      return;
    }
    /* Route-harness convenience: select an own stack by table index directly,
       reproducing the click handler's core selection assignment (world_001.c:52)
       without needing the stack's screen position. Test instrumentation only;
       reached solely via CLASH95_WORLD_INPUT_SCRIPT. Lets a multi-turn march
       re-select a queued-path stack each turn (which the next-unit cycle skips)
       without per-turn tile discovery. */
    if ( strcmp(command, "select_stack") == 0 && fields >= 2 )
    {
      if ( a >= 0 && a < UNIT_STACK_TABLE_COUNT
        && *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a + UNIT_STACK_SLOT_BASE_OFFSET) != -1 )
      {
        int slot_index;
        g_SelectedUnitIndex = a;
        g_UnitStackSelectionActiveUnitIndex = -1;
        for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
          g_UnitStackSlotSelectedFlags[slot_index] = 0;
        Diagnostics_TraceWorldMapActionEvent(
          "selected_stack_changed",
          a,
          *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a),
          *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a + 2),
          0);
      }
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=select_stack index=%d selected=%d cursor=%d,%d\n", a, g_SelectedUnitIndex, cursor_x, cursor_y);
      return;
    }
    /* Route-harness convenience: write an engine-authored save via the
       recovered saveGame writer (persistence_002.c) into slot <a>. Test
       instrumentation only; dead by default and reached solely via
       CLASH95_WORLD_INPUT_SCRIPT. Lets a route capture a mid-campaign world
       state as a real save/<n>.dat + save/<n>.fac pair that the original
       clash95.exe can load (e.g. slot 10 for the `clash95.exe a` auto-load). */
    if ( strcmp(command, "save_slot") == 0 && fields >= 2 && a >= 0 )
    {
      static char save_label[16] CLASH95_LOCAL_DATA_SYMBOL("save_label.0", "WorldMap_RunInputScriptStep.save_label") = "route-save";
      signed int save_ok;

      save_ok = saveGame(a, (DWORD)(uintptr_t)save_label, 0.0);
      fprintf(stderr, "[bootstrap] debug-save-written slot=%d ok=%d\n", a, save_ok);
      if ( trace_enabled )
        fprintf(stderr, "[world_input] command=save_slot slot=%d ok=%d cursor=%d,%d\n", a, save_ok, cursor_x, cursor_y);
      return;
    }
  }
  if ( script_file && feof(script_file) )
    clearerr(script_file);
}

#if defined(__cplusplus) && defined(__clang__)
/* Emit C tentative storage at the end of this TU, in its observed order. */
extern CLASH95_INTERNAL int g_BattleInputScriptInitialized;
extern CLASH95_INTERNAL int g_BattleInputScriptTraceChecked;
extern CLASH95_INTERNAL int g_BattleInputScriptTraceEnabled;
extern CLASH95_INTERNAL int g_BattleInputScriptWaitReads;
extern CLASH95_INTERNAL FILE *g_BattleInputScriptFile;
#else
CLASH95_INTERNAL int g_BattleInputScriptInitialized;
CLASH95_INTERNAL int g_BattleInputScriptTraceChecked;
CLASH95_INTERNAL int g_BattleInputScriptTraceEnabled;
CLASH95_INTERNAL int g_BattleInputScriptWaitReads;
CLASH95_INTERNAL FILE *g_BattleInputScriptFile;
#endif

CLASH95_INTERNAL void Battle_ResetInputScriptReader(void)
{
  if ( g_BattleInputScriptFile )
  {
    fclose(g_BattleInputScriptFile);
    g_BattleInputScriptFile = NULL;
  }
  g_BattleInputScriptInitialized = 0;
  g_BattleInputScriptWaitReads = 0;
}

CLASH95_INTERNAL void Battle_RunInputScriptStep(void)
{
  char line[256];
  const char *script_path;

  if ( !g_BattleInputScriptTraceChecked )
  {
    const char *trace_value = getenv("CLASH95_TRACE_BATTLE_INPUT_SCRIPT");
    g_BattleInputScriptTraceEnabled = trace_value && *trace_value;
    g_BattleInputScriptTraceChecked = 1;
  }
  if ( !g_BattleInputScriptInitialized )
  {
    g_BattleInputScriptInitialized = 1;
    script_path = getenv("CLASH95_BATTLE_INPUT_SCRIPT");
    if ( script_path && *script_path )
    {
      g_BattleInputScriptFile = fopen(script_path, "r");
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] open path=%s ok=%d\n", script_path, g_BattleInputScriptFile != NULL);
    }
  }
  if ( g_BattleInputScriptWaitReads > 0 )
  {
    if ( g_BattleInputScriptTraceEnabled )
      fprintf(
        stderr,
        "[battle_input] wait remaining=%d cursor=%d,%d selected=%d\n",
        g_BattleInputScriptWaitReads,
        g_MouseCursorRawX >> g_CursorCoordShift,
        g_MouseCursorRawY >> g_CursorCoordShift,
        g_SelectedUnitIndex);
    --g_BattleInputScriptWaitReads;
    return;
  }
  while ( g_BattleInputScriptFile && fgets(line, sizeof(line), g_BattleInputScriptFile) )
  {
    char command[32];
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int fields;
    int cursor_x;
    int cursor_y;

    fields = sscanf(line, " %31s %d %d %d %d %d", command, &a, &b, &c, &d, &e);
    if ( fields <= 0 || command[0] == '#' )
      continue;
    if ( strcmp(command, "wait") == 0 )
    {
      if ( fields >= 2 && a > 0 )
        g_BattleInputScriptWaitReads = a - 1;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=wait reads=%d cursor=%d,%d\n", a, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
      return;
    }
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( strcmp(command, "move") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=move target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "down") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=down target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 1, 0);
      return;
    }
    if ( strcmp(command, "up") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=up target=%d,%d cursor=%d,%d delta=%d,%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a - cursor_x, b - cursor_y, 0, 0);
      return;
    }
    if ( strcmp(command, "click") == 0 && fields >= 3 )
    {
      int reads = fields >= 4 && c > 0 ? c : 2;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=click target=%d,%d cursor=%d,%d delta=%d,%d reads=%d\n", a, b, cursor_x, cursor_y, a - cursor_x, b - cursor_y, reads);
      Platform_DebugPrimeInputFallbackMousePulse(a - cursor_x, b - cursor_y, 1, 0, reads);
      return;
    }
    if ( strcmp(command, "key") == 0 && fields >= 2 )
    {
      int reads = fields >= 3 && b > 0 ? b : 2;
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=key scan=%d reads=%d cursor=%d,%d\n", a, reads, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackKeyPulse(a, reads);
      return;
    }
    if ( strcmp(command, "delta") == 0 && fields >= 3 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=delta delta=%d,%d buttons=%d,%d cursor=%d,%d\n", a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMouseDelta(a, b, fields >= 4 ? c : 0, fields >= 5 ? d : 0);
      return;
    }
    if ( strcmp(command, "pulse") == 0 && fields >= 6 )
    {
      if ( g_BattleInputScriptTraceEnabled )
        fprintf(stderr, "[battle_input] command=pulse delta=%d,%d buttons=%d,%d reads=%d cursor=%d,%d\n", a, b, c, d, e, cursor_x, cursor_y);
      Platform_DebugPrimeInputFallbackMousePulse(a, b, c, d, e);
      return;
    }
  }
  if ( g_BattleInputScriptFile && feof(g_BattleInputScriptFile) )
    clearerr(g_BattleInputScriptFile);
}

#if defined(__cplusplus) && defined(__clang__)
CLASH95_INTERNAL FILE *g_BattleInputScriptFile;
CLASH95_INTERNAL int g_BattleInputScriptInitialized;
CLASH95_INTERNAL int g_BattleInputScriptWaitReads;
CLASH95_INTERNAL int g_BattleInputScriptTraceChecked;
CLASH95_INTERNAL int g_BattleInputScriptTraceEnabled;
#endif
