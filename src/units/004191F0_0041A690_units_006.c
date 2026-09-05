/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "units_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE int UI_InvokeWidgetTransitionCallback (uintptr_t widget, int callback_arg);
CLASH95_TEST_VISIBLE int UI_InvokeWidgetActionCallback (uintptr_t widget);
CLASH95_TEST_VISIBLE unsigned int Compat_WidgetPackedField (uintptr_t widget, unsigned int field_offset);
CLASH95_TEST_VISIBLE unsigned int Compat_WidgetSpriteSetHandle (uintptr_t widget);

//----- (004191F0) --------------------------------------------------------
unsigned __int16 * UI_DrawWidgetIcon(unsigned __int16 *result, int doRefresh)
{
  unsigned char *widget;
  int left;
  int top;
  int flags;
  unsigned int sprite_set_holder;
  unsigned int sprite_set;
  int sprite_index;
  int overlay_sprite_index;
  int sprite_for_char;
  int cursorOverlayPresented;
  __int16 eraseSpriteHeight;
  unsigned __int16 eraseRight;

  widget = (unsigned char *)result;
  left = *(_DWORD *)(widget + 0);
  top = *(_DWORD *)(widget + 4);
  flags = *(_DWORD *)(widget + 8);
  sprite_set_holder = *(_DWORD *)(widget + 12);
  sprite_set = sprite_set_holder ? *(_DWORD *)(uintptr_t)sprite_set_holder : 0;
  sprite_index = (flags & 1) != 0 ? *(_DWORD *)(widget + 16) : *(_DWORD *)(widget + 20);
  overlay_sprite_index = *(_DWORD *)(widget + 24);
  if ( sprite_set && sprite_index != -1 )
  {
    /*
     * Original sub_4191F0 loc_41920B (clash95.asm 39089-39112) latches
     * dword_544D10 (g_CursorOverlayPresented) once and, when the live device
     * is the main render device, erases the software mouse cursor over the
     * icon rect before repainting it:
     *   call DLX_GetSpriteWidth / add ax,[esi+4] / dec eax / push eax
     *   call DLX_GetSpriteHeight / mov bx,[esi] / add eax,ebx / dec eax
     *   mov dx,[esi] / mov cx,ax / mov bx,[esi+4]
     *   mov eax, offset dword_544CD8 / call sub_460BB0
     * i.e. RenderState_PumpIfRectInViewBounds(g_RenderState, widget[0],
     * widget[0] + height - 1, widget[4], widget[4] + width - 1).
     * The raw decompile dropped both this call and its twin below; the
     * sibling UI_DrawWidgetIconWithTransition kept them.
     */
    cursorOverlayPresented = g_CursorOverlayPresented;
    if ( g_RenderDevice == &g_MainRenderDevice && cursorOverlayPresented )
    {
      eraseRight = (unsigned __int16)(result[2] + DLX_GetSpriteWidth(sprite_set, (unsigned __int16)sprite_index) - 1);
      eraseSpriteHeight = DLX_GetSpriteHeight(sprite_set, (unsigned __int16)sprite_index);
      RenderState_PumpIfRectInViewBounds(
        g_RenderState,
        *result,
        (unsigned __int16)(*result + eraseSpriteHeight - 1),
        result[2],
        eraseRight);
    }
    sprite_for_char = DLX_GetSpriteForChar(sprite_set, sprite_index);
    Compat_RenderDeviceDrawMenuSprite(left, top, sprite_for_char, 0);
    if ( (flags & 4) != 0 && overlay_sprite_index != -1 )
    {
      sprite_for_char = DLX_GetSpriteForChar(sprite_set, overlay_sprite_index);
      Compat_RenderDeviceDrawMenuSprite(left, top, sprite_for_char, 1);
    }
    if ( g_RenderDevice == &g_MainRenderDevice && cursorOverlayPresented )
      return (unsigned __int16 *)(uintptr_t)Render_Present((int)(intptr_t)g_RenderState);
    if ( doRefresh && g_RenderDevice != &g_MainRenderDevice )
    {
      /*
       * Original sub_4191F0 loc_419316->39203: the same cursor erase runs
       * again on the offscreen-device refresh path, guarded only by the
       * latched dword_544D10, before the slot blit below.
       */
      if ( cursorOverlayPresented )
      {
        eraseRight = (unsigned __int16)(result[2] + DLX_GetSpriteWidth(sprite_set, (unsigned __int16)sprite_index) - 1);
        eraseSpriteHeight = DLX_GetSpriteHeight(sprite_set, (unsigned __int16)sprite_index);
        RenderState_PumpIfRectInViewBounds(
          g_RenderState,
          *result,
          (unsigned __int16)(*result + eraseSpriteHeight - 1),
          result[2],
          eraseRight);
      }
      Render_FillRect(
        g_RenderDevice,
        0,
        (unsigned __int16)top,
        (unsigned __int16)left,
        (unsigned __int16)(top + DLX_GetSpriteHeight(sprite_set, sprite_index) - 1),
        (unsigned __int16)(left + DLX_GetSpriteWidth(sprite_set, sprite_index) - 1),
        (unsigned __int16)left,
        (unsigned __int16)top);
      /* asm loc_4193F0: the offscreen path presents too when the cursor
       * overlay is up. */
      if ( cursorOverlayPresented )
        return (unsigned __int16 *)(uintptr_t)Render_Present((int)(intptr_t)g_RenderState);
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

CLASH95_INTERNAL int Compat_RenderDeviceFillSolidRect(
        unsigned __int16 left,
        unsigned __int16 top,
        unsigned __int16 right,
        unsigned __int16 bottom,
        unsigned char color)
{
  _DWORD *surface;
  unsigned char *surface_pixels;
  int pitch;
  int surface_width;
  int surface_height;
  int row;

  if ( !g_RenderDevice )
    return 0;
  surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
  if ( !surface || !RenderSurface_IsLinearSoftware(surface) )
    return 0;
  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !surface_pixels )
    return 0;

  pitch = *(unsigned __int16 *)surface;
  surface_width = *(unsigned __int16 *)surface;
  surface_height = *((unsigned __int16 *)surface + 1);
  if ( left > right || top > bottom || left >= surface_width || top >= surface_height )
    return 0;
  if ( right >= surface_width )
    right = surface_width - 1;
  if ( bottom >= surface_height )
    bottom = surface_height - 1;

  for ( row = top; row <= bottom; ++row )
    memset(surface_pixels + row * pitch + left, color, right - left + 1);
  return 0;
}

CLASH95_INTERNAL int Compat_RenderSurfaceCopyRect(
        _DWORD *source,
        _DWORD *destination,
        int source_left,
        int source_top,
        int source_right,
        int source_bottom,
        int destination_left,
        int destination_top)
{
  _DWORD *source_surface;
  _DWORD *destination_surface;
  unsigned char *source_pixels;
  unsigned char *destination_pixels;
  int source_pitch;
  int destination_pitch;
  int source_width;
  int source_height;
  int destination_width;
  int destination_height;
  int copy_width;
  int copy_height;
  int row;

  if ( !source )
    source = &g_MainRenderDevice;
  if ( !destination )
    destination = &g_MainRenderDevice;
  source_surface = RenderSurface_ResolvePrimaryCompanion(source);
  destination_surface = RenderSurface_ResolvePrimaryCompanion(destination);
  if ( !source_surface || !destination_surface
    || !RenderSurface_IsLinearSoftware(source_surface)
    || !RenderSurface_IsLinearSoftware(destination_surface) )
  {
    return 0;
  }

  source_pixels = (unsigned char *)(uintptr_t)(unsigned int)source_surface[1];
  destination_pixels = (unsigned char *)(uintptr_t)(unsigned int)destination_surface[1];
  if ( !source_pixels || !destination_pixels )
    return 0;

  source_pitch = *(unsigned __int16 *)source_surface;
  destination_pitch = *(unsigned __int16 *)destination_surface;
  source_width = source_pitch;
  destination_width = destination_pitch;
  source_height = *((unsigned __int16 *)source_surface + 1);
  destination_height = *((unsigned __int16 *)destination_surface + 1);
  copy_width = source_right - source_left + 1;
  copy_height = source_bottom - source_top + 1;
  if ( copy_width <= 0 || copy_height <= 0 )
    return 1;

  if ( source_left < 0 )
  {
    destination_left -= source_left;
    copy_width += source_left;
    source_left = 0;
  }
  if ( source_top < 0 )
  {
    destination_top -= source_top;
    copy_height += source_top;
    source_top = 0;
  }
  if ( destination_left < 0 )
  {
    source_left -= destination_left;
    copy_width += destination_left;
    destination_left = 0;
  }
  if ( destination_top < 0 )
  {
    source_top -= destination_top;
    copy_height += destination_top;
    destination_top = 0;
  }
  if ( source_left >= source_width || source_top >= source_height
    || destination_left >= destination_width || destination_top >= destination_height )
  {
    return 1;
  }
  if ( source_left + copy_width > source_width )
    copy_width = source_width - source_left;
  if ( destination_left + copy_width > destination_width )
    copy_width = destination_width - destination_left;
  if ( source_top + copy_height > source_height )
    copy_height = source_height - source_top;
  if ( destination_top + copy_height > destination_height )
    copy_height = destination_height - destination_top;
  if ( copy_width <= 0 || copy_height <= 0 )
    return 1;

  for ( row = 0; row < copy_height; ++row )
    memmove(
      destination_pixels + (destination_top + row) * destination_pitch + destination_left,
      source_pixels + (source_top + row) * source_pitch + source_left,
      copy_width);
  return 1;
}

CLASH95_INTERNAL int Compat_RenderDeviceDrawMenuSprite(int left, int top, int sprite_for_char, unsigned char draw_mode)
{
  _DWORD *surface;
  unsigned char *surface_pixels;
  unsigned char *stream;
  unsigned char *stream_end;
  int pitch;
  int surface_width;
  int surface_height;
  int width;
  int height;
  int format;
  int entry_size;
  int row;

  if ( !g_RenderDevice || !sprite_for_char )
    return 0;
  surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
  if ( !surface || !RenderSurface_IsLinearSoftware(surface) )
    return 0;
  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !surface_pixels )
    return 0;

  /*
   * Several recovered callers still reach the generic `sub_402E80`
   * (`Render_BlitCompressedSpriteRLE`) decoder, but that path is polluted by
   * x86-sized helper objects that are unsafe on x86-64. This seam decodes the
   * format-0 stream byte-exactly per the recovered reference
   * (render_002.c:358-381, 577-580, 643-712):
   *  - opcode & 0x80: transparent run of (opcode & 0x7F); opaque mode fills
   *    g_Render_BackgroundColorIndex (ref :691); consumes no stream bytes.
   *  - opcode 1..0x7F: literal run; consumes the FULL run of pixel bytes and
   *    advances the column by the full length (ref :580,706) - clipping only
   *    affects drawing, never stream position or column arithmetic.
   *  - opcode 0: back-reference; the NEXT byte is a one-byte offset measured
   *    backwards from its own position to a prior literal run's length byte
   *    (ref :378-381); decode that run's pixels, then resume at the byte after
   *    the offset byte (ref :577-578). References may reach before this
   *    record into earlier bytes of the loaded DLX file - no floor.
   *  - rows that fall off the surface still consume their runs (the original
   *    clips via its blit cursor, never aborting the stream); row overshoot
   *    pixels are written like the original's linear cursor and are
   *    overdrawn by the following tile.
   * The earlier partial decoder desynchronized the stream (4-byte offset
   * guess + clamped consumption), which misread data bytes >= 0x80 as
   * transparent runs and produced black speckles in world terrain tiles
   * (proven by the tile-by-tile comparison vs the original on real Win98).
   */
  width = *(unsigned __int16 *)(uintptr_t)sprite_for_char;
  height = *(unsigned __int16 *)(uintptr_t)(sprite_for_char + 2);
  format = *(unsigned __int16 *)(uintptr_t)(sprite_for_char + 4);
  if ( format != 0 || width <= 0 || height <= 0 )
    return 0;

  stream = (unsigned char *)(uintptr_t)(unsigned int)*(unsigned int *)(uintptr_t)(sprite_for_char + 10);
  if ( !stream )
    return 0;
  entry_size = *(int *)(uintptr_t)(sprite_for_char + 14);
  if ( entry_size <= 10 )
    return 0;
  stream_end = stream + (entry_size - 10);
  pitch = *(unsigned __int16 *)surface;
  surface_width = *(unsigned __int16 *)surface;
  surface_height = *((unsigned __int16 *)surface + 1);

  for ( row = 0; row < height; ++row )
  {
    int column;
    int row_y;
    int row_visible;
    unsigned char *destination_row;

    row_y = top + row;
    row_visible = row_y >= 0 && row_y < surface_height;
    destination_row = row_visible ? surface_pixels + row_y * pitch : 0;
    column = 0;
    while ( column < width )
    {
      unsigned char opcode;
      unsigned int run_length;
      const unsigned char *run_pixels;

      if ( stream >= stream_end )   /* crash guard only; the original never
                                     * bounds the stream - a hit means
                                     * malformed data, draw what we have */
        return 0;
      opcode = *stream++;
      if ( (opcode & 0x80u) != 0 )
      {
        run_length = opcode & 0x7F;
        if ( !draw_mode && row_visible )
        {
          unsigned int i;

          for ( i = 0; i < run_length; ++i )
          {
            int destination_x;

            destination_x = left + column + (int)i;
            if ( destination_x >= 0 && destination_x < surface_width )
              destination_row[destination_x] = (unsigned char)g_Render_BackgroundColorIndex;
          }
        }
        column += run_length;
        continue;
      }

      if ( opcode )
      {
        run_length = opcode;
        run_pixels = stream;
        stream += run_length;               /* consume the FULL run */
      }
      else
      {
        /* back-reference: opcode 0 is followed by a 32-bit little-endian offset
         * field; the referenced run's length byte sits at (offset_field -
         * offset) and its pixels follow. The original reads the offset as a
         * DWORD (`sub esi,[ecx]` at 0x403492) and resumes 4 bytes past it (the
         * render_002.c reference types backref_len_ptr _DWORD*, :378,577). The
         * earlier 1-byte reimplementation desynced every back-reference sprite
         * (water / mountains / textured edges) -> the horizontal black bands on
         * mission terrain; verified: all 959 backgr1.s32 64x64 entries decode
         * with every row summing to width under the 4-byte rule (0 corrupted). */
        const unsigned char *referenced_run;
        unsigned int back_offset;

        back_offset = (unsigned int)stream[0]
                    | ((unsigned int)stream[1] << 8)
                    | ((unsigned int)stream[2] << 16)
                    | ((unsigned int)stream[3] << 24);
        referenced_run = stream - back_offset;
        run_length = *referenced_run;
        run_pixels = referenced_run + 1;
        stream += 4;                        /* resume past the 4-byte offset field */
      }
      if ( row_visible )
      {
        unsigned int i;

        for ( i = 0; i < run_length; ++i )
        {
          int destination_x;

          destination_x = left + column + (int)i;
          if ( destination_x >= 0 && destination_x < surface_width )
            destination_row[destination_x] = run_pixels[i];
        }
      }
      column += run_length;
    }
  }

  return 0;
}

//----- (00419410) --------------------------------------------------------
int  UI_DrawWidgetIconWithTransition(unsigned __int16 *iconWidget, int animate, int transitionDuration, DWORD allocContext)
{
  int result; // eax
  unsigned char *widget; // edi
  int left; // ebx
  int top; // ebx
  int flags; // edx
  unsigned int sprite_set_holder; // esi
  unsigned int sprite_set; // esi
  int overlay_sprite_index; // esi
  __int16 SpriteHeight; // ax
  int v7; // ecx
  _DWORD *Surface; // eax
  int v9; // ecx
  _DWORD *iconSurface; // eax
  void *renderedSurface; // ebp
  int renderedSurfaceHandle; // edi
  void *prevRenderDevice; // eax
  int SpriteForChar; // eax
  int v15; // edx
  int v16; // ecx
  int startTime; // eax
  int v18; // ecx
  unsigned int animDeadline; // ebp
  int v20; // edx
  int v21; // ecx
  int nowTime; // eax
  int v23; // edx
  int overlaySprite; // eax
  int iconSprite; // eax
  unsigned __int16 rectRight; // [esp+18h] [ebp-4Ch]
  void *restoreRenderDevice; // [esp+1Ch] [ebp-48h]
  unsigned int fadeDuration; // [esp+20h] [ebp-44h]
  __int16 SpriteWidth; // [esp+24h] [ebp-40h]
  int spriteIndex; // [esp+28h] [ebp-3Ch]
  int animStartTime; // [esp+2Ch] [ebp-38h]
  int cursorOverlayPresented; // [esp+3Ch] [ebp-28h]
  int savedSurface; // [esp+40h] [ebp-24h]
  __int16 transSpriteHeight; // [esp+48h] [ebp-1Ch]
  unsigned __int16 transRight; // [esp+4Ch] [ebp-18h]
  unsigned __int16 transBottom; // [esp+50h] [ebp-14h]

  widget = (unsigned char *)iconWidget;
  fadeDuration = transitionDuration;
  left = *(_DWORD *)(widget + 0);
  top = *(_DWORD *)(widget + 4);
  flags = widget[8];
  sprite_set_holder = *(_DWORD *)(widget + 12);
  if ( sprite_set_holder )
    sprite_set = *(_DWORD *)(uintptr_t)sprite_set_holder;
  else
    sprite_set = 0;
  overlay_sprite_index = *(_DWORD *)(widget + 24);
  if ( (iconWidget[4] & 1) != 0 )
    result = *((_DWORD *)iconWidget + 4);
  else
    result = *((_DWORD *)iconWidget + 5);
  spriteIndex = result;
  if ( !animate )
  {
    if ( !sprite_set || spriteIndex == -1 )
      return result;
    iconSprite = DLX_GetSpriteForChar(sprite_set, spriteIndex);
    result = Compat_RenderDeviceDrawMenuSprite(left, top, iconSprite, 0);
    if ( (flags & 4) != 0 && overlay_sprite_index != -1 )
    {
      overlaySprite = DLX_GetSpriteForChar(sprite_set, overlay_sprite_index);
      result = Compat_RenderDeviceDrawMenuSprite(left, top, overlaySprite, 1);
    }
    return result;
  }
  if ( result != -1 )
  {
    cursorOverlayPresented = g_CursorOverlayPresented;
    if ( animate && g_CursorOverlayPresented )
    {
      rectRight = iconWidget[2] + DLX_GetSpriteWidth(sprite_set, result) - 1;
      SpriteHeight = DLX_GetSpriteHeight(sprite_set, spriteIndex);
      LOWORD(transitionDuration) = iconWidget[2];
      RenderState_PumpIfRectInViewBounds(g_RenderState, *iconWidget, *iconWidget + SpriteHeight - 1, transitionDuration, rectRight);
    }
    if ( animate )
    {
      _DWORD *menu_surface;

      menu_surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
      if ( menu_surface && RenderSurface_IsLinearSoftware(menu_surface) )
      {
        iconSprite = DLX_GetSpriteForChar(sprite_set, spriteIndex);
        result = Compat_RenderDeviceDrawMenuSprite(left, top, iconSprite, 0);
        if ( (iconWidget[4] & 4) != 0 && *((_DWORD *)iconWidget + 6) != -1 )
        {
          overlaySprite = DLX_GetSpriteForChar(sprite_set, *((_DWORD *)iconWidget + 6));
          result = Compat_RenderDeviceDrawMenuSprite(left, top, overlaySprite, 1);
        }
        if ( cursorOverlayPresented )
          return Render_Present((int)(intptr_t)g_RenderState);
        return result;
      }
    }
    if ( animate )
    {
      transSpriteHeight = DLX_GetSpriteHeight(sprite_set, spriteIndex);
      SpriteWidth = DLX_GetSpriteWidth(sprite_set, spriteIndex);
      Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, transitionDuration, allocContext);
      if ( Surface )
      {
        LOBYTE(transitionDuration) = SpriteWidth;
        Surface = Render_CreateSurface((int)(intptr_t)Surface, transSpriteHeight, SpriteWidth);
      }
      savedSurface = (int)(intptr_t)Surface;
      iconSurface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v9, transitionDuration, allocContext);
      if ( iconSurface )
        iconSurface = Render_CreateSurface((int)(intptr_t)iconSurface, transSpriteHeight, SpriteWidth);
      renderedSurface = iconSurface;
      renderedSurfaceHandle = (int)(intptr_t)iconSurface;
      Render_FillRect(g_RenderDevice, (_DWORD *)(uintptr_t)savedSurface, iconWidget[2], *iconWidget, transSpriteHeight + *iconWidget - 1, SpriteWidth + iconWidget[2] - 1, 0, 0);
      prevRenderDevice = g_RenderDevice;
      g_RenderDevice = renderedSurface;
      restoreRenderDevice = prevRenderDevice;
      SpriteForChar = DLX_GetSpriteForChar(sprite_set, spriteIndex);
      Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 0);
      g_RenderDevice = restoreRenderDevice;
      startTime = Time_Now(v16, v15);
      animDeadline = startTime + fadeDuration;
      animStartTime = startTime;
      v20 = fadeDuration;
      transBottom = transSpriteHeight - 1;
      transRight = SpriteWidth - 1;
      while ( Time_Now(v18, v20) < animDeadline )
      {
        nowTime = Time_Now(v21, animStartTime);
        Render_BlendSurfaceRect(0, savedSurface, 0, renderedSurfaceHandle, 0, transBottom, transRight, *iconWidget, iconWidget[2], 255 * (nowTime - v23) / fadeDuration);
        if ( g_ActiveDialogAnimationTickHook )
          g_ActiveDialogAnimationTickHook();
      }
      result = Render_FillRect((_DWORD *)(uintptr_t)renderedSurfaceHandle, 0, 0, 0, transBottom, transRight, *iconWidget, iconWidget[2]);
      if ( g_RenderDevice != &g_MainRenderDevice )
        result = Render_FillRect((_DWORD *)(uintptr_t)renderedSurfaceHandle, g_RenderDevice, 0, 0, transBottom, transRight, *iconWidget, iconWidget[2]);
      if ( savedSurface )
        result = RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)savedSurface, 2);
      if ( renderedSurfaceHandle )
        result = RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)renderedSurfaceHandle, 2);
    }
    else
    {
      iconSprite = DLX_GetSpriteForChar(sprite_set, spriteIndex);
      result = Compat_RenderDeviceDrawMenuSprite(left, top, iconSprite, 0);
    }
    if ( (iconWidget[4] & 4) != 0 && *((_DWORD *)iconWidget + 6) != -1 )
    {
      overlaySprite = DLX_GetSpriteForChar(sprite_set, *((_DWORD *)iconWidget + 6));
      result = Compat_RenderDeviceDrawMenuSprite(left, top, overlaySprite, 1);
    }
    if ( animate && cursorOverlayPresented )
      return Render_Present((int)(intptr_t)g_RenderState);
  }
  return result;
}
// 4194DD: variable 'v7' is possibly undefined
// 419502: variable 'v9' is possibly undefined
// 4195B5: variable 'v16' is possibly undefined
// 4195B5: variable 'v15' is possibly undefined
// 4195DA: variable 'v18' is possibly undefined
// 4195DA: variable 'v20' is possibly undefined
// 4195E7: variable 'v21' is possibly undefined
// 4195EC: variable 'v23' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 526A30: using guessed type int (*dword_526A30)(void);
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00419770) --------------------------------------------------------
int  UI_DrawWidgetIconTransitionSlow(unsigned __int16 *a1, int a2, DWORD a3)
{
  return UI_DrawWidgetIconWithTransition(a1, a2, 20, a3);
}

//----- (00419780) --------------------------------------------------------
int  UI_DrawWidgetIconTransitionFast(unsigned __int16 *a1, int a2, DWORD a3)
{
  return UI_DrawWidgetIconWithTransition(a1, a2, 10, a3);
}

CLASH95_TEST_VISIBLE int UI_InvokeWidgetTransitionCallback(uintptr_t widget, int callback_arg)
{
  unsigned int callback;

  callback = *(_DWORD *)(widget + 28);
  if ( !callback )
    return 0;
  return ((int (__cdecl *)(uintptr_t, int, DWORD))(uintptr_t)callback)(widget, callback_arg, 0);
}

CLASH95_TEST_VISIBLE int UI_InvokeWidgetActionCallback(uintptr_t widget)
{
  unsigned int callback;

  callback = *(_DWORD *)(widget + 32);
  if ( !callback )
    return 0;
  return ((int (__cdecl *)(uintptr_t, int, DWORD, char, double))(uintptr_t)callback)(widget, 0, 0, 0, 0.0);
}

CLASH95_TEST_VISIBLE unsigned int Compat_WidgetPackedField(uintptr_t widget, unsigned int field_offset)
{
  return (unsigned int)*(_DWORD *)(widget + field_offset);
}

CLASH95_TEST_VISIBLE unsigned int Compat_WidgetSpriteSetHandle(uintptr_t widget)
{
  unsigned int sprite_set_holder;

  sprite_set_holder = Compat_WidgetPackedField(widget, 12);
  if ( !sprite_set_holder )
    return 0;
  return (unsigned int)*(_DWORD *)(uintptr_t)sprite_set_holder;
}

CLASH95_INTERNAL const char *Compat_WidgetPackedString(uintptr_t widget, unsigned int field_offset)
{
  return (const char *)(uintptr_t)Compat_WidgetPackedField(widget, field_offset);
}

//----- (00419790) --------------------------------------------------------
int  UI_SetActiveWidgetTable(int result)
{
  g_ActiveWidgetSpriteTableIndex = result;
  return result;
}
// 526A2C: using guessed type int dword_526A2C;

//----- (004197A0) --------------------------------------------------------
BOOL  UIWidget_ShowTextWithFadeTransition(uintptr_t widget, DWORD allocContext)
{
  int cursorX; // ebx
  int TextXOffset; // eax
  int v4; // edx
  int textBottom; // edx
  int v6; // ecx
  int v7; // ebx
  int v8; // edx
  _DWORD *Surface; // eax
  int v10; // ecx
  int backgroundSurface; // esi
  _DWORD *v12; // eax
  _DWORD *textSurface; // ebp
  int textSurfaceHandle; // edi
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // edx
  int fadeInNow; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  DWORD fadeOutDeadline; // ebp
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int fadeOutNow; // eax
  int v29; // edx
  int savedTextSlot; // [esp+0h] [ebp-64h]
  int rectRight; // [esp+4h] [ebp-60h]
  int fadeOutStart; // [esp+8h] [ebp-5Ch]
  int fadeInStart; // [esp+Ch] [ebp-58h]
  void *savedRenderDevice; // [esp+24h] [ebp-40h]
  DWORD rectLeft; // [esp+2Ch] [ebp-38h]
  int cursorY; // [esp+30h] [ebp-34h]
  int rectBottom; // [esp+34h] [ebp-30h]
  unsigned __int16 rectHeightIn; // [esp+3Ch] [ebp-28h]
  unsigned __int16 rectHeightOut; // [esp+40h] [ebp-24h]
  unsigned __int16 rectWidthOut; // [esp+44h] [ebp-20h]
  unsigned __int16 rectWidthIn; // [esp+48h] [ebp-1Ch]

  savedTextSlot = g_ActiveTextSpriteSlot;
  Render_ReleaseSurface(g_ActiveWidgetSpriteTableIndex, allocContext);
  savedRenderDevice = g_RenderDevice;
  cursorY = g_MouseCursorRawY >> g_CursorCoordShift;
  cursorX = g_MouseCursorRawX >> g_CursorCoordShift;
  rectRight = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(widget + 4 * (unsigned __int8)g_LanguageIndex + 36))
      + (g_MouseCursorRawX >> g_CursorCoordShift);
  TextXOffset = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
  textBottom = TextXOffset + v4;
  rectLeft = cursorX;
  v6 = rectRight;
  rectBottom = textBottom;
  if ( cursorX + *(_DWORD *)(uintptr_t)(g_ActiveCursorDescriptorPtr + 12) > rectRight )
    rectRight = cursorX + *(_DWORD *)(uintptr_t)(g_ActiveCursorDescriptorPtr + 12);
  v7 = *(_DWORD *)(uintptr_t)(g_ActiveCursorDescriptorPtr + 16);
  if ( cursorY + v7 > textBottom )
    rectBottom = cursorY + v7;
  if ( rectRight > 639 )
  {
    allocContext = rectLeft - (rectRight - 639);
    rectLeft = allocContext;
    LOWORD(rectRight) = 639;
  }
  v8 = rectBottom;
  if ( rectBottom > 479 )
  {
    LOBYTE(v7) = -33;
    v6 = cursorY - (rectBottom - 479);
    LOWORD(rectBottom) = 479;
    cursorY -= v8 - 479;
  }
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v6, v7, allocContext);
  if ( Surface )
  {
    LOWORD(v7) = rectBottom - cursorY + 1;
    Surface = Render_CreateSurface((int)(intptr_t)Surface, rectRight - rectLeft + 1, v7);
  }
  backgroundSurface = (int)(intptr_t)Surface;
  v12 = (_DWORD *)(uintptr_t)Mem_Alloc(188, v10, v7, allocContext);
  if ( v12 )
    v12 = Render_CreateSurface((int)(intptr_t)v12, rectRight - rectLeft + 1, rectBottom - cursorY + 1);
  textSurface = v12;
  Render_FillRect(0, (_DWORD *)(uintptr_t)backgroundSurface, (unsigned __int16)cursorY, (unsigned __int16)rectLeft, rectRight, rectBottom, 0, 0);
  Render_SaveBackbuffer((int)(intptr_t)&g_MainRenderDevice);
  Render_Pump();
  Render_FillRect(0, textSurface, (unsigned __int16)cursorY, (unsigned __int16)rectLeft, rectRight, rectBottom, 0, 0);
  textSurfaceHandle = (int)(intptr_t)textSurface;
  Render_Present((int)(intptr_t)&g_RenderState);
  g_RenderDevice = textSurface;
  UI_DrawText(0, 0, *(_DWORD *)(widget + 4 * (unsigned __int8)g_LanguageIndex + 36));
  fadeInStart = Time_Now(v16, v15);
  v18 = 30;
  rectWidthIn = rectRight - rectLeft;
  rectHeightIn = rectBottom - cursorY;
  while ( Time_Now(v17, v18) < (unsigned int)(fadeInStart + 30) )
  {
    fadeInNow = Time_Now(fadeInStart, v19);
    Render_BlendSurfaceRect(0, backgroundSurface, 0, (int)(intptr_t)textSurface, 0, rectWidthIn, rectHeightIn, rectLeft, cursorY, 255 * (fadeInNow - v21) / 0x1Eu);
  }
  Render_FillRect(textSurface, 0, 0, 0, rectWidthIn, rectHeightIn, rectLeft, cursorY);
  Render_FlipRect((int)(intptr_t)&g_RenderState, 0);
  fadeOutStart = Time_Now(v23, v22);
  fadeOutDeadline = fadeOutStart + 30;
  v25 = rectLeft;
  v26 = cursorY;
  rectWidthOut = rectRight - rectLeft;
  rectHeightOut = rectBottom - cursorY;
  while ( Time_Now(v25, v26) < fadeOutDeadline )
  {
    fadeOutNow = Time_Now(v27, fadeOutStart);
    Render_BlendSurfaceRect(0, textSurfaceHandle, 0, backgroundSurface, 0, rectWidthOut, rectHeightOut, rectLeft, cursorY, 255 * (fadeOutNow - v29) / 0x1Eu);
  }
  Render_FillRect((_DWORD *)(uintptr_t)backgroundSurface, 0, 0, 0, rectWidthOut, rectHeightOut, rectLeft, cursorY);
  if ( backgroundSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)backgroundSurface, 2);
  if ( textSurfaceHandle )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)textSurfaceHandle, 2);
  Render_ReleaseSurface(savedTextSlot, fadeOutDeadline);
  g_RenderDevice = savedRenderDevice;
  return Render_Begin((int)(intptr_t)&g_RenderState, 0);
}
// 419827: variable 'v4' is possibly undefined
// 4198E5: variable 'v10' is possibly undefined
// 4199BE: variable 'v16' is possibly undefined
// 4199BE: variable 'v15' is possibly undefined
// 4199EC: variable 'v17' is possibly undefined
// 4199EC: variable 'v18' is possibly undefined
// 4199F9: variable 'v19' is possibly undefined
// 4199FE: variable 'v21' is possibly undefined
// 419A80: variable 'v23' is possibly undefined
// 419A80: variable 'v22' is possibly undefined
// 419AB0: variable 'v25' is possibly undefined
// 419AB0: variable 'v26' is possibly undefined
// 419ABD: variable 'v27' is possibly undefined
// 419AC2: variable 'v29' is possibly undefined
// 419B4B: variable 'v31' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 526A2C: using guessed type int dword_526A2C;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00419B80) --------------------------------------------------------
signed int  UIWidget_PollHitHoverAndClick(uintptr_t widget, DWORD a2)
{
  int resultState; // esi
  int hitSpriteIndex; // eax
  int widthSpriteIndex; // eax
  int sprite_set_handle;
  uintptr_t localizedStringBase; // eax
  uintptr_t localizedTooltipBase; // eax
  int tooltipString; // ecx
  int queen_widget_index;
  int queen_widget_sprite;
  int queen_widget_width;
  int queen_widget_height;
  int queen_cursor_x;
  int queen_cursor_y;
  char v10; // [esp+0h] [ebp-18h]

  resultState = 0;
  sprite_set_handle = Compat_WidgetSpriteSetHandle(widget);
  if ( g_QueenMarriageProposalWidgetTableBase
    && widget >= g_QueenMarriageProposalWidgetTableBase
    && widget < g_QueenMarriageProposalWidgetTableBase + 2 * 53
    && (DD_IsFlipping((int)(intptr_t)g_RenderState) || DD_IsLost((int)(intptr_t)g_RenderState)) )
  {
    queen_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    queen_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    queen_widget_index = (int)((widget - g_QueenMarriageProposalWidgetTableBase) / 53);
    queen_widget_sprite = *(_DWORD *)(widget + 20) == -1 ? *(_DWORD *)(widget + 16) : *(_DWORD *)(widget + 20);
    queen_widget_width = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, queen_widget_sprite) : 0;
    queen_widget_height = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, queen_widget_sprite) : 0;
    if ( getenv("CLASH95_TRACE_QUEEN_WIDGET_VERBOSE")
      || (queen_cursor_x >= *(_DWORD *)widget
       && queen_cursor_y >= *(_DWORD *)(widget + 4)
       && queen_cursor_x < *(_DWORD *)widget + queen_widget_height
       && queen_cursor_y < *(_DWORD *)(widget + 4) + queen_widget_width) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_probe",
        queen_widget_index,
        *(_DWORD *)widget,
        *(_DWORD *)(widget + 4),
        *(_DWORD *)(widget + 8));
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_bounds",
        queen_widget_index,
        queen_widget_height,
        queen_widget_width,
        *(_DWORD *)(widget + 32));
    }
  }
  if ( widget >= (uintptr_t)BuildingGarrisonDialogActions
    && widget < (uintptr_t)(BuildingGarrisonDialogActions
                      + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT)
    && (DD_IsFlipping((int)(intptr_t)g_RenderState) || DD_IsLost((int)(intptr_t)g_RenderState) || getenv("CLASH95_TRACE_GARRISON_WIDGET_VERBOSE")) )
  {
    int garrison_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    int garrison_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    int garrison_widget_index = (int)((widget - (uintptr_t)BuildingGarrisonDialogActions) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
    int garrison_widget_sprite = *(_DWORD *)(widget + 20) == -1 ? *(_DWORD *)(widget + 16) : *(_DWORD *)(widget + 20);
    int garrison_widget_width = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, garrison_widget_sprite) : 0;
    int garrison_widget_height = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, garrison_widget_sprite) : 0;
    int garrison_widget_inside = garrison_cursor_x >= *(_DWORD *)widget
                              && garrison_cursor_y >= *(_DWORD *)(widget + 4)
                              && garrison_cursor_x < *(_DWORD *)widget + garrison_widget_height
                              && garrison_cursor_y < *(_DWORD *)(widget + 4) + garrison_widget_width;

    if ( getenv("CLASH95_TRACE_GARRISON_WIDGET_VERBOSE") || garrison_widget_inside )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_probe",
        garrison_widget_index,
        *(_DWORD *)widget,
        *(_DWORD *)(widget + 4),
        *(_DWORD *)(widget + 8));
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_bounds",
        garrison_widget_index,
        garrison_widget_height,
        garrison_widget_width,
        garrison_widget_inside);
    }
  }
  if ( g_MouseCursorRawX >> g_CursorCoordShift < *(_DWORD *)widget || g_MouseCursorRawY >> g_CursorCoordShift < *(_DWORD *)(widget + 4) )
    goto LABEL_29;
  hitSpriteIndex = *(_DWORD *)(widget + 20) == -1 ? *(_DWORD *)(widget + 16) : *(_DWORD *)(widget + 20);
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= *(_DWORD *)widget
                                    + (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, hitSpriteIndex)
                                    - 1 )
    goto LABEL_29;
  widthSpriteIndex = *(_DWORD *)(widget + 20);
  if ( widthSpriteIndex == -1 )
    widthSpriteIndex = *(_DWORD *)(widget + 16);
  if ( g_MouseCursorRawY >> g_CursorCoordShift >= *(_DWORD *)(widget + 4)
                                    + (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, widthSpriteIndex)
                                    - 1 )
  {
LABEL_29:
    if ( (*(_BYTE *)(widget + 8) & 4) == 0 )
      goto LABEL_34;
    localizedTooltipBase = widget + 4 * (unsigned __int8)g_LanguageIndex;
    tooltipString = *(_DWORD *)(localizedTooltipBase + 36);
    if ( tooltipString && *(_BYTE *)(widget + 48) == 1 )
      Tooltip_RestoreIfTextMatches(tooltipString, tooltipString);
    resultState = 1;
    *(_BYTE *)(widget + 8) &= ~4u;
LABEL_23:
    if ( *(_DWORD *)(widget + 24) == -1 )
      return resultState;
    UI_InvokeWidgetTransitionCallback(widget, 1);
    return resultState;
  }
  if ( (uintptr_t)widget >= (uintptr_t)g_WorldMapActionButtonWidgetTable
    && (uintptr_t)widget < (uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * WORLD_MAP_ACTION_WIDGET_COUNT)
    && (DD_IsFlipping((int)(intptr_t)g_RenderState) || DD_IsLost((int)(intptr_t)g_RenderState)) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "action_widget_hit",
      (int)(((uintptr_t)widget - (uintptr_t)g_WorldMapActionButtonWidgetTable) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE),
      *(_DWORD *)widget,
      *(_DWORD *)(widget + 4),
      *(_DWORD *)(widget + 8));
  }
  if ( DD_IsLost((int)(intptr_t)g_RenderState) && *(_BYTE *)(widget + 48) == 2 )
    UIWidget_ShowTextWithFadeTransition(widget, a2);
  if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && *(_DWORD *)(widget + 32) )
  {
    if ( widget >= (uintptr_t)BuildingGarrisonDialogActions
      && widget < (uintptr_t)(BuildingGarrisonDialogActions
                        + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_action",
        (int)((widget - (uintptr_t)BuildingGarrisonDialogActions) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE),
        *(_DWORD *)widget,
        *(_DWORD *)(widget + 4),
        *(_DWORD *)(widget + 32));
    }
    if ( g_QueenMarriageProposalWidgetTableBase
      && widget >= g_QueenMarriageProposalWidgetTableBase
      && widget < g_QueenMarriageProposalWidgetTableBase + 2 * 53 )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_action",
        (int)((widget - g_QueenMarriageProposalWidgetTableBase) / 53),
        *(_DWORD *)widget,
        *(_DWORD *)(widget + 4),
        *(_DWORD *)(widget + 32));
    }
    UI_InvokeWidgetActionCallback(widget);
    if ( (*(_BYTE *)(widget + 8) & 1) != 0 )
      resultState = 3;
    if ( (*(_BYTE *)(widget + 8) & 2) != 0 )
    {
      resultState = 4;
LABEL_18:
      UI_InvokeWidgetTransitionCallback(widget, 1);
      return resultState;
    }
    goto LABEL_34;
  }
  if ( (*(_BYTE *)(widget + 8) & 4) == 0 )
  {
    localizedStringBase = widget + 4 * (unsigned __int8)g_LanguageIndex;
    if ( *(_DWORD *)(localizedStringBase + 36) && *(_BYTE *)(widget + 48) == 1 )
      Tooltip_ShowText(3, (char *)Compat_WidgetPackedString(widget, 36 + 4 * (unsigned __int8)g_LanguageIndex), v10);
    resultState = 2;
    *(_BYTE *)(widget + 8) |= 4u;
    goto LABEL_23;
  }
LABEL_34:
  if ( resultState == 3 )
    goto LABEL_18;
  return resultState;
}
// 419CA2: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419D3F: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419D48: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419CE5: variable 'v10' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00419D60) --------------------------------------------------------
int  UIWidget_RefreshActionButtonState(uintptr_t result, int callbackArg)
{
  if ( result == (uintptr_t)g_WorldMapActionButtonWidgetTable
    || result == (uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3) )
  {
    WorldMap_EnsureActionButtonWidgetTable();
  }
  if ( UnitBattle_IsActionButtonWidgetAddress(result) )
    UnitBattle_EnsureActionButtonWidgetTable();
  if ( *(int *)result < 640 )
    return UI_InvokeWidgetTransitionCallback(result, callbackArg);
  return (int)result;
}

//----- (00419D80) --------------------------------------------------------
_DWORD * UIWidgetTable_InitDrawStates(_DWORD *result)
{
  unsigned char *widget;

  if ( (uintptr_t)result == (uintptr_t)g_WorldMapActionButtonWidgetTable )
    WorldMap_EnsureActionButtonWidgetTable();
  if ( (uintptr_t)result == (uintptr_t)g_UnitBattleActionWidgetTable )
    UnitBattle_EnsureActionButtonWidgetTable();
  widget = (unsigned char *)result;
  if ( *(_DWORD *)widget == -1 )
    return result;
  do
  {
    while ( *(int *)widget >= 640 )
    {
      widget += 53;
      if ( *(_DWORD *)widget == -1 )
        return result;
    }
    UI_InvokeWidgetTransitionCallback((uintptr_t)widget, 0);
    widget += 53;
  }
  while ( *(_DWORD *)widget != -1 );
  return result;
}

//----- (00419DC0) --------------------------------------------------------
signed int  UIWidgetTable_PollHoverAndActions(_DWORD *widgetTable, DWORD allocContext)
{
  uintptr_t widget; // edx
  int has_tooltip; // ebx
  signed int result; // ecx
  signed int widget_result; // eax

  if ( (uintptr_t)widgetTable == (uintptr_t)g_WorldMapActionButtonWidgetTable )
    WorldMap_EnsureActionButtonWidgetTable();
  if ( (uintptr_t)widgetTable == (uintptr_t)g_UnitBattleActionWidgetTable )
    UnitBattle_EnsureActionButtonWidgetTable();
  widget = (uintptr_t)widgetTable;
  has_tooltip = 0;
  result = 0;
  if ( *widgetTable != -1 )
  {
    do
    {
      widget_result = UIWidget_PollHitHoverAndClick(widget, allocContext);
      if ( widget_result > result )
        result = widget_result;
      if ( (*(_BYTE *)(widget + 8) & 4) != 0 )
        has_tooltip = 1;
      widget += 53;
    }
    while ( *(_DWORD *)widget != -1 );
  }
  if ( !g_TooltipCursorActive && has_tooltip )
  {
    g_SavedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
    g_TooltipCursorActive = 1;
    return result;
  }
  if ( !g_TooltipCursorActive || has_tooltip )
    return result;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_SavedCursorDescriptor);
  g_TooltipCursorActive = 0;
  return result;
}
// 419DDB: variable 'v4' is possibly undefined
// 419DDF: variable 'v6' is possibly undefined
// 419E53: variable 'v9' is possibly undefined
// 526A24: using guessed type int dword_526A24;
// 526A34: using guessed type int dword_526A34;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D14: using guessed type int dword_544D14;
// 545150: using guessed type int dword_545150;

//----- (00419E60) --------------------------------------------------------
int  UIWidget_PlayPressedReleaseAnimationWithDelay(uintptr_t widget, int a2)
{
  unsigned int deadline; // ecx

  (void)a2;
  if ( *(_DWORD *)(widget + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(widget, 49));
  *(_DWORD *)(widget + 8) = 6;
  UIWidget_RefreshActionButtonState(widget, 1);
  deadline = Time_Now(0, 0) + 20;
  while ( Time_Now(0, 0) < deadline )
    DD_Pump((int)(intptr_t)g_RenderState, 0);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  *(_DWORD *)(widget + 8) = 5;
  return UIWidget_RefreshActionButtonState(widget, 1);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00419ED0) --------------------------------------------------------
int  UIWidget_PlayPressedReleaseAnimation(uintptr_t widget)
{
  if ( *(_DWORD *)(widget + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(widget, 49));
  *(_DWORD *)(widget + 8) = 6;
  UIWidget_RefreshActionButtonState(widget, 1);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  *(_DWORD *)(widget + 8) = 5;
  return UIWidget_RefreshActionButtonState(widget, 1);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00419F20) --------------------------------------------------------
int  UIWidget_ShowPressedState(uintptr_t widget)
{
  if ( *(_DWORD *)(widget + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(widget, 49));
  *(_DWORD *)(widget + 8) = 6;
  return UIWidget_RefreshActionButtonState(widget, 1);
}

//----- (00419F50) --------------------------------------------------------
int  UIWidget_ShowReleasedState(uintptr_t widget, int a2)
{
  (void)a2;
  *(_DWORD *)(widget + 8) = 5;
  return UIWidget_RefreshActionButtonState(widget, 1);
}

//----- (00419F70) --------------------------------------------------------
int  UI_DrawUnitInfoPane(
        int panelLeftArg,
        int panelTopArg,
        int a3,
        __int16 *slotRecordArg,
        DWORD allocContext,
        int drawContext)
{
  int v6; // edi
  _DWORD *spriteSet; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int sideIndex; // edx
  int SpriteForChar; // eax
  DWORD v13; // ebp
  int v14; // ecx
  _DWORD *Surface; // esi
  __int16 spriteWidth; // bx
  __int16 SpriteHeight; // ax
  int healthBarSpriteFrame; // eax
  __int16 v19; // ax
  int textRight; // esi
  int rankSpriteIndex; // edx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  unsigned __int8 orderStateFlags; // al
  int orderSpriteIndex; // edx
  int v28; // eax
  int chevronTop; // esi
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // eax
  int unitType; // eax
  int displayedStat;
  unsigned __int16 specialSpriteIndex; // cx
  unsigned __int16 v36; // si
  int iconTop; // ebx
  int v38; // ecx
  int v39; // eax
  unsigned __int16 healthBarFillRight; // [esp+64h] [ebp-40h]
  _DWORD *v42; // [esp+70h] [ebp-34h] BYREF
  int textLeft; // [esp+74h] [ebp-30h]
  int panelTop; // [esp+78h] [ebp-2Ch]
  int v45 CLASH95_UNUSED; // [esp+7Ch] [ebp-28h]
  DWORD v46; // [esp+80h] [ebp-24h]
  void *savedRenderDevice; // [esp+84h] [ebp-20h]
  int statLineBottom; // [esp+88h] [ebp-1Ch]
  const UnitTypeRuntimeCoreMetadataRecord *unitMetadata; // [esp+8Ch] [ebp-18h]
  int panelLeft; // [esp+90h] [ebp-14h]
  __int16 *slotRecord; // [esp+94h] [ebp-10h]

  v6 = drawContext;
  panelLeft = panelLeftArg;
  panelTop = panelTopArg;
  slotRecord = slotRecordArg;
  unitType = UNIT_SLOT_TYPE(slotRecordArg);
  unitMetadata = &g_UnitTypeRuntimeCoreMetadata[unitType];
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a3, (char)(intptr_t)slotRecordArg, allocContext);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)(intptr_t)slotRecordArg);
  v42 = spriteSet;
  Render_ReleaseSurface(7, allocContext);
  if ( *(unsigned __int8 *)(uintptr_t)(v9 + 2) == g_CurrentPlayerIndex )
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)(intptr_t)v42, 0, v8, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
    v10 = (int)(intptr_t)v42;
    sideIndex = 0;
  }
  else
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)(intptr_t)v42, 1, v8, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
    sideIndex = 1;
    v10 = (int)(intptr_t)v42;
  }
  SpriteForChar = DLX_GetSpriteForChar(v10, sideIndex);
  v13 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(uintptr_t)(v13 + 52))(
    panelTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    0);
  if ( *((char *)slotRecord + 9) < 100 )
  {
    savedRenderDevice = g_RenderDevice;
    Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v14, panelLeft, v13);
    if ( Surface )
    {
      spriteWidth = DLX_GetSpriteWidth((int)(intptr_t)v42, 2u) + 1;
      SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)v42, 2u);
      Surface = Render_CreateSurface((int)(intptr_t)Surface, SpriteHeight + 1, spriteWidth);
    }
    g_RenderDevice = Surface;
    healthBarSpriteFrame = DLX_GetSpriteForChar((int)(intptr_t)v42, 2);
    v13 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(v13 + 52))(
      0,
      healthBarSpriteFrame,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    g_RenderDevice = savedRenderDevice;
    healthBarFillRight = 106 * (100 - *((char *)slotRecord + 9)) / 100 + 5;
    v19 = DLX_GetSpriteHeight((int)(intptr_t)v42, 2u);
    Render_FillRect(Surface, g_RenderDevice, 5, 0, v19 - 1, healthBarFillRight, panelLeft + 42, panelTop + 5);
    if ( Surface )
      (*(void (**)(void))(uintptr_t)Surface[46])();
  }
  UI_DrawTextFmt(drawContext, panelLeft + 64, panelLeft + 192, panelTop + 5, 3, UnitType_GetLocalizedName((unit_type)unitType));
  if ( *((unsigned __int8 *)slotRecord + 2) == g_CurrentPlayerIndex )
  {
    statLineBottom = panelTop + 95;
    textLeft = panelLeft + 85;
    textRight = panelLeft + 105;
    if ( unitMetadata->base_shot_power )
    {
      if ( unitMetadata->base_melee_attack )
      {
        displayedStat = UI_IconIndexFromStats(slotRecord);
        UI_DrawTextFmt(drawContext, textLeft, textRight, panelTop + 74, 2, aD_12, displayedStat);
        displayedStat = Unit_GetBaseC(slotRecord);
        v13 = statLineBottom;
        UI_DrawTextFmt(drawContext, textLeft, textRight, statLineBottom, 2, aD_13, displayedStat);
      }
      else
      {
        DLX_GetSpriteForChar((int)(intptr_t)v42, 10);
        v46 = *((_DWORD *)g_RenderDevice + 46);
        v13 = v46;
        (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(v46 + 52))(-1, -1, -1, -1, 1, 0, 0);
        displayedStat = Unit_GetBaseC(slotRecord);
        UI_DrawTextFmt(drawContext, textLeft, textRight, statLineBottom, 2, aD_2, displayedStat);
      }
    }
    else
    {
      DLX_GetSpriteForChar((int)(intptr_t)v42, 9);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      displayedStat = UI_IconIndexFromStats(slotRecord);
      v13 = statLineBottom;
      UI_DrawTextFmt(drawContext, textLeft, textRight, statLineBottom, 2, aD_1, displayedStat);
    }
    UI_DrawTextFmt(drawContext, panelLeft + 85, panelLeft + 105, panelTop + 50, 2, aD_14, ((unsigned char *)slotRecord)[8]);
    if ( (unsigned int)((signed char *)slotRecord)[11] > 4 )
    {
      v32 = *((char *)slotRecord + 11);
      if ( v32 < 11 || v32 > 15 )
      {
        v33 = *((char *)slotRecord + 11);
        if ( v33 < 16 || v33 > 20 )
          goto LABEL_19;
        rankSpriteIndex = 3;
      }
      else
      {
        rankSpriteIndex = 4;
      }
    }
    else
    {
      rankSpriteIndex = 5;
    }
    v23 = DLX_GetSpriteForChar((int)(intptr_t)v42, rankSpriteIndex);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      panelTop + 21,
      v23,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
LABEL_19:
    if ( *((char *)slotRecord + 11) >= 1 )
      v24 = 7;
    else
      v24 = 13;
    Render_ReleaseSurface(v24, v13);
    UI_DrawTextFmt(drawContext, panelLeft + 132, panelLeft + 148, panelTop + 50, 2, aD_15, ((signed char *)slotRecord)[11]);
    if ( *((char *)slotRecord + 10) <= 90 )
      v25 = 7;
    else
      v25 = 13;
    Render_ReleaseSurface(v25, v13);
    UI_DrawTextFmt(drawContext, panelLeft + 160, panelLeft + 191, panelTop + 50, 2, aD_16, ((signed char *)slotRecord)[10]);
    Render_ReleaseSurface(7, v13);
    displayedStat = Unit_CalcIndexB(slotRecord);
    UI_DrawTextFmt(drawContext, panelLeft + 132, panelLeft + 148, panelTop + 95, 2, aD_17, displayedStat);
    orderStateFlags = slotRecord[6] & 3;
    if ( orderStateFlags )
    {
      if ( orderStateFlags <= 1u )
      {
        orderSpriteIndex = 7;
      }
      else
      {
        if ( orderStateFlags != 3 )
        {
LABEL_26:
          v6 = 0;
          chevronTop = panelTop + 71;
          v45 = panelLeft + 178;
          while ( v6 <= (unsigned __int8)(16 * *((_BYTE *)slotRecord + 12)) >> 6 )
          {
            v30 = DLX_GetSpriteForChar((int)(intptr_t)v42, 14);
            v31 = chevronTop;
            v13 = *((_DWORD *)g_RenderDevice + 46);
            ++v6;
            chevronTop += 10;
            (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(v13 + 52))(
              v31,
              v30,
              -1,
              -1,
              -1,
              -1,
              1,
              0,
              0);
          }
          goto LABEL_47;
        }
        orderSpriteIndex = 8;
      }
    }
    else
    {
      orderSpriteIndex = 6;
    }
    v28 = DLX_GetSpriteForChar((int)(intptr_t)v42, orderSpriteIndex);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      panelTop + 65,
      v28,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    goto LABEL_26;
  }
LABEL_47:
  unitType = *slotRecord;
  if ( unitType == UNIT_TYPE_FORESTER )
  {
    specialSpriteIndex = 11;
  }
  else if ( unitType == UNIT_TYPE_GORAL )
  {
    specialSpriteIndex = 12;
  }
  else
  {
    if ( (unitMetadata->flags & 1) == 0 )
      goto LABEL_50;
    specialSpriteIndex = 13;
  }
  v36 = specialSpriteIndex;
  iconTop = (33 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)v42, specialSpriteIndex)) / 2 + 76 + panelTop;
  v6 = (34 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)v42, v36)) / 2 + 8 + panelLeft;
  v39 = DLX_GetSpriteForChar((int)(intptr_t)v42, v38);
  v13 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(v13 + 52))(
    iconTop,
    v39,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
LABEL_50:
  Render_ReleaseSurface(7, v13);
  UI_DrawTextFmt(v6, panelLeft + 41, panelLeft + 70, panelTop + 98, 3, aD_18, ((signed char *)slotRecord)[9]);
  Render_ReleaseSurface(7, v13);
  return DLXSpriteSet_ReleaseAndClear((int *)&v42);
}
// 41A23D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 419FBC: variable 'v9' is possibly undefined
// 419FCD: variable 'v8' is possibly undefined
// 41A031: variable 'v14' is possibly undefined
// 41A5E6: variable 'v38' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041A690) --------------------------------------------------------
int  Unit_Info(
        int leftArg,
        int topArg,
        int iconSpriteIndex,
        unsigned __int8 *unitRecord,
        DWORD allocContext,
        DWORD drawContext)
{
  int v8; // ecx
  int unitType; // eax
  char ownerIndex; // bl
  int v11; // ecx
  _DWORD *unitSpriteSet; // eax
  int v13; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int animSpriteTop; // ebp
  int animFrameIndex; // esi
  int v18; // ecx
  int v19; // ecx
  unsigned int currentTick; // eax
  unsigned int v21; // edx
  int v22; // ecx
  int animSprite; // eax
  int v25; // ecx
  char infoBuffer[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *spriteSet; // [esp+64h] [ebp-28h] BYREF
  int screenTop; // [esp+68h] [ebp-24h]
  int renderSpriteObj; // [esp+6Ch] [ebp-20h]
  _DWORD *surface; // [esp+70h] [ebp-1Ch]
  int screenLeft; // [esp+74h] [ebp-18h]
  int animSpriteLeft CLASH95_UNUSED; // [esp+78h] [ebp-14h]
  int lastAnimTick; // [esp+7Ch] [ebp-10h]

  screenLeft = leftArg;
  screenTop = topArg;
  Debug_Log(topArg, (char)(intptr_t)unitRecord, allocContext, (int)(intptr_t)aUnit_infoDD0x0);
  unitType = UNIT_STACK_TILE_ROW(unitRecord);
  if ( unitType == UNIT_TYPE_PEASANT_CARGO
    || unitType == UNIT_TYPE_GOLD_CARGO
    || unitType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
    || unitType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    return UI_DrawSpecialUnitInfoPane(screenLeft, screenTop, v8, unitRecord, allocContext, iconSpriteIndex);
  ownerIndex = unitRecord[2];
  UI_BeginUnitInfo(infoBuffer, *unitRecord, ownerIndex);
  unitSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v11, ownerIndex, allocContext);
  if ( unitSpriteSet )
    unitSpriteSet = DLXSpriteSet_Load(unitSpriteSet, ownerIndex);
  spriteSet = unitSpriteSet;
  if ( drawContext )
  {
    ownerIndex = g_MapPalettePtr;
    DLXSpriteSet_DrawText((int)(intptr_t)unitSpriteSet, 0, drawContext, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr);
  }
  Render_Pump();
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v13, ownerIndex, drawContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, 201, 116);
  surface = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)screenTop, (unsigned __int16)screenLeft, screenLeft + 200, screenTop + 115, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  UI_DrawUnitInfoPane(screenLeft, screenTop, drawContext, (__int16 *)unitRecord, drawContext, iconSpriteIndex);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, 0);
  animSpriteTop = screenTop + 5;
  renderSpriteObj = *((_DWORD *)g_RenderDevice + 46);
  animSpriteLeft = screenLeft + 11;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderSpriteObj + 52))(
    screenTop + 5,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  animFrameIndex = 0;
  g_RenderDevice = &g_MainRenderDevice;
  lastAnimTick = Time_Now(v18, (int)(intptr_t)&g_MainRenderDevice);
  while ( DD_IsLost((int)(intptr_t)g_RenderState) || DD_IsFlipping((int)(intptr_t)g_RenderState) )
  {
    DD_Pump((int)(intptr_t)g_RenderState, drawContext);
    if ( !drawContext )
    {
      currentTick = Time_Now(v19, lastAnimTick + 10);
      if ( v21 < currentTick )
      {
        lastAnimTick = Time_Now(v22, v21);
        animFrameIndex = (animFrameIndex + 1) % 8;
        animSprite = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, animFrameIndex);
        renderSpriteObj = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderSpriteObj + 52))(
          animSpriteTop,
          animSprite,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
    }
  }
  Render_FillRect(surface, 0, 0, 0, 0xC8u, 0x73u, screenLeft, screenTop);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( v25 )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)v25, 2);
  return DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
}
// 41A6FD: variable 'v11' is possibly undefined
// 41A73A: variable 'v13' is possibly undefined
// 41A817: variable 'v18' is possibly undefined
// 41A850: variable 'v19' is possibly undefined
// 41A857: variable 'v21' is possibly undefined
// 41A859: variable 'v22' is possibly undefined
// 41A8C1: variable 'v8' is possibly undefined
// 41A91B: variable 'v25' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];
