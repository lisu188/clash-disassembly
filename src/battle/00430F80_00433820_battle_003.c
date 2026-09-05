/* Generated from src/recovered/battle/0042CB50_battle.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "battle_internal.h"
#include "battle_state.h"
#include "battle_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00430F80) --------------------------------------------------------
int  UnitBattle_DrawSelectedUnitPanel(int result, int restoreFlag, int a3 CLASH95_UNUSED, int a4 CLASH95_UNUSED)
{
  __int16 *unitRecord; // esi
  const BattleUnitEntry *battleUnit;
  int SpriteForChar; // eax
  DWORD v6; // ebp
  int panelBottomFrameSprite; // eax
  char v8; // bl
  int fatiguePercent; // eax
  _DWORD *Surface; // edi
  void (__fastcall **surface_methods)(_DWORD *, int);
  __int16 fatigueSurfaceWidth; // bx
  __int16 SpriteHeight; // ax
  int fatigueBarSprite; // eax
  int v14; // ecx
  _DWORD *apTextSurface; // eax
  int v16; // ecx
  DWORD apTextSurfaceHandle; // ebp
  _DWORD *apTextSurface2; // eax
  int v19; // edi
  int statusIconChar; // edx
  int statusIconSprite; // eax
  unsigned __int8 statusLevel; // al
  int statusSpriteChar; // edx
  int statusSprite; // eax
  DWORD v25; // ebp
  int orderMarkerX; // edi
  int orderMarkerSprite; // eax
  int v28; // eax
  int v29; // eax
  int v30; // edi
  int volleyMarkerSprite; // eax
  char ownerPlayerIndex; // bl
  int v33; // ecx
  _DWORD *portraitSprites; // eax
  int portraitSprite; // eax
  int shouldRestore; // edi
  unsigned __int16 v37 CLASH95_UNUSED; // cx
  char v38[92]; // [esp+B0h] [ebp-8Ch] BYREF
  int portraitHandle; // [esp+10Ch] [ebp-30h] BYREF
  int savedRestoreFlag; // [esp+110h] [ebp-2Ch]
  void *savedRenderDevice; // [esp+114h] [ebp-28h]
  DWORD v42 CLASH95_UNUSED; // [esp+120h] [ebp-1Ch]
  int i; // [esp+124h] [ebp-18h]
  int orderMarkerIndex; // [esp+128h] [ebp-14h]
  const UnitTypeRuntimeCoreMetadataRecord *unitMetadata; // [esp+12Ch] [ebp-10h]
  _DWORD *renderDeviceBackup; // [esp+130h] [ebp-Ch]
  int apTextSurface2Handle; // [esp+134h] [ebp-8h]

  savedRestoreFlag = restoreFlag;
  unitRecord = 0;
  if ( result )
  {
    unitRecord = (__int16 *)(uintptr_t)(unsigned int)result;
  }
  else if ( g_SelectedUnitIndex != -1 )
  {
    result = 31 * g_SelectedUnitIndex;
    unitRecord = (__int16 *)(uintptr_t)(unsigned int)(g_MapData + 852 + 31 * g_SelectedUnitIndex);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_panel_candidate", g_SelectedUnitIndex, result, (int)(uintptr_t)unitRecord, 0);
  if ( unitRecord )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_panel_before_slot_read", g_SelectedUnitIndex, result, (int)(uintptr_t)unitRecord, 0);
    result = *unitRecord;
    Diagnostics_TraceWorldMapActionEvent("battle_panel_after_slot_read", g_SelectedUnitIndex, result, (int)(uintptr_t)unitRecord, 0);
    if ( result != -1 )
    {
      battleUnit = (const BattleUnitEntry *)unitRecord;
      Diagnostics_TraceWorldMapActionEvent("battle_panel_enter", result, *((unsigned __int8 *)unitRecord + 2), *((char *)unitRecord + 9), *((unsigned __int8 *)unitRecord + 12) & 3);
      savedRenderDevice = g_RenderDevice;
      g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
      SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 1);
      Compat_RenderDeviceDrawMenuSprite(335, 0, SpriteForChar, 1);
      panelBottomFrameSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 3);
      v8 = 79;
      Compat_RenderDeviceDrawMenuSprite(335, 243, panelBottomFrameSprite, 1);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_frame", *unitRecord, (int)(uintptr_t)g_RenderDevice, SpriteForChar, panelBottomFrameSprite);
      fatiguePercent = *((char *)unitRecord + 9);
      unitMetadata = &g_UnitTypeRuntimeCoreMetadata[*unitRecord];
      g_BattlePanelUnitFatiguePercent = fatiguePercent;
      renderDeviceBackup = g_RenderDevice;
      if ( fatiguePercent < 100 )
      {
        Diagnostics_TraceWorldMapActionEvent("battle_panel_before_fatigue", *unitRecord, fatiguePercent, (int)(uintptr_t)renderDeviceBackup, 0);
        Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, fatiguePercent, 79, v6);
        if ( Surface )
        {
          fatigueSurfaceWidth = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 0xAu) + 1;
          SpriteHeight = DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xAu);
          Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight + 1, fatigueSurfaceWidth);
        }
        if ( Surface )
        {
          g_RenderDevice = Surface;
          fatigueBarSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 10);
          Compat_RenderDeviceDrawMenuSprite(0, 0, fatigueBarSprite, 1);
          v8 = 0;
          Render_FillRect(Surface, renderDeviceBackup, 0, 0, 88 * (100 - g_BattlePanelUnitFatiguePercent) / 100, 0x38u, 0x216u, 0x1Au);
          Compat_InvokeCompactSurfaceDestructor((int)(uintptr_t)Surface, 2);
        }
        g_RenderDevice = renderDeviceBackup;
        Diagnostics_TraceWorldMapActionEvent("battle_panel_after_fatigue", *unitRecord, (int)(uintptr_t)Surface, (int)(uintptr_t)g_RenderDevice, 0);
      }
      Render_ReleaseSurface(7, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_release7", *unitRecord, (int)(uintptr_t)g_RenderDevice, 0, 0);
      apTextSurface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v14, v8, v6);
      if ( apTextSurface )
      {
        v8 = 21;
        apTextSurface = Render_CreateSurface((int)(intptr_t)apTextSurface, 119, 21);
      }
      apTextSurfaceHandle = (DWORD)(intptr_t)apTextSurface;
      apTextSurface2 = (_DWORD *)(uintptr_t)Mem_Alloc(188, v16, v8, (DWORD)(intptr_t)apTextSurface);
      if ( apTextSurface2 )
        apTextSurface2 = Render_CreateSurface((int)(intptr_t)apTextSurface2, 119, 21);
      v19 = (int)(intptr_t)apTextSurface2;
      g_RenderDevice = (_UNKNOWN *)(uintptr_t)apTextSurfaceHandle;
      Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, (_DWORD *)(uintptr_t)apTextSurfaceHandle, 69, 500, 0x26Au, 0x59u, 0, 0);
      Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, (_DWORD *)(uintptr_t)v19, 69, 500, 0x26Au, 0x59u, 0, 0);
      apTextSurface2Handle = v19;
      UI_DrawTextFmt(v19, 0, 118, 0, 2, aD_48, g_BattlePanelUnitFatiguePercent);
      /* The x86 iterator path in Render_BlendSurfaceRect is not yet safe on SDL/x86_64. */
      Render_FillRect((_DWORD *)(uintptr_t)v19, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, 0x76u, 0x14u, 0x1F4u, 0x45u);
      Compat_InvokeCompactSurfaceDestructor((int)(uintptr_t)apTextSurfaceHandle, 2);
      Compat_InvokeCompactSurfaceDestructor(apTextSurface2Handle, 2);
      g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_ap_surfaces", *unitRecord, (int)(uintptr_t)apTextSurfaceHandle, apTextSurface2Handle, (int)(uintptr_t)g_RenderDevice);
      Render_ReleaseSurface(15, 0);
      UI_DrawTextFmt(v19, 500, 618, 106, 2, aD_49, *((unsigned __int8 *)unitRecord + 8));
      Render_ReleaseSurface(14, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_quantity", *unitRecord, *((unsigned __int8 *)unitRecord + 8), g_BattlePanelUnitFatiguePercent, 0);
      if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + 140051) )
      {
        if ( unitMetadata->base_melee_attack )
        {
          int statValue = UI_IconIndexFromStats(unitRecord);
          UI_DrawTextFmt(v19, 500, 618, 151, 2, aD_50, statValue);
        }
      }
      else
      {
        v19 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitBattlePanelQuantityIconCharBase[0] + 8);
        Compat_RenderDeviceDrawMenuSprite(498, 143, v19, 1);
      }
      if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + 140051) )
      {
        int statValue = Unit_CalcIndexB(unitRecord);
        UI_DrawTextFmt(v19, 500, 618, 219, 2, aD_51, statValue);
      }
      else
      {
        v19 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitBattlePanelAttackIconChar + 8);
        Compat_RenderDeviceDrawMenuSprite(497, 211, v19, 1);
      }
      if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + 140051) )
      {
        if ( unitMetadata->base_shot_power )
        {
          int statValue = Unit_GetBaseC(unitRecord);
          UI_DrawTextFmt(v19, 500, 618, 185, 2, aD_52, statValue);
        }
      }
      else
      {
        v19 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitBattlePanelDefenseIconChar + 8);
        Compat_RenderDeviceDrawMenuSprite(497, 177, v19, 1);
      }
      if ( (unsigned int)*((char *)unitRecord + 11) > 4 )
      {
        v28 = *((char *)unitRecord + 11);
        if ( v28 < 11 || v28 > 15 )
        {
          v29 = *((char *)unitRecord + 11);
          if ( v29 < 16 || v29 > 20 )
          {
LABEL_33:
            statusLevel = battleUnit->stance_bits & 0x03;
            if ( statusLevel )
            {
              if ( statusLevel <= 1u )
              {
                statusSpriteChar = 5;
              }
              else
              {
                if ( statusLevel != 3 )
                {
LABEL_36:
                  v25 = 0;
                  orderMarkerIndex = 0;
                  orderMarkerX = 618 - (unsigned __int16)DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xDu);
                  while ( ((battleUnit->stance_bits >> 2) & 0x03) >= orderMarkerIndex )
                  {
                    orderMarkerSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 13);
                    Compat_RenderDeviceDrawMenuSprite(orderMarkerX, 255, orderMarkerSprite, 1);
                    v25 = ++orderMarkerIndex;
                    orderMarkerX -= (unsigned __int16)DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xDu) + 1;
                  }
                  v30 = 529;
                  if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + gameData + 140051) )
                  {
                    for ( i = 0; unitMetadata->base_shot_power; v30 += 12 )
                    {
                      if ( ((battleUnit->stance_bits & 0x03) + 1 - ((battleUnit->stance_bits >> 4) & 0x07)) <= i )
                        break;
                      volleyMarkerSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 11);
                      Compat_RenderDeviceDrawMenuSprite(v30, 180, volleyMarkerSprite, 1);
                      ++i;
                    }
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitBattlePanelVolleyIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 245, v30, 1);
                  }
                  if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + gameData + 140051) )
                  {
                    UI_DrawTextFmt(v30, 500, 618, 287, 2, aD_53, (signed char)battleUnit->morale);
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitBattlePanelMoraleIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 279, v30, 1);
                  }
                  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitRecord + 2) + 140051) )
                  {
                    UI_DrawTextFmt(v30, 500, 618, 321, 2, aD_54, (signed char)battleUnit->fatigue);
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, (unsigned __int8)g_UnitPanelRow3FallbackIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 313, v30, 1);
                  }
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_before_portrait", *unitRecord, *((unsigned __int8 *)unitRecord + 2), (int)(uintptr_t)g_RenderDevice, 0);
                  ownerPlayerIndex = *((_BYTE *)unitRecord + 2);
                  UI_BeginUnitInfo(v38, *(_BYTE *)unitRecord, ownerPlayerIndex);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_path", *unitRecord, ownerPlayerIndex, (unsigned char)v38[0], (unsigned char)v38[1]);
                  portraitSprites = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v33, ownerPlayerIndex, v25);
                  if ( portraitSprites )
                    portraitSprites = DLXSpriteSet_Load(portraitSprites, v38);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_load", *unitRecord, (int)(uintptr_t)portraitSprites, 0, 0);
                  portraitSprite = DLX_GetSpriteForChar((int)(intptr_t)portraitSprites, 0);
                  Compat_RenderDeviceDrawMenuSprite(501, 24, portraitSprite, 1);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_draw", *unitRecord, (int)(uintptr_t)portraitSprites, portraitSprite, 0);
                  portraitHandle = (int)(uintptr_t)portraitSprites;
                  DLXSpriteSet_ReleaseAndClear(&portraitHandle);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_free", *unitRecord, portraitHandle, 0, 0);
                  shouldRestore = savedRestoreFlag;
                  RenderState_PumpIfRectInViewBounds(g_RenderState, 0x1F2u, 0x270u, 0xAu, 0x162u);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_rect", *unitRecord, shouldRestore, 0, 0);
                  if ( shouldRestore )
                    Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 10, 498, 0x270u, 0x162u, 0x1F2u, 0xAu);
                  Render_Present((int)(intptr_t)g_RenderState);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_present", *unitRecord, 0, 0, 0);
                  Tooltip_ShowText(3, UnitType_GetLocalizedName((unit_type)*unitRecord), 0);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_tooltip", *unitRecord, (int)(uintptr_t)savedRenderDevice, 0, 0);
                  result = 0;
                  g_RenderDevice = savedRenderDevice;
                  return result;
                }
                statusSpriteChar = 6;
              }
            }
            else
            {
              statusSpriteChar = 4;
            }
            statusSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, statusSpriteChar);
            Compat_RenderDeviceDrawMenuSprite(488, 243, statusSprite, 1);
            goto LABEL_36;
          }
          statusIconChar = 7;
        }
        else
        {
          statusIconChar = 8;
        }
      }
      else
      {
        statusIconChar = 9;
      }
      statusIconSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, statusIconChar);
      Compat_RenderDeviceDrawMenuSprite(498, 279, statusIconSprite, 1);
      goto LABEL_33;
    }
  }
  return result;
}
// 430F80: could not find valid save-restore pair for ebx
// 430F80: could not find valid save-restore pair for edi
// 4313BD: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 43117D: variable 'v14' is possibly undefined
// 43119C: variable 'v16' is possibly undefined
// 431780: variable 'v33' is possibly undefined
// 4317EE: variable 'v37' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 514DA4: using guessed type __int16 word_514DA4[];
// 514DA6: using guessed type __int16 word_514DA6[];
// 514DC1: using guessed type char byte_514DC1;
// 514DC2: using guessed type char byte_514DC2;
// 514DC3: using guessed type char byte_514DC3;
// 514DC4: using guessed type char byte_514DC4;
// 514DC5: using guessed type char byte_514DC5;
// 5202BC: using guessed type int dword_5202BC;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 532054: using guessed type int dword_532054;
// 53210C: using guessed type int dword_53210C;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00431940) --------------------------------------------------------
int  UnitBattle_ShowWallInfoPopup(int popupX, int popupY, int tileCol, int spriteName, DWORD localTileRow)
{
  _DWORD *spriteSetAlloc; // eax
  int v6; // ecx
  _DWORD *Surface; // ebp
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // edx
  int SpriteForChar; // eax
  int wallStyleFrameIndex; // edx
  int wallStyleFrameSprite; // eax
  int ownerFlagSprite; // eax
  char v15; // bl
  __int16 spriteHeight; // ax
  int frameIndex; // esi
  int v18; // edx
  int v19; // ecx
  int flagDrawY; // edi
  int v21; // ecx
  unsigned int currentTimeMs; // eax
  unsigned int v23; // edx
  int v24; // ecx
  int flagAnimSprite; // eax
  int presentPopupX; // ebx
  __int16 presentSpriteWidth; // ax
  __int16 v28; // cx
  __int16 presentSpriteHeight; // ax
  int v30; // ecx
  _DWORD *surfaceToFree; // ebp
  unsigned __int16 spriteWidthMinus1; // [esp+3Ch] [ebp-44h]
  unsigned __int16 presentRectWidth; // [esp+3Ch] [ebp-44h]
  unsigned __int16 fillRectX; // [esp+40h] [ebp-40h]
  unsigned __int16 presentFillRectX; // [esp+40h] [ebp-40h]
  unsigned __int16 fillRectY; // [esp+44h] [ebp-3Ch]
  unsigned __int16 presentFillRectY; // [esp+44h] [ebp-3Ch]
  int labelTextByLanguage[3]; // [esp+48h] [ebp-38h]
  _DWORD *spriteSet; // [esp+54h] [ebp-2Ch] BYREF
  int lastFrameTime; // [esp+58h] [ebp-28h]
  int savedSpriteName CLASH95_UNUSED; // [esp+5Ch] [ebp-24h]
  int savedPopupY; // [esp+60h] [ebp-20h]
  int flagDrawX; // [esp+64h] [ebp-1Ch]
  _DWORD *savedSurface; // [esp+68h] [ebp-18h]
  int savedTileCol CLASH95_UNUSED; // [esp+6Ch] [ebp-14h]
  int savedPopupX; // [esp+70h] [ebp-10h]

  savedPopupX = popupX;
  savedPopupY = popupY;
  savedSpriteName = spriteName;
  savedTileCol = tileCol;
  spriteSetAlloc = (_DWORD *)(uintptr_t)Mem_Alloc(4112, tileCol, spriteName, localTileRow);
  if ( spriteSetAlloc )
    spriteSetAlloc = DLXSpriteSet_Load(spriteSetAlloc, spriteName);
  spriteSet = spriteSetAlloc;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v6, spriteName, localTileRow);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 0xCu);
    SpriteHeight = DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xCu);
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  }
  g_RenderDevice = Surface;
  Render_ReleaseSurface(7, (DWORD)(intptr_t)Surface);
  SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, v10);
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
  wallStyleFrameIndex = *(_DWORD *)(uintptr_t)(g_MapData + 820) + 14;
  savedSurface = Surface;
  wallStyleFrameSprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, wallStyleFrameIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    17,
    wallStyleFrameSprite,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  labelTextByLanguage[0] = (int)(intptr_t)g_WallInfoPopupLabelTexts[0];
  labelTextByLanguage[1] = (int)(intptr_t)g_WallInfoPopupLabelTexts[1];
  labelTextByLanguage[2] = (int)(intptr_t)g_WallInfoPopupLabelTexts[2];
  UI_DrawTextFmt((int)(intptr_t)&spriteSet, 51, 189, 5, 3, labelTextByLanguage[(unsigned __int8)g_LanguageIndex]);
  Render_ReleaseSurface(14, (DWORD)(intptr_t)Surface);
  UI_DrawTextFmt((int)(intptr_t)&spriteSet, 0, 111, 53, 2, (int)(intptr_t)aD_34);
  UI_DrawTextFmt((int)(intptr_t)&spriteSet, 0, 177, 53, 2, (int)(intptr_t)aD_35);
  ownerFlagSprite = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 8 * *(_DWORD *)(uintptr_t)(g_MapData + 840));
  v15 = 0;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    5,
    ownerFlagSprite,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_Pump();
  fillRectY = savedPopupY;
  fillRectX = savedPopupX;
  spriteWidthMinus1 = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 0xCu) - 1;
  spriteHeight = DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xCu);
  frameIndex = 0;
  Render_FillRect(Surface, 0, 0, 0, spriteHeight - 1, spriteWidthMinus1, fillRectX, fillRectY);
  g_RenderDevice = &g_MainRenderDevice;
  lastFrameTime = Time_Now(v19, v18);
  flagDrawY = savedPopupY + 5;
  flagDrawX = savedPopupX + 11;
  while ( DD_IsLost((int)(intptr_t)g_RenderState) )
  {
    DD_Pump((int)(intptr_t)g_RenderState, v15);
    currentTimeMs = Time_Now(v21, lastFrameTime + 10);
    if ( v23 < currentTimeMs )
    {
      lastFrameTime = Time_Now(v24, v23);
      frameIndex = (frameIndex + 1) % 8;
      flagAnimSprite = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, frameIndex + 8 * *(_DWORD *)(uintptr_t)(g_MapData + 840));
      v15 = flagDrawX;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        flagDrawY,
        flagAnimSprite,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
    }
  }
  presentFillRectY = savedPopupY;
  presentPopupX = (unsigned __int16)savedPopupX;
  presentFillRectX = savedPopupX;
  presentSpriteWidth = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 0xCu);
  presentRectWidth = v28 + presentSpriteWidth - 1;
  presentSpriteHeight = DLX_GetSpriteHeight(g_ActiveUiSpriteSet, 0xCu);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, v30, presentPopupX, presentPopupX + presentSpriteHeight - 1, presentRectWidth, presentFillRectX, presentFillRectY);
  surfaceToFree = savedSurface;
  Render_Present((int)(intptr_t)g_RenderState);
  if ( surfaceToFree )
    (*(void (**)(void))(uintptr_t)surfaceToFree[46])();
  return DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
}
// 431971: variable 'v6' is possibly undefined
// 4319C7: variable 'v10' is possibly undefined
// 431B6E: variable 'v19' is possibly undefined
// 431B6E: variable 'v18' is possibly undefined
// 431BAE: variable 'v21' is possibly undefined
// 431BB5: variable 'v23' is possibly undefined
// 431BB7: variable 'v24' is possibly undefined
// 431C46: variable 'v28' is possibly undefined
// 431C6E: variable 'v30' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514E5C: using guessed type char *off_514E5C[2];
// 5202BC: using guessed type int dword_5202BC;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00431CC0) --------------------------------------------------------
__int16 UnitBattle_UpdateIdleAnimatedUnits(void)
{
  int slot_index;
  unsigned char *slot;
  int unit_type;
  unsigned int next_animation_tick;
  unsigned char animation_state;
  __int16 result;

  result = 0;
  slot = (unsigned char *)(uintptr_t)(unsigned int)(g_MapData + 0x354);
  for ( slot_index = 0; slot_index < 22; ++slot_index, slot += UNIT_STACK_SLOT_STRIDE )
  {
    unit_type = *(__int16 *)slot;
    if ( unit_type != -1 )
    {
      if ( (g_UnitTypeHasIdleAnimationFlags[88 * unit_type] & 1) != 0 )
      {
        next_animation_tick = *(unsigned int *)(slot + 0x12) + (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * unit_type];
        if ( next_animation_tick < Time_Now(slot_index, (int)(uintptr_t)slot) )
        {
          *(unsigned int *)(slot + 0x12) = Time_Now(slot_index, (int)(uintptr_t)slot);
          animation_state = slot[0x11] & 0xF8;
          slot[0x11] = animation_state | (((slot[0x11] & 7) + 1) & 7);
          result = UnitBattle_RedrawUnitFootprint(slot_index);
          continue;
        }
      }
    }
    result = UnitBattle_CountAdjacentEnemies((int)(uintptr_t)slot);
    if ( result >= 3 && unit_type != -1 )
    {
      next_animation_tick = *(unsigned int *)(slot + 0x12) + (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * unit_type];
      if ( next_animation_tick < Time_Now(slot_index, (int)(uintptr_t)slot) )
      {
        *(unsigned int *)(slot + 0x12) = Time_Now(slot_index, (int)(uintptr_t)slot);
        result = UnitBattle_RedrawUnitFootprint(slot_index);
      }
    }
  }
  if ( g_UnitBattleChargeModeActive_532060 && g_SelectedUnitIndex != g_ActiveUnitMoveTileIndex )
    result = UnitBattle_RedrawUnitFootprint(g_SelectedUnitIndex);
  return result;
}
// 431D15: variable 'v6' is possibly undefined
// 431D15: variable 'v2' is possibly undefined
// 431D1A: variable 'v8' is possibly undefined
// 431D46: variable 'v10' is possibly undefined
// 431D50: variable 'v12' is possibly undefined
// 431DA6: variable 'v15' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;

//----- (00431DE0) --------------------------------------------------------
__int16  UnitBattle_RedrawUnitFootprint(int unitIndex)
{
  __int16 *slot;
  unsigned int unit_type;
  unsigned __int16 tile_x;
  unsigned __int16 tile_y;
  unsigned __int8 facing;
  __int16 result;

  slot = (__int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852);
  unit_type = (unsigned __int16)*slot;
  result = *slot;
  if ( unit_type <= 0x28 )
  {
    tile_x = (unsigned __int16)slot[2];
    tile_y = (unsigned __int16)slot[3];
    result = UnitBattle_RedrawTile(tile_x, tile_y);
    if ( g_UnitTypeSpriteVerticalOffsetPx[88 * unit_type] && unit_type >= 0x1B )
    {
      if ( unit_type == 0x1B )
      {
        facing = *((unsigned __int8 *)slot + 3);
        switch ( facing )
        {
          case DIRECTION8_WEST:
          case DIRECTION8_EAST:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x + 1, tile_y);
            break;
          case DIRECTION8_SOUTHWEST:
            UnitBattle_RedrawTile(tile_x + 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case DIRECTION8_SOUTH:
          case DIRECTION8_NORTH:
            UnitBattle_RedrawTile(tile_x, tile_y - 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y + 1);
            break;
          case DIRECTION8_SOUTHEAST:
            UnitBattle_RedrawTile(tile_x + 1, tile_y);
            UnitBattle_RedrawTile(tile_x, tile_y + 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case DIRECTION8_NORTHEAST:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            UnitBattle_RedrawTile(tile_x, tile_y + 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case DIRECTION8_NORTHWEST:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          default:
            break;
        }
      }
      else if ( unit_type == 30 )
      {
        UnitBattle_RedrawTile(tile_x + 1, tile_y);
        UnitBattle_RedrawTile(tile_x, tile_y - 1);
        UnitBattle_RedrawTile(tile_x - 1, tile_y);
        result = UnitBattle_RedrawTile(tile_x, tile_y + 1);
      }
    }
  }
  return result;
}
// 431DFC: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 431E17: variable 'v4' is possibly undefined
// 431E5E: variable 'v5' is possibly undefined
// 431E89: variable 'v6' is possibly undefined
// 431EB0: variable 'v7' is possibly undefined
// 431ED7: variable 'v8' is possibly undefined
// 431EE9: variable 'v9' is possibly undefined
// 431F10: variable 'v10' is possibly undefined
// 431F22: variable 'v11' is possibly undefined
// 431F49: variable 'v12' is possibly undefined
// 431F70: variable 'v13' is possibly undefined
// 431F7E: variable 'v14' is possibly undefined
// 431F94: variable 'v15' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00431FB0) --------------------------------------------------------
unsigned int  UnitBattle_RedrawUnitNeighborhood(int unitIndex)
{
  __int16 *slot;
  unsigned int result;
  unsigned __int16 tile_x;
  unsigned __int16 tile_y;

  slot = (__int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852);
  result = (unsigned __int16)*slot;
  if ( result <= 0x28 )
  {
    tile_x = (unsigned __int16)slot[2];
    tile_y = (unsigned __int16)slot[3];
    UnitBattle_RedrawTile(tile_x, tile_y);
    result = UnitBattle_GetSpriteVerticalOffsetPx(unitIndex);
    if ( result )
    {
      UnitBattle_RedrawTile(tile_x, tile_y - 1);
      UnitBattle_RedrawTile(tile_x, tile_y + 1);
      UnitBattle_RedrawTile(tile_x - 1, tile_y);
      UnitBattle_RedrawTile(tile_x + 1, tile_y);
      UnitBattle_RedrawTile(tile_x - 1, tile_y - 1);
      UnitBattle_RedrawTile(tile_x - 1, tile_y + 1);
      UnitBattle_RedrawTile(tile_x + 1, tile_y - 1);
      return UnitBattle_RedrawTile(tile_x + 1, tile_y + 1);
    }
  }
  return result;
}
// 431FCD: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 431FFC: variable 'v4' is possibly undefined
// 43200E: variable 'v5' is possibly undefined
// 43201C: variable 'v6' is possibly undefined
// 43202E: variable 'v7' is possibly undefined
// 432044: variable 'v8' is possibly undefined
// 432057: variable 'v9' is possibly undefined
// 43206A: variable 'v10' is possibly undefined
// 43207D: variable 'v11' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00432090) --------------------------------------------------------
int  BuildingGarrisonDialog_HandleExitButtonPress(int widget, int unitIndex)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, unitIndex);
  g_GarrisonDialogExitScratch = v4;
  return result;
}
// 43209B: variable 'v4' is possibly undefined

//----- (00432120) --------------------------------------------------------
__int16  Battle_PlaceReservedUnitSlotAtTile(int unitRecord, int tileRow, int tileCol)
{
  int destPtr; // edi
  char facing; // al

  destPtr = g_MapData + 1503;
  qmemcpy((void *)(uintptr_t)(g_MapData + 1503), (const void *)(uintptr_t)unitRecord, 0x1Cu);
  destPtr += 28;
  *(_WORD *)(uintptr_t)destPtr = *(_WORD *)(uintptr_t)(unitRecord + 28);
  *(_BYTE *)(uintptr_t)(destPtr + 2) = *(_BYTE *)(uintptr_t)(unitRecord + 30);
  *(_WORD *)(uintptr_t)(g_MapData + 1507) = tileRow;
  *(_WORD *)(uintptr_t)(g_MapData + 1509) = tileCol;
  if ( *(_DWORD *)(uintptr_t)(g_MapData + 804) / 2 < tileRow )
    facing = 6;
  else
    facing = 2;
  *(_BYTE *)(uintptr_t)(g_MapData + 1506) = facing;
  *(_WORD *)(uintptr_t)(g_MapData + 40 * tileRow + 2 * tileCol + 1534) = 21;
  g_UnitFadeAnimUnitIndex = 21;
  return UnitBattle_RedrawUnitFootprint(21);
}
// 514E48: using guessed type int dword_514E48;
// 532048: using guessed type int g_MapData;

//----- (004321D0) --------------------------------------------------------
int Battle_ClearReservedUnitSlot(void)
{
  int result; // eax
  int reservedUnitType; // ebx
  int tileRow; // ecx
  int tileCol; // edx
  bool hasVerticalOffset; // si

  result = g_MapData;
  reservedUnitType = *(__int16 *)(uintptr_t)(g_MapData + 1503);
  if ( reservedUnitType != -1 )
  {
    tileRow = *(unsigned __int16 *)(uintptr_t)(g_MapData + 1507);
    tileCol = *(unsigned __int16 *)(uintptr_t)(g_MapData + 1509);
    hasVerticalOffset = g_UnitTypeSpriteVerticalOffsetPx[88 * reservedUnitType] != 0;
    *(_WORD *)(uintptr_t)(g_MapData + 1503) = -1;
    *(_WORD *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)tileRow + 2 * (unsigned __int16)tileCol + 1534) = -1;
    g_UnitFadeAnimUnitIndex = -1;
    if ( hasVerticalOffset )
      return UnitBattle_RedrawVisibleGrid();
    else
      return UnitBattle_RedrawTile(tileRow, tileCol);
  }
  return result;
}
// 514E48: using guessed type int dword_514E48;
// 532048: using guessed type int g_MapData;

//----- (00432770) --------------------------------------------------------
signed int Battle_RestoreSavedActionPointsBeforeResultCopy(void)
{
  signed int result; // eax
  int recordOffset; // edx
  int recordPtr; // ebx

  result = 0;
  recordOffset = 0;
  do
  {
    ++result;
    recordPtr = recordOffset + g_MapData;
    recordOffset += 31;
    *(_BYTE *)(uintptr_t)(recordPtr + 860) = g_BattleSavedActionPointsBySlot[result - 1];
  }
  while ( result < 22 );
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (004327B0) --------------------------------------------------------
signed int  Battle_PlaceUnit(unsigned __int8 *unitRecord, int tileRow, char facing, int tileCol)
{
  int v5 CLASH95_UNUSED; // ecx
  int slotIndex; // edx
  int i; // eax
  int recordOffset; // eax
  int savedMapData; // edi

  Debug_Log(tileRow, tileCol, (DWORD)(intptr_t)unitRecord, (int)(intptr_t)aBattle_placeun);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_place_unit_enter",
    *(__int16 *)unitRecord,
    unitRecord[2],
    tileRow,
    tileCol);
  if ( *(__int16 *)(uintptr_t)(40 * tileRow + g_MapData + 2 * tileCol + 1534) != -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "battle_place_unit_occupied",
      *(__int16 *)unitRecord,
      tileRow,
      tileCol,
      *(__int16 *)(uintptr_t)(40 * tileRow + g_MapData + 2 * tileCol + 1534));
    return 0;
  }
  slotIndex = 0;
  for ( i = 0; i < 682; i += 31 )
  {
    if ( *(__int16 *)(uintptr_t)(g_MapData + i + 852) == -1 )
      break;
    ++slotIndex;
  }
  recordOffset = 31 * slotIndex;
  qmemcpy((void *)(uintptr_t)(g_MapData + 31 * slotIndex + 852), unitRecord, 0x1Fu);
  *(_WORD *)(uintptr_t)(g_MapData + recordOffset + 856) = tileRow;
  *(_WORD *)(uintptr_t)(g_MapData + recordOffset + 858) = tileCol;
  *(_BYTE *)(uintptr_t)(g_MapData + recordOffset + 855) = facing;
  g_BattleSavedActionPointsBySlot[slotIndex] = unitRecord[8];
  savedMapData = g_MapData;
  *(_BYTE *)(uintptr_t)(g_MapData + recordOffset + 860) = g_UnitTypeBaseActionPoints_512580[88 * *(__int16 *)unitRecord];
  *(_BYTE *)(uintptr_t)(g_MapData + recordOffset + 874) &= ~1u;
  *(_BYTE *)(uintptr_t)(g_MapData + recordOffset + 864) &= 0x8Fu;
  *(_WORD *)(uintptr_t)(40 * tileRow + g_MapData + 2 * tileCol + 1534) = slotIndex;
  *(_DWORD *)(uintptr_t)(g_MapData + 4 * unitRecord[2] + 3944) = slotIndex;
  g_SelectedUnitIndex = slotIndex;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_place_unit_placed",
    slotIndex,
    *(__int16 *)unitRecord,
    unitRecord[2],
    tileRow);
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, tileCol, savedMapData);
  return 1;
}
// 4327DE: variable 'v5' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 532048: using guessed type int g_MapData;

//----- (00432910) --------------------------------------------------------
int BuildingGarrisonDialog_CountSelectedSlots(void)
{
  int selectedCount; // edx
  int i; // eax

  selectedCount = 0;
  for ( i = 0; i != 12; ++i )
  {
    if ( g_BuildingGarrisonDialogSelectedSlots[i] )
      ++selectedCount;
  }
  return selectedCount;
}
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[];

//----- (00432940) --------------------------------------------------------
void * BuildingGarrisonDialog_DrawSlotGrid(int targetSlot)
{
  int v1 CLASH95_UNUSED; // esi
  unsigned __int8 outlineColor; // al
  int slotIndex; // esi
  int cellY; // edi
  int unitSprite; // eax
  DWORD isSelected; // ebp
  int selectionSpriteIndex; // edx
  char serviceState; // cl
  int repairSprite; // eax
  int exitCountdownSprite; // eax
  int rectLeft; // ebp
  int rectBottom; // edi
  void *result; // eax
  int trainingSprite; // eax
  int SpriteForChar; // edx
  unsigned __int8 v16[4]; // [esp+74h] [ebp-38h] BYREF
  int cellX; // [esp+78h] [ebp-34h]
  int overlayPresented; // [esp+7Ch] [ebp-30h]
  int v19; // [esp+80h] [ebp-2Ch]
  int rectTop; // [esp+84h] [ebp-28h]
  void *savedRenderDevice; // [esp+88h] [ebp-24h]
  int textX; // [esp+8Ch] [ebp-20h]
  int savedTargetSlot; // [esp+90h] [ebp-1Ch]
  int slot_record;
  int slot_status_bits;

  savedTargetSlot = targetSlot;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_GarrisonUnitCellSurface;
  v1 = *(_DWORD *)(uintptr_t)(g_GarrisonUnitCellSurface + 184);
  v16[0] = -1;
  v16[1] = -1;
  v16[2] = -1;
  v16[3] = 0;
  outlineColor = Render_ApplyColorTripletBytes(g_BuildingGarrisonDialogResourceHandle, v16);
  Surface_DrawRectOutline((unsigned __int16 *)(uintptr_t)(unsigned int)g_GarrisonUnitCellSurface, 0, 32, 0, 63, (unsigned char)outlineColor);
  slotIndex = 0;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  do
  {
    if ( savedTargetSlot != -1 )
      slotIndex = savedTargetSlot;
    cellX = 71 * (slotIndex % 6) + 126;
    cellY = 131 * (slotIndex / 6) + 75;
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * slotIndex + 18;
    if ( UNIT_SLOT_TYPE(slot_record) == -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 15);
      Compat_RenderDeviceDrawMenuSprite(cellX, cellY, SpriteForChar, 1);
      goto LABEL_13;
    }
    v19 = 4 * slotIndex;
    if ( !g_BuildingGarrisonDialogSlotSpriteSets[slotIndex] )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 15);
      Compat_RenderDeviceDrawMenuSprite(cellX, cellY, SpriteForChar, 1);
      goto LABEL_13;
    }
    unitSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogSlotSpriteSets[slotIndex], g_BuildingGarrisonDialogSlotAnimFrames[slotIndex]);
    Compat_RenderDeviceDrawMenuSprite(cellX, cellY, unitSprite, 1);
    isSelected = *(int *)((char *)g_BuildingGarrisonDialogSelectedSlots + v19);
    if ( isSelected )
    {
      selectionSpriteIndex = 23;
    }
    else
    {
      if ( BuildingGarrisonDialog_CountSelectedSlots() < 10 )
        goto LABEL_8;
      selectionSpriteIndex = 24;
    }
    SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, selectionSpriteIndex);
    Compat_RenderDeviceDrawMenuSprite(cellX, cellY, SpriteForChar, 1);
LABEL_8:
    Render_ReleaseSurface(5, isSelected);
    serviceState = BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, slotIndex);
    textX = cellX + 15;
    if ( (serviceState & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
    {
      repairSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 14);
      Compat_RenderDeviceDrawMenuSprite(cellX, cellY, repairSprite, 1);
      slot_status_bits = (unsigned char)serviceState;
      UI_DrawText(textX, 131 * (slotIndex / 6) + 75, (int)(intptr_t)aD_55, (slot_status_bits & BUILDING_GARRISON_REPAIR_TURNS_MASK) >> 3);
    }
    else if ( (serviceState & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
    {
      trainingSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 13);
      Compat_RenderDeviceDrawMenuSprite(cellX, cellY, trainingSprite, 1);
      UI_DrawText(textX, 131 * (slotIndex / 6) + 75, (int)(intptr_t)aD_56, (unsigned char)serviceState & BUILDING_GARRISON_TRAINING_TURNS_MASK);
    }
    UI_DrawTextFmt(cellY, cellX, cellX + 33, 131 * (slotIndex / 6) + 125, 3, (int)(intptr_t)aD_57, (signed char)UNIT_SLOT_HEALTH_PERCENT(slot_record));
    if ( g_BuildingGarrisonDialogPendingExitCountdown && g_BuildingGarrisonDialogSelectedSlots[slotIndex] )
    {
      exitCountdownSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 22 - g_BuildingGarrisonDialogPendingExitCountdown);
      Compat_RenderDeviceDrawMenuSprite(cellX, cellY, exitCountdownSprite, 1);
    }
LABEL_13:
    overlayPresented = g_CursorOverlayPresented;
    rectLeft = (unsigned __int16)cellX;
    v19 = (unsigned __int16)(cellX + 32);
    rectTop = (unsigned __int16)cellY;
    RenderState_PumpIfRectInViewBounds(g_RenderState, cellX, cellX + 32, cellY, 131 * (slotIndex / 6) + 138);
    rectBottom = 131 * (slotIndex / 6) + 139;
    Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, rectTop, rectLeft, v19, 131 * (slotIndex / 6) + 139, rectLeft, rectTop);
    if ( overlayPresented )
      Render_Present((int)(intptr_t)g_RenderState);
    if ( savedTargetSlot != -1 )
      break;
    ++slotIndex;
  }
  while ( slotIndex < 12 );
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, (DWORD)(intptr_t)&g_MainRenderDevice);
  UI_DrawTextFmt(rectBottom, 545, 613, 53, 3, (int)(intptr_t)aD_58, *(_DWORD *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 438));
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532144: using guessed type int dword_532144;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 532194: using guessed type int g_BuildingGarrisonDialogSlotSpriteSets[];
// 5321C4: using guessed type int dword_5321C4[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;
// 5321F8: using guessed type int dword_5321F8;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00432D30) --------------------------------------------------------
int  BuildingGarrisonDialog_ReloadSlotSprite(int result, int a2, int a3, DWORD a4)
{
  int slot_index;
  int slot_record;
  int sprite_set;
  char sprite_path[104];

  (void)a2;
  (void)a3;
  slot_index = result;
  if ( slot_index == -1 )
    return 0;
  if ( g_BuildingGarrisonDialogSlotSpriteSets[slot_index] )
  {
    nfree_(g_BuildingGarrisonDialogSlotSpriteSets[slot_index]);
    g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = 0;
  }
  slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * slot_index;
  if ( *(__int16 *)(uintptr_t)(slot_record + 18) == -1 )
    return 0;
  Unit_BuildGarrisonSlotIconSpritePath(sprite_path, *(_BYTE *)(uintptr_t)(slot_record + 18), slot_index);
  sprite_set = Mem_Alloc(4112, 0, 0, a4);
  if ( sprite_set )
    sprite_set = (int)(intptr_t)DLXSpriteSet_Load((_DWORD *)(uintptr_t)sprite_set, sprite_path);
  g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = sprite_set;
  return sprite_set;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532194: using guessed type int g_BuildingGarrisonDialogSlotSpriteSets[];

//----- (00432DC0) --------------------------------------------------------
void * BuildingGarrisonDialog_RebuildSlotSprites(int a1, DWORD a2)
{
  int i; // edx

  for ( i = 0; i < 12; ++i )
    BuildingGarrisonDialog_ReloadSlotSprite(i, i + 1, a1, a2);
  return BuildingGarrisonDialog_DrawSlotGrid(-1);
}

//----- (00432DF0) --------------------------------------------------------
void * BuildingGarrisonDialog_TickExitCountdown(int a1, double a2)
{
  int now;
  int i;
  int staged_slots[14];
  int staged_count;
  int countdown_frame;

  (void)a1;
  now = Time_Now(0, 0);
  if ( (unsigned int)now < (unsigned int)(g_BuildingGarrisonDialogExitCountdownLastTickMs + 10) )
    return (void *)(uintptr_t)(unsigned int)now;
  g_BuildingGarrisonDialogExitCountdownLastTickMs = now;
  for ( i = 0; i < 12; ++i )
    g_BuildingGarrisonDialogSlotAnimFrames[i] = (g_BuildingGarrisonDialogSlotAnimFrames[i] + 1) & 7;
  countdown_frame = g_BuildingGarrisonDialogPendingExitCountdown;
  if ( countdown_frame )
  {
    ++g_BuildingGarrisonDialogPendingExitCountdown;
    if ( countdown_frame == 7 )
    {
      staged_count = 0;
      g_BuildingGarrisonDialogPendingExitCountdown = 0;
      for ( i = 0; i < 12; ++i )
      {
        if ( g_BuildingGarrisonDialogSelectedSlots[i] )
          staged_slots[staged_count++] = i;
      }
      staged_slots[staged_count] = -1;
      if ( staged_count )
      {
        Building_UnitsLeave((unsigned __int8 *)(uintptr_t)g_BuildingGarrisonDialogActiveBuilding, staged_slots, a2);
        memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
      }
    }
  }
  return BuildingGarrisonDialog_DrawSlotGrid(-1);
}
// 532138: using guessed type int dword_532138;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 5321C0: using guessed type int dword_5321C0[];
// 5321C4: using guessed type int dword_5321C4[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;

//----- (00432ED0) --------------------------------------------------------
void *BuildingGarrisonDialog_DrawSelectedUnitPanel(void)
{
  int overlayPresented; // edi
  __int16 placeholderSpriteHeight; // ax
  int placeholderSprite; // eax
  void *result; // eax
  char textColor; // al
  int unitType; // eax
  const UnitTypeRuntimeCoreMetadataRecord *unitMetadata; // esi
  int frameSprite; // edx
  int SpriteForChar; // eax
  int fontContextPersonage; // edi
  int personageUnitType; // eax
  int personageBadgeSprite; // eax
  int unitPortraitSprite; // eax
  __int16 SpriteWidth; // ax
  __int16 SpriteHeight; // ax
  unsigned __int16 restoreTop; // di
  unsigned __int16 restoreLeft; // si
  int frameWidthUnitType; // eax
  unsigned __int16 frameWidthSpriteIndex; // ax
  __int16 frameSpriteWidth; // ax
  int frameHeightUnitType; // eax
  unsigned __int16 frameHeightSpriteIndex; // ax
  __int16 frameSpriteHeight; // ax
  int fontContext; // edi
  int iconSprite; // eax
  int classIconY; // ecx
  int classIconSprite; // edx
  int panelXCopy; // edi
  int statValue; // edx
  int col2X; // edi
  int col1XCopy; // esi
  unsigned __int8 orderBits; // al
  int orderSpriteIndex; // edx
  int orderSprite; // eax
  int orderMarkerY; // esi
  int orderMarkerSprite; // eax
  int unitClassLevel; // eax
  int unitClassLevelAlt; // eax
  unsigned __int16 frameFillRight; // [esp-Ch] [ebp-38h]
  unsigned __int16 placeholderFillRight; // [esp-4h] [ebp-30h]
  unsigned __int16 portraitFillRight; // [esp-4h] [ebp-30h]
  unsigned __int8 colorTokenBytes[2]; // [esp+0h] [ebp-2Ch] BYREF
  char colorTokenStr[2]; // [esp+2h] [ebp-2Ah] BYREF
  int fontContextTemp; // [esp+4h] [ebp-28h]
  int panelX; // [esp+8h] [ebp-24h]
  __int16 *unitRecord; // [esp+Ch] [ebp-20h]
  int overlayPresentedAfter; // [esp+10h] [ebp-1Ch]
  void *savedRenderDevice; // [esp+14h] [ebp-18h]
  int row3Y; // [esp+18h] [ebp-14h]
  int col1X; // [esp+1Ch] [ebp-10h]
  int panelY; // [esp+20h] [ebp-Ch]
  int orderMarkerX; // [esp+24h] [ebp-8h]
  int orderMarkerCount; // [esp+28h] [ebp-4h]
  _DWORD savedregs[6]; // [esp+2Ch] [ebp+0h] BYREF
  const char *selected_unit_name;

  savedRenderDevice = g_RenderDevice;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() && g_BuildingGarrisonDialogSelectedSlotIndex != -1 )
    fprintf(
      stderr,
      "[barracks] selected_panel_draw_enter selected=%d sprite_set=%08x\n",
      g_BuildingGarrisonDialogSelectedSlotIndex,
      g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedSlotIndex != -1
    && *(__int16 *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18) != -1 )
  {
    g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
    colorTokenBytes[0] = -31;
    strcpy(colorTokenStr, "d");
    colorTokenBytes[1] = -47;
    textColor = Render_ApplyColorTripletBytes(g_BuildingGarrisonDialogResourceHandle, colorTokenBytes);
    TextSprite_ActivateResourceSlot(3, textColor, (DWORD)(intptr_t)savedregs);
    panelX = 289;
    unitRecord = (__int16 *)(uintptr_t)(31
                    * g_BuildingGarrisonDialogSelectedSlotIndex
                    + g_BuildingGarrisonDialogActiveBuilding
                    + 18);
    panelY = 220;
    unitType = *(__int16 *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
    unitMetadata = &g_UnitTypeRuntimeCoreMetadata[*unitRecord];
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      frameSprite = 33;
    else
      frameSprite = 10;
    selected_unit_name = UnitType_GetLocalizedName((unit_type)unitType);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_draw_body type=%d frame_sprite=%d\n", unitType, frameSprite);
    SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, frameSprite);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_frame_sprite ptr=%08x\n", SpriteForChar);
    fontContextPersonage = *((_DWORD *)g_RenderDevice + 46);
    Compat_RenderDeviceDrawMenuSprite(panelX, panelY, SpriteForChar, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_frame_drawn\n");
    Render_ReleaseSurface(7, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_after_release7\n");
    personageUnitType = *(__int16 *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
    if ( personageUnitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || personageUnitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      UI_DrawTextFmt(
        fontContextPersonage,
        panelX + 64,
        panelX + 162,
        panelY + 8,
        3,
        selected_unit_name);
      UI_DrawTextFmt(fontContextPersonage, panelX + 15, panelX + 88, panelY + 32, 2, aD_67, (unsigned char)unitMetadata->base_action_points);
      personageBadgeSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 34);
      Compat_RenderDeviceDrawMenuSprite(panelX + 93, panelY + 20, personageBadgeSprite, 1);
LABEL_10:
      if ( !g_BuildingGarrisonDialogSelectedUnitSpriteSet )
      {
        if ( Diagnostics_IsWorldMapClickTraceEnabled() )
          fprintf(stderr, "[barracks] selected_panel_missing_unit_sprite selected=%d\n", g_BuildingGarrisonDialogSelectedSlotIndex);
        goto LABEL_4;
      }
      unitPortraitSprite = DLX_GetSpriteForChar(
              g_BuildingGarrisonDialogSelectedUnitSpriteSet,
              g_BuildingGarrisonDialogSelectedUnitAnimFrame);
      Compat_RenderDeviceDrawMenuSprite(panelX + 8, panelY + 6, unitPortraitSprite, 0);
      overlayPresentedAfter = g_CursorOverlayPresented;
      SpriteWidth = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, 0xAu);
      portraitFillRight = panelX + 4 + SpriteWidth;
      SpriteHeight = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, 0xAu);
      restoreTop = panelY;
      restoreLeft = panelX;
      RenderState_PumpIfRectInViewBounds(g_RenderState, panelY, panelY + 49 + SpriteHeight, panelX, portraitFillRight);
      frameWidthUnitType = *(__int16 *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
      if ( frameWidthUnitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || frameWidthUnitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        frameWidthSpriteIndex = 33;
      else
        frameWidthSpriteIndex = 10;
      frameSpriteWidth = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, frameWidthSpriteIndex);
      frameFillRight = panelX - 1 + frameSpriteWidth;
      frameHeightUnitType = *(__int16 *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
      if ( frameHeightUnitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || frameHeightUnitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        frameHeightSpriteIndex = 33;
      else
        frameHeightSpriteIndex = 10;
      frameSpriteHeight = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, frameHeightSpriteIndex);
      Render_FillRect(
        (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
        &g_MainRenderDevice,
        (unsigned __int16)panelY,
        (unsigned __int16)panelX,
        frameFillRight,
        panelY + frameSpriteHeight - 1,
        restoreLeft,
        restoreTop);
      if ( !overlayPresentedAfter )
        goto LABEL_4;
      Render_Present((int)(intptr_t)g_RenderState);
      result = savedRenderDevice;
      g_RenderDevice = savedRenderDevice;
      return result;
    }
    fontContext = *((_DWORD *)g_RenderDevice + 46);
    UI_DrawTextFmt(fontContext, panelX + 64, panelX + 192, panelY + 5, 3, selected_unit_name);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_name_drawn name=%s\n", selected_unit_name);
    UI_DrawTextFmt(fontContext, panelX + 85, panelX + 105, panelY + 50, 2, aD_59, (unsigned char)unitMetadata->base_action_points);
    statValue = Unit_CalcIndexB(unitRecord);
    UI_DrawTextFmt(fontContext, panelX + 132, panelX + 148, panelY + 95, 2, (int)(intptr_t)aD_60, statValue);
    if ( (unsigned int)*((char *)unitRecord + 11) > 4 )
    {
      unitClassLevel = *((char *)unitRecord + 11);
      if ( unitClassLevel >= 11 && unitClassLevel <= 15 )
      {
        classIconSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 27);
        classIconY = panelY;
        fontContext = *((_DWORD *)g_RenderDevice + 46);
      }
      else
      {
        unitClassLevelAlt = *((char *)unitRecord + 11);
        if ( unitClassLevelAlt < 16 || unitClassLevelAlt > 20 )
          goto LABEL_22;
        classIconSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 26);
        classIconY = panelY;
        fontContext = *((_DWORD *)g_RenderDevice + 46);
      }
    }
    else
    {
      iconSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 28);
      classIconY = panelY;
      fontContextTemp = *((_DWORD *)g_RenderDevice + 46);
      classIconSprite = iconSprite;
      fontContext = fontContextTemp;
    }
    Compat_RenderDeviceDrawMenuSprite(panelX + 106, classIconY + 21, classIconSprite, 0);
LABEL_22:
    UI_DrawTextFmt(fontContext, panelX + 132, panelX + 148, panelY + 50, 2, (int)(intptr_t)aD_61, (signed char)UNIT_SLOT_MORALE((intptr_t)unitRecord));
    panelXCopy = panelX;
    UI_DrawTextFmt(fontContext, panelX + 160, panelX + 191, panelY + 50, 2, (int)(intptr_t)aD_62, (signed char)UNIT_SLOT_FATIGUE((intptr_t)unitRecord));
    col2X = panelXCopy + 105;
    row3Y = panelY + 95;
    col1X = panelX + 85;
    if ( unitMetadata->base_shot_power )
    {
      if ( unitMetadata->base_melee_attack )
      {
        statValue = UI_IconIndexFromStats(unitRecord);
        col1XCopy = col1X;
        UI_DrawTextFmt(col2X, col1X, col2X, panelY + 74, 2, (int)(intptr_t)aD_65, statValue);
        statValue = Unit_GetBaseC(unitRecord);
        UI_DrawTextFmt(col2X, col1XCopy, col2X, row3Y, 2, (int)(intptr_t)aD_66, statValue);
      }
      else
      {
        iconSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 12);
        Compat_RenderDeviceDrawMenuSprite(panelX + 62, panelY + 65, iconSprite, 1);
        statValue = Unit_GetBaseC(unitRecord);
        UI_DrawTextFmt(col2X, col1X, col2X, row3Y, 2, (int)(intptr_t)aD_64, statValue);
      }
    }
    else
    {
      iconSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 11);
      fontContextTemp = *((_DWORD *)g_RenderDevice + 46);
      Compat_RenderDeviceDrawMenuSprite(panelX + 62, panelY + 65, iconSprite, 1);
      statValue = UI_IconIndexFromStats(unitRecord);
      UI_DrawTextFmt(col2X, col1X, col2X, row3Y, 2, (int)(intptr_t)aD_63, statValue);
    }
    orderBits = unitRecord[6] & 3;
    if ( orderBits )
    {
      if ( orderBits <= 1u )
      {
        orderSpriteIndex = 30;
      }
      else
      {
        if ( orderBits != 3 )
        {
LABEL_28:
          orderMarkerCount = 0;
          orderMarkerY = panelY + 71;
          orderMarkerX = panelX + 178;
          while ( (unsigned __int8)(16 * *((_BYTE *)unitRecord + 12)) >> 6 >= orderMarkerCount )
          {
            orderMarkerSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 32);
            Compat_RenderDeviceDrawMenuSprite(orderMarkerX, orderMarkerY, orderMarkerSprite, 1);
            orderMarkerY += 10;
            ++orderMarkerCount;
          }
          goto LABEL_10;
        }
        orderSpriteIndex = 31;
      }
    }
    else
    {
      orderSpriteIndex = 29;
    }
    orderSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, orderSpriteIndex);
    Compat_RenderDeviceDrawMenuSprite(panelX + 149, panelY + 65, orderSprite, 0);
    goto LABEL_28;
  }
  overlayPresented = g_CursorOverlayPresented;
  g_RenderDevice = &g_MainRenderDevice;
  placeholderFillRight = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, 0x19u) + 289;
  placeholderSpriteHeight = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, 0x19u);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xDCu, placeholderSpriteHeight + 220, 0x121u, placeholderFillRight);
  placeholderSprite = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 25);
  Compat_RenderDeviceDrawMenuSprite(289, 220, placeholderSprite, 0);
  if ( !overlayPresented )
  {
LABEL_4:
    result = savedRenderDevice;
    g_RenderDevice = savedRenderDevice;
    return result;
  }
  Render_Present((int)(intptr_t)g_RenderState);
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 43334D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 4333F6: variable 'v29' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202E0: using guessed type int dword_5202E0;
// 532144: using guessed type int dword_532144;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532188: using guessed type int g_BuildingGarrisonDialogSelectedSlotIndex;
// 53218C: using guessed type int g_BuildingGarrisonDialogSelectedUnitSpriteSet;
// 532190: using guessed type int g_BuildingGarrisonDialogSelectedUnitAnimFrame;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (004336C0) --------------------------------------------------------
void  BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(int a1, char a2, DWORD a3)
{
  int slot_record;
  int sprite_set;
  int palette_entries[256];
  int palette_index;
  char asset_path[104];

  (void)a1;
  (void)a2;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[barracks] selected_assets_enter selected=%d current_sprite=%08x\n",
      g_BuildingGarrisonDialogSelectedSlotIndex,
      g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedSlotIndex != -1 )
  {
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex;
    if ( *(__int16 *)(uintptr_t)(slot_record + 18) != -1 )
    {
      Unit_BuildSelectedUnitPanelIconSpritePath(asset_path, *(_BYTE *)(uintptr_t)(slot_record + 18), g_BuildingGarrisonDialogActiveBuilding);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[barracks] selected_assets_unit_path idx=%d type=%d path=%s\n",
          g_BuildingGarrisonDialogSelectedSlotIndex,
          *(__int16 *)(uintptr_t)(slot_record + 18),
          asset_path);
      sprite_set = Mem_Alloc(4112, 0, a2, a3);
      if ( sprite_set )
        sprite_set = (int)(intptr_t)DLXSpriteSet_Load((_DWORD *)(uintptr_t)sprite_set, asset_path);
      g_BuildingGarrisonDialogSelectedUnitSpriteSet = sprite_set;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_unit_loaded sprite_set=%08x\n", sprite_set);
      Unit_BuildSelectedUnitPanelIconPalettePath(asset_path, *(_BYTE *)(uintptr_t)(slot_record + 18), g_BuildingGarrisonDialogActiveBuilding);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_path path=%s\n", asset_path);
      Compat_LoadPalCOLIntoTable(palette_entries, asset_path, a3);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_loaded\n");
      for ( palette_index = 224; palette_index <= 255; ++palette_index )
        *(_DWORD *)(uintptr_t)(g_BuildingGarrisonDialogResourceHandle + 4 * palette_index) = palette_entries[palette_index];
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_copied\n");
      Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
      BuildingGarrisonDialog_DrawSelectedUnitPanel();
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_panel_drawn\n");
      BuildingGarrisonDialog_ReloadSlotSprite(g_BuildingGarrisonDialogSelectedSlotIndex, 0, 0, a3);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_slot_reloaded\n");
    }
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_assets_done\n");
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532188: using guessed type int g_BuildingGarrisonDialogSelectedSlotIndex;
// 53218C: using guessed type int g_BuildingGarrisonDialogSelectedUnitSpriteSet;

//----- (004337E0) --------------------------------------------------------
void *__thiscall BuildingGarrisonDialog_AnimateSelectedUnit(void *this)
{
  int now;

  (void)this;
  now = Time_Now(0, 0);
  if ( (unsigned int)now < (unsigned int)(g_BuildingGarrisonDialogSelectedUnitAnimLastTickMs + 10) )
    return (void *)(uintptr_t)(unsigned int)now;
  g_BuildingGarrisonDialogSelectedUnitAnimLastTickMs = now;
  g_BuildingGarrisonDialogSelectedUnitAnimFrame = ((_BYTE)g_BuildingGarrisonDialogSelectedUnitAnimFrame + 1) & 7;
  return BuildingGarrisonDialog_DrawSelectedUnitPanel();
}
// 53213C: using guessed type int dword_53213C;
// 532190: using guessed type int g_BuildingGarrisonDialogSelectedUnitAnimFrame;

//----- (00433820) --------------------------------------------------------
int BuildingGarrisonDialog_HitTestSlotGrid(void)
{
  int mouseX; // eax
  int relY; // ebx
  int col; // ecx
  int row; // eax

  mouseX = g_MouseCursorRawX >> g_CursorCoordShift;
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= 126
    && g_MouseCursorRawY >> g_CursorCoordShift >= 75
    && (relY = (g_MouseCursorRawY >> g_CursorCoordShift) - 75, (mouseX - 126) % 71 <= 33)
    && relY % 131 <= 64
    && (col = (mouseX - 126) / 71, row = relY / 131, col < 6)
    && row <= 1 )
  {
    return col + 6 * row;
  }
  else
  {
    return -1;
  }
}
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
