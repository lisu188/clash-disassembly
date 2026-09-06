/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "strategic_shared_state.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00452753) --------------------------------------------------------
int Rules_HostTemple(int unused, double clips_context)
{
  int tile_x = Rules_RtnLong(1, 0, clips_context);
  int tile_y = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  return MapTile_GetReligiousSiteCategory(tile_x, tile_y);
}

//----- (0045279F) --------------------------------------------------------
int Rules_HostDigTreasure(int unused, double clips_context)
{
  static int bound CLASH95_LOCAL_DATA_SYMBOL("bound.1", "Rules_HostDigTreasure.bound");

  (void)unused;
  if ( !bound )
  {
    /* 64-bit host seam: each 24-byte outcome record stores three 32-bit string
       pointers that cannot be static initializers under -no-pie; bind them once
       from the recovered pointer list. Treasure_TryDigHere is reached only from
       this handler (the world_002 builder-dig path is gc-removed). */
    static const struct { unsigned char *table; int records; } outcome_tables[4] CLASH95_LOCAL_DATA_SYMBOL("outcome_tables.0", "Rules_HostDigTreasure.outcome_tables") = {
      { g_TreasureDigOutcomeTable_Human, 9 },
      { g_TreasureDigOutcomeTable_AI, 8 },
      { g_Mission7ScriptedTreasureEventData, 1 },
      { g_Mission17ScriptedTreasureEventData, 1 },
    };
    int pointer_index = 0;
    for ( int table_index = 0; table_index < 4; ++table_index )
      for ( int record_index = 0; record_index < outcome_tables[table_index].records; ++record_index )
        for ( int string_index = 0; string_index < 3; ++string_index )
          *(int *)(outcome_tables[table_index].table + 24 * record_index + 12 + 4 * string_index) =
              (int)(intptr_t)g_TreasureOutcomeStringPtrs[pointer_index++];
    bound = 1;
  }
  return Treasure_TryDigHere(Rules_RtnLong(1, 0, clips_context), 0, 0, 0, 0, clips_context);
}

//----- (004528AB) --------------------------------------------------------
int Rules_HostRoadExists(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathToTile(stack_index, target_x, target_y, 0);
}

//----- (00452907) --------------------------------------------------------
int Rules_HostRoadExistsNearby(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathNearTile(stack_index, target_x, target_y, 0);
}

//----- (00452963) --------------------------------------------------------
int Rules_HostRoadExistsNearCastle(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int castle_x = Rules_RtnLong(2, 0, clips_context);
  int castle_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathNearCastle(stack_index, castle_x, castle_y, 0);
}

//----- (004529BF) --------------------------------------------------------
int Rules_HostRoadExistsToPort(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathToPort(stack_index, target_x, target_y, 0);
}

//----- (00452A1B) --------------------------------------------------------
int Rules_HostRoadExistsToCastle(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathToCastle(stack_index, target_x, target_y, 0);
}

//----- (00452A77) --------------------------------------------------------
int Rules_HostRoadExistsToTemple(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Move_IsAtTargetOrCanStay(stack_index, target_x, target_y);
}

//----- (00452AD3) --------------------------------------------------------
int Rules_HostTroopInArmyRange(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_QueuePathIntoArmyRange(stack_index, target_x, target_y, 0);
}

//----- (00452B2F) --------------------------------------------------------
int Rules_HostBuildingInArmyRange(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Move_TryApproachTarget(stack_index, target_x, target_y);
}

//----- (00452B8B) --------------------------------------------------------
int Rules_HostDistanceFromObject(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_GetPathDistanceToObject(stack_index, target_x, target_y, 0);
}

//----- (00452BE7) --------------------------------------------------------
int Rules_HostTempleInArmyRange(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int temple_x = Rules_RtnLong(2, 0, clips_context);
  int temple_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_IsTempleWithinArmyRange(stack_index, temple_x, temple_y);
}

//----- (00452C43) --------------------------------------------------------
int Rules_HostTempleOk(int unused, double clips_context)
{
  int player_index = Rules_RtnLong(1, 0, clips_context);
  int tile_x = Rules_RtnLong(2, 0, clips_context);
  int tile_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Player_CanEnterReligiousSiteTile(player_index, tile_x, tile_y);
}

//----- (00452C9F) --------------------------------------------------------
int Rules_HostMarch(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Move_CommitIfWithinCost(stack_index, target_x, target_y, clips_context);
}

//----- (00452CFB) --------------------------------------------------------
int Rules_HostMarchToTemple(int unused, double clips_context)
{
  int stack_index;
  int temple_x;
  int temple_y;

  (void)unused;
  stack_index = Rules_RtnLong(1, 0, clips_context);
  temple_x = Rules_RtnLong(2, 0, clips_context);
  temple_y = Rules_RtnLong(3, 0, clips_context);
  return Rules_MarchToTemple(stack_index, temple_x, temple_y, clips_context);
}

//----- (00452D57) --------------------------------------------------------
int Rules_HostMarchNear(int unused, double clips_context)
{
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  int target_x = Rules_RtnLong(2, 0, clips_context);
  int target_y = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_MarchNearTile(stack_index, target_x, target_y, clips_context);
}

//----- (00452DB3) --------------------------------------------------------
int Rules_HostAttackTroop(int unused, double clips_context)
{
  int attacker_stack_index = Rules_RtnLong(1, 0, clips_context);
  int defender_stack_index = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  return Rules_HostUnitAttack(attacker_stack_index, defender_stack_index, 0, 0, clips_context);
}

//----- (00452DFF) --------------------------------------------------------
int Rules_HostCaptureTroop(int unused, double clips_context)
{
  int capturing_stack_index = Rules_RtnLong(1, 0, clips_context);
  int defeated_stack_index = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  return Rules_HostUnitCaptureDefeatedStack(capturing_stack_index, defeated_stack_index, clips_context);
}

//----- (00452E4B) --------------------------------------------------------
int Rules_HostHideTroop(int unused, double clips_context)
{
  int target_x = Rules_RtnLong(1, 0, clips_context);
  int target_y = Rules_RtnLong(2, 0, clips_context);
  int stack_index = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_HostUnitMoveAndHide(target_x, target_y, stack_index, clips_context);
}

//----- (00452EA7) --------------------------------------------------------
int Rules_HostArmyExists(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_HasNormalCombatUnitsByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00452EE3) --------------------------------------------------------
// CLIPS host fn `liczba_jednostek_w_oddziale` (registered above at
// aLiczba_jedno_0 -> &Rules_HostUnitCountInTroop, a11i). Recovered from the
// loc_452EE3 handler thunk in clash95.asm (reads 1 CLIPS int arg via
// Rules_RtnLong, tail-calls UnitStack_GetSquadCountByIndex).
int Rules_HostUnitCountInTroop(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_GetSquadCountByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00452F1F) --------------------------------------------------------
int Rules_HostAttackBuilding(int unused, double clips_context)
{
  int army_index = Rules_RtnLong(1, 0, clips_context);
  int building_index = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  return Rules_HostUnitAttackBuilding(army_index, building_index, 0, 0, clips_context);
}

//----- (00452F6B) --------------------------------------------------------
int Rules_HostFordExists(int unused, double clips_context)
{
  (void)unused;
  return Rules_IsQueuedPathTargetBridgeCrossing(Rules_RtnLong(1, 0, clips_context));
}

//----- (00452FA7) --------------------------------------------------------
int Rules_HostBuildRoad(int unused, double clips_context)
{
  (void)unused;
  return Rules_BuildRoadOrStepTowardQueuedPath(Rules_RtnLong(1, 0, clips_context), 0, clips_context);
}

//----- (00452FE3) --------------------------------------------------------
int Rules_HostBuildTrap(int unused, double clips_context)
{
  int target_x = Rules_RtnLong(1, 0, clips_context);
  int target_y = Rules_RtnLong(2, 0, clips_context);
  int stack_index = Rules_RtnLong(3, 0, clips_context);
  (void)unused;
  return Rules_BuildTrapNearTile(target_x, target_y, stack_index, clips_context);
}

//----- (0045303F) --------------------------------------------------------
int Rules_HostUnitCanMove(int unused, double clips_context)
{
  (void)unused;
  return Unit_AttemptNeighborMove(Rules_RtnLong(1, 0, clips_context));
}

