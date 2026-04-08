#include "../defs.h"
#include "../platform_sdl.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

int Mem_Alloc(int a1, int a2, char a3, _DWORD a4);
int sub_48703D(int a1, __lock *a2, int a3);
int sub_406740(void);
void sub_40AEC0(void);
int sub_40BD40(_BYTE *a1);
void sub_40C1F0(int a1, _BYTE *a2, int a3, char a4, DWORD a5);
int sub_40C5E0(void);
_DWORD __stdcall GetLastError(void);
extern __int64 (__fastcall *off_51A568)(_DWORD, _DWORD);
extern int dword_51A648;
extern void *lpTlsValue;

static const signed char k_DosErrnoMap[20] = {
  0, 9, 1, 1, 11, 6, 4, 5, 5, 5, 2, 3, -1, -1, 7, 9, 6, 8, 1, -1
};

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
#define COMPAT_WSL_GAME_ROOT "/mnt/c/clash"

static DWORD g_compat_last_error;
static LPVOID g_compat_tls_slots[COMPAT_TLS_SLOT_COUNT];
static unsigned char g_compat_tls_slot_in_use[COMPAT_TLS_SLOT_COUNT];

typedef int (*CompatCtorFn)(void *this_ptr);

typedef struct CompatWcppArrayStoreDesc {
  unsigned char kind;
  unsigned char unk1;
  unsigned char unk2;
  unsigned char unk3;
  CompatCtorFn ctor;
  void *copy_ctor;
  void *dtor;
  int stride;
  const char *type_name;
} CompatWcppArrayStoreDesc;

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

static void CompatNormalizePathSlashes(const char *input, char *output, size_t output_size)
{
  size_t index;

  if ( !output_size )
    return;
  if ( !input )
  {
    output[0] = 0;
    return;
  }
  index = 0;
  while ( input[index] && index + 1 < output_size )
  {
    output[index] = input[index] == '\\' ? '/' : input[index];
    ++index;
  }
  output[index] = 0;
}

static int CompatAppendPathComponent(char *path, size_t path_size, const char *component)
{
  size_t path_len;
  size_t component_len;

  if ( !path || !component )
    return 0;
  if ( !*component )
    return 1;
  path_len = strlen(path);
  component_len = strlen(component);
  if ( path_len && path[path_len - 1] != '/' )
  {
    if ( path_len + 1 >= path_size )
      return 0;
    path[path_len++] = '/';
    path[path_len] = 0;
  }
  if ( path_len + component_len >= path_size )
    return 0;
  memcpy(path + path_len, component, component_len + 1);
  return 1;
}

static int CompatTranslatePathToWsl(const char *input, char *output, size_t output_size)
{
  char normalized[PATH_MAX];
  char current[PATH_MAX];
  const char *cursor;
  struct stat st;
  int current_is_dir;

  if ( !input || !*input || !output || !output_size )
    return 0;
  CompatNormalizePathSlashes(input, normalized, sizeof(normalized));
  if ( !normalized[0] )
    return 0;
  if ( stat(normalized, &st) == 0 )
  {
    Compat_CopyPrefixN(output, normalized, (unsigned int)strlen(normalized) + 1);
    return 1;
  }
  if ( isalpha((unsigned __int8)normalized[0]) && normalized[1] == ':' )
  {
    snprintf(current, sizeof(current), "/mnt/%c", (char)tolower((unsigned __int8)normalized[0]));
    cursor = normalized + 2;
    if ( *cursor == '/' )
      ++cursor;
  }
  else if ( normalized[0] == '/' )
  {
    Compat_CopyPrefixN(current, "/", 2);
    cursor = normalized + 1;
  }
  else
  {
    Compat_CopyPrefixN(current, COMPAT_WSL_GAME_ROOT, sizeof(COMPAT_WSL_GAME_ROOT));
    cursor = normalized;
  }
  current_is_dir = stat(current, &st) == 0 && S_ISDIR(st.st_mode);
  while ( *cursor )
  {
    char component[PATH_MAX];
    char candidate[PATH_MAX];
    size_t component_len;

    while ( *cursor == '/' )
      ++cursor;
    if ( !*cursor )
      break;
    component_len = 0;
    while ( cursor[component_len] && cursor[component_len] != '/' )
      ++component_len;
    if ( component_len + 1 > sizeof(component) )
      return 0;
    memcpy(component, cursor, component_len);
    component[component_len] = 0;
    cursor += component_len;
    if ( !strcmp(component, ".") )
      continue;
    if ( !strcmp(component, "..") )
    {
      if ( !CompatAppendPathComponent(current, sizeof(current), component) )
        return 0;
      current_is_dir = stat(current, &st) == 0 && S_ISDIR(st.st_mode);
      continue;
    }
    if ( current_is_dir )
    {
      DIR *dir_stream;
      struct dirent *entry;
      int matched;

      Compat_CopyPrefixN(candidate, current, (unsigned int)strlen(current) + 1);
      if ( !CompatAppendPathComponent(candidate, sizeof(candidate), component) )
        return 0;
      if ( stat(candidate, &st) == 0 )
      {
        Compat_CopyPrefixN(current, candidate, (unsigned int)strlen(candidate) + 1);
        current_is_dir = S_ISDIR(st.st_mode);
        continue;
      }
      matched = 0;
      dir_stream = opendir(current);
      if ( dir_stream )
      {
        while ( (entry = readdir(dir_stream)) != 0 )
        {
          if ( !strcasecmp(entry->d_name, component) )
          {
            matched = 1;
            Compat_CopyPrefixN(component, entry->d_name, (unsigned int)strlen(entry->d_name) + 1);
            break;
          }
        }
        closedir(dir_stream);
      }
      if ( matched )
      {
        Compat_CopyPrefixN(candidate, current, (unsigned int)strlen(current) + 1);
        if ( !CompatAppendPathComponent(candidate, sizeof(candidate), component) )
          return 0;
        Compat_CopyPrefixN(current, candidate, (unsigned int)strlen(candidate) + 1);
        current_is_dir = stat(current, &st) == 0 && S_ISDIR(st.st_mode);
        continue;
      }
    }
    if ( !CompatAppendPathComponent(current, sizeof(current), component) )
      return 0;
    current_is_dir = stat(current, &st) == 0 && S_ISDIR(st.st_mode);
  }
  Compat_CopyPrefixN(output, current, (unsigned int)strlen(current) + 1);
  return 1;
}

int Compat_CanOpenReadPath(const char *path)
{
  char translated_path[PATH_MAX];
  const char *effective_path;
  int fd;

  if ( !path || !*path )
    return 0;
  effective_path = path;
  if ( CompatTranslatePathToWsl(path, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  fd = open(effective_path, O_RDONLY | O_BINARY);
  if ( fd < 0 )
    return 0;
  close(fd);
  return 1;
}

char *Compat_StrrchrChar(const char *text, int ch)
{
  if ( !text )
    return 0;
  return strrchr(text, ch);
}

char *Compat_StruprAsciiInPlace(char *text)
{
  unsigned char *cursor;

  if ( !text )
    return 0;
  cursor = (unsigned char *)text;
  while ( *cursor )
  {
    *cursor = (unsigned char)toupper(*cursor);
    ++cursor;
  }
  return text;
}

void Compat_CopyPrefixN(char *dest, const char *src, unsigned int count)
{
  unsigned int index;

  if ( !dest || !count )
    return;
  if ( !src )
  {
    memset(dest, 0, count);
    return;
  }
  for ( index = 0; index < count; ++index )
  {
    dest[index] = src[index];
    if ( !src[index] )
    {
      memset(dest + index + 1, 0, count - index - 1);
      return;
    }
  }
}

int Compat_WcppCtorArrayStorage1m(void *base, int count, const void *descriptor)
{
  const CompatWcppArrayStoreDesc *desc;
  unsigned char *cursor;
  int index;

  if ( !base )
    return 0;
  desc = (const CompatWcppArrayStoreDesc *)descriptor;
  if ( !desc || desc->stride <= 0 || count <= 0 )
    return (int)(uintptr_t)base;
  cursor = (unsigned char *)base;
  for ( index = 0; index < count; ++index )
  {
    if ( desc->ctor )
      desc->ctor(cursor + index * desc->stride);
  }
  return (int)(uintptr_t)base;
}

int Compat_WcppCtorArrayStorage1s(void *block, int count, const void *descriptor)
{
  unsigned char *data;

  if ( !block )
    return 0;
  *(int *)block = count;
  data = (unsigned char *)block + 4;
  return Compat_WcppCtorArrayStorage1m(data, count, descriptor);
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
  char translated_path[PATH_MAX];
  const char *effective_path;

  if ( !lpFileName || !*lpFileName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpFileName;
  if ( CompatTranslatePathToWsl(lpFileName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( unlink(effective_path) == 0 )
  {
    g_compat_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

BOOL __stdcall CreateDirectoryA(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
  char translated_path[PATH_MAX];
  const char *effective_path;

  (void)lpSecurityAttributes;
  if ( !lpPathName || !*lpPathName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpPathName;
  if ( CompatTranslatePathToWsl(lpPathName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( mkdir(effective_path, 0777) == 0 )
  {
    g_compat_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

BOOL __stdcall RemoveDirectoryA(LPCSTR lpPathName)
{
  char translated_path[PATH_MAX];
  const char *effective_path;

  if ( !lpPathName || !*lpPathName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpPathName;
  if ( CompatTranslatePathToWsl(lpPathName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( rmdir(effective_path) == 0 )
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
  char translated_path[PATH_MAX];
  const char *effective_path;
  struct stat st;

  if ( !lpFileName || !*lpFileName )
  {
    g_compat_last_error = (DWORD)EINVAL;
    return COMPAT_INVALID_FILE_ATTRIBUTES;
  }
  effective_path = lpFileName;
  if ( CompatTranslatePathToWsl(lpFileName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( stat(effective_path, &st) != 0 )
  {
    CompatSetLastErrorFromErrno();
    return COMPAT_INVALID_FILE_ATTRIBUTES;
  }
  attributes = 0;
  if ( S_ISDIR(st.st_mode) )
    attributes |= COMPAT_FILE_ATTRIBUTE_DIRECTORY;
  if ( access(effective_path, W_OK) != 0 )
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

int __fastcall sub_473ED5(_DWORD a1, _DWORD a2)
{
  _DWORD *node;

  (void)a2;
  node = (_DWORD *)(uintptr_t)a1;
  off_51A568(a1, a1);
  *node = dword_51A648;
  dword_51A648 = (int)(uintptr_t)node;
  return 0;
}

__int64 __fastcall sub_485374(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return (unsigned int)(uintptr_t)lpTlsValue;
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

int __cdecl _set_errno_dos_(unsigned int code)
{
  int mapped;

  if ( code == 0x7B )
    mapped = 1;
  else if ( code == 0xCE )
    mapped = 9;
  else if ( code == 0xB7 )
    mapped = 7;
  else
    mapped = k_DosErrnoMap[code <= 0x13 ? code : 0x13];
  errno = mapped;
  return -1;
}

int __cdecl _set_errno_nt_(_DWORD ignored)
{
  (void)ignored;
  return _set_errno_dos_(GetLastError());
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

/*
 * Executable-bootstrap quarantine:
 *
 * The current smoke executable still links the whole recovered translation
 * unit, so some unresolved runtime helpers remain live through retained
 * tables/sections even though the smoke path never executes them. Keep these
 * narrow placeholder definitions isolated here until their usercall/register
 * ABIs are reconstructed from asm strongly enough for the authentic boot path.
 */

int Render_SetResourceHandle(int a1, int a2)
{
  int previous_handle;

  previous_handle = *(_DWORD *)(a1 + 0xCC);
  *(_DWORD *)(a1 + 0xCC) = a2;
  return previous_handle;
}

int Render_DrawSprite(void)
{
  return sub_406740();
}

void Render_LoadResourceSprite_v2(void)
{
  sub_40AEC0();
}

int Render_LoadResourceSprite_v3(_BYTE *a1)
{
  return sub_40BD40(a1);
}

void Render_LoadResourceSprite_v4(int a1, _BYTE *a2, int a3, char a4, DWORD a5)
{
  sub_40C1F0(a1, a2, a3, a4, a5);
}

int Render_CreateSprite(void)
{
  return sub_40C5E0();
}

signed int Unit_GetSquadCount(int a1)
{
  unsigned char *slot;
  int squad_count;

  slot = (unsigned char *)(uintptr_t)(a1 + 6);
  squad_count = 0;
  while ( squad_count < 10 )
  {
    if ( *(short *)slot == -1 )
      break;
    ++squad_count;
    slot += 31;
  }
  return squad_count;
}

int __cdecl j__nfree_(void)
{
  return 0;
}

int __cdecl j_j__nfree_(void)
{
  return 0;
}

int __fastcall _wcpp_4_dtor_array_store__(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return (int)a1;
}

int __fastcall _wcpp_4_ctor_array__(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return (int)a1;
}

int __fastcall sub_476322(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

__int64 __fastcall nmalloc_(_DWORD a1, _DWORD a2)
{
  void *block;

  /*
   * `_nmalloc_` is a raw custom allocator in the original binary, not a
   * zeroing CRT helper. The decompiled extra argument is register noise from
   * the lost usercall ABI, so keep the compatibility stub size-driven and let
   * repaired callers supply the real size explicitly.
   */
  (void)a2;
  if ( !a1 )
    return 0;
  block = malloc((size_t)a1);
  return (unsigned int)(uintptr_t)block;
}

int __fastcall memset_(_DWORD a1, _DWORD a2)
{
  if ( a1 )
    *(unsigned char *)(uintptr_t)a1 = (unsigned char)a2;
  return (int)a1;
}

int __fastcall _FiniRtns(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int _freefp_(void)
{
  return 0;
}

int _chktty_(void)
{
  return 0;
}

int _allocfp_(void)
{
  return 0;
}

int tell_(void)
{
  return 0;
}

int __fastcall lseek_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __fastcall _flush_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int _NTAtMaxFiles_(void)
{
  return 0;
}

int __fastcall stricmp_(_DWORD a1, _DWORD a2)
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
  return strcasecmp(lhs, rhs);
}

int __cdecl strrchr_(void)
{
  return 0;
}

int __fastcall strupr_(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return (int)(uintptr_t)Compat_StruprAsciiInPlace((char *)(uintptr_t)a1);
}

int __fastcall strncpy_(_DWORD a1, _DWORD a2)
{
  char *dest;
  const char *src;

  dest = (char *)(uintptr_t)a1;
  src = (const char *)(uintptr_t)a2;
  if ( !dest )
    return (int)a1;
  if ( !src )
  {
    *dest = 0;
    return (int)a1;
  }
  Compat_CopyPrefixN(dest, src, (unsigned int)(strlen(src) + 1));
  return (int)a1;
}

__int64 __fastcall ftell_(_DWORD a1, _DWORD a2)
{
  /*
   * Quarantine only: the original helper operates on the private stream
   * runtime, not host libc FILE*. Returning zero keeps the retained boot-path
   * code linkable until `_allocfp_`, `tell_`, and `_flush_` are reconstructed.
   */
  (void)a1;
  (void)a2;
  return 0;
}

int __fastcall setvbuf_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __thiscall fflush_(_DWORD a1)
{
  (void)a1;
  return 0;
}

int __cdecl _NTGetFakeHandle_(_DWORD a1, _DWORD a2, _DWORD a3)
{
  (void)a1;
  (void)a2;
  (void)a3;
  return -1;
}

int __fastcall isatty_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __cdecl _SetIOMode_(_DWORD a1, _DWORD a2, _DWORD a3)
{
  (void)a1;
  (void)a2;
  (void)a3;
  return 0;
}

int __fastcall sub_488A97(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int _ioalloc_(void)
{
  return 0;
}

int __thiscall _wcpp_4_corrupted_stack__(_DWORD a1)
{
  (void)a1;
  return 0;
}

__int64 __thiscall _wcpp_4_pgm_thread__(_DWORD a1)
{
  (void)a1;
  return 0;
}

int _wcpp_4_stab_trav_init__(void)
{
  return 0;
}

int _wcpp_4_stab_trav_next__(void)
{
  return 0;
}

int __fastcall _wcpp_4_stab_trav_move__(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __fastcall _wcpp_4_dtor_array__(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return (int)a1;
}

int __cdecl _wcpp_4_ctor_array_storage_1m__(void)
{
  return 0;
}

int __cdecl _wcpp_4_ctor_array_storage_1s__(void)
{
  return 0;
}

int __fastcall wctomb_(_DWORD a1, _DWORD a2)
{
  char *output;

  output = (char *)(uintptr_t)a1;
  if ( !output )
    return 0;
  if ( (unsigned int)a2 < 0x80 )
    *output = (char)a2;
  else
    *output = '?';
  return 1;
}

int __fastcall _clib_ulltoa_(_DWORD a1, _DWORD a2)
{
  sprintf((char *)(uintptr_t)a2, "%u", (unsigned int)a1);
  return (int)a2;
}

int __fastcall sub_4B5A33(_DWORD a1, _DWORD a2)
{
  sprintf((char *)(uintptr_t)a2, "%d", (int)a1);
  return (int)a2;
}

HANDLE __stdcall CreateFileA(
  LPCSTR lpFileName,
  DWORD dwDesiredAccess,
  DWORD dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD dwCreationDisposition,
  DWORD dwFlagsAndAttributes,
  HANDLE hTemplateFile)
{
  int flags;
  int fd;
  char translated_path[PATH_MAX];
  const char *effective_path;

  (void)dwShareMode;
  (void)lpSecurityAttributes;
  (void)dwFlagsAndAttributes;
  (void)hTemplateFile;
  if ( !lpFileName )
    return (HANDLE)-1;
  effective_path = lpFileName;
  if ( CompatTranslatePathToWsl(lpFileName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  flags = O_BINARY;
  if ( (dwDesiredAccess & 0x40000000u) != 0 && (dwDesiredAccess & 0x80000000u) != 0 )
    flags |= O_RDWR;
  else if ( (dwDesiredAccess & 0x40000000u) != 0 )
    flags |= O_WRONLY;
  else
    flags |= O_RDONLY;
  if ( dwCreationDisposition == 2 )
    flags |= O_CREAT | O_EXCL;
  else if ( dwCreationDisposition == 4 )
    flags |= O_CREAT | O_TRUNC;
  else if ( dwCreationDisposition == 5 )
    flags |= O_TRUNC;
  else if ( dwCreationDisposition == 1 )
    flags |= O_CREAT;
  fd = open(effective_path, flags, 0666);
  if ( fd < 0 )
  {
    CompatSetLastErrorFromErrno();
    return (HANDLE)-1;
  }
  g_compat_last_error = 0;
  return (HANDLE)(uintptr_t)fd;
}

void __fastcall __writefsdword(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
}
