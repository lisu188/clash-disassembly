/* Generated from src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "persistence_internal.h"
#include "persistence_state.h"
#include "persistence_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0044E880) --------------------------------------------------------
int  BuildingPrisoner_RecalculateRansomValue(int prisonerRecord)
{
  int basePower; // ebx
  int v2; // edx
  unsigned int ransomValue; // eax
  int v4; // ecx
  int result; // eax
  int v6; // eax

  basePower = AI_TickNationPostTurn(*(unsigned __int8 *)(uintptr_t)(prisonerRecord + 1));
  ransomValue = basePower * Rng_RandRange(7, v2) / 0x64;
  *(_WORD *)(uintptr_t)(v4 + 4) = ransomValue;
  if ( !(_WORD)ransomValue )
  {
    v6 = AI_TickNationPostTurn(g_CurrentPlayerIndex);
    *(_WORD *)(uintptr_t)(v4 + 4) = 13 * v6 / 10;
  }
  result = 10 * (*(unsigned __int16 *)(uintptr_t)(v4 + 4) / 10);
  *(_WORD *)(uintptr_t)(v4 + 4) = result;
  return result;
}
// 44E89B: variable 'v2' is possibly undefined
// 44E8AC: variable 'v4' is possibly undefined
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044E900) --------------------------------------------------------
signed int  Prisoner_SetInCastles(int a1, char a2, DWORD a3)
{
  int queued_index; // ecx
  signed int result; // eax
  int queued_prisoner; // edx
  int building_index; // esi
  int best_building_index; // edi
  int building; // ebx
  int best_distance; // [esp+10h] [ebp-1Ch]
  int distance; // eax
  int dx; // ebp/ebx
  int dy; // ebp/edi
  int prisoner_slot; // eax
  int prisoner; // eax
  int building_offset; // ebp
  char prisoner_owner; // bl
  const char *message_format; // edi
  int message_table[3]; // [esp+0h] [ebp-2Ch]

  Debug_Log(a1, a2, a3, (int)(intptr_t)aPrisoner_setin);
  result = 0;
  for ( queued_index = 0; queued_index < 10; ++queued_index )
  {
    queued_prisoner = PLAYER_DATA(g_CurrentPlayerIndex) + 1357 + 6 * queued_index;
    if ( *(char *)(uintptr_t)queued_prisoner == -1 )
      continue;

    building_index = 0;
    best_building_index = -1;
    best_distance = MAP_WIDTH_TILES + MAP_HEIGHT_TILES;
    while ( building_index < 100 )
    {
      building = UNIT_RECORD(building_index);
      result = *(char *)(uintptr_t)(building + 4);
      if ( (unsigned int)result < 4 && *(__int16 *)(uintptr_t)(building + 16) != -1 )
      {
        if ( *(char *)(uintptr_t)(building + 4) == 2 && *(unsigned __int8 *)(uintptr_t)(building + 2) == g_CurrentPlayerIndex )
        {
          dx = *(unsigned __int16 *)(uintptr_t)(queued_prisoner + 4) - *(unsigned __int8 *)(uintptr_t)(building + 1);
          dy = *(unsigned __int16 *)(uintptr_t)(queued_prisoner + 2) - *(unsigned __int8 *)(uintptr_t)building;
          distance = Math_CeilSqrt(dx * dx + dy * dy);
          if ( distance < best_distance && Building_FindFreePrisonerSlot(building) != -1 )
          {
            best_distance = distance;
            best_building_index = building_index;
          }
        }
      }
      ++building_index;
    }

    if ( best_building_index == -1 )
    {
      *(_BYTE *)(uintptr_t)queued_prisoner = -1;
      continue;
    }

    building_offset = BUILDING_RECORD_SIZE * best_building_index;
    building = UNIT_RECORD(best_building_index);
    prisoner_slot = Building_FindFreePrisonerSlot(building);
    prisoner = BUILDING_PRISONER_SLOT(building, prisoner_slot);
    BUILDING_PRISONER_TYPE(prisoner) = *(char *)(uintptr_t)queued_prisoner;
    prisoner_owner = *(_BYTE *)(uintptr_t)(queued_prisoner + 1);
    *(_BYTE *)(uintptr_t)(prisoner + 2) = 0;
    BUILDING_PRISONER_ACTION(prisoner) = 0;
    BUILDING_PRISONER_OWNER(prisoner) = prisoner_owner;
    BuildingPrisoner_RecalculateRansomValue(prisoner);
    *(_BYTE *)(uintptr_t)queued_prisoner = -1;
    result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      continue;
    Win_PlayModeChangeFrameTransition(aUwiezic, 1, queued_index, prisoner_owner, building_offset);
    message_table[0] = (int)(intptr_t)g_PrisonerCastleIntakeTexts[0];
    message_table[1] = (int)(intptr_t)g_PrisonerCastleIntakeTexts[1];
    message_table[2] = (int)(intptr_t)g_PrisonerCastleIntakeTexts[2];
    message_format = (const char *)(uintptr_t)message_table[(unsigned __int8)g_LanguageIndex];
    sprintf_(&g_PrisonerIntakeMessageBuffer, message_format, building + 5);
    result = UI_ShowInfoWindow(
               (int)(intptr_t)&g_PrisonerIntakeMessageBuffer,
               0,
               0,
               building_offset,
               (int)(intptr_t)message_format,
               (int)(intptr_t)&g_PrisonerCastleIntakeTexts[3]);
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D08: using guessed type char *g_PrisonerCastleIntakeTexts[21];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044EB70) --------------------------------------------------------
int  BuildingPrisoner_SetAction(int a1, char actionCode, DWORD a3)
{
  int slotIndex; // edx
  int result; // eax
  int buildingRecord; // ecx

  Debug_Log(a1, actionCode, a3, (int)(intptr_t)aBuilding_setpr);
  result = slotIndex;
  BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(buildingRecord, slotIndex)) = actionCode;
  return result;
}
// 44EB80: variable 'v3' is possibly undefined
// 44EB8E: variable 'v5' is possibly undefined

//----- (0044EBA0) --------------------------------------------------------
int  BuildingPrisoner_GetAction(int buildingRecord, int prisonerSlot)
{
  return BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot));
}

//----- (0044EBC0) --------------------------------------------------------
int  Prisoner_Kill(int buildingRecord, char prisonerSlot, DWORD a3)
{
  unsigned __int8 prisoner_slot; // edx

  Debug_Log(buildingRecord, prisonerSlot, a3, (int)(intptr_t)aPrisoner_kill0);
  prisoner_slot = (unsigned __int8)prisonerSlot;
  BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, prisoner_slot)) = -1;
  return prisoner_slot;
}

//----- (0044EBF0) --------------------------------------------------------
int  Prisoner_Behead(int buildingRecord, int prisonerRecord, char slotIndex, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  const char *formatString; // esi
  int v9; // ecx
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-74h] BYREF
  int beheadTextTable[4]; // [esp+64h] [ebp-10h] BYREF

  beheadTextTable[3] = prisonerRecord;
  Debug_Log(buildingRecord, slotIndex, a4, (int)(intptr_t)aPrisoner_behea);
  Prisoner_Kill(v4, slotIndex, a4);
  result = gameData;
  if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(v5 + 2) + gameData + 140051) )
  {
    Win_PlayModeChangeFrameTransition(aZciecie, 1, v5, slotIndex, a4);
    beheadTextTable[0] = (int)(intptr_t)g_PrisonerBeheadingTexts[0];
    beheadTextTable[1] = (int)(intptr_t)g_PrisonerBeheadingTexts[1];
    beheadTextTable[2] = (int)(intptr_t)g_PrisonerBeheadingTexts[2];
    formatString = (const char *)(uintptr_t)beheadTextTable[(unsigned __int8)g_LanguageIndex];
    sprintf_(messageBuffer, formatString, v7 + 5);
    return UI_ShowInfoWindow((const char *)messageBuffer, 0, v9, a4, (int)(intptr_t)&beheadTextTable[3], (int)(intptr_t)formatString);
  }
  return result;
}
// 44EC07: variable 'v4' is possibly undefined
// 44EC0E: variable 'v5' is possibly undefined
// 44EC52: variable 'v7' is possibly undefined
// 44EC6B: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D14: using guessed type char *g_PrisonerBeheadingTexts[18];
// 5202E4: using guessed type int gameData;

//----- (0044EC80) --------------------------------------------------------
BOOL  Building_IsVisibleToPlayer(unsigned __int8 *buildingCoords, int playerIndex)
{
  unsigned __int8 *v3; // ecx
  BOOL result; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 *v6; // ecx

  if ( Map_IsTileVisibleToPlayer(*buildingCoords, buildingCoords[1], playerIndex) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v3 + 1, v3[1], playerIndex) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v5 + 1, v5[1] + 1, playerIndex) )
    return 1;
  result = Map_IsTileVisibleToPlayer(*v6, v6[1] + 1, playerIndex);
  if ( result )
    return 1;
  return result;
}
// 44ECA6: variable 'v3' is possibly undefined
// 44ECBB: variable 'v5' is possibly undefined
// 44ECD2: variable 'v6' is possibly undefined

//----- (0044ECF0) --------------------------------------------------------
int  Prisoner_FindRichestHiddenEnemyCastle(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int bestValue; // edi
  int castleIndex; // ebx
  int castleRecordOffset; // ecx
  int castleValue; // eax
  int bestCastleIndex; // [esp+4h] [ebp-18h]

  bestValue = 0;
  castleIndex = 0;
  castleRecordOffset = 0;
  bestCastleIndex = -1;
  do
  {
    if ( *(_BYTE *)(uintptr_t)(castleRecordOffset + gameData + 509678) == 2
      && *(unsigned __int8 *)(uintptr_t)(castleRecordOffset + gameData + 509676) == enemyPlayerIndex
      && !Building_IsVisibleToPlayer((unsigned __int8 *)(uintptr_t)(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET), viewerPlayerIndex) )
    {
      castleValue = Building_GetTotalValue(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET);
      if ( castleValue > bestValue )
      {
        bestValue = castleValue;
        bestCastleIndex = castleIndex;
      }
    }
    ++castleIndex;
    castleRecordOffset += 467;
  }
  while ( castleIndex < 100 );
  if ( bestCastleIndex == -1 )
    return 0;
  else
    return UNIT_RECORD(bestCastleIndex);
}
// 44ED4A: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EDB0) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyCastle(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int castleRecordOffset; // ecx

  castleRecordOffset = 0;
  while ( *(_BYTE *)(uintptr_t)(gameData + castleRecordOffset + 509678) != 2
       || *(unsigned __int8 *)(uintptr_t)(gameData + castleRecordOffset + 509676) != enemyPlayerIndex
       || Building_IsVisibleToPlayer((unsigned __int8 *)(uintptr_t)(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET), viewerPlayerIndex) )
  {
    castleRecordOffset += 467;
    if ( castleRecordOffset >= 46700 )
      return 0;
  }
  return castleRecordOffset + gameData + BUILDING_TABLE_OFFSET;
}
// 44EDF0: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EE20) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyUnitStack(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int stackIndex; // ecx
  int stackRecordOffset; // edi
  int stackRecordBase; // eax

  stackIndex = 0;
LABEL_2:
  if ( (unsigned int)*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28 )
  {
    stackRecordOffset = UNIT_STACK_STRIDE * stackIndex;
    stackRecordBase = gameData + UNIT_STACK_STRIDE * stackIndex;
    if ( *(unsigned __int8 *)(uintptr_t)(stackRecordBase + 147178) == enemyPlayerIndex
      && !Map_IsTileVisibleToPlayer(*(__int16 *)(uintptr_t)(stackRecordBase + 147174), *(__int16 *)(uintptr_t)(stackRecordBase + 147176), viewerPlayerIndex) )
    {
      return gameData + UNIT_STACK_TABLE_OFFSET + stackRecordOffset;
    }
  }
  while ( ++stackIndex < 500 )
  {
    if ( stackIndex >= 0 )
      goto LABEL_2;
  }
  return 0;
}
// 44EEB0: conditional instruction was optimized away because ecx.4<1F4u
// 44EE57: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 44EE9D: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EEE0) --------------------------------------------------------
void  Map_RevealTilesInRadius2ForPlayer(int centerRow, int centerColumn, int playerIndex)
{
  int rowCursor; // edi
  int colDelta; // esi
  signed int colCursor; // ecx
  int rowMax; // [esp+4h] [ebp-24h]
  int colMin; // [esp+8h] [ebp-20h]
  int i; // [esp+Ch] [ebp-1Ch]
  int colMax; // [esp+14h] [ebp-14h]

  colMax = centerColumn + 2;
  rowCursor = centerRow - 2;
  colMin = centerColumn - 2;
  rowMax = centerRow + 2;
  for ( i = -2; rowCursor < rowMax; ++i )
  {
    colDelta = colMin - centerColumn;
    if ( colMin < colMax )
    {
      do
      {
        if ( Math_CeilSqrt(i * i + colDelta * colDelta) <= 2 )
          Map_RevealTileWithPropagation(rowCursor, colCursor, playerIndex);
        ++colDelta;
      }
      while ( colCursor + 1 < colMax );
    }
    ++rowCursor;
  }
  Locale_DrawInteger();
}
// 44EF47: variable 'v5' is possibly undefined

//----- (0044EFA0) --------------------------------------------------------
unsigned int  Prisoner_Torture(int buildingRecord, int prisonerSlot, int prisonerRecord, char slotIndex, DWORD context)
{
  unsigned int result; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  unsigned __int8 *revealTarget; // ebx
  int v11; // ecx
  char **revealTextTablePtr; // esi
  int v13; // ecx
  int *revealFormatArg; // edi
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int localizedCastleTexts[3]; // [esp+0h] [ebp-4Ch]
  int localizedResistanceTexts[3]; // [esp+Ch] [ebp-40h] BYREF
  int localizedRichestCastleTexts[3]; // [esp+18h] [ebp-34h] BYREF
  int localizedNoConfessionTexts[3]; // [esp+24h] [ebp-28h]
  int localizedEnemyStackTexts[7]; // [esp+30h] [ebp-1Ch] BYREF

  localizedEnemyStackTexts[5] = prisonerRecord;
  Debug_Log(buildingRecord, slotIndex, context, (int)(intptr_t)aPrisoner_tortu);
  result = Rng_RandRange(0, 7);
  switch ( result )
  {
    case 0u:
    case 5u:
      Debug_Log(v7, slotIndex, context, (int)(intptr_t)aPrisoner_tor_0);
      revealTarget = (unsigned __int8 *)(uintptr_t)Prisoner_FindRichestHiddenEnemyCastle(*(unsigned __int8 *)(uintptr_t)(v8 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(uintptr_t)(v8 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)(intptr_t)revealTarget, context);
      Prisoner_Kill(v9, (char)(intptr_t)revealTarget, context);
      Map_RevealTilesInRadius2ForPlayer(*revealTarget, revealTarget[1], *(unsigned __int8 *)(uintptr_t)(v11 + 2));
      localizedRichestCastleTexts[0] = (int)(intptr_t)g_PrisonerTortureRichestCastleRevealTexts[0];
      localizedRichestCastleTexts[1] = (int)(intptr_t)g_PrisonerTortureRichestCastleRevealTexts[1];
      localizedRichestCastleTexts[2] = (int)(intptr_t)g_PrisonerTortureRichestCastleRevealTexts[2];
      revealTextTablePtr = &g_PrisonerTortureRichestCastleRevealTexts[3];
      revealFormatArg = (int *)(uintptr_t)localizedRichestCastleTexts[(unsigned __int8)g_LanguageIndex];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)revealFormatArg, v13 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, context, (int)(intptr_t)revealFormatArg, (int)(intptr_t)revealTextTablePtr);
    case 1u:
    case 6u:
      Debug_Log(v7, slotIndex, context, (int)(intptr_t)aPrisoner_tor_1);
      revealTarget = (unsigned __int8 *)(uintptr_t)Prisoner_FindAnyHiddenEnemyCastle(*(unsigned __int8 *)(uintptr_t)(v16 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(uintptr_t)(v16 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)(intptr_t)revealTarget, context);
      Prisoner_Kill(v9, (char)(intptr_t)revealTarget, context);
      Map_RevealTilesInRadius2ForPlayer(*revealTarget, revealTarget[1], *(unsigned __int8 *)(uintptr_t)(v17 + 2));
      localizedCastleTexts[0] = (int)(intptr_t)g_PrisonerTortureCastleRevealTexts[0];
      localizedCastleTexts[1] = (int)(intptr_t)g_PrisonerTortureCastleRevealTexts[1];
      localizedCastleTexts[2] = (int)(intptr_t)g_PrisonerTortureCastleRevealTexts[2];
      revealFormatArg = localizedResistanceTexts;
      revealTextTablePtr = (char **)(uintptr_t)localizedCastleTexts[(unsigned __int8)g_LanguageIndex];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)revealTextTablePtr, v18 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, context, (int)(intptr_t)revealFormatArg, (int)(intptr_t)revealTextTablePtr);
    case 2u:
    case 7u:
      Debug_Log(v7, slotIndex, context, (int)(intptr_t)aPrisoner_tor_2);
      revealTarget = (unsigned __int8 *)(uintptr_t)Prisoner_FindAnyHiddenEnemyUnitStack(*(unsigned __int8 *)(uintptr_t)(v19 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(uintptr_t)(v19 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)(intptr_t)revealTarget, context);
      Prisoner_Kill(v9, (char)(intptr_t)revealTarget, context);
      Map_RevealTilesInRadius2ForPlayer(*(__int16 *)revealTarget, *((__int16 *)revealTarget + 1), *(unsigned __int8 *)(uintptr_t)(v20 + 2));
      localizedEnemyStackTexts[0] = (int)(intptr_t)g_PrisonerTortureEnemyStackRevealTexts[0];
      localizedEnemyStackTexts[1] = (int)(intptr_t)g_PrisonerTortureEnemyStackRevealTexts[1];
      localizedEnemyStackTexts[2] = (int)(intptr_t)g_PrisonerTortureEnemyStackRevealTexts[2];
      revealTextTablePtr = &g_PrisonerTortureEnemyStackRevealTexts[3];
      revealFormatArg = &localizedEnemyStackTexts[3];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)(uintptr_t)localizedEnemyStackTexts[(unsigned __int8)g_LanguageIndex], v21 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, context, (int)(intptr_t)revealFormatArg, (int)(intptr_t)revealTextTablePtr);
    case 3u:
      Debug_Log(v7, slotIndex, context, (int)(intptr_t)aPrisoner_tor_3);
      Prisoner_Kill(v22, slotIndex, context);
      localizedNoConfessionTexts[0] = (int)(intptr_t)g_PrisonerTortureNoConfessionDeathTexts[0];
      localizedNoConfessionTexts[1] = (int)(intptr_t)g_PrisonerTortureNoConfessionDeathTexts[1];
      localizedNoConfessionTexts[2] = (int)(intptr_t)g_PrisonerTortureNoConfessionDeathTexts[2];
      revealTextTablePtr = &g_PrisonerTortureNoConfessionDeathTexts[3];
      revealFormatArg = localizedEnemyStackTexts;
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)(uintptr_t)localizedNoConfessionTexts[(unsigned __int8)g_LanguageIndex], v23 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, context, (int)(intptr_t)revealFormatArg, (int)(intptr_t)revealTextTablePtr);
    case 4u:
      Debug_Log(v7, slotIndex, context, (int)(intptr_t)aPrisoner_tor_4);
      BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(v24, prisonerSlot)) = BUILDING_PRISONER_ACTION_NONE;
      localizedResistanceTexts[0] = (int)(intptr_t)g_PrisonerTortureResistanceTexts[0];
      localizedResistanceTexts[1] = (int)(intptr_t)g_PrisonerTortureResistanceTexts[1];
      localizedResistanceTexts[2] = (int)(intptr_t)g_PrisonerTortureResistanceTexts[2];
      revealTextTablePtr = &g_PrisonerTortureResistanceTexts[3];
      revealFormatArg = localizedRichestCastleTexts;
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)(uintptr_t)localizedResistanceTexts[(unsigned __int8)g_LanguageIndex], v24 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, context, (int)(intptr_t)revealFormatArg, (int)(intptr_t)revealTextTablePtr);
    default:
      return result;
  }
}
// 44EFDB: variable 'v7' is possibly undefined
// 44EFF1: variable 'v8' is possibly undefined
// 44F010: variable 'v9' is possibly undefined
// 44F015: variable 'v11' is possibly undefined
// 44F03B: variable 'v13' is possibly undefined
// 44F055: variable 'v15' is possibly undefined
// 44F08E: variable 'v16' is possibly undefined
// 44F0B9: variable 'v17' is possibly undefined
// 44F0DA: variable 'v18' is possibly undefined
// 44F100: variable 'v19' is possibly undefined
// 44F12E: variable 'v20' is possibly undefined
// 44F14F: variable 'v21' is possibly undefined
// 44F174: variable 'v22' is possibly undefined
// 44F186: variable 'v23' is possibly undefined
// 44F1AA: variable 'v24' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D20: using guessed type char *g_PrisonerTortureRichestCastleRevealTexts[15];
// 518D2C: using guessed type char *g_PrisonerTortureCastleRevealTexts[12];
// 518D38: using guessed type char *g_PrisonerTortureEnemyStackRevealTexts[9];
// 518D44: using guessed type char *g_PrisonerTortureNoConfessionDeathTexts[6];
// 518D50: using guessed type char *g_PrisonerTortureResistanceTexts[3];

//----- (0044F1E0) --------------------------------------------------------
int  Building_CreateSpecialPersonageGarrisonUnit(DWORD buildingRecord, unit_type unitType, int a3, char prisonerSlot, double a5)
{
  int garrison_slot_ptr; // edx
  int slot_index; // eax
  int result; // eax
  int slot_offset; // ecx
  int leave_mask[12]; // [esp+0h] [ebp-48h] BYREF

  Debug_Log(a3, prisonerSlot, buildingRecord, (int)(intptr_t)aBuilding_creat);
  garrison_slot_ptr = buildingRecord + 18;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)(uintptr_t)garrison_slot_ptr == -1 )
      break;
    garrison_slot_ptr += 31;
  }
  if ( slot_index == 12 )
  {
    qmemcpy(leave_mask, &g_SpecialPersonageLeaveMaskTemplate, sizeof(leave_mask));
    Building_UnitsLeave((unsigned __int8 *)(uintptr_t)buildingRecord, leave_mask, a5);
    slot_index = 0;
  }
  slot_offset = 31 * slot_index;
  result = UnitSlot_InitFromType(buildingRecord + 18 + slot_offset, unitType, *(_BYTE *)(uintptr_t)(buildingRecord + 2));
  *(_BYTE *)(uintptr_t)(buildingRecord + 30 + slot_offset) |= 3u;
  return result;
}

//----- (0044F260) --------------------------------------------------------
unsigned int  Prisoner_Pay(int a1, int prisonerSlot, DWORD a3, double a4)
{
  DWORD buildingRecord; // ecx
  unsigned int result; // eax
  unsigned int playerGold; // edi
  int v8; // ecx
  int v9; // ecx
  const char *defectionFormat; // esi
  int v11; // ecx
  int defectionTexts[8]; // [esp+0h] [ebp-20h] BYREF

  Debug_Log(a1, prisonerSlot, a3, (int)(intptr_t)aPrisoner_pay0x);
  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 2) + 140051) )
  {
    result = BUILDING_PRISONER_RANSOM(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot));
    playerGold = *(_DWORD *)(uintptr_t)(buildingRecord + 438);
    if ( result > playerGold )
      return result;
    a3 = playerGold - result;
    *(_DWORD *)(uintptr_t)(buildingRecord + 438) = playerGold - result;
  }
  Building_CreateSpecialPersonageGarrisonUnit(buildingRecord, BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot)), buildingRecord, prisonerSlot, a4);
  Prisoner_Kill(v8, prisonerSlot, a3);
  result = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(v9 + 2);
  if ( *(_DWORD *)(uintptr_t)(gameData + result + 140051) )
  {
    defectionTexts[0] = (int)(intptr_t)g_PrisonerBriberyDefectionTexts[0];
    defectionTexts[1] = (int)(intptr_t)g_PrisonerBriberyDefectionTexts[1];
    defectionTexts[2] = (int)(intptr_t)g_PrisonerBriberyDefectionTexts[2];
    defectionFormat = (const char *)(uintptr_t)defectionTexts[(unsigned __int8)g_LanguageIndex];
    sprintf_(&g_InfoWindowFormatBuffer, defectionFormat, v9 + 5);
    return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v11, a3, (int)(intptr_t)&defectionTexts[3], (int)(intptr_t)defectionFormat);
  }
  return result;
}
// 44F27A: variable 'v5' is possibly undefined
// 44F2E3: variable 'v8' is possibly undefined
// 44F2EA: variable 'v9' is possibly undefined
// 44F33A: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D8C: using guessed type char *g_PrisonerBriberyDefectionTexts[6];
// 5202E4: using guessed type int gameData;

//----- (0044F350) --------------------------------------------------------
char  Prisoner_NewTurn(DWORD buildingRecord, int a2, char a3, double a4)
{
  int missionIndex; // edx
  int result; // eax
  int slotIndex; // ebx
  char *prisonerCursor; // ecx
  int v9; // ecx
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-90h] BYREF
  int exhaustionTextTable[3]; // [esp+64h] [ebp-2Ch]
  int prisonerSlotPtr; // [esp+70h] [ebp-20h] BYREF
  DWORD buildingNamePtr; // [esp+74h] [ebp-1Ch]

  missionIndex = ACTIVE_MISSION_INDEX;
  if ( missionIndex != 4 && missionIndex != 6 || (result = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 2), *(_DWORD *)(uintptr_t)(gameData + result + 140051)) )
  {
    Debug_Log(a2, a3, buildingRecord, (int)(intptr_t)aPrisoner_newtu);
    buildingNamePtr = buildingRecord + 5;
    slotIndex = 0;
    prisonerCursor = (char *)(uintptr_t)buildingRecord;
    prisonerSlotPtr = buildingRecord + 445;
    do
    {
      result = prisonerCursor[445];
      if ( result != -1 )
      {
        ++prisonerCursor[447];
        if ( !*(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 2) + 140051) && prisonerCursor[447] == 9 )
          prisonerCursor[448] = BUILDING_PRISONER_ACTION_PAY;
        BuildingPrisoner_RecalculateRansomValue(prisonerSlotPtr);
        if ( prisonerCursor[447] == 10 )
        {
          prisonerCursor[445] = -1;
          result = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 2);
          if ( *(_DWORD *)(uintptr_t)(gameData + result + 140051) )
          {
            exhaustionTextTable[0] = (int)(intptr_t)g_PrisonerDeathByExhaustionTexts[0];
            exhaustionTextTable[1] = (int)(intptr_t)g_PrisonerDeathByExhaustionTexts[1];
            exhaustionTextTable[2] = (int)(intptr_t)g_PrisonerDeathByExhaustionTexts[2];
            a4 = sprintf_(messageBuffer, (const char *)(uintptr_t)exhaustionTextTable[(unsigned __int8)g_LanguageIndex], buildingNamePtr);
            LOBYTE(result) = UI_ShowInfoWindow((const char *)messageBuffer, 0, v9, buildingRecord, (int)(intptr_t)&prisonerSlotPtr, (int)(intptr_t)&g_PrisonerDeathByExhaustionTexts[3]);
          }
        }
        else
        {
          LOBYTE(result) = prisonerCursor[448];
          if ( (unsigned __int8)result >= BUILDING_PRISONER_ACTION_TORTURE )
          {
            if ( (unsigned __int8)result <= BUILDING_PRISONER_ACTION_TORTURE )
            {
              LOBYTE(result) = Prisoner_Torture(buildingRecord, slotIndex, (int)(intptr_t)prisonerCursor, slotIndex, buildingRecord);
            }
            else if ( (_BYTE)result == BUILDING_PRISONER_ACTION_PAY )
            {
              LOBYTE(result) = Prisoner_Pay(buildingRecord, slotIndex, buildingRecord, a4);
            }
          }
          else if ( (_BYTE)result == BUILDING_PRISONER_ACTION_BEHEAD )
          {
            LOBYTE(result) = Prisoner_Behead(buildingRecord, (int)(intptr_t)prisonerCursor, slotIndex, buildingRecord);
          }
        }
      }
      prisonerCursor += 6;
      ++slotIndex;
      prisonerSlotPtr += 6;
    }
    while ( slotIndex < 3 );
  }
  return result;
}
// 44F3F1: variable 'v8' is possibly undefined
// 44F450: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D98: using guessed type char *g_PrisonerDeathByExhaustionTexts[3];
// 5202E4: using guessed type int gameData;

//----- (0044F4E0) --------------------------------------------------------
int  Building_CountPrisoners(int buildingRecord)
{
  int slotLoopEnd; // ebx
  int prisonerCount; // edx

  slotLoopEnd = buildingRecord + 18;
  prisonerCount = 0;
  do
  {
    if ( *(char *)(uintptr_t)(buildingRecord + 445) != -1 )
      ++prisonerCount;
    buildingRecord += 6;
  }
  while ( buildingRecord != slotLoopEnd );
  return prisonerCount;
}

//----- (0044F510) --------------------------------------------------------
BOOL  BuildingPrisonerActionWidget_HasPrisoner(int widgetRecord)
{
  return *(char *)(uintptr_t)(g_CurrentPrisonBuildingRecord + 6 * ((widgetRecord - (int)(intptr_t)&g_PrisonerActionButtonWidgets) / 53 / 3) + 445) != -1;
}
// 5443FC: using guessed type int dword_5443FC;

//----- (0044F580) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBehead(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)(intptr_t)g_RenderState, 0);
  result = (char *)(uintptr_t)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(uintptr_t)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)(intptr_t)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(uintptr_t)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(uintptr_t)(widgetRecord + 49));
  }
  return result;
}
// 44F5BA: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F5F0) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectTorture(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)(intptr_t)g_RenderState, 0);
  result = (char *)(uintptr_t)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(uintptr_t)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)(intptr_t)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(uintptr_t)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(uintptr_t)(widgetRecord + 49));
  }
  return result;
}
// 44F62A: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F660) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBribery(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)(intptr_t)g_RenderState, 0);
  result = (char *)(uintptr_t)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(uintptr_t)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(uintptr_t)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)(intptr_t)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(uintptr_t)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(uintptr_t)(widgetRecord + 49));
  }
  return result;
}
// 44F69A: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F6D0) --------------------------------------------------------
int  BuildingPrisonerPanel_BackButton(int widgetRecord)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  g_PrisonerDialogExitSignal = v3;
  return result;
}
// 44F6DB: variable 'v3' is possibly undefined
// 5443F4: using guessed type int dword_5443F4;

//----- (0044FC70) --------------------------------------------------------
int  Building_DrawPrisonerRows(DWORD a1)
{
  int prisonerRecordOffset; // edi
  int rowIndex; // esi
  int result; // eax
  int SpriteForChar; // eax
  int prisonerTypeSprite; // eax

  prisonerRecordOffset = 0;
  rowIndex = 0;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(18, a1);
  do
  {
    result = *(char *)(uintptr_t)(prisonerRecordOffset + g_CurrentPrisonBuildingRecord + 445);
    if ( result != -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 5);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        368,
        SpriteForChar,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      prisonerTypeSprite = DLX_GetSpriteForChar(g_StatScreenSpriteSet, *(unsigned __int8 *)(uintptr_t)(prisonerRecordOffset + g_CurrentPrisonBuildingRecord + 446));
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        378,
        prisonerTypeSprite,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      result = UI_DrawTextFmt(
                 prisonerRecordOffset,
                 (unsigned __int16)g_PrisonerRowTextXTable[rowIndex] + 1,
                 (unsigned __int16)g_PrisonerRowTextXTable[rowIndex] + 68,
                 461,
                 3,
                 (int)(intptr_t)aD_79);
    }
    ++rowIndex;
    prisonerRecordOffset += 6;
  }
  while ( rowIndex != 3 );
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518DBC: using guessed type __int16 word_518DBC[];
// 5443F0: using guessed type int dword_5443F0;
// 5443FC: using guessed type int dword_5443FC;

//----- (0044FD90) --------------------------------------------------------
int  Queen_DrawRelationshipPanel(DWORD a1, int a2)
{
  int SpriteForChar; // eax
  int queenRelationshipState; // eax

  g_RenderDevice = &g_MainRenderDevice;
  queenRelationshipState = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
  if ( queenRelationshipState > 0 )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 25);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      199,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  Render_ReleaseSurface(17, a1);
  if ( queenRelationshipState == -1 )
    queenRelationshipState = 0;
  return UI_DrawTextFmt(
           a2,
           180,
           500,
           215,
           6,
           (int)(intptr_t)(&g_QueenRelationshipStateTexts[3 * queenRelationshipState])[(unsigned __int8)g_LanguageIndex]);
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519010: using guessed type char *g_QueenRelationshipStateTexts[30];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5443F0: using guessed type int dword_5443F0;

//----- (0044FE70) --------------------------------------------------------
int  Building_ShowPrisonerManagementPanel(int buildingRecord, void *a2, DWORD a3)
{
  int i; // eax
  _DWORD *actionWidgetCursor; // esi
  int j; // edi
  unsigned int prisonerAction; // eax
  int selectedButtonState; // ecx
  int paletteBuffer; // eax
  int v9; // ecx
  _DWORD *spriteSet; // eax
  char paletteBufferByte; // bl
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  void *v17; // ecx
  int SpriteForChar; // eax
  int nationFlagSpriteP1; // eax
  int nationFlagSpriteP2; // eax
  int nationFlagSpriteP3; // eax
  int barIndex; // edx
  int maxPopulation; // ebp
  int zeroBaseline; // ecx
  int playerIndex; // esi
  int playerRecordOffset; // edi
  int playerRuntimeState; // ebx
  int prevMaxNationScore; // ebx
  int nationScore; // eax
  int nationScoreBarByteOffset; // edx
  int prevMaxMilitaryStrength; // ebx
  int militaryStrength; // eax
  int population; // eax
  int currentPopulation; // ebx
  int chartBgSprite1; // eax
  DWORD populationRange; // ebp
  int chartBgSprite2; // eax
  int chartBgSprite3; // eax
  int barRowIndex; // edi
  int chartBgRenderMethods; // esi
  int barValueIndex; // esi
  int nationScoreDivisor; // ecx
  int militaryBarNumerator; // edx
  int maxMilitaryStrengthValue; // ebx
  int militaryDivisor; // ecx
  int militaryBarWidth; // eax
  int playerPopulation; // edx
  int populationBarNumerator; // edx
  int populationDivisor; // ecx
  int initialExitSignal; // ecx
  int exitSignalSentinel; // ecx
  char prisoner0Action; // bl
  int prisonRecordSlot0; // eax
  char prisoner1Action; // bl
  int prisonRecordSlot1; // eax
  char prisoner2Action; // bl
  int prisonRecordSlot2; // eax
  int nationFlagSpriteP4; // eax
  int player5RenderMethods; // edi
  int militaryStrengthBars[5]; // [esp+C4h] [ebp-64h]
  int nationScoreBars[5]; // [esp+D8h] [ebp-50h]
  int populationBars[5]; // [esp+ECh] [ebp-3Ch]
  int maxNationScore; // [esp+100h] [ebp-28h]
  int minPopulation; // [esp+104h] [ebp-24h]
  int barPlayerOffset; // [esp+108h] [ebp-20h]
  int maxMilitaryStrength; // [esp+10Ch] [ebp-1Ch]

  g_CurrentPrisonBuildingRecord = buildingRecord;
  for ( i = 0; i != 477; *(char **)((char *)g_PrisonerDeathByExhaustionTexts + i + 3) = (char *)1 )
    i += 53;
  actionWidgetCursor = g_PrisonerActionButtonWidgets;
  for ( j = 0; j < 3; ++j )
  {
    prisonerAction = BuildingPrisoner_GetAction(g_CurrentPrisonBuildingRecord, j);
    if ( prisonerAction >= BUILDING_PRISONER_ACTION_TORTURE )
    {
      if ( prisonerAction <= BUILDING_PRISONER_ACTION_TORTURE )
      {
        *(_DWORD *)((char *)actionWidgetCursor + 61) = selectedButtonState;
      }
      else if ( prisonerAction == BUILDING_PRISONER_ACTION_PAY )
      {
        *(_DWORD *)((char *)actionWidgetCursor + 114) = selectedButtonState;
      }
    }
    else if ( prisonerAction == BUILDING_PRISONER_ACTION_BEHEAD )
    {
      actionWidgetCursor[2] = selectedButtonState;
    }
    actionWidgetCursor = (_DWORD *)((char *)actionWidgetCursor + 159);
  }
  paletteBuffer = Mem_Alloc(1024, selectedButtonState, (char)(intptr_t)a2, a3);
  if ( paletteBuffer )
  {
    a2 = &g_Runtime_PaletteArrayCtorDescriptor;
    paletteBuffer = _wcpp_4_ctor_array__(v9, 256);
  }
  g_StatScreenPaletteBuffer = paletteBuffer;
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v9, (char)(intptr_t)a2, a3);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)(intptr_t)a2);
  g_StatScreenSpriteSet = (int)(intptr_t)spriteSet;
  paletteBufferByte = g_StatScreenPaletteBuffer;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    aStat_gfx,
    0,
    (uintptr_t)(unsigned int)g_StatScreenPaletteBuffer);
  Palette_LoadOrBuildBlendLookupTable(aStat, g_StatScreenPaletteBuffer, v12, a3);
  Render_LoadResourceSprite_v4(8, (_BYTE *)(uintptr_t)g_StatScreenPaletteBuffer, v13, paletteBufferByte, a3);
  Render_LoadResourceSprite_v4(18, (_BYTE *)(uintptr_t)g_StatScreenPaletteBuffer, v14, paletteBufferByte, a3);
  Render_LoadResourceSprite_v4(17, (_BYTE *)(uintptr_t)g_StatScreenPaletteBuffer, v15, paletteBufferByte, a3);
  RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, g_StatScreenPaletteBuffer, v16, a3);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  g_RenderDevice = v17;
  Render_ReleaseSurface(18, a3);
  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_RUNTIME_STATE_OFFSET) )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(uintptr_t)(gameData + 140063) == 0) + 13);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      8,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 88, 214, 30, 3, gameData + 140028);
  }
  if ( *(_DWORD *)(uintptr_t)(gameData + 141447) )
  {
    nationFlagSpriteP1 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(uintptr_t)(gameData + 141486) == 0) + 15);
    j = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(j + 52))(
      8,
      nationFlagSpriteP1,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 254, 380, 30, 3, gameData + 141451);
  }
  if ( *(_DWORD *)(uintptr_t)(gameData + 142870) )
  {
    nationFlagSpriteP2 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(uintptr_t)(gameData + 142909) == 0) + 17);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      8,
      nationFlagSpriteP2,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 420, 546, 30, 3, gameData + 142874);
  }
  if ( *(_DWORD *)(uintptr_t)(gameData + 144293) )
  {
    nationFlagSpriteP3 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(uintptr_t)(gameData + 144332) == 0) + 19);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      52,
      nationFlagSpriteP3,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 172, 298, 75, 3, gameData + 144297);
  }
  if ( *(_DWORD *)(uintptr_t)(gameData + 145716) )
  {
    nationFlagSpriteP4 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(uintptr_t)(gameData + 145755) == 0) + 21);
    player5RenderMethods = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(player5RenderMethods + 52))(
      52,
      nationFlagSpriteP4,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(player5RenderMethods, 336, 462, 75, 3, gameData + 145720);
  }
  barIndex = 0;
  maxPopulation = 0;
  zeroBaseline = 0;
  playerIndex = 0;
  playerRecordOffset = 0;
  maxNationScore = 0;
  maxMilitaryStrength = 0;
  minPopulation = 0;
  do
  {
    playerRuntimeState = *(_DWORD *)(uintptr_t)(playerRecordOffset + gameData + PLAYER_RUNTIME_STATE_OFFSET);
    if ( zeroBaseline == playerRuntimeState )
    {
      populationBars[barIndex] = playerRuntimeState;
      militaryStrengthBars[barIndex] = playerRuntimeState;
      nationScoreBars[barIndex] = playerRuntimeState;
    }
    else
    {
      prevMaxNationScore = maxNationScore;
      nationScore = AI_TickNationPostTurn(playerIndex);
      *(int *)((char *)nationScoreBars + nationScoreBarByteOffset) = nationScore;
      if ( nationScore > prevMaxNationScore )
        maxNationScore = nationScore;
      prevMaxMilitaryStrength = maxMilitaryStrength;
      militaryStrength = Player_CalcMilitaryStrength(playerIndex);
      militaryStrengthBars[barIndex] = militaryStrength;
      if ( militaryStrength > prevMaxMilitaryStrength )
        maxMilitaryStrength = militaryStrength;
      population = *(__int16 *)(uintptr_t)(playerRecordOffset + gameData + 141441);
      populationBars[barIndex] = population;
      if ( maxPopulation < population )
        maxPopulation = population;
      currentPopulation = populationBars[barIndex];
      if ( zeroBaseline > currentPopulation && currentPopulation < minPopulation )
        minPopulation = populationBars[barIndex];
    }
    playerRecordOffset += 1423;
    ++playerIndex;
    ++barIndex;
  }
  while ( playerIndex < 5 );
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  chartBgSprite1 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  populationRange = maxPopulation - minPopulation;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    107,
    chartBgSprite1,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  chartBgSprite2 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    107,
    chartBgSprite2,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  chartBgSprite3 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  barRowIndex = 0;
  chartBgRenderMethods = *((_DWORD *)g_RenderDevice + 46);
  barPlayerOffset = 0;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(chartBgRenderMethods + 52))(
    107,
    chartBgSprite3,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  barValueIndex = 0;
  do
  {
    if ( *(_DWORD *)(uintptr_t)(barPlayerOffset + gameData + PLAYER_RUNTIME_STATE_OFFSET) )
    {
      if ( maxNationScore )
        nationScoreDivisor = maxNationScore;
      else
        nationScoreDivisor = 1;
      militaryBarNumerator = 123 * militaryStrengthBars[barValueIndex];
      maxMilitaryStrengthValue = maxMilitaryStrength;
      nationScoreBars[barValueIndex] = 123 * nationScoreBars[barValueIndex] / nationScoreDivisor;
      if ( maxMilitaryStrengthValue )
        militaryDivisor = maxMilitaryStrengthValue;
      else
        militaryDivisor = 1;
      militaryBarWidth = militaryBarNumerator / militaryDivisor;
      playerPopulation = populationBars[barValueIndex];
      militaryStrengthBars[barValueIndex] = militaryBarWidth;
      populationBarNumerator = 123 * (playerPopulation - minPopulation);
      if ( populationRange )
        populationDivisor = populationRange;
      else
        populationDivisor = 1;
      populationBars[barValueIndex] = populationBarNumerator / populationDivisor;
      Render_FillRect(
        (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        299,
        LOWORD(nationScoreBars[barValueIndex]) + 299,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x12Bu,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
      Render_FillRect(
        (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        88,
        LOWORD(militaryStrengthBars[barValueIndex]) + 88,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x58u,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
      Render_FillRect(
        (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        510,
        LOWORD(populationBars[barValueIndex]) + 510,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x1FEu,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
    }
    ++barRowIndex;
    ++barValueIndex;
    barPlayerOffset += 1423;
  }
  while ( barRowIndex != 5 );
  Building_DrawPrisonerRows(populationRange);
  Queen_DrawRelationshipPanel(populationRange, 10);
  UIWidgetTable_InitDrawStates(g_PrisonerActionButtonWidgets);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_StatScreenPaletteBuffer, 20);
  Render_Present((int)(intptr_t)g_RenderState);
  g_PrisonerDialogExitSignal = initialExitSignal;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)g_RenderState);
    g_RenderDevice = &g_MainRenderDevice;
    UIWidgetTable_PollHoverAndActions(g_PrisonerActionButtonWidgets, populationRange);
  }
  while ( exitSignalSentinel == g_PrisonerDialogExitSignal );
  if ( g_PrisonerActionButtonState0 == 2 )
  {
    prisoner0Action = BUILDING_PRISONER_ACTION_BEHEAD;
LABEL_48:
    prisonRecordSlot0 = g_CurrentPrisonBuildingRecord;
    goto LABEL_49;
  }
  if ( g_PrisonerActionButtonState1 == 2 )
  {
    prisonRecordSlot0 = g_CurrentPrisonBuildingRecord;
    prisoner0Action = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else
  {
    if ( g_PrisonerActionButtonState2 == 2 )
    {
      prisoner0Action = BUILDING_PRISONER_ACTION_PAY;
      goto LABEL_48;
    }
    prisonRecordSlot0 = g_CurrentPrisonBuildingRecord;
    prisoner0Action = BUILDING_PRISONER_ACTION_NONE;
  }
LABEL_49:
  BuildingPrisoner_SetAction(prisonRecordSlot0, prisoner0Action, populationRange);
  if ( g_PrisonerActionButtonState3 == 2 )
  {
    prisoner1Action = BUILDING_PRISONER_ACTION_BEHEAD;
    prisonRecordSlot1 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState4 == 2 )
  {
    prisonRecordSlot1 = g_CurrentPrisonBuildingRecord;
    prisoner1Action = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else if ( g_PrisonerActionButtonState5 == 2 )
  {
    prisoner1Action = BUILDING_PRISONER_ACTION_PAY;
    prisonRecordSlot1 = g_CurrentPrisonBuildingRecord;
  }
  else
  {
    prisonRecordSlot1 = g_CurrentPrisonBuildingRecord;
    prisoner1Action = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(prisonRecordSlot1, prisoner1Action, populationRange);
  if ( g_PrisonerActionButtonState6 == 2 )
  {
    prisoner2Action = BUILDING_PRISONER_ACTION_BEHEAD;
    prisonRecordSlot2 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState7 == 2 )
  {
    prisoner2Action = BUILDING_PRISONER_ACTION_TORTURE;
    prisonRecordSlot2 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState8 == 2 )
  {
    prisoner2Action = BUILDING_PRISONER_ACTION_PAY;
    prisonRecordSlot2 = g_CurrentPrisonBuildingRecord;
  }
  else
  {
    prisonRecordSlot2 = g_CurrentPrisonBuildingRecord;
    prisoner2Action = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(prisonRecordSlot2, prisoner2Action, g_PrisonerActionButtonState6);
  DLXSpriteSet_ReleaseAndClear(&g_StatScreenSpriteSet);
  j__nfree_();
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 44FEBB: variable 'v7' is possibly undefined
// 44FEE2: variable 'v9' is possibly undefined
// 44FF2F: variable 'v12' is possibly undefined
// 44FF3F: variable 'v13' is possibly undefined
// 44FF4F: variable 'v14' is possibly undefined
// 44FF5F: variable 'v15' is possibly undefined
// 44FF6F: variable 'v16' is possibly undefined
// 44FF8C: variable 'v17' is possibly undefined
// 45019B: variable 'v24' is possibly undefined
// 4501AC: variable 'v30' is possibly undefined
// 4501C3: variable 'v22' is possibly undefined
// 450464: variable 'v50' is possibly undefined
// 450495: variable 'v51' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518D98: using guessed type char *off_518D98[3];
// 518DB0: using guessed type __int16 word_518DB0[];
// 518DB2: using guessed type __int16 word_518DB2[];
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 518E05: using guessed type int dword_518E05;
// 518E3A: using guessed type int dword_518E3A;
// 518E6F: using guessed type int dword_518E6F;
// 518EA4: using guessed type int dword_518EA4;
// 518ED9: using guessed type int dword_518ED9;
// 518F0E: using guessed type int dword_518F0E;
// 518F43: using guessed type int dword_518F43;
// 518F78: using guessed type int dword_518F78;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5443F0: using guessed type int dword_5443F0;
// 5443F4: using guessed type int dword_5443F4;
// 5443F8: using guessed type int dword_5443F8;
// 5443FC: using guessed type int dword_5443FC;
// 544CD8: using guessed type _DWORD g_RenderState[9];
