#include "platform_sdl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

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
static MSG g_platform_message_queue[PLATFORM_QUEUE_CAPACITY];
static size_t g_platform_message_head;
static size_t g_platform_message_tail;
static int g_platform_quit_requested;
static int g_platform_quit_code;

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
  if ( !lpMsg )
    return 0;
  if ( lpMsg->message == PLATFORM_WM_QUIT )
  {
    g_platform_quit_requested = 1;
    g_platform_quit_code = (int)lpMsg->wParam;
    return 0;
  }
  if ( g_platform_has_window_class && (void *)g_platform_window_class.lpfnWndProc == (void *)Platform_MainWindowProc )
    return Platform_MainWindowProc(0, lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
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
  return 0;
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
  return 1;
}

BOOL __stdcall ClientToScreen(HWND hWnd, LPPOINT lpPoint)
{
  (void)hWnd;
  (void)lpPoint;
  return 1;
}
