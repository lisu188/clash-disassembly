/* Generated from src/recovered/runtime/00461520_platform_input.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00461520) --------------------------------------------------------
int Input_Init(void)
{
  return 0;
}

//----- (00461530) --------------------------------------------------------
int Input_Shutdown(void)
{
  return 0;
}

//----- (00461540) --------------------------------------------------------
int  DD_GetSurfacePitch(int renderState)
{
  return Compat_RenderStateTailFields(renderState)->field_468_active;
}

//----- (00461570) --------------------------------------------------------
BOOL  Input_IsKeyPressed(int scanCode)
{
  return g_Input_KeyStateArray[scanCode] < 0;
}

//----- (00461580) --------------------------------------------------------
BOOL Input_IsAnyKeyPressed(void)
{
  int scanCode; // edx
  BOOL result; // eax
  int v2; // edx

  scanCode = 0;
  while ( 1 )
  {
    result = Input_IsKeyPressed(scanCode);
    if ( result )
      break;
    scanCode = v2 + 1;
    if ( scanCode >= 128 )
      return result;
  }
  return 1;
}
// 46158E: variable 'v2' is possibly undefined

//----- (004615A0) --------------------------------------------------------
signed int Input_PopKey(void)
{
  int scanCode; // edx
  int pressedScanCode; // edx

  scanCode = 0;
  while ( !Input_IsKeyPressed(scanCode) )
  {
    scanCode = pressedScanCode + 1;
    if ( scanCode >= 128 )
      return -1;
  }
  return pressedScanCode;
}
// 4615AE: variable 'v1' is possibly undefined

//----- (004615D0) --------------------------------------------------------
char  Input_KeyToChar(unsigned int scanCode)
{
  if ( g_LanguageIndex == 2 )
  {
    g_KeyChar = 122;
    g_Input_ScanCodeChar_LangSwap = 121;
  }
  if ( (int)scanCode >= 16 && scanCode <= 0x1A )
    return g_Input_ScanCodeChars_TopRow[scanCode];
  if ( (int)scanCode >= 30 && scanCode <= 0x29 )
    return g_Input_ScanCodeChars_HomeRow[scanCode];
  if ( (int)scanCode >= 44 && scanCode <= 0x35 )
    return g_Input_ScanCodeChars_BottomRow[scanCode];
  if ( (int)scanCode >= 2 && scanCode <= 0xE )
    return g_Input_ScanCodeChars_NumberRow[scanCode];
  if ( scanCode == 57 )
    return 32;
  return 0;
}
// 511130: using guessed type char g_LanguageIndex;
// 519985: using guessed type char g_KeyChar;
// 5199A0: using guessed type char byte_5199A0;

//----- (00461650) --------------------------------------------------------
BOOL  Input_ClearKey(int keyCode, int a2)
{
  int v3; // ecx
  int i; // ebx
  int v5; // ecx
  int repeatDelay; // eax
  unsigned int nowTick; // eax
  unsigned int v8; // edx
  BOOL result; // eax
  int v10; // ecx

  if ( keyCode == g_Input_LastRepeatKeyCode )
    ++g_Input_KeyRepeatCount;
  else
    g_Input_KeyRepeatCount = 1;
  for ( i = Time_Now(keyCode, a2); Input_IsKeyPressed(v3); DD_Pump((int)g_RenderState, i) )
  {
    repeatDelay = g_Input_KeyRepeatCount <= 1 ? 30 : 10;
    nowTick = Time_Now(v5, i + repeatDelay);
    if ( nowTick >= v8 )
      break;
  }
  result = Input_IsKeyPressed(v5);
  if ( !result )
    g_Input_KeyRepeatCount = 0;
  g_Input_LastRepeatKeyCode = v10;
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
int Input_MouseInit(void)
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
BOOL Input_MousePresent(void)
{
  return (GetVersion() & 0x80000000) == 0 && (unsigned __int8)GetVersion() == 4;
}

//----- (00461770) --------------------------------------------------------
BOOL Input_MouseAcquire(void)
{
  return (GetVersion() & 0x80000000) != 0 && (unsigned __int8)GetVersion() == 4;
}

//----- (004617A0) --------------------------------------------------------
int  Render_DefaultRH(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aStdrhCall);
  return Render_EndModeSwitch((int)&g_MainRenderDevice, a2, a3);
}

//----- (004617C0) --------------------------------------------------------
LRESULT __thiscall Platform_MainWindowProc(void *this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  DWORD lostStatus; // eax
  DWORD surfaceLost; // ebp
  int v7; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  lostStatus = 0;
  if ( g_DDrawDevicePtr )
    lostStatus = Compat_DirectDrawSurfaceHandleIsLost(g_DDrawDevicePtr);
  surfaceLost = lostStatus;
  Debug_Log((int)this, Msg, lostStatus, (int)aDmessage0x08xL);
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
    Debug_Log(v7, Msg, surfaceLost, (int)aWm_paint);
    if ( *(_BYTE *)g_AppCommandLine == 119 )
      DefWindowProcA(hWnd, Msg, wParam, lParam);
    else
      ValidateRect(hWnd, 0);
    if ( g_AppIsActive != 1 || !g_DDrawDevicePtr )
      return 0;
    Debug_Log(v12, Msg, surfaceLost, (int)aRestoreD);
    if ( g_DDrawDevicePtr )
      Render_RestoreLostSurfaceIfNeeded(g_RenderContext);
    if ( g_RenderHook && g_DisplaySurfaceBitDepth == 8 )
    {
      Debug_Log((int)g_RenderHook, Msg, surfaceLost, (int)aRedrawhandler0);
      g_RenderHook(v13, Msg, surfaceLost);
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
    Debug_Log(v7, wParam, surfaceLost, (int)aWm_activateapp);
    if ( (unsigned __int16)wParam == 1 )
    {
      Debug_Log(v9, 1, surfaceLost, (int)aAcquire);
      InputBackend_Acquire(&g_InputBackendState);
      if ( g_DDrawDevicePtr )
        Render_RestoreLostSurfaceIfNeeded(g_RenderContext);
      if ( g_ShouldPresentOnReactivate )
        Render_Present((int)g_RenderState);
      if ( g_SoundPausedForInactiveApp )
        CSS_ResumeSound(g_Audio_ActiveSoundHandle, 1000);
      g_SoundPausedForInactiveApp = 0;
      Debug_Log(v11, 1, surfaceLost, (int)aResumedSoundD);
    }
    if ( !(_WORD)wParam )
    {
      g_ShouldPresentOnReactivate = g_CursorOverlayPresented;
      if ( !surfaceLost )
        Render_Pump();
      Debug_Log(v9, 0, surfaceLost, (int)aUnacquire);
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
HWND  Platform_CreateMainWindow(HINSTANCE a1, int nCmdShow)
{
  DWORD windowStyle; // ebx
  HWND result; // eax
  WNDCLASSA wndClass; // [esp+0h] [ebp-34h] BYREF
  int savedCmdShow; // [esp+2Ch] [ebp-8h]

  savedCmdShow = nCmdShow;
  wndClass.hInstance = a1;
  wndClass.style = 3;
  wndClass.lpfnWndProc = (WNDPROC)Platform_MainWindowProc;
  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hIcon = LoadIconA(a1, (LPCSTR)0x64);
  wndClass.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  wndClass.hbrBackground = (HBRUSH)GetStockObject(4);
  wndClass.lpszClassName = aClash_1;
  wndClass.lpszMenuName = 0;
  RegisterClassA(&wndClass);
  windowStyle = 0x80000000;
  if ( *(_BYTE *)g_AppCommandLine && *(_BYTE *)(g_AppCommandLine + 1) == 119 )
    windowStyle = -2133917696;
  result = CreateWindowExA(0, ClassName, WindowName, windowStyle, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, a1, 0);
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

  Render_BlitSurface(&g_MainRenderDevice, 0, a1, (DWORD)savedregs);
  while ( 1 )
  {
    if ( !PeekMessageA(&Msg, 0, 0, 0, 0) && g_AppIsActive )
      return 1;
    hwnd = Msg.hwnd;
    if ( g_DDrawDevicePtr )
      Compat_DirectDrawSurfaceHandleIsLost(g_DDrawDevicePtr);
    Debug_Log((int)hwnd, 0, (DWORD)savedregs, (int)aAmessage0x08xL);
    if ( !GetMessageA(&Msg, 0, 0, 0) )
      break;
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
    if ( !g_AppIsActive )
      WaitMessage();
  }
  Render_BeginModeSwitch(&g_MainRenderDevice);
  return Msg.wParam;
}
// 461B87: variable 'hwnd' is possibly undefined
// 5199D4: using guessed type int g_AppIsActive;
// 51D57C: using guessed type int dword_51D57C;

//----- (00461C00) --------------------------------------------------------
int  Mem_Alloc(int size, int a2, char a3, DWORD a4)
{
  int allocatedPtr; // [esp+0h] [ebp-18h] BYREF
  _DWORD v7[5]; // [esp+4h] [ebp-14h] BYREF

  v7[4] = a2;
  v7[0] = nmalloc_(size, 0);
  qmemcpy(&allocatedPtr, v7, sizeof(allocatedPtr));
  if ( !allocatedPtr )
  {
    Debug_Log(0, a3, a4, (int)aNotEnoughMe_13);
    App_RequestQuit((int)aNotEnoughMe_14);
  }
  return allocatedPtr;
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
signed int  Win_BeginModeChange(const char *aviName, char *pathBuffer)
{
  char *base_path;
  int query_handle;
  int direct_file_available;

  query_handle = 0;
  direct_file_available = 0;
  base_path = FileSystem_GetInstallRootPath();
  sprintf_(pathBuffer, "%savi\\%s.avi", base_path, aviName);
  query_handle = FileSystem_ResolveReadPath(pathBuffer, 0);
  if ( !query_handle )
    direct_file_available = Compat_CanOpenReadPath(pathBuffer);
  if ( !query_handle )
  {
    if ( !direct_file_available )
    {
      sprintf_(pathBuffer, "avi\\%s.avi", aviName);
      query_handle = FileSystem_ResolveReadPath(pathBuffer, 0);
      if ( !query_handle )
        direct_file_available = Compat_CanOpenReadPath(pathBuffer);
    }
  }
  if ( !query_handle && !direct_file_available )
    App_RequestQuit((int)g_UI_CdMissingMessageByLanguage[(unsigned __int8)g_LanguageIndex]);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  return 1;
}
// 511130: using guessed type char g_LanguageIndex;
// 5199F0: using guessed type char *off_5199F0[3];

//----- (00461D90) --------------------------------------------------------
void  Win_EndModeChange(int a1, char *aviPath, int stretchPlayback, int a4)
{
  tagRECT destRect; // [esp+0h] [ebp-10h] BYREF

  if ( g_SdlTransitionAnimSkipRequested )
  {
    destRect = *(tagRECT *)g_Device_DefaultWindowRect;
    if ( stretchPlayback )
    {
      PlayAviStretch(
        aviPath,
        *(IDirectDrawSurface **)(*(_DWORD *)(g_RenderContext + 4) + 164),
        &destRect,
        (int (*)(void))Video_CanContinuePlayback,
        1500);
    }
    else
    {
      if ( g_RenderDeviceAviModeChangeGuard )
        g_RenderDeviceAviModeChangePending = 1;
      PlayAvi(
        aviPath,
        *(IDirectDrawSurface **)(g_DDrawDevicePtr + 164),
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
void  Video_Avi_playIn(const char *aviName, int a2, int fadeOutFirst, int a4, int switchTo16bpp, int switchBackTo8bpp)
{
  int v7; // edi
  int v9; // ecx
  DWORD TickCount; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int (*renderHook)(); // ebp
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  char pathBuffer[100]; // [esp+0h] [ebp-80h] BYREF
  int (*savedRenderHook)(); // [esp+64h] [ebp-1Ch]
  int v20; // [esp+68h] [ebp-18h]
  int prevHandle; // [esp+6Ch] [ebp-14h]
  int stdHandle; // [esp+70h] [ebp-10h]

  if ( g_BootstrapSkipIntroAviPlayback )
    return;
  v20 = a2;
  v7 = a4;
  Debug_Log(fadeOutFirst, a4, (DWORD)aviName, (int)aAvi_playIn);
  stdHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v9, a4, (DWORD)aviName, (int)aSetrhS08x_19);
  prevHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  if ( fadeOutFirst && g_DisplaySurfaceBitDepth == 8 )
  {
    Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 40);
    Render_UnlockBackbuffer((int)&g_MainRenderDevice);
  }
  else if ( g_DisplaySurfaceBitDepth == 8 )
  {
    Render_BlitSurface(&g_MainRenderDevice, 1, a4, (DWORD)aviName);
  }
  TickCount = GetTickCount();
  v11 = switchTo16bpp;
  g_VideoModeSwitchStartTick = TickCount;
  if ( switchTo16bpp && g_DisplaySurfaceBitDepth == 8 )
  {
    Debug_Log(switchTo16bpp, a4, (DWORD)aviName, (int)aInit16bpp);
    LOBYTE(a4) = 16;
    Render_BeginModeSwitch(&g_MainRenderDevice);
    Render_SetPixelFormat((int)&g_MainRenderDevice, (int)(intptr_t)hWnd, 16, (DWORD)aviName);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    InputBackend_Acquire(&g_InputBackendState);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
    DD_Pump((int)g_RenderState, 16);
  }
  if ( Win_BeginModeChange(aviName, pathBuffer) )
  {
    LOBYTE(a4) = v20;
    Win_EndModeChange(v7, pathBuffer, fadeOutFirst, v20);
    Render_Begin((int)g_RenderState, 0);
  }
  if ( switchBackTo8bpp && g_DisplaySurfaceBitDepth != 8 )
  {
    Debug_Log(v13, a4, (DWORD)aviName, (int)aClose16bpp);
    LOBYTE(a4) = 8;
    Render_BeginModeSwitch(&g_MainRenderDevice);
    Render_SetPixelFormat((int)&g_MainRenderDevice, (int)(intptr_t)hWnd, 8, (DWORD)aviName);
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
    if ( g_DisplaySurfaceBitDepth == 8 )
      Render_ReleaseTempSurface((int *)&g_MainRenderDevice);
    if ( g_DisplaySurfaceBitDepth == 8 && !switchTo16bpp )
      Render_EndModeSwitch((int)&g_MainRenderDevice, a4, (DWORD)aviName);
  }
  g_VideoModeSwitchStartTick = 0;
  Render_SetResourceHandle((int)&g_MainRenderDevice, prevHandle);
  renderHook = g_RenderHook;
  Debug_Log(v15, a4, (DWORD)g_RenderHook, (int)aUnsetrh08x_19);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, stdHandle);
  Debug_Log(v16, a4, (DWORD)renderHook, (int)aAvi_playOut);
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
signed int  Win_PlayModeChangeFrameTransition(const char *aviName, int restorePalette, int a3, char a4, DWORD a5, ...)
{
  signed int result; // eax
  int stdHandle; // edi
  int v8; // ecx
  void *paletteArrayCtorDescriptor; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  _DWORD *loadedSpriteSet; // eax
  int v15; // ecx
  _DWORD *Surface; // eax
  _DWORD *animSurface; // esi
  DWORD v18; // ebp
  int v19; // ecx
  void (**v20)(void); // ebx
  int v21; // ecx
  int v22; // edx
  char pathBuffer[100]; // [esp+1Ch] [ebp-88h] BYREF
  _DWORD *animSpriteSet; // [esp+80h] [ebp-24h] BYREF
  int SpriteWidth; // [esp+84h] [ebp-20h]
  int paletteArray; // [esp+88h] [ebp-1Ch]
  int prevHandle; // [esp+8Ch] [ebp-18h]
  int (*savedRenderHook)(); // [esp+90h] [ebp-14h]
  int restorePaletteFlag; // [esp+94h] [ebp-10h]
  int SpriteHeight; // [esp+98h] [ebp-Ch]

  restorePaletteFlag = restorePalette;
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
      (int)(intptr_t)aviName,
      restorePaletteFlag,
      a3);
    return 1;
  }
  result = Win_BeginModeChange(aviName, pathBuffer);
  Diagnostics_TraceWorldMapActionEvent("transition_after_begin_mode", g_SelectedUnitIndex, result, restorePaletteFlag, 0);
  if ( result )
  {
    result = gameData;
    if ( *(_DWORD *)(gameData + 147147) )
    {
      if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      {
        stdHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
        Diagnostics_TraceWorldMapActionEvent("transition_after_set_rh_std", g_SelectedUnitIndex, stdHandle, 0, 0);
        savedRenderHook = g_RenderHook;
        g_RenderHook = (int (*)())Render_DefaultRH;
        Debug_Log(v8, a4, a5, (int)aSetrhS08x_20);
        prevHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_set_rh_prev", g_SelectedUnitIndex, prevHandle, 0, 0);
        Render_Pump();
        Diagnostics_TraceWorldMapActionEvent("transition_after_render_pump", g_SelectedUnitIndex, 0, 0, 0);
        LOBYTE(paletteArrayCtorDescriptor) = 0;
        Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_backbuffer_fill", g_SelectedUnitIndex, 0, 0, 0);
        Video_EnterGreyscaleTransition((int *)&g_MainRenderDevice, v10, 0, a5);
        Diagnostics_TraceWorldMapActionEvent("transition_after_gray_palette", g_SelectedUnitIndex, 0, 0, 0);
        v12 = Mem_Alloc(1024, 0, 0, a5);
        if ( v12 )
        {
          paletteArrayCtorDescriptor = &g_Runtime_PaletteArrayCtorDescriptor;
          v12 = _wcpp_4_ctor_array__(v12, 256);
        }
        paletteArray = v12;
        Diagnostics_TraceWorldMapActionEvent("transition_after_palette_alloc", g_SelectedUnitIndex, paletteArray, 0, 0);
        g_RenderDevice = &g_MainRenderDevice;
        loadedSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)&g_MainRenderDevice);
        if ( loadedSpriteSet )
          loadedSpriteSet = DLXSpriteSet_Load(loadedSpriteSet, "anim_fr.s32");
        animSpriteSet = loadedSpriteSet;
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_load", g_SelectedUnitIndex, (int)(uintptr_t)animSpriteSet, 0, 0);
        if ( !animSpriteSet )
        {
          Win_EndModeChange(0, pathBuffer, 0, 0);
          g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
          if ( paletteArray )
            j__nfree_(paletteArray);
          Render_SetResourceHandle((int)&g_MainRenderDevice, prevHandle);
          g_RenderHook = savedRenderHook;
          Render_SetResourceHandle((int)&g_MainRenderDevice, stdHandle);
          Diagnostics_TraceWorldMapActionEvent("transition_anim_missing_unwound", g_SelectedUnitIndex, 0, 0, 0);
          return 0;
        }
        SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)loadedSpriteSet, 0);
        SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)animSpriteSet, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_dims", g_SelectedUnitIndex, SpriteHeight, SpriteWidth, 0);
        Surface = (_DWORD *)Mem_Alloc(188, 0, 0, (DWORD)&g_MainRenderDevice);
        if ( Surface )
          Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
        animSurface = Surface;
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_create", g_SelectedUnitIndex, (int)(uintptr_t)animSurface, 0, 0);
        Render_FillRect(0, Surface, 80, 80, SpriteHeight + 79, SpriteWidth + 79, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_fill", g_SelectedUnitIndex, 0, 0, 0);
        v12 = DLX_GetSpriteForChar((int)animSpriteSet, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_sprite_lookup", g_SelectedUnitIndex, v12, 0, 0);
        Compat_RenderDeviceDrawMenuSprite(80, 80, v12, 0);
        v18 = *((_DWORD *)g_RenderDevice + 46);
        Diagnostics_TraceWorldMapActionEvent("transition_after_sprite_draw", g_SelectedUnitIndex, 0, 0, 0);
        DLXSpriteSet_ReleaseAndClear((int *)&animSpriteSet);
        Diagnostics_TraceWorldMapActionEvent("transition_after_anim_free", g_SelectedUnitIndex, 0, 0, 0);
        Audio_DuckMusicVolume();
        Diagnostics_TraceWorldMapActionEvent("transition_after_fade_wait", g_SelectedUnitIndex, 0, 0, 0);
        Win_EndModeChange(100, pathBuffer, 0, 100);
        Diagnostics_TraceWorldMapActionEvent("transition_after_end_mode", g_SelectedUnitIndex, 0, 0, 0);
        if ( g_SdlTransitionAnimSkipRequested )
          Diagnostics_TraceWorldMapActionEvent("transition_skip_temp_release_sdl", g_SelectedUnitIndex, g_SdlTransitionAnimSkipRequested, 0, 0);
        Diagnostics_TraceWorldMapActionEvent("transition_after_temp_release", g_SelectedUnitIndex, g_SdlTransitionAnimSkipRequested, 0, 0);
        LOBYTE(v20) = 0;
        Render_FillRect(animSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, 0x50u, 0x50u);
        Diagnostics_TraceWorldMapActionEvent("transition_after_restore_surface_fill", g_SelectedUnitIndex, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
        if ( restorePaletteFlag )
        {
          Video_ExitGreyscaleTransition((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, v21, 0, v18);
          Audio_RestoreMusicVolume();
          Diagnostics_TraceWorldMapActionEvent("transition_after_palette_restore", g_SelectedUnitIndex, 0, 0, 0);
        }
        if ( animSurface )
        {
          v20 = (void (**)(void))animSurface[46];
          RenderSurface_InvokeSlot0(animSurface, 2);
        }
        Diagnostics_TraceWorldMapActionEvent("transition_after_surface_release", g_SelectedUnitIndex, 0, 0, 0);
        j__nfree_(paletteArray);
        Diagnostics_TraceWorldMapActionEvent("transition_after_palette_free", g_SelectedUnitIndex, 0, 0, 0);
        v22 = prevHandle;
        Render_Present((int)g_RenderState);
        Diagnostics_TraceWorldMapActionEvent("transition_after_present", g_SelectedUnitIndex, 0, 0, 0);
        Render_SetResourceHandle((int)&g_MainRenderDevice, v22);
        Debug_Log((int)g_RenderHook, (char)v20, v18, (int)aUnsetrh08x_20);
        g_RenderHook = savedRenderHook;
        return Render_SetResourceHandle((int)&g_MainRenderDevice, stdHandle);
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
void __fastcall Video_PlayAviWithModeGuard(int aviName, const char *aviPath)
{
  if ( !strcmp_(aviName, aKon_por1_1) )
  {
    if ( g_MissionDefeatVideoPlayedGuard )
      return;
    g_MissionDefeatVideoPlayedGuard = 1;
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  Video_Avi_playIn(aviPath, 0, 1, 0, 1, 1);
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 5452E8: using guessed type int dword_5452E8;

//----- (00462480) --------------------------------------------------------
int  Mission_PlayInfoSlideshow(int missionIndex, char *a2)
{
  int v2; // ecx
  int v3; // ecx
  int wavFileNumber; // eax
  unsigned __int8 wavPrefixChar; // al
  _DWORD *Surface; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  int surfaceC; // esi
  int v11; // ecx
  int slideANumber; // eax
  unsigned __int8 slideAPrefixChar; // al
  int slideBNumber; // eax
  unsigned __int8 slideBPrefixChar; // al
  _DWORD *slideBSurface; // edi
  int slideCNumber; // eax
  unsigned __int8 slideCPrefixChar; // al
  int v19; // edx
  int v20; // ecx
  int musicHandle; // edi
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
  int wavNumberArg; // [esp-4h] [ebp-44Ch]
  int slideANumberArg; // [esp-4h] [ebp-44Ch]
  int slideBNumberArg; // [esp-4h] [ebp-44Ch]
  int slideCNumberArg; // [esp-4h] [ebp-44Ch]
  unsigned __int8 paletteBuffer[1024]; // [esp+0h] [ebp-448h] BYREF
  char filenameBuffer[52]; // [esp+400h] [ebp-48h] BYREF
  int (*savedRenderHook)(); // [esp+434h] [ebp-14h]
  int stdHandle; // [esp+438h] [ebp-10h]
  _DWORD *surfaceB; // [esp+43Ch] [ebp-Ch]
  int missionNumber; // [esp+440h] [ebp-8h]
  int lectorSoundHandle; // [esp+444h] [ebp-4h]
  _DWORD savedregs[6]; // [esp+448h] [ebp+0h] BYREF

  missionNumber = missionIndex;
  stdHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v2, (char)a2, (DWORD)savedregs, (int)aSetrhS08x_21);
  Render_Pump();
  v3 = -1;
  lectorSoundHandle = -1;
  if ( g_LanguageIndex == 1 )
  {
    a2 = aSfxMisinfoC_02;
    if ( missionNumber > 9 )
      wavFileNumber = missionNumber - 9;
    else
      wavFileNumber = missionNumber + (unsigned __int8)g_LanguageIndex;
    wavNumberArg = wavFileNumber;
    if ( missionNumber > 9 )
      wavPrefixChar = 80;
    else
      wavPrefixChar = 67;
    sprintf_(filenameBuffer, "sfx\\misinfo\\%c_%02d.WAV", wavPrefixChar, wavNumberArg);
    loadFileSusp(filenameBuffer, aDataLector_w_0);
  }
  Surface = (_DWORD *)Mem_Alloc(188, v3, (char)a2, (DWORD)savedregs);
  if ( Surface )
  {
    LOBYTE(a2) = -32;
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  }
  surfaceB = Surface;
  v8 = Mem_Alloc(188, v7, (char)a2, (DWORD)savedregs);
  if ( v8 )
    v8 = (int)Render_CreateSurface(v8, SCREEN_WIDTH, SCREEN_HEIGHT);
  RenderSurface_InvokeSlot56((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  RenderSurface_InvokeSlot56(surfaceB);
  surfaceC = v8;
  RenderSurface_InvokeSlot56((_DWORD *)(uintptr_t)(unsigned int)surfaceC);
  _wcpp_4_ctor_array__((int)paletteBuffer, 256);
  if ( missionNumber > 9 )
    slideANumber = missionNumber - 9;
  else
    slideANumber = missionNumber + 1;
  slideANumberArg = slideANumber;
  if ( missionNumber > 9 )
    slideAPrefixChar = 80;
  else
    slideAPrefixChar = 67;
  sprintf_(filenameBuffer, "misinfo\\%c_%02d_A.PCX", slideAPrefixChar, slideANumberArg);
  RenderSurface_InvokeSlot48LoadPCX(
    (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
    filenameBuffer,
    0,
    (uintptr_t)paletteBuffer);
  if ( missionNumber > 9 )
    slideBNumber = missionNumber - 9;
  else
    slideBNumber = missionNumber + 1;
  slideBNumberArg = slideBNumber;
  if ( missionNumber > 9 )
    slideBPrefixChar = 80;
  else
    slideBPrefixChar = 67;
  slideBSurface = surfaceB;
  sprintf_(filenameBuffer, "misinfo\\%c_%02d_B.PCX", slideBPrefixChar, slideBNumberArg);
  RenderSurface_InvokeSlot48LoadPCX(slideBSurface, filenameBuffer, 0, (uintptr_t)paletteBuffer);
  if ( missionNumber > 9 )
    slideCNumber = missionNumber - 9;
  else
    slideCNumber = missionNumber + 1;
  slideCNumberArg = slideCNumber;
  if ( missionNumber > 9 )
    slideCPrefixChar = 80;
  else
    slideCPrefixChar = 67;
  sprintf_(filenameBuffer, "misinfo\\%c_%02d_C.PCX", slideCPrefixChar, slideCNumberArg);
  RenderSurface_InvokeSlot48LoadPCX((_DWORD *)(uintptr_t)(unsigned int)surfaceC, filenameBuffer, 0, (uintptr_t)paletteBuffer);
  RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
  intro_start_time = Time_Now(v20, v19);
  musicHandle = Sound_PlayNamedSfxFile(aMusicCampain, 21);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 50);
  if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 420, 0) )
  {
    RenderSurface_InvokeSlot36(surfaceB);
    if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 550, 0) )
    {
      RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
      if ( !UI_WaitForAnyKeyOrClick(intro_start_time + 660, 0) )
      {
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)surfaceC);
        if ( g_LanguageIndex == 1 )
          lectorSoundHandle = CSS_PlaySound((int)aDataLector_w_2, 64, 0, 0);
        while ( (g_LanguageIndex != 1 || CSS_IsPlaying(lectorSoundHandle)) && !UI_WaitForKeyOrTimeout(10, v33) )
          RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)surfaceC);
        if ( g_LanguageIndex == 1 )
          CSS_StopSound(lectorSoundHandle, 0);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        UI_WaitForKeyOrTimeout(30, v34);
      }
    }
  }
  IO_RemoveFileByPath((int)aDataLector_w_0, 0);
  Sleep(0x12Cu);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 60);
  Audio_StopMusicWithFade(musicHandle);
  if ( surfaceB )
    RenderSurface_InvokeSlot0(surfaceB, 2);
  if ( surfaceC )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)surfaceC, 2);
  Debug_Log(stdHandle, (char)g_RenderHook, (DWORD)savedregs, (int)aUnsetrh08x_21);
  g_RenderHook = savedRenderHook;
  return Render_SetResourceHandle((int)&g_MainRenderDevice, stdHandle);
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
int __cdecl Palette_QueryNearestColorIndex(int palettePtr, unsigned __int8 red, unsigned __int8 green, unsigned __int8 blue)
{
  g_Palette_ActivePalettePtr = palettePtr;
  return Palette_FindNearestColorIndex(red, green, blue);
}
// 519A10: using guessed type int dword_519A10;

//----- (004628B0) --------------------------------------------------------
int __cdecl Palette_BuildNearestColorLUT(int palettePtr)
{
  int v2; // [esp+4h] [ebp-10h]
  int blueLevel; // [esp+8h] [ebp-Ch]
  int greenLevel; // [esp+Ch] [ebp-8h]
  unsigned int redLevel; // [esp+10h] [ebp-4h]

  g_Palette_ActivePalettePtr = palettePtr;
  redLevel = 0;
  greenLevel = 0;
  blueLevel = 0;
  while ( 1 )
  {
    do
    {
      g_Rgb15ToPaletteLut[1024 * redLevel + 32 * greenLevel + blueLevel] = Palette_FindNearestColorIndex(8 * redLevel, 8 * greenLevel, 8 * blueLevel);
      ++redLevel;
    }
    while ( redLevel < 0x20 );
    redLevel = 0;
    if ( (unsigned int)++greenLevel >= 0x20 )
    {
      greenLevel = 0;
      if ( (unsigned int)++blueLevel >= 0x20 )
        break;
    }
  }
  return v2;
}
// 462938: variable 'v2' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (0046293B) --------------------------------------------------------
int  Palette_FindNearestColorIndex(unsigned __int8 red, unsigned __int8 green, unsigned __int8 blue)
{
  char *paletteEntry; // esi
  int entriesLeft; // ecx
  int colorIndex; // edx
  char entryRed; // bh
  unsigned __int8 redDiff; // bl
  __int16 v8; // ax
  unsigned __int8 entryGreen; // bh
  unsigned __int8 greenDiff; // bl
  __int16 v11; // ax
  unsigned __int8 entryBlue; // bh
  unsigned __int8 blueDiff; // bl
  __int16 diffSum; // ax
  unsigned int distance; // eax
  unsigned __int8 maxDiff; // [esp+4h] [ebp-1Ch]
  unsigned int bestDistance; // [esp+14h] [ebp-Ch]
  int bestIndex; // [esp+18h] [ebp-8h]

  bestDistance = -1;
  paletteEntry = (char *)g_Palette_ActivePalettePtr;
  entriesLeft = 256;
  colorIndex = 0;
  do
  {
    entryRed = *paletteEntry;
    if ( red > (unsigned __int8)*paletteEntry )
      redDiff = red - entryRed;
    else
      redDiff = entryRed - red;
    v8 = redDiff;
    maxDiff = redDiff;
    entryGreen = paletteEntry[1];
    if ( green > entryGreen )
      greenDiff = green - entryGreen;
    else
      greenDiff = entryGreen - green;
    v11 = greenDiff + v8;
    if ( greenDiff > maxDiff )
      maxDiff = greenDiff;
    entryBlue = paletteEntry[2];
    if ( blue > entryBlue )
      blueDiff = blue - entryBlue;
    else
      blueDiff = entryBlue - blue;
    diffSum = blueDiff + v11;
    if ( blueDiff > maxDiff )
      maxDiff = blueDiff;
    distance = (unsigned __int16)(maxDiff + diffSum);
    if ( distance <= bestDistance )
    {
      bestDistance = distance;
      bestIndex = colorIndex;
    }
    ++colorIndex;
    paletteEntry += 4;
    --entriesLeft;
  }
  while ( entriesLeft );
  return bestIndex;
}
// 4629D7: variable 'v22' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (004629E1) --------------------------------------------------------
int __cdecl Palette_BlendIndexedPixelRun(char *destPixels, char *srcPixels, unsigned __int8 *targetPixels, int count)
{
  int remaining; // ecx
  int srcRed; // ecx
  int targetIndex; // eax
  int redDelta; // edx
  int srcGreen; // ecx
  int greenDelta; // edx
  int srcBlue; // ecx
  int blueDelta; // edx
  char outPixel; // al
  int v15; // [esp-14h] [ebp-2Ch]
  int v16; // [esp+4h] [ebp-14h]
  int absRedDelta; // [esp+8h] [ebp-10h]
  int deltaSum; // [esp+8h] [ebp-10h]
  unsigned int totalDelta; // [esp+8h] [ebp-10h]
  char blendedGreen; // [esp+10h] [ebp-8h]
  char blendedRed; // [esp+14h] [ebp-4h]

  if ( !count )
    return v16;
  remaining = count;
  do
  {
    v15 = remaining;
    srcRed = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*srcPixels);
    targetIndex = *targetPixels;
    redDelta = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * targetIndex) - srcRed)) >> 8;
    if ( redDelta < 0 )
      absRedDelta = -redDelta;
    else
      absRedDelta = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * targetIndex) - srcRed)) >> 8;
    blendedRed = srcRed + redDelta;
    srcGreen = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*srcPixels + 1);
    greenDelta = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *targetPixels + 1) - srcGreen)) >> 8;
    if ( greenDelta < 0 )
      deltaSum = absRedDelta - greenDelta;
    else
      deltaSum = greenDelta + absRedDelta;
    blendedGreen = srcGreen + greenDelta;
    srcBlue = *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * (unsigned __int8)*srcPixels + 2);
    blueDelta = (g_Palette_BlendRatio * (*(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *targetPixels + 2) - srcBlue)) >> 8;
    if ( blueDelta < 0 )
      totalDelta = deltaSum - blueDelta;
    else
      totalDelta = blueDelta + deltaSum;
    if ( totalDelta > 0x14 )
      outPixel = g_Rgb15ToPaletteLut[128 * (blendedRed & 0xF8) + 4 * (blendedGreen & 0xF8) + ((unsigned int)(srcBlue + blueDelta) >> 3)];
    else
      outPixel = *srcPixels;
    *destPixels = outPixel;
    ++srcPixels;
    ++targetPixels;
    ++destPixels;
    remaining = v15 - 1;
  }
  while ( v15 != 1 );
  return v16;
}
// 4629F6: variable 'v16' is possibly undefined
// 519A10: using guessed type int dword_519A10;
// 519A14: using guessed type int dword_519A14;

//----- (00462B0B) --------------------------------------------------------
int __cdecl Palette_OffsetIndexedPixelsRGB(unsigned __int8 *pixels, int count, int redOffset, int greenOffset, int blueOffset)
{
  int remaining; // ecx
  int red; // edx
  int green; // edx
  int blue; // edx
  int v11; // [esp-14h] [ebp-2Ch]
  int v12; // [esp+4h] [ebp-14h]
  char clampedGreen; // [esp+10h] [ebp-8h]
  char clampedRed; // [esp+14h] [ebp-4h]

  if ( !count )
    return v12;
  remaining = count;
  do
  {
    v11 = remaining;
    red = redOffset + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *pixels);
    if ( red < 0 )
      red = 0;
    if ( (unsigned int)red > 0xFF )
      LOBYTE(red) = -1;
    clampedRed = red;
    green = greenOffset + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *pixels + 1);
    if ( green < 0 )
      green = 0;
    if ( (unsigned int)green > 0xFF )
      LOBYTE(green) = -1;
    clampedGreen = green;
    blue = blueOffset + *(unsigned __int8 *)(g_Palette_ActivePalettePtr + 4 * *pixels + 2);
    if ( blue < 0 )
      blue = 0;
    if ( (unsigned int)blue > 0xFF )
      blue = 255;
    *pixels++ = g_Rgb15ToPaletteLut[128 * (clampedRed & 0xF8) + 4 * (clampedGreen & 0xF8) + ((unsigned int)blue >> 3)];
    --remaining;
  }
  while ( v11 != 1 );
  return v12;
}
// 462B20: variable 'v12' is possibly undefined
// 519A10: using guessed type int dword_519A10;

//----- (00462BE0) --------------------------------------------------------
_DWORD * IO_StreamAdapterConstruct(_DWORD *result, int aviPlayer)
{
  *result = g_IOStreamAdapter_Vtable;
  result[1] = aviPlayer;
  return result;
}
// 50F364: using guessed type int (*off_50F364[4])();

//----- (00462BF0) --------------------------------------------------------
_DWORD * IO_StreamAdapterRelease(_DWORD *adapter, char freeFlags)
{
  _DWORD *v3; // ecx
  int v5; // ecx

  v3 = adapter;
  if ( (freeFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(adapter, &g_IOStreamAdapter_DtorArrayTag);
    j_j__nfree_();
    return (_DWORD *)v5;
  }
  else
  {
    *adapter = g_IOStreamAdapter_Vtable;
    if ( (freeFlags & 2) != 0 )
      j__nfree_();
    return v3;
  }
}
// 462C51: variable 'v3' is possibly undefined
// 462C7A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50F364: using guessed type int (*off_50F364[4])();

//----- (00462C90) --------------------------------------------------------
int  IO_StreamAdapterReadBytes(int adapter, int destBuffer, signed int bytesRequested)
{
  int v3; // eax
  int player; // ebp
  signed int chunkSize; // edx
  unsigned int frameBytesLeft; // eax
  int v9; // [esp+4h] [ebp-18h]
  int totalRead; // [esp+8h] [ebp-14h]

  v3 = *(_DWORD *)(adapter + 4);
  player = v3;
  totalRead = 0;
  if ( bytesRequested )
  {
    v9 = v3 + 219;
    do
    {
      if ( !*(_DWORD *)(player + 383) )
      {
        frameBytesLeft = AviPlayer_PopBufferedAudioData(player, *(void **)(player + 379));
        *(_DWORD *)(player + 383) = frameBytesLeft;
        if ( !frameBytesLeft )
          break;
      }
      chunkSize = *(_DWORD *)(player + 383);
      if ( bytesRequested < chunkSize )
        chunkSize = bytesRequested;
      qmemcpy(
        (void *)(totalRead + destBuffer),
        (const void *)(*(_DWORD *)(v9 + 40) - *(_DWORD *)(player + 383) + *(_DWORD *)(player + 379)),
        chunkSize);
      totalRead += chunkSize;
      *(_DWORD *)(player + 383) -= chunkSize;
      bytesRequested -= chunkSize;
    }
    while ( bytesRequested );
  }
  return totalRead;
}

//----- (00462CA0) --------------------------------------------------------
BOOL  IO_StreamAdapterIsAtEnd(int adapter)
{
  return *(_BYTE *)(*(_DWORD *)(adapter + 4) + 1) != 0;
}

//----- (00462CB0) --------------------------------------------------------
int  IO_StreamAdapterInvokeAtEnd(int adapter)
{
  return (*(int (**)(void))(*(_DWORD *)adapter + 4))();
}

//----- (00462CC0) --------------------------------------------------------
int IO_StreamAdapterReadStub(void)
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
int  ExcString_ConstructEmpty(_DWORD *excStr)
{
  int v2; // ecx

  *excStr = 0;
  excStr[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(excStr);
  return v2;
}
// 462D17: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();

//----- (00462D20) --------------------------------------------------------
int  ExcString_ReleaseText(_DWORD *excStr)
{
  int v1; // ecx

  Compat_StringHolderDestructor(excStr);
  return v1;
}
// 462D28: variable 'v1' is possibly undefined

//----- (00462D30) --------------------------------------------------------
int  ExcString_GetTextPtr(int excStr)
{
  return *(_DWORD *)excStr;
}

//----- (00462D40) --------------------------------------------------------
int  ExcString_GetTextPtrDup(int excStr)
{
  return *(_DWORD *)excStr;
}

//----- (00462D50) --------------------------------------------------------
int  ExcString_ReleaseTextDup(_DWORD *excStr)
{
  int v1; // ecx

  Compat_StringHolderDestructor(excStr);
  return v1;
}
// 462D58: variable 'v1' is possibly undefined

//----- (00462D60) --------------------------------------------------------
int ExcString_GetErrorCodeStub(void)
{
  return 0;
}

//----- (00462D80) --------------------------------------------------------
int ExcString_GetErrorCodeStubDup(void)
{
  return 0;
}

//----- (00462E40) --------------------------------------------------------
int  CAviDecompressor_ConvertRGB888to565Row(_WORD *dest, _DWORD *src, int pixelCount)
{
  int pixel565; // ebx
  unsigned __int64 v7; // rt0
  int result; // eax

  pixel565 = 0;
  do
  {
    HIDWORD(v7) = pixel565;
    LODWORD(v7) = *src;
    HIDWORD(v7) = v7 >> 19;
    LODWORD(v7) = *src << 16;
    HIDWORD(v7) = v7 >> 26;
    LODWORD(v7) = *src << 24;
    pixel565 = v7 >> 27;
    result = pixel565;
    src = (_DWORD *)((char *)src + 3);
    *dest++ = pixel565;
    --pixelCount;
  }
  while ( pixelCount );
  return result;
}

//----- (00462EA0) --------------------------------------------------------
unsigned int  CAviDecompressor_ConvertRGB565to888Row(unsigned int *result, _WORD *src, int pixelCount)
{
  unsigned int pixel888; // ebx
  unsigned int pixel565; // eax
  unsigned int v8; // ebx
  unsigned int v9; // eax
  unsigned __int64 v10; // rt0

  pixel888 = 0;
  HIWORD(pixel565) = 0;
  do
  {
    LOWORD(pixel565) = *src;
    v8 = __PAIR64__(pixel888, pixel565) >> 8;
    v9 = pixel565 << 21;
    HIDWORD(v10) = __PAIR64__(v8, v9) >> 24;
    LODWORD(v10) = v9 << 6;
    pixel888 = v10 >> 24;
    pixel565 = 0;
    ++src;
    *result = pixel888;
    result = (unsigned int *)((char *)result + 3);
    --pixelCount;
  }
  while ( pixelCount );
  return pixel565;
}

//----- (00462FE0) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow16bpp(void *dest, const void *src, int pixelCount)
{
  int result; // eax

  result = 2 * pixelCount;
  qmemcpy(dest, src, 2 * pixelCount);
  return result;
}

//----- (00463010) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow24bpp(void *dest, const void *src, int pixelCount)
{
  int result; // eax

  result = 3 * pixelCount;
  qmemcpy(dest, src, 3 * pixelCount);
  return result;
}

//----- (00463040) --------------------------------------------------------
int  CAviDecompressor_CopyPixelRow32bpp(void *dest, const void *src, int pixelCount)
{
  int result; // eax

  result = 4 * pixelCount;
  qmemcpy(dest, src, 4 * ((unsigned int)(4 * pixelCount) >> 2));
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
