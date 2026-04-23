#include "platform_sdl.h"

#define SDL_MAIN_HANDLED
#define SDL_Window SDL2_Window
#define SDL_Renderer SDL2_Renderer
#define SDL_Texture SDL2_Texture
#define SDL_Surface SDL2_Surface
#define SDL_Palette SDL2_Palette
#define SDL_Cursor SDL2_Cursor
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#undef SDL_Window
#undef SDL_Renderer
#undef SDL_Texture
#undef SDL_Surface
#undef SDL_Palette
#undef SDL_Cursor

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * Minimal SDL-target runtime seam for the recovered platform layer.
 *
 * The decompiled core still calls Win32-style window/message/timing helpers.
 * These placeholders keep the compile target moving toward SDL by owning the
 * window/message abstractions locally instead of depending on Win32 headers or
 * import libraries. They are intentionally narrow and conservative.
 */

struct SDL_Window {
  int x;
  int y;
  int width;
  int height;
  int visible;
  DWORD style;
  const char *class_name;
  const char *title;
  SDL2_Window *host_window;
  struct SDL_Surface *device_context;
};

struct SDL_Renderer {
  int unused;
};

struct SDL_Texture {
  int unused;
};

struct SDL_Surface {
  int width;
  int height;
  const char *resource_name;
  COLORREF key_pixel;
  struct SDL_Window *owner_window;
};

struct SDL_Palette {
  int version;
};

struct SDL_Cursor {
  int cursor_id;
};

static struct SDL_Surface g_platform_default_surface;
static int g_platform_frame_dump_checked;
static const char *g_platform_frame_dump_prefix;
static int g_platform_frame_present_index;
static int g_platform_frame_dump_index;
static int g_platform_frame_dump_skip;
static int g_platform_frame_dump_limit;
static HWND g_platform_foreground_window;

#define PLATFORM_PRESENTED_FRAME_DUMP_DEFAULT_LIMIT 512

int Compat_AllocLow32Bytes(int size);
void Compat_FreeLow32Bytes(int ptr);

typedef struct CompatDirectDraw CompatDirectDraw;
typedef struct CompatDirectDrawPalette CompatDirectDrawPalette;
typedef struct CompatDirectDrawSurface CompatDirectDrawSurface;
typedef struct CompatDirectDrawClipper CompatDirectDrawClipper;

typedef struct CompatDirectDrawVTable {
  HRESULT (__stdcall *QueryInterface)(CompatDirectDraw *self, const void *riid, void *out_object);
  ULONG (__stdcall *AddRef)(CompatDirectDraw *self);
  ULONG (__stdcall *Release)(CompatDirectDraw *self);
  HRESULT (__stdcall *Compact)(CompatDirectDraw *self);
  HRESULT (__stdcall *CreateClipper)(CompatDirectDraw *self, DWORD flags, void *out_clipper, IUnknown *outer);
  HRESULT (__stdcall *CreatePalette)(CompatDirectDraw *self, DWORD flags, void *entries, void *out_palette, IUnknown *outer);
  HRESULT (__stdcall *CreateSurface)(CompatDirectDraw *self, int *desc, void *out_surface, IUnknown *outer);
  HRESULT (__stdcall *DuplicateSurface)(CompatDirectDraw *self, void *source, void *out_surface);
  HRESULT (__stdcall *EnumDisplayModes)(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback);
  HRESULT (__stdcall *EnumSurfaces)(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback);
  HRESULT (__stdcall *FlipToGDISurface)(CompatDirectDraw *self);
  HRESULT (__stdcall *GetCaps)(CompatDirectDraw *self, void *driver_caps, void *hel_caps);
  HRESULT (__stdcall *GetDisplayMode)(CompatDirectDraw *self, int *desc);
  HRESULT (__stdcall *GetFourCCCodes)(CompatDirectDraw *self, void *count, void *codes);
  HRESULT (__stdcall *GetGDISurface)(CompatDirectDraw *self, void *out_surface);
  HRESULT (__stdcall *GetMonitorFrequency)(CompatDirectDraw *self, DWORD *frequency);
  HRESULT (__stdcall *GetScanLine)(CompatDirectDraw *self, DWORD *scanline);
  HRESULT (__stdcall *GetVerticalBlankStatus)(CompatDirectDraw *self, BOOL *in_vblank);
  HRESULT (__stdcall *Initialize)(CompatDirectDraw *self, GUID *guid);
  HRESULT (__stdcall *RestoreDisplayMode)(CompatDirectDraw *self);
  HRESULT (__stdcall *SetCooperativeLevel)(CompatDirectDraw *self, HWND hwnd, DWORD flags);
  HRESULT (__stdcall *SetDisplayMode)(CompatDirectDraw *self, int width, int height, int bpp, int refresh_rate, int flags);
  HRESULT (__stdcall *WaitForVerticalBlank)(CompatDirectDraw *self, DWORD flags, HANDLE event_handle);
} CompatDirectDrawVTable;

typedef struct CompatDirectDrawSurfaceVTable {
  HRESULT (__stdcall *QueryInterface)(CompatDirectDrawSurface *self, const void *riid, void *out_object);
  ULONG (__stdcall *AddRef)(CompatDirectDrawSurface *self);
  ULONG (__stdcall *Release)(CompatDirectDrawSurface *self);
  HRESULT (__stdcall *AddAttachedSurface)(CompatDirectDrawSurface *self, void *attached_surface);
  HRESULT (__stdcall *AddOverlayDirtyRect)(CompatDirectDrawSurface *self, const RECT *dirty_rect);
  HRESULT (__stdcall *Blt)(CompatDirectDrawSurface *self, RECT *dest_rect, void *src_surface, RECT *src_rect, DWORD flags, void *blt_fx);
  HRESULT (__stdcall *BltBatch)(CompatDirectDrawSurface *self, void *batch, DWORD count, DWORD flags);
  HRESULT (__stdcall *BltFast)(CompatDirectDrawSurface *self, int x, int y, void *src_surface, RECT *src_rect, DWORD flags);
  HRESULT (__stdcall *DeleteAttachedSurface)(CompatDirectDrawSurface *self, DWORD flags, void *attached_surface);
  HRESULT (__stdcall *EnumAttachedSurfaces)(CompatDirectDrawSurface *self, void *ctx, void *callback);
  HRESULT (__stdcall *EnumOverlayZOrders)(CompatDirectDrawSurface *self, DWORD flags, void *ctx, void *callback);
  HRESULT (__stdcall *Flip)(CompatDirectDrawSurface *self, void *target_override, DWORD flags);
  HRESULT (__stdcall *GetAttachedSurface)(CompatDirectDrawSurface *self, void *caps, void *out_surface);
  HRESULT (__stdcall *GetBltStatus)(CompatDirectDrawSurface *self, DWORD flags);
  HRESULT (__stdcall *GetCaps)(CompatDirectDrawSurface *self, void *caps);
  HRESULT (__stdcall *GetClipper)(CompatDirectDrawSurface *self, void *out_clipper);
  HRESULT (__stdcall *GetColorKey)(CompatDirectDrawSurface *self, DWORD flags, void *color_key);
  HRESULT (__stdcall *GetDC)(CompatDirectDrawSurface *self, void *out_dc);
  HRESULT (__stdcall *GetFlipStatus)(CompatDirectDrawSurface *self, DWORD flags);
  HRESULT (__stdcall *GetOverlayPosition)(CompatDirectDrawSurface *self, LONG *x, LONG *y);
  HRESULT (__stdcall *GetPalette)(CompatDirectDrawSurface *self, void *out_palette);
  HRESULT (__stdcall *GetPixelFormat)(CompatDirectDrawSurface *self, void *pixel_format);
  HRESULT (__stdcall *GetSurfaceDesc)(CompatDirectDrawSurface *self, int *desc);
  HRESULT (__stdcall *Initialize)(CompatDirectDrawSurface *self, CompatDirectDraw *owner, int *desc);
  HRESULT (__stdcall *IsLost)(CompatDirectDrawSurface *self);
  HRESULT (__stdcall *Lock)(CompatDirectDrawSurface *self, RECT *rect, int *desc, DWORD flags, HANDLE event_handle);
  HRESULT (__stdcall *ReleaseDC)(CompatDirectDrawSurface *self, HDC dc);
  HRESULT (__stdcall *Restore)(CompatDirectDrawSurface *self);
  HRESULT (__stdcall *SetClipper)(CompatDirectDrawSurface *self, void *clipper);
  HRESULT (__stdcall *SetColorKey)(CompatDirectDrawSurface *self, DWORD flags, void *color_key);
  HRESULT (__stdcall *SetOverlayPosition)(CompatDirectDrawSurface *self, LONG x, LONG y);
  HRESULT (__stdcall *SetPalette)(CompatDirectDrawSurface *self, void *palette);
  HRESULT (__stdcall *Unlock)(CompatDirectDrawSurface *self, void *lock_ptr);
  HRESULT (__stdcall *UpdateOverlay)(CompatDirectDrawSurface *self, RECT *src_rect, void *dest_surface, RECT *dest_rect, DWORD flags, void *overlay_fx);
  HRESULT (__stdcall *UpdateOverlayDisplay)(CompatDirectDrawSurface *self, DWORD flags);
  HRESULT (__stdcall *UpdateOverlayZOrder)(CompatDirectDrawSurface *self, DWORD flags, void *reference_surface);
} CompatDirectDrawSurfaceVTable;

typedef struct CompatDirectDrawPaletteVTable {
  HRESULT (__stdcall *QueryInterface)(CompatDirectDrawPalette *self, const void *riid, void *out_object);
  ULONG (__stdcall *AddRef)(CompatDirectDrawPalette *self);
  ULONG (__stdcall *Release)(CompatDirectDrawPalette *self);
  HRESULT (__stdcall *GetCaps)(CompatDirectDrawPalette *self, DWORD *caps);
  HRESULT (__stdcall *GetEntries)(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries);
  HRESULT (__stdcall *Initialize)(CompatDirectDrawPalette *self, CompatDirectDraw *owner, DWORD flags, void *entries);
  HRESULT (__stdcall *SetEntries)(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries);
} CompatDirectDrawPaletteVTable;

typedef struct CompatDirectDrawClipperVTable {
  HRESULT (__stdcall *QueryInterface)(CompatDirectDrawClipper *self, const void *riid, void *out_object);
  ULONG (__stdcall *AddRef)(CompatDirectDrawClipper *self);
  ULONG (__stdcall *Release)(CompatDirectDrawClipper *self);
  HRESULT (__stdcall *GetClipList)(CompatDirectDrawClipper *self, RECT *clip_rect, void *clip_list, DWORD *size);
  HRESULT (__stdcall *GetHWnd)(CompatDirectDrawClipper *self, HWND *hwnd);
  HRESULT (__stdcall *Initialize)(CompatDirectDrawClipper *self, CompatDirectDraw *owner, DWORD flags);
  HRESULT (__stdcall *IsClipListChanged)(CompatDirectDrawClipper *self, BOOL *changed);
  HRESULT (__stdcall *SetClipList)(CompatDirectDrawClipper *self, void *clip_list, DWORD flags);
  HRESULT (__stdcall *SetHWnd)(CompatDirectDrawClipper *self, DWORD flags, HWND hwnd);
} CompatDirectDrawClipperVTable;

struct CompatDirectDraw {
  CompatDirectDrawVTable *lpVtbl;
  ULONG ref_count;
  HWND cooperative_window;
  DWORD cooperative_flags;
  int width;
  int height;
  int bpp;
  CompatDirectDrawSurface *primary_surface;
};

struct CompatDirectDrawSurface {
  CompatDirectDrawSurfaceVTable *lpVtbl;
  ULONG ref_count;
  CompatDirectDraw *owner;
  struct SDL_Surface surface;
  DWORD caps;
  int width;
  int height;
  int bpp;
  void *clipper;
  void *palette;
  CompatDirectDrawSurface *attached_surface;
  int pitch;
  void *pixels;
  int lost;
  DWORD color_key_low;
  DWORD color_key_high;
  int has_color_key;
};

typedef struct CompatPaletteEntry {
  BYTE red;
  BYTE green;
  BYTE blue;
  BYTE flags;
} CompatPaletteEntry;

struct CompatDirectDrawPalette {
  CompatDirectDrawPaletteVTable *lpVtbl;
  ULONG ref_count;
  CompatDirectDraw *owner;
  DWORD flags;
  CompatPaletteEntry entries[256];
};

struct CompatDirectDrawClipper {
  CompatDirectDrawClipperVTable *lpVtbl;
  ULONG ref_count;
  HWND hwnd;
};

static void *PlatformAllocLow32(size_t size)
{
  int ptr_value;

  if ( !size || size > 0x7fffffffU )
    return 0;
  ptr_value = Compat_AllocLow32Bytes((int)size);
  if ( !ptr_value )
    return 0;
  return (void *)(uintptr_t)(unsigned int)ptr_value;
}

static void PlatformFreeLow32(void *ptr)
{
  if ( ptr )
    Compat_FreeLow32Bytes((int)(uintptr_t)ptr);
}

static int CompatSurfaceBytesPerPixel(const CompatDirectDrawSurface *surface)
{
  if ( !surface || surface->bpp <= 8 )
    return 1;
  return (surface->bpp + 7) >> 3;
}

static HRESULT CompatDirectDrawSurfaceEnsurePixels(CompatDirectDrawSurface *surface)
{
  size_t pixel_bytes;

  if ( !surface )
    return (HRESULT)0x80070057;
  if ( surface->pitch <= 0 )
    surface->pitch = surface->width * CompatSurfaceBytesPerPixel(surface);
  if ( surface->pixels )
    return 0;
  pixel_bytes = (size_t)surface->pitch * (size_t)surface->height;
  surface->pixels = PlatformAllocLow32(pixel_bytes);
  if ( !surface->pixels )
    return (HRESULT)0x8007000E;
  memset(surface->pixels, 0, pixel_bytes);
  return 0;
}

static Uint32 *PlatformConvertSurfacePixelsToArgb32(const CompatDirectDrawSurface *surface, int *out_pitch)
{
  const unsigned char *src_base;
  const CompatDirectDrawPalette *palette;
  Uint32 *pixels;
  int dst_pitch;
  int y;
  int x;

  if ( !surface || !surface->pixels || surface->width <= 0 || surface->height <= 0 || surface->pitch <= 0 )
    return 0;
  dst_pitch = surface->width * (int)sizeof(*pixels);
  pixels = (Uint32 *)malloc((size_t)dst_pitch * (size_t)surface->height);
  if ( !pixels )
    return 0;
  src_base = (const unsigned char *)surface->pixels;
  palette = (const CompatDirectDrawPalette *)surface->palette;
  for ( y = 0; y < surface->height; ++y )
  {
    const unsigned char *src_row;
    Uint32 *dst_row;

    src_row = src_base + (size_t)y * (size_t)surface->pitch;
    dst_row = (Uint32 *)((unsigned char *)pixels + (size_t)y * (size_t)dst_pitch);
    for ( x = 0; x < surface->width; ++x )
    {
      if ( surface->bpp <= 8 )
      {
        unsigned char index;

        index = src_row[x];
        if ( palette )
        {
          const CompatPaletteEntry *entry;

          entry = &palette->entries[index];
          dst_row[x] = 0xFF000000u | ((Uint32)entry->red << 16) | ((Uint32)entry->green << 8) | (Uint32)entry->blue;
        }
        else
        {
          Uint32 value;

          value = index;
          dst_row[x] = 0xFF000000u | (value << 16) | (value << 8) | value;
        }
      }
      else if ( surface->bpp <= 16 )
      {
        unsigned short pixel16;
        Uint32 red;
        Uint32 green;
        Uint32 blue;

        pixel16 = ((const unsigned short *)src_row)[x];
        red = (Uint32)((pixel16 >> 11) & 0x1Fu);
        green = (Uint32)((pixel16 >> 5) & 0x3Fu);
        blue = (Uint32)(pixel16 & 0x1Fu);
        dst_row[x] = 0xFF000000u
                   | ((red * 255u / 31u) << 16)
                   | ((green * 255u / 63u) << 8)
                   | (blue * 255u / 31u);
      }
      else if ( surface->bpp <= 24 )
      {
        const unsigned char *src_pixel;

        src_pixel = src_row + x * 3;
        dst_row[x] = 0xFF000000u | ((Uint32)src_pixel[2] << 16) | ((Uint32)src_pixel[1] << 8) | (Uint32)src_pixel[0];
      }
      else
      {
        const unsigned char *src_pixel;
        Uint32 alpha;

        src_pixel = src_row + x * 4;
        alpha = src_pixel[3] ? (Uint32)src_pixel[3] : 0xFFu;
        dst_row[x] = (alpha << 24) | ((Uint32)src_pixel[2] << 16) | ((Uint32)src_pixel[1] << 8) | (Uint32)src_pixel[0];
      }
    }
  }
  if ( out_pitch )
    *out_pitch = dst_pitch;
  return pixels;
}

static Uint32 CompatPaletteIndexToArgb32(const CompatDirectDrawSurface *surface, unsigned char index)
{
  const CompatDirectDrawPalette *palette;

  palette = (const CompatDirectDrawPalette *)surface->palette;
  if ( palette )
  {
    const CompatPaletteEntry *entry;

    entry = &palette->entries[index];
    return 0xFF000000u | ((Uint32)entry->red << 16) | ((Uint32)entry->green << 8) | (Uint32)entry->blue;
  }
  return 0xFF000000u | ((Uint32)index << 16) | ((Uint32)index << 8) | (Uint32)index;
}

static unsigned short CompatPaletteIndexToRgb565(const CompatDirectDrawSurface *surface, unsigned char index)
{
  Uint32 pixel32;
  Uint32 red;
  Uint32 green;
  Uint32 blue;

  pixel32 = CompatPaletteIndexToArgb32(surface, index);
  red = (pixel32 >> 16) & 0xFFu;
  green = (pixel32 >> 8) & 0xFFu;
  blue = pixel32 & 0xFFu;
  return (unsigned short)(((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3));
}

static Uint32 CompatSurfaceReadPixelValue(const CompatDirectDrawSurface *surface, const unsigned char *src_pixel)
{
  int src_bpp;

  src_bpp = CompatSurfaceBytesPerPixel(surface);
  if ( src_bpp <= 1 )
    return src_pixel[0];
  if ( src_bpp == 2 )
    return ((const unsigned short *)src_pixel)[0];
  if ( src_bpp == 3 )
    return (Uint32)src_pixel[0] | ((Uint32)src_pixel[1] << 8) | ((Uint32)src_pixel[2] << 16);
  return ((const Uint32 *)src_pixel)[0];
}

static int PlatformReadNonNegativeIntEnv(const char *name, int fallback)
{
  const char *value;
  char *end;
  long parsed;

  value = getenv(name);
  if ( !value || !*value )
    return fallback;
  parsed = strtol(value, &end, 10);
  if ( end == value || *end || parsed < 0 || parsed > INT_MAX )
    return fallback;
  return (int)parsed;
}

static void PlatformMaybeDumpPresentedFrame(SDL2_Surface *surface)
{
  char frame_path[1024];
  int current_present_index;

  if ( !g_platform_frame_dump_checked )
  {
    g_platform_frame_dump_prefix = getenv("CLASH95_DUMP_PRESENTED_FRAMES_PREFIX");
    if ( !g_platform_frame_dump_prefix || !*g_platform_frame_dump_prefix )
      g_platform_frame_dump_prefix = getenv("CLASH95_SCREENSHOT_PREFIX");
    g_platform_frame_dump_skip = PlatformReadNonNegativeIntEnv("CLASH95_DUMP_PRESENTED_FRAMES_SKIP", 0);
    g_platform_frame_dump_limit = PlatformReadNonNegativeIntEnv(
      "CLASH95_DUMP_PRESENTED_FRAMES_LIMIT",
      PLATFORM_PRESENTED_FRAME_DUMP_DEFAULT_LIMIT);
    g_platform_frame_dump_checked = 1;
  }
  if ( !g_platform_frame_dump_prefix || !*g_platform_frame_dump_prefix || !surface )
    return;
  current_present_index = g_platform_frame_present_index++;
  if ( current_present_index < g_platform_frame_dump_skip )
    return;
  if ( g_platform_frame_dump_limit && g_platform_frame_dump_index >= g_platform_frame_dump_limit )
    return;
  snprintf(frame_path, sizeof(frame_path), "%s-%03d.bmp", g_platform_frame_dump_prefix, g_platform_frame_dump_index++);
  if ( SDL_SaveBMP(surface, frame_path) != 0 )
    fprintf(stderr, "[platform_sdl] SDL_SaveBMP failed for %s: %s\n", frame_path, SDL_GetError());
}

void Platform_ResetPresentedFrameDump(void)
{
  g_platform_frame_present_index = 0;
  g_platform_frame_dump_index = 0;
}

static void PlatformPresentDirectDrawSurface(CompatDirectDrawSurface *surface)
{
  struct SDL_Window *window;
  SDL2_Surface *host_surface;
  SDL2_Surface *dib_surface;
  Uint32 *argb_pixels;
  SDL_Rect dest_rect;
  int argb_pitch;

  if ( !surface || !surface->pixels )
    return;
  window = surface->surface.owner_window;
  if ( !window && surface->owner )
    window = (struct SDL_Window *)surface->owner->cooperative_window;
  if ( !window || !window->host_window )
    return;
  argb_pixels = PlatformConvertSurfacePixelsToArgb32(surface, &argb_pitch);
  if ( !argb_pixels )
    return;
  dib_surface = SDL_CreateRGBSurfaceWithFormatFrom(
    argb_pixels,
    surface->width,
    surface->height,
    32,
    argb_pitch,
    SDL_PIXELFORMAT_ARGB8888);
  if ( !dib_surface )
  {
    free(argb_pixels);
    return;
  }
  host_surface = SDL_GetWindowSurface(window->host_window);
  if ( host_surface )
  {
    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = window->width > 0 ? window->width : surface->width;
    dest_rect.h = window->height > 0 ? window->height : surface->height;
    SDL_BlitScaled(dib_surface, 0, host_surface, &dest_rect);
    PlatformMaybeDumpPresentedFrame(dib_surface);
    SDL_UpdateWindowSurface(window->host_window);
  }
  SDL_FreeSurface(dib_surface);
  free(argb_pixels);
}

void Platform_PresentRecoveredIndexedSurfaceHandle(void *surface_handle, const uint32_t *palette_entries)
{
  const unsigned char *surface_bytes;
  const unsigned char *src_pixels;
  struct SDL_Window *window;
  SDL2_Surface *host_surface;
  SDL2_Surface *dib_surface;
  Uint32 *argb_pixels;
  SDL_Rect dest_rect;
  int width;
  int height;
  int argb_pitch;
  int x;
  int y;

  if ( !surface_handle || !palette_entries )
    return;
  surface_bytes = (const unsigned char *)surface_handle;
  width = *(const unsigned short *)surface_bytes;
  height = *(const unsigned short *)(surface_bytes + 2);
  src_pixels = (const unsigned char *)(uintptr_t)*(const unsigned int *)(surface_bytes + 4);
  if ( !src_pixels || width <= 0 || height <= 0 )
    return;
  window = (struct SDL_Window *)g_platform_foreground_window;
  if ( !window || !window->host_window )
    return;

  argb_pitch = width * (int)sizeof(*argb_pixels);
  argb_pixels = (Uint32 *)malloc((size_t)argb_pitch * (size_t)height);
  if ( !argb_pixels )
    return;

  for ( y = 0; y < height; ++y )
  {
    Uint32 *dst_row;
    const unsigned char *src_row;

    dst_row = (Uint32 *)((unsigned char *)argb_pixels + (size_t)y * (size_t)argb_pitch);
    src_row = src_pixels + (size_t)y * (size_t)width;
    for ( x = 0; x < width; ++x )
    {
      uint32_t entry;

      entry = palette_entries[src_row[x]];
      dst_row[x] = 0xFF000000u
                 | ((entry & 0xFFu) << 16)
                 | (entry & 0xFF00u)
                 | ((entry >> 16) & 0xFFu);
    }
  }

  dib_surface = SDL_CreateRGBSurfaceWithFormatFrom(
    argb_pixels,
    width,
    height,
    32,
    argb_pitch,
    SDL_PIXELFORMAT_ARGB8888);
  if ( !dib_surface )
  {
    free(argb_pixels);
    return;
  }

  host_surface = SDL_GetWindowSurface(window->host_window);
  if ( host_surface )
  {
    dest_rect.x = 0;
    dest_rect.y = 0;
    dest_rect.w = window->width > 0 ? window->width : width;
    dest_rect.h = window->height > 0 ? window->height : height;
    SDL_BlitScaled(dib_surface, 0, host_surface, &dest_rect);
    PlatformMaybeDumpPresentedFrame(dib_surface);
    SDL_UpdateWindowSurface(window->host_window);
  }
  SDL_FreeSurface(dib_surface);
  free(argb_pixels);
}

static void CompatDirectDrawSurfaceFillRect(CompatDirectDrawSurface *surface, const RECT *rect, DWORD color)
{
  unsigned char *dst_base;
  int bytes_per_pixel;
  int left;
  int top;
  int right;
  int bottom;
  int x;
  int y;

  if ( !surface || !surface->pixels )
    return;
  bytes_per_pixel = CompatSurfaceBytesPerPixel(surface);
  left = rect ? rect->left : 0;
  top = rect ? rect->top : 0;
  right = rect ? rect->right : surface->width;
  bottom = rect ? rect->bottom : surface->height;
  if ( left < 0 )
    left = 0;
  if ( top < 0 )
    top = 0;
  if ( right > surface->width )
    right = surface->width;
  if ( bottom > surface->height )
    bottom = surface->height;
  if ( left >= right || top >= bottom )
    return;
  dst_base = (unsigned char *)surface->pixels;
  for ( y = top; y < bottom; ++y )
  {
    unsigned char *dst_row;

    dst_row = dst_base + (size_t)y * (size_t)surface->pitch + (size_t)left * (size_t)bytes_per_pixel;
    if ( bytes_per_pixel == 1 )
    {
      memset(dst_row, (unsigned char)color, (size_t)(right - left));
      continue;
    }
    if ( bytes_per_pixel == 2 )
    {
      unsigned short fill16;

      fill16 = (unsigned short)color;
      for ( x = left; x < right; ++x )
        ((unsigned short *)dst_row)[x - left] = fill16;
      continue;
    }
    if ( bytes_per_pixel == 3 )
    {
      unsigned char blue;
      unsigned char green;
      unsigned char red;

      blue = (unsigned char)(color & 0xFFu);
      green = (unsigned char)((color >> 8) & 0xFFu);
      red = (unsigned char)((color >> 16) & 0xFFu);
      for ( x = left; x < right; ++x )
      {
        unsigned char *dst_pixel;

        dst_pixel = dst_row + (size_t)(x - left) * 3u;
        dst_pixel[0] = blue;
        dst_pixel[1] = green;
        dst_pixel[2] = red;
      }
      continue;
    }
    for ( x = left; x < right; ++x )
      ((Uint32 *)dst_row)[x - left] = color;
  }
}

static void CompatDirectDrawSurfaceCopyRect(
  CompatDirectDrawSurface *dst,
  const RECT *dst_rect,
  const CompatDirectDrawSurface *src,
  const RECT *src_rect,
  DWORD flags)
{
  int apply_src_color_key;
  int dst_bpp;
  int src_bpp;
  int dst_left;
  int dst_top;
  int src_left;
  int src_top;
  int width;
  int height;
  int x;
  int y;

  if ( !dst || !dst->pixels || !src || !src->pixels )
    return;
  dst_left = dst_rect ? dst_rect->left : 0;
  dst_top = dst_rect ? dst_rect->top : 0;
  src_left = src_rect ? src_rect->left : 0;
  src_top = src_rect ? src_rect->top : 0;
  width = dst_rect ? (dst_rect->right - dst_rect->left) : dst->width;
  height = dst_rect ? (dst_rect->bottom - dst_rect->top) : dst->height;
  if ( src_rect )
  {
    if ( width > src_rect->right - src_rect->left )
      width = src_rect->right - src_rect->left;
    if ( height > src_rect->bottom - src_rect->top )
      height = src_rect->bottom - src_rect->top;
  }
  if ( dst_left < 0 )
  {
    src_left -= dst_left;
    width += dst_left;
    dst_left = 0;
  }
  if ( dst_top < 0 )
  {
    src_top -= dst_top;
    height += dst_top;
    dst_top = 0;
  }
  if ( src_left < 0 )
  {
    dst_left -= src_left;
    width += src_left;
    src_left = 0;
  }
  if ( src_top < 0 )
  {
    dst_top -= src_top;
    height += src_top;
    src_top = 0;
  }
  if ( dst_left + width > dst->width )
    width = dst->width - dst_left;
  if ( dst_top + height > dst->height )
    height = dst->height - dst_top;
  if ( src_left + width > src->width )
    width = src->width - src_left;
  if ( src_top + height > src->height )
    height = src->height - src_top;
  if ( width <= 0 || height <= 0 )
    return;
  dst_bpp = CompatSurfaceBytesPerPixel(dst);
  src_bpp = CompatSurfaceBytesPerPixel(src);
  apply_src_color_key = src->has_color_key && (flags & 0x8000u) != 0;
  for ( y = 0; y < height; ++y )
  {
    unsigned char *dst_row;
    const unsigned char *src_row;

    dst_row = (unsigned char *)dst->pixels
            + (size_t)(dst_top + y) * (size_t)dst->pitch
            + (size_t)dst_left * (size_t)dst_bpp;
    src_row = (const unsigned char *)src->pixels
            + (size_t)(src_top + y) * (size_t)src->pitch
            + (size_t)src_left * (size_t)src_bpp;
    if ( dst_bpp == src_bpp && !apply_src_color_key )
    {
      memmove(dst_row, src_row, (size_t)width * (size_t)dst_bpp);
      continue;
    }
    for ( x = 0; x < width; ++x )
    {
      const unsigned char *src_pixel;
      unsigned char *dst_pixel;

      src_pixel = src_row + (size_t)x * (size_t)src_bpp;
      dst_pixel = dst_row + (size_t)x * (size_t)dst_bpp;
      if ( apply_src_color_key )
      {
        Uint32 src_value;

        src_value = CompatSurfaceReadPixelValue(src, src_pixel);
        if ( src_value >= src->color_key_low && src_value <= src->color_key_high )
          continue;
      }
      if ( src_bpp == 1 && dst_bpp == 2 )
      {
        unsigned short pixel16;

        pixel16 = CompatPaletteIndexToRgb565(src, src_pixel[0]);
        ((unsigned short *)dst_pixel)[0] = pixel16;
      }
      else if ( src_bpp == 2 && dst_bpp == 1 )
      {
        unsigned short pixel16;
        unsigned int red;
        unsigned int green;
        unsigned int blue;

        pixel16 = ((const unsigned short *)src_pixel)[0];
        red = ((pixel16 >> 11) & 0x1Fu) * 255u / 31u;
        green = ((pixel16 >> 5) & 0x3Fu) * 255u / 63u;
        blue = (pixel16 & 0x1Fu) * 255u / 31u;
        dst_pixel[0] = (unsigned char)((red + green + blue) / 3u);
      }
      else if ( src_bpp == 1 && dst_bpp == 4 )
      {
        ((Uint32 *)dst_pixel)[0] = CompatPaletteIndexToArgb32(src, src_pixel[0]);
      }
      else if ( src_bpp == 4 && dst_bpp == 2 )
      {
        Uint32 pixel32;
        unsigned short pixel16;

        pixel32 = ((const Uint32 *)src_pixel)[0];
        pixel16 = (unsigned short)((((pixel32 >> 19) & 0x1Fu) << 11)
                                 | (((pixel32 >> 10) & 0x3Fu) << 5)
                                 | ((pixel32 >> 3) & 0x1Fu));
        ((unsigned short *)dst_pixel)[0] = pixel16;
      }
      else
      {
        int copy_bytes;

        copy_bytes = dst_bpp < src_bpp ? dst_bpp : src_bpp;
        memcpy(dst_pixel, src_pixel, (size_t)copy_bytes);
        if ( dst_bpp > copy_bytes )
          memset(dst_pixel + copy_bytes, 0, (size_t)(dst_bpp - copy_bytes));
      }
    }
  }
}

static HDC PlatformEnsureWindowDeviceContext(struct SDL_Window *window);

static HRESULT __stdcall CompatDirectDraw_QueryInterface(CompatDirectDraw *self, const void *riid, void *out_object);
static ULONG __stdcall CompatDirectDraw_AddRef(CompatDirectDraw *self);
static ULONG __stdcall CompatDirectDraw_Release(CompatDirectDraw *self);
static HRESULT __stdcall CompatDirectDraw_Compact(CompatDirectDraw *self);
static HRESULT __stdcall CompatDirectDraw_CreateClipper(CompatDirectDraw *self, DWORD flags, void *out_clipper, IUnknown *outer);
static HRESULT __stdcall CompatDirectDraw_CreatePalette(CompatDirectDraw *self, DWORD flags, void *entries, void *out_palette, IUnknown *outer);
static HRESULT __stdcall CompatDirectDraw_CreateSurface(CompatDirectDraw *self, int *desc, void *out_surface, IUnknown *outer);
static HRESULT __stdcall CompatDirectDraw_DuplicateSurface(CompatDirectDraw *self, void *source, void *out_surface);
static HRESULT __stdcall CompatDirectDraw_EnumDisplayModes(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback);
static HRESULT __stdcall CompatDirectDraw_EnumSurfaces(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback);
static HRESULT __stdcall CompatDirectDraw_FlipToGDISurface(CompatDirectDraw *self);
static HRESULT __stdcall CompatDirectDraw_GetCaps(CompatDirectDraw *self, void *driver_caps, void *hel_caps);
static HRESULT __stdcall CompatDirectDraw_GetDisplayMode(CompatDirectDraw *self, int *desc);
static HRESULT __stdcall CompatDirectDraw_GetFourCCCodes(CompatDirectDraw *self, void *count, void *codes);
static HRESULT __stdcall CompatDirectDraw_GetGDISurface(CompatDirectDraw *self, void *out_surface);
static HRESULT __stdcall CompatDirectDraw_GetMonitorFrequency(CompatDirectDraw *self, DWORD *frequency);
static HRESULT __stdcall CompatDirectDraw_GetScanLine(CompatDirectDraw *self, DWORD *scanline);
static HRESULT __stdcall CompatDirectDraw_GetVerticalBlankStatus(CompatDirectDraw *self, BOOL *in_vblank);
static HRESULT __stdcall CompatDirectDraw_Initialize(CompatDirectDraw *self, GUID *guid);
static HRESULT __stdcall CompatDirectDraw_RestoreDisplayMode(CompatDirectDraw *self);
static HRESULT __stdcall CompatDirectDraw_SetCooperativeLevel(CompatDirectDraw *self, HWND hwnd, DWORD flags);
static HRESULT __stdcall CompatDirectDraw_SetDisplayMode(CompatDirectDraw *self, int width, int height, int bpp, int refresh_rate, int flags);
static HRESULT __stdcall CompatDirectDraw_WaitForVerticalBlank(CompatDirectDraw *self, DWORD flags, HANDLE event_handle);

static HRESULT __stdcall CompatDirectDrawSurface_QueryInterface(CompatDirectDrawSurface *self, const void *riid, void *out_object);
static ULONG __stdcall CompatDirectDrawSurface_AddRef(CompatDirectDrawSurface *self);
static ULONG __stdcall CompatDirectDrawSurface_Release(CompatDirectDrawSurface *self);
static HRESULT __stdcall CompatDirectDrawSurface_AddAttachedSurface(CompatDirectDrawSurface *self, void *attached_surface);
static HRESULT __stdcall CompatDirectDrawSurface_AddOverlayDirtyRect(CompatDirectDrawSurface *self, const RECT *dirty_rect);
static HRESULT __stdcall CompatDirectDrawSurface_Blt(CompatDirectDrawSurface *self, RECT *dest_rect, void *src_surface, RECT *src_rect, DWORD flags, void *blt_fx);
static HRESULT __stdcall CompatDirectDrawSurface_BltBatch(CompatDirectDrawSurface *self, void *batch, DWORD count, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_BltFast(CompatDirectDrawSurface *self, int x, int y, void *src_surface, RECT *src_rect, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_DeleteAttachedSurface(CompatDirectDrawSurface *self, DWORD flags, void *attached_surface);
static HRESULT __stdcall CompatDirectDrawSurface_EnumAttachedSurfaces(CompatDirectDrawSurface *self, void *ctx, void *callback);
static HRESULT __stdcall CompatDirectDrawSurface_EnumOverlayZOrders(CompatDirectDrawSurface *self, DWORD flags, void *ctx, void *callback);
static HRESULT __stdcall CompatDirectDrawSurface_Flip(CompatDirectDrawSurface *self, void *target_override, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_GetAttachedSurface(CompatDirectDrawSurface *self, void *caps, void *out_surface);
static HRESULT __stdcall CompatDirectDrawSurface_GetBltStatus(CompatDirectDrawSurface *self, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_GetCaps(CompatDirectDrawSurface *self, void *caps);
static HRESULT __stdcall CompatDirectDrawSurface_GetClipper(CompatDirectDrawSurface *self, void *out_clipper);
static HRESULT __stdcall CompatDirectDrawSurface_GetColorKey(CompatDirectDrawSurface *self, DWORD flags, void *color_key);
static HRESULT __stdcall CompatDirectDrawSurface_GetDC(CompatDirectDrawSurface *self, void *out_dc);
static HRESULT __stdcall CompatDirectDrawSurface_GetFlipStatus(CompatDirectDrawSurface *self, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_GetOverlayPosition(CompatDirectDrawSurface *self, LONG *x, LONG *y);
static HRESULT __stdcall CompatDirectDrawSurface_GetPalette(CompatDirectDrawSurface *self, void *out_palette);
static HRESULT __stdcall CompatDirectDrawSurface_GetPixelFormat(CompatDirectDrawSurface *self, void *pixel_format);
static HRESULT __stdcall CompatDirectDrawSurface_GetSurfaceDesc(CompatDirectDrawSurface *self, int *desc);
static HRESULT __stdcall CompatDirectDrawSurface_Initialize(CompatDirectDrawSurface *self, CompatDirectDraw *owner, int *desc);
static HRESULT __stdcall CompatDirectDrawSurface_IsLost(CompatDirectDrawSurface *self);
static HRESULT __stdcall CompatDirectDrawSurface_Lock(CompatDirectDrawSurface *self, RECT *rect, int *desc, DWORD flags, HANDLE event_handle);
static HRESULT __stdcall CompatDirectDrawSurface_ReleaseDC(CompatDirectDrawSurface *self, HDC dc);
static HRESULT __stdcall CompatDirectDrawSurface_Restore(CompatDirectDrawSurface *self);
static HRESULT __stdcall CompatDirectDrawSurface_SetClipper(CompatDirectDrawSurface *self, void *clipper);
static HRESULT __stdcall CompatDirectDrawSurface_SetColorKey(CompatDirectDrawSurface *self, DWORD flags, void *color_key);
static HRESULT __stdcall CompatDirectDrawSurface_SetOverlayPosition(CompatDirectDrawSurface *self, LONG x, LONG y);
static HRESULT __stdcall CompatDirectDrawSurface_SetPalette(CompatDirectDrawSurface *self, void *palette);
static HRESULT __stdcall CompatDirectDrawSurface_Unlock(CompatDirectDrawSurface *self, void *lock_ptr);
static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlay(CompatDirectDrawSurface *self, RECT *src_rect, void *dest_surface, RECT *dest_rect, DWORD flags, void *overlay_fx);
static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlayDisplay(CompatDirectDrawSurface *self, DWORD flags);
static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlayZOrder(CompatDirectDrawSurface *self, DWORD flags, void *reference_surface);

static HRESULT __stdcall CompatDirectDrawPalette_QueryInterface(CompatDirectDrawPalette *self, const void *riid, void *out_object);
static ULONG __stdcall CompatDirectDrawPalette_AddRef(CompatDirectDrawPalette *self);
static ULONG __stdcall CompatDirectDrawPalette_Release(CompatDirectDrawPalette *self);
static HRESULT __stdcall CompatDirectDrawPalette_GetCaps(CompatDirectDrawPalette *self, DWORD *caps);
static HRESULT __stdcall CompatDirectDrawPalette_GetEntries(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries);
static HRESULT __stdcall CompatDirectDrawPalette_Initialize(CompatDirectDrawPalette *self, CompatDirectDraw *owner, DWORD flags, void *entries);
static HRESULT __stdcall CompatDirectDrawPalette_SetEntries(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries);

static HRESULT __stdcall CompatDirectDrawClipper_QueryInterface(CompatDirectDrawClipper *self, const void *riid, void *out_object);
static ULONG __stdcall CompatDirectDrawClipper_AddRef(CompatDirectDrawClipper *self);
static ULONG __stdcall CompatDirectDrawClipper_Release(CompatDirectDrawClipper *self);
static HRESULT __stdcall CompatDirectDrawClipper_GetClipList(CompatDirectDrawClipper *self, RECT *clip_rect, void *clip_list, DWORD *size);
static HRESULT __stdcall CompatDirectDrawClipper_GetHWnd(CompatDirectDrawClipper *self, HWND *hwnd);
static HRESULT __stdcall CompatDirectDrawClipper_Initialize(CompatDirectDrawClipper *self, CompatDirectDraw *owner, DWORD flags);
static HRESULT __stdcall CompatDirectDrawClipper_IsClipListChanged(CompatDirectDrawClipper *self, BOOL *changed);
static HRESULT __stdcall CompatDirectDrawClipper_SetClipList(CompatDirectDrawClipper *self, void *clip_list, DWORD flags);
static HRESULT __stdcall CompatDirectDrawClipper_SetHWnd(CompatDirectDrawClipper *self, DWORD flags, HWND hwnd);

static CompatDirectDrawVTable g_compat_directdraw_vtable = {
  CompatDirectDraw_QueryInterface,
  CompatDirectDraw_AddRef,
  CompatDirectDraw_Release,
  CompatDirectDraw_Compact,
  CompatDirectDraw_CreateClipper,
  CompatDirectDraw_CreatePalette,
  CompatDirectDraw_CreateSurface,
  CompatDirectDraw_DuplicateSurface,
  CompatDirectDraw_EnumDisplayModes,
  CompatDirectDraw_EnumSurfaces,
  CompatDirectDraw_FlipToGDISurface,
  CompatDirectDraw_GetCaps,
  CompatDirectDraw_GetDisplayMode,
  CompatDirectDraw_GetFourCCCodes,
  CompatDirectDraw_GetGDISurface,
  CompatDirectDraw_GetMonitorFrequency,
  CompatDirectDraw_GetScanLine,
  CompatDirectDraw_GetVerticalBlankStatus,
  CompatDirectDraw_Initialize,
  CompatDirectDraw_RestoreDisplayMode,
  CompatDirectDraw_SetCooperativeLevel,
  CompatDirectDraw_SetDisplayMode,
  CompatDirectDraw_WaitForVerticalBlank
};

static CompatDirectDrawSurfaceVTable g_compat_directdraw_surface_vtable = {
  CompatDirectDrawSurface_QueryInterface,
  CompatDirectDrawSurface_AddRef,
  CompatDirectDrawSurface_Release,
  CompatDirectDrawSurface_AddAttachedSurface,
  CompatDirectDrawSurface_AddOverlayDirtyRect,
  CompatDirectDrawSurface_Blt,
  CompatDirectDrawSurface_BltBatch,
  CompatDirectDrawSurface_BltFast,
  CompatDirectDrawSurface_DeleteAttachedSurface,
  CompatDirectDrawSurface_EnumAttachedSurfaces,
  CompatDirectDrawSurface_EnumOverlayZOrders,
  CompatDirectDrawSurface_Flip,
  CompatDirectDrawSurface_GetAttachedSurface,
  CompatDirectDrawSurface_GetBltStatus,
  CompatDirectDrawSurface_GetCaps,
  CompatDirectDrawSurface_GetClipper,
  CompatDirectDrawSurface_GetColorKey,
  CompatDirectDrawSurface_GetDC,
  CompatDirectDrawSurface_GetFlipStatus,
  CompatDirectDrawSurface_GetOverlayPosition,
  CompatDirectDrawSurface_GetPalette,
  CompatDirectDrawSurface_GetPixelFormat,
  CompatDirectDrawSurface_GetSurfaceDesc,
  CompatDirectDrawSurface_Initialize,
  CompatDirectDrawSurface_IsLost,
  CompatDirectDrawSurface_Lock,
  CompatDirectDrawSurface_ReleaseDC,
  CompatDirectDrawSurface_Restore,
  CompatDirectDrawSurface_SetClipper,
  CompatDirectDrawSurface_SetColorKey,
  CompatDirectDrawSurface_SetOverlayPosition,
  CompatDirectDrawSurface_SetPalette,
  CompatDirectDrawSurface_Unlock,
  CompatDirectDrawSurface_UpdateOverlay,
  CompatDirectDrawSurface_UpdateOverlayDisplay,
  CompatDirectDrawSurface_UpdateOverlayZOrder
};

static CompatDirectDrawPaletteVTable g_compat_directdraw_palette_vtable = {
  CompatDirectDrawPalette_QueryInterface,
  CompatDirectDrawPalette_AddRef,
  CompatDirectDrawPalette_Release,
  CompatDirectDrawPalette_GetCaps,
  CompatDirectDrawPalette_GetEntries,
  CompatDirectDrawPalette_Initialize,
  CompatDirectDrawPalette_SetEntries
};

static CompatDirectDrawClipperVTable g_compat_directdraw_clipper_vtable = {
  CompatDirectDrawClipper_QueryInterface,
  CompatDirectDrawClipper_AddRef,
  CompatDirectDrawClipper_Release,
  CompatDirectDrawClipper_GetClipList,
  CompatDirectDrawClipper_GetHWnd,
  CompatDirectDrawClipper_Initialize,
  CompatDirectDrawClipper_IsClipListChanged,
  CompatDirectDrawClipper_SetClipList,
  CompatDirectDrawClipper_SetHWnd
};

static CompatDirectDrawPalette *CompatDirectDrawPaletteCreate(CompatDirectDraw *owner, DWORD flags, void *entries)
{
  CompatDirectDrawPalette *palette;

  palette = (CompatDirectDrawPalette *)PlatformAllocLow32(sizeof(*palette));
  if ( !palette )
    return 0;
  memset(palette, 0, sizeof(*palette));
  palette->lpVtbl = &g_compat_directdraw_palette_vtable;
  palette->ref_count = 1;
  palette->owner = owner;
  palette->flags = flags;
  CompatDirectDrawPalette_Initialize(palette, owner, flags, entries);
  if ( owner )
    CompatDirectDraw_AddRef(owner);
  return palette;
}

static CompatDirectDrawSurface *CompatDirectDrawSurfaceCreate(CompatDirectDraw *owner, int width, int height, int bpp, DWORD caps)
{
  CompatDirectDrawSurface *surface;

  surface = (CompatDirectDrawSurface *)PlatformAllocLow32(sizeof(*surface));
  if ( !surface )
    return 0;
  memset(surface, 0, sizeof(*surface));
  surface->lpVtbl = &g_compat_directdraw_surface_vtable;
  surface->ref_count = 1;
  surface->owner = owner;
  surface->caps = caps;
  surface->width = width > 0 ? width : 640;
  surface->height = height > 0 ? height : 480;
  surface->bpp = bpp > 0 ? bpp : 16;
  surface->pitch = surface->width * CompatSurfaceBytesPerPixel(surface);
  surface->surface.width = surface->width;
  surface->surface.height = surface->height;
  surface->surface.resource_name = "directdraw-surface";
  surface->surface.owner_window = owner ? (struct SDL_Window *)owner->cooperative_window : 0;
  if ( owner )
    CompatDirectDraw_AddRef(owner);
  return surface;
}

static HRESULT __stdcall CompatDirectDraw_QueryInterface(CompatDirectDraw *self, const void *riid, void *out_object)
{
  (void)riid;
  if ( !self || !out_object )
    return (HRESULT)0x80070057;
  *(void **)out_object = self;
  CompatDirectDraw_AddRef(self);
  return 0;
}

static ULONG __stdcall CompatDirectDraw_AddRef(CompatDirectDraw *self)
{
  if ( !self )
    return 0;
  return ++self->ref_count;
}

static ULONG __stdcall CompatDirectDraw_Release(CompatDirectDraw *self)
{
  if ( !self )
    return 0;
  if ( self->ref_count )
    --self->ref_count;
  if ( !self->ref_count )
    PlatformFreeLow32(self);
  return self->ref_count;
}

static HRESULT __stdcall CompatDirectDraw_Compact(CompatDirectDraw *self)
{
  (void)self;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_CreateClipper(CompatDirectDraw *self, DWORD flags, void *out_clipper, IUnknown *outer)
{
  CompatDirectDrawClipper *clipper;

  (void)self;
  (void)flags;
  (void)outer;
  if ( !out_clipper )
    return (HRESULT)0x80070057;
  clipper = (CompatDirectDrawClipper *)PlatformAllocLow32(sizeof(*clipper));
  if ( !clipper )
    return (HRESULT)0x8007000E;
  memset(clipper, 0, sizeof(*clipper));
  clipper->lpVtbl = &g_compat_directdraw_clipper_vtable;
  clipper->ref_count = 1;
  *(void **)out_clipper = clipper;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_CreatePalette(CompatDirectDraw *self, DWORD flags, void *entries, void *out_palette, IUnknown *outer)
{
  CompatDirectDrawPalette *palette;

  (void)outer;
  if ( !out_palette )
    return (HRESULT)0x80070057;
  palette = CompatDirectDrawPaletteCreate(self, flags, entries);
  *(void **)out_palette = palette;
  return palette ? 0 : (HRESULT)0x8007000E;
}

static HRESULT __stdcall CompatDirectDraw_CreateSurface(CompatDirectDraw *self, int *desc, void *out_surface, IUnknown *outer)
{
  CompatDirectDrawSurface *surface;
  DWORD caps;

  (void)outer;
  if ( !self || !out_surface )
    return (HRESULT)0x80070057;
  caps = 0;
  if ( desc )
    caps = (DWORD)desc[1];
  surface = CompatDirectDrawSurfaceCreate(self, self->width, self->height, self->bpp, caps);
  if ( !surface )
    return (HRESULT)0x8007000E;
  *(void **)out_surface = surface;
  if ( !self->primary_surface )
    self->primary_surface = surface;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_DuplicateSurface(CompatDirectDraw *self, void *source, void *out_surface)
{
  (void)self;
  if ( !out_surface )
    return (HRESULT)0x80070057;
  *(void **)out_surface = source;
  if ( source )
    CompatDirectDrawSurface_AddRef((CompatDirectDrawSurface *)source);
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_EnumDisplayModes(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback)
{
  (void)self;
  (void)flags;
  (void)desc;
  (void)ctx;
  (void)callback;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_EnumSurfaces(CompatDirectDraw *self, DWORD flags, void *desc, void *ctx, void *callback)
{
  (void)self;
  (void)flags;
  (void)desc;
  (void)ctx;
  (void)callback;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_FlipToGDISurface(CompatDirectDraw *self)
{
  (void)self;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetCaps(CompatDirectDraw *self, void *driver_caps, void *hel_caps)
{
  (void)self;
  (void)driver_caps;
  (void)hel_caps;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetDisplayMode(CompatDirectDraw *self, int *desc)
{
  if ( !self || !desc )
    return (HRESULT)0x80070057;
  memset(desc, 0, 108);
  desc[0] = 108;
  desc[2] = self->height;
  desc[3] = self->width;
  desc[4] = self->width * ((self->bpp <= 8 ? 1 : self->bpp >> 3));
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetFourCCCodes(CompatDirectDraw *self, void *count, void *codes)
{
  (void)self;
  (void)count;
  (void)codes;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetGDISurface(CompatDirectDraw *self, void *out_surface)
{
  if ( !out_surface )
    return (HRESULT)0x80070057;
  *(void **)out_surface = self ? self->primary_surface : 0;
  if ( self && self->primary_surface )
    CompatDirectDrawSurface_AddRef(self->primary_surface);
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetMonitorFrequency(CompatDirectDraw *self, DWORD *frequency)
{
  (void)self;
  if ( frequency )
    *frequency = 60;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetScanLine(CompatDirectDraw *self, DWORD *scanline)
{
  (void)self;
  if ( scanline )
    *scanline = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_GetVerticalBlankStatus(CompatDirectDraw *self, BOOL *in_vblank)
{
  (void)self;
  if ( in_vblank )
    *in_vblank = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_Initialize(CompatDirectDraw *self, GUID *guid)
{
  (void)self;
  (void)guid;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_RestoreDisplayMode(CompatDirectDraw *self)
{
  (void)self;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_SetCooperativeLevel(CompatDirectDraw *self, HWND hwnd, DWORD flags)
{
  if ( !self )
    return (HRESULT)0x80070057;
  self->cooperative_window = hwnd;
  self->cooperative_flags = flags;
  if ( self->primary_surface )
    self->primary_surface->surface.owner_window = (struct SDL_Window *)hwnd;
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_SetDisplayMode(CompatDirectDraw *self, int width, int height, int bpp, int refresh_rate, int flags)
{
  struct SDL_Window *window;

  (void)refresh_rate;
  (void)flags;
  if ( !self )
    return (HRESULT)0x80070057;
  if ( width > 0 )
    self->width = width;
  if ( height > 0 )
    self->height = height;
  if ( bpp > 0 )
    self->bpp = bpp;
  g_platform_default_surface.width = self->width;
  g_platform_default_surface.height = self->height;
  if ( self->cooperative_window )
  {
    window = (struct SDL_Window *)self->cooperative_window;
    window->width = self->width;
    window->height = self->height;
    PlatformEnsureWindowDeviceContext(window);
    if ( window->host_window )
      SDL_SetWindowSize(window->host_window, self->width, self->height);
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_WaitForVerticalBlank(CompatDirectDraw *self, DWORD flags, HANDLE event_handle)
{
  (void)self;
  (void)flags;
  (void)event_handle;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawPalette_QueryInterface(CompatDirectDrawPalette *self, const void *riid, void *out_object)
{
  (void)riid;
  if ( !self || !out_object )
    return (HRESULT)0x80070057;
  *(void **)out_object = self;
  CompatDirectDrawPalette_AddRef(self);
  return 0;
}

static ULONG __stdcall CompatDirectDrawPalette_AddRef(CompatDirectDrawPalette *self)
{
  if ( !self )
    return 0;
  return ++self->ref_count;
}

static ULONG __stdcall CompatDirectDrawPalette_Release(CompatDirectDrawPalette *self)
{
  CompatDirectDraw *owner;

  if ( !self )
    return 0;
  if ( self->ref_count )
    --self->ref_count;
  if ( self->ref_count )
    return self->ref_count;
  owner = self->owner;
  PlatformFreeLow32(self);
  if ( owner )
    CompatDirectDraw_Release(owner);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawPalette_GetCaps(CompatDirectDrawPalette *self, DWORD *caps)
{
  if ( caps )
    *caps = self ? self->flags : 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawPalette_GetEntries(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries)
{
  (void)flags;
  if ( !self || !entries )
    return (HRESULT)0x80070057;
  if ( base > 256u || count > 256u || base + count > 256u )
    return (HRESULT)0x80070057;
  memcpy(entries, self->entries + base, (size_t)count * sizeof(self->entries[0]));
  return 0;
}

static HRESULT __stdcall CompatDirectDrawPalette_Initialize(CompatDirectDrawPalette *self, CompatDirectDraw *owner, DWORD flags, void *entries)
{
  if ( !self )
    return (HRESULT)0x80070057;
  self->owner = owner;
  self->flags = flags;
  if ( entries )
    memcpy(self->entries, entries, sizeof(self->entries));
  else
    memset(self->entries, 0, sizeof(self->entries));
  return 0;
}

static HRESULT __stdcall CompatDirectDrawPalette_SetEntries(CompatDirectDrawPalette *self, DWORD flags, DWORD base, DWORD count, void *entries)
{
  (void)flags;
  if ( !self || !entries )
    return (HRESULT)0x80070057;
  if ( base > 256u || count > 256u || base + count > 256u )
    return (HRESULT)0x80070057;
  memcpy(self->entries + base, entries, (size_t)count * sizeof(self->entries[0]));
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_QueryInterface(CompatDirectDrawSurface *self, const void *riid, void *out_object)
{
  (void)riid;
  if ( !self || !out_object )
    return (HRESULT)0x80070057;
  *(void **)out_object = self;
  CompatDirectDrawSurface_AddRef(self);
  return 0;
}

static ULONG __stdcall CompatDirectDrawSurface_AddRef(CompatDirectDrawSurface *self)
{
  if ( !self )
    return 0;
  return ++self->ref_count;
}

static ULONG __stdcall CompatDirectDrawSurface_Release(CompatDirectDrawSurface *self)
{
  CompatDirectDraw *owner;

  if ( !self )
    return 0;
  if ( self->ref_count )
    --self->ref_count;
  if ( self->ref_count )
    return self->ref_count;
  if ( self->attached_surface )
  {
    CompatDirectDrawSurface_Release(self->attached_surface);
    self->attached_surface = 0;
  }
  if ( self->pixels )
  {
    PlatformFreeLow32(self->pixels);
    self->pixels = 0;
  }
  if ( self->palette )
  {
    CompatDirectDrawPalette_Release((CompatDirectDrawPalette *)self->palette);
    self->palette = 0;
  }
  owner = self->owner;
  if ( owner && owner->primary_surface == self )
    owner->primary_surface = 0;
  PlatformFreeLow32(self);
  if ( owner )
    CompatDirectDraw_Release(owner);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_AddAttachedSurface(CompatDirectDrawSurface *self, void *attached_surface)
{
  if ( !self )
    return (HRESULT)0x80070057;
  self->attached_surface = (CompatDirectDrawSurface *)attached_surface;
  if ( self->attached_surface )
    CompatDirectDrawSurface_AddRef(self->attached_surface);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_AddOverlayDirtyRect(CompatDirectDrawSurface *self, const RECT *dirty_rect)
{
  (void)self;
  (void)dirty_rect;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Blt(CompatDirectDrawSurface *self, RECT *dest_rect, void *src_surface, RECT *src_rect, DWORD flags, void *blt_fx)
{
  CompatDirectDrawSurface *src;
  HRESULT hr;

  (void)flags;
  if ( !self )
    return (HRESULT)0x80070057;
  hr = CompatDirectDrawSurfaceEnsurePixels(self);
  if ( hr )
    return hr;
  src = (CompatDirectDrawSurface *)src_surface;
  if ( src )
  {
    hr = CompatDirectDrawSurfaceEnsurePixels(src);
    if ( hr )
      return hr;
    CompatDirectDrawSurfaceCopyRect(self, dest_rect, src, src_rect, flags);
    self->surface.width = src->surface.width;
    self->surface.height = src->surface.height;
  }
  else
  {
    DWORD fill_color;

    fill_color = blt_fx ? ((DWORD *)blt_fx)[20] : 0;
    CompatDirectDrawSurfaceFillRect(self, dest_rect, fill_color);
  }
  self->lost = 0;
  if ( self == (self->owner ? self->owner->primary_surface : 0) || self->surface.owner_window )
    PlatformPresentDirectDrawSurface(self);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_BltBatch(CompatDirectDrawSurface *self, void *batch, DWORD count, DWORD flags)
{
  (void)self;
  (void)batch;
  (void)count;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_BltFast(CompatDirectDrawSurface *self, int x, int y, void *src_surface, RECT *src_rect, DWORD flags)
{
  RECT dest_rect;

  if ( src_rect )
  {
    dest_rect.left = x;
    dest_rect.top = y;
    dest_rect.right = x + (src_rect->right - src_rect->left);
    dest_rect.bottom = y + (src_rect->bottom - src_rect->top);
  }
  else
  {
    CompatDirectDrawSurface *src;

    src = (CompatDirectDrawSurface *)src_surface;
    dest_rect.left = x;
    dest_rect.top = y;
    dest_rect.right = x + (src ? src->width : self->width);
    dest_rect.bottom = y + (src ? src->height : self->height);
  }
  return CompatDirectDrawSurface_Blt(self, &dest_rect, src_surface, src_rect, flags, 0);
}

static HRESULT __stdcall CompatDirectDrawSurface_DeleteAttachedSurface(CompatDirectDrawSurface *self, DWORD flags, void *attached_surface)
{
  (void)flags;
  if ( self && self->attached_surface == (CompatDirectDrawSurface *)attached_surface )
  {
    CompatDirectDrawSurface_Release(self->attached_surface);
    self->attached_surface = 0;
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_EnumAttachedSurfaces(CompatDirectDrawSurface *self, void *ctx, void *callback)
{
  (void)self;
  (void)ctx;
  (void)callback;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_EnumOverlayZOrders(CompatDirectDrawSurface *self, DWORD flags, void *ctx, void *callback)
{
  (void)self;
  (void)flags;
  (void)ctx;
  (void)callback;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Flip(CompatDirectDrawSurface *self, void *target_override, DWORD flags)
{
  CompatDirectDrawSurface *src;

  (void)flags;
  if ( !self )
    return (HRESULT)0x80070057;
  src = (CompatDirectDrawSurface *)target_override;
  if ( !src )
    src = self->attached_surface;
  if ( src )
  {
    HRESULT hr;

    hr = CompatDirectDrawSurface_Blt(self, 0, src, 0, 0, 0);
    if ( hr )
      return hr;
  }
  if ( self == (self->owner ? self->owner->primary_surface : 0) || self->surface.owner_window )
    PlatformPresentDirectDrawSurface(self);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetAttachedSurface(CompatDirectDrawSurface *self, void *caps, void *out_surface)
{
  (void)caps;
  if ( !self || !out_surface )
    return (HRESULT)0x80070057;
  if ( !self->attached_surface )
    self->attached_surface = CompatDirectDrawSurfaceCreate(self->owner, self->width, self->height, self->bpp, self->caps);
  *(void **)out_surface = self->attached_surface;
  if ( self->attached_surface )
    CompatDirectDrawSurface_AddRef(self->attached_surface);
  return self->attached_surface ? 0 : (HRESULT)0x8007000E;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetBltStatus(CompatDirectDrawSurface *self, DWORD flags)
{
  (void)self;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetCaps(CompatDirectDrawSurface *self, void *caps)
{
  if ( caps )
    *(DWORD *)caps = self ? self->caps : 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetClipper(CompatDirectDrawSurface *self, void *out_clipper)
{
  if ( out_clipper )
    *(void **)out_clipper = self ? self->clipper : 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetColorKey(CompatDirectDrawSurface *self, DWORD flags, void *color_key)
{
  (void)flags;
  if ( self && color_key )
  {
    DWORD *color_values;

    color_values = (DWORD *)color_key;
    color_values[0] = self->color_key_low;
    color_values[1] = self->color_key_high;
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetDC(CompatDirectDrawSurface *self, void *out_dc)
{
  if ( !self || !out_dc )
    return (HRESULT)0x80070057;
  if ( !self->surface.owner_window && self->owner && self->owner->cooperative_window )
    self->surface.owner_window = (struct SDL_Window *)self->owner->cooperative_window;
  self->surface.width = self->width;
  self->surface.height = self->height;
  *(void **)out_dc = &self->surface;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetFlipStatus(CompatDirectDrawSurface *self, DWORD flags)
{
  (void)self;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetOverlayPosition(CompatDirectDrawSurface *self, LONG *x, LONG *y)
{
  (void)self;
  if ( x )
    *x = 0;
  if ( y )
    *y = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetPalette(CompatDirectDrawSurface *self, void *out_palette)
{
  if ( out_palette )
  {
    *(void **)out_palette = self ? self->palette : 0;
    if ( self && self->palette )
      CompatDirectDrawPalette_AddRef((CompatDirectDrawPalette *)self->palette);
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetPixelFormat(CompatDirectDrawSurface *self, void *pixel_format)
{
  (void)self;
  (void)pixel_format;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetSurfaceDesc(CompatDirectDrawSurface *self, int *desc)
{
  if ( !self || !desc )
    return (HRESULT)0x80070057;
  memset(desc, 0, 108);
  desc[0] = 108;
  desc[2] = self->height;
  desc[3] = self->width;
  desc[4] = self->pitch;
  desc[9] = (int)(uintptr_t)self->pixels;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Initialize(CompatDirectDrawSurface *self, CompatDirectDraw *owner, int *desc)
{
  (void)desc;
  if ( self )
    self->owner = owner;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_IsLost(CompatDirectDrawSurface *self)
{
  if ( self && self->lost )
    return (HRESULT)0x887600c2;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Lock(CompatDirectDrawSurface *self, RECT *rect, int *desc, DWORD flags, HANDLE event_handle)
{
  HRESULT hr;

  (void)rect;
  (void)flags;
  (void)event_handle;
  if ( !self || !desc )
    return (HRESULT)0x80070057;
  hr = CompatDirectDrawSurfaceEnsurePixels(self);
  if ( hr )
    return hr;
  memset(desc, 0, 108);
  desc[0] = 108;
  desc[2] = self->height;
  desc[3] = self->width;
  desc[4] = self->pitch;
  desc[9] = (int)(uintptr_t)self->pixels;
  self->lost = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_ReleaseDC(CompatDirectDrawSurface *self, HDC dc)
{
  (void)self;
  (void)dc;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Restore(CompatDirectDrawSurface *self)
{
  if ( self )
    self->lost = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_SetClipper(CompatDirectDrawSurface *self, void *clipper)
{
  if ( self )
    self->clipper = clipper;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_SetColorKey(CompatDirectDrawSurface *self, DWORD flags, void *color_key)
{
  (void)flags;
  if ( self )
  {
    if ( color_key )
    {
      const DWORD *color_values;

      color_values = (const DWORD *)color_key;
      self->color_key_low = color_values[0];
      self->color_key_high = color_values[1];
      self->has_color_key = 1;
    }
    else
    {
      self->color_key_low = 0;
      self->color_key_high = 0;
      self->has_color_key = 0;
    }
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_SetOverlayPosition(CompatDirectDrawSurface *self, LONG x, LONG y)
{
  (void)self;
  (void)x;
  (void)y;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_SetPalette(CompatDirectDrawSurface *self, void *palette)
{
  if ( self )
  {
    if ( palette )
      CompatDirectDrawPalette_AddRef((CompatDirectDrawPalette *)palette);
    if ( self->palette )
      CompatDirectDrawPalette_Release((CompatDirectDrawPalette *)self->palette);
    self->palette = palette;
    if ( self == (self->owner ? self->owner->primary_surface : 0) || self->surface.owner_window )
      PlatformPresentDirectDrawSurface(self);
  }
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Unlock(CompatDirectDrawSurface *self, void *lock_ptr)
{
  (void)self;
  (void)lock_ptr;
  if ( self == (self->owner ? self->owner->primary_surface : 0) || (self && self->surface.owner_window) )
    PlatformPresentDirectDrawSurface(self);
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlay(CompatDirectDrawSurface *self, RECT *src_rect, void *dest_surface, RECT *dest_rect, DWORD flags, void *overlay_fx)
{
  (void)self;
  (void)src_rect;
  (void)dest_surface;
  (void)dest_rect;
  (void)flags;
  (void)overlay_fx;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlayDisplay(CompatDirectDrawSurface *self, DWORD flags)
{
  (void)self;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_UpdateOverlayZOrder(CompatDirectDrawSurface *self, DWORD flags, void *reference_surface)
{
  (void)self;
  (void)flags;
  (void)reference_surface;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_QueryInterface(CompatDirectDrawClipper *self, const void *riid, void *out_object)
{
  (void)riid;
  if ( !self || !out_object )
    return (HRESULT)0x80070057;
  *(void **)out_object = self;
  CompatDirectDrawClipper_AddRef(self);
  return 0;
}

static ULONG __stdcall CompatDirectDrawClipper_AddRef(CompatDirectDrawClipper *self)
{
  if ( !self )
    return 0;
  return ++self->ref_count;
}

static ULONG __stdcall CompatDirectDrawClipper_Release(CompatDirectDrawClipper *self)
{
  if ( !self )
    return 0;
  if ( self->ref_count )
    --self->ref_count;
  if ( !self->ref_count )
    PlatformFreeLow32(self);
  return self->ref_count;
}

static HRESULT __stdcall CompatDirectDrawClipper_GetClipList(CompatDirectDrawClipper *self, RECT *clip_rect, void *clip_list, DWORD *size)
{
  (void)self;
  (void)clip_rect;
  (void)clip_list;
  if ( size )
    *size = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_GetHWnd(CompatDirectDrawClipper *self, HWND *hwnd)
{
  if ( hwnd )
    *hwnd = self ? self->hwnd : 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_Initialize(CompatDirectDrawClipper *self, CompatDirectDraw *owner, DWORD flags)
{
  (void)self;
  (void)owner;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_IsClipListChanged(CompatDirectDrawClipper *self, BOOL *changed)
{
  (void)self;
  if ( changed )
    *changed = 0;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_SetClipList(CompatDirectDrawClipper *self, void *clip_list, DWORD flags)
{
  (void)self;
  (void)clip_list;
  (void)flags;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawClipper_SetHWnd(CompatDirectDrawClipper *self, DWORD flags, HWND hwnd)
{
  (void)flags;
  if ( self )
    self->hwnd = hwnd;
  return 0;
}

extern LRESULT Platform_MainWindowProc(void *this_, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
DWORD __stdcall timeGetTime(void);

#define PLATFORM_QUEUE_CAPACITY 32
#define PLATFORM_WM_PAINT 0x000F
#define PLATFORM_WM_QUIT 0x0012
#define PLATFORM_WM_ACTIVATEAPP 0x001C

static WNDCLASSA g_platform_window_class;
static int g_platform_has_window_class;
static HWND g_platform_foreground_window;
static struct SDL_Surface g_platform_default_surface = { 640, 480 };
static struct SDL_Surface g_platform_default_icon = { 32, 32 };
static struct SDL_Cursor g_platform_default_cursor = { 0 };
static int g_platform_stock_brush;
static int g_platform_module_handle_token;
static MSG g_platform_message_queue[PLATFORM_QUEUE_CAPACITY];
static size_t g_platform_message_head;
static size_t g_platform_message_tail;
static int g_platform_quit_requested;
static int g_platform_quit_code;
static int g_platform_sdl_initialized;
static int g_platform_sdl_available;
static int g_platform_host_mouse_x;
static int g_platform_host_mouse_y;
static int g_platform_host_mouse_delta_x;
static int g_platform_host_mouse_delta_y;
static int g_platform_host_mouse_delta_is_host_pixels;
static signed char g_platform_host_mouse_primary;
static signed char g_platform_host_mouse_secondary;
static int g_platform_host_mouse_primary_pending_press;
static int g_platform_host_mouse_secondary_pending_press;
static int g_platform_debug_mouse_primary_pulse_reads;
static int g_platform_debug_mouse_secondary_pulse_reads;
static signed char g_platform_host_keyboard_state[256];

static int PlatformSurfaceIsWindowDeviceContext(const struct SDL_Surface *surface)
{
  return surface && surface->owner_window && surface->owner_window->device_context == surface;
}

static int PlatformSurfaceIsBuiltin(const struct SDL_Surface *surface)
{
  return surface == &g_platform_default_surface
      || surface == &g_platform_default_icon
      || PlatformSurfaceIsWindowDeviceContext(surface);
}

static struct SDL_Window *PlatformGetWindowFromHdc(HDC hdc)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)hdc;
  if ( !surface )
    return 0;
  return surface->owner_window;
}

static HDC PlatformEnsureWindowDeviceContext(struct SDL_Window *window)
{
  struct SDL_Surface *surface;

  if ( !window )
    return &g_platform_default_surface;
  surface = window->device_context;
  if ( !surface )
  {
    surface = (struct SDL_Surface *)PlatformAllocLow32(sizeof(*surface));
    if ( !surface )
      return &g_platform_default_surface;
    memset(surface, 0, sizeof(*surface));
    surface->resource_name = "window-device-context";
    surface->owner_window = window;
    window->device_context = surface;
  }
  surface->width = window->width > 0 ? window->width : 640;
  surface->height = window->height > 0 ? window->height : 480;
  return surface;
}

static Uint32 *PlatformConvertDibToArgb32(const void *bits, const BITMAPINFO *bitmap_info, int fallback_width, int fallback_height, int *out_pitch)
{
  const BITMAPINFOHEADER *header;
  const BYTE *src_base;
  const RGBQUAD *palette;
  Uint32 *pixels;
  int width;
  int height;
  int src_pitch;
  int dst_pitch;
  int bit_count;
  int top_down;
  int y;
  int x;

  if ( !bits || !bitmap_info )
    return 0;
  header = &bitmap_info->bmiHeader;
  width = header->biWidth ? abs(header->biWidth) : fallback_width;
  height = header->biHeight ? abs(header->biHeight) : fallback_height;
  if ( width <= 0 || height <= 0 )
    return 0;
  bit_count = header->biBitCount ? header->biBitCount : 32;
  if ( bit_count != 8 && bit_count != 24 && bit_count != 32 )
    return 0;
  src_pitch = ((width * bit_count + 31) / 32) * 4;
  dst_pitch = width * (int)sizeof(*pixels);
  pixels = (Uint32 *)malloc((size_t)dst_pitch * (size_t)height);
  if ( !pixels )
    return 0;
  src_base = (const BYTE *)bits;
  palette = bitmap_info->bmiColors;
  top_down = header->biHeight < 0;
  for ( y = 0; y < height; ++y )
  {
    const BYTE *src_row;
    Uint32 *dst_row;

    src_row = src_base + (size_t)(top_down ? y : (height - 1 - y)) * (size_t)src_pitch;
    dst_row = (Uint32 *)((BYTE *)pixels + (size_t)y * (size_t)dst_pitch);
    for ( x = 0; x < width; ++x )
    {
      switch ( bit_count )
      {
        case 8:
        {
          RGBQUAD color;

          color = palette[src_row[x]];
          dst_row[x] = 0xFF000000u | ((Uint32)color.rgbRed << 16) | ((Uint32)color.rgbGreen << 8) | (Uint32)color.rgbBlue;
          break;
        }
        case 24:
        {
          const BYTE *src_pixel;

          src_pixel = src_row + x * 3;
          dst_row[x] = 0xFF000000u | ((Uint32)src_pixel[2] << 16) | ((Uint32)src_pixel[1] << 8) | (Uint32)src_pixel[0];
          break;
        }
        case 32:
        {
          const BYTE *src_pixel;
          Uint32 alpha;

          src_pixel = src_row + x * 4;
          alpha = src_pixel[3] ? (Uint32)src_pixel[3] : 0xFFu;
          dst_row[x] = (alpha << 24) | ((Uint32)src_pixel[2] << 16) | ((Uint32)src_pixel[1] << 8) | (Uint32)src_pixel[0];
          break;
        }
      }
    }
  }
  if ( out_pitch )
    *out_pitch = dst_pitch;
  return pixels;
}

static int PlatformQueueIsEmpty(void)
{
  return g_platform_message_head == g_platform_message_tail;
}

static void PlatformFillQuitMessage(LPMSG lpMsg)
{
  if ( !lpMsg )
    return;
  memset(lpMsg, 0, sizeof(*lpMsg));
  lpMsg->hwnd = g_platform_foreground_window;
  lpMsg->message = PLATFORM_WM_QUIT;
  lpMsg->wParam = (WPARAM)g_platform_quit_code;
}

static BOOL PlatformQueuePush(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  size_t next_tail;

  next_tail = (g_platform_message_tail + 1) % PLATFORM_QUEUE_CAPACITY;
  if ( next_tail == g_platform_message_head )
    return 0;
  g_platform_message_queue[g_platform_message_tail].hwnd = hwnd;
  g_platform_message_queue[g_platform_message_tail].message = message;
  g_platform_message_queue[g_platform_message_tail].wParam = wParam;
  g_platform_message_queue[g_platform_message_tail].lParam = lParam;
  g_platform_message_queue[g_platform_message_tail].time = timeGetTime();
  g_platform_message_queue[g_platform_message_tail].pt.x = 0;
  g_platform_message_queue[g_platform_message_tail].pt.y = 0;
  g_platform_message_tail = next_tail;
  return 1;
}

static BOOL PlatformQueuePeek(LPMSG lpMsg, BOOL remove_message)
{
  if ( PlatformQueueIsEmpty() )
    return 0;
  if ( lpMsg )
    *lpMsg = g_platform_message_queue[g_platform_message_head];
  if ( remove_message )
    g_platform_message_head = (g_platform_message_head + 1) % PLATFORM_QUEUE_CAPACITY;
  return 1;
}

static int PlatformEnsureSdlVideo(void)
{
  if ( g_platform_sdl_initialized )
    return g_platform_sdl_available;
  g_platform_sdl_initialized = 1;
  SDL_SetMainReady();
  SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
  if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) == 0 )
  {
    g_platform_sdl_available = 1;
    return 1;
  }
  fprintf(stderr, "[platform_sdl] SDL_Init failed: %s\n", SDL_GetError());
  return 0;
}

static HWND PlatformFindWindowByHostId(Uint32 window_id)
{
  struct SDL_Window *window;
  SDL2_Window *host_window;

  if ( !window_id || !g_platform_foreground_window || !g_platform_sdl_available )
    return 0;
  host_window = SDL_GetWindowFromID(window_id);
  window = (struct SDL_Window *)g_platform_foreground_window;
  if ( !host_window || !window || window->host_window != host_window )
    return 0;
  return g_platform_foreground_window;
}

static int PlatformMapSdlKeyToInputScan(SDL_Keycode sym)
{
  switch ( sym )
  {
    case SDLK_ESCAPE: return 1;
    case SDLK_1: return 2;
    case SDLK_2: return 3;
    case SDLK_3: return 4;
    case SDLK_4: return 5;
    case SDLK_5: return 6;
    case SDLK_6: return 7;
    case SDLK_7: return 8;
    case SDLK_8: return 9;
    case SDLK_9: return 10;
    case SDLK_0: return 11;
    case SDLK_MINUS: return 12;
    case SDLK_EQUALS: return 13;
    case SDLK_BACKSPACE: return 14;
    case SDLK_TAB: return 15;
    case SDLK_q: return 16;
    case SDLK_w: return 17;
    case SDLK_e: return 18;
    case SDLK_r: return 19;
    case SDLK_t: return 20;
    case SDLK_y: return 21;
    case SDLK_u: return 22;
    case SDLK_i: return 23;
    case SDLK_o: return 24;
    case SDLK_p: return 25;
    case SDLK_LEFTBRACKET: return 26;
    case SDLK_RIGHTBRACKET: return 27;
    case SDLK_RETURN:
    case SDLK_KP_ENTER: return 28;
    case SDLK_a: return 30;
    case SDLK_s: return 31;
    case SDLK_d: return 32;
    case SDLK_f: return 33;
    case SDLK_g: return 34;
    case SDLK_h: return 35;
    case SDLK_j: return 36;
    case SDLK_k: return 37;
    case SDLK_l: return 38;
    case SDLK_SEMICOLON: return 39;
    case SDLK_QUOTE: return 40;
    case SDLK_z: return 44;
    case SDLK_x: return 45;
    case SDLK_c: return 46;
    case SDLK_v: return 47;
    case SDLK_b: return 48;
    case SDLK_n: return 49;
    case SDLK_m: return 50;
    case SDLK_COMMA: return 51;
    case SDLK_PERIOD: return 52;
    case SDLK_SLASH: return 53;
    case SDLK_SPACE: return 57;
    case SDLK_F1: return 59;
    case SDLK_F2: return 60;
    case SDLK_F3: return 61;
    case SDLK_F4: return 62;
    case SDLK_F5: return 63;
    case SDLK_F6: return 64;
    case SDLK_F7: return 65;
    case SDLK_F8: return 66;
    case SDLK_F9: return 67;
    case SDLK_F10: return 68;
    case SDLK_HOME: return 199;
    case SDLK_UP: return 200;
    case SDLK_PAGEUP: return 201;
    case SDLK_LEFT: return 203;
    case SDLK_RIGHT: return 205;
    case SDLK_END: return 207;
    case SDLK_DOWN: return 208;
    case SDLK_PAGEDOWN: return 209;
    case SDLK_INSERT: return 210;
    case SDLK_DELETE: return 211;
    default: return -1;
  }
}

static void PlatformSetKeyboardScan(int scan_code, int pressed)
{
  if ( scan_code < 0 || scan_code >= (int)sizeof(g_platform_host_keyboard_state) )
    return;
  g_platform_host_keyboard_state[scan_code] = pressed ? (signed char)0x80 : 0;
}

static void PlatformHandleHostEvent(const SDL_Event *event)
{
  HWND hwnd;
  int scan_code;

  if ( !event )
    return;
  switch ( event->type )
  {
    case SDL_QUIT:
      g_platform_quit_requested = 1;
      g_platform_quit_code = 0;
      break;
    case SDL_WINDOWEVENT:
      hwnd = PlatformFindWindowByHostId(event->window.windowID);
      if ( !hwnd )
        break;
      switch ( event->window.event )
      {
        case SDL_WINDOWEVENT_SHOWN:
        case SDL_WINDOWEVENT_EXPOSED:
          PlatformQueuePush(hwnd, PLATFORM_WM_PAINT, 0, 0);
          break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESIZED:
          if ( event->window.data1 > 0 )
            ((struct SDL_Window *)hwnd)->width = event->window.data1;
          if ( event->window.data2 > 0 )
            ((struct SDL_Window *)hwnd)->height = event->window.data2;
          PlatformQueuePush(hwnd, PLATFORM_WM_PAINT, 0, 0);
          break;
        case SDL_WINDOWEVENT_MOVED:
          ((struct SDL_Window *)hwnd)->x = event->window.data1;
          ((struct SDL_Window *)hwnd)->y = event->window.data2;
          break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
          PlatformQueuePush(hwnd, PLATFORM_WM_ACTIVATEAPP, 1, 0);
          break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
          PlatformQueuePush(hwnd, PLATFORM_WM_ACTIVATEAPP, 0, 0);
          break;
        case SDL_WINDOWEVENT_CLOSE:
          g_platform_quit_requested = 1;
          g_platform_quit_code = 0;
          break;
        default:
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      g_platform_host_mouse_delta_x += event->motion.x - g_platform_host_mouse_x;
      g_platform_host_mouse_delta_y += event->motion.y - g_platform_host_mouse_y;
      g_platform_host_mouse_delta_is_host_pixels = 1;
      g_platform_host_mouse_x = event->motion.x;
      g_platform_host_mouse_y = event->motion.y;
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      g_platform_host_mouse_delta_x += event->button.x - g_platform_host_mouse_x;
      g_platform_host_mouse_delta_y += event->button.y - g_platform_host_mouse_y;
      g_platform_host_mouse_delta_is_host_pixels = 1;
      g_platform_host_mouse_x = event->button.x;
      g_platform_host_mouse_y = event->button.y;
      if ( event->button.button == SDL_BUTTON_LEFT )
      {
        if ( event->type == SDL_MOUSEBUTTONDOWN )
          g_platform_host_mouse_primary_pending_press = 1;
        g_platform_host_mouse_primary = event->type == SDL_MOUSEBUTTONDOWN ? (signed char)0x80 : 0;
      }
      else if ( event->button.button == SDL_BUTTON_RIGHT )
      {
        if ( event->type == SDL_MOUSEBUTTONDOWN )
          g_platform_host_mouse_secondary_pending_press = 1;
        g_platform_host_mouse_secondary = event->type == SDL_MOUSEBUTTONDOWN ? (signed char)0x80 : 0;
      }
      break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      scan_code = PlatformMapSdlKeyToInputScan(event->key.keysym.sym);
      if ( scan_code >= 0 )
        PlatformSetKeyboardScan(scan_code, event->type == SDL_KEYDOWN);
      break;
    default:
      break;
  }
}

static int PlatformQueryX11PointerState(struct SDL_Window *window, int *mouse_x, int *mouse_y, Uint32 *mouse_buttons)
{
#if defined(SDL_VIDEO_DRIVER_X11)
  SDL_SysWMinfo wm_info;
  Window root_window;
  Window child_window;
  int root_x;
  int root_y;
  int window_x;
  int window_y;
  unsigned int state_mask;

  if ( !window || !window->host_window || !mouse_x || !mouse_y || !mouse_buttons )
    return 0;
  SDL_VERSION(&wm_info.version);
  if ( !SDL_GetWindowWMInfo(window->host_window, &wm_info) || wm_info.subsystem != SDL_SYSWM_X11 )
    return 0;
  if ( !wm_info.info.x11.display || !wm_info.info.x11.window )
    return 0;
  root_window = 0;
  child_window = 0;
  root_x = 0;
  root_y = 0;
  window_x = 0;
  window_y = 0;
  state_mask = 0;
  if ( !XQueryPointer(
          wm_info.info.x11.display,
          wm_info.info.x11.window,
          &root_window,
          &child_window,
          &root_x,
          &root_y,
          &window_x,
          &window_y,
          &state_mask) )
  {
    return 0;
  }
  if ( window_x < 0 || window_y < 0 || window_x >= window->width || window_y >= window->height )
    return 0;
  *mouse_x = window_x;
  *mouse_y = window_y;
  *mouse_buttons = 0;
  if ( (state_mask & Button1Mask) != 0 )
    *mouse_buttons |= SDL_BUTTON_LMASK;
  if ( (state_mask & Button3Mask) != 0 )
    *mouse_buttons |= SDL_BUTTON_RMASK;
  return 1;
#else
  (void)window;
  (void)mouse_x;
  (void)mouse_y;
  (void)mouse_buttons;
  return 0;
#endif
}

static void PlatformSyncPolledMouseState(void)
{
  struct SDL_Window *window;
  int mouse_x;
  int mouse_y;
  int global_mouse_x;
  int global_mouse_y;
  int window_x;
  int window_y;
  Uint32 mouse_buttons;
  int primary_down;
  int secondary_down;

  window = (struct SDL_Window *)g_platform_foreground_window;
  if ( !window || !window->host_window )
    return;
  global_mouse_x = 0;
  global_mouse_y = 0;
  window_x = window->x;
  window_y = window->y;
  SDL_GetWindowPosition(window->host_window, &window_x, &window_y);
  if ( PlatformQueryX11PointerState(window, &mouse_x, &mouse_y, &mouse_buttons) )
  {
    global_mouse_x = window_x + mouse_x;
    global_mouse_y = window_y + mouse_y;
  }
  else
  {
    mouse_buttons = SDL_GetGlobalMouseState(&global_mouse_x, &global_mouse_y);
    mouse_x = global_mouse_x - window_x;
    mouse_y = global_mouse_y - window_y;
  }
  if ( mouse_x < 0 || mouse_y < 0 || mouse_x >= window->width || mouse_y >= window->height )
  {
    mouse_x = g_platform_host_mouse_x;
    mouse_y = g_platform_host_mouse_y;
    mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
  }
  if ( mouse_x < 0 || mouse_y < 0 || mouse_x >= window->width || mouse_y >= window->height )
    return;

  g_platform_host_mouse_delta_x += mouse_x - g_platform_host_mouse_x;
  g_platform_host_mouse_delta_y += mouse_y - g_platform_host_mouse_y;
  if ( mouse_x != g_platform_host_mouse_x || mouse_y != g_platform_host_mouse_y )
    g_platform_host_mouse_delta_is_host_pixels = 1;
  g_platform_host_mouse_x = mouse_x;
  g_platform_host_mouse_y = mouse_y;

  primary_down = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
  secondary_down = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
  if ( primary_down && !g_platform_host_mouse_primary )
    g_platform_host_mouse_primary_pending_press = 1;
  if ( secondary_down && !g_platform_host_mouse_secondary )
    g_platform_host_mouse_secondary_pending_press = 1;
  g_platform_host_mouse_primary = primary_down ? (signed char)0x80 : 0;
  g_platform_host_mouse_secondary = secondary_down ? (signed char)0x80 : 0;
}

static void PlatformPumpHostEvents(void)
{
  SDL_Event event;

  if ( !PlatformEnsureSdlVideo() )
    return;
  while ( SDL_PollEvent(&event) )
    PlatformHandleHostEvent(&event);
  PlatformSyncPolledMouseState();
}

ATOM __stdcall RegisterClassA(const WNDCLASSA *lpWndClass)
{
  if ( !lpWndClass )
    return 0;
  g_platform_window_class = *lpWndClass;
  g_platform_has_window_class = 1;
  return 1;
}

HWND __stdcall CreateWindowExA(
  DWORD dwExStyle,
  LPCSTR lpClassName,
  LPCSTR lpWindowName,
  DWORD dwStyle,
  int X,
  int Y,
  int nWidth,
  int nHeight,
  HWND hWndParent,
  HMENU hMenu,
  HINSTANCE hInstance,
  LPVOID lpParam)
{
  struct SDL_Window *window;

  (void)dwExStyle;
  (void)hWndParent;
  (void)hMenu;
  (void)hInstance;
  (void)lpParam;
  window = (struct SDL_Window *)PlatformAllocLow32(sizeof(*window));
  if ( !window )
    return 0;
  memset(window, 0, sizeof(*window));
  window->x = X;
  window->y = Y;
  window->width = nWidth;
  window->height = nHeight;
  window->style = dwStyle;
  window->class_name = lpClassName;
  window->title = lpWindowName;
  if ( PlatformEnsureSdlVideo() )
  {
    window->host_window = SDL_CreateWindow(
      lpWindowName ? lpWindowName : "clash95_recovered",
      X,
      Y,
      nWidth > 0 ? nWidth : 640,
      nHeight > 0 ? nHeight : 480,
      SDL_WINDOW_HIDDEN);
    if ( !window->host_window )
      fprintf(stderr, "[platform_sdl] SDL_CreateWindow failed: %s\n", SDL_GetError());
  }
  g_platform_foreground_window = window;
  g_platform_quit_requested = 0;
  g_platform_quit_code = 0;
  return window;
}

LRESULT __stdcall DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  (void)hWnd;
  (void)Msg;
  (void)wParam;
  (void)lParam;
  return 0;
}

LRESULT __stdcall DispatchMessageA(const MSG *lpMsg)
{
  WNDPROC window_proc;

  if ( !lpMsg )
    return 0;
  if ( lpMsg->message == PLATFORM_WM_QUIT )
  {
    g_platform_quit_requested = 1;
    g_platform_quit_code = (int)lpMsg->wParam;
    return 0;
  }
  if ( g_platform_has_window_class )
  {
    window_proc = g_platform_window_class.lpfnWndProc;
    if ( window_proc )
    {
      if ( (void *)window_proc == (void *)Platform_MainWindowProc )
        return Platform_MainWindowProc(0, lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
      return window_proc(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);
    }
  }
  return 0;
}

BOOL __stdcall GetClientRect(HWND hWnd, LPRECT lpRect)
{
  struct SDL_Window *window;

  if ( !lpRect )
    return 0;
  memset(lpRect, 0, sizeof(*lpRect));
  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    lpRect->right = window->width;
    lpRect->bottom = window->height;
  }
  return 1;
}

HDC __stdcall GetDC(HWND hWnd)
{
  struct SDL_Window *window;

  window = (struct SDL_Window *)(hWnd ? hWnd : g_platform_foreground_window);
  if ( !window )
    return &g_platform_default_surface;
  return PlatformEnsureWindowDeviceContext(window);
}

int __stdcall GetDeviceCaps(HDC hdc, int index)
{
  (void)hdc;
  switch ( index )
  {
    case 12:
      return 32;
    case 14:
      return 1;
    default:
      return 0;
  }
}

COLORREF __stdcall GetPixel(HDC hdc, int x, int y)
{
  struct SDL_Surface *surface;

  (void)x;
  (void)y;
  surface = (struct SDL_Surface *)hdc;
  if ( !surface )
    return 0;
  return surface->key_pixel;
}

COLORREF __stdcall SetPixel(HDC hdc, int x, int y, COLORREF color)
{
  struct SDL_Surface *surface;

  (void)x;
  (void)y;
  surface = (struct SDL_Surface *)hdc;
  if ( !surface )
    return 0;
  surface->key_pixel = color;
  return color;
}

BOOL __stdcall SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom)
{
  if ( !lprc )
    return 0;
  lprc->left = xLeft;
  lprc->top = yTop;
  lprc->right = xRight;
  lprc->bottom = yBottom;
  return 1;
}

BOOL __stdcall EqualRect(const RECT *lprc1, const RECT *lprc2)
{
  if ( !lprc1 || !lprc2 )
    return 0;
  return lprc1->left == lprc2->left
      && lprc1->top == lprc2->top
      && lprc1->right == lprc2->right
      && lprc1->bottom == lprc2->bottom;
}

BOOL __stdcall IsRectEmpty(const RECT *lprc)
{
  if ( !lprc )
    return 1;
  return lprc->left >= lprc->right || lprc->top >= lprc->bottom;
}

BOOL __stdcall IntersectRect(LPRECT lprcDst, const RECT *lprcSrc1, const RECT *lprcSrc2)
{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;

  if ( !lprcDst || !lprcSrc1 || !lprcSrc2 )
    return 0;
  left = lprcSrc1->left > lprcSrc2->left ? lprcSrc1->left : lprcSrc2->left;
  top = lprcSrc1->top > lprcSrc2->top ? lprcSrc1->top : lprcSrc2->top;
  right = lprcSrc1->right < lprcSrc2->right ? lprcSrc1->right : lprcSrc2->right;
  bottom = lprcSrc1->bottom < lprcSrc2->bottom ? lprcSrc1->bottom : lprcSrc2->bottom;
  if ( left >= right || top >= bottom )
  {
    SetRect(lprcDst, 0, 0, 0, 0);
    return 0;
  }
  SetRect(lprcDst, left, top, right, bottom);
  return 1;
}

HWND __stdcall GetForegroundWindow()
{
  return g_platform_foreground_window;
}

BOOL __stdcall GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  (void)hWnd;
  (void)wMsgFilterMin;
  (void)wMsgFilterMax;
  for ( ; ; )
  {
    PlatformPumpHostEvents();
    if ( PlatformQueuePeek(lpMsg, 1) )
    {
      if ( lpMsg && lpMsg->message == PLATFORM_WM_QUIT )
      {
        g_platform_quit_requested = 1;
        g_platform_quit_code = (int)lpMsg->wParam;
        return 0;
      }
      return 1;
    }
    if ( g_platform_quit_requested )
    {
      PlatformFillQuitMessage(lpMsg);
      return 0;
    }
    usleep(10000);
  }
}

HGDIOBJ __stdcall GetStockObject(int i)
{
  g_platform_stock_brush = i;
  return &g_platform_stock_brush;
}

HCURSOR __stdcall LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName)
{
  (void)hInstance;
  (void)lpCursorName;
  return &g_platform_default_cursor;
}

HICON __stdcall LoadIconA(HINSTANCE hInstance, LPCSTR lpIconName)
{
  (void)hInstance;
  (void)lpIconName;
  return &g_platform_default_icon;
}

int __stdcall MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
  (void)hWnd;
  (void)uType;
  fprintf(stderr, "[platform_sdl] %s: %s\n", lpCaption ? lpCaption : "(no caption)", lpText ? lpText : "(no text)");
  return 0;
}

BOOL __stdcall PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  (void)hWnd;
  (void)wMsgFilterMin;
  (void)wMsgFilterMax;
  PlatformPumpHostEvents();
  if ( PlatformQueuePeek(lpMsg, wRemoveMsg != 0) )
    return 1;
  if ( g_platform_quit_requested )
  {
    PlatformFillQuitMessage(lpMsg);
    return 1;
  }
  if ( lpMsg )
    memset(lpMsg, 0, sizeof(*lpMsg));
  return 0;
}

void __stdcall PostQuitMessage(int nExitCode)
{
  g_platform_quit_requested = 1;
  g_platform_quit_code = nExitCode;
}

int __stdcall ReleaseDC(HWND hWnd, HDC hDC)
{
  (void)hWnd;
  (void)hDC;
  return 1;
}

HDC __stdcall CreateCompatibleDC(HDC hdc)
{
  struct SDL_Surface *source;
  struct SDL_Surface *surface;

  source = (struct SDL_Surface *)hdc;
  surface = (struct SDL_Surface *)PlatformAllocLow32(sizeof(*surface));
  if ( !surface )
    return 0;
  memset(surface, 0, sizeof(*surface));
  if ( source )
  {
    surface->width = source->width;
    surface->height = source->height;
  }
  else
  {
    surface->width = 64;
    surface->height = 64;
  }
  return surface;
}

BOOL __stdcall DeleteDC(HDC hdc)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)hdc;
  if ( !surface || PlatformSurfaceIsBuiltin(surface) )
    return 1;
  PlatformFreeLow32(surface);
  return 1;
}

BOOL __stdcall DeleteObject(HGDIOBJ ho)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)ho;
  if ( !surface || PlatformSurfaceIsBuiltin(surface) )
    return 1;
  PlatformFreeLow32(surface);
  return 1;
}

int __stdcall GetObjectA(HANDLE h, int c, LPVOID pv)
{
  const struct SDL_Surface *surface;
  int *bitmap_fields;

  if ( !h || !pv || c <= 0 )
    return 0;
  surface = (const struct SDL_Surface *)h;
  memset(pv, 0, (size_t)c);
  bitmap_fields = (int *)pv;
  if ( c >= 12 )
  {
    bitmap_fields[1] = surface->width;
    bitmap_fields[2] = surface->height;
  }
  return c;
}

HGDIOBJ __stdcall SelectObject(HDC hdc, HGDIOBJ h)
{
  struct SDL_Surface *dc_surface;
  const struct SDL_Surface *object_surface;

  dc_surface = (struct SDL_Surface *)hdc;
  object_surface = (const struct SDL_Surface *)h;
  if ( dc_surface && object_surface && !PlatformSurfaceIsBuiltin(dc_surface) )
  {
    dc_surface->width = object_surface->width;
    dc_surface->height = object_surface->height;
  }
  return h;
}

BOOL __stdcall StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop)
{
  struct SDL_Surface *dest_surface;

  (void)xDest;
  (void)yDest;
  (void)hdcSrc;
  (void)xSrc;
  (void)ySrc;
  (void)wSrc;
  (void)hSrc;
  (void)rop;
  dest_surface = (struct SDL_Surface *)hdcDest;
  if ( dest_surface && !PlatformSurfaceIsBuiltin(dest_surface) )
  {
    if ( wDest > 0 )
      dest_surface->width = wDest;
    if ( hDest > 0 )
      dest_surface->height = hDest;
  }
  return 1;
}

int __stdcall StretchDIBits(HDC hdc, int xDest, int yDest, int DestWidth, int DestHeight, int xSrc, int ySrc, int SrcWidth, int SrcHeight, const void *lpBits, const BITMAPINFO *lpbmi, UINT iUsage, DWORD rop)
{
  struct SDL_Surface *surface;
  struct SDL_Window *window;
  SDL2_Surface *host_surface;
  SDL2_Surface *dib_surface;
  Uint32 *argb_pixels;
  SDL_Rect dest_rect;
  int argb_pitch;
  int surface_width;
  int surface_height;

  (void)xSrc;
  (void)ySrc;
  (void)iUsage;
  (void)rop;
  surface = (struct SDL_Surface *)hdc;
  if ( surface )
  {
    if ( DestWidth > 0 )
      surface->width = DestWidth;
    if ( DestHeight > 0 )
      surface->height = DestHeight;
  }
  window = PlatformGetWindowFromHdc(hdc);
  if ( !window || !window->host_window || !lpBits || !lpbmi )
    return SrcHeight ? SrcHeight : DestHeight;
  surface_width = lpbmi->bmiHeader.biWidth ? abs(lpbmi->bmiHeader.biWidth) : SrcWidth;
  surface_height = lpbmi->bmiHeader.biHeight ? abs(lpbmi->bmiHeader.biHeight) : abs(SrcHeight);
  argb_pixels = PlatformConvertDibToArgb32(lpBits, lpbmi, surface_width, surface_height, &argb_pitch);
  if ( !argb_pixels )
    return 0;
  dib_surface = SDL_CreateRGBSurfaceWithFormatFrom(
    argb_pixels,
    surface_width,
    surface_height,
    32,
    argb_pitch,
    SDL_PIXELFORMAT_ARGB8888);
  if ( !dib_surface )
  {
    free(argb_pixels);
    return 0;
  }
  host_surface = SDL_GetWindowSurface(window->host_window);
  if ( !host_surface )
  {
    SDL_FreeSurface(dib_surface);
    free(argb_pixels);
    return 0;
  }
  dest_rect.x = xDest;
  dest_rect.y = yDest;
  dest_rect.w = DestWidth > 0 ? DestWidth : surface_width;
  dest_rect.h = DestHeight > 0 ? DestHeight : surface_height;
  SDL_BlitScaled(dib_surface, 0, host_surface, &dest_rect);
  PlatformMaybeDumpPresentedFrame(dib_surface);
  SDL_UpdateWindowSurface(window->host_window);
  SDL_FreeSurface(dib_surface);
  free(argb_pixels);
  return SrcHeight ? SrcHeight : DestHeight;
}

HANDLE __stdcall LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  struct SDL_Surface *surface;

  (void)hInst;
  (void)type;
  (void)fuLoad;
  surface = (struct SDL_Surface *)PlatformAllocLow32(sizeof(*surface));
  if ( !surface )
    return 0;
  memset(surface, 0, sizeof(*surface));
  surface->width = cx > 0 ? cx : 64;
  surface->height = cy > 0 ? cy : 64;
  surface->resource_name = name;
  return surface;
}

BOOL __stdcall ShowWindow(HWND hWnd, int nCmdShow)
{
  struct SDL_Window *window;

  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    window->visible = nCmdShow != 0;
    if ( window->host_window )
    {
      if ( window->visible )
      {
        SDL_ShowWindow(window->host_window);
        SDL_RaiseWindow(window->host_window);
      }
      else
      {
        SDL_HideWindow(window->host_window);
      }
    }
    if ( window->visible )
      PlatformQueuePush(hWnd, PLATFORM_WM_ACTIVATEAPP, 1, 0);
  }
  return 1;
}

DWORD __stdcall timeGetTime()
{
  struct timeval tv;

  if ( gettimeofday(&tv, 0) )
    return 0;
  return (DWORD)(tv.tv_sec * 1000u + tv.tv_usec / 1000u);
}

DWORD __stdcall GetTickCount()
{
  return timeGetTime();
}

BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
{
  struct timeval tv;
  unsigned long long ticks;

  if ( !lpPerformanceCount )
    return 0;
  if ( gettimeofday(&tv, 0) != 0 )
  {
    lpPerformanceCount->QuadPart = 0;
    return 0;
  }
  ticks = (unsigned long long)tv.tv_sec * 1000000ull + (unsigned long long)tv.tv_usec;
  lpPerformanceCount->QuadPart = (long long)ticks;
  return 1;
}

BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
{
  if ( !lpFrequency )
    return 0;
  lpFrequency->QuadPart = 1000000ll;
  return 1;
}

DWORD __stdcall GetVersion()
{
  /*
   * Report an NT-style major version 4 so the recovered platform probes pick a
   * stable, non-9x path until the startup/runtime layer is fully re-emitted.
   */
  return 4u;
}

HMODULE __stdcall GetModuleHandleA(LPCSTR lpModuleName)
{
  (void)lpModuleName;
  return &g_platform_module_handle_token;
}

HRESULT __stdcall DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter)
{
  CompatDirectDraw *direct_draw;

  (void)lpGUID;
  (void)pUnkOuter;
  if ( !lplpDD )
    return (HRESULT)0x80070057;
  *lplpDD = 0;
  direct_draw = (CompatDirectDraw *)PlatformAllocLow32(sizeof(*direct_draw));
  if ( !direct_draw )
    return (HRESULT)0x8007000E;
  memset(direct_draw, 0, sizeof(*direct_draw));
  direct_draw->lpVtbl = &g_compat_directdraw_vtable;
  direct_draw->ref_count = 1;
  direct_draw->width = g_platform_default_surface.width ? g_platform_default_surface.width : 640;
  direct_draw->height = g_platform_default_surface.height ? g_platform_default_surface.height : 480;
  direct_draw->bpp = 16;
  direct_draw->cooperative_window = g_platform_foreground_window;
  *lplpDD = (LPDIRECTDRAW)direct_draw;
  return 0;
}

HRESULT Compat_DirectDraw_QueryInterface(LPDIRECTDRAW dd, const void *riid, void *out_object)
{
  CompatDirectDraw *query_result;
  HRESULT hr;

  query_result = 0;
  hr = CompatDirectDraw_QueryInterface((CompatDirectDraw *)dd, riid, &query_result);
  if ( hr )
    return hr;
  if ( out_object )
    *(int *)out_object = (int)(uintptr_t)query_result;
  return 0;
}

ULONG Compat_DirectDraw_Release(LPDIRECTDRAW dd)
{
  return CompatDirectDraw_Release((CompatDirectDraw *)dd);
}

HRESULT Compat_DirectDraw_SetCooperativeLevel(LPDIRECTDRAW dd, HWND hwnd, DWORD flags)
{
  return CompatDirectDraw_SetCooperativeLevel((CompatDirectDraw *)dd, hwnd, flags);
}

HRESULT Compat_DirectDraw_SetDisplayMode(LPDIRECTDRAW dd, int width, int height, int bpp, int refresh_rate, int flags)
{
  return CompatDirectDraw_SetDisplayMode((CompatDirectDraw *)dd, width, height, bpp, refresh_rate, flags);
}

HRESULT Compat_DirectDraw_CreatePalette(LPDIRECTDRAW dd, DWORD flags, void *entries, void *out_palette)
{
  CompatDirectDrawPalette *palette;
  HRESULT hr;

  palette = 0;
  hr = CompatDirectDraw_CreatePalette((CompatDirectDraw *)dd, flags, entries, &palette, 0);
  if ( hr )
    return hr;
  if ( out_palette )
    *(int *)out_palette = (int)(uintptr_t)palette;
  return 0;
}

HRESULT Compat_DirectDraw_CreateSurface(LPDIRECTDRAW dd, int *desc, void *out_surface)
{
  CompatDirectDrawSurface *surface;
  HRESULT hr;

  surface = 0;
  hr = CompatDirectDraw_CreateSurface((CompatDirectDraw *)dd, desc, &surface, 0);
  if ( hr )
    return hr;
  if ( out_surface )
    *(int *)out_surface = (int)(uintptr_t)surface;
  return 0;
}

HRESULT Compat_DirectDrawSurface_GetAttachedSurface(LPDIRECTDRAWSURFACE surface, void *caps, void *out_surface)
{
  CompatDirectDrawSurface *attached_surface;
  HRESULT hr;

  attached_surface = 0;
  hr = CompatDirectDrawSurface_GetAttachedSurface((CompatDirectDrawSurface *)surface, caps, &attached_surface);
  if ( hr )
    return hr;
  if ( out_surface )
    *(int *)out_surface = (int)(uintptr_t)attached_surface;
  return 0;
}

HRESULT Compat_DirectDrawSurface_Blt(LPDIRECTDRAWSURFACE surface, RECT *dest_rect, LPDIRECTDRAWSURFACE src_surface, RECT *src_rect, DWORD flags, void *blt_fx)
{
  return CompatDirectDrawSurface_Blt((CompatDirectDrawSurface *)surface, dest_rect, src_surface, src_rect, flags, blt_fx);
}

HRESULT Compat_DirectDrawSurface_IsLost(LPDIRECTDRAWSURFACE surface)
{
  return CompatDirectDrawSurface_IsLost((CompatDirectDrawSurface *)surface);
}

HRESULT Compat_DirectDrawSurface_Restore(LPDIRECTDRAWSURFACE surface)
{
  return CompatDirectDrawSurface_Restore((CompatDirectDrawSurface *)surface);
}

HRESULT Compat_DirectDrawSurface_Lock(LPDIRECTDRAWSURFACE surface, RECT *rect, int *desc, DWORD flags, HANDLE event_handle)
{
  return CompatDirectDrawSurface_Lock((CompatDirectDrawSurface *)surface, rect, desc, flags, event_handle);
}

HRESULT Compat_DirectDrawSurface_Unlock(LPDIRECTDRAWSURFACE surface, void *lock_ptr)
{
  return CompatDirectDrawSurface_Unlock((CompatDirectDrawSurface *)surface, lock_ptr);
}

HRESULT Compat_DirectDrawSurface_SetClipper(LPDIRECTDRAWSURFACE surface, void *clipper)
{
  return CompatDirectDrawSurface_SetClipper((CompatDirectDrawSurface *)surface, clipper);
}

HRESULT Compat_DirectDrawSurface_SetPalette(LPDIRECTDRAWSURFACE surface, void *palette)
{
  return CompatDirectDrawSurface_SetPalette((CompatDirectDrawSurface *)surface, palette);
}

int __stdcall DirectSoundCreate(void *lpGuid, void *lplpDS, void *punkOuter)
{
  (void)lpGuid;
  (void)punkOuter;
  if ( lplpDS )
    *(void **)lplpDS = 0;

  /*
   * Audio still goes through the SDL seam rather than legacy DirectSound.
   * Returning failure keeps the legacy device slots inert until that bridge is
   * reconstructed from recovered behavior.
   */
  return 1;
}

HRESULT __stdcall DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPVOID lplpDirectInput, LPVOID punkOuter)
{
  (void)hinst;
  (void)dwVersion;
  (void)lplpDirectInput;
  (void)punkOuter;

  /*
   * SDL owns input on the target platform, but the recovered boot path still
   * calls into DirectInput-era setup during window creation. Returning failure
   * keeps the legacy device slots inert while allowing the authentic window
   * proc and message loop to come up.
   */
  return 1;
}

UINT __stdcall GetDriveTypeA(LPCSTR lpRootPathName)
{
  struct stat st;
  char drive_letter;
  char probe_path[64];

  if ( !lpRootPathName || !lpRootPathName[0] )
    return 0;
  drive_letter = lpRootPathName[0];
  if ( drive_letter >= 'A' && drive_letter <= 'Z' )
    drive_letter = (char)(drive_letter - 'A' + 'a');
  if ( drive_letter < 'a' || drive_letter > 'z' )
    return 0;
  snprintf(probe_path, sizeof(probe_path), "/mnt/%c/clash", drive_letter);
  if ( stat(probe_path, &st) == 0 && S_ISDIR(st.st_mode) )
    return 5;
  snprintf(probe_path, sizeof(probe_path), "/mnt/%c/CLASH", drive_letter);
  if ( stat(probe_path, &st) == 0 && S_ISDIR(st.st_mode) )
    return 5;
  snprintf(probe_path, sizeof(probe_path), "/mnt/%c", drive_letter);
  if ( stat(probe_path, &st) == 0 && S_ISDIR(st.st_mode) )
    return 3;
  return 0;
}

void __stdcall OutputDebugStringA(LPCSTR lpOutputString)
{
  if ( lpOutputString )
    fprintf(stderr, "[platform_sdl] debug: %s\n", lpOutputString);
}

BOOL __stdcall TranslateMessage(const MSG *lpMsg)
{
  (void)lpMsg;
  return 1;
}

BOOL __stdcall UpdateWindow(HWND hWnd)
{
  PlatformQueuePush(hWnd, PLATFORM_WM_PAINT, 0, 0);
  return 1;
}

BOOL __stdcall ValidateRect(HWND hWnd, const RECT *lpRect)
{
  (void)hWnd;
  (void)lpRect;
  return 1;
}

BOOL __stdcall WaitMessage()
{
  PlatformPumpHostEvents();
  if ( PlatformQueueIsEmpty() && !g_platform_quit_requested )
    usleep(10000);
  return 1;
}

void __stdcall Sleep(DWORD dwMilliseconds)
{
  if ( dwMilliseconds )
    usleep(dwMilliseconds * 1000u);
}

BOOL __stdcall ClientToScreen(HWND hWnd, LPPOINT lpPoint)
{
  struct SDL_Window *window;

  if ( !lpPoint )
    return 0;
  window = (struct SDL_Window *)hWnd;
  if ( window )
  {
    lpPoint->x += window->x;
    lpPoint->y += window->y;
  }
  return 1;
}

void Platform_ResetInputFallbackState(void)
{
  g_platform_host_mouse_x = 0;
  g_platform_host_mouse_y = 0;
  g_platform_host_mouse_delta_x = 0;
  g_platform_host_mouse_delta_y = 0;
  g_platform_host_mouse_delta_is_host_pixels = 0;
  g_platform_host_mouse_primary = 0;
  g_platform_host_mouse_secondary = 0;
  g_platform_host_mouse_primary_pending_press = 0;
  g_platform_host_mouse_secondary_pending_press = 0;
  g_platform_debug_mouse_primary_pulse_reads = 0;
  g_platform_debug_mouse_secondary_pulse_reads = 0;
  memset(g_platform_host_keyboard_state, 0, sizeof(g_platform_host_keyboard_state));
}

void Platform_DebugPrimeInputFallbackMouseState(int x, int y, int primary_down, int secondary_down)
{
  /*
   * Keep the contained menu probe on the same fallback-input corridor the SDL
   * seam already uses. This only seeds the next `Platform_ReadInputFallbackState`
   * sample; it does not bypass the recovered `DD_Pump -> InputBackend_PollState`
   * path.
   */
  g_platform_host_mouse_delta_x += x - g_platform_host_mouse_x;
  g_platform_host_mouse_delta_y += y - g_platform_host_mouse_y;
  g_platform_host_mouse_delta_is_host_pixels = 0;
  g_platform_host_mouse_x = x;
  g_platform_host_mouse_y = y;
  g_platform_host_mouse_primary = primary_down ? (signed char)0x80 : 0;
  g_platform_host_mouse_secondary = secondary_down ? (signed char)0x80 : 0;
}

void Platform_DebugPrimeInputFallbackMouseDelta(int delta_x, int delta_y, int primary_down, int secondary_down)
{
  /*
   * The contained menu auto-click path needs to steer the recovered cursor via
   * the same delta-based sample that `DD_Pump -> InputBackend_PollState ->
   * sub_460A50` consumes, rather than assuming the SDL-side absolute mouse
   * position is already synchronized with the recovered render-state cursor.
   */
  g_platform_host_mouse_delta_x += delta_x;
  g_platform_host_mouse_delta_y += delta_y;
  g_platform_host_mouse_delta_is_host_pixels = 0;
  g_platform_host_mouse_x += delta_x;
  g_platform_host_mouse_y += delta_y;
  g_platform_host_mouse_primary = primary_down ? (signed char)0x80 : 0;
  g_platform_host_mouse_secondary = secondary_down ? (signed char)0x80 : 0;
}

void Platform_DebugPrimeInputFallbackMousePulse(
  int delta_x,
  int delta_y,
  int primary_down,
  int secondary_down,
  int read_count)
{
  Platform_DebugPrimeInputFallbackMouseDelta(delta_x, delta_y, primary_down, secondary_down);
  g_platform_debug_mouse_primary_pulse_reads = primary_down && read_count > 0 ? read_count : 0;
  g_platform_debug_mouse_secondary_pulse_reads = secondary_down && read_count > 0 ? read_count : 0;
}

void Platform_ReadInputFallbackState(
  int *mouse_delta_x,
  int *mouse_delta_y,
  signed char *mouse_button_primary,
  signed char *mouse_button_secondary,
  signed char *keyboard_state,
  int keyboard_state_size,
  int *mouse_delta_is_host_pixels)
{
  PlatformPumpHostEvents();
  if ( mouse_delta_x )
    *mouse_delta_x = g_platform_host_mouse_delta_x;
  if ( mouse_delta_y )
    *mouse_delta_y = g_platform_host_mouse_delta_y;
  if ( mouse_delta_is_host_pixels )
    *mouse_delta_is_host_pixels = g_platform_host_mouse_delta_is_host_pixels;
  if ( mouse_button_primary )
  {
    *mouse_button_primary = g_platform_host_mouse_primary;
    if ( !*mouse_button_primary && g_platform_host_mouse_primary_pending_press )
      *mouse_button_primary = (signed char)0x80;
  }
  if ( mouse_button_secondary )
  {
    *mouse_button_secondary = g_platform_host_mouse_secondary;
    if ( !*mouse_button_secondary && g_platform_host_mouse_secondary_pending_press )
      *mouse_button_secondary = (signed char)0x80;
  }
  if ( keyboard_state && keyboard_state_size > 0 )
  {
    size_t copy_size;

    copy_size = (size_t)keyboard_state_size;
    if ( copy_size > sizeof(g_platform_host_keyboard_state) )
      copy_size = sizeof(g_platform_host_keyboard_state);
    memcpy(keyboard_state, g_platform_host_keyboard_state, copy_size);
  }
  g_platform_host_mouse_delta_x = 0;
  g_platform_host_mouse_delta_y = 0;
  g_platform_host_mouse_delta_is_host_pixels = 0;
  g_platform_host_mouse_primary_pending_press = 0;
  g_platform_host_mouse_secondary_pending_press = 0;
  if ( g_platform_debug_mouse_primary_pulse_reads > 0 && --g_platform_debug_mouse_primary_pulse_reads == 0 )
    g_platform_host_mouse_primary = 0;
  if ( g_platform_debug_mouse_secondary_pulse_reads > 0 && --g_platform_debug_mouse_secondary_pulse_reads == 0 )
    g_platform_host_mouse_secondary = 0;
}
