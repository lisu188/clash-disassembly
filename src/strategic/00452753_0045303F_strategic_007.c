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
int Rules_HostTemple(int a1, double a2)
{
  int tileX = Rules_RtnLong(1, 0, a2);
  int tileY = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return MapTile_GetReligiousSiteCategory(tileX, tileY);
}

//----- (0045279F) --------------------------------------------------------
int Rules_HostDigTreasure(int a1, double a2)
{
  static int bound;

  (void)a1;
  if ( !bound )
  {
    /* 64-bit host seam: each 24-byte outcome record stores three 32-bit string
       pointers that cannot be static initializers under -no-pie; bind them once
       from the recovered pointer list. Treasure_TryDigHere is reached only from
       this handler (the world_002 builder-dig path is gc-removed). */
    static const struct { unsigned char *table; int records; } outcome_tables[4] = {
      { g_TreasureDigOutcomeTable_TempleActive, 9 },
      { g_TreasureDigOutcomeTable_TempleInactive, 8 },
      { g_Mission7ScriptedTreasureEventData, 1 },
      { g_Mission17ScriptedTreasureEventData, 1 },
    };
    int slot = 0;
    for ( int t = 0; t < 4; ++t )
      for ( int r = 0; r < outcome_tables[t].records; ++r )
        for ( int k = 0; k < 3; ++k )
          *(int *)(outcome_tables[t].table + 24 * r + 12 + 4 * k) =
              (int)(intptr_t)g_TreasureOutcomeStringPtrs[slot++];
    bound = 1;
  }
  return Treasure_TryDigHere(Rules_RtnLong(1, 0, a2), 0, 0, 0, 0, a2);
}

//----- (004528AB) --------------------------------------------------------
int Rules_HostRoadExists(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToTile(a3, a4, a5, 0);
}

//----- (00452907) --------------------------------------------------------
int Rules_HostRoadExistsNearby(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int target_x = Rules_RtnLong(2, 0, a2);
  int target_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathNearTile(stack_index, target_x, target_y, 0);
}

//----- (00452963) --------------------------------------------------------
int Rules_HostRoadExistsNearCastle(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int castle_x = Rules_RtnLong(2, 0, a2);
  int castle_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathNearCastle(stack_index, castle_x, castle_y, 0);
}

//----- (004529BF) --------------------------------------------------------
int Rules_HostRoadExistsToPort(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToPort(a3, a4, a5, 0);
}

//----- (00452A1B) --------------------------------------------------------
int Rules_HostRoadExistsToCastle(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToCastle(a3, a4, a5, 0);
}

//----- (00452A77) --------------------------------------------------------
int Rules_HostRoadExistsToTemple(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_IsAtTargetOrCanStay(a3, a4, a5);
}

//----- (00452AD3) --------------------------------------------------------
int Rules_HostTroopInArmyRange(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathIntoArmyRange(a3, a4, a5, 0);
}

//----- (00452B2F) --------------------------------------------------------
int Rules_HostBuildingInArmyRange(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_TryApproachTarget(a3, a4, a5);
}

//----- (00452B8B) --------------------------------------------------------
int Rules_HostDistanceFromObject(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int target_x = Rules_RtnLong(2, 0, a2);
  int target_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_GetPathDistanceToObject(stack_index, target_x, target_y, 0);
}

//----- (00452BE7) --------------------------------------------------------
int Rules_HostTempleInArmyRange(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int temple_x = Rules_RtnLong(2, 0, a2);
  int temple_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_IsTempleWithinArmyRange(stack_index, temple_x, temple_y);
}

//----- (00452C43) --------------------------------------------------------
int Rules_HostTempleOk(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Player_CanEnterReligiousSiteTile(a3, a4, a5);
}

//----- (00452C9F) --------------------------------------------------------
int Rules_HostMarch(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_CommitIfWithinCost(a3, a4, a5, a2);
}

//----- (00452CFB) --------------------------------------------------------
int Rules_HostMarchToTemple(int a1, double a2)
{
  int stack_index;
  int temple_x;
  int temple_y;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  temple_x = Rules_RtnLong(2, 0, a2);
  temple_y = Rules_RtnLong(3, 0, a2);
  return Rules_MarchToTemple(stack_index, temple_x, temple_y, a2);
}

//----- (00452D57) --------------------------------------------------------
int Rules_HostMarchNear(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_MarchNearTile(a3, a4, a5, a2);
}

//----- (00452DB3) --------------------------------------------------------
int Rules_HostAttackTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitAttack(a3, a4, 0, 0, a2);
}

//----- (00452DFF) --------------------------------------------------------
int Rules_HostCaptureTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitCaptureDefeatedStack(a3, a4, a2);
}

//----- (00452E4B) --------------------------------------------------------
int Rules_HostHideTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_HostUnitMoveAndHide(a3, a4, a5, a2);
}

//----- (00452EA7) --------------------------------------------------------
int Rules_HostArmyExists(int a1, double a2)
{
  (void)a1;
  return UnitStack_HasNormalCombatUnitsByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00452EE3) --------------------------------------------------------
// CLIPS host fn `liczba_jednostek_w_oddziale` (registered above at
// aLiczba_jedno_0 -> &Rules_HostUnitCountInTroop, a11i). Recovered from the
// loc_452EE3 handler thunk in clash95.asm (reads 1 CLIPS int arg via
// Rules_RtnLong, tail-calls UnitStack_GetSquadCountByIndex).
int Rules_HostUnitCountInTroop(int a1, double a2)
{
  (void)a1;
  return UnitStack_GetSquadCountByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00452F1F) --------------------------------------------------------
int Rules_HostAttackBuilding(int a1, double a2)
{
  int army_index = Rules_RtnLong(1, 0, a2);
  int building_index = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitAttackBuilding(army_index, building_index, 0, 0, a2);
}

//----- (00452F6B) --------------------------------------------------------
int Rules_HostFordExists(int a1, double a2)
{
  (void)a1;
  return Rules_IsQueuedPathTargetBridgeCrossing(Rules_RtnLong(1, 0, a2));
}

//----- (00452FA7) --------------------------------------------------------
int Rules_HostBuildRoad(int a1, double a2)
{
  (void)a1;
  return Rules_BuildRoadOrStepTowardQueuedPath(Rules_RtnLong(1, 0, a2), 0, a2);
}

//----- (00452FE3) --------------------------------------------------------
int Rules_HostBuildTrap(int a1, double a2)
{
  int target_x = Rules_RtnLong(1, 0, a2);
  int target_y = Rules_RtnLong(2, 0, a2);
  int stack_index = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_BuildTrapNearTile(target_x, target_y, stack_index, a2);
}

//----- (0045303F) --------------------------------------------------------
int Rules_HostUnitCanMove(int a1, double a2)
{
  (void)a1;
  return Unit_AttemptNeighborMove(Rules_RtnLong(1, 0, a2));
}

