#include "platform_sdl.h"

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

static WNDCLASSA g_platform_window_class;
static int g_platform_has_window_class;
static HWND g_platform_foreground_window;
static struct SDL_Surface g_platform_default_surface = { 640, 480 };
static struct SDL_Surface g_platform_default_icon = { 32, 32 };
static struct SDL_Cursor g_platform_default_cursor = { 0 };
static int g_platform_stock_brush;
static int g_platform_module_handle_token;
static MSG g_platform_message_queue[PLATFORM_QUEUE_CAPACITY];
static size_t g_platform_message_head;
static size_t g_platform_message_tail;
static int g_platform_quit_requested;
static int g_platform_quit_code;

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
    window->visible = nCmdShow != 0;
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
