/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "00471C60_00473570_media_008_local.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../clips/clips_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE void Compat_StringHolderAssignJoined (_DWORD *holder, const char *prefix, const char *suffix);
CLASH95_TEST_VISIBLE void Compat_StringHolderInsertText (_DWORD *holder, int index, const char *inserted_text);

//----- (00471C60) --------------------------------------------------------
int  Compat_StringHolderScalarDeletingDtor(int holder, char flags)
{
  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(holder, ((_DWORD)(uintptr_t)(&g_CompatStringHolder_DtorArrayDescriptor)));
    j_j__nfree_();
    return holder;
  }
  *(_DWORD *)(uintptr_t)(holder + 4) = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderFreeText((_DWORD *)(uintptr_t)holder);
  if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
    ((void)(holder), j__nfree_());
  return holder;
}
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();

CLASH95_INTERNAL const char *Compat_StringHolderGetText(_DWORD *holder)
{
  if ( !holder || !*holder )
    return 0;
  return (const char *)(uintptr_t)(unsigned int)*holder;
}

CLASH95_INTERNAL const char *Compat_StringArgGetText(const void *arg)
{
  const _DWORD *words;
  uintptr_t native_text_ptr;

  if ( !arg )
    return 0;
  words = (const _DWORD *)(uintptr_t)arg;
  if ( words[1] == (unsigned int)(uintptr_t)&g_CompatStringHolder_Vtable || words[1] == (unsigned int)(uintptr_t)&g_PathEntry_Vtable )
    return Compat_StringHolderGetText((_DWORD *)(uintptr_t)arg);
  native_text_ptr = *(const uintptr_t *)arg;
  if ( !native_text_ptr )
    return 0;
  return (const char *)native_text_ptr;
}

CLASH95_INTERNAL int Compat_QueryRead(int query_handle, void *buffer, int byte_count)
{
  uintptr_t *vtable;

  if ( !query_handle )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)query_handle;
  if ( !vtable || !vtable[5] )
    return 0;
  return ((int (*)(int, void *, int))(uintptr_t)vtable[5])(query_handle, buffer, byte_count);
}

CLASH95_INTERNAL int Compat_QuerySeek(int query_handle, int offset)
{
  uintptr_t *vtable;

  if ( !query_handle )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)query_handle;
  if ( !vtable || !vtable[0] )
    return 0;
  return ((int (*)(int, int))(uintptr_t)vtable[0])(query_handle, offset);
}

CLASH95_TEST_VISIBLE void Compat_StringHolderAssignJoined(_DWORD *holder, const char *prefix, const char *suffix)
{
  unsigned int prefix_size;
  unsigned int suffix_size;
  unsigned int total_size;
  unsigned char *copy;

  if ( !holder )
    return;
  if ( prefix )
    prefix_size = (unsigned int)strlen(prefix);
  else
    prefix_size = 0;
  if ( suffix )
    suffix_size = (unsigned int)strlen(suffix);
  else
    suffix_size = 0;
  if ( !prefix_size && !suffix_size )
  {
    Compat_StringHolderFreeText(holder);
    return;
  }
  total_size = prefix_size + suffix_size;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)(total_size + 1));
  if ( !copy )
  {
    Compat_StringHolderFreeText(holder);
    return;
  }
  if ( prefix_size )
    memcpy(copy, prefix, prefix_size);
  if ( suffix_size )
    memcpy(copy + prefix_size, suffix, suffix_size);
  copy[total_size] = 0;
  Compat_StringHolderFreeText(holder);
  *holder = (int)(uintptr_t)copy;
}

CLASH95_TEST_VISIBLE void Compat_StringHolderInsertText(_DWORD *holder, signed int index, const char *inserted_text)
{
  const char *existing_text;
  unsigned int existing_size;
  unsigned int inserted_size;
  unsigned int total_size;
  unsigned char *copy;

  if ( !holder )
    return;
  existing_text = Compat_StringHolderGetText(holder);
  if ( existing_text )
    existing_size = (unsigned int)strlen(existing_text);
  else
    existing_size = 0;
  if ( inserted_text )
    inserted_size = (unsigned int)strlen(inserted_text);
  else
    inserted_size = 0;
  if ( index < 0 || (unsigned int)index > existing_size || !inserted_size )
    return;
  total_size = existing_size + inserted_size;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)(total_size + 1));
  if ( !copy )
    return;
  if ( index > 0 )
    memcpy(copy, existing_text, (unsigned int)index);
  memcpy(copy + index, inserted_text, inserted_size);
  if ( existing_size > (unsigned int)index )
    memcpy(copy + index + inserted_size, existing_text + index, existing_size - (unsigned int)index);
  copy[total_size] = 0;
  Compat_StringHolderFreeText(holder);
  *holder = (int)(uintptr_t)copy;
}

CLASH95_INTERNAL void Compat_StringHolderCopyText(_DWORD *holder, const char *source)
{
  unsigned char *copy;
  unsigned int copy_size;

  if ( !holder )
    return;
  Compat_StringHolderFreeText(holder);
  if ( !source || !*source )
    return;
  copy_size = (unsigned int)strlen(source) + 1;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)copy_size);
  if ( !copy )
    return;
  memcpy(copy, source, copy_size);
  *holder = (int)(uintptr_t)copy;
}

CLASH95_INTERNAL void Compat_StringHolderInitText(_DWORD *holder, const char *source)
{
  if ( !holder )
    return;
  Compat_StringHolderFreeText(holder);
  if ( source && *source )
    Compat_StringHolderCopyText(holder, source);
}

CLASH95_INTERNAL const char **Compat_StringHolderBuildParentPath(_DWORD *holder, const char *source_text)
{
  unsigned int text_len;
  int slash_index;

  holder[0] = 0;
  holder[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)((const char **)holder)));
  holder[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  if ( source_text && *source_text )
    Compat_StringHolderCopyText(holder, source_text);
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)holder);
  if ( slash_index == -1 )
  {
    Compat_StringHolderCopyText(holder, "");
    return (const char **)holder;
  }
  source_text = Compat_StringHolderGetText(holder);
  text_len = source_text ? (unsigned int)strlen(source_text) : 0;
  Compat_StringHolderRemoveRange((char **)holder, slash_index, text_len, (int)(text_len - (unsigned int)slash_index));
  return (const char **)holder;
}

CLASH95_INTERNAL _DWORD *Compat_StringHolderBuildLeafName(_DWORD *holder, const char *source_text)
{
  unsigned int text_len;
  int slash_index;

  holder[0] = 0;
  holder[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)((const char **)holder)));
  holder[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  if ( source_text && *source_text )
    Compat_StringHolderCopyText(holder, source_text);
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)holder);
  if ( slash_index == -1 )
    return holder;
  source_text = Compat_StringHolderGetText(holder);
  text_len = source_text ? (unsigned int)strlen(source_text) : 0;
  Compat_StringHolderRemoveRange((char **)holder, 0, text_len, slash_index + 1);
  return holder;
}

CLASH95_INTERNAL int Compat_StringHolderDestroyStack(_DWORD *holder, char flags)
{
  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__((int)(uintptr_t)holder, ((_DWORD)(uintptr_t)(&g_CompatStringHolder_DtorArrayDescriptor)));
    j_j__nfree_();
    return (int)(uintptr_t)holder;
  }
  holder[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderFreeText(holder);
  if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
    ((void)((int)(uintptr_t)holder), j__nfree_());
  return (int)(uintptr_t)holder;
}

//----- (00471CA0) --------------------------------------------------------
_DWORD * Compat_StringHolderConstructJoined(_DWORD *holder, _DWORD *prefix_holder, const char *suffix)
{
  holder[0] = 0;
  holder[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderAssignJoined(holder, Compat_StringHolderGetText(prefix_holder), suffix);
  holder[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  return holder;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00471D10) --------------------------------------------------------
const char ** Compat_StringHolderAppendText(const char **holder_ref, const char *appended_text)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  if ( appended_text && *appended_text )
    Compat_StringHolderAssignJoined(holder, Compat_StringHolderGetText(holder), appended_text);
  return holder_ref;
}

//----- (00471DE0) --------------------------------------------------------
const char ** Compat_StringHolderPrependText(const char **holder_ref, const char *prepended_text)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  if ( prepended_text && *prepended_text )
    Compat_StringHolderAssignJoined(holder, prepended_text, Compat_StringHolderGetText(holder));
  return holder_ref;
}

//----- (00471EE0) --------------------------------------------------------
int  Compat_StringHolderFindSubstringOffset(_DWORD *holder, int a2, int needle)
{
  int match_ptr; // eax
  _DWORD *v5; // ecx

  if ( a2 && *holder && (match_ptr = ((int (__cdecl *)(int))(uintptr_t)strstr_)(needle)) != 0 )
    return match_ptr - *v5;
  else
    return -1;
}
// 471EFD: variable 'v5' is possibly undefined

//----- (00471F10) --------------------------------------------------------
const char ** Compat_StringHolderUppercaseInPlace(const char **holder_ref, unsigned int a2 CLASH95_UNUSED)
{
  const char *text; // eax

  text = Compat_StringHolderGetText((_DWORD *)holder_ref);
  if ( text && *text )
  {
    Compat_StringHolderAssignJoined((_DWORD *)holder_ref, text, 0);
    Compat_StruprAsciiInPlace((char *)Compat_StringHolderGetText((_DWORD *)holder_ref));
  }
  return holder_ref;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 47BBE3: using guessed type int __fastcall strupr_(_DWORD, _DWORD);

//----- (00472120) --------------------------------------------------------
int  Compat_StringHolderFindCharFrom(const char **holder_ref, char search_char, signed int start_index)
{
  const char *text;
  const char *match;
  unsigned int text_len;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)holder_ref);
  if ( !text || !*text || start_index < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)start_index >= text_len )
    return -1;
  match = strchr(text + start_index, search_char);
  if ( !match )
    return -1;
  return (int)(match - text);
}

//----- (00472190) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslash(_BYTE **holder_ref)
{
  const char *text;
  char *last_slash;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)holder_ref);
  if ( !text || !*text )
    return -1;
  last_slash = Compat_StrrchrChar(text, '\\');
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (004721C0) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslashBefore(char **holder_ref, signed int end_index)
{
  _DWORD *holder;
  char *text;
  unsigned int text_len;
  char saved_char;
  char *last_slash;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  text = (char *)Compat_StringHolderGetText(holder);
  if ( !text || !*text || end_index < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)end_index >= text_len )
    return -1;
  saved_char = text[end_index + 1];
  text[end_index + 1] = 0;
  last_slash = Compat_StrrchrChar(text, '\\');
  text[end_index + 1] = saved_char;
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (00472230) --------------------------------------------------------
char ** Compat_StringHolderRemoveRange(char **holder_ref, int start_index, unsigned int a3, int remove_count)
{
  _DWORD *holder;
  const char *text;
  unsigned int text_len;
  char *copy;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  text = Compat_StringHolderGetText(holder);
  if ( !text || !*text || start_index < 0 )
    return holder_ref;
  text_len = (unsigned int)strlen(text);
  a3 = text_len;
  if ( text_len != (unsigned int)remove_count )
  {
    copy = (char *)(uintptr_t)(unsigned int)j_Mem_Alloc(a3 + 1);
    if ( !copy )
      return holder_ref;
    Compat_CopyPrefixN(copy, text, start_index);
    copy[start_index] = 0;
    if ( (unsigned int)(start_index + remove_count) < text_len )
      Compat_CopyPrefixN(copy + start_index, text + start_index + remove_count, text_len - (unsigned int)(start_index + remove_count) + 1);
    Compat_StringHolderFreeText(holder);
    *holder = (int)(uintptr_t)copy;
    j_j__nfree_();
    return holder_ref;
  }
  Compat_StringHolderDestructor(((_DWORD*)((const char **)holder)));
  return holder_ref;
}
// 47228D: variable 'v9' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00472320) --------------------------------------------------------
const char ** Compat_StringHolderInsertTextChecked(const char **result, signed int insert_index, const char *inserted_text)
{
  if ( insert_index >= 0 && inserted_text && *inserted_text )
    Compat_StringHolderInsertText((_DWORD *)result, insert_index, inserted_text);
  return result;
}

//----- (00472470) --------------------------------------------------------
_DWORD * Compat_StringHolderInitBase(_DWORD *result)
{
  *result = 0;
  result[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();

//----- (00472558) --------------------------------------------------------
void  __noreturn CRT_ExitProcessWithFinalizers(int exit_code, int a2, int a3)
{
  (void)a2;
  (void)a3;

  /*
   * The original CRT finalizer band is still under-recovered and currently
   * crashes inside `sub_4B52E6` on fatal quit paths under WSL. For process
   * termination we only need a reliable exit, so quarantine the finalizer walk
   * until its object-registration contract is reconstructed safely.
   */
  ExitProcess((UINT)exit_code);
}
// 472575: variable 'v5' is possibly undefined
// 47257C: variable 'v4' is possibly undefined
// 48569B: using guessed type int __fastcall _FiniRtns(_DWORD, _DWORD);
// 519EF4: using guessed type int (__fastcall *off_519EF4)(_DWORD, _DWORD);

//----- (00472584) --------------------------------------------------------
void  __noreturn CRT_ExitProcessRunFinalizers(int a1, int a2, int a3)
{
  int v3; // edx
  int v4; // ecx
  UINT exit_code; // ebx
  int v6; // ecx

  g_CRT_ExitFinalizerCallbackA(a3, a1);
  g_CRT_ExitFinalizerCallbackB(a2);
  if ( g_CRT_ExitProcessFinalizerHook )
    g_CRT_ExitProcessFinalizerHook();
  exit_code = v3;
  if ( g_CrtThreadDataMgmtDisabledFlag )
  {
    if ( g_CRT_ProcessExitThreadHook )
      g_CRT_ProcessExitThreadHook(v4, 255);
  }
  else
  {
    CRT_RemoveUnhandledExceptionFilter(v4, v3);
    _FiniRtns(v6, 15);
    g_CRT_TlsIndexDestroyHook();
  }
  ExitProcess(exit_code);
}
// 485601: variable 'v3' is possibly undefined
// 48561C: variable 'v4' is possibly undefined
// 485630: variable 'v6' is possibly undefined
// 485379: using guessed type _DWORD nullsub_8();
// 48569B: using guessed type int __fastcall _FiniRtns(_DWORD, _DWORD);
// 519EF4: using guessed type int (__fastcall *off_519EF4)(_DWORD, _DWORD);
// 519EF8: using guessed type int (__cdecl *off_519EF8)(_DWORD);
// 51A5A4: using guessed type _DWORD (*off_51A5A4)();
// 51A5B0: using guessed type int (__fastcall *dword_51A5B0)(_DWORD, _DWORD);
// 51A5F4: using guessed type int (*dword_51A5F4)(void);

//----- (004725B0) --------------------------------------------------------
int __fastcall Mem_InitReserveBlock(int a1, int a2)
{
  int result; // eax
  int v3; // ecx

  (void)a1;
  (void)a2;
  g_ClipsMemoryTable = nmalloc_(0x7D0, 0);
  if ( !g_ClipsMemoryTable )
  {
    Rules_PrintErrorID((int)(intptr_t)aMemory, 1, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOutOfMemory_, v3);
    IO_RunRouterExitCallbacks(1);
  }
  for ( result = 0; result != 2000; result += 4 )
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + result) = 0;
  return result;
}
// 472605: variable 'v3' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472620) --------------------------------------------------------
signed int  Mem_HeapAllocWithRetry(_DWORD *requested_bytes)
{
  int request_size;
  int grow_size;
  signed int result; // eax
  signed int (__fastcall *allocator_callback)(int);

  request_size = (int)(uintptr_t)requested_bytes;
  result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
  if ( result )
    goto LABEL_5;
  grow_size = 5 * request_size;
  if ( (unsigned int)grow_size <= 0x1000 )
    grow_size = 4096;
  Mem_PurgeFreeListsForSpace(grow_size, 0, request_size);
  result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
  if ( result || (Mem_PurgeFreeListsForSpace(-1, 1, request_size), (result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size)) != 0) )
  {
LABEL_5:
    g_Mem_TotalAllocatedBytes += request_size;
    ++g_Mem_TotalAllocationCount;
  }
  else
  {
    allocator_callback = (signed int (__fastcall *)(int))g_Mem_OutOfMemoryHandler;
    while ( !allocator_callback(request_size) )
    {
      result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
      if ( result )
        goto LABEL_5;
    }
    return 0;
  }
  return result;
}
// 519EFC: using guessed type int dword_519EFC;
// 519F00: using guessed type int dword_519F00;
// 519F10: using guessed type signed int (*off_519F10)();

//----- (004726C0) --------------------------------------------------------
signed int Mem_FatalOutOfMemory(void)
{
  int v0; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMemory, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOutOfMemory_, v0);
  IO_RunRouterExitCallbacks(1);
  return 1;
}
// 4726DD: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00472700) --------------------------------------------------------
int Mem_SetOutOfMemoryHandler(int a1)
{
  int previous_handler;

  previous_handler = (int)(intptr_t)g_Mem_OutOfMemoryHandler;
  g_Mem_OutOfMemoryHandler = (signed int (*)())(intptr_t)a1;
  return previous_handler;
}

//----- (00472710) --------------------------------------------------------
signed int  Mem_ReleasePoolBlock(int block, int block_size)
{
  int v2; // ecx
  signed int result; // eax
  int v4; // ecx

  if ( Mem_PoolFreeCoalesce(block, block_size) )
  {
    result = 0;
    g_Mem_TotalAllocatedBytes -= v2;
    --g_Mem_TotalAllocationCount;
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aMemory, 2, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aReleaseErrorIn, v4);
    return -1;
  }
  return result;
}
// 47272D: variable 'v2' is possibly undefined
// 47275A: variable 'v4' is possibly undefined
// 519EFC: using guessed type int dword_519EFC;
// 519F00: using guessed type int dword_519F00;
// 51A614: using guessed type char *off_51A614[5];

//----- (00472770) --------------------------------------------------------
_DWORD * Mem_Realloc(char *old_block, unsigned int old_size, unsigned int new_size)
{
  _DWORD *alloc_result; // eax
  int copy_size; // edx
  int copy_limit; // edi
  unsigned int v8; // eax
  _DWORD *dest_cursor; // edx
  char *src_cursor; // ecx
  char v11; // bl
  _BYTE *zero_cursor; // edx
  _DWORD *new_block; // [esp+0h] [ebp-10h]

  if ( new_size )
    alloc_result = Mem_SmallBlockAlloc(new_size);
  else
    alloc_result = 0;
  new_block = alloc_result;
  if ( old_block )
  {
    if ( old_size >= new_size )
      copy_size = new_size;
    else
      copy_size = old_size;
    copy_limit = copy_size;
    v8 = 0;
    if ( copy_size > 0 )
    {
      dest_cursor = new_block;
      src_cursor = old_block;
      do
      {
        dest_cursor = (_DWORD *)((char *)dest_cursor + 1);
        v11 = *src_cursor++;
        ++v8;
        *((_BYTE *)dest_cursor - 1) = v11;
      }
      while ( (int)v8 < copy_limit );
    }
    zero_cursor = ((_BYTE*)((char *)new_block + v8));
    while ( v8 < new_size )
    {
      ++v8;
      *zero_cursor++ = 0;
    }
    Mem_SmallBlockFree(((_DWORD*)(old_block)), old_size);
  }
  return new_block;
}

//----- (00472800) --------------------------------------------------------
int Mem_GetTotalAllocatedBytes(void)
{
  return g_Mem_TotalAllocatedBytes;
}
// 519EFC: using guessed type int dword_519EFC;

//----- (00472810) --------------------------------------------------------
int Mem_GetTotalAllocationCount(void)
{
  return g_Mem_TotalAllocationCount;
}
// 519F00: using guessed type int dword_519F00;

//----- (00472860) --------------------------------------------------------
int  Mem_PurgeFreeListsForSpace(int bytes_needed, int verbose_flag, int request_size)
{
  int freed_bytes; // esi
  unsigned int size_class; // ecx
  int table_offset; // edi
  int free_node; // eax
  int next_node; // ebx

  freed_bytes = 0;
  if ( verbose_flag == 1 )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aDeallocatingMe, request_size);
  size_class = 499;
  table_offset = 1996;
  do
  {
    free_node = *(_DWORD *)(uintptr_t)(table_offset + g_ClipsMemoryTable);
    if ( free_node )
    {
      do
      {
        next_node = *(_DWORD *)(uintptr_t)(unsigned int)free_node;
        Mem_ReleasePoolBlock((int)free_node, size_class);
        freed_bytes += size_class;
        free_node = next_node;
      }
      while ( next_node );
    }
    *(_DWORD *)(uintptr_t)(table_offset + g_ClipsMemoryTable) = 0;
    if ( freed_bytes > bytes_needed && bytes_needed > 0 )
      break;
    --size_class;
    table_offset -= 4;
  }
  while ( size_class >= 4 );
  if ( verbose_flag == 1 )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aMemoryDealloca, size_class);
  return freed_bytes;
}
// 47288E: variable 'v5' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004728F0) --------------------------------------------------------
_BYTE * Mem_SmallBlockAllocZeroed(unsigned int size)
{
  signed int clamped_size; // ecx
  int free_list_slot; // eax
  int free_node; // edx
  int block; // esi
  signed int i; // eax
  _BYTE *zero_cursor; // edx
  int allocation_size; // ecx
  int allocated_block; // esi
  int j; // eax

  clamped_size = size;
  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_BYTE *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)size);
  }
  else
  {
    clamped_size = 4;
  }
  free_list_slot = 4 * clamped_size + g_ClipsMemoryTable;
  free_node = *(_DWORD *)(uintptr_t)free_list_slot;
  if ( free_node )
  {
    block = free_node;
    *(_DWORD *)(uintptr_t)free_list_slot = *(_DWORD *)(uintptr_t)free_node;
    for ( i = 0; i < clamped_size; ++free_node )
    {
      ++i;
      *(_BYTE *)(uintptr_t)free_node = 0;
    }
    return (_BYTE *)(uintptr_t)block;
  }
  else
  {
    allocation_size = clamped_size;
    zero_cursor = (_BYTE *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)allocation_size);
    allocated_block = (int)(intptr_t)zero_cursor;
    for ( j = 0; j < allocation_size; ++zero_cursor )
    {
      ++j;
      *zero_cursor = 0;
    }
    return (_BYTE *)(uintptr_t)allocated_block;
  }
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472980) --------------------------------------------------------
_DWORD * Mem_SmallBlockAlloc(unsigned int size)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)size);
  }
  else
  {
    size = 4;
  }
  free_list_slot = g_ClipsMemoryTable + 4 * size;
  free_node = *(_DWORD *)(uintptr_t)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)(uintptr_t)free_list_slot = *(_DWORD *)(uintptr_t)free_node;
    return (_DWORD *)(uintptr_t)free_node;
  }
  return (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)size);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004729C0) --------------------------------------------------------
_DWORD * Mem_NewArray(unsigned int size)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)size);
  }
  else
  {
    size = 4;
  }
  free_list_slot = g_ClipsMemoryTable + 4 * size;
  free_node = *(_DWORD *)(uintptr_t)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)(uintptr_t)free_list_slot = *(_DWORD *)(uintptr_t)free_node;
    return (_DWORD *)(uintptr_t)free_node;
  }
  return (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)size);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A00) --------------------------------------------------------
signed int  Mem_SmallBlockFree(_DWORD *block, int size)
{
  int clamped_size; // ecx

  clamped_size = size;
  if ( !size )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks(3);
  }
  if ( (unsigned int)clamped_size < 4 )
  {
    clamped_size = 4;
LABEL_5:
    *block = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * clamped_size);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * clamped_size) = ((_DWORD)(uintptr_t)(block));
    return 1;
  }
  if ( clamped_size < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)(intptr_t)block, clamped_size);
}
// 472A0D: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A60) --------------------------------------------------------
signed int  Mem_SmallBlockRelease(_DWORD *block, int size)
{
  int clamped_size; // ecx

  clamped_size = size;
  if ( !size )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks(3);
  }
  if ( (unsigned int)clamped_size < 4 )
  {
    clamped_size = 4;
LABEL_5:
    *block = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * clamped_size);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * clamped_size) = ((_DWORD)(uintptr_t)(block));
    return 1;
  }
  if ( clamped_size < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)(intptr_t)block, clamped_size);
}
// 472A6D: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472B10) --------------------------------------------------------
int Mem_GetAllocFlag(void)
{
  return g_Mem_AllocFlag;
}
// 519F04: using guessed type int dword_519F04;

//----- (00472B50) --------------------------------------------------------
signed int  Mem_InitPool(unsigned int requested_bytes, char a2)
{
  unsigned int request_size;
  int block_header_bytes;
  int available_size;
  int first_block;
  int tail_header;

  request_size = requested_bytes;
  g_MemPoolBlockHeaderSize = 16;
  g_HeapChunkHeaderSize = 16;
  if ( requested_bytes < 0x3E800 )
    requested_bytes = 256000;
  block_header_bytes = 2 * g_MemPoolBlockHeaderSize;
  available_size = 8 * ((g_HeapChunkHeaderSize + block_header_bytes + requested_bytes - 1) >> 3) + 8 - block_header_bytes - g_HeapChunkHeaderSize;
  if ( request_size < 0x3E800 && (unsigned int)available_size <= request_size + g_MemPoolBlockHeaderSize )
    available_size = 8 * ((g_HeapChunkHeaderSize + request_size + block_header_bytes - 1) >> 3) + 8 - block_header_bytes - g_HeapChunkHeaderSize;
  /* loc_472BD4 calls _nmalloc_ with EAX = the ROUNDED TOTAL (available_size
     + 2*g_MemPoolBlockHeaderSize + g_HeapChunkHeaderSize); ECX (= available_size)
     is only what gets stored at [pool+0Ch]. The recovery passed ECX as the size,
     under-allocating by 48 bytes and putting the tail sentinel out of bounds. */
  g_MemPoolListHead = nmalloc_(available_size + block_header_bytes + g_HeapChunkHeaderSize, 0);
  if ( g_MemPoolListHead )
  {
    *(_DWORD *)(uintptr_t)g_MemPoolListHead = 0;
    *(_DWORD *)(uintptr_t)(g_MemPoolListHead + 4) = 0;
    first_block = g_MemPoolListHead + g_HeapChunkHeaderSize;
    *(_DWORD *)(uintptr_t)(g_MemPoolListHead + 8) = first_block;
    *(_DWORD *)(uintptr_t)(g_MemPoolListHead + 12) = available_size;
    tail_header = g_MemPoolListHead + g_HeapChunkHeaderSize + g_MemPoolBlockHeaderSize + available_size;
    *(_DWORD *)(uintptr_t)(tail_header + 4) = 0;
    *(_DWORD *)(uintptr_t)(tail_header + 8) = 0;
    *(_DWORD *)(uintptr_t)(tail_header + 12) = 0;
    *(_DWORD *)(uintptr_t)tail_header = first_block;
    *(_DWORD *)(uintptr_t)(first_block + 4) = 0;
    *(_DWORD *)(uintptr_t)(first_block + 8) = 0;
    *(_DWORD *)(uintptr_t)first_block = 0;
    *(_DWORD *)(uintptr_t)(first_block + 12) = available_size;
    g_Mem_PoolInitializedFlag = 1;
    return 1;
  }
  else
  {
    Output_WriteFormatted(0, 0, (int)(intptr_t)&g_CRT_StdoutStream, (int)(intptr_t)aUnableToAlloca, a2);
    return 0;
  }
}
// 472B50: could not find valid save-restore pair for esi
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 519F0C: using guessed type int dword_519F0C;
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472CB0) --------------------------------------------------------
int  Mem_GrowPoolChain(int pool, unsigned int requested_bytes)
{
  int available_size;
  int new_pool;
  int first_block;
  int tail_header;

  if ( requested_bytes < 0x3E800 )
    requested_bytes = 256000;
  available_size = 8 * ((requested_bytes + 2 * g_MemPoolBlockHeaderSize + g_HeapChunkHeaderSize - 1) >> 3) + 8 - g_HeapChunkHeaderSize - 2 * g_MemPoolBlockHeaderSize;
  /* sub_472CB0: same as sub_472B50 - _nmalloc_ receives EAX = the rounded total;
     EDX (= available_size) is only the value stored at [pool+0Ch]. */
  new_pool = nmalloc_(available_size + 2 * g_MemPoolBlockHeaderSize + g_HeapChunkHeaderSize, 0);
  if ( new_pool )
  {
    *(_DWORD *)(uintptr_t)new_pool = 0;
    *(_DWORD *)(uintptr_t)(new_pool + 4) = pool;
    first_block = new_pool + g_HeapChunkHeaderSize;
    *(_DWORD *)(uintptr_t)(new_pool + 12) = available_size;
    *(_DWORD *)(uintptr_t)(new_pool + 8) = first_block;
    *(_DWORD *)(uintptr_t)pool = new_pool;
    tail_header = new_pool + g_HeapChunkHeaderSize + g_MemPoolBlockHeaderSize + available_size;
    *(_DWORD *)(uintptr_t)(tail_header + 4) = 0;
    *(_DWORD *)(uintptr_t)(tail_header + 8) = 0;
    *(_DWORD *)(uintptr_t)(tail_header + 12) = 0;
    *(_DWORD *)(uintptr_t)tail_header = first_block;
    *(_DWORD *)(uintptr_t)(first_block + 4) = 0;
    *(_DWORD *)(uintptr_t)(first_block + 8) = 0;
    *(_DWORD *)(uintptr_t)first_block = 0;
    *(_DWORD *)(uintptr_t)(first_block + 12) = available_size;
    return 1;
  }
  return 0;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472D70) --------------------------------------------------------
signed int  Mem_PoolAllocBlock(unsigned int size, _DWORD *error_context)
{
  _DWORD *pool;
  _DWORD *block;
  unsigned int requested_size;
  signed int result; // eax
  int callback_arg;

  if ( !g_Mem_PoolInitializedFlag )
  {
    result = Mem_InitPool(size, size);
    if ( !result )
      return result;
    IO_AddRouter((int)(intptr_t)aBmexit, -2000, 0, 0, 0, 0, (int)(intptr_t)Mem_HeapExitHandler);
  }
  requested_size = 8 * ((size - 1) >> 3) + 8;
  if ( g_MemPoolListHead )
  {
    pool = (_DWORD *)(uintptr_t)g_MemPoolListHead;
    while ( 1 )
    {
      block = (_DWORD *)(uintptr_t)pool[2];
      while ( block )
      {
        if ( requested_size == (unsigned int)block[3] || requested_size + g_MemPoolBlockHeaderSize < (unsigned int)block[3] )
        {
          Mem_PoolSplitBlock((int)(uintptr_t)pool, block, requested_size);
          return (int)(uintptr_t)((char *)block + g_MemPoolBlockHeaderSize);
        }
        block = (_DWORD *)(uintptr_t)block[1];
      }
      if ( !*pool )
      {
        result = Mem_GrowPoolChain((int)(uintptr_t)pool, requested_size);
        if ( !result )
          return result;
      }
      pool = (_DWORD *)(uintptr_t)*pool;
      if ( !pool )
        break;
    }
LABEL_10:
    callback_arg = (int)(uintptr_t)error_context;
    Rules_ReportSystemError(callback_arg, 2);
    IO_RunRouterExitCallbacks(1);
    return 0;
  }
  goto LABEL_10;
}
// 519F0C: using guessed type int dword_519F0C;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472E40) --------------------------------------------------------
int  Mem_PoolSplitBlock(int result, _DWORD *block, int alloc_size)
{
  int pool;
  int block_size;
  int previous_free;
  int next_free;
  _DWORD *tail_header;
  _DWORD *split_block;
  int prev_of_split;
  int next_of_split;

  pool = result;
  block_size = block[3];
  if ( alloc_size == block_size )
  {
    previous_free = block[2];
    block[3] = -alloc_size;
    if ( previous_free )
    {
      *(_DWORD *)(uintptr_t)(previous_free + 4) = block[1];
    }
    else
    {
      next_free = block[1];
      if ( next_free )
        *(_DWORD *)(uintptr_t)(pool + 8) = next_free;
      else
        *(_DWORD *)(uintptr_t)(pool + 8) = 0;
    }
    next_free = block[1];
    if ( next_free )
    {
      *(_DWORD *)(uintptr_t)(next_free + 8) = block[2];
    }
    block[2] = 0;
    block[1] = 0;
  }
  else
  {
    tail_header = (_DWORD *)((char *)block + g_MemPoolBlockHeaderSize + block_size);
    split_block = (_DWORD *)((char *)block + g_MemPoolBlockHeaderSize + alloc_size);
    split_block[3] = block_size - (alloc_size + g_MemPoolBlockHeaderSize);
    *split_block = ((_DWORD)(uintptr_t)(block));
    split_block[1] = block[1];
    split_block[2] = block[2];
    *tail_header = ((_DWORD)(uintptr_t)(split_block));
    prev_of_split = split_block[2];
    if ( prev_of_split )
      *(_DWORD *)(uintptr_t)(prev_of_split + 4) = (int)(uintptr_t)split_block;
    else
      *(_DWORD *)(uintptr_t)(pool + 8) = (int)(uintptr_t)split_block;
    next_of_split = split_block[1];
    if ( next_of_split )
      *(_DWORD *)(uintptr_t)(next_of_split + 8) = (int)(uintptr_t)split_block;
    block[2] = 0;
    block[1] = 0;
    block[3] = -alloc_size;
    result = -alloc_size;
  }
  return result;
}
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472F00) --------------------------------------------------------
signed int  Mem_PoolFreeCoalesce(int block_ptr, int block_size)
{
  unsigned int aligned_size; // ebx
  _DWORD *block_record; // edx
  int stored_size; // edi
  int next_link; // ecx
  _DWORD *chain_cursor; // eax
  int *pool_header; // eax
  _DWORD *adjacent_block; // ebx
  int freelist_head; // esi
  _DWORD *chained_block; // ecx
  int old_freelist_head; // esi
  int chained_size; // edi
  int prev_free; // ebp
  int next_free; // esi
  int adjacent_size; // ebp
  _DWORD *following_block; // ecx
  int adjacent_next; // esi
  int *unlink_node; // ecx
  int chain_next; // edx
  int pool_next; // ecx

  aligned_size = 8 * ((unsigned int)(block_size - 1) >> 3) + 8;
  block_record = (_DWORD *)(uintptr_t)(block_ptr - g_MemPoolBlockHeaderSize);
  if ( block_ptr == g_MemPoolBlockHeaderSize )
    return 0;
  stored_size = block_record[3];
  if ( stored_size >= 0 || -aligned_size != stored_size )
    return 0;
  next_link = *block_record;
  block_record[3] = aligned_size;
  chain_cursor = block_record;
  if ( next_link )
  {
    do
      chain_cursor = (_DWORD *)(uintptr_t)*chain_cursor;
    while ( *chain_cursor );
  }
  pool_header = ((int*)((_DWORD *)((char *)chain_cursor - g_HeapChunkHeaderSize)));
  adjacent_block = (_DWORD *)(uintptr_t)(block_ptr + aligned_size);
  freelist_head = pool_header[2];
  chained_block = (_DWORD *)(uintptr_t)*block_record;
  if ( freelist_head )
    *(_DWORD *)(uintptr_t)(freelist_head + 8) = ((_DWORD)(uintptr_t)(block_record));
  old_freelist_head = pool_header[2];
  block_record[2] = 0;
  block_record[1] = old_freelist_head;
  pool_header[2] = (int)(intptr_t)block_record;
  if ( chained_block )
  {
    chained_size = chained_block[3];
    if ( chained_size > 0 )
    {
      chained_block[3] = block_record[3] + g_MemPoolBlockHeaderSize + chained_size;
      if ( !adjacent_block )
        return 0;
      *adjacent_block = ((_DWORD)(uintptr_t)(chained_block));
      prev_free = chained_block[2];
      if ( prev_free )
        *(_DWORD *)(uintptr_t)(prev_free + 4) = chained_block[1];
      if ( chained_block[1] )
        *(_DWORD *)(uintptr_t)(chained_block[1] + 8) = chained_block[2];
      next_free = block_record[1];
      chained_block[1] = next_free;
      if ( next_free )
        *(_DWORD *)(uintptr_t)(next_free + 8) = ((_DWORD)(uintptr_t)(chained_block));
      chained_block[2] = 0;
      pool_header[2] = (int)(intptr_t)chained_block;
      block_record[2] = 0;
      block_record[1] = 0;
      block_record = chained_block;
    }
  }
  if ( !adjacent_block || !block_record )
    return 0;
  adjacent_size = adjacent_block[3];
  if ( adjacent_size > 0 )
  {
    block_record[3] += adjacent_size + g_MemPoolBlockHeaderSize;
    following_block = (_DWORD *)((char *)adjacent_block + adjacent_block[3] + g_MemPoolBlockHeaderSize);
    if ( following_block )
    {
      *following_block = ((_DWORD)(uintptr_t)(block_record));
      if ( adjacent_block[2] )
        *(_DWORD *)(uintptr_t)(adjacent_block[2] + 4) = adjacent_block[1];
      adjacent_next = adjacent_block[1];
      if ( adjacent_next )
        *(_DWORD *)(uintptr_t)(adjacent_next + 8) = adjacent_block[2];
      goto LABEL_27;
    }
    return 0;
  }
LABEL_27:
  if ( *block_record || block_record[3] != pool_header[3] )
    return 1;
  if ( pool_header[1] )
  {
    unlink_node = (int *)(uintptr_t)pool_header[1];
    chain_next = *pool_header;
    *unlink_node = *pool_header;
    if ( chain_next )
    {
      unlink_node = (int *)(uintptr_t)chain_next;
      *(_DWORD *)(uintptr_t)(chain_next + 4) = pool_header[1];
    }
    /* Original EAX still holds the removed pool, not the ECX link cursor. */
    nfree_((_DWORD)(uintptr_t)pool_header);
    return 1;
  }
  pool_next = *pool_header;
  if ( !*pool_header )
    return 1;
  *(_DWORD *)(uintptr_t)(pool_next + 4) = 0;
  g_MemPoolListHead = *pool_header;
  /* The new head remains allocated; original EAX still holds pool_header. */
  nfree_((_DWORD)(uintptr_t)pool_header);
  return 1;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00473090) --------------------------------------------------------
int __thiscall Mem_ReleaseAllPools(void *this_)
{
  int result; // eax
  int next_pool;
  int freelist_next;

  (void)this_;

  if ( g_MemPoolListHead )
  {
    do
    {
      next_pool = *(_DWORD *)(uintptr_t)g_MemPoolListHead;
      nfree_(g_MemPoolListHead);
      g_MemPoolListHead = next_pool;
    }
    while ( next_pool );
  }
  result = g_Mem_ReservedBlockListHead;
  g_MemPoolListHead = 0;
  if ( g_Mem_ReservedBlockListHead )
  {
    do
    {
      freelist_next = *(_DWORD *)(uintptr_t)(result + 4);
      Mem_ReleasePoolBlock(result, *(_DWORD *)(uintptr_t)(result + 8));
      result = freelist_next;
    }
    while ( freelist_next );
  }
  g_Mem_ReservedBlockListHead = 0;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 519F08: using guessed type int dword_519F08;
// 54DBBC: using guessed type int dword_54DBBC;

//----- (004730F0) --------------------------------------------------------
int __thiscall Mem_HeapExitHandler(void *this_)
{
  Mem_ReleaseAllPools(this_);
  return 1;
}

//----- (00473250) --------------------------------------------------------
_DWORD * Surface_Construct(_DWORD *result)
{
  result[43] = ((_DWORD)(uintptr_t)(g_Surface_BlitFunctionTable));
  result[41] = 0;
  result[3] = 0;
  result[13] = 0;
  result[42] = 0;
  result[4] = -1;
  result[10] = 0;
  result[9] = 0;
  result[12] = 0;
  result[11] = 0;
  return result;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (004732A0) --------------------------------------------------------
_DWORD * Surface_ConstructWithSurface(_DWORD *surface, _DWORD *ddraw_obj, int height, int width)
{
  surface[43] = ((_DWORD)(uintptr_t)(g_Surface_BlitFunctionTable));
  if ( !Surface_CreateDDSurface(surface, ddraw_obj, height, width) )
    return 0;
  return surface;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (004732E0) --------------------------------------------------------
int  Surface_Destruct(int result)
{
  int surface; // ebx
  int dd_surface; // edx

  surface = result;
  dd_surface = *(_DWORD *)(uintptr_t)(result + 164);
  *(_DWORD *)(uintptr_t)(result + 172) = ((_DWORD)(uintptr_t)(g_Surface_BlitFunctionTable));
  if ( dd_surface )
  {
    (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)dd_surface + 8))(dd_surface);
    *(_DWORD *)(uintptr_t)(surface + 164) = 0;
    return surface;
  }
  return result;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (00473320) --------------------------------------------------------
signed int  Surface_CreateDDSurface(_DWORD *surface, _DWORD *ddraw_obj, int height, int width)
{
  HRESULT hr;
  int direct_draw_handle;

  if ( !surface )
    return 0;
  memset(surface + 14, 0, 108);
  surface[14] = 108;
  surface[15] = 7;
  surface[40] = 64;
  surface[16] = height;
  surface[17] = width;
  if ( !ddraw_obj )
    return 0;
  direct_draw_handle = *ddraw_obj;
  if ( !direct_draw_handle )
    return 0;
  hr = Compat_DirectDraw_CreateSurface(
         (LPDIRECTDRAW)(uintptr_t)(unsigned int)direct_draw_handle,
         (int *)(surface + 14),
         surface + 41);
  if ( hr )
  {
    Render_HandleDirectDrawFatalError(hr, ddraw_obj[9]);
    return 0;
  }
  surface[4] = -1;
  surface[10] = 0;
  surface[9] = 0;
  surface[6] = 0;
  surface[5] = 0;
  surface[3] = 0;
  surface[13] = 0;
  surface[2] = 0;
  surface[42] = ((_DWORD)(uintptr_t)(ddraw_obj));
  surface[1] = height;
  *surface = width;
  surface[12] = surface[1];
  surface[11] = *surface;
  surface[8] = surface[1];
  surface[7] = *surface;
  return 1;
}

//----- (004733F0) --------------------------------------------------------
int  Surface_CreateFromBitmapFile(_DWORD *surface, int *ddraw_obj, const CHAR *bitmap_path)
{
  int result; // eax
  int v6; // ecx
  int surface_height; // eax

  if ( !bitmap_path )
    return 0;
  result = Surface_DDCopyBitmapToNewSurface(*ddraw_obj, bitmap_path, surface + 1, (int)(intptr_t)surface);
  surface[41] = result;
  if ( result )
  {
    surface[3] = 0;
    surface[13] = 0;
    surface[4] = -1;
    surface[10] = 0;
    surface[9] = 0;
    surface[6] = 0;
    surface[5] = 0;
    surface_height = surface[1];
    surface[2] = ((_DWORD)(uintptr_t)(bitmap_path));
    surface[12] = surface_height;
    surface[11] = *surface;
    surface[8] = surface[1];
    surface[7] = *surface;
    surface[42] = ((_DWORD)(uintptr_t)(ddraw_obj));
    memset_(v6, 0);
    surface[14] = 108;
    surface[15] = 7;
    surface[40] = 64;
    surface[17] = *surface;
    surface[16] = surface[1];
    return 1;
  }
  return result;
}
// 473477: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004734B0) --------------------------------------------------------
int  Surface_BltOntoSurface(int surface, int dest_surface)
{
  int result; // eax
  int v4; // edx

  result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(dest_surface + 164) + 20))(
             *(_DWORD *)(uintptr_t)(dest_surface + 164),
             surface + 36,
             *(_DWORD *)(uintptr_t)(surface + 164),
             surface + 20,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(surface);
    return v4;
  }
  return result;
}
// 4734EB: variable 'v4' is possibly undefined

//----- (004734F0) --------------------------------------------------------
int  Surface_BltFastOpaqueTo(int src_surface, int dest_x, int dest_surface, int dest_y)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(dest_surface + 164) + 28))(
             *(_DWORD *)(uintptr_t)(dest_surface + 164),
             dest_x,
             dest_y,
             *(_DWORD *)(uintptr_t)(src_surface + 164),
             src_surface + 20,
             16);
  if ( result == -2005532222 )
  {
    Surface_Restore(src_surface);
    return -2005532222;
  }
  return result;
}

//----- (00473530) --------------------------------------------------------
int  Surface_BltFastKeyedTo(int src_surface, int dest_x, int dest_surface, int dest_y)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(dest_surface + 164) + 28))(
             *(_DWORD *)(uintptr_t)(dest_surface + 164),
             dest_x,
             dest_y,
             *(_DWORD *)(uintptr_t)(src_surface + 164),
             src_surface + 20,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore(src_surface);
    return -2005532222;
  }
  return result;
}

//----- (00473570) --------------------------------------------------------
int  Surface_BltFastKeyedClippedTo(_DWORD *src_surface, int dest_x, int dest_surface, int dest_y, _DWORD *clip_bounds)
{
  int result; // eax
  int v7; // edx
  _DWORD src_rect[4]; // [esp+0h] [ebp-28h] BYREF
  int blit_x; // [esp+10h] [ebp-18h] BYREF
  int blit_y; // [esp+14h] [ebp-14h] BYREF
  int target_surface; // [esp+18h] [ebp-10h]

  blit_x = dest_x;
  blit_y = dest_y;
  target_surface = dest_surface;
  src_rect[0] = src_surface[5];
  src_rect[1] = src_surface[6];
  src_rect[2] = src_surface[7];
  src_rect[3] = src_surface[8];
  Render_ClampBlitRectToBounds(((_DWORD*)(&blit_x)), ((_DWORD*)(&blit_y)), clip_bounds, src_rect);
  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, _DWORD *, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(target_surface + 164) + 28))(
             *(_DWORD *)(uintptr_t)(target_surface + 164),
             blit_x,
             blit_y,
             src_surface[41],
             src_rect,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)(intptr_t)src_surface);
    return v7;
  }
  return result;
}
// 473570: could not find valid save-restore pair for ebx
// 4735E3: variable 'v7' is possibly undefined
