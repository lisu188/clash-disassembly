/* Generated from src/recovered/render/00401A40_render.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "render_internal.h"
#include "render_state.h"
#include "render_shared_state.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

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

  *(_DWORD *)(uintptr_t)(render_device + 212) = bits_per_pixel;
  dd_context = (LPVOID *)(uintptr_t)Mem_Alloc(44, a2, bits_per_pixel, context);
  if ( dd_context )
    dd_context = (LPVOID *)Render_ZeroDirectDrawObjectFields((_DWORD*)(dd_context));
  v19 = 0;
  v18 = *(_DWORD **)(uintptr_t)(render_device + 212);
  screen_width = *(_WORD *)(uintptr_t)render_device;
  screen_height = (_DWORD *)(uintptr_t)*(unsigned __int16 *)(uintptr_t)(render_device + 2);
  *(_DWORD *)(uintptr_t)(render_device + 196) = (_DWORD)(uintptr_t)(dd_context);
  Render_InitDirectDrawFullscreenMode(dd_context, (_DWORD *)(uintptr_t)a2, screen_height, (_DWORD *)(uintptr_t)screen_width, v18, 0, v19);
  if ( *(_DWORD *)(uintptr_t)(render_device + 212) == 8 )
    *(_DWORD *)(uintptr_t)(render_device + 188) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(render_device + 196) + 4);
  else
    *(_DWORD *)(uintptr_t)(render_device + 188) = 0;
  v11 = *(_DWORD *)(uintptr_t)(render_device + 196);
  *(_DWORD *)(uintptr_t)(render_device + 192) = 0;
  Render_FillSurfaceSolidColor(*(_DWORD *)(uintptr_t)(v11 + 4), 0, 0);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v12, screen_width, context);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, *(_WORD *)(uintptr_t)render_device, *(_WORD *)(uintptr_t)(render_device + 2));
  pixel_format = *(_DWORD *)(uintptr_t)(render_device + 212);
  *(_DWORD *)(uintptr_t)(render_device + 208) = (_DWORD)(uintptr_t)(Surface);
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
    while ( gray_level < PALETTE_COLOR_COUNT );
    render_context = *(_DWORD *)(uintptr_t)(render_device + 196);
    if ( render_context )
    {
      hr = Compat_DirectDraw_CreatePalette(
             (LPDIRECTDRAW)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)render_context,
             68,
             palette_entries,
             (void *)(uintptr_t)(unsigned int)(render_context + 16));
      if ( hr )
        Render_HandleDirectDrawFatalError(hr, 0);
    }
    surface_handle = 0;
    palette_handle = 0;
    if ( *(_DWORD *)(uintptr_t)(render_device + 188) )
      surface_handle = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(render_device + 188) + 164);
    if ( render_context )
      palette_handle = *(_DWORD *)(uintptr_t)(render_context + 16);
    if ( surface_handle && palette_handle )
    {
      hr = Compat_DirectDrawSurface_SetPalette(
             (LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)surface_handle,
             (void *)(uintptr_t)(unsigned int)palette_handle);
      if ( hr )
        Render_HandleDirectDrawFatalError(hr, 0);
    }
    return Palette_ApplyWithBrightnessOffset((int *)(uintptr_t)render_device, (const void *)(uintptr_t)(render_device + 220));
  }
  else
  {
    result = *(_DWORD *)(uintptr_t)(render_device + 196);
    *(_DWORD *)(uintptr_t)(result + 16) = 0;
  }
  return result;
}
// 404750: variable 'v12' is possibly undefined

CLASH95_INTERNAL void Compat_InvokeNativeComMethod0(int object_handle, unsigned int x86_vtable_offset)
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

CLASH95_INTERNAL void Compat_InvokeCompactSurfaceDestructor(int surface_handle, int flags)
{
  int vtable;
  int (*destructor)(int, int);

  if ( !surface_handle )
    return;
  vtable = *(_DWORD *)(uintptr_t)(surface_handle + 184);
  if ( !vtable )
    return;
  destructor = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(vtable);
  if ( destructor )
    destructor(surface_handle, flags);
}

CLASH95_INTERNAL int Compat_DirectDrawSurfaceHandleIsLost(int surface_handle)
{
  int direct_draw_surface;

  if ( !surface_handle )
    return 0;
  direct_draw_surface = *(_DWORD *)(uintptr_t)(surface_handle + 164);
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

  dd_context = (_DWORD *)(uintptr_t)render_device[49];
  if ( dd_context && *dd_context )
    Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)*dd_context, hWnd, 11);
  dd_object = (_DWORD *)(uintptr_t)render_device[49];
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
  int v5 CLASH95_UNUSED; // eax
  int v6; // ecx
  int cursor_visible; // edi
  int surface_handle;

  render_device = result;
  if ( *(_DWORD *)(uintptr_t)(result + 208) )
  {
    result = *(_DWORD *)(uintptr_t)(result + 212);
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
          Debug_Log(v6, a2, a3, (int)(intptr_t)aRestorescreenc);
          cursor_visible = g_CursorOverlayPresented;
          if ( g_CursorOverlayPresented )
            Render_Pump();
          result = Render_FillRect(
                     (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(render_device + 208),
                     (_DWORD *)(uintptr_t)render_device,
                     0,
                     0,
                     *(_WORD *)(uintptr_t)render_device - 1,
                     *(_WORD *)(uintptr_t)(render_device + 2) - 1,
                     0,
                     0);
          if ( cursor_visible )
            result = Render_Present((int)(intptr_t)g_RenderState);
          *(_DWORD *)(uintptr_t)(render_device + 200) = 0;
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

  render_device = (int)(intptr_t)result;
  copy_target = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(render_device + 208);
  pixel_format = *(_DWORD *)(uintptr_t)(render_device + 212);
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
          saved_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
          Render_FillRect(
            *(_DWORD **)((int)(intptr_t)&g_RenderState + 8),
            0,
            0,
            0,
            *(_WORD *)(uintptr_t)(*(_DWORD *)((int)(intptr_t)&g_RenderState + 60) + 12) - 1,
            *(_WORD *)(uintptr_t)(*(_DWORD *)((int)(intptr_t)&g_RenderState + 60) + 16) - 1,
            *(unsigned __int16 *)&g_RenderState,
            *(unsigned __int16 *)((int)(intptr_t)&g_RenderState + 4));
          Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, saved_handle);
        }
        result = (_DWORD *)(uintptr_t)Render_FillRect(
                             (_DWORD *)(uintptr_t)render_device,
                             copy_target,
                             0,
                             0,
                             *(_WORD *)(uintptr_t)render_device - 1,
                             *(_WORD *)(uintptr_t)(render_device + 2) - 1,
                             0,
                             0);
        if ( cursor_visible )
          result = (_DWORD *)(uintptr_t)Render_Present((int)(intptr_t)&g_RenderState);
        *(_DWORD *)(uintptr_t)(render_device + 200) = 0;
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
            Debug_Log(v7, a3, a4, (int)(intptr_t)aRemsc);
            cursor_visible = g_CursorOverlayPresented;
            if ( g_CursorOverlayPresented )
            {
              g_CursorOverlayPresented = 0;
              saved_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
              Render_FillRect(
                *(_DWORD **)((int)(intptr_t)&g_RenderState + 8),
                0,
                0,
                0,
                *(_WORD *)(uintptr_t)(*(_DWORD *)((int)(intptr_t)&g_RenderState + 60) + 12) - 1,
                *(_WORD *)(uintptr_t)(*(_DWORD *)((int)(intptr_t)&g_RenderState + 60) + 16) - 1,
                *(unsigned __int16 *)&g_RenderState,
                *(unsigned __int16 *)((int)(intptr_t)&g_RenderState + 4));
              Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, saved_handle);
            }
            result = (_DWORD *)(uintptr_t)Render_FillRect(
                                 (_DWORD *)(uintptr_t)render_device,
                                 copy_target,
                                 0,
                                 0,
                                 *(_WORD *)(uintptr_t)render_device - 1,
                                 *(_WORD *)(uintptr_t)(render_device + 2) - 1,
                                 0,
                                 0);
            if ( cursor_visible )
              result = (_DWORD *)(uintptr_t)Render_Present((int)(intptr_t)&g_RenderState);
            *(_DWORD *)(uintptr_t)(render_device + 200) = 0;
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

  old_flag = *(_DWORD *)(uintptr_t)(surface + 204);
  *(_DWORD *)(uintptr_t)(surface + 204) = new_flag;
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
    (*(void (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(companion_surface + 164) + 124))(
      *(_DWORD *)(uintptr_t)(companion_surface + 164),
      *(_DWORD *)(uintptr_t)(result[49] + 16));
    return (int *)(uintptr_t)Palette_ApplyWithBrightnessOffset(render_device, render_device + 55);
  }
  return result;
}

//----- (00404AA0) --------------------------------------------------------
int  Surface_BeginPixelRead(int surface, int x, int y, DWORD context)
{
  int result; // eax
  int v6; // ecx
  __int64 v7; // rax
  unsigned int lock_status; // eax
  int v9; // ecx
  int row_stride; // eax
  int pixel_cursor; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v6 + 184) + 60))();
    *(_DWORD *)(uintptr_t)HIDWORD(v7) = (_DWORD)(uintptr_t)(g_RenderSurface_LinkedBlitCursorVtable);
    *(_DWORD *)(uintptr_t)(HIDWORD(v7) + 4) = v7;
    lock_status = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( lock_status )
      Render_HandleDirectDrawFatalError(lock_status, v9);
    row_stride = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v9 + 4))();
    *(_DWORD *)(uintptr_t)(pixel_cursor + 8) = y * row_stride + x + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(pixel_cursor + 4) + 92);
    return pixel_cursor;
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
  unsigned int lock_status; // eax
  int v9; // ecx
  int row_stride; // eax
  int pixel_cursor; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v6 + 184) + 64))();
    *(_DWORD *)(uintptr_t)HIDWORD(v7) = (_DWORD)(uintptr_t)(g_RenderSurface_LinkedBlitCursorVtable);
    *(_DWORD *)(uintptr_t)(HIDWORD(v7) + 4) = v7;
    lock_status = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( lock_status )
      Render_HandleDirectDrawFatalError(lock_status, v9);
    row_stride = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v9 + 4))();
    *(_DWORD *)(uintptr_t)(pixel_cursor + 8) = y * row_stride + x + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(pixel_cursor + 4) + 92);
    return pixel_cursor;
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
  *(_DWORD *)(uintptr_t)(surface + 200) = 1;
  return result;
}

//----- (00404BA0) --------------------------------------------------------
int  Render_SaveBackbuffer(int render_device)
{
  _DWORD surface_wrapper;
  _DWORD surface_device;
  uintptr_t *surface_vtable;

  if ( render_device == (int)(intptr_t)&g_MainRenderDevice )
  {
    Compat_PresentPrimaryIndexedSurfaceToPlatform();
    return 0;
  }
  surface_wrapper = *(_DWORD *)(uintptr_t)(render_device + 196);
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
  *(_DWORD *)(uintptr_t)(result + 216) = brightness_offset;
  return result;
}

//----- (00404C80) --------------------------------------------------------
int  Palette_ApplyWithBrightnessOffset(int *render_device, const void *new_palette)
{
  unsigned char *palette_bytes;
  unsigned int converted_palette[PALETTE_COLOR_COUNT];
  int base_color;
  int channel_value;
  unsigned int palette_index;

  palette_bytes = (unsigned char *)(render_device + 55);
  qmemcpy(palette_bytes, new_palette, PALETTE_TABLE_COPY_BYTES);
  base_color = render_device[54];
  for ( palette_index = 0; palette_index < PALETTE_COLOR_COUNT; ++palette_index )
  {
    unsigned int converted_entry;

    channel_value = base_color + palette_bytes[4 * palette_index];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > PALETTE_CHANNEL_MAX )
      channel_value = PALETTE_CHANNEL_MAX;
    converted_entry = (unsigned char)channel_value;

    channel_value = base_color + palette_bytes[4 * palette_index + 1];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > PALETTE_CHANNEL_MAX )
      channel_value = PALETTE_CHANNEL_MAX;
    converted_entry |= (unsigned int)(unsigned char)channel_value << 8;

    channel_value = base_color + palette_bytes[4 * palette_index + 2];
    if ( channel_value < 0 )
      channel_value = 0;
    if ( channel_value > PALETTE_CHANNEL_MAX )
      channel_value = PALETTE_CHANNEL_MAX;
    converted_entry |= (unsigned int)(unsigned char)channel_value << 16;

    converted_palette[palette_index] = converted_entry;
  }
  if ( render_device == (int *)&g_MainRenderDevice || !render_device[49] || (render_device[49] & 3) != 0 )
    return 0;
  return IO_StreamWrite(render_device[49], 0, (int)(intptr_t)converted_palette, PALETTE_COLOR_COUNT);
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
  for ( i = 0; i <= step_count; result = (int *)(uintptr_t)Palette_CrossfadeStep(render_device, target_palette, step, step_count) )
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
    qmemcpy(&g_PaletteCrossfadeSourceBuffer, render_device + 55, PALETTE_TABLE_COPY_BYTES);
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
  while ( target_ptr != target_palette + PALETTE_TABLE_BYTES );
  Palette_ApplyWithBrightnessOffset(render_device, render_device + 55);
  return Render_SaveBackbuffer((int)(intptr_t)render_device);
}

//----- (00404F20) --------------------------------------------------------
int  Palette_FadeOutToBlack(int *render_device, signed int step_count)
{
  _DWORD *device_palette; // esi
  int result; // eax
  int step; // ebx
  unsigned __int8 *source_ptr; // ecx
  _DWORD *write_ptr; // esi
  int green_scaled; // edx
  __int64 v9; // rtt
  int red_scaled; // edx
  unsigned int source_palette[PALETTE_COLOR_COUNT]; // [esp+0h] [ebp-428h] BYREF
  int *device; // [esp+400h] [ebp-28h] BYREF
  int packed_entry; // [esp+404h] [ebp-24h]
  _DWORD *write_base; // [esp+408h] [ebp-20h]
  unsigned __int8 blue_value; // [esp+40Ch] [ebp-1Ch]
  char green_value; // [esp+410h] [ebp-18h]

  device = render_device;
  device_palette = (_DWORD*)(render_device + 55);
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
        green_scaled = step * source_ptr[1];
        blue_value = step * source_ptr[2] / step_count;
        v9 = green_scaled;
        red_scaled = step * *source_ptr;
        green_value = v9 / step_count;
        LOBYTE(packed_entry) = red_scaled / step_count;
        BYTE1(packed_entry) = green_value;
        HIWORD(packed_entry) = blue_value;
        ++write_ptr;
        source_ptr += 4;
        *(write_ptr - 1) = packed_entry;
      }
      while ( source_ptr != (unsigned __int8 *)source_palette + sizeof(source_palette) );
      Palette_ApplyWithBrightnessOffset(device, write_base);
      --step;
      result = Render_SaveBackbuffer((int)(intptr_t)device);
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
    device_palette = (_DWORD*)(result + 55);
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
      while ( target_ptr != target_palette + PALETTE_TABLE_BYTES );
      Palette_ApplyWithBrightnessOffset(device, device_palette);
      ++step;
      result = (int *)(uintptr_t)Render_SaveBackbuffer((int)(intptr_t)device);
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
  int v6 CLASH95_UNUSED; // ecx
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
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, a2, a3, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  temp_surface = Surface;
  g_RenderDevice = (_UNKNOWN*)(Surface);
  Render_FillRect((_DWORD*)(render_device), Surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  LoadPalPCX((int)(intptr_t)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
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
    while ( candidate_index < PALETTE_COLOR_COUNT );
    g_PaletteShadowRemapTableMinus1[++remap_index] = best_index;
    palette_cursor += 4;
  }
  while ( remap_index < 32 );
  for ( i = 0; i < SCREEN_PIXEL_COUNT; ++i )
  {
    pixel_ptr = (_BYTE *)(uintptr_t)(i + temp_surface[1]);
    if ( (unsigned __int8)*pixel_ptr <= 0x1Fu )
      *pixel_ptr = g_Video_LowColorRemapTable[(unsigned __int8)*pixel_ptr];
  }
  /*
   * Original sub_4050F0, right after the <=0x1F remap sweep (clash95.asm
   * 7317-7325, loc_40520E tail):
   *   mov eax, ds:g_RenderDevice / mov edx,[eax+0B8h] / call dword ptr [edx+24h]
   * i.e. render-device slot +36 (RenderSurface_InvokeSlot36) is invoked on the
   * live device before the grey ramp is built.  The raw decompile dropped it.
   */
  RenderSurface_InvokeSlot36((_DWORD *)g_RenderDevice);
  ramp_cursor = (unsigned int)(intptr_t)g_PaletteScratchSurfaceBuffer;
  ramp_end = (unsigned int)(intptr_t)&g_PaletteScratchSurfaceBuffer[128];
  gray_accum = 0;
  do
  {
    gray_level = gray_accum / 31;
    ramp_cursor += 4;
    *(_BYTE *)(uintptr_t)(ramp_cursor - 4) = gray_accum / 31;
    *(_BYTE *)(uintptr_t)(ramp_cursor - 3) = gray_accum / 31;
    gray_accum += 255;
    *(_BYTE *)(uintptr_t)(ramp_cursor - 2) = gray_level;
  }
  while ( ramp_cursor != ramp_end );
  pixel_index = ramp_end ^ ramp_cursor;
  pixel_cursor = (_BYTE *)(uintptr_t)temp_surface[1];
  do
  {
    if ( (unsigned __int8)*pixel_cursor > 0x1Fu )
      *pixel_cursor = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*pixel_cursor] >> 3;
    ++pixel_index;
    ++pixel_cursor;
  }
  while ( pixel_index < SCREEN_PIXEL_COUNT );
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  /*
   * Original sub_4050F0 tail (clash95.asm 7367-7370):
   *   mov eax, ds:g_RenderDevice / mov edx,[eax+0B8h] / call dword ptr [edx+24h]
   * The raw decompile turned the slot +36 invocation into a bare read of
   * g_RenderDevice.
   */
  RenderSurface_InvokeSlot36((_DWORD *)g_RenderDevice);
  if ( temp_surface )
    ((void)(temp_surface), j__nfree_());
  result = saved_render_device;
  g_RenderDevice = (_UNKNOWN*)(saved_render_device);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;

//----- (00405330) --------------------------------------------------------
void * Video_ExitGreyscaleTransition(int *render_device, unsigned __int8 *target_palette, int a3, char a4, DWORD a5)
{
  _DWORD *Surface; // eax
  void *current_render_device CLASH95_UNUSED; // ebp
  _DWORD *snapshot_surface; // esi
  int i; // edx
  _BYTE *pixel_ptr; // ebx
  _BYTE *pixel_cursor; // ecx
  int j; // ebx
  int k; // edx
  _BYTE *pixel_byte_ptr; // ebx
  unsigned int pixel_value; // ecx
  int v16 CLASH95_UNUSED; // ecx
  void *result; // eax
  void *saved_render_device; // [esp+4h] [ebp-18h]

  saved_render_device = g_RenderDevice;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, a3, a4, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  current_render_device = g_RenderDevice;
  snapshot_surface = Surface;
  Render_FillRect((_DWORD*)(g_RenderDevice), Surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  for ( i = 0; i < SCREEN_PIXEL_COUNT; ++i )
  {
    pixel_ptr = (_BYTE *)(uintptr_t)(i + snapshot_surface[1]);
    if ( (unsigned __int8)*pixel_ptr <= 0x1Fu )
      *pixel_ptr = g_Video_LowColorRemapTable[(unsigned __int8)*pixel_ptr];
  }
  pixel_cursor = (_BYTE *)(uintptr_t)snapshot_surface[1];
  for ( j = 0; j < SCREEN_PIXEL_COUNT; ++j )
  {
    if ( (unsigned __int8)*pixel_cursor > 0x1Fu )
      *pixel_cursor = (int)(unsigned __int8)g_PaletteScratchSurfaceBuffer[4 * (unsigned __int8)*pixel_cursor] >> 3;
    ++pixel_cursor;
  }
  /* asm 7515-7517: mov edx,[esi+0B8h] / mov eax,esi / call dword ptr [edx+24h] */
  RenderSurface_InvokeSlot36(snapshot_surface);
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  Render_FillRect((_DWORD*)(g_RenderDevice), snapshot_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  for ( k = 0; k < SCREEN_PIXEL_COUNT; ++k )
  {
    pixel_byte_ptr = (_BYTE *)(uintptr_t)(k + snapshot_surface[1]);
    pixel_value = (unsigned __int8)*pixel_byte_ptr;
    if ( pixel_value <= 0x1F )
      *pixel_byte_ptr = g_Video_LowColorRemapTable[pixel_value];
  }
  /* asm 7549-7551: mov edx,[esi+0B8h] / mov eax,esi / call dword ptr [edx+24h] */
  RenderSurface_InvokeSlot36(snapshot_surface);
  LoadPalPCX((int)(intptr_t)g_PaletteScratchSurfaceBuffer, aPal_grey_pcx, 0);
  Palette_ApplyWithBrightnessOffset(render_device, g_PaletteScratchSurfaceBuffer);
  Render_FillRect((_DWORD*)(g_RenderDevice), snapshot_surface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  /* asm 7568-7571: mov edx,[esi+0B8h] / mov eax,esi / mov ebx,14h /
   * call dword ptr [edx+24h] (ebx=20 is the crossfade step that follows). */
  RenderSurface_InvokeSlot36(snapshot_surface);
  Palette_CrossfadeToTarget(render_device, target_palette, 20);
  if ( snapshot_surface )
    ((void)(snapshot_surface), j__nfree_());
  result = saved_render_device;
  g_RenderDevice = (_UNKNOWN*)(saved_render_device);
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
void __noreturn Surface_GetReadIncrNotImplemented(void)
{
  App_RequestQuit((int)(intptr_t)aGetreadincrZap);
}

//----- (004055D0) --------------------------------------------------------
void __noreturn Surface_GetWriteIncrNotImplemented(void)
{
  App_RequestQuit((int)(intptr_t)aGetwriteincrZa);
}

//----- (004055E0) --------------------------------------------------------
void __noreturn Surface_DrawPixNotImplemented(void)
{
  App_RequestQuit((int)(intptr_t)aDrawpixZapisNa);
}

//----- (004055F0) --------------------------------------------------------
void __noreturn Surface_GetPixNotImplemented(void)
{
  App_RequestQuit((int)(intptr_t)aGetpixZapisNaE);
}

//----- (00405600) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawLineNotImplemented(int a1 CLASH95_UNUSED, int a2 CLASH95_UNUSED)
{
  App_RequestQuit((int)(intptr_t)aDrawlineZapisN);
}

//----- (00405610) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawRectNotImplemented(int a1 CLASH95_UNUSED, int a2 CLASH95_UNUSED)
{
  App_RequestQuit((int)(intptr_t)aDrawrectZapisN);
}

//----- (00405620) --------------------------------------------------------
void __stdcall __noreturn Surface_DrawBoxNotImplemented(int a1 CLASH95_UNUSED, int a2 CLASH95_UNUSED)
{
  App_RequestQuit((int)(intptr_t)aDrawboxZapisNa);
}

//----- (00405630) --------------------------------------------------------
void __stdcall __noreturn Surface_DotBoxNotImplemented(int a1 CLASH95_UNUSED, int a2 CLASH95_UNUSED)
{
  App_RequestQuit((int)(intptr_t)aDotboxZapisNaE);
}

//----- (00405640) --------------------------------------------------------
int Surface_GetReadIncrZero(void)
{
  return 0;
}

//----- (00405650) --------------------------------------------------------
int Surface_GetWriteIncrZero(void)
{
  return 0;
}

//----- (00405660) --------------------------------------------------------
int  Surface_GetReadIncrFromStride(int surface)
{
  return *(_DWORD *)(uintptr_t)(surface + 188);
}

//----- (00405670) --------------------------------------------------------
int  Surface_GetWriteIncrFromStride(int surface)
{
  return *(_DWORD *)(uintptr_t)(surface + 188);
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

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__((_DWORD)(uintptr_t)(surface), (_DWORD)(uintptr_t)(&g_Surface_DtorArrayTag));
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = Render_DestructScratchSurface(surface, 1);
    if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, (_DWORD)(uintptr_t)(&g_SurfaceCursor_DtorArrayTag));
    j_j__nfree_();
    return v3;
  }
  else if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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
signed int SurfaceCursor_GetIncrUnbounded(void)
{
  return 0x7FFFFFFF;
}

//----- (00405730) --------------------------------------------------------
signed int SurfaceCursor_GetExtentUnbounded(void)
{
  return 0x7FFFFFFF;
}

//----- (00405750) --------------------------------------------------------
int SurfaceCursor_GetOffsetZero(void)
{
  return 0;
}

//----- (00405760) --------------------------------------------------------
int  RenderSurface_Destroy(int surface, char flags)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, (_DWORD)(uintptr_t)(&g_RenderSurface_DtorArrayTag));
    j_j__nfree_();
    return v5;
  }
  else
  {
    v3 = Surface_Destruct(surface + 8);
    if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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
  return *(_DWORD *)(uintptr_t)(cursor + 8);
}

//----- (004057C0) --------------------------------------------------------
signed int RenderSurface_GetBlitCursorCapacity(void)
{
  return 0x7FFFFFFF;
}

//----- (004057D0) --------------------------------------------------------
int  RenderSurface_AdvanceBlitCursor(int result, int delta)
{
  *(_DWORD *)(uintptr_t)(result + 4) += delta;
  return result;
}

//----- (004057E0) --------------------------------------------------------
int  RenderSurface_GetBlitCursorPosition(int cursor)
{
  return *(_DWORD *)(uintptr_t)(cursor + 4);
}

//----- (004057F0) --------------------------------------------------------
int  RenderSurface_DestroyLinkedBlitCursor(_DWORD *cursor, char flags)
{
  int v2; // ecx
  char v3; // dl
  int v5; // ecx

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__((_DWORD)(uintptr_t)(cursor), (_DWORD)(uintptr_t)(&g_LinkedBlitCursor_DtorArrayTag));
    j_j__nfree_();
    return v5;
  }
  else
  {
    *cursor = (_DWORD)(uintptr_t)(g_RenderSurface_LinkedBlitCursorVtable);
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
signed int RenderSurface_GetLinkedBlitCursorCapacity(void)
{
  return 0x7FFFFFFF;
}

//----- (00405840) --------------------------------------------------------
int  RenderSurface_AdvanceLinkedBlitCursor(int result, int delta)
{
  *(_DWORD *)(uintptr_t)(result + 8) += delta;
  return result;
}

//----- (00405850) --------------------------------------------------------
int  RenderSurface_GetLinkedBlitCursorPosition(int cursor)
{
  return *(_DWORD *)(uintptr_t)(cursor + 8);
}

//----- (00405860) --------------------------------------------------------
int  RenderSurface_GetLinkedSurfaceBuffer(int cursor)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(cursor + 4) + 72);
}

//----- (00405870) --------------------------------------------------------
int  RenderSurface_DestroyBlitCursor(int result, char flags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, (_DWORD)(uintptr_t)(&g_BlitCursor_DtorArrayTag));
    j_j__nfree_();
    return v3;
  }
  else if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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
  *result = (_DWORD)(uintptr_t)(g_NullBlitCursor_Vtable);
  return result;
}
// 50EF24: using guessed type int (*off_50EF24[5])();

//----- (004058C0) --------------------------------------------------------
int __thiscall RenderSurface_CloneInternalArray(void *this_)
{
  return _wcpp_4_copy_array__((int)(uintptr_t)(this_));
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
  return Render_ConstructSurfaceObject(surface_addr, SCREEN_WIDTH, SCREEN_HEIGHT);
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
int  Res_ProbeGfxFileExists(CHAR *file_name, int a2 CLASH95_UNUSED, DWORD context, int a4 CLASH95_UNUSED)
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
  char cur_char; // al
  char next_char; // al
  int result; // eax
  int v7; // ecx
  char path[256]; // [esp-100h] [ebp-114h] BYREF
  int query_handle[5]; // [esp+0h] [ebp-14h] BYREF

  query_handle[4] = a2;
  qmemcpy(path, aGfx_4, 0xFFu);
  path_cursor = &path[strlen(path)];
  do
  {
    cur_char = *archive_name;
    *path_cursor = *archive_name;
    if ( !cur_char )
      break;
    next_char = archive_name[1];
    archive_name += 2;
    path_cursor[1] = next_char;
    path_cursor += 2;
  }
  while ( next_char );
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
  sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] = 0;
  sprite_set[DLX_SPRITE_SET_VTABLE_DWORD_INDEX] = (_DWORD)(uintptr_t)&g_DLXSpriteSet_Vtable;
  Debug_Log(63, 0, (DWORD)(intptr_t)resource_name, (int)(intptr_t)aDlxspritesetDl);
  strcpy(path, aGfx);
  strcat(path, resource_name);
  query_handle = FileSystem_ResolveReadPath(path, 0);
  sprite_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX] = IO_QueryVTableStreamSize(query_handle);
  if ( !query_handle || sprite_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX] <= DLX_DIRECTORY_BYTES )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(
        stderr,
        "[dlx] load failed path=%s size=%d caller=%p\n",
        path,
        sprite_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX],
        __builtin_return_address(0));
    App_RequestQuit((int)(intptr_t)aIOCouldnTOpenF);
    return sprite_set;
  }
  Compat_QueryRead(query_handle, g_DlxSpriteSetOffsetTable, DLX_DIRECTORY_BYTES);
  data_size = sprite_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX] - DLX_DIRECTORY_BYTES;
  sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] = (unsigned int)nmalloc_(data_size, 4);
  if ( !sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] )
  {
    Debug_Log(0, 0, data_size, (int)(intptr_t)aNotEnoughMem_1);
    App_RequestQuit((int)(intptr_t)aNotEnoughMem_2);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX], data_size);
  entry_index = 0;
  while ( entry_index < 1023 && g_DlxSpriteSetOffsetTable[entry_index] )
  {
    entry_end_offset = g_DlxDirEntryEndOffsetTable[entry_index];
    if ( entry_end_offset )
      entry_size = entry_end_offset - g_DlxSpriteSetOffsetTable[entry_index];
    else
      entry_size = IO_QueryVTableStreamSize(query_handle) - g_DlxSpriteSetOffsetTable[entry_index];
    sprite_set[entry_index] = Mem_Alloc(22, entry_index, entry_size, (DWORD)(intptr_t)sprite_set);
    if ( sprite_set[entry_index] )
      sprite_set[entry_index] = DLXSprite_ConstructFromBuffer(sprite_set[entry_index], g_DlxSpriteSetOffsetTable[entry_index] + sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] - DLX_DIRECTORY_BYTES, entry_size);
    ++entry_index;
  }
  sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX] = entry_index;
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

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(a3, (_DWORD)(uintptr_t)(&g_DLXSpriteSet_DtorArrayTag));
    j_j__nfree_();
    return sprite_set;
  }
  sprite_set[DLX_SPRITE_SET_VTABLE_DWORD_INDEX] = (int)(intptr_t)&g_DLXSpriteSet_Vtable;
  entry_index = 0;
  if ( sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX] > 0 )
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
    while ( entry_index < sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX] );
  }
  if ( sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] )
    j__nfree_();
  if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) == 0 )
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

  sprite_set[DLX_SPRITE_SET_VTABLE_DWORD_INDEX] = (int)(intptr_t)&g_DLXSpriteSet_Vtable;
  DLXSpriteSet_CopyEntriesFrom(sprite_set, source_set, (int)(intptr_t)sprite_set, entry_count);
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
  sprite_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX] = source_set[DLX_SPRITE_SET_FILE_SIZE_DWORD_INDEX];
  sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX] = source_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX];
  entry_index = 0;
  v7 = sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX];
  sprite_set[DLX_SPRITE_SET_DATA_POINTER_DWORD_INDEX] = 0;
  if ( v7 > 0 )
  {
    dest_entry = sprite_set;
    do
    {
      if ( *source_set )
      {
        new_sprite = Mem_Alloc(22, entry_index, (char)(intptr_t)source_set, entry_count);
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
      entry_count = sprite_set[DLX_SPRITE_SET_ENTRY_COUNT_DWORD_INDEX];
      ++dest_entry;
    }
    while ( entry_index < entry_count );
  }
  return sprite_set;
}
// 405D73: variable 'v6' is possibly undefined
