/* Generated from src/recovered/render/00401A40_render.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "render_internal.h"
#include "render_state.h"
#include "render_shared_state.h"
#include "../core/core_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00401A40) --------------------------------------------------------
__int16 Render_LoadResourceBackbuffer(void)
{
  Render_InitRecoveredVtableStorage();
  g_ActiveBlitCursor = (int)(intptr_t)g_NullBlitCursor_Vtable;
  Surface_ConstructBackbufferInstance((int)(intptr_t)&g_MainRenderDevice);
  CRT_RegisterFinalizableObject((int)(intptr_t)&g_RenderBackbufferScanlineBuffer, SCREEN_WIDTH);
  Render_ConstructSurfaceObject((int)(intptr_t)&g_RenderDeviceStorage, SCREEN_WIDTH, SCREEN_HEIGHT);
  CRT_RegisterFinalizableObject((int)(intptr_t)&g_RenderPaletteRemapBuffer, PALETTE_COLOR_COUNT);
  _wcpp_4_ctor_array__((int)(intptr_t)&g_DefaultPaletteTable, PALETTE_COLOR_COUNT);
  g_Render_BackgroundColorIndex = 0;
  return (unsigned __int8)Palette_BuildGrayscaleIdentityTable((int)(intptr_t)g_PaletteScratchSurfaceBuffer);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EF24: using guessed type int (*off_50EF24[5])();
// 51D4B8: using guessed type int dword_51D4B8;
// 51E265: using guessed type char byte_51E265;

//----- (00401AB0) --------------------------------------------------------
_BYTE * Palette_QuantizeChannelsInPlace(_BYTE *result, char bits_per_channel)
{
  _BYTE *palette_end; // ecx
  int channel_mask; // edx
  char blue_value; // bl

  palette_end = result + PALETTE_TABLE_BYTES;
  channel_mask = ~((1 << (8 - bits_per_channel)) - 1);
  do
  {
    *result &= channel_mask;
    result[1] &= channel_mask;
    blue_value = result[2];
    result += 4;
    *(result - 2) = channel_mask & blue_value;
  }
  while ( result != palette_end );
  return result;
}

//----- (00401AF0) --------------------------------------------------------
int  Palette_LoadFromQueryHandle(intptr_t palette_addr, intptr_t palette_name)
{
  int *palette_table;

  palette_table = (int *)(uintptr_t)palette_addr;
  if ( !palette_table )
    return 0;
  Compat_LoadPalCOLIntoTable(palette_table, (const char *)(uintptr_t)palette_name, 0);
  return (int)(uintptr_t)palette_table;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401B20) --------------------------------------------------------
int  Palette_ExpandRGBTripletsToTable(int palette_table, int query_handle, int context)
{
  int palette_offset;
  int write_ptr;
  int packed_rgb;
  unsigned __int8 red;
  unsigned __int8 green;
  unsigned __int8 blue;
  char palette_bytes[PALETTE_RGB_DATA_BYTES]; // [esp+0h] [ebp-310h]

  (void)context;
  Compat_QueryRead(query_handle, palette_bytes, PALETTE_RGB_READ_BYTES);
  write_ptr = palette_table;
  palette_offset = 0;
  while ( write_ptr != palette_table + PALETTE_TABLE_BYTES )
  {
    red = (unsigned __int8)palette_bytes[palette_offset];
    green = (unsigned __int8)palette_bytes[palette_offset + 1];
    blue = (unsigned __int8)palette_bytes[palette_offset + 2];
    packed_rgb = red | (green << 8) | (blue << 16);
    *(_DWORD *)(uintptr_t)write_ptr = packed_rgb;
    write_ptr += 4;
    palette_offset += 3;
  }
  return palette_offset;
}

//----- (00401BA0) --------------------------------------------------------
int  LoadPalPCX(int palette_table, const char *palette_name, DWORD context)
{
  char path[256]; // [esp+0h] [ebp-114h] BYREF
  int query_handle; // [esp+100h] [ebp-14h] BYREF

  (void)context;
  Debug_Log(63, (DWORD)(uintptr_t)palette_name, (DWORD)palette_table, (int)(intptr_t)a_loadpalpcxS0x);
  strcpy(path, aGfx_7);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, -PALETTE_RGB_READ_BYTES);
  Palette_ExpandRGBTripletsToTable(palette_table, query_handle, 0);
  return Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
}

//----- (00401C40) --------------------------------------------------------
int  LoadPalCOL(int palette_table, intptr_t palette_name_addr, DWORD context)
{
  const char *palette_name;
  char path[256]; // [esp+0h] [ebp-114h] BYREF
  int query_handle; // [esp+100h] [ebp-14h] BYREF

  palette_name = (const char *)(uintptr_t)palette_name_addr;
  Debug_Log(63, palette_table, context, (int)(intptr_t)a_loadpalcolS0x);
  strcpy(path, aGfx_0);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, 8);
  Palette_ExpandRGBTripletsToTable(palette_table, query_handle, 0);
  return Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
}

CLASH95_INTERNAL int Compat_LoadPalCOLIntoTable(int *palette_table, const char *palette_name, DWORD context)
{
  char path[256];
  unsigned char palette_bytes[PALETTE_RGB_DATA_BYTES];
  int query_handle;
  int palette_index;

  (void)context;
  if ( !palette_table || !palette_name )
    return 0;
  strcpy(path, aGfx_0);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, 8);
  Compat_QueryRead(query_handle, palette_bytes, sizeof(palette_bytes));
  for ( palette_index = 0; palette_index < PALETTE_COLOR_COUNT; ++palette_index )
  {
    unsigned char red = palette_bytes[3 * palette_index];
    unsigned char green = palette_bytes[3 * palette_index + 1];
    unsigned char blue = palette_bytes[3 * palette_index + 2];
    palette_table[palette_index] = red | (green << 8) | (blue << 16);
  }
  return Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
}

//----- (00401CE0) --------------------------------------------------------
int  Render_ApplyColorTripletBytes(int palette, unsigned __int8 *rgb_bytes)
{
  return Palette_QueryNearestColorIndex(palette, *rgb_bytes, rgb_bytes[1], rgb_bytes[2]);
}

//----- (00401D10) --------------------------------------------------------
int  Palette_BuildGrayscaleIdentityTable(int palette_table)
{
  int write_ptr; // edx
  int table_base; // ecx
  int i; // eax
  int packed_entry; // [esp+0h] [ebp-10h]

  write_ptr = _wcpp_4_ctor_array__(palette_table, PALETTE_COLOR_COUNT);
  table_base = write_ptr;
  for ( i = 0; i < PALETTE_COLOR_COUNT; ++i )
  {
    LOBYTE(packed_entry) = i;
    BYTE1(packed_entry) = i;
    HIWORD(packed_entry) = (unsigned __int8)i;
    write_ptr += 4;
    *(_DWORD *)(uintptr_t)(write_ptr - 4) = packed_entry;
  }
  return table_base;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401D60) --------------------------------------------------------
_BYTE * Str_CompactSkippingZeroBytes(_BYTE *result, _BYTE *src, unsigned int count)
{
  unsigned int i; // ecx

  for ( i = 0; i < count; ++result )
  {
    while ( !*src )
    {
      ++i;
      ++src;
      ++result;
      if ( i >= count )
        return result;
    }
    *result = *src;
    ++i;
    ++src;
  }
  return result;
}

//----- (00401D90) --------------------------------------------------------
void __cdecl __noreturn App_RequestQuit(int message_addr)
{
  const char *message;

  Render_BeginModeSwitch((_DWORD*)(&g_MainRenderDevice));
  message = (const char *)(uintptr_t)(unsigned int)message_addr;
  if ( message )
    snprintf(Text, sizeof(Text), "%s", message);
  else
    Text[0] = 0;
  ShowWindow(hWnd, 0);
  MessageBoxA(hWnd, Text, Caption, 0);
  App_Shutdown();
  CRT_ExitProcessWithFinalizers(1, 0, 0);
}

//----- (00401E00) --------------------------------------------------------
_DWORD * Render_ConstructSurfaceObject(int surface_addr, __int16 width, __int16 height)
{
  _DWORD *surface_body; // eax
  _DWORD *surface; // eax

  surface_body = (_DWORD *)(uintptr_t)(surface_addr + 8);
  *(surface_body - 1) = 0;
  *((_WORD *)surface_body - 4) = width;
  *((_WORD *)surface_body - 3) = height;
  surface = Surface_Construct(surface_body);
  surface[44] = (_DWORD)(uintptr_t)(g_Surface_BaseVtable);
  return surface - 2;
}
// 50EDD4: using guessed type int (*off_50EDD4[5])();

//----- (00401E30) --------------------------------------------------------
int  Render_ClearGameScreen(_DWORD *surface)
{
  return Render_FillRect(surface, (_DWORD*)(&g_MainRenderDevice), 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
}

//----- (00401E60) --------------------------------------------------------
int  Surface_ClearWholeArea(unsigned __int16 *surface)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, int))(uintptr_t)(*((_DWORD *)surface + 46) + 32))(0, 0, surface[1] * *surface);
}

//----- (00401E90) --------------------------------------------------------
int  Render_FillClippedScanlines(int surface, unsigned int pixel_count)
{
  unsigned __int8 v3; // cl
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // eax
  unsigned int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int write_cursor; // [esp+4h] [ebp-14h]
  unsigned __int8 fill_color; // [esp+8h] [ebp-10h]

  write_cursor = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 8))();
  fill_color = v3;
  do
  {
    if ( pixel_count > (*(int (__thiscall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(pixel_count) )
      (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
    v4 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 8))();
    if ( v5 > v4 )
      v5 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 8))();
    v6 = (*(int (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(v5);
    if ( v7 > v6 )
      v7 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
    (*(void (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 16))(v7);
    (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 16))();
    memset_(v8, fill_color);
    (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 12))(v9, v9);
    (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v10, v10);
    (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v11, v11);
    pixel_count -= v12;
  }
  while ( pixel_count );
  return (**(int (***)(void))(uintptr_t)write_cursor)();
}
// 401EAD: variable 'v3' is possibly undefined
// 401ED7: variable 'v5' is possibly undefined
// 401EF2: variable 'v7' is possibly undefined
// 401F34: variable 'v8' is possibly undefined
// 401F3F: variable 'v9' is possibly undefined
// 401F4F: variable 'v10' is possibly undefined
// 401F5F: variable 'v11' is possibly undefined
// 401F62: variable 'v12' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 51D4B8: using guessed type int dword_51D4B8;

//----- (00401FA0) --------------------------------------------------------
int  Render_BlitRectViaVirtualSurfaces(
        int source_surface,
        int dest_surface,
        int src_top,
        __int16 src_left,
        __int16 src_right,
        unsigned __int16 src_bottom,
        unsigned __int16 dest_x,
        __int16 a8 CLASH95_UNUSED)
{
  int read_cursor; // eax
  int v11; // ecx
  int write_cursor; // ebx
  int i; // edi
  __int64 v14; // rax
  int v15; // ecx
  int v16; // edi
  int *v17; // ecx
  int v18; // edi
  int (__fastcall ***v19)(_DWORD, int); // ecx
  unsigned __int16 span_width; // [esp+0h] [ebp-14h]

  read_cursor = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(source_surface + 184) + 4))();
  write_cursor = (*(int (__fastcall **)(int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)(dest_surface + 184) + 8))(read_cursor, dest_x);
  span_width = src_right - src_left + 1;
  while ( 1 )
  {
    src_top += 2;
    if ( (unsigned __int16)src_top > src_bottom )
      break;
    for ( i = 0; i < span_width / 2; ++i )
    {
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v11 + 16))();
      v14 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 16))();
      *(_BYTE *)v14 = *(_BYTE *)(uintptr_t)HIDWORD(v14);
      (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v15 + 12))(v15, 2);
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 12))();
    }
    v16 = *(_DWORD *)(uintptr_t)write_cursor;
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)write_cursor + 4))();
    (*(void (**)(void))(uintptr_t)(v16 + 12))();
    v18 = *v17;
    (*(void (**)(void))(uintptr_t)(*v17 + 4))();
    (*(void (**)(void))(uintptr_t)(v18 + 12))();
  }
  (**(void (***)(void))(uintptr_t)write_cursor)();
  return (**v19)((_DWORD)(uintptr_t)v19, 2);
}
// 402018: variable 'v11' is possibly undefined
// 40202C: variable 'v15' is possibly undefined
// 402056: variable 'v17' is possibly undefined
// 402081: variable 'v19' is possibly undefined

//----- (004020A0) --------------------------------------------------------
int  Render_LoadPCXImage(int surface, char *file_name, int transparent, uintptr_t palette_out_addr)
{
  unsigned char *file_buffer;
  unsigned char *decode_cursor;
  unsigned char *surface_pixels;
  unsigned char *palette_bytes;
  unsigned int pixel_index;
  unsigned int pixel_count;
  unsigned int file_size;
  unsigned int file_offset;
  unsigned int run_length;
  unsigned int palette_offset;
  unsigned int *palette_out;
  unsigned int packed_rgb;
  unsigned char value;
  unsigned short width;
  unsigned short height;
  int query_handle;
  char path[256];

  Debug_Log(transparent, 0, (DWORD)(intptr_t)file_name, (int)(intptr_t)a_loadpcxS0x08x);
  if ( !surface || !file_name )
    return 0;

  strcpy(path, aGfx_8);
  strcat(path, file_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  if ( !query_handle )
    return 0;

  file_size = (unsigned int)IO_QueryVTableStreamSize(query_handle);
  if ( !file_size )
  {
    Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
    return 0;
  }

  file_buffer = (unsigned char *)(uintptr_t)(unsigned int)nmalloc_(file_size, 4);
  if ( !file_buffer )
  {
    Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
    return 0;
  }

  Compat_QueryRead(query_handle, file_buffer, file_size);
  Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
  if ( file_size < 128 )
  {
    Compat_FreeLow32Bytes((int)(uintptr_t)file_buffer);
    return 0;
  }

  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(surface + 4);
  if ( !surface_pixels )
  {
    Compat_FreeLow32Bytes((int)(uintptr_t)file_buffer);
    return 0;
  }

  width = *(unsigned short *)(file_buffer + 8) + 1;
  height = *(unsigned short *)(file_buffer + 10) + 1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[pcx] load path=%s size=%u header=%02x/%02x/%02x dims=%ux%u target=%08x target_dims=%ux%u transparent=%d palette_out=%d\n",
      path,
      file_size,
      file_buffer[0],
      file_buffer[1],
      file_buffer[2],
      width,
      height,
      surface,
      *(unsigned __int16 *)(uintptr_t)surface,
      *((unsigned __int16 *)(uintptr_t)surface + 1),
      transparent,
      palette_out_addr != 0);
  pixel_count = (unsigned int)width * (unsigned int)height;
  decode_cursor = file_buffer + 128;
  file_offset = (unsigned int)(decode_cursor - file_buffer);
  pixel_index = 0;
  while ( pixel_index < pixel_count && file_offset < file_size )
  {
    value = *decode_cursor++;
    ++file_offset;
    if ( (value & 0xC0) == 0xC0 )
    {
      if ( file_offset >= file_size )
        break;
      run_length = (unsigned int)(value & 0x3F);
      value = *decode_cursor++;
      ++file_offset;
      if ( !transparent || value )
        memset(surface_pixels + pixel_index, value, run_length);
      pixel_index += run_length;
    }
    else
    {
      if ( !transparent || value )
        surface_pixels[pixel_index] = value;
      ++pixel_index;
    }
  }

  if ( file_offset < file_size )
  {
    ++decode_cursor;
    ++file_offset;
  }
  if ( palette_out_addr && file_offset + PALETTE_RGB_DATA_BYTES <= file_size )
  {
    palette_out = (unsigned int *)palette_out_addr;
    palette_bytes = decode_cursor;
    for ( palette_offset = 0; palette_offset != PALETTE_RGB_DATA_BYTES; palette_offset += 3 )
    {
      packed_rgb = palette_bytes[palette_offset]
                 | (palette_bytes[palette_offset + 1] << 8)
                 | (palette_bytes[palette_offset + 2] << 16);
      if ( !transparent || packed_rgb )
        *palette_out = packed_rgb;
      ++palette_out;
    }
  }

  Compat_FreeLow32Bytes((int)(uintptr_t)file_buffer);
  return 0;
}

//----- (004024E0) --------------------------------------------------------
int  Render_FillRect(
        _DWORD *source_surface,
        _DWORD *dest_surface,
        int src_top,
        int src_left,
        unsigned __int16 src_right,
        unsigned __int16 src_bottom,
        unsigned __int16 dest_x,
        unsigned __int16 dest_y)
{
  _DWORD *src_resolved; // esi
  _DWORD *dest_resolved; // edi
  int v10 CLASH95_UNUSED; // ecx
  void (**v11)(void); // ecx
  __int64 v12; // rax
  int v13; // ecx
  int v14; // eax
  unsigned int chunk_length; // ebx
  const void *copy_source; // esi
  unsigned int v17; // ecx
  int v18; // ecx
  int v19 CLASH95_UNUSED; // ecx
  __int64 v20 CLASH95_UNUSED; // rax
  int v21 CLASH95_UNUSED; // ecx
  __int64 v22 CLASH95_UNUSED; // rax
  int src_view_handle; // ebx
  int dest_view_handle; // eax
  int (__fastcall **v25)(_DWORD, int); // ecx
  void *copy_dest; // [esp-4h] [ebp-114h]
  _DWORD v28[49] CLASH95_UNUSED; // [esp+0h] [ebp-110h] BYREF
  int v29; // [esp+C4h] [ebp-4Ch]
  int span_width; // [esp+C8h] [ebp-48h]
  int rows_remaining; // [esp+CCh] [ebp-44h]
  void (***v32)(void); // [esp+D0h] [ebp-40h]
  void (***v33)(void); // [esp+D4h] [ebp-3Ch]
  int src_right_saved; // [esp+D8h] [ebp-38h]
  void (***dest_cursor)(void); // [esp+DCh] [ebp-34h]
  int (***src_cursor)(void); // [esp+E0h] [ebp-30h]
  int src_bottom_saved; // [esp+E4h] [ebp-2Ch]
  int span_height; // [esp+E8h] [ebp-28h]
  int v39 CLASH95_UNUSED; // [esp+ECh] [ebp-24h]
  unsigned int row_width; // [esp+F0h] [ebp-20h]
  int v41 CLASH95_UNUSED; // [esp+F4h] [ebp-1Ch]
  int v42; // [esp+F8h] [ebp-18h]
  int v43; // [esp+FCh] [ebp-14h]
  unsigned int pixels_remaining; // [esp+100h] [ebp-10h]
  int v45; // [esp+104h] [ebp-Ch]
  int src_left_saved; // [esp+108h] [ebp-8h]
  int src_top_saved; // [esp+10Ch] [ebp-4h]
  _DWORD *temp_surface;

  source_surface = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)source_surface;
  dest_surface = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)dest_surface;
  src_resolved = source_surface;
  dest_resolved = dest_surface;
  src_left_saved = src_left;
  src_top_saved = src_top;
  if ( !source_surface )
    src_resolved = (_DWORD*)(&g_MainRenderDevice);
  if ( !dest_surface )
    dest_resolved = (_DWORD*)(&g_MainRenderDevice);
  src_resolved = RenderSurface_ResolvePrimaryCompanion(src_resolved);
  dest_resolved = RenderSurface_ResolvePrimaryCompanion(dest_resolved);
  src_right_saved = src_right;
  span_width = src_right - (unsigned __int16)src_left_saved + 1;
  src_bottom_saved = src_bottom;
  v10 = src_resolved[46];
  span_height = src_bottom - (unsigned __int16)src_top_saved + 1;
  if ( RenderSurface_IsLinearSoftware(src_resolved) && RenderSurface_IsLinearSoftware(dest_resolved) )
  {
    unsigned char *source_pixels;
    unsigned char *destination_pixels;
    int source_x;
    int source_y;
    int destination_x;
    int destination_y;
    int source_width;
    int source_height;
    int destination_width;
    int destination_height;
    int source_pitch;
    int destination_pitch;
    int copy_width;
    int copy_height;
    int row_index;

    source_pixels = (unsigned char *)(uintptr_t)(unsigned int)src_resolved[1];
    destination_pixels = (unsigned char *)(uintptr_t)(unsigned int)dest_resolved[1];
    if ( !source_pixels || !destination_pixels )
      return 0;
    source_x = (short)(unsigned __int16)src_left;
    source_y = (short)(unsigned __int16)src_top_saved;
    destination_x = (short)dest_x;
    destination_y = (short)dest_y;
    source_pitch = *(unsigned __int16 *)src_resolved;
    destination_pitch = *(unsigned __int16 *)dest_resolved;
    source_width = source_pitch;
    source_height = HIWORD(src_resolved[0]);
    destination_width = destination_pitch;
    destination_height = HIWORD(dest_resolved[0]);
    copy_width = span_width;
    copy_height = span_height;
    if ( copy_width <= 0 || copy_height <= 0 )
      return 0;
    if ( source_x < 0 )
    {
      destination_x -= source_x;
      copy_width += source_x;
      source_x = 0;
    }
    if ( source_y < 0 )
    {
      destination_y -= source_y;
      copy_height += source_y;
      source_y = 0;
    }
    if ( destination_x < 0 )
    {
      source_x -= destination_x;
      copy_width += destination_x;
      destination_x = 0;
    }
    if ( destination_y < 0 )
    {
      source_y -= destination_y;
      copy_height += destination_y;
      destination_y = 0;
    }
    if ( source_x >= source_width || source_y >= source_height
      || destination_x >= destination_width || destination_y >= destination_height )
    {
      return 0;
    }
    if ( source_x + copy_width > source_width )
      copy_width = source_width - source_x;
    if ( destination_x + copy_width > destination_width )
      copy_width = destination_width - destination_x;
    if ( source_y + copy_height > source_height )
      copy_height = source_height - source_y;
    if ( destination_y + copy_height > destination_height )
      copy_height = destination_height - destination_y;
    if ( copy_width <= 0 || copy_height <= 0 )
      return 0;
    for ( row_index = 0; row_index < copy_height; ++row_index )
      qmemcpy(
        destination_pixels + (destination_y + row_index) * destination_pitch + destination_x,
        source_pixels + (source_y + row_index) * source_pitch + source_x,
        copy_width);
    return 0;
  }
  src_view_handle = RenderSurface_InvokeSlot60(src_resolved);
  dest_view_handle = RenderSurface_InvokeSlot64(dest_resolved);
  if ( src_view_handle && dest_view_handle )
  {
    v29 = src_bottom_saved + 1;
    Surface_SetSrcRect((_DWORD *)(uintptr_t)(unsigned int)src_view_handle, 0, src_bottom_saved + 1, (unsigned __int16)src_left_saved, src_right_saved + 1);
    v29 = dest_y + span_height;
    Surface_SetDestRect((_DWORD *)(uintptr_t)(unsigned int)src_view_handle, 0, v29, dest_x, dest_x + span_width);
    return RenderHandle_InvokeCopyDispatch(src_view_handle, dest_view_handle);
  }
  else if ( g_MousePresentAtStartup && (src_resolved == (_DWORD *)&g_MainRenderDevice || dest_resolved == (_DWORD *)&g_MainRenderDevice) )
  {
    if ( (src_resolved == (_DWORD *)&g_MainRenderDevice && !src_resolved[47]) || (dest_resolved == (_DWORD *)&g_MainRenderDevice && !dest_resolved[47]) )
      return 0;
    temp_surface = (_DWORD *)(uintptr_t)Mem_Alloc(196, 0, 0, 0);
    if ( !temp_surface )
      return 0;
    Render_ConstructScratchSurface((int)(intptr_t)temp_surface, span_width, 1u, span_height);
    Render_FillRect(src_resolved, temp_surface, (unsigned __int16)src_top_saved, (unsigned __int16)src_left_saved, src_right, src_bottom, 0, 0);
    Render_FillRect(temp_surface, dest_resolved, 0, 0, LOWORD(temp_surface[0]) - 1, HIWORD(temp_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(temp_surface, 2);
  }
  else
  {
    dest_cursor = (void (***)(void))(uintptr_t)(*(int (**)(void))(uintptr_t)(dest_resolved[46] + 8))();
    src_cursor = (int (***)(void))(uintptr_t)(*(int (**)(void))(uintptr_t)(src_resolved[46] + 4))();
    rows_remaining = span_height;
    v11 = *dest_cursor;
    row_width = span_width;
    v12 = ((__int64 (*)(void))v11[1])();
    v42 = v12 - span_width;
    v13 = *(_DWORD *)(uintptr_t)HIDWORD(v12);
    v43 = HIDWORD(v12);
    v39 = (*(int (**)(void))(uintptr_t)(v13 + 4))() - span_width;
    v14 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 4))();
    v32 = dest_cursor;
    v41 = v14 - span_width;
    while ( --rows_remaining != -1 )
    {
      pixels_remaining = row_width;
      v33 = v32;
      v45 = v43;
      do
      {
        chunk_length = pixels_remaining;
        if ( (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v45 + 8))() < pixels_remaining )
          chunk_length = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v45 + 8))();
        if ( chunk_length > ((int (*)(void))(*v33)[2])() )
          chunk_length = ((int (*)(void))(*v33)[2])();
        if ( chunk_length > (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))() )
          chunk_length = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
        (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
        copy_source = (const void *)(uintptr_t)(*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v45 + 16))();
        copy_dest = (void *)(uintptr_t)((int (__thiscall *)(unsigned int))(*v33)[4])(chunk_length);
        qmemcpy(copy_dest, copy_source, v17);
        (*v33)[3]();
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v45 + 12))();
        (*(void (__fastcall **)(unsigned int, unsigned int))(uintptr_t)(g_ActiveBlitCursor + 12))(pixels_remaining, chunk_length);
        pixels_remaining = v18 - chunk_length;
      }
      while ( v18 != chunk_length );
      ((void (__fastcall *)(_DWORD, int))(*v32)[3])(0, v42);
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 12))();
      (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 12))();
    }
    (**dest_cursor)();
    return (**src_cursor)();
  }
}
// 40269C: variable 'v17' is possibly undefined
// 4026D5: variable 'v18' is possibly undefined
// 40277E: variable 'v25' is possibly undefined
// 51D018: using guessed type int g_MousePresentAtStartup;
// 51D4B8: using guessed type int dword_51D4B8;

//----- (00402850) --------------------------------------------------------
int  Render_BlitSurfaceRect(
        _DWORD *source_surface,
        _DWORD *dest_surface,
        int src_top,
        int src_left,
        unsigned __int16 src_right,
        unsigned __int16 src_bottom,
        unsigned __int16 dest_x,
        unsigned __int16 dest_y)
{
  _DWORD *src_resolved; // esi
  _DWORD *dest_resolved; // edi
  int src_backend CLASH95_UNUSED; // edx
  int *v11; // ecx
  int v12; // ebx
  __int64 v13; // rax
  int v14; // ecx
  int v15; // ecx
  unsigned int v16; // eax
  unsigned int v17; // ecx
  unsigned int v18; // eax
  unsigned int v19; // ecx
  unsigned int v20; // eax
  unsigned int v21; // ecx
  __int64 v22; // rax
  unsigned int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int colorkey_surface; // eax
  int v29; // ecx
  int v30; // ecx
  _DWORD *src_rect_surface; // eax
  int v32; // ecx
  _DWORD *dest_rect_surface; // eax
  int v34; // ecx
  int src_blit_surface; // eax
  int dest_backend; // edx
  int dest_target_surface; // eax
  _DWORD scratch_surface[51]; // [esp+0h] [ebp-110h] BYREF
  int blit_interface; // [esp+CCh] [ebp-44h]
  int span_height; // [esp+D0h] [ebp-40h]
  int v42 CLASH95_UNUSED; // [esp+D4h] [ebp-3Ch]
  int v43; // [esp+D8h] [ebp-38h]
  int pixels_remaining; // [esp+DCh] [ebp-34h]
  int (***src_cursor)(void); // [esp+E0h] [ebp-30h]
  int src_top_u16; // [esp+E4h] [ebp-2Ch]
  int src_right_saved; // [esp+E8h] [ebp-28h]
  void (***dest_cursor)(void); // [esp+ECh] [ebp-24h]
  int rows_remaining; // [esp+F0h] [ebp-20h]
  int span_width; // [esp+F4h] [ebp-1Ch]
  int v51 CLASH95_UNUSED; // [esp+F8h] [ebp-18h]
  int row_width; // [esp+FCh] [ebp-14h]
  int i; // [esp+100h] [ebp-10h]
  int v54; // [esp+104h] [ebp-Ch]
  int src_left_saved; // [esp+108h] [ebp-8h]
  int src_top_saved; // [esp+10Ch] [ebp-4h]

  source_surface = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)source_surface;
  dest_surface = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)dest_surface;
  src_resolved = source_surface;
  dest_resolved = dest_surface;
  src_left_saved = src_left;
  src_top_saved = src_top;
  if ( !source_surface )
    src_resolved = (_DWORD*)(&g_MainRenderDevice);
  if ( !dest_surface )
    dest_resolved = (_DWORD*)(&g_MainRenderDevice);
  src_resolved = RenderSurface_ResolvePrimaryCompanion(src_resolved);
  dest_resolved = RenderSurface_ResolvePrimaryCompanion(dest_resolved);
  src_right_saved = src_right;
  span_width = src_right - (unsigned __int16)src_left_saved + 1;
  src_top_u16 = (unsigned __int16)src_top_saved;
  src_backend = src_resolved[46];
  span_height = src_bottom - (unsigned __int16)src_top_saved + 1;
  /*
   * 0x00402850 is the register-allocation twin of Render_FillRect
   * (0x004024E0): identical prologue, identical slot +60/+64 probe, identical
   * blit-cursor fallback - with exactly ONE semantic difference in the
   * software path.  Where Render_FillRect's inner run copy is
   * "rep movsd / rep movsb" (clash95.asm 2494-2502, an opaque copy),
   * 0x00402850 calls Str_CompactSkippingZeroBytes / sub_401D60
   * (clash95.asm 2846), which advances the destination cursor without writing
   * wherever the SOURCE byte is 0.  So Render_FillRect = opaque rect copy,
   * Render_BlitSurfaceRect = the same rect blit with palette index 0 as the
   * transparent key.
   *
   * The port already replaced Render_FillRect's 32-bit blit-cursor machinery
   * with a native linear-software seam; 0x00402850 kept the raw decompile,
   * whose "(*(int (**)(void))(uintptr_t)(table + 60))()" loads an 8-byte
   * function pointer out of the recovered 4-byte-entry method tables
   * (g_Surface_Vtable et al are int[]) and jumps into two packed slot values.
   * That is a guaranteed SIGSEGV the first time this function is actually
   * reached - observed as rax=0x40b0310040b022 when the restored world-map
   * top-menu-bar strip blit finally called it.  Give it the same seam, with
   * the transparent skip the original's copy helper performs.
   */
  if ( RenderSurface_IsLinearSoftware(src_resolved) && RenderSurface_IsLinearSoftware(dest_resolved) )
  {
    unsigned char *source_pixels;
    unsigned char *destination_pixels;
    int source_x;
    int source_y;
    int destination_x;
    int destination_y;
    int source_width;
    int source_height;
    int destination_width;
    int destination_height;
    int source_pitch;
    int destination_pitch;
    int copy_width;
    int copy_height;
    int row_index;
    int column_index;

    source_pixels = (unsigned char *)(uintptr_t)(unsigned int)src_resolved[1];
    destination_pixels = (unsigned char *)(uintptr_t)(unsigned int)dest_resolved[1];
    if ( !source_pixels || !destination_pixels )
      return 0;
    source_x = (short)(unsigned __int16)src_left_saved;
    source_y = (short)(unsigned __int16)src_top_saved;
    destination_x = (short)dest_x;
    destination_y = (short)dest_y;
    source_pitch = *(unsigned __int16 *)src_resolved;
    destination_pitch = *(unsigned __int16 *)dest_resolved;
    source_width = source_pitch;
    source_height = HIWORD(src_resolved[0]);
    destination_width = destination_pitch;
    destination_height = HIWORD(dest_resolved[0]);
    copy_width = span_width;
    copy_height = span_height;
    if ( copy_width <= 0 || copy_height <= 0 )
      return 0;
    if ( source_x < 0 )
    {
      destination_x -= source_x;
      copy_width += source_x;
      source_x = 0;
    }
    if ( source_y < 0 )
    {
      destination_y -= source_y;
      copy_height += source_y;
      source_y = 0;
    }
    if ( destination_x < 0 )
    {
      source_x -= destination_x;
      copy_width += destination_x;
      destination_x = 0;
    }
    if ( destination_y < 0 )
    {
      source_y -= destination_y;
      copy_height += destination_y;
      destination_y = 0;
    }
    if ( source_x >= source_width || source_y >= source_height
      || destination_x >= destination_width || destination_y >= destination_height )
    {
      return 0;
    }
    if ( source_x + copy_width > source_width )
      copy_width = source_width - source_x;
    if ( destination_x + copy_width > destination_width )
      copy_width = destination_width - destination_x;
    if ( source_y + copy_height > source_height )
      copy_height = source_height - source_y;
    if ( destination_y + copy_height > destination_height )
      copy_height = destination_height - destination_y;
    if ( copy_width <= 0 || copy_height <= 0 )
      return 0;
    for ( row_index = 0; row_index < copy_height; ++row_index )
    {
      const unsigned char *source_row;
      unsigned char *destination_row;

      source_row = source_pixels + (source_y + row_index) * source_pitch + source_x;
      destination_row = destination_pixels + (destination_y + row_index) * destination_pitch + destination_x;
      for ( column_index = 0; column_index < copy_width; ++column_index )
      {
        if ( source_row[column_index] )
          destination_row[column_index] = source_row[column_index];
      }
    }
    return 0;
  }
  /*
   * Original sub_402850 (clash95.asm 2731-2741):
   *   mov edx,[esi+0B8h] / mov eax,esi / call dword ptr [edx+3Ch]
   *   test eax,eax / jz  loc_4028C8
   *   mov edx,[edi+0B8h] / mov eax,edi / call dword ptr [edx+40h]
   *   test eax,eax / jnz loc_402A51
   * i.e. surface method-table slots +60 (src) and +64 (dest), each called
   * with the surface itself as the `this` pointer.  The raw decompile turned
   * both into `(*(int (**)(void))(uintptr_t)(table + N))()`, which loads an
   * 8-byte function pointer out of the recovered 4-byte-entry method tables
   * (`g_Surface_Vtable` et al are `int[]`) and jumps to two packed slot
   * values - a guaranteed SIGSEGV, observed as rax=0x40b0310040b022 the first
   * time this function was actually reached.  Route through the sanctioned
   * RenderSurface_InvokeSlot60/64 seams, the same repair applied to the other
   * 32-bit surface-vtable call sites.
   */
  if ( RenderSurface_InvokeSlot60(src_resolved) && RenderSurface_InvokeSlot64(dest_resolved) )
  {
    colorkey_surface = (*(int (**)(void))(uintptr_t)(src_resolved[46] + 60))();
    Surface_SetSrcColorKey(colorkey_surface, 0, v29);
    src_rect_surface = (_DWORD *)(uintptr_t)(*(int (__thiscall **)(int))(uintptr_t)(src_resolved[46] + 60))(v30 + 1);
    Surface_SetSrcRect(src_rect_surface, src_top_u16, v32, (unsigned __int16)src_left_saved, src_right_saved + 1);
    scratch_surface[49] = dest_x;
    scratch_surface[50] = dest_y;
    dest_rect_surface = (_DWORD *)(uintptr_t)(*(int (__thiscall **)(int))(uintptr_t)(src_resolved[46] + 60))(dest_y + span_height);
    Surface_SetDestRect(dest_rect_surface, dest_y, v34, dest_x, span_width + dest_x);
    src_blit_surface = (*(int (**)(void))(uintptr_t)(src_resolved[46] + 60))();
    dest_backend = dest_resolved[46];
    blit_interface = *(_DWORD *)(uintptr_t)(src_blit_surface + 172);
    dest_target_surface = (*(int (**)(void))(uintptr_t)(dest_backend + 64))();
    return (*(int (__fastcall **)(int, _DWORD))(uintptr_t)(blit_interface + 8))(dest_target_surface, dest_x);
  }
  else if ( g_MousePresentAtStartup && (src_resolved == (_DWORD *)&g_MainRenderDevice || dest_resolved == (_DWORD *)&g_MainRenderDevice) )
  {
    Render_ConstructScratchSurface((int)(intptr_t)scratch_surface, span_width, 1u, span_height);
    Render_FillRect(src_resolved, scratch_surface, (unsigned __int16)src_top_saved, (unsigned __int16)src_left_saved, src_right, src_bottom, 0, 0);
    Render_BlitSurfaceRect(scratch_surface, dest_resolved, 0, 0, LOWORD(scratch_surface[0]) - 1, HIWORD(scratch_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(scratch_surface, 0);
  }
  else
  {
    dest_cursor = (void (***)(void))(uintptr_t)(*(int (**)(void))(uintptr_t)(dest_resolved[46] + 8))();
    src_cursor = (int (***)(void))(uintptr_t)(*(int (__fastcall **)(void (***)(void), _DWORD))(uintptr_t)(src_resolved[46] + 4))(dest_cursor, (unsigned __int16)src_left_saved);
    rows_remaining = span_height;
    v12 = *v11;
    row_width = span_width;
    v13 = ((__int64 (__fastcall *)(int *, int (***)(void)))(uintptr_t)*(_DWORD *)(uintptr_t)(v12 + 4))(v11, src_cursor);
    v54 = v14;
    v15 = *(_DWORD *)(uintptr_t)HIDWORD(v13);
    v42 = v13 - span_width;
    v43 = HIDWORD(v13);
    v51 = (*(int (**)(void))(uintptr_t)(v15 + 4))() - span_width;
    for ( i = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 4))() - span_width;
          --rows_remaining != -1;
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, i) )
    {
      pixels_remaining = row_width;
      do
      {
        v16 = (*(int (__thiscall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 8))(pixels_remaining);
        if ( v16 < v17 )
          v17 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 8))();
        v18 = (*(int (__fastcall **)(unsigned int))(uintptr_t)(*(_DWORD *)(uintptr_t)v54 + 8))(v17);
        if ( v19 > v18 )
          v19 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v54 + 8))();
        v20 = (*(int (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(v19);
        if ( v21 > v20 )
          v21 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
        (*(void (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 16))(v21);
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 16))();
        v22 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v54 + 16))();
        Str_CompactSkippingZeroBytes((_BYTE *)v22, (_BYTE *)(uintptr_t)HIDWORD(v22), v23);
        (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v54 + 12))(v24, v24);
        (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 12))(v25, v25);
        (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v26, v26);
        pixels_remaining -= v27;
      }
      while ( pixels_remaining );
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v54 + 12))();
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v43 + 12))();
    }
    (**dest_cursor)();
    return (**src_cursor)();
  }
}
// 40292A: variable 'v11' is possibly undefined
// 402937: variable 'v14' is possibly undefined
// 402989: variable 'v17' is possibly undefined
// 40299D: variable 'v19' is possibly undefined
// 4029B8: variable 'v21' is possibly undefined
// 4029EA: variable 'v23' is possibly undefined
// 4029F5: variable 'v24' is possibly undefined
// 4029FE: variable 'v25' is possibly undefined
// 402A0E: variable 'v26' is possibly undefined
// 402A16: variable 'v27' is possibly undefined
// 402A5E: variable 'v29' is possibly undefined
// 402A70: variable 'v30' is possibly undefined
// 402A77: variable 'v32' is possibly undefined
// 402AAB: variable 'v34' is possibly undefined
// 51D018: using guessed type int g_MousePresentAtStartup;
// 51D4B8: using guessed type int dword_51D4B8;

//----- (00402BB0) --------------------------------------------------------
int  Render_BlendSurfaceRect(
        _DWORD *dest_surface,
        int first_source,
        int src_left,
        int second_source,
        unsigned __int16 src_top,
        unsigned __int16 src_right,
        unsigned __int16 src_bottom,
        unsigned __int16 dest_x,
        unsigned __int16 dest_y,
        int blend_ratio)
{
  _DWORD *dest_device; // esi
  int v12; // esi
  int v13; // esi
  int v14; // edi
  _DWORD *v15; // ecx
  int v16; // ebx
  int v17; // eax
  int v18; // ecx
  __int64 v19; // rax
  int v20; // ecx
  unsigned int chunk_length; // ebx
  unsigned __int8 *second_read_ptr; // eax
  int v23; // edx
  __int64 v24; // rax
  _DWORD scratch_surface[49]; // [esp+0h] [ebp-120h] BYREF
  int (***second_src_cursor)(void); // [esp+C4h] [ebp-5Ch]
  int v28 CLASH95_UNUSED; // [esp+C8h] [ebp-58h]
  int src_top_saved; // [esp+CCh] [ebp-54h]
  int second_source_saved; // [esp+D0h] [ebp-50h]
  unsigned __int8 *blend_source_ptr; // [esp+D4h] [ebp-4Ch]
  int span_width; // [esp+D8h] [ebp-48h]
  int v33; // [esp+DCh] [ebp-44h]
  void (***dest_cursor)(void); // [esp+E0h] [ebp-40h]
  int src_right_saved; // [esp+E4h] [ebp-3Ch]
  void (***first_src_cursor)(void); // [esp+E8h] [ebp-38h]
  int span_height; // [esp+ECh] [ebp-34h]
  int src_bottom_saved; // [esp+F0h] [ebp-30h]
  int v39; // [esp+F4h] [ebp-2Ch]
  _DWORD *v40; // [esp+F8h] [ebp-28h]
  int v41; // [esp+FCh] [ebp-24h]
  int v42 CLASH95_UNUSED; // [esp+100h] [ebp-20h]
  unsigned int row_width; // [esp+104h] [ebp-1Ch]
  int v44 CLASH95_UNUSED; // [esp+108h] [ebp-18h]
  int v45 CLASH95_UNUSED; // [esp+10Ch] [ebp-14h]
  int rows_remaining; // [esp+110h] [ebp-10h]
  int v47; // [esp+114h] [ebp-Ch]
  unsigned int pixels_remaining; // [esp+118h] [ebp-8h]
  int src_left_saved; // [esp+11Ch] [ebp-4h]

  dest_device = dest_surface;
  second_source_saved = second_source;
  src_left_saved = src_left;
  if ( !dest_surface )
    dest_device = (_DWORD*)(&g_MainRenderDevice);
  src_right_saved = src_right;
  v33 = (unsigned __int16)src_left_saved;
  span_width = src_right - (unsigned __int16)src_left_saved + 1;
  src_bottom_saved = src_bottom;
  src_top_saved = src_top;
  span_height = src_bottom - src_top + 1;
  if ( g_MousePresentAtStartup && dest_device == (_DWORD *)&g_MainRenderDevice )
  {
    Render_ConstructScratchSurface((int)(intptr_t)scratch_surface, span_width, 1u, span_height);
    Render_BlendSurfaceRect(scratch_surface, first_source, v33, second_source_saved, src_top_saved, src_right_saved, src_bottom_saved, 0, 0, blend_ratio);
    Render_FillRect(scratch_surface, dest_device, 0, 0, LOWORD(scratch_surface[0]) - 1, HIWORD(scratch_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(scratch_surface, 0);
  }
  else
  {
    dest_cursor = (void (***)(void))(uintptr_t)(*(int (**)(void))(uintptr_t)(dest_device[46] + 8))();
    v28 = src_top;
    v12 = *(_DWORD *)(uintptr_t)(first_source + 184);
    blend_source_ptr = (unsigned __int8 *)(uintptr_t)(unsigned __int16)src_left_saved;
    v13 = (*(int (__fastcall **)(void (***)(void), _DWORD))(uintptr_t)(v12 + 4))(dest_cursor, (unsigned __int16)src_left_saved);
    v14 = *(_DWORD *)(uintptr_t)(second_source_saved + 184);
    first_src_cursor = (void (***)(void))(uintptr_t)v13;
    second_src_cursor = (int (***)(void))(uintptr_t)(*(int (**)(void))(uintptr_t)(v14 + 4))();
    g_Palette_BlendRatio = blend_ratio;
    v40 = v15;
    rows_remaining = span_height;
    v16 = *v15;
    row_width = span_width;
    v17 = (*(int (__fastcall **)(_DWORD *, int (***)(void)))(uintptr_t)(v16 + 4))(v15, second_src_cursor);
    v18 = *(_DWORD *)(uintptr_t)v13;
    v45 = v17 - span_width;
    v41 = v13;
    v19 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(v18 + 4))();
    v20 = *(_DWORD *)(uintptr_t)HIDWORD(v19);
    v42 = v19 - span_width;
    v47 = HIDWORD(v19);
    v44 = (*(int (**)(void))(uintptr_t)(v20 + 4))() - span_width;
    while ( --rows_remaining != -1 )
    {
      pixels_remaining = row_width;
      v39 = v47;
      do
      {
        chunk_length = pixels_remaining;
        if ( (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v13 + 8))() < pixels_remaining )
          chunk_length = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v13 + 8))();
        if ( chunk_length > (*(int (**)(void))(uintptr_t)(*v40 + 8))() )
          chunk_length = (*(int (**)(void))(uintptr_t)(*v40 + 8))();
        if ( chunk_length > (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v39 + 8))() )
          chunk_length = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v39 + 8))();
        second_read_ptr = (unsigned __int8 *)(uintptr_t)(*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v39 + 16))();
        v23 = *(_DWORD *)(uintptr_t)v13;
        blend_source_ptr = second_read_ptr;
        (*(void (**)(void))(uintptr_t)(v23 + 16))();
        v24 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*v40 + 16))();
        Palette_BlendIndexedPixelRun((char *)v24, (char *)(uintptr_t)HIDWORD(v24), blend_source_ptr, chunk_length);
        (*(void (**)(void))(uintptr_t)(*v40 + 12))();
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v13 + 12))();
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v39 + 12))();
        pixels_remaining -= chunk_length;
      }
      while ( pixels_remaining );
      (*(void (**)(void))(uintptr_t)(*v40 + 12))();
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v41 + 12))();
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v47 + 12))();
    }
    (**dest_cursor)();
    (**first_src_cursor)();
    return (**second_src_cursor)();
  }
}
// 402C84: variable 'v15' is possibly undefined
// 519A14: using guessed type int dword_519A14;
// 51D018: using guessed type int g_MousePresentAtStartup;
