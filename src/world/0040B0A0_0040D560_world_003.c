/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
#include "../recovered_internal.h"

CLASH95_LOCAL TextSpriteResourceSlotRecord *TextSprite_GetActiveResourceSlot (void);

//----- (0040B0A0) --------------------------------------------------------
void  WorldMap_RunHumanTurnLoop(
        int entry_resource_handle,
        int ( *entry_render_hook)(int a1, char a2, DWORD a3),
        DWORD runtime_context,
        double st0_runtime)
{
  int selected_stack_record;
  unsigned char new_facing;
  int *queued_path;
  signed int available_action_points;
  unsigned __int16 required_action_points;
  int last_path_step;
  int saved_resource_handle;
  int (*saved_render_hook)();

  Diagnostics_TraceWorldMapActionEvent("human_turn_before_plague_notices", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  WorldMap_NotifyPlagueOutbreak(entry_resource_handle, (const char *)entry_render_hook, runtime_context);
  Diagnostics_TraceWorldMapActionEvent("human_turn_after_plague_notices", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  Diagnostics_TraceWorldMapActionEvent("human_turn_before_color_notice", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  UI_ShowTechnologyLevelUpIfChanged(0, runtime_context);
  g_CursorDesc_Default[5] = 0;
  g_CursorDesc_Default[6] = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)(unsigned int)g_RenderState, 0, 640, 0, 480);
  Diagnostics_TraceWorldMapActionEvent("human_turn_cursor_restored", g_SelectedUnitIndex, g_ActiveCursorDescriptorPtr, g_ActiveCursorDescriptor, 0);
  {
    _DWORD *render_state = (_DWORD *)(uintptr_t)(unsigned int)g_RenderState;
    Diagnostics_TraceWorldMapActionEvent(
      "human_turn_cursor_bounds",
      g_SelectedUnitIndex,
      render_state[4] >> render_state[277],
      render_state[5] >> render_state[277],
      g_CursorDesc_Default[6]);
  }
  Diagnostics_TraceWorldMapActionEvent("human_turn_after_color_notice", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  g_AdvanceToNextPlayerFlag = 0;
  g_WorldMapTurnLoopExitFlag = 0;
  Diagnostics_TraceWorldMapUnitSnapshot("human_turn_enter");
  do
  {
    UI_ReadCheatString(0);
    WorldMap_RunInputScriptStep();
    DD_Pump((int)g_RenderState, 0);
    WorldMap_TickPaletteFlashEffect(0, 0, 0);
    WorldMap_RedrawFrame(0);
    MiniMap_UpdateViewportFromCursor();
    if ( !WorldMap_HandleTopMenuBar(0, 0) )
    {
      Diagnostics_TraceWorldMapActionEvent("human_turn_break_top_menu", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
      break;
    }
    if ( !UnitStackSelection_HandleInput(0, st0_runtime) )
      WorldMap_HandleTileHoverAndClick(st0_runtime);
    if ( !g_WorldMap_KeyboardInputDisabled )
    {
      if ( !Input_IsKeyPressed(56) )
      {
        if ( Input_IsKeyPressed(34) )
        {
          if ( !*(_DWORD *)(gameData + 147151) )
          {
            *(_DWORD *)(gameData + 147151) = 1;
            goto LABEL_24;
          }
        }
        else if ( *(_DWORD *)(gameData + 147151) )
        {
          *(_DWORD *)(gameData + 147151) = 0;
LABEL_24:
          WorldMap_RedrawViewport(1);
        }
      }
      if ( Input_IsKeyPressed(56) )
      {
        if ( Input_IsKeyPressed(205) && g_SelectedUnitIndex != -1 )
        {
          selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
          new_facing = UNIT_STACK_FACING(selected_stack_record) + 1;
          UNIT_STACK_FACING(selected_stack_record) = new_facing & 7;
          Map_RedrawUnitNeighborhoodByIndex(g_SelectedUnitIndex);
          while ( Input_IsKeyPressed(205) )
            DD_Pump((int)g_RenderState, 0);
        }
        if ( Input_IsKeyPressed(203) )
        {
          if ( g_SelectedUnitIndex != -1 )
          {
            selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
            new_facing = UNIT_STACK_FACING(selected_stack_record) - 1;
            UNIT_STACK_FACING(selected_stack_record) = new_facing & 7;
            Map_RedrawUnitNeighborhoodByIndex(g_SelectedUnitIndex);
            while ( Input_IsKeyPressed(203) )
              DD_Pump((int)g_RenderState, 0);
          }
        }
        if ( Input_IsKeyPressed(200) )
        {
          if ( g_SelectedUnitIndex != -1 )
          {
            selected_stack_record = UNIT_STACK(g_SelectedUnitIndex);
            queued_path = Unit_MoveTrack(
                    g_SelectedUnitIndex,
                    UNIT_STACK_TILE_ROW(selected_stack_record),
                    UNIT_STACK_TILE_ROW(selected_stack_record)
                      + Map_NeighborDX[2 * (unsigned __int8)UNIT_STACK_FACING(selected_stack_record)],
                    UNIT_STACK_TILE_COLUMN(selected_stack_record),
                    0,
                    UNIT_STACK_TILE_COLUMN(selected_stack_record)
                      + Map_NeighborDY[2 * (unsigned __int8)UNIT_STACK_FACING(selected_stack_record)]);
            if ( queued_path )
            {
              last_path_step = queued_path[*queued_path];
              required_action_points = HIWORD(last_path_step);
              available_action_points = UnitStack_GetMinCurrentActionPoints(selected_stack_record);
              if ( available_action_points >= required_action_points )
              {
                qmemcpy((void *)UNIT_STACK_PATH_BUFFER(selected_stack_record), queued_path, UNIT_STACK_PATH_BYTES);
                if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
                  Audio_PlayUnitMoveOrderSound(*(__int16 *)UNIT_STACK_SLOT(selected_stack_record, 0));
                UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, 0, 0, st0_runtime);
              }
              j__nfree_();
              WorldMap_RedrawViewport(1);
              WorldMap_RefreshUnitStatusPanel(0);
            }
          }
        }
      }
    }
    WorldMap_HandleScrollKeysAndIdle(0);
    Diagnostics_TraceWorldMapActionEvent(
      "selection_after_sub407d20",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    WorldMap_PollActionButtonWidgets(0);
    Diagnostics_TraceWorldMapActionEvent(
      "selection_after_action_widgets",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    if ( Input_IsKeyPressed(1) )
    {
      saved_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
      saved_render_hook = g_RenderHook;
      g_RenderHook = (int (*)())Render_DefaultRH;
      Debug_Log(saved_resource_handle, 0, 0, (int)aSetrhS08x_0);
      WorldMap_ShowQuitConfirmDialog(0, 0, 0);
      Debug_Log((int)g_RenderHook, 0, 0, (int)aUnsetrh08x);
      g_RenderHook = saved_render_hook;
      Render_SetResourceHandle((int)&g_MainRenderDevice, saved_resource_handle);
    }
    if ( Player_CheckForDefeatAndHandleElimination(g_CurrentPlayerIndex, 0) )
    {
      g_WorldMapGameLostExitFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
    }
    if ( ACTIVE_MISSION_INDEX != -1 && Mission_CheckFailureCondition() )
    {
      g_WorldMapGameLostExitFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
      Video_PlayAviWithModeGuard((int)aArama1, aKon_por1);
      return;
    }
    if ( !PLAYER_IS_ACTIVE(g_CurrentPlayerIndex) )
    {
      Diagnostics_TraceWorldMapActionEvent("human_turn_player_inactive", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
      g_AdvanceToNextPlayerFlag = 1;
    }
    if ( ACTIVE_MISSION_INDEX == -1 )
    {
      if ( UI_CheckEndTurnHotkey(g_CurrentPlayerIndex) )
      {
        g_TurnEndedByCompletionFlag = 1;
        g_WorldMapTurnLoopExitFlag = 1;
        return;
      }
    }
    else if ( Mission_CheckObjectiveComplete(0, st0_runtime) )
    {
      Diagnostics_TraceWorldMapActionEvent("mission_objective_complete", g_SelectedUnitIndex, ACTIVE_MISSION_INDEX, g_CurrentPlayerIndex, 0);
      g_TurnEndedByCompletionFlag = 1;
      g_WorldMapTurnLoopExitFlag = 1;
      return;
    }
  }
  while ( !g_WorldMapTurnLoopExitFlag && !g_AdvanceToNextPlayerFlag );
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F8: using guessed type int dword_5202F8;
// 5202FC: using guessed type int dword_5202FC;
// 520300: using guessed type int dword_520300;
// 520304: using guessed type int dword_520304;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545140: using guessed type int dword_545140;

//----- (0040B640) --------------------------------------------------------
unsigned int  WorldMap_Initialize(char a1, DWORD loadContext)
{
  WorldMap_LoadResources(a1, loadContext);
  Map_InitTerrainMoveTableOffsets();
  UnitSpriteCache_ClearAllEntries();
  BuildingSpriteCache_Reset();
  return Map_InitBuildingSwayJitterOffsets(0);
}

//----- (0040B660) --------------------------------------------------------
int  PlayGame(int a1, char a2, DWORD allocContext, char a4, double st0_runtime, ...)
{
  int player_index;
  _DWORD *background_sprite_set;
  _DWORD *tree_sprite_set;
  int previous_resource_handle;
  int (*previous_render_hook)(int, char, DWORD);
  int active_mission_index;
  const char *background_resource_name;
  const char *tree_resource_name;

  (void)a1;
  (void)a2;

  g_MissionDefeatVideoPlayedGuard = 0;
  Debug_Log(0, 0, allocContext, (int)aPlaygame);
  Noop_PlayGameSessionBoundaryHook(0);
  for ( player_index = 0; player_index < 5; ++player_index )
  {
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(player_index) )
      Map_RevealAllTilesForPlayer(player_index);
  }
  background_resource_name = 0;
  tree_resource_name = 0;
  if ( MAP_THEME_INDEX == MAP_THEME_A )
  {
    background_resource_name = "backgr1.s32";
    tree_resource_name = "treemas1.s32";
  }
  else if ( MAP_THEME_INDEX == MAP_THEME_B )
  {
    background_resource_name = "backgr2.s32";
    tree_resource_name = "treemas2.s32";
  }
  else if ( MAP_THEME_INDEX == MAP_THEME_C )
  {
    background_resource_name = "backgr3.s32";
    tree_resource_name = "treemas3.s32";
  }
  if ( background_resource_name )
  {
    if ( g_WorldMapBackgroundSpriteSet )
      DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
    background_sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, allocContext);
    if ( background_sprite_set )
      background_sprite_set = DLXSpriteSet_Load(background_sprite_set, background_resource_name);
    g_WorldMapBackgroundSpriteSet = (int)background_sprite_set;
    tree_sprite_set = (_DWORD *)Mem_Alloc(4112, 0, 0, allocContext);
    if ( tree_sprite_set )
      tree_sprite_set = DLXSpriteSet_Load(tree_sprite_set, tree_resource_name);
    g_TreeSpriteSet = (int)tree_sprite_set;
  }
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  g_SelectedUnitIndex = -1;
  Locale_DrawInteger();
  UI_SetActiveWidgetTable(8);
  *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(gameData + VIEWED_PLAYER_INDEX_OFFSET) + gameData + 140039);
  *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(gameData + VIEWED_PLAYER_INDEX_OFFSET) + gameData + 140043);
  Locale_DrawInteger();
  Music_PlayMainMapTrack(MAP_THEME_INDEX, 0, 7, allocContext);
  Render_DrawSprite();
  WorldMap_RedrawViewport(1);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  WorldMap_LoadActionButtonSprites(0, 0, allocContext);
  g_CursorDesc_Default[5] = 0;
  g_CursorDesc_Default[6] = 0;
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)(unsigned int)g_RenderState, 0, 640, 0, 480);
  {
    _DWORD *render_state = (_DWORD *)(uintptr_t)(unsigned int)g_RenderState;
    Diagnostics_TraceWorldMapActionEvent(
      "playgame_cursor_bounds_restored",
      g_SelectedUnitIndex,
      render_state[4] >> render_state[277],
      render_state[5] >> render_state[277],
      g_CursorDesc_Default[6]);
  }
  UnitStackSelection_SyncForCurrentSelection((void *)(uintptr_t)(unsigned int)gameData, allocContext);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  Render_Present((int)g_RenderState);
  WorldMap_RedrawViewport(1);
  Debug_Log(0, 20, allocContext, (int)aStart);
  LogAllUnits(0, 20, allocContext);
  LogAllBuildings(0, 20, allocContext);
  if ( ACTIVE_MISSION_INDEX != -1 && GAME_TURN_COUNTER == 1 && !getenv("CLASH95_SKIP_MISSION_STATUS_PANEL") )
    UI_ShowMissionStatusPanel(0, allocContext);
  g_WorldMapGameLostExitFlag = 0;
  g_TurnEndedByCompletionFlag = 0;
  g_AdvanceToNextPlayerFlag = 0;
  g_WorldMapTurnLoopExitFlag = 0;
  g_PendingLoadGameSlotIndex = -1;
  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  previous_render_hook = (int (*)(int, char, DWORD))g_RenderHook;
  g_RenderHook = (int (*)())WorldMap_RenderHook;
  Debug_Log(previous_resource_handle, 0, allocContext, (int)aSetrhS08x, "RedrawMainMap", WorldMap_RenderHook);
  while ( 1 )
  {
    Diagnostics_TraceWorldMapActionEvent("playgame_loop_top", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    UI_LoadCurrentPlayerInfoSpriteSet(g_CurrentPlayerIndex, 0, 0, allocContext);
    Diagnostics_TraceWorldMapActionEvent("playgame_after_player_info", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex));
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    {
      Diagnostics_TraceWorldMapActionEvent("playgame_before_human_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
      WorldMap_RunHumanTurnLoop(previous_resource_handle, previous_render_hook, allocContext, st0_runtime);
      Diagnostics_TraceWorldMapActionEvent("playgame_after_human_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, g_WorldMapTurnLoopExitFlag);
    }
    else if ( GAME_TURN_COUNTER )
    {
      Diagnostics_TraceWorldMapActionEvent("playgame_before_ai_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
      Debug_Log(0, 0, allocContext, (int)aComputerplay);
      Rules_ExecuteAITurn();
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
      Diagnostics_TraceWorldMapActionEvent("playgame_after_ai_turn", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, g_WorldMapTurnLoopExitFlag);
    }
    if ( g_WorldMapTurnLoopExitFlag )
      break;
    Diagnostics_TraceWorldMapActionEvent("advance_turn_call", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    Game_AdvanceToNextPlayerTurn(0, 0, allocContext, st0_runtime);
    Diagnostics_TraceWorldMapActionEvent("advance_turn_return", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
    Diagnostics_TraceWorldMapUnitSnapshot("after_turn_advance");
  }
  Render_Pump();
  Debug_Log(0, 0, allocContext, (int)aUnsetrh08x_1, g_RenderHook);
  g_RenderHook = (int (*)())previous_render_hook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, allocContext, (int)aKoniecGryPoDTu, GAME_TURN_COUNTER);
  LogAllUnits(0, 20, allocContext);
  LogAllBuildings(0, 20, allocContext);
  Audio_StopMainMusic();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  MiniMap_DestroySurface(0);
  WorldMap_UnloadActionButtonSprites(0, 0);
  WorldMap_UnloadResources(allocContext);
  Tooltip_ReleaseBackdropSurface();
  Rules_ShowBanner_StrategicClash();
  Mem_PurgeFreeListsForSpace(-1, 0, 0);
  Debug_Log(0, 0, allocContext, (int)aPlaygameEnd);
  Noop_PlayGameSessionBoundaryHook(0);
  if ( g_PendingLoadGameSlotIndex != -1 )
  {
    WorldMap_Initialize(0, allocContext);
    SaveSlot_LoadGame(g_PendingLoadGameSlotIndex, allocContext, st0_runtime);
    PlayGame(0, 0, allocContext, a4, st0_runtime);
    return 0;
  }
  active_mission_index = ACTIVE_MISSION_INDEX;
  Diagnostics_TraceWorldMapActionEvent(
    "mission_playgame_return",
    g_SelectedUnitIndex,
    active_mission_index,
    g_TurnEndedByCompletionFlag,
    g_CurrentPlayerIndex);
  if ( active_mission_index == -1 || !g_TurnEndedByCompletionFlag )
    return 0;
  if ( active_mission_index == 9 || active_mission_index == 19 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      active_mission_index == 9 ? "campaign_first_victory_branch" : "campaign_second_victory_branch",
      g_SelectedUnitIndex,
      active_mission_index,
      g_CurrentPlayerIndex,
      0);
    Video_PlayAviWithModeGuard(-1, aZwy02);
    return 0;
  }
  Diagnostics_TraceWorldMapActionEvent(
    "mission_auto_advance",
    g_SelectedUnitIndex,
    active_mission_index,
    active_mission_index + 1,
    g_CurrentPlayerIndex);
  Scenario_LoadMissionByIndexAndPlay((char *)(uintptr_t)(unsigned int)(active_mission_index + 1), -1, allocContext, st0_runtime);
  return 0;
}
// 4476A0: using guessed type int __thiscall nullsub_3(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B64: using guessed type int dword_511B64;
// 519808: using guessed type int dword_519808;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202C0: using guessed type int dword_5202C0;
// 5202D8: using guessed type int dword_5202D8;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 5202F8: using guessed type int dword_5202F8;
// 5202FC: using guessed type int dword_5202FC;
// 520300: using guessed type int dword_520300;
// 520304: using guessed type int dword_520304;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;
// 5452E8: using guessed type int dword_5452E8;

TextSpriteResourceSlotRecord *TextSprite_GetResourceSlot(int slot_index)
{
  if ( slot_index < 0 || slot_index >= TEXT_SPRITE_RESOURCE_SLOT_COUNT )
    return 0;
  return &g_TextSpriteResourceSlots[slot_index];
}

CLASH95_LOCAL TextSpriteResourceSlotRecord *TextSprite_GetActiveResourceSlot(void)
{
  return TextSprite_GetResourceSlot(g_ActiveTextSpriteSlot);
}

//----- (0040BAE0) --------------------------------------------------------
int  Render_ReleaseSurface(int slotIndex, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  _DWORD *sprite_set;
  int result; // eax

  slot = TextSprite_GetResourceSlot(slotIndex);
  g_ActiveTextSpriteSlot = slotIndex;
  if ( !slot )
    return 0;
  sprite_set = (_DWORD *)(uintptr_t)(unsigned int)slot->cached_sprite_set;
  if ( !sprite_set )
  {
    sprite_set = (_DWORD *)Mem_Alloc(4112, slotIndex, 0, allocContext);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, slot->source_stem);
    slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
  }
  result = 12 * slotIndex;
  g_TextSpriteLastActivatedSlotIndex = slotIndex;
  return result;
}
// 520724: using guessed type int dword_520724;
// 520728: using guessed type int dword_520728;

//----- (0040BB60) --------------------------------------------------------
char  TextSprite_ActivateResourceSlot(int slotIndex, char styleFlag, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  _DWORD *sprite_set;
  char result; // al

  slot = TextSprite_GetResourceSlot(slotIndex);
  g_ActiveTextSpriteSlot = slotIndex;
  if ( !slot )
    return styleFlag;
  sprite_set = (_DWORD *)(uintptr_t)(unsigned int)slot->cached_sprite_set;
  if ( !sprite_set )
  {
    sprite_set = (_DWORD *)Mem_Alloc(4112, slotIndex, 0, allocContext);
    if ( sprite_set )
      sprite_set = DLXSpriteSet_Load(sprite_set, slot->source_stem);
    slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
  }
  result = styleFlag;
  g_TextSpriteLastActivatedSlotIndex = slotIndex;
  g_TextSprite_StyleFlag = styleFlag;
  return result;
}
// 51F28C: using guessed type char byte_51F28C;
// 520724: using guessed type int dword_520724;
// 520728: using guessed type int dword_520728;

//----- (0040BBF0) --------------------------------------------------------
char  TextSprite_SetStyleFlag(char result)
{
  g_TextSprite_StyleFlag = result;
  return result;
}
// 51F28C: using guessed type char byte_51F28C;

//----- (0040BC00) --------------------------------------------------------
int  TextSprite_DrawGlyphAndAdvance(int penX, int penY, unsigned __int8 charCode)
{
  TextSpriteResourceSlotRecord *slot;
  unsigned __int16 sprite_index;
  int sprite_for_char;

  slot = TextSprite_GetActiveResourceSlot();
  if ( !slot || !slot->cached_sprite_set )
    return penX;
  sprite_index = (unsigned __int16)(charCode - 32);
  sprite_for_char = DLX_GetSpriteForChar(slot->cached_sprite_set, sprite_index);
  Compat_RenderDeviceDrawMenuSprite((unsigned __int16)penX, (unsigned __int16)penY, sprite_for_char, 1);
  DLX_GetSpriteWidth(slot->cached_sprite_set, sprite_index);
  return penX + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, sprite_index) + slot->glyph_spacing_word;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520724: using guessed type int dword_520724;

//----- (0040BC90) --------------------------------------------------------
int  TextSprite_DrawStringWithOrientation(int penX, int penY, char vertical, unsigned __int8 *text)
{
  TextSpriteResourceSlotRecord *slot;
  int lineStep; // edx
  unsigned __int8 glyph; // bl

  slot = TextSprite_GetActiveResourceSlot();
  if ( vertical == 1 )
  {
    while ( *text )
    {
      TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, *text);
      LOWORD(lineStep) = slot ? slot->line_step_word : 0;
      ++text;
      penY += lineStep;
    }
  }
  else
  {
    while ( *text )
    {
      glyph = *text++;
      penX = TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, glyph);
    }
  }
  return penX;
}
// 40BCD2: variable 'v7' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BD40) --------------------------------------------------------
int  TextSprite_MeasureStringExtent(_BYTE *text)
{
  TextSpriteResourceSlotRecord *slot;
  _BYTE *cursor; // ecx
  int extent; // ebx
  unsigned __int16 glyphSpacing; // si

  slot = TextSprite_GetActiveResourceSlot();
  cursor = text;
  extent = 0;
  if ( !slot || !slot->cached_sprite_set || !*text )
    return extent;
  do
  {
    while ( *cursor == 10 )
    {
      if ( !*++cursor )
        return extent;
    }
    glyphSpacing = slot->glyph_spacing_word;
    extent += glyphSpacing + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, (unsigned __int8)*cursor - 32);
  }
  while ( *cursor );
  return extent;
}
// 40BD4E: variable 'v1' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BDA0) --------------------------------------------------------
_BYTE * TextSprite_FindWordWrapBreak(_BYTE *text, int maxWidth)
{
  TextSpriteResourceSlotRecord *slot;
  _BYTE *cursor; // ecx
  _BYTE *lastSpaceBreak; // ebp
  int accumWidth; // ebx
  unsigned __int16 glyphSpacing; // si

  slot = TextSprite_GetActiveResourceSlot();
  cursor = text;
  lastSpaceBreak = text;
  accumWidth = 0;
  if ( !slot || !slot->cached_sprite_set || !*text )
    return 0;
  while ( 1 )
  {
    if ( *cursor == 10 )
      return cursor;
    if ( *cursor == 32 )
      lastSpaceBreak = cursor;
    glyphSpacing = slot->glyph_spacing_word;
    accumWidth += glyphSpacing + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, (unsigned __int8)*cursor - 32);
    if ( accumWidth > maxWidth )
      break;
    if ( !*cursor )
      return 0;
  }
  return lastSpaceBreak;
}
// 40BDB6: variable 'v2' is possibly undefined
// 520724: using guessed type int dword_520724;

//----- (0040BE20) --------------------------------------------------------
int  Str_CountSpaces(char *text)
{
  int spaceCount; // edx
  char ch; // bl

  spaceCount = 0;
  while ( *text )
  {
    ch = *text++;
    if ( ch == 32 )
      ++spaceCount;
  }
  return spaceCount;
}

//----- (0040BE50) --------------------------------------------------------
int __cdecl UI_DrawText(int penX, int penY, int format, ...)
{
  unsigned __int8 *text;
  va_list args;

  if ( !format )
    g_UiDrawTextBuffer[0] = 0;
  else
  {
    va_start(args, format);
    vsnprintf((char *)g_UiDrawTextBuffer, sizeof(g_UiDrawTextBuffer), (const char *)(uintptr_t)(unsigned int)format, args);
    va_end(args);
  }
  text = g_UiDrawTextBuffer;
  while ( *text )
    penX = (unsigned __int16)TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, penY, *text++);
  return penX;
}
// 520320: using guessed type unsigned __int8 byte_520320[512];

//----- (0040BEE0) --------------------------------------------------------
int  UI_RenderAlignedTextWithCursor(
        int left,
        int right,
        int alignMode,
        int y,
        int penX,
        unsigned __int8 *text)
{
  unsigned __int8 *cursor;
  unsigned __int8 *line_start;
  _BYTE *line_break;
  int text_width;
  int extra_space_width;
  int glyph_index;
  int saved_x;
  int line_step;
  int wrap_width;
  char saved_break_char;

  cursor = text;
  text_width = Render_LoadResourceSprite_v3(text);
  extra_space_width = 0;
  glyph_index = 0;

  switch ( alignMode )
  {
    case 1:
      penX = left;
      break;
    case 2:
      penX = right - text_width;
      break;
    case 3:
      penX = (right - left - text_width) / 2 + left;
      break;
    case 4:
    {
      int space_count;

      penX = left;
      space_count = Str_CountSpaces((char *)text);
      if ( space_count > 0 )
        extra_space_width = (right - left - text_width) / space_count;
      break;
    }
    case 5:
    case 6:
      wrap_width = right - left;
      line_start = text;
      while ( line_start && *line_start )
      {
        int line_width;
        unsigned __int8 *newline;

        line_width = (unsigned __int16)Render_LoadResourceSprite_v3(line_start);
        newline = line_start;
        while ( *newline && *newline != 10 )
          ++newline;
        if ( line_width <= wrap_width && !*newline )
        {
          UI_DrawTextFmt(penX, left, right, y, alignMode == 5 ? 1 : 3, (const char *)line_start);
          return penX;
        }

        line_break = TextSprite_FindWordWrapBreak(line_start, wrap_width);
        if ( !line_break )
          line_break = (_BYTE *)newline;
        if ( !line_break || !*line_break )
        {
          UI_DrawTextFmt(penX, left, right, y, alignMode == 5 ? 1 : 3, (const char *)line_start);
          return penX;
        }

        saved_break_char = *line_break;
        *line_break = 0;
        UI_DrawTextFmt(penX, left, right, y, (alignMode == 5) + 3, (const char *)line_start);
        *line_break = saved_break_char;
        line_step = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
        y += line_step;
        line_start = (unsigned __int8 *)line_break + 1;
      }
      return penX;
    default:
      break;
  }

  while ( cursor && *cursor )
  {
    unsigned __int8 glyph;

    if ( *cursor == 32 )
      penX += extra_space_width;
    saved_x = penX;
    glyph = *cursor++;
    if ( glyph != 10 )
      penX = (unsigned __int16)TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, y, glyph);
    if ( glyph_index == g_UITextCursorGlyphIndex )
      TextSprite_DrawGlyphAndAdvance(saved_x, y, 0x5Fu);
    ++glyph_index;
  }
  if ( glyph_index == g_UITextCursorGlyphIndex )
    TextSprite_DrawGlyphAndAdvance((unsigned __int16)penX, y, 0x5Fu);
  return penX;
}
// 511EC0: using guessed type int dword_511EC0;
// 520728: using guessed type int dword_520728;

//----- (0040C150) --------------------------------------------------------
int  UI_DrawTextFmt(int penX, int left, int right, int y, int alignMode, const char *format, ...)
{
  va_list args;

  if ( !format )
    g_UiDrawTextFmtBuffer[0] = 0;
  else
  {
    va_start(args, format);
    vsnprintf((char *)g_UiDrawTextFmtBuffer, sizeof(g_UiDrawTextFmtBuffer), format, args);
    va_end(args);
  }
  return UI_RenderAlignedTextWithCursor(left, right, alignMode, y, penX, g_UiDrawTextFmtBuffer);
}
// 520520: using guessed type unsigned __int8 byte_520520[516];

//----- (0040C190) --------------------------------------------------------
int  UI_DrawTextFmtV(int left, int right, int alignMode, int y, const char *format, va_list args)
{
  unsigned __int8 textBuffer[524]; // [esp+0h] [ebp-20Ch] BYREF

  if ( !format )
    textBuffer[0] = 0;
  else
    vsnprintf((char *)textBuffer, sizeof(textBuffer), format, args);
  return UI_RenderAlignedTextWithCursor(left, right, alignMode, y, y, textBuffer);
}
// 473FC3: using guessed type int __fastcall vsprintf_(_DWORD, _DWORD);

//----- (0040C1D0) --------------------------------------------------------
int  UI_GetTextXOffset(int slotIndex)
{
  TextSpriteResourceSlotRecord *slot;

  slot = TextSprite_GetResourceSlot(slotIndex);
  if ( !slot )
    return 0;
  return slot->line_step_word;
}

//----- (0040C1F0) --------------------------------------------------------
void  TextSprite_BuildOrLoadCachedFont(int slotIndex, _BYTE *fontData, int a3, char a4, DWORD allocContext)
{
  TextSpriteResourceSlotRecord *slot;
  int v6; // edx
  int existingSpriteSet; // ecx
  _BYTE *fontCursor; // eax
  unsigned __int8 *checksum; // ebx
  unsigned __int16 checksumSum; // cx
  int i; // edx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int cacheFileExists; // eax
  _DWORD *spriteSet; // eax
  _DWORD *loadedSpriteSet; // ecx
  char *destCursor; // edi
  char *srcCursor; // esi
  char firstChar; // al
  char secondChar; // al
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  _DWORD *cachedSpriteSet; // eax
  unsigned __int8 v26[1024]; // [esp+0h] [ebp-4E0h] BYREF
  CHAR cacheFilename[100]; // [esp+400h] [ebp-E0h] BYREF
  char sourceStemCopy[100]; // [esp+464h] [ebp-7Ch] BYREF
  _BYTE *fontBytes; // [esp+4C8h] [ebp-18h]

  fontBytes = fontData;
  slot = TextSprite_GetResourceSlot(slotIndex);
  Debug_Log(a3, a4, allocContext, (int)a_conformfont2p);
  if ( !slot )
    return;
  existingSpriteSet = slot->cached_sprite_set;
  if ( existingSpriteSet )
  {
    nfree_(existingSpriteSet);
    slot->cached_sprite_set = 0;
  }
  fontCursor = fontBytes;
  LOBYTE(checksum) = 0;
  checksumSum = 0;
  for ( i = 0; i < 768; ++i )
  {
    BYTE1(checksum) = *fontCursor;
    LOBYTE(checksum) = *fontCursor++ ^ (unsigned __int8)checksum;
    checksumSum += BYTE1(checksum);
  }
  sprintf_(cacheFilename, "cache\\%02x%02x%04x.s32", slotIndex, (unsigned __int8)checksum, checksumSum);
  Res_ProbeGfxFileExists(cacheFilename, v13, allocContext, v12);
  if ( cacheFileExists )
  {
    cachedSpriteSet = (_DWORD *)Mem_Alloc(4112, v14, (char)checksum, allocContext);
    if ( cachedSpriteSet )
      cachedSpriteSet = DLXSpriteSet_Load(cachedSpriteSet, (char)checksum);
    slot->cached_sprite_set = (int)(uintptr_t)cachedSpriteSet;
  }
  else
  {
    spriteSet = (_DWORD *)Mem_Alloc(4112, v14, (char)checksum, allocContext);
    loadedSpriteSet = spriteSet;
    if ( spriteSet )
      loadedSpriteSet = DLXSpriteSet_Load(spriteSet, (char)checksum);
    destCursor = sourceStemCopy;
    srcCursor = (char *)slot->source_stem;
    slot->cached_sprite_set = (int)(uintptr_t)loadedSpriteSet;
    do
    {
      firstChar = *srcCursor;
      *destCursor = *srcCursor;
      if ( !firstChar )
        break;
      secondChar = srcCursor[1];
      srcCursor += 2;
      destCursor[1] = secondChar;
      destCursor += 2;
    }
    while ( secondChar );
    checksum = v26;
    cacheFilename[strlen(sourceStemCopy) + 97] = 'p';
    Palette_LoadFromQueryHandle((int)fontBytes, 12 * slotIndex);
    DLXSpriteSet_DrawText(slot->cached_sprite_set, -1, v22, v26);
    DLXSpriteSet_Save((int *)(uintptr_t)(unsigned int)slot->cached_sprite_set, (int)cacheFilename, (char)v26);
  }
  Debug_Log(v23, (char)checksum, allocContext, (int)a_end);
}
// 40C21A: variable 'v6' is possibly undefined
// 40C364: variable 'v24' is possibly undefined
// 40C27C: variable 'v13' is possibly undefined
// 40C27C: variable 'v12' is possibly undefined
// 40C283: variable 'v15' is possibly undefined
// 40C28E: variable 'v14' is possibly undefined
// 40C32B: variable 'v22' is possibly undefined
// 40C347: variable 'v23' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 511EC8: using guessed type char *off_511EC8;
// 511ECC: using guessed type int dword_511ECC[];

//----- (0040C3A0) --------------------------------------------------------
int  UI_EndDraw(int slotIndex)
{
  TextSpriteResourceSlotRecord *slot;
  int result; // eax

  slot = TextSprite_GetResourceSlot(slotIndex);
  if ( slot && slot->cached_sprite_set )
  {
    nfree_(slot->cached_sprite_set);
    slot->cached_sprite_set = 0;
  }
  result = 3 * slotIndex;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);

//----- (0040C3F0) --------------------------------------------------------
int TextSprite_ReleaseAllResourceSlots()
{
  int slot_index;
  int result; // eax

  result = 0;
  for ( slot_index = 0; slot_index < TEXT_SPRITE_RESOURCE_SLOT_COUNT; ++slot_index )
  {
    result = UI_EndDraw(slot_index);
  }
  return result;
}

//----- (0040C430) --------------------------------------------------------
int  UI_SetTextCursorPosition(int result)
{
  g_UITextCursorGlyphIndex = result;
  return result;
}
// 511EC0: using guessed type int dword_511EC0;

//----- (0040C450) --------------------------------------------------------
char  Str_TitleCase(_BYTE *result, int a2, int a3)
{
  _BYTE *cursor; // esi

  (void)a2;
  (void)a3;
  cursor = result;
  if ( !cursor || !*cursor )
    return (char)(uintptr_t)result;
  strlwr_((char *)cursor);
  while ( cursor && *cursor )
  {
    *cursor = toupper_(*cursor);
    while ( *cursor && *cursor != ' ' )
      ++cursor;
    if ( !*cursor )
      break;
    while ( *cursor == ' ' )
      ++cursor;
  }
  return (char)(uintptr_t)result;
}
// 476253: using guessed type int __fastcall strlwr_(_DWORD, _DWORD);
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (0040C4C0) --------------------------------------------------------
_WORD * Font_ResetGlyphFallbackTable(_WORD *result)
{
  _WORD *tableEnd; // edx

  tableEnd = result + 1536;
  do
  {
    *result = -1;
    result = (_WORD *)((char *)result + 3);
    *((_BYTE *)result - 1) = 0;
  }
  while ( result != tableEnd );
  return result;
}

//----- (0040C4F0) --------------------------------------------------------
int  Font_SetGlyphFallbackEntry(int tableBase, unsigned __int16 glyphId, char flagByte, __int16 fallbackValue)
{
  int result; // eax

  result = 3 * glyphId;
  *(_WORD *)(tableBase + result) = fallbackValue;
  *(_BYTE *)(tableBase + result + 2) = flagByte;
  return result;
}

//----- (0040C510) --------------------------------------------------------
int __cdecl Font_BuildGlyphFallbackChain(int tableBase, char flagByte, unsigned __int16 firstGlyphId, ...)
{
  unsigned __int16 current_id;
  unsigned __int16 fallback_id;
  int result; // eax
  va_list args;

  result = 0;
  current_id = firstGlyphId;
  va_start(args, firstGlyphId);
  while ( 1 )
  {
    if ( current_id == 0xFFFF || current_id == 0xFFFE || *(unsigned __int16 *)(3 * (unsigned int)current_id + tableBase) != 0xFFFF )
      break;
    fallback_id = (unsigned __int16)va_arg(args, unsigned int);
    result = Font_SetGlyphFallbackEntry(tableBase, current_id, flagByte, fallback_id);
    current_id = fallback_id;
  }
  va_end(args);
  return result;
}

//----- (0040C5E0) --------------------------------------------------------
int Font_InitGlyphFallbackTablesForLanguage()
{
  unsigned int i;
  unsigned int base;
  unsigned char language;

  Font_ResetGlyphFallbackTable(&g_TerrainAnimationRemapTable);
  Font_ResetGlyphFallbackTable(&g_SpriteCodeRemapTable);
  Font_ResetGlyphFallbackTable(g_FontGlyphFallbackTable3);
  for ( i = 0; i < 0x400u; ++i )
    g_Font_GlyphRemapTable[i] = i;
  Font_BuildGlyphFallbackChain((int)&g_SpriteCodeRemapTable, 15, 0x24Bu, 0x24Cu, 0x24Du, 0x24Eu, 0x24Fu, 0x250u, 0x251u, 0x252u, 0x24Bu);
  for ( base = 0xDF; base <= 0xEA; ++base )
  {
    Font_BuildGlyphFallbackChain(
      (int)&g_SpriteCodeRemapTable,
      15,
      (unsigned __int16)base,
      (unsigned __int16)(base + 0x0C),
      (unsigned __int16)(base + 0x18),
      (unsigned __int16)(base + 0x24),
      (unsigned __int16)(base + 0x30),
      (unsigned __int16)(base + 0x3C),
      (unsigned __int16)(base + 0x48),
      (unsigned __int16)(base + 0x54),
      (unsigned __int16)(base + 0x60),
      (unsigned __int16)(base + 0x6C),
      (unsigned __int16)(base + 0x78),
      (unsigned __int16)(base + 0x84),
      (unsigned __int16)(base + 0x90),
      (unsigned __int16)(base + 0x9C),
      (unsigned __int16)(base + 0xA8),
      (unsigned __int16)(base + 0xB4),
      (unsigned __int16)base);
  }
  for ( i = 6; i <= 9; ++i )
  {
    base = 0x253 + 8 * i;
    Font_BuildGlyphFallbackChain(
      (int)&g_SpriteCodeRemapTable,
      15,
      (unsigned __int16)base,
      (unsigned __int16)(base + 1),
      (unsigned __int16)(base + 2),
      (unsigned __int16)(base + 3),
      (unsigned __int16)(base + 4),
      (unsigned __int16)(base + 5),
      (unsigned __int16)(base + 6),
      (unsigned __int16)(base + 7),
      (unsigned __int16)base);
  }

  language = *(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET);
  switch ( language )
  {
    case 0:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          15,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)(base + 0x40),
          (unsigned __int16)(base + 0x48),
          (unsigned __int16)(base + 0x50),
          (unsigned __int16)(base + 0x58),
          (unsigned __int16)(base + 0x60),
          (unsigned __int16)(base + 0x68),
          (unsigned __int16)(base + 0x70),
          (unsigned __int16)(base + 0x78),
          (unsigned __int16)base);
      }
      break;
    case 1:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          15,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)base);
      }
      break;
    case 2:
      for ( base = 0x19F; base <= 0x1A6; ++base )
      {
        Font_BuildGlyphFallbackChain(
          (int)&g_SpriteCodeRemapTable,
          10,
          (unsigned __int16)base,
          (unsigned __int16)(base + 8),
          (unsigned __int16)(base + 0x10),
          (unsigned __int16)(base + 0x18),
          (unsigned __int16)(base + 0x20),
          (unsigned __int16)(base + 0x28),
          (unsigned __int16)(base + 0x30),
          (unsigned __int16)(base + 0x38),
          (unsigned __int16)(base + 0x40),
          (unsigned __int16)(base + 0x48),
          (unsigned __int16)(base + 0x50),
          (unsigned __int16)(base + 0x58),
          (unsigned __int16)(base + 0x60),
          (unsigned __int16)(base + 0x68),
          (unsigned __int16)(base + 0x70),
          (unsigned __int16)(base + 0x78),
          (unsigned __int16)base);
      }
      break;
    default:
      break;
  }

  for ( i = 0; i <= 5; ++i )
  {
    base = 0x253 + 8 * i;
    Font_BuildGlyphFallbackChain(
      (int)&g_TerrainAnimationRemapTable,
      10,
      (unsigned __int16)base,
      (unsigned __int16)(base + 1),
      (unsigned __int16)(base + 2),
      (unsigned __int16)(base + 3),
      (unsigned __int16)(base + 4),
      (unsigned __int16)(base + 5),
      (unsigned __int16)(base + 6),
      (unsigned __int16)(base + 7),
      (unsigned __int16)base);
  }
  if ( language == 2 )
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0xBBu, 0x2BDu, 0x2BEu, 0x2BFu, 0x2C0u, 0x2C1u, 0x2C2u, 0xBBu);
  if ( language )
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 15, 0x304u, 0x305u, 0x306u, 0x307u, 0x308u, 0x309u, 0x30Au, 0x303u, 0xFFFFu);
  else
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 5, 0x303u, 0x304u, 0x305u, 0x306u, 0x307u, 0x308u, 0x309u, 0x30Au, 0x24u, 0xFFFFu);

  if ( language == 0 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x313u, 0x314u, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x31Bu, 0x31Cu, 0x31Du, 0x31Eu, 0x31Fu, 0x320u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x321u, 0x322u, 0x323u, 0x324u, 0x325u, 0x326u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x327u, 0x328u, 0x329u, 0x32Au, 0x32Bu, 0x32Cu, 0x32Du, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x32Eu, 0x32Fu, 0x330u, 0x331u, 0x332u, 0xFFFEu);
  }
  else if ( language == 1 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0x313u, 0x314u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0x31Bu, 0x31Cu, 0x31Du, 0x31Eu, 0xFFFEu);
  }
  else if ( language == 2 )
  {
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x30Bu, 0x30Cu, 0x30Du, 0x30Eu, 0x30Fu, 0x310u, 0x311u, 0x312u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x313u, 0x314u, 0x315u, 0x316u, 0x317u, 0x318u, 0x319u, 0x31Au, 0x31Bu, 0x31Cu, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x31Du, 0x31Eu, 0x31Fu, 0x320u, 0x321u, 0x322u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x323u, 0x324u, 0x325u, 0x326u, 0x327u, 0x328u, 0x329u, 0xFFFEu);
    Font_BuildGlyphFallbackChain((int)&g_TerrainAnimationRemapTable, 10, 0x32Au, 0x32Bu, 0x32Cu, 0x32Du, 0x32Eu, 0x32Fu, 0x330u, 0x331u, 0x332u, 0x333u, 0xFFFEu);
  }

  return language;
}
// 5202E4: using guessed type int gameData;
// 520738: using guessed type __int16 word_520738;
// 521338: using guessed type __int16 word_521338;
// 521F38: using guessed type _WORD word_521F38[1528];
// 522B38: using guessed type __int16 word_522B38[223];

//----- (0040CE70) --------------------------------------------------------
int  MiniMap_BuildTileColorTables(unsigned int themeIndex, int a2)
{
  unsigned char *base0;
  unsigned char *base1;
  unsigned char *base2;

  (void)a2;

  if ( themeIndex )
  {
    if ( themeIndex <= 1 )
    {
      g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTerrainColorTableVariant1;
    }
    else if ( themeIndex == 2 )
    {
      g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTerrainColorTableVariant2;
    }
  }
  else
  {
    g_MiniMapTerrainColorTable_523F50 = (int)(uintptr_t)g_MiniMapTileColorTableTheme0;
  }
  base0 = (unsigned char *)g_MiniMapTileColorTableTheme0;
  base1 = (unsigned char *)g_MiniMapTerrainColorTableVariant1;
  base2 = (unsigned char *)g_MiniMapTerrainColorTableVariant2;

#define MINIMAP_FILL(base, offset, count, value) memset((base) + (offset), (value), (count))
  MINIMAP_FILL(base0, 0x000, 0x004, 0xB7);
  MINIMAP_FILL(base0, 0x004, 0x003, 0x97);
  MINIMAP_FILL(base0, 0x007, 0x001, 0x27);
  MINIMAP_FILL(base0, 0x008, 0x008, 0x97);
  MINIMAP_FILL(base0, 0x010, 0x010, 0xB7);
  MINIMAP_FILL(base0, 0x020, 0x00D, 0x97);
  MINIMAP_FILL(base0, 0x02D, 0x074, 0xB9);
  MINIMAP_FILL(base0, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base0, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base0, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base0, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base0, 0x2C3, 0x004, 0xB7);
  MINIMAP_FILL(base0, 0x2C7, 0x005, 0x97);
  MINIMAP_FILL(base0, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base0, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base0, 0x2EF, 0x003, 0xB7);
  MINIMAP_FILL(base0, 0x2F2, 0x003, 0x97);
  MINIMAP_FILL(base0, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base0, 0x303, 0x008, 0x97);

  MINIMAP_FILL(base1, 0x000, 0x004, 0x4C);
  MINIMAP_FILL(base1, 0x004, 0x003, 0x97);
  MINIMAP_FILL(base1, 0x007, 0x001, 0x27);
  MINIMAP_FILL(base1, 0x008, 0x008, 0x97);
  MINIMAP_FILL(base1, 0x010, 0x010, 0x4C);
  MINIMAP_FILL(base1, 0x020, 0x00D, 0x97);
  MINIMAP_FILL(base1, 0x02D, 0x074, 0xB9);
  MINIMAP_FILL(base1, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base1, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base1, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base1, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base1, 0x2C3, 0x004, 0x4C);
  MINIMAP_FILL(base1, 0x2C7, 0x005, 0x97);
  MINIMAP_FILL(base1, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base1, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base1, 0x2EF, 0x003, 0x4C);
  MINIMAP_FILL(base1, 0x2F2, 0x003, 0x97);
  MINIMAP_FILL(base1, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base1, 0x303, 0x008, 0x97);

  MINIMAP_FILL(base2, 0x000, 0x004, 0x7F);
  MINIMAP_FILL(base2, 0x004, 0x003, 0xC0);
  MINIMAP_FILL(base2, 0x007, 0x001, 0xC4);
  MINIMAP_FILL(base2, 0x008, 0x008, 0xC0);
  MINIMAP_FILL(base2, 0x010, 0x010, 0x7F);
  MINIMAP_FILL(base2, 0x020, 0x00D, 0xC0);
  MINIMAP_FILL(base2, 0x02D, 0x074, 0x80);
  MINIMAP_FILL(base2, 0x0A1, 0x019, 0xCC);
  MINIMAP_FILL(base2, 0x0BA, 0x024, 0xCA);
  MINIMAP_FILL(base2, 0x0DE, 0x1D6, 0x93);
  MINIMAP_FILL(base2, 0x2B4, 0x00F, 0xCC);
  MINIMAP_FILL(base2, 0x2C3, 0x004, 0x7F);
  MINIMAP_FILL(base2, 0x2C7, 0x005, 0xC0);
  MINIMAP_FILL(base2, 0x2CC, 0x01E, 0x93);
  MINIMAP_FILL(base2, 0x2EA, 0x005, 0xCA);
  MINIMAP_FILL(base2, 0x2EF, 0x003, 0x7F);
  MINIMAP_FILL(base2, 0x2F2, 0x003, 0xC0);
  MINIMAP_FILL(base2, 0x2F5, 0x00E, 0x93);
  MINIMAP_FILL(base2, 0x303, 0x008, 0xC0);
#undef MINIMAP_FILL

  return 0;
}
// 40CEAC: variable 'v2' is possibly undefined
// 40CEC0: variable 'v3' is possibly undefined
// 40CED4: variable 'v4' is possibly undefined
// 40CEE8: variable 'v5' is possibly undefined
// 40CEFC: variable 'v6' is possibly undefined
// 40CF10: variable 'v7' is possibly undefined
// 40CF24: variable 'v8' is possibly undefined
// 40CF38: variable 'v9' is possibly undefined
// 40CF4C: variable 'v10' is possibly undefined
// 40CF60: variable 'v11' is possibly undefined
// 40CF74: variable 'v12' is possibly undefined
// 40CF88: variable 'v13' is possibly undefined
// 40CF9C: variable 'v14' is possibly undefined
// 40CFB0: variable 'v15' is possibly undefined
// 40CFC4: variable 'v16' is possibly undefined
// 40CFD8: variable 'v17' is possibly undefined
// 40CFEC: variable 'v18' is possibly undefined
// 40D000: variable 'v19' is possibly undefined
// 40D014: variable 'v20' is possibly undefined
// 40D028: variable 'v21' is possibly undefined
// 40D03C: variable 'v22' is possibly undefined
// 40D050: variable 'v23' is possibly undefined
// 40D064: variable 'v24' is possibly undefined
// 40D078: variable 'v25' is possibly undefined
// 40D08C: variable 'v26' is possibly undefined
// 40D0A0: variable 'v27' is possibly undefined
// 40D0B4: variable 'v28' is possibly undefined
// 40D0C8: variable 'v29' is possibly undefined
// 40D0DC: variable 'v30' is possibly undefined
// 40D0F0: variable 'v31' is possibly undefined
// 40D104: variable 'v32' is possibly undefined
// 40D118: variable 'v33' is possibly undefined
// 40D12C: variable 'v34' is possibly undefined
// 40D140: variable 'v35' is possibly undefined
// 40D154: variable 'v36' is possibly undefined
// 40D168: variable 'v37' is possibly undefined
// 40D17C: variable 'v38' is possibly undefined
// 40D190: variable 'v39' is possibly undefined
// 40D1A4: variable 'v40' is possibly undefined
// 40D1B8: variable 'v41' is possibly undefined
// 40D1CC: variable 'v42' is possibly undefined
// 40D1E0: variable 'v43' is possibly undefined
// 40D1F4: variable 'v44' is possibly undefined
// 40D208: variable 'v45' is possibly undefined
// 40D21C: variable 'v46' is possibly undefined
// 40D230: variable 'v47' is possibly undefined
// 40D244: variable 'v48' is possibly undefined
// 40D258: variable 'v49' is possibly undefined
// 40D26C: variable 'v50' is possibly undefined
// 40D280: variable 'v51' is possibly undefined
// 40D294: variable 'v52' is possibly undefined
// 40D2A8: variable 'v53' is possibly undefined
// 40D2BC: variable 'v54' is possibly undefined
// 40D2D0: variable 'v55' is possibly undefined
// 40D2E4: variable 'v56' is possibly undefined
// 40D2F8: variable 'v57' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 523F50: using guessed type int dword_523F50;

//----- (0040D330) --------------------------------------------------------
int  MiniMap_CreateSurface(DWORD allocContext)
{
  _DWORD *Surface; // eax
  int minimap_frame_sprite; // eax

  g_MiniMapPixelsPerTile_523F54 = 2;
  if ( *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) * *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) <= 2500 )
    g_MiniMapPixelsPerTile_523F54 = 4;
  g_MiniMapRectWidth_523348 = (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_WIDTH_TILES_OFFSET) + 14;
  g_MiniMapRectHeight_52334A = *(_WORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) * (unsigned __int8)g_MiniMapPixelsPerTile_523F54 + 14;
  g_MiniMapRectTop_523346 = 16;
  g_MiniMapRectLeft_523344 = 608 - g_MiniMapRectWidth_523348;
  Surface = (_DWORD *)Mem_Alloc(188, 16, g_MiniMapRectWidth_523348, allocContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, g_MiniMapRectWidth_523348, g_MiniMapRectHeight_52334A);
  g_MiniMapSurface_52334C = (int)Surface;
  g_RenderDevice = Surface;
  minimap_frame_sprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 4);
  Compat_RenderDeviceDrawMenuSprite(0, 0, minimap_frame_sprite, 1u);
  return MiniMap_BuildTileColorTables(MAP_THEME_INDEX, 0);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202BC: using guessed type int dword_5202BC;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523348: using guessed type __int16 word_523348;
// 52334A: using guessed type __int16 word_52334A;
// 52334C: using guessed type int dword_52334C;
// 523F54: using guessed type char byte_523F54;

//----- (0040D430) --------------------------------------------------------
int __thiscall MiniMap_DestroySurface(void *this)
{
  int result; // eax

  (void)this;
  result = 0;
  if ( g_MiniMapSurface_52334C )
    Compat_InvokeCompactSurfaceDestructor(g_MiniMapSurface_52334C, 2);
  return result;
}
// 52334C: using guessed type int dword_52334C;

//----- (0040D560) --------------------------------------------------------
int  MiniMap_BlitDirtyRectAndDrawViewportBox(
        int result,
        unsigned __int16 top,
        unsigned __int16 bottom,
        unsigned __int16 right)
{
  if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX)
    && right >= (unsigned __int16)g_MiniMapRectLeft_523344
    && top <= (unsigned __int16)g_MiniMapRectTop_523346 + (unsigned __int16)g_MiniMapRectHeight_52334A )
  {
    if ( (unsigned __int16)result < (unsigned __int16)g_MiniMapRectLeft_523344 )
      LOWORD(result) = g_MiniMapRectLeft_523344;
    if ( bottom > (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346 )
      bottom = g_MiniMapRectHeight_52334A + g_MiniMapRectTop_523346 - 1;
    Render_FillRect(
      (_DWORD *)g_MiniMapSurface_52334C,
      g_RenderDevice,
      (unsigned __int16)(top - g_MiniMapRectTop_523346),
      (unsigned __int16)(result - g_MiniMapRectLeft_523344),
      right - g_MiniMapRectLeft_523344,
      bottom - g_MiniMapRectTop_523346,
      result,
      top);
    {
      _DWORD *surface; // esi
      unsigned __int16 right; // cx
      unsigned __int16 top; // bx
      unsigned __int16 left; // dx
      unsigned __int16 bottom; // stack

      surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
      if ( !surface )
        return result;
      right = (unsigned __int16)(g_MiniMapRectLeft_523344 + 7 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (*(_WORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9));
      top = (unsigned __int16)(g_MiniMapRectTop_523346 + 6 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_VIEW_TOP_OFFSET));
      left = (unsigned __int16)(g_MiniMapRectLeft_523344 + 6 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * *(_WORD *)(gameData + MAP_VIEW_LEFT_OFFSET));
      bottom = (unsigned __int16)(g_MiniMapRectTop_523346 + 7 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (*(_WORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7));
      Surface_DrawRectOutline((unsigned __int16 *)surface, left, right, top, bottom, 0x4Cu);
      return result;
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 52334A: using guessed type __int16 word_52334A;
// 52334C: using guessed type int dword_52334C;
// 523F54: using guessed type char byte_523F54;
