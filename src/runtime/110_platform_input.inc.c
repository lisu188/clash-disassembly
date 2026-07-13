/* Recovered input, window, message, and platform-facing behavior.
 * Original function-marker range: 0x00461520..0x004635A0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00461520) --------------------------------------------------------
int Input_Init()
{
  return 0;
}

//----- (00461530) --------------------------------------------------------
int Input_Shutdown()
{
  return 0;
}

//----- (00461540) --------------------------------------------------------
int  DD_GetSurfacePitch(int a1)
{
  return Compat_RenderStateTailFields(a1)->field_468_active;
}

//----- (00461570) --------------------------------------------------------
BOOL  Input_IsKeyPressed(int a1)
{
  return byte_5451CC[a1] < 0;
}

//----- (00461580) --------------------------------------------------------
BOOL Input_IsAnyKeyPressed()
{
  int v0; // edx
  BOOL result; // eax
  int v2; // edx

  v0 = 0;
  while ( 1 )
  {
    result = Input_IsKeyPressed(v0);
    if ( result )
      break;
    v0 = v2 + 1;
    if ( v0 >= 128 )
      return result;
  }
  return 1;
}
// 46158E: variable 'v2' is possibly undefined

//----- (004615A0) --------------------------------------------------------
signed int Input_PopKey()
{
  int v0; // edx
  int v1; // edx

  v0 = 0;
  while ( !Input_IsKeyPressed(v0) )
  {
    v0 = v1 + 1;
    if ( v0 >= 128 )
      return -1;
  }
  return v1;
}
// 4615AE: variable 'v1' is possibly undefined

//----- (004615D0) --------------------------------------------------------
char  Input_KeyToChar(unsigned int a1)
{
  if ( g_LanguageIndex == 2 )
  {
    g_KeyChar = 122;
    g_Input_ScanCodeChar_LangSwap = 121;
  }
  if ( (int)a1 >= 16 && a1 <= 0x1A )
    return g_Input_ScanCodeChars_TopRow[a1];
  if ( (int)a1 >= 30 && a1 <= 0x29 )
    return g_Input_ScanCodeChars_HomeRow[a1];
  if ( (int)a1 >= 44 && a1 <= 0x35 )
    return g_Input_ScanCodeChars_BottomRow[a1];
  if ( (int)a1 >= 2 && a1 <= 0xE )
    return g_Input_ScanCodeChars_NumberRow[a1];
  if ( a1 == 57 )
    return 32;
  return 0;
}
// 511130: using guessed type char g_LanguageIndex;
// 519985: using guessed type char g_KeyChar;
// 5199A0: using guessed type char byte_5199A0;

//----- (00461650) --------------------------------------------------------
BOOL  Input_ClearKey(int a1, int a2)
{
  int v3; // ecx
  int i; // ebx
  int v5; // ecx
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // edx
  BOOL result; // eax
  int v10; // ecx

  if ( a1 == dword_54517C )
    ++g_Input_KeyRepeatCount;
  else
    g_Input_KeyRepeatCount = 1;
  for ( i = Time_Now(a1, a2); Input_IsKeyPressed(v3); DD_Pump((int)g_RenderState, i) )
  {
    v6 = g_Input_KeyRepeatCount <= 1 ? 30 : 10;
    v7 = Time_Now(v5, i + v6);
    if ( v7 >= v8 )
      break;
  }
  result = Input_IsKeyPressed(v5);
  if ( !result )
    g_Input_KeyRepeatCount = 0;
  dword_54517C = v10;
  return result;
}
// 461670: variable 'v3' is possibly undefined
// 46168A: variable 'v5' is possibly undefined
// 461691: variable 'v8' is possibly undefined
// 4616BB: variable 'v10' is possibly undefined
// 5199C0: using guessed type int dword_5199C0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 54517C: using guessed type int dword_54517C;

//----- (004616E0) --------------------------------------------------------
int Input_MouseInit()
{
  int v0; // edx
  int v1; // ecx

  InputBackend_ResetState(&g_InputBackendState);
  return CRT_RegisterFinalizableObject(v1, v0);
}
// 4616EF: variable 'v1' is possibly undefined
// 4616EF: variable 'v0' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 545198: using guessed type _DWORD g_InputBackendState[80];

//----- (00461740) --------------------------------------------------------
BOOL Input_MousePresent()
{
  return (GetVersion() & 0x80000000) == 0 && (unsigned __int8)GetVersion() == 4;
}

//----- (00461770) --------------------------------------------------------
BOOL Input_MouseAcquire()
{
  return (GetVersion() & 0x80000000) != 0 && (unsigned __int8)GetVersion() == 4;
}

//----- (004617A0) --------------------------------------------------------
int  Render_DefaultRH(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aStdrhCall);
  return Render_EndModeSwitch((int)&unk_51D4C0, a2, a3);
}

//----- (004617C0) --------------------------------------------------------
LRESULT __thiscall Platform_MainWindowProc(void *this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  DWORD v5; // eax
  DWORD v6; // ebp
  int v7; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  v5 = 0;
  if ( dword_51D57C )
    v5 = Compat_DirectDrawSurfaceHandleIsLost(dword_51D57C);
  v6 = v5;
  Debug_Log((int)this, Msg, v5, (int)aDmessage0x08xL);
  if ( Msg < 0xF )
  {
    if ( Msg == 2 )
    {
      PostQuitMessage(0);
      return 0;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
  }
  if ( Msg <= 0xF )
  {
    Debug_Log(v7, Msg, v6, (int)aWm_paint);
    if ( *(_BYTE *)g_AppCommandLine == 119 )
      DefWindowProcA(hWnd, Msg, wParam, lParam);
    else
      ValidateRect(hWnd, 0);
    if ( g_AppIsActive != 1 || !dword_51D57C )
      return 0;
    Debug_Log(v12, Msg, v6, (int)aRestoreD);
    if ( dword_51D57C )
      Render_RestoreLostSurfaceIfNeeded(dword_51D584);
    if ( g_RenderHook && dword_51D594 == 8 )
    {
      Debug_Log((int)g_RenderHook, Msg, v6, (int)aRedrawhandler0);
      g_RenderHook(v13, Msg, v6);
    }
    DD_Pump((int)g_RenderState, Msg);
    return 0;
  }
  else
  {
    if ( Msg <= 0x10 )
      return 0;
    if ( Msg != 28 )
      return DefWindowProcA(hWnd, Msg, wParam, lParam);
    Debug_Log(v7, wParam, v6, (int)aWm_activateapp);
    if ( (unsigned __int16)wParam == 1 )
    {
      Debug_Log(v9, 1, v6, (int)aAcquire);
      InputBackend_Acquire(&g_InputBackendState);
      if ( dword_51D57C )
        Render_RestoreLostSurfaceIfNeeded(dword_51D584);
      if ( g_ShouldPresentOnReactivate )
        Render_Present((int)g_RenderState);
      if ( g_SoundPausedForInactiveApp )
        CSS_ResumeSound(g_Audio_ActiveSoundHandle, 1000);
      g_SoundPausedForInactiveApp = 0;
      Debug_Log(v11, 1, v6, (int)aResumedSoundD);
    }
    if ( !(_WORD)wParam )
    {
      g_ShouldPresentOnReactivate = dword_544D10;
      if ( !v6 )
        Render_Pump();
      Debug_Log(v9, 0, v6, (int)aUnacquire);
      InputBackend_Unacquire(&g_InputBackendState);
      if ( !g_SoundPausedForInactiveApp )
        CSS_PauseSound(g_Audio_ActiveSoundHandle, 1000);
      g_SoundPausedForInactiveApp = 1;
      Debug_Log(v10, 0, g_Audio_ActiveSoundHandle, (int)aPausedSoundD);
    }
    g_AppIsActive = (unsigned __int16)wParam;
    return 0;
  }
}
// 4617E9: variable 'this' is possibly undefined
// 46182E: variable 'v7' is possibly undefined
// 46185C: variable 'v9' is possibly undefined
// 461892: variable 'v10' is possibly undefined
// 461913: variable 'v11' is possibly undefined
// 461982: variable 'v12' is possibly undefined
// 4619BF: variable 'v13' is possibly undefined
// 5174D0: using guessed type int dword_5174D0;
// 5199D4: using guessed type int g_AppIsActive;
// 5199D8: using guessed type int ( *g_RenderHook)(int a1, char a2, DWORD a3);
// 51D020: using guessed type int g_AppCommandLine;
// 51D57C: using guessed type int dword_51D57C;
// 51D584: using guessed type int dword_51D584;
// 51D594: using guessed type int dword_51D594;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;
// 545190: using guessed type int g_SoundPausedForInactiveApp;
// 545198: using guessed type _DWORD g_InputBackendState[80];
// 5452D8: using guessed type int g_ShouldPresentOnReactivate;

//----- (00461A20) --------------------------------------------------------
HWND  Platform_CreateMainWindow(HINSTANCE a1, int a2)
{
  DWORD v3; // ebx
  HWND result; // eax
  WNDCLASSA v5; // [esp+0h] [ebp-34h] BYREF
  int v6; // [esp+2Ch] [ebp-8h]

  v6 = a2;
  v5.hInstance = a1;
  v5.style = 3;
  v5.lpfnWndProc = (WNDPROC)Platform_MainWindowProc;
  v5.cbClsExtra = 0;
  v5.cbWndExtra = 0;
  v5.hIcon = LoadIconA(a1, (LPCSTR)0x64);
  v5.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  v5.hbrBackground = (HBRUSH)GetStockObject(4);
  v5.lpszClassName = aClash_1;
  v5.lpszMenuName = 0;
  RegisterClassA(&v5);
  v3 = 0x80000000;
  if ( *(_BYTE *)g_AppCommandLine && *(_BYTE *)(g_AppCommandLine + 1) == 119 )
    v3 = -2133917696;
  result = CreateWindowExA(0, ClassName, WindowName, v3, 0, 0, 640, 480, 0, 0, a1, 0);
  hWnd = result;
  if ( result )
  {
    InputBackend_ResetState(&g_InputBackendState);
    ShowWindow(result, 3);
    UpdateWindow(hWnd);
    InputBackend_Initialize(&g_InputBackendState, (int)a1, (int)hWnd);
    return (HWND)1;
  }
  return result;
}
// 51D020: using guessed type int g_AppCommandLine;
// 545198: using guessed type _DWORD g_InputBackendState[80];

//----- (00461B30) --------------------------------------------------------
WPARAM  Platform_PumpMessagesAndBlitFrame(char a1)
{
  HWND hwnd; // ecx
  struct tagMSG Msg; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD savedregs[6]; // [esp+1Ch] [ebp+0h] BYREF

  Render_BlitSurface(&unk_51D4C0, 0, a1, (DWORD)savedregs);
  while ( 1 )
  {
    if ( !PeekMessageA(&Msg, 0, 0, 0, 0) && g_AppIsActive )
      return 1;
    hwnd = Msg.hwnd;
    if ( dword_51D57C )
      Compat_DirectDrawSurfaceHandleIsLost(dword_51D57C);
    Debug_Log((int)hwnd, 0, (DWORD)savedregs, (int)aAmessage0x08xL);
    if ( !GetMessageA(&Msg, 0, 0, 0) )
      break;
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
    if ( !g_AppIsActive )
      WaitMessage();
  }
  Render_BeginModeSwitch(&unk_51D4C0);
  return Msg.wParam;
}
// 461B87: variable 'hwnd' is possibly undefined
// 5199D4: using guessed type int g_AppIsActive;
// 51D57C: using guessed type int dword_51D57C;

//----- (00461C00) --------------------------------------------------------
int  Mem_Alloc(int a1, int a2, char a3, DWORD a4)
{
  int v6; // [esp+0h] [ebp-18h] BYREF
  _DWORD v7[5]; // [esp+4h] [ebp-14h] BYREF

  v7[4] = a2;
  v7[0] = nmalloc_(a1, 0);
  qmemcpy(&v6, v7, sizeof(v6));
  if ( !v6 )
  {
    Debug_Log(0, a3, a4, (int)aNotEnoughMe_13);
    App_RequestQuit((int)aNotEnoughMe_14);
  }
  return v6;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);

//----- (00461C80) --------------------------------------------------------
BOOL  Video_CanContinuePlayback(char a1)
{
  DD_Pump((int)g_RenderState, a1);
  DD_Pump((int)g_RenderState, a1);
  DD_Pump((int)g_RenderState, a1);
  return !Input_IsAnyKeyPressed() && !DD_IsFlipping((int)g_RenderState) && !DD_IsLost((int)g_RenderState);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00461CE0) --------------------------------------------------------
signed int  Win_BeginModeChange(const char *a1, char *a2)
{
  char *base_path;
  int query_handle;
  int direct_file_available;

  query_handle = 0;
  direct_file_available = 0;
  base_path = FileSystem_GetInstallRootPath();
  sprintf_(a2, "%savi\\%s.avi", base_path, a1);
  query_handle = FileSystem_ResolveReadPath(a2, 0);
  if ( !query_handle )
    direct_file_available = Compat_CanOpenReadPath(a2);
  if ( !query_handle )
  {
    if ( !direct_file_available )
    {
      sprintf_(a2, "avi\\%s.avi", a1);
      query_handle = FileSystem_ResolveReadPath(a2, 0);
      if ( !query_handle )
        direct_file_available = Compat_CanOpenReadPath(a2);
    }
  }
  if ( !query_handle && !direct_file_available )
    App_RequestQuit((int)g_UI_CdMissingMessageByLanguage[(unsigned __int8)g_LanguageIndex]);
  Compat_FileSystemQueryRelease((int)&dword_543CC8, &query_handle);
  return 1;
}
// 511130: using guessed type char g_LanguageIndex;
// 5199F0: using guessed type char *off_5199F0[3];

//----- (00461D90) --------------------------------------------------------
void  Win_EndModeChange(int a1, char *a2, int a3, int a4)
{
  tagRECT v4; // [esp+0h] [ebp-10h] BYREF

  if ( g_SdlTransitionAnimSkipRequested )
  {
    v4 = *(tagRECT *)g_Device_DefaultWindowRect;
    if ( a3 )
    {
      PlayAviStretch(
        a2,
        *(IDirectDrawSurface **)(*(_DWORD *)(dword_51D584 + 4) + 164),
        &v4,
        (int (*)(void))Video_CanContinuePlayback,
        1500);
    }
    else
    {
      if ( dword_51D58C )
        dword_51D588 = 1;
      PlayAvi(
        a2,
        *(IDirectDrawSurface **)(dword_51D57C + 164),
        a4,
        a1,
        (int (*)(void))Video_CanContinuePlayback,
        1000);
    }
  }
}
// 511134: using guessed type int dword_511134;
// 51D57C: using guessed type int dword_51D57C;
// 51D584: using guessed type int dword_51D584;
// 51D588: using guessed type int dword_51D588;
// 51D58C: using guessed type int dword_51D58C;

//----- (00461E20) --------------------------------------------------------
void  Video_Avi_playIn(const char *a1, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // edi
  int v9; // ecx
  DWORD TickCount; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int (*v14)(); // ebp
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  char v18[100]; // [esp+0h] [ebp-80h] BYREF
  int (*v19)(); // [esp+64h] [ebp-1Ch]
  int v20; // [esp+68h] [ebp-18h]
  int v21; // [esp+6Ch] [ebp-14h]
  int v22; // [esp+70h] [ebp-10h]

  if ( g_BootstrapSkipIntroAviPlayback )
    return;
  v20 = a2;
  v7 = a4;
  Debug_Log(a3, a4, (DWORD)a1, (int)aAvi_playIn);
  v22 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v19 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v9, a4, (DWORD)a1, (int)aSetrhS08x_19);
  v21 = Render_SetResourceHandle((int)&unk_51D4C0, 0);
  if ( a3 && dword_51D594 == 8 )
  {
    Palette_FadeOutToBlack((int *)&unk_51D4C0, 40);
    Render_UnlockBackbuffer((int)&unk_51D4C0);
  }
  else if ( dword_51D594 == 8 )
  {
    Render_BlitSurface(&unk_51D4C0, 1, a4, (DWORD)a1);
  }
  TickCount = GetTickCount();
  v11 = a5;
  dword_5452E4 = TickCount;
  if ( a5 && dword_51D594 == 8 )
  {
    Debug_Log(a5, a4, (DWORD)a1, (int)aInit16bpp);
    LOBYTE(a4) = 16;
    Render_BeginModeSwitch(&unk_51D4C0);
    Render_SetPixelFormat((int)&unk_51D4C0, (int)(intptr_t)hWnd, 16, (DWORD)a1);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    InputBackend_Acquire(&g_InputBackendState);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
  }
  if ( Win_BeginModeChange(a1, v18) )
  {
    LOBYTE(a4) = v20;
    Win_EndModeChange(v7, v18, a3, v20);
    Render_Begin((int)g_RenderState, 0);
  }
  if ( a6 && dword_51D594 != 8 )
  {
    Debug_Log(v13, a4, (DWORD)a1, (int)aClose16bpp);
    LOBYTE(a4) = 8;
    Render_BeginModeSwitch(&unk_51D4C0);
    Render_SetPixelFormat((int)&unk_51D4C0, (int)(intptr_t)hWnd, 8, (DWORD)a1);
    DD_Pump((int)g_RenderState, 8);
    DD_Pump((int)g_RenderState, 8);
    DD_Pump((int)g_RenderState, 8);
    InputBackend_Acquire(&g_InputBackendState);
    DD_Pump((int)g_RenderState, 8);
    DD_Pump((int)g_RenderState, 8);
    DD_Pump((int)g_RenderState, 8);
  }
  else
  {
    if ( dword_51D594 == 8 )
      Render_ReleaseTempSurface((int *)&unk_51D4C0);
    if ( dword_51D594 == 8 && !a5 )
      Render_EndModeSwitch((int)&unk_51D4C0, a4, (DWORD)a1);
  }
  dword_5452E4 = 0;
  Render_SetResourceHandle((int)&unk_51D4C0, v21);
  v14 = g_RenderHook;
  Debug_Log(v15, a4, (DWORD)g_RenderHook, (int)aUnsetrh08x_19);
  g_RenderHook = v19;
  Render_SetResourceHandle((int)&unk_51D4C0, v22);
  Debug_Log(v16, a4, (DWORD)v14, (int)aAvi_playOut);
}
// 461E7C: variable 'v9' is possibly undefined
// 461F13: variable 'v12' is possibly undefined
// 461F6E: variable 'v11' is possibly undefined
// 461FF8: variable 'v15' is possibly undefined
// 46201C: variable 'v16' is possibly undefined
// 462060: variable 'v13' is possibly undefined
// 462082: variable 'v17' is possibly undefined
// 5199D8: using guessed type int (*g_RenderHook)();
// 51D594: using guessed type int dword_51D594;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 5452E4: using guessed type int dword_5452E4;

//----- (004620F0) --------------------------------------------------------
signed int  Win_PlayModeChangeFrameTransition(const char *a1, int a2, int a3, char a4, DWORD a5, ...)
{
  signed int result; // eax
  int v7; // edi
  int v8; // ecx
  void *v9; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  _DWORD *v14; // eax
  int v15; // ecx
  _DWORD *Surface; // eax
  _DWORD *v17; // esi
  DWORD v18; // ebp
  int v19; // ecx
  void (**v20)(void); // ebx
  int v21; // ecx
  int v22; // edx
  char v23[100]; // [esp+1Ch] [ebp-88h] BYREF
  _DWORD *v24; // [esp+80h] [ebp-24h] BYREF
  int SpriteWidth; // [esp+84h] [ebp-20h]
  int v26; // [esp+88h] [ebp-1Ch]
  int v27; // [esp+8Ch] [ebp-18h]
  int (*v28)(); // [esp+90h] [ebp-14h]
  int v29; // [esp+94h] [ebp-10h]
  int SpriteHeight; // [esp+98h] [ebp-Ch]

  v29 = a2;
  if ( g_SdlTransitionAnimSkipRequested && !getenv("CLASH95_ENABLE_SDL_TRANSITION_ANIMS") )
  {
    /*
     * The recovered transition animation path still uses the old temporary
     * DirectDraw-surface cleanup contract. Under the SDL surface shim it can
     * corrupt the runtime after repeated turn/battle transitions. Keep the
     * authentic caller flow intact and present the current frame while the
     * temp-surface ABI is still quarantined.
     */
    Diagnostics_TraceWorldMapActionEvent(
      "transition_sdl_anim_bypass",
      g_SelectedUnitIndex,
      (int)(intptr_t)a1,
      v29,
      a3);
    return 1;
  }
  result = Win_BeginModeChange(a1, v23);
  Diagnostics_TraceWorldMapActionEvent("transition_after_begin_mode", g_SelectedUnitIndex, result, v29, 0);
  if ( result )
  {
    result = gameData;
    if ( *(_DWORD *)(gameData + 147147) )
    {
      if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      {
        v7 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
        Diagnostics_TraceWorldMapActionEvent("transition_after_set_rh_std", g_SelectedUnitIndex, v7, 0, 0);
        v28 = g_RenderHook;
        g_RenderHook = (int (*)())Render_DefaultRH;
        Debug_Log(v8, a4, a5, (int)aSetrhS08x_20);
        v27 = Render_SetResourceHandle((int)&unk_51D4C0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_set_rh_prev", g_SelectedUnitIndex, v27, 0, 0);
        Render_Pump();
        Diagnostics_TraceWorldMapActionEvent("transition_after_render_pump", g_SelectedUnitIndex, 0, 0, 0);
        LOBYTE(v9) = 0;
        Render_FillRect(0, (_DWORD *)dword_5202E0, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_backbuffer_fill", g_SelectedUnitIndex, 0, 0, 0);
        Video_EnterGreyscaleTransition((int *)&unk_51D4C0, v10, 0, a5);
        Diagnostics_TraceWorldMapActionEvent("transition_after_gray_palette", g_SelectedUnitIndex, 0, 0, 0);
        v12 = Mem_Alloc(1024, 0, 0, a5);
        if ( v12 )
        {
          v9 = &g_Runtime_PaletteArrayCtorDescriptor;
          v12 = _wcpp_4_ctor_array__(v12, 256);
        }
        v26 = v12;
        Diagnostics_TraceWorldMapActionEvent("transition_after_palette_alloc", g_SelectedUnitIndex, v26, 0, 0);
        g_RenderDevice = &unk_51D4C0;
        v14 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)&unk_51D4C0);
        if ( v14 )
          v14 = DLXSpriteSet_Load(v14, "anim_fr.s32");
        v24 = v14;
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_load", g_SelectedUnitIndex, (int)(uintptr_t)v24, 0, 0);
        if ( !v24 )
        {
          Win_EndModeChange(0, v23, 0, 0);
          g_RenderDevice = (_UNKNOWN *)dword_5202E0;
          if ( v26 )
            j__nfree_(v26);
          Render_SetResourceHandle((int)&unk_51D4C0, v27);
          g_RenderHook = v28;
          Render_SetResourceHandle((int)&unk_51D4C0, v7);
          Diagnostics_TraceWorldMapActionEvent("transition_anim_missing_unwound", g_SelectedUnitIndex, 0, 0, 0);
          return 0;
        }
        SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v14, 0);
        SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v24, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_dims", g_SelectedUnitIndex, SpriteHeight, SpriteWidth, 0);
        Surface = (_DWORD *)Mem_Alloc(188, 0, 0, (DWORD)&unk_51D4C0);
        if ( Surface )
          Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
        v17 = Surface;
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_create", g_SelectedUnitIndex, (int)(uintptr_t)v17, 0, 0);
        Render_FillRect(0, Surface, 80, 80, SpriteHeight + 79, SpriteWidth + 79, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_fill", g_SelectedUnitIndex, 0, 0, 0);
        v12 = DLX_GetSpriteForChar((int)v24, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_sprite_lookup", g_SelectedUnitIndex, v12, 0, 0);
        Compat_RenderDeviceDrawMenuSprite(80, 80, v12, 0);
        v18 = *((_DWORD *)g_RenderDevice + 46);
        Diagnostics_TraceWorldMapActionEvent("transition_after_sprite_draw", g_SelectedUnitIndex, 0, 0, 0);
        DLXSpriteSet_ReleaseAndClear((int *)&v24);
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_free", g_SelectedUnitIndex, 0, 0, 0);
        Audio_DuckMusicVolume();
        Diagnostics_TraceWorldMapActionEvent("transition_after_fade_wait", g_SelectedUnitIndex, 0, 0, 0);
        Win_EndModeChange(100, v23, 0, 100);
        Diagnostics_TraceWorldMapActionEvent("transition_after_end_mode", g_SelectedUnitIndex, 0, 0, 0);
        if ( g_SdlTransitionAnimSkipRequested )
          Diagnostics_TraceWorldMapActionEvent("transition_skip_temp_release_sdl", g_SelectedUnitIndex, g_SdlTransitionAnimSkipRequested, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_temp_release", g_SelectedUnitIndex, g_SdlTransitionAnimSkipRequested, 0, 0);
        LOBYTE(v20) = 0;
        Render_FillRect(v17, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, 0x50u, 0x50u);
        Diagnostics_TraceWorldMapActionEvent("transition_after_restore_surface_fill", g_SelectedUnitIndex, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)dword_5202E0;
        if ( v29 )
        {
          Video_ExitGreyscaleTransition((int *)&unk_51D4C0, (unsigned __int8 *)dword_5202F4, v21, 0, v18);
          Audio_RestoreMusicVolume();
          Diagnostics_TraceWorldMapActionEvent("transition_after_palette_restore", g_SelectedUnitIndex, 0, 0, 0);
        }
        if ( v17 )
        {
          v20 = (void (**)(void))v17[46];
          RenderSurface_InvokeSlot0(v17, 2);
        }
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_release", g_SelectedUnitIndex, 0, 0, 0);
        j__nfree_(v26);
        Diagnostics_TraceWorldMapActionEvent("transition_after_palette_free", g_SelectedUnitIndex, 0, 0, 0);
        v22 = v27;
        Render_Present((int)g_RenderState);
        Diagnostics_TraceWorldMapActionEvent("transition_after_present", g_SelectedUnitIndex, 0, 0, 0);
        Render_SetResourceHandle((int)&unk_51D4C0, v22);
        Debug_Log((int)g_RenderHook, (char)v20, v18, (int)aUnsetrh08x_20);
        g_RenderHook = v28;
        return Render_SetResourceHandle((int)&unk_51D4C0, v7);
      }
    }
  }
  return result;
}
// 4620F0: could not find valid save-restore pair for ebx
// 462178: variable 'v8' is possibly undefined
// 4621BE: variable 'v10' is possibly undefined
// 4621C8: variable 'v11' is possibly undefined
// 4621DB: variable 'v13' is possibly undefined
// 462237: variable 'v15' is possibly undefined
// 4622D6: variable 'v19' is possibly undefined
// 462338: variable 'v21' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511134: using guessed type int dword_511134;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004623C0) --------------------------------------------------------
void __fastcall Video_PlayAviWithModeGuard(int a1, const char *a2)
{
  if ( !strcmp_(a1, aKon_por1_1) )
  {
    if ( dword_5452E8 )
      return;
    dword_5452E8 = 1;
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
  Palette_ApplyDefaultPalette((int *)&unk_51D4C0);
  Video_Avi_playIn(a2, 0, 1, 0, 1, 1);
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 5452E8: using guessed type int dword_5452E8;

//----- (00462480) --------------------------------------------------------
int  Mission_PlayInfoSlideshow(int a1, char *a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // eax
  unsigned __int8 v5; // al
  _DWORD *Surface; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  int v10; // esi
  int v11; // ecx
  int v12; // eax
  unsigned __int8 v13; // al
  int v14; // eax
  unsigned __int8 v15; // al
  _DWORD *v16; // edi
  int v17; // eax
  unsigned __int8 v18; // al
  int v19; // edx
  int v20; // ecx
  int v21; // edi
  int v22; // ecx
  int v23; // edx
  int v24; // edx
  int v25; // ecx
  int v26; // ecx
  int v27; // edx
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // edx
  int v33; // ecx
  int v34; // ecx
  int intro_start_time;
  int v35; // [esp-4h] [ebp-44Ch]
  int v36; // [esp-4h] [ebp-44Ch]
  int v37; // [esp-4h] [ebp-44Ch]
  int v38; // [esp-4h] [ebp-44Ch]
  unsigned __int8 v39[1024]; // [esp+0h] [ebp-448h] BYREF
  char v40[52]; // [esp+400h] [ebp-48h] BYREF
  int (*v41)(); // [esp+434h] [ebp-14h]
  int v42; // [esp+438h] [ebp-10h]
  _DWORD *v43; // [esp+43Ch] [ebp-Ch]
  int v44; // [esp+440h] [ebp-8h]
  int v45; // [esp+444h] [ebp-4h]
  _DWORD savedregs[6]; // [esp+448h] [ebp+0h] BYREF

  v44 = a1;
  v42 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v41 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v2, (char)a2, (DWORD)savedregs, (int)aSetrhS08x_21);
  Render_Pump();
  v3 = -1;
  v45 = -1;
  if ( g_LanguageIndex == 1 )
  {
    a2 = aSfxMisinfoC_02;
    if ( v44 > 9 )
      v4 = v44 - 9;
    else
      v4 = v44 + (unsigned __int8)g_LanguageIndex;
    v35 = v4;
    if ( v44 > 9 )
      v5 = 80;
    else
      v5 = 67;
    sprintf_(v40, "sfx\\misinfo\\%c_%02d.WAV", v5, v35);
    loadFileSusp(v40, aDataLector_w_0);
  }
  Surface = (_DWORD *)Mem_Alloc(188, v3, (char)a2, (DWORD)savedregs);
  if ( Surface )
  {
    LOBYTE(a2) = -32;
    Surface = Render_CreateSurface((int)Surface, 640, 480);
  }
  v43 = Surface;
  v8 = Mem_Alloc(188, v7, (char)a2, (DWORD)savedregs);
  if ( v8 )
    v8 = (int)Render_CreateSurface(v8, 640, 480);
  RenderSurface_InvokeSlot56((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
  RenderSurface_InvokeSlot56(v43);
  v10 = v8;
  RenderSurface_InvokeSlot56((_DWORD *)(uintptr_t)(unsigned int)v10);
  _wcpp_4_ctor_array__((int)v39, 256);
  if ( v44 > 9 )
    v12 = v44 - 9;
  else
    v12 = v44 + 1;
  v36 = v12;
  if ( v44 > 9 )
    v13 = 80;
  else
    v13 = 67;
  sprintf_(v40, "misinfo\\%c_%02d_A.PCX", v13, v36);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)dword_5202E0,
    v40,
    0,
    (uintptr_t)v39);
  if ( v44 > 9 )
    v14 = v44 - 9;
  else
    v14 = v44 + 1;
  v37 = v14;
  if ( v44 > 9 )
    v15 = 80;
  else
    v15 = 67;
  v16 = v43;
  sprintf_(v40, "misinfo\\%c_%02d_B.PCX", v15, v37);
  RenderSurface_InvokeSlot48LoadPCX(v16, v40, 0, (uintptr_t)v39);
  if ( v44 > 9 )
    v17 = v44 - 9;
  else
    v17 = v44 + 1;
  v38 = v17;
  if ( v44 > 9 )
    v18 = 80;
  else
    v18 = 67;
  sprintf_(v40, "misinfo\\%c_%02d_C.PCX", v18, v38);
  RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)v10, v40, 0, (uintptr_t)v39);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
  intro_start_time = Time_Now(v20, v19);
  v21 = Sound_PlayNamedSfxFile(aMusicCampain, 21);
  Palette_FadeInFromBlack((int *)&unk_51D4C0, v39, 50);
  if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 420, 0) )
  {
    RenderSurface_InvokeSlot36(v43);
    if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 550, 0) )
    {
      RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
      if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 660, 0) )
      {
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)v10);
        if ( g_LanguageIndex == 1 )
          v45 = CSS_PlaySound((int)aDataLector_w_2, 64, 0, 0);
        while ( (g_LanguageIndex != 1 || CSS_IsPlaying(v45)) && !UI_WaitForKeyOrTimeout(10, v33) )
          RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)v10);
        if ( g_LanguageIndex == 1 )
          CSS_StopSound(v45, 0);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
        UI_WaitForKeyOrTimeout(30, v34);
      }
    }
  }
  IO_RemoveFileByPath((int)aDataLector_w_0, 0);
  Sleep(0x12Cu);
  Palette_FadeOutToBlack((int *)&unk_51D4C0, 60);
  Audio_StopMusicWithFade(v21);
  if ( v43 )
    RenderSurface_InvokeSlot0(v43, 2);
  if ( v10 )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)v10, 2);
  Debug_Log(v42, (char)g_RenderHook, (DWORD)savedregs, (int)aUnsetrh08x_21);
  g_RenderHook = v41;
  return Render_SetResourceHandle((int)&unk_51D4C0, v42);
}
// 4624CE: variable 'v2' is possibly undefined
// 462538: variable 'v3' is possibly undefined
// 462558: variable 'v7' is possibly undefined
// 46259C: variable 'v9' is possibly undefined
// 4625BF: variable 'v11' is possibly undefined
// 462698: variable 'v20' is possibly undefined
// 462698: variable 'v19' is possibly undefined
// 4626C5: variable 'v22' is possibly undefined
// 4626CB: variable 'v23' is possibly undefined
// 4626DD: variable 'v25' is possibly undefined
// 4626DD: variable 'v24' is possibly undefined
// 462709: variable 'v26' is possibly undefined
// 462747: variable 'v27' is possibly undefined
// 4627AC: variable 'v29' is possibly undefined
// 4627B2: variable 'v30' is possibly undefined
// 4627CD: variable 'v31' is possibly undefined
// 4627D3: variable 'v32' is possibly undefined
// 46280A: variable 'v33' is possibly undefined
// 46286C: variable 'v34' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;

//----- (00462890) --------------------------------------------------------
int __cdecl Palette_QueryNearestColorIndex(int a1, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4)
{
  g_Palette_ActivePalettePtr = a1;
  return Palette_FindNearestColorIndex(a2, a3, a4);
}
// 519A10: using guessed type int dword_519A10;

//----- (004628B0) --------------------------------------------------------
int __cdecl Palette_BuildNearestColorLUT(int a1)
{
  int v2; // [esp+4h] [ebp-10h]
  int v3; // [esp+8h] [ebp-Ch]
  int v4; // [esp+Ch] [ebp-8h]
  unsigned int v5; // [esp+10h] [ebp-4h]

  g_Palette_ActivePalettePtr = a1;
  v5 = 0;
  v4 = 0;
  v3 = 0;
  while ( 1 )
  {
    do
    {
      byte_5452EC[1024 * v5 + 32 * v4 + v3] = Palette_FindNearestColorIndex(8 * v5, 8 * v4, 8 * v3);
      ++v5;
    }
    while ( v5 < 0x20 );
    v5 = 0;
    if ( (unsigned int)++v4 >= 0x20 )
    {
      v4 = 0;
      if ( (unsigned int)++v3 >= 0x20 )
        break;
    }
  }
  return v2;
}
// 462938: variable 'v2' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (0046293B) --------------------------------------------------------
int  Palette_FindNearestColorIndex(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
  char *v3; // esi
  int v4; // ecx
  int v5; // edx
  char v6; // bh
  unsigned __int8 v7; // bl
  __int16 v8; // ax
  unsigned __int8 v9; // bh
  unsigned __int8 v10; // bl
  __int16 v11; // ax
  unsigned __int8 v12; // bh
  unsigned __int8 v13; // bl
  __int16 v14; // ax
  unsigned int v15; // eax
  unsigned __int8 v17; // [esp+4h] [ebp-1Ch]
  unsigned int v21; // [esp+14h] [ebp-Ch]
  int v22; // [esp+18h] [ebp-8h]

  v21 = -1;
  v3 = (char *)g_Palette_ActivePalettePtr;
  v4 = 256;
  v5 = 0;
  do
  {
    v6 = *v3;
    if ( a1 > (unsigned __int8)*v3 )
      v7 = a1 - v6;
    else
      v7 = v6 - a1;
    v8 = v7;
    v17 = v7;
    v9 = v3[1];
    if ( a2 > v9 )
      v10 = a2 - v9;
    else
      v10 = v9 - a2;
    v11 = v10 + v8;
    if ( v10 > v17 )
      v17 = v10;
    v12 = v3[2];
    if ( a3 > v12 )
      v13 = a3 - v12;
    else
      v13 = v12 - a3;
    v14 = v13 + v11;
    if ( v13 > v17 )
      v17 = v13;
    v15 = (unsigned __int16)(v17 + v14);
    if ( v15 <= v21 )
    {
      v21 = v15;
      v22 = v5;
    }
    ++v5;
    v3 += 4;
    --v4;
  }
  while ( v4 );
  return v22;
}
// 4629D7: variable 'v22' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (004629E1) --------------------------------------------------------
int __cdecl Palette_BlendIndexedPixelRun(char *a1, char *a2, unsigned __int8 *a3, int a4)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  char v14; // al
  int v15; // [esp-14h] [ebp-2Ch]
  int v16; // [esp+4h] [ebp-14h]
  int v17; // [esp+8h] [ebp-10h]
  int v18; // [esp+8h] [ebp-10h]
  unsigned int v19; // [esp+8h] [ebp-10h]
  char v20; // [esp+10h] [ebp-8h]
  char v21; // [esp+14h] [ebp-4h]

  if ( !a4 )
    return v16;
  v6 = a4;
  do
  {
    v15 = v6;
    v7 = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*a2);
    v8 = *a3;
    v9 = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * v8) - v7)) >> 8;
    if ( v9 < 0 )
      v17 = -v9;
    else
      v17 = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * v8) - v7)) >> 8;
    v21 = v7 + v9;
    v10 = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*a2 + 1);
    v11 = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *a3 + 1) - v10)) >> 8;
    if ( v11 < 0 )
      v18 = v17 - v11;
    else
      v18 = v11 + v17;
    v20 = v10 + v11;
    v12 = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*a2 + 2);
    v13 = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *a3 + 2) - v12)) >> 8;
    if ( v13 < 0 )
      v19 = v18 - v13;
    else
      v19 = v13 + v18;
    if ( v19 > 0x14 )
      v14 = byte_5452EC[128 * (v21 & 0xF8) + 4 * (v20 & 0xF8) + ((unsigned int)(v12 + v13) >> 3)];
    else
      v14 = *a2;
    *a1 = v14;
    ++a2;
    ++a3;
    ++a1;
    v6 = v15 - 1;
  }
  while ( v15 != 1 );
  return v16;
}
// 4629F6: variable 'v16' is possibly undefined
// 519A10: using guessed type int dword_519A10;
// 519A14: using guessed type int dword_519A14;

//----- (00462B0B) --------------------------------------------------------
int __cdecl Palette_OffsetIndexedPixelsRGB(unsigned __int8 *a1, int a2, int a3, int a4, int a5)
{
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // [esp-14h] [ebp-2Ch]
  int v12; // [esp+4h] [ebp-14h]
  char v13; // [esp+10h] [ebp-8h]
  char v14; // [esp+14h] [ebp-4h]

  if ( !a2 )
    return v12;
  v7 = a2;
  do
  {
    v11 = v7;
    v8 = a3 + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *a1);
    if ( v8 < 0 )
      v8 = 0;
    if ( (unsigned int)v8 > 0xFF )
      LOBYTE(v8) = -1;
    v14 = v8;
    v9 = a4 + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *a1 + 1);
    if ( v9 < 0 )
      v9 = 0;
    if ( (unsigned int)v9 > 0xFF )
      LOBYTE(v9) = -1;
    v13 = v9;
    v10 = a5 + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *a1 + 2);
    if ( v10 < 0 )
      v10 = 0;
    if ( (unsigned int)v10 > 0xFF )
      v10 = 255;
    *a1++ = byte_5452EC[128 * (v14 & 0xF8) + 4 * (v13 & 0xF8) + ((unsigned int)v10 >> 3)];
    --v7;
  }
  while ( v11 != 1 );
  return v12;
}
// 462B20: variable 'v12' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (00462BE0) --------------------------------------------------------
_DWORD * IO_StreamAdapterConstruct(_DWORD *result, int a2)
{
  *result = g_IOStreamAdapter_Vtable;
  result[1] = a2;
  return result;
}
// 50F364: using guessed type int (*off_50F364[4])();

//----- (00462BF0) --------------------------------------------------------
_DWORD * IO_StreamAdapterRelease(_DWORD *a1, char a2)
{
  _DWORD *v3; // ecx
  int v5; // ecx

  v3 = a1;
  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_IOStreamAdapter_DtorArrayTag);
    j_j__nfree_();
    return (_DWORD *)v5;
  }
  else
  {
    *a1 = g_IOStreamAdapter_Vtable;
    if ( (a2 & 2) != 0 )
      j__nfree_();
    return v3;
  }
}
// 462C51: variable 'v3' is possibly undefined
// 462C7A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50F364: using guessed type int (*off_50F364[4])();

//----- (00462C90) --------------------------------------------------------
int  IO_StreamAdapterReadBytes(int a1, int a2, signed int a3)
{
  int v3; // eax
  int v4; // ebp
  signed int v5; // edx
  unsigned int v7; // eax
  int v9; // [esp+4h] [ebp-18h]
  int v10; // [esp+8h] [ebp-14h]

  v3 = *(_DWORD *)(a1 + 4);
  v4 = v3;
  v10 = 0;
  if ( a3 )
  {
    v9 = v3 + 219;
    do
    {
      if ( !*(_DWORD *)(v4 + 383) )
      {
        v7 = AviPlayer_PopBufferedVideoFrame(v4, *(void **)(v4 + 379));
        *(_DWORD *)(v4 + 383) = v7;
        if ( !v7 )
          break;
      }
      v5 = *(_DWORD *)(v4 + 383);
      if ( a3 < v5 )
        v5 = a3;
      qmemcpy(
        (void *)(v10 + a2),
        (const void *)(*(_DWORD *)(v9 + 40) - *(_DWORD *)(v4 + 383) + *(_DWORD *)(v4 + 379)),
        v5);
      v10 += v5;
      *(_DWORD *)(v4 + 383) -= v5;
      a3 -= v5;
    }
    while ( a3 );
  }
  return v10;
}

//----- (00462CA0) --------------------------------------------------------
BOOL  IO_StreamAdapterIsAtEnd(int a1)
{
  return *(_BYTE *)(*(_DWORD *)(a1 + 4) + 1) != 0;
}

//----- (00462CB0) --------------------------------------------------------
int  IO_StreamAdapterInvokeAtEnd(int a1)
{
  return (*(int (**)(void))(*(_DWORD *)a1 + 4))();
}

//----- (00462CC0) --------------------------------------------------------
int IO_StreamAdapterReadStub()
{
  return 0;
}

//----- (00462CE0) --------------------------------------------------------
_DWORD * IO_StreamAdapterAlloc(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax
  int v5; // edx

  result = (_DWORD *)Mem_Alloc(8, a1, a2, a3);
  if ( result )
    return IO_StreamAdapterConstruct(result, v5);
  return result;
}
// 462CF3: variable 'v5' is possibly undefined

//----- (00462D00) --------------------------------------------------------
int  ExcString_ConstructEmpty(_DWORD *a1)
{
  int v2; // ecx

  *a1 = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(a1);
  return v2;
}
// 462D17: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();

//----- (00462D20) --------------------------------------------------------
int  ExcString_ReleaseText(_DWORD *a1)
{
  int v1; // ecx

  Compat_StringHolderDestructor(a1);
  return v1;
}
// 462D28: variable 'v1' is possibly undefined

//----- (00462D30) --------------------------------------------------------
int  ExcString_GetTextPtr(int a1)
{
  return *(_DWORD *)a1;
}

//----- (00462D40) --------------------------------------------------------
int  ExcString_GetTextPtrDup(int a1)
{
  return *(_DWORD *)a1;
}

//----- (00462D50) --------------------------------------------------------
int  ExcString_ReleaseTextDup(_DWORD *a1)
{
  int v1; // ecx

  Compat_StringHolderDestructor(a1);
  return v1;
}
// 462D58: variable 'v1' is possibly undefined

//----- (00462D60) --------------------------------------------------------
int ExcString_GetErrorCodeStub()
{
  return 0;
}

//----- (00462D80) --------------------------------------------------------
int ExcString_GetErrorCodeStubDup()
{
  return 0;
}

//----- (00462E40) --------------------------------------------------------
int  CAviDecompressor_ConvertRGB888to565Row(_WORD *a1, _DWORD *a2, int a3)
{
  int v6; // ebx
  unsigned __int64 v7; // rt0
  int result; // eax

  v6 = 0;
  do
  {
    HIDWORD(v7) = v6;
    LODWORD(v7) = *a2;
    HIDWORD(v7) = v7 >> 19;
    LODWORD(v7) = *a2 << 16;
    HIDWORD(v7) = v7 >> 26;
    LODWORD(v7) = *a2 << 24;
    v6 = v7 >> 27;
    result = v6;
    a2 = (_DWORD *)((char *)a2 + 3);
    *a1++ = v6;
    --a3;
  }
  while ( a3 );
  return result;
}

//----- (00462EA0) --------------------------------------------------------
unsigned int  CAviDecompressor_ConvertRGB565to888Row(unsigned int *result, _WORD *a2, int a3)
{
  unsigned int v6; // ebx
  unsigned int v7; // eax
  unsigned int v8; // ebx
  unsigned int v9; // eax
  unsigned __int64 v10; // rt0

  v6 = 0;
  HIWORD(v7) = 0;
  do
  {
    LOWORD(v7) = *a2;
    v8 = __PAIR64__(v6, v7) >> 8;
    v9 = v7 << 21;
    HIDWORD(v10) = __PAIR64__(v8, v9) >> 24;
    LODWORD(v10) = v9 << 6;
    v6 = v10 >> 24;
    v7 = 0;
    ++a2;
    *result = v6;
    result = (unsigned int *)((char *)result + 3);
    --a3;
  }
  while ( a3 );
  return v7;
}

//----- (00462FE0) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow16bpp(void *a1, const void *a2, int a3)
{
  int result; // eax

  result = 2 * a3;
  qmemcpy(a1, a2, 2 * a3);
  return result;
}

//----- (00463010) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow24bpp(void *a1, const void *a2, int a3)
{
  int result; // eax

  result = 3 * a3;
  qmemcpy(a1, a2, 3 * a3);
  return result;
}

//----- (00463040) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow32bpp(void *a1, const void *a2, int a3)
{
  int result; // eax

  result = 4 * a3;
  qmemcpy(a1, a2, 4 * ((unsigned int)(4 * a3) >> 2));
  return result;
}

//----- (00463070) --------------------------------------------------------
int (* CAviDecompressor_FindColorConvertRoutine(int (**a1)(), int (**a2)()))()
{
  int v4; // ecx
  int (**v5)(); // eax
  int (**i)(); // edx

  v4 = 0;
  v5 = &g_AviDecompressor_PixelCopyFnTable[1];
  for ( i = &g_AviDecompressor_PixelCopyFnTable[4];
        *v5 != *a1 || v5[1] != a1[1] || v5[2] != a1[2] || *i != *a2 || i[1] != a2[1] || i[2] != a2[2];
        i += 7 )
  {
    v5 += 7;
    if ( ++v4 >= 2 )
      return 0;
  }
  return g_AviDecompressor_PixelCopyFnTable[7 * v4];
}
// 519A40: using guessed type int (*off_519A40[7])();

//----- (00463220) --------------------------------------------------------
__int16  CAviDecompressor_SetupBlitFormat(int (*a1)(), int a2, int a3, int a4, int a5)
{
  int (*v5)(); // esi
  int v7; // ecx
  unsigned int v8; // edi
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v19; // [esp+0h] [ebp-28h] BYREF
  int v20; // [esp+4h] [ebp-24h]
  int v21; // [esp+8h] [ebp-20h]
  int v22; // [esp+Ch] [ebp-1Ch] BYREF
  int v23; // [esp+10h] [ebp-18h]
  int v24; // [esp+14h] [ebp-14h]
  int v25; // [esp+18h] [ebp-10h]

  v5 = a1;
  v7 = *(_DWORD *)(a2 + 16);
  LOWORD(a1) = *(_WORD *)(a2 + 14);
  v8 = *(unsigned __int16 *)(a4 + 14);
  v25 = (unsigned __int16)a1;
  if ( v7 && v7 != 3 )
    return (__int16)a1;
  v9 = *(_DWORD *)(a4 + 16);
  if ( v9 )
  {
    if ( v9 != 3 )
      return (__int16)a1;
  }
  v10 = *(_DWORD *)(a2 + 16);
  if ( v10 )
  {
    v22 = *(_DWORD *)(a2 + 40);
    v23 = *(_DWORD *)(a2 + 44);
    v24 = *(_DWORD *)(a2 + 48);
  }
  else
  {
    LOWORD(v10) = *(_WORD *)(a2 + 14);
    if ( (unsigned __int16)v10 == 16 )
    {
      v22 = 63488;
      v23 = 2016;
      v24 = 31;
    }
    else if ( v10 == 24 )
    {
      v22 = 16711680;
      v23 = 65280;
      v24 = 255;
    }
    else
    {
      v22 = 1 << v10;
      v23 = 1 << v10;
      v24 = 1 << v10;
    }
  }
  if ( *(_DWORD *)(a4 + 16) )
  {
    v19 = *(_DWORD *)(a4 + 40);
    v20 = *(_DWORD *)(a4 + 44);
    v12 = *(_DWORD *)(a4 + 48);
  }
  else
  {
    v11 = *(unsigned __int16 *)(a4 + 14);
    if ( (unsigned __int16)v11 == 16 )
    {
      v19 = 63488;
      v12 = 31;
      v20 = 2016;
    }
    else
    {
      if ( v11 == 24 )
      {
        v19 = 16711680;
        v20 = 65280;
        v21 = 255;
        goto LABEL_12;
      }
      v12 = 1 << v11;
      v19 = 1 << v11;
      v20 = 1 << v11;
    }
  }
  v21 = v12;
LABEL_12:
  *(_DWORD *)v5 = *(_DWORD *)(a4 + 4);
  if ( a5 )
  {
    v13 = a5;
  }
  else
  {
    v13 = *(_DWORD *)v5 * ((int)(v8 + 7) >> 3) + 3;
    LOBYTE(v13) = v13 & 0xFC;
  }
  *((_DWORD *)v5 + 2) = v13;
  if ( !a3 )
  {
    v17 = *(_DWORD *)v5 * ((v25 + 7) >> 3) + 3;
    LOBYTE(v17) = v17 & 0xFC;
    a3 = v17;
  }
  *((_DWORD *)v5 + 3) = a3;
  v14 = *(_DWORD *)(a4 + 8);
  v15 = *(_DWORD *)(a2 + 8);
  if ( v14 < 0 )
    v16 = -v14;
  else
    v16 = v14;
  *((_DWORD *)v5 + 1) = v16;
  if ( v19 == v22 && v20 == v23 && v21 == v24 )
  {
    LOWORD(a1) = v15 * v14;
    if ( v15 * v14 <= 0 )
    {
      if ( v8 >= 0x18 )
      {
        if ( v8 <= 0x18 )
        {
          *((_DWORD *)v5 + 5) = CAviDecompressor_CopyPixelRow24bpp;
        }
        else if ( v8 == 32 )
        {
          *((_DWORD *)v5 + 5) = CAviDecompressor_CopyPixelRow32bpp;
        }
      }
      else if ( v8 == 16 )
      {
        *((_DWORD *)v5 + 5) = CAviDecompressor_CopyPixelRow16bpp;
      }
    }
    else
    {
      *((_DWORD *)v5 + 4) = (int)(v8 + 7) >> 3;
    }
  }
  else
  {
    a1 = CAviDecompressor_FindColorConvertRoutine((int (**)())&v19, (int (**)())&v22);
    *((_DWORD *)v5 + 5) = a1;
  }
  if ( v14 >= 0 )
  {
    if ( v15 >= 0 )
      return (__int16)a1;
    goto LABEL_47;
  }
  *((_DWORD *)v5 + 2) = -*((_DWORD *)v5 + 2);
  if ( v15 < 0 )
LABEL_47:
    *((_DWORD *)v5 + 3) = -*((_DWORD *)v5 + 3);
  return (__int16)a1;
}
// 46333D: variable 'v15' is possibly undefined

//----- (004634A0) --------------------------------------------------------
signed int  CAviDecompressor_BlitRows(_DWORD *a1, char *a2, char *a3)
{
  _DWORD *v3; // ecx
  int v5; // edx
  char *v6; // esi
  char *v7; // edi
  signed int result; // eax
  int i; // ebp

  v3 = a1;
  v5 = a1[4];
  if ( v5 )
  {
    result = a1[1] * *a1 * v5;
    qmemcpy(a2, a3, result);
  }
  else
  {
    v6 = a2;
    v7 = a3;
    if ( (int)a1[2] < 0 )
      v7 = &a3[(a1[1] - 1) * -a1[2]];
    result = a1[3];
    if ( result < 0 )
      v6 += -result * (v3[1] - 1);
    for ( i = 0; i < v3[1]; v6 += v3[3] )
    {
      ++i;
      ((void (__fastcall *)(_DWORD *, char *))v3[5])(v3, v7);
      result = v3[2];
      v7 += result;
    }
  }
  return result;
}
// 4634D1: variable 'v3' is possibly undefined

//----- (004635A0) --------------------------------------------------------
unsigned int  CAviDecompressor_NormalizeColorMask(unsigned int a1)
{
  char v1; // cl
  char v2; // cf

  v1 = 0;
  do
  {
    ++v1;
    v2 = a1 & 1;
    a1 >>= 1;
  }
  while ( !v2 );
  return a1 << v1;
}

