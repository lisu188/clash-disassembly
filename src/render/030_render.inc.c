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
  Render_ConstructSurfaceObject((int)&g_RenderDeviceStorage, 640, 480);
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
_BYTE * Palette_QuantizeChannelsInPlace(_BYTE *result, char a2)
{
  _BYTE *v2; // ecx
  int v3; // edx
  char v4; // bl

  v2 = result + 1024;
  v3 = ~((1 << (8 - a2)) - 1);
  do
  {
    *result &= v3;
    result[1] &= v3;
    v4 = result[2];
    result += 4;
    *(result - 2) = v3 & v4;
  }
  while ( result != v2 );
  return result;
}

//----- (00401AF0) --------------------------------------------------------
int  Palette_LoadFromQueryHandle(intptr_t a1, intptr_t a2)
{
  int *palette_table;

  palette_table = (int *)(uintptr_t)a1;
  if ( !palette_table )
    return 0;
  Compat_LoadPalCOLIntoTable(palette_table, (const char *)(uintptr_t)a2, 0);
  return (int)(uintptr_t)palette_table;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401B20) --------------------------------------------------------
int  Palette_ExpandRGBTripletsToTable(int a1, int a2, int a3)
{
  int palette_offset;
  int write_ptr;
  int packed_rgb;
  unsigned __int8 red;
  unsigned __int8 green;
  unsigned __int8 blue;
  char palette_bytes[768]; // [esp+0h] [ebp-310h]

  (void)a3;
  Compat_QueryRead(a2, palette_bytes, 0x300);
  write_ptr = a1;
  palette_offset = 0;
  while ( write_ptr != a1 + 1024 )
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
int  LoadPalPCX(int a1, const char *palette_name, DWORD a3)
{
  char path[256]; // [esp+0h] [ebp-114h] BYREF
  int query_handle; // [esp+100h] [ebp-14h] BYREF

  (void)a3;
  Debug_Log(63, (DWORD)(uintptr_t)palette_name, (DWORD)a1, (int)a_loadpalpcxS0x);
  strcpy(path, aGfx_7);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, -0x300);
  Palette_ExpandRGBTripletsToTable(a1, query_handle, 0);
  return Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
}

//----- (00401C40) --------------------------------------------------------
int  LoadPalCOL(int a1, intptr_t a2, DWORD a3)
{
  const char *palette_name;
  char path[256]; // [esp+0h] [ebp-114h] BYREF
  int query_handle; // [esp+100h] [ebp-14h] BYREF

  palette_name = (const char *)(uintptr_t)a2;
  Debug_Log(63, a1, a3, (int)a_loadpalcolS0x);
  strcpy(path, aGfx_0);
  strcat(path, palette_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  Compat_QuerySkipBytes(query_handle, 8);
  Palette_ExpandRGBTripletsToTable(a1, query_handle, 0);
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
int  Render_ApplyColorTripletBytes(int a1, unsigned __int8 *a2)
{
  return Palette_QueryNearestColorIndex(a1, *a2, a2[1], a2[2]);
}

//----- (00401D10) --------------------------------------------------------
int  Palette_BuildGrayscaleIdentityTable(int a1)
{
  int v1; // edx
  int v2; // ecx
  int i; // eax
  int v5; // [esp+0h] [ebp-10h]

  v1 = _wcpp_4_ctor_array__(a1, 256);
  v2 = v1;
  for ( i = 0; i < 256; ++i )
  {
    LOBYTE(v5) = i;
    BYTE1(v5) = i;
    HIWORD(v5) = (unsigned __int8)i;
    v1 += 4;
    *(_DWORD *)(v1 - 4) = v5;
  }
  return v2;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401D60) --------------------------------------------------------
_BYTE * Str_CompactSkippingZeroBytes(_BYTE *result, _BYTE *a2, unsigned int a3)
{
  unsigned int i; // ecx

  for ( i = 0; i < a3; ++result )
  {
    while ( !*a2 )
    {
      ++i;
      ++a2;
      ++result;
      if ( i >= a3 )
        return result;
    }
    *result = *a2;
    ++i;
    ++a2;
  }
  return result;
}

//----- (00401D90) --------------------------------------------------------
void __cdecl __noreturn App_RequestQuit(int a1)
{
  const char *message;

  Render_BeginModeSwitch(&g_MainRenderDevice);
  message = (const char *)(uintptr_t)(unsigned int)a1;
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
_DWORD * Render_ConstructSurfaceObject(int a1, __int16 a2, __int16 a3)
{
  _DWORD *v3; // eax
  _DWORD *v4; // eax

  v3 = (_DWORD *)(a1 + 8);
  *(v3 - 1) = 0;
  *((_WORD *)v3 - 4) = a2;
  *((_WORD *)v3 - 3) = a3;
  v4 = Surface_Construct(v3);
  v4[44] = g_Surface_BaseVtable;
  return v4 - 2;
}
// 50EDD4: using guessed type int (*off_50EDD4[5])();

//----- (00401E30) --------------------------------------------------------
int  Render_ClearGameScreen(_DWORD *a1)
{
  return Render_FillRect(a1, &g_MainRenderDevice, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
}

//----- (00401E60) --------------------------------------------------------
int  Surface_ClearWholeArea(unsigned __int16 *a1)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, int))(*((_DWORD *)a1 + 46) + 32))(0, 0, a1[1] * *a1);
}

//----- (00401E90) --------------------------------------------------------
int  Render_FillClippedScanlines(int a1, unsigned int a2)
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
  int v14; // [esp+4h] [ebp-14h]
  unsigned __int8 v15; // [esp+8h] [ebp-10h]

  v14 = (*(int (**)(void))(*(_DWORD *)(a1 + 184) + 8))();
  v15 = v3;
  do
  {
    if ( a2 > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(a2) )
      (*(void (**)(void))(g_ActiveBlitCursor + 8))();
    v4 = (*(int (**)(void))(*(_DWORD *)v14 + 8))();
    if ( v5 > v4 )
      v5 = (*(int (**)(void))(*(_DWORD *)v14 + 8))();
    v6 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v5);
    if ( v7 > v6 )
      v7 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
    (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v7);
    (*(void (**)(void))(g_ActiveBlitCursor + 16))();
    (*(void (**)(void))(*(_DWORD *)v14 + 16))();
    memset_(v8, v15);
    (*(void (__fastcall **)(int, int))(*(_DWORD *)v14 + 12))(v9, v9);
    (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v10, v10);
    (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v11, v11);
    a2 -= v12;
  }
  while ( a2 );
  return (**(int (***)(void))v14)();
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
        int a1,
        int a2,
        int a3,
        __int16 a4,
        __int16 a5,
        unsigned __int16 a6,
        unsigned __int16 a7,
        __int16 a8)
{
  int v10; // eax
  int v11; // ecx
  int v12; // ebx
  int i; // edi
  __int64 v14; // rax
  int v15; // ecx
  int v16; // edi
  int *v17; // ecx
  int v18; // edi
  int (__fastcall ***v19)(_DWORD, int); // ecx
  unsigned __int16 v21; // [esp+0h] [ebp-14h]

  v10 = (*(int (**)(void))(*(_DWORD *)(a1 + 184) + 4))();
  v12 = (*(int (__fastcall **)(int, _DWORD))(*(_DWORD *)(a2 + 184) + 8))(v10, a7);
  v21 = a5 - a4 + 1;
  while ( 1 )
  {
    a3 += 2;
    if ( (unsigned __int16)a3 > a6 )
      break;
    for ( i = 0; i < v21 / 2; ++i )
    {
      (*(void (**)(void))(*(_DWORD *)v11 + 16))();
      v14 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)v12 + 16))();
      *(_BYTE *)v14 = *(_BYTE *)HIDWORD(v14);
      (*(void (__fastcall **)(int, int))(*(_DWORD *)v15 + 12))(v15, 2);
      (*(void (**)(void))(*(_DWORD *)v12 + 12))();
    }
    v16 = *(_DWORD *)v12;
    (*(void (**)(void))(*(_DWORD *)v12 + 4))();
    (*(void (**)(void))(v16 + 12))();
    v18 = *v17;
    (*(void (**)(void))(*v17 + 4))();
    (*(void (**)(void))(v18 + 12))();
  }
  (**(void (***)(void))v12)();
  return (**v19)(v19, 2);
}
// 402018: variable 'v11' is possibly undefined
// 40202C: variable 'v15' is possibly undefined
// 402056: variable 'v17' is possibly undefined
// 402081: variable 'v19' is possibly undefined

//----- (004020A0) --------------------------------------------------------
int  Render_LoadPCXImage(int a1, char *a2, int a3, uintptr_t a4)
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

  Debug_Log(a3, 0, (DWORD)a2, (int)a_loadpcxS0x08x);
  if ( !a1 || !a2 )
    return 0;

  strcpy(path, aGfx_8);
  strcat(path, a2);
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

  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 4);
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
      a1,
      *(unsigned __int16 *)a1,
      *((unsigned __int16 *)a1 + 1),
      a3,
      a4 != 0);
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
      if ( !a3 || value )
        memset(surface_pixels + pixel_index, value, run_length);
      pixel_index += run_length;
    }
    else
    {
      if ( !a3 || value )
        surface_pixels[pixel_index] = value;
      ++pixel_index;
    }
  }

  if ( file_offset < file_size )
  {
    ++decode_cursor;
    ++file_offset;
  }
  if ( a4 && file_offset + 768 <= file_size )
  {
    palette_out = (unsigned int *)a4;
    palette_bytes = decode_cursor;
    for ( palette_offset = 0; palette_offset != 768; palette_offset += 3 )
    {
      packed_rgb = palette_bytes[palette_offset]
                 | (palette_bytes[palette_offset + 1] << 8)
                 | (palette_bytes[palette_offset + 2] << 16);
      if ( !a3 || packed_rgb )
        *palette_out = packed_rgb;
      ++palette_out;
    }
  }

  Compat_FreeLow32Bytes((int)(uintptr_t)file_buffer);
  return 0;
}

//----- (004024E0) --------------------------------------------------------
int  Render_FillRect(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        int a4,
        unsigned __int16 a5,
        unsigned __int16 a6,
        unsigned __int16 a7,
        unsigned __int16 a8)
{
  _DWORD *v8; // esi
  _DWORD *v9; // edi
  int v10; // ecx
  void (**v11)(void); // ecx
  __int64 v12; // rax
  int v13; // ecx
  int v14; // eax
  unsigned int v15; // ebx
  const void *v16; // esi
  unsigned int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  __int64 v20; // rax
  int v21; // ecx
  __int64 v22; // rax
  int v23; // ebx
  int v24; // eax
  int (__fastcall **v25)(_DWORD, int); // ecx
  void *v27; // [esp-4h] [ebp-114h]
  _DWORD v28[49]; // [esp+0h] [ebp-110h] BYREF
  int v29; // [esp+C4h] [ebp-4Ch]
  int v30; // [esp+C8h] [ebp-48h]
  int v31; // [esp+CCh] [ebp-44h]
  void (***v32)(void); // [esp+D0h] [ebp-40h]
  void (***v33)(void); // [esp+D4h] [ebp-3Ch]
  int v34; // [esp+D8h] [ebp-38h]
  void (***v35)(void); // [esp+DCh] [ebp-34h]
  int (***v36)(void); // [esp+E0h] [ebp-30h]
  int v37; // [esp+E4h] [ebp-2Ch]
  int v38; // [esp+E8h] [ebp-28h]
  int v39; // [esp+ECh] [ebp-24h]
  unsigned int v40; // [esp+F0h] [ebp-20h]
  int v41; // [esp+F4h] [ebp-1Ch]
  int v42; // [esp+F8h] [ebp-18h]
  int v43; // [esp+FCh] [ebp-14h]
  unsigned int v44; // [esp+100h] [ebp-10h]
  int v45; // [esp+104h] [ebp-Ch]
  int v46; // [esp+108h] [ebp-8h]
  int v47; // [esp+10Ch] [ebp-4h]
  _DWORD *temp_surface;

  a1 = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)a1;
  a2 = (_DWORD *)(uintptr_t)(unsigned int)(uintptr_t)a2;
  v8 = a1;
  v9 = a2;
  v46 = a4;
  v47 = a3;
  if ( !a1 )
    v8 = &g_MainRenderDevice;
  if ( !a2 )
    v9 = &g_MainRenderDevice;
  v8 = RenderSurface_ResolvePrimaryCompanion(v8);
  v9 = RenderSurface_ResolvePrimaryCompanion(v9);
  v34 = a5;
  v30 = a5 - (unsigned __int16)v46 + 1;
  v37 = a6;
  v10 = v8[46];
  v38 = a6 - (unsigned __int16)v47 + 1;
  if ( RenderSurface_IsLinearSoftware(v8) && RenderSurface_IsLinearSoftware(v9) )
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

    source_pixels = (unsigned char *)(uintptr_t)(unsigned int)v8[1];
    destination_pixels = (unsigned char *)(uintptr_t)(unsigned int)v9[1];
    if ( !source_pixels || !destination_pixels )
      return 0;
    source_x = (short)(unsigned __int16)a4;
    source_y = (short)(unsigned __int16)v47;
    destination_x = (short)a7;
    destination_y = (short)a8;
    source_pitch = *(unsigned __int16 *)v8;
    destination_pitch = *(unsigned __int16 *)v9;
    source_width = source_pitch;
    source_height = HIWORD(v8[0]);
    destination_width = destination_pitch;
    destination_height = HIWORD(v9[0]);
    copy_width = v30;
    copy_height = v38;
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
  v23 = RenderSurface_InvokeSlot60(v8);
  v24 = RenderSurface_InvokeSlot64(v9);
  if ( v23 && v24 )
  {
    v29 = v37 + 1;
    Surface_SetSrcRect((_DWORD *)(uintptr_t)(unsigned int)v23, 0, v37 + 1, (unsigned __int16)v46, v34 + 1);
    v29 = a8 + v38;
    Surface_SetDestRect((_DWORD *)(uintptr_t)(unsigned int)v23, 0, v29, a7, a7 + v30);
    return RenderHandle_InvokeCopyDispatch(v23, v24);
  }
  else if ( g_MousePresentAtStartup && (v8 == (_DWORD *)&g_MainRenderDevice || v9 == (_DWORD *)&g_MainRenderDevice) )
  {
    if ( (v8 == (_DWORD *)&g_MainRenderDevice && !v8[47]) || (v9 == (_DWORD *)&g_MainRenderDevice && !v9[47]) )
      return 0;
    temp_surface = (_DWORD *)Mem_Alloc(196, 0, 0, 0);
    if ( !temp_surface )
      return 0;
    Render_ConstructScratchSurface((int)temp_surface, v30, 1u, v38);
    Render_FillRect(v8, temp_surface, (unsigned __int16)v47, (unsigned __int16)v46, a5, a6, 0, 0);
    Render_FillRect(temp_surface, v9, 0, 0, LOWORD(temp_surface[0]) - 1, HIWORD(temp_surface[0]) - 1, a7, a8);
    return Render_DestructScratchSurface(temp_surface, 2);
  }
  else
  {
    v35 = (void (***)(void))(*(int (**)(void))(v9[46] + 8))();
    v36 = (int (***)(void))(*(int (**)(void))(v8[46] + 4))();
    v31 = v38;
    v11 = *v35;
    v40 = v30;
    v12 = ((__int64 (*)(void))v11[1])();
    v42 = v12 - v30;
    v13 = *(_DWORD *)HIDWORD(v12);
    v43 = HIDWORD(v12);
    v39 = (*(int (**)(void))(v13 + 4))() - v30;
    v14 = (*(int (**)(void))(g_ActiveBlitCursor + 4))();
    v32 = v35;
    v41 = v14 - v30;
    while ( --v31 != -1 )
    {
      v44 = v40;
      v33 = v32;
      v45 = v43;
      do
      {
        v15 = v44;
        if ( (*(int (**)(void))(*(_DWORD *)v45 + 8))() < v44 )
          v15 = (*(int (**)(void))(*(_DWORD *)v45 + 8))();
        if ( v15 > ((int (*)(void))(*v33)[2])() )
          v15 = ((int (*)(void))(*v33)[2])();
        if ( v15 > (*(int (**)(void))(g_ActiveBlitCursor + 8))() )
          v15 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
        (*(void (**)(void))(g_ActiveBlitCursor + 16))();
        v16 = (const void *)(*(int (**)(void))(*(_DWORD *)v45 + 16))();
        v27 = (void *)((int (__thiscall *)(unsigned int))(*v33)[4])(v15);
        qmemcpy(v27, v16, v17);
        (*v33)[3]();
        (*(void (**)(void))(*(_DWORD *)v45 + 12))();
        (*(void (__fastcall **)(unsigned int, unsigned int))(g_ActiveBlitCursor + 12))(v44, v15);
        v44 = v18 - v15;
      }
      while ( v18 != v15 );
      ((void (__fastcall *)(_DWORD, int))(*v32)[3])(0, v42);
      (*(void (**)(void))(*(_DWORD *)v43 + 12))();
      (*(void (**)(void))(g_ActiveBlitCursor + 12))();
    }
    (**v35)();
    return (**v36)();
  }
}
// 40269C: variable 'v17' is possibly undefined
// 4026D5: variable 'v18' is possibly undefined
// 40277E: variable 'v25' is possibly undefined
// 51D018: using guessed type int g_MousePresentAtStartup;
// 51D4B8: using guessed type int dword_51D4B8;

//----- (00402850) --------------------------------------------------------
int  Render_BlitSurfaceRect(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        int a4,
        unsigned __int16 a5,
        unsigned __int16 a6,
        unsigned __int16 a7,
        unsigned __int16 a8)
{
  _DWORD *v8; // esi
  _DWORD *v9; // edi
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
  _DWORD v39[51]; // [esp+0h] [ebp-110h] BYREF
  int v40; // [esp+CCh] [ebp-44h]
  int v41; // [esp+D0h] [ebp-40h]
  int v42; // [esp+D4h] [ebp-3Ch]
  int v43; // [esp+D8h] [ebp-38h]
  int v44; // [esp+DCh] [ebp-34h]
  int (***v45)(void); // [esp+E0h] [ebp-30h]
  int v46; // [esp+E4h] [ebp-2Ch]
  int v47; // [esp+E8h] [ebp-28h]
  void (***v48)(void); // [esp+ECh] [ebp-24h]
  int v49; // [esp+F0h] [ebp-20h]
  int v50; // [esp+F4h] [ebp-1Ch]
  int v51; // [esp+F8h] [ebp-18h]
  int v52; // [esp+FCh] [ebp-14h]
  int i; // [esp+100h] [ebp-10h]
  int v54; // [esp+104h] [ebp-Ch]
  int v55; // [esp+108h] [ebp-8h]
  int v56; // [esp+10Ch] [ebp-4h]

  v8 = a1;
  v9 = a2;
  v55 = a4;
  v56 = a3;
  if ( !a1 )
    v8 = &g_MainRenderDevice;
  if ( !a2 )
    v9 = &g_MainRenderDevice;
  v47 = a5;
  v50 = a5 - (unsigned __int16)v55 + 1;
  v46 = (unsigned __int16)v56;
  v10 = v8[46];
  v41 = a6 - (unsigned __int16)v56 + 1;
  if ( (*(int (**)(void))(v10 + 60))() && (*(int (**)(void))(v9[46] + 64))() )
  {
    v28 = (*(int (**)(void))(v8[46] + 60))();
    Surface_SetSrcColorKey(v28, 0, v29);
    v31 = (_DWORD *)(*(int (__thiscall **)(int))(v8[46] + 60))(v30 + 1);
    Surface_SetSrcRect(v31, v46, v32, (unsigned __int16)v55, v47 + 1);
    v39[49] = a7;
    v39[50] = a8;
    v33 = (_DWORD *)(*(int (__thiscall **)(int))(v8[46] + 60))(a8 + v41);
    Surface_SetDestRect(v33, a8, v34, a7, v50 + a7);
    v35 = (*(int (**)(void))(v8[46] + 60))();
    v36 = v9[46];
    v40 = *(_DWORD *)(v35 + 172);
    v37 = (*(int (**)(void))(v36 + 64))();
    return (*(int (__fastcall **)(int, _DWORD))(v40 + 8))(v37, a7);
  }
  else if ( g_MousePresentAtStartup && (v8 == (_DWORD *)&g_MainRenderDevice || v9 == (_DWORD *)&g_MainRenderDevice) )
  {
    Render_ConstructScratchSurface((int)v39, v50, 1u, v41);
    Render_FillRect(v8, v39, (unsigned __int16)v56, (unsigned __int16)v55, a5, a6, 0, 0);
    Render_BlitSurfaceRect(v39, v9, 0, 0, LOWORD(v39[0]) - 1, HIWORD(v39[0]) - 1, a7, a8);
    return Render_DestructScratchSurface(v39, 0);
  }
  else
  {
    v48 = (void (***)(void))(*(int (**)(void))(v9[46] + 8))();
    v45 = (int (***)(void))(*(int (__fastcall **)(void (***)(void), _DWORD))(v8[46] + 4))(v48, (unsigned __int16)v55);
    v49 = v41;
    v12 = *v11;
    v52 = v50;
    v13 = ((__int64 (__fastcall *)(int *, int (***)(void)))*(_DWORD *)(v12 + 4))(v11, v45);
    v54 = v14;
    v15 = *(_DWORD *)HIDWORD(v13);
    v42 = v13 - v50;
    v43 = HIDWORD(v13);
    v51 = (*(int (**)(void))(v15 + 4))() - v50;
    for ( i = (*(int (**)(void))(g_ActiveBlitCursor + 4))() - v50;
          --v49 != -1;
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, i) )
    {
      v44 = v52;
      do
      {
        v16 = (*(int (__thiscall **)(int))(*(_DWORD *)v43 + 8))(v44);
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
        v44 -= v27;
      }
      while ( v44 );
      (*(void (**)(void))(*(_DWORD *)v54 + 12))();
      (*(void (**)(void))(*(_DWORD *)v43 + 12))();
    }
    (**v48)();
    return (**v45)();
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
        _DWORD *a1,
        int a2,
        int a3,
        int a4,
        unsigned __int16 a5,
        unsigned __int16 a6,
        unsigned __int16 a7,
        unsigned __int16 a8,
        unsigned __int16 a9,
        int a10)
{
  _DWORD *v10; // esi
  int v12; // esi
  int v13; // esi
  int v14; // edi
  _DWORD *v15; // ecx
  int v16; // ebx
  int v17; // eax
  int v18; // ecx
  __int64 v19; // rax
  int v20; // ecx
  unsigned int v21; // ebx
  unsigned __int8 *v22; // eax
  int v23; // edx
  __int64 v24; // rax
  _DWORD v26[49]; // [esp+0h] [ebp-120h] BYREF
  int (***v27)(void); // [esp+C4h] [ebp-5Ch]
  int v28; // [esp+C8h] [ebp-58h]
  int v29; // [esp+CCh] [ebp-54h]
  int v30; // [esp+D0h] [ebp-50h]
  unsigned __int8 *v31; // [esp+D4h] [ebp-4Ch]
  int v32; // [esp+D8h] [ebp-48h]
  int v33; // [esp+DCh] [ebp-44h]
  void (***v34)(void); // [esp+E0h] [ebp-40h]
  int v35; // [esp+E4h] [ebp-3Ch]
  void (***v36)(void); // [esp+E8h] [ebp-38h]
  int v37; // [esp+ECh] [ebp-34h]
  int v38; // [esp+F0h] [ebp-30h]
  int v39; // [esp+F4h] [ebp-2Ch]
  _DWORD *v40; // [esp+F8h] [ebp-28h]
  int v41; // [esp+FCh] [ebp-24h]
  int v42; // [esp+100h] [ebp-20h]
  unsigned int v43; // [esp+104h] [ebp-1Ch]
  int v44; // [esp+108h] [ebp-18h]
  int v45; // [esp+10Ch] [ebp-14h]
  int v46; // [esp+110h] [ebp-10h]
  int v47; // [esp+114h] [ebp-Ch]
  unsigned int v48; // [esp+118h] [ebp-8h]
  int v49; // [esp+11Ch] [ebp-4h]

  v10 = a1;
  v30 = a4;
  v49 = a3;
  if ( !a1 )
    v10 = &g_MainRenderDevice;
  v35 = a6;
  v33 = (unsigned __int16)v49;
  v32 = a6 - (unsigned __int16)v49 + 1;
  v38 = a7;
  v29 = a5;
  v37 = a7 - a5 + 1;
  if ( g_MousePresentAtStartup && v10 == (_DWORD *)&g_MainRenderDevice )
  {
    Render_ConstructScratchSurface((int)v26, v32, 1u, v37);
    Render_BlendSurfaceRect(v26, a2, v33, v30, v29, v35, v38, 0, 0, a10);
    Render_FillRect(v26, v10, 0, 0, LOWORD(v26[0]) - 1, HIWORD(v26[0]) - 1, a8, a9);
    return Render_DestructScratchSurface(v26, 0);
  }
  else
  {
    v34 = (void (***)(void))(*(int (**)(void))(v10[46] + 8))();
    v28 = a5;
    v12 = *(_DWORD *)(a2 + 184);
    v31 = (unsigned __int8 *)(unsigned __int16)v49;
    v13 = (*(int (__fastcall **)(void (***)(void), _DWORD))(v12 + 4))(v34, (unsigned __int16)v49);
    v14 = *(_DWORD *)(v30 + 184);
    v36 = (void (***)(void))v13;
    v27 = (int (***)(void))(*(int (**)(void))(v14 + 4))();
    g_Palette_BlendRatio = a10;
    v40 = v15;
    v46 = v37;
    v16 = *v15;
    v43 = v32;
    v17 = (*(int (__fastcall **)(_DWORD *, int (***)(void)))(v16 + 4))(v15, v27);
    v18 = *(_DWORD *)v13;
    v45 = v17 - v32;
    v41 = v13;
    v19 = ((__int64 (*)(void))*(_DWORD *)(v18 + 4))();
    v20 = *(_DWORD *)HIDWORD(v19);
    v42 = v19 - v32;
    v47 = HIDWORD(v19);
    v44 = (*(int (**)(void))(v20 + 4))() - v32;
    while ( --v46 != -1 )
    {
      v48 = v43;
      v39 = v47;
      do
      {
        v21 = v48;
        if ( (*(int (**)(void))(*(_DWORD *)v13 + 8))() < v48 )
          v21 = (*(int (**)(void))(*(_DWORD *)v13 + 8))();
        if ( v21 > (*(int (**)(void))(*v40 + 8))() )
          v21 = (*(int (**)(void))(*v40 + 8))();
        if ( v21 > (*(int (**)(void))(*(_DWORD *)v39 + 8))() )
          v21 = (*(int (**)(void))(*(_DWORD *)v39 + 8))();
        v22 = (unsigned __int8 *)(*(int (**)(void))(*(_DWORD *)v39 + 16))();
        v23 = *(_DWORD *)v13;
        v31 = v22;
        (*(void (**)(void))(v23 + 16))();
        v24 = ((__int64 (*)(void))*(_DWORD *)(*v40 + 16))();
        Palette_BlendIndexedPixelRun((char *)v24, (char *)HIDWORD(v24), v31, v21);
        (*(void (**)(void))(*v40 + 12))();
        (*(void (**)(void))(*(_DWORD *)v13 + 12))();
        (*(void (**)(void))(*(_DWORD *)v39 + 12))();
        v48 -= v21;
      }
      while ( v48 );
      (*(void (**)(void))(*v40 + 12))();
      (*(void (**)(void))(*(_DWORD *)v41 + 12))();
      (*(void (**)(void))(*(_DWORD *)v47 + 12))();
    }
    (**v34)();
    (**v36)();
    return (**v27)();
  }
}
// 402C84: variable 'v15' is possibly undefined
// 519A14: using guessed type int dword_519A14;
// 51D018: using guessed type int g_MousePresentAtStartup;

//----- (00402E80) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
int  Render_BlitCompressedSpriteRLE(
        int a1,
        int a2,
        int a3,
        int a4,
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
        __int128 a31,
        int a32,
        int a33,
        __int64 a34)
{
  int *v34; // esi
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
  unsigned __int8 v58; // al
  _DWORD *v59; // ecx
  unsigned __int8 v60; // dh
  unsigned int v61; // edi
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
  unsigned __int8 *v75; // esi
  int v76; // ecx
  unsigned int v77; // ebx
  unsigned __int8 *v78; // esi
  unsigned int v79; // ecx
  int v80; // ebx
  int v81; // ecx
  int v82; // edx
  int v83; // ecx
  int v84; // ecx
  int v85; // ebx
  unsigned int v86; // ecx
  unsigned int v87; // esi
  int *v88; // edx
  unsigned int v89; // ebx
  __int64 v90; // rax
  int v91; // ebx
  int *v92; // eax
  int v93; // esi
  int v94; // ecx
  unsigned int v95; // ecx
  int v96; // ebx
  unsigned __int8 *v97; // esi
  int *v98; // edx
  unsigned int v99; // ecx
  int v100; // ecx
  int v101; // ebx
  int v102; // ecx
  unsigned int v103; // edi
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
  int v120; // [esp+6Eh] [ebp-96h]
  int v121; // [esp+72h] [ebp-92h]
  int v122; // [esp+76h] [ebp-8Eh]
  int v123; // [esp+7Ah] [ebp-8Ah]
  int v124; // [esp+7Eh] [ebp-86h]
  int v125; // [esp+86h] [ebp-7Eh]
  int v126; // [esp+8Ah] [ebp-7Ah]
  int v127; // [esp+8Eh] [ebp-76h]
  int v128; // [esp+92h] [ebp-72h]
  int v129; // [esp+96h] [ebp-6Eh]
  _DWORD v130[4]; // [esp+9Ah] [ebp-6Ah] BYREF
  unsigned __int8 *v131; // [esp+AAh] [ebp-5Ah]
  int v132; // [esp+B2h] [ebp-52h]
  int v133; // [esp+B6h] [ebp-4Eh]
  _DWORD *v134; // [esp+BAh] [ebp-4Ah]
  void *v135; // [esp+BEh] [ebp-46h]
  int v136; // [esp+C2h] [ebp-42h]
  int v137; // [esp+C6h] [ebp-3Eh]
  int v138; // [esp+CAh] [ebp-3Ah]
  unsigned __int8 **v139; // [esp+CEh] [ebp-36h]
  int v140; // [esp+D2h] [ebp-32h]
  unsigned __int8 *v141; // [esp+D6h] [ebp-2Eh]
  void *v142; // [esp+DAh] [ebp-2Ah]
  int v143; // [esp+DEh] [ebp-26h]
  signed int v144; // [esp+E2h] [ebp-22h]
  int v145; // [esp+E6h] [ebp-1Eh]
  int v146; // [esp+EAh] [ebp-1Ah]
  int v147; // [esp+EEh] [ebp-16h]
  __int16 *v148; // [esp+F2h] [ebp-12h]
  int v149; // [esp+F6h] [ebp-Eh]
  int v150; // [esp+FAh] [ebp-Ah]
  int v151; // [esp+FEh] [ebp-6h]
  int var2; // [esp+102h] [ebp-2h]
  int vars2; // [esp+106h] [ebp+2h]
  _DWORD *vars6; // [esp+10Ah] [ebp+6h]
  __int16 _10E; // [esp+10Eh] [ebp+Ah] OVERLAPPED
  _UNKNOWN *retaddr; // [esp+110h] [ebp+Ch] OVERLAPPED
  void *v158; // [esp+116h] [ebp+12h]
  void *v159; // [esp+11Ah] [ebp+16h]
  int v160; // [esp+122h] [ebp+1Eh]
  unsigned __int8 **v161; // [esp+126h] [ebp+22h]
  int **v162; // [esp+12Ah] [ebp+26h]
  int **v163; // [esp+12Eh] [ebp+2Ah]
  int v164; // [esp+132h] [ebp+2Eh]
  _BYTE *v165; // [esp+136h] [ebp+32h]
  int v166; // [esp+13Eh] [ebp+3Ah]
  unsigned __int8 *v167; // [esp+142h] [ebp+3Eh]
  unsigned __int8 *v168; // [esp+14Ah] [ebp+46h]
  unsigned int v169; // [esp+14Eh] [ebp+4Ah]
  unsigned int v170; // [esp+152h] [ebp+4Eh]
  unsigned int v171; // [esp+156h] [ebp+52h]
  void *v172; // [esp+15Eh] [ebp+5Ah]
  __int16 v173; // [esp+162h] [ebp+5Eh]
  unsigned __int8 v174; // [esp+166h] [ebp+62h]

  v34 = *(int **)((char *)&a34 + 2);
  v150 = a1;
  v148 = (__int16 *)a2;
  var2 = a4;
  v151 = a3;
  v165 = *(_BYTE **)(a2 + 10);
  v173 = *(_WORD *)(a2 + 4);
  v134 = 0;
  BYTE2(a26) = g_TextSprite_StyleFlag;
  if ( g_MousePresentAtStartup && (_UNKNOWN *)v150 == &g_MainRenderDevice )
  {
    if ( *(_DWORD *)((char *)&a31 + 2) != -1 )
      App_RequestQuit((int)aDlxvscreenDraw);
    Surface = (_DWORD *)Mem_Alloc(188, g_MousePresentAtStartup, a4, (DWORD)v130);
    if ( Surface )
      Surface = Render_CreateSurface((int)Surface, *v148, v148[1]);
    v134 = Surface;
    if ( BYTE2(a32) )
      Render_FillRect(
        &g_MainRenderDevice,
        Surface,
        (unsigned __int16)v151,
        (unsigned __int16)var2,
        var2 + *v148 - 1,
        v151 + v148[1] - 1,
        0,
        0);
  }
  if ( v134 )
  {
    v36 = v134[46];
    v37 = 0;
    v38 = 0;
  }
  else
  {
    v37 = v151;
    v36 = *(_DWORD *)(v150 + 184);
    v38 = var2;
  }
  v142 = (void *)(*(int (__fastcall **)(int, int))(v36 + 8))(v36, v38);
  v120 = *(_DWORD *)((char *)&a31 + 2);
  v121 = *(_DWORD *)((char *)&a31 + 6);
  v122 = *(_DWORD *)((char *)&a31 + 10);
  v123 = *(_DWORD *)((char *)&a31 + 14);
  if ( *(_DWORD *)((char *)&a31 + 2) == -1
    && *(_DWORD *)((char *)&a31 + 6) == -1
    && *(_DWORD *)((char *)&a31 + 2) == *(_DWORD *)((char *)&a31 + 10)
    && *(_DWORD *)((char *)&a31 + 14) == *(_DWORD *)((char *)&a31 + 2) )
  {
    v39 = *(_DWORD *)((char *)&a31 + 2) ^ *(_DWORD *)((char *)&a31 + 14);
  }
  else
  {
    v39 = 1;
  }
  v124 = v39;
  v125 = *(_DWORD *)((char *)&a31 + 2);
  v126 = *(_DWORD *)((char *)&a31 + 6);
  v40 = *(_DWORD *)((char *)&a31 + 2);
  v127 = *(_DWORD *)((char *)&a31 + 10);
  v128 = *(_DWORD *)((char *)&a31 + 14);
  if ( *(_DWORD *)((char *)&a31 + 2) == -1
    && *(_DWORD *)((char *)&a31 + 6) == -1
    && *(_DWORD *)((char *)&a31 + 2) == *(_DWORD *)((char *)&a31 + 10)
    && *(_DWORD *)((char *)&a31 + 14) == *(_DWORD *)((char *)&a31 + 2) )
  {
    v41 = *(_DWORD *)((char *)&a31 + 2) ^ *(_DWORD *)((char *)&a31 + 14);
  }
  else
  {
    v41 = 1;
  }
  v129 = v41;
  v161 = 0;
  v163 = 0;
  v162 = 0;
  if ( v173 == 1 )
  {
    v42 = (unsigned __int8 **)Mem_Alloc(24, *(int *)((char *)&a31 + 2), v37, (DWORD)v130);
    if ( v42 )
    {
      v44 = *(unsigned __int8 **)((char *)&a31 + 2);
      *v42 = (unsigned __int8 *)&a26 + 2;
      v42[1] = v44;
      v42[2] = *(unsigned __int8 **)((char *)&a31 + 6);
      v45 = *(_DWORD *)((char *)&a31 + 2);
      v42[3] = *(unsigned __int8 **)((char *)&a31 + 10);
      v40 = *(_DWORD *)((char *)&a31 + 14);
      v43 = v42;
      v42[4] = *(unsigned __int8 **)((char *)&a31 + 14);
      if ( v45 == -1
        && *(_DWORD *)((char *)&a31 + 6) == -1
        && *(_DWORD *)((char *)&a31 + 10) == -1
        && *(_DWORD *)((char *)&a31 + 14) == -1 )
      {
        v46 = ~*(_DWORD *)((char *)&a31 + 6);
      }
      else
      {
        v46 = 1;
      }
      v43[5] = (unsigned __int8 *)v46;
    }
    v161 = v43;
  }
  if ( BYTE2(a33) == 1 )
  {
    v47 = (int **)Mem_Alloc(24, v40, v37, (DWORD)v130);
    if ( v47 )
    {
      v48 = *(int **)((char *)&a31 + 2);
      *v47 = v34;
      v47[1] = v48;
      v47[2] = *(int **)((char *)&a31 + 6);
      v49 = *(_DWORD *)((char *)&a31 + 2);
      v47[3] = *(int **)((char *)&a31 + 10);
      v40 = *(_DWORD *)((char *)&a31 + 14);
      v50 = v47;
      v47[4] = *(int **)((char *)&a31 + 14);
      if ( v49 == -1
        && *(_DWORD *)((char *)&a31 + 6) == -1
        && *(_DWORD *)((char *)&a31 + 10) == -1
        && *(_DWORD *)((char *)&a31 + 14) == -1 )
      {
        v51 = ~*(_DWORD *)((char *)&a31 + 6);
      }
      else
      {
        v51 = 1;
      }
      v50[5] = (int *)v51;
      v47 = v50;
    }
    v163 = v47;
  }
  if ( BYTE2(a33) != 2 )
    goto LABEL_40;
  v54 = (int **)Mem_Alloc(24, v40, v37, (DWORD)v130);
  if ( v54 )
  {
    v55 = *(int **)((char *)&a31 + 2);
    *v54 = v34;
    v54[1] = v55;
    v54[2] = *(int **)((char *)&a31 + 6);
    v54[3] = *(int **)((char *)&a31 + 10);
    v56 = *(_DWORD *)((char *)&a31 + 14);
    v57 = *(_DWORD *)((char *)&a31 + 2);
    v54[4] = *(int **)((char *)&a31 + 14);
    if ( v57 != -1 || *(_DWORD *)((char *)&a31 + 6) != -1 || *(_DWORD *)((char *)&a31 + 10) != -1 || v56 != -1 )
    {
      v54[5] = (int *)1;
      v162 = v54;
      goto LABEL_40;
    }
    v54[5] = (int *)~*(_DWORD *)((char *)&a31 + 10);
  }
  v162 = v54;
LABEL_40:
  v164 = v151;
  v144 = v122 + 1;
  v145 = v120 + 1;
  v147 = v127 + 1;
  v143 = 0;
  v146 = v125 + 1;
  while ( (unsigned __int16)v148[1] > v143 )
  {
    vars2 = 0;
    v166 = var2;
    while ( (unsigned __int16)*v148 > vars2 )
    {
      v58 = *v165;
      v59 = v165 + 1;
      v174 = v58;
      ++v165;
      if ( (v58 & 0x80u) == 0 )
      {
        if ( !v173 )
        {
          if ( v58 )
          {
            vars6 = 0;
          }
          else
          {
            v75 = (unsigned __int8 *)v59 - *v59;
            vars6 = v59;
            v174 = *v75;
            v165 = v75 + 1;
          }
          v131 = v165;
          v130[3] = g_RenderSurface_BlitCursorVtable;
          if ( BYTE2(a33) )
          {
            if ( BYTE2(a33) <= 1u )
            {
              v130[1] = (*(int (__thiscall **)(_DWORD))(*(_DWORD *)v142 + 16))(0);
              LOBYTE(v86) = v174;
              v149 = v166;
              v130[0] = g_RenderSurface_BlitCursorVtable;
              *(_UNKNOWN **)((char *)&retaddr + 2) = v142;
              v87 = v86;
              v88 = v163[5];
              v137 = 0;
              if ( v88 )
              {
                if ( v164 < (int)v163[2]
                  || v164 > (int)v163[4]
                  || v166 > (int)v163[3]
                  || (int)(v86 + v166) < (int)v163[1] + 1 )
                {
                  (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                  (*(void (**)(void))(v130[0] + 12))();
                  v131 += v87;
                  goto LABEL_97;
                }
                v92 = v163[1];
                if ( (int)v92 > v166 )
                {
                  v93 = (int)v92 - v166;
                  (*(void (**)(void))(*(_DWORD *)v142 + 12))();
                  (*(void (**)(void))(v130[0] + 12))();
                  v131 += v93;
                  v87 = v94 - v93;
                }
                if ( (int)v163[3] + 1 < (int)(v87 + v149) )
                {
                  v137 = v87 + v149 - (_DWORD)v163[3] - 1;
                  v87 -= v137;
                }
              }
              v171 = v87;
              do
              {
                v89 = v171;
                if ( (*(int (**)(void))(v130[0] + 8))() < v171 )
                  v89 = (*(int (**)(void))(v130[0] + 8))();
                if ( v89 > (*(int (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 8))() )
                  v89 = (*(int (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 8))();
                if ( v89 > 0x7FFFFFFF )
                  v89 = 0x7FFFFFFF;
                v141 = v131;
                (*(void (**)(void))(v130[0] + 16))();
                v90 = ((__int64 (*)(void))*(_DWORD *)(**(_DWORD **)((char *)&retaddr + 2) + 16))();
                Palette_BlendIndexedPixelRun((char *)v90, (char *)HIDWORD(v90), v141, v89);
                (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(v130[0] + 12))();
                v131 += v89;
                v171 -= v89;
              }
              while ( v171 );
              v91 = v137;
              if ( v137 )
              {
                (*(void (**)(void))(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(v130[0] + 12))();
                v131 += v91;
              }
              goto LABEL_97;
            }
            if ( BYTE2(a33) != 2 )
              App_RequestQuit((int)aDlxmemscreenDr);
            v132 = v166;
            v138 = 0;
            v95 = v174;
            v158 = v142;
            if ( v162[5] )
            {
              if ( v164 < (int)v162[2] || v164 > (int)v162[4] || v166 > (int)v162[3] || v174 + v166 < (int)v162[1] + 1 )
              {
                (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)v142 + 12))(v174, v174);
                v131 += v100;
                (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v100, v100);
                goto LABEL_97;
              }
              if ( (int)v162[1] > v166 )
              {
                v101 = v174 - ((_DWORD)v162[1] - v166);
                (*(void (**)(void))(*(_DWORD *)v142 + 12))();
                v131 += v102;
                (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v101, v102);
              }
              if ( (int)v162[3] + 1 < (int)(v95 + v132) )
              {
                v138 = v95 + v132 - (_DWORD)v162[3] - 1;
                v95 -= v138;
              }
            }
            v170 = v95;
            do
            {
              v96 = v170;
              if ( v170 > 0x7FFFFFFF )
                v96 = 0x7FFFFFFF;
              if ( v96 > (unsigned int)(*(int (**)(void))(*(_DWORD *)v158 + 8))() )
                v96 = (*(int (**)(void))(*(_DWORD *)v158 + 8))();
              if ( v96 > (unsigned int)(*(int (**)(void))(g_ActiveBlitCursor + 8))() )
                v96 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
              (*(void (**)(void))(g_ActiveBlitCursor + 16))();
              v168 = v131;
              v97 = v131;
              v167 = (unsigned __int8 *)(*(int (__thiscall **)(int))(*(_DWORD *)v158 + 16))(v96);
              v98 = *v162;
              qmemcpy(v167, v97, v99);
              if ( v96 > 1 || *v168 != v98[3] )
                Palette_OffsetIndexedPixelsRGB(v167, v96, *v98, v98[1], v98[2]);
              (*(void (**)(void))(*(_DWORD *)v158 + 12))();
              v131 += v96;
              (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v96);
              v170 -= v96;
            }
            while ( v170 );
            if ( v138 )
            {
              (*(void (**)(void))(*(_DWORD *)v158 + 12))();
              v131 += v138;
              v81 = g_ActiveBlitCursor;
              v82 = v138;
LABEL_96:
              (*(void (__fastcall **)(int, int))(v81 + 12))(v81, v82);
            }
          }
          else
          {
            v135 = v142;
            v76 = v174;
            v136 = 0;
            if ( !v129 )
              goto LABEL_86;
            if ( v164 < v126 || v164 > v128 || v166 > v127 || v166 + v174 < v146 )
            {
              (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)v135 + 12))(v174, v174);
              v131 += v83;
              (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v83, v83);
            }
            else
            {
              if ( v125 > v166 )
              {
                (*(void (__fastcall **)(int, int))(*(_DWORD *)v142 + 12))(v125 - v166, v125 - v166);
                v131 += v84;
                v85 = v174 - v84;
                (*(void (**)(void))(g_ActiveBlitCursor + 12))();
                v76 = v85;
              }
              if ( v166 + v76 > v147 )
              {
                v136 = v166 + v76 - v127 - 1;
                v76 = 1 - (v166 - v127);
              }
LABEL_86:
              v169 = v76;
              v172 = v135;
              do
              {
                v77 = v169;
                if ( v169 > 0x7FFFFFFF )
                  v77 = 0x7FFFFFFF;
                if ( v77 > (*(int (**)(void))(*(_DWORD *)v172 + 8))() )
                  v77 = (*(int (**)(void))(*(_DWORD *)v172 + 8))();
                if ( v77 > (*(int (**)(void))(g_ActiveBlitCursor + 8))() )
                  v77 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
                (*(void (**)(void))(g_ActiveBlitCursor + 16))();
                v78 = v131;
                v119 = (unsigned __int8 *)(*(int (__thiscall **)(unsigned int))(*(_DWORD *)v172 + 16))(v77);
                qmemcpy(v119, v78, v79);
                (*(void (**)(void))(*(_DWORD *)v172 + 12))();
                v131 += v77;
                (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v77);
                v169 -= v77;
              }
              while ( v169 );
              v80 = v136;
              if ( v136 )
              {
                (*(void (**)(void))(*(_DWORD *)v135 + 12))();
                v81 = g_ActiveBlitCursor;
                v82 = v80;
                v131 += v80;
                goto LABEL_96;
              }
            }
          }
LABEL_97:
          if ( vars6 )
            v165 = vars6 + 1;
          else
            v165 += v174;
          goto LABEL_180;
        }
        if ( v173 != 1 )
          goto LABEL_180;
        if ( BYTE2(a33) )
          App_RequestQuit((int)aDlxmemscreen_0);
        v133 = v166;
        v160 = 0;
        v103 = v58;
        v159 = v142;
        if ( v161[5] )
        {
          if ( v164 < (int)v161[2] || v164 > (int)v161[4] || v166 > (int)v161[3] || v58 + v166 < (int)(v161[1] + 1) )
          {
            (*(void (**)(void))(*(_DWORD *)v142 + 12))();
            (*(void (__fastcall **)(int, _DWORD))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v174);
            (*(void (__fastcall **)(int, _DWORD))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v174);
            goto LABEL_180;
          }
          v114 = v161[1];
          if ( (int)v114 > v166 )
          {
            v115 = &v114[-v166];
            (*(void (**)(void))(*(_DWORD *)v142 + 12))();
            (*(void (**)(void))(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, unsigned __int8 *))(g_ActiveBlitCursor + 12))(v116 - (_DWORD)v115, v115);
            v103 = v117;
          }
          if ( (int)(v161[3] + 1) < (int)(v103 + v133) )
          {
            v160 = v103 + v133 - (_DWORD)v161[3] - 1;
            v103 = 1 - (v133 - (_DWORD)v161[3]);
          }
        }
        v139 = v161;
        do
        {
          if ( v103 > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(v103) )
            v104 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          v105 = (*(int (__fastcall **)(int))(*(_DWORD *)v159 + 8))(v104);
          if ( v106 > v105 )
            v106 = (*(int (**)(void))(*(_DWORD *)v159 + 8))();
          v107 = (*(int (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 8))(v106);
          if ( v108 > v107 )
            v108 = (*(int (**)(void))(g_ActiveBlitCursor + 8))();
          (*(void (__fastcall **)(unsigned int))(g_ActiveBlitCursor + 16))(v108);
          (*(void (**)(void))(g_ActiveBlitCursor + 16))();
          (*(void (**)(void))(*(_DWORD *)v159 + 16))();
          memset_(v109, **v139);
          (*(void (__fastcall **)(int, int))(*(_DWORD *)v159 + 12))(v110, v110);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v111, v111);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v112, v112);
          v103 -= v113;
        }
        while ( v103 );
        if ( v160 )
        {
          (*(void (**)(void))(*(_DWORD *)v159 + 12))();
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v160);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v160);
        }
      }
      else
      {
        v60 = v58 & 0x7F;
        v174 = v58 & 0x7F;
        if ( BYTE2(a32) )
        {
          (*(void (**)(void))(*(_DWORD *)v142 + 12))();
          goto LABEL_180;
        }
        *(_DWORD *)&_10E = v142;
        v61 = v60;
        v140 = 0;
        if ( v124 )
        {
          if ( v164 < v121 || v164 > v123 || v166 > v122 || v166 + v60 < v145 )
          {
            (*(void (**)(void))(**(_DWORD **)&_10E + 12))();
            (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v61);
            (*(void (__fastcall **)(int, unsigned int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v61);
            goto LABEL_180;
          }
          if ( v120 > v166 )
          {
            (*(void (**)(void))(*(_DWORD *)v142 + 12))();
            (*(void (**)(void))(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(v73 - (v120 - v166), v120 - v166);
            v61 = v74;
          }
          if ( (int)(v166 + v61) > v144 )
          {
            v140 = v166 + v61 - v122 - 1;
            v61 = 1 - (v166 - v122);
          }
        }
        v62 = *(_DWORD *)&_10E;
        do
        {
          if ( v61 > (*(int (__thiscall **)(unsigned int))(g_ActiveBlitCursor + 8))(v61) )
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
          v61 -= v72;
        }
        while ( v61 );
        if ( v140 )
        {
          (*(void (**)(void))(**(_DWORD **)&_10E + 12))();
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v140);
          (*(void (__fastcall **)(int, int))(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, v140);
        }
      }
LABEL_180:
      vars2 += v174;
      v166 += v174;
    }
    v52 = (*(int (**)(void))(*(_DWORD *)v142 + 4))();
    (*(void (__fastcall **)(int, int))(v53 + 12))(v53, v52 - (unsigned __int16)*v148);
    ++v143;
    ++v164;
  }
  if ( v161 )
    j__nfree_();
  if ( v163 )
    j__nfree_();
  if ( v162 )
    j__nfree_();
  result = (**(int (***)(void))v142)();
  if ( v134 )
  {
    result = Render_FillRect(v134, &g_MainRenderDevice, 0, 0, *v148 - 1, v148[1] - 1, var2, v151);
    if ( v134 )
      return (*(int (**)(void))v134[46])();
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
_DWORD * Render_CreateSurface(int a1, __int16 a2, __int16 a3)
{
  _DWORD *surface;
  unsigned int pixel_count;

  surface = Render_ConstructSurfaceObject(a1, a2, a3);
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
int  Surface_DestructRawBuffer(int a1, char a2)
{
  int result; // eax

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_SurfaceRawBuffer_DtorArrayTag);
    j_j__nfree_();
    return a1;
  }
  *(_DWORD *)(a1 + 184) = g_Surface_RawBuffer8Vtable;
  nfree_(*(_DWORD *)(a1 + 4));
  *(_DWORD *)(a1 + 4) = 0;
  result = Surface_Destruct(a1 + 8) - 8;
  if ( (a2 & 2) != 0 )
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
_DWORD * Surface_ConstructRegionViewA(int a1, int a2, DWORD a3)
{
  _DWORD *result; // eax
  int v5; // edx
  unsigned __int16 *v6; // ecx
  unsigned __int16 v7; // si
  int v8; // ebx
  int v9; // ecx

  result = (_DWORD *)Mem_Alloc(12, a1, a2, a3);
  if ( result )
  {
    v7 = *v6;
    v8 = *v6 * a2;
    v9 = *((_DWORD *)v6 + 1);
    *result = g_RenderSurface_BlitCursorVtable;
    result[2] = v7;
    result[1] = v5 + v8 + v9;
  }
  return result;
}
// 403EC6: variable 'v6' is possibly undefined
// 403EDA: variable 'v5' is possibly undefined
// 50ED94: using guessed type int (*off_50ED94[5])();

//----- (00403EF0) --------------------------------------------------------
_DWORD * Surface_ConstructRegionViewB(int a1, int a2, DWORD a3)
{
  _DWORD *result; // eax
  int v5; // edx
  unsigned __int16 *v6; // ecx
  unsigned __int16 v7; // si
  int v8; // ebx
  int v9; // ecx

  result = (_DWORD *)Mem_Alloc(12, a1, a2, a3);
  if ( result )
  {
    v7 = *v6;
    v8 = *v6 * a2;
    v9 = *((_DWORD *)v6 + 1);
    *result = g_RenderSurface_BlitCursorVtable;
    result[2] = v7;
    result[1] = v5 + v8 + v9;
  }
  return result;
}
// 403F06: variable 'v6' is possibly undefined
// 403F1A: variable 'v5' is possibly undefined
// 50ED94: using guessed type int (*off_50ED94[5])();

//----- (00403F30) --------------------------------------------------------
int  Surface_SetPixel8(unsigned __int16 *a1, int a2, char a3, int a4)
{
  int result; // eax

  result = *a1 * a4 + *((_DWORD *)a1 + 1);
  *(_BYTE *)(a2 + result) = a3;
  return result;
}

//----- (00403F50) --------------------------------------------------------
int  Surface_GetPixel8(unsigned __int16 *a1, int a2, int a3)
{
  return *(unsigned __int8 *)(a2 + a3 * *a1 + *((_DWORD *)a1 + 1));
}

//----- (00403F70) --------------------------------------------------------
_BYTE * Surface_DrawDashedLine(
        unsigned __int16 *a1,
        unsigned __int16 a2,
        unsigned __int16 a3,
        int a4,
        unsigned __int16 a5,
        int a6)
{
  int v6; // ecx
  unsigned __int16 v7; // di
  _BYTE *result; // eax
  unsigned __int16 v9; // bx
  unsigned __int16 v10; // dx
  unsigned __int16 v11; // dx

  v6 = a6;
  v7 = *a1;
  result = (_BYTE *)(a2 + *((_DWORD *)a1 + 1) + *a1 * (unsigned __int16)a4);
  if ( (a6 & 0x100) != 0 )
  {
    if ( (_WORD)a4 == a5 )
    {
      while ( 1 )
      {
        v9 = a2++;
        if ( v9 >= a3 )
          break;
        if ( (a2 & 3) == 3 )
          *result = a6;
        ++result;
      }
    }
    else
    {
      while ( 1 )
      {
        v10 = a4;
        LOWORD(a4) = a4 + 1;
        if ( v10 >= a5 )
          break;
        if ( (a4 & 3) == 3 )
          *result = a6;
        result += v7;
      }
    }
  }
  else if ( (_WORD)a4 == a5 )
  {
    BYTE1(v6) = 0;
    return (_BYTE *)memset_(v6, (unsigned __int8)a6);
  }
  else
  {
    while ( 1 )
    {
      v11 = a4++;
      if ( v11 > a5 )
        break;
      *result = a6;
      result += v7;
    }
  }
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00404040) --------------------------------------------------------
int  Surface_DrawRectOutline(
        unsigned __int16 *a1,
        unsigned __int16 a2,
        unsigned __int16 a3,
        int a4,
        unsigned __int16 a5,
        unsigned __int8 a6)
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

  width = *a1;
  height = *((unsigned __int16 *)a1 + 1);
  pixels = (unsigned char *)(uintptr_t)(unsigned int)*((_DWORD *)a1 + 1);
  left = a2;
  right = a3;
  top = (unsigned __int16)a4;
  bottom = a5;
  if ( !pixels || !width || !height || left > right || top > bottom || left >= width || top >= height )
    return 0;
  if ( right >= width )
    right = width - 1;
  if ( bottom >= height )
    bottom = height - 1;
  if ( right > left + 1 )
    memset(pixels + top * width + left + 1, a6, right - left - 1);
  for ( y = top; y < bottom; ++y )
  {
    row_left = pixels + y * width + left;
    row_left[0] = a6;
    row_left[right - left] = a6;
  }
  memset(pixels + bottom * width + left, a6, right - left + 1);
  return (int)(uintptr_t)(pixels + bottom * width + left);
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004040F0) --------------------------------------------------------
unsigned __int16 * Surface_FillVerticalSpan(
        unsigned __int16 *result,
        int a2,
        unsigned __int16 a3,
        unsigned __int16 a4,
        unsigned __int8 a5)
{
  unsigned __int16 *v5; // edi
  int v6; // esi
  int v7; // ecx
  int v8; // ecx

  v5 = result;
  v6 = a3;
  v7 = a3 * *result + *((_DWORD *)result + 1);
  HIWORD(a2) = 0;
  while ( 1 )
  {
    v8 = a2 + v7;
    if ( v6 > a4 )
      break;
    result = (unsigned __int16 *)memset_(v8, a5);
    a2 = *v5;
    ++v6;
  }
  return result;
}
// 404117: variable 'v7' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00404160) --------------------------------------------------------
__int16  Surface_FillCheckerPattern(
        unsigned __int16 *a1,
        int a2,
        int a3,
        int a4,
        int a5,
        char a6)
{
  int v7; // esi
  int v8; // eax
  int i; // edi
  int v10; // edx
  int j; // eax

  v7 = a4;
  v8 = *((_DWORD *)a1 + 1) + a4 * *a1;
  for ( i = v8 + a2; v7 <= a5; i += *a1 )
  {
    v10 = a2;
    for ( j = i + (v7 & 1); v10 <= a3; *(_BYTE *)(j - 2) = a6 )
    {
      j += 2;
      v10 += 2;
    }
    LOWORD(v8) = *a1;
    ++v7;
  }
  return v8;
}

//----- (004041D0) --------------------------------------------------------
_DWORD * Render_ConstructScratchSurface(int a1, unsigned __int16 a2, DWORD a3, __int16 a4)
{
  int v5; // edi
  _DWORD *result; // eax
  _DWORD *v8; // esi
  _DWORD *v9; // eax
  _DWORD *allocated_companion; // eax
  int render_context; // edx

  v5 = a2;
  result = Render_ConstructSurfaceObject(a1, a2, a4);
  v8 = result;
  result[46] = g_ScratchSurface_Vtable;
  if ( a3 )
  {
    v9 = 0;
    allocated_companion = (_DWORD *)Mem_Alloc(176, 0, a4, a3);
    render_context = g_RenderContext;
    if ( allocated_companion && render_context )
      v9 = Surface_ConstructWithSurface(allocated_companion, (_DWORD *)(uintptr_t)(unsigned int)render_context, a4, v5);
    if ( allocated_companion && !v9 )
      nfree_((int)(uintptr_t)allocated_companion);
    v8[48] = v9 != 0;
    v8[47] = v9;
    return v8;
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
int  Render_DestructScratchSurface(_DWORD *a1, char a2)
{
  int owned_buffer; // edx
  int result; // eax

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_ScratchSurface_DtorArrayTag);
    j_j__nfree_();
    return (int)a1;
  }
  owned_buffer = a1[47];
  a1[46] = g_ScratchSurface_Vtable;
  if ( owned_buffer && a1[48] )
  {
    Surface_Destruct(owned_buffer);
    j__nfree_();
  }
  result = Surface_Destruct((int)(a1 + 2)) - 8;
  if ( (a2 & 2) != 0 )
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
int  Surface_ConstructLockedRegionView(int a1, int a2, int a3, DWORD a4)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, a1, a3, a4);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 60))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = a3 * v10 + a2 + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 4042DA: variable 'v6' is possibly undefined
// 4042FF: variable 'v9' is possibly undefined
// 404311: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404330) --------------------------------------------------------
int  Surface_ConstructPitchRegionView(int a1, int a2, int a3, DWORD a4)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, a1, a3, a4);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 64))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = a3 * v10 + a2 + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 40434A: variable 'v6' is possibly undefined
// 40436F: variable 'v9' is possibly undefined
// 404381: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (004043A0) --------------------------------------------------------
int  Surface_DrawPix(int a1, int a2)
{
  int v2; // esi
  int v3; // ecx
  int v4; // edx
  char v5; // cl

  v2 = (*(int (**)(void))(*(_DWORD *)(a1 + 184) + 64))();
  Surface_LockWithRestore(v2, v3);
  Surface_SetPixelByte(v2, v4, v5, a2);
  return Surface_Unlock(v2);
}
// 4043AC: variable 'v3' is possibly undefined
// 4043B3: variable 'v4' is possibly undefined
// 4043B3: variable 'v5' is possibly undefined

//----- (004043D0) --------------------------------------------------------
int  Surface_GetPix(int a1, int a2, int a3)
{
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  unsigned __int8 v7; // dl

  v3 = (*(int (__cdecl **)(int))(*(_DWORD *)(a1 + 184) + 60))(a2);
  Surface_LockWithRestore(v3, v3);
  Surface_GetPixelByte(v5, v4, a3);
  Surface_Unlock(v6);
  return v7;
}
// 4043E3: variable 'v5' is possibly undefined
// 4043E3: variable 'v4' is possibly undefined
// 4043EC: variable 'v6' is possibly undefined
// 4043F3: variable 'v7' is possibly undefined

//----- (00404400) --------------------------------------------------------
unsigned __int16  Surface_DrawLine(
        int a1,
        unsigned __int16 a2,
        unsigned __int16 a3,
        unsigned __int16 a4,
        unsigned __int16 a5,
        __int16 a6)
{
  unsigned __int16 v7; // di
  unsigned __int16 result; // ax
  unsigned __int16 v9; // dx
  unsigned __int16 v10; // dx
  __int64 v11; // rax
  int v12; // ecx
  __int64 v13; // rax
  int v14; // ecx
  __int64 v15; // rax
  int v16; // ecx
  unsigned __int16 v18; // [esp+Ch] [ebp-10h]

  v18 = a2;
  v7 = a4;
  result = (unsigned __int8)a6;
  if ( (a6 & 0x100) != 0 )
  {
    if ( a4 == a5 )
    {
      while ( 1 )
      {
        v9 = v18;
        result = ++v18;
        if ( v9 >= a3 )
          break;
        if ( (result & 3) == 3 )
        {
          (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)(a1 + 184) + 12))((unsigned __int8)a6, result);
        }
        else
        {
          while ( 1 )
          {
            v10 = v7++;
            if ( v10 >= a5 )
              break;
            if ( (v7 & 3) == 3 )
              (*(void (__fastcall **)(_DWORD, _DWORD))(*(_DWORD *)(a1 + 184) + 12))((unsigned __int8)a6, v18);
          }
        }
      }
    }
  }
  else if ( a4 == a5 )
  {
    v13 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(a1 + 184) + 64))(a5, a2);
    return Render_DrawHorizontalRun(v13, SHIDWORD(v13), v14, a3, a6);
  }
  else if ( a3 == a2 )
  {
    v11 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(a1 + 184) + 64))(a2, a4);
    return Render_DrawVerticalRun(v11, SHIDWORD(v11), v12, a5, a6);
  }
  else
  {
    v15 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(a1 + 184) + 64))(a3, a2);
    return Render_DrawLine(v15, SHIDWORD(v15), v16, a4, a5, a6);
  }
  return result;
}
// 4044E4: variable 'v12' is possibly undefined
// 404515: variable 'v14' is possibly undefined
// 404548: variable 'v16' is possibly undefined

//----- (00404560) --------------------------------------------------------
int  Surface_DrawRect(
        int a1,
        unsigned __int16 a2,
        unsigned __int16 a3,
        unsigned __int16 a4,
        unsigned __int16 a5,
        char a6)
{
  __int64 v6; // rax
  int v7; // ecx

  v6 = ((__int64 (__fastcall *)(_DWORD, _DWORD))*(_DWORD *)(*(_DWORD *)(a1 + 184) + 64))(a2, a4);
  return Surface_DrawRectBorderByte(v6, SHIDWORD(v6), v7, a3, a5, a6);
}
// 40458C: variable 'v7' is possibly undefined

//----- (004045A0) --------------------------------------------------------
int  Surface_DrawBox(
        int a1,
        unsigned __int16 a2,
        unsigned __int16 a3,
        unsigned __int16 a4,
        unsigned __int16 a5,
        unsigned __int8 a6)
{
  __int64 v6; // rax
  int v7; // ecx

  v6 = ((__int64 (__fastcall *)(unsigned int, _DWORD))*(_DWORD *)(*(_DWORD *)(a1 + 184) + 64))((unsigned int)a3 + 1, a2);
  return Surface_FillRectColor(v6, SHIDWORD(v6), v7, a4, a5 + 1, a6);
}
// 4045CE: variable 'v7' is possibly undefined

//----- (004045E0) --------------------------------------------------------
int  Surface_DotBox(int result, int a2, int a3, int a4, int a5, int a6)
{
  int v6; // edi
  int j; // esi
  int i; // [esp+8h] [ebp-10h]

  v6 = result;
  for ( i = a4; i <= a5; i += 2 )
  {
    for ( j = a2; j <= a3; j += 2 )
    {
      (*(void (__fastcall **)(int, int))(*(_DWORD *)(v6 + 184) + 12))(a6, j);
      result = a3;
    }
  }
  return result;
}
// 4045E0: could not find valid save-restore pair for ebx

//----- (00404640) --------------------------------------------------------
int  Render_UnlockBackbuffer(int a1)
{
  int v1; // eax

  v1 = RenderSurface_InvokeSlot64((_DWORD *)(uintptr_t)(unsigned int)a1);
  return Render_FillSurfaceSolidColor(v1, 0, 0);
}

//----- (00404660) --------------------------------------------------------
int  Surface_ConstructBackbufferInstance(int a1)
{
  int palette_array;

  palette_array = (int)Render_ConstructScratchSurface(a1, 0x280u, 0, 480) + 0xDC;
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
int  Render_SetPixelFormat(int a1, int a2, int a3, DWORD a4)
{
  LPVOID *v6; // eax
  unsigned __int16 v8; // bx
  _DWORD *v9; // ecx
  int v11; // eax
  int v12; // ecx
  _DWORD *Surface; // eax
  int v14; // edi
  int v15; // edx
  int v16; // eax
  int result; // eax
  HRESULT hr;
  int render_context;
  int surface_handle;
  int palette_handle;
  _DWORD *v18; // [esp-8h] [ebp-41Ch]
  DWORD v19; // [esp+0h] [ebp-414h]
  _BYTE v20[1040]; // [esp+4h] [ebp-410h] BYREF

  *(_DWORD *)(a1 + 212) = a3;
  v6 = (LPVOID *)Mem_Alloc(44, a2, a3, a4);
  if ( v6 )
    v6 = (LPVOID *)Render_ZeroDirectDrawObjectFields(v6);
  v19 = 0;
  v18 = *(_DWORD **)(a1 + 212);
  v8 = *(_WORD *)a1;
  v9 = (_DWORD *)*(unsigned __int16 *)(a1 + 2);
  *(_DWORD *)(a1 + 196) = v6;
  Render_InitDirectDrawFullscreenMode(v6, (_DWORD *)(uintptr_t)a2, v9, (_DWORD *)v8, v18, 0, v19);
  if ( *(_DWORD *)(a1 + 212) == 8 )
    *(_DWORD *)(a1 + 188) = *(_DWORD *)(*(_DWORD *)(a1 + 196) + 4);
  else
    *(_DWORD *)(a1 + 188) = 0;
  v11 = *(_DWORD *)(a1 + 196);
  *(_DWORD *)(a1 + 192) = 0;
  Render_FillSurfaceSolidColor(*(_DWORD *)(v11 + 4), 0, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v12, v8, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, *(_WORD *)a1, *(_WORD *)(a1 + 2));
  v14 = *(_DWORD *)(a1 + 212);
  *(_DWORD *)(a1 + 208) = Surface;
  if ( v14 == 8 )
  {
    v15 = 0;
    v16 = 0;
    do
    {
      v16 += 4;
      v20[v16 - 4] = v15;
      v20[v16 - 3] = v15;
      v20[v16 - 2] = v15++;
      v20[v16 - 1] = 0;
    }
    while ( v15 < 256 );
    render_context = *(_DWORD *)(a1 + 196);
    if ( render_context )
    {
      hr = Compat_DirectDraw_CreatePalette(
             (LPDIRECTDRAW)(uintptr_t)(unsigned int)*(_DWORD *)render_context,
             68,
             v20,
             (void *)(uintptr_t)(unsigned int)(render_context + 16));
      if ( hr )
        Render_HandleDirectDrawFatalError(hr, 0);
    }
    surface_handle = 0;
    palette_handle = 0;
    if ( *(_DWORD *)(a1 + 188) )
      surface_handle = *(_DWORD *)(*(_DWORD *)(a1 + 188) + 164);
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
    return Palette_ApplyWithBrightnessOffset((int *)a1, (const void *)(a1 + 220));
  }
  else
  {
    result = *(_DWORD *)(a1 + 196);
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
int  Render_BeginModeSwitch(_DWORD *a1)
{
  _DWORD *v2; // edx
  _DWORD *v3; // eax
  int result; // eax

  v2 = (_DWORD *)a1[49];
  if ( v2 && *v2 )
    Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)*v2, hWnd, 11);
  v3 = (_DWORD *)a1[49];
  a1[47] = 0;
  if ( v3 )
  {
    Render_DestroyDirectDrawObject(v3);
    j__nfree_();
  }
  result = a1[52];
  if ( result )
    Compat_InvokeCompactSurfaceDestructor(result, 2);
  a1[49] = 0;
  a1[52] = 0;
  return result;
}

//----- (004048B0) --------------------------------------------------------
int  Render_EndModeSwitch(int result, char a2, DWORD a3)
{
  int v4; // esi
  int v5; // eax
  int v6; // ecx
  int v7; // edi
  int surface_handle;

  v4 = result;
  if ( *(_DWORD *)(result + 208) )
  {
    result = *(_DWORD *)(result + 212);
    if ( result == 8 )
    {
      surface_handle = RenderSurface_InvokeSlot60((_DWORD *)(uintptr_t)(unsigned int)v4);
      result = surface_handle;
      if ( surface_handle )
      {
        v5 = surface_handle;
        result = Compat_DirectDrawSurfaceHandleIsLost(surface_handle);
        if ( !result )
        {
          Debug_Log(v6, a2, a3, (int)aRestorescreenc);
          v7 = g_CursorOverlayPresented;
          if ( g_CursorOverlayPresented )
            Render_Pump();
          result = Render_FillRect(
                     (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(v4 + 208),
                     (_DWORD *)v4,
                     0,
                     0,
                     *(_WORD *)v4 - 1,
                     *(_WORD *)(v4 + 2) - 1,
                     0,
                     0);
          if ( v7 )
            result = Render_Present((int)g_RenderState);
          *(_DWORD *)(v4 + 200) = 0;
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
_DWORD * Render_BlitSurface(_DWORD *result, int a2, char a3, DWORD a4)
{
  _DWORD *copy_target;
  int pixel_format;
  int v5; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int surface_handle;

  v5 = (int)result;
  copy_target = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(v5 + 208);
  pixel_format = *(_DWORD *)(v5 + 212);
  if ( result[50] || a2 )
  {
    if ( copy_target )
    {
      if ( pixel_format != 8 )
      {
        v8 = g_CursorOverlayPresented;
        if ( g_CursorOverlayPresented )
        {
          g_CursorOverlayPresented = 0;
          v6 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
          Render_FillRect(
            *(_DWORD **)((int)&g_RenderState + 8),
            0,
            0,
            0,
            *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 12) - 1,
            *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 16) - 1,
            *(unsigned __int16 *)&g_RenderState,
            *(unsigned __int16 *)((int)&g_RenderState + 4));
          Render_SetResourceHandle((int)&g_MainRenderDevice, v6);
        }
        result = (_DWORD *)Render_FillRect(
                             (_DWORD *)v5,
                             copy_target,
                             0,
                             0,
                             *(_WORD *)v5 - 1,
                             *(_WORD *)(v5 + 2) - 1,
                             0,
                             0);
        if ( v8 )
          result = (_DWORD *)Render_Present((int)&g_RenderState);
        *(_DWORD *)(v5 + 200) = 0;
      }
      else
      {
        surface_handle = RenderSurface_InvokeSlot60((_DWORD *)(uintptr_t)(unsigned int)v5);
        result = (_DWORD *)(uintptr_t)(unsigned int)surface_handle;
        if ( surface_handle )
        {
          v6 = surface_handle;
          result = (_DWORD *)(uintptr_t)(unsigned int)Compat_DirectDrawSurfaceHandleIsLost(surface_handle);
          if ( !result )
          {
            Debug_Log(v7, a3, a4, (int)aRemsc);
            v8 = g_CursorOverlayPresented;
            if ( g_CursorOverlayPresented )
            {
              g_CursorOverlayPresented = 0;
              v6 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
              Render_FillRect(
                *(_DWORD **)((int)&g_RenderState + 8),
                0,
                0,
                0,
                *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 12) - 1,
                *(_WORD *)(*(_DWORD *)((int)&g_RenderState + 60) + 16) - 1,
                *(unsigned __int16 *)&g_RenderState,
                *(unsigned __int16 *)((int)&g_RenderState + 4));
              Render_SetResourceHandle((int)&g_MainRenderDevice, v6);
            }
            result = (_DWORD *)Render_FillRect(
                                 (_DWORD *)v5,
                                 copy_target,
                                 0,
                                 0,
                                 *(_WORD *)v5 - 1,
                                 *(_WORD *)(v5 + 2) - 1,
                                 0,
                                 0);
            if ( v8 )
              result = (_DWORD *)Render_Present((int)&g_RenderState);
            *(_DWORD *)(v5 + 200) = 0;
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
int  Surface_SwapDirtyTrackingFlag(int a1, int a2)
{
  int v3; // edx

  v3 = *(_DWORD *)(a1 + 204);
  *(_DWORD *)(a1 + 204) = a2;
  return v3;
}

//----- (00404A60) --------------------------------------------------------
int * Render_ReleaseTempSurface(int *result)
{
  int *v1; // ebx
  int v2; // edx

  v1 = result;
  v2 = result[47];
  if ( v2 )
  {
    (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(v2 + 164) + 124))(
      *(_DWORD *)(v2 + 164),
      *(_DWORD *)(result[49] + 16));
    return (int *)Palette_ApplyWithBrightnessOffset(v1, v1 + 55);
  }
  return result;
}

//----- (00404AA0) --------------------------------------------------------
int  Surface_BeginPixelRead(int a1, int a2, int a3, DWORD a4)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, a1, a3, a4);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 60))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = a3 * v10 + a2 + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 404ABA: variable 'v6' is possibly undefined
// 404ADF: variable 'v9' is possibly undefined
// 404AF1: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404B10) --------------------------------------------------------
int  Surface_BeginPixelWrite(int a1, int a2, int a3, DWORD a4)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx

  result = Mem_Alloc(12, a1, a3, a4);
  if ( result )
  {
    v7 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v6 + 184) + 64))();
    *(_DWORD *)HIDWORD(v7) = g_RenderSurface_LinkedBlitCursorVtable;
    *(_DWORD *)(HIDWORD(v7) + 4) = v7;
    v8 = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( v8 )
      Render_HandleDirectDrawFatalError(v8, v9);
    v10 = (*(int (**)(void))(*(_DWORD *)v9 + 4))();
    *(_DWORD *)(v11 + 8) = a3 * v10 + a2 + *(_DWORD *)(*(_DWORD *)(v11 + 4) + 92);
    return v11;
  }
  return result;
}
// 404B2A: variable 'v6' is possibly undefined
// 404B4F: variable 'v9' is possibly undefined
// 404B61: variable 'v11' is possibly undefined
// 50EDB4: using guessed type int (*off_50EDB4[5])();

//----- (00404B80) --------------------------------------------------------
int  Surface_DrawPixAndMarkDirty(int a1, int a2)
{
  int result; // eax

  result = Surface_DrawPix(a1, a2);
  *(_DWORD *)(a1 + 200) = 1;
  return result;
}

//----- (00404BA0) --------------------------------------------------------
int  Render_SaveBackbuffer(int a1)
{
  _DWORD surface_wrapper;
  _DWORD surface_device;
  uintptr_t *surface_vtable;

  if ( a1 == (int)&g_MainRenderDevice )
  {
    Compat_PresentPrimaryIndexedSurfaceToPlatform();
    return 0;
  }
  surface_wrapper = *(_DWORD *)(a1 + 196);
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
int  Palette_SetBrightnessOffset(int result, int a2)
{
  *(_DWORD *)(result + 216) = a2;
  return result;
}

//----- (00404C80) --------------------------------------------------------
int  Palette_ApplyWithBrightnessOffset(int *a1, const void *a2)
{
  unsigned char *palette_bytes;
  unsigned int converted_palette[256];
  int base_color;
  int channel_value;
  unsigned int palette_index;

  palette_bytes = (unsigned char *)(a1 + 55);
  qmemcpy(palette_bytes, a2, 0x400u);
  base_color = a1[54];
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
  if ( a1 == (int *)&g_MainRenderDevice || !a1[49] || (a1[49] & 3) != 0 )
    return 0;
  return IO_StreamWrite(a1[49], 0, (int)converted_palette, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00404D90) --------------------------------------------------------
int  Palette_ApplyDefaultPalette(int *a1)
{
  return Palette_ApplyWithBrightnessOffset(a1, &g_DefaultPaletteTable);
}

//----- (00404DA0) --------------------------------------------------------
int * Palette_CrossfadeToTarget(int *result, unsigned __int8 *a2, signed int a3)
{
  int *v3; // ebp
  signed int i; // esi
  int v5; // ecx

  v3 = result;
  for ( i = 0; i <= a3; result = (int *)Palette_CrossfadeStep(v3, a2, v5, a3) )
    v5 = i++;
  return result;
}

//----- (00404DE0) --------------------------------------------------------
int  Palette_CrossfadeStep(int *a1, unsigned __int8 *a2, int a3, signed int a4)
{
  unsigned __int8 *v6; // ecx
  int *v7; // esi
  unsigned __int8 *v8; // ebx
  int v12; // [esp+18h] [ebp-14h]

  if ( !a3 )
    qmemcpy(&g_PaletteCrossfadeSourceBuffer, a1 + 55, 0x400u);
  v6 = a2;
  v7 = a1 + 55;
  v8 = (unsigned __int8 *)&g_PaletteCrossfadeSourceBuffer;
  do
  {
    LOBYTE(v12) = (int)a3 * (*v6 - *v8) / a4 + *v8;
    ++v7;
    BYTE1(v12) = (int)a3 * (v6[1] - v8[1]) / a4 + v8[1];
    HIWORD(v12) = (unsigned __int8)(v8[2] + (int)a3 * (v6[2] - v8[2]) / a4);
    v8 += 4;
    v6 += 4;
    *(v7 - 1) = v12;
  }
  while ( v6 != a2 + 1024 );
  Palette_ApplyWithBrightnessOffset(a1, a1 + 55);
  return Render_SaveBackbuffer((int)a1);
}

//----- (00404F20) --------------------------------------------------------
int  Palette_FadeOutToBlack(int *a1, signed int a2)
{
  _DWORD *v3; // esi
  int result; // eax
  int v5; // ebx
  unsigned __int8 *v6; // ecx
  _DWORD *v7; // esi
  int v8; // edx
  __int64 v9; // rtt
  int v10; // edx
  unsigned int source_palette[256]; // [esp+0h] [ebp-428h] BYREF
  int *v12; // [esp+400h] [ebp-28h] BYREF
  int v13; // [esp+404h] [ebp-24h]
  _DWORD *v14; // [esp+408h] [ebp-20h]
  unsigned __int8 v15; // [esp+40Ch] [ebp-1Ch]
  char v16; // [esp+410h] [ebp-18h]

  v12 = a1;
  v3 = a1 + 55;
  qmemcpy(source_palette, v3, sizeof(source_palette));
  result = 0;
  v5 = a2;
  if ( a2 >= 0 )
  {
    v14 = v3;
    do
    {
      v6 = (unsigned __int8 *)source_palette;
      v7 = v14;
      do
      {
        v8 = v5 * v6[1];
        v15 = v5 * v6[2] / a2;
        v9 = v8;
        v10 = v5 * *v6;
        v16 = v9 / a2;
        LOBYTE(v13) = v10 / a2;
        BYTE1(v13) = v16;
        HIWORD(v13) = v15;
        ++v7;
        v6 += 4;
        *(v7 - 1) = v13;
      }
      while ( v6 != (unsigned __int8 *)source_palette + sizeof(source_palette) );
      Palette_ApplyWithBrightnessOffset(v12, v14);
      --v5;
      result = Render_SaveBackbuffer((int)v12);
    }
    while ( v5 >= 0 );
  }
  return result;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00405020) --------------------------------------------------------
int * Palette_FadeInFromBlack(int *result, unsigned __int8 *a2, signed int a3)
{
  signed int v4; // ecx
  unsigned __int8 *v5; // ebx
  _DWORD *v6; // edi
  int *v7; // [esp+0h] [ebp-28h]
  _DWORD *v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]

  v7 = result;
  v4 = 0;
  if ( a3 >= 0 )
  {
    v9 = result + 55;
    do
    {
      v5 = a2;
      v6 = v9;
      do
      {
        LOBYTE(v10) = v4 * *v5 / a3;
        BYTE1(v10) = v4 * v5[1] / a3;
        HIWORD(v10) = (unsigned __int8)(v4 * v5[2] / a3);
        ++v6;
        v5 += 4;
        *(v6 - 1) = v10;
      }
      while ( v5 != a2 + 1024 );
      Palette_ApplyWithBrightnessOffset(v7, v9);
      ++v4;
      result = (int *)Render_SaveBackbuffer((int)v7);
    }
    while ( v4 <= a3 );
  }
  return result;
}
// 405086: variable 'v4' is possibly undefined

//----- (004050F0) --------------------------------------------------------
void * Video_EnterGreyscaleTransition(int *a1, int a2, char a3, DWORD a4)
{
  _DWORD *Surface; // eax
  int v6; // ecx
  int v7; // ebp
  int v8; // eax
  unsigned __int8 v9; // bh
  unsigned __int8 v10; // bl
  unsigned __int8 *v11; // edx
  int v12; // ecx
  int v13; // esi
  int v14; // edi
  int v15; // ecx
  int i; // eax
  _BYTE *v17; // ecx
  unsigned int v18; // esi
  unsigned int v19; // edi
  int v20; // ecx
  int v21; // eax
  int v22; // esi
  _BYTE *v23; // ecx
  void *result; // eax
  void *v25; // [esp+0h] [ebp-28h]
  _DWORD *v27; // [esp+8h] [ebp-20h]
  unsigned __int8 *v28; // [esp+Ch] [ebp-1Ch]
  char v29; // [esp+10h] [ebp-18h]

  v25 = g_RenderDevice;
  Surface = (_DWORD *)Mem_Alloc(188, a2, a3, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 640, 480);
  v27 = Surface;
  g_RenderDevice = Surface;
  Render_FillRect(a1, Surface, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  LoadPalPCX((int)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
  Palette_CrossfadeToTarget(a1, g_PaletteScratchSurfaceBuffer, 20);
  v7 = 0;
  v28 = g_PaletteScratchSurfaceBuffer;
  do
  {
    v8 = 32;
    v9 = *v28;
    v10 = -1;
    v11 = &g_PaletteScratchSurfaceBuffer[128];
    v29 = -1;
    do
    {
      v12 = v9 - v10;
      if ( v12 <= 0 )
        v12 = v10 - v9;
      v13 = v12;
      v14 = *v11;
      v15 = v9 - v14;
      if ( v15 <= 0 )
        v15 = v14 - v9;
      if ( v13 > v15 )
      {
        v29 = v8;
        v10 = *v11;
      }
      ++v8;
      v11 += 4;
    }
    while ( v8 < 256 );
    g_PaletteShadowRemapTableMinus1[++v7] = v29;
    v28 += 4;
  }
  while ( v7 < 32 );
  for ( i = 0; i < 307200; ++i )
  {
    v17 = (_BYTE *)(i + v27[1]);
    if ( (unsigned __int8)*v17 <= 0x1Fu )
      *v17 = g_Video_LowColorRemapTable[(unsigned __int8)*v17];
  }
  v18 = (unsigned int)g_PaletteScratchSurfaceBuffer;
  v19 = (unsigned int)&g_PaletteScratchSurfaceBuffer[128];
  v20 = 0;
  do
  {
    v21 = v20 / 31;
    v18 += 4;
    *(_BYTE *)(v18 - 4) = v20 / 31;
    *(_BYTE *)(v18 - 3) = v20 / 31;
    v20 += 255;
    *(_BYTE *)(v18 - 2) = v21;
  }
  while ( v18 != v19 );
  v22 = v19 ^ v18;
  v23 = (_BYTE *)v27[1];
  do
  {
    if ( (unsigned __int8)*v23 > 0x1Fu )
      *v23 = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*v23] >> 3;
    ++v22;
    ++v23;
  }
  while ( v22 < 307200 );
  Palette_ApplyWithBrightnessOffset(a1, g_PaletteScratchSurfaceBuffer);
  (void)g_RenderDevice;
  if ( v27 )
    j__nfree_(v27);
  result = v25;
  g_RenderDevice = v25;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (00405330) --------------------------------------------------------
void * Video_ExitGreyscaleTransition(int *a1, unsigned __int8 *a2, int a3, char a4, DWORD a5)
{
  _DWORD *Surface; // eax
  void *v7; // ebp
  _DWORD *v8; // esi
  int i; // edx
  _BYTE *v10; // ebx
  _BYTE *v11; // ecx
  int j; // ebx
  int k; // edx
  _BYTE *v14; // ebx
  unsigned int v15; // ecx
  int v16; // ecx
  void *result; // eax
  void *v19; // [esp+4h] [ebp-18h]

  v19 = g_RenderDevice;
  Surface = (_DWORD *)Mem_Alloc(188, a3, a4, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 640, 480);
  v7 = g_RenderDevice;
  v8 = Surface;
  Render_FillRect(g_RenderDevice, Surface, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  for ( i = 0; i < 307200; ++i )
  {
    v10 = (_BYTE *)(i + v8[1]);
    if ( (unsigned __int8)*v10 <= 0x1Fu )
      *v10 = g_Video_LowColorRemapTable[(unsigned __int8)*v10];
  }
  v11 = (_BYTE *)v8[1];
  for ( j = 0; j < 307200; ++j )
  {
    if ( (unsigned __int8)*v11 > 0x1Fu )
      *v11 = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*v11] >> 3;
    ++v11;
  }
  (void)v11;
  Palette_ApplyWithBrightnessOffset(a1, g_PaletteScratchSurfaceBuffer);
  Render_FillRect(g_RenderDevice, v8, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  for ( k = 0; k < 307200; ++k )
  {
    v14 = (_BYTE *)(k + v8[1]);
    v15 = (unsigned __int8)*v14;
    if ( v15 <= 0x1F )
      *v14 = g_Video_LowColorRemapTable[v15];
  }
  (void)v15;
  LoadPalPCX((int)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
  Palette_ApplyWithBrightnessOffset(a1, g_PaletteScratchSurfaceBuffer);
  Render_FillRect(g_RenderDevice, v8, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  (void)v8;
  Palette_CrossfadeToTarget(a1, a2, 20);
  if ( v8 )
    j__nfree_(v8);
  result = v19;
  g_RenderDevice = v19;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (00405510) --------------------------------------------------------
int  Sprite_DrawSimpleTrackingOffset(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        unsigned __int8 a8)
{
  g_Palette_BlendRatio = a7;
  (void)a4;
  (void)a5;
  (void)a6;
  return Compat_RenderDeviceDrawMenuSprite(a2, a3, a1, a8);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519A14: using guessed type int dword_519A14;

//----- (00405560) --------------------------------------------------------
int  Sprite_DrawSimpleIgnoringRect(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        unsigned __int8 a11)
{
  (void)a4;
  (void)a5;
  (void)a6;
  (void)a7;
  (void)a8;
  (void)a9;
  (void)a10;
  return Compat_RenderDeviceDrawMenuSprite(a2, a3, a1, a11);
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
int  Surface_GetReadIncrFromStride(int a1)
{
  return *(_DWORD *)(a1 + 188);
}

//----- (00405670) --------------------------------------------------------
int  Surface_GetWriteIncrFromStride(int a1)
{
  return *(_DWORD *)(a1 + 188);
}

//----- (00405680) --------------------------------------------------------
int  Surface_GetWriteIncrAndMarkDirty(_DWORD *a1)
{
  if ( a1[51] )
    a1[50] = 1;
  return a1[47];
}

//----- (004056B0) --------------------------------------------------------
int  Surface_Destroy(_DWORD *a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_Surface_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = Render_DestructScratchSurface(a1, 1);
    if ( (a2 & 2) != 0 )
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
int  SurfaceCursor_Destroy(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_SurfaceCursor_DtorArrayTag);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
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
int  RenderSurface_Destroy(int a1, char a2)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_RenderSurface_DtorArrayTag);
    j_j__nfree_();
    return v5;
  }
  else
  {
    v3 = Surface_Destruct(a1 + 8);
    if ( (a2 & 2) != 0 )
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
int  RenderSurface_GetBlitCursorRowStride(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

//----- (004057C0) --------------------------------------------------------
signed int RenderSurface_GetBlitCursorCapacity()
{
  return 0x7FFFFFFF;
}

//----- (004057D0) --------------------------------------------------------
int  RenderSurface_AdvanceBlitCursor(int result, int a2)
{
  *(_DWORD *)(result + 4) += a2;
  return result;
}

//----- (004057E0) --------------------------------------------------------
int  RenderSurface_GetBlitCursorPosition(int a1)
{
  return *(_DWORD *)(a1 + 4);
}

//----- (004057F0) --------------------------------------------------------
int  RenderSurface_DestroyLinkedBlitCursor(_DWORD *a1, char a2)
{
  int v2; // ecx
  char v3; // dl
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_LinkedBlitCursor_DtorArrayTag);
    j_j__nfree_();
    return v5;
  }
  else
  {
    *a1 = g_RenderSurface_LinkedBlitCursorVtable;
    Surface_Unlock(a1[1]);
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
int  RenderSurface_AdvanceLinkedBlitCursor(int result, int a2)
{
  *(_DWORD *)(result + 8) += a2;
  return result;
}

//----- (00405850) --------------------------------------------------------
int  RenderSurface_GetLinkedBlitCursorPosition(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

//----- (00405860) --------------------------------------------------------
int  RenderSurface_GetLinkedSurfaceBuffer(int a1)
{
  return *(_DWORD *)(*(_DWORD *)(a1 + 4) + 72);
}

//----- (00405870) --------------------------------------------------------
int  RenderSurface_DestroyBlitCursor(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_BlitCursor_DtorArrayTag);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
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
_BYTE * RenderSurface_CopyFourByteFields(_BYTE *result, _BYTE *a2)
{
  *result = *a2;
  result[1] = a2[1];
  result[2] = a2[2];
  result[3] = a2[3];
  return result;
}

//----- (00405900) --------------------------------------------------------
_DWORD * RenderSurface_ConstructFullScreenBuffer(int a1)
{
  return Render_ConstructSurfaceObject(a1, 640, 480);
}

//----- (00405920) --------------------------------------------------------
int  DLXSpriteSet_ReleaseAndClear(int *a1)
{
  int result; // eax
  uintptr_t method_table;

  result = *a1;
  if ( result )
  {
    method_table = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)result + 4108);
    if ( method_table )
      result = ((int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)method_table)(result, 2);
  }
  *a1 = 0;
  return result;
}

//----- (00405950) --------------------------------------------------------
int  DLXSprite_ReleaseAndClear(int *a1)
{
  int *v1; // ecx
  int result; // eax

  v1 = a1;
  result = *a1;
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
int  Res_ProbeGfxFileExists(CHAR *a1, int a2, DWORD a3, int a4)
{
  unsigned int v5; // kr04_4
  int open_handle;
  CHAR v10[264]; // [esp-110h] [ebp-110h] BYREF

  qmemcpy(v10, aGfx_1, 0xFFu);
  v5 = strlen(v10) + 1;
  strcat(v10, a1);
  open_handle = IO_FOpen(v10, (unsigned __int8 *)aRb_0, ~v5, a3);
  if ( !open_handle )
    return 0;
  fclose_(open_handle);
  return 0;
}
// 4059DC: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00405A00) --------------------------------------------------------
int  DLX_OpenArchive(char *a1, int a2)
{
  char *v3; // edi
  char v4; // al
  char v5; // al
  int result; // eax
  int v7; // ecx
  char v8[256]; // [esp-100h] [ebp-114h] BYREF
  int v9[5]; // [esp+0h] [ebp-14h] BYREF

  v9[4] = a2;
  qmemcpy(v8, aGfx_4, 0xFFu);
  v3 = &v8[strlen(v8)];
  do
  {
    v4 = *a1;
    *v3 = *a1;
    if ( !v4 )
      break;
    v5 = a1[1];
    a1 += 2;
    v3[1] = v5;
    v3 += 2;
  }
  while ( v5 );
  result = FileSystem_ResolveReadPath(v8, 0);
  v9[0] = result;
  if ( result )
  {
    Compat_FileSystemQueryRelease(v7, v9);
    return 1;
  }
  return result;
}
// 405A6C: variable 'v7' is possibly undefined

//----- (00405A90) --------------------------------------------------------
_DWORD * DLXSpriteSet_Load(_DWORD *a1, const void *a2)
{
  const char *resource_name;
  int data_size;
  int entry_index;
  int entry_end_offset;
  int entry_size;
  char path[256]; // [esp+0h] [ebp-11Ch] BYREF
  int query_handle; // [esp+100h] [ebp-1Ch] BYREF

  resource_name = a2 ? (const char *)a2 : "";
  a1[1024] = 0;
  a1[1027] = &g_DLXSpriteSet_Vtable;
  Debug_Log(63, 0, (DWORD)resource_name, (int)aDlxspritesetDl);
  strcpy(path, aGfx);
  strcat(path, resource_name);
  query_handle = FileSystem_ResolveReadPath(path, 0);
  a1[1026] = IO_QueryVTableStreamSize(query_handle);
  if ( !query_handle || a1[1026] <= 4096 )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(
        stderr,
        "[dlx] load failed path=%s size=%d caller=%p\n",
        path,
        a1[1026],
        __builtin_return_address(0));
    App_RequestQuit((int)aIOCouldnTOpenF);
    return a1;
  }
  Compat_QueryRead(query_handle, g_DlxSpriteSetOffsetTable, 4096);
  data_size = a1[1026] - 4096;
  a1[1024] = (unsigned int)nmalloc_(data_size, 4);
  if ( !a1[1024] )
  {
    Debug_Log(0, 0, data_size, (int)aNotEnoughMem_1);
    App_RequestQuit((int)aNotEnoughMem_2);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)a1[1024], data_size);
  entry_index = 0;
  while ( entry_index < 1023 && g_DlxSpriteSetOffsetTable[entry_index] )
  {
    entry_end_offset = g_DlxDirEntryEndOffsetTable[entry_index];
    if ( entry_end_offset )
      entry_size = entry_end_offset - g_DlxSpriteSetOffsetTable[entry_index];
    else
      entry_size = IO_QueryVTableStreamSize(query_handle) - g_DlxSpriteSetOffsetTable[entry_index];
    a1[entry_index] = Mem_Alloc(22, entry_index, entry_size, (DWORD)a1);
    if ( a1[entry_index] )
      a1[entry_index] = DLXSprite_ConstructFromBuffer(a1[entry_index], g_DlxSpriteSetOffsetTable[entry_index] + a1[1024] - 4096, entry_size);
    ++entry_index;
  }
  a1[1025] = entry_index;
  Compat_FileSystemQueryRelease(entry_index, &query_handle);
  return a1;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 50F044: using guessed type int (*off_50F044)();
// 51F290: using guessed type int dword_51F290[];
// 51F294: using guessed type int dword_51F294[1022];

//----- (00405C60) --------------------------------------------------------
int * DLXSpriteSet_Destroy(int *a1, char a2, int a3)
{
  int v4; // ebx
  int *v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a3, &g_DLXSpriteSet_DtorArrayTag);
    j_j__nfree_();
    return a1;
  }
  a1[1027] = (int)&g_DLXSpriteSet_Vtable;
  v4 = 0;
  if ( a1[1025] > 0 )
  {
    v5 = a1;
    do
    {
      if ( *v5 )
      {
        DLXSprite_Destroy(*v5);
        j__nfree_();
      }
      ++v4;
      ++v5;
    }
    while ( v4 < a1[1025] );
  }
  if ( a1[1024] )
    j__nfree_();
  if ( (a2 & 2) == 0 )
    return a1;
  j__nfree_();
  return a1;
}
// 405CA6: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50F044: using guessed type int (*off_50F044)();

//----- (00405D00) --------------------------------------------------------
int  DLXSpriteSet_ConstructCopy(int *a1, DWORD *a2, signed int a3)
{
  int v3; // ecx

  a1[1027] = (int)&g_DLXSpriteSet_Vtable;
  DLXSpriteSet_CopyEntriesFrom(a1, a2, (int)a1, a3);
  return v3;
}
// 405D12: variable 'v3' is possibly undefined
// 50F044: using guessed type int (*off_50F044)();

//----- (00405D20) --------------------------------------------------------
int * DLXSpriteSet_CopyEntriesFrom(int *a1, DWORD *a2, int a3, signed int a4)
{
  int v6; // ecx
  int v7; // edx
  int *v8; // esi
  int v10; // eax

  DLXSpriteSet_Destroy(a1, 0, a3);
  a1[1026] = a2[1026];
  a1[1025] = a2[1025];
  v6 = 0;
  v7 = a1[1025];
  a1[1024] = 0;
  if ( v7 > 0 )
  {
    v8 = a1;
    do
    {
      if ( *a2 )
      {
        v10 = Mem_Alloc(22, v6, (char)a2, a4);
        if ( v10 )
          v10 = DLXSprite_ConstructOwningCopy(v10, *a2);
        *v8 = v10;
      }
      else
      {
        a1[v6] = 0;
      }
      ++a2;
      ++v6;
      a4 = a1[1025];
      ++v8;
    }
    while ( v6 < a4 );
  }
  return a1;
}
// 405D73: variable 'v6' is possibly undefined

//----- (00405DB0) --------------------------------------------------------
int  DLXSpriteSet_Save(int *a1, int a2, char a3)
{
  int v4; // ecx
  char *v5; // edi
  char *v6; // esi
  char *v7; // edx
  char *v8; // esi
  unsigned int v9; // kr04_4
  char *v10; // edi
  char v11; // al
  char v12; // al
  int v13; // eax
  int v14; // edx
  int v15; // esi
  int v16; // eax
  DWORD v17; // ecx
  int v18; // ecx
  int *v19; // ebx
  int v20; // ecx
  char *v22; // [esp-4h] [ebp-118h]
  char v23[276]; // [esp+0h] [ebp-114h] BYREF

  HIBYTE(v22) = HIBYTE(a2);
  Debug_Log(63, a3, (DWORD)a1, (int)aDlxspritesetSa);
  qmemcpy(v23, aGfx_2, 4 * v4);
  v6 = &aGfx_2[4 * v4];
  v5 = &v23[4 * v4];
  *(_WORD *)v5 = *(_WORD *)v6;
  v5[2] = v6[2];
  v8 = v7;
  v22 = v23;
  v9 = strlen(v23) + 1;
  v10 = &v23[v9 - 1];
  do
  {
    v11 = *v8;
    *v10 = *v8;
    if ( !v11 )
      break;
    v12 = v8[1];
    v8 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  v13 = IO_FOpen(v23, (unsigned __int8 *)aWb, ~v9, (DWORD)a1);
  v14 = 4096;
  v15 = v13;
  v16 = 0;
  if ( a1[1025] > 0 )
  {
    v17 = (DWORD)a1;
    do
    {
      g_DlxSpriteSetOffsetTable[v16++] = v14;
      v14 += *(_DWORD *)(*(_DWORD *)v17 + 14);
      v17 += 4;
    }
    while ( v16 < a1[1025] );
  }
  g_DlxDirTotalDataOffset = v14;
  fwrite_(g_DlxSpriteSetOffsetTable, 4096, v15, 1);
  v18 = 0;
  if ( a1[1025] > 0 )
  {
    v19 = a1;
    do
    {
      DLXSprite_Save(*v19, v15);
      v18 = v20 + 1;
      ++v19;
    }
    while ( v18 < a1[1025] );
  }
  return fclose_(v18);
}
// 405DD9: variable 'v4' is possibly undefined
// 405DE0: variable 'v7' is possibly undefined
// 405E83: variable 'v20' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51F290: using guessed type int dword_51F290[];
// 52028C: using guessed type int dword_52028C;

//----- (00405EC0) --------------------------------------------------------
int  DLX_GetSpriteForChar(int a1, int a2)
{
  return *(_DWORD *)(a1 + 4 * a2);
}

//----- (00405ED0) --------------------------------------------------------
int  DLXSpriteSet_GetLastCharIndex(int a1)
{
  LOWORD(a1) = *(_WORD *)(a1 + 4100);
  return a1 - 1;
}

//----- (00405EE0) --------------------------------------------------------
__int16  DLX_GetSpriteWidth(int a1, unsigned __int16 a2)
{
  return *(_WORD *)(DLX_GetSpriteForChar(a1, a2) + 2);
}

//----- (00405EF0) --------------------------------------------------------
__int16  DLX_GetSpriteHeight(int a1, unsigned __int16 a2)
{
  return *(_WORD *)DLX_GetSpriteForChar(a1, a2);
}

//----- (00405F00) --------------------------------------------------------
char  DLXSpriteSet_DrawText(int a1, int a2, int a3, unsigned __int8 *a4)
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

  (void)Time_Now(a3, a2);
  source_entry = a4;
  for ( palette_index = 0; palette_index < 256; ++palette_index )
  {
    best_distance = 768;
    best_index = 0;
    target_red = source_entry[0];
    target_green = source_entry[1];
    target_blue = source_entry[2];
    candidate_index = 1;
    candidate_palette_entry = (unsigned __int8 *)(uintptr_t)(unsigned int)(a3 + 4);
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
  if ( a2 == -1 )
  {
    last_char_index = (unsigned __int16)DLXSpriteSet_GetLastCharIndex(a1);
    for ( remapped_sprite = 0; remapped_sprite <= (int)last_char_index; ++remapped_sprite )
    {
      DLXSprite_RemapPalette(DLX_GetSpriteForChar(a1, remapped_sprite), (unsigned __int8 *)remap_table);
    }
    return (char)last_char_index;
  }
  return DLXSprite_RemapPalette(DLX_GetSpriteForChar(a1, a2), (unsigned __int8 *)remap_table);
}

//----- (004060A0) --------------------------------------------------------
int  DLXSpriteSet_DrawFormattedText(DWORD a1, int a2, int a3, const char *a4)
{
  unsigned __int8 *v6; // eax

  v6 = (unsigned __int8 *)Mem_Alloc(1024, (int)(uintptr_t)a4, 0, a1);
  if ( v6 )
    v6 = (unsigned __int8 *)Palette_LoadFromQueryHandle((intptr_t)v6, (intptr_t)a4);
  DLXSpriteSet_DrawText(a1, a2, a3, v6);
  return j__nfree_();
}

//----- (004060E0) --------------------------------------------------------
DWORD  DLXSprite_LoadCachedEntry(DWORD a1, char *a2, int a3)
{
  int query_handle; // [esp+100h] [ebp-1Ch] BYREF
  int entry_offset; // [esp+104h] [ebp-18h]
  int entry_end_offset; // [esp+108h] [ebp-14h]
  int payload_size;
  unsigned int payload_handle;
  char path[256]; // [esp+0h] [ebp-11Ch] BYREF

  *(_DWORD *)(a1 + 10) = 0;
  strcpy(path, aGfx_3);
  strcat(path, a2);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  if ( !query_handle )
    return a1;
  Compat_QueryRead(query_handle, g_DlxDirectoryEntryStartOffsets, 4096);
  entry_offset = g_DlxDirectoryEntryStartOffsets[a3];
  if ( g_DlxDirectoryEntryEndOffsets[a3] )
    entry_end_offset = g_DlxDirectoryEntryEndOffsets[a3];
  else
    entry_end_offset = IO_QueryVTableStreamSize(query_handle);
  *(_DWORD *)(a1 + 14) = entry_end_offset - entry_offset;
  Compat_QuerySeek(query_handle, entry_offset);
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)a1, 10);
  payload_size = *(_DWORD *)(a1 + 14) - 10;
  payload_handle = (unsigned int)nmalloc_(payload_size, 4);
  *(_DWORD *)(a1 + 10) = payload_handle;
  if ( !*(_DWORD *)(a1 + 10) )
  {
    Debug_Log(0, 10, payload_size, (int)aNotEnoughMem_7);
    App_RequestQuit((int)aNotEnoughMem_8);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)payload_handle, payload_size);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  return a1;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 51E288: using guessed type int dword_51E288[];
// 51E28C: using guessed type int dword_51E28C[1024];

//----- (00406260) --------------------------------------------------------
int  DLXSprite_ConstructFromBuffer(int result, int a2, int a3)
{
  *(_DWORD *)(result + 18) = 0;
  *(_DWORD *)(result + 14) = a3;
  qmemcpy((void *)result, (const void *)a2, 8u);
  qmemcpy((void *)(result + 8), (const void *)(a2 + 8), 2u);
  *(_DWORD *)(result + 10) = a2 + 10;
  return result;
}

//----- (00406350) --------------------------------------------------------
int  DLXSprite_ConstructOwningCopy(int a1, DWORD a2)
{
  int v2; // ecx

  *(_DWORD *)(a1 + 10) = 0;
  *(_DWORD *)(a1 + 18) = 1;
  DLXSprite_CopyFrom(a1, a2);
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
int  DLXSprite_CopyFrom(int a1, DWORD a2)
{
  unsigned int v6; // ecx
  int v7; // edx
  unsigned int v8; // ecx
  _DWORD v10[6]; // [esp+0h] [ebp-18h] BYREF

  DLXSprite_Destroy(a1);
  qmemcpy((void *)a1, (const void *)a2, v6);
  *(_DWORD *)(a1 + 14) = *(_DWORD *)(a2 + 14);
  *(_DWORD *)(a1 + 18) = 1;
  v10[0] = nmalloc_(4, v7);
  qmemcpy((void *)(a1 + 10), v10, v8);
  if ( !*(_DWORD *)(a1 + 10) )
  {
    Debug_Log(0, a1, a2, (int)aNotEnoughMe_15);
    App_RequestQuit((int)aNotEnoughMe_16);
  }
  qmemcpy(*(void **)(a1 + 10), *(const void **)(a2 + 10), *(_DWORD *)(a1 + 14) - 10);
  return a1;
}
// 4063B2: variable 'v6' is possibly undefined
// 4063D9: variable 'v7' is possibly undefined
// 4063E7: variable 'v8' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);

//----- (00406460) --------------------------------------------------------
int  DLXSprite_Save(int a1, int a2)
{
  fwrite_((const void *)a1, 10, a2, 1);
  return fwrite_(*(const void **)(a1 + 10), *(_DWORD *)(a1 + 14) - 10, a2, 1);
}

//----- (004064A0) --------------------------------------------------------
char  DLXSprite_RemapPalette(int a1, const unsigned __int8 *a2)
{
  unsigned __int16 *v3; // esi
  _BYTE *v5; // edx
  int v6; // ecx
  int v7; // ebx
  int i; // [esp+0h] [ebp-18h]

  v3 = (unsigned __int16 *)a1;
  v5 = (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 10);
  if ( *(_WORD *)(a1 + 4) )
    App_RequestQuit((int)aConvertsprUnsu);
  for ( i = 0; v3[1] > i; ++i )
  {
    v6 = 0;
    while ( v6 < *v3 )
    {
      LOBYTE(a1) = *v5++;
      if ( (a1 & 0x80u) == 0 )
      {
        if ( !(_BYTE)a1 )
          App_RequestQuit((int)aCannotConform2);
        v6 += (unsigned __int8)a1;
        while ( (_BYTE)a1 )
        {
          v7 = (unsigned __int8)*v5++;
          LOBYTE(a1) = a1 - 1;
          *(v5 - 1) = a2[v7];
        }
      }
      else
      {
        LOBYTE(a1) = a1 & 0x7F;
        v6 += (unsigned __int8)a1;
      }
    }
  }
  return a1;
}

//----- (00406540) --------------------------------------------------------
signed int  UnitBattle_ScanSpriteMinOpaqueRunLength(unsigned __int16 *a1)
{
  unsigned __int16 v2; // dx
  unsigned __int8 *v3; // eax
  int i; // ebp
  int v5; // esi
  int v6; // edx
  unsigned __int8 v7; // bl
  int v8; // ecx
  int v10; // [esp+0h] [ebp-1Ch]

  v10 = 100000;
  v2 = a1[2];
  v3 = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 5);
  if ( !v2 )
  {
    for ( i = 0; i < a1[1]; ++i )
    {
      v5 = 0;
      v6 = 0;
      while ( v6 < *a1 )
      {
        v7 = *v3++;
        if ( (v7 & 0x80u) == 0 )
        {
          if ( v7 )
          {
            v6 += v7;
            v3 += v7;
          }
          else
          {
            v8 = v3[-*(_DWORD *)v3];
            v3 += 4;
            v6 += v8;
          }
        }
        else
        {
          v5 = v7 & 0x7F;
          v6 += v5;
        }
      }
      if ( v5 < v10 )
        v10 = v5;
    }
  }
  return v10;
}

//----- (004065D0) --------------------------------------------------------
int  UnitBattle_ScanSpriteFirstOpaqueRunLength(unsigned __int16 *a1)
{
  unsigned __int16 v2; // dx
  unsigned __int8 *v3; // eax
  int i; // ebp
  int v5; // esi
  int v6; // edx
  unsigned __int8 v7; // bl
  unsigned __int8 v8; // bl
  int v9; // ecx
  int v10; // [esp+0h] [ebp-1Ch]

  v10 = 100000;
  v2 = a1[2];
  v3 = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 5);
  if ( !v2 )
  {
    for ( i = 0; i < a1[1]; ++i )
    {
      v5 = 0;
      v6 = 0;
      while ( v6 < *a1 )
      {
        v7 = *v3++;
        if ( (v7 & 0x80u) == 0 )
        {
          if ( v7 )
          {
            v6 += v7;
            v3 += v7;
          }
          else
          {
            v9 = v3[-*(_DWORD *)v3];
            v3 += 4;
            v6 += v9;
          }
        }
        else
        {
          v8 = v7 & 0x7F;
          v6 += v8;
          if ( !v5 )
            v5 = v8;
        }
      }
      if ( v5 < v10 )
        v10 = v5;
    }
  }
  return v10;
}

//----- (00406650) --------------------------------------------------------
int  UnitBattle_CountLeadingBlankSpriteRows(unsigned __int16 *a1)
{
  char *v2; // ecx
  int v3; // esi
  int i; // edi
  int v5; // edx
  char v6; // al
  int v7; // [esp+0h] [ebp-1Ch]

  v2 = (char *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 5);
  v3 = 0;
  v7 = 0;
  if ( !a1[2] )
  {
    for ( i = 0; i < a1[1] && !v3; ++i )
    {
      v5 = 0;
      while ( v5 < *a1 )
      {
        v6 = *v2++;
        if ( v6 >= 0 )
          v3 = 1;
        else
          v5 += v6 & 0x7F;
      }
      ++v7;
    }
  }
  return v7;
}

//----- (004066C0) --------------------------------------------------------
int  UnitBattle_CountTrailingBlankSpriteRows(unsigned __int16 *a1)
{
  unsigned __int8 *v2; // eax
  int v3; // esi
  int i; // ebp
  int v5; // edx
  unsigned __int8 v6; // bl
  int v7; // ecx

  v2 = (unsigned __int8 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 5);
  v3 = 0;
  if ( !a1[2] )
  {
    for ( i = 0; i < a1[1]; ++i )
    {
      v5 = 0;
      while ( v5 < *a1 )
      {
        v6 = *v2++;
        if ( (v6 & 0x80u) == 0 )
        {
          v3 = 0;
          if ( v6 )
          {
            v5 += v6;
            v2 += v6;
          }
          else
          {
            v7 = v2[-*(_DWORD *)v2];
            v2 += 4;
            v5 += v7;
          }
        }
        else
        {
          v5 += v6 & 0x7F;
        }
      }
      ++v3;
    }
  }
  return v3;
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
  int v3; // esi
  char v4; // bl
  signed int v5; // ebp
  int v6; // ecx
  _DWORD *Surface; // eax
  int v8; // esi
  __int16 SpriteWidth; // ax
  int i; // esi
  int SpriteForChar; // eax
  int v12; // eax
  __int16 v13; // ax
  int min_base_action_points; // eax
  void *result; // eax
  char v16; // [esp+1Ch] [ebp-18h]
  _DWORD *v17; // [esp+1Ch] [ebp-18h]
  void *v18; // [esp+20h] [ebp-14h]

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
    v18 = g_RenderDevice;
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
    v3 = 100 * UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_current_ap",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      v3);
    v4 = gameData;
    min_base_action_points = UnitStack_GetMinBaseActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex);
    if ( min_base_action_points <= 0 )
      v5 = 0;
    else
      v5 = v3 / min_base_action_points;
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_before_surface_alloc",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      v5);
    Surface = (_DWORD *)Mem_Alloc(188, 0, v4, v5);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_after_surface_alloc",
      (int)(uintptr_t)Surface,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      v5);
    v8 = (int)Surface;
    if ( Surface )
    {
      SpriteWidth = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 7u);
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_after_sprite_width",
        SpriteWidth,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        v5);
      Surface = Render_CreateSurface(v8, 100, SpriteWidth);
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_after_create_surface",
        (int)(uintptr_t)Surface,
        Surface ? Surface[1] : 0,
        g_UnitStackSlotSelectedFlags[0],
        v5);
    }
    v17 = Surface;
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_surface_ready",
      (int)(uintptr_t)v17,
      v17 ? v17[1] : 0,
      (int)(uintptr_t)g_UnitStackSlotSelectedFlags,
      g_UnitStackSlotSelectedFlags[0]);
    g_RenderDevice = Surface;
    for ( i = 0; i < v5; ++i )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 7);
      Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
    }
    while ( i < 100 )
    {
      v12 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 6);
      ++i;
      Compat_RenderDeviceDrawMenuSprite(0, 0, v12, 1);
    }
    v13 = DLX_GetSpriteWidth(g_ActiveUiSpriteSet, 7u);
    Diagnostics_TraceWorldMapActionEvent(
      "status_panel_before_blit",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      v17 ? v17[1] : 0);
    Render_FillRect(v17, 0, 0, 0, 0x63u, v13 - 1, 0x16Bu, 0x1D4u);
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
    if ( v17 )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "status_panel_before_destroy",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        (int)(uintptr_t)v17);
      RenderSurface_InvokeSlot0(v17, 2);
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
    result = v18;
    g_RenderDevice = v18;
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
  int v4; // esi
  int v5; // ebp
  unsigned __int16 *v6; // edx
  unsigned int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  _WORD *v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
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
  int v32; // edi
  int v33; // ecx
  unsigned __int16 v34; // ax
  int v35; // esi
  int v36; // edx
  unsigned __int8 v37; // al
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
  __int64 v53; // rax
  int v54; // ecx
  int v55; // esi
  int v56; // ecx
  int v57; // ebx
  _WORD *v58; // edx
  int v59; // edx
  int v60; // esi
  int kk; // ecx
  int v62; // edx
  unsigned __int16 v63; // di
  unsigned __int8 v64; // dl
  __int16 v65; // di
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
  int v77; // [esp+4h] [ebp-78h]
  int v78; // [esp+8h] [ebp-74h]
  int v79; // [esp+Ch] [ebp-70h]
  int v80; // [esp+10h] [ebp-6Ch]
  int v81; // [esp+20h] [ebp-5Ch]
  int v82; // [esp+58h] [ebp-24h]
  int v83; // [esp+5Ch] [ebp-20h]
  int v84; // [esp+60h] [ebp-1Ch]
  int jj; // [esp+64h] [ebp-18h]
  unsigned __int16 v86; // [esp+68h] [ebp-14h]
  unsigned __int16 v87; // [esp+6Ch] [ebp-10h]

  if ( g_WorldMapViewportScrolledFlag )
  {
    g_WorldMapViewportScrolledFlag = 0;
  }
  else
  {
    v80 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    for ( i = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET); i < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7; ++i )
    {
      v4 = 14 * i;
      DD_Pump((int)&g_RenderState, ii, i);
      ii = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      v5 = i + 1;
      for ( j = TILE_TERRAIN_ROW_STRIDE * ii; ; j += TILE_TERRAIN_ROW_STRIDE )
      {
        v1 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
        if ( ii >= v1 )
          break;
        v6 = (unsigned __int16 *)(v4 + j + gameData);
        if ( *v6 != 0xFFFF && *v6 < TERRAIN_ANIMATION_REMAP_COUNT )
        {
          v86 = *(__int16 *)((char *)&g_TerrainAnimationRemapTable + 3 * *v6);
          if ( v86 != 0xFFFF )
          {
            v7 = Time_Now(j, (int)v6);
            if ( v7 > *(_DWORD *)((char *)v6 + 6) )
            {
              v20 = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * *v6];
              v9 = Time_Now(j, v20);
              *(_DWORD *)((char *)v6 + 6) = v9 + v20;
              *v6 = v86;
              WorldMap_RedrawTileIfVisible(ii, i);
              if ( !*(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) && v86 == 36 )
              {
                v12 = (_WORD *)(14 * v5 + j + gameData);
                if ( *v12 == 36 )
                {
                  *v12 = 771;
                  v14 = (unsigned __int8)g_SpecialTileAnimFrameDuration;
                  v13 = Time_Now(j, v14);
                  *(_DWORD *)((char *)v12 + 6) = v13 + v14;
                  WorldMap_RedrawTileIfVisible(ii, i + 1);
                }
              }
            }
          }
        }
        v81 = v4 + j + gameData;
        v16 = *(unsigned __int16 *)(v81 + 2);
        if ( v16 == 0xFFFE )
        {
          *(_WORD *)(v81 + 2) = -1;
          WorldMap_RedrawTileIfVisible(ii, i);
        }
        else if ( v16 != 0xFFFF && v16 < TERRAIN_ANIMATION_REMAP_COUNT )
        {
          v87 = *(__int16 *)((char *)&g_TerrainAnimationRemapTable + 3 * v16);
          if ( v87 != 0xFFFF )
          {
            v17 = Time_Now(j, v81);
            if ( v17 > *(_DWORD *)((char *)v6 + 10) )
            {
              if ( v87 == 65534 )
              {
                v6[1] = -1;
              }
              else
              {
                v20 = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * v6[1]];
                v19 = Time_Now(j, v20);
                *(_DWORD *)((char *)v6 + 10) = v19 + v20;
                v6[1] = v87;
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
      v32 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      v22 = 2 * v32;
      v82 = 14 * v32;
      while ( v32 < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
      {
        DD_Pump((int)&g_RenderState, ii, v32);
        v33 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        for ( ii = TILE_TERRAIN_ROW_STRIDE * v33; ; ii += TILE_TERRAIN_ROW_STRIDE )
        {
          v22 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
          if ( v33 >= v22 )
            break;
          HIWORD(v35) = 0;
          v34 = *(_WORD *)(ii + gameData + v82);
          LOWORD(v35) = v34;
          if ( v34 >= 0xDFu && v35 <= 234
            || (HIWORD(v36) = 0, v34 >= 0x19Fu) && (LOWORD(v36) = *(_WORD *)(ii + gameData + v82), v36 <= 422)
            || *(_WORD *)(ii + gameData + v82) == 587
            || *(unsigned __int16 *)(ii + gameData + v82) >= 0x283u
            && *(unsigned __int16 *)(ii + gameData + v82) <= 0x2A2u )
          {
            WorldMap_RedrawTileIfVisible(v33, v32);
          }
          ++v33;
        }
        v23 = v82 + 14;
        ++v32;
        v82 += 14;
      }
    }
    if ( Time_Now(v23, v22) > (unsigned int)g_WorldMap_NextTileStateAnimTime )
    {
      v37 = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
      if ( v37 )
      {
        if ( v37 <= 1u )
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
        else if ( v37 == 2 )
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
                v53 = rand_(v50, 7);
                if ( (unsigned int)v53 < 0x333 )
                {
                  *(_WORD *)(v51 + gameData + v83 + 2) = g_WorldMapAmbientAnimFramesSetC[4 * (unsigned int)rand_(v50, HIDWORD(v53)) / 0x7FFF];
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
      v55 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      v77 = 14 * v55;
      v78 = 14 * v55 + 14;
      while ( v55 < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
      {
        v56 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        v57 = TILE_TERRAIN_ROW_STRIDE * v56;
        while ( v56 < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
        {
          v58 = (_WORD *)(v57 + gameData + v77);
          if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) )
          {
            if ( *v58 == 771 && (unsigned int)rand_(v56, v58) < 0x199 )
            {
              *(_WORD *)(v77 + v57 + gameData) = 772;
              WorldMap_RedrawTileIfVisible(v56, v55);
            }
          }
          else if ( *v58 == 36 && *(_WORD *)(v78 + v57 + gameData) == 36 && (unsigned int)rand_(v56, 36) < 0x28 )
          {
            *(_WORD *)(v77 + v57 + gameData) = 771;
            WorldMap_RedrawTileIfVisible(v56, v55);
          }
          v57 += TILE_TERRAIN_ROW_STRIDE;
          ++v56;
        }
        ++v55;
        v77 += 14;
        v78 += 14;
      }
      v79 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      for ( jj = 14 * v79; ; jj += 14 )
      {
        v59 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7;
        if ( v59 <= v79 )
          break;
        v60 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        for ( kk = TILE_TERRAIN_ROW_STRIDE * v60; ; kk += TILE_TERRAIN_ROW_STRIDE )
        {
          v62 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
          if ( v60 >= v62 )
            break;
          v63 = *(_WORD *)(jj + kk + gameData);
          if ( v63 >= 0x2Du && v63 <= 0x51u && (unsigned int)rand_(kk, v62) < 0xA3 )
          {
            v64 = *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET);
            v65 = v63 - 46;
            if ( v64 )
            {
              if ( v64 <= 1u )
              {
                switch ( v65 )
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
              switch ( v65 )
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
            WorldMap_RedrawTileIfVisible(v60, v79);
          }
          ++v60;
        }
        ++v79;
      }
      g_WorldMap_NextTileStateAnimTime = Time_Now(v79, v59) + 10;
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
unsigned int  WorldMap_TickPaletteFlashEffect(int a1, int a2, int a3)
{
  unsigned int result; // eax
  __lock *v4; // ecx
  int v5; // edx
  int v6; // ecx

  if ( a1 )
  {
    g_WorldMap_PaletteFlashStep = 0;
    g_PaletteCrossfadeNextStepTime = Time_Now(a3, 0);
  }
  result = Time_Now(a3, a2);
  if ( result >= g_PaletteCrossfadeNextStepTime && g_WorldMap_PaletteFlashStep <= 10 )
  {
    v4 = (__lock *)g_WorldMap_PaletteFlashStep++;
    Palette_CrossfadeStep((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, v4, 10);
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
  int v1; // esi
  int v2; // ebx
  int v4; // eax
  int v5; // esi
  int v6; // ecx

  Render_Pump();
  v1 = g_MouseCursorRawX >> g_CursorCoordShift;
  v2 = g_MouseCursorRawY >> g_CursorCoordShift;
  while ( DD_IsLost((int)g_RenderState) )
  {
    WorldMap_RedrawFrame(v2);
    DD_Pump((int)g_RenderState, v2);
    v4 = (g_MouseCursorRawX >> g_CursorCoordShift) - v1;
    if ( v4 <= 0 )
      v4 = v1 - (g_MouseCursorRawX >> g_CursorCoordShift);
    if ( v4 < 8 )
    {
      if ( (g_MouseCursorRawY >> g_CursorCoordShift) - v2 <= 0 )
      {
        if ( v2 - (g_MouseCursorRawY >> g_CursorCoordShift) >= 8 )
          goto LABEL_7;
      }
      else if ( (g_MouseCursorRawY >> g_CursorCoordShift) - v2 >= 8 )
      {
        goto LABEL_7;
      }
    }
    else
    {
LABEL_7:
      *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) += ((g_MouseCursorRawX >> g_CursorCoordShift)
                                       - v1
                                       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - v1) >> 31, 3)
                                        + 8 * (((g_MouseCursorRawX >> g_CursorCoordShift) - v1) >> 31))) >> 3;
      *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) += ((g_MouseCursorRawY >> g_CursorCoordShift)
                                       - v2
                                       - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - v2) >> 31, 3)
                                        + 8 * (((g_MouseCursorRawY >> g_CursorCoordShift) - v2) >> 31))) >> 3;
      if ( *(int *)(gameData + MAP_VIEW_LEFT_OFFSET) < 0 )
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = 0;
      v5 = *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 > v5 )
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = v5 - 9;
      if ( *(int *)(gameData + MAP_VIEW_TOP_OFFSET) < 0 )
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = 0;
      v6 = *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET);
      if ( *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 > v6 )
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = v6 - 7;
      WorldMap_RedrawViewport(1);
      v1 = g_MouseCursorRawX >> g_CursorCoordShift;
      v2 = g_MouseCursorRawY >> g_CursorCoordShift;
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
  unsigned int v3; // eax
  unsigned int v4; // edx
  int v5; // edx
  int v6; // ecx
  int v7; // ebx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ebx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int result; // eax
  int v17; // esi
  int v18; // ecx
  unsigned int v19; // edx

  v3 = Time_Now(g_WorldMapKeyScrollRepeatTime, 16 - *(unsigned __int8 *)(gameData + 147171) + g_WorldMapKeyScrollRepeatTime);
  if ( v3 > v4 && !g_WorldMap_KeyboardInputDisabled && !Input_IsKeyPressed(56) )
  {
    if ( Input_IsKeyPressed(203) )
    {
      v7 = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      if ( v7 > 0 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) = v7 - 1;
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
      v12 = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      if ( v12 > 0 )
      {
        *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) = v12 - 1;
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
    v17 = (((g_MouseCursorRawX >> g_CursorCoordShift)
          - 32
          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
           + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
        + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    result = DD_IsLost((int)g_RenderState);
    if ( result )
    {
      v18 = (((g_MouseCursorRawY >> g_CursorCoordShift)
            - 16
            - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
             + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
          + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
      result = TILE_INDEX(v17, v18);
      v19 = *(unsigned __int16 *)result;
      if ( (unsigned __int16)v19 == 0xFFFF )
        return Render_RestoreLostSurfaces();
      if ( v19 < 0x8000 )
      {
        result = UNIT_STACK_STRIDE * v19;
        if ( *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v19 + 147894) )
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

