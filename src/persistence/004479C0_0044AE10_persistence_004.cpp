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
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004479C0) --------------------------------------------------------
int  PlayGame_Dispatch(int a1, signed int a2, char *a3, double a4)
{
  _DWORD *Surface; // eax
  _DWORD *mainMenuSpriteSet; // eax
  int v12; // ecx
  int mainMenuWidgetOffset; // eax
  int v18 CLASH95_UNUSED; // ecx
  char *v19 CLASH95_UNUSED; // edi
  char *v20 CLASH95_UNUSED; // esi
  int mainMenuSecondLabelOffset CLASH95_UNUSED; // ecx
  int v24 CLASH95_UNUSED; // ecx
  _DWORD *campaignSpriteSet; // eax
  bool i; // zf
  int campaign_menu_cancelled_by_escape; // ecx
  int v33; // ecx
  _DWORD *multiplayerSpriteSet; // eax
  int j; // edx
  int selectedMapIndex; // eax
  int v69; // edx
  int v70; // edx
  int v71; // edx
  unsigned int nameLength; // kr08_4
  int v73; // edx
  int v74; // edx
  int v75; // ecx
  int v76; // edx
  const char *nameCharPtr; // edi
  unsigned int nameTailLength; // kr10_4
  int v79; // edx
  int v80; // ecx
  int v81; // edx
  int v82; // ecx
  int editedNameSlot; // eax
  signed int poppedKey; // esi
  unsigned __int16 nameTextWidth; // ax
  int maxNameWidth; // edx
  int v87; // edx
  int newCaretPos; // ecx
  int v89; // edx
  _DWORD *optionsSpriteSet; // eax
  int optionsWidgetOffset; // eax
  DWORD optionsFirstLabelOffset; // ebp
  int optionsSecondLabelOffset; // ecx
  _DWORD *loadMenuSpriteSet; // eax
  int k; // edx
  unsigned int loadSlotRow; // eax
  int ( *defaultRenderHook)(int, char, DWORD); // [esp-4h] [ebp-2140h]
  _BYTE v112[7112] CLASH95_UNUSED; // [esp+4h] [ebp-2138h] BYREF
  /* Options-menu widget table: 4 records x 53 (0x35) bytes, 371 bytes
   * total, filled from g_OptionsMenuWidgetTemplateBlob. In the original
   * stack frame (clash95.asm PlayGame_Dispatch, table = var_570) the
   * decompiler emitted named locals that were ALIASES into this table:
   * var_568 = +0x08 (record-0 checkbox state), var_560 = +0x10 (sprite
   * base), var_55C = +0x14 (selected base), var_533/var_4FE/var_4C9 =
   * +0x3D/+0x72/+0xA7 (+0x08 of records 1..3), var_591 = table-0x21.
   * Rebuilt as independent C locals those reads/writes MISSED the table
   * (language column stuck at Polish column 0, checkbox states unbound),
   * so the table is declared at its real extent and indexed directly
   * (asm: rep movsd x92 + movsw + movsb = 371; add eax,35h; cmp eax,0D4h).
   */
  char optionsWidgetTable[371]; // [esp+1BCCh] [ebp-570h] BYREF
  /*
   * Original frame: v119[8] at ebp-41Dh, mainMenuWidgetTable[16] at
   * ebp-3FCh, v121[89] at ebp-3ECh together held the 371-byte main-menu
   * widget table plus the aliases used by the language-column loop. The
   * rebuild owns the whole table as one array and indexes it directly.
   */
  char mainMenuWidgetTable[371]; // [esp+1D40h] [ebp-3FCh] BYREF
  char multiplayerWidgetTable[268]; // [esp+1EB4h] [ebp-288h] BYREF
  _DWORD loadMenuWidgetTable[40]; // [esp+1FC0h] [ebp-17Ch] BYREF
  char campaignWidgetTable[160]; // [esp+2060h] [ebp-DCh] BYREF
  int rulerNamesTable[5]; // [esp+2100h] [ebp-3Ch] BYREF
  int previous_load_slot;
  int selected_load_slot;
  char multiplayer_player_states[PLAYER_DATA_STRIDE * 5];
  int multiplayer_player_index;
  int multiplayer_player_type;
  char *multiplayer_player_state;
  int multiplayer_player_type_slot;
  int multiplayer_selected_name_slot;
  int multiplayer_previous_name_slot;
  int multiplayer_map_row;
  int previousResourceHandle; // [esp+2114h] [ebp-28h]
  int (*previousRenderHook)(int, char, DWORD); // [esp+2118h] [ebp-24h]
  int needMenuFadeIn; // [esp+211Ch] [ebp-20h]
  char typedChar; // [esp+2120h] [ebp-1Ch]

  Debug_Log(a1, a2, (DWORD)(intptr_t)a3, (int)(intptr_t)aStartmenu);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, 0);
  if ( Surface )
  {
    LOBYTE(a2) = -32;
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  }
  g_PrimaryRenderSurface = (int)(intptr_t)Surface;
  UI_StartAnims(0, a2, (DWORD)(intptr_t)a3);
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  defaultRenderHook = Render_DefaultRH;
  previousRenderHook = g_RenderHook;
  g_RenderHook = Render_DefaultRH;
  Debug_Log(0, 0, (DWORD)(intptr_t)a3, (int)(intptr_t)aSetrhS08x_15, aStdrh_10, Render_DefaultRH);
  DD_Pump((int)(intptr_t)g_RenderState, a2);
  needMenuFadeIn = 1;
  do
  {
    mainMenuSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
    if ( mainMenuSpriteSet )
      mainMenuSpriteSet = DLXSpriteSet_Load(mainMenuSpriteSet, "menu\\main.s32");
    g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)mainMenuSpriteSet;
    Render_LoadPCXImage(g_PrimaryRenderSurface, aMenuMain_gfx, 0, (uintptr_t)g_MenuScreenPaletteBuffer);
    Palette_LoadOrBuildBlendLookupTable(aMenuMain, (int)(intptr_t)g_MenuScreenPaletteBuffer, v12, (DWORD)(intptr_t)a3);
    if ( needMenuFadeIn && g_Options_MusicEnabledFlag )
      g_MainMenuMusicHandle = Sound_PlayNamedSfxFile(aMusicMenu, 64);
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    if ( needMenuFadeIn )
      Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    Debug_Log(0, 0, (DWORD)(intptr_t)a3, (int)(intptr_t)aDraw1);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
    Debug_Log(0, 0, (DWORD)(intptr_t)a3, (int)(intptr_t)aDraw2);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
    Debug_Log(0, 0, (DWORD)(intptr_t)a3, (int)(intptr_t)aDrawend);
    MainMenu_RebuildButtonWidgetTemplate();
    qmemcpy(mainMenuWidgetTable, g_MainMenuButtonWidgetsTemplate, sizeof(g_MainMenuButtonWidgetsTemplate));
    /*
     * The original 004479C0 loop adds g_LanguageIndex to each 0x35-byte
     * widget record's +0x10 (label sprite base) and +0x14 (pressed sprite
     * base) so the PL/EN/DE column of menu\main.s32 is selected. The raw
     * decompile expressed those stores through frame-offset aliases
     * (`v121` = table+0x10, `v119` = table-0x21) that only held for the
     * original stack layout; with compiler-chosen local placement the adds
     * landed outside the table and the menu stayed on the Polish column.
     * Index the widget table directly instead.
     */
    for ( mainMenuWidgetOffset = 0; mainMenuWidgetOffset != 371; mainMenuWidgetOffset += WORLD_MAP_ACTION_WIDGET_RECORD_SIZE )
    {
      *(_DWORD *)(void *)&mainMenuWidgetTable[mainMenuWidgetOffset + 16] += (unsigned __int8)g_LanguageIndex;
      *(_DWORD *)(void *)&mainMenuWidgetTable[mainMenuWidgetOffset + 20] += (unsigned __int8)g_LanguageIndex;
    }
    a2 = (signed int)(intptr_t)&g_MainRenderDevice;
    g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
    UIWidgetTable_InitDrawStates((_DWORD*)(mainMenuWidgetTable));
    if ( needMenuFadeIn )
    {
      a2 = 60;
      Palette_FadeInFromBlack((int *)&g_MainRenderDevice, g_MenuScreenPaletteBuffer, 60);
    }
    g_PlayGameMenuExitRequested = 0;
    RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_MenuScreenPaletteBuffer, 0, 0);
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
    g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
    Render_Present((int)(intptr_t)g_RenderState);
    needMenuFadeIn = 0;
    if ( !g_PlayGameMenuExitRequested )
    {
      a2 = (signed int)(intptr_t)g_RenderState;
      do
      {
        DD_Pump((int)(intptr_t)g_RenderState, 0);
        UIWidgetTable_PollHoverAndActions((_DWORD*)(mainMenuWidgetTable), 0);
      }
      while ( !g_PlayGameMenuExitRequested );
    }
    Render_Pump();
    DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
    switch ( g_MainMenuRequestedScreen )
    {
      case MAIN_MENU_REQUEST_CAMPAIGN:
        campaignSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
        if ( campaignSpriteSet )
          campaignSpriteSet = DLXSpriteSet_Load(campaignSpriteSet, "menu\\kamp.s32");
        g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)campaignSpriteSet;
        RenderSurface_InvokeSlot48LoadPCX(
          (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
          aMenuMain_gfx_0,
          0,
          (uintptr_t)g_MenuScreenPaletteBuffer);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        CampaignMenu_RebuildButtonWidgetTemplate();
        qmemcpy(campaignWidgetTable, g_CampaignMenuButtonWidgetsTemplate, sizeof(g_CampaignMenuButtonWidgetsTemplate));
        g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
        UIWidgetTable_InitDrawStates((_DWORD*)(campaignWidgetTable));
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_MenuScreenPaletteBuffer, 0, 0);
        a3 = (char *)&g_CursorDesc_Default;
        RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
        Render_Present((int)(intptr_t)g_RenderState);
        campaign_menu_cancelled_by_escape = 0;
        for ( i = g_PlayGameMenuExitRequested == 0; i; i = g_PlayGameMenuExitRequested == 0 )
        {
          DD_Pump((int)(intptr_t)g_RenderState, 0);
          UIWidgetTable_PollHoverAndActions((_DWORD*)(campaignWidgetTable), 0);
          if ( Input_IsKeyPressed(1) )
          {
            campaign_menu_cancelled_by_escape = 1;
            g_PlayGameMenuExitRequested = 1;
            break;
          }
        }
        Render_Pump();
        if ( !campaign_menu_cancelled_by_escape )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !campaign_menu_cancelled_by_escape && g_PlayGameMenuSelectedAction != -1 )
        {
          if ( g_PlayGameMenuSelectedAction == 1 )
          {
            LOBYTE(a2) = 1;
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            needMenuFadeIn = 1;
            Scenario_LoadMissionByIndexAndPlay(0, 0, (DWORD)(intptr_t)&g_CursorDesc_Default, a4);
          }
          else
          {
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            Scenario_LoadMissionByIndexAndPlay((char *)0xA, 0, (DWORD)(intptr_t)&g_CursorDesc_Default, a4);
            needMenuFadeIn = 1;
          }
        }
        break;
      case MAIN_MENU_REQUEST_CREDITS:
        CSS_StopSound(g_MainMenuMusicHandle, 1000);
        Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        LOBYTE(a2) = 0;
        Video_Avi_playIn(aCre_an, 0, 1, 0, 1, 1);
        needMenuFadeIn = 1;
        break;
      case MAIN_MENU_REQUEST_MULTIPLAYER:
        memset(g_MultiplayerPlayerSlotTypes, 5, 5);
        g_MultiplayerPlayerSlotTypes[0] = 3;
        g_MultiplayerPlayerSlot1Type = 0;
        g_MultiplayerPlayerSlot3Type = 1;
        g_MultiplayerPlayerSlot2Type = 2;
        qmemcpy(rulerNamesTable, &g_MultiplayerDefaultRulerNamesTable, sizeof(rulerNamesTable));
        Player_AssignRandomUniqueRulerNames(5, rulerNamesTable);
        g_MultiplayerSelectedMapIndex = 0;
        g_MpEditNameSlotIndex = -1;
        g_MultiplayerOpponentListScrollOffset = 0;
        multiplayerSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
        if ( multiplayerSpriteSet )
          multiplayerSpriteSet = DLXSpriteSet_Load(multiplayerSpriteSet, aMenuMultipl_s32);
        g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)multiplayerSpriteSet;
        a2 = (signed int)(intptr_t)g_MenuScreenPaletteBuffer;
        RenderSurface_InvokeSlot48LoadPCX(
          (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
          aMenuMultipl_gf,
          0,
          (uintptr_t)g_MenuScreenPaletteBuffer);
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
        MultiplayerSetup_RedrawPlayerSlotIcons();
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        for ( j = 0; j < 5; ++j )
          MultiplayerSetup_RepaintPlayerSlotRow(j, j + 1, 0);
        MultiplayerSetup_RedrawOpponentNameList();
        qmemcpy(multiplayerWidgetTable, &g_MultiplayerSetupWidgetTemplateBlob, 265);
        g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
        UIWidgetTable_InitDrawStates((_DWORD*)(multiplayerWidgetTable));
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
        Render_Present((int)(intptr_t)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)(intptr_t)g_RenderState, 0);
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState)
            && g_MouseCursorRawX >> g_CursorCoordShift >= 176
            && g_MouseCursorRawX >> g_CursorCoordShift <= 236
            && (unsigned int)(((g_MouseCursorRawY >> g_CursorCoordShift) - 129) / 53) <= 4 )
          {
            multiplayer_player_type_slot = ((g_MouseCursorRawY >> g_CursorCoordShift) - 129) / 53;
            Audio_PlayButtonSound(aMale_2);
            g_MultiplayerPlayerSlotTypes[multiplayer_player_type_slot] = ((unsigned __int8)g_MultiplayerPlayerSlotTypes[multiplayer_player_type_slot] + 1) % 6;
            MultiplayerSetup_RedrawPlayerSlotIcons();
            MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_player_type_slot, 0, 0);
            Render_Begin((int)(intptr_t)g_RenderState, 0);
          }
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 239 && g_MouseCursorRawX >> g_CursorCoordShift <= 339 )
            {
              multiplayer_selected_name_slot = ((g_MouseCursorRawY >> g_CursorCoordShift) - 144) / 53;
              if ( multiplayer_selected_name_slot <= 4 )
              {
                multiplayer_previous_name_slot = g_MpEditNameSlotIndex;
                if ( multiplayer_selected_name_slot != g_MpEditNameSlotIndex )
                {
                  g_MpEditNameSlotIndex = multiplayer_selected_name_slot;
                  g_PlayerNameEditCaretPos = 0;
                  if ( multiplayer_previous_name_slot != -1 )
                    MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_previous_name_slot, 0, 0);
                  MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, 0, 0);
                }
              }
            }
          }
          if ( g_MpEditNameSlotIndex != -1 )
          {
            if ( Input_IsKeyPressed(203) )
            {
              v69 = g_PlayerNameEditCaretPos;
              if ( g_PlayerNameEditCaretPos )
              {
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v69, --g_PlayerNameEditCaretPos);
                Input_ClearKey(203, v70);
              }
            }
            if ( Input_IsKeyPressed(205) )
            {
              nameLength = strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex])) + 1;
              if ( nameLength - 1 > g_PlayerNameEditCaretPos )
              {
                ++g_PlayerNameEditCaretPos;
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v71, nameLength - 1);
                Input_ClearKey(205, v73);
              }
            }
            if ( Input_IsKeyPressed(211) )
            {
              LOBYTE(a2) = strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + 1 + g_PlayerNameEditCaretPos])) + 1;
              memmove_(
                &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1])) + 1);
              MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v74, v75);
              Input_ClearKey(211, v76);
            }
            if ( Input_IsKeyPressed(14) )
            {
              LOBYTE(a2) = g_PlayerNameEditCaretPos;
              if ( g_PlayerNameEditCaretPos )
              {
                nameCharPtr = (const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos--]);
                nameTailLength = strlen(nameCharPtr) + 1;
                a3 = (char *)(uintptr_t)g_PlayerNameEditCaretPos;
                LOBYTE(a2) = nameTailLength;
                memmove_(
                  &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                  &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                  nameTailLength);
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v79, v80);
                Input_ClearKey(14, v81);
              }
            }
            if ( Input_IsKeyPressed(28) )
            {
              editedNameSlot = g_MpEditNameSlotIndex;
              g_MpEditNameSlotIndex = -1;
              MultiplayerSetup_RepaintPlayerSlotRow(editedNameSlot, -1, v82);
            }
            poppedKey = Input_PopKey();
            Render_ReleaseSurface(18, 0);
            if ( poppedKey != -1 )
            {
              typedChar = Input_KeyToChar(poppedKey);
              if ( typedChar )
              {
                if ( strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex])) < 0xA )
                {
                  Render_LoadResourceSprite_v3((_BYTE*)(aW));
                  LOBYTE(a2) = g_MpEditNameSlotIndex;
                  nameTextWidth = Render_LoadResourceSprite_v3(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex]);
                  if ( nameTextWidth < maxNameWidth )
                  {
                    LOBYTE(a2) = strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos])) + 1;
                    memmove_(
                      &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                      &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                      strlen((const char*)(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos])) + 1);
                    v87 = 11 * g_MpEditNameSlotIndex;
                    newCaretPos = g_PlayerNameEditCaretPos + 1;
                    LOBYTE(v87) = typedChar;
                    g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos] = typedChar;
                    g_PlayerNameEditCaretPos = newCaretPos;
                    MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v87, newCaretPos);
                    Input_ClearKey(poppedKey, v89);
                  }
                }
              }
            }
          }
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 356 && g_MouseCursorRawX >> g_CursorCoordShift <= 477 )
            {
              multiplayer_map_row = ((g_MouseCursorRawY >> g_CursorCoordShift) - 134) / 22;
              if ( multiplayer_map_row <= 0xA )
              {
                LOBYTE(a2) = g_MultiplayerOpponentListScrollOffset;
                selectedMapIndex = g_MultiplayerOpponentListScrollOffset + multiplayer_map_row;
                if ( selectedMapIndex != g_MultiplayerSelectedMapIndex )
                {
                  g_MultiplayerSelectedMapIndex = selectedMapIndex;
                  Audio_PlayButtonSound(aMale_1);
                  MultiplayerSetup_RedrawOpponentNameList();
                  Render_Begin((int)(intptr_t)g_RenderState, 0);
                }
              }
            }
          }
          UIWidgetTable_PollHoverAndActions((_DWORD*)(multiplayerWidgetTable), 0);
        }
        Render_Pump();
        if ( g_PlayGameMenuLaunchGameFlag )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        needMenuFadeIn = g_PlayGameMenuLaunchGameFlag;
        if ( g_PlayGameMenuLaunchGameFlag )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize(0, (DWORD)(intptr_t)a3);
          for ( multiplayer_player_index = 0; multiplayer_player_index < 5; ++multiplayer_player_index )
          {
            multiplayer_player_state = &multiplayer_player_states[PLAYER_DATA_STRIDE * multiplayer_player_index];
            PlayerRuntimeState_ResetDefaults((uintptr_t)multiplayer_player_state);
            *(_DWORD *)multiplayer_player_state = 1;
            multiplayer_player_type = (unsigned __int8)g_MultiplayerPlayerSlotTypes[multiplayer_player_index];
            switch ( multiplayer_player_type )
            {
              case MP_PLAYER_SLOT_AI_EASY:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = PLAYER_AI_INTELLIGENCE_EASY;
                break;
              case MP_PLAYER_SLOT_AI_NORMAL:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = PLAYER_AI_INTELLIGENCE_NORMAL;
                break;
              case MP_PLAYER_SLOT_AI_HARD:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = PLAYER_AI_INTELLIGENCE_HARD;
                break;
              case MP_PLAYER_SLOT_HUMAN_RELIGIOUS:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_MINIMAP_VISIBLE_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_RELIGION_FLAG_OFFSET) = 1;
                break;
              case MP_PLAYER_SLOT_HUMAN_SECULAR:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_MINIMAP_VISIBLE_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_RELIGION_FLAG_OFFSET) = 0;
                break;
              case MP_PLAYER_SLOT_CLOSED:
                *(_DWORD *)multiplayer_player_state = 0;
                break;
              default:
                break;
            }
            strcpy(multiplayer_player_state + PLAYER_DISPLAY_NAME_OFFSET, (const char*)(&g_MultiplayerPlayerNameEditTable[11 * multiplayer_player_index]));
          }
          Scenario_LoadMultiplayerMapAndSeedPlayers(g_MultiplayerSelectedMapIndex, (uintptr_t)multiplayer_player_states);
          PlayGame(0, 0, (DWORD)(intptr_t)a3, 0, a4);
        }
        break;
      case MAIN_MENU_REQUEST_OPTIONS:
        optionsSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
        if ( optionsSpriteSet )
          optionsSpriteSet = DLXSpriteSet_Load(optionsSpriteSet, aMenuOpt_s32);
        g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)optionsSpriteSet;
        if ( g_LanguageIndex )
        {
          if ( (unsigned __int8)g_LanguageIndex <= 1u )
          {
            a2 = (signed int)(intptr_t)g_MenuScreenPaletteBuffer;
            RenderSurface_InvokeSlot48LoadPCX(
              (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
              aMenuOpt_a_gfx,
              0,
              (uintptr_t)g_MenuScreenPaletteBuffer);
          }
          else if ( g_LanguageIndex == 2 )
          {
            a2 = (signed int)(intptr_t)g_MenuScreenPaletteBuffer;
            RenderSurface_InvokeSlot48LoadPCX(
              (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
              aMenuOpt_g_gfx,
              0,
              (uintptr_t)g_MenuScreenPaletteBuffer);
          }
        }
        else
        {
          a2 = (signed int)(intptr_t)g_MenuScreenPaletteBuffer;
          RenderSurface_InvokeSlot48LoadPCX(
            (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
            aMenuOpt_p_gfx,
            0,
            (uintptr_t)g_MenuScreenPaletteBuffer);
        }
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        optionsWidgetOffset = 0;
        Options_RebuildMainMenuWidgetTemplates();
        qmemcpy(optionsWidgetTable, &g_OptionsMenuWidgetTemplateBlob, 371);
        do
        {
          optionsFirstLabelOffset = (unsigned __int8)g_LanguageIndex + *(_DWORD *)&optionsWidgetTable[optionsWidgetOffset + 0x10];
          *(_DWORD *)&optionsWidgetTable[optionsWidgetOffset + 0x10] = optionsFirstLabelOffset;
          optionsSecondLabelOffset = *(_DWORD *)&optionsWidgetTable[optionsWidgetOffset + 0x14];
          optionsWidgetOffset += WORLD_MAP_ACTION_WIDGET_RECORD_SIZE;
          *(_DWORD *)&optionsWidgetTable[optionsWidgetOffset - 0x21] = (unsigned __int8)g_LanguageIndex + optionsSecondLabelOffset;
        }
        while ( optionsWidgetOffset != 212 );
        if ( g_OptionsConfigRecordFlag0C )
          *(_DWORD *)&optionsWidgetTable[0x08] = 2;
        if ( g_OptionsConfigRecordBase )
          *(_DWORD *)&optionsWidgetTable[0x3D] = 2;
        if ( g_Options_MusicEnabledFlag )
          *(_DWORD *)&optionsWidgetTable[0x72] = 2;
        if ( g_Options_UnitSoundsEnabledFlag )
          *(_DWORD *)&optionsWidgetTable[0xA7] = 2;
        g_Options_BrightnessSliderValue = ((g_OptionsMainMenuMusicVolumeRaw << 8)
                      + 0x4000
                      - (__CFSHL__(((g_OptionsMainMenuMusicVolumeRaw << 8) + 0x4000) >> 31, 7)
                       + (((g_OptionsMainMenuMusicVolumeRaw << 8) + 0x4000) >> 31 << 7))) >> 7;
        g_Options_ScrollSpeedSliderValue = (((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8)
                      - (__CFSHL__((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8 >> 31, 4)
                       + 16 * ((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8 >> 31))) >> 4;
        g_Options_MouseSpeedSliderValue = (((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8)
                      - (__CFSHL__((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8 >> 31, 4)
                       + 16 * ((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8 >> 31))) >> 4;
        g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
        UIWidgetTable_InitDrawStates((_DWORD*)(optionsWidgetTable));
        Options_DrawAllSliderThumbs((unsigned __int16 *)g_OptionsMenuSliderThumbPositions, a2, optionsFirstLabelOffset);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
        Render_Present((int)(intptr_t)g_RenderState);
        if ( !g_PlayGameMenuExitRequested )
        {
          do
          {
            DD_Pump((int)(intptr_t)g_RenderState, 0);
            Options_AnimateAllSliderThumbs((_DWORD *)g_OptionsMenuSliderThumbPositions);
            UIWidgetTable_PollHoverAndActions((_DWORD*)(optionsWidgetTable), 0);
          }
          while ( !g_PlayGameMenuExitRequested );
        }
        a2 = g_Options_MusicEnabledFlag;
        g_OptionsConfigRecordFlag0C = *(_DWORD *)&optionsWidgetTable[0x08] == 2;
        g_OptionsConfigRecordBase = *(_DWORD *)&optionsWidgetTable[0x3D] == 2;
        g_Options_MusicEnabledFlag = *(_DWORD *)&optionsWidgetTable[0x72] == 2;
        g_Options_UnitSoundsEnabledFlag = *(_DWORD *)&optionsWidgetTable[0xA7] == 2;
        g_OptionsMainMenuMusicVolumeRaw = ((unsigned __int16)(((_WORD)g_Options_BrightnessSliderValue << 7)
                                        - (__CFSHL__(g_Options_BrightnessSliderValue << 7 >> 31, 8)
                                         + ((__int16)((unsigned int)g_Options_BrightnessSliderValue >> 9) >> 15 << 8))) >> 8)
                    - 64;
        g_OptionsMainMenuScrollSpeedRaw = (unsigned __int16)(16 * g_Options_ScrollSpeedSliderValue
                                       - (__CFSHL__((16 * g_Options_ScrollSpeedSliderValue) >> 31, 8)
                                        + ((__int16)((unsigned int)g_Options_ScrollSpeedSliderValue >> 12) >> 15 << 8))) >> 8;
        g_OptionsMainMenuSoundVolumeRaw = (unsigned __int16)(16 * g_Options_MouseSpeedSliderValue
                                       - (__CFSHL__((16 * g_Options_MouseSpeedSliderValue) >> 31, 8)
                                        + ((__int16)((unsigned int)g_Options_MouseSpeedSliderValue >> 12) >> 15 << 8))) >> 8;
        if ( *(_DWORD *)&optionsWidgetTable[0x72] == 2 )
        {
          Audio_SetMusicActiveFlag();
          if ( !a2 )
            g_MainMenuMusicHandle = Sound_PlayNamedSfxFile(aMusicMenu_0, 64);
        }
        else
        {
          if ( a2 )
            Audio_StopMusicWithFade(g_MainMenuMusicHandle);
          Audio_ClearMusicActiveFlag();
        }
        Options_ApplyRecordSettings((int)(intptr_t)&g_OptionsConfigRecordBase, 0, 0);
        Options_SaveConfigToFile(0, 0);
        Options_DestroySliderThumbList((_DWORD *)g_OptionsMenuSliderThumbPositions);
        Render_Pump();
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        break;
      case MAIN_MENU_REQUEST_LOAD_GAME:
        g_LoadMenuSelectedSlotIndex = -1;
        loadMenuSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
        if ( loadMenuSpriteSet )
          loadMenuSpriteSet = DLXSpriteSet_Load(loadMenuSpriteSet, aMenuLoad_s32);
        g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)loadMenuSpriteSet;
        RenderSurface_InvokeSlot48LoadPCX(
          (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
          aMenuLoad_gfx,
          0,
          (uintptr_t)g_MenuScreenPaletteBuffer);
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        for ( k = 0; k < 10; ++k )
          LoadMenu_RedrawSaveSlotRow(k, (DWORD)(intptr_t)a3);
        LoadMenu_RebuildButtonWidgetTemplate();
        qmemcpy(loadMenuWidgetTable, &g_LoadMenuButtonWidgetsTemplate, 0x9Fu);
        g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
        UIWidgetTable_InitDrawStates(loadMenuWidgetTable);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)(intptr_t)g_RenderState, (int)(intptr_t)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
        Render_Present((int)(intptr_t)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)(intptr_t)g_RenderState, 0);
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 244 && g_MouseCursorRawX >> g_CursorCoordShift <= 410 )
            {
              loadSlotRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 155) / 22;
              if ( loadSlotRow <= 9 )
              {
                previous_load_slot = g_LoadMenuSelectedSlotIndex;
                if ( loadSlotRow != g_LoadMenuSelectedSlotIndex )
                {
                  g_LoadMenuSelectedSlotIndex = ((g_MouseCursorRawY >> g_CursorCoordShift) - 155) / 22;
                  if ( previous_load_slot != -1 )
                    LoadMenu_RedrawSaveSlotRow(previous_load_slot, (DWORD)(intptr_t)a3);
                  LoadMenu_RedrawSaveSlotRow(g_LoadMenuSelectedSlotIndex, (DWORD)(intptr_t)a3);
                }
                if ( RenderState_IsCursorFlipStillActive((int)(intptr_t)g_RenderState) )
                  LoadMenu_HandleSlotConfirmButtonRelease(0, (DWORD)(intptr_t)a3);
              }
            }
          }
          UIWidgetTable_PollHoverAndActions(loadMenuWidgetTable, 0);
        }
        Render_Pump();
        if ( g_PlayGameMenuLaunchGameFlag )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !g_PlayGameMenuLaunchGameFlag )
          g_LoadMenuSelectedSlotIndex = -1;
        selected_load_slot = g_LoadMenuSelectedSlotIndex;
        if ( selected_load_slot != -1 )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize((char)selected_load_slot, (DWORD)(intptr_t)a3);
          needMenuFadeIn = 1;
          SaveSlot_LoadGame(selected_load_slot, (DWORD)(intptr_t)a3, a4);
          PlayGame(0, (char)selected_load_slot, (DWORD)(intptr_t)a3, 1, a4);
        }
        break;
      default:
        break;
    }
  }
  while ( g_MainMenuRequestedScreen );
  CSS_StopSound(g_MainMenuMusicHandle, 1000);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_UnlockBackbuffer((int)(intptr_t)&g_MainRenderDevice);
  HIBYTE(defaultRenderHook) = HIBYTE(g_RenderHook);
  Debug_Log(v33, a2, (DWORD)(intptr_t)g_RenderHook, (int)(intptr_t)aUnsetrh08x_15);
  g_RenderHook = previousRenderHook;
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
}
// 44806D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 4480F9: simplified comparisons for 'eax.4': <0 || >=B became >=Bu
// 448AAB: simplified comparisons for 'eax.4': <0 || >=A became >=Au
// 44824F: simplified comparisons for '((($dword_544D00.4 >>a $byte_54512C.1)-#0x81.4) /s #0x35.4)': <0 || >=5 became >=5u
// 4479DE: variable 'v5' is possibly undefined
// 4479F0: variable 'v7' is possibly undefined
// 447A39: variable 'v8' is possibly undefined
// 447A50: variable 'v9' is possibly undefined
// 447A9F: variable 'v12' is possibly undefined
// 447AF1: variable 'v14' is possibly undefined
// 447B0C: variable 'v15' is possibly undefined
// 447B38: variable 'v16' is possibly undefined
// 447B42: variable 'v18' is possibly undefined
// 447BC9: variable 'v23' is possibly undefined
// 447C24: variable 'v24' is possibly undefined
// 447DA4: variable 'v33' is possibly undefined
// 4482D9: variable 'v70' is possibly undefined
// 44831B: variable 'v71' is possibly undefined
// 448325: variable 'v73' is possibly undefined
// 448381: variable 'v74' is possibly undefined
// 448381: variable 'v75' is possibly undefined
// 44838B: variable 'v76' is possibly undefined
// 4483F4: variable 'v79' is possibly undefined
// 4483F4: variable 'v80' is possibly undefined
// 4483FE: variable 'v81' is possibly undefined
// 448421: variable 'v82' is possibly undefined
// 4484B1: variable 'v86' is possibly undefined
// 44852A: variable 'v89' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5184DC: using guessed type char *off_5184DC;
// 518600: using guessed type unsigned __int16 word_518600[6];
// 51860C: using guessed type int dword_51860C;
// 518630: using guessed type int dword_518630;
// 518654: using guessed type int dword_518654;
// 5188B0: using guessed type int dword_5188B0;
// 5188BC: using guessed type int dword_5188BC;
// 5188C0: using guessed type int dword_5188C0;
// 5188C4: using guessed type int dword_5188C4;
// 5188C8: using guessed type char byte_5188C8;
// 5188C9: using guessed type char byte_5188C9;
// 5188CA: using guessed type char byte_5188CA;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D74: using guessed type int g_PlayGameMenuSpriteSetHandle;
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;
// 543D80: using guessed type unsigned __int8 byte_543D80[1024];
// 544180: using guessed type int g_MainMenuMusicHandle;
// 544184: using guessed type int dword_544184;
// 544189: using guessed type char byte_544189;
// 54418A: using guessed type char byte_54418A;
// 54418B: using guessed type char byte_54418B;
// 544190: using guessed type int dword_544190;
// 544194: using guessed type int dword_544194;
// 544198: using guessed type int dword_544198;
// 5441A0: using guessed type _BYTE byte_5441A0[11];
// 5441D8: using guessed type int dword_5441D8;
// 5441DC: using guessed type int dword_5441DC;
// 5441E0: using guessed type int dword_5441E0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00448B90) --------------------------------------------------------
int  MultiplayerSetup_HandleConfirmButtonRelease(uintptr_t widgetRecord)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuSelectedAction = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544184: using guessed type int dword_544184;

//----- (00448BB0) --------------------------------------------------------
int  MultiplayerSetup_HandleCancelButtonRelease(uintptr_t widgetRecord)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuSelectedAction = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544184: using guessed type int dword_544184;

//----- (00448D10) --------------------------------------------------------
int  MultiplayerSetup_RepaintPlayerSlotRow(int slotRow, int a2, int a3)
{
  __int16 rowBaseY; // di
  DWORD rowBottomY; // ebp
  int rowTopY; // edi
  int slotType; // eax
  int result; // eax
  unsigned __int16 rowBottomY16; // [esp-4h] [ebp-20h]
  int cursorOverlayPresented; // [esp+0h] [ebp-1Ch]

  rowBaseY = 53 * slotRow;
  Str_TitleCase(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex], a2, a3);
  cursorOverlayPresented = g_CursorOverlayPresented;
  rowBottomY = (unsigned __int16)(rowBaseY + 167);
  rowBottomY16 = rowBaseY + 167;
  rowTopY = (unsigned __int16)(rowBaseY + 144);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xEFu, 0x153u, rowTopY, rowBottomY16);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, rowTopY, 234, 0x15Du, rowBottomY, 0xEAu, rowTopY);
  Render_ReleaseSurface(18, rowBottomY);
  if ( slotRow == g_MpEditNameSlotIndex )
    UI_SetTextCursorPosition(g_PlayerNameEditCaretPos);
  slotType = (unsigned __int8)g_MultiplayerPlayerSlotTypes[slotRow];
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  if ( slotType != 5 )
    UI_DrawTextFmt(rowTopY, 239, 339, 53 * slotRow + 144, 3, (const char*)(intptr_t)((int)(intptr_t)&g_MultiplayerPlayerNameEditTable[11 * slotRow]));
  result = UI_SetTextCursorPosition(-1);
  if ( cursorOverlayPresented )
    return Render_Present((int)(intptr_t)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 544194: using guessed type int dword_544194;
// 544198: using guessed type int dword_544198;
// 5441A0: using guessed type _BYTE byte_5441A0[11];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00448E10) --------------------------------------------------------
signed int  MultiplayerSetup_HandleStartButtonRelease(int widgetRecord)
{
  signed int result; // eax
  int slotType; // edx
  int activePlayerCount; // edx

  UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  for ( result = 0; result < 5; ++result )
  {
    slotType = (unsigned __int8)g_MultiplayerPlayerSlotTypes[result];
    if ( slotType == 3 )
      break;
    if ( slotType == 4 )
      break;
  }
  if ( result != 5 )
  {
    activePlayerCount = 0;
    for ( result = 0; result < 5; ++result )
    {
      if ( g_MultiplayerPlayerSlotTypes[result] != 5 )
        ++activePlayerCount;
    }
    if ( activePlayerCount > 1 && g_MultiplayerSelectedMapIndex != -1 )
    {
      g_PlayGameMenuLaunchGameFlag = 1;
      g_PlayGameMenuExitRequested = 1;
    }
  }
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;
// 5441D8: using guessed type int dword_5441D8;

//----- (00448E80) --------------------------------------------------------
int  MultiplayerSetup_HandleBackButtonRelease(int widgetRecord)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuLaunchGameFlag = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;

//----- (00448EA0) --------------------------------------------------------
int MultiplayerSetup_RedrawPlayerSlotIcons(void)
{
  int iconLeftX; // edi
  int slotIndex; // esi
  int SpriteForChar; // eax
  int iconX; // ecx
  int result; // eax
  int cursorOverlayPresented; // [esp+1Ch] [ebp-1Ch]

  iconLeftX = 129;
  cursorOverlayPresented = g_CursorOverlayPresented;
  slotIndex = 0;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xB0u, 0xECu, 0x81u, 0x18Au);
  do
  {
    SpriteForChar = DLX_GetSpriteForChar(g_PlayGameMenuSpriteSetHandle, (unsigned __int8)g_MultiplayerPlayerSlotTypes[slotIndex] + 8);
    iconX = iconLeftX;
    ++slotIndex;
    iconLeftX += 53;
    result = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46)
                                                                                      + 52))(
               iconX,
               SpriteForChar,
               -1,
               -1,
               -1,
               -1,
               1,
               0,
               0);
  }
  while ( slotIndex < 5 );
  if ( cursorOverlayPresented )
    return Render_Present((int)(intptr_t)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 543D74: using guessed type int g_PlayGameMenuSpriteSetHandle;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00449330) --------------------------------------------------------
int MultiplayerSetup_RedrawOpponentNameList(void)
{
  DWORD cursorOverlayPresented; // ebp
  int rowTopY; // edi
  int rowIndex; // esi
  int result; // eax
  int rowSpriteId; // eax

  cursorOverlayPresented = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
    RenderState_PumpIfRectInViewBounds(g_RenderState, 0x164u, 0x1DDu, 0x86u, 0x175u);
  rowTopY = 134;
  rowIndex = 0;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  do
  {
    result = Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, (unsigned __int16)rowTopY, 356, 0x1DDu, rowTopY + 22, 0x164u, rowTopY);
    if ( rowIndex + g_MultiplayerOpponentListScrollOffset < 20 )
    {
      if ( rowIndex + g_MultiplayerOpponentListScrollOffset == g_MultiplayerSelectedMapIndex )
        rowSpriteId = 21;
      else
        rowSpriteId = 18;
      Render_ReleaseSurface(rowSpriteId, cursorOverlayPresented);
      result = UI_DrawText(356, rowTopY, (int)(intptr_t)&aKarkhan[13 * rowIndex + 13 * g_MultiplayerOpponentListScrollOffset]);
    }
    ++rowIndex;
    rowTopY += 22;
  }
  while ( rowIndex < 11 );
  if ( cursorOverlayPresented )
    return Render_Present((int)(intptr_t)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5441D8: using guessed type int dword_5441D8;
// 5441DC: using guessed type int dword_5441DC;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (004494B0) --------------------------------------------------------
int  MultiplayerSetup_HandleScrollListDownButton(int widgetRecord)
{
  UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  if ( g_MultiplayerOpponentListScrollOffset < 19 )
    ++g_MultiplayerOpponentListScrollOffset;
  return MultiplayerSetup_RedrawOpponentNameList();
}
// 5441DC: using guessed type int dword_5441DC;

//----- (004494E0) --------------------------------------------------------
int  PlayGameMenu_HandleScrollButtonRelease(int widgetRecord)
{
  UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  if ( g_MultiplayerOpponentListScrollOffset )
    --g_MultiplayerOpponentListScrollOffset;
  return MultiplayerSetup_RedrawOpponentNameList();
}
// 5441DC: using guessed type int dword_5441DC;

//----- (00449C30) --------------------------------------------------------
void  Options_ApplyMainMenuSliders(int a1, DWORD a2)
{
  g_OptionsMainMenuMusicVolumeRaw = ((unsigned __int16)(((_WORD)g_Options_BrightnessSliderValue << 7)
                                  - (__CFSHL__(g_Options_BrightnessSliderValue << 7 >> 31, 8)
                                   + ((unsigned __int16)(g_Options_BrightnessSliderValue << 7 >> 31) << 8))) >> 8)
              - 64;
  g_OptionsMainMenuSoundVolumeRaw = (unsigned __int16)(16 * g_Options_MouseSpeedSliderValue
                                 - (__CFSHL__((16 * g_Options_MouseSpeedSliderValue) >> 31, 8)
                                  + ((unsigned __int16)((16 * g_Options_MouseSpeedSliderValue) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings((int)(intptr_t)&g_OptionsConfigRecordBase, a1, a2);
}
// 51860C: using guessed type int dword_51860C;
// 518654: using guessed type int dword_518654;
// 5188B0: using guessed type int dword_5188B0;
// 5188C9: using guessed type char byte_5188C9;
// 5188CA: using guessed type char byte_5188CA;

//----- (00449C80) --------------------------------------------------------
int  PlayGameMenu_HandleCloseButton(uintptr_t widgetRecord)
{
  int result; // eax

  /*
   * Widget records live on the caller's stack; the callback must keep the
   * full pointer (like the other converted widget callbacks). Original
   * 00449C80: `mov edx, 1; call sub_419ED0; mov ds:dword_543D78, edx` — the
   * exit flag is the constant 1, which the raw decompile left undefined.
   */
  result = UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 449C8B: variable 'v3' is possibly undefined
// 543D78: using guessed type int g_PlayGameMenuExitRequested;

//----- (00449CA0) --------------------------------------------------------
unsigned __int16 * Options_InitMainMenuSlidersAndWidgets(uintptr_t widgetRecord, int a2, DWORD a3)
{
  uintptr_t widgetContextBase; // ecx

  /*
   * Original 00449CA0: `mov ecx, eax` — the reset-button offsets are all
   * relative to the CLICKED widget record (the last table entry, which
   * lives on the caller's stack — keep the full pointer). The raw decompile
   * left `widgetContextBase` undefined; bind it to the argument.
   */
  widgetContextBase = widgetRecord;
  UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  if ( (*(_BYTE *)(widgetContextBase - 98) & 2) == 0 )
  {
    *(_DWORD *)(widgetContextBase - 98) = 2;
    UIWidget_RefreshActionButtonState(widgetContextBase - 106, (int)widgetContextBase);
  }
  if ( (*(_BYTE *)(widgetContextBase - 151) & 2) == 0 )
  {
    *(_DWORD *)(widgetContextBase - 151) = 2;
    UIWidget_RefreshActionButtonState(widgetContextBase - 159, (int)widgetContextBase);
  }
  if ( (*(_BYTE *)(widgetContextBase - 204) & 2) == 0 )
  {
    *(_DWORD *)(widgetContextBase - 204) = 2;
    UIWidget_RefreshActionButtonState(widgetContextBase - 212, (int)widgetContextBase);
  }
  if ( (*(_BYTE *)(widgetContextBase - 257) & 1) == 0 )
  {
    *(_DWORD *)(widgetContextBase - 257) = 1;
    UIWidget_RefreshActionButtonState(widgetContextBase - 265, (int)widgetContextBase);
  }
  g_Options_BrightnessSliderValue = 128;
  g_Options_ScrollSpeedSliderValue = 128;
  g_Options_MouseSpeedSliderValue = 128;
  return Options_DrawAllSliderThumbs((unsigned __int16 *)g_OptionsMenuSliderThumbPositions, a2, a3);
}
// 449CA9: variable 'v4' is possibly undefined
// 518600: using guessed type unsigned __int16 word_518600[6];
// 51860C: using guessed type int dword_51860C;
// 518630: using guessed type int dword_518630;
// 518654: using guessed type int dword_518654;

//----- (00449D60) --------------------------------------------------------
BOOL  Options_ToggleCheckboxMainMenu(uintptr_t widgetRecord)
{
  char toggledState; // dl

  /* Stack-resident widget record: keep the full pointer, and load the
   * 4-byte compact sound-name pointer at +49 (not an 8-byte field). */
  toggledState = *(_BYTE *)(widgetRecord + 8) ^ 1;
  *(_BYTE *)(widgetRecord + 8) = toggledState;
  *(_BYTE *)(widgetRecord + 8) = toggledState ^ 2;
  Audio_PlayButtonSound((char *)(uintptr_t)(unsigned int)*(_DWORD *)(widgetRecord + 49));
  return Render_Begin((int)(intptr_t)g_RenderState, 0);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A110) --------------------------------------------------------
int  LoadMenu_HandleSlotConfirmButtonRelease(int widgetRecord, DWORD a2)
{
  int result; // eax

  if ( widgetRecord )
    UIWidget_PlayPressedReleaseAnimation(widgetRecord);
  result = SaveSlot_HasDataFile(g_LoadMenuSelectedSlotIndex, a2);
  if ( result )
  {
    g_PlayGameMenuLaunchGameFlag = 1;
    g_PlayGameMenuExitRequested = 1;
  }
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;
// 5441E0: using guessed type int dword_5441E0;

//----- (0044A140) --------------------------------------------------------
void * LoadMenu_RedrawSaveSlotRow(int slotRow, DWORD a2)
{
  int rowTopY; // edi
  int rowSpriteId; // eax
  char *row_label; // eax
  void *result; // eax
  void *previousRenderDevice; // [esp+14h] [ebp-20h]
  int cursorOverlayPresented; // [esp+18h] [ebp-1Ch]

  previousRenderDevice = g_RenderDevice;
  row_label = (char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes(20);
  if ( !row_label )
    return previousRenderDevice;
  SaveSlot_LoadLabelOrPlaceholder(slotRow, row_label, a2);
  cursorOverlayPresented = g_CursorOverlayPresented;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  rowTopY = (unsigned __int16)(22 * slotRow + 155);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, rowTopY, 22 * slotRow + 175);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, (unsigned __int16)rowTopY, 244, 0x1A4u, 22 * slotRow + 175, 0xF4u, rowTopY);
  if ( slotRow == g_LoadMenuSelectedSlotIndex )
    rowSpriteId = 18;
  else
    rowSpriteId = 21;
  Render_ReleaseSurface(rowSpriteId, (unsigned __int16)(22 * slotRow + 175));
  UI_DrawTextFmt(rowTopY, 244, 410, 22 * slotRow + 155, 3, (const char*)(intptr_t)((int)(uintptr_t)row_label));
  if ( cursorOverlayPresented )
    Render_Present((int)(intptr_t)g_RenderState);
  Compat_FreeLow32Bytes((int)(uintptr_t)row_label);
  result = previousRenderDevice;
  g_RenderDevice = (_UNKNOWN*)(previousRenderDevice);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5441E0: using guessed type int dword_5441E0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (0044A510) --------------------------------------------------------
int  Options_DrawSliderThumb(unsigned __int16 *sliderRecord, char a2, DWORD a3)
{
  int v4; // ecx
  int previousResourceHandle; // edi
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9 CLASH95_UNUSED; // ecx
  __int16 thumbSpriteHeight; // ax
  int SpriteForChar; // eax
  int result; // eax
  __int16 thumbTravel16; // bx
  unsigned __int16 fillRightExtent; // ax
  unsigned __int16 fillBottomExtent; // [esp+10h] [ebp-2Ch]
  unsigned __int16 spriteWidthExtent; // [esp+10h] [ebp-2Ch]
  unsigned __int16 trackLeftX; // [esp+14h] [ebp-28h]
  unsigned __int16 trackTopY; // [esp+18h] [ebp-24h]
  void *previousRenderDevice; // [esp+1Ch] [ebp-20h]
  __int16 thumbTravel; // [esp+20h] [ebp-1Ch]

  Render_Pump();
  previousResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  previousRenderDevice = g_RenderDevice;
  if ( *((_DWORD *)sliderRecord + 8) )
  {
    trackTopY = sliderRecord[4];
    trackLeftX = *sliderRecord;
    spriteWidthExtent = DLX_GetSpriteWidth(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]) - 1;
    thumbTravel16 = sliderRecord[2] - *sliderRecord;
    fillRightExtent = thumbTravel16 + DLX_GetSpriteHeight(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]) - 1;
    Render_FillRect(
      (_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 8),
      0,
      0,
      0,
      fillRightExtent,
      spriteWidthExtent,
      trackLeftX,
      trackTopY);
  }
  else
  {
    Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v4, a2, a3);
    if ( Surface )
    {
      SpriteWidth = DLX_GetSpriteWidth(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]);
      thumbTravel = sliderRecord[2] - *sliderRecord;
      SpriteHeight = DLX_GetSpriteHeight(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]);
      /* Original 0044A510: `mov eax, ecx` — the Mem_Alloc result is the
       * surface buffer argument; the raw decompile left `v9` undefined. */
      Surface = Render_CreateSurface((int)(intptr_t)Surface, thumbTravel + SpriteHeight, SpriteWidth);
    }
    *((_DWORD *)sliderRecord + 8) = (int)(uintptr_t)Surface;
    fillBottomExtent = sliderRecord[4] + DLX_GetSpriteWidth(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]) - 1;
    thumbSpriteHeight = DLX_GetSpriteHeight(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), sliderRecord[12]);
    Render_FillRect(
      0,
      (_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 8),
      sliderRecord[4],
      *sliderRecord,
      sliderRecord[2] + thumbSpriteHeight - 1,
      fillBottomExtent,
      0,
      0);
  }
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  SpriteForChar = DLX_GetSpriteForChar(*(_DWORD *)(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 5), *((_DWORD *)sliderRecord + 6));
  /*
   * Original 0044A510 draws the thumb through render-device slot +52
   * (Render_BlitCompressedSpriteRLE) with ebx = track_min + travel*value/256
   * (the position along the horizontal track) and ecx = the record's
   * cross-track row; the raw decompile dropped the ebx computation and used
   * a 64-bit-wide slot load. Route through the sanctioned native seam like
   * the other converted +52 callers.
   */
  Compat_RenderDeviceDrawMenuSprite(
    *(_DWORD *)sliderRecord
      + ((*((_DWORD *)sliderRecord + 1) - *(_DWORD *)sliderRecord) * *((_DWORD *)sliderRecord + 3) >> 8),
    *((_DWORD *)sliderRecord + 2),
    SpriteForChar,
    1);
  g_RenderDevice = (_UNKNOWN*)(previousRenderDevice);
  Render_Present((int)(intptr_t)g_RenderState);
  result = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previousResourceHandle);
  if ( *((_DWORD *)sliderRecord + 7) )
    return ((int (*)(void))(uintptr_t)(unsigned int)*((_DWORD *)sliderRecord + 7))();
  return result;
}
// 44A54B: variable 'v4' is possibly undefined
// 44A591: variable 'v9' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A6D0) --------------------------------------------------------
unsigned int  Options_AnimateSliderThumbDrag(int sliderRecord)
{
  unsigned int result; // eax
  int thumbOffsetScaled; // eax
  int thumbLeftEdge; // esi
  int sliderBottomY; // edx
  int lastMouseX; // esi
  int dragStartMouseX; // edi
  DWORD dragBaseValue; // ebp
  int newThumbValue; // edx
  int mouseCursorRawX; // esi
  DWORD sliderMinX; // ebp
  unsigned __int16 SpriteHeight; // ax
  char v13 CLASH95_UNUSED; // cl

  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  if ( result )
  {
    thumbOffsetScaled = *(_DWORD *)(uintptr_t)(sliderRecord + 12) * (*(_DWORD *)(uintptr_t)(sliderRecord + 4) - *(_DWORD *)(uintptr_t)sliderRecord);
    thumbLeftEdge = *(_DWORD *)(uintptr_t)sliderRecord + ((thumbOffsetScaled - (__CFSHL__(thumbOffsetScaled >> 31, 8) + (thumbOffsetScaled >> 31 << 8))) >> 8);
    result = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( g_MouseCursorRawY >> g_CursorCoordShift >= *(_DWORD *)(uintptr_t)(sliderRecord + 8) )
    {
      sliderBottomY = (unsigned __int16)DLX_GetSpriteWidth(*(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(sliderRecord + 20), *(_WORD *)(uintptr_t)(sliderRecord + 24)) + *(_DWORD *)(uintptr_t)(sliderRecord + 8);
      result = g_MouseCursorRawY >> g_CursorCoordShift;
      if ( g_MouseCursorRawY >> g_CursorCoordShift <= sliderBottomY )
      {
        if ( thumbLeftEdge > g_MouseCursorRawX >> g_CursorCoordShift
          || g_MouseCursorRawX >> g_CursorCoordShift > (unsigned __int16)DLX_GetSpriteHeight(
                                                               *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(sliderRecord + 20),
                                                               *(_WORD *)(uintptr_t)(sliderRecord + 24))
                                         + thumbLeftEdge )
        {
          mouseCursorRawX = g_MouseCursorRawX;
          sliderMinX = *(_DWORD *)(uintptr_t)sliderRecord;
          SpriteHeight = DLX_GetSpriteHeight(*(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(sliderRecord + 20), *(_WORD *)(uintptr_t)(sliderRecord + 24));
          result = (int)(((mouseCursorRawX >> g_CursorCoordShift) - sliderMinX - SpriteHeight / 2) << 8) / (*(_DWORD *)(uintptr_t)(sliderRecord + 4) - *(_DWORD *)(uintptr_t)sliderRecord);
          if ( result <= 0x100 )
          {
            *(_DWORD *)(uintptr_t)(sliderRecord + 12) = result;
            return Options_DrawSliderThumb((unsigned __int16 *)(uintptr_t)sliderRecord, sliderRecord, sliderMinX);
          }
        }
        else
        {
          lastMouseX = g_MouseCursorRawX >> g_CursorCoordShift;
          dragStartMouseX = g_MouseCursorRawX >> g_CursorCoordShift;
          dragBaseValue = *(_DWORD *)(uintptr_t)(sliderRecord + 12);
          while ( 1 )
          {
            result = DD_IsFlipping((int)(intptr_t)g_RenderState);
            if ( !result )
              break;
            DD_Pump((int)(intptr_t)g_RenderState, sliderRecord);
            if ( lastMouseX != g_MouseCursorRawX >> g_CursorCoordShift )
            {
              newThumbValue = (((g_MouseCursorRawX >> g_CursorCoordShift) - dragStartMouseX) << 8) / (*(_DWORD *)(uintptr_t)(sliderRecord + 4) - *(_DWORD *)(uintptr_t)sliderRecord) + dragBaseValue;
              *(_DWORD *)(uintptr_t)(sliderRecord + 12) = newThumbValue;
              if ( newThumbValue < 0 )
              {
                *(_DWORD *)(uintptr_t)(sliderRecord + 12) = 0;
              }
              else if ( newThumbValue > 256 )
              {
                *(_DWORD *)(uintptr_t)(sliderRecord + 12) = 256;
              }
              Options_DrawSliderThumb((unsigned __int16 *)(uintptr_t)sliderRecord, sliderRecord, dragBaseValue);
              lastMouseX = g_MouseCursorRawX >> g_CursorCoordShift;
            }
          }
        }
      }
    }
  }
  return result;
}
// 44A851: simplified comparisons for 'eax.4': <0 || >=101 became >=101u
// 44A836: variable 'v13' is possibly undefined
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0044A880) --------------------------------------------------------
unsigned __int16 * Options_DrawAllSliderThumbs(unsigned __int16 *result, int a2, DWORD a3)
{
  unsigned __int16 *currentSlider; // edx
  int v4 CLASH95_UNUSED; // edx

  currentSlider = result;
  if ( *(_DWORD *)result != -1 )
  {
    do
    {
      /*
       * Original 0044A880 walk: `mov ebx,[edx+24h]; add edx,24h` — the next
       * pointer is the CURRENT record plus 36; the raw decompile routed it
       * through an undefined temporary (`v4`).
       */
      result = (unsigned __int16 *)(uintptr_t)Options_DrawSliderThumb(currentSlider, a2, a3);
      a2 = *(_DWORD *)(void *)((char *)currentSlider + 36);
      currentSlider = (unsigned __int16 *)(void *)((char *)currentSlider + 36);
    }
    while ( a2 != -1 );
  }
  return result;
}
// 44A893: variable 'v4' is possibly undefined

//----- (0044A8B0) --------------------------------------------------------
_DWORD * Options_AnimateAllSliderThumbs(_DWORD *result)
{
  int currentSlider; // edx
  int v2 CLASH95_UNUSED; // edx
  int nextLink; // ebx

  currentSlider = (int)(intptr_t)result;
  if ( *result != -1 )
  {
    do
    {
      /* Same undefined-temporary repair as Options_DrawAllSliderThumbs. */
      result = (_DWORD *)(uintptr_t)Options_AnimateSliderThumbDrag(currentSlider);
      nextLink = *(_DWORD *)(uintptr_t)(currentSlider + 36);
      currentSlider = currentSlider + 36;
    }
    while ( nextLink != -1 );
  }
  return result;
}
// 44A8C3: variable 'v2' is possibly undefined

//----- (0044A8E0) --------------------------------------------------------
_DWORD * Options_DestroySliderThumbList(_DWORD *result)
{
  _DWORD *currentSlider; // ecx
  int thumbSurface; // esi
  int nextLink; // ebx

  currentSlider = result;
  if ( *result != -1 )
  {
    do
    {
      thumbSurface = currentSlider[8];
      if ( thumbSurface )
        result = (_DWORD *)(uintptr_t)(unsigned int)RenderSurface_InvokeSlot0(
                                                     (_DWORD *)(uintptr_t)(unsigned int)thumbSurface,
                                                     2);
      currentSlider[8] = 0;
      nextLink = currentSlider[9];
      currentSlider += 9;
    }
    while ( nextLink != -1 );
  }
  return result;
}
// 44A905: variable 'v1' is possibly undefined

//----- (0044A920) --------------------------------------------------------
void  lodaOptionsCfg(DWORD a1)
{
  int configStream; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // [esp-4h] [ebp-Ch]
  int configStreamHandle; // [esp+0h] [ebp-8h] BYREF

  configStream = FileSystem_ResolveReadPath(aOptions_cfg, 0);
  configStreamHandle = configStream;
  if ( configStream )
  {
    v5 = v3;
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)configStream + 20))();
    Compat_FileSystemQueryRelease(v4, &configStreamHandle);
    Options_ApplyRecordSettings((int)(intptr_t)&g_OptionsConfigRecordBase, v5, a1);
  }
  else
  {
    Options_ApplyRecordSettings((int)(intptr_t)&g_OptionsConfigRecordBase, v3, a1);
  }
}
// 44A93C: variable 'v3' is possibly undefined
// 44A960: variable 'v4' is possibly undefined
// 5188B0: using guessed type int dword_5188B0;

//----- (0044A980) --------------------------------------------------------
int  Options_SaveConfigToFile(int a1, DWORD a2)
{
  int fileHandle; // eax
  int v3; // ecx

  fileHandle = IO_FOpen(aOptions_cfg_0, (unsigned __int8 *)aWb_1, a1, a2);
  fwrite_(&g_OptionsConfigRecordBase, 27, fileHandle, 1);
  return fclose_(v3);
}
// 44A9AD: variable 'v3' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5188B0: using guessed type int dword_5188B0;

//----- (0044A9C0) --------------------------------------------------------
void  Options_ApplyRecordSettings(int configRecord, int a2, DWORD a3)
{
  int v5; // edx
  _DWORD paletteArray[260]; // [esp-40Ch] [ebp-410h] BYREF

  (void)a2;
  Palette_SetBrightnessOffset((int)(intptr_t)&g_MainRenderDevice, *(char *)(uintptr_t)(configRecord + 26));
  /*
   * Original 0044A9C0: `mov edx, offset unk_51D59C; mov eax, esp;
   * call __wcpp_4_copy_array__` — copy the device's staged palette
   * (g_MainRenderDevice+0xDC, 256 dwords) into the stack array, then
   * re-apply it with the new brightness offset. The raw decompile dropped
   * the copy source and applied an uninitialized stack buffer to the DAC.
   */
  qmemcpy(paletteArray, (unsigned char *)&g_MainRenderDevice + 0xDC, 1024);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, paletteArray);
  RenderState_SetMouseSpeed((int)(intptr_t)g_RenderState, 8 * *(unsigned __int8 *)(uintptr_t)(configRecord + 25) + 20, a3);
  if ( (int *)(uintptr_t)configRecord == &g_OptionsConfigRecordBase )
  {
    if ( *(_DWORD *)(uintptr_t)(configRecord + 16) )
      Audio_SetMusicActiveFlag();
    else
      Audio_ClearMusicActiveFlag();
  }
  else if ( *(_DWORD *)(uintptr_t)(configRecord + 16) )
  {
    Audio_StartMainMusicIfStopped(v5, a3);
  }
  else
  {
    Audio_StopMainMusicIfPlaying();
  }
  if ( *(_DWORD *)(uintptr_t)(configRecord + 20) )
    Audio_EnableUnitSounds();
  else
    Audio_DisableUnitSounds();
}
// 44AA23: variable 'v5' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5188B0: using guessed type int dword_5188B0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044AD60) --------------------------------------------------------
char  PlayerRuntimeState_ResetDefaults(uintptr_t playerState)
{
  uintptr_t playerStateBase; // ecx
  uintptr_t queenSlotLoopEnd; // edx

  playerStateBase = playerState;
  *(_DWORD *)(playerState + PLAYER_MINIMAP_VISIBLE_OFFSET) = 0;
  *(_DWORD *)(playerState + 43) = -1;
  *(_DWORD *)(playerState + 35) = 1;
  *(_BYTE *)(playerState + 47) = 1;
  *(_BYTE *)(playerState + 48) = 1;
  *(_DWORD *)(playerState + PLAYER_RELIGION_FLAG_OFFSET) = 1;
  *(_DWORD *)(playerState + PLAYER_IS_HUMAN_OFFSET) = 1;
  *(_DWORD *)(playerState + PLAYER_AI_INTELLIGENCE_OFFSET) = PLAYER_AI_INTELLIGENCE_EASY;
  *(_DWORD *)playerState = 0;
  *(_WORD *)(playerState + 1417) = 0;
  queenSlotLoopEnd = playerState + 60;
  *(_BYTE *)(playerState + PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET) = 0;
  do
  {
    playerState += 6;
    *(_BYTE *)(playerState + 1351) = -1;
  }
  while ( playerState != queenSlotLoopEnd );
  memset((void *)(playerStateBase + PLAYER_REVEALED_TILES_OFFSET), 0, 0x514u);
  strcpy((char *)(playerStateBase + PLAYER_DISPLAY_NAME_OFFSET), aDoc);
  return 0;
}

//----- (0044AE10) --------------------------------------------------------
char  Game_ResetPlayerRuntimeStateByIndex(int playerIndex)
{
  return PlayerRuntimeState_ResetDefaults(PLAYER_RUNTIME_STATE(playerIndex));
}
// 5202E4: using guessed type int gameData;
