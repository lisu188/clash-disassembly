#include "platform_sdl.h"

#include <stdint.h>
#include <string.h>

/*
 * Asm-backed bootstrap for the missing early startup slice:
 *   start -> sub_486369 -> _WinMain@16
 *
 * This executable path stays inside recovered game code instead of opening a
 * dummy window. The broader CRT/bootstrap band is still unresolved, so this
 * file rebuilds the recoverable WinMain logic first and relies on section GC
 * to keep unrelated unresolved helpers out of the initial link surface.
 */

extern int dword_51D020;
extern int dword_51D018;
extern int dword_51D01C;
extern int dword_511134;
extern int g_AppIsActive;
extern int dword_5188B0;
extern int dword_5202E0;
extern int logEnabled;
extern HWND hWnd;
extern unsigned int dword_544CD8[9];
extern unsigned char unk_51D4C0;
extern LRESULT __thiscall Platform_MainWindowProc(void *this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int dword_51D014;
int dword_543CA0;
int (*g_RenderHook)(int a1, char a2, DWORD a3);

char __thiscall DetectGameCDPath(void *this);
int __thiscall sub_442AD0(int this);
int Game_Init(int a1, char a2, DWORD a3);
void createLogFiles(int a1, int a2, DWORD a3);
signed int sub_451E46(void);
int sub_472860(int a1, int a2, int a3);
int nullsub_4(void);
int Render_SetPixelFormat(int a1, int a2, int a3, DWORD a4);
int sub_460490(int a1, int a2, char a3, DWORD a4);
int Render_CreateSprite(void);
void lodaOptionsCfg(DWORD a1);
void initRandomSeed(char a1, DWORD a2);
unsigned int WorldMap_Initialize(char a1, DWORD a2);
signed int sub_44C400(DWORD a1, double a2);
signed int sub_44C410(int a1);
int PlayGame(int a1, char a2, DWORD a3, char a4, double a5, ...);
int PlayGame_Dispatch(int a1, signed int a2, char *a3, double a4);
int App_Shutdown(void);
HWND Platform_CreateMainWindow(HINSTANCE a1, int a2);
BOOL Platform_IsWindowsNt4(void);
BOOL Platform_IsWindows9x(void);
int __stdcall CSS_SetDirectSoundHWnd(int a1);
int __stdcall CSS_SetDeviceSearch(int a1);
signed int __stdcall CSS_Init(int a1, int a2, int a3, int a4);
void Video_Avi_playIn(const char *a1, int a2, int a3, int a4, int a5, int a6);

int _no_support_loaded(void)
{
  return 0;
}

int j___NTAddFileHandle_(void)
{
  return 0;
}

static char g_boot_command_line[1024];

static void Bootstrap_BuildCommandLineFromArgv(int argc, char **argv)
{
  int arg_index;
  size_t write_index;

  g_boot_command_line[0] = 0;
  if ( argc <= 1 )
    return;

  write_index = 0;
  for ( arg_index = 1; arg_index < argc && write_index + 1 < sizeof(g_boot_command_line); ++arg_index )
  {
    const char *argument;

    if ( arg_index > 1 )
      g_boot_command_line[write_index++] = ' ';
    argument = argv[arg_index];
    while ( *argument && write_index + 1 < sizeof(g_boot_command_line) )
      g_boot_command_line[write_index++] = *argument++;
  }
  g_boot_command_line[write_index] = 0;
}

static int Bootstrap_ParseIntroMissionIndex(const char *command_line)
{
  int mission_base;
  int mission_digit;

  mission_base = 0;
  if ( command_line[1] == 'a' )
    mission_base = 10;
  mission_digit = (unsigned char)command_line[2] - '0';
  return mission_base + mission_digit;
}

static int App_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCommandLine, int nShowCmd)
{
  char command_mode;
  int device_search_mode;

  (void)hPrevInstance;
  (void)nShowCmd;

  dword_51D020 = (int)(intptr_t)lpCommandLine;
  command_mode = lpCommandLine && *lpCommandLine ? *lpCommandLine : 0;
  if ( !Platform_CreateMainWindow(hInstance, command_mode) )
    return 0;

  dword_51D018 = Platform_IsWindowsNt4();
  if ( !Platform_IsWindows9x() )
    (void)Platform_IsWindowsNt4();

  CSS_SetDirectSoundHWnd((int)(intptr_t)hWnd);
  DetectGameCDPath(0);
  sub_442AD0(0);
  Game_Init(0, command_mode, 0);

  logEnabled = 1;
  device_search_mode = 0;
  if ( command_mode == 'g' || command_mode == 'G' )
  {
    if ( lpCommandLine[1] == '1' )
      device_search_mode = 1;
    if ( lpCommandLine[1] == '2' )
      device_search_mode = 2;
  }

  CSS_SetDeviceSearch(device_search_mode);
  sub_472860(-1, 0, 0);
  CSS_Init(6, 0xC0, 0xFA0, 0x9C4);
  dword_543CA0 = 1;
  createLogFiles(0, 0, 0);
  sub_451E46();
  sub_472860(-1, 0, 0);
  nullsub_4();
  Render_SetPixelFormat((int)(intptr_t)&unk_51D4C0, (int)(intptr_t)hWnd, 16, 0);
  sub_460490((int)(intptr_t)dword_544CD8, 0, command_mode, 0);
  Render_CreateSprite();
  lodaOptionsCfg(0);
  initRandomSeed(command_mode, 0);

  if ( command_mode == 'r' )
    dword_51D014 = 1;

  if ( command_mode == 'a' )
  {
    WorldMap_Initialize(command_mode, 0);
    sub_44C400(0, 0.0);
    PlayGame(0, command_mode, 0, 0, 0.0);
  }
  else
  {
    if ( lpCommandLine[0] && (lpCommandLine[1] == 'A' || lpCommandLine[1] == 'a') && lpCommandLine[2] )
      dword_51D01C = 1;
    else
      dword_51D01C = 0;

    if ( !lpCommandLine[0] || (lpCommandLine[1] != 'n' && lpCommandLine[1] != 'N') )
      dword_511134 = 1;
    else
      dword_511134 = 0;

    if ( dword_51D01C )
    {
      Video_Avi_playIn("logo", 0, 0, 1, 1, 1);
      WorldMap_Initialize(0, 0);
      sub_44C410(Bootstrap_ParseIntroMissionIndex(lpCommandLine));
      dword_5188B0 = 0;
      PlayGame(0, 0, 0, 0, 0.0);
    }
    else
    {
      PlayGame_Dispatch(0, command_mode, 0, 0.0);
    }
  }

  /*
   * The original boot slice invokes an object cleanup callback hanging off
   * dword_5202E0 before App_Shutdown(). That callback is still usercall/vtable
   * shaped and not yet safe to re-emit under the current host ABI, so the
   * bootstrap currently stops at the surrounding high-confidence shutdown.
   */
  (void)dword_5202E0;
  App_Shutdown();
  return 0;
}

static LRESULT __stdcall Bootstrap_SmokeWindowProc(HWND hWndValue, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  (void)lParam;

  /*
   * Keep the first executable milestone on a narrow, asm-backed Win32 message
   * subset. Rooting Platform_MainWindowProc already drags the unresolved
   * render/runtime band, so this smoke proc preserves the authentic message
   * shapes that matter for startup without claiming the full boot path is
   * rebuilt yet.
   */
  if ( Msg == 2 )
  {
    PostQuitMessage(0);
    return 0;
  }
  if ( Msg == 0xF )
  {
    ValidateRect(hWndValue, 0);
    return 0;
  }
  if ( Msg == 28 )
  {
    g_AppIsActive = (unsigned __int16)wParam;
    return 0;
  }
  return DefWindowProcA(hWndValue, Msg, wParam, lParam);
}

static int Bootstrap_RunWindowSmokeLoop(void)
{
  HINSTANCE instance;
  HWND window;
  WNDCLASSA wndclass;
  MSG message;

  instance = GetModuleHandleA(0);
  dword_51D020 = (int)(intptr_t)g_boot_command_line;
  memset(&wndclass, 0, sizeof(wndclass));
  wndclass.hInstance = instance;
  wndclass.style = 3;
  wndclass.lpfnWndProc = Bootstrap_SmokeWindowProc;
  wndclass.hIcon = LoadIconA(instance, (LPCSTR)0x64);
  wndclass.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
  wndclass.hbrBackground = (HBRUSH)GetStockObject(4);
  wndclass.lpszClassName = "Clash";
  RegisterClassA(&wndclass);
  window = CreateWindowExA(0, "Clash", "Clash", 0x80000000u, 0, 0, 640, 480, 0, 0, instance, 0);
  hWnd = window;
  if ( !window )
    return 1;
  ShowWindow(window, 3);
  UpdateWindow(window);
  while ( GetMessageA(&message, 0, 0, 0) )
  {
    TranslateMessage(&message);
    DispatchMessageA(&message);
  }
  return (int)message.wParam;
}

int main(int argc, char **argv)
{
  Bootstrap_BuildCommandLineFromArgv(argc, argv);
  /*
   * Keep the recovered WinMain slice compiled in-tree, but stop the default
   * executable at the narrower SDL window/message-loop milestone until the
   * larger boot/menu render surface links cleanly.
   */
  (void)g_boot_command_line;
  return Bootstrap_RunWindowSmokeLoop();
}
