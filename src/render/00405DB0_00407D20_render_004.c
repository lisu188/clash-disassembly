/* Generated from src/recovered/render/00401A40_render.inc.c; original address order retained. */
#include "../recovered_internal.h"

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
  char cur_char; // al
  char next_char; // al
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
    cur_char = *v8;
    *append_cursor = *v8;
    if ( !cur_char )
      break;
    next_char = v8[1];
    v8 += 2;
    append_cursor[1] = next_char;
    append_cursor += 2;
  }
  while ( next_char );
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
  int col_right_bound; // edx
  int j; // ecx
  int i; // edi
  int row_offset; // esi
  int next_row_index; // ebp
  unsigned __int16 *tile_ptr; // edx
  unsigned int now; // eax
  int v8; // edx
  int anim_now; // eax
  int v10; // edx
  int v11; // ecx
  _WORD *next_row_tile; // eax
  int special_now; // eax
  int special_frame_duration; // edx
  int v15; // ecx
  int overlay_frame; // eax
  unsigned int overlay_now; // eax
  int v18; // edx
  int overlay_anim_now; // eax
  int anim_frame_duration; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int k; // eax
  int cycle_remap_offset_a; // edx
  int m; // eax
  int cycle_remap_offset_b; // edx
  int n; // eax
  int cycle_remap_offset_c; // edx
  int palette_now; // eax
  int v31; // edx
  int anim_row; // edi
  int anim_col; // ecx
  unsigned __int16 tile_code; // ax
  int v35; // esi
  int v36; // edx
  unsigned __int8 map_theme; // al
  int setA_row; // esi
  int setA_col; // ecx
  int setA_col_offset; // ebx
  _WORD *setA_tile; // eax
  int v42; // edx
  int v43; // ecx
  int setB_row; // esi
  int setB_col; // ecx
  int setB_col_offset; // ebx
  _WORD *setB_tile; // eax
  int v48; // ecx
  int setC_row; // esi
  int setC_col; // ecx
  int setC_col_offset; // ebx
  _WORD *setC_tile; // eax
  __int64 random_value; // rax
  int v54; // ecx
  int row_cursor; // esi
  int col_cursor; // ecx
  int col_offset; // ebx
  _WORD *smoke_tile; // edx
  int row_bottom_bound; // edx
  int deco_col; // esi
  int kk; // ecx
  int deco_col_right_bound; // edx
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
  int setA_row_offset; // [esp+0h] [ebp-7Ch]
  int smoke_row_offset; // [esp+4h] [ebp-78h]
  int next_row_offset; // [esp+8h] [ebp-74h]
  int deco_row; // [esp+Ch] [ebp-70h]
  int saved_render_handle; // [esp+10h] [ebp-6Ch]
  int tile_addr; // [esp+20h] [ebp-5Ch]
  int anim_row_offset; // [esp+58h] [ebp-24h]
  int setC_row_offset; // [esp+5Ch] [ebp-20h]
  int setB_row_offset; // [esp+60h] [ebp-1Ch]
  int jj; // [esp+64h] [ebp-18h]
  unsigned __int16 next_frame; // [esp+68h] [ebp-14h]
  unsigned __int16 next_overlay_frame; // [esp+6Ch] [ebp-10h]

  if ( g_WorldMapViewportScrolledFlag )
  {
    g_WorldMapViewportScrolledFlag = 0;
  }
  else
  {
    saved_render_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    for ( i = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET); i < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7; ++i )
    {
      row_offset = 14 * i;
      DD_Pump((int)&g_RenderState, ii, i);
      ii = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
      next_row_index = i + 1;
      for ( j = TILE_TERRAIN_ROW_STRIDE * ii; ; j += TILE_TERRAIN_ROW_STRIDE )
      {
        col_right_bound = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
        if ( ii >= col_right_bound )
          break;
        tile_ptr = (unsigned __int16 *)(row_offset + j + gameData);
        if ( *tile_ptr != 0xFFFF && *tile_ptr < TERRAIN_ANIMATION_REMAP_COUNT )
        {
          next_frame = *(__int16 *)((char *)&g_TerrainAnimationRemapTable + 3 * *tile_ptr);
          if ( next_frame != 0xFFFF )
          {
            now = Time_Now(j, (int)tile_ptr);
            if ( now > *(_DWORD *)((char *)tile_ptr + 6) )
            {
              anim_frame_duration = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * *tile_ptr];
              anim_now = Time_Now(j, anim_frame_duration);
              *(_DWORD *)((char *)tile_ptr + 6) = anim_now + anim_frame_duration;
              *tile_ptr = next_frame;
              WorldMap_RedrawTileIfVisible(ii, i);
              if ( !*(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) && next_frame == 36 )
              {
                next_row_tile = (_WORD *)(14 * next_row_index + j + gameData);
                if ( *next_row_tile == 36 )
                {
                  *next_row_tile = 771;
                  special_frame_duration = (unsigned __int8)g_SpecialTileAnimFrameDuration;
                  special_now = Time_Now(j, special_frame_duration);
                  *(_DWORD *)((char *)next_row_tile + 6) = special_now + special_frame_duration;
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
            overlay_now = Time_Now(j, tile_addr);
            if ( overlay_now > *(_DWORD *)((char *)tile_ptr + 10) )
            {
              if ( next_overlay_frame == 65534 )
              {
                tile_ptr[1] = -1;
              }
              else
              {
                anim_frame_duration = (unsigned __int8)g_TerrainAnimFrameDurationTable[3 * tile_ptr[1]];
                overlay_anim_now = Time_Now(j, anim_frame_duration);
                *(_DWORD *)((char *)tile_ptr + 10) = overlay_anim_now + anim_frame_duration;
                tile_ptr[1] = next_overlay_frame;
              }
              WorldMap_RedrawTileIfVisible(ii, i);
            }
          }
        }
        ++ii;
      }
    }
    if ( Time_Now(j, col_right_bound) > (unsigned int)g_WorldMap_NextPaletteAnimTime )
    {
      g_ColorCyclePrimaryFrameIndex = *(__int16 *)((char *)&g_SpriteCodeRemapTable + 3 * (unsigned __int16)g_ColorCyclePrimaryFrameIndex);
      for ( k = 223; k != 235; g_ColorCycleStateArrayBase[k] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + cycle_remap_offset_a) )
        cycle_remap_offset_a = 3 * (unsigned __int16)g_Font_GlyphRemapTable[k++];
      for ( m = 643; m != 675; g_Render_AnimatedFrameTable[m] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + cycle_remap_offset_b) )
      {
        cycle_remap_offset_b = 3 * (unsigned __int16)g_Font_GlyphRemapTable[m];
        m += 8;
      }
      for ( n = 415; n != 423; g_ColorCycleStateArrayBase[n] = *(__int16 *)((char *)&g_SpriteCodeRemapTable + cycle_remap_offset_c) )
        cycle_remap_offset_c = 3 * (unsigned __int16)g_Font_GlyphRemapTable[n++];
      palette_now = Time_Now(v23, (unsigned __int8)g_Render_SpriteAnimDelayBytes[3 * (unsigned __int16)g_ColorCycleDelayLookupIndex]);
      g_WorldMap_NextPaletteAnimTime = v31 + palette_now;
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
          setB_row = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
          setB_row_offset = 14 * setB_row;
          while ( setB_row < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
          {
            setB_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
            setB_col_offset = TILE_TERRAIN_ROW_STRIDE * setB_col;
            while ( setB_col < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
            {
              setB_tile = (_WORD *)(setB_row_offset + setB_col_offset + gameData);
              if ( *setB_tile == 7 && (unsigned __int16)setB_tile[1] == 0xFFFF && (unsigned int)rand_() < 0x333 )
              {
                *(_WORD *)(setB_col_offset + gameData + setB_row_offset + 2) = g_WorldMapAmbientAnimFramesSetB[(unsigned int)(rand_() / 0x7FFFuLL)];
                WorldMap_RedrawTileIfVisible(v48, setB_row);
              }
              setB_col_offset += TILE_TERRAIN_ROW_STRIDE;
              ++setB_col;
            }
            ++setB_row;
            setB_row_offset += 14;
          }
        }
        else if ( map_theme == 2 )
        {
          setC_row = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
          setC_row_offset = 14 * setC_row;
          while ( setC_row < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
          {
            setC_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
            setC_col_offset = TILE_TERRAIN_ROW_STRIDE * setC_col;
            while ( setC_col < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
            {
              setC_tile = (_WORD *)(setC_row_offset + setC_col_offset + gameData);
              if ( *setC_tile == 7 && (unsigned __int16)setC_tile[1] == 0xFFFF )
              {
                random_value = rand_();
                if ( (unsigned int)random_value < 0x333 )
                {
                  *(_WORD *)(setC_col_offset + gameData + setC_row_offset + 2) = g_WorldMapAmbientAnimFramesSetC[4 * (unsigned int)rand_() / 0x7FFF];
                  WorldMap_RedrawTileIfVisible(v54, setC_row);
                }
              }
              setC_col_offset += TILE_TERRAIN_ROW_STRIDE;
              ++setC_col;
            }
            ++setC_row;
            setC_row_offset += 14;
          }
        }
      }
      else
      {
        setA_row = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
        setA_row_offset = 14 * setA_row;
        while ( setA_row < *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7 )
        {
          setA_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
          setA_col_offset = TILE_TERRAIN_ROW_STRIDE * setA_col;
          while ( setA_col < *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9 )
          {
            setA_tile = (_WORD *)(setA_row_offset + setA_col_offset + gameData);
            if ( *setA_tile == 7 && (unsigned __int16)setA_tile[1] == 0xFFFF && (unsigned int)rand_() < 0x333 )
            {
              *(_WORD *)(setA_row_offset + setA_col_offset + gameData + 2) = g_WorldMapAmbientAnimFramesSetA[6 * (int)rand_() / 0x7FFFu];
              WorldMap_RedrawTileIfVisible(v43, setA_row);
            }
            setA_col_offset += TILE_TERRAIN_ROW_STRIDE;
            ++setA_col;
          }
          ++setA_row;
          setA_row_offset += 14;
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
          smoke_tile = (_WORD *)(col_offset + gameData + smoke_row_offset);
          if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) )
          {
            if ( *smoke_tile == 771 && (unsigned int)rand_() < 0x199 )
            {
              *(_WORD *)(smoke_row_offset + col_offset + gameData) = 772;
              WorldMap_RedrawTileIfVisible(col_cursor, row_cursor);
            }
          }
          else if ( *smoke_tile == 36 && *(_WORD *)(next_row_offset + col_offset + gameData) == 36 && (unsigned int)rand_() < 0x28 )
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
        row_bottom_bound = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET) + 7;
        if ( row_bottom_bound <= deco_row )
          break;
        deco_col = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
        for ( kk = TILE_TERRAIN_ROW_STRIDE * deco_col; ; kk += TILE_TERRAIN_ROW_STRIDE )
        {
          deco_col_right_bound = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET) + 9;
          if ( deco_col >= deco_col_right_bound )
            break;
          tile_frame = *(_WORD *)(jj + kk + gameData);
          if ( tile_frame >= 0x2Du && tile_frame <= 0x51u && (unsigned int)rand_() < 0xA3 )
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
      g_WorldMap_NextTileStateAnimTime = Time_Now(deco_row, row_bottom_bound) + 10;
    }
    Render_SetResourceHandle((int)&g_MainRenderDevice, saved_render_handle);
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
