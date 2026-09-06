/* Generated from src/recovered/render/00401A40_render.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "render_internal.h"
#include "render_state.h"
#include "render_shared_state.h"
#include "../units/units_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00402E80) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
int  Render_BlitCompressedSpriteRLE(
        int dest_device,
        int sprite,
        int draw_y,
        int draw_x,
        int a5 CLASH95_UNUSED,
        int a6 CLASH95_UNUSED,
        int a7 CLASH95_UNUSED,
        int a8 CLASH95_UNUSED,
        int a9 CLASH95_UNUSED,
        int a10 CLASH95_UNUSED,
        int a11 CLASH95_UNUSED,
        int a12 CLASH95_UNUSED,
        int a13 CLASH95_UNUSED,
        int a14 CLASH95_UNUSED,
        int a15 CLASH95_UNUSED,
        int a16 CLASH95_UNUSED,
        int a17 CLASH95_UNUSED,
        int a18 CLASH95_UNUSED,
        int a19 CLASH95_UNUSED,
        int a20 CLASH95_UNUSED,
        int a21 CLASH95_UNUSED,
        int a22 CLASH95_UNUSED,
        int a23 CLASH95_UNUSED,
        int a24 CLASH95_UNUSED,
        int a25 CLASH95_UNUSED,
        int fill_color_source,
        int a27 CLASH95_UNUSED,
        int a28 CLASH95_UNUSED,
        int a29 CLASH95_UNUSED,
        int a30 CLASH95_UNUSED,
        __int128 clip_bounds,
        int transparent_flags,
        int blend_mode_flags,
        __int64 rgb_offsets_packed)
{
  int *rgb_offset_table; // esi
  _DWORD *Surface; // eax
  int dest_context; // ecx
  char origin_y; // bl
  int cursor_x; // edx
  int v39; // eax
  int v40; // ecx
  int v41; // eax
  unsigned __int8 **fill_ctx; // eax
  unsigned __int8 **v43; // edx
  unsigned __int8 *fill_clip_left; // ecx
  int v45; // edi
  int v46; // eax
  int **blend_ctx; // eax
  int *blend_clip_left; // ecx
  int v49; // edi
  int **v50; // edx
  int v51; // eax
  int row_write_pos; // eax
  int v53; // ecx
  int **offset_ctx; // eax
  int *offset_clip_left; // ecx
  int v56; // ecx
  int v57; // esi
  unsigned __int8 run_byte; // al
  _DWORD *backref_len_ptr; // ecx
  unsigned __int8 transparent_run_length; // dh
  unsigned int skip_remaining; // edi
  int skip_write_cursor; // esi
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
  unsigned __int8 *copy_read_ptr; // esi
  int v80; // ebx
  int v81; // ecx
  int v82; // edx
  int v83; // ecx
  int v84; // ecx
  int v85; // ebx
  unsigned int v86; // ecx
  unsigned int blend_run_length; // esi
  int *blend_clip_enabled; // edx
  unsigned int blend_chunk_length; // ebx
  __int64 blend_dest_packed; // rax
  int v91; // ebx
  int *blend_clip_left_ptr; // eax
  int v93; // esi
  int v94; // ecx
  unsigned int offset_run_length; // ecx
  int offset_chunk_length; // ebx
  unsigned __int8 *copy_src_ptr; // esi
  int *offset_rgb_table; // edx
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
  unsigned __int8 *fill_clip_left_ptr; // eax
  unsigned __int8 *v115; // edi
  int v116; // ecx
  unsigned int v117; // ecx
  int result; // eax
  unsigned __int8 *copy_dest_ptr; // [esp-4h] [ebp-108h]
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
  sprite_header = (__int16 *)(uintptr_t)sprite;
  var2 = draw_x;
  draw_y_saved = draw_y;
  rle_cursor = *(_BYTE **)(uintptr_t)(sprite + 10);
  sprite_format = *(_WORD *)(uintptr_t)(sprite + 4);
  offscreen_surface = 0;
  BYTE2(fill_color_source) = g_TextSprite_StyleFlag;
  if ( g_MousePresentAtStartup && (_UNKNOWN *)(uintptr_t)device_addr == (_UNKNOWN *)&g_MainRenderDevice )
  {
    if ( *(_DWORD *)((char *)&clip_bounds + 2) != -1 )
      App_RequestQuit((int)(intptr_t)aDlxvscreenDraw);
    Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, g_MousePresentAtStartup, draw_x, (DWORD)(intptr_t)v130);
    if ( Surface )
      Surface = Render_CreateSurface((int)(intptr_t)Surface, *sprite_header, sprite_header[1]);
    offscreen_surface = Surface;
    if ( BYTE2(transparent_flags) )
      Render_FillRect(
        (_DWORD*)(&g_MainRenderDevice),
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
    dest_context = offscreen_surface[46];
    origin_y = 0;
    cursor_x = 0;
  }
  else
  {
    origin_y = draw_y_saved;
    dest_context = *(_DWORD *)(uintptr_t)(device_addr + 184);
    cursor_x = var2;
  }
  write_cursor = (void *)(uintptr_t)(*(int (__fastcall **)(int, int))(uintptr_t)(dest_context + 8))(dest_context, cursor_x);
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
    fill_ctx = (unsigned __int8 **)(uintptr_t)Mem_Alloc(24, *(int *)((char *)&clip_bounds + 2), origin_y, (DWORD)(intptr_t)v130);
    if ( fill_ctx )
    {
      fill_clip_left = *(unsigned __int8 **)((char *)&clip_bounds + 2);
      *fill_ctx = (unsigned __int8 *)&fill_color_source + 2;
      fill_ctx[1] = fill_clip_left;
      fill_ctx[2] = *(unsigned __int8 **)((char *)&clip_bounds + 6);
      v45 = *(_DWORD *)((char *)&clip_bounds + 2);
      fill_ctx[3] = *(unsigned __int8 **)((char *)&clip_bounds + 10);
      v40 = *(_DWORD *)((char *)&clip_bounds + 14);
      v43 = fill_ctx;
      fill_ctx[4] = *(unsigned __int8 **)((char *)&clip_bounds + 14);
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
      v43[5] = (unsigned __int8 *)(uintptr_t)v46;
    }
    fill_clip_ctx = v43;
  }
  if ( BYTE2(blend_mode_flags) == 1 )
  {
    blend_ctx = (int **)(uintptr_t)Mem_Alloc(24, v40, origin_y, (DWORD)(intptr_t)v130);
    if ( blend_ctx )
    {
      blend_clip_left = *(int **)((char *)&clip_bounds + 2);
      *blend_ctx = rgb_offset_table;
      blend_ctx[1] = blend_clip_left;
      blend_ctx[2] = *(int **)((char *)&clip_bounds + 6);
      v49 = *(_DWORD *)((char *)&clip_bounds + 2);
      blend_ctx[3] = *(int **)((char *)&clip_bounds + 10);
      v40 = *(_DWORD *)((char *)&clip_bounds + 14);
      v50 = blend_ctx;
      blend_ctx[4] = *(int **)((char *)&clip_bounds + 14);
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
      v50[5] = (int *)(uintptr_t)v51;
      blend_ctx = v50;
    }
    blend_clip_ctx = blend_ctx;
  }
  if ( BYTE2(blend_mode_flags) != 2 )
    goto LABEL_40;
  offset_ctx = (int **)(uintptr_t)Mem_Alloc(24, v40, origin_y, (DWORD)(intptr_t)v130);
  if ( offset_ctx )
  {
    offset_clip_left = *(int **)((char *)&clip_bounds + 2);
    *offset_ctx = rgb_offset_table;
    offset_ctx[1] = offset_clip_left;
    offset_ctx[2] = *(int **)((char *)&clip_bounds + 6);
    offset_ctx[3] = *(int **)((char *)&clip_bounds + 10);
    v56 = *(_DWORD *)((char *)&clip_bounds + 14);
    v57 = *(_DWORD *)((char *)&clip_bounds + 2);
    offset_ctx[4] = *(int **)((char *)&clip_bounds + 14);
    if ( v57 != -1 || *(_DWORD *)((char *)&clip_bounds + 6) != -1 || *(_DWORD *)((char *)&clip_bounds + 10) != -1 || v56 != -1 )
    {
      offset_ctx[5] = (int *)1;
      offset_clip_ctx = offset_ctx;
      goto LABEL_40;
    }
    offset_ctx[5] = (int *)(uintptr_t)~*(_DWORD *)((char *)&clip_bounds + 10);
  }
  offset_clip_ctx = offset_ctx;
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
      backref_len_ptr = (_DWORD*)(rle_cursor + 1);
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
          v130[3] = (_DWORD)(uintptr_t)(g_RenderSurface_BlitCursorVtable);
          if ( BYTE2(blend_mode_flags) )
          {
            if ( BYTE2(blend_mode_flags) <= 1u )
            {
              v130[1] = (*(int (__thiscall **)(_DWORD))(uintptr_t)(*(_DWORD *)write_cursor + 16))(0);
              LOBYTE(v86) = run_length;
              blend_x_saved = screen_x;
              v130[0] = (_DWORD)(uintptr_t)(g_RenderSurface_BlitCursorVtable);
              *(_UNKNOWN **)((char *)&retaddr + 2) = (_UNKNOWN*)(write_cursor);
              blend_run_length = v86;
              blend_clip_enabled = blend_clip_ctx[5];
              blend_clip_overflow = 0;
              if ( blend_clip_enabled )
              {
                if ( screen_y < (int)(intptr_t)blend_clip_ctx[2]
                  || screen_y > (int)(intptr_t)blend_clip_ctx[4]
                  || screen_x > (int)(intptr_t)blend_clip_ctx[3]
                  || (int)(v86 + screen_x) < (int)(intptr_t)blend_clip_ctx[1] + 1 )
                {
                  (*(void (**)(void))(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                  (*(void (**)(void))(uintptr_t)(v130[0] + 12))();
                  run_pixel_ptr += blend_run_length;
                  goto LABEL_97;
                }
                blend_clip_left_ptr = blend_clip_ctx[1];
                if ( (int)(intptr_t)blend_clip_left_ptr > screen_x )
                {
                  v93 = (int)(intptr_t)blend_clip_left_ptr - screen_x;
                  (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
                  (*(void (**)(void))(uintptr_t)(v130[0] + 12))();
                  run_pixel_ptr += v93;
                  blend_run_length = v94 - v93;
                }
                if ( (int)(intptr_t)blend_clip_ctx[3] + 1 < (int)(blend_run_length + blend_x_saved) )
                {
                  blend_clip_overflow = blend_run_length + blend_x_saved - (_DWORD)(intptr_t)blend_clip_ctx[3] - 1;
                  blend_run_length -= blend_clip_overflow;
                }
              }
              blend_run_remaining = blend_run_length;
              do
              {
                blend_chunk_length = blend_run_remaining;
                if ( (*(int (**)(void))(uintptr_t)(v130[0] + 8))() < blend_run_remaining )
                  blend_chunk_length = (*(int (**)(void))(uintptr_t)(v130[0] + 8))();
                if ( blend_chunk_length > (*(int (**)(void))(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 8))() )
                  blend_chunk_length = (*(int (**)(void))(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 8))();
                if ( blend_chunk_length > 0x7FFFFFFF )
                  blend_chunk_length = 0x7FFFFFFF;
                blend_src_ptr = run_pixel_ptr;
                (*(void (**)(void))(uintptr_t)(v130[0] + 16))();
                blend_dest_packed = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 16))();
                Palette_BlendIndexedPixelRun((char *)blend_dest_packed, (char *)(uintptr_t)HIDWORD(blend_dest_packed), blend_src_ptr, blend_chunk_length);
                (*(void (**)(void))(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(uintptr_t)(v130[0] + 12))();
                run_pixel_ptr += blend_chunk_length;
                blend_run_remaining -= blend_chunk_length;
              }
              while ( blend_run_remaining );
              v91 = blend_clip_overflow;
              if ( blend_clip_overflow )
              {
                (*(void (**)(void))(uintptr_t)(**(_DWORD **)((char *)&retaddr + 2) + 12))();
                (*(void (**)(void))(uintptr_t)(v130[0] + 12))();
                run_pixel_ptr += v91;
              }
              goto LABEL_97;
            }
            if ( BYTE2(blend_mode_flags) != 2 )
              App_RequestQuit((int)(intptr_t)aDlxmemscreenDr);
            offset_x_saved = screen_x;
            offset_clip_overflow = 0;
            offset_run_length = run_length;
            offset_write_cursor = write_cursor;
            if ( offset_clip_ctx[5] )
            {
              if ( screen_y < (int)(intptr_t)offset_clip_ctx[2] || screen_y > (int)(intptr_t)offset_clip_ctx[4] || screen_x > (int)(intptr_t)offset_clip_ctx[3] || run_length + screen_x < (int)(intptr_t)offset_clip_ctx[1] + 1 )
              {
                (*(void (__fastcall **)(_DWORD, _DWORD))(uintptr_t)(*(_DWORD *)write_cursor + 12))(run_length, run_length);
                run_pixel_ptr += v100;
                (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v100, v100);
                goto LABEL_97;
              }
              if ( (int)(intptr_t)offset_clip_ctx[1] > screen_x )
              {
                v101 = run_length - ((_DWORD)(intptr_t)offset_clip_ctx[1] - screen_x);
                (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
                run_pixel_ptr += v102;
                (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v101, v102);
              }
              if ( (int)(intptr_t)offset_clip_ctx[3] + 1 < (int)(offset_run_length + offset_x_saved) )
              {
                offset_clip_overflow = offset_run_length + offset_x_saved - (_DWORD)(intptr_t)offset_clip_ctx[3] - 1;
                offset_run_length -= offset_clip_overflow;
              }
            }
            offset_run_remaining = offset_run_length;
            do
            {
              offset_chunk_length = offset_run_remaining;
              if ( offset_run_remaining > 0x7FFFFFFF )
                offset_chunk_length = 0x7FFFFFFF;
              if ( offset_chunk_length > (unsigned int)(*(int (**)(void))(uintptr_t)(*(_DWORD *)offset_write_cursor + 8))() )
                offset_chunk_length = (*(int (**)(void))(uintptr_t)(*(_DWORD *)offset_write_cursor + 8))();
              if ( offset_chunk_length > (unsigned int)(*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))() )
                offset_chunk_length = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
              (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
              run_start_ptr = run_pixel_ptr;
              copy_src_ptr = run_pixel_ptr;
              dest_write_ptr = (unsigned __int8 *)(uintptr_t)(*(int (__thiscall **)(int))(uintptr_t)(*(_DWORD *)offset_write_cursor + 16))(offset_chunk_length);
              offset_rgb_table = *offset_clip_ctx;
              // 004038CE: mov ecx, ebx / shr ecx, 2 / rep movsd / mov cl, al / and cl, 3 / rep movsb
              // -> the byte count is the per-chunk run length in ebx (offset_chunk_length), the same
              // value handed to Palette_OffsetIndexedPixelsRGB (sub_462B0B) two instructions later.
              qmemcpy(dest_write_ptr, copy_src_ptr, offset_chunk_length);
              if ( offset_chunk_length > 1 || *run_start_ptr != offset_rgb_table[3] )
                Palette_OffsetIndexedPixelsRGB(dest_write_ptr, offset_chunk_length, *offset_rgb_table, offset_rgb_table[1], offset_rgb_table[2]);
              (*(void (**)(void))(uintptr_t)(*(_DWORD *)offset_write_cursor + 12))();
              run_pixel_ptr += offset_chunk_length;
              (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, offset_chunk_length);
              offset_run_remaining -= offset_chunk_length;
            }
            while ( offset_run_remaining );
            if ( offset_clip_overflow )
            {
              (*(void (**)(void))(uintptr_t)(*(_DWORD *)offset_write_cursor + 12))();
              run_pixel_ptr += offset_clip_overflow;
              v81 = g_ActiveBlitCursor;
              v82 = offset_clip_overflow;
LABEL_96:
              (*(void (__fastcall **)(int, int))(uintptr_t)(v81 + 12))(v81, v82);
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
              (*(void (__fastcall **)(_DWORD, _DWORD))(uintptr_t)(*(_DWORD *)copy_write_cursor + 12))(run_length, run_length);
              run_pixel_ptr += v83;
              (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v83, v83);
            }
            else
            {
              if ( copy_clip_left > screen_x )
              {
                (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)write_cursor + 12))(copy_clip_left - screen_x, copy_clip_left - screen_x);
                run_pixel_ptr += v84;
                v85 = run_length - v84;
                (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 12))();
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
                if ( copy_chunk_length > (*(int (**)(void))(uintptr_t)(*(_DWORD *)v172 + 8))() )
                  copy_chunk_length = (*(int (**)(void))(uintptr_t)(*(_DWORD *)v172 + 8))();
                if ( copy_chunk_length > (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))() )
                  copy_chunk_length = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
                (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
                copy_read_ptr = run_pixel_ptr;
                copy_dest_ptr = (unsigned __int8 *)(uintptr_t)(*(int (__thiscall **)(unsigned int))(uintptr_t)(*(_DWORD *)v172 + 16))(copy_chunk_length);
                // 00403578: mov ecx, ebx / shr ecx, 2 / rep movsd / mov cl, al / and cl, 3 / rep movsb
                // -> the byte count is the per-chunk run length in ebx (copy_chunk_length), i.e. the
                // same value just passed to the destination lock (vtable+16) and added to the cursors.
                qmemcpy(copy_dest_ptr, copy_read_ptr, copy_chunk_length);
                (*(void (**)(void))(uintptr_t)(*(_DWORD *)v172 + 12))();
                run_pixel_ptr += copy_chunk_length;
                (*(void (__fastcall **)(int, unsigned int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, copy_chunk_length);
                copy_run_remaining -= copy_chunk_length;
              }
              while ( copy_run_remaining );
              v80 = copy_clip_overflow;
              if ( copy_clip_overflow )
              {
                (*(void (**)(void))(uintptr_t)(*(_DWORD *)copy_write_cursor + 12))();
                v81 = g_ActiveBlitCursor;
                v82 = v80;
                run_pixel_ptr += v80;
                goto LABEL_96;
              }
            }
          }
LABEL_97:
          if ( vars6 )
            rle_cursor = (_BYTE*)(vars6 + 1);
          else
            rle_cursor += run_length;
          goto LABEL_180;
        }
        if ( sprite_format != 1 )
          goto LABEL_180;
        if ( BYTE2(blend_mode_flags) )
          App_RequestQuit((int)(intptr_t)aDlxmemscreen_0);
        fill_x_saved = screen_x;
        fill_clip_overflow = 0;
        fill_run_length = run_byte;
        fill_write_cursor = write_cursor;
        if ( fill_clip_ctx[5] )
        {
          if ( screen_y < (int)(intptr_t)fill_clip_ctx[2] || screen_y > (int)(intptr_t)fill_clip_ctx[4] || screen_x > (int)(intptr_t)fill_clip_ctx[3] || run_byte + screen_x < (int)(intptr_t)(fill_clip_ctx[1] + 1) )
          {
            (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
            (*(void (__fastcall **)(int, _DWORD))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, run_length);
            (*(void (__fastcall **)(int, _DWORD))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, run_length);
            goto LABEL_180;
          }
          fill_clip_left_ptr = fill_clip_ctx[1];
          if ( (int)(intptr_t)fill_clip_left_ptr > screen_x )
          {
            v115 = &fill_clip_left_ptr[-screen_x];
            (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
            (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, unsigned __int8 *))(uintptr_t)(g_ActiveBlitCursor + 12))(v116 - (_DWORD)(intptr_t)v115, v115);
            fill_run_length = v117;
          }
          if ( (int)(intptr_t)(fill_clip_ctx[3] + 1) < (int)(fill_run_length + fill_x_saved) )
          {
            fill_clip_overflow = fill_run_length + fill_x_saved - (_DWORD)(intptr_t)fill_clip_ctx[3] - 1;
            fill_run_length = 1 - (fill_x_saved - (_DWORD)(intptr_t)fill_clip_ctx[3]);
          }
        }
        fill_ctx_ref = fill_clip_ctx;
        do
        {
          if ( fill_run_length > (*(int (__thiscall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(fill_run_length) )
            v104 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
          v105 = (*(int (__fastcall **)(int))(uintptr_t)(*(_DWORD *)fill_write_cursor + 8))(v104);
          if ( v106 > v105 )
            v106 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)fill_write_cursor + 8))();
          v107 = (*(int (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(v106);
          if ( v108 > v107 )
            v108 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
          (*(void (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 16))(v108);
          (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
          (*(void (**)(void))(uintptr_t)(*(_DWORD *)fill_write_cursor + 16))();
          memset_(v109, **fill_ctx_ref);
          (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)fill_write_cursor + 12))(v110, v110);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v111, v111);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v112, v112);
          fill_run_length -= v113;
        }
        while ( fill_run_length );
        if ( fill_clip_overflow )
        {
          (*(void (**)(void))(uintptr_t)(*(_DWORD *)fill_write_cursor + 12))();
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, fill_clip_overflow);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, fill_clip_overflow);
        }
      }
      else
      {
        transparent_run_length = run_byte & 0x7F;
        run_length = run_byte & 0x7F;
        if ( BYTE2(transparent_flags) )
        {
          (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
          goto LABEL_180;
        }
        *(_DWORD *)&_10E = (_DWORD)(uintptr_t)(write_cursor);
        skip_remaining = transparent_run_length;
        skip_clip_overflow = 0;
        if ( skip_clip_enabled )
        {
          if ( screen_y < skip_clip_top || screen_y > skip_clip_bottom || screen_x > skip_clip_right || screen_x + transparent_run_length < skip_clip_left_plus1 )
          {
            (*(void (**)(void))(uintptr_t)(**(_DWORD **)&_10E + 12))();
            (*(void (__fastcall **)(int, unsigned int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_remaining);
            (*(void (__fastcall **)(int, unsigned int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_remaining);
            goto LABEL_180;
          }
          if ( skip_clip_left > screen_x )
          {
            (*(void (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 12))();
            (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 12))();
            (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v73 - (skip_clip_left - screen_x), skip_clip_left - screen_x);
            skip_remaining = v74;
          }
          if ( (int)(screen_x + skip_remaining) > skip_clip_right_plus1 )
          {
            skip_clip_overflow = screen_x + skip_remaining - skip_clip_right - 1;
            skip_remaining = 1 - (screen_x - skip_clip_right);
          }
        }
        skip_write_cursor = *(_DWORD *)&_10E;
        do
        {
          if ( skip_remaining > (*(int (__thiscall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(skip_remaining) )
            v63 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
          v64 = (*(int (__fastcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)skip_write_cursor + 8))(v63);
          if ( v65 > v64 )
            v65 = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)skip_write_cursor + 8))();
          v66 = (*(int (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 8))(v65);
          if ( v67 > v66 )
            v67 = (*(int (**)(void))(uintptr_t)(g_ActiveBlitCursor + 8))();
          (*(void (__fastcall **)(unsigned int))(uintptr_t)(g_ActiveBlitCursor + 16))(v67);
          (*(void (**)(void))(uintptr_t)(g_ActiveBlitCursor + 16))();
          (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)skip_write_cursor + 16))();
          memset_(v68, (unsigned __int8)g_Render_BackgroundColorIndex);
          (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)skip_write_cursor + 12))(v69, v69);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v70, v70);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(v71, v71);
          skip_remaining -= v72;
        }
        while ( skip_remaining );
        if ( skip_clip_overflow )
        {
          (*(void (**)(void))(uintptr_t)(**(_DWORD **)&_10E + 12))();
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_clip_overflow);
          (*(void (__fastcall **)(int, int))(uintptr_t)(g_ActiveBlitCursor + 12))(g_ActiveBlitCursor, skip_clip_overflow);
        }
      }
LABEL_180:
      vars2 += run_length;
      screen_x += run_length;
    }
    row_write_pos = (*(int (**)(void))(uintptr_t)(*(_DWORD *)write_cursor + 4))();
    (*(void (__fastcall **)(int, int))(uintptr_t)(v53 + 12))(v53, row_write_pos - (unsigned __int16)*sprite_header);
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
    result = Render_FillRect(offscreen_surface, (_DWORD*)(&g_MainRenderDevice), 0, 0, *sprite_header - 1, sprite_header[1] - 1, var2, draw_y_saved);
    if ( offscreen_surface )
      return RenderSurface_InvokeSlot0(offscreen_surface, 2);
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
  surface[46] = (_DWORD)(uintptr_t)(g_Surface_RawBuffer8Vtable);
  pixel_count = (unsigned __int16)*(unsigned __int16 *)surface * (unsigned __int16)*((unsigned __int16 *)surface + 1);
  surface[1] = (unsigned int)nmalloc_(pixel_count, 4);
  if ( !surface[1] )
  {
    Debug_Log(0, 0, pixel_count, (int)(intptr_t)aNotEnoughMemor);
    App_RequestQuit((int)(intptr_t)aNotEnoughMem_0);
  }
  memset((void *)(uintptr_t)(unsigned int)surface[1], 0, pixel_count);
  if ( !surface[1] )
    App_RequestQuit((int)(intptr_t)aNotEnoughFreeM);
  return surface;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 50EE24: using guessed type int (*off_50EE24[5])();

//----- (00403E50) --------------------------------------------------------
int  Surface_DestructRawBuffer(int surface, char flags)
{
  int result; // eax

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__(surface, (_DWORD)(uintptr_t)(&g_SurfaceRawBuffer_DtorArrayTag));
    j_j__nfree_();
    return surface;
  }
  *(_DWORD *)(uintptr_t)(surface + 184) = (_DWORD)(uintptr_t)(g_Surface_RawBuffer8Vtable);
  nfree_(*(_DWORD *)(uintptr_t)(surface + 4));
  *(_DWORD *)(uintptr_t)(surface + 4) = 0;
  result = Surface_Destruct(surface + 8) - 8;
  if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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

  result = (_DWORD *)(uintptr_t)Mem_Alloc(12, x, y, context);
  if ( result )
  {
    row_pitch = *surface;
    row_offset = *surface * y;
    pixel_base = *((_DWORD *)surface + 1);
    *result = (_DWORD)(uintptr_t)(g_RenderSurface_BlitCursorVtable);
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

  result = (_DWORD *)(uintptr_t)Mem_Alloc(12, x, y, context);
  if ( result )
  {
    row_pitch = *surface;
    row_offset = *surface * y;
    pixel_base = *((_DWORD *)surface + 1);
    *result = (_DWORD)(uintptr_t)(g_RenderSurface_BlitCursorVtable);
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
  *(_BYTE *)(uintptr_t)(x + result) = color;
  return result;
}

//----- (00403F50) --------------------------------------------------------
int  Surface_GetPixel8(unsigned __int16 *surface, int x, int y)
{
  return *(unsigned __int8 *)(uintptr_t)(x + y * *surface + *((_DWORD *)surface + 1));
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
  unsigned __int16 x_cursor; // bx
  unsigned __int16 dashed_y_cursor; // dx
  unsigned __int16 y_cursor; // dx

  v6 = color_flags;
  pitch = *surface;
  result = (_BYTE *)(uintptr_t)(x_start + *((_DWORD *)surface + 1) + *surface * (unsigned __int16)y_start);
  if ( (color_flags & 0x100) != 0 )
  {
    if ( (_WORD)y_start == y_end )
    {
      while ( 1 )
      {
        x_cursor = x_start++;
        if ( x_cursor >= x_end )
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
        dashed_y_cursor = y_start;
        LOWORD(y_start) = y_start + 1;
        if ( dashed_y_cursor >= y_end )
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
    return (_BYTE *)(uintptr_t)memset_(v6, (unsigned __int8)color_flags);
  }
  else
  {
    while ( 1 )
    {
      y_cursor = y_start++;
      if ( y_cursor > y_end )
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
  int row_base; // ecx
  int row_addr; // ecx

  surface_ptr = result;
  row_index = y_start;
  row_base = y_start * *result + *((_DWORD *)result + 1);
  HIWORD(x) = 0;
  while ( 1 )
  {
    row_addr = x + row_base;
    if ( row_index > y_end )
      break;
    result = (unsigned __int16 *)(uintptr_t)memset_(row_addr, color);
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
    for ( j = i + (row_y & 1); col_x <= x_end; *(_BYTE *)(uintptr_t)(j - 2) = color )
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
  result[46] = (_DWORD)(uintptr_t)(g_ScratchSurface_Vtable);
  if ( companion_flag )
  {
    companion_surface = 0;
    allocated_companion = (_DWORD *)(uintptr_t)Mem_Alloc(176, 0, height, companion_flag);
    render_context = g_RenderContext;
    if ( allocated_companion && render_context )
      companion_surface = Surface_ConstructWithSurface(allocated_companion, (_DWORD *)(uintptr_t)(unsigned int)render_context, height, width_saved);
    if ( allocated_companion && !companion_surface )
      nfree_((int)(uintptr_t)allocated_companion);
    constructed_surface[48] = companion_surface != 0;
    constructed_surface[47] = (_DWORD)(uintptr_t)(companion_surface);
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

  if ( (flags & CRT_DTOR_FLAG_ARRAY_STORAGE) != 0 )
  {
    _wcpp_4_dtor_array_store__((_DWORD)(uintptr_t)(surface), (_DWORD)(uintptr_t)(&g_ScratchSurface_DtorArrayTag));
    j_j__nfree_();
    return (int)(intptr_t)surface;
  }
  owned_buffer = surface[47];
  surface[46] = (_DWORD)(uintptr_t)(g_ScratchSurface_Vtable);
  if ( owned_buffer && surface[48] )
  {
    Surface_Destruct(owned_buffer);
    j__nfree_();
  }
  result = Surface_Destruct((int)(intptr_t)(surface + 2)) - 8;
  if ( (flags & CRT_DTOR_FLAG_RELEASE_STORAGE) != 0 )
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
  unsigned int lock_error; // eax
  int v9; // ecx
  int pitch; // eax
  int region_view; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v6 + 184) + 60))();
    *(_DWORD *)(uintptr_t)HIDWORD(v7) = (_DWORD)(uintptr_t)(g_RenderSurface_LinkedBlitCursorVtable);
    *(_DWORD *)(uintptr_t)(HIDWORD(v7) + 4) = v7;
    lock_error = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( lock_error )
      Render_HandleDirectDrawFatalError(lock_error, v9);
    pitch = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v9 + 4))();
    *(_DWORD *)(uintptr_t)(region_view + 8) = y * pitch + x + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(region_view + 4) + 92);
    return region_view;
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
  unsigned int lock_error; // eax
  int v9; // ecx
  int pitch; // eax
  int region_view; // ecx

  result = Mem_Alloc(12, surface, y, context);
  if ( result )
  {
    v7 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v6 + 184) + 64))();
    *(_DWORD *)(uintptr_t)HIDWORD(v7) = (_DWORD)(uintptr_t)(g_RenderSurface_LinkedBlitCursorVtable);
    *(_DWORD *)(uintptr_t)(HIDWORD(v7) + 4) = v7;
    lock_error = Surface_LockWithRestore(v7, SHIDWORD(v7));
    if ( lock_error )
      Render_HandleDirectDrawFatalError(lock_error, v9);
    pitch = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v9 + 4))();
    *(_DWORD *)(uintptr_t)(region_view + 8) = y * pitch + x + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(region_view + 4) + 92);
    return region_view;
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

  write_view = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))();
  Surface_LockWithRestore(write_view, v3);
  Surface_SetPixelByte(write_view, v4, v5, y);
  return Surface_Unlock(write_view);
}
// 4043AC: variable 'v3' is possibly undefined
// 4043B3: variable 'v4' is possibly undefined
// 4043B3: variable 'v5' is possibly undefined

//----- (004043D0) --------------------------------------------------------
int  Surface_GetPix(int surface, int x, int y)
{
  int read_view; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  unsigned __int8 pixel_value; // dl

  read_view = (*(int (__cdecl **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 60))(x);
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
  unsigned __int16 prev_x; // dx
  unsigned __int16 prev_y; // dx
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
        prev_x = x_cursor;
        result = ++x_cursor;
        if ( prev_x >= x_end )
          break;
        if ( (result & 3) == 3 )
        {
          (*(void (__fastcall **)(_DWORD, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 12))((unsigned __int8)color_flags, result);
        }
        else
        {
          while ( 1 )
          {
            prev_y = y_cursor++;
            if ( prev_y >= y_end )
              break;
            if ( (y_cursor & 3) == 3 )
              (*(void (__fastcall **)(_DWORD, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 12))((unsigned __int8)color_flags, x_cursor);
          }
        }
      }
    }
  }
  else if ( y_start == y_end )
  {
    v13 = ((__int64 (__fastcall *)(_DWORD, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))(y_end, x_start);
    return Render_DrawHorizontalRun(v13, SHIDWORD(v13), v14, x_end, color_flags);
  }
  else if ( x_end == x_start )
  {
    v11 = ((__int64 (__fastcall *)(_DWORD, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))(x_start, y_start);
    return Render_DrawVerticalRun(v11, SHIDWORD(v11), v12, y_end, color_flags);
  }
  else
  {
    v15 = ((__int64 (__fastcall *)(_DWORD, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))(x_end, x_start);
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

  v6 = ((__int64 (__fastcall *)(_DWORD, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))(x1, y1);
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

  v6 = ((__int64 (__fastcall *)(unsigned int, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 64))((unsigned int)x2 + 1, x1);
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
      (*(void (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)(surface + 184) + 12))(color, j);
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

  palette_array = (int)(intptr_t)Render_ConstructScratchSurface(surface_addr, 0x280u, 0, SCREEN_HEIGHT) + 0xDC;
  *(_DWORD *)(uintptr_t)(palette_array - 24) = 0;
  *(_DWORD *)(uintptr_t)(palette_array - 20) = 1;
  *(_DWORD *)(uintptr_t)(palette_array - 16) = 1;
  *(_DWORD *)(uintptr_t)(palette_array - 12) = 0;
  *(_DWORD *)(uintptr_t)(palette_array - 8) = 0;
  *(_DWORD *)(uintptr_t)(palette_array - 4) = 0;
  palette_array = _wcpp_4_ctor_array__(palette_array, PALETTE_COLOR_COUNT);
  *(_DWORD *)(uintptr_t)(palette_array - 36) = (_DWORD)(uintptr_t)(g_Surface_Vtable);
  return palette_array - 0xDC;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 50EEC4: using guessed type int (*off_50EEC4[5])();
