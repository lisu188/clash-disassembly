/* Generated from src/recovered/rules/strategic/00455740_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../state/state_shared.h"
#include "../buildings/buildings_api.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00456706) ----------------------------------------------------------
void Rules_HostHealing(int a1, double a2)
{
  (void)a1;
  Building_StartRepairIdleGarrisonUnits(Rules_RtnLong(1, 0, a2));
}

//----- (00456736) ----------------------------------------------------------
void Rules_HostTraining(int a1, double a2)
{
    (void)a1;
    Building_StartTrainingIdleGarrisonUnits(Rules_RtnLong(1, 0, a2));
}

//----- (00456766) ----------------------------------------------------------
void Rules_HostBurnBuildings(int a1, double a2)
{
  (void)a1;
  Rules_OnCastleUpdate(Rules_RtnLong(1, 0, a2), 0, 0, a2);
}

//----- (00456796) ----------------------------------------------------------
void Rules_HostUpgradeWall(int a1, double a2)
{
    (void)a1;
    Building_TryStartUpgradeByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (004567C6) ----------------------------------------------------------
void Rules_HostChangeTax(int a1, double a2)
{
  int building_index;
  float tax_delta;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  tax_delta = Rules_RtnDouble(2, 0, a2);
  Building_AdjustTaxRateByIndex(building_index, 0, tax_delta);
}

//----- (00456806) ----------------------------------------------------------
void Rules_HostRemoveLicence(int a1, double a2)
{
  int building_index;
  int licence_type;

  (void)a1;
  licence_type = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  Building_RemoveUnitLicenceByIndex(building_index, licence_type, 0);
}

//----- (00456842) ----------------------------------------------------------
void Rules_HostStartHealing(int a1, double a2)
{
  int slot_index;
  int building_index;

  (void)a1;
  slot_index = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  Building_RepairUnitByIndex(building_index, slot_index, 0);
}

//----- (0045687E) ----------------------------------------------------------
void Rules_HostStartTraining(int a1, double a2)
{
  int building_index;
  int unit_slot;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  unit_slot = Rules_RtnLong(2, 0, a2);
  Building_TrainUnitByIndex(building_index, unit_slot, 0);
}

//----- (004568BA) ----------------------------------------------------------
void Rules_HostStartProduction(int a1, double a2)
{
  int building_index = Rules_RtnLong(1, 0, a2);
  int production = Rules_RtnLong(2, 0, a2);
  (void)a1;
  Building_SetUnitProductionByIndex(building_index, production, 0);
}

//----- (004568F6) ----------------------------------------------------------
int Rules_HostTax(int a1, double a2)
{
  (void)a1;
  int building_index = Rules_RtnLong(1, 0, a2);
  return Building_GetTaxRateByIndex(building_index);
}

//----- (0045692C) ----------------------------------------------------------
int Rules_HostIsLicence(int a1, double a2)
{
  int building_index;
  int licence_type;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  licence_type = Rules_RtnLong(2, 0, a2);
  return Building_HasUnitLicenceByIndex(building_index, licence_type);
}

//----- (0045696E) ----------------------------------------------------------
int Rules_HostBuySchool(int a1, double a2)
{
  (void)a1;
  return Building_BuildSchoolByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}

//----- (004569A4) ----------------------------------------------------------
int Rules_HostBuyForge(int a1, double a2)
{
  (void)a1;
  return Building_BuildSmithsByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}

//----- (004569DA) ----------------------------------------------------------
int Rules_HostMoney(int a1, double a2)
{
  (void)a1;
  return Building_GetMoneyByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456A10) ----------------------------------------------------------
int Rules_HostWallStrength(int a1, double a2)
{
  (void)a1;
  return Building_GetWallStrengthByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456A46) ----------------------------------------------------------
int Rules_HostCastleStrength(int a1, double a2)
{
  (void)a1;
  return Building_GetCastleStrengthByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456A7C) ----------------------------------------------------------
int Rules_HostTurnNumber(int a1, double a2)
{
    (void)a1;
    (void)a2;
    return Game_GetTurnNumber();
}

//----- (00456AA8) ----------------------------------------------------------
int Rules_HostBuildCastle(int a1, double a2)
{
  int p1 = Rules_RtnLong(1, 0, a2);
  int p2 = Rules_RtnLong(2, 0, a2);
  int p3 = Rules_RtnLong(3, 0, a2);
  int p4 = Rules_RtnLong(4, 0, a2);
  (void)a1;
  return Rules_BuildCastle(p1, p2, p3, p4, (char *)(uintptr_t)Rules_RtnLexeme(5, 0, a2));
}

//----- (00456B0D) ----------------------------------------------------------
int Rules_HostBuyLicence(int a1, double a2)
{
  int licence_type;
  int building_index;

  (void)a1;
  licence_type = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_BuyUnitLicenceByIndex(building_index, licence_type, 0);
}

//----- (00456B4F) ----------------------------------------------------------
int Rules_HostBuyBarracks(int a1, double a2)
{
  int building_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Building_BuildBarracksByIndex(building_index, 0, 0);
}

//----- (00456B85) ----------------------------------------------------------
int Rules_HostBuyHospital(int a1, double a2)
{
  (void)a1;
  return Building_BuildHospitalByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}

//----- (00456BBB) ----------------------------------------------------------
int Rules_HostTechLevel(int a1, double a2)
{
  (void)a1;
  return Building_GetTechLevelByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456BF1) ----------------------------------------------------------
int Rules_HostBuildingType(int a1, double a2)
{
    (void)a1;
    return Building_GetTypeByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456C27) ----------------------------------------------------------
int Rules_HostPlayerStrength(int a1, double a2)
{
  (void)a1;
  return AI_TickNationPostTurn(Rules_RtnLong(1, 0, a2));
}

//----- (00456C5D) ----------------------------------------------------------
int Rules_HostBuyWorkshop(int a1, double a2)
{
  (void)a1;
  return Building_BuildWorkshopByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}

//----- (00456C93) ----------------------------------------------------------
int Rules_HostHappiness(int a1, double a2)
{
  (void)a1;
  return Building_GetSatisfactionByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456CC9) ----------------------------------------------------------
int Rules_HostIsProduction(int a1, double a2)
{
    (void)a1;
    return Building_HasProductionByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456CFF) ----------------------------------------------------------
int Rules_HostPeasantCount(int a1, double a2)
{
    (void)a1;
    return Building_GetPeasantCountByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456D35) ----------------------------------------------------------
int Rules_HostIsMinimal(int a1, double a2)
{
  int candidate_row;
  int candidate_column;
  int site_column;
  int site_row;

  (void)a1;
  candidate_row = Rules_RtnLong(1, 0, a2);
  candidate_column = Rules_RtnLong(2, 0, a2);
  site_row = Rules_RtnLong(3, 0, a2);
  site_column = Rules_RtnLong(4, 0, a2);
  return Map_IsCastleSiteDistanceMinimal(candidate_row, candidate_column, site_column, site_row);
}

//----- (00456D8F) ----------------------------------------------------------
int Rules_HostCanBuyLicence(int a1, double a2)
{
  int building_index;
  unit_type licence_type;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  licence_type = (unit_type)Rules_RtnLong(2, 0, a2);
  return Building_CanBuyUnitLicenceByIndex(building_index, licence_type);
}

//----- (00456DD1) ----------------------------------------------------------
int Rules_HostLicenceIndex(int a1, double a2)
{
  int licence_type;   // edx
  int building_index; // eax

  (void)a1;
  licence_type = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_FindUnitLicenceSlotIndexOrZero(building_index, licence_type);
}

//----- (00456E13) ----------------------------------------------------------
int Rules_HostLicenceInd(int a1, double a2)
{
  (void)a1;
  return Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(Rules_RtnLong(1, 0, a2));
}

//----- (00456E49) ----------------------------------------------------------
int Rules_HostCanUpgradeWall(int a1, double a2)
{
  (void)a1;
  return Building_CanStartUpgradeByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456E7F) ----------------------------------------------------------
int Rules_HostTroopCount(int a1, double a2)
{
  (void)a1;
  return Building_GetGarrisonCountByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456EB5) ----------------------------------------------------------
int Rules_HostIsProductionAny(int a1, double a2)
{
  int licence_type;
  int building_index;

  (void)a1;
  licence_type = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_SelectedUnitLicenceMatchesTypeByIndex(building_index, licence_type);
}

//----- (00456EF7) ----------------------------------------------------------
int Rules_HostLeadOutPeasants(int a1, double a2)
{
    (void)a1;
    return Building_Transfer(
        Rules_RtnLong(1, 0, a2),
        Rules_RtnLong(2, 0, a2),
        Rules_RtnLong(4, 0, a2),
        Rules_RtnLong(3, 0, a2),
        a2);
}

//----- (00456F51) ----------------------------------------------------------
int Rules_HostUnitsToSchool(int a1, double a2)
{
  (void)a1;
  return Building_HasTrainableIdleGarrisonUnit(Rules_RtnLong(1, 0, a2));
}

//----- (00456F87) ----------------------------------------------------------
int Rules_HostMaxTroopCount(int a1, double a2)
{
  (void)a1;
  return Building_IsGarrisonFullByIndex(Rules_RtnLong(1, 0, a2));
}

//----- (00456FBD) ----------------------------------------------------------
int Rules_HostUnitInCastleExists(int a1, double a2)
{
  int building_index;
  unit_type sought_type;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  sought_type = (unit_type)Rules_RtnLong(2, 0, a2);
  return Building_HasGarrisonUnitTypeByIndex(building_index, sought_type);
}

//----- (00456FFF) ----------------------------------------------------------
int Rules_HostUnitsToHospital(int a1, double a2)
{
  (void)a1;
  return Building_HasRepairableIdleGarrisonUnit(Rules_RtnLong(1, 0, a2));
}

//----- (00457035) ----------------------------------------------------------
int Rules_HostLeadOutTroop(int a1, double a2)
{
  int building_index = Rules_RtnLong(1, 0, a2);
  int leave_type = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Building_UnitsLeaveByUnitType(building_index, leave_type, 0, a2);
}

//----- (00457077) ----------------------------------------------------------
int Rules_HostLeadOutTroops(int a1, double a2)
{
  int building_index;

  (void)a1;
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_UnitsLeaveReadyGarrisonSlots(building_index, 0, a2);
}

//----- (004570AD) ----------------------------------------------------------
int Rules_HostCastleName(int a1, double a2)
{
  (void)a1;
  return Player_GetInternedNameByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}

//----- (00457351) ----------------------------------------------------------
int Rules_HostEnterCastle(int a1, double a2)
{
  int building_index;
  int stack_index;

  (void)a1;
  building_index = Rules_RtnLong(2, 0, a2);
  stack_index = Rules_RtnLong(1, 0, a2);
  return (int)(intptr_t)UnitStack_MoveToBuildingAndCheckArrival(stack_index, building_index, a2);
}

//----- (00457393) ----------------------------------------------------------
int Rules_HostJoinTroop(int a1, double a2)
{
  int unit_index;
  int group_index;

  (void)a1;
  unit_index = Rules_RtnLong(1, 0, a2);
  group_index = Rules_RtnLong(2, 0, a2);
  return Script_UnitAddToGroup(unit_index, group_index, 0, a2);
}

//----- (004573D5) ----------------------------------------------------------
int Rules_HostRegroupTroops(int a1, double a2)
{
  int stack_index;
  int other_stack_index;

  (void)a1;
  other_stack_index = Rules_RtnLong(2, 0, a2);
  stack_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_RegroupWithOtherStackByHealth(stack_index, other_stack_index, 0, 0, a2);
}

//----- (00457417) ----------------------------------------------------------
int Rules_HostRegroupCastle(int a1, double a2)
{
  (void)a1;
  return UnitStack_RegroupWithBuildingGarrisonByHealth(
      Rules_RtnLong(1, 0, a2),
      Rules_RtnLong(2, 0, a2),
      0,
      0,
      a2);
}

//----- (00457459) ----------------------------------------------------------
int Rules_HostArmyHeadcount(int a1, double a2)
{
  int stack_index;
  int aggregate_mode;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  aggregate_mode = Rules_RtnLong(2, 0, a2);
  return UnitStack_GetHealthPercentAggregate(stack_index, aggregate_mode);
}

//----- (0045749B) ----------------------------------------------------------
int Rules_HostArmyHasUnitsOfType(int a1, double a2)
{
  int stack_index;
  int sought_type;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  sought_type = Rules_RtnLong(2, 0, a2);
  return UnitStack_HasUnitType(stack_index, (unit_type)sought_type);
}

//----- (0045751F) ----------------------------------------------------------
int Rules_HostCastleFreeSlotCount(int a1, double a2)
{
  (void)a1;
  return Building_CountFreeGarrisonSlots(Rules_RtnLong(1, 0, a2));
}

//----- (00457555) ----------------------------------------------------------
int Rules_HostEnemyPowerAtWalls(int a1, double a2)
{
    (void)a1;
    return Building_GetMaxEnemyStrengthUnderWalls(Rules_RtnLong(1, 0, a2));
}

//----- (0045758B) ----------------------------------------------------------
int Rules_HostFindRoadNearCastle(int a1, double a2)
{
  int stack_index;
  int building_index;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  building_index = Rules_RtnLong(2, 0, a2);
  return UnitStack_QueuePathNearBuilding(stack_index, building_index, 0, 0);
}

//----- (004575CD) ----------------------------------------------------------
int Rules_HostHasUnitsToHeal(int a1, double a2)
{
  int stack_index;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_HasUnitsNeedingHealing(stack_index);
}

//----- (00457603) ----------------------------------------------------------
int Rules_HostFindCastleForHealing(int a1, double a2)
{
  (void)a1;
  return UnitStack_FindPathToNearestHospitalCastle(Rules_RtnLong(1, 0, a2));
}

//----- (00457639) ----------------------------------------------------------
int Rules_HostGoToHealing(int a1, double a2)
{
  (void)a1;
  return UnitStack_ExecuteHealingPathAndCheckArrival(Rules_RtnLong(1, 0, a2), 0, 0, a2);
}

//----- (0045766F) ----------------------------------------------------------
int Rules_HostPlagueInCastleExists(int a1, double a2)
{
  (void)a1;
  return Building_GetPlagueState(Rules_RtnLong(1, 0, a2));
}

//----- (004576A5) ----------------------------------------------------------
int Rules_HostPlagueInTroopExists(int a1, double a2)
{
  (void)a1;
  int stack_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_HasPlagueByIndex(stack_index);
}

//----- (004576DB) ----------------------------------------------------------
int Rules_HostDetachWeakUnits(int a1, double a2)
{
  (void)a1;
  return UnitStack_DetachWeakUnitsToAdjacentTile(Rules_RtnLong(1, 0, a2), 0, 0, a2);
}

//----- (00457711) ----------------------------------------------------------
int Rules_HostDetachUnitsOfType(int a1, double a2)
{
  (void)a1;
  return UnitStack_DetachUnitTypeToAdjacentTile(
      Rules_RtnLong(1, 0, a2),
      Rules_RtnLong(2, 0, a2),
      0,
      0,
      a2);
}

//----- (00457753) ----------------------------------------------------------
int Rules_HostMarchAlongRoad(int a1, double a2)
{
  (void)a1;
  return Unit_ExecuteQueuedPathAndCheckFinished(Rules_RtnLong(1, 0, a2), 0, 0, a2);
}

//----- (00457789) ----------------------------------------------------------
int Rules_HostFindBest(int a1, double a2)
{
  (void)a1;
  return AI_FindBestStrategicTargetNearTile(
      Rules_RtnLong(1, 0, a2),   /* type_filter  -> eax */
      Rules_RtnLong(2, 0, a2),   /* owner_filter -> edx */
      Rules_RtnLong(4, 0, a2),   /* origin_x     -> ecx (CLIPS arg4, swapped) */
      Rules_RtnLong(3, 0, a2),   /* origin_y     -> ebx (CLIPS arg3, swapped) */
      Rules_RtnLong(5, 0, a2));  /* search_radius-> stack */
}

