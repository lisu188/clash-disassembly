/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../strategic/strategic_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00421240) --------------------------------------------------------
char  Castle_RenderCompositeSceneLayers(int surface, int drawModeArg, int buildingRecordArg, int variantArg)
{
  int surface2; // ebp
  char addonFlags; // dl
  char v6; // bh
  char v7; // dl
  char v8; // bh
  char v9; // dl
  char *addonLayerName; // edx
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  char *v19; // esi
  char *v20; // edi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char addonFlags2; // bh
  char v28; // ch
  char v29; // dh
  char *addonLayer2Name; // edx
  char *v31; // esi
  char *v32; // edi
  char v33; // al
  char v34; // al
  char *v35; // esi
  char *v36; // edi
  char v37; // al
  char v38; // al
  char *v39; // esi
  char *v40; // edi
  char v41; // al
  char v42; // al
  char *v43; // esi
  char *v44; // edi
  char v45; // al
  char v46; // al
  char *v47; // esi
  char *v48; // edi
  char v49; // al
  char v50; // al
  char *v51; // esi
  char *v52; // edi
  char v53; // al
  char v54; // al
  char v55; // bh
  char v56; // dl
  int SpriteForChar; // eax
  int castle_icon_owner; // eax
  void *v58; // ecx
  int savedBuildingRecord; // edx
  char pathBuffer[256]; // [esp+0h] [ebp-138h] BYREF
  __int16 ownerIconPositions[10]; // [esp+100h] [ebp-38h] BYREF
  char castleSpriteName[8]; // [esp+114h] [ebp-24h] BYREF
  void *savedRenderDevice; // [esp+11Ch] [ebp-1Ch]
  int buildingRecord; // [esp+120h] [ebp-18h]
  int variant; // [esp+124h] [ebp-14h]
  int drawMode; // [esp+128h] [ebp-10h]
  int load_result;

  surface2 = surface;
  drawMode = drawModeArg;
  variant = variantArg;
  buildingRecord = buildingRecordArg;
  strcpy(castleSpriteName, "zamek_1");
  LOBYTE(surface) = g_CurrentPlayerIndex + 49;
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  if ( variantArg != 2 )
  {
    addonFlags = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
    if ( (addonFlags & 1) == 0 || (addonFlags & 2) != 0 || (addonFlags & 4) != 0 )
    {
      v6 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
      if ( (v6 & 1) != 0 || (v6 & 2) != 0 || (v6 & 4) == 0 )
      {
        v7 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
        if ( (v7 & 1) != 0 || (v7 & 2) == 0 || (v7 & 4) != 0 )
        {
          v8 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
          if ( (v8 & 1) == 0 && (v8 & 2) != 0 && (v8 & 4) != 0 )
          {
            addonLayerName = a11_7;
          }
          else
          {
            v9 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
            if ( (v9 & 1) != 0 && (v9 & 2) != 0 && (v9 & 4) != 0 )
            {
              addonLayerName = a12;
            }
            else
            {
              v55 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
              if ( (v55 & 1) != 0 && (v55 & 2) != 0 && (v55 & 4) == 0 )
              {
                addonLayerName = a10;
              }
              else
              {
                v56 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
                if ( (v56 & 1) != 0 && (v56 & 2) == 0 && (v56 & 4) != 0 )
                  addonLayerName = a07;
                else
                  addonLayerName = a01_3;
              }
            }
          }
        }
        else
        {
          addonLayerName = a09;
        }
      }
      else
      {
        addonLayerName = a05;
      }
    }
    else
    {
      addonLayerName = a03;
    }
    v11 = castleSpriteName;
    v12 = pathBuffer;
    do
    {
      v13 = *v11;
      *v12 = *v11;
      if ( !v13 )
        break;
      v14 = v11[1];
      v11 += 2;
      v12[1] = v14;
      v12 += 2;
    }
    while ( v14 );
    v15 = aZ_;
    v16 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v17 = *v15;
      *v16 = *v15;
      if ( !v17 )
        break;
      v18 = v15[1];
      v15 += 2;
      v16[1] = v18;
      v16 += 2;
    }
    while ( v18 );
    v19 = addonLayerName;
    v20 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v21 = *v19;
      *v20 = *v19;
      if ( !v21 )
        break;
      v22 = v19[1];
      v19 += 2;
      v20[1] = v22;
      v20 += 2;
    }
    while ( v22 );
    if ( drawMode )
      v23 = aM_gfx;
    else
      v23 = a_gfx;
    v24 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v25 = *v23;
      *v24 = *v23;
      if ( !v25 )
        break;
      v26 = v23[1];
      v23 += 2;
      v24[1] = v26;
      v24 += 2;
    }
    while ( v26 );
    load_result = RenderSurface_InvokeSlot48LoadPCX(
                    (_DWORD *)(uintptr_t)(unsigned int)surface2,
                    pathBuffer,
                    0,
                    (uintptr_t)g_CastleScreenPaletteBuffer);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=0 result=%d target=%08x\n", pathBuffer, load_result, surface2);
    LOBYTE(surface) = load_result;
  }
  if ( variant != 1 )
  {
    addonFlags2 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
    if ( (addonFlags2 & 8) != 0 && (addonFlags2 & 0x10) == 0 )
    {
      addonLayer2Name = a04;
    }
    else
    {
      v28 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
      if ( (v28 & 8) != 0 || (v28 & 0x10) == 0 )
      {
        v29 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
        if ( (v29 & 8) != 0 && (v29 & 0x10) != 0 )
          addonLayer2Name = a08;
        else
          addonLayer2Name = a02;
      }
      else
      {
        addonLayer2Name = a06;
      }
    }
    v31 = castleSpriteName;
    v32 = pathBuffer;
    do
    {
      v33 = *v31;
      *v32 = *v31;
      if ( !v33 )
        break;
      v34 = v31[1];
      v31 += 2;
      v32[1] = v34;
      v32 += 2;
    }
    while ( v34 );
    v35 = aZ__0;
    v36 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v37 = *v35;
      *v36 = *v35;
      if ( !v37 )
        break;
      v38 = v35[1];
      v35 += 2;
      v36[1] = v38;
      v36 += 2;
    }
    while ( v38 );
    v39 = addonLayer2Name;
    v40 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v41 = *v39;
      *v40 = *v39;
      if ( !v41 )
        break;
      v42 = v39[1];
      v39 += 2;
      v40[1] = v42;
      v40 += 2;
    }
    while ( v42 );
    v43 = drawMode ? aM_gfx_0 : a_gfx_0;
    v44 = &pathBuffer[strlen(pathBuffer)];
    do
    {
      v45 = *v43;
      *v44 = *v43;
      if ( !v45 )
        break;
      v46 = v43[1];
      v43 += 2;
      v44[1] = v46;
      v44 += 2;
    }
    while ( v46 );
    load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, pathBuffer, 1, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", pathBuffer, load_result, surface2);
    surface = *(char *)(uintptr_t)(g_SelectedBuildingRecord + 4);
    if ( surface == 1 )
    {
      v47 = castleSpriteName;
      v48 = pathBuffer;
      do
      {
        v49 = *v47;
        *v48 = *v47;
        if ( !v49 )
          break;
        v50 = v47[1];
        v47 += 2;
        v48[1] = v50;
        v48 += 2;
      }
      while ( v50 );
      v51 = aZ_13_tw_gfx;
      v52 = &pathBuffer[strlen(pathBuffer)];
      do
      {
        v53 = *v51;
        *v52 = *v51;
        if ( !v53 )
          break;
        v54 = v51[1];
        v51 += 2;
        v52[1] = v54;
        v52 += 2;
      }
      while ( v54 );
      load_result = RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surface2, pathBuffer, 1, 0);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[castle] load_layer path=%s transparent=1 result=%d target=%08x\n", pathBuffer, load_result, surface2);
      LOBYTE(surface) = load_result;
    }
  }
  if ( !drawMode )
  {
    savedRenderDevice = g_RenderDevice;
    g_RenderDevice = (_UNKNOWN *)(uintptr_t)surface2;
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 0);
    Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 0);
    qmemcpy(ownerIconPositions, &g_CastleOwnerIconPositions, sizeof(ownerIconPositions));
    castle_icon_owner = *(unsigned __int8 *)(uintptr_t)(g_SelectedBuildingRecord + 2);
    SpriteForChar = DLX_GetSpriteForChar(g_CastleSceneIconSpriteSet, 8);
    Compat_RenderDeviceDrawMenuSprite(ownerIconPositions[2 * castle_icon_owner + 1], ownerIconPositions[2 * castle_icon_owner], SpriteForChar, 1);
    savedBuildingRecord = g_SelectedBuildingRecord;
    g_SelectedBuildingRecord = buildingRecord;
    Castle_DrawAllAmbientAnimationLayers(v58);
    g_SelectedBuildingRecord = savedBuildingRecord;
    Castle_EnsureCompositeStatusWidget();
    UIWidgetTable_InitDrawStates((_DWORD *)g_CastleStatusWidgetRecord);
    LOBYTE(surface) = (_BYTE)(intptr_t)savedRenderDevice;
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  }
  return surface;
}
// 42170D: variable 'v58' is possibly undefined
// 421717: variable 'v59' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513D98: using guessed type _DWORD dword_513D98[3];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E74: using guessed type int g_CastleSceneIconSpriteSet;

//----- (00421740) --------------------------------------------------------
int  Castle_DrawAmbientAnimationSprite(
        unsigned __int16 top,
        int left,
        int spriteChar,
        int spriteSet,
        unsigned __int8 drawFlags)
{
  int overlayWasPresented; // ebp
  __int16 SpriteHeight; // ax
  int SpriteForChar; // eax
  int result; // eax
  unsigned __int16 rightX; // [esp-4h] [ebp-1Ch]

  overlayWasPresented = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    rightX = left + DLX_GetSpriteWidth(spriteSet, spriteChar);
    SpriteHeight = DLX_GetSpriteHeight(spriteSet, spriteChar);
    RenderState_PumpIfRectInViewBounds(g_RenderState, top, top + SpriteHeight, left, rightX);
  }
  SpriteForChar = DLX_GetSpriteForChar(spriteSet, spriteChar);
  result = Compat_RenderDeviceDrawMenuSprite(left, top, SpriteForChar, drawFlags);
  if ( overlayWasPresented )
    return Render_Present((int)(intptr_t)g_RenderState);
  return result;
}
// 42177B: variable 'v7' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00421830) --------------------------------------------------------
int  Castle_DrawAmbientAnimationLayer(int layerIndex)
{
  int result; // eax
  char addonFlagsLayer1; // dh
  char addonFlagsLayer2; // ch

  switch ( layerIndex )
  {
    case 1:
      result = g_SelectedBuildingRecord;
      addonFlagsLayer1 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
      if ( (addonFlagsLayer1 & 4) != 0 && (addonFlagsLayer1 & 1) != 0 )
      {
        result = g_CastleAmbientLayer1_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(
                     g_CastleAmbientLayer1_SpriteIds[20 * g_CurrentPlayerIndex],
                     g_CastleAmbientLayer1_XOffsets[20 * g_CurrentPlayerIndex],
                     g_CastleAmbientLayer1_Frame,
                     g_CastleAmbientSpriteSet,
                     1u);
      }
      break;
    case 2:
      result = g_SelectedBuildingRecord;
      addonFlagsLayer2 = *(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416);
      if ( (addonFlagsLayer2 & 0x10) != 0 && (addonFlagsLayer2 & 8) != 0 )
      {
        result = g_CastleAmbientLayer2_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer2_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer2_Frame + 12, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 3:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SMITHS) != 0 )
      {
        result = g_CastleAmbientLayer3_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer3_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer3AnimFrame + 24, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 4:
      if ( g_CurrentPlayerIndex != 1 && g_CurrentPlayerIndex != 4
        || (result = *(_DWORD *)(uintptr_t)(g_SelectedBuildingRecord + 416) << 28 >> 31, (*(_DWORD *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0) )
      {
        if ( g_CurrentPlayerIndex != 3
          || (result = *(_DWORD *)(uintptr_t)(g_SelectedBuildingRecord + 416) << 30 >> 31, (*(_DWORD *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0) )
        {
          result = g_CastleAmbientLayer4_SpriteIds[20 * g_CurrentPlayerIndex];
          if ( result != -1 )
            result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer4_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer4_Frame + 36, g_CastleAmbientSpriteSet, 1u);
        }
      }
      break;
    case 5:
      result = g_CastleAmbientLayer5_SpriteIds[20 * g_CurrentPlayerIndex];
      if ( result != -1 )
        result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer5_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer5_Frame + 48, g_CastleAmbientSpriteSet, 0);
      break;
    case 6:
      result = *(char *)(uintptr_t)(g_SelectedBuildingRecord + 4);
      if ( result != 1 )
      {
        result = g_CastleAmbientLayer6_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer6_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer6_Frame + 71, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 7:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
      {
        result = g_CastleAmbientLayer7_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer7_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer7_Frame + 83, g_CastleAmbientSpriteSet, 1u);
      }
      break;
    case 8:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
      {
        result = g_CastleAmbientLayer8_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer8_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer8_Frame + 95, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 9:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
      {
        result = g_CastleAmbientLayer9_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer9_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer9_Frame + 136, g_CastleAmbientSpriteSet, 0);
      }
      break;
    case 10:
      result = g_SelectedBuildingRecord;
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedBuildingRecord + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
      {
        result = g_CastleAmbientLayer10_SpriteIds[20 * g_CurrentPlayerIndex];
        if ( result != -1 )
          result = Castle_DrawAmbientAnimationSprite(result, g_CastleAmbientLayer10_XOffsets[20 * g_CurrentPlayerIndex], g_CastleAmbientLayer10AnimFrame + 167, g_CastleAmbientSpriteSet, 0);
      }
      break;
    default:
      App_RequestQuit((int)(intptr_t)asc_4EE6D4);
  }
  return result;
}
// 513C3C: using guessed type __int16 word_513C3C[];
// 513C3E: using guessed type __int16 word_513C3E[];
// 513C40: using guessed type __int16 word_513C40[];
// 513C42: using guessed type __int16 word_513C42[];
// 513C44: using guessed type __int16 word_513C44[];
// 513C46: using guessed type __int16 word_513C46[];
// 513C48: using guessed type __int16 word_513C48[];
// 513C4A: using guessed type __int16 word_513C4A[];
// 513C4C: using guessed type __int16 word_513C4C[];
// 513C4E: using guessed type __int16 word_513C4E[];
// 513C50: using guessed type __int16 word_513C50[];
// 513C52: using guessed type __int16 word_513C52[];
// 513C54: using guessed type __int16 word_513C54[];
// 513C56: using guessed type __int16 word_513C56[];
// 513C58: using guessed type __int16 word_513C58[];
// 513C5A: using guessed type __int16 word_513C5A[];
// 513C5C: using guessed type __int16 word_513C5C[];
// 513C5E: using guessed type __int16 word_513C5E[];
// 513C60: using guessed type __int16 word_513C60[];
// 513C62: using guessed type __int16 word_513C62[83];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526E78: using guessed type int g_CastleAmbientSpriteSet;
// 526E8C: using guessed type int dword_526E8C;
// 526E94: using guessed type int dword_526E94;
// 526E9C: using guessed type int dword_526E9C;
// 526EA8: using guessed type int dword_526EA8;
// 526EB4: using guessed type int dword_526EB4;
// 526EBC: using guessed type int dword_526EBC;
// 526EC4: using guessed type int dword_526EC4;
// 526ED0: using guessed type int dword_526ED0;
// 526EDC: using guessed type int dword_526EDC;
// 526EE8: using guessed type int dword_526EE8;

//----- (00421C20) --------------------------------------------------------
int __thiscall Castle_DrawAllAmbientAnimationLayers(void *this_ CLASH95_UNUSED)
{
  int i; // edx
  int layerIndex; // eax
  int result; // eax

  for ( i = 1; i <= 10; ++i )
  {
    layerIndex = i;
    result = Castle_DrawAmbientAnimationLayer(layerIndex);
  }
  return result;
}

//----- (00421C40) --------------------------------------------------------
unsigned int Castle_UpdateAmbientAnimationLayers(void)
{
  void *savedRenderDevice; // ebx
  unsigned int v2; // eax
  unsigned int v3; // edx
  unsigned int v4; // ecx
  unsigned int v5; // eax
  unsigned int v6; // edx
  unsigned int v7; // ecx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // ecx
  int v11; // edx
  unsigned int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  int v15; // edx
  unsigned int layer3RandomDelay; // eax
  int v17; // ecx
  int v18; // edx
  unsigned int v19; // eax
  unsigned int v20; // ecx
  int v21; // ecx
  unsigned int layer5RandomDelay; // eax
  int v23; // ecx
  unsigned int v24; // eax
  int v25; // edx
  unsigned int v26; // ecx
  unsigned int v27; // eax
  unsigned int v28; // edx
  unsigned int v29; // ecx
  int v30; // edx
  unsigned int v31; // ecx
  unsigned int v32; // eax
  int v33; // edx
  unsigned int layer8RandomDelay; // eax
  int v35; // ecx
  int v36; // edx
  unsigned int v37; // ecx
  unsigned int v38; // eax
  int v39; // edx
  unsigned int layer9RandomDelay; // eax
  int v41; // ecx
  unsigned int result; // eax
  int v43; // edx
  int v44; // edx
  unsigned int v45; // ecx
  int v46; // edx
  int v47; // ecx

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  v2 = Time_Now(g_CastleAmbientLayer1_LastTick + 10, (int)(intptr_t)&g_MainRenderDevice);
  if ( v4 < v2 )
  {
    g_CastleAmbientLayer1_LastTick = Time_Now(v4, v3);
    v3 = ++g_CastleAmbientLayer1_Frame % 0xCu;
    g_CastleAmbientLayer1_Frame %= 0xCu;
    Castle_DrawAmbientAnimationLayer(1);
  }
  v5 = Time_Now(g_CastleAmbientLayer2_LastTick + 10, v3);
  if ( v7 < v5 )
  {
    g_CastleAmbientLayer2_LastTick = Time_Now(v7, v6);
    v6 = (g_CastleAmbientLayer2_Frame + 1) % 0xCu;
    g_CastleAmbientLayer2_Frame = v6;
    Castle_DrawAmbientAnimationLayer(2);
  }
  v8 = Time_Now(g_CastleAmbientLayer4_LastTick + 10, v6);
  if ( v10 < v8 )
  {
    g_CastleAmbientLayer4_LastTick = Time_Now(v10, v9);
    v9 = (g_CastleAmbientLayer4_Frame + 1) % 0xCu;
    g_CastleAmbientLayer4_Frame = v9;
    Castle_DrawAmbientAnimationLayer(4);
  }
  if ( Time_Now(v10, v9) >= (unsigned int)g_CastleAmbientLayer3_NextDueTick )
  {
    v13 = Time_Now(g_CastleAmbientLayer3_DelayJitter + g_CastleAmbientLayer3_LastTick, v11);
    if ( v12 < v13 )
    {
      g_CastleAmbientLayer3_LastTick = Time_Now(v12, v11);
      Castle_DrawAmbientAnimationLayer(3);
      v12 = g_CastleAmbientLayer3AnimFrame + 1;
      g_CastleAmbientLayer3AnimFrame = v12;
      if ( v12 == 12 )
      {
        g_CastleAmbientLayer3AnimFrame = Rng_RandRange(0, 10);
        Time_Now(v14, 500);
        layer3RandomDelay = Rng_RandRange(0, v15);
        g_CastleAmbientLayer3_NextDueTick = layer3RandomDelay + v17;
        g_CastleAmbientLayer3_DelayJitter = Rng_RandRange(2, 10);
      }
    }
  }
  if ( Time_Now(v12, v11) >= (unsigned int)g_CastleAmbientLayer5_NextDueTick )
  {
    v19 = Time_Now(g_CastleAmbientLayer5_LastTick + 10, v18);
    if ( v20 < v19 )
    {
      g_CastleAmbientLayer5_LastTick = Time_Now(v20, v18);
      Castle_DrawAmbientAnimationLayer(5);
      if ( ++g_CastleAmbientLayer5_Frame == 23 )
      {
        g_CastleAmbientLayer5_Frame = 0;
        Time_Now(v21, 0);
        layer5RandomDelay = Rng_RandRange(500, 2000);
        g_CastleAmbientLayer5_NextDueTick = layer5RandomDelay + v23;
      }
    }
  }
  v24 = Time_Now(g_CastleAmbientLayer6_LastTick + g_CastleAmbientLayer6_DelayJitter, v18);
  if ( v26 < v24 )
  {
    g_CastleAmbientLayer6_LastTick = Time_Now(v26, v25);
    g_CastleAmbientLayer6_Frame = (g_CastleAmbientLayer6_Frame + 1) % 0xCu;
    g_CastleAmbientLayer6_DelayJitter = Rng_RandRange(5, 15);
    Castle_DrawAmbientAnimationLayer(6);
  }
  v27 = Time_Now(g_CastleAmbientLayer7_LastTick + 10, v25);
  if ( v29 < v27 )
  {
    g_CastleAmbientLayer7_LastTick = Time_Now(v29, v28);
    v28 = (g_CastleAmbientLayer7_Frame + 1) % 0xCu;
    g_CastleAmbientLayer7_Frame = v28;
    Castle_DrawAmbientAnimationLayer(7);
  }
  if ( Time_Now(v29, v28) >= (unsigned int)g_CastleAmbientLayer8_NextDueTick )
  {
    v32 = Time_Now(g_CastleAmbientLayer8_LastFrameTimeMs + 10, v30);
    if ( v31 < v32 )
    {
      g_CastleAmbientLayer8_LastFrameTimeMs = Time_Now(v31, v30);
      Castle_DrawAmbientAnimationLayer(8);
      if ( ++g_CastleAmbientLayer8_Frame == 41 )
      {
        g_CastleAmbientLayer8_Frame = 0;
        Time_Now(0, 2000);
        layer8RandomDelay = Rng_RandRange(500, v33);
        v31 = layer8RandomDelay + v35;
        g_CastleAmbientLayer8_NextDueTick = v31;
      }
    }
  }
  if ( Time_Now(v31, v30) >= (unsigned int)g_CastleAmbientLayer9_NextPlayTimeMs )
  {
    v38 = Time_Now(g_CastleAmbientLayer9_LastFrameTimeMs + 10, v36);
    if ( v37 < v38 )
    {
      g_CastleAmbientLayer9_LastFrameTimeMs = Time_Now(v37, v36);
      Castle_DrawAmbientAnimationLayer(9);
      if ( ++g_CastleAmbientLayer9_Frame == 31 )
      {
        g_CastleAmbientLayer9_Frame = 0;
        Time_Now(v37, 2000);
        layer9RandomDelay = Rng_RandRange(500, v39);
        v37 = layer9RandomDelay + v41;
        g_CastleAmbientLayer9_NextPlayTimeMs = v37;
      }
    }
  }
  result = Time_Now(v37, v36);
  if ( result >= g_CastleAmbientLayer10_NextPlayTimeMs
    && (result = Time_Now(g_CastleAmbientLayer10_LastFrameTimeMs + 10, v43), v45 < result)
    && (g_CastleAmbientLayer10_LastFrameTimeMs = Time_Now(v45, v44), result = Castle_DrawAmbientAnimationLayer(10), ++g_CastleAmbientLayer10AnimFrame, g_CastleAmbientLayer10AnimFrame == 31) )
  {
    g_CastleAmbientLayer10AnimFrame = 0;
    Time_Now(31, 2000);
    result = Rng_RandRange(500, v46);
    g_CastleAmbientLayer10_NextPlayTimeMs = result + v47;
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  }
  else
  {
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  }
  return result;
}
// 421C67: variable 'v4' is possibly undefined
// 421F79: variable 'v3' is possibly undefined
// 421C7D: variable 'v7' is possibly undefined
// 421C7F: variable 'v6' is possibly undefined
// 421CC1: variable 'v10' is possibly undefined
// 421CC3: variable 'v9' is possibly undefined
// 421D12: variable 'v11' is possibly undefined
// 421D19: variable 'v12' is possibly undefined
// 421D57: variable 'v14' is possibly undefined
// 421D60: variable 'v15' is possibly undefined
// 421D71: variable 'v17' is possibly undefined
// 421D97: variable 'v18' is possibly undefined
// 421D9E: variable 'v20' is possibly undefined
// 421DCE: variable 'v21' is possibly undefined
// 421DE6: variable 'v23' is possibly undefined
// 421E00: variable 'v26' is possibly undefined
// 421E02: variable 'v25' is possibly undefined
// 421E58: variable 'v29' is possibly undefined
// 421E5A: variable 'v28' is possibly undefined
// 421EA2: variable 'v30' is possibly undefined
// 421EA9: variable 'v31' is possibly undefined
// 421EE8: variable 'v33' is possibly undefined
// 421EED: variable 'v35' is possibly undefined
// 421F0B: variable 'v36' is possibly undefined
// 421F12: variable 'v37' is possibly undefined
// 421F52: variable 'v39' is possibly undefined
// 421F57: variable 'v41' is possibly undefined
// 421FBC: variable 'v43' is possibly undefined
// 421FC3: variable 'v45' is possibly undefined
// 421FC5: variable 'v44' is possibly undefined
// 422004: variable 'v46' is possibly undefined
// 42200B: variable 'v47' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 51416C: using guessed type int dword_51416C;
// 514170: using guessed type int dword_514170;
// 526E88: using guessed type int dword_526E88;
// 526E8C: using guessed type int dword_526E8C;
// 526E90: using guessed type int dword_526E90;
// 526E94: using guessed type int dword_526E94;
// 526E98: using guessed type int dword_526E98;
// 526E9C: using guessed type int dword_526E9C;
// 526EA0: using guessed type int dword_526EA0;
// 526EA4: using guessed type int dword_526EA4;
// 526EA8: using guessed type int dword_526EA8;
// 526EAC: using guessed type int dword_526EAC;
// 526EB0: using guessed type int dword_526EB0;
// 526EB4: using guessed type int dword_526EB4;
// 526EB8: using guessed type int dword_526EB8;
// 526EBC: using guessed type int dword_526EBC;
// 526EC0: using guessed type int dword_526EC0;
// 526EC4: using guessed type int dword_526EC4;
// 526EC8: using guessed type int dword_526EC8;
// 526ECC: using guessed type int dword_526ECC;
// 526ED0: using guessed type int dword_526ED0;
// 526ED4: using guessed type int dword_526ED4;
// 526ED8: using guessed type int dword_526ED8;
// 526EDC: using guessed type int dword_526EDC;
// 526EE0: using guessed type int dword_526EE0;
// 526EE4: using guessed type int dword_526EE4;
// 526EE8: using guessed type int dword_526EE8;

//----- (00422020) --------------------------------------------------------
int * Castle_RebuildSceneBuffers(int paletteBuffer, DWORD runtime_context)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char castleSpriteName[20]; // [esp-6h] [ebp-1Ch] BYREF
  int savedArg CLASH95_UNUSED; // [esp+Eh] [ebp-8h]
  unsigned int primary_surface_handle;

  savedArg = paletteBuffer;
  Castle_RenderCompositeSceneLayers(g_PrimaryRenderSurface, 0, g_SelectedBuildingRecord, 0);
  strcpy(castleSpriteName, "zamek_1");
  castleSpriteName[6] = g_CurrentPlayerIndex + 49;
  Palette_LoadOrBuildBlendLookupTable(castleSpriteName, (int)(intptr_t)g_CastleScreenPaletteBuffer, v3, runtime_context);
  Render_LoadResourceSprite_v4(8, g_CastleScreenPaletteBuffer, v4, 0, runtime_context);
  Render_LoadResourceSprite_v4(7, g_CastleScreenPaletteBuffer, v5, 0, runtime_context);
  Render_LoadResourceSprite_v4(13, g_CastleScreenPaletteBuffer, v6, 0, runtime_context);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  Castle_DrawStatusPanel();
  RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_CastleScreenPaletteBuffer, 0, runtime_context);
  RenderState_DrawCursorSpriteToPrimarySurface((int)(intptr_t)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
    fprintf(
      stderr,
      "[castle] before_surface_copy map_surface=%08x primary_surface=%08x map_sum=%08x primary_sum=%08x\n",
      (unsigned int)g_PrimaryRenderSurface,
      primary_surface_handle,
      Diagnostics_SurfaceByteChecksum(g_PrimaryRenderSurface),
      Diagnostics_SurfaceByteChecksum(primary_surface_handle));
  }
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
    fprintf(
      stderr,
      "[castle] after_surface_copy map_surface=%08x primary_surface=%08x map_sum=%08x primary_sum=%08x\n",
      (unsigned int)g_PrimaryRenderSurface,
      primary_surface_handle,
      Diagnostics_SurfaceByteChecksum(g_PrimaryRenderSurface),
      Diagnostics_SurfaceByteChecksum(primary_surface_handle));
  }
  Castle_UpdateAmbientAnimationLayers();
  Castle_RenderCompositeSceneLayers(g_CastleScreenSurface, 1, g_SelectedBuildingRecord, 0);
  return Palette_FadeInFromBlack((int *)&g_MainRenderDevice, g_CastleScreenPaletteBuffer, 20);
}
// 422057: variable 'v3' is possibly undefined
// 422066: variable 'v4' is possibly undefined
// 422075: variable 'v5' is possibly undefined
// 422084: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526A64: using guessed type int g_SelectedBuildingRecord;
// 526A68: using guessed type int g_CastleScreenSurface;
// 526A70: using guessed type _BYTE byte_526A70[1024];
// 544CD8: using guessed type _DWORD g_RenderState[9];
