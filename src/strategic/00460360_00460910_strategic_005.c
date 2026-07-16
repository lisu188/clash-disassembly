/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE int Compat_MenuProbeTraceEnabled (void);

//----- (00460360) --------------------------------------------------------
void Scenario_LoadMissionByIndex(int mission_index, double a2)
{
  int building_record; // eax
  unsigned __int16 building_word; // cx
  int castle_index; // eax
  int player_index; // edx
  unsigned __int16 stack_index; // ax
  int slot_index; // ecx

  Diagnostics_TraceWorldMapActionEvent("mission_load_enter", g_SelectedUnitIndex, mission_index, ACTIVE_MISSION_INDEX, 0);
  switch ( mission_index )
  {
    case 0:
      Diagnostics_TraceBootstrapEvent("mission0-load-map");
      Map_LoadFromFile((uintptr_t)"k_mapa1l.map");
      Diagnostics_TraceBootstrapEvent("mission0-reset-players");
      ACTIVE_MISSION_INDEX = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Bochuwit");
      Diagnostics_TraceBootstrapEvent("mission0-minimap-create");
      MiniMap_CreateSurface(a2);
      Diagnostics_TraceBootstrapEvent("mission0-create-castle");
      createCastle(a2, 30, 42, 0, 2, "Cantbelly", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      Diagnostics_TraceBootstrapEvent("mission0-create-player-stacks");
      createUnit(a2, 30, 44, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 31, 44, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 32, 44, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      Diagnostics_TraceBootstrapEvent("mission0-create-enemy-stacks");
      createUnit(a2, 46, 45, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 15, 6, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 48, 14, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, -1);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 35, 0, 11);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 49, 0, 39);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 40, 0, 3);
      Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, 1, 19, 0, 12);
      Diagnostics_TraceBootstrapEvent("mission0-ai-init");
      Rules_LogMissionSetupInfo();
      Diagnostics_TraceBootstrapEvent("mission0-player-view");
      Game_InitPlayerViewState();
      Diagnostics_TraceBootstrapEvent("mission0-load-done");
      break;
    case 1:
      Map_LoadFromFile((uintptr_t)"k_mapa2l.map");
      ACTIVE_MISSION_INDEX = 1;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Ianos");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 44, 46, 0, 2, "Stormus", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 44, 48, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      castle_index = createCastle(a2, 1, 23, 1, 2, "Drakefly", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 1, 25, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 44, 24, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 48, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 12, 0, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 91;
      PLAYER_CAMERA_TOP(0) = 21;
      MAP_VIEW_LEFT = 90;
      MAP_VIEW_TOP = 21;
      break;
    case 2:
      Map_LoadFromFile((uintptr_t)"k_mapa3l.map");
      ACTIVE_MISSION_INDEX = 2;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Bochuwit");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 98, 24, 0, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 98, 25, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 97, 25, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 97, 24, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 98, 26, 0, UNIT_TYPE_RAM, -1);
      castle_index = createCastle(a2, 41, 68, 1, 2, "Treg Rock", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 83, 16, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 69, 46, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 87, 61, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 52, 58, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 40, 18, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 91, 6, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 85, 9, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 43, 52, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 68, 68, 1, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 35, 69, 1, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 94, 77, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 74, 31, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 91;
      PLAYER_CAMERA_TOP(0) = 21;
      MAP_VIEW_LEFT = 90;
      MAP_VIEW_TOP = 21;
      break;
    case 3:
      Map_LoadFromFile((uintptr_t)"k_mapa4j.map");
      ACTIVE_MISSION_INDEX = 3;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "McDonowan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Sir Wenom");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Gorio");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 21, 21, 0, 1, "Ughuata", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 300;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 20, 20, 0, UNIT_TYPE_CATAPULT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 23, 20, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 20, 23, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 23, 23, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(23, 23));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) = Rng_RandRange(5, 20);
      createUnit(a2, 22, 23, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 41, 34, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 13, 31, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 15, 24, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 24, 13, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 37, 22, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 12, 0, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(12, 0));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) = (*(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) & 0xFC) | 1;
      createUnit(a2, 10, 27, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 21, 48, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 29, 15, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 6, 20, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 1, 9, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 40, 1, 2, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_WINGER, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 23, 43, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 39, 31, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(39, 31));
      *(_BYTE *)(uintptr_t)(UNIT_STACK(stack_index) + 204) |= 3u;
      createUnit(a2, 39, 35, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 49, 48, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 1, 47, 3, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 4:
      Map_LoadFromFile((uintptr_t)"k_mapa5j.map");
      ACTIVE_MISSION_INDEX = 4;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh II");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "McDonowan");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 41, 48, 0, 2, "Totaweon", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 41, 50, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 42, 50, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 43, 50, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      castle_index = createCastle(a2, 56, 69, 1, 1, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_WORD *)(uintptr_t)(building_record + 18) = 9;
      createUnit(a2, 56, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(gameData + 567716);
      Building_UnitGetInto(stack_index, castle_index, 56, 71, a2);
      for ( slot_index = 0; slot_index < 12; ++slot_index )
        *(_BYTE *)(uintptr_t)(building_record + 31 * slot_index + 30) |= 3u;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 1)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 1)) = 0;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 55, 71, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 56, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 57, 71, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 32, 36, 2, 2, "Jolarion", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      castle_index = createCastle(a2, 50, 23, 2, 2, "Akserion", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 50, 25, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      castle_index = createCastle(a2, 25, 48, 2, 2, "Bodeon", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 25, 50, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(uintptr_t)(gameData + 567712) - TILE_OCCUPANT_BUILDING_INDEX_BASE, 4);
      Game_InitPlayerViewState();
      break;
    case 5:
      Map_LoadFromFile((uintptr_t)"k_mapa6j.map");
      ACTIVE_MISSION_INDEX = 5;
      *(_BYTE *)(uintptr_t)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      PLAYER_AI_INTELLIGENCE(1) = 1;
      PLAYER_AI_INTELLIGENCE(2) = 1;
      PLAYER_AI_INTELLIGENCE(3) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      if ( g_LanguageIndex )
      {
        strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Furd");
        strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Dulimam");
      }
      else
      {
        strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Wetus");
        strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      }
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 71, 45, 0, 2, "Defambrion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 200;
      createUnit(a2, 70, 47, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 71, 47, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 72, 47, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 73, 47, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 71, 44, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 72, 44, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 56, 21, 1, 2, "Histone", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 26, 41, 1, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 1000;
      createUnit(a2, 56, 23, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 57, 23, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 58, 23, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 73, 23, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createCastle(a2, 68, 77, 2, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 67, 79, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 68, 79, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 73, 63, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 69, 79, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 70, 79, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 59, 50, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CROSSBOWER, -1);
      castle_index = createCastle(a2, 42, 54, 3, 2, "Ghih Up", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 18) = -1;
      createUnit(a2, 41, 56, 3, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, -1);
      createUnit(a2, 42, 56, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 43, 56, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 44, 56, 3, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 42, 53, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(gameData + 564880);
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) |= 3u;
      createUnit(a2, 87, 66, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedPlayerFact(3, 5);
      Game_InitPlayerViewState();
      break;
    case 6:
      Map_LoadFromFile((uintptr_t)"k_mapa7z.map");
      ACTIVE_MISSION_INDEX = 6;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Walter");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 13, 4, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 14, 4, 0, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 14, 3, 0, UNIT_TYPE_CANNON, -1);
      createCastle(a2, 30, 23, 1, 2, "Dragmounth", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createCastle(a2, 54, 4, 1, 2, "Akserion", UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 30, 25, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 31, 25, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 54, 6, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 85, 81, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 12, 92, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_RAM, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(12, 92));
      *(_BYTE *)(uintptr_t)(UNIT_STACK(stack_index) + 251) |= 3u;
      createUnit(a2, 17, 39, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 57, 38, 1, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 74, 71, 1, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(74, 71));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      Rules_SyncArmyFactStrength(
        (__int16 *)(uintptr_t)UNIT_STACK(stack_index),
        145 * stack_index,
        gameData + UNIT_STACK_TABLE_OFFSET,
        UNIT_STACK_OWNER_INDEX(UNIT_STACK(stack_index)),
        200 * UNIT_STACK_TILE_ROW(UNIT_STACK(stack_index)),
        a2);
      createUnit(a2, 82, 9, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(82, 9));
      Rules_SyncArmyFactStrength(
        (__int16 *)(uintptr_t)UNIT_STACK(stack_index),
        145 * stack_index,
        gameData + UNIT_STACK_TABLE_OFFSET,
        UNIT_STACK_OWNER_INDEX(UNIT_STACK(stack_index)),
        200 * UNIT_STACK_TILE_ROW(UNIT_STACK(stack_index)),
        a2);
      castle_index = createCastle(a2, 90, 41, 2, 2, "Ghettan", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      castle_index = createCastle(a2, 41, 67, 2, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 1000;
      castle_index = createCastle(a2, 5, 56, 2, 1, "Jolarion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 2000;
      createUnit(a2, 41, 69, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 42, 69, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 10;
      PLAYER_CAMERA_TOP(0) = 0;
      MAP_VIEW_LEFT = 10;
      MAP_VIEW_TOP = 0;
      break;
    case 7:
      Map_LoadFromFile((uintptr_t)"k_mapa8z.map");
      ACTIVE_MISSION_INDEX = 7;
      Rules_RetractTreasureFact(55, 45, a2);
      Rules_RetractTreasureFact(50, 27, a2);
      Rules_RetractTreasureFact(35, 63, a2);
      Rules_RetractTreasureFact(14, 68, a2);
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Uraken");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Wodar");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Richard V");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 56, 70, 0, 2, "Weghetown", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 1, 51, 0, 1, "Henrion", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 56, 72, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 57, 72, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 1, 53, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_RAM, UNIT_TYPE_MUSKETEER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 2, 53, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 9, 25, 1, 2, "Moon Town", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 18, 34, 1, 2, "Gate Stone", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 9, 27, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 18, 36, 1, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_GHOST, -1);
      createUnit(a2, 19, 36, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CYCLOP, -1);
      createCastle(a2, 43, 21, 2, 2, "Canoowar", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 54, 31, 2, 1, "Trungeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 42, 23, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 43, 23, 2, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(43, 23));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 44, 23, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 45, 23, 2, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 54, 33, 2, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 55, 33, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 77, 39, 3, 2, "Leweburg", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 75, 67, 3, 1, "Defambrion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 77, 41, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 78, 41, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ELEPHANT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(78, 41));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 75, 69, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 76, 69, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(76, 69));
      for ( slot_index = 1; slot_index < 3; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      for ( slot_index = 3; slot_index < 5; ++slot_index )
      {
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) &= 0xFCu;
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index + 1) + 27) =
          *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) | 2;
      }
      createUnit(a2, 77, 69, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 8:
      Map_LoadFromFile((uintptr_t)"k_mapa9z.map");
      ACTIVE_MISSION_INDEX = 8;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_QUEEN_RELATIONSHIP_STATE(0) = 5;
      PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(0) = 10;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Sir James");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Ruryk");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 8, 27, 0, 2, "Totaweon", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      castle_index = createCastle(a2, 30, 23, 0, 2, "Gordmouth", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      createUnit(a2, 8, 29, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 9, 29, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 10, 29, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 10, 14, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 11, 31, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 22, 29, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 30, 39, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 1, 28, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 8, 50, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 21, 57, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 21, 59, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 28, 57, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 22, 77, 1, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 59, 66, 1, 2, "Ghettan", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 22, 79, 1, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, -1);
      createUnit(a2, 59, 68, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 60, 68, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createCastle(a2, 4, 62, 2, 2, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 84, 64, 2, 2, "Katha Gha", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 4, 64, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 5, 64, 2, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(5, 64));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 6, 64, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 84, 66, 2, UNIT_TYPE_WINGER, UNIT_TYPE_EAGLE, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_MUSKETEER, UNIT_TYPE_BUILDER, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(84, 66));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 85, 66, 2, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, -1);
      createUnit(a2, 86, 66, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 96, 86, 3, 2, "Werneom", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 95, 88, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_TROLL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 96, 88, 3, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_ELEPHANT, -1);
      createUnit(a2, 97, 88, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_WIZARD, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(103, 0));
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 5) + 27) =
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 5) + 27) & 0xFC | 2;
      createUnit(a2, 96, 85, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(102, 69));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 97, 85, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(102, 97));
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 27) =
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 27) & 0xFC | 2;
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 9:
      Map_LoadFromFile((uintptr_t)"k_map10l.map");
      ACTIVE_MISSION_INDEX = 9;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Twogor");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Mieszko");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Chester");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 13, 3, 0, 2, "Gorendberg", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      *(_BYTE *)(uintptr_t)(building_record + 444) = *(_BYTE *)(uintptr_t)(building_record + 444) & 0xF8 | 2;
      castle_index = createCastle(a2, 94, 95, 0, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) = 500;
      *(_BYTE *)(uintptr_t)(building_record + 444) = *(_BYTE *)(uintptr_t)(building_record + 444) & 0xF8 | 2;
      createUnit(a2, 13, 5, 0, UNIT_TYPE_FLY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 14, 5, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 94, 97, 0, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 95, 97, 0, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_DRAGON, -1);
      castle_index = createCastle(a2, 62, 53, 1, 2, "Ghettan", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) = 3000;
      createUnit(a2, 61, 55, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 62, 55, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 63, 55, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CANNON, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 64, 55, 1, UNIT_TYPE_DRAGON, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 62, 52, 1, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createUnit(a2, 63, 52, 1, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      castle_index = createCastle(a2, 58, 11, 2, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) = 3000;
      createUnit(a2, 57, 13, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 58, 13, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CANNON, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 59, 13, 2, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 60, 13, 2, UNIT_TYPE_WINGER, UNIT_TYPE_PEGASUS, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_WIZARD, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 58, 10, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 58, 10, 2, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createCastle(a2, 95, 16, 3, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 11, 41, 3, 2, "Stormus", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 95, 18, 3, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 96, 18, 3, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 11, 43, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 12, 43, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 32, 84, 4, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) += 500;
      *(_BYTE *)(uintptr_t)(building_record + 444) = *(_BYTE *)(uintptr_t)(building_record + 444) & 0xF8 | 3;
      createUnit(a2, 31, 86, 4, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 32, 86, 4, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 33, 86, 4, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 34, 86, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 32, 83, 4, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 10:
      Map_LoadFromFile((uintptr_t)"p_mapa1z.map");
      ACTIVE_MISSION_INDEX = 10;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Gaalaad");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 15, 31, 1, 2, "Timbran", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      building_word = *(_WORD *)(uintptr_t)(building_record + 430);
      *(_WORD *)(uintptr_t)(building_record + 430) = (building_word & 0xF000) | (((building_word & 0xFFF) - 0x32) & 0xFFF);
      createUnit(a2, 15, 33, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 16, 33, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 17, 33, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 1, 22, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 27, 12, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 48, 20, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 34, 37, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 11, 13, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 4, 22, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 10, 25, 2, UNIT_TYPE_LIGHT_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 11:
      Map_LoadFromFile((uintptr_t)"p_mapa2z.map");
      ACTIVE_MISSION_INDEX = 11;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Wetus");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 22, 13, 1, 2, "Gatgally", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 22, 15, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createCastle(a2, 34, 5, 2, 2, "Guluali", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 33, 7, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 34, 7, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 35, 7, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 36, 7, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 12:
      Map_LoadFromFile((uintptr_t)"p_mapa3z.map");
      ACTIVE_MISSION_INDEX = 12;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Gaalaad");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 70, 81, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 71, 81, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 69, 82, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 70, 82, 1, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 71, 83, 1, UNIT_TYPE_RAM, -1);
      castle_index = createCastle(a2, 59, 14, 2, 2, "Sarturia", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) = 5000;
      createUnit(a2, 67, 36, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 85, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 45, 73, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 69, 91, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 77, 64, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 36, 52, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 41, 49, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 62, 94, 2, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      MAP_VIEW_LEFT = 67;
      PLAYER_CAMERA_LEFT(1) = MAP_VIEW_LEFT;
      MAP_VIEW_TOP = 77;
      PLAYER_CAMERA_TOP(1) = MAP_VIEW_TOP;
      break;
    case 13:
      Map_LoadFromFile((uintptr_t)"p_mapa4l.map");
      ACTIVE_MISSION_INDEX = 13;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Leryks X");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Glazur");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Sir John");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 23, 26, 1, 2, "Ungught", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 22, 25, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 25, 1, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 22, 28, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 28, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(25, 28));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) = Rng_RandRange(5, 20);
      createUnit(a2, 26, 28, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createUnit(a2, 7, 15, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 1, 1, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 26, 47, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 38, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 35, 18, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 33, 35, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 45, 29, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 10, 33, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 26, 45, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 48, 8, 4, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 21, 10, 4, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 35, 17, 4, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 14:
      Map_LoadFromFile((uintptr_t)"p_mapa5l.map");
      ACTIVE_MISSION_INDEX = 14;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Uraken");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Wodar");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 50, 3, 1, 2, "Weghetown", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      building_word = *(_WORD *)(uintptr_t)(building_record + 430);
      *(_WORD *)(uintptr_t)(building_record + 430) = building_word & 0xF000;
      createUnit(a2, 50, 5, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 51, 5, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 52, 5, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 49, 5, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      castle_index = createCastle(a2, 52, 24, 2, 2, "Timbran", UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_WORD *)(uintptr_t)(building_record + 18) = 0xF;
      createUnit(a2, 52, 26, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(52, 26));
      Building_UnitGetInto(stack_index, castle_index, 52, 26, a2);
      for ( slot_index = 0; slot_index < 12; ++slot_index )
        *(_BYTE *)(uintptr_t)(building_record + 31 * slot_index + 30) =
          (*(_BYTE *)(uintptr_t)(building_record + 31 * slot_index + 30) & 0xFC) | 1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 1)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 1)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 2)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 2)) = 0;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 64, 4, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 50, 27, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      castle_index = createCastle(a2, 39, 18, 3, 2, "Fraggmeon", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 200;
      castle_index = createCastle(a2, 17, 34, 3, 2, "Eufurhon", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 200;
      createUnit(a2, 39, 20, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 40, 20, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 16, 36, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 17, 36, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 18, 36, 3, UNIT_TYPE_PIKEMAN, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 25, 4, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(52, 24)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, 14);
      Game_InitPlayerViewState();
      break;
    case 15:
      Map_LoadFromFile((uintptr_t)"p_mapa6l.map");
      ACTIVE_MISSION_INDEX = 15;
      *(_BYTE *)(uintptr_t)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Frederic");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Sir James");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 59, 9, 1, 2, "Defambrion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 200;
      createCastle(a2, 50, 96, 1, 1, "Ghondur", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 59, 11, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 60, 11, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 61, 11, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 49, 98, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 50, 98, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 51, 98, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 86, 55, 2, 2, "Histone", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 86, 57, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 87, 57, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createCastle(a2, 79, 2, 3, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 78, 4, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 79, 4, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 80, 4, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 81, 4, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 80, 1, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      castle_index = createCastle(a2, 48, 38, 4, 2, "Ghih Up", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) = 1000;
      *(_WORD *)(uintptr_t)(building_record + 18) = -1;
      createUnit(a2, 48, 40, 4, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 49, 40, 4, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, -1);
      createUnit(a2, 50, 40, 4, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 48, 57, 4, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 75, 4, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 37, 6, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      castle_index = createCastle(a2, 19, 32, 4, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 2000;
      createUnit(a2, 19, 34, 4, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedPlayerFact(4, 15);
      Game_InitPlayerViewState();
      break;
    case 16:
      Map_LoadFromFile((uintptr_t)"p_mapa7j.map");
      ACTIVE_MISSION_INDEX = 16;
      *(_BYTE *)(uintptr_t)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 1;
      PLAYER_AI_INTELLIGENCE(3) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Kalev");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Ianos");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 21, 35, 1, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 20, 36, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 22, 36, 1, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 22, 36, 1, UNIT_TYPE_CANNON, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 91, 43, 2, 2, "Gwadat", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_BYTE *)(uintptr_t)(building_record + 444) = *(_BYTE *)(uintptr_t)(building_record + 444) & 0xF8 | 3;
      createCastle(a2, 54, 74, 2, 2, "Cantown", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 91, 45, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 92, 45, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 93, 45, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 54, 76, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, -1);
      createCastle(a2, 35, 3, 2, 3, "Thubeos", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 66, 45, 2, 3, "Akserion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 35, 5, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 36, 5, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 66, 47, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 67, 47, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 21, 28, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 28, 76, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_SPEARMAN, UNIT_TYPE_HEAVY_SPEARMAN, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      MAP_VIEW_LEFT = 17;
      PLAYER_CAMERA_LEFT(1) = MAP_VIEW_LEFT;
      MAP_VIEW_TOP = 32;
      PLAYER_CAMERA_TOP(1) = MAP_VIEW_TOP;
      break;
    case 17:
      Map_LoadFromFile((uintptr_t)"p_mapa8j.map");
      ACTIVE_MISSION_INDEX = 17;
      *(_BYTE *)(uintptr_t)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      Rules_RetractTreasureFact(50, 34, a2);
      Rules_RetractTreasureFact(51, 73, a2);
      Rules_RetractTreasureFact(77, 34, a2);
      Rules_RetractTreasureFact(24, 49, a2);
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_AI_INTELLIGENCE(3) = 2;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Ruwe");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "McGregor");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Crowley");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 11, 45, 1, 2, "Stormus", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 70, 20, 1, 1, "Dark Town", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      createUnit(a2, 12, 47, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 22, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 72, 22, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_RAM, UNIT_TYPE_MUSKETEER, UNIT_TYPE_ARCHER, -1);
      createCastle(a2, 32, 5, 2, 2, "Treg Rock", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 42, 27, 2, 2, "Bodeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 32, 7, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 33, 7, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 34, 7, 2, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CANNON, -1);
      createCastle(a2, 25, 38, 3, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 61, 41, 3, 1, "Bodeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 25, 40, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 26, 40, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(26, 40));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 60, 43, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 61, 43, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(61, 43));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 62, 43, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 63, 43, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 62, 84, 4, 2, "Leweburg", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 58, 61, 4, 1, "Defambrion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 62, 86, 4, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 63, 86, 4, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ELEPHANT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(63, 86));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 56, 79, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 65, 44, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(65, 44));
      for ( slot_index = 2; slot_index < 4; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      for ( slot_index = 4; slot_index < 6; ++slot_index )
      {
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) &= 0xFCu;
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 2u;
      }
      createUnit(a2, 58, 63, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 18:
      Map_LoadFromFile((uintptr_t)"p_mapa9j.map");
      ACTIVE_MISSION_INDEX = 18;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Tubius");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Gorio");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "McDan");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 85, 38, 1, 2, "Cantbelly", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 15, 23, 1, 2, "Stone Bell", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      createUnit(a2, 85, 40, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 86, 40, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, -1);
      createUnit(a2, 15, 25, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 16, 25, 1, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createCastle(a2, 9, 89, 2, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 9, 91, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 10, 91, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 11, 91, 2, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createCastle(a2, 6, 5, 3, 2, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 82, 55, 3, 2, "Katha Gha", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createUnit(a2, 6, 7, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 7, 7, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(7, 7));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 82, 57, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 83, 57, 3, UNIT_TYPE_WINGER, UNIT_TYPE_EAGLE, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_MUSKETEER, UNIT_TYPE_BUILDER, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(83, 57));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 84, 57, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, -1);
      createUnit(a2, 6, 91, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 27, 49, 4, 2, "Werneom", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 48, 72, 4, 1, "Bokumia", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 27, 51, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_TROLL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 28, 51, 4, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_ELEPHANT, -1);
      createUnit(a2, 10, 51, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_WIZARD, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(10, 51));
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 3u;
      createUnit(a2, 48, 74, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(48, 74));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 49, 74, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(49, 74));
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) &= 0xFCu;
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 2u;
      castle_index = createCastle(a2, 62, 79, 0, 1, "Fhur Tao", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) += 200;
      createUnit(a2, 62, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 63, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 61, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 70, 80, 0, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(70, 80));
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 28) &= 0xFCu;
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 28) |= 1u;
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) &= 0xFCu;
      *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 1u;
      createUnit(a2, 37, 29, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(37, 29));
      for ( slot_index = 0; slot_index < 5; ++slot_index )
        *(_BYTE *)(uintptr_t)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 19:
      Map_LoadFromFile((uintptr_t)"p_map10z.map");
      ACTIVE_MISSION_INDEX = 19;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(uintptr_t)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Sir Mordus");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Galaghan");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Longhand");
      strcpy((char *)(uintptr_t)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 83, 15, 1, 2, "Gorendberg", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(uintptr_t)(building_record + 438) -= 100;
      createCastle(a2, 73, 68, 1, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 83, 17, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_FLY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 84, 17, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 73, 70, 1, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      castle_index = createCastle(a2, 20, 9, 2, 2, "Ghettan", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) = 600;
      createCastle(a2, 70, 30, 2, 2, "Drakefly", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 20, 11, 2, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 21, 11, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 22, 11, 2, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CANNON, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 70, 32, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_DRAGON, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 71, 32, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createCastle(a2, 36, 54, 3, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 35, 56, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 36, 56, 3, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CANNON, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 37, 56, 3, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 38, 56, 3, UNIT_TYPE_WINGER, UNIT_TYPE_PEGASUS, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 36, 53, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 79, 2, 4, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 88, 63, 4, 1, "Stormus", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 300;
      createUnit(a2, 79, 4, 4, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 80, 4, 4, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 88, 65, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 89, 65, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      castle_index = createCastle(a2, 95, 51, 0, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(uintptr_t)(BUILDING_RECORD(castle_index) + 438) += 300;
      createUnit(a2, 95, 53, 0, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 96, 53, 0, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 97, 53, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      createUnit(a2, 55, 79, 0, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 78, 98, 0, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    default:
      break;
  }
  Diagnostics_TraceWorldMapActionEvent(
    "mission_load_done",
    g_SelectedUnitIndex,
    mission_index,
    ACTIVE_MISSION_INDEX,
    g_CurrentPlayerIndex);
  Diagnostics_TraceWorldMapUnitSnapshot("after_mission_load");
}

//----- (00460370) --------------------------------------------------------
int  Scenario_LoadMissionByIndexAndPlay(char *mission_index_arg, int a2, DWORD a3, double a4)
{
  int mission_index; // eax
  unsigned __int8 saved_campaign_state[27]; // [esp-1Bh] [ebp-1Bh] BYREF

  mission_index = (int)(size_t)mission_index_arg;
  qmemcpy(saved_campaign_state, (const void *)(uintptr_t)(gameData + 147147), 0x1Bu);
  if ( mission_index && mission_index != 10 )
    Video_PlayAviWithModeGuard(0, aZwy01_0);
  Mission_PlayInfoSlideshow(mission_index, mission_index_arg);
  WorldMap_Initialize((char)mission_index, a3);
  Scenario_LoadMissionByIndex(mission_index, a4);
  if ( mission_index && mission_index != 10 )
    qmemcpy((void *)(uintptr_t)(gameData + 147147), saved_campaign_state, 0x1Bu);
  return PlayGame(0, (char)mission_index, a3, 0, a4);
}
// 5202E4: using guessed type int gameData;

//----- (004603F0) --------------------------------------------------------
int __thiscall RenderState_ConstructGlobalInstance(void *this)
{
  int v1; // edx
  int v2; // ecx

  Device_GetParamA((int)(intptr_t)g_RenderState, (int)(intptr_t)this);
  return CRT_RegisterFinalizableObject(v2, v1);
}
// 4603FF: variable 'v2' is possibly undefined
// 4603FF: variable 'v1' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 544CD8: using guessed type _DWORD g_RenderState[9];

/*
 * The original `unk_545158` descriptor lives far beyond the render-state slab
 * rooted at `g_RenderState`. In the compacted C global layout those regions sit
 * adjacent, so mutating the descriptor's width/height fields would overwrite
 * `g_RenderState + 0x3c`, which is the live descriptor pointer used by
 * `RenderState_SelectCursorDescriptor` and `RenderState_RecalculateCursorBoundsForRect`. Keep the bootstrap cursor descriptor in
 * dedicated storage until the broader DGROUP layout is recovered safely.
 */
CLASH95_INTERNAL _DWORD g_RenderVideoInitCursorDescriptor[9];
CLASH95_INTERNAL _DWORD *Compat_RenderStateSurface(int render_state, unsigned int field_offset);
CLASH95_INTERNAL _DWORD *Compat_RenderStateCursorDescriptor(int render_state);

CLASH95_INTERNAL void Compat_SyncRenderCursorGlobals(const _DWORD *render_state)
{
  g_MouseCursorRawX = render_state[9];
  g_MouseCursorRawY = render_state[10];
  g_CursorCoordShift = (unsigned char)render_state[277];
}

/* Type declaration moved to recovered_types.h. */








CLASH95_INTERNAL CompatRenderStateTail g_RenderStateTail;

CLASH95_INTERNAL CompatRenderStateTail *Compat_RenderStateTailFields(int render_state)
{
  (void)render_state;
  return &g_RenderStateTail;
}

CLASH95_TEST_VISIBLE int Compat_MenuProbeTraceEnabled(void)
{
  static int trace_state = -1;

  if ( trace_state == -1 )
  {
    const char *value = getenv("CLASH95_TRACE_RENDER_INPUT");
    trace_state = value && *value;
  }
  return trace_state;
}

CLASH95_INTERNAL void Compat_MenuProbeTraceRenderInput(
        const char *phase,
        int render_state,
        int arg0,
        int arg1,
        int extra0,
        int extra1)
{
  static unsigned int trace_count;
  CompatRenderStateTail *tail;

  if ( !Compat_MenuProbeTraceEnabled() || trace_count >= 1024 )
    return;
  tail = Compat_RenderStateTailFields(render_state);
  fprintf(
    stderr,
    "[menu-input] phase=%s arg0=%d arg1=%d extra0=%d extra1=%d field468=%d flags=%u x=%d y=%d scale=%u deadline=%d\n",
    phase,
    arg0,
    arg1,
    extra0,
    extra1,
    tail->field_468_active,
    *(unsigned __int8 *)(uintptr_t)(render_state + 44),
    *(_DWORD *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108),
    *(_DWORD *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108),
    *(unsigned __int8 *)(uintptr_t)(render_state + 1108),
    g_RenderStateNextRefreshTick);
  fflush(stderr);
  ++trace_count;
}

//----- (00460410) --------------------------------------------------------
_DWORD * RenderState_ConstructDefault(int render_state, int a2)
{
  int palette_base; // eax
  _DWORD *palette_array; // eax

  (void)a2;
  palette_base = render_state + 80;
  *(_DWORD *)(uintptr_t)(palette_base - 64) = 0;
  *(_DWORD *)(uintptr_t)(palette_base - 60) = 0;
  *(_DWORD *)(uintptr_t)(palette_base - 56) = 639;
  *(_DWORD *)(uintptr_t)(palette_base - 52) = 479;
  *(_DWORD *)(uintptr_t)(palette_base - 48) = 64;
  *(_DWORD *)(uintptr_t)(palette_base - 16) = 0;
  palette_array = (_DWORD *)(uintptr_t)(unsigned int)_wcpp_4_ctor_array__(palette_base, 256);
  palette_array[256] = 50;
  palette_array[257] = 6;
  palette_array[258] = 2;
  palette_array[259] = 5;
  palette_array[260] = g_RenderState_Vtable;
  return palette_array - 20;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 50F1E4: using guessed type int (*off_50F1E4[6])();

//----- (00460490) --------------------------------------------------------
int  RenderState_InitCursorResources(int render_state, int a2, char a3, DWORD a4)
{
  _DWORD *sprite_set;
  _DWORD *surface;

  g_CursorOverlayPresented = 0;
  *(_DWORD *)(uintptr_t)(render_state + 44) = 0;
  sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a2, a3, a4);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, "mouse.s32");
  *(_DWORD *)(uintptr_t)(render_state + 64) = sprite_set;
  surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
  {
    a3 = 64;
    surface = Render_CreateSurface((int)(intptr_t)surface, 64, 64);
  }
  *(_DWORD *)(uintptr_t)(render_state + 8) = surface;
  surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
    surface = Render_CreateSurface((int)(intptr_t)surface, 64, 64);
  *(_DWORD *)(uintptr_t)(render_state + 12) = surface;
  RenderState_SelectCursorDescriptor(render_state, (int)(uintptr_t)g_RenderVideoInitCursorDescriptor);
  Compat_RenderStateInvokeMethod(render_state, 20);
  *(_DWORD *)(uintptr_t)(render_state + 48) = (*(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(render_state + 60) + 20);
  *(_DWORD *)(uintptr_t)(render_state + 52) = (*(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(render_state + 60) + 24);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)render_state, 0, 640, 0, 480);
  return LoadPalCOL(render_state + 80, (intptr_t)aMap_pal_1, a4);
}
// 544D10: using guessed type int dword_544D10;

//----- (00460580) --------------------------------------------------------
int  RenderState_ReleaseCursorResources(int render_state)
{
  int surface_handle;
  int vtable;
  int (*release_proc)(int, int);

  DLXSpriteSet_ReleaseAndClear((int *)(uintptr_t)(render_state + 64));
  surface_handle = *(_DWORD *)(uintptr_t)(render_state + 8);
  if ( surface_handle )
  {
    vtable = *(_DWORD *)(uintptr_t)(surface_handle + 184);
    release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(vtable);
    release_proc(surface_handle, 2);
  }
  surface_handle = *(_DWORD *)(uintptr_t)(render_state + 12);
  if ( !surface_handle )
    return 0;
  vtable = *(_DWORD *)(uintptr_t)(surface_handle + 184);
  release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(vtable);
  release_proc(surface_handle, 2);
  return 0;
}

//----- (004605D0) --------------------------------------------------------
unsigned int  DD_Pump(int render_state, int a2, ...)
{
  _DWORD *primary_surface;
  _DWORD *back_surface;
  _DWORD *cursor_descriptor;
  unsigned int message_pump_result;
  int v4; // edx
  int v5; // ecx
  unsigned int result; // eax
  int cursor_update_deadline;
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int descriptor_addr; // edi
  int frame_interval; // ebp
  int cursor_frame_advanced; // ebx
  unsigned int now; // eax
  _DWORD *descriptor_frames; // eax
  int cursor_screen_y; // ecx
  int resource_handle; // ebp
  int v20; // eax
  int SpriteForChar; // eax
  void *saved_render_device; // [esp+1Ch] [ebp-18h]

  message_pump_result = Platform_PumpMessagesAndBlitFrame(a2);
  result = Time_Now(v5, v4);
  Compat_MenuProbeTraceRenderInput(
    "dd-pump",
    render_state,
    message_pump_result,
    result,
    g_RenderStateNextRefreshTick,
    *(_DWORD *)(uintptr_t)(render_state + 1112));
  if ( result >= g_RenderStateNextRefreshTick || message_pump_result )
  {
    g_RenderStateNextRefreshTick = *(_DWORD *)(uintptr_t)(render_state + 1112) + Time_Now(v8, v7);
    Compat_RenderStateInvokeMethod(render_state, 20);
    if ( g_DDPageFlipWasInProgressFlag && !DD_IsFlipping(render_state) )
    {
      *(_DWORD *)(uintptr_t)(render_state + 68) = Time_Now(v10, v9);
      *(_DWORD *)(uintptr_t)(render_state + 72) = *(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108);
      *(_DWORD *)(uintptr_t)(render_state + 76) = *(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108);
    }
    g_DDPageFlipWasInProgressFlag = DD_IsFlipping(render_state);
    Compat_RenderStateInvokeMethod(render_state, 4);
    cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
    descriptor_addr = (int)(intptr_t)cursor_descriptor;
    frame_interval = *(_DWORD *)(uintptr_t)(descriptor_addr + 8);
    cursor_frame_advanced = 0;
    if ( frame_interval )
    {
      cursor_update_deadline = *(_DWORD *)(uintptr_t)(descriptor_addr + 28) + frame_interval;
      now = Time_Now(cursor_update_deadline, v11);
      if ( (unsigned int)cursor_update_deadline < now )
      {
        *(_DWORD *)((char *)cursor_descriptor + 28) = Time_Now(now, v11);
        ++*(_DWORD *)((char *)cursor_descriptor + 32);
        descriptor_frames = cursor_descriptor;
        if ( descriptor_frames[1] - *descriptor_frames < descriptor_frames[8] )
          descriptor_frames[8] = 0;
        cursor_frame_advanced = 1;
      }
    }
    *(_DWORD *)(uintptr_t)(render_state + 48) = (*(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 20);
    cursor_screen_y = (*(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 24);
    *(_DWORD *)(uintptr_t)(render_state + 52) = cursor_screen_y;
    result = g_CursorOverlayPresented;
    if ( g_CursorOverlayPresented )
    {
      if ( message_pump_result
        || cursor_frame_advanced
        || (result = *(_DWORD *)(uintptr_t)(render_state + 48), result != *(_DWORD *)(uintptr_t)render_state)
        || cursor_screen_y != *(_DWORD *)(uintptr_t)(render_state + 4) )
      {
        saved_render_device = g_RenderDevice;
        resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
        primary_surface = Compat_RenderStateSurface(render_state, 8);
        back_surface = Compat_RenderStateSurface(render_state, 12);
        if ( *(_DWORD *)(uintptr_t)render_state == *(_DWORD *)(uintptr_t)(render_state + 48) && *(_DWORD *)(uintptr_t)(render_state + 52) == *(_DWORD *)(uintptr_t)(render_state + 4) )
        {
          g_RenderDevice = (_UNKNOWN *)back_surface;
          Render_FillRect(
            primary_surface,
            back_surface,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            0,
            0);
          SpriteForChar = DLX_GetSpriteForChar(
                            *(_DWORD *)(uintptr_t)(render_state + 64),
                            *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)SpriteForChar;
          Render_FillRect(
            back_surface,
            0,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            *(_WORD *)(uintptr_t)render_state,
            *(_WORD *)(uintptr_t)(render_state + 4));
        }
        else
        {
          g_RenderDevice = &g_MainRenderDevice;
          Render_FillRect(
            primary_surface,
            0,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            *(_WORD *)(uintptr_t)render_state,
            *(_WORD *)(uintptr_t)(render_state + 4));
          Render_FillRect(
            0,
            primary_surface,
            *(unsigned __int16 *)(uintptr_t)(render_state + 52),
            *(unsigned __int16 *)(uintptr_t)(render_state + 48),
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(uintptr_t)(render_state + 48) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(uintptr_t)(render_state + 52) - 1,
            0,
            0);
          v20 = DLX_GetSpriteForChar(
                  *(_DWORD *)(uintptr_t)(render_state + 64),
                  *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)v20;
          *(_DWORD *)(uintptr_t)render_state = *(_DWORD *)(uintptr_t)(render_state + 48);
          *(_DWORD *)(uintptr_t)(render_state + 4) = *(_DWORD *)(uintptr_t)(render_state + 52);
        }
        g_RenderDevice = saved_render_device;
        return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, resource_handle);
      }
    }
  }
  return result;
}
// 4605DF: variable 'v5' is possibly undefined
// 4605DF: variable 'v4' is possibly undefined
// 4605EE: variable 'v7' is possibly undefined
// 4605F4: variable 'v8' is possibly undefined
// 4607E8: variable 'v10' is possibly undefined
// 4607E8: variable 'v9' is possibly undefined
// 46065C: variable 'v11' is possibly undefined
// 460663: variable 'v16' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5448B0: using guessed type int dword_5448B0;
// 5448B4: using guessed type int dword_5448B4;
// 544D10: using guessed type int dword_544D10;

//----- (004608D0) --------------------------------------------------------
void  RenderState_SetMouseSpeed(int render_state, int mouse_speed, DWORD a3)
{
  Debug_Log(render_state, mouse_speed, a3, (int)(intptr_t)aMouse_speedD);
  *(_DWORD *)(uintptr_t)(render_state + 32) = mouse_speed;
}

//----- (004608F0) --------------------------------------------------------
BOOL  DD_IsFlipping(int render_state)
{
  return (*(_BYTE *)(uintptr_t)(render_state + 44) & 1) != 0;
}

//----- (00460900) --------------------------------------------------------
BOOL  DD_IsLost(int render_state)
{
  return (*(_BYTE *)(uintptr_t)(render_state + 44) & 2) != 0;
}

//----- (00460910) --------------------------------------------------------
BOOL  Input_PollEventsUntil(int render_state, char a2)
{
  int previous_poll_state;

  previous_poll_state = *(_DWORD *)(uintptr_t)(render_state + 56);
  *(_DWORD *)(uintptr_t)(render_state + 56) = 0;
  Platform_PumpMessagesAndBlitFrame(a2);
  *(_DWORD *)(uintptr_t)(render_state + 56) = previous_poll_state;
  InputBackend_PollState(&g_InputBackendState, render_state, previous_poll_state);
  return g_InputMousePrimaryButtonState < 0 || g_InputMouseSecondaryButtonState < 0;
}
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;
