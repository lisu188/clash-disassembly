#include "../defs.h"
#include "../platform_sdl.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <execinfo.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
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
void *Mem_Realloc(void *a1, int a2, int a3);
int CRT_DeleteFile(int a1, int a2);
int CRT_RegisterFinalizer(int a1, __lock *a2, int a3);
int Menu_DrawFrameBackdrop(void);
int DLX_GetSpriteForChar(int a1, unsigned __int16 a2);
__int16 DLX_GetSpriteWidth(int a1, unsigned __int16 a2);
__int16 DLX_GetSpriteHeight(int a1, unsigned __int16 a2);
void WorldMap_EnableFrameRedraw(void);
int TextSprite_MeasureStringExtent(_BYTE *a1);
void TextSprite_BuildOrLoadCachedFont(int a1, _BYTE *a2, int a3, char a4, DWORD a5);
int Font_InitGlyphFallbackTablesForLanguage(void);
int Res_ProbeGfxFileExists(CHAR *a1, int a2, DWORD a3, int a4);
int FileSystem_ResolveReadPath(char *a1, int a2);
_DWORD *DLXSpriteSet_Load(_DWORD *a1, const void *a2);
char DLXSpriteSet_DrawText(int a1, int a2, int a3, unsigned __int8 *a4);
int __fastcall Compat_FileSystemQueryRelease(int a1, int *a2);
int Compat_QuerySkipBytes(int a1, int a2);
signed int CRT_GetOsHandleFromFd(int a1, int a2);
char CRT_FillFindDataRecord(int a1, _DWORD *a2);
_DWORD * Rules_CreateFact(signed int a1);
int Rules_PrintMultifieldRange(int result, int a2, int a3, int a4, int a5);
signed int Rules_CheckLiteralSlotValueConstraint(int *a1, int a2);
_DWORD * Lexer_FindSlotWithIndex(int a1, int a2, _DWORD *a3);
char * Str_Append(const char *a1, char *a2, unsigned int *a3, int *a4);
char * Rules_SavePPBuffer(char *result);
int Rules_BackupPPBuffer(void);
signed int Rules_ImportExportConflictMessage(int a1, int a2, int a3);
errno_t __cdecl _set_errno_(int value);
typedef struct TextSpriteResourceSlotRecord {
  const char *source_stem;
  int cached_sprite_set;
  unsigned __int16 line_step_word;
  unsigned __int16 glyph_spacing_word;
} TextSpriteResourceSlotRecord;
TextSpriteResourceSlotRecord *TextSprite_GetResourceSlot(int slot_index);
_DWORD __stdcall GetLastError(void);
extern __int64 (__fastcall *off_51A568)(_DWORD, _DWORD);
extern int dword_51A648;
extern void *lpTlsValue;
extern int g_FileSystemMountTable[11];
extern int g_ActiveTextSpriteSlot;
extern _UNKNOWN *g_RenderDevice;
extern char IsTable[256];

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
_UNKNOWN g_Audio_DriverModuleTableBase;

#define COMPAT_TLS_SLOT_COUNT 64
#define COMPAT_TLS_SEARCH_START 3u
#define COMPAT_FILE_ATTRIBUTE_READONLY 0x1u
#define COMPAT_FILE_ATTRIBUTE_DIRECTORY 0x10u
#define COMPAT_INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define COMPAT_WSL_GAME_ROOT "/mnt/c/clash"
#define COMPAT_LOW32_ALLOC_MAGIC 0xC10A110Cu

/* Shared with platform_sdl_runtime.c, which owns GetLastError/SetLastError. */
extern DWORD g_platform_last_error;
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

typedef struct CompatLow32AllocHeader {
  size_t mapped_size;
  unsigned int magic;
  int used_mmap;
  struct CompatLow32AllocHeader *next_free;
} CompatLow32AllocHeader;

typedef struct CompatLow32Arena {
  CompatLow32AllocHeader *mapping;
  unsigned char *base;
  size_t capacity;
  size_t offset;
  struct CompatLow32Arena *next;
} CompatLow32Arena;

typedef struct CompatFileRuntimeMeta {
  int next_link;
  int stream_ptr;
  int buffer_base;
  int buffer_state;
  int fd_index;
  int mode_char;
  int buffer_size;
} CompatFileRuntimeMeta;

typedef struct CompatFileRuntimeStream {
  int current_ptr;
  int remaining_count;
  int meta;
  unsigned char flags0;
  unsigned char flags1;
  unsigned char reserved14;
  unsigned char reserved15;
  int fd_index;
  int reserved20;
  int reserved24;
} CompatFileRuntimeStream;

typedef struct CompatFindHandle {
  DIR *dir;
  char directory[PATH_MAX];
  char pattern[PATH_MAX];
} CompatFindHandle;

#define COMPAT_FIND_HANDLE_SLOTS 64
#define COMPAT_STREAM_HANDLE_SLOTS 256
#define COMPAT_EVENT_HANDLE_SLOTS 128
#define COMPAT_EVENT_HANDLE_BASE 0x45560000u
#define COMPAT_EVENT_MAGIC 0x45564E54u
#define COMPAT_WAIT_OBJECT_0 0u
#define COMPAT_WAIT_TIMEOUT 258u
#define COMPAT_WAIT_FAILED 0xFFFFFFFFu
#define COMPAT_WAIT_INFINITE 0xFFFFFFFFu
#define COMPAT_SIGNAL_SLOT_COUNT 13

static CompatFindHandle *g_compat_find_handles[COMPAT_FIND_HANDLE_SLOTS];
static int g_compat_stream_handles[COMPAT_STREAM_HANDLE_SLOTS];
static CompatLow32Arena *g_compat_low32_arenas;
static CompatLow32AllocHeader *g_compat_low32_free_blocks;
static size_t g_compat_low32_arena_count;
static size_t g_compat_low32_arena_capacity_total;
static size_t g_compat_low32_arena_offset_total;
static size_t g_compat_low32_arena_free_bytes;
static size_t g_compat_low32_arena_reused_bytes;

typedef struct CompatEventHandle {
  unsigned int magic;
  int manual_reset;
  int signaled;
} CompatEventHandle;

static CompatEventHandle *g_compat_event_handles[COMPAT_EVENT_HANDLE_SLOTS];

typedef struct CompatTimeb {
  int time_value;
  unsigned short milliseconds;
  short timezone_minutes;
  short dst_flag;
} CompatTimeb;

static unsigned int CompatEventHandleIndexFromHandle(HANDLE handle)
{
  unsigned int public_handle;

  public_handle = (unsigned int)(uintptr_t)handle;
  if ( public_handle <= COMPAT_EVENT_HANDLE_BASE
    || public_handle > COMPAT_EVENT_HANDLE_BASE + COMPAT_EVENT_HANDLE_SLOTS )
  {
    return 0;
  }
  return public_handle - COMPAT_EVENT_HANDLE_BASE;
}

static HANDLE CompatRegisterEventHandle(CompatEventHandle *event_handle)
{
  unsigned int slot_index;

  for ( slot_index = 0; slot_index < COMPAT_EVENT_HANDLE_SLOTS; ++slot_index )
  {
    if ( !g_compat_event_handles[slot_index] )
    {
      g_compat_event_handles[slot_index] = event_handle;
      return (HANDLE)(uintptr_t)(COMPAT_EVENT_HANDLE_BASE + slot_index + 1);
    }
  }
  return 0;
}

static void CompatUnregisterEventHandle(HANDLE handle)
{
  unsigned int public_index;

  public_index = CompatEventHandleIndexFromHandle(handle);
  if ( public_index )
    g_compat_event_handles[public_index - 1] = 0;
}

static CompatEventHandle *CompatGetEventHandle(HANDLE handle)
{
  CompatEventHandle *event_handle;
  unsigned int public_index;

  public_index = CompatEventHandleIndexFromHandle(handle);
  if ( !public_index )
    return 0;
  event_handle = g_compat_event_handles[public_index - 1];
  if ( !event_handle || event_handle->magic != COMPAT_EVENT_MAGIC )
    return 0;
  return event_handle;
}

static intptr_t g_compat_signal_handlers[COMPAT_SIGNAL_SLOT_COUNT] = {
  1,
  2,
  1,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  2,
  1,
};

static int g_compat_signal_os_codes[COMPAT_SIGNAL_SLOT_COUNT] = {
  -1,
  -1,
  -1,
  (int)0xC000001D,
  (int)0xC000013A,
  (int)0xC0000005,
  (int)0xC000013A,
  (int)0xC000013A,
  -1,
  -1,
  -1,
  (int)0xC0000094,
  (int)0xC0000095,
};

static unsigned char g_compat_ctrl_handler_installed;

#define COMPAT_READABLE_RANGE_COUNT 512

typedef struct CompatReadableRange {
  uintptr_t start;
  uintptr_t end;
} CompatReadableRange;

static CompatReadableRange g_compat_readable_ranges[COMPAT_READABLE_RANGE_COUNT];
static size_t g_compat_readable_range_count;
static const CompatReadableRange *g_compat_last_readable_range;
static int g_compat_readable_ranges_loaded;

static void CompatInvalidateReadableRanges(void)
{
  g_compat_readable_range_count = 0;
  g_compat_last_readable_range = 0;
  g_compat_readable_ranges_loaded = 0;
}

static void CompatRefreshReadableRanges(void)
{
  FILE *maps_file;
  char line[256];

  g_compat_readable_range_count = 0;
  g_compat_readable_ranges_loaded = 1;
  maps_file = fopen("/proc/self/maps", "r");
  if ( !maps_file )
    return;
  while ( fgets(line, sizeof(line), maps_file) )
  {
    unsigned long long start;
    unsigned long long end;
    char permissions[5];

    if ( sscanf(line, "%llx-%llx %4s", &start, &end, permissions) != 3 )
      continue;
    if ( permissions[0] != 'r' || start >= end )
      continue;
    if ( g_compat_readable_range_count >= COMPAT_READABLE_RANGE_COUNT )
      break;
    g_compat_readable_ranges[g_compat_readable_range_count].start = (uintptr_t)start;
    g_compat_readable_ranges[g_compat_readable_range_count].end = (uintptr_t)end;
    ++g_compat_readable_range_count;
  }
  fclose(maps_file);
}

static const CompatReadableRange *CompatFindReadableRange(uintptr_t address)
{
  size_t left;
  size_t right;

  if ( !g_compat_readable_ranges_loaded )
    CompatRefreshReadableRanges();
  if ( g_compat_last_readable_range
    && address >= g_compat_last_readable_range->start
    && address < g_compat_last_readable_range->end )
  {
    return g_compat_last_readable_range;
  }
  left = 0;
  right = g_compat_readable_range_count;
  while ( left < right )
  {
    size_t middle;
    const CompatReadableRange *range;

    middle = left + (right - left) / 2;
    range = &g_compat_readable_ranges[middle];
    if ( address < range->start )
      right = middle;
    else if ( address >= range->end )
      left = middle + 1;
    else
    {
      g_compat_last_readable_range = range;
      return range;
    }
  }
  return 0;
}

static long CompatPageSize(void)
{
  static long page_size;

  if ( !page_size )
  {
    page_size = sysconf(_SC_PAGESIZE);
    if ( page_size <= 0 )
      page_size = 4096;
  }
  return page_size;
}

static uintptr_t CompatPointerPage(const void *ptr)
{
  uintptr_t address;

  address = (uintptr_t)ptr;
  return address & ~((uintptr_t)CompatPageSize() - 1u);
}

static int CompatPointerPageReadable(uintptr_t page_address)
{
  if ( !page_address )
    return 0;
  return CompatFindReadableRange(page_address) != 0;
}

static int CompatPointerReadable(const void *ptr)
{
  if ( !ptr )
    return 0;
  return CompatPointerPageReadable(CompatPointerPage(ptr));
}

static int CompatSafeStrcmp(const char *lhs, const char *rhs)
{
  size_t index;
  uintptr_t lhs_page;
  uintptr_t rhs_page;
  int lhs_readable;
  int rhs_readable;

  if ( lhs == rhs )
    return 0;
  if ( !lhs )
    return -1;
  if ( !rhs )
    return 1;
  lhs_page = (uintptr_t)-1;
  rhs_page = (uintptr_t)-1;
  lhs_readable = 0;
  rhs_readable = 0;
  for ( index = 0; index < 4096; ++index )
  {
    unsigned char left_char;
    unsigned char right_char;
    uintptr_t current_lhs_page;
    uintptr_t current_rhs_page;

    current_lhs_page = CompatPointerPage(lhs + index);
    if ( current_lhs_page != lhs_page )
    {
      lhs_page = current_lhs_page;
      lhs_readable = CompatPointerPageReadable(lhs_page);
    }
    if ( !lhs_readable )
      return CompatPointerReadable(rhs + index) ? -1 : 0;
    current_rhs_page = CompatPointerPage(rhs + index);
    if ( current_rhs_page != rhs_page )
    {
      rhs_page = current_rhs_page;
      rhs_readable = CompatPointerPageReadable(rhs_page);
    }
    if ( !rhs_readable )
      return 1;
    left_char = (unsigned char)lhs[index];
    right_char = (unsigned char)rhs[index];
    if ( left_char != right_char )
      return (int)left_char - (int)right_char;
    if ( !left_char )
      return 0;
  }
  return 0;
}

static int CompatSignalNeedsCtrlHandler(int signal_number)
{
  intptr_t handler_value;

  handler_value = g_compat_signal_handlers[signal_number];
  return handler_value != 2 && handler_value != 3;
}

/*
 * Watcom signal registration wrapper used by retained startup code.
 * Keep the handler table and ctrl-handler gating behavior, but quarantine
 * the platform-specific console/FPU details here while SDL/WSL remains the
 * only supported runtime target.
 */
intptr_t __fastcall CRT_RegisterSignalHandler(int signal_number, intptr_t handler_value)
{
  intptr_t previous_handler;

  if ( signal_number < 1 || signal_number > 12 )
  {
    _set_errno_(9);
    return 3;
  }

  previous_handler = g_compat_signal_handlers[signal_number];
  g_compat_signal_handlers[signal_number] = handler_value;

  if ( signal_number == 2 && handler_value != 2 && handler_value != 3 && g_compat_signal_os_codes[signal_number] )
  {
    /* Original code also touched the Watcom FPU mask via _control87_. */
  }

  g_compat_ctrl_handler_installed =
    CompatSignalNeedsCtrlHandler(4) || CompatSignalNeedsCtrlHandler(7);

  return previous_handler;
}

int ftime_(void *time_buffer)
{
  struct timeval current_time;
  CompatTimeb *buffer;

  buffer = (CompatTimeb *)time_buffer;
  if ( !buffer )
    return _set_errno_(EINVAL);

  if ( gettimeofday(&current_time, 0) != 0 )
    return _set_errno_(errno);

  buffer->time_value = (int)current_time.tv_sec;
  buffer->milliseconds = (unsigned short)(current_time.tv_usec / 1000);
  buffer->timezone_minutes = 0;
  buffer->dst_flag = 0;
  return 0;
}

int time_(void)
{
  return (int)time(0);
}

int system_(const char *command)
{
  return system(command);
}

/*
 * Watcom runtime thunks that the authentic save-load path now reaches while
 * staying inside the recovered executable wedge.
 */
_DWORD CRT_ProbeStackFrame(_DWORD size)
{
  (void)size;
  return 0;
}

void *plib_malloc__1(size_t size)
{
  return malloc(size);
}

int j_rand_(void)
{
  return rand() & 0x7FFF;
}

void j_srand_(unsigned int seed)
{
  srand(seed);
}

int rand_(void)
{
  return rand() & 0x7FFF;
}

void srand_(unsigned int seed)
{
  srand(seed);
}

char *strlwr_(char *text)
{
  unsigned char *cursor;

  if ( !text )
    return 0;
  cursor = (unsigned char *)text;
  while ( *cursor )
  {
    *cursor = (unsigned char)tolower(*cursor);
    ++cursor;
  }
  return text;
}

void *memmove_(void *destination, const void *source, size_t byte_count)
{
  return memmove(destination, source, byte_count);
}

int atoi_(const char *text)
{
  const unsigned char *cursor;
  unsigned char sign_char;
  int value;

  if ( !text )
    return 0;
  cursor = (const unsigned char *)text;
  while ( (IsTable[(unsigned char)(*cursor + 1)] & 2) != 0 )
    ++cursor;
  sign_char = *cursor;
  if ( sign_char == '+' || sign_char == '-' )
    ++cursor;
  value = 0;
  while ( (IsTable[(unsigned char)(*cursor + 1)] & 0x20) != 0 )
  {
    value *= 10;
    value += *cursor - '0';
    ++cursor;
  }
  if ( sign_char == '-' )
    value = -value;
  return value;
}

double strtod_(const char *text, char **endptr)
{
  return strtod(text, endptr);
}

/*
 * Several parser helpers are already recovered in clash95.c under raw address
 * names. Keep the public symbol bridges here until those bodies are renamed in
 * place.
 */
_DWORD *Module_AllocList(signed int a1)
{
  return Rules_CreateFact(a1);
}

int Lexer_OutputFieldRange(int result, int a2, int a3, int a4, int a5)
{
  return Rules_PrintMultifieldRange(result, a2, a3, a4, a5);
}

signed int Lexer_CheckValueList(int *a1, int a2)
{
  return Rules_CheckLiteralSlotValueConstraint(a1, a2);
}

_DWORD *Lexer_FindTemplateSlot(int a1, int a2, _DWORD *a3)
{
  return Lexer_FindSlotWithIndex(a1, a2, a3);
}

char *IO_OutWriteToken(char *result)
{
  return Rules_SavePPBuffer(result);
}

int IO_OutNewline(void)
{
  return Rules_BackupPPBuffer();
}

signed int Lexer_WarnImpliedTemplate(int a1, int a2, int a3)
{
  return Rules_ImportExportConflictMessage(a1, a2, a3);
}

static void CompatSetLastErrorFromErrno(void)
{
  if ( errno )
    g_platform_last_error = (DWORD)errno;
  else
    g_platform_last_error = (DWORD)EIO;
}

static int CompatTlsSlotIsValid(DWORD dwTlsIndex)
{
  return dwTlsIndex < COMPAT_TLS_SLOT_COUNT && g_compat_tls_slot_in_use[dwTlsIndex] != 0;
}

static int CompatFindHandleIndexFromHandle(HANDLE hFindFile)
{
  uintptr_t raw_index;

  raw_index = (uintptr_t)hFindFile;
  if ( !raw_index || raw_index > COMPAT_FIND_HANDLE_SLOTS )
    return -1;
  if ( !g_compat_find_handles[raw_index - 1] )
    return -1;
  return (int)(raw_index - 1);
}

static HANDLE CompatRegisterFindHandle(CompatFindHandle *handle)
{
  int slot_index;

  for ( slot_index = 0; slot_index < COMPAT_FIND_HANDLE_SLOTS; ++slot_index )
  {
    if ( !g_compat_find_handles[slot_index] )
    {
      g_compat_find_handles[slot_index] = handle;
      return (HANDLE)(uintptr_t)(slot_index + 1);
    }
  }
  g_platform_last_error = (DWORD)ENOMEM;
  return (HANDLE)-1;
}

static void CompatRegisterStreamHandle(int stream_ptr)
{
  int slot_index;

  if ( !stream_ptr )
    return;
  for ( slot_index = 0; slot_index < COMPAT_STREAM_HANDLE_SLOTS; ++slot_index )
  {
    if ( g_compat_stream_handles[slot_index] == stream_ptr )
      return;
    if ( !g_compat_stream_handles[slot_index] )
    {
      g_compat_stream_handles[slot_index] = stream_ptr;
      return;
    }
  }
}

static void CompatUnregisterStreamHandle(int stream_ptr)
{
  int slot_index;

  if ( !stream_ptr )
    return;
  for ( slot_index = 0; slot_index < COMPAT_STREAM_HANDLE_SLOTS; ++slot_index )
  {
    if ( g_compat_stream_handles[slot_index] == stream_ptr )
    {
      g_compat_stream_handles[slot_index] = 0;
      return;
    }
  }
}

static int CompatIsRegisteredStreamHandle(int stream_ptr)
{
  int slot_index;

  if ( !stream_ptr )
    return 0;
  for ( slot_index = 0; slot_index < COMPAT_STREAM_HANDLE_SLOTS; ++slot_index )
  {
    if ( g_compat_stream_handles[slot_index] == stream_ptr )
      return 1;
  }
  return 0;
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

static int CompatWildcardMatchNoCase(const char *pattern, const char *text)
{
  unsigned char pattern_char;
  unsigned char text_char;

  if ( !pattern || !text )
    return 0;
  if ( !strcmp(pattern, "*.*") )
    return 1;
  while ( *pattern )
  {
    pattern_char = (unsigned char)*pattern;
    if ( pattern_char == '*' )
    {
      while ( *pattern == '*' )
        ++pattern;
      if ( !*pattern )
        return 1;
      while ( *text )
      {
        if ( CompatWildcardMatchNoCase(pattern, text) )
          return 1;
        ++text;
      }
      return 0;
    }
    if ( !*text )
      return 0;
    if ( pattern_char != '?' )
    {
      text_char = (unsigned char)*text;
      if ( tolower(pattern_char) != tolower(text_char) )
        return 0;
    }
    ++pattern;
    ++text;
  }
  return *text == 0;
}

static void CompatUnixSecondsToFileTime(time_t unix_seconds, DWORD *low_part, DWORD *high_part)
{
  unsigned long long windows_ticks;

  windows_ticks = ((unsigned long long)unix_seconds + 11644473600ULL) * 10000000ULL;
  *low_part = (DWORD)windows_ticks;
  *high_part = (DWORD)(windows_ticks >> 32);
}

static int CompatFillFindData(const char *directory, const char *entry_name, LPWIN32_FIND_DATAA find_data)
{
  char full_path[PATH_MAX];
  struct stat st;

  if ( !directory || !entry_name || !find_data )
    return 0;
  Compat_CopyPrefixN(full_path, directory, (unsigned int)strlen(directory) + 1);
  if ( !CompatAppendPathComponent(full_path, sizeof(full_path), entry_name) )
  {
    g_platform_last_error = (DWORD)ENAMETOOLONG;
    return 0;
  }
  if ( stat(full_path, &st) != 0 )
  {
    CompatSetLastErrorFromErrno();
    return 0;
  }
  memset(find_data, 0, sizeof(*find_data));
  if ( S_ISDIR(st.st_mode) )
    find_data->dwFileAttributes |= COMPAT_FILE_ATTRIBUTE_DIRECTORY;
  else
    find_data->dwFileAttributes |= 0x20u;
  if ( access(full_path, W_OK) != 0 )
    find_data->dwFileAttributes |= COMPAT_FILE_ATTRIBUTE_READONLY;
  if ( entry_name[0] == '.' )
    find_data->dwFileAttributes |= 2u;
  CompatUnixSecondsToFileTime(st.st_ctime, &find_data->ftCreationTimeLow, &find_data->ftCreationTimeHigh);
  CompatUnixSecondsToFileTime(st.st_atime, &find_data->ftLastAccessTimeLow, &find_data->ftLastAccessTimeHigh);
  CompatUnixSecondsToFileTime(st.st_mtime, &find_data->ftLastWriteTimeLow, &find_data->ftLastWriteTimeHigh);
  find_data->nFileSizeLow = (DWORD)((unsigned long long)st.st_size & 0xFFFFFFFFu);
  find_data->nFileSizeHigh = (DWORD)(((unsigned long long)st.st_size >> 32) & 0xFFFFFFFFu);
  Compat_CopyPrefixN(find_data->cFileName, entry_name, (unsigned int)strlen(entry_name) + 1);
  find_data->cAlternateFileName[0] = 0;
  g_platform_last_error = 0;
  return 1;
}

static int CompatFindNextMatch(CompatFindHandle *handle, LPWIN32_FIND_DATAA find_data)
{
  struct dirent *entry;

  if ( !handle || !handle->dir || !find_data )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  while ( (entry = readdir(handle->dir)) != 0 )
  {
    if ( !strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") )
      continue;
    if ( !CompatWildcardMatchNoCase(handle->pattern, entry->d_name) )
      continue;
    if ( CompatFillFindData(handle->directory, entry->d_name, find_data) )
      return 1;
  }
  g_platform_last_error = (DWORD)ENOENT;
  return 0;
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

static int CompatPointerFitsSigned32(const void *ptr)
{
  return ptr && (uintptr_t)ptr <= (uintptr_t)INT_MAX;
}

enum
{
  COMPAT_LOW32_ARENA_BLOCK = 2,
  COMPAT_LOW32_ARENA_FREE_BLOCK = 3
};

#define COMPAT_LOW32_ARENA_SIZE ((size_t)16 * 1024 * 1024)
#define COMPAT_LOW32_ARENA_MAX_ALLOC ((size_t)1024 * 1024)

static size_t CompatAlignLow32Size(size_t size)
{
  return (size + 7u) & ~(size_t)7u;
}

static CompatLow32AllocHeader *CompatTryMapSignedLow32(size_t total_size, int flags, void *hint)
{
  CompatLow32AllocHeader *header;

  header = (CompatLow32AllocHeader *)mmap(
    hint,
    total_size,
    PROT_READ | PROT_WRITE,
    MAP_PRIVATE | MAP_ANONYMOUS | flags,
    -1,
    0);
  if ( header == MAP_FAILED )
    return 0;
  if ( !CompatPointerFitsSigned32(header + 1) )
  {
    munmap(header, total_size);
    return 0;
  }
  header->mapped_size = total_size;
  header->magic = COMPAT_LOW32_ALLOC_MAGIC;
  header->used_mmap = 1;
  header->next_free = 0;
  return header;
}

static CompatLow32AllocHeader *CompatMapSignedLow32(size_t total_size)
{
  CompatLow32AllocHeader *header;
#ifdef MAP_FIXED_NOREPLACE
  uintptr_t hint;
  uintptr_t step;
  size_t page_size;
  long page_size_result;
#endif

#ifdef MAP_32BIT
  header = CompatTryMapSignedLow32(total_size, MAP_32BIT, 0);
  if ( header )
    return header;
#endif
#ifdef MAP_FIXED_NOREPLACE
  page_size_result = sysconf(_SC_PAGESIZE);
  if ( page_size_result > 0 )
    page_size = (size_t)page_size_result;
  else
    page_size = 4096;
  total_size = (total_size + page_size - 1) & ~(page_size - 1);
  step = total_size < 0x01000000u ? 0x00100000u : 0x01000000u;
  for ( hint = 0x01000000u; hint + total_size <= 0x7F000000u; hint += step )
  {
    header = CompatTryMapSignedLow32(total_size, MAP_FIXED_NOREPLACE, (void *)hint);
    if ( header )
      return header;
  }
#endif
  return 0;
}

static void *CompatAllocLow32FromArena(size_t size)
{
  CompatLow32Arena *arena;
  CompatLow32AllocHeader *mapping;
  CompatLow32AllocHeader *block_header;
  CompatLow32AllocHeader **free_link;
  size_t header_size;
  size_t payload_size;
  size_t block_size;
  size_t arena_capacity;
  size_t mapping_size;

  if ( size > COMPAT_LOW32_ARENA_MAX_ALLOC )
    return 0;
  header_size = CompatAlignLow32Size(sizeof(CompatLow32AllocHeader));
  payload_size = CompatAlignLow32Size(size);
  if ( payload_size > (size_t)-1 - header_size )
    return 0;
  block_size = header_size + payload_size;
  for ( free_link = &g_compat_low32_free_blocks; *free_link; free_link = &(*free_link)->next_free )
  {
    if ( (*free_link)->magic == COMPAT_LOW32_ALLOC_MAGIC
      && (*free_link)->used_mmap == COMPAT_LOW32_ARENA_FREE_BLOCK
      && (*free_link)->mapped_size >= block_size )
    {
      block_header = *free_link;
      *free_link = block_header->next_free;
      block_header->next_free = 0;
      block_header->used_mmap = COMPAT_LOW32_ARENA_BLOCK;
      g_compat_low32_arena_reused_bytes += block_header->mapped_size;
      if ( g_compat_low32_arena_free_bytes >= block_header->mapped_size )
        g_compat_low32_arena_free_bytes -= block_header->mapped_size;
      else
        g_compat_low32_arena_free_bytes = 0;
      CompatInvalidateReadableRanges();
      return block_header + 1;
    }
  }
  for ( arena = g_compat_low32_arenas; arena; arena = arena->next )
  {
    if ( arena->offset <= arena->capacity && arena->capacity - arena->offset >= block_size )
      break;
  }
  if ( !arena )
  {
    arena_capacity = COMPAT_LOW32_ARENA_SIZE;
    if ( arena_capacity < block_size )
      arena_capacity = block_size;
    if ( arena_capacity > (size_t)-1 - sizeof(*mapping) )
      return 0;
    mapping_size = sizeof(*mapping) + arena_capacity;
    mapping = CompatMapSignedLow32(mapping_size);
    if ( !mapping && arena_capacity != block_size )
    {
      arena_capacity = block_size;
      mapping_size = sizeof(*mapping) + arena_capacity;
      mapping = CompatMapSignedLow32(mapping_size);
    }
    if ( !mapping )
      return 0;
    arena = (CompatLow32Arena *)malloc(sizeof(*arena));
    if ( !arena )
    {
      munmap(mapping, mapping->mapped_size);
      return 0;
    }
    arena->mapping = mapping;
    arena->base = (unsigned char *)(mapping + 1);
    arena->capacity = mapping->mapped_size - sizeof(*mapping);
    arena->offset = 0;
    arena->next = g_compat_low32_arenas;
    g_compat_low32_arenas = arena;
    ++g_compat_low32_arena_count;
    g_compat_low32_arena_capacity_total += arena->capacity;
  }

  block_header = (CompatLow32AllocHeader *)(void *)(arena->base + arena->offset);
  if ( !CompatPointerFitsSigned32(block_header + 1) )
    return 0;
  arena->offset += block_size;
  g_compat_low32_arena_offset_total += block_size;
  block_header->mapped_size = block_size;
  block_header->magic = COMPAT_LOW32_ALLOC_MAGIC;
  block_header->used_mmap = COMPAT_LOW32_ARENA_BLOCK;
  block_header->next_free = 0;
  CompatInvalidateReadableRanges();
  return block_header + 1;
}

static void CompatLogLow32AllocFailure(size_t size)
{
  void *frames[16];
  int frame_count;

  fprintf(
    stderr,
    "[compat] low32 alloc failed size=%zu arenas=%zu arena_capacity=%zu arena_offset=%zu arena_free=%zu arena_reused=%zu\n",
    size,
    g_compat_low32_arena_count,
    g_compat_low32_arena_capacity_total,
    g_compat_low32_arena_offset_total,
    g_compat_low32_arena_free_bytes,
    g_compat_low32_arena_reused_bytes);
  frame_count = backtrace(frames, 16);
  if ( frame_count > 0 )
    backtrace_symbols_fd(frames, frame_count, STDERR_FILENO);
}

static void *CompatAllocLow32(size_t size)
{
  CompatLow32AllocHeader *header;
  void *arena_block;
  size_t total_size;

  if ( !size )
    return 0;
  arena_block = CompatAllocLow32FromArena(size);
  if ( arena_block )
    return arena_block;
  if ( size > (size_t)-1 - sizeof(*header) )
  {
    CompatLogLow32AllocFailure(size);
    return 0;
  }
  total_size = sizeof(*header) + size;
  header = CompatMapSignedLow32(total_size);
  if ( header )
  {
    CompatInvalidateReadableRanges();
    return header + 1;
  }
  header = (CompatLow32AllocHeader *)malloc(total_size);
  if ( !header )
  {
    CompatLogLow32AllocFailure(size);
    return 0;
  }
  if ( !CompatPointerFitsSigned32(header + 1) )
  {
    free(header);
    CompatLogLow32AllocFailure(size);
    return 0;
  }
  header->mapped_size = total_size;
  header->magic = COMPAT_LOW32_ALLOC_MAGIC;
  header->used_mmap = 0;
  header->next_free = 0;
  CompatInvalidateReadableRanges();
  return header + 1;
}

static void CompatFreeLow32(void *ptr)
{
  CompatLow32AllocHeader *header;

  if ( !ptr )
    return;
  header = ((CompatLow32AllocHeader *)ptr) - 1;
  if ( !CompatPointerReadable(header)
    || !CompatPointerReadable((const char *)header + sizeof(*header) - 1)
    || header->magic != COMPAT_LOW32_ALLOC_MAGIC )
  {
    return;
  }
  if ( header->used_mmap == COMPAT_LOW32_ARENA_BLOCK )
  {
    header->used_mmap = COMPAT_LOW32_ARENA_FREE_BLOCK;
    header->next_free = g_compat_low32_free_blocks;
    g_compat_low32_free_blocks = header;
    g_compat_low32_arena_free_bytes += header->mapped_size;
    CompatInvalidateReadableRanges();
    return;
  }
  if ( header->used_mmap == COMPAT_LOW32_ARENA_FREE_BLOCK )
    return;
  CompatInvalidateReadableRanges();
  if ( header->used_mmap )
    munmap(header, header->mapped_size);
  else
    free(header);
}

static CompatFileRuntimeStream *CompatGetFileRuntimeStream(int stream_ptr)
{
  if ( !stream_ptr )
    return 0;
  return (CompatFileRuntimeStream *)(uintptr_t)stream_ptr;
}

static CompatFileRuntimeMeta *CompatGetFileRuntimeMeta(CompatFileRuntimeStream *stream)
{
  if ( !stream )
    return 0;
  return (CompatFileRuntimeMeta *)(uintptr_t)(unsigned int)stream->meta;
}

static int CompatGetOsFdFromStream(CompatFileRuntimeStream *stream)
{
  if ( !stream )
    return -1;
  return stream->fd_index;
}

int Compat_AllocFileStream(void)
{
  CompatFileRuntimeMeta *meta;
  CompatFileRuntimeStream *stream;

  meta = (CompatFileRuntimeMeta *)CompatAllocLow32(sizeof(*meta));
  if ( !meta )
    return 0;
  stream = (CompatFileRuntimeStream *)CompatAllocLow32(sizeof(*stream));
  if ( !stream )
  {
    CompatFreeLow32(meta);
    return 0;
  }
  memset(meta, 0, sizeof(*meta));
  memset(stream, 0, sizeof(*stream));
  meta->stream_ptr = (int)(uintptr_t)stream;
  meta->fd_index = -1;
  stream->meta = (int)(uintptr_t)meta;
  stream->fd_index = -1;
  CompatRegisterStreamHandle((int)(uintptr_t)stream);
  return (int)(uintptr_t)stream;
}

int Compat_AllocLow32Bytes(int size)
{
  void *block;

  if ( size <= 0 )
    return 0;
  block = CompatAllocLow32((size_t)size);
  if ( !block )
    return 0;
  memset(block, 0, (size_t)size);
  return (int)(uintptr_t)block;
}

void Compat_FreeFileStream(int stream_ptr)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;

  CompatUnregisterStreamHandle(stream_ptr);
  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return;
  if ( stream->fd_index >= 0 )
    close(stream->fd_index);
  meta = CompatGetFileRuntimeMeta(stream);
  if ( meta && meta->buffer_base )
    CompatFreeLow32((void *)(uintptr_t)(unsigned int)meta->buffer_base);
  if ( meta )
    CompatFreeLow32(meta);
  CompatFreeLow32(stream);
}

void Compat_FreeLow32Bytes(int ptr)
{
  CompatFreeLow32((void *)(uintptr_t)ptr);
}

int Compat_InitFileStream(int stream_ptr, int fd_index, int mode_char, int open_flags)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;

  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return 0;
  meta = CompatGetFileRuntimeMeta(stream);
  if ( !meta )
    return 0;
  memset(stream, 0, sizeof(*stream));
  memset(meta, 0, sizeof(*meta));
  meta->stream_ptr = stream_ptr;
  meta->fd_index = fd_index;
  meta->mode_char = mode_char;
  stream->meta = (int)(uintptr_t)meta;
  stream->flags0 = (unsigned char)open_flags;
  stream->fd_index = fd_index;
  return stream_ptr;
}

int Compat_OpenFileDescriptor(const char *path, int mode_char, int open_flags)
{
  char translated_path[PATH_MAX];
  const char *effective_path;
  int flags;
  int fd;

  if ( !path || !*path )
  {
    errno = EINVAL;
    g_platform_last_error = (DWORD)EINVAL;
    return -1;
  }
  effective_path = path;
  if ( CompatTranslatePathToWsl(path, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  flags = O_BINARY;
  if ( (open_flags & 0x80u) != 0 )
    mode_char = 'a';
  else if ( (open_flags & 2) != 0 )
    mode_char = 'w';
  else
    mode_char = 'r';
  switch ( mode_char )
  {
    case 'r':
      flags |= (open_flags & 2) != 0 ? O_RDWR : O_RDONLY;
      break;
    case 'w':
      flags |= (open_flags & 1) != 0 ? O_RDWR : O_WRONLY;
      flags |= O_CREAT | O_TRUNC;
      break;
    case 'a':
      flags |= (open_flags & 1) != 0 ? O_RDWR : O_WRONLY;
      flags |= O_CREAT | O_APPEND;
      break;
    default:
      errno = EINVAL;
      g_platform_last_error = (DWORD)EINVAL;
      return -1;
  }
  fd = open(effective_path, flags, 0666);
  if ( fd < 0 )
  {
    CompatSetLastErrorFromErrno();
    return -1;
  }
  g_platform_last_error = 0;
  return fd;
}

int Compat_StreamSetBuffer(int stream_ptr, int buffer_size)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;

  if ( buffer_size <= 0 )
    return 0;
  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return -1;
  meta = CompatGetFileRuntimeMeta(stream);
  if ( !meta )
    return -1;
  if ( !meta->buffer_base )
  {
    meta->buffer_base = (int)(uintptr_t)CompatAllocLow32((size_t)buffer_size);
    if ( !meta->buffer_base )
      return -1;
    memset((void *)(uintptr_t)(unsigned int)meta->buffer_base, 0, (size_t)buffer_size);
    meta->buffer_size = buffer_size;
  }
  stream->current_ptr = meta->buffer_base;
  stream->remaining_count = 0;
  return 0;
}

int Compat_StreamRead(int stream_ptr, void *buffer, int byte_count)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;
  int os_fd;
  ssize_t bytes_read;

  if ( !buffer || byte_count < 0 )
    return 0;
  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return 0;
  os_fd = CompatGetOsFdFromStream(stream);
  if ( os_fd < 0 )
    return 0;
  bytes_read = read(os_fd, buffer, (size_t)byte_count);
  if ( bytes_read <= 0 )
  {
    if ( bytes_read < 0 )
      CompatSetLastErrorFromErrno();
    return 0;
  }
  meta = CompatGetFileRuntimeMeta(stream);
  stream->remaining_count = 0;
  stream->current_ptr = meta ? meta->buffer_base : 0;
  return (int)bytes_read;
}

int Compat_StreamWrite(int stream_ptr, const void *buffer, int byte_count)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;
  int os_fd;
  ssize_t bytes_written;

  if ( !buffer || byte_count < 0 )
    return 0;
  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return 0;
  os_fd = CompatGetOsFdFromStream(stream);
  if ( os_fd < 0 )
    return 0;
  bytes_written = write(os_fd, buffer, (size_t)byte_count);
  if ( bytes_written <= 0 )
  {
    if ( bytes_written < 0 )
      CompatSetLastErrorFromErrno();
    return 0;
  }
  meta = CompatGetFileRuntimeMeta(stream);
  stream->remaining_count = 0;
  stream->current_ptr = meta ? meta->buffer_base : 0;
  return (int)bytes_written;
}

int Compat_StreamSeek(int stream_ptr, int offset, int whence)
{
  CompatFileRuntimeStream *stream;
  CompatFileRuntimeMeta *meta;
  int os_fd;
  int seek_whence;
  off_t position;

  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return -1;
  os_fd = CompatGetOsFdFromStream(stream);
  if ( os_fd < 0 )
    return -1;
  switch ( whence )
  {
    case 0:
      seek_whence = SEEK_SET;
      break;
    case 1:
      seek_whence = SEEK_CUR;
      break;
    case 2:
      seek_whence = SEEK_END;
      break;
    default:
      errno = EINVAL;
      g_platform_last_error = (DWORD)EINVAL;
      return -1;
  }
  position = lseek(os_fd, (off_t)offset, seek_whence);
  if ( position == (off_t)-1 )
  {
    CompatSetLastErrorFromErrno();
    return -1;
  }
  meta = CompatGetFileRuntimeMeta(stream);
  stream->remaining_count = 0;
  stream->current_ptr = meta ? meta->buffer_base : 0;
  if ( whence == 2 )
    stream->flags0 &= 0xEFu;
  else
    stream->flags0 &= 0xEBu;
  return 0;
}

int Compat_StreamTell(int stream_ptr)
{
  CompatFileRuntimeStream *stream;
  int os_fd;
  off_t position;

  stream = CompatGetFileRuntimeStream(stream_ptr);
  if ( !stream )
    return -1;
  os_fd = CompatGetOsFdFromStream(stream);
  if ( os_fd < 0 )
    return -1;
  position = lseek(os_fd, 0, SEEK_CUR);
  if ( position == (off_t)-1 )
  {
    CompatSetLastErrorFromErrno();
    return -1;
  }
  return (int)position;
}

int Compat_WcppCtorArrayStorage1m(void *base, int count, const void *descriptor)
{
  const CompatWcppArrayStoreDesc *desc;
  unsigned char *cursor;
  int index;

  if ( !base )
    return 0;
  desc = (const CompatWcppArrayStoreDesc *)descriptor;
  if ( !desc || desc->kind == 0 || desc->stride <= 0 || count <= 0 )
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
      g_platform_last_error = 0;
      return index;
    }
  }
  for ( index = 0; index < COMPAT_TLS_SEARCH_START; ++index )
  {
    if ( !g_compat_tls_slot_in_use[index] )
    {
      g_compat_tls_slot_in_use[index] = 1;
      g_compat_tls_slots[index] = 0;
      g_platform_last_error = 0;
      return index;
    }
  }
  g_platform_last_error = (DWORD)ENOMEM;
  return (DWORD)-1;
}

BOOL __stdcall TlsFree(DWORD dwTlsIndex)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_tls_slot_in_use[dwTlsIndex] = 0;
  g_compat_tls_slots[dwTlsIndex] = 0;
  g_platform_last_error = 0;
  return 1;
}

LPVOID __stdcall TlsGetValue(DWORD dwTlsIndex)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_platform_last_error = 0;
  return g_compat_tls_slots[dwTlsIndex];
}

BOOL __stdcall TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue)
{
  if ( !CompatTlsSlotIsValid(dwTlsIndex) )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_compat_tls_slots[dwTlsIndex] = lpTlsValue;
  g_platform_last_error = 0;
  return 1;
}

BOOL __stdcall DeleteFileA(LPCSTR lpFileName)
{
  char translated_path[PATH_MAX];
  const char *effective_path;

  if ( !lpFileName || !*lpFileName )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpFileName;
  if ( CompatTranslatePathToWsl(lpFileName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( unlink(effective_path) == 0 )
  {
    g_platform_last_error = 0;
    return 1;
  }
  CompatSetLastErrorFromErrno();
  return 0;
}

BOOL __stdcall MoveFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName)
{
  char translated_existing[PATH_MAX];
  char translated_new[PATH_MAX];
  const char *existing_path;
  const char *new_path;

  if ( !lpExistingFileName || !*lpExistingFileName || !lpNewFileName || !*lpNewFileName )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  existing_path = lpExistingFileName;
  new_path = lpNewFileName;
  if ( CompatTranslatePathToWsl(lpExistingFileName, translated_existing, sizeof(translated_existing)) )
    existing_path = translated_existing;
  if ( CompatTranslatePathToWsl(lpNewFileName, translated_new, sizeof(translated_new)) )
    new_path = translated_new;
  if ( access(new_path, F_OK) == 0 )
  {
    errno = EEXIST;
    g_platform_last_error = (DWORD)EEXIST;
    return 0;
  }
  if ( rename(existing_path, new_path) == 0 )
  {
    g_platform_last_error = 0;
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
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpPathName;
  if ( CompatTranslatePathToWsl(lpPathName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( mkdir(effective_path, 0777) == 0 )
  {
    g_platform_last_error = 0;
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
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  effective_path = lpPathName;
  if ( CompatTranslatePathToWsl(lpPathName, translated_path, sizeof(translated_path)) )
    effective_path = translated_path;
  if ( rmdir(effective_path) == 0 )
  {
    g_platform_last_error = 0;
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
    g_platform_last_error = (DWORD)EINVAL;
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
  g_platform_last_error = 0;
  return attributes;
}

HANDLE __stdcall FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
  CompatFindHandle *handle;
  HANDLE public_handle;
  char normalized_search[PATH_MAX];
  char directory_spec[PATH_MAX];
  char translated_directory[PATH_MAX];
  char *leaf_spec;
  char *slash;

  if ( !lpFileName || !*lpFileName || !lpFindFileData )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return (HANDLE)-1;
  }
  CompatNormalizePathSlashes(lpFileName, normalized_search, sizeof(normalized_search));
  slash = strrchr(normalized_search, '/');
  if ( slash )
  {
    *slash = 0;
    leaf_spec = slash + 1;
    if ( normalized_search[0] )
      Compat_CopyPrefixN(directory_spec, normalized_search, (unsigned int)strlen(normalized_search) + 1);
    else
      Compat_CopyPrefixN(directory_spec, COMPAT_WSL_GAME_ROOT, sizeof(COMPAT_WSL_GAME_ROOT));
  }
  else
  {
    leaf_spec = normalized_search;
    Compat_CopyPrefixN(directory_spec, COMPAT_WSL_GAME_ROOT, sizeof(COMPAT_WSL_GAME_ROOT));
  }
  if ( !leaf_spec[0] )
    leaf_spec = "*";
  if ( CompatTranslatePathToWsl(directory_spec, translated_directory, sizeof(translated_directory)) )
    Compat_CopyPrefixN(directory_spec, translated_directory, (unsigned int)strlen(translated_directory) + 1);
  handle = (CompatFindHandle *)calloc(1, sizeof(*handle));
  if ( !handle )
  {
    g_platform_last_error = (DWORD)ENOMEM;
    return (HANDLE)-1;
  }
  Compat_CopyPrefixN(handle->directory, directory_spec, (unsigned int)strlen(directory_spec) + 1);
  Compat_CopyPrefixN(handle->pattern, leaf_spec, (unsigned int)strlen(leaf_spec) + 1);
  handle->dir = opendir(handle->directory);
  if ( !handle->dir )
  {
    free(handle);
    CompatSetLastErrorFromErrno();
    return (HANDLE)-1;
  }
  if ( !CompatFindNextMatch(handle, lpFindFileData) )
  {
    closedir(handle->dir);
    free(handle);
    return (HANDLE)-1;
  }
  public_handle = CompatRegisterFindHandle(handle);
  if ( public_handle == (HANDLE)-1 )
  {
    closedir(handle->dir);
    free(handle);
    return (HANDLE)-1;
  }
  return public_handle;
}

BOOL __stdcall FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
  int slot_index;

  slot_index = CompatFindHandleIndexFromHandle(hFindFile);
  if ( slot_index < 0 || !lpFindFileData )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  return CompatFindNextMatch(g_compat_find_handles[slot_index], lpFindFileData);
}

BOOL __stdcall FindClose(HANDLE hFindFile)
{
  int slot_index;
  CompatFindHandle *handle;

  slot_index = CompatFindHandleIndexFromHandle(hFindFile);
  if ( slot_index < 0 )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  handle = g_compat_find_handles[slot_index];
  g_compat_find_handles[slot_index] = 0;
  if ( handle->dir )
    closedir(handle->dir);
  free(handle);
  g_platform_last_error = 0;
  return 1;
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

void __lock_p(__lock *this)
{
  (void)this;
}

void __lock_v(__lock *this)
{
  (void)this;
}

BOOL __stdcall CloseHandle(HANDLE hObject)
{
  CompatEventHandle *event_handle;

  if ( !hObject )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  event_handle = CompatGetEventHandle(hObject);
  if ( event_handle )
  {
    CompatUnregisterEventHandle(hObject);
    event_handle->magic = 0;
    free(event_handle);
  }
  g_platform_last_error = 0;
  return 1;
}

DWORD __stdcall ResumeThread(HANDLE hThread)
{
  if ( !hThread )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return (DWORD)-1;
  }
  g_platform_last_error = 0;
  return 0;
}

HANDLE __stdcall beginthreadex_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  g_platform_last_error = 0;
  return (HANDLE)(uintptr_t)1;
}

BOOL __stdcall SetThreadPriority(HANDLE hThread, int nPriority)
{
  (void)nPriority;
  if ( !hThread )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  g_platform_last_error = 0;
  return 1;
}

HANDLE __stdcall CreateEventA(
        LPSECURITY_ATTRIBUTES lpEventAttributes,
        BOOL bManualReset,
        BOOL bInitialState,
        LPCSTR lpName)
{
  CompatEventHandle *event_handle;
  HANDLE public_handle;

  (void)lpEventAttributes;
  (void)lpName;
  event_handle = (CompatEventHandle *)calloc(1, sizeof(*event_handle));
  if ( !event_handle )
  {
    CompatSetLastErrorFromErrno();
    return 0;
  }
  event_handle->magic = COMPAT_EVENT_MAGIC;
  event_handle->manual_reset = bManualReset != 0;
  event_handle->signaled = bInitialState != 0;
  public_handle = CompatRegisterEventHandle(event_handle);
  if ( !public_handle )
  {
    free(event_handle);
    g_platform_last_error = (DWORD)ENOMEM;
    return 0;
  }
  g_platform_last_error = 0;
  return public_handle;
}

DWORD __stdcall WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
  CompatEventHandle *event_handle;

  event_handle = CompatGetEventHandle(hHandle);
  if ( !event_handle )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return COMPAT_WAIT_FAILED;
  }
  if ( event_handle->signaled )
  {
    if ( !event_handle->manual_reset )
      event_handle->signaled = 0;
    g_platform_last_error = 0;
    return COMPAT_WAIT_OBJECT_0;
  }
  if ( dwMilliseconds == 0 )
  {
    g_platform_last_error = 0;
    return COMPAT_WAIT_TIMEOUT;
  }
  if ( dwMilliseconds != COMPAT_WAIT_INFINITE )
    usleep((useconds_t)(dwMilliseconds * 1000));
  else
    usleep(1000);
  if ( event_handle->signaled )
  {
    if ( !event_handle->manual_reset )
      event_handle->signaled = 0;
    g_platform_last_error = 0;
    return COMPAT_WAIT_OBJECT_0;
  }
  g_platform_last_error = 0;
  return COMPAT_WAIT_TIMEOUT;
}

BOOL __stdcall PulseEvent(HANDLE hEvent)
{
  CompatEventHandle *event_handle;

  event_handle = CompatGetEventHandle(hEvent);
  if ( !event_handle )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  event_handle->signaled = event_handle->manual_reset;
  g_platform_last_error = 0;
  return 1;
}

BOOL __stdcall ResetEvent(HANDLE hEvent)
{
  CompatEventHandle *event_handle;

  event_handle = CompatGetEventHandle(hEvent);
  if ( !event_handle )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  event_handle->signaled = 0;
  g_platform_last_error = 0;
  return 1;
}

BOOL __stdcall SetEvent(HANDLE hEvent)
{
  CompatEventHandle *event_handle;

  event_handle = CompatGetEventHandle(hEvent);
  if ( !event_handle )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return 0;
  }
  event_handle->signaled = 1;
  g_platform_last_error = 0;
  return 1;
}

DWORD __stdcall SuspendThread(HANDLE hThread)
{
  if ( !hThread )
  {
    g_platform_last_error = (DWORD)EINVAL;
    return (DWORD)-1;
  }
  g_platform_last_error = 0;
  return 0;
}

int __cdecl _wcpp_4_copy_array__(int a1)
{
  return a1;
}

int _wcpp_4_static_init__(unsigned char *flag_byte)
{
  if ( !flag_byte )
    return 1;
  if ( (*flag_byte & 1) != 0 )
    return 1;
  *flag_byte |= 1;
  return 0;
}

int __cdecl ICClose(int a1)
{
  (void)a1;
  return 0;
}

int AVIFileExit(void)
{
  return 0;
}

int __stdcall AVIStreamEndStreaming(int a1)
{
  (void)a1;
  return 0;
}

int __stdcall AVIStreamRelease(int a1)
{
  (void)a1;
  return 0;
}

int __stdcall AVIFileRelease(int a1)
{
  (void)a1;
  return 0;
}

int __cdecl ICDecompress(int a1, int a2, int a3, int a4, int a5, int a6)
{
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  return 0;
}

int __stdcall ICSendMessage(DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5)
{
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  return 0;
}

int __cdecl abs32(int value)
{
  return value < 0 ? -value : value;
}

int ExcString_AsCharPtr(void *a1, void *a2, void *a3, int a4)
{
  static const char kCompatEmptyString[] = "";

  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  return (int)(uintptr_t)kCompatEmptyString;
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
    CompatFreeLow32((void *)(uintptr_t)a1);
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
   * The real binary routes this through the CRT finalizer list. That list is
   * still under-recovered and the direct decompiled body corrupts the live WSL
   * bootstrap. Keep registration quarantined as a no-op until the underlying
   * thread-data/finalizer contract is reconstructed from asm.
   */
  (void)a1;
  (void)a2;
  return 0;
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
  return CompatSafeStrcmp(lhs, rhs);
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

int __cdecl sscanf_(const char *buffer, const char *format, ...)
{
  int result;
  va_list args;

  if ( !buffer || !format )
    return -1;
  va_start(args, format);
  result = vsscanf(buffer, format, args);
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

double __cdecl _CHP(_DWORD low, _DWORD high)
{
  union
  {
    struct
    {
      uint32_t low;
      uint32_t high;
    } parts;
    double value;
  } value_bits;

  /*
   * The original `__CHP` is a collapsed x87 helper in the binary, but the
   * decompiled C has already widened those sites into ordinary two-argument
   * calls. Rebuilding the split double keeps return-using callsites stable and
   * lets the wider executable relink while the authentic x87-side behavior
   * stays deferred.
   */
  value_bits.parts.low = (uint32_t)low;
  value_bits.parts.high = (uint32_t)high;
  return value_bits.value;
}

int __thiscall fclose_(_DWORD a1)
{
  if ( !a1 || a1 == (_DWORD)-1 )
    return 0;
  if ( CompatIsRegisteredStreamHandle((int)a1) )
  {
    Compat_FreeFileStream((int)a1);
    return 0;
  }
  return 0;
}

int __cdecl close_(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return fclose_(a1);
}

int fwrite_(const void *buffer, int size, int file_handle, int count)
{
  int bytes_written;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  if ( !CompatIsRegisteredStreamHandle(file_handle) || !size || !count )
    return 0;
  bytes_written = Compat_StreamWrite(file_handle, buffer, size * count);
  if ( bytes_written <= 0 )
    return 0;
  return bytes_written / size;
}

int __fastcall fputs_(_DWORD a1, _DWORD a2)
{
  const char *text;
  int length;

  (void)a2;
  text = (const char *)(uintptr_t)a1;
  if ( !text )
    return -1;
  length = (int)strlen(text);
  if ( length <= 0 )
    return 0;
  return fwrite(text, 1, (size_t)length, stderr) == (size_t)length ? 0 : -1;
}

int fread_(void *buffer, int size, int file_handle, int count)
{
  int bytes_read;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  if ( !CompatIsRegisteredStreamHandle(file_handle) || !size || !count )
    return 0;
  bytes_read = Compat_StreamRead(file_handle, buffer, size * count);
  if ( bytes_read <= 0 )
    return 0;
  return bytes_read / size;
}

int __fastcall strncmp_(_DWORD a1, _DWORD a2, unsigned int count)
{
  const char *lhs;
  const char *rhs;

  lhs = (const char *)(uintptr_t)a1;
  rhs = (const char *)(uintptr_t)a2;
  if ( lhs == rhs || !count )
    return 0;
  if ( !lhs )
    return -1;
  if ( !rhs )
    return 1;
  return strncmp(lhs, rhs, count);
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

int __fastcall CAviDecompressor_ApplyDecoderFormatParams(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int CRT_ThrowExcStringException(void)
{
  return 0;
}

void __noreturn CRT_WatcomEHHandleNestedException(int a1, int a2)
{
  (void)a1;
  (void)a2;
  abort();
}

int CRT_WatcomEHFrameHandler(void)
{
  return 0;
}

/*
 * Map/asm corroborate these as collapsed one-byte `retn` placeholders.
 * Returning zero here is a compile/link quarantine choice, not a claim that
 * the original callers depended on a specific non-void result.
 */
int Noop_WorldMapFrameRedrawHook(void)
{
  return 0;
}

int __thiscall Noop_AppShutdownPostAudioCloseHook(_DWORD a1)
{
  (void)a1;
  return 0;
}

int __thiscall Noop_PlayGameSessionBoundaryHook(_DWORD a1)
{
  (void)a1;
  return 0;
}

int Noop_AppShutdownPreAudioCloseHook(void)
{
  return 0;
}

int Noop_DebugHotkeyF1Handler(void)
{
  return 0;
}

int __fastcall Noop_CrtExitHandlerPair(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __thiscall Noop_WCIsvListErrorHook(_DWORD a1)
{
  (void)a1;
  return 0;
}

_DWORD Noop_CrtSingleThreadLockStub(void)
{
  return 0;
}

int Noop_CrtLockEnterLeaveResetStub(void)
{
  return 0;
}

int Noop_CrtIoInitHook(void)
{
  return 0;
}

int __fastcall Noop_DeftemplateResetCallback(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int Noop_InputDeviceDoOp(void)
{
  return 0;
}

int Noop_PathEntryArrayDeletingDtor(void)
{
  return 0;
}

int Noop_SurfaceCursorUnboundedAdvance(void)
{
  return 0;
}

int Noop_InputDeviceGetParamB(void)
{
  return 0;
}

int Noop_InputDeviceSetParamA(void)
{
  return 0;
}

int Noop_FatalQueryStreamDestruct(void)
{
  return 0;
}

int Noop_FatalQueryStreamPutBackByte(void)
{
  return 0;
}

int Noop_RulesRecordScalarDeletingDtor(void)
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
  return Menu_DrawFrameBackdrop();
}

static int Compat_LoadFontPaletteTable(const char *source_stem, uint32_t *palette_out)
{
  char palette_name[100];
  char query_path[104];
  unsigned char palette_bytes[768];
  int query_handle;
  int palette_index;
  int palette_offset;
  size_t source_name_len;
  uintptr_t *query_vtable;

  if ( !source_stem || !palette_out )
    return 0;

  strcpy(palette_name, source_stem);
  source_name_len = strlen(palette_name);
  if ( source_name_len < 4 || strcmp(palette_name + source_name_len - 4, ".sfn") )
    return 0;
  palette_name[source_name_len - 3] = 'p';

  strcpy(query_path, "gfx\\");
  strcat(query_path, palette_name);
  query_handle = FileSystem_ResolveReadPath(query_path, 1);
  if ( !query_handle )
    return 0;

  Compat_QuerySkipBytes(query_handle, 8);
  query_vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query_handle;
  if ( !query_vtable || !query_vtable[5] )
  {
    Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
    return 0;
  }
  if ( ((int (*)(int, void *, int))(uintptr_t)query_vtable[5])(query_handle, palette_bytes, sizeof(palette_bytes))
    != (int)sizeof(palette_bytes) )
  {
    Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
    return 0;
  }
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  palette_offset = 0;
  for ( palette_index = 0; palette_index < 256; ++palette_index )
  {
    palette_out[palette_index] =
      (uint32_t)palette_bytes[palette_offset]
      | ((uint32_t)palette_bytes[palette_offset + 1] << 8)
      | ((uint32_t)palette_bytes[palette_offset + 2] << 16);
    palette_offset += 3;
  }
  return 1;
}

void Render_LoadResourceSprite_v2(void)
{
  WorldMap_EnableFrameRedraw();
}

int Render_LoadResourceSprite_v3(_BYTE *a1)
{
  TextSpriteResourceSlotRecord *slot;
  const unsigned char *cursor;
  int total_width;

  slot = TextSprite_GetResourceSlot(g_ActiveTextSpriteSlot);
  cursor = (const unsigned char *)a1;
  total_width = 0;
  if ( !slot || !slot->cached_sprite_set || !cursor || !*cursor )
    return total_width;

  for ( ; ; )
  {
    while ( *cursor == '\n' )
    {
      ++cursor;
      if ( !*cursor )
        return total_width;
    }
    total_width += slot->glyph_spacing_word + (unsigned __int16)DLX_GetSpriteHeight(slot->cached_sprite_set, *cursor - 32);
    ++cursor;
    if ( !*cursor )
      return total_width;
  }
}

void Render_LoadResourceSprite_v4(int a1, _BYTE *a2, int a3, char a4, DWORD a5)
{
  char cache_path[100];
  char query_path[104];
  TextSpriteResourceSlotRecord *slot;
  _DWORD *sprite_set;
  int cached_sprite_set;
  int cache_query_handle;
  const char *source_stem;
  unsigned int checksum_sum;
  unsigned char checksum_xor;
  int source_offset;
  uint32_t source_palette[256];

  (void)a3;
  (void)a4;
  (void)a5;

  slot = TextSprite_GetResourceSlot(a1);
  if ( !slot )
    return;
  cached_sprite_set = slot->cached_sprite_set;
  if ( cached_sprite_set )
    nfree_(cached_sprite_set);
  slot->cached_sprite_set = 0;
  if ( !a2 )
    return;

  checksum_sum = 0;
  checksum_xor = 0;
  for ( source_offset = 0; source_offset < 0x300; ++source_offset )
  {
    checksum_xor ^= a2[source_offset];
    checksum_sum += a2[source_offset];
  }
  sprintf_(cache_path, "cache\\%02x%02x%04x.s32", a1, checksum_xor, checksum_sum & 0xFFFFu);

  sprite_set = 0;
  cache_query_handle = 0;
  if ( Res_ProbeGfxFileExists(cache_path, 0, a5, 0) )
  {
    strcpy(query_path, "gfx\\");
    strcat(query_path, cache_path);
    cache_query_handle = FileSystem_ResolveReadPath(query_path, 0);
    if ( cache_query_handle )
    {
      Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &cache_query_handle);
      sprite_set = (_DWORD *)Mem_Alloc(0x1010, 0, 0, a5);
      if ( sprite_set )
        sprite_set = DLXSpriteSet_Load(sprite_set, cache_path);
      slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
      if ( sprite_set )
        return;
    }
  }

  source_stem = slot->source_stem;
  sprite_set = (_DWORD *)Mem_Alloc(0x1010, 0, 0, a5);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, source_stem);
  slot->cached_sprite_set = (int)(uintptr_t)sprite_set;
  if ( !sprite_set )
    return;

  source_offset = Compat_LoadFontPaletteTable(source_stem, source_palette);
  if ( !source_offset )
    return;

  DLXSpriteSet_DrawText(
    (int)(intptr_t)sprite_set,
    -1,
    (int)(intptr_t)a2,
    (unsigned __int8 *)(void *)source_palette);
}

int Render_CreateSprite(void)
{
  return Font_InitGlyphFallbackTablesForLanguage();
}

signed int Unit_GetSquadCount(intptr_t a1)
{
  unsigned char *slot;
  int squad_count;

  slot = (unsigned char *)(a1 + 6);
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

int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD a1, _DWORD a2)
{
  const char *message;

  (void)a2;
  message = (const char *)(uintptr_t)a1;
  if ( message && *message )
    fprintf(stderr, "[compat] fatal runtime error: %s\n", message);
  abort();
}

int __fastcall IO_InertRouterCallbackSlot(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __fastcall IO_RemoveFileByPath(_DWORD a1, _DWORD a2)
{
  return CRT_DeleteFile((int)a1, (int)a2);
}

__int64 __fastcall nmalloc_(_DWORD a1, _DWORD a2)
{
  void *block;

  /*
   * `_nmalloc_` is a raw custom allocator in the original binary, not a
   * zeroing CRT helper. The decompiled extra argument is register noise from
   * the lost usercall ABI, so keep the compatibility stub size-driven and let
   * repaired callers supply the real size explicitly. The recovered code still
   * stores many of these allocations in 32-bit fields, so under 64-bit WSL the
   * compatibility allocator must keep returned pointers in the low 32-bit
   * address range.
   */
  (void)a2;
  if ( !a1 )
    return 0;
  block = CompatAllocLow32((size_t)a1);
  return (unsigned int)(uintptr_t)block;
}

int __fastcall memset_(_DWORD a1, _DWORD a2)
{
  if ( a1 )
    *(unsigned char *)(uintptr_t)a1 = (unsigned char)a2;
  return (int)a1;
}

int __cdecl CSyncObject_Unlock(void *raw_sync_object, __int32 lock_state, __int32 *previous_lock_state)
{
  (void)lock_state;
  if ( previous_lock_state )
    *previous_lock_state = 0;
  return raw_sync_object ? 1 : 0;
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

int __thiscall findclose_(_DWORD a1)
{
  if ( (int)a1 <= 0 )
    return 0;
  if ( FindClose((HANDLE)(uintptr_t)(unsigned int)a1) )
    return 0;
  return _set_errno_nt_(0);
}

int __fastcall findnext_(_DWORD a1, _DWORD a2)
{
  WIN32_FIND_DATAA find_data;

  if ( !FindNextFileA((HANDLE)(uintptr_t)(unsigned int)a1, &find_data) )
    return _set_errno_nt_(0);
  CRT_FillFindDataRecord((int)(intptr_t)&find_data, (_DWORD *)(uintptr_t)(unsigned int)a2);
  return 0;
}

int __fastcall getcwd_(_DWORD a1, _DWORD a2)
{
  char *buffer;
  struct stat st;

  buffer = (char *)(uintptr_t)a1;
  if ( !buffer || !a2 )
    return 0;
  if ( stat(COMPAT_WSL_GAME_ROOT, &st) == 0 && S_ISDIR(st.st_mode) )
  {
    Compat_CopyPrefixN(buffer, COMPAT_WSL_GAME_ROOT, (unsigned int)a2);
    return (int)a1;
  }
  return (int)(intptr_t)getcwd(buffer, (size_t)(unsigned int)a2);
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

__int64 __fastcall fgetc_(_DWORD a1, _DWORD a2)
{
  unsigned char byte_value;

  (void)a2;
  if ( !a1 || a1 == (_DWORD)-1 || !CompatIsRegisteredStreamHandle((int)a1) )
    return -1;
  if ( Compat_StreamRead((int)a1, &byte_value, 1) != 1 )
    return -1;
  return byte_value;
}

char *fgets_(char *buffer, int buffer_size, int stream_handle)
{
  int index;
  unsigned char byte_value;

  if ( !buffer || buffer_size <= 0 || !CompatIsRegisteredStreamHandle(stream_handle) )
    return 0;
  if ( buffer_size == 1 )
  {
    buffer[0] = 0;
    return buffer;
  }
  index = 0;
  while ( index < buffer_size - 1 )
  {
    if ( Compat_StreamRead(stream_handle, &byte_value, 1) != 1 )
    {
      if ( !index )
      {
        buffer[0] = 0;
        return 0;
      }
      break;
    }
    buffer[index++] = (char)byte_value;
    if ( byte_value == '\n' )
      break;
  }
  buffer[index] = 0;
  return buffer;
}

__int64 __fastcall ftell_(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  if ( !CompatIsRegisteredStreamHandle((int)a1) )
    return -1;
  return Compat_StreamTell((int)a1);
}

int __fastcall setvbuf_(_DWORD a1, _DWORD a2)
{
  if ( CompatIsRegisteredStreamHandle((int)a1) && (int)a2 > 0 )
    return Compat_StreamSetBuffer((int)a1, (int)a2);
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

int __fastcall CRT_PutcToStream(_DWORD a1, _DWORD a2)
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

int __fastcall CRT_SignedLongToDecimalString(_DWORD a1, _DWORD a2)
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
  g_platform_last_error = 0;
  return (HANDLE)(uintptr_t)fd;
}

void __fastcall __writefsdword(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
}
