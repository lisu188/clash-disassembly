/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0041F1A0) --------------------------------------------------------
signed int  Building_Transfer(int buildingIndex, int targetStackIndex, int transferGold, int transferAmount, double a5)
{
  int buildingByteOffset; // edx
  unsigned __int16 populationField; // ax
  signed int result; // eax
  unsigned __int8 *buildingPtrCopy; // ecx
  int newStackBase; // ecx
  unsigned int squadWritePtr; // ebx
  int v12; // ecx
  int squadCount; // eax
  __int16 *squadTemplatePtr; // esi
  int partialSquadFill; // eax
  __int16 *partialSquadTemplatePtr; // esi
  int v17; // edx
  __int64 amount64; // rtt
  int *pathTrack; // esi
  int pathNode; // edx
  int currentPopulation; // eax
  int newPopulation; // eax
  unsigned __int8 *buildingPtrBase; // edx
  int buildingType; // ebx
  int newPathLen; // eax
  int pathStartTile; // edx
  __int16 *newStackHdr; // ecx
  __int16 *pathDest; // edi
  __int16 *newStackReady; // eax
  __int16 tileOccupantValue; // dx
  unsigned __int8 *buildingPtrTile; // ebx
  unsigned __int8 *buildingPtrFlags; // ebx
  int v33; // ecx
  __int16 *newStackForFact; // edx
  __int16 *newStackSpawn; // edx
  int spawnRow; // [esp+0h] [ebp-2Ch] BYREF
  int spawnColumn; // [esp+4h] [ebp-28h] BYREF
  __int16 *newStackPtr; // [esp+8h] [ebp-24h]
  int buildingTileByteOffset; // [esp+Ch] [ebp-20h]
  int targetUnitRecord; // [esp+10h] [ebp-1Ch]
  int savedBuildingIndex; // [esp+14h] [ebp-18h]
  int savedTargetStack; // [esp+18h] [ebp-14h]
  int transferGoldFlag; // [esp+1Ch] [ebp-10h]
  int amount; // [esp+20h] [ebp-Ch]
  int i; // [esp+24h] [ebp-8h]
  unsigned __int8 *buildingPtr; // [esp+28h] [ebp-4h]
  _DWORD savedregs[3]; // [esp+2Ch] [ebp+0h] BYREF

  savedBuildingIndex = buildingIndex;
  savedTargetStack = targetStackIndex;
  amount = transferAmount;
  transferGoldFlag = transferGold;
  Debug_Log(transferGold, targetStackIndex, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aBuildingTransfer);
  buildingPtr = (unsigned __int8 *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET + buildingByteOffset);
  targetUnitRecord = 0;
  if ( targetStackIndex != -1 )
    targetUnitRecord = UNIT_RECORD(targetStackIndex);
  if ( transferGoldFlag && (unsigned int)amount > *(_DWORD *)(buildingPtr + 438) )
    return 0;
  if ( !transferGoldFlag )
  {
    populationField = *((_WORD *)buildingPtr + 215);
    HIBYTE(populationField) &= 0xFu;
    if ( populationField < amount )
      return 0;
  }
  if ( Building_FindFreeAdjacentSpawnTile(buildingPtr, (_DWORD*)(&spawnRow), gameData + BUILDING_TABLE_OFFSET + buildingByteOffset, (_DWORD*)(&spawnColumn)) != 1 )
    return 0;
  WorldMap_DisableFrameRedraw();
  *(_WORD *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) = -1;
  buildingPtrCopy = buildingPtr;
  *(_WORD *)(uintptr_t)(gameData + TILE_ROW_STRIDE * (*buildingPtr + 1) + 2 * buildingPtr[1] + TILE_MAP_OFFSET) = -1;
  *(_WORD *)(uintptr_t)(200 * (*buildingPtrCopy + 1) + gameData + 2 * buildingPtrCopy[1] + 556376) = -1;
  *(_WORD *)(uintptr_t)(200 * *buildingPtrCopy + gameData + 2 * buildingPtrCopy[1] + 556376) = -1;
  result = Unit_Create((unit_type)(unsigned int)((char)((transferGoldFlag == 0) + 31)), buildingPtrCopy[2], *buildingPtrCopy, 0, buildingPtrCopy[1]);
  if ( result )
  {
    newStackPtr = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) + gameData + UNIT_STACK_TABLE_OFFSET);
    UnitStack_ClearRemainingActionPoints(newStackPtr, (DWORD)(intptr_t)savedregs, a5);
    squadWritePtr = newStackBase + 6;
    v12 = 100;
    squadCount = amount / 100;
    for ( i = 1; squadCount >= i; ++i )
    {
      squadTemplatePtr = newStackPtr + 3;
      qmemcpy((void *)(uintptr_t)squadWritePtr, newStackPtr + 3, 0x1Cu);
      squadTemplatePtr += 14;
      v12 = 0;
      *(_WORD *)(uintptr_t)(squadWritePtr + 28) = *squadTemplatePtr;
      *(_BYTE *)(uintptr_t)(squadWritePtr + 30) = *((_BYTE *)squadTemplatePtr + 2);
      squadWritePtr += UNIT_SLOT_RECORD_BYTES;
    }
    if ( i <= 10 )
    {
      partialSquadFill = amount;
      partialSquadTemplatePtr = newStackPtr + 3;
      v17 = amount;
      qmemcpy((void *)(uintptr_t)squadWritePtr, newStackPtr + 3, 0x1Cu);
      partialSquadTemplatePtr += 14;
      *(_WORD *)(uintptr_t)(squadWritePtr + 28) = *partialSquadTemplatePtr;
      *(_BYTE *)(uintptr_t)(squadWritePtr + 30) = *((_BYTE *)partialSquadTemplatePtr + 2);
      v12 = 100;
      LODWORD(amount64) = partialSquadFill;
      HIDWORD(amount64) = v17 >> 31;
      LOBYTE(partialSquadFill) = (int)(100 * (amount64 % 100)) / 100;
      UNIT_SLOT_HEALTH_PERCENT(squadWritePtr) = partialSquadFill;
      if ( !(_BYTE)partialSquadFill )
        *(_WORD *)(uintptr_t)squadWritePtr = -1;
    }
    if ( transferGoldFlag )
    {
      *(_DWORD *)(buildingPtr + 438) -= amount;
    }
    else
    {
      HIWORD(currentPopulation) = HIWORD(buildingPtr);
      LOWORD(currentPopulation) = *((_WORD *)buildingPtr + 215);
      BYTE1(currentPopulation) &= 0xFu;
      newPopulation = currentPopulation - amount;
      buildingPtrBase = buildingPtr;
      LOWORD(squadWritePtr) = *((_WORD *)buildingPtr + 215);
      squadWritePtr &= 0xFFFFF000;
      BYTE1(newPopulation) &= 0xFu;
      *((_WORD *)buildingPtr + 215) = squadWritePtr;
      v12 = newPopulation | squadWritePtr;
      *((_WORD *)buildingPtrBase + 215) = newPopulation | squadWritePtr;
    }
    if ( targetUnitRecord
      && (pathTrack = (int *)Building_GenerateApproachTrack(
                         *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])),
                         savedTargetStack,
                         (int)(intptr_t)buildingPtr,
                         squadWritePtr,
                         (DWORD)(intptr_t)savedregs)) != 0 )
    {
      while ( 1 )
      {
        pathNode = pathTrack[*pathTrack];
        if ( (_WORD)pathNode != *(_WORD *)buildingPtr )
        {
          buildingType = (char)buildingPtr[4];
          if ( buildingType != 1 && buildingType != 2 )
            break;
          if ( (unsigned __int8)pathNode < *buildingPtr
            || (unsigned __int8)pathNode > *buildingPtr + 1
            || BYTE1(pathNode) < buildingPtr[1]
            || BYTE1(pathNode) > buildingPtr[1] + 1 )
          {
            break;
          }
        }
        --*pathTrack;
      }
      newPathLen = *pathTrack - 1;
      *pathTrack = newPathLen;
      pathStartTile = pathTrack[newPathLen + 1];
      newStackHdr = newStackPtr;
      *newStackPtr = (unsigned __int8)pathStartTile;
      newStackHdr[1] = BYTE1(pathStartTile);
      buildingTileByteOffset = 2 * buildingPtr[1] + gameData + 200 * *buildingPtr;
      pathDest = newStackPtr + 158;
      *(_WORD *)(uintptr_t)(2 * BYTE1(pathStartTile) + TILE_ROW_STRIDE * (unsigned __int8)pathStartTile + gameData + TILE_MAP_OFFSET) = *(_WORD *)(uintptr_t)(buildingTileByteOffset + 556374);
      newStackReady = newStackPtr;
      qmemcpy(pathDest, pathTrack, UNIT_STACK_PATH_BYTES);
      UnitStack_SetReadyFlags((int)(intptr_t)newStackReady);
    }
    else
    {
      Building_FindFreeAdjacentSpawnTile(buildingPtr, (_DWORD*)(&spawnRow), v12, (_DWORD*)(&spawnColumn));
      newStackSpawn = newStackPtr;
      *newStackPtr = spawnRow;
      newStackSpawn[1] = spawnColumn;
      *(_WORD *)(uintptr_t)(2 * spawnColumn + TILE_ROW_STRIDE * spawnRow + gameData + TILE_MAP_OFFSET) = *(_WORD *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1]));
    }
    tileOccupantValue = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    *(_WORD *)(uintptr_t)(TILE_INDEX(*buildingPtr, buildingPtr[1])) = savedBuildingIndex + TILE_OCCUPANT_BUILDING_INDEX_BASE;
    buildingPtrTile = buildingPtr;
    *(_WORD *)(uintptr_t)(TILE_ROW_STRIDE * (*buildingPtr + 1) + gameData + 2 * buildingPtr[1] + TILE_MAP_OFFSET) = tileOccupantValue;
    *(_WORD *)(uintptr_t)(200 * (*buildingPtrTile + 1) + gameData + 2 * buildingPtr[1] + 556376) = tileOccupantValue;
    buildingPtrFlags = buildingPtr;
    *(_WORD *)(uintptr_t)(200 * *buildingPtr + gameData + 2 * buildingPtr[1] + 556376) = tileOccupantValue;
    Render_LoadResourceSprite_v2();
    if ( (buildingPtrFlags[435] & 7) != 0 && !transferGoldFlag )
      UnitStack_SetPlagueFlag((int)(intptr_t)newStackPtr);
    Rules_LinkArmyFact(newStackPtr, (int)(intptr_t)newStackPtr, v33, a5, (char)(intptr_t)buildingPtrFlags, (DWORD)(intptr_t)savedregs);
    if ( !*(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)newStackForFact + 4) + PLAYER_CONTROLLER_MODE_TABLE_OFFSET) )
      Rules_LogBuildingTransferFact(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*newStackForFact, newStackPtr[1])), savedBuildingIndex, savedTargetStack);
    return 1;
  }
  return result;
}
// 41F1E0: variable 'v6' is possibly undefined
// 41F3C8: variable 'v10' is possibly undefined
// 41F6FE: variable 'v33' is possibly undefined
// 41F705: variable 'v34' is possibly undefined
// 41F77D: variable 'v12' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041F810) --------------------------------------------------------
int  Building_CalcGarrisonAverageHealthPercent(int buildingPtr)
{
  int slotsEnd; // ebx
  int damageSum; // edx
  int slotDamage; // ecx

  slotsEnd = buildingPtr + 7;
  damageSum = 0;
  do
  {
    slotDamage = *(unsigned __int8 *)(uintptr_t)(buildingPtr + 422);
    ++buildingPtr;
    damageSum += slotDamage;
  }
  while ( buildingPtr != slotsEnd );
  return 100 - damageSum / 7;
}

int  UI_DrawUnitStatsValues(int a1)
{
  return Building_CalcGarrisonAverageHealthPercent(a1);
}

//----- (0041F850) --------------------------------------------------------
BOOL  Building_CanStartUpgrade(unsigned __int8 *buildingPtr)
{
  return buildingPtr[421] < 2u && buildingPtr[421] < (buildingPtr[444] & 7) - 1 && !buildingPtr[429];
}

//----- (0041F890) --------------------------------------------------------
BOOL  Building_TryStartUpgrade(unsigned __int8 *buildingPtr)
{
  BOOL result; // eax
  int buildingRecord; // edx

  result = Building_CanStartUpgrade(buildingPtr);
  if ( result )
  {
    if ( (unsigned int)(unsigned __int8)g_BuildingUpgradeCostByLevel[4 * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 421)] <= *(_DWORD *)(uintptr_t)(buildingRecord + 438) )
    {
      *(_BYTE *)(uintptr_t)(buildingRecord + 429) = g_BuildingUpgradeDurationByLevel[4 * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 421)];
      result = 1;
      *(_DWORD *)(uintptr_t)(buildingRecord + 438) -= (unsigned __int8)g_BuildingUpgradeCostByLevel[4 * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 421)];
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 41F8A0: variable 'v2' is possibly undefined

//----- (0041F900) --------------------------------------------------------
_DWORD * Unit_CaptureBuilding(int capturingStackIndex, DWORD buildingIndex, int a3, signed int j, double a5)
{
  DWORD buildingByteOffset; // ebx
  int buildingPtr; // ecx
  DWORD buildingBase; // eax
  unsigned __int8 buildingTechLevel; // bl
  unsigned __int8 playerTechLevel; // bh
  char preservedNonTechBits; // dh
  int v13; // edx
  int turnCounter; // ebx
  int ownerPlayerDataOffset; // eax
  DWORD buildingRecordPtr; // ecx
  DWORD personageSlotPtr; // ebx
  int i; // edi
  int personageType; // edx
  int v20 CLASH95_UNUSED; // ecx
  int k; // edi
  int garrisonSlotIndex; // edx
  int v23 CLASH95_UNUSED; // ecx
  DWORD buildingRecordOffset; // ebx
  DWORD buildingRecordOffset2; // ecx
  int m; // edi
  int savedBuildingOffset; // [esp+4h] [ebp-24h]

  buildingByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
  v13 = buildingByteOffset;
  Debug_Log(a3, -45 * buildingIndex, buildingIndex, (int)(intptr_t)aUnit_capturebu);
  buildingPtr = buildingByteOffset + gameData + BUILDING_TABLE_OFFSET;
  if ( *(_WORD *)(uintptr_t)(buildingByteOffset + gameData + BUILDING_CONSTRUCTION_TURNS_REMAINING_TABLE_OFFSET) )
    return Building_Destroy(buildingByteOffset + gameData + BUILDING_TABLE_OFFSET, buildingByteOffset, buildingIndex, a5);
  *(_BYTE *)(uintptr_t)(buildingByteOffset + gameData + BUILDING_OWNER_PLAYER_INDEX_TABLE_OFFSET) = *(_BYTE *)(uintptr_t)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + UNIT_STACK_OWNER_PLAYER_INDEX_TABLE_OFFSET);
  buildingBase = buildingByteOffset + gameData;
  buildingTechLevel = *(_BYTE *)(uintptr_t)(buildingByteOffset + gameData + BUILDING_TECH_LEVEL_BITS_TABLE_OFFSET) & 7;
  playerTechLevel = *(_BYTE *)(uintptr_t)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(UNIT_STACK_STRIDE * capturingStackIndex + gameData + UNIT_STACK_OWNER_PLAYER_INDEX_TABLE_OFFSET) + gameData + PLAYER_TECH_LEVEL_TABLE_OFFSET);
  if ( buildingTechLevel < playerTechLevel )
  {
    preservedNonTechBits = *(_BYTE *)(uintptr_t)(buildingBase + 510118) & 0xF8;
    *(_BYTE *)(uintptr_t)(buildingBase + 510118) = preservedNonTechBits;
    *(_BYTE *)(uintptr_t)(buildingBase + 510118) = playerTechLevel & 7 | preservedNonTechBits;
  }
  Rules_SyncCastleFactOwner(UNIT_RECORD(buildingIndex), buildingPtr, a5);
  savedBuildingOffset = v13;
  turnCounter = *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET);
  Rules_LogBuildingCapturedFact(*(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * capturingStackIndex + UNIT_STACK_OWNER_PLAYER_INDEX_TABLE_OFFSET), buildingIndex, turnCounter);
  ownerPlayerDataOffset = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(savedBuildingOffset + gameData + BUILDING_OWNER_PLAYER_INDEX_TABLE_OFFSET) + gameData;
  if ( buildingIndex == *(_DWORD *)(uintptr_t)(ownerPlayerDataOffset + 140067) )
    *(_DWORD *)(uintptr_t)(ownerPlayerDataOffset + 140067) = -1;
  Building_UnitGetInto(capturingStackIndex, buildingIndex, turnCounter, buildingIndex, a5);
  buildingRecordPtr = buildingPtr;
  personageSlotPtr = buildingRecordPtr;
  for ( i = 0; i < 3; ++i )
  {
    personageType = *(char *)(uintptr_t)(personageSlotPtr + 445);
    if ( personageType != -1 && *(_BYTE *)(uintptr_t)(personageSlotPtr + 446) == *(_BYTE *)(uintptr_t)(buildingRecordPtr + 2) )
    {
      Building_CreateSpecialPersonageGarrisonUnit(buildingRecordPtr, (unit_type)(unsigned int)(personageType), buildingRecordPtr, (char)i, a5);
      Prisoner_Kill(buildingRecordPtr, (char)i, buildingIndex);
    }
    personageSlotPtr += 6;
  }
  for ( k = 0; k < 12; ++k )
  {
    Building_ClearGarrisonTrainingTimer(buildingRecordPtr, k);
    garrisonSlotIndex = k;
    Building_ClearGarrisonRepairTimer(buildingRecordPtr, garrisonSlotIndex);
  }
  buildingRecordOffset = BUILDING_RECORD_SIZE * buildingIndex;
  buildingRecordOffset2 = BUILDING_RECORD_SIZE * buildingIndex;
  for ( m = *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * buildingIndex + BUILDING_TABLE_OFFSET); m <= *(unsigned __int8 *)(uintptr_t)(buildingRecordOffset + gameData + BUILDING_TABLE_OFFSET) + 1; ++m )
  {
    for ( j = *(unsigned __int8 *)(uintptr_t)(buildingRecordOffset + gameData + BUILDING_TILE_COLUMN_TABLE_OFFSET); j <= *(unsigned __int8 *)(uintptr_t)(buildingRecordOffset2 + gameData + BUILDING_TILE_COLUMN_TABLE_OFFSET) + 1; ++j )
      MiniMap_DrawTileCell((void *)(uintptr_t)m, j);
  }
  return (_DWORD *)(uintptr_t)MiniMap_RedrawTileRect(m, j, j + 1, m + 1);
}
// 41FA10: variable 'v13' is possibly undefined
// 41FA69: variable 'v16' is possibly undefined
// 41FA8F: variable 'v20' is possibly undefined
// 41FAAE: variable 'v23' is possibly undefined
// 41FAEF: variable 'v25' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041FB50) --------------------------------------------------------
_DWORD * Building_Destroy(int a1, char a2, DWORD a3, double a4)
{
  int buildingPtr; // ecx
  int scanIndex; // eax
  int recordPtr; // ebx
  int recordOffset; // edx
  int writeIndex; // edx
  int writeIndex2; // eax
  int occupiedSlots[11]; // [esp+0h] [ebp-48h] BYREF
  int slotIndex; // [esp+2Ch] [ebp-1Ch]
  int outCount; // [esp+30h] [ebp-18h]

  Debug_Log(a1, a2, a3, (int)(intptr_t)aBuilding_destr);
  if ( *(__int16 *)(uintptr_t)(buildingPtr + 18) != -1 )
  {
    slotIndex = 0;
    outCount = 0;
    while ( slotIndex < BUILDING_GARRISON_SLOT_COUNT && outCount < 10 )
    {
      if ( *(__int16 *)(uintptr_t)(buildingPtr + UNIT_SLOT_RECORD_BYTES * slotIndex + 18) != -1 )
      {
        writeIndex = outCount++;
        occupiedSlots[writeIndex] = slotIndex;
      }
      ++slotIndex;
    }
    if ( outCount < 10 )
      occupiedSlots[outCount] = -1;
    Building_UnitsLeave((unsigned __int8 *)(uintptr_t)buildingPtr, occupiedSlots, a4);
    if ( slotIndex < BUILDING_GARRISON_SLOT_COUNT && *(__int16 *)(uintptr_t)(buildingPtr + UNIT_SLOT_RECORD_BYTES * slotIndex + 18) != -1 )
    {
      outCount = 0;
      while ( slotIndex < BUILDING_GARRISON_SLOT_COUNT )
      {
        if ( *(__int16 *)(uintptr_t)(buildingPtr + UNIT_SLOT_RECORD_BYTES * slotIndex + 18) != -1 )
        {
          writeIndex2 = outCount++;
          occupiedSlots[writeIndex2] = slotIndex;
        }
        ++slotIndex;
      }
      occupiedSlots[outCount] = -1;
      Building_UnitsLeave((unsigned __int8 *)(uintptr_t)buildingPtr, occupiedSlots, a4);
    }
  }
  *(_WORD *)(uintptr_t)(buildingPtr + 16) = -1;
  scanIndex = 0;
LABEL_3:
  recordPtr = UNIT_RECORD(scanIndex);
  if ( (unsigned int)*(char *)(uintptr_t)(recordPtr + 4) >= 4
    || *(__int16 *)(uintptr_t)(recordPtr + 16) == -1
    || (recordOffset = gameData + BUILDING_RECORD_SIZE * scanIndex, !*(_BYTE *)(uintptr_t)(recordOffset + 509678))
    || *(_BYTE *)(uintptr_t)(recordOffset + 509676) != *(_BYTE *)(uintptr_t)(buildingPtr + 2) )
  {
    while ( ++scanIndex < 100 )
    {
      if ( scanIndex >= 0 )
        goto LABEL_3;
    }
  }
  if ( scanIndex == 100 )
    *(_BYTE *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2) + 141443) = -1;
  return Rules_RetractCastleFact((unsigned __int8 *)(uintptr_t)buildingPtr, a4);
}
// 41FCFF: conditional instruction was optimized away because eax.4<64u
// 41FB97: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 41FB65: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0041FD10) --------------------------------------------------------
int  Building_CalcRemainingConstructionTurns(int buildingPtr)
{
  int buildingBase; // esi
  int slotsEnd; // ebx
  int progressPerTurn; // ecx

  buildingBase = buildingPtr;
  if ( !*(_WORD *)(uintptr_t)(buildingPtr + 16) )
    return 0;
  slotsEnd = buildingPtr + BUILDING_GARRISON_SLOTS_BYTES;
  progressPerTurn = 0;
  do
  {
    if ( *(_WORD *)(uintptr_t)(buildingPtr + 18) == UNIT_TYPE_BUILDER )
      progressPerTurn += (unsigned __int8)g_BuilderConstructionProgressPerTurn;
    buildingPtr += UNIT_SLOT_RECORD_BYTES;
  }
  while ( buildingPtr != slotsEnd );
  if ( progressPerTurn )
    return *(__int16 *)(uintptr_t)(buildingBase + 16) / progressPerTurn + 1;
  else
    return 50;
}
// 512B58: using guessed type char g_BuilderConstructionProgressPerTurn;

//----- (0041FD70) --------------------------------------------------------
signed int  Building_FindRandomOwnedCompletedCastle(int ownerPlayer, int a2)
{
  int matchCount; // ecx
  int buildingIndex; // eax
  int buildingByteOffset; // ebx
  int recordBase; // edx
  char matchList[113]; // [esp+1h] [ebp-79h]
  int v10 CLASH95_UNUSED; // [esp+72h] [ebp-8h]

  v10 = a2;
  matchCount = 0;
  buildingIndex = 0;
  buildingByteOffset = 0;
  do
  {
    recordBase = buildingByteOffset + gameData;
    if ( *(unsigned __int8 *)(uintptr_t)(buildingByteOffset + gameData + BUILDING_OWNER_PLAYER_INDEX_TABLE_OFFSET) == ownerPlayer && *(_BYTE *)(uintptr_t)(recordBase + 509678) == 2 && !*(_WORD *)(uintptr_t)(recordBase + 509690) )
      matchList[++matchCount] = buildingIndex;
    ++buildingIndex;
    buildingByteOffset += BUILDING_RECORD_SIZE;
  }
  while ( buildingIndex < 100 );
  if ( matchCount )
    return (unsigned __int8)matchList[Rng_RandRange(0, matchCount - 1) + 1];
  else
    return -1;
}

signed int  Unit_FindById(int a1)
{
  return Building_FindRandomOwnedCompletedCastle(a1, 0);
}
// 5202E4: using guessed type int gameData;

//----- (0041FDF0) --------------------------------------------------------
void * Building_ShowHoverInfoPopup(unsigned __int8 *buildingPtr, char spriteSetId, int a3)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9; // ecx
  __int16 popupSpriteHeight; // ax
  int SpriteForChar; // eax
  int languageIndex; // ecx
  int addonSpriteId; // eax
  int textBaseY; // esi
  int v15; // ecx
  int v16; // ecx
  int prisonerRowY; // edi
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx
  int spriteCharIndex; // edx
  int spriteRenderer; // edi
  __int16 fillHeight; // ax
  _DWORD *surfacePtr; // edi
  void *result; // eax
  int spriteId; // eax
  int localizedName; // edi
  int v29; // edx
  unsigned __int16 popupRight; // [esp+3Ch] [ebp-48h]
  unsigned __int16 fillRight; // [esp+3Ch] [ebp-48h]
  unsigned __int16 fillTop; // [esp+40h] [ebp-44h]
  unsigned __int16 fillLeft; // [esp+44h] [ebp-40h]
  int buildingNamesByLang[3]; // [esp+48h] [ebp-3Ch]
  _DWORD *spriteSet; // [esp+54h] [ebp-30h] BYREF
  int panelY; // [esp+58h] [ebp-2Ch]
  int v37 CLASH95_UNUSED; // [esp+5Ch] [ebp-28h]
  _DWORD *surface; // [esp+60h] [ebp-24h]
  void *savedRenderDevice; // [esp+64h] [ebp-20h]
  int panelX; // [esp+68h] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_Pump();
  loadedSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, spriteSetId, (DWORD)(intptr_t)buildingPtr);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, (const void*)(intptr_t)(spriteSetId));
  spriteSet = loadedSpriteSet;
  panelY = 100;
  panelX = 100;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 100, spriteSetId, (DWORD)(intptr_t)buildingPtr);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
    Surface = Render_CreateSurface(v9, SpriteHeight, SpriteWidth);
  }
  surface = Surface;
  popupRight = panelX + DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0) - 1;
  popupSpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
  Render_FillRect(0, surface, (unsigned __int16)panelX, (unsigned __int16)panelY, panelY + popupSpriteHeight - 1, popupRight, 0, 0);
  Render_ReleaseSurface(7, (DWORD)(intptr_t)buildingPtr);
  if ( buildingPtr[4] )
  {
    SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, buildingPtr[2] != g_CurrentPlayerIndex);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      panelX,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  else
  {
    spriteId = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 6);
    a3 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(a3 + 52))(
      panelX,
      spriteId,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  languageIndex = (char)buildingPtr[4];
  if ( buildingPtr[4] )
  {
    UI_DrawTextFmt(a3, panelY + 10, panelY + 235, panelX + 5, 3, (const char*)(intptr_t)((int)(intptr_t)(buildingPtr + 5)));
    if ( buildingPtr[2] == g_CurrentPlayerIndex )
    {
      if ( (buildingPtr[435] & 7) != 0 )
      {
        addonSpriteId = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 2);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
          panelX + 37,
          addonSpriteId,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      textBaseY = panelY;
      UI_DrawTextFmt(a3, panelY, panelY + 89, panelX + 25, 2, (const char*)(intptr_t)((int)(intptr_t)aD_21));
      UI_DrawTextFmt(a3, textBaseY, textBaseY + 150, v15, 2, (const char*)(intptr_t)((int)(intptr_t)aD_22));
      UI_DrawTextFmt(a3, textBaseY, textBaseY + 210, v16, 2, (const char*)(intptr_t)((int)(intptr_t)aD_23));
    }
    Building_DrawGarrisonRow((int)(intptr_t)buildingPtr);
    UI_DrawTextFmt(a3, panelY, panelY + 89, panelX + 62, 2, (const char*)(intptr_t)((int)(intptr_t)aD_24));
    Building_CountGarrison((int)(intptr_t)buildingPtr);
    Building_DrawGarrisonRow((int)(intptr_t)buildingPtr);
    prisonerRowY = panelY;
    v37 = panelY + 150;
    UI_DrawTextFmt(panelY, panelY, panelY + 150, v18, 2, (const char*)(intptr_t)((int)(intptr_t)aD_25));
    Building_CountPrisoners((int)(intptr_t)buildingPtr);
    UI_DrawTextFmt(prisonerRowY, prisonerRowY, prisonerRowY + 208, v19, 2, (const char*)(intptr_t)((int)(intptr_t)aD_26));
    UI_DrawTextFmt(prisonerRowY, prisonerRowY, v20, panelX + 99, 2, (const char*)(intptr_t)((int)(intptr_t)aD_27));
    spriteCharIndex = panelY ^ v21;
    LOBYTE(spriteCharIndex) = buildingPtr[421];
    DLX_GetSpriteForChar((int)(intptr_t)spriteSet, spriteCharIndex + 3);
    spriteRenderer = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(spriteRenderer + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(spriteRenderer, panelY, panelY + 150, panelX + 99, 2, (const char*)(intptr_t)((int)(intptr_t)aD_28));
    UI_DrawUnitStatsValues((int)(intptr_t)buildingPtr);
    UI_DrawTextFmt(spriteRenderer, panelY, panelY + 205, panelX + 99, 2, (const char*)(intptr_t)((int)(intptr_t)aD_29));
  }
  else
  {
    buildingNamesByLang[0] = (int)(intptr_t)UI_Locale_BuildingNames_A[0];
    buildingNamesByLang[1] = (int)(intptr_t)UI_Locale_BuildingNames_A[1];
    buildingNamesByLang[2] = (int)(intptr_t)UI_Locale_BuildingNames_A[2];
    LOBYTE(languageIndex) = g_LanguageIndex;
    localizedName = buildingNamesByLang[languageIndex];
    UI_DrawTextFmt(localizedName, panelY + 10, panelY + 175, panelX + 5, 3, (const char*)(intptr_t)(localizedName));
    Building_DrawGarrisonRow((int)(intptr_t)buildingPtr);
    UI_DrawTextFmt(localizedName, panelY, panelY + 87, panelX + 25, 2, (const char*)(intptr_t)((int)(intptr_t)aD_30));
    Building_CountGarrison((int)(intptr_t)buildingPtr);
    Building_DrawGarrisonRow((int)(intptr_t)buildingPtr);
    UI_DrawTextFmt(localizedName, panelY, panelY + 150, v29, 2, (const char*)(intptr_t)((int)(intptr_t)aD_31));
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  fillLeft = panelX;
  fillTop = panelY;
  fillRight = DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0) - 1;
  fillHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
  surfacePtr = surface;
  Render_FillRect(surface, 0, 0, 0, fillHeight - 1, fillRight, fillTop, fillLeft);
  if ( surfacePtr )
    RenderSurface_InvokeSlot0(surfacePtr, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  Render_Present((int)(intptr_t)g_RenderState);
  result = savedRenderDevice;
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return result;
}
// 41FE1E: variable 'v4' is possibly undefined
// 41FE6E: variable 'v9' is possibly undefined
// 41FFF0: variable 'v15' is possibly undefined
// 420012: variable 'v16' is possibly undefined
// 420074: variable 'v18' is possibly undefined
// 420094: variable 'v19' is possibly undefined
// 4200BD: variable 'v20' is possibly undefined
// 4200C5: variable 'v21' is possibly undefined
// 42029B: variable 'v29' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513B44: using guessed type char *off_513B44[2];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004202C0) --------------------------------------------------------
int  Building_ShowConstructionProgressDialog(DWORD buildingRecord, char spriteSetId, DWORD a3, double a4)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 fillSpriteHeight; // ax
  int SpriteForChar; // eax
  int textY; // ebx
  int v14; // edx
  int buildingNameStr; // edi
  int v16; // edx
  int v17; // edx
  int remainingTurns; // eax
  int v19; // ecx
  int turnsTextX; // ecx
  int stopBtnXMin; // edi
  int okBtnYMin; // ebx
  signed int okBtnXMax; // ebp
  int okBtnYMax; // esi
  int cursorCoordShift; // ecx
  __int16 teardownSpriteHeight; // ax
  unsigned __int16 spriteRightX; // [esp+10h] [ebp-C4h]
  unsigned __int16 spriteWidthMinus1; // [esp+10h] [ebp-C4h]
  unsigned __int16 spriteTopY; // [esp+14h] [ebp-C0h]
  unsigned __int16 spriteLeftX; // [esp+18h] [ebp-BCh]
  int namesTableE[12]; // [esp+1Ch] [ebp-B8h] BYREF
  int namesTableG[3]; // [esp+4Ch] [ebp-88h]
  int namesTableH[3]; // [esp+58h] [ebp-7Ch]
  int namesTableB[3]; // [esp+64h] [ebp-70h] BYREF
  int namesTableC[3]; // [esp+70h] [ebp-64h]
  int namesTableD[3]; // [esp+7Ch] [ebp-58h]
  int namesTableF[3]; // [esp+88h] [ebp-4Ch]
  _DWORD *spriteSet; // [esp+94h] [ebp-40h] BYREF
  _DWORD *surface; // [esp+98h] [ebp-3Ch]
  int centeredY; // [esp+9Ch] [ebp-38h]
  int stopBtnYMin; // [esp+A0h] [ebp-34h]
  int stopBtnXMax; // [esp+A4h] [ebp-30h]
  int okBtnXMin; // [esp+A8h] [ebp-2Ch]
  int stopBtnYMax; // [esp+ACh] [ebp-28h]
  void *savedRenderDevice; // [esp+B0h] [ebp-24h]
  DWORD buildingPtr; // [esp+B4h] [ebp-20h]
  int centeredX; // [esp+B8h] [ebp-1Ch]

  buildingPtr = buildingRecord;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_Pump();
  loadedSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, spriteSetId, a3);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, (const void*)(intptr_t)(spriteSetId));
  spriteSet = loadedSpriteSet;
  centeredY = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)loadedSpriteSet, 0)) / 2;
  centeredX = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0)) / 2;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v6, spriteSetId, a3);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  surface = Surface;
  spriteRightX = centeredX + DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0) - 1;
  fillSpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
  Render_FillRect(0, surface, (unsigned __int16)centeredX, (unsigned __int16)centeredY, centeredY + fillSpriteHeight - 1, spriteRightX, 0, 0);
  Render_ReleaseSurface(17, a3);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    centeredX,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  namesTableB[0] = (int)(intptr_t)UI_Locale_BuildingNames_B[0];
  namesTableB[1] = (int)(intptr_t)UI_Locale_BuildingNames_B[1];
  namesTableB[2] = (int)(intptr_t)UI_Locale_BuildingNames_B[2];
  namesTableC[0] = (int)(intptr_t)UI_Locale_BuildingNames_C[0];
  namesTableC[1] = (int)(intptr_t)UI_Locale_BuildingNames_C[1];
  namesTableC[2] = (int)(intptr_t)UI_Locale_BuildingNames_C[2];
  namesTableD[0] = (int)(intptr_t)UI_Locale_BuildingNames_D[0];
  namesTableD[1] = (int)(intptr_t)UI_Locale_BuildingNames_D[1];
  namesTableD[2] = (int)(intptr_t)UI_Locale_BuildingNames_D[2];
  qmemcpy(namesTableE, UI_Locale_BuildingNames_E, sizeof(namesTableE));
  namesTableF[0] = (int)(intptr_t)UI_Locale_BuildingNames_F[0];
  namesTableF[1] = (int)(intptr_t)UI_Locale_BuildingNames_F[1];
  namesTableF[2] = (int)(intptr_t)UI_Locale_BuildingNames_F[2];
  namesTableG[0] = (int)(intptr_t)UI_Locale_BuildingNames_G[0];
  namesTableG[1] = (int)(intptr_t)UI_Locale_BuildingNames_G[1];
  namesTableG[2] = (int)(intptr_t)UI_Locale_BuildingNames_G[2];
  namesTableH[0] = (int)(intptr_t)UI_Locale_BuildingNames_H[0];
  namesTableH[1] = (int)(intptr_t)UI_Locale_BuildingNames_H[1];
  namesTableH[2] = (int)(intptr_t)UI_Locale_BuildingNames_H[2];
  textY = centeredY + 30;
  UI_DrawTextFmt((int)(intptr_t)namesTableB, centeredY + 30, centeredY + 250, centeredX + 12, 3, (const char*)(intptr_t)(namesTableB[(unsigned __int8)g_LanguageIndex]));
  UI_DrawTextFmt((int)(intptr_t)namesTableB, textY, v14, centeredX + 32, 3, (const char*)(intptr_t)(namesTableC[(unsigned __int8)g_LanguageIndex]));
  buildingNameStr = namesTableE[4 * *(char *)(uintptr_t)(buildingPtr + 4) + (unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(buildingNameStr, textY, v16, centeredX + 52, 3, (const char*)(intptr_t)(namesTableD[(unsigned __int8)g_LanguageIndex]));
  remainingTurns = Building_CalcRemainingConstructionTurns(buildingPtr);
  turnsTextX = v19 + 77;
  if ( remainingTurns == 1 )
  {
    UI_DrawTextFmt(buildingNameStr, textY, v17, turnsTextX, 3, (const char*)(intptr_t)(namesTableF[(unsigned __int8)g_LanguageIndex]));
  }
  else if ( remainingTurns > 4 )
  {
    UI_DrawTextFmt(buildingNameStr, textY, v17, turnsTextX, 3, (const char*)(intptr_t)(namesTableH[(unsigned __int8)g_LanguageIndex]));
  }
  else
  {
    UI_DrawTextFmt(namesTableG[(unsigned __int8)g_LanguageIndex], textY, v17, turnsTextX, 3, (const char*)(intptr_t)(namesTableG[(unsigned __int8)g_LanguageIndex]));
  }
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)(intptr_t)g_RenderState);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  stopBtnYMin = centeredX + 103;
  stopBtnXMax = centeredY + 220;
  stopBtnXMin = centeredY + 175;
  okBtnYMin = centeredX + 100;
  stopBtnYMax = centeredX + 117;
  okBtnXMax = centeredY + 92;
  okBtnYMax = centeredX + 113;
  okBtnXMin = centeredY + 60;
  while ( 1 )
  {
    do
      DD_Pump((int)(intptr_t)g_RenderState, okBtnYMin);
    while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= okBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= okBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= okBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= okBtnYMax )
    {
      break;
    }
    LOBYTE(cursorCoordShift) = g_CursorCoordShift;
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= stopBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= stopBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= stopBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= stopBtnYMax )
    {
      Building_Stop(buildingPtr, cursorCoordShift, okBtnYMin, okBtnXMax, a4);
      break;
    }
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Render_Pump();
  spriteLeftX = centeredX;
  spriteTopY = centeredY;
  spriteWidthMinus1 = DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0) - 1;
  teardownSpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0);
  Render_FillRect(surface, 0, 0, 0, teardownSpriteHeight - 1, spriteWidthMinus1, spriteTopY, spriteLeftX);
  if ( surface )
    RenderSurface_InvokeSlot0(surface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return WorldMap_RedrawViewport(1);
}
// 4202F9: variable 'v4' is possibly undefined
// 420359: variable 'v6' is possibly undefined
// 420386: variable 'v10' is possibly undefined
// 4204DE: variable 'v14' is possibly undefined
// 42051C: variable 'v16' is possibly undefined
// 420537: variable 'v19' is possibly undefined
// 420555: variable 'v17' is possibly undefined
// 420675: variable 'v25' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513B50: using guessed type char *off_513B50[12];
// 513B5C: using guessed type char *off_513B5C[9];
// 513B68: using guessed type char *off_513B68[6];
// 513B74: using guessed type char *off_513B74[3];
// 513BA4: using guessed type char *off_513BA4[9];
// 513BB0: using guessed type char *off_513BB0[6];
// 513BBC: using guessed type char *off_513BBC[3];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00420770) --------------------------------------------------------
DWORD Timer_InitPerfCounterFrequency(void)
{
  QueryPerformanceFrequency(&Frequency);
  Frequency.QuadPart /= 100;
  return Frequency.LowPart;
}

//----- (004207B0) --------------------------------------------------------
int __fastcall Time_Now(int a1, int a2)
{
  LARGE_INTEGER v3; // [esp+0h] [ebp-18h] BYREF
  (void)a1;
  (void)a2;
  QueryPerformanceCounter(&v3);
  if ( !Frequency.QuadPart )
    return v3.LowPart;
  return (int)(v3.QuadPart / Frequency.QuadPart);
}

//----- (00420800) --------------------------------------------------------
unsigned int  Timer_BusyWaitWithCallback(int durationTicks, int callbackAddr, int a3)
{
  void (__cdecl *callback)(void);
  unsigned int deadline;
  unsigned int result; // eax

  (void)a3;
  callback = (void (__cdecl *)(void))(uintptr_t)callbackAddr;
  deadline = Time_Now(0, 0) + (unsigned int)durationTicks;
  while ( 1 )
  {
    result = Time_Now(0, 0);
    if ( result >= deadline )
      break;
    if ( callback )
      callback();
  }
  return result;
}

//----- (00420820) --------------------------------------------------------
int __thiscall Mem_ConstructObjectArray256(void *this_)
{
  return _wcpp_4_ctor_array__((_DWORD)(uintptr_t)(this_), 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00420840) --------------------------------------------------------
int  Castle_RequestManagementScreenExit(uintptr_t widgetRecord, int animationDelay)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widgetRecord, animationDelay);
  g_CastleScreenExitRequested = 1;
  return result;
}
// 526E80: using guessed type int g_CastleScreenExitRequested;

//----- (00420870) --------------------------------------------------------
int Castle_RebuildMissingAddonFlags(void)
{
  int anyAddonMissing; // edx
  int result; // eax

  g_CastleAddonSchoolMissingFlags[0] = (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) == 0;
  g_CastleAddonHospitalMissingFlag = (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) == 0;
  g_CastleAddonBarracksMissingFlag = (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) == 0;
  g_CastleAddonWorkshopMissingFlag = (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) == 0;
  anyAddonMissing = 0;
  g_CastleAddonSmithsMissingFlag = (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) == 0;
  for ( result = 0; result != 50; result += 10 )
  {
    if ( g_CastleAddonSchoolMissingFlags[result] )
      anyAddonMissing = 1;
  }
  if ( !anyAddonMissing )
    g_CastleAnyAddonMissingFlag = 0;
  return result * 4;
}
// 513E22: using guessed type int dword_513E22;
// 513FC2: using guessed type int dword_513FC2[];
// 513FEA: using guessed type int dword_513FEA;
// 514012: using guessed type int dword_514012;
// 51403A: using guessed type int dword_51403A;
// 514062: using guessed type int dword_514062;
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420910) --------------------------------------------------------
void *Castle_ShowNewBuildingMenu(void)
{
  void *result; // eax
  int v1; // ecx
  void *v2; // edx
  int frameOffset; // esi
  int delayAccum; // edi
  int nowTicks; // eax
  int v6; // ecx
  unsigned int deadline; // edx
  unsigned int now; // eax
  int absFrame; // eax
  int SpriteForChar; // eax
  DWORD renderContext; // ebp
  void (*menuAction)(void); // eax
  void *savedRenderDevice; // [esp+1Ch] [ebp-1Ch]

  savedRenderDevice = g_RenderDevice;
  if ( !DD_IsFlipping((int)(intptr_t)g_RenderState) || g_MouseCursorRawX >> g_CursorCoordShift <= 509 || g_MouseCursorRawY >> g_CursorCoordShift >= 66 )
    goto LABEL_4;
  Castle_RebuildMissingAddonFlags();
  v2 = &g_MainRenderDevice;
  frameOffset = -5;
  delayAccum = 0;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  do
  {
    nowTicks = Time_Now(v1, (int)(intptr_t)v2);
    v6 = 3;
    deadline = delayAccum / 3 + nowTicks;
    do
      now = Time_Now(v6, deadline);
    while ( now < deadline );
    Render_Pump();
    if ( frameOffset <= 0 )
      absFrame = -frameOffset;
    else
      absFrame = frameOffset;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 5 - absFrame);
    renderContext = *((_DWORD *)g_RenderDevice + 46);
    delayAccum += 2;
    (*(void (__fastcall **)(_DWORD, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(uintptr_t)(renderContext + 52))(
      0,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      0,
      0,
      0);
    ++frameOffset;
    Render_Present((int)(intptr_t)g_RenderState);
  }
  while ( frameOffset <= 5 );
  Render_Pump();
  Render_FillRect(0, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 300, SCREEN_MAX_X, 0x12Cu, 0x12Cu, 0);
  Render_Present((int)(intptr_t)g_RenderState);
  g_WorldMapTargetSurface = g_PrimaryRenderSurface;
  menuAction = (void (*)(void))(uintptr_t)UI_RunMenu(g_CastleNewBuildingMenu, renderContext);
  if ( menuAction )
  {
    menuAction();
    result = savedRenderDevice;
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  }
  else
  {
LABEL_4:
    result = savedRenderDevice;
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  }
  return result;
}
// 420980: variable 'v1' is possibly undefined
// 420980: variable 'v2' is possibly undefined
// 420998: variable 'v6' is possibly undefined
// 420998: variable 'v7' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513E08: using guessed type _WORD word_513E08[5];
// 5202E0: using guessed type int dword_5202E0;
// 523F60: using guessed type int dword_523F60;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00420A90) --------------------------------------------------------
int  Castle_PlayAddonConstructionReveal(int addonTileMarker, int buildingRecord)
{
  int minX; // edi
  int scanY; // esi
  int rowCursor; // ecx
  int i; // ebx
  int pixelCursor; // ecx
  int revealLeftX; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // edx
  int currentTime; // eax
  int v15; // ecx
  int savedBuildingRecord; // [esp+4h] [ebp-30h]
  int startTime; // [esp+Ch] [ebp-28h]
  int maxX; // [esp+14h] [ebp-20h]
  int minY; // [esp+18h] [ebp-1Ch]
  int maxY; // [esp+1Ch] [ebp-18h]

  minX = 639;
  Render_Pump();
  scanY = 0;
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_CastleScreenSurface;
  minY = 479;
  maxX = 0;
  maxY = 0;
  do
  {
    rowCursor = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(g_CastleScreenSurface + 184) + 4))();
    for ( i = 0; i < 640; ++i )
    {
      if ( *(unsigned __int8 *)(uintptr_t)(*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)rowCursor + 16))() == addonTileMarker )
      {
        if ( i < minX )
          minX = i;
        if ( i > maxX )
          maxX = i;
        if ( scanY < minY )
          minY = scanY;
        if ( scanY > maxY )
          maxY = scanY;
      }
      (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)pixelCursor + 12))(pixelCursor, 1);
    }
    ++scanY;
    (**(void (__fastcall ***)(int, int))(uintptr_t)rowCursor)(rowCursor, 2);
  }
  while ( scanY < 480 );
  revealLeftX = minX - 50;
  if ( revealLeftX < 0 )
    LOWORD(revealLeftX) = 0;
  if ( addonTileMarker == 254 || addonTileMarker == 250 )
    LOWORD(revealLeftX) = 0;
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 0, buildingRecord, 0);
  startTime = Time_Now(v9, v8);
  savedBuildingRecord = g_SelectedBuildingRecord;
  v11 = buildingRecord;
  g_SelectedBuildingRecord = buildingRecord;
  while ( Time_Now(v10, v11) < (unsigned int)(startTime + 200) )
  {
    currentTime = Time_Now(startTime, v12);
    Render_BlendSurfaceRect(
      0,
      g_PrimaryRenderSurface,
      (unsigned __int16)revealLeftX,
      g_CastleScreenSurface,
      minY,
      maxX,
      maxY,
      revealLeftX,
      minY,
      255 * (currentTime - v15) / 0xC8u);
    Castle_UpdateAmbientAnimationLayers();
  }
  g_SelectedBuildingRecord = savedBuildingRecord;
  Render_FillRect(
    (_DWORD *)(uintptr_t)g_CastleScreenSurface,
    (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
    (unsigned __int16)minY,
    (unsigned __int16)revealLeftX,
    maxX,
    maxY,
    revealLeftX,
    minY);
  Render_FillRect((_DWORD *)(uintptr_t)g_CastleScreenSurface, 0, (unsigned __int16)minY, (unsigned __int16)revealLeftX, maxX, maxY, revealLeftX, minY);
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Castle_DrawStatusPanel();
  return Render_Present((int)(intptr_t)g_RenderState);
}
// 420B10: variable 'v4' is possibly undefined
// 420B4F: variable 'v6' is possibly undefined
// 420BA5: variable 'v9' is possibly undefined
// 420BA5: variable 'v8' is possibly undefined
// 420BCC: variable 'v10' is possibly undefined
// 420BCC: variable 'v11' is possibly undefined
// 420C82: variable 'v12' is possibly undefined
// 420C87: variable 'v15' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00420CD0) --------------------------------------------------------
int  Castle_BuildSchoolWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  /* 420F17: `mov ecx, 74h` - 116 dwords, then the trailing `movsw; movsb`
     completes the 467-byte record.  IDA never initialised this counter
     (flagged at 420F25), so the copy length was garbage. */
  int recordDwordCount = 116; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildSchool((char *)(uintptr_t)g_SelectedBuildingRecord, a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
  {
    recordCopy = (_BYTE *)(uintptr_t)Mem_Alloc(BUILDING_RECORD_SIZE, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)(uintptr_t)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)(uintptr_t)tailSrc;
    tailDst[2] = *(_BYTE *)(uintptr_t)(tailSrc + 2);
    recordCopyPtr = (int)(intptr_t)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_SCHOOL;
    Audio_PlaySoundEffectByName(aBudowaSzkola, 64);
    Castle_PlayAddonConstructionReveal(251, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420D05: variable 'v5' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420D50) --------------------------------------------------------
int  Castle_BuildWorkshopWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  /* sub_420D50: `mov eax, ds:dword_526A64` - the selected building record. */
  Building_BuildWorkshop(g_SelectedBuildingRecord, a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
  {
    recordCopy = (_BYTE *)(uintptr_t)Mem_Alloc(BUILDING_RECORD_SIZE, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)(uintptr_t)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)(uintptr_t)tailSrc;
    tailDst[2] = *(_BYTE *)(uintptr_t)(tailSrc + 2);
    recordCopyPtr = (int)(intptr_t)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_WORKSHOP;
    Audio_PlaySoundEffectByName(aBudowaWarszt_0, 64);
    Castle_PlayAddonConstructionReveal(252, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420D85: variable 'v5' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420DD0) --------------------------------------------------------
int  Castle_BuildBarracksWithAnimation(int a1 CLASH95_UNUSED, char a2, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  Building_BuildBarracks(g_SelectedBuildingRecord, a2, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    recordCopy = (_BYTE *)(uintptr_t)Mem_Alloc(BUILDING_RECORD_SIZE, 116, a2, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)(uintptr_t)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)(uintptr_t)tailSrc;
    tailDst[2] = *(_BYTE *)(uintptr_t)(tailSrc + 2);
    recordCopyPtr = (int)(intptr_t)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_BARRACKS;
    Audio_PlaySoundEffectByName(aBudowaBaraki, 64);
    Castle_PlayAddonConstructionReveal(254, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420E05: variable 'v6' is possibly undefined
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420E50) --------------------------------------------------------
int  Castle_BuildHospitalWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx
  char *soundName; // eax

  /* same __usercall: eax = the selected building record. */
  Building_BuildHospital(g_SelectedBuildingRecord, a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
  {
    recordCopy = (_BYTE *)(uintptr_t)Mem_Alloc(BUILDING_RECORD_SIZE, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)(uintptr_t)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)(uintptr_t)tailSrc;
    tailDst[2] = *(_BYTE *)(uintptr_t)(tailSrc + 2);
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_HOSPITAL;
    recordCopyPtr = (int)(intptr_t)recordCopy;
    if ( PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(uintptr_t)(g_SelectedBuildingRecord + 2)) )
      soundName = aBudowaChrzesci;
    else
      soundName = aBudowaPoganie;
    Audio_PlaySoundEffectByName(soundName, 64);
    Castle_PlayAddonConstructionReveal(250, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 420E85: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420EF0) --------------------------------------------------------
int  Castle_BuildSmithsWithAnimation(char a1, DWORD runtime_context)
{
  int result; // eax
  _BYTE *recordCopy; // eax
  int recordBase; // esi
  int recordDwordCount; // ecx
  _BYTE *tailDst; // edi
  int tailSrc; // esi
  int recordCopyPtr; // ebx

  /* 420EF0: `mov eax, ds:dword_526A64; call sub_41F020` - the selected
     building record is the EAX argument. */
  Building_BuildSmiths(g_SelectedBuildingRecord, a1, runtime_context);
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) != 0 )
  {
    recordCopy = (_BYTE *)(uintptr_t)Mem_Alloc(BUILDING_RECORD_SIZE, 116, a1, runtime_context);
    recordBase = g_SelectedBuildingRecord;
    qmemcpy(recordCopy, (const void *)(uintptr_t)g_SelectedBuildingRecord, 4 * recordDwordCount);
    tailSrc = recordBase + 4 * recordDwordCount;
    tailDst = &recordCopy[4 * recordDwordCount];
    *(_WORD *)tailDst = *(_WORD *)(uintptr_t)tailSrc;
    tailDst[2] = *(_BYTE *)(uintptr_t)(tailSrc + 2);
    recordCopyPtr = (int)(intptr_t)recordCopy;
    recordCopy[416] &= ~BUILDING_ADDON_FLAG_SMITHS;
    Audio_PlaySoundEffectByName(aBudowaKuznia, 64);
    Castle_PlayAddonConstructionReveal(253, recordCopyPtr);
    Castle_UpdateGateToggles();
    return j__nfree_();
  }
  return result;
}
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420F70) --------------------------------------------------------
BOOL Building_HandleUpgradeButtonAction(void)
{
  BOOL result; // eax

  result = Building_TryStartUpgrade((unsigned __int8 *)(uintptr_t)g_SelectedBuildingRecord);
  if ( result )
    return CRT_RunGuardedStaticLocalInit();
  return result;
}
// 420F80: using guessed type int sub_41FF80(void);
// 526A64: using guessed type int g_SelectedBuildingRecord;

//----- (00420FB0) --------------------------------------------------------
int  Castle_ConfirmDestroyCurrentBuilding(int a1, char a2, DWORD a3, double a4)
{
  int result; // eax
  int v5; // edx
  int promptStrings[6]; // [esp+0h] [ebp-18h]

  promptStrings[0] = (int)(intptr_t)g_CastleConfirmDestroyPrompt[0];
  promptStrings[1] = (int)(intptr_t)g_CastleConfirmDestroyPrompt[1];
  promptStrings[2] = (int)(intptr_t)g_CastleConfirmDestroyPrompt[2];
  result = YesNoWindow(promptStrings[(unsigned __int8)g_LanguageIndex], g_CastleScreenPaletteBuffer, a1, a2, a3);
  if ( result )
  {
    Building_Destroy(g_SelectedBuildingRecord, a2, a3, a4);
    result = Audio_PlaySoundEffectByName(aNiszcz, v5);
    g_CastleDestroyConfirmed = 1;
    g_CastleScreenExitRequested = 1;
  }
  return result;
}
// 420FF3: variable 'v5' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 514144: using guessed type char *off_514144[3];
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 526E80: using guessed type int g_CastleScreenExitRequested;
// 526E84: using guessed type int g_CastleDestroyConfirmed;

//----- (00421010) --------------------------------------------------------
int Castle_DrawStatusPanel(void)
{
  int SpriteForChar; // eax
  int buildingSprite; // eax
  int result; // eax
  int overlaySprite; // eax

  SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(5, 5, SpriteForChar, 0);
  if ( PLAYER_RELIGION_FLAG(g_CurrentPlayerIndex) )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, g_CurrentPlayerIndex + 5);
    Compat_RenderDeviceDrawMenuSprite(9, 9, SpriteForChar, 1);
  }
  Render_ReleaseSurface(7, 0);
  buildingSprite = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, *(unsigned __int8 *)(uintptr_t)(g_SelectedBuildingRecord + 421) + 3 * g_CurrentPlayerIndex + 11);
  Compat_RenderDeviceDrawMenuSprite(26, 156, buildingSprite, 1);
  UI_DrawTextFmt(5, 41, 275, 10, 3, (const char*)(intptr_t)(g_SelectedBuildingRecord + 5));
  UI_DrawTextFmt(5, 58, 87, 30, 2, (const char*)(intptr_t)((int)(intptr_t)aD_42));
  UI_DrawTextFmt(5, 58, 149, 30, 2, (const char*)(intptr_t)((int)(intptr_t)aD_43));
  UI_DrawUnitStatsValues(g_SelectedBuildingRecord);
  UI_DrawTextFmt(5, 58, 211, 30, 2, (const char*)(intptr_t)((int)(intptr_t)aD_44));
  UI_DrawTextFmt(5, 58, 273, 30, 2, (const char*)(intptr_t)((int)(intptr_t)aD_45));
  result = g_SelectedBuildingRecord;
  if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 435) & 7) != 0 )
  {
    overlaySprite = DLX_GetSpriteForChar(g_CastleStatusSpriteSet, 10);
    return Compat_RenderDeviceDrawMenuSprite(43, 127, overlaySprite, 1);
  }
  return result;
}
// 421142: variable 'v3' is possibly undefined
// 421142: variable 'v4' is possibly undefined
// 42116C: variable 'v5' is possibly undefined
// 42116C: variable 'v6' is possibly undefined
// 421197: variable 'v7' is possibly undefined
// 421197: variable 'v8' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E7C: using guessed type int g_CastleStatusSpriteSet;

CLASH95_INTERNAL void Castle_EnsureCompositeStatusWidget(void)
{
  static const char castle_status_button_sound[] CLASH95_LOCAL_DATA_SYMBOL("castle_status_button_sound.0", "Castle_EnsureCompositeStatusWidget.castle_status_button_sound") = "duze";

  if ( g_CastleCompositeStatusWidgetInitialized )
    return;

  memset(g_CastleStatusWidgetRecord, 0, sizeof(g_CastleStatusWidgetRecord));
  *(_DWORD *)(g_CastleStatusWidgetRecord + 0) = 31;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 4) = 432;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 8) = 1;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 12) = (int)(uintptr_t)&g_CastleSceneIconSpriteSet;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 16) = 6;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 20) = 7;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 24) = -1;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 32) = (int)(uintptr_t)&Castle_RequestManagementScreenExit;
  *(_DWORD *)(g_CastleStatusWidgetRecord + 49) = (int)(uintptr_t)castle_status_button_sound;
  *(_DWORD *)(g_CastleStatusWidgetRecord + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE) = -1;
  g_CastleCompositeStatusWidgetInitialized = 1;
}
