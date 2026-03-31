#ifndef CLASH95_WINDOWS_H
#define CLASH95_WINDOWS_H

#include <stddef.h>
#include <stdint.h>

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

typedef void VOID;
typedef char CHAR;
typedef wchar_t WCHAR;
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
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HMODULE;
typedef HANDLE HGLOBAL;
typedef HANDLE HMENU;
typedef HANDLE HCURSOR;
typedef HANDLE HICON;
typedef HANDLE HBRUSH;
typedef HANDLE HGDIOBJ;
typedef HANDLE HDC;
typedef HANDLE HRSRC;
typedef HANDLE HWAVEOUT;
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
  struct {
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
  union {
    struct {
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

static inline PTEB NtCurrentTeb(void)
{
  static TEB fake_teb;
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

#endif
