/* Test-only compatibility definitions retain the C symbol names used by recovered code. */
#ifndef CLASH95_TEST_COMPAT_DECLS_H
#define CLASH95_TEST_COMPAT_DECLS_H
#include "../../src/platform/platform_sdl.h"
#include "../../src/compatibility/defs.h"
#ifdef __cplusplus
extern "C" {
#endif
int _no_support_loaded(void);
DWORD __stdcall GetTimeZoneInformation(LPTIME_ZONE_INFORMATION info);
int getenv_(void);
int _brktime_(_DWORD value, _DWORD context);
int wcstombs_(_DWORD destination, _DWORD source);
int _I8D(void);
int _GetThreadData_(void);
int _ReallocThreadData_(void);
int _RemoveThreadData_(void);
int ismbclegal_(_DWORD first, _DWORD second);
_DWORD j___NTAddFileHandle_(void);
int __cdecl CRT_RunGuardedStaticLocalInit(void);
HMODULE __stdcall LoadLibraryA(LPCSTR library_name);
FARPROC __stdcall GetProcAddress(HMODULE module, LPCSTR procedure_name);
HANDLE __stdcall CreateThread(LPSECURITY_ATTRIBUTES attributes, SIZE_T stack_size, LPTHREAD_START_ROUTINE start, LPVOID parameter, DWORD flags, LPDWORD thread_id);
HANDLE __stdcall GetCurrentThread(void);
BOOL __stdcall WriteFile(HANDLE file, LPCVOID buffer, DWORD bytes_to_write, LPDWORD bytes_written, LPOVERLAPPED overlapped);
LONG __stdcall UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *info);
LPTOP_LEVEL_EXCEPTION_FILTER __stdcall SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER filter);
int CRT_ConstructThreadDataBlock(void);
int CRT_DestroyThreadDataBlock(void);
int CRT_DispatchRegisteredFpeHandler(void);
int _fatal_runtime_error_(void);
int _NTConsoleOutput_(void);
int _AddThreadData_(void);
int _InitThreadData_(void);
int _NTRemoveFileHandle_(void);
int j___NTRemoveFileHandle_(void);
_DWORD j___NTAddFileHandle__0(void);
void endthread_(void);
int calloc_(int count, int size);
extern int (*g_RenderHook)(int a1, char a2, DWORD a3);
#ifdef __cplusplus
}
#endif
#endif
