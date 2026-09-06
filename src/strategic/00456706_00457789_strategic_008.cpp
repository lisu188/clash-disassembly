/* Generated from src/recovered/rules/strategic/00455740_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../buildings/buildings_api.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00456706) ----------------------------------------------------------
void Rules_HostHealing(int unused, double clips_context)
{
  (void)unused;
  Building_StartRepairIdleGarrisonUnits(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456736) ----------------------------------------------------------
void Rules_HostTraining(int unused, double clips_context)
{
  (void)unused;
  Building_StartTrainingIdleGarrisonUnits(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456766) ----------------------------------------------------------
void Rules_HostBurnBuildings(int unused, double clips_context)
{
  (void)unused;
  Rules_OnCastleUpdate(Rules_RtnLong(1, 0, clips_context), 0, 0, clips_context);
}

//----- (00456796) ----------------------------------------------------------
void Rules_HostUpgradeWall(int unused, double clips_context)
{
  (void)unused;
  Building_TryStartUpgradeByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (004567C6) ----------------------------------------------------------
void Rules_HostChangeTax(int unused, double clips_context)
{
  int building_index;
  float tax_delta;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  tax_delta = Rules_RtnDouble(2, 0, clips_context);
  Building_AdjustTaxRateByIndex(building_index, 0, tax_delta);
}

//----- (00456806) ----------------------------------------------------------
void Rules_HostRemoveLicence(int unused, double clips_context)
{
  int building_index;
  int licence_type;

  (void)unused;
  licence_type = Rules_RtnLong(2, 0, clips_context);
  building_index = Rules_RtnLong(1, 0, clips_context);
  Building_RemoveUnitLicenceByIndex(building_index, (unit_type)(unsigned int)(licence_type), 0);
}

//----- (00456842) ----------------------------------------------------------
void Rules_HostStartHealing(int unused, double clips_context)
{
  int slot_index;
  int building_index;

  (void)unused;
  slot_index = Rules_RtnLong(2, 0, clips_context);
  building_index = Rules_RtnLong(1, 0, clips_context);
  Building_RepairUnitByIndex(building_index, slot_index, 0);
}

//----- (0045687E) ----------------------------------------------------------
void Rules_HostStartTraining(int unused, double clips_context)
{
  int building_index;
  int unit_slot;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  unit_slot = Rules_RtnLong(2, 0, clips_context);
  Building_TrainUnitByIndex(building_index, unit_slot, 0);
}

//----- (004568BA) ----------------------------------------------------------
void Rules_HostStartProduction(int unused, double clips_context)
{
  int building_index = Rules_RtnLong(1, 0, clips_context);
  int production = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  Building_SetUnitProductionByIndex(building_index, production, 0);
}

//----- (004568F6) ----------------------------------------------------------
int Rules_HostTax(int unused, double clips_context)
{
  (void)unused;
  int building_index = Rules_RtnLong(1, 0, clips_context);
  return Building_GetTaxRateByIndex(building_index);
}

//----- (0045692C) ----------------------------------------------------------
int Rules_HostIsLicence(int unused, double clips_context)
{
  int building_index;
  int licence_type;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  licence_type = Rules_RtnLong(2, 0, clips_context);
  return Building_HasUnitLicenceByIndex(building_index, (unit_type)(unsigned int)(licence_type));
}

//----- (0045696E) ----------------------------------------------------------
int Rules_HostBuySchool(int unused, double clips_context)
{
  (void)unused;
  return Building_BuildSchoolByIndex(Rules_RtnLong(1, 0, clips_context), 0, 0);
}

//----- (004569A4) ----------------------------------------------------------
int Rules_HostBuyForge(int unused, double clips_context)
{
  (void)unused;
  return Building_BuildSmithsByIndex(Rules_RtnLong(1, 0, clips_context), 0, 0);
}

//----- (004569DA) ----------------------------------------------------------
int Rules_HostMoney(int unused, double clips_context)
{
  (void)unused;
  return Building_GetMoneyByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456A10) ----------------------------------------------------------
int Rules_HostWallStrength(int unused, double clips_context)
{
  (void)unused;
  return Building_GetWallStrengthByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456A46) ----------------------------------------------------------
int Rules_HostCastleStrength(int unused, double clips_context)
{
  (void)unused;
  return Building_GetCastleStrengthByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456A7C) ----------------------------------------------------------
int Rules_HostTurnNumber(int unused, double clips_context)
{
  (void)unused;
  (void)clips_context;
  return Game_GetTurnNumber();
}

//----- (00456AA8) ----------------------------------------------------------
int Rules_HostBuildCastle(int unused, double clips_context)
{
  int building_type = Rules_RtnLong(1, 0, clips_context);
  int arg2 = Rules_RtnLong(2, 0, clips_context);
  int arg3 = Rules_RtnLong(3, 0, clips_context);
  int arg4 = Rules_RtnLong(4, 0, clips_context);
  (void)unused;
  return Rules_BuildCastle(building_type, arg2, arg3, arg4, (char *)(uintptr_t)Rules_RtnLexeme(5, 0, clips_context), clips_context);
}

//----- (00456B0D) ----------------------------------------------------------
int Rules_HostBuyLicence(int unused, double clips_context)
{
  int licence_type;
  int building_index;

  (void)unused;
  licence_type = Rules_RtnLong(2, 0, clips_context);
  building_index = Rules_RtnLong(1, 0, clips_context);
  return Building_BuyUnitLicenceByIndex(building_index, (unit_type)(unsigned int)(licence_type), 0);
}

//----- (00456B4F) ----------------------------------------------------------
int Rules_HostBuyBarracks(int unused, double clips_context)
{
  int building_index = Rules_RtnLong(1, 0, clips_context);
  (void)unused;
  return Building_BuildBarracksByIndex(building_index, 0, 0);
}

//----- (00456B85) ----------------------------------------------------------
int Rules_HostBuyHospital(int unused, double clips_context)
{
  (void)unused;
  return Building_BuildHospitalByIndex(Rules_RtnLong(1, 0, clips_context), 0, 0);
}

//----- (00456BBB) ----------------------------------------------------------
int Rules_HostTechLevel(int unused, double clips_context)
{
  (void)unused;
  return Building_GetTechLevelByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456BF1) ----------------------------------------------------------
int Rules_HostBuildingType(int unused, double clips_context)
{
  (void)unused;
  return Building_GetTypeByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456C27) ----------------------------------------------------------
int Rules_HostPlayerStrength(int unused, double clips_context)
{
  (void)unused;
  return AI_TickNationPostTurn(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456C5D) ----------------------------------------------------------
int Rules_HostBuyWorkshop(int unused, double clips_context)
{
  (void)unused;
  return Building_BuildWorkshopByIndex(Rules_RtnLong(1, 0, clips_context), 0, 0);
}

//----- (00456C93) ----------------------------------------------------------
int Rules_HostHappiness(int unused, double clips_context)
{
  (void)unused;
  return Building_GetSatisfactionByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456CC9) ----------------------------------------------------------
int Rules_HostIsProduction(int unused, double clips_context)
{
  (void)unused;
  return Building_HasProductionByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456CFF) ----------------------------------------------------------
int Rules_HostPeasantCount(int unused, double clips_context)
{
  (void)unused;
  return Building_GetPeasantCountByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456D35) ----------------------------------------------------------
int Rules_HostIsMinimal(int unused, double clips_context)
{
  int candidate_row;
  int candidate_column;
  int site_column;
  int site_row;

  (void)unused;
  candidate_row = Rules_RtnLong(1, 0, clips_context);
  candidate_column = Rules_RtnLong(2, 0, clips_context);
  site_row = Rules_RtnLong(3, 0, clips_context);
  site_column = Rules_RtnLong(4, 0, clips_context);
  return Map_IsCastleSiteDistanceMinimal(candidate_row, candidate_column, site_column, site_row);
}

//----- (00456D8F) ----------------------------------------------------------
int Rules_HostCanBuyLicence(int unused, double clips_context)
{
  int building_index;
  unit_type licence_type;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  licence_type = (unit_type)Rules_RtnLong(2, 0, clips_context);
  return Building_CanBuyUnitLicenceByIndex(building_index, licence_type);
}

//----- (00456DD1) ----------------------------------------------------------
int Rules_HostLicenceIndex(int unused, double clips_context)
{
  int licence_type;
  int building_index;

  (void)unused;
  licence_type = Rules_RtnLong(2, 0, clips_context);
  building_index = Rules_RtnLong(1, 0, clips_context);
  return Building_FindUnitLicenceSlotIndexOrZero(building_index, (unit_type)(unsigned int)(licence_type));
}

//----- (00456E13) ----------------------------------------------------------
int Rules_HostLicenceInd(int unused, double clips_context)
{
  (void)unused;
  return Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456E49) ----------------------------------------------------------
int Rules_HostCanUpgradeWall(int unused, double clips_context)
{
  (void)unused;
  return Building_CanStartUpgradeByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456E7F) ----------------------------------------------------------
int Rules_HostTroopCount(int unused, double clips_context)
{
  (void)unused;
  return Building_GetGarrisonCountByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456EB5) ----------------------------------------------------------
int Rules_HostIsProductionAny(int unused, double clips_context)
{
  int licence_type;
  int building_index;

  (void)unused;
  licence_type = Rules_RtnLong(2, 0, clips_context);
  building_index = Rules_RtnLong(1, 0, clips_context);
  return Building_SelectedUnitLicenceMatchesTypeByIndex(building_index, (unit_type)(unsigned int)(licence_type));
}

//----- (00456EF7) ----------------------------------------------------------
int Rules_HostLeadOutPeasants(int unused, double clips_context)
{
  (void)unused;
  return Building_Transfer(
      Rules_RtnLong(1, 0, clips_context),
      Rules_RtnLong(2, 0, clips_context),
      Rules_RtnLong(4, 0, clips_context),
      Rules_RtnLong(3, 0, clips_context),
      clips_context);
}

//----- (00456F51) ----------------------------------------------------------
int Rules_HostUnitsToSchool(int unused, double clips_context)
{
  (void)unused;
  return Building_HasTrainableIdleGarrisonUnit(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456F87) ----------------------------------------------------------
int Rules_HostMaxTroopCount(int unused, double clips_context)
{
  (void)unused;
  return Building_IsGarrisonFullByIndex(Rules_RtnLong(1, 0, clips_context));
}

//----- (00456FBD) ----------------------------------------------------------
int Rules_HostUnitInCastleExists(int unused, double clips_context)
{
  int building_index;
  unit_type sought_type;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  sought_type = (unit_type)Rules_RtnLong(2, 0, clips_context);
  return Building_HasGarrisonUnitTypeByIndex(building_index, sought_type);
}

//----- (00456FFF) ----------------------------------------------------------
int Rules_HostUnitsToHospital(int unused, double clips_context)
{
  (void)unused;
  return Building_HasRepairableIdleGarrisonUnit(Rules_RtnLong(1, 0, clips_context));
}

//----- (00457035) ----------------------------------------------------------
int Rules_HostLeadOutTroop(int unused, double clips_context)
{
  int building_index = Rules_RtnLong(1, 0, clips_context);
  int unit_type_id = Rules_RtnLong(2, 0, clips_context);
  (void)unused;
  return Building_UnitsLeaveByUnitType(building_index, (unit_type)(unsigned int)(unit_type_id), 0, clips_context);
}

//----- (00457077) ----------------------------------------------------------
int Rules_HostLeadOutTroops(int unused, double clips_context)
{
  int building_index;

  (void)unused;
  building_index = Rules_RtnLong(1, 0, clips_context);
  return Building_UnitsLeaveReadyGarrisonSlots(building_index, 0, clips_context);
}

//----- (004570AD) ----------------------------------------------------------
int Rules_HostCastleName(int unused, double clips_context)
{
  (void)unused;
  return Player_GetInternedNameByIndex(Rules_RtnLong(1, 0, clips_context), 0, 0);
}

//----- (00457351) ----------------------------------------------------------
int Rules_HostEnterCastle(int unused, double clips_context)
{
  int building_index;
  int stack_index;

  (void)unused;
  building_index = Rules_RtnLong(2, 0, clips_context);
  stack_index = Rules_RtnLong(1, 0, clips_context);
  return (int)(intptr_t)UnitStack_MoveToBuildingAndCheckArrival(stack_index, building_index, clips_context);
}

//----- (00457393) ----------------------------------------------------------
int Rules_HostJoinTroop(int unused, double clips_context)
{
  int unit_index;
  int group_index;

  (void)unused;
  unit_index = Rules_RtnLong(1, 0, clips_context);
  group_index = Rules_RtnLong(2, 0, clips_context);
  return Script_UnitAddToGroup(unit_index, group_index, 0, clips_context);
}

//----- (004573D5) ----------------------------------------------------------
int Rules_HostRegroupTroops(int unused, double clips_context)
{
  int stack_index;
  int other_stack_index;

  (void)unused;
  other_stack_index = Rules_RtnLong(2, 0, clips_context);
  stack_index = Rules_RtnLong(1, 0, clips_context);
  return UnitStack_RegroupWithOtherStackByHealth(stack_index, other_stack_index, 0, 0, clips_context);
}

//----- (00457417) ----------------------------------------------------------
int Rules_HostRegroupCastle(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_RegroupWithBuildingGarrisonByHealth(
      Rules_RtnLong(1, 0, clips_context),
      Rules_RtnLong(2, 0, clips_context),
      0,
      0,
      clips_context);
}

//----- (00457459) ----------------------------------------------------------
int Rules_HostArmyHeadcount(int unused, double clips_context)
{
  int stack_index;
  int aggregate_mode;

  (void)unused;
  stack_index = Rules_RtnLong(1, 0, clips_context);
  aggregate_mode = Rules_RtnLong(2, 0, clips_context);
  return UnitStack_GetHealthPercentAggregate(stack_index, aggregate_mode);
}

//----- (0045749B) ----------------------------------------------------------
int Rules_HostArmyHasUnitsOfType(int unused, double clips_context)
{
  int stack_index;
  int sought_type;

  (void)unused;
  stack_index = Rules_RtnLong(1, 0, clips_context);
  sought_type = Rules_RtnLong(2, 0, clips_context);
  return UnitStack_HasUnitType(stack_index, (unit_type)sought_type);
}

//----- (0045751F) ----------------------------------------------------------
int Rules_HostCastleFreeSlotCount(int unused, double clips_context)
{
  (void)unused;
  return Building_CountFreeGarrisonSlots(Rules_RtnLong(1, 0, clips_context));
}

//----- (00457555) ----------------------------------------------------------
int Rules_HostEnemyPowerAtWalls(int unused, double clips_context)
{
  (void)unused;
  return Building_GetMaxEnemyStrengthUnderWalls(Rules_RtnLong(1, 0, clips_context));
}

//----- (0045758B) ----------------------------------------------------------
int Rules_HostFindRoadNearCastle(int unused, double clips_context)
{
  int stack_index;
  int building_index;

  (void)unused;
  stack_index = Rules_RtnLong(1, 0, clips_context);
  building_index = Rules_RtnLong(2, 0, clips_context);
  return UnitStack_QueuePathNearBuilding(stack_index, building_index, 0, 0);
}

//----- (004575CD) ----------------------------------------------------------
int Rules_HostHasUnitsToHeal(int unused, double clips_context)
{
  int stack_index;

  (void)unused;
  stack_index = Rules_RtnLong(1, 0, clips_context);
  return UnitStack_HasUnitsNeedingHealing(stack_index);
}

//----- (00457603) ----------------------------------------------------------
int Rules_HostFindCastleForHealing(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_FindPathToNearestHospitalCastle(Rules_RtnLong(1, 0, clips_context));
}

//----- (00457639) ----------------------------------------------------------
int Rules_HostGoToHealing(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_ExecuteHealingPathAndCheckArrival(Rules_RtnLong(1, 0, clips_context), 0, 0, clips_context);
}

//----- (0045766F) ----------------------------------------------------------
int Rules_HostPlagueInCastleExists(int unused, double clips_context)
{
  (void)unused;
  return Building_GetPlagueState(Rules_RtnLong(1, 0, clips_context));
}

//----- (004576A5) ----------------------------------------------------------
int Rules_HostPlagueInTroopExists(int unused, double clips_context)
{
  (void)unused;
  int stack_index = Rules_RtnLong(1, 0, clips_context);
  return UnitStack_HasPlagueByIndex(stack_index);
}

//----- (004576DB) ----------------------------------------------------------
int Rules_HostDetachWeakUnits(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_DetachWeakUnitsToAdjacentTile(Rules_RtnLong(1, 0, clips_context), 0, 0, clips_context);
}

//----- (00457711) ----------------------------------------------------------
int Rules_HostDetachUnitsOfType(int unused, double clips_context)
{
  (void)unused;
  return UnitStack_DetachUnitTypeToAdjacentTile(
      Rules_RtnLong(1, 0, clips_context),
      (unit_type)(unsigned int)(Rules_RtnLong(2, 0, clips_context)),
      0,
      0,
      clips_context);
}

//----- (00457753) ----------------------------------------------------------
int Rules_HostMarchAlongRoad(int unused, double clips_context)
{
  (void)unused;
  return Unit_ExecuteQueuedPathAndCheckFinished(Rules_RtnLong(1, 0, clips_context), 0, 0, clips_context);
}

//----- (00457789) ----------------------------------------------------------
int Rules_HostFindBest(int unused, double clips_context)
{
  (void)unused;
  return AI_FindBestStrategicTargetNearTile(
      Rules_RtnLong(1, 0, clips_context),   /* type_filter  -> eax */
      Rules_RtnLong(2, 0, clips_context),   /* owner_filter -> edx */
      Rules_RtnLong(4, 0, clips_context),   /* origin_x     -> ecx (CLIPS arg4, swapped) */
      Rules_RtnLong(3, 0, clips_context),   /* origin_y     -> ebx (CLIPS arg3, swapped) */
      Rules_RtnLong(5, 0, clips_context));  /* search_radius-> stack */
}
