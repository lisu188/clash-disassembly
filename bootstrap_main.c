#include "platform_sdl.h"

#include <stdio.h>
#include <stdlib.h>
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
extern int g_PlayGameMenuSpriteSetHandle;
extern int g_PlayGameMenuExitRequested;
extern int g_MainMenuRequestedScreen;
extern int g_MainMenuMusicHandle;
extern int dword_544190;
extern int dword_5441E0;
extern int dword_545150;
extern int dword_54DBA8;
extern int logEnabled;
extern HWND hWnd;
extern unsigned int dword_544CD8[286];
extern unsigned char g_LanguageIndex;
extern unsigned char byte_54512C;
extern unsigned char byte_543D80[1024];
extern unsigned char g_MainMenuButtonWidgetsTemplate[371];
extern unsigned char g_LoadMenuButtonWidgetsTemplate[159];
extern unsigned char unk_5196A0;
extern unsigned char unk_51D4C0;
extern void *g_RenderDevice;
extern LRESULT __thiscall Platform_MainWindowProc(void *this, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

#define dword_544CFC (*((int *)&dword_544CD8[9]))
#define dword_544D00 (*((int *)&dword_544CD8[10]))

typedef struct BootstrapProbeInputBackendState
{
  unsigned int direct_input;
  unsigned int keyboard_device;
  unsigned int mouse_device;
  unsigned int joystick_device;
  int mouse_delta_x;
  int mouse_delta_y;
  int joystick_axis_x;
  int joystick_axis_y;
  int joystick_button_primary;
  int joystick_button_secondary;
  int mouse_button_primary;
  int mouse_button_middle;
  int mouse_button_secondary;
  char keyboard_state[256];
  int mouse_device_ready;
  int keyboard_device_ready;
  int joystick_device_ready;
} BootstrapProbeInputBackendState;

extern BootstrapProbeInputBackendState g_InputBackendState;

int dword_51D014;
int dword_543CA0;
int (*g_RenderHook)(int a1, char a2, DWORD a3);
int g_BootstrapSkipIntroAviPlayback;

char __thiscall DetectGameCDPath(void *this);
int __thiscall sub_442AD0(int this);
int sub_442760(int a1, char a2, DWORD a3);
int Game_Init(int a1, char a2, DWORD a3);
void createLogFiles(int a1, int a2, DWORD a3);
signed int sub_451E46(void);
int __fastcall sub_4725B0(int a1, int a2);
int sub_472860(int a1, int a2, int a3);
int nullsub_4(void);
int sub_401A40(void);
int Render_DefaultRH(int a1, char a2, DWORD a3);
int Render_SetPixelFormat(int a1, int a2, int a3, DWORD a4);
int Render_SetResourceHandle(int a1, int a2);
int Render_LoadPCXImage(int a1, char *a2, int a3, int a4);
void Render_LoadResourceSprite_v4(int a1, unsigned char *a2, int a3, char a4, DWORD a5);
int sub_401E30(unsigned int *a1);
void *Device_GetParamA(int a1, int a2);
int sub_460490(int a1, int a2, char a3, DWORD a4);
int Render_CreateSprite(void);
int Render_Pump(void);
DWORD UI_StartAnims(int a1, char a2, DWORD a3);
void *Render_CreateSurface(int a1, short a2, short a3);
int DD_Pump(int a1, int a2, ...);
BOOL DD_IsFlipping(int a1);
void *Mem_Alloc(int a1, int a2, char a3, DWORD a4);
int Compat_AllocLow32Bytes(int size);
void Compat_FreeLow32Bytes(int ptr);
short DLX_GetSpriteWidth(int a1, unsigned short a2);
short DLX_GetSpriteHeight(int a1, unsigned short a2);
void *DLXSpriteSet_Load(void *a1, const void *a2);
int sub_435ED0(char *a1, int a2, int a3, DWORD a4);
int sub_441670(char *a1, int a2);
int sub_404D90(int *a1);
int *sub_405020(int *result, unsigned char *a2, signed int a3);
int sub_405920(int *a1);
void MainMenu_RebuildButtonWidgetTemplate(void);
void LoadMenu_RebuildButtonWidgetTemplate(void);
void *sub_419D80(void *result);
signed int sub_419DC0(unsigned int *a1, DWORD a2);
void *sub_460CB0(int a1, int a2, int a3, DWORD a4);
short sub_460D80(int a1, int a2);
BOOL sub_460950(int a1);
int Render_Present(int a1);
int sub_44A110(int a1, DWORD a2);
void *sub_44A140(int a1, DWORD a2);
int sub_404F20(int *a1, int a2);
void lodaOptionsCfg(DWORD a1);
void initRandomSeed(char a1, DWORD a2);
int *sub_482260(void);
signed int sub_491B10(void);
unsigned int WorldMap_Initialize(char a1, DWORD a2);
signed int sub_444490(int a1, DWORD a2, double a3);
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
int __stdcall CSS_StopSound(int a1, int a2);
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
static int g_boot_run_platform_window_only;
static int g_boot_run_startup_prelude;
static int g_boot_run_video_init_probe;
static int g_boot_run_menu_probe;
static int g_boot_trace_menu_probe_checked;
static int g_boot_trace_menu_probe_enabled;
static int g_boot_menu_probe_auto_click_checked;
static int g_boot_menu_probe_auto_click_index = -1;
static int g_boot_load_menu_probe_auto_click_checked;
static int g_boot_load_menu_probe_auto_click_index = -1;
static int g_boot_load_menu_probe_auto_slot_checked;
static int g_boot_load_menu_probe_auto_slot_index = -1;
static int g_boot_load_menu_probe_post_confirm_checked;
static int g_boot_load_menu_probe_post_confirm_enabled;
static int g_boot_load_menu_probe_broader_rules_checked;
static int g_boot_load_menu_probe_broader_rules_enabled;

static void Bootstrap_RunRecoveredLoadGameMenuProbe(char command_mode);

static void Bootstrap_TraceMenuProbe(const char *step)
{
  if ( !g_boot_trace_menu_probe_checked )
  {
    g_boot_trace_menu_probe_enabled = getenv("CLASH95_TRACE_MENU_PROBE") != 0;
    g_boot_trace_menu_probe_checked = 1;
  }
  if ( g_boot_trace_menu_probe_enabled )
  {
    fprintf(stderr, "[menu-probe] %s\n", step);
    fflush(stderr);
  }
}

static int Bootstrap_GetMenuProbeAutoClickIndex(void)
{
  const char *env_value;
  char *parse_end;
  long parsed_value;

  if ( g_boot_menu_probe_auto_click_checked )
    return g_boot_menu_probe_auto_click_index;

  g_boot_menu_probe_auto_click_checked = 1;
  env_value = getenv("CLASH95_MENU_PROBE_AUTO_CLICK");
  if ( !env_value || !*env_value )
    return g_boot_menu_probe_auto_click_index;

  if ( !strcmp(env_value, "load") || !strcmp(env_value, "load-game") )
    g_boot_menu_probe_auto_click_index = 0;
  else if ( !strcmp(env_value, "campaign") )
    g_boot_menu_probe_auto_click_index = 1;
  else if ( !strcmp(env_value, "exit") )
    g_boot_menu_probe_auto_click_index = 2;
  else if ( !strcmp(env_value, "options") )
    g_boot_menu_probe_auto_click_index = 3;
  else if ( !strcmp(env_value, "multiplayer") )
    g_boot_menu_probe_auto_click_index = 4;
  else if ( !strcmp(env_value, "credits") )
    g_boot_menu_probe_auto_click_index = 5;
  else
  {
    parsed_value = strtol(env_value, &parse_end, 10);
    if ( parse_end != env_value && !*parse_end && parsed_value >= 0 && parsed_value <= 5 )
      g_boot_menu_probe_auto_click_index = (int)parsed_value;
  }
  return g_boot_menu_probe_auto_click_index;
}

static int Bootstrap_GetLoadMenuProbeAutoClickIndex(void)
{
  const char *env_value;
  char *parse_end;
  long parsed_value;

  if ( g_boot_load_menu_probe_auto_click_checked )
    return g_boot_load_menu_probe_auto_click_index;

  g_boot_load_menu_probe_auto_click_checked = 1;
  env_value = getenv("CLASH95_LOAD_MENU_PROBE_AUTO_CLICK");
  if ( !env_value || !*env_value )
    return g_boot_load_menu_probe_auto_click_index;

  if ( !strcmp(env_value, "load") || !strcmp(env_value, "confirm") || !strcmp(env_value, "select") )
    g_boot_load_menu_probe_auto_click_index = 0;
  else if ( !strcmp(env_value, "back") || !strcmp(env_value, "cancel") || !strcmp(env_value, "return") )
    g_boot_load_menu_probe_auto_click_index = 1;
  else
  {
    parsed_value = strtol(env_value, &parse_end, 10);
    if ( parse_end != env_value && !*parse_end && parsed_value >= 0 && parsed_value <= 1 )
      g_boot_load_menu_probe_auto_click_index = (int)parsed_value;
  }
  return g_boot_load_menu_probe_auto_click_index;
}

static int Bootstrap_GetLoadMenuProbeAutoSlotIndex(void)
{
  const char *env_value;
  char *parse_end;
  long parsed_value;

  if ( g_boot_load_menu_probe_auto_slot_checked )
    return g_boot_load_menu_probe_auto_slot_index;

  g_boot_load_menu_probe_auto_slot_checked = 1;
  env_value = getenv("CLASH95_LOAD_MENU_PROBE_AUTO_SLOT");
  if ( !env_value || !*env_value )
    return g_boot_load_menu_probe_auto_slot_index;

  if ( !strcmp(env_value, "first") )
    g_boot_load_menu_probe_auto_slot_index = 0;
  else
  {
    parsed_value = strtol(env_value, &parse_end, 10);
    if ( parse_end != env_value && !*parse_end && parsed_value >= 0 && parsed_value <= 9 )
      g_boot_load_menu_probe_auto_slot_index = (int)parsed_value;
  }
  return g_boot_load_menu_probe_auto_slot_index;
}

static int Bootstrap_ShouldRunLoadMenuProbePostConfirm(void)
{
  const char *env_value;

  if ( g_boot_load_menu_probe_post_confirm_checked )
    return g_boot_load_menu_probe_post_confirm_enabled;

  g_boot_load_menu_probe_post_confirm_checked = 1;
  env_value = getenv("CLASH95_LOAD_MENU_PROBE_POST_CONFIRM");
  if ( env_value && *env_value && strcmp(env_value, "0") )
    g_boot_load_menu_probe_post_confirm_enabled = 1;
  return g_boot_load_menu_probe_post_confirm_enabled;
}

static int Bootstrap_ShouldRunLoadMenuProbeBroaderRulesBootstrap(void)
{
  const char *env_value;

  if ( g_boot_load_menu_probe_broader_rules_checked )
    return g_boot_load_menu_probe_broader_rules_enabled;

  g_boot_load_menu_probe_broader_rules_checked = 1;
  g_boot_load_menu_probe_broader_rules_enabled = 1;
  env_value = getenv("CLASH95_LOAD_MENU_PROBE_BROADER_RULES");
  if ( env_value && *env_value && !strcmp(env_value, "0") )
    g_boot_load_menu_probe_broader_rules_enabled = 0;
  return g_boot_load_menu_probe_broader_rules_enabled;
}

static int Bootstrap_ShouldDrawLoadMenuRows(void)
{
  const char *env_value;

  env_value = getenv("CLASH95_LOAD_MENU_PROBE_DRAW_ROWS");
  return !env_value || !*env_value || strcmp(env_value, "0");
}

static int Bootstrap_ShouldExitAfterCapturePhase(const char *phase)
{
  const char *env_value;

  env_value = getenv("CLASH95_MENU_PROBE_EXIT_AFTER_CAPTURE");
  if ( !env_value || !*env_value || !strcmp(env_value, "0") )
    return 0;
  return !strcmp(env_value, "1") || !strcmp(env_value, "all") || !strcmp(env_value, phase);
}

static int Bootstrap_GetMenuProbeWidgetClickCandidate(
  const unsigned char *widget,
  int variant_index,
  int *x_out,
  int *y_out)
{
  unsigned int sprite_set_holder;
  unsigned int sprite_set;
  int sprite_index;
  int top;
  int left;
  int width;
  int height;

  if ( !widget || !x_out || !y_out )
    return 0;
  sprite_set_holder = *(const unsigned int *)(const void *)(widget + 12);
  if ( !sprite_set_holder )
    return 0;
  sprite_set = *(const unsigned int *)(const void *)(uintptr_t)sprite_set_holder;
  if ( !sprite_set )
    return 0;
  sprite_index = *(const int *)(const void *)(widget + 20);
  if ( sprite_index == -1 )
    sprite_index = *(const int *)(const void *)(widget + 16);
  if ( sprite_index == -1 )
    return 0;

  /*
   * The original `unk_5181C0` blob and the `sub_419B80` / `sub_419410`
   * corridor corroborate `[+0]=left/x` and `[+4]=top/y` for the 0x35-byte
   * menu records. The sprite-size helpers are semantically swapped on this
   * menu path: `DLX_GetSpriteHeight` returns the horizontal span and
   * `DLX_GetSpriteWidth` returns the vertical span.
   */
  left = *(const int *)(const void *)(widget + 0);
  top = *(const int *)(const void *)(widget + 4);
  width = (unsigned short)DLX_GetSpriteHeight((int)(intptr_t)sprite_set, (unsigned short)sprite_index);
  height = (unsigned short)DLX_GetSpriteWidth((int)(intptr_t)sprite_set, (unsigned short)sprite_index);
  switch ( variant_index )
  {
    case 0:
      *x_out = left + width / 2;
      *y_out = top + height / 2;
      break;
    case 1:
      *x_out = left + height / 2;
      *y_out = top + width / 2;
      break;
    case 2:
      *x_out = top + width / 2;
      *y_out = left + height / 2;
      break;
    case 3:
      *x_out = top + height / 2;
      *y_out = left + width / 2;
      break;
    default:
      return 0;
  }
  return 1;
}

static void Bootstrap_SurfaceRendererLoadGfx(int surface_handle, const char *path)
{
  Render_LoadPCXImage(surface_handle, (char *)path, 0, (int)(intptr_t)byte_543D80);
}

static void Bootstrap_SurfaceRendererDrawStage(int surface_handle, int value, int has_value)
{
  (void)value;
  (void)has_value;
  sub_401E30((unsigned int *)(uintptr_t)(unsigned int)surface_handle);
}

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
    if ( !strcmp(argv[arg_index], "--platform-window-only") )
    {
      g_boot_run_platform_window_only = 1;
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
  Device_GetParamA((int)(intptr_t)dword_544CD8, 0);
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
  Bootstrap_TraceMenuProbe("video-init-probe-start");
  dword_543CA0 = 1;
  Bootstrap_TraceMenuProbe("video-init-sub_401A40");
  sub_401A40();
  Bootstrap_TraceMenuProbe("video-init-device-get-param-a");
  Device_GetParamA((int)(intptr_t)dword_544CD8, 0);
  Bootstrap_TraceMenuProbe("video-init-nullsub_4");
  nullsub_4();
  Bootstrap_TraceMenuProbe("video-init-set-pixel-format");
  Render_SetPixelFormat((int)(intptr_t)&unk_51D4C0, (int)(intptr_t)hWnd, 16, 0);
  Bootstrap_TraceMenuProbe("video-init-sub_460490");
  sub_460490((int)(intptr_t)dword_544CD8, 0, command_mode, 0);
  Bootstrap_TraceMenuProbe("video-init-render-create-sprite");
  Render_CreateSprite();
  Bootstrap_TraceMenuProbe("video-init-probe-end");
}

static void Bootstrap_RunRecoveredMainMenuFirstFrameProbe(char command_mode)
{
  unsigned char *menu_widgets;
  const size_t menu_widgets_size = 371;
  int have_menu_widget_template;
  int menu_entry_mode;
  int saved_skip_intro_avi;
  unsigned int widget_offset;
  void *surface;
  int auto_click_index;
  int auto_click_x;
  int auto_click_y;
  int auto_click_phase;
  int auto_click_variant;
  int auto_click_settle_loops;
  int menu_trace_loops;
  int menu_ui_result;
  int fallback_probe_delta_x;
  int fallback_probe_delta_y;
  signed char fallback_probe_primary;
  signed char fallback_probe_secondary;

  menu_widgets = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)menu_widgets_size);
  if ( !menu_widgets )
    return;
  auto_click_index = -1;
  auto_click_x = 0;
  auto_click_y = 0;
  auto_click_phase = -1;
  auto_click_variant = 0;
  auto_click_settle_loops = 0;
  menu_trace_loops = 0;
  menu_ui_result = 0;
  fallback_probe_delta_x = 0;
  fallback_probe_delta_y = 0;
  fallback_probe_primary = 0;
  fallback_probe_secondary = 0;

  Bootstrap_TraceMenuProbe("create-menu-surface");
  surface = Mem_Alloc(188, 0, command_mode, 0);
  if ( surface )
    surface = Render_CreateSurface((int)(intptr_t)surface, 640, 480);
  dword_5202E0 = (int)(intptr_t)surface;

  Bootstrap_TraceMenuProbe("start-ui-anims");
  saved_skip_intro_avi = g_BootstrapSkipIntroAviPlayback;
  g_BootstrapSkipIntroAviPlayback = 1;
  UI_StartAnims(0, command_mode, 0);
  g_BootstrapSkipIntroAviPlayback = saved_skip_intro_avi;
  Render_SetResourceHandle((int)(intptr_t)&unk_51D4C0, 1);
  g_RenderHook = Render_DefaultRH;
  menu_entry_mode = (unsigned char)command_mode;
  Bootstrap_TraceMenuProbe("first-dd-pump");
  DD_Pump((int)(intptr_t)dword_544CD8, menu_entry_mode);

  Bootstrap_TraceMenuProbe("load-menu-s32");
  surface = Mem_Alloc(0x1010, 0, command_mode, 0);
  if ( surface )
    surface = DLXSpriteSet_Load(surface, "menu\\main.s32");
  g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)surface;

  Bootstrap_TraceMenuProbe("load-menu-gfx");
  Bootstrap_SurfaceRendererLoadGfx(dword_5202E0, "menu\\main.gfx");
  Bootstrap_TraceMenuProbe("load-menu-pal");
  sub_435ED0("menu\\main", (int)(intptr_t)byte_543D80, 0, 0);
  if ( menu_entry_mode && dword_5188C0 )
  {
    Bootstrap_TraceMenuProbe("start-menu-music");
    g_MainMenuMusicHandle = sub_441670("music\\menu", 64);
  }

  /*
   * Match the recovered PlayGame_Dispatch prologue: the first-frame top-menu
   * helpers are gated by the carried entry-state variable (`v128`), not by the
   * return value of `DD_Pump`.
   */
  Bootstrap_TraceMenuProbe("second-dd-pump");
  DD_Pump((int)(intptr_t)dword_544CD8, menu_entry_mode);
  if ( menu_entry_mode )
  {
    Bootstrap_TraceMenuProbe("apply-palette-block");
    sub_404D90((int *)&unk_51D4C0);
  }
  Bootstrap_TraceMenuProbe("third-dd-pump");
  DD_Pump((int)(intptr_t)dword_544CD8, menu_entry_mode);
  Bootstrap_TraceMenuProbe("draw-menu-stage-1");
  Bootstrap_SurfaceRendererDrawStage(dword_5202E0, 0, 0);
  Bootstrap_TraceMenuProbe("draw-menu-stage-2");
  Bootstrap_SurfaceRendererDrawStage(dword_5202E0, 92, 1);

  MainMenu_RebuildButtonWidgetTemplate();
  have_menu_widget_template = *(const unsigned int *)(const void *)&g_MainMenuButtonWidgetsTemplate != 0;
  if ( have_menu_widget_template )
  {
    memcpy(menu_widgets, &g_MainMenuButtonWidgetsTemplate, menu_widgets_size);
    for ( widget_offset = 0; widget_offset < menu_widgets_size; widget_offset += 0x35 )
    {
      if ( *(const int *)(const void *)(menu_widgets + widget_offset) == -1 )
        break;
      *(uint32_t *)(void *)(menu_widgets + widget_offset + 0x10) += (unsigned char)g_LanguageIndex;
      *(uint32_t *)(void *)(menu_widgets + widget_offset + 0x14) += (unsigned char)g_LanguageIndex;
    }
  }

  g_RenderDevice = &unk_51D4C0;
  if ( have_menu_widget_template )
  {
    Bootstrap_TraceMenuProbe("init-menu-widgets");
    sub_419D80((void *)menu_widgets);
  }
  else
  {
    Bootstrap_TraceMenuProbe("skip-menu-widgets-template-missing");
  }
  if ( menu_entry_mode )
  {
    Bootstrap_TraceMenuProbe("apply-menu-fade");
    sub_405020((int *)&unk_51D4C0, byte_543D80, 60);
  }
  g_PlayGameMenuExitRequested = 0;
  g_MainMenuRequestedScreen = 0;
  if ( have_menu_widget_template )
  {
    Bootstrap_TraceMenuProbe("build-menu-text-cache");
    sub_460CB0((int)(intptr_t)dword_544CD8, (int)(intptr_t)byte_543D80, 0, 0);
  }
  else
  {
    Bootstrap_TraceMenuProbe("skip-menu-text-cache-template-missing");
  }
  Bootstrap_TraceMenuProbe("select-cursor-descriptor");
  sub_460D80((int)(intptr_t)dword_544CD8, (int)(intptr_t)&unk_5196A0);
  dword_545150 = (int)(intptr_t)&unk_5196A0;
  Bootstrap_TraceMenuProbe("present-menu");
  Render_Present((int)(intptr_t)dword_544CD8);

  /*
   * The contained probe still lacks the dirty-bit/runtime invalidation that
   * normally carries the recovered companion surface onto the SDL window. The
   * companion already holds the staged menu frame here, so present it directly
   * and keep the workaround quarantined to the probe.
   */
  Bootstrap_TraceMenuProbe("force-menu-window-present");
  Platform_PresentRecoveredIndexedSurfaceHandle(
    (void *)(uintptr_t)*(const unsigned int *)(const void *)((const unsigned char *)&unk_51D4C0 + 0xD0),
    (const uint32_t *)(const void *)byte_543D80);
  if ( Bootstrap_ShouldExitAfterCapturePhase("main-menu") )
  {
    Bootstrap_TraceMenuProbe("main-menu-capture-exit");
    Compat_FreeLow32Bytes((int)(uintptr_t)menu_widgets);
    return;
  }

  if ( !have_menu_widget_template )
  {
    Bootstrap_TraceMenuProbe("enter-menu-idle-fallback");
    while ( !g_PlayGameMenuExitRequested )
    {
      Bootstrap_TraceMenuProbe("menu-idle-pump");
      DD_Pump((int)(intptr_t)dword_544CD8, 16);
    }
    Compat_FreeLow32Bytes((int)(uintptr_t)menu_widgets);
    return;
  }

  auto_click_index = Bootstrap_GetMenuProbeAutoClickIndex();
  if ( auto_click_index >= 0
    && Bootstrap_GetMenuProbeWidgetClickCandidate(
         menu_widgets + 0x35 * auto_click_index,
         auto_click_variant,
         &auto_click_x,
         &auto_click_y) )
  {
    auto_click_phase = 0;
    if ( g_boot_trace_menu_probe_enabled )
    {
      fprintf(
        stderr,
        "[menu-probe] auto-click-arm widget=%d variant=%d x=%d y=%d\n",
        auto_click_index,
        auto_click_variant,
        auto_click_x,
        auto_click_y);
      fflush(stderr);
    }
  }

  Bootstrap_TraceMenuProbe("enter-menu-loop");
  while ( !g_PlayGameMenuExitRequested )
  {
    if ( auto_click_phase == 0 )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(
        auto_click_x - (dword_544CFC >> byte_54512C),
        auto_click_y - (dword_544D00 >> byte_54512C),
        0,
        0);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] fallback-readback phase=move mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMouseDelta(
          auto_click_x - (dword_544CFC >> byte_54512C),
          auto_click_y - (dword_544D00 >> byte_54512C),
          0,
          0);
      }
      Bootstrap_TraceMenuProbe("auto-click-move");
      auto_click_phase = 1;
    }
    else if ( auto_click_phase == 1 )
    {
      Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] fallback-readback phase=down mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      }
      Bootstrap_TraceMenuProbe("auto-click-down");
      auto_click_phase = 2;
    }
    else if ( auto_click_phase == 2 )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] fallback-readback phase=up mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      }
      Bootstrap_TraceMenuProbe("auto-click-up");
      auto_click_phase = 3;
      auto_click_settle_loops = 0;
    }
    else if ( auto_click_phase == 3 )
    {
      ++auto_click_settle_loops;
      if ( auto_click_settle_loops >= 16 && auto_click_variant < 3 )
      {
        ++auto_click_variant;
        if ( Bootstrap_GetMenuProbeWidgetClickCandidate(
               menu_widgets + 0x35 * auto_click_index,
               auto_click_variant,
               &auto_click_x,
               &auto_click_y) )
        {
          auto_click_phase = 0;
          auto_click_settle_loops = 0;
          if ( g_boot_trace_menu_probe_enabled )
          {
            fprintf(
              stderr,
              "[menu-probe] auto-click-rearm widget=%d variant=%d x=%d y=%d\n",
              auto_click_index,
              auto_click_variant,
              auto_click_x,
              auto_click_y);
            fflush(stderr);
          }
        }
      }
    }
    Bootstrap_TraceMenuProbe("menu-loop-pump");
    DD_Pump((int)(intptr_t)dword_544CD8, (char)(intptr_t)dword_544CD8);
    Bootstrap_TraceMenuProbe("menu-loop-ui");
    menu_ui_result = sub_419DC0((unsigned int *)menu_widgets, 0);
    if ( g_boot_trace_menu_probe_enabled && auto_click_index >= 0 && menu_trace_loops < 256 )
    {
      const unsigned char widget_flags = *(menu_widgets + 0x35 * auto_click_index + 8);
      const unsigned char device_flags =
        *((const unsigned char *)(const void *)dword_544CD8 + 44);
      const unsigned int render_method_table = *((const unsigned int *)(const void *)((const unsigned char *)dword_544CD8 + 1120));
      const unsigned int render_method_input =
        render_method_table ? (unsigned int)(uintptr_t)((const uintptr_t *)(const void *)(uintptr_t)render_method_table)[5] : 0;

      fprintf(
        stderr,
        "[menu-probe] loop-state variant=%d phase=%d result=%d widget_flags=%u cursor_x=%d cursor_y=%d device_flags=%u screen=%d method_table=%u method20=%u\n",
        auto_click_variant,
        auto_click_phase,
        menu_ui_result,
        widget_flags,
        dword_544CFC >> byte_54512C,
        dword_544D00 >> byte_54512C,
        device_flags,
        g_MainMenuRequestedScreen,
        render_method_table,
        render_method_input);
      fflush(stderr);
      fprintf(
        stderr,
        "[menu-probe] input-state mdx=%d mdy=%d mp=%d ms=%d mouse_ready=%d keyboard_ready=%d mouse_dev=%u keyboard_dev=%u direct_input=%u\n",
        g_InputBackendState.mouse_delta_x,
        g_InputBackendState.mouse_delta_y,
        g_InputBackendState.mouse_button_primary,
        g_InputBackendState.mouse_button_secondary,
        g_InputBackendState.mouse_device_ready,
        g_InputBackendState.keyboard_device_ready,
        g_InputBackendState.mouse_device,
        g_InputBackendState.keyboard_device,
        g_InputBackendState.direct_input);
      fflush(stderr);
      ++menu_trace_loops;
    }
    Platform_PresentRecoveredIndexedSurfaceHandle(
      (void *)(uintptr_t)*(const unsigned int *)(const void *)((const unsigned char *)&unk_51D4C0 + 0xD0),
      (const uint32_t *)(const void *)byte_543D80);
  }
  if ( g_boot_trace_menu_probe_enabled )
  {
    fprintf(
      stderr,
      "[menu-probe] menu-loop-exit screen=%d\n",
      g_MainMenuRequestedScreen);
    fflush(stderr);
  }
  Compat_FreeLow32Bytes((int)(uintptr_t)menu_widgets);
  Bootstrap_TraceMenuProbe("menu-loop-cleanup");
  Render_Pump();
  if ( g_MainMenuRequestedScreen == 5 )
  {
    Bootstrap_TraceMenuProbe("menu-loop-enter-load-menu-probe");
    Bootstrap_RunRecoveredLoadGameMenuProbe(command_mode);
  }
}

static void Bootstrap_RunRecoveredLoadGameMenuProbe(char command_mode)
{
  unsigned char *menu_widgets;
  const size_t menu_widgets_size = 159;
  void *surface;
  int previous_slot_index;
  int slot_index;
  int auto_click_index;
  int auto_click_x;
  int auto_click_y;
  int auto_click_phase;
  int auto_click_variant;
  int auto_click_settle_loops;
  int menu_trace_loops;
  int menu_ui_result;
  int auto_hover_slot_index;
  int auto_hover_slot_x;
  int auto_hover_slot_y;
  int auto_hover_slot_pending;
  int auto_hover_exit_on_select;
  int auto_slot_click_phase;
  int fallback_probe_delta_x;
  int fallback_probe_delta_y;
  signed char fallback_probe_primary;
  signed char fallback_probe_secondary;

  menu_widgets = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)menu_widgets_size);
  if ( !menu_widgets )
    return;

  auto_click_index = -1;
  auto_click_x = 0;
  auto_click_y = 0;
  auto_click_phase = -1;
  auto_click_variant = 0;
  auto_click_settle_loops = 0;
  menu_trace_loops = 0;
  menu_ui_result = 0;
  auto_hover_slot_index = -1;
  auto_hover_slot_x = 0;
  auto_hover_slot_y = 0;
  auto_hover_slot_pending = 0;
  auto_hover_exit_on_select = 0;
  auto_slot_click_phase = -1;
  fallback_probe_delta_x = 0;
  fallback_probe_delta_y = 0;
  fallback_probe_primary = 0;
  fallback_probe_secondary = 0;
  dword_544190 = 0;
  dword_5441E0 = -1;

  Bootstrap_TraceMenuProbe("load-menu-load-s32");
  surface = Mem_Alloc(0x1010, 0, command_mode, 0);
  if ( surface )
    surface = DLXSpriteSet_Load(surface, "menu\\load.s32");
  g_PlayGameMenuSpriteSetHandle = (int)(intptr_t)surface;

  Bootstrap_TraceMenuProbe("load-menu-gfx");
  Bootstrap_SurfaceRendererLoadGfx(dword_5202E0, "menu\\load.gfx");
  Bootstrap_TraceMenuProbe("load-menu-row-resource-draw");
  if ( Bootstrap_ShouldDrawLoadMenuRows() )
  {
    int row_index;

    Bootstrap_TraceMenuProbe("load-menu-row-resource-18");
    Render_LoadResourceSprite_v4(18, byte_543D80, 0, 0, 0);
    Bootstrap_TraceMenuProbe("load-menu-row-resource-21");
    Render_LoadResourceSprite_v4(21, byte_543D80, 0, 0, 0);
    for ( row_index = 0; row_index < 10; ++row_index )
    {
      Bootstrap_TraceMenuProbe("load-menu-row-draw");
      sub_44A140(row_index, 0);
    }
  }
  Bootstrap_TraceMenuProbe("load-menu-draw-stage");
  Bootstrap_SurfaceRendererDrawStage(dword_5202E0, 0, 0);
  Bootstrap_TraceMenuProbe("load-menu-row-draws-complete");

  LoadMenu_RebuildButtonWidgetTemplate();
  memcpy(menu_widgets, &g_LoadMenuButtonWidgetsTemplate, menu_widgets_size);
  g_RenderDevice = &unk_51D4C0;
  Bootstrap_TraceMenuProbe("load-menu-init-widgets");
  sub_419D80((void *)menu_widgets);
  g_PlayGameMenuExitRequested = 0;
  Bootstrap_TraceMenuProbe("load-menu-build-text-cache");
  sub_460CB0((int)(intptr_t)dword_544CD8, (int)(intptr_t)byte_543D80, 0, 0);
  Bootstrap_TraceMenuProbe("load-menu-select-cursor-descriptor");
  sub_460D80((int)(intptr_t)dword_544CD8, (int)(intptr_t)&unk_5196A0);
  dword_545150 = (int)(intptr_t)&unk_5196A0;
  Bootstrap_TraceMenuProbe("load-menu-present");
  Render_Present((int)(intptr_t)dword_544CD8);
  Bootstrap_TraceMenuProbe("load-menu-force-window-present");
  Platform_PresentRecoveredIndexedSurfaceHandle(
    (void *)(uintptr_t)*(const unsigned int *)(const void *)((const unsigned char *)&unk_51D4C0 + 0xD0),
    (const uint32_t *)(const void *)byte_543D80);

  auto_click_index = Bootstrap_GetLoadMenuProbeAutoClickIndex();
  if ( auto_click_index >= 0
    && Bootstrap_GetMenuProbeWidgetClickCandidate(
         menu_widgets + 0x35 * auto_click_index,
         auto_click_variant,
         &auto_click_x,
         &auto_click_y) )
  {
    auto_click_phase = 0;
    if ( g_boot_trace_menu_probe_enabled )
    {
      fprintf(
        stderr,
        "[menu-probe] load-auto-click-arm widget=%d variant=%d x=%d y=%d\n",
        auto_click_index,
        auto_click_variant,
        auto_click_x,
        auto_click_y);
      fflush(stderr);
    }
  }
  auto_hover_slot_index = Bootstrap_GetLoadMenuProbeAutoSlotIndex();
  if ( auto_hover_slot_index >= 0 )
  {
    auto_hover_slot_x = 327;
    auto_hover_slot_y = 165 + 22 * auto_hover_slot_index;
    auto_hover_slot_pending = 1;
    auto_hover_exit_on_select = auto_click_index < 0;
    if ( auto_click_index >= 0 )
    {
      /*
       * The recovered load-menu loop treats a click on the save-slot strip as
       * the authentic entry into `dword_5441E0` / `sub_44A110`. When the
       * contained probe also wants the bottom-row button, click the slot first
       * and only fall through to the button if the row click does not exit.
       */
      auto_slot_click_phase = 0;
      auto_click_phase = -1;
    }
    if ( g_boot_trace_menu_probe_enabled )
    {
      fprintf(
        stderr,
        "[menu-probe] load-auto-hover-arm slot=%d x=%d y=%d\n",
        auto_hover_slot_index,
        auto_hover_slot_x,
        auto_hover_slot_y);
      fflush(stderr);
    }
  }

  Bootstrap_TraceMenuProbe("enter-load-menu-loop");
  while ( !g_PlayGameMenuExitRequested )
  {
    if ( auto_hover_slot_pending )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(
        auto_hover_slot_x - (dword_544CFC >> byte_54512C),
        auto_hover_slot_y - (dword_544D00 >> byte_54512C),
        0,
        0);
      Bootstrap_TraceMenuProbe("load-auto-hover-slot");
      auto_hover_slot_pending = 0;
    }
    else if ( auto_slot_click_phase == 0 )
    {
      Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] load-fallback-readback phase=slot-down mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      }
      Bootstrap_TraceMenuProbe("load-auto-slot-down");
      auto_slot_click_phase = 1;
    }
    else if ( auto_slot_click_phase == 1 )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] load-fallback-readback phase=slot-up mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      }
      Bootstrap_TraceMenuProbe("load-auto-slot-up");
      auto_slot_click_phase = 2;
    }
    else if ( auto_slot_click_phase == 2 )
    {
      if ( dword_544190 )
      {
        auto_slot_click_phase = 3;
      }
      else if ( auto_click_index >= 0 && dword_5441E0 != -1 )
      {
        auto_click_phase = 0;
        auto_slot_click_phase = 3;
        Bootstrap_TraceMenuProbe("load-auto-click-after-slot");
      }
    }
    else if ( auto_click_phase == 0 )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(
        auto_click_x - (dword_544CFC >> byte_54512C),
        auto_click_y - (dword_544D00 >> byte_54512C),
        0,
        0);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] load-fallback-readback phase=move mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMouseDelta(
          auto_click_x - (dword_544CFC >> byte_54512C),
          auto_click_y - (dword_544D00 >> byte_54512C),
          0,
          0);
      }
      Bootstrap_TraceMenuProbe("load-auto-click-move");
      auto_click_phase = 1;
    }
    else if ( auto_click_phase == 1 )
    {
      Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] load-fallback-readback phase=down mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMousePulse(0, 0, 1, 0, 1);
      }
      Bootstrap_TraceMenuProbe("load-auto-click-down");
      auto_click_phase = 2;
    }
    else if ( auto_click_phase == 2 )
    {
      Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      if ( g_boot_trace_menu_probe_enabled )
      {
        Platform_ReadInputFallbackState(
          &fallback_probe_delta_x,
          &fallback_probe_delta_y,
          &fallback_probe_primary,
          &fallback_probe_secondary,
          0,
          0);
        fprintf(
          stderr,
          "[menu-probe] load-fallback-readback phase=up mdx=%d mdy=%d mp=%d ms=%d\n",
          fallback_probe_delta_x,
          fallback_probe_delta_y,
          fallback_probe_primary,
          fallback_probe_secondary);
        fflush(stderr);
        Platform_DebugPrimeInputFallbackMouseDelta(0, 0, 0, 0);
      }
      Bootstrap_TraceMenuProbe("load-auto-click-up");
      auto_click_phase = 3;
      auto_click_settle_loops = 0;
    }
    else if ( auto_click_phase == 3 )
    {
      ++auto_click_settle_loops;
      if ( auto_click_settle_loops >= 16 && auto_click_variant < 3 )
      {
        ++auto_click_variant;
        if ( Bootstrap_GetMenuProbeWidgetClickCandidate(
               menu_widgets + 0x35 * auto_click_index,
               auto_click_variant,
               &auto_click_x,
               &auto_click_y) )
        {
          auto_click_phase = 0;
          auto_click_settle_loops = 0;
          if ( g_boot_trace_menu_probe_enabled )
          {
            fprintf(
              stderr,
              "[menu-probe] load-auto-click-rearm widget=%d variant=%d x=%d y=%d\n",
              auto_click_index,
              auto_click_variant,
              auto_click_x,
              auto_click_y);
            fflush(stderr);
          }
        }
      }
    }

    Bootstrap_TraceMenuProbe("load-menu-loop-pump");
    DD_Pump((int)(intptr_t)dword_544CD8, (char)(intptr_t)&unk_5196A0);
    if ( auto_hover_exit_on_select )
    {
      if ( dword_544CFC >> byte_54512C >= 244 && dword_544CFC >> byte_54512C <= 410 )
      {
        slot_index = ((dword_544D00 >> byte_54512C) - 155) / 22;
        if ( slot_index >= 0 && slot_index <= 9 )
        {
          dword_5441E0 = slot_index;
          g_PlayGameMenuExitRequested = 1;
          Bootstrap_TraceMenuProbe("load-auto-hover-selected");
        }
      }
    }
    if ( DD_IsFlipping((int)(intptr_t)dword_544CD8) )
    {
      if ( dword_544CFC >> byte_54512C >= 244 && dword_544CFC >> byte_54512C <= 410 )
      {
        slot_index = ((dword_544D00 >> byte_54512C) - 155) / 22;
        if ( slot_index <= 9 )
        {
          previous_slot_index = dword_5441E0;
          if ( slot_index != dword_5441E0 )
          {
            dword_5441E0 = slot_index;
            if ( previous_slot_index != -1 )
              sub_44A140(previous_slot_index, 0);
            sub_44A140(dword_5441E0, 0);
          }
          if ( auto_hover_exit_on_select && dword_5441E0 == auto_hover_slot_index )
          {
            g_PlayGameMenuExitRequested = 1;
            Bootstrap_TraceMenuProbe("load-auto-hover-selected");
          }
          if ( sub_460950((int)(intptr_t)dword_544CD8) )
            sub_44A110(0, 0);
        }
      }
    }
    if ( g_PlayGameMenuExitRequested )
      break;
    Bootstrap_TraceMenuProbe("load-menu-loop-ui");
    menu_ui_result = sub_419DC0((unsigned int *)menu_widgets, 0);
    if ( g_boot_trace_menu_probe_enabled && menu_trace_loops < 256 )
    {
      fprintf(
        stderr,
        "[menu-probe] load-loop-state variant=%d phase=%d result=%d selected_slot=%d confirm=%d cursor_x=%d cursor_y=%d exit=%d screen=%d\n",
        auto_click_variant,
        auto_click_phase,
        menu_ui_result,
        dword_5441E0,
        dword_544190,
        dword_544CFC >> byte_54512C,
        dword_544D00 >> byte_54512C,
        g_PlayGameMenuExitRequested,
        g_MainMenuRequestedScreen);
      fflush(stderr);
      ++menu_trace_loops;
    }
    Platform_PresentRecoveredIndexedSurfaceHandle(
      (void *)(uintptr_t)*(const unsigned int *)(const void *)((const unsigned char *)&unk_51D4C0 + 0xD0),
      (const uint32_t *)(const void *)byte_543D80);
  }
  if ( g_boot_trace_menu_probe_enabled )
  {
    fprintf(
      stderr,
      "[menu-probe] load-menu-loop-exit selected_slot=%d confirm=%d screen=%d\n",
      dword_5441E0,
      dword_544190,
      g_MainMenuRequestedScreen);
    fflush(stderr);
  }
  Compat_FreeLow32Bytes((int)(uintptr_t)menu_widgets);
  Bootstrap_TraceMenuProbe("load-menu-loop-cleanup");
  Render_Pump();
  if ( dword_544190 )
    sub_404F20((int *)&unk_51D4C0, 20);
  sub_405920(&g_PlayGameMenuSpriteSetHandle);
  if ( !dword_544190 )
    dword_5441E0 = -1;
  if ( Bootstrap_ShouldRunLoadMenuProbePostConfirm() && dword_5441E0 != -1 )
  {
    Bootstrap_TraceMenuProbe("load-menu-post-confirm-stop-sound");
    CSS_StopSound(g_MainMenuMusicHandle, 1000);
    Bootstrap_TraceMenuProbe("load-menu-post-confirm-worldmap-init");
    WorldMap_Initialize((char)dword_5441E0, 0);
    if ( Bootstrap_ShouldRunLoadMenuProbeBroaderRulesBootstrap() )
    {
      if ( !dword_54DBA8 )
      {
        Bootstrap_TraceMenuProbe("load-menu-post-confirm-rules-slab-init");
        sub_4725B0(0, 0);
      }
      Bootstrap_TraceMenuProbe("load-menu-post-confirm-rules-index-init");
      sub_482260();
      Bootstrap_TraceMenuProbe("load-menu-post-confirm-parser-bootstrap");
      sub_491B10();
    }
    Bootstrap_TraceMenuProbe("load-menu-post-confirm-load-save");
    sub_444490(dword_5441E0, 0, 0.0);
    Bootstrap_TraceMenuProbe("load-menu-post-confirm-after-save");
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
  if ( g_boot_run_platform_window_only )
    return Bootstrap_RunPlatformWindowLoop();
  /*
   * Explicit probes let us isolate startup, render init, and menu presentation
   * slices without always entering the default front-end path below.
   */
  if ( g_boot_run_startup_prelude )
  {
    char command_mode;

    if ( !Bootstrap_RunRecoveredEarlyStartupPrelude(GetModuleHandleA(0), g_boot_command_line, &command_mode) )
      return 1;
    if ( g_boot_run_video_init_probe )
    {
      Bootstrap_TraceMenuProbe("main-before-video-init-probe");
      Bootstrap_RunRecoveredVideoInitProbe(command_mode);
      Bootstrap_TraceMenuProbe("main-after-video-init-probe");
    }
    if ( g_boot_run_menu_probe )
    {
      Bootstrap_TraceMenuProbe("main-before-menu-probe-video-init");
      Bootstrap_RunRecoveredVideoInitProbe(command_mode);
      Bootstrap_TraceMenuProbe("main-before-menu-probe");
      Bootstrap_RunRecoveredMainMenuFirstFrameProbe(command_mode);
      Bootstrap_TraceMenuProbe("main-after-menu-probe");
      if ( Bootstrap_ShouldExitAfterCapturePhase("main-menu")
        || Bootstrap_ShouldExitAfterCapturePhase("load-menu") )
      {
        return 0;
      }
      return Bootstrap_RunMessageLoop();
    }
    (void)command_mode;
    return Bootstrap_RunMessageLoop();
  }
  /*
   * Default to the recovered front-end foothold rather than a bare SDL window:
   * early startup prelude, video/render init, and the contained authentic menu
   * presentation path. The full `App_WinMain` game-entry handoff remains
   * gated until the wider runtime/session surface is ready.
   */
  {
    char command_mode;

    if ( !Bootstrap_RunRecoveredEarlyStartupPrelude(GetModuleHandleA(0), g_boot_command_line, &command_mode) )
      return 1;
    Bootstrap_RunRecoveredVideoInitProbe(command_mode);
    Bootstrap_RunRecoveredMainMenuFirstFrameProbe(command_mode);
    if ( Bootstrap_ShouldExitAfterCapturePhase("main-menu")
      || Bootstrap_ShouldExitAfterCapturePhase("load-menu") )
    {
      return 0;
    }
    return Bootstrap_RunMessageLoop();
  }
}
