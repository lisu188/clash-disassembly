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
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE void QueenMarriageProposal_WriteButtonWidgetRecord (unsigned char *record, int left, int top, int sprite_index_base, int sprite_index_selected_base, int action_callback, _DWORD **sprite_set_holder, const char *sound_name);
CLASH95_TEST_VISIBLE void QueenMarriageProposal_RebuildButtonWidgets (unsigned char *widgets, _DWORD **sprite_set_holder, int confirm_left, int top, int cancel_left);
CLASH95_TEST_VISIBLE void YesNoWindow_WriteButtonWidgetRecord (unsigned char *record, int left, int top, int sprite_index_base, int sprite_index_selected_base, int action_callback);
CLASH95_TEST_VISIBLE void YesNoWindow_RebuildButtonWidgets (unsigned char *widgets, int confirm_left, int top, int cancel_left);
CLASH95_TEST_VISIBLE void MainMenu_WriteButtonWidgetTemplateRecord (unsigned char *record, int left, int top, int sprite_index_base, int sprite_index_selected_base, int action_callback, const char *sound_name);
CLASH95_TEST_VISIBLE void CampaignMenu_WriteButtonWidgetTemplateRecord (unsigned char *record, int left, int top, int sprite_index_base, int sprite_index_selected_base, int action_callback, const char *sound_name);

//----- (00446230) --------------------------------------------------------
int  Demo_ShowNumberedTextScreen(char spriteSetName, DWORD textScreenNumber)
{
  int previousResourceHandle; // edi
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  _DWORD *spriteSet; // eax
  int v7; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // ax
  int v10; // ecx
  _DWORD *fillSurface; // esi
  _DWORD *backdropSurface; // ebp
  __int16 fillHeight; // ax
  int SpriteForChar; // eax
  int v15; // ecx
  int v16; // edx
  _DWORD *renderState; // ecx
  int v18; // edx
  int v19; // ecx
  unsigned int currentTime; // eax
  unsigned int deadlineTime; // edx
  __int16 clearHeight; // ax
  _BYTE resourcePathBuffer[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *textSpriteSet; // [esp+64h] [ebp-28h] BYREF
  int renderDeviceVtbl; // [esp+68h] [ebp-24h]
  void *previousRenderDevice; // [esp+6Ch] [ebp-20h]
  int (*previousRenderHook)(); // [esp+70h] [ebp-1Ch]

  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, spriteSetName, textScreenNumber, (int)(intptr_t)aSetrhS08x_23);
  sprintf_(resourcePathBuffer, "demo\\tekst%02d.s32", v4 + 1);
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v5, spriteSetName, textScreenNumber);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, spriteSetName);
  textSpriteSet = spriteSet;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, spriteSetName, textScreenNumber);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)textSpriteSet, 0);
    Surface = Render_CreateSurface(v10, SCREEN_WIDTH, SpriteWidth);
  }
  fillSurface = Surface;
  backdropSurface = Surface;
  fillHeight = DLX_GetSpriteWidth((int)(intptr_t)textSpriteSet, 0);
  Render_FillRect(0, fillSurface, 0, 0, SCREEN_MAX_X, fillHeight - 1, 0, 0);
  DLXSpriteSet_DrawText((int)(intptr_t)textSpriteSet, 0, (int)(intptr_t)&g_RenderEnvPaletteContext, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
  previousRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)textSpriteSet, 0);
  renderDeviceVtbl = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(uintptr_t)(renderDeviceVtbl + 52))(
    0,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    0);
  g_RenderDevice = previousRenderDevice;
  Time_Now(v15, 1);
  Render_BlitSurface(&g_MainRenderDevice, v16, 0, (DWORD)(intptr_t)backdropSurface);
  renderState = g_RenderState;
  while ( !Input_PollEventsUntil((int)(intptr_t)renderState, (char)(intptr_t)&g_InputBackendState) )
  {
    currentTime = Time_Now(v19, v18);
    if ( currentTime >= deadlineTime || Input_IsAnyKeyPressed() )
      break;
    InputBackend_PollState(&g_InputBackendState, deadlineTime, v19);
  }
  Debug_Log(v19, (char)(intptr_t)g_RenderHook, (DWORD)(intptr_t)backdropSurface, (int)(intptr_t)aUnsetrh08x_23);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  clearHeight = DLX_GetSpriteWidth((int)(intptr_t)textSpriteSet, 0);
  Render_FillRect(backdropSurface, 0, 0, 0, SCREEN_MAX_X, clearHeight - 1, 0, 0);
  return DLXSpriteSet_ReleaseAndClear((int *)&textSpriteSet);
}
// 446278: variable 'v3' is possibly undefined
// 446281: variable 'v4' is possibly undefined
// 446299: variable 'v5' is possibly undefined
// 4462B2: variable 'v7' is possibly undefined
// 4462D4: variable 'v10' is possibly undefined
// 446378: variable 'v15' is possibly undefined
// 446384: variable 'v16' is possibly undefined
// 44639B: variable 'v17' is possibly undefined
// 4463A4: variable 'v19' is possibly undefined
// 4463A4: variable 'v18' is possibly undefined
// 4463AB: variable 'v21' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00446430) --------------------------------------------------------
int  DecisionDialog_ConfirmIfAllowed(uintptr_t a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  if ( !g_DecisionDialogConfirmDisabled )
  {
    g_DecisionDialogExitSignal = 1;
    g_DecisionDialogResult = 1;
  }
  return result;
}
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 543D5C: using guessed type int g_DecisionDialogConfirmDisabled;

//----- (00446460) --------------------------------------------------------
int  DecisionDialog_Cancel(uintptr_t a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_DecisionDialogExitSignal = 1;
  g_DecisionDialogResult = 0;
  return result;
}
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;

CLASH95_INTERNAL _DWORD *g_QueenMarriageProposalWidgetSpriteSet;

CLASH95_TEST_VISIBLE void QueenMarriageProposal_WriteButtonWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        _DWORD **sprite_set_holder,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)sprite_set_holder;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

CLASH95_TEST_VISIBLE void QueenMarriageProposal_RebuildButtonWidgets(
        unsigned char *widgets,
        _DWORD **sprite_set_holder,
        int confirm_left,
        int top,
        int cancel_left)
{
  static const char proposal_button_sound[] = "male";

  QueenMarriageProposal_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    confirm_left,
    top,
    10,
    12,
    (int)(uintptr_t)&DecisionDialog_ConfirmIfAllowed,
    sprite_set_holder,
    proposal_button_sound);
  QueenMarriageProposal_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    cancel_left,
    top,
    11,
    13,
    (int)(uintptr_t)&DecisionDialog_Cancel,
    sprite_set_holder,
    proposal_button_sound);
  memset(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2) = -1;
}

//----- (00446480) --------------------------------------------------------
int  Queen_ShowWhimDecisionDialog(int text, int requiredAmount, int a3, int a4, DWORD allocContext)
{
  int v6; // ecx
  _DWORD *spriteSet; // eax
  int v8; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v12; // edx
  int v13 CLASH95_UNUSED; // ecx
  int v14 CLASH95_UNUSED; // ecx
  int v15; // ecx
  int result; // eax
  _DWORD widgetTable[40]; // [esp+38h] [ebp-D8h] BYREF
  _DWORD *whimSpriteSet; // [esp+D8h] [ebp-38h] BYREF
  int playerAmount; // [esp+DCh] [ebp-34h]
  int SpriteHeight; // [esp+E0h] [ebp-30h]
  int panelTop; // [esp+E4h] [ebp-2Ch]
  int deviceVtable; // [esp+E8h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+ECh] [ebp-24h]
  int previousResourceHandle; // [esp+F0h] [ebp-20h]
  int messageText; // [esp+F4h] [ebp-1Ch]
  int SpriteWidth; // [esp+F8h] [ebp-18h]
  int panelLeft; // [esp+FCh] [ebp-14h]

  messageText = text;
  playerAmount = a4;
  Debug_Log(a3, a4, allocContext, (int)(intptr_t)aQueenwhimmessa);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, a4, allocContext, (int)(intptr_t)aSetrhS08x_18);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, allocContext);
  whimSpriteSet = 0;
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v6, 0, allocContext);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, 0);
  whimSpriteSet = spriteSet;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)whimSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)whimSpriteSet, 0);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v8, 0, allocContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)(intptr_t)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)whimSpriteSet, 0);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)whimSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(panelLeft + 41, panelTop + 18, SpriteForChar, 1);
  Render_ReleaseSurface(17, backdropSurface);
  UI_DrawTextFmt(deviceVtable, panelLeft + 175, panelLeft + 525, panelTop + 65, 6, messageText);
  Render_ReleaseSurface(18, backdropSurface);
  UI_DrawText(panelLeft + 198, panelTop + 12, (int)(intptr_t)aD_6);
  UI_DrawTextFmt(playerAmount, panelLeft + 126, v12, panelTop + 207, 3, (int)(intptr_t)aD_7);
  g_DecisionDialogConfirmDisabled = requiredAmount > playerAmount;
  qmemcpy(widgetTable, &g_QueenWhimDecisionButtonWidgetsTemplate, 0x9Fu);
  widgetTable[0] = panelLeft + 126;
  widgetTable[1] = panelTop + 175;
  widgetTable[3] = &whimSpriteSet;
  *(_DWORD *)((char *)&widgetTable[13] + 1) = panelLeft + 451;
  *(_DWORD *)((char *)&widgetTable[14] + 1) = panelTop + 175;
  *(_DWORD *)((char *)&widgetTable[16] + 1) = &whimSpriteSet;
  UIWidgetTable_InitDrawStates(widgetTable);
  Render_Present((int)(intptr_t)g_RenderState);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(widgetTable, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v15, (char)(intptr_t)g_RenderState, backdropSurface, (int)(intptr_t)aUnsetrh08x_18);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)(uintptr_t)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&whimSpriteSet);
  result = g_DecisionDialogResult;
  g_DecisionDialogConfirmDisabled = 0;
  return result;
}
// 446527: variable 'v6' is possibly undefined
// 4465A9: variable 'v8' is possibly undefined
// 446776: variable 'v12' is possibly undefined
// 446801: variable 'v13' is possibly undefined
// 44681D: variable 'v14' is possibly undefined
// 446835: variable 'v15' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 543D5C: using guessed type int g_DecisionDialogConfirmDisabled;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

CLASH95_INTERNAL _DWORD *g_YesNoWindowWidgetSpriteSet;

CLASH95_TEST_VISIBLE void YesNoWindow_WriteButtonWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback)
{
  static const char yesno_button_sound[] = "male";

  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_YesNoWindowWidgetSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)yesno_button_sound;
}

CLASH95_TEST_VISIBLE void YesNoWindow_RebuildButtonWidgets(unsigned char *widgets, int confirm_left, int top, int cancel_left)
{
  YesNoWindow_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    confirm_left,
    top,
    5,
    6,
    (int)(uintptr_t)&DecisionDialog_ConfirmIfAllowed);
  YesNoWindow_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    cancel_left,
    top,
    7,
    8,
    (int)(uintptr_t)&DecisionDialog_Cancel);
  memset(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2) = -1;
}

//----- (004468F0) --------------------------------------------------------
int  YesNoWindow(int text, _BYTE *imageData, int a3, char a4, DWORD allocContext)
{
  int v6; // ecx
  char mapPaletteByte; // bl
  _DWORD *spriteSet; // eax
  int i; // esi
  int drawFrameIndex; // edx
  int v11; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int deviceVtable; // edi
  int panelLeftForButtons; // eax
  int v17 CLASH95_UNUSED; // ecx
  _DWORD *v18 CLASH95_UNUSED; // edi
  char *v19 CLASH95_UNUSED; // esi
  int v20 CLASH95_UNUSED; // edx
  int v21 CLASH95_UNUSED; // ecx
  int v22; // ecx
  _DWORD widgetTable[40]; // [esp+1Ch] [ebp-D0h] BYREF
  _DWORD *scrollSpriteSet; // [esp+BCh] [ebp-30h] BYREF
  int panelTop; // [esp+C0h] [ebp-2Ch]
  int promptText; // [esp+C4h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+C8h] [ebp-24h]
  int previousResourceHandle; // [esp+CCh] [ebp-20h]
  int SpriteWidth; // [esp+D0h] [ebp-1Ch]
  int SpriteHeight; // [esp+D4h] [ebp-18h]
  int panelLeft; // [esp+D8h] [ebp-14h]

  promptText = text;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] enter text=%p image=%p\n", (void *)(uintptr_t)text, (void *)imageData);
  Debug_Log(a3, a4, allocContext, (int)(intptr_t)aYesnowindowS);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, a4, allocContext, (int)(intptr_t)aSetrhS08x_12);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, allocContext);
  if ( imageData )
    Render_LoadResourceSprite_v4(17, imageData, v6, a4, allocContext);
  mapPaletteByte = 0;
  scrollSpriteSet = 0;
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v6, 0, allocContext);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, "pergamin.s32");
  scrollSpriteSet = spriteSet;
  g_YesNoWindowWidgetSpriteSet = scrollSpriteSet;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] sprite_load set=%p data=%x\n", (void *)scrollSpriteSet, scrollSpriteSet ? (unsigned int)scrollSpriteSet[1024] : 0);
  if ( imageData )
  {
    for ( i = 4; i <= 8; ++i )
    {
      mapPaletteByte = g_MapPalettePtr;
      drawFrameIndex = i;
      DLXSpriteSet_DrawText((int)(intptr_t)scrollSpriteSet, drawFrameIndex, (int)(intptr_t)imageData, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
    }
  }
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 4u)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 4u);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v11, mapPaletteByte, allocContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)(intptr_t)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 4);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] before_background sprite=%x left=%d top=%d\n", SpriteForChar, panelLeft, panelTop);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_background\n");
  UI_DrawTextFmt(deviceVtable, panelLeft + 30, panelLeft + 260, panelTop + 15, 3, promptText);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_text\n");
  panelLeftForButtons = panelLeft;
  YesNoWindow_RebuildButtonWidgets((unsigned char *)widgetTable, panelLeftForButtons + 72, panelTop + 38, panelLeft + 146);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] before_widget_init holder=%p widget=%p\n", (void *)&g_YesNoWindowWidgetSpriteSet, (void *)widgetTable);
  UIWidgetTable_InitDrawStates(widgetTable);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_widget_init\n");
  Render_Present((int)(intptr_t)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_present\n");
  g_DecisionDialogConfirmDisabled = 0;
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(widgetTable, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v22, (char)(intptr_t)g_RenderState, backdropSurface, (int)(intptr_t)aUnsetrh08x_12);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)(uintptr_t)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  g_YesNoWindowWidgetSpriteSet = 0;
  UI_EndDraw(17);
  return g_DecisionDialogResult;
}
// 44698D: variable 'v6' is possibly undefined
// 446A58: variable 'v11' is possibly undefined
// 446B62: variable 'v17' is possibly undefined
// 446BC6: variable 'v20' is possibly undefined
// 446BE3: variable 'v21' is possibly undefined
// 446BFB: variable 'v22' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202F4: using guessed type int dword_5202F4;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00446CB0) --------------------------------------------------------
int  UI_ShowSimpleTextInfoWindow(int a1, int a2, char a3, DWORD context)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  int panelLeft; // edi
  int v7; // ecx
  _DWORD *Surface; // eax
  _DWORD *backdropSurface; // esi
  int SpriteForChar; // eax
  DWORD deviceVtable; // ebp
  int v12; // ecx
  unsigned __int16 v13; // cx
  _DWORD *scrollSpriteSet; // [esp+18h] [ebp-3Ch] BYREF
  int previousResourceHandle; // [esp+1Ch] [ebp-38h]
  int SpriteWidth; // [esp+20h] [ebp-34h]
  int (*previousRenderHook)(); // [esp+24h] [ebp-30h]
  int SpriteHeight; // [esp+28h] [ebp-2Ch]
  int messageText; // [esp+2Ch] [ebp-28h]
  int v21 CLASH95_UNUSED; // [esp+30h] [ebp-24h]
  int v22 CLASH95_UNUSED; // [esp+34h] [ebp-20h]
  int panelTop; // [esp+38h] [ebp-1Ch]

  messageText = a1;
  Debug_Log(a2, a3, context, (int)(intptr_t)aInfowindowS);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, a3, context, (int)(intptr_t)aSetrhS08x_13);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, context);
  scrollSpriteSet = 0;
  loadedSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, 0, context);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, 0);
  scrollSpriteSet = loadedSpriteSet;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)loadedSpriteSet, 9u)) / 2;
  panelTop = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 9u)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)scrollSpriteSet, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)scrollSpriteSet, 4u);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, 0, context);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = Surface;
  v21 = (unsigned __int16)panelTop;
  v22 = (unsigned __int16)panelLeft;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    panelLeft + SpriteHeight - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)scrollSpriteSet, 9);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceVtable + 52))(
    panelTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(panelLeft + 25, panelLeft + 25, panelLeft + 250, panelTop + 34, 3, messageText);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Debug_Log(v12, panelLeft, deviceVtable, (int)(intptr_t)aUnsetrh08x_13);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, v13);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    (*(void (**)(void))(uintptr_t)backdropSurface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  return UI_EndDraw(17);
}
// 446D40: variable 'v4' is possibly undefined
// 446DCE: variable 'v7' is possibly undefined
// 446EA7: variable 'v12' is possibly undefined
// 446EEE: variable 'v13' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00446F40) --------------------------------------------------------
int  Queen_ShowMarriageProposalDialog(int a1, char a2, DWORD logContext)
{
  int v3; // ecx
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v10; // eax
  int v11 CLASH95_UNUSED; // ecx
  _DWORD *v12 CLASH95_UNUSED; // edi
  char *v13 CLASH95_UNUSED; // esi
  int v14 CLASH95_UNUSED; // ecx
  int v15 CLASH95_UNUSED; // ecx
  int v16; // ecx
  _DWORD widgetTable[40]; // [esp+38h] [ebp-DCh] BYREF
  int proposalTextTable[3]; // [esp+D8h] [ebp-3Ch]
  _DWORD *proposalSpriteSet; // [esp+E4h] [ebp-30h] BYREF
  int panelTop; // [esp+E8h] [ebp-2Ch]
  int panelLeft; // [esp+ECh] [ebp-28h]
  int (*previousRenderHook)(); // [esp+F0h] [ebp-24h]
  int SpriteWidth; // [esp+F4h] [ebp-20h]
  int previousResourceHandle; // [esp+F8h] [ebp-1Ch]
  int SpriteHeight; // [esp+FCh] [ebp-18h]

  Debug_Log(a1, a2, logContext, (int)(intptr_t)aNewqueenwindow);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_log",
    g_SelectedUnitIndex,
    a1,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, a2, logContext, (int)(intptr_t)aSetrhS08x_17);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_set_rh",
    g_SelectedUnitIndex,
    previousResourceHandle,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_render_pump",
    g_SelectedUnitIndex,
    g_ActiveCursorDescriptor,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_ReleaseSurface(17, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_release_surface",
    g_SelectedUnitIndex,
    17,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  proposalSpriteSet = 0;
  v5 = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, a2, logContext);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, aQueen_s32_0);
  proposalSpriteSet = v5;
  g_QueenMarriageProposalWidgetSpriteSet = proposalSpriteSet;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_sprite_load",
    g_SelectedUnitIndex,
    (int)(uintptr_t)proposalSpriteSet,
    proposalSpriteSet ? (int)proposalSpriteSet[1025] : -1,
    proposalSpriteSet ? (int)proposalSpriteSet[1024] : 0);
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)v5, 0)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)proposalSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)proposalSpriteSet, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_dims",
    g_SelectedUnitIndex,
    SpriteHeight,
    SpriteWidth,
    panelLeft);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v6, 150, logContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)(intptr_t)Surface;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_surface_create",
    g_SelectedUnitIndex,
    (int)(uintptr_t)Surface,
    SpriteHeight,
    SpriteWidth);
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)proposalSpriteSet, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_background_lookup",
    g_SelectedUnitIndex,
    SpriteForChar,
    0,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_background_draw",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(uintptr_t)SpriteForChar,
    *(unsigned __int16 *)(uintptr_t)(SpriteForChar + 2),
    *(int *)(uintptr_t)(SpriteForChar + 14));
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_background_draw",
    g_SelectedUnitIndex,
    panelLeft,
    panelTop,
    0);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)proposalSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_portrait_lookup",
    g_SelectedUnitIndex,
    SpriteForChar,
    PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_portrait_draw",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(uintptr_t)SpriteForChar,
    *(unsigned __int16 *)(uintptr_t)(SpriteForChar + 2),
    *(int *)(uintptr_t)(SpriteForChar + 14));
  Compat_RenderDeviceDrawMenuSprite(panelLeft + 41, panelTop + 18, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_portrait_draw",
    g_SelectedUnitIndex,
    panelLeft + 41,
    panelTop + 18,
    0);
  proposalTextTable[0] = (int)(intptr_t)g_QueenMarriageProposalTexts[0];
  proposalTextTable[1] = (int)(intptr_t)g_QueenMarriageProposalTexts[1];
  proposalTextTable[2] = (int)(intptr_t)g_QueenMarriageProposalTexts[2];
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_text",
    g_SelectedUnitIndex,
    (int)(uintptr_t)proposalTextTable[(unsigned __int8)g_LanguageIndex],
    (unsigned __int8)g_LanguageIndex,
    0);
  UI_DrawTextFmt((int)(intptr_t)widgetTable, panelLeft + 175, panelLeft + 525, panelTop + 55, 6, proposalTextTable[(unsigned __int8)g_LanguageIndex]);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_text",
    g_SelectedUnitIndex,
    panelLeft + 175,
    panelTop + 55,
    0);
  v10 = panelLeft;
  QueenMarriageProposal_RebuildButtonWidgets(
    (unsigned char *)widgetTable,
    &g_QueenMarriageProposalWidgetSpriteSet,
    v10 + 126,
    panelTop + 175,
    panelLeft + 451);
  g_QueenMarriageProposalWidgetTableBase = (uintptr_t)widgetTable;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_widget_rebuild",
    g_SelectedUnitIndex,
    (int)(uintptr_t)widgetTable,
    0x9F,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_widget_init",
    g_SelectedUnitIndex,
    widgetTable[0],
    widgetTable[1],
    *(_DWORD *)((char *)&widgetTable[13] + 1));
  UIWidgetTable_InitDrawStates(widgetTable);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_widget_init",
    g_SelectedUnitIndex,
    (int)(uintptr_t)widgetTable,
    0,
    0);
  Render_Present((int)(intptr_t)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_present",
    g_SelectedUnitIndex,
    (int)(uintptr_t)widgetTable,
    (int)(uintptr_t)backdropSurface,
    0);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(widgetTable, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v16, (char)(intptr_t)g_RenderState, backdropSurface, (int)(intptr_t)aUnsetrh08x_17);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)(uintptr_t)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&proposalSpriteSet);
  g_QueenMarriageProposalWidgetSpriteSet = 0;
  g_QueenMarriageProposalWidgetTableBase = 0;
  UI_EndDraw(17);
  return g_DecisionDialogResult;
}
// 446F9D: variable 'v3' is possibly undefined
// 446FD0: variable 'v4' is possibly undefined
// 447059: variable 'v6' is possibly undefined
// 4471D4: variable 'v11' is possibly undefined
// 447238: variable 'v14' is possibly undefined
// 447255: variable 'v15' is possibly undefined
// 44726D: variable 'v16' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518010: using guessed type char *g_QueenMarriageProposalTexts[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00447330) --------------------------------------------------------
int  Queen_ShowMessageDialog(int message, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  _DWORD *loadedSpriteSet; // eax
  int panelLeft; // esi
  int v7; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int portraitSprite; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  _DWORD *queenSpriteSet; // [esp+34h] [ebp-38h] BYREF
  int messageText; // [esp+38h] [ebp-34h]
  int deviceVtable; // [esp+3Ch] [ebp-30h]
  int (*previousRenderHook)(); // [esp+40h] [ebp-2Ch]
  _DWORD *backdropSurface; // [esp+44h] [ebp-28h]
  int previousResourceHandle; // [esp+48h] [ebp-24h]
  int SpriteWidth; // [esp+4Ch] [ebp-20h]
  int SpriteHeight; // [esp+50h] [ebp-1Ch]

  messageText = message;
  Debug_Log(a2, a3, a4, (int)(intptr_t)aQueenmessageS);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, a3, a4, (int)(intptr_t)aSetrhS08x_16);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, a4);
  queenSpriteSet = 0;
  loadedSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, 0, a4);
  if ( loadedSpriteSet )
    loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, 0);
  queenSpriteSet = loadedSpriteSet;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)loadedSpriteSet, 0)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)queenSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)queenSpriteSet, 0);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, 0, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = Surface;
  Render_FillRect(0, Surface, 150, (unsigned __int16)panelLeft, panelLeft + SpriteHeight - 1, SpriteWidth + 149, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)queenSpriteSet, 14);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    150,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  portraitSprite = DLX_GetSpriteForChar((int)(intptr_t)queenSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceVtable + 52))(
    168,
    portraitSprite,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(150, panelLeft + 175, panelLeft + 525, 205, 6, messageText);
  Render_Present((int)(intptr_t)g_RenderState);
  while ( !DD_IsFlipping(v11) )
    DD_Pump(v12, 0);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v13, 0, (DWORD)(intptr_t)g_RenderHook, (int)(intptr_t)aUnsetrh08x_16);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, 0x96u);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( backdropSurface )
    (*(void (**)(void))(uintptr_t)backdropSurface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&queenSpriteSet);
  return UI_EndDraw(17);
}
// 4473C0: variable 'v4' is possibly undefined
// 447424: variable 'v7' is possibly undefined
// 447537: variable 'v11' is possibly undefined
// 447544: variable 'v12' is possibly undefined
// 447579: variable 'v13' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00447610) --------------------------------------------------------
int  UI_ShowMissionStatusPanel(int a1, DWORD a2)
{
  int missionIndex; // ecx
  const char *formatString; // esi
  int v5; // ecx
  int result; // eax
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-80h] BYREF
  int statusFormatTable[7]; // [esp+64h] [ebp-1Ch] BYREF

  statusFormatTable[6] = a1;
  statusFormatTable[0] = (int)(intptr_t)g_MissionStatusFormatsByLanguage[0];
  statusFormatTable[1] = (int)(intptr_t)g_MissionStatusFormatsByLanguage[1];
  statusFormatTable[2] = (int)(intptr_t)g_MissionStatusFormatsByLanguage[2];
  missionIndex = ACTIVE_MISSION_INDEX;
  if ( missionIndex != -1 )
  {
    formatString = (const char *)(uintptr_t)statusFormatTable[(unsigned __int8)g_LanguageIndex];
    sprintf_(
      messageBuffer,
      formatString,
      ACTIVE_MISSION_INDEX % 10 + 1,
      (&g_MissionStatusTextsByLanguage[3 * missionIndex])[(unsigned __int8)g_LanguageIndex]);
    return UI_ShowInfoWindow((const char *)messageBuffer, 2u, v5, a2, (int)(intptr_t)&statusFormatTable[3], (int)(intptr_t)formatString);
  }
  return result;
}
// 44768C: variable 'v5' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 5180C0: using guessed type char *g_MissionStatusTextsByLanguage[63];
// 5181B0: using guessed type char *g_MissionStatusFormatsByLanguage[3];
// 5202E4: using guessed type int gameData;

//----- (004476B0) --------------------------------------------------------
int Debug_GetUsedMemoryCount(void)
{
  return 0;
}

//----- (004476C0) --------------------------------------------------------
int __thiscall Object_ConstructInt256Array(void *this)
{
  return _wcpp_4_ctor_array__(this, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (004476E0) --------------------------------------------------------
int  MainMenu_RequestExit(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_PlayGameMenuExitRequested = 1;
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_EXIT;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (004476D0) --------------------------------------------------------
CLASH95_TEST_VISIBLE void MainMenu_WriteButtonWidgetTemplateRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *sound_name)
{
  memset(record, 0, 53);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  record[8] = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_PlayGameMenuSpriteSetHandle;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionFast;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

CLASH95_TEST_VISIBLE void CampaignMenu_WriteButtonWidgetTemplateRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *sound_name)
{
  MainMenu_WriteButtonWidgetTemplateRecord(
    record,
    left,
    top,
    sprite_index_base,
    sprite_index_selected_base,
    action_callback,
    sound_name);
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
}

//----- (004476D0) --------------------------------------------------------
void MainMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aMainMenuButtonClickSound[] = "menduze";

  /*
   * The original PE stores the top-level button table as a 0x35-byte record
   * blob at `unk_5181C0`. Rebuild it with live symbol addresses so the
   * recovered runtime sees the real menu layout instead of a one-byte stub.
   */
  memset(g_MainMenuButtonWidgetsTemplate, 0, sizeof(g_MainMenuButtonWidgetsTemplate));
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 0,
    159,
    136,
    0,
    3,
    (int)(uintptr_t)&MainMenu_RequestLoadGameMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 1,
    152,
    168,
    6,
    9,
    (int)(uintptr_t)&MainMenu_RequestCampaignMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 2,
    185,
    204,
    12,
    15,
    (int)(uintptr_t)&MainMenu_RequestExit,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 3,
    357,
    136,
    18,
    21,
    (int)(uintptr_t)&MainMenu_RequestOptionsMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 4,
    344,
    168,
    24,
    27,
    (int)(uintptr_t)&MainMenu_RequestMultiplayerMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 5,
    388,
    204,
    30,
    33,
    (int)(uintptr_t)&MainMenu_RequestCreditsCinematic,
    aMainMenuButtonClickSound);
  *(_DWORD *)(g_MainMenuButtonWidgetsTemplate + 53 * 6) = -1;
}

void CampaignMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aCampaignMenuButtonClickSound[] = "menduze";

  /*
   * `unk_518338` is the original campaign choice blob: two 0x35-byte
   * button records plus a 0x35-byte terminator slot whose first dword is
   * `-1`. Rebuild it with live callback addresses and the slower
   * `sub_419770` transition used by asm.
   */
  memset(g_CampaignMenuButtonWidgetsTemplate, 0, sizeof(g_CampaignMenuButtonWidgetsTemplate));
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_CampaignMenuButtonWidgetsTemplate + 53 * 0,
    152,
    279,
    0,
    1,
    (int)(uintptr_t)&MultiplayerSetup_HandleConfirmButtonRelease,
    aCampaignMenuButtonClickSound);
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_CampaignMenuButtonWidgetsTemplate + 53 * 1,
    384,
    279,
    2,
    3,
    (int)(uintptr_t)&MultiplayerSetup_HandleCancelButtonRelease,
    aCampaignMenuButtonClickSound);
  *(_DWORD *)(g_CampaignMenuButtonWidgetsTemplate + 53 * 2) = -1;
}

void LoadMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aLoadMenuButtonClickSound[] = "menmale";

  /*
   * The original PE stores the load-menu button table as a 0x35-byte record
   * blob at `unk_518808`. Rebuild it with live symbol addresses so the
   * recovered runtime no longer depends on the weak-data stub on this path.
   */
  memset(g_LoadMenuButtonWidgetsTemplate, 0, sizeof(g_LoadMenuButtonWidgetsTemplate));
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_LoadMenuButtonWidgetsTemplate + 53 * 0,
    249,
    392,
    0,
    1,
    (int)(uintptr_t)&LoadMenu_HandleSlotConfirmButtonRelease,
    aLoadMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_LoadMenuButtonWidgetsTemplate + 53 * 1,
    329,
    408,
    2,
    3,
    (int)(uintptr_t)&MultiplayerSetup_HandleBackButtonRelease,
    aLoadMenuButtonClickSound);
  *(_DWORD *)(g_LoadMenuButtonWidgetsTemplate + 53 * 2) = -1;
}

CLASH95_TEST_VISIBLE void Options_WriteSliderThumbRecord(
        unsigned char *record,
        int track_min,
        int track_max,
        int track_cross,
        int value,
        int draw_arg,
        int apply_callback)
{
  memset(record, 0, 36);
  *(_DWORD *)(record + 0) = track_min;
  *(_DWORD *)(record + 4) = track_max;
  *(_DWORD *)(record + 8) = track_cross;
  *(_DWORD *)(record + 12) = value;
  *(_DWORD *)(record + 16) = draw_arg;
  *(_DWORD *)(record + 20) = (int)(uintptr_t)&g_PlayGameMenuSpriteSetHandle;
  *(_DWORD *)(record + 24) = 28;
  *(_DWORD *)(record + 28) = apply_callback;
  *(_DWORD *)(record + 32) = 0;
}

void Options_RebuildMainMenuWidgetTemplates(void)
{
  static const char aOptionsMenuButtonClickSound[] = "menmale";

  /*
   * The original PE stores the options-menu widget table as a 0x35-byte
   * record blob at `unk_518690` (4 checkboxes, OK, reset, -1 terminator) and
   * the three option slider records as 36-byte entries at `word_518600`.
   * Rebuild both with live symbol addresses so the recovered runtime sees
   * the real layout instead of the one-byte weak-data stubs (same
   * convention as MainMenu/CampaignMenu/LoadMenu_RebuildButtonWidgetTemplate).
   * Field values decoded from the original image (see the blob dumps in the
   * repo history): checkboxes at x=180 y=246/280/312/344 with sprite pairs
   * (3,0)/(9,6)/(15,12)/(21,18) and the slow icon transition; OK at
   * (248,392) sprites (24,25); reset at (329,408) sprites (26,27).
   */
  memset(g_OptionsMenuWidgetTemplateBlob, 0, sizeof(g_OptionsMenuWidgetTemplateBlob));
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 0,
    180,
    246,
    3,
    0,
    (int)(uintptr_t)&Options_ToggleCheckboxMainMenu,
    aOptionsMenuButtonClickSound);
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 1,
    180,
    280,
    9,
    6,
    (int)(uintptr_t)&Options_ToggleCheckboxMainMenu,
    aOptionsMenuButtonClickSound);
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 2,
    180,
    312,
    15,
    12,
    (int)(uintptr_t)&Options_ToggleCheckboxMainMenu,
    aOptionsMenuButtonClickSound);
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 3,
    180,
    344,
    21,
    18,
    (int)(uintptr_t)&Options_ToggleCheckboxMainMenu,
    aOptionsMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 4,
    248,
    392,
    24,
    25,
    (int)(uintptr_t)&PlayGameMenu_HandleCloseButton,
    aOptionsMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_OptionsMenuWidgetTemplateBlob + 53 * 5,
    329,
    408,
    26,
    27,
    (int)(uintptr_t)&Options_InitMainMenuSlidersAndWidgets,
    aOptionsMenuButtonClickSound);
  *(_DWORD *)(void *)(g_OptionsMenuWidgetTemplateBlob + 53 * 6) = -1;

  /*
   * Slider records (original values: min=323 max=473, cross rows 140/166/192,
   * value 128, draw args 4/-1/-1, sprite char 28, sprite-set holder
   * `dword_543D74`, apply callback only on the first record). The value
   * fields at +12/+48/+84 are the storage behind the recovered
   * g_Options_*SliderValue names and are refreshed from the saved config on
   * every options-screen entry.
   */
  Options_WriteSliderThumbRecord(
    (unsigned char *)g_OptionsMenuSliderThumbPositions + 36 * 0,
    323,
    473,
    140,
    128,
    4,
    (int)(uintptr_t)&Options_ApplyMainMenuSliders);
  Options_WriteSliderThumbRecord((unsigned char *)g_OptionsMenuSliderThumbPositions + 36 * 1, 323, 473, 166, 128, -1, 0);
  Options_WriteSliderThumbRecord((unsigned char *)g_OptionsMenuSliderThumbPositions + 36 * 2, 323, 473, 192, 128, -1, 0);
  *(_DWORD *)(void *)&g_OptionsMenuSliderThumbPositions[108] = -1;
}

//----- (00447700) --------------------------------------------------------
int  MainMenu_RequestCampaignMenu(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_CAMPAIGN;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447720) --------------------------------------------------------
int  MainMenu_RequestMultiplayerMenu(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_MULTIPLAYER;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447740) --------------------------------------------------------
int  MainMenu_RequestCreditsCinematic(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_CREDITS;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447760) --------------------------------------------------------
int  MainMenu_RequestOptionsMenu(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_OPTIONS;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447780) --------------------------------------------------------
int  MainMenu_RequestLoadGameMenu(uintptr_t widget)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_LOAD_GAME;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (004477A0) --------------------------------------------------------
signed int  UI_WaitForKeyOrTimeout(int timeoutMs, int a2)
{
  (void)a2;
  return UI_WaitForAnyKeyOrClick(Time_Now(0, 0) + timeoutMs, 0);
}

//----- (004477C0) --------------------------------------------------------
signed int  UI_WaitForAnyKeyOrClick(int deadlineTime, int a2)
{
  unsigned int deadline;

  (void)a2;
  deadline = (unsigned int)deadlineTime;
  Time_Now(0, 0);
  do
  {
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    if ( Input_IsKeyPressed(1)
      || Input_IsKeyPressed(57)
      || Input_IsKeyPressed(28)
      || DD_IsFlipping((int)(intptr_t)g_RenderState)
      || DD_IsLost((int)(intptr_t)g_RenderState) )
    {
      return 1;
    }
  }
  while ( (unsigned int)Time_Now(0, 0) <= deadline );
  return 0;
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00447840) --------------------------------------------------------
DWORD  UI_StartAnims(int a1, char a2, DWORD a3)
{
  int (*previous_render_hook)(); // edi
  int previous_resource_handle; // esi

  Debug_Log(a1, a2, a3, (int)(intptr_t)aStartanims);
  previous_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  previous_render_hook = g_RenderHook;
  g_RenderHook = 0;
  Debug_Log(0, 0, a3, (int)(intptr_t)aSetrhS08x_14, aNull, 0);
  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  DD_Pump((int)(intptr_t)g_RenderState, 0);
  Sleep(0x4B0u);
  Video_Avi_playIn(aLogo_0, 0, 1, 0, 1, 0);
  if ( g_LanguageIndex == 2 )
    Video_Avi_playIn(aSoft2000, 0, 1, 0, 1, 0);
  if ( g_LanguageIndex )
  {
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      Video_Avi_playIn(aInt_a_0, 0, 1, 0, 1, 1);
    }
    else if ( g_LanguageIndex == 2 )
    {
      Video_Avi_playIn(aInt_g, 0, 1, 0, 1, 1);
    }
  }
  else
  {
    Video_Avi_playIn(aInt_a, 0, 1, 0, 1, 1);
  }
  DD_Pump((int)(intptr_t)g_RenderState, 0);
  Debug_Log(0, 0, a3, (int)(intptr_t)aUnsetrh08x_14, g_RenderHook);
  g_RenderHook = previous_render_hook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, a3, (int)(intptr_t)aStartanimsEnd);
  return a3;
}
// 511130: using guessed type char g_LanguageIndex;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];
