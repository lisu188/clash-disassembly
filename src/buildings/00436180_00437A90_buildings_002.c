/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00436180) --------------------------------------------------------
int  BuildingTransferDialog_IncreaseTransferAmount(int widget)
{
  int v2; // edx
  int v3; // ecx
  int startAmount; // ebx
  int v5; // edx
  int v6; // ecx
  int timePrev; // eax
  int v8; // ecx
  int timeNow; // eax
  int v10; // edx
  int v11; // ecx
  DWORD sourceGold; // ebp
  int v13; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount += 10;
  startAmount = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, startAmount);
    timePrev = Time_Now(v6, v5);
    timeNow = Time_Now(v8, timePrev);
    g_Building_TransferAmount = 10 * ((startAmount + (v10 - v11) * (timeNow - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount > 1000 )
      g_Building_TransferAmount = 1000;
    sourceGold = *(_DWORD *)(uintptr_t)(g_BuildingTransferSourcePtr + 438);
    if ( g_Building_TransferAmount > sourceGold )
    {
      sourceGold = 10;
      g_Building_TransferAmount = 10 * (*(_DWORD *)(uintptr_t)(g_BuildingTransferSourcePtr + 438) / 0xAu);
    }
    BuildingTransferDialog_DrawTransferAmountValue(sourceGold, (int)(intptr_t)g_RenderState);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v13);
}
// 436197: variable 'v3' is possibly undefined
// 436197: variable 'v2' is possibly undefined
// 4361BD: variable 'v6' is possibly undefined
// 4361BD: variable 'v5' is possibly undefined
// 4361C4: variable 'v8' is possibly undefined
// 4361C9: variable 'v10' is possibly undefined
// 4361C9: variable 'v11' is possibly undefined
// 436237: variable 'v13' is possibly undefined
// 532350: using guessed type int dword_532350;
// 532354: using guessed type int dword_532354;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00436250) --------------------------------------------------------
int  BuildingTransferDialog_DecreaseTransferAmount(int widget)
{
  int v2; // edx
  int v3; // ecx
  int startAmount; // ebx
  int v5; // edx
  int v6; // ecx
  int timeValue; // eax
  int v8; // ecx
  int currentTime; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount -= 10;
  startAmount = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, startAmount);
    timeValue = Time_Now(v6, v5);
    currentTime = Time_Now(v8, timeValue);
    g_Building_TransferAmount = 10 * ((startAmount - (v10 - v11) * (currentTime - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount < 0 )
      g_Building_TransferAmount = 0;
    BuildingTransferDialog_DrawTransferAmountValue((DWORD)(intptr_t)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v12);
}
// 43626A: variable 'v3' is possibly undefined
// 43626A: variable 'v2' is possibly undefined
// 436292: variable 'v6' is possibly undefined
// 436292: variable 'v5' is possibly undefined
// 436299: variable 'v8' is possibly undefined
// 43629E: variable 'v10' is possibly undefined
// 43629E: variable 'v11' is possibly undefined
// 4362F1: variable 'v12' is possibly undefined
// 532350: using guessed type int dword_532350;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00436610) --------------------------------------------------------
int  BuildingTransferTargetList_SetDrawOrigin(int result, int originY)
{
  g_BuildingTransferTargetListDrawX = result;
  g_BuildingTransferTargetListDrawY = originY;
  return result;
}
// 53242C: using guessed type int g_BuildingTransferTargetListDrawX;
// 532430: using guessed type int g_BuildingTransferTargetListDrawY;

//----- (00436620) --------------------------------------------------------
void * BuildingTransferTargetList_Draw(int a1, DWORD renderContext)
{
  _DWORD *spriteSet; // eax
  int row_y_offset; // ebp
  int target_index CLASH95_UNUSED; // edi
  void *saved_render_device; // eax
  int highlight_surface; // eax
  int building_index; // eax
  int SpriteForChar; // eax
  int v13; // eax
  int v15[3]; // [esp+4h] [ebp-40h]
  int row_index; // [esp+18h] [ebp-2Ch]
  int building_record; // [esp+1Ch] [ebp-28h]
  int row_bottom; // [esp+24h] [ebp-20h]

  saved_render_device = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  if ( !g_BuildingTransferTargetListSpriteSet )
  {
    spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a1, 0, renderContext);
    if ( spriteSet )
      spriteSet = DLXSpriteSet_Load(spriteSet, aCas_list_s32);
    g_BuildingTransferTargetListSpriteSet = (int)(intptr_t)spriteSet;
    DLXSpriteSet_DrawFormattedText((DWORD)(intptr_t)spriteSet, -1, a1, aCas_list_pal);
  }
  Render_ReleaseSurface(5, renderContext);
  row_index = g_BuildingTransferTargetListIndex - 2;
  row_y_offset = 0;
  row_bottom = 18;
  while ( row_index <= g_BuildingTransferTargetListIndex + 2 )
  {
    Render_FillRect(
      (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
      0,
      (unsigned __int16)(row_y_offset + g_BuildingTransferTargetListDrawY),
      (unsigned __int16)g_BuildingTransferTargetListDrawX,
      g_BuildingTransferTargetListDrawX + 266,
      row_bottom + g_BuildingTransferTargetListDrawY,
      g_BuildingTransferTargetListDrawX,
      row_y_offset + g_BuildingTransferTargetListDrawY);
    if ( row_index >= 0
      && row_index < BUILDING_TRANSFER_TARGET_LIST_CAPACITY
      && g_BuildingTransferTargetIds[row_index] != -1 )
    {
      if ( row_index == g_BuildingTransferTargetListIndex )
        highlight_surface = 9;
      else
        highlight_surface = 5;
      Render_ReleaseSurface(highlight_surface, 0);
      building_index = g_BuildingTransferTargetIds[row_index];
      if ( building_index == -2 )
      {
        v15[0] = (int)(intptr_t)g_BuildingTransferOutsideCastleLabel[0];
        v15[1] = (int)(intptr_t)g_BuildingTransferOutsideCastleLabel[1];
        v15[2] = (int)(intptr_t)g_BuildingTransferOutsideCastleLabel[2];
        UI_DrawText(
          g_BuildingTransferTargetListDrawX,
          row_y_offset + g_BuildingTransferTargetListDrawY,
          v15[(unsigned __int8)g_LanguageIndex]);
      }
      else
      {
        building_record = BUILDING_RECORD(building_index);
        UI_DrawText(
          g_BuildingTransferTargetListDrawX,
          row_y_offset + g_BuildingTransferTargetListDrawY,
          building_record + 5);
        SpriteForChar = DLX_GetSpriteForChar(g_BuildingTransferTargetListSpriteSet, 1);
        Compat_RenderDeviceDrawMenuSprite(
          g_BuildingTransferTargetListDrawX + 108,
          row_y_offset + g_BuildingTransferTargetListDrawY - 4,
          SpriteForChar,
          1);
        UI_DrawText(
          g_BuildingTransferTargetListDrawX + 124,
          row_y_offset + g_BuildingTransferTargetListDrawY,
          (int)(intptr_t)aD_10,
          *(unsigned __int16 *)(uintptr_t)(building_record + 430));
        v13 = DLX_GetSpriteForChar(g_BuildingTransferTargetListSpriteSet, 2);
        Compat_RenderDeviceDrawMenuSprite(
          g_BuildingTransferTargetListDrawX + 170,
          row_y_offset + g_BuildingTransferTargetListDrawY - 2,
          v13,
          1);
        UI_DrawText(
          g_BuildingTransferTargetListDrawX + 206,
          row_y_offset + g_BuildingTransferTargetListDrawY,
          (int)(intptr_t)aD_11,
          *(_DWORD *)(uintptr_t)(building_record + 438));
      }
    }
    row_y_offset += 18;
    row_bottom += 18;
    ++row_index;
  }
  g_RenderDevice = saved_render_device;
  return saved_render_device;
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5156E4: using guessed type char *off_5156E4[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];
// 532428: using guessed type int g_BuildingTransferTargetListSpriteSet;
// 53242C: using guessed type int g_BuildingTransferTargetListDrawX;
// 532430: using guessed type int g_BuildingTransferTargetListDrawY;

//----- (004368F0) --------------------------------------------------------
int  BuildingTransferTargetList_SelectPrevious(int widget, DWORD renderContext)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(widget);
  if ( g_BuildingTransferTargetListIndex )
    --g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_previous old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)(intptr_t)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
  return UIWidget_ShowReleasedState(widget, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;

//----- (00436930) --------------------------------------------------------
int  BuildingTransferTargetList_SelectNext(int widget, DWORD renderContext)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(widget);
  if ( g_BuildingTransferTargetIdsLookahead[g_BuildingTransferTargetListIndex] != -1 )
    ++g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_next old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)(intptr_t)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
  return UIWidget_ShowReleasedState(widget, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532362: using guessed type __int16 word_532362[99];

//----- (00436970) --------------------------------------------------------
int  BuildingTransferTargetList_Rebuild(int sourceBuildingRecord, int reserveFirstSlot)
{
  int building_index; // edx
  int insert_index; // ebx
  int result; // eax
  int current_player; // ebp
  int building_record; // ecx

  memset(g_BuildingTransferTargetIds, 0xFF, sizeof(g_BuildingTransferTargetIds));
  g_BuildingTransferTargetIds[0] = -2;
  building_index = 0;
  current_player = g_CurrentPlayerIndex;
  result = 0;
  insert_index = reserveFirstSlot ? 1 : 0;
  do
  {
    building_record = result + gameData + BUILDING_TABLE_OFFSET;
    if ( *(char *)(uintptr_t)(result + gameData + 509678) != -1
      && *(_BYTE *)(uintptr_t)(result + gameData + 509678)
      && *(unsigned __int8 *)(uintptr_t)(building_record + 2) == current_player
      && building_record != sourceBuildingRecord
      && !*(_WORD *)(uintptr_t)(building_record + 16)
      && insert_index < BUILDING_TRANSFER_TARGET_LIST_CAPACITY )
    {
      g_BuildingTransferTargetIds[insert_index] = building_index;
      ++insert_index;
    }
    ++building_index;
    result += BUILDING_RECORD_SIZE;
  }
  while ( building_index < 100 );
  g_BuildingTransferTargetListIndex = 0;
  return result;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];

//----- (00436A30) --------------------------------------------------------
int  BuildingTransferTargetList_HandleClick(DWORD renderContext)
{
  int rowOffset; // ebx
  int result; // eax

  rowOffset = ((g_MouseCursorRawY >> g_CursorCoordShift) - g_BuildingTransferTargetListDrawY) / 18 - 2;
  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  if ( result )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= g_BuildingTransferTargetListDrawX )
    {
      result = g_BuildingTransferTargetListDrawX + 266;
      if ( g_MouseCursorRawX >> g_CursorCoordShift <= g_BuildingTransferTargetListDrawX + 266
        && rowOffset >= -2
        && rowOffset <= 2
        && rowOffset + g_BuildingTransferTargetListIndex >= 0 )
      {
        result = g_BuildingTransferTargetIds[rowOffset + g_BuildingTransferTargetListIndex];
        if ( result != -1 )
        {
          g_BuildingTransferTargetListIndex += rowOffset;
          Render_Pump();
          BuildingTransferTargetList_Draw((int)(intptr_t)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
          Render_Present((int)(intptr_t)g_RenderState);
          return Render_Begin((int)(intptr_t)g_RenderState, 0);
        }
      }
    }
  }
  return result;
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];
// 53242C: using guessed type int g_BuildingTransferTargetListDrawX;
// 532430: using guessed type int g_BuildingTransferTargetListDrawY;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00436AF0) --------------------------------------------------------
int BuildingTransferTargetList_FreeSpriteSet(void)
{
  int result; // eax

  if ( g_BuildingTransferTargetListSpriteSet )
    result = DLXSpriteSet_ReleaseAndClear(&g_BuildingTransferTargetListSpriteSet);
  g_BuildingTransferTargetListSpriteSet = 0;
  return result;
}
// 532428: using guessed type int g_BuildingTransferTargetListSpriteSet;

//----- (00436B20) --------------------------------------------------------
int  UI_DrawFormattedTokenLine(int leftX, int rightX, int templateIndex, int penX)
{
  int availableWidth; // esi
  int result; // eax
  unsigned __int8 *tokenRecord; // ecx
  int v9; // ecx
  _BYTE *wrapTextPtr; // ecx
  _BYTE *segmentText; // ecx
  char *wrapBreakPos; // eax
  int v13; // ecx
  _BYTE *v14; // edx
  char *templateRow; // [esp+0h] [ebp-18h]
  int tokenOffset; // [esp+4h] [ebp-14h]
  char savedChar; // [esp+8h] [ebp-10h]

  availableWidth = rightX - leftX;
  tokenOffset = 0;
  templateRow = (char *)&g_UiFormattedMessageTemplateTable + 150 * templateIndex;
  do
  {
    result = (int)(intptr_t)&templateRow[50 * (unsigned __int8)g_LanguageIndex];
    tokenRecord = (unsigned __int8 *)(uintptr_t)(result + tokenOffset);
    if ( !*(_DWORD *)(uintptr_t)(result + tokenOffset + 1) )
      break;
    if ( *tokenRecord == 4 && (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(tokenRecord + 1)) > availableWidth )
    {
      wrapTextPtr = *(_BYTE **)(tokenRecord + 1);
      while ( (unsigned __int16)Render_LoadResourceSprite_v3(wrapTextPtr) > availableWidth )
      {
        wrapBreakPos = TextSprite_FindWordWrapBreak(segmentText, availableWidth);
        savedChar = *wrapBreakPos;
        *wrapBreakPos = 0;
        UI_DrawTextFmt(leftX, leftX, rightX, penX, 4, v13);
        *v14 = savedChar;
        penX += UI_GetTextXOffset(g_ActiveTextSpriteSlot);
      }
      UI_DrawTextFmt(leftX, leftX, rightX, penX, 1, (int)(intptr_t)segmentText);
    }
    else
    {
      UI_DrawTextFmt(leftX, leftX, rightX, penX, *tokenRecord, *(_DWORD *)(tokenRecord + 1));
    }
    result = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
    penX += result;
    tokenOffset = v9 + 5;
  }
  while ( v9 + 5 < 50 );
  return result;
}
// 436B7A: variable 'v8' is possibly undefined
// 436B9B: variable 'v9' is possibly undefined
// 436BC1: variable 'v10' is possibly undefined
// 436BD3: variable 'v11' is possibly undefined
// 436BE9: variable 'v13' is possibly undefined
// 436BF5: variable 'v14' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 520728: using guessed type int dword_520728;

//----- (00436C10) --------------------------------------------------------
int __thiscall UnitBattle_ConstructAiCandidateQueue(void *this)
{
  g_UnitBattleAiCandidateQueue = 0;
  g_UnitBattleAiCandidateQueueTail = 0;
  g_BattleAiUnitQueueCount = 0;
  g_BattleAiCandidateQueue_AllocFn = 0;
  g_BattleAiCandidateQueue_FreeFn = 0;
  g_BattleAiCandidateQueue_Vtable = (int)(intptr_t)&g_WCIsvListBaseVariant134_Vtable;
  return CRT_RegisterFinalizableObject(this, 0);
}
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50F134: using guessed type void *off_50F134;
// 5437C0: using guessed type int dword_5437C0;
// 5437C4: using guessed type int dword_5437C4;
// 5437C8: using guessed type int dword_5437C8;
// 5437CC: using guessed type int dword_5437CC;
// 5437D0: using guessed type int dword_5437D0;
// 5437D4: using guessed type int dword_5437D4;

//----- (00436C50) --------------------------------------------------------
int  UnitBattle_ResetAiReachGridForSide(int side)
{
  int reachGridBase; // edi
  int result; // eax
  int gridRow; // ecx
  int rowEndOffset; // ebx
  int unitRecordOffset; // [esp+4h] [ebp-1Ch]

  reachGridBase = 0;
  unitRecordOffset = 0;
  do
  {
    result = unitRecordOffset + g_MapData;
    if ( *(__int16 *)(uintptr_t)(unitRecordOffset + g_MapData + 852) != -1 )
    {
      result = *(unsigned __int8 *)(uintptr_t)(result + 854);
      if ( result == side )
      {
        gridRow = 0;
        rowEndOffset = reachGridBase + 160;
        do
        {
          result = reachGridBase + 160 * gridRow;
          do
          {
            result += 8;
            *(int *)((char *)&g_UnitBattleAiReachGrid + result) = 0;
            *(int *)((char *)&g_UnitBattleAiReachGridCellSecondField + result) = 0;
          }
          while ( result != rowEndOffset );
          ++gridRow;
          rowEndOffset += 160;
        }
        while ( gridRow < 20 );
      }
    }
    reachGridBase += 3204;
    unitRecordOffset += 31;
  }
  while ( reachGridBase != 70488 );
  return result;
}
// 532048: using guessed type int g_MapData;
// 532440: using guessed type int dword_532440;
// 532444: using guessed type int dword_532444;

//----- (00436D10) --------------------------------------------------------
signed int  UnitBattle_RetreatUnit(int unitIndex, int a2, char a3, DWORD a4)
{
  int movingUnitIndex; // edx
  __int16 *unitRecord; // ecx
  signed int j; // ebp
  int v8; // ebx
  signed int result; // eax
  int scanUnitOffset; // esi
  int scanRecordBase; // eax
  int *movePath; // eax
  int unitRecordAddr; // ecx
  int searchRadius; // [esp+4h] [ebp-34h]
  int signY; // [esp+8h] [ebp-30h]
  int i; // [esp+Ch] [ebp-2Ch]
  int offsetX; // [esp+10h] [ebp-28h]
  int signX; // [esp+14h] [ebp-24h]
  int originY; // [esp+18h] [ebp-20h]
  int originX; // [esp+1Ch] [ebp-1Ch]
  int candidateY; // [esp+20h] [ebp-18h]
  int candidateX; // [esp+24h] [ebp-14h]

  Debug_Log(a2, a3, a4, (int)(intptr_t)aCofnij_oddzial);
  unitRecord = (__int16 *)(uintptr_t)(31 * movingUnitIndex + g_MapData + 852);
  searchRadius = 0;
  originX = (unsigned __int16)unitRecord[2];
  signX = 1;
  signY = 1;
  originY = (unsigned __int16)unitRecord[3];
  while ( 2 )
  {
    for ( i = 1; i <= 2; ++i )
    {
      signY = -signY;
      offsetX = 0;
      candidateY = signY * searchRadius + originY;
      while ( 2 )
      {
        for ( j = 1; j <= 2; ++j )
        {
          signX = -signX;
          candidateX = signX * offsetX + originX;
          if ( candidateX < 0 )
            candidateX = 0;
          if ( candidateX > *(_DWORD *)(uintptr_t)(g_MapData + 804) )
            candidateX = *(_DWORD *)(uintptr_t)(g_MapData + 804);
          if ( candidateY < 0 )
            candidateY = 0;
          v8 = *(_DWORD *)(uintptr_t)(g_MapData + 800);
          if ( candidateY > v8 )
            candidateY = *(_DWORD *)(uintptr_t)(g_MapData + 800);
          if ( *(__int16 *)(uintptr_t)(40 * candidateX + g_MapData + 2 * candidateY + 1534) == -1 )
          {
            v8 = candidateY;
            if ( UnitBattle_GetTileMoveCostOrZero(*unitRecord, candidateX, candidateY) )
            {
              unitRecord[2] = candidateX;
              scanUnitOffset = 0;
              unitRecord[3] = candidateY;
              while ( 1 )
              {
                scanRecordBase = scanUnitOffset + g_MapData;
                if ( *(__int16 *)(uintptr_t)(scanUnitOffset + g_MapData + 852) != -1 && *(_BYTE *)(uintptr_t)(scanRecordBase + 854) != *((_BYTE *)unitRecord + 2) )
                {
                  v8 = *(unsigned __int16 *)(uintptr_t)(scanRecordBase + 858);
                  if ( UnitBattle_IsTileWithinRange(unitIndex, *(unsigned __int16 *)(uintptr_t)(scanRecordBase + 856), (unsigned __int16)v8) )
                  {
                    unitRecord[2] = originX;
                    unitRecord[3] = originY;
                    g_UnitBattleScanTileRow = *(unsigned __int16 *)(uintptr_t)(scanUnitOffset + g_MapData + 856);
                    v8 = candidateY;
                    g_BattleTargetTileCol = *(unsigned __int16 *)(uintptr_t)(scanUnitOffset + g_MapData + 858);
                    movePath = UnitBattle_MoveTrack(unitIndex, candidateX, (int)(intptr_t)unitRecord, candidateY, j);
                    *(_DWORD *)((char *)unitRecord + 23) = movePath;
                    if ( movePath )
                      break;
                  }
                }
                scanUnitOffset += 31;
                if ( scanUnitOffset >= 682 )
                  goto LABEL_14;
              }
              UnitBattle_Move(unitIndex, (int)(intptr_t)unitRecord, candidateY, j);
              if ( *(_DWORD *)(uintptr_t)(unitRecordAddr + 23) )
                j__nfree_();
              result = 1;
              *(_DWORD *)(uintptr_t)(unitRecordAddr + 23) = 0;
              return result;
            }
          }
LABEL_14:
          ;
        }
        offsetX = v8 + 1;
        if ( v8 + 1 <= 2 )
          continue;
        break;
      }
    }
    if ( ++searchRadius <= 2 )
      continue;
    return 0;
  }
}
// 436D3B: variable 'v5' is possibly undefined
// 436E82: variable 'v6' is possibly undefined
// 436F3B: variable 'v13' is possibly undefined
// 532048: using guessed type int g_MapData;
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;

//----- (00437050) --------------------------------------------------------
BOOL  UnitBattle_IsTileWithinMinRange(int unitIndex, int targetX, int targetY)
{
  int unit_record;
  signed int distance; // eax

  if ( !g_MapData || unitIndex < 0 || unitIndex >= 22 )
    return 0;
  unit_record = g_MapData + 31 * unitIndex + 852;
  if ( *(__int16 *)(uintptr_t)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852 + 4) - targetX)
       * (*(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852 + 4) - targetX)
       + (*(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852 + 6) - targetY)
       * (*(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852 + 6) - targetY));
  return distance <= (unsigned __int8)g_UnitTypeMinRange_512583[88 * *(__int16 *)(uintptr_t)unit_record];
}
// 532048: using guessed type int g_MapData;

//----- (004370B0) --------------------------------------------------------
signed int  UnitBattle_MoveShootingUnit(int attackerIndex, int defenderSide, char a3, DWORD gameContext)
{
  int movingUnitIndex; // edx
  DWORD unitRecordOffset; // ebp
  int unitRecord; // esi
  int v7; // ecx
  int v8; // ecx
  int scanRowBase; // edx
  int targetOccupant; // eax
  int targetUnitIndex; // ebx
  int targetRecordOffset; // esi
  int v13; // ecx
  int shotResult; // edx
  signed int result; // eax
  int v16; // ecx
  int movePath; // eax
  int v18; // ecx
  int v19; // ecx
  int reachedRange; // edi
  int *pathArray; // eax
  int stepIndex; // ebx
  int pathToFree; // edi
  int v24; // ecx
  int occupantUnitIndex; // ebx
  int v26; // ecx
  int shooterRecordOffset; // esi
  int v28; // ecx
  int v29; // ecx
  int shotTargetUnitIndex; // esi
  int shotShooterRecordOffset; // ebx
  int v32; // ecx
  int secondShotResult; // edx
  int wallShotResult; // edx
  __int16 savedRow; // [esp+0h] [ebp-2Ch]
  __int16 savedCol; // [esp+4h] [ebp-28h]
  int pathStep; // [esp+14h] [ebp-18h]

  Debug_Log(attackerIndex, a3, gameContext, (int)(intptr_t)aRuch_oddzialem);
  unitRecordOffset = 31 * movingUnitIndex;
  unitRecord = g_MapData + 852 + 31 * movingUnitIndex;
  g_BattleShootingUnitMoveActiveFlag = 1;
  if ( UnitBattle_IsTileWithinRange(v7, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    scanRowBase = g_MapData + 40 * g_UnitBattleScanTileRow;
    targetOccupant = *(__int16 *)(uintptr_t)(scanRowBase + 2 * g_BattleTargetTileCol + 1534);
    if ( targetOccupant != -1 )
    {
      targetUnitIndex = *(__int16 *)(uintptr_t)(scanRowBase + 2 * g_BattleTargetTileCol + 1534);
      targetRecordOffset = 31 * targetOccupant;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        shotResult = UnitBattle_Shot(v13, targetUnitIndex);
        if ( !shotResult && *(unsigned __int8 *)(uintptr_t)(unitRecordOffset + g_MapData + 860) < 5u )
          break;
        if ( !shotResult && *(unsigned __int8 *)(uintptr_t)(unitRecordOffset + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(uintptr_t)(g_MapData + unitRecordOffset + 852) == -1 )
          break;
        if ( *(__int16 *)(uintptr_t)(targetRecordOffset + g_MapData + 852) == -1 )
          return 1;
      }
      return 0;
    }
  }
  if ( UnitBattle_IsTileWithinMinRange(v8, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    result = UnitBattle_RetreatUnit(v16, v16, g_BattleTargetTileCol, unitRecordOffset);
    if ( !result )
      return result;
  }
  if ( *(char *)(uintptr_t)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
    && *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * v16 + 854) == *(_DWORD *)(uintptr_t)(g_MapData + 836) )
  {
    movePath = UnitBattle_MoveTrackNearWall(v16, g_UnitBattleScanTileRow, g_BattleTargetTileCol, unitRecordOffset);
  }
  else
  {
    movePath = (int *)UnitBattle_MoveTrackNear(v16, v16, g_BattleTargetTileCol, unitRecordOffset);
  }
  *(_DWORD *)(uintptr_t)(unitRecord + 23) = movePath;
  if ( !*(_DWORD *)(uintptr_t)(unitRecord + 23) )
    *(_DWORD *)(uintptr_t)(unitRecord + 23) = UnitBattle_MoveTrackForce(v18, g_BattleTargetTileCol, unitRecordOffset);
  if ( !*(_DWORD *)(uintptr_t)(unitRecord + 23) )
    return 0;
  if ( UnitBattle_IsTileWithinRange(v18, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    if ( !*(_DWORD *)(uintptr_t)(unitRecord + 23) )
      goto LABEL_41;
  }
  else
  {
    reachedRange = -1;
    savedRow = BATTLE_UNIT_GRID_X(unitRecord);
    HIWORD(pathStep) = 0;
    savedCol = BATTLE_UNIT_GRID_Y(unitRecord);
    LOBYTE(pathStep) = *(_BYTE *)(uintptr_t)(unitRecord + 4);
    while ( HIWORD(pathStep) <= *(unsigned __int8 *)(uintptr_t)(unitRecord + 8) - 5 && **(_DWORD **)(uintptr_t)(unitRecord + 23) && reachedRange == -1 )
    {
      if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
      {
        reachedRange = 1;
      }
      else
      {
        pathArray = *(int **)(uintptr_t)(unitRecord + 23);
        stepIndex = *pathArray - 1;
        *pathArray = stepIndex;
        pathStep = pathArray[stepIndex + 1];
        if ( *(unsigned __int8 *)(uintptr_t)(unitRecord + 8) >= HIWORD(pathStep) + 5 )
        {
          BATTLE_UNIT_GRID_X(unitRecord) = (unsigned __int8)pathStep;
          BATTLE_UNIT_GRID_Y(unitRecord) = BYTE1(pathStep);
        }
      }
    }
    if ( reachedRange == -1 )
    {
      if ( *(_DWORD *)(uintptr_t)(unitRecord + 23) )
        j__nfree_();
      *(_DWORD *)(uintptr_t)(unitRecord + 23) = 0;
      return 0;
    }
    BATTLE_UNIT_GRID_X(unitRecord) = savedRow;
    pathToFree = *(_DWORD *)(uintptr_t)(unitRecord + 23);
    BATTLE_UNIT_GRID_Y(unitRecord) = savedCol;
    if ( pathToFree )
      j__nfree_();
    *(_DWORD *)(uintptr_t)(unitRecord + 23) = UnitBattle_MoveTrack(v19, (unsigned __int8)pathStep, v19, BYTE1(pathStep), 0xFFFFFFFF);
    UnitBattle_Move(v24, v24, BYTE1(pathStep), 0xFFFFFFFF);
    if ( !*(_DWORD *)(uintptr_t)(unitRecord + 23) )
      goto LABEL_40;
  }
  j__nfree_();
LABEL_40:
  *(_DWORD *)(uintptr_t)(unitRecord + 23) = 0;
LABEL_41:
  if ( *(char *)(uintptr_t)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) <= 0
    || *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * v19 + 854) != *(_DWORD *)(uintptr_t)(g_MapData + 836)
    || (occupantUnitIndex = *(__int16 *)(uintptr_t)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), occupantUnitIndex != -1)
    && *(unsigned __int8 *)(uintptr_t)(31 * occupantUnitIndex + g_MapData + 854) != defenderSide )
  {
    if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    {
      shotTargetUnitIndex = *(__int16 *)(uintptr_t)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
      shotShooterRecordOffset = 31 * v29;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        secondShotResult = UnitBattle_Shot(v32, shotTargetUnitIndex);
        if ( !secondShotResult && *(unsigned __int8 *)(uintptr_t)(shotShooterRecordOffset + g_MapData + 860) < 5u )
          break;
        if ( !secondShotResult && *(unsigned __int8 *)(uintptr_t)(shotShooterRecordOffset + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(uintptr_t)(g_MapData + shotShooterRecordOffset + 852) == -1 )
          return 0;
        if ( *(__int16 *)(uintptr_t)(31 * shotTargetUnitIndex + g_MapData + 852) == -1 )
          return 1;
      }
    }
    return 0;
  }
  if ( !UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    return 0;
  shooterRecordOffset = 31 * v26;
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( *(char *)(uintptr_t)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) <= 0 )
      return 1;
    wallShotResult = UnitBattle_ShotWall(v28, g_UnitBattleScanTileRow);
    if ( !wallShotResult && *(unsigned __int8 *)(uintptr_t)(shooterRecordOffset + g_MapData + 860) < 5u )
      return 0;
  }
  while ( wallShotResult || *(unsigned __int8 *)(uintptr_t)(shooterRecordOffset + g_MapData + 860) < 5u );
  return 1;
}
// 4370DD: variable 'v4' is possibly undefined
// 4370FE: variable 'v7' is possibly undefined
// 437160: variable 'v13' is possibly undefined
// 4371E9: variable 'v8' is possibly undefined
// 437200: variable 'v16' is possibly undefined
// 437283: variable 'v18' is possibly undefined
// 437343: variable 'v19' is possibly undefined
// 4373BF: variable 'v38' is possibly undefined
// 4373D1: variable 'v24' is possibly undefined
// 43748A: variable 'v26' is possibly undefined
// 437545: variable 'v29' is possibly undefined
// 437552: variable 'v32' is possibly undefined
// 4375CE: variable 'v28' is possibly undefined
// 429740: using guessed type int __fastcall UnitBattle_Shot(_DWORD, _DWORD);
// 429BD0: using guessed type int __fastcall UnitBattle_ShotWall(_DWORD, _DWORD);
// 532048: using guessed type int g_MapData;
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;
// 5437AC: using guessed type int dword_5437AC;

//----- (00437630) --------------------------------------------------------
int * UnitBattle_EstimateDamageScoreAgainstUnit(int attackerIndex, DWORD defenderIndex)
{
  __int16 *attackerRecord; // esi
  int attackerUnitType; // eax
  int *result; // eax
  char *v7; // ecx
  int altEffectiveness; // eax
  int v9; // ecx
  __int16 *defenderRecordPtr2; // edx
  int *pathBeforeFree; // ebp
  __int16 *defenderRecordPtr3; // edx
  int *pathBeforeFree2; // ebx
  bool i; // zf
  int *pathToFree; // edi
  int v16; // ecx
  __int16 *defenderRecordPtr; // edx
  int *pathPtr; // ebp
  int remainingSteps; // edx
  int *pathArray; // ebx
  int stepApCost; // edx
  char savedAttackerHealth; // [esp+0h] [ebp-40h]
  char savedAttackerHealth2; // [esp+0h] [ebp-40h]
  char savedActionPoints; // [esp+4h] [ebp-3Ch]
  int attackerHealthOut; // [esp+8h] [ebp-38h] BYREF
  int defenderHealthOut; // [esp+Ch] [ebp-34h] BYREF
  int savedRow; // [esp+10h] [ebp-30h]
  int savedCol; // [esp+14h] [ebp-2Ch]
  int effectiveness; // [esp+18h] [ebp-28h]
  int defenderHealth; // [esp+1Ch] [ebp-24h]
  __int16 *defenderRecord; // [esp+20h] [ebp-20h]
  int trackStep; // [esp+24h] [ebp-1Ch]
  int *movePath; // [esp+28h] [ebp-18h]

  attackerRecord = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * attackerIndex);
  savedRow = (unsigned __int16)attackerRecord[2];
  savedCol = (unsigned __int16)attackerRecord[3];
  savedActionPoints = *((_BYTE *)attackerRecord + 8);
  attackerUnitType = *attackerRecord;
  defenderRecord = (__int16 *)(uintptr_t)(31 * defenderIndex + g_MapData + 852);
  if ( attackerUnitType == UNIT_TYPE_RAM )
    return 0;
  result = (int *)UnitBattle_MoveTrackNear(
                    attackerIndex,
                    31 * defenderIndex + g_MapData + 852,
                    *(unsigned __int16 *)(uintptr_t)(31 * defenderIndex + g_MapData + 852 + 6),
                    defenderIndex);
  movePath = result;
  if ( result )
  {
    effectiveness = Unit_CalcEffectivenessA(v7, 0);
    altEffectiveness = Unit_CalcEffectivenessC(defenderRecord);
    if ( altEffectiveness > v9 )
      effectiveness = altEffectiveness;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(g_MapData + 31 * attackerIndex + 852)] )
    {
      defenderHealth = *((char *)defenderRecord + 9);
      HIWORD(trackStep) = 0;
      for ( i = *movePath == 0; ; i = *movePath == 0 )
      {
        if ( i || !movePath )
        {
          attackerRecord[2] = savedRow;
          attackerRecord[3] = savedCol;
          pathToFree = movePath;
          *((_BYTE *)attackerRecord + 8) = savedActionPoints;
          if ( !pathToFree )
            return 0;
          goto LABEL_41;
        }
        if ( UnitBattle_IsUnitWithinRange(attackerIndex, defenderIndex) )
          break;
        remainingSteps = *movePath - 1;
        pathArray = movePath;
        *movePath = remainingSteps;
        trackStep = pathArray[remainingSteps + 1];
        attackerRecord[2] = (unsigned __int8)trackStep;
        attackerRecord[3] = BYTE1(trackStep);
        stepApCost = HIWORD(trackStep) - v16;
        if ( stepApCost > *((unsigned __int8 *)attackerRecord + 8) )
        {
          attackerRecord[2] = savedRow;
          attackerRecord[3] = savedCol;
          *((_BYTE *)attackerRecord + 8) = savedActionPoints;
LABEL_41:
          j__nfree_();
          return 0;
        }
        *((_BYTE *)attackerRecord + 8) -= stepApCost;
      }
      while ( *((unsigned __int8 *)attackerRecord + 8) >= HIWORD(trackStep) + 5 )
      {
        *((_BYTE *)defenderRecord + 9) = UnitBattle_CalcShotTargetHealthAfterHit(attackerIndex, defenderIndex);
        *((_BYTE *)attackerRecord + 8) -= 5;
      }
      defenderHealthOut = defenderHealth;
      attackerRecord[2] = savedRow;
      attackerRecord[3] = savedCol;
      defenderRecordPtr = defenderRecord;
      *((_BYTE *)attackerRecord + 8) = savedActionPoints;
      pathPtr = movePath;
      *((_BYTE *)defenderRecordPtr + 9) = defenderHealth;
      if ( pathPtr )
        j__nfree_();
      return (int *)(uintptr_t)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
    }
    else
    {
      if ( !movePath )
        return 0;
      if ( *movePath )
      {
        trackStep = movePath[1];
        if ( *((unsigned __int8 *)attackerRecord + 8) < HIWORD(trackStep) + 5 )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          if ( movePath )
          {
            j__nfree_();
            return 0;
          }
          return 0;
        }
        savedAttackerHealth = *((_BYTE *)attackerRecord + 9);
        defenderHealth = *((char *)defenderRecord + 9);
        while ( *((unsigned __int8 *)attackerRecord + 8) >= HIWORD(trackStep) + 5 )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          *((_BYTE *)attackerRecord + 9) = attackerHealthOut;
          *((_BYTE *)defenderRecord + 9) = defenderHealthOut;
          *((_BYTE *)attackerRecord + 8) -= 5;
        }
        *((_BYTE *)attackerRecord + 8) = savedActionPoints;
        defenderRecordPtr2 = defenderRecord;
        *((_BYTE *)attackerRecord + 9) = savedAttackerHealth;
        pathBeforeFree = movePath;
        *((_BYTE *)defenderRecordPtr2 + 9) = defenderHealth;
        if ( pathBeforeFree )
          j__nfree_();
        return (int *)(uintptr_t)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
      }
      else if ( *((unsigned __int8 *)attackerRecord + 8) < 5u )
      {
        defenderHealth = *(char *)(uintptr_t)(31 * defenderIndex + g_MapData + 861);
        UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
        j__nfree_();
        return (int *)(uintptr_t)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
      }
      else
      {
        savedAttackerHealth2 = *((_BYTE *)attackerRecord + 9);
        defenderHealth = *((char *)defenderRecord + 9);
        while ( *((unsigned __int8 *)attackerRecord + 8) >= 5u )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          *((_BYTE *)attackerRecord + 9) = attackerHealthOut;
          *((_BYTE *)defenderRecord + 9) = defenderHealthOut;
          *((_BYTE *)attackerRecord + 8) -= 5;
        }
        *((_BYTE *)attackerRecord + 8) = savedActionPoints;
        defenderRecordPtr3 = defenderRecord;
        *((_BYTE *)attackerRecord + 9) = savedAttackerHealth2;
        pathBeforeFree2 = movePath;
        *((_BYTE *)defenderRecordPtr3 + 9) = defenderHealth;
        if ( pathBeforeFree2 )
          j__nfree_();
        return (int *)(uintptr_t)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
      }
    }
  }
  return result;
}
// 437898: conditional instruction was optimized away because edi.4!=0
// 437A66: conditional instruction was optimized away because ebx.4!=0
// 43778A: conditional instruction was optimized away because %var_18.4==0
// 4376AC: variable 'v7' is possibly undefined
// 4376C4: variable 'v9' is possibly undefined
// 437A40: variable 'v16' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00437A90) --------------------------------------------------------
int  UnitBattle_ScoreTileAgainstRangedUnitsOfSide(int unitIndex, int side, int a3)
{
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int targetCol; // ebx
  int unitRecordPtr; // esi
  int v9; // edx
  int scoreDelta; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // ebx
  int unitRecordPtr2; // esi
  int v17; // edx
  int scoreDelta2; // edx
  int v20; // ecx
  int v21; // eax
  int *v22; // eax
  int *movePath; // ecx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int *v28; // ecx
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int v32; // ecx
  int v33; // eax
  int *v34; // eax
  int *movePath2; // ecx
  int v36; // eax
  int v37; // eax
  int v38; // edx
  int *v39; // ecx
  int v40; // edx
  int v41; // ebx
  int v42; // edx
  int scanOffset; // [esp+0h] [ebp-50h]
  __int16 savedRow; // [esp+8h] [ebp-48h]
  int unitRecordOffset; // [esp+Ch] [ebp-44h]
  int trackStep; // [esp+10h] [ebp-40h]
  int packedTrackStep; // [esp+10h] [ebp-40h]
  int bestScore; // [esp+18h] [ebp-38h]
  int effectiveness2; // [esp+1Ch] [ebp-34h]
  int effectiveness; // [esp+20h] [ebp-30h]
  __int16 savedCol; // [esp+24h] [ebp-2Ch]
  __int16 savedCol2; // [esp+28h] [ebp-28h]
  int trackStep2; // [esp+2Ch] [ebp-24h]
  int packedTrackStep2; // [esp+2Ch] [ebp-24h]
  int targetRow; // [esp+30h] [ebp-20h]
  int targetCol2; // [esp+34h] [ebp-1Ch]
  __int16 savedRow2; // [esp+38h] [ebp-18h]

  bestScore = 0;
  scanOffset = 0;
  unitRecordOffset = 31 * unitIndex;
  do
  {
    v3 = *(__int16 *)(uintptr_t)(g_MapData + scanOffset + 852);
    if ( v3 != -1 && *(unsigned __int8 *)(uintptr_t)(g_MapData + scanOffset + 854) == side && g_UnitTypeRole[88 * v3] == 4 )
    {
      Unit_CalcEffectivenessA((char *)(uintptr_t)(unitRecordOffset + g_MapData + 852), 0);
      v4 = Unit_CalcEffectivenessC((__int16 *)(uintptr_t)(unitRecordOffset + g_MapData + 852));
      if ( v5 <= v4 )
        v6 = Unit_CalcEffectivenessC((__int16 *)(uintptr_t)(unitRecordOffset + g_MapData + 852));
      else
        v6 = Unit_CalcEffectivenessA((char *)(uintptr_t)(unitRecordOffset + g_MapData + 852), 0);
      effectiveness = v6;
      targetCol = *(unsigned __int16 *)(uintptr_t)(scanOffset + g_MapData + 858);
      targetRow = *(unsigned __int16 *)(uintptr_t)(scanOffset + g_MapData + 856);
      Debug_Log(scanOffset, targetCol, a3, (int)(intptr_t)aOddzial_w_zasi);
      unitRecordPtr = unitRecordOffset + g_MapData + 852;
      a3 = (unsigned __int16)targetCol;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v9, (unsigned __int16)targetCol)
        && (*(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
      {
        scoreDelta = 0;
LABEL_10:
        LOBYTE(scoreDelta) = BATTLE_UNIT_ACTION_POINTS(unitRecordPtr);
        goto LABEL_11;
      }
      v20 = targetRow;
      if ( *(char *)(uintptr_t)(g_MapData + 20 * targetRow + targetCol + 3134) <= 0
        || (v20 = g_MapData + 40 * targetRow, *(__int16 *)(uintptr_t)(v20 + 2 * targetCol + 1534) != -1)
        && ((v21 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v21 + 852)] & 1) != 0)
         || (*(_BYTE *)(uintptr_t)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v21 + 864)) >> 5) > 0) )
      {
        v22 = (int *)UnitBattle_MoveTrackNear(unitIndex, v20, targetCol, (unsigned __int16)targetCol);
      }
      else
      {
        v22 = UnitBattle_MoveTrackNearWall(unitIndex, targetRow, targetCol, (unsigned __int16)targetCol);
      }
      movePath = v22;
      if ( !v22 )
      {
        v24 = 31 * unitIndex + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v24 + 852)] )
        {
          if ( (*(_BYTE *)(uintptr_t)(v24 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v24 + 864)) >> 5) > 0 )
            movePath = UnitBattle_MoveTrackForce(unitIndex, targetCol, (unsigned __int16)targetCol);
        }
      }
      if ( !movePath )
      {
        scoreDelta = -1;
        goto LABEL_11;
      }
      if ( !*movePath )
      {
        j__nfree_();
        goto LABEL_10;
      }
      v25 = g_MapData + 31 * unitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v25 + 852)]
        && (*(_BYTE *)(uintptr_t)(v25 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v25 + 864)) >> 5) > 0 )
      {
        savedRow = BATTLE_UNIT_GRID_X(unitRecordPtr);
        HIWORD(packedTrackStep) = 0;
        savedCol = BATTLE_UNIT_GRID_Y(unitRecordPtr);
        if ( *movePath )
        {
          while ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, (unsigned __int16)targetCol) )
          {
            v30 = *v28 - 1;
            *v28 = v30;
            packedTrackStep = v28[v30 + 1];
            if ( HIWORD(packedTrackStep) > (int)*(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) )
              goto LABEL_54;
            BATTLE_UNIT_GRID_X(unitRecordPtr) = (unsigned __int8)packedTrackStep;
            BATTLE_UNIT_GRID_Y(unitRecordPtr) = BYTE1(packedTrackStep);
            if ( !*v28 )
              goto LABEL_51;
          }
          BATTLE_UNIT_GRID_X(unitRecordPtr) = savedRow;
          BATTLE_UNIT_GRID_Y(unitRecordPtr) = savedCol;
          j__nfree_();
          LOBYTE(v29) = BATTLE_UNIT_ACTION_POINTS(unitRecordPtr);
          if ( v29 > HIWORD(packedTrackStep) )
          {
            scoreDelta = v29 - HIWORD(packedTrackStep);
            goto LABEL_11;
          }
          goto LABEL_48;
        }
LABEL_51:
        if ( UnitBattle_IsTileWithinRange(unitIndex, targetRow, (unsigned __int16)targetCol) )
        {
          BATTLE_UNIT_GRID_X(unitRecordPtr) = savedRow;
          BATTLE_UNIT_GRID_Y(unitRecordPtr) = savedCol;
          if ( *(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) > (int)HIWORD(packedTrackStep) )
          {
            j__nfree_();
            scoreDelta = *(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) - v31;
            goto LABEL_11;
          }
LABEL_47:
          j__nfree_();
LABEL_48:
          scoreDelta = 0;
          goto LABEL_11;
        }
LABEL_54:
        BATTLE_UNIT_GRID_X(unitRecordPtr) = savedRow;
        BATTLE_UNIT_GRID_Y(unitRecordPtr) = savedCol;
        j__nfree_();
      }
      else
      {
        if ( !*movePath )
          goto LABEL_47;
        trackStep = movePath[1];
        j__nfree_();
        LOWORD(v26) = HIWORD(trackStep);
        v27 = *(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8);
        if ( v27 <= v26 )
          scoreDelta = 0;
        else
          scoreDelta = v27 - v26;
      }
LABEL_11:
      if ( effectiveness * (scoreDelta / 5) <= bestScore )
        goto LABEL_19;
      Unit_CalcEffectivenessA((char *)(uintptr_t)(unitRecordOffset + g_MapData + 852), 0);
      v11 = Unit_CalcEffectivenessC((__int16 *)(uintptr_t)(unitRecordOffset + g_MapData + 852));
      if ( v12 <= v11 )
        v13 = Unit_CalcEffectivenessC((__int16 *)(uintptr_t)(unitRecordOffset + g_MapData + 852));
      else
        v13 = Unit_CalcEffectivenessA((char *)(uintptr_t)(unitRecordOffset + g_MapData + 852), 0);
      effectiveness2 = v13;
      LOWORD(v15) = *(_WORD *)(uintptr_t)(scanOffset + g_MapData + 858);
      targetCol2 = (unsigned __int16)v15;
      Debug_Log(v14, v15, a3, (int)(intptr_t)aOddzial_w_zasi);
      unitRecordPtr2 = g_MapData + 852 + unitRecordOffset;
      a3 = v17;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v17, (unsigned __int16)v15)
        && (*(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
      {
        scoreDelta2 = 0;
LABEL_17:
        LOBYTE(scoreDelta2) = BATTLE_UNIT_ACTION_POINTS(unitRecordPtr2);
LABEL_18:
        bestScore = scoreDelta2 / 5 * effectiveness2;
        goto LABEL_19;
      }
      v32 = (unsigned __int16)v15;
      if ( *(char *)(uintptr_t)((unsigned __int16)v15 + g_MapData + 20 * a3 + 3134) <= 0 )
      {
        v15 = (unsigned __int16)v15;
      }
      else
      {
        v32 = g_MapData + 40 * a3;
        if ( *(__int16 *)(uintptr_t)(v32 + 2 * (unsigned __int16)v15 + 1534) == -1
          || (v33 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v33 + 852)] & 1) == 0)
          && (*(_BYTE *)(uintptr_t)(v33 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v33 + 864)) >> 5) <= 0 )
        {
          v34 = UnitBattle_MoveTrackNearWall(unitIndex, a3, (unsigned __int16)v15, a3);
          goto LABEL_61;
        }
        v15 = (unsigned __int16)v15;
      }
      v34 = (int *)UnitBattle_MoveTrackNear(unitIndex, v32, v15, a3);
LABEL_61:
      movePath2 = v34;
      if ( !v34 )
      {
        v36 = 31 * unitIndex + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)] )
        {
          if ( (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
            movePath2 = UnitBattle_MoveTrackForce(unitIndex, (unsigned __int16)v15, a3);
        }
      }
      if ( !movePath2 )
      {
        scoreDelta2 = -1;
        goto LABEL_18;
      }
      if ( !*movePath2 )
      {
        j__nfree_();
        goto LABEL_17;
      }
      v37 = g_MapData + 31 * unitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v37 + 852)]
        && (*(_BYTE *)(uintptr_t)(v37 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v37 + 864)) >> 5) > 0 )
      {
        savedRow2 = BATTLE_UNIT_GRID_X(unitRecordPtr2);
        savedCol2 = BATTLE_UNIT_GRID_Y(unitRecordPtr2);
        HIWORD(packedTrackStep2) = 0;
        if ( *movePath2 )
        {
          while ( !UnitBattle_IsTileWithinRange(unitIndex, a3, targetCol2) )
          {
            v41 = *v39 - 1;
            *v39 = v41;
            packedTrackStep2 = v39[v41 + 1];
            if ( HIWORD(packedTrackStep2) > (int)*(unsigned __int8 *)(uintptr_t)(unitRecordPtr2 + 8) )
              goto LABEL_89;
            BATTLE_UNIT_GRID_X(unitRecordPtr2) = (unsigned __int8)packedTrackStep2;
            BATTLE_UNIT_GRID_Y(unitRecordPtr2) = BYTE1(packedTrackStep2);
            if ( !*v39 )
              goto LABEL_86;
          }
          BATTLE_UNIT_GRID_X(unitRecordPtr2) = savedRow2;
          BATTLE_UNIT_GRID_Y(unitRecordPtr2) = savedCol2;
          j__nfree_();
          LOBYTE(v40) = BATTLE_UNIT_ACTION_POINTS(unitRecordPtr2);
          if ( v40 > HIWORD(packedTrackStep2) )
          {
            scoreDelta2 = v40 - HIWORD(packedTrackStep2);
            goto LABEL_18;
          }
LABEL_83:
          scoreDelta2 = 0;
          goto LABEL_18;
        }
LABEL_86:
        if ( !UnitBattle_IsTileWithinRange(unitIndex, a3, targetCol2) )
        {
LABEL_89:
          BATTLE_UNIT_GRID_X(unitRecordPtr2) = savedRow2;
          BATTLE_UNIT_GRID_Y(unitRecordPtr2) = savedCol2;
          j__nfree_();
          goto LABEL_18;
        }
        BATTLE_UNIT_GRID_X(unitRecordPtr2) = savedRow2;
        BATTLE_UNIT_GRID_Y(unitRecordPtr2) = savedCol2;
        if ( *(unsigned __int8 *)(uintptr_t)(unitRecordPtr2 + 8) > (int)HIWORD(packedTrackStep2) )
        {
          j__nfree_();
          scoreDelta2 = *(unsigned __int8 *)(uintptr_t)(unitRecordPtr2 + 8) - v42;
          goto LABEL_18;
        }
      }
      else if ( *movePath2 )
      {
        trackStep2 = movePath2[1];
        j__nfree_();
        LOBYTE(v38) = BATTLE_UNIT_ACTION_POINTS(unitRecordPtr2);
        if ( v38 <= HIWORD(trackStep2) )
          scoreDelta2 = 0;
        else
          scoreDelta2 = v38 - HIWORD(trackStep2);
        goto LABEL_18;
      }
      j__nfree_();
      goto LABEL_83;
    }
LABEL_19:
    scanOffset += 31;
  }
  while ( scanOffset != 682 );
  return bestScore;
}
// 437B33: variable 'v5' is possibly undefined
// 437BA1: variable 'v9' is possibly undefined
// 437BF2: variable 'v10' is possibly undefined
// 437C31: variable 'v12' is possibly undefined
// 437C7F: variable 'v14' is possibly undefined
// 437C99: variable 'v17' is possibly undefined
// 437CEB: variable 'v18' is possibly undefined
// 437E93: variable 'v26' is possibly undefined
// 437F31: variable 'v29' is possibly undefined
// 437F4F: variable 'v28' is possibly undefined
// 437FC6: variable 'v31' is possibly undefined
// 438167: variable 'v38' is possibly undefined
// 438203: variable 'v40' is possibly undefined
// 438221: variable 'v39' is possibly undefined
// 43829A: variable 'v42' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
