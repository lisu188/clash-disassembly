/* Generated from src/recovered/battle/0042CB50_battle.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (0042E9E0) --------------------------------------------------------
DWORD  Battle_RunTacticalCombat(
        __int16 *attackerGroupArg,
        __int16 *defenderGroupArg,
        int attackerControlArg,
        unsigned __int8 *buildingRecordArg,
        DWORD logCtx,
        int defenderControlFlag)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  unsigned __int8 backgroundVariant; // al
  _DWORD *backgroundSpriteSet; // eax
  _DWORD *buttonsSpriteSet; // eax
  int v12; // ecx
  _DWORD *panelIconSpriteSet; // eax
  int v14; // ecx
  _DWORD *casualtySpriteSet; // eax
  _DWORD *uiFrameSpriteSet; // eax
  int SpriteForChar; // eax
  int uiFrameSprite1; // eax
  int uiFrameSprite2; // eax
  int uiFrameSprite3; // eax
  int v21; // edx
  unsigned int v22; // ecx
  unsigned __int8 defenderPlayerIndex; // al
  int otherMapX; // eax
  int otherMapY; // ecx
  int attackerMapX; // edx
  int v27; // ecx
  int rowCount; // eax
  int i; // edx
  int colCount; // eax
  int j; // edx
  int colTileValue; // ecx
  int v33; // ecx
  int k; // eax
  int v35; // ecx
  int v36; // ecx
  unsigned __int8 *buildingRecordPtr; // esi
  int activeRowBase; // edx
  __int16 *defenderGroupPtr; // esi
  signed int defenderCount; // eax
  DWORD defenderUnitCount; // ebp
  char *defenderUnitArray; // esi
  char *attackerUnitArray; // edi
  char attackerViewportStart; // al
  char defenderViewportStart; // al
  int defenderCoordBase; // ecx
  int v47; // ebx
  int v48; // edx
  int v49; // ecx
  BOOL prevSideWasAi; // edi
  int v51; // ecx
  DWORD phaseFlag; // ebp
  int v53; // ecx
  int gateColIndex; // esi
  signed int turnResult; // esi
  int m; // eax
  int unitRecordPtr; // edx
  int unitType; // ecx
  int v59; // ecx
  DWORD battleOutcome; // ebp
  int v61; // ecx
  char v62; // bl
  unsigned __int8 *buildingRecordForSave; // edi
  int v64; // ecx
  int v65; // ecx
  int v66; // ecx
  int playerData; // eax
  int v69; // ecx
  char mapFileNameBuffer[100]; // [esp+Ch] [ebp-A8h] BYREF
  int outcomeTextStrings[3]; // [esp+70h] [ebp-44h]
  int v72; // [esp+7Ch] [ebp-38h] BYREF
  int mapFileHandle; // [esp+80h] [ebp-34h] BYREF
  unsigned __int8 *buildingRecord; // [esp+84h] [ebp-30h]
  int attackerControlFlag; // [esp+88h] [ebp-2Ch]
  int savedMusicHandle; // [esp+8Ch] [ebp-28h]
  int (*savedRenderHook)(); // [esp+90h] [ebp-24h]
  int savedPlayerIndex; // [esp+94h] [ebp-20h]
  int savedResourceHandle; // [esp+98h] [ebp-1Ch]
  int attackerSquadCount; // [esp+9Ch] [ebp-18h]
  __int16 *attackerGroup; // [esp+A0h] [ebp-14h]
  __int16 *defenderGroup; // [esp+A4h] [ebp-10h]
  const char *battle_background_resource;
  int battle_map_bytes_read;

  attackerGroup = attackerGroupArg;
  defenderGroup = defenderGroupArg;
  buildingRecord = buildingRecordArg;
  attackerControlFlag = attackerControlArg;
  Diagnostics_ResetFrameDumpOnBattleEnter();
  Debug_Log(attackerControlArg, (char)buildingRecordArg, logCtx, (int)aBattle_0);
  Battle_StoreLastOutcomeValue(1);
  Debug_Log(v6, (char)buildingRecordArg, logCtx, (int)aNewBattle_0);
  savedResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, (char *)UnitBattle_InitBattleScreenFrame == (char *)Render_DefaultRH);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())UnitBattle_InitBattleScreenFrame;
  Debug_Log(v7, (char)buildingRecordArg, logCtx, (int)aSetrhS08x_8);
  savedMusicHandle = Audio_PauseMusicAndPlayLoopedSound(aBattle_1, 1);
  DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
  backgroundVariant = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
  battle_background_resource = 0;
  if ( !backgroundVariant )
    battle_background_resource = aBattleBat_bkg1;
  else if ( backgroundVariant <= 1u )
    battle_background_resource = aBattleBat_bkg2;
  else if ( backgroundVariant == 2 )
    battle_background_resource = aBattleBat_bkg3;
  if ( battle_background_resource )
  {
    backgroundSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( backgroundSpriteSet )
      backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, battle_background_resource);
  }
  else
  {
    backgroundSpriteSet = 0;
  }
  g_BattleHudSprites = (int)backgroundSpriteSet;
  buttonsSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( buttonsSpriteSet )
    buttonsSpriteSet = DLXSpriteSet_Load(buttonsSpriteSet, aBattleButtons_);
  g_BattleButtonsSpriteSet = (int)buttonsSpriteSet;
  panelIconSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( panelIconSpriteSet )
    panelIconSpriteSet = DLXSpriteSet_Load(panelIconSpriteSet, aBattleFr_anim_);
  g_BattleUnitPanelIconSpriteSet = (int)panelIconSpriteSet;
  casualtySpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( casualtySpriteSet )
    casualtySpriteSet = DLXSpriteSet_Load(casualtySpriteSet, aBattleTrupki_s);
  g_BattleCasualtySpriteSet = (int)casualtySpriteSet;
  g_UnitActionTooltipLastShownAction = -1;
  g_UnitFadeAnimUnitIndex = -1;
  g_ActiveUnitMoveTileIndex = -1;
  g_UnitBattleExitButtonOverlaySpriteIndex = (unsigned __int8)g_LanguageIndex + 13;
  g_UnitBattleAnimatingUnitIndex = -1;
  uiFrameSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( uiFrameSpriteSet )
    uiFrameSpriteSet = DLXSpriteSet_Load(uiFrameSpriteSet, aBattleFrame_s3);
  g_ActiveUiSpriteSet = (int)uiFrameSpriteSet;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_resources", g_ActiveUiSpriteSet, g_BattleHudSprites, g_BattleButtonsSpriteSet, g_BattleUnitPanelIconSpriteSet);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)uiFrameSpriteSet, 0);
  Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  uiFrameSprite1 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 1);
  Compat_RenderDeviceDrawMenuSprite(0, 0, uiFrameSprite1, 1);
  uiFrameSprite2 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 2);
  Compat_RenderDeviceDrawMenuSprite(243, 0, uiFrameSprite2, 1);
  uiFrameSprite3 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 3);
  Compat_RenderDeviceDrawMenuSprite(243, 0, uiFrameSprite3, 1);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_frame_draw", g_ActiveUiSpriteSet, SpriteForChar, uiFrameSprite1, uiFrameSprite2);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_backdrop", 0, 0, 0, 0);
  g_MapData = (int)nmalloc_(0xF7C, 4);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_state_alloc", g_MapData, 0xF7C, 0, 0);
  if ( !g_MapData )
  {
    Debug_Log(0, 211, (DWORD)&g_MainRenderDevice, (int)aNotEnoughMem_9);
    App_RequestQuit((int)aNotEnoughMe_10);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_player_state", g_MapData, (int)attackerGroup, (int)defenderGroup, 0);
  savedPlayerIndex = g_CurrentPlayerIndex;
  g_CurrentPlayerIndex = *((unsigned __int8 *)attackerGroup + 4);
  *(_DWORD *)(g_MapData + 836) = g_CurrentPlayerIndex;
  if ( defenderGroup )
    defenderPlayerIndex = *((_BYTE *)defenderGroup + 4);
  else
    defenderPlayerIndex = buildingRecord[2];
  *(_DWORD *)(g_MapData + 840) = defenderPlayerIndex;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_players", *(_DWORD *)(g_MapData + 836), *(_DWORD *)(g_MapData + 840), 0, 0);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 836) + gameData + 140077) = 0;
  *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 840) + 140077) = 0;
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 836) + gameData + 140073) = 0;
  *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 840) + 140073) = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_player_counters", *(_DWORD *)(g_MapData + 836), *(_DWORD *)(g_MapData + 840), 0, 0);
  if ( *((_BYTE *)attackerGroup + 720) )
  {
    *(_DWORD *)(g_MapData + 844) = *((unsigned __int8 *)attackerGroup + 4);
  }
  else if ( defenderGroup && *((_BYTE *)defenderGroup + 720) )
  {
    *(_DWORD *)(g_MapData + 844) = *((unsigned __int8 *)defenderGroup + 4);
  }
  else
  {
    *(_DWORD *)(g_MapData + 844) = -1;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_castle_owner", *(_DWORD *)(g_MapData + 844), 0, 0, 0);
  if ( defenderGroup )
    otherMapX = *defenderGroup;
  else
    otherMapX = *buildingRecord;
  if ( defenderGroup )
    otherMapY = defenderGroup[1];
  else
    otherMapY = buildingRecord[1];
  attackerMapX = *attackerGroup;
  if ( attackerMapX >= otherMapX )
  {
    if ( attackerMapX <= otherMapX )
    {
      if ( attackerGroup[1] >= otherMapY )
      {
        otherMapY = 1;
        g_DefenderStartsOnLeft = 1;
        g_AttackerStartsOnLeft = 0;
      }
      else
      {
        g_AttackerStartsOnLeft = 1;
        g_DefenderStartsOnLeft = 0;
      }
    }
    else
    {
      g_DefenderStartsOnLeft = 1;
      g_AttackerStartsOnLeft = 0;
    }
  }
  else
  {
    otherMapY = 0;
    g_AttackerStartsOnLeft = 1;
    g_DefenderStartsOnLeft = 0;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_orientation", g_AttackerStartsOnLeft, g_DefenderStartsOnLeft, otherMapX, otherMapY);
  if ( defenderGroup )
    BattleMapFileName(mapFileNameBuffer, *defenderGroup, defenderGroup[1]);
  else
    BattleMap_GetOutcomeVariantFileName(mapFileNameBuffer, g_DefenderStartsOnLeft, buildingRecord[1]);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_name", g_AttackerStartsOnLeft, g_DefenderStartsOnLeft, otherMapY, 0);
  mapFileHandle = FileSystem_ResolveReadPath(mapFileNameBuffer, 1);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_open", mapFileHandle, 0, 0, 0);
  battle_map_bytes_read = Compat_QueryRead(mapFileHandle, (void *)(uintptr_t)(unsigned int)g_MapData, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_read", mapFileHandle, battle_map_bytes_read, 0x320, 0);
  Compat_FileSystemQueryRelease(v27, &mapFileHandle);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_close", mapFileHandle, 0, 0, 0);
  rowCount = 0;
  for ( i = 0; i < 800; i += 40 )
  {
    if ( *(__int16 *)(g_MapData + i) == -1 )
      break;
    ++rowCount;
  }
  *(_DWORD *)(g_MapData + 804) = rowCount;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_row_count", rowCount, i, *(__int16 *)g_MapData, 0);
  colCount = 0;
  for ( j = 0; j < 40; j += 2 )
  {
    colTileValue = *(__int16 *)(g_MapData + j);
    if ( colTileValue == -1 )
      break;
    ++colCount;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_col_count", colCount, j, *(__int16 *)g_MapData, 0);
  *(_DWORD *)(g_MapData + 800) = 7;
  *(_DWORD *)(g_MapData + 808) = 0;
  *(_DWORD *)(g_MapData + 812) = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_dims_store", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0x5FE), -1, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_overlay_clear", g_MapData, 0x5FE, 0x320, 0);
  for ( k = UNIT_STACK_SLOT_STRIDE; k <= 0x2AA; k += UNIT_STACK_SLOT_STRIDE )
    *(_WORD *)(g_MapData + k + 0x335) = -1;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_slot_sentinels", k, 0, 0, 0);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0xC3E), 0, 0x190);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0xDCE), 0, 0x190);
  *(_DWORD *)(g_MapData + 828) = -1;
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0x91E), -1, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_grid_clears", g_MapData, *(_DWORD *)(g_MapData + 828), 0, 0);
  buildingRecordPtr = buildingRecord;
  *(_DWORD *)(g_MapData + 816) = 5;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_pathing", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), *(_DWORD *)(g_MapData + 816), 0);
  UnitBattle_InitPathingTables();
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_pathing", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), g_TilePassabilityMask[0], 0);
  if ( buildingRecordPtr )
    Battle_LoadWallSegmentsFromBuildingRecord((int)buildingRecordPtr);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_building_setup", (int)(uintptr_t)buildingRecordPtr, *(_DWORD *)(g_MapData + 848), 0, 0);
  *(_DWORD *)(g_MapData + 848) = buildingRecord == 0;
  g_RenderDevice = &g_MainRenderDevice;
  UIWidgetTable_InitDrawStates(g_UnitBattleActionWidgetTable);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_ui_sync", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_first_grid_draw", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  *(_DWORD *)(g_MapData + 824) = 0;
  *(_DWORD *)(g_MapData + 832) = 0;
  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    for ( ; ; ++*(_DWORD *)(g_MapData + 824) )
    {
      if ( *(_DWORD *)(g_MapData + 824) >= *(_DWORD *)(g_MapData + 804) )
        App_RequestQuit((int)aBattleActiveTi);
      activeRowBase = g_MapData + 20 * *(_DWORD *)(g_MapData + 824);
      if ( *(_BYTE *)(activeRowBase + 3534) )
        break;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_init_after_active_tile", *(_DWORD *)(g_MapData + 824), activeRowBase, *(_BYTE *)(activeRowBase + 3534), 0);
    *(_DWORD *)(g_MapData + 832) = *(char *)(*(_DWORD *)(g_MapData + 828) + activeRowBase + 3134);
    Diagnostics_TraceWorldMapActionEvent("battle_init_after_active_cost", *(_DWORD *)(g_MapData + 832), *(_DWORD *)(g_MapData + 828), 0, 0);
  }
  else
  {
    Diagnostics_TraceWorldMapActionEvent("battle_init_no_active_gate", *(_DWORD *)(g_MapData + 824), *(_DWORD *)(g_MapData + 828), 0, 0);
  }
  defenderGroupPtr = defenderGroup;
  attackerSquadCount = Unit_GetSquadCount((int)attackerGroup);
  if ( defenderGroupPtr )
    defenderCount = Unit_GetSquadCount((int)defenderGroupPtr);
  else
    defenderCount = Building_CountGarrison((int)buildingRecord);
  defenderUnitCount = defenderCount;
  if ( defenderGroup )
    defenderUnitArray = (char *)(defenderGroup + 3);
  else
    defenderUnitArray = (char *)(buildingRecord + 18);
  attackerUnitArray = (char *)(attackerGroup + 3);
  Battle_DeploySideUnitsByRoleBuckets((char *)attackerGroup + 6, attackerSquadCount, defenderUnitArray, g_AttackerStartsOnLeft, defenderCount);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_deploy_attacker",
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 836)),
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 840)),
    Diagnostics_CountBattleUnitsTotal(),
    g_SelectedUnitIndex);
  Battle_DeploySideUnitsByRoleBuckets(defenderUnitArray, defenderUnitCount, attackerUnitArray, g_DefenderStartsOnLeft, attackerSquadCount);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_deploy_defender",
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 836)),
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 840)),
    Diagnostics_CountBattleUnitsTotal(),
    g_SelectedUnitIndex);
  Diagnostics_TraceBattleUnitSnapshot("after_deploy_defender");
  UnitBattle_OverrideControllerOrderBits(*(_DWORD *)(g_MapData + 836), attackerControlFlag, defenderControlFlag, *(_DWORD *)(g_MapData + 840));
  if ( g_AttackerStartsOnLeft )
    attackerViewportStart = 0;
  else
    attackerViewportStart = *(_DWORD *)(g_MapData + 804) - 7;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 836) + 3934) = attackerViewportStart;
  if ( g_DefenderStartsOnLeft )
    defenderViewportStart = 0;
  else
    defenderViewportStart = *(_DWORD *)(g_MapData + 804) - 7;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 840) + 3934) = defenderViewportStart;
  defenderCoordBase = 2 * *(_DWORD *)(g_MapData + 840) + g_MapData;
  *(_BYTE *)(defenderCoordBase + 3935) = (*(_DWORD *)(g_MapData + 800) - 7) / 2;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 836) + 3935) = *(_BYTE *)(defenderCoordBase + 3935);
  g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
  g_Battle_ShootModeEnabled = 0;
  g_BattleLoopExitCode = 0;
  g_SelectedUnitIndex = *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_selected_grid_draw",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944),
    0);
  v47 = 20;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_selected_panel", g_SelectedUnitIndex, v48, (int)(uintptr_t)attackerUnitArray, v47);
  UnitBattle_DrawSelectedUnitPanel(0, v48, 20, (int)attackerUnitArray);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_selected_panel", g_SelectedUnitIndex, v48, (int)(uintptr_t)attackerUnitArray, v47);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_palette_ramp", g_MapPalettePtr, (int)(uintptr_t)&g_MainRenderDevice, 20, 0);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_palette_ramp", g_MapPalettePtr, (int)(uintptr_t)&g_MainRenderDevice, 20, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_palette_cache", g_MapPalettePtr, v49, (int)defenderUnitCount, 0);
  Palette_LoadOrBuildBlendLookupTable(aMainmap_3, g_MapPalettePtr, v49, defenderUnitCount);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_palette_cache", g_MapPalettePtr, v49, (int)defenderUnitCount, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_cursor_mode", (int)(uintptr_t)g_RenderState, (int)(uintptr_t)&g_CursorDesc_ActionBusy, g_ActiveCursorDescriptor, 0);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_cursor_mode", (int)(uintptr_t)g_RenderState, (int)(uintptr_t)&g_CursorDesc_ActionBusy, g_ActiveCursorDescriptor, 0);
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_present", (int)(uintptr_t)g_RenderState, g_ActiveCursorDescriptor, 0, 0);
  Render_Present((int)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_present", (int)(uintptr_t)g_RenderState, g_ActiveCursorDescriptor, 0, 0);
  prevSideWasAi = PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) == 0;
  Debug_Log(v51, 20, defenderUnitCount, (int)aStart_0);
  phaseFlag = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_log_units", g_CurrentPlayerIndex, v47, phaseFlag, 0);
  Battle_LogAllUnits(v53, 20, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_log_units", g_CurrentPlayerIndex, v47, phaseFlag, 0);
  while ( 1 )
  {
    gateColIndex = *(_DWORD *)(g_MapData + 828);
    if ( gateColIndex != -1 )
    {
      if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
      {
        *(_DWORD *)(g_MapData + 832) = *(char *)(gateColIndex + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134);
        *(_BYTE *)(*(_DWORD *)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134) = 0;
      }
      else
      {
        *(_BYTE *)(gateColIndex + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134) = *(_BYTE *)(g_MapData + 832);
      }
    }
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    {
      if ( prevSideWasAi )
        UnitBattle_AnimateSelectedUnitPanel(0, v47, prevSideWasAi);
      turnResult = UnitBattle_RunTurnLoop(v47, phaseFlag);
      prevSideWasAi = 0;
    }
    else
    {
      if ( !prevSideWasAi )
        UnitBattle_AnimateSelectedUnitPanel(1, v47, 0);
      prevSideWasAi = 1;
      turnResult = UnitBattle_RunAiTurnForSide(g_CurrentPlayerIndex);
      if ( !Battle_HasUnitsForBothSides() )
        turnResult = 1;
    }
    for ( m = 0; m != 682; m += 31 )
    {
      unitRecordPtr = m + g_MapData;
      unitType = *(__int16 *)(m + g_MapData + 852);
      if ( unitType != -1 )
      {
        v47 = *(unsigned __int8 *)(unitRecordPtr + 854);
        if ( v47 == g_CurrentPlayerIndex )
        {
          *(_BYTE *)(unitRecordPtr + 860) = g_UnitTypeBaseActionPoints_512580[88 * unitType];
          *(_BYTE *)(g_MapData + m + 864) &= 0x8Fu;
        }
      }
    }
    if ( turnResult )
      break;
    playerData = PLAYER_DATA(g_CurrentPlayerIndex);
    if ( *(_DWORD *)(playerData + PLAYER_BATTLE_IDLE_FLAG_OFFSET) )
      *(_DWORD *)(playerData + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET) = 0;
    else
      ++*(_DWORD *)(playerData + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET);
    v69 = g_CurrentPlayerIndex;
    if ( *(int *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET) >= 2 )
      GodAnger(g_CurrentPlayerIndex, g_CurrentPlayerIndex, v47);
    *(_DWORD *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_BATTLE_IDLE_FLAG_OFFSET) = 0;
    *(_DWORD *)(4 * g_CurrentPlayerIndex + g_MapData + 3944) = g_SelectedUnitIndex;
    *(_BYTE *)(g_MapData + 2 * g_CurrentPlayerIndex + 3934) = *(_BYTE *)(g_MapData + 808);
    *(_BYTE *)(g_MapData + 2 * g_CurrentPlayerIndex + 3935) = *(_BYTE *)(g_MapData + 812);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 844) )
    {
      if ( phaseFlag )
      {
        if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
          g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 840);
        else
          g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
        phaseFlag = 0;
      }
      else
      {
        phaseFlag = 1;
      }
    }
    else
    {
      v69 = *(_DWORD *)(g_MapData + 836);
      if ( g_CurrentPlayerIndex == v69 )
        g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 840);
      else
        g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
    }
    g_SelectedUnitIndex = *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
      Battle_NewTurn(v69, v47, phaseFlag);
  }
  UnitBattle_RestoreControllerOrderBits();
  Debug_Log(v59, v47, phaseFlag, (int)aEndOfBattle);
  battleOutcome = 0;
  if ( Battle_HasUnitsForBothSides() )
  {
    Battle_ApplyPeriodicDamageToSideUnits(g_CurrentPlayerIndex);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
      battleOutcome = 1;
    else
      battleOutcome = 2;
  }
  v62 = (char)buildingRecord;
  buildingRecordForSave = buildingRecord;
  HandleBattleResults((int)attackerGroup, (int)defenderGroup, v61, buildingRecord, battleOutcome);
  if ( buildingRecordForSave )
    Battle_SaveWallSegmentsToBuildingRecord((int)buildingRecordForSave);
  if ( battleOutcome == 2 && *(_DWORD *)(PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 840) + gameData + 140051)
    || battleOutcome == 1 && *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(_DWORD *)(g_MapData + 836) + 140051) )
  {
    outcomeTextStrings[0] = (int)g_BattleForcedRetreatOutcomeTexts[0];
    outcomeTextStrings[1] = (int)g_BattleForcedRetreatOutcomeTexts[1];
    outcomeTextStrings[2] = (int)g_BattleForcedRetreatOutcomeTexts[2];
    UI_ShowInfoWindow(outcomeTextStrings[(unsigned __int8)g_LanguageIndex], 0, v64, battleOutcome, (int)&v72, (int)&g_BattleForcedRetreatOutcomeTexts[3]);
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_BattleHudSprites);
  DLXSpriteSet_ReleaseAndClear(&g_BattleButtonsSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_BattleUnitPanelIconSpriteSet);
  DLXSpriteSet_ReleaseAndClear(&g_BattleCasualtySpriteSet);
  nfree_(g_MapData);
  g_MapData = 0;
  Tooltip_ReleaseBackdropSurface();
  TextSprite_ReleaseAllResourceSlots();
  UnitSpriteCache_FreeAllEntries(v66, battleOutcome);
  CSS_EmptySampleCache();
  g_SelectedUnitIndex = -1;
  g_CurrentPlayerIndex = savedPlayerIndex;
  CSS_EmptySampleCache();
  Audio_ResumeMusicAndStopLoopedSound(savedMusicHandle);
  Battle_StoreLastOutcomeValue(0);
  Debug_Log((int)g_RenderHook, v62, battleOutcome, (int)aUnsetrh08x_9);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, savedResourceHandle);
  return battleOutcome;
}
// 42E9E0: could not find valid save-restore pair for ebx
// 42F75C: conditional instruction was optimized away because esi.4==0
// 42EA1B: variable 'v6' is possibly undefined
// 42EA6B: variable 'v7' is possibly undefined
// 42EAAF: variable 'v8' is possibly undefined
// 42EAE9: variable 'v12' is possibly undefined
// 42EB06: variable 'v14' is possibly undefined
// 42EC77: variable 'v21' is possibly undefined
// 42EC86: variable 'v22' is possibly undefined
// 42EE2D: variable 'v27' is possibly undefined
// 42EEEB: variable 'v33' is possibly undefined
// 42EF01: variable 'v35' is possibly undefined
// 42EF29: variable 'v36' is possibly undefined
// 42F2B1: variable 'v48' is possibly undefined
// 42F2D1: variable 'v49' is possibly undefined
// 42F31C: variable 'v51' is possibly undefined
// 42F326: variable 'v53' is possibly undefined
// 42F41D: variable 'v59' is possibly undefined
// 42F46C: variable 'v61' is possibly undefined
// 42F4DC: variable 'v64' is possibly undefined
// 42F531: variable 'v65' is possibly undefined
// 42F547: variable 'v66' is possibly undefined
// 42F755: variable 'v69' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 514B78: using guessed type _DWORD dword_514B78[2];
// 514C99: using guessed type int dword_514C99;
// 514E28: using guessed type int dword_514E28;
// 514E38: using guessed type char *off_514E38[3];
// 514E44: using guessed type int dword_514E44;
// 514E48: using guessed type int dword_514E48;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 532048: using guessed type int g_MapData;
// 53204C: using guessed type int g_BattleHudSprites;
// 532050: using guessed type int dword_532050;
// 532054: using guessed type int dword_532054;
// 532058: using guessed type int dword_532058;
// 53205C: using guessed type int dword_53205C;
// 532064: using guessed type int g_BattleLoopExitCode;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (0042F7C0) --------------------------------------------------------
int  UnitBattle_GetSpriteVerticalOffsetPx(int unitIndex)
{
  return (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(g_MapData + 31 * unitIndex + 852)];
}
// 532048: using guessed type int g_MapData;

//----- (0042F7F0) --------------------------------------------------------
int  UnitBattle_InitUnitFadeAnimation(int unitIndex, int startOffset, int stepRate, int targetOffset)
{
  int result; // eax

  g_UnitFadeAnimUnitIndex = unitIndex;
  g_UnitFadeAnimCurrentOffset = startOffset;
  g_UnitFadeAnimTargetOffset = targetOffset;
  g_UnitFadeAnimStepRate = stepRate;
  result = Time_Now(stepRate, startOffset);
  g_UnitFadeAnimLastUpdateTime = result;
  return result;
}
// 514E48: using guessed type int dword_514E48;
// 514E4C: using guessed type int dword_514E4C;
// 514E50: using guessed type int dword_514E50;
// 5320F4: using guessed type int dword_5320F4;
// 5320F8: using guessed type int dword_5320F8;

//----- (0042F820) --------------------------------------------------------
int  UnitBattle_DrawUnitSprite(int unitIndex, int screenX, int screenY, int yOffset)
{
  int unitRecord; // edx
  int unitType; // eax
  int spriteFrameIndex; // edx
  int spriteSet; // eax
  int SpriteForChar; // eax
  int v10; // edx
  int v11; // ecx
  int currentTime; // eax
  int chargePulse; // eax
  int result; // eax
  int unitRecordOffset; // edx
  int adjacentEnemies; // esi
  int v17; // ecx
  int neighborIndex; // edi
  int neighborRecord; // ecx
  int pulseTime; // eax
  int markPulseSin; // eax
  int v22; // edx
  int markSpriteBase; // eax
  int markSprite; // eax
  int v25; // ecx
  int newFadeOffset; // edx
  int markPulse; // [esp-8h] [ebp-3Ch]
  int spriteVOffset; // [esp+8h] [ebp-2Ch]
  int spriteChar; // [esp+10h] [ebp-24h]
  int recordOffset; // [esp+24h] [ebp-10h]
  int markCounter; // [esp+30h] [ebp-4h]
  _DWORD savedregs[3]; // [esp+34h] [ebp+0h] BYREF

  if ( unitIndex == -1 )
    goto LABEL_13;
  unitRecord = g_MapData + 31 * unitIndex;
  unitType = *(__int16 *)(unitRecord + 852);
  if ( unitType == -1 )
    goto LABEL_13;
  spriteVOffset = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * unitType];
  if ( g_ActiveUnitMoveTileIndex == -1 || unitIndex != g_ActiveUnitMoveTileIndex )
  {
    if ( g_UnitBattleAnimatingUnitIndex == -1 || unitIndex != g_UnitBattleAnimatingUnitIndex )
    {
      SpriteForChar = UnitSpriteCache_FindEntryOrLoad(
                        *(unsigned __int16 *)(g_MapData + 31 * unitIndex + 852),
                        *(_BYTE *)(g_MapData + 31 * unitIndex + 854),
                        *(_BYTE *)(g_MapData + 31 * unitIndex + 869) & 7,
                        *(_BYTE *)(g_MapData + 31 * unitIndex + 855));
      goto LABEL_7;
    }
    spriteFrameIndex = 8 * *(unsigned __int8 *)(31 * g_UnitBattleAnimatingUnitIndex + g_MapData + 855) + g_UnitBattleHitAnimFrame;
    spriteSet = g_UnitBattleAnimatingUnitSpriteSet;
  }
  else
  {
    spriteFrameIndex = g_UnitBattleAnimFrameCount * *(unsigned __int8 *)(unitRecord + 855) + g_UnitAnimFrameIndex;
    spriteSet = g_ActiveUnitAnimSpriteSet;
  }
  SpriteForChar = DLX_GetSpriteForChar(spriteSet, spriteFrameIndex);
LABEL_7:
  spriteChar = SpriteForChar;
  if ( g_UnitFadeAnimUnitIndex == -1 )
    g_UnitFadeAnimLastUpdateTime = 0;
  if ( unitIndex == g_SelectedUnitIndex && g_UnitBattleChargeModeActive_532060 )
  {
    currentTime = Time_Now(v11, v10);
    chargePulse = Math_SinDegreesQ16(2 * (currentTime - g_UnitBattleChargeModeStartTick_532074) - 90);
    Sprite_DrawSimpleIgnoringRect(spriteChar, screenX, screenY + yOffset - spriteVOffset, screenY, screenX + 63, screenY + 63, ((50 * chargePulse) >> 16) + 50, 0, 0, 200, 1u);
  }
  else if ( unitIndex == g_UnitFadeAnimUnitIndex )
  {
    if ( !g_UnitFadeAnimLastUpdateTime )
      g_UnitFadeAnimLastUpdateTime = Time_Now(v11, v10);
    newFadeOffset = g_UnitFadeAnimStepRate * (Time_Now(v11, v10) - g_UnitFadeAnimLastUpdateTime) + g_UnitFadeAnimCurrentOffset;
    g_UnitFadeAnimCurrentOffset = newFadeOffset;
    if ( newFadeOffset > g_UnitFadeAnimTargetOffset )
      g_UnitFadeAnimCurrentOffset = g_UnitFadeAnimTargetOffset;
    if ( g_UnitFadeAnimCurrentOffset < 0 )
      g_UnitFadeAnimCurrentOffset = 0;
    g_UnitFadeAnimLastUpdateTime = Time_Now(g_UnitFadeAnimTargetOffset, newFadeOffset);
    Sprite_DrawSimpleTrackingOffset(spriteChar, screenX, screenY + yOffset - spriteVOffset, screenY, screenX + 63, screenY + 63, g_UnitFadeAnimCurrentOffset, 1u);
  }
  else
  {
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY + yOffset - spriteVOffset, SpriteForChar, 1);
  }
  TextSprite_ActivateResourceSlot(0, 1, (DWORD)savedregs);
LABEL_13:
  result = UnitBattle_CountAdjacentEnemies(31 * unitIndex + g_MapData + 852);
  adjacentEnemies = result;
  if ( !v17 && !yOffset && result >= 3 )
  {
    markCounter = 0;
    recordOffset = unitRecordOffset;
    neighborIndex = 0;
    do
    {
      if ( adjacentEnemies > 6 )
        adjacentEnemies = 6;
      result = *(__int16 *)(g_MapData
                          + 40 * (Map_NeighborDX[neighborIndex] + *(unsigned __int16 *)(g_MapData + recordOffset + 856))
                          + 2 * (Map_NeighborDY[neighborIndex] + *(unsigned __int16 *)(g_MapData + recordOffset + 858))
                          + 1534);
      if ( result != -1 )
      {
        neighborRecord = 31 * result + g_MapData;
        if ( *(_BYTE *)(neighborRecord + 854) != *(_BYTE *)(g_MapData + recordOffset + 854) && result != g_ActiveUnitMoveTileIndex )
        {
          pulseTime = Time_Now(neighborRecord, 10 * adjacentEnemies);
          markPulseSin = Math_SinDegreesQ16(adjacentEnemies * pulseTime);
          markPulse = v22 + 120 + ((v22 * markPulseSin) >> 16);
          if ( *(unsigned __int8 *)(recordOffset + g_MapData + 854) == *(_DWORD *)(g_MapData + 836) )
            markSpriteBase = 17;
          else
            markSpriteBase = 25;
          markSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, markSpriteBase + markCounter);
          result = Sprite_DrawSimpleTrackingOffset(markSprite, v25, screenY, screenY, screenX + 63, screenY + 63, markPulse, 1u);
        }
      }
      neighborIndex += 2;
      ++markCounter;
    }
    while ( markCounter < 8 );
  }
  return result;
}
// 42F8DE: variable 'v11' is possibly undefined
// 42F8DE: variable 'v10' is possibly undefined
// 42F95F: variable 'v17' is possibly undefined
// 42F987: variable 'v15' is possibly undefined
// 42FA1E: variable 'v22' is possibly undefined
// 42FA77: variable 'v25' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 514E44: using guessed type int dword_514E44;
// 514E48: using guessed type int dword_514E48;
// 514E4C: using guessed type int dword_514E4C;
// 514E50: using guessed type int dword_514E50;
// 5202C8: using guessed type int dword_5202C8;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;
// 532074: using guessed type int dword_532074;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 5320F4: using guessed type int dword_5320F4;
// 5320F8: using guessed type int dword_5320F8;

//----- (0042FC30) --------------------------------------------------------
int  UnitBattle_DrawMovingUnitInAdjacentTile(int result, int tileCol, int screenY, int screenX)
{
  int leftUnit; // eax
  int rightUnit; // eax
  int upUnit; // eax
  int downUnit; // eax
  int upLeftUnit; // eax
  int tileRow; // [esp+0h] [ebp-10h]

  tileRow = result;
  if ( g_ActiveUnitMoveTileIndex != -1 )
  {
    result = *(__int16 *)(g_MapData + 31 * g_ActiveUnitMoveTileIndex + 852);
    if ( result != 27 && result != 30 )
    {
      if ( tileCol > 0 )
      {
        leftUnit = *(__int16 *)(g_MapData + 40 * tileRow + 2 * tileCol + 1532);
        if ( leftUnit != -1 && g_UnitMoveAnimOffsetY > 0 && leftUnit == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(leftUnit, screenX, screenY, g_UnitMoveAnimOffsetY - 64);
      }
      if ( tileCol < *(_DWORD *)(g_MapData + 804) - 1 )
      {
        rightUnit = *(__int16 *)(g_MapData + 40 * tileRow + 2 * tileCol + 1536);
        if ( rightUnit != -1 && g_UnitMoveAnimOffsetY < 0 && rightUnit == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(rightUnit, screenX, screenY, g_UnitMoveAnimOffsetY + 64);
      }
      if ( tileRow > 0 )
      {
        upUnit = *(__int16 *)(g_MapData + 40 * (tileRow - 1) + 2 * tileCol + 1534);
        if ( upUnit != -1 && g_UnitMoveAnimOffsetX > 0 && upUnit == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(upUnit, screenX, screenY, g_UnitMoveAnimOffsetY);
      }
      if ( *(_DWORD *)(g_MapData + 804) - 1 > tileRow )
      {
        downUnit = *(__int16 *)(40 * (tileRow + 1) + g_MapData + 2 * tileCol + 1534);
        if ( downUnit != -1 && g_UnitMoveAnimOffsetX < 0 && downUnit == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(downUnit, screenX, screenY, g_UnitMoveAnimOffsetY);
      }
      if ( tileRow > 0 && tileCol > 0 )
      {
        upLeftUnit = *(__int16 *)(40 * (tileRow - 1) + g_MapData + 2 * tileCol + 1532);
        if ( upLeftUnit != -1 && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX > 0 && upLeftUnit == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(upLeftUnit, screenX, screenY, g_UnitMoveAnimOffsetY - 64);
      }
      result = tileRow;
      if ( tileRow > 0 && tileCol < *(_DWORD *)(g_MapData + 800) )
      {
        result = *(__int16 *)(40 * (tileRow - 1) + g_MapData + 2 * tileCol + 1536);
        if ( result != -1 && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX > 0 && result == g_ActiveUnitMoveTileIndex )
          result = UnitBattle_DrawUnitSprite(result, screenX, screenY, g_UnitMoveAnimOffsetY + 64);
      }
      if ( tileCol > 0 )
      {
        result = tileRow;
        if ( tileRow < *(_DWORD *)(g_MapData + 804) )
        {
          result = *(__int16 *)(40 * (tileRow + 1) + g_MapData + 2 * tileCol + 1532);
          if ( result != -1 && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX < 0 && result == g_ActiveUnitMoveTileIndex )
            result = UnitBattle_DrawUnitSprite(result, screenX, screenY, g_UnitMoveAnimOffsetY - 64);
        }
      }
      if ( tileCol < *(_DWORD *)(g_MapData + 800) )
      {
        result = tileRow;
        if ( tileRow < *(_DWORD *)(g_MapData + 804) )
        {
          result = *(__int16 *)(g_MapData + 40 * (tileRow + 1) + 2 * tileCol + 1536);
          if ( result != -1 && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX < 0 && result == g_ActiveUnitMoveTileIndex )
            return UnitBattle_DrawUnitSprite(result, screenX, screenY, g_UnitMoveAnimOffsetY + 64);
        }
      }
    }
  }
  return result;
}
// 512360: using guessed type int dword_512360;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 532048: using guessed type int g_MapData;

//----- (0042FFB0) --------------------------------------------------------
int  UnitBattle_DrawTileContents(int tileRow, int tileCol)
{
  int screenX; // esi
  int SpriteForChar; // eax
  int tileDataPtr; // eax
  int casualtySpriteChar; // edx
  int wallCellPtr; // eax
  char wallCellValue; // dl
  unsigned int v8; // eax
  int wallSprite; // eax
  int gateCellPtr; // eax
  int gateCellValue; // eax
  unsigned int v12; // eax
  int prevRowWallCellPtr; // edi
  int cornerSpriteVariant; // eax
  int cornerSprite; // eax
  int gateSprite; // eax
  int prevColUnitIndex; // edi
  int prevColMoveOffsetY; // edx
  int prevRowPrevColUnitIndex; // edi
  int nextRowNextColUnitIndex; // edi
  int prevRowBasePtr; // edx
  int prevRowUnitIndex; // edi
  int prevRowMoveOffsetY; // eax
  int curRowBasePtr; // ecx
  int nextColUnitIndex; // edi
  int nextColMoveOffsetY; // eax
  int prevRowNextColUnitIndex; // edi
  int nextRowPrevColUnitIndex; // edi
  int nextRowBasePtr; // edx
  int nextRowUnitIndex; // edi
  int nextRowMoveOffsetY; // eax
  int overlaySprite; // eax
  int selectSprite; // eax
  int v34; // ecx
  int result; // eax
  int casualtySprite; // eax
  int v37; // ecx
  int gateSpriteEarly; // eax
  int prevRowGateCellPtr; // ecx
  _BYTE *cornerCellPtr; // edx
  int casualtyTrackOffset; // [esp-8h] [ebp-38h]
  int rowByteOffset; // [esp+0h] [ebp-30h]
  int colByteOffset; // [esp+8h] [ebp-28h]
  int unitYOffset; // [esp+10h] [ebp-20h]
  int gateDrawDeferred; // [esp+14h] [ebp-1Ch]
  int tileUnitIndex; // [esp+18h] [ebp-18h]
  int wallSpriteChar; // [esp+1Ch] [ebp-14h]
  int gateSpriteChar; // [esp+20h] [ebp-10h]
  int screenY; // [esp+24h] [ebp-Ch]

  screenX = ((tileRow - *(_DWORD *)(g_MapData + 808)) << 6) + 32;
  screenY = ((tileCol - *(_DWORD *)(g_MapData + 812)) << 6) + 16;
  if ( tileRow < 0
    || tileCol < 0
    || tileRow >= *(_DWORD *)(g_MapData + 804)
    || tileCol >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  rowByteOffset = 40 * tileRow;
  colByteOffset = 2 * tileCol;
  SpriteForChar = DLX_GetSpriteForChar(g_BattleHudSprites, *(__int16 *)(2 * tileCol + 40 * tileRow + g_MapData));
  Compat_RenderDeviceDrawMenuSprite(screenX, screenY, SpriteForChar, 1);
  tileDataPtr = colByteOffset + rowByteOffset + g_MapData;
  casualtySpriteChar = *(char *)(tileDataPtr + 2334);
  if ( casualtySpriteChar != -1 )
  {
    casualtyTrackOffset = *(unsigned __int8 *)(tileDataPtr + 2335);
    casualtySprite = DLX_GetSpriteForChar(g_BattleCasualtySpriteSet, casualtySpriteChar);
    Sprite_DrawSimpleTrackingOffset(casualtySprite, screenX, screenY, screenY, screenX + 63, screenY + 63, casualtyTrackOffset, 1u);
  }
  if ( tileCol != *(_DWORD *)(g_MapData + 828) )
  {
    wallCellPtr = tileCol + g_MapData + 20 * tileRow;
    wallCellValue = *(_BYTE *)(wallCellPtr + 3134);
    if ( wallCellValue )
    {
      if ( wallCellValue >= 33 )
        wallSpriteChar = wallCellValue < 66;
      else
        wallSpriteChar = 2;
    }
    else
    {
      if ( !*(_BYTE *)(wallCellPtr + 3534) )
        goto LABEL_10;
      wallSpriteChar = 3;
    }
    v8 = *(_DWORD *)(g_MapData + 820);
    if ( v8 )
    {
      if ( v8 <= 1 )
      {
        wallSpriteChar += 412;
      }
      else if ( v8 == 2 )
      {
        wallSpriteChar += 404;
      }
    }
    else
    {
      wallSpriteChar += 420;
    }
    wallSprite = DLX_GetSpriteForChar(g_BattleHudSprites, wallSpriteChar);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, wallSprite, 1);
    g_BattleWallGateLastSpriteChar = wallSpriteChar;
  }
LABEL_10:
  gateCellPtr = tileCol + g_MapData + 20 * tileRow;
  gateDrawDeferred = 1;
  if ( *(_BYTE *)(gateCellPtr + 3534) && tileCol == *(_DWORD *)(g_MapData + 828) )
  {
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
      gateCellValue = *(_DWORD *)(g_MapData + 832);
    else
      gateCellValue = *(char *)(gateCellPtr + 3134);
    if ( gateCellValue )
    {
      if ( gateCellValue >= 33 )
        gateSpriteChar = gateCellValue < 66;
      else
        gateSpriteChar = 2;
    }
    else if ( *(_BYTE *)(tileCol + g_MapData + 20 * tileRow + 3534) )
    {
      gateSpriteChar = 3;
      gateDrawDeferred = 0;
    }
    v12 = *(_DWORD *)(g_MapData + 820);
    if ( v12 )
    {
      if ( v12 <= 1 )
      {
        gateSpriteChar += 416;
      }
      else if ( v12 == 2 )
      {
        gateSpriteChar += 408;
      }
    }
    else
    {
      gateSpriteChar += 424;
    }
    if ( !gateDrawDeferred )
    {
      gateSpriteEarly = DLX_GetSpriteForChar(g_BattleHudSprites, gateSpriteChar);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, gateSpriteEarly, 1);
    }
    g_BattleWallGateLastSpriteChar = gateSpriteChar;
  }
  if ( tileRow > 0 )
  {
    prevRowWallCellPtr = g_MapData + 20 * (tileRow - 1) + tileCol;
    if ( *(_BYTE *)(prevRowWallCellPtr + 3134) )
    {
      if ( tileCol != *(_DWORD *)(g_MapData + 828) )
      {
        cornerSpriteVariant = tileCol <= 0 || *(_BYTE *)(prevRowWallCellPtr + 3133) && tileCol - 1 != *(_DWORD *)(g_MapData + 828);
        goto LABEL_29;
      }
    }
  }
  if ( tileRow > 0 )
  {
    prevRowGateCellPtr = tileCol + g_MapData + 20 * (tileRow - 1);
    if ( *(_BYTE *)(prevRowGateCellPtr + 3534) )
    {
      if ( tileCol > 0 && *(_BYTE *)(prevRowGateCellPtr + 3133) && tileCol - 1 != *(_DWORD *)(g_MapData + 828) )
      {
        cornerSpriteVariant = 2;
LABEL_29:
        cornerSprite = DLX_GetSpriteForChar(g_BattleHudSprites, cornerSpriteVariant + 5 * *(_DWORD *)(g_MapData + 820) + 428);
        Compat_RenderDeviceDrawMenuSprite(screenX, screenY, cornerSprite, 1);
        goto LABEL_30;
      }
      if ( tileCol == *(_DWORD *)(g_MapData + 828) && *(_DWORD *)(g_MapData + 832) )
      {
        cornerSpriteVariant = 4;
        goto LABEL_29;
      }
    }
  }
  if ( tileCol > 0 )
  {
    cornerCellPtr = (_BYTE *)(tileCol + g_MapData + 20 * tileRow);
    if ( !cornerCellPtr[3134]
      && cornerCellPtr[3534]
      && (cornerCellPtr[3133] || tileCol - 1 == *(_DWORD *)(g_MapData + 828) && *(_DWORD *)(g_MapData + 832)) )
    {
      cornerSpriteVariant = 3;
      goto LABEL_29;
    }
  }
LABEL_30:
  tileUnitIndex = *(__int16 *)(40 * tileRow + g_MapData + 2 * tileCol + 1534);
  unitYOffset = 0;
  if ( g_ActiveUnitMoveTileIndex == tileUnitIndex )
    unitYOffset = g_UnitMoveAnimOffsetY;
  if ( tileUnitIndex != -1 && (g_UnitTypeFlags[22 * *(__int16 *)(g_MapData + 31 * tileUnitIndex + 852)] & 1) == 0 )
    UnitBattle_DrawUnitSprite(tileUnitIndex, screenX, screenY, unitYOffset);
  UnitBattle_DrawMovingUnitInAdjacentTile(tileRow, tileCol, screenY, screenX);
  if ( *(_BYTE *)(tileCol + g_MapData + 20 * tileRow + 3534) && tileCol == *(_DWORD *)(g_MapData + 828) && gateDrawDeferred )
  {
    gateSprite = DLX_GetSpriteForChar(g_BattleHudSprites, gateSpriteChar);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, gateSprite, 1);
  }
  if ( tileCol > 0 )
  {
    prevColUnitIndex = *(__int16 *)(40 * tileRow + g_MapData + 2 * tileCol + 1532);
    if ( prevColUnitIndex != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(40 * tileRow + g_MapData + 2 * tileCol + 1532)) )
      {
        prevColMoveOffsetY = 0;
        if ( prevColUnitIndex == g_ActiveUnitMoveTileIndex )
          prevColMoveOffsetY = g_UnitMoveAnimOffsetY;
        UnitBattle_DrawUnitSprite(prevColUnitIndex, screenX, screenY, prevColMoveOffsetY - 64);
      }
    }
  }
  if ( tileCol > 0 && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    prevRowPrevColUnitIndex = *(__int16 *)(40 * (tileRow - 1) + g_MapData + 2 * tileCol + 1532);
    if ( prevRowPrevColUnitIndex == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(prevRowPrevColUnitIndex, screenX, screenY, g_UnitMoveAnimOffsetY - 64);
    }
  }
  if ( tileCol < *(_DWORD *)(g_MapData + 800) && tileRow < *(_DWORD *)(g_MapData + 804) && g_ActiveUnitMoveTileIndex != -1 )
  {
    nextRowNextColUnitIndex = *(__int16 *)(40 * (tileRow + 1) + g_MapData + 2 * tileCol + 1536);
    if ( nextRowNextColUnitIndex == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(nextRowNextColUnitIndex, screenX, screenY, g_UnitMoveAnimOffsetY + 64);
    }
  }
  if ( tileRow > 0 )
  {
    prevRowBasePtr = 40 * (tileRow - 1) + g_MapData;
    prevRowUnitIndex = *(__int16 *)(prevRowBasePtr + 2 * tileCol + 1534);
    if ( prevRowUnitIndex != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(prevRowBasePtr + 2 * tileCol + 1534)) )
      {
        prevRowMoveOffsetY = 0;
        if ( prevRowUnitIndex == g_ActiveUnitMoveTileIndex )
          prevRowMoveOffsetY = g_UnitMoveAnimOffsetY;
        UnitBattle_DrawUnitSprite(prevRowUnitIndex, screenX, screenY, prevRowMoveOffsetY);
      }
    }
  }
  if ( tileUnitIndex != -1 && (g_UnitTypeFlags[22 * *(__int16 *)(g_MapData + 31 * tileUnitIndex + 852)] & 1) != 0 )
    UnitBattle_DrawUnitSprite(tileUnitIndex, screenX, screenY, unitYOffset);
  if ( tileCol < *(_DWORD *)(g_MapData + 800) )
  {
    curRowBasePtr = 40 * tileRow + g_MapData;
    nextColUnitIndex = *(__int16 *)(curRowBasePtr + 2 * tileCol + 1536);
    if ( nextColUnitIndex != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(curRowBasePtr + 2 * tileCol + 1536)) )
      {
        nextColMoveOffsetY = 0;
        if ( nextColUnitIndex == g_ActiveUnitMoveTileIndex )
          nextColMoveOffsetY = g_UnitMoveAnimOffsetY;
        UnitBattle_DrawUnitSprite(nextColUnitIndex, screenX, screenY, nextColMoveOffsetY + 64);
      }
    }
  }
  if ( tileCol < *(_DWORD *)(g_MapData + 800) && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    prevRowNextColUnitIndex = *(__int16 *)(40 * (tileRow - 1) + g_MapData + 2 * tileCol + 1536);
    if ( prevRowNextColUnitIndex == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(prevRowNextColUnitIndex, screenX, screenY, g_UnitMoveAnimOffsetY + 64);
    }
  }
  if ( tileCol > 0 && tileRow < *(_DWORD *)(g_MapData + 804) && g_ActiveUnitMoveTileIndex != -1 )
  {
    nextRowPrevColUnitIndex = *(__int16 *)(40 * (tileRow + 1) + g_MapData + 2 * tileCol + 1532);
    if ( nextRowPrevColUnitIndex == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(nextRowPrevColUnitIndex, screenX, screenY, g_UnitMoveAnimOffsetY - 64);
    }
  }
  if ( tileRow < *(_DWORD *)(g_MapData + 804) )
  {
    nextRowBasePtr = 40 * (tileRow + 1) + g_MapData;
    nextRowUnitIndex = *(__int16 *)(nextRowBasePtr + 2 * tileCol + 1534);
    if ( nextRowUnitIndex != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(nextRowBasePtr + 2 * tileCol + 1534)) )
      {
        nextRowMoveOffsetY = 0;
        if ( nextRowUnitIndex == g_ActiveUnitMoveTileIndex )
          nextRowMoveOffsetY = g_UnitMoveAnimOffsetY;
        UnitBattle_DrawUnitSprite(nextRowUnitIndex, screenX, screenY, nextRowMoveOffsetY);
      }
    }
  }
  if ( tileRow == g_UnitBattleShotProjectileTileX && tileCol == g_UnitBattleShotProjectileTileY )
  {
    overlaySprite = DLX_GetSpriteForChar(g_UnitBattleProjectileSpriteSet, g_BattleShotAnimFrameIndex);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, overlaySprite, 1);
  }
  if ( tileUnitIndex != -1 )
  {
    if ( *(unsigned __int8 *)(g_MapData + 31 * tileUnitIndex + 854) == g_CurrentPlayerIndex
      && (*(_BYTE *)(g_MapData + 31 * tileUnitIndex + 874) & 1) != 0 )
    {
      overlaySprite = DLX_GetSpriteForChar(g_MarksSpriteSet, 16);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY + 2, overlaySprite, 1);
    }
    if ( tileUnitIndex == g_SelectedUnitIndex && g_ActiveUnitMoveTileIndex == -1 )
    {
      selectSprite = DLX_GetSpriteForChar(g_MarksSpriteSet, *(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET) == 1);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, selectSprite, 1);
    }
  }
  result = gameData;
  if ( *(_DWORD *)(gameData + 147151) )
  {
    if ( tileCol > *(_DWORD *)(g_MapData + 812) )
      Compat_RenderDeviceFillSolidRect(screenX, screenY, (unsigned __int16)(screenX + 63), screenY, 1u);
    result = g_MapData;
    if ( tileRow > *(_DWORD *)(g_MapData + 808) )
      return Compat_RenderDeviceFillSolidRect(screenX, screenY, screenX, (unsigned __int16)(screenY + 63), 1u);
  }
  return result;
}
// 430878: variable 'v37' is possibly undefined
// 430180: variable 'v48' is possibly undefined
// 4303A7: variable 'v18' is possibly undefined
// 43080C: variable 'v34' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 514E54: using guessed type int dword_514E54;
// 514E58: using guessed type int dword_514E58;
// 5202C8: using guessed type int dword_5202C8;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 532048: using guessed type int g_MapData;
// 53204C: using guessed type int g_BattleHudSprites;
// 532058: using guessed type int dword_532058;
// 5320FC: using guessed type int dword_5320FC;
// 532100: using guessed type int dword_532100;
// 532104: using guessed type int dword_532104;

//----- (00430B20) --------------------------------------------------------
int  UnitBattle_RedrawTile(int tileRow, int tileCol)
{
  int result; // eax
  void *savedRenderDevice; // ebp
  __int16 screenXBase; // si
  __int16 colOrigin; // bx
  unsigned __int16 screenYBottom; // di
  unsigned __int16 screenYTop; // [esp+4h] [ebp-10h]

  result = g_MapData;
  savedRenderDevice = g_RenderDevice;
  if ( tileRow < *(_DWORD *)(g_MapData + 808) + 7
    && tileCol < *(_DWORD *)(g_MapData + 812) + 7
    && tileRow >= *(_DWORD *)(g_MapData + 808)
    && tileCol >= *(_DWORD *)(g_MapData + 812) )
  {
    screenXBase = ((_WORD)tileRow - *(_WORD *)(g_MapData + 808)) << 6;
    colOrigin = *(_WORD *)(g_MapData + 812);
    screenYTop = (((_WORD)tileCol - colOrigin) << 6) + 16;
    g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
    screenYBottom = (((_WORD)tileCol - colOrigin) << 6) + 80;
    UnitBattle_DrawTileContents(tileRow, tileCol);
    RenderState_PumpIfRectInViewBounds(g_RenderState, screenXBase + 32, screenXBase + 96, screenYTop, screenYBottom);
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, screenYTop, (unsigned __int16)(screenXBase + 32), screenXBase + 95, screenYTop + 63, screenXBase + 32, screenYTop);
    result = Render_Present((int)g_RenderState);
    g_RenderDevice = savedRenderDevice;
  }
  return result;
}
// 430B20: could not find valid save-restore pair for ebx
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00430C20) --------------------------------------------------------
int UnitBattle_RedrawVisibleGrid()
{
  int i; // ebx
  int j; // ecx
  int cursorRight; // edi
  int cursorBottom; // esi
  int overlayPresented; // ebp
  int result; // eax
  int cursorX; // [esp+4h] [ebp-20h]
  int cursorY; // [esp+8h] [ebp-1Ch]

  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_grid_redraw_enter",
    *(_DWORD *)(g_MapData + 808),
    *(_DWORD *)(g_MapData + 812),
    *(_DWORD *)(g_MapData + 800),
    *(_DWORD *)(g_MapData + 804));
  for ( i = *(_DWORD *)(g_MapData + 808); i < *(_DWORD *)(g_MapData + 808) + 7; ++i )
  {
    for ( j = *(_DWORD *)(g_MapData + 812); j < *(_DWORD *)(g_MapData + 812) + 7; ++j )
    {
      if ( Diagnostics_IsBattleTileDrawTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "battle_grid_before_tile",
          i,
          j,
          *(__int16 *)(g_MapData + 40 * i + 2 * j + 1534),
          g_SelectedUnitIndex);
      UnitBattle_DrawTileContents(i, j);
      if ( Diagnostics_IsBattleTileDrawTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "battle_grid_after_tile",
          i,
          j,
          *(__int16 *)(g_MapData + 40 * i + 2 * j + 1534),
          g_SelectedUnitIndex);
    }
  }
  cursorX = g_MouseCursorRawX >> g_CursorCoordShift;
  cursorY = g_MouseCursorRawY >> g_CursorCoordShift;
  cursorRight = (g_MouseCursorRawX >> g_CursorCoordShift) + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12);
  cursorBottom = *(_DWORD *)(g_ActiveCursorDescriptorPtr + 16) + (g_MouseCursorRawY >> g_CursorCoordShift);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_redraw_after_tiles", cursorX, cursorY, cursorRight, cursorBottom);
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= 480 || cursorRight <= 32 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_full_restore", cursorX, cursorY, cursorRight, cursorBottom);
    return Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 32, 0x1DFu, 0x1CFu, 0x20u, 0x10u);
  }
  overlayPresented = g_CursorOverlayPresented;
  if ( g_MouseCursorRawX >> g_CursorCoordShift < 32 )
  {
    LOWORD(cursorX) = 32;
    if ( g_CursorOverlayPresented )
      Render_Pump();
  }
  if ( cursorRight > 479 )
  {
    cursorRight = 479;
    if ( overlayPresented )
      Render_Pump();
  }
  if ( cursorY < 16 )
  {
    LOWORD(cursorY) = 16;
    if ( overlayPresented )
      Render_Pump();
  }
  if ( cursorBottom > 463 )
  {
    cursorBottom = 463;
    if ( overlayPresented )
      Render_Pump();
  }
  Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_top", cursorX, cursorY, cursorRight, cursorBottom);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 32, 0x1DFu, cursorY, 0x20u, 0x10u);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_top", cursorX, cursorY, cursorRight, cursorBottom);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)cursorY, 32, cursorX, cursorBottom, 0x20u, cursorY);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_left", cursorX, cursorY, cursorRight, cursorBottom);
  if ( overlayPresented )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_input_flush", cursorX, cursorY, cursorRight, cursorBottom);
    Input_Flush();
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_input_flush", cursorX, cursorY, cursorRight, cursorBottom);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_active", cursorX, cursorY, cursorRight, cursorBottom);
  result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)cursorY, (unsigned __int16)cursorX, cursorRight, cursorBottom, cursorX, cursorY);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_active", cursorX, cursorY, cursorRight, cursorBottom);
  if ( overlayPresented )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_present", cursorX, cursorY, cursorRight, cursorBottom);
    result = Render_Present((int)g_RenderState);
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_present", cursorX, cursorY, cursorRight, cursorBottom);
  }
  if ( cursorRight != 479 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_right", cursorX, cursorY, cursorRight, cursorBottom);
    result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)cursorY, (unsigned __int16)cursorRight, 0x1DFu, cursorBottom, cursorRight, cursorY);
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_right", cursorX, cursorY, cursorRight, cursorBottom);
  }
  if ( cursorBottom != 463 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_bottom", cursorX, cursorY, cursorRight, cursorBottom);
    if ( Compat_RenderSurfaceCopyRect((_DWORD *)g_PrimaryRenderSurface, 0, 32, (unsigned __int16)cursorBottom, 0x1DFu, 0x1CFu, 0x20u, cursorBottom) )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_bottom", cursorX, cursorY, cursorRight, cursorBottom);
      return result;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_grid_skip_restore_bottom", cursorX, cursorY, cursorRight, cursorBottom);
    return result;
  }
  return result;
}
// 430CD0: conditional instruction was optimized away because edi.4>=21
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;
