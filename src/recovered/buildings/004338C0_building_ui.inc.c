/* Castle, garrison, production, and building modal interfaces.
 * Original function-marker range: 0x004338C0..0x00441D20.
 * Included by clash95.c; not a standalone translation unit. */

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
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
  {
    Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
    Render_Pump();
    Castle_ShowUnitProductionPanel(g_BuildingGarrisonDialogActiveBuilding, renderContext, panelArg);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      backgroundPath = aCastle_chrD_15;
    else
      backgroundPath = aCastle_pogD_15;
    resourceHandle = g_BuildingGarrisonDialogResourceHandle;
    (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, backgroundPath);
    if ( g_BuildingGarrisonDialogUseChrTheme )
      palettePath = aCastle_chrD_16;
    else
      palettePath = aCastle_pogD_16;
    Palette_LoadOrBuildBlendLookupTable(palettePath, g_BuildingGarrisonDialogResourceHandle, g_BuildingGarrisonDialogUseChrTheme, renderContext);
    RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_BuildingGarrisonDialogResourceHandle, v7, renderContext);
    Render_LoadResourceSprite_v4(5, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v8, resourceHandle, renderContext);
    Render_LoadResourceSprite_v4(7, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v9, resourceHandle, renderContext);
    Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)g_BuildingGarrisonDialogResourceHandle, v10, resourceHandle, renderContext);
    g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
    BuildingGarrisonDialog_EnsureActionWidgets(g_BuildingGarrisonDialogActiveBuilding);
    UIWidgetTable_InitDrawStates((_DWORD *)BuildingGarrisonDialogActions);
    (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
    BuildingGarrisonDialog_DrawSlotGrid(-1);
    BuildingGarrisonDialog_DrawSelectedUnitPanel();
    BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(v11, 20, renderContext);
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
void * BuildingGarrisonDialog_ToggleRepairSelectedUnits(int widget, DWORD gameContext)
{
  void *result; // eax
  int slotIndex; // ecx
  int selectedSlotIndex; // ebx

  UIWidget_PlayPressedReleaseAnimation(widget);
  result = (void *)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
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
  result = (void *)g_BuildingGarrisonDialogActiveBuilding;
  if ( (*(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
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
    *(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 0),
    *(_BYTE *)(g_BuildingGarrisonDialogActiveBuilding + 1));
  if ( selectedSlots[0] == -1 || !Building_HasFreeAdjacentExitTile((unsigned __int8 *)g_BuildingGarrisonDialogActiveBuilding) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "garrison_exit_blocked",
      selectedCount,
      selectedSlots[0],
      Building_HasFreeAdjacentExitTile((unsigned __int8 *)g_BuildingGarrisonDialogActiveBuilding),
      0);
    Audio_PlayButtonSound(aWrong_7);
    return Render_Begin((int)g_RenderState, 0);
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

  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  BuildingGarrisonDialog_AnimateSelectedUnit(0);
  BuildingGarrisonDialog_TickExitCountdown(0, deltaTime);
  return Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
}

//----- (00434110) --------------------------------------------------------
int CastleProduction_DrawSelectedUnitPortrait()
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
  if ( cursorOverlayPresented )
    result = Render_Present((int)g_RenderState);
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
void * CastleProduction_RedrawSelectedUnitPanel(int a1, int a2, DWORD renderContext, int a4, int a5)
{
  int v5; // ecx
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
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int selectedUnitMetaOffset; // esi
  int infoPanelSprite; // eax
  DWORD renderMethods; // ebp
  char *unitMetadataPtr; // esi
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
  spriteSet = (_DWORD *)Mem_Alloc(4112, 0x1010, a2, renderContext);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, pathBuffer);
  v35 = v7;
  g_CastleProductionSelectedUnitSpriteSet = (int)spriteSet;
  Unit_BuildSelectedUnitPanelIconPalettePath(pathBuffer, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v7);
  Palette_LoadFromQueryHandle(queryHandle, renderContext);
  paletteIndex = 224;
  srcPalettePtr = &loadedPaletteData;
  do
  {
    ++srcPalettePtr;
    dstPaletteEntry = (_DWORD *)(g_CastleProductionPaletteBuffer + 4 * paletteIndex++);
    *dstPaletteEntry = *(srcPalettePtr - 1);
  }
  while ( paletteIndex <= 255 );
  savedRenderDevice = g_RenderDevice;
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
        (int)(**(&g_UnitTypeMetadataRecords + 22 * unitType))[(unsigned __int8)g_LanguageIndex]);
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
          (int)(**(&g_UnitTypeMetadataRecords + 22 * unitType))[(unsigned __int8)g_LanguageIndex]);
        Render_ReleaseSurface(5, 0x2Du);
      }
      else
      {
        UI_DrawText(
          45,
          rowY,
          (int)(**(&g_UnitTypeMetadataRecords + 22 * unitType))[(unsigned __int8)g_LanguageIndex]);
      }
      availableUnitByteOffset += 4;
      ++stripUnitIndex;
      rowY += 17;
    }
  }
  selectedUnitMetaOffset = 88 * g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
  infoPanelSprite = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 17);
  renderMethods = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int))(renderMethods + 52))(186, infoPanelSprite, -1, -1, -1);
  unitMetadataPtr = (char *)&g_UnitTypeMetadataRecords + selectedUnitMetaOffset;
  Render_ReleaseSurface(7, renderMethods);
  v26 = *(_DWORD *)(*(_DWORD *)unitMetadataPtr + 4 * (unsigned __int8)g_LanguageIndex);
  UI_DrawTextFmt(69, 133, 261, 191, 3, v26);
  UI_DrawTextFmt(69, 201, 217, panelBaseY + 95, 2, (int)aD_68);
  UI_DrawTextFmt(69, 154, 174, panelBaseY + 50, 2, (int)aD_69);
  UI_DrawTextFmt(69, 201, 217, panelBaseY + 50, 2, (int)aD_70);
  UI_DrawTextFmt(69, 229, 260, v27, 2, (int)a0_3);
  if ( unitMetadataPtr[25] )
  {
    if ( unitMetadataPtr[22] )
    {
      UI_DrawTextFmt(154, 154, 174, panelBaseY + 74, 2, (int)aD_73);
      UI_DrawTextFmt(154, 154, v28, panelBaseY + 95, 2, (int)aD_74);
    }
    else
    {
      DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 19);
      renderMethods2 = *((_DWORD *)g_RenderDevice + 46);
      v26 = renderMethods2;
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(renderMethods2 + 52))(-1, -1, -1, -1, 1, 0, 0);
      UI_DrawTextFmt(154, 154, 174, panelBaseY + 95, 2, (int)aD_72);
    }
  }
  else
  {
    DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 18);
    renderMethods2 = *((_DWORD *)g_RenderDevice + 46);
    v26 = renderMethods2;
    (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(renderMethods2 + 52))(-1, -1, -1, -1, 1, 0, 0);
    UI_DrawTextFmt(154, 154, 174, panelBaseY + 95, 2, (int)aD_71);
  }
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 340, 72, 0x138u, 0x16Eu, 0x48u, 0x154u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, v26);
  UI_DrawTextFmt(-1, 0, 119, 348, 2, (int)aD_75);
  UI_DrawTextFmt(-1, 0, 215, 348, 2, (int)aD_76);
  UI_DrawTextFmt(-1, 0, 311, 348, 2, (int)aD_77);
  unitStripRight = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x14u) + 28;
  SpriteHeight = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x14u);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 28, 40, SpriteHeight + 40, unitStripRight, 0x28u, 0x1Cu);
  infoPanelRight = DLX_GetSpriteWidth(g_BuildingUiDlxSpriteSet, 0x11u) + 186;
  infoSpriteHeight = DLX_GetSpriteHeight(g_BuildingUiDlxSpriteSet, 0x11u);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 186, 69, infoSpriteHeight + 69, infoPanelRight, 0x45u, 0xBAu);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
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
void * CastleProduction_DrawLicenceGrid()
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
    if ( *(char *)(slotIndex + g_CastleProductionBuildingPtr + 402) == -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingUiDlxSpriteSet, 22);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
      Render_Present((int)g_RenderState);
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

  result = *(char *)(slotIndex + g_CastleProductionBuildingPtr + 402);
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
    Unit_BuildGarrisonSlotIconSpritePath(iconSpritePath, *(_BYTE *)(slotIndex + g_CastleProductionBuildingPtr + 402), slotIndex);
    result = Mem_Alloc(4112, 0x1010, resourceContext, sprite_set);
    if ( result )
      result = (int)DLXSpriteSet_Load((_DWORD *)result, iconSpritePath);
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
        Building_RemoveUnitLicence(g_CastleProductionBuildingPtr, *(char *)(g_CastleLicenceRemovalSlotIndex + g_CastleProductionBuildingPtr + 402), gameContext);
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
  char *v11; // [esp+44h] [ebp-28h]
  int statusHeaderFull_Strings[9]; // [esp+48h] [ebp-24h]

  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 288, 401, 0x251u, 0x165u, 0x191u, 0x120u);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderContext);
  result = g_CastleProductionBuildingPtr;
  if ( BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(g_CastleProductionBuildingPtr) != -1 )
  {
    if ( Building_CountGarrison(g_CastleProductionBuildingPtr) < 12 || BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) > 1 )
    {
      statusHeader_Strings[0] = (int)UI_Locale_StatusHeader[0];
      statusHeader_Strings[1] = (int)UI_Locale_StatusHeader[1];
      v11 = UI_Locale_StatusHeader[2];
      if ( BUILDING_PRODUCTION_TURNS_REMAINING(g_CastleProductionBuildingPtr) == 1 )
        turnLabelText = aDZugBisZum;
      else
        turnLabelText = aDZbgeBisZum;
      statusLine1_Strings[0] = (int)UI_Locale_StatusLine1[0];
      statusLine1_Strings[1] = (int)UI_Locale_StatusLine1[1];
      statusLine1_Strings[2] = (int)UI_Locale_StatusLine1[2];
      statusDetailA_Strings[0] = (int)UI_Locale_StatusDetail_A[0];
      statusDetailA_Strings[1] = (int)UI_Locale_StatusDetail_A[1];
      statusDetailA_Strings[2] = (int)UI_Locale_StatusDetail_A[2];
      statusDetailB_Strings[0] = (int)UI_Locale_StatusDetail_B[0];
      statusDetailB_Strings[1] = (int)UI_Locale_StatusDetail_B[1];
      statusDetailB_Strings[2] = (int)UI_Locale_StatusDetail_B[2];
      statusDetailC_Strings[0] = (int)UI_Locale_StatusDetail_C[0];
      statusDetailC_Strings[1] = (int)UI_Locale_StatusDetail_C[1];
      statusDetailC_Strings[2] = (int)UI_Locale_StatusDetail_C[2];
      v11 = turnLabelText;
      UI_DrawTextFmt((int)v6, 401, 593, 297, 3, statusHeader_Strings[(unsigned __int8)g_LanguageIndex]);
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
      statusHeaderFull_Strings[0] = (int)UI_Locale_StatusHeader_Full[0];
      statusHeaderFull_Strings[1] = (int)UI_Locale_StatusHeader_Full[1];
      statusHeaderFull_Strings[2] = (int)UI_Locale_StatusHeader_Full[2];
      v6[0] = (int)UI_Locale_StatusLine1_Full[0];
      v6[1] = (int)UI_Locale_StatusLine1_Full[1];
      v6[2] = (int)UI_Locale_StatusLine1_Full[2];
      UI_DrawTextFmt((int)statusLine1_Strings, 401, 593, 307, 3, statusHeaderFull_Strings[(unsigned __int8)g_LanguageIndex]);
      return UI_DrawTextFmt((int)statusLine1_Strings, 401, 593, 327, 3, v6[(unsigned __int8)g_LanguageIndex]);
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
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 425, 285, 0x15Eu, 0x1C2u, 0x11Du, 0x1A9u);
  result = UI_DrawTextFmt(drawContext, 285, 349, 430, 3, (int)aD_38);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532218: using guessed type int dword_532218;

//----- (00435580) --------------------------------------------------------
int UI_GetGridIndexFromMouse()
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
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
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
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, (const void *)g_CastleProductionPaletteBuffer);
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
  int v9; // ecx
  int v10; // edx
  void *v11; // ecx
  int v12; // ecx
  int v13; // [esp-Ch] [ebp-10h]

  UIWidget_ShowPressedState(widget);
  if ( !Building_BuyUnitLicence(g_CastleProductionBuildingPtr, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v4, gameContext) )
    return UIWidget_ShowReleasedState(widget, v5);
  v13 = v5;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  for ( i = 0; ; ++i )
  {
    selectedUnitType = g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex];
    if ( *(char *)(i + g_CastleProductionBuildingPtr + 402) == selectedUnitType )
      break;
  }
  g_LicenceGridAddAnimSlotIndex = i;
  Audio_PlaySoundEffectByName(aDopen, 64);
  CastleProduction_ReloadLicenceSlotSprite(i, widget);
  UI_DrawActionBox(actionContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, v10);
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
int  CastleProduction_HandleProduceAction(int result, char productionSlot, DWORD gameContext)
{
  int v4; // ecx

  if ( g_ProductionGridSelectedIndex != -1 )
  {
    UIWidget_ShowPressedState(result);
    Render_Begin((int)g_RenderState, 0);
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
  int v11; // [esp-4h] [ebp-8h]

  v11 = a2;
  UIWidget_PlayPressedReleaseAnimation(widget);
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Unit_BuildBigInfoGraphicPath(infoGraphicPath, g_CastleProduction_AvailableUnitTypes[g_CastleProductionSelectedAvailableUnitIndex], v5);
  (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, infoGraphicPath);
  (*(void (**)(void))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_CastleProductionPaletteBuffer, 20);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) )
    DD_Pump((int)g_RenderState, (char)g_RenderState);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  if ( g_CastleProductionUseChrTheme )
    backgroundPath = aCastle_chrD_23;
  else
    backgroundPath = aCastle_pogD_23;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *))(renderSurface + 48))(0, backgroundPath);
  Palette_QuantizeChannelsInPlace((_BYTE *)g_CastleProductionPaletteBuffer, 6);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  CastleProduction_RedrawSelectedUnitPanel(v8, 20, gameContext, actionBoxArg, renderSurface);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(gameContext);
  UI_DrawActionBox(actionBoxArg);
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
int  CastleProduction_HandleLicenceGridClick(DWORD gameContext, int renderDevice, int a3)
{
  int result; // eax
  int gridIndex; // ecx
  int v5; // ecx
  int availableUnitIndex; // edx
  int slotUnitType; // ecx

  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    result = UI_GetGridIndexFromMouse();
    gridIndex = result;
    if ( result != -1 )
    {
      result = *(char *)(result + g_CastleProductionBuildingPtr + 402);
      if ( result != -1 && gridIndex != g_ProductionGridSelectedIndex )
      {
        Audio_PlaySoundEffectByName(aMarker_0, 64);
        g_ProductionGridSelectedIndex = v5;
        availableUnitIndex = 0;
        slotUnitType = *(char *)(v5 + g_CastleProductionBuildingPtr + 402);
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
int  CastleProduction_HandleAvailableUnitStripClick(DWORD gameContext, int renderDevice, int widgetTable)
{
  int stripRowOffset; // ebx
  int result; // eax
  int v5; // ecx

  stripRowOffset = ((g_MouseCursorRawY >> g_CursorCoordShift) - 35) / 17 - 2;
  result = DD_IsFlipping((int)g_RenderState);
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
int  CastleProduction_TickAnimations(DWORD gameContext)
{
  int previousResourceHandle; // edx
  void *v2; // ecx
  int v3; // ecx

  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  CastleProduction_AnimateSelectedUnitPortrait(v2);
  CastleProduction_TickLicenceGridAnimations(v3, gameContext);
  return Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
}
// 435B9F: variable 'v2' is possibly undefined
// 435BA4: variable 'v3' is possibly undefined

//----- (00435BC0) --------------------------------------------------------
int  Castle_ShowUnitProductionPanel(int buildingPtr, DWORD renderContext, int actionBoxArg)
{
  unsigned int v3; // eax
  int v4; // ecx
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
  int v25; // ecx

  g_CastleProductionBuildingPtr = buildingPtr;
  g_CastleProductionUseChrTheme = *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + 140063);
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
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  v11 = g_CastleProductionPaletteBuffer;
  (*(void (__fastcall **)(_DWORD, char *))(renderSurface + 48))(0, panelBackgroundPath);
  Palette_QuantizeChannelsInPlace((_BYTE *)g_CastleProductionPaletteBuffer, 6);
  dlxSpriteSet = (_DWORD *)Mem_Alloc(4112, v12, v11, useChrTheme);
  if ( dlxSpriteSet )
    dlxSpriteSet = DLXSpriteSet_Load(dlxSpriteSet, g_CastleProductionUseChrTheme ? aCastle_chrD_19 : aCastle_pogD_19);
  g_BuildingUiDlxSpriteSet = (int)dlxSpriteSet;
  if ( g_CastleProductionUseChrTheme )
    panelPalettePath = aCastle_chrD_19;
  else
    panelPalettePath = aCastle_pogD_19;
  Palette_LoadOrBuildBlendLookupTable(panelPalettePath, g_CastleProductionPaletteBuffer, g_CastleProductionUseChrTheme, useChrTheme);
  Render_LoadResourceSprite_v4(5, (_BYTE *)g_CastleProductionPaletteBuffer, v15, v11, useChrTheme);
  Render_LoadResourceSprite_v4(20, (_BYTE *)g_CastleProductionPaletteBuffer, v16, v11, useChrTheme);
  Render_LoadResourceSprite_v4(9, (_BYTE *)g_CastleProductionPaletteBuffer, v17, v11, useChrTheme);
  Render_LoadResourceSprite_v4(7, (_BYTE *)g_CastleProductionPaletteBuffer, v18, v11, useChrTheme);
  Render_LoadResourceSprite_v4(g_ActiveWidgetSpriteTableIndex, (_BYTE *)g_CastleProductionPaletteBuffer, v19, v11, useChrTheme);
  UI_SetActiveWidgetTable(8);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_CastleProductionPaletteBuffer, v20, useChrTheme);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  UIWidgetTable_InitDrawStates(g_CastleUnitProductionWidgetTable);
  RenderState_SelectCursorDescriptor((int)g_RenderState, v21);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  CastleProduction_RedrawSelectedUnitPanel(v22, 20, useChrTheme, actionBoxArg, renderSurface);
  CastleProduction_ReloadLicenceSlotSprites(20);
  CastleProduction_DrawProductionStatus(useChrTheme);
  UI_DrawActionBox(actionBoxArg);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_CastleProductionPaletteBuffer, 20);
  Render_Present((int)g_RenderState);
  g_CastleProductionExitSignal = 0;
  g_ActiveDialogAnimationTickHook = (int (*)(void))CastleProduction_TickAnimations;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    CastleProduction_TickAnimations(useChrTheme);
    UI_RunHoverTooltipZones(g_CastleUnitProductionTooltipZone);
    g_RenderDevice = &g_MainRenderDevice;
    if ( !UIWidgetTable_PollHoverAndActions(g_CastleUnitProductionWidgetTable, useChrTheme) )
    {
      CastleProduction_HandleLicenceGridClick(useChrTheme, (int)&g_MainRenderDevice, (int)g_CastleUnitProductionWidgetTable);
      CastleProduction_HandleAvailableUnitStripClick(useChrTheme, (int)&g_MainRenderDevice, (int)g_CastleUnitProductionWidgetTable);
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
    return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
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
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 48, 400, 0x1BBu, 0x3Cu, 0x190u, 0x30u);
  result = UI_DrawTextFmt(drawContext, 347, 445, 48, 3, (int)aD_39);
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
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 272, 548, 0x259u, 0x12Cu, 0x224u, 0x110u);
  result = UI_DrawTextFmt(drawContext, 548, 601, 272, 3, (int)aD_40);
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

//----- (00436180) --------------------------------------------------------
int  BuildingTransferDialog_IncreaseTransferAmount(int widget)
{
  int v2; // edx
  int v3; // ecx
  int startAmount; // ebx
  int v5; // edx
  int v6; // ecx
  int timePrev; // eax
  int v8; // ecx
  int timeNow; // eax
  int v10; // edx
  int v11; // ecx
  DWORD sourceGold; // ebp
  int v13; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount += 10;
  startAmount = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)g_RenderState, startAmount);
    timePrev = Time_Now(v6, v5);
    timeNow = Time_Now(v8, timePrev);
    g_Building_TransferAmount = 10 * ((startAmount + (v10 - v11) * (timeNow - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount > 1000 )
      g_Building_TransferAmount = 1000;
    sourceGold = *(_DWORD *)(g_BuildingTransferSourcePtr + 438);
    if ( g_Building_TransferAmount > sourceGold )
    {
      sourceGold = 10;
      g_Building_TransferAmount = 10 * (*(_DWORD *)(g_BuildingTransferSourcePtr + 438) / 0xAu);
    }
    BuildingTransferDialog_DrawTransferAmountValue(sourceGold, (int)g_RenderState);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v13);
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
int  BuildingTransferDialog_DecreaseTransferAmount(int widget)
{
  int v2; // edx
  int v3; // ecx
  int startAmount; // ebx
  int v5; // edx
  int v6; // ecx
  int timeValue; // eax
  int v8; // ecx
  int currentTime; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // ecx

  UIWidget_ShowPressedState(widget);
  Render_Pump();
  Time_Now(v3, v2);
  g_Building_TransferAmount -= 10;
  startAmount = g_Building_TransferAmount;
  do
  {
    DD_Pump((int)g_RenderState, startAmount);
    timeValue = Time_Now(v6, v5);
    currentTime = Time_Now(v8, timeValue);
    g_Building_TransferAmount = 10 * ((startAmount - (v10 - v11) * (currentTime - v11) / 0x32u) / 0xA);
    if ( g_Building_TransferAmount < 0 )
      g_Building_TransferAmount = 0;
    BuildingTransferDialog_DrawTransferAmountValue((DWORD)g_RenderState, 0);
  }
  while ( DD_IsFlipping((int)g_RenderState) );
  Render_Present((int)g_RenderState);
  return UIWidget_ShowReleasedState(widget, v12);
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
int  BuildingTransferTargetList_SetDrawOrigin(int result, int originY)
{
  g_BuildingTransferTargetListDrawX = result;
  g_BuildingTransferTargetListDrawY = originY;
  return result;
}
// 53242C: using guessed type int g_BuildingTransferTargetListDrawX;
// 532430: using guessed type int g_BuildingTransferTargetListDrawY;

//----- (00436620) --------------------------------------------------------
void * BuildingTransferTargetList_Draw(int a1, DWORD renderContext)
{
  _DWORD *spriteSet; // eax
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
    spriteSet = (_DWORD *)Mem_Alloc(4112, a1, 0, renderContext);
    if ( spriteSet )
      spriteSet = DLXSpriteSet_Load(spriteSet, aCas_list_s32);
    g_BuildingTransferTargetListSpriteSet = (int)spriteSet;
    DLXSpriteSet_DrawFormattedText((DWORD)spriteSet, -1, a1, aCas_list_pal);
  }
  Render_ReleaseSurface(5, renderContext);
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
int  BuildingTransferTargetList_SelectPrevious(int widget, DWORD renderContext)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(widget);
  if ( g_BuildingTransferTargetListIndex )
    --g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_previous old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
  return UIWidget_ShowReleasedState(widget, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;

//----- (00436930) --------------------------------------------------------
int  BuildingTransferTargetList_SelectNext(int widget, DWORD renderContext)
{
  int old_index;

  old_index = g_BuildingTransferTargetListIndex;
  UIWidget_ShowPressedState(widget);
  if ( g_BuildingTransferTargetIdsLookahead[g_BuildingTransferTargetListIndex] != -1 )
    ++g_BuildingTransferTargetListIndex;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[economy] list_next old=%d new=%d target=%d\n",
      old_index,
      g_BuildingTransferTargetListIndex,
      g_BuildingTransferTargetIds[g_BuildingTransferTargetListIndex]);
  BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
  return UIWidget_ShowReleasedState(widget, 1);
}
// 511234: using guessed type char (*off_511234)[1024];
// 53235C: using guessed type int g_BuildingTransferTargetListIndex;
// 532362: using guessed type __int16 word_532362[99];

//----- (00436970) --------------------------------------------------------
int  BuildingTransferTargetList_Rebuild(int sourceBuildingRecord, int reserveFirstSlot)
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
  insert_index = reserveFirstSlot ? 1 : 0;
  do
  {
    building_record = result + gameData + BUILDING_TABLE_OFFSET;
    if ( *(char *)(result + gameData + 509678) != -1
      && *(_BYTE *)(result + gameData + 509678)
      && *(unsigned __int8 *)(building_record + 2) == current_player
      && building_record != sourceBuildingRecord
      && !*(_WORD *)(building_record + 16)
      && insert_index < BUILDING_TRANSFER_TARGET_LIST_CAPACITY )
    {
      g_BuildingTransferTargetIds[insert_index] = building_index;
      ++insert_index;
    }
    ++building_index;
    result += BUILDING_RECORD_SIZE;
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
int  BuildingTransferTargetList_HandleClick(DWORD renderContext)
{
  int rowOffset; // ebx
  int result; // eax

  rowOffset = ((g_MouseCursorRawY >> g_CursorCoordShift) - g_BuildingTransferTargetListDrawY) / 18 - 2;
  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= g_BuildingTransferTargetListDrawX )
    {
      result = g_BuildingTransferTargetListDrawX + 266;
      if ( g_MouseCursorRawX >> g_CursorCoordShift <= g_BuildingTransferTargetListDrawX + 266
        && rowOffset >= -2
        && rowOffset <= 2
        && rowOffset + g_BuildingTransferTargetListIndex >= 0 )
      {
        result = g_BuildingTransferTargetIds[rowOffset + g_BuildingTransferTargetListIndex];
        if ( result != -1 )
        {
          g_BuildingTransferTargetListIndex += rowOffset;
          Render_Pump();
          BuildingTransferTargetList_Draw((int)g_BuildingTransferTargetListSurfaceBuffer, renderContext);
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
int  UI_DrawFormattedTokenLine(int leftX, int rightX, int templateIndex, int penX)
{
  int availableWidth; // esi
  int result; // eax
  unsigned __int8 *tokenRecord; // ecx
  int v9; // ecx
  _BYTE *wrapTextPtr; // ecx
  _BYTE *segmentText; // ecx
  char *wrapBreakPos; // eax
  int v13; // ecx
  _BYTE *v14; // edx
  char *templateRow; // [esp+0h] [ebp-18h]
  int tokenOffset; // [esp+4h] [ebp-14h]
  char savedChar; // [esp+8h] [ebp-10h]

  availableWidth = rightX - leftX;
  tokenOffset = 0;
  templateRow = (char *)&g_UiFormattedMessageTemplateTable + 150 * templateIndex;
  do
  {
    result = (int)&templateRow[50 * (unsigned __int8)g_LanguageIndex];
    tokenRecord = (unsigned __int8 *)(result + tokenOffset);
    if ( !*(_DWORD *)(result + tokenOffset + 1) )
      break;
    if ( *tokenRecord == 4 && (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(tokenRecord + 1)) > availableWidth )
    {
      wrapTextPtr = *(_BYTE **)(tokenRecord + 1);
      while ( (unsigned __int16)Render_LoadResourceSprite_v3(wrapTextPtr) > availableWidth )
      {
        wrapBreakPos = TextSprite_FindWordWrapBreak(segmentText, availableWidth);
        savedChar = *wrapBreakPos;
        *wrapBreakPos = 0;
        UI_DrawTextFmt(leftX, leftX, rightX, penX, 4, v13);
        *v14 = savedChar;
        penX += UI_GetTextXOffset(g_ActiveTextSpriteSlot);
      }
      UI_DrawTextFmt(leftX, leftX, rightX, penX, 1, (int)segmentText);
    }
    else
    {
      UI_DrawTextFmt(leftX, leftX, rightX, penX, *tokenRecord, *(_DWORD *)(tokenRecord + 1));
    }
    result = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
    penX += result;
    tokenOffset = v9 + 5;
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
int  UnitBattle_ResetAiReachGridForSide(int side)
{
  int reachGridBase; // edi
  int result; // eax
  int gridRow; // ecx
  int rowEndOffset; // ebx
  int unitRecordOffset; // [esp+4h] [ebp-1Ch]

  reachGridBase = 0;
  unitRecordOffset = 0;
  do
  {
    result = unitRecordOffset + g_MapData;
    if ( *(__int16 *)(unitRecordOffset + g_MapData + 852) != -1 )
    {
      result = *(unsigned __int8 *)(result + 854);
      if ( result == side )
      {
        gridRow = 0;
        rowEndOffset = reachGridBase + 160;
        do
        {
          result = reachGridBase + 160 * gridRow;
          do
          {
            result += 8;
            *(int *)((char *)&g_UnitBattleAiReachGrid + result) = 0;
            *(int *)((char *)&g_UnitBattleAiReachGridCellSecondField + result) = 0;
          }
          while ( result != rowEndOffset );
          ++gridRow;
          rowEndOffset += 160;
        }
        while ( gridRow < 20 );
      }
    }
    reachGridBase += 3204;
    unitRecordOffset += 31;
  }
  while ( reachGridBase != 70488 );
  return result;
}
// 532048: using guessed type int g_MapData;
// 532440: using guessed type int dword_532440;
// 532444: using guessed type int dword_532444;

//----- (00436D10) --------------------------------------------------------
signed int  UnitBattle_RetreatUnit(int unitIndex, int a2, char a3, DWORD a4)
{
  int movingUnitIndex; // edx
  __int16 *unitRecord; // ecx
  signed int j; // ebp
  int v8; // ebx
  signed int result; // eax
  int scanUnitOffset; // esi
  int scanRecordBase; // eax
  int *movePath; // eax
  int unitRecordAddr; // ecx
  int searchRadius; // [esp+4h] [ebp-34h]
  int signY; // [esp+8h] [ebp-30h]
  int i; // [esp+Ch] [ebp-2Ch]
  int offsetX; // [esp+10h] [ebp-28h]
  int signX; // [esp+14h] [ebp-24h]
  int originY; // [esp+18h] [ebp-20h]
  int originX; // [esp+1Ch] [ebp-1Ch]
  int candidateY; // [esp+20h] [ebp-18h]
  int candidateX; // [esp+24h] [ebp-14h]

  Debug_Log(a2, a3, a4, (int)aCofnij_oddzial);
  unitRecord = (__int16 *)(31 * movingUnitIndex + g_MapData + 852);
  searchRadius = 0;
  originX = (unsigned __int16)unitRecord[2];
  signX = 1;
  signY = 1;
  originY = (unsigned __int16)unitRecord[3];
  while ( 2 )
  {
    for ( i = 1; i <= 2; ++i )
    {
      signY = -signY;
      offsetX = 0;
      candidateY = signY * searchRadius + originY;
      while ( 2 )
      {
        for ( j = 1; j <= 2; ++j )
        {
          signX = -signX;
          candidateX = signX * offsetX + originX;
          if ( candidateX < 0 )
            candidateX = 0;
          if ( candidateX > *(_DWORD *)(g_MapData + 804) )
            candidateX = *(_DWORD *)(g_MapData + 804);
          if ( candidateY < 0 )
            candidateY = 0;
          v8 = *(_DWORD *)(g_MapData + 800);
          if ( candidateY > v8 )
            candidateY = *(_DWORD *)(g_MapData + 800);
          if ( *(__int16 *)(40 * candidateX + g_MapData + 2 * candidateY + 1534) == -1 )
          {
            v8 = candidateY;
            if ( UnitBattle_GetTileMoveCostOrZero(*unitRecord, candidateX, candidateY) )
            {
              unitRecord[2] = candidateX;
              scanUnitOffset = 0;
              unitRecord[3] = candidateY;
              while ( 1 )
              {
                scanRecordBase = scanUnitOffset + g_MapData;
                if ( *(__int16 *)(scanUnitOffset + g_MapData + 852) != -1 && *(_BYTE *)(scanRecordBase + 854) != *((_BYTE *)unitRecord + 2) )
                {
                  v8 = *(unsigned __int16 *)(scanRecordBase + 858);
                  if ( UnitBattle_IsTileWithinRange(unitIndex, *(unsigned __int16 *)(scanRecordBase + 856), (unsigned __int16)v8) )
                  {
                    unitRecord[2] = originX;
                    unitRecord[3] = originY;
                    g_UnitBattleScanTileRow = *(unsigned __int16 *)(scanUnitOffset + g_MapData + 856);
                    v8 = candidateY;
                    g_BattleTargetTileCol = *(unsigned __int16 *)(scanUnitOffset + g_MapData + 858);
                    movePath = UnitBattle_MoveTrack(unitIndex, candidateX, (int)unitRecord, candidateY, j);
                    *(_DWORD *)((char *)unitRecord + 23) = movePath;
                    if ( movePath )
                      break;
                  }
                }
                scanUnitOffset += 31;
                if ( scanUnitOffset >= 682 )
                  goto LABEL_14;
              }
              UnitBattle_Move(unitIndex, (int)unitRecord, candidateY, j);
              if ( *(_DWORD *)(unitRecordAddr + 23) )
                j__nfree_();
              result = 1;
              *(_DWORD *)(unitRecordAddr + 23) = 0;
              return result;
            }
          }
LABEL_14:
          ;
        }
        offsetX = v8 + 1;
        if ( v8 + 1 <= 2 )
          continue;
        break;
      }
    }
    if ( ++searchRadius <= 2 )
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
BOOL  UnitBattle_IsTileWithinMinRange(int unitIndex, int targetX, int targetY)
{
  int unit_record;
  signed int distance; // eax

  if ( !g_MapData || unitIndex < 0 || unitIndex >= 22 )
    return 0;
  unit_record = g_MapData + 31 * unitIndex + 852;
  if ( *(__int16 *)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(31 * unitIndex + g_MapData + 852 + 4) - targetX)
       * (*(unsigned __int16 *)(31 * unitIndex + g_MapData + 852 + 4) - targetX)
       + (*(unsigned __int16 *)(31 * unitIndex + g_MapData + 852 + 6) - targetY)
       * (*(unsigned __int16 *)(31 * unitIndex + g_MapData + 852 + 6) - targetY));
  return distance <= (unsigned __int8)g_UnitTypeMinRange_512583[88 * *(__int16 *)unit_record];
}
// 532048: using guessed type int g_MapData;

//----- (004370B0) --------------------------------------------------------
signed int  UnitBattle_MoveShootingUnit(int attackerIndex, int defenderSide, char a3, DWORD gameContext)
{
  int movingUnitIndex; // edx
  DWORD unitRecordOffset; // ebp
  int unitRecord; // esi
  int v7; // ecx
  int v8; // ecx
  int scanRowBase; // edx
  int targetOccupant; // eax
  int targetUnitIndex; // ebx
  int targetRecordOffset; // esi
  int v13; // ecx
  int shotResult; // edx
  signed int result; // eax
  int v16; // ecx
  int movePath; // eax
  int v18; // ecx
  int v19; // ecx
  int reachedRange; // edi
  int *pathArray; // eax
  int stepIndex; // ebx
  int pathToFree; // edi
  int v24; // ecx
  int occupantUnitIndex; // ebx
  int v26; // ecx
  int shooterRecordOffset; // esi
  int v28; // ecx
  int v29; // ecx
  int shotTargetUnitIndex; // esi
  int shotShooterRecordOffset; // ebx
  int v32; // ecx
  int secondShotResult; // edx
  int wallShotResult; // edx
  __int16 savedRow; // [esp+0h] [ebp-2Ch]
  __int16 savedCol; // [esp+4h] [ebp-28h]
  int pathStep; // [esp+14h] [ebp-18h]

  Debug_Log(attackerIndex, a3, gameContext, (int)aRuch_oddzialem);
  unitRecordOffset = 31 * movingUnitIndex;
  unitRecord = g_MapData + 852 + 31 * movingUnitIndex;
  g_BattleShootingUnitMoveActiveFlag = 1;
  if ( UnitBattle_IsTileWithinRange(v7, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    scanRowBase = g_MapData + 40 * g_UnitBattleScanTileRow;
    targetOccupant = *(__int16 *)(scanRowBase + 2 * g_BattleTargetTileCol + 1534);
    if ( targetOccupant != -1 )
    {
      targetUnitIndex = *(__int16 *)(scanRowBase + 2 * g_BattleTargetTileCol + 1534);
      targetRecordOffset = 31 * targetOccupant;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        shotResult = UnitBattle_Shot(v13, targetUnitIndex);
        if ( !shotResult && *(unsigned __int8 *)(unitRecordOffset + g_MapData + 860) < 5u )
          break;
        if ( !shotResult && *(unsigned __int8 *)(unitRecordOffset + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(g_MapData + unitRecordOffset + 852) == -1 )
          break;
        if ( *(__int16 *)(targetRecordOffset + g_MapData + 852) == -1 )
          return 1;
      }
      return 0;
    }
  }
  if ( UnitBattle_IsTileWithinMinRange(v8, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    result = UnitBattle_RetreatUnit(v16, v16, g_BattleTargetTileCol, unitRecordOffset);
    if ( !result )
      return result;
  }
  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
    && *(unsigned __int8 *)(g_MapData + 31 * v16 + 854) == *(_DWORD *)(g_MapData + 836) )
  {
    movePath = UnitBattle_MoveTrackNearWall(v16, g_UnitBattleScanTileRow, g_BattleTargetTileCol, unitRecordOffset);
  }
  else
  {
    movePath = (int *)UnitBattle_MoveTrackNear(v16, v16, g_BattleTargetTileCol, unitRecordOffset);
  }
  *(_DWORD *)(unitRecord + 23) = movePath;
  if ( !*(_DWORD *)(unitRecord + 23) )
    *(_DWORD *)(unitRecord + 23) = UnitBattle_MoveTrackForce(v18, g_BattleTargetTileCol, unitRecordOffset);
  if ( !*(_DWORD *)(unitRecord + 23) )
    return 0;
  if ( UnitBattle_IsTileWithinRange(v18, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
  {
    if ( !*(_DWORD *)(unitRecord + 23) )
      goto LABEL_41;
  }
  else
  {
    reachedRange = -1;
    savedRow = *(_WORD *)(unitRecord + 4);
    HIWORD(pathStep) = 0;
    savedCol = *(_WORD *)(unitRecord + 6);
    LOBYTE(pathStep) = *(_BYTE *)(unitRecord + 4);
    while ( HIWORD(pathStep) <= *(unsigned __int8 *)(unitRecord + 8) - 5 && **(_DWORD **)(unitRecord + 23) && reachedRange == -1 )
    {
      if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
      {
        reachedRange = 1;
      }
      else
      {
        pathArray = *(int **)(unitRecord + 23);
        stepIndex = *pathArray - 1;
        *pathArray = stepIndex;
        pathStep = pathArray[stepIndex + 1];
        if ( *(unsigned __int8 *)(unitRecord + 8) >= HIWORD(pathStep) + 5 )
        {
          *(_WORD *)(unitRecord + 4) = (unsigned __int8)pathStep;
          *(_WORD *)(unitRecord + 6) = BYTE1(pathStep);
        }
      }
    }
    if ( reachedRange == -1 )
    {
      if ( *(_DWORD *)(unitRecord + 23) )
        j__nfree_();
      *(_DWORD *)(unitRecord + 23) = 0;
      return 0;
    }
    *(_WORD *)(unitRecord + 4) = savedRow;
    pathToFree = *(_DWORD *)(unitRecord + 23);
    *(_WORD *)(unitRecord + 6) = savedCol;
    if ( pathToFree )
      j__nfree_();
    *(_DWORD *)(unitRecord + 23) = UnitBattle_MoveTrack(v19, (unsigned __int8)pathStep, v19, BYTE1(pathStep), 0xFFFFFFFF);
    UnitBattle_Move(v24, v24, BYTE1(pathStep), 0xFFFFFFFF);
    if ( !*(_DWORD *)(unitRecord + 23) )
      goto LABEL_40;
  }
  j__nfree_();
LABEL_40:
  *(_DWORD *)(unitRecord + 23) = 0;
LABEL_41:
  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) <= 0
    || *(unsigned __int8 *)(g_MapData + 31 * v19 + 854) != *(_DWORD *)(g_MapData + 836)
    || (occupantUnitIndex = *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), occupantUnitIndex != -1)
    && *(unsigned __int8 *)(31 * occupantUnitIndex + g_MapData + 854) != defenderSide )
  {
    if ( UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    {
      shotTargetUnitIndex = *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
      shotShooterRecordOffset = 31 * v29;
      while ( 1 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        secondShotResult = UnitBattle_Shot(v32, shotTargetUnitIndex);
        if ( !secondShotResult && *(unsigned __int8 *)(shotShooterRecordOffset + g_MapData + 860) < 5u )
          break;
        if ( !secondShotResult && *(unsigned __int8 *)(shotShooterRecordOffset + g_MapData + 860) >= 5u )
          return 1;
        if ( *(__int16 *)(g_MapData + shotShooterRecordOffset + 852) == -1 )
          return 0;
        if ( *(__int16 *)(31 * shotTargetUnitIndex + g_MapData + 852) == -1 )
          return 1;
      }
    }
    return 0;
  }
  if ( !UnitBattle_IsTileWithinRange(v19, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
    return 0;
  shooterRecordOffset = 31 * v26;
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( *(char *)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) <= 0 )
      return 1;
    wallShotResult = UnitBattle_ShotWall(v28, g_UnitBattleScanTileRow);
    if ( !wallShotResult && *(unsigned __int8 *)(shooterRecordOffset + g_MapData + 860) < 5u )
      return 0;
  }
  while ( wallShotResult || *(unsigned __int8 *)(shooterRecordOffset + g_MapData + 860) < 5u );
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
int * UnitBattle_EstimateDamageScoreAgainstUnit(int attackerIndex, DWORD defenderIndex)
{
  __int16 *attackerRecord; // esi
  int attackerUnitType; // eax
  int *result; // eax
  char *v7; // ecx
  int altEffectiveness; // eax
  int v9; // ecx
  __int16 *defenderRecordPtr2; // edx
  int *pathBeforeFree; // ebp
  __int16 *defenderRecordPtr3; // edx
  int *pathBeforeFree2; // ebx
  bool i; // zf
  int *pathToFree; // edi
  int v16; // ecx
  __int16 *defenderRecordPtr; // edx
  int *pathPtr; // ebp
  int remainingSteps; // edx
  int *pathArray; // ebx
  int stepApCost; // edx
  char savedAttackerHealth; // [esp+0h] [ebp-40h]
  char savedAttackerHealth2; // [esp+0h] [ebp-40h]
  char savedActionPoints; // [esp+4h] [ebp-3Ch]
  int attackerHealthOut; // [esp+8h] [ebp-38h] BYREF
  int defenderHealthOut; // [esp+Ch] [ebp-34h] BYREF
  int savedRow; // [esp+10h] [ebp-30h]
  int savedCol; // [esp+14h] [ebp-2Ch]
  int effectiveness; // [esp+18h] [ebp-28h]
  int defenderHealth; // [esp+1Ch] [ebp-24h]
  __int16 *defenderRecord; // [esp+20h] [ebp-20h]
  int trackStep; // [esp+24h] [ebp-1Ch]
  int *movePath; // [esp+28h] [ebp-18h]

  attackerRecord = (__int16 *)(g_MapData + 852 + 31 * attackerIndex);
  savedRow = (unsigned __int16)attackerRecord[2];
  savedCol = (unsigned __int16)attackerRecord[3];
  savedActionPoints = *((_BYTE *)attackerRecord + 8);
  attackerUnitType = *attackerRecord;
  defenderRecord = (__int16 *)(31 * defenderIndex + g_MapData + 852);
  if ( attackerUnitType == UNIT_TYPE_RAM )
    return 0;
  result = (int *)UnitBattle_MoveTrackNear(
                    attackerIndex,
                    31 * defenderIndex + g_MapData + 852,
                    *(unsigned __int16 *)(31 * defenderIndex + g_MapData + 852 + 6),
                    defenderIndex);
  movePath = result;
  if ( result )
  {
    effectiveness = Unit_CalcEffectivenessA(v7, 0);
    altEffectiveness = Unit_CalcEffectivenessC(defenderRecord);
    if ( altEffectiveness > v9 )
      effectiveness = altEffectiveness;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(g_MapData + 31 * attackerIndex + 852)] )
    {
      defenderHealth = *((char *)defenderRecord + 9);
      HIWORD(trackStep) = 0;
      for ( i = *movePath == 0; ; i = *movePath == 0 )
      {
        if ( i || !movePath )
        {
          attackerRecord[2] = savedRow;
          attackerRecord[3] = savedCol;
          pathToFree = movePath;
          *((_BYTE *)attackerRecord + 8) = savedActionPoints;
          if ( !pathToFree )
            return 0;
          goto LABEL_41;
        }
        if ( UnitBattle_IsUnitWithinRange(attackerIndex, defenderIndex) )
          break;
        remainingSteps = *movePath - 1;
        pathArray = movePath;
        *movePath = remainingSteps;
        trackStep = pathArray[remainingSteps + 1];
        attackerRecord[2] = (unsigned __int8)trackStep;
        attackerRecord[3] = BYTE1(trackStep);
        stepApCost = HIWORD(trackStep) - v16;
        if ( stepApCost > *((unsigned __int8 *)attackerRecord + 8) )
        {
          attackerRecord[2] = savedRow;
          attackerRecord[3] = savedCol;
          *((_BYTE *)attackerRecord + 8) = savedActionPoints;
LABEL_41:
          j__nfree_();
          return 0;
        }
        *((_BYTE *)attackerRecord + 8) -= stepApCost;
      }
      while ( *((unsigned __int8 *)attackerRecord + 8) >= HIWORD(trackStep) + 5 )
      {
        *((_BYTE *)defenderRecord + 9) = UnitBattle_CalcShotTargetHealthAfterHit(attackerIndex, defenderIndex);
        *((_BYTE *)attackerRecord + 8) -= 5;
      }
      defenderHealthOut = defenderHealth;
      attackerRecord[2] = savedRow;
      attackerRecord[3] = savedCol;
      defenderRecordPtr = defenderRecord;
      *((_BYTE *)attackerRecord + 8) = savedActionPoints;
      pathPtr = movePath;
      *((_BYTE *)defenderRecordPtr + 9) = defenderHealth;
      if ( pathPtr )
        j__nfree_();
      return (int *)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
    }
    else
    {
      if ( !movePath )
        return 0;
      if ( *movePath )
      {
        trackStep = movePath[1];
        if ( *((unsigned __int8 *)attackerRecord + 8) < HIWORD(trackStep) + 5 )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          if ( movePath )
          {
            j__nfree_();
            return 0;
          }
          return 0;
        }
        savedAttackerHealth = *((_BYTE *)attackerRecord + 9);
        defenderHealth = *((char *)defenderRecord + 9);
        while ( *((unsigned __int8 *)attackerRecord + 8) >= HIWORD(trackStep) + 5 )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          *((_BYTE *)attackerRecord + 9) = attackerHealthOut;
          *((_BYTE *)defenderRecord + 9) = defenderHealthOut;
          *((_BYTE *)attackerRecord + 8) -= 5;
        }
        *((_BYTE *)attackerRecord + 8) = savedActionPoints;
        defenderRecordPtr2 = defenderRecord;
        *((_BYTE *)attackerRecord + 9) = savedAttackerHealth;
        pathBeforeFree = movePath;
        *((_BYTE *)defenderRecordPtr2 + 9) = defenderHealth;
        if ( pathBeforeFree )
          j__nfree_();
        return (int *)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
      }
      else if ( *((unsigned __int8 *)attackerRecord + 8) < 5u )
      {
        defenderHealth = *(char *)(31 * defenderIndex + g_MapData + 861);
        UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
        j__nfree_();
        return (int *)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
      }
      else
      {
        savedAttackerHealth2 = *((_BYTE *)attackerRecord + 9);
        defenderHealth = *((char *)defenderRecord + 9);
        while ( *((unsigned __int8 *)attackerRecord + 8) >= 5u )
        {
          UnitBattle_CalcMeleeExchange(attackerIndex, defenderIndex, &defenderHealthOut, &attackerHealthOut, 0);
          *((_BYTE *)attackerRecord + 9) = attackerHealthOut;
          *((_BYTE *)defenderRecord + 9) = defenderHealthOut;
          *((_BYTE *)attackerRecord + 8) -= 5;
        }
        *((_BYTE *)attackerRecord + 8) = savedActionPoints;
        defenderRecordPtr3 = defenderRecord;
        *((_BYTE *)attackerRecord + 9) = savedAttackerHealth2;
        pathBeforeFree2 = movePath;
        *((_BYTE *)defenderRecordPtr3 + 9) = defenderHealth;
        if ( pathBeforeFree2 )
          j__nfree_();
        return (int *)(effectiveness * (defenderHealth - defenderHealthOut) / 100);
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
int  UnitBattle_ScoreTileAgainstRangedUnitsOfSide(int unitIndex, int side, int a3)
{
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int targetCol; // ebx
  int unitRecordPtr; // esi
  int v9; // edx
  int scoreDelta; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // ebx
  int unitRecordPtr2; // esi
  int v17; // edx
  int scoreDelta2; // edx
  int v20; // ecx
  int v21; // eax
  int *v22; // eax
  int *movePath; // ecx
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
  int *movePath2; // ecx
  int v36; // eax
  int v37; // eax
  int v38; // edx
  int *v39; // ecx
  int v40; // edx
  int v41; // ebx
  int v42; // edx
  int scanOffset; // [esp+0h] [ebp-50h]
  __int16 savedRow; // [esp+8h] [ebp-48h]
  int unitRecordOffset; // [esp+Ch] [ebp-44h]
  int trackStep; // [esp+10h] [ebp-40h]
  int packedTrackStep; // [esp+10h] [ebp-40h]
  int bestScore; // [esp+18h] [ebp-38h]
  int effectiveness2; // [esp+1Ch] [ebp-34h]
  int effectiveness; // [esp+20h] [ebp-30h]
  __int16 savedCol; // [esp+24h] [ebp-2Ch]
  __int16 savedCol2; // [esp+28h] [ebp-28h]
  int trackStep2; // [esp+2Ch] [ebp-24h]
  int packedTrackStep2; // [esp+2Ch] [ebp-24h]
  int targetRow; // [esp+30h] [ebp-20h]
  int targetCol2; // [esp+34h] [ebp-1Ch]
  __int16 savedRow2; // [esp+38h] [ebp-18h]

  bestScore = 0;
  scanOffset = 0;
  unitRecordOffset = 31 * unitIndex;
  do
  {
    v3 = *(__int16 *)(g_MapData + scanOffset + 852);
    if ( v3 != -1 && *(unsigned __int8 *)(g_MapData + scanOffset + 854) == side && g_UnitTypeRole[88 * v3] == 4 )
    {
      Unit_CalcEffectivenessA((char *)(unitRecordOffset + g_MapData + 852), 0);
      v4 = Unit_CalcEffectivenessC((__int16 *)(unitRecordOffset + g_MapData + 852));
      if ( v5 <= v4 )
        v6 = Unit_CalcEffectivenessC((__int16 *)(unitRecordOffset + g_MapData + 852));
      else
        v6 = Unit_CalcEffectivenessA((char *)(unitRecordOffset + g_MapData + 852), 0);
      effectiveness = v6;
      targetCol = *(unsigned __int16 *)(scanOffset + g_MapData + 858);
      targetRow = *(unsigned __int16 *)(scanOffset + g_MapData + 856);
      Debug_Log(scanOffset, targetCol, a3, (int)aOddzial_w_zasi);
      unitRecordPtr = unitRecordOffset + g_MapData + 852;
      a3 = (unsigned __int16)targetCol;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v9, (unsigned __int16)targetCol)
        && (*(_BYTE *)(unitRecordOffset + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
      {
        scoreDelta = 0;
LABEL_10:
        LOBYTE(scoreDelta) = *(_BYTE *)(unitRecordPtr + 8);
        goto LABEL_11;
      }
      v20 = targetRow;
      if ( *(char *)(g_MapData + 20 * targetRow + targetCol + 3134) <= 0
        || (v20 = g_MapData + 40 * targetRow, *(__int16 *)(v20 + 2 * targetCol + 1534) != -1)
        && ((v21 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v21 + 852)] & 1) != 0)
         || (*(_BYTE *)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v21 + 864)) >> 5) > 0) )
      {
        v22 = (int *)UnitBattle_MoveTrackNear(unitIndex, v20, targetCol, (unsigned __int16)targetCol);
      }
      else
      {
        v22 = UnitBattle_MoveTrackNearWall(unitIndex, targetRow, targetCol, (unsigned __int16)targetCol);
      }
      movePath = v22;
      if ( !v22 )
      {
        v24 = 31 * unitIndex + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v24 + 852)] )
        {
          if ( (*(_BYTE *)(v24 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v24 + 864)) >> 5) > 0 )
            movePath = UnitBattle_MoveTrackForce(unitIndex, targetCol, (unsigned __int16)targetCol);
        }
      }
      if ( !movePath )
      {
        scoreDelta = -1;
        goto LABEL_11;
      }
      if ( !*movePath )
      {
        j__nfree_();
        goto LABEL_10;
      }
      v25 = g_MapData + 31 * unitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v25 + 852)]
        && (*(_BYTE *)(v25 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v25 + 864)) >> 5) > 0 )
      {
        savedRow = *(_WORD *)(unitRecordPtr + 4);
        HIWORD(packedTrackStep) = 0;
        savedCol = *(_WORD *)(unitRecordPtr + 6);
        if ( *movePath )
        {
          while ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, (unsigned __int16)targetCol) )
          {
            v30 = *v28 - 1;
            *v28 = v30;
            packedTrackStep = v28[v30 + 1];
            if ( HIWORD(packedTrackStep) > (int)*(unsigned __int8 *)(unitRecordPtr + 8) )
              goto LABEL_54;
            *(_WORD *)(unitRecordPtr + 4) = (unsigned __int8)packedTrackStep;
            *(_WORD *)(unitRecordPtr + 6) = BYTE1(packedTrackStep);
            if ( !*v28 )
              goto LABEL_51;
          }
          *(_WORD *)(unitRecordPtr + 4) = savedRow;
          *(_WORD *)(unitRecordPtr + 6) = savedCol;
          j__nfree_();
          LOBYTE(v29) = *(_BYTE *)(unitRecordPtr + 8);
          if ( v29 > HIWORD(packedTrackStep) )
          {
            scoreDelta = v29 - HIWORD(packedTrackStep);
            goto LABEL_11;
          }
          goto LABEL_48;
        }
LABEL_51:
        if ( UnitBattle_IsTileWithinRange(unitIndex, targetRow, (unsigned __int16)targetCol) )
        {
          *(_WORD *)(unitRecordPtr + 4) = savedRow;
          *(_WORD *)(unitRecordPtr + 6) = savedCol;
          if ( *(unsigned __int8 *)(unitRecordPtr + 8) > (int)HIWORD(packedTrackStep) )
          {
            j__nfree_();
            scoreDelta = *(unsigned __int8 *)(unitRecordPtr + 8) - v31;
            goto LABEL_11;
          }
LABEL_47:
          j__nfree_();
LABEL_48:
          scoreDelta = 0;
          goto LABEL_11;
        }
LABEL_54:
        *(_WORD *)(unitRecordPtr + 4) = savedRow;
        *(_WORD *)(unitRecordPtr + 6) = savedCol;
        j__nfree_();
      }
      else
      {
        if ( !*movePath )
          goto LABEL_47;
        trackStep = movePath[1];
        j__nfree_();
        LOWORD(v26) = HIWORD(trackStep);
        v27 = *(unsigned __int8 *)(unitRecordPtr + 8);
        if ( v27 <= v26 )
          scoreDelta = 0;
        else
          scoreDelta = v27 - v26;
      }
LABEL_11:
      if ( effectiveness * (scoreDelta / 5) <= bestScore )
        goto LABEL_19;
      Unit_CalcEffectivenessA((char *)(unitRecordOffset + g_MapData + 852), 0);
      v11 = Unit_CalcEffectivenessC((__int16 *)(unitRecordOffset + g_MapData + 852));
      if ( v12 <= v11 )
        v13 = Unit_CalcEffectivenessC((__int16 *)(unitRecordOffset + g_MapData + 852));
      else
        v13 = Unit_CalcEffectivenessA((char *)(unitRecordOffset + g_MapData + 852), 0);
      effectiveness2 = v13;
      LOWORD(v15) = *(_WORD *)(scanOffset + g_MapData + 858);
      targetCol2 = (unsigned __int16)v15;
      Debug_Log(v14, v15, a3, (int)aOddzial_w_zasi);
      unitRecordPtr2 = g_MapData + 852 + unitRecordOffset;
      a3 = v17;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v17, (unsigned __int16)v15)
        && (*(_BYTE *)(unitRecordOffset + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
      {
        scoreDelta2 = 0;
LABEL_17:
        LOBYTE(scoreDelta2) = *(_BYTE *)(unitRecordPtr2 + 8);
LABEL_18:
        bestScore = scoreDelta2 / 5 * effectiveness2;
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
          || (v33 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v33 + 852)] & 1) == 0)
          && (*(_BYTE *)(v33 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v33 + 864)) >> 5) <= 0 )
        {
          v34 = UnitBattle_MoveTrackNearWall(unitIndex, a3, (unsigned __int16)v15, a3);
          goto LABEL_61;
        }
        v15 = (unsigned __int16)v15;
      }
      v34 = (int *)UnitBattle_MoveTrackNear(unitIndex, v32, v15, a3);
LABEL_61:
      movePath2 = v34;
      if ( !v34 )
      {
        v36 = 31 * unitIndex + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
        {
          if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
            movePath2 = UnitBattle_MoveTrackForce(unitIndex, (unsigned __int16)v15, a3);
        }
      }
      if ( !movePath2 )
      {
        scoreDelta2 = -1;
        goto LABEL_18;
      }
      if ( !*movePath2 )
      {
        j__nfree_();
        goto LABEL_17;
      }
      v37 = g_MapData + 31 * unitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v37 + 852)]
        && (*(_BYTE *)(v37 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v37 + 864)) >> 5) > 0 )
      {
        savedRow2 = *(_WORD *)(unitRecordPtr2 + 4);
        savedCol2 = *(_WORD *)(unitRecordPtr2 + 6);
        HIWORD(packedTrackStep2) = 0;
        if ( *movePath2 )
        {
          while ( !UnitBattle_IsTileWithinRange(unitIndex, a3, targetCol2) )
          {
            v41 = *v39 - 1;
            *v39 = v41;
            packedTrackStep2 = v39[v41 + 1];
            if ( HIWORD(packedTrackStep2) > (int)*(unsigned __int8 *)(unitRecordPtr2 + 8) )
              goto LABEL_89;
            *(_WORD *)(unitRecordPtr2 + 4) = (unsigned __int8)packedTrackStep2;
            *(_WORD *)(unitRecordPtr2 + 6) = BYTE1(packedTrackStep2);
            if ( !*v39 )
              goto LABEL_86;
          }
          *(_WORD *)(unitRecordPtr2 + 4) = savedRow2;
          *(_WORD *)(unitRecordPtr2 + 6) = savedCol2;
          j__nfree_();
          LOBYTE(v40) = *(_BYTE *)(unitRecordPtr2 + 8);
          if ( v40 > HIWORD(packedTrackStep2) )
          {
            scoreDelta2 = v40 - HIWORD(packedTrackStep2);
            goto LABEL_18;
          }
LABEL_83:
          scoreDelta2 = 0;
          goto LABEL_18;
        }
LABEL_86:
        if ( !UnitBattle_IsTileWithinRange(unitIndex, a3, targetCol2) )
        {
LABEL_89:
          *(_WORD *)(unitRecordPtr2 + 4) = savedRow2;
          *(_WORD *)(unitRecordPtr2 + 6) = savedCol2;
          j__nfree_();
          goto LABEL_18;
        }
        *(_WORD *)(unitRecordPtr2 + 4) = savedRow2;
        *(_WORD *)(unitRecordPtr2 + 6) = savedCol2;
        if ( *(unsigned __int8 *)(unitRecordPtr2 + 8) > (int)HIWORD(packedTrackStep2) )
        {
          j__nfree_();
          scoreDelta2 = *(unsigned __int8 *)(unitRecordPtr2 + 8) - v42;
          goto LABEL_18;
        }
      }
      else if ( *movePath2 )
      {
        trackStep2 = movePath2[1];
        j__nfree_();
        LOBYTE(v38) = *(_BYTE *)(unitRecordPtr2 + 8);
        if ( v38 <= HIWORD(trackStep2) )
          scoreDelta2 = 0;
        else
          scoreDelta2 = v38 - HIWORD(trackStep2);
        goto LABEL_18;
      }
      j__nfree_();
      goto LABEL_83;
    }
LABEL_19:
    scanOffset += 31;
  }
  while ( scanOffset != 682 );
  return bestScore;
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
signed int  UnitBattle_ScoreAiActionGridForUnit(int unitIndex, int side, int a3, signed int advanceDir)
{
  int v5; // ecx
  int scoreGridUnitBase; // edi
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edi
  int v12; // ecx
  int advanceOffset6; // esi
  int v14; // ecx
  int i; // ecx
  int scanRecordPtr; // eax
  int *scanTrackPath; // eax
  int pathNode; // ecx
  int v19; // ecx
  int v20; // edi
  int scoreRowByteOffset; // ebx
  int occupantCellPtr; // eax
  __int16 v23; // dx
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  DWORD v30; // ebp
  int unitRecordPtr; // esi
  int v32; // ecx
  int v33; // edx
  int moveScoreDelta; // edx
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
  int trackRowArg; // ecx
  int v84; // eax
  int trackColArg; // ebx
  int *trackPath; // eax
  int *trackPathPtr; // ecx
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
  int tileScore; // ebp
  int *v144; // eax
  int v145; // ecx
  int v146; // edx
  int v147; // eax
  int v148; // eax
  int v149; // ecx
  int actingUnitPtr; // esi
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
  int result; // [esp+0h] [ebp-E0h]
  __int16 savedOccupant; // [esp+Ch] [ebp-D4h]
  __int16 v169; // [esp+10h] [ebp-D0h]
  int enemyRow; // [esp+14h] [ebp-CCh]
  DWORD targetRow; // [esp+18h] [ebp-C8h]
  int enemyCol; // [esp+1Ch] [ebp-C4h]
  int v173; // [esp+20h] [ebp-C0h]
  int v174; // [esp+20h] [ebp-C0h]
  int unitScoreBase; // [esp+28h] [ebp-B8h]
  __int16 v176; // [esp+2Ch] [ebp-B4h]
  int enemyScanOffset; // [esp+30h] [ebp-B0h]
  DWORD enemyIndex; // [esp+34h] [ebp-ACh]
  int unitRecordOffset; // [esp+3Ch] [ebp-A4h]
  int pathCost; // [esp+40h] [ebp-A0h]
  int pathEntry; // [esp+40h] [ebp-A0h]
  __int16 savedUnitRow; // [esp+50h] [ebp-90h]
  __int16 savedUnitCol; // [esp+54h] [ebp-8Ch]
  int targetCol; // [esp+64h] [ebp-7Ch]
  int actingUnitOffset; // [esp+6Ch] [ebp-74h]
  __int16 v187; // [esp+70h] [ebp-70h]
  __int16 v188; // [esp+74h] [ebp-6Ch]
  __int16 v189; // [esp+78h] [ebp-68h]
  __int16 v190; // [esp+7Ch] [ebp-64h]
  __int16 v191; // [esp+80h] [ebp-60h]
  __int16 v192; // [esp+84h] [ebp-5Ch]
  __int16 v193; // [esp+88h] [ebp-58h]
  int scoreGridBase; // [esp+8Ch] [ebp-54h]
  __int16 v195; // [esp+90h] [ebp-50h]
  __int16 v196; // [esp+94h] [ebp-4Ch]
  __int16 v197; // [esp+98h] [ebp-48h]
  __int16 savedTileOccupant; // [esp+A0h] [ebp-40h]
  int v199; // [esp+A4h] [ebp-3Ch]
  int v200; // [esp+A4h] [ebp-3Ch]
  int v201; // [esp+A8h] [ebp-38h]
  int v202; // [esp+A8h] [ebp-38h]
  int v203; // [esp+ACh] [ebp-34h]
  int v204; // [esp+ACh] [ebp-34h]
  int enemyRecordOffset; // [esp+B4h] [ebp-2Ch]
  int v206; // [esp+B8h] [ebp-28h]
  int v207; // [esp+B8h] [ebp-28h]
  int trackTargetCol; // [esp+BCh] [ebp-24h]
  int v209; // [esp+C0h] [ebp-20h]
  int v210; // [esp+C0h] [ebp-20h]
  int enemyScanIndex; // [esp+C4h] [ebp-1Ch]

  result = 1;
  switch ( g_UnitBattleAiCurrentPlanMode )
  {
    case BATTLE_AI_PLAN_HOLD:
    case BATTLE_AI_PLAN_DISENGAGE:
      goto LABEL_29;
    case BATTLE_AI_PLAN_ADVANCE:
      unitScoreBase = 801 * unitIndex;
      enemyScanIndex = 0;
      enemyScanOffset = 0;
      actingUnitOffset = 31 * unitIndex;
      do
      {
        if ( *(__int16 *)(enemyScanOffset + g_MapData + 852) != -1 && *(unsigned __int8 *)(enemyScanOffset + g_MapData + 854) != side )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          result = 0;
          targetRow = *(unsigned __int16 *)(g_MapData + enemyScanOffset + 856);
          targetCol = *(unsigned __int16 *)(g_MapData + enemyScanOffset + 858);
          v140 = 160 * targetRow + unitScoreBase * 4;
          v141 = 2 * targetCol + g_MapData + 40 * targetRow;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(g_MapData + enemyScanOffset + 852)]];
          v142 = *(_WORD *)(v141 + 1534);
          *(_WORD *)(v141 + 1534) = -1;
          savedTileOccupant = v142;
          tileScore = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) - 800;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) = tileScore;
          v144 = UnitBattle_EstimateDamageScoreAgainstUnit(unitIndex, enemyScanIndex);
          v146 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) - 15 * (_DWORD)v144;
          v147 = enemyScanOffset + g_MapData;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146 - 2 * *(unsigned __int8 *)(v147 + 860);
          v148 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(enemyScanIndex, side, tileScore);
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v149] + v140) -= 2 * v148;
          trackTargetCol = v149;
          Debug_Log(v149, v140, targetRow, (int)aOddzial_w_zasi);
          actingUnitPtr = actingUnitOffset + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(unitIndex, v151, v152)
            && (*(_BYTE *)(actingUnitOffset + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(actingUnitOffset + g_MapData + 864)) >> 5) > 0 )
          {
            v153 = 0;
LABEL_278:
            LOBYTE(v153) = *(_BYTE *)(actingUnitPtr + 8);
            goto LABEL_279;
          }
          v154 = trackTargetCol;
          if ( *(char *)(trackTargetCol + g_MapData + 20 * targetRow + 3134) <= 0 )
          {
            v156 = trackTargetCol;
          }
          else
          {
            v154 = g_MapData + 40 * targetRow;
            if ( *(__int16 *)(v154 + 2 * trackTargetCol + 1534) == -1
              || (v155 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v155 + 852)] & 1) == 0)
              && (*(_BYTE *)(v155 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v155 + 864)) >> 5) <= 0 )
            {
              v157 = UnitBattle_MoveTrackNearWall(unitIndex, targetRow, trackTargetCol, targetRow);
              goto LABEL_289;
            }
            v156 = trackTargetCol;
          }
          v157 = (int *)UnitBattle_MoveTrackNear(unitIndex, v154, v156, targetRow);
LABEL_289:
          v158 = v157;
          if ( !v157 )
          {
            v159 = g_MapData + 31 * unitIndex;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v159 + 852)] )
            {
              if ( (*(_BYTE *)(v159 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v159 + 864)) >> 5) > 0 )
                v158 = UnitBattle_MoveTrackForce(unitIndex, trackTargetCol, targetRow);
            }
          }
          if ( !v158 )
            goto LABEL_294;
          if ( !*v158 )
          {
            j__nfree_();
            goto LABEL_278;
          }
          v160 = 31 * unitIndex + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v160 + 852)]
            && (*(_BYTE *)(v160 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v160 + 864)) >> 5) > 0 )
          {
            v176 = *(_WORD *)(actingUnitPtr + 4);
            HIWORD(v174) = 0;
            v169 = *(_WORD *)(actingUnitPtr + 6);
            if ( *v158 )
            {
              while ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, trackTargetCol) )
              {
                v165 = *v162 - 1;
                *v162 = v165;
                v174 = v162[v165 + 1];
                if ( HIWORD(v174) > (int)*(unsigned __int8 *)(actingUnitPtr + 8) )
                  goto LABEL_317;
                *(_WORD *)(actingUnitPtr + 4) = (unsigned __int8)v174;
                *(_WORD *)(actingUnitPtr + 6) = BYTE1(v174);
                if ( !*v162 )
                  goto LABEL_314;
              }
              *(_WORD *)(actingUnitPtr + 4) = v176;
              *(_WORD *)(actingUnitPtr + 6) = v169;
              j__nfree_();
              LOWORD(v163) = HIWORD(v174);
              v164 = *(unsigned __int8 *)(actingUnitPtr + 8);
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
            if ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, trackTargetCol) )
            {
LABEL_317:
              *(_WORD *)(actingUnitPtr + 4) = v176;
              *(_WORD *)(actingUnitPtr + 6) = v169;
              j__nfree_();
              goto LABEL_280;
            }
            *(_WORD *)(actingUnitPtr + 4) = v176;
            *(_WORD *)(actingUnitPtr + 6) = v169;
            if ( *(unsigned __int8 *)(actingUnitPtr + 8) > (int)HIWORD(v174) )
            {
              j__nfree_();
              v153 = *(unsigned __int8 *)(actingUnitPtr + 8) - v166;
LABEL_279:
              if ( v153 > -1 )
              {
LABEL_280:
                g_UnitBattleTileScoreGrid[40 * targetRow + 2 * targetCol + unitScoreBase] -= 5 * (v153 / 5);
LABEL_281:
                *(_WORD *)(40 * targetRow + g_MapData + 2 * targetCol + 1534) = savedTileOccupant;
                goto LABEL_282;
              }
LABEL_294:
              g_UnitBattleTileScoreGrid[40 * targetRow + 2 * targetCol + unitScoreBase] += 700;
              goto LABEL_281;
            }
          }
          else if ( *v158 )
          {
            v173 = v158[1];
            j__nfree_();
            LOBYTE(v161) = *(_BYTE *)(actingUnitPtr + 8);
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
        enemyScanOffset += 31;
        ++enemyScanIndex;
      }
      while ( enemyScanIndex < 22 );
      return result;
    case BATTLE_AI_PLAN_RANGED_ENGAGE:
    case BATTLE_AI_PLAN_INITIAL_SWEEP:
      if ( side == *(_DWORD *)(g_MapData + 836) )
      {
        if ( g_AttackerStartsOnLeft == 1 )
          advanceDir = 1;
        else
          advanceDir = -1;
      }
      if ( side == *(_DWORD *)(g_MapData + 840) )
      {
        if ( g_DefenderStartsOnLeft == 1 )
          advanceDir = 1;
        else
          advanceDir = -1;
      }
      scoreGridUnitBase = 801 * unitIndex;
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(31 * unitIndex + g_MapData + 852),
             *(unsigned __int16 *)(31 * unitIndex + g_MapData + 856) + 3 * advanceDir,
             *(unsigned __int16 *)(31 * unitIndex + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[120 * advanceDir
                   + 40 * *(unsigned __int16 *)(g_MapData + v5 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v5 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v5 + g_MapData + 852),
             4 * advanceDir + *(unsigned __int16 *)(v5 + g_MapData + 856),
             *(unsigned __int16 *)(v5 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[160 * advanceDir
                   + 40 * *(unsigned __int16 *)(g_MapData + v8 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v8 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v8 + g_MapData + 852),
             2 * advanceDir + *(unsigned __int16 *)(v8 + g_MapData + 856),
             *(unsigned __int16 *)(v8 + g_MapData + 858)) )
      {
        v10 = g_MapData + v9;
        v11 = 160 * (*(unsigned __int16 *)(v10 + 856) + 2 * advanceDir) + scoreGridUnitBase * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(v10 + 858)] + v11) -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(v9 + g_MapData + 852),
             5 * advanceDir + *(unsigned __int16 *)(v9 + g_MapData + 856),
             *(unsigned __int16 *)(v9 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[200 * advanceDir
                   + 40 * *(unsigned __int16 *)(g_MapData + v12 + 856)
                   + 2 * *(unsigned __int16 *)(g_MapData + v12 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      a3 = *(unsigned __int16 *)(v12 + g_MapData + 856);
      advanceOffset6 = 6 * advanceDir;
      if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(v12 + g_MapData + 852), advanceOffset6 + a3, *(unsigned __int16 *)(v12 + g_MapData + 858)) )
      {
        v19 = g_MapData + v14;
        v20 = 160 * (advanceOffset6 + *(unsigned __int16 *)(v19 + 856)) + scoreGridUnitBase * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(v19 + 858)] + v20) -= 500;
        return 0;
      }
      for ( i = 0; i < 682; i += 31 )
      {
        scanRecordPtr = i + g_MapData;
        if ( *(__int16 *)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(scanRecordPtr + 854) != side )
        {
          scanTrackPath = (int *)UnitBattle_MoveTrackNear(unitIndex, i, *(unsigned __int16 *)(scanRecordPtr + 858), a3);
          if ( scanTrackPath && *scanTrackPath > 3 )
          {
            pathNode = scanTrackPath[*scanTrackPath - 3];
            g_UnitBattleTileScoreGrid[801 * unitIndex + 40 * (unsigned __int8)pathNode + 2 * BYTE1(pathNode)] -= 500;
            j__nfree_();
            return 0;
          }
          if ( scanTrackPath )
            j__nfree_();
        }
      }
LABEL_29:
      scoreGridBase = 801 * unitIndex;
      enemyIndex = 0;
      enemyRecordOffset = 0;
      unitRecordOffset = 31 * unitIndex;
      break;
    default:
      return result;
  }
  while ( 1 )
  {
    if ( *(__int16 *)(enemyRecordOffset + g_MapData + 852) == -1 || *(unsigned __int8 *)(enemyRecordOffset + g_MapData + 854) == side )
      goto LABEL_39;
    UnitBattle_UpdateIdleAnimatedUnits();
    enemyRow = *(unsigned __int16 *)(g_MapData + enemyRecordOffset + 856);
    enemyCol = *(unsigned __int16 *)(g_MapData + enemyRecordOffset + 858);
    result = 0;
    scoreRowByteOffset = 160 * enemyRow + scoreGridBase * 4;
    occupantCellPtr = 40 * enemyRow + g_MapData + 2 * enemyCol;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * enemyCol] + scoreRowByteOffset) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88
                                                                                               * *(__int16 *)(g_MapData + enemyRecordOffset + 852)]];
    v23 = *(_WORD *)(occupantCellPtr + 1534);
    *(_WORD *)(occupantCellPtr + 1534) = -1;
    savedOccupant = v23;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * enemyCol] + scoreRowByteOffset) -= 800;
    v24 = UnitBattle_EstimateDamageScoreAgainstUnit(unitIndex, enemyIndex);
    v26 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) - 15 * (_DWORD)v24;
    v27 = enemyRecordOffset + g_MapData;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) = v26;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) = v26 - 2 * *(unsigned __int8 *)(v27 + 860);
    v28 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(enemyIndex, side, a3);
    v30 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + scoreRowByteOffset) - 2 * v28;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + scoreRowByteOffset) = v30;
    Debug_Log(v29, scoreRowByteOffset, v30, (int)aOddzial_w_zasi);
    unitRecordPtr = unitRecordOffset + g_MapData + 852;
    a3 = v32;
    if ( UnitBattle_IsTileWithinRange(unitIndex, v33, v32)
      && (*(_BYTE *)(unitRecordOffset + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
    {
      moveScoreDelta = 0;
LABEL_35:
      LOBYTE(moveScoreDelta) = *(_BYTE *)(unitRecordPtr + 8);
      goto LABEL_36;
    }
    trackRowArg = enemyRow;
    if ( *(char *)(g_MapData + 20 * enemyRow + a3 + 3134) <= 0 )
    {
      trackColArg = a3;
    }
    else
    {
      trackRowArg = g_MapData + 40 * enemyRow;
      if ( *(__int16 *)(trackRowArg + 2 * a3 + 1534) == -1
        || (v84 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v84 + 852)] & 1) == 0)
        && (*(_BYTE *)(v84 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v84 + 864)) >> 5) <= 0 )
      {
        trackPath = UnitBattle_MoveTrackNearWall(unitIndex, enemyRow, a3, a3);
        goto LABEL_83;
      }
      trackColArg = a3;
    }
    trackPath = (int *)UnitBattle_MoveTrackNear(unitIndex, trackRowArg, trackColArg, a3);
LABEL_83:
    trackPathPtr = trackPath;
    if ( !trackPath )
    {
      v88 = 31 * unitIndex + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v88 + 852)] )
      {
        if ( (*(_BYTE *)(v88 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v88 + 864)) >> 5) > 0 )
          trackPathPtr = UnitBattle_MoveTrackForce(unitIndex, a3, a3);
      }
    }
    if ( !trackPathPtr )
    {
LABEL_88:
      g_UnitBattleTileScoreGrid[40 * enemyRow + 2 * enemyCol + scoreGridBase] += 700;
      goto LABEL_38;
    }
    if ( !*trackPathPtr )
    {
      j__nfree_();
      goto LABEL_35;
    }
    v89 = g_MapData + 31 * unitIndex;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v89 + 852)]
      && (*(_BYTE *)(v89 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v89 + 864)) >> 5) > 0 )
    {
      savedUnitRow = *(_WORD *)(unitRecordPtr + 4);
      HIWORD(pathEntry) = 0;
      savedUnitCol = *(_WORD *)(unitRecordPtr + 6);
      if ( *trackPathPtr )
      {
        while ( !UnitBattle_IsTileWithinRange(unitIndex, enemyRow, a3) )
        {
          v93 = *v91 - 1;
          *v91 = v93;
          pathEntry = v91[v93 + 1];
          if ( HIWORD(pathEntry) > (int)*(unsigned __int8 *)(unitRecordPtr + 8) )
            goto LABEL_111;
          *(_WORD *)(unitRecordPtr + 4) = (unsigned __int8)pathEntry;
          *(_WORD *)(unitRecordPtr + 6) = BYTE1(pathEntry);
          if ( !*v91 )
            goto LABEL_108;
        }
        *(_WORD *)(unitRecordPtr + 4) = savedUnitRow;
        *(_WORD *)(unitRecordPtr + 6) = savedUnitCol;
        j__nfree_();
        LOBYTE(v92) = *(_BYTE *)(unitRecordPtr + 8);
        if ( v92 <= HIWORD(pathEntry) )
          goto LABEL_105;
        moveScoreDelta = v92 - HIWORD(pathEntry);
      }
      else
      {
LABEL_108:
        if ( !UnitBattle_IsTileWithinRange(unitIndex, enemyRow, a3) )
        {
LABEL_111:
          *(_WORD *)(unitRecordPtr + 4) = savedUnitRow;
          *(_WORD *)(unitRecordPtr + 6) = savedUnitCol;
          j__nfree_();
          goto LABEL_37;
        }
        *(_WORD *)(unitRecordPtr + 4) = savedUnitRow;
        *(_WORD *)(unitRecordPtr + 6) = savedUnitCol;
        if ( *(unsigned __int8 *)(unitRecordPtr + 8) <= (int)HIWORD(pathEntry) )
        {
LABEL_104:
          j__nfree_();
LABEL_105:
          moveScoreDelta = 0;
          goto LABEL_37;
        }
        j__nfree_();
        moveScoreDelta = *(unsigned __int8 *)(unitRecordPtr + 8) - v94;
      }
    }
    else
    {
      if ( !*trackPathPtr )
        goto LABEL_104;
      pathCost = trackPathPtr[1];
      j__nfree_();
      LOBYTE(v90) = *(_BYTE *)(unitRecordPtr + 8);
      if ( v90 <= HIWORD(pathCost) )
      {
        moveScoreDelta = 0;
        goto LABEL_37;
      }
      moveScoreDelta = v90 - HIWORD(pathCost);
    }
LABEL_36:
    if ( moveScoreDelta <= -1 )
      goto LABEL_88;
LABEL_37:
    g_UnitBattleTileScoreGrid[40 * enemyRow + 2 * enemyCol + scoreGridBase] -= 5 * (moveScoreDelta / 5);
LABEL_38:
    *(_WORD *)(g_MapData + 40 * enemyRow + 2 * enemyCol + 1534) = savedOccupant;
LABEL_39:
    enemyRecordOffset += 31;
    if ( (int)++enemyIndex >= 22 )
    {
      v35 = g_UnitBattleWallScanTileRow;
      if ( g_UnitBattleWallScanTileRow <= 0 || *(unsigned __int16 *)(g_MapData + 31 * unitIndex + 856) == g_UnitBattleWallScanTileRow )
        return result;
      v36 = g_BattleWallScanColumn;
      if ( *(char *)(g_BattleWallScanColumn + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
        goto LABEL_49;
      Debug_Log(31 * unitIndex, g_BattleWallScanColumn, g_UnitBattleWallScanTileRow, (int)aOddzial_w_zasi);
      v38 = v37 + g_MapData + 852;
      v39 = v36;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v36)
        && (*(_BYTE *)(v40 + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(v40 + g_MapData + 864)) >> 5) > 0 )
      {
        v41 = 0;
        goto LABEL_46;
      }
      if ( *(char *)(v36 + g_MapData + 20 * v35 + 3134) <= 0
        || *(__int16 *)(g_MapData + 40 * v35 + 2 * v36 + 1534) != -1
        && ((v95 = g_MapData + 31 * unitIndex, (g_UnitTypeFlags[22 * *(__int16 *)(v95 + 852)] & 1) != 0)
         || (*(_BYTE *)(v95 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v95 + 864)) >> 5) > 0) )
      {
        v96 = (int *)UnitBattle_MoveTrackNear(unitIndex, g_MapData, v36, v35);
      }
      else
      {
        v96 = UnitBattle_MoveTrackNearWall(unitIndex, v35, v36, v35);
      }
      v97 = v96;
      if ( !v96 )
      {
        LOBYTE(v36) = g_MapData;
        v98 = g_MapData + 31 * unitIndex;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v98 + 852)] )
        {
          v36 = *(_BYTE *)(v98 + 864) & 3;
          if ( v36 + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v98 + 864)) >> 5) > 0 )
          {
            LOBYTE(v36) = v39;
            v97 = UnitBattle_MoveTrackForce(unitIndex, v39, v35);
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
        v50 = 31 * unitIndex + g_MapData + 852;
        if ( UnitBattle_IsTileWithinRange(unitIndex, v48, v49) )
        {
          LOBYTE(v36) = 31 * unitIndex;
          if ( (*(_BYTE *)(31 * unitIndex + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
          {
            v51 = 0;
            goto LABEL_53;
          }
        }
        v105 = g_MapData;
        if ( *(char *)(g_MapData + 20 * v48 + v35 + 3134) <= 0
          || *(__int16 *)(g_MapData + 40 * v48 + 2 * v35 + 1534) != -1
          && ((v105 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v105 + 852)] & 1) != 0)
           || (*(_BYTE *)(v105 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v105 + 864)) >> 5) > 0) )
        {
          LOBYTE(v36) = v35;
          v106 = (int *)UnitBattle_MoveTrackNear(unitIndex, v105, v35, v35);
        }
        else
        {
          LOBYTE(v36) = v35;
          v106 = UnitBattle_MoveTrackNearWall(unitIndex, v48, v35, v35);
        }
        v107 = v106;
        if ( !v106 )
        {
          v36 = 31 * unitIndex + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
          {
            if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
            {
              LOBYTE(v36) = v35;
              v107 = UnitBattle_MoveTrackForce(unitIndex, v35, v35);
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
          v57 = 31 * unitIndex + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(unitIndex, v55, v56) )
          {
            LOBYTE(v36) = 31 * unitIndex;
            if ( (*(_BYTE *)(31 * unitIndex + g_MapData + 864) & 3)
               + 1
               - ((unsigned __int8)(2 * *(_BYTE *)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
            {
              v58 = 0;
              goto LABEL_60;
            }
          }
          v113 = g_MapData;
          if ( *(char *)(g_MapData + 20 * v55 + v35 + 3134) <= 0
            || *(__int16 *)(g_MapData + 40 * v55 + 2 * v35 + 1534) != -1
            && ((v113 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v113 + 852)] & 1) != 0)
             || (*(_BYTE *)(v113 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v113 + 864)) >> 5) > 0) )
          {
            LOBYTE(v36) = v35;
            v114 = (int *)UnitBattle_MoveTrackNear(unitIndex, v113, v35, v35);
          }
          else
          {
            LOBYTE(v36) = v35;
            v114 = UnitBattle_MoveTrackNearWall(unitIndex, v55, v35, v35);
          }
          v115 = v114;
          if ( !v114 )
          {
            v36 = 31 * unitIndex + g_MapData;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v36 + 852)] )
            {
              if ( (*(_BYTE *)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v36 + 864)) >> 5) > 0 )
              {
                LOBYTE(v36) = v35;
                v115 = UnitBattle_MoveTrackForce(unitIndex, v35, v35);
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
            Debug_Log(unitIndex, g_BattleWallScanColumn + 2, g_UnitBattleWallScanTileRow, (int)aOddzial_w_zasi);
            v63 = g_MapData + 852;
            v64 = UnitBattle_IsTileWithinRange(unitIndex, v35, v36);
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
              && ((v65 = unitIndex, v121 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v121 + 852)] & 1) != 0)
               || (*(_BYTE *)(v121 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v121 + 864)) >> 5) > 0) )
            {
              LOBYTE(v36) = v62;
              v122 = (int *)UnitBattle_MoveTrackNear(unitIndex, v65, v62, v35);
            }
            else
            {
              LOBYTE(v36) = v62;
              v122 = UnitBattle_MoveTrackNearWall(unitIndex, v35, v62, v35);
            }
            v123 = v122;
            if ( !v122 )
            {
              LOBYTE(v36) = g_MapData;
              v124 = g_MapData + 31 * unitIndex;
              if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v124 + 852)] )
              {
                if ( (*(_BYTE *)(v124 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v124 + 864)) >> 5) > 0 )
                {
                  LOBYTE(v36) = v62;
                  v123 = UnitBattle_MoveTrackForce(unitIndex, v62, v35);
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
                return result;
              Debug_Log(v72, v36, v35, (int)aOddzial_w_zasi);
              v74 = v73;
              v75 = v71;
              v76 = v71;
              v77 = 31 * unitIndex + g_MapData + 852;
              if ( UnitBattle_IsTileWithinRange(unitIndex, v73, v76)
                && (*(_BYTE *)(31 * unitIndex + g_MapData + 864) & 3)
                 + 1
                 - ((unsigned __int8)(2 * *(_BYTE *)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
              {
                v78 = 0;
                goto LABEL_74;
              }
              v130 = g_MapData;
              if ( *(char *)(v75 + g_MapData + 20 * v74 + 3134) <= 0
                || *(__int16 *)(g_MapData + 40 * v74 + 2 * v75 + 1534) != -1
                && ((v130 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v130 + 852)] & 1) != 0)
                 || (*(_BYTE *)(v130 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v130 + 864)) >> 5) > 0) )
              {
                v131 = (int *)UnitBattle_MoveTrackNear(unitIndex, v130, v75, v74);
              }
              else
              {
                v131 = UnitBattle_MoveTrackNearWall(unitIndex, v74, v75, v74);
              }
              v132 = v131;
              if ( !v131 )
              {
                v133 = 31 * unitIndex + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v133 + 852)] )
                {
                  if ( (*(_BYTE *)(v133 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v133 + 864)) >> 5) > 0 )
                    v132 = UnitBattle_MoveTrackForce(unitIndex, v75, v74);
                }
              }
              if ( !v132 )
                return result;
              if ( *v132 )
              {
                v134 = 31 * unitIndex + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(v134 + 852)]
                  && (*(_BYTE *)(v134 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v134 + 864)) >> 5) > 0 )
                {
                  v192 = *(_WORD *)(v77 + 4);
                  v195 = *(_WORD *)(v77 + 6);
                  HIWORD(v210) = 0;
                  if ( *v132 )
                  {
                    while ( !UnitBattle_IsTileWithinRange(unitIndex, v74, v75) )
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
                    v79 = 8 * g_BattleWallScanTileX + 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow;
                    v80 = *(int *)((char *)g_UnitBattleTileScoreGrid + v79) - 640 - 5 * (v78 / 5);
                    v81 = g_BattleWallScanTileX;
                    v82 = g_MapData + 20 * g_UnitBattleWallScanTileRow;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) -= 640;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = v80;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = *(char *)(v81 + v82 + 3134) + v80;
                    return result;
                  }
LABEL_268:
                  if ( !UnitBattle_IsTileWithinRange(unitIndex, v74, v75) )
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
              return result;
            }
            if ( !*v123 )
            {
              j__nfree_();
LABEL_67:
              LOBYTE(v67) = *(_BYTE *)(v66 + 8);
              goto LABEL_68;
            }
            v36 = 31 * unitIndex + g_MapData;
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
                  if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v62) )
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
                v68 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
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
              if ( !UnitBattle_IsTileWithinRange(unitIndex, v35, v62) )
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
          v36 = 31 * unitIndex + g_MapData;
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
                if ( UnitBattle_IsTileWithinRange(unitIndex, v55, v35) )
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
              v59 = 160 * g_UnitBattleWallScanTileRow + 3204 * unitIndex + 8 * g_BattleWallScanTileX;
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
            if ( !UnitBattle_IsTileWithinRange(unitIndex, v55, v35) )
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
        v36 = 31 * unitIndex + g_MapData;
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
              if ( UnitBattle_IsTileWithinRange(unitIndex, v48, v35) )
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
            v52 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
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
          if ( !UnitBattle_IsTileWithinRange(unitIndex, v48, v35) )
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
      v99 = g_MapData + 31 * unitIndex;
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
            if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v39) )
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
          v42 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanColumn;
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
        if ( !UnitBattle_IsTileWithinRange(unitIndex, v35, v39) )
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
int  WCIsvListBase_TransferAllInto(int result, int destList)
{
  int v3; // ecx
  int v4; // ecx

  if ( *(_DWORD *)(result + 8) )
  {
    WCIsvListBase_PopFrontValue(result, destList);
    WCIsvListBase_TransferAllInto(v3, destList);
    return WCIsvListBase_AppendValue(destList, v4);
  }
  return result;
}
// 43A823: variable 'v3' is possibly undefined
// 43A82C: variable 'v4' is possibly undefined

//----- (0043A880) --------------------------------------------------------
signed int __fastcall WCIsvListBase_PopUntilMatchOrEmpty(int matchValue, int list)
{
  int poppedValue; // eax
  int targetValue; // ecx

  if ( !*(_DWORD *)(list + 8) )
    return 0;
  while ( 1 )
  {
    poppedValue = WCIsvListBase_PopFrontValue(list, list);
    if ( poppedValue == targetValue )
      break;
    if ( !*(_DWORD *)(list + 8) )
      return 0;
  }
  return 1;
}
// 43A898: variable 'v4' is possibly undefined

//----- (0043A8B0) --------------------------------------------------------
signed int  UnitBattle_SelectAiActionForUnit(int unitIndex, int side)
{
  int unitRecordAddr; // eax
  int bestScore; // ebx
  int scanRow; // esi
  int scanCol; // eax
  int colByteOffset; // edx
  int scoreGridOffset; // ecx
  int cellStateBase; // ebp
  int attemptCount; // eax
  int rangedUnitRecord; // eax
  int targetCol; // ebp
  int unitRecordByteOffset; // ecx
  int unitRecordPtr; // edi
  int v15; // ecx
  int remainingMove; // eax
  int cellStateByteOffset; // ecx
  int *movePath; // edi
  DWORD scanSide; // ebp
  int recordOffset; // edx
  int i; // eax
  int recordAddr; // ecx
  int rowTileOffset; // esi
  int altMovePath; // ecx
  int j; // eax
  int moveAttemptCount; // eax
  int v27; // ecx
  int unitRecordForTrackCheck; // edx
  int trackUnitIndex; // eax
  int trackTargetCol; // ebx
  int *trackResult; // eax
  int *trackPath; // esi
  int unitRecordForForceTrack; // eax
  int unitRecordForFallback; // eax
  int unitRecordForPathTrace; // eax
  int maxMove; // edx
  int pathNodeCount; // edx
  int pathTopIndex; // eax
  int v39; // edx
  int moveCost; // edx
  int moveAllowance; // eax
  int *walkPath; // ecx
  int unitRecordForWalk; // eax
  int unitRecordOffset; // esi
  int walkTopIndex; // edi
  int walkUnitRecord; // eax
  int occupantAtTile; // edx
  int occupantSide; // eax
  int v49; // ecx
  WCIsvListBase *v50; // ecx
  bool shouldRetry; // bl
  int v52; // ecx
  int savedOccupants[66]; // [esp+0h] [ebp-164h]
  int candidateListCopy; // [esp+108h] [ebp-5Ch] BYREF
  void **candidateListVtable; // [esp+10Ch] [ebp-58h]
  int v56; // [esp+110h] [ebp-54h]
  int v57; // [esp+114h] [ebp-50h]
  int v58; // [esp+118h] [ebp-4Ch]
  int v59; // [esp+11Ch] [ebp-48h]
  int trackStep; // [esp+120h] [ebp-44h]
  int rowByteOffset; // [esp+124h] [ebp-40h]
  int savedRow; // [esp+128h] [ebp-3Ch]
  int sideCopy; // [esp+12Ch] [ebp-38h]
  int savedUnitCol; // [esp+130h] [ebp-34h]
  int savedUnitRow; // [esp+134h] [ebp-30h]
  int pathStep; // [esp+138h] [ebp-2Ch]
  int targetRow; // [esp+13Ch] [ebp-28h]
  int unitIndexCopy; // [esp+140h] [ebp-24h]
  int savedCol; // [esp+144h] [ebp-20h]
  int pathNode; // [esp+148h] [ebp-1Ch]
  int unitIndexSaved; // [esp+14Ch] [ebp-18h]

  unitIndexCopy = unitIndex;
  sideCopy = side;
  g_BattleTargetTileCol = -1;
  g_UnitBattleScanTileRow = -1;
  unitRecordAddr = g_MapData + 31 * unitIndex;
  bestScore = 0;
  if ( g_UnitTypeRole[88 * *(__int16 *)(unitRecordAddr + 852)] == 4
    && (*(_BYTE *)(unitRecordAddr + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordAddr + 864)) >> 5) <= 0 )
  {
    g_BattleCellStateGrid[801 * unitIndexCopy - 42] = 5;
    return 1;
  }
  scanRow = 0;
  rowByteOffset = 0;
  while ( scanRow < *(_DWORD *)(g_MapData + 804) )
  {
    scanCol = 0;
    colByteOffset = 0;
    while ( scanCol < *(_DWORD *)(g_MapData + 800) )
    {
      scoreGridOffset = colByteOffset + rowByteOffset + 3204 * unitIndexCopy;
      if ( bestScore > *(int *)((char *)g_UnitBattleTileScoreGrid + scoreGridOffset) )
      {
        g_UnitBattleScanTileRow = scanRow;
        g_BattleTargetTileCol = scanCol;
        bestScore = *(int *)((char *)g_UnitBattleTileScoreGrid + scoreGridOffset);
      }
      colByteOffset += 8;
      ++scanCol;
    }
    ++scanRow;
    rowByteOffset += 160;
  }
  if ( g_UnitBattleAiCurrentPlanMode == 2 || g_UnitBattleAiCurrentPlanMode == 6 )
  {
    g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 6;
    return 1;
  }
  cellStateBase = 801 * unitIndexCopy;
  if ( bestScore < 0 )
  {
    rangedUnitRecord = 31 * unitIndexCopy + g_MapData;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(rangedUnitRecord + 852)] )
    {
      if ( (*(_BYTE *)(rangedUnitRecord + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(rangedUnitRecord + 864)) >> 5) > 0 )
      {
        LOBYTE(bestScore) = g_BattleTargetTileCol;
        if ( UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
        {
          if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
            && *(unsigned __int8 *)(g_MapData + 31 * unitIndexCopy + 854) == *(_DWORD *)(g_MapData + 836)
            && *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534) == -1 )
          {
            g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] = 8;
            return 1;
          }
          else
          {
            g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 1;
            return 1;
          }
        }
      }
    }
    targetCol = g_BattleTargetTileCol;
    unitIndexSaved = unitIndexCopy;
    targetRow = g_UnitBattleScanTileRow;
    Debug_Log(31 * unitIndexCopy, bestScore, g_BattleTargetTileCol, (int)aOddzial_w_zasi);
    unitRecordPtr = g_MapData + 852 + unitRecordByteOffset;
    if ( UnitBattle_IsTileWithinRange(unitIndexCopy, targetRow, targetCol)
      && (*(_BYTE *)(g_MapData + v15 + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(g_MapData + v15 + 864)) >> 5) > 0 )
    {
      goto LABEL_24;
    }
    v27 = targetRow;
    if ( *(char *)(g_MapData + 20 * targetRow + targetCol + 3134) <= 0 )
    {
      trackUnitIndex = unitIndexSaved;
      trackTargetCol = targetCol;
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * targetRow + 2 * targetCol + 1534) == -1
        || (v27 = unitIndexSaved, unitRecordForTrackCheck = 31 * unitIndexSaved + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(unitRecordForTrackCheck + 852)] & 1) == 0)
        && (v27 = (*(_BYTE *)(unitRecordForTrackCheck + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForTrackCheck + 864)) >> 5), v27 <= 0) )
      {
        trackResult = UnitBattle_MoveTrackNearWall(unitIndexSaved, targetRow, targetCol, targetCol);
LABEL_58:
        trackPath = trackResult;
        if ( !trackResult )
        {
          unitRecordForForceTrack = g_MapData + 31 * unitIndexSaved;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForForceTrack + 852)] )
          {
            if ( (*(_BYTE *)(unitRecordForForceTrack + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForForceTrack + 864)) >> 5) > 0 )
              trackPath = UnitBattle_MoveTrackForce(unitIndexSaved, targetCol, targetCol);
          }
        }
        if ( !trackPath )
          goto LABEL_63;
        if ( *trackPath )
        {
          unitRecordForPathTrace = g_MapData + 31 * unitIndexSaved;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForPathTrace + 852)]
            && (*(_BYTE *)(unitRecordForPathTrace + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForPathTrace + 864)) >> 5) > 0 )
          {
            savedRow = *(unsigned __int16 *)(unitRecordPtr + 4);
            HIWORD(pathNode) = 0;
            pathNodeCount = *trackPath;
            savedCol = *(unsigned __int16 *)(unitRecordPtr + 6);
            if ( pathNodeCount )
            {
              while ( !UnitBattle_IsTileWithinRange(unitIndexSaved, targetRow, targetCol) )
              {
                pathTopIndex = *trackPath - 1;
                *trackPath = pathTopIndex;
                pathNode = trackPath[pathTopIndex + 1];
                if ( HIWORD(pathNode) > (int)*(unsigned __int8 *)(unitRecordPtr + 8) )
                  goto LABEL_86;
                *(_WORD *)(unitRecordPtr + 4) = (unsigned __int8)pathNode;
                *(_WORD *)(unitRecordPtr + 6) = BYTE1(pathNode);
                if ( !*trackPath )
                  goto LABEL_80;
              }
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
              j__nfree_();
              LOWORD(moveCost) = HIWORD(pathNode);
              moveAllowance = *(unsigned __int8 *)(unitRecordPtr + 8);
              if ( moveAllowance <= moveCost )
                goto LABEL_63;
              remainingMove = moveAllowance - moveCost;
              goto LABEL_25;
            }
LABEL_80:
            if ( UnitBattle_IsTileWithinRange(unitIndexSaved, targetRow, targetCol) )
            {
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
              if ( *(unsigned __int8 *)(unitRecordPtr + 8) > (int)HIWORD(pathNode) )
              {
                j__nfree_();
                remainingMove = *(unsigned __int8 *)(unitRecordPtr + 8) - v39;
LABEL_25:
                if ( remainingMove >= 5 )
                {
                  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
                    && *(unsigned __int8 *)(g_MapData + 31 * unitIndexCopy + 854) == *(_DWORD *)(g_MapData + 836)
                    && *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) == -1 )
                  {
                    cellStateByteOffset = 160 * g_UnitBattleScanTileRow + 3204 * unitIndexCopy;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + cellStateByteOffset) = 8;
                  }
                  else
                  {
                    cellStateByteOffset = 160 * g_UnitBattleScanTileRow + 3204 * unitIndexCopy;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + cellStateByteOffset) = 1;
                  }
                  goto LABEL_30;
                }
LABEL_63:
                unitRecordForFallback = g_MapData + 31 * unitIndexCopy;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForFallback + 852)]
                  && (*(_BYTE *)(unitRecordForFallback + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForFallback + 864)) >> 5) <= 0 )
                {
                  g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                  return 1;
                }
                cellStateByteOffset = 3204 * unitIndexCopy;
                g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 7;
LABEL_30:
                movePath = (int *)UnitBattle_MoveTrackNear(unitIndexCopy, cellStateByteOffset, g_BattleTargetTileCol, targetCol);
                if ( !movePath )
                  movePath = UnitBattle_MoveTrackForce(unitIndexCopy, g_BattleTargetTileCol, targetCol);
                if ( movePath && *movePath )
                {
                  scanSide = sideCopy;
                  recordOffset = 0;
                  for ( i = 0; i != 66; i += 3 )
                  {
                    savedOccupants[i] = -1;
                    recordAddr = g_MapData + recordOffset;
                    if ( *(unsigned __int8 *)(g_MapData + recordOffset + 854) == scanSide && *(__int16 *)(recordAddr + 852) != -1 )
                    {
                      savedOccupants[i] = *(__int16 *)(40 * *(unsigned __int16 *)(recordAddr + 856)
                                          + g_MapData
                                          + 2 * *(unsigned __int16 *)(recordAddr + 858)
                                          + 1534);
                      savedOccupants[i + 1] = *(unsigned __int16 *)(g_MapData + recordOffset + 856);
                      savedOccupants[i + 2] = *(unsigned __int16 *)(g_MapData + recordOffset + 858);
                      rowTileOffset = 40 * *(unsigned __int16 *)(g_MapData + recordOffset + 856);
                      recordAddr = rowTileOffset + g_MapData;
                      *(_WORD *)(rowTileOffset + g_MapData + 2 * *(unsigned __int16 *)(g_MapData + recordOffset + 858) + 1534) = -1;
                    }
                    recordOffset += 31;
                  }
                  altMovePath = UnitBattle_MoveTrackNear(unitIndexCopy, recordAddr, g_BattleTargetTileCol, scanSide);
                  for ( j = 0; j != 66; j += 3 )
                  {
                    if ( savedOccupants[j] != -1 )
                      *(_WORD *)(40 * savedOccupants[j + 1] + g_MapData + 2 * savedOccupants[j + 2] + 1534) = savedOccupants[j];
                  }
                  moveAttemptCount = g_BattleAiActionAttemptCount++;
                  if ( moveAttemptCount > 20 )
                  {
                    g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                    if ( altMovePath )
                      j__nfree_();
LABEL_123:
                    j__nfree_();
                    return 1;
                  }
                  trackStep = movePath[1];
                  if ( !altMovePath )
                    return 0;
                  pathStep = *(_DWORD *)(altMovePath + 4);
                  j__nfree_();
                  if ( HIWORD(pathStep) < HIWORD(trackStep) )
                  {
                    unitRecordForWalk = g_MapData + 31 * unitIndexCopy;
                    savedUnitRow = *(unsigned __int16 *)(unitRecordForWalk + 856);
                    savedUnitCol = *(unsigned __int16 *)(unitRecordForWalk + 858);
                    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForWalk + 852)]
                      && (*(_BYTE *)(unitRecordForWalk + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForWalk + 864)) >> 5) > 0
                      && UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                    {
                      return 1;
                    }
                    unitRecordOffset = 31 * unitIndexCopy;
                    while ( walkPath && *walkPath )
                    {
                      UnitBattle_UpdateIdleAnimatedUnits();
                      walkTopIndex = *walkPath - 1;
                      *walkPath = walkTopIndex;
                      pathStep = walkPath[walkTopIndex + 1];
                      walkUnitRecord = unitRecordOffset + g_MapData;
                      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)]
                        && (*(_BYTE *)(walkUnitRecord + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(walkUnitRecord + 864)) >> 5) > 0 )
                      {
                        *(_WORD *)(walkUnitRecord + 856) = (unsigned __int8)pathStep;
                        *(_WORD *)(g_MapData + unitRecordOffset + 858) = BYTE1(pathStep);
                        if ( *(__int16 *)(40 * (unsigned __int8)pathStep + g_MapData + 2 * BYTE1(pathStep) + 1534) == -1
                          && UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                        {
                          *(_WORD *)(unitRecordOffset + g_MapData + 856) = savedUnitRow;
                          *(_WORD *)(g_MapData + unitRecordOffset + 858) = savedUnitCol;
                          if ( !walkPath )
                            return 1;
                          goto LABEL_123;
                        }
                        *(_WORD *)(unitRecordOffset + g_MapData + 856) = savedUnitRow;
                        *(_WORD *)(unitRecordOffset + g_MapData + 858) = savedUnitCol;
                      }
                      occupantAtTile = *(__int16 *)(g_MapData + 40 * (unsigned __int8)pathStep + 2 * BYTE1(pathStep) + 1534);
                      if ( occupantAtTile != -1 )
                      {
                        occupantSide = *(unsigned __int8 *)(31 * occupantAtTile + g_MapData + 854);
                        if ( occupantSide == sideCopy )
                        {
                          candidateListCopy = 0;
                          v56 = sideCopy ^ occupantSide;
                          v57 = 0;
                          v58 = 0;
                          candidateListVtable = &g_WCIsvListBaseVariant124_Vtable;
                          v59 = 0;
                          WCIsvListBase_CopyAppendAll(&candidateListCopy, &g_UnitBattleAiCandidateQueue, (int)walkPath);
                          candidateListVtable = &g_WCIsvListBaseVariant134_Vtable;
                          shouldRetry = WCIsvListBase_PopUntilMatchOrEmpty(v49, (int)&candidateListCopy) && g_BattleAiActionAttemptCount < 20;
                          WCIsvListBase_DestroyElementsAndDtor(v50, (int)&candidateListCopy);
                          if ( shouldRetry )
                          {
                            if ( v52 )
                              j__nfree_();
                            return 0;
                          }
                          if ( !v52 )
                            return 1;
                        }
                        else if ( !walkPath )
                        {
                          return 1;
                        }
                        goto LABEL_123;
                      }
                    }
                  }
                  if ( walkPath )
                    goto LABEL_123;
                }
                else if ( movePath )
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
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
            }
          }
          else if ( *trackPath )
          {
            pathNode = trackPath[1];
            j__nfree_();
            LOBYTE(maxMove) = *(_BYTE *)(unitRecordPtr + 8);
            if ( maxMove <= HIWORD(pathNode) )
              goto LABEL_63;
            remainingMove = maxMove - HIWORD(pathNode);
            goto LABEL_25;
          }
          j__nfree_();
          goto LABEL_63;
        }
        j__nfree_();
LABEL_24:
        remainingMove = *(unsigned __int8 *)(unitRecordPtr + 8);
        goto LABEL_25;
      }
      trackUnitIndex = unitIndexSaved;
      trackTargetCol = targetCol;
    }
    trackResult = (int *)UnitBattle_MoveTrackNear(trackUnitIndex, v27, trackTargetCol, targetCol);
    goto LABEL_58;
  }
  attemptCount = g_BattleAiActionAttemptCount++;
  if ( attemptCount < 20 )
    return 0;
  g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] = 5;
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
int  UnitBattle_ApproachToSafeDistance(int unitIndex, int a2, char a3, int a4)
{
  int v4; // edx
  int v5; // edx
  int mapScanBase; // ecx
  __int16 targetCol; // bx
  int nearTrackPtr; // eax
  int v9; // ecx
  int v10; // ebx
  int v12; // eax
  int *v13; // eax
  _DWORD *trackPath; // eax
  int occupantRecordOffset; // edx
  int enemyIndex; // edi
  int enemyRecordPtr; // esi
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int *enemyTrack; // eax
  int *enemyTrackPath; // ecx
  int enemyMapBase; // eax
  int enemyRecordBase; // eax
  int v26; // edx
  int *v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int *v32; // eax
  int trackStep; // [esp+4h] [ebp-40h]
  int movePoints; // [esp+8h] [ebp-3Ch]
  int effectiveness; // [esp+10h] [ebp-34h]
  int unitRecordPtr; // [esp+14h] [ebp-30h]
  __int16 savedCol; // [esp+18h] [ebp-2Ch]
  __int16 savedRow; // [esp+1Ch] [ebp-28h]
  int enemyPathStep; // [esp+24h] [ebp-20h]
  int pathStep; // [esp+24h] [ebp-20h]
  unsigned __int8 destRow; // [esp+28h] [ebp-1Ch]
  unsigned __int8 destCol; // [esp+2Ch] [ebp-18h]

  Debug_Log(a2, a3, a4, (int)aPodejdz_na_bez);
  v5 = 31 * v4 + g_MapData + 852;
  movePoints = *(unsigned __int8 *)(v5 + 8);
  unitRecordPtr = v5;
  mapScanBase = 40 * g_UnitBattleScanTileRow + g_MapData;
  if ( *(__int16 *)(mapScanBase + 2 * g_BattleTargetTileCol + 1534) == -1 )
  {
    targetCol = g_BattleTargetTileCol;
    nearTrackPtr = UnitBattle_MoveTrackNear(unitIndex, mapScanBase, g_BattleTargetTileCol, a4);
    *(_DWORD *)(unitRecordPtr + 23) = nearTrackPtr;
    if ( !nearTrackPtr )
    {
      targetCol = g_BattleTargetTileCol;
      *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, a4);
    }
    if ( *(_DWORD *)(unitRecordPtr + 23) )
      UnitBattle_Move(unitIndex, v9, targetCol, a4);
    v10 = *(_DWORD *)(unitRecordPtr + 23);
    if ( v10 )
      goto LABEL_7;
    goto LABEL_8;
  }
  LOWORD(v10) = g_BattleTargetTileCol;
  v12 = UnitBattle_MoveTrackNear(unitIndex, mapScanBase, g_BattleTargetTileCol, a4);
  *(_DWORD *)(unitRecordPtr + 23) = v12;
  if ( !v12 )
  {
    LOWORD(v10) = g_BattleTargetTileCol;
    *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, a4);
  }
  if ( *(_DWORD *)(unitRecordPtr + 23) )
  {
    a4 = 0;
    destRow = -1;
    HIWORD(trackStep) = 0;
    effectiveness = 0;
    while ( 1 )
    {
      if ( !**(_DWORD **)(unitRecordPtr + 23) || HIWORD(trackStep) + 5 > movePoints )
      {
        if ( *(_DWORD *)(unitRecordPtr + 23) )
          j__nfree_();
        v9 = destRow;
        *(_DWORD *)(unitRecordPtr + 23) = 0;
        if ( destRow != 255 )
        {
          LOWORD(v10) = destCol;
          v13 = UnitBattle_MoveTrack(unitIndex, destRow, destRow, destCol, a4);
          *(_DWORD *)(unitRecordPtr + 23) = v13;
          if ( !v13 )
          {
            LOWORD(v10) = destCol;
            *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, destCol, a4);
          }
        }
        if ( *(_DWORD *)(unitRecordPtr + 23) )
          UnitBattle_Move(unitIndex, v9, v10, a4);
        if ( !*(_DWORD *)(unitRecordPtr + 23) )
          goto LABEL_8;
LABEL_7:
        j__nfree_();
        *(_DWORD *)(unitRecordPtr + 23) = 0;
LABEL_8:
        UnitBattle_Defence(v9, v10, a4);
        return 0;
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      trackPath = *(_DWORD **)(unitRecordPtr + 23);
      a4 = *trackPath - 1;
      *trackPath = a4;
      trackStep = trackPath[a4 + 1];
      if ( HIWORD(trackStep) + 5 <= movePoints )
      {
        destCol = BYTE1(trackPath[a4 + 1]);
        destRow = trackPath[a4 + 1];
      }
      occupantRecordOffset = 31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534);
      v10 = (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(g_MapData + occupantRecordOffset + 852)];
      if ( v10 != 4 )
        break;
LABEL_35:
      if ( v9 * effectiveness > 20 )
      {
        if ( destRow == 255 )
        {
          a4 = *(_DWORD *)(unitRecordPtr + 23);
          if ( !a4 )
            goto LABEL_8;
        }
        else
        {
          if ( *(_DWORD *)(unitRecordPtr + 23) )
            j__nfree_();
          LOWORD(v10) = destCol;
          *(_DWORD *)(unitRecordPtr + 23) = 0;
          v32 = UnitBattle_MoveTrack(unitIndex, destRow, destRow, destCol, a4);
          *(_DWORD *)(unitRecordPtr + 23) = v32;
          if ( !v32 )
          {
            LOWORD(v10) = destCol;
            *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, destCol, a4);
          }
          if ( *(_DWORD *)(unitRecordPtr + 23) )
            UnitBattle_Move(unitIndex, v9, v10, a4);
          if ( !*(_DWORD *)(unitRecordPtr + 23) )
            goto LABEL_8;
        }
        goto LABEL_7;
      }
    }
    effectiveness = Unit_CalcEffectivenessA((char *)(occupantRecordOffset + g_MapData + 852), 0);
    if ( effectiveness < Unit_CalcEffectivenessC((__int16 *)(31
                                                 * *(__int16 *)(g_MapData
                                                              + 40 * g_UnitBattleScanTileRow
                                                              + 2 * g_BattleTargetTileCol
                                                              + 1534)
                                                 + g_MapData
                                                 + 852)) )
      effectiveness = Unit_CalcEffectivenessC((__int16 *)(31
                                              * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                                              + g_MapData
                                              + 852));
    LOWORD(v10) = BYTE1(trackStep);
    enemyIndex = *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
    Debug_Log(enemyIndex, SBYTE1(trackStep), a4, (int)aOddzial_w_zasi);
    enemyRecordPtr = g_MapData + 852 + 31 * enemyIndex;
    a4 = v18;
    if ( UnitBattle_IsTileWithinRange(v19, v18, BYTE1(trackStep))
      && (*(_BYTE *)(31 * enemyIndex + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(31 * enemyIndex + g_MapData + 864)) >> 5) > 0 )
    {
      v20 = 0;
LABEL_33:
      LOBYTE(v20) = *(_BYTE *)(enemyRecordPtr + 8);
LABEL_34:
      v9 = v20 / 5;
      goto LABEL_35;
    }
    if ( *(char *)(BYTE1(trackStep) + g_MapData + 20 * a4 + 3134) <= 0 )
    {
      v10 = BYTE1(trackStep);
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * a4 + 2 * BYTE1(trackStep) + 1534) == -1
        || (v21 = 31 * enemyIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v21 + 852)] & 1) == 0)
        && (*(_BYTE *)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v21 + 864)) >> 5) <= 0 )
      {
        LOWORD(v10) = BYTE1(trackStep);
        enemyTrack = UnitBattle_MoveTrackNearWall(enemyIndex, a4, BYTE1(trackStep), a4);
        goto LABEL_44;
      }
      v10 = BYTE1(trackStep);
    }
    enemyTrack = (int *)UnitBattle_MoveTrackNear(enemyIndex, BYTE1(trackStep), v10, a4);
LABEL_44:
    enemyTrackPath = enemyTrack;
    if ( !enemyTrack )
    {
      enemyMapBase = 31 * enemyIndex + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyMapBase + 852)] )
      {
        if ( (*(_BYTE *)(enemyMapBase + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyMapBase + 864)) >> 5) > 0 )
        {
          LOWORD(v10) = BYTE1(trackStep);
          enemyTrackPath = UnitBattle_MoveTrackForce(enemyIndex, BYTE1(trackStep), a4);
        }
      }
    }
    if ( !enemyTrackPath )
    {
      v20 = -1;
      goto LABEL_34;
    }
    if ( !*enemyTrackPath )
    {
      j__nfree_();
      goto LABEL_33;
    }
    enemyRecordBase = g_MapData + 31 * enemyIndex;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyRecordBase + 852)]
      && (*(_BYTE *)(enemyRecordBase + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyRecordBase + 864)) >> 5) > 0 )
    {
      savedRow = *(_WORD *)(enemyRecordPtr + 4);
      HIWORD(pathStep) = 0;
      savedCol = *(_WORD *)(enemyRecordPtr + 6);
      if ( *enemyTrackPath )
      {
        while ( 1 )
        {
          LOWORD(v10) = BYTE1(trackStep);
          if ( UnitBattle_IsTileWithinRange(enemyIndex, a4, BYTE1(trackStep)) )
            break;
          v30 = *v27 - 1;
          *v27 = v30;
          pathStep = v27[v30 + 1];
          if ( HIWORD(pathStep) > (int)*(unsigned __int8 *)(enemyRecordPtr + 8) )
            goto LABEL_72;
          *(_WORD *)(enemyRecordPtr + 4) = (unsigned __int8)pathStep;
          *(_WORD *)(enemyRecordPtr + 6) = BYTE1(pathStep);
          if ( !*v27 )
            goto LABEL_69;
        }
        *(_WORD *)(enemyRecordPtr + 4) = savedRow;
        *(_WORD *)(enemyRecordPtr + 6) = savedCol;
        j__nfree_();
        LOWORD(v28) = HIWORD(pathStep);
        v29 = *(unsigned __int8 *)(enemyRecordPtr + 8);
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
      LOWORD(v10) = BYTE1(trackStep);
      if ( !UnitBattle_IsTileWithinRange(enemyIndex, a4, BYTE1(trackStep)) )
      {
LABEL_72:
        *(_WORD *)(enemyRecordPtr + 4) = savedRow;
        *(_WORD *)(enemyRecordPtr + 6) = savedCol;
        j__nfree_();
        goto LABEL_34;
      }
      *(_WORD *)(enemyRecordPtr + 4) = savedRow;
      *(_WORD *)(enemyRecordPtr + 6) = savedCol;
      if ( *(unsigned __int8 *)(enemyRecordPtr + 8) > (int)HIWORD(pathStep) )
      {
        j__nfree_();
        v20 = *(unsigned __int8 *)(enemyRecordPtr + 8) - v31;
        goto LABEL_34;
      }
    }
    else if ( *enemyTrackPath )
    {
      enemyPathStep = enemyTrackPath[1];
      j__nfree_();
      LOBYTE(v26) = *(_BYTE *)(enemyRecordPtr + 8);
      if ( v26 <= HIWORD(enemyPathStep) )
        v20 = 0;
      else
        v20 = v26 - HIWORD(enemyPathStep);
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
int  UnitBattle_ExecuteAiActionForUnit(int unitIndex, int side, DWORD gameContext)
{
  DWORD unitRecordOffset; // ebx
  DWORD cellStateBase; // edi
  int v6; // ecx
  int result; // eax
  __int16 targetCol; // bx
  int *v9; // eax
  int v10; // ecx
  __int16 meleeTargetCol; // bx
  int v12; // eax
  int v13; // ecx
  int targetStrength; // ebp
  int ownStrength; // edi
  int targetRemaining; // ebp
  int ownRemaining; // edi
  DWORD wallUnitRecordOffset; // edi
  int v19; // ecx
  int ownLoss; // [esp+0h] [ebp-2Ch] BYREF
  int targetLoss; // [esp+4h] [ebp-28h] BYREF
  int netExchange; // [esp+8h] [ebp-24h]
  signed int actionResult; // [esp+Ch] [ebp-20h]
  DWORD meleeUnitRecordOffset; // [esp+10h] [ebp-1Ch]
  __int16 *unitRecord; // [esp+14h] [ebp-18h]

  unitRecordOffset = 31 * unitIndex;
  unitRecord = (__int16 *)(31 * unitIndex + g_MapData + 852);
  cellStateBase = 801 * unitIndex;
  actionResult = 0;
  UnitBattle_UpdateIdleAnimatedUnits();
  v6 = g_UnitBattleScanTileRow;
  switch ( g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] )
  {
    case BATTLE_AI_CELL_MELEE:
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)] )
      {
        v6 = (unitRecord[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)unitRecord + 12)) >> 5);
        if ( v6 > 0 )
          goto LABEL_4;
      }
      meleeTargetCol = g_BattleTargetTileCol;
      v12 = UnitBattle_MoveTrackNear(unitIndex, v6, g_BattleTargetTileCol, gameContext);
      *(_DWORD *)((char *)unitRecord + 23) = v12;
      if ( v12 )
        UnitBattle_Move(unitIndex, v13, meleeTargetCol, gameContext);
      if ( *(_DWORD *)((char *)unitRecord + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)unitRecord + 23) = 0;
      }
      meleeUnitRecordOffset = 31 * unitIndex;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        targetStrength = *(char *)(31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                      + g_MapData
                      + 861);
        ownStrength = *((char *)unitRecord + 9);
        UnitBattle_CalcMeleeExchange(unitIndex, *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), &targetLoss, &ownLoss, 0);
        netExchange = targetStrength - targetLoss - (ownStrength - ownLoss);
        UnitBattle_CalcMeleeExchange(unitIndex, *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534), &targetLoss, &ownLoss, 1);
        targetRemaining = targetStrength - targetLoss;
        ownRemaining = ownStrength - ownLoss;
        if ( targetRemaining <= 0 && ownRemaining <= 0
          || !UnitBattle_Attack(
                unitIndex,
                *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534),
                targetRemaining - ownRemaining > netExchange)
          || *(__int16 *)(g_MapData + meleeUnitRecordOffset + 852) == -1 )
        {
          goto LABEL_5;
        }
      }
      while ( *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) != -1 );
      if ( *(unsigned __int8 *)(g_MapData + meleeUnitRecordOffset + 860) <= 4u )
        goto LABEL_5;
      actionResult = 1;
      result = 1;
      break;
    case BATTLE_AI_CELL_NOOP:
      result = 0;
      break;
    case BATTLE_AI_CELL_FORCE_MOVE:
      targetCol = g_BattleTargetTileCol;
      v9 = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, gameContext);
      *(_DWORD *)((char *)unitRecord + 23) = v9;
      if ( v9 )
        UnitBattle_Move(unitIndex, v10, targetCol, gameContext);
      if ( *(_DWORD *)((char *)unitRecord + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)unitRecord + 23) = 0;
      }
      result = 0;
      break;
    case BATTLE_AI_CELL_KITE:
      result = UnitBattle_ApproachToSafeDistance(unitIndex, g_UnitBattleScanTileRow, unitRecordOffset, gameContext);
      break;
    case BATTLE_AI_CELL_SHOOT:
      if ( g_UnitTypeMaxRange_512582[88 * *unitRecord] && (unitRecord[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)unitRecord + 12)) >> 5) > 0 )
      {
LABEL_4:
        UnitBattle_UpdateIdleAnimatedUnits();
        actionResult = UnitBattle_MoveShootingUnit(unitIndex, side, unitRecordOffset, gameContext);
        goto LABEL_5;
      }
      wallUnitRecordOffset = 31 * unitIndex;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( !UnitBattle_AttackWall(unitIndex, g_UnitBattleScanTileRow, v19, g_BattleTargetTileCol) || *(__int16 *)(g_MapData + wallUnitRecordOffset + 852) == -1 )
          goto LABEL_5;
      }
      while ( *(_BYTE *)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) );
      if ( *(unsigned __int8 *)(g_MapData + wallUnitRecordOffset + 860) <= 4u )
        goto LABEL_5;
      actionResult = 1;
      result = 1;
      break;
    default:
LABEL_5:
      result = actionResult;
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
signed int  UnitBattle_BuildAiUnitQueueForCurrentMode(int side)
{
  int v1; // edx
  int v2; // ecx
  int bestEffectiveness; // esi
  int slotCounter; // ebx
  int slotByteOffset; // ecx
  int candidateId; // eax
  char *candidateRecord; // eax
  int k; // ecx
  int role4UnitId; // eax
  int m; // ecx
  signed int result; // eax
  int colIndex; // ebx
  int colByteOffset; // edx
  int writeOffset; // eax
  int tileAddr; // edi
  int occupantUnitIndex; // esi
  __int16 occupantId; // cx
  int nextOccupantCount; // edi
  int firstUnitRow; // ecx
  int j; // ebx
  int i; // ebx
  int slotCounter2; // ecx
  char *candidateRecord2; // eax
  int bestEffectiveness2; // esi
  int slotByteOffset2; // ebx
  int n; // ebx
  int role4UnitId2; // eax
  int ii; // ecx
  int rangedUnitId; // eax
  int candidateId2; // eax
  int candidateRecordOffset; // eax
  int hasMoreUnits; // ecx
  __int16 v33; // [esp+0h] [ebp-72h]
  WCIsvListBase *occupantUnitIds[5]; // [esp+2h] [ebp-70h]
  int rowByteOffsetCopy; // [esp+16h] [ebp-5Ch]
  int forwardUnitId; // [esp+1Ah] [ebp-58h]
  int reverseUnitId; // [esp+1Eh] [ebp-54h]
  int bestMeleeUnitId; // [esp+22h] [ebp-50h]
  int role4Id; // [esp+26h] [ebp-4Ch]
  int rangedId; // [esp+2Ah] [ebp-48h]
  int planRole4Id; // [esp+2Eh] [ebp-44h]
  int planRangedId; // [esp+32h] [ebp-40h]
  int bestUnitId; // [esp+36h] [ebp-3Ch]
  int rowIndex; // [esp+3Ah] [ebp-38h]
  int rowByteOffset; // [esp+3Eh] [ebp-34h]
  int sideCopy; // [esp+42h] [ebp-30h]
  int foundMeleeUnit; // [esp+46h] [ebp-2Ch]
  int foundUnit; // [esp+4Ah] [ebp-28h]
  int bestSlot; // [esp+4Eh] [ebp-24h]
  signed int bestSlot2; // [esp+52h] [ebp-20h]
  int occupantCount; // [esp+56h] [ebp-1Ch]

  sideCopy = side;
  WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
  memset(occupantUnitIds, 0xFF, 20);
  occupantCount = 0;
  rowIndex = 0;
  rowByteOffset = 0;
  while ( *(_DWORD *)(g_MapData + 804) - 1 >= rowIndex )
  {
    colIndex = 0;
    rowByteOffsetCopy = rowByteOffset;
    colByteOffset = 0;
    writeOffset = 2 * occupantCount;
    while ( colIndex <= *(_DWORD *)(g_MapData + 800) - 1 )
    {
      tileAddr = colByteOffset + g_MapData + rowByteOffsetCopy;
      occupantUnitIndex = *(__int16 *)(tileAddr + 1534);
      if ( occupantUnitIndex == -1 || *(unsigned __int8 *)(g_MapData + 31 * occupantUnitIndex + 854) != sideCopy )
      {
        colByteOffset += 2;
        ++colIndex;
      }
      else
      {
        occupantId = *(_WORD *)(tileAddr + 1534);
        writeOffset += 2;
        nextOccupantCount = occupantCount + 1;
        *(__int16 *)((char *)&v33 + writeOffset) = occupantId;
        occupantCount = nextOccupantCount;
        colByteOffset += 2;
        ++colIndex;
      }
    }
    rowByteOffset += 40;
    ++rowIndex;
  }
  if ( (unsigned int)g_UnitBattleAiCurrentPlanMode >= 2 )
  {
    if ( (unsigned int)g_UnitBattleAiCurrentPlanMode <= 2 || g_UnitBattleAiCurrentPlanMode == 6 )
    {
      firstUnitRow = *(unsigned __int16 *)(g_MapData + 31 * SLOWORD(occupantUnitIds[0]) + 856);
      if ( (unsigned __int16)firstUnitRow >= *(_DWORD *)(g_MapData + 804) / 2 )
      {
        for ( i = 0; i != 20; i += 2 )
        {
          result = *(__int16 *)((char *)occupantUnitIds + i);
          if ( result != -1 )
          {
            forwardUnitId = *(__int16 *)((char *)occupantUnitIds + i);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, forwardUnitId);
          }
        }
      }
      else
      {
        for ( j = 18; j != -2; j -= 2 )
        {
          result = *(__int16 *)((char *)occupantUnitIds + j);
          if ( result != -1 )
          {
            reverseUnitId = *(__int16 *)((char *)occupantUnitIds + j);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, reverseUnitId);
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
      bestEffectiveness = -1;
      foundMeleeUnit = 0;
      bestSlot = 0;
      slotCounter = 0;
      slotByteOffset = 0;
      do
      {
        candidateId = *(__int16 *)((char *)occupantUnitIds + slotByteOffset);
        if ( candidateId != -1 && !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * candidateId + g_MapData + 852)] )
        {
          foundMeleeUnit = 1;
          if ( bestEffectiveness < Unit_CalcEffectivenessA((char *)(31 * candidateId + g_MapData + 852), 0) )
          {
            candidateRecord = (char *)(31 * *(__int16 *)((char *)occupantUnitIds + slotByteOffset) + g_MapData + 852);
            bestSlot = slotCounter;
            bestEffectiveness = Unit_CalcEffectivenessA(candidateRecord, 0);
          }
        }
        ++slotCounter;
        slotByteOffset += 2;
      }
      while ( slotCounter < 10 );
      if ( *((__int16 *)occupantUnitIds + bestSlot) != -1 )
      {
        bestMeleeUnitId = *((__int16 *)occupantUnitIds + bestSlot);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, bestMeleeUnitId);
      }
      *((_WORD *)occupantUnitIds + bestSlot) = -1;
    }
    while ( foundMeleeUnit );
    for ( k = 0; k != 20; k += 2 )
    {
      role4UnitId = *(__int16 *)((char *)occupantUnitIds + k);
      if ( role4UnitId != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * role4UnitId + g_MapData + 852)] == 4 )
      {
        role4Id = *(__int16 *)((char *)occupantUnitIds + k);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, role4Id);
        *(_WORD *)((char *)occupantUnitIds + k) = -1;
      }
    }
    for ( m = 0; m != 20; m += 2 )
    {
      result = *(__int16 *)((char *)occupantUnitIds + m);
      if ( result != -1 )
      {
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * result + g_MapData + 852)] )
        {
          rangedId = *(__int16 *)((char *)occupantUnitIds + m);
          result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, rangedId);
          *(_WORD *)((char *)occupantUnitIds + m) = -1;
        }
      }
    }
    return result;
  }
  for ( n = 0; n != 20; n += 2 )
  {
    role4UnitId2 = *(__int16 *)((char *)occupantUnitIds + n);
    if ( role4UnitId2 != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * role4UnitId2 + g_MapData + 852)] == 4 )
    {
      planRole4Id = *(__int16 *)((char *)occupantUnitIds + n);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, planRole4Id);
      *(_WORD *)((char *)occupantUnitIds + n) = -1;
    }
  }
  for ( ii = 0; ii != 20; ii += 2 )
  {
    rangedUnitId = *(__int16 *)((char *)occupantUnitIds + ii);
    if ( rangedUnitId != -1 && g_UnitTypeMaxRange_512582[88 * *(__int16 *)(g_MapData + 31 * rangedUnitId + 852)] )
    {
      planRangedId = *(__int16 *)((char *)occupantUnitIds + ii);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, planRangedId);
      *(_WORD *)((char *)occupantUnitIds + ii) = -1;
    }
  }
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    bestEffectiveness2 = -1;
    foundUnit = 0;
    bestSlot2 = 0;
    slotCounter2 = 0;
    slotByteOffset2 = 0;
    while ( 1 )
    {
      candidateId2 = *(__int16 *)((char *)occupantUnitIds + slotByteOffset2);
      if ( candidateId2 != -1 )
        break;
LABEL_45:
      ++slotCounter2;
      slotByteOffset2 += 2;
      if ( slotCounter2 >= 10 )
        goto LABEL_63;
    }
    candidateRecordOffset = 31 * candidateId2;
    foundUnit = 1;
    if ( g_UnitTypeRole[88 * *(__int16 *)(g_MapData + candidateRecordOffset + 852)] != 4 )
    {
      if ( bestEffectiveness2 < Unit_CalcEffectivenessA((char *)(g_MapData + 852 + candidateRecordOffset), 0) )
      {
        candidateRecord2 = (char *)(31 * *(__int16 *)((char *)occupantUnitIds + slotByteOffset2) + g_MapData + 852);
        bestSlot2 = slotCounter2;
        bestEffectiveness2 = Unit_CalcEffectivenessA(candidateRecord2, 0);
      }
      goto LABEL_45;
    }
    bestSlot2 = slotCounter2;
LABEL_63:
    if ( *((__int16 *)occupantUnitIds + bestSlot2) != -1 )
    {
      bestUnitId = *((__int16 *)occupantUnitIds + bestSlot2);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, bestUnitId);
    }
    result = bestSlot2;
    hasMoreUnits = foundUnit;
    *((_WORD *)occupantUnitIds + bestSlot2) = -1;
  }
  while ( hasMoreUnits );
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
signed int  UnitBattle_ScanAiPlanRangeLine(int side, signed int scanDirection)
{
  int i; // eax
  int recordAddr; // edx
  int projectedRow; // edx
  int targetRow; // ebp
  int enemyRecordAddr; // ebx
  int targetCol; // ebx
  int recordBase; // esi
  int v9; // edx
  BOOL inRange; // eax
  int v11; // ecx
  int enemyRecord; // esi
  int v14; // ecx
  int enemyUnitRecord; // eax
  int *trackList; // eax
  int *track; // ecx
  int enemyUnitRecord2; // eax
  int enemyUnitRecord3; // eax
  int pathMoveCost; // edx
  int rangeValue; // eax
  int *v22; // ecx
  int trackIndex; // eax
  int v24; // edx
  int unitRange; // edx
  int firstTrackStep; // [esp+8h] [ebp-34h]
  int trackEntry; // [esp+8h] [ebp-34h]
  int enemyRecordOffset; // [esp+10h] [ebp-2Ch]
  int battle_width;
  int battle_height;
  __int16 savedTileRow; // [esp+14h] [ebp-28h]
  __int16 savedTileCol; // [esp+18h] [ebp-24h]
  int bestProjectedRow; // [esp+1Ch] [ebp-20h]
  int enemyUnitIndex; // [esp+20h] [ebp-1Ch]

  bestProjectedRow = -20;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_enter", side, scanDirection, g_AttackerStartsOnLeft, g_DefenderStartsOnLeft);
  if ( *(_DWORD *)(g_MapData + 836) == side )
  {
    if ( g_AttackerStartsOnLeft )
      scanDirection = 1;
    else
      scanDirection = -1;
  }
  if ( side == *(_DWORD *)(g_MapData + 840) )
  {
    if ( g_DefenderStartsOnLeft )
      scanDirection = 1;
    else
      scanDirection = -1;
  }
  for ( i = 0; i != 682; i += 31 )
  {
    recordAddr = i + g_MapData;
    if ( *(__int16 *)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(recordAddr + 854) == side )
    {
      projectedRow = scanDirection * *(unsigned __int16 *)(recordAddr + 856);
      if ( projectedRow > bestProjectedRow )
        bestProjectedRow = projectedRow;
    }
  }
  enemyUnitIndex = 0;
  enemyRecordOffset = 0;
  targetRow = scanDirection * (bestProjectedRow + 3);
  battle_width = *(_DWORD *)(g_MapData + 800);
  battle_height = *(_DWORD *)(g_MapData + 804);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_ai_plan_range_line",
    side,
    targetRow,
    battle_width,
    battle_height);
  if ( targetRow < 0 || targetRow >= battle_height )
    return 0;
  while ( 1 )
  {
    enemyRecordAddr = g_MapData + enemyRecordOffset;
    if ( *(__int16 *)(g_MapData + enemyRecordOffset + 852) == -1 || *(unsigned __int8 *)(enemyRecordAddr + 854) == side )
      goto LABEL_23;
    targetCol = *(unsigned __int16 *)(enemyRecordAddr + 858);
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_plan_range_candidate",
      enemyUnitIndex,
      targetRow,
      targetCol,
      *(__int16 *)(enemyRecordAddr + 852));
    if ( targetCol < 0 || targetCol >= battle_width )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_skip_oob_target", enemyUnitIndex, targetRow, targetCol, battle_width);
      goto LABEL_23;
    }
    if ( *(__int16 *)(40 * targetRow + g_MapData + 2 * targetCol + 1534) != -1 )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_target_occupied", enemyUnitIndex, targetRow, targetCol, 0);
      return 0;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_log", enemyUnitIndex, targetRow, targetCol, side);
    Debug_Log(side, targetCol, targetRow, (int)aOddzial_w_zasi);
    recordBase = g_MapData + 852;
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_range", enemyUnitIndex, targetRow, targetCol, side);
    inRange = UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_after_range", enemyUnitIndex, targetRow, targetCol, inRange);
    enemyRecord = g_MapData + enemyRecordOffset + 852;
    if ( inRange
      && (*(_BYTE *)(enemyRecordOffset + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(enemyRecordOffset + g_MapData + 864)) >> 5) > 0 )
    {
      goto LABEL_17;
    }
    v14 = targetCol;
    if ( *(char *)(targetCol + g_MapData + 20 * targetRow + 3134) <= 0
      || (v14 = g_MapData + 40 * targetRow, *(__int16 *)(v14 + 2 * targetCol + 1534) != -1)
      && ((enemyUnitRecord = 31 * enemyUnitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(enemyUnitRecord + 852)] & 1) != 0)
       || (v14 = (unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord + 864)) >> 5, (*(_BYTE *)(enemyUnitRecord + 864) & 3) + 1 - v14 > 0)) )
    {
      trackList = UnitBattle_MoveTrackNear(enemyUnitIndex, targetRow, targetCol, targetRow);
    }
    else
    {
      trackList = UnitBattle_MoveTrackNearWall(enemyUnitIndex, targetRow, targetCol, targetRow);
    }
    track = trackList;
    if ( !trackList )
    {
      enemyUnitRecord2 = g_MapData + 31 * enemyUnitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyUnitRecord2 + 852)] )
      {
        if ( (*(_BYTE *)(enemyUnitRecord2 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord2 + 864)) >> 5) > 0 )
          track = UnitBattle_MoveTrackForce(enemyUnitIndex, targetCol, targetRow);
      }
    }
    if ( !track )
      goto LABEL_23;
    if ( !*track )
    {
      nfree_((int)(uintptr_t)track);
LABEL_17:
      if ( *(_BYTE *)(enemyRecord + 8) )
        return 0;
      goto LABEL_23;
    }
    enemyUnitRecord3 = 31 * enemyUnitIndex + g_MapData;
    if ( !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyUnitRecord3 + 852)]
      || (*(_BYTE *)(enemyUnitRecord3 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord3 + 864)) >> 5) <= 0 )
    {
      if ( !*track )
        goto LABEL_59;
      firstTrackStep = track[1];
      nfree_((int)(uintptr_t)track);
      LOWORD(pathMoveCost) = HIWORD(firstTrackStep);
      rangeValue = *(unsigned __int8 *)(enemyRecord + 8);
      if ( rangeValue > pathMoveCost && rangeValue - pathMoveCost > 0 )
        return 0;
      goto LABEL_23;
    }
    savedTileRow = *(_WORD *)(enemyRecord + 4);
    HIWORD(trackEntry) = 0;
    savedTileCol = *(_WORD *)(enemyRecord + 6);
    if ( *track )
      break;
LABEL_50:
    if ( !UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol) )
    {
LABEL_58:
      *(_WORD *)(enemyRecord + 4) = savedTileRow;
      *(_WORD *)(enemyRecord + 6) = savedTileCol;
LABEL_59:
      nfree_((int)(uintptr_t)track);
      goto LABEL_23;
    }
    *(_WORD *)(enemyRecord + 4) = savedTileRow;
    *(_WORD *)(enemyRecord + 6) = savedTileCol;
    if ( *(unsigned __int8 *)(enemyRecord + 8) <= (int)HIWORD(trackEntry) )
      goto LABEL_59;
    nfree_((int)(uintptr_t)track);
    if ( *(unsigned __int8 *)(enemyRecord + 8) - HIWORD(trackEntry) > 0 )
      return 0;
LABEL_23:
    enemyRecordOffset += 31;
    if ( ++enemyUnitIndex >= 22 )
      return 1;
  }
  while ( !UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol) )
  {
    trackIndex = *track - 1;
    *track = trackIndex;
    trackEntry = track[trackIndex + 1];
    if ( HIWORD(trackEntry) > (int)*(unsigned __int8 *)(enemyRecord + 8) )
      goto LABEL_58;
    *(_WORD *)(enemyRecord + 4) = (unsigned __int8)trackEntry;
    *(_WORD *)(enemyRecord + 6) = BYTE1(trackEntry);
    if ( !*track )
      goto LABEL_50;
  }
  *(_WORD *)(enemyRecord + 4) = savedTileRow;
  *(_WORD *)(enemyRecord + 6) = savedTileCol;
  nfree_((int)(uintptr_t)track);
  unitRange = *(unsigned __int8 *)(enemyRecord + 8);
  if ( unitRange <= HIWORD(trackEntry) || unitRange - HIWORD(trackEntry) <= 0 )
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
  int scanRow; // edx
  int rowByteOffset; // ecx
  int scanCol; // eax
  int scanRowByteOffset; // esi
  int tileAddr; // edx
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
  scanRow = 1;
  rowByteOffset = 20;
  while ( scanRow < battle_height - 1 )
  {
    if ( *(char *)(g_MapData + rowByteOffset + wall_column + 3135) > 0 )
      g_UnitBattleWallScanTileRow = scanRow;
    rowByteOffset += 20;
    ++scanRow;
  }
  g_BattleWallScanColumn = wall_column;
  g_BattleWallScanTileX = g_BattleWallScanColumn + 1;
  scanCol = 1;
  scanRowByteOffset = 20 * g_UnitBattleWallScanTileRow;
  while ( scanCol < battle_width - 1 )
  {
    tileAddr = g_MapData + scanRowByteOffset + scanCol;
    if ( *(char *)(tileAddr + 3134) >= 0 && *(_BYTE *)(tileAddr + 3134) < *(_BYTE *)(g_BattleWallScanColumn + g_MapData + scanRowByteOffset + 3134) )
    {
      g_BattleWallScanTileX = g_BattleWallScanColumn;
      g_BattleWallScanColumn = scanCol++;
    }
    else
    {
      ++scanCol;
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
signed int  UnitBattle_SelectAiPlanMode(int side, signed int scanDirection)
{
  int sideCopy; // edx

  sideCopy = side;
  if ( g_UnitBattleAiTurnCounter <= 3 && UnitBattle_ScanAiPlanRangeLine(side, scanDirection) )
    return BATTLE_AI_PLAN_RANGED_ENGAGE;
  if ( *(int *)(g_MapData + 828) <= 0 )
    return BATTLE_AI_PLAN_DISENGAGE;
  if ( g_UnitBattleAiTurnCounter == 1 && sideCopy == *(_DWORD *)(g_MapData + 840) && g_UnitBattleAiCurrentPlanMode != 6 )
    return BATTLE_AI_PLAN_INITIAL_SWEEP;
  if ( sideCopy == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter < 3 )
    return BATTLE_AI_PLAN_HOLD;
  if ( sideCopy == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter >= 3 )
    return BATTLE_AI_PLAN_DISENGAGE;
  return BATTLE_AI_PLAN_ADVANCE;
}
// 43CC79: variable 'v2' is possibly undefined
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532078: using guessed type int dword_532078;

//----- (0043CD00) --------------------------------------------------------
signed int  UnitBattle_RunAiTurnForSide(unsigned __int8 side)
{
  signed int turnResult; // esi
  int v3; // edx
  int poppedUnitId; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  signed int queueIndex; // esi
  int i; // edi
  int queuedUnitId; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int unitRecordAddr; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int unitIndex; // [esp+0h] [ebp-1Ch]

  turnResult = 1;
  unitIndex = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_enter", side, g_CurrentPlayerIndex, g_UnitBattleAiTurnCounter, 0);
  g_BattleAiActionAttemptCount = 0;
  ++g_UnitBattleAiTurnCounter;
  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_before_wall_scan",
      side,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 800),
      *(_DWORD *)(g_MapData + 804));
    UnitBattle_ScanAiWallTargetColumns();
    Diagnostics_TraceWorldMapActionEvent("battle_ai_after_wall_scan", side, g_UnitBattleWallScanTileRow, g_BattleWallScanColumn, g_BattleWallScanTileX);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_ai_before_idle", side, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_idle", side, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(side, side);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_mode", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  UnitBattle_BuildAiUnitQueueForCurrentMode(side);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_queue", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
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
        poppedUnitId = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        unitIndex = poppedUnitId;
        UnitBattle_ResetAiReachGridForSide(side);
        UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, 1);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(unitIndex, side) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0);
        }
        else
        {
          WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
        }
      }
      goto LABEL_8;
    case 6:
LABEL_8:
      queueIndex = 0;
      for ( i = g_BattleAiUnitQueueCount; queueIndex < i; ++queueIndex )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        queuedUnitId = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        unitIndex = queuedUnitId;
        UnitBattle_ResetAiReachGridForSide(side);
        UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, queueIndex);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(unitIndex, side) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0);
        }
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(side, side);
      UnitBattle_UpdateIdleAnimatedUnits();
      turnResult = 0;
      UnitBattle_BuildAiUnitQueueForCurrentMode(side);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_after_requeue", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
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
    unitIndex = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_unit_candidate", unitIndex, side, g_UnitBattleAiCandidateQueueTail, turnResult);
    unitRecordAddr = g_MapData + 31 * unitIndex;
    if ( *(__int16 *)(unitRecordAddr + 852) != -1 && side == *(_BYTE *)(unitRecordAddr + 854) )
      break;
LABEL_20:
    if ( !g_UnitBattleAiCandidateQueueTail )
    {
LABEL_21:
      WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_exit", side, turnResult, g_UnitBattleAiCandidateQueueTail, 0);
      return turnResult;
    }
  }
  while ( 1 )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    UnitBattle_ResetAiReachGridForSide(side);
    if ( UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, turnResult) )
      return 1;
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_SelectAiActionForUnit(unitIndex, side) )
    {
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
LABEL_19:
      turnResult = 0;
      goto LABEL_20;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0) )
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
int  WCIsvListBase_dtorRoot(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_WCIsvListBaseRoot_DtorArrayTag);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
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
int __cdecl WCIsvListBase_vtblFree()
{
  return j__nfree_();
}

//----- (0043CFA0) --------------------------------------------------------
BOOL  WCIsvListBase_ValuesEqual(_DWORD *leftNode, _DWORD *rightNode)
{
  return *leftNode == *rightNode;
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
int  WCIsvListBase_dtorVariant124(WCIsvListBase *a1, char dtorFlags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant124_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (dtorFlags & 2) != 0 )
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
int  WCIsvListBase_ctorVariant124AndCopy(_DWORD *dest, _DWORD *source)
{
  int v2; // ecx

  *dest = 0;
  dest[1] = &g_WCIsvListBaseRoot_Vtable;
  dest[2] = 0;
  dest[3] = 0;
  dest[4] = 0;
  dest[5] = 0;
  dest[1] = &g_WCIsvListBaseDtor_Vtable;
  dest[1] = &g_WCIsvListBaseDestroyElements_Vtable;
  dest[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(dest, source, (int)dest);
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
int  WCIsvListBase_dtorVariant134(WCIsvListBase *a1, char dtorFlags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant134_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (dtorFlags & 2) != 0 )
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
_DWORD *WCIsvListBase_vtblDtor(WCIsvListBase *this)
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
  return WCIsvListBase_vtblDtor(this);
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
_DWORD * WCIsvListBase_AllocLinkNode(int listHandle, int a2)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  list = WCCompat_ListFromHandle(listHandle);
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
int  WCIsvListBase_ReleaseLinkNode(int listHandle, int linkHandle, int freeSize)
{
  if ( !linkHandle )
    return 0;
  if ( *(_DWORD *)(listHandle + 20) )
    return (*(int (__cdecl **)(int))(uintptr_t)(unsigned int)*(_DWORD *)(listHandle + 20))(freeSize);
  return nfree_(linkHandle);
}

//----- (0043D180) --------------------------------------------------------
int  WCIsvListBase_CopyAppendAll(_DWORD *destList, _DWORD *sourceList, int startCursor)
{
  int link_handle;
  WCCompatLink *link;

  *destList = *sourceList;
  destList[4] = sourceList[4];
  destList[5] = sourceList[5];
  link_handle = WCIsvListBase_base_next((int)(uintptr_t)sourceList, startCursor);
  while ( link_handle )
  {
    link = WCCompat_LinkFromHandle(link_handle);
    if ( !link )
      break;
    WCIsvListBase_AppendValue((int)(uintptr_t)destList, link->value);
    link_handle = WCIsvListBase_base_next((int)(uintptr_t)sourceList, link_handle);
  }
  return link_handle;
}

//----- (0043D1E0) --------------------------------------------------------
int  WCIsvListBase_DestroyElementsAndDtor(WCIsvListBase *this, int listHandle)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromHandle(listHandle);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseDestroyElements_Vtable;
  if ( list->tail_link )
  {
    Noop_WCIsvListErrorHook(listHandle);
    WCIsvListBase_base_destroy(this);
  }
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseFreeOnly_Vtable;
  return WCIsvListBase_dtor(this);
}

//----- (0043D220) --------------------------------------------------------
signed int  WCIsvListBase_AppendValue(int listHandle, int value)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  link = (WCCompatLink *)WCIsvListBase_AllocLinkNode(listHandle, value);
  if ( link )
  {
    list = WCCompat_ListFromHandle(listHandle);
    WCIsvListBase_base_insert(listHandle, (int)(uintptr_t)link);
    list->tail_link = (int)(uintptr_t)link;
    return 1;
  }
  Noop_WCIsvListErrorHook(listHandle);
  return 0;
}

//----- (0043D250) --------------------------------------------------------
int  WCIsvListBase_PopFrontValue(int listHandle, int defaultValue)
{
  int link_handle;
  WCCompatLink *link;

  link_handle = WCIsvListBase_base_sget(listHandle);
  if ( !link_handle )
    return defaultValue;
  link = WCCompat_LinkFromHandle(link_handle);
  if ( !link )
    return defaultValue;
  defaultValue = link->value;
  WCIsvListBase_ReleaseLinkNode(listHandle, link_handle, 8);
  return defaultValue;
}

//----- (0043D280) --------------------------------------------------------
int  WCIsvListBase_CopyCtor(_DWORD *dest, _DWORD *source)
{
  int v2; // ecx
  int result; // eax

  *dest = 0;
  dest[1] = &g_WCIsvListBaseRoot_Vtable;
  dest[2] = 0;
  dest[3] = 0;
  dest[4] = 0;
  dest[5] = 0;
  dest[1] = &g_WCIsvListBaseDtor_Vtable;
  dest[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(dest, source, (int)dest);
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
int  Battle_DeploySideUnitsByRoleBuckets(char *ownUnits, int ownCount, char *enemyUnits, int placementSide, int enemyCount)
{
  int ownDefenseTotal; // esi
  int ownAttackTotal; // edi
  int enemyAttackTotal; // ebp
  int ownIndex; // ebx
  char *ownCursor; // ecx
  int enemyIndex; // ebx
  char *enemyCursor; // ecx
  int enemyUnitDefense; // eax
  unsigned __int8 deployMode; // al
  float defenseRatioFloat; // [esp+10h] [ebp-24h]
  float attackRatioFloat; // [esp+14h] [ebp-20h]
  int enemyDefenseTotal; // [esp+20h] [ebp-14h]
  int attackRatio; // [esp+24h] [ebp-10h]
  int defenseRatio; // [esp+24h] [ebp-10h]
  int deploy_result;

  Diagnostics_TraceWorldMapActionEvent("battle_deploy_enter", ownCount, placementSide, enemyCount, *(__int16 *)ownUnits);
  ownDefenseTotal = 0;
  ownAttackTotal = 0;
  enemyAttackTotal = 0;
  ownIndex = 0;
  enemyDefenseTotal = 0;
  if ( ownCount > 0 )
  {
    ownCursor = ownUnits;
    do
    {
      ownAttackTotal += Unit_CalcEffectivenessA(ownCursor, 0);
      Unit_CalcEffectivenessB(ownCursor, 0);
      ++ownIndex;
      ownDefenseTotal += Unit_CalcEffectivenessC((__int16 *)ownCursor);
      ownCursor += UNIT_STACK_SLOT_STRIDE;
    }
    while ( ownIndex < ownCount );
  }
  enemyIndex = 0;
  if ( enemyCount > 0 )
  {
    enemyCursor = enemyUnits;
    do
    {
      enemyAttackTotal += Unit_CalcEffectivenessA(enemyCursor, 0);
      Unit_CalcEffectivenessB(enemyCursor, 0);
      ++enemyIndex;
      enemyUnitDefense = Unit_CalcEffectivenessC((__int16 *)enemyCursor);
      enemyCursor += UNIT_STACK_SLOT_STRIDE;
      enemyDefenseTotal += enemyUnitDefense;
    }
    while ( enemyIndex < enemyCount );
  }
  if ( enemyAttackTotal <= 0 )
    attackRatio = ownAttackTotal;
  else
    attackRatio = ownAttackTotal / enemyAttackTotal;
  attackRatioFloat = (float)attackRatio;
  if ( enemyDefenseTotal <= 0 )
    defenseRatio = ownDefenseTotal;
  else
    defenseRatio = ownDefenseTotal / enemyDefenseTotal;
  defenseRatioFloat = (float)defenseRatio;
  deployMode = defenseRatioFloat < g_Battle_RoleDeployRatioHighThreshold && (defenseRatioFloat <= g_Battle_RoleDeployRatioLowThreshold || SLODWORD(attackRatioFloat) > 1065353216);
  Battle_BuildRoleDeploymentBuckets((int)ownUnits, ownCount, deployMode);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_build",
    ownCount,
    deployMode,
    Diagnostics_CountBattleDeploymentBucketEntries(),
    *(__int16 *)ownUnits);
  deploy_result = Battle_PlaceRoleDeploymentBuckets(deployMode, placementSide);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_place",
    deploy_result,
    Diagnostics_CountBattleUnitsTotal(),
    Diagnostics_CountBattleUnitsForOwner(ownUnits[2]),
    g_SelectedUnitIndex);
  return deploy_result;
}
// 43D2D0: could not find valid save-restore pair for ebx
// 4F18A7: using guessed type double dbl_4F18A7;
// 4F18AF: using guessed type double dbl_4F18AF;

//----- (0043D430) --------------------------------------------------------
int  Battle_BuildRoleDeploymentBuckets(int unitsPtr, int unitCount, unsigned __int8 deployMode)
{
  int result; // eax
  __int16 *unitRecord; // ecx
  int unitIndex; // edi
  int bucket1Count; // ebp
  int bucket2Count; // esi
  int bucket3Count; // [esp+4h] [ebp-20h]
  unsigned __int8 bucketCode; // [esp+Ch] [ebp-18h]

  memset(g_BattleDeploymentBucketStorage_5437DC, 0, 0xC0);
  result = 0;
  unitRecord = (__int16 *)(uintptr_t)(unsigned int)unitsPtr;
  unitIndex = 0;
  if ( unitCount > 0 )
  {
    bucket3Count = 0;
    bucket1Count = 0;
    bucket2Count = 0;
    do
    {
      bucketCode = g_BattleRoleDeploymentBucketTable[7 * deployMode + (unsigned __int8)g_UnitTypeRole[88 * *unitRecord]];
      if ( (bucketCode - bucketCode % 10) / 10 == 1 )
        g_BattleDeploymentBucketRole1[++bucket1Count] = (int)unitRecord;
      if ( (bucketCode - bucketCode % 10) / 10 == 2 )
        g_BattleDeploymentBucketRole2[++bucket2Count] = (int)unitRecord;
      result = (bucketCode - bucketCode % 10) / 10;
      if ( result == 3 )
      {
        result = bucket3Count * 4;
        g_BattleDeploymentBucketRole3[bucket3Count++] = (int)unitRecord;
      }
      ++unitIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
    }
    while ( unitIndex < unitCount );
  }
  return result;
}
// 43D466: variable 'v4' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 543808: using guessed type int dword_543808[];
// 543838: using guessed type int dword_543838[];
// 54386C: using guessed type int dword_54386C[];

//----- (0043D560) --------------------------------------------------------
signed int  Battle_PlaceUnitAtNextOpenDeploymentTile(unsigned __int8 *unitRecord, _DWORD *columnCursor, int isAttackerSide, int *rowCursor)
{
  int tileY; // ebp
  int nextRowRight; // edx
  int tileYLeft; // ecx
  int tileX2; // ebp
  char facingCode; // al
  signed int result; // eax
  int nextRowLeft; // edx
  char facingCode2; // al
  int tileYLeftKept; // [esp+8h] [ebp-18h]
  int tileX; // [esp+Ch] [ebp-14h]

  while ( 1 )
  {
    while ( 1 )
    {
      tileY = isAttackerSide ? 2 - *rowCursor : *rowCursor + *(_DWORD *)(g_MapData + 804) - 3;
      tileX = *(_DWORD *)(g_MapData + 800) / 2 + *columnCursor;
      if ( tileX < *(_DWORD *)(g_MapData + 800) )
        break;
      *columnCursor = 0;
      nextRowRight = ++*rowCursor % 3;
      *rowCursor = nextRowRight;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)unitRecord, tileY, tileX) )
    {
      facingCode = isAttackerSide ? 2 : 6;
      result = Battle_PlaceUnit(unitRecord, tileY, facingCode, tileX);
      if ( result )
        break;
    }
    while ( 1 )
    {
      tileYLeft = isAttackerSide ? 2 - *rowCursor : *rowCursor + *(_DWORD *)(g_MapData + 804) - 3;
      tileX2 = *(_DWORD *)(g_MapData + 800) / 2 - *columnCursor;
      tileYLeftKept = tileYLeft;
      if ( tileX2 >= 0 )
        break;
      *columnCursor = 0;
      nextRowLeft = ++*rowCursor % 3;
      *rowCursor = nextRowLeft;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)unitRecord, tileYLeft, tileX2) )
    {
      facingCode2 = isAttackerSide ? 2 : 6;
      result = Battle_PlaceUnit(unitRecord, tileYLeftKept, facingCode2, tileX2);
      if ( result )
      {
        ++*columnCursor;
        return result;
      }
    }
    ++*columnCursor;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0043D6E0) --------------------------------------------------------
int  Battle_PlaceRoleDeploymentBuckets(unsigned __int8 deployMode, int placementSide)
{
  int candidateReadByteOffset; // edi
  int bestRow; // ebx
  int bestCol; // esi
  int bucketColIndex; // ecx
  int result; // eax
  int bestEntryOffset; // esi
  int candidateTableIndex; // edx
  char *bestUnitPtr; // ebp
  int bestUnitTypeOffset; // eax
  unsigned int bestBucketTableValue; // edx
  int bestEffectiveness; // ebp
  int rowCursor; // [esp+0h] [ebp-44h] BYREF
  int columnCursor; // [esp+4h] [ebp-40h] BYREF
  int candidateRankMod10; // [esp+8h] [ebp-3Ch]
  int bucketRowByteOffset; // [esp+Ch] [ebp-38h]
  int placementSideCopy; // [esp+10h] [ebp-34h]
  int rowReadByteOffsetBase; // [esp+14h] [ebp-30h]
  int rowStorageByteOffsetBase; // [esp+18h] [ebp-2Ch]
  int placementIteration; // [esp+1Ch] [ebp-28h]
  int bucketHasEntry; // [esp+20h] [ebp-24h]
  int bucketRow; // [esp+24h] [ebp-20h]
  int storageByteOffset; // [esp+28h] [ebp-1Ch]
  int deployModeTableBase; // [esp+2Ch] [ebp-18h]
  unsigned __int8 deployModeCopy; // [esp+30h] [ebp-14h]
  unsigned __int8 *candidate;
  unsigned __int8 *best_candidate;

  deployModeCopy = deployMode;
  placementSideCopy = placementSide;
  rowCursor = 0;
  bucketRow = 1;
  bucketRowByteOffset = 48;
  do
  {
    columnCursor = 0;
    bucketHasEntry = 0;
    placementIteration = 0;
    rowCursor = (rowCursor + 1) % 3;
    rowReadByteOffsetBase = bucketRowByteOffset;
    rowStorageByteOffsetBase = bucketRowByteOffset;
    do
    {
      candidateReadByteOffset = rowReadByteOffsetBase;
      bestRow = 0;
      bestCol = 0;
      bucketColIndex = 0;
      storageByteOffset = rowStorageByteOffsetBase;
      do
      {
        result = storageByteOffset;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + storageByteOffset) )
        {
          bucketHasEntry = 1;
          if ( !bestRow )
          {
            bestRow = bucketRow;
            bestCol = bucketColIndex;
          }
          candidate = BattleDeploymentBucketReadPointer(candidateReadByteOffset);
          candidateTableIndex = 7 * deployModeCopy + (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)candidate];
          deployModeTableBase = 7 * deployModeCopy;
          best_candidate = BattleDeploymentBucketReadPointer(48 * bestRow + 4 * bestCol);
          bestUnitPtr = (char *)best_candidate;
          bestUnitTypeOffset = 88 * *(__int16 *)bestUnitPtr;
          candidateRankMod10 = (unsigned __int8)g_BattleRoleDeploymentBucketTable[candidateTableIndex] % 10;
          bestBucketTableValue = (unsigned __int8)g_BattleRoleDeploymentBucketTable[(unsigned __int8)g_UnitTypeRole[bestUnitTypeOffset] + deployModeTableBase];
          deployModeTableBase = 10;
          result = bestBucketTableValue / 10LL;
          if ( bestBucketTableValue % 10LL <= candidateRankMod10 )
          {
            bestEffectiveness = Unit_CalcEffectivenessA(bestUnitPtr, 0);
            result = Unit_CalcEffectivenessA((char *)candidate, 0);
            if ( bestEffectiveness <= result )
            {
              bestRow = bucketRow;
              bestCol = bucketColIndex;
            }
          }
          else
          {
            bestRow = bucketRow;
            bestCol = bucketColIndex;
          }
        }
        candidateReadByteOffset += 4;
        ++bucketColIndex;
        storageByteOffset += 4;
      }
      while ( bucketColIndex < 12 );
      if ( bucketHasEntry )
      {
        bestEntryOffset = 48 * bestRow + 4 * bestCol;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + bestEntryOffset) )
        {
          result = Battle_PlaceUnitAtNextOpenDeploymentTile(BattleDeploymentBucketReadPointer(bestEntryOffset), &columnCursor, placementSideCopy, &rowCursor);
          *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + bestEntryOffset) = 0;
        }
      }
      ++placementIteration;
    }
    while ( placementIteration < 12 );
    bucketRowByteOffset += 48;
    ++bucketRow;
  }
  while ( bucketRow < 4 );
  return result;
}
// 43D77B: variable 'v5' is possibly undefined
// 5437DC: using guessed type int dword_5437DC[];

//----- (0043D8C0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v1(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V1 = v4;
  return result;
}
// 43D8CB: variable 'v4' is possibly undefined
// 5438A4: using guessed type int dword_5438A4;

//----- (0043D8E0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v1(int buildingPtr, int stringBuffer, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(stringBuffer, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_3;
  else
    backgroundPath = aCastle_pogDw_3;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV1SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrDw_5;
  else
    palettePath = aCastle_pogDw_5;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_6);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V1);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V1 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V1, renderContext);
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
int  Building_HandleGateDoorDialogClose_v2(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V2 = v4;
  return result;
}
// 43DACB: variable 'v4' is possibly undefined
// 5438B0: using guessed type int dword_5438B0;

//----- (0043DAE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v2(int buildingPtr, int a2, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_6;
  else
    backgroundPath = aCastle_pogDw_6;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV2SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrDw_8;
  else
    palettePath = aCastle_pogDw_8;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_7);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V2);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V2 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V2, renderContext);
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
int  Building_HandleGateDoorDialogClose_v3(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V3 = v4;
  return result;
}
// 43DCCB: variable 'v4' is possibly undefined
// 5438BC: using guessed type int dword_5438BC;

//----- (0043DCE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v3(int buildingPtr, int objectArray, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(objectArray, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_9;
  else
    backgroundPath = aCastle_pogDw_9;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV3SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrD_11;
  else
    palettePath = aCastle_pogD_11;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_8);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V3);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V3 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V3, renderContext);
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
int  Building_HandleGateDoorDialogClose_v4(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V4 = v4;
  return result;
}
// 43DECB: variable 'v4' is possibly undefined
// 5438C8: using guessed type int dword_5438C8;

//----- (0043DEE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v4(int buildingPtr, int ctorArrayBuffer, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(ctorArrayBuffer, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrD_12;
  else
    backgroundPath = aCastle_pogD_12;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV4SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrD_14;
  else
    palettePath = aCastle_pogD_14;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_9);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V4);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V4 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V4, renderContext);
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
BOOL  Building_HasFreeAdjacentExitTile(unsigned __int8 *building)
{
  int *neighborOffsets; // esi
  int i; // ebp
  int neighborX; // ebx
  int neighborY; // ecx

  if ( building[4] )
    neighborOffsets = (int *)&g_LargeBuildingNeighborOffsets;
  else
    neighborOffsets = Map_NeighborDX;
  for ( i = 0; i < 12; ++i )
  {
    neighborX = *neighborOffsets + *building;
    neighborY = neighborOffsets[1] + building[1];
    if ( neighborX >= 0
      && neighborX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
      && neighborY >= 0
      && neighborY < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && *(unsigned __int16 *)(TILE_INDEX(neighborX, neighborY)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(building[2], 0, neighborY, neighborX) )
    {
      break;
    }
    neighborOffsets += 2;
  }
  return i != 12;
}
// 513334: using guessed type int dword_513334[];
// 5202E4: using guessed type int gameData;

//----- (0043E160) --------------------------------------------------------
signed int  Building_UnitsLeave(unsigned __int8 *building, int *exitSlots, double gameTime)
{
  int *neighborOffset; // esi
  int i; // edi
  int neighborX; // ebx
  int neighborY; // ecx
  int *chosenOffset; // edx
  int spawnY; // edi
  int spawnX; // esi
  char facing; // al
  int *slotIndexPtr; // eax
  int movedCount; // edx
  __int16 *destSlot; // ebx
  unsigned __int8 *srcSlot; // esi
  int movedSlotIndex; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  double v21; // st7
  double v22; // st7
  int v23; // ecx
  int *neighborOffsets; // [esp+0h] [ebp-20h]
  __int16 *newStackRecord; // [esp+8h] [ebp-18h]

  Debug_Log(exitSlots[3], exitSlots[2], (DWORD)building, (int)aBuildingUnitsLeave);
  if ( building[4] )
    neighborOffsets = (int *)&g_LargeBuildingNeighborOffsets;
  else
    neighborOffsets = Map_NeighborDX;
  neighborOffset = neighborOffsets;
  for ( i = 0; i < 12; ++i )
  {
    neighborX = *neighborOffset + *building;
    neighborY = neighborOffset[1] + building[1];
    if ( neighborX >= 0
      && neighborX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
      && neighborY >= 0
      && neighborY < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && *(unsigned __int16 *)(TILE_INDEX(neighborX, neighborY)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(building[2], 0, neighborY, neighborX) )
    {
      break;
    }
    neighborOffset += 2;
  }
  if ( i == 12 )
    return -1;
  chosenOffset = &neighborOffsets[2 * i];
  spawnY = building[1] + chosenOffset[1];
  spawnX = *building + *chosenOffset;
  facing = Facing_DirectionFromDelta8(*chosenOffset, chosenOffset[1]);
  Diagnostics_TraceWorldMapActionEvent("building_units_leave_request", -1, *building, building[1], exitSlots[0]);
  Unit_Create(0xFFFFFFFF, building[2], spawnX, facing, spawnY);
  slotIndexPtr = exitSlots;
  movedCount = 0;
  newStackRecord = (__int16 *)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(spawnX, spawnY)) + gameData + UNIT_STACK_TABLE_OFFSET);
  Diagnostics_TraceWorldMapActionEvent(
    "building_units_leave_spawn",
    *(unsigned __int16 *)(TILE_INDEX(spawnX, spawnY)),
    spawnX,
    spawnY,
    exitSlots[0]);
  destSlot = newStackRecord + 3;
  if ( *exitSlots != -1 )
  {
    do
    {
      srcSlot = &building[31 * *slotIndexPtr + 18];
      qmemcpy(destSlot, srcSlot, 0x1Cu);
      srcSlot += 28;
      destSlot[14] = *(_WORD *)srcSlot;
      *((_BYTE *)destSlot + 30) = srcSlot[2];
      *(_WORD *)&building[31 * *slotIndexPtr + 18] = -1;
      BUILDING_GARRISON_SERVICE_STATE(building, *slotIndexPtr) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
      movedSlotIndex = *slotIndexPtr++;
      ++movedCount;
      destSlot = (__int16 *)((char *)destSlot + 31);
      BUILDING_GARRISON_SERVICE_STATE(building, movedSlotIndex) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
    }
    while ( movedCount < 10 && *slotIndexPtr != -1 );
  }
  UnitStack_ClearRemainingActionPoints(newStackRecord, (DWORD)building, gameTime);
  Rules_LinkArmyFact(newStackRecord, v17, v18, gameTime, (char)destSlot, (DWORD)building);
  Rules_SyncArmyFactStrength(newStackRecord, 0, v19, (char)destSlot, (DWORD)building, gameTime);
  Building_OnGarrisonChange(*(unsigned __int16 *)(TILE_INDEX(*building, building[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v20, v21);
  UnitStack_UpdateVision(*(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1])));
  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(*(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1])), v22);
  Debug_Log(v23, (char)destSlot, (DWORD)building, (int)aBuildings_unit);
  Unit_DebugDumpFormationSizes((int)newStackRecord, (DWORD)building);
  return *(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1]));
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
int  Building_CountFreeGarrisonSlots(int buildingId)
{
  int buildingRecord; // esi
  int freeCount; // ebx
  int slotPtr; // eax
  int i; // edx
  int slotLimit; // ecx

  buildingRecord = UNIT_RECORD(buildingId);
  freeCount = 0;
  slotPtr = buildingRecord;
  for ( i = 0; ; ++i )
  {
    slotLimit = *(_BYTE *)(buildingRecord + 4) ? 12 : 10;
    if ( i >= slotLimit )
      break;
    if ( *(__int16 *)(slotPtr + 18) == -1 )
      ++freeCount;
    slotPtr += 31;
  }
  return freeCount;
}
// 5202E4: using guessed type int gameData;

//----- (0043E500) --------------------------------------------------------
signed int  Building_UnitGetInto(
        int unitStackId,
        int buildingId,
        char a3,
        signed int i,
        double gameTime)
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
  Debug_Log(unitStackId, buildingId, (DWORD)unitStackId, (int)aBuilding_unitg);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-log");
  Render_DrawSprite_v3(unitStackId, unitStackId);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-debug-dump");

  stack_record = UNIT_STACK(unitStackId);
  building_record = BUILDING_RECORD(buildingId);
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
  Unit_CompactSquad(stack, 0, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-compact-1");
  squad_count = Unit_GetSquadCount(stack_record);
  if ( !squad_count )
  {
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-unlink-empty");
    Rules_UnlinkArmyFact(stack, gameTime);
    Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-after-unlink-empty");
    return 1;
  }

  if ( squad_count <= Building_CountFreeGarrisonSlots(buildingId) )
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
  Unit_CompactSquad(stack, 0, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-finalize");
  Rules_LinkArmyFinalize(stack, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-link-fact");
  Rules_LinkArmyFact(stack, 0, 0, gameTime, 0, (DWORD)stack_record);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-sync-strength");
  Rules_SyncArmyFactStrength(stack, 0, 0, 0, (DWORD)stack_record, gameTime);
  Diagnostics_TraceBootstrapEvent("Building_UnitGetInto-before-garrison-change");
  if ( *(_DWORD *)(building_record + 463) )
    Building_OnGarrisonChange(buildingId, 0, gameTime);
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
signed int  Building_CanAcceptUnitStack(int stackIndex, int buildingId)
{
  int buildingRecord; // ecx
  int stackRecord; // edx
  unsigned __int8 buildingType; // al
  int v5; // edx
  int v6; // edx

  buildingRecord = UNIT_RECORD(buildingId);
  stackRecord = UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET;
  if ( *(_WORD *)(buildingRecord + 16) )
    return 0;
  buildingType = *(_BYTE *)(buildingRecord + 4);
  if ( !buildingType )
    return UnitStack_HasNormalCombatUnits(stackRecord);
  if ( buildingType > 1u )
    return buildingType == 2;
  if ( UnitStack_HasPeasantCargo(stackRecord) )
    return 0;
  return UnitStack_HasNormalCombatUnits(v5) || UnitStack_HasGoldCargo(v5) || UnitStack_HasSpecialPersonageUnits(v6);
}
// 43E7D7: variable 'v5' is possibly undefined
// 43E7F5: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043E820) --------------------------------------------------------
signed int  Building_HasUnitLicence(int building, unit_type unitType)
{
  int licenceEnd; // esi
  int hasLicence; // ecx

  licenceEnd = building + 12;
  hasLicence = 0;
  do
  {
    if ( *(char *)(building + 402) == unitType )
      hasLicence = 1;
    ++building;
  }
  while ( building != licenceEnd );
  return hasLicence;
}

//----- (0043E850) --------------------------------------------------------
BOOL  Building_BuyUnitLicence(int building, unit_type unitType, int a3, DWORD gameContext)
{
  int v5; // edx
  BOOL result; // eax
  int nationData; // eax
  unsigned int licenceCost; // esi
  int licenceSlotPtr; // edx
  int slotIndex; // eax

  Debug_Log(a3, building, gameContext, (int)aBuildingBuyUnitLicence);
  if ( Building_HasUnitLicence(building, unitType) )
    return 0;
  result = Building_IsUnitLicenceEligible((char *)building, unitType);
  if ( result )
  {
    nationData = gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(building + 2);
    licenceCost = (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * unitType];
    if ( !*(_DWORD *)(nationData + 140051) && *(int *)(nationData + 140055) >= 2 )
      licenceCost = (int)(75 * licenceCost) / 100;
    if ( licenceCost > *(_DWORD *)(building + 438) )
      return 0;
    licenceSlotPtr = building;
    slotIndex = 0;
    while ( *(char *)(licenceSlotPtr + 402) != -1 )
    {
      ++slotIndex;
      ++licenceSlotPtr;
      if ( slotIndex >= 12 )
      {
        if ( slotIndex == 12 )
          return 0;
        break;
      }
    }
    *(_DWORD *)(building + 438) -= licenceCost;
    *(_BYTE *)(building + slotIndex + 402) = unitType;
    return 1;
  }
  return result;
}
// 43E8D7: conditional instruction was optimized away because eax.4<C
// 43E86D: variable 'v5' is possibly undefined
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];
// 5202E4: using guessed type int gameData;

//----- (0043E940) --------------------------------------------------------
int  Building_RemoveUnitLicence(int building, unit_type unitType, DWORD gameContext)
{
  int activeProductionLicenceSlot; // eax
  int addonSlot; // edx

  Debug_Log(building, unitType, gameContext, (int)aBuildingRemoveUnitLicence);
  activeProductionLicenceSlot = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(building);
  if ( activeProductionLicenceSlot != -1 && *(signed __int8 *)(building + activeProductionLicenceSlot + 402) == unitType )
    Building_StopUnitProduction(building, unitType, gameContext);
  for ( addonSlot = 0; addonSlot < 12; ++addonSlot )
  {
    if ( *(signed __int8 *)(building + addonSlot + 402) == unitType )
    {
      *(_BYTE *)(building + addonSlot + 402) = -1;
      return building + addonSlot;
    }
  }
  return building + 12;
}

//----- (0043E9A0) --------------------------------------------------------
int  Building_SetUnitProduction(int building, char licenceSlot, DWORD gameContext)
{
  unsigned __int8 *buildingPtr; // ecx
  int slotIndex; // edx
  int result; // eax

  buildingPtr = (unsigned __int8 *)building;
  slotIndex = (unsigned __int8)licenceSlot;
  Debug_Log(building, licenceSlot, gameContext, (int)aBuildingSetUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(buildingPtr) = slotIndex;
  result = PLAYER_DATA_STRIDE * buildingPtr[2];
  BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) = g_UnitTypeProductionTime[88 * (char)buildingPtr[slotIndex + 402]];
  if ( !*(_DWORD *)(result + gameData + 140051)
    && *(int *)(result + gameData + 140055) >= 1
    && (char)BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr) > 1 )
  {
    --BUILDING_PRODUCTION_TURNS_REMAINING(buildingPtr);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EA10) --------------------------------------------------------
void  Building_StopUnitProduction(int building, char unitType, DWORD gameContext)
{
  Debug_Log(building, unitType, gameContext, (int)aBuildingStopUnitProduction);
  BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(building) = -1;
}

//----- (0043EA30) --------------------------------------------------------
_BYTE * Building_TrainUnit(int building, char garrisonSlot, DWORD gameContext)
{
  int slotIndex; // edx
  int buildingBase; // ecx
  _BYTE *result; // eax
  char trainingTurns; // bl
  char serviceStateBits; // bh

  slotIndex = (unsigned __int8)garrisonSlot;
  buildingBase = building;
  Debug_Log(building, garrisonSlot, gameContext, (int)aBuildingTrainUnit);
  result = (_BYTE *)(*(_BYTE *)(buildingBase + 31 * slotIndex + 30) & 3);
  if ( result != (_BYTE *)3 )
  {
    result = (_BYTE *)(buildingBase + BUILDING_GARRISON_SERVICE_STATE_OFFSET + slotIndex);
    if ( *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingBase + 2) + gameData + 140051) )
      trainingTurns = (*(_BYTE *)(buildingBase + 4) == 2) + 1;
    else
      trainingTurns = (*(_BYTE *)(buildingBase + 4) == 2) + 4;
    serviceStateBits = *result & 0xF8;
    *result = serviceStateBits;
    *result = trainingTurns & BUILDING_GARRISON_TRAINING_TURNS_MASK | serviceStateBits;
    BUILDING_GARRISON_SERVICE_STATE(buildingBase, slotIndex) &= 0xC7u;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043EAC0) --------------------------------------------------------
int  Building_ClearGarrisonTrainingTimer(int result, int building)
{
  BUILDING_GARRISON_SERVICE_STATE(building, result) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
  return result;
}

//----- (0043EAD0) --------------------------------------------------------
__int16  Building_RepairUnit(int building, int slotIndex, DWORD gameContext)
{
  int currentHealth; // eax
  unsigned __int8 *repairTimer; // edx
  unsigned __int8 repairTurns; // al

  Debug_Log(building, slotIndex, gameContext, (int)aBuildingRepairUnit);
  currentHealth = *(signed __int8 *)(building + 31 * slotIndex + 27);
  if ( currentHealth != 100 )
  {
    repairTimer = (unsigned __int8 *)(building + BUILDING_GARRISON_SERVICE_STATE_OFFSET + slotIndex);
    repairTurns = (*(_BYTE *)(building + 4) == 2) + 2;
    *repairTimer = *repairTimer & 0xC0 | ((repairTurns & 7) << 3);
  }
  return currentHealth;
}

//----- (0043EB40) --------------------------------------------------------
int  Building_ClearGarrisonRepairTimer(int result, int building)
{
  BUILDING_GARRISON_SERVICE_STATE(building, result) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
  return result;
}

//----- (0043EB50) --------------------------------------------------------
int  Building_CountGarrison(int building)
{
  int garrisonEnd; // ebx
  int count; // edx

  garrisonEnd = building + 372;
  count = 0;
  do
  {
    if ( *(__int16 *)(building + 18) != -1 )
      ++count;
    building += 31;
  }
  while ( building != garrisonEnd );
  return count;
}

//----- (0043EB80) --------------------------------------------------------
int  Building_CountSpecialPersonageGarrisonEntries(int building)
{
  int garrisonEnd; // ebx
  int count; // ecx
  int unitType; // edx

  garrisonEnd = building + 372;
  count = 0;
  do
  {
    while ( 1 )
    {
      unitType = *(__int16 *)(building + 18);
      if ( unitType != -1 )
        break;
LABEL_5:
      building += 31;
      if ( building == garrisonEnd )
        return count;
    }
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      ++count;
      goto LABEL_5;
    }
    building += 31;
  }
  while ( building != garrisonEnd );
  return count;
}

int  Building_DrawGarrisonRow(int building)
{
  return Building_CountSpecialPersonageGarrisonEntries(building);
}

//----- (0043EBC0) --------------------------------------------------------
int  Building_CountNonCombatGarrisonEntries(int building)
{
  int slotPtr; // edx
  int count; // ecx
  int garrisonEnd; // ebx
  int unitType; // eax

  slotPtr = building;
  count = 0;
  garrisonEnd = building + 372;
  do
  {
    while ( 1 )
    {
      unitType = *(__int16 *)(slotPtr + 18);
      if ( unitType != -1 )
        break;
LABEL_5:
      slotPtr += 31;
      if ( slotPtr == garrisonEnd )
        return count;
    }
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE
      || unitType == UNIT_TYPE_GOLD_CARGO
      || unitType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++count;
      goto LABEL_5;
    }
    slotPtr += 31;
  }
  while ( slotPtr != garrisonEnd );
  return count;
}

//----- (0043EC10) --------------------------------------------------------
signed int  Building_HasSpecialPersonageGarrisonEntries(int building)
{
  int slotIndex; // edx
  int unitType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    unitType = *(__int16 *)(building + 18);
    if ( unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++slotIndex;
    building += 31;
    if ( slotIndex >= 12 )
      return 0;
  }
  return 1;
}

//----- (0043EC40) --------------------------------------------------------
int  Building_CompactGarrison(unsigned __int8 *building, unsigned __int8 *a2, double gameTime)
{
  int writeIndex; // ebp
  int readIndex; // edx
  unsigned __int8 *movePtr; // eax
  unsigned __int8 *j; // ebx
  _BYTE *destPtr; // edi
  _BYTE *srcPtr; // esi
  int i; // [esp+4h] [ebp-20h]
  unsigned __int8 *slotPtr; // [esp+8h] [ebp-1Ch]

  writeIndex = 0;
  slotPtr = building;
  for ( i = 0; i < 11; ++i )
  {
    if ( *((__int16 *)slotPtr + 9) == -1 )
    {
      readIndex = writeIndex;
      movePtr = &building[31 * writeIndex];
      for ( j = &building[31 * writeIndex + 31]; readIndex < 11; destPtr[2] = srcPtr[2] )
      {
        destPtr = movePtr + 18;
        movePtr += 31;
        srcPtr = j + 18;
        j += 31;
        ++readIndex;
        qmemcpy(destPtr, srcPtr, 0x1Cu);
        srcPtr += 28;
        destPtr += 28;
        a2 = 0;
        *(_WORD *)destPtr = *(_WORD *)srcPtr;
      }
      *((_WORD *)movePtr + 9) = -1;
    }
    else
    {
      a2 = slotPtr + 31;
      ++writeIndex;
      slotPtr += 31;
    }
  }
  return Building_OnGarrisonChange(
           *(unsigned __int16 *)(TILE_INDEX(*building, building[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
           (int)a2,
           gameTime);
}
// 5202E4: using guessed type int gameData;

//----- (0043ED20) --------------------------------------------------------
BOOL  Building_IsUnitLicenceEligible(char *building, unit_type unitType)
{
  int buildingType; // eax
  int v5; // edx
  char requiredTechLevel; // al
  int i; // eax
  int smithReqType; // edx
  int j; // eax
  int workshopReqType; // edx

  buildingType = building[4];
  if ( !buildingType )
    return 0;
  v5 = 88 * unitType;
  requiredTechLevel = buildingType == 2
     ? g_UnitTypeProductionRequiredTechLevelMode2[v5]
     : g_UnitTypeProductionRequiredTechLevelOtherModes[v5];
  if ( (unsigned __int8)(building[444] & 7) < (unsigned __int8)requiredTechLevel )
    return 0;
  if ( (building[416] & BUILDING_ADDON_FLAG_SMITHS) == 0 )
  {
    for ( i = 0; ; ++i )
    {
      smithReqType = g_ProductionLicenceSmithsRequiredUnitTypes[i];
      if ( smithReqType == -1 || smithReqType == unitType )
        break;
    }
    if ( g_ProductionLicenceSmithsRequiredUnitTypes[i] == unitType )
      return 0;
  }
  if ( (building[416] & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
    return 1;
  for ( j = 0; ; ++j )
  {
    workshopReqType = g_ProductionLicenceWorkshopRequiredUnitTypes[j];
    if ( workshopReqType == -1 || workshopReqType == unitType )
      break;
  }
  return g_ProductionLicenceWorkshopRequiredUnitTypes[j] != unitType;
}

//----- (0043EDC0) --------------------------------------------------------
int  Building_AdjustAllGarrisonMoraleByDelta(int building, int moraleDelta)
{
  int slot; // ebp
  int slot_index; // ecx
  int result; // eax

  slot = building + 18;
  result = 0;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)slot != -1 )
      result = UnitSlot_AdjustMoraleByPredicate(slot, moraleDelta, UnitSlot_PredicateAlways);
    slot += 31;
  }
  return result;
}

//----- (0043EE10) --------------------------------------------------------
int  Building_CycleAllGarrisonOrdersOnce(int building)
{
  int garrisonBase; // esi
  int slotIndex; // edx
  int slotPtr; // ecx
  int result; // eax
  int v5; // edx
  int v6; // ecx

  garrisonBase = building + 18;
  slotIndex = 0;
  slotPtr = building;
  do
  {
    while ( 1 )
    {
      result = 31 * slotIndex;
      if ( *(__int16 *)(slotPtr + 18) != -1 )
        break;
      ++slotIndex;
      slotPtr += 31;
      if ( slotIndex >= 12 )
        return result;
    }
    result = UnitSlot_CycleOrderState(garrisonBase + result);
    slotIndex = v5 + 1;
    slotPtr = v6 + 31;
  }
  while ( slotIndex < 12 );
  return result;
}
// 43EE41: variable 'v5' is possibly undefined
// 43EE42: variable 'v6' is possibly undefined

//----- (0043EE50) --------------------------------------------------------
signed int  Building_GetTaxBurdenTier(int building)
{
  unsigned __int16 population; // ax
  int populationTier; // edx
  int thresholdIndex; // edx
  signed int result; // eax

  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  if ( population >= 0x1F4u )
  {
    if ( population >= 0x3E8u )
      populationTier = 2;
    else
      populationTier = 1;
  }
  else
  {
    populationTier = 0;
  }
  thresholdIndex = 4 * populationTier;
  result = 0;
  while ( (unsigned __int8)(*(_BYTE *)(building + 436) & 0x3F) > (unsigned __int8)g_SettlementTaxBurdenThresholds[thresholdIndex] )
  {
    ++result;
    ++thresholdIndex;
    if ( result > 3 )
      return 3;
  }
  return result;
}
// 43EE8A: conditional instruction was optimized away because eax.4<4

//----- (0043EED0) --------------------------------------------------------
__int16  Building_UpdatePopulationGrowth(int buildingRecord)
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

  building = (uintptr_t)(unsigned int)buildingRecord;
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
    case TAX_BURDEN_TIER_LOW:
      growth_percent += 5;
      break;
    case TAX_BURDEN_TIER_HIGH:
      growth_percent -= 4;
      break;
    case TAX_BURDEN_TIER_SEVERE:
      growth_percent -= (int)Rng_RandRange(10, 15);
      break;
    default:
      break;
  }
  if ( (*(_BYTE *)(building + 416) & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
    growth_percent += 3;
  if ( (*(_BYTE *)(building + 416) & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
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
int  Building_CollectGoldIncome(int building)
{
  int incomeDivisor; // ecx
  unsigned __int16 population; // ax
  int goldIncome; // ecx
  int result; // eax
  int currentGold; // esi

  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(building + 2) + 140051) )
    incomeDivisor = 400;
  else
    incomeDivisor = 200;
  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  goldIncome = (*(_BYTE *)(building + 436) & 0x3F) * population / incomeDivisor;
  result = *(char *)(building + 434);
  if ( result < 25 )
  {
    result = goldIncome / 2;
    goldIncome /= 2;
  }
  if ( (*(_BYTE *)(building + 435) & 7) != 0 )
    goldIncome = 0;
  currentGold = *(_DWORD *)(building + 438);
  *(_WORD *)(building + 442) = goldIncome;
  *(_DWORD *)(building + 438) = goldIncome + currentGold;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043F160) --------------------------------------------------------
__int16  Building_UpdatePlagueState(unsigned int buildingRecord)
{
  uintptr_t building; // ecx
  unsigned int plague_state; // eax
  unsigned int population; // ebx
  unsigned int plague_roll; // eax
  unsigned __int16 population_flags; // dx
  unsigned int result; // eax
  unsigned char building_state; // dl

  building = (uintptr_t)buildingRecord;
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
int  Building_GetTotalValue(int building)
{
  int goldReserve; // ecx
  unsigned __int16 population; // ax
  int totalValue; // ecx
  int licencePtr; // eax
  int licenceEnd; // ebx
  int licenceType; // edx

  goldReserve = *(_DWORD *)(building + 438);
  population = *(_WORD *)(building + 430);
  HIBYTE(population) &= 0xFu;
  totalValue = 190 * (*(_DWORD *)(building + 416) << 29 >> 31)
     + 200 * (*(_DWORD *)(building + 416) << 30 >> 31)
     + 230 * (*(_DWORD *)(building + 416) << 27 >> 31)
     + 400 * (*(_DWORD *)(building + 416) << 28 >> 31)
     + 200 * (*(_DWORD *)(building + 416) & BUILDING_ADDON_FLAG_HOSPITAL)
     + population
     + goldReserve;
  licencePtr = building;
  licenceEnd = building + 12;
  do
  {
    licenceType = *(char *)(licencePtr + 402);
    if ( licenceType != -1 )
      totalValue += (unsigned __int16)g_UnitTypeProductionLicenceCost[44 * licenceType];
    ++licencePtr;
  }
  while ( licencePtr != licenceEnd );
  return totalValue;
}
// 5125B1: using guessed type __int16 g_UnitTypeProductionLicenceCost[];

//----- (0043F340) --------------------------------------------------------
int  AI_TickNationPostTurn(int playerIndex)
{
  int totalValue; // ecx
  int buildingIndex; // edx
  int buildingOffset; // ebx
  int buildingState; // eax
  int buildingRecord; // eax
  int buildingValue; // eax
  int v7; // ecx
  int i; // edi
  int j; // eax
  int cargoType; // edx

  totalValue = 0;
  buildingIndex = 0;
  buildingOffset = 0;
  do
  {
    buildingState = *(char *)(buildingOffset + gameData + 509678);
    if ( (buildingState == 2 || buildingState == 1) && *(unsigned __int8 *)(buildingOffset + gameData + 509676) == playerIndex && buildingIndex >= 0 )
    {
      buildingRecord = buildingOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( (unsigned int)*(char *)(buildingRecord + 4) < 4 && *(__int16 *)(buildingRecord + 16) != -1 )
      {
        buildingValue = Building_GetTotalValue(buildingRecord);
        totalValue = buildingValue + v7;
      }
    }
    ++buildingIndex;
    buildingOffset += 467;
  }
  while ( buildingIndex < 100 );
  for ( i = 0; i != 362500; i += 725 )
  {
    if ( *(unsigned __int8 *)(i + gameData + 147178) == playerIndex && *(__int16 *)(i + gameData + 147180) != -1 )
    {
      for ( j = 0; j != 310; j += 31 )
      {
        cargoType = *(__int16 *)(i + gameData + j + 147180);
        if ( cargoType == UNIT_TYPE_GOLD_CARGO || cargoType == UNIT_TYPE_PEASANT_CARGO )
          totalValue += *(char *)(i + gameData + j + 147189);
      }
    }
  }
  return totalValue;
}
// 43F391: conditional instruction was optimized away because edx.4<64u
// 43F3A0: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 43F3B5: variable 'v7' is possibly undefined
// 43F3B7: variable 'v2' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0043F460) --------------------------------------------------------
int  Player_CalcAvailableStrongholdFunds(int playerIndex)
{
  int totalFunds; // edi
  int buildingIndex; // eax
  int buildingOffset; // edx
  int buildingState; // ecx
  int buildingRecord; // ecx

  totalFunds = 0;
  buildingIndex = 0;
  buildingOffset = 0;
  do
  {
    buildingState = *(char *)(gameData + buildingOffset + 509678);
    if ( (buildingState == 2 || buildingState == 1) && *(unsigned __int8 *)(buildingOffset + gameData + 509676) == playerIndex && buildingIndex >= 0 )
    {
      buildingRecord = buildingOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( (unsigned int)*(char *)(buildingRecord + 4) < 4 && *(__int16 *)(buildingRecord + 16) != -1 )
        totalFunds += *(_DWORD *)(buildingOffset + gameData + 510112);
    }
    ++buildingIndex;
    buildingOffset += 467;
  }
  while ( buildingIndex < 100 );
  return totalFunds;
}
// 43F4AE: conditional instruction was optimized away because eax.4<64u
// 43F4BE: simplified comparisons for 'esi.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;

//----- (0043F500) --------------------------------------------------------
int  Player_SpendStrongholdFundsEvenly(int playerIndex, signed int remaining)
{
  int strongholdCount; // ecx
  int i; // eax
  int buildingState; // edx
  unsigned int sharePerStronghold; // esi
  int buildingOffset; // edx
  int result; // eax
  unsigned int availableFunds; // ebp

  do
  {
    strongholdCount = 0;
    for ( i = 0; i != 46700; i += 467 )
    {
      buildingState = *(char *)(gameData + i + 509678);
      if ( (buildingState == 2 || buildingState == 1)
        && *(unsigned __int8 *)(i + gameData + 509676) == playerIndex
        && *(_DWORD *)(i + gameData + 510112) )
      {
        ++strongholdCount;
      }
    }
    sharePerStronghold = remaining / strongholdCount;
    if ( !(remaining / strongholdCount) )
    {
      strongholdCount = 1;
      sharePerStronghold = remaining;
    }
    buildingOffset = 0;
    do
    {
      result = *(char *)(buildingOffset + gameData + 509678);
      if ( result == 2 || result == 1 )
      {
        result = buildingOffset + gameData;
        if ( playerIndex == *(unsigned __int8 *)(buildingOffset + gameData + 509676) )
        {
          availableFunds = *(_DWORD *)(result + 510112);
          if ( availableFunds )
          {
            --strongholdCount;
            if ( sharePerStronghold > availableFunds )
            {
              *(_DWORD *)(result + 510112) = 0;
              remaining -= availableFunds;
            }
            else
            {
              remaining -= sharePerStronghold;
              *(_DWORD *)(result + 510112) = availableFunds - sharePerStronghold;
            }
          }
        }
      }
      buildingOffset += 467;
    }
    while ( buildingOffset < 46700 && strongholdCount );
  }
  while ( remaining );
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
        int buildingKind,
        int variantIndex,
        signed int orientation,
        int assetSet,
        DWORD allocContext,
        signed int a6,
        int frameIndex)
{
  int entry_index;
  int entry_offset;
  unsigned int oldest_tick;
  int i;
  signed int orientationBaseIndex; // eax
  signed int spriteSubIndex; // ebx
  int spriteAssetIndex; // ebx
  unsigned __int8 mapThemeIndex; // al
  int orientationSubIndex; // eax
  int variantSubIndex; // ebx
  int spriteHandleTheme0; // eax
  int spriteHandleTheme1; // eax
  int spriteHandleTheme2; // eax

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
  g_BuildingSpriteCache[entry_offset] = (char)buildingKind;
  g_BuildingSpriteCacheKeyCol2[entry_offset] = (char)variantIndex;
  g_BuildingSpriteCacheKeyCol3[entry_offset] = (char)assetSet;
  g_BuildingSpriteCacheKeyCol4Signed[entry_offset] = (char)orientation;
  g_BuildingSpriteCacheKeyCol5[entry_offset] = (char)frameIndex;
  *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(entry_index, entry_offset);
  if ( buildingKind )
  {
    if ( orientation >= 3 )
    {
      variantSubIndex = 4 * variantIndex + 12 + frameIndex;
    }
    else
    {
      if ( orientation == -1 )
        orientationSubIndex = frameIndex + 32;
      else
        orientationSubIndex = frameIndex + 4 * orientation;
      variantSubIndex = orientationSubIndex;
    }
    spriteAssetIndex = 36 * assetSet + 180 * (buildingKind - 1) + 45 + variantSubIndex;
  }
  else
  {
    if ( orientation >= 3 )
    {
      spriteSubIndex = variantIndex + 3;
    }
    else
    {
      if ( orientation == -1 )
        orientationBaseIndex = 8;
      else
        orientationBaseIndex = orientation;
      spriteSubIndex = orientationBaseIndex;
    }
    spriteAssetIndex = 9 * assetSet + spriteSubIndex;
  }
  mapThemeIndex = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
  if ( mapThemeIndex == 0 )
  {
    spriteHandleTheme0 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme0 )
      spriteHandleTheme0 = DLXSprite_LoadCachedEntry(spriteHandleTheme0, aBuildin1_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme0;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( mapThemeIndex == 1 )
  {
    spriteHandleTheme1 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme1 )
      spriteHandleTheme1 = DLXSprite_LoadCachedEntry(spriteHandleTheme1, aBuildin2_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme1;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  if ( mapThemeIndex == 2 )
  {
    spriteHandleTheme2 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);
    if ( spriteHandleTheme2 )
      spriteHandleTheme2 = DLXSprite_LoadCachedEntry(spriteHandleTheme2, aBuildin3_s32, spriteAssetIndex);
    *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5) = spriteHandleTheme2;
    return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
  }
  return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
}
// 5202E4: using guessed type int gameData;
// 5438ED: using guessed type int dword_5438ED;
// 5438F1: using guessed type int dword_5438F1;

//----- (0043F880) --------------------------------------------------------
int  BuildingSpriteCache_GetOrLoadEntry(DWORD buildingKind, int variantIndex, signed int orientation, int assetSet, int frameIndex)
{
  int entry_index;

  for ( entry_index = 0; entry_index < BUILDING_SPRITE_CACHE_RECORD_COUNT; ++entry_index )
  {
    int entry_offset;

    entry_offset = BUILDING_SPRITE_CACHE_RECORD_STRIDE * entry_index;
    if ( (signed char)g_BuildingSpriteCache[entry_offset] == (int)buildingKind )
    {
      if ( (unsigned char)g_BuildingSpriteCacheKeyCol2[entry_offset] == (unsigned int)variantIndex )
      {
        if ( (unsigned char)g_BuildingSpriteCacheKeyCol3[entry_offset] == (unsigned int)assetSet )
        {
          if ( (signed char)g_BuildingSpriteCacheKeyCol4Signed[entry_offset] == orientation )
          {
            if ( (unsigned char)g_BuildingSpriteCacheKeyCol5[entry_offset] == (unsigned int)frameIndex )
            {
              *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 9) = Time_Now(frameIndex, entry_index);
              return *(int *)(void *)(g_BuildingSpriteCache + entry_offset + 5);
            }
          }
        }
      }
    }
  }
  return BuildingSpriteCache_LoadEntry(buildingKind, variantIndex, orientation, assetSet, buildingKind, variantIndex, frameIndex);
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
  int count; // edx
  int i; // eax

  count = 0;
  for ( i = 0; i != 650; i += 13 )
  {
    if ( g_BuildingSpriteCache[i] != -1 )
      ++count;
  }
  return count;
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
    if ( i >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    for ( j = 0; j < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); j = v4 + 1 )
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
signed int  MapTile_GetReligiousSiteCategory(int tileX, int tileY)
{
  signed int result; // eax

  switch ( *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY + 2) )
  {
    case TILE_OVERLAY_SHRINE_A:
    case TILE_OVERLAY_SHRINE_B:
    case TILE_OVERLAY_SHRINE_C:
      result = RELIGIOUS_SITE_CATEGORY_SHRINE;
      break;
    case TILE_OVERLAY_EMPTY_SHRINE_A:
    case TILE_OVERLAY_EMPTY_SHRINE_B:
    case TILE_OVERLAY_EMPTY_SHRINE_C:
      result = RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE;
      break;
    case TILE_OVERLAY_CULT_PLACE_A:
    case TILE_OVERLAY_CULT_PLACE_B:
    case TILE_OVERLAY_CULT_PLACE_C:
      result = RELIGIOUS_SITE_CATEGORY_CULT_PLACE;
      break;
    case TILE_OVERLAY_EMPTY_CULT_PLACE_A:
    case TILE_OVERLAY_EMPTY_CULT_PLACE_B:
    case TILE_OVERLAY_EMPTY_CULT_PLACE_C:
      result = RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE;
      break;
    default:
      result = RELIGIOUS_SITE_CATEGORY_NONE;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FBA0) --------------------------------------------------------
int * Temple_GenerateApproachTrack(int stackIndex, int tileX, int a3, int tileY)
{
  int tile_column_offset; // ebp
  int tile_record_offset; // eax
  unsigned __int16 saved_site_word; // dx
  int current_y; // ebx
  int *result; // eax

  (void)a3;
  tile_column_offset = TILE_TERRAIN_ROW_STRIDE * tileX;
  tile_record_offset = tile_column_offset + 14 * tileY;
  Debug_Log(stackIndex, tileX, tileY, (int)aUnit_movetra_2);
  saved_site_word = *(_WORD *)(gameData + tile_record_offset + 2);
  *(_WORD *)(gameData + tile_record_offset + 2) = -1;
  current_y = *(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + 147176);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_request", stackIndex, tileX, tileY, saved_site_word);
  result = Unit_MoveTrack(
             stackIndex,
             *(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET),
             tileX,
             current_y,
             tileX,
             tileY);
  *(_WORD *)(gameData + tile_record_offset + 2) = saved_site_word;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent("temple_track_result", stackIndex, tileX, tileY, result ? *result : -1);
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0043FC60) --------------------------------------------------------
__int16 * Temple_SpawnGiftUnitGroup(int tileX, int tileY, double gameTime)
{
  char v3; // cl
  signed int giftUnitCount; // ebp
  _WORD *scriptedSlotPtr; // edi
  int i; // esi
  __int16 *result; // eax
  signed int spawnedCount; // edi
  _WORD *randomSlotPtr; // esi
  int missionIndex; // ebx
  unsigned int troopRoll; // eax
  char v12; // cl
  char ownerFaction; // bl
  unit_type unitType; // edx
  unsigned int monsterRoll; // eax
  char v16; // cl
  _WORD unitStack[172]; // [esp+0h] [ebp-170h] BYREF
  int siteX; // [esp+158h] [ebp-18h]
  int siteY; // [esp+15Ch] [ebp-14h]

  siteX = tileX;
  siteY = tileY;
  giftUnitCount = Rng_RandRange(1, 5);
  if ( ACTIVE_MISSION_INDEX == 2 && siteX == 95 && siteY == 16 || ACTIVE_MISSION_INDEX == 12 && siteX == 58 && siteY == 77 )
  {
    scriptedSlotPtr = unitStack;
    for ( i = 0; i != 4; ++i )
    {
      UnitSlot_InitFromType((int)scriptedSlotPtr, g_TempleGiftUnitPool_ScriptedRam[i], v3);
      scriptedSlotPtr = (_WORD *)((char *)scriptedSlotPtr + 31);
    }
    giftUnitCount = 4;
  }
  else
  {
    spawnedCount = 0;
    if ( giftUnitCount > 0 )
    {
      randomSlotPtr = unitStack;
      do
      {
        missionIndex = ACTIVE_MISSION_INDEX;
        if ( missionIndex == 2 || missionIndex == 6 || missionIndex == 12 || missionIndex == 16 )
        {
          troopRoll = Rng_RandRange(0, 6);
          ownerFaction = v12;
          unitType = g_TempleGiftUnitPool_HumanTroops[troopRoll];
        }
        else
        {
          monsterRoll = Rng_RandRange(0, 4);
          ownerFaction = v16;
          unitType = g_TempleGiftUnitPool_MinorMonsters[monsterRoll];
        }
        UnitSlot_InitFromType((int)randomSlotPtr, unitType, ownerFaction);
        ++spawnedCount;
        randomSlotPtr = (_WORD *)((char *)randomSlotPtr + 31);
      }
      while ( spawnedCount < giftUnitCount );
    }
  }
  *(_WORD *)((char *)unitStack + 31 * giftUnitCount) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(siteX, siteY, (unsigned __int8 *)unitStack, gameTime);
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
__int16 * Temple_SpawnGiftGoldCargoStack(signed int goldAmount, int originX, char ownerFaction, int originY, double gameTime)
{
  int cargoSlotCount; // esi
  int fullCargoByteLimit; // ebp
  int i; // ecx
  signed int goldTotal; // eax
  int lastSlotIndex; // esi
  char partialGold; // dl
  __int16 *result; // eax
  _WORD cargoStack[4]; // [esp+0h] [ebp-170h] BYREF
  char v14[335]; // [esp+9h] [ebp-167h]
  int spawnY; // [esp+158h] [ebp-18h]
  int spawnX; // [esp+15Ch] [ebp-14h]
  signed int goldAmountCopy; // [esp+160h] [ebp-10h]

  goldAmountCopy = goldAmount;
  spawnX = originX;
  spawnY = originY;
  cargoSlotCount = 0;
  fullCargoByteLimit = 31 * (goldAmount / 100);
  for ( i = 0; i <= fullCargoByteLimit; UnitSlot_InitFromType((int)cargoStack + i, UNIT_TYPE_GOLD_CARGO, ownerFaction) )
    ++cargoSlotCount;
  goldTotal = goldAmountCopy;
  *(_WORD *)((char *)cargoStack + i) = -1;
  lastSlotIndex = cargoSlotCount - 1;
  partialGold = 100 * (goldTotal % 100) / 100;
  v14[31 * lastSlotIndex] = partialGold;
  if ( !partialGold )
    *(_WORD *)((char *)cargoStack + 31 * lastSlotIndex) = -1;
  result = (__int16 *)Unit_CreateNearbyUnitGroup(spawnX, spawnY, (unsigned __int8 *)cargoStack, gameTime);
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
  spriteSetPtr = (_DWORD *)Mem_Alloc(4112, a3, playSound, gameContext);
  if ( spriteSetPtr )
    spriteSetPtr = DLXSpriteSet_Load(spriteSetPtr, playSound);
  spriteSet = spriteSetPtr;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  DLX_GetSpriteWidth((int)spriteSet, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)spriteSet, 0x16u);
  maxExtent = v7 + 6;
  if ( (unsigned __int16)SpriteWidth > v7 + 6 )
    maxExtent = SpriteWidth;
  popupHeight = maxExtent;
  Surface = (_DWORD *)Mem_Alloc(188, v7, playSound, gameContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, popupHeight);
  surface = (int)Surface;
  Render_FillRect(0, Surface, 150, 0, SCREEN_MAX_X, popupHeight + 149, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)spriteSet, 22);
  deviceMethods = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(deviceMethods + 52))(
    150,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  DLX_GetSpriteHeight((int)spriteSet, 0x16u);
  v12 = DLX_GetSpriteForChar((int)spriteSet, 23);
  deviceMethods = *((_DWORD *)g_RenderDevice + 46);
  deviceMethodsPtr = deviceMethods;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(deviceMethods + 52))(
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
    iconSprite = DLX_GetSpriteForChar((int)spriteSet, iconIndex);
    deviceMethodsPtr = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(deviceMethodsPtr + 52))(
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
  UI_DrawTextFmt(surface, 70, 569, 210, 6, messageText);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping(v14) && !DD_IsLost(v15) )
    DD_Pump(v19, 0);
  Render_Begin((int)g_RenderState, 0);
  if ( playSoundFlag )
  {
    artifactSoundId = iconIndex;
    if ( iconIndex == -1 )
      artifactSoundId = 7;
    Audio_PlayArtifactSound(artifactSoundId);
  }
  Render_Pump();
  Render_FillRect((_DWORD *)surface, 0, 0, 0, SCREEN_MAX_X, popupHeight - 1, 0, 0x96u);
  Render_Present((int)g_RenderState);
  if ( surface )
    (**(void (***)(void))(surface + 184))();
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
_DWORD * Temple_Random(outcomeTable, a2, a3, a4)
_DWORD *outcomeTable;
int a2;
char a3;
DWORD a4;
{
  int totalWeight; // ecx
  _DWORD *scanPtr; // eax
  int entryWeight; // ebx
  int entrySentinel; // edi
  signed int roll; // ebx
  int v11; // ecx
  signed int cumulative; // edx
  _DWORD *result; // eax

  Debug_Log(a2, a3, a4, (int)aTemple_random);
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
  Debug_Log(v11, roll, a4, (int)a__RDSum_probD);
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

  Debug_Log(tileY, tileX, giftType, (int)aTemple_process);
  switch ( giftType )
  {
    case TEMPLE_GIFT_SPAWN_UNITS:
      Temple_SpawnGiftUnitGroup(tileX, v7, gameTime);
      return;
    case TEMPLE_GIFT_KILL_STACK:
      UI_StartTileBlinkFlash(*unitStack, unitStack[1], v8);
      Unit_Kill((int)unitStack, tileX, giftType, gameTime);
      return;
    case TEMPLE_GIFT_REST:
      UnitStack_AdjustFatigueByPredicate(unitStack, -100, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v9);
      return;
    case TEMPLE_GIFT_BLESS_MORALE:
      UnitStack_AdjustMoraleByPredicate(unitStack, 20, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v10);
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
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v14);
      return;
    case TEMPLE_GIFT_CYCLE_ORDERS_3:
      do
        UnitStack_CycleAllSlotOrders(unitStack, giftType, gameTime);
      while ( v17 < 3 );
      goto LABEL_15;
    case TEMPLE_GIFT_BLESS_MORALE_MINOR:
      UnitStack_AdjustMoraleByPredicate(unitStack, 2, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), unitStack[1], v18);
      return;
    case TEMPLE_GIFT_CYCLE_ORDERS_2:
      do
        UnitStack_CycleAllSlotOrders(unitStack, giftType, gameTime);
      while ( v19 < 2 );
LABEL_15:
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), gameData + 200 * *unitStack, v16);
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
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v20);
      break;
    case TEMPLE_GIFT_CURSE_MORALE_FATIGUE:
      UnitStack_AdjustMoraleByPredicate(unitStack, -1, UnitSlot_PredicateAlways, giftType, gameTime);
      UnitStack_AdjustFatigueByPredicate(unitStack, 50, UnitSlot_PredicateAlways, giftType, gameTime);
      UI_StartUnitBlinkFlash(*(unsigned __int16 *)(TILE_INDEX(*unitStack, unitStack[1])), 200 * *unitStack + gameData, v21);
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
  int v6; // edx
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
  int cultActiveFlag; // ecx
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
  Debug_Log(tile_x, tile_y, gameContext, (int)aTemple_unitget);
  unitStack = (__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
  Diagnostics_TraceWorldMapActionEvent("temple_unit_getinto_enter", stack_index, tile_x, tile_y, MapTile_GetReligiousSiteCategory(tile_x, tile_y));
  playerData = gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
  if ( *(_DWORD *)(playerData + 140063) )
  {
    if ( *(_DWORD *)(playerData + 140051) )
      outcomeTable = &g_TempleGiftOutcomeTable_OwnCultActive;
    else
      outcomeTable = &g_TempleGiftOutcomeTable_OwnCultInactive;
  }
  else if ( *(_DWORD *)(playerData + 140051) )
  {
    outcomeTable = &g_TempleGiftOutcomeTable_ForeignCultActive;
  }
  else
  {
    outcomeTable = &g_TempleGiftOutcomeTable_ForeignCultInactive;
  }
  siteCategory = MapTile_GetReligiousSiteCategory(siteX, siteY);
  playerDataOffset = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
  ownCultFlag = *(_DWORD *)(gameData + playerDataOffset + 140063);
  if ( ownCultFlag && (siteCategory == 3 || siteCategory == 4)
    || (LOBYTE(playerDataOffset) = gameData, !*(_DWORD *)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData + 140063))
    && (siteCategory == 1 || siteCategory == 2) )
  {
    Debug_Log(ownCultFlag, playerDataOffset, (DWORD)unitStack, (int)aTemple_unitg_0);
    sacrilegeTexts[0] = (int)g_TempleSacrilegeUnitKilledTexts[0];
    sacrilegeTexts[1] = (int)g_TempleSacrilegeUnitKilledTexts[1];
    sacrilegeTexts[2] = (int)g_TempleSacrilegeUnitKilledTexts[2];
    if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + 140051) )
    {
      LOBYTE(playerDataOffset) = 1;
      Temple_ShowOutcomePopup(sacrilegeTexts[(unsigned __int8)g_LanguageIndex], 0, v13, 1, (DWORD)unitStack);
    }
    UI_StartTileBlinkFlash(*unitStack, unitStack[1], v13);
    return Unit_Kill((int)unitStack, playerDataOffset, (DWORD)unitStack, gameTime);
  }
  else
  {
    missionIndex = ACTIVE_MISSION_INDEX;
    if ( missionIndex == 1 || missionIndex == 11 )
    {
      result = 14 * siteY;
      ++*(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * siteX + TILE_TERRAIN_RECORD_STRIDE * siteY + 2);
      Diagnostics_TraceWorldMapActionEvent(
        "temple_unit_getinto_mission_site_increment",
        stack_index,
        siteX,
        siteY,
        MapTile_GetReligiousSiteCategory(siteX, siteY));
    }
    else if ( siteCategory == 2 || siteCategory == 4 )
    {
      Debug_Log(missionIndex, gameData, (DWORD)unitStack, (int)aTemple_unitg_2);
      giftRewardTexts[0] = (int)g_TempleGiftRewardText[0];
      giftRewardTexts[1] = (int)g_TempleGiftRewardText[1];
      giftRewardTexts[2] = (int)g_TempleGiftRewardText[2];
      giftEmptyTexts[0] = (int)g_TempleGiftEmptyText[0];
      giftEmptyTexts[1] = (int)g_TempleGiftEmptyText[1];
      giftEmptyTexts[2] = (int)g_TempleGiftEmptyText[2];
      result = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData;
      if ( *(_DWORD *)(result + 140051) )
      {
        ownCultFlagValue = *(_DWORD *)(result + 140063);
        if ( ownCultFlagValue )
          return Temple_ShowOutcomePopup(giftRewardTexts[(unsigned __int8)g_LanguageIndex], -1, ownCultFlagValue, 0, (DWORD)unitStack);
        else
          return Temple_ShowOutcomePopup(giftEmptyTexts[(unsigned __int8)g_LanguageIndex], -1, 0, 0, (DWORD)unitStack);
      }
    }
    else
    {
      outcomeTablePtr = outcomeTable;
      outcomePtr = Temple_Random(outcomeTable, missionIndex, gameData, (DWORD)unitStack);
      activeMission = ACTIVE_MISSION_INDEX;
      if ( (activeMission == 2 || activeMission == 6 || activeMission == 12 || activeMission == 16)
        && *(_DWORD *)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4) + gameData + 140051) )
      {
        if ( ACTIVE_MISSION_INDEX == 2 && siteX == 95 && siteY == 16
          || ACTIVE_MISSION_INDEX == 12 && siteX == 58 && siteY == 77 )
        {
          outcomePtr = (DWORD *)&g_TempleGiftOutcomeTable_OwnCultActive;
        }
        else
        {
          while ( *outcomePtr && *outcomePtr != 15 )
            outcomePtr = Temple_Random(outcomeTablePtr, v17, playerDataOffset, (DWORD)unitStack);
        }
      }
      Debug_Log(v17, playerDataOffset, (DWORD)unitStack, (int)aTemple_unitg_1);
      playerDataOffset2 = PLAYER_DATA_STRIDE * *((unsigned __int8 *)unitStack + 4);
      cultActiveFlag = *(_DWORD *)(playerDataOffset2 + gameData + 140051);
      if ( cultActiveFlag )
      {
        isOwnCult = *(_DWORD *)(playerDataOffset2 + gameData + 140063);
        if ( isOwnCult )
          transitionName = aSw_chs;
        else
          transitionName = aSw_pog;
        Win_PlayModeChangeFrameTransition(transitionName, 1, cultActiveFlag, isOwnCult, (DWORD)unitStack);
        Temple_ShowOutcomePopup(outcomePtr[(unsigned __int8)g_LanguageIndex + 3], outcomePtr[2], v24, 1, (DWORD)unitStack);
      }
      Temple_ProcessGift(*outcomePtr, unitStack, siteY, siteX, gameTime);
      siteRowBase = gameData + TILE_TERRAIN_ROW_STRIDE * siteX;
      LOWORD(siteOverlayWord) = *(_WORD *)(siteRowBase + 14 * siteY + 2);
      *(_WORD *)(siteRowBase + 14 * siteY + 2) = ++siteOverlayWord;
      return (int)Rules_RetractTempleFact(siteX, siteOverlayWord, siteRowBase, (DWORD)unitStack);
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
  int v18; // [esp+0h] [ebp-50h]
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
    Building_UnitsLeave((unsigned __int8 *)g_BuildingUIRecordPtr, selectedSlots, gameTime);
    Audio_PlaySoundEffectByName(aDclose_1, 64);
    spriteFrame = 12;
    g_RenderDevice = &g_MainRenderDevice;
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
  Surface = (_DWORD *)Mem_Alloc(188, a1, a2, renderContext);
  if ( Surface )
  {
    surfaceWidth = DLX_GetSpriteWidth(g_DemoTextDLXSpriteSet, 0) + 1;
    SpriteHeight = DLX_GetSpriteHeight(g_DemoTextDLXSpriteSet, 0);
    Surface = Render_CreateSurface(v16, SpriteHeight + 1, surfaceWidth);
  }
  surface = Surface;
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
  slotIndex = 0;
  slotOffset = 0;
  spriteSetIndex = 0;
  do
  {
    if ( *(__int16 *)(slotOffset + g_BuildingUIRecordPtr + 18) == -1 )
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
      DLX_GetSpriteForChar(g_BuildingUnitsPopupSlotSpriteSets[spriteSetIndex], 0);
      renderVtable = *((_DWORD *)g_RenderDevice + 46);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(renderVtable + 52))(-1, -1, -1, -1, 1, 0, 0);
      if ( g_BuildingUnitsPopupSelectedSlots[slotIndex] )
      {
        v9 = DLX_GetSpriteForChar(g_MarksSpriteSet, 5);
        renderVtable = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(renderVtable + 52))(
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
      if ( *(_BYTE *)(slotOffset + g_BuildingUIRecordPtr + 28) )
      {
        v10 = DLX_GetSpriteForChar(g_DemoTextDLXSpriteSet, 3);
        renderVtable = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(renderVtable + 52))(
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
        (int)aD_78);
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
  Render_Present((int)g_RenderState);
  if ( surface )
    (*(void (**)(void))surface[46])();
  result = savedRenderDevice;
  g_RenderDevice = savedRenderDevice;
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
  int v27; // [esp+70h] [ebp-4h]

  v27 = a2;
  savedRenderDevice = g_RenderDevice;
  g_BuildingUIRecordPtr = UNIT_RECORD(unitStackId);
  g_TempleOutcomePopupCloseFlag = 0;
  dlxSpriteSet = (_DWORD *)Mem_Alloc(4112, a2, spriteVariant, renderContext);
  if ( dlxSpriteSet )
    dlxSpriteSet = DLXSpriteSet_Load(dlxSpriteSet, spriteVariant);
  g_DemoTextDLXSpriteSet = (int)dlxSpriteSet;
  slotOffset = 0;
  memset_(0, 0);
  do
  {
    slotRecordPtr = slotOffset + g_BuildingUIRecordPtr;
    if ( *(__int16 *)(slotOffset + g_BuildingUIRecordPtr + 18) != -1 )
    {
      slotVariantDigit = *(_BYTE *)(slotRecordPtr + 20);
      UI_BeginUnitInfo(unitInfoBuffer, *(_BYTE *)(slotRecordPtr + 18), slotVariantDigit);
      slotSpriteSet = (_DWORD *)Mem_Alloc(4112, v10, slotVariantDigit, renderContext);
      if ( slotSpriteSet )
        slotSpriteSet = DLXSpriteSet_Load(slotSpriteSet, slotVariantDigit);
      *(int *)((char *)g_BuildingUnitsPopupSlotSpriteSets + spriteSetOffset) = (int)slotSpriteSet;
    }
    spriteSetOffset += 4;
    slotOffset += 31;
  }
  while ( spriteSetOffset != 40 );
  LOBYTE(selectedSlot) = 10;
  memset_(40, 0);
  RenderHook_DemoText(v13, 10, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  g_RenderDevice = v14;
  Render_Begin((int)g_RenderState, 0);
  while ( !g_TempleOutcomePopupCloseFlag )
  {
    DD_Pump((int)g_RenderState, (char)selectedSlot);
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
    if ( hoverRow <= 1 && (unsigned int)selectedSlot <= 4 )
    {
      selectedSlot += 5 * hoverRow;
      if ( *(__int16 *)(31 * (_DWORD)selectedSlot + g_BuildingUIRecordPtr + 18) != -1 )
      {
        if ( DD_IsFlipping((int)g_RenderState) )
        {
          g_BuildingUnitsPopupSelectedSlots[(_DWORD)selectedSlot] ^= 1u;
          Audio_PlaySoundEffectByName(aMarker, 64);
          RenderHook_DemoText(v22, (char)selectedSlot, renderContext);
          Render_Begin((int)g_RenderState, 0);
        }
        else if ( DD_IsLost((int)g_RenderState) )
        {
          hasSpecialPersonage = Building_HasSpecialPersonageGarrisonEntries(g_BuildingUIRecordPtr);
          selectedSlot = (unsigned __int8 *)(g_BuildingUIRecordPtr + 18 + v24);
          Unit_Info(100, 100, hasSpecialPersonage, selectedSlot, renderContext, 0);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(g_DemoTextHoverWidgetTable, renderContext);
  }
  DLXSpriteSet_ReleaseAndClear(&g_DemoTextDLXSpriteSet);
  freeIndex = 0;
  g_RenderDevice = savedRenderDevice;
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

  Debug_Log(tileX, tileY, (DWORD)outPath, (int)aBattlemapfilen);
  strcpy(outPath, aMaps);
  tile = gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY;
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
  strcat(outPath, suffix);
  outPath[strlen(outPath) + 1] = 0;
  outPath[strlen(outPath)] = Rng_RandRange(0, 1) + 48;
  strcat(outPath, a_mab);
  Debug_Log((int)outPath, 0, 0, (int)aBattlemapfil_0);
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
  return (unsigned __int8)g_MoveSoundSurfaceClassTable[*(__int16 *)(40 * tileRow + g_MapData + 2 * tileCol)];
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
  sprintf_(numberSuffix, "%d.wav", trackNumber);
  numReadCursor = numberSuffix;
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
  soundHandle = CSS_PlaySound((int)pathBuffer, volume, 0, 0);
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
  int v18; // [esp+C8h] [ebp-8h]
  int v19; // [esp+CCh] [ebp-4h]

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
    g_MainMapMusicHandle = CSS_PlaySound((int)wavPath, 64, 0, 2000);
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
  soundHandle = CSS_PlaySound((int)pathBuffer, 64, 0, 2000);
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
    return Music_PlayMainMapTrack(*(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET), a1, 1, gameContext);
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
  char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char digitSlot[5]; // [esp+1h] [ebp-69h]
  char soundPath[100]; // [esp+6h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPath, aSfxOddzialy, sizeof(soundPath));
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
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
    result = CSS_PlaySound((int)soundPath, 64, 0, 0);
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
  int metadataOffset; // ebx
  char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char digitSlot[5]; // [esp+1h] [ebp-6Dh]
  char soundPath[104]; // [esp+6h] [ebp-68h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    metadataOffset = 22 * result;
    CSS_SetSoundVolume(g_LastUnitActivateSoundHandle, 0, 500);
    qmemcpy(soundPath, aSfxOddzialy_0, 0x64u);
    resourceKey = (&g_UnitTypeResourceKeys)[metadataOffset];
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
    return CSS_PlaySound((int)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 543CA4: using guessed type int g_LastUnitActivateSoundHandle;

//----- (00441BE0) --------------------------------------------------------
int  Audio_PlayUnitRangedAttackSound(int result)
{
  char *resourceKey; // esi
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
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
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
    return CSS_PlaySound((int)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441C80) --------------------------------------------------------
int  Audio_PlayUnitHitSound(int result)
{
  char *resourceKey; // esi
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
    qmemcpy(soundPath, aSfxOddzialy_2, sizeof(soundPath));
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
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
    suffixCursor = aDostal_wav;
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
    return CSS_PlaySound((int)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441D20) --------------------------------------------------------
int  Audio_PlayUnitDeathSound(int result)
{
  char *resourceKey; // esi
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
    qmemcpy(soundPath, aSfxOddzialy_3, sizeof(soundPath));
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
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
    suffixCursor = aDead_wav;
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
    return CSS_PlaySound((int)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

