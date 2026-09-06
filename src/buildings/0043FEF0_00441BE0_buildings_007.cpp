/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
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
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0043FEF0) --------------------------------------------------------
int  Temple_ShowOutcomePopup(int messageTextPtr, int iconChar, int a3, int playSound, DWORD gameContext)
{
  _DWORD *spriteSetPtr; // eax
  int SpriteWidth; // edx
  int v7; // ecx
  int maxExtent; // eax
  _DWORD *Surface; // eax
  int surface; // edi
  int SpriteForChar; // eax
  int v12; // eax
  DWORD deviceMethodsPtr; // ebp
  int v14; // ecx
  int v15; // ecx
  int artifactSoundId; // eax
  int iconSprite; // eax
  int v19; // ecx
  _DWORD *spriteSet; // [esp+38h] [ebp-28h] BYREF
  int playSoundFlag; // [esp+3Ch] [ebp-24h]
  DWORD deviceMethods; // [esp+40h] [ebp-20h]
  int messageText; // [esp+44h] [ebp-1Ch]
  int popupHeight; // [esp+48h] [ebp-18h]
  int iconIndex; // [esp+4Ch] [ebp-14h]

  messageText = messageTextPtr;
  iconIndex = iconChar;
  playSoundFlag = playSound;
  spriteSetPtr = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a3, playSound, gameContext);
  if ( spriteSetPtr )
    spriteSetPtr = DLXSpriteSet_Load(spriteSetPtr, (const void*)(intptr_t)(playSound));
  spriteSet = spriteSetPtr;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0x16u);
  maxExtent = v7 + 6;
  if ( (unsigned __int16)SpriteWidth > v7 + 6 )
    maxExtent = SpriteWidth;
  popupHeight = maxExtent;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, playSound, gameContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, popupHeight);
  surface = (int)(intptr_t)Surface;
  Render_FillRect(0, Surface, 150, 0, SCREEN_MAX_X, popupHeight + 149, 0, 0);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 22);
  deviceMethods = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceMethods + 52))(
    150,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0x16u);
  v12 = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 23);
  deviceMethods = *((_DWORD *)g_RenderDevice + 46);
  deviceMethodsPtr = deviceMethods;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceMethods + 52))(
    156,
    v12,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  if ( iconIndex != -1 )
  {
    iconSprite = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, iconIndex);
    deviceMethodsPtr = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceMethodsPtr + 52))(
      285,
      iconSprite,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  Render_ReleaseSurface(17, deviceMethodsPtr);
  UI_DrawTextFmt(surface, 70, 569, 210, 6, (const char*)(intptr_t)(messageText));
  Render_Present((int)(intptr_t)g_RenderState);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  while ( !DD_IsFlipping(v14) && !DD_IsLost(v15) )
    DD_Pump(v19, 0);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  if ( playSoundFlag )
  {
    artifactSoundId = iconIndex;
    if ( iconIndex == -1 )
      artifactSoundId = 7;
    Audio_PlayArtifactSound(artifactSoundId);
  }
  Render_Pump();
  Render_FillRect((_DWORD *)(uintptr_t)surface, 0, 0, 0, SCREEN_MAX_X, popupHeight - 1, 0, 0x96u);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( surface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)surface, 2);
  return DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
}
// 43FF56: variable 'v7' is possibly undefined
// 44008E: variable 'v14' is possibly undefined
// 44015C: variable 'v15' is possibly undefined
// 44016D: variable 'v19' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (004401A0) --------------------------------------------------------
_DWORD * Temple_Random(_DWORD *outcomeTable, int a2, int a3_promoted, DWORD a4)
{
  char a3 = (char)a3_promoted;
  int totalWeight; // ecx
  _DWORD *scanPtr; // eax
  int entryWeight; // ebx
  int entrySentinel; // edi
  signed int roll; // ebx
  int v11; // ecx
  signed int cumulative; // edx
  _DWORD *result; // eax

  Debug_Log(a2, a3, a4, (int)(intptr_t)aTemple_random);
  totalWeight = 0;
  scanPtr = outcomeTable;
  if ( *outcomeTable != -1 )
  {
    do
    {
      entryWeight = scanPtr[1];
      entrySentinel = scanPtr[6];
      scanPtr += 6;
      totalWeight += entryWeight;
    }
    while ( entrySentinel != -1 );
  }
  roll = Rng_RandRange(0, totalWeight - 1);
  Debug_Log(v11, roll, a4, (int)(intptr_t)a__RDSum_probD);
  for ( result = outcomeTable; ; result += 6 )
  {
    cumulative += result[1];
    if ( cumulative >= roll )
      break;
  }
  return result;
}
// 4401E5: variable 'v11' is possibly undefined
// 4401EF: variable 'v12' is possibly undefined

//----- (00440250) --------------------------------------------------------
void  Temple_ProcessGift(DWORD giftType, __int16 *unitStack, int tileY, char tileX, double gameTime)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  __int16 *slotPtr; // eax
  int slotIndex; // edx
  int slotUnitType; // ecx
  int v14; // ecx
  __int16 *slotPtrB; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // ecx

  Debug_Log(tileY, tileX, giftType, (int)(intptr_t)aTemple_process);
  switch ( giftType )
  {
    case TEMPLE_GIFT_SPAWN_UNITS:
      Temple_SpawnGiftUnitGroup(tileX, v7, gameTime);
      return;
    case TEMPLE_GIFT_KILL_STACK:
      UI_StartTileBlinkFlash(*unitStack, unitStack[1], v8);
      Unit_Kill((int)(intptr_t)unitStack, tileX, giftType, gameTime);
      return;
    case TEMPLE_GIFT_REST:
      UnitStack_AdjustFatigueByPredicate(unitStack, -100, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v9);
      return;
    case TEMPLE_GIFT_BLESS_MORALE:
      UnitStack_AdjustMoraleByPredicate(unitStack, 20, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v10);
      return;
    case TEMPLE_GIFT_HEAL_FULL:
      slotPtr = unitStack;
      slotIndex = v8 ^ v7;
      do
      {
        slotUnitType = slotPtr[3];
        if ( slotUnitType == -1 )
          break;
        slotPtr = (__int16 *)((char *)slotPtr + 31);
        ++slotIndex;
        *((_BYTE *)slotPtr - 16) = 100;
      }
      while ( slotIndex < 10 );
      goto LABEL_9;
    case TEMPLE_GIFT_HEAL_FULL_RESET:
      slotPtrB = unitStack;
      slotIndex = v8 ^ v7;
      do
      {
        slotUnitType = slotPtrB[3];
        if ( slotUnitType == -1 )
          break;
        slotPtrB = (__int16 *)((char *)slotPtrB + 31);
        *((_BYTE *)slotPtrB - 16) = 100;
        ++slotIndex;
        *((_BYTE *)slotPtrB - 15) = 0;
      }
      while ( slotIndex < 10 );
LABEL_9:
      Rules_SyncArmyFactStrength(unitStack, slotIndex, slotUnitType, tileX, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v14);
      return;
    case TEMPLE_GIFT_CYCLE_ORDERS_3:
      do
        UnitStack_CycleAllSlotOrders(unitStack, giftType, gameTime);
      while ( v17 < 3 );
      goto LABEL_15;
    case TEMPLE_GIFT_BLESS_MORALE_MINOR:
      UnitStack_AdjustMoraleByPredicate(unitStack, 2, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), unitStack[1], v18);
      return;
    case TEMPLE_GIFT_CYCLE_ORDERS_2:
      do
        UnitStack_CycleAllSlotOrders(unitStack, giftType, gameTime);
      while ( v19 < 2 );
LABEL_15:
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), gameData + 200 * *unitStack, v16);
      break;
    case TEMPLE_GIFT_GOLD_100:
      Temple_SpawnGiftGoldCargoStack(100, tileX, *((_BYTE *)unitStack + 4), v7, gameTime);
      break;
    case TEMPLE_GIFT_GOLD_200:
      Temple_SpawnGiftGoldCargoStack(200, tileX, *((_BYTE *)unitStack + 4), v7, gameTime);
      break;
    case TEMPLE_GIFT_GOLD_50:
      Temple_SpawnGiftGoldCargoStack(50, tileX, *((_BYTE *)unitStack + 4), v7, gameTime);
      break;
    case TEMPLE_GIFT_GOLD_300:
      Temple_SpawnGiftGoldCargoStack(300, tileX, *((_BYTE *)unitStack + 4), v7, gameTime);
      break;
    case TEMPLE_GIFT_CURSE_MORALE:
      UnitStack_AdjustMoraleByPredicate(unitStack, -20, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v20);
      break;
    case TEMPLE_GIFT_CURSE_MORALE_FATIGUE:
      UnitStack_AdjustMoraleByPredicate(unitStack, -1, UnitSlot_PredicateAlways, giftType, gameTime);
      UnitStack_AdjustFatigueByPredicate(unitStack, 50, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v21);
      break;
    default:
      return;
  }
}
// 44027F: variable 'v7' is possibly undefined
// 44028F: variable 'v8' is possibly undefined
// 4402E5: variable 'v9' is possibly undefined
// 440334: variable 'v10' is possibly undefined
// 440393: variable 'v14' is possibly undefined
// 44040C: variable 'v17' is possibly undefined
// 440442: variable 'v16' is possibly undefined
// 440490: variable 'v18' is possibly undefined
// 4404A6: variable 'v19' is possibly undefined
// 440588: variable 'v20' is possibly undefined
// 4405E8: variable 'v21' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00440600) --------------------------------------------------------
int  Temple_UnitGetInto(int stack_index, int tile_x, int tile_y, DWORD gameContext, double gameTime)
{
  int v6 CLASH95_UNUSED; // edx
  __int16 *unitStack; // ebp
  int playerData; // eax
  _DWORD *outcomeTable; // esi
  signed int siteCategory; // eax
  int playerDataOffset; // ebx
  int ownCultFlag; // ecx
  int v13; // ecx
  int result; // eax
  int missionIndex; // ecx
  _DWORD *outcomeTablePtr; // edi
  int v17; // ecx
  DWORD *outcomePtr; // esi
  int activeMission; // edx
  int playerDataOffset2; // edx
  int isHumanPlayer; // ecx
  int isOwnCult; // ebx
  const char *transitionName; // eax
  int v24; // ecx
  int siteRowBase; // ebx
  int siteOverlayWord; // ecx
  int ownCultFlagValue; // ecx
  int giftEmptyTexts[3]; // [esp+0h] [ebp-3Ch]
  int giftRewardTexts[3]; // [esp+Ch] [ebp-30h]
  int sacrilegeTexts[3]; // [esp+18h] [ebp-24h]
  int siteX; // [esp+24h] [ebp-18h]
  int siteY; // [esp+28h] [ebp-14h]

  siteX = tile_x;
  siteY = tile_y;
  Debug_Log(tile_x, tile_y, gameContext, (int)(intptr_t)aTemple_unitget);
  unitStack = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
  Diagnostics_TraceWorldMapActionEvent("temple_unit_getinto_enter", stack_index, tile_x, tile_y, MapTile_GetReligiousSiteCategory(tile_x, tile_y));
  playerData = gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
  if ( *(_DWORD *)(uintptr_t)(playerData + 140063) )
  {
    if ( *(_DWORD *)(uintptr_t)(playerData + 140051) )
      outcomeTable = (_DWORD*)(&g_TempleGiftOutcomeTable_OwnCultHuman);
    else
      outcomeTable = (_DWORD*)(&g_TempleGiftOutcomeTable_OwnCultAI);
  }
  else if ( *(_DWORD *)(uintptr_t)(playerData + 140051) )
  {
    outcomeTable = (_DWORD*)(&g_TempleGiftOutcomeTable_ForeignCultHuman);
  }
  else
  {
    outcomeTable = (_DWORD*)(&g_TempleGiftOutcomeTable_ForeignCultAI);
  }
  siteCategory = MapTile_GetReligiousSiteCategory(siteX, siteY);
  playerDataOffset = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
  ownCultFlag = *(_DWORD *)(uintptr_t)(gameData + playerDataOffset + 140063);
  if ( ownCultFlag && (siteCategory == 3 || siteCategory == 4)
    || (LOBYTE(playerDataOffset) = gameData, !*(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData + 140063))
    && (siteCategory == 1 || siteCategory == 2) )
  {
    Debug_Log(ownCultFlag, playerDataOffset, (DWORD)(intptr_t)unitStack, (int)(intptr_t)aTemple_unitg_0);
    sacrilegeTexts[0] = (int)(intptr_t)g_TempleSacrilegeUnitKilledTexts[0];
    sacrilegeTexts[1] = (int)(intptr_t)g_TempleSacrilegeUnitKilledTexts[1];
    sacrilegeTexts[2] = (int)(intptr_t)g_TempleSacrilegeUnitKilledTexts[2];
    if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + 140051) )
    {
      LOBYTE(playerDataOffset) = 1;
      Temple_ShowOutcomePopup(sacrilegeTexts[(unsigned __int8)g_LanguageIndex], 0, v13, 1, (DWORD)(intptr_t)unitStack);
    }
    UI_StartTileBlinkFlash(*unitStack, unitStack[1], v13);
    return Unit_Kill((int)(intptr_t)unitStack, playerDataOffset, (DWORD)(intptr_t)unitStack, gameTime);
  }
  else
  {
    missionIndex = ACTIVE_MISSION_INDEX;
    if ( missionIndex == 1 || missionIndex == 11 )
    {
      result = 14 * siteY;
      ++*(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * siteX + TILE_TERRAIN_RECORD_STRIDE * siteY + 2);
      Diagnostics_TraceWorldMapActionEvent(
        "temple_unit_getinto_mission_site_increment",
        stack_index,
        siteX,
        siteY,
        MapTile_GetReligiousSiteCategory(siteX, siteY));
    }
    else if ( siteCategory == 2 || siteCategory == 4 )
    {
      Debug_Log(missionIndex, gameData, (DWORD)(intptr_t)unitStack, (int)(intptr_t)aTemple_unitg_2);
      giftRewardTexts[0] = (int)(intptr_t)g_TempleGiftRewardText[0];
      giftRewardTexts[1] = (int)(intptr_t)g_TempleGiftRewardText[1];
      giftRewardTexts[2] = (int)(intptr_t)g_TempleGiftRewardText[2];
      giftEmptyTexts[0] = (int)(intptr_t)g_TempleGiftEmptyText[0];
      giftEmptyTexts[1] = (int)(intptr_t)g_TempleGiftEmptyText[1];
      giftEmptyTexts[2] = (int)(intptr_t)g_TempleGiftEmptyText[2];
      result = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData;
      if ( *(_DWORD *)(uintptr_t)(result + 140051) )
      {
        ownCultFlagValue = *(_DWORD *)(uintptr_t)(result + 140063);
        if ( ownCultFlagValue )
          return Temple_ShowOutcomePopup(giftRewardTexts[(unsigned __int8)g_LanguageIndex], -1, ownCultFlagValue, 0, (DWORD)(intptr_t)unitStack);
        else
          return Temple_ShowOutcomePopup(giftEmptyTexts[(unsigned __int8)g_LanguageIndex], -1, 0, 0, (DWORD)(intptr_t)unitStack);
      }
    }
    else
    {
      outcomeTablePtr = outcomeTable;
      outcomePtr = Temple_Random(outcomeTable, missionIndex, gameData, (DWORD)(intptr_t)unitStack);
      activeMission = ACTIVE_MISSION_INDEX;
      if ( (activeMission == 2 || activeMission == 6 || activeMission == 12 || activeMission == 16)
        && *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData + 140051) )
      {
        if ( ACTIVE_MISSION_INDEX == 2 && siteX == 95 && siteY == 16
          || ACTIVE_MISSION_INDEX == 12 && siteX == 58 && siteY == 77 )
        {
          outcomePtr = (DWORD *)&g_TempleGiftOutcomeTable_OwnCultHuman;
        }
        else
        {
          while ( *outcomePtr && *outcomePtr != 15 )
            outcomePtr = Temple_Random(outcomeTablePtr, v17, playerDataOffset, (DWORD)(intptr_t)unitStack);
        }
      }
      Debug_Log(v17, playerDataOffset, (DWORD)(intptr_t)unitStack, (int)(intptr_t)aTemple_unitg_1);
      playerDataOffset2 = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
      isHumanPlayer = *(_DWORD *)(uintptr_t)(playerDataOffset2 + gameData + 140051);
      if ( isHumanPlayer )
      {
        isOwnCult = *(_DWORD *)(uintptr_t)(playerDataOffset2 + gameData + 140063);
        if ( isOwnCult )
          transitionName = aSw_chs;
        else
          transitionName = aSw_pog;
        Win_PlayModeChangeFrameTransition(transitionName, 1, isHumanPlayer, isOwnCult, (DWORD)(intptr_t)unitStack);
        Temple_ShowOutcomePopup(outcomePtr[(unsigned __int8)g_LanguageIndex + 3], outcomePtr[2], v24, 1, (DWORD)(intptr_t)unitStack);
      }
      Temple_ProcessGift(*outcomePtr, unitStack, siteY, siteX, gameTime);
      siteRowBase = gameData + TILE_TERRAIN_ROW_STRIDE * siteX;
      LOWORD(siteOverlayWord) = *(_WORD *)(uintptr_t)(siteRowBase + 14 * siteY + 2);
      *(_WORD *)(uintptr_t)(siteRowBase + 14 * siteY + 2) = ++siteOverlayWord;
      return (int)(intptr_t)Rules_RetractTempleFact(siteX, siteOverlayWord, siteRowBase, (DWORD)(intptr_t)unitStack);
    }
  }
  return result;
}
// 440643: variable 'v6' is possibly undefined
// 4406F5: variable 'v13' is possibly undefined
// 4407FC: variable 'v17' is possibly undefined
// 440850: variable 'v24' is possibly undefined
// 4408AD: variable 'v26' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 5162F0: using guessed type char *off_5162F0[9];
// 5162FC: using guessed type char *off_5162FC[6];
// 516308: using guessed type char *off_516308[3];
// 5202E4: using guessed type int gameData;

//----- (00440A20) --------------------------------------------------------
int  Temple_OutcomePopup_HandleCloseClick(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_TempleOutcomePopupCloseFlag = v4;
  return result;
}
// 440A2B: variable 'v4' is possibly undefined
// 543C84: using guessed type int dword_543C84;

//----- (00440A40) --------------------------------------------------------
_DWORD * Temple_OutcomePopup_HandleDestroyBuildingClick(int widget, int delayTicks, char a3, DWORD gameContext, double gameTime)
{
  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_TempleOutcomePopupCloseFlag = 1;
  return Building_Destroy(g_BuildingUIRecordPtr, a3, gameContext, gameTime);
}
// 543C80: using guessed type int dword_543C80;
// 543C84: using guessed type int dword_543C84;

//----- (00440A60) --------------------------------------------------------
int  Temple_OutcomePopup_HandleAcceptUnitsClick(int widget, int delayTicks, double gameTime)
{
  int result; // eax
  int selectedWriteIdx; // ecx
  int selectedCount; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int lastFrameTick; // ebx
  unsigned int nowTick; // eax
  unsigned int v12; // edx
  int animFrame; // ebp
  int i; // esi
  int SpriteForChar; // eax
  int v16; // ecx
  int prevSpriteFrame; // edi
  int v18 CLASH95_UNUSED; // [esp+0h] [ebp-50h]
  int selectedSlots[11]; // [esp+4h] [ebp-4Ch] BYREF
  int v20; // [esp+30h] [ebp-20h]
  int spriteFrame; // [esp+34h] [ebp-1Ch]

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  result = 0;
  selectedWriteIdx = 0;
  selectedCount = 0;
  do
  {
    if ( g_BuildingUnitsPopupSelectedSlots[result] )
    {
      ++selectedCount;
      ++selectedWriteIdx;
      selectedSlots[selectedCount - 1] = result;
    }
    ++result;
  }
  while ( result < 10 );
  selectedSlots[selectedWriteIdx] = -1;
  if ( selectedSlots[0] != -1 )
  {
    Building_UnitsLeave((unsigned __int8 *)(uintptr_t)g_BuildingUIRecordPtr, selectedSlots, gameTime);
    Audio_PlaySoundEffectByName(aDclose_1, 64);
    spriteFrame = 12;
    g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
    lastFrameTick = Time_Now(v8, v7);
    do
    {
      do
        nowTick = Time_Now(v9, lastFrameTick + 10);
      while ( nowTick < v12 );
      animFrame = spriteFrame;
      for ( i = 0; i < 10; ++i )
      {
        if ( g_BuildingUnitsPopupSelectedSlots[i] )
        {
          SpriteForChar = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, animFrame);
          v18 = 0;
          v20 = *((_DWORD *)g_RenderDevice + 46);
          (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(v20 + 52))(
            v16 + 148,
            SpriteForChar,
            -1,
            -1,
            -1,
            -1,
            1,
            0,
            0);
        }
      }
      prevSpriteFrame = spriteFrame;
      result = Time_Now(v9, v12);
      lastFrameTick = result;
      spriteFrame = prevSpriteFrame - 1;
    }
    while ( prevSpriteFrame != 5 );
  }
  g_TempleOutcomePopupCloseFlag = 1;
  return result;
}
// 440AE9: variable 'v8' is possibly undefined
// 440AE9: variable 'v7' is possibly undefined
// 440AF3: variable 'v9' is possibly undefined
// 440AFA: variable 'v12' is possibly undefined
// 440B74: variable 'v16' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 543C54: using guessed type int dword_543C54;
// 543C80: using guessed type int dword_543C80;
// 543C84: using guessed type int dword_543C84;

//----- (00440BB0) --------------------------------------------------------
void * RenderHook_DemoText(int a1, char a2, DWORD renderContext)
{
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int slotIndex; // esi
  int slotOffset; // edi
  DWORD renderVtable; // ebp
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  __int16 spriteHeight; // ax
  void *result; // eax
  __int16 surfaceWidth; // bx
  __int16 SpriteHeight; // ax
  int v16; // ecx
  unsigned __int16 spriteWidthMinus1; // [esp+60h] [ebp-38h]
  void *savedRenderDevice; // [esp+70h] [ebp-28h]
  _DWORD *surface; // [esp+74h] [ebp-24h]
  int spriteSetIndex; // [esp+78h] [ebp-20h]

  savedRenderDevice = g_RenderDevice;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, a1, a2, renderContext);
  if ( Surface )
  {
    surfaceWidth = DLX_GetSpriteWidth(g_DemoTextDLXSpriteSet, 0) + 1;
    SpriteHeight = DLX_GetSpriteHeight(g_DemoTextDLXSpriteSet, 0);
    Surface = Render_CreateSurface(v16, SpriteHeight + 1, surfaceWidth);
  }
  surface = Surface;
  g_RenderDevice = (_UNKNOWN*)(Surface);
  SpriteForChar = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 0);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    0,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  slotIndex = 0;
  slotOffset = 0;
  spriteSetIndex = 0;
  do
  {
    if ( *(__int16 *)(uintptr_t)(slotOffset + g_BuildingUIRecordPtr + 18) == -1 )
    {
      DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 5);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
      DLX_GetSpriteForChar(g_BuildingUnitsPopupSlotSpriteSets[spriteSetIndex], 0);
      renderVtable = *((_DWORD *)g_RenderDevice + 46);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderVtable + 52))(-1, -1, -1, -1, 1, 0, 0);
      if ( g_BuildingUnitsPopupSelectedSlots[slotIndex] )
      {
        v9 = DLX_GetSpriteForChar(g_MarksSpriteSet, 5);
        renderVtable = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderVtable + 52))(
          78 * (slotIndex / 5) + 50,
          v9,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( *(_BYTE *)(uintptr_t)(slotOffset + g_BuildingUIRecordPtr + 28) )
      {
        v10 = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 3);
        renderVtable = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderVtable + 52))(
          v11 + 49,
          v10,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      Render_ReleaseSurface(7, renderVtable);
      UI_DrawTextFmt(
        slotOffset,
        (unsigned __int16)g_DemoTextColumnXOffsets[slotIndex % 5],
        (unsigned __int16)g_DemoTextColumnXOffsets[slotIndex % 5] + 32,
        78 * (slotIndex / 5) + 98,
        3,
        (const char*)(intptr_t)((int)(intptr_t)aD_78));
    }
    slotOffset += 31;
    ++slotIndex;
    ++spriteSetIndex;
  }
  while ( slotIndex < 10 );
  Render_Pump();
  spriteWidthMinus1 = DLX_GetSpriteWidth(g_DemoTextDLXSpriteSet, 0) - 1;
  spriteHeight = DLX_GetSpriteHeight(g_DemoTextDLXSpriteSet, 0);
  Render_BlitSurfaceRect(surface, 0, 0, 0, spriteHeight - 1, spriteWidthMinus1, 0xC8u, 0x64u);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( surface )
    RenderSurface_InvokeSlot0(surface, 2);
  result = savedRenderDevice;
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return result;
}
// 440E4A: variable 'v16' is possibly undefined
// 440D44: variable 'v11' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 516320: using guessed type __int16 word_516320[8];
// 5202C8: using guessed type int dword_5202C8;
// 543C54: using guessed type int dword_543C54;
// 543C58: using guessed type int dword_543C58[];
// 543C80: using guessed type int dword_543C80;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004410B0) --------------------------------------------------------
int  UI_DemoTextPresent(int unitStackId, int a2, char spriteVariant, DWORD renderContext)
{
  _DWORD *dlxSpriteSet; // eax
  int slotOffset; // esi
  int spriteSetOffset; // ecx
  int slotRecordPtr; // eax
  char slotVariantDigit; // bl
  int v10; // ecx
  _DWORD *slotSpriteSet; // eax
  unsigned __int8 *selectedSlot; // ebx
  int v13; // ecx
  void *v14; // ecx
  int freeIndex; // edx
  int nullSpriteSet; // ecx
  unsigned int hoverRow; // edi
  int columnIndex; // edx
  int relativeMouseX; // ecx
  int columnX; // eax
  int v22; // ecx
  signed int hasSpecialPersonage; // eax
  int v24; // edx
  char unitInfoBuffer[100]; // [esp+0h] [ebp-74h] BYREF
  void *savedRenderDevice; // [esp+64h] [ebp-10h]
  int v27 CLASH95_UNUSED; // [esp+70h] [ebp-4h]

  v27 = a2;
  savedRenderDevice = g_RenderDevice;
  g_BuildingUIRecordPtr = UNIT_RECORD(unitStackId);
  g_TempleOutcomePopupCloseFlag = 0;
  dlxSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a2, spriteVariant, renderContext);
  if ( dlxSpriteSet )
    dlxSpriteSet = DLXSpriteSet_Load(dlxSpriteSet, (const void*)(intptr_t)(spriteVariant));
  g_DemoTextDLXSpriteSet = (int)(intptr_t)dlxSpriteSet;
  slotOffset = 0;
  memset_(0, 0);
  do
  {
    slotRecordPtr = slotOffset + g_BuildingUIRecordPtr;
    if ( *(__int16 *)(uintptr_t)(slotOffset + g_BuildingUIRecordPtr + 18) != -1 )
    {
      slotVariantDigit = *(_BYTE *)(uintptr_t)(slotRecordPtr + 20);
      UI_BeginUnitInfo(unitInfoBuffer, *(_BYTE *)(uintptr_t)(slotRecordPtr + 18), slotVariantDigit);
      slotSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v10, slotVariantDigit, renderContext);
      if ( slotSpriteSet )
        slotSpriteSet = DLXSpriteSet_Load(slotSpriteSet, (const void*)(intptr_t)(slotVariantDigit));
      *(int *)((char *)g_BuildingUnitsPopupSlotSpriteSets + spriteSetOffset) = (int)(intptr_t)slotSpriteSet;
    }
    spriteSetOffset += 4;
    slotOffset += 31;
  }
  while ( spriteSetOffset != 40 );
  LOBYTE(selectedSlot) = 10;
  memset_(40, 0);
  RenderHook_DemoText(v13, 10, renderContext);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  g_RenderDevice = (_UNKNOWN*)(v14);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  while ( !g_TempleOutcomePopupCloseFlag )
  {
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)selectedSlot);
    selectedSlot = 0;
    hoverRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 148) / 78;
    columnIndex = 0;
    relativeMouseX = (g_MouseCursorRawX >> g_CursorCoordShift) - 200;
    do
    {
      columnX = (unsigned __int16)g_DemoTextColumnXOffsets[columnIndex];
      if ( (unsigned __int16)columnX <= relativeMouseX && relativeMouseX <= columnX + 32 )
        break;
      ++columnIndex;
      ++selectedSlot;
    }
    while ( columnIndex < 5 );
    if ( hoverRow <= 1 && (unsigned int)(intptr_t)selectedSlot <= 4 )
    {
      selectedSlot += 5 * hoverRow;
      if ( *(__int16 *)(uintptr_t)(31 * (_DWORD)(intptr_t)selectedSlot + g_BuildingUIRecordPtr + 18) != -1 )
      {
        if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
        {
          g_BuildingUnitsPopupSelectedSlots[(_DWORD)(intptr_t)selectedSlot] ^= 1u;
          Audio_PlaySoundEffectByName(aMarker, 64);
          RenderHook_DemoText(v22, (char)(intptr_t)selectedSlot, renderContext);
          Render_Begin((int)(intptr_t)g_RenderState, 0);
        }
        else if ( DD_IsLost((int)(intptr_t)g_RenderState) )
        {
          hasSpecialPersonage = Building_HasSpecialPersonageGarrisonEntries(g_BuildingUIRecordPtr);
          selectedSlot = (unsigned __int8 *)(uintptr_t)(g_BuildingUIRecordPtr + 18 + v24);
          Unit_Info(100, 100, hasSpecialPersonage, selectedSlot, renderContext, 0);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(g_DemoTextHoverWidgetTable, renderContext);
  }
  DLXSpriteSet_ReleaseAndClear(&g_DemoTextDLXSpriteSet);
  freeIndex = 0;
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  nullSpriteSet = 0;
  do
  {
    if ( nullSpriteSet != g_BuildingUnitsPopupSlotSpriteSets[freeIndex] )
    {
      nfree_(nullSpriteSet);
      g_BuildingUnitsPopupSlotSpriteSets[freeIndex] = nullSpriteSet;
    }
    ++freeIndex;
  }
  while ( freeIndex != 10 );
  return WorldMap_RedrawViewport(1);
}
// 441273: simplified comparisons for 'edi.4': !=0 && !=1 became >=2u
// 44127B: simplified comparisons for 'ebx.4': <0 || >=5 became >=5u
// 441145: variable 'v10' is possibly undefined
// 441157: variable 'v7' is possibly undefined
// 441179: variable 'v13' is possibly undefined
// 441199: variable 'v14' is possibly undefined
// 4411D8: variable 'v16' is possibly undefined
// 4411E1: variable 'v15' is possibly undefined
// 4412C5: variable 'v22' is possibly undefined
// 441332: variable 'v24' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 516320: using guessed type __int16 word_516320[8];
// 516330: using guessed type _DWORD dword_516330[3];
// 5202E4: using guessed type int gameData;
// 543C54: using guessed type int dword_543C54;
// 543C58: using guessed type int dword_543C58[];
// 543C80: using guessed type int dword_543C80;
// 543C84: using guessed type int dword_543C84;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00441350) --------------------------------------------------------
void  BattleMapFileName(char *outPath, int tileX, int tileY)
{
  unsigned __int16 primary; // bx
  unsigned __int16 secondary; // cx
  unsigned __int16 tertiary; // dx
  const char *suffix;
  int tile;

  Debug_Log(tileX, tileY, (DWORD)(intptr_t)outPath, (int)(intptr_t)aBattlemapfilen);
  strcpy(outPath, aMaps);
  tile = gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY;
  primary = *(_WORD *)(uintptr_t)tile;
  secondary = *(_WORD *)(uintptr_t)(tile + 2);
  tertiary = *(_WORD *)(uintptr_t)(tile + 4);
  if ( secondary != 0xFFFF && secondary < 7 && g_BattleMapFileSuffixByFactionTable[secondary] )
  {
    suffix = g_BattleMapFileSuffixByFactionTable[secondary] + 1;
  }
  else if ( tertiary != 0xFFFF && tertiary < 7 && g_BattleMapFileSuffixByFactionTable[tertiary] )
  {
    suffix = g_BattleMapFileSuffixByFactionTable[tertiary];
  }
  else
  {
    suffix = primary < 7 && g_BattleMapFileSuffixByFactionTable[primary] ? g_BattleMapFileSuffixByFactionTable[primary] : g_BattleMapFileSuffixByFactionTable[0];
  }
  strcat(outPath, suffix);
  outPath[strlen(outPath) + 1] = 0;
  outPath[strlen(outPath)] = Rng_RandRange(0, 1) + 48;
  strcat(outPath, a_mab);
  Debug_Log((int)(intptr_t)outPath, 0, 0, (int)(intptr_t)aBattlemapfil_0);
}
// 4413AA: variable 'v5' is possibly undefined
// 516410: using guessed type char *off_516410[7];
// 5202E4: using guessed type int gameData;

//----- (004414C0) --------------------------------------------------------
char  Str_SwapAndConcatInPlace(char *targetStr, char *otherStr)
{
  const char *readCursor; // esi
  char *writeCursor; // edi
  char *savedCopy; // edx
  char targetChar; // al
  char targetNextChar; // al
  char *otherReadCursor; // esi
  char *targetWriteCursor; // edi
  char otherChar; // al
  char otherNextChar; // al
  char *copyReadCursor; // esi
  char *appendWriteCursor; // edi
  char result; // al

  readCursor = targetStr;
  writeCursor = (char *)j_Mem_Alloc(strlen(targetStr));
  savedCopy = writeCursor;
  do
  {
    targetChar = *readCursor;
    *writeCursor = *readCursor;
    if ( !targetChar )
      break;
    targetNextChar = readCursor[1];
    readCursor += 2;
    writeCursor[1] = targetNextChar;
    writeCursor += 2;
  }
  while ( targetNextChar );
  otherReadCursor = otherStr;
  targetWriteCursor = targetStr;
  do
  {
    otherChar = *otherReadCursor;
    *targetWriteCursor = *otherReadCursor;
    if ( !otherChar )
      break;
    otherNextChar = otherReadCursor[1];
    otherReadCursor += 2;
    targetWriteCursor[1] = otherNextChar;
    targetWriteCursor += 2;
  }
  while ( otherNextChar );
  copyReadCursor = savedCopy;
  appendWriteCursor = &targetStr[strlen(targetStr)];
  do
  {
    result = *copyReadCursor;
    *appendWriteCursor = *copyReadCursor;
    if ( !result )
      break;
    result = copyReadCursor[1];
    copyReadCursor += 2;
    appendWriteCursor[1] = result;
    appendWriteCursor += 2;
  }
  while ( result );
  return result;
}
// 4730FB: using guessed type int __thiscall j_Mem_Alloc(_DWORD);

//----- (00441550) --------------------------------------------------------
char  BattleMap_GetOutcomeVariantFileName(char *outPath, int tileX, int tileY)
{
  char *name;
  int insert_offset;

  BattleMapFileName(outPath, tileX, tileY);
  name = strrchr(outPath, '\\');
  if ( name )
    ++name;
  else
    name = outPath;
  insert_offset = (tileX == 0) + 1;
  if ( name[0] == 'n' )
  {
    name[0] = 'v';
    memmove(name + insert_offset + 1, name + insert_offset, strlen(name + insert_offset) + 1);
    name[insert_offset] = 'z';
  }
  else
  {
    name[0] = 'v';
    name[insert_offset] = 'z';
  }
  return *name;
}

//----- (004415A0) --------------------------------------------------------
int  BattleMap_GetMoveSoundSurfaceClass(int tileRow, int tileCol)
{
  return (unsigned __int8)g_MoveSoundSurfaceClassTable[*(__int16 *)(uintptr_t)(40 * tileRow + g_MapData + 2 * tileCol)];
}
// 532048: using guessed type int g_MapData;

//----- (004415E0) --------------------------------------------------------
char * Sound_BuildMusicTrackPath(char *outPath, char *trackSubdir, int trackNumber)
{
  char *prefixCursor; // esi
  char *writeCursor; // edi
  char prefixChar; // al
  char prefixNextChar; // al
  char *subdirWriteCursor; // edi
  char subdirChar; // al
  char subdirNextChar; // al
  const char *pathBase; // edi
  char *numReadCursor; // esi
  char *numWriteCursor; // edi
  char numChar; // al
  char numNextChar; // al
  _BYTE numberSuffix[28]; // [esp+0h] [ebp-1Ch] BYREF

  prefixCursor = aSfxMusic;
  writeCursor = outPath;
  do
  {
    prefixChar = *prefixCursor;
    *writeCursor = *prefixCursor;
    if ( !prefixChar )
      break;
    prefixNextChar = prefixCursor[1];
    prefixCursor += 2;
    writeCursor[1] = prefixNextChar;
    writeCursor += 2;
  }
  while ( prefixNextChar );
  subdirWriteCursor = &outPath[strlen(outPath)];
  do
  {
    subdirChar = *trackSubdir;
    *subdirWriteCursor = *trackSubdir;
    if ( !subdirChar )
      break;
    subdirNextChar = trackSubdir[1];
    trackSubdir += 2;
    subdirWriteCursor[1] = subdirNextChar;
    subdirWriteCursor += 2;
  }
  while ( subdirNextChar );
  pathBase = outPath;
  sprintf_((char*)(numberSuffix), "%d.wav", trackNumber);
  numReadCursor = (char*)(numberSuffix);
  numWriteCursor = (char *)&pathBase[strlen(pathBase)];
  do
  {
    numChar = *numReadCursor;
    *numWriteCursor = *numReadCursor;
    if ( !numChar )
      break;
    numNextChar = numReadCursor[1];
    numReadCursor += 2;
    numWriteCursor[1] = numNextChar;
    numWriteCursor += 2;
  }
  while ( numNextChar );
  return outPath;
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00441670) --------------------------------------------------------
int  Sound_PlayNamedSfxFile(char *soundName, int volume)
{
  char *writeCursor; // edi
  char nameChar; // al
  char nameNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  int soundHandle; // esi
  char pathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( !g_Audio_MusicActiveFlag )
    return 0;
  qmemcpy(pathBuffer, aSfx_0, sizeof(pathBuffer));
  writeCursor = &pathBuffer[strlen(pathBuffer)];
  do
  {
    nameChar = *soundName;
    *writeCursor = *soundName;
    if ( !nameChar )
      break;
    nameNextChar = soundName[1];
    soundName += 2;
    writeCursor[1] = nameNextChar;
    writeCursor += 2;
  }
  while ( nameNextChar );
  suffixCursor = a_wav_5;
  suffixWriteCursor = &pathBuffer[strlen(pathBuffer)];
  do
  {
    suffixChar = *suffixCursor;
    *suffixWriteCursor = *suffixCursor;
    if ( !suffixChar )
      break;
    suffixNextChar = suffixCursor[1];
    suffixCursor += 2;
    suffixWriteCursor[1] = suffixNextChar;
    suffixWriteCursor += 2;
  }
  while ( suffixNextChar );
  soundHandle = CSS_PlaySound((int)(intptr_t)pathBuffer, volume, 0, 0);
  Audio_SetSoundLoopIfMusicActive(soundHandle, 0, -1);
  g_Audio_ActiveSoundHandle = soundHandle;
  return soundHandle;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;

//----- (00441720) --------------------------------------------------------
int  Music_PlayMainMapTrack(int result, int a2, int a3, DWORD gameContext)
{
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  CHAR wavPath[100]; // [esp+0h] [ebp-D0h] BYREF
  char sourcePath[100]; // [esp+64h] [ebp-6Ch] BYREF
  int v18 CLASH95_UNUSED; // [esp+C8h] [ebp-8h]
  int v19 CLASH95_UNUSED; // [esp+CCh] [ebp-4h]

  v19 = a3;
  v18 = a2;
  if ( g_Audio_MusicActiveFlag )
  {
    sprintf_(wavPath, "data\\mainmap%d.wav", result + 1);
    if ( IO_FOpen(wavPath, (unsigned __int8 *)aRb, v4, gameContext) )
    {
      fclose_(v6);
    }
    else
    {
      IO_RemoveFileByPath(v6, v5);
      IO_RemoveFileByPath(v8, v7);
      IO_RemoveFileByPath(v10, v9);
      IO_RemoveFileByPath(v12, v11);
      IO_RemoveFileByPath(v14, v13);
      sprintf_(sourcePath, "sfx\\music\\mainmap%d.wav", v15);
      loadFileSusp(sourcePath, wavPath);
    }
    g_MainMapMusicHandle = CSS_PlaySound((int)(intptr_t)wavPath, 64, 0, 2000);
    CSS_SetSoundLoop(g_MainMapMusicHandle, 0, -1);
    result = g_MainMapMusicHandle;
    g_Audio_ActiveSoundHandle = g_MainMapMusicHandle;
  }
  return result;
}
// 44175A: variable 'v4' is possibly undefined
// 441763: variable 'v6' is possibly undefined
// 4417A2: variable 'v5' is possibly undefined
// 4417AC: variable 'v8' is possibly undefined
// 4417AC: variable 'v7' is possibly undefined
// 4417B6: variable 'v10' is possibly undefined
// 4417B6: variable 'v9' is possibly undefined
// 4417C0: variable 'v12' is possibly undefined
// 4417C0: variable 'v11' is possibly undefined
// 4417CA: variable 'v14' is possibly undefined
// 4417CA: variable 'v13' is possibly undefined
// 4417DA: variable 'v15' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441800) --------------------------------------------------------
int  Audio_PauseMusicAndPlayLoopedSound(char *trackName, int trackNumber)
{
  int soundHandle; // ebx
  char pathBuffer[108]; // [esp+0h] [ebp-6Ch] BYREF

  if ( !g_Audio_MusicActiveFlag )
    return 0;
  CSS_PauseSound(g_MainMapMusicHandle, 2000);
  Sound_BuildMusicTrackPath(pathBuffer, trackName, trackNumber);
  soundHandle = CSS_PlaySound((int)(intptr_t)pathBuffer, 64, 0, 2000);
  CSS_SetSoundLoop(soundHandle, 0, -1);
  g_Audio_ActiveSoundHandle = soundHandle;
  return soundHandle;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441870) --------------------------------------------------------
int  Audio_ResumeMusicAndStopLoopedSound(int result)
{
  int soundHandle; // ebx

  soundHandle = result;
  if ( g_Audio_MusicActiveFlag )
  {
    CSS_ResumeSound(g_MainMapMusicHandle, 2000);
    CSS_SetSoundVolume(g_MainMapMusicHandle, 64, 1000);
    result = CSS_StopSound(soundHandle, 0);
    g_Audio_ActiveSoundHandle = g_MainMapMusicHandle;
  }
  return result;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (004418E0) --------------------------------------------------------
int Audio_StopMainMusic(void)
{
  return Audio_StopMusicWithFade(g_MainMapMusicHandle);
}
// 543C9C: using guessed type int dword_543C9C;

//----- (004418F0) --------------------------------------------------------
int  Audio_StopMusicWithFade(int result)
{
  if ( g_Audio_MusicActiveFlag )
  {
    result = CSS_StopSound(result, 1000);
    g_Audio_ActiveSoundHandle = -1;
  }
  return result;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;

//----- (00441900) --------------------------------------------------------
void Audio_DuckMusicVolume(void)
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundVolume(g_MainMapMusicHandle, 16, 1000);
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441930) --------------------------------------------------------
void Audio_RestoreMusicVolume(void)
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundVolume(g_MainMapMusicHandle, 64, 1000);
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441960) --------------------------------------------------------
int  Audio_SetMusicVolume(int volume, signed int fadeMs)
{
  int result; // eax

  if ( g_Audio_MusicActiveFlag )
    return CSS_SetSoundVolume(g_MainMapMusicHandle, volume, fadeMs);
  return result;
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441980) --------------------------------------------------------
void  Audio_SetSoundLoopIfMusicActive(int soundHandle, int loopStart, int loopEnd)
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundLoop(soundHandle, loopStart, loopEnd);
}
// 5174D8: using guessed type int dword_5174D8;

//----- (004419A0) --------------------------------------------------------
int  Audio_StartMainMusicIfStopped(int a1, DWORD gameContext)
{
  int result; // eax

  if ( !g_Audio_MusicActiveFlag )
  {
    g_Audio_MusicActiveFlag = 1;
    return Music_PlayMainMapTrack(*(unsigned __int8 *)(uintptr_t)(gameData + MAP_THEME_INDEX_OFFSET), a1, 1, gameContext);
  }
  return result;
}
// 5174D8: using guessed type int dword_5174D8;
// 5202E4: using guessed type int gameData;

//----- (004419D0) --------------------------------------------------------
int Audio_StopMainMusicIfPlaying(void)
{
  int result; // eax
  int v1; // ecx

  if ( g_Audio_MusicActiveFlag )
  {
    result = Audio_StopMainMusic();
    g_Audio_MusicActiveFlag = v1;
  }
  return result;
}
// 4419E2: variable 'v1' is possibly undefined
// 5174D8: using guessed type int dword_5174D8;

//----- (004419F0) --------------------------------------------------------
void Audio_SetMusicActiveFlag(void)
{
  g_Audio_MusicActiveFlag = 1;
}
// 5174D8: using guessed type int dword_5174D8;

//----- (00441A00) --------------------------------------------------------
void Audio_ClearMusicActiveFlag(void)
{
  g_Audio_MusicActiveFlag = 0;
}
// 5174D8: using guessed type int dword_5174D8;

//----- (00441A10) --------------------------------------------------------
void Audio_EnableUnitSounds(void)
{
  g_UnitSoundsEnabled = 1;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441A20) --------------------------------------------------------
void Audio_DisableUnitSounds(void)
{
  g_UnitSoundsEnabled = 0;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441A30) --------------------------------------------------------
int  Audio_PlayUnitActivateSound(int result)
{
  const char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char digitSlot[5] CLASH95_UNUSED; // [esp+1h] [ebp-69h]
  char soundPath[100]; // [esp+6h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPath, aSfxOddzialy, sizeof(soundPath));
    resourceKey = g_UnitTypeRuntimePointers[result].resource_key;
    writeCursor = &soundPath[strlen(soundPath)];
    do
    {
      keyChar = *resourceKey;
      *writeCursor = *resourceKey;
      if ( !keyChar )
        break;
      keyNextChar = resourceKey[1];
      resourceKey += 2;
      writeCursor[1] = keyNextChar;
      writeCursor += 2;
    }
    while ( keyNextChar );
    suffixCursor = aActiv1_wav;
    suffixWriteCursor = &soundPath[strlen(soundPath)];
    do
    {
      suffixChar = *suffixCursor;
      *suffixWriteCursor = *suffixCursor;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixCursor[1];
      suffixCursor += 2;
      suffixWriteCursor[1] = suffixNextChar;
      suffixWriteCursor += 2;
    }
    while ( suffixNextChar );
    digitSlot[strlen(soundPath)] = Rng_RandRange(49, 50);
    result = CSS_PlaySound((int)(intptr_t)soundPath, 64, 0, 0);
    g_LastUnitActivateSoundHandle = result;
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 543CA4: using guessed type int g_LastUnitActivateSoundHandle;

//----- (00441B00) --------------------------------------------------------
int  Audio_PlayUnitMoveOrderSound(int result)
{
  const char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char digitSlot[5] CLASH95_UNUSED; // [esp+1h] [ebp-6Dh]
  char soundPath[104]; // [esp+6h] [ebp-68h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    CSS_SetSoundVolume(g_LastUnitActivateSoundHandle, 0, 500);
    qmemcpy(soundPath, aSfxOddzialy_0, 0x64u);
    resourceKey = g_UnitTypeRuntimePointers[result].resource_key;
    writeCursor = &soundPath[strlen(soundPath)];
    do
    {
      keyChar = *resourceKey;
      *writeCursor = *resourceKey;
      if ( !keyChar )
        break;
      keyNextChar = resourceKey[1];
      resourceKey += 2;
      writeCursor[1] = keyNextChar;
      writeCursor += 2;
    }
    while ( keyNextChar );
    suffixCursor = aGo1_wav;
    suffixWriteCursor = &soundPath[strlen(soundPath)];
    do
    {
      suffixChar = *suffixCursor;
      *suffixWriteCursor = *suffixCursor;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixCursor[1];
      suffixCursor += 2;
      suffixWriteCursor[1] = suffixNextChar;
      suffixWriteCursor += 2;
    }
    while ( suffixNextChar );
    digitSlot[strlen(soundPath)] = Rng_RandRange(49, 50);
    return CSS_PlaySound((int)(intptr_t)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 543CA4: using guessed type int g_LastUnitActivateSoundHandle;

//----- (00441BE0) --------------------------------------------------------
int  Audio_PlayUnitRangedAttackSound(int result)
{
  const char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPath[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPath, aSfxOddzialy_1, sizeof(soundPath));
    resourceKey = g_UnitTypeRuntimePointers[result].resource_key;
    writeCursor = &soundPath[strlen(soundPath)];
    do
    {
      keyChar = *resourceKey;
      *writeCursor = *resourceKey;
      if ( !keyChar )
        break;
      keyNextChar = resourceKey[1];
      resourceKey += 2;
      writeCursor[1] = keyNextChar;
      writeCursor += 2;
    }
    while ( keyNextChar );
    suffixCursor = aStrzal_wav;
    suffixWriteCursor = &soundPath[strlen(soundPath)];
    do
    {
      suffixChar = *suffixCursor;
      *suffixWriteCursor = *suffixCursor;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixCursor[1];
      suffixCursor += 2;
      suffixWriteCursor[1] = suffixNextChar;
      suffixWriteCursor += 2;
    }
    while ( suffixNextChar );
    return CSS_PlaySound((int)(intptr_t)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
