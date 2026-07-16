/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (0043E500) --------------------------------------------------------
signed int  Building_UnitGetInto(
        int unitStackId,
        int buildingId,
        char a3,
        signed int i,
        double gameTime)
{
  int stack_record;
  int building_record;
  int slot_index;
  int source_slot;
  int target_slot;
  int squad_count;
  int peasant_count;
  __int16 *stack;

  (void)a3;
  (void)i;

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-enter");
  Debug_Log(unitStackId, buildingId, (DWORD)unitStackId, (int)aBuilding_unitg);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-log");
  Render_DrawSprite_v3(unitStackId, unitStackId);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-dump");

  stack_record = UNIT_STACK(unitStackId);
  building_record = BUILDING_RECORD(buildingId);
  stack = (__int16 *)stack_record;

  if ( *(_DWORD *)(stack_record + UNIT_STACK_PATH_OFFSET) )
    *(_DWORD *)(stack_record + UNIT_STACK_PATH_OFFSET) = 0;
  if ( UnitStack_HasPlague(stack_record) && (*(_BYTE *)(building_record + 435) & 7) == 0 )
    *(_BYTE *)(building_record + 435) = (*(_BYTE *)(building_record + 435) & 0xF8) | 6;

  if ( *(_BYTE *)(building_record + 4) )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      int slot = UNIT_STACK_SLOT(stack_record, slot_index);
      if ( *(__int16 *)slot == UNIT_TYPE_GOLD_CARGO )
      {
        *(_DWORD *)(building_record + 438) += 100 * *(char *)(slot + 9) / 100;
        *(__int16 *)slot = -1;
      }
    }
  }
  if ( *(_BYTE *)(building_record + 4) == 2 )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      int slot = UNIT_STACK_SLOT(stack_record, slot_index);
      if ( *(__int16 *)slot == UNIT_TYPE_PEASANT_CARGO )
      {
        peasant_count = (*(_WORD *)(building_record + 430) & 0x0FFF) + 100 * *(char *)(slot + 9) / 100;
        *(_WORD *)(building_record + 430) =
          (*(_WORD *)(building_record + 430) & 0xF000) | (peasant_count & 0x0FFF);
        *(__int16 *)slot = -1;
      }
    }
  }

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-compact-1");
  Unit_CompactSquad(stack, 0, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-compact-1");
  squad_count = Unit_GetSquadCount(stack_record);
  if ( !squad_count )
  {
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-unlink-empty");
    Rules_UnlinkArmyFact(stack, gameTime);
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-unlink-empty");
    return 1;
  }

  if ( squad_count <= Building_CountFreeGarrisonSlots(buildingId) )
  {
    for ( source_slot = 0; source_slot < UNIT_STACK_SLOT_COUNT; ++source_slot )
    {
      int source = UNIT_STACK_SLOT(stack_record, source_slot);
      if ( *(__int16 *)source == -1 )
        break;
      for ( target_slot = 0; target_slot < 12; ++target_slot )
      {
        int target = building_record + 18 + UNIT_STACK_SLOT_STRIDE * target_slot;
        if ( *(__int16 *)target == -1 )
        {
          qmemcpy((void *)target, (const void *)source, UNIT_STACK_SLOT_STRIDE);
          *(__int16 *)source = -1;
          break;
        }
      }
    }
  }

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-compact-2");
  Unit_CompactSquad(stack, 0, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-finalize");
  Rules_LinkArmyFinalize(stack, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-fact");
  Rules_LinkArmyFact(stack, 0, 0, gameTime, 0, (DWORD)stack_record);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-sync-strength");
  Rules_SyncArmyFactStrength(stack, 0, 0, 0, (DWORD)stack_record, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-garrison-change");
  if ( *(_DWORD *)(building_record + 463) )
    Building_OnGarrisonChange(buildingId, 0, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-done");
  return 1;
}
// 43E521: variable 'v5' is possibly undefined
// 43E543: variable 'v6' is possibly undefined
// 43E68A: variable 'v16' is possibly undefined
// 43E6E0: variable 'v15' is possibly undefined
// 43E6F2: variable 'v20' is possibly undefined
// 43E6F2: variable 'v21' is possibly undefined
// 43E6FB: variable 'v22' is possibly undefined
// 43E6FB: variable 'v23' is possibly undefined
// 43E70D: variable 'v24' is possibly undefined
// 43E70D: variable 'v25' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043E770) --------------------------------------------------------
signed int  Building_CanAcceptUnitStack(int stackIndex, int buildingId)
{
  int buildingRecord; // ecx
  int stackRecord; // edx
  unsigned __int8 buildingType; // al
  int v5; // edx
  int v6; // edx

  buildingRecord = UNIT_RECORD(buildingId);
  stackRecord = UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET;
  if ( *(_WORD *)(buildingRecord + 16) )
    return 0;
  buildingType = *(_BYTE *)(buildingRecord + 4);
  if ( !buildingType )
    return UnitStack_HasNormalCombatUnits(stackRecord);
  if ( buildingType > 1u )
    return buildingType == 2;
  if ( UnitStack_HasPeasantCargo(stackRecord) )
    return 0;
  return UnitStack_HasNormalCombatUnits(v5) || UnitStack_HasGoldCargo(v5) || UnitStack_HasSpecialPersonageUnits(v6);
}
// 43E7D7: variable 'v5' is possibly undefined
// 43E7F5: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043E820) --------------------------------------------------------
signed int  Building_HasUnitLicence(int building, unit_type unitType)
{
  int licenceEnd; // esi
  int hasLicence; // ecx

  licenceEnd = building + 12;
  hasLicence = 0;
  do
  {
    if ( *(char *)(building + 402) == unitType )
      hasLicence = 1;
    ++building;
  }
  while ( building != licenceEnd );
  return hasLicence;
}

//----- (0043E850) --------------------------------------------------------
BOOL  Building_BuyUnitLicence(int building, unit_type unitType, int a3, DWORD gameContext)
{
  int v5; // edx
  BOOL result; // eax
  int nationData; // eax
  unsigned int licenceCost; // esi
  int licenceSlotPtr; // edx
  int slotIndex; // eax

  Debug_Log(a3, building, gameContext, (int)aBuildingBuyUnitLicence);
  if ( Building_HasUnitLicence(building, unitType) )
    return 0;
  result = Building_IsUnitLicenceEligible((char *)building, unitType);
  if ( result )
  {
    nationData = gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(building + 2);
    licenceCost = (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * unitType];
    if ( !*(_DWORD *)(nationData + 140051) && *(int *)(nationData + 140055) >= 2 )
      licenceCost = (int)(75 * licenceCost) / 100;
    if ( licenceCost > *(_DWORD *)(building + 438) )
      return 0;
    licenceSlotPtr = building;
    slotIndex = 0;
    while ( *(char *)(licenceSlotPtr + 402) != -1 )
    {
      ++slotIndex;
      ++licenceSlotPtr;
      if ( slotIndex >= 12 )
      {
        if ( slotIndex == 12 )
          return 0;
        break;
      }
    }
    *(_DWORD *)(building + 438) -= licenceCost;
    *(_BYTE *)(building + slotIndex + 402) = unitType;
    return 1;
  }
  return result;
}
// 43E8D7: conditional instruction was optimized away because eax.4<C
// 43E86D: variable 'v5' is possibly undefined
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];
// 5202E4: using guessed type int gameData;

//----- (0043E940) --------------------------------------------------------
int  Building_RemoveUnitLicence(int building, unit_type unitType, DWORD gameContext)
{
  int activeProductionLicenceSlot; // eax
  int addonSlot; // edx

  Debug_Log(building, unitType, gameContext, (int)aBuildingRemoveUnitLicence);
  activeProductionLicenceSlot = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(building);
  if ( activeProductionLicenceSlot != -1 && *(signed __int8 *)(building + activeProductionLicenceSlot + 402) == unitType )
    Building_StopUnitProduction(building, unitType, gameContext);
  for ( addonSlot = 0; addonSlot < 12; ++addonSlot )
  {
    if ( *(signed __int8 *)(building + addonSlot + 402) == unitType )
    {
      *(_BYTE *)(building + addonSlot + 402) = -1;
      return building + addonSlot;
    }
  }
  return building + 12;
}

//----- (0043E9A0) --------------------------------------------------------
int  Building_SetUnitProduction(int building, char licenceSlot, DWORD gameContext)
{
  unsigned __int8 *buildingPtr; // ecx
  int slotIndex; // edx
  int result; // eax

  buildingPtr = (unsigned __int8 *)building;
  slotIndex = (unsigned __int8)licenceSlot;
  Debug_Log(building, licenceSlot, gameContext, (int)aBuildingSetUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = slotIndex;
  result = PLAYER_DATA_STRIDE * buildingPtr[2];
  BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = g_UnitTypeProductionTime[88 * (char)buildingPtr[slotIndex + 402]];
  if ( !*(_DWORD *)(result + gameData + 140051)
    && *(int *)(result + gameData + 140055) >= 1
    && (char)BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) > 1 )
  {
    --BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EA10) --------------------------------------------------------
void  Building_StopUnitProduction(int building, char unitType, DWORD gameContext)
{
  Debug_Log(building, unitType, gameContext, (int)aBuildingStopUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(building) = -1;
}

//----- (0043EA30) --------------------------------------------------------
_BYTE * Building_TrainUnit(int building, char garrisonSlot, DWORD gameContext)
{
  int slotIndex; // edx
  int buildingBase; // ecx
  _BYTE *result; // eax
  char trainingTurns; // bl
  char serviceStateBits; // bh

  slotIndex = (unsigned __int8)garrisonSlot;
  buildingBase = building;
  Debug_Log(building, garrisonSlot, gameContext, (int)aBuildingTrainUnit);
  result = (_BYTE *)(*(_BYTE *)(buildingBase + 31 * slotIndex + 30) & 3);
  if ( result != (_BYTE *)3 )
  {
    result = (_BYTE *)(buildingBase + BUILDING_GARRISON_SERVICE_STATE_OFFSET + slotIndex);
    if ( *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingBase + 2) + gameData + 140051) )
      trainingTurns = (*(_BYTE *)(buildingBase + 4) == 2) + 1;
    else
      trainingTurns = (*(_BYTE *)(buildingBase + 4) == 2) + 4;
    serviceStateBits = *result & 0xF8;
    *result = serviceStateBits;
    *result = trainingTurns & BUILDING_GARRISON_TRAINING_TURNS_MASK | serviceStateBits;
    BUILDING_GARRISON_SERVICE_STATE(buildingBase, slotIndex) &= 0xC7u;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EAC0) --------------------------------------------------------
int  Building_ClearGarrisonTrainingTimer(int result, int building)
{
  BUILDING_GARRISON_SERVICE_STATE(building, result) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
  return result;
}

//----- (0043EAD0) --------------------------------------------------------
__int16  Building_RepairUnit(int building, int slotIndex, DWORD gameContext)
{
  int currentHealth; // eax
  unsigned __int8 *repairTimer; // edx
  unsigned __int8 repairTurns; // al

  Debug_Log(building, slotIndex, gameContext, (int)aBuildingRepairUnit);
  currentHealth = *(signed __int8 *)(building + 31 * slotIndex + 27);
  if ( currentHealth != 100 )
  {
    repairTimer = (unsigned __int8 *)(building + BUILDING_GARRISON_SERVICE_STATE_OFFSET + slotIndex);
    repairTurns = (*(_BYTE *)(building + 4) == 2) + 2;
    *repairTimer = *repairTimer & 0xC0 | ((repairTurns & 7) << 3);
  }
  return currentHealth;
}

//----- (0043EB40) --------------------------------------------------------
int  Building_ClearGarrisonRepairTimer(int result, int building)
{
  BUILDING_GARRISON_SERVICE_STATE(building, result) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
  return result;
}

//----- (0043EB50) --------------------------------------------------------
int  Building_CountGarrison(int building)
{
  int garrisonEnd; // ebx
  int count; // edx

  garrisonEnd = building + 372;
  count = 0;
  do
  {
    if ( *(__int16 *)(building + 18) != -1 )
      ++count;
    building += 31;
  }
  while ( building != garrisonEnd );
  return count;
}

//----- (0043EB80) --------------------------------------------------------
int  Building_CountSpecialPersonageGarrisonEntries(int building)
{
  int garrisonEnd; // ebx
  int count; // ecx
  int unitType; // edx

  garrisonEnd = building + 372;
  count = 0;
  do
  {
    while ( 1 )
    {
      unitType = *(__int16 *)(building + 18);
      if ( unitType != -1 )
        break;
LABEL_5:
      building += 31;
      if ( building == garrisonEnd )
        return count;
    }
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      ++count;
      goto LABEL_5;
    }
    building += 31;
  }
  while ( building != garrisonEnd );
  return count;
}

int  Building_DrawGarrisonRow(int building)
{
  return Building_CountSpecialPersonageGarrisonEntries(building);
}

//----- (0043EBC0) --------------------------------------------------------
int  Building_CountNonCombatGarrisonEntries(int building)
{
  int slotPtr; // edx
  int count; // ecx
  int garrisonEnd; // ebx
  int unitType; // eax

  slotPtr = building;
  count = 0;
  garrisonEnd = building + 372;
  do
  {
    while ( 1 )
    {
      unitType = *(__int16 *)(slotPtr + 18);
      if ( unitType != -1 )
        break;
LABEL_5:
      slotPtr += 31;
      if ( slotPtr == garrisonEnd )
        return count;
    }
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE
      || unitType == UNIT_TYPE_GOLD_CARGO
      || unitType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++count;
      goto LABEL_5;
    }
    slotPtr += 31;
  }
  while ( slotPtr != garrisonEnd );
  return count;
}

//----- (0043EC10) --------------------------------------------------------
signed int  Building_HasSpecialPersonageGarrisonEntries(int building)
{
  int slotIndex; // edx
  int unitType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    unitType = *(__int16 *)(building + 18);
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++slotIndex;
    building += 31;
    if ( slotIndex >= 12 )
      return 0;
  }
  return 1;
}

//----- (0043EC40) --------------------------------------------------------
int  Building_CompactGarrison(unsigned __int8 *building, unsigned __int8 *a2, double gameTime)
{
  int writeIndex; // ebp
  int readIndex; // edx
  unsigned __int8 *movePtr; // eax
  unsigned __int8 *j; // ebx
  _BYTE *destPtr; // edi
  _BYTE *srcPtr; // esi
  int i; // [esp+4h] [ebp-20h]
  unsigned __int8 *slotPtr; // [esp+8h] [ebp-1Ch]

  writeIndex = 0;
  slotPtr = building;
  for ( i = 0; i < 11; ++i )
  {
    if ( *((__int16 *)slotPtr + 9) == -1 )
    {
      readIndex = writeIndex;
      movePtr = &building[31 * writeIndex];
      for ( j = &building[31 * writeIndex + 31]; readIndex < 11; destPtr[2] = srcPtr[2] )
      {
        destPtr = movePtr + 18;
        movePtr += 31;
        srcPtr = j + 18;
        j += 31;
        ++readIndex;
        qmemcpy(destPtr, srcPtr, 0x1Cu);
        srcPtr += 28;
        destPtr += 28;
        a2 = 0;
        *(_WORD *)destPtr = *(_WORD *)srcPtr;
      }
      *((_WORD *)movePtr + 9) = -1;
    }
    else
    {
      a2 = slotPtr + 31;
      ++writeIndex;
      slotPtr += 31;
    }
  }
  return Building_OnGarrisonChange(
           *(unsigned __int16 *)(TILE_INDEX(*building, building[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
           (int)a2,
           gameTime);
}
// 5202E4: using guessed type int gameData;

//----- (0043ED20) --------------------------------------------------------
BOOL  Building_IsUnitLicenceEligible(char *building, unit_type unitType)
{
  int buildingType; // eax
  int v5; // edx
  char requiredTechLevel; // al
  int i; // eax
  int smithReqType; // edx
  int j; // eax
  int workshopReqType; // edx

  buildingType = building[4];
  if ( !buildingType )
    return 0;
  v5 = 88 * unitType;
  requiredTechLevel = buildingType == 2
     ? g_UnitTypeProductionRequiredTechLevelMode2[v5]
     : g_UnitTypeProductionRequiredTechLevelOtherModes[v5];
  if ( (unsigned __int8)(building[444] & 7) < (unsigned __int8)requiredTechLevel )
    return 0;
  if ( (building[416] & BUILDING_ADDON_FLAG_SMITHS) == 0 )
  {
    for ( i = 0; ; ++i )
    {
      smithReqType = g_ProductionLicenceSmithsRequiredUnitTypes[i];
      if ( smithReqType == -1 || smithReqType == unitType )
        break;
    }
    if ( g_ProductionLicenceSmithsRequiredUnitTypes[i] == unitType )
      return 0;
  }
  if ( (building[416] & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
    return 1;
  for ( j = 0; ; ++j )
  {
    workshopReqType = g_ProductionLicenceWorkshopRequiredUnitTypes[j];
    if ( workshopReqType == -1 || workshopReqType == unitType )
      break;
  }
  return g_ProductionLicenceWorkshopRequiredUnitTypes[j] != unitType;
}

//----- (0043EDC0) --------------------------------------------------------
int  Building_AdjustAllGarrisonMoraleByDelta(int building, int moraleDelta)
{
  int slot; // ebp
  int slot_index; // ecx
  int result; // eax

  slot = building + 18;
  result = 0;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)slot != -1 )
      result = UnitSlot_AdjustMoraleByPredicate(slot, moraleDelta, UnitSlot_PredicateAlways);
    slot += 31;
  }
  return result;
}

//----- (0043EE10) --------------------------------------------------------
int  Building_CycleAllGarrisonOrdersOnce(int building)
{
  int garrisonBase; // esi
  int slotIndex; // edx
  int slotPtr; // ecx
  int result; // eax
  int v5; // edx
  int v6; // ecx

  garrisonBase = building + 18;
  slotIndex = 0;
  slotPtr = building;
  do
  {
    while ( 1 )
    {
      result = 31 * slotIndex;
      if ( *(__int16 *)(slotPtr + 18) != -1 )
        break;
      ++slotIndex;
      slotPtr += 31;
      if ( slotIndex >= 12 )
        return result;
    }
    result = UnitSlot_CycleOrderState(garrisonBase + result);
    slotIndex = v5 + 1;
    slotPtr = v6 + 31;
  }
  while ( slotIndex < 12 );
  return result;
}
// 43EE41: variable 'v5' is possibly undefined
// 43EE42: variable 'v6' is possibly undefined

//----- (0043EE50) --------------------------------------------------------
signed int  Building_GetTaxBurdenTier(int building)
{
  unsigned __int16 population; // ax
  int populationTier; // edx
  int thresholdIndex; // edx
  signed int result; // eax

  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  if ( population >= 0x1F4u )
  {
    if ( population >= 0x3E8u )
      populationTier = 2;
    else
      populationTier = 1;
  }
  else
  {
    populationTier = 0;
  }
  thresholdIndex = 4 * populationTier;
  result = 0;
  while ( (unsigned __int8)(*(_BYTE *)(building + 436) & 0x3F) > (unsigned __int8)g_SettlementTaxBurdenThresholds[thresholdIndex] )
  {
    ++result;
    ++thresholdIndex;
    if ( result > 3 )
      return 3;
  }
  return result;
}
// 43EE8A: conditional instruction was optimized away because eax.4<4

//----- (0043EED0) --------------------------------------------------------
__int16  Building_UpdatePopulationGrowth(int buildingRecord)
{
  uintptr_t building; // ecx
  int previous_growth; // edx/eax
  int satisfaction; // eax
  int growth_percent; // edx
  int peasant_count; // eax
  int new_growth; // eax/ebx
  unsigned __int16 growth_flags; // dx
  unsigned __int16 population_flags; // si
  int updated_population; // eax

  building = (uintptr_t)(unsigned int)buildingRecord;
  previous_growth = (__int16)(16 * *(_WORD *)(building + 432)) >> 4;
  if ( previous_growth <= 0 )
    satisfaction = previous_growth / 2;
  else
    satisfaction = previous_growth / 3;
  satisfaction += *(char *)(building + 434);
  if ( satisfaction > 100 )
    satisfaction = 100;
  if ( satisfaction < 0 )
    satisfaction = 0;
  *(_BYTE *)(building + 434) = satisfaction;

  growth_percent = (int)Rng_RandRange(3, 5);
  switch ( (unsigned __int8)Building_GetTaxBurdenTier((int)building) )
  {
    case TAX_BURDEN_TIER_LOW:
      growth_percent += 5;
      break;
    case TAX_BURDEN_TIER_HIGH:
      growth_percent -= 4;
      break;
    case TAX_BURDEN_TIER_SEVERE:
      growth_percent -= (int)Rng_RandRange(10, 15);
      break;
    default:
      break;
  }
  if ( (*(_BYTE *)(building + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
    growth_percent += 3;
  if ( (*(_BYTE *)(building + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
    ++growth_percent;
  if ( (*(_BYTE *)(building + 444) & 7u) > 1 )
    growth_percent += (*(_BYTE *)(building + 444) & 7) - 1;
  satisfaction = *(char *)(building + 434);
  if ( satisfaction > 75 )
  {
    ++growth_percent;
  }
  else if ( satisfaction < 30 )
  {
    growth_percent -= 2;
  }

  peasant_count = *(_WORD *)(building + 430) & 0x0FFF;
  new_growth = peasant_count * growth_percent / 100;
  growth_flags = *(_WORD *)(building + 432) & 0xF000;
  new_growth &= 0x0FFF;
  population_flags = *(_WORD *)(building + 430) & 0xF000;
  *(_WORD *)(building + 432) = growth_flags | new_growth;

  updated_population = peasant_count + ((__int16)(16 * (growth_flags | new_growth)) >> 4);
  updated_population &= 0x0FFF;
  *(_WORD *)(building + 430) = population_flags | updated_population;
  if ( updated_population > 2000 )
  {
    updated_population = 2000 - (int)Rng_RandRange(0, 100);
    updated_population &= 0x0FFF;
    *(_WORD *)(building + 430) = population_flags | updated_population;
  }
  return updated_population;
}

//----- (0043F0C0) --------------------------------------------------------
int  Building_CollectGoldIncome(int building)
{
  int incomeDivisor; // ecx
  unsigned __int16 population; // ax
  int goldIncome; // ecx
  int result; // eax
  int currentGold; // esi

  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(building + 2) + 140051) )
    incomeDivisor = 400;
  else
    incomeDivisor = 200;
  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  goldIncome = (*(_BYTE *)(building + 436) & 0x3F) * population / incomeDivisor;
  result = *(char *)(building + 434);
  if ( result < 25 )
  {
    result = goldIncome / 2;
    goldIncome /= 2;
  }
  if ( (*(_BYTE *)(building + 435) & 7) != 0 )
    goldIncome = 0;
  currentGold = *(_DWORD *)(building + 438);
  *(_WORD *)(building + 442) = goldIncome;
  *(_DWORD *)(building + 438) = goldIncome + currentGold;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043F160) --------------------------------------------------------
__int16  Building_UpdatePlagueState(unsigned int buildingRecord)
{
  uintptr_t building; // ecx
  unsigned int plague_state; // eax
  unsigned int population; // ebx
  unsigned int plague_roll; // eax
  unsigned __int16 population_flags; // dx
  unsigned int result; // eax
  unsigned char building_state; // dl

  building = (uintptr_t)buildingRecord;
  plague_state = *(_BYTE *)(building + 435) & 7;
  if ( plague_state )
  {
    building_state = *(_BYTE *)(building + 435) & 0xF8;
    *(_BYTE *)(building + 435) = building_state | ((plague_state - 1) & 7);
    population = *(_WORD *)(building + 430) & 0x0FFF;
    plague_roll = Rng_RandRange(15, 25);
    population -= population * plague_roll / 100;
    population_flags = *(_WORD *)(building + 430) & 0xF000;
    *(_WORD *)(building + 430) = population_flags | (population & 0x0FFF);
    return population;
  }

  result = *(_WORD *)(building + 430) & 0x0FFF;
  if ( result >= 1000 )
  {
    result = Rng_RandRange(0, 2000 - result + 300);
    if ( result < 100 )
    {
      building_state = *(_BYTE *)(building + 435) & 0xF8;
      *(_BYTE *)(building + 435) = building_state | 5;
    }
  }
  return result;
}

//----- (0043F240) --------------------------------------------------------
int  Building_GetTotalValue(int building)
{
  int goldReserve; // ecx
  unsigned __int16 population; // ax
  int totalValue; // ecx
  int licencePtr; // eax
  int licenceEnd; // ebx
  int licenceType; // edx

  goldReserve = *(_DWORD *)(building + 438);
  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  totalValue = 190 * (*(_DWORD *)(building + 416) << 29 >> 31)
     + 200 * (*(_DWORD *)(building + 416) << 30 >> 31)
     + 230 * (*(_DWORD *)(building + 416) << 27 >> 31)
     + 400 * (*(_DWORD *)(building + 416) << 28 >> 31)
     + 200 * (*(_DWORD *)(building + 416) & BUILDING_ADDON_FLAG_HOSPITAL)
     + population
     + goldReserve;
  licencePtr = building;
  licenceEnd = building + 12;
  do
  {
    licenceType = *(char *)(licencePtr + 402);
    if ( licenceType != -1 )
      totalValue += (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * licenceType];
    ++licencePtr;
  }
  while ( licencePtr != licenceEnd );
  return totalValue;
}
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];

//----- (0043F340) --------------------------------------------------------
int  AI_TickNationPostTurn(int playerIndex)
{
  int totalValue; // ecx
  int buildingIndex; // edx
  int buildingOffset; // ebx
  int buildingState; // eax
  int buildingRecord; // eax
  int buildingValue; // eax
  int v7; // ecx
  int i; // edi
  int j; // eax
  int cargoType; // edx

  totalValue = 0;
  buildingIndex = 0;
  buildingOffset = 0;
  do
  {
    buildingState = *(char *)(buildingOffset + gameData + 509678);
    if ( (buildingState == 2 || buildingState == 1) && *(unsigned __int8 *)(buildingOffset + gameData + 509676) == playerIndex && buildingIndex >= 0 )
    {
      buildingRecord = buildingOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( (unsigned int)*(char *)(buildingRecord + 4) < 4 && *(__int16 *)(buildingRecord + 16) != -1 )
      {
        buildingValue = Building_GetTotalValue(buildingRecord);
        totalValue = buildingValue + v7;
      }
    }
    ++buildingIndex;
    buildingOffset += 467;
  }
  while ( buildingIndex < 100 );
  for ( i = 0; i != 362500; i += 725 )
  {
    if ( *(unsigned __int8 *)(i + gameData + 147178) == playerIndex && *(__int16 *)(i + gameData + 147180) != -1 )
    {
      for ( j = 0; j != 310; j += 31 )
      {
        cargoType = *(__int16 *)(i + gameData + j + 147180);
        if ( cargoType == UNIT_TYPE_GOLD_CARGO || cargoType == UNIT_TYPE_PEASANT_CARGO )
          totalValue += *(char *)(i + gameData + j + 147189);
      }
    }
  }
  return totalValue;
}
// 43F391: conditional instruction was optimized away because edx.4<64u
// 43F3A0: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 43F3B5: variable 'v7' is possibly undefined
// 43F3B7: variable 'v2' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043F460) --------------------------------------------------------
int  Player_CalcAvailableStrongholdFunds(int playerIndex)
{
  int totalFunds; // edi
  int buildingIndex; // eax
  int buildingOffset; // edx
  int buildingState; // ecx
  int buildingRecord; // ecx

  totalFunds = 0;
  buildingIndex = 0;
  buildingOffset = 0;
  do
  {
    buildingState = *(char *)(gameData + buildingOffset + 509678);
    if ( (buildingState == 2 || buildingState == 1) && *(unsigned __int8 *)(buildingOffset + gameData + 509676) == playerIndex && buildingIndex >= 0 )
    {
      buildingRecord = buildingOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( (unsigned int)*(char *)(buildingRecord + 4) < 4 && *(__int16 *)(buildingRecord + 16) != -1 )
        totalFunds += *(_DWORD *)(buildingOffset + gameData + 510112);
    }
    ++buildingIndex;
    buildingOffset += 467;
  }
  while ( buildingIndex < 100 );
  return totalFunds;
}
// 43F4AE: conditional instruction was optimized away because eax.4<64u
// 43F4BE: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;

//----- (0043F500) --------------------------------------------------------
int  Player_SpendStrongholdFundsEvenly(int playerIndex, signed int remaining)
{
  int strongholdCount; // ecx
  int i; // eax
  int buildingState; // edx
  unsigned int sharePerStronghold; // esi
  int buildingOffset; // edx
  int result; // eax
  unsigned int availableFunds; // ebp

  do
  {
    strongholdCount = 0;
    for ( i = 0; i != 46700; i += 467 )
    {
      buildingState = *(char *)(gameData + i + 509678);
      if ( (buildingState == 2 || buildingState == 1)
        && *(unsigned __int8 *)(i + gameData + 509676) == playerIndex
        && *(_DWORD *)(i + gameData + 510112) )
      {
        ++strongholdCount;
      }
    }
    sharePerStronghold = remaining / strongholdCount;
    if ( !(remaining / strongholdCount) )
    {
      strongholdCount = 1;
      sharePerStronghold = remaining;
    }
    buildingOffset = 0;
    do
    {
      result = *(char *)(buildingOffset + gameData + 509678);
      if ( result == 2 || result == 1 )
      {
        result = buildingOffset + gameData;
        if ( playerIndex == *(unsigned __int8 *)(buildingOffset + gameData + 509676) )
        {
          availableFunds = *(_DWORD *)(result + 510112);
          if ( availableFunds )
          {
            --strongholdCount;
            if ( sharePerStronghold > availableFunds )
            {
              *(_DWORD *)(result + 510112) = 0;
              remaining -= availableFunds;
            }
            else
            {
              remaining -= sharePerStronghold;
              *(_DWORD *)(result + 510112) = availableFunds - sharePerStronghold;
            }
          }
        }
      }
      buildingOffset += 467;
    }
    while ( buildingOffset < 46700 && strongholdCount );
  }
  while ( remaining );
  return result;
}
// 43F5D4: conditional instruction was optimized away because ecx.4!=0
// 5202E4: using guessed type int gameData;

//----- (0043F600) --------------------------------------------------------
int BuildingSpriteCache_Reset(void)
{
  int result; // eax

  for ( result = 0; result != 650; result += 13 )
    g_BuildingSpriteCache[result] = -1;
  return result;
}

//----- (0043F630) --------------------------------------------------------
int  BuildingSpriteCache_LoadEntry(
        int buildingKind,
        int variantIndex,
        signed int orientation,
        int assetSet,
        DWORD allocContext,
        signed int a6,
        int frameIndex)
{
  int entry_index;
  int entry_offset;
  unsigned int oldest_tick;
  int i;
  signed int orientationBaseIndex; // eax
  signed int spriteSubIndex; // ebx
  int spriteAssetIndex; // ebx
  unsigned __int8 mapThemeIndex; // al
  int orientationSubIndex; // eax
  int variantSubIndex; // ebx
  int spriteHandleTheme0; // eax
  int spriteHandleTheme1; // eax
  int spriteHandleTheme2; // eax

  (void)a6;
  entry_index = -1;
  for ( i = 0; i < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++i )
  {
    if ( g_BuildingSpriteCache[BUILDING_SPRITE_CACHE_RECORD_STRIDE * i] == -1 )
    {
      entry_index = i;
      break;
    }
  }
  if ( entry_index < 0 )
  {
    oldest_tick = (unsigned int)-1;
    entry_index = 0;
    for ( i = 0; i < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++i )
    {
      int last_used_tick;

      entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * i;
      last_used_tick = *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9);
      if ( oldest_tick > (unsigned int)last_used_tick )
      {
        oldest_tick = (unsigned int)last_used_tick;
        entry_index = i;
      }
    }
    DLXSprite_ReleaseAndClear((int *)(void *)(g_BuildingSpriteCache + BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index + 5));
  }
  entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index;
  g_BuildingSpriteCache[entry_offset] = (char)buildingKind;
  g_BuildingSpriteCacheKeyCol2[entry_offset] = (char)variantIndex;
  g_BuildingSpriteCacheKeyCol3[entry_offset] = (char)assetSet;
  g_BuildingSpriteCacheKeyCol4Signed[entry_offset] = (char)orientation;
  g_BuildingSpriteCacheKeyCol5[entry_offset] = (char)frameIndex;
  *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(entry_index, entry_offset);
  if ( buildingKind )
  {
    if ( orientation >= 3 )
    {
      variantSubIndex = 4 * variantIndex + 12 + frameIndex;
    }
    else
    {
      if ( orientation == -1 )
        orientationSubIndex = frameIndex + 32;
      else
        orientationSubIndex = frameIndex + 4 * orientation;
      variantSubIndex = orientationSubIndex;
    }
    spriteAssetIndex = 36 * assetSet + 180 * (buildingKind - 1) + 45 + variantSubIndex;
  }
  else
  {
    if ( orientation >= 3 )
    {
      spriteSubIndex = variantIndex + 3;
    }
    else
    {
      if ( orientation == -1 )
        orientationBaseIndex = 8;
      else
        orientationBaseIndex = orientation;
      spriteSubIndex = orientationBaseIndex;
    }
    spriteAssetIndex = 9 * assetSet + spriteSubIndex;
  }
  mapThemeIndex = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
  if ( mapThemeIndex == 0 )
  {
    spriteHandleTheme0 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme0 )
      spriteHandleTheme0 = DLXSprite_LoadCachedEntry(spriteHandleTheme0, aBuildin1_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme0;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( mapThemeIndex == 1 )
  {
    spriteHandleTheme1 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme1 )
      spriteHandleTheme1 = DLXSprite_LoadCachedEntry(spriteHandleTheme1, aBuildin2_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme1;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( mapThemeIndex == 2 )
  {
    spriteHandleTheme2 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme2 )
      spriteHandleTheme2 = DLXSprite_LoadCachedEntry(spriteHandleTheme2, aBuildin3_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme2;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
}
// 5202E4: using guessed type int gameData;
// 5438ED: using guessed type int dword_5438ED;
// 5438F1: using guessed type int dword_5438F1;

//----- (0043F880) --------------------------------------------------------
int  BuildingSpriteCache_GetOrLoadEntry(DWORD buildingKind, int variantIndex, signed int orientation, int assetSet, int frameIndex)
{
  int entry_index;

  for ( entry_index = 0; entry_index < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++entry_index )
  {
    int entry_offset;

    entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index;
    if ( (signed char)g_BuildingSpriteCache[entry_offset] == (int)buildingKind )
    {
      if ( (unsigned char)g_BuildingSpriteCacheKeyCol2[entry_offset] == (unsigned int)variantIndex )
      {
        if ( (unsigned char)g_BuildingSpriteCacheKeyCol3[entry_offset] == (unsigned int)assetSet )
        {
          if ( (signed char)g_BuildingSpriteCacheKeyCol4Signed[entry_offset] == orientation )
          {
            if ( (unsigned char)g_BuildingSpriteCacheKeyCol5[entry_offset] == (unsigned int)frameIndex )
            {
              *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(frameIndex, entry_index);
              return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
            }
          }
        }
      }
    }
  }
  return BuildingSpriteCache_LoadEntry(buildingKind, variantIndex, orientation, assetSet, buildingKind, variantIndex, frameIndex);
}
// 5438ED: using guessed type int dword_5438ED;
// 5438F1: using guessed type int dword_5438F1;

//----- (0043F920) --------------------------------------------------------
int BuildingSpriteCache_Clear(void)
{
  int i; // edx
  int result; // eax

  for ( i = 0; i != 650; i += 13 )
  {
    while ( 1 )
    {
      result = g_BuildingSpriteCache[i];
      if ( result != -1 )
        break;
      i += 13;
      if ( i == 650 )
        return result;
    }
    g_BuildingSpriteCache[i] = -1;
    result = DLXSprite_ReleaseAndClear((int *)(void *)&g_BuildingSpriteCache[i + 5]);
    *(int *)(void *)(g_BuildingSpriteCache + i + 5) = 0;
  }
  return result;
}
// 5438ED: using guessed type int dword_5438ED;

//----- (0043F980) --------------------------------------------------------
int BuildingSpriteCache_CountEntries(void)
{
  int count; // edx
  int i; // eax

  count = 0;
  for ( i = 0; i != 650; i += 13 )
  {
    if ( g_BuildingSpriteCache[i] != -1 )
      ++count;
  }
  return count;
}

//----- (0043F9B0) --------------------------------------------------------
int Rules_RebuildTempleFacts(void)
{
  int i; // ebx
  int result; // eax
  int j; // ecx
  int v4; // ecx

  for ( i = 0; ; ++i )
  {
    result = gameData;
    if ( i >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    for ( j = 0; j < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); j = v4 + 1 )
    {
      if ( MapTile_GetReligiousSiteCategory(i, j) )
        Rules_LogTempleFact(i, v4);
    }
  }
  return result;
}
// 43F9E8: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043FB10) --------------------------------------------------------
signed int  MapTile_GetReligiousSiteCategory(int tileX, int tileY)
{
  signed int result; // eax

  switch ( *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY + 2) )
  {
    case TILE_OVERLAY_SHRINE_A:
    case TILE_OVERLAY_SHRINE_B:
    case TILE_OVERLAY_SHRINE_C:
      result = RELIGIOUS_SITE_CATEGORY_SHRINE;
      break;
    case TILE_OVERLAY_EMPTY_SHRINE_A:
    case TILE_OVERLAY_EMPTY_SHRINE_B:
    case TILE_OVERLAY_EMPTY_SHRINE_C:
      result = RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE;
      break;
    case TILE_OVERLAY_CULT_PLACE_A:
    case TILE_OVERLAY_CULT_PLACE_B:
    case TILE_OVERLAY_CULT_PLACE_C:
      result = RELIGIOUS_SITE_CATEGORY_CULT_PLACE;
      break;
    case TILE_OVERLAY_EMPTY_CULT_PLACE_A:
    case TILE_OVERLAY_EMPTY_CULT_PLACE_B:
    case TILE_OVERLAY_EMPTY_CULT_PLACE_C:
      result = RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE;
      break;
    default:
      result = RELIGIOUS_SITE_CATEGORY_NONE;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FBA0) --------------------------------------------------------
int * Temple_GenerateApproachTrack(int stackIndex, int tileX, int a3, int tileY)
{
  int tile_column_offset; // ebp
  int tile_record_offset; // eax
  unsigned __int16 saved_site_word; // dx
  int current_y; // ebx
  int *result; // eax

  (void)a3;
  tile_column_offset = TILE_TERRAIN_ROW_STRIDE * tileX;
  tile_record_offset = tile_column_offset + 14 * tileY;
  Debug_Log(stackIndex, tileX, tileY, (int)aUnit_movetra_2);
  saved_site_word = *(_WORD *)(gameData + tile_record_offset + 2);
  *(_WORD *)(gameData + tile_record_offset + 2) = -1;
  current_y = *(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + 147176);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_request", stackIndex, tileX, tileY, saved_site_word);
  result = Unit_MoveTrack(
             stackIndex,
             *(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET),
             tileX,
             current_y,
             tileX,
             tileY);
  *(_WORD *)(gameData + tile_record_offset + 2) = saved_site_word;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_result", stackIndex, tileX, tileY, result ? *result : -1);
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FC60) --------------------------------------------------------
__int16 * Temple_SpawnGiftUnitGroup(int tileX, int tileY, double gameTime)
{
  char v3; // cl
  signed int giftUnitCount; // ebp
  _WORD *scriptedSlotPtr; // edi
  int i; // esi
  __int16 *result; // eax
  signed int spawnedCount; // edi
  _WORD *randomSlotPtr; // esi
  int missionIndex; // ebx
  unsigned int troopRoll; // eax
  char v12; // cl
  char ownerFaction; // bl
  unit_type unitType; // edx
  unsigned int monsterRoll; // eax
  char v16; // cl
  _WORD unitStack[172]; // [esp+0h] [ebp-170h] BYREF
  int siteX; // [esp+158h] [ebp-18h]
  int siteY; // [esp+15Ch] [ebp-14h]

  siteX = tileX;
  siteY = tileY;
  giftUnitCount = Rng_RandRange(1, 5);
  if ( ACTIVE_MISSION_INDEX == 2 && siteX == 95 && siteY == 16 || ACTIVE_MISSION_INDEX == 12 && siteX == 58 && siteY == 77 )
  {
    scriptedSlotPtr = unitStack;
    for ( i = 0; i != 4; ++i )
    {
      UnitSlot_InitFromType((int)scriptedSlotPtr, g_TempleGiftUnitPool_ScriptedRam[i], v3);
      scriptedSlotPtr = (_WORD *)((char *)scriptedSlotPtr + 31);
    }
    giftUnitCount = 4;
  }
  else
  {
    spawnedCount = 0;
    if ( giftUnitCount > 0 )
    {
      randomSlotPtr = unitStack;
      do
      {
        missionIndex = ACTIVE_MISSION_INDEX;
        if ( missionIndex == 2 || missionIndex == 6 || missionIndex == 12 || missionIndex == 16 )
        {
          troopRoll = Rng_RandRange(0, 6);
          ownerFaction = v12;
          unitType = g_TempleGiftUnitPool_HumanTroops[troopRoll];
        }
        else
        {
          monsterRoll = Rng_RandRange(0, 4);
          ownerFaction = v16;
          unitType = g_TempleGiftUnitPool_MinorMonsters[monsterRoll];
        }
        UnitSlot_InitFromType((int)randomSlotPtr, unitType, ownerFaction);
        ++spawnedCount;
        randomSlotPtr = (_WORD *)((char *)randomSlotPtr + 31);
      }
      while ( spawnedCount < giftUnitCount );
    }
  }
  *(_WORD *)((char *)unitStack + 31 * giftUnitCount) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(siteX, siteY, (unsigned __int8 *)unitStack, gameTime);
  if ( result )
    return (__int16 *)UI_StartWorldMapUnitAttentionFlash(
                        *(unsigned __int16 *)(TILE_INDEX(*result, result[1])),
                        (int)result,
                        200 * *result + gameData);
  return result;
}
// 43FCBB: variable 'v3' is possibly undefined
// 43FD55: variable 'v12' is possibly undefined
// 43FD89: variable 'v16' is possibly undefined
// 515D10: using guessed type unit_type dword_515D10[5];
// 515D24: using guessed type unit_type dword_515D24[7];
// 515D40: using guessed type unit_type dword_515D40[];
// 5202E4: using guessed type int gameData;

//----- (0043FDE0) --------------------------------------------------------
__int16 * Temple_SpawnGiftGoldCargoStack(signed int goldAmount, int originX, char ownerFaction, int originY, double gameTime)
{
  int cargoSlotCount; // esi
  int fullCargoByteLimit; // ebp
  int i; // ecx
  signed int goldTotal; // eax
  int lastSlotIndex; // esi
  char partialGold; // dl
  __int16 *result; // eax
  _WORD cargoStack[4]; // [esp+0h] [ebp-170h] BYREF
  char v14[335]; // [esp+9h] [ebp-167h]
  int spawnY; // [esp+158h] [ebp-18h]
  int spawnX; // [esp+15Ch] [ebp-14h]
  signed int goldAmountCopy; // [esp+160h] [ebp-10h]

  goldAmountCopy = goldAmount;
  spawnX = originX;
  spawnY = originY;
  cargoSlotCount = 0;
  fullCargoByteLimit = 31 * (goldAmount / 100);
  for ( i = 0; i <= fullCargoByteLimit; UnitSlot_InitFromType((int)cargoStack + i, UNIT_TYPE_GOLD_CARGO, ownerFaction) )
    ++cargoSlotCount;
  goldTotal = goldAmountCopy;
  *(_WORD *)((char *)cargoStack + i) = -1;
  lastSlotIndex = cargoSlotCount - 1;
  partialGold = 100 * (goldTotal % 100) / 100;
  v14[31 * lastSlotIndex] = partialGold;
  if ( !partialGold )
    *(_WORD *)((char *)cargoStack + 31 * lastSlotIndex) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(spawnX, spawnY, (unsigned __int8 *)cargoStack, gameTime);
  if ( result )
    return (__int16 *)UI_StartWorldMapUnitAttentionFlash(
                        *(unsigned __int16 *)(TILE_INDEX(*result, result[1])),
                        (int)result,
                        gameData + 200 * *result);
  return result;
}
// 43FE25: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;
