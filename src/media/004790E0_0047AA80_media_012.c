/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004790E0) --------------------------------------------------------
int  File_SourceScalarDtor(_DWORD *a1, char flags)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v7; // ecx
  int v8; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileSource_DtorArrayDescriptor);
    j_j__nfree_();
    return v7;
  }
  else
  {
    *a1 = g_FileSource_VTable;
    File_CacheClearEntryTree((int)a1);
    v4 = *(_DWORD *)(v3 + 4);
    if ( v4 )
    {
      FileSystem_ArchiveEntryReaderScalarDeletingDtor(v4);
      j__nfree_();
    }
    v5 = Compat_StringHolderScalarDeletingDtor(v3 + 12, 0);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v8;
    }
    else
    {
      return v5 - 12;
    }
  }
}
// 4790F6: variable 'v3' is possibly undefined
// 47912F: variable 'v7' is possibly undefined
// 47913B: variable 'v8' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479140) --------------------------------------------------------
int  Res_OpenBufferedStreamForRead(const CHAR *path, int a2, unsigned __int8 *mode, DWORD heap_ctx)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(path, mode, a2, heap_ctx);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (00479170) --------------------------------------------------------
int  Res_OpenBufferedStreamForWrite(const CHAR *path, int a2, unsigned __int8 *mode, DWORD heap_ctx)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(path, mode, a2, heap_ctx);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (004791A0) --------------------------------------------------------
int  File_SourceReadAndDecodeHeader(
        int *source,
        const CHAR *path,
        int a3,
        unsigned __int8 *mode,
        int a5)
{
  int stream_ptr; // eax
  unsigned __int8 *headerBytePtr; // esi
  int i; // ecx
  int raw_byte; // ebx
  unsigned __int8 decoded_byte; // al
  int v13; // ecx
  int readerResult; // eax
  _DWORD *reader; // esi
  _DWORD header[4]; // [esp+0h] [ebp-28h] BYREF
  _DWORD source_name_holder[2]; // [esp+10h] [ebp-18h] BYREF
  int bytes_read; // [esp+18h] [ebp-10h]
  int *v25; // [esp+1Ch] [ebp-Ch]
  int *sourceObj; // [esp+20h] [ebp-8h]
  int *decodeSource; // [esp+24h] [ebp-4h]
  _DWORD savedregs[4]; // [esp+28h] [ebp+0h] BYREF

  sourceObj = source;
  stream_ptr = Res_OpenBufferedStreamForRead(path, a3, mode, (DWORD)savedregs);
  sourceObj[13] = 0;
  v25 = sourceObj;
  sourceObj[2] = stream_ptr;
  bytes_read = Compat_StreamRead(stream_ptr, header, 16);
  if ( sourceObj[5] )
  {
    headerBytePtr = (unsigned __int8 *)header;
    decodeSource = sourceObj;
    a5 = bytes_read;
    for ( i = sourceObj[12]; a5; *(headerBytePtr - 1) = decoded_byte )
    {
      --a5;
      raw_byte = *headerBytePtr++;
      decoded_byte = Res_XorDecodeByte((int)decodeSource, i, raw_byte);
      i = v13 + 1;
    }
  }
  v25[12] += bytes_read;
  Compat_StreamSeek(sourceObj[2], header[3], 1);
  sourceObj[12] = Compat_StreamTell(sourceObj[2]);
  readerResult = Mem_Alloc(44, 0, 1, (DWORD)savedregs);
  reader = (_DWORD *)readerResult;
  source_name_holder[0] = 0;
  source_name_holder[1] = (int)&g_PathEntry_Vtable;
  if ( readerResult )
  {
    readerResult = FileSystem_ArchiveEntryReaderCtor(reader, sourceObj, sourceObj[12], 26 * header[2] + 4, (const void *)source_name_holder);
  }
  else
  {
    readerResult = 0;
  }
  sourceObj[1] = readerResult;
  return readerResult;
}
// 479202: variable 'v13' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004792B0) --------------------------------------------------------
_DWORD * File_CacheNodeNewValidated(int a1, char a2, int a3, DWORD a4)
{
  _DWORD *v4; // eax
  int v5; // ecx
  _DWORD *v6; // ebx

  v4 = (_DWORD *)Mem_Alloc(20, a1, a2, a4);
  if ( v4 )
    v4 = (_DWORD *)File_SourceEntryConstructor(v4, v5, v5, a4);
  v6 = v4;
  if ( (*(int (__cdecl **)(int))(*v4 + 12))(a3) )
    return v6;
  (*(void (**)(void))(*v6 + 20))();
  return 0;
}
// 4792D8: variable 'v5' is possibly undefined

//----- (004792F0) --------------------------------------------------------
int  File_CacheTreeAdvanceSuccessor(_DWORD *a1)
{
  if ( a1[11] )
  {
    *(_DWORD *)(a1[11] + 4) = *(_DWORD *)(a1[10] + 4);
    *(_DWORD *)(a1[10] + 4) = a1[9];
    a1[9] = a1[10];
  }
  return *(_DWORD *)a1[9];
}

//----- (00479330) --------------------------------------------------------
int * File_CacheNodeFreeTree(int *node)
{
  int *v1; // ecx

  v1 = node;
  if ( *node )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(*node);
    j__nfree_();
  }
  if ( v1[1] )
  {
    File_CacheNodeFreeTree((int *)v1[1]);
    j__nfree_();
  }
  return v1;
}
// 479353: conditional instruction was optimized away because ebx.4!=0
// 47934A: variable 'v1' is possibly undefined

//----- (00479370) --------------------------------------------------------
int * File_CacheTreeUnlinkLeftmost(int *result)
{
  int *v1; // ecx
  int i; // eax
  int v3; // eax
  int v4; // esi

  v1 = result;
  if ( result[9] )
  {
    result[11] = 0;
    for ( i = result[9]; ; i = *(_DWORD *)(v3 + 4) )
    {
      v1[10] = i;
      v3 = v1[10];
      if ( !*(_DWORD *)(v3 + 4) )
        break;
      v1[11] = v3;
    }
    v4 = v1[11];
    if ( v4 )
      *(_DWORD *)(v4 + 4) = 0;
    else
      v1[9] = 0;
    result = (int *)v1[10];
    if ( result )
    {
      File_CacheNodeFreeTree(result);
      result = (int *)j__nfree_();
    }
    --v1[8];
  }
  return result;
}
// 4793B1: variable 'v1' is possibly undefined

//----- (004793D0) --------------------------------------------------------
int  File_CacheInsertWithEviction(int *cache, int entry, char a3, DWORD heap_ctx)
{
  _DWORD *cache_node; // eax

  (void)a3;
  (void)heap_ctx;
  if ( !entry )
    return 0;
  while ( cache[8] >= cache[7] && cache[9] )
    File_CacheTreeUnlinkLeftmost(cache);
  cache_node = (_DWORD *)Mem_Alloc(8, (int)cache, 0, heap_ctx);
  if ( cache_node )
  {
    cache_node[0] = entry;
    cache_node[1] = cache[9];
  }
  cache[9] = (int)cache_node;
  ++cache[8];
  if ( !cache_node )
    return 0;
  return cache_node[0];
}

//----- (00479420) --------------------------------------------------------
int  File_ResolveCachedPathEntry(_DWORD *fs, _DWORD *path_holder, const char *a3, DWORD heap_ctx)
{
  const char *path_text;
  _DWORD *cache_node;
  int entry;
  const char *entry_name;
  const char *last_slash;
  size_t path_len;
  size_t parent_len;
  _DWORD parent_holder[2];
  int parent_entry;
  _DWORD *resolved_entry;

  (void)a3;
  path_text = Compat_StringHolderGetText(path_holder);
  if ( !path_text || !*path_text )
    return fs[1];
  fs[11] = 0;
  fs[10] = fs[9];
  cache_node = (_DWORD *)(uintptr_t)(unsigned int)fs[10];
  while ( cache_node )
  {
    entry = cache_node[0];
    entry_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)entry;
    if ( entry_name && !strcmp_(path_text, entry_name) )
      return File_CacheTreeAdvanceSuccessor(fs);
    fs[11] = (int)cache_node;
    fs[10] = cache_node[1];
    cache_node = (_DWORD *)(uintptr_t)(unsigned int)fs[10];
  }
  ++g_FS_PathEntryCacheMissCount;
  parent_holder[0] = 0;
  parent_holder[1] = (int)&g_PathEntry_Vtable;
  last_slash = Compat_StrrchrChar(path_text, '\\');
  if ( last_slash )
  {
    Compat_StringHolderCopyText(parent_holder, path_text);
    path_len = strlen(path_text);
    parent_len = (size_t)(last_slash - path_text);
    Compat_StringHolderRemoveRange((char **)parent_holder, (int)parent_len, (unsigned int)path_len, (int)(path_len - parent_len));
  }
  parent_entry = File_ResolveCachedPathEntry(fs, parent_holder, 0, heap_ctx);
  Compat_StringHolderDestroyStack(parent_holder, 1);
  if ( !parent_entry )
    return 0;
  resolved_entry = FileSystem_ArchiveOpenEntryReader(parent_entry, path_holder);
  if ( !resolved_entry )
    return 0;
  return File_CacheInsertWithEviction((int *)fs, (int)resolved_entry, 0, heap_ctx);
}
// 54DD18: using guessed type int dword_54DD18;

//----- (004794F0) --------------------------------------------------------
int  File_ResolvePathByParentAndLeaf(_DWORD *fs, const char *path, DWORD heap_ctx)
{
  _DWORD parent_path_holder[2]; // [esp+0h] [ebp-118h] BYREF
  _DWORD leaf_name_holder[2]; // [esp+8h] [ebp-110h] BYREF
  int parent_entry; // ebx
  int result; // ecx

  ++g_FS_ResolvePathByParentLeafCount;
  if ( !path || !*path )
    return 0;
  Compat_StringHolderBuildParentPath(parent_path_holder, path);
  parent_entry = File_ResolveCachedPathEntry(fs, parent_path_holder, 0, heap_ctx);
  Compat_StringHolderDestroyStack(parent_path_holder, 1);
  Compat_StringHolderBuildLeafName(leaf_name_holder, path);
  if ( parent_entry )
    result = FileSystem_ArchiveHashTableFind(parent_entry, (const char **)leaf_name_holder);
  else
    result = 0;
  Compat_StringHolderDestroyStack(leaf_name_holder, 1);
  return result;
}
// 54DD14: using guessed type int dword_54DD14;

//----- (00479560) --------------------------------------------------------
int  File_ResolveAbsolutePathEntry(const char *path, DWORD heap_ctx)
{
  const char **parent_dir_holder; // eax
  char *v4; // ecx
  int parent_entry; // ecx
  int result; // eax
  const char **leaf_name_holder; // eax
  int v8; // ecx
  int found_entry; // ebx
  int v10; // ecx
  _DWORD leaf_name[2]; // [esp-8h] [ebp-18h] BYREF
  const char *parent_dir_path[4]; // [esp+0h] [ebp-10h] BYREF

  parent_dir_path[2] = path;
  parent_dir_holder = FileSystem_PathTrimToParentDir(parent_dir_path);
  File_ResolveCachedPathEntry(v4, parent_dir_holder, v4, heap_ctx);
  Compat_StringHolderScalarDeletingDtor((int)parent_dir_path, 1);
  if ( !parent_entry )
    return 0;
  leaf_name_holder = (const char **)FileSystem_PathExtractFileName(leaf_name);
  found_entry = FileSystem_ArchiveHashTableFind(v8, leaf_name_holder);
  Compat_StringHolderScalarDeletingDtor((int)leaf_name, 1);
  *(_DWORD *)(v10 + 28) = 1;
  result = found_entry;
  *(_DWORD *)(v10 + 12) = 1;
  return result;
}
// 479576: variable 'v4' is possibly undefined
// 47958D: variable 'v5' is possibly undefined
// 4795A4: variable 'v8' is possibly undefined
// 4795BA: variable 'v10' is possibly undefined

//----- (004795D0) --------------------------------------------------------
char  File_ApplyResolvedEntryFlag(int a1, int flag_value, DWORD heap_ctx)
{
  _DWORD *v4; // ecx

  *(_DWORD *)(File_ResolveAbsolutePathEntry((const char *)(a1 + 12), heap_ctx) + 22) = flag_value;
  return Compat_StringHolderDestructor(v4);
}
// 4795E8: variable 'v4' is possibly undefined

//----- (004795F0) --------------------------------------------------------
_DWORD * File_OpenNodeByFlags(char flags)
{
  char *v1; // ecx
  int resolvedEntry; // edi
  int self; // ecx
  _DWORD *result; // eax
  int v5; // ecx
  int excStringField; // ebx
  const char **parentDir; // eax
  char *v8; // ecx
  _DWORD *parentEntry; // ebx
  int v10; // ecx
  int dirEntry; // edi
  _DWORD *v12; // ebx
  int v13; // ecx
  _DWORD *dirStream; // eax
  int v15; // ecx
  _DWORD *resultNode; // ebx
  int resolveHolder; // [esp+0h] [ebp-40h] BYREF
  int (**v18)(); // [esp+4h] [ebp-3Ch]
  int fileNameHolder; // [esp+8h] [ebp-38h] BYREF
  int (**v20)(); // [esp+Ch] [ebp-34h]
  int parentDirHolder; // [esp+10h] [ebp-30h] BYREF
  int (**v22)(); // [esp+14h] [ebp-2Ch]
  int dirInsertHolder; // [esp+18h] [ebp-28h] BYREF
  int (**v24)(); // [esp+1Ch] [ebp-24h]
  const char *parentDirPath[2]; // [esp+20h] [ebp-20h] BYREF
  const char *fileName[6]; // [esp+28h] [ebp-18h] BYREF

  resolveHolder = 0;
  v18 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&resolveHolder);
  v18 = &g_PathEntry_Vtable;
  resolvedEntry = File_ResolvePathByParentAndLeaf(v1, v1, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)&resolveHolder, 1);
  if ( resolvedEntry )
  {
    if ( (flags & 8) == 0 )
    {
      result = (_DWORD *)Mem_Alloc(20, self, flags, (DWORD)&g_PathEntry_Vtable);
      if ( result )
      {
        result = FileSystem_ArchiveEntryStreamCtor(result, resolvedEntry, v5);
        *result = g_FileArchiveEntryStream_VTable;
      }
      return result;
    }
    return 0;
  }
  if ( (flags & 8) == 0 )
    return 0;
  excStringField = self + 12;
  if ( ExcString_GetTextPtr(self + 12) && *(_BYTE *)ExcString_GetTextPtr(excStringField) )
    return 0;
  parentDirHolder = 0;
  v22 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&parentDirHolder);
  v22 = &g_PathEntry_Vtable;
  parentDir = FileSystem_PathTrimToParentDir(parentDirPath);
  parentEntry = (_DWORD *)File_ResolveCachedPathEntry(v8, parentDir, v8, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)parentDirPath, 1);
  Compat_StringHolderScalarDeletingDtor((int)&parentDirHolder, 1);
  fileNameHolder = 0;
  v20 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&fileNameHolder);
  v20 = &g_PathEntry_Vtable;
  FileSystem_PathExtractFileName(fileName);
  Compat_StringHolderScalarDeletingDtor((int)&fileNameHolder, 1);
  if ( parentEntry && (dirEntry = FileSystem_ArchiveInsertDirectoryEntry(parentEntry, fileName)) != 0 )
  {
    v24 = &g_CompatStringHolder_Vtable;
    dirInsertHolder = 0;
    v12 = (_DWORD *)(v10 + 12);
    Compat_StringHolderDestructor(&dirInsertHolder);
    v24 = &g_PathEntry_Vtable;
    ExcString_GetTextPtr((int)&dirInsertHolder);
    ExcString_ReleaseText(v12);
    Compat_StringHolderScalarDeletingDtor((int)&dirInsertHolder, 1);
    dirStream = (_DWORD *)Mem_Alloc(20, v13, (char)v12, (DWORD)&g_CompatStringHolder_Vtable);
    if ( dirStream )
    {
      dirStream = FileSystem_ArchiveEntryStreamCtor(dirStream, dirEntry, v15);
      *dirStream = g_FileDirNode_VTable;
    }
    resultNode = dirStream;
    Compat_StringHolderScalarDeletingDtor((int)fileName, 1);
    return resultNode;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)fileName, 1);
    return 0;
  }
}
// 47961F: variable 'v1' is possibly undefined
// 479640: variable 'v3' is possibly undefined
// 47964D: variable 'v5' is possibly undefined
// 4796BB: variable 'v8' is possibly undefined
// 479749: variable 'v10' is possibly undefined
// 47977F: variable 'v13' is possibly undefined
// 47978C: variable 'v15' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 510B74: using guessed type int (*off_510B74[10])();
// 510BA4: using guessed type int (*off_510BA4[4])();

//----- (004797F0) --------------------------------------------------------
signed int  File_OpenEntryForWrite(int a1, int access_mode)
{
  int v2; // edx
  int v3; // ecx
  const char **parentDirPath; // eax
  char *v5; // ecx
  _DWORD *parentEntry; // ecx
  signed int insertResult; // eax
  signed int result; // ebx
  const char *fileName[2]; // [esp+0h] [ebp-2Ch] BYREF
  int v11; // [esp+8h] [ebp-24h] BYREF
  int (**v12)(); // [esp+Ch] [ebp-20h]
  int v13; // [esp+10h] [ebp-1Ch] BYREF
  int (**v14)(); // [esp+14h] [ebp-18h]
  const char *parentPath[5]; // [esp+18h] [ebp-14h] BYREF

  if ( ExcString_GetTextPtr(a1 + 12) && *(_BYTE *)ExcString_GetTextPtr(v2) )
    return -1;
  if ( !access_mode )
    access_mode = *(_DWORD *)(v3 + 24);
  v13 = 0;
  v14 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v13);
  v14 = &g_PathEntry_Vtable;
  parentDirPath = FileSystem_PathTrimToParentDir(parentPath);
  File_ResolveCachedPathEntry(v5, parentDirPath, v5, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)parentPath, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v13, 1);
  v11 = 0;
  v12 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v11);
  v12 = &g_PathEntry_Vtable;
  FileSystem_PathExtractFileName(fileName);
  Compat_StringHolderScalarDeletingDtor((int)&v11, 1);
  if ( parentEntry )
    insertResult = FileSystem_ArchiveInsertFileEntry(parentEntry, fileName, access_mode);
  else
    insertResult = -1;
  result = insertResult;
  Compat_StringHolderScalarDeletingDtor((int)fileName, 1);
  return result;
}
// 479810: variable 'v3' is possibly undefined
// 479848: variable 'v5' is possibly undefined
// 4798A1: variable 'v6' is possibly undefined
// 4798CA: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004798F0) --------------------------------------------------------
int * File_CacheClearEntryTree(int a1)
{
  int v1; // ecx
  int *result; // eax

  fflush_(a1);
  result = *(int **)(v1 + 36);
  if ( result )
  {
    File_CacheNodeFreeTree(result);
    result = (int *)j__nfree_();
  }
  *(_DWORD *)(v1 + 36) = 0;
  *(_DWORD *)(v1 + 32) = 0;
  return result;
}
// 4798FB: variable 'v1' is possibly undefined
// 48A216: using guessed type int __thiscall fflush_(_DWORD);

//----- (00479930) --------------------------------------------------------
int  File_PrimePathCacheEntry(int a1, DWORD a2)
{
  char *v2; // ecx
  int v3; // ecx
  int v5; // [esp+0h] [ebp-18h] BYREF
  int (**v6)(); // [esp+4h] [ebp-14h]
  int v7; // [esp+10h] [ebp-8h]

  v7 = a1;
  v5 = 0;
  v6 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v5);
  v6 = &g_PathEntry_Vtable;
  File_ResolveCachedPathEntry(v2, &v5, v2, a2);
  Compat_StringHolderScalarDeletingDtor((int)&v5, 1);
  return v3;
}
// 47995B: variable 'v2' is possibly undefined
// 479975: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00479980) --------------------------------------------------------
int  File_SeekStreamEndAndRecordPos(int source, int heap_ctx)
{
  int result; // eax

  IO_SeekStreamGuarded(*(_DWORD *)(source + 8), 0, 2u, heap_ctx);
  result = Compat_StreamTell(*(_DWORD *)(source + 8));
  *(_DWORD *)(source + 48) = result;
  return result;
}

//----- (004799B0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode1(int *result, int position, int heap_ctx)
{
  if ( position != result[12] || result[13] != 1 )
  {
    IO_SeekStreamGuarded(result[2], position, 0, heap_ctx);
    result[13] = 1;
    result[12] = position;
  }
  return result;
}

//----- (004799E0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode2(int *result, int position, int heap_ctx)
{
  if ( position != result[12] || result[13] != 2 )
  {
    IO_SeekStreamGuarded(result[2], position, 0, heap_ctx);
    result[13] = 2;
    result[12] = position;
  }
  return result;
}

//----- (00479A10) --------------------------------------------------------
int  Res_StreamWriteWithXorCipher(int *stream, const void *buffer, int a3, unsigned int a4)
{
  unsigned int remaining; // ecx
  unsigned __int8 *v6; // eax
  int i; // edx
  int v8; // ecx
  int result; // eax
  int encoded_byte; // [esp+0h] [ebp-18h]
  unsigned __int8 *temp_buffer; // [esp+4h] [ebp-14h]

  if ( stream[5] )
  {
    temp_buffer = (unsigned __int8 *)j_Mem_Alloc(a3);
    qmemcpy(temp_buffer, buffer, a4);
    remaining = a4;
    v6 = temp_buffer;
    for ( i = stream[12]; remaining; *(v6 - 1) = encoded_byte )
    {
      --remaining;
      encoded_byte = (i + stream[5]) ^ *v6++;
      ++i;
    }
    fwrite_(temp_buffer, 1, stream[2], a4);
    j_j__nfree_();
    stream[12] += v8;
    return v8;
  }
  else
  {
    result = fwrite_(buffer, 1, stream[2], a4);
    stream[12] += result;
  }
  return result;
}
// 479AA7: variable 'v8' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00479AE0) --------------------------------------------------------
int * File_ConstructReadOnlySource(int *source, const CHAR *path, int a3, int a4, int a5)
{
  int *result; // eax

  result = File_SourceConstructFromStream(source, path, (unsigned __int8 *)aRb_11, a4, a5, a3);
  *result = (int)g_FileReadOnlySource_VTable;
  return result;
}
// 510C04: using guessed type int (*off_510C04[4])();

//----- (00479B00) --------------------------------------------------------
_DWORD * File_OpenMountRootEntry(int fs, char flags, DWORD heap_ctx)
{
  _DWORD *result; // eax
  int root_entry; // esi

  if ( (flags & 8) != 0 )
    return 0;
  root_entry = File_ResolvePathByParentAndLeaf((_DWORD *)fs, (const char *)(uintptr_t)(unsigned int)g_FileSystemStrippedPathHolderText, heap_ctx);
  if ( !root_entry )
    return 0;
  result = (_DWORD *)Mem_Alloc(20, fs, flags, heap_ctx);
  if ( result )
  {
    result = FileSystem_ArchiveEntryStreamCtor(result, root_entry, fs);
    *result = g_FileArchiveEntryStream_VTable;
  }
  return result;
}
// 510B74: using guessed type int (*off_510B74[10])();

//----- (00479BE0) --------------------------------------------------------
int * File_AllocateReadOnlySource(const CHAR *path, int a2, char cipher_key, DWORD heap_ctx, int a5)
{
  int *result; // eax

  result = (int *)Mem_Alloc(56, a2, cipher_key, heap_ctx);
  if ( result )
    return File_ConstructReadOnlySource(result, path, a2, cipher_key, a5);
  return result;
}

//----- (00479C20) --------------------------------------------------------
_DWORD * File_CacheNodeConstructBase(_DWORD *result)
{
  *result = g_FileCacheNode_VTable;
  return result;
}
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00479C30) --------------------------------------------------------
int  Res_XorDecodeByte(int stream, int a2, int encoded_byte)
{
  return encoded_byte ^ (a2 + *(_DWORD *)(stream + 20));
}

//----- (00479C40) --------------------------------------------------------
unsigned __int8 * Compat_QueryXorDecodeBuffer(int stream, unsigned __int8 *buffer, int length)
{
  unsigned __int8 *result; // eax
  int i; // edx
  int decoded_byte; // [esp+0h] [ebp-10h]

  result = buffer;
  for ( i = *(_DWORD *)(stream + 48); length; *(result - 1) = decoded_byte )
  {
    --length;
    decoded_byte = (i + *(_DWORD *)(stream + 20)) ^ *result++;
    ++i;
  }
  return result;
}

//----- (00479C80) --------------------------------------------------------
_DWORD * Compat_QueryConstructDefault(int a1)
{
  _DWORD *v1; // eax
  _DWORD *result; // eax

  v1 = (_DWORD *)(a1 + 12);
  *v1 = 0;
  result = v1 - 3;
  result[4] = &g_PathEntry_Vtable;
  result[7] = 0;
  *result = g_FileSource_VTable;
  return result;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479CB0) --------------------------------------------------------
int  Compat_QuerySkipBytes(int query, int count)
{
  uintptr_t *vtable;

  if ( !query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(query, count);
}

//----- (00479CC0) --------------------------------------------------------
int  Compat_QuerySkipBytesFromBase(int query, int offset)
{
  uintptr_t *vtable;

  if ( !query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(query, offset + *(_DWORD *)(query + 12));
}

//----- (00479CD0) --------------------------------------------------------
int  Compat_QueryGetLength(int query)
{
  return *(_DWORD *)(query + 8);
}

//----- (00479CE0) --------------------------------------------------------
int  Compat_QueryDestruct(int result, char flags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatQuery_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (flags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 479D09: variable 'v4' is possibly undefined
// 479D00: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00479D20) --------------------------------------------------------
int  Compat_QueryCloseAndDestruct(_DWORD *query, char flags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(query, &g_CompatQueryCloseAndDestruct_DtorArrayDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = File_SourceScalarDtor(query, 1);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 479D50: variable 'v4' is possibly undefined
// 479D5A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00479D60) --------------------------------------------------------
int Rules_InitFacts(void)
{
  Rules_InitFactHashTable();
  Rules_AddResetFunction((int)aFacts_0, (int)Rules_ResetFacts, 60);
  Rules_AddClearReadyFunction((int)aFacts_0, (int)Rules_ClearFacts, 0);
  Rules_AddPeriodicFunction((int)aFacts_0, (int)Rules_RemoveGarbageFacts, 0);
  Rules_RegisterFactsConstruct();
  Rules_AddWatchItem((int)aFacts_0, 0, 80, (int)&g_Rules_WatchFactsFlag, (int)Rules_ToggleFactWatchFlag, (int)Rules_WatchPrintFactsState);
  Rules_RegisterFactCommands();
  Rules_RegisterFactQueryFunctions();
  Rules_RegisterFactPatternNetworkPersistence();
  return Rules_RegisterFactPatternNetworkCodeGen();
}
// 51A150: using guessed type int dword_51A150;

//----- (00479DE0) --------------------------------------------------------
signed int __fastcall Rules_PrintFactWithIndex(int logicalName, int fact)
{
  int v3; // ecx
  int v4; // ecx
  _BYTE buffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+14h] [ebp-8h]

  v7 = logicalName;
  sprintf_(buffer, "f-%-5ld ", *(_DWORD *)(fact + 24));
  Output_Write(v3, (int)buffer, v3);
  return Rules_PrintFact(v4, fact);
}
// 479E03: variable 'v3' is possibly undefined
// 479E0C: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00479E20) --------------------------------------------------------
signed int __fastcall Rules_PrintFactLabel(int logicalName, int fact)
{
  int v2; // ecx
  _BYTE buffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v5; // [esp+14h] [ebp-8h]

  v5 = logicalName;
  sprintf_(buffer, "f-%ld", *(_DWORD *)(fact + 24));
  return Output_Write(v2, (int)buffer, v2);
}
// 479E41: variable 'v2' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00479E50) --------------------------------------------------------
signed int  Rules_PrintFactIdentifier(int logicalName, int fact)
{
  int v2; // ecx
  int v4; // ecx
  char *label_text; // edx
  signed int result; // eax
  int v7; // ecx

  v2 = logicalName;
  if ( g_Print_AddressesToStringsFlag )
    Output_Write(logicalName, (int)asc_502524, logicalName);
  if ( (void **)fact == &g_Rules_DummyFactPtr )
  {
    label_text = aDummyFact;
  }
  else
  {
    Output_Write(v2, (int)aFact_2, v2);
    Rules_PrintLongInteger(v4, *(_DWORD *)(fact + 24));
    label_text = asc_502530;
  }
  result = Output_Write(v2, (int)label_text, v2);
  if ( g_Print_AddressesToStringsFlag )
    return Output_Write(v7, (int)asc_502524, v7);
  return result;
}
// 479E6E: variable 'v2' is possibly undefined
// 479E78: variable 'v4' is possibly undefined
// 479EAF: variable 'v7' is possibly undefined
// 51A114: using guessed type void *off_51A114;
// 51A5FC: using guessed type int dword_51A5FC;

//----- (00479EC0) --------------------------------------------------------
int  Rules_DecrementFactRefCount(int result)
{
  --*(_DWORD *)(result + 8);
  return result;
}

//----- (00479ED0) --------------------------------------------------------
int  Rules_IncrementFactRefCount(int result)
{
  ++*(_DWORD *)(result + 8);
  return result;
}

//----- (00479EE0) --------------------------------------------------------
signed int  Rules_PrintFact(int logicalName, int fact)
{
  int v3; // ecx
  int v4; // ecx
  int multifield; // edi

  if ( (*(_BYTE *)(*(_DWORD *)(fact + 16) + 24) & 1) == 0 )
    return Rules_PrintTemplateFactSlots(logicalName, fact, fact);
  Output_Write(logicalName, (int)asc_502544, fact);
  Output_Write(logicalName, *(_DWORD *)(**(_DWORD **)(v3 + 16) + 16), v3);
  multifield = *(_DWORD *)(v4 + 56);
  if ( *(_DWORD *)(multifield + 6) )
  {
    Output_Write(logicalName, (int)asc_502548, v4);
    Lexer_OutputFieldRange(logicalName, multifield, *(_DWORD *)(multifield + 6) - 1, 0, 0);
  }
  return Output_Write(logicalName, (int)asc_50254C, v4);
}
// 479EFC: variable 'v3' is possibly undefined
// 479F0B: variable 'v4' is possibly undefined

//----- (00479F50) --------------------------------------------------------
int  Rules_NetworkAssertFact(int fact, double a2)
{
  return Rules_MatchFactAgainstPatternNetwork(fact, *(_DWORD *)(*(_DWORD *)(fact + 16) + 32), 0, 0, a2, 0);
}

//----- (00479F70) --------------------------------------------------------
signed int  Rules_RetractFact(int fact_ptr, double a2)
{
  uintptr_t fact; // ecx

  fact = (uintptr_t)(unsigned int)fact_ptr;
  if ( g_Rules_JoinOperationInProgress )
  {
    Rules_PrintErrorID((int)aFactmngr, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactsMayNotBeR, 0);
    return 0;
  }
  if ( !fact )
  {
    while ( g_Rules_FactListHead )
      Rules_RetractFact(g_Rules_FactListHead, a2);
    return 1;
  }
  if ( *(char *)(fact + 29) < 0 )
    return 0;
  if ( (*(_BYTE *)((uintptr_t)(unsigned int)*(_DWORD *)(fact + 16) + 24) & 2) != 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502590, 0);
    Rules_PrintFactWithIndex((int)g_IO_LogicalNameTable_WTrace[0], (int)fact);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502598, 0);
  }
  g_Rules_FactListChangedFlag = 1;
  Rules_ReleaseLogicalSupportList((int)fact);
  Rules_RemoveFactHashEntry((int)fact);
  if ( (int)fact == g_Rules_LastFactPointer )
    g_Rules_LastFactPointer = *(_DWORD *)(fact + 32);
  if ( *(_DWORD *)(fact + 32) )
  {
    uintptr_t previous = (uintptr_t)(unsigned int)*(_DWORD *)(fact + 32);
    int next = *(_DWORD *)(fact + 36);
    *(_DWORD *)(previous + 36) = next;
    if ( next )
      *(_DWORD *)((uintptr_t)(unsigned int)next + 32) = *(_DWORD *)(fact + 32);
  }
  else
  {
    int new_head = *(_DWORD *)((uintptr_t)(unsigned int)g_Rules_FactListHead + 36);
    g_Rules_FactListHead = new_head;
    if ( new_head )
      *(_DWORD *)((uintptr_t)(unsigned int)new_head + 32) = 0;
  }
  Rules_DeinstallFact((int)fact);
  ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += 6 * *(_DWORD *)(fact + 46) + 60;
  *(_DWORD *)(fact + 36) = g_Rules_GarbageFactListHead;
  g_Rules_GarbageFactListHead = (int)fact;
  *(_BYTE *)(fact + 29) |= 0x80u;
  Lexer_ErrorRecover(0);
  g_Rules_JoinOperationInProgress = 1;
  Rules_RetractFactFromNetwork(*(_DWORD **)(fact + 20), a2);
  g_Rules_JoinOperationInProgress = 0;
  if ( !g_Rules_CurrentlyExecutingRule )
    Rules_FlushPendingNetworkGarbage();
  Rules_FlushPendingDependencyDestructors();
  if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
    Rules_RunPeriodicCleanup(1, 0);
  return 1;
}
// 51A110: using guessed type int dword_51A110;
// 51A154: using guessed type int dword_51A154;
// 51A158: using guessed type int dword_51A158;
// 51A15C: using guessed type int dword_51A15C;
// 51A1F0: using guessed type int dword_51A1F0;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A954: using guessed type int dword_51A954;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047A120) --------------------------------------------------------
_DWORD *Rules_RemoveGarbageFacts(void)
{
  _DWORD *result; // eax
  int v1; // edx
  _DWORD *v2; // edx
  int v3; // ecx

  result = (_DWORD *)g_Rules_GarbageFactListHead;
  if ( g_Rules_GarbageFactListHead )
  {
    do
    {
      while ( 1 )
      {
        v1 = result[9];
        if ( !result[2] && (result[7] & 0x7FFF) > g_ClipsCurrentEvaluationDepth )
          break;
        result = (_DWORD *)result[9];
        if ( !v1 )
          return result;
      }
      --g_ClipsEphemeralItemCount;
      g_ClipsEphemeralItemBytes -= 6 * *(_DWORD *)((char *)result + 46) + 60;
      Rules_ReturnFact(result);
      if ( v3 )
        *(_DWORD *)(v3 + 36) = v2;
      else
        g_Rules_GarbageFactListHead = (int)v2;
      result = v2;
    }
    while ( v2 );
  }
  return result;
}
// 47A16E: variable 'v3' is possibly undefined
// 47A170: variable 'v2' is possibly undefined
// 51A154: using guessed type int dword_51A154;
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A96C: using guessed type int dword_51A96C;

//----- (0047A1A0) --------------------------------------------------------
_DWORD * Rules_AssertFactDriver(_DWORD *fact, double a2)
{
  char *slot_ptr; // eax
  int slot_count; // ecx
  int slot_index; // ebx
  char *slot_cursor; // edx
  signed int *interned_nil; // eax
  int v9; // ecx
  int hash_value; // ecx
  int prev_fact; // eax
  int fact_index; // eax
  int time_tag; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _DWORD *v17; // ecx

  if ( g_Rules_JoinOperationInProgress )
  {
    Rules_ReturnFact(fact);
    Rules_PrintErrorID((int)aFactmngr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactsMayNotBeA, v9);
    return 0;
  }
  slot_ptr = (char *)fact + 54;
  slot_count = *((_DWORD *)slot_ptr - 2);
  slot_index = 0;
  if ( slot_count > 0 )
  {
    slot_cursor = slot_ptr;
    do
    {
      if ( *(_WORD *)slot_cursor == 105 )
      {
        *(_WORD *)slot_cursor = 2;
        interned_nil = Str_Intern(aNil_2, slot_count);
        *(_DWORD *)(slot_cursor + 2) = interned_nil;
      }
      ++slot_index;
      slot_cursor += 6;
    }
    while ( slot_index < slot_count );
  }
  hash_value = Rules_DeduplicateFactOnAssert((int)fact);
  if ( hash_value < 0 )
    return 0;
  if ( Rules_AddLogicalDependencyLink((int)fact, 0) )
  {
    Rules_InsertFactHashEntry((int)fact, hash_value);
    fact[9] = 0;
    fact[5] = 0;
    prev_fact = g_Rules_LastFactPointer;
    fact[8] = g_Rules_LastFactPointer;
    if ( prev_fact )
      *(_DWORD *)(prev_fact + 36) = fact;
    else
      g_Rules_FactListHead = (int)fact;
    fact_index = g_Rules_NextFactIndex;
    g_Rules_LastFactPointer = (int)fact;
    ++g_Rules_NextFactIndex;
    fact[6] = fact_index;
    time_tag = g_Rules_EntityTimeTagCounter++;
    fact[3] = time_tag;
    Rules_InstallFact(fact);
    if ( (*(_BYTE *)(fact[4] + 24) & 2) != 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_5025D4, v14);
      Rules_PrintFactWithIndex(v15, (int)fact);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502598, v16);
    }
    g_Rules_FactListChangedFlag = 1;
    Rules_CheckFactAgainstSlotConstraints((int)fact);
    Lexer_ErrorRecover(0);
    g_Rules_JoinOperationInProgress = 1;
    Rules_MatchFactAgainstPatternNetwork((int)fact, *(_DWORD *)(fact[4] + 32), 0, 0, a2, 0);
    g_Rules_JoinOperationInProgress = 0;
    Rules_FlushPendingDependencyDestructors();
    if ( !g_Rules_CurrentlyExecutingRule )
      Rules_FlushPendingNetworkGarbage();
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    return fact;
  }
  else
  {
    Rules_ReturnFact(fact);
    return 0;
  }
}
// 47A1CF: variable 'v4' is possibly undefined
// 47A1D4: variable 'v6' is possibly undefined
// 47A217: variable 'v9' is possibly undefined
// 47A233: variable 'v10' is possibly undefined
// 47A29E: variable 'v14' is possibly undefined
// 47A2AA: variable 'v15' is possibly undefined
// 47A2B9: variable 'v16' is possibly undefined
// 47A2ED: variable 'v17' is possibly undefined
// 51A110: using guessed type int dword_51A110;
// 51A158: using guessed type int dword_51A158;
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;
// 51A1F0: using guessed type int dword_51A1F0;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A954: using guessed type int dword_51A954;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51A998: using guessed type int dword_51A998;

//----- (0047A350) --------------------------------------------------------
signed int  Rules_RemoveAllFacts(double a1)
{
  signed int result; // eax

  for ( ; g_Rules_FactListHead; result = Rules_RetractFact(g_Rules_FactListHead, a1) )
    ;
  return result;
}
// 51A15C: using guessed type int dword_51A15C;

//----- (0047A3F0) --------------------------------------------------------
int  Lexer_EmitSlotBinding(int fact, char *slot_name, int a3, _DWORD *result_value)
{
  int deftemplate; // edi
  int result; // eax
  int multifieldValue; // eax
  signed int *slot_symbol; // eax
  _DWORD *slotDataObject; // ecx
  int slotType; // edx
  int slotMultifield; // eax
  _DWORD slotPosition[4]; // [esp+0h] [ebp-10h] BYREF

  slotPosition[3] = a3;
  deftemplate = *(_DWORD *)(fact + 16);
  if ( (*(_BYTE *)(deftemplate + 24) & 1) != 0 )
  {
    if ( !slot_name )
    {
      result_value[1] = *(__int16 *)(fact + 54);
      result_value[2] = *(_DWORD *)(fact + 56);
      multifieldValue = result_value[2];
      result_value[3] = 0;
      result_value[4] = *(_DWORD *)(multifieldValue + 6) - 1;
      return 1;
    }
    return 0;
  }
  slot_symbol = Str_Intern(slot_name, (int)result_value);
  result = (int)Lexer_FindTemplateSlot(deftemplate, (int)slot_symbol, slotPosition);
  if ( result )
  {
    slotDataObject[1] = *(__int16 *)(fact + 6 * (slotPosition[0] - 1) + 54);
    slotType = slotDataObject[1];
    slotDataObject[2] = *(_DWORD *)(fact + 6 * (slotPosition[0] - 1) + 56);
    if ( slotType == 4 )
    {
      slotMultifield = slotDataObject[2];
      slotDataObject[3] = 0;
      slotDataObject[4] = *(_DWORD *)(slotMultifield + 6) - 1;
    }
    return slotDataObject[1] != 105;
  }
  return result;
}
// 47A45D: variable 'v9' is possibly undefined

//----- (0047A730) --------------------------------------------------------
_DWORD * Rules_CreateFact(signed int slot_count)
{
  signed int v1; // ecx
  signed int effective_count; // edx
  int v3; // eax
  _DWORD *result; // eax
  __int16 eval_depth; // dx
  __int16 v6; // bx
  int v7; // edi
  __int16 v8; // dx

  v1 = slot_count;
  if ( slot_count <= 0 )
    effective_count = 1;
  else
    effective_count = slot_count;
  if ( (unsigned int)(6 * (effective_count - 1) + 60) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (effective_count - 1) + 240) )
  {
    v3 = g_ClipsMemoryTable + 24 * (effective_count - 1);
    g_ClipsMemFreeListTemp = *(_DWORD *)(v3 + 240);
    *(_DWORD *)(v3 + 240) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (effective_count - 1) + 60);
  }
  eval_depth = g_ClipsCurrentEvaluationDepth;
  result[6] = 0;
  result[2] = 0;
  *result = &g_Rules_FactPatternEntityRecord;
  result[1] = 0;
  result[4] = 0;
  v6 = *((_WORD *)result + 14);
  result[9] = 0;
  result[8] = 0;
  *((_WORD *)result + 14) = v6 & 0x8000;
  v7 = result[7];
  result[5] = 0;
  result[7] = eval_depth & 0x7FFF | v7;
  LOBYTE(eval_depth) = *((_BYTE *)result + 29);
  *(_DWORD *)((char *)result + 46) = v1;
  *((_BYTE *)result + 29) = eval_depth & 0x7F;
  v8 = g_ClipsCurrentEvaluationDepth;
  result[10] = 0;
  *((_WORD *)result + 22) = v8;
  return result;
}
// 47A802: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047A850) --------------------------------------------------------
_DWORD * Rules_ReturnFact(_DWORD *fact)
{
  _DWORD *v2; // ebx
  int slot_index; // ecx
  _DWORD *slot_cursor; // edx
  int v5; // eax
  unsigned int bucket_size; // eax
  _DWORD *result; // eax

  v2 = fact + 10;
  slot_index = 0;
  if ( *(int *)((char *)fact + 46) > 0 )
  {
    slot_cursor = fact + 10;
    do
    {
      if ( *((_WORD *)slot_cursor + 7) == 4 )
        Rules_ReturnMultifieldToPool((_DWORD *)slot_cursor[4]);
      ++slot_index;
      slot_cursor = (_DWORD *)((char *)slot_cursor + 6);
    }
    while ( slot_index < *(_DWORD *)((char *)v2 + 6) );
  }
  if ( *(_DWORD *)((char *)fact + 46) )
    v5 = *(_DWORD *)((char *)fact + 46);
  else
    v5 = 1;
  bucket_size = 6 * (v5 - 1) + 60;
  g_ClipsMemPoolReturnBucketIndex = bucket_size;
  if ( bucket_size >= 0x1F4 )
    return (_DWORD *)Mem_SmallBlockRelease(fact, bucket_size);
  g_ClipsMemFreeListTemp = (int)fact;
  *fact = *(_DWORD *)(g_ClipsMemoryTable + 4 * bucket_size);
  result = (_DWORD *)(g_ClipsMemoryTable + 4 * g_ClipsMemPoolReturnBucketIndex);
  *result = g_ClipsMemFreeListTemp;
  return result;
}
// 47A86D: variable 'v3' is possibly undefined
// 47A871: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0047A900) --------------------------------------------------------
int  Rules_InstallFact(_DWORD *fact)
{
  int result; // eax
  int slot_index; // ebx
  int slot_cursor; // ecx
  int v5; // ecx

  ++g_Rules_InstalledFactCount;
  result = fact[4];
  ++*(_DWORD *)(result + 28);
  slot_index = 0;
  if ( *(int *)((char *)fact + 46) > 0 )
  {
    slot_cursor = (int)(fact + 10);
    do
    {
      Rules_AtomInstall(*(__int16 *)(slot_cursor + 14), *(_DWORD *)(slot_cursor + 16), slot_cursor);
      ++slot_index;
      result = *(_DWORD *)((char *)fact + 46);
      slot_cursor = v5 + 6;
    }
    while ( slot_index < result );
  }
  ++fact[2];
  return result;
}
// 47A936: variable 'v5' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A950) --------------------------------------------------------
int  Rules_DeinstallFact(int fact)
{
  int slot_base; // esi
  int result; // eax
  int slot_index; // ebx
  int slot_cursor; // ecx
  int v6; // ecx

  slot_base = fact + 40;
  --g_Rules_InstalledFactCount;
  result = *(_DWORD *)(fact + 16);
  --*(_DWORD *)(result + 28);
  slot_index = 0;
  if ( *(int *)(slot_base + 6) > 0 )
  {
    slot_cursor = slot_base;
    do
    {
      Rules_AtomDeinstall(*(__int16 *)(slot_cursor + 14), *(__int16 **)(slot_cursor + 16), slot_cursor);
      ++slot_index;
      result = *(_DWORD *)(slot_base + 6);
      slot_cursor = v6 + 6;
    }
    while ( slot_index < result );
  }
  --*(_DWORD *)(fact + 8);
  return result;
}
// 47A989: variable 'v6' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A9A0) --------------------------------------------------------
int  Rules_GetNextFact(int fact)
{
  if ( !fact )
    return g_Rules_FactListHead;
  if ( *(char *)(fact + 29) >= 0 )
    return *(_DWORD *)(fact + 36);
  return 0;
}
// 51A15C: using guessed type int dword_51A15C;

//----- (0047A9C0) --------------------------------------------------------
int  Rules_GetNextFactInModule(int fact)
{
  int next_fact; // edx

  if ( fact )
  {
    if ( *(char *)(fact + 29) < 0 )
      return 0;
    next_fact = *(_DWORD *)(fact + 36);
  }
  else
  {
    next_fact = g_Rules_FactListHead;
    if ( g_Rules_LastFactModuleCache != g_Module_ChangeGeneration )
    {
      Lexer_MarkImpliedTemplates();
      g_Rules_LastFactModuleCache = g_Module_ChangeGeneration;
    }
  }
  while ( next_fact && (*(_BYTE *)(*(_DWORD *)(next_fact + 16) + 24) & 4) == 0 )
    next_fact = *(_DWORD *)(next_fact + 36);
  return next_fact;
}
// 47A9DD: variable 'v1' is possibly undefined
// 51A15C: using guessed type int dword_51A15C;
// 51A168: using guessed type int dword_51A168;
// 51A9C0: using guessed type int dword_51A9C0;

//----- (0047AA40) --------------------------------------------------------
int  Rules_GetFactIndex(int fact)
{
  return *(_DWORD *)(fact + 24);
}

//----- (0047AA50) --------------------------------------------------------
_DWORD * Rules_Log(const char *string, int a2, double a3)
{
  _DWORD *result; // eax

  result = Rules_StringToFact(string, a2, a3);
  if ( result )
    return Rules_AssertFactDriver(result, a3);
  return result;
}

//----- (0047AA80) --------------------------------------------------------
int Rules_GetInstalledFactCount(void)
{
  return g_Rules_InstalledFactCount;
}
// 51A164: using guessed type int dword_51A164;
