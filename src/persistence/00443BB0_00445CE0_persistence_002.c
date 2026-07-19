/* Generated from src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "persistence_internal.h"
#include "persistence_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00443BB0) --------------------------------------------------------
BOOL  MapTile_HasHiddenTreasure(int tileRow, int tileColumn)
{
  int tileId; // eax

  tileId = *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * tileRow + TILE_TERRAIN_RECORD_STRIDE * tileColumn);
  return tileId == 755 || tileId == 752;
}
// 5202E4: using guessed type int gameData;

//----- (00443C20) --------------------------------------------------------
signed int  Treasure_TryDigHere(
        int a1,
        char a2,
        DWORD a3,
        char a4,
        char *a5,
        double a6)
{
  char v6; // bl
  int unitStackIndex; // edx
  __int16 *stackTileRecord; // ebp
  int v9; // ecx
  int v11; // ecx
  _BYTE *scriptedEventData; // ecx
  _DWORD *outcomeRecord; // ecx
  unsigned __int16 *tileWordPtr; // edx
  unsigned __int16 tileValue; // ax
  DWORD *v16; // ecx
  void *outcomeTablePtr; // eax
  int digOutcome; // eax
  _BYTE mission17EventBuffer[24]; // [esp+0h] [ebp-40h] BYREF
  _BYTE mission7EventBuffer[40]; // [esp+18h] [ebp-28h] BYREF

  Debug_Log(a1, a2, a3, (int)(intptr_t)aTreasure_dighe, a1);
  v6 = gameData;
  stackTileRecord = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * unitStackIndex + gameData + UNIT_STACK_TABLE_OFFSET);
  if ( !MapTile_HasHiddenTreasure(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitStackIndex + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitStackIndex + 147176))
    || !UnitStack_HasBuilder(v9) )
  {
    return 0;
  }
  if ( ACTIVE_MISSION_INDEX == 7
    && (*stackTileRecord == 55 && stackTileRecord[1] == 45 || *stackTileRecord == 50 && stackTileRecord[1] == 27 || *stackTileRecord == 35 && stackTileRecord[1] == 63 || *stackTileRecord == 14 && stackTileRecord[1] == 68) )
  {
    qmemcpy(mission7EventBuffer, &g_Mission7ScriptedTreasureEventData, 0x18u);
    a5 = (char *)&g_Mission7ScriptedTreasureEventData + 24;
    scriptedEventData = mission7EventBuffer;
  }
  else if ( ACTIVE_MISSION_INDEX == 17
         && (*stackTileRecord == 50 && stackTileRecord[1] == 34 || *stackTileRecord == 51 && stackTileRecord[1] == 73
                                      || *stackTileRecord == 77 && stackTileRecord[1] == 34
                                      || *stackTileRecord == 24 && stackTileRecord[1] == 49) )
  {
    qmemcpy(mission17EventBuffer, &g_Mission17ScriptedTreasureEventData, sizeof(mission17EventBuffer));
    a5 = (char *)&g_Mission17ScriptedTreasureEventData + 24;
    scriptedEventData = mission17EventBuffer;
  }
  else
  {
    if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackTileRecord + 4) + gameData + 140051) )
      outcomeTablePtr = &g_TreasureDigOutcomeTable_Human;
    else
      outcomeTablePtr = &g_TreasureDigOutcomeTable_AI;
    digOutcome = Temple_Random((int)(intptr_t)outcomeTablePtr, v11, v6, (DWORD)(intptr_t)stackTileRecord, a4);
    Debug_Log(digOutcome, v6, (DWORD)(intptr_t)stackTileRecord, (int)(intptr_t)aTreasure_dig_0, digOutcome);
  }
  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackTileRecord + 4) + 140051) )
  {
    Win_PlayModeChangeFrameTransition((int)(intptr_t)aKop_bud, 1, (int)(intptr_t)scriptedEventData, v6, (DWORD)(intptr_t)stackTileRecord, (char)(intptr_t)a5);
    Temple_ShowOutcomePopup(outcomeRecord[(unsigned __int8)g_LanguageIndex + 3], outcomeRecord[2], (int)(intptr_t)outcomeRecord, *outcomeRecord != 15, (DWORD)(intptr_t)stackTileRecord);
  }
  tileWordPtr = (unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * *stackTileRecord + gameData + TILE_TERRAIN_RECORD_STRIDE * stackTileRecord[1]);
  tileValue = *tileWordPtr;
  if ( *tileWordPtr >= 0x2F0u )
  {
    if ( tileValue > 0x2F0u )
    {
      if ( tileValue == 755 )
        *tileWordPtr = 4;
    }
    else
    {
      *tileWordPtr = 0;
    }
  }
  Rules_RetractTreasureFact(*stackTileRecord, stackTileRecord[1], a6);
  Temple_ProcessGift(*v16, (int)(intptr_t)stackTileRecord, stackTileRecord[1], *stackTileRecord, a6);
  return 1;
}
// 443C53: variable 'v7' is possibly undefined
// 443C85: variable 'v9' is possibly undefined
// 443CF5: variable 'v12' is possibly undefined
// 443D10: variable 'v13' is possibly undefined
// 443D88: variable 'v16' is possibly undefined
// 443E76: variable 'v11' is possibly undefined
// 511130: using guessed type char byte_511130;
// 5202E4: using guessed type int gameData;

//----- (00443EB0) --------------------------------------------------------
signed int  UnitStack_TryHide(int unitStackIndex, unsigned __int16 neighborStackIndex, DWORD a3, double a4)
{
  __int16 *stackRecord; // esi
  int v6; // ecx
  int rowDelta; // edx
  int v8; // edx
  int neighborStackByteOffset; // eax
  int v10; // ecx
  unsigned int buildingIndex; // eax
  int buildingByteOffset; // eax
  int buildingRecord; // ecx
  int v14; // ecx
  int playerDataOffset; // eax
  int lowRankMessageTable[3]; // [esp+0h] [ebp-3Ch]
  int noSpotMessageTable[3]; // [esp+Ch] [ebp-30h] BYREF
  int spotBlocked; // [esp+18h] [ebp-24h] BYREF
  int columnDeltaSquared; // [esp+1Ch] [ebp-20h]
  int columnDelta; // [esp+20h] [ebp-1Ch]

  stackRecord = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * unitStackIndex);
  if ( UnitStack_GetMinCurrentActionPoints((intptr_t)stackRecord) < 0 || *((_BYTE *)stackRecord + 720) || !UnitStack_HasNormalCombatUnits((intptr_t)stackRecord) )
    return 0;
  if ( UnitStack_GetMaxOrderTier((intptr_t)stackRecord) < 2 )
  {
    if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4) + gameData + 140051) )
    {
      lowRankMessageTable[0] = (int)(intptr_t)g_UnitHideFailedLowRankText[0];
      lowRankMessageTable[1] = (int)(intptr_t)g_UnitHideFailedLowRankText[1];
      lowRankMessageTable[2] = (int)(intptr_t)g_UnitHideFailedLowRankText[2];
      Audio_PlaySoundEffectByName(aWrong_0, 64);
      UI_ShowInfoWindow(lowRankMessageTable[(unsigned __int8)g_LanguageIndex], 1u, v6, a3, (int)(intptr_t)noSpotMessageTable, (int)(intptr_t)&g_UnitHideFailedLowRankText[3]);
      return 0;
    }
    return 0;
  }
  spotBlocked = 0;
  columnDelta = -8;
  do
  {
    rowDelta = -8;
    columnDeltaSquared = columnDelta * columnDelta;
    while ( 1 )
    {
      if ( Math_CeilSqrt(columnDeltaSquared + rowDelta * rowDelta) <= 8 )
      {
        neighborStackIndex = *(_WORD *)(uintptr_t)(gameData + TILE_ROW_STRIDE * (v8 + *stackRecord) + 2 * (columnDelta + stackRecord[1]) + TILE_MAP_OFFSET);
        if ( neighborStackIndex != 0xFFFF )
        {
          if ( neighborStackIndex <= 0x1F4u )
          {
            neighborStackByteOffset = UNIT_STACK_STRIDE * neighborStackIndex;
            if ( (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + neighborStackByteOffset + 6) <= 0x28
              && *(_BYTE *)(uintptr_t)(gameData + neighborStackByteOffset + 147178) != *((_BYTE *)stackRecord + 4) )
            {
              break;
            }
          }
          buildingIndex = neighborStackIndex - TILE_OCCUPANT_BUILDING_INDEX_BASE;
          if ( buildingIndex <= 0x64 )
          {
            buildingByteOffset = BUILDING_RECORD_SIZE * buildingIndex;
            LOBYTE(neighborStackIndex) = gameData;
            buildingRecord = buildingByteOffset + gameData + BUILDING_TABLE_OFFSET;
            if ( (unsigned int)*(char *)(uintptr_t)(buildingRecord + 4) < 4
              && *(__int16 *)(uintptr_t)(buildingRecord + 16) != -1
              && *(_BYTE *)(uintptr_t)(gameData + buildingByteOffset + 509676) != *((_BYTE *)stackRecord + 4) )
            {
              break;
            }
          }
        }
      }
      rowDelta = v8 + 1;
      if ( rowDelta >= 8 )
        goto LABEL_16;
    }
    spotBlocked = 1;
LABEL_16:
    ++columnDelta;
  }
  while ( columnDelta < 8 );
  if ( spotBlocked )
  {
    if ( !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4) + gameData + 140051) )
      return 0;
    noSpotMessageTable[0] = (int)(intptr_t)g_UnitHideFailedNoSpotText[0];
    noSpotMessageTable[1] = (int)(intptr_t)g_UnitHideFailedNoSpotText[1];
    noSpotMessageTable[2] = (int)(intptr_t)g_UnitHideFailedNoSpotText[2];
    Audio_PlaySoundEffectByName(aWrong_1, 64);
    UI_ShowInfoWindow(noSpotMessageTable[(unsigned __int8)g_LanguageIndex], 0, v10, 0, (int)(intptr_t)&spotBlocked, (int)(intptr_t)&g_UnitHideFailedNoSpotText[3]);
    return 0;
  }
  else
  {
    UnitStack_ClearRemainingActionPoints(stackRecord, 0, a4);
    playerDataOffset = PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4);
    *((_BYTE *)stackRecord + 720) = 1;
    if ( *(_DWORD *)(uintptr_t)(gameData + playerDataOffset + 140051) )
      Win_PlayModeChangeFrameTransition(aUkrycie, 1, v14, neighborStackIndex, 0);
    WorldMap_RedrawTileIfVisible(*stackRecord, stackRecord[1]);
    return 1;
  }
}
// 443FDF: simplified comparisons for 'eax.4': <0 || >=1F5 became >=1F5u
// 444003: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 4440B6: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 4440D7: simplified comparisons for 'edi.4': <0 || >=4 became >=4u
// 443F5C: variable 'v6' is possibly undefined
// 443FAA: variable 'v8' is possibly undefined
// 44408D: variable 'v10' is possibly undefined
// 44412B: variable 'v14' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 517DE8: using guessed type char *off_517DE8[6];
// 517DF4: using guessed type char *off_517DF4[3];
// 5202E4: using guessed type int gameData;

//----- (00444150) --------------------------------------------------------
signed int  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(unsigned int attackingStackIndex, double a2)
{
  __int16 *stack; // ebx
  int result; // [esp+8h] [ebp-2Ch]
  int neighbor_index;

  if ( attackingStackIndex > 0x1F4 )
    return 0;
  stack = (__int16 *)(uintptr_t)UNIT_STACK(attackingStackIndex);
  if ( (unsigned int)stack[3] > 0x28 )
    return 0;

  result = 0;
  if ( UnitStack_GetMaxOrderTier((intptr_t)stack) >= 3 )
  {
    int vision_radius = UnitStack_GetVisionRadius((int)(intptr_t)stack);
    int center_row = *stack;
    int center_column = stack[1];
    int row;

    for ( row = center_row - vision_radius; row < center_row + vision_radius; ++row )
    {
      int column;

      if ( row < 0 || row >= MAP_WIDTH_TILES )
        continue;
      for ( column = center_column - vision_radius; column < center_column + vision_radius; ++column )
      {
        unsigned int hidden_stack_index;
        int distance;

        if ( column < 0 || column >= MAP_HEIGHT_TILES )
          continue;
        distance = Math_CeilSqrt(
                     (column - center_column) * (column - center_column)
                   + (row - center_row) * (row - center_row));
        if ( distance > vision_radius )
          continue;
        hidden_stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(row, column));
        if ( hidden_stack_index <= 0x1F4 )
        {
          __int16 *hidden_stack = (__int16 *)(uintptr_t)UNIT_STACK(hidden_stack_index);
          if ( (unsigned int)hidden_stack[3] <= 0x28
            && UNIT_STACK_OWNER_INDEX((int)(intptr_t)hidden_stack) != UNIT_STACK_OWNER_INDEX((int)(intptr_t)stack)
            && *((_BYTE *)hidden_stack + 720) )
          {
            *((_BYTE *)hidden_stack + 720) = 0;
            WorldMap_RedrawViewport(1);
          }
        }
      }
    }
  }

  for ( neighbor_index = 0; neighbor_index < 24; neighbor_index += 2 )
  {
    int row = Map_NeighborDX[neighbor_index] + *stack;
    int column = Map_NeighborDY[neighbor_index] + stack[1];
    unsigned int adjacent_stack_index;

    if ( row < 0 || row >= MAP_WIDTH_TILES || column < 0 || column >= MAP_HEIGHT_TILES )
      continue;
    adjacent_stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(row, column));
    if ( adjacent_stack_index <= 0x1F4 )
    {
      __int16 *adjacent_stack = (__int16 *)(uintptr_t)UNIT_STACK(adjacent_stack_index);
      if ( (unsigned int)adjacent_stack[3] <= 0x28
        && UNIT_STACK_OWNER_INDEX((int)(intptr_t)adjacent_stack) != UNIT_STACK_OWNER_INDEX((int)(intptr_t)stack)
        && *((_BYTE *)adjacent_stack + 720) )
      {
        Unit_Attack(adjacent_stack_index, attackingStackIndex, (char)(intptr_t)stack, 1u, a2);
        UnitStack_ClearRemainingActionPoints(stack, 1u, a2);
        *((_BYTE *)adjacent_stack + 720) = 0;
        result = 1;
        WorldMap_RedrawViewport(1);
      }
    }
    if ( attackingStackIndex > 0x1F4 )
      break;
    if ( (unsigned int)*(__int16 *)(uintptr_t)(UNIT_STACK(attackingStackIndex) + 6) > 0x28 )
      break;
  }
  return result;
}
// 444212: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 44425E: simplified comparisons for '%var_28.4': <0 || >=1F5 became >=1F5u
// 44427C: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 44437B: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 444283: variable 'j' is possibly undefined
// 444342: variable 'v12' is possibly undefined
// 4443AC: variable 'v11' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (004443C0) --------------------------------------------------------
int  SaveSlot_FormatDataFilePath(int slotIndex, char *outPath)
{
  return sprintf_(outPath, "save\\%d.dat", slotIndex);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443D0) --------------------------------------------------------
int  SaveSlot_FormatFactsFilePath(int slotIndex, char *outPath)
{
  return sprintf_(outPath, "save\\%d.fac", slotIndex);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443E0) --------------------------------------------------------
signed int  saveGame(int slotIndex, DWORD headerBuffer, double a3)
{
  int v5; // ecx
  int fileHandle; // esi
  int v7; // ecx
  int v8 CLASH95_UNUSED; // edx
  CHAR filePathBuffer[120]; // [esp+0h] [ebp-78h] BYREF

  SaveSlot_FormatDataFilePath(slotIndex, filePathBuffer);
  PLAYER_CAMERA_LEFT(VIEWED_PLAYER_INDEX) = MAP_VIEW_LEFT;
  PLAYER_CAMERA_TOP(VIEWED_PLAYER_INDEX) = MAP_VIEW_TOP;
  fileHandle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aWb_4, v5, headerBuffer);
  fwrite_((const void *)(uintptr_t)headerBuffer, 16, fileHandle, 1);
  fwrite_((const void *)(uintptr_t)gameData, GAMEDATA_SAVE_IMAGE_BYTES, fileHandle, 1);
  fclose_(v7);
  SaveSlot_FormatFactsFilePath(slotIndex, filePathBuffer);
  return Rules_SaveFactsToFile(filePathBuffer, 2, 0, a3);
}
// 44443B: variable 'v5' is possibly undefined
// 44446A: variable 'v7' is possibly undefined
// 444473: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00444490) --------------------------------------------------------
signed int  SaveSlot_LoadGame(int slotIndex, DWORD a2, double a3)
{
  int file_handle; // eax
  int trace_load_save; // eax
  int stack_index; // ecx
  int slot_index; // edx
  int building_index; // edx
  int unit_record_index; // ecx
  int unit_record; // edx
  CHAR filePathBuffer[120]; // [esp+0h] [ebp-78h] BYREF

  trace_load_save = 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-enter\n");
  SaveSlot_FormatDataFilePath(slotIndex, filePathBuffer);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-path %s\n", filePathBuffer);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_5, 0, a2);
  if ( file_handle )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-file-opened handle=%d\n", file_handle);
    IO_SeekStreamGuarded(file_handle, 16, 1u, slotIndex);
    fread_((void *)(uintptr_t)(unsigned int)gameData, GAMEDATA_SAVE_IMAGE_BYTES, file_handle, 1);
    fclose_(file_handle);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-read\n");
    g_CurrentPlayerIndex = TURN_OWNER_PLAYER_INDEX;
    Rules_ResetEngineOnLoad();
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-fact-reset\n");
    for ( stack_index = 0; stack_index < 500; ++stack_index )
    {
      if ( (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28 )
      {
        if ( trace_load_save )
          fprintf(
            stderr,
            "[menu-probe] load-save-link-army stack=%d type=%d x=%d y=%d owner=%u\n",
            stack_index,
            *(unsigned __int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147180),
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
            *(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147178));
        UnitStack_LinkArmyFact((__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index), 1, a2);
      }
      for ( slot_index = 0; slot_index < 10; ++slot_index )
      {
        *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 31 * slot_index + 147198) = 0;
      }
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-army-loop\n");
    for ( building_index = 0; building_index < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET); ++building_index )
    {
      for ( slot_index = 0; slot_index < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET); ++slot_index )
      {
        *(_DWORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * slot_index + TILE_TERRAIN_ROW_STRIDE * building_index + gameData + 6) = 0;
        *(_DWORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * slot_index + TILE_TERRAIN_ROW_STRIDE * building_index + gameData + 10) = 0;
      }
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-building-loop\n");
    for ( unit_record_index = 0; unit_record_index < 100; ++unit_record_index )
    {
      unit_record = UNIT_RECORD(unit_record_index);
      if ( (unsigned int)*(char *)(uintptr_t)(unit_record + 4) < 4 && *(__int16 *)(uintptr_t)(unit_record + 16) != -1 )
        Rules_AssertCastleFact((unsigned __int8 *)(uintptr_t)unit_record, unit_record_index);
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-castle-loop\n");
    SaveSlot_FormatFactsFilePath(slotIndex, filePathBuffer);
    Rules_LoadFactsFromFile(filePathBuffer, 0, a2, a3);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-sidecar-write\n");
    Render_CreateSprite();
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-render-create\n");
    UI_ClearTileHighlight(0);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-ui-clear\n");
    MiniMap_CreateSurface(a2);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-minimap\n");
    return 1;
  }
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-open-failed\n");
  return file_handle;
}
// 4445A5: conditional instruction was optimized away because ecx.4<1F4u
// 44466F: conditional instruction was optimized away because ecx.4<64u
// 444529: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 444639: simplified comparisons for 'eax.4': <0 || >=4 became >=4u
// 4444A8: variable 'v5' is possibly undefined
// 4444E4: variable 'v8' is possibly undefined
// 44451D: variable 'v9' is possibly undefined
// 444662: variable 'v15' is possibly undefined
// 44467E: variable 'v17' is possibly undefined
// 444688: variable 'v18' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004446E0) --------------------------------------------------------
char  SaveSlot_LoadLabelOrPlaceholder(int slotIndex, char *outLabelBuffer, DWORD a3)
{
  int file_handle; // eax
  char result; // al
  char *placeholderChars; // esi
  CHAR filePathBuffer[108]; // [esp+0h] [ebp-6Ch] BYREF

  snprintf(filePathBuffer, sizeof(filePathBuffer), "save\\%d.dat", slotIndex);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_7, 0, a3);
  if ( file_handle )
  {
    fread_(outLabelBuffer, 1, file_handle, 16);
    outLabelBuffer[16] = 0;
    return fclose_(file_handle);
  }
  else
  {
    placeholderChars = asc_4F94BB;
    do
    {
      result = *placeholderChars;
      *outLabelBuffer = *placeholderChars;
      if ( !result )
        break;
      result = placeholderChars[1];
      placeholderChars += 2;
      outLabelBuffer[1] = result;
      outLabelBuffer += 2;
    }
    while ( result );
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00444750) --------------------------------------------------------
int  SaveSlot_HasDataFile(int slotIndex, DWORD a2)
{
  int file_handle; // eax
  int result; // eax
  CHAR filePathBuffer[104]; // [esp-68h] [ebp-68h] BYREF

  snprintf(filePathBuffer, sizeof(filePathBuffer), "save\\%d.dat", slotIndex);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_8, 0, a2);
  result = file_handle;
  if ( file_handle )
  {
    fclose_(file_handle);
    return 1;
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00444780) --------------------------------------------------------
int  SaveSlotDialog_RepaintRow(int a1)
{
  void *previousRenderDevice; // ebp
  char *editNameChars; // esi
  char *labelCursor; // edi
  char nameChar; // al
  char nameNextChar; // al
  int rowBottomY; // edi
  unsigned __int16 rowTopY; // si
  int rowRenderIndex; // eax
  int result; // eax
  char labelBuffer[20]; // [esp+0h] [ebp-30h] BYREF
  int rowIndex; // [esp+14h] [ebp-1Ch]

  rowIndex = a1;
  previousRenderDevice = g_RenderDevice;
  if ( g_SaveSlotDialogIsSaveMode && a1 == g_SaveSlotDialogSelectedRow )
  {
    editNameChars = g_SaveSlotNameEditBuffer;
    labelCursor = labelBuffer;
    do
    {
      nameChar = *editNameChars;
      *labelCursor = *editNameChars;
      if ( !nameChar )
        break;
      nameNextChar = editNameChars[1];
      editNameChars += 2;
      labelCursor[1] = nameNextChar;
      labelCursor += 2;
    }
    while ( nameNextChar );
  }
  else
  {
    SaveSlot_LoadLabelOrPlaceholder(rowIndex, labelBuffer, (DWORD)(intptr_t)g_RenderDevice);
  }
  g_RenderDevice = &g_MainRenderDevice;
  rowBottomY = (unsigned __int16)(22 * rowIndex + 157);
  rowTopY = 22 * rowIndex + 137;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, rowTopY, rowBottomY);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, rowTopY, 244, 0x1A4u, rowBottomY, 0xF4u, rowTopY);
  if ( rowIndex == g_SaveSlotDialogSelectedRow )
    rowRenderIndex = 18;
  else
    rowRenderIndex = 21;
  Render_ReleaseSurface(rowRenderIndex, (DWORD)(intptr_t)previousRenderDevice);
  if ( g_SaveSlotDialogIsSaveMode )
    UI_SetTextCursorPosition(g_TextInputCaretPos);
  UI_DrawTextFmt(rowBottomY, 244, 410, 22 * rowIndex + 137, 3, (int)(intptr_t)labelBuffer);
  UI_SetTextCursorPosition(-1);
  result = Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = previousRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D24: using guessed type int dword_543D24;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00444920) --------------------------------------------------------
int  SaveSlotDialog_HandleCancel(int result, int delay)
{
  if ( result )
    result = UIWidget_PlayPressedReleaseAnimationWithDelay(result, delay);
  g_SaveSlotDialogResult = -1;
  g_SaveSlotDialogDone = 1;
  return result;
}
// 543D14: using guessed type int dword_543D14;
// 543D20: using guessed type int dword_543D20;

//----- (00444950) --------------------------------------------------------
signed int  SaveSlotDialog_HandleConfirm(int widgetHandle, int delay, DWORD a3, double a4)
{
  signed int result; // eax
  void *previousRenderDevice; // ecx

  if ( widgetHandle )
    UIWidget_PlayPressedReleaseAnimationWithDelay(widgetHandle, delay);
  if ( g_SaveSlotDialogIsSaveMode && g_SaveSlotDialogSelectedRow != -1 )
  {
    result = saveGame(g_SaveSlotDialogSelectedRow, (DWORD)(intptr_t)g_SaveSlotNameEditBuffer, a4);
    g_SaveSlotDialogDone = 1;
    goto LABEL_6;
  }
  result = SaveSlot_HasDataFile(g_SaveSlotDialogSelectedRow, a3);
  if ( !result )
  {
LABEL_6:
    g_RenderDevice = previousRenderDevice;
    return result;
  }
  result = g_SaveSlotDialogSelectedRow;
  g_SaveSlotDialogResult = g_SaveSlotDialogSelectedRow;
  g_SaveSlotDialogDone = 1;
  g_RenderDevice = previousRenderDevice;
  return result;
}
// 444981: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 543D14: using guessed type int dword_543D14;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D20: using guessed type int dword_543D20;

//----- (00444D50) --------------------------------------------------------
int  SaveSlotDialog_Run(int a1, char a2, DWORD a3, double a4)
{
  _DWORD *spriteSet; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int SpriteForChar; // eax
  int v10; // ecx
  int mainDeviceSprite; // eax
  int i; // edx
  int v13; // eax
  int v14; // ebx
  int v15; // edx
  int v16; // eax
  int v17; // ebp
  unsigned int hoveredRow; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  const char *caretCharPtr; // edi
  unsigned int v27; // kr0C_4
  int v28; // edx
  int v29; // ecx
  int v30; // ecx
  unsigned int poppedKey; // eax
  char *nameChars; // esi
  char *nameCursor; // edi
  char nameChar; // al
  char nameNextChar; // al
  int caretPos; // edx
  int v37; // edx
  _DWORD v38[40]; // [esp+2Ch] [ebp-E0h] BYREF
  char v39[20]; // [esp+CCh] [ebp-40h] BYREF
  _DWORD *dialogSpriteSet; // [esp+E0h] [ebp-2Ch] BYREF
  int savedResourceHandle; // [esp+E4h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+E8h] [ebp-24h]
  int previousResourceHandleA; // [esp+ECh] [ebp-20h]
  char typedChar; // [esp+F0h] [ebp-1Ch]

  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a1, a2, a3);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, a2);
  dialogSpriteSet = spriteSet;
  previousResourceHandleA = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v6, 0, a3, (int)(intptr_t)aSetrhS08x_22);
  g_SaveSlotDialogIsSaveMode = v7;
  g_TextInputCaretPos = 0;
  g_SaveSlotDialogSelectedRow = -1;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, v8);
  g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)dialogSpriteSet, g_SaveSlotDialogIsSaveMode != 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    51,
    SpriteForChar,
    v10,
    v10,
    v10,
    v10,
    1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  mainDeviceSprite = DLX_GetSpriteForChar((int)(intptr_t)dialogSpriteSet, g_SaveSlotDialogIsSaveMode != 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    51,
    mainDeviceSprite,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  for ( i = 0; i < 10; SaveSlotDialog_RepaintRow(i) )
    ;
  qmemcpy(v38, &g_SaveSlotDialogWidgetTemplateBlob, 0x9Fu);
  v38[3] = &dialogSpriteSet;
  *(_DWORD *)((char *)&v38[16] + 1) = &dialogSpriteSet;
  if ( g_SaveSlotDialogIsSaveMode )
    v13 = -1;
  else
    v13 = 4;
  LOBYTE(v14) = g_SaveSlotDialogIsSaveMode;
  *(_DWORD *)((char *)&v38[17] + 1) = v13;
  *(_DWORD *)((char *)&v38[18] + 1) = (g_SaveSlotDialogIsSaveMode != 0) + 2;
  g_RenderDevice = &g_MainRenderDevice;
  UIWidgetTable_InitDrawStates(v38);
  g_SaveSlotDialogDone = 0;
  Render_Present((int)(intptr_t)g_RenderState);
  v16 = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, v15);
  v17 = g_SaveSlotDialogDone;
  savedResourceHandle = v16;
  while ( !g_SaveSlotDialogDone )
  {
    if ( g_SaveSlotDialogIsSaveMode && g_SaveSlotDialogSelectedRow != -1 )
    {
      if ( Input_IsKeyPressed(203) )
      {
        LOBYTE(v14) = g_TextInputCaretPos;
        if ( g_TextInputCaretPos )
        {
          --g_TextInputCaretPos;
          SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          Input_ClearKey(203, v23);
        }
      }
      if ( Input_IsKeyPressed(205) && strlen(g_SaveSlotNameEditBuffer) > g_TextInputCaretPos )
      {
        v17 = ++g_TextInputCaretPos;
        SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
        Input_ClearKey(205, v24);
      }
      if ( Input_IsKeyPressed(211) )
      {
        LOBYTE(v14) = strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1]) + 1;
        memmove_(
          &g_SaveSlotNameEditBuffer[g_TextInputCaretPos],
          &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1],
          strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1]) + 1);
        SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
        Input_ClearKey(211, v25);
      }
      if ( Input_IsKeyPressed(14) )
      {
        LOBYTE(v14) = g_TextInputCaretPos;
        if ( g_TextInputCaretPos )
        {
          caretCharPtr = &g_SaveSlotNameEditBuffer[g_TextInputCaretPos--];
          v27 = strlen(caretCharPtr) + 1;
          LOBYTE(v14) = v27;
          memmove_(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos], &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1], v27);
          SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          Input_ClearKey(14, v28);
        }
      }
      if ( Input_IsKeyPressed(28) )
        SaveSlotDialog_HandleConfirm(0, v29, v17, a4);
      if ( Input_IsKeyPressed(1) )
        SaveSlotDialog_HandleCancel(0, v30);
      poppedKey = Input_PopKey();
      v17 = poppedKey;
      if ( poppedKey != -1 )
      {
        typedChar = Input_KeyToChar(poppedKey);
        if ( typedChar )
        {
          if ( strlen(g_SaveSlotNameEditBuffer) < 0x10 )
          {
            if ( g_SaveSlotDialogIsSaveMode )
            {
              nameChars = g_SaveSlotNameEditBuffer;
              nameCursor = v39;
              do
              {
                nameChar = *nameChars;
                *nameCursor = *nameChars;
                if ( !nameChar )
                  break;
                nameNextChar = nameChars[1];
                nameChars += 2;
                nameCursor[1] = nameNextChar;
                nameCursor += 2;
              }
              while ( nameNextChar );
            }
            else
            {
              SaveSlot_LoadLabelOrPlaceholder(g_SaveSlotDialogSelectedRow, v39, v17);
            }
            Render_ReleaseSurface(21, v17);
            if ( (unsigned __int16)Render_LoadResourceSprite_v3(v39) < 0x97u )
            {
              LOBYTE(v14) = strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos]) + 1;
              memmove_(
                &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1],
                &g_SaveSlotNameEditBuffer[g_TextInputCaretPos],
                strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos]) + 1);
              caretPos = g_TextInputCaretPos;
              g_SaveSlotNameEditBuffer[g_TextInputCaretPos] = typedChar;
              g_TextInputCaretPos = caretPos + 1;
              SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
              Input_ClearKey(v17, v37);
            }
          }
        }
      }
    }
    DD_Pump((int)(intptr_t)g_RenderState, v14);
    if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
    {
      if ( g_MouseCursorRawX >> g_CursorCoordShift >= 244 && g_MouseCursorRawX >> g_CursorCoordShift <= 410 )
      {
        hoveredRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 142) / 22;
        if ( hoveredRow <= 9 )
        {
          v14 = g_SaveSlotDialogSelectedRow;
          if ( hoveredRow != g_SaveSlotDialogSelectedRow )
          {
            g_SaveSlotDialogSelectedRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 142) / 22;
            g_TextInputCaretPos = 0;
            if ( v14 != -1 )
              SaveSlotDialog_RepaintRow(v14);
            if ( g_SaveSlotDialogIsSaveMode )
            {
              SaveSlot_LoadLabelOrPlaceholder(g_SaveSlotDialogSelectedRow, g_SaveSlotNameEditBuffer, v17);
              if ( !strcmp_(v19, asc_4F94C2) )
                g_SaveSlotNameEditBuffer[0] = 0;
            }
            SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          }
          if ( RenderState_IsCursorFlipStillActive((int)(intptr_t)g_RenderState) )
            SaveSlotDialog_HandleConfirm(0, v20, v17, a4);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(v38, v17);
  }
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedResourceHandle);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Debug_Log(v21, v14, (DWORD)(intptr_t)g_RenderHook, (int)(intptr_t)aUnsetrh08x_22);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandleA);
  DLXSpriteSet_ReleaseAndClear((int *)&dialogSpriteSet);
  return g_SaveSlotDialogResult;
}
// 444FB0: simplified comparisons for 'eax.4': <0 || >=A became >=Au
// 444DC0: variable 'v6' is possibly undefined
// 444DCD: variable 'v7' is possibly undefined
// 444DF3: variable 'v8' is possibly undefined
// 444E47: variable 'v10' is possibly undefined
// 444EA3: variable 'i' is possibly undefined
// 444F23: variable 'v15' is possibly undefined
// 445006: variable 'v19' is possibly undefined
// 445031: variable 'v20' is possibly undefined
// 445031: variable 'a4' is possibly undefined
// 445073: variable 'v21' is possibly undefined
// 44510E: variable 'v23' is possibly undefined
// 445152: variable 'v24' is possibly undefined
// 4451AD: variable 'v25' is possibly undefined
// 445215: variable 'v28' is possibly undefined
// 44522A: variable 'v29' is possibly undefined
// 44523F: variable 'v30' is possibly undefined
// 445342: variable 'v37' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D14: using guessed type int dword_543D14;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D20: using guessed type int dword_543D20;
// 543D24: using guessed type int dword_543D24;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00445360) --------------------------------------------------------
int  UI_ShowInfoWindow(
        const char *message,
        unsigned int windowStyle,
        int a3,
        DWORD a4,
        int windowLeft,
        int windowTop)
{
  DWORD deviceVtable; // ebp
  int v8; // ecx
  int v9 CLASH95_UNUSED; // ecx
  int v10 CLASH95_UNUSED; // ecx
  int v11 CLASH95_UNUSED; // ecx
  _DWORD *templeSprites; // eax
  int v13 CLASH95_UNUSED; // edx
  int v14 CLASH95_UNUSED; // ecx
  int contentWidth; // eax
  _DWORD *infoBackdrop; // eax
  int headerSprite; // eax
  int footerSprite; // eax
  _DWORD *parchmentSprites; // eax
  int v20; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  _DWORD *parchmentSpritesSmall; // eax
  int v24; // ecx
  _DWORD *scrollBackdrop; // eax
  int scrollSprite; // eax
  _DWORD *finalSurface; // ebx
  int result; // eax
  _DWORD *scrollSpriteSet; // [esp+68h] [ebp-34h] BYREF
  int (*previousRenderHook)(); // [esp+6Ch] [ebp-30h]
  const char *messageText; // [esp+70h] [ebp-2Ch]
  _DWORD *backdropSurface; // [esp+74h] [ebp-28h]
  DWORD deviceVtableTmp; // [esp+78h] [ebp-24h]
  int SpriteHeight; // [esp+7Ch] [ebp-20h]
  int previousResourceHandle; // [esp+80h] [ebp-1Ch]
  int SpriteWidth; // [esp+84h] [ebp-18h]
  int info_header_height;
  int info_footer_width;
  int info_header_width;

  messageText = message;
  Debug_Log(a3, windowStyle, a4, (int)(intptr_t)aWindowmessageS);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, windowStyle, a4, (int)(intptr_t)aSetrhS08x_10);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  deviceVtable = 0;
  Render_ReleaseSurface(17, 0);
  scrollSpriteSet = 0;
  if ( windowStyle )
  {
    if ( windowStyle <= 1 )
    {
      parchmentSprites = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v8, windowStyle, 0);
      if ( parchmentSprites )
        parchmentSprites = DLXSpriteSet_Load(parchmentSprites, "pergamin.s32");
      scrollSpriteSet = parchmentSprites;
      windowTop = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)parchmentSprites, 3u)) / 2;
      windowLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 3u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 3u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 3u);
      Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v20, windowStyle, 0);
      if ( Surface )
        Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
      backdropSurface = Surface;
      Render_FillRect(
        0,
        Surface,
        (unsigned __int16)windowTop,
        (unsigned __int16)windowLeft,
        windowLeft + SpriteHeight - 1,
        windowTop + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &g_MainRenderDevice;
      SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 3);
      deviceVtableTmp = *((_DWORD *)g_RenderDevice + 46);
      deviceVtable = deviceVtableTmp;
      Compat_RenderDeviceDrawMenuSprite(windowTop, windowLeft, SpriteForChar, 1);
      UI_DrawTextFmt(windowLeft, windowLeft, windowLeft + SpriteHeight, windowTop + 18, 3, messageText);
    }
    else if ( windowStyle == 2 )
    {
      parchmentSpritesSmall = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v8, 2, 0);
      if ( parchmentSpritesSmall )
        parchmentSpritesSmall = DLXSpriteSet_Load(parchmentSpritesSmall, "pergamin.s32");
      scrollSpriteSet = parchmentSpritesSmall;
      windowTop = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)parchmentSpritesSmall, 2u)) / 2;
      windowLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 2u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 2u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 2u);
      scrollBackdrop = (_DWORD *)(uintptr_t)Mem_Alloc(188, v24, 2, 0);
      if ( scrollBackdrop )
        scrollBackdrop = Render_CreateSurface((int)(intptr_t)scrollBackdrop, SpriteHeight, SpriteWidth);
      backdropSurface = scrollBackdrop;
      Render_FillRect(
        0,
        scrollBackdrop,
        (unsigned __int16)windowTop,
        (unsigned __int16)windowLeft,
        windowLeft + SpriteHeight - 1,
        windowTop + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &g_MainRenderDevice;
      scrollSprite = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 2);
      deviceVtable = *((_DWORD *)g_RenderDevice + 46);
      Compat_RenderDeviceDrawMenuSprite(windowTop, windowLeft, scrollSprite, 1);
      UI_DrawTextFmt(windowLeft, windowLeft + 25, windowLeft + SpriteHeight - 25, windowTop + 25, 6, messageText);
    }
  }
  else
  {
    templeSprites = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v8, 0, 0);
    if ( templeSprites )
      templeSprites = DLXSpriteSet_Load(templeSprites, "temple.s32");
    windowTop = 150;
    scrollSpriteSet = templeSprites;
    info_footer_width = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)templeSprites, 0x17u);
    windowLeft = 0;
    info_header_width = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 0x16u);
    contentWidth = info_footer_width + 6;
    SpriteHeight = 640;
    if ( info_header_width > info_footer_width + 6 )
      contentWidth = info_header_width;
    SpriteWidth = contentWidth;
    infoBackdrop = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, 0x280u);
    if ( infoBackdrop )
      infoBackdrop = Render_CreateSurface((int)(intptr_t)infoBackdrop, SCREEN_WIDTH, SpriteWidth);
    backdropSurface = infoBackdrop;
    Render_FillRect(0, infoBackdrop, 150, 0, SCREEN_MAX_X, SpriteWidth + 149, 0, 0);
    g_RenderDevice = &g_MainRenderDevice;
    headerSprite = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 22);
    Compat_RenderDeviceDrawMenuSprite(150, 0, headerSprite, 1);
    info_header_height = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 0x16u);
    footerSprite = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 23);
    deviceVtable = *((_DWORD *)g_RenderDevice + 46);
    Compat_RenderDeviceDrawMenuSprite(156, info_header_height, footerSprite, 1);
    UI_DrawTextFmt(0, 70, 569, 210, 6, messageText);
  }
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  Render_Present((int)(intptr_t)g_RenderState);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) && !DD_IsLost((int)(intptr_t)g_RenderState) )
    DD_Pump((int)(intptr_t)g_RenderState, 0);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Render_Pump();
  Debug_Log((int)(intptr_t)g_RenderHook, 0, deviceVtable, (int)(intptr_t)aUnsetrh08x_10);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  if ( (uintptr_t)backdropSurface >> 32 )
    backdropSurface = 0;
  if ( backdropSurface )
    Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, windowLeft, windowTop);
  finalSurface = backdropSurface;
  result = Render_Present((int)(intptr_t)g_RenderState);
  if ( finalSurface )
    return RenderSurface_InvokeSlot0(finalSurface, 2);
  return result;
}
// 445457: variable 'v8' is possibly undefined
// 44541F: variable 'v9' is possibly undefined
// 44542E: variable 'v10' is possibly undefined
// 44543F: variable 'v11' is possibly undefined
// 44549A: variable 'v14' is possibly undefined
// 44561E: variable 'v20' is possibly undefined
// 445767: variable 'v24' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (004458E0) --------------------------------------------------------
int  WorldMap_NotifyPlagueOutbreak(int a1, const char *a2, DWORD a3)
{
  int buildingRecordOffset; // ecx
  int result; // eax
  int v6 CLASH95_UNUSED; // ecx
  int v7 CLASH95_UNUSED; // ecx
  _BYTE messageBuffer[256]; // [esp+0h] [ebp-120h] BYREF
  int noticeTextTable[8]; // [esp+100h] [ebp-20h] BYREF

  result = 0;
  noticeTextTable[6] = a1;
  buildingRecordOffset = 0;
  noticeTextTable[0] = (int)(intptr_t)g_PlagueOutbreakNoticeFmtText[0];
  noticeTextTable[1] = (int)(intptr_t)g_PlagueOutbreakNoticeFmtText[1];
  noticeTextTable[2] = (int)(intptr_t)g_PlagueOutbreakNoticeFmtText[2];
  do
  {
    result = buildingRecordOffset + gameData;
    if ( (*(_BYTE *)(uintptr_t)(buildingRecordOffset + gameData + 510109) & 7) == 5 )
    {
      result = *(unsigned __int8 *)(uintptr_t)(result + 509676);
      if ( result == g_CurrentPlayerIndex )
      {
        Diagnostics_TraceWorldMapActionEvent("plague_notice_match", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        Win_PlayModeChangeFrameTransition(aZaraza, 1, buildingRecordOffset, (char)(intptr_t)a2, a3);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_transition", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        a2 = (const char *)(uintptr_t)noticeTextTable[(unsigned __int8)g_LanguageIndex];
        sprintf_(messageBuffer, a2, gameData + buildingRecordOffset + BUILDING_TABLE_OFFSET + 5);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_before_info_window", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        result = UI_ShowInfoWindow((const char *)messageBuffer, 0, 0, a3, (int)(intptr_t)&noticeTextTable[3], (int)(intptr_t)&g_PlagueOutbreakNoticeFmtText[3]);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_info_window", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, result);
      }
    }
    buildingRecordOffset += BUILDING_RECORD_SIZE;
  }
  while ( buildingRecordOffset != 46700 );
  return result;
}
// 445949: variable 'v6' is possibly undefined
// 44596F: variable 'v7' is possibly undefined
// 445974: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 517EA0: using guessed type char *off_517EA0[12];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004459A0) --------------------------------------------------------
int  UI_ShowTechnologyLevelUpIfChanged(int a1, DWORD a2)
{
  int result; // eax
  int noticeTextTable[6]; // [esp+0h] [ebp-18h] BYREF

  noticeTextTable[0] = (int)(intptr_t)g_TechLevelUpNoticeText[0];
  noticeTextTable[1] = (int)(intptr_t)g_TechLevelUpNoticeText[1];
  noticeTextTable[2] = (int)(intptr_t)g_TechLevelUpNoticeText[2];
  if ( *(_BYTE *)(uintptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) != *(_BYTE *)(uintptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_LAST_SHOWN_TECH_LEVEL_OFFSET) )
  {
    Diagnostics_TraceWorldMapActionEvent("color_notice_before_info_window", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
    UI_ShowInfoWindow(noticeTextTable[(unsigned __int8)g_LanguageIndex], 0, a1, a2, (int)(intptr_t)&noticeTextTable[3], (int)(intptr_t)&g_TechLevelUpNoticeText[3]);
    Diagnostics_TraceWorldMapActionEvent("color_notice_after_info_window", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
  }
  result = PLAYER_DATA(g_CurrentPlayerIndex);
  *(_BYTE *)(uintptr_t)(result + PLAYER_LAST_SHOWN_TECH_LEVEL_OFFSET) = *(_BYTE *)(uintptr_t)(result + PLAYER_TECH_LEVEL_OFFSET);
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 517EAC: using guessed type char *off_517EAC[9];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00445A40) --------------------------------------------------------
int  UI_CheatEditRepaint(DWORD backdropSurface, int a2)
{
  unsigned __int16 v2; // dx
  unsigned __int16 v3; // cx
  char savedFirstChar; // [esp+0h] [ebp-10h]

  savedFirstChar = g_CheatEntryTextBuffer[0];
  strupr_(440, 200);
  g_CheatEntryTextBuffer[0] = savedFirstChar;
  RenderState_PumpIfRectInViewBounds(g_RenderState, v2, v3, 0x104u, 0x122u);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  Render_ReleaseSurface(22, backdropSurface);
  UI_SetTextCursorPosition(g_CheatEditCaretIndex);
  UI_DrawTextFmt(a2, 200, 440, 260, 3, (int)(intptr_t)g_CheatEntryTextBuffer);
  UI_SetTextCursorPosition(-1);
  return Render_Present((int)(intptr_t)g_RenderState);
}
// 445A7C: variable 'v2' is possibly undefined
// 445A7C: variable 'v3' is possibly undefined
// 47BBE3: using guessed type int __fastcall strupr_(_DWORD, _DWORD);
// 5202E0: using guessed type int dword_5202E0;
// 543D44: using guessed type int dword_543D44;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00445CE0) --------------------------------------------------------
char  Building_ShowConstructionFinishedDialog(int building, int a2, char spriteSetName, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  char *editDstCursor; // edi
  char *buildingNameChars; // esi
  char currentNameChar; // al
  char nextNameChar; // al
  char *editTextCursor; // edi
  _DWORD *spriteSetAlloc; // eax
  int v12; // ecx
  int SpriteWidth; // edx
  int v14; // ecx
  int panelWidthMax; // eax
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int spriteForChar23; // eax
  int completionText; // eax
  char v21; // bl
  int v22; // edx
  unsigned int textLength; // kr04_4
  int v24; // edx
  unsigned int deleteTailLen; // kr08_4
  int v26; // edx
  const char *backspaceSrc; // edi
  unsigned int backspaceTailLen; // kr0C_4
  int v29; // edx
  unsigned int poppedKeyRaw; // eax
  int poppedKey; // esi
  unsigned int currentTextLen; // kr10_4
  unsigned int insertTailLen; // kr14_4
  int newCaretIndex; // eax
  int v35; // edx
  int v36; // ecx
  char *copyBackSrc; // esi
  char *copyBackDst; // edi
  char result; // al
  int buildingCompleteAltText[3]; // [esp+38h] [ebp-4Ch]
  int buildingCompleteText[3]; // [esp+44h] [ebp-40h]
  _DWORD *spriteSet; // [esp+50h] [ebp-34h] BYREF
  int panelWidth; // [esp+54h] [ebp-30h]
  int (*previousRenderHook)(); // [esp+58h] [ebp-2Ch]
  int previousResourceHandle; // [esp+5Ch] [ebp-28h]
  int buildingRecord; // [esp+60h] [ebp-24h]
  int panelLeft; // [esp+64h] [ebp-20h]
  char typedChar; // [esp+68h] [ebp-1Ch]

  buildingRecord = building;
  Debug_Log(a2, spriteSetName, a4, (int)(intptr_t)aMessage_buildf);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v4, spriteSetName, a4, (int)(intptr_t)aSetrhS08x_11);
  buildingCompleteText[0] = (int)(intptr_t)g_BuildingCompleteNoticeText[0];
  buildingCompleteText[1] = (int)(intptr_t)g_BuildingCompleteNoticeText[1];
  buildingCompleteText[2] = (int)(intptr_t)g_BuildingCompleteNoticeText[2];
  buildingCompleteAltText[0] = (int)(intptr_t)g_BuildingCompleteNoticeTextAlt[0];
  buildingCompleteAltText[1] = (int)(intptr_t)g_BuildingCompleteNoticeTextAlt[1];
  buildingCompleteAltText[2] = (int)(intptr_t)g_BuildingCompleteNoticeTextAlt[2];
  editDstCursor = g_CheatEntryTextBuffer;
  buildingNameChars = (char *)(uintptr_t)(buildingRecord + 5);
  do
  {
    currentNameChar = *buildingNameChars;
    *editDstCursor = *buildingNameChars;
    if ( !currentNameChar )
      break;
    nextNameChar = buildingNameChars[1];
    buildingNameChars += 2;
    editDstCursor[1] = nextNameChar;
    editDstCursor += 2;
  }
  while ( nextNameChar );
  editTextCursor = g_CheatEntryTextBuffer;
  spriteSetAlloc = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v5, spriteSetName, a4);
  if ( spriteSetAlloc )
    spriteSetAlloc = DLXSpriteSet_Load(spriteSetAlloc, spriteSetName);
  spriteSet = spriteSetAlloc;
  Render_Pump();
  panelLeft = v12;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0x16u);
  panelWidthMax = v14 + 6;
  if ( (unsigned __int16)SpriteWidth > v14 + 6 )
    panelWidthMax = SpriteWidth;
  panelWidth = panelWidthMax;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v14, spriteSetName, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, panelWidth);
  backdropSurface = (DWORD)(intptr_t)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)panelLeft, 0, SCREEN_MAX_X, panelWidth + panelLeft - 1, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 22);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    panelLeft,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0x16u);
  spriteForChar23 = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 23);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    panelLeft + 6,
    spriteForChar23,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(17, backdropSurface);
  if ( *(_BYTE *)(uintptr_t)(buildingRecord + 4) == 2 )
    completionText = buildingCompleteText[(unsigned __int8)g_LanguageIndex];
  else
    completionText = buildingCompleteAltText[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt((int)(intptr_t)g_CheatEntryTextBuffer, 70, 569, panelLeft + 60, 6, completionText);
  v21 = -56;
  Render_FillRect(0, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)g_CheatEntryTextBuffer);
  Render_Present((int)(intptr_t)g_RenderState);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  g_DecisionDialogExitSignal = 0;
  while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) && !g_DecisionDialogExitSignal )
  {
    DD_Pump((int)(intptr_t)g_RenderState, v21);
    if ( Input_IsKeyPressed(203) && g_CheatEditCaretIndex )
    {
      --g_CheatEditCaretIndex;
      UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)editTextCursor);
      Input_ClearKey(203, v22);
    }
    if ( Input_IsKeyPressed(205) )
    {
      textLength = strlen(g_CheatEntryTextBuffer) + 1;
      editTextCursor = &g_CheatEntryTextBuffer[textLength];
      v21 = g_CheatEditCaretIndex;
      if ( textLength - 1 > g_CheatEditCaretIndex )
      {
        ++g_CheatEditCaretIndex;
        UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)editTextCursor);
        Input_ClearKey(205, v24);
      }
    }
    if ( Input_IsKeyPressed(211) )
    {
      deleteTailLen = strlen(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1]) + 1;
      editTextCursor = (char *)(uintptr_t)g_CheatEditCaretIndex;
      v21 = deleteTailLen;
      memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], deleteTailLen);
      UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)editTextCursor);
      Input_ClearKey(211, v26);
    }
    if ( Input_IsKeyPressed(14) && g_CheatEditCaretIndex )
    {
      backspaceSrc = &g_CheatEntryTextBuffer[g_CheatEditCaretIndex--];
      backspaceTailLen = strlen(backspaceSrc) + 1;
      editTextCursor = (char *)&backspaceSrc[backspaceTailLen];
      v21 = backspaceTailLen;
      memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], backspaceTailLen);
      UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)editTextCursor);
      Input_ClearKey(14, v29);
    }
    if ( Input_IsKeyPressed(28) )
      g_DecisionDialogExitSignal = 1;
    poppedKeyRaw = Input_PopKey();
    poppedKey = poppedKeyRaw;
    if ( poppedKeyRaw != -1 )
    {
      typedChar = Input_KeyToChar(poppedKeyRaw);
      if ( typedChar )
      {
        currentTextLen = strlen(g_CheatEntryTextBuffer) + 1;
        editTextCursor = &g_CheatEntryTextBuffer[currentTextLen];
        if ( currentTextLen - 1 < 0xA )
        {
          insertTailLen = strlen(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex]) + 1;
          editTextCursor = &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + insertTailLen];
          v21 = insertTailLen;
          memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex], insertTailLen);
          newCaretIndex = g_CheatEditCaretIndex + 1;
          *((_BYTE *)&g_CheatEditCaretIndex + newCaretIndex + 3) = typedChar;
          g_CheatEditCaretIndex = newCaretIndex;
          UI_CheatEditRepaint(backdropSurface, (int)(intptr_t)editTextCursor);
          Input_ClearKey(poppedKey, v35);
        }
      }
    }
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v36, (char)(intptr_t)g_RenderHook, backdropSurface, (int)(intptr_t)aUnsetrh08x_11);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)(uintptr_t)backdropSurface, 0, 0, 0, SCREEN_MAX_X, panelWidth - 1, 0, panelLeft);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(uintptr_t)(backdropSurface + 184))(buildingCompleteAltText[0], buildingCompleteAltText[1], buildingCompleteAltText[2], buildingCompleteText[0], buildingCompleteText[1], buildingCompleteText[2]);
  copyBackSrc = g_CheatEntryTextBuffer;
  copyBackDst = (char *)(uintptr_t)(buildingRecord + 5);
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  do
  {
    result = *copyBackSrc;
    *copyBackDst = *copyBackSrc;
    if ( !result )
      break;
    result = copyBackSrc[1];
    copyBackSrc += 2;
    copyBackDst[1] = result;
    copyBackDst += 2;
  }
  while ( result );
  return result;
}
// 445D46: variable 'v4' is possibly undefined
// 445D86: variable 'v5' is possibly undefined
// 445DB7: variable 'v12' is possibly undefined
// 445DE6: variable 'v14' is possibly undefined
// 445FA7: variable 'v22' is possibly undefined
// 445FE6: variable 'v24' is possibly undefined
// 44603C: variable 'v26' is possibly undefined
// 44609E: variable 'v29' is possibly undefined
// 446148: variable 'v35' is possibly undefined
// 44618F: variable 'v36' is possibly undefined
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 517EB8: using guessed type char *off_517EB8[6];
// 517EC4: using guessed type char *off_517EC4[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D44: using guessed type int dword_543D44;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;
