/* Generated recovered prelude helpers. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "state_internal.h"
#include "state_shared.h"
#include "state_local.h"
#include "../core/core_state.h"
#include "../render/render_state.h"
#include "../world/world_state.h"
#include "../units/units_state.h"
#include "../buildings/buildings_state.h"
#include "../battle/battle_state.h"
#include "../persistence/persistence_state.h"
#include "../strategic/strategic_state.h"
#include "../clips/clips_state.h"
#include "../media/media_state.h"
#include "../runtime/runtime_state.h"
#include "../core/core_api.h"
#include "../render/render_api.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE uintptr_t RenderSurface_GetCompactMethodPointer (_DWORD *surface, unsigned int table_offset);

CLASH95_INTERNAL int Runtime_DescriptorNoop(void)
{
  return 0;
}

CLASH95_INTERNAL void Runtime_InitCompactEvalDescriptor(EvalNodeDescriptorCompact descriptor, uintptr_t evaluator)
{
  descriptor[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  descriptor[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  descriptor[4] = (int)evaluator;
}

// weak

CLASH95_INTERNAL void Render_InitRecoveredVtableStorage(void)
{
  static int initialized;

  if ( initialized )
    return;
  initialized = 1;

  g_CompatStringHolder_Vtable = (int)(uintptr_t)&Compat_StringHolderScalarDeletingDtor;
  g_PathEntry_Vtable = (int)(uintptr_t)&PathEntry_Destruct;
  g_PathEntryArray_Vtable[0] = (int)(uintptr_t)&PathEntryArray_Destruct;
  g_PathEntryArray_Vtable[1] = (int)(uintptr_t)&Noop_PathEntryArrayDeletingDtor;

  g_RenderSurface_BlitCursorVtable[0] = (int)(uintptr_t)&RenderSurface_DestroyBlitCursor;
  g_RenderSurface_BlitCursorVtable[1] = (int)(uintptr_t)&RenderSurface_GetBlitCursorRowStride;
  g_RenderSurface_BlitCursorVtable[2] = (int)(uintptr_t)&RenderSurface_GetBlitCursorCapacity;
  g_RenderSurface_BlitCursorVtable[3] = (int)(uintptr_t)&RenderSurface_AdvanceBlitCursor;
  g_RenderSurface_BlitCursorVtable[4] = (int)(uintptr_t)&RenderSurface_GetBlitCursorPosition;

  g_RenderSurface_LinkedBlitCursorVtable[0] = (int)(uintptr_t)&RenderSurface_DestroyLinkedBlitCursor;
  g_RenderSurface_LinkedBlitCursorVtable[1] = (int)(uintptr_t)&RenderSurface_GetLinkedSurfaceBuffer;
  g_RenderSurface_LinkedBlitCursorVtable[2] = (int)(uintptr_t)&RenderSurface_GetLinkedBlitCursorCapacity;
  g_RenderSurface_LinkedBlitCursorVtable[3] = (int)(uintptr_t)&RenderSurface_AdvanceLinkedBlitCursor;
  g_RenderSurface_LinkedBlitCursorVtable[4] = (int)(uintptr_t)&RenderSurface_GetLinkedBlitCursorPosition;

  g_Surface_BaseVtable[0] = (int)(uintptr_t)&RenderSurface_Destroy;
  g_Surface_BaseVtable[1] = (int)(uintptr_t)&Surface_GetReadIncrNotImplemented;
  g_Surface_BaseVtable[2] = (int)(uintptr_t)&Surface_GetWriteIncrNotImplemented;
  g_Surface_BaseVtable[3] = (int)(uintptr_t)&Surface_DrawPixNotImplemented;
  g_Surface_BaseVtable[4] = (int)(uintptr_t)&Surface_GetPixNotImplemented;
  g_Surface_BaseVtable[5] = (int)(uintptr_t)&Surface_DrawLineNotImplemented;
  g_Surface_BaseVtable[6] = (int)(uintptr_t)&Surface_DrawRectNotImplemented;
  g_Surface_BaseVtable[7] = (int)(uintptr_t)&Surface_DrawBoxNotImplemented;
  g_Surface_BaseVtable[8] = (int)(uintptr_t)&Render_FillClippedScanlines;
  g_Surface_BaseVtable[9] = (int)(uintptr_t)&Render_ClearGameScreen;
  g_Surface_BaseVtable[10] = (int)(uintptr_t)&Surface_DotBoxNotImplemented;
  g_Surface_BaseVtable[11] = (int)(uintptr_t)&Render_BlitRectViaVirtualSurfaces;
  g_Surface_BaseVtable[12] = (int)(uintptr_t)&Render_LoadPCXImage;
  g_Surface_BaseVtable[13] = (int)(uintptr_t)&Render_BlitCompressedSpriteRLE;
  g_Surface_BaseVtable[14] = (int)(uintptr_t)&Surface_ClearWholeArea;
  g_Surface_BaseVtable[15] = (int)(uintptr_t)&Surface_GetReadIncrZero;
  g_Surface_BaseVtable[16] = (int)(uintptr_t)&Surface_GetWriteIncrZero;

  g_Surface_RawBuffer8Vtable[0] = (int)(uintptr_t)&Surface_DestructRawBuffer;
  g_Surface_RawBuffer8Vtable[1] = (int)(uintptr_t)&Surface_ConstructRegionViewA;
  g_Surface_RawBuffer8Vtable[2] = (int)(uintptr_t)&Surface_ConstructRegionViewB;
  g_Surface_RawBuffer8Vtable[3] = (int)(uintptr_t)&Surface_SetPixel8;
  g_Surface_RawBuffer8Vtable[4] = (int)(uintptr_t)&Surface_GetPixel8;
  g_Surface_RawBuffer8Vtable[5] = (int)(uintptr_t)&Surface_DrawDashedLine;
  g_Surface_RawBuffer8Vtable[6] = (int)(uintptr_t)&Surface_DrawRectOutline;
  g_Surface_RawBuffer8Vtable[7] = (int)(uintptr_t)&Surface_FillVerticalSpan;
  g_Surface_RawBuffer8Vtable[8] = (int)(uintptr_t)&Render_FillClippedScanlines;
  g_Surface_RawBuffer8Vtable[9] = (int)(uintptr_t)&Render_ClearGameScreen;
  g_Surface_RawBuffer8Vtable[10] = (int)(uintptr_t)&Surface_FillCheckerPattern;
  g_Surface_RawBuffer8Vtable[11] = (int)(uintptr_t)&Render_BlitRectViaVirtualSurfaces;
  g_Surface_RawBuffer8Vtable[12] = (int)(uintptr_t)&Render_LoadPCXImage;
  g_Surface_RawBuffer8Vtable[13] = (int)(uintptr_t)&Render_BlitCompressedSpriteRLE;
  g_Surface_RawBuffer8Vtable[14] = (int)(uintptr_t)&Surface_ClearWholeArea;
  g_Surface_RawBuffer8Vtable[15] = (int)(uintptr_t)&Surface_GetReadIncrZero;
  g_Surface_RawBuffer8Vtable[16] = (int)(uintptr_t)&Surface_GetWriteIncrZero;

  g_ScratchSurface_Vtable[0] = (int)(uintptr_t)&Render_DestructScratchSurface;
  g_ScratchSurface_Vtable[1] = (int)(uintptr_t)&Surface_ConstructLockedRegionView;
  g_ScratchSurface_Vtable[2] = (int)(uintptr_t)&Surface_ConstructPitchRegionView;
  g_ScratchSurface_Vtable[3] = (int)(uintptr_t)&Surface_DrawPix;
  g_ScratchSurface_Vtable[4] = (int)(uintptr_t)&Surface_GetPix;
  g_ScratchSurface_Vtable[5] = (int)(uintptr_t)&Surface_DrawLine;
  g_ScratchSurface_Vtable[6] = (int)(uintptr_t)&Surface_DrawRect;
  g_ScratchSurface_Vtable[7] = (int)(uintptr_t)&Surface_DrawBox;
  g_ScratchSurface_Vtable[8] = (int)(uintptr_t)&Render_FillClippedScanlines;
  g_ScratchSurface_Vtable[9] = (int)(uintptr_t)&Render_ClearGameScreen;
  g_ScratchSurface_Vtable[10] = (int)(uintptr_t)&Surface_DotBox;
  g_ScratchSurface_Vtable[11] = (int)(uintptr_t)&Render_BlitRectViaVirtualSurfaces;
  g_ScratchSurface_Vtable[12] = (int)(uintptr_t)&Render_LoadPCXImage;
  g_ScratchSurface_Vtable[13] = (int)(uintptr_t)&Render_BlitCompressedSpriteRLE;
  g_ScratchSurface_Vtable[14] = (int)(uintptr_t)&Render_UnlockBackbuffer;
  g_ScratchSurface_Vtable[15] = (int)(uintptr_t)&Surface_GetReadIncrFromStride;
  g_ScratchSurface_Vtable[16] = (int)(uintptr_t)&Surface_GetWriteIncrFromStride;

  g_Surface_Vtable[0] = (int)(uintptr_t)&Surface_Destroy;
  g_Surface_Vtable[1] = (int)(uintptr_t)&Surface_BeginPixelRead;
  g_Surface_Vtable[2] = (int)(uintptr_t)&Surface_BeginPixelWrite;
  g_Surface_Vtable[3] = (int)(uintptr_t)&Surface_DrawPixAndMarkDirty;
  g_Surface_Vtable[4] = (int)(uintptr_t)&Surface_GetPix;
  g_Surface_Vtable[5] = (int)(uintptr_t)&Surface_DrawLine;
  g_Surface_Vtable[6] = (int)(uintptr_t)&Surface_DrawRect;
  g_Surface_Vtable[7] = (int)(uintptr_t)&Surface_DrawBox;
  g_Surface_Vtable[8] = (int)(uintptr_t)&Render_FillClippedScanlines;
  g_Surface_Vtable[9] = (int)(uintptr_t)&Render_ClearGameScreen;
  g_Surface_Vtable[10] = (int)(uintptr_t)&Surface_DotBox;
  g_Surface_Vtable[11] = (int)(uintptr_t)&Render_BlitRectViaVirtualSurfaces;
  g_Surface_Vtable[12] = (int)(uintptr_t)&Render_LoadPCXImage;
  g_Surface_Vtable[13] = (int)(uintptr_t)&Render_BlitCompressedSpriteRLE;
  g_Surface_Vtable[14] = (int)(uintptr_t)&Render_UnlockBackbuffer;
  g_Surface_Vtable[15] = (int)(uintptr_t)&Surface_GetReadIncrFromStride;
  g_Surface_Vtable[16] = (int)(uintptr_t)&Surface_GetWriteIncrAndMarkDirty;
  g_Surface_Vtable[17] = (int)(uintptr_t)&Render_SetPixelFormat;
  g_Surface_Vtable[18] = (int)(uintptr_t)&Render_BeginModeSwitch;
  g_Surface_Vtable[19] = (int)(uintptr_t)&Render_EndModeSwitch;
  g_Surface_Vtable[20] = (int)(uintptr_t)&Render_BlitSurface;

  g_NullBlitCursor_Vtable[0] = (int)(uintptr_t)&SurfaceCursor_Destroy;
  g_NullBlitCursor_Vtable[1] = (int)(uintptr_t)&SurfaceCursor_GetIncrUnbounded;
  g_NullBlitCursor_Vtable[2] = (int)(uintptr_t)&SurfaceCursor_GetExtentUnbounded;
  g_NullBlitCursor_Vtable[3] = (int)(uintptr_t)&Noop_SurfaceCursorUnboundedAdvance;
  g_NullBlitCursor_Vtable[4] = (int)(uintptr_t)&SurfaceCursor_GetOffsetZero;
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot60(_DWORD *surface)
{
  unsigned int vtable;

  vtable = (unsigned int)surface[46];
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_Vtable || vtable == (unsigned int)(uintptr_t)g_ScratchSurface_Vtable )
    return Surface_GetReadIncrFromStride((int)surface);
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable || vtable == (unsigned int)(uintptr_t)g_Surface_BaseVtable )
    return Surface_GetReadIncrZero();
  return 0;
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot64(_DWORD *surface)
{
  unsigned int vtable;

  vtable = (unsigned int)surface[46];
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_Vtable )
    return Surface_GetWriteIncrAndMarkDirty(surface);
  if ( vtable == (unsigned int)(uintptr_t)g_ScratchSurface_Vtable )
    return Surface_GetWriteIncrFromStride((int)surface);
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable || vtable == (unsigned int)(uintptr_t)g_Surface_BaseVtable )
    return Surface_GetWriteIncrZero();
  return 0;
}

CLASH95_TEST_VISIBLE uintptr_t RenderSurface_GetCompactMethodPointer(_DWORD *surface, unsigned int table_offset)
{
  unsigned int vtable;

  if ( !surface )
    return 0;
  vtable = (unsigned int)surface[46];
  if ( !vtable )
    return 0;
  return (uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(vtable + table_offset);
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot0(_DWORD *surface, int flags)
{
  uintptr_t method;

  method = RenderSurface_GetCompactMethodPointer(surface, 0);
  if ( !method )
    return 0;
  return ((int (__cdecl *)(_DWORD *, char))method)(surface, (char)flags);
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot36(_DWORD *surface)
{
  uintptr_t method;

  method = RenderSurface_GetCompactMethodPointer(surface, 36);
  if ( !method )
    return 0;
  return ((int (__cdecl *)(_DWORD *))method)(surface);
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot48LoadPCX(_DWORD *surface, char *path, int transparent, uintptr_t palette)
{
  uintptr_t method;

  method = RenderSurface_GetCompactMethodPointer(surface, 48);
  if ( !method )
    return 0;
  return ((int (__cdecl *)(int, char *, int, uintptr_t))method)((int)(uintptr_t)surface, path, transparent, palette);
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot56(_DWORD *surface)
{
  unsigned int vtable;
  uintptr_t method;

  if ( !surface )
    return 0;
  vtable = (unsigned int)surface[46];
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_Vtable || vtable == (unsigned int)(uintptr_t)g_ScratchSurface_Vtable )
    return Render_UnlockBackbuffer((int)(uintptr_t)surface);
  if ( vtable == (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable || vtable == (unsigned int)(uintptr_t)g_Surface_BaseVtable )
  {
    unsigned int pixel_count;
    unsigned char *pixels;

    pixel_count = (unsigned int)*(unsigned __int16 *)surface * (unsigned int)*((unsigned __int16 *)surface + 1);
    pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
    if ( pixels && pixel_count )
      memset(pixels, 0, pixel_count);
    return 0;
  }
  method = RenderSurface_GetCompactMethodPointer(surface, 56);
  if ( !method )
    return 0;
  return ((int (__cdecl *)(_DWORD *))method)(surface);
}

CLASH95_INTERNAL int RenderHandle_InvokeCopyDispatch(int source_handle, int destination_handle)
{
  int dispatch_fn;

  dispatch_fn = *(_DWORD *)(source_handle + 172);
  if ( !dispatch_fn )
    return 0;
  return ((int (__cdecl *)(int, int))(uintptr_t)(unsigned int)dispatch_fn)(source_handle, destination_handle);
}

CLASH95_INTERNAL _DWORD *RenderSurface_ResolvePrimaryCompanion(_DWORD *surface)
{
  if ( surface == (_DWORD *)&g_MainRenderDevice )
  {
    _DWORD *companion;

    companion = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
    if ( companion )
      return companion;
  }
  return surface;
}

CLASH95_INTERNAL int RenderSurface_IsLinearSoftware(_DWORD *surface)
{
  unsigned int vtable;

  if ( !surface )
    return 0;
  if ( !surface[1] )
    return 0;
  vtable = (unsigned int)surface[46];
  return vtable == (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable
      || vtable == (unsigned int)(uintptr_t)g_Surface_BaseVtable;
}

CLASH95_INTERNAL int RenderSurface_InvokeSlot16ReadPixel(_DWORD *surface, int x, int y)
{
  uintptr_t method;

  if ( !surface )
    return 0;
  if ( RenderSurface_IsLinearSoftware(surface) )
  {
    int width;
    int height;
    unsigned char *pixels;

    width = *(unsigned __int16 *)surface;
    height = *((unsigned __int16 *)surface + 1);
    pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
    if ( !pixels || x < 0 || y < 0 || x >= width || y >= height )
      return 0;
    return pixels[y * width + x];
  }
  method = RenderSurface_GetCompactMethodPointer(surface, 16);
  if ( !method )
    return 0;
  return ((int (__cdecl *)(_DWORD *, int, int))method)(surface, x, y);
}

CLASH95_INTERNAL void RenderSurface_WriteSoftwarePixel(_DWORD *surface, unsigned int x, unsigned int y, unsigned char color)
{
  unsigned int width;
  unsigned int height;
  unsigned char *pixels;

  if ( !RenderSurface_IsLinearSoftware(surface) || !surface[1] )
    return;
  width = *(unsigned __int16 *)surface;
  height = *((unsigned __int16 *)surface + 1);
  if ( x >= width || y >= height )
    return;
  pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  pixels[y * width + x] = color;
}

CLASH95_INTERNAL void RenderSurface_FillSoftwareRect(
        _DWORD *surface,
        unsigned int x0,
        unsigned int y0,
        unsigned int x1,
        unsigned int y1,
        unsigned char color)
{
  unsigned int width;
  unsigned int height;
  unsigned char *pixels;
  unsigned int y;

  if ( !RenderSurface_IsLinearSoftware(surface) || !surface[1] )
    return;
  width = *(unsigned __int16 *)surface;
  height = *((unsigned __int16 *)surface + 1);
  if ( !width || !height || x0 > x1 || y0 > y1 || x0 >= width || y0 >= height )
    return;
  if ( x1 >= width )
    x1 = width - 1;
  if ( y1 >= height )
    y1 = height - 1;
  pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  for ( y = y0; y <= y1; ++y )
    memset(pixels + y * width + x0, color, x1 - x0 + 1);
}

CLASH95_INTERNAL char *UnitType_GetLocalizedName(unit_type unitType)
{
  unsigned int language_index;

  if ( unitType == UNIT_TYPE_PEASANT )
  {
    language_index = (unsigned __int8)g_LanguageIndex;
    if ( language_index < 3 && g_UnitTypeMetadataRecordsStorage[language_index] )
      return g_UnitTypeMetadataRecordsStorage[language_index];
  }
  if ( unitType >= UNIT_TYPE_PEASANT && unitType < UNIT_TYPE_COUNT )
    return g_RecoveredUnitTypeEnglishNames[unitType];
  return "Unknown unit";
}

CLASH95_INTERNAL unsigned char UnitType_GetWorldMoveCost(int unit_type, int profile_offset)
{
  if ( unit_type < 0 || unit_type >= (int)(sizeof(g_UnitTypeWorldMoveCosts) / sizeof(g_UnitTypeWorldMoveCosts[0])) )
    return 0;
  if ( profile_offset < TERRAIN_MOVE_PROFILE_PLAIN_A || profile_offset > TERRAIN_MOVE_PROFILE_MOUNTAINS )
    return 0;
  return g_UnitTypeWorldMoveCosts[unit_type][profile_offset + 1];
}

CLASH95_INTERNAL unsigned char UnitType_GetRoadMoveCost(int unit_type)
{
  if ( unit_type < 0 || unit_type >= (int)(sizeof(g_UnitTypeWorldMoveCosts) / sizeof(g_UnitTypeWorldMoveCosts[0])) )
    return 0;
  return g_UnitTypeWorldMoveCosts[unit_type][0];
}

// idb


CLASH95_INTERNAL void Rules_EnsureObjectPatternVTable(void)
{
  static int initialized;

  if ( initialized )
    return;
  /*
   * Original data at 0x51A290 is a packed 32-bit callback vector beginning
   * with dword 7, followed by low-address function pointers.
   */
  g_Rules_ObjectPatternVTable[0] = 7;
  g_Rules_ObjectPatternVTable[1] = (int)(uintptr_t)Instance_PrintStaleOrClassLabel;
  g_Rules_ObjectPatternVTable[2] = (int)(uintptr_t)Instance_PrintNameOrDummyLabel;
  g_Rules_ObjectPatternVTable[3] = (int)(uintptr_t)Rules_UnmakeInstance;
  g_Rules_ObjectPatternVTable[4] = 0;
  g_Rules_ObjectPatternVTable[5] = (int)(uintptr_t)Rules_GetNextInstance;
  g_Rules_ObjectPatternVTable[6] = (int)(uintptr_t)Instance_DecrementBusyCount;
  g_Rules_ObjectPatternVTable[7] = (int)(uintptr_t)Rules_IncrementRefCountField40;
  g_Rules_ObjectPatternVTable[8] = (int)(uintptr_t)Instance_ReleaseSlotValueContainer;
  g_Rules_ObjectPatternVTable[9] = (int)(uintptr_t)Instance_AcquireLocalSlotArray;
  g_Rules_ObjectPatternVTable[10] = (int)(uintptr_t)Instance_NotifyCreated;
  initialized = 1;
}
