#ifndef CLASH95_PLATFORM_SDL_H
#define CLASH95_PLATFORM_SDL_H

/*
 * SDL-target platform shim for the recovered Clash codebase.
 *
 * The decompiled translation unit still speaks in Win32/DirectDraw-era types,
 * but the port target is SDL. This header keeps the old surface area compiling
 * while rebinding the stable window / surface / cursor / palette concepts to
 * SDL-style opaque handles instead of Windows SDK types.
 *
 * The DirectDraw COM-shaped adapters remain for now because the recovered
 * render path still calls through legacy vtables. Those adapters are the seam
 * to replace with SDL renderer / texture / surface backends in later waves.
 */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __stdcall
#define __stdcall
#endif

#ifndef __fastcall
#define __fastcall
#endif

#ifndef __thiscall
#define __thiscall
#endif

#ifndef WINAPI
#define WINAPI
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef PASCAL
#define PASCAL
#endif

#define CLASH_PLATFORM_USES_SDL 1

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Palette SDL_Palette;
typedef struct SDL_Cursor SDL_Cursor;

typedef void VOID;
typedef char CHAR;
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR;
typedef char *LPCH;
typedef signed char SCHAR;
typedef unsigned char UCHAR;
typedef short SHORT;
typedef unsigned short USHORT;
typedef int INT;
typedef unsigned int UINT;
typedef uintptr_t UINT_PTR;
typedef long LONG;
typedef unsigned long ULONG;
typedef size_t SIZE_T;
typedef uintptr_t ULONG_PTR;
typedef uintptr_t DWORD_PTR;
typedef intptr_t LONG_PTR;
typedef int BOOL;
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef float FLOAT;
typedef double DOUBLE;
typedef LONG HRESULT;
typedef DWORD COLORREF;
typedef UINT MMRESULT;
typedef void *LPVOID;
typedef LPVOID PVOID;
typedef const void *LPCVOID;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef const WCHAR *LPCWSTR;
typedef void (*FARPROC)(void);

typedef LONG_PTR LPARAM;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LRESULT;

typedef void *HANDLE;
typedef SDL_Window *HWND;
typedef void *HINSTANCE;
typedef void *HMODULE;
typedef void *HGLOBAL;
typedef void *HMENU;
typedef SDL_Cursor *HCURSOR;
typedef SDL_Surface *HICON;
typedef void *HBRUSH;
typedef void *HGDIOBJ;
typedef SDL_Surface *HDC;
typedef void *HRSRC;
typedef HANDLE HWAVEOUT;
typedef SDL_Surface *HBITMAP;
typedef SDL_Palette *HPALETTE;
typedef WORD ATOM;
typedef int HFILE;

typedef struct _GUID {
  DWORD Data1;
  WORD Data2;
  WORD Data3;
  BYTE Data4[8];
} GUID;

typedef GUID IID;

typedef union _LARGE_INTEGER {
  __extension__ struct {
    DWORD LowPart;
    LONG HighPart;
  };
  long long QuadPart;
} LARGE_INTEGER;

typedef struct tagPOINT {
  LONG x;
  LONG y;
} POINT, *LPPOINT;

typedef struct tagRECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT, tagRECT, *LPRECT;

typedef struct tagMSG {
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD time;
  POINT pt;
} MSG, *LPMSG;

typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagWNDCLASSA {
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCSTR lpszMenuName;
  LPCSTR lpszClassName;
} WNDCLASSA, WNDCLASS;

typedef struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
} BITMAPINFO;

typedef struct _OVERLAPPED {
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  __extension__ union {
    __extension__ struct {
      DWORD Offset;
      DWORD OffsetHigh;
    };
    LPVOID Pointer;
  };
  HANDLE hEvent;
} OVERLAPPED;
typedef OVERLAPPED *LPOVERLAPPED;
typedef DWORD *LPDWORD;

typedef struct tagSYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME;

void Platform_PresentRecoveredIndexedSurfaceHandle(void *surface_handle, const uint32_t *palette_entries);
void Platform_ResetPresentedFrameDump(void);
void Platform_DebugPrimeInputFallbackMouseState(int x, int y, int primary_down, int secondary_down);
void Platform_DebugPrimeInputFallbackMouseDelta(int delta_x, int delta_y, int primary_down, int secondary_down);
void Platform_DebugPrimeInputFallbackMousePulse(
  int delta_x,
  int delta_y,
  int primary_down,
  int secondary_down,
  int read_count);
void Platform_DebugPrimeInputFallbackKeyPulse(int scan_code, int read_count);

typedef struct _SECURITY_ATTRIBUTES {
  DWORD nLength;
  LPVOID lpSecurityDescriptor;
  BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _CPINFO {
  UINT MaxCharSize;
  BYTE DefaultChar[2];
  BYTE LeadByte[12];
} CPINFO, *LPCPINFO;

typedef struct _STARTUPINFOA {
  DWORD cb;
  LPSTR lpReserved;
  LPSTR lpDesktop;
  LPSTR lpTitle;
  DWORD dwX;
  DWORD dwY;
  DWORD dwXSize;
  DWORD dwYSize;
  DWORD dwXCountChars;
  DWORD dwYCountChars;
  DWORD dwFillAttribute;
  DWORD dwFlags;
  WORD wShowWindow;
  WORD cbReserved2;
  BYTE *lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD dwProcessId;
  DWORD dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);
int __stdcall ICSendMessage(DWORD hic, DWORD msg, DWORD dw1, DWORD dw2, DWORD dw3);

typedef struct _RTL_CRITICAL_SECTION {
  LPVOID DebugInfo;
  LONG LockCount;
  LONG RecursionCount;
  HANDLE OwningThread;
  HANDLE LockSemaphore;
  ULONG_PTR SpinCount;
} CRITICAL_SECTION, *LPCRITICAL_SECTION;

typedef struct tagWAVEFORMATEX {
  WORD wFormatTag;
  WORD nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD nBlockAlign;
  WORD wBitsPerSample;
  WORD cbSize;
} WAVEFORMATEX, *LPWAVEFORMATEX;

typedef const WAVEFORMATEX *LPCWAVEFORMATEX;

typedef struct wavehdr_tag {
  LPSTR lpData;
  DWORD dwBufferLength;
  DWORD dwBytesRecorded;
  DWORD_PTR dwUser;
  DWORD dwFlags;
  DWORD dwLoops;
  struct wavehdr_tag *lpNext;
  DWORD_PTR reserved;
} WAVEHDR, *LPWAVEHDR;

typedef struct tagWAVEOUTCAPSA {
  WORD wMid;
  WORD wPid;
  DWORD vDriverVersion;
  CHAR szPname[32];
  DWORD dwFormats;
  WORD wChannels;
  WORD wReserved1;
  DWORD dwSupport;
} WAVEOUTCAPSA, *LPWAVEOUTCAPSA;

typedef struct _WIN32_FIND_DATAA {
  DWORD dwFileAttributes;
  DWORD ftCreationTimeLow;
  DWORD ftCreationTimeHigh;
  DWORD ftLastAccessTimeLow;
  DWORD ftLastAccessTimeHigh;
  DWORD ftLastWriteTimeLow;
  DWORD ftLastWriteTimeHigh;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD dwReserved0;
  DWORD dwReserved1;
  CHAR cFileName[260];
  CHAR cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _TIME_ZONE_INFORMATION {
  LONG Bias;
  WCHAR StandardName[32];
  SYSTEMTIME StandardDate;
  LONG StandardBias;
  WCHAR DaylightName[32];
  SYSTEMTIME DaylightDate;
  LONG DaylightBias;
} TIME_ZONE_INFORMATION, *LPTIME_ZONE_INFORMATION;

typedef struct _EXCEPTION_RECORD {
  DWORD ExceptionCode;
  DWORD ExceptionFlags;
  struct _EXCEPTION_RECORD *ExceptionRecord;
  LPVOID ExceptionAddress;
  DWORD NumberParameters;
  ULONG_PTR ExceptionInformation[15];
} EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

typedef struct _FLOATING_SAVE_AREA {
  DWORD ControlWord;
  DWORD StatusWord;
} FLOATING_SAVE_AREA;

typedef struct _CONTEXT {
  DWORD ContextFlags;
  FLOATING_SAVE_AREA FloatSave;
} CONTEXT, *PCONTEXT;

typedef struct _EXCEPTION_POINTERS {
  EXCEPTION_RECORD *ExceptionRecord;
  PCONTEXT ContextRecord;
} EXCEPTION_POINTERS;

typedef LONG (__stdcall *LPTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *ExceptionInfo);

typedef struct _EXCEPTION_REGISTRATION_RECORD {
  struct _EXCEPTION_REGISTRATION_RECORD *Next;
  FARPROC Handler;
} _EXCEPTION_REGISTRATION_RECORD;

typedef struct _NT_TIB {
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
  LPVOID StackBase;
  LPVOID StackLimit;
  LPVOID SubSystemTib;
  union {
    LPVOID FiberData;
    DWORD Version;
  };
  LPVOID ArbitraryUserPointer;
  struct _NT_TIB *Self;
} NT_TIB, *PNT_TIB;

typedef struct _TEB {
  NT_TIB NtTib;
} TEB, *PTEB;

typedef struct _MEMORYSTATUS {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  SIZE_T dwTotalPhys;
  SIZE_T dwAvailPhys;
  SIZE_T dwTotalPageFile;
  SIZE_T dwAvailPageFile;
  SIZE_T dwTotalVirtual;
  SIZE_T dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

/* This header precedes recovered_abi.h, so use direct GNU asm labels here. */
#if defined(__cplusplus) && (defined(__GNUC__) || defined(__clang__))
static inline PTEB NtCurrentTeb(void) __asm__("NtCurrentTeb");
#endif
#ifndef CLASH95_FAKE_TEB_GCC_SYMBOL
#define CLASH95_FAKE_TEB_GCC_SYMBOL "fake_teb.0"
#endif
static inline PTEB NtCurrentTeb(void)
{
#if defined(__cplusplus) && defined(__clang__)
  static TEB fake_teb __asm__("NtCurrentTeb.fake_teb");
#elif defined(__cplusplus) && defined(__GNUC__)
  static TEB fake_teb __asm__(CLASH95_FAKE_TEB_GCC_SYMBOL);
#else
  static TEB fake_teb;
#endif
  return &fake_teb;
}

typedef struct IUnknownVtbl {
  HRESULT (__stdcall *QueryInterface)(void *self, const void *riid, void *out_object);
  ULONG (__stdcall *AddRef)(void *self);
  ULONG (__stdcall *Release)(void *self);
} IUnknownVtbl;

typedef struct IUnknown {
  IUnknownVtbl *lpVtbl;
} IUnknown;

typedef struct IDirectDraw {
  IUnknownVtbl *lpVtbl;
} IDirectDraw, *LPDIRECTDRAW;

typedef struct IDirectDrawSurface {
  IUnknownVtbl *lpVtbl;
} IDirectDrawSurface, *LPDIRECTDRAWSURFACE;

typedef struct IDirectDrawSurface2 {
  IUnknownVtbl *lpVtbl;
} IDirectDrawSurface2, *LPDIRECTDRAWSURFACE2;

typedef struct IDirectInput {
  IUnknownVtbl *lpVtbl;
} IDirectInput, *LPDIRECTINPUT;

typedef struct IDirectInputDevice {
  IUnknownVtbl *lpVtbl;
} IDirectInputDevice, *LPDIRECTINPUTDEVICE;

typedef HWAVEOUT *LPHWAVEOUT;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef WM_PAINT
#define WM_PAINT 0x000F
#endif

#ifndef WM_ACTIVATEAPP
#define WM_ACTIVATEAPP 0x001C
#endif

/*
 * SDL-owned compatibility wrappers exported to the recovered gameplay code.
 * Keeping these declarations at the seam avoids redeclaring the same
 * Win32-shaped surface inside clash95.c.
 */
ATOM __stdcall RegisterClassA(const WNDCLASSA *lpWndClass);
HWND __stdcall CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
LRESULT __stdcall DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall DispatchMessageA(const MSG *lpMsg);
BOOL __stdcall GetClientRect(HWND hWnd, LPRECT lpRect);
HDC __stdcall GetDC(HWND hWnd);
int __stdcall GetDeviceCaps(HDC hdc, int index);
COLORREF __stdcall GetPixel(HDC hdc, int x, int y);
COLORREF __stdcall SetPixel(HDC hdc, int x, int y, COLORREF color);
BOOL __stdcall SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);
BOOL __stdcall EqualRect(const RECT *lprc1, const RECT *lprc2);
BOOL __stdcall IsRectEmpty(const RECT *lprc);
BOOL __stdcall IntersectRect(LPRECT lprcDst, const RECT *lprcSrc1, const RECT *lprcSrc2);
HWND __stdcall GetForegroundWindow(void);
BOOL __stdcall GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
HGDIOBJ __stdcall GetStockObject(int i);
HCURSOR __stdcall LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);
HICON __stdcall LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName);
int __stdcall MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
BOOL __stdcall PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
void __stdcall PostQuitMessage(int nExitCode);
int __stdcall ReleaseDC(HWND hWnd, HDC hDC);
HDC __stdcall CreateCompatibleDC(HDC hdc);
BOOL __stdcall DeleteDC(HDC hdc);
BOOL __stdcall DeleteObject(HGDIOBJ ho);
int __stdcall GetObjectA(HANDLE h, int c, LPVOID pv);
HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ h);
BOOL __stdcall StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop);
int __stdcall StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, const void *lpBits, const BITMAPINFO *lpbmi, UINT iUsage, DWORD rop);
HANDLE __stdcall LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad);
BOOL __stdcall ShowWindow(HWND hWnd, int nCmdShow);
BOOL __stdcall TranslateMessage(const MSG *lpMsg);
BOOL __stdcall UpdateWindow(HWND hWnd);
BOOL __stdcall ValidateRect(HWND hWnd, const RECT *lpRect);
BOOL __stdcall WaitMessage(void);
DWORD __stdcall timeGetTime(void);
DWORD __stdcall GetTickCount(void);
DWORD __stdcall GetVersion(void);
BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
void __stdcall GlobalMemoryStatus(LPMEMORYSTATUS lpBuffer);
void __stdcall InitializeCriticalSection(LPCRITICAL_SECTION criticalSection);
void __stdcall DeleteCriticalSection(LPCRITICAL_SECTION criticalSection);
HANDLE __stdcall CreateEventA(
  LPSECURITY_ATTRIBUTES eventAttributes,
  BOOL manualReset,
  BOOL initialState,
  LPCSTR name);
BOOL __stdcall CloseHandle(HANDLE object);
BOOL __stdcall PulseEvent(HANDLE eventHandle);

/* Legacy Video-for-Windows import surface retained by recovered media code. */
int AVIFileInit(void);
int __stdcall AVIFileOpenA(DWORD file, DWORD name, DWORD mode, DWORD handler);
int __stdcall AVIFileInfoA(DWORD file, DWORD info, DWORD size);
int __stdcall AVIFileGetStream(DWORD file, DWORD stream, DWORD type, DWORD index);
int __stdcall AVIFileRelease(int file);
int __stdcall AVIStreamBeginStreaming(DWORD stream, DWORD start, DWORD end, DWORD rate);
int __stdcall AVIStreamInfoA(DWORD stream, DWORD info, DWORD size);
int __stdcall AVIStreamReadFormat(DWORD stream, DWORD position, DWORD format, DWORD size);
int __stdcall AVIStreamFindSample(DWORD stream, DWORD position, DWORD flags);
int __fastcall AVIStreamRead(
  DWORD blockAlign,
  DWORD byteOffset,
  DWORD stream,
  DWORD byteCount,
  DWORD sampleCount,
  DWORD startSample,
  DWORD destination,
  DWORD bytesRead,
  DWORD samplesRead);
int __stdcall AVIStreamRelease(int stream);
HMODULE __stdcall GetModuleHandleA(LPCSTR lpModuleName);
HRESULT __stdcall DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
UINT __stdcall GetDriveTypeA(LPCSTR lpRootPathName);
void __stdcall OutputDebugStringA(LPCSTR lpOutputString);
void __stdcall Sleep(DWORD dwMilliseconds);
BOOL __stdcall ClientToScreen(HWND hWnd, LPPOINT lpPoint);
void Platform_ResetInputFallbackState(void);
void Platform_ReadInputFallbackState(
  int *mouse_delta_x,
  int *mouse_delta_y,
  signed char *mouse_button_primary,
  signed char *mouse_button_secondary,
  signed char *keyboard_state,
  int keyboard_state_size,
  int *mouse_delta_is_host_pixels);

#ifdef __cplusplus
}
#endif

#endif
