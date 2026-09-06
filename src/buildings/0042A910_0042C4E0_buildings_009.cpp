/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "0042A910_0042C4E0_buildings_009_local.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL void BuildingEconomyDialog_InitWidget (unsigned char *record, int left, int top, int normal_sprite, int hover_sprite, int (*transition_callback) (short unsigned int *, int, DWORD), void *action_callback, const char *text_pl, const char *text_en, const char *text_de, unsigned char tooltip_mode, const char *sound);
CLASH95_LOCAL void BuildingEconomyDialog_EnsureWidgets (void);

//----- (0042A910) --------------------------------------------------------
int  UI_DrawConfirmBottom(DWORD renderState, int a2 CLASH95_UNUSED)
{
  void *savedRenderDevice; // esi
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_ReleaseSurface(5, renderState);
  Render_SaveBackbuffer((int)(intptr_t)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x124u, 0x224u, 0x110u);
  result = UI_DrawTextFmt(548, 548, 601, 272, 3, aD_9, g_BuildingEconomyDialogPendingGoldTransfer);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;

CLASH95_LOCAL void BuildingEconomyDialog_InitWidget(
        unsigned char *record,
        int left,
        int top,
        int normal_sprite,
        int hover_sprite,
        int (*transition_callback)(unsigned __int16 *, int, DWORD),
        void *action_callback,
        const char *text_pl,
        const char *text_en,
        const char *text_de,
        unsigned char tooltip_mode,
        const char *sound)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_BuildingEconomyDialogSpriteSet;
  *(_DWORD *)(record + 16) = normal_sprite;
  *(_DWORD *)(record + 20) = hover_sprite;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)transition_callback;
  *(_DWORD *)(record + 32) = (int)(uintptr_t)action_callback;
  *(_DWORD *)(record + 36) = (int)(uintptr_t)text_pl;
  *(_DWORD *)(record + 40) = (int)(uintptr_t)text_en;
  *(_DWORD *)(record + 44) = (int)(uintptr_t)text_de;
  *(_BYTE *)(record + 48) = tooltip_mode;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound;
}

CLASH95_LOCAL void BuildingEconomyDialog_EnsureWidgets(void)
{
  static const char sound_cash[] CLASH95_LOCAL_DATA_SYMBOL("sound_cash.8", "BuildingEconomyDialog_EnsureWidgets.sound_cash") = "kasa";
  static const char sound_small[] CLASH95_LOCAL_DATA_SYMBOL("sound_small.7", "BuildingEconomyDialog_EnsureWidgets.sound_small") = "male";
  static const char sound_large[] CLASH95_LOCAL_DATA_SYMBOL("sound_large.3", "BuildingEconomyDialog_EnsureWidgets.sound_large") = "duze";
  static const char text_back_pl[] CLASH95_LOCAL_DATA_SYMBOL("text_back_pl.6", "BuildingEconomyDialog_EnsureWidgets.text_back_pl") = "Koniec";
  static const char text_back_en[] CLASH95_LOCAL_DATA_SYMBOL("text_back_en.5", "BuildingEconomyDialog_EnsureWidgets.text_back_en") = "Back";
  static const char text_back_de[] CLASH95_LOCAL_DATA_SYMBOL("text_back_de.4", "BuildingEconomyDialog_EnsureWidgets.text_back_de") = "Zuruck";
  static const char text_transfer_pl[] CLASH95_LOCAL_DATA_SYMBOL("text_transfer_pl.2", "BuildingEconomyDialog_EnsureWidgets.text_transfer_pl") = "Transferuj";
  static const char text_transfer_en[] CLASH95_LOCAL_DATA_SYMBOL("text_transfer_en.1", "BuildingEconomyDialog_EnsureWidgets.text_transfer_en") = "Transfer";
  static const char text_transfer_de[] CLASH95_LOCAL_DATA_SYMBOL("text_transfer_de.0", "BuildingEconomyDialog_EnsureWidgets.text_transfer_de") = "Uberfuhrung";

  if ( g_BuildingEconomyDialogWidgetsInitialized )
    return;

  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    174,
    173,
    6,
    7,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingEconomyDialog_IncreaseTaxRate),
    NULL,
    NULL,
    NULL,
    0,
    sound_cash);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    174,
    206,
    8,
    9,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingEconomyDialog_DecreaseTaxRate),
    NULL,
    NULL,
    NULL,
    0,
    sound_cash);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2,
    459,
    270,
    10,
    11,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferTargetList_SelectPrevious),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3,
    459,
    323,
    12,
    13,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferTargetList_SelectNext),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 4,
    513,
    331,
    18,
    19,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferDialog_IncreasePeasantTransferAmount),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 5,
    513,
    365,
    20,
    21,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferDialog_DecreasePeasantTransferAmount),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 6,
    513,
    247,
    14,
    15,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferDialog_IncreaseGoldTransferAmount),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 7,
    513,
    281,
    16,
    17,
    UI_DrawWidgetIconTransitionFast,
    (void*)(BuildingTransferDialog_DecreaseGoldTransferAmount),
    NULL,
    NULL,
    NULL,
    0,
    sound_small);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 8,
    42,
    426,
    22,
    23,
    UI_DrawWidgetIconTransitionSlow,
    (void*)(BuildingEconomyDialog_SetExitSignal),
    text_back_pl,
    text_back_en,
    text_back_de,
    2,
    sound_large);
  BuildingEconomyDialog_InitWidget(
    g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 9,
    505,
    426,
    24,
    25,
    UI_DrawWidgetIconTransitionSlow,
    (void*)(BuildingEconomyDialog_CommitTransfers),
    text_transfer_pl,
    text_transfer_en,
    text_transfer_de,
    2,
    sound_large);
  *(_DWORD *)(g_BuildingEconomyDialogActionWidgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_ECONOMY_DIALOG_WIDGET_COUNT) = -1;
  g_BuildingEconomyDialogWidgetsInitialized = 1;
}

//----- (0042A990) --------------------------------------------------------
int  BuildingEconomyDialog_SetExitSignal(int widget, int a2 CLASH95_UNUSED)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay((uintptr_t)widget, 1);
  g_BuildingEconomyDialogExitSignal = 1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[economy] back exit_signal=%d\n", g_BuildingEconomyDialogExitSignal);
  return result;
}
// 531CE8: using guessed type int g_BuildingEconomyDialogExitSignal;

//----- (0042A9B0) --------------------------------------------------------
int  BuildingEconomyDialog_CommitTransfers(
        int widget,
        int a2,
        DWORD renderState,
        char a4,
        double a5)
{
  int targetBuildingId; // eax
  int peasantTargetId; // esi
  int goldTargetId; // esi

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  if ( g_BuildingEconomyDialogPendingPeasantTransfer )
  {
    targetBuildingId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( targetBuildingId == -2 || *(_BYTE *)(uintptr_t)(BUILDING_RECORD_SIZE * targetBuildingId + gameData + 509678) != 1 )
    {
      peasantTargetId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
      if ( peasantTargetId == -2 )
        peasantTargetId = -1;
      a4 = -45;
      Building_Transfer(
        (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
        peasantTargetId,
        0,
        g_BuildingEconomyDialogPendingPeasantTransfer,
        a5);
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    }
  }
  if ( g_BuildingEconomyDialogPendingGoldTransfer )
  {
    goldTargetId = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( goldTargetId == -2 )
      goldTargetId = -1;
    a4 = -45;
    Building_Transfer(
      (g_BuildingEconomyDialogBuilding - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE,
      goldTargetId,
      1,
      g_BuildingEconomyDialogPendingGoldTransfer,
      a5);
    g_BuildingEconomyDialogPendingGoldTransfer = 0;
  }
  UI_DrawConfirmTop(renderState, a4);
  UI_DrawConfirmBottom(renderState, a4);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 20, 200, 0x17Cu, 0x41u, 0xC8u, 0x14u);
  Render_ReleaseSurface(16, renderState);
  UI_DrawTextFmt((int)(intptr_t)&g_MainRenderDevice, 0, 370, 20, 2, (const char*)(intptr_t)((int)(intptr_t)aD_47));
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 30, 545, 0x25Au, 0x32u, 0x221u, 0x1Eu);
  Render_ReleaseSurface(5, renderState);
  return UI_DrawTextFmt((int)(intptr_t)&g_MainRenderDevice, 545, 602, 30, 3, (const char*)(intptr_t)((int)(intptr_t)aD_46));
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];

//----- (0042AB80) --------------------------------------------------------
int  BuildingEconomyDialog_DecreaseTaxRate(int widget, char startTaxRate)
{
  int v4; // edx
  int v5; // ecx
  int buildingRecord; // eax
  char taxByte; // dl
  int currentTaxRate; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int timeNow; // eax
  int v14; // edx
  int v15; // ecx
  unsigned int taxDecrement; // eax
  char newTaxRate; // dl
  int buildingRecord2; // eax
  char taxHighBits; // dh
  int v20; // ecx
  char taxHighBits0; // dh

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, startTaxRate);
  Time_Now(v5, v4);
  buildingRecord = g_BuildingEconomyDialogBuilding;
  taxByte = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436);
  if ( (taxByte & 0x3F) != 0 )
  {
    taxHighBits0 = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits0;
    *(_BYTE *)(uintptr_t)(buildingRecord + 436) = ((taxByte & 0x3F) - 1) & 0x3F | taxHighBits0;
  }
  currentTaxRate = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, currentTaxRate);
    v11 = Time_Now(v10, v9);
    timeNow = Time_Now(v12, v11);
    taxDecrement = (v14 - v15) * (timeNow - v15) / 0x15Eu;
    newTaxRate = currentTaxRate - taxDecrement;
    if ( (int)(currentTaxRate - taxDecrement) < 0 )
      newTaxRate = 0;
    buildingRecord2 = g_BuildingEconomyDialogBuilding;
    taxHighBits = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits;
    *(_BYTE *)(uintptr_t)(buildingRecord2 + 436) = newTaxRate & 0x3F | taxHighBits;
    UI_DrawNoticeBoxSmall((DWORD)(intptr_t)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v20);
}
// 42ABA6: variable 'v5' is possibly undefined
// 42ABA6: variable 'v4' is possibly undefined
// 42ABE2: variable 'v10' is possibly undefined
// 42ABE2: variable 'v9' is possibly undefined
// 42ABE9: variable 'v12' is possibly undefined
// 42ABEE: variable 'v14' is possibly undefined
// 42ABEE: variable 'v15' is possibly undefined
// 42AC46: variable 'v20' is possibly undefined
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AC80) --------------------------------------------------------
int  BuildingEconomyDialog_IncreaseTaxRate(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int buildingRecord; // eax
  char newTaxRate; // dl
  char taxHighBits; // dh
  int currentTaxRate; // ebx
  int v10; // edx
  int v11; // ecx
  int timeNow; // eax
  int v13; // ecx
  int currentTime; // eax
  int v15; // edx
  int v16; // ecx
  int taxRateAnim; // edx
  int buildingRecord2; // eax
  int v19; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  Time_Now(v5, v4);
  buildingRecord = g_BuildingEconomyDialogBuilding;
  newTaxRate = ((*(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0x3F) + 1) & 0x3F;
  taxHighBits = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
  *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) = taxHighBits;
  *(_BYTE *)(uintptr_t)(buildingRecord + 436) = newTaxRate | taxHighBits;
  currentTaxRate = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, currentTaxRate);
    timeNow = Time_Now(v11, v10);
    currentTime = Time_Now(v13, timeNow);
    taxRateAnim = currentTaxRate + (v15 - v16) * (currentTime - v16) / 0x15Eu;
    if ( taxRateAnim > 40 )
      LOBYTE(taxRateAnim) = 40;
    buildingRecord2 = g_BuildingEconomyDialogBuilding;
    BYTE1(taxRateAnim) = *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) & 0xC0;
    *(_BYTE *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 436) = BYTE1(taxRateAnim);
    *(_BYTE *)(uintptr_t)(buildingRecord2 + 436) = taxRateAnim & 0x3F | BYTE1(taxRateAnim);
    UI_DrawNoticeBoxSmall(0x15Eu, (int)(intptr_t)g_RenderState);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v19);
}
// 42ACA3: variable 'v5' is possibly undefined
// 42ACA3: variable 'v4' is possibly undefined
// 42ACFA: variable 'v11' is possibly undefined
// 42ACFA: variable 'v10' is possibly undefined
// 42AD01: variable 'v13' is possibly undefined
// 42AD06: variable 'v15' is possibly undefined
// 42AD06: variable 'v16' is possibly undefined
// 42AD59: variable 'v19' is possibly undefined
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AD70) --------------------------------------------------------
int  BuildingTransferDialog_DecreasePeasantTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int peasantAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int currentTime; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer -= 10;
  peasantAmount = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, peasantAmount);
    v9 = Time_Now(v8, v7);
    currentTime = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((peasantAmount - (v12 - v13) * (currentTime - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer < 0 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 0;
    UI_DrawConfirmTop((DWORD)(intptr_t)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v14);
}
// 42AD96: variable 'v5' is possibly undefined
// 42AD96: variable 'v4' is possibly undefined
// 42ADBE: variable 'v8' is possibly undefined
// 42ADBE: variable 'v7' is possibly undefined
// 42ADC5: variable 'v10' is possibly undefined
// 42ADCA: variable 'v12' is possibly undefined
// 42ADCA: variable 'v13' is possibly undefined
// 42AE1D: variable 'v14' is possibly undefined
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AE30) --------------------------------------------------------
int  BuildingTransferDialog_IncreasePeasantTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int peasantAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int timeNow; // eax
  int v12; // edx
  int v13; // ecx
  unsigned __int16 maxPeasants; // ax
  int v15; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingPeasantTransfer += 10;
  peasantAmount = g_BuildingEconomyDialogPendingPeasantTransfer;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, peasantAmount);
    v9 = Time_Now(v8, v7);
    timeNow = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingPeasantTransfer = 10 * ((peasantAmount + (v12 - v13) * (timeNow - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingPeasantTransfer > 1000 )
      g_BuildingEconomyDialogPendingPeasantTransfer = 1000;
    maxPeasants = *(_WORD *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 430);
    HIBYTE(maxPeasants) &= 0xFu;
    if ( maxPeasants < g_BuildingEconomyDialogPendingPeasantTransfer )
      g_BuildingEconomyDialogPendingPeasantTransfer = maxPeasants;
    UI_DrawConfirmTop(0xAu, (int)(intptr_t)g_RenderState);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v15);
}
// 42AE53: variable 'v5' is possibly undefined
// 42AE53: variable 'v4' is possibly undefined
// 42AE79: variable 'v8' is possibly undefined
// 42AE79: variable 'v7' is possibly undefined
// 42AE80: variable 'v10' is possibly undefined
// 42AE85: variable 'v12' is possibly undefined
// 42AE85: variable 'v13' is possibly undefined
// 42AEEE: variable 'v15' is possibly undefined
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AF10) --------------------------------------------------------
int  BuildingTransferDialog_DecreaseGoldTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int goldAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer -= 10;
  goldAmount = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, goldAmount);
    v9 = Time_Now(v8, v7);
    v11 = Time_Now(v10, v9);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((goldAmount - (v12 - v13) * (v11 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer < 0 )
      g_BuildingEconomyDialogPendingGoldTransfer = 0;
    UI_DrawConfirmBottom((DWORD)(intptr_t)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v14);
}
// 42AF36: variable 'v5' is possibly undefined
// 42AF36: variable 'v4' is possibly undefined
// 42AF5E: variable 'v8' is possibly undefined
// 42AF5E: variable 'v7' is possibly undefined
// 42AF65: variable 'v10' is possibly undefined
// 42AF6A: variable 'v12' is possibly undefined
// 42AF6A: variable 'v13' is possibly undefined
// 42AFBD: variable 'v14' is possibly undefined
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042AFD0) --------------------------------------------------------
int  BuildingTransferDialog_IncreaseGoldTransferAmount(int widget, char a2)
{
  int v4; // edx
  int v5; // ecx
  int goldAmount; // ebx
  int v7; // edx
  int v8; // ecx
  int timeSample; // eax
  int v10; // ecx
  int timeSample2; // eax
  int v12; // edx
  int v13; // ecx
  DWORD maxGold; // ebp
  int v15; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  Time_Now(v5, v4);
  g_BuildingEconomyDialogPendingGoldTransfer += 10;
  goldAmount = g_BuildingEconomyDialogPendingGoldTransfer;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, goldAmount);
    timeSample = Time_Now(v8, v7);
    timeSample2 = Time_Now(v10, timeSample);
    g_BuildingEconomyDialogPendingGoldTransfer = 10 * ((goldAmount + (v12 - v13) * (timeSample2 - v13) / 0x32u) / 0xA);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > 1000 )
      g_BuildingEconomyDialogPendingGoldTransfer = 1000;
    maxGold = *(_DWORD *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 438);
    if ( g_BuildingEconomyDialogPendingGoldTransfer > maxGold )
      g_BuildingEconomyDialogPendingGoldTransfer = *(_DWORD *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 438);
    UI_DrawConfirmBottom(maxGold, (int)(intptr_t)g_RenderState);
  }
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) );
  Render_Present((int)(intptr_t)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v15);
}
// 42AFF3: variable 'v5' is possibly undefined
// 42AFF3: variable 'v4' is possibly undefined
// 42B019: variable 'v8' is possibly undefined
// 42B019: variable 'v7' is possibly undefined
// 42B020: variable 'v10' is possibly undefined
// 42B025: variable 'v12' is possibly undefined
// 42B025: variable 'v13' is possibly undefined
// 42B086: variable 'v15' is possibly undefined
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042B0A0) --------------------------------------------------------
int  BuildingEconomyDialog_Run(int buildingRecord)
{
  int player_has_religion; // edi
  int building_index;
  char *background_path; // edx
  char *sprite_path; // edx
  char *resource_base_path; // eax
  _DWORD *dialog_sprite_set; // eax
  int SpriteForChar; // eax
  int exit_signal_snapshot; // ecx
  unsigned __int8 *palette_buffer; // [esp+0h] [ebp-418h]

  g_BuildingEconomyDialogBuilding = buildingRecord;
  building_index = (buildingRecord - (gameData + BUILDING_TABLE_OFFSET)) / BUILDING_RECORD_SIZE;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] enter building_idx=%d owner=%d\n",
      building_index,
      *(unsigned __int8 *)(uintptr_t)(buildingRecord + 2));
  Diagnostics_ResetFrameDumpOnEconomyEnter();
  player_has_religion = PLAYER_RELIGION_FLAG(*(unsigned __int8 *)(uintptr_t)(buildingRecord + 2));
  BuildingTransferTargetList_Rebuild(buildingRecord, 1);
  g_BuildingEconomyDialogPendingPeasantTransfer = 0;
  g_BuildingEconomyDialogPendingGoldTransfer = 0;
  palette_buffer = g_CastleScreenPaletteBuffer;
  memset(palette_buffer, 0, 0x400u);
  if ( player_has_religion )
    background_path = aCastle_chrDw_1;
  else
    background_path = aCastle_pogDw_1;
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    background_path,
    0,
    (uintptr_t)palette_buffer);
  dialog_sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( player_has_religion )
    sprite_path = aCastle_chrDw_0;
  else
    sprite_path = aCastle_pogDw_0;
  if ( dialog_sprite_set )
    dialog_sprite_set = DLXSpriteSet_Load(dialog_sprite_set, sprite_path);
  g_BuildingEconomyDialogSpriteSet = (int)(intptr_t)dialog_sprite_set;
  if ( player_has_religion )
    resource_base_path = aCastle_chrDw_2;
  else
    resource_base_path = aCastle_pogDw_2;
  Palette_LoadOrBuildBlendLookupTable(resource_base_path, (int)(uintptr_t)palette_buffer, (int)(intptr_t)dialog_sprite_set, 0);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingEconomyDialogSpriteSet, (unsigned __int8)g_LanguageIndex);
  Compat_RenderDeviceDrawMenuSprite(267, 149, SpriteForChar, 0);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_ReleaseSurface(5, 0);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, palette_buffer, 0, (char)(intptr_t)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(5, palette_buffer, 0, (char)(intptr_t)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(9, palette_buffer, 0, (char)(intptr_t)&g_MainRenderDevice, 0);
  Render_LoadResourceSprite_v4(16, palette_buffer, 0, (char)(intptr_t)&g_MainRenderDevice, 0);
  UI_DrawTextFmt(267, 267, 343, 90, 2, aD_32, *(signed char *)(uintptr_t)(buildingRecord + 434));
  UI_DrawTextFmt(444, 444, 503, 198, 3, aD_33, *(unsigned __int16 *)(uintptr_t)(buildingRecord + 442));
  UI_DrawNoticeBoxSmall(0, 0);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 20, 200, 0x17Cu, 0x41u, 0xC8u, 0x14u);
  Render_ReleaseSurface(16, 0);
  UI_DrawTextFmt(0, 0, 370, 20, 2, aD_47, *(unsigned __int16 *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 430));
  BuildingEconomyDialog_EnsureWidgets();
  UIWidgetTable_InitDrawStates((_DWORD*)(g_BuildingEconomyDialogActionWidgets));
  BuildingTransferTargetList_SetDrawOrigin(184, 279);
  BuildingTransferTargetList_Draw((int)(uintptr_t)palette_buffer, 0);
  UI_DrawConfirmTop(0, 0);
  UI_DrawConfirmBottom(0, 0);
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 30, 545, 0x25Au, 0x32u, 0x221u, 0x1Eu);
  Render_ReleaseSurface(5, 0);
  UI_DrawTextFmt(545, 545, 602, 30, 3, aD_46, *(_DWORD *)(uintptr_t)(g_BuildingEconomyDialogBuilding + 438));
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, palette_buffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(uintptr_t)palette_buffer, 0, 0);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] first_present building_idx=%d list_index=%d target=%d\n",
      building_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  g_BuildingEconomyDialogExitSignal = 0;
  exit_signal_snapshot = 0;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)g_RenderState);
    BuildingTransferTargetList_HandleClick(0);
    UIWidgetTable_PollHoverAndActions((_DWORD*)(g_BuildingEconomyDialogActionWidgets), 0);
    UI_RunHoverTooltipZones(g_BuildingEconomyDialogTooltipZoneRect);
  }
  while ( exit_signal_snapshot == g_BuildingEconomyDialogExitSignal );
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] exit building_idx=%d list_index=%d exit_signal=%d\n",
      building_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingEconomyDialogExitSignal);
  BuildingTransferTargetList_FreeSpriteSet();
  DLXSpriteSet_ReleaseAndClear(&g_BuildingEconomyDialogSpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514840: using guessed type _DWORD dword_514840[3];
// 514A88: using guessed type __int16 word_514A88[4];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526A2C: using guessed type int dword_526A2C;
// 531CE4: using guessed type int g_BuildingEconomyDialogSpriteSet;
// 531CE8: using guessed type int g_BuildingEconomyDialogExitSignal;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
// 531CF0: using guessed type int g_BuildingEconomyDialogPendingGoldTransfer;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042B3F0) --------------------------------------------------------
BOOL  Trap_CanPlaceAtTile(int tileX, int tileY)
{
  int v3; // ecx
  BOOL result; // eax
  signed int surfaceClass; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  result = 0;
  if ( !Trap_GetTileOwnerMask(tileX, tileY, g_CurrentPlayerIndex) )
  {
    surfaceClass = Map_GetTileSurfaceClassOrUnexplored(v3, tileY);
    if ( surfaceClass != 185
      && surfaceClass != 39
      && surfaceClass != 204
      && surfaceClass != 202
      && surfaceClass != 147
      && surfaceClass != 1
      && !MapTile_IsCastleFoundationTile(v6, tileY, 2)
      && *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(v7, tileY)) == 0xFFFF
      && !MapTile_GetReligiousSiteCategory(v7, tileY)
      && !MapTile_HasHiddenTreasure(v8, tileY) )
    {
      return 1;
    }
  }
  return result;
}
// 42B410: variable 'v3' is possibly undefined
// 42B444: variable 'v6' is possibly undefined
// 42B467: variable 'v7' is possibly undefined
// 42B499: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0042B4B0) --------------------------------------------------------
signed int  Trap_New(DWORD tileX, int tileY, int a3, int stackIndex, double a5)
{
  signed int result; // eax
  int v9; // ecx
  int dxTile; // eax
  int dyTile; // eax
  int stackByteOffset; // ebx
  DWORD tileDataPtr; // ebp
  signed int squadCount; // eax
  _WORD *squadSlot; // edx
  signed int squadIndex; // ecx
  double v17; // st7
  int v18; // ecx
  int v19; // edx

  Debug_Log(a3, stackIndex, tileX, (int)(intptr_t)aTrap_newDDD, tileX);
  result = UnitStack_HasBuilder(stackIndex);
  if ( result )
  {
    if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET) < 0 || !Trap_CanPlaceAtTile(tileX, tileY) )
      return 0;
    dxTile = tileX - *(__int16 *)(uintptr_t)(v9 + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( dxTile <= 0 )
      dxTile = *(__int16 *)(uintptr_t)(v9 + gameData + UNIT_STACK_TABLE_OFFSET) - tileX;
    if ( dxTile > 1 )
      return 0;
    dyTile = tileY - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176);
    if ( dyTile <= 0 )
      dyTile = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147176) - tileY;
    if ( dyTile <= 1 )
    {
      stackByteOffset = UNIT_STACK_STRIDE * stackIndex;
      tileDataPtr = gameData + 100 * tileX;
      TILE_TRAP_OWNER_MASK(tileX, tileY) = 1 << *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178);
      UnitStack_SpendActionPointsByIndexClamped(stackIndex, 0, tileDataPtr, a5);
      while ( 1 )
      {
        squadCount = Unit_GetSquadCount(stackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( squadIndex >= squadCount )
          break;
        if ( *squadSlot == UNIT_TYPE_BUILDER )
        {
          *squadSlot = -1;
          break;
        }
      }
      Rules_SyncArmyFactStrength((short int*)(intptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET), UNIT_STACK_STRIDE * stackIndex, gameData, stackByteOffset, tileDataPtr, a5);
      Unit_CompactSquad((short int*)(intptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET), v18, v17);
      if ( *(__int16 *)(uintptr_t)(gameData + v19 + 147180) == -1 )
      {
        Rules_UnlinkArmyFact((short int*)(intptr_t)(v19 + gameData + UNIT_STACK_TABLE_OFFSET), v17);
        WorldMap_SyncSelectionForHumanPlayer(tileDataPtr);
      }
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 42B52E: variable 'v9' is possibly undefined
// 42B5EA: variable 'v16' is possibly undefined
// 42B5EC: variable 'v15' is possibly undefined
// 42B643: variable 'v18' is possibly undefined
// 42B643: variable 'v17' is possibly undefined
// 42B64D: variable 'v19' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0042B680) --------------------------------------------------------
int  Trap_ClearTileOwnerMask(int tileX, int tileY)
{
  int result; // eax

  result = gameData + TILE_TRAP_OWNER_MASK_ROW_STRIDE * tileX;
  TILE_TRAP_OWNER_MASK(tileX, tileY) = 0;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0042B6A0) --------------------------------------------------------
__int16 * Trap_HurtStack(__int16 *stack, char a2, DWORD a3, double a4)
{
  int unitIndex; // esi
  char *unitPtr; // ecx
  int unitRecord; // ecx
  unsigned int effectiveness; // ebx
  unsigned int damageRoll; // eax

  unitIndex = 0;
  Debug_Log((int)(intptr_t)(stack + 3), a2, a3, (int)(intptr_t)Trap_HurtUnit);
  do
  {
    if ( *(__int16 *)unitPtr == -1 )
      break;
    effectiveness = Unit_CalcEffectivenessB(unitPtr, 0);
    if ( effectiveness )
    {
      damageRoll = Rng_RandRange(270, 340);
      *(_BYTE *)(uintptr_t)(unitRecord + 9) -= damageRoll / effectiveness;
    }
    else
    {
      *(_BYTE *)(uintptr_t)(unitRecord + 9) = 0;
    }
    if ( *(char *)(uintptr_t)(unitRecord + 9) <= 0 )
      *(_WORD *)(uintptr_t)unitRecord = -1;
    unitPtr = (char *)(uintptr_t)(unitRecord + 31);
    ++unitIndex;
    *(unitPtr - 23) = 0;
  }
  while ( unitIndex < 10 );
  Unit_CompactSquad(stack, (int)(intptr_t)unitPtr, a4);
  return Rules_LinkArmyFinalize(stack, a4);
}
// 42B6BA: variable 'v6' is possibly undefined
// 42B6FA: variable 'v8' is possibly undefined

//----- (0042B730) --------------------------------------------------------
int  Trap_GetTileOwnerMask(int tileX, int tileY, int playerIndex)
{
  if ( playerIndex == -1 )
    return TILE_TRAP_OWNER_MASK(tileX, tileY);
  else
    return TILE_TRAP_OWNER_MASK(tileX, tileY) & (1 << playerIndex);
}
// 5202E4: using guessed type int gameData;

//----- (0042B770) --------------------------------------------------------
signed int  Trap_TriggerAtStackTile(int stackIndex, DWORD a2, double gameTime)
{
  __int16 *stackRecord; // ebx
  int stackBase; // eax
  int tileDataPtr; // ebx
  int ownerIndex; // ecx
  int v9; // edx
  int v10; // ecx
  int endTime; // edx
  int v12; // ecx
  unsigned int currentTime; // eax
  int v14; // ecx
  unsigned int v15; // edx
  int visionRadius; // eax
  int scanRow; // esi
  int i; // edx
  int stackCol; // edi
  int v20 CLASH95_UNUSED; // eax
  char owner; // cl
  int stackAddr; // eax
  int trapMaskRowBase; // ebx
  int v24; // ecx
  int scanRowTileBase; // [esp+4h] [ebp-24h]
  signed int radius; // [esp+Ch] [ebp-1Ch]

  stackRecord = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex);
  if ( UnitStack_GetMaxOrderTier((intptr_t)stackRecord) >= 3 )
  {
    visionRadius = UnitStack_GetVisionRadius((int)(intptr_t)stackRecord);
    scanRow = *stackRecord - visionRadius;
    radius = visionRadius;
    scanRowTileBase = 100 * scanRow;
    while ( scanRow < radius + *stackRecord )
    {
      for ( i = stackRecord[1] - radius; ; ++i )
      {
        stackCol = stackRecord[1];
        if ( i >= stackCol + radius )
          break;
        if ( scanRow >= 0
          && scanRow < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
          && i >= 0
          && i < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Math_CeilSqrt((i - stackCol) * (i - stackCol) + (scanRow - *stackRecord) * (scanRow - *stackRecord)) <= radius )
        {
          a2 = scanRowTileBase;
          if ( TILE_TRAP_OWNER_MASK(scanRow, i) )
          {
            owner = *((_BYTE *)stackRecord + 4);
            a2 = 1 << owner;
            if ( ((1 << owner) & TILE_TRAP_OWNER_MASK(scanRow, i)) == 0 )
            {
              TILE_TRAP_OWNER_MASK(scanRow, i) |= 1 << owner;
              WorldMap_RedrawViewport(1);
            }
          }
        }
      }
      ++scanRow;
      scanRowTileBase += 100;
    }
  }
  stackBase = gameData + UNIT_STACK_STRIDE * stackIndex;
  tileDataPtr = gameData + 100 * *(__int16 *)(uintptr_t)(stackBase + 147174) + *(__int16 *)(uintptr_t)(stackBase + 147176);
  if ( !TILE_TRAP_OWNER_MASK(*(__int16 *)(uintptr_t)(stackBase + 147174), *(__int16 *)(uintptr_t)(stackBase + 147176)) )
    return 0;
  ownerIndex = *(unsigned __int8 *)(uintptr_t)(stackBase + 147178);
  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * ownerIndex + 140059) )
  {
    TILE_TRAP_OWNER_MASK(*(__int16 *)(uintptr_t)(stackBase + 147174), *(__int16 *)(uintptr_t)(stackBase + 147176)) |= 1 << ownerIndex;
    WorldMap_RedrawViewport(1);
    WorldMap_RedrawViewport(1);
    endTime = Time_Now(v10, v9) + 200;
    while ( 1 )
    {
      currentTime = Time_Now(v12, endTime);
      if ( currentTime >= v15 )
        break;
      WorldMap_RedrawFrame(tileDataPtr);
    }
    Win_PlayModeChangeFrameTransition(aWpad_pul, 1, v14, tileDataPtr, a2);
  }
  stackAddr = gameData + UNIT_STACK_STRIDE * stackIndex;
  trapMaskRowBase = TILE_TRAP_OWNER_MASK_ROW_STRIDE * *(__int16 *)(uintptr_t)(stackAddr + 147174);
  TILE_TRAP_OWNER_MASK(*(__int16 *)(uintptr_t)(stackAddr + 147174), *(__int16 *)(uintptr_t)(stackAddr + 147176)) = 0;
  Rules_RetractTrapFact(*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + 147176));
  Trap_HurtStack((__int16 *)(uintptr_t)(v24 + gameData + UNIT_STACK_TABLE_OFFSET), trapMaskRowBase, a2, gameTime);
  return 1;
}
// 42B839: variable 'v10' is possibly undefined
// 42B839: variable 'v9' is possibly undefined
// 42B844: variable 'v12' is possibly undefined
// 42B844: variable 'v11' is possibly undefined
// 42B84B: variable 'v15' is possibly undefined
// 42B900: variable 'i' is possibly undefined
// 42B941: variable 'v14' is possibly undefined
// 42B9AA: variable 'v24' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0042B9D0) --------------------------------------------------------
int  Trap_ShowPitfallDiscoveryDialog(int tileX, int tileY, char spritePath, DWORD a4)
{
  int v4; // ecx
  _DWORD *spriteSetAlloc; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // ecx
  __int16 spriteHeight; // ax
  int glyphIndex; // edx
  int SpriteForChar; // eax
  int confirmBtnYMin; // esi
  int cancelBtnXMin; // ebx
  int cancelBtnYMin; // ebp
  int cancelBtnYMax; // edi
  __int16 eraseHeight; // ax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int secondLineY; // ebx
  unsigned __int16 fillRectYMax; // [esp+10h] [ebp-58h]
  unsigned __int16 eraseWidth; // [esp+10h] [ebp-58h]
  unsigned __int16 eraseX; // [esp+14h] [ebp-54h]
  unsigned __int16 eraseY; // [esp+18h] [ebp-50h]
  int messageStrings[3]; // [esp+1Ch] [ebp-4Ch]
  _DWORD *dialogSpriteSet; // [esp+28h] [ebp-40h] BYREF
  _DWORD *dialogSurface; // [esp+2Ch] [ebp-3Ch]
  int dialogY; // [esp+30h] [ebp-38h]
  int confirmBtnYMax; // [esp+34h] [ebp-34h]
  int confirmBtnXMax; // [esp+38h] [ebp-30h]
  int tileX2; // [esp+3Ch] [ebp-2Ch]
  int tileY2; // [esp+40h] [ebp-28h]
  void *savedRenderDevice; // [esp+44h] [ebp-24h]
  int dialogX; // [esp+48h] [ebp-20h]
  int confirmBtnXMin; // [esp+4Ch] [ebp-1Ch]
  int cancelBtnXMax; // [esp+50h] [ebp-18h]

  tileX2 = tileX;
  tileY2 = tileY;
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  Render_Pump();
  spriteSetAlloc = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, spritePath, a4);
  if ( spriteSetAlloc )
    spriteSetAlloc = DLXSpriteSet_Load(spriteSetAlloc, (const void*)(intptr_t)(spritePath));
  dialogSpriteSet = spriteSetAlloc;
  dialogX = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)spriteSetAlloc, 0)) / 2;
  dialogY = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)dialogSpriteSet, 0)) / 2;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v6, spritePath, a4);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)dialogSpriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)dialogSpriteSet, 0);
    Surface = Render_CreateSurface(v10, SpriteHeight, SpriteWidth);
  }
  dialogSurface = Surface;
  fillRectYMax = dialogY + DLX_GetSpriteWidth((int)(intptr_t)dialogSpriteSet, 0) - 1;
  spriteHeight = DLX_GetSpriteHeight((int)(intptr_t)dialogSpriteSet, 0);
  Render_FillRect(0, dialogSurface, (unsigned __int16)dialogY, (unsigned __int16)dialogX, dialogX + spriteHeight - 1, fillRectYMax, 0, 0);
  Render_ReleaseSurface(17, a4);
  if ( g_LanguageIndex == 2 )
    glyphIndex = 10;
  else
    glyphIndex = 0;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)dialogSpriteSet, glyphIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    dialogY,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  messageStrings[0] = (int)(intptr_t)g_TrapPitfallDiscoveryMessageStrings[0];
  messageStrings[1] = (int)(intptr_t)g_TrapPitfallDiscoveryMessageStrings[1];
  messageStrings[2] = (int)(intptr_t)g_TrapPitfallDiscoveryMessageStrings[2];
  if ( g_LanguageIndex )
  {
    secondLineY = dialogY + 52;
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      UI_DrawTextFmt((int)(intptr_t)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 32, 3, (const char*)(intptr_t)((int)(intptr_t)aThisIsAPitfall));
      UI_DrawTextFmt((int)(intptr_t)&dialogSpriteSet, v20, v21, secondLineY, 3, (const char*)(intptr_t)((int)(intptr_t)aDoYouWantToCov));
      goto LABEL_9;
    }
    if ( g_LanguageIndex == 2 )
    {
      UI_DrawTextFmt((int)(intptr_t)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 32, 3, (const char*)(intptr_t)((int)(intptr_t)aDasIstDieWolfs));
      UI_DrawTextFmt((int)(intptr_t)&dialogSpriteSet, v22, v23, secondLineY, 3, (const char*)(intptr_t)((int)(intptr_t)aWillstDuSieZus));
      goto LABEL_9;
    }
  }
  UI_DrawTextFmt((int)(intptr_t)&dialogSpriteSet, dialogX + 30, dialogX + 250, dialogY + 42, 3, (const char*)(intptr_t)(messageStrings[(unsigned __int8)g_LanguageIndex]));
LABEL_9:
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_Present((int)(intptr_t)g_RenderState);
  confirmBtnXMin = dialogX + 175;
  confirmBtnXMax = dialogX + 220;
  confirmBtnYMin = dialogY + 103;
  cancelBtnXMin = dialogX + 60;
  confirmBtnYMax = dialogY + 117;
  cancelBtnYMin = dialogY + 100;
  cancelBtnYMax = dialogY + 113;
  cancelBtnXMax = dialogX + 92;
  while ( 1 )
  {
    do
      DD_Pump((int)(intptr_t)g_RenderState, cancelBtnXMin);
    while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) );
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= cancelBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= cancelBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= cancelBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= cancelBtnYMax )
    {
      break;
    }
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= confirmBtnXMin
      && g_MouseCursorRawY >> g_CursorCoordShift >= confirmBtnYMin
      && g_MouseCursorRawX >> g_CursorCoordShift <= confirmBtnXMax
      && g_MouseCursorRawY >> g_CursorCoordShift <= confirmBtnYMax )
    {
      Trap_ClearTileOwnerMask(tileX2, tileY2);
      break;
    }
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Render_Pump();
  eraseY = dialogY;
  eraseX = dialogX;
  eraseWidth = DLX_GetSpriteWidth((int)(intptr_t)dialogSpriteSet, 0) - 1;
  eraseHeight = DLX_GetSpriteHeight((int)(intptr_t)dialogSpriteSet, 0);
  Render_FillRect(dialogSurface, 0, 0, 0, eraseHeight - 1, eraseWidth, eraseX, eraseY);
  if ( dialogSurface )
    (*(void (__cdecl **)(int, int, int))(uintptr_t)dialogSurface[46])(messageStrings[0], messageStrings[1], messageStrings[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&dialogSpriteSet);
  Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return WorldMap_RedrawViewport(1);
}
// 42BA03: variable 'v4' is possibly undefined
// 42BA5D: variable 'v6' is possibly undefined
// 42BA8A: variable 'v10' is possibly undefined
// 42BD1C: variable 'v20' is possibly undefined
// 42BD1C: variable 'v21' is possibly undefined
// 42BD3D: variable 'v22' is possibly undefined
// 42BD3D: variable 'v23' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B3C: using guessed type char *off_514B3C[2];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (0042BF00) --------------------------------------------------------
int  Battle_LoadWallSegmentsFromBuildingRecord(int buildingRecord)
{
  int buildingCellPtr; // ebx
  int col; // eax
  int colByteOffset; // edx
  int tileValue; // esi
  int aboveTileValue; // esi
  int belowTileValue; // ecx
  int result; // eax
  int wallRowBase; // [esp+4h] [ebp-30h]
  int prevRowIndex; // [esp+8h] [ebp-2Ch]
  int rowByteOffset; // [esp+Ch] [ebp-28h]
  int row; // [esp+10h] [ebp-24h]

  row = 1;
  rowByteOffset = 40;
  prevRowIndex = 0;
  wallRowBase = 20;
  while ( *(_DWORD *)(uintptr_t)(g_MapData + 804) - 1 > row )
  {
    buildingCellPtr = buildingRecord;
    col = 0;
    colByteOffset = 0;
    while ( col < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
    {
      tileValue = *(__int16 *)(uintptr_t)(colByteOffset + g_MapData + rowByteOffset);
      if ( tileValue >= 388 && tileValue <= 403 )
      {
        aboveTileValue = *(__int16 *)(uintptr_t)(colByteOffset + g_MapData + 40 * prevRowIndex);
        if ( aboveTileValue < 388 || aboveTileValue > 403 || (belowTileValue = *(__int16 *)(uintptr_t)(40 * (row + 1) + g_MapData + colByteOffset), belowTileValue < 388) || belowTileValue > 403 )
        {
          *(_BYTE *)(uintptr_t)(wallRowBase + g_MapData + col + 3134) = *(_BYTE *)(uintptr_t)(buildingCellPtr + 422);
          *(_BYTE *)(uintptr_t)(wallRowBase + g_MapData + col + 3534) = 100;
        }
      }
      colByteOffset += 2;
      ++buildingCellPtr;
      ++col;
    }
    rowByteOffset += 40;
    ++prevRowIndex;
    wallRowBase += 20;
    ++row;
  }
  *(_DWORD *)(uintptr_t)(g_MapData + 828) = *(_DWORD *)(uintptr_t)(g_MapData + 800) / 2;
  result = *(unsigned __int8 *)(uintptr_t)(buildingRecord + 421);
  *(_DWORD *)(uintptr_t)(g_MapData + 820) = result;
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C060) --------------------------------------------------------
char  Battle_SaveWallSegmentsToBuildingRecord(int buildingRecord)
{
  int wallRow; // edx
  int i; // eax
  int buildingCellPtr; // ecx
  int col; // eax
  int wallRowBase; // ebx
  char wallHp; // dl
  char result; // al

  wallRow = 0;
  for ( i = 0; wallRow < *(_DWORD *)(uintptr_t)(g_MapData + 804) && !*(_BYTE *)(uintptr_t)(g_MapData + i + 3534); i += 20 )
    ++wallRow;
  buildingCellPtr = buildingRecord;
  col = 0;
  wallRowBase = 20 * wallRow;
  while ( col < *(_DWORD *)(uintptr_t)(g_MapData + 800) )
  {
    ++buildingCellPtr;
    wallHp = *(_BYTE *)(uintptr_t)(wallRowBase + g_MapData + col++ + 3134);
    *(_BYTE *)(uintptr_t)(buildingCellPtr + 421) = wallHp;
  }
  result = g_CurrentPlayerIndex;
  if ( g_CurrentPlayerIndex == *(_DWORD *)(uintptr_t)(g_MapData + 840) )
  {
    result = *(_BYTE *)(uintptr_t)(g_MapData + 832);
    *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_MapData + 828) + buildingRecord + 422) = result;
  }
  return result;
}
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;

//----- (0042C0F0) --------------------------------------------------------
BOOL  UnitBattle_IsTileInViewport(int tileRow, int tileCol)
{
  int rowOrigin; // ebx
  int colOrigin; // esi
  BOOL result; // eax

  rowOrigin = *(_DWORD *)(uintptr_t)(g_MapData + 808);
  result = 0;
  if ( tileRow >= rowOrigin && tileRow < rowOrigin + 7 )
  {
    colOrigin = *(_DWORD *)(uintptr_t)(g_MapData + 812);
    if ( tileCol >= colOrigin && tileCol < colOrigin + 7 )
      return 1;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042C130) --------------------------------------------------------
void  Battle_LogUnitEntry(__int16 *unitRecord, DWORD a2, ...)
{
  char *unit_name;

  if ( !unitRecord )
    return;
  unit_name = UnitType_GetLocalizedName((unit_type)*unitRecord);
  Debug_Log((int)(uintptr_t)unitRecord, 0, a2, (int)(intptr_t)aD0x08x15sPl1dP, unit_name);
}
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0042C180) --------------------------------------------------------
void  Battle_LogAllUnits(int a1, char a2, DWORD a3)
{
  int slotIndex; // ebx
  __int16 *unitRecord; // ecx
  int v6 CLASH95_UNUSED; // ecx

  Debug_Log(a1, a2, a3, (int)(intptr_t)aBattle_logallu);
  slotIndex = 0;
  unitRecord = (__int16 *)(uintptr_t)(g_MapData + 852);
  do
  {
    while ( *unitRecord == -1 )
    {
      ++slotIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
      if ( slotIndex >= 22 )
        return;
    }
    Battle_LogUnitEntry(unitRecord, a3);
    ++slotIndex;
    unitRecord = (__int16 *)((char *)unitRecord + 31);
  }
  while ( slotIndex < 22 );
}
// 42C1BF: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042C1D0) --------------------------------------------------------
int  GodAnger(DWORD playerIndex, int a2, char a3)
{
  int k; // ecx
  int unitRecord; // esi
  int result; // eax
  int v7 CLASH95_UNUSED; // ecx
  int v8 CLASH95_UNUSED; // ecx
  int v9 CLASH95_UNUSED; // ecx
  _DWORD *spriteSet; // eax
  int i; // esi
  __lock *blackFadeStepArg; // ecx
  int SpriteForChar; // eax
  unsigned __int8 *v14 CLASH95_UNUSED; // edx
  __lock *v15 CLASH95_UNUSED; // ecx
  int v16 CLASH95_UNUSED; // ecx
  __int16 SpriteHeight; // ax
  int flashLevel; // esi
  __lock *flashLevelArg; // ecx
  int j; // esi
  __lock *mapFadeStepArg; // ecx
  unsigned __int16 lightningWidth; // [esp+Ch] [ebp-838h]
  unsigned __int8 blackPalette[1024]; // [esp+1Ch] [ebp-828h] BYREF
  unsigned __int8 whitePalette[1024]; // [esp+41Ch] [ebp-428h] BYREF
  int messageStrings[3]; // [esp+81Ch] [ebp-28h]
  _DWORD *lightningSpriteSet; // [esp+828h] [ebp-1Ch] BYREF
  void *savedRenderDevice; // [esp+82Ch] [ebp-18h]

  Debug_Log(a2, a3, playerIndex, (int)(intptr_t)aGodanger);
  messageStrings[0] = (int)(intptr_t)g_GodAngerMessageStrings[0];
  messageStrings[1] = (int)(intptr_t)g_GodAngerMessageStrings[1];
  messageStrings[2] = (int)(intptr_t)g_GodAngerMessageStrings[2];
  if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * playerIndex + 140059) )
  {
    UnitBattle_ShowPlayerMessageBanner(messageStrings[(unsigned __int8)g_LanguageIndex], playerIndex, 0, playerIndex);
    Render_Pump();
    savedRenderDevice = g_RenderDevice;
    memset(blackPalette, 0, sizeof(blackPalette));
    Palette_LoadFromQueryHandle((intptr_t)whitePalette, (intptr_t)"white.pal");
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_white_palette", (int)playerIndex, 0, 0, 0);
    spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
    if ( spriteSet )
      spriteSet = DLXSpriteSet_Load(spriteSet, "lightn.s32");
    lightningSpriteSet = spriteSet;
    for ( i = 0; i < 300; ++i )
    {
      blackFadeStepArg = (__lock *)(uintptr_t)i;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, blackPalette, (int)(intptr_t)(blackFadeStepArg), 450);
    }
    g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
    SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)lightningSpriteSet, 0);
    Compat_RenderDeviceDrawMenuSprite(16, 100, SpriteForChar, 1);
    Diagnostics_TraceWorldMapActionEvent("god_anger_after_lightning_draw", (int)playerIndex, (int)(uintptr_t)lightningSpriteSet, SpriteForChar, 0);
    Audio_PlayArtifactSound(0);
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, whitePalette, 150, 200);
    Timer_BusyWaitWithCallback(10, 0, 0);
    lightningWidth = DLX_GetSpriteWidth((int)(intptr_t)lightningSpriteSet, 0) + 16;
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)lightningSpriteSet, 0);
    flashLevel = 150;
    Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 16, 50, SpriteHeight + 200, lightningWidth, 0x32u, 0x10u);
    do
    {
      flashLevelArg = (__lock *)(uintptr_t)flashLevel;
      flashLevel -= 60;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, whitePalette, (int)(intptr_t)(flashLevelArg), 200);
    }
    while ( flashLevel > 0 );
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, blackPalette, (int)(intptr_t)((__lock *)0x96), 200);
    for ( j = 0; j < 150; ++j )
    {
      mapFadeStepArg = (__lock *)(uintptr_t)j;
      Palette_CrossfadeStep((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr, (int)(intptr_t)(mapFadeStepArg), 150);
    }
    Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)(uintptr_t)g_MapPalettePtr);
    DLXSpriteSet_ReleaseAndClear((int *)&lightningSpriteSet);
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
    Render_Present((int)(intptr_t)g_RenderState);
    UnitBattle_RedrawVisibleGrid();
  }
  for ( k = 0; k != 682; k += 31 )
  {
    unitRecord = k + g_MapData;
    result = *(__int16 *)(uintptr_t)(k + g_MapData + 852);
    if ( result != -1 )
    {
      result = *(unsigned __int8 *)(uintptr_t)(unitRecord + 854);
      if ( result == playerIndex )
      {
        *(_BYTE *)(uintptr_t)(unitRecord + 861) -= Rng_RandRange(20, 30);
        result = *(char *)(uintptr_t)(k + g_MapData + 861);
        if ( result <= 0 )
        {
          *(_WORD *)(uintptr_t)(k + g_MapData + 852) = -1;
          result = *(unsigned __int16 *)(uintptr_t)(k + g_MapData + 858);
          *(_WORD *)(uintptr_t)(g_MapData + 40 * *(unsigned __int16 *)(uintptr_t)(k + g_MapData + 856) + 2 * result + 1534) = -1;
        }
      }
    }
  }
  return result;
}
// 42C25B: variable 'k' is possibly undefined
// 42C2BF: variable 'v7' is possibly undefined
// 42C2D0: variable 'v8' is possibly undefined
// 42C2DA: variable 'v9' is possibly undefined
// 42C37C: variable 'v14' is possibly undefined
// 42C37C: variable 'v15' is possibly undefined
// 42C388: variable 'v16' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B50: using guessed type char *off_514B50[9];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042C4C0) --------------------------------------------------------
int  Battle_NewTurn(int a1, char a2, DWORD a3)
{
  int v3; // ecx
  int result; // eax

  Debug_Log(a1, a2, a3, (int)(intptr_t)aBattle_newturn);
  Battle_LogAllUnits(v3, a2, a3);
  for ( result = 0; result < 2; ++result )
    ;
  return result;
}
// 42C4CD: variable 'v3' is possibly undefined

//----- (0042C4E0) --------------------------------------------------------
BOOL Battle_HasUnitsForBothSides(void)
{
  int attackerPresent; // esi
  int defenderPresent; // edi
  int i; // eax
  int owner; // ecx

  attackerPresent = 0;
  defenderPresent = 0;
  for ( i = 0; i != 682; i += 31 )
  {
    if ( *(__int16 *)(uintptr_t)(i + g_MapData + 852) != -1 )
    {
      owner = *(unsigned __int8 *)(uintptr_t)(i + g_MapData + 854);
      if ( owner == *(_DWORD *)(uintptr_t)(g_MapData + 836) )
      {
        attackerPresent = 1;
      }
      else if ( owner == *(_DWORD *)(uintptr_t)(g_MapData + 840) )
      {
        defenderPresent = 1;
      }
    }
  }
  return attackerPresent && defenderPresent;
}
// 532048: using guessed type int g_MapData;
