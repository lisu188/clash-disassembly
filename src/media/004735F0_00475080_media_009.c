/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL _DWORD *Compat_FileSystemQueryOpen (int file_system, int mode_flags);
CLASH95_LOCAL int Compat_FileSystemQueryResultIsReady (_DWORD *opened_query);
CLASH95_TEST_VISIBLE void Compat_FileSystemQueryResultRelease (_DWORD *opened_query);

//----- (004735F0) --------------------------------------------------------
int  Surface_BltToWindowClient(int surface, int dest_surface)
{
  int result; // eax
  struct tagRECT client_rect[2]; // [esp+0h] [ebp-24h] BYREF

  GetClientRect(*(HWND *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 168) + 36), client_rect);
  ClientToScreen(*(HWND *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 168) + 36), (LPPOINT)client_rect);
  ClientToScreen(*(HWND *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 168) + 36), (LPPOINT)&client_rect[0].right);
  result = (*(int (__stdcall **)(_DWORD, struct tagRECT *, _DWORD, _DWORD, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(dest_surface + 164) + 20))(
             *(_DWORD *)(uintptr_t)(dest_surface + 164),
             client_rect,
             *(_DWORD *)(uintptr_t)(surface + 164),
             0,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(surface);
    return -2005532222;
  }
  return result;
}

//----- (00473690) --------------------------------------------------------
int  Surface_BltScaledKeyedOnto(_DWORD *src_surface, int dest_top, int a3, float scale, int dest_surface)
{
  int height; // ecx
  double scaled_bottom; // st6
  int *v8; // eax
  int width; // ebx
  int v10; // edx
  double scaled_right; // st7
  int v12; // eax
  int result; // eax
  int v14; // edx
  int v15; // [esp+4h] [ebp-Ch]

  height = src_surface[1];
  src_surface[10] = dest_top;
  scaled_bottom = (double)(height + dest_top) * scale;
  _CHP(height + dest_top, a3);
  v8[12] = (int)scaled_bottom;
  width = *v8;
  v8[9] = v10;
  scaled_right = scale * (double)(width + v10);
  _CHP(width + v10, v15);
  *(_DWORD *)(uintptr_t)(v12 + 44) = (int)scaled_right;
  result = (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(dest_surface + 164) + 20))(
             *(_DWORD *)(uintptr_t)(dest_surface + 164),
             src_surface + 9,
             src_surface[41],
             src_surface + 5,
             16809984,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)(intptr_t)src_surface);
    return v14;
  }
  return result;
}
// 4736B1: variable 'v8' is possibly undefined
// 4736B6: variable 'v10' is possibly undefined
// 4736C3: variable 'v15' is possibly undefined
// 4736C8: variable 'v12' is possibly undefined
// 47370C: variable 'v14' is possibly undefined

//----- (00473730) --------------------------------------------------------
int  Surface_BltMirrorLeftRight(int surface)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-64h] BYREF

  blt_fx[0] = 100;
  blt_fx[1] = 2;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 20))(
           *(_DWORD *)(uintptr_t)(surface + 164),
           0,
           0,
           0,
           16779264,
           blt_fx);
}

//----- (00473770) --------------------------------------------------------
int  Surface_BltMirrorUpDown(int surface)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-64h] BYREF

  blt_fx[0] = 100;
  blt_fx[1] = 4;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 20))(
           *(_DWORD *)(uintptr_t)(surface + 164),
           0,
           0,
           0,
           16779264,
           blt_fx);
}

//----- (004737B0) --------------------------------------------------------
_DWORD * Surface_SetDestRect(_DWORD *result, int top, int bottom, int left, int right)
{
  result[10] = top;
  result[9] = left;
  result[12] = bottom;
  result[11] = right;
  return result;
}

//----- (004737D0) --------------------------------------------------------
_DWORD * Surface_SetSrcRect(_DWORD *result, int top, int bottom, int left, int right)
{
  result[6] = top;
  result[5] = left;
  result[8] = bottom;
  result[7] = right;
  return result;
}

//----- (004737F0) --------------------------------------------------------
int  Surface_SetSrcColorKey(int surface, int color_key, int a3)
{
  _DWORD color_key_struct[3]; // [esp+0h] [ebp-Ch] BYREF

  color_key_struct[2] = a3;
  *(_DWORD *)(uintptr_t)(surface + 16) = color_key;
  color_key_struct[0] = color_key;
  color_key_struct[1] = color_key;
  return (*(int (__stdcall **)(_DWORD, int, _DWORD *))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 116))(*(_DWORD *)(uintptr_t)(surface + 164), 8, color_key_struct);
}

//----- (00473820) --------------------------------------------------------
int  Surface_Restore(int surface)
{
  return (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 108))(*(_DWORD *)(uintptr_t)(surface + 164));
}

//----- (00473840) --------------------------------------------------------
int  Surface_LockWithRestore(int surface, int a2)
{
  int surface_desc; // edi
  int dd_surface; // eax
  int result; // eax

  surface_desc = surface + 56;
  memset_(a2, 0);
  dd_surface = *(_DWORD *)(uintptr_t)(surface + 164);
  *(_DWORD *)(uintptr_t)(surface + 56) = 108;
  result = (*(int (__stdcall **)(int, _DWORD, int, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)dd_surface + 100))(dd_surface, 0, surface_desc, 1, 0);
  if ( result == -2005532222 )
  {
    (*(void (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 108))(*(_DWORD *)(uintptr_t)(surface + 164));
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 100))(
      *(_DWORD *)(uintptr_t)(surface + 164),
      0,
      surface_desc,
      1,
      0);
    return -2005532222;
  }
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004738B0) --------------------------------------------------------
int  Surface_Unlock(int surface)
{
  return (*(int (__stdcall **)(_DWORD, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 128))(*(_DWORD *)(uintptr_t)(surface + 164), surface + 56);
}

//----- (004739C0) --------------------------------------------------------
int  Surface_SetPixelByte(int result, int x, char color, int y)
{
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 72) * y + x + *(_DWORD *)(uintptr_t)(result + 92)) = color;
  return result;
}

//----- (004739D0) --------------------------------------------------------
int  Surface_GetPixelByte(int surface, int x, int y)
{
  return *(unsigned __int8 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 92) + *(_DWORD *)(uintptr_t)(surface + 72) * y + x);
}

//----- (004739F0) --------------------------------------------------------
int * Mem_SwapDwordPair(int *result, int *other)
{
  int temp; // ebx

  temp = *result;
  *result = *other;
  *other = temp;
  return result;
}

//----- (00473A00) --------------------------------------------------------
int  Surface_DrawRectBorderByte(int surface, int left, int right, int top, int bottom, char color)
{
  int i; // ebp
  int j; // ebp

  for ( i = left; i < right; ++i )
  {
    Surface_SetPixelByte(surface, i, color, top);
    Surface_SetPixelByte(surface, i, color, bottom);
  }
  for ( j = top; j < bottom; ++j )
  {
    Surface_SetPixelByte(surface, left, color, j);
    Surface_SetPixelByte(surface, right, color, j);
  }
  Surface_SetPixelByte(surface, left, color, top);
  return Surface_SetPixelByte(surface, right, color, bottom);
}

//----- (00473AB0) --------------------------------------------------------
int  Surface_FillRectColor(int surface, int left, int right, int top, int bottom, int fill_color)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-7Ch] BYREF
  _DWORD dest_rect[6]; // [esp+64h] [ebp-18h] BYREF

  dest_rect[0] = left;
  dest_rect[3] = bottom;
  blt_fx[0] = 100;
  blt_fx[20] = fill_color;
  dest_rect[1] = top;
  dest_rect[2] = right;
  return (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD, int, _DWORD *))(uintptr_t)(**(_DWORD **)(uintptr_t)(surface + 164) + 20))(
           *(_DWORD *)(uintptr_t)(surface + 164),
           dest_rect,
           0,
           0,
           16778240,
           blt_fx);
}

//----- (00473B10) --------------------------------------------------------
int  Render_DrawLine(int surface, int x0, int x1, int y0, int y1, char color)
{
  char color_byte; // bp
  signed int delta_x; // esi
  signed int delta_y; // eax
  int result; // eax
  int cur_x; // esi
  int cur_y; // esi
  int v13; // [esp+0h] [ebp-3Ch]
  double x_step; // [esp+0h] [ebp-3Ch]
  int v15; // [esp+4h] [ebp-38h]
  double y_step; // [esp+8h] [ebp-34h]
  double j; // [esp+10h] [ebp-2Ch]
  double i; // [esp+18h] [ebp-24h]
  int x_start; // [esp+20h] [ebp-1Ch] BYREF
  int y_start; // [esp+24h] [ebp-18h] BYREF
  int x_end; // [esp+28h] [ebp-14h] BYREF
  int last_plot CLASH95_UNUSED; // [esp+2Ch] [ebp-10h]

  color_byte = color;
  x_start = x0;
  y_start = y0;
  x_end = x1;
  delta_x = abs32(x1 - x0);
  delta_y = abs32(y1 - y0);
  if ( !delta_x )
    return Render_DrawVerticalRun(surface, y_start, x_start, y1, color);
  if ( !delta_y )
    return Render_DrawHorizontalRun(surface, x_start, y_start, x_end, color);
  if ( delta_x <= delta_y )
  {
    if ( y_start > y1 )
    {
      Mem_SwapDwordPair(&x_start, &x_end);
      Mem_SwapDwordPair(&y_start, &y1);
    }
    result = y1 - y_start;
    x_step = (double)(x_end - x_start) / (double)(y1 - y_start);
    last_plot = x_start;
    cur_y = y_start;
    for ( i = (double)x_start; cur_y <= y1; i = i + x_step )
    {
      _CHP(LODWORD(x_step), HIDWORD(x_step));
      last_plot = (int)i;
      result = Surface_SetPixelByte(surface, (int)i, color_byte, cur_y++);
    }
  }
  else
  {
    if ( x_start > x_end )
    {
      Mem_SwapDwordPair(&x_start, &x_end);
      Mem_SwapDwordPair(&y_start, &y1);
    }
    result = x_end - x_start;
    y_step = (double)(y1 - y_start) / (double)(x_end - x_start);
    last_plot = y_start;
    cur_x = x_start;
    for ( j = (double)y_start; cur_x <= x_end; j = j + y_step )
    {
      _CHP(v13, v15);
      last_plot = (int)j;
      Surface_SetPixelByte(surface, cur_x++, color_byte, (int)j);
      result = x_end;
    }
  }
  return result;
}
// 473BC2: variable 'v13' is possibly undefined
// 473BC2: variable 'v15' is possibly undefined
// 473C9E: variable 'v14' is possibly undefined

//----- (00473CE0) --------------------------------------------------------
int  Render_DrawVerticalRun(int surface, int y_start, int x, int y_end, char color)
{
  int pixels_base; // ebp
  int result; // eax
  int row_offset; // edx

  pixels_base = *(_DWORD *)(uintptr_t)(surface + 92);
  for ( result = y_start; result < y_end; *(_BYTE *)(uintptr_t)(row_offset + pixels_base) = color )
  {
    row_offset = x + result * *(_DWORD *)(uintptr_t)(surface + 72);
    ++result;
  }
  return result;
}

//----- (00473D20) --------------------------------------------------------
int  Render_DrawHorizontalRun(int result, int x_start, int y, int x_end, char color)
{
  int surface; // edi
  int i; // esi

  surface = result;
  for ( i = x_start; i < x_end; ++i )
    result = Surface_SetPixelByte(surface, i, color, y);
  return result;
}
// 473D20: could not find valid save-restore pair for ebx

//----- (00473E30) --------------------------------------------------------
int  Render_FillSurfaceSolidColor(int surface, int fill_color, int a3)
{
  _DWORD blt_fx[26]; // [esp+0h] [ebp-68h] BYREF

  blt_fx[25] = a3;
  blt_fx[20] = fill_color;
  blt_fx[0] = 100;
  return Compat_DirectDrawSurface_Blt(
           (LPDIRECTDRAWSURFACE)(uintptr_t)*(int *)(uintptr_t)(surface + 164),
           0,
           0,
           0,
           16778240,
           blt_fx);
}

//----- (00473E60) --------------------------------------------------------
int  Render_ClampBlitRectToBounds(_DWORD *x_ptr, _DWORD *y_ptr, _DWORD *bounds_rect, _DWORD *src_rect)
{
  int bounds_right; // edi
  int right_edge; // esi
  int bounds_top; // esi
  int bounds_bottom; // ebp
  int result; // eax

  bounds_right = bounds_rect[2];
  right_edge = *x_ptr + src_rect[2] - *src_rect;
  if ( right_edge > bounds_right )
    src_rect[2] -= right_edge - bounds_right;
  if ( *x_ptr < *bounds_rect )
  {
    *src_rect += *bounds_rect - *x_ptr;
    *x_ptr = *bounds_rect;
  }
  bounds_top = bounds_rect[1];
  if ( *y_ptr < bounds_top )
  {
    src_rect[1] += bounds_top - *y_ptr;
    *y_ptr = bounds_rect[1];
  }
  bounds_bottom = bounds_rect[3];
  result = *y_ptr + src_rect[3] - src_rect[1];
  if ( result > bounds_bottom )
  {
    result -= bounds_bottom;
    src_rect[3] -= result;
  }
  return result;
}

//----- (00473EE0) --------------------------------------------------------
int __fastcall Compat_FileSystemQueryRelease(int a1, int *handle_ptr)
{
  int object_handle;
  int result;
  uintptr_t *vtable;

  (void)a1;
  if ( !handle_ptr )
    return 0;
  object_handle = *handle_ptr;
  if ( !object_handle )
  {
    *handle_ptr = 0;
    return 0;
  }
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)object_handle;
  result = ((int (*)(int, int))(uintptr_t)vtable[3])(object_handle, 2);
  *handle_ptr = 0;
  return result;
}

//----- (00473F10) --------------------------------------------------------
int  FileSystem_OpenViaOpenSlotAndNotify(int entry)
{
  int result; // eax
  int v3; // ecx

  result = (*(int (__thiscall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)entry + 12))(entry);
  if ( result )
  {
    (*(void (__cdecl **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)v3 + 20))(result);
    return 1;
  }
  return result;
}
// 473F30: variable 'v3' is possibly undefined

//----- (00473F50) --------------------------------------------------------
int Compat_NoOpQueryCallback(void)
{
  return 0;
}

CLASH95_LOCAL _DWORD *Compat_FileSystemQueryOpen(int file_system, int mode_flags)
{
  uintptr_t *vtable;
  char query_mode;

  if ( !file_system )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)file_system;
  if ( !vtable )
    return 0;
  query_mode = (char)(mode_flags | 4);
  if ( vtable[0] == (uintptr_t)Compat_FileFinderCreate
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountScalarDeletingDtor
      || vtable[2] == (uintptr_t)FileSystem_DiskMountVariantScalarDeletingDtor )
      return (_DWORD *)(uintptr_t)FileSystem_DiskMountOpenFileQuery(file_system, query_mode, 0);
  }
  return File_OpenMountRootEntry(file_system, query_mode, 0);
}

CLASH95_LOCAL int Compat_FileSystemQueryResultIsReady(_DWORD *opened_query)
{
  uintptr_t *vtable;

  if ( !opened_query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)(intptr_t)opened_query;
  if ( !vtable )
    return 0;
  if ( vtable[0] == (uintptr_t)Compat_FileStreamSeekFromStart
    && vtable[1] == (uintptr_t)Compat_FileStreamTell
    && vtable[2] == (uintptr_t)Compat_FileStreamSeekFromEnd )
    return Compat_FileStreamIsReady((int)(intptr_t)opened_query);
  if ( vtable[0] == (uintptr_t)Compat_QuerySkipBytes
    && vtable[1] == (uintptr_t)Compat_QueryGetLength
    && vtable[2] == (uintptr_t)Compat_QuerySkipBytesFromBase )
    return FileSystem_ArchiveStreamHasRemainingData((int)(intptr_t)opened_query);
  return 0;
}

CLASH95_TEST_VISIBLE void Compat_FileSystemQueryResultRelease(_DWORD *opened_query)
{
  uintptr_t *vtable;

  if ( !opened_query )
    return;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)(intptr_t)opened_query;
  if ( !vtable )
    return;
  if ( vtable[0] == (uintptr_t)Compat_FileStreamSeekFromStart
    && vtable[1] == (uintptr_t)Compat_FileStreamTell
    && vtable[2] == (uintptr_t)Compat_FileStreamSeekFromEnd )
  {
    Compat_FileStreamRelease(opened_query, 2);
    return;
  }
  if ( vtable[0] == (uintptr_t)Compat_QuerySkipBytes
    && vtable[1] == (uintptr_t)Compat_QueryGetLength
    && vtable[2] == (uintptr_t)Compat_QuerySkipBytesFromBase )
    Compat_QueryDestruct((int)(intptr_t)opened_query, 2);
}

CLASH95_INTERNAL int Compat_FileSystemOnMounted(int mounted_file_system, int *root_file_system)
{
  uintptr_t *vtable;

  if ( !mounted_file_system )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)mounted_file_system;
  if ( !vtable )
    return 0;
  if ( vtable[0] == (uintptr_t)Compat_FileFinderCreate
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountScalarDeletingDtor )
      return FileSystem_DiskMountResolveRegisteredRootPath(mounted_file_system, (int)(intptr_t)root_file_system);
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountVariantScalarDeletingDtor )
      return FileSystem_DiskMountRegisterNestedMount(mounted_file_system, root_file_system, 0, 0);
  }
  if ( vtable[0] == (uintptr_t)File_CacheNodeNewValidated
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)Compat_QueryCloseAndDestruct )
      return (int)(uintptr_t)File_OpenMountRootEntry(mounted_file_system, 0, 0);
  }
  return 0;
}

//----- (00473F70) --------------------------------------------------------
int  Compat_FileSystemOpenIfReady(int file_system, int mode_flags)
{
  _DWORD *opened_query; // ecx

  opened_query = Compat_FileSystemQueryOpen(file_system, mode_flags);
  if ( opened_query && Compat_FileSystemQueryResultIsReady(opened_query) == 1 )
    return (int)(intptr_t)opened_query;
  if ( opened_query )
    Compat_FileSystemQueryResultRelease(opened_query);
  return 0;
}
// 473F9E: variable 'v3' is possibly undefined

//----- (004741F0) --------------------------------------------------------
void  __noreturn Render_HandleDirectDrawFatalError(unsigned int error_code, int a2)
{
  const char *error_name; // eax
  char message_buffer[256]; // [esp+0h] [ebp-104h] BYREF
  int saved_context CLASH95_UNUSED; // [esp+100h] [ebp-4h]

  saved_context = a2;
  if ( error_code >= 0x8876019A )
  {
    if ( error_code <= 0x8876019A )
    {
      error_name = aDderr_surfacea;
      goto LABEL_10;
    }
    if ( error_code >= 0x8876023B )
    {
      if ( error_code <= 0x8876023B )
      {
        error_name = aDderr_hwndalre;
        goto LABEL_10;
      }
      if ( error_code < 0x88760248 )
      {
        if ( error_code >= 0x88760241 )
        {
          if ( error_code <= 0x88760241 )
          {
            error_name = aDderr_overlayn;
          }
          else if ( error_code >= 0x88760244 )
          {
            if ( error_code <= 0x88760244 )
            {
              error_name = aDderr_notaover;
            }
            else if ( error_code < 0x88760246 )
            {
              error_name = aDderr_exclusiv;
            }
            else if ( error_code <= 0x88760246 )
            {
              error_name = aDderr_notflipp;
            }
            else
            {
              error_name = aDderr_cantdupl;
            }
          }
          else if ( error_code <= 0x88760242 )
          {
            error_name = aDderr_nooverla;
          }
          else
          {
            error_name = aDderr_invalidp;
          }
        }
        else if ( error_code >= 0x8876023E )
        {
          if ( error_code <= 0x8876023E )
          {
            error_name = aDderr_bltfastc;
          }
          else if ( error_code <= 0x8876023F )
          {
            error_name = aDderr_noblthw;
          }
          else
          {
            error_name = aDderr_noddrops;
          }
        }
        else if ( error_code <= 0x8876023C )
        {
          error_name = aDderr_nopalett;
        }
        else
        {
          error_name = aDderr_nopale_0;
        }
        goto LABEL_10;
      }
      if ( error_code <= 0x88760248 )
      {
        error_name = aDderr_notlocke;
        goto LABEL_10;
      }
      if ( error_code < 0x8876024E )
      {
        if ( error_code >= 0x8876024B )
        {
          if ( error_code <= 0x8876024B )
          {
            sprintf_(message_buffer, aDderr_wrongmod);
          }
          else if ( error_code <= 0x8876024C )
          {
            sprintf_(message_buffer, aDderr_implicit);
          }
          else
          {
            sprintf_(message_buffer, aDderr_notpalet);
          }
        }
        else
        {
          if ( error_code <= 0x88760249 )
          {
            error_name = aDderr_cantcrea;
            goto LABEL_10;
          }
          sprintf_(message_buffer, aDderr_nodc);
        }
LABEL_11:
        sprintf_(&g_DirectDrawErrorMessageBuffer, "DirectDraw Error %s", message_buffer);
        App_RequestQuit((int)(intptr_t)aDirectdrawEr_0);
      }
      if ( error_code <= 0x8876024E )
      {
        sprintf_(message_buffer, aDderr_unsupp_0);
        goto LABEL_11;
      }
      if ( error_code >= 0x8876026C )
      {
        if ( error_code <= 0x8876026C )
        {
          sprintf_(message_buffer, aDderr_dcalread);
          goto LABEL_11;
        }
        if ( error_code >= 0x88760294 )
        {
          if ( error_code <= 0x88760294 )
          {
            sprintf_(message_buffer, aDderr_cantpa_0);
            goto LABEL_11;
          }
          if ( error_code == -2005531992 )
          {
            sprintf_(message_buffer, aDderr_notpagel);
            goto LABEL_11;
          }
        }
        else if ( error_code == -2005532032 )
        {
          sprintf_(message_buffer, aDderr_cantpage);
          goto LABEL_11;
        }
      }
      else
      {
        if ( error_code <= 0x8876024F )
        {
          sprintf_(message_buffer, aDderr_nomipmap);
          goto LABEL_11;
        }
        if ( error_code == -2005532080 )
        {
          sprintf_(message_buffer, aDderr_invalids);
          goto LABEL_11;
        }
      }
    }
    else if ( error_code >= 0x88760219 )
    {
      if ( error_code <= 0x88760219 )
      {
        error_name = aDderr_vertical;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760234 )
      {
        if ( error_code <= 0x88760234 )
        {
          error_name = aDderr_primarys;
        }
        else if ( error_code >= 0x88760237 )
        {
          if ( error_code <= 0x88760237 )
          {
            error_name = aDderr_clipperi;
          }
          else if ( error_code < 0x88760239 )
          {
            error_name = aDderr_noclippe;
          }
          else if ( error_code <= 0x88760239 )
          {
            error_name = aDderr_nohwnd;
          }
          else
          {
            error_name = aDderr_hwndsubc;
          }
        }
        else if ( error_code <= 0x88760235 )
        {
          error_name = aDderr_noemulat;
        }
        else
        {
          error_name = aDderr_regionto;
        }
        goto LABEL_10;
      }
      if ( error_code >= 0x88760231 )
      {
        if ( error_code <= 0x88760231 )
        {
          error_name = aDderr_invalidd;
        }
        else if ( error_code <= 0x88760232 )
        {
          error_name = aDderr_directdr;
        }
        else
        {
          error_name = aDderr_nodirect;
        }
        goto LABEL_10;
      }
      if ( error_code >= 0x8876021C )
      {
        if ( error_code <= 0x8876021C )
        {
          error_name = aDderr_wasstill;
          goto LABEL_10;
        }
        if ( error_code == -2005532112 )
        {
          error_name = aDderr_xalign;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601CC )
    {
      if ( error_code <= 0x887601CC )
      {
        error_name = aDderr_surfacen;
        goto LABEL_10;
      }
      if ( error_code >= 0x887601EA )
      {
        if ( error_code <= 0x887601EA )
        {
          error_name = aDderr_toobigwi;
          goto LABEL_10;
        }
        if ( error_code >= 0x887601FE )
        {
          if ( error_code <= 0x887601FE )
          {
            error_name = aDderr_unsupp_1;
            goto LABEL_10;
          }
          if ( error_code == -2005532152 )
          {
            error_name = aDderr_unsupp_2;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x887601D6 )
      {
        if ( error_code <= 0x887601D6 )
        {
          error_name = aDderr_toobighe;
          goto LABEL_10;
        }
        if ( error_code == -2005532192 )
        {
          error_name = aDderr_toobigsi;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601B3 )
    {
      if ( error_code <= 0x887601B3 )
      {
        error_name = aDderr_cantlock;
        goto LABEL_10;
      }
      if ( error_code >= 0x887601B8 )
      {
        if ( error_code <= 0x887601B8 )
        {
          error_name = aDderr_surfacei;
          goto LABEL_10;
        }
        if ( error_code == -2005532222 )
        {
          error_name = aDderr_surfacel;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601A4 )
    {
      if ( error_code <= 0x887601A4 )
      {
        error_name = aDderr_surfac_0;
        goto LABEL_10;
      }
      if ( error_code == -2005532242 )
      {
        error_name = aDderr_surfaceb;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x887600D7 )
  {
    if ( error_code <= 0x887600D7 )
    {
      error_name = aDderr_nocolork;
      goto LABEL_10;
    }
    if ( error_code >= 0x8876013C )
    {
      if ( error_code <= 0x8876013C )
      {
        error_name = aDderr_not4bitc;
        goto LABEL_10;
      }
      if ( error_code >= 0x8876015E )
      {
        if ( error_code <= 0x8876015E )
        {
          error_name = aDderr_nozoverl;
          goto LABEL_10;
        }
        if ( error_code >= 0x8876017E )
        {
          if ( error_code <= 0x8876017E )
          {
            error_name = aDderr_overlayc;
            goto LABEL_10;
          }
          if ( error_code >= 0x88760183 )
          {
            if ( error_code <= 0x88760183 )
            {
              error_name = aDderr_paletteb;
              goto LABEL_10;
            }
            if ( error_code == -2005532272 )
            {
              error_name = aDderr_colorkey;
              goto LABEL_10;
            }
          }
          else if ( error_code == -2005532288 )
          {
            error_name = aDderr_overla_0;
            goto LABEL_10;
          }
        }
        else if ( error_code >= 0x88760168 )
        {
          if ( error_code <= 0x88760168 )
          {
            error_name = aDderr_outofcap;
            goto LABEL_10;
          }
          if ( error_code == -2005532292 )
          {
            error_name = aDderr_outofvid;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x8876014A )
      {
        if ( error_code <= 0x8876014A )
        {
          error_name = aDderr_notextur;
          goto LABEL_10;
        }
        if ( error_code >= 0x8876014F )
        {
          if ( error_code <= 0x8876014F )
          {
            error_name = aDderr_novsynch;
            goto LABEL_10;
          }
          if ( error_code == -2005532332 )
          {
            error_name = aDderr_nozbuffe;
            goto LABEL_10;
          }
        }
      }
      else
      {
        if ( error_code <= 0x8876013D )
        {
          error_name = aDderr_not4bi_0;
          goto LABEL_10;
        }
        if ( error_code == -2005532352 )
        {
          error_name = aDderr_not8bitc;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600FA )
    {
      if ( error_code <= 0x887600FA )
      {
        error_name = aDderr_nomirror;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760118 )
      {
        if ( error_code <= 0x88760118 )
        {
          error_name = aDderr_noraster;
          goto LABEL_10;
        }
        if ( error_code >= 0x88760122 )
        {
          if ( error_code <= 0x88760122 )
          {
            error_name = aDderr_norotati;
            goto LABEL_10;
          }
          if ( error_code == -2005532362 )
          {
            error_name = aDderr_nostretc;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x887600FF )
      {
        if ( error_code <= 0x887600FF )
        {
          error_name = aDderr_notfound;
          goto LABEL_10;
        }
        if ( error_code == -2005532412 )
        {
          error_name = aDderr_noover_0;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600E1 )
    {
      if ( error_code <= 0x887600E1 )
      {
        error_name = aDderr_noexclus;
        goto LABEL_10;
      }
      if ( error_code >= 0x887600E6 )
      {
        if ( error_code <= 0x887600E6 )
        {
          error_name = aDderr_nofliphw;
          goto LABEL_10;
        }
        if ( error_code == -2005532432 )
        {
          error_name = aDderr_nogdi;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600DC )
    {
      if ( error_code <= 0x887600DC )
      {
        error_name = aDderr_nocolo_0;
        goto LABEL_10;
      }
      if ( error_code == -2005532450 )
      {
        error_name = aDderr_nodire_0;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x8876005F )
  {
    if ( error_code <= 0x8876005F )
    {
      error_name = aDderr_incompat;
      goto LABEL_10;
    }
    if ( error_code >= 0x88760096 )
    {
      if ( error_code <= 0x88760096 )
      {
        error_name = aDderr_invalidr;
        goto LABEL_10;
      }
      if ( error_code >= 0x887600B4 )
      {
        if ( error_code <= 0x887600B4 )
        {
          error_name = aDderr_noalphah;
          goto LABEL_10;
        }
        if ( error_code >= 0x887600D2 )
        {
          if ( error_code <= 0x887600D2 )
          {
            error_name = aDderr_nocolorc;
            goto LABEL_10;
          }
          if ( error_code == -2005532460 )
          {
            error_name = aDderr_nocooper;
            goto LABEL_10;
          }
        }
        else if ( error_code == -2005532467 )
        {
          error_name = aDderr_noclipli;
          goto LABEL_10;
        }
      }
      else if ( error_code >= 0x887600A0 )
      {
        if ( error_code <= 0x887600A0 )
        {
          error_name = aDderr_lockedsu;
          goto LABEL_10;
        }
        if ( error_code == -2005532502 )
        {
          error_name = aDderr_no3d;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x88760078 )
    {
      if ( error_code <= 0x88760078 )
      {
        error_name = aDderr_invalidm;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760082 )
      {
        if ( error_code <= 0x88760082 )
        {
          error_name = aDderr_invalido;
          goto LABEL_10;
        }
        if ( error_code == -2005532527 )
        {
          error_name = aDderr_invali_1;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x88760064 )
    {
      if ( error_code <= 0x88760064 )
      {
        error_name = aDderr_invalidc;
        goto LABEL_10;
      }
      if ( error_code == -2005532562 )
      {
        error_name = aDderr_invali_0;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x88760005 )
  {
    if ( error_code <= 0x88760005 )
    {
      error_name = aDderr_alreadyi;
      goto LABEL_10;
    }
    if ( error_code >= 0x88760028 )
    {
      if ( error_code <= 0x88760028 )
      {
        error_name = aDderr_currentl;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760037 )
      {
        if ( error_code <= 0x88760037 )
        {
          error_name = aDderr_exceptio;
          goto LABEL_10;
        }
        if ( error_code == -2005532582 )
        {
          error_name = aDderr_heightal;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x8876000A )
    {
      if ( error_code <= 0x8876000A )
      {
        error_name = aDderr_cannotat;
        goto LABEL_10;
      }
      if ( error_code == -2005532652 )
      {
        error_name = aDderr_cannotde;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x800401F0 )
  {
    if ( error_code <= 0x800401F0 )
    {
      error_name = aDderr_notiniti;
      goto LABEL_10;
    }
    if ( error_code >= 0x8007000E )
    {
      if ( error_code <= 0x8007000E )
      {
        error_name = aDderr_outofmem;
        goto LABEL_10;
      }
      if ( error_code == -2147024809 )
      {
        error_name = aDderr_invali_2;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x80004001 )
  {
    if ( error_code <= 0x80004001 )
    {
      error_name = aDderr_unsuppor;
      goto LABEL_10;
    }
    if ( error_code == -2147467259 )
    {
      error_name = aDderr_generic;
LABEL_10:
      sprintf_(message_buffer, error_name);
      goto LABEL_11;
    }
  }
  sprintf_(message_buffer, aUnknownError);
  goto LABEL_11;
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00474D60) --------------------------------------------------------
_DWORD * Render_ZeroDirectDrawObjectFields(_DWORD *result)
{
  *result = 0;
  result[1] = 0;
  result[2] = 0;
  result[4] = 0;
  result[5] = 0;
  result[3] = 0;
  return result;
}

//----- (00474DE0) --------------------------------------------------------
_DWORD * Render_DestroyDirectDrawObject(_DWORD *dd_object)
{
  int back_surface; // eax
  int primary_surface; // eax
  int v4; // ecx
  int clipper; // esi
  int v6; // edi

  if ( *dd_object )
    Compat_InvokeNativeComMethod0(*dd_object, 76);
  back_surface = dd_object[2];
  if ( back_surface )
  {
    Surface_Destruct(back_surface);
    j__nfree_();
  }
  primary_surface = dd_object[1];
  if ( primary_surface )
  {
    Surface_Destruct(primary_surface);
    j__nfree_();
  }
  v4 = dd_object[3];
  if ( v4 )
  {
    Compat_InvokeNativeComMethod0(v4, 8);
    dd_object[3] = 0;
  }
  clipper = dd_object[5];
  if ( clipper )
  {
    Compat_InvokeNativeComMethod0(clipper, 8);
    dd_object[5] = 0;
  }
  v6 = dd_object[4];
  if ( v6 )
  {
    Compat_InvokeNativeComMethod0(v6, 8);
    dd_object[4] = 0;
  }
  if ( *dd_object )
  {
    Compat_InvokeNativeComMethod0(*dd_object, 8);
    *dd_object = 0;
  }
  return dd_object;
}

//----- (00474E80) --------------------------------------------------------
signed int  Render_InitDirectDrawWindowedMode(LPVOID *dd_context, void *hwnd, void *height, DWORD width, int create_back_surface)
{
  HDC DC; // ebx
  HRESULT dd_create_hr; // eax
  int v10; // ecx
  unsigned int query_hr; // eax
  int v12; // ecx
  unsigned int coop_hr; // eax
  int v14; // ecx
  _DWORD *primary_surface_obj; // eax
  unsigned int create_primary_hr; // eax
  int v17; // ecx
  _DWORD *back_surface_obj; // eax
  unsigned int create_back_hr; // eax
  int v20; // ecx
  unsigned int create_clipper_hr; // eax
  int v22; // ecx
  unsigned int clipper_hwnd_hr; // eax
  int v24; // ecx
  unsigned int set_clipper_hr; // eax
  int v26; // ecx
  int surface_desc; // [esp+2Ch] [ebp-84h] BYREF
  int surface_flags CLASH95_UNUSED; // [esp+30h] [ebp-80h]
  int desc_height CLASH95_UNUSED; // [esp+34h] [ebp-7Ch]
  DWORD desc_width CLASH95_UNUSED; // [esp+38h] [ebp-78h]
  int surface_caps CLASH95_UNUSED; // [esp+94h] [ebp-1Ch]
  LPDIRECTDRAW lpDD; // [esp+98h] [ebp-18h] BYREF
  int DeviceCaps; // [esp+9Ch] [ebp-14h]
  int saved_height; // [esp+A0h] [ebp-10h]

  saved_height = (int)(intptr_t)height;
  *dd_context = 0;
  dd_context[10] = 0;
  dd_context[4] = 0;
  dd_context[6] = (LPVOID)(uintptr_t)width;
  dd_context[7] = height;
  dd_context[9] = hwnd;
  DC = GetDC(0);
  DeviceCaps = GetDeviceCaps(DC, 14);
  dd_context[8] = (LPVOID)(uintptr_t)(GetDeviceCaps(DC, 12) * DeviceCaps);
  ReleaseDC(0, DC);
  dd_create_hr = DirectDrawCreate(0, &lpDD, 0);
  if ( dd_create_hr )
    Render_HandleDirectDrawFatalError(dd_create_hr, v10);
  query_hr = lpDD->lpVtbl->QueryInterface(lpDD, &stru_51CA08, dd_context);
  if ( query_hr )
    Render_HandleDirectDrawFatalError(query_hr, v12);
  if ( lpDD )
  {
    lpDD->lpVtbl->Release(lpDD);
    lpDD = 0;
  }
  coop_hr = (*(int (__stdcall **)(LPVOID, void *, int))(uintptr_t)(*(_DWORD *)*dd_context + 80))(*dd_context, hwnd, 8);
  if ( coop_hr )
    Render_HandleDirectDrawFatalError(coop_hr, v14);
  surface_desc = 108;
  surface_flags = 1;
  surface_caps = 512;
  primary_surface_obj = (_DWORD *)(uintptr_t)Mem_Alloc(176, v14, 108, width);
  if ( primary_surface_obj )
    primary_surface_obj = Surface_Construct(primary_surface_obj);
  dd_context[1] = primary_surface_obj;
  create_primary_hr = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(uintptr_t)(*(_DWORD *)*dd_context + 24))(*dd_context, &surface_desc, (int)(intptr_t)dd_context[1] + 164, 0);
  if ( create_primary_hr )
    Render_HandleDirectDrawFatalError(create_primary_hr, v17);
  if ( create_back_surface )
  {
    back_surface_obj = (_DWORD *)(uintptr_t)Mem_Alloc(176, v17, (char)(intptr_t)&surface_desc, width);
    if ( back_surface_obj )
      back_surface_obj = Surface_Construct(back_surface_obj);
    dd_context[2] = back_surface_obj;
    surface_flags = 7;
    surface_caps = 64;
    desc_width = width;
    desc_height = saved_height;
    create_back_hr = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(uintptr_t)(*(_DWORD *)*dd_context + 24))(*dd_context, &surface_desc, (int)(intptr_t)dd_context[2] + 164, 0);
    if ( create_back_hr )
      Render_HandleDirectDrawFatalError(create_back_hr, v20);
  }
  create_clipper_hr = (*(int (__stdcall **)(LPVOID, _DWORD, LPVOID *, _DWORD))(uintptr_t)(*(_DWORD *)*dd_context + 16))(*dd_context, 0, dd_context + 5, 0);
  if ( create_clipper_hr )
    Render_HandleDirectDrawFatalError(create_clipper_hr, v22);
  clipper_hwnd_hr = (*(int (__stdcall **)(LPVOID, _DWORD, void *))(uintptr_t)(*(_DWORD *)dd_context[5] + 32))(dd_context[5], 0, hwnd);
  if ( clipper_hwnd_hr )
    Render_HandleDirectDrawFatalError(clipper_hwnd_hr, v24);
  set_clipper_hr = (*(int (__stdcall **)(_DWORD, LPVOID))(uintptr_t)(**((_DWORD **)dd_context[1] + 41) + 112))(*((_DWORD *)dd_context[1] + 41), dd_context[5]);
  if ( set_clipper_hr )
    Render_HandleDirectDrawFatalError(set_clipper_hr, v26);
  return 1;
}
// 474F18: variable 'v12' is possibly undefined
// 474F41: variable 'v14' is possibly undefined
// 474F95: variable 'v17' is possibly undefined
// 474FF7: variable 'v20' is possibly undefined
// 475012: variable 'v22' is possibly undefined
// 475029: variable 'v24' is possibly undefined
// 475055: variable 'v10' is possibly undefined
// 475061: variable 'v26' is possibly undefined
// 51CA08: using guessed type IID stru_51CA08;

//----- (00475080) --------------------------------------------------------
signed int  Render_InitDirectDrawFullscreenMode(
        LPVOID *dd_context,
        _DWORD *hwnd,
        _DWORD *height,
        _DWORD *width,
        _DWORD *bpp,
        int mode_flag,
        DWORD use_flip_chain)
{
  _DWORD *raw;
  HRESULT hr;
  _DWORD *display_dim; // ebx
  _DWORD *primary_surface; // eax
  int ddraw_handle; // ebx
  _DWORD *back_surface; // eax
  int surface_desc_size; // [esp+34h] [ebp-80h] BYREF
  int desc_flags CLASH95_UNUSED; // [esp+38h] [ebp-7Ch]
  BOOL has_backbuffer CLASH95_UNUSED; // [esp+48h] [ebp-6Ch]
  int surface_caps CLASH95_UNUSED; // [esp+9Ch] [ebp-18h]
  int attach_caps; // [esp+A0h] [ebp-14h] BYREF
  LPDIRECTDRAW lpDD; // [esp+A4h] [ebp-10h] BYREF

  raw = (_DWORD *)dd_context;
  raw[0] = 0;
  raw[10] = 1;
  raw[4] = 0;
  raw[6] = (int)(uintptr_t)width;
  raw[7] = (int)(uintptr_t)height;
  raw[2] = 0;
  raw[8] = (int)(uintptr_t)bpp;
  raw[1] = raw[2];
  raw[9] = (int)(uintptr_t)hwnd;
  hr = DirectDrawCreate(0, &lpDD, 0);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  hr = Compat_DirectDraw_QueryInterface(lpDD, &stru_51CA08, raw);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( lpDD )
  {
    Compat_DirectDraw_Release(lpDD);
    lpDD = 0;
  }
  hr = Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], (HWND)(uintptr_t)hwnd, 83);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( mode_flag )
  {
    display_dim = (_DWORD *)(uintptr_t)(unsigned int)raw[6];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           (int)(uintptr_t)display_dim,
           raw[7],
           raw[8],
           0,
           1);
  }
  else
  {
    display_dim = (_DWORD *)(uintptr_t)(unsigned int)raw[7];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           raw[6],
           (int)(uintptr_t)display_dim,
           raw[8],
           0,
           0);
  }
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  primary_surface = (_DWORD *)(uintptr_t)Mem_Alloc(176, 0, (char)(intptr_t)display_dim, use_flip_chain);
  if ( primary_surface )
    primary_surface = Surface_Construct(primary_surface);
  raw[1] = (int)(uintptr_t)primary_surface;
  desc_flags = 1;
  surface_caps = 512;
  surface_desc_size = 108;
  if ( use_flip_chain )
  {
    desc_flags = 33;
    surface_caps = 536;
  }
  has_backbuffer = use_flip_chain != 0;
  ddraw_handle = raw[0];
  hr = Compat_DirectDraw_CreateSurface((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], &surface_desc_size, (_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( use_flip_chain )
  {
    back_surface = (_DWORD *)(uintptr_t)Mem_Alloc(176, 0, ddraw_handle, use_flip_chain);
    if ( back_surface )
      back_surface = Surface_Construct(back_surface);
    raw[2] = (int)(uintptr_t)back_surface;
    attach_caps = 4;
    hr = Compat_DirectDrawSurface_GetAttachedSurface(
           (LPDIRECTDRAWSURFACE)(uintptr_t)*((_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41),
           &attach_caps,
           (_DWORD *)(uintptr_t)(unsigned int)raw[2] + 41);
    if ( hr )
      Render_HandleDirectDrawFatalError(hr, 0);
  }
  return 1;
}
// 51CA08: using guessed type IID stru_51CA08;
