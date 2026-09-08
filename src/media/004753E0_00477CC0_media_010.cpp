/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../core/core_api.h"
#include "../units/units_api.h"
#include "../clips/clips_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004753E0) --------------------------------------------------------
int  Render_RestoreLostSurfaceIfNeeded(int ddraw_ctx)
{
  int result; // eax
  int dd_surface; // edx

  result = *(_DWORD *)(uintptr_t)(ddraw_ctx + 4);
  if ( !result )
    return 0;
  dd_surface = *(_DWORD *)(uintptr_t)(result + 164);
  if ( dd_surface )
  {
    result = Compat_DirectDrawSurface_IsLost((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)dd_surface);
    if ( result )
      return Compat_DirectDrawSurface_Restore((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)dd_surface);
  }
  return result;
}

//----- (00475420) --------------------------------------------------------
int  Render_SetPaletteEntryColor(int ddraw_ctx, int entry_index, char green, int red, char blue)
{
  _BYTE palette_entry[4]; // [esp+14h] [ebp-10h] BYREF
  int red_value; // [esp+18h] [ebp-Ch]

  red_value = red;
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(uintptr_t)(**(_DWORD **)(uintptr_t)(ddraw_ctx + 16) + 16))(
    *(_DWORD *)(uintptr_t)(ddraw_ctx + 16),
    0,
    entry_index,
    1,
    palette_entry);
  palette_entry[0] = red_value;
  palette_entry[1] = green;
  palette_entry[2] = blue;
  return (*(int (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(uintptr_t)(**(_DWORD **)(uintptr_t)(ddraw_ctx + 16) + 24))(
           *(_DWORD *)(uintptr_t)(ddraw_ctx + 16),
           0,
           entry_index,
           1,
           palette_entry);
}

//----- (004754B0) --------------------------------------------------------
int  IO_StreamWrite(int result, int a2, int a3, int a4)
{
  int backing_stream; // esi

  backing_stream = *(_DWORD *)(uintptr_t)(result + 16);
  if ( backing_stream )
    return (*(int (__stdcall **)(int, _DWORD, int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backing_stream + 24))(backing_stream, 0, a2, a4, a3);
  return result;
}

//----- (00475A83) --------------------------------------------------------
int  IO_ParseOpenModeFlags(unsigned __int8 *mode_string, _DWORD *commit_mode_out)
{
  unsigned __int8 *mode_cursor; // ebx
  int parse_ok; // ecx
  int plus_seen; // ebp
  int text_mode_seen; // esi
  int commit_seen; // edi
  unsigned __int8 first_char; // al
  unsigned __int8 mode_char; // al
  int Value; // [esp+0h] [ebp-18h]

  mode_cursor = mode_string;
  parse_ok = 1;
  plus_seen = 0;
  text_mode_seen = 0;
  commit_seen = 0;
  Value = 0;
  if ( commit_mode_out )
    *commit_mode_out = g_CRT_DefaultCommitMode == 1;
  first_char = *mode_string;
  if ( *mode_cursor < 0x72u )
  {
    if ( first_char == 97 )
    {
      LOBYTE(Value) = -126;
      goto LABEL_15;
    }
LABEL_14:
    _set_errno_(0);
    return 0;
  }
  if ( *mode_cursor > 0x72u )
  {
    if ( first_char == 119 )
    {
      LOBYTE(Value) = 2;
      goto LABEL_15;
    }
    goto LABEL_14;
  }
  LOBYTE(Value) = 1;
LABEL_15:
  while ( 1 )
  {
    mode_char = *++mode_cursor;
    if ( !*mode_cursor || !parse_ok )
      break;
    if ( mode_char < 0x63u )
    {
      if ( mode_char >= 0x2Bu )
      {
        if ( mode_char <= 0x2Bu )
        {
          if ( plus_seen )
            goto LABEL_28;
          plus_seen = 1;
          LOBYTE(Value) = Value | 3;
        }
        else if ( mode_char == 98 )
        {
          if ( text_mode_seen )
            goto LABEL_28;
          text_mode_seen = 1;
          LOBYTE(Value) = Value | 0x40;
        }
      }
    }
    else if ( mode_char <= 0x63u )
    {
      if ( commit_seen )
        goto LABEL_28;
      commit_seen = 1;
      *(_BYTE *)commit_mode_out |= 1u;
    }
    else if ( mode_char >= 0x6Eu )
    {
      if ( mode_char <= 0x6Eu )
      {
        if ( commit_seen )
        {
LABEL_28:
          parse_ok = 0;
        }
        else
        {
          commit_seen = 1;
          *(_BYTE *)commit_mode_out &= ~1u;
        }
      }
      else if ( mode_char == 116 )
      {
        if ( text_mode_seen )
          goto LABEL_28;
        text_mode_seen = 1;
      }
    }
  }
  if ( !text_mode_seen && g_CRT_DefaultFileTranslationMode == 512 )
    LOBYTE(Value) = Value | 0x40;
  return Value;
}
// 51A549: using guessed type int dword_51A549;
// 51A64C: using guessed type int dword_51A64C;

//----- (00475B9E) --------------------------------------------------------
int  IO_OpenStreamWithMode(
        const CHAR *file_path,
        int a2 CLASH95_UNUSED,
        int stream_flags,
        DWORD a4 CLASH95_UNUSED,
        int a5,
        int a6,
        int stream)
{
  unsigned int open_flags;
  int fd_index;
  int mode_char;

  (void)a5;
  (void)a6;
  *(_BYTE *)(uintptr_t)(stream + 12) &= 0xFCu;
  *(_BYTE *)(uintptr_t)(stream + 12) |= (unsigned __int8)stream_flags;
  if ( (stream_flags & 0x80u) != 0 )
    mode_char = 'a';
  else if ( (stream_flags & 2) != 0 )
    mode_char = 'w';
  else
    mode_char = 'r';
  if ( mode_char == 'r' )
  {
    open_flags = 0;
    if ( (stream_flags & 2) != 0 )
      open_flags = 2;
    if ( (stream_flags & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(file_path, mode_char, stream_flags);
  }
  else
  {
    open_flags = ((stream_flags & 1) != 0) + 33;
    if ( (stream_flags & 0x80u) == 0 )
      open_flags |= 0x40u;
    else
      open_flags |= 0x10u;
    if ( (stream_flags & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(file_path, mode_char, stream_flags);
  }
  if ( fd_index == -1 )
  {
    Compat_FreeFileStream(stream);
    return 0;
  }
  Compat_InitFileStream(stream, fd_index, mode_char, stream_flags);
  if ( (stream_flags & 0x80u) != 0 )
    Compat_StreamSeek(stream, 0, 2);
  _chktty_();
  return stream;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);
// 4884E3: using guessed type int _chktty_(void);

//----- (00475C84) --------------------------------------------------------
int  IO_OpenStream(
        const CHAR *file_path,
        unsigned __int8 *mode_string,
        int a3,
        int a4,
        DWORD a5)
{
  int result; // eax
  int open_flags; // ebx
  int stream_ptr; // eax
  int mode_info[4]; // [esp+0h] [ebp-10h] BYREF

  mode_info[3] = a3;
  result = IO_ParseOpenModeFlags(mode_string, ((_DWORD*)(mode_info)));
  open_flags = result;
  if ( result )
  {
    stream_ptr = Compat_AllocFileStream();
    if ( stream_ptr )
      return IO_OpenStreamWithMode(file_path, mode_info[0], open_flags, a5, a4, 0, stream_ptr);
    return 0;
  }
  return result;
}

//----- (00475CC8) --------------------------------------------------------
int  IO_FOpen(const CHAR *file_path, unsigned __int8 *mode_string, int a3, DWORD a4)
{
  return IO_OpenStream(file_path, mode_string, a3, 0, a4);
}

//----- (00475CD2) --------------------------------------------------------
int  IO_CloseStream(int stream, int error_code)
{
  int v3; // ecx
  _DWORD *i; // eax
  int stream_handle; // edx
  int *j; // edx
  int *list_node; // eax
  int old_head; // edx

  g_CRT_StaticLock1AcquireHook();
  for ( i = (_DWORD *)(uintptr_t)g_CRT_OpenStreamListHead; i; i = (_DWORD *)(uintptr_t)*i )
  {
    stream_handle = i[1];
    if ( stream == stream_handle )
    {
      if ( (*(_BYTE *)(uintptr_t)(stream_handle + 12) & 3) != 0 )
        _doclose_(v3, 1);
LABEL_6:
      g_CRT_StaticLock1ReleaseHook();
      return stream;
    }
  }
  for ( j = &g_IO_OpenStreamListHead; ; j = (int *)(uintptr_t)*j )
  {
    list_node = (int *)(uintptr_t)*j;
    if ( !*j )
      break;
    if ( stream == list_node[1] )
    {
      *j = *list_node;
      old_head = g_CRT_OpenStreamListHead;
      g_CRT_OpenStreamListHead = (int)(intptr_t)list_node;
      *list_node = old_head;
      goto LABEL_6;
    }
  }
  _set_errno_(error_code);
  g_CRT_StaticLock1ReleaseHook();
  return 0;
}
// 475CFA: variable 'v3' is possibly undefined
// 475ECD: using guessed type int __fastcall _doclose_(_DWORD, _DWORD);
// 485379: using guessed type _DWORD nullsub_8();
// 51A57C: using guessed type _DWORD (*off_51A57C)();
// 51A580: using guessed type _DWORD (*off_51A580)();
// 54DD88: using guessed type int dword_54DD88;
// 54DD8C: using guessed type int dword_54DD8C;

//----- (004761EF) --------------------------------------------------------
char * Str_FormatUnsignedRadixDigits(unsigned int value, char *buffer, unsigned int radix)
{
  char *out_cursor; // esi
  char *digit_cursor; // ecx
  char digit_char; // al
  char digit_stack[0x24]; // original stack +0x00 sentinel, +0x01 digits, +0x24 quotient
  unsigned int quotient; // [esp+24h] [ebp-14h]

  out_cursor = buffer;
  digit_stack[0] = 0; // 00476202: original zero sentinel before the first digit
  digit_cursor = &digit_stack[1];
  do
  {
    quotient = value / radix;
    *digit_cursor = g_Str_RadixDigitCharacters[value % radix];
    value = quotient;
    ++digit_cursor;
  }
  while ( quotient );
  do
  {
    digit_char = *--digit_cursor;
    *out_cursor++ = *digit_cursor;
  }
  while ( digit_char );
  return buffer;
}

//----- (00476238) --------------------------------------------------------
int  Str_FormatSignedRadixDigits(signed int value, char *buffer, unsigned int radix)
{
  char *original_buffer = buffer;
  unsigned int magnitude = (unsigned int)value;

  if ( radix == 10 && value < 0 )
  {
    // Original NEG EAX wraps in 32 bits, including INT_MIN.
    magnitude = 0u - magnitude;
    *buffer++ = '-';
  }
  Str_FormatUnsignedRadixDigits(magnitude, buffer, radix);
  // 0047624F: EAX receives the original destination saved in ECX.
  return (int)(uintptr_t)original_buffer;
}

//----- (004762AE) --------------------------------------------------------
unsigned int  IO_OpenFileDescriptorBinaryMode(const CHAR *file_path, DWORD a2)
{
  return CRT_OpenFile(a2, file_path, 98);
}

//----- (00476301) --------------------------------------------------------
/* compatibility/decomp_runtime_stubs.c; renders Watcom printf output for
   compat file streams (the recovered CRT putc bridge is a no-op, so without
   this the fast-save facts stream received nothing). */

int Output_WriteFormatted(int a1, int a2, int output_stream, int format_string, ...)
{
  const char *format;
  int arg_count;
  int args_ptr;
  int cursor;
  int result;
  int direct_result;
  int i;
  va_list args;

  (void)a1;
  (void)a2;
  if ( !output_stream || !format_string )
    return 0;

  format = (const char *)(uintptr_t)(unsigned int)format_string;
  arg_count = Compat_CountPrintfArgs32(format);
  if ( arg_count <= 0 )
  {
    direct_result = Compat_StreamWriteFormat32(output_stream, format, 0, 0);
    if ( direct_result >= 0 )
      return direct_result;
    cursor = 0;
    return CRT_VfprintfLockedWrite(output_stream, format_string, &cursor);
  }

  args_ptr = Compat_AllocLow32Bytes(4 * arg_count);
  if ( !args_ptr )
    return 0;

  va_start(args, format_string);
  for ( i = 0; i < arg_count; ++i )
    *(_DWORD *)(uintptr_t)(unsigned int)(args_ptr + 4 * i) = va_arg(args, int);
  va_end(args);

  direct_result = Compat_StreamWriteFormat32(
    output_stream,
    format,
    (const unsigned int *)(uintptr_t)(unsigned int)args_ptr,
    arg_count);
  if ( direct_result >= 0 )
  {
    Compat_FreeLow32Bytes(args_ptr);
    return direct_result;
  }

  cursor = args_ptr;
  result = CRT_VfprintfLockedWrite(output_stream, format_string, &cursor);
  Compat_FreeLow32Bytes(args_ptr);
  return result;
}

//----- (00476A0C) --------------------------------------------------------
void __thiscall Compat_TriggerFatalRuntimeErrorOnce(void *this_)
{
  if ( !g_FatalRuntimeErrorOnceGuard )
  {
    g_FatalRuntimeErrorOnceGuard = 1;
    _wcpp_4_fatal_runtime_error__(((_DWORD)(uintptr_t)(this_)), 1);
  }
}
// 486342: using guessed type int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD, _DWORD);
// 51A644: using guessed type __int16 word_51A644;

//----- (00476A80) --------------------------------------------------------
int FileSystem_InitCurrentEntryPathHolder(void)
{
  g_FileSystemStrippedPathHolderText = 0;
  g_CurrentEntryPathHolder_VtablePtr = (int)(intptr_t)&g_PathEntry_Vtable;
  return CRT_RegisterFinalizableObject(((_DWORD)(uintptr_t)(&g_PathEntry_Vtable)), 0);
}
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EC94: using guessed type int (*off_50EC94)();
// 54DD00: using guessed type int dword_54DD00;
// 54DD04: using guessed type int dword_54DD04;

//----- (00476AB0) --------------------------------------------------------
int  FileSystem_WalkEntryListInvokingCleanup(int result)
{
  int i; // ecx
  _DWORD *v2; // ecx
  int (__fastcall ***v3)(_DWORD *, _DWORD); // esi
  int v4; // ecx

  for ( i = result; *(_DWORD *)(uintptr_t)i; result = (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)v4 + 16))() )
  {
    result = (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)i + 12))();
    if ( !result )
      break;
    v3 = (int (__fastcall ***)(_DWORD *, _DWORD))(uintptr_t)v2[2];
    if ( !v3 )
      break;
    result = (**v3)(v2, *v2);
    if ( result )
      break;
  }
  return result;
}
// 476ABC: variable 'i' is possibly undefined
// 476AC7: variable 'v2' is possibly undefined
// 476ADF: variable 'v4' is possibly undefined

//----- (00476AF0) --------------------------------------------------------
int  FileSystem_ConstructMountTable(int mount_table, int file_system, const CHAR *log_file_path, DWORD alloc_context)
{
  int entry_path_holder; // [esp+4h] [ebp-1Ch] BYREF
  int (**entry_path_vtable)(); // [esp+8h] [ebp-18h]
  int open_mode_handle; // [esp+Ch] [ebp-14h]
  _DWORD *entry_record;
  int entry_index;
  int child_path;

  *(_DWORD *)(uintptr_t)(mount_table + 4) = 0;
  *(_DWORD *)(uintptr_t)(mount_table + 8) = (int)(intptr_t)&g_PathEntry_Vtable;
  *(_DWORD *)(uintptr_t)(mount_table + 12) = 0;
  *(_DWORD *)(uintptr_t)(mount_table + 16) = (int)(intptr_t)&g_PathEntry_Vtable;
  *(_DWORD *)(uintptr_t)(mount_table + 24) = 1;
  *(_DWORD *)(uintptr_t)(mount_table + 28) = 0;
  *(_DWORD *)(uintptr_t)(mount_table + 32) = 0;
  *(_DWORD *)(uintptr_t)(mount_table + 36) = (int)(intptr_t)g_PathEntryArray_Vtable;
  *(_DWORD *)(uintptr_t)(mount_table + 20) = 0;
  *(_DWORD *)(uintptr_t)mount_table = (int)(intptr_t)g_FileSystemMountTable_VTable;
  open_mode_handle = 0;
  if ( log_file_path )
    open_mode_handle = IO_FOpen(log_file_path, (unsigned __int8 *)aWt, mount_table, alloc_context);
  entry_path_holder = 0;
  entry_path_vtable = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&entry_path_holder)));
  entry_path_vtable = ((int (**)())(&g_PathEntry_Vtable));
  if ( *(_DWORD *)(uintptr_t)(mount_table + 28) == *(_DWORD *)(uintptr_t)(mount_table + 32) )
    PathEntryArray_GrowByDelta(((int*)((_DWORD *)(uintptr_t)(mount_table + 20))), *(_DWORD *)(uintptr_t)(mount_table + 24));
  entry_index = *(_DWORD *)(uintptr_t)(mount_table + 28);
  *(_DWORD *)(uintptr_t)(mount_table + 28) = entry_index + 1;
  entry_record = (_DWORD *)(uintptr_t)(16 * entry_index + *(_DWORD *)(uintptr_t)(mount_table + 20));
  *entry_record = file_system;
  Compat_StringHolderCopyText(entry_record + 1, Compat_StringHolderGetText((_DWORD *)&entry_path_holder));
  entry_record[3] = open_mode_handle;
  FileSystem_DiskMountResolveRegisteredRootPath(file_system, mount_table);
  child_path = (int)(intptr_t)FileSystem_DiskMountGetCurrentDirectory((void *)(intptr_t)file_system);
  if ( child_path )
    FileSystem_SetCurrentDirectoryFromPath((const char **)(intptr_t)mount_table, child_path);
  Compat_StringHolderDestroyStack((_DWORD *)&entry_path_holder, 0);
  return mount_table;
}

//----- (00476C30) --------------------------------------------------------
int  FileSystem_DestructMountTable(_DWORD *mount_table, char flags)
{
  _DWORD *v3; // ecx
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(((_DWORD)(uintptr_t)(mount_table)), ((_DWORD)(uintptr_t)(&g_FileSystemMountTable_DtorArrayTag)));
    j_j__nfree_();
    return v8;
  }
  else
  {
    *mount_table = ((_DWORD)(uintptr_t)(g_FileSystemMountTable_VTable));
    FileSystem_RemoveMountsFromIndex((int)(intptr_t)mount_table, 0);
    v3[4] = ((_DWORD)(uintptr_t)(g_PathEntryArray_Vtable));
    PathEntryArray_DestructElements(v3);
    v5 = Compat_StringHolderScalarDeletingDtor(v4 - 8, 0);
    v6 = Compat_StringHolderScalarDeletingDtor(v5 - 8, 0);
    if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
    {
      j__nfree_();
      return v9;
    }
    else
    {
      return v6 - 4;
    }
  }
}
// 476C4D: variable 'v3' is possibly undefined
// 476C5B: variable 'v4' is possibly undefined
// 476C89: variable 'v8' is possibly undefined
// 476C95: variable 'v9' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50ECA4: using guessed type int (*off_50ECA4[2])();
// 510964: using guessed type int (*off_510964[13])();

//----- (00476CA0) --------------------------------------------------------
_DWORD * FileSystem_RemoveMountsFromIndex(int mount_table, int start_index)
{
  int entry_index; // ecx
  _DWORD *result; // eax
  _DWORD *v4; // edi
  _DWORD *v5; // ebp
  int entry_offset; // esi
  int mount_obj; // eax
  int v8; // ecx
  _DWORD *v9; // [esp+0h] [ebp-1Ch]

  entry_index = *(_DWORD *)(uintptr_t)(mount_table + 28) - 1;
  result = (_DWORD *)(uintptr_t)(mount_table + 20);
  if ( entry_index >= start_index )
  {
    v4 = result;
    v5 = result;
    v9 = result;
    entry_offset = 16 * entry_index;
    do
    {
      mount_obj = *(_DWORD *)(uintptr_t)(entry_offset + *v9);
      if ( mount_obj )
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)mount_obj + 8))();
      if ( *(_DWORD *)(uintptr_t)(entry_offset + *v5 + 12) )
      {
        fclose_(entry_index);
        *(_DWORD *)(uintptr_t)(entry_offset + *v5 + 12) = 0;
      }
      result = PathEntryArray_RemoveAt(v4, entry_index, 1);
      entry_index = v8 - 1;
      entry_offset -= 16;
    }
    while ( entry_index >= start_index );
  }
  return result;
}
// 476CDD: variable 'v2' is possibly undefined
// 476CFF: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00476D20) --------------------------------------------------------
char  FileSystem_NormalizePath(int mount_table, const char **path_holder)
{
  const char *path_text;
  signed int colon_index;
  signed int search_index;
  int dot_index;
  int dot_next_index;
  int parent_index;
  _DWORD v18[2];

  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || !*path_text )
    return 0;
  if ( Compat_StringHolderFindCharFrom(path_holder, 58, 0) == -1 )
  {
    if ( *path_text == 92 )
    {
      Compat_StringHolderPrependText(path_holder, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(mount_table + 4));
    }
    else
    {
      v18[0] = 0;
      v18[1] = (int)(intptr_t)&g_PathEntry_Vtable;
      Compat_StringHolderConstructJoined(v18, (_DWORD *)(uintptr_t)(unsigned int)(mount_table + 4), (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(mount_table + 12));
      Compat_StringHolderPrependText(path_holder, Compat_StringHolderGetText(v18));
      Compat_StringHolderDestroyStack(v18, 1);
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(path_holder, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(path_holder, colon_index, asc_5024B0);
  search_index = 0;
  while ( 1 )
  {
    dot_index = Compat_StringHolderFindCharFrom(path_holder, 46, search_index);
    if ( dot_index == -1 )
      break;
    dot_next_index = dot_index + 1;
    path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
    if ( !path_text )
      break;
    if ( path_text[dot_next_index] == 46 )
    {
      if ( path_text[dot_index - 1] != 92 || (parent_index = Compat_StringHolderFindLastBackslashBefore((char **)path_holder, dot_index - 2), parent_index == -1) )
      {
        Compat_StringHolderCopyText((_DWORD *)path_holder, "");
        return 0;
      }
      Compat_StringHolderRemoveRange((char **)path_holder, parent_index, (unsigned int)(uintptr_t)path_holder, dot_index - parent_index + 2);
    }
    else if ( path_text[dot_index - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)path_holder, dot_index - 1, (unsigned int)(uintptr_t)path_holder, 2);
    }
    else
    {
      search_index = dot_next_index;
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(path_holder, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(path_holder, colon_index, asc_5024B4);
  return (char)(unsigned __int8)(uintptr_t)Compat_StringHolderUppercaseInPlace(path_holder, (unsigned int)(uintptr_t)path_holder);
}

//----- (00476ED0) --------------------------------------------------------
const char ** FileSystem_StripMountPrefix(int mount_table, int entry_index, unsigned int a3, const char **path_holder)
{
  const char *entry_path;
  const char *holder_text;
  unsigned int holder_len;
  int entry_path_len;
  const char **result CLASH95_UNUSED; // eax

  entry_path = Compat_StringHolderGetText((_DWORD *)(uintptr_t)(16 * entry_index + *(_DWORD *)(uintptr_t)(mount_table + 20) + 4));
  if ( entry_path )
  {
    a3 = (unsigned int)strlen(entry_path);
    entry_path_len = (int)a3;
  }
  else
  {
    entry_path_len = 0;
  }
  result = ((const char**)(Compat_StringHolderRemoveRange((char **)path_holder, 0, a3, entry_path_len)));
  holder_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( holder_text )
  {
    holder_len = (unsigned int)strlen(holder_text) + 1;
    if ( holder_len != 1 && *(const unsigned char *)holder_text == 92 )
      return ((const char**)(Compat_StringHolderRemoveRange((char **)path_holder, 0, holder_len - 1, 1)));
  }
  return path_holder;
}

//----- (00476F40) --------------------------------------------------------
int  FileSystem_CallEntryOpSlot12(int entry)
{
  return (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)entry + 48))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00476F60) --------------------------------------------------------
signed int  FileSystem_FindMatchingMountIndex(int mount_table, const char **path_holder, int start_index)
{
  const char *entry_path;
  unsigned int entry_path_len;
  unsigned int requested_path_len;
  int current_index;
  int current_offset;
  int limit_offset;

  current_index = start_index;
  if ( start_index >= *(_DWORD *)(uintptr_t)(mount_table + 28) )
    return -1;
  current_offset = 16 * start_index;
  limit_offset = 16 * *(_DWORD *)(uintptr_t)(mount_table + 28);
  do
  {
    entry_path = Compat_StringHolderGetText((_DWORD *)(uintptr_t)(current_offset + *(_DWORD *)(uintptr_t)(mount_table + 20) + 4));
    if ( entry_path )
      entry_path_len = strlen(entry_path);
    else
      entry_path_len = 0;
    if ( !entry_path_len )
      return current_index;
    if ( *path_holder )
      requested_path_len = strlen(*path_holder);
    else
      requested_path_len = 0;
    if ( entry_path_len < requested_path_len )
    {
      if ( !memcmp(*path_holder, entry_path, entry_path_len) && (*path_holder)[entry_path_len] == 92 )
        return current_index;
    }
    else if ( entry_path_len == requested_path_len && !memcmp(*path_holder, entry_path, requested_path_len) )
    {
      return current_index;
    }
    current_offset += 16;
    ++current_index;
  }
  while ( current_offset < limit_offset );
  return -1;
}

//----- (004770B0) --------------------------------------------------------
int  FileSystem_ResolveAndInvokeForPath(int mount_table, int default_result, int (*callback)(void))
{
  int matched_index; // eax
  int callback_result; // eax
  int next_index; // eax
  const char *normalized_path; // [esp+0h] [ebp-18h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-14h]
  int entries_ptr CLASH95_UNUSED; // [esp+8h] [ebp-10h]

  normalized_path = 0;
  normalized_vtable = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&normalized_path)));
  normalized_vtable = ((int (**)())(&g_PathEntry_Vtable));
  FileSystem_NormalizePath(mount_table, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    entries_ptr = mount_table + 20;
    next_index = 0;
    while ( 1 )
    {
      matched_index = FileSystem_FindMatchingMountIndex(mount_table, &normalized_path, next_index);
      if ( matched_index == -1 )
        break;
      Compat_StringHolderDestructor(((_DWORD*)(&g_FileSystemStrippedPathHolderText)));
      FileSystem_StripMountPrefix(mount_table, matched_index, matched_index, (const char **)&g_FileSystemStrippedPathHolderText);
      callback_result = callback();
      if ( callback_result != default_result )
      {
        Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
        return callback_result;
      }
      next_index = matched_index + 1;
    }
  }
  Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
  return default_result;
}
// 54DD00: using guessed type int dword_54DD00;

CLASH95_INTERNAL int Compat_FileSystemQuery(int filesystem, const char *requested_path, int expected_result, int (*callback)(int))
{
  int callback_result;
  int current_entry;
  int next_entry;
  int entry_base;
  const char *normalized_path; // [esp+0h] [ebp-18h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-14h]

  normalized_path = 0;
  normalized_vtable = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderCopyText((_DWORD *)&normalized_path, requested_path);
  normalized_vtable = ((int (**)())(&g_PathEntry_Vtable));
  FileSystem_NormalizePath(filesystem, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    next_entry = 0;
    entry_base = *(_DWORD *)(uintptr_t)(filesystem + 20);
    while ( 1 )
    {
      current_entry = FileSystem_FindMatchingMountIndex(filesystem, &normalized_path, next_entry);
      if ( current_entry == -1 )
        break;
      Compat_StringHolderCopyText(((_DWORD*)(&g_FileSystemStrippedPathHolderText)), Compat_StringHolderGetText((_DWORD *)&normalized_path));
      FileSystem_StripMountPrefix(filesystem, current_entry, current_entry, (const char **)&g_FileSystemStrippedPathHolderText);
      callback_result = callback(entry_base + 16 * current_entry);
      if ( callback_result != expected_result )
      {
        Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
        return callback_result;
      }
      next_entry = current_entry + 1;
    }
  }
  Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
  return expected_result;
}

//----- (00477170) --------------------------------------------------------
int  FileSystem_TryOpenEntryCallback(int entry)
{
  int opened_query; // ebx

  opened_query = Compat_FileSystemOpenIfReady(*(_DWORD *)(uintptr_t)entry, g_FileSystemMountOpenMode);
  if ( !*(_DWORD *)(uintptr_t)(entry + 12) )
    return opened_query;
  if ( opened_query )
  {
    Output_WriteFormatted(entry + 12, g_FileSystemStrippedPathHolderText, *(_DWORD *)(uintptr_t)(entry + 12), (int)(intptr_t)aS_15, g_FileSystemStrippedPathHolderText);
    return opened_query;
  }
  Output_WriteFormatted(entry + 12, g_FileSystemStrippedPathHolderText, *(_DWORD *)(uintptr_t)(entry + 12), (int)(intptr_t)aS_2, g_FileSystemStrippedPathHolderText);
  return opened_query;
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (004771D0) --------------------------------------------------------
signed int  FileSystem_SetCurrentDirectoryFromPath(const char **file_system, int dir_path)
{
  _DWORD *fs_words;
  unsigned int path_len_with_nul;
  int colon_index;
  const char *root_text;
  unsigned int root_text_len;
  unsigned int normalized_text_len;
  const char *normalized_path; // [esp+0h] [ebp-20h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-1Ch]

  fs_words = (_DWORD *)(uintptr_t)file_system;
  if ( !(*((int (__thiscall **)(int))*file_system + 12))(dir_path) )
    return 0;
  normalized_path = 0;
  normalized_vtable = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderInitText((_DWORD *)&normalized_path, (const char *)(uintptr_t)(unsigned int)dir_path);
  normalized_vtable = ((int (**)())(&g_PathEntry_Vtable));
  FileSystem_NormalizePath((int)(intptr_t)file_system, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    path_len_with_nul = (unsigned int)strlen(normalized_path) + 1;
    if ( path_len_with_nul >= 2 && normalized_path[path_len_with_nul - 2] != 92 )
      Compat_StringHolderInsertTextChecked(&normalized_path, path_len_with_nul - 1, asc_5024C0);
    colon_index = Compat_StringHolderFindCharFrom(&normalized_path, 58, 0);
    Compat_StringHolderCopyText(fs_words + 1, normalized_path);
    root_text = Compat_StringHolderGetText(fs_words + 1);
    if ( root_text )
      root_text_len = (unsigned int)strlen(root_text);
    else
      root_text_len = 0;
    Compat_StringHolderRemoveRange((char **)(fs_words + 1), colon_index + 1, root_text_len, (int)(root_text_len - (unsigned int)(colon_index + 1)));
    normalized_text_len = (unsigned int)strlen(normalized_path);
    Compat_StringHolderRemoveRange(((char**)(&normalized_path)), 0, normalized_text_len, colon_index + 1);
    Compat_StringHolderCopyText(fs_words + 3, normalized_path);
    Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&normalized_path, 1);
    return 1;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&normalized_path, 1);
    return 0;
  }
}
// 477288: variable 'v5' is possibly undefined
// 4772A3: variable 'v7' is possibly undefined
// 4772B1: variable 'v9' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477300) --------------------------------------------------------
int  FileSystem_ResolveRelativeToCurrentDir(int file_system, int path_holder)
{
  int fs_saved; // edx
  int path_holder_saved; // [esp-10h] [ebp-14h]
  _DWORD joined_holder[4]; // [esp-Ch] [ebp-10h] BYREF

  fs_saved = file_system;
  if ( (g_FileSystem_CwdHolderInitFlag & 1) == 0 )
  {
    path_holder_saved = path_holder;
    g_FileSystem_CwdHolderInitFlag |= 1u;
    g_FS_ResolvedPathEntryHolder = 0;
    g_CurrentDirPathHolder_VtablePtr = (int)(intptr_t)&g_PathEntry_Vtable;
    CRT_RegisterFinalizableObject(0, file_system);
    path_holder = path_holder_saved;
  }
  Compat_StringHolderConstructJoined(joined_holder, ((_DWORD*)(intptr_t)(path_holder)), *(const char **)(uintptr_t)(fs_saved + 12));
  Compat_StringHolderDestructor(((_DWORD*)(&g_FS_ResolvedPathEntryHolder)));
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_holder, 1);
  return g_FS_ResolvedPathEntryHolder;
}
// 477312: variable 'v3' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EC94: using guessed type int (*off_50EC94)();
// 54DCF0: using guessed type int dword_54DCF0;
// 54DCF4: using guessed type int dword_54DCF4;
// 54DCF8: using guessed type char byte_54DCF8;

//----- (00477370) --------------------------------------------------------
int  FileSystem_AddMountEntry(int *mount_table, const CHAR *mount_path, const CHAR *log_file_path, DWORD mount)
{
  int archive_mode; // eax
  const char *path_text; // eax
  unsigned int path_len; // ecx
  _DWORD *entry_array; // ecx
  int entry_index; // edx
  _DWORD *entry_record; // ecx
  _DWORD *entry_path_holder; // ebx
  const char *normalized_path; // [esp+10h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+14h] [ebp-14h]
  const CHAR *log_path_saved; // [esp+18h] [ebp-10h]

  archive_mode = 0;
  log_path_saved = log_file_path;
  normalized_path = 0;
  vtable_ptr = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderInitText((_DWORD *)&normalized_path, mount_path);
  FileSystem_NormalizePath((int)(intptr_t)mount_table, &normalized_path);
  path_text = Compat_StringHolderGetText((_DWORD *)&normalized_path);
  if ( path_text && *path_text )
  {
    path_len = strlen(path_text);
    if ( path_len && path_text[path_len - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)&normalized_path, (int)(path_len - 1), (unsigned int)(uintptr_t)&normalized_path, 1);
    }
    if ( log_path_saved )
      archive_mode = IO_FOpen(log_path_saved, (unsigned __int8 *)aWt_0, 0, mount);
    entry_array = ((_DWORD*)(mount_table + 5));
    if ( mount_table[7] == mount_table[8] )
      PathEntryArray_GrowByDelta(mount_table + 5, mount_table[6]);
    entry_index = entry_array[2];
    entry_array[2] = entry_index + 1;
    entry_record = (_DWORD *)(uintptr_t)(16 * entry_index + *entry_array);
    *entry_record = mount;
    entry_path_holder = entry_record + 1;
    Compat_StringHolderCopyText(entry_path_holder, Compat_StringHolderGetText((_DWORD *)&normalized_path));
    entry_record[3] = archive_mode;
    Compat_FileSystemOnMounted((int)mount, mount_table);
  }
  return Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
}
// 477460: variable 'v9' is possibly undefined
// 477478: variable 'v10' is possibly undefined
// 4774A6: variable 'v14' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004774D0) --------------------------------------------------------
_DWORD * FileSystem_CreateEntryHandleWrapper(DWORD *file_system, int a2, int a3)
{
  _DWORD *result; // eax
  DWORD vtable; // ebp
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  _DWORD *wrapper; // esi
  _DWORD *opened_entry; // [esp+0h] [ebp-10h]

  result = (_DWORD *)(uintptr_t)(*(int (__fastcall **)(int, int))(uintptr_t)(*file_system + 12))(a2, a3);
  opened_entry = result;
  if ( result )
  {
    vtable = *file_system;
    if ( (*(int (**)(void))(uintptr_t)(*file_system + 16))() )
    {
      result = (_DWORD *)(uintptr_t)Mem_Alloc(16, v7, 10, vtable);
      wrapper = result;
      if ( result )
      {
        *result = v9;
        result[2] = ((_DWORD)(uintptr_t)(opened_entry));
        result[3] = v8;
        result[1] = j_Mem_Alloc(v9);
        return wrapper;
      }
    }
    else
    {
      (*(void (**)(void))(uintptr_t)(*file_system + 20))();
      return 0;
    }
  }
  return result;
}
// 47750D: variable 'v7' is possibly undefined
// 47751B: variable 'v9' is possibly undefined
// 477522: variable 'v8' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00477550) --------------------------------------------------------
int  FileSystem_AdvanceEntryEnumerator(int enumerator)
{
  int advance_result; // esi
  int v2; // ecx

  advance_result = (*(int (__fastcall **)(int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(enumerator + 8) + 20))(enumerator, *(_DWORD *)(uintptr_t)(enumerator + 4));
  (*(void (__fastcall **)(int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(v2 + 12) + 24))(v2, *(_DWORD *)(uintptr_t)(v2 + 4));
  return advance_result;
}
// 477566: variable 'v2' is possibly undefined

//----- (00477580) --------------------------------------------------------
int  Compat_FileSystemReleaseFileRecord(int file_system, int *record_ptr)
{
  int v3; // ecx
  int result; // eax

  (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)file_system + 20))(file_system, *record_ptr + 8);
  (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v3 + 20))(v3, *record_ptr + 12);
  result = *record_ptr;
  if ( *record_ptr )
  {
    Compat_FileSystemFreeFileRecordName();
    result = j__nfree_();
  }
  *record_ptr = 0;
  return result;
}
// 477591: variable 'v3' is possibly undefined

//----- (004775D0) --------------------------------------------------------
int Compat_FileSystemFreeFileRecordName(void)
{
  int v1; // ecx

  j_j__nfree_();
  return v1;
}
// 4775DB: variable 'v1' is possibly undefined

//----- (004775E0) --------------------------------------------------------
signed int  Compat_FileSystemVisitFile(DWORD *file_system, int a2, int a3)
{
  int v5; // ecx
  _DWORD *wrapper; // [esp+0h] [ebp-8h] BYREF

  wrapper = FileSystem_CreateEntryHandleWrapper(file_system, a2, a3);
  if ( !wrapper )
    return -1;
  while ( FileSystem_AdvanceEntryEnumerator((int)(intptr_t)wrapper) )
    ;
  Compat_FileSystemReleaseFileRecord((int)(intptr_t)file_system, (int *)&wrapper);
  return v5;
}
// 47760B: variable 'v5' is possibly undefined

//----- (00477620) --------------------------------------------------------
_DWORD * Compat_FileSystemReleaseMountedPaths(int mount_table)
{
  int entry_index; // ecx
  _DWORD *result; // eax
  _DWORD *entries_ptr; // esi
  int entry_offset; // edx

  entry_index = *(_DWORD *)(uintptr_t)(mount_table + 28) - 1;
  result = (_DWORD *)(uintptr_t)(mount_table + 20);
  if ( entry_index >= 0 )
  {
    entries_ptr = result;
    entry_offset = 16 * entry_index;
    do
      result = (_DWORD *)(uintptr_t)(*(int (__fastcall **)(int, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(entry_offset + *entries_ptr) + 40))(entry_index - 1, entry_offset - 16);
    while ( entry_offset >= 0 );
  }
  return result;
}
// 477638: variable 'v4' is possibly undefined
// 477640: variable 'v1' is possibly undefined

//----- (00477660) --------------------------------------------------------
int  Compat_FileSystemProcessDirectChildren(int (__thiscall ***file_system)(_DWORD), int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int entry_list; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]
  int v10 CLASH95_UNUSED; // [esp+8h] [ebp-10h]
  int v11 CLASH95_UNUSED; // [esp+10h] [ebp-8h]

  v11 = a2;
  entry_list = (**file_system)(0);
  v9 = (int)(intptr_t)file_system;
  v10 = v3;
  FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&entry_list);
  for ( ; entry_list; v4 = v5 + 1 )
  {
    if ( !(*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)entry_list + 12))() )
      break;
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)entry_list + 16))();
    FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&entry_list);
  }
  (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v9 + 4))(v4, entry_list);
  return v6;
}
// 477677: variable 'v3' is possibly undefined
// 4776A7: variable 'v5' is possibly undefined
// 4776B9: variable 'v4' is possibly undefined
// 4776BC: variable 'v6' is possibly undefined

//----- (004776D0) --------------------------------------------------------
int  Compat_FileSystemFindMountedPathById(int mount_table, int mount_id)
{
  int entry_index; // edx
  _DWORD *v4; // eax
  _DWORD *entries_ptr; // esi
  int entry_offset; // eax
  _DWORD *entry_record; // ecx

  entry_index = *(_DWORD *)(uintptr_t)(mount_table + 28) - 1;
  v4 = (_DWORD *)(uintptr_t)(mount_table + 20);
  if ( entry_index < 0 )
    return 0;
  entries_ptr = v4;
  entry_offset = 16 * entry_index;
  while ( 1 )
  {
    entry_record = (_DWORD *)(uintptr_t)(entry_offset + *entries_ptr);
    if ( mount_id == *entry_record )
      break;
    entry_offset -= 16;
    --entry_index;
    if ( entry_offset < 0 )
      return 0;
  }
  return entry_record[1];
}

//----- (00477710) --------------------------------------------------------
signed int  Compat_FileSystemWalkDirectoryTree(int (***file_system)(void), int dir_path, int base_path)
{
  const char *v4; // ecx
  int visit_result; // edi
  const char *v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int file_visit_failed; // ebx
  int v15; // ecx
  int enumerator; // [esp+0h] [ebp-48h] BYREF
  int (***file_system_saved)(void); // [esp+4h] [ebp-44h]
  int v18 CLASH95_UNUSED; // [esp+8h] [ebp-40h]
  _DWORD recurse_path_holder[2]; // [esp+Ch] [ebp-3Ch] BYREF
  const char *v20; // [esp+14h] [ebp-34h] BYREF
  int (**v21)(); // [esp+18h] [ebp-30h]
  const char *v22; // [esp+1Ch] [ebp-2Ch] BYREF
  int (**v23)(); // [esp+20h] [ebp-28h]
  const char *entry_name_holder; // [esp+24h] [ebp-24h] BYREF
  int (**v25)(); // [esp+28h] [ebp-20h]
  _DWORD file_path_holder[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  _DWORD subdir_path_holder[2]; // [esp+34h] [ebp-14h] BYREF
  _DWORD joined_path_holder[2]; // [esp+3Ch] [ebp-Ch] BYREF
  int dir_path_copy; // [esp+44h] [ebp-4h]

  dir_path_copy = dir_path;
  v20 = 0;
  v21 = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&v20)));
  v21 = ((int (**)())(&g_PathEntry_Vtable));
  Compat_StringHolderAppendText(&v20, asc_5024C5);
  v22 = v4;
  v23 = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&v22)));
  v23 = ((int (**)())(&g_PathEntry_Vtable));
  Compat_StringHolderAppendText(&v22, asc_5024C7);
  enumerator = (**file_system)();
  v18 = dir_path_copy;
  file_system_saved = file_system;
  FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&enumerator);
  visit_result = 0;
  if ( enumerator )
  {
    while ( (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 12))() )
    {
      (**(void (__thiscall ***)(_DWORD))(uintptr_t)enumerator)(0);
      entry_name_holder = v6;
      v25 = ((int (**)())(&g_CompatStringHolder_Vtable));
      Compat_StringHolderDestructor(((_DWORD*)(&entry_name_holder)));
      v25 = ((int (**)())(&g_PathEntry_Vtable));
      Compat_StringHolderConstructJoined(joined_path_holder, ((_DWORD*)(intptr_t)(v7)), entry_name_holder);
      if ( strcmp_(v8, ((_DWORD)(uintptr_t)(a__34))) && strcmp_(v9, ((_DWORD)(uintptr_t)(a___1))) )
      {
        if ( ((*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 4))() & 0x10) != 0 )
        {
          Compat_StringHolderConstructJoined(subdir_path_holder, ((_DWORD*)(intptr_t)(v10)), entry_name_holder);
          visit_result += Compat_FileSystemProcessDirectChildren((int (__thiscall ***)(_DWORD))file_system, v11);
          Compat_StringHolderScalarDeletingDtor((int)(intptr_t)subdir_path_holder, 1);
          (*file_system)[6]();
          Compat_StringHolderConstructJoined(recurse_path_holder, ((_DWORD*)(intptr_t)(dir_path_copy)), entry_name_holder);
          Compat_FileSystemWalkDirectoryTree((int (***)(void))(intptr_t)(int)(intptr_t)file_system, v12, base_path);
          Compat_StringHolderScalarDeletingDtor((int)(intptr_t)recurse_path_holder, 1);
        }
        else
        {
          file_visit_failed = *Compat_StringHolderConstructJoined(file_path_holder, ((_DWORD*)(intptr_t)(base_path)), entry_name_holder);
          LOBYTE(file_visit_failed) = Compat_FileSystemVisitFile((DWORD *)file_system, v15, file_visit_failed) == -1;
          Compat_StringHolderScalarDeletingDtor((int)(intptr_t)file_path_holder, 1);
          if ( (_BYTE)file_visit_failed )
          {
            Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_path_holder, 1);
            visit_result = -1;
            Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&entry_name_holder, 1);
            break;
          }
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)(intptr_t)joined_path_holder, 1);
      Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&entry_name_holder, 1);
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&enumerator);
      if ( !enumerator )
        break;
    }
  }
  (*file_system_saved)[1]();
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&v22, 1);
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&v20, 1);
  return visit_result;
}
// 47774A: variable 'v4' is possibly undefined
// 4777B9: variable 'v6' is possibly undefined
// 4777D8: variable 'v7' is possibly undefined
// 4777E5: variable 'v8' is possibly undefined
// 4777FA: variable 'v9' is possibly undefined
// 477823: variable 'v10' is possibly undefined
// 47782C: variable 'v11' is possibly undefined
// 477875: variable 'v12' is possibly undefined
// 477905: variable 'v15' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477950) --------------------------------------------------------
signed int __fastcall Compat_FileSystemWalkDirectoryEntries(int fileSystem, int a2)
{
  int (__fastcall ***v3)(_DWORD, const char *); // ecx
  int *v8; // ecx
  int *v9; // eax
  bool recurse_failed; // bl
  int callback_result; // ebx
  int v14; // esi
  int enumerator; // [esp+0h] [ebp-40h] BYREF
  int queryHandle; // [esp+4h] [ebp-3Ch]
  int v17 CLASH95_UNUSED; // [esp+8h] [ebp-38h]
  _DWORD file_path_holder[2]; // [esp+Ch] [ebp-34h] BYREF
  _DWORD subdir_path_holder[2]; // [esp+14h] [ebp-2Ch] BYREF
  const char *entry_name_holder; // [esp+1Ch] [ebp-24h] BYREF
  int (**v21)(); // [esp+20h] [ebp-20h]
  const char *pattern_holder; // [esp+24h] [ebp-1Ch] BYREF
  int (**v23)(); // [esp+28h] [ebp-18h]

  /*
   * asm sub_477950 (clash95.asm 00477950):
   *     mov  ecx, eax          ; ecx = fileSystem (the this-pointer)
   *     mov  edi, edx          ; edi = a2
   *     ... two Compat_StringHolder helpers (sub_471BF0, sub_471D10) -- both
   *     ... push/pop ecx, as does every virtual callee reached from here
   *     mov  ebx, [ecx]        ; ebx = fileSystem vtable
   *     mov  eax, ecx          ; this
   *     call dword ptr [ebx]   ; vtable[0](this, pattern) -> enumerator
   *     mov  [esp+40h+var_3C], ecx   ; queryHandle = the same this-pointer
   *   loc_477A7F:
   *     mov  ebx, [ecx] / mov edx, edi / mov eax, ecx / call [ebx+1Ch]
   *   loc_477AEB:
   *     mov  esi, [ecx] / ... / mov eax, ecx / call [esi+20h]
   * ecx is never reloaded, so v3/v4/v5/v8/v10 are all fileSystem; the
   * decompiler emitted them unassigned, which made the very first call a jump
   * through an uninitialised vtable pointer. The two strcmp_ calls likewise
   * take eax = entry_name_holder, not ecx.
   */
  v3 = (int (__fastcall ***)(_DWORD, const char *))(uintptr_t)fileSystem;
  v8 = (int *)(uintptr_t)fileSystem;
  pattern_holder = 0;
  v23 = ((int (**)())(&g_CompatStringHolder_Vtable));
  Compat_StringHolderDestructor(((_DWORD*)(&pattern_holder)));
  v23 = ((int (**)())(&g_PathEntry_Vtable));
  Compat_StringHolderAppendText(&pattern_holder, asc_5024CE);
  enumerator = (**v3)((_DWORD)(uintptr_t)v3, pattern_holder);
  queryHandle = fileSystem;
  v17 = 0;
  FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&enumerator);
  if ( enumerator )
  {
    while ( (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 12))() )
    {
      (**(void (***)(void))(uintptr_t)enumerator)();
      entry_name_holder = 0;
      v21 = ((int (**)())(&g_CompatStringHolder_Vtable));
      Compat_StringHolderDestructor(((_DWORD*)(&entry_name_holder)));
      v21 = ((int (**)())(&g_PathEntry_Vtable));
      if ( strcmp_((_DWORD)(uintptr_t)entry_name_holder, ((_DWORD)(uintptr_t)(a__35)))
        && strcmp_((_DWORD)(uintptr_t)entry_name_holder, ((_DWORD)(uintptr_t)(a___2))) )
      {
        if ( ((*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 4))() & 0x10) != 0 )
        {
          v9 = ((int*)(Compat_StringHolderConstructJoined(subdir_path_holder, ((_DWORD*)(intptr_t)((int)(intptr_t)v8)), entry_name_holder)));
          recurse_failed = Compat_FileSystemWalkDirectoryEntries(fileSystem, *v9) == -1;
          Compat_StringHolderScalarDeletingDtor((int)(intptr_t)subdir_path_holder, 1);
          if ( recurse_failed )
          {
            Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&entry_name_holder, 1);
            (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)queryHandle + 4))();
            Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&pattern_holder, 1);
            return -1;
          }
        }
        else
        {
          v14 = *v8;
          Compat_StringHolderConstructJoined(file_path_holder, ((_DWORD*)(intptr_t)((int)(intptr_t)v8)), entry_name_holder);
          (*(void (**)(void))(uintptr_t)(v14 + 32))();
          Compat_StringHolderScalarDeletingDtor((int)(intptr_t)file_path_holder, 1);
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&entry_name_holder, 1);
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)enumerator + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)(intptr_t)&enumerator);
      if ( !enumerator )
        break;
    }
  }
  callback_result = (*(int (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)fileSystem + 28))(fileSystem, a2);
  (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)queryHandle + 4))();
  Compat_StringHolderScalarDeletingDtor((int)(intptr_t)&pattern_holder, 1);
  return callback_result;
}
// 477991/47799C/477A32/477A3B/477A7F: v3/v4/v8/v10/v5 are all the ecx copy of
//   the fileSystem this-pointer; 4779FB/477A0D (v6/v7) are the eax argument of
//   strcmp_, i.e. entry_name_holder. Repaired above.
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477B20) --------------------------------------------------------
int __fastcall Compat_FileSystemCloseQuery(int a1, int query)
{
  int result; // eax

  result = query;
  if ( query )
    return (*(int (__cdecl **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)query + 20))(a1);
  return result;
}

//----- (00477B40) --------------------------------------------------------
int  Compat_FileSystemInvokeInnerHandleMethod(int wrapper, int method_arg)
{
  int v2; // ecx

  (*(void (__cdecl **)(int))(uintptr_t)(**(_DWORD **)(uintptr_t)(wrapper + 4) + 4))(method_arg);
  return v2;
}
// 477B4E: variable 'v2' is possibly undefined

//----- (00477B60) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot16(int entry)
{
  return (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)entry + 16))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477B80) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot32(int entry)
{
  return (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)entry + 32))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BA0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot24(int entry)
{
  return (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)entry + 24))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477BC0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot28(int entry)
{
  return (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)entry + 28))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BE0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot0(int (****mount_entry)(void))
{
  return (***mount_entry)();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477C00) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot0(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot0);
}

//----- (00477C20) --------------------------------------------------------
int  Compat_FileSystemForEachMountPrintSearchResult(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))FileSystem_TryOpenEntryCallback);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C40) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot16(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot16);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C60) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot32(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot32);
}

//----- (00477C80) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot24(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot24);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477CA0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot28(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot28);
}

//----- (00477CC0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeCallback(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))FileSystem_CallEntryOpSlot12);
}
