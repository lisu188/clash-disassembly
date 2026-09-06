/* Coverage-only compatibility seams. These preserve the historical harness
 * behavior for weak Win32/CRT imports without entering the recovered source. */

#include "../../src/platform/platform_sdl.h"
#include "../../src/compatibility/defs.h"

#include "test_compat_decls.h"

#include <stdint.h>
#include <string.h>

int _no_support_loaded(void) { return 0; }

static int cov_render_hook_noop(int a1, char a2, DWORD a3) {
  (void)a1;
  (void)a2;
  (void)a3;
  return 0;
}

int (*g_RenderHook)(int a1, char a2, DWORD a3) = cov_render_hook_noop;

DWORD __stdcall GetTimeZoneInformation(LPTIME_ZONE_INFORMATION info) {
  if (info != NULL) {
    memset(info, 0, sizeof(*info));
  }
  return 0;
}

int getenv_(void) { return 0; }

int _brktime_(_DWORD value, _DWORD context) {
  (void)value;
  (void)context;
  return 0;
}

int wcstombs_(_DWORD destination, _DWORD source) {
  (void)destination;
  (void)source;
  return 0;
}

int _I8D(void) { return 0; }

static _DWORD cov_thread_data_block[256];

int _GetThreadData_(void) {
  memset(cov_thread_data_block, 0, sizeof(cov_thread_data_block));
  return (int)(intptr_t)cov_thread_data_block;
}

int _ReallocThreadData_(void) {
  return (int)(intptr_t)cov_thread_data_block;
}

int _RemoveThreadData_(void) { return 0; }

int ismbclegal_(_DWORD first, _DWORD second) {
  (void)first;
  (void)second;
  return 1;
}

_DWORD j___NTAddFileHandle_(void) { return 0; }
int __cdecl CRT_RunGuardedStaticLocalInit(void) { return 0; }
HMODULE __stdcall LoadLibraryA(LPCSTR library_name) {
  (void)library_name;
  return 0;
}

FARPROC __stdcall GetProcAddress(HMODULE module, LPCSTR procedure_name) {
  (void)module;
  (void)procedure_name;
  return 0;
}

HANDLE __stdcall CreateThread(LPSECURITY_ATTRIBUTES attributes,
                              SIZE_T stack_size,
                              LPTHREAD_START_ROUTINE start,
                              LPVOID parameter,
                              DWORD flags,
                              LPDWORD thread_id) {
  (void)attributes;
  (void)stack_size;
  (void)start;
  (void)parameter;
  (void)flags;
  if (thread_id != NULL) {
    *thread_id = 0;
  }
  return 0;
}

HANDLE __stdcall GetCurrentThread(void) { return 0; }

BOOL __stdcall WriteFile(HANDLE file,
                         LPCVOID buffer,
                         DWORD bytes_to_write,
                         LPDWORD bytes_written,
                         LPOVERLAPPED overlapped) {
  (void)file;
  (void)buffer;
  (void)bytes_to_write;
  (void)bytes_written;
  (void)overlapped;
  return 0;
}

LONG __stdcall UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *info) {
  (void)info;
  return 0;
}

LPTOP_LEVEL_EXCEPTION_FILTER __stdcall
SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER filter) {
  (void)filter;
  return 0;
}

int CRT_ConstructThreadDataBlock(void) { return 0; }
int CRT_DestroyThreadDataBlock(void) { return 0; }
int CRT_DispatchRegisteredFpeHandler(void) { return 0; }
int _fatal_runtime_error_(void) { return 0; }
int _NTConsoleOutput_(void) { return 0; }
int _AddThreadData_(void) { return 1; }
int _InitThreadData_(void) { return 0; }
int _NTRemoveFileHandle_(void) { return 0; }
int j___NTRemoveFileHandle_(void) { return 0; }
_DWORD j___NTAddFileHandle__0(void) { return 0; }
void endthread_(void) {}

int calloc_(int count, int size) {
  static char cov_arena[1 << 20];
  static int cov_offset = 0;
  int bytes = (count > 0 ? count : 1) * (size > 0 ? size : 1);
  char *result;

  if (bytes <= 0 || bytes > 8192) {
    bytes = 8192;
  }
  if (cov_offset + bytes > (int)sizeof(cov_arena)) {
    cov_offset = 0;
  }
  result = cov_arena + cov_offset;
  cov_offset += bytes;
  memset(result, 0, (size_t)bytes);
  return (int)(intptr_t)result;
}
