/* Castle, garrison, production, and building modal interfaces.
 * Original function-marker range: 0x004338C0..0x00441D20.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004338C0) --------------------------------------------------------
int  BuildingGarrisonDialog_RequestClose(int a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_BuildingGarrisonDialogCloseRequested = 1;
  return result;
}
// 532148: using guessed type int dword_532148;

//----- (004338E0) --------------------------------------------------------
int  BuildingGarrisonDialog_ShowProductionDialog(int a1, DWORD a2, char a3)
{
  int result; // eax
  char *v4; // edx
  char v5; // bl
  CHAR *v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  UIWidget_PlayPressedReleaseAnimation(a1);
  result = g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & 2) != 0 )
  {
    Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
    Render_Pump();
    Castle_ShowUnitProductionPanel(g_BuildingGarrisonDialogActiveBuilding, a2, a3);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      v4 = aCastle_chrD_15;
    else
      v4 = aCastle_pogD_15;
    v5 = g_BuildingGarrisonDialogResourceHandle;
    (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, v4);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      v6 = aCastle_chrD_16;
    else
      v6 = aCastle_pogD_16;
    Palette_LoadOrBuildBlendLookupTable(v6, g_BuildingGarrisonDialogResourceHandle, g_BuildingGarrisonDialogUseChrTheme, a2);
    RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_BuildingGarrisonDialogResourceHandle, v7, a2);
    Render_LoadResourceSprite_v4(5, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v8, v5, a2);
    Render_LoadResourceSprite_v4(7, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v9, v5, a2);
    Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v10, v5, a2);
    g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
    BuildingGarrisonDialog_EnsureActionWidgets(g_BuildingGarrisonDialogActiveBuilding);
    UIWidgetTable_InitDrawStates((_DWORD *)BuildingGarrisonDialogActions);
    (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
    BuildingGarrisonDialog_DrawSlotGrid(-1);
    BuildingGarrisonDialog_DrawSelectedUnitPanel();
    BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(v11, 20, a2);
    Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_BuildingGarrisonDialogResourceHandle, 20);
    Render_Present((int)g_RenderState);
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
    Render_Present((int)g_RenderState);
    Render_Pump();
    return Render_Present((int)g_RenderState);
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
void * BuildingGarrisonDialog_ToggleRepairSelectedUnits(int a1, DWORD a2)
{
  void *result; // eax
  int v4; // ecx
  int v5; // ebx

  UIWidget_PlayPressedReleaseAnimation(a1);
  result = (void *)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & 1) != 0 )
  {
    v4 = 0;
    v5 = 0;
    do
    {
      if ( g_BuildingGarrisonDialogSelectedSlots[v5] )
      {
        if ( (BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, v4) & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
          Building_ClearGarrisonRepairTimer(g_BuildingGarrisonDialogActiveBuilding, v4);
        else
          Building_RepairUnit(g_BuildingGarrisonDialogActiveBuilding, v4, a2);
      }
      ++v4;
      ++v5;
    }
    while ( v4 < 12 );
    memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
    return BuildingGarrisonDialog_DrawSlotGrid(-1);
  }
  return result;
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];

//----- (00433AC0) --------------------------------------------------------
void * BuildingGarrisonDialog_ToggleTrainingSelectedUnits(int a1, DWORD a2)
{
  void *result; // eax
  int v4; // ecx
  int v5; // ebx

  UIWidget_PlayPressedReleaseAnimation(a1);
  result = (void *)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & 8) != 0 )
  {
    v4 = 0;
    v5 = 0;
    do
    {
      if ( g_BuildingGarrisonDialogSelectedSlots[v5] )
      {
        if ( (BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, v4) & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
          Building_ClearGarrisonTrainingTimer(g_BuildingGarrisonDialogActiveBuilding, v4);
        else
          Building_TrainUnit(g_BuildingGarrisonDialogActiveBuilding, v5 * 4, a2);
      }
      ++v4;
      ++v5;
    }
    while ( v4 < 12 );
    memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
    return BuildingGarrisonDialog_DrawSlotGrid(-1);
  }
  return result;
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];

//----- (00433B40) --------------------------------------------------------
int  BuildingGarrisonDialog_BeginSelectedUnitsExit(int a1)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v11[16]; // [esp+4h] [ebp-40h]

  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  do
  {
    if ( g_BuildingGarrisonDialogSelectedSlots[v5] )
    {
      ++v6;
      ++v4;
      v11[v6 - 1] = v3;
    }
    ++v3;
    ++v5;
  }
  while ( v3 < 12 );
  v11[v4] = -1;
  Diagnostics_TraceWorldMapActionEvent(
    "garrison_exit_begin",
    v4,
    v11[0],
    *(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 0),
    *(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 1));
  if ( v11[0] == -1 || !Building_HasFreeAdjacentExitTile((unsigned __int8 *)g_BuildingGarrisonDialogActiveBuilding) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "garrison_exit_blocked",
      v4,
      v11[0],
      Building_HasFreeAdjacentExitTile((unsigned __int8 *)g_BuildingGarrisonDialogActiveBuilding),
      0);
    Audio_PlayButtonSound(aWrong_7);
    return Render_Begin((int)g_RenderState, 0);
  }
  else
  {
    UIWidget_ShowPressedState(a1);
    g_BuildingGarrisonDialogPendingExitCountdown = 1;
    Audio_PlaySoundEffectByName(aDclose, 64);
    return UIWidget_ShowReleasedState(a1, 1);
  }
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00433BF0) --------------------------------------------------------
int  BuildingGarrisonDialog_TickAnimations(double a1)
{
  int previous_resource_handle;

  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  BuildingGarrisonDialog_AnimateSelectedUnit(0);
  BuildingGarrisonDialog_TickExitCountdown(0, a1);
  return Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
}

//----- (00434110) --------------------------------------------------------
int CastleProduction_DrawSelectedUnitPortrait()
{
  void *v0; // ebp
  __int16 SpriteWidth; // ax
  int v2; // edi
  __int16 v3; // cx
  int SpriteForChar; // eax
  int result; // eax

  v0 = g_RenderDevice;
  DLX_GetSpriteHeight(g_CastleProductionSelectedUnitSpriteSet, 0);
  SpriteWidth = DLX_GetSpriteWidth(g_CastleProductionSelectedUnitSpriteSet, 0);
  v2 = g_CursorOverlayPresented;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0x50u, v3 + 80, 0xC3u, SpriteWidth + 195);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar(g_CastleProductionSelectedUnitSpriteSet, g_CastleProductionUnitPortraitFrame);
  result = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46)
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
  if ( v2 )
    result = Render_Present((int)g_RenderState);
  g_RenderDevice = v0;
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

  result = Time_Now((int)this, g_CastleProductionPortraitAnimLastTickMs + 10);
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
void * CastleProduction_RedrawSelectedUnitPanel(int a1, int a2, DWORD a3, int a4, int a5)
{
  int v5; // ecx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int *v10; // ebx
  _DWORD *v11; // edx
  int SpriteForChar; // eax
  int v13; // ebx
  int v14; // esi
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // esi
  int v23; // eax
  DWORD v24; // ebp
  char *v25; // esi
  DWORD v26; // ebp
  int v27; // edx
  int v28; // edx
  __int16 SpriteHeight; // ax
  __int16 v30; // ax
  void *result; // eax
  unsigned __int16 v32; // [esp-18h] [ebp-490h]
  unsigned __int16 v33; // [esp-18h] [ebp-490h]
  int v35; // [esp-8h] [ebp-480h]
  int v36; // [esp+380h] [ebp-F8h] BYREF
  char v37[100]; // [esp+400h] [ebp-78h] BYREF
  DWORD v38; // [esp+464h] [ebp-14h]
  void *v39; // [esp+468h] [ebp-10h]
  int v40; // [esp+46Ch] [ebp-Ch]

  if ( g_CastleProductionSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_CastleProductionSelectedUnitSpriteSet);
  Unit_BuildSelectedUnitPanelIconSpritePath(v37, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], a1);
  v6 = (_DWORD *)Mem_Alloc(4112, 0x1010, a2, a3);
  if ( v6 )
    v6 = DLXSpriteSet_Load(v6, v37);
  v35 = v7;
  g_CastleProductionSelectedUnitSpriteSet = (int)v6;
  Unit_BuildSelectedUnitPanelIconPalettePath(v37, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v7);
  Palette_LoadFromQueryHandle(v8, a3);
  v9 = 224;
  v10 = &v36;
  do
  {
    ++v10;
    v11 = (_DWORD *)(g_CastleProductionPaletteBuffer + 4 * v9++);
    *v11 = *(v10 - 1);
  }
  while ( v9 <= 255 );
  v39 = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 20);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD, int, int, int, int))(*((_DWORD *)g_RenderDevice
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
  Render_ReleaseSurface(5, a3);
  v13 = g_CastleProductionSelectedAvailableUnitIndex - 2;
  v14 = 35;
  v15 = 4 * (g_CastleProductionSelectedAvailableUnitIndex - 2);
  while ( v13 <= g_CastleProductionSelectedAvailableUnitIndex + 2 )
  {
    if ( v13 < 0 || (v16 = g_CastleProduction_AvailableUnitTypes[v15 / 4], v16 == -1) )
    {
      v15 += 4;
      ++v13;
      v14 += 17;
    }
    else if ( v13 == g_CastleProductionSelectedAvailableUnitIndex )
    {
      Render_ReleaseSurface(9, 0x2Du);
      UI_DrawText(
        45,
        v14,
        (int)(**(&g_UnitTypeMetadataRecords + 22 * v16))[(unsigned __int8)g_LanguageIndex]);
      Render_ReleaseSurface(5, 0x2Du);
      v15 += 4;
      ++v13;
      v14 += 17;
    }
    else
    {
      if ( Building_HasUnitLicence(g_CastleProductionBuildingPtr, v16) )
      {
        Render_ReleaseSurface(20, 0x2Du);
        UI_DrawText(
          45,
          v14,
          (int)(**(&g_UnitTypeMetadataRecords + 22 * v16))[(unsigned __int8)g_LanguageIndex]);
        Render_ReleaseSurface(5, 0x2Du);
      }
      else
      {
        UI_DrawText(
          45,
          v14,
          (int)(**(&g_UnitTypeMetadataRecords + 22 * v16))[(unsigned __int8)g_LanguageIndex]);
      }
      v15 += 4;
      ++v13;
      v14 += 17;
    }
  }
  v22 = 88 * g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
  v23 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 17);
  v24 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int))(v24 + 52))(186, v23, -1, -1, -1);
  v25 = (char *)&g_UnitTypeMetadataRecords + v22;
  Render_ReleaseSurface(7, v24);
  v26 = *(_DWORD *)(*(_DWORD *)v25 + 4 * (unsigned __int8)g_LanguageIndex);
  UI_DrawTextFmt(69, 133, 261, 191, 3, v26);
  UI_DrawTextFmt(69, 201, 217, v40 + 95, 2, (int)aD_68);
  UI_DrawTextFmt(69, 154, 174, v40 + 50, 2, (int)aD_69);
  UI_DrawTextFmt(69, 201, 217, v40 + 50, 2, (int)aD_70);
  UI_DrawTextFmt(69, 229, 260, v27, 2, (int)a0_3);
  if ( v25[25] )
  {
    if ( v25[22] )
    {
      UI_DrawTextFmt(154, 154, 174, v40 + 74, 2, (int)aD_73);
      UI_DrawTextFmt(154, 154, v28, v40 + 95, 2, (int)aD_74);
    }
    else
    {
      DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 19);
      v38 = *((_DWORD *)g_RenderDevice + 46);
      v26 = v38;
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v38 + 52))(-1, -1, -1, -1, 1, 0, 0);
      UI_DrawTextFmt(154, 154, 174, v40 + 95, 2, (int)aD_72);
    }
  }
  else
  {
    DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 18);
    v38 = *((_DWORD *)g_RenderDevice + 46);
    v26 = v38;
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v38 + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(154, 154, 174, v40 + 95, 2, (int)aD_71);
  }
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 340, 72, 0x138u, 0x16Eu, 0x48u, 0x154u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, v26);
  UI_DrawTextFmt(-1, 0, 119, 348, 2, (int)aD_75);
  UI_DrawTextFmt(-1, 0, 215, 348, 2, (int)aD_76);
  UI_DrawTextFmt(-1, 0, 311, 348, 2, (int)aD_77);
  v32 = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x14u) + 28;
  SpriteHeight = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x14u);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 28, 40, SpriteHeight + 40, v32, 0x28u, 0x1Cu);
  v33 = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x11u) + 186;
  v30 = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x11u);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 186, 69, v30 + 69, v33, 0x45u, 0xBAu);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  CastleProduction_DrawSelectedUnitPortrait();
  result = v39;
  g_RenderDevice = v39;
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
void * CastleProduction_DrawLicenceGrid()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // edx
  void *result; // eax
  int SpriteForChar; // edx
  int v9; // [esp+8Ch] [ebp-2Ch]
  int v10; // [esp+90h] [ebp-28h]
  void *v11; // [esp+98h] [ebp-20h]
  int v12; // [esp+9Ch] [ebp-1Ch]

  v0 = 0;
  v11 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  v10 = 0;
  do
  {
    v1 = 48 * (v0 % 4) + 426;
    v12 = 82 * ((v0 - (__CFSHL__(v0 >> 31, 2) + 4 * (v0 >> 31))) >> 2) + 32;
    if ( v0 % 4 >= 2 )
      v1 = 48 * (v0 % 4) + 425;
    v9 = g_CursorOverlayPresented;
    RenderState_PumpIfRectInViewBounds(g_RenderState, v1, v1 + 31, v12, v12 + 63);
    if ( *(char *)(v0 + g_CastleProductionBuildingPtr + 402) == -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 22);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        v12,
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
      v2 = DLX_GetSpriteForChar(g_CastleProduction_LicenceSlotSpriteHandles[v10], g_CastleProductionSlotAnimFrames[v10]);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        v12,
        v2,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      if ( v0 == g_ProductionGridSelectedIndex )
      {
        v3 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 32);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          82 * ((v0 - (__CFSHL__(v0 >> 31, 2) + 4 * (v0 >> 31))) >> 2) + 33,
          v3,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(g_CastleProductionBuildingPtr) == v0 )
      {
        v4 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 21);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          v12,
          v4,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( v0 == g_LicenceGridAddAnimSlotIndex )
      {
        v5 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, g_CastleProductionLicenceTransitionFrame + 22);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          v12,
          v5,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( v0 == g_CastleLicenceRemovalSlotIndex )
      {
        v6 = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 30 - g_CastleProductionLicenceTransitionFrame);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
          v12,
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
    if ( v9 )
      Render_Present((int)g_RenderState);
    ++v0;
    ++v10;
  }
  while ( v0 < 12 );
  result = v11;
  g_RenderDevice = v11;
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
int  CastleProduction_ReloadLicenceSlotSprite(int a1, char a2)
{
  int result; // eax
  DWORD sprite_set; // ebp
  char v9[112]; // [esp+0h] [ebp-70h] BYREF

  result = *(char *)(a1 + g_CastleProductionBuildingPtr + 402);
  if ( result == -1 )
  {
    if ( g_CastleProduction_LicenceSlotSpriteHandles[a1] )
    {
      result = nfree_(g_CastleProduction_LicenceSlotSpriteHandles[a1]);
      g_CastleProduction_LicenceSlotSpriteHandles[a1] = 0;
    }
    g_CastleProduction_LicenceSlotSpriteHandles[a1] = 0;
  }
  else
  {
    sprite_set = g_CastleProduction_LicenceSlotSpriteHandles[a1];
    if ( sprite_set )
    {
      nfree_(sprite_set);
      g_CastleProduction_LicenceSlotSpriteHandles[a1] = 0;
    }
    Unit_BuildGarrisonSlotIconSpritePath(v9, *(_BYTE *)(a1 + g_CastleProductionBuildingPtr + 402), a1);
    result = Mem_Alloc(4112, 0x1010, a2, sprite_set);
    if ( result )
      result = (int)DLXSpriteSet_Load((_DWORD *)result, v9);
    g_CastleProduction_LicenceSlotSpriteHandles[a1] = result;
  }
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 532218: using guessed type int dword_532218;
// 532304: using guessed type int dword_532304[12];

//----- (00435150) --------------------------------------------------------
void * CastleProduction_ReloadLicenceSlotSprites(char a1)
{
  int i; // edx

  for ( i = 0; i < 12; CastleProduction_ReloadLicenceSlotSprite(i, a1) )
    ;
  return CastleProduction_DrawLicenceGrid();
}
// 435163: variable 'i' is possibly undefined

//----- (00435180) --------------------------------------------------------
void * CastleProduction_TickLicenceGridAnimations(int a1, DWORD a2)
{
  void *result; // eax
  unsigned int v3; // edx
  int v4; // ecx
  int i; // eax

  result = (void *)Time_Now(a1, g_CastleProductionLicenceGridAnimLastTickMs + 10);
  if ( v3 <= (unsigned int)result )
  {
    g_CastleProductionLicenceGridAnimLastTickMs = Time_Now(v4, v3);
    for ( i = 0; i != 12; ++i )
      g_CastleProductionSlotAnimFrames[i] = (g_CastleProductionSlotAnimFrames[i] + 1) & 7;
    if ( (g_LicenceGridAddAnimSlotIndex != -1 || g_CastleLicenceRemovalSlotIndex != -1) && ++g_CastleProductionLicenceTransitionFrame == 8 )
    {
      if ( g_CastleLicenceRemovalSlotIndex != -1 )
      {
        Building_RemoveUnitLicence(g_CastleProductionBuildingPtr, *(char *)(g_CastleLicenceRemovalSlotIndex + g_CastleProductionBuildingPtr + 402), a2);
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
int  CastleProduction_DrawProductionStatus(DWORD a1)
{
  int result; // eax
  char *v2; // eax
  int v3; // edi
  int v4; // eax
  int v5[3]; // [esp+0h] [ebp-6Ch]
  int v6[3]; // [esp+Ch] [ebp-60h] BYREF
  int v7[3]; // [esp+18h] [ebp-54h] BYREF
  int v8[3]; // [esp+24h] [ebp-48h]
  int v9[3]; // [esp+30h] [ebp-3Ch]
  int v10[2]; // [esp+3Ch] [ebp-30h]
  char *v11; // [esp+44h] [ebp-28h]
  int v12[9]; // [esp+48h] [ebp-24h]

  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 288, 401, 0x251u, 0x165u, 0x191u, 0x120u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, a1);
  result = g_CastleProductionBuildingPtr;
  if ( BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(g_CastleProductionBuildingPtr) != -1 )
  {
    if ( Building_CountGarrison(g_CastleProductionBuildingPtr) < 12 || BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) > 1 )
    {
      v10[0] = (int)UI_Locale_StatusHeader[0];
      v10[1] = (int)UI_Locale_StatusHeader[1];
      v11 = UI_Locale_StatusHeader[2];
      if ( BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) == 1 )
        v2 = aDZugBisZum;
      else
        v2 = aDZbgeBisZum;
      v7[0] = (int)UI_Locale_StatusLine1[0];
      v7[1] = (int)UI_Locale_StatusLine1[1];
      v7[2] = (int)UI_Locale_StatusLine1[2];
      v8[0] = (int)UI_Locale_StatusDetail_A[0];
      v8[1] = (int)UI_Locale_StatusDetail_A[1];
      v8[2] = (int)UI_Locale_StatusDetail_A[2];
      v9[0] = (int)UI_Locale_StatusDetail_B[0];
      v9[1] = (int)UI_Locale_StatusDetail_B[1];
      v9[2] = (int)UI_Locale_StatusDetail_B[2];
      v5[0] = (int)UI_Locale_StatusDetail_C[0];
      v5[1] = (int)UI_Locale_StatusDetail_C[1];
      v5[2] = (int)UI_Locale_StatusDetail_C[2];
      v11 = v2;
      UI_DrawTextFmt((int)v6, 401, 593, 297, 3, v10[(unsigned __int8)g_LanguageIndex]);
      v3 = v7[(unsigned __int8)g_LanguageIndex];
      UI_DrawTextFmt(v3, 401, 593, 317, 3, v3);
      v4 = BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr);
      if ( v4 == 1 )
      {
        return UI_DrawTextFmt(v3, 401, 593, 337, 3, v9[(unsigned __int8)g_LanguageIndex]);
      }
      else if ( v4 < 2 || v4 > 4 )
      {
        return UI_DrawTextFmt(v3, 401, 593, 337, 3, v8[(unsigned __int8)g_LanguageIndex]);
      }
      else
      {
        return UI_DrawTextFmt(v3, 401, 593, 337, 3, v5[(unsigned __int8)g_LanguageIndex]);
      }
    }
    else
    {
      v12[0] = (int)UI_Locale_StatusHeader_Full[0];
      v12[1] = (int)UI_Locale_StatusHeader_Full[1];
      v12[2] = (int)UI_Locale_StatusHeader_Full[2];
      v6[0] = (int)UI_Locale_StatusLine1_Full[0];
      v6[1] = (int)UI_Locale_StatusLine1_Full[1];
      v6[2] = (int)UI_Locale_StatusLine1_Full[2];
      UI_DrawTextFmt((int)v7, 401, 593, 307, 3, v12[(unsigned __int8)g_LanguageIndex]);
      return UI_DrawTextFmt((int)v7, 401, 593, 327, 3, v6[(unsigned __int8)g_LanguageIndex]);
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
int  UI_DrawActionBox(int a1)
{
  void *v1; // esi
  int result; // eax

  v1 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 425, 285, 0x15Eu, 0x1C2u, 0x11Du, 0x1A9u);
  result = UI_DrawTextFmt(a1, 285, 349, 430, 3, (int)aD_38);
  g_RenderDevice = v1;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532218: using guessed type int dword_532218;

//----- (00435580) --------------------------------------------------------
int UI_GetGridIndexFromMouse()
{
  int v0; // eax
  int v1; // ebx
  int v2; // ecx
  int v3; // eax

  v0 = g_MouseCursorRawX >> g_CursorCoordShift;
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= 426
    && g_MouseCursorRawY >> g_CursorCoordShift >= 32
    && (v1 = (g_MouseCursorRawY >> g_CursorCoordShift) - 32, (v0 - 426) % 48 <= 33)
    && v1 % 82 <= 64
    && (v2 = (v0 - 426) / 48, v3 = v1 / 82, v2 < 4)
    && v3 < 3 )
  {
    return v2 + 4 * v3;
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
int  CastleProduction_SetExitSignal(int a1)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_CastleProductionExitSignal = v3;
  return result;
}
// 43562B: variable 'v3' is possibly undefined
// 532210: using guessed type int g_CastleProductionExitSignal;

//----- (00435640) --------------------------------------------------------
int  CastleProduction_SelectPreviousAvailableUnit(int a1, int a2, DWORD a3, int a4, int a5)
{
  int v5; // ecx
  int v6; // ecx

  UIWidget_ShowPressedState(a1);
  if ( g_CastleProductionSelectedAvailableUnitIndex )
    --g_CastleProductionSelectedAvailableUnitIndex;
  CastleProduction_RedrawSelectedUnitPanel(v5, a2, a3, a4, a5);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
  return UIWidget_ShowReleasedState(v6, v6);
}
// 43565E: variable 'v5' is possibly undefined
// 435675: variable 'v6' is possibly undefined
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];

//----- (00435680) --------------------------------------------------------
int  CastleProduction_SelectNextAvailableUnit(int a1, int a2, DWORD a3, int a4, int a5)
{
  int v5; // ecx
  int v6; // ecx

  UIWidget_ShowPressedState(a1);
  if ( g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex + 1] != -1 )
    ++g_CastleProductionSelectedAvailableUnitIndex;
  CastleProduction_RedrawSelectedUnitPanel(v5, a2, a3, a4, a5);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
  return UIWidget_ShowReleasedState(v6, v6);
}
// 43569E: variable 'v5' is possibly undefined
// 4356B5: variable 'v6' is possibly undefined
// 53221C: using guessed type int dword_53221C;
// 532220: using guessed type int dword_532220[];
// 532228: using guessed type int dword_532228[40];

//----- (004356C0) --------------------------------------------------------
int  CastleProduction_HandleBuyLicenceAction(int a1, DWORD a2, int a3)
{
  int v4; // ecx
  int v5; // ecx
  int i; // ecx
  int v8; // esi
  int v9; // ecx
  int v10; // edx
  void *v11; // ecx
  int v12; // ecx
  int v13; // [esp-Ch] [ebp-10h]

  UIWidget_ShowPressedState(a1);
  if ( !Building_BuyUnitLicence(g_CastleProductionBuildingPtr, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v4, a2) )
    return UIWidget_ShowReleasedState(a1, v5);
  v13 = v5;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  for ( i = 0; ; ++i )
  {
    v8 = g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
    if ( *(char *)(i + g_CastleProductionBuildingPtr + 402) == v8 )
      break;
  }
  g_LicenceGridAddAnimSlotIndex = i;
  Audio_PlaySoundEffectByName(aDopen, 64);
  CastleProduction_ReloadLicenceSlotSprite(i, a1);
  UI_DrawActionBox(a3);
  RenderState_SelectCursorDescriptor((int)g_RenderState, v10);
  CastleProduction_RebuildAvailableUnitList(v11);
  CastleProduction_RedrawSelectedUnitPanel(v12, a1, a2, a3, v8);
  return UIWidget_ShowReleasedState(a1, v13);
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
int  CastleProduction_HandleRemoveLicenceAction(int a1)
{
  int v2; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Begin((int)g_RenderState, 0);
  if ( g_ProductionGridSelectedIndex != -1 )
  {
    g_CastleLicenceRemovalSlotIndex = g_ProductionGridSelectedIndex;
    Audio_PlaySoundEffectByName(aDclose_0, 64);
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  }
  return UIWidget_ShowReleasedState(v2, v2);
}
// 435792: variable 'v2' is possibly undefined
// 519808: using guessed type int dword_519808;
// 5322C8: using guessed type int dword_5322C8;
// 532338: using guessed type int dword_532338;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004357E0) --------------------------------------------------------
int  CastleProduction_HandleProduceAction(int result, char a2, DWORD a3)
{
  int v4; // ecx

  if ( g_ProductionGridSelectedIndex != -1 )
  {
    UIWidget_ShowPressedState(result);
    Render_Begin((int)g_RenderState, 0);
    Building_SetUnitProduction(g_CastleProductionBuildingPtr, a2, a3);
    CastleProduction_DrawLicenceGrid();
    CastleProduction_DrawProductionStatus(a3);
    return UIWidget_ShowReleasedState(v4, v4);
  }
  return result;
}
// 43581C: variable 'v4' is possibly undefined
// 532218: using guessed type int dword_532218;
// 5322C8: using guessed type int dword_5322C8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00435830) --------------------------------------------------------
int  CastleProduction_HandleStopProductionAction(int a1, char a2, DWORD a3)
{
  int v3; // ecx
  int v4; // edx
  int v5; // ecx

  UIWidget_ShowPressedState(a1);
  Building_StopUnitProduction(v3, a2, a3);
  CastleProduction_DrawLicenceGrid();
  CastleProduction_DrawProductionStatus(a3);
  return UIWidget_ShowReleasedState(v4, v5);
}
// 43583D: variable 'v3' is possibly undefined
// 43584E: variable 'v4' is possibly undefined
// 43584E: variable 'v5' is possibly undefined
// 532218: using guessed type int dword_532218;

//----- (00435860) --------------------------------------------------------
int  CastleProduction_HandleInfoAction(int a1, int a2, DWORD a3, char a4)
{
  int v5; // ecx
  char *v6; // edx
  int v7; // esi
  int v8; // ecx
  char v10[108]; // [esp-70h] [ebp-74h] BYREF
  int v11; // [esp-4h] [ebp-8h]

  v11 = a2;
  UIWidget_PlayPressedReleaseAnimation(a1);
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Unit_BuildBigInfoGraphicPath(v10, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v5);
  (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, v10);
  (*(void (**)(void))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_CastleProductionPaletteBuffer, 20);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) )
    DD_Pump((int)g_RenderState, (char)g_RenderState);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  if ( g_CastleProductionUseChrTheme )
    v6 = aCastle_chrD_23;
  else
    v6 = aCastle_pogD_23;
  v7 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *))(v7 + 48))(0, v6);
  Palette_QuantizeChannelsInPlace((_BYTE *)g_CastleProductionPaletteBuffer, 6);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  CastleProduction_RedrawSelectedUnitPanel(v8, 20, a3, a4, v7);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(a3);
  UI_DrawActionBox(a4);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_CastleProductionPaletteBuffer, 20);
  return Render_Present((int)g_RenderState);
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
  int metadata_offset; // esi
  int out_index; // ebx
  unit_type unitType; // ecx
  BOOL result; // eax

  (void)this;
  memset(g_CastleProduction_AvailableUnitTypes, 0xFF, 0xA4);
  metadata_offset = 0;
  out_index = 0;
  unitType = UNIT_TYPE_PEASANT;
  do
  {
    result = Building_IsUnitLicenceEligible((char *)g_CastleProductionBuildingPtr, unitType);
    if ( result && *(_DWORD *)((char *)&g_UnitTypeMetadataRecords + metadata_offset) )
      g_CastleProduction_AvailableUnitTypes[out_index++] = unitType;
    ++unitType;
    metadata_offset += 88;
  }
  while ( unitType < 40 );
  return result;
}
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 532218: using guessed type int dword_532218;
// 532220: using guessed type int dword_532220[];

//----- (00435A00) --------------------------------------------------------
int  CastleProduction_HandleLicenceGridClick(DWORD a1, int a2, int a3)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx

  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    result = UI_GetGridIndexFromMouse();
    v4 = result;
    if ( result != -1 )
    {
      result = *(char *)(result + g_CastleProductionBuildingPtr + 402);
      if ( result != -1 && v4 != g_ProductionGridSelectedIndex )
      {
        Audio_PlaySoundEffectByName(aMarker_0, 64);
        g_ProductionGridSelectedIndex = v5;
        v6 = 0;
        v7 = *(char *)(v5 + g_CastleProductionBuildingPtr + 402);
        result = 0;
        if ( g_CastleProduction_AvailableUnitTypes[0] != -1 )
        {
          do
          {
            if ( v7 == g_CastleProduction_AvailableUnitTypes[v6] )
              break;
            a3 = g_CastleProductionAvailableUnitTypesLookahead[v6];
            result += sizeof(int);
            ++v6;
          }
          while ( a3 != -1 );
        }
        if ( v7 == g_CastleProduction_AvailableUnitTypes[v6] && v6 != g_CastleProductionSelectedAvailableUnitIndex )
        {
          g_CastleProductionSelectedAvailableUnitIndex = v6;
          CastleProduction_RedrawSelectedUnitPanel(v7, g_CastleProduction_AvailableUnitTypes[0], a1, a2, a3);
          return Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
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
int  CastleProduction_HandleAvailableUnitStripClick(DWORD a1, int a2, int a3)
{
  int v3; // ebx
  int result; // eax
  int v5; // ecx

  v3 = ((g_MouseCursorRawY >> g_CursorCoordShift) - 35) / 17 - 2;
  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= 40 )
    {
      result = (unsigned __int16)DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x14u) + 40;
      if ( g_MouseCursorRawX >> g_CursorCoordShift <= result
        && v3 >= -2
        && v3 <= 2
        && v3 + g_CastleProductionSelectedAvailableUnitIndex >= 0
        && g_CastleProduction_AvailableUnitTypes[v3 + g_CastleProductionSelectedAvailableUnitIndex] != -1 )
      {
        g_CastleProductionSelectedAvailableUnitIndex += v3;
        Render_Pump();
        CastleProduction_RedrawSelectedUnitPanel(v5, v3, a1, a2, a3);
        Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
        Render_Present((int)g_RenderState);
        return Render_Begin((int)g_RenderState, 0);
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
int  CastleProduction_TickAnimations(DWORD a1)
{
  int v1; // edx
  void *v2; // ecx
  int v3; // ecx

  v1 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  CastleProduction_AnimateSelectedUnitPortrait(v2);
  CastleProduction_TickLicenceGridAnimations(v3, a1);
  return Render_SetResourceHandle((int)&g_MainRenderDevice, v1);
}
// 435B9F: variable 'v2' is possibly undefined
// 435BA4: variable 'v3' is possibly undefined

//----- (00435BC0) --------------------------------------------------------
int  Castle_ShowUnitProductionPanel(int a1, DWORD a2, int a3)
{
  unsigned int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  DWORD v8; // ebp
  char *v9; // edx
  int v10; // esi
  char v11; // bl
  int v12; // ecx
  _DWORD *v13; // eax
  CHAR *v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int (*v23)(void); // ecx
  int v24; // edx
  int v25; // ecx

  g_CastleProductionBuildingPtr = a1;
  g_CastleProductionUseChrTheme = *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(a1 + 2) + 140063);
  g_CastleProductionSelectedAvailableUnitIndex = 0;
  g_CastleProductionSelectedUnitSpriteSet = 0;
  memset(g_CastleProduction_LicenceSlotSpriteHandles, 0, sizeof(g_CastleProduction_LicenceSlotSpriteHandles));
  for ( v24 = 0; v24 != 12; ++v24 )
    g_CastleProductionSlotAnimFrames[v24] = Rng_RandRange(0, 7);
  g_CastleLicenceRemovalSlotIndex = -1;
  g_LicenceGridAddAnimSlotIndex = -1;
  g_ProductionGridSelectedIndex = -1;
  CastleProduction_RebuildAvailableUnitList(0);
  v6 = Mem_Alloc(1024, v5, -1, a2);
  if ( v6 )
    v6 = _wcpp_4_ctor_array__(v7, 256);
  v8 = g_CastleProductionUseChrTheme;
  g_CastleProductionPaletteBuffer = v6;
  if ( g_CastleProductionUseChrTheme )
    v9 = aCastle_chrD_17;
  else
    v9 = aCastle_pogD_17;
  v10 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  v11 = g_CastleProductionPaletteBuffer;
  (*(void (__fastcall **)(_DWORD, char *))(v10 + 48))(0, v9);
  Palette_QuantizeChannelsInPlace((_BYTE *)g_CastleProductionPaletteBuffer, 6);
  v13 = (_DWORD *)Mem_Alloc(4112, v12, v11, v8);
  if ( v13 )
    v13 = DLXSpriteSet_Load(v13, g_CastleProductionUseChrTheme ? aCastle_chrD_19 : aCastle_pogD_19);
  g_BuildingUiDlxSpriteSet = (int)v13;
  if ( g_CastleProductionUseChrTheme )
    v14 = aCastle_chrD_19;
  else
    v14 = aCastle_pogD_19;
  Palette_LoadOrBuildBlendLookupTable(v14, g_CastleProductionPaletteBuffer, g_CastleProductionUseChrTheme, v8);
  Render_LoadResourceSprite_v4(5, (_BYTE *)g_CastleProductionPaletteBuffer, v15, v11, v8);
  Render_LoadResourceSprite_v4(20, (_BYTE *)g_CastleProductionPaletteBuffer, v16, v11, v8);
  Render_LoadResourceSprite_v4(9, (_BYTE *)g_CastleProductionPaletteBuffer, v17, v11, v8);
  Render_LoadResourceSprite_v4(7, (_BYTE *)g_CastleProductionPaletteBuffer, v18, v11, v8);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)g_CastleProductionPaletteBuffer, v19, v11, v8);
  UI_SetActiveWidgetTable(8);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_CastleProductionPaletteBuffer, v20, v8);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  RenderState_SelectCursorDescriptor((int)g_RenderState, v21);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  CastleProduction_RedrawSelectedUnitPanel(v22, 20, v8, a3, v10);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(v8);
  UI_DrawActionBox(a3);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_CastleProductionPaletteBuffer, 20);
  Render_Present((int)g_RenderState);
  g_CastleProductionExitSignal = 0;
  g_ActiveDialogAnimationTickHook = (int (*)(void))CastleProduction_TickAnimations;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    CastleProduction_TickAnimations(v8);
    UI_RunHoverTooltipZones(g_CastleUnitProductionTooltipZone);
    g_RenderDevice = &g_MainRenderDevice;
    if ( !UIWidgetTable_PollHoverAndActions(g_CastleUnitProductionWidgetTable, v8) )
    {
      CastleProduction_HandleLicenceGridClick(v8, (int)&g_MainRenderDevice, (int)g_CastleUnitProductionWidgetTable);
      CastleProduction_HandleAvailableUnitStripClick(v8, (int)&g_MainRenderDevice, (int)g_CastleUnitProductionWidgetTable);
    }
  }
  while ( !g_CastleProductionExitSignal );
  g_ActiveDialogAnimationTickHook = v23;
  DLXSpriteSet_ReleaseAndClear(&g_BuildingUiDlxSpriteSet);
  if ( g_CastleProductionSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_CastleProductionSelectedUnitSpriteSet);
  for ( v24 = 0; v24 != 12; ++v24 )
  {
    if ( g_CastleProduction_LicenceSlotSpriteHandles[v24] )
    {
      nfree_(g_CastleProduction_LicenceSlotSpriteHandles[v24]);
      g_CastleProduction_LicenceSlotSpriteHandles[v24] = 0;
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
int  Palette_LoadOrBuildBlendLookupTable(CHAR *a1, int a2, int a3, DWORD a4)
{
  unsigned int cube_size;
  int query_handle;
  int output_handle;
  CHAR path[256];

  (void)a3;
  strcpy(path, aGfx_5);
  strcat(path, a1);
  strcat(path, a_mtb);
  query_handle = FileSystem_ResolveReadPath(path, 0);
  if ( query_handle )
  {
    cube_size = 1u << g_Palette_ColorCubeBits;
    cube_size *= cube_size * cube_size;
    g_Palette_ActivePalettePtr = a2;
    Compat_QueryRead(query_handle, g_Rgb15ToPaletteLut, (int)cube_size);
    return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  }

  Palette_BuildNearestColorLUT(a2);
  output_handle = IO_FOpen(path, (unsigned __int8 *)aWb_0, 0, a4);
  cube_size = 1u << g_Palette_ColorCubeBits;
  cube_size *= cube_size * cube_size;
  fwrite_(g_Rgb15ToPaletteLut, (int)cube_size, output_handle, 1);
  return fclose_(output_handle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 519A10: using guessed type int dword_519A10;
// 519A18: using guessed type char byte_519A18;

//----- (00435FE0) --------------------------------------------------------
int  BuildingTransferDialog_DrawSourceRemainingValue(DWORD a1, int a2)
{
  void *v2; // esi
  int v3; // edx
  int result; // eax

  v2 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, a1);
  Render_SaveBackbuffer(v3);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 48, 400, 0x1BBu, 0x3Cu, 0x190u, 0x30u);
  result = UI_DrawTextFmt(a2, 347, 445, 48, 3, (int)aD_39);
  g_RenderDevice = v2;
  return result;
}
// 436001: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532354: using guessed type int dword_532354;

//----- (00436060) --------------------------------------------------------
int  BuildingTransferDialog_DrawTransferAmountValue(DWORD a1, int a2)
{
  void *v2; // esi
  int v3; // edx
  int result; // eax

  v2 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, a1);
  Render_SaveBackbuffer(v3);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x12Cu, 0x224u, 0x110u);
  result = UI_DrawTextFmt(a2, 548, 601, 272, 3, (int)aD_40);
  g_RenderDevice = v2;
  return result;
}
// 436081: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532350: using guessed type int dword_532350;

//----- (004360E0) --------------------------------------------------------
int  BuildingTransferDialog_HandleExitButtonPress(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_BuildingTransferDialogExitScratch = v4;
  return result;
}
// 4360EB: variable 'v4' is possibly undefined
// 53234C: using guessed type int dword_53234C;

//----- (00436100) --------------------------------------------------------
int  BuildingTransferDialog_CommitTransfer(int a1, int a2, DWORD a3, double a4)
{
  int result; // eax
  int v6; // esi

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  if ( g_Building_TransferAmount )
  {
    v6 = g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex];
    if ( v6 == -2 )
      v6 = -1;
    Building_Transfer((g_BuildingTransferSourcePtr - (gameData + 509674)) / 467, v6, 1, g_Building_TransferAmount, a4);
    g_Building_TransferAmount = 0;
    BuildingTransferDialog_DrawTransferAmountValue(a3, 467);
    return BuildingTransferDialog_DrawSourceRemainingValue(a3, 467);
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 532350: using guessed type int dword_532350;
// 532354: using guessed type int dword_532354;
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532360: using guessed type __int16 g_BuildingTransferTargetIds[];

//----- (00436180) --------------------------------------------------------
int  BuildingTransferDialog_IncreaseTransferAmount(int a1)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  DWORD v12; // ebp
  int v13; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount += 10;
  v4 = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)g_RenderState, v4);
    v7 = Time_Now(v6, v5);
    v9 = Time_Now(v8, v7);
    g_Building_TransferAmount = 10 * ((v4 + (v10 - v11) * (v9 - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount > 1000 )
      g_Building_TransferAmount = 1000;
    v12 = *(_DWORD *)(g_BuildingTransferSourcePtr + 438);
    if ( g_Building_TransferAmount > v12 )
    {
      v12 = 10;
      g_Building_TransferAmount = 10 * (*(_DWORD *)(g_BuildingTransferSourcePtr + 438) / 0xAu);
    }
    BuildingTransferDialog_DrawTransferAmountValue(v12, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v13);
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
int  BuildingTransferDialog_DecreaseTransferAmount(int a1)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // ecx

  UIWidget_ShowPressedState(a1);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount -= 10;
  v4 = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)g_RenderState, v4);
    v7 = Time_Now(v6, v5);
    v9 = Time_Now(v8, v7);
    g_Building_TransferAmount = 10 * ((v4 - (v10 - v11) * (v9 - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount < 0 )
      g_Building_TransferAmount = 0;
    BuildingTransferDialog_DrawTransferAmountValue((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(a1, v12);
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
int  BuildingTransferTargetList_SetDrawOrigin(int result, int a2)
{
  g_BuildingTransferTargetListDrawX = result;
  g_BuildingTransferTargetListDrawY = a2;
  return result;
}
// 53242C: using guessed type int g_BuildingTransferTargetListDrawX;
// 532430: using guessed type int g_BuildingTransferTargetListDrawY;

//----- (00436620) --------------------------------------------------------
void * BuildingTransferTargetList_Draw(int a1, DWORD a2)
{
  _DWORD *v2; // eax
  int row_y_offset; // ebp
  int target_index; // edi
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
    v2 = (_DWORD *)Mem_Alloc(4112, a1, 0, a2);
    if ( v2 )
      v2 = DLXSpriteSet_Load(v2, aCas_list_s32);
    g_BuildingTransferTargetListSpriteSet = (int)v2;
    DLXSpriteSet_DrawFormattedText((DWORD)v2, -1, a1, aCas_list_pal);
  }
  Render_ReleaseSurface(5, a2);
  row_index = g_BuildingTransferTargetListIndex - 2;
  row_y_offset = 0;
  row_bottom = 18;
  while ( row_index <= g_BuildingTransferTargetListIndex + 2 )
  {
    Render_FillRect(
      (_DWORD *)g_PrimaryRenderSurface,
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
        v15[0] = (int)g_BuildingTransferOutsideCastleLabel[0];
        v15[1] = (int)g_BuildingTransferOutsideCastleLabel[1];
        v15[2] = (int)g_BuildingTransferOutsideCastleLabel[2];
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
          (int)aD_10,
          *(unsigned __int16 *)(building_record + 430));
        v13 = DLX_GetSpriteForChar(g_BuildingTransferTargetListSpriteSet, 2);
        Compat_RenderDeviceDrawMenuSprite(
          g_BuildingTransferTargetListDrawX + 170,
          row_y_offset + g_BuildingTransferTargetListDrawY - 2,
          v13,
          1);
        UI_DrawText(
          g_BuildingTransferTargetListDrawX + 206,
          row_y_offset + g_BuildingTransferTargetListDrawY,
          (int)aD_11,
          *(_DWORD *)(building_record + 438));
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
int  BuildingTransferTargetList_SelectPrevious(int a1, DWORD a2)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(a1);
  if ( g_BuildingTransferTargetListIndex )
    --g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_previous old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, a2);
  return UIWidget_ShowReleasedState(a1, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;

//----- (00436930) --------------------------------------------------------
int  BuildingTransferTargetList_SelectNext(int a1, DWORD a2)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(a1);
  if ( g_BuildingTransferTargetIdsLookahead[g_BuildingTransferTargetListIndex] != -1 )
    ++g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_next old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, a2);
  return UIWidget_ShowReleasedState(a1, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532362: using guessed type __int16 word_532362[99];

//----- (00436970) --------------------------------------------------------
int  BuildingTransferTargetList_Rebuild(int a1, int a2)
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
  insert_index = a2 ? 1 : 0;
  do
  {
    building_record = result + gameData + BUILDING_TABLE_OFFSET;
    if ( *(char *)(result + gameData + 509678) != -1
      && *(_BYTE *)(result + gameData + 509678)
      && *(unsigned __int8 *)(building_record + 2) == current_player
      && building_record != a1
      && !*(_WORD *)(building_record + 16)
      && insert_index < BUILDING_TRANSFER_TARGET_LIST_CAPACITY )
    {
      g_BuildingTransferTargetIds[insert_index] = building_index;
      ++insert_index;
    }
    ++building_index;
    result += 467;
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
int  BuildingTransferTargetList_HandleClick(DWORD a1)
{
  int v2; // ebx
  int result; // eax

  v2 = ((g_MouseCursorRawY >> g_CursorCoordShift) - g_BuildingTransferTargetListDrawY) / 18 - 2;
  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= g_BuildingTransferTargetListDrawX )
    {
      result = g_BuildingTransferTargetListDrawX + 266;
      if ( g_MouseCursorRawX >> g_CursorCoordShift <= g_BuildingTransferTargetListDrawX + 266
        && v2 >= -2
        && v2 <= 2
        && v2 + g_BuildingTransferTargetListIndex >= 0 )
      {
        result = g_BuildingTransferTargetIds[v2 + g_BuildingTransferTargetListIndex];
        if ( result != -1 )
        {
          g_BuildingTransferTargetListIndex += v2;
          Render_Pump();
          BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, a1);
          Render_Present((int)g_RenderState);
          return Render_Begin((int)g_RenderState, 0);
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
int BuildingTransferTargetList_FreeSpriteSet()
{
  int result; // eax

  if ( g_BuildingTransferTargetListSpriteSet )
    result = DLXSpriteSet_ReleaseAndClear(&g_BuildingTransferTargetListSpriteSet);
  g_BuildingTransferTargetListSpriteSet = 0;
  return result;
}
// 532428: using guessed type int g_BuildingTransferTargetListSpriteSet;

//----- (00436B20) --------------------------------------------------------
int  UI_DrawFormattedTokenLine(int a1, int a2, int a3, int a4)
{
  int v6; // esi
  int result; // eax
  unsigned __int8 *v8; // ecx
  int v9; // ecx
  _BYTE *v10; // ecx
  _BYTE *v11; // ecx
  char *v12; // eax
  int v13; // ecx
  _BYTE *v14; // edx
  char *v15; // [esp+0h] [ebp-18h]
  int v16; // [esp+4h] [ebp-14h]
  char v17; // [esp+8h] [ebp-10h]

  v6 = a2 - a1;
  v16 = 0;
  v15 = (char *)&g_UiFormattedMessageTemplateTable + 150 * a3;
  do
  {
    result = (int)&v15[50 * (unsigned __int8)g_LanguageIndex];
    v8 = (unsigned __int8 *)(result + v16);
    if ( !*(_DWORD *)(result + v16 + 1) )
      break;
    if ( *v8 == 4 && (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(v8 + 1)) > v6 )
    {
      v10 = *(_BYTE **)(v8 + 1);
      while ( (unsigned __int16)Render_LoadResourceSprite_v3(v10) > v6 )
      {
        v12 = TextSprite_FindWordWrapBreak(v11, v6);
        v17 = *v12;
        *v12 = 0;
        UI_DrawTextFmt(a1, a1, a2, a4, 4, v13);
        *v14 = v17;
        a4 += UI_GetTextXOffset(g_ActiveTextSpriteSlot);
      }
      UI_DrawTextFmt(a1, a1, a2, a4, 1, (int)v11);
    }
    else
    {
      UI_DrawTextFmt(a1, a1, a2, a4, *v8, *(_DWORD *)(v8 + 1));
    }
    result = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
    a4 += result;
    v16 = v9 + 5;
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
  g_BattleAiCandidateQueue_Vtable = (int)&g_WCIsvListBaseVariant134_Vtable;
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
int  UnitBattle_ResetAiReachGridForSide(int a1)
{
  int v1; // edi
  int result; // eax
  int v3; // ecx
  int v4; // ebx
  int v6; // [esp+4h] [ebp-1Ch]

  v1 = 0;
  v6 = 0;
  do
  {
    result = v6 + g_MapData;
    if ( *(__int16 *)(v6 + g_MapData + 852) != -1 )
    {
      result = *(unsigned __int8 *)(result + 854);
      if ( result == a1 )
      {
        v3 = 0;
        v4 = v1 + 160;
        do
        {
          result = v1 + 160 * v3;
          do
          {
            result += 8;
            *(int *)((char *)&g_UnitBattleAiReachGrid + result) = 0;
            *(int *)((char *)&g_UnitBattleAiReachGridCellSecondField + result) = 0;
          }
          while ( result != v4 );
          ++v3;
          v4 += 160;
        }
        while ( v3 < 20 );
      }
    }
    v1 += 3204;
    v6 += 31;
  }
  while ( v1 != 70488 );
  return result;
}
// 532048: using guessed type int g_MapData;
// 532440: using guessed type int dword_532440;
// 532444: using guessed type int dword_532444;

//----- (00436D10) --------------------------------------------------------
signed int  UnitBattle_RetreatUnit(int a1, int a2, char a3, DWORD a4)
{
  int v5; // edx
  __int16 *v6; // ecx
  signed int j; // ebp
  int v8; // ebx
  signed int result; // eax
  int v10; // esi
  int v11; // eax
  int *v12; // eax
  int v13; // ecx
  int v14; // [esp+4h] [ebp-34h]
  int v15; // [esp+8h] [ebp-30h]
  int i; // [esp+Ch] [ebp-2Ch]
  int v17; // [esp+10h] [ebp-28h]
  int v18; // [esp+14h] [ebp-24h]
  int v19; // [esp+18h] [ebp-20h]
  int v20; // [esp+1Ch] [ebp-1Ch]
  int v21; // [esp+20h] [ebp-18h]
  int v22; // [esp+24h] [ebp-14h]

  Debug_Log(a2, a3, a4, (int)aCofnij_oddzial);
  v6 = (__int16 *)(31 * v5 + g_MapData + 852);
  v14 = 0;
  v20 = (unsigned __int16)v6[2];
  v18 = 1;
  v15 = 1;
  v19 = (unsigned __int16)v6[3];
  while ( 2 )
  {
    for ( i = 1; i <= 2; ++i )
    {
      v15 = -v15;
      v17 = 0;
      v21 = v15 * v14 + v19;
      while ( 2 )
      {
        for ( j = 1; j <= 2; ++j )
        {
          v18 = -v18;
          v22 = v18 * v17 + v20;
          if ( v22 < 0 )
            v22 = 0;
          if ( v22 > *(_DWORD *)(g_MapData + 804) )
            v22 = *(_DWORD *)(g_MapData + 804);
          if ( v21 < 0 )
            v21 = 0;
          v8 = *(_DWORD *)(g_MapData + 800);
          if ( v21 > v8 )
            v21 = *(_DWORD *)(g_MapData + 800);
          if ( *(__int16 *)(40 * v22 + g_MapData + 2 * v21 + 1534) == -1 )
          {
            v8 = v21;
            if ( UnitBattle_GetTileMoveCostOrZero(*v6, v22, v21) )
            {
              v6[2] = v22;
              v10 = 0;
              v6[3] = v21;
              while ( 1 )
              {
                v11 = v10 + g_MapData;
                if ( *(__int16 *)(v10 + g_MapData + 852) != -1 && *(_BYTE *)(v11 + 854) != *((_BYTE *)v6 + 2) )
                {
                  v8 = *(unsigned __int16 *)(v11 + 858);
                  if ( UnitBattle_IsTileWithinRange(a1, *(unsigned __int16 *)(v11 + 856), (unsigned __int16)v8) )
                  {
                    v6[2] = v20;
                    v6[3] = v19;
                    g_UnitBattleScanTileRow = *(unsigned __int16 *)(v10 + g_MapData + 856);
                    v8 = v21;
                    g_BattleTargetTileCol = *(unsigned __int16 *)(v10 + g_MapData + 858);
                    v12 = UnitBattle_MoveTrack(a1, v22, (int)v6, v21, j);
                    *(_DWORD *)((char *)v6 + 23) = v12;
                    if ( v12 )
                      break;
                  }
                }
                v10 += 31;
                if ( v10 >= 682 )
                  goto LABEL_14;
              }
              UnitBattle_Move(a1, (int)v6, v21, j);
              if ( *(_DWORD *)(v13 + 23) )
                j__nfree_();
              result = 1;
              *(_DWORD *)(v13 + 23) = 0;
              return result;
            }
          }
LABEL_14:
          ;
        }
        v17 = v8 + 1;
        if ( v8 + 1 <= 2 )
          continue;
        break;
      }
    }
    if ( ++v14 <= 2 )
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
BOOL  UnitBattle_IsTileWithinMinRange(int a1, int a2, int a3)
{
  int unit_record;
  signed int distance; // eax

  if ( !g_MapData || a1 < 0 || a1 >= 22 )
    return 0;
  unit_record = g_MapData + 31 * a1 + 852;
  if ( *(__int16 *)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 4) - a2)
       * (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 4) - a2)
       + (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 6) - a3)
       * (*(unsigned __int16 *)(31 * a1 + g_MapData + 852 + 6) - a3));
  return distance <= (unsigned __int8)g_UnitTypeMinRange_512583[88 * *(__int16 *)unit_record];
}
// 532048: using guessed type int g_MapData;

//----- (004370B0) --------------------------------------------------------
signed int  UnitBattle_MoveShootingUnit(int a1, int a2, char a3, DWORD a4)
{
  int v4; // edx
  DWORD v5; // ebp
  int v6; // esi
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // esi
  int v13; // ecx
  int v14; // edx
  signed int result; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // edi
  int *v21; // eax
  int v22; // ebx
  int v23; // edi
  int v24; // ecx
  int v25; // ebx
  int v26; // ecx
  int v27; // esi
  int v28; // ecx
  int v29; // ecx
  int v30; // esi
  int v31; // ebx
  int v32; // ecx
  int v33; // edx
  int v34; // edx
  __int16 v35; // [esp+0h] [ebp-2Ch]
  __int16 v36; // [esp+4h] [ebp-28h]
  int v38; // [esp+14h] [ebp-18h]

  Debug_Log(a1, a3, a4, (int)aRuch_oddzialem);
  v5 = 31 * v4;
  v6 = g_MapData + 852 + 31 * v4;
  g_BattleShootingUnitMoveActiveFlag = 1;
  if ( UnitBattle_IsTileWithinRange(v7, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    v9 = g_MapData + 40 * g_UnitBattleScanTileRow;
    v10 = *(__int16 *)(v9 + 2 * g_BattleTargetTileCol + 1534);
    if ( v10 != -1 )
    {
      v11 = *(__int16 *)(v9 + 2 * g_BattleTargetTileCol + 1534);
      v12 = 31 * v10;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        v14 = UnitBattle_Shot(v13, v11);
        if ( !v14 && *(unsigned __int8 *)(v5 + g_MapData + 860) < 5u )
          break;
        if ( !v14 && *(unsigned __int8 *)(v5 + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(g_MapData + v5 + 852) == -1 )
          break;
        if ( *(__int16 *)(v12 + g_MapData + 852) == -1 )
          return 1;
      }
      return 0;
    }
  }
  if ( UnitBattle_IsTileWithinMinRange(v8, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    result = UnitBattle_RetreatUnit(v16, v16, g_BattleTargetTileCol, v5);
    if ( !result )
      return result;
  }
  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
    && *(unsigned __int8 *)(g_MapData + 31 * v16 + 854) == *(_DWORD *)(g_MapData + 836) )
  {
    v17 = UnitBattle_MoveTrackNearWall(v16, g_UnitBattleScanTileRow, g_BattleTargetTileCol, v5);
  }
  else
  {
    v17 = (int *)UnitBattle_MoveTrackNear(v16, v16, g_BattleTargetTileCol, v5);
  }
  *(_DWORD *)(v6 + 23) = v17;
  if ( !*(_DWORD *)(v6 + 23) )
    *(_DWORD *)(v6 + 23) = UnitBattle_MoveTrackForce(v18, g_BattleTargetTileCol, v5);
  if ( !*(_DWORD *)(v6 + 23) )
    return 0;
  if ( UnitBattle_IsTileWithinRange(v18, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    if ( !*(_DWORD *)(v6 + 23) )
      goto LABEL_41;
  }
  else
  {
    v20 = -1;
    v35 = *(_WORD *)(v6 + 4);
    HIWORD(v38) = 0;
    v36 = *(_WORD *)(v6 + 6);
    LOBYTE(v38) = *(_BYTE *)(v6 + 4);
    while ( HIWORD(v38) <= *(unsigned __int8 *)(v6 + 8) - 5 && **(_DWORD **)(v6 + 23) && v20 == -1 )
    {
      if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
      {
        v20 = 1;
      }
      else
      {
        v21 = *(int **)(v6 + 23);
        v22 = *v21 - 1;
        *v21 = v22;
        v38 = v21[v22 + 1];
        if ( *(unsigned __int8 *)(v6 + 8) >= HIWORD(v38) + 5 )
        {
          *(_WORD *)(v6 + 4) = (unsigned __int8)v38;
          *(_WORD *)(v6 + 6) = BYTE1(v38);
        }
      }
    }
    if ( v20 == -1 )
    {
      if ( *(_DWORD *)(v6 + 23) )
        j__nfree_();
      *(_DWORD *)(v6 + 23) = 0;
      return 0;
    }
    *(_WORD *)(v6 + 4) = v35;
    v23 = *(_DWORD *)(v6 + 23);
    *(_WORD *)(v6 + 6) = v36;
    if ( v23 )
      j__nfree_();
    *(_DWORD *)(v6 + 23) = UnitBattle_MoveTrack(v19, (unsigned __int8)v38, v19, BYTE1(v38), 0xFFFFFFFF);
    UnitBattle_Move(v24, v24, BYTE1(v38), 0xFFFFFFFF);
    if ( !*(_DWORD *)(v6 + 23) )
      goto LABEL_40;
  }
  j__nfree_();
LABEL_40:
  *(_DWORD *)(v6 + 23) = 0;
LABEL_41:
  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) <= 0
    || *(unsigned __int8 *)(g_MapData + 31 * v19 + 854) != *(_DWORD *)(g_MapData + 836)
    || (v25 = *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), v25 != -1)
    && *(unsigned __int8 *)(31 * v25 + g_MapData + 854) != a2 )
  {
    if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    {
      v30 = *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
      v31 = 31 * v29;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        v33 = UnitBattle_Shot(v32, v30);
        if ( !v33 && *(unsigned __int8 *)(v31 + g_MapData + 860) < 5u )
          break;
        if ( !v33 && *(unsigned __int8 *)(v31 + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(g_MapData + v31 + 852) == -1 )
          return 0;
        if ( *(__int16 *)(31 * v30 + g_MapData + 852) == -1 )
          return 1;
      }
    }
    return 0;
  }
  if ( !UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    return 0;
  v27 = 31 * v26;
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( *(char *)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) <= 0 )
      return 1;
    v34 = UnitBattle_ShotWall(v28, g_UnitBattleScanTileRow);
    if ( !v34 && *(unsigned __int8 *)(v27 + g_MapData + 860) < 5u )
      return 0;
  }
  while ( v34 || *(unsigned __int8 *)(v27 + g_MapData + 860) < 5u );
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
int * UnitBattle_EstimateDamageScoreAgainstUnit(int a1, DWORD a2)
{
  __int16 *v4; // esi
  int v5; // eax
  int *result; // eax
  char *v7; // ecx
  int v8; // eax
  int v9; // ecx
  __int16 *v10; // edx
  int *v11; // ebp
  __int16 *v12; // edx
  int *v13; // ebx
  bool i; // zf
  int *v15; // edi
  int v16; // ecx
  __int16 *v17; // edx
  int *v18; // ebp
  int v19; // edx
  int *v20; // ebx
  int v21; // edx
  char v22; // [esp+0h] [ebp-40h]
  char v23; // [esp+0h] [ebp-40h]
  char v24; // [esp+4h] [ebp-3Ch]
  int v25; // [esp+8h] [ebp-38h] BYREF
  int v26; // [esp+Ch] [ebp-34h] BYREF
  int v27; // [esp+10h] [ebp-30h]
  int v28; // [esp+14h] [ebp-2Ch]
  int v29; // [esp+18h] [ebp-28h]
  int v30; // [esp+1Ch] [ebp-24h]
  __int16 *v31; // [esp+20h] [ebp-20h]
  int v32; // [esp+24h] [ebp-1Ch]
  int *v33; // [esp+28h] [ebp-18h]

  v4 = (__int16 *)(g_MapData + 852 + 31 * a1);
  v27 = (unsigned __int16)v4[2];
  v28 = (unsigned __int16)v4[3];
  v24 = *((_BYTE *)v4 + 8);
  v5 = *v4;
  v31 = (__int16 *)(31 * a2 + g_MapData + 852);
  if ( v5 == UNIT_TYPE_RAM )
    return 0;
  result = (int *)UnitBattle_MoveTrackNear(
                    a1,
                    31 * a2 + g_MapData + 852,
                    *(unsigned __int16 *)(31 * a2 + g_MapData + 852 + 6),
                    a2);
  v33 = result;
  if ( result )
  {
    v29 = Unit_CalcEffectivenessA(v7, 0);
    v8 = Unit_CalcEffectivenessC(v31);
    if ( v8 > v9 )
      v29 = v8;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(g_MapData + 31 * a1 + 852)] )
    {
      v30 = *((char *)v31 + 9);
      HIWORD(v32) = 0;
      for ( i = *v33 == 0; ; i = *v33 == 0 )
      {
        if ( i || !v33 )
        {
          v4[2] = v27;
          v4[3] = v28;
          v15 = v33;
          *((_BYTE *)v4 + 8) = v24;
          if ( !v15 )
            return 0;
          goto LABEL_41;
        }
        if ( UnitBattle_IsUnitWithinRange(a1, a2) )
          break;
        v19 = *v33 - 1;
        v20 = v33;
        *v33 = v19;
        v32 = v20[v19 + 1];
        v4[2] = (unsigned __int8)v32;
        v4[3] = BYTE1(v32);
        v21 = HIWORD(v32) - v16;
        if ( v21 > *((unsigned __int8 *)v4 + 8) )
        {
          v4[2] = v27;
          v4[3] = v28;
          *((_BYTE *)v4 + 8) = v24;
LABEL_41:
          j__nfree_();
          return 0;
        }
        *((_BYTE *)v4 + 8) -= v21;
      }
      while ( *((unsigned __int8 *)v4 + 8) >= HIWORD(v32) + 5 )
      {
        *((_BYTE *)v31 + 9) = UnitBattle_CalcShotTargetHealthAfterHit(a1, a2);
        *((_BYTE *)v4 + 8) -= 5;
      }
      v26 = v30;
      v4[2] = v27;
      v4[3] = v28;
      v17 = v31;
      *((_BYTE *)v4 + 8) = v24;
      v18 = v33;
      *((_BYTE *)v17 + 9) = v30;
      if ( v18 )
        j__nfree_();
      return (int *)(v29 * (v30 - v26) / 100);
    }
    else
    {
      if ( !v33 )
        return 0;
      if ( *v33 )
      {
        v32 = v33[1];
        if ( *((unsigned __int8 *)v4 + 8) < HIWORD(v32) + 5 )
        {
          UnitBattle_CalcMeleeExchange(a1, a2, &v26, &v25, 0);
          if ( v33 )
          {
            j__nfree_();
            return 0;
          }
          return 0;
        }
        v22 = *((_BYTE *)v4 + 9);
        v30 = *((char *)v31 + 9);
        while ( *((unsigned __int8 *)v4 + 8) >= HIWORD(v32) + 5 )
        {
          UnitBattle_CalcMeleeExchange(a1, a2, &v26, &v25, 0);
          *((_BYTE *)v4 + 9) = v25;
          *((_BYTE *)v31 + 9) = v26;
          *((_BYTE *)v4 + 8) -= 5;
        }
        *((_BYTE *)v4 + 8) = v24;
        v10 = v31;
        *((_BYTE *)v4 + 9) = v22;
        v11 = v33;
        *((_BYTE *)v10 + 9) = v30;
        if ( v11 )
          j__nfree_();
        return (int *)(v29 * (v30 - v26) / 100);
      }
      else if ( *((unsigned __int8 *)v4 + 8) < 5u )
      {
        v30 = *(char *)(31 * a2 + g_MapData + 861);
        UnitBattle_CalcMeleeExchange(a1, a2, &v26, &v25, 0);
        j__nfree_();
        return (int *)(v29 * (v30 - v26) / 100);
      }
      else
      {
        v23 = *((_BYTE *)v4 + 9);
        v30 = *((char *)v31 + 9);
        while ( *((unsigned __int8 *)v4 + 8) >= 5u )
        {
          UnitBattle_CalcMeleeExchange(a1, a2, &v26, &v25, 0);
          *((_BYTE *)v4 + 9) = v25;
          *((_BYTE *)v31 + 9) = v26;
          *((_BYTE *)v4 + 8) -= 5;
        }
        *((_BYTE *)v4 + 8) = v24;
        v12 = v31;
        *((_BYTE *)v4 + 9) = v23;
        v13 = v33;
        *((_BYTE *)v12 + 9) = v30;
        if ( v13 )
          j__nfree_();
        return (int *)(v29 * (v30 - v26) / 100);
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
int  UnitBattle_ScoreTileAgainstRangedUnitsOfSide(int a1, int a2, int a3)
{
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // esi
  int v9; // edx
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // ebx
  int v16; // esi
  int v17; // edx
  int v18; // edx
  int v20; // ecx
  int v21; // eax
  int *v22; // eax
  int *v23; // ecx
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
  int *v35; // ecx
  int v36; // eax
  int v37; // eax
  int v38; // edx
  int *v39; // ecx
  int v40; // edx
  int v41; // ebx
  int v42; // edx
  int v43; // [esp+0h] [ebp-50h]
  __int16 v45; // [esp+8h] [ebp-48h]
  int v46; // [esp+Ch] [ebp-44h]
  int v47; // [esp+10h] [ebp-40h]
  int v48; // [esp+10h] [ebp-40h]
  int v50; // [esp+18h] [ebp-38h]
  int v51; // [esp+1Ch] [ebp-34h]
  int v52; // [esp+20h] [ebp-30h]
  __int16 v53; // [esp+24h] [ebp-2Ch]
  __int16 v54; // [esp+28h] [ebp-28h]
  int v55; // [esp+2Ch] [ebp-24h]
  int v56; // [esp+2Ch] [ebp-24h]
  int v57; // [esp+30h] [ebp-20h]
  int v58; // [esp+34h] [ebp-1Ch]
  __int16 v59; // [esp+38h] [ebp-18h]

  v50 = 0;
  v43 = 0;
  v46 = 31 * a1;
  do
  {
    v3 = *(__int16 *)(g_MapData + v43 + 852);
    if ( v3 != -1 && *(unsigned __int8 *)(g_MapData + v43 + 854) == a2 && g_UnitTypeRole[88 * v3] == 4 )
    {
      Unit_CalcEffectivenessA((char *)(v46 + g_MapData + 852), 0);
      v4 = Unit_CalcEffectivenessC((__int16 *)(v46 + g_MapData + 852));
      if ( v5 <= v4 )
        v6 = Unit_CalcEffectivenessC((__int16 *)(v46 + g_MapData + 852));
      else
        v6 = Unit_CalcEffectivenessA((char *)(v46 + g_MapData + 852), 0);
      v52 = v6;
      v7 = *(unsigned __int16 *)(v43 + g_MapData + 858);
      v57 = *(unsigned __int16 *)(v43 + g_MapData + 856);
      Debug_Log(v43, v7, a3, (int)aOddzial_w_zasi);
      v8 = v46 + g_MapData + 852;
      a3 = (unsigned __int16)v7;
      if ( UnitBattle_IsTileWithinRange(a1, v9, (unsigned __int16)v7)
        && (*(_BYTE *)(v46 + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(v46 + g_MapData + 864)) >> 5) > 0 )
      {
        v10 = 0;
LABEL_10:
        LOBYTE(v10) = *(_BYTE *)(v8 + 8);
        goto LABEL_11;
      }
      v20 = v57;
      if ( *(char *)(g_MapData + 20 * v57 + v7 + 3134) <= 0
        || (v20 = g_MapData + 40 * v57, *(__int16 *)(v20 + 2 * v7 + 1534) != -1)
        && ((v21 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v21 + 852)] & 1) != 0)
         || (*(_BYTE *)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v21 + 864)) >> 5) > 0) )
      {
        v22 = (int *)UnitBattle_MoveTrackNear(a1, v20, v7, (unsigned __int16)v7);
      }
      else
      {
        v22 = UnitBattle_MoveTrackNearWall(a1, v57, v7, (unsigned __int16)v7);
      }
      v23 = v22;
      if ( !v22 )
      {
        v24 = 31 * a1 + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v24 + 852)] )
        {
          if ( (*(_BYTE *)(v24 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v24 + 864)) >> 5) > 0 )
            v23 = UnitBattle_MoveTrackForce(a1, v7, (unsigned __int16)v7);
        }
      }
      if ( !v23 )
      {
        v10 = -1;
        goto LABEL_11;
      }
      if ( !*v23 )
      {
        j__nfree_();
        goto LABEL_10;
      }
      v25 = g_MapData + 31 * a1;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v25 + 852)]
        && (*(_BYTE *)(v25 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v25 + 864)) >> 5) > 0 )
      {
        v45 = *(_WORD *)(v8 + 4);
        HIWORD(v48) = 0;
        v53 = *(_WORD *)(v8 + 6);
        if ( *v23 )
        {
          while ( !UnitBattle_IsTileWithinRange(a1, v57, (unsigned __int16)v7) )
          {
            v30 = *v28 - 1;
            *v28 = v30;
            v48 = v28[v30 + 1];
            if ( HIWORD(v48) > (int)*(unsigned __int8 *)(v8 + 8) )
              goto LABEL_54;
            *(_WORD *)(v8 + 4) = (unsigned __int8)v48;
            *(_WORD *)(v8 + 6) = BYTE1(v48);
            if ( !*v28 )
              goto LABEL_51;
          }
          *(_WORD *)(v8 + 4) = v45;
          *(_WORD *)(v8 + 6) = v53;
          j__nfree_();
          LOBYTE(v29) = *(_BYTE *)(v8 + 8);
          if ( v29 > HIWORD(v48) )
          {
            v10 = v29 - HIWORD(v48);
            goto LABEL_11;
          }
          goto LABEL_48;
        }
LABEL_51:
        if ( UnitBattle_IsTileWithinRange(a1, v57, (unsigned __int16)v7) )
        {
          *(_WORD *)(v8 + 4) = v45;
          *(_WORD *)(v8 + 6) = v53;
          if ( *(unsigned __int8 *)(v8 + 8) > (int)HIWORD(v48) )
          {
            j__nfree_();
            v10 = *(unsigned __int8 *)(v8 + 8) - v31;
            goto LABEL_11;
          }
LABEL_47:
          j__nfree_();
LABEL_48:
          v10 = 0;
          goto LABEL_11;
        }
LABEL_54:
        *(_WORD *)(v8 + 4) = v45;
        *(_WORD *)(v8 + 6) = v53;
        j__nfree_();
      }
      else
      {
        if ( !*v23 )
          goto LABEL_47;
        v47 = v23[1];
        j__nfree_();
        LOWORD(v26) = HIWORD(v47);
        v27 = *(unsigned __int8 *)(v8 + 8);
        if ( v27 <= v26 )
          v10 = 0;
        else
          v10 = v27 - v26;
      }
LABEL_11:
      if ( v52 * (v10 / 5) <= v50 )
        goto LABEL_19;
      Unit_CalcEffectivenessA((char *)(v46 + g_MapData + 852), 0);
      v11 = Unit_CalcEffectivenessC((__int16 *)(v46 + g_MapData + 852));
      if ( v12 <= v11 )
        v13 = Unit_CalcEffectivenessC((__int16 *)(v46 + g_MapData + 852));
      else
        v13 = Unit_CalcEffectivenessA((char *)(v46 + g_MapData + 852), 0);
      v51 = v13;
      LOWORD(v15) = *(_WORD *)(v43 + g_MapData + 858);
      v58 = (unsigned __int16)v15;
      Debug_Log(v14, v15, a3, (int)aOddzial_w_zasi);
      v16 = g_MapData + 852 + v46;
      a3 = v17;
      if ( UnitBattle_IsTileWithinRange(a1, v17, (unsigned __int16)v15)
        && (*(_BYTE *)(v46 + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(v46 + g_MapData + 864)) >> 5) > 0 )
      {
        v18 = 0;
LABEL_17:
        LOBYTE(v18) = *(_BYTE *)(v16 + 8);
LABEL_18:
        v50 = v18 / 5 * v51;
        goto LABEL_19;
      }
      v32 = (unsigned __int16)v15;
      if ( *(char *)((unsigned __int16)v15 + g_MapData + 20 * a3 + 3134) <= 0 )
      {
        v15 = (unsigned __int16)v15;
      }
      else
      {
        v32 = g_MapData + 40 * a3;
        if ( *(__int16 *)(v32 + 2 * (unsigned __int16)v15 + 1534) == -1
          || (v33 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v33 + 852)] & 1) == 0)
          && (*(_BYTE *)(v33 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v33 + 864)) >> 5) <= 0 )
        {
          v34 = UnitBattle_MoveTrackNearWall(a1, a3, (unsigned __int16)v15, a3);
          goto LABEL_61;
        }
        v15 = (unsigned __int16)v15;
      }
      v34 = (int *)UnitBattle_MoveTrackNear(a1, v32, v15, a3);
LABEL_61:
      v35 = v34;
      if ( !v34 )
      {
        v36 = 31 * a1 + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
        {
          if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
            v35 = UnitBattle_MoveTrackForce(a1, (unsigned __int16)v15, a3);
        }
      }
      if ( !v35 )
      {
        v18 = -1;
        goto LABEL_18;
      }
      if ( !*v35 )
      {
        j__nfree_();
        goto LABEL_17;
      }
      v37 = g_MapData + 31 * a1;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v37 + 852)]
        && (*(_BYTE *)(v37 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v37 + 864)) >> 5) > 0 )
      {
        v59 = *(_WORD *)(v16 + 4);
        v54 = *(_WORD *)(v16 + 6);
        HIWORD(v56) = 0;
        if ( *v35 )
        {
          while ( !UnitBattle_IsTileWithinRange(a1, a3, v58) )
          {
            v41 = *v39 - 1;
            *v39 = v41;
            v56 = v39[v41 + 1];
            if ( HIWORD(v56) > (int)*(unsigned __int8 *)(v16 + 8) )
              goto LABEL_89;
            *(_WORD *)(v16 + 4) = (unsigned __int8)v56;
            *(_WORD *)(v16 + 6) = BYTE1(v56);
            if ( !*v39 )
              goto LABEL_86;
          }
          *(_WORD *)(v16 + 4) = v59;
          *(_WORD *)(v16 + 6) = v54;
          j__nfree_();
          LOBYTE(v40) = *(_BYTE *)(v16 + 8);
          if ( v40 > HIWORD(v56) )
          {
            v18 = v40 - HIWORD(v56);
            goto LABEL_18;
          }
LABEL_83:
          v18 = 0;
          goto LABEL_18;
        }
LABEL_86:
        if ( !UnitBattle_IsTileWithinRange(a1, a3, v58) )
        {
LABEL_89:
          *(_WORD *)(v16 + 4) = v59;
          *(_WORD *)(v16 + 6) = v54;
          j__nfree_();
          goto LABEL_18;
        }
        *(_WORD *)(v16 + 4) = v59;
        *(_WORD *)(v16 + 6) = v54;
        if ( *(unsigned __int8 *)(v16 + 8) > (int)HIWORD(v56) )
        {
          j__nfree_();
          v18 = *(unsigned __int8 *)(v16 + 8) - v42;
          goto LABEL_18;
        }
      }
      else if ( *v35 )
      {
        v55 = v35[1];
        j__nfree_();
        LOBYTE(v38) = *(_BYTE *)(v16 + 8);
        if ( v38 <= HIWORD(v55) )
          v18 = 0;
        else
          v18 = v38 - HIWORD(v55);
        goto LABEL_18;
      }
      j__nfree_();
      goto LABEL_83;
    }
LABEL_19:
    v43 += 31;
  }
  while ( v43 != 682 );
  return v50;
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

//----- (004382E0) --------------------------------------------------------
signed int  UnitBattle_ScoreAiActionGridForUnit(int a1, int a2, int a3, signed int a4)
{
  int v5; // ecx
  int v6; // edi
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edi
  int v12; // ecx
  int v13; // esi
  int v14; // ecx
  int i; // ecx
  int v16; // eax
  int *v17; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // edi
  int v21; // ebx
  int v22; // eax
  __int16 v23; // dx
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  DWORD v30; // ebp
  int v31; // esi
  int v32; // ecx
  int v33; // edx
  int v34; // edx
  int v35; // ebp
  int v36; // ebx
  int v37; // ecx
  int v38; // esi
  int v39; // edi
  int v40; // ecx
  int v41; // edx
  int v42; // ecx
  __int64 v43; // rtt
  int v44; // edx
  int v45; // eax
  int v46; // esi
  int v47; // eax
  int v48; // edi
  int v49; // edx
  int v50; // esi
  int v51; // edx
  int v52; // ecx
  int v53; // esi
  int v54; // eax
  int v55; // edi
  int v56; // edx
  int v57; // esi
  int v58; // edx
  int v59; // ecx
  int v60; // esi
  int v61; // eax
  int v62; // edi
  int v63; // esi
  BOOL v64; // eax
  int v65; // ecx
  int v66; // esi
  int v67; // edx
  int v68; // ecx
  int v69; // edx
  int v70; // eax
  int v71; // esi
  int v72; // ecx
  int v73; // edx
  DWORD v74; // ebp
  int v75; // edi
  int v76; // ebx
  int v77; // esi
  int v78; // edx
  int v79; // ecx
  int v80; // ebp
  int v81; // edx
  int v82; // eax
  int v83; // ecx
  int v84; // eax
  int v85; // ebx
  int *v86; // eax
  int *v87; // ecx
  int v88; // eax
  int v89; // eax
  int v90; // edx
  int *v91; // ecx
  int v92; // edx
  int v93; // eax
  int v94; // edx
  int v95; // eax
  int *v96; // eax
  int *v97; // ecx
  int v98; // edx
  int v99; // eax
  int v100; // edx
  int *v101; // ecx
  int v102; // edx
  int v103; // eax
  int v104; // edx
  int v105; // ecx
  int *v106; // eax
  int *v107; // ecx
  int v108; // edx
  int *v109; // ecx
  int v110; // edx
  int v111; // eax
  int v112; // edx
  int v113; // ecx
  int *v114; // eax
  int *v115; // ecx
  int v116; // edx
  int *v117; // ecx
  int v118; // edx
  int v119; // eax
  int v120; // edx
  int v121; // edx
  int *v122; // eax
  int *v123; // ecx
  int v124; // eax
  int v125; // edx
  int *v126; // ecx
  int v127; // edx
  int v128; // ebx
  int v129; // edx
  int v130; // ecx
  int *v131; // eax
  int *v132; // ecx
  int v133; // ebx
  int v134; // ebx
  int v135; // edx
  int *v136; // ecx
  int v137; // edx
  int v138; // ebx
  int v139; // edx
  int v140; // ebx
  int v141; // eax
  __int16 v142; // dx
  int v143; // ebp
  int *v144; // eax
  int v145; // ecx
  int v146; // edx
  int v147; // eax
  int v148; // eax
  int v149; // ecx
  int v150; // esi
  int v151; // edx
  int v152; // ecx
  int v153; // edx
  int v154; // ecx
  int v155; // eax
  int v156; // ebx
  int *v157; // eax
  int *v158; // ecx
  int v159; // eax
  int v160; // eax
  int v161; // edx
  int *v162; // ecx
  int v163; // edx
  int v164; // eax
  int v165; // ebx
  int v166; // edx
  int v167; // [esp+0h] [ebp-E0h]
  __int16 v168; // [esp+Ch] [ebp-D4h]
  __int16 v169; // [esp+10h] [ebp-D0h]
  int v170; // [esp+14h] [ebp-CCh]
  DWORD v171; // [esp+18h] [ebp-C8h]
  int v172; // [esp+1Ch] [ebp-C4h]
  int v173; // [esp+20h] [ebp-C0h]
  int v174; // [esp+20h] [ebp-C0h]
  int v175; // [esp+28h] [ebp-B8h]
  __int16 v176; // [esp+2Ch] [ebp-B4h]
  int v177; // [esp+30h] [ebp-B0h]
  DWORD v178; // [esp+34h] [ebp-ACh]
  int v179; // [esp+3Ch] [ebp-A4h]
  int v180; // [esp+40h] [ebp-A0h]
  int v181; // [esp+40h] [ebp-A0h]
  __int16 v182; // [esp+50h] [ebp-90h]
  __int16 v183; // [esp+54h] [ebp-8Ch]
  int v184; // [esp+64h] [ebp-7Ch]
  int v186; // [esp+6Ch] [ebp-74h]
  __int16 v187; // [esp+70h] [ebp-70h]
  __int16 v188; // [esp+74h] [ebp-6Ch]
  __int16 v189; // [esp+78h] [ebp-68h]
  __int16 v190; // [esp+7Ch] [ebp-64h]
  __int16 v191; // [esp+80h] [ebp-60h]
  __int16 v192; // [esp+84h] [ebp-5Ch]
  __int16 v193; // [esp+88h] [ebp-58h]
  int v194; // [esp+8Ch] [ebp-54h]
  __int16 v195; // [esp+90h] [ebp-50h]
  __int16 v196; // [esp+94h] [ebp-4Ch]
  __int16 v197; // [esp+98h] [ebp-48h]
  __int16 v198; // [esp+A0h] [ebp-40h]
  int v199; // [esp+A4h] [ebp-3Ch]
  int v200; // [esp+A4h] [ebp-3Ch]
  int v201; // [esp+A8h] [ebp-38h]
  int v202; // [esp+A8h] [ebp-38h]
  int v203; // [esp+ACh] [ebp-34h]
  int v204; // [esp+ACh] [ebp-34h]
  int v205; // [esp+B4h] [ebp-2Ch]
  int v206; // [esp+B8h] [ebp-28h]
  int v207; // [esp+B8h] [ebp-28h]
  int v208; // [esp+BCh] [ebp-24h]
  int v209; // [esp+C0h] [ebp-20h]
  int v210; // [esp+C0h] [ebp-20h]
  int v211; // [esp+C4h] [ebp-1Ch]

  v167 = 1;
  switch ( g_UnitBattleAiCurrentPlanMode )
  {
    case 0:
    case 4:
      goto LABEL_29;
    case 1:
      v175 = 801 * a1;
      v211 = 0;
      v177 = 0;
      v186 = 31 * a1;
      do
      {
        if ( *(__int16 *)(v177 + g_MapData + 852) != -1 && *(unsigned __int8 *)(v177 + g_MapData + 854) != a2 )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          v167 = 0;
          v171 = *(unsigned __int16 *)(g_MapData + v177 + 856);
          v184 = *(unsigned __int16 *)(g_MapData + v177 + 858);
          v140 = 160 * v171 + v175 * 4;
          v141 = 2 * v184 + g_MapData + 40 * v171;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v184] + v140) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(g_MapData + v177 + 852)]];
          v142 = *(_WORD *)(v141 + 1534);
          *(_WORD *)(v141 + 1534) = -1;
          v198 = v142;
          v143 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v184] + v140) - 800;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v184] + v140) = v143;
          v144 = UnitBattle_EstimateDamageScoreAgainstUnit(a1, v211);
          v146 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) - 15 * (_DWORD)v144;
          v147 = v177 + g_MapData;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146 - 2 * *(unsigned __int8 *)(v147 + 860);
          v148 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(v211, a2, v143);
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v149] + v140) -= 2 * v148;
          v208 = v149;
          Debug_Log(v149, v140, v171, (int)aOddzial_w_zasi);
          v150 = v186 + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(a1, v151, v152)
            && (*(_BYTE *)(v186 + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(v186 + g_MapData + 864)) >> 5) > 0 )
          {
            v153 = 0;
LABEL_278:
            LOBYTE(v153) = *(_BYTE *)(v150 + 8);
            goto LABEL_279;
          }
          v154 = v208;
          if ( *(char *)(v208 + g_MapData + 20 * v171 + 3134) <= 0 )
          {
            v156 = v208;
          }
          else
          {
            v154 = g_MapData + 40 * v171;
            if ( *(__int16 *)(v154 + 2 * v208 + 1534) == -1
              || (v155 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v155 + 852)] & 1) == 0)
              && (*(_BYTE *)(v155 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v155 + 864)) >> 5) <= 0 )
            {
              v157 = UnitBattle_MoveTrackNearWall(a1, v171, v208, v171);
              goto LABEL_289;
            }
            v156 = v208;
          }
          v157 = (int *)UnitBattle_MoveTrackNear(a1, v154, v156, v171);
LABEL_289:
          v158 = v157;
          if ( !v157 )
          {
            v159 = g_MapData + 31 * a1;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v159 + 852)] )
            {
              if ( (*(_BYTE *)(v159 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v159 + 864)) >> 5) > 0 )
                v158 = UnitBattle_MoveTrackForce(a1, v208, v171);
            }
          }
          if ( !v158 )
            goto LABEL_294;
          if ( !*v158 )
          {
            j__nfree_();
            goto LABEL_278;
          }
          v160 = 31 * a1 + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v160 + 852)]
            && (*(_BYTE *)(v160 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v160 + 864)) >> 5) > 0 )
          {
            v176 = *(_WORD *)(v150 + 4);
            HIWORD(v174) = 0;
            v169 = *(_WORD *)(v150 + 6);
            if ( *v158 )
            {
              while ( !UnitBattle_IsTileWithinRange(a1, v171, v208) )
              {
                v165 = *v162 - 1;
                *v162 = v165;
                v174 = v162[v165 + 1];
                if ( HIWORD(v174) > (int)*(unsigned __int8 *)(v150 + 8) )
                  goto LABEL_317;
                *(_WORD *)(v150 + 4) = (unsigned __int8)v174;
                *(_WORD *)(v150 + 6) = BYTE1(v174);
                if ( !*v162 )
                  goto LABEL_314;
              }
              *(_WORD *)(v150 + 4) = v176;
              *(_WORD *)(v150 + 6) = v169;
              j__nfree_();
              LOWORD(v163) = HIWORD(v174);
              v164 = *(unsigned __int8 *)(v150 + 8);
              if ( v164 > v163 )
              {
                v153 = v164 - v163;
                goto LABEL_279;
              }
LABEL_311:
              v153 = 0;
              goto LABEL_280;
            }
LABEL_314:
            if ( !UnitBattle_IsTileWithinRange(a1, v171, v208) )
            {
LABEL_317:
              *(_WORD *)(v150 + 4) = v176;
              *(_WORD *)(v150 + 6) = v169;
              j__nfree_();
              goto LABEL_280;
            }
            *(_WORD *)(v150 + 4) = v176;
            *(_WORD *)(v150 + 6) = v169;
            if ( *(unsigned __int8 *)(v150 + 8) > (int)HIWORD(v174) )
            {
              j__nfree_();
              v153 = *(unsigned __int8 *)(v150 + 8) - v166;
LABEL_279:
              if ( v153 > -1 )
              {
LABEL_280:
                g_UnitBattleTileScoreGrid[40 * v171 + 2 * v184 + v175] -= 5 * (v153 / 5);
LABEL_281:
                *(_WORD *)(40 * v171 + g_MapData + 2 * v184 + 1534) = v198;
                goto LABEL_282;
              }
LABEL_294:
              g_UnitBattleTileScoreGrid[40 * v171 + 2 * v184 + v175] += 700;
              goto LABEL_281;
            }
          }
          else if ( *v158 )
          {
            v173 = v158[1];
            j__nfree_();
            LOBYTE(v161) = *(_BYTE *)(v150 + 8);
            if ( v161 <= HIWORD(v173) )
            {
              v153 = 0;
              goto LABEL_280;
            }
            v153 = v161 - HIWORD(v173);
            goto LABEL_279;
          }
          j__nfree_();
          goto LABEL_311;
        }
LABEL_282:
        v177 += 31;
        ++v211;
      }
      while ( v211 < 22 );
      return v167;
    case 2:
    case 6:
      if ( a2 == *(_DWORD *)(g_MapData + 836) )
      {
        if ( g_AttackerStartsOnLeft == 1 )
          a4 = 1;
        else
          a4 = -1;
      }
      if ( a2 == *(_DWORD *)(g_MapData + 840) )
      {
        if ( g_DefenderStartsOnLeft == 1 )
          a4 = 1;
        else
          a4 = -1;
      }
      v6 = 801 * a1;
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(31 * a1 + g_MapData + 852),
             *(unsigned __int16 *)(31 * a1 + g_MapData + 856) + 3 * a4,
             *(unsigned __int16 *)(31 * a1 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[120 * a4
                   + 40 * *(unsigned __int16 *)(g_MapData + v5 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v5 + 858)
                   + v6] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v5 + g_MapData + 852),
             4 * a4 + *(unsigned __int16 *)(v5 + g_MapData + 856),
             *(unsigned __int16 *)(v5 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[160 * a4
                   + 40 * *(unsigned __int16 *)(g_MapData + v8 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v8 + 858)
                   + v6] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v8 + g_MapData + 852),
             2 * a4 + *(unsigned __int16 *)(v8 + g_MapData + 856),
             *(unsigned __int16 *)(v8 + g_MapData + 858)) )
      {
        v10 = g_MapData + v9;
        v11 = 160 * (*(unsigned __int16 *)(v10 + 856) + 2 * a4) + v6 * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(v10 + 858)] + v11) -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v9 + g_MapData + 852),
             5 * a4 + *(unsigned __int16 *)(v9 + g_MapData + 856),
             *(unsigned __int16 *)(v9 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[200 * a4
                   + 40 * *(unsigned __int16 *)(g_MapData + v12 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v12 + 858)
                   + v6] -= 500;
        return 0;
      }
      a3 = *(unsigned __int16 *)(v12 + g_MapData + 856);
      v13 = 6 * a4;
      if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(v12 + g_MapData + 852), v13 + a3, *(unsigned __int16 *)(v12 + g_MapData + 858)) )
      {
        v19 = g_MapData + v14;
        v20 = 160 * (v13 + *(unsigned __int16 *)(v19 + 856)) + v6 * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(v19 + 858)] + v20) -= 500;
        return 0;
      }
      for ( i = 0; i < 682; i += 31 )
      {
        v16 = i + g_MapData;
        if ( *(__int16 *)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(v16 + 854) != a2 )
        {
          v17 = (int *)UnitBattle_MoveTrackNear(a1, i, *(unsigned __int16 *)(v16 + 858), a3);
          if ( v17 && *v17 > 3 )
          {
            v18 = v17[*v17 - 3];
            g_UnitBattleTileScoreGrid[801 * a1 + 40 * (unsigned __int8)v18 + 2 * BYTE1(v18)] -= 500;
            j__nfree_();
            return 0;
          }
          if ( v17 )
            j__nfree_();
        }
      }
LABEL_29:
      v194 = 801 * a1;
      v178 = 0;
      v205 = 0;
      v179 = 31 * a1;
      break;
    default:
      return v167;
  }
  while ( 1 )
  {
    if ( *(__int16 *)(v205 + g_MapData + 852) == -1 || *(unsigned __int8 *)(v205 + g_MapData + 854) == a2 )
      goto LABEL_39;
    UnitBattle_UpdateIdleAnimatedUnits();
    v170 = *(unsigned __int16 *)(g_MapData + v205 + 856);
    v172 = *(unsigned __int16 *)(g_MapData + v205 + 858);
    v167 = 0;
    v21 = 160 * v170 + v194 * 4;
    v22 = 40 * v170 + g_MapData + 2 * v172;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v172] + v21) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88
                                                                                               * *(__int16 *)(g_MapData + v205 + 852)]];
    v23 = *(_WORD *)(v22 + 1534);
    *(_WORD *)(v22 + 1534) = -1;
    v168 = v23;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v172] + v21) -= 800;
    v24 = UnitBattle_EstimateDamageScoreAgainstUnit(a1, v178);
    v26 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + v21) - 15 * (_DWORD)v24;
    v27 = v205 + g_MapData;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + v21) = v26;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + v21) = v26 - 2 * *(unsigned __int8 *)(v27 + 860);
    v28 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(v178, a2, a3);
    v30 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + v21) - 2 * v28;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + v21) = v30;
    Debug_Log(v29, v21, v30, (int)aOddzial_w_zasi);
    v31 = v179 + g_MapData + 852;
    a3 = v32;
    if ( UnitBattle_IsTileWithinRange(a1, v33, v32)
      && (*(_BYTE *)(v179 + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(v179 + g_MapData + 864)) >> 5) > 0 )
    {
      v34 = 0;
LABEL_35:
      LOBYTE(v34) = *(_BYTE *)(v31 + 8);
      goto LABEL_36;
    }
    v83 = v170;
    if ( *(char *)(g_MapData + 20 * v170 + a3 + 3134) <= 0 )
    {
      v85 = a3;
    }
    else
    {
      v83 = g_MapData + 40 * v170;
      if ( *(__int16 *)(v83 + 2 * a3 + 1534) == -1
        || (v84 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v84 + 852)] & 1) == 0)
        && (*(_BYTE *)(v84 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v84 + 864)) >> 5) <= 0 )
      {
        v86 = UnitBattle_MoveTrackNearWall(a1, v170, a3, a3);
        goto LABEL_83;
      }
      v85 = a3;
    }
    v86 = (int *)UnitBattle_MoveTrackNear(a1, v83, v85, a3);
LABEL_83:
    v87 = v86;
    if ( !v86 )
    {
      v88 = 31 * a1 + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v88 + 852)] )
      {
        if ( (*(_BYTE *)(v88 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v88 + 864)) >> 5) > 0 )
          v87 = UnitBattle_MoveTrackForce(a1, a3, a3);
      }
    }
    if ( !v87 )
    {
LABEL_88:
      g_UnitBattleTileScoreGrid[40 * v170 + 2 * v172 + v194] += 700;
      goto LABEL_38;
    }
    if ( !*v87 )
    {
      j__nfree_();
      goto LABEL_35;
    }
    v89 = g_MapData + 31 * a1;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v89 + 852)]
      && (*(_BYTE *)(v89 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v89 + 864)) >> 5) > 0 )
    {
      v182 = *(_WORD *)(v31 + 4);
      HIWORD(v181) = 0;
      v183 = *(_WORD *)(v31 + 6);
      if ( *v87 )
      {
        while ( !UnitBattle_IsTileWithinRange(a1, v170, a3) )
        {
          v93 = *v91 - 1;
          *v91 = v93;
          v181 = v91[v93 + 1];
          if ( HIWORD(v181) > (int)*(unsigned __int8 *)(v31 + 8) )
            goto LABEL_111;
          *(_WORD *)(v31 + 4) = (unsigned __int8)v181;
          *(_WORD *)(v31 + 6) = BYTE1(v181);
          if ( !*v91 )
            goto LABEL_108;
        }
        *(_WORD *)(v31 + 4) = v182;
        *(_WORD *)(v31 + 6) = v183;
        j__nfree_();
        LOBYTE(v92) = *(_BYTE *)(v31 + 8);
        if ( v92 <= HIWORD(v181) )
          goto LABEL_105;
        v34 = v92 - HIWORD(v181);
      }
      else
      {
LABEL_108:
        if ( !UnitBattle_IsTileWithinRange(a1, v170, a3) )
        {
LABEL_111:
          *(_WORD *)(v31 + 4) = v182;
          *(_WORD *)(v31 + 6) = v183;
          j__nfree_();
          goto LABEL_37;
        }
        *(_WORD *)(v31 + 4) = v182;
        *(_WORD *)(v31 + 6) = v183;
        if ( *(unsigned __int8 *)(v31 + 8) <= (int)HIWORD(v181) )
        {
LABEL_104:
          j__nfree_();
LABEL_105:
          v34 = 0;
          goto LABEL_37;
        }
        j__nfree_();
        v34 = *(unsigned __int8 *)(v31 + 8) - v94;
      }
    }
    else
    {
      if ( !*v87 )
        goto LABEL_104;
      v180 = v87[1];
      j__nfree_();
      LOBYTE(v90) = *(_BYTE *)(v31 + 8);
      if ( v90 <= HIWORD(v180) )
      {
        v34 = 0;
        goto LABEL_37;
      }
      v34 = v90 - HIWORD(v180);
    }
LABEL_36:
    if ( v34 <= -1 )
      goto LABEL_88;
LABEL_37:
    g_UnitBattleTileScoreGrid[40 * v170 + 2 * v172 + v194] -= 5 * (v34 / 5);
LABEL_38:
    *(_WORD *)(g_MapData + 40 * v170 + 2 * v172 + 1534) = v168;
LABEL_39:
    v205 += 31;
    if ( (int)++v178 >= 22 )
    {
      v35 = g_UnitBattleWallScanTileRow;
      if ( g_UnitBattleWallScanTileRow <= 0 || *(unsigned __int16 *)(g_MapData + 31 * a1 + 856) == g_UnitBattleWallScanTileRow )
        return v167;
      v36 = g_BattleWallScanColumn;
      if ( *(char *)(g_BattleWallScanColumn + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
        goto LABEL_49;
      Debug_Log(31 * a1, g_BattleWallScanColumn, g_UnitBattleWallScanTileRow, (int)aOddzial_w_zasi);
      v38 = v37 + g_MapData + 852;
      v39 = v36;
      if ( UnitBattle_IsTileWithinRange(a1, v35, v36)
        && (*(_BYTE *)(v40 + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(v40 + g_MapData + 864)) >> 5) > 0 )
      {
        v41 = 0;
        goto LABEL_46;
      }
      if ( *(char *)(v36 + g_MapData + 20 * v35 + 3134) <= 0
        || *(__int16 *)(g_MapData + 40 * v35 + 2 * v36 + 1534) != -1
        && ((v95 = g_MapData + 31 * a1, (g_UnitTypeFlags[22 * *(__int16 *)(v95 + 852)] & 1) != 0)
         || (*(_BYTE *)(v95 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v95 + 864)) >> 5) > 0) )
      {
        v96 = (int *)UnitBattle_MoveTrackNear(a1, g_MapData, v36, v35);
      }
      else
      {
        v96 = UnitBattle_MoveTrackNearWall(a1, v35, v36, v35);
      }
      v97 = v96;
      if ( !v96 )
      {
        LOBYTE(v36) = g_MapData;
        v98 = g_MapData + 31 * a1;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v98 + 852)] )
        {
          v36 = *(_BYTE *)(v98 + 864) & 3;
          if ( v36 + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v98 + 864)) >> 5) > 0 )
          {
            LOBYTE(v36) = v39;
            v97 = UnitBattle_MoveTrackForce(a1, v39, v35);
          }
        }
      }
      if ( !v97 )
      {
LABEL_49:
        g_BattleWallScanTileX = g_BattleWallScanColumn + 1;
        if ( *(char *)(g_BattleWallScanColumn + 1 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
          goto LABEL_56;
        v48 = g_UnitBattleWallScanTileRow;
        Debug_Log(g_MapData, v36, v35, (int)aOddzial_w_zasi);
        v35 = v49;
        v50 = 31 * a1 + g_MapData + 852;
        if ( UnitBattle_IsTileWithinRange(a1, v48, v49) )
        {
          LOBYTE(v36) = 31 * a1;
          if ( (*(_BYTE *)(31 * a1 + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(31 * a1 + g_MapData + 864)) >> 5) > 0 )
          {
            v51 = 0;
            goto LABEL_53;
          }
        }
        v105 = g_MapData;
        if ( *(char *)(g_MapData + 20 * v48 + v35 + 3134) <= 0
          || *(__int16 *)(g_MapData + 40 * v48 + 2 * v35 + 1534) != -1
          && ((v105 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v105 + 852)] & 1) != 0)
           || (*(_BYTE *)(v105 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v105 + 864)) >> 5) > 0) )
        {
          LOBYTE(v36) = v35;
          v106 = (int *)UnitBattle_MoveTrackNear(a1, v105, v35, v35);
        }
        else
        {
          LOBYTE(v36) = v35;
          v106 = UnitBattle_MoveTrackNearWall(a1, v48, v35, v35);
        }
        v107 = v106;
        if ( !v106 )
        {
          v36 = 31 * a1 + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
          {
            if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
            {
              LOBYTE(v36) = v35;
              v107 = UnitBattle_MoveTrackForce(a1, v35, v35);
            }
          }
        }
        if ( !v107 )
        {
LABEL_56:
          g_BattleWallScanTileX = g_BattleWallScanColumn - 1;
          if ( *(char *)(g_BattleWallScanColumn - 1 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
            goto LABEL_63;
          v55 = g_UnitBattleWallScanTileRow;
          Debug_Log(g_MapData, v36, v35, (int)aOddzial_w_zasi);
          v35 = v56;
          v57 = 31 * a1 + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(a1, v55, v56) )
          {
            LOBYTE(v36) = 31 * a1;
            if ( (*(_BYTE *)(31 * a1 + g_MapData + 864) & 3)
               + 1
               - ((unsigned __int8)(2 * *(_BYTE *)(31 * a1 + g_MapData + 864)) >> 5) > 0 )
            {
              v58 = 0;
              goto LABEL_60;
            }
          }
          v113 = g_MapData;
          if ( *(char *)(g_MapData + 20 * v55 + v35 + 3134) <= 0
            || *(__int16 *)(g_MapData + 40 * v55 + 2 * v35 + 1534) != -1
            && ((v113 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v113 + 852)] & 1) != 0)
             || (*(_BYTE *)(v113 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v113 + 864)) >> 5) > 0) )
          {
            LOBYTE(v36) = v35;
            v114 = (int *)UnitBattle_MoveTrackNear(a1, v113, v35, v35);
          }
          else
          {
            LOBYTE(v36) = v35;
            v114 = UnitBattle_MoveTrackNearWall(a1, v55, v35, v35);
          }
          v115 = v114;
          if ( !v114 )
          {
            v36 = 31 * a1 + g_MapData;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
            {
              if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
              {
                LOBYTE(v36) = v35;
                v115 = UnitBattle_MoveTrackForce(a1, v35, v35);
              }
            }
          }
          if ( !v115 )
          {
LABEL_63:
            g_BattleWallScanTileX = g_BattleWallScanColumn + 2;
            if ( *(char *)(g_BattleWallScanColumn + 2 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
              goto LABEL_70;
            v35 = g_UnitBattleWallScanTileRow;
            v62 = g_BattleWallScanColumn + 2;
            v36 = g_BattleWallScanColumn + 2;
            Debug_Log(a1, g_BattleWallScanColumn + 2, g_UnitBattleWallScanTileRow, (int)aOddzial_w_zasi);
            v63 = g_MapData + 852;
            v64 = UnitBattle_IsTileWithinRange(a1, v35, v36);
            v66 = v65 + v63;
            if ( v64
              && (*(_BYTE *)(v65 + g_MapData + 864) & 3)
               + 1
               - ((unsigned __int8)(2 * *(_BYTE *)(v65 + g_MapData + 864)) >> 5) > 0 )
            {
              v67 = 0;
              goto LABEL_67;
            }
            if ( *(char *)(v62 + g_MapData + 20 * v35 + 3134) <= 0
              || *(__int16 *)(g_MapData + 40 * v35 + 2 * v62 + 1534) != -1
              && ((v65 = a1, v121 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v121 + 852)] & 1) != 0)
               || (*(_BYTE *)(v121 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v121 + 864)) >> 5) > 0) )
            {
              LOBYTE(v36) = v62;
              v122 = (int *)UnitBattle_MoveTrackNear(a1, v65, v62, v35);
            }
            else
            {
              LOBYTE(v36) = v62;
              v122 = UnitBattle_MoveTrackNearWall(a1, v35, v62, v35);
            }
            v123 = v122;
            if ( !v122 )
            {
              LOBYTE(v36) = g_MapData;
              v124 = g_MapData + 31 * a1;
              if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v124 + 852)] )
              {
                if ( (*(_BYTE *)(v124 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v124 + 864)) >> 5) > 0 )
                {
                  LOBYTE(v36) = v62;
                  v123 = UnitBattle_MoveTrackForce(a1, v62, v35);
                }
              }
            }
            if ( !v123 )
            {
LABEL_70:
              g_BattleWallScanTileX = g_BattleWallScanColumn - 2;
              v71 = g_BattleWallScanColumn - 2;
              v72 = g_BattleWallScanColumn - 2 + 20 * g_UnitBattleWallScanTileRow + g_MapData;
              if ( *(char *)(v72 + 3134) <= 0 )
                return v167;
              Debug_Log(v72, v36, v35, (int)aOddzial_w_zasi);
              v74 = v73;
              v75 = v71;
              v76 = v71;
              v77 = 31 * a1 + g_MapData + 852;
              if ( UnitBattle_IsTileWithinRange(a1, v73, v76)
                && (*(_BYTE *)(31 * a1 + g_MapData + 864) & 3)
                 + 1
                 - ((unsigned __int8)(2 * *(_BYTE *)(31 * a1 + g_MapData + 864)) >> 5) > 0 )
              {
                v78 = 0;
                goto LABEL_74;
              }
              v130 = g_MapData;
              if ( *(char *)(v75 + g_MapData + 20 * v74 + 3134) <= 0
                || *(__int16 *)(g_MapData + 40 * v74 + 2 * v75 + 1534) != -1
                && ((v130 = 31 * a1 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v130 + 852)] & 1) != 0)
                 || (*(_BYTE *)(v130 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v130 + 864)) >> 5) > 0) )
              {
                v131 = (int *)UnitBattle_MoveTrackNear(a1, v130, v75, v74);
              }
              else
              {
                v131 = UnitBattle_MoveTrackNearWall(a1, v74, v75, v74);
              }
              v132 = v131;
              if ( !v131 )
              {
                v133 = 31 * a1 + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v133 + 852)] )
                {
                  if ( (*(_BYTE *)(v133 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v133 + 864)) >> 5) > 0 )
                    v132 = UnitBattle_MoveTrackForce(a1, v75, v74);
                }
              }
              if ( !v132 )
                return v167;
              if ( *v132 )
              {
                v134 = 31 * a1 + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v134 + 852)]
                  && (*(_BYTE *)(v134 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v134 + 864)) >> 5) > 0 )
                {
                  v192 = *(_WORD *)(v77 + 4);
                  v195 = *(_WORD *)(v77 + 6);
                  HIWORD(v210) = 0;
                  if ( *v132 )
                  {
                    while ( !UnitBattle_IsTileWithinRange(a1, v74, v75) )
                    {
                      v138 = *v136 - 1;
                      *v136 = v138;
                      v210 = v136[v138 + 1];
                      if ( HIWORD(v210) > (int)*(unsigned __int8 *)(v77 + 8) )
                        goto LABEL_271;
                      *(_WORD *)(v77 + 4) = (unsigned __int8)v210;
                      *(_WORD *)(v77 + 6) = BYTE1(v210);
                      if ( !*v136 )
                        goto LABEL_268;
                    }
                    *(_WORD *)(v77 + 4) = v192;
                    *(_WORD *)(v77 + 6) = v195;
                    j__nfree_();
                    LOBYTE(v137) = *(_BYTE *)(v77 + 8);
                    if ( v137 > HIWORD(v210) )
                    {
                      v78 = v137 - HIWORD(v210);
                      goto LABEL_75;
                    }
LABEL_265:
                    v78 = 0;
LABEL_76:
                    v79 = 8 * g_BattleWallScanTileX + 3204 * a1 + 160 * g_UnitBattleWallScanTileRow;
                    v80 = *(int *)((char *)g_UnitBattleTileScoreGrid + v79) - 640 - 5 * (v78 / 5);
                    v81 = g_BattleWallScanTileX;
                    v82 = g_MapData + 20 * g_UnitBattleWallScanTileRow;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) -= 640;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = v80;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = *(char *)(v81 + v82 + 3134) + v80;
                    return v167;
                  }
LABEL_268:
                  if ( !UnitBattle_IsTileWithinRange(a1, v74, v75) )
                  {
LABEL_271:
                    *(_WORD *)(v77 + 4) = v192;
                    *(_WORD *)(v77 + 6) = v195;
                    j__nfree_();
                    goto LABEL_76;
                  }
                  *(_WORD *)(v77 + 4) = v192;
                  *(_WORD *)(v77 + 6) = v195;
                  if ( *(unsigned __int8 *)(v77 + 8) > (int)HIWORD(v210) )
                  {
                    j__nfree_();
                    LOBYTE(v139) = *(_BYTE *)(v77 + 8);
                    v78 = v139 - HIWORD(v210);
                    goto LABEL_75;
                  }
                }
                else if ( *v132 )
                {
                  v209 = v132[1];
                  j__nfree_();
                  LOBYTE(v135) = *(_BYTE *)(v77 + 8);
                  if ( v135 > HIWORD(v209) )
                  {
                    v78 = v135 - HIWORD(v209);
                    goto LABEL_75;
                  }
                  v78 = 0;
                  goto LABEL_76;
                }
                j__nfree_();
                goto LABEL_265;
              }
              j__nfree_();
LABEL_74:
              LOBYTE(v78) = *(_BYTE *)(v77 + 8);
LABEL_75:
              if ( v78 > -1 )
                goto LABEL_76;
              return v167;
            }
            if ( !*v123 )
            {
              j__nfree_();
LABEL_67:
              LOBYTE(v67) = *(_BYTE *)(v66 + 8);
              goto LABEL_68;
            }
            v36 = 31 * a1 + g_MapData;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)]
              && (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
            {
              v196 = *(_WORD *)(v66 + 4);
              v189 = *(_WORD *)(v66 + 6);
              HIWORD(v200) = 0;
              if ( *v123 )
              {
                while ( 1 )
                {
                  LOBYTE(v36) = v62;
                  if ( UnitBattle_IsTileWithinRange(a1, v35, v62) )
                    break;
                  v128 = *v126 - 1;
                  *v126 = v128;
                  v200 = v126[v128 + 1];
                  if ( HIWORD(v200) > (int)*(unsigned __int8 *)(v66 + 8) )
                    goto LABEL_239;
                  *(_WORD *)(v66 + 4) = (unsigned __int8)v200;
                  *(_WORD *)(v66 + 6) = BYTE1(v200);
                  if ( !*v126 )
                    goto LABEL_236;
                }
                *(_WORD *)(v66 + 4) = v196;
                *(_WORD *)(v66 + 6) = v189;
                j__nfree_();
                LOBYTE(v127) = *(_BYTE *)(v66 + 8);
                if ( v127 > HIWORD(v200) )
                {
                  v67 = v127 - HIWORD(v200);
                  goto LABEL_68;
                }
LABEL_233:
                v67 = 0;
LABEL_69:
                v68 = 3204 * a1 + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
                v35 = *(int *)((char *)g_UnitBattleTileScoreGrid + v68) - 640 - 5 * (v67 / 5);
                v69 = g_BattleWallScanTileX;
                v70 = g_MapData + 20 * g_UnitBattleWallScanTileRow;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) -= 640;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) = v35;
                v36 = *(char *)(v69 + v70 + 3134) + v35;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) = v36;
                goto LABEL_70;
              }
LABEL_236:
              if ( !UnitBattle_IsTileWithinRange(a1, v35, v62) )
              {
LABEL_239:
                *(_WORD *)(v66 + 4) = v196;
                *(_WORD *)(v66 + 6) = v189;
                j__nfree_();
                goto LABEL_69;
              }
              *(_WORD *)(v66 + 4) = v196;
              *(_WORD *)(v66 + 6) = v189;
              v36 = HIWORD(v200);
              if ( *(unsigned __int8 *)(v66 + 8) > (int)HIWORD(v200) )
              {
                j__nfree_();
                LOBYTE(v129) = *(_BYTE *)(v66 + 8);
                v67 = v129 - HIWORD(v200);
                goto LABEL_68;
              }
            }
            else if ( *v123 )
            {
              v199 = v123[1];
              j__nfree_();
              LOBYTE(v125) = *(_BYTE *)(v66 + 8);
              if ( v125 <= HIWORD(v199) )
              {
                v67 = 0;
              }
              else
              {
                v67 = v125 - HIWORD(v199);
LABEL_68:
                if ( v67 <= -1 )
                  goto LABEL_70;
              }
              goto LABEL_69;
            }
            j__nfree_();
            goto LABEL_233;
          }
          if ( !*v115 )
          {
            j__nfree_();
LABEL_60:
            LOBYTE(v58) = *(_BYTE *)(v57 + 8);
            goto LABEL_61;
          }
          v36 = 31 * a1 + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)]
            && (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
          {
            v193 = *(_WORD *)(v57 + 4);
            HIWORD(v202) = 0;
            v191 = *(_WORD *)(v57 + 6);
            if ( *v115 )
            {
              while ( 1 )
              {
                LOBYTE(v36) = v35;
                if ( UnitBattle_IsTileWithinRange(a1, v55, v35) )
                  break;
                v119 = *v117 - 1;
                *v117 = v119;
                v202 = v117[v119 + 1];
                if ( HIWORD(v202) > (int)*(unsigned __int8 *)(v57 + 8) )
                  goto LABEL_207;
                *(_WORD *)(v57 + 4) = (unsigned __int8)v202;
                *(_WORD *)(v57 + 6) = BYTE1(v202);
                if ( !*v117 )
                  goto LABEL_204;
              }
              *(_WORD *)(v57 + 4) = v193;
              *(_WORD *)(v57 + 6) = v191;
              j__nfree_();
              LOBYTE(v118) = *(_BYTE *)(v57 + 8);
              if ( v118 > HIWORD(v202) )
              {
                v58 = v118 - HIWORD(v202);
                goto LABEL_61;
              }
LABEL_201:
              v58 = 0;
LABEL_62:
              v59 = 160 * g_UnitBattleWallScanTileRow + 3204 * a1 + 8 * g_BattleWallScanTileX;
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) -= 640;
              v60 = *(int *)((char *)g_UnitBattleTileScoreGrid + v59) - 5 * (v58 / 5);
              LOBYTE(v36) = g_MapData;
              v61 = g_BattleWallScanTileX + g_MapData + 20 * g_UnitBattleWallScanTileRow;
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) = v60;
              v35 = v60 + *(char *)(v61 + 3134);
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) = v35;
              goto LABEL_63;
            }
LABEL_204:
            if ( !UnitBattle_IsTileWithinRange(a1, v55, v35) )
            {
LABEL_207:
              *(_WORD *)(v57 + 4) = v193;
              *(_WORD *)(v57 + 6) = v191;
              j__nfree_();
              goto LABEL_62;
            }
            *(_WORD *)(v57 + 4) = v193;
            *(_WORD *)(v57 + 6) = v191;
            v36 = HIWORD(v202);
            if ( *(unsigned __int8 *)(v57 + 8) > (int)HIWORD(v202) )
            {
              j__nfree_();
              LOBYTE(v120) = *(_BYTE *)(v57 + 8);
              v58 = v120 - HIWORD(v202);
              goto LABEL_61;
            }
          }
          else if ( *v115 )
          {
            v201 = v115[1];
            j__nfree_();
            LOBYTE(v116) = *(_BYTE *)(v57 + 8);
            if ( v116 <= HIWORD(v201) )
            {
              v58 = 0;
            }
            else
            {
              v58 = v116 - HIWORD(v201);
LABEL_61:
              if ( v58 <= -1 )
                goto LABEL_63;
            }
            goto LABEL_62;
          }
          j__nfree_();
          goto LABEL_201;
        }
        if ( !*v107 )
        {
          j__nfree_();
LABEL_53:
          LOBYTE(v51) = *(_BYTE *)(v50 + 8);
          goto LABEL_54;
        }
        v36 = 31 * a1 + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)]
          && (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
        {
          v188 = *(_WORD *)(v50 + 4);
          HIWORD(v207) = 0;
          v187 = *(_WORD *)(v50 + 6);
          if ( *v107 )
          {
            while ( 1 )
            {
              LOBYTE(v36) = v35;
              if ( UnitBattle_IsTileWithinRange(a1, v48, v35) )
                break;
              v111 = *v109 - 1;
              *v109 = v111;
              v207 = v109[v111 + 1];
              if ( HIWORD(v207) > (int)*(unsigned __int8 *)(v50 + 8) )
                goto LABEL_175;
              *(_WORD *)(v50 + 4) = (unsigned __int8)v207;
              *(_WORD *)(v50 + 6) = BYTE1(v207);
              if ( !*v109 )
                goto LABEL_172;
            }
            *(_WORD *)(v50 + 4) = v188;
            *(_WORD *)(v50 + 6) = v187;
            j__nfree_();
            LOBYTE(v110) = *(_BYTE *)(v50 + 8);
            if ( v110 > HIWORD(v207) )
            {
              v51 = v110 - HIWORD(v207);
              goto LABEL_54;
            }
LABEL_169:
            v51 = 0;
LABEL_55:
            v52 = 3204 * a1 + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) -= 640;
            v53 = *(int *)((char *)g_UnitBattleTileScoreGrid + v52) - 5 * (v51 / 5);
            LOBYTE(v36) = g_MapData;
            v54 = g_BattleWallScanTileX + g_MapData + 20 * g_UnitBattleWallScanTileRow;
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) = v53;
            v35 = v53 + *(char *)(v54 + 3134);
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) = v35;
            goto LABEL_56;
          }
LABEL_172:
          if ( !UnitBattle_IsTileWithinRange(a1, v48, v35) )
          {
LABEL_175:
            *(_WORD *)(v50 + 4) = v188;
            *(_WORD *)(v50 + 6) = v187;
            j__nfree_();
            goto LABEL_55;
          }
          *(_WORD *)(v50 + 4) = v188;
          *(_WORD *)(v50 + 6) = v187;
          v36 = HIWORD(v207);
          if ( *(unsigned __int8 *)(v50 + 8) > (int)HIWORD(v207) )
          {
            j__nfree_();
            LOBYTE(v112) = *(_BYTE *)(v50 + 8);
            v51 = v112 - HIWORD(v207);
            goto LABEL_54;
          }
        }
        else if ( *v107 )
        {
          v206 = v107[1];
          j__nfree_();
          LOBYTE(v108) = *(_BYTE *)(v50 + 8);
          if ( v108 <= HIWORD(v206) )
          {
            v51 = 0;
          }
          else
          {
            v51 = v108 - HIWORD(v206);
LABEL_54:
            if ( v51 <= -1 )
              goto LABEL_56;
          }
          goto LABEL_55;
        }
        j__nfree_();
        goto LABEL_169;
      }
      if ( !*v97 )
      {
        j__nfree_();
LABEL_46:
        LOBYTE(v41) = *(_BYTE *)(v38 + 8);
        goto LABEL_47;
      }
      LOBYTE(v36) = g_MapData;
      v99 = g_MapData + 31 * a1;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v99 + 852)]
        && (*(_BYTE *)(v99 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v99 + 864)) >> 5) > 0 )
      {
        v197 = *(_WORD *)(v38 + 4);
        v190 = *(_WORD *)(v38 + 6);
        HIWORD(v204) = 0;
        if ( *v97 )
        {
          while ( 1 )
          {
            LOBYTE(v36) = v39;
            if ( UnitBattle_IsTileWithinRange(a1, v35, v39) )
              break;
            v103 = *v101 - 1;
            *v101 = v103;
            v204 = v101[v103 + 1];
            if ( HIWORD(v204) > (int)*(unsigned __int8 *)(v38 + 8) )
              goto LABEL_143;
            *(_WORD *)(v38 + 4) = (unsigned __int8)v204;
            *(_WORD *)(v38 + 6) = BYTE1(v204);
            if ( !*v101 )
              goto LABEL_140;
          }
          *(_WORD *)(v38 + 4) = v197;
          *(_WORD *)(v38 + 6) = v190;
          j__nfree_();
          LOBYTE(v102) = *(_BYTE *)(v38 + 8);
          if ( v102 > HIWORD(v204) )
          {
            v41 = v102 - HIWORD(v204);
            goto LABEL_47;
          }
LABEL_137:
          v41 = 0;
LABEL_48:
          v42 = 3204 * a1 + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanColumn;
          v43 = v41;
          v44 = g_UnitBattleWallScanTileRow;
          v36 = *(int *)((char *)g_UnitBattleTileScoreGrid + v42) - 5 * (v43 / 5);
          v45 = 4 * g_UnitBattleWallScanTileRow;
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v36;
          v46 = v36 - 650;
          LOBYTE(v36) = g_MapData;
          v47 = g_BattleWallScanColumn + g_MapData + 4 * (v44 + v45);
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v46;
          v35 = v46 + *(char *)(v47 + 3134);
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v35;
          goto LABEL_49;
        }
LABEL_140:
        if ( !UnitBattle_IsTileWithinRange(a1, v35, v39) )
        {
LABEL_143:
          *(_WORD *)(v38 + 4) = v197;
          *(_WORD *)(v38 + 6) = v190;
          j__nfree_();
          goto LABEL_48;
        }
        *(_WORD *)(v38 + 4) = v197;
        *(_WORD *)(v38 + 6) = v190;
        v36 = HIWORD(v204);
        if ( *(unsigned __int8 *)(v38 + 8) > (int)HIWORD(v204) )
        {
          j__nfree_();
          LOBYTE(v104) = *(_BYTE *)(v38 + 8);
          v41 = v104 - HIWORD(v204);
          goto LABEL_47;
        }
      }
      else if ( *v97 )
      {
        v203 = v97[1];
        j__nfree_();
        LOBYTE(v100) = *(_BYTE *)(v38 + 8);
        if ( v100 <= HIWORD(v203) )
        {
          v41 = 0;
        }
        else
        {
          v41 = v100 - HIWORD(v203);
LABEL_47:
          if ( v41 <= -1 )
            goto LABEL_49;
        }
        goto LABEL_48;
      }
      j__nfree_();
      goto LABEL_137;
    }
  }
}
// 438681: conditional instruction was optimized away because eax.4!=0
// 4383B1: variable 'v5' is possibly undefined
// 438441: variable 'v8' is possibly undefined
// 4384C7: variable 'v9' is possibly undefined
// 43855E: variable 'v12' is possibly undefined
// 4386A5: variable 'v14' is possibly undefined
// 438702: variable 'i' is possibly undefined
// 43882E: variable 'v25' is possibly undefined
// 438874: variable 'v29' is possibly undefined
// 4388BD: variable 'v32' is possibly undefined
// 4388BF: variable 'v33' is possibly undefined
// 438909: variable 'v34' is possibly undefined
// 438A03: variable 'v37' is possibly undefined
// 438A1E: variable 'v40' is possibly undefined
// 438A53: variable 'v41' is possibly undefined
// 438B49: variable 'v49' is possibly undefined
// 438BBB: variable 'v51' is possibly undefined
// 438CB7: variable 'v56' is possibly undefined
// 438D2A: variable 'v58' is possibly undefined
// 438E4C: variable 'v65' is possibly undefined
// 438E8F: variable 'v67' is possibly undefined
// 438F86: variable 'v73' is possibly undefined
// 438FFB: variable 'v78' is possibly undefined
// 439234: variable 'v90' is possibly undefined
// 4392D3: variable 'v92' is possibly undefined
// 4392F1: variable 'v91' is possibly undefined
// 43936D: variable 'v94' is possibly undefined
// 439514: variable 'v100' is possibly undefined
// 4395BC: variable 'v102' is possibly undefined
// 4395DA: variable 'v101' is possibly undefined
// 439665: variable 'v104' is possibly undefined
// 43980A: variable 'v108' is possibly undefined
// 4398A9: variable 'v110' is possibly undefined
// 4398C7: variable 'v109' is possibly undefined
// 43994F: variable 'v112' is possibly undefined
// 439AF1: variable 'v116' is possibly undefined
// 439B9C: variable 'v118' is possibly undefined
// 439BBA: variable 'v117' is possibly undefined
// 439C48: variable 'v120' is possibly undefined
// 439DF6: variable 'v125' is possibly undefined
// 439E9A: variable 'v127' is possibly undefined
// 439EB8: variable 'v126' is possibly undefined
// 439F45: variable 'v129' is possibly undefined
// 43A105: variable 'v135' is possibly undefined
// 43A1B3: variable 'v137' is possibly undefined
// 43A1D1: variable 'v136' is possibly undefined
// 43A264: variable 'v139' is possibly undefined
// 43A3B0: variable 'v145' is possibly undefined
// 43A3F6: variable 'v149' is possibly undefined
// 43A43F: variable 'v151' is possibly undefined
// 43A43F: variable 'v152' is possibly undefined
// 43A489: variable 'v153' is possibly undefined
// 43A69E: variable 'v161' is possibly undefined
// 43A73B: variable 'v163' is possibly undefined
// 43A75B: variable 'v162' is possibly undefined
// 43A7D7: variable 'v166' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5159F0: using guessed type int dword_5159F0[8];
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;
// 53244C: using guessed type int dword_53244C[17621];
// 5437B0: using guessed type int dword_5437B0;
// 5437B4: using guessed type int dword_5437B4;
// 5437B8: using guessed type int dword_5437B8;

//----- (0043A800) --------------------------------------------------------
int  WCIsvListBase_TransferAllInto(int result, int a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( *(_DWORD *)(result + 8) )
  {
    WCIsvListBase_PopFrontValue(result, a2);
    WCIsvListBase_TransferAllInto(v3, a2);
    return WCIsvListBase_AppendValue(a2, v4);
  }
  return result;
}
// 43A823: variable 'v3' is possibly undefined
// 43A82C: variable 'v4' is possibly undefined

//----- (0043A880) --------------------------------------------------------
signed int __fastcall WCIsvListBase_PopUntilMatchOrEmpty(int a1, int a2)
{
  int v3; // eax
  int v4; // ecx

  if ( !*(_DWORD *)(a2 + 8) )
    return 0;
  while ( 1 )
  {
    v3 = WCIsvListBase_PopFrontValue(a2, a2);
    if ( v3 == v4 )
      break;
    if ( !*(_DWORD *)(a2 + 8) )
      return 0;
  }
  return 1;
}
// 43A898: variable 'v4' is possibly undefined

//----- (0043A8B0) --------------------------------------------------------
signed int  UnitBattle_SelectAiActionForUnit(int a1, int a2)
{
  int v2; // eax
  int v3; // ebx
  int v4; // esi
  int v5; // eax
  int v6; // edx
  int v8; // ecx
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  int v12; // ebp
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int *v18; // edi
  DWORD v19; // ebp
  int v20; // edx
  int i; // eax
  int v22; // ecx
  int v23; // esi
  int v24; // ecx
  int j; // eax
  int v26; // eax
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // ebx
  int *v31; // eax
  int *v32; // esi
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // edx
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // eax
  int *v42; // ecx
  int v43; // eax
  int v44; // esi
  int v45; // edi
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // ecx
  WCIsvListBase *v50; // ecx
  bool v51; // bl
  int v52; // ecx
  int v53[66]; // [esp+0h] [ebp-164h]
  int v54; // [esp+108h] [ebp-5Ch] BYREF
  void **v55; // [esp+10Ch] [ebp-58h]
  int v56; // [esp+110h] [ebp-54h]
  int v57; // [esp+114h] [ebp-50h]
  int v58; // [esp+118h] [ebp-4Ch]
  int v59; // [esp+11Ch] [ebp-48h]
  int v60; // [esp+120h] [ebp-44h]
  int v61; // [esp+124h] [ebp-40h]
  int v62; // [esp+128h] [ebp-3Ch]
  int v63; // [esp+12Ch] [ebp-38h]
  int v64; // [esp+130h] [ebp-34h]
  int v65; // [esp+134h] [ebp-30h]
  int v66; // [esp+138h] [ebp-2Ch]
  int v67; // [esp+13Ch] [ebp-28h]
  int v68; // [esp+140h] [ebp-24h]
  int v69; // [esp+144h] [ebp-20h]
  int v70; // [esp+148h] [ebp-1Ch]
  int v71; // [esp+14Ch] [ebp-18h]

  v68 = a1;
  v63 = a2;
  g_BattleTargetTileCol = -1;
  g_UnitBattleScanTileRow = -1;
  v2 = g_MapData + 31 * a1;
  v3 = 0;
  if ( g_UnitTypeRole[88 * *(__int16 *)(v2 + 852)] == 4
    && (*(_BYTE *)(v2 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v2 + 864)) >> 5) <= 0 )
  {
    g_BattleCellStateGrid[801 * v68 - 42] = 5;
    return 1;
  }
  v4 = 0;
  v61 = 0;
  while ( v4 < *(_DWORD *)(g_MapData + 804) )
  {
    v5 = 0;
    v6 = 0;
    while ( v5 < *(_DWORD *)(g_MapData + 800) )
    {
      v8 = v6 + v61 + 3204 * v68;
      if ( v3 > *(int *)((char *)g_UnitBattleTileScoreGrid + v8) )
      {
        g_UnitBattleScanTileRow = v4;
        g_BattleTargetTileCol = v5;
        v3 = *(int *)((char *)g_UnitBattleTileScoreGrid + v8);
      }
      v6 += 8;
      ++v5;
    }
    ++v4;
    v61 += 160;
  }
  if ( g_UnitBattleAiCurrentPlanMode == 2 || g_UnitBattleAiCurrentPlanMode == 6 )
  {
    g_BattleCellStateGrid[801 * v68 + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 6;
    return 1;
  }
  v9 = 801 * v68;
  if ( v3 < 0 )
  {
    v11 = 31 * v68 + g_MapData;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v11 + 852)] )
    {
      if ( (*(_BYTE *)(v11 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v11 + 864)) >> 5) > 0 )
      {
        LOBYTE(v3) = g_BattleTargetTileCol;
        if ( UnitBattle_IsTileWithinRange(v68, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
        {
          if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
            && *(unsigned __int8 *)(g_MapData + 31 * v68 + 854) == *(_DWORD *)(g_MapData + 836)
            && *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534) == -1 )
          {
            g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + v9] = 8;
            return 1;
          }
          else
          {
            g_BattleCellStateGrid[801 * v68 + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 1;
            return 1;
          }
        }
      }
    }
    v12 = g_BattleTargetTileCol;
    v71 = v68;
    v67 = g_UnitBattleScanTileRow;
    Debug_Log(31 * v68, v3, g_BattleTargetTileCol, (int)aOddzial_w_zasi);
    v14 = g_MapData + 852 + v13;
    if ( UnitBattle_IsTileWithinRange(v68, v67, v12)
      && (*(_BYTE *)(g_MapData + v15 + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(g_MapData + v15 + 864)) >> 5) > 0 )
    {
      goto LABEL_24;
    }
    v27 = v67;
    if ( *(char *)(g_MapData + 20 * v67 + v12 + 3134) <= 0 )
    {
      v29 = v71;
      v30 = v12;
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * v67 + 2 * v12 + 1534) == -1
        || (v27 = v71, v28 = 31 * v71 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v28 + 852)] & 1) == 0)
        && (v27 = (*(_BYTE *)(v28 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v28 + 864)) >> 5), v27 <= 0) )
      {
        v31 = UnitBattle_MoveTrackNearWall(v71, v67, v12, v12);
LABEL_58:
        v32 = v31;
        if ( !v31 )
        {
          v33 = g_MapData + 31 * v71;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v33 + 852)] )
          {
            if ( (*(_BYTE *)(v33 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v33 + 864)) >> 5) > 0 )
              v32 = UnitBattle_MoveTrackForce(v71, v12, v12);
          }
        }
        if ( !v32 )
          goto LABEL_63;
        if ( *v32 )
        {
          v35 = g_MapData + 31 * v71;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v35 + 852)]
            && (*(_BYTE *)(v35 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v35 + 864)) >> 5) > 0 )
          {
            v62 = *(unsigned __int16 *)(v14 + 4);
            HIWORD(v70) = 0;
            v37 = *v32;
            v69 = *(unsigned __int16 *)(v14 + 6);
            if ( v37 )
            {
              while ( !UnitBattle_IsTileWithinRange(v71, v67, v12) )
              {
                v38 = *v32 - 1;
                *v32 = v38;
                v70 = v32[v38 + 1];
                if ( HIWORD(v70) > (int)*(unsigned __int8 *)(v14 + 8) )
                  goto LABEL_86;
                *(_WORD *)(v14 + 4) = (unsigned __int8)v70;
                *(_WORD *)(v14 + 6) = BYTE1(v70);
                if ( !*v32 )
                  goto LABEL_80;
              }
              *(_WORD *)(v14 + 4) = v62;
              *(_WORD *)(v14 + 6) = v69;
              j__nfree_();
              LOWORD(v40) = HIWORD(v70);
              v41 = *(unsigned __int8 *)(v14 + 8);
              if ( v41 <= v40 )
                goto LABEL_63;
              v16 = v41 - v40;
              goto LABEL_25;
            }
LABEL_80:
            if ( UnitBattle_IsTileWithinRange(v71, v67, v12) )
            {
              *(_WORD *)(v14 + 4) = v62;
              *(_WORD *)(v14 + 6) = v69;
              if ( *(unsigned __int8 *)(v14 + 8) > (int)HIWORD(v70) )
              {
                j__nfree_();
                v16 = *(unsigned __int8 *)(v14 + 8) - v39;
LABEL_25:
                if ( v16 >= 5 )
                {
                  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
                    && *(unsigned __int8 *)(g_MapData + 31 * v68 + 854) == *(_DWORD *)(g_MapData + 836)
                    && *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) == -1 )
                  {
                    v17 = 160 * g_UnitBattleScanTileRow + 3204 * v68;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + v17) = 8;
                  }
                  else
                  {
                    v17 = 160 * g_UnitBattleScanTileRow + 3204 * v68;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + v17) = 1;
                  }
                  goto LABEL_30;
                }
LABEL_63:
                v34 = g_MapData + 31 * v68;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v34 + 852)]
                  && (*(_BYTE *)(v34 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v34 + 864)) >> 5) <= 0 )
                {
                  g_BattleCellStateGrid[801 * v68 + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                  return 1;
                }
                v17 = 3204 * v68;
                g_BattleCellStateGrid[801 * v68 + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 7;
LABEL_30:
                v18 = (int *)UnitBattle_MoveTrackNear(v68, v17, g_BattleTargetTileCol, v12);
                if ( !v18 )
                  v18 = UnitBattle_MoveTrackForce(v68, g_BattleTargetTileCol, v12);
                if ( v18 && *v18 )
                {
                  v19 = v63;
                  v20 = 0;
                  for ( i = 0; i != 66; i += 3 )
                  {
                    v53[i] = -1;
                    v22 = g_MapData + v20;
                    if ( *(unsigned __int8 *)(g_MapData + v20 + 854) == v19 && *(__int16 *)(v22 + 852) != -1 )
                    {
                      v53[i] = *(__int16 *)(40 * *(unsigned __int16 *)(v22 + 856)
                                          + g_MapData
                                          + 2 * *(unsigned __int16 *)(v22 + 858)
                                          + 1534);
                      v53[i + 1] = *(unsigned __int16 *)(g_MapData + v20 + 856);
                      v53[i + 2] = *(unsigned __int16 *)(g_MapData + v20 + 858);
                      v23 = 40 * *(unsigned __int16 *)(g_MapData + v20 + 856);
                      v22 = v23 + g_MapData;
                      *(_WORD *)(v23 + g_MapData + 2 * *(unsigned __int16 *)(g_MapData + v20 + 858) + 1534) = -1;
                    }
                    v20 += 31;
                  }
                  v24 = UnitBattle_MoveTrackNear(v68, v22, g_BattleTargetTileCol, v19);
                  for ( j = 0; j != 66; j += 3 )
                  {
                    if ( v53[j] != -1 )
                      *(_WORD *)(40 * v53[j + 1] + g_MapData + 2 * v53[j + 2] + 1534) = v53[j];
                  }
                  v26 = g_BattleAiActionAttemptCount++;
                  if ( v26 > 20 )
                  {
                    g_BattleCellStateGrid[801 * v68 + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                    if ( v24 )
                      j__nfree_();
LABEL_123:
                    j__nfree_();
                    return 1;
                  }
                  v60 = v18[1];
                  if ( !v24 )
                    return 0;
                  v66 = *(_DWORD *)(v24 + 4);
                  j__nfree_();
                  if ( HIWORD(v66) < HIWORD(v60) )
                  {
                    v43 = g_MapData + 31 * v68;
                    v65 = *(unsigned __int16 *)(v43 + 856);
                    v64 = *(unsigned __int16 *)(v43 + 858);
                    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v43 + 852)]
                      && (*(_BYTE *)(v43 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v43 + 864)) >> 5) > 0
                      && UnitBattle_IsTileWithinRange(v68, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                    {
                      return 1;
                    }
                    v44 = 31 * v68;
                    while ( v42 && *v42 )
                    {
                      UnitBattle_UpdateIdleAnimatedUnits();
                      v45 = *v42 - 1;
                      *v42 = v45;
                      v66 = v42[v45 + 1];
                      v46 = v44 + g_MapData;
                      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v44 + g_MapData + 852)]
                        && (*(_BYTE *)(v46 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v46 + 864)) >> 5) > 0 )
                      {
                        *(_WORD *)(v46 + 856) = (unsigned __int8)v66;
                        *(_WORD *)(g_MapData + v44 + 858) = BYTE1(v66);
                        if ( *(__int16 *)(40 * (unsigned __int8)v66 + g_MapData + 2 * BYTE1(v66) + 1534) == -1
                          && UnitBattle_IsTileWithinRange(v68, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                        {
                          *(_WORD *)(v44 + g_MapData + 856) = v65;
                          *(_WORD *)(g_MapData + v44 + 858) = v64;
                          if ( !v42 )
                            return 1;
                          goto LABEL_123;
                        }
                        *(_WORD *)(v44 + g_MapData + 856) = v65;
                        *(_WORD *)(v44 + g_MapData + 858) = v64;
                      }
                      v47 = *(__int16 *)(g_MapData + 40 * (unsigned __int8)v66 + 2 * BYTE1(v66) + 1534);
                      if ( v47 != -1 )
                      {
                        v48 = *(unsigned __int8 *)(31 * v47 + g_MapData + 854);
                        if ( v48 == v63 )
                        {
                          v54 = 0;
                          v56 = v63 ^ v48;
                          v57 = 0;
                          v58 = 0;
                          v55 = &g_WCIsvListBaseVariant124_Vtable;
                          v59 = 0;
                          WCIsvListBase_CopyAppendAll(&v54, &g_UnitBattleAiCandidateQueue, (int)v42);
                          v55 = &g_WCIsvListBaseVariant134_Vtable;
                          v51 = WCIsvListBase_PopUntilMatchOrEmpty(v49, (int)&v54) && g_BattleAiActionAttemptCount < 20;
                          WCIsvListBase_DestroyElementsAndDtor(v50, (int)&v54);
                          if ( v51 )
                          {
                            if ( v52 )
                              j__nfree_();
                            return 0;
                          }
                          if ( !v52 )
                            return 1;
                        }
                        else if ( !v42 )
                        {
                          return 1;
                        }
                        goto LABEL_123;
                      }
                    }
                  }
                  if ( v42 )
                    goto LABEL_123;
                }
                else if ( v18 )
                {
                  j__nfree_();
                  return 1;
                }
                return 1;
              }
            }
            else
            {
LABEL_86:
              *(_WORD *)(v14 + 4) = v62;
              *(_WORD *)(v14 + 6) = v69;
            }
          }
          else if ( *v32 )
          {
            v70 = v32[1];
            j__nfree_();
            LOBYTE(v36) = *(_BYTE *)(v14 + 8);
            if ( v36 <= HIWORD(v70) )
              goto LABEL_63;
            v16 = v36 - HIWORD(v70);
            goto LABEL_25;
          }
          j__nfree_();
          goto LABEL_63;
        }
        j__nfree_();
LABEL_24:
        v16 = *(unsigned __int8 *)(v14 + 8);
        goto LABEL_25;
      }
      v29 = v71;
      v30 = v12;
    }
    v31 = (int *)UnitBattle_MoveTrackNear(v29, v27, v30, v12);
    goto LABEL_58;
  }
  v10 = g_BattleAiActionAttemptCount++;
  if ( v10 < 20 )
    return 0;
  g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + v9] = 5;
  return 1;
}
// 43ADF3: conditional instruction was optimized away because edi.4!=0
// 43B385: conditional instruction was optimized away because edi.4!=0
// 43B3AC: conditional instruction was optimized away because edi.4!=0
// 43AB26: variable 'v13' is possibly undefined
// 43AB44: variable 'v15' is possibly undefined
// 43B152: variable 'v36' is possibly undefined
// 43B272: variable 'v39' is possibly undefined
// 43B2B3: variable 'v40' is possibly undefined
// 43B452: variable 'v42' is possibly undefined
// 43B6D6: variable 'v49' is possibly undefined
// 43B6F6: variable 'v50' is possibly undefined
// 43B701: variable 'v52' is possibly undefined
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532448: using guessed type int dword_532448[];
// 53244C: using guessed type int dword_53244C[17621];
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;
// 5437A8: using guessed type int dword_5437A8;
// 5437C0: using guessed type int dword_5437C0;

//----- (0043B740) --------------------------------------------------------
int  UnitBattle_ApproachToSafeDistance(int a1, int a2, char a3, int a4)
{
  int v4; // edx
  int v5; // edx
  int v6; // ecx
  __int16 v7; // bx
  int v8; // eax
  int v9; // ecx
  int v10; // ebx
  int v12; // eax
  int *v13; // eax
  _DWORD *v14; // eax
  int v15; // edx
  int v16; // edi
  int v17; // esi
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int *v22; // eax
  int *v23; // ecx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int *v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int *v32; // eax
  int v34; // [esp+4h] [ebp-40h]
  int v35; // [esp+8h] [ebp-3Ch]
  int v36; // [esp+10h] [ebp-34h]
  int v37; // [esp+14h] [ebp-30h]
  __int16 v38; // [esp+18h] [ebp-2Ch]
  __int16 v39; // [esp+1Ch] [ebp-28h]
  int v40; // [esp+24h] [ebp-20h]
  int v41; // [esp+24h] [ebp-20h]
  unsigned __int8 v42; // [esp+28h] [ebp-1Ch]
  unsigned __int8 v43; // [esp+2Ch] [ebp-18h]

  Debug_Log(a2, a3, a4, (int)aPodejdz_na_bez);
  v5 = 31 * v4 + g_MapData + 852;
  v35 = *(unsigned __int8 *)(v5 + 8);
  v37 = v5;
  v6 = 40 * g_UnitBattleScanTileRow + g_MapData;
  if ( *(__int16 *)(v6 + 2 * g_BattleTargetTileCol + 1534) == -1 )
  {
    v7 = g_BattleTargetTileCol;
    v8 = UnitBattle_MoveTrackNear(a1, v6, g_BattleTargetTileCol, a4);
    *(_DWORD *)(v37 + 23) = v8;
    if ( !v8 )
    {
      v7 = g_BattleTargetTileCol;
      *(_DWORD *)(v37 + 23) = UnitBattle_MoveTrackForce(a1, g_BattleTargetTileCol, a4);
    }
    if ( *(_DWORD *)(v37 + 23) )
      UnitBattle_Move(a1, v9, v7, a4);
    v10 = *(_DWORD *)(v37 + 23);
    if ( v10 )
      goto LABEL_7;
    goto LABEL_8;
  }
  LOWORD(v10) = g_BattleTargetTileCol;
  v12 = UnitBattle_MoveTrackNear(a1, v6, g_BattleTargetTileCol, a4);
  *(_DWORD *)(v37 + 23) = v12;
  if ( !v12 )
  {
    LOWORD(v10) = g_BattleTargetTileCol;
    *(_DWORD *)(v37 + 23) = UnitBattle_MoveTrackForce(a1, g_BattleTargetTileCol, a4);
  }
  if ( *(_DWORD *)(v37 + 23) )
  {
    a4 = 0;
    v42 = -1;
    HIWORD(v34) = 0;
    v36 = 0;
    while ( 1 )
    {
      if ( !**(_DWORD **)(v37 + 23) || HIWORD(v34) + 5 > v35 )
      {
        if ( *(_DWORD *)(v37 + 23) )
          j__nfree_();
        v9 = v42;
        *(_DWORD *)(v37 + 23) = 0;
        if ( v42 != 255 )
        {
          LOWORD(v10) = v43;
          v13 = UnitBattle_MoveTrack(a1, v42, v42, v43, a4);
          *(_DWORD *)(v37 + 23) = v13;
          if ( !v13 )
          {
            LOWORD(v10) = v43;
            *(_DWORD *)(v37 + 23) = UnitBattle_MoveTrackForce(a1, v43, a4);
          }
        }
        if ( *(_DWORD *)(v37 + 23) )
          UnitBattle_Move(a1, v9, v10, a4);
        if ( !*(_DWORD *)(v37 + 23) )
          goto LABEL_8;
LABEL_7:
        j__nfree_();
        *(_DWORD *)(v37 + 23) = 0;
LABEL_8:
        UnitBattle_Defence(v9, v10, a4);
        return 0;
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      v14 = *(_DWORD **)(v37 + 23);
      a4 = *v14 - 1;
      *v14 = a4;
      v34 = v14[a4 + 1];
      if ( HIWORD(v34) + 5 <= v35 )
      {
        v43 = BYTE1(v14[a4 + 1]);
        v42 = v14[a4 + 1];
      }
      v15 = 31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534);
      v10 = (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(g_MapData + v15 + 852)];
      if ( v10 != 4 )
        break;
LABEL_35:
      if ( v9 * v36 > 20 )
      {
        if ( v42 == 255 )
        {
          a4 = *(_DWORD *)(v37 + 23);
          if ( !a4 )
            goto LABEL_8;
        }
        else
        {
          if ( *(_DWORD *)(v37 + 23) )
            j__nfree_();
          LOWORD(v10) = v43;
          *(_DWORD *)(v37 + 23) = 0;
          v32 = UnitBattle_MoveTrack(a1, v42, v42, v43, a4);
          *(_DWORD *)(v37 + 23) = v32;
          if ( !v32 )
          {
            LOWORD(v10) = v43;
            *(_DWORD *)(v37 + 23) = UnitBattle_MoveTrackForce(a1, v43, a4);
          }
          if ( *(_DWORD *)(v37 + 23) )
            UnitBattle_Move(a1, v9, v10, a4);
          if ( !*(_DWORD *)(v37 + 23) )
            goto LABEL_8;
        }
        goto LABEL_7;
      }
    }
    v36 = Unit_CalcEffectivenessA((char *)(v15 + g_MapData + 852), 0);
    if ( v36 < Unit_CalcEffectivenessC((__int16 *)(31
                                                 * *(__int16 *)(g_MapData
                                                              + 40 * g_UnitBattleScanTileRow
                                                              + 2 * g_BattleTargetTileCol
                                                              + 1534)
                                                 + g_MapData
                                                 + 852)) )
      v36 = Unit_CalcEffectivenessC((__int16 *)(31
                                              * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                                              + g_MapData
                                              + 852));
    LOWORD(v10) = BYTE1(v34);
    v16 = *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
    Debug_Log(v16, SBYTE1(v34), a4, (int)aOddzial_w_zasi);
    v17 = g_MapData + 852 + 31 * v16;
    a4 = v18;
    if ( UnitBattle_IsTileWithinRange(v19, v18, BYTE1(v34))
      && (*(_BYTE *)(31 * v16 + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(31 * v16 + g_MapData + 864)) >> 5) > 0 )
    {
      v20 = 0;
LABEL_33:
      LOBYTE(v20) = *(_BYTE *)(v17 + 8);
LABEL_34:
      v9 = v20 / 5;
      goto LABEL_35;
    }
    if ( *(char *)(BYTE1(v34) + g_MapData + 20 * a4 + 3134) <= 0 )
    {
      v10 = BYTE1(v34);
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * a4 + 2 * BYTE1(v34) + 1534) == -1
        || (v21 = 31 * v16 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v21 + 852)] & 1) == 0)
        && (*(_BYTE *)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v21 + 864)) >> 5) <= 0 )
      {
        LOWORD(v10) = BYTE1(v34);
        v22 = UnitBattle_MoveTrackNearWall(v16, a4, BYTE1(v34), a4);
        goto LABEL_44;
      }
      v10 = BYTE1(v34);
    }
    v22 = (int *)UnitBattle_MoveTrackNear(v16, BYTE1(v34), v10, a4);
LABEL_44:
    v23 = v22;
    if ( !v22 )
    {
      v24 = 31 * v16 + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v24 + 852)] )
      {
        if ( (*(_BYTE *)(v24 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v24 + 864)) >> 5) > 0 )
        {
          LOWORD(v10) = BYTE1(v34);
          v23 = UnitBattle_MoveTrackForce(v16, BYTE1(v34), a4);
        }
      }
    }
    if ( !v23 )
    {
      v20 = -1;
      goto LABEL_34;
    }
    if ( !*v23 )
    {
      j__nfree_();
      goto LABEL_33;
    }
    v25 = g_MapData + 31 * v16;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v25 + 852)]
      && (*(_BYTE *)(v25 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v25 + 864)) >> 5) > 0 )
    {
      v39 = *(_WORD *)(v17 + 4);
      HIWORD(v41) = 0;
      v38 = *(_WORD *)(v17 + 6);
      if ( *v23 )
      {
        while ( 1 )
        {
          LOWORD(v10) = BYTE1(v34);
          if ( UnitBattle_IsTileWithinRange(v16, a4, BYTE1(v34)) )
            break;
          v30 = *v27 - 1;
          *v27 = v30;
          v41 = v27[v30 + 1];
          if ( HIWORD(v41) > (int)*(unsigned __int8 *)(v17 + 8) )
            goto LABEL_72;
          *(_WORD *)(v17 + 4) = (unsigned __int8)v41;
          *(_WORD *)(v17 + 6) = BYTE1(v41);
          if ( !*v27 )
            goto LABEL_69;
        }
        *(_WORD *)(v17 + 4) = v39;
        *(_WORD *)(v17 + 6) = v38;
        j__nfree_();
        LOWORD(v28) = HIWORD(v41);
        v29 = *(unsigned __int8 *)(v17 + 8);
        if ( v29 > v28 )
        {
          v20 = v29 - v28;
          goto LABEL_34;
        }
LABEL_66:
        v20 = 0;
        goto LABEL_34;
      }
LABEL_69:
      LOWORD(v10) = BYTE1(v34);
      if ( !UnitBattle_IsTileWithinRange(v16, a4, BYTE1(v34)) )
      {
LABEL_72:
        *(_WORD *)(v17 + 4) = v39;
        *(_WORD *)(v17 + 6) = v38;
        j__nfree_();
        goto LABEL_34;
      }
      *(_WORD *)(v17 + 4) = v39;
      *(_WORD *)(v17 + 6) = v38;
      if ( *(unsigned __int8 *)(v17 + 8) > (int)HIWORD(v41) )
      {
        j__nfree_();
        v20 = *(unsigned __int8 *)(v17 + 8) - v31;
        goto LABEL_34;
      }
    }
    else if ( *v23 )
    {
      v40 = v23[1];
      j__nfree_();
      LOBYTE(v26) = *(_BYTE *)(v17 + 8);
      if ( v26 <= HIWORD(v40) )
        v20 = 0;
      else
        v20 = v26 - HIWORD(v40);
      goto LABEL_34;
    }
    j__nfree_();
    goto LABEL_66;
  }
  return 0;
}
// 43B76C: variable 'v4' is possibly undefined
// 43B7F1: variable 'v9' is possibly undefined
// 43B8C0: variable 'v43' is possibly undefined
// 43BA5B: variable 'v18' is possibly undefined
// 43BA5D: variable 'v19' is possibly undefined
// 43BAAC: variable 'v20' is possibly undefined
// 43BC59: variable 'v26' is possibly undefined
// 43BCF5: variable 'v28' is possibly undefined
// 43BD15: variable 'v27' is possibly undefined
// 43BD8E: variable 'v31' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;

//----- (0043BE50) --------------------------------------------------------
int  UnitBattle_ExecuteAiActionForUnit(int a1, int a2, DWORD a3)
{
  DWORD v4; // ebx
  DWORD v5; // edi
  int v6; // ecx
  int result; // eax
  __int16 v8; // bx
  int *v9; // eax
  int v10; // ecx
  __int16 v11; // bx
  int v12; // eax
  int v13; // ecx
  int v14; // ebp
  int v15; // edi
  int v16; // ebp
  int v17; // edi
  DWORD v18; // edi
  int v19; // ecx
  int v20; // [esp+0h] [ebp-2Ch] BYREF
  int v21; // [esp+4h] [ebp-28h] BYREF
  int v22; // [esp+8h] [ebp-24h]
  signed int v23; // [esp+Ch] [ebp-20h]
  DWORD v24; // [esp+10h] [ebp-1Ch]
  __int16 *v25; // [esp+14h] [ebp-18h]

  v4 = 31 * a1;
  v25 = (__int16 *)(31 * a1 + g_MapData + 852);
  v5 = 801 * a1;
  v23 = 0;
  UnitBattle_UpdateIdleAnimatedUnits();
  v6 = g_UnitBattleScanTileRow;
  switch ( g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + v5] )
  {
    case 1:
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v4 + g_MapData + 852)] )
      {
        v6 = (v25[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)v25 + 12)) >> 5);
        if ( v6 > 0 )
          goto LABEL_4;
      }
      v11 = g_BattleTargetTileCol;
      v12 = UnitBattle_MoveTrackNear(a1, v6, g_BattleTargetTileCol, a3);
      *(_DWORD *)((char *)v25 + 23) = v12;
      if ( v12 )
        UnitBattle_Move(a1, v13, v11, a3);
      if ( *(_DWORD *)((char *)v25 + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)v25 + 23) = 0;
      }
      v24 = 31 * a1;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        v14 = *(char *)(31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                      + g_MapData
                      + 861);
        v15 = *((char *)v25 + 9);
        UnitBattle_CalcMeleeExchange(a1, *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), &v21, &v20, 0);
        v22 = v14 - v21 - (v15 - v20);
        UnitBattle_CalcMeleeExchange(a1, *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534), &v21, &v20, 1);
        v16 = v14 - v21;
        v17 = v15 - v20;
        if ( v16 <= 0 && v17 <= 0
          || !UnitBattle_Attack(
                a1,
                *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534),
                v16 - v17 > v22)
          || *(__int16 *)(g_MapData + v24 + 852) == -1 )
        {
          goto LABEL_5;
        }
      }
      while ( *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) != -1 );
      if ( *(unsigned __int8 *)(g_MapData + v24 + 860) <= 4u )
        goto LABEL_5;
      v23 = 1;
      result = 1;
      break;
    case 5:
      result = 0;
      break;
    case 6:
      v8 = g_BattleTargetTileCol;
      v9 = UnitBattle_MoveTrackForce(a1, g_BattleTargetTileCol, a3);
      *(_DWORD *)((char *)v25 + 23) = v9;
      if ( v9 )
        UnitBattle_Move(a1, v10, v8, a3);
      if ( *(_DWORD *)((char *)v25 + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)v25 + 23) = 0;
      }
      result = 0;
      break;
    case 7:
      result = UnitBattle_ApproachToSafeDistance(a1, g_UnitBattleScanTileRow, v4, a3);
      break;
    case 8:
      if ( g_UnitTypeMaxRange_512582[88 * *v25] && (v25[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)v25 + 12)) >> 5) > 0 )
      {
LABEL_4:
        UnitBattle_UpdateIdleAnimatedUnits();
        v23 = UnitBattle_MoveShootingUnit(a1, a2, v4, a3);
        goto LABEL_5;
      }
      v18 = 31 * a1;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( !UnitBattle_AttackWall(a1, g_UnitBattleScanTileRow, v19, g_BattleTargetTileCol) || *(__int16 *)(g_MapData + v18 + 852) == -1 )
          goto LABEL_5;
      }
      while ( *(_BYTE *)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) );
      if ( *(unsigned __int8 *)(g_MapData + v18 + 860) <= 4u )
        goto LABEL_5;
      v23 = 1;
      result = 1;
      break;
    default:
LABEL_5:
      result = v23;
      break;
  }
  return result;
}
// 43BF67: variable 'v10' is possibly undefined
// 43BF9E: variable 'v13' is possibly undefined
// 43C147: variable 'v19' is possibly undefined
// 532048: using guessed type int g_MapData;
// 532448: using guessed type int dword_532448[];
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;

//----- (0043C1E0) --------------------------------------------------------
signed int  UnitBattle_BuildAiUnitQueueForCurrentMode(int a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // esi
  int v4; // ebx
  int v5; // ecx
  int v6; // eax
  char *v7; // eax
  int k; // ecx
  int v9; // eax
  int m; // ecx
  signed int result; // eax
  int v12; // ebx
  int v13; // edx
  int v14; // eax
  int v15; // edi
  int v16; // esi
  __int16 v17; // cx
  int v18; // edi
  int v19; // ecx
  int j; // ebx
  int i; // ebx
  int v22; // ecx
  char *v23; // eax
  int v24; // esi
  int v25; // ebx
  int n; // ebx
  int v27; // eax
  int ii; // ecx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // ecx
  __int16 v33; // [esp+0h] [ebp-72h]
  WCIsvListBase *v34[5]; // [esp+2h] [ebp-70h]
  int v35; // [esp+16h] [ebp-5Ch]
  int v36; // [esp+1Ah] [ebp-58h]
  int v37; // [esp+1Eh] [ebp-54h]
  int v38; // [esp+22h] [ebp-50h]
  int v39; // [esp+26h] [ebp-4Ch]
  int v40; // [esp+2Ah] [ebp-48h]
  int v41; // [esp+2Eh] [ebp-44h]
  int v42; // [esp+32h] [ebp-40h]
  int v43; // [esp+36h] [ebp-3Ch]
  int v44; // [esp+3Ah] [ebp-38h]
  int v45; // [esp+3Eh] [ebp-34h]
  int v46; // [esp+42h] [ebp-30h]
  int v47; // [esp+46h] [ebp-2Ch]
  int v48; // [esp+4Ah] [ebp-28h]
  int v49; // [esp+4Eh] [ebp-24h]
  signed int v50; // [esp+52h] [ebp-20h]
  int v51; // [esp+56h] [ebp-1Ch]

  v46 = a1;
  WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
  memset(v34, 0xFF, 20);
  v51 = 0;
  v44 = 0;
  v45 = 0;
  while ( *(_DWORD *)(g_MapData + 804) - 1 >= v44 )
  {
    v12 = 0;
    v35 = v45;
    v13 = 0;
    v14 = 2 * v51;
    while ( v12 <= *(_DWORD *)(g_MapData + 800) - 1 )
    {
      v15 = v13 + g_MapData + v35;
      v16 = *(__int16 *)(v15 + 1534);
      if ( v16 == -1 || *(unsigned __int8 *)(g_MapData + 31 * v16 + 854) != v46 )
      {
        v13 += 2;
        ++v12;
      }
      else
      {
        v17 = *(_WORD *)(v15 + 1534);
        v14 += 2;
        v18 = v51 + 1;
        *(__int16 *)((char *)&v33 + v14) = v17;
        v51 = v18;
        v13 += 2;
        ++v12;
      }
    }
    v45 += 40;
    ++v44;
  }
  if ( (unsigned int)g_UnitBattleAiCurrentPlanMode >= 2 )
  {
    if ( (unsigned int)g_UnitBattleAiCurrentPlanMode <= 2 || g_UnitBattleAiCurrentPlanMode == 6 )
    {
      v19 = *(unsigned __int16 *)(g_MapData + 31 * SLOWORD(v34[0]) + 856);
      if ( (unsigned __int16)v19 >= *(_DWORD *)(g_MapData + 804) / 2 )
      {
        for ( i = 0; i != 20; i += 2 )
        {
          result = *(__int16 *)((char *)v34 + i);
          if ( result != -1 )
          {
            v36 = *(__int16 *)((char *)v34 + i);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v36);
          }
        }
      }
      else
      {
        for ( j = 18; j != -2; j -= 2 )
        {
          result = *(__int16 *)((char *)v34 + j);
          if ( result != -1 )
          {
            v37 = *(__int16 *)((char *)v34 + j);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v37);
          }
        }
      }
      return result;
    }
  }
  else if ( !g_UnitBattleAiCurrentPlanMode )
  {
    do
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      v3 = -1;
      v47 = 0;
      v49 = 0;
      v4 = 0;
      v5 = 0;
      do
      {
        v6 = *(__int16 *)((char *)v34 + v5);
        if ( v6 != -1 && !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * v6 + g_MapData + 852)] )
        {
          v47 = 1;
          if ( v3 < Unit_CalcEffectivenessA((char *)(31 * v6 + g_MapData + 852), 0) )
          {
            v7 = (char *)(31 * *(__int16 *)((char *)v34 + v5) + g_MapData + 852);
            v49 = v4;
            v3 = Unit_CalcEffectivenessA(v7, 0);
          }
        }
        ++v4;
        v5 += 2;
      }
      while ( v4 < 10 );
      if ( *((__int16 *)v34 + v49) != -1 )
      {
        v38 = *((__int16 *)v34 + v49);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v38);
      }
      *((_WORD *)v34 + v49) = -1;
    }
    while ( v47 );
    for ( k = 0; k != 20; k += 2 )
    {
      v9 = *(__int16 *)((char *)v34 + k);
      if ( v9 != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * v9 + g_MapData + 852)] == 4 )
      {
        v39 = *(__int16 *)((char *)v34 + k);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v39);
        *(_WORD *)((char *)v34 + k) = -1;
      }
    }
    for ( m = 0; m != 20; m += 2 )
    {
      result = *(__int16 *)((char *)v34 + m);
      if ( result != -1 )
      {
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * result + g_MapData + 852)] )
        {
          v40 = *(__int16 *)((char *)v34 + m);
          result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v40);
          *(_WORD *)((char *)v34 + m) = -1;
        }
      }
    }
    return result;
  }
  for ( n = 0; n != 20; n += 2 )
  {
    v27 = *(__int16 *)((char *)v34 + n);
    if ( v27 != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * v27 + g_MapData + 852)] == 4 )
    {
      v41 = *(__int16 *)((char *)v34 + n);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v41);
      *(_WORD *)((char *)v34 + n) = -1;
    }
  }
  for ( ii = 0; ii != 20; ii += 2 )
  {
    v29 = *(__int16 *)((char *)v34 + ii);
    if ( v29 != -1 && g_UnitTypeMaxRange_512582[88 * *(__int16 *)(g_MapData + 31 * v29 + 852)] )
    {
      v42 = *(__int16 *)((char *)v34 + ii);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v42);
      *(_WORD *)((char *)v34 + ii) = -1;
    }
  }
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    v24 = -1;
    v48 = 0;
    v50 = 0;
    v22 = 0;
    v25 = 0;
    while ( 1 )
    {
      v30 = *(__int16 *)((char *)v34 + v25);
      if ( v30 != -1 )
        break;
LABEL_45:
      ++v22;
      v25 += 2;
      if ( v22 >= 10 )
        goto LABEL_63;
    }
    v31 = 31 * v30;
    v48 = 1;
    if ( g_UnitTypeRole[88 * *(__int16 *)(g_MapData + v31 + 852)] != 4 )
    {
      if ( v24 < Unit_CalcEffectivenessA((char *)(g_MapData + 852 + v31), 0) )
      {
        v23 = (char *)(31 * *(__int16 *)((char *)v34 + v25) + g_MapData + 852);
        v50 = v22;
        v24 = Unit_CalcEffectivenessA(v23, 0);
      }
      goto LABEL_45;
    }
    v50 = v22;
LABEL_63:
    if ( *((__int16 *)v34 + v50) != -1 )
    {
      v43 = *((__int16 *)v34 + v50);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v43);
    }
    result = v50;
    v32 = v48;
    *((_WORD *)v34 + v50) = -1;
  }
  while ( v32 );
  return result;
}
// 43C351: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C3AE: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C591: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C5EE: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C203: variable 'v2' is possibly undefined
// 43C203: variable 'v1' is possibly undefined
// 43C2B4: variable 'v5' is possibly undefined
// 43C362: variable 'k' is possibly undefined
// 43C3BF: variable 'm' is possibly undefined
// 43C4B3: variable 'v19' is possibly undefined
// 43C51E: variable 'v22' is possibly undefined
// 43C5FF: variable 'ii' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 5437C0: using guessed type int dword_5437C0;

//----- (0043C6B0) --------------------------------------------------------
signed int  UnitBattle_ScanAiPlanRangeLine(int a1, signed int a2)
{
  int i; // eax
  int v3; // edx
  int v4; // edx
  int v5; // ebp
  int v6; // ebx
  int v7; // ebx
  int v8; // esi
  int v9; // edx
  BOOL v10; // eax
  int v11; // ecx
  int v12; // esi
  int v14; // ecx
  int v15; // eax
  int *v16; // eax
  int *v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int *v22; // ecx
  int v23; // eax
  int v24; // edx
  int v25; // edx
  int v27; // [esp+8h] [ebp-34h]
  int v28; // [esp+8h] [ebp-34h]
  int v29; // [esp+10h] [ebp-2Ch]
  int battle_width;
  int battle_height;
  __int16 v30; // [esp+14h] [ebp-28h]
  __int16 v31; // [esp+18h] [ebp-24h]
  int v32; // [esp+1Ch] [ebp-20h]
  int v33; // [esp+20h] [ebp-1Ch]

  v32 = -20;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_enter", a1, a2, g_AttackerStartsOnLeft, g_DefenderStartsOnLeft);
  if ( *(_DWORD *)(g_MapData + 836) == a1 )
  {
    if ( g_AttackerStartsOnLeft )
      a2 = 1;
    else
      a2 = -1;
  }
  if ( a1 == *(_DWORD *)(g_MapData + 840) )
  {
    if ( g_DefenderStartsOnLeft )
      a2 = 1;
    else
      a2 = -1;
  }
  for ( i = 0; i != 682; i += 31 )
  {
    v3 = i + g_MapData;
    if ( *(__int16 *)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(v3 + 854) == a1 )
    {
      v4 = a2 * *(unsigned __int16 *)(v3 + 856);
      if ( v4 > v32 )
        v32 = v4;
    }
  }
  v33 = 0;
  v29 = 0;
  v5 = a2 * (v32 + 3);
  battle_width = *(_DWORD *)(g_MapData + 800);
  battle_height = *(_DWORD *)(g_MapData + 804);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_ai_plan_range_line",
    a1,
    v5,
    battle_width,
    battle_height);
  if ( v5 < 0 || v5 >= battle_height )
    return 0;
  while ( 1 )
  {
    v6 = g_MapData + v29;
    if ( *(__int16 *)(g_MapData + v29 + 852) == -1 || *(unsigned __int8 *)(v6 + 854) == a1 )
      goto LABEL_23;
    v7 = *(unsigned __int16 *)(v6 + 858);
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_plan_range_candidate",
      v33,
      v5,
      v7,
      *(__int16 *)(v6 + 852));
    if ( v7 < 0 || v7 >= battle_width )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_skip_oob_target", v33, v5, v7, battle_width);
      goto LABEL_23;
    }
    if ( *(__int16 *)(40 * v5 + g_MapData + 2 * v7 + 1534) != -1 )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_target_occupied", v33, v5, v7, 0);
      return 0;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_log", v33, v5, v7, a1);
    Debug_Log(a1, v7, v5, (int)aOddzial_w_zasi);
    v8 = g_MapData + 852;
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_range", v33, v5, v7, a1);
    v10 = UnitBattle_IsTileWithinRange(v33, v5, v7);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_after_range", v33, v5, v7, v10);
    v12 = g_MapData + v29 + 852;
    if ( v10
      && (*(_BYTE *)(v29 + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(v29 + g_MapData + 864)) >> 5) > 0 )
    {
      goto LABEL_17;
    }
    v14 = v7;
    if ( *(char *)(v7 + g_MapData + 20 * v5 + 3134) <= 0
      || (v14 = g_MapData + 40 * v5, *(__int16 *)(v14 + 2 * v7 + 1534) != -1)
      && ((v15 = 31 * v33 + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v15 + 852)] & 1) != 0)
       || (v14 = (unsigned __int8)(2 * *(_BYTE *)(v15 + 864)) >> 5, (*(_BYTE *)(v15 + 864) & 3) + 1 - v14 > 0)) )
    {
      v16 = UnitBattle_MoveTrackNear(v33, v5, v7, v5);
    }
    else
    {
      v16 = UnitBattle_MoveTrackNearWall(v33, v5, v7, v5);
    }
    v17 = v16;
    if ( !v16 )
    {
      v18 = g_MapData + 31 * v33;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v18 + 852)] )
      {
        if ( (*(_BYTE *)(v18 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v18 + 864)) >> 5) > 0 )
          v17 = UnitBattle_MoveTrackForce(v33, v7, v5);
      }
    }
    if ( !v17 )
      goto LABEL_23;
    if ( !*v17 )
    {
      nfree_((int)(uintptr_t)v17);
LABEL_17:
      if ( *(_BYTE *)(v12 + 8) )
        return 0;
      goto LABEL_23;
    }
    v19 = 31 * v33 + g_MapData;
    if ( !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v19 + 852)]
      || (*(_BYTE *)(v19 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v19 + 864)) >> 5) <= 0 )
    {
      if ( !*v17 )
        goto LABEL_59;
      v27 = v17[1];
      nfree_((int)(uintptr_t)v17);
      LOWORD(v20) = HIWORD(v27);
      v21 = *(unsigned __int8 *)(v12 + 8);
      if ( v21 > v20 && v21 - v20 > 0 )
        return 0;
      goto LABEL_23;
    }
    v30 = *(_WORD *)(v12 + 4);
    HIWORD(v28) = 0;
    v31 = *(_WORD *)(v12 + 6);
    if ( *v17 )
      break;
LABEL_50:
    if ( !UnitBattle_IsTileWithinRange(v33, v5, v7) )
    {
LABEL_58:
      *(_WORD *)(v12 + 4) = v30;
      *(_WORD *)(v12 + 6) = v31;
LABEL_59:
      nfree_((int)(uintptr_t)v17);
      goto LABEL_23;
    }
    *(_WORD *)(v12 + 4) = v30;
    *(_WORD *)(v12 + 6) = v31;
    if ( *(unsigned __int8 *)(v12 + 8) <= (int)HIWORD(v28) )
      goto LABEL_59;
    nfree_((int)(uintptr_t)v17);
    if ( *(unsigned __int8 *)(v12 + 8) - HIWORD(v28) > 0 )
      return 0;
LABEL_23:
    v29 += 31;
    if ( ++v33 >= 22 )
      return 1;
  }
  while ( !UnitBattle_IsTileWithinRange(v33, v5, v7) )
  {
    v23 = *v17 - 1;
    *v17 = v23;
    v28 = v17[v23 + 1];
    if ( HIWORD(v28) > (int)*(unsigned __int8 *)(v12 + 8) )
      goto LABEL_58;
    *(_WORD *)(v12 + 4) = (unsigned __int8)v28;
    *(_WORD *)(v12 + 6) = BYTE1(v28);
    if ( !*v17 )
      goto LABEL_50;
  }
  *(_WORD *)(v12 + 4) = v30;
  *(_WORD *)(v12 + 6) = v31;
  nfree_((int)(uintptr_t)v17);
  v25 = *(unsigned __int8 *)(v12 + 8);
  if ( v25 <= HIWORD(v28) || v25 - HIWORD(v28) <= 0 )
    goto LABEL_23;
  return 0;
}
// 43C807: variable 'v9' is possibly undefined
// 43C80C: variable 'v11' is possibly undefined
// 43C9FF: variable 'v20' is possibly undefined
// 43CA80: variable 'v22' is possibly undefined
// 43CB00: variable 'v24' is possibly undefined
// 43CB45: variable 'v25' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;

//----- (0043CB80) --------------------------------------------------------
void UnitBattle_ScanAiWallTargetColumns()
{
  int v0; // edx
  int v1; // ecx
  int v2; // eax
  int v3; // esi
  int v4; // edx
  int battle_width;
  int battle_height;
  int wall_column;

  battle_width = *(_DWORD *)(g_MapData + 800);
  battle_height = *(_DWORD *)(g_MapData + 804);
  wall_column = *(_DWORD *)(g_MapData + 828);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_enter", wall_column, battle_width, battle_height, g_UnitBattleWallScanTileRow);
  if ( wall_column < 0 || wall_column >= battle_width || battle_width <= 2 || battle_height <= 2 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_skip", wall_column, battle_width, battle_height, g_UnitBattleWallScanTileRow);
    return;
  }
  g_UnitBattleWallScanTileRow = 1;
  v0 = 1;
  v1 = 20;
  while ( v0 < battle_height - 1 )
  {
    if ( *(char *)(g_MapData + v1 + wall_column + 3135) > 0 )
      g_UnitBattleWallScanTileRow = v0;
    v1 += 20;
    ++v0;
  }
  g_BattleWallScanColumn = wall_column;
  g_BattleWallScanTileX = g_BattleWallScanColumn + 1;
  v2 = 1;
  v3 = 20 * g_UnitBattleWallScanTileRow;
  while ( v2 < battle_width - 1 )
  {
    v4 = g_MapData + v3 + v2;
    if ( *(char *)(v4 + 3134) >= 0 && *(_BYTE *)(v4 + 3134) < *(_BYTE *)(g_BattleWallScanColumn + g_MapData + v3 + 3134) )
    {
      g_BattleWallScanTileX = g_BattleWallScanColumn;
      g_BattleWallScanColumn = v2++;
    }
    else
    {
      ++v2;
    }
  }
  Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_exit", g_UnitBattleWallScanTileRow, g_BattleWallScanColumn, g_BattleWallScanTileX, 0);
  return;
}
// 43CBE0: control flows out of bounds to 43C853
// 532048: using guessed type int g_MapData;
// 5437B0: using guessed type int dword_5437B0;
// 5437B4: using guessed type int dword_5437B4;
// 5437B8: using guessed type int dword_5437B8;

//----- (0043CC50) --------------------------------------------------------
signed int  UnitBattle_SelectAiPlanMode(int a1, signed int a2)
{
  int v2; // edx

  v2 = a1;
  if ( g_UnitBattleAiTurnCounter <= 3 && UnitBattle_ScanAiPlanRangeLine(a1, a2) )
    return 2;
  if ( *(int *)(g_MapData + 828) <= 0 )
    return 4;
  if ( g_UnitBattleAiTurnCounter == 1 && v2 == *(_DWORD *)(g_MapData + 840) && g_UnitBattleAiCurrentPlanMode != 6 )
    return 6;
  if ( v2 == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter < 3 )
    return 0;
  if ( v2 == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter >= 3 )
    return 4;
  return 1;
}
// 43CC79: variable 'v2' is possibly undefined
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532078: using guessed type int dword_532078;

//----- (0043CD00) --------------------------------------------------------
signed int  UnitBattle_RunAiTurnForSide(unsigned __int8 a1)
{
  signed int v2; // esi
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  signed int v10; // esi
  int i; // edi
  int v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v26; // [esp+0h] [ebp-1Ch]

  v2 = 1;
  v26 = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_enter", a1, g_CurrentPlayerIndex, g_UnitBattleAiTurnCounter, 0);
  g_BattleAiActionAttemptCount = 0;
  ++g_UnitBattleAiTurnCounter;
  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_before_wall_scan",
      a1,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 800),
      *(_DWORD *)(g_MapData + 804));
    UnitBattle_ScanAiWallTargetColumns();
    Diagnostics_TraceWorldMapActionEvent("battle_ai_after_wall_scan", a1, g_UnitBattleWallScanTileRow, g_BattleWallScanColumn, g_BattleWallScanTileX);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_ai_before_idle", a1, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_idle", a1, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(a1, a1);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_mode", a1, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  UnitBattle_BuildAiUnitQueueForCurrentMode(a1);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_queue", a1, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
  UnitBattle_UpdateIdleAnimatedUnits();
  g_BattleShootingUnitMoveActiveFlag = 0;
  switch ( g_UnitBattleAiCurrentPlanMode )
  {
    case 0:
    case 1:
    case 4:
      goto LABEL_13;
    case 2:
      while ( g_UnitBattleAiCandidateQueueTail )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        v4 = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        v26 = v4;
        UnitBattle_ResetAiReachGridForSide(a1);
        UnitBattle_ScoreAiActionGridForUnit(v26, a1, 0, 1);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(v26, a1) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(v26, a1, 0);
        }
        else
        {
          WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v26);
        }
      }
      goto LABEL_8;
    case 6:
LABEL_8:
      v10 = 0;
      for ( i = g_BattleAiUnitQueueCount; v10 < i; ++v10 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        v12 = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        v26 = v12;
        UnitBattle_ResetAiReachGridForSide(a1);
        UnitBattle_ScoreAiActionGridForUnit(v26, a1, 0, v10);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(v26, a1) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(v26, a1, 0);
        }
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v26);
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(a1, a1);
      UnitBattle_UpdateIdleAnimatedUnits();
      v2 = 0;
      UnitBattle_BuildAiUnitQueueForCurrentMode(a1);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_after_requeue", a1, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
      UnitBattle_UpdateIdleAnimatedUnits();
LABEL_13:
      if ( !g_UnitBattleAiCandidateQueueTail )
        goto LABEL_21;
      break;
    default:
      goto LABEL_21;
  }
  while ( 1 )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    v26 = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_unit_candidate", v26, a1, g_UnitBattleAiCandidateQueueTail, v2);
    v19 = g_MapData + 31 * v26;
    if ( *(__int16 *)(v19 + 852) != -1 && a1 == *(_BYTE *)(v19 + 854) )
      break;
LABEL_20:
    if ( !g_UnitBattleAiCandidateQueueTail )
    {
LABEL_21:
      WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_exit", a1, v2, g_UnitBattleAiCandidateQueueTail, 0);
      return v2;
    }
  }
  while ( 1 )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    UnitBattle_ResetAiReachGridForSide(a1);
    if ( UnitBattle_ScoreAiActionGridForUnit(v26, a1, 0, v2) )
      return 1;
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_SelectAiActionForUnit(v26, a1) )
    {
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, v26);
LABEL_19:
      v2 = 0;
      goto LABEL_20;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_ExecuteAiActionForUnit(v26, a1, 0) )
      goto LABEL_19;
  }
}
// 43CD57: variable 'v3' is possibly undefined
// 43CD9F: variable 'v5' is possibly undefined
// 43CDA9: variable 'v6' is possibly undefined
// 43CDB8: variable 'v7' is possibly undefined
// 43CDCF: variable 'v9' is possibly undefined
// 43CE04: variable 'v13' is possibly undefined
// 43CE0E: variable 'v14' is possibly undefined
// 43CE1D: variable 'v15' is possibly undefined
// 43CE30: variable 'v17' is possibly undefined
// 43CE3C: variable 'v16' is possibly undefined
// 43CE64: variable 'v18' is possibly undefined
// 43CEBC: variable 'v20' is possibly undefined
// 43CEC6: variable 'v21' is possibly undefined
// 43CED9: variable 'v22' is possibly undefined
// 43CEEC: variable 'v24' is possibly undefined
// 43CF10: variable 'v26' is possibly undefined
// 43CF28: variable 'v8' is possibly undefined
// 43CF40: variable 'v23' is possibly undefined
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532078: using guessed type int dword_532078;
// 5437A8: using guessed type int dword_5437A8;
// 5437AC: using guessed type int dword_5437AC;
// 5437C0: using guessed type int dword_5437C0;
// 5437C8: using guessed type int dword_5437C8;
// 5437CC: using guessed type int dword_5437CC;

//----- (0043CF50) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorRoot(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();

//----- (0043CF60) --------------------------------------------------------
int  WCIsvListBase_dtorRoot(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_WCIsvListBaseRoot_DtorArrayTag);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 43CF89: variable 'v4' is possibly undefined
// 43CF80: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0043CF90) --------------------------------------------------------
int __cdecl WCIsvListBase_dtorFreeOnly()
{
  return j__nfree_();
}

//----- (0043CFA0) --------------------------------------------------------
BOOL  WCIsvListBase_ValuesEqual(_DWORD *a1, _DWORD *a2)
{
  return *a1 == *a2;
}

//----- (0043CFB0) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorVariant124(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  result[2] = 0;
  result[3] = 0;
  result[4] = 0;
  result[5] = 0;
  result[1] = &g_WCIsvListBaseDtor_Vtable;
  result[1] = &g_WCIsvListBaseDestroyElements_Vtable;
  result[1] = &g_WCIsvListBaseVariant124_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F114: using guessed type int (__thiscall *off_50F114)(WCIsvListBase *this);
// 50F124: using guessed type void *off_50F124;

//----- (0043CFF0) --------------------------------------------------------
int  WCIsvListBase_dtorVariant124(WCIsvListBase *a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant124_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (a2 & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 43D020: variable 'v4' is possibly undefined
// 43D02A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0043D030) --------------------------------------------------------
int  WCIsvListBase_ctorVariant124AndCopy(_DWORD *a1, _DWORD *a2)
{
  int v2; // ecx

  *a1 = 0;
  a1[1] = &g_WCIsvListBaseRoot_Vtable;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = 0;
  a1[5] = 0;
  a1[1] = &g_WCIsvListBaseDtor_Vtable;
  a1[1] = &g_WCIsvListBaseDestroyElements_Vtable;
  a1[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(a1, a2, (int)a1);
  return v2;
}
// 43D076: variable 'v2' is possibly undefined
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F114: using guessed type int (__thiscall *off_50F114)(WCIsvListBase *this);
// 50F124: using guessed type void *off_50F124;

//----- (0043D080) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorVariant134(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  result[2] = 0;
  result[3] = 0;
  result[4] = 0;
  result[5] = 0;
  result[1] = &g_WCIsvListBaseDtor_Vtable;
  result[1] = &g_WCIsvListBaseVariant124_Vtable;
  result[1] = &g_WCIsvListBaseVariant134_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;

//----- (0043D0C0) --------------------------------------------------------
int  WCIsvListBase_dtorVariant134(WCIsvListBase *a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant134_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (a2 & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 43D0F0: variable 'v4' is possibly undefined
// 43D0FA: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

typedef struct WCCompatLink {
  int next_link;
  int value;
} WCCompatLink;

typedef struct WCCompatListBase {
  int head_link;
  int vtable;
  int tail_link;
  int count;
  int alloc_fn;
  int free_fn;
} WCCompatListBase;

static WCCompatListBase *WCCompat_ListFromBase(WCIsvListBase *this)
{
  return (WCCompatListBase *)this;
}

static WCCompatListBase *WCCompat_ListFromHandle(int list_handle)
{
  return (WCCompatListBase *)(uintptr_t)(unsigned int)list_handle;
}

static WCCompatLink *WCCompat_LinkFromHandle(int link_handle)
{
  return (WCCompatLink *)(uintptr_t)(unsigned int)link_handle;
}

//----- (0043D100) --------------------------------------------------------
_DWORD *unknown_libname_3(WCIsvListBase *this)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromBase(this);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseFreeOnly_Vtable;
  WCIsvListBase_dtor(this);
  return (_DWORD *)this;
}

//----- (0043D100) --------------------------------------------------------
_DWORD * WCIsvListBase_dtorVariant104(WCIsvListBase *this)
{
  return unknown_libname_3(this);
}

int __fastcall WCIsvListBase_base_next(int list_handle, int cursor_handle)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  list = WCCompat_ListFromHandle(list_handle);
  if ( !list || !list->head_link )
    return 0;
  for ( link = WCCompat_LinkFromHandle(list->head_link); link; link = WCCompat_LinkFromHandle(link->next_link) )
  {
    if ( (int)(uintptr_t)link == cursor_handle )
      return link->next_link;
  }
  return list->head_link;
}

int __fastcall WCIsvListBase_base_insert(int list_handle, int link_handle)
{
  WCCompatListBase *list;
  WCCompatLink *link;
  WCCompatLink *tail;

  list = WCCompat_ListFromHandle(list_handle);
  link = WCCompat_LinkFromHandle(link_handle);
  if ( !list || !link )
    return 0;
  link->next_link = 0;
  if ( list->tail_link )
  {
    tail = WCCompat_LinkFromHandle(list->tail_link);
    if ( tail )
      tail->next_link = link_handle;
    else
      list->head_link = link_handle;
  }
  else
  {
    list->head_link = link_handle;
  }
  list->count += 1;
  return link_handle;
}

int __fastcall WCIsvListBase_base_sget(int list_handle)
{
  WCCompatListBase *list;
  WCCompatLink *head;
  int link_handle;

  list = WCCompat_ListFromHandle(list_handle);
  if ( !list || !list->head_link )
    return 0;
  link_handle = list->head_link;
  head = WCCompat_LinkFromHandle(link_handle);
  if ( !head )
  {
    list->head_link = 0;
    list->tail_link = 0;
    list->count = 0;
    return 0;
  }
  list->head_link = head->next_link;
  if ( !list->head_link )
    list->tail_link = 0;
  if ( list->count > 0 )
    list->count -= 1;
  return link_handle;
}

void WCIsvListBase_base_destroy(WCIsvListBase *this)
{
  int link_handle;

  for ( link_handle = WCIsvListBase_base_sget((int)(uintptr_t)this); link_handle; link_handle = WCIsvListBase_base_sget((int)(uintptr_t)this) )
    WCIsvListBase_ReleaseLinkNode((int)(uintptr_t)this, link_handle, 8);
}

_DWORD WCIsvListBase_dtor(WCIsvListBase *this)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromBase(this);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseDtor_Vtable;
  if ( list->tail_link )
    Noop_WCIsvListErrorHook((int)(uintptr_t)this);
  return (unsigned int)(uintptr_t)this;
}

//----- (0043D120) --------------------------------------------------------
_DWORD * WCIsvListBase_AllocLinkNode(int a1, int a2)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  list = WCCompat_ListFromHandle(a1);
  if ( !list )
    return 0;
  if ( !list->alloc_fn )
    link = (WCCompatLink *)(uintptr_t)(unsigned int)j_Mem_Alloc(8);
  else
    link = (WCCompatLink *)(uintptr_t)(unsigned int)(*(int (__cdecl **)(int))(uintptr_t)(unsigned int)list->alloc_fn)(8);
  if ( !link )
    return 0;
  link->next_link = 0;
  link->value = a2;
  return (_DWORD *)link;
}

//----- (0043D160) --------------------------------------------------------
int  WCIsvListBase_ReleaseLinkNode(int a1, int a2, int a3)
{
  if ( !a2 )
    return 0;
  if ( *(_DWORD *)(a1 + 20) )
    return (*(int (__cdecl **)(int))(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 20))(a3);
  return nfree_(a2);
}

//----- (0043D180) --------------------------------------------------------
int  WCIsvListBase_CopyAppendAll(_DWORD *a1, _DWORD *a2, int a3)
{
  int link_handle;
  WCCompatLink *link;

  *a1 = *a2;
  a1[4] = a2[4];
  a1[5] = a2[5];
  link_handle = WCIsvListBase_base_next((int)(uintptr_t)a2, a3);
  while ( link_handle )
  {
    link = WCCompat_LinkFromHandle(link_handle);
    if ( !link )
      break;
    WCIsvListBase_AppendValue((int)(uintptr_t)a1, link->value);
    link_handle = WCIsvListBase_base_next((int)(uintptr_t)a2, link_handle);
  }
  return link_handle;
}

//----- (0043D1E0) --------------------------------------------------------
int  WCIsvListBase_DestroyElementsAndDtor(WCIsvListBase *this, int a2)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromHandle(a2);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseDestroyElements_Vtable;
  if ( list->tail_link )
  {
    Noop_WCIsvListErrorHook(a2);
    WCIsvListBase_base_destroy(this);
  }
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseFreeOnly_Vtable;
  return WCIsvListBase_dtor(this);
}

//----- (0043D220) --------------------------------------------------------
signed int  WCIsvListBase_AppendValue(int a1, int a2)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  link = (WCCompatLink *)WCIsvListBase_AllocLinkNode(a1, a2);
  if ( link )
  {
    list = WCCompat_ListFromHandle(a1);
    WCIsvListBase_base_insert(a1, (int)(uintptr_t)link);
    list->tail_link = (int)(uintptr_t)link;
    return 1;
  }
  Noop_WCIsvListErrorHook(a1);
  return 0;
}

//----- (0043D250) --------------------------------------------------------
int  WCIsvListBase_PopFrontValue(int a1, int a2)
{
  int link_handle;
  WCCompatLink *link;

  link_handle = WCIsvListBase_base_sget(a1);
  if ( !link_handle )
    return a2;
  link = WCCompat_LinkFromHandle(link_handle);
  if ( !link )
    return a2;
  a2 = link->value;
  WCIsvListBase_ReleaseLinkNode(a1, link_handle, 8);
  return a2;
}

//----- (0043D280) --------------------------------------------------------
int  WCIsvListBase_CopyCtor(_DWORD *a1, _DWORD *a2)
{
  int v2; // ecx
  int result; // eax

  *a1 = 0;
  a1[1] = &g_WCIsvListBaseRoot_Vtable;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = 0;
  a1[5] = 0;
  a1[1] = &g_WCIsvListBaseDtor_Vtable;
  a1[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(a1, a2, (int)a1);
  result = v2;
  *(_DWORD *)(v2 + 4) = &g_WCIsvListBaseVariant134_Vtable;
  return result;
}
// 43D2BF: variable 'v2' is possibly undefined
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;

//----- (0043D2D0) --------------------------------------------------------
int  Battle_DeploySideUnitsByRoleBuckets(char *a1, int a2, char *a3, int a4, int a5)
{
  int v5; // esi
  int v6; // edi
  int v7; // ebp
  int v8; // ebx
  char *v9; // ecx
  int v13; // ebx
  char *v14; // ecx
  int v17; // eax
  unsigned __int8 v19; // al
  float v24; // [esp+10h] [ebp-24h]
  float v25; // [esp+14h] [ebp-20h]
  int v28; // [esp+20h] [ebp-14h]
  int v29; // [esp+24h] [ebp-10h]
  int v30; // [esp+24h] [ebp-10h]
  int deploy_result;

  Diagnostics_TraceWorldMapActionEvent("battle_deploy_enter", a2, a4, a5, *(__int16 *)a1);
  v5 = 0;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v28 = 0;
  if ( a2 > 0 )
  {
    v9 = a1;
    do
    {
      v6 += Unit_CalcEffectivenessA(v9, 0);
      Unit_CalcEffectivenessB(v9, 0);
      ++v8;
      v5 += Unit_CalcEffectivenessC((__int16 *)v9);
      v9 += UNIT_STACK_SLOT_STRIDE;
    }
    while ( v8 < a2 );
  }
  v13 = 0;
  if ( a5 > 0 )
  {
    v14 = a3;
    do
    {
      v7 += Unit_CalcEffectivenessA(v14, 0);
      Unit_CalcEffectivenessB(v14, 0);
      ++v13;
      v17 = Unit_CalcEffectivenessC((__int16 *)v14);
      v14 += UNIT_STACK_SLOT_STRIDE;
      v28 += v17;
    }
    while ( v13 < a5 );
  }
  if ( v7 <= 0 )
    v29 = v6;
  else
    v29 = v6 / v7;
  v25 = (float)v29;
  if ( v28 <= 0 )
    v30 = v5;
  else
    v30 = v5 / v28;
  v24 = (float)v30;
  v19 = v24 < g_Battle_RoleDeployRatioHighThreshold && (v24 <= g_Battle_RoleDeployRatioLowThreshold || SLODWORD(v25) > 1065353216);
  Battle_BuildRoleDeploymentBuckets((int)a1, a2, v19);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_build",
    a2,
    v19,
    Diagnostics_CountBattleDeploymentBucketEntries(),
    *(__int16 *)a1);
  deploy_result = Battle_PlaceRoleDeploymentBuckets(v19, a4);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_place",
    deploy_result,
    Diagnostics_CountBattleUnitsTotal(),
    Diagnostics_CountBattleUnitsForOwner(a1[2]),
    g_SelectedUnitIndex);
  return deploy_result;
}
// 43D2D0: could not find valid save-restore pair for ebx
// 4F18A7: using guessed type double dbl_4F18A7;
// 4F18AF: using guessed type double dbl_4F18AF;

//----- (0043D430) --------------------------------------------------------
int  Battle_BuildRoleDeploymentBuckets(int a1, int a2, unsigned __int8 a3)
{
  int result; // eax
  __int16 *v4; // ecx
  int v5; // edi
  int v6; // ebp
  int v7; // esi
  int v9; // [esp+4h] [ebp-20h]
  unsigned __int8 v10; // [esp+Ch] [ebp-18h]

  memset(g_BattleDeploymentBucketStorage_5437DC, 0, 0xC0);
  result = 0;
  v4 = (__int16 *)(uintptr_t)(unsigned int)a1;
  v5 = 0;
  if ( a2 > 0 )
  {
    v9 = 0;
    v6 = 0;
    v7 = 0;
    do
    {
      v10 = g_BattleRoleDeploymentBucketTable[7 * a3 + (unsigned __int8)g_UnitTypeRole[88 * *v4]];
      if ( (v10 - v10 % 10) / 10 == 1 )
        g_BattleDeploymentBucketRole1[++v6] = (int)v4;
      if ( (v10 - v10 % 10) / 10 == 2 )
        g_BattleDeploymentBucketRole2[++v7] = (int)v4;
      result = (v10 - v10 % 10) / 10;
      if ( result == 3 )
      {
        result = v9 * 4;
        g_BattleDeploymentBucketRole3[v9++] = (int)v4;
      }
      ++v5;
      v4 = (__int16 *)((char *)v4 + 31);
    }
    while ( v5 < a2 );
  }
  return result;
}
// 43D466: variable 'v4' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 543808: using guessed type int dword_543808[];
// 543838: using guessed type int dword_543838[];
// 54386C: using guessed type int dword_54386C[];

//----- (0043D560) --------------------------------------------------------
signed int  Battle_PlaceUnitAtNextOpenDeploymentTile(unsigned __int8 *a1, _DWORD *a2, int a3, int *a4)
{
  int v5; // ebp
  int v6; // edx
  int v7; // ecx
  int v8; // ebp
  char v9; // al
  signed int result; // eax
  int v11; // edx
  char v12; // al
  int v14; // [esp+8h] [ebp-18h]
  int v15; // [esp+Ch] [ebp-14h]

  while ( 1 )
  {
    while ( 1 )
    {
      v5 = a3 ? 2 - *a4 : *a4 + *(_DWORD *)(g_MapData + 804) - 3;
      v15 = *(_DWORD *)(g_MapData + 800) / 2 + *a2;
      if ( v15 < *(_DWORD *)(g_MapData + 800) )
        break;
      *a2 = 0;
      v6 = ++*a4 % 3;
      *a4 = v6;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)a1, v5, v15) )
    {
      v9 = a3 ? 2 : 6;
      result = Battle_PlaceUnit(a1, v5, v9, v15);
      if ( result )
        break;
    }
    while ( 1 )
    {
      v7 = a3 ? 2 - *a4 : *a4 + *(_DWORD *)(g_MapData + 804) - 3;
      v8 = *(_DWORD *)(g_MapData + 800) / 2 - *a2;
      v14 = v7;
      if ( v8 >= 0 )
        break;
      *a2 = 0;
      v11 = ++*a4 % 3;
      *a4 = v11;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)a1, v7, v8) )
    {
      v12 = a3 ? 2 : 6;
      result = Battle_PlaceUnit(a1, v14, v12, v8);
      if ( result )
      {
        ++*a2;
        return result;
      }
    }
    ++*a2;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0043D6E0) --------------------------------------------------------
int  Battle_PlaceRoleDeploymentBuckets(unsigned __int8 a1, int a2)
{
  int v2; // edi
  int v3; // ebx
  int v4; // esi
  int v5; // ecx
  int result; // eax
  int v7; // esi
  int v8; // edx
  char *v9; // ebp
  int v10; // eax
  unsigned int v11; // edx
  int v12; // ebp
  int v13; // [esp+0h] [ebp-44h] BYREF
  int v14; // [esp+4h] [ebp-40h] BYREF
  int v15; // [esp+8h] [ebp-3Ch]
  int v16; // [esp+Ch] [ebp-38h]
  int v17; // [esp+10h] [ebp-34h]
  int v18; // [esp+14h] [ebp-30h]
  int v19; // [esp+18h] [ebp-2Ch]
  int v20; // [esp+1Ch] [ebp-28h]
  int v21; // [esp+20h] [ebp-24h]
  int v22; // [esp+24h] [ebp-20h]
  int v23; // [esp+28h] [ebp-1Ch]
  int v24; // [esp+2Ch] [ebp-18h]
  unsigned __int8 v25; // [esp+30h] [ebp-14h]
  unsigned __int8 *candidate;
  unsigned __int8 *best_candidate;

  v25 = a1;
  v17 = a2;
  v13 = 0;
  v22 = 1;
  v16 = 48;
  do
  {
    v14 = 0;
    v21 = 0;
    v20 = 0;
    v13 = (v13 + 1) % 3;
    v18 = v16;
    v19 = v16;
    do
    {
      v2 = v18;
      v3 = 0;
      v4 = 0;
      v5 = 0;
      v23 = v19;
      do
      {
        result = v23;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + v23) )
        {
          v21 = 1;
          if ( !v3 )
          {
            v3 = v22;
            v4 = v5;
          }
          candidate = BattleDeploymentBucketReadPointer(v2);
          v8 = 7 * v25 + (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)candidate];
          v24 = 7 * v25;
          best_candidate = BattleDeploymentBucketReadPointer(48 * v3 + 4 * v4);
          v9 = (char *)best_candidate;
          v10 = 88 * *(__int16 *)v9;
          v15 = (unsigned __int8)g_BattleRoleDeploymentBucketTable[v8] % 10;
          v11 = (unsigned __int8)g_BattleRoleDeploymentBucketTable[(unsigned __int8)g_UnitTypeRole[v10] + v24];
          v24 = 10;
          result = v11 / 10LL;
          if ( v11 % 10LL <= v15 )
          {
            v12 = Unit_CalcEffectivenessA(v9, 0);
            result = Unit_CalcEffectivenessA((char *)candidate, 0);
            if ( v12 <= result )
            {
              v3 = v22;
              v4 = v5;
            }
          }
          else
          {
            v3 = v22;
            v4 = v5;
          }
        }
        v2 += 4;
        ++v5;
        v23 += 4;
      }
      while ( v5 < 12 );
      if ( v21 )
      {
        v7 = 48 * v3 + 4 * v4;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + v7) )
        {
          result = Battle_PlaceUnitAtNextOpenDeploymentTile(BattleDeploymentBucketReadPointer(v7), &v14, v17, &v13);
          *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + v7) = 0;
        }
      }
      ++v20;
    }
    while ( v20 < 12 );
    v16 += 48;
    ++v22;
  }
  while ( v22 < 4 );
  return result;
}
// 43D77B: variable 'v5' is possibly undefined
// 5437DC: using guessed type int dword_5437DC[];

//----- (0043D8C0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v1(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_GateDoorDialogExitFlag_V1 = v4;
  return result;
}
// 43D8CB: variable 'v4' is possibly undefined
// 5438A4: using guessed type int dword_5438A4;

//----- (0043D8E0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v1(int a1, int a2, DWORD a3)
{
  int v4; // esi
  int v5; // ecx
  char *v6; // edx
  int v7; // edi
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ecx
  char v11; // bl
  CHAR *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 v20[1040]; // [esp+0h] [ebp-410h] BYREF

  v4 = *(_DWORD *)(1423 * *(unsigned __int8 *)(a1 + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( v4 )
    v6 = aCastle_chrDw_3;
  else
    v6 = aCastle_pogDw_3;
  v7 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(v7 + 48))(0, v6, v5);
  v9 = (_DWORD *)Mem_Alloc(4112, v8, (char)v20, a3);
  v11 = (char)v9;
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, (char)v9);
  g_GateDoorDialogV1SpriteSet = (int)v9;
  if ( v4 )
    v12 = aCastle_chrDw_5;
  else
    v12 = aCastle_pogDw_5;
  Palette_LoadOrBuildBlendLookupTable(v12, (int)v20, v10, a3);
  Render_LoadResourceSprite_v4(10, v20, v13, v11, a3);
  Render_LoadResourceSprite_v4(8, v20, v14, v11, a3);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, a3);
  UI_DrawTextFmt(v7, 193, 439, 80, 3, (int)aS_6);
  Render_ReleaseSurface(10, a3);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V1);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, v20, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)v20, v17, a3);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V1 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V1, a3);
  }
  while ( !g_GateDoorDialogExitFlag_V1 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV1SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43D934: variable 'v5' is possibly undefined
// 43D93C: variable 'v8' is possibly undefined
// 43D971: variable 'v10' is possibly undefined
// 43D97F: variable 'v13' is possibly undefined
// 43D98D: variable 'v14' is possibly undefined
// 43D9EE: variable 'v15' is possibly undefined
// 43D9EE: variable 'v16' is possibly undefined
// 43DA31: variable 'v17' is possibly undefined
// 43DA53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515A90: using guessed type _DWORD dword_515A90[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438A0: using guessed type int dword_5438A0;
// 5438A4: using guessed type int dword_5438A4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DAC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v2(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_GateDoorDialogExitFlag_V2 = v4;
  return result;
}
// 43DACB: variable 'v4' is possibly undefined
// 5438B0: using guessed type int dword_5438B0;

//----- (0043DAE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v2(int a1, int a2, DWORD a3)
{
  int v4; // esi
  int v5; // ecx
  char *v6; // edx
  int v7; // edi
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ecx
  char v11; // bl
  CHAR *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 v20[1040]; // [esp+0h] [ebp-410h] BYREF

  v4 = *(_DWORD *)(1423 * *(unsigned __int8 *)(a1 + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( v4 )
    v6 = aCastle_chrDw_6;
  else
    v6 = aCastle_pogDw_6;
  v7 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(v7 + 48))(0, v6, v5);
  v9 = (_DWORD *)Mem_Alloc(4112, v8, (char)v20, a3);
  v11 = (char)v9;
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, (char)v9);
  g_GateDoorDialogV2SpriteSet = (int)v9;
  if ( v4 )
    v12 = aCastle_chrDw_8;
  else
    v12 = aCastle_pogDw_8;
  Palette_LoadOrBuildBlendLookupTable(v12, (int)v20, v10, a3);
  Render_LoadResourceSprite_v4(10, v20, v13, v11, a3);
  Render_LoadResourceSprite_v4(8, v20, v14, v11, a3);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, a3);
  UI_DrawTextFmt(v7, 193, 439, 80, 3, (int)aS_7);
  Render_ReleaseSurface(10, a3);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V2);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, v20, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)v20, v17, a3);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V2 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V2, a3);
  }
  while ( !g_GateDoorDialogExitFlag_V2 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV2SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DB34: variable 'v5' is possibly undefined
// 43DB3C: variable 'v8' is possibly undefined
// 43DB71: variable 'v10' is possibly undefined
// 43DB7F: variable 'v13' is possibly undefined
// 43DB8D: variable 'v14' is possibly undefined
// 43DBEE: variable 'v15' is possibly undefined
// 43DBEE: variable 'v16' is possibly undefined
// 43DC31: variable 'v17' is possibly undefined
// 43DC53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515B10: using guessed type _DWORD dword_515B10[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438AC: using guessed type int dword_5438AC;
// 5438B0: using guessed type int dword_5438B0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DCC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v3(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_GateDoorDialogExitFlag_V3 = v4;
  return result;
}
// 43DCCB: variable 'v4' is possibly undefined
// 5438BC: using guessed type int dword_5438BC;

//----- (0043DCE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v3(int a1, int a2, DWORD a3)
{
  int v4; // esi
  int v5; // ecx
  char *v6; // edx
  int v7; // edi
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ecx
  char v11; // bl
  CHAR *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 v20[1040]; // [esp+0h] [ebp-410h] BYREF

  v4 = *(_DWORD *)(1423 * *(unsigned __int8 *)(a1 + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( v4 )
    v6 = aCastle_chrDw_9;
  else
    v6 = aCastle_pogDw_9;
  v7 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(v7 + 48))(0, v6, v5);
  v9 = (_DWORD *)Mem_Alloc(4112, v8, (char)v20, a3);
  v11 = (char)v9;
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, (char)v9);
  g_GateDoorDialogV3SpriteSet = (int)v9;
  if ( v4 )
    v12 = aCastle_chrD_11;
  else
    v12 = aCastle_pogD_11;
  Palette_LoadOrBuildBlendLookupTable(v12, (int)v20, v10, a3);
  Render_LoadResourceSprite_v4(10, v20, v13, v11, a3);
  Render_LoadResourceSprite_v4(8, v20, v14, v11, a3);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, a3);
  UI_DrawTextFmt(v7, 193, 439, 80, 3, (int)aS_8);
  Render_ReleaseSurface(10, a3);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V3);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, v20, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)v20, v17, a3);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V3 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V3, a3);
  }
  while ( !g_GateDoorDialogExitFlag_V3 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV3SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DD34: variable 'v5' is possibly undefined
// 43DD3C: variable 'v8' is possibly undefined
// 43DD71: variable 'v10' is possibly undefined
// 43DD7F: variable 'v13' is possibly undefined
// 43DD8D: variable 'v14' is possibly undefined
// 43DDEE: variable 'v15' is possibly undefined
// 43DDEE: variable 'v16' is possibly undefined
// 43DE31: variable 'v17' is possibly undefined
// 43DE53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515B90: using guessed type _DWORD dword_515B90[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438B8: using guessed type int dword_5438B8;
// 5438BC: using guessed type int dword_5438BC;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DEC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v4(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_GateDoorDialogExitFlag_V4 = v4;
  return result;
}
// 43DECB: variable 'v4' is possibly undefined
// 5438C8: using guessed type int dword_5438C8;

//----- (0043DEE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v4(int a1, int a2, DWORD a3)
{
  int v4; // esi
  int v5; // ecx
  char *v6; // edx
  int v7; // edi
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ecx
  char v11; // bl
  CHAR *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 v20[1040]; // [esp+0h] [ebp-410h] BYREF

  v4 = *(_DWORD *)(1423 * *(unsigned __int8 *)(a1 + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( v4 )
    v6 = aCastle_chrD_12;
  else
    v6 = aCastle_pogD_12;
  v7 = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(v7 + 48))(0, v6, v5);
  v9 = (_DWORD *)Mem_Alloc(4112, v8, (char)v20, a3);
  v11 = (char)v9;
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, (char)v9);
  g_GateDoorDialogV4SpriteSet = (int)v9;
  if ( v4 )
    v12 = aCastle_chrD_14;
  else
    v12 = aCastle_pogD_14;
  Palette_LoadOrBuildBlendLookupTable(v12, (int)v20, v10, a3);
  Render_LoadResourceSprite_v4(10, v20, v13, v11, a3);
  Render_LoadResourceSprite_v4(8, v20, v14, v11, a3);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, a3);
  UI_DrawTextFmt(v7, 193, 439, 80, 3, (int)aS_9);
  Render_ReleaseSurface(10, a3);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V4);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, v20, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)v20, v17, a3);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V4 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V4, a3);
  }
  while ( !g_GateDoorDialogExitFlag_V4 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV4SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DF34: variable 'v5' is possibly undefined
// 43DF3C: variable 'v8' is possibly undefined
// 43DF71: variable 'v10' is possibly undefined
// 43DF7F: variable 'v13' is possibly undefined
// 43DF8D: variable 'v14' is possibly undefined
// 43DFEE: variable 'v15' is possibly undefined
// 43DFEE: variable 'v16' is possibly undefined
// 43E031: variable 'v17' is possibly undefined
// 43E053: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515C10: using guessed type _DWORD dword_515C10[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438C4: using guessed type int dword_5438C4;
// 5438C8: using guessed type int dword_5438C8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043E0C0) --------------------------------------------------------
BOOL  Building_HasFreeAdjacentExitTile(unsigned __int8 *a1)
{
  int *v2; // esi
  int i; // ebp
  int v4; // ebx
  int v5; // ecx

  if ( a1[4] )
    v2 = (int *)&g_LargeBuildingNeighborOffsets;
  else
    v2 = Map_NeighborDX;
  for ( i = 0; i < 12; ++i )
  {
    v4 = *v2 + *a1;
    v5 = v2[1] + a1[1];
    if ( v4 >= 0
      && v4 < *(_DWORD *)(gameData + 140000)
      && v5 >= 0
      && v5 < *(_DWORD *)(gameData + 140004)
      && *(unsigned __int16 *)(TILE_INDEX(v4, v5)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(a1[2], 0, v5, v4) )
    {
      break;
    }
    v2 += 2;
  }
  return i != 12;
}
// 513334: using guessed type int dword_513334[];
// 5202E4: using guessed type int gameData;

//----- (0043E160) --------------------------------------------------------
signed int  Building_UnitsLeave(unsigned __int8 *a1, int *a2, double a3)
{
  int *v4; // esi
  int i; // edi
  int v6; // ebx
  int v7; // ecx
  int *v8; // edx
  int v9; // edi
  int v10; // esi
  char v11; // al
  int *v12; // eax
  int v13; // edx
  __int16 *v14; // ebx
  unsigned __int8 *v15; // esi
  int v16; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  double v21; // st7
  double v22; // st7
  int v23; // ecx
  int *v25; // [esp+0h] [ebp-20h]
  __int16 *v27; // [esp+8h] [ebp-18h]

  Debug_Log(a2[3], a2[2], (DWORD)a1, (int)aBuildingUnitsLeave);
  if ( a1[4] )
    v25 = (int *)&g_LargeBuildingNeighborOffsets;
  else
    v25 = Map_NeighborDX;
  v4 = v25;
  for ( i = 0; i < 12; ++i )
  {
    v6 = *v4 + *a1;
    v7 = v4[1] + a1[1];
    if ( v6 >= 0
      && v6 < *(_DWORD *)(gameData + 140000)
      && v7 >= 0
      && v7 < *(_DWORD *)(gameData + 140004)
      && *(unsigned __int16 *)(TILE_INDEX(v6, v7)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(a1[2], 0, v7, v6) )
    {
      break;
    }
    v4 += 2;
  }
  if ( i == 12 )
    return -1;
  v8 = &v25[2 * i];
  v9 = a1[1] + v8[1];
  v10 = *a1 + *v8;
  v11 = Facing_DirectionFromDelta8(*v8, v8[1]);
  Diagnostics_TraceWorldMapActionEvent("building_units_leave_request", -1, *a1, a1[1], a2[0]);
  Unit_Create(0xFFFFFFFF, a1[2], v10, v11, v9);
  v12 = a2;
  v13 = 0;
  v27 = (__int16 *)(725 * *(unsigned __int16 *)(TILE_INDEX(v10, v9)) + gameData + 147174);
  Diagnostics_TraceWorldMapActionEvent(
    "building_units_leave_spawn",
    *(unsigned __int16 *)(TILE_INDEX(v10, v9)),
    v10,
    v9,
    a2[0]);
  v14 = v27 + 3;
  if ( *a2 != -1 )
  {
    do
    {
      v15 = &a1[31 * *v12 + 18];
      qmemcpy(v14, v15, 0x1Cu);
      v15 += 28;
      v14[14] = *(_WORD *)v15;
      *((_BYTE *)v14 + 30) = v15[2];
      *(_WORD *)&a1[31 * *v12 + 18] = -1;
      BUILDING_GARRISON_SERVICE_STATE(a1, *v12) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
      v16 = *v12++;
      ++v13;
      v14 = (__int16 *)((char *)v14 + 31);
      BUILDING_GARRISON_SERVICE_STATE(a1, v16) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
    }
    while ( v13 < 10 && *v12 != -1 );
  }
  UnitStack_ClearRemainingActionPoints(v27, (DWORD)a1, a3);
  Rules_LinkArmyFact(v27, v17, v18, a3, (char)v14, (DWORD)a1);
  Rules_SyncArmyFactStrength(v27, 0, v19, (char)v14, (DWORD)a1, a3);
  Building_OnGarrisonChange(*(unsigned __int16 *)(TILE_INDEX(*a1, a1[1])) - 0x8000, v20, v21);
  UnitStack_UpdateVision(*(unsigned __int16 *)(TILE_INDEX(*v27, v27[1])));
  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(*(unsigned __int16 *)(TILE_INDEX(*v27, v27[1])), v22);
  Debug_Log(v23, (char)v14, (DWORD)a1, (int)aBuildings_unit);
  Unit_DebugDumpFormationSizes((int)v27, (DWORD)a1);
  return *(unsigned __int16 *)(TILE_INDEX(*v27, v27[1]));
}
// 43E33C: variable 'v17' is possibly undefined
// 43E33C: variable 'v18' is possibly undefined
// 43E347: variable 'v19' is possibly undefined
// 43E38B: variable 'v20' is possibly undefined
// 43E38B: variable 'v21' is possibly undefined
// 43E40B: variable 'v22' is possibly undefined
// 43E42B: variable 'v23' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 5202E4: using guessed type int gameData;

//----- (0043E4B0) --------------------------------------------------------
int  Building_CountFreeGarrisonSlots(int a1)
{
  int v1; // esi
  int v2; // ebx
  int v3; // eax
  int i; // edx
  int v5; // ecx

  v1 = UNIT_RECORD(a1);
  v2 = 0;
  v3 = v1;
  for ( i = 0; ; ++i )
  {
    v5 = *(_BYTE *)(v1 + 4) ? 12 : 10;
    if ( i >= v5 )
      break;
    if ( *(__int16 *)(v3 + 18) == -1 )
      ++v2;
    v3 += 31;
  }
  return v2;
}
// 5202E4: using guessed type int gameData;

//----- (0043E500) --------------------------------------------------------
signed int  Building_UnitGetInto(
        int a1,
        int a2,
        char a3,
        signed int i,
        double a5)
{
  int stack_record;
  int building_record;
  int slot_index;
  int source_slot;
  int target_slot;
  int squad_count;
  int peasant_count;
  __int16 *stack;

  (void)a3;
  (void)i;

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-enter");
  Debug_Log(a1, a2, (DWORD)a1, (int)aBuilding_unitg);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-log");
  Render_DrawSprite_v3(a1, a1);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-dump");

  stack_record = UNIT_STACK(a1);
  building_record = BUILDING_RECORD(a2);
  stack = (__int16 *)stack_record;

  if ( *(_DWORD *)(stack_record + UNIT_STACK_PATH_OFFSET) )
    *(_DWORD *)(stack_record + UNIT_STACK_PATH_OFFSET) = 0;
  if ( UnitStack_HasPlague(stack_record) && (*(_BYTE *)(building_record + 435) & 7) == 0 )
    *(_BYTE *)(building_record + 435) = (*(_BYTE *)(building_record + 435) & 0xF8) | 6;

  if ( *(_BYTE *)(building_record + 4) )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      int slot = UNIT_STACK_SLOT(stack_record, slot_index);
      if ( *(__int16 *)slot == UNIT_TYPE_GOLD_CARGO )
      {
        *(_DWORD *)(building_record + 438) += 100 * *(char *)(slot + 9) / 100;
        *(__int16 *)slot = -1;
      }
    }
  }
  if ( *(_BYTE *)(building_record + 4) == 2 )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      int slot = UNIT_STACK_SLOT(stack_record, slot_index);
      if ( *(__int16 *)slot == UNIT_TYPE_PEASANT_CARGO )
      {
        peasant_count = (*(_WORD *)(building_record + 430) & 0x0FFF) + 100 * *(char *)(slot + 9) / 100;
        *(_WORD *)(building_record + 430) =
          (*(_WORD *)(building_record + 430) & 0xF000) | (peasant_count & 0x0FFF);
        *(__int16 *)slot = -1;
      }
    }
  }

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-compact-1");
  Unit_CompactSquad(stack, 0, a5);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-compact-1");
  squad_count = Unit_GetSquadCount(stack_record);
  if ( !squad_count )
  {
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-unlink-empty");
    Rules_UnlinkArmyFact(stack, a5);
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-unlink-empty");
    return 1;
  }

  if ( squad_count <= Building_CountFreeGarrisonSlots(a2) )
  {
    for ( source_slot = 0; source_slot < UNIT_STACK_SLOT_COUNT; ++source_slot )
    {
      int source = UNIT_STACK_SLOT(stack_record, source_slot);
      if ( *(__int16 *)source == -1 )
        break;
      for ( target_slot = 0; target_slot < 12; ++target_slot )
      {
        int target = building_record + 18 + UNIT_STACK_SLOT_STRIDE * target_slot;
        if ( *(__int16 *)target == -1 )
        {
          qmemcpy((void *)target, (const void *)source, UNIT_STACK_SLOT_STRIDE);
          *(__int16 *)source = -1;
          break;
        }
      }
    }
  }

  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-compact-2");
  Unit_CompactSquad(stack, 0, a5);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-finalize");
  Rules_LinkArmyFinalize(stack, a5);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-fact");
  Rules_LinkArmyFact(stack, 0, 0, a5, 0, (DWORD)stack_record);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-sync-strength");
  Rules_SyncArmyFactStrength(stack, 0, 0, 0, (DWORD)stack_record, a5);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-garrison-change");
  if ( *(_DWORD *)(building_record + 463) )
    Building_OnGarrisonChange(a2, 0, a5);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-done");
  return 1;
}
// 43E521: variable 'v5' is possibly undefined
// 43E543: variable 'v6' is possibly undefined
// 43E68A: variable 'v16' is possibly undefined
// 43E6E0: variable 'v15' is possibly undefined
// 43E6F2: variable 'v20' is possibly undefined
// 43E6F2: variable 'v21' is possibly undefined
// 43E6FB: variable 'v22' is possibly undefined
// 43E6FB: variable 'v23' is possibly undefined
// 43E70D: variable 'v24' is possibly undefined
// 43E70D: variable 'v25' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043E770) --------------------------------------------------------
signed int  Building_CanAcceptUnitStack(int a1, int a2)
{
  int v2; // ecx
  int v3; // edx
  unsigned __int8 v4; // al
  int v5; // edx
  int v6; // edx

  v2 = UNIT_RECORD(a2);
  v3 = 725 * a1 + gameData + 147174;
  if ( *(_WORD *)(v2 + 16) )
    return 0;
  v4 = *(_BYTE *)(v2 + 4);
  if ( !v4 )
    return UnitStack_HasNormalCombatUnits(v3);
  if ( v4 > 1u )
    return v4 == 2;
  if ( UnitStack_HasPeasantCargo(v3) )
    return 0;
  return UnitStack_HasNormalCombatUnits(v5) || UnitStack_HasGoldCargo(v5) || UnitStack_HasSpecialPersonageUnits(v6);
}
// 43E7D7: variable 'v5' is possibly undefined
// 43E7F5: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043E820) --------------------------------------------------------
signed int  Building_HasUnitLicence(int a1, unit_type a2)
{
  int v2; // esi
  int v3; // ecx

  v2 = a1 + 12;
  v3 = 0;
  do
  {
    if ( *(char *)(a1 + 402) == a2 )
      v3 = 1;
    ++a1;
  }
  while ( a1 != v2 );
  return v3;
}

//----- (0043E850) --------------------------------------------------------
BOOL  Building_BuyUnitLicence(int a1, unit_type a2, int a3, DWORD a4)
{
  int v5; // edx
  BOOL result; // eax
  int v7; // eax
  unsigned int v8; // esi
  int v9; // edx
  int v10; // eax

  Debug_Log(a3, a1, a4, (int)aBuildingBuyUnitLicence);
  if ( Building_HasUnitLicence(a1, a2) )
    return 0;
  result = Building_IsUnitLicenceEligible((char *)a1, a2);
  if ( result )
  {
    v7 = gameData + 1423 * *(unsigned __int8 *)(a1 + 2);
    v8 = (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * a2];
    if ( !*(_DWORD *)(v7 + 140051) && *(int *)(v7 + 140055) >= 2 )
      v8 = (int)(75 * v8) / 100;
    if ( v8 > *(_DWORD *)(a1 + 438) )
      return 0;
    v9 = a1;
    v10 = 0;
    while ( *(char *)(v9 + 402) != -1 )
    {
      ++v10;
      ++v9;
      if ( v10 >= 12 )
      {
        if ( v10 == 12 )
          return 0;
        break;
      }
    }
    *(_DWORD *)(a1 + 438) -= v8;
    *(_BYTE *)(a1 + v10 + 402) = a2;
    return 1;
  }
  return result;
}
// 43E8D7: conditional instruction was optimized away because eax.4<C
// 43E86D: variable 'v5' is possibly undefined
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];
// 5202E4: using guessed type int gameData;

//----- (0043E940) --------------------------------------------------------
int  Building_RemoveUnitLicence(int a1, unit_type a2, DWORD a3)
{
  int activeProductionLicenceSlot; // eax
  int addonSlot; // edx

  Debug_Log(a1, a2, a3, (int)aBuildingRemoveUnitLicence);
  activeProductionLicenceSlot = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(a1);
  if ( activeProductionLicenceSlot != -1 && *(signed __int8 *)(a1 + activeProductionLicenceSlot + 402) == a2 )
    Building_StopUnitProduction(a1, a2, a3);
  for ( addonSlot = 0; addonSlot < 12; ++addonSlot )
  {
    if ( *(signed __int8 *)(a1 + addonSlot + 402) == a2 )
    {
      *(_BYTE *)(a1 + addonSlot + 402) = -1;
      return a1 + addonSlot;
    }
  }
  return a1 + 12;
}

//----- (0043E9A0) --------------------------------------------------------
int  Building_SetUnitProduction(int a1, char a2, DWORD a3)
{
  unsigned __int8 *v3; // ecx
  int v4; // edx
  int result; // eax

  v3 = (unsigned __int8 *)a1;
  v4 = (unsigned __int8)a2;
  Debug_Log(a1, a2, a3, (int)aBuildingSetUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(v3) = v4;
  result = 1423 * v3[2];
  BUILDING_PRODUCTION_TURNS_REMAINING(v3) = g_UnitTypeProductionTime[88 * (char)v3[v4 + 402]];
  if ( !*(_DWORD *)(result + gameData + 140051)
    && *(int *)(result + gameData + 140055) >= 1
    && (char)BUILDING_PRODUCTION_TURNS_REMAINING(v3) > 1 )
  {
    --BUILDING_PRODUCTION_TURNS_REMAINING(v3);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EA10) --------------------------------------------------------
void  Building_StopUnitProduction(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aBuildingStopUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(a1) = -1;
}

//----- (0043EA30) --------------------------------------------------------
_BYTE * Building_TrainUnit(int a1, char a2, DWORD a3)
{
  int v3; // edx
  int v4; // ecx
  _BYTE *result; // eax
  char v6; // bl
  char v7; // bh

  v3 = (unsigned __int8)a2;
  v4 = a1;
  Debug_Log(a1, a2, a3, (int)aBuildingTrainUnit);
  result = (_BYTE *)(*(_BYTE *)(v4 + 31 * v3 + 30) & 3);
  if ( result != (_BYTE *)3 )
  {
    result = (_BYTE *)(v4 + BUILDING_GARRISON_SERVICE_STATE_OFFSET + v3);
    if ( *(_DWORD *)(1423 * *(unsigned __int8 *)(v4 + 2) + gameData + 140051) )
      v6 = (*(_BYTE *)(v4 + 4) == 2) + 1;
    else
      v6 = (*(_BYTE *)(v4 + 4) == 2) + 4;
    v7 = *result & 0xF8;
    *result = v7;
    *result = v6 & BUILDING_GARRISON_TRAINING_TURNS_MASK | v7;
    BUILDING_GARRISON_SERVICE_STATE(v4, v3) &= 0xC7u;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EAC0) --------------------------------------------------------
int  Building_ClearGarrisonTrainingTimer(int result, int a2)
{
  BUILDING_GARRISON_SERVICE_STATE(a2, result) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
  return result;
}

//----- (0043EAD0) --------------------------------------------------------
__int16  Building_RepairUnit(int a1, int a2, DWORD a3)
{
  int v6; // eax
  unsigned __int8 *repairTimer; // edx
  unsigned __int8 repairTurns; // al

  Debug_Log(a1, a2, a3, (int)aBuildingRepairUnit);
  v6 = *(signed __int8 *)(a1 + 31 * a2 + 27);
  if ( v6 != 100 )
  {
    repairTimer = (unsigned __int8 *)(a1 + BUILDING_GARRISON_SERVICE_STATE_OFFSET + a2);
    repairTurns = (*(_BYTE *)(a1 + 4) == 2) + 2;
    *repairTimer = *repairTimer & 0xC0 | ((repairTurns & 7) << 3);
  }
  return v6;
}

//----- (0043EB40) --------------------------------------------------------
int  Building_ClearGarrisonRepairTimer(int result, int a2)
{
  BUILDING_GARRISON_SERVICE_STATE(a2, result) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
  return result;
}

//----- (0043EB50) --------------------------------------------------------
int  Building_CountGarrison(int a1)
{
  int v1; // ebx
  int v2; // edx

  v1 = a1 + 372;
  v2 = 0;
  do
  {
    if ( *(__int16 *)(a1 + 18) != -1 )
      ++v2;
    a1 += 31;
  }
  while ( a1 != v1 );
  return v2;
}

//----- (0043EB80) --------------------------------------------------------
int  Building_CountSpecialPersonageGarrisonEntries(int a1)
{
  int v1; // ebx
  int v2; // ecx
  int v3; // edx

  v1 = a1 + 372;
  v2 = 0;
  do
  {
    while ( 1 )
    {
      v3 = *(__int16 *)(a1 + 18);
      if ( v3 != -1 )
        break;
LABEL_5:
      a1 += 31;
      if ( a1 == v1 )
        return v2;
    }
    if ( v3 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v3 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      ++v2;
      goto LABEL_5;
    }
    a1 += 31;
  }
  while ( a1 != v1 );
  return v2;
}

int  Building_DrawGarrisonRow(int a1)
{
  return Building_CountSpecialPersonageGarrisonEntries(a1);
}

//----- (0043EBC0) --------------------------------------------------------
int  Building_CountNonCombatGarrisonEntries(int a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // eax

  v1 = a1;
  v2 = 0;
  v3 = a1 + 372;
  do
  {
    while ( 1 )
    {
      v4 = *(__int16 *)(v1 + 18);
      if ( v4 != -1 )
        break;
LABEL_5:
      v1 += 31;
      if ( v1 == v3 )
        return v2;
    }
    if ( v4 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || v4 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE
      || v4 == UNIT_TYPE_GOLD_CARGO
      || v4 == UNIT_TYPE_PEASANT_CARGO )
    {
      ++v2;
      goto LABEL_5;
    }
    v1 += 31;
  }
  while ( v1 != v3 );
  return v2;
}

//----- (0043EC10) --------------------------------------------------------
signed int  Building_HasSpecialPersonageGarrisonEntries(int a1)
{
  int v1; // edx
  int v2; // ecx

  v1 = 0;
  while ( 1 )
  {
    v2 = *(__int16 *)(a1 + 18);
    if ( v2 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v2 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++v1;
    a1 += 31;
    if ( v1 >= 12 )
      return 0;
  }
  return 1;
}

//----- (0043EC40) --------------------------------------------------------
int  Building_CompactGarrison(unsigned __int8 *a1, unsigned __int8 *a2, double a3)
{
  int v3; // ebp
  int v4; // edx
  unsigned __int8 *v5; // eax
  unsigned __int8 *j; // ebx
  _BYTE *v7; // edi
  _BYTE *v8; // esi
  int i; // [esp+4h] [ebp-20h]
  unsigned __int8 *v12; // [esp+8h] [ebp-1Ch]

  v3 = 0;
  v12 = a1;
  for ( i = 0; i < 11; ++i )
  {
    if ( *((__int16 *)v12 + 9) == -1 )
    {
      v4 = v3;
      v5 = &a1[31 * v3];
      for ( j = &a1[31 * v3 + 31]; v4 < 11; v7[2] = v8[2] )
      {
        v7 = v5 + 18;
        v5 += 31;
        v8 = j + 18;
        j += 31;
        ++v4;
        qmemcpy(v7, v8, 0x1Cu);
        v8 += 28;
        v7 += 28;
        a2 = 0;
        *(_WORD *)v7 = *(_WORD *)v8;
      }
      *((_WORD *)v5 + 9) = -1;
    }
    else
    {
      a2 = v12 + 31;
      ++v3;
      v12 += 31;
    }
  }
  return Building_OnGarrisonChange(
           *(unsigned __int16 *)(TILE_INDEX(*a1, a1[1])) - 0x8000,
           (int)a2,
           a3);
}
// 5202E4: using guessed type int gameData;

//----- (0043ED20) --------------------------------------------------------
BOOL  Building_IsUnitLicenceEligible(char *a1, unit_type a2)
{
  int v4; // eax
  int v5; // edx
  char v6; // al
  int i; // eax
  int v8; // edx
  int j; // eax
  int v11; // edx

  v4 = a1[4];
  if ( !v4 )
    return 0;
  v5 = 88 * a2;
  v6 = v4 == 2
     ? g_UnitTypeProductionRequiredTechLevelMode2[v5]
     : g_UnitTypeProductionRequiredTechLevelOtherModes[v5];
  if ( (unsigned __int8)(a1[444] & 7) < (unsigned __int8)v6 )
    return 0;
  if ( (a1[416] & 0x10) == 0 )
  {
    for ( i = 0; ; ++i )
    {
      v8 = g_ProductionLicenceSmithsRequiredUnitTypes[i];
      if ( v8 == -1 || v8 == a2 )
        break;
    }
    if ( g_ProductionLicenceSmithsRequiredUnitTypes[i] == a2 )
      return 0;
  }
  if ( (a1[416] & 4) != 0 )
    return 1;
  for ( j = 0; ; ++j )
  {
    v11 = g_ProductionLicenceWorkshopRequiredUnitTypes[j];
    if ( v11 == -1 || v11 == a2 )
      break;
  }
  return g_ProductionLicenceWorkshopRequiredUnitTypes[j] != a2;
}

//----- (0043EDC0) --------------------------------------------------------
int  Building_AdjustAllGarrisonMoraleByDelta(int a1, int a2)
{
  int slot; // ebp
  int slot_index; // ecx
  int result; // eax

  slot = a1 + 18;
  result = 0;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)slot != -1 )
      result = UnitSlot_AdjustMoraleByPredicate(slot, a2, UnitSlot_PredicateAlways);
    slot += 31;
  }
  return result;
}

//----- (0043EE10) --------------------------------------------------------
int  Building_CycleAllGarrisonOrdersOnce(int a1)
{
  int v1; // esi
  int v2; // edx
  int v3; // ecx
  int result; // eax
  int v5; // edx
  int v6; // ecx

  v1 = a1 + 18;
  v2 = 0;
  v3 = a1;
  do
  {
    while ( 1 )
    {
      result = 31 * v2;
      if ( *(__int16 *)(v3 + 18) != -1 )
        break;
      ++v2;
      v3 += 31;
      if ( v2 >= 12 )
        return result;
    }
    result = UnitSlot_CycleOrderState(v1 + result);
    v2 = v5 + 1;
    v3 = v6 + 31;
  }
  while ( v2 < 12 );
  return result;
}
// 43EE41: variable 'v5' is possibly undefined
// 43EE42: variable 'v6' is possibly undefined

//----- (0043EE50) --------------------------------------------------------
signed int  Building_GetTaxBurdenTier(int a1)
{
  unsigned __int16 v2; // ax
  int v3; // edx
  int v4; // edx
  signed int result; // eax

  v2 = *(_WORD *)(a1 + 430);
  HIBYTE(v2) &= 0xFu;
  if ( v2 >= 0x1F4u )
  {
    if ( v2 >= 0x3E8u )
      v3 = 2;
    else
      v3 = 1;
  }
  else
  {
    v3 = 0;
  }
  v4 = 4 * v3;
  result = 0;
  while ( (unsigned __int8)(*(_BYTE *)(a1 + 436) & 0x3F) > (unsigned __int8)g_SettlementTaxBurdenThresholds[v4] )
  {
    ++result;
    ++v4;
    if ( result > 3 )
      return 3;
  }
  return result;
}
// 43EE8A: conditional instruction was optimized away because eax.4<4

//----- (0043EED0) --------------------------------------------------------
__int16  Building_UpdatePopulationGrowth(int a1)
{
  uintptr_t building; // ecx
  int previous_growth; // edx/eax
  int satisfaction; // eax
  int growth_percent; // edx
  int peasant_count; // eax
  int new_growth; // eax/ebx
  unsigned __int16 growth_flags; // dx
  unsigned __int16 population_flags; // si
  int updated_population; // eax

  building = (uintptr_t)(unsigned int)a1;
  previous_growth = (__int16)(16 * *(_WORD *)(building + 432)) >> 4;
  if ( previous_growth <= 0 )
    satisfaction = previous_growth / 2;
  else
    satisfaction = previous_growth / 3;
  satisfaction += *(char *)(building + 434);
  if ( satisfaction > 100 )
    satisfaction = 100;
  if ( satisfaction < 0 )
    satisfaction = 0;
  *(_BYTE *)(building + 434) = satisfaction;

  growth_percent = (int)Rng_RandRange(3, 5);
  switch ( (unsigned __int8)Building_GetTaxBurdenTier((int)building) )
  {
    case 0u:
      growth_percent += 5;
      break;
    case 2u:
      growth_percent -= 4;
      break;
    case 3u:
      growth_percent -= (int)Rng_RandRange(10, 15);
      break;
    default:
      break;
  }
  if ( (*(_BYTE *)(building + 416) & 1) != 0 )
    growth_percent += 3;
  if ( (*(_BYTE *)(building + 416) & 8) != 0 )
    ++growth_percent;
  if ( (*(_BYTE *)(building + 444) & 7u) > 1 )
    growth_percent += (*(_BYTE *)(building + 444) & 7) - 1;
  satisfaction = *(char *)(building + 434);
  if ( satisfaction > 75 )
  {
    ++growth_percent;
  }
  else if ( satisfaction < 30 )
  {
    growth_percent -= 2;
  }

  peasant_count = *(_WORD *)(building + 430) & 0x0FFF;
  new_growth = peasant_count * growth_percent / 100;
  growth_flags = *(_WORD *)(building + 432) & 0xF000;
  new_growth &= 0x0FFF;
  population_flags = *(_WORD *)(building + 430) & 0xF000;
  *(_WORD *)(building + 432) = growth_flags | new_growth;

  updated_population = peasant_count + ((__int16)(16 * (growth_flags | new_growth)) >> 4);
  updated_population &= 0x0FFF;
  *(_WORD *)(building + 430) = population_flags | updated_population;
  if ( updated_population > 2000 )
  {
    updated_population = 2000 - (int)Rng_RandRange(0, 100);
    updated_population &= 0x0FFF;
    *(_WORD *)(building + 430) = population_flags | updated_population;
  }
  return updated_population;
}

//----- (0043F0C0) --------------------------------------------------------
int  Building_CollectGoldIncome(int a1)
{
  int v2; // ecx
  unsigned __int16 v3; // ax
  int v4; // ecx
  int result; // eax
  int v6; // esi

  if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(a1 + 2) + 140051) )
    v2 = 400;
  else
    v2 = 200;
  v3 = *(_WORD *)(a1 + 430);
  HIBYTE(v3) &= 0xFu;
  v4 = (*(_BYTE *)(a1 + 436) & 0x3F) * v3 / v2;
  result = *(char *)(a1 + 434);
  if ( result < 25 )
  {
    result = v4 / 2;
    v4 /= 2;
  }
  if ( (*(_BYTE *)(a1 + 435) & 7) != 0 )
    v4 = 0;
  v6 = *(_DWORD *)(a1 + 438);
  *(_WORD *)(a1 + 442) = v4;
  *(_DWORD *)(a1 + 438) = v4 + v6;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043F160) --------------------------------------------------------
__int16  Building_UpdatePlagueState(unsigned int a1)
{
  uintptr_t building; // ecx
  unsigned int plague_state; // eax
  unsigned int population; // ebx
  unsigned int plague_roll; // eax
  unsigned __int16 population_flags; // dx
  unsigned int result; // eax
  unsigned char building_state; // dl

  building = (uintptr_t)a1;
  plague_state = *(_BYTE *)(building + 435) & 7;
  if ( plague_state )
  {
    building_state = *(_BYTE *)(building + 435) & 0xF8;
    *(_BYTE *)(building + 435) = building_state | ((plague_state - 1) & 7);
    population = *(_WORD *)(building + 430) & 0x0FFF;
    plague_roll = Rng_RandRange(15, 25);
    population -= population * plague_roll / 100;
    population_flags = *(_WORD *)(building + 430) & 0xF000;
    *(_WORD *)(building + 430) = population_flags | (population & 0x0FFF);
    return population;
  }

  result = *(_WORD *)(building + 430) & 0x0FFF;
  if ( result >= 1000 )
  {
    result = Rng_RandRange(0, 2000 - result + 300);
    if ( result < 100 )
    {
      building_state = *(_BYTE *)(building + 435) & 0xF8;
      *(_BYTE *)(building + 435) = building_state | 5;
    }
  }
  return result;
}

//----- (0043F240) --------------------------------------------------------
int  Building_GetTotalValue(int a1)
{
  int v2; // ecx
  unsigned __int16 v3; // ax
  int v4; // ecx
  int v5; // eax
  int v6; // ebx
  int v7; // edx

  v2 = *(_DWORD *)(a1 + 438);
  v3 = *(_WORD *)(a1 + 430);
  HIBYTE(v3) &= 0xFu;
  v4 = 190 * (*(_DWORD *)(a1 + 416) << 29 >> 31)
     + 200 * (*(_DWORD *)(a1 + 416) << 30 >> 31)
     + 230 * (*(_DWORD *)(a1 + 416) << 27 >> 31)
     + 400 * (*(_DWORD *)(a1 + 416) << 28 >> 31)
     + 200 * (*(_DWORD *)(a1 + 416) & 1)
     + v3
     + v2;
  v5 = a1;
  v6 = a1 + 12;
  do
  {
    v7 = *(char *)(v5 + 402);
    if ( v7 != -1 )
      v4 += (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * v7];
    ++v5;
  }
  while ( v5 != v6 );
  return v4;
}
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];

//----- (0043F340) --------------------------------------------------------
int  AI_TickNationPostTurn(int a1)
{
  int v1; // ecx
  int v2; // edx
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int i; // edi
  int j; // eax
  int v10; // edx

  v1 = 0;
  v2 = 0;
  v3 = 0;
  do
  {
    v4 = *(char *)(v3 + gameData + 509678);
    if ( (v4 == 2 || v4 == 1) && *(unsigned __int8 *)(v3 + gameData + 509676) == a1 && v2 >= 0 )
    {
      v5 = v3 + gameData + 509674;
      if ( (unsigned int)*(char *)(v5 + 4) < 4 && *(__int16 *)(v5 + 16) != -1 )
      {
        v6 = Building_GetTotalValue(v5);
        v1 = v6 + v7;
      }
    }
    ++v2;
    v3 += 467;
  }
  while ( v2 < 100 );
  for ( i = 0; i != 362500; i += 725 )
  {
    if ( *(unsigned __int8 *)(i + gameData + 147178) == a1 && *(__int16 *)(i + gameData + 147180) != -1 )
    {
      for ( j = 0; j != 310; j += 31 )
      {
        v10 = *(__int16 *)(i + gameData + j + 147180);
        if ( v10 == UNIT_TYPE_GOLD_CARGO || v10 == UNIT_TYPE_PEASANT_CARGO )
          v1 += *(char *)(i + gameData + j + 147189);
      }
    }
  }
  return v1;
}
// 43F391: conditional instruction was optimized away because edx.4<64u
// 43F3A0: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 43F3B5: variable 'v7' is possibly undefined
// 43F3B7: variable 'v2' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043F460) --------------------------------------------------------
int  Player_CalcAvailableStrongholdFunds(int a1)
{
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx

  v2 = 0;
  v3 = 0;
  v4 = 0;
  do
  {
    v5 = *(char *)(gameData + v4 + 509678);
    if ( (v5 == 2 || v5 == 1) && *(unsigned __int8 *)(v4 + gameData + 509676) == a1 && v3 >= 0 )
    {
      v6 = v4 + gameData + 509674;
      if ( (unsigned int)*(char *)(v6 + 4) < 4 && *(__int16 *)(v6 + 16) != -1 )
        v2 += *(_DWORD *)(v4 + gameData + 510112);
    }
    ++v3;
    v4 += 467;
  }
  while ( v3 < 100 );
  return v2;
}
// 43F4AE: conditional instruction was optimized away because eax.4<64u
// 43F4BE: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;

//----- (0043F500) --------------------------------------------------------
int  Player_SpendStrongholdFundsEvenly(int a1, signed int a2)
{
  int v4; // ecx
  int i; // eax
  int v6; // edx
  unsigned int v7; // esi
  int v8; // edx
  int result; // eax
  unsigned int v10; // ebp

  do
  {
    v4 = 0;
    for ( i = 0; i != 46700; i += 467 )
    {
      v6 = *(char *)(gameData + i + 509678);
      if ( (v6 == 2 || v6 == 1)
        && *(unsigned __int8 *)(i + gameData + 509676) == a1
        && *(_DWORD *)(i + gameData + 510112) )
      {
        ++v4;
      }
    }
    v7 = a2 / v4;
    if ( !(a2 / v4) )
    {
      v4 = 1;
      v7 = a2;
    }
    v8 = 0;
    do
    {
      result = *(char *)(v8 + gameData + 509678);
      if ( result == 2 || result == 1 )
      {
        result = v8 + gameData;
        if ( a1 == *(unsigned __int8 *)(v8 + gameData + 509676) )
        {
          v10 = *(_DWORD *)(result + 510112);
          if ( v10 )
          {
            --v4;
            if ( v7 > v10 )
            {
              *(_DWORD *)(result + 510112) = 0;
              a2 -= v10;
            }
            else
            {
              a2 -= v7;
              *(_DWORD *)(result + 510112) = v10 - v7;
            }
          }
        }
      }
      v8 += 467;
    }
    while ( v8 < 46700 && v4 );
  }
  while ( a2 );
  return result;
}
// 43F5D4: conditional instruction was optimized away because ecx.4!=0
// 5202E4: using guessed type int gameData;

//----- (0043F600) --------------------------------------------------------
int BuildingSpriteCache_Reset()
{
  int result; // eax

  for ( result = 0; result != 650; result += 13 )
    g_BuildingSpriteCache[result] = -1;
  return result;
}

//----- (0043F630) --------------------------------------------------------
int  BuildingSpriteCache_LoadEntry(
        int a1,
        int a2,
        signed int a3,
        int a4,
        DWORD a5,
        signed int a6,
        int a7)
{
  int entry_index;
  int entry_offset;
  unsigned int oldest_tick;
  int i;
  signed int v16; // eax
  signed int v17; // ebx
  int v18; // ebx
  unsigned __int8 v19; // al
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v25; // eax
  int v27; // eax

  (void)a6;
  entry_index = -1;
  for ( i = 0; i < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++i )
  {
    if ( g_BuildingSpriteCache[BUILDING_SPRITE_CACHE_RECORD_STRIDE * i] == -1 )
    {
      entry_index = i;
      break;
    }
  }
  if ( entry_index < 0 )
  {
    oldest_tick = (unsigned int)-1;
    entry_index = 0;
    for ( i = 0; i < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++i )
    {
      int last_used_tick;

      entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * i;
      last_used_tick = *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9);
      if ( oldest_tick > (unsigned int)last_used_tick )
      {
        oldest_tick = (unsigned int)last_used_tick;
        entry_index = i;
      }
    }
    DLXSprite_ReleaseAndClear((int *)(void *)(g_BuildingSpriteCache + BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index + 5));
  }
  entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index;
  g_BuildingSpriteCache[entry_offset] = (char)a1;
  g_BuildingSpriteCacheKeyCol2[entry_offset] = (char)a2;
  g_BuildingSpriteCacheKeyCol3[entry_offset] = (char)a4;
  g_BuildingSpriteCacheKeyCol4Signed[entry_offset] = (char)a3;
  g_BuildingSpriteCacheKeyCol5[entry_offset] = (char)a7;
  *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(entry_index, entry_offset);
  if ( a1 )
  {
    if ( a3 >= 3 )
    {
      v21 = 4 * a2 + 12 + a7;
    }
    else
    {
      if ( a3 == -1 )
        v20 = a7 + 32;
      else
        v20 = a7 + 4 * a3;
      v21 = v20;
    }
    v18 = 36 * a4 + 180 * (a1 - 1) + 45 + v21;
  }
  else
  {
    if ( a3 >= 3 )
    {
      v17 = a2 + 3;
    }
    else
    {
      if ( a3 == -1 )
        v16 = 8;
      else
        v16 = a3;
      v17 = v16;
    }
    v18 = 9 * a4 + v17;
  }
  v19 = *(_BYTE *)(gameData + 140016);
  if ( v19 == 0 )
  {
    v22 = Mem_Alloc(22, entry_index, v18, a5);
    if ( v22 )
      v22 = DLXSprite_LoadCachedEntry(v22, aBuildin1_s32, v18);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = v22;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( v19 == 1 )
  {
    v25 = Mem_Alloc(22, entry_index, v18, a5);
    if ( v25 )
      v25 = DLXSprite_LoadCachedEntry(v25, aBuildin2_s32, v18);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = v25;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( v19 == 2 )
  {
    v27 = Mem_Alloc(22, entry_index, v18, a5);
    if ( v27 )
      v27 = DLXSprite_LoadCachedEntry(v27, aBuildin3_s32, v18);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = v27;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
}
// 5202E4: using guessed type int gameData;
// 5438ED: using guessed type int dword_5438ED;
// 5438F1: using guessed type int dword_5438F1;

//----- (0043F880) --------------------------------------------------------
int  BuildingSpriteCache_GetOrLoadEntry(DWORD a1, int a2, signed int a3, int a4, int a5)
{
  int entry_index;

  for ( entry_index = 0; entry_index < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++entry_index )
  {
    int entry_offset;

    entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index;
    if ( (signed char)g_BuildingSpriteCache[entry_offset] == (int)a1 )
    {
      if ( (unsigned char)g_BuildingSpriteCacheKeyCol2[entry_offset] == (unsigned int)a2 )
      {
        if ( (unsigned char)g_BuildingSpriteCacheKeyCol3[entry_offset] == (unsigned int)a4 )
        {
          if ( (signed char)g_BuildingSpriteCacheKeyCol4Signed[entry_offset] == a3 )
          {
            if ( (unsigned char)g_BuildingSpriteCacheKeyCol5[entry_offset] == (unsigned int)a5 )
            {
              *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(a5, entry_index);
              return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
            }
          }
        }
      }
    }
  }
  return BuildingSpriteCache_LoadEntry(a1, a2, a3, a4, a1, a2, a5);
}
// 5438ED: using guessed type int dword_5438ED;
// 5438F1: using guessed type int dword_5438F1;

//----- (0043F920) --------------------------------------------------------
int BuildingSpriteCache_Clear()
{
  int i; // edx
  int result; // eax

  for ( i = 0; i != 650; i += 13 )
  {
    while ( 1 )
    {
      result = g_BuildingSpriteCache[i];
      if ( result != -1 )
        break;
      i += 13;
      if ( i == 650 )
        return result;
    }
    g_BuildingSpriteCache[i] = -1;
    result = DLXSprite_ReleaseAndClear((int *)(void *)&g_BuildingSpriteCache[i + 5]);
    *(int *)(void *)(g_BuildingSpriteCache + i + 5) = 0;
  }
  return result;
}
// 5438ED: using guessed type int dword_5438ED;

//----- (0043F980) --------------------------------------------------------
int BuildingSpriteCache_CountEntries()
{
  int v0; // edx
  int i; // eax

  v0 = 0;
  for ( i = 0; i != 650; i += 13 )
  {
    if ( g_BuildingSpriteCache[i] != -1 )
      ++v0;
  }
  return v0;
}

//----- (0043F9B0) --------------------------------------------------------
int Rules_RebuildTempleFacts()
{
  int i; // ebx
  int result; // eax
  int j; // ecx
  int v4; // ecx

  for ( i = 0; ; ++i )
  {
    result = gameData;
    if ( i >= *(_DWORD *)(gameData + 140000) )
      break;
    for ( j = 0; j < *(_DWORD *)(gameData + 140004); j = v4 + 1 )
    {
      if ( MapTile_GetReligiousSiteCategory(i, j) )
        Rules_LogTempleFact(i, v4);
    }
  }
  return result;
}
// 43F9E8: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043FB10) --------------------------------------------------------
signed int  MapTile_GetReligiousSiteCategory(int a1, int a2)
{
  signed int result; // eax

  switch ( *(_WORD *)(gameData + 1400 * a1 + 14 * a2 + 2) )
  {
    case 0x2D8:
    case 0x2DA:
    case 0x2DC:
      result = 1;
      break;
    case 0x2D9:
    case 0x2DB:
    case 0x2DD:
      result = 2;
      break;
    case 0x2DE:
    case 0x2E0:
    case 0x2E2:
      result = 3;
      break;
    case 0x2DF:
    case 0x2E1:
    case 0x2E3:
      result = 4;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FBA0) --------------------------------------------------------
int * Temple_GenerateApproachTrack(int a1, int a2, int a3, int a4)
{
  int tile_column_offset; // ebp
  int tile_record_offset; // eax
  unsigned __int16 saved_site_word; // dx
  int current_y; // ebx
  int *result; // eax

  (void)a3;
  tile_column_offset = 1400 * a2;
  tile_record_offset = tile_column_offset + 14 * a4;
  Debug_Log(a1, a2, a4, (int)aUnit_movetra_2);
  saved_site_word = *(_WORD *)(gameData + tile_record_offset + 2);
  *(_WORD *)(gameData + tile_record_offset + 2) = -1;
  current_y = *(__int16 *)(725 * a1 + gameData + 147176);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_request", a1, a2, a4, saved_site_word);
  result = Unit_MoveTrack(
             a1,
             *(__int16 *)(725 * a1 + gameData + 147174),
             a2,
             current_y,
             a2,
             a4);
  *(_WORD *)(gameData + tile_record_offset + 2) = saved_site_word;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_result", a1, a2, a4, result ? *result : -1);
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FC60) --------------------------------------------------------
__int16 * Temple_SpawnGiftUnitGroup(int a1, int a2, double a3)
{
  char v3; // cl
  signed int v4; // ebp
  _WORD *v5; // edi
  int i; // esi
  __int16 *result; // eax
  signed int v8; // edi
  _WORD *v9; // esi
  int v10; // ebx
  unsigned int v11; // eax
  char v12; // cl
  char v13; // bl
  unit_type v14; // edx
  unsigned int v15; // eax
  char v16; // cl
  _WORD v17[172]; // [esp+0h] [ebp-170h] BYREF
  int v18; // [esp+158h] [ebp-18h]
  int v19; // [esp+15Ch] [ebp-14h]

  v18 = a1;
  v19 = a2;
  v4 = Rng_RandRange(1, 5);
  if ( ACTIVE_MISSION_INDEX == 2 && v18 == 95 && v19 == 16 || ACTIVE_MISSION_INDEX == 12 && v18 == 58 && v19 == 77 )
  {
    v5 = v17;
    for ( i = 0; i != 4; ++i )
    {
      UnitSlot_InitFromType((int)v5, g_TempleGiftUnitPool_ScriptedRam[i], v3);
      v5 = (_WORD *)((char *)v5 + 31);
    }
    v4 = 4;
  }
  else
  {
    v8 = 0;
    if ( v4 > 0 )
    {
      v9 = v17;
      do
      {
        v10 = ACTIVE_MISSION_INDEX;
        if ( v10 == 2 || v10 == 6 || v10 == 12 || v10 == 16 )
        {
          v11 = Rng_RandRange(0, 6);
          v13 = v12;
          v14 = g_TempleGiftUnitPool_HumanTroops[v11];
        }
        else
        {
          v15 = Rng_RandRange(0, 4);
          v13 = v16;
          v14 = g_TempleGiftUnitPool_MinorMonsters[v15];
        }
        UnitSlot_InitFromType((int)v9, v14, v13);
        ++v8;
        v9 = (_WORD *)((char *)v9 + 31);
      }
      while ( v8 < v4 );
    }
  }
  *(_WORD *)((char *)v17 + 31 * v4) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(v18, v19, (unsigned __int8 *)v17, a3);
  if ( result )
    return (__int16 *)UI_StartWorldMapUnitAttentionFlash(
                        *(unsigned __int16 *)(TILE_INDEX(*result, result[1])),
                        (int)result,
                        200 * *result + gameData);
  return result;
}
// 43FCBB: variable 'v3' is possibly undefined
// 43FD55: variable 'v12' is possibly undefined
// 43FD89: variable 'v16' is possibly undefined
// 515D10: using guessed type unit_type dword_515D10[5];
// 515D24: using guessed type unit_type dword_515D24[7];
// 515D40: using guessed type unit_type dword_515D40[];
// 5202E4: using guessed type int gameData;

//----- (0043FDE0) --------------------------------------------------------
__int16 * Temple_SpawnGiftGoldCargoStack(signed int a1, int a2, char a3, int a4, double a5)
{
  int v6; // esi
  int v7; // ebp
  int i; // ecx
  signed int v9; // eax
  int v10; // esi
  char v11; // dl
  __int16 *result; // eax
  _WORD v13[4]; // [esp+0h] [ebp-170h] BYREF
  char v14[335]; // [esp+9h] [ebp-167h]
  int v15; // [esp+158h] [ebp-18h]
  int v16; // [esp+15Ch] [ebp-14h]
  signed int v17; // [esp+160h] [ebp-10h]

  v17 = a1;
  v16 = a2;
  v15 = a4;
  v6 = 0;
  v7 = 31 * (a1 / 100);
  for ( i = 0; i <= v7; UnitSlot_InitFromType((int)v13 + i, UNIT_TYPE_GOLD_CARGO, a3) )
    ++v6;
  v9 = v17;
  *(_WORD *)((char *)v13 + i) = -1;
  v10 = v6 - 1;
  v11 = 100 * (v9 % 100) / 100;
  v14[31 * v10] = v11;
  if ( !v11 )
    *(_WORD *)((char *)v13 + 31 * v10) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(v16, v15, (unsigned __int8 *)v13, a5);
  if ( result )
    return (__int16 *)UI_StartWorldMapUnitAttentionFlash(
                        *(unsigned __int16 *)(TILE_INDEX(*result, result[1])),
                        (int)result,
                        gameData + 200 * *result);
  return result;
}
// 43FE25: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043FEF0) --------------------------------------------------------
int  Temple_ShowOutcomePopup(int a1, int a2, int a3, int a4, DWORD a5)
{
  _DWORD *v5; // eax
  int SpriteWidth; // edx
  int v7; // ecx
  int v8; // eax
  _DWORD *Surface; // eax
  int v10; // edi
  int SpriteForChar; // eax
  int v12; // eax
  DWORD v13; // ebp
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  int v18; // eax
  int v19; // ecx
  _DWORD *v20; // [esp+38h] [ebp-28h] BYREF
  int v21; // [esp+3Ch] [ebp-24h]
  DWORD v22; // [esp+40h] [ebp-20h]
  int v23; // [esp+44h] [ebp-1Ch]
  int v24; // [esp+48h] [ebp-18h]
  int v25; // [esp+4Ch] [ebp-14h]

  v23 = a1;
  v25 = a2;
  v21 = a4;
  v5 = (_DWORD *)Mem_Alloc(4112, a3, a4, a5);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a4);
  v20 = v5;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  DLX_GetSpriteWidth((int)v20, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v20, 0x16u);
  v8 = v7 + 6;
  if ( (unsigned __int16)SpriteWidth > v7 + 6 )
    v8 = SpriteWidth;
  v24 = v8;
  Surface = (_DWORD *)Mem_Alloc(188, v7, a4, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 640, v24);
  v10 = (int)Surface;
  Render_FillRect(0, Surface, 150, 0, 0x27Fu, v24 + 149, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)v20, 22);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v22 + 52))(
    150,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  DLX_GetSpriteHeight((int)v20, 0x16u);
  v12 = DLX_GetSpriteForChar((int)v20, 23);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  v13 = v22;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v22 + 52))(
    156,
    v12,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  if ( v25 != -1 )
  {
    v18 = DLX_GetSpriteForChar((int)v20, v25);
    v13 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v13 + 52))(
      285,
      v18,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  Render_ReleaseSurface(17, v13);
  UI_DrawTextFmt(v10, 70, 569, 210, 6, v23);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping(v14) && !DD_IsLost(v15) )
    DD_Pump(v19, 0);
  Render_Begin((int)g_RenderState, 0);
  if ( v21 )
  {
    v16 = v25;
    if ( v25 == -1 )
      v16 = 7;
    Audio_PlayArtifactSound(v16);
  }
  Render_Pump();
  Render_FillRect((_DWORD *)v10, 0, 0, 0, 0x27Fu, v24 - 1, 0, 0x96u);
  Render_Present((int)g_RenderState);
  if ( v10 )
    (**(void (***)(void))(v10 + 184))();
  return DLXSpriteSet_ReleaseAndClear((int *)&v20);
}
// 43FF56: variable 'v7' is possibly undefined
// 44008E: variable 'v14' is possibly undefined
// 44015C: variable 'v15' is possibly undefined
// 44016D: variable 'v19' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (004401A0) --------------------------------------------------------
_DWORD * Temple_Random(a1, a2, a3, a4)
_DWORD *a1;
int a2;
char a3;
DWORD a4;
{
  int v6; // ecx
  _DWORD *v7; // eax
  int v8; // ebx
  int v9; // edi
  signed int v10; // ebx
  int v11; // ecx
  signed int v12; // edx
  _DWORD *result; // eax

  Debug_Log(a2, a3, a4, (int)aTemple_random);
  v6 = 0;
  v7 = a1;
  if ( *a1 != -1 )
  {
    do
    {
      v8 = v7[1];
      v9 = v7[6];
      v7 += 6;
      v6 += v8;
    }
    while ( v9 != -1 );
  }
  v10 = Rng_RandRange(0, v6 - 1);
  Debug_Log(v11, v10, a4, (int)a__RDSum_probD);
  for ( result = a1; ; result += 6 )
  {
    v12 += result[1];
    if ( v12 >= v10 )
      break;
  }
  return result;
}
// 4401E5: variable 'v11' is possibly undefined
// 4401EF: variable 'v12' is possibly undefined

//----- (00440250) --------------------------------------------------------
void  Temple_ProcessGift(DWORD a1, __int16 *a2, int a3, char a4, double a5)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  __int16 *v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  __int16 *v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // ecx

  Debug_Log(a3, a4, a1, (int)aTemple_process);
  switch ( a1 )
  {
    case 0u:
      Temple_SpawnGiftUnitGroup(a4, v7, a5);
      return;
    case 1u:
      UI_StartTileBlinkFlash(*a2, a2[1], v8);
      Unit_Kill((int)a2, a4, a1, a5);
      return;
    case 2u:
      UnitStack_AdjustFatigueByPredicate(a2, -100, UnitSlot_PredicateAlways, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), 200 * *a2 + gameData, v9);
      return;
    case 3u:
      UnitStack_AdjustMoraleByPredicate(a2, 20, UnitSlot_PredicateAlways, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), 200 * *a2 + gameData, v10);
      return;
    case 4u:
      v11 = a2;
      v12 = v8 ^ v7;
      do
      {
        v13 = v11[3];
        if ( v13 == -1 )
          break;
        v11 = (__int16 *)((char *)v11 + 31);
        ++v12;
        *((_BYTE *)v11 - 16) = 100;
      }
      while ( v12 < 10 );
      goto LABEL_9;
    case 5u:
      v15 = a2;
      v12 = v8 ^ v7;
      do
      {
        v13 = v15[3];
        if ( v13 == -1 )
          break;
        v15 = (__int16 *)((char *)v15 + 31);
        *((_BYTE *)v15 - 16) = 100;
        ++v12;
        *((_BYTE *)v15 - 15) = 0;
      }
      while ( v12 < 10 );
LABEL_9:
      Rules_SyncArmyFactStrength(a2, v12, v13, a4, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), 200 * *a2 + gameData, v14);
      return;
    case 6u:
      do
        UnitStack_CycleAllSlotOrders(a2, a1, a5);
      while ( v17 < 3 );
      goto LABEL_15;
    case 7u:
      UnitStack_AdjustMoraleByPredicate(a2, 2, UnitSlot_PredicateAlways, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), a2[1], v18);
      return;
    case 8u:
      do
        UnitStack_CycleAllSlotOrders(a2, a1, a5);
      while ( v19 < 2 );
LABEL_15:
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), gameData + 200 * *a2, v16);
      break;
    case 9u:
      Temple_SpawnGiftGoldCargoStack(100, a4, *((_BYTE *)a2 + 4), v7, a5);
      break;
    case 0xAu:
      Temple_SpawnGiftGoldCargoStack(200, a4, *((_BYTE *)a2 + 4), v7, a5);
      break;
    case 0xBu:
      Temple_SpawnGiftGoldCargoStack(50, a4, *((_BYTE *)a2 + 4), v7, a5);
      break;
    case 0xCu:
      Temple_SpawnGiftGoldCargoStack(300, a4, *((_BYTE *)a2 + 4), v7, a5);
      break;
    case 0xDu:
      UnitStack_AdjustMoraleByPredicate(a2, -20, UnitSlot_PredicateAlways, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), 200 * *a2 + gameData, v20);
      break;
    case 0xEu:
      UnitStack_AdjustMoraleByPredicate(a2, -1, UnitSlot_PredicateAlways, a1, a5);
      UnitStack_AdjustFatigueByPredicate(a2, 50, UnitSlot_PredicateAlways, a1, a5);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*a2, a2[1])), 200 * *a2 + gameData, v21);
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
int  Temple_UnitGetInto(int stack_index, int tile_x, int tile_y, DWORD a4, double a5)
{
  int v6; // edx
  __int16 *v7; // ebp
  int v8; // eax
  _DWORD *v9; // esi
  signed int v10; // eax
  int v11; // ebx
  int v12; // ecx
  int v13; // ecx
  int result; // eax
  int v15; // ecx
  _DWORD *v16; // edi
  int v17; // ecx
  DWORD *v18; // esi
  int v19; // edx
  int v20; // edx
  int v21; // ecx
  int v22; // ebx
  const char *v23; // eax
  int v24; // ecx
  int v25; // ebx
  int v26; // ecx
  int v27; // ecx
  int v28[3]; // [esp+0h] [ebp-3Ch]
  int v29[3]; // [esp+Ch] [ebp-30h]
  int v30[3]; // [esp+18h] [ebp-24h]
  int v31; // [esp+24h] [ebp-18h]
  int v32; // [esp+28h] [ebp-14h]

  v31 = tile_x;
  v32 = tile_y;
  Debug_Log(tile_x, tile_y, a4, (int)aTemple_unitget);
  v7 = (__int16 *)(725 * stack_index + gameData + 147174);
  Diagnostics_TraceWorldMapActionEvent("temple_unit_getinto_enter", stack_index, tile_x, tile_y, MapTile_GetReligiousSiteCategory(tile_x, tile_y));
  v8 = gameData + 1423 * *((unsigned __int8 *)v7 + 4);
  if ( *(_DWORD *)(v8 + 140063) )
  {
    if ( *(_DWORD *)(v8 + 140051) )
      v9 = &g_TempleGiftOutcomeTable_OwnCultActive;
    else
      v9 = &g_TempleGiftOutcomeTable_OwnCultInactive;
  }
  else if ( *(_DWORD *)(v8 + 140051) )
  {
    v9 = &g_TempleGiftOutcomeTable_ForeignCultActive;
  }
  else
  {
    v9 = &g_TempleGiftOutcomeTable_ForeignCultInactive;
  }
  v10 = MapTile_GetReligiousSiteCategory(v31, v32);
  v11 = 1423 * *((unsigned __int8 *)v7 + 4);
  v12 = *(_DWORD *)(gameData + v11 + 140063);
  if ( v12 && (v10 == 3 || v10 == 4)
    || (LOBYTE(v11) = gameData, !*(_DWORD *)(1423 * *((unsigned __int8 *)v7 + 4) + gameData + 140063))
    && (v10 == 1 || v10 == 2) )
  {
    Debug_Log(v12, v11, (DWORD)v7, (int)aTemple_unitg_0);
    v30[0] = (int)g_TempleSacrilegeUnitKilledTexts[0];
    v30[1] = (int)g_TempleSacrilegeUnitKilledTexts[1];
    v30[2] = (int)g_TempleSacrilegeUnitKilledTexts[2];
    if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v7 + 4) + 140051) )
    {
      LOBYTE(v11) = 1;
      Temple_ShowOutcomePopup(v30[(unsigned __int8)g_LanguageIndex], 0, v13, 1, (DWORD)v7);
    }
    UI_StartTileBlinkFlash(*v7, v7[1], v13);
    return Unit_Kill((int)v7, v11, (DWORD)v7, a5);
  }
  else
  {
    v15 = ACTIVE_MISSION_INDEX;
    if ( v15 == 1 || v15 == 11 )
    {
      result = 14 * v32;
      ++*(_WORD *)(gameData + 1400 * v31 + 14 * v32 + 2);
      Diagnostics_TraceWorldMapActionEvent(
        "temple_unit_getinto_mission_site_increment",
        stack_index,
        v31,
        v32,
        MapTile_GetReligiousSiteCategory(v31, v32));
    }
    else if ( v10 == 2 || v10 == 4 )
    {
      Debug_Log(v15, gameData, (DWORD)v7, (int)aTemple_unitg_2);
      v29[0] = (int)g_TempleGiftRewardText[0];
      v29[1] = (int)g_TempleGiftRewardText[1];
      v29[2] = (int)g_TempleGiftRewardText[2];
      v28[0] = (int)g_TempleGiftEmptyText[0];
      v28[1] = (int)g_TempleGiftEmptyText[1];
      v28[2] = (int)g_TempleGiftEmptyText[2];
      result = 1423 * *((unsigned __int8 *)v7 + 4) + gameData;
      if ( *(_DWORD *)(result + 140051) )
      {
        v27 = *(_DWORD *)(result + 140063);
        if ( v27 )
          return Temple_ShowOutcomePopup(v29[(unsigned __int8)g_LanguageIndex], -1, v27, 0, (DWORD)v7);
        else
          return Temple_ShowOutcomePopup(v28[(unsigned __int8)g_LanguageIndex], -1, 0, 0, (DWORD)v7);
      }
    }
    else
    {
      v16 = v9;
      v18 = Temple_Random(v9, v15, gameData, (DWORD)v7);
      v19 = ACTIVE_MISSION_INDEX;
      if ( (v19 == 2 || v19 == 6 || v19 == 12 || v19 == 16)
        && *(_DWORD *)(1423 * *((unsigned __int8 *)v7 + 4) + gameData + 140051) )
      {
        if ( ACTIVE_MISSION_INDEX == 2 && v31 == 95 && v32 == 16
          || ACTIVE_MISSION_INDEX == 12 && v31 == 58 && v32 == 77 )
        {
          v18 = (DWORD *)&g_TempleGiftOutcomeTable_OwnCultActive;
        }
        else
        {
          while ( *v18 && *v18 != 15 )
            v18 = Temple_Random(v16, v17, v11, (DWORD)v7);
        }
      }
      Debug_Log(v17, v11, (DWORD)v7, (int)aTemple_unitg_1);
      v20 = 1423 * *((unsigned __int8 *)v7 + 4);
      v21 = *(_DWORD *)(v20 + gameData + 140051);
      if ( v21 )
      {
        v22 = *(_DWORD *)(v20 + gameData + 140063);
        if ( v22 )
          v23 = aSw_chs;
        else
          v23 = aSw_pog;
        Win_PlayModeChangeFrameTransition(v23, 1, v21, v22, (DWORD)v7);
        Temple_ShowOutcomePopup(v18[(unsigned __int8)g_LanguageIndex + 3], v18[2], v24, 1, (DWORD)v7);
      }
      Temple_ProcessGift(*v18, v7, v32, v31, a5);
      v25 = gameData + 1400 * v31;
      LOWORD(v26) = *(_WORD *)(v25 + 14 * v32 + 2);
      *(_WORD *)(v25 + 14 * v32 + 2) = ++v26;
      return (int)Rules_RetractTempleFact(v31, v26, v25, (DWORD)v7);
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
int  Temple_OutcomePopup_HandleCloseClick(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_TempleOutcomePopupCloseFlag = v4;
  return result;
}
// 440A2B: variable 'v4' is possibly undefined
// 543C84: using guessed type int dword_543C84;

//----- (00440A40) --------------------------------------------------------
_DWORD * Temple_OutcomePopup_HandleDestroyBuildingClick(int a1, int a2, char a3, DWORD a4, double a5)
{
  UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_TempleOutcomePopupCloseFlag = 1;
  return Building_Destroy(g_BuildingUIRecordPtr, a3, a4, a5);
}
// 543C80: using guessed type int dword_543C80;
// 543C84: using guessed type int dword_543C84;

//----- (00440A60) --------------------------------------------------------
int  Temple_OutcomePopup_HandleAcceptUnitsClick(int a1, int a2, double a3)
{
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ebx
  unsigned int v11; // eax
  unsigned int v12; // edx
  int v13; // ebp
  int i; // esi
  int SpriteForChar; // eax
  int v16; // ecx
  int v17; // edi
  int v18; // [esp+0h] [ebp-50h]
  int v19[11]; // [esp+4h] [ebp-4Ch] BYREF
  int v20; // [esp+30h] [ebp-20h]
  int v21; // [esp+34h] [ebp-1Ch]

  UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  result = 0;
  v5 = 0;
  v6 = 0;
  do
  {
    if ( g_BuildingUnitsPopupSelectedSlots[result] )
    {
      ++v6;
      ++v5;
      v19[v6 - 1] = result;
    }
    ++result;
  }
  while ( result < 10 );
  v19[v5] = -1;
  if ( v19[0] != -1 )
  {
    Building_UnitsLeave((unsigned __int8 *)g_BuildingUIRecordPtr, v19, a3);
    Audio_PlaySoundEffectByName(aDclose_1, 64);
    v21 = 12;
    g_RenderDevice = &g_MainRenderDevice;
    v10 = Time_Now(v8, v7);
    do
    {
      do
        v11 = Time_Now(v9, v10 + 10);
      while ( v11 < v12 );
      v13 = v21;
      for ( i = 0; i < 10; ++i )
      {
        if ( g_BuildingUnitsPopupSelectedSlots[i] )
        {
          SpriteForChar = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, v13);
          v18 = 0;
          v20 = *((_DWORD *)g_RenderDevice + 46);
          (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v20 + 52))(
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
      v17 = v21;
      result = Time_Now(v9, v12);
      v10 = result;
      v21 = v17 - 1;
    }
    while ( v17 != 5 );
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
void * RenderHook_DemoText(int a1, char a2, DWORD a3)
{
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int v6; // esi
  int v7; // edi
  DWORD v8; // ebp
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  __int16 v12; // ax
  void *result; // eax
  __int16 v14; // bx
  __int16 SpriteHeight; // ax
  int v16; // ecx
  unsigned __int16 v17; // [esp+60h] [ebp-38h]
  void *v18; // [esp+70h] [ebp-28h]
  _DWORD *v19; // [esp+74h] [ebp-24h]
  int v20; // [esp+78h] [ebp-20h]

  v18 = g_RenderDevice;
  Surface = (_DWORD *)Mem_Alloc(188, a1, a2, a3);
  if ( Surface )
  {
    v14 = DLX_GetSpriteWidth(g_DemoTextDLXSpriteSet, 0) + 1;
    SpriteHeight = DLX_GetSpriteHeight(g_DemoTextDLXSpriteSet, 0);
    Surface = Render_CreateSurface(v16, SpriteHeight + 1, v14);
  }
  v19 = Surface;
  g_RenderDevice = Surface;
  SpriteForChar = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 0);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    0,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v6 = 0;
  v7 = 0;
  v20 = 0;
  do
  {
    if ( *(__int16 *)(v7 + g_BuildingUIRecordPtr + 18) == -1 )
    {
      DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 5);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
      DLX_GetSpriteForChar(g_BuildingUnitsPopupSlotSpriteSets[v20], 0);
      v8 = *((_DWORD *)g_RenderDevice + 46);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v8 + 52))(-1, -1, -1, -1, 1, 0, 0);
      if ( g_BuildingUnitsPopupSelectedSlots[v6] )
      {
        v9 = DLX_GetSpriteForChar(g_MarksSpriteSet, 5);
        v8 = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v8 + 52))(
          78 * (v6 / 5) + 50,
          v9,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
      if ( *(_BYTE *)(v7 + g_BuildingUIRecordPtr + 28) )
      {
        v10 = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 3);
        v8 = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v8 + 52))(
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
      Render_ReleaseSurface(7, v8);
      UI_DrawTextFmt(
        v7,
        (unsigned __int16)g_DemoTextColumnXOffsets[v6 % 5],
        (unsigned __int16)g_DemoTextColumnXOffsets[v6 % 5] + 32,
        78 * (v6 / 5) + 98,
        3,
        (int)aD_78);
    }
    v7 += 31;
    ++v6;
    ++v20;
  }
  while ( v6 < 10 );
  Render_Pump();
  v17 = DLX_GetSpriteWidth(g_DemoTextDLXSpriteSet, 0) - 1;
  v12 = DLX_GetSpriteHeight(g_DemoTextDLXSpriteSet, 0);
  Render_BlitSurfaceRect(v19, 0, 0, 0, v12 - 1, v17, 0xC8u, 0x64u);
  Render_Present((int)g_RenderState);
  if ( v19 )
    (*(void (**)(void))v19[46])();
  result = v18;
  g_RenderDevice = v18;
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
int  UI_DemoTextPresent(int a1, int a2, char a3, DWORD a4)
{
  _DWORD *v5; // eax
  int v6; // esi
  int v7; // ecx
  int v8; // eax
  char v9; // bl
  int v10; // ecx
  _DWORD *v11; // eax
  unsigned __int8 *v12; // ebx
  int v13; // ecx
  void *v14; // ecx
  int v15; // edx
  int v16; // ecx
  unsigned int v18; // edi
  int v19; // edx
  int v20; // ecx
  int v21; // eax
  int v22; // ecx
  signed int v23; // eax
  int v24; // edx
  char v25[100]; // [esp+0h] [ebp-74h] BYREF
  void *v26; // [esp+64h] [ebp-10h]
  int v27; // [esp+70h] [ebp-4h]

  v27 = a2;
  v26 = g_RenderDevice;
  g_BuildingUIRecordPtr = UNIT_RECORD(a1);
  g_TempleOutcomePopupCloseFlag = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, a2, a3, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a3);
  g_DemoTextDLXSpriteSet = (int)v5;
  v6 = 0;
  memset_(0, 0);
  do
  {
    v8 = v6 + g_BuildingUIRecordPtr;
    if ( *(__int16 *)(v6 + g_BuildingUIRecordPtr + 18) != -1 )
    {
      v9 = *(_BYTE *)(v8 + 20);
      UI_BeginUnitInfo(v25, *(_BYTE *)(v8 + 18), v9);
      v11 = (_DWORD *)Mem_Alloc(4112, v10, v9, a4);
      if ( v11 )
        v11 = DLXSpriteSet_Load(v11, v9);
      *(int *)((char *)g_BuildingUnitsPopupSlotSpriteSets + v7) = (int)v11;
    }
    v7 += 4;
    v6 += 31;
  }
  while ( v7 != 40 );
  LOBYTE(v12) = 10;
  memset_(40, 0);
  RenderHook_DemoText(v13, 10, a4);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  g_RenderDevice = v14;
  Render_Begin((int)g_RenderState, 0);
  while ( !g_TempleOutcomePopupCloseFlag )
  {
    DD_Pump((int)g_RenderState, (char)v12);
    v12 = 0;
    v18 = ((g_MouseCursorRawY >> g_CursorCoordShift) - 148) / 78;
    v19 = 0;
    v20 = (g_MouseCursorRawX >> g_CursorCoordShift) - 200;
    do
    {
      v21 = (unsigned __int16)g_DemoTextColumnXOffsets[v19];
      if ( (unsigned __int16)v21 <= v20 && v20 <= v21 + 32 )
        break;
      ++v19;
      ++v12;
    }
    while ( v19 < 5 );
    if ( v18 <= 1 && (unsigned int)v12 <= 4 )
    {
      v12 += 5 * v18;
      if ( *(__int16 *)(31 * (_DWORD)v12 + g_BuildingUIRecordPtr + 18) != -1 )
      {
        if ( DD_IsFlipping((int)g_RenderState) )
        {
          g_BuildingUnitsPopupSelectedSlots[(_DWORD)v12] ^= 1u;
          Audio_PlaySoundEffectByName(aMarker, 64);
          RenderHook_DemoText(v22, (char)v12, a4);
          Render_Begin((int)g_RenderState, 0);
        }
        else if ( DD_IsLost((int)g_RenderState) )
        {
          v23 = Building_HasSpecialPersonageGarrisonEntries(g_BuildingUIRecordPtr);
          v12 = (unsigned __int8 *)(g_BuildingUIRecordPtr + 18 + v24);
          Unit_Info(100, 100, v23, v12, a4, 0);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(g_DemoTextHoverWidgetTable, a4);
  }
  DLXSpriteSet_ReleaseAndClear(&g_DemoTextDLXSpriteSet);
  v15 = 0;
  g_RenderDevice = v26;
  v16 = 0;
  do
  {
    if ( v16 != g_BuildingUnitsPopupSlotSpriteSets[v15] )
    {
      nfree_(v16);
      g_BuildingUnitsPopupSlotSpriteSets[v15] = v16;
    }
    ++v15;
  }
  while ( v15 != 10 );
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
void  BattleMapFileName(char *a1, int a2, int a3)
{
  unsigned __int16 primary; // bx
  unsigned __int16 secondary; // cx
  unsigned __int16 tertiary; // dx
  const char *suffix;
  int tile;

  Debug_Log(a2, a3, (DWORD)a1, (int)aBattlemapfilen);
  strcpy(a1, aMaps);
  tile = gameData + 1400 * a2 + 14 * a3;
  primary = *(_WORD *)tile;
  secondary = *(_WORD *)(tile + 2);
  tertiary = *(_WORD *)(tile + 4);
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
  strcat(a1, suffix);
  a1[strlen(a1) + 1] = 0;
  a1[strlen(a1)] = Rng_RandRange(0, 1) + 48;
  strcat(a1, a_mab);
  Debug_Log((int)a1, 0, 0, (int)aBattlemapfil_0);
}
// 4413AA: variable 'v5' is possibly undefined
// 516410: using guessed type char *off_516410[7];
// 5202E4: using guessed type int gameData;

//----- (004414C0) --------------------------------------------------------
char  Str_SwapAndConcatInPlace(char *a1, char *a2)
{
  const char *v4; // esi
  char *v5; // edi
  char *v6; // edx
  char v7; // al
  char v8; // al
  char *v9; // esi
  char *v10; // edi
  char v11; // al
  char v12; // al
  char *v13; // esi
  char *v14; // edi
  char result; // al

  v4 = a1;
  v5 = (char *)j_Mem_Alloc(strlen(a1));
  v6 = v5;
  do
  {
    v7 = *v4;
    *v5 = *v4;
    if ( !v7 )
      break;
    v8 = v4[1];
    v4 += 2;
    v5[1] = v8;
    v5 += 2;
  }
  while ( v8 );
  v9 = a2;
  v10 = a1;
  do
  {
    v11 = *v9;
    *v10 = *v9;
    if ( !v11 )
      break;
    v12 = v9[1];
    v9 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  v13 = v6;
  v14 = &a1[strlen(a1)];
  do
  {
    result = *v13;
    *v14 = *v13;
    if ( !result )
      break;
    result = v13[1];
    v13 += 2;
    v14[1] = result;
    v14 += 2;
  }
  while ( result );
  return result;
}
// 4730FB: using guessed type int __thiscall j_Mem_Alloc(_DWORD);

//----- (00441550) --------------------------------------------------------
char  BattleMap_GetOutcomeVariantFileName(char *a1, int a2, int a3)
{
  char *name;
  int insert_offset;

  BattleMapFileName(a1, a2, a3);
  name = strrchr(a1, '\\');
  if ( name )
    ++name;
  else
    name = a1;
  insert_offset = (a2 == 0) + 1;
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
int  BattleMap_GetMoveSoundSurfaceClass(int a1, int a2)
{
  return (unsigned __int8)g_MoveSoundSurfaceClassTable[*(__int16 *)(40 * a1 + g_MapData + 2 * a2)];
}
// 532048: using guessed type int g_MapData;

//----- (004415E0) --------------------------------------------------------
char * Sound_BuildMusicTrackPath(char *a1, char *a2, int a3)
{
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  char *v9; // edi
  char v10; // al
  char v11; // al
  const char *v12; // edi
  char *v13; // esi
  char *v14; // edi
  char v15; // al
  char v16; // al
  _BYTE v19[28]; // [esp+0h] [ebp-1Ch] BYREF

  v4 = aSfxMusic;
  v5 = a1;
  do
  {
    v6 = *v4;
    *v5 = *v4;
    if ( !v6 )
      break;
    v7 = v4[1];
    v4 += 2;
    v5[1] = v7;
    v5 += 2;
  }
  while ( v7 );
  v9 = &a1[strlen(a1)];
  do
  {
    v10 = *a2;
    *v9 = *a2;
    if ( !v10 )
      break;
    v11 = a2[1];
    a2 += 2;
    v9[1] = v11;
    v9 += 2;
  }
  while ( v11 );
  v12 = a1;
  sprintf_(v19, "%d.wav", a3);
  v13 = v19;
  v14 = (char *)&v12[strlen(v12)];
  do
  {
    v15 = *v13;
    *v14 = *v13;
    if ( !v15 )
      break;
    v16 = v13[1];
    v13 += 2;
    v14[1] = v16;
    v14 += 2;
  }
  while ( v16 );
  return a1;
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00441670) --------------------------------------------------------
int  Sound_PlayNamedSfxFile(char *a1, int a2)
{
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  int v11; // esi
  char v12[100]; // [esp+0h] [ebp-64h] BYREF

  if ( !g_Audio_MusicActiveFlag )
    return 0;
  qmemcpy(v12, aSfx_0, sizeof(v12));
  v4 = &v12[strlen(v12)];
  do
  {
    v5 = *a1;
    *v4 = *a1;
    if ( !v5 )
      break;
    v6 = a1[1];
    a1 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = a_wav_5;
  v8 = &v12[strlen(v12)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = CSS_PlaySound((int)v12, a2, 0, 0);
  Audio_SetSoundLoopIfMusicActive(v11, 0, -1);
  g_Audio_ActiveSoundHandle = v11;
  return v11;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;

//----- (00441720) --------------------------------------------------------
int  Music_PlayMainMapTrack(int result, int a2, int a3, DWORD a4)
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
  CHAR v16[100]; // [esp+0h] [ebp-D0h] BYREF
  char v17[100]; // [esp+64h] [ebp-6Ch] BYREF
  int v18; // [esp+C8h] [ebp-8h]
  int v19; // [esp+CCh] [ebp-4h]

  v19 = a3;
  v18 = a2;
  if ( g_Audio_MusicActiveFlag )
  {
    sprintf_(v16, "data\\mainmap%d.wav", result + 1);
    if ( IO_FOpen(v16, (unsigned __int8 *)aRb, v4, a4) )
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
      sprintf_(v17, "sfx\\music\\mainmap%d.wav", v15);
      loadFileSusp(v17, v16);
    }
    g_MainMapMusicHandle = CSS_PlaySound((int)v16, 64, 0, 2000);
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
int  Audio_PauseMusicAndPlayLoopedSound(char *a1, int a2)
{
  int v5; // ebx
  char v6[108]; // [esp+0h] [ebp-6Ch] BYREF

  if ( !g_Audio_MusicActiveFlag )
    return 0;
  CSS_PauseSound(g_MainMapMusicHandle, 2000);
  Sound_BuildMusicTrackPath(v6, a1, a2);
  v5 = CSS_PlaySound((int)v6, 64, 0, 2000);
  CSS_SetSoundLoop(v5, 0, -1);
  g_Audio_ActiveSoundHandle = v5;
  return v5;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441870) --------------------------------------------------------
int  Audio_ResumeMusicAndStopLoopedSound(int result)
{
  int v1; // ebx

  v1 = result;
  if ( g_Audio_MusicActiveFlag )
  {
    CSS_ResumeSound(g_MainMapMusicHandle, 2000);
    CSS_SetSoundVolume(g_MainMapMusicHandle, 64, 1000);
    result = CSS_StopSound(v1, 0);
    g_Audio_ActiveSoundHandle = g_MainMapMusicHandle;
  }
  return result;
}
// 5174D0: using guessed type int dword_5174D0;
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (004418E0) --------------------------------------------------------
int Audio_StopMainMusic()
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
void Audio_DuckMusicVolume()
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundVolume(g_MainMapMusicHandle, 16, 1000);
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441930) --------------------------------------------------------
void Audio_RestoreMusicVolume()
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundVolume(g_MainMapMusicHandle, 64, 1000);
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441960) --------------------------------------------------------
int  Audio_SetMusicVolume(int a1, signed int a2)
{
  int result; // eax

  if ( g_Audio_MusicActiveFlag )
    return CSS_SetSoundVolume(g_MainMapMusicHandle, a1, a2);
  return result;
}
// 5174D8: using guessed type int dword_5174D8;
// 543C9C: using guessed type int dword_543C9C;

//----- (00441980) --------------------------------------------------------
void  Audio_SetSoundLoopIfMusicActive(int a1, int a2, int a3)
{
  if ( g_Audio_MusicActiveFlag )
    CSS_SetSoundLoop(a1, a2, a3);
}
// 5174D8: using guessed type int dword_5174D8;

//----- (004419A0) --------------------------------------------------------
int  Audio_StartMainMusicIfStopped(int a1, DWORD a2)
{
  int result; // eax

  if ( !g_Audio_MusicActiveFlag )
  {
    g_Audio_MusicActiveFlag = 1;
    return Music_PlayMainMapTrack(*(unsigned __int8 *)(gameData + 140016), a1, 1, a2);
  }
  return result;
}
// 5174D8: using guessed type int dword_5174D8;
// 5202E4: using guessed type int gameData;

//----- (004419D0) --------------------------------------------------------
int Audio_StopMainMusicIfPlaying()
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
void Audio_SetMusicActiveFlag()
{
  g_Audio_MusicActiveFlag = 1;
}
// 5174D8: using guessed type int dword_5174D8;

//----- (00441A00) --------------------------------------------------------
void Audio_ClearMusicActiveFlag()
{
  g_Audio_MusicActiveFlag = 0;
}
// 5174D8: using guessed type int dword_5174D8;

//----- (00441A10) --------------------------------------------------------
void Audio_EnableUnitSounds()
{
  g_UnitSoundsEnabled = 1;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441A20) --------------------------------------------------------
void Audio_DisableUnitSounds()
{
  g_UnitSoundsEnabled = 0;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441A30) --------------------------------------------------------
int  Audio_PlayUnitActivateSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[5]; // [esp+1h] [ebp-69h]
  char v10[100]; // [esp+6h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v10, aSfxOddzialy, sizeof(v10));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v10[strlen(v10)];
    do
    {
      v3 = *v1;
      *v2 = *v1;
      if ( !v3 )
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    }
    while ( v4 );
    v5 = aActiv1_wav;
    v6 = &v10[strlen(v10)];
    do
    {
      v7 = *v5;
      *v6 = *v5;
      if ( !v7 )
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    }
    while ( v8 );
    v9[strlen(v10)] = Rng_RandRange(49, 50);
    result = CSS_PlaySound((int)v10, 64, 0, 0);
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
  int v1; // ebx
  char *v2; // esi
  char *v3; // edi
  char v4; // al
  char v5; // al
  char *v6; // esi
  char *v7; // edi
  char v8; // al
  char v9; // al
  char v10[5]; // [esp+1h] [ebp-6Dh]
  char v11[104]; // [esp+6h] [ebp-68h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    v1 = 22 * result;
    CSS_SetSoundVolume(g_LastUnitActivateSoundHandle, 0, 500);
    qmemcpy(v11, aSfxOddzialy_0, 0x64u);
    v2 = (&g_UnitTypeResourceKeys)[v1];
    v3 = &v11[strlen(v11)];
    do
    {
      v4 = *v2;
      *v3 = *v2;
      if ( !v4 )
        break;
      v5 = v2[1];
      v2 += 2;
      v3[1] = v5;
      v3 += 2;
    }
    while ( v5 );
    v6 = aGo1_wav;
    v7 = &v11[strlen(v11)];
    do
    {
      v8 = *v6;
      *v7 = *v6;
      if ( !v8 )
        break;
      v9 = v6[1];
      v6 += 2;
      v7[1] = v9;
      v7 += 2;
    }
    while ( v9 );
    v10[strlen(v11)] = Rng_RandRange(49, 50);
    return CSS_PlaySound((int)v11, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 543CA4: using guessed type int g_LastUnitActivateSoundHandle;

//----- (00441BE0) --------------------------------------------------------
int  Audio_PlayUnitRangedAttackSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxOddzialy_1, sizeof(v9));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v9[strlen(v9)];
    do
    {
      v3 = *v1;
      *v2 = *v1;
      if ( !v3 )
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    }
    while ( v4 );
    v5 = aStrzal_wav;
    v6 = &v9[strlen(v9)];
    do
    {
      v7 = *v5;
      *v6 = *v5;
      if ( !v7 )
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    }
    while ( v8 );
    return CSS_PlaySound((int)v9, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441C80) --------------------------------------------------------
int  Audio_PlayUnitHitSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxOddzialy_2, sizeof(v9));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v9[strlen(v9)];
    do
    {
      v3 = *v1;
      *v2 = *v1;
      if ( !v3 )
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    }
    while ( v4 );
    v5 = aDostal_wav;
    v6 = &v9[strlen(v9)];
    do
    {
      v7 = *v5;
      *v6 = *v5;
      if ( !v7 )
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    }
    while ( v8 );
    return CSS_PlaySound((int)v9, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441D20) --------------------------------------------------------
int  Audio_PlayUnitDeathSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxOddzialy_3, sizeof(v9));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v9[strlen(v9)];
    do
    {
      v3 = *v1;
      *v2 = *v1;
      if ( !v3 )
        break;
      v4 = v1[1];
      v1 += 2;
      v2[1] = v4;
      v2 += 2;
    }
    while ( v4 );
    v5 = aDead_wav;
    v6 = &v9[strlen(v9)];
    do
    {
      v7 = *v5;
      *v6 = *v5;
      if ( !v7 )
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    }
    while ( v8 );
    return CSS_PlaySound((int)v9, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

