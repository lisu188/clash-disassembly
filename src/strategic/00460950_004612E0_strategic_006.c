/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE uintptr_t Compat_RenderStateMethodPointer (int render_state, unsigned int table_offset);
CLASH95_LOCAL int Compat_RenderClearPresentedRect (int render_state);

//----- (00460950) --------------------------------------------------------
BOOL  RenderState_IsCursorFlipStillActive(int render_state)
{
  int now; // eax
  int delta_x; // eax
  int delta_y; // eax

  if ( !DD_IsFlipping(render_state) )
    return 0;
  now = Time_Now(0, 0);
  if ( (unsigned int)(now - *(_DWORD *)(uintptr_t)(render_state + 68)) >= *(_DWORD *)(uintptr_t)(render_state + 1104) )
    return 0;
  delta_x = *(_DWORD *)(uintptr_t)(render_state + 72) - (*(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108));
  if ( delta_x <= 0 )
    delta_x = (*(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(render_state + 72);
  if ( delta_x >= *(_DWORD *)(uintptr_t)(render_state + 1116) )
    return 0;
  delta_y = *(_DWORD *)(uintptr_t)(render_state + 76) - (*(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108));
  if ( delta_y <= 0 )
    delta_y = (*(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(render_state + 76);
  return delta_y < *(_DWORD *)(uintptr_t)(render_state + 1116);
}

//----- (004609D0) --------------------------------------------------------
BOOL  Render_Begin(int render_state, void (*idle_callback)(void), ...)
{
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(render_state) )
    {
      result = DD_IsLost(render_state);
      if ( !result )
        break;
    }
    DD_Pump(render_state, (char)(intptr_t)idle_callback);
    if ( idle_callback )
      idle_callback();
  }
  return result;
}

//----- (00460A10) --------------------------------------------------------
BOOL  Render_FlipRect(int render_state, char a2)
{
  int previous_poll_state;
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(render_state) )
    {
      result = DD_IsLost(render_state);
      if ( !result )
        break;
    }
    previous_poll_state = *(_DWORD *)(uintptr_t)(render_state + 56);
    *(_DWORD *)(uintptr_t)(render_state + 56) = 0;
    Platform_PumpMessagesAndBlitFrame(a2);
    *(_DWORD *)(uintptr_t)(render_state + 56) = previous_poll_state;
    Compat_RenderStateInvokeMethod(render_state, 20);
  }
  return result;
}

//----- (00460A50) --------------------------------------------------------
int  RenderState_PollInputAndClampCursor(int render_state, int a2)
{
  _DWORD *state; // edx
  int scaled_delta_y; // eax
  int prev_cursor_y; // edi
  int min_x; // ecx
  int min_y; // ebx
  int max_x; // esi
  int result; // eax
  int max_y; // edi

  state = (_DWORD *)(uintptr_t)(unsigned int)render_state;
  InputBackend_PollState(&g_InputBackendState, render_state, a2);
  Compat_MenuProbeTraceRenderInput(
    "live-input",
    render_state,
    g_InputBackendState.mouse_delta_x,
    g_InputBackendState.mouse_delta_y,
    g_InputBackendState.mouse_button_primary,
    g_InputBackendState.mouse_button_secondary);
  state[9] += state[8] * g_InputBackendState.mouse_delta_x;
  scaled_delta_y = state[8] * g_InputBackendState.mouse_delta_y;
  prev_cursor_y = state[10];
  state[11] = 0;
  state[10] = scaled_delta_y + prev_cursor_y;
  if ( g_InputMousePrimaryButtonState < 0 )
    ++state[11];
  if ( g_InputMouseSecondaryButtonState < 0 )
    state[11] += 2;
  min_x = state[4];
  if ( state[9] < min_x )
    state[9] = min_x;
  min_y = state[5];
  if ( state[10] < min_y )
    state[10] = min_y;
  max_x = state[6];
  if ( state[9] > max_x )
    state[9] = max_x;
  result = state[10];
  max_y = state[7];
  if ( result > max_y )
    state[10] = max_y;
  Compat_SyncRenderCursorGlobals(state);
  return result;
}
// 460A66: variable 'v2' is possibly undefined
// 5451A8: using guessed type int dword_5451A8;
// 5451AC: using guessed type int dword_5451AC;
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;

//----- (00460AF0) --------------------------------------------------------
unsigned int  RenderState_WarpCursorAndPump(_DWORD *render_state, unsigned __int16 cursor_x, unsigned __int16 cursor_y)
{
  render_state[9] = cursor_x << render_state[277];
  render_state[10] = cursor_y << render_state[277];
  Compat_SyncRenderCursorGlobals(render_state);
  return DD_Pump((int)(intptr_t)render_state, cursor_y);
}

//----- (00460B20) --------------------------------------------------------
_DWORD * RenderState_RecalculateCursorBoundsForRect(
        _DWORD *result,
        __int16 rect_left,
        __int16 rect_right,
        __int16 rect_top,
        __int16 rect_bottom)
{
  _WORD *descriptor_words; // edx
  unsigned __int16 min_x; // si
  unsigned __int16 min_y; // bx
  unsigned __int16 max_x; // di
  __int16 v10; // cx

  descriptor_words = (_WORD *)(uintptr_t)result[15];
  min_x = descriptor_words[10] + 1 + rect_left;
  min_y = descriptor_words[12] + 1 + rect_top;
  max_x = rect_right - (descriptor_words[6] - descriptor_words[10] + 1);
  v10 = descriptor_words[8];
  LOWORD(descriptor_words) = descriptor_words[12];
  result[4] = min_x << result[277];
  result[5] = min_y << result[277];
  result[6] = max_x << result[277];
  result[7] = (unsigned __int16)(rect_bottom - (v10 - (_WORD)(intptr_t)descriptor_words + 1)) << result[277];
  return result;
}

//----- (00460BB0) --------------------------------------------------------
_DWORD * RenderState_PumpIfRectInViewBounds(
        _DWORD *result,
        unsigned __int16 rect_left,
        unsigned __int16 rect_right,
        unsigned __int16 rect_top,
        unsigned __int16 rect_bottom)
{
  int cursor_descriptor; // ebx

  cursor_descriptor = result[15];
  if ( *(_DWORD *)(uintptr_t)(cursor_descriptor + 12) + result[12] >= rect_left
    && rect_right >= (int)result[12]
    && result[13] + *(_DWORD *)(uintptr_t)(cursor_descriptor + 16) >= rect_top
    && rect_bottom >= (int)result[13] )
  {
    return (_DWORD *)(uintptr_t)Render_Pump();
  }
  return result;
}

//----- (00460C70) --------------------------------------------------------
_DWORD * RenderState_LoadDefaultCursorSprite(int render_state)
{
  _DWORD *result; // eax
  if ( *(_DWORD *)(uintptr_t)(render_state + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(uintptr_t)(render_state + 64));
  result = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, "mouse.s32");
    *(_DWORD *)(uintptr_t)(render_state + 64) = result;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(render_state + 64) = 0;
  }
  return result;
}

//----- (00460CB0) --------------------------------------------------------
_DWORD * RenderState_LoadOrRenderCursorLabelSprite(int render_state, int label_text, int a3 CLASH95_UNUSED, DWORD a4)
{
  unsigned __int8 *source_bytes; // eax
  unsigned __int8 checksum_xor; // bl
  unsigned __int16 checksum_sum; // cx
  int i; // edx
  unsigned __int8 current_byte; // bh
  int cache_query_handle;
  _DWORD *result; // eax
  CHAR cache_path[104]; // [esp+0h] [ebp-78h] BYREF
  CHAR query_path[104]; // [esp+68h] [ebp-10h] BYREF

  if ( *(_DWORD *)(uintptr_t)(render_state + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(uintptr_t)(render_state + 64));
  source_bytes = (unsigned __int8 *)(uintptr_t)label_text;
  checksum_xor = 0;
  checksum_sum = 0;
  for ( i = 0; i < 768; ++i )
  {
    current_byte = *source_bytes++;
    checksum_xor ^= current_byte;
    checksum_sum += current_byte;
  }
  sprintf_(cache_path, "cache\\m%02x%04x.s32", checksum_xor, checksum_sum);
  cache_query_handle = 0;
  if ( Res_ProbeGfxFileExists(cache_path, 0, a4, 0) )
  {
    strcpy(query_path, aGfx);
    strcat(query_path, cache_path);
    cache_query_handle = FileSystem_ResolveReadPath(query_path, 0);
    if ( cache_query_handle )
    {
      Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &cache_query_handle);
      result = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, a4);
      if ( result )
        result = DLXSpriteSet_Load(result, cache_path);
      *(_DWORD *)(uintptr_t)(render_state + 64) = result;
      return result;
    }
  }
  RenderState_LoadDefaultCursorSprite(render_state);
  DLXSpriteSet_DrawText(*(_DWORD *)(uintptr_t)(render_state + 64), -1, label_text, (unsigned __int8 *)(uintptr_t)(render_state + 80));
  result = *(_DWORD **)(uintptr_t)(render_state + 64);
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00460D80) --------------------------------------------------------
CLASH95_TEST_VISIBLE uintptr_t Compat_RenderStateMethodPointer(int render_state, unsigned int table_offset)
{
  uintptr_t *vtable;

  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(render_state + 1120);
  if ( !vtable )
    return 0;
  return vtable[table_offset / 4];
}

CLASH95_INTERNAL void Compat_RenderStateInvokeMethod(int render_state, unsigned int table_offset)
{
  uintptr_t method_ptr;

  method_ptr = Compat_RenderStateMethodPointer(render_state, table_offset);
  if ( method_ptr )
    ((void (*)(int))(uintptr_t)method_ptr)(render_state);
}

CLASH95_INTERNAL _DWORD *Compat_RenderStateSurface(int render_state, unsigned int field_offset)
{
  return (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(render_state + field_offset);
}

CLASH95_INTERNAL _DWORD *Compat_RenderStateCursorDescriptor(int render_state)
{
  unsigned int descriptor_handle;

  descriptor_handle = (unsigned int)*(_DWORD *)(uintptr_t)(render_state + 60);
  if ( !descriptor_handle )
  {
    descriptor_handle = (unsigned int)(uintptr_t)g_RenderVideoInitCursorDescriptor;
    *(_DWORD *)(uintptr_t)(render_state + 60) = descriptor_handle;
  }
  return (_DWORD *)(uintptr_t)descriptor_handle;
}

CLASH95_INTERNAL void Compat_PresentPrimaryIndexedSurfaceToPlatform(void)
{
  unsigned int primary_surface_handle;

  primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
  if ( primary_surface_handle )
  {
    Platform_PresentRecoveredIndexedSurfaceHandle(
      (void *)(uintptr_t)primary_surface_handle,
      (const uint32_t *)(const void *)((unsigned char *)&g_MainRenderDevice + 220));
  }
}

CLASH95_LOCAL int Compat_RenderClearPresentedRect(int render_state)
{
  _DWORD *present_surface;
  _DWORD *cursor_descriptor;
  int resource_handle;

  if ( !g_CursorOverlayPresented )
    return g_CursorOverlayPresented;
  g_CursorOverlayPresented = 0;
  resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
  present_surface = Compat_RenderStateSurface(render_state, 8);
  cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
  Render_FillRect(
    present_surface,
    0,
    0,
    0,
    *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
    *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
    *(unsigned __int16 *)(uintptr_t)render_state,
    *(unsigned __int16 *)(uintptr_t)(render_state + 4));
  return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, resource_handle);
}

__int16  RenderState_SelectCursorDescriptor(int render_state, int new_descriptor)
{
  int descriptor;
  int result;
  int active_descriptor;
  unsigned int sprite_index;
  unsigned __int16 max_height;
  unsigned __int16 max_width;
  unsigned __int16 sprite_height;
  unsigned __int16 sprite_width;
  unsigned char was_presenting;

  result = render_state;
  active_descriptor = new_descriptor;
  if ( !active_descriptor )
    active_descriptor = *(_DWORD *)(uintptr_t)(render_state + 60);
  if ( active_descriptor )
    g_ActiveCursorDescriptorPtr = active_descriptor;
  if ( new_descriptor == *(_DWORD *)(uintptr_t)(render_state + 60) )
    return result;
  was_presenting = (unsigned char)g_CursorOverlayPresented;
  if ( was_presenting )
    Compat_RenderClearPresentedRect(render_state);
  *(_DWORD *)(uintptr_t)(render_state + 60) = new_descriptor;
  descriptor = *(_DWORD *)(uintptr_t)(render_state + 60);
  max_height = 0;
  max_width = 0;
  for ( sprite_index = *(unsigned __int16 *)(uintptr_t)descriptor; sprite_index <= (unsigned int)*(int *)(uintptr_t)(descriptor + 4); ++sprite_index )
  {
    sprite_height = DLX_GetSpriteHeight(*(_DWORD *)(uintptr_t)(render_state + 64), (int)sprite_index);
    sprite_width = DLX_GetSpriteWidth(*(_DWORD *)(uintptr_t)(render_state + 64), (int)sprite_index);
    if ( sprite_height > max_height )
      max_height = sprite_height;
    if ( sprite_width > max_width )
      max_width = sprite_width;
  }
  *(_DWORD *)(uintptr_t)(descriptor + 12) = max_height;
  *(_DWORD *)(uintptr_t)(descriptor + 16) = max_width;
  *(_DWORD *)(uintptr_t)(descriptor + 32) = 0;
  *(_DWORD *)(uintptr_t)(descriptor + 28) = 0;
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)(uintptr_t)render_state, 0, 640, 0, 480);
  Compat_RenderStateInvokeMethod(render_state, 20);
  Compat_RenderStateInvokeMethod(render_state, 4);
  *(_DWORD *)(uintptr_t)(render_state + 48) = (*(int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(descriptor + 20);
  *(_DWORD *)(uintptr_t)(render_state + 52) = (*(int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108)) - *(_DWORD *)(uintptr_t)(descriptor + 24);
  if ( was_presenting )
    result = Render_Present(render_state);
  return result;
}
// 544D10: using guessed type int dword_544D10;

//----- (00460EA0) --------------------------------------------------------
int  Render_Present(int render_state)
{
  _DWORD *cursor_descriptor;
  _DWORD *present_surface;
  int result; // eax
  int resource_handle; // edi
  int SpriteForChar; // eax
  void *saved_render_device; // [esp+1Ch] [ebp-Ch]

  present_surface = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(render_state + 8);
  cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
  result = g_CursorOverlayPresented;
  if ( !g_CursorOverlayPresented )
  {
    resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
    g_CursorOverlayPresented = 1;
    saved_render_device = g_RenderDevice;
    Render_FillRect(
      0,
      present_surface,
      *(unsigned __int16 *)(uintptr_t)(render_state + 52),
      *(unsigned __int16 *)(uintptr_t)(render_state + 48),
      *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(uintptr_t)(render_state + 48) - 1,
      *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(uintptr_t)(render_state + 52) - 1,
      0,
      0);
    g_RenderDevice = &g_MainRenderDevice;
    SpriteForChar = DLX_GetSpriteForChar(
                      *(_DWORD *)(uintptr_t)(render_state + 64),
                      *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
    /*
     * Original 0x00460F32: `mov ebx,[esi+30h]` / `mov ecx,[esi+34h]` /
     * `mov eax,ds:g_RenderDevice` / `mov ebp,[eax+0B8h]` /
     * `call dword ptr [ebp+34h]` with stack args 0,0,1,-1,-1,-1,-1.
     * ebx = render_state+48 (cursor x) -> left, ecx = render_state+52
     * (cursor y) -> top, edx = the sprite, the `1` push -> draw_mode.
     * The decompiler dropped the indirect call; route it through the
     * sanctioned native seam like the other converted +0B8h/+34h callers.
     */
    Compat_RenderDeviceDrawMenuSprite(
      *(_DWORD *)(uintptr_t)(render_state + 48),
      *(_DWORD *)(uintptr_t)(render_state + 52),
      SpriteForChar,
      1);
    *(_DWORD *)(uintptr_t)render_state = *(_DWORD *)(uintptr_t)(render_state + 48);
    *(_DWORD *)(uintptr_t)(render_state + 4) = *(_DWORD *)(uintptr_t)(render_state + 52);
    g_RenderDevice = saved_render_device;
    result = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, resource_handle);
    Compat_PresentPrimaryIndexedSurfaceToPlatform();
    return result;
  }
  Compat_PresentPrimaryIndexedSurfaceToPlatform();
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544D10: using guessed type int dword_544D10;

//----- (00460F90) --------------------------------------------------------
int Render_Pump(void)
{
  _DWORD *cursor_descriptor;
  _DWORD *present_surface;
  int result; // eax
  int render_state;
  int resource_handle; // esi

  result = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    g_CursorOverlayPresented = 0;
    resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 0);
    render_state = (int)(intptr_t)g_RenderState;
    present_surface = Compat_RenderStateSurface(render_state, 8);
    cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
    Render_FillRect(
      present_surface,
      0,
      0,
      0,
      *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
      *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
      *(_WORD *)(uintptr_t)render_state,
      *(_WORD *)(uintptr_t)(render_state + 4));
    return Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, resource_handle);
  }
  return result;
}
// 544D10: using guessed type int dword_544D10;

//----- (00461000) --------------------------------------------------------
void Input_Flush(void)
{
  g_CursorOverlayPresented = 0;
}
// 544D10: using guessed type int dword_544D10;

//----- (004610B0) --------------------------------------------------------
int  RenderState_DrawCursorSpriteToPrimarySurface(int render_state)
{
  void *saved_render_device; // esi
  int SpriteForChar; // eax
  int result; // eax

  saved_render_device = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, &g_CursorSpritePalette);
  SpriteForChar = DLX_GetSpriteForChar(*(_DWORD *)(uintptr_t)(render_state + 64), g_CursorDesc_Busy[0] + 1);
  result = Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  g_RenderDevice = saved_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519808: using guessed type int dword_519808;

//----- (00461140) --------------------------------------------------------
_DWORD * Device_GetParamA(int render_state, int a2)
{
  _DWORD *result; // eax
  CompatRenderStateTail *tail;

  result = RenderState_ConstructDefault(render_state, a2);
  result[280] = g_Device_Vtable;
  tail = Compat_RenderStateTailFields(render_state);
  tail->field_464_active = 0;
  tail->field_468_active = 0;
  tail->field_46C_ticks = 0;
  tail->field_470_ticks = 0;
  tail->field_474_handle = 0;
  Compat_SyncRenderCursorGlobals(result);
  return result;
}
// 50F204: using guessed type int (*off_50F204[6])();

//----- (00461170) --------------------------------------------------------
int  Device_DoOp(int render_state, int a2, DWORD a3)
{
  CompatRenderStateTail *tail;
  int record_handle;

  (void)a2;
  tail = Compat_RenderStateTailFields(render_state);
  tail->field_464_active = 1;
  tail->field_46C_ticks = Time_Now(0, 0);
  record_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aWb_7, 0, a3);
  return fclose_(record_handle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004611A0) --------------------------------------------------------
__int16  Device_GetParamB(int render_state, DWORD a2, int a3, int a4)
{
  CompatRenderStateTail *tail;
  unsigned int current_x;
  unsigned int current_y;
  int current_flags;
  _DWORD elapsed_ticks;
  int record_handle;

  (void)a3;
  (void)a4;
  tail = Compat_RenderStateTailFields(render_state);
  if ( tail->field_464_active )
  {
    current_flags = *(_DWORD *)(uintptr_t)(render_state + 44);
    current_x = *(unsigned int *)(uintptr_t)(render_state + 36) >> *(_BYTE *)(uintptr_t)(render_state + 1108);
    current_y = *(unsigned int *)(uintptr_t)(render_state + 40) >> *(_BYTE *)(uintptr_t)(render_state + 1108);
    if ( (unsigned __int8)g_DeviceRecordLastFlipLostState != current_flags
      || current_x != (unsigned __int16)g_DeviceRecordLastX
      || current_y != (unsigned __int16)g_DeviceRecordLastY )
    {
      g_DeviceRecordLastX = *(_WORD *)(uintptr_t)(render_state + 36);
      g_DeviceRecordLastY = *(_WORD *)(uintptr_t)(render_state + 40);
      g_DeviceRecordLastFlipLostState = (unsigned char)(2 * (DD_IsFlipping(render_state) + DD_IsLost(render_state)));
      elapsed_ticks = Time_Now(0, 0) - tail->field_46C_ticks;
      record_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aAb, 1, a2);
      fwrite_(&g_DeviceRecordLastX, 2, record_handle, 1);
      fwrite_(&g_DeviceRecordLastY, 2, record_handle, 1);
      fwrite_(&g_DeviceRecordLastFlipLostState, 1, record_handle, 1);
      fwrite_(&elapsed_ticks, 4, record_handle, 1);
      return fclose_(record_handle);
    }
  }
  return 0;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 544CBA: using guessed type __int16 word_544CBA;
// 544CBC: using guessed type __int16 word_544CBC;
// 544CBE: using guessed type char byte_544CBE;

//----- (004612A0) --------------------------------------------------------
int  Device_SetParamA(int render_state, DWORD a2)
{
  CompatRenderStateTail *tail;

  tail = Compat_RenderStateTailFields(render_state);
  tail->field_468_active = 1;
  tail->field_470_ticks = Time_Now(0, 0);
  tail->field_474_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aRb_9, 0, a2);
  return tail->field_474_handle;
}

//----- (004612E0) --------------------------------------------------------
int  Device_UpdateRect(_DWORD *render_state, int a2, int a3)
{
  CompatRenderStateTail *tail;
  int now; // eax
  char v5; // bl
  int segment_start_ticks; // ecx
  unsigned int elapsed_ticks; // edx
  int replay_handle; // ecx
  int trigger_count; // edx
  int trigger_index; // eax
  int result; // eax
  int message_id; // edi
  unsigned int tween_fraction; // ecx

  tail = Compat_RenderStateTailFields((int)(intptr_t)render_state);
  Compat_MenuProbeTraceRenderInput(
    "device-update",
    (int)(intptr_t)render_state,
    a2,
    a3,
    tail->field_470_ticks,
    tail->field_474_handle);
  if ( !tail->field_468_active )
    return RenderState_PollInputAndClampCursor((int)(intptr_t)render_state, a3);
  now = Time_Now(a3, a2);
  v5 = g_DeviceRectTweenTimeBase;
  segment_start_ticks = tail->field_470_ticks;
  elapsed_ticks = now - segment_start_ticks - g_DeviceRectTweenTimeBase;
  if ( elapsed_ticks < g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick )
  {
    tween_fraction = ((Time_Now(segment_start_ticks, elapsed_ticks) - tail->field_470_ticks - g_DeviceRectTweenTimeBase) << 8)
        / (unsigned int)(g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick);
    render_state[9] = (unsigned __int16)g_DeviceRectLastWidth
          + ((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)
                 - (__CFSHL__((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31, 8)
                  + ((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31 << 8))) >> 8);
    result = (unsigned __int16)g_RenderCursor_TweenPrevY
           + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction
                  - (__CFSHL__((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction) >> 31, 8)
                   + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction) >> 31 << 8))) >> 8);
    render_state[10] = result;
    Compat_SyncRenderCursorGlobals(render_state);
  }
  else
  {
    g_DeviceRectTweenTimeBase = Time_Now(segment_start_ticks, elapsed_ticks) - tail->field_470_ticks;
    g_DeviceReplaySegmentBaseTick = g_DeviceReplaySegmentTargetTick;
    g_DeviceRectLastWidth = g_DeviceRectTargetWidth;
    g_RenderCursor_TweenPrevY = g_DeviceRectTargetHeight;
    render_state[9] = (unsigned __int16)g_DeviceRectTargetWidth;
    render_state[10] = (unsigned __int16)g_DeviceRectTargetHeight;
    Compat_SyncRenderCursorGlobals(render_state);
    replay_handle = tail->field_474_handle;
    render_state[11] = (unsigned __int8)g_DemoPlaybackCursorButtonState;
    if ( (*(_BYTE *)(uintptr_t)(replay_handle + 12) & 0x10) == 0 )
    {
      fread_();
      fread_();
      fread_();
      v5 = 1;
      fread_();
    }
    trigger_count = 0;
    trigger_index = 0;
    if ( g_DemoScript_TriggerTickTable[0] != -1 )
    {
      while ( g_DemoScriptCurrentTick != g_DemoScript_TriggerTickTable[trigger_index] )
      {
        message_id = g_DemoScript_MessageIdTable[trigger_index++];
        ++trigger_count;
        if ( message_id == -1 )
          goto LABEL_8;
      }
      Demo_ShowNumberedTextScreen(v5, g_DemoScriptCurrentTick);
    }
LABEL_8:
    result = Input_IsKeyPressed(1);
    if ( result )
      App_RequestQuit((int)(intptr_t)&g_App_QuitReason_DemoSkipKey);
    ++g_DemoScriptCurrentTick;
  }
  return result;
}
// 519620: using guessed type __int16 word_519620;
// 519622: using guessed type __int16 word_519622;
// 519624: using guessed type __int16 word_519624;
// 519626: using guessed type __int16 word_519626;
// 519628: using guessed type int dword_519628[];
// 51962C: using guessed type int dword_51962C[];
// 544CC0: using guessed type int dword_544CC0;
// 544CC4: using guessed type int dword_544CC4;
// 544CC8: using guessed type int dword_544CC8;
// 544CCC: using guessed type char byte_544CCC;
// 544CD0: using guessed type int dword_544CD0;
