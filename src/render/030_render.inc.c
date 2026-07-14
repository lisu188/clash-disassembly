/* Core surfaces, sprites, palettes, fonts, and rendering.
 * Original function-marker range: 0x00401A40..0x00407D20.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00401A40) --------------------------------------------------------
__int16 Render_LoadResourceBackbuffer()
{
  Render_InitRecoveredVtableStorage();
  g_ActiveBlitCursor = (int)g_NullBlitCursor_Vtable;
  Surface_ConstructBackbufferInstance((int)&g_MainRenderDevice);
  CRT_RegisterFinalizableObject((int)&g_RenderBackbufferScanlineBuffer, 640);
  Render_ConstructSurfaceObject((int)&g_RenderDeviceStorage, 640, SCREEN_HEIGHT);
  CRT_RegisterFinalizableObject((int)&g_RenderPaletteRemapBuffer, 256);
  _wcpp_4_ctor_array__((int)&g_DefaultPaletteTable, 256);
  g_Render_BackgroundColorIndex = 0;
  return (unsigned __int8)Palette_BuildGrayscaleIdentityTable((int)g_PaletteScratchSurfaceBuffer);
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

  palette_end = result + 1024;
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
  char palette_bytes[768]; // [esp+0h] [ebp-310h]

  (void)context;
  Compat_QueryRead(query_handle, palette_bytes, 0x300);
  write_ptr = palette_table;
  palette_offset = 0;
  while ( write_ptr != palette_table + 1024 )
  {
    red = (unsigned __int8)palette_bytes[palette_offset];
    green = (unsigned __int8)palette_bytes[palette_offset + 1];
    blue = (unsigned __int8)palette_bytes[palette_offset + 2];
    packed_rgb = red | (green << 8) | (blue << 16);
    *(_DWORD *)write_ptr = packed_rgb;
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
  Debug_Log(63, (DWORD)(uintptr_t)palette_name, (DWORD)palette_table, (int)a_loadpalpcxS0x);
  strcpy(path, aGfx_7);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, -0x300);
  Palette_ExpandRGBTripletsToTable(palette_table, query_handle, 0);
  return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
}

//----- (00401C40) --------------------------------------------------------
int  LoadPalCOL(int palette_table, intptr_t palette_name_addr, DWORD context)
{
  const char *palette_name;
  char path[256]; // [esp+0h] [ebp-114h] BYREF
  int query_handle; // [esp+100h] [ebp-14h] BYREF

  palette_name = (const char *)(uintptr_t)palette_name_addr;
  Debug_Log(63, palette_table, context, (int)a_loadpalcolS0x);
  strcpy(path, aGfx_0);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, 8);
  Palette_ExpandRGBTripletsToTable(palette_table, query_handle, 0);
  return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
}

static int Compat_LoadPalCOLIntoTable(int *palette_table, const char *palette_name, DWORD context)
{
  char path[256];
  unsigned char palette_bytes[768];
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
  for ( palette_index = 0; palette_index < 256; ++palette_index )
  {
    unsigned char red = palette_bytes[3 * palette_index];
    unsigned char green = palette_bytes[3 * palette_index + 1];
    unsigned char blue = palette_bytes[3 * palette_index + 2];
    palette_table[palette_index] = red | (green << 8) | (blue << 16);
  }
  return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
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

  write_ptr = _wcpp_4_ctor_array__(palette_table, 256);
  table_base = write_ptr;
  for ( i = 0; i < 256; ++i )
  {
    LOBYTE(packed_entry) = i;
    BYTE1(packed_entry) = i;
    HIWORD(packed_entry) = (unsigned __int8)i;
    write_ptr += 4;
    *(_DWORD *)(write_ptr - 4) = packed_entry;
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

  Render_BeginModeSwitch(&g_MainRenderDevice);
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

  surface_body = (_DWORD *)(surface_addr + 8);
  *(surface_body - 1) = 0;
  *((_WORD *)surface_body - 4) = width;
  *((_WORD *)surface_body - 3) = height;
  surface = Surface_Construct(surface_body);
  surface[44] = g_Surface_BaseVtable;
  return surface - 2;
}
// 50EDD4: using guessed type int (*off_50EDD4[5])();

//----- (00401E30) --------------------------------------------------------
int  Render_ClearGameScreen(_DWORD *surface)
{
  return Render_FillRect(surface, &g_MainRenderDevice, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
}

//----- (00401E60) --------------------------------------------------------
int  Surface_ClearWholeArea(unsigned __int16 *surface)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, int))(*((_DWORD *)surface + 46) + 32))(0, 0, surface[1] * *surface);
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

  write_cursor = (*(int (**)(void))(*(_DWORD *)(surface + 184) + 8))();
  fill_color = v3;
  do
  {
    if ( pixel_count > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(pixel_count) )
      (*(void (**)(void))(g_ActiveBlitCursor + 8))();
    v4 = (*(int (**)(void))(*(_DWORD *)write_cursor + 8))();
    if ( v5 > v4 )
      v5 = (*(int (**)(void))(*(_DWORD *)write_cursor + 8))();
    v6 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v5);
    if ( v7 > v6 )
      v7 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
    (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v7);
    (*(void (**)(void))(g_ActiveBlitCursor + 16))();
    (*(void (**)(void))(*(_DWORD *)write_cursor + 16))();
    memset_(v8, fill_color);
    (*(void (__fastcall **)(int, int))(*(_DWORD *)write_cursor + 12))(v9, v9);
    (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v10, v10);
    (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v11, v11);
    pixel_count -= v12;
  }
  while ( pixel_count );
  return (**(int (***)(void))write_cursor)();
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
        __int16 a8)
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

  read_cursor = (*(int (**)(void))(*(_DWORD *)(source_surface + 184) + 4))();
  write_cursor = (*(int (__fastcall **)(int, _DWORD))(*(_DWORD *)(dest_surface + 184) + 8))(read_cursor, dest_x);
  span_width = src_right - src_left + 1;
  while ( 1 )
  {
    src_top += 2;
    if ( (unsigned __int16)src_top > src_bottom )
      break;
    for ( i = 0; i < span_width / 2; ++i )
    {
      (*(void (**)(void))(*(_DWORD *)v11 + 16))();
      v14 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)write_cursor + 16))();
      *(_BYTE *)v14 = *(_BYTE *)HIDWORD(v14);
      (*(void (__fastcall **)(int, int))(*(_DWORD *)v15 + 12))(v15, 2);
      (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
    }
    v16 = *(_DWORD *)write_cursor;
    (*(void (**)(void))(*(_DWORD *)write_cursor + 4))();
    (*(void (**)(void))(v16 + 12))();
    v18 = *v17;
    (*(void (**)(void))(*v17 + 4))();
    (*(void (**)(void))(v18 + 12))();
  }
  (**(void (***)(void))write_cursor)();
  return (**v19)(v19, 2);
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

  Debug_Log(transparent, 0, (DWORD)file_name, (int)a_loadpcxS0x08x);
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
    Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
    return 0;
  }

  file_buffer = (unsigned char *)(uintptr_t)(unsigned int)nmalloc_(file_size, 4);
  if ( !file_buffer )
  {
    Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
    return 0;
  }

  Compat_QueryRead(query_handle, file_buffer, file_size);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  if ( file_size < 128 )
  {
    Compat_FreeLow32Bytes((int)(uintptr_t)file_buffer);
    return 0;
  }

  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)*(_DWORD *)(surface + 4);
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
      *(unsigned __int16 *)surface,
      *((unsigned __int16 *)surface + 1),
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
  if ( palette_out_addr && file_offset + 768 <= file_size )
  {
    palette_out = (unsigned int *)palette_out_addr;
    palette_bytes = decode_cursor;
    for ( palette_offset = 0; palette_offset != 768; palette_offset += 3 )
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
  int v10; // ecx
  void (**v11)(void); // ecx
  __int64 v12; // rax
  int v13; // ecx
  int v14; // eax
  unsigned int chunk_length; // ebx
  const void *copy_source; // esi
  unsigned int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  __int64 v20; // rax
  int v21; // ecx
  __int64 v22; // rax
  int src_view_handle; // ebx
  int dest_view_handle; // eax
  int (__fastcall **v25)(_DWORD, int); // ecx
  void *copy_dest; // [esp-4h] [ebp-114h]
  _DWORD v28[49]; // [esp+0h] [ebp-110h] BYREF
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
  int v39; // [esp+ECh] [ebp-24h]
  unsigned int row_width; // [esp+F0h] [ebp-20h]
  int v41; // [esp+F4h] [ebp-1Ch]
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
    src_resolved = &g_MainRenderDevice;
  if ( !dest_surface )
    dest_resolved = &g_MainRenderDevice;
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
    temp_surface = (_DWORD *)Mem_Alloc(196, 0, 0, 0);
    if ( !temp_surface )
      return 0;
    Render_ConstructScratchSurface((int)temp_surface, span_width, 1u, span_height);
    Render_FillRect(src_resolved, temp_surface, (unsigned __int16)src_top_saved, (unsigned __int16)src_left_saved, src_right, src_bottom, 0, 0);
    Render_FillRect(temp_surface, dest_resolved, 0, 0, LOWORD(temp_surface[0]) - 1, HIWORD(temp_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(temp_surface, 2);
  }
  else
  {
    dest_cursor = (void (***)(void))(*(int (**)(void))(dest_resolved[46] + 8))();
    src_cursor = (int (***)(void))(*(int (**)(void))(src_resolved[46] + 4))();
    rows_remaining = span_height;
    v11 = *dest_cursor;
    row_width = span_width;
    v12 = ((__int64 (*)(void))v11[1])();
    v42 = v12 - span_width;
    v13 = *(_DWORD *)HIDWORD(v12);
    v43 = HIDWORD(v12);
    v39 = (*(int (**)(void))(v13 + 4))() - span_width;
    v14 = (*(int (**)(void))(g_ActiveBlitCursor + 4))();
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
        if ( (*(int (**)(void))(*(_DWORD *)v45 + 8))() < pixels_remaining )
          chunk_length = (*(int (**)(void))(*(_DWORD *)v45 + 8))();
        if ( chunk_length > ((int (*)(void))(*v33)[2])() )
          chunk_length = ((int (*)(void))(*v33)[2])();
        if ( chunk_length > (*(int (**)(void))(g_ActiveBlitCursor + 8))() )
          chunk_length = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
        (*(void (**)(void))(g_ActiveBlitCursor + 16))();
        copy_source = (const void *)(*(int (**)(void))(*(_DWORD *)v45 + 16))();
        copy_dest = (void *)((int (__thiscall *)(unsigned int))(*v33)[4])(chunk_length);
        qmemcpy(copy_dest, copy_source, v17);
        (*v33)[3]();
        (*(void (**)(void))(*(_DWORD *)v45 + 12))();
        (*(void (__fastcall **)(unsigned int, unsigned int))(g_ActiveBlitCursor + 12))(pixels_remaining, chunk_length);
        pixels_remaining = v18 - chunk_length;
      }
      while ( v18 != chunk_length );
      ((void (__fastcall *)(_DWORD, int))(*v32)[3])(0, v42);
      (*(void (**)(void))(*(_DWORD *)v43 + 12))();
      (*(void (**)(void))(g_ActiveBlitCursor + 12))();
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
  int v10; // edx
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
  int v28; // eax
  int v29; // ecx
  int v30; // ecx
  _DWORD *v31; // eax
  int v32; // ecx
  _DWORD *v33; // eax
  int v34; // ecx
  int v35; // eax
  int v36; // edx
  int v37; // eax
  _DWORD scratch_surface[51]; // [esp+0h] [ebp-110h] BYREF
  int v40; // [esp+CCh] [ebp-44h]
  int span_height; // [esp+D0h] [ebp-40h]
  int v42; // [esp+D4h] [ebp-3Ch]
  int v43; // [esp+D8h] [ebp-38h]
  int pixels_remaining; // [esp+DCh] [ebp-34h]
  int (***src_cursor)(void); // [esp+E0h] [ebp-30h]
  int v46; // [esp+E4h] [ebp-2Ch]
  int src_right_saved; // [esp+E8h] [ebp-28h]
  void (***dest_cursor)(void); // [esp+ECh] [ebp-24h]
  int rows_remaining; // [esp+F0h] [ebp-20h]
  int span_width; // [esp+F4h] [ebp-1Ch]
  int v51; // [esp+F8h] [ebp-18h]
  int row_width; // [esp+FCh] [ebp-14h]
  int i; // [esp+100h] [ebp-10h]
  int v54; // [esp+104h] [ebp-Ch]
  int src_left_saved; // [esp+108h] [ebp-8h]
  int src_top_saved; // [esp+10Ch] [ebp-4h]

  src_resolved = source_surface;
  dest_resolved = dest_surface;
  src_left_saved = src_left;
  src_top_saved = src_top;
  if ( !source_surface )
    src_resolved = &g_MainRenderDevice;
  if ( !dest_surface )
    dest_resolved = &g_MainRenderDevice;
  src_right_saved = src_right;
  span_width = src_right - (unsigned __int16)src_left_saved + 1;
  v46 = (unsigned __int16)src_top_saved;
  v10 = src_resolved[46];
  span_height = src_bottom - (unsigned __int16)src_top_saved + 1;
  if ( (*(int (**)(void))(v10 + 60))() && (*(int (**)(void))(dest_resolved[46] + 64))() )
  {
    v28 = (*(int (**)(void))(src_resolved[46] + 60))();
    Surface_SetSrcColorKey(v28, 0, v29);
    v31 = (_DWORD *)(*(int (__thiscall **)(int))(src_resolved[46] + 60))(v30 + 1);
    Surface_SetSrcRect(v31, v46, v32, (unsigned __int16)src_left_saved, src_right_saved + 1);
    scratch_surface[49] = dest_x;
    scratch_surface[50] = dest_y;
    v33 = (_DWORD *)(*(int (__thiscall **)(int))(src_resolved[46] + 60))(dest_y + span_height);
    Surface_SetDestRect(v33, dest_y, v34, dest_x, span_width + dest_x);
    v35 = (*(int (**)(void))(src_resolved[46] + 60))();
    v36 = dest_resolved[46];
    v40 = *(_DWORD *)(v35 + 172);
    v37 = (*(int (**)(void))(v36 + 64))();
    return (*(int (__fastcall **)(int, _DWORD))(v40 + 8))(v37, dest_x);
  }
  else if ( g_MousePresentAtStartup && (src_resolved == (_DWORD *)&g_MainRenderDevice || dest_resolved == (_DWORD *)&g_MainRenderDevice) )
  {
    Render_ConstructScratchSurface((int)scratch_surface, span_width, 1u, span_height);
    Render_FillRect(src_resolved, scratch_surface, (unsigned __int16)src_top_saved, (unsigned __int16)src_left_saved, src_right, src_bottom, 0, 0);
    Render_BlitSurfaceRect(scratch_surface, dest_resolved, 0, 0, LOWORD(scratch_surface[0]) - 1, HIWORD(scratch_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(scratch_surface, 0);
  }
  else
  {
    dest_cursor = (void (***)(void))(*(int (**)(void))(dest_resolved[46] + 8))();
    src_cursor = (int (***)(void))(*(int (__fastcall **)(void (***)(void), _DWORD))(src_resolved[46] + 4))(dest_cursor, (unsigned __int16)src_left_saved);
    rows_remaining = span_height;
    v12 = *v11;
    row_width = span_width;
    v13 = ((__int64 (__fastcall *)(int *, int (***)(void)))*(_DWORD *)(v12 + 4))(v11, src_cursor);
    v54 = v14;
    v15 = *(_DWORD *)HIDWORD(v13);
    v42 = v13 - span_width;
    v43 = HIDWORD(v13);
    v51 = (*(int (**)(void))(v15 + 4))() - span_width;
    for ( i = (*(int (**)(void))(g_ActiveBlitCursor + 4))() - span_width;
          --rows_remaining != -1;
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, i) )
    {
      pixels_remaining = row_width;
      do
      {
        v16 = (*(int (__thiscall **)(int))(*(_DWORD *)v43 + 8))(pixels_remaining);
        if ( v16 < v17 )
          v17 = (*(int (**)(void))(*(_DWORD *)v43 + 8))();
        v18 = (*(int (__fastcall **)(unsigned int))(*(_DWORD *)v54 + 8))(v17);
        if ( v19 > v18 )
          v19 = (*(int (**)(void))(*(_DWORD *)v54 + 8))();
        v20 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v19);
        if ( v21 > v20 )
          v21 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
        (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v21);
        (*(void (**)(void))(*(_DWORD *)v43 + 16))();
        v22 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)v54 + 16))();
        Str_CompactSkippingZeroBytes((_BYTE *)v22, (_BYTE *)HIDWORD(v22), v23);
        (*(void (__fastcall **)(int, int))(*(_DWORD *)v54 + 12))(v24, v24);
        (*(void (__fastcall **)(int, int))(*(_DWORD *)v43 + 12))(v25, v25);
        (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v26, v26);
        pixels_remaining -= v27;
      }
      while ( pixels_remaining );
      (*(void (**)(void))(*(_DWORD *)v54 + 12))();
      (*(void (**)(void))(*(_DWORD *)v43 + 12))();
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
  int v28; // [esp+C8h] [ebp-58h]
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
  int v42; // [esp+100h] [ebp-20h]
  unsigned int row_width; // [esp+104h] [ebp-1Ch]
  int v44; // [esp+108h] [ebp-18h]
  int v45; // [esp+10Ch] [ebp-14h]
  int rows_remaining; // [esp+110h] [ebp-10h]
  int v47; // [esp+114h] [ebp-Ch]
  unsigned int pixels_remaining; // [esp+118h] [ebp-8h]
  int src_left_saved; // [esp+11Ch] [ebp-4h]

  dest_device = dest_surface;
  second_source_saved = second_source;
  src_left_saved = src_left;
  if ( !dest_surface )
    dest_device = &g_MainRenderDevice;
  src_right_saved = src_right;
  v33 = (unsigned __int16)src_left_saved;
  span_width = src_right - (unsigned __int16)src_left_saved + 1;
  src_bottom_saved = src_bottom;
  src_top_saved = src_top;
  span_height = src_bottom - src_top + 1;
  if ( g_MousePresentAtStartup && dest_device == (_DWORD *)&g_MainRenderDevice )
  {
    Render_ConstructScratchSurface((int)scratch_surface, span_width, 1u, span_height);
    Render_BlendSurfaceRect(scratch_surface, first_source, v33, second_source_saved, src_top_saved, src_right_saved, src_bottom_saved, 0, 0, blend_ratio);
    Render_FillRect(scratch_surface, dest_device, 0, 0, LOWORD(scratch_surface[0]) - 1, HIWORD(scratch_surface[0]) - 1, dest_x, dest_y);
    return Render_DestructScratchSurface(scratch_surface, 0);
  }
  else
  {
    dest_cursor = (void (***)(void))(*(int (**)(void))(dest_device[46] + 8))();
    v28 = src_top;
    v12 = *(_DWORD *)(first_source + 184);
    blend_source_ptr = (unsigned __int8 *)(unsigned __int16)src_left_saved;
    v13 = (*(int (__fastcall **)(void (***)(void), _DWORD))(v12 + 4))(dest_cursor, (unsigned __int16)src_left_saved);
    v14 = *(_DWORD *)(second_source_saved + 184);
    first_src_cursor = (void (***)(void))v13;
    second_src_cursor = (int (***)(void))(*(int (**)(void))(v14 + 4))();
    g_Palette_BlendRatio = blend_ratio;
    v40 = v15;
    rows_remaining = span_height;
    v16 = *v15;
    row_width = span_width;
    v17 = (*(int (__fastcall **)(_DWORD *, int (***)(void)))(v16 + 4))(v15, second_src_cursor);
    v18 = *(_DWORD *)v13;
    v45 = v17 - span_width;
    v41 = v13;
    v19 = ((__int64 (*)(void))*(_DWORD *)(v18 + 4))();
    v20 = *(_DWORD *)HIDWORD(v19);
    v42 = v19 - span_width;
    v47 = HIDWORD(v19);
    v44 = (*(int (**)(void))(v20 + 4))() - span_width;
    while ( --rows_remaining != -1 )
    {
      pixels_remaining = row_width;
      v39 = v47;
      do
      {
        chunk_length = pixels_remaining;
        if ( (*(int (**)(void))(*(_DWORD *)v13 + 8))() < pixels_remaining )
          chunk_length = (*(int (**)(void))(*(_DWORD *)v13 + 8))();
        if ( chunk_length > (*(int (**)(void))(*v40 + 8))() )
          chunk_length = (*(int (**)(void))(*v40 + 8))();
        if ( chunk_length > (*(int (**)(void))(*(_DWORD *)v39 + 8))() )
          chunk_length = (*(int (**)(void))(*(_DWORD *)v39 + 8))();
        second_read_ptr = (unsigned __int8 *)(*(int (**)(void))(*(_DWORD *)v39 + 16))();
        v23 = *(_DWORD *)v13;
        blend_source_ptr = second_read_ptr;
        (*(void (**)(void))(v23 + 16))();
        v24 = ((__int64 (*)(void))*(_DWORD *)(*v40 + 16))();
        Palette_BlendIndexedPixelRun((char *)v24, (char *)HIDWORD(v24), blend_source_ptr, chunk_length);
        (*(void (**)(void))(*v40 + 12))();
        (*(void (**)(void))(*(_DWORD *)v13 + 12))();
        (*(void (**)(void))(*(_DWORD *)v39 + 12))();
        pixels_remaining -= chunk_length;
      }
      while ( pixels_remaining );
      (*(void (**)(void))(*v40 + 12))();
      (*(void (**)(void))(*(_DWORD *)v41 + 12))();
      (*(void (**)(void))(*(_DWORD *)v47 + 12))();
    }
    (**dest_cursor)();
    (**first_src_cursor)();
    return (**second_src_cursor)();
  }
}
// 402C84: variable 'v15' is possibly undefined
// 519A14: using guessed type int dword_519A14;
// 51D018: using guessed type int g_MousePresentAtStartup;

//----- (00402E80) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
int  Render_BlitCompressedSpriteRLE(
        int dest_device,
        int sprite,
        int draw_y,
        int draw_x,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        int a21,
        int a22,
        int a23,
        int a24,
        int a25,
        int a26,
        int a27,
        int a28,
        int a29,
        int a30,
        __int128 clip_bounds,
        int transparent_flags,
        int blend_mode_flags,
        __int64 rgb_offsets_packed)
{
  int *rgb_offset_table; // esi
  _DWORD *Surface; // eax
  int v36; // ecx
  char v37; // bl
  int v38; // edx
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  unsigned __int8 **v42; // eax
  unsigned __int8 **v43; // edx
  unsigned __int8 *v44; // ecx
  int v45; // edi
  int v46; // eax
  int **v47; // eax
  int *v48; // ecx
  int v49; // edi
  int **v50; // edx
  int v51; // eax
  int v52; // eax
  int v53; // ecx
  int **v54; // eax
  int *v55; // ecx
  int v56; // ecx
  int v57; // esi
  unsigned __int8 run_byte; // al
  _DWORD *backref_len_ptr; // ecx
  unsigned __int8 transparent_run_length; // dh
  unsigned int skip_remaining; // edi
  int v62; // esi
  int v63; // ecx
  unsigned int v64; // eax
  unsigned int v65; // ecx
  unsigned int v66; // eax
  unsigned int v67; // ecx
  int v68; // ecx
  int v69; // ecx
  int v70; // ecx
  int v71; // ecx
  int v72; // ecx
  int v73; // ecx
  unsigned int v74; // ecx
  unsigned __int8 *backref_data_ptr; // esi
  int copy_run_length; // ecx
  unsigned int copy_chunk_length; // ebx
  unsigned __int8 *v78; // esi
  unsigned int v79; // ecx
  int v80; // ebx
  int v81; // ecx
  int v82; // edx
  int v83; // ecx
  int v84; // ecx
  int v85; // ebx
  unsigned int v86; // ecx
  unsigned int blend_run_length; // esi
  int *v88; // edx
  unsigned int blend_chunk_length; // ebx
  __int64 v90; // rax
  int v91; // ebx
  int *v92; // eax
  int v93; // esi
  int v94; // ecx
  unsigned int offset_run_length; // ecx
  int offset_chunk_length; // ebx
  unsigned __int8 *copy_src_ptr; // esi
  int *v98; // edx
  unsigned int v99; // ecx
  int v100; // ecx
  int v101; // ebx
  int v102; // ecx
  unsigned int fill_run_length; // edi
  int v104; // ecx
  unsigned int v105; // eax
  unsigned int v106; // ecx
  unsigned int v107; // eax
  unsigned int v108; // ecx
  int v109; // ecx
  int v110; // ecx
  int v111; // ecx
  int v112; // ecx
  int v113; // ecx
  unsigned __int8 *v114; // eax
  unsigned __int8 *v115; // edi
  int v116; // ecx
  unsigned int v117; // ecx
  int result; // eax
  unsigned __int8 *v119; // [esp-4h] [ebp-108h]
  int skip_clip_left; // [esp+6Eh] [ebp-96h]
  int skip_clip_top; // [esp+72h] [ebp-92h]
  int skip_clip_right; // [esp+76h] [ebp-8Eh]
  int skip_clip_bottom; // [esp+7Ah] [ebp-8Ah]
  int skip_clip_enabled; // [esp+7Eh] [ebp-86h]
  int copy_clip_left; // [esp+86h] [ebp-7Eh]
  int copy_clip_top; // [esp+8Ah] [ebp-7Ah]
  int copy_clip_right; // [esp+8Eh] [ebp-76h]
  int copy_clip_bottom; // [esp+92h] [ebp-72h]
  int copy_clip_enabled; // [esp+96h] [ebp-6Eh]
  _DWORD v130[4]; // [esp+9Ah] [ebp-6Ah] BYREF
  unsigned __int8 *run_pixel_ptr; // [esp+AAh] [ebp-5Ah]
  int offset_x_saved; // [esp+B2h] [ebp-52h]
  int fill_x_saved; // [esp+B6h] [ebp-4Eh]
  _DWORD *offscreen_surface; // [esp+BAh] [ebp-4Ah]
  void *copy_write_cursor; // [esp+BEh] [ebp-46h]
  int copy_clip_overflow; // [esp+C2h] [ebp-42h]
  int blend_clip_overflow; // [esp+C6h] [ebp-3Eh]
  int offset_clip_overflow; // [esp+CAh] [ebp-3Ah]
  unsigned __int8 **fill_ctx_ref; // [esp+CEh] [ebp-36h]
  int skip_clip_overflow; // [esp+D2h] [ebp-32h]
  unsigned __int8 *blend_src_ptr; // [esp+D6h] [ebp-2Eh]
  void *write_cursor; // [esp+DAh] [ebp-2Ah]
  int row_index; // [esp+DEh] [ebp-26h]
  signed int skip_clip_right_plus1; // [esp+E2h] [ebp-22h]
  int skip_clip_left_plus1; // [esp+E6h] [ebp-1Eh]
  int copy_clip_left_plus1; // [esp+EAh] [ebp-1Ah]
  int copy_clip_right_plus1; // [esp+EEh] [ebp-16h]
  __int16 *sprite_header; // [esp+F2h] [ebp-12h]
  int blend_x_saved; // [esp+F6h] [ebp-Eh]
  int device_addr; // [esp+FAh] [ebp-Ah]
  int draw_y_saved; // [esp+FEh] [ebp-6h]
  int var2; // [esp+102h] [ebp-2h]
  int vars2; // [esp+106h] [ebp+2h]
  _DWORD *vars6; // [esp+10Ah] [ebp+6h]
  __int16 _10E; // [esp+10Eh] [ebp+Ah] OVERLAPPED
  _UNKNOWN *retaddr; // [esp+110h] [ebp+Ch] OVERLAPPED
  void *offset_write_cursor; // [esp+116h] [ebp+12h]
  void *fill_write_cursor; // [esp+11Ah] [ebp+16h]
  int fill_clip_overflow; // [esp+122h] [ebp+1Eh]
  unsigned __int8 **fill_clip_ctx; // [esp+126h] [ebp+22h]
  int **offset_clip_ctx; // [esp+12Ah] [ebp+26h]
  int **blend_clip_ctx; // [esp+12Eh] [ebp+2Ah]
  int screen_y; // [esp+132h] [ebp+2Eh]
  _BYTE *rle_cursor; // [esp+136h] [ebp+32h]
  int screen_x; // [esp+13Eh] [ebp+3Ah]
  unsigned __int8 *dest_write_ptr; // [esp+142h] [ebp+3Eh]
  unsigned __int8 *run_start_ptr; // [esp+14Ah] [ebp+46h]
  unsigned int copy_run_remaining; // [esp+14Eh] [ebp+4Ah]
  unsigned int offset_run_remaining; // [esp+152h] [ebp+4Eh]
  unsigned int blend_run_remaining; // [esp+156h] [ebp+52h]
  void *v172; // [esp+15Eh] [ebp+5Ah]
  __int16 sprite_format; // [esp+162h] [ebp+5Eh]
  unsigned __int8 run_length; // [esp+166h] [ebp+62h]

  rgb_offset_table = *(int **)((char *)&rgb_offsets_packed + 2);
  device_addr = dest_device;
  sprite_header = (__int16 *)sprite;
  var2 = draw_x;
  draw_y_saved = draw_y;
  rle_cursor = *(_BYTE **)(sprite + 10);
  sprite_format = *(_WORD *)(sprite + 4);
  offscreen_surface = 0;
  BYTE2(a26) = g_TextSprite_StyleFlag;
  if ( g_MousePresentAtStartup && (_UNKNOWN *)device_addr == &g_MainRenderDevice )
  {
    if ( *(_DWORD *)((char *)&clip_bounds + 2) != -1 )
      App_RequestQuit((int)aDlxvscreenDraw);
    Surface = (_DWORD *)Mem_Alloc(188, g_MousePresentAtStartup, draw_x, (DWORD)v130);
    if ( Surface )
      Surface = Render_CreateSurface((int)Surface, *sprite_header, sprite_header[1]);
    offscreen_surface = Surface;
    if ( BYTE2(transparent_flags) )
      Render_FillRect(
        &g_MainRenderDevice,
        Surface,
        (unsigned __int16)draw_y_saved,
        (unsigned __int16)var2,
        var2 + *sprite_header - 1,
        draw_y_saved + sprite_header[1] - 1,
        0,
        0);
  }
  if ( offscreen_surface )
  {
    v36 = offscreen_surface[46];
    v37 = 0;
    v38 = 0;
  }
  else
  {
    v37 = draw_y_saved;
    v36 = *(_DWORD *)(device_addr + 184);
    v38 = var2;
  }
  write_cursor = (void *)(*(int (__fastcall **)(int, int))(v36 + 8))(v36, v38);
  skip_clip_left = *(_DWORD *)((char *)&clip_bounds + 2);
  skip_clip_top = *(_DWORD *)((char *)&clip_bounds + 6);
  skip_clip_right = *(_DWORD *)((char *)&clip_bounds + 10);
  skip_clip_bottom = *(_DWORD *)((char *)&clip_bounds + 14);
  if ( *(_DWORD *)((char *)&clip_bounds + 2) == -1
    && *(_DWORD *)((char *)&clip_bounds + 6) == -1
    && *(_DWORD *)((char *)&clip_bounds + 2) == *(_DWORD *)((char *)&clip_bounds + 10)
    && *(_DWORD *)((char *)&clip_bounds + 14) == *(_DWORD *)((char *)&clip_bounds + 2) )
  {
    v39 = *(_DWORD *)((char *)&clip_bounds + 2) ^ *(_DWORD *)((char *)&clip_bounds + 14);
  }
  else
  {
    v39 = 1;
  }
  skip_clip_enabled = v39;
  copy_clip_left = *(_DWORD *)((char *)&clip_bounds + 2);
  copy_clip_top = *(_DWORD *)((char *)&clip_bounds + 6);
  v40 = *(_DWORD *)((char *)&clip_bounds + 2);
  copy_clip_right = *(_DWORD *)((char *)&clip_bounds + 10);
  copy_clip_bottom = *(_DWORD *)((char *)&clip_bounds + 14);
  if ( *(_DWORD *)((char *)&clip_bounds + 2) == -1
    && *(_DWORD *)((char *)&clip_bounds + 6) == -1
    && *(_DWORD *)((char *)&clip_bounds + 2) == *(_DWORD *)((char *)&clip_bounds + 10)
    && *(_DWORD *)((char *)&clip_bounds + 14) == *(_DWORD *)((char *)&clip_bounds + 2) )
  {
    v41 = *(_DWORD *)((char *)&clip_bounds + 2) ^ *(_DWORD *)((char *)&clip_bounds + 14);
  }
  else
  {
    v41 = 1;
  }
  copy_clip_enabled = v41;
  fill_clip_ctx = 0;
  blend_clip_ctx = 0;
  offset_clip_ctx = 0;
  if ( sprite_format == 1 )
  {
    v42 = (unsigned __int8 **)Mem_Alloc(24, *(int *)((char *)&clip_bounds + 2), v37, (DWORD)v130);
    if ( v42 )
    {
      v44 = *(unsigned __int8 **)((char *)&clip_bounds + 2);
      *v42 = (unsigned __int8 *)&a26 + 2;
      v42[1] = v44;
      v42[2] = *(unsigned __int8 **)((char *)&clip_bounds + 6);
      v45 = *(_DWORD *)((char *)&clip_bounds + 2);
      v42[3] = *(unsigned __int8 **)((char *)&clip_bounds + 10);
      v40 = *(_DWORD *)((char *)&clip_bounds + 14);
      v43 = v42;
      v42[4] = *(unsigned __int8 **)((char *)&clip_bounds + 14);
      if ( v45 == -1
        && *(_DWORD *)((char *)&clip_bounds + 6) == -1
        && *(_DWORD *)((char *)&clip_bounds + 10) == -1
        && *(_DWORD *)((char *)&clip_bounds + 14) == -1 )
      {
        v46 = ~*(_DWORD *)((char *)&clip_bounds + 6);
      }
      else
      {
        v46 = 1;
      }
      v43[5] = (unsigned __int8 *)v46;
    }
    fill_clip_ctx = v43;
  }
  if ( BYTE2(blend_mode_flags) == 1 )
  {
    v47 = (int **)Mem_Alloc(24, v40, v37, (DWORD)v130);
    if ( v47 )
    {
      v48 = *(int **)((char *)&clip_bounds + 2);
      *v47 = rgb_offset_table;
      v47[1] = v48;
      v47[2] = *(int **)((char *)&clip_bounds + 6);
      v49 = *(_DWORD *)((char *)&clip_bounds + 2);
      v47[3] = *(int **)((char *)&clip_bounds + 10);
      v40 = *(_DWORD *)((char *)&clip_bounds + 14);
      v50 = v47;
      v47[4] = *(int **)((char *)&clip_bounds + 14);
      if ( v49 == -1
        && *(_DWORD *)((char *)&clip_bounds + 6) == -1
        && *(_DWORD *)((char *)&clip_bounds + 10) == -1
        && *(_DWORD *)((char *)&clip_bounds + 14) == -1 )
      {
        v51 = ~*(_DWORD *)((char *)&clip_bounds + 6);
      }
      else
      {
        v51 = 1;
      }
      v50[5] = (int *)v51;
      v47 = v50;
    }
    blend_clip_ctx = v47;
  }
  if ( BYTE2(blend_mode_flags) != 2 )
    goto LABEL_40;
  v54 = (int **)Mem_Alloc(24, v40, v37, (DWORD)v130);
  if ( v54 )
  {
    v55 = *(int **)((char *)&clip_bounds + 2);
    *v54 = rgb_offset_table;
    v54[1] = v55;
    v54[2] = *(int **)((char *)&clip_bounds + 6);
    v54[3] = *(int **)((char *)&clip_bounds + 10);
    v56 = *(_DWORD *)((char *)&clip_bounds + 14);
    v57 = *(_DWORD *)((char *)&clip_bounds + 2);
    v54[4] = *(int **)((char *)&clip_bounds + 14);
    if ( v57 != -1 || *(_DWORD *)((char *)&clip_bounds + 6) != -1 || *(_DWORD *)((char *)&clip_bounds + 10) != -1 || v56 != -1 )
    {
      v54[5] = (int *)1;
      offset_clip_ctx = v54;
      goto LABEL_40;
    }
    v54[5] = (int *)~*(_DWORD *)((char *)&clip_bounds + 10);
  }
  offset_clip_ctx = v54;
LABEL_40:
  screen_y = draw_y_saved;
  skip_clip_right_plus1 = skip_clip_right + 1;
  skip_clip_left_plus1 = skip_clip_left + 1;
  copy_clip_right_plus1 = copy_clip_right + 1;
  row_index = 0;
  copy_clip_left_plus1 = copy_clip_left + 1;
  while ( (unsigned __int16)sprite_header[1] > row_index )
  {
    vars2 = 0;
    screen_x = var2;
    while ( (unsigned __int16)*sprite_header > vars2 )
    {
      run_byte = *rle_cursor;
      backref_len_ptr = rle_cursor + 1;
      run_length = run_byte;
      ++rle_cursor;
      if ( (run_byte & 0x80u) == 0 )
      {
        if ( !sprite_format )
        {
          if ( run_byte )
          {
            vars6 = 0;
          }
          else
          {
            backref_data_ptr = (unsigned __int8 *)backref_len_ptr - *backref_len_ptr;
            vars6 = backref_len_ptr;
            run_length = *backref_data_ptr;
            rle_cursor = backref_data_ptr + 1;
          }
          run_pixel_ptr = rle_cursor;
          v130[3] = g_RenderSurface_BlitCursorVtable;
          if ( BYTE2(blend_mode_flags) )
          {
            if ( BYTE2(blend_mode_flags) <= 1u )
            {
              v130[1] = (*(int (__thiscall **)(_DWORD))(*(_DWORD *)write_cursor + 16))(0);
              LOBYTE(v86) = run_length;
              blend_x_saved = screen_x;
              v130[0] = g_RenderSurface_BlitCursorVtable;
              *(_UNKNOWN **)((char *)&retaddr + 2) = write_cursor;
              blend_run_length = v86;
              v88 = blend_clip_ctx[5];
              blend_clip_overflow = 0;
              if ( v88 )
              {
                if ( screen_y < (int)blend_clip_ctx[2]
                  || screen_y > (int)blend_clip_ctx[4]
                  || screen_x > (int)blend_clip_ctx[3]
                  || (int)(v86 + screen_x) < (int)blend_clip_ctx[1] + 1 )
                {
                  (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                  (*(void (**)(void))(v130[0] + 12))();
                  run_pixel_ptr += blend_run_length;
                  goto LABEL_97;
                }
                v92 = blend_clip_ctx[1];
                if ( (int)v92 > screen_x )
                {
                  v93 = (int)v92 - screen_x;
                  (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
                  (*(void (**)(void))(v130[0] + 12))();
                  run_pixel_ptr += v93;
                  blend_run_length = v94 - v93;
                }
                if ( (int)blend_clip_ctx[3] + 1 < (int)(blend_run_length + blend_x_saved) )
                {
                  blend_clip_overflow = blend_run_length + blend_x_saved - (_DWORD)blend_clip_ctx[3] - 1;
                  blend_run_length -= blend_clip_overflow;
                }
              }
              blend_run_remaining = blend_run_length;
              do
              {
                blend_chunk_length = blend_run_remaining;
                if ( (*(int (**)(void))(v130[0] + 8))() < blend_run_remaining )
                  blend_chunk_length = (*(int (**)(void))(v130[0] + 8))();
                if ( blend_chunk_length > (*(int (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 8))() )
                  blend_chunk_length = (*(int (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 8))();
                if ( blend_chunk_length > 0x7FFFFFFF )
                  blend_chunk_length = 0x7FFFFFFF;
                blend_src_ptr = run_pixel_ptr;
                (*(void (**)(void))(v130[0] + 16))();
                v90 = ((__int64 (*)(void))*(_DWORD *)(**(_DWORD **)((char *)&retaddr + 2) + 16))();
                Palette_BlendIndexedPixelRun((char *)v90, (char *)HIDWORD(v90), blend_src_ptr, blend_chunk_length);
                (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(v130[0] + 12))();
                run_pixel_ptr += blend_chunk_length;
                blend_run_remaining -= blend_chunk_length;
              }
              while ( blend_run_remaining );
              v91 = blend_clip_overflow;
              if ( blend_clip_overflow )
              {
                (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(v130[0] + 12))();
                run_pixel_ptr += v91;
              }
              goto LABEL_97;
            }
            if ( BYTE2(blend_mode_flags) != 2 )
              App_RequestQuit((int)aDlxmemscreenDr);
            offset_x_saved = screen_x;
            offset_clip_overflow = 0;
            offset_run_length = run_length;
            offset_write_cursor = write_cursor;
            if ( offset_clip_ctx[5] )
            {
              if ( screen_y < (int)offset_clip_ctx[2] || screen_y > (int)offset_clip_ctx[4] || screen_x > (int)offset_clip_ctx[3] || run_length + screen_x < (int)offset_clip_ctx[1] + 1 )
              {
                (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)write_cursor + 12))(run_length, run_length);
                run_pixel_ptr += v100;
                (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v100, v100);
                goto LABEL_97;
              }
              if ( (int)offset_clip_ctx[1] > screen_x )
              {
                v101 = run_length - ((_DWORD)offset_clip_ctx[1] - screen_x);
                (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
                run_pixel_ptr += v102;
                (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v101, v102);
              }
              if ( (int)offset_clip_ctx[3] + 1 < (int)(offset_run_length + offset_x_saved) )
              {
                offset_clip_overflow = offset_run_length + offset_x_saved - (_DWORD)offset_clip_ctx[3] - 1;
                offset_run_length -= offset_clip_overflow;
              }
            }
            offset_run_remaining = offset_run_length;
            do
            {
              offset_chunk_length = offset_run_remaining;
              if ( offset_run_remaining > 0x7FFFFFFF )
                offset_chunk_length = 0x7FFFFFFF;
              if ( offset_chunk_length > (unsigned int)(*(int (**)(void))(*(_DWORD *)offset_write_cursor + 8))() )
                offset_chunk_length = (*(int (**)(void))(*(_DWORD *)offset_write_cursor + 8))();
              if ( offset_chunk_length > (unsigned int)(*(int (**)(void))(g_ActiveBlitCursor + 8))() )
                offset_chunk_length = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
              (*(void (**)(void))(g_ActiveBlitCursor + 16))();
              run_start_ptr = run_pixel_ptr;
              copy_src_ptr = run_pixel_ptr;
              dest_write_ptr = (unsigned __int8 *)(*(int (__thiscall **)(int))(*(_DWORD *)offset_write_cursor + 16))(offset_chunk_length);
              v98 = *offset_clip_ctx;
              qmemcpy(dest_write_ptr, copy_src_ptr, v99);
              if ( offset_chunk_length > 1 || *run_start_ptr != v98[3] )
                Palette_OffsetIndexedPixelsRGB(dest_write_ptr, offset_chunk_length, *v98, v98[1], v98[2]);
              (*(void (**)(void))(*(_DWORD *)offset_write_cursor + 12))();
              run_pixel_ptr += offset_chunk_length;
              (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, offset_chunk_length);
              offset_run_remaining -= offset_chunk_length;
            }
            while ( offset_run_remaining );
            if ( offset_clip_overflow )
            {
              (*(void (**)(void))(*(_DWORD *)offset_write_cursor + 12))();
              run_pixel_ptr += offset_clip_overflow;
              v81 = g_ActiveBlitCursor;
              v82 = offset_clip_overflow;
LABEL_96:
              (*(void (__fastcall **)(int, int))(v81 + 12))(v81, v82);
            }
          }
          else
          {
            copy_write_cursor = write_cursor;
            copy_run_length = run_length;
            copy_clip_overflow = 0;
            if ( !copy_clip_enabled )
              goto LABEL_86;
            if ( screen_y < copy_clip_top || screen_y > copy_clip_bottom || screen_x > copy_clip_right || screen_x + run_length < copy_clip_left_plus1 )
            {
              (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)copy_write_cursor + 12))(run_length, run_length);
              run_pixel_ptr += v83;
              (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v83, v83);
            }
            else
            {
              if ( copy_clip_left > screen_x )
              {
                (*(void (__fastcall **)(int, int))(*(_DWORD *)write_cursor + 12))(copy_clip_left - screen_x, copy_clip_left - screen_x);
                run_pixel_ptr += v84;
                v85 = run_length - v84;
                (*(void (**)(void))(g_ActiveBlitCursor + 12))();
                copy_run_length = v85;
              }
              if ( screen_x + copy_run_length > copy_clip_right_plus1 )
              {
                copy_clip_overflow = screen_x + copy_run_length - copy_clip_right - 1;
                copy_run_length = 1 - (screen_x - copy_clip_right);
              }
LABEL_86:
              copy_run_remaining = copy_run_length;
              v172 = copy_write_cursor;
              do
              {
                copy_chunk_length = copy_run_remaining;
                if ( copy_run_remaining > 0x7FFFFFFF )
                  copy_chunk_length = 0x7FFFFFFF;
                if ( copy_chunk_length > (*(int (**)(void))(*(_DWORD *)v172 + 8))() )
                  copy_chunk_length = (*(int (**)(void))(*(_DWORD *)v172 + 8))();
                if ( copy_chunk_length > (*(int (**)(void))(g_ActiveBlitCursor + 8))() )
                  copy_chunk_length = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
                (*(void (**)(void))(g_ActiveBlitCursor + 16))();
                v78 = run_pixel_ptr;
                v119 = (unsigned __int8 *)(*(int (__thiscall **)(unsigned int))(*(_DWORD *)v172 + 16))(copy_chunk_length);
                qmemcpy(v119, v78, v79);
                (*(void (**)(void))(*(_DWORD *)v172 + 12))();
                run_pixel_ptr += copy_chunk_length;
                (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, copy_chunk_length);
                copy_run_remaining -= copy_chunk_length;
              }
              while ( copy_run_remaining );
              v80 = copy_clip_overflow;
              if ( copy_clip_overflow )
              {
                (*(void (**)(void))(*(_DWORD *)copy_write_cursor + 12))();
                v81 = g_ActiveBlitCursor;
                v82 = v80;
                run_pixel_ptr += v80;
                goto LABEL_96;
              }
            }
          }
LABEL_97:
          if ( vars6 )
            rle_cursor = vars6 + 1;
          else
            rle_cursor += run_length;
          goto LABEL_180;
        }
        if ( sprite_format != 1 )
          goto LABEL_180;
        if ( BYTE2(blend_mode_flags) )
          App_RequestQuit((int)aDlxmemscreen_0);
        fill_x_saved = screen_x;
        fill_clip_overflow = 0;
        fill_run_length = run_byte;
        fill_write_cursor = write_cursor;
        if ( fill_clip_ctx[5] )
        {
          if ( screen_y < (int)fill_clip_ctx[2] || screen_y > (int)fill_clip_ctx[4] || screen_x > (int)fill_clip_ctx[3] || run_byte + screen_x < (int)(fill_clip_ctx[1] + 1) )
          {
            (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
            (*(void (__fastcall **)(int, _DWORD))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, run_length);
            (*(void (__fastcall **)(int, _DWORD))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, run_length);
            goto LABEL_180;
          }
          v114 = fill_clip_ctx[1];
          if ( (int)v114 > screen_x )
          {
            v115 = &v114[-screen_x];
            (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
            (*(void (**)(void))(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, unsigned __int8 *))(g_ActiveBlitCursor + 12))(v116 - (_DWORD)v115, v115);
            fill_run_length = v117;
          }
          if ( (int)(fill_clip_ctx[3] + 1) < (int)(fill_run_length + fill_x_saved) )
          {
            fill_clip_overflow = fill_run_length + fill_x_saved - (_DWORD)fill_clip_ctx[3] - 1;
            fill_run_length = 1 - (fill_x_saved - (_DWORD)fill_clip_ctx[3]);
          }
        }
        fill_ctx_ref = fill_clip_ctx;
        do
        {
          if ( fill_run_length > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(fill_run_length) )
            v104 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          v105 = (*(int (__fastcall **)(int))(*(_DWORD *)fill_write_cursor + 8))(v104);
          if ( v106 > v105 )
            v106 = (*(int (**)(void))(*(_DWORD *)fill_write_cursor + 8))();
          v107 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v106);
          if ( v108 > v107 )
            v108 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v108);
          (*(void (**)(void))(g_ActiveBlitCursor + 16))();
          (*(void (**)(void))(*(_DWORD *)fill_write_cursor + 16))();
          memset_(v109, **fill_ctx_ref);
          (*(void (__fastcall **)(int, int))(*(_DWORD *)fill_write_cursor + 12))(v110, v110);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v111, v111);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v112, v112);
          fill_run_length -= v113;
        }
        while ( fill_run_length );
        if ( fill_clip_overflow )
        {
          (*(void (**)(void))(*(_DWORD *)fill_write_cursor + 12))();
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, fill_clip_overflow);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, fill_clip_overflow);
        }
      }
      else
      {
        transparent_run_length = run_byte & 0x7F;
        run_length = run_byte & 0x7F;
        if ( BYTE2(transparent_flags) )
        {
          (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
          goto LABEL_180;
        }
        *(_DWORD *)&_10E = write_cursor;
        skip_remaining = transparent_run_length;
        skip_clip_overflow = 0;
        if ( skip_clip_enabled )
        {
          if ( screen_y < skip_clip_top || screen_y > skip_clip_bottom || screen_x > skip_clip_right || screen_x + transparent_run_length < skip_clip_left_plus1 )
          {
            (*(void (**)(void))(**(_DWORD **)&_10E + 12))();
            (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_remaining);
            (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_remaining);
            goto LABEL_180;
          }
          if ( skip_clip_left > screen_x )
          {
            (*(void (**)(void))(*(_DWORD *)write_cursor + 12))();
            (*(void (**)(void))(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v73 - (skip_clip_left - screen_x), skip_clip_left - screen_x);
            skip_remaining = v74;
          }
          if ( (int)(screen_x + skip_remaining) > skip_clip_right_plus1 )
          {
            skip_clip_overflow = screen_x + skip_remaining - skip_clip_right - 1;
            skip_remaining = 1 - (screen_x - skip_clip_right);
          }
        }
        v62 = *(_DWORD *)&_10E;
        do
        {
          if ( skip_remaining > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(skip_remaining) )
            v63 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          v64 = (*(int (__fastcall **)(int))(*(_DWORD *)v62 + 8))(v63);
          if ( v65 > v64 )
            v65 = (*(int (**)(void))(*(_DWORD *)v62 + 8))();
          v66 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v65);
          if ( v67 > v66 )
            v67 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v67);
          (*(void (**)(void))(g_ActiveBlitCursor + 16))();
          (*(void (**)(void))(*(_DWORD *)v62 + 16))();
          memset_(v68, (unsigned __int8)g_Render_BackgroundColorIndex);
          (*(void (__fastcall **)(int, int))(*(_DWORD *)v62 + 12))(v69, v69);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v70, v70);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v71, v71);
          skip_remaining -= v72;
        }
        while ( skip_remaining );
        if ( skip_clip_overflow )
        {
          (*(void (**)(void))(**(_DWORD **)&_10E + 12))();
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_clip_overflow);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_clip_overflow);
        }
      }
LABEL_180:
      vars2 += run_length;
      screen_x += run_length;
    }
    v52 = (*(int (**)(void))(*(_DWORD *)write_cursor + 4))();
    (*(void (__fastcall **)(int, int))(v53 + 12))(v53, v52 - (unsigned __int16)*sprite_header);
    ++row_index;
    ++screen_y;
  }
  if ( fill_clip_ctx )
    j__nfree_();
  if ( blend_clip_ctx )
    j__nfree_();
  if ( offset_clip_ctx )
    j__nfree_();
  result = (**(int (***)(void))write_cursor)();
  if ( offscreen_surface )
  {
    result = Render_FillRect(offscreen_surface, &g_MainRenderDevice, 0, 0, *sprite_header - 1, sprite_header[1] - 1, var2, draw_y_saved);
    if ( offscreen_surface )
      return (*(int (**)(void))offscreen_surface[46])();
  }
  return result;
}
// 402E80: variables would overlap: ^132.2 and ^132.4
// 402E80: variables would overlap: ^134.4(retaddr) and ^136.4
// 402FAF: inconsistent variable size for '^1A0.16'
// 402FD5: inconsistent variable size for '^1A0.16'
// 402FDB: inconsistent variable size for '^1A0.16'
// 40300C: inconsistent variable size for '^1A0.16'
// 40302F: inconsistent variable size for '^1A0.16'
// 403035: inconsistent variable size for '^1A0.16'
// 40307B: inconsistent variable size for '^1A0.16'
// 403083: inconsistent variable size for '^1A0.16'
// 4030AC: inconsistent variable size for '^1A0.16'
// 4030EB: inconsistent variable size for '^1A0.16'
// 4030F3: inconsistent variable size for '^1A0.16'
// 40311C: inconsistent variable size for '^1A0.16'
// 403237: inconsistent variable size for '^1A0.16'
// 403240: inconsistent variable size for '^1A0.16'
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 50ED94: using guessed type int (*off_50ED94[5])();
// 51D018: using guessed type int g_MousePresentAtStartup;
// 51D4B8: using guessed type int dword_51D4B8;
// 51E265: using guessed type char byte_51E265;
// 51F28C: using guessed type char byte_51F28C;

//----- (00403D70) --------------------------------------------------------
_DWORD * Render_CreateSurface(int surface_addr, __int16 width, __int16 height)
{
  _DWORD *surface;
  unsigned int pixel_count;

  surface = Render_ConstructSurfaceObject(surface_addr, width, height);
  surface[46] = g_Surface_RawBuffer8Vtable;
  pixel_count = (unsigned __int16)*(unsigned __int16 *)surface * (unsigned __int16)*((unsigned __int16 *)surface + 1);
  surface[1] = (unsigned int)nmalloc_(pixel_count, 4);
  if ( !surface[1] )
  {
    Debug_Log(0, 0, pixel_count, (int)aNotEnoughMemor);
    App_RequestQuit((int)aNotEnoughMem_0);
  }
  memset((void *)(uintptr_t)(unsigned int)surface[1], 0, pixel_count);
  if ( !surface[1] )
    App_RequestQuit((int)aNotEnoughFreeM);
  return surface;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 50EE24: using guessed type int (*off_50EE24[5])();

//----- (00403E50) --------------------------------------------------------
int  Surface_DestructRawBuffer(int surface, char flags)
{
  int result; // eax

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, &g_SurfaceRawBuffer_DtorArrayTag);
    j_j__nfree_();
    return surface;
  }
  *(_DWORD *)(surface + 184) = g_Surface_RawBuffer8Vtable;
  nfree_(*(_DWORD *)(surface + 4));
  *(_DWORD *)(surface + 4) = 0;
  result = Surface_Destruct(surface + 8) - 8;
  if ( (flags & 2) != 0 )
  {
    j__nfree_();
    return result;
  }
  return result;
}
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 50EE24: using guessed type int (*off_50EE24[5])();

//----- (00403EB0) --------------------------------------------------------
_DWORD * Surface_ConstructRegionViewA(int x, int y, DWORD context)
{
  _DWORD *result; // eax
  int x_offset; // edx
  unsigned __int16 *surface; // ecx
  unsigned __int16 row_pitch; // si
  int row_offset; // ebx
  int pixel_base; // ecx

  result = (_DWORD *)Mem_Alloc(12, x, y, context);
  if ( result )
  {
    row_pitch = *surface;
    row_offset = *surface * y;
    pixel_base = *((_DWORD *)surface + 1);
    *result = g_RenderSurface_BlitCursorVtable;
    result[2] = row_pitch;
    result[1] = x_offset + row_offset + pixel_base;
  }
  return result;
}
// 403EC6: variable 'v6' is possibly undefined
// 403EDA: variable 'v5' is possibly undefined
// 50ED94: using guessed type int (*off_50ED94[5])();

//----- (00403EF0) --------------------------------------------------------
_DWORD * Surface_ConstructRegionViewB(int x, int y, DWORD context)
{
  _DWORD *result; // eax
  int x_offset; // edx
  unsigned __int16 *surface; // ecx
  unsigned __int16 row_pitch; // si
  int row_offset; // ebx
  int pixel_base; // ecx

  result = (_DWORD *)Mem_Alloc(12, x, y, context);
  if ( result )
  {
    row_pitch = *surface;
    row_offset = *surface * y;
    pixel_base = *((_DWORD *)surface + 1);
    *result = g_RenderSurface_BlitCursorVtable;
    result[2] = row_pitch;
    result[1] = x_offset + row_offset + pixel_base;
  }
  return result;
}
// 403F06: variable 'v6' is possibly undefined
// 403F1A: variable 'v5' is possibly undefined
// 50ED94: using guessed type int (*off_50ED94[5])();

//----- (00403F30) --------------------------------------------------------
int  Surface_SetPixel8(unsigned __int16 *surface, int x, char color, int y)
{
  int result; // eax

  result = *surface * y + *((_DWORD *)surface + 1);
  *(_BYTE *)(x + result) = color;
  return result;
}

//----- (00403F50) --------------------------------------------------------
int  Surface_GetPixel8(unsigned __int16 *surface, int x, int y)
{
  return *(unsigned __int8 *)(x + y * *surface + *((_DWORD *)surface + 1));
}

//----- (00403F70) --------------------------------------------------------
_BYTE * Surface_DrawDashedLine(
        unsigned __int16 *surface,
        unsigned __int16 x_start,
        unsigned __int16 x_end,
        int y_start,
        unsigned __int16 y_end,
        int color_flags)
{
  int v6; // ecx
  unsigned __int16 pitch; // di
  _BYTE *result; // eax
  unsigned __int16 v9; // bx
  unsigned __int16 v10; // dx
  unsigned __int16 v11; // dx

  v6 = color_flags;
  pitch = *surface;
  result = (_BYTE *)(x_start + *((_DWORD *)surface + 1) + *surface * (unsigned __int16)y_start);
  if ( (color_flags & 0x100) != 0 )
  {
    if ( (_WORD)y_start == y_end )
    {
      while ( 1 )
      {
        v9 = x_start++;
        if ( v9 >= x_end )
          break;
        if ( (x_start & 3) == 3 )
          *result = color_flags;
        ++result;
      }
    }
    else
    {
      while ( 1 )
      {
        v10 = y_start;
        LOWORD(y_start) = y_start + 1;
        if ( v10 >= y_end )
          break;
        if ( (y_start & 3) == 3 )
          *result = color_flags;
        result += pitch;
      }
    }
  }
  else if ( (_WORD)y_start == y_end )
  {
    BYTE1(v6) = 0;
    return (_BYTE *)memset_(v6, (unsigned __int8)color_flags);
  }
  else
  {
    while ( 1 )
    {
      v11 = y_start++;
      if ( v11 > y_end )
        break;
      *result = color_flags;
      result += pitch;
    }
  }
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00404040) --------------------------------------------------------
int  Surface_DrawRectOutline(
        unsigned __int16 *surface,
        unsigned __int16 x1,
        unsigned __int16 x2,
        int y1,
        unsigned __int16 y2,
        unsigned __int8 color)
{
  unsigned int width; // di
  unsigned int height;
  unsigned int left; // dx
  unsigned int right; // cx
  unsigned int top; // bx
  unsigned int bottom; // stack
  unsigned int y; // esi
  unsigned char *pixels;
  unsigned char *row_left;

  width = *surface;
  height = *((unsigned __int16 *)surface + 1);
  pixels = (unsigned char *)(uintptr_t)(unsigned int)*((_DWORD *)surface + 1);
  left = x1;
  right = x2;
  top = (unsigned __int16)y1;
  bottom = y2;
  if ( !pixels || !width || !height || left > right || top > bottom || left >= width || top >= height )
    return 0;
  if ( right >= width )
    right = width - 1;
  if ( bottom >= height )
    bottom = height - 1;
  if ( right > left + 1 )
    memset(pixels + top * width + left + 1, color, right - left - 1);
  for ( y = top; y < bottom; ++y )
  {
    row_left = pixels + y * width + left;
    row_left[0] = color;
    row_left[right - left] = color;
  }
  memset(pixels + bottom * width + left, color, right - left + 1);
  return (int)(uintptr_t)(pixels + bottom * width + left);
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004040F0) --------------------------------------------------------
unsigned __int16 * Surface_FillVerticalSpan(
        unsigned __int16 *result,
        int x,
        unsigned __int16 y_start,
        unsigned __int16 y_end,
        unsigned __int8 color)
{
  unsigned __int16 *surface_ptr; // edi
  int row_index; // esi
  int v7; // ecx
  int row_addr; // ecx

  surface_ptr = result;
  row_index = y_start;
  v7 = y_start * *result + *((_DWORD *)result + 1);
  HIWORD(x) = 0;
  while ( 1 )
  {
    row_addr = x + v7;
    if ( row_index > y_end )
      break;
    result = (unsigned __int16 *)memset_(row_addr, color);
    x = *surface_ptr;
    ++row_index;
  }
  return result;
}
// 404117: variable 'v7' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00404160) --------------------------------------------------------
__int16  Surface_FillCheckerPattern(
        unsigned __int16 *surface,
        int x_start,
        int x_end,
        int y_start,
        int y_end,
        char color)
{
  int row_y; // esi
  int row_base; // eax
  int i; // edi
  int col_x; // edx
  int j; // eax

  row_y = y_start;
  row_base = *((_DWORD *)surface + 1) + y_start * *surface;
  for ( i = row_base + x_start; row_y <= y_end; i += *surface )
  {
    col_x = x_start;
    for ( j = i + (row_y & 1); col_x <= x_end; *(_BYTE *)(j - 2) = color )
    {
      j += 2;
      col_x += 2;
    }
    LOWORD(row_base) = *surface;
    ++row_y;
  }
  return row_base;
}

//----- (004041D0) --------------------------------------------------------
_DWORD * Render_ConstructScratchSurface(int surface_addr, unsigned __int16 width, DWORD companion_flag, __int16 height)
{
  int width_saved; // edi
  _DWORD *result; // eax
  _DWORD *constructed_surface; // esi
  _DWORD *companion_surface; // eax
  _DWORD *allocated_companion; // eax
  int render_context; // edx

  width_saved = width;
  result = Render_ConstructSurfaceObject(surface_addr, width, height);
  constructed_surface = result;
  result[46] = g_ScratchSurface_Vtable;
  if ( companion_flag )
  {
    companion_surface = 0;
    allocated_companion = (_DWORD *)Mem_Alloc(176, 0, height, companion_flag);
    render_context = g_RenderContext;
    if ( allocated_companion && render_context )
      companion_surface = Surface_ConstructWithSurface(allocated_companion, (_DWORD *)(uintptr_t)(unsigned int)render_context, height, width_saved);
    if ( allocated_companion && !companion_surface )
      nfree_((int)(uintptr_t)allocated_companion);
    constructed_surface[48] = companion_surface != 0;
    constructed_surface[47] = companion_surface;
    return constructed_surface;
  }
  else
  {
    result[47] = 0;
    result[48] = 0;
  }
  return result;
}
// 50EE74: using guessed type int (*off_50EE74[5])();
// 51D584: using guessed type int dword_51D584;

//----- (00404240) --------------------------------------------------------
int  Render_DestructScratchSurface(_DWORD *surface, char flags)
{
  int owned_buffer; // edx
  int result; // eax

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, &g_ScratchSurface_DtorArrayTag);
    j_j__nfree_();
    return (int)surface;
  }
  owned_buffer = surface[47];
  surface[46] = g_ScratchSurface_Vtable;
  if ( owned_buffer && surface[48] )
  {
    Surface_Destruct(owned_buffer);
    j__nfree_();
  }
  result = Surface_Destruct((int)(surface + 2)) - 8;
  if ( (flags & 2) != 0 )
  {
    j__nfree_();
    return result;
  }
  return result;
}
// 40426C: conditional instruction was optimized away because edx.4!=0
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50EE74: using guessed type int (*off_50EE74[5])();

//----- (004042C0) --------------------------------------------------------
int  Surface_ConstructLockedRegionView(int surface, int x, int y, DWORD context)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 60))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = y * v10 + x + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 4042DA: variable 'v6' is possibly undefined
// 4042FF: variable 'v9' is possibly undefined
// 404311: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404330) --------------------------------------------------------
int  Surface_ConstructPitchRegionView(int surface, int x, int y, DWORD context)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 64))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = y * v10 + x + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 40434A: variable 'v6' is possibly undefined
// 40436F: variable 'v9' is possibly undefined
// 404381: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (004043A0) --------------------------------------------------------
int  Surface_DrawPix(int surface, int y)
{
  int write_view; // esi
  int v3; // ecx
  int v4; // edx
  char v5; // cl

  write_view = (*(int (**)(void))(*(_DWORD *)(surface + 184) + 64))();
  Surface_LockWithRestore(write_view, v3);
  Surface_SetPixelByte(write_view, v4, v5, y);
  return Surface_Unlock(write_view);
}
// 4043AC: variable 'v3' is possibly undefined
// 4043B3: variable 'v4' is possibly undefined
// 4043B3: variable 'v5' is possibly undefined

//----- (004043D0) --------------------------------------------------------
int  Surface_GetPix(int surface, int a2, int y)
{
  int read_view; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  unsigned __int8 pixel_value; // dl

  read_view = (*(int (__cdecl **)(int))(*(_DWORD *)(surface + 184) + 60))(a2);
  Surface_LockWithRestore(read_view, read_view);
  Surface_GetPixelByte(v5, v4, y);
  Surface_Unlock(v6);
  return pixel_value;
}
// 4043E3: variable 'v5' is possibly undefined
// 4043E3: variable 'v4' is possibly undefined
// 4043EC: variable 'v6' is possibly undefined
// 4043F3: variable 'v7' is possibly undefined

//----- (00404400) --------------------------------------------------------
unsigned __int16  Surface_DrawLine(
        int surface,
        unsigned __int16 x_start,
        unsigned __int16 x_end,
        unsigned __int16 y_start,
        unsigned __int16 y_end,
        __int16 color_flags)
{
  unsigned __int16 y_cursor; // di
  unsigned __int16 result; // ax
  unsigned __int16 v9; // dx
  unsigned __int16 v10; // dx
  __int64 v11; // rax
  int v12; // ecx
  __int64 v13; // rax
  int v14; // ecx
  __int64 v15; // rax
  int v16; // ecx
  unsigned __int16 x_cursor; // [esp+Ch] [ebp-10h]

  x_cursor = x_start;
  y_cursor = y_start;
  result = (unsigned __int8)color_flags;
  if ( (color_flags & 0x100) != 0 )
  {
    if ( y_start == y_end )
    {
      while ( 1 )
      {
        v9 = x_cursor;
        result = ++x_cursor;
        if ( v9 >= x_end )
          break;
        if ( (result & 3) == 3 )
        {
          (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)(surface + 184) + 12))((unsigned __int8)color_flags, result);
        }
        else
        {
          while ( 1 )
          {
            v10 = y_cursor++;
            if ( v10 >= y_end )
              break;
            if ( (y_cursor & 3) == 3 )
              (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)(surface + 184) + 12))((unsigned __int8)color_flags, x_cursor);
          }
        }
      }
    }
  }
  else if ( y_start == y_end )
  {
    v13 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(surface + 184) + 64))(y_end, x_start);
    return Render_DrawHorizontalRun(v13, SHIDWORD(v13), v14, x_end, color_flags);
  }
  else if ( x_end == x_start )
  {
    v11 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(surface + 184) + 64))(x_start, y_start);
    return Render_DrawVerticalRun(v11, SHIDWORD(v11), v12, y_end, color_flags);
  }
  else
  {
    v15 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(surface + 184) + 64))(x_end, x_start);
    return Render_DrawLine(v15, SHIDWORD(v15), v16, y_start, y_end, color_flags);
  }
  return result;
}
// 4044E4: variable 'v12' is possibly undefined
// 404515: variable 'v14' is possibly undefined
// 404548: variable 'v16' is possibly undefined

//----- (00404560) --------------------------------------------------------
int  Surface_DrawRect(
        int surface,
        unsigned __int16 x1,
        unsigned __int16 x2,
        unsigned __int16 y1,
        unsigned __int16 y2,
        char color)
{
  __int64 v6; // rax
  int v7; // ecx

  v6 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(surface + 184) + 64))(x1, y1);
  return Surface_DrawRectBorderByte(v6, SHIDWORD(v6), v7, x2, y2, color);
}
// 40458C: variable 'v7' is possibly undefined

//----- (004045A0) --------------------------------------------------------
int  Surface_DrawBox(
        int surface,
        unsigned __int16 x1,
        unsigned __int16 x2,
        unsigned __int16 y1,
        unsigned __int16 y2,
        unsigned __int8 color)
{
  __int64 v6; // rax
  int v7; // ecx

  v6 = ((__int64 (__fastcall *)(unsigned int, _DWORD))*(_DWORD *)(*(_DWORD *)(surface + 184) + 64))((unsigned int)x2 + 1, x1);
  return Surface_FillRectColor(v6, SHIDWORD(v6), v7, y1, y2 + 1, color);
}
// 4045CE: variable 'v7' is possibly undefined

//----- (004045E0) --------------------------------------------------------
int  Surface_DotBox(int result, int x1, int x2, int y1, int y2, int color)
{
  int surface; // edi
  int j; // esi
  int i; // [esp+8h] [ebp-10h]

  surface = result;
  for ( i = y1; i <= y2; i += 2 )
  {
    for ( j = x1; j <= x2; j += 2 )
    {
      (*(void (__fastcall **)(int, int))(*(_DWORD *)(surface + 184) + 12))(color, j);
      result = x2;
    }
  }
  return result;
}
// 4045E0: could not find valid save-restore pair for ebx

//----- (00404640) --------------------------------------------------------
int  Render_UnlockBackbuffer(int surface)
{
  int write_handle; // eax

  write_handle = RenderSurface_InvokeSlot64((_DWORD *)(uintptr_t)(unsigned int)surface);
  return Render_FillSurfaceSolidColor(write_handle, 0, 0);
}

//----- (00404660) --------------------------------------------------------
int  Surface_ConstructBackbufferInstance(int surface_addr)
{
  int palette_array;

  palette_array = (int)Render_ConstructScratchSurface(surface_addr, 0x280u, 0, 480) + 0xDC;
  *(_DWORD *)(palette_array - 24) = 0;
  *(_DWORD *)(palette_array - 20) = 1;
  *(_DWORD *)(palette_array - 16) = 1;
  *(_DWORD *)(palette_array - 12) = 0;
  *(_DWORD *)(palette_array - 8) = 0;
  *(_DWORD *)(palette_array - 4) = 0;
  palette_array = _wcpp_4_ctor_array__(palette_array, 256);
  *(_DWORD *)(palette_array - 36) = g_Surface_Vtable;
  return palette_array - 0xDC;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 50EEC4: using guessed type int (*off_50EEC4[5])();

//----- (004046D0) --------------------------------------------------------
int  Render_SetPixelFormat(int render_device, int a2, int bits_per_pixel, DWORD context)
{
  LPVOID *dd_context; // eax
  unsigned __int16 screen_width; // bx
  _DWORD *screen_height; // ecx
  int v11; // eax
  int v12; // ecx
  _DWORD *Surface; // eax
  int pixel_format; // edi
  int gray_level; // edx
  int entry_offset; // eax
  int result; // eax
  HRESULT hr;
  int render_context;
  int surface_handle;
  int palette_handle;
  _DWORD *v18; // [esp-8h] [ebp-41Ch]
  DWORD v19; // [esp+0h] [ebp-414h]
  _BYTE palette_entries[1040]; // [esp+4h] [ebp-410h] BYREF

  *(_DWORD *)(render_device + 212) = bits_per_pixel;
  dd_context = (LPVOID *)Mem_Alloc(44, a2, bits_per_pixel, context);
  if ( dd_context )
    dd_context = (LPVOID *)Render_ZeroDirectDrawObjectFields(dd_context);
  v19 = 0;
  v18 = *(_DWORD **)(render_device + 212);
  screen_width = *(_WORD *)render_device;
  screen_height = (_DWORD *)*(unsigned __int16 *)(render_device + 2);
  *(_DWORD *)(render_device + 196) = dd_context;
  Render_InitDirectDrawFullscreenMode(dd_context, (_DWORD *)(uintptr_t)a2, screen_height, (_DWORD *)screen_width, v18, 0, v19);
  if ( *(_DWORD *)(render_device + 212) == 8 )
    *(_DWORD *)(render_device + 188) = *(_DWORD *)(*(_DWORD *)(render_device + 196) + 4);
  else
    *(_DWORD *)(render_device + 188) = 0;
  v11 = *(_DWORD *)(render_device + 196);
  *(_DWORD *)(render_device + 192) = 0;
  Render_FillSurfaceSolidColor(*(_DWORD *)(v11 + 4), 0, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v12, screen_width, context);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, *(_WORD *)render_device, *(_WORD *)(render_device + 2));
  pixel_format = *(_DWORD *)(render_device + 212);
  *(_DWORD *)(render_device + 208) = Surface;
  if ( pixel_format == 8 )
  {
    gray_level = 0;
    entry_offset = 0;
    do
    {
      entry_offset += 4;
      palette_entries[entry_offset - 4] = gray_level;
      palette_entries[entry_offset - 3] = gray_level;
      palette_entries[entry_offset - 2] = gray_level++;
      palette_entries[entry_offset - 1] = 0;
    }
    while ( gray_level < 256 );
    render_context = *(_DWORD *)(render_device + 196);
    if ( render_context )
    {
      hr = Compat_DirectDraw_CreatePalette(
             (LPDIRECTDRAW)(uintptr_t)(unsigned int)*(_DWORD *)render_context,
             68,
             palette_entries,
             (void *)(uintptr_t)(unsigned int)(render_context + 16));
      if ( hr )
        Render_HandleDirectDrawFatalError(hr, 0);
    }
    surface_handle = 0;
    palette_handle = 0;
    if ( *(_DWORD *)(render_device + 188) )
      surface_handle = *(_DWORD *)(*(_DWORD *)(render_device + 188) + 164);
    if ( render_context )
      palette_handle = *(_DWORD *)(render_context + 16);
    if ( surface_handle && palette_handle )
    {
      hr = Compat_DirectDrawSurface_SetPalette(
             (LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)surface_handle,
             (void *)(uintptr_t)(unsigned int)palette_handle);
      if ( hr )
        Render_HandleDirectDrawFatalError(hr, 0);
    }
    return Palette_ApplyWithBrightnessOffset((int *)render_device, (const void *)(render_device + 220));
  }
  else
  {
    result = *(_DWORD *)(render_device + 196);
    *(_DWORD *)(result + 16) = 0;
  }
  return result;
}
// 404750: variable 'v12' is possibly undefined

static void Compat_InvokeNativeComMethod0(int object_handle, unsigned int x86_vtable_offset)
{
  uintptr_t *vtable;
  void (*method)(void *);

  if ( !object_handle )
    return;
  vtable = *(uintptr_t **)(uintptr_t)(unsigned int)object_handle;
  if ( !vtable )
    return;
  method = (void (*)(void *))(uintptr_t)vtable[x86_vtable_offset / 4];
  if ( method )
    method((void *)(uintptr_t)(unsigned int)object_handle);
}

static void Compat_InvokeCompactSurfaceDestructor(int surface_handle, int flags)
{
  int vtable;
  int (*destructor)(int, int);

  if ( !surface_handle )
    return;
  vtable = *(_DWORD *)(surface_handle + 184);
  if ( !vtable )
    return;
  destructor = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(vtable);
  if ( destructor )
    destructor(surface_handle, flags);
}

static int Compat_DirectDrawSurfaceHandleIsLost(int surface_handle)
{
  int direct_draw_surface;

  if ( !surface_handle )
    return 0;
  direct_draw_surface = *(_DWORD *)(surface_handle + 164);
  if ( !direct_draw_surface )
    return 0;
  return Compat_DirectDrawSurface_IsLost((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)direct_draw_surface);
}

//----- (00404830) --------------------------------------------------------
int  Render_BeginModeSwitch(_DWORD *render_device)
{
  _DWORD *dd_context; // edx
  _DWORD *dd_object; // eax
  int result; // eax

  dd_context = (_DWORD *)render_device[49];
  if ( dd_context && *dd_context )
    Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)*dd_context, hWnd, 11);
  dd_object = (_DWORD *)render_device[49];
  render_device[47] = 0;
  if ( dd_object )
  {
    Render_DestroyDirectDrawObject(dd_object);
    j__nfree_();
  }
  result = render_device[52];
  if ( result )
    Compat_InvokeCompactSurfaceDestructor(result, 2);
  render_device[49] = 0;
  render_device[52] = 0;
  return result;
}

//----- (004048B0) --------------------------------------------------------
int  Render_EndModeSwitch(int result, char a2, DWORD a3)
{
  int render_device; // esi
  int v5; // eax
  int v6; // ecx
  int cursor_visible; // edi
  int surface_handle;

  render_device = result;
  if ( *(_DWORD *)(result + 208) )
  {
    result = *(_DWORD *)(result + 212);
    if ( result == 8 )
    {
      surface_handle = RenderSurface_InvokeSlot60((_DWORD *)(uintptr_t)(unsigned int)render_device);
      result = surface_handle;
      if ( surface_handle )
      {
        v5 = surface_handle;
        result = Compat_DirectDrawSurfaceHandleIsLost(surface_handle);
        if ( !result )
        {
          Debug_Log(v6, a2, a3, (int)aRestorescreenc);
          cursor_visible = g_CursorOverlayPresented;
          if ( g_CursorOverlayPresented )
            Render_Pump();
          result = Render_FillRect(
                     (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(render_device + 208),
                     (_DWORD *)render_device,
                     0,
                     0,
                     *(_WORD *)render_device - 1,
                     *(_WORD *)(render_device + 2) - 1,
                     0,
                     0);
          if ( cursor_visible )
            result = Render_Present((int)g_RenderState);
          *(_DWORD *)(render_device + 200) = 0;
        }
      }
    }
  }
  return result;
}
// 404900: variable 'v6' is possibly undefined
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00404970) --------------------------------------------------------
_DWORD * Render_BlitSurface(_DWORD *result, int force_flag, char a3, DWORD a4)
{
  _DWORD *copy_target;
  int pixel_format;
  int render_device; // esi
  int saved_handle; // eax
  int v7; // ecx
  int cursor_visible; // edi
  int surface_handle;

  render_device = (int)result;
  copy_target = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(render_device + 208);
  pixel_format = *(_DWORD *)(render_device + 212);
  if ( result[50] || force_flag )
  {
    if ( copy_target )
    {
      if ( pixel_format != 8 )
      {
        cursor_visible = g_CursorOverlayPresented;
        if ( g_CursorOverlayPresented )
        {
          g_CursorOverlayPresented = 0;
          saved_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
          Render_FillRect(
            *(_DWORD **)((int)&g_RenderState + 8),
            0,
            0,
            0,
            *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 12) - 1,
            *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 16) - 1,
            *(unsigned __int16 *)&g_RenderState,
            *(unsigned __int16 *)((int)&g_RenderState + 4));
          Render_SetResourceHandle((int)&g_MainRenderDevice, saved_handle);
        }
        result = (_DWORD *)Render_FillRect(
                             (_DWORD *)render_device,
                             copy_target,
                             0,
                             0,
                             *(_WORD *)render_device - 1,
                             *(_WORD *)(render_device + 2) - 1,
                             0,
                             0);
        if ( cursor_visible )
          result = (_DWORD *)Render_Present((int)&g_RenderState);
        *(_DWORD *)(render_device + 200) = 0;
      }
      else
      {
        surface_handle = RenderSurface_InvokeSlot60((_DWORD *)(uintptr_t)(unsigned int)render_device);
        result = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
        if ( surface_handle )
        {
          saved_handle = surface_handle;
          result = (_DWORD *)(uintptr_t)(unsigned int)Compat_DirectDrawSurfaceHandleIsLost(surface_handle);
          if ( !result )
          {
            Debug_Log(v7, a3, a4, (int)aRemsc);
            cursor_visible = g_CursorOverlayPresented;
            if ( g_CursorOverlayPresented )
            {
              g_CursorOverlayPresented = 0;
              saved_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
              Render_FillRect(
                *(_DWORD **)((int)&g_RenderState + 8),
                0,
                0,
                0,
                *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 12) - 1,
                *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 16) - 1,
                *(unsigned __int16 *)&g_RenderState,
                *(unsigned __int16 *)((int)&g_RenderState + 4));
              Render_SetResourceHandle((int)&g_MainRenderDevice, saved_handle);
            }
            result = (_DWORD *)Render_FillRect(
                                 (_DWORD *)render_device,
                                 copy_target,
                                 0,
                                 0,
                                 *(_WORD *)render_device - 1,
                                 *(_WORD *)(render_device + 2) - 1,
                                 0,
                                 0);
            if ( cursor_visible )
              result = (_DWORD *)Render_Present((int)&g_RenderState);
            *(_DWORD *)(render_device + 200) = 0;
          }
        }
      }
    }
  }
  return result;
}
// 4049D0: variable 'v7' is possibly undefined
// 544D10: using guessed type int dword_544D10;

//----- (00404A40) --------------------------------------------------------
int  Surface_SwapDirtyTrackingFlag(int surface, int new_flag)
{
  int old_flag; // edx

  old_flag = *(_DWORD *)(surface + 204);
  *(_DWORD *)(surface + 204) = new_flag;
  return old_flag;
}

//----- (00404A60) --------------------------------------------------------
int * Render_ReleaseTempSurface(int *result)
{
  int *render_device; // ebx
  int companion_surface; // edx

  render_device = result;
  companion_surface = result[47];
  if ( companion_surface )
  {
    (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(companion_surface + 164) + 124))(
      *(_DWORD *)(companion_surface + 164),
      *(_DWORD *)(result[49] + 16));
    return (int *)Palette_ApplyWithBrightnessOffset(render_device, render_device + 55);
  }
  return result;
}

//----- (00404AA0) --------------------------------------------------------
int  Surface_BeginPixelRead(int surface, int x, int y, DWORD context)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 60))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = y * v10 + x + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 404ABA: variable 'v6' is possibly undefined
// 404ADF: variable 'v9' is possibly undefined
// 404AF1: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404B10) --------------------------------------------------------
int  Surface_BeginPixelWrite(int surface, int x, int y, DWORD context)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 64))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = y * v10 + x + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 404B2A: variable 'v6' is possibly undefined
// 404B4F: variable 'v9' is possibly undefined
// 404B61: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404B80) --------------------------------------------------------
int  Surface_DrawPixAndMarkDirty(int surface, int y)
{
  int result; // eax

  result = Surface_DrawPix(surface, y);
  *(_DWORD *)(surface + 200) = 1;
  return result;
}

//----- (00404BA0) --------------------------------------------------------
int  Render_SaveBackbuffer(int render_device)
{
  _DWORD surface_wrapper;
  _DWORD surface_device;
  uintptr_t *surface_vtable;

  if ( render_device == (int)&g_MainRenderDevice )
  {
    Compat_PresentPrimaryIndexedSurfaceToPlatform();
    return 0;
  }
  surface_wrapper = *(_DWORD *)(render_device + 196);
  if ( !surface_wrapper || (surface_wrapper & 3) != 0 )
    return 0;
  surface_device = *(_DWORD *)(uintptr_t)surface_wrapper;
  if ( !surface_device )
    return 0;
  surface_vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)surface_device;
  if ( !surface_vtable || !surface_vtable[11] )
    return 0;
  return ((int (__stdcall *)(_DWORD, int, _DWORD))(uintptr_t)surface_vtable[11])(surface_device, 1, 0);
}

//----- (00404BC0) --------------------------------------------------------
int  Palette_SetBrightnessOffset(int result, int brightness_offset)
{
  *(_DWORD *)(result + 216) = brightness_offset;
  return result;
}

//----- (00404C80) --------------------------------------------------------
int  Palette_ApplyWithBrightnessOffset(int *render_device, const void *new_palette)
{
  unsigned char *palette_bytes;
  unsigned int converted_palette[256];
  int base_color;
  int channel_value;
  unsigned int palette_index;

  palette_bytes = (unsigned char *)(render_device + 55);
  qmemcpy(palette_bytes, new_palette, 0x400u);
  base_color = render_device[54];
  for ( palette_index = 0; palette_index < 256; ++palette_index )
  {
    unsigned int converted_entry;

    channel_value = base_color + palette_bytes[4 * palette_index];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > 255 )
      channel_value = 255;
    converted_entry = (unsigned char)channel_value;

    channel_value = base_color + palette_bytes[4 * palette_index + 1];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > 255 )
      channel_value = 255;
    converted_entry |= (unsigned int)(unsigned char)channel_value << 8;

    channel_value = base_color + palette_bytes[4 * palette_index + 2];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > 255 )
      channel_value = 255;
    converted_entry |= (unsigned int)(unsigned char)channel_value << 16;

    converted_palette[palette_index] = converted_entry;
  }
  if ( render_device == (int *)&g_MainRenderDevice || !render_device[49] || (render_device[49] & 3) != 0 )
    return 0;
  return IO_StreamWrite(render_device[49], 0, (int)converted_palette, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00404D90) --------------------------------------------------------
int  Palette_ApplyDefaultPalette(int *render_device)
{
  return Palette_ApplyWithBrightnessOffset(render_device, &g_DefaultPaletteTable);
}

//----- (00404DA0) --------------------------------------------------------
int * Palette_CrossfadeToTarget(int *result, unsigned __int8 *target_palette, signed int step_count)
{
  int *render_device; // ebp
  signed int i; // esi
  int step; // ecx

  render_device = result;
  for ( i = 0; i <= step_count; result = (int *)Palette_CrossfadeStep(render_device, target_palette, step, step_count) )
    step = i++;
  return result;
}

//----- (00404DE0) --------------------------------------------------------
int  Palette_CrossfadeStep(int *render_device, unsigned __int8 *target_palette, int step, signed int step_count)
{
  unsigned __int8 *target_ptr; // ecx
  int *write_ptr; // esi
  unsigned __int8 *source_ptr; // ebx
  int blended_entry; // [esp+18h] [ebp-14h]

  if ( !step )
    qmemcpy(&g_PaletteCrossfadeSourceBuffer, render_device + 55, 0x400u);
  target_ptr = target_palette;
  write_ptr = render_device + 55;
  source_ptr = (unsigned __int8 *)&g_PaletteCrossfadeSourceBuffer;
  do
  {
    LOBYTE(blended_entry) = (int)step * (*target_ptr - *source_ptr) / step_count + *source_ptr;
    ++write_ptr;
    BYTE1(blended_entry) = (int)step * (target_ptr[1] - source_ptr[1]) / step_count + source_ptr[1];
    HIWORD(blended_entry) = (unsigned __int8)(source_ptr[2] + (int)step * (target_ptr[2] - source_ptr[2]) / step_count);
    source_ptr += 4;
    target_ptr += 4;
    *(write_ptr - 1) = blended_entry;
  }
  while ( target_ptr != target_palette + 1024 );
  Palette_ApplyWithBrightnessOffset(render_device, render_device + 55);
  return Render_SaveBackbuffer((int)render_device);
}

//----- (00404F20) --------------------------------------------------------
int  Palette_FadeOutToBlack(int *render_device, signed int step_count)
{
  _DWORD *device_palette; // esi
  int result; // eax
  int step; // ebx
  unsigned __int8 *source_ptr; // ecx
  _DWORD *write_ptr; // esi
  int v8; // edx
  __int64 v9; // rtt
  int v10; // edx
  unsigned int source_palette[256]; // [esp+0h] [ebp-428h] BYREF
  int *device; // [esp+400h] [ebp-28h] BYREF
  int packed_entry; // [esp+404h] [ebp-24h]
  _DWORD *write_base; // [esp+408h] [ebp-20h]
  unsigned __int8 blue_value; // [esp+40Ch] [ebp-1Ch]
  char green_value; // [esp+410h] [ebp-18h]

  device = render_device;
  device_palette = render_device + 55;
  qmemcpy(source_palette, device_palette, sizeof(source_palette));
  result = 0;
  step = step_count;
  if ( step_count >= 0 )
  {
    write_base = device_palette;
    do
    {
      source_ptr = (unsigned __int8 *)source_palette;
      write_ptr = write_base;
      do
      {
        v8 = step * source_ptr[1];
        blue_value = step * source_ptr[2] / step_count;
        v9 = v8;
        v10 = step * *source_ptr;
        green_value = v9 / step_count;
        LOBYTE(packed_entry) = v10 / step_count;
        BYTE1(packed_entry) = green_value;
        HIWORD(packed_entry) = blue_value;
        ++write_ptr;
        source_ptr += 4;
        *(write_ptr - 1) = packed_entry;
      }
      while ( source_ptr != (unsigned __int8 *)source_palette + sizeof(source_palette) );
      Palette_ApplyWithBrightnessOffset(device, write_base);
      --step;
      result = Render_SaveBackbuffer((int)device);
    }
    while ( step >= 0 );
  }
  return result;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00405020) --------------------------------------------------------
int * Palette_FadeInFromBlack(int *result, unsigned __int8 *target_palette, signed int step_count)
{
  signed int step; // ecx
  unsigned __int8 *target_ptr; // ebx
  _DWORD *write_ptr; // edi
  int *device; // [esp+0h] [ebp-28h]
  _DWORD *device_palette; // [esp+8h] [ebp-20h]
  int packed_entry; // [esp+Ch] [ebp-1Ch]

  device = result;
  step = 0;
  if ( step_count >= 0 )
  {
    device_palette = result + 55;
    do
    {
      target_ptr = target_palette;
      write_ptr = device_palette;
      do
      {
        LOBYTE(packed_entry) = step * *target_ptr / step_count;
        BYTE1(packed_entry) = step * target_ptr[1] / step_count;
        HIWORD(packed_entry) = (unsigned __int8)(step * target_ptr[2] / step_count);
        ++write_ptr;
        target_ptr += 4;
        *(write_ptr - 1) = packed_entry;
      }
      while ( target_ptr != target_palette + 1024 );
      Palette_ApplyWithBrightnessOffset(device, device_palette);
      ++step;
      result = (int *)Render_SaveBackbuffer((int)device);
    }
    while ( step <= step_count );
  }
  return result;
}
// 405086: variable 'v4' is possibly undefined

//----- (004050F0) --------------------------------------------------------
void * Video_EnterGreyscaleTransition(int *render_device, int a2, char a3, DWORD a4)
{
  _DWORD *Surface; // eax
  int v6; // ecx
  int remap_index; // ebp
  int candidate_index; // eax
  unsigned __int8 red_value; // bh
  unsigned __int8 best_value; // bl
  unsigned __int8 *candidate_ptr; // edx
  int distance; // ecx
  int best_distance; // esi
  int candidate_value; // edi
  int candidate_distance; // ecx
  int i; // eax
  _BYTE *pixel_ptr; // ecx
  unsigned int ramp_cursor; // esi
  unsigned int ramp_end; // edi
  int gray_accum; // ecx
  int gray_level; // eax
  int pixel_index; // esi
  _BYTE *pixel_cursor; // ecx
  void *result; // eax
  void *saved_render_device; // [esp+0h] [ebp-28h]
  _DWORD *temp_surface; // [esp+8h] [ebp-20h]
  unsigned __int8 *palette_cursor; // [esp+Ch] [ebp-1Ch]
  char best_index; // [esp+10h] [ebp-18h]

  saved_render_device = g_RenderDevice;
  Surface = (_DWORD *)Mem_Alloc(188, a2, a3, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  temp_surface = Surface;
  g_RenderDevice = Surface;
  Render_FillRect(render_device, Surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  LoadPalPCX((int)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
  Palette_CrossfadeToTarget(render_device, g_PaletteScratchSurfaceBuffer, 20);
  remap_index = 0;
  palette_cursor = g_PaletteScratchSurfaceBuffer;
  do
  {
    candidate_index = 32;
    red_value = *palette_cursor;
    best_value = -1;
    candidate_ptr = &g_PaletteScratchSurfaceBuffer[128];
    best_index = -1;
    do
    {
      distance = red_value - best_value;
      if ( distance <= 0 )
        distance = best_value - red_value;
      best_distance = distance;
      candidate_value = *candidate_ptr;
      candidate_distance = red_value - candidate_value;
      if ( candidate_distance <= 0 )
        candidate_distance = candidate_value - red_value;
      if ( best_distance > candidate_distance )
      {
        best_index = candidate_index;
        best_value = *candidate_ptr;
      }
      ++candidate_index;
      candidate_ptr += 4;
    }
    while ( candidate_index < 256 );
    g_PaletteShadowRemapTableMinus1[++remap_index] = best_index;
    palette_cursor += 4;
  }
  while ( remap_index < 32 );
  for ( i = 0; i < 307200; ++i )
  {
    pixel_ptr = (_BYTE *)(i + temp_surface[1]);
    if ( (unsigned __int8)*pixel_ptr <= 0x1Fu )
      *pixel_ptr = g_Video_LowColorRemapTable[(unsigned __int8)*pixel_ptr];
  }
  ramp_cursor = (unsigned int)g_PaletteScratchSurfaceBuffer;
  ramp_end = (unsigned int)&g_PaletteScratchSurfaceBuffer[128];
  gray_accum = 0;
  do
  {
    gray_level = gray_accum / 31;
    ramp_cursor += 4;
    *(_BYTE *)(ramp_cursor - 4) = gray_accum / 31;
    *(_BYTE *)(ramp_cursor - 3) = gray_accum / 31;
    gray_accum += 255;
    *(_BYTE *)(ramp_cursor - 2) = gray_level;
  }
  while ( ramp_cursor != ramp_end );
  pixel_index = ramp_end ^ ramp_cursor;
  pixel_cursor = (_BYTE *)temp_surface[1];
  do
  {
    if ( (unsigned __int8)*pixel_cursor > 0x1Fu )
      *pixel_cursor = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*pixel_cursor] >> 3;
    ++pixel_index;
    ++pixel_cursor;
  }
  while ( pixel_index < 307200 );
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  (void)g_RenderDevice;
  if ( temp_surface )
    j__nfree_(temp_surface);
  result = saved_render_device;
  g_RenderDevice = saved_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (00405330) --------------------------------------------------------
void * Video_ExitGreyscaleTransition(int *render_device, unsigned __int8 *target_palette, int a3, char a4, DWORD a5)
{
  _DWORD *Surface; // eax
  void *current_render_device; // ebp
  _DWORD *snapshot_surface; // esi
  int i; // edx
  _BYTE *pixel_ptr; // ebx
  _BYTE *pixel_cursor; // ecx
  int j; // ebx
  int k; // edx
  _BYTE *pixel_byte_ptr; // ebx
  unsigned int pixel_value; // ecx
  int v16; // ecx
  void *result; // eax
  void *saved_render_device; // [esp+4h] [ebp-18h]

  saved_render_device = g_RenderDevice;
  Surface = (_DWORD *)Mem_Alloc(188, a3, a4, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  current_render_device = g_RenderDevice;
  snapshot_surface = Surface;
  Render_FillRect(g_RenderDevice, Surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  for ( i = 0; i < 307200; ++i )
  {
    pixel_ptr = (_BYTE *)(i + snapshot_surface[1]);
    if ( (unsigned __int8)*pixel_ptr <= 0x1Fu )
      *pixel_ptr = g_Video_LowColorRemapTable[(unsigned __int8)*pixel_ptr];
  }
  pixel_cursor = (_BYTE *)snapshot_surface[1];
  for ( j = 0; j < 307200; ++j )
  {
    if ( (unsigned __int8)*pixel_cursor > 0x1Fu )
      *pixel_cursor = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*pixel_cursor] >> 3;
    ++pixel_cursor;
  }
  (void)pixel_cursor;
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  Render_FillRect(g_RenderDevice, snapshot_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  for ( k = 0; k < 307200; ++k )
  {
    pixel_byte_ptr = (_BYTE *)(k + snapshot_surface[1]);
    pixel_value = (unsigned __int8)*pixel_byte_ptr;
    if ( pixel_value <= 0x1F )
      *pixel_byte_ptr = g_Video_LowColorRemapTable[pixel_value];
  }
  (void)pixel_value;
  LoadPalPCX((int)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  Render_FillRect(g_RenderDevice, snapshot_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  (void)snapshot_surface;
  Palette_CrossfadeToTarget(render_device, target_palette, 20);
  if ( snapshot_surface )
    j__nfree_(snapshot_surface);
  result = saved_render_device;
  g_RenderDevice = saved_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (00405510) --------------------------------------------------------
int  Sprite_DrawSimpleTrackingOffset(
        int sprite,
        int x,
        int y,
        int a4,
        int a5,
        int a6,
        int blend_ratio,
        unsigned __int8 draw_flag)
{
  g_Palette_BlendRatio = blend_ratio;
  (void)a4;
  (void)a5;
  (void)a6;
  return Compat_RenderDeviceDrawMenuSprite(x, y, sprite, draw_flag);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519A14: using guessed type int dword_519A14;

//----- (00405560) --------------------------------------------------------
int  Sprite_DrawSimpleIgnoringRect(
        int sprite,
        int x,
        int y,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned __int8 draw_flag)
{
  (void)a4;
  (void)a5;
  (void)a6;
  (void)a7;
  (void)a8;
  (void)a9;
  (void)a10;
  return Compat_RenderDeviceDrawMenuSprite(x, y, sprite, draw_flag);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (004055C0) --------------------------------------------------------
void __noreturn Surface_GetReadIncrNotImplemented()
{
  App_RequestQuit((int)aGetreadincrZap);
}

//----- (004055D0) --------------------------------------------------------
void __noreturn Surface_GetWriteIncrNotImplemented()
{
  App_RequestQuit((int)aGetwriteincrZa);
}

//----- (004055E0) --------------------------------------------------------
void __noreturn Surface_DrawPixNotImplemented()
{
  App_RequestQuit((int)aDrawpixZapisNa);
}

//----- (004055F0) --------------------------------------------------------
void __noreturn Surface_GetPixNotImplemented()
{
  App_RequestQuit((int)aGetpixZapisNaE);
}

//----- (00405600) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawLineNotImplemented(int a1, int a2)
{
  App_RequestQuit((int)aDrawlineZapisN);
}

//----- (00405610) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawRectNotImplemented(int a1, int a2)
{
  App_RequestQuit((int)aDrawrectZapisN);
}

//----- (00405620) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawBoxNotImplemented(int a1, int a2)
{
  App_RequestQuit((int)aDrawboxZapisNa);
}

//----- (00405630) --------------------------------------------------------
void __stdcall __noreturn Surface_DotBoxNotImplemented(int a1, int a2)
{
  App_RequestQuit((int)aDotboxZapisNaE);
}

//----- (00405640) --------------------------------------------------------
int Surface_GetReadIncrZero()
{
  return 0;
}

//----- (00405650) --------------------------------------------------------
int Surface_GetWriteIncrZero()
{
  return 0;
}

//----- (00405660) --------------------------------------------------------
int  Surface_GetReadIncrFromStride(int surface)
{
  return *(_DWORD *)(surface + 188);
}

//----- (00405670) --------------------------------------------------------
int  Surface_GetWriteIncrFromStride(int surface)
{
  return *(_DWORD *)(surface + 188);
}

//----- (00405680) --------------------------------------------------------
int  Surface_GetWriteIncrAndMarkDirty(_DWORD *surface)
{
  if ( surface[51] )
    surface[50] = 1;
  return surface[47];
}

//----- (004056B0) --------------------------------------------------------
int  Surface_Destroy(_DWORD *surface, char flags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, &g_Surface_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = Render_DestructScratchSurface(surface, 1);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 4056E0: variable 'v4' is possibly undefined
// 4056EA: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (004056F0) --------------------------------------------------------
int  SurfaceCursor_Destroy(int result, char flags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_SurfaceCursor_DtorArrayTag);
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
// 405719: variable 'v4' is possibly undefined
// 405710: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00405720) --------------------------------------------------------
signed int SurfaceCursor_GetIncrUnbounded()
{
  return 0x7FFFFFFF;
}

//----- (00405730) --------------------------------------------------------
signed int SurfaceCursor_GetExtentUnbounded()
{
  return 0x7FFFFFFF;
}

//----- (00405750) --------------------------------------------------------
int SurfaceCursor_GetOffsetZero()
{
  return 0;
}

//----- (00405760) --------------------------------------------------------
int  RenderSurface_Destroy(int surface, char flags)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, &g_RenderSurface_DtorArrayTag);
    j_j__nfree_();
    return v5;
  }
  else
  {
    v3 = Surface_Destruct(surface + 8);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v6;
    }
    else
    {
      return v3 - 8;
    }
  }
}
// 405791: variable 'v5' is possibly undefined
// 40579D: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (004057B0) --------------------------------------------------------
int  RenderSurface_GetBlitCursorRowStride(int cursor)
{
  return *(_DWORD *)(cursor + 8);
}

//----- (004057C0) --------------------------------------------------------
signed int RenderSurface_GetBlitCursorCapacity()
{
  return 0x7FFFFFFF;
}

//----- (004057D0) --------------------------------------------------------
int  RenderSurface_AdvanceBlitCursor(int result, int delta)
{
  *(_DWORD *)(result + 4) += delta;
  return result;
}

//----- (004057E0) --------------------------------------------------------
int  RenderSurface_GetBlitCursorPosition(int cursor)
{
  return *(_DWORD *)(cursor + 4);
}

//----- (004057F0) --------------------------------------------------------
int  RenderSurface_DestroyLinkedBlitCursor(_DWORD *cursor, char flags)
{
  int v2; // ecx
  char v3; // dl
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(cursor, &g_LinkedBlitCursor_DtorArrayTag);
    j_j__nfree_();
    return v5;
  }
  else
  {
    *cursor = g_RenderSurface_LinkedBlitCursorVtable;
    Surface_Unlock(cursor[1]);
    if ( (v3 & 2) != 0 )
      j__nfree_();
    return v2;
  }
}
// 405806: variable 'v3' is possibly undefined
// 40580B: variable 'v2' is possibly undefined
// 40581E: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00405830) --------------------------------------------------------
signed int RenderSurface_GetLinkedBlitCursorCapacity()
{
  return 0x7FFFFFFF;
}

//----- (00405840) --------------------------------------------------------
int  RenderSurface_AdvanceLinkedBlitCursor(int result, int delta)
{
  *(_DWORD *)(result + 8) += delta;
  return result;
}

//----- (00405850) --------------------------------------------------------
int  RenderSurface_GetLinkedBlitCursorPosition(int cursor)
{
  return *(_DWORD *)(cursor + 8);
}

//----- (00405860) --------------------------------------------------------
int  RenderSurface_GetLinkedSurfaceBuffer(int cursor)
{
  return *(_DWORD *)(*(_DWORD *)(cursor + 4) + 72);
}

//----- (00405870) --------------------------------------------------------
int  RenderSurface_DestroyBlitCursor(int result, char flags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_BlitCursor_DtorArrayTag);
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
// 405899: variable 'v4' is possibly undefined
// 405890: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (004058A0) --------------------------------------------------------
_DWORD * RenderSurface_ConstructNullBlitCursor(_DWORD *result)
{
  *result = g_NullBlitCursor_Vtable;
  return result;
}
// 50EF24: using guessed type int (*off_50EF24[5])();

//----- (004058C0) --------------------------------------------------------
int __thiscall RenderSurface_CloneInternalArray(void *this)
{
  return _wcpp_4_copy_array__(this);
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (004058E0) --------------------------------------------------------
_BYTE * RenderSurface_CopyFourByteFields(_BYTE *result, _BYTE *source)
{
  *result = *source;
  result[1] = source[1];
  result[2] = source[2];
  result[3] = source[3];
  return result;
}

//----- (00405900) --------------------------------------------------------
_DWORD * RenderSurface_ConstructFullScreenBuffer(int surface_addr)
{
  return Render_ConstructSurfaceObject(surface_addr, 640, SCREEN_HEIGHT);
}

//----- (00405920) --------------------------------------------------------
int  DLXSpriteSet_ReleaseAndClear(int *sprite_set_slot)
{
  int result; // eax
  uintptr_t method_table;

  result = *sprite_set_slot;
  if ( result )
  {
    method_table = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)result + 4108);
    if ( method_table )
      result = ((int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)method_table)(result, 2);
  }
  *sprite_set_slot = 0;
  return result;
}

//----- (00405950) --------------------------------------------------------
int  DLXSprite_ReleaseAndClear(int *sprite_slot)
{
  int *v1; // ecx
  int result; // eax

  v1 = sprite_slot;
  result = *sprite_slot;
  if ( result )
  {
    DLXSprite_Destroy(result);
    result = j__nfree_();
  }
  *v1 = 0;
  return result;
}
// 405959: variable 'v1' is possibly undefined

//----- (00405980) --------------------------------------------------------
int  Res_ProbeGfxFileExists(CHAR *file_name, int a2, DWORD context, int a4)
{
  unsigned int path_len; // kr04_4
  int open_handle;
  CHAR path[264]; // [esp-110h] [ebp-110h] BYREF

  qmemcpy(path, aGfx_1, 0xFFu);
  path_len = strlen(path) + 1;
  strcat(path, file_name);
  open_handle = IO_FOpen(path, (unsigned __int8 *)aRb_0, ~path_len, context);
  if ( !open_handle )
    return 0;
  fclose_(open_handle);
  return 0;
}
// 4059DC: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00405A00) --------------------------------------------------------
int  DLX_OpenArchive(char *archive_name, int a2)
{
  char *path_cursor; // edi
  char v4; // al
  char v5; // al
  int result; // eax
  int v7; // ecx
  char path[256]; // [esp-100h] [ebp-114h] BYREF
  int query_handle[5]; // [esp+0h] [ebp-14h] BYREF

  query_handle[4] = a2;
  qmemcpy(path, aGfx_4, 0xFFu);
  path_cursor = &path[strlen(path)];
  do
  {
    v4 = *archive_name;
    *path_cursor = *archive_name;
    if ( !v4 )
      break;
    v5 = archive_name[1];
    archive_name += 2;
    path_cursor[1] = v5;
    path_cursor += 2;
  }
  while ( v5 );
  result = FileSystem_ResolveReadPath(path, 0);
  query_handle[0] = result;
  if ( result )
  {
    Compat_FileSystemQueryRelease(v7, query_handle);
    return 1;
  }
  return result;
}
// 405A6C: variable 'v7' is possibly undefined

//----- (00405A90) --------------------------------------------------------
_DWORD * DLXSpriteSet_Load(_DWORD *sprite_set, const void *file_name)
{
  const char *resource_name;
  int data_size;
  int entry_index;
  int entry_end_offset;
  int entry_size;
  char path[256]; // [esp+0h] [ebp-11Ch] BYREF
  int query_handle; // [esp+100h] [ebp-1Ch] BYREF

  resource_name = file_name ? (const char *)file_name : "";
  sprite_set[1024] = 0;
  sprite_set[1027] = &g_DLXSpriteSet_Vtable;
  Debug_Log(63, 0, (DWORD)resource_name, (int)aDlxspritesetDl);
  strcpy(path, aGfx);
  strcat(path, resource_name);
  query_handle = FileSystem_ResolveReadPath(path, 0);
  sprite_set[1026] = IO_QueryVTableStreamSize(query_handle);
  if ( !query_handle || sprite_set[1026] <= 4096 )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(
        stderr,
        "[dlx] load failed path=%s size=%d caller=%p\n",
        path,
        sprite_set[1026],
        __builtin_return_address(0));
    App_RequestQuit((int)aIOCouldnTOpenF);
    return sprite_set;
  }
  Compat_QueryRead(query_handle, g_DlxSpriteSetOffsetTable, 4096);
  data_size = sprite_set[1026] - 4096;
  sprite_set[1024] = (unsigned int)nmalloc_(data_size, 4);
  if ( !sprite_set[1024] )
  {
    Debug_Log(0, 0, data_size, (int)aNotEnoughMem_1);
    App_RequestQuit((int)aNotEnoughMem_2);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)sprite_set[1024], data_size);
  entry_index = 0;
  while ( entry_index < 1023 && g_DlxSpriteSetOffsetTable[entry_index] )
  {
    entry_end_offset = g_DlxDirEntryEndOffsetTable[entry_index];
    if ( entry_end_offset )
      entry_size = entry_end_offset - g_DlxSpriteSetOffsetTable[entry_index];
    else
      entry_size = IO_QueryVTableStreamSize(query_handle) - g_DlxSpriteSetOffsetTable[entry_index];
    sprite_set[entry_index] = Mem_Alloc(22, entry_index, entry_size, (DWORD)sprite_set);
    if ( sprite_set[entry_index] )
      sprite_set[entry_index] = DLXSprite_ConstructFromBuffer(sprite_set[entry_index], g_DlxSpriteSetOffsetTable[entry_index] + sprite_set[1024] - 4096, entry_size);
    ++entry_index;
  }
  sprite_set[1025] = entry_index;
  Compat_FileSystemQueryRelease(entry_index, &query_handle);
  return sprite_set;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 50F044: using guessed type int (*off_50F044)();
// 51F290: using guessed type int dword_51F290[];
// 51F294: using guessed type int dword_51F294[1022];

//----- (00405C60) --------------------------------------------------------
int * DLXSpriteSet_Destroy(int *sprite_set, char flags, int a3)
{
  int entry_index; // ebx
  int *entry_ptr; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a3, &g_DLXSpriteSet_DtorArrayTag);
    j_j__nfree_();
    return sprite_set;
  }
  sprite_set[1027] = (int)&g_DLXSpriteSet_Vtable;
  entry_index = 0;
  if ( sprite_set[1025] > 0 )
  {
    entry_ptr = sprite_set;
    do
    {
      if ( *entry_ptr )
      {
        DLXSprite_Destroy(*entry_ptr);
        j__nfree_();
      }
      ++entry_index;
      ++entry_ptr;
    }
    while ( entry_index < sprite_set[1025] );
  }
  if ( sprite_set[1024] )
    j__nfree_();
  if ( (flags & 2) == 0 )
    return sprite_set;
  j__nfree_();
  return sprite_set;
}
// 405CA6: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50F044: using guessed type int (*off_50F044)();

//----- (00405D00) --------------------------------------------------------
int  DLXSpriteSet_ConstructCopy(int *sprite_set, DWORD *source_set, signed int entry_count)
{
  int v3; // ecx

  sprite_set[1027] = (int)&g_DLXSpriteSet_Vtable;
  DLXSpriteSet_CopyEntriesFrom(sprite_set, source_set, (int)sprite_set, entry_count);
  return v3;
}
// 405D12: variable 'v3' is possibly undefined
// 50F044: using guessed type int (*off_50F044)();

//----- (00405D20) --------------------------------------------------------
int * DLXSpriteSet_CopyEntriesFrom(int *sprite_set, DWORD *source_set, int a3, signed int entry_count)
{
  int entry_index; // ecx
  int v7; // edx
  int *dest_entry; // esi
  int new_sprite; // eax

  DLXSpriteSet_Destroy(sprite_set, 0, a3);
  sprite_set[1026] = source_set[1026];
  sprite_set[1025] = source_set[1025];
  entry_index = 0;
  v7 = sprite_set[1025];
  sprite_set[1024] = 0;
  if ( v7 > 0 )
  {
    dest_entry = sprite_set;
    do
    {
      if ( *source_set )
      {
        new_sprite = Mem_Alloc(22, entry_index, (char)source_set, entry_count);
        if ( new_sprite )
          new_sprite = DLXSprite_ConstructOwningCopy(new_sprite, *source_set);
        *dest_entry = new_sprite;
      }
      else
      {
        sprite_set[entry_index] = 0;
      }
      ++source_set;
      ++entry_index;
      entry_count = sprite_set[1025];
      ++dest_entry;
    }
    while ( entry_index < entry_count );
  }
  return sprite_set;
}
// 405D73: variable 'v6' is possibly undefined

//----- (00405DB0) --------------------------------------------------------
int  DLXSpriteSet_Save(int *sprite_set, int a2, char a3)
{
  int v4; // ecx
  char *v5; // edi
  char *v6; // esi
  char *v7; // edx
  char *v8; // esi
  unsigned int prefix_length; // kr04_4
  char *append_cursor; // edi
  char v11; // al
  char v12; // al
  int open_handle; // eax
  int data_offset; // edx
  int file_handle; // esi
  int entry_index; // eax
  DWORD entry_cursor; // ecx
  int write_index; // ecx
  int *sprite_slot; // ebx
  int v20; // ecx
  char *v22; // [esp-4h] [ebp-118h]
  char path[276]; // [esp+0h] [ebp-114h] BYREF

  HIBYTE(v22) = HIBYTE(a2);
  Debug_Log(63, a3, (DWORD)sprite_set, (int)aDlxspritesetSa);
  qmemcpy(path, aGfx_2, 4 * v4);
  v6 = &aGfx_2[4 * v4];
  v5 = &path[4 * v4];
  *(_WORD *)v5 = *(_WORD *)v6;
  v5[2] = v6[2];
  v8 = v7;
  v22 = path;
  prefix_length = strlen(path) + 1;
  append_cursor = &path[prefix_length - 1];
  do
  {
    v11 = *v8;
    *append_cursor = *v8;
    if ( !v11 )
      break;
    v12 = v8[1];
    v8 += 2;
    append_cursor[1] = v12;
    append_cursor += 2;
  }
  while ( v12 );
  open_handle = IO_FOpen(path, (unsigned __int8 *)aWb, ~prefix_length, (DWORD)sprite_set);
  data_offset = 4096;
  file_handle = open_handle;
  entry_index = 0;
  if ( sprite_set[1025] > 0 )
  {
    entry_cursor = (DWORD)sprite_set;
    do
    {
      g_DlxSpriteSetOffsetTable[entry_index++] = data_offset;
      data_offset += *(_DWORD *)(*(_DWORD *)entry_cursor + 14);
      entry_cursor += 4;
    }
    while ( entry_index < sprite_set[1025] );
  }
  g_DlxDirTotalDataOffset = data_offset;
  fwrite_(g_DlxSpriteSetOffsetTable, 4096, file_handle, 1);
  write_index = 0;
  if ( sprite_set[1025] > 0 )
  {
    sprite_slot = sprite_set;
    do
    {
      DLXSprite_Save(*sprite_slot, file_handle);
      write_index = v20 + 1;
      ++sprite_slot;
    }
    while ( write_index < sprite_set[1025] );
  }
  return fclose_(write_index);
}
// 405DD9: variable 'v4' is possibly undefined
// 405DE0: variable 'v7' is possibly undefined
// 405E83: variable 'v20' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51F290: using guessed type int dword_51F290[];
// 52028C: using guessed type int dword_52028C;

//----- (00405EC0) --------------------------------------------------------
int  DLX_GetSpriteForChar(int sprite_set, int char_index)
{
  return *(_DWORD *)(sprite_set + 4 * char_index);
}

//----- (00405ED0) --------------------------------------------------------
int  DLXSpriteSet_GetLastCharIndex(int sprite_set)
{
  LOWORD(sprite_set) = *(_WORD *)(sprite_set + 4100);
  return sprite_set - 1;
}

//----- (00405EE0) --------------------------------------------------------
__int16  DLX_GetSpriteWidth(int sprite_set, unsigned __int16 char_index)
{
  return *(_WORD *)(DLX_GetSpriteForChar(sprite_set, char_index) + 2);
}

//----- (00405EF0) --------------------------------------------------------
__int16  DLX_GetSpriteHeight(int sprite_set, unsigned __int16 char_index)
{
  return *(_WORD *)DLX_GetSpriteForChar(sprite_set, char_index);
}

//----- (00405F00) --------------------------------------------------------
char  DLXSpriteSet_DrawText(int sprite_set, int char_index, int dest_palette, unsigned __int8 *source_palette)
{
  int palette_index;
  int candidate_index;
  int best_index;
  int best_distance;
  int distance;
  int remapped_sprite;
  unsigned __int8 *source_entry;
  unsigned __int8 *candidate_palette_entry;
  unsigned int target_red;
  unsigned int target_green;
  unsigned int target_blue;
  unsigned __int16 last_char_index;
  char remap_table[256]; // [esp+0h] [ebp-12Ch] BYREF

  (void)Time_Now(dest_palette, char_index);
  source_entry = source_palette;
  for ( palette_index = 0; palette_index < 256; ++palette_index )
  {
    best_distance = 768;
    best_index = 0;
    target_red = source_entry[0];
    target_green = source_entry[1];
    target_blue = source_entry[2];
    candidate_index = 1;
    candidate_palette_entry = (unsigned __int8 *)(uintptr_t)(unsigned int)(dest_palette + 4);
    while ( candidate_index < 256 )
    {
      distance = (int)target_red - candidate_palette_entry[0];
      if ( distance < 0 )
        distance = -distance;
      distance += abs((int)target_green - candidate_palette_entry[1]);
      distance += abs((int)target_blue - candidate_palette_entry[2]);
      if ( distance < best_distance )
      {
        best_distance = distance;
        best_index = candidate_index;
      }
      ++candidate_index;
      candidate_palette_entry += 4;
    }
    remap_table[palette_index] = best_index;
    source_entry += 4;
  }
  if ( char_index == -1 )
  {
    last_char_index = (unsigned __int16)DLXSpriteSet_GetLastCharIndex(sprite_set);
    for ( remapped_sprite = 0; remapped_sprite <= (int)last_char_index; ++remapped_sprite )
    {
      DLXSprite_RemapPalette(DLX_GetSpriteForChar(sprite_set, remapped_sprite), (unsigned __int8 *)remap_table);
    }
    return (char)last_char_index;
  }
  return DLXSprite_RemapPalette(DLX_GetSpriteForChar(sprite_set, char_index), (unsigned __int8 *)remap_table);
}

//----- (004060A0) --------------------------------------------------------
int  DLXSpriteSet_DrawFormattedText(DWORD sprite_set, int char_index, int dest_palette, const char *palette_name)
{
  unsigned __int8 *loaded_palette; // eax

  loaded_palette = (unsigned __int8 *)Mem_Alloc(1024, (int)(uintptr_t)palette_name, 0, sprite_set);
  if ( loaded_palette )
    loaded_palette = (unsigned __int8 *)Palette_LoadFromQueryHandle((intptr_t)loaded_palette, (intptr_t)palette_name);
  DLXSpriteSet_DrawText(sprite_set, char_index, dest_palette, loaded_palette);
  return j__nfree_();
}

//----- (004060E0) --------------------------------------------------------
DWORD  DLXSprite_LoadCachedEntry(DWORD sprite, char *file_name, int entry_index)
{
  int query_handle; // [esp+100h] [ebp-1Ch] BYREF
  int entry_offset; // [esp+104h] [ebp-18h]
  int entry_end_offset; // [esp+108h] [ebp-14h]
  int payload_size;
  unsigned int payload_handle;
  char path[256]; // [esp+0h] [ebp-11Ch] BYREF

  *(_DWORD *)(sprite + 10) = 0;
  strcpy(path, aGfx_3);
  strcat(path, file_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  if ( !query_handle )
    return sprite;
  Compat_QueryRead(query_handle, g_DlxDirectoryEntryStartOffsets, 4096);
  entry_offset = g_DlxDirectoryEntryStartOffsets[entry_index];
  if ( g_DlxDirectoryEntryEndOffsets[entry_index] )
    entry_end_offset = g_DlxDirectoryEntryEndOffsets[entry_index];
  else
    entry_end_offset = IO_QueryVTableStreamSize(query_handle);
  *(_DWORD *)(sprite + 14) = entry_end_offset - entry_offset;
  Compat_QuerySeek(query_handle, entry_offset);
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)sprite, 10);
  payload_size = *(_DWORD *)(sprite + 14) - 10;
  payload_handle = (unsigned int)nmalloc_(payload_size, 4);
  *(_DWORD *)(sprite + 10) = payload_handle;
  if ( !*(_DWORD *)(sprite + 10) )
  {
    Debug_Log(0, 10, payload_size, (int)aNotEnoughMem_7);
    App_RequestQuit((int)aNotEnoughMem_8);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)payload_handle, payload_size);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  return sprite;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 51E288: using guessed type int dword_51E288[];
// 51E28C: using guessed type int dword_51E28C[1024];

//----- (00406260) --------------------------------------------------------
int  DLXSprite_ConstructFromBuffer(int result, int source_buffer, int data_size)
{
  *(_DWORD *)(result + 18) = 0;
  *(_DWORD *)(result + 14) = data_size;
  qmemcpy((void *)result, (const void *)source_buffer, 8u);
  qmemcpy((void *)(result + 8), (const void *)(source_buffer + 8), 2u);
  *(_DWORD *)(result + 10) = source_buffer + 10;
  return result;
}

//----- (00406350) --------------------------------------------------------
int  DLXSprite_ConstructOwningCopy(int sprite, DWORD source_sprite)
{
  int v2; // ecx

  *(_DWORD *)(sprite + 10) = 0;
  *(_DWORD *)(sprite + 18) = 1;
  DLXSprite_CopyFrom(sprite, source_sprite);
  return v2;
}
// 406366: variable 'v2' is possibly undefined

//----- (00406370) --------------------------------------------------------
int  DLXSprite_Destroy(int result)
{
  int v2; // ecx

  if ( *(_DWORD *)(result + 10) )
  {
    if ( *(_DWORD *)(result + 18) )
    {
      j__nfree_();
      return v2;
    }
  }
  return result;
}
// 40638B: variable 'v2' is possibly undefined

//----- (00406390) --------------------------------------------------------
int  DLXSprite_CopyFrom(int sprite, DWORD source_sprite)
{
  unsigned int v6; // ecx
  int v7; // edx
  unsigned int v8; // ecx
  _DWORD alloc_buffer[6]; // [esp+0h] [ebp-18h] BYREF

  DLXSprite_Destroy(sprite);
  qmemcpy((void *)sprite, (const void *)source_sprite, v6);
  *(_DWORD *)(sprite + 14) = *(_DWORD *)(source_sprite + 14);
  *(_DWORD *)(sprite + 18) = 1;
  alloc_buffer[0] = nmalloc_(4, v7);
  qmemcpy((void *)(sprite + 10), alloc_buffer, v8);
  if ( !*(_DWORD *)(sprite + 10) )
  {
    Debug_Log(0, sprite, source_sprite, (int)aNotEnoughMe_15);
    App_RequestQuit((int)aNotEnoughMe_16);
  }
  qmemcpy(*(void **)(sprite + 10), *(const void **)(source_sprite + 10), *(_DWORD *)(sprite + 14) - 10);
  return sprite;
}
// 4063B2: variable 'v6' is possibly undefined
// 4063D9: variable 'v7' is possibly undefined
// 4063E7: variable 'v8' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);

//----- (00406460) --------------------------------------------------------
int  DLXSprite_Save(int sprite, int file_handle)
{
  fwrite_((const void *)sprite, 10, file_handle, 1);
  return fwrite_(*(const void **)(sprite + 10), *(_DWORD *)(sprite + 14) - 10, file_handle, 1);
}

//----- (004064A0) --------------------------------------------------------
char  DLXSprite_RemapPalette(int sprite, const unsigned __int8 *remap_table)
{
  unsigned __int16 *sprite_header; // esi
  _BYTE *pixel_cursor; // edx
  int x; // ecx
  int pixel_value; // ebx
  int i; // [esp+0h] [ebp-18h]

  sprite_header = (unsigned __int16 *)sprite;
  pixel_cursor = (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)(sprite + 10);
  if ( *(_WORD *)(sprite + 4) )
    App_RequestQuit((int)aConvertsprUnsu);
  for ( i = 0; sprite_header[1] > i; ++i )
  {
    x = 0;
    while ( x < *sprite_header )
    {
      LOBYTE(sprite) = *pixel_cursor++;
      if ( (sprite & 0x80u) == 0 )
      {
        if ( !(_BYTE)sprite )
          App_RequestQuit((int)aCannotConform2);
        x += (unsigned __int8)sprite;
        while ( (_BYTE)sprite )
        {
          pixel_value = (unsigned __int8)*pixel_cursor++;
          LOBYTE(sprite) = sprite - 1;
          *(pixel_cursor - 1) = remap_table[pixel_value];
        }
      }
      else
      {
        LOBYTE(sprite) = sprite & 0x7F;
        x += (unsigned __int8)sprite;
      }
    }
  }
  return sprite;
}

//----- (00406540) --------------------------------------------------------
signed int  UnitBattle_ScanSpriteMinOpaqueRunLength(unsigned __int16 *sprite)
{
  unsigned __int16 sprite_mode; // dx
  unsigned __int8 *rle_cursor; // eax
  int i; // ebp
  int run_length; // esi
  int x; // edx
  unsigned __int8 run_byte; // bl
  int back_ref_length; // ecx
  int min_run_length; // [esp+0h] [ebp-1Ch]

  min_run_length = 100000;
  sprite_mode = sprite[2];
  rle_cursor = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(sprite + 5);
  if ( !sprite_mode )
  {
    for ( i = 0; i < sprite[1]; ++i )
    {
      run_length = 0;
      x = 0;
      while ( x < *sprite )
      {
        run_byte = *rle_cursor++;
        if ( (run_byte & 0x80u) == 0 )
        {
          if ( run_byte )
          {
            x += run_byte;
            rle_cursor += run_byte;
          }
          else
          {
            back_ref_length = rle_cursor[-*(_DWORD *)rle_cursor];
            rle_cursor += 4;
            x += back_ref_length;
          }
        }
        else
        {
          run_length = run_byte & 0x7F;
          x += run_length;
        }
      }
      if ( run_length < min_run_length )
        min_run_length = run_length;
    }
  }
  return min_run_length;
}

//----- (004065D0) --------------------------------------------------------
int  UnitBattle_ScanSpriteFirstOpaqueRunLength(unsigned __int16 *sprite)
{
  unsigned __int16 sprite_mode; // dx
  unsigned __int8 *rle_cursor; // eax
  int i; // ebp
  int first_run_length; // esi
  int x; // edx
  unsigned __int8 run_byte; // bl
  unsigned __int8 opaque_length; // bl
  int back_ref_length; // ecx
  int min_run_length; // [esp+0h] [ebp-1Ch]

  min_run_length = 100000;
  sprite_mode = sprite[2];
  rle_cursor = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(sprite + 5);
  if ( !sprite_mode )
  {
    for ( i = 0; i < sprite[1]; ++i )
    {
      first_run_length = 0;
      x = 0;
      while ( x < *sprite )
      {
        run_byte = *rle_cursor++;
        if ( (run_byte & 0x80u) == 0 )
        {
          if ( run_byte )
          {
            x += run_byte;
            rle_cursor += run_byte;
          }
          else
          {
            back_ref_length = rle_cursor[-*(_DWORD *)rle_cursor];
            rle_cursor += 4;
            x += back_ref_length;
          }
        }
        else
        {
          opaque_length = run_byte & 0x7F;
          x += opaque_length;
          if ( !first_run_length )
            first_run_length = opaque_length;
        }
      }
      if ( first_run_length < min_run_length )
        min_run_length = first_run_length;
    }
  }
  return min_run_length;
}

//----- (00406650) --------------------------------------------------------
int  UnitBattle_CountLeadingBlankSpriteRows(unsigned __int16 *sprite)
{
  char *rle_cursor; // ecx
  int found_opaque; // esi
  int i; // edi
  int x; // edx
  char run_byte; // al
  int blank_row_count; // [esp+0h] [ebp-1Ch]

  rle_cursor = (char *)(uintptr_t)(unsigned int)*(_DWORD *)(sprite + 5);
  found_opaque = 0;
  blank_row_count = 0;
  if ( !sprite[2] )
  {
    for ( i = 0; i < sprite[1] && !found_opaque; ++i )
    {
      x = 0;
      while ( x < *sprite )
      {
        run_byte = *rle_cursor++;
        if ( run_byte >= 0 )
          found_opaque = 1;
        else
          x += run_byte & 0x7F;
      }
      ++blank_row_count;
    }
  }
  return blank_row_count;
}

//----- (004066C0) --------------------------------------------------------
int  UnitBattle_CountTrailingBlankSpriteRows(unsigned __int16 *sprite)
{
  unsigned __int8 *rle_cursor; // eax
  int blank_row_count; // esi
  int i; // ebp
  int x; // edx
  unsigned __int8 run_byte; // bl
  int back_ref_length; // ecx

  rle_cursor = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(sprite + 5);
  blank_row_count = 0;
  if ( !sprite[2] )
  {
    for ( i = 0; i < sprite[1]; ++i )
    {
      x = 0;
      while ( x < *sprite )
      {
        run_byte = *rle_cursor++;
        if ( (run_byte & 0x80u) == 0 )
        {
          blank_row_count = 0;
          if ( run_byte )
          {
            x += run_byte;
            rle_cursor += run_byte;
          }
          else
          {
            back_ref_length = rle_cursor[-*(_DWORD *)rle_cursor];
            rle_cursor += 4;
            x += back_ref_length;
          }
        }
        else
        {
          x += run_byte & 0x7F;
        }
      }
      ++blank_row_count;
    }
  }
  return blank_row_count;
}

//----- (00406740) --------------------------------------------------------
int Menu_DrawFrameBackdrop()
{
  int result; // eax

  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  result = Compat_RenderDeviceDrawMenuSprite(0, 0, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 0), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(314, 0, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 1), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(0, 237, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 2), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(315, 238, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 3), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(155, 465, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 5), 1u);
  g_RenderDevice = &g_MainRenderDevice;
  result = Compat_RenderDeviceDrawMenuSprite(0, 0, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 0), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(314, 0, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 1), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(0, 237, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 2), 1u);
  result = Compat_RenderDeviceDrawMenuSprite(315, 238, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 3), 1u);
  return Compat_RenderDeviceDrawMenuSprite(155, 465, DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 5), 1u);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202BC: using guessed type int dword_5202BC;
// 5202E0: using guessed type int dword_5202E0;

//----- (00406980) --------------------------------------------------------
void * WorldMap_RefreshUnitStatusPanel(DWORD a1)
{
  int v1; // ecx
  unsigned __int16 v2; // dx
  int scaled_current_ap; // esi
  char v4; // bl
  signed int ap_percent; // ebp
  int v6; // ecx
  _DWORD *Surface; // eax
  int surface_addr; // esi
  __int16 SpriteWidth; // ax
  int i; // esi
  int SpriteForChar; // eax
  int empty_bar_sprite; // eax
  __int16 bar_sprite_width; // ax
  int min_base_action_points; // eax
  void *result; // eax
  char v16; // [esp+1Ch] [ebp-18h]
  _DWORD *bar_surface; // [esp+1Ch] [ebp-18h]
  void *saved_render_device; // [esp+20h] [ebp-14h]

  Diagnostics_TraceWorldMapActionEvent(
    "status_panel_refresh_enter",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  WorldMap_SyncSelectionForHumanPlayer(a1);
  Diagnostics_TraceWorldMapActionEvent(
    "status_panel_refresh_after_sync",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  if ( g_SelectedUnitIndex == -1 )
    return (void *)Tooltip_RestoreBackdrop();
  if ( UnitStack_HasLowMoraleUnit(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
  {
    Tooltip_SetResourceHandle(13);
    Tooltip_ShowText(3, g_Text_LowMorale[(unsigned __int8)g_LanguageIndex]);
    return (void *)Tooltip_SetResourceHandle(7);
  }
  else
  {
    Tooltip_ShowText(
      1,
      aS,
      UnitType_GetLocalizedName((unit_type)*(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180)));
    saved_render_device = g_RenderDevice;
    g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_before_pump_rect",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      v2);
    RenderState_PumpIfRectInViewBounds(g_RenderState, v2, 0x1F7u, 0x1D4u, 0x1DCu);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_pump_rect",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    scaled_current_ap = 100 * UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_current_ap",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      scaled_current_ap);
    v4 = gameData;
    min_base_action_points = UnitStack_GetMinBaseActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex);
    if ( min_base_action_points <= 0 )
      ap_percent = 0;
    else
      ap_percent = scaled_current_ap / min_base_action_points;
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_before_surface_alloc",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      ap_percent);
    Surface = (_DWORD *)Mem_Alloc(188, 0, v4, ap_percent);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_surface_alloc",
      (int)(uintptr_t)Surface,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      ap_percent);
    surface_addr = (int)Surface;
    if ( Surface )
    {
      SpriteWidth = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 7u);
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_after_sprite_width",
        SpriteWidth,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        ap_percent);
      Surface = Render_CreateSurface(surface_addr, 100, SpriteWidth);
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_after_create_surface",
        (int)(uintptr_t)Surface,
        Surface ? Surface[1] : 0,
        g_UnitStackSlotSelectedFlags[0],
        ap_percent);
    }
    bar_surface = Surface;
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_surface_ready",
      (int)(uintptr_t)bar_surface,
      bar_surface ? bar_surface[1] : 0,
      (int)(uintptr_t)g_UnitStackSlotSelectedFlags,
      g_UnitStackSlotSelectedFlags[0]);
    g_RenderDevice = Surface;
    for ( i = 0; i < ap_percent; ++i )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 7);
      Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
    }
    while ( i < 100 )
    {
      empty_bar_sprite = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 6);
      ++i;
      Compat_RenderDeviceDrawMenuSprite(0, 0, empty_bar_sprite, 1);
    }
    bar_sprite_width = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 7u);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_before_blit",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      bar_surface ? bar_surface[1] : 0);
    Render_FillRect(bar_surface, 0, 0, 0, 0x63u, bar_sprite_width - 1, 0x16Bu, 0x1D4u);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_blit",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    Render_Present((int)g_RenderState);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_present",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    if ( bar_surface )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_before_destroy",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        (int)(uintptr_t)bar_surface);
      RenderSurface_InvokeSlot0(bar_surface, 2);
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_after_destroy",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        0);
    }
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_refresh_done",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      0);
    result = saved_render_device;
    g_RenderDevice = saved_render_device;
  }
  return result;
}
// 406A4F: variable 'v2' is possibly undefined
// 406ACD: variable 'v6' is possibly undefined
// 406BFC: variable 'v16' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B20: using guessed type char *g_Text_LowMorale[3];
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202BC: using guessed type int dword_5202BC;
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00406FA0) --------------------------------------------------------
void  WorldMap_TickAmbientMapAnimations(int ii)
{
  int v1; // edx
  int j; // ecx
  int i; // edi
  int row_offset; // esi
  int next_row_index; // ebp
  unsigned __int16 *tile_ptr; // edx
  unsigned int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  _WORD *next_row_tile; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int overlay_frame; // eax
  unsigned int v17; // eax
  int v18; // edx
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int k; // eax
  int v25; // edx
  int m; // eax
  int v27; // edx
  int n; // eax
  int v29; // edx
  int v30; // eax
  int v31; // edx
  int anim_row; // edi
  int anim_col; // ecx
  unsigned __int16 tile_code; // ax
  int v35; // esi
  int v36; // edx
  unsigned __int8 map_theme; // al
  int v38; // esi
  int v39; // ecx
  int v40; // ebx
  _WORD *v41; // eax
  int v42; // edx
  int v43; // ecx
  int v44; // esi
  int v45; // ecx
  int v46; // ebx
  _WORD *v47; // eax
  int v48; // ecx
  int v49; // esi
  int v50; // ecx
  int v51; // ebx
  _WORD *v52; // eax
  __int64 random_value; // rax
  int v54; // ecx
  int row_cursor; // esi
  int col_cursor; // ecx
  int col_offset; // ebx
  _WORD *v58; // edx
  int v59; // edx
  int deco_col; // esi
  int kk; // ecx
  int v62; // edx
  unsigned __int16 tile_frame; // di
  unsigned __int8 map_theme_byte; // dl
  __int16 decoration_code; // di
  int v66; // eax
  int v67; // eax
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int v73; // eax
  int v74; // eax
  int v75; // eax
  int v76; // [esp+0h] [ebp-7Ch]
  int smoke_row_offset; // [esp+4h] [ebp-78h]
  int next_row_offset; // [esp+8h] [ebp-74h]
  int deco_row; // [esp+Ch] [ebp-70h]
  int v80; // [esp+10h] [ebp-6Ch]
  int tile_addr; // [esp+20h] [ebp-5Ch]
  int anim_row_offset; // [esp+58h] [ebp-24h]
  int v83; // [esp+5Ch] [ebp-20h]
  int v84; // [esp+60h] [ebp-1Ch]
  int jj; // [esp+64h] [ebp-18h]
  unsigned __int16 next_frame; // [esp+68h] [ebp-14h]
  unsigned __int16 next_overlay_frame; // [esp+6Ch] [ebp-10h]

  if ( g_WorldMapViewportScrolledFlag )
  {
    g_WorldMapViewportScrolledFlag = 0;
  }
  else
  {
    v80 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    for ( i = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET); i < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7; ++i )
    {
      row_offset = 14 * i;
      DD_Pump((int)&g_RenderState, ii, i);
      ii = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      next_row_index = i + 1;
      for ( j = TILE_TERRAIN_ROW_STRIDE * ii; ; j += TILE_TERRAIN_ROW_STRIDE )
      {
        v1 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
        if ( ii >= v1 )
          break;
        tile_ptr = (unsigned __int16 *)(row_offset + j + gameData);
        if ( *tile_ptr != 0xFFFF && *tile_ptr < TERRAIN_ANIMATION_REMAP_COUNT )
        {
          next_frame = *(__int16 *)((char *)&g_TerrainAnimationRemapTable + 3 * *tile_ptr);
          if ( next_frame != 0xFFFF )
          {
            v7 = Time_Now(j, (int)tile_ptr);
            if ( v7 > *(_DWORD *)((char *)tile_ptr + 6) )
            {
              v20 = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * *tile_ptr];
              v9 = Time_Now(j, v20);
              *(_DWORD *)((char *)tile_ptr + 6) = v9 + v20;
              *tile_ptr = next_frame;
              WorldMap_RedrawTileIfVisible(ii, i);
              if ( !*(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) && next_frame == 36 )
              {
                next_row_tile = (_WORD *)(14 * next_row_index + j + gameData);
                if ( *next_row_tile == 36 )
                {
                  *next_row_tile = 771;
                  v14 = (unsigned __int8)g_SpecialTileAnimFrameDuration;
                  v13 = Time_Now(j, v14);
                  *(_DWORD *)((char *)next_row_tile + 6) = v13 + v14;
                  WorldMap_RedrawTileIfVisible(ii, i + 1);
                }
              }
            }
          }
        }
        tile_addr = row_offset + j + gameData;
        overlay_frame = *(unsigned __int16 *)(tile_addr + 2);
        if ( overlay_frame == 0xFFFE )
        {
          *(_WORD *)(tile_addr + 2) = -1;
          WorldMap_RedrawTileIfVisible(ii, i);
        }
        else if ( overlay_frame != 0xFFFF && overlay_frame < TERRAIN_ANIMATION_REMAP_COUNT )
        {
          next_overlay_frame = *(__int16 *)((char *)&g_TerrainAnimationRemapTable + 3 * overlay_frame);
          if ( next_overlay_frame != 0xFFFF )
          {
            v17 = Time_Now(j, tile_addr);
            if ( v17 > *(_DWORD *)((char *)tile_ptr + 10) )
            {
              if ( next_overlay_frame == 65534 )
              {
                tile_ptr[1] = -1;
              }
              else
              {
                v20 = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * tile_ptr[1]];
                v19 = Time_Now(j, v20);
                *(_DWORD *)((char *)tile_ptr + 10) = v19 + v20;
                tile_ptr[1] = next_overlay_frame;
              }
              WorldMap_RedrawTileIfVisible(ii, i);
            }
          }
        }
        ++ii;
      }
    }
    if ( Time_Now(j, v1) > (unsigned int)g_WorldMap_NextPaletteAnimTime )
    {
      g_ColorCyclePrimaryFrameIndex = *(__int16 *)((char *)&g_SpriteCodeRemapTable + 3 * (unsigned __int16)g_ColorCyclePrimaryFrameIndex);
      for ( k = 223; k != 235; g_ColorCycleStateArrayBase[k] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + v25) )
        v25 = 3 * (unsigned __int16)g_Font_GlyphRemapTable[k++];
      for ( m = 643; m != 675; g_Render_AnimatedFrameTable[m] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + v27) )
      {
        v27 = 3 * (unsigned __int16)g_Font_GlyphRemapTable[m];
        m += 8;
      }
      for ( n = 415; n != 423; g_ColorCycleStateArrayBase[n] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + v29) )
        v29 = 3 * (unsigned __int16)g_Font_GlyphRemapTable[n++];
      v30 = Time_Now(v23, (unsigned __int8)g_Render_SpriteAnimDelayBytes[3 * (unsigned __int16)g_ColorCycleDelayLookupIndex]);
      g_WorldMap_NextPaletteAnimTime = v31 + v30;
      anim_row = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      v22 = 2 * anim_row;
      anim_row_offset = 14 * anim_row;
      while ( anim_row < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
      {
        DD_Pump((int)&g_RenderState, ii, anim_row);
        anim_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        for ( ii = TILE_TERRAIN_ROW_STRIDE * anim_col; ; ii += TILE_TERRAIN_ROW_STRIDE )
        {
          v22 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
          if ( anim_col >= v22 )
            break;
          HIWORD(v35) = 0;
          tile_code = *(_WORD *)(ii + gameData + anim_row_offset);
          LOWORD(v35) = tile_code;
          if ( tile_code >= 0xDFu && v35 <= 234
            || (HIWORD(v36) = 0, tile_code >= 0x19Fu) && (LOWORD(v36) = *(_WORD *)(ii + gameData + anim_row_offset), v36 <= 422)
            || *(_WORD *)(ii + gameData + anim_row_offset) == 587
            || *(unsigned __int16 *)(ii + gameData + anim_row_offset) >= 0x283u
            && *(unsigned __int16 *)(ii + gameData + anim_row_offset) <= 0x2A2u )
          {
            WorldMap_RedrawTileIfVisible(anim_col, anim_row);
          }
          ++anim_col;
        }
        v23 = anim_row_offset + 14;
        ++anim_row;
        anim_row_offset += 14;
      }
    }
    if ( Time_Now(v23, v22) > (unsigned int)g_WorldMap_NextTileStateAnimTime )
    {
      map_theme = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
      if ( map_theme )
      {
        if ( map_theme <= 1u )
        {
          v44 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
          v84 = 14 * v44;
          while ( v44 < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
          {
            v45 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
            v46 = TILE_TERRAIN_ROW_STRIDE * v45;
            while ( v45 < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
            {
              v47 = (_WORD *)(v84 + v46 + gameData);
              if ( *v47 == 7 && (unsigned __int16)v47[1] == 0xFFFF && (unsigned int)rand_(v45, 7) < 0x333 )
              {
                *(_WORD *)(v46 + gameData + v84 + 2) = g_WorldMapAmbientAnimFramesSetB[(unsigned int)(rand_(v45, 0) / 0x7FFFuLL)];
                WorldMap_RedrawTileIfVisible(v48, v44);
              }
              v46 += TILE_TERRAIN_ROW_STRIDE;
              ++v45;
            }
            ++v44;
            v84 += 14;
          }
        }
        else if ( map_theme == 2 )
        {
          v49 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
          v83 = 14 * v49;
          while ( v49 < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
          {
            v50 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
            v51 = TILE_TERRAIN_ROW_STRIDE * v50;
            while ( v50 < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
            {
              v52 = (_WORD *)(v83 + v51 + gameData);
              if ( *v52 == 7 && (unsigned __int16)v52[1] == 0xFFFF )
              {
                random_value = rand_(v50, 7);
                if ( (unsigned int)random_value < 0x333 )
                {
                  *(_WORD *)(v51 + gameData + v83 + 2) = g_WorldMapAmbientAnimFramesSetC[4 * (unsigned int)rand_(v50, HIDWORD(random_value)) / 0x7FFF];
                  WorldMap_RedrawTileIfVisible(v54, v49);
                }
              }
              v51 += TILE_TERRAIN_ROW_STRIDE;
              ++v50;
            }
            ++v49;
            v83 += 14;
          }
        }
      }
      else
      {
        v38 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
        v76 = 14 * v38;
        while ( v38 < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
        {
          v39 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
          v40 = TILE_TERRAIN_ROW_STRIDE * v39;
          while ( v39 < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
          {
            v41 = (_WORD *)(v76 + v40 + gameData);
            if ( *v41 == 7 && (unsigned __int16)v41[1] == 0xFFFF && (unsigned int)rand_(v39, 7) < 0x333 )
            {
              *(_WORD *)(v76 + v40 + gameData + 2) = g_WorldMapAmbientAnimFramesSetA[6 * (int)rand_(v39, v42) / 0x7FFFu];
              WorldMap_RedrawTileIfVisible(v43, v38);
            }
            v40 += TILE_TERRAIN_ROW_STRIDE;
            ++v39;
          }
          ++v38;
          v76 += 14;
        }
      }
      row_cursor = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      smoke_row_offset = 14 * row_cursor;
      next_row_offset = 14 * row_cursor + 14;
      while ( row_cursor < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
      {
        col_cursor = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        col_offset = TILE_TERRAIN_ROW_STRIDE * col_cursor;
        while ( col_cursor < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
        {
          v58 = (_WORD *)(col_offset + gameData + smoke_row_offset);
          if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) )
          {
            if ( *v58 == 771 && (unsigned int)rand_(col_cursor, v58) < 0x199 )
            {
              *(_WORD *)(smoke_row_offset + col_offset + gameData) = 772;
              WorldMap_RedrawTileIfVisible(col_cursor, row_cursor);
            }
          }
          else if ( *v58 == 36 && *(_WORD *)(next_row_offset + col_offset + gameData) == 36 && (unsigned int)rand_(col_cursor, 36) < 0x28 )
          {
            *(_WORD *)(smoke_row_offset + col_offset + gameData) = 771;
            WorldMap_RedrawTileIfVisible(col_cursor, row_cursor);
          }
          col_offset += TILE_TERRAIN_ROW_STRIDE;
          ++col_cursor;
        }
        ++row_cursor;
        smoke_row_offset += 14;
        next_row_offset += 14;
      }
      deco_row = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      for ( jj = 14 * deco_row; ; jj += 14 )
      {
        v59 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7;
        if ( v59 <= deco_row )
          break;
        deco_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        for ( kk = TILE_TERRAIN_ROW_STRIDE * deco_col; ; kk += TILE_TERRAIN_ROW_STRIDE )
        {
          v62 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
          if ( deco_col >= v62 )
            break;
          tile_frame = *(_WORD *)(jj + kk + gameData);
          if ( tile_frame >= 0x2Du && tile_frame <= 0x51u && (unsigned int)rand_(kk, v62) < 0xA3 )
          {
            map_theme_byte = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
            decoration_code = tile_frame - 46;
            if ( map_theme_byte )
            {
              if ( map_theme_byte <= 1u )
              {
                switch ( decoration_code )
                {
                  case 0:
                    v68 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v68 + 2) == 0xFFFF )
                      *(_WORD *)(v68 + 2) = 97;
                    break;
                  case 1:
                    v69 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v69 + 2) == 0xFFFF )
                      *(_WORD *)(v69 + 2) = 105;
                    break;
                  case 3:
                    v71 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v71 + 2) == 0xFFFF )
                      *(_WORD *)(v71 + 2) = 121;
                    break;
                  case 8:
                    v72 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v72 + 2) == 0xFFFF )
                      *(_WORD *)(v72 + 2) = 129;
                    break;
                  case 9:
                    v74 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v74 + 2) == 0xFFFF )
                      *(_WORD *)(v74 + 2) = 145;
                    break;
                  case 10:
                    v73 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v73 + 2) == 0xFFFF )
                      *(_WORD *)(v73 + 2) = 137;
                    break;
                  case 11:
                    v75 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v75 + 2) == 0xFFFF )
                      *(_WORD *)(v75 + 2) = 153;
                    break;
                  case 12:
                    v70 = jj + kk + gameData;
                    if ( *(unsigned __int16 *)(v70 + 2) == 0xFFFF )
                      *(_WORD *)(v70 + 2) = 113;
                    break;
                  default:
                    break;
                }
              }
            }
            else
            {
              switch ( decoration_code )
              {
                case 0:
                  if ( *(unsigned __int16 *)(kk + gameData + jj + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 97;
                  break;
                case 1:
                  if ( *(unsigned __int16 *)(jj + kk + gameData + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 105;
                  break;
                case 3:
                case 4:
                  v67 = jj + kk + gameData;
                  if ( *(unsigned __int16 *)(v67 + 2) == 0xFFFF )
                    *(_WORD *)(v67 + 2) = 121;
                  break;
                case 8:
                  if ( *(unsigned __int16 *)(jj + kk + gameData + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 129;
                  break;
                case 9:
                  if ( *(unsigned __int16 *)(jj + kk + gameData + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 145;
                  break;
                case 10:
                  if ( *(unsigned __int16 *)(jj + kk + gameData + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 137;
                  break;
                case 11:
                  if ( *(unsigned __int16 *)(jj + kk + gameData + 2) == 0xFFFF )
                    *(_WORD *)(jj + kk + gameData + 2) = 153;
                  break;
                case 12:
                  v66 = jj + kk + gameData;
                  if ( *(unsigned __int16 *)(v66 + 2) == 0xFFFF )
                    *(_WORD *)(v66 + 2) = 113;
                  break;
                default:
                  break;
              }
            }
            WorldMap_RedrawTileIfVisible(deco_col, deco_row);
          }
          ++deco_col;
        }
        ++deco_row;
      }
      g_WorldMap_NextTileStateAnimTime = Time_Now(deco_row, v59) + 10;
    }
    Render_SetResourceHandle((int)&g_MainRenderDevice, v80);
  }
}
// 407065: variable 'v8' is possibly undefined
// 407094: variable 'j' is possibly undefined
// 407099: variable 'v10' is possibly undefined
// 4070A0: variable 'v11' is possibly undefined
// 40710B: variable 'v14' is possibly undefined
// 407113: variable 'v15' is possibly undefined
// 407175: variable 'v18' is possibly undefined
// 4071C9: variable 'v20' is possibly undefined
// 4071D0: variable 'v21' is possibly undefined
// 4071FB: variable 'v1' is possibly undefined
// 4072C0: variable 'v23' is possibly undefined
// 4072CD: variable 'v31' is possibly undefined
// 4073B9: variable 'v33' is possibly undefined
// 4073BC: variable 'v22' is possibly undefined
// 407477: variable 'v39' is possibly undefined
// 407477: variable 'v42' is possibly undefined
// 4074AA: variable 'v43' is possibly undefined
// 40754B: variable 'v45' is possibly undefined
// 407572: variable 'v48' is possibly undefined
// 40760C: variable 'v50' is possibly undefined
// 407641: variable 'v54' is possibly undefined
// 407732: variable 'v56' is possibly undefined
// 40785C: variable 'kk' is possibly undefined
// 47619A: using guessed type __int64 __fastcall rand_(_DWORD, _DWORD);
// 511B2C: using guessed type __int16 word_511B2C[7];
// 511B3A: using guessed type __int16 word_511B3A[2];
// 511B3E: using guessed type __int16 word_511B3E[5];
// 520290: using guessed type int dword_520290;
// 520294: using guessed type int dword_520294;
// 5202E4: using guessed type int gameData;
// 5202F0: using guessed type int dword_5202F0;
// 520738: using guessed type __int16 word_520738;
// 521043: using guessed type char byte_521043;
// 521338: using guessed type __int16 word_521338;
// 522B28: using guessed type __int16 word_522B28[];
// 522B36: using guessed type __int16 word_522B36[];
// 522B38: using guessed type __int16 word_522B38[];
// 522CF6: using guessed type __int16 word_522CF6;
// 522FCE: using guessed type __int16 word_522FCE;

//----- (00407B20) --------------------------------------------------------
unsigned int  WorldMap_TickPaletteFlashEffect(int reset_flag, int a2, int a3)
{
  unsigned int result; // eax
  __lock *flash_step; // ecx
  int v5; // edx
  int v6; // ecx

  if ( reset_flag )
  {
    g_WorldMap_PaletteFlashStep = 0;
    g_PaletteCrossfadeNextStepTime = Time_Now(a3, 0);
  }
  result = Time_Now(a3, a2);
  if ( result >= g_PaletteCrossfadeNextStepTime && g_WorldMap_PaletteFlashStep <= 10 )
  {
    flash_step = (__lock *)g_WorldMap_PaletteFlashStep++;
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, flash_step, 10);
    result = Time_Now(v6, v5) + 5;
    g_PaletteCrossfadeNextStepTime = result;
  }
  return result;
}
// 407B38: variable 'a3' is possibly undefined
// 407B38: variable 'a2' is possibly undefined
// 407B73: variable 'v6' is possibly undefined
// 407B73: variable 'v5' is possibly undefined
// 520298: using guessed type int dword_520298;
// 52029C: using guessed type int dword_52029C;
// 5202F4: using guessed type int dword_5202F4;

//----- (00407B90) --------------------------------------------------------
int Render_RestoreLostSurfaces()
{
  int last_cursor_x; // esi
  int last_cursor_y; // ebx
  int cursor_delta_x; // eax
  int map_width; // esi
  int map_height; // ecx

  Render_Pump();
  last_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
  last_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
  while ( DD_IsLost((int)g_RenderState) )
  {
    WorldMap_RedrawFrame(last_cursor_y);
    DD_Pump((int)g_RenderState, last_cursor_y);
    cursor_delta_x = (g_MouseCursorRawX >> g_CursorCoordShift) - last_cursor_x;
    if ( cursor_delta_x <= 0 )
      cursor_delta_x = last_cursor_x - (g_MouseCursorRawX >> g_CursorCoordShift);
    if ( cursor_delta_x < 8 )
    {
      if ( (g_MouseCursorRawY >> g_CursorCoordShift) - last_cursor_y <= 0 )
      {
        if ( last_cursor_y - (g_MouseCursorRawY >> g_CursorCoordShift) >= 8 )
          goto LABEL_7;
      }
      else if ( (g_MouseCursorRawY >> g_CursorCoordShift) - last_cursor_y >= 8 )
      {
        goto LABEL_7;
      }
    }
    else
    {
LABEL_7:
      *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) += ((g_MouseCursorRawX >> g_CursorCoordShift)
                                       - last_cursor_x
                                       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - last_cursor_x) >> 31, 3)
                                        + 8 * (((g_MouseCursorRawX >> g_CursorCoordShift) - last_cursor_x) >> 31))) >> 3;
      *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) += ((g_MouseCursorRawY >> g_CursorCoordShift)
                                       - last_cursor_y
                                       - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - last_cursor_y) >> 31, 3)
                                        + 8 * (((g_MouseCursorRawY >> g_CursorCoordShift) - last_cursor_y) >> 31))) >> 3;
      if ( *(int *)(gameData + MAP_VIEW_LEFT_OFFSET) < 0 )
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = 0;
      map_width = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 > map_width )
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = map_width - 9;
      if ( *(int *)(gameData + MAP_VIEW_TOP_OFFSET) < 0 )
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = 0;
      map_height = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 > map_height )
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = map_height - 7;
      WorldMap_RedrawViewport(1);
      last_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
      last_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    }
  }
  return Render_Present((int)g_RenderState);
}
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00407D20) --------------------------------------------------------
int  WorldMap_HandleScrollKeysAndIdle(signed int a1, ...)
{
  unsigned int time_now; // eax
  unsigned int next_scroll_time; // edx
  int v5; // edx
  int v6; // ecx
  int viewport_left; // ebx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int viewport_top; // ebx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int result; // eax
  int tile_x; // esi
  int tile_y; // ecx
  unsigned int unit_id; // edx

  time_now = Time_Now(g_WorldMapKeyScrollRepeatTime, 16 - *(unsigned __int8 *)(gameData + 147171) + g_WorldMapKeyScrollRepeatTime);
  if ( time_now > next_scroll_time && !g_WorldMap_KeyboardInputDisabled && !Input_IsKeyPressed(56) )
  {
    if ( Input_IsKeyPressed(203) )
    {
      viewport_left = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      if ( viewport_left > 0 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = viewport_left - 1;
        g_WorldMapKeyScrollRepeatTime = Time_Now(v6, v5);
        WorldMap_RedrawViewport(1);
        g_WorldMapViewportScrolledFlag = 1;
      }
    }
    if ( Input_IsKeyPressed(205) )
    {
      a1 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) - 9 > a1 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = a1 + 1;
        g_WorldMapKeyScrollRepeatTime = Time_Now(v8, a1 + 1);
        WorldMap_RedrawViewport(1);
        g_WorldMapViewportScrolledFlag = v9;
      }
    }
    if ( Input_IsKeyPressed(200) )
    {
      viewport_top = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      if ( viewport_top > 0 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = viewport_top - 1;
        g_WorldMapKeyScrollRepeatTime = Time_Now(v11, v10);
        WorldMap_RedrawViewport(1);
        g_WorldMapViewportScrolledFlag = 1;
      }
    }
    if ( Input_IsKeyPressed(208) )
    {
      a1 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) - 7 > a1 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = a1 + 1;
        g_WorldMapKeyScrollRepeatTime = Time_Now(v13, a1 + 1);
        WorldMap_RedrawViewport(1);
        g_WorldMapViewportScrolledFlag = v14;
      }
    }
    if ( Input_IsKeyPressed(50) )
    {
      MiniMap_ToggleVisibility();
      while ( Input_IsKeyPressed(50) )
        DD_Pump((int)g_RenderState, 50);
    }
    if ( Input_IsKeyPressed(59) )
    {
      Noop_DebugHotkeyF1Handler();
      while ( Input_IsKeyPressed(59) )
        DD_Pump((int)g_RenderState, (char)g_RenderState);
    }
    if ( Input_IsKeyPressed(60) )
    {
      Debug_Log(v15, (char)g_RenderState, a1, (int)asc_4EC5AC);
      while ( Input_IsKeyPressed(60) )
        DD_Pump((int)g_RenderState, (char)g_RenderState);
    }
  }
  result = MiniMap_IsCursorInside();
  if ( !result )
  {
    tile_x = (((g_MouseCursorRawX >> g_CursorCoordShift)
          - 32
          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
           + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
        + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    result = DD_IsLost((int)g_RenderState);
    if ( result )
    {
      tile_y = (((g_MouseCursorRawY >> g_CursorCoordShift)
            - 16
            - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
             + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
          + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      result = TILE_INDEX(tile_x, tile_y);
      unit_id = *(unsigned __int16 *)result;
      if ( (unsigned __int16)unit_id == 0xFFFF )
        return Render_RestoreLostSurfaces();
      if ( unit_id < 0x8000 )
      {
        result = UNIT_STACK_STRIDE * unit_id;
        if ( *(_BYTE *)(gameData + UNIT_STACK_STRIDE * unit_id + 147894) )
          return Render_RestoreLostSurfaces();
      }
    }
  }
  return result;
}
// 407FDD: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 407D4A: variable 'v4' is possibly undefined
// 407D95: variable 'v6' is possibly undefined
// 407D95: variable 'v5' is possibly undefined
// 407DE3: variable 'v8' is possibly undefined
// 407DFC: variable 'v9' is possibly undefined
// 407E28: variable 'v11' is possibly undefined
// 407E28: variable 'v10' is possibly undefined
// 407E76: variable 'v13' is possibly undefined
// 407E8F: variable 'v14' is possibly undefined
// 407F1C: variable 'v15' is possibly undefined
// 407FCB: variable 'v18' is possibly undefined
// 461730: using guessed type int nullsub_5(void);
// 5202A0: using guessed type int dword_5202A0;
// 5202E4: using guessed type int gameData;
// 5202F0: using guessed type int dword_5202F0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545140: using guessed type int dword_545140;

