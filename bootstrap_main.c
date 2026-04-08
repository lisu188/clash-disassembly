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
extern int dword_5188C0;
extern int dword_5202E0;
extern int dword_543D74;
extern int dword_543D78;
extern int dword_544180;
extern int dword_545150;
extern int logEnabled;
extern HWND hWnd;
extern unsigned int dword_544CD8[9];
extern unsigned char g_LanguageIndex;
extern unsigned char byte_543D80[1024];
extern unsigned char g_MainMenuButtonWidgetsTemplate;
extern unsigned char unk_5196A0;
extern unsigned char unk_51D4C0;
extern void *g_RenderDevice;
extern LRESULT __thiscall Platform_MainWindowProc(void *this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int dword_51D014;
int dword_543CA0;
int (*g_RenderHook)(int a1, char a2, DWORD a3);

char __thiscall DetectGameCDPath(void *this);
int __thiscall sub_442AD0(int this);
int sub_442760(int a1, char a2, DWORD a3);
int Game_Init(int a1, char a2, DWORD a3);
void createLogFiles(int a1, int a2, DWORD a3);
signed int sub_451E46(void);
int sub_472860(int a1, int a2, int a3);
int nullsub_4(void);
int sub_401A40(void);
int Render_DefaultRH(int a1, char a2, DWORD a3);
int Render_SetPixelFormat(int a1, int a2, int a3, DWORD a4);
int Render_SetResourceHandle(int a1, int a2);
int sub_460490(int a1, int a2, char a3, DWORD a4);
int Render_CreateSprite(void);
DWORD UI_StartAnims(int a1, char a2, DWORD a3);
void *Render_CreateSurface(int a1, short a2, short a3);
int DD_Pump(int a1, int a2, ...);
void *Mem_Alloc(int a1, int a2, char a3, DWORD a4);
void *DLXSpriteSet_Load(void *a1, const void *a2);
int sub_435ED0(char *a1, int a2, int a3, DWORD a4);
int sub_441670(char *a1, int a2);
int sub_404D90(int *a1);
int *sub_405020(int *result, unsigned char *a2, signed int a3);
void *sub_419D80(void *result);
signed int sub_419DC0(unsigned int *a1, DWORD a2);
void *sub_460CB0(int a1, int a2, int a3, DWORD a4);
short sub_460D80(int a1, int a2);
int Render_Present(int a1);
void lodaOptionsCfg(DWORD a1);
void initRandomSeed(char a1, DWORD a2);
unsigned int WorldMap_Initialize(char a1, DWORD a2);
signed int sub_44C400(DWORD a1, double a2);
signed int sub_44C410(int a1);
int PlayGame(int a1, char a2, DWORD a3, char a4, double a5, ...);
int PlayGame_Dispatch(int a1, signed int a2, char *a3, double a4);
int App_Shutdown(void);
HWND Platform_CreateMainWindow(HINSTANCE a1, int a2);
BOOL Input_MousePresent(void);
BOOL Input_MouseAcquire(void);
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
static int g_boot_run_startup_prelude;
static int g_boot_run_video_init_probe;
static int g_boot_run_menu_probe;

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

    if ( !strcmp(argv[arg_index], "--authentic-startup-prelude") )
    {
      g_boot_run_startup_prelude = 1;
      continue;
    }
    if ( !strcmp(argv[arg_index], "--authentic-video-init") )
    {
      g_boot_run_startup_prelude = 1;
      g_boot_run_video_init_probe = 1;
      continue;
    }
    if ( !strcmp(argv[arg_index], "--authentic-menu-probe") )
    {
      g_boot_run_startup_prelude = 1;
      g_boot_run_menu_probe = 1;
      continue;
    }
    if ( write_index > 0 )
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

static int Bootstrap_RunRecoveredStartupPrelude(HINSTANCE hInstance, LPSTR lpCommandLine, char *command_mode_out)
{
  char command_mode;

  dword_51D020 = (int)(intptr_t)lpCommandLine;
  command_mode = lpCommandLine && *lpCommandLine ? *lpCommandLine : 0;
  if ( command_mode_out )
    *command_mode_out = command_mode;
  if ( !Platform_CreateMainWindow(hInstance, command_mode) )
    return 0;

  dword_51D018 = Input_MousePresent();
  if ( !Input_MouseAcquire() )
    (void)Input_MousePresent();

  CSS_SetDirectSoundHWnd((int)(intptr_t)hWnd);
  DetectGameCDPath(0);
  sub_442AD0(0);
  Game_Init(0, command_mode, 0);
  return 1;
}

static void Bootstrap_RunRecoveredRuntimeAndRenderInit(char command_mode, LPSTR lpCommandLine)
{
  int device_search_mode;

  logEnabled = 1;
  /*
   * The original binary reaches this render-object constructor through the
   * static-init band before the video bootstrap starts. Until that `_wcpp_*`
   * path is reconstructed end-to-end, call the recovered helper explicitly so
   * `unk_51D4C0` and its palette/resource backing state are initialized before
   * `Render_SetPixelFormat`.
   */
  sub_401A40();
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
}

static int Bootstrap_RunRecoveredEarlyStartupPrelude(HINSTANCE hInstance, LPSTR lpCommandLine, char *command_mode_out)
{
  char command_mode;

  dword_51D020 = (int)(intptr_t)lpCommandLine;
  command_mode = lpCommandLine && *lpCommandLine ? *lpCommandLine : 0;
  if ( command_mode_out )
    *command_mode_out = command_mode;
  if ( !Platform_CreateMainWindow(hInstance, command_mode) )
    return 0;

  /*
   * This is the smallest authentic `_WinMain@16` slice we can currently root
   * without immediately dragging the deeper rules/render/menu surface back into
   * the executable link. Keep it limited to real window/input/CD/game-state
   * bootstrap until the next runtime/helper wave is rebuilt.
   */
  dword_51D018 = Input_MousePresent();
  if ( !Input_MouseAcquire() )
    (void)Input_MousePresent();
  CSS_SetDirectSoundHWnd((int)(intptr_t)hWnd);
  sub_442760(0, 0, 0);
  DetectGameCDPath(0);
  sub_442AD0(0);
  Game_Init(0, command_mode, 0);
  if ( command_mode == 'r' )
    dword_51D014 = 1;
  return 1;
}

static void Bootstrap_RunRecoveredVideoInitProbe(char command_mode)
{
  dword_543CA0 = 1;
  sub_401A40();
  nullsub_4();
  Render_SetPixelFormat((int)(intptr_t)&unk_51D4C0, (int)(intptr_t)hWnd, 16, 0);
  sub_460490((int)(intptr_t)dword_544CD8, 0, command_mode, 0);
  Render_CreateSprite();
}

static void Bootstrap_RunRecoveredMainMenuFirstFrameProbe(char command_mode)
{
  unsigned char menu_widgets[372];
  unsigned int widget_offset;
  void *surface;
  uintptr_t surface_renderer;

  surface = Mem_Alloc(188, 0, command_mode, 0);
  if ( surface )
    surface = Render_CreateSurface((int)(intptr_t)surface, 640, 480);
  dword_5202E0 = (int)(intptr_t)surface;

  UI_StartAnims(0, command_mode, 0);
  Render_SetResourceHandle((int)(intptr_t)&unk_51D4C0, 1);
  g_RenderHook = Render_DefaultRH;
  DD_Pump((int)(intptr_t)dword_544CD8, 1);

  surface = Mem_Alloc(0x1010, 0, command_mode, 0);
  if ( surface )
    surface = DLXSpriteSet_Load(surface, "menu\\main.s32");
  dword_543D74 = (int)(intptr_t)surface;

  surface_renderer = *(uintptr_t *)(uintptr_t)(unsigned int)(dword_5202E0 + 184);
  (*(void (__fastcall **)(int, const char *))(uintptr_t)(*(uintptr_t *)(surface_renderer + 48)))(0, "menu\\main.gfx");
  sub_435ED0("menu\\main", (int)(intptr_t)byte_543D80, 0, 0);
  if ( dword_5188C0 )
    dword_544180 = sub_441670("music\\menu", 64);

  DD_Pump((int)(intptr_t)dword_544CD8, 0);
  (*(void (**)(void))(uintptr_t)(*(uintptr_t *)(surface_renderer + 36)))();
  (*(void (__thiscall **)(int))(uintptr_t)(*(uintptr_t *)(surface_renderer + 36)))(92);

  memcpy(menu_widgets, &g_MainMenuButtonWidgetsTemplate, sizeof(menu_widgets));
  for ( widget_offset = 0; widget_offset < sizeof(menu_widgets); widget_offset += 0x35 )
  {
    *(uint32_t *)(void *)(menu_widgets + widget_offset + 0x10) += (unsigned char)g_LanguageIndex;
    *(uint32_t *)(void *)(menu_widgets + widget_offset + 0x21) += (unsigned char)g_LanguageIndex;
  }

  g_RenderDevice = &unk_51D4C0;
  sub_419D80(menu_widgets);
  sub_405020((int *)&unk_51D4C0, byte_543D80, 60);
  dword_543D78 = 0;
  sub_460CB0((int)(intptr_t)dword_544CD8, (int)(intptr_t)byte_543D80, 0, 0);
  sub_460D80((int)(intptr_t)dword_544CD8, (int)(intptr_t)&unk_5196A0);
  dword_545150 = (int)(intptr_t)&unk_5196A0;
  Render_Present((int)(intptr_t)dword_544CD8);

  while ( !dword_543D78 )
  {
    DD_Pump((int)(intptr_t)dword_544CD8, 0);
    sub_419DC0((unsigned int *)menu_widgets, 0);
  }
}

static void Bootstrap_RunRecoveredGameEntry(char command_mode, LPSTR lpCommandLine)
{
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
}

static int App_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCommandLine, int nShowCmd)
{
  char command_mode;

  (void)hPrevInstance;
  (void)nShowCmd;

  if ( !Bootstrap_RunRecoveredStartupPrelude(hInstance, lpCommandLine, &command_mode) )
    return 0;
  Bootstrap_RunRecoveredRuntimeAndRenderInit(command_mode, lpCommandLine);
  Bootstrap_RunRecoveredGameEntry(command_mode, lpCommandLine);

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

static int Bootstrap_RunMessageLoop(void)
{
  MSG message;
  while ( GetMessageA(&message, 0, 0, 0) )
  {
    TranslateMessage(&message);
    DispatchMessageA(&message);
  }
  return (int)message.wParam;
}

static int Bootstrap_RunPlatformWindowLoop(void)
{
  dword_51D020 = (int)(intptr_t)g_boot_command_line;
  if ( !Platform_CreateMainWindow(GetModuleHandleA(0), g_boot_command_line[0]) )
    return 1;
  return Bootstrap_RunMessageLoop();
}

int main(int argc, char **argv)
{
  Bootstrap_BuildCommandLineFromArgv(argc, argv);
  /*
   * Keep the deeper menu/game-entry branch out of the default link surface
   * until its runtime/data dependencies are rebuilt. The explicit prelude
   * probe lets us root the recoverable startup slice without dragging the
   * whole menu/world path back in.
   */
  if ( g_boot_run_startup_prelude )
  {
    char command_mode;

    if ( !Bootstrap_RunRecoveredEarlyStartupPrelude(GetModuleHandleA(0), g_boot_command_line, &command_mode) )
      return 1;
    if ( g_boot_run_video_init_probe )
      Bootstrap_RunRecoveredVideoInitProbe(command_mode);
    if ( g_boot_run_menu_probe )
    {
      Bootstrap_RunRecoveredVideoInitProbe(command_mode);
      Bootstrap_RunRecoveredMainMenuFirstFrameProbe(command_mode);
      return Bootstrap_RunMessageLoop();
    }
    (void)command_mode;
    return Bootstrap_RunMessageLoop();
  }
  return Bootstrap_RunPlatformWindowLoop();
}
