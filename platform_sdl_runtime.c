#include "platform_sdl.h"

#define SDL_MAIN_HANDLED
#define SDL_Window SDL2_Window
#define SDL_Renderer SDL2_Renderer
#define SDL_Texture SDL2_Texture
#define SDL_Surface SDL2_Surface
#define SDL_Palette SDL2_Palette
#define SDL_Cursor SDL2_Cursor
#include <SDL2/SDL.h>
#undef SDL_Window
#undef SDL_Renderer
#undef SDL_Texture
#undef SDL_Surface
#undef SDL_Palette
#undef SDL_Cursor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * Minimal SDL-target runtime seam for the recovered platform layer.
 *
 * The decompiled core still calls Win32-style window/message/timing helpers.
 * These placeholders keep the compile target moving toward SDL by owning the
 * window/message abstractions locally instead of depending on Win32 headers or
 * import libraries. They are intentionally narrow and conservative.
 */

struct SDL_Window {
  int x;
  int y;
  int width;
  int height;
  int visible;
  DWORD style;
  const char *class_name;
  const char *title;
  SDL2_Window *host_window;
};

struct SDL_Renderer {
  int unused;
};

struct SDL_Texture {
  int unused;
};

struct SDL_Surface {
  int width;
  int height;
  const char *resource_name;
  COLORREF key_pixel;
};

struct SDL_Palette {
  int version;
};

struct SDL_Cursor {
  int cursor_id;
};

extern LRESULT Platform_MainWindowProc(void *this_, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
DWORD __stdcall timeGetTime(void);

#define PLATFORM_QUEUE_CAPACITY 32
#define PLATFORM_WM_PAINT 0x000F
#define PLATFORM_WM_QUIT 0x0012
#define PLATFORM_WM_ACTIVATEAPP 0x001C

static WNDCLASSA g_platform_window_class;
static int g_platform_has_window_class;
static HWND g_platform_foreground_window;
static struct SDL_Surface g_platform_default_surface = { 640, 480 };
static struct SDL_Surface g_platform_default_icon = { 32, 32 };
static struct SDL_Cursor g_platform_default_cursor = { 0 };
static int g_platform_stock_brush;
static int g_platform_module_handle_token;
static DWORD g_platform_last_error;
static MSG g_platform_message_queue[PLATFORM_QUEUE_CAPACITY];
static size_t g_platform_message_head;
static size_t g_platform_message_tail;
static int g_platform_quit_requested;
static int g_platform_quit_code;
static int g_platform_sdl_initialized;
static int g_platform_sdl_available;
static int g_platform_host_mouse_x;
static int g_platform_host_mouse_y;
static int g_platform_host_mouse_delta_x;
static int g_platform_host_mouse_delta_y;
static signed char g_platform_host_mouse_primary;
static signed char g_platform_host_mouse_secondary;
static signed char g_platform_host_keyboard_state[256];

static int PlatformSurfaceIsBuiltin(const struct SDL_Surface *surface)
{
  return surface == &g_platform_default_surface || surface == &g_platform_default_icon;
}

static int PlatformQueueIsEmpty(void)
{
  return g_platform_message_head == g_platform_message_tail;
}

static void PlatformFillQuitMessage(LPMSG lpMsg)
{
  if ( !lpMsg )
    return;
  memset(lpMsg, 0, sizeof(*lpMsg));
  lpMsg->hwnd = g_platform_foreground_window;
  lpMsg->message = PLATFORM_WM_QUIT;
  lpMsg->wParam = (WPARAM)g_platform_quit_code;
}

static BOOL PlatformQueuePush(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  size_t next_tail;

  next_tail = (g_platform_message_tail + 1) % PLATFORM_QUEUE_CAPACITY;
  if ( next_tail == g_platform_message_head )
    return 0;
  g_platform_message_queue[g_platform_message_tail].hwnd = hwnd;
  g_platform_message_queue[g_platform_message_tail].message = message;
  g_platform_message_queue[g_platform_message_tail].wParam = wParam;
  g_platform_message_queue[g_platform_message_tail].lParam = lParam;
  g_platform_message_queue[g_platform_message_tail].time = timeGetTime();
  g_platform_message_queue[g_platform_message_tail].pt.x = 0;
  g_platform_message_queue[g_platform_message_tail].pt.y = 0;
  g_platform_message_tail = next_tail;
  return 1;
}

static BOOL PlatformQueuePeek(LPMSG lpMsg, BOOL remove_message)
{
  if ( PlatformQueueIsEmpty() )
    return 0;
  if ( lpMsg )
    *lpMsg = g_platform_message_queue[g_platform_message_head];
  if ( remove_message )
    g_platform_message_head = (g_platform_message_head + 1) % PLATFORM_QUEUE_CAPACITY;
  return 1;
}

static int PlatformEnsureSdlVideo(void)
{
  if ( g_platform_sdl_initialized )
    return g_platform_sdl_available;
  g_platform_sdl_initialized = 1;
  SDL_SetMainReady();
  if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) == 0 )
  {
    g_platform_sdl_available = 1;
    return 1;
  }
  fprintf(stderr, "[platform_sdl] SDL_Init failed: %s\n", SDL_GetError());
  return 0;
}

static HWND PlatformFindWindowByHostId(Uint32 window_id)
{
  struct SDL_Window *window;
  SDL2_Window *host_window;

  if ( !window_id || !g_platform_foreground_window || !g_platform_sdl_available )
    return 0;
  host_window = SDL_GetWindowFromID(window_id);
  window = (struct SDL_Window *)g_platform_foreground_window;
  if ( !host_window || !window || window->host_window != host_window )
    return 0;
  return g_platform_foreground_window;
}

static int PlatformMapSdlKeyToInputScan(SDL_Keycode sym)
{
  switch ( sym )
  {
    case SDLK_ESCAPE: return 1;
    case SDLK_1: return 2;
    case SDLK_2: return 3;
    case SDLK_3: return 4;
    case SDLK_4: return 5;
    case SDLK_5: return 6;
    case SDLK_6: return 7;
    case SDLK_7: return 8;
    case SDLK_8: return 9;
    case SDLK_9: return 10;
    case SDLK_0: return 11;
    case SDLK_MINUS: return 12;
    case SDLK_EQUALS: return 13;
    case SDLK_BACKSPACE: return 14;
    case SDLK_TAB: return 15;
    case SDLK_q: return 16;
    case SDLK_w: return 17;
    case SDLK_e: return 18;
    case SDLK_r: return 19;
    case SDLK_t: return 20;
    case SDLK_y: return 21;
    case SDLK_u: return 22;
    case SDLK_i: return 23;
    case SDLK_o: return 24;
    case SDLK_p: return 25;
    case SDLK_LEFTBRACKET: return 26;
    case SDLK_RIGHTBRACKET: return 27;
    case SDLK_RETURN:
    case SDLK_KP_ENTER: return 28;
    case SDLK_a: return 30;
    case SDLK_s: return 31;
    case SDLK_d: return 32;
    case SDLK_f: return 33;
    case SDLK_g: return 34;
    case SDLK_h: return 35;
    case SDLK_j: return 36;
    case SDLK_k: return 37;
    case SDLK_l: return 38;
    case SDLK_SEMICOLON: return 39;
    case SDLK_QUOTE: return 40;
    case SDLK_z: return 44;
    case SDLK_x: return 45;
    case SDLK_c: return 46;
    case SDLK_v: return 47;
    case SDLK_b: return 48;
    case SDLK_n: return 49;
    case SDLK_m: return 50;
    case SDLK_COMMA: return 51;
    case SDLK_PERIOD: return 52;
    case SDLK_SLASH: return 53;
    case SDLK_SPACE: return 57;
    case SDLK_F1: return 59;
    case SDLK_F2: return 60;
    case SDLK_F3: return 61;
    case SDLK_F4: return 62;
    case SDLK_F5: return 63;
    case SDLK_F6: return 64;
    case SDLK_F7: return 65;
    case SDLK_F8: return 66;
    case SDLK_F9: return 67;
    case SDLK_F10: return 68;
    case SDLK_HOME: return 199;
    case SDLK_UP: return 200;
    case SDLK_PAGEUP: return 201;
    case SDLK_LEFT: return 203;
    case SDLK_RIGHT: return 205;
    case SDLK_END: return 207;
    case SDLK_DOWN: return 208;
    case SDLK_PAGEDOWN: return 209;
    case SDLK_INSERT: return 210;
    case SDLK_DELETE: return 211;
    default: return -1;
  }
}

static void PlatformSetKeyboardScan(int scan_code, int pressed)
{
  if ( scan_code < 0 || scan_code >= (int)sizeof(g_platform_host_keyboard_state) )
    return;
  g_platform_host_keyboard_state[scan_code] = pressed ? (signed char)0x80 : 0;
}

static void PlatformHandleHostEvent(const SDL_Event *event)
{
  HWND hwnd;
  int scan_code;

  if ( !event )
    return;
  switch ( event->type )
  {
    case SDL_QUIT:
      g_platform_quit_requested = 1;
      g_platform_quit_code = 0;
      break;
    case SDL_WINDOWEVENT:
      hwnd = PlatformFindWindowByHostId(event->window.windowID);
      if ( !hwnd )
        break;
      switch ( event->window.event )
      {
        case SDL_WINDOWEVENT_EXPOSED:
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESIZED:
          ((struct SDL_Window *)hwnd)->width = event->window.data1;
          ((struct SDL_Window *)hwnd)->height = event->window.data2;
          PlatformQueuePush(hwnd, PLATFORM_WM_PAINT, 0, 0);
          break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
          PlatformQueuePush(hwnd, PLATFORM_WM_ACTIVATEAPP, 1, 0);
          break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
          PlatformQueuePush(hwnd, PLATFORM_WM_ACTIVATEAPP, 0, 0);
          break;
        case SDL_WINDOWEVENT_CLOSE:
          g_platform_quit_requested = 1;
          g_platform_quit_code = 0;
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      g_platform_host_mouse_x = event->motion.x;
      g_platform_host_mouse_y = event->motion.y;
      g_platform_host_mouse_delta_x += event->motion.xrel;
      g_platform_host_mouse_delta_y += event->motion.yrel;
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      if ( event->button.button == SDL_BUTTON_LEFT )
        g_platform_host_mouse_primary = event->type == SDL_MOUSEBUTTONDOWN ? (signed char)0x80 : 0;
      else if ( event->button.button == SDL_BUTTON_RIGHT )
        g_platform_host_mouse_secondary = event->type == SDL_MOUSEBUTTONDOWN ? (signed char)0x80 : 0;
      break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      scan_code = PlatformMapSdlKeyToInputScan(event->key.keysym.sym);
      if ( scan_code >= 0 )
        PlatformSetKeyboardScan(scan_code, event->type == SDL_KEYDOWN);
      break;
    default:
      break;
  }
}

static void PlatformPumpHostEvents(void)
{
  SDL_Event event;

  if ( !PlatformEnsureSdlVideo() )
    return;
  while ( SDL_PollEvent(&event) )
    PlatformHandleHostEvent(&event);
}

ATOM __stdcall RegisterClassA(const WNDCLASSA *lpWndClass)
{
  if ( !lpWndClass )
    return 0;
  g_platform_window_class = *lpWndClass;
  g_platform_has_window_class = 1;
  return 1;
}

HWND __stdcall CreateWindowExA(
  DWORD dwExStyle,
  LPCSTR lpClassName,
  LPCSTR lpWindowName,
  DWORD dwStyle,
  int X,
  int Y,
  int nWidth,
  int nHeight,
  HWND hWndParent,
  HMENU hMenu,
  HINSTANCE hInstance,
  LPVOID lpParam)
{
  struct SDL_Window *window;

  (void)dwExStyle;
  (void)hWndParent;
  (void)hMenu;
  (void)hInstance;
  (void)lpParam;
  window = (struct SDL_Window *)calloc(1, sizeof(*window));
  if ( !window )
    return 0;
  window->x = X;
  window->y = Y;
  window->width = nWidth;
  window->height = nHeight;
  window->style = dwStyle;
  window->class_name = lpClassName;
  window->title = lpWindowName;
  if ( PlatformEnsureSdlVideo() )
  {
    window->host_window = SDL_CreateWindow(
      lpWindowName ? lpWindowName : "clash95_recovered",
      X,
      Y,
      nWidth > 0 ? nWidth : 640,
      nHeight > 0 ? nHeight : 480,
      SDL_WINDOW_HIDDEN);
    if ( !window->host_window )
      fprintf(stderr, "[platform_sdl] SDL_CreateWindow failed: %s\n", SDL_GetError());
  }
  g_platform_foreground_window = window;
  g_platform_quit_requested = 0;
  g_platform_quit_code = 0;
  return window;
}

LRESULT __stdcall DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  (void)hWnd;
  (void)Msg;
  (void)wParam;
  (void)lParam;
  return 0;
}

LRESULT __stdcall DispatchMessageA(const MSG *lpMsg)
{
  WNDPROC window_proc;

  if ( !lpMsg )
    return 0;
  if ( lpMsg->message == PLATFORM_WM_QUIT )
  {
    g_platform_quit_requested = 1;
    g_platform_quit_code = (int)lpMsg->wParam;
    return 0;
  }
  if ( g_platform_has_window_class )
  {
    window_proc = g_platform_window_class.lpfnWndProc;
    if ( window_proc )
    {
      if ( (void *)window_proc == (void *)Platform_MainWindowProc )
        return Platform_MainWindowProc(0, lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
      return window_proc(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
    }
  }
  return 0;
}

BOOL __stdcall GetClientRect(HWND hWnd, LPRECT lpRect)
{
  struct SDL_Window *window;

  if ( !lpRect )
    return 0;
  memset(lpRect, 0, sizeof(*lpRect));
  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    lpRect->right = window->width;
    lpRect->bottom = window->height;
  }
  return 1;
}

DWORD __stdcall GetLastError(void)
{
  return g_platform_last_error;
}

void __stdcall SetLastError(DWORD dwErrCode)
{
  g_platform_last_error = dwErrCode;
}

HDC __stdcall GetDC(HWND hWnd)
{
  (void)hWnd;
  return &g_platform_default_surface;
}

int __stdcall GetDeviceCaps(HDC hdc, int index)
{
  (void)hdc;
  switch ( index )
  {
    case 12:
      return 32;
    case 14:
      return 1;
    default:
      return 0;
  }
}

COLORREF __stdcall GetPixel(HDC hdc, int x, int y)
{
  struct SDL_Surface *surface;

  (void)x;
  (void)y;
  surface = (struct SDL_Surface *)hdc;
  if ( !surface )
    return 0;
  return surface->key_pixel;
}

COLORREF __stdcall SetPixel(HDC hdc, int x, int y, COLORREF color)
{
  struct SDL_Surface *surface;

  (void)x;
  (void)y;
  surface = (struct SDL_Surface *)hdc;
  if ( !surface )
    return 0;
  surface->key_pixel = color;
  return color;
}

BOOL __stdcall SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom)
{
  if ( !lprc )
    return 0;
  lprc->left = xLeft;
  lprc->top = yTop;
  lprc->right = xRight;
  lprc->bottom = yBottom;
  return 1;
}

BOOL __stdcall EqualRect(const RECT *lprc1, const RECT *lprc2)
{
  if ( !lprc1 || !lprc2 )
    return 0;
  return lprc1->left == lprc2->left
      && lprc1->top == lprc2->top
      && lprc1->right == lprc2->right
      && lprc1->bottom == lprc2->bottom;
}

BOOL __stdcall IsRectEmpty(const RECT *lprc)
{
  if ( !lprc )
    return 1;
  return lprc->left >= lprc->right || lprc->top >= lprc->bottom;
}

BOOL __stdcall IntersectRect(LPRECT lprcDst, const RECT *lprcSrc1, const RECT *lprcSrc2)
{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;

  if ( !lprcDst || !lprcSrc1 || !lprcSrc2 )
    return 0;
  left = lprcSrc1->left > lprcSrc2->left ? lprcSrc1->left : lprcSrc2->left;
  top = lprcSrc1->top > lprcSrc2->top ? lprcSrc1->top : lprcSrc2->top;
  right = lprcSrc1->right < lprcSrc2->right ? lprcSrc1->right : lprcSrc2->right;
  bottom = lprcSrc1->bottom < lprcSrc2->bottom ? lprcSrc1->bottom : lprcSrc2->bottom;
  if ( left >= right || top >= bottom )
  {
    SetRect(lprcDst, 0, 0, 0, 0);
    return 0;
  }
  SetRect(lprcDst, left, top, right, bottom);
  return 1;
}

HWND __stdcall GetForegroundWindow()
{
  return g_platform_foreground_window;
}

BOOL __stdcall GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  (void)hWnd;
  (void)wMsgFilterMin;
  (void)wMsgFilterMax;
  PlatformPumpHostEvents();
  if ( PlatformQueuePeek(lpMsg, 1) )
  {
    if ( lpMsg && lpMsg->message == PLATFORM_WM_QUIT )
    {
      g_platform_quit_requested = 1;
      g_platform_quit_code = (int)lpMsg->wParam;
      return 0;
    }
    return 1;
  }
  if ( g_platform_quit_requested )
  {
    PlatformFillQuitMessage(lpMsg);
    return 0;
  }
  usleep(10000);
  if ( lpMsg )
    memset(lpMsg, 0, sizeof(*lpMsg));
  return 1;
}

HGDIOBJ __stdcall GetStockObject(int i)
{
  g_platform_stock_brush = i;
  return &g_platform_stock_brush;
}

HCURSOR __stdcall LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName)
{
  (void)hInstance;
  (void)lpCursorName;
  return &g_platform_default_cursor;
}

HICON __stdcall LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName)
{
  (void)hInstance;
  (void)lpIconName;
  return &g_platform_default_icon;
}

int __stdcall MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
  (void)hWnd;
  (void)uType;
  fprintf(stderr, "[platform_sdl] %s: %s\n", lpCaption ? lpCaption : "(no caption)", lpText ? lpText : "(no text)");
  return 0;
}

BOOL __stdcall PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  (void)hWnd;
  (void)wMsgFilterMin;
  (void)wMsgFilterMax;
  PlatformPumpHostEvents();
  if ( PlatformQueuePeek(lpMsg, wRemoveMsg != 0) )
    return 1;
  if ( g_platform_quit_requested )
  {
    PlatformFillQuitMessage(lpMsg);
    return 1;
  }
  if ( lpMsg )
    memset(lpMsg, 0, sizeof(*lpMsg));
  return 0;
}

void __stdcall PostQuitMessage(int nExitCode)
{
  g_platform_quit_requested = 1;
  g_platform_quit_code = nExitCode;
}

int __stdcall ReleaseDC(HWND hWnd, HDC hDC)
{
  (void)hWnd;
  (void)hDC;
  return 1;
}

HDC __stdcall CreateCompatibleDC(HDC hdc)
{
  struct SDL_Surface *source;
  struct SDL_Surface *surface;

  source = (struct SDL_Surface *)hdc;
  surface = (struct SDL_Surface *)calloc(1, sizeof(*surface));
  if ( !surface )
    return 0;
  if ( source )
  {
    surface->width = source->width;
    surface->height = source->height;
  }
  else
  {
    surface->width = 64;
    surface->height = 64;
  }
  return surface;
}

BOOL __stdcall DeleteDC(HDC hdc)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)hdc;
  if ( !surface || PlatformSurfaceIsBuiltin(surface) )
    return 1;
  free(surface);
  return 1;
}

BOOL __stdcall DeleteObject(HGDIOBJ ho)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)ho;
  if ( !surface || PlatformSurfaceIsBuiltin(surface) )
    return 1;
  free(surface);
  return 1;
}

int __stdcall GetObjectA(HANDLE h, int c, LPVOID pv)
{
  const struct SDL_Surface *surface;
  int *bitmap_fields;

  if ( !h || !pv || c <= 0 )
    return 0;
  surface = (const struct SDL_Surface *)h;
  memset(pv, 0, (size_t)c);
  bitmap_fields = (int *)pv;
  if ( c >= 12 )
  {
    bitmap_fields[1] = surface->width;
    bitmap_fields[2] = surface->height;
  }
  return c;
}

HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ h)
{
  struct SDL_Surface *dc_surface;
  const struct SDL_Surface *object_surface;

  dc_surface = (struct SDL_Surface *)hdc;
  object_surface = (const struct SDL_Surface *)h;
  if ( dc_surface && object_surface && !PlatformSurfaceIsBuiltin(dc_surface) )
  {
    dc_surface->width = object_surface->width;
    dc_surface->height = object_surface->height;
  }
  return h;
}

BOOL __stdcall StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
  struct SDL_Surface *dest_surface;

  (void)xDest;
  (void)yDest;
  (void)hdcSrc;
  (void)xSrc;
  (void)ySrc;
  (void)wSrc;
  (void)hSrc;
  (void)rop;
  dest_surface = (struct SDL_Surface *)hdcDest;
  if ( dest_surface && !PlatformSurfaceIsBuiltin(dest_surface) )
  {
    if ( wDest > 0 )
      dest_surface->width = wDest;
    if ( hDest > 0 )
      dest_surface->height = hDest;
  }
  return 1;
}

int __stdcall StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, const void *lpBits, const BITMAPINFO *lpbmi, UINT iUsage, DWORD rop)
{
  struct SDL_Surface *surface;

  (void)xDest;
  (void)yDest;
  (void)xSrc;
  (void)ySrc;
  (void)SrcWidth;
  (void)lpBits;
  (void)lpbmi;
  (void)iUsage;
  (void)rop;
  surface = (struct SDL_Surface *)hdc;
  if ( surface && !PlatformSurfaceIsBuiltin(surface) )
  {
    if ( DestWidth > 0 )
      surface->width = DestWidth;
    if ( DestHeight > 0 )
      surface->height = DestHeight;
  }
  return SrcHeight ? SrcHeight : DestHeight;
}

HANDLE __stdcall LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  struct SDL_Surface *surface;

  (void)hInst;
  (void)type;
  (void)fuLoad;
  surface = (struct SDL_Surface *)calloc(1, sizeof(*surface));
  if ( !surface )
    return 0;
  surface->width = cx > 0 ? cx : 64;
  surface->height = cy > 0 ? cy : 64;
  surface->resource_name = name;
  return surface;
}

BOOL __stdcall ShowWindow(HWND hWnd, int nCmdShow)
{
  struct SDL_Window *window;

  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    window->visible = nCmdShow != 0;
    if ( window->host_window )
    {
      if ( window->visible )
      {
        SDL_ShowWindow(window->host_window);
        SDL_RaiseWindow(window->host_window);
      }
      else
      {
        SDL_HideWindow(window->host_window);
      }
    }
    if ( window->visible )
      PlatformQueuePush(hWnd, PLATFORM_WM_ACTIVATEAPP, 1, 0);
  }
  return 1;
}

DWORD __stdcall timeGetTime()
{
  struct timeval tv;

  if ( gettimeofday(&tv, 0) )
    return 0;
  return (DWORD)(tv.tv_sec * 1000u + tv.tv_usec / 1000u);
}

DWORD __stdcall GetTickCount()
{
  return timeGetTime();
}

BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
{
  struct timeval tv;
  unsigned long long ticks;

  if ( !lpPerformanceCount )
    return 0;
  if ( gettimeofday(&tv, 0) != 0 )
  {
    lpPerformanceCount->QuadPart = 0;
    return 0;
  }
  ticks = (unsigned long long)tv.tv_sec * 1000000ull + (unsigned long long)tv.tv_usec;
  lpPerformanceCount->QuadPart = (long long)ticks;
  return 1;
}

BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
{
  if ( !lpFrequency )
    return 0;
  lpFrequency->QuadPart = 1000000ll;
  return 1;
}

DWORD __stdcall GetVersion()
{
  /*
   * Report an NT-style major version 4 so the recovered platform probes pick a
   * stable, non-9x path until the startup/runtime layer is fully re-emitted.
   */
  return 4u;
}

HMODULE __stdcall GetModuleHandleA(LPCSTR lpModuleName)
{
  (void)lpModuleName;
  return &g_platform_module_handle_token;
}

HRESULT __stdcall DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPVOID lplpDirectInput, LPVOID punkOuter)
{
  (void)hinst;
  (void)dwVersion;
  (void)lplpDirectInput;
  (void)punkOuter;

  /*
   * SDL owns input on the target platform, but the recovered boot path still
   * calls into DirectInput-era setup during window creation. Returning failure
   * keeps the legacy device slots inert while allowing the authentic window
   * proc and message loop to come up.
   */
  return 1;
}

UINT __stdcall GetDriveTypeA(LPCSTR lpRootPathName)
{
  (void)lpRootPathName;
  return 3;
}

void __stdcall OutputDebugStringA(LPCSTR lpOutputString)
{
  if ( lpOutputString )
    fprintf(stderr, "[platform_sdl] debug: %s\n", lpOutputString);
}

BOOL __stdcall TranslateMessage(const MSG *lpMsg)
{
  (void)lpMsg;
  return 1;
}

BOOL __stdcall UpdateWindow(HWND hWnd)
{
  PlatformQueuePush(hWnd, PLATFORM_WM_PAINT, 0, 0);
  return 1;
}

BOOL __stdcall ValidateRect(HWND hWnd, const RECT *lpRect)
{
  (void)hWnd;
  (void)lpRect;
  return 1;
}

BOOL __stdcall WaitMessage()
{
  PlatformPumpHostEvents();
  if ( PlatformQueueIsEmpty() && !g_platform_quit_requested )
    usleep(10000);
  return 1;
}

void __stdcall Sleep(DWORD dwMilliseconds)
{
  if ( dwMilliseconds )
    usleep(dwMilliseconds * 1000u);
}

BOOL __stdcall ClientToScreen(HWND hWnd, LPPOINT lpPoint)
{
  struct SDL_Window *window;

  if ( !lpPoint )
    return 0;
  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    lpPoint->x += window->x;
    lpPoint->y += window->y;
  }
  return 1;
}

void Platform_ResetInputFallbackState(void)
{
  g_platform_host_mouse_x = 0;
  g_platform_host_mouse_y = 0;
  g_platform_host_mouse_delta_x = 0;
  g_platform_host_mouse_delta_y = 0;
  g_platform_host_mouse_primary = 0;
  g_platform_host_mouse_secondary = 0;
  memset(g_platform_host_keyboard_state, 0, sizeof(g_platform_host_keyboard_state));
}

void Platform_ReadInputFallbackState(
  int *mouse_delta_x,
  int *mouse_delta_y,
  signed char *mouse_button_primary,
  signed char *mouse_button_secondary,
  signed char *keyboard_state,
  int keyboard_state_size)
{
  PlatformPumpHostEvents();
  if ( mouse_delta_x )
    *mouse_delta_x = g_platform_host_mouse_delta_x;
  if ( mouse_delta_y )
    *mouse_delta_y = g_platform_host_mouse_delta_y;
  if ( mouse_button_primary )
    *mouse_button_primary = g_platform_host_mouse_primary;
  if ( mouse_button_secondary )
    *mouse_button_secondary = g_platform_host_mouse_secondary;
  if ( keyboard_state && keyboard_state_size > 0 )
  {
    size_t copy_size;

    copy_size = (size_t)keyboard_state_size;
    if ( copy_size > sizeof(g_platform_host_keyboard_state) )
      copy_size = sizeof(g_platform_host_keyboard_state);
    memcpy(keyboard_state, g_platform_host_keyboard_state, copy_size);
  }
  g_platform_host_mouse_delta_x = 0;
  g_platform_host_mouse_delta_y = 0;
}
