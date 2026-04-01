#include "../defs.h"
#include "../platform_sdl.h"

#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

int Mem_Alloc(int a1, int a2, char a3, _DWORD a4);
int sub_48703D(int a1, __lock *a2, int a3);
extern void *lpTlsValue;

/*
 * Narrow compile-time quarantine for late runtime helpers that still need
 * asm-backed reconstruction. These are outside the user-priority gameplay
 * path and are kept isolated so clash95.c can continue compiling.
 */

unsigned __int16 __ES__;
unsigned __int16 __DS__;
__lock unk_51A638;

#define COMPAT_TLS_SLOT_COUNT 64
#define COMPAT_TLS_SEARCH_START 3u
#define COMPAT_FILE_ATTRIBUTE_READONLY 0x1u
#define COMPAT_FILE_ATTRIBUTE_DIRECTORY 0x10u
#define COMPAT_INVALID_FILE_ATTRIBUTES ((DWORD)-1)

static DWORD g_compat_last_error;
static LPVOID g_compat_tls_slots[COMPAT_TLS_SLOT_COUNT];
static unsigned char g_compat_tls_slot_in_use[COMPAT_TLS_SLOT_COUNT];

static void CompatSetLastErrorFromErrno(void)
{
  if ( errno )
    g_compat_last_error = (DWORD)errno;
  else
    g_compat_last_error = (DWORD)EIO;
}

static DWORD CompatResolveOsErrorCode(DWORD fallback)
{
  if ( g_compat_last_error )
    return g_compat_last_error;
  if ( fallback )
    return fallback;
  if ( errno )
    return (DWORD)errno;
  return (DWORD)EIO;
}

static int CompatMapOsErrorToErrno(DWORD error_code)
{
  switch ( error_code )
  {
    case 0:
      return 0;
    case 2:
    case 3:
      return ENOENT;
    case 5:
      return EACCES;
    case 6:
      return EBADF;
    case 8:
    case 12:
    case 14:
      return ENOMEM;
    case 13:
      return EACCES;
    case 16:
    case 32:
      return EBUSY;
    case 17:
    case 80:
    case 183:
      return EEXIST;
    case 20:
    case 267:
      return ENOTDIR;
    case 21:
      return EISDIR;
    case 22:
    case 87:
      return EINVAL;
    case 28:
    case 112:
      return ENOSPC;
    case 145:
      return ENOTEMPTY;
    case 258:
      return EAGAIN;
    default:
      if ( error_code <= 255 )
        return (int)error_code;
      return EIO;
  }
}

static int CompatTlsSlotIsValid(DWORD dwTlsIndex)
{
  return dwTlsIndex < COMPAT_TLS_SLOT_COUNT && g_compat_tls_slot_in_use[dwTlsIndex] != 0;
}

DWORD __stdcall GetLastError(void)
{
  return g_compat_last_error;
}

void __stdcall SetLastError(DWORD dwErrCode)
{
  g_compat_last_error = dwErrCode;
}

int __cdecl _set_errno_dos_(DWORD error_code)
{
  errno = CompatMapOsErrorToErrno(CompatResolveOsErrorCode(error_code));
  return -1;
}

int __cdecl _set_errno_nt_(DWORD error_code)
{
  errno = CompatMapOsErrorToErrno(CompatResolveOsErrorCode(error_code));
  return -1;
}

DWORD __stdcall TlsAlloc(void)
{
  DWORD index;

  for ( index = COMPAT_TLS_SEARCH_START; index < COMPAT_TLS_SLOT_COUNT; ++index )
  {
    if ( !g_compat_tls_slot_in_use[index] )
    {
      g_compat_tls_slot_in_use[index] = 1;
      g_compat_tls_slots[index] = 0;
      g_compat_last_error = 0;
      return index;
    }
  }
  for ( index = 0; index < COMPAT_TLS_SEARCH_START; ++index )
  {
    if ( !g_compat_tls_slot_in_use[index] )
    {
      g_compat_tls_slot_in_use[index] = 1;
      g_compat_tls_slots[index] = 0;
      g_compat_last_error = 0;
      return index;
    }
  }
  g_compat_last_error = (DWORD)ENOMEM;
  return (DWORD)-1;
}

BOOL __stdcall TlsFree(DWORD dwTlsIndex)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_tls_slot_in_use[dwTlsIndex] = 0;
  g_compat_tls_slots[dwTlsIndex] = 0;
  g_compat_last_error = 0;
  return 1;
}

LPVOID __stdcall TlsGetValue(DWORD dwTlsIndex)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_last_error = 0;
  return g_compat_tls_slots[dwTlsIndex];
}

BOOL __stdcall TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_tls_slots[dwTlsIndex] = lpTlsValue;
  g_compat_last_error = 0;
  return 1;
}

BOOL __stdcall DeleteFileA(LPCSTR lpFileName)
{
  if ( !lpFileName || !*lpFileName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  if ( unlink(lpFileName) == 0 )
  {
    g_compat_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

BOOL __stdcall CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
  (void)lpSecurityAttributes;
  if ( !lpPathName || !*lpPathName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  if ( mkdir(lpPathName, 0777) == 0 )
  {
    g_compat_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

BOOL __stdcall RemoveDirectoryA(LPCSTR lpPathName)
{
  if ( !lpPathName || !*lpPathName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  if ( rmdir(lpPathName) == 0 )
  {
    g_compat_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

DWORD __stdcall GetFileAttributesA(LPCSTR lpFileName)
{
  DWORD attributes;
  struct stat st;

  if ( !lpFileName || !*lpFileName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return COMPAT_INVALID_FILE_ATTRIBUTES;
  }
  if ( stat(lpFileName, &st) != 0 )
  {
    CompatSetLastErrorFromErrno();
    return COMPAT_INVALID_FILE_ATTRIBUTES;
  }
  attributes = 0;
  if ( S_ISDIR(st.st_mode) )
    attributes |= COMPAT_FILE_ATTRIBUTE_DIRECTORY;
  if ( access(lpFileName, W_OK) != 0 )
    attributes |= COMPAT_FILE_ATTRIBUTE_READONLY;
  g_compat_last_error = 0;
  return attributes;
}

void __noreturn ExitProcess(UINT uExitCode)
{
  exit((int)uExitCode);
}

DWORD __stdcall GetCurrentProcessId(void)
{
  return (DWORD)getpid();
}

DWORD __stdcall GetCurrentThreadId(void)
{
  /*
   * The current recovered host only runs the decompiled core on one thread.
   * Mirror the process id here until real thread creation/resume is rebuilt.
   */
  return (DWORD)getpid();
}

BOOL __stdcall CloseHandle(HANDLE hObject)
{
  if ( !hObject )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_last_error = 0;
  return 1;
}

DWORD __stdcall ResumeThread(HANDLE hThread)
{
  if ( !hThread )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return (DWORD)-1;
  }
  g_compat_last_error = 0;
  return 0;
}

void __stdcall InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
  if ( !lpCriticalSection )
    return;
  memset(lpCriticalSection, 0, sizeof(*lpCriticalSection));
  lpCriticalSection->LockCount = -1;
}

void __stdcall EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
  if ( !lpCriticalSection )
    return;
  ++lpCriticalSection->LockCount;
  ++lpCriticalSection->RecursionCount;
  lpCriticalSection->OwningThread = (HANDLE)(uintptr_t)GetCurrentThreadId();
}

void __stdcall LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
  if ( !lpCriticalSection )
    return;
  if ( lpCriticalSection->RecursionCount > 0 )
    --lpCriticalSection->RecursionCount;
  if ( lpCriticalSection->LockCount >= -1 )
    --lpCriticalSection->LockCount;
  if ( lpCriticalSection->RecursionCount == 0 )
    lpCriticalSection->OwningThread = 0;
}

void __stdcall DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{
  if ( !lpCriticalSection )
    return;
  memset(lpCriticalSection, 0, sizeof(*lpCriticalSection));
}

/*
 * These are the lowest-risk CRT aliases still missing from the link surface.
 * They are kept here instead of being spread through gameplay code so later
 * runtime reconstruction can replace them in one place.
 */
int __thiscall nfree_(_DWORD a1)
{
  if ( a1 && a1 != (_DWORD)-1 )
    free((void *)(uintptr_t)a1);
  return 0;
}

__int64 __fastcall CRT_GetBootstrapThreadData(_DWORD a1, _DWORD a2)
{
  (void)a1;
  return __PAIR64__(a2, lpTlsValue);
}

int __fastcall CRT_RegisterFinalizableObject(_DWORD a1, _DWORD a2)
{
  /*
   * clash95.asm marks 0x473ED5 as an exact thunk to sub_48703D and shows
   * the target body using the fixed lock object at 0x51A638 rather than the
   * incoming edx value. Keeping the wrapper here removes the unresolved
   * thunk without spreading CRT bootstrap glue through clash95.c.
   */
  return sub_48703D((int)a1, &unk_51A638, (int)a2);
}

__int64 __thiscall j_Mem_Alloc(_DWORD a1)
{
  /*
   * clash95.asm marks 0x4730FB as a collapsed 5-byte thunk. The map binds
   * that thunk to j_Mem_Alloc, and the jump target is the recovered
   * Mem_Alloc body at 0x461C00.
   */
  return (unsigned int)Mem_Alloc((int)a1, 0, 0, 0);
}

int __fastcall strcmp_(_DWORD a1, _DWORD a2)
{
  const char *lhs;
  const char *rhs;

  lhs = (const char *)(uintptr_t)a1;
  rhs = (const char *)(uintptr_t)a2;
  if ( lhs == rhs )
    return 0;
  if ( !lhs )
    return -1;
  if ( !rhs )
    return 1;
  return strcmp(lhs, rhs);
}

int __cdecl sprintf_(char *buffer, const char *format, ...)
{
  int result;
  va_list args;

  if ( !buffer || !format )
    return -1;
  va_start(args, format);
  result = vsprintf(buffer, format, args);
  va_end(args);
  return result;
}

int __cdecl vsprintf_(char *buffer, const char *format, ...)
{
  int result;
  va_list args;

  if ( !buffer || !format )
    return -1;
  va_start(args, format);
  result = vsprintf(buffer, format, args);
  va_end(args);
  return result;
}

int __thiscall fclose_(_DWORD a1)
{
  FILE *stream;

  if ( !a1 || a1 == (_DWORD)-1 )
    return 0;
  stream = (FILE *)(uintptr_t)a1;
  return fclose(stream);
}

int fwrite_(const void *buffer, int size, int file_handle, int count)
{
  FILE *stream;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  stream = (FILE *)(uintptr_t)file_handle;
  return (int)fwrite(buffer, (size_t)size, (size_t)count, stream);
}

int fread_(void *buffer, int size, int file_handle, int count)
{
  FILE *stream;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  stream = (FILE *)(uintptr_t)file_handle;
  return (int)fread(buffer, (size_t)size, (size_t)count, stream);
}

int __fastcall strncmp_(_DWORD a1, _DWORD a2)
{
  return strcmp_(a1, a2);
}

int __fastcall tolower_(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return tolower((unsigned __int8)a1);
}

int __thiscall toupper_(_DWORD a1)
{
  return toupper((unsigned __int8)a1);
}

int __thiscall towupper_(_DWORD a1)
{
  return towupper((wint_t)(unsigned __int16)a1);
}

errno_t __cdecl _set_errno_(int value)
{
  errno = value;
  return value;
}

int __fastcall sub_4697E0(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int sub_4849EE(void)
{
  return 0;
}

void __noreturn sub_4842DF(int a1, int a2)
{
  (void)a1;
  (void)a2;
  abort();
}

int sub_48469F(void)
{
  return 0;
}

/*
 * Map/asm corroborate these as collapsed one-byte `retn` placeholders.
 * Returning zero here is a compile/link quarantine choice, not a claim that
 * the original callers depended on a specific non-void result.
 */
int nullsub_1(void)
{
  return 0;
}

int __thiscall nullsub_2(_DWORD a1)
{
  (void)a1;
  return 0;
}

int __thiscall nullsub_3(_DWORD a1)
{
  (void)a1;
  return 0;
}

int nullsub_4(void)
{
  return 0;
}

int nullsub_5(void)
{
  return 0;
}

int __fastcall nullsub_6(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __thiscall nullsub_7(_DWORD a1)
{
  (void)a1;
  return 0;
}

_DWORD nullsub_8(void)
{
  return 0;
}

int nullsub_9(void)
{
  return 0;
}

int nullsub_10(void)
{
  return 0;
}

int __fastcall nullsub_11(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int nullsub_15(void)
{
  return 0;
}

int nullsub_16(void)
{
  return 0;
}

int nullsub_19(void)
{
  return 0;
}

int nullsub_23(void)
{
  return 0;
}

int nullsub_24(void)
{
  return 0;
}

int nullsub_29(void)
{
  return 0;
}

int nullsub_30(void)
{
  return 0;
}

int nullsub_32(void)
{
  return 0;
}
