/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004338C0) --------------------------------------------------------
int  BuildingGarrisonDialog_RequestClose(int widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_BuildingGarrisonDialogCloseRequested = 1;
  return result;
}
// 532148: using guessed type int dword_532148;

//----- (004338E0) --------------------------------------------------------
int  BuildingGarrisonDialog_ShowProductionDialog(int widget, DWORD renderContext, char panelArg)
{
  int result; // eax
  char *backgroundPath; // edx
  char resourceHandle; // bl
  CHAR *palettePath; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  UIWidget_PlayPressedReleaseAnimation(widget);
  result = g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
    Render_Pump();
    Castle_ShowUnitProductionPanel(g_BuildingGarrisonDialogActiveBuilding, renderContext, panelArg);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      backgroundPath = aCastle_chrD_15;
    else
      backgroundPath = aCastle_pogD_15;
    resourceHandle = g_BuildingGarrisonDialogResourceHandle;
    RenderSurface_InvokeSlot48LoadPCX(
      (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
      backgroundPath,
      0,
      (uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      palettePath = aCastle_chrD_16;
    else
      palettePath = aCastle_pogD_16;
    Palette_LoadOrBuildBlendLookupTable(palettePath, g_BuildingGarrisonDialogResourceHandle, g_BuildingGarrisonDialogUseChrTheme, renderContext);
    RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, g_BuildingGarrisonDialogResourceHandle, v7, renderContext);
    Render_LoadResourceSprite_v4(5, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, v8, resourceHandle, renderContext);
    Render_LoadResourceSprite_v4(7, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, v9, resourceHandle, renderContext);
    Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, v10, resourceHandle, renderContext);
    g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
    BuildingGarrisonDialog_EnsureActionWidgets(g_BuildingGarrisonDialogActiveBuilding);
    UIWidgetTable_InitDrawStates((_DWORD *)BuildingGarrisonDialogActions);
    RenderSurface_InvokeSlot36((_DWORD *)g_RenderDevice);
    BuildingGarrisonDialog_DrawSlotGrid(-1);
    BuildingGarrisonDialog_DrawSelectedUnitPanel();
    BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(v11, 20, renderContext);
    Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_BuildingGarrisonDialogResourceHandle, 20);
    Render_Present((int)(intptr_t)g_RenderState);
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
    Render_Present((int)(intptr_t)g_RenderState);
    Render_Pump();
    return Render_Present((int)(intptr_t)g_RenderState);
  }
  return result;
}
// 43396D: variable 'v7' is possibly undefined
// 43397D: variable 'v8' is possibly undefined
// 43398D: variable 'v9' is possibly undefined
// 43399D: variable 'v10' is possibly undefined
// 4339D8: variable 'v11' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514FC0: using guessed type _DWORD BuildingGarrisonDialogActions[3];
// 5202E0: using guessed type int dword_5202E0;
// 526A2C: using guessed type int dword_526A2C;
// 53214C: using guessed type int g_BuildingGarrisonDialogUseChrTheme;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00433A40) --------------------------------------------------------
void * BuildingGarrisonDialog_ToggleRepairSelectedUnits(int widget, DWORD gameContext)
{
  void *result; // eax
  int slotIndex; // ecx
  int selectedSlotIndex; // ebx

  UIWidget_PlayPressedReleaseAnimation(widget);
  result = (void *)(uintptr_t)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
  {
    slotIndex = 0;
    selectedSlotIndex = 0;
    do
    {
      if ( g_BuildingGarrisonDialogSelectedSlots[selectedSlotIndex] )
      {
        if ( (BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, slotIndex) & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
          Building_ClearGarrisonRepairTimer(g_BuildingGarrisonDialogActiveBuilding, slotIndex);
        else
          Building_RepairUnit(g_BuildingGarrisonDialogActiveBuilding, slotIndex, gameContext);
      }
      ++slotIndex;
      ++selectedSlotIndex;
    }
    while ( slotIndex < 12 );
    memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
    return BuildingGarrisonDialog_DrawSlotGrid(-1);
  }
  return result;
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];

//----- (00433AC0) --------------------------------------------------------
void * BuildingGarrisonDialog_ToggleTrainingSelectedUnits(int widget, DWORD gameContext)
{
  void *result; // eax
  int slotIndex; // ecx
  int selectedSlotIndex; // ebx

  UIWidget_PlayPressedReleaseAnimation(widget);
  result = (void *)(uintptr_t)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
  {
    slotIndex = 0;
    selectedSlotIndex = 0;
    do
    {
      if ( g_BuildingGarrisonDialogSelectedSlots[selectedSlotIndex] )
      {
        if ( (BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, slotIndex) & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
          Building_ClearGarrisonTrainingTimer(g_BuildingGarrisonDialogActiveBuilding, slotIndex);
        else
          Building_TrainUnit(g_BuildingGarrisonDialogActiveBuilding, selectedSlotIndex * 4, gameContext);
      }
      ++slotIndex;
      ++selectedSlotIndex;
    }
    while ( slotIndex < 12 );
    memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
    return BuildingGarrisonDialog_DrawSlotGrid(-1);
  }
  return result;
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];

//----- (00433B40) --------------------------------------------------------
int  BuildingGarrisonDialog_BeginSelectedUnitsExit(int widget)
{
  int slotIndex; // eax
  int selectedCount; // ebx
  int selectedSlotIndex; // edx
  int writeIndex; // ecx
  int selectedSlots[16]; // [esp+4h] [ebp-40h]

  slotIndex = 0;
  selectedCount = 0;
  selectedSlotIndex = 0;
  writeIndex = 0;
  do
  {
    if ( g_BuildingGarrisonDialogSelectedSlots[selectedSlotIndex] )
    {
      ++writeIndex;
      ++selectedCount;
      selectedSlots[writeIndex - 1] = slotIndex;
    }
    ++slotIndex;
    ++selectedSlotIndex;
  }
  while ( slotIndex < 12 );
  selectedSlots[selectedCount] = -1;
  Diagnostics_TraceWorldMapActionEvent(
    "garrison_exit_begin",
    selectedCount,
    selectedSlots[0],
    *(_BYTE *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 0),
    *(_BYTE *)(uintptr_t)(g_BuildingGarrisonDialogActiveBuilding + 1));
  if ( selectedSlots[0] == -1 || !Building_HasFreeAdjacentExitTile((unsigned __int8 *)(uintptr_t)g_BuildingGarrisonDialogActiveBuilding) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "garrison_exit_blocked",
      selectedCount,
      selectedSlots[0],
      Building_HasFreeAdjacentExitTile((unsigned __int8 *)(uintptr_t)g_BuildingGarrisonDialogActiveBuilding),
      0);
    Audio_PlayButtonSound(aWrong_7);
    return Render_Begin((int)(intptr_t)g_RenderState, 0);
  }
  else
  {
    UIWidget_ShowPressedState(widget);
    g_BuildingGarrisonDialogPendingExitCountdown = 1;
    Audio_PlaySoundEffectByName(aDclose, 64);
    return UIWidget_ShowReleasedState(widget, 1);
  }
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00433BF0) --------------------------------------------------------
int  BuildingGarrisonDialog_TickAnimations(double deltaTime)
{
  int previous_resource_handle;

  previous_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  BuildingGarrisonDialog_AnimateSelectedUnit(0);
  BuildingGarrisonDialog_TickExitCountdown(0, deltaTime);
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
}

//----- (00434110) --------------------------------------------------------
int CastleProduction_DrawSelectedUnitPortrait(void)
{
  void *savedRenderDevice; // ebp
  __int16 SpriteWidth; // ax
  int cursorOverlayPresented; // edi
  __int16 spriteHeight; // cx
  int SpriteForChar; // eax
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  DLX_GetSpriteHeight(g_CastleProductionSelectedUnitSpriteSet, 0);
  SpriteWidth = DLX_GetSpriteWidth(g_CastleProductionSelectedUnitSpriteSet, 0);
  cursorOverlayPresented = g_CursorOverlayPresented;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0x50u, spriteHeight + 80, 0xC3u, SpriteWidth + 195);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar(g_CastleProductionSelectedUnitSpriteSet, g_CastleProductionUnitPortraitFrame);
  result = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46)
                                                                                    + 52))(
             193,
             SpriteForChar,
             -1,
             -1,
             -1,
             -1,
             1,
             0,
             0);
  if ( cursorOverlayPresented )
    result = Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 43415E: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5322CC: using guessed type int dword_5322CC;
// 5322D0: using guessed type int dword_5322D0[];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00434760) --------------------------------------------------------
unsigned int __thiscall CastleProduction_AnimateSelectedUnitPortrait(void *this)
{
  unsigned int result; // eax
  unsigned int v2; // edx
  int v3; // ecx

  result = Time_Now((int)(intptr_t)this, g_CastleProductionPortraitAnimLastTickMs + 10);
  if ( v2 <= result )
  {
    g_CastleProductionPortraitAnimLastTickMs = Time_Now(v3, v2);
    g_CastleProductionUnitPortraitFrame = ((_BYTE)g_CastleProductionUnitPortraitFrame + 1) & 7;
    return CastleProduction_DrawSelectedUnitPortrait();
  }
  return result;
}
// 434771: variable 'v2' is possibly undefined
// 434776: variable 'v3' is possibly undefined
// 532200: using guessed type int dword_532200;
// 5322CC: using guessed type int dword_5322CC;

//----- (004347A0) --------------------------------------------------------
void * CastleProduction_RedrawSelectedUnitPanel(int a1, int a2, DWORD renderContext, int a4, int a5)
{
  int v5 CLASH95_UNUSED; // ecx
  _DWORD *spriteSet; // eax
  int v7; // ecx
  int queryHandle; // ecx
  int paletteIndex; // ecx
  int *srcPalettePtr; // ebx
  _DWORD *dstPaletteEntry; // edx
  int SpriteForChar; // eax
  int stripUnitIndex; // ebx
  int rowY; // esi
  int availableUnitByteOffset; // ecx
  int unitType; // edx
  int v17 CLASH95_UNUSED; // ecx
  int v18 CLASH95_UNUSED; // ecx
  int v19 CLASH95_UNUSED; // ecx
  int v20 CLASH95_UNUSED; // ecx
  int v21 CLASH95_UNUSED; // ecx
  int selectedUnitType; // esi
  int infoPanelSprite; // eax
  DWORD renderMethods; // ebp
  const UnitTypeRuntimeCoreMetadataRecord *unitMetadataPtr; // esi
  const char *selectedUnitName;
  int baseMorale;
  DWORD v26; // ebp
  int v27; // edx
  int v28; // edx
  __int16 SpriteHeight; // ax
  __int16 infoSpriteHeight; // ax
  void *result; // eax
  unsigned __int16 unitStripRight; // [esp-18h] [ebp-490h]
  unsigned __int16 infoPanelRight; // [esp-18h] [ebp-490h]
  int v35; // [esp-8h] [ebp-480h]
  int loadedPaletteData; // [esp+380h] [ebp-F8h] BYREF
  char pathBuffer[100]; // [esp+400h] [ebp-78h] BYREF
  DWORD renderMethods2; // [esp+464h] [ebp-14h]
  void *savedRenderDevice; // [esp+468h] [ebp-10h]
  int panelBaseY; // [esp+46Ch] [ebp-Ch]

  if ( g_CastleProductionSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_CastleProductionSelectedUnitSpriteSet);
  Unit_BuildSelectedUnitPanelIconSpritePath(pathBuffer, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], a1);
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0x1010, a2, renderContext);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, pathBuffer);
  v35 = v7;
  g_CastleProductionSelectedUnitSpriteSet = (int)(intptr_t)spriteSet;
  Unit_BuildSelectedUnitPanelIconPalettePath(pathBuffer, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v7);
  Palette_LoadFromQueryHandle(queryHandle, renderContext);
  paletteIndex = 224;
  srcPalettePtr = &loadedPaletteData;
  do
  {
    ++srcPalettePtr;
    dstPaletteEntry = (_DWORD *)(uintptr_t)(g_CastleProductionPaletteBuffer + 4 * paletteIndex++);
    *dstPaletteEntry = *(srcPalettePtr - 1);
  }
  while ( paletteIndex <= 255 );
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 20);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD, int, int, int, int))(uintptr_t)(*((_DWORD *)g_RenderDevice
                                                                                                  + 46)
                                                                                                + 52))(
    28,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0,
    a4,
    a2,
    v35,
    a5);
  Render_ReleaseSurface(5, renderContext);
  stripUnitIndex = g_CastleProductionSelectedAvailableUnitIndex - 2;
  rowY = 35;
  availableUnitByteOffset = 4 * (g_CastleProductionSelectedAvailableUnitIndex - 2);
  while ( stripUnitIndex <= g_CastleProductionSelectedAvailableUnitIndex + 2 )
  {
    if ( stripUnitIndex < 0 || (unitType = g_CastleProduction_AvailableUnitTypes[availableUnitByteOffset / 4], unitType == -1) )
    {
      availableUnitByteOffset += 4;
      ++stripUnitIndex;
      rowY += 17;
    }
    else if ( stripUnitIndex == g_CastleProductionSelectedAvailableUnitIndex )
    {
      Render_ReleaseSurface(9, 0x2Du);
      UI_DrawText(
        45,
        rowY,
        (int)(intptr_t)UnitType_GetLocalizedName((unit_type)unitType));
      Render_ReleaseSurface(5, 0x2Du);
      availableUnitByteOffset += 4;
      ++stripUnitIndex;
      rowY += 17;
    }
    else
    {
      if ( Building_HasUnitLicence(g_CastleProductionBuildingPtr, unitType) )
      {
        Render_ReleaseSurface(20, 0x2Du);
        UI_DrawText(
          45,
          rowY,
          (int)(intptr_t)UnitType_GetLocalizedName((unit_type)unitType));
        Render_ReleaseSurface(5, 0x2Du);
      }
      else
      {
        UI_DrawText(
          45,
          rowY,
          (int)(intptr_t)UnitType_GetLocalizedName((unit_type)unitType));
      }
      availableUnitByteOffset += 4;
      ++stripUnitIndex;
      rowY += 17;
    }
  }
  selectedUnitType = g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
  infoPanelSprite = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 17);
  renderMethods = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int))(uintptr_t)(renderMethods + 52))(186, infoPanelSprite, -1, -1, -1);
  unitMetadataPtr = &g_UnitTypeRuntimeCoreMetadata[selectedUnitType];
  Render_ReleaseSurface(7, renderMethods);
  selectedUnitName = UnitType_GetLocalizedName((unit_type)selectedUnitType);
  v26 = (DWORD)(uintptr_t)selectedUnitName;
  UI_DrawTextFmt(69, 133, 261, 191, 3, selectedUnitName);
  baseMorale = (unitMetadataPtr->flags & 2) ? 6 : 10;
  UI_DrawTextFmt(69, 201, 217, panelBaseY + 95, 2, aD_68, unitMetadataPtr->base_defense_power + baseMorale / 5);
  UI_DrawTextFmt(69, 154, 174, panelBaseY + 50, 2, aD_69, unitMetadataPtr->base_action_points);
  UI_DrawTextFmt(69, 201, 217, panelBaseY + 50, 2, aD_70, baseMorale);
  UI_DrawTextFmt(69, 229, 260, v27, 2, (int)(intptr_t)a0_3);
  if ( unitMetadataPtr->base_shot_power )
  {
    if ( unitMetadataPtr->base_melee_attack )
    {
      UI_DrawTextFmt(154, 154, 174, panelBaseY + 74, 2, aD_73, unitMetadataPtr->base_melee_attack + baseMorale / 5);
      UI_DrawTextFmt(154, 154, v28, panelBaseY + 95, 2, aD_74, unitMetadataPtr->base_shot_power);
    }
    else
    {
      DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 19);
      renderMethods2 = *((_DWORD *)g_RenderDevice + 46);
      v26 = renderMethods2;
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderMethods2 + 52))(-1, -1, -1, -1, 1, 0, 0);
      UI_DrawTextFmt(154, 154, 174, panelBaseY + 95, 2, aD_72, unitMetadataPtr->base_shot_power);
    }
  }
  else
  {
    DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 18);
    renderMethods2 = *((_DWORD *)g_RenderDevice + 46);
    v26 = renderMethods2;
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderMethods2 + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(154, 154, 174, panelBaseY + 95, 2, aD_71, unitMetadataPtr->base_melee_attack + baseMorale / 5);
  }
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 340, 72, 0x138u, 0x16Eu, 0x48u, 0x154u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, v26);
  UI_DrawTextFmt(-1, 0, 119, 348, 2, aD_75, unitMetadataPtr->production_licence_cost);
  UI_DrawTextFmt(-1, 0, 215, 348, 2, aD_76, unitMetadataPtr->production_cost);
  UI_DrawTextFmt(-1, 0, 311, 348, 2, aD_77, unitMetadataPtr->production_time);
  unitStripRight = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x14u) + 28;
  SpriteHeight = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x14u);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 28, 40, SpriteHeight + 40, unitStripRight, 0x28u, 0x1Cu);
  infoPanelRight = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x11u) + 186;
  infoSpriteHeight = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x11u);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 186, 69, infoSpriteHeight + 69, infoPanelRight, 0x45u, 0xBAu);
  Render_SaveBackbuffer((int)(intptr_t)&g_MainRenderDevice);
  CastleProduction_DrawSelectedUnitPortrait();
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 4347A0: could not find valid save-restore pair for edi
// 4347A0: could not find valid save-restore pair for esi
// 4347CF: variable 'a1' is possibly undefined
// 4347D9: variable 'v5' is possibly undefined
// 4347EF: variable 'v7' is possibly undefined
// 434820: variable 'v8' is possibly undefined
// 434934: variable 'v18' is possibly undefined
// 43495D: variable 'v19' is possibly undefined
// 434969: variable 'v17' is possibly undefined
// 4349A1: variable 'v20' is possibly undefined
// 4349C9: variable 'v21' is possibly undefined
// 434B1F: variable 'v27' is possibly undefined
// 434BA8: variable 'v28' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202E0: using guessed type int dword_5202E0;
// 53220C: using guessed type int dword_53220C;
// 532218: using guessed type int dword_532218;
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532224: using guessed type unit_type dword_532224[41];
// 5322D0: using guessed type int dword_5322D0[];

//----- (00434E20) --------------------------------------------------------
void * CastleProduction_DrawLicenceGrid(void)
{
  int slotIndex; // esi
  int slotX; // edi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // edx
  void *result; // eax
  int SpriteForChar; // edx
  int cursorOverlayPresented; // [esp+8Ch] [ebp-2Ch]
  int slotAnimIndex; // [esp+90h] [ebp-28h]
  void *savedRenderDevice; // [esp+98h] [ebp-20h]
  int slotY; // [esp+9Ch] [ebp-1Ch]

  slotIndex = 0;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  slotAnimIndex = 0;
  do
  {
    slotX = 48 * (slotIndex % 4) + 426;
    slotY = 82 * ((slotIndex - (__CFSHL__(slotIndex >> 31, 2) + 4 * (slotIndex >> 31))) >> 2) + 32;
    if ( slotIndex % 4 >= 2 )
      slotX = 48 * (slotIndex % 4) + 425;
    cursorOverlayPresented = g_CursorOverlayPresented;
    RenderState_PumpIfRectInViewBounds(g_RenderState, slotX, slotX + 31, slotY, slotY + 63);
    if ( *(char *)(uintptr_t)(slotIndex + g_CastleProductionBuildingPtr + 402) == -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 22);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        slotY,
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
      v2 = DLX_GetSpriteForChar(g_CastleProduction_LicenceSlotSpriteHandles[slotAnimIndex], g_CastleProductionSlotAnimFrames[slotAnimIndex]);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        slotY,
        v2,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      if ( slotIndex == g_ProductionGridSelectedIndex )
      {
        v3 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 32);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
          82 * ((slotIndex - (__CFSHL__(slotIndex >> 31, 2) + 4 * (slotIndex >> 31))) >> 2) + 33,
          v3,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(g_CastleProductionBuildingPtr) == slotIndex )
      {
        v4 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 21);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
          slotY,
          v4,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( slotIndex == g_LicenceGridAddAnimSlotIndex )
      {
        v5 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, g_CastleProductionLicenceTransitionFrame + 22);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
          slotY,
          v5,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( slotIndex == g_CastleLicenceRemovalSlotIndex )
      {
        v6 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 30 - g_CastleProductionLicenceTransitionFrame);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
          slotY,
          v6,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
    }
    if ( cursorOverlayPresented )
      Render_Present((int)(intptr_t)g_RenderState);
    ++slotIndex;
    ++slotAnimIndex;
  }
  while ( slotIndex < 12 );
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 53220C: using guessed type int dword_53220C;
// 532218: using guessed type int dword_532218;
// 5322C8: using guessed type int dword_5322C8;
// 5322D4: using guessed type int dword_5322D4[];
// 532304: using guessed type int dword_532304[];
// 532334: using guessed type int dword_532334;
// 532338: using guessed type int dword_532338;
// 53233C: using guessed type int dword_53233C;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (004350A0) --------------------------------------------------------
int  CastleProduction_ReloadLicenceSlotSprite(int slotIndex, char resourceContext)
{
  int result; // eax
  DWORD sprite_set; // ebp
  char iconSpritePath[112]; // [esp+0h] [ebp-70h] BYREF

  result = *(char *)(uintptr_t)(slotIndex + g_CastleProductionBuildingPtr + 402);
  if ( result == -1 )
  {
    if ( g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] )
    {
      result = nfree_(g_CastleProduction_LicenceSlotSpriteHandles[slotIndex]);
      g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] = 0;
    }
    g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] = 0;
  }
  else
  {
    sprite_set = g_CastleProduction_LicenceSlotSpriteHandles[slotIndex];
    if ( sprite_set )
    {
      nfree_(sprite_set);
      g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] = 0;
    }
    Unit_BuildGarrisonSlotIconSpritePath(iconSpritePath, *(_BYTE *)(uintptr_t)(slotIndex + g_CastleProductionBuildingPtr + 402), slotIndex);
    result = Mem_Alloc(4112, 0x1010, resourceContext, sprite_set);
    if ( result )
      result = (int)(intptr_t)DLXSpriteSet_Load((_DWORD *)(uintptr_t)result, iconSpritePath);
    g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] = result;
  }
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 532218: using guessed type int dword_532218;
// 532304: using guessed type int dword_532304[12];

//----- (00435150) --------------------------------------------------------
void * CastleProduction_ReloadLicenceSlotSprites(char resourceContext)
{
  int i; // edx

  for ( i = 0; i < 12; CastleProduction_ReloadLicenceSlotSprite(i, resourceContext) )
    ;
  return CastleProduction_DrawLicenceGrid();
}
// 435163: variable 'i' is possibly undefined

//----- (00435180) --------------------------------------------------------
void * CastleProduction_TickLicenceGridAnimations(int a1, DWORD gameContext)
{
  void *result; // eax
  unsigned int v3; // edx
  int v4; // ecx
  int i; // eax

  result = (void *)(uintptr_t)Time_Now(a1, g_CastleProductionLicenceGridAnimLastTickMs + 10);
  if ( v3 <= (unsigned int)(intptr_t)result )
  {
    g_CastleProductionLicenceGridAnimLastTickMs = Time_Now(v4, v3);
    for ( i = 0; i != 12; ++i )
      g_CastleProductionSlotAnimFrames[i] = (g_CastleProductionSlotAnimFrames[i] + 1) & 7;
    if ( (g_LicenceGridAddAnimSlotIndex != -1 || g_CastleLicenceRemovalSlotIndex != -1) && ++g_CastleProductionLicenceTransitionFrame == 8 )
    {
      if ( g_CastleLicenceRemovalSlotIndex != -1 )
      {
        Building_RemoveUnitLicence(g_CastleProductionBuildingPtr, *(char *)(uintptr_t)(g_CastleLicenceRemovalSlotIndex + g_CastleProductionBuildingPtr + 402), gameContext);
        nfree_(g_CastleProduction_LicenceSlotSpriteHandles[g_CastleLicenceRemovalSlotIndex]);
        g_ProductionGridSelectedIndex = -1;
        g_CastleProduction_LicenceSlotSpriteHandles[g_CastleLicenceRemovalSlotIndex] = 0;
      }
      g_CastleProductionLicenceTransitionFrame = 0;
      g_CastleLicenceRemovalSlotIndex = -1;
      g_LicenceGridAddAnimSlotIndex = -1;
    }
    return CastleProduction_DrawLicenceGrid();
  }
  return result;
}
// 435192: variable 'v3' is possibly undefined
// 435197: variable 'v4' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 532204: using guessed type int dword_532204;
// 532218: using guessed type int dword_532218;
// 5322C8: using guessed type int dword_5322C8;
// 5322D0: using guessed type int dword_5322D0[];
// 5322D4: using guessed type int dword_5322D4[];
// 532304: using guessed type int dword_532304[12];
// 532334: using guessed type int dword_532334;
// 532338: using guessed type int dword_532338;
// 53233C: using guessed type int dword_53233C;

//----- (00435280) --------------------------------------------------------
int  CastleProduction_DrawProductionStatus(DWORD renderContext)
{
  int result; // eax
  char *turnLabelText; // eax
  int statusLine1; // edi
  int turnsRemaining; // eax
  int statusDetailC_Strings[3]; // [esp+0h] [ebp-6Ch]
  int v6[3]; // [esp+Ch] [ebp-60h] BYREF
  int statusLine1_Strings[3]; // [esp+18h] [ebp-54h] BYREF
  int statusDetailA_Strings[3]; // [esp+24h] [ebp-48h]
  int statusDetailB_Strings[3]; // [esp+30h] [ebp-3Ch]
  int statusHeader_Strings[2]; // [esp+3Ch] [ebp-30h]
  char *v11 CLASH95_UNUSED; // [esp+44h] [ebp-28h]
  int statusHeaderFull_Strings[9]; // [esp+48h] [ebp-24h]

  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 288, 401, 0x251u, 0x165u, 0x191u, 0x120u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderContext);
  result = g_CastleProductionBuildingPtr;
  if ( BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(g_CastleProductionBuildingPtr) != -1 )
  {
    if ( Building_CountGarrison(g_CastleProductionBuildingPtr) < 12 || BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) > 1 )
    {
      statusHeader_Strings[0] = (int)(intptr_t)UI_Locale_StatusHeader[0];
      statusHeader_Strings[1] = (int)(intptr_t)UI_Locale_StatusHeader[1];
      v11 = UI_Locale_StatusHeader[2];
      if ( BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) == 1 )
        turnLabelText = aDZugBisZum;
      else
        turnLabelText = aDZbgeBisZum;
      statusLine1_Strings[0] = (int)(intptr_t)UI_Locale_StatusLine1[0];
      statusLine1_Strings[1] = (int)(intptr_t)UI_Locale_StatusLine1[1];
      statusLine1_Strings[2] = (int)(intptr_t)UI_Locale_StatusLine1[2];
      statusDetailA_Strings[0] = (int)(intptr_t)UI_Locale_StatusDetail_A[0];
      statusDetailA_Strings[1] = (int)(intptr_t)UI_Locale_StatusDetail_A[1];
      statusDetailA_Strings[2] = (int)(intptr_t)UI_Locale_StatusDetail_A[2];
      statusDetailB_Strings[0] = (int)(intptr_t)UI_Locale_StatusDetail_B[0];
      statusDetailB_Strings[1] = (int)(intptr_t)UI_Locale_StatusDetail_B[1];
      statusDetailB_Strings[2] = (int)(intptr_t)UI_Locale_StatusDetail_B[2];
      statusDetailC_Strings[0] = (int)(intptr_t)UI_Locale_StatusDetail_C[0];
      statusDetailC_Strings[1] = (int)(intptr_t)UI_Locale_StatusDetail_C[1];
      statusDetailC_Strings[2] = (int)(intptr_t)UI_Locale_StatusDetail_C[2];
      v11 = turnLabelText;
      UI_DrawTextFmt((int)(intptr_t)v6, 401, 593, 297, 3, statusHeader_Strings[(unsigned __int8)g_LanguageIndex]);
      statusLine1 = statusLine1_Strings[(unsigned __int8)g_LanguageIndex];
      UI_DrawTextFmt(statusLine1, 401, 593, 317, 3, statusLine1);
      turnsRemaining = BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr);
      if ( turnsRemaining == 1 )
      {
        return UI_DrawTextFmt(statusLine1, 401, 593, 337, 3, statusDetailB_Strings[(unsigned __int8)g_LanguageIndex]);
      }
      else if ( turnsRemaining < 2 || turnsRemaining > 4 )
      {
        return UI_DrawTextFmt(statusLine1, 401, 593, 337, 3, statusDetailA_Strings[(unsigned __int8)g_LanguageIndex]);
      }
      else
      {
        return UI_DrawTextFmt(statusLine1, 401, 593, 337, 3, statusDetailC_Strings[(unsigned __int8)g_LanguageIndex]);
      }
    }
    else
    {
      statusHeaderFull_Strings[0] = (int)(intptr_t)UI_Locale_StatusHeader_Full[0];
      statusHeaderFull_Strings[1] = (int)(intptr_t)UI_Locale_StatusHeader_Full[1];
      statusHeaderFull_Strings[2] = (int)(intptr_t)UI_Locale_StatusHeader_Full[2];
      v6[0] = (int)(intptr_t)UI_Locale_StatusLine1_Full[0];
      v6[1] = (int)(intptr_t)UI_Locale_StatusLine1_Full[1];
      v6[2] = (int)(intptr_t)UI_Locale_StatusLine1_Full[2];
      UI_DrawTextFmt((int)(intptr_t)statusLine1_Strings, 401, 593, 307, 3, statusHeaderFull_Strings[(unsigned __int8)g_LanguageIndex]);
      return UI_DrawTextFmt((int)(intptr_t)statusLine1_Strings, 401, 593, 327, 3, v6[(unsigned __int8)g_LanguageIndex]);
    }
  }
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515414: using guessed type char *off_515414[2];
// 515420: using guessed type char *off_515420[5];
// 51542C: using guessed type char *off_51542C[2];
// 515438: using guessed type char *off_515438[2];
// 515444: using guessed type char *off_515444[2];
// 515450: using guessed type char *off_515450[6];
// 51545C: using guessed type char *off_51545C[3];
// 5202E0: using guessed type int dword_5202E0;
// 532218: using guessed type int dword_532218;

//----- (00435500) --------------------------------------------------------
int  UI_DrawActionBox(int drawContext)
{
  void *savedRenderDevice; // esi
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 425, 285, 0x15Eu, 0x1C2u, 0x11Du, 0x1A9u);
  result = UI_DrawTextFmt(drawContext, 285, 349, 430, 3, (int)(intptr_t)aD_38);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532218: using guessed type int dword_532218;

//----- (00435580) --------------------------------------------------------
int UI_GetGridIndexFromMouse(void)
{
  int mouseX; // eax
  int gridY; // ebx
  int col; // ecx
  int row; // eax

  mouseX = g_MouseCursorRawX >> g_CursorCoordShift;
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= 426
    && g_MouseCursorRawY >> g_CursorCoordShift >= 32
    && (gridY = (g_MouseCursorRawY >> g_CursorCoordShift) - 32, (mouseX - 426) % 48 <= 33)
    && gridY % 82 <= 64
    && (col = (mouseX - 426) / 48, row = gridY / 82, col < 4)
    && row < 3 )
  {
    return col + 4 * row;
  }
  else
  {
    return -1;
  }
}
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00435620) --------------------------------------------------------
int  CastleProduction_SetExitSignal(int widget)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_CastleProductionExitSignal = v3;
  return result;
}
// 43562B: variable 'v3' is possibly undefined
// 532210: using guessed type int g_CastleProductionExitSignal;

//----- (00435640) --------------------------------------------------------
int  CastleProduction_SelectPreviousAvailableUnit(int widget, int a2, DWORD renderContext, int a4, int a5)
{
  int v5; // ecx
  int v6; // ecx

  UIWidget_ShowPressedState(widget);
  if ( g_CastleProductionSelectedAvailableUnitIndex )
    --g_CastleProductionSelectedAvailableUnitIndex;
  CastleProduction_RedrawSelectedUnitPanel(v5, a2, renderContext, a4, a5);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)g_CastleProductionPaletteBuffer);
  return UIWidget_ShowReleasedState(v6, v6);
}
// 43565E: variable 'v5' is possibly undefined
// 435675: variable 'v6' is possibly undefined
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];

//----- (00435680) --------------------------------------------------------
int  CastleProduction_SelectNextAvailableUnit(int widget, int a2, DWORD renderContext, int a4, int a5)
{
  int v5; // ecx
  int v6; // ecx

  UIWidget_ShowPressedState(widget);
  if ( g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex + 1] != -1 )
    ++g_CastleProductionSelectedAvailableUnitIndex;
  CastleProduction_RedrawSelectedUnitPanel(v5, a2, renderContext, a4, a5);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)g_CastleProductionPaletteBuffer);
  return UIWidget_ShowReleasedState(v6, v6);
}
// 43569E: variable 'v5' is possibly undefined
// 4356B5: variable 'v6' is possibly undefined
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532228: using guessed type int dword_532228[40];

//----- (004356C0) --------------------------------------------------------
int  CastleProduction_HandleBuyLicenceAction(int widget, DWORD gameContext, int actionContext)
{
  int v4; // ecx
  int v5; // ecx
  int i; // ecx
  int selectedUnitType; // esi
  int v9 CLASH95_UNUSED; // ecx
  int v10; // edx
  void *v11; // ecx
  int v12; // ecx
  int v13; // [esp-Ch] [ebp-10h]

  UIWidget_ShowPressedState(widget);
  if ( !Building_BuyUnitLicence(g_CastleProductionBuildingPtr, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v4, gameContext) )
    return UIWidget_ShowReleasedState(widget, v5);
  v13 = v5;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
  for ( i = 0; ; ++i )
  {
    selectedUnitType = g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
    if ( *(char *)(uintptr_t)(i + g_CastleProductionBuildingPtr + 402) == selectedUnitType )
      break;
  }
  g_LicenceGridAddAnimSlotIndex = i;
  Audio_PlaySoundEffectByName(aDopen, 64);
  CastleProduction_ReloadLicenceSlotSprite(i, widget);
  UI_DrawActionBox(actionContext);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, v10);
  CastleProduction_RebuildAvailableUnitList(v11);
  CastleProduction_RedrawSelectedUnitPanel(v12, widget, gameContext, actionContext, selectedUnitType);
  return UIWidget_ShowReleasedState(widget, v13);
}
// 4356DB: variable 'v4' is possibly undefined
// 4356E7: variable 'v5' is possibly undefined
// 435745: variable 'v9' is possibly undefined
// 435754: variable 'v10' is possibly undefined
// 435759: variable 'v11' is possibly undefined
// 43575E: variable 'v12' is possibly undefined
// 519808: using guessed type int dword_519808;
// 532218: using guessed type int dword_532218;
// 532220: using guessed type int dword_532220[];
// 532224: using guessed type unit_type dword_532224[41];
// 532334: using guessed type int dword_532334;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00435770) --------------------------------------------------------
int  CastleProduction_HandleRemoveLicenceAction(int widget)
{
  int v2; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  if ( g_ProductionGridSelectedIndex != -1 )
  {
    g_CastleLicenceRemovalSlotIndex = g_ProductionGridSelectedIndex;
    Audio_PlaySoundEffectByName(aDclose_0, 64);
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  }
  return UIWidget_ShowReleasedState(v2, v2);
}
// 435792: variable 'v2' is possibly undefined
// 519808: using guessed type int dword_519808;
// 5322C8: using guessed type int dword_5322C8;
// 532338: using guessed type int dword_532338;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004357E0) --------------------------------------------------------
int  CastleProduction_HandleProduceAction(int result, char productionSlot, DWORD gameContext)
{
  int v4; // ecx

  if ( g_ProductionGridSelectedIndex != -1 )
  {
    UIWidget_ShowPressedState(result);
    Render_Begin((int)(intptr_t)g_RenderState, 0);
    Building_SetUnitProduction(g_CastleProductionBuildingPtr, productionSlot, gameContext);
    CastleProduction_DrawLicenceGrid();
    CastleProduction_DrawProductionStatus(gameContext);
    return UIWidget_ShowReleasedState(v4, v4);
  }
  return result;
}
// 43581C: variable 'v4' is possibly undefined
// 532218: using guessed type int dword_532218;
// 5322C8: using guessed type int dword_5322C8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00435830) --------------------------------------------------------
int  CastleProduction_HandleStopProductionAction(int widget, char productionSlot, DWORD gameContext)
{
  int v3; // ecx
  int v4; // edx
  int v5; // ecx

  UIWidget_ShowPressedState(widget);
  Building_StopUnitProduction(v3, productionSlot, gameContext);
  CastleProduction_DrawLicenceGrid();
  CastleProduction_DrawProductionStatus(gameContext);
  return UIWidget_ShowReleasedState(v4, v5);
}
// 43583D: variable 'v3' is possibly undefined
// 43584E: variable 'v4' is possibly undefined
// 43584E: variable 'v5' is possibly undefined
// 532218: using guessed type int dword_532218;

//----- (00435860) --------------------------------------------------------
int  CastleProduction_HandleInfoAction(int widget, int a2, DWORD gameContext, char actionBoxArg)
{
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // esi
  int v8; // ecx
  char infoGraphicPath[108]; // [esp-70h] [ebp-74h] BYREF
  int v11 CLASH95_UNUSED; // [esp-4h] [ebp-8h]

  v11 = a2;
  UIWidget_PlayPressedReleaseAnimation(widget);
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Unit_BuildBigInfoGraphicPath(infoGraphicPath, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v5);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    infoGraphicPath,
    0,
    (uintptr_t)(unsigned int)g_CastleProductionPaletteBuffer);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_CastleProductionPaletteBuffer, 20);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) )
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)g_RenderState);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  if ( g_CastleProductionUseChrTheme )
    backgroundPath = aCastle_chrD_23;
  else
    backgroundPath = aCastle_pogD_23;
  renderSurface = *(_DWORD *)(uintptr_t)(g_PrimaryRenderSurface + 184);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    backgroundPath,
    0,
    (uintptr_t)(unsigned int)g_CastleProductionPaletteBuffer);
  Palette_QuantizeChannelsInPlace((_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, 6);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  RenderSurface_InvokeSlot36((_DWORD *)g_RenderDevice);
  CastleProduction_RedrawSelectedUnitPanel(v8, 20, gameContext, actionBoxArg, renderSurface);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(gameContext);
  UI_DrawActionBox(actionBoxArg);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_CastleProductionPaletteBuffer, 20);
  return Render_Present((int)(intptr_t)g_RenderState);
}
// 43589A: variable 'v5' is possibly undefined
// 435970: variable 'v8' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515130: using guessed type _DWORD dword_515130[3];
// 5202E0: using guessed type int dword_5202E0;
// 532214: using guessed type int dword_532214;
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532224: using guessed type unit_type dword_532224[41];
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004359B0) --------------------------------------------------------
BOOL __thiscall CastleProduction_RebuildAvailableUnitList(void *this)
{
  int out_index; // ebx
  unit_type unitType; // ecx
  BOOL result; // eax

  (void)this;
  memset(g_CastleProduction_AvailableUnitTypes, 0xFF, 0xA4);
  out_index = 0;
  unitType = UNIT_TYPE_PEASANT;
  do
  {
    result = Building_IsUnitLicenceEligible((char *)(uintptr_t)g_CastleProductionBuildingPtr, unitType);
    if ( result && g_UnitTypeRuntimeCoreMetadata[unitType].original_localized_name_table_va )
      g_CastleProduction_AvailableUnitTypes[out_index++] = unitType;
    ++unitType;
  }
  while ( unitType < UNIT_TYPE_METADATA_CAPACITY );
  return result;
}
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 532218: using guessed type int dword_532218;
// 532220: using guessed type int dword_532220[];

//----- (00435A00) --------------------------------------------------------
int  CastleProduction_HandleLicenceGridClick(DWORD gameContext, int renderDevice, int a3)
{
  int result; // eax
  int gridIndex; // ecx
  int v5; // ecx
  int availableUnitIndex; // edx
  int slotUnitType; // ecx

  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  if ( result )
  {
    result = UI_GetGridIndexFromMouse();
    gridIndex = result;
    if ( result != -1 )
    {
      result = *(char *)(uintptr_t)(result + g_CastleProductionBuildingPtr + 402);
      if ( result != -1 && gridIndex != g_ProductionGridSelectedIndex )
      {
        Audio_PlaySoundEffectByName(aMarker_0, 64);
        g_ProductionGridSelectedIndex = v5;
        availableUnitIndex = 0;
        slotUnitType = *(char *)(uintptr_t)(v5 + g_CastleProductionBuildingPtr + 402);
        result = 0;
        if ( g_CastleProduction_AvailableUnitTypes[0] != -1 )
        {
          do
          {
            if ( slotUnitType == g_CastleProduction_AvailableUnitTypes[availableUnitIndex] )
              break;
            a3 = g_CastleProductionAvailableUnitTypesLookahead[availableUnitIndex];
            result += sizeof(int);
            ++availableUnitIndex;
          }
          while ( a3 != -1 );
        }
        if ( slotUnitType == g_CastleProduction_AvailableUnitTypes[availableUnitIndex] && availableUnitIndex != g_CastleProductionSelectedAvailableUnitIndex )
        {
          g_CastleProductionSelectedAvailableUnitIndex = availableUnitIndex;
          CastleProduction_RedrawSelectedUnitPanel(slotUnitType, g_CastleProduction_AvailableUnitTypes[0], gameContext, renderDevice, a3);
          return Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)g_CastleProductionPaletteBuffer);
        }
      }
    }
  }
  return result;
}
// 435A57: variable 'v5' is possibly undefined
// 532218: using guessed type int dword_532218;
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532224: using guessed type unit_type dword_532224[41];
// 532228: using guessed type int dword_532228[];
// 5322C8: using guessed type int dword_5322C8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00435AC0) --------------------------------------------------------
int  CastleProduction_HandleAvailableUnitStripClick(DWORD gameContext, int renderDevice, int widgetTable)
{
  int stripRowOffset; // ebx
  int result; // eax
  int v5; // ecx

  stripRowOffset = ((g_MouseCursorRawY >> g_CursorCoordShift) - 35) / 17 - 2;
  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  if ( result )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= 40 )
    {
      result = (unsigned __int16)DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x14u) + 40;
      if ( g_MouseCursorRawX >> g_CursorCoordShift <= result
        && stripRowOffset >= -2
        && stripRowOffset <= 2
        && stripRowOffset + g_CastleProductionSelectedAvailableUnitIndex >= 0
        && g_CastleProduction_AvailableUnitTypes[stripRowOffset + g_CastleProductionSelectedAvailableUnitIndex] != -1 )
      {
        g_CastleProductionSelectedAvailableUnitIndex += stripRowOffset;
        Render_Pump();
        CastleProduction_RedrawSelectedUnitPanel(v5, stripRowOffset, gameContext, renderDevice, widgetTable);
        Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)g_CastleProductionPaletteBuffer);
        Render_Present((int)(intptr_t)g_RenderState);
        return Render_Begin((int)(intptr_t)g_RenderState, 0);
      }
    }
  }
  return result;
}
// 435B61: variable 'v5' is possibly undefined
// 53220C: using guessed type int dword_53220C;
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532224: using guessed type unit_type dword_532224[41];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00435B90) --------------------------------------------------------
int  CastleProduction_TickAnimations(DWORD gameContext)
{
  int previousResourceHandle; // edx
  void *v2; // ecx
  int v3; // ecx

  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  CastleProduction_AnimateSelectedUnitPortrait(v2);
  CastleProduction_TickLicenceGridAnimations(v3, gameContext);
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
}
// 435B9F: variable 'v2' is possibly undefined
// 435BA4: variable 'v3' is possibly undefined

//----- (00435BC0) --------------------------------------------------------
int  Castle_ShowUnitProductionPanel(int buildingPtr, DWORD renderContext, int actionBoxArg)
{
  unsigned int v3 CLASH95_UNUSED; // eax
  int v4 CLASH95_UNUSED; // ecx
  int v5; // ecx
  int paletteBuffer; // eax
  int v7; // ecx
  DWORD useChrTheme; // ebp
  char *panelBackgroundPath; // edx
  int renderSurface; // esi
  char v11; // bl
  int v12; // ecx
  _DWORD *dlxSpriteSet; // eax
  CHAR *panelPalettePath; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int (*previousAnimationHook)(void); // ecx
  int slotIndex; // edx
  int v25 CLASH95_UNUSED; // ecx

  g_CastleProductionBuildingPtr = buildingPtr;
  g_CastleProductionUseChrTheme = *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(buildingPtr + 2) + 140063);
  g_CastleProductionSelectedAvailableUnitIndex = 0;
  g_CastleProductionSelectedUnitSpriteSet = 0;
  memset(g_CastleProduction_LicenceSlotSpriteHandles, 0, sizeof(g_CastleProduction_LicenceSlotSpriteHandles));
  for ( slotIndex = 0; slotIndex != 12; ++slotIndex )
    g_CastleProductionSlotAnimFrames[slotIndex] = Rng_RandRange(0, 7);
  g_CastleLicenceRemovalSlotIndex = -1;
  g_LicenceGridAddAnimSlotIndex = -1;
  g_ProductionGridSelectedIndex = -1;
  CastleProduction_RebuildAvailableUnitList(0);
  paletteBuffer = Mem_Alloc(1024, v5, -1, renderContext);
  if ( paletteBuffer )
    paletteBuffer = _wcpp_4_ctor_array__(v7, 256);
  useChrTheme = g_CastleProductionUseChrTheme;
  g_CastleProductionPaletteBuffer = paletteBuffer;
  if ( g_CastleProductionUseChrTheme )
    panelBackgroundPath = aCastle_chrD_17;
  else
    panelBackgroundPath = aCastle_pogD_17;
  renderSurface = *(_DWORD *)(uintptr_t)(g_PrimaryRenderSurface + 184);
  v11 = g_CastleProductionPaletteBuffer;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    panelBackgroundPath,
    0,
    (uintptr_t)(unsigned int)g_CastleProductionPaletteBuffer);
  Palette_QuantizeChannelsInPlace((_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, 6);
  dlxSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v12, v11, useChrTheme);
  if ( dlxSpriteSet )
    dlxSpriteSet = DLXSpriteSet_Load(dlxSpriteSet, g_CastleProductionUseChrTheme ? aCastle_chrD_19 : aCastle_pogD_19);
  g_BuildingUiDlxSpriteSet = (int)(intptr_t)dlxSpriteSet;
  if ( g_CastleProductionUseChrTheme )
    panelPalettePath = aCastle_chrD_19;
  else
    panelPalettePath = aCastle_pogD_19;
  Palette_LoadOrBuildBlendLookupTable(panelPalettePath, g_CastleProductionPaletteBuffer, g_CastleProductionUseChrTheme, useChrTheme);
  Render_LoadResourceSprite_v4(5, (_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, v15, v11, useChrTheme);
  Render_LoadResourceSprite_v4(20, (_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, v16, v11, useChrTheme);
  Render_LoadResourceSprite_v4(9, (_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, v17, v11, useChrTheme);
  Render_LoadResourceSprite_v4(7, (_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, v18, v11, useChrTheme);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)(uintptr_t)g_CastleProductionPaletteBuffer, v19, v11, useChrTheme);
  UI_SetActiveWidgetTable(8);
  RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, g_CastleProductionPaletteBuffer, v20, useChrTheme);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, v21);
  RenderSurface_InvokeSlot36((_DWORD *)g_RenderDevice);
  CastleProduction_RedrawSelectedUnitPanel(v22, 20, useChrTheme, actionBoxArg, renderSurface);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(useChrTheme);
  UI_DrawActionBox(actionBoxArg);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_CastleProductionPaletteBuffer, 20);
  Render_Present((int)(intptr_t)g_RenderState);
  g_CastleProductionExitSignal = 0;
  g_ActiveDialogAnimationTickHook = (int (*)(void))CastleProduction_TickAnimations;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    CastleProduction_TickAnimations(useChrTheme);
    UI_RunHoverTooltipZones(g_CastleUnitProductionTooltipZone);
    g_RenderDevice = &g_MainRenderDevice;
    if ( !UIWidgetTable_PollHoverAndActions(g_CastleUnitProductionWidgetTable, useChrTheme) )
    {
      CastleProduction_HandleLicenceGridClick(useChrTheme, (int)(intptr_t)&g_MainRenderDevice, (int)(intptr_t)g_CastleUnitProductionWidgetTable);
      CastleProduction_HandleAvailableUnitStripClick(useChrTheme, (int)(intptr_t)&g_MainRenderDevice, (int)(intptr_t)g_CastleUnitProductionWidgetTable);
    }
  }
  while ( !g_CastleProductionExitSignal );
  g_ActiveDialogAnimationTickHook = previousAnimationHook;
  DLXSpriteSet_ReleaseAndClear(&g_BuildingUiDlxSpriteSet);
  if ( g_CastleProductionSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_CastleProductionSelectedUnitSpriteSet);
  for ( slotIndex = 0; slotIndex != 12; ++slotIndex )
  {
    if ( g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] )
    {
      nfree_(g_CastleProduction_LicenceSlotSpriteHandles[slotIndex]);
      g_CastleProduction_LicenceSlotSpriteHandles[slotIndex] = 0;
    }
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  return nfree_(g_CastleProductionPaletteBuffer);
}
// 435C1C: variable 'v4' is possibly undefined
// 435C48: variable 'v5' is possibly undefined
// 435E82: variable 'v7' is possibly undefined
// 435C97: variable 'v12' is possibly undefined
// 435CEA: variable 'v15' is possibly undefined
// 435CFA: variable 'v16' is possibly undefined
// 435D0A: variable 'v17' is possibly undefined
// 435D1A: variable 'v18' is possibly undefined
// 435D2A: variable 'v19' is possibly undefined
// 435D44: variable 'v20' is possibly undefined
// 435D67: variable 'v21' is possibly undefined
// 435D7F: variable 'v22' is possibly undefined
// 435E0F: variable 'v23' is possibly undefined
// 435E38: variable 'v25' is possibly undefined
// 435E41: variable 'v24' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515130: using guessed type _DWORD dword_515130[3];
// 515310: using guessed type __int16 word_515310[4];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526A2C: using guessed type int dword_526A2C;
// 526A30: using guessed type int (*dword_526A30)(void);
// 53220C: using guessed type int dword_53220C;
// 532210: using guessed type int g_CastleProductionExitSignal;
// 532214: using guessed type int dword_532214;
// 532218: using guessed type int dword_532218;
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 5322C8: using guessed type int dword_5322C8;
// 5322D0: using guessed type int dword_5322D0[];
// 532304: using guessed type int dword_532304[12];
// 532334: using guessed type int dword_532334;
// 532338: using guessed type int dword_532338;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00435ED0) --------------------------------------------------------
int  Palette_LoadOrBuildBlendLookupTable(CHAR *themeName, int palettePtr, int a3, DWORD fileContext)
{
  unsigned int cube_size;
  int query_handle;
  int output_handle;
  CHAR path[256];

  (void)a3;
  strcpy(path, aGfx_5);
  strcat(path, themeName);
  strcat(path, a_mtb);
  query_handle = FileSystem_ResolveReadPath(path, 0);
  if ( query_handle )
  {
    cube_size = 1u << g_Palette_ColorCubeBits;
    cube_size *= cube_size * cube_size;
    g_Palette_ActivePalettePtr = palettePtr;
    Compat_QueryRead(query_handle, g_Rgb15ToPaletteLut, (int)cube_size);
    return Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
  }

  Palette_BuildNearestColorLUT(palettePtr);
  output_handle = IO_FOpen(path, (unsigned __int8 *)aWb_0, 0, fileContext);
  cube_size = 1u << g_Palette_ColorCubeBits;
  cube_size *= cube_size * cube_size;
  fwrite_(g_Rgb15ToPaletteLut, (int)cube_size, output_handle, 1);
  return fclose_(output_handle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 519A10: using guessed type int dword_519A10;
// 519A18: using guessed type char byte_519A18;

//----- (00435FE0) --------------------------------------------------------
int  BuildingTransferDialog_DrawSourceRemainingValue(DWORD renderContext, int drawContext)
{
  void *savedRenderDevice; // esi
  int v3; // edx
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderContext);
  Render_SaveBackbuffer(v3);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 48, 400, 0x1BBu, 0x3Cu, 0x190u, 0x30u);
  result = UI_DrawTextFmt(drawContext, 347, 445, 48, 3, (int)(intptr_t)aD_39);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 436001: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532354: using guessed type int dword_532354;

//----- (00436060) --------------------------------------------------------
int  BuildingTransferDialog_DrawTransferAmountValue(DWORD renderContext, int drawContext)
{
  void *savedRenderDevice; // esi
  int v3; // edx
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderContext);
  Render_SaveBackbuffer(v3);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x12Cu, 0x224u, 0x110u);
  result = UI_DrawTextFmt(drawContext, 548, 601, 272, 3, (int)(intptr_t)aD_40);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 436081: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532350: using guessed type int dword_532350;

//----- (004360E0) --------------------------------------------------------
int  BuildingTransferDialog_HandleExitButtonPress(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_BuildingTransferDialogExitScratch = v4;
  return result;
}
// 4360EB: variable 'v4' is possibly undefined
// 53234C: using guessed type int dword_53234C;

//----- (00436100) --------------------------------------------------------
int  BuildingTransferDialog_CommitTransfer(int widget, int delayTicks, DWORD renderContext, double a4)
{
  int result; // eax
  int targetBuildingId; // esi

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  if ( g_Building_TransferAmount )
  {
    targetBuildingId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( targetBuildingId == -2 )
      targetBuildingId = -1;
    Building_Transfer((g_BuildingTransferSourcePtr - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE, targetBuildingId, 1, g_Building_TransferAmount, a4);
    g_Building_TransferAmount = 0;
    BuildingTransferDialog_DrawTransferAmountValue(renderContext, 467);
    return BuildingTransferDialog_DrawSourceRemainingValue(renderContext, 467);
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 532350: using guessed type int dword_532350;
// 532354: using guessed type int dword_532354;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];
