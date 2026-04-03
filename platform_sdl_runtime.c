#include "platform_sdl.h"

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
};

struct SDL_Palette {
  int version;
};

struct SDL_Cursor {
  int cursor_id;
};

static struct SDL_Surface g_platform_default_surface;

int Compat_AllocLow32Bytes(int size);
void Compat_FreeLow32Bytes(int ptr);

typedef struct CompatDirectDraw CompatDirectDraw;
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
  (void)self;
  (void)flags;
  (void)entries;
  (void)outer;
  if ( out_palette )
    *(void **)out_palette = 0;
  return 0;
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
  return 0;
}

static HRESULT __stdcall CompatDirectDraw_SetDisplayMode(CompatDirectDraw *self, int width, int height, int bpp, int refresh_rate, int flags)
{
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
    ((struct SDL_Window *)self->cooperative_window)->width = self->width;
    ((struct SDL_Window *)self->cooperative_window)->height = self->height;
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

  (void)dest_rect;
  (void)src_rect;
  (void)flags;
  (void)blt_fx;
  if ( !self )
    return (HRESULT)0x80070057;
  src = (CompatDirectDrawSurface *)src_surface;
  if ( src )
  {
    self->surface.width = src->surface.width;
    self->surface.height = src->surface.height;
  }
  self->lost = 0;
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
  (void)x;
  (void)y;
  return CompatDirectDrawSurface_Blt(self, 0, src_surface, src_rect, flags, 0);
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
  (void)self;
  (void)target_override;
  (void)flags;
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
  (void)self;
  (void)flags;
  (void)color_key;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_GetDC(CompatDirectDrawSurface *self, void *out_dc)
{
  if ( !self || !out_dc )
    return (HRESULT)0x80070057;
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
    *(void **)out_palette = self ? self->palette : 0;
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
  size_t pixel_bytes;

  (void)rect;
  (void)flags;
  (void)event_handle;
  if ( !self || !desc )
    return (HRESULT)0x80070057;
  if ( !self->pixels )
  {
    pixel_bytes = (size_t)self->pitch * (size_t)self->height;
    self->pixels = PlatformAllocLow32(pixel_bytes);
    if ( !self->pixels )
      return (HRESULT)0x8007000E;
    memset(self->pixels, 0, pixel_bytes);
  }
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
  (void)self;
  (void)flags;
  (void)color_key;
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
    self->palette = palette;
  return 0;
}

static HRESULT __stdcall CompatDirectDrawSurface_Unlock(CompatDirectDrawSurface *self, void *lock_ptr)
{
  (void)self;
  (void)lock_ptr;
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

static int PlatformSurfaceIsBuiltin(const struct SDL_Surface *surface)
{
  return surface == &g_platform_default_surface || surface == &g_platform_default_icon;
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
  window = (struct SDL_Window *)calloc(1, sizeof(*window));
  if ( !window )
    return 0;
  window->x = X;
  window->y = Y;
  window->width = nWidth;
  window->height = nHeight;
  window->style = dwStyle;
  window->class_name = lpClassName;
  window->title = lpWindowName;
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
  (void)hWnd;
  return &g_platform_default_surface;
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
  if ( lpMsg )
    memset(lpMsg, 0, sizeof(*lpMsg));
  return 1;
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
  surface = (struct SDL_Surface *)calloc(1, sizeof(*surface));
  if ( !surface )
    return 0;
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
  free(surface);
  return 1;
}

BOOL __stdcall DeleteObject(HGDIOBJ ho)
{
  struct SDL_Surface *surface;

  surface = (struct SDL_Surface *)ho;
  if ( !surface || PlatformSurfaceIsBuiltin(surface) )
    return 1;
  free(surface);
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

  (void)xDest;
  (void)yDest;
  (void)xSrc;
  (void)ySrc;
  (void)SrcWidth;
  (void)lpBits;
  (void)lpbmi;
  (void)iUsage;
  (void)rop;
  surface = (struct SDL_Surface *)hdc;
  if ( surface && !PlatformSurfaceIsBuiltin(surface) )
  {
    if ( DestWidth > 0 )
      surface->width = DestWidth;
    if ( DestHeight > 0 )
      surface->height = DestHeight;
  }
  return SrcHeight ? SrcHeight : DestHeight;
}

HANDLE __stdcall LoadImageA(HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  struct SDL_Surface *surface;

  (void)hInst;
  (void)type;
  (void)fuLoad;
  surface = (struct SDL_Surface *)calloc(1, sizeof(*surface));
  if ( !surface )
    return 0;
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
