/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../clips/clips_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00477CE0) --------------------------------------------------------
_DWORD * Compat_FileStreamOpen(_DWORD *stream, const CHAR *file_path, int a3, char mode_flags, DWORD a5)
{
  char *mode_string; // edx

  *stream = ((_DWORD)(uintptr_t)(g_CompatFileStream_VTable));
  if ( (mode_flags & 0x10) != 0 )
  {
    if ( (mode_flags & 2) != 0 )
      mode_string = aAb_0;
    else
      mode_string = aA_3;
  }
  else if ( (mode_flags & 8) != 0 )
  {
    if ( (mode_flags & 2) != 0 )
      mode_string = aWb_8;
    else
      mode_string = aW_7;
  }
  else if ( (mode_flags & 2) != 0 )
  {
    mode_string = aRb_10;
  }
  else
  {
    mode_string = aR_7;
  }
  stream[1] = IO_FOpen(file_path, (unsigned __int8 *)mode_string, a3, a5);
  if ( (mode_flags & 0x20) != 0 )
    Compat_StreamSetBuffer((int)stream[1], 0x1800);
  return stream;
}
// 5109C4: using guessed type int (*off_5109C4[9])();

//----- (00477D60) --------------------------------------------------------
_DWORD * Compat_FileStreamRelease(_DWORD *result, char flags)
{
  int stream_handle; // ebx
  int v4; // ecx
  int v5; // ecx
  int v7; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(result)), ((_DWORD)(uintptr_t)(&g_CompatFileStream_DtorArrayDescriptor)));
    j_j__nfree_();
    return (_DWORD *)(uintptr_t)v4;
  }
  stream_handle = result[1];
  *result = ((_DWORD)(uintptr_t)(g_CompatFileStream_VTable));
  if ( stream_handle )
  {
    fclose_(stream_handle);
    if ( (flags & 2) == 0 )
      return (_DWORD *)(uintptr_t)v5;
    goto LABEL_8;
  }
  if ( (flags & 2) != 0 )
  {
LABEL_8:
    j__nfree_();
    return (_DWORD *)(uintptr_t)v7;
  }
  return result;
}
// 477D8F: variable 'v4' is possibly undefined
// 477DA0: variable 'v5' is possibly undefined
// 477DAC: variable 'v7' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5109C4: using guessed type int (*off_5109C4[9])();

//----- (00477DC0) --------------------------------------------------------
int Compat_FileStreamRead(int stream, void *buffer, int a3)
{
  return fread_(buffer, 1, *(_DWORD *)(uintptr_t)(stream + 4), a3);
}

//----- (00477DE0) --------------------------------------------------------
int  Compat_FileStreamReadChar(int stream, unsigned int a2)
{
  int stream_ptr;
  unsigned __int8 next_byte;

  (void)a2;
  stream_ptr = *(_DWORD *)(uintptr_t)(stream + 4);
  if ( *(_DWORD *)(uintptr_t)(stream_ptr + 4) > 0 )
  {
    next_byte = *(unsigned __int8 *)(uintptr_t)*(_DWORD *)(uintptr_t)stream_ptr;
    if ( (unsigned int)(next_byte - 13) > 0xFD )
    {
      --*(_DWORD *)(uintptr_t)(stream_ptr + 4);
      ++*(_DWORD *)(uintptr_t)stream_ptr;
      return next_byte;
    }
  }
  if ( Compat_StreamRead(stream_ptr, &next_byte, 1) == 1 )
    return next_byte;
  return -1;
}

//----- (00477E30) --------------------------------------------------------
signed int  Compat_FileStreamUngetChar(int stream, signed int pushed_char)
{
  return CRT_FlushBufferAndPutChar(pushed_char, stream);
}

//----- (00477E40) --------------------------------------------------------
int  Compat_FileStreamWrite(int stream, const void *buffer, int a3)
{
  return fwrite_(buffer, 1, *(_DWORD *)(uintptr_t)(stream + 4), a3);
}

//----- (00477E60) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromStart(int stream, int offset, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(uintptr_t)(stream + 4), offset, 0, a3);
}

//----- (00477E70) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromEnd(int stream, int offset, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(uintptr_t)(stream + 4), offset, 2u, a3);
}

//----- (00477E80) --------------------------------------------------------
int __fastcall Compat_FileStreamTell(int stream, int a2 CLASH95_UNUSED)
{
  return Compat_StreamTell(*(_DWORD *)(uintptr_t)(stream + 4));
}

//----- (00477E90) --------------------------------------------------------
signed int  Compat_FileStreamIsReady(int stream)
{
  int stream_handle; // edx

  stream_handle = *(_DWORD *)(uintptr_t)(stream + 4);
  if ( !stream_handle )
    return -2;
  if ( (*(_BYTE *)(uintptr_t)(stream_handle + 12) & 0x10) != 0 )
    return -1;
  return 1;
}

//----- (00477EC0) --------------------------------------------------------
int  Compat_FileFinderOpen(_DWORD *finder, int search_path)
{
  int v2; // ecx
  signed int find_handle; // eax
  int v4; // ecx
  int v5; // ecx
  const char *pattern_holder; // [esp+0h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-14h]
  int search_path_saved CLASH95_UNUSED; // [esp+10h] [ebp-8h]

  search_path_saved = search_path;
  finder[71] = -1;
  *finder = ((_DWORD)(uintptr_t)(g_CompatFileFinder_VTable));
  pattern_holder = 0;
  vtable_ptr = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&pattern_holder)));
  vtable_ptr = ((int (**)())(&g_PathEntry_Vtable));
  Compat_StringHolderAppendText(&pattern_holder, a__31);
  find_handle = CRT_FindFirstFile(pattern_holder, (_DWORD *)(uintptr_t)(v2 + 4), v2);
  *(_DWORD *)(uintptr_t)(v4 + 284) = find_handle;
  *(_DWORD *)(uintptr_t)(v4 + 288) = find_handle;
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&pattern_holder, 1);
  return v5;
}
// 477F06: variable 'v2' is possibly undefined
// 477F0E: variable 'v4' is possibly undefined
// 477F26: variable 'v5' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 5109F4: using guessed type int (*off_5109F4[6])();

//----- (00477F30) --------------------------------------------------------
_DWORD * Compat_FileFinderRelease(_DWORD *result, char flags)
{
  int find_handle; // ebx
  int v4; // ecx
  int v5; // ecx
  char v6; // dl
  int v7; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(result)), ((_DWORD)(uintptr_t)(&g_CompatFileFinder_DtorArrayDescriptor)));
    j_j__nfree_();
    return (_DWORD *)(uintptr_t)v4;
  }
  find_handle = result[71];
  *result = ((_DWORD)(uintptr_t)(g_CompatFileFinder_VTable));
  if ( find_handle == -1 )
  {
    findclose_(((_DWORD)(uintptr_t)(result)));
    if ( (v6 & 2) == 0 )
      return (_DWORD *)(uintptr_t)v5;
    goto LABEL_8;
  }
  if ( (flags & 2) != 0 )
  {
LABEL_8:
    j__nfree_();
    return (_DWORD *)(uintptr_t)v7;
  }
  return result;
}
// 477F63: variable 'v4' is possibly undefined
// 477F6F: variable 'v6' is possibly undefined
// 477F74: variable 'v5' is possibly undefined
// 477F80: variable 'v7' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 489F44: using guessed type int __thiscall findclose_(_DWORD);
// 5109F4: using guessed type int (*off_5109F4[6])();

//----- (00477F90) --------------------------------------------------------
int  Compat_FileFinderHasEntry(int result)
{
  if ( *(_DWORD *)(uintptr_t)(result + 288) == -1 )
    return 0;
  return result;
}

//----- (00477FA0) --------------------------------------------------------
int  Compat_FileFinderAdvance(int finder)
{
  int result; // eax
  int v2; // ecx

  result = findnext_(finder, finder + 4);
  *(_DWORD *)(uintptr_t)(v2 + 288) = result;
  return result;
}
// 477FB2: variable 'v2' is possibly undefined
// 489F5D: using guessed type int __fastcall findnext_(_DWORD, _DWORD);

//----- (00477FC0) --------------------------------------------------------
int  Compat_FileFinderGetName(int finder)
{
  return finder + 24;
}

//----- (00477FD0) --------------------------------------------------------
int  Compat_FileFinderGetAttributes(int finder)
{
  return *(_DWORD *)(uintptr_t)(finder + 4);
}

//----- (00477FE0) --------------------------------------------------------
int  Compat_FileFinderGetSize(int finder)
{
  return *(_DWORD *)(uintptr_t)(finder + 20);
}

//----- (00477FF0) --------------------------------------------------------
int  Compat_FileFinderCreate(int search_path, char a2, DWORD alloc_context)
{
  _DWORD *finder; // eax
  int v5; // ecx
  int v6; // ecx

  finder = (_DWORD *)(uintptr_t)Mem_Alloc(292, search_path, a2, alloc_context);
  if ( finder )
    finder = (_DWORD *)(uintptr_t)Compat_FileFinderOpen(finder, v5);
  if ( (*(int (__cdecl **)(int))(uintptr_t)(*finder + 12))(search_path) )
    return v6;
  (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v6 + 20))(v6, 2);
  return 0;
}
// 478010: variable 'v5' is possibly undefined
// 47800C: variable 'v6' is possibly undefined

//----- (00478030) --------------------------------------------------------
const char ** FileSystem_DiskMountCtor(const char **mount, int root_path)
{
  const char *path_text;
  unsigned int path_len;

  *(_DWORD *)(mount + 4) = 0;
  *(_DWORD *)(mount + 8) = (int)(intptr_t)&g_PathEntry_Vtable;
  *(_DWORD *)mount = (int)(intptr_t)g_FileSystemDiskMount_VTable;
  if ( !root_path )
    return mount;
  Compat_StringHolderDestructor(((_DWORD*)((const char **)(uintptr_t)((unsigned int)(uintptr_t)mount + 4))));
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)((unsigned int)(uintptr_t)mount + 4));
  path_len = path_text ? (unsigned int)strlen(path_text) : 0;
  if ( !path_len || path_text[path_len - 1] == 92 )
    return mount;
  Compat_StringHolderAppendText((const char **)(uintptr_t)((unsigned int)(uintptr_t)mount + 4), asc_5024EA);
  return mount;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510A14: using guessed type int (*off_510A14[4])();

//----- (004780A0) --------------------------------------------------------
int  FileSystem_DiskMountScalarDeletingDtor(_DWORD *mount, char flags)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(mount)), ((_DWORD)(uintptr_t)(&g_FileSystemDiskMount_DtorArrayDescriptor)));
    j_j__nfree_();
    return v5;
  }
  else
  {
    *mount = ((_DWORD)(uintptr_t)(g_FileSystemDiskMount_VTable));
    v3 = Compat_StringHolderScalarDeletingDtor((int)(intptr_t)(mount + 1), 0);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v6;
    }
    else
    {
      return v3 - 4;
    }
  }
}
// 4780D7: variable 'v5' is possibly undefined
// 4780E3: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510A14: using guessed type int (*off_510A14[4])();

//----- (004780F0) --------------------------------------------------------
int  FileSystem_DiskMountOpenFileQuery(int mount, char mode_flags, DWORD alloc_context)
{
  _DWORD *result; // ecx
  _DWORD joined_path[2]; // [esp+0h] [ebp-8h] BYREF

  joined_path[0] = 0;
  joined_path[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  result = (_DWORD *)(uintptr_t)Mem_Alloc(8, mount, mode_flags, alloc_context);
  if ( result )
  {
    Compat_StringHolderConstructJoined(joined_path, (_DWORD *)(uintptr_t)(unsigned int)(mount + 4), 0);
    result = Compat_FileStreamOpen(result, (const CHAR *)(uintptr_t)(unsigned int)joined_path[0], 0, mode_flags, alloc_context);
  }
  Compat_StringHolderDestroyStack(joined_path, 1);
  return (int)(intptr_t)result;
}

//----- (00478140) --------------------------------------------------------
int __fastcall FileSystem_DiskMountDeleteFile(int mount, const char *file_name)
{
  int v3; // ecx
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[4]; // [esp-Ch] [ebp-10h] BYREF

  joined_path[2] = mount;
  Compat_StringHolderConstructJoined(joined_path, ((_DWORD*)(intptr_t)(mount)), file_name);
  IO_RemoveFileByPath(v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_path, v4);
  return v5;
}
// 478158: variable 'v3' is possibly undefined
// 478161: variable 'v4' is possibly undefined
// 478166: variable 'v5' is possibly undefined
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (00478170) --------------------------------------------------------
int __fastcall FileSystem_DiskMountCreateDirectory(int mount, const char *dir_name)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[3]; // [esp-Ch] [ebp-Ch] BYREF

  joined_path[2] = mount;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(joined_path, ((_DWORD*)(intptr_t)(mount)), dir_name);
  CRT_MakeDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_path, v4);
  return v5;
}
// 478190: variable 'v4' is possibly undefined
// 478195: variable 'v5' is possibly undefined

//----- (004781A0) --------------------------------------------------------
int __fastcall FileSystem_DiskMountRemoveDirectory(int mount, const char *dir_name)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[4]; // [esp-Ch] [ebp-10h] BYREF

  joined_path[2] = mount;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(joined_path, ((_DWORD*)(intptr_t)(mount)), dir_name);
  CRT_RemoveDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_path, v4);
  return v5;
}
// 4781C1: variable 'v4' is possibly undefined
// 4781C6: variable 'v5' is possibly undefined

//----- (004781E0) --------------------------------------------------------
char *__thiscall FileSystem_DiskMountGetCurrentDirectory(void *this_)
{
  char *suffix_cursor; // esi
  char *buffer_end; // edi
  char first_char; // al
  char second_char; // al

  (void)this_;
  getcwd_(((_DWORD)(uintptr_t)(g_FileSystem_CurrentDirectoryBuffer)), 100);
  if ( g_FileSystem_CwdBufferSentinel[strlen(g_FileSystem_CurrentDirectoryBuffer)] == 92 )
    return g_FileSystem_CurrentDirectoryBuffer;
  suffix_cursor = asc_5024EC;
  buffer_end = &g_FileSystem_CurrentDirectoryBuffer[strlen(g_FileSystem_CurrentDirectoryBuffer)];
  do
  {
    first_char = *suffix_cursor;
    *buffer_end = *suffix_cursor;
    if ( !first_char )
      break;
    second_char = suffix_cursor[1];
    suffix_cursor += 2;
    buffer_end[1] = second_char;
    buffer_end += 2;
  }
  while ( second_char );
  return g_FileSystem_CurrentDirectoryBuffer;
}
// 489FF2: using guessed type int __fastcall getcwd_(_DWORD, _DWORD);

//----- (00478250) --------------------------------------------------------
int __thiscall FileSystem_DiskMountDirectoryExists(void *this_)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int find_data; // [esp-118h] [ebp-130h] BYREF
  const char *search_pattern; // [esp+0h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-14h]
  void *this_saved CLASH95_UNUSED; // [esp+10h] [ebp-8h]

  this_saved = this_;
  search_pattern = 0;
  vtable_ptr = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&search_pattern)));
  vtable_ptr = ((int (**)())(&g_PathEntry_Vtable));
  if ( search_pattern && *search_pattern && search_pattern[strlen(search_pattern) - 1] != 92 )
    Compat_StringHolderAppendText(&search_pattern, asc_5024EE);
  Compat_StringHolderAppendText(&search_pattern, a__36);
  if ( CRT_FindFirstFile(search_pattern, ((_DWORD*)(&find_data)), v1) == -1 )
  {
    Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&search_pattern, 1);
    return 0;
  }
  else
  {
    findclose_(v2);
    Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&search_pattern, 1);
    return v3;
  }
}
// 4782AC: variable 'v1' is possibly undefined
// 4782B6: variable 'v2' is possibly undefined
// 4782CE: variable 'v3' is possibly undefined
// 489F44: using guessed type int __thiscall findclose_(_DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478340) --------------------------------------------------------
char  FileSystem_DiskMountResolveRegisteredRootPath(int mount, int mount_table)
{
  const char *resolved_path; // eax

  resolved_path = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(mount + 4);
  if ( !resolved_path || !*resolved_path )
    Compat_StringHolderCopyText((_DWORD *)(uintptr_t)(mount + 4), (const char *)(uintptr_t)(unsigned int)Compat_FileSystemFindMountedPathById(mount_table, mount));
  return mount_table;
}

//----- (00478370) --------------------------------------------------------
const char ** FileSystem_DiskMountCreate(int root_path, char a2, DWORD alloc_context)
{
  const char **result; // eax

  result = (const char **)(uintptr_t)Mem_Alloc(12, root_path, a2, alloc_context);
  if ( result )
    return FileSystem_DiskMountCtor(result, root_path);
  return result;
}

//----- (004783B0) --------------------------------------------------------
int  FileSystem_DiskMountRegisterNestedMount(int mount, int *mount_table, char a3, DWORD alloc_context)
{
  _DWORD *stream_buf; // eax

  stream_buf = IO_StreambufAlloc(mount, a3, alloc_context);
  return FileSystem_AddMountEntry(
           mount_table,
           (const CHAR *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(mount + 4),
           0,
           (DWORD)(intptr_t)stream_buf);
}

//----- (004783D0) --------------------------------------------------------
int  FileSystem_DiskMountVariantScalarDeletingDtor(_DWORD *mount, char flags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(mount)), ((_DWORD)(uintptr_t)(&g_FileSystemDiskMountVariant_DtorArrayDescriptor)));
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = FileSystem_DiskMountScalarDeletingDtor(mount, 1);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 478400: variable 'v4' is possibly undefined
// 47840A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00478410) --------------------------------------------------------
int  FileSystem_ArchiveGenerateBlankRecord(int record)
{
  int v1; // edx

  FileSystem_ArchiveFillBlankRecordBytes(record);
  return v1;
}
// 478418: variable 'v1' is possibly undefined

//----- (00478420) --------------------------------------------------------
int  FileSystem_ArchiveFillBlankRecordBytes(int record)
{
  __int64 v2; // rax
  int record_end; // ecx

  HIDWORD(v2) = record;
  record_end = record + 26;
  do
  {
    v2 = rand_();
    *(_BYTE *)(uintptr_t)(HIDWORD(v2) - 1) = v2;
  }
  while ( HIDWORD(v2) != record_end );
  *(_DWORD *)(uintptr_t)(record + 14) = 0;
  return v2;
}
// 478431: variable 'v3' is possibly undefined
// 47619A: using guessed type __int64 __fastcall rand_(_DWORD, _DWORD);

//----- (00478450) --------------------------------------------------------
const char ** FileSystem_PathTrimToParentDir(const char **path_holder)
{
  const char *text; // eax
  int v3; // edx
  unsigned int text_len; // ecx

  *path_holder = 0;
  path_holder[1] = (const char *)&g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(((_DWORD*)(path_holder)));
  path_holder[1] = (const char *)&g_PathEntry_Vtable;
  if ( Compat_StringHolderFindLastBackslash((_BYTE **)path_holder) == -1 )
  {
    Compat_StringHolderDestructor(((_DWORD*)(path_holder)));
    return path_holder;
  }
  else
  {
    text = (const char *)(uintptr_t)ExcString_GetTextPtr((int)(intptr_t)path_holder);
    if ( text )
      text_len = strlen(text);
    else
      text_len = 0;
    Compat_StringHolderRemoveRange(((char**)(path_holder)), v3, text_len, text_len - v3);
    return path_holder;
  }
}
// 4784A9: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004784E0) --------------------------------------------------------
_DWORD * FileSystem_PathExtractFileName(_DWORD *path_holder)
{
  int slash_index; // eax
  unsigned int v3; // ecx

  *path_holder = 0;
  path_holder[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(path_holder);
  path_holder[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)path_holder);
  if ( slash_index != -1 )
    Compat_StringHolderRemoveRange(((char**)((const char **)path_holder)), 0, v3, slash_index + 1);
  return path_holder;
}
// 478524: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478540) --------------------------------------------------------
int * FileSystem_ArchiveRecordCacheCtor(int *cache, int stream, int base_offset, int record_count)
{
  int total_records; // edx
  int window_size; // eax
  int capacity; // ecx
  int *result; // eax

  cache[3] = 0;
  *cache = record_count;
  cache[5] = stream;
  total_records = *cache;
  cache[6] = base_offset;
  if ( total_records >= 200 )
    window_size = 200;
  else
    window_size = total_records;
  cache[2] = window_size;
  cache[4] = Compat_WcppCtorArrayStorage1m(
            (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * cache[2]),
            cache[2],
            &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  capacity = cache[2];
  cache[1] = capacity;
  result = cache;
  cache[1] = -capacity;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00478590) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheCopyCtor(int *cache, int *source_cache)
{
  int record_count; // eax
  int base_offset; // eax
  int total_records; // edx
  int window_size; // eax
  int records_buffer; // eax
  _DWORD *v9 CLASH95_UNUSED; // ecx
  int capacity; // ebx
  _DWORD *result; // eax

  record_count = *source_cache;
  cache[3] = 0;
  *cache = record_count;
  cache[5] = source_cache[5];
  base_offset = source_cache[6];
  total_records = *cache;
  cache[6] = base_offset;
  if ( total_records >= 200 )
    window_size = 200;
  else
    window_size = total_records;
  cache[2] = window_size;
  records_buffer = Compat_WcppCtorArrayStorage1m(
         (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * cache[2]),
         cache[2],
         &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  cache[4] = records_buffer;
  capacity = cache[2];
  cache[1] = capacity;
  result = (_DWORD *)cache;
  cache[1] = -capacity;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (004785F0) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheDestruct(_DWORD *cache)
{
  FileSystem_ArchiveRecordCacheFlushWindow(cache);
  ((void)(cache[4]), j_j__nfree_());
  return (int)(intptr_t)cache;
}

//----- (00478610) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheGetRecord(_DWORD *cache, int record_index)
{
  int window_start; // ebp

  ++g_FS_ArchiveRecordCacheAccessCount;
  window_start = cache[1];
  if ( record_index >= window_start && record_index < cache[2] + window_start )
    return cache[4] + 26 * (record_index - cache[1]);
  FileSystem_ArchiveRecordCacheLoadWindow(cache, record_index);
  ++g_FS_ArchiveRecordCacheMissCount;
  return cache[4] + 26 * (record_index - cache[1]);
}
// 54DD0C: using guessed type int dword_54DD0C;
// 54DD10: using guessed type int dword_54DD10;

//----- (00478670) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheLoadWindow(_DWORD *cache, int record_index)
{
  int window_start; // edx
  int *stream; // esi
  unsigned __int8 *records_buffer; // edi
  int result; // eax

  FileSystem_ArchiveRecordCacheFlushWindow(cache);
  window_start = record_index - cache[2] + 1;
  cache[1] = window_start;
  if ( window_start < 0 )
    cache[1] = 0;
  stream = (int *)(uintptr_t)cache[5];
  records_buffer = (unsigned __int8 *)(uintptr_t)cache[4];
  File_SeekIfPositionChangedMode1(stream, cache[6] + 26 * cache[1], (int)(intptr_t)records_buffer);
  result = Compat_StreamRead(stream[2], records_buffer, 26 * cache[2]);
  if ( stream[5] )
  {
    Compat_QueryXorDecodeBuffer((int)(intptr_t)stream, records_buffer, result);
  }
  stream[12] += result;
  return result;
}

//----- (004786E0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheFlushWindow(_DWORD *result)
{
  unsigned int window_bytes; // ebx
  int *stream; // esi
  const void *records_buffer; // edi

  if ( result[3] )
  {
    window_bytes = 26 * result[2];
    stream = (int *)(uintptr_t)result[5];
    records_buffer = (const void *)(uintptr_t)result[4];
    File_SeekIfPositionChangedMode2(stream, result[6] + 26 * result[1], (int)(intptr_t)records_buffer);
    Res_StreamWriteWithXorCipher(stream, records_buffer, window_bytes, window_bytes);
    result[3] = 0;
  }
  return result;
}
// 47870B: variable 'v4' is possibly undefined
// 478710: variable 'v5' is possibly undefined

//----- (00478720) --------------------------------------------------------
int  FileSystem_ArchiveEntryCopyConstruct(_DWORD *entry, int source_reader)
{
  _DWORD *v3; // ecx
  int v4; // ecx

  *entry = 0;
  entry[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(entry);
  v3[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  v3[2] = *(_DWORD *)(uintptr_t)(source_reader + 8);
  v3[3] = 0;
  FileSystem_ArchiveRecordCacheCopyCtor(((int*)(v3 + 4)), (int *)(uintptr_t)(source_reader + 16));
  FileSystem_ArchiveEntryReaderFlushHeader(source_reader);
  return v4;
}
// 47873A: variable 'v3' is possibly undefined
// 478765: variable 'v4' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478770) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderCtor(_DWORD *reader, int *stream, int base_offset, int data_size, const void *entry_name)
{
  int *cache_ptr; // eax
  int reader_base; // esi
  int bytes_read; // eax
  int result; // eax
  const char *name_text; // edx
  unsigned __int8 *header_buf; // [esp+0h] [ebp-10h]

  *reader = 0;
  reader[1] = ((_DWORD)(uintptr_t)(&g_CompatStringHolder_Vtable));
  Compat_StringHolderFreeText(reader);
  name_text = Compat_StringArgGetText(entry_name);
  if ( name_text && *name_text )
  {
    *reader = (int)(uintptr_t)j_Mem_Alloc((unsigned int)strlen(name_text) + 1);
    Compat_CopyPrefixN((char *)(uintptr_t)*reader, name_text, (unsigned int)strlen(name_text) + 1);
  }
  reader[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  reader[3] = 0;
  cache_ptr = FileSystem_ArchiveRecordCacheCtor(((int*)(reader + 4)), (int)(intptr_t)stream, base_offset + 4, (data_size - 4) / 0x1Au);
  reader_base = (int)(intptr_t)(cache_ptr - 4);
  header_buf = (unsigned __int8 *)(cache_ptr - 2);
  File_SeekIfPositionChangedMode1(stream, base_offset, 0);
  bytes_read = Compat_StreamRead((int)(intptr_t)stream, header_buf, 4);
  if ( stream[5] )
  {
    Compat_QueryXorDecodeBuffer((int)(intptr_t)stream, header_buf, bytes_read);
    result = reader_base;
    stream[12] += bytes_read;
  }
  else
  {
    stream[12] += bytes_read;
    result = reader_base;
  }
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478830) --------------------------------------------------------
int  FileSystem_ArchiveIndexCreateEmpty(_DWORD *index, int stream, int record_count)
{
  int *cache_ptr; // edi
  int end_offset; // eax

  *index = 0;
  index[1] = ((_DWORD)(uintptr_t)(&g_PathEntry_Vtable));
  index[2] = 0;
  index[3] = 0;
  cache_ptr = ((int*)(index + 4));
  end_offset = File_SeekStreamEndAndRecordPos(stream, (int)(intptr_t)(index + 4));
  FileSystem_ArchiveRecordCacheCtor(cache_ptr, stream, end_offset + 4, record_count);
  FileSystem_ArchiveWritePaddingRecords((int)(intptr_t)cache_ptr, record_count, (int)(intptr_t)cache_ptr);
  return (int)(intptr_t)cache_ptr;
}
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478880) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderScalarDeletingDtor(int reader)
{
  FileSystem_ArchiveEntryReaderFlushHeader(reader);
  return Compat_StringHolderScalarDeletingDtor(FileSystem_ArchiveRecordCacheDestruct((_DWORD *)(uintptr_t)(reader + 16)) - 16, 0);
}

//----- (004788A0) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderFlushHeader(int reader)
{
  int result; // eax
  int *stream; // esi
  const void *header_ptr; // edi

  FileSystem_ArchiveRecordCacheFlushWindow((_DWORD *)(uintptr_t)(reader + 16));
  result = *(_DWORD *)(uintptr_t)(reader + 12);
  if ( result )
  {
    stream = *(int **)(uintptr_t)(reader + 36);
    header_ptr = (const void *)(uintptr_t)(reader + 8);
    File_SeekIfPositionChangedMode2(stream, *(_DWORD *)(uintptr_t)(reader + 40) - 4, (int)(intptr_t)header_ptr);
    result = Res_StreamWriteWithXorCipher(stream, header_ptr, 4, 4u);
    *(_DWORD *)(uintptr_t)(reader + 12) = 0;
  }
  return result;
}

//----- (004788F0) --------------------------------------------------------
unsigned int  FileSystem_ArchiveNameHash(int archive, const char **name_holder)
{
  const char *text;
  unsigned int hash_value;
  unsigned int text_len;
  unsigned int index;

  text = Compat_StringArgGetText((const void *)name_holder);
  if ( !text || !*text )
    return 0;
  hash_value = (unsigned __int8)*text;
  text_len = (unsigned int)strlen(text);
  index = 1;
  while ( index < text_len )
  {
    hash_value *= (unsigned __int8)text[index];
    ++index;
  }
  return hash_value % *(_DWORD *)(uintptr_t)(archive + 16);
}

//----- (00478950) --------------------------------------------------------
int  FileSystem_ArchiveHashTableFind(int archive, const char **name_holder)
{
  const char *text;
  unsigned int slot_index; // ecx
  _DWORD *table; // edi
  int entry; // esi

  text = Compat_StringArgGetText((const void *)name_holder);
  if ( !text || !*text )
    return 0;
  slot_index = FileSystem_ArchiveNameHash(archive, name_holder);
  table = (_DWORD *)(uintptr_t)(archive + 16);
  while ( 1 )
  {
    entry = FileSystem_ArchiveRecordCacheGetRecord(table, slot_index);
    if ( !*(_DWORD *)(uintptr_t)(entry + 14) )
      return 0;
    if ( !strncmp_((_DWORD)(uintptr_t)text, (_DWORD)(uintptr_t)(const char *)(uintptr_t)entry, 13) )
      return entry;
    if ( slot_index )
      --slot_index;
    else
      slot_index = *table - 1;
  }
}
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004789C0) --------------------------------------------------------
unsigned int  FileSystem_ArchiveHashTableFindFreeSlot(int archive, const char **name_holder)
{
  unsigned int slot_index; // ecx
  _DWORD *table; // ebx

  slot_index = FileSystem_ArchiveNameHash(archive, name_holder);
  table = (_DWORD *)(uintptr_t)(archive + 16);
  while ( *(_DWORD *)(uintptr_t)(FileSystem_ArchiveRecordCacheGetRecord(table, slot_index) + 14) )
  {
    if ( slot_index )
      --slot_index;
    else
      slot_index = *table - 1;
  }
  return slot_index;
}

//----- (004789F0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveOpenEntryReader(int archive, const void *path_arg)
{
  const char *path_text;
  const char *leaf_text;
  int entry; // ecx
  _DWORD *result; // eax
  _DWORD leaf_holder[2]; // [esp+0h] [ebp-8h] BYREF
  _DWORD savedregs[4]; // [esp+8h] [ebp+0h] BYREF

  leaf_holder[0] = 0;
  leaf_holder[1] = (int)(intptr_t)&g_PathEntry_Vtable;
  path_text = Compat_StringArgGetText(path_arg);
  if ( path_text && *path_text )
  {
    leaf_text = Compat_StrrchrChar(path_text, '\\');
    if ( leaf_text )
      ++leaf_text;
    else
      leaf_text = path_text;
    Compat_StringHolderCopyText(leaf_holder, leaf_text);
  }
  entry = FileSystem_ArchiveHashTableFind(archive, (const char **)leaf_holder);
  Compat_StringHolderDestroyStack(leaf_holder, 1);
  if ( !entry || (*(_DWORD *)(uintptr_t)(entry + 14) & 2) == 0 )
    return 0;
  result = (_DWORD *)(uintptr_t)Mem_Alloc(44, entry, (char)(uintptr_t)path_arg, (DWORD)(intptr_t)savedregs);
  if ( result )
    return (_DWORD *)(uintptr_t)FileSystem_ArchiveEntryReaderCtor(
                       result,
                       (int *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(archive + 36),
                       *(_DWORD *)(uintptr_t)(entry + 18),
                       *(_DWORD *)(uintptr_t)(entry + 22),
                       path_arg);
  return result;
}

//----- (00478A60) --------------------------------------------------------
signed int  FileSystem_ArchiveHashTableInsert(_DWORD *archive, const char **name_holder, int data_size, int entry_flags)
{
  unsigned int slot_index; // ebp
  int entry; // eax
  int entry_count; // edx

  if ( archive[2] == archive[4] - 1 || !*name_holder || !**name_holder )
    return -1;
  slot_index = FileSystem_ArchiveHashTableFindFreeSlot((int)(intptr_t)archive, name_holder);
  entry = FileSystem_ArchiveRecordCacheGetRecord(archive + 4, slot_index);
  *(_BYTE *)(uintptr_t)(entry + 13) = 0;
  Compat_CopyPrefixN((char *)(uintptr_t)entry, *name_holder, 13);
  *(_DWORD *)(uintptr_t)(entry + 14) = entry_flags;
  *(_DWORD *)(uintptr_t)(entry + 18) = File_SeekStreamEndAndRecordPos(archive[9], (int)(intptr_t)name_holder);
  *(_DWORD *)(uintptr_t)(entry + 22) = data_size;
  archive[7] = 1;
  entry_count = archive[2];
  archive[3] = 1;
  archive[2] = entry_count + 1;
  return slot_index;
}

//----- (00478B10) --------------------------------------------------------
int  FileSystem_ArchiveWritePaddingRecords(int archive, int record_count, int a3)
{
  int result; // eax
  int v6; // ecx
  const void *v7; // edx
  int v8; // ecx
  _BYTE blank_record[28]; // [esp-1Ch] [ebp-30h] BYREF
  _DWORD header_words[5]; // [esp+0h] [ebp-14h] BYREF

  header_words[3] = a3;
  header_words[0] = 0;
  Res_StreamWriteWithXorCipher(*(int **)(uintptr_t)(archive + 36), header_words, a3, 4u);
  result = FileSystem_ArchiveGenerateBlankRecord((int)(intptr_t)blank_record);
  if ( record_count > 0 )
  {
    do
    {
      FileSystem_ArchiveFillBlankRecordBytes((int)(intptr_t)blank_record);
      result = Res_StreamWriteWithXorCipher(*(int **)(uintptr_t)(archive + 36), v7, v6 + 1, 0x1Au);
    }
    while ( v8 < record_count );
  }
  return result;
}
// 478B51: variable 'v7' is possibly undefined
// 478B50: variable 'v6' is possibly undefined
// 478B58: variable 'v8' is possibly undefined

//----- (00478B70) --------------------------------------------------------
signed int  FileSystem_ArchiveInsertFileEntry(_DWORD *archive, const char **name_holder, int record_count)
{
  signed int result; // eax
  int v5; // ecx

  result = FileSystem_ArchiveHashTableInsert(archive, name_holder, 26 * record_count, 2);
  if ( result != -1 )
  {
    FileSystem_ArchiveWritePaddingRecords((int)(intptr_t)archive, record_count, v5);
    return 0;
  }
  return result;
}
// 478B91: variable 'v5' is possibly undefined

//----- (00478BA0) --------------------------------------------------------
int  FileSystem_ArchiveInsertDirectoryEntry(_DWORD *archive, const char **name_holder)
{
  signed int slot_index; // eax

  slot_index = FileSystem_ArchiveHashTableInsert(archive, name_holder, 0, 1);
  if ( slot_index == -1 )
    return 0;
  else
    return FileSystem_ArchiveRecordCacheGetRecord(archive + 4, slot_index);
}

//----- (00478BD0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveEntryStreamCtor(_DWORD *result, int entry_record, int stream)
{
  int data_offset; // ecx
  int data_size; // edx

  data_offset = *(_DWORD *)(uintptr_t)(entry_record + 18);
  result[2] = 0;
  result[1] = data_offset;
  data_size = *(_DWORD *)(uintptr_t)(entry_record + 22);
  *result = ((_DWORD)(uintptr_t)(g_FileSystemArchiveEntryStream_VTable));
  result[3] = data_size;
  result[4] = stream;
  return result;
}
// 510BD4: using guessed type int (*off_510BD4[10])();

//----- (00478BF0) --------------------------------------------------------
signed int  FileSystem_ArchiveStreamHasRemainingData(int stream)
{
  if ( *(_DWORD *)(uintptr_t)(stream + 8) == *(_DWORD *)(uintptr_t)(stream + 12) )
    return -1;
  else
    return 1;
}

//----- (00478C20) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadBytes(_DWORD *stream, unsigned __int8 *buffer, int a3)
{
  int *source_stream; // edi
  int bytes_read; // ebx
  int remaining_bytes;
  int result; // eax

  if ( stream[3] == stream[2] )
    return 0;
  remaining_bytes = stream[3] - stream[2];
  if ( a3 > remaining_bytes )
    a3 = remaining_bytes;
  source_stream = (int *)(uintptr_t)stream[4];
  File_SeekIfPositionChangedMode1(source_stream, stream[2] + stream[1], (int)(intptr_t)source_stream);
  bytes_read = Compat_StreamRead(source_stream[2], buffer, a3);
  if ( source_stream[5] )
    Compat_QueryXorDecodeBuffer((int)(intptr_t)source_stream, buffer, bytes_read);
  source_stream[12] += bytes_read;
  result = bytes_read;
  stream[2] += bytes_read;
  return result;
}

//----- (00478CA0) --------------------------------------------------------
int FileSystem_ArchiveStreamNoOpFlush(void)
{
  return 0;
}

//----- (00478CB0) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadByte(int stream, int a2)
{
  int result; // eax
  int *source_stream; // ecx
  int xor_key; // edi
  unsigned __int8 next_byte;

  if ( *(_DWORD *)(uintptr_t)(stream + 12) == *(_DWORD *)(uintptr_t)(stream + 8) )
    return -1;
  source_stream = *(int **)(uintptr_t)(stream + 16);
  File_SeekIfPositionChangedMode1(source_stream, *(_DWORD *)(uintptr_t)(stream + 8) + *(_DWORD *)(uintptr_t)(stream + 4), a2);
  ++*(_DWORD *)(uintptr_t)(stream + 8);
  if ( Compat_StreamRead(source_stream[2], &next_byte, 1) == 1 )
    result = next_byte;
  else
    result = -1;
  xor_key = source_stream[5];
  if ( xor_key )
    result ^= xor_key + source_stream[12];
  ++source_stream[12];
  return result;
}

//----- (00478D10) --------------------------------------------------------
signed int  Res_StreamPutBackDecodedByte(int entry_stream, int putback_byte)
{
  int source_stream; // eax
  signed int encoded_byte; // eax
  signed int result; // eax
  int v6; // ecx

  source_stream = *(_DWORD *)(uintptr_t)(entry_stream + 16);
  if ( putback_byte != -1 )
    --*(_DWORD *)(uintptr_t)(source_stream + 48);
  if ( *(_DWORD *)(uintptr_t)(source_stream + 20) )
    encoded_byte = putback_byte ^ (*(_DWORD *)(uintptr_t)(source_stream + 48) + *(_DWORD *)(uintptr_t)(source_stream + 20));
  else
    encoded_byte = putback_byte;
  result = CRT_FlushBufferAndPutChar(encoded_byte, putback_byte);
  if ( v6 != -1 )
    --*(_DWORD *)(uintptr_t)(entry_stream + 8);
  return result;
}
// 478D3E: variable 'v6' is possibly undefined

//----- (00478D70) --------------------------------------------------------
int  Res_StreamWriteBytes(int stream, const void *buffer, unsigned int a3)
{
  int result; // eax
  int v4; // ecx
  int new_length; // ebx

  result = Res_StreamWriteWithXorCipher(*(int **)(uintptr_t)(stream + 16), buffer, stream, a3);
  new_length = result + *(_DWORD *)(uintptr_t)(v4 + 12);
  *(_DWORD *)(uintptr_t)(v4 + 8) += result;
  *(_DWORD *)(uintptr_t)(v4 + 12) = new_length;
  return result;
}
// 478D7E: variable 'v4' is possibly undefined

//----- (00478D90) --------------------------------------------------------
int  Res_StreamSeekClamped(int result, int position)
{
  int stream_length; // ecx

  if ( position < 0 )
  {
    *(_DWORD *)(uintptr_t)(result + 8) = 0;
  }
  else
  {
    stream_length = *(_DWORD *)(uintptr_t)(result + 12);
    if ( position <= stream_length )
      *(_DWORD *)(uintptr_t)(result + 8) = position;
    else
      *(_DWORD *)(uintptr_t)(result + 8) = stream_length;
  }
  return result;
}

//----- (00478DB0) --------------------------------------------------------
int  File_DirNodeScalarDtor(_DWORD *node, char flags, DWORD a3)
{
  int v4; // ecx
  int v6; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(node)), ((_DWORD)(uintptr_t)(&g_FileDirNode_DtorArrayDescriptor)));
    j_j__nfree_();
    return v6;
  }
  else
  {
    *node = ((_DWORD)(uintptr_t)(g_FileDirNode_VTable));
    File_ApplyResolvedEntryFlag(node[4], node[3], a3);
    if ( (flags & 2) != 0 )
      j__nfree_();
    return v4;
  }
}
// 478DD1: variable 'v4' is possibly undefined
// 478DE5: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510BA4: using guessed type int (*off_510BA4[4])();

//----- (00478E00) --------------------------------------------------------
_DWORD * Res_BuildTaggedRecordHeader(_DWORD *result, int version, int data_offset, int record_count)
{
  result[1] = version;
  result[3] = data_offset;
  result[2] = record_count;
  qmemcpy(result, aLlrs, sizeof(_DWORD));
  return result;
}

//----- (00478E30) --------------------------------------------------------
int  File_SourceEntryConstructor(_DWORD *node, int a2, int a3, DWORD allocContext)
{
  int v4; // ecx
  int resolved_entry; // eax
  int v6; // ecx
  int v7; // ecx
  _DWORD *archive_entry; // eax
  _DWORD *v10; // ecx
  int v11; // ecx
  int path_holder; // [esp+0h] [ebp-14h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-10h]
  int v14 CLASH95_UNUSED; // [esp+10h] [ebp-4h]

  v14 = a3;
  node[2] = 0;
  node[3] = 0;
  node[4] = -1;
  *node = ((_DWORD)(uintptr_t)(g_FileCacheNode_VTable));
  node[1] = a2;
  path_holder = 0;
  vtable_ptr = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&path_holder)));
  vtable_ptr = ((int (**)())(&g_PathEntry_Vtable));
  resolved_entry = File_ResolveCachedPathEntry(*(_DWORD **)(uintptr_t)(v4 + 4), ((_DWORD*)(&path_holder)), (const char *)(uintptr_t)v4, allocContext);
  *(_DWORD *)(uintptr_t)(v6 + 8) = resolved_entry;
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&path_holder, 1);
  if ( !*(_DWORD *)(uintptr_t)(v7 + 8) )
    return v7;
  archive_entry = (_DWORD *)(uintptr_t)Mem_Alloc(44, v7, 0, allocContext);
  if ( archive_entry )
    archive_entry = (_DWORD *)(uintptr_t)FileSystem_ArchiveEntryCopyConstruct(archive_entry, v10[2]);
  v10[2] = ((_DWORD)(uintptr_t)(archive_entry));
  File_CacheNodeRebalance(v10);
  return v11;
}
// 478E7A: variable 'v4' is possibly undefined
// 478E87: variable 'v6' is possibly undefined
// 478E91: variable 'v7' is possibly undefined
// 478EAE: variable 'v10' is possibly undefined
// 478EC0: variable 'v11' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00478ED0) --------------------------------------------------------
_DWORD * File_CacheNodeScalarDtor(_DWORD *node, char flags)
{
  int entry_reader; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(node)), ((_DWORD)(uintptr_t)(&g_FileCacheNode_DtorArrayDescriptor)));
    j_j__nfree_();
    return (_DWORD *)(uintptr_t)v6;
  }
  *node = ((_DWORD)(uintptr_t)(g_FileCacheNode_VTable));
  entry_reader = node[2];
  if ( entry_reader )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(entry_reader);
    j__nfree_();
    if ( (flags & 2) == 0 )
      return (_DWORD *)(uintptr_t)v7;
  }
  else if ( (flags & 2) == 0 )
  {
    return node;
  }
  j__nfree_();
  return (_DWORD *)(uintptr_t)v8;
}
// 478F01: variable 'v6' is possibly undefined
// 478F17: variable 'v7' is possibly undefined
// 478F23: variable 'v8' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00478F30) --------------------------------------------------------
int  File_CacheNodeCheckChildHeight(int result)
{
  int child_node; // edx

  child_node = *(_DWORD *)(uintptr_t)(result + 8);
  if ( !child_node || *(_DWORD *)(uintptr_t)(child_node + 16) <= *(_DWORD *)(uintptr_t)(result + 16) )
    return 0;
  return result;
}

//----- (00478F50) --------------------------------------------------------
_DWORD * File_CacheNodeRebalance(_DWORD *cache_node)
{
  _DWORD *v1; // ecx
  int entry_reader; // eax
  int total_records; // edx
  _DWORD *result; // eax
  int record; // eax

  v1 = cache_node;
  ++cache_node[4];
  while ( 1 )
  {
    entry_reader = v1[2];
    total_records = *(_DWORD *)(uintptr_t)(entry_reader + 16);
    result = (_DWORD *)(uintptr_t)(entry_reader + 16);
    if ( total_records <= v1[4] )
      break;
    record = FileSystem_ArchiveRecordCacheGetRecord(result, v1[4]);
    v1[3] = record;
    result = *(_DWORD **)(uintptr_t)(record + 14);
    if ( result )
      break;
    ++v1[4];
  }
  return result;
}
// 478F58: variable 'v1' is possibly undefined

//----- (00478F90) --------------------------------------------------------
int  File_CacheNodeGetTag(int node)
{
  return *(_DWORD *)(uintptr_t)(node + 12);
}

//----- (00478FA0) --------------------------------------------------------
signed int  File_CacheNodeGetEntrySize(int node)
{
  if ( (*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 12) + 14) & 2) != 0 )
    return 16;
  else
    return FileSystem_ArchiveStreamNoOpFlush();
}

//----- (00478FC0) --------------------------------------------------------
int  File_CacheNodeGetChildTag(int node)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 12) + 22);
}

//----- (00478FD0) --------------------------------------------------------
int * File_SourceConstructFromStream(
        int *source,
        const CHAR *path,
        unsigned __int8 *mode,
        int a4,
        int a5,
        int a6)
{
  source[3] = 0;
  source[4] = (int)(intptr_t)&g_PathEntry_Vtable;
  source[8] = 0;
  source[5] = a4;
  source[9] = 0;
  source[7] = a6;
  *source = (int)(intptr_t)g_FileSource_VTable;
  File_SourceReadAndDecodeHeader(source, path, (int)(intptr_t)mode, mode, a5);
  return source;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479020) --------------------------------------------------------
int * File_SourceBuildAndWriteHeader(
        int *source,
        const CHAR *path,
        int useCipher,
        int a4,
        DWORD heap_ctx,
        int a6)
{
  const CHAR *writePath; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD *archiveIndex; // eax
  _DWORD header[6]; // [esp+0h] [ebp-18h] BYREF

  source[2] = 0;
  source[3] = 0;
  source[4] = (int)(intptr_t)&g_PathEntry_Vtable;
  source[8] = 0;
  source[9] = 0;
  source[6] = a4;
  source[7] = a6;
  source[5] = useCipher;
  *source = (int)(intptr_t)g_FileSource_VTable;
  CRT_DeleteFile(path, (int)(intptr_t)path);
  source[2] = Res_OpenBufferedStreamForWrite(writePath, 0, (unsigned __int8 *)aWB, heap_ctx);
  Res_BuildTaggedRecordHeader(header, 1, v8, a4);
  source[13] = 0;
  File_SeekIfPositionChangedMode2(source, 0, a4);
  Res_StreamWriteWithXorCipher(source, header, v9, 0x10u);
  archiveIndex = (_DWORD *)(uintptr_t)Mem_Alloc(44, v10, 16, heap_ctx);
  if ( archiveIndex )
    source[1] = FileSystem_ArchiveIndexCreateEmpty(archiveIndex, (int)(intptr_t)source, a4);
  else
    source[1] = 0;
  return source;
}
// 479074: variable 'v7' is possibly undefined
// 479085: variable 'v8' is possibly undefined
// 4790A3: variable 'v9' is possibly undefined
// 4790AD: variable 'v10' is possibly undefined
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();
