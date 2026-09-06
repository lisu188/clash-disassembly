/* cov00: RenderSurface method-dispatch / palette / cursor / misc cluster */

/* ---- Runtime_DescriptorNoop --------------------------------------- */
TEST(cov00_runtime, descriptor_noop) {
  CHECK_EQ(Runtime_DescriptorNoop(), 0);
}

/* ---- RenderSurface_GetCompactMethodPointer ------------------------- */
TEST(cov00_rsurf, get_compact_method_pointer) {
  static _DWORD surface[64];
  memset(surface, 0, sizeof surface);

  /* surface == NULL */
  CHECK_EQ(RenderSurface_GetCompactMethodPointer(NULL, 0), 0);

  /* surface valid, vtable == 0 */
  CHECK_EQ(RenderSurface_GetCompactMethodPointer(surface, 4), 0);

  /* surface valid, vtable != 0: read straight out of a real global table,
   * without ever calling through the returned value (safe). */
  surface[46] = (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable;
  TOUCH(RenderSurface_GetCompactMethodPointer(surface, 0));
  TOUCH(RenderSurface_GetCompactMethodPointer(surface, 4));
}

/* ---- RenderSurface_InvokeSlot0 / 36 / 48LoadPCX -------------------- */
TEST(cov00_rsurf, invoke_slots) {
  static _DWORD fakeVt[64];
  static _DWORD surfZero[64];
  static _DWORD surfCalls[64];
  char path[16];

  memset(fakeVt, 0, sizeof fakeVt);
  memset(surfZero, 0, sizeof surfZero);
  memset(surfCalls, 0, sizeof surfCalls);
  strcpy(path, "x.pcx");

  /* fakeVt slots point at a real no-arg function that ignores whatever
   * extra args the callers pass on the stack/registers -- safe to invoke
   * with mismatched signatures. */
  fakeVt[0] = (unsigned int)(uintptr_t)Runtime_DescriptorNoop;  /* offset 0  */
  fakeVt[9] = (unsigned int)(uintptr_t)Runtime_DescriptorNoop;  /* offset 36 */
  fakeVt[12] = (unsigned int)(uintptr_t)Runtime_DescriptorNoop; /* offset 48 */
  surfCalls[46] = (unsigned int)(uintptr_t)fakeVt;

  /* surface == NULL */
  CHECK_EQ(RenderSurface_InvokeSlot0(NULL, 1), 0);
  CHECK_EQ(RenderSurface_InvokeSlot36(NULL), 0);
  CHECK_EQ(RenderSurface_InvokeSlot48LoadPCX(NULL, path, 0, 0), 0);

  /* surface valid, vtable == 0 -> method == 0 */
  CHECK_EQ(RenderSurface_InvokeSlot0(surfZero, 1), 0);
  CHECK_EQ(RenderSurface_InvokeSlot36(surfZero), 0);
  CHECK_EQ(RenderSurface_InvokeSlot48LoadPCX(surfZero, path, 0, 0), 0);

  /* surface valid, vtable + slot both populated -> actually calls through */
  TOUCH(RenderSurface_InvokeSlot0(surfCalls, 1));
  TOUCH(RenderSurface_InvokeSlot36(surfCalls));
  TOUCH(RenderSurface_InvokeSlot48LoadPCX(surfCalls, path, 1, 0));
}

/* ---- RenderHandle_InvokeCopyDispatch -------------------------------- */
TEST(cov00_rsurf, invoke_copy_dispatch) {
  static unsigned char handleBuf[256];
  int source_handle;

  memset(handleBuf, 0, sizeof handleBuf);
  source_handle = (int)(intptr_t)(uintptr_t)handleBuf;

  /* dispatch_fn == 0 */
  *(_DWORD *)(handleBuf + 172) = 0;
  CHECK_EQ(RenderHandle_InvokeCopyDispatch(source_handle, source_handle), 0);

  /* dispatch_fn != 0 -> calls through (ignored args, safe) */
  *(_DWORD *)(handleBuf + 172) = (unsigned int)(uintptr_t)Runtime_DescriptorNoop;
  TOUCH(RenderHandle_InvokeCopyDispatch(source_handle, source_handle));
}

/* ---- RenderSurface_InvokeSlot16ReadPixel --------------------------- */
TEST(cov00_rsurf, invoke_slot16_read_pixel) {
  static _DWORD surfaceLinear[64];
  static _DWORD surfaceOther[64];
  static _DWORD fakeVt[64];
  static unsigned char pixels[64];

  memset(surfaceLinear, 0, sizeof surfaceLinear);
  memset(surfaceOther, 0, sizeof surfaceOther);
  memset(fakeVt, 0, sizeof fakeVt);
  memset(pixels, 0, sizeof pixels);
  pixels[1 * 4 + 1] = 0x42; /* pixel at (1,1) for a width-4 surface */

  /* surface == NULL */
  CHECK_EQ(RenderSurface_InvokeSlot16ReadPixel(NULL, 0, 0), 0);

  /* linear software surface, in-bounds read */
  surfaceLinear[0] = 4u | (4u << 16); /* width=4 height=4 */
  surfaceLinear[1] = (unsigned int)(uintptr_t)pixels;
  surfaceLinear[46] = (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable;
  CHECK_EQ(RenderSurface_InvokeSlot16ReadPixel(surfaceLinear, 1, 1), 0x42);

  /* linear software surface, out-of-bounds read */
  CHECK_EQ(RenderSurface_InvokeSlot16ReadPixel(surfaceLinear, -1, 0), 0);
  CHECK_EQ(RenderSurface_InvokeSlot16ReadPixel(surfaceLinear, 100, 0), 0);

  /* not linear software, vtable == 0 -> method == 0 */
  CHECK_EQ(RenderSurface_InvokeSlot16ReadPixel(surfaceOther, 0, 0), 0);

  /* not linear software, vtable + slot populated -> calls through */
  fakeVt[4] = (unsigned int)(uintptr_t)Runtime_DescriptorNoop; /* offset 16 */
  surfaceOther[46] = (unsigned int)(uintptr_t)fakeVt;
  TOUCH(RenderSurface_InvokeSlot16ReadPixel(surfaceOther, 2, 2));
}

/* ---- RenderSurface_WriteSoftwarePixel ------------------------------ */
TEST(cov00_rsurf, write_software_pixel) {
  static _DWORD surface[64];
  static unsigned char pixels[64];

  memset(surface, 0, sizeof surface);
  memset(pixels, 0, sizeof pixels);

  /* not linear software -> early return */
  RenderSurface_WriteSoftwarePixel(surface, 0, 0, 7);

  /* linear software, but no pixel buffer -> early return */
  surface[46] = (unsigned int)(uintptr_t)g_Surface_RawBuffer8Vtable;
  RenderSurface_WriteSoftwarePixel(surface, 0, 0, 7);

  /* linear software, valid pixel buffer, out-of-bounds -> early return */
  surface[0] = 4u | (4u << 16);
  surface[1] = (unsigned int)(uintptr_t)pixels;
  RenderSurface_WriteSoftwarePixel(surface, 10, 10, 7);

  /* linear software, valid pixel buffer, in-bounds write */
  RenderSurface_WriteSoftwarePixel(surface, 2, 2, 0x55);
  CHECK_EQ(pixels[2 * 4 + 2], 0x55);
}

/* ---- UnitType_GetWorldMoveCost -------------------------------------- */
TEST(cov00_unit, world_move_cost) {
  /* unit_type out of range */
  CHECK_EQ(UnitType_GetWorldMoveCost(-1, 0), 0);
  CHECK_EQ(UnitType_GetWorldMoveCost(100000, 0), 0);

  /* profile_offset out of range */
  CHECK_EQ(UnitType_GetWorldMoveCost(0, -100), 0);
  CHECK_EQ(UnitType_GetWorldMoveCost(0, 100000), 0);

  /* in-range on both axes */
  TOUCH(UnitType_GetWorldMoveCost(0, 0));
  TOUCH(UnitType_GetWorldMoveCost(1, 1));
}

/* ---- PathEntryArray_ConstructCapacity256 ---------------------------- */
TEST(cov00_path, construct_capacity256) {
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  TOUCH(PathEntryArray_ConstructCapacity256(buf));
}

/* ---- Palette_QuantizeChannelsInPlace -------------------------------- */
TEST(cov00_pal, quantize_channels_in_place) {
  static unsigned char buf[1024];
  int i;
  for (i = 0; i < 1024; ++i) buf[i] = (unsigned char)(i * 37);

  TOUCH(Palette_QuantizeChannelsInPlace(buf, 0));
  TOUCH(Palette_QuantizeChannelsInPlace(buf, 3));
  TOUCH(Palette_QuantizeChannelsInPlace(buf, 8));
}

/* ---- Palette_LoadFromQueryHandle ------------------------------------ */
TEST(cov00_pal, load_from_query_handle) {
  /* palette_table == NULL -> early return, no file I/O attempted */
  CHECK_EQ(Palette_LoadFromQueryHandle(0, 0), 0);
}

/* ---- Palette_ExpandRGBTripletsToTable -------------------------------- */
TEST(cov00_pal, expand_rgb_triplets_to_table) {
  static _DWORD dest[300];
  memset(dest, 0, sizeof dest);
  /* a2 == 0 query handle: Compat_QueryRead bails out immediately (safe),
   * the write loop still runs over the (uninitialized) local staging
   * buffer purely for coverage. */
  TOUCH(Palette_ExpandRGBTripletsToTable((int)(intptr_t)(uintptr_t)dest, 0, 0));
}

/* ---- Palette_BuildGrayscaleIdentityTable ----------------------------- */
TEST(cov00_pal, build_grayscale_identity_table) {
  static _DWORD dest[300];
  memset(dest, 0, sizeof dest);
  TOUCH(Palette_BuildGrayscaleIdentityTable((int)(intptr_t)(uintptr_t)dest));
}

/* ---- Str_CompactSkippingZeroBytes ------------------------------------ */
TEST(cov00_str, compact_skipping_zero_bytes) {
  unsigned char src[16] = { 0, 0, 'a', 0, 'b', 'c', 0, 0, 'd', 0, 0, 0, 0, 0, 0, 0 };
  unsigned char dst[16];
  memset(dst, 0, sizeof dst);

  TOUCH(Str_CompactSkippingZeroBytes(dst, src, 9));

  /* a3 == 0: loop body never runs */
  TOUCH(Str_CompactSkippingZeroBytes(dst, src, 0));

  /* all zero bytes up to the count -> exercises the early-return-inside
   * the skip loop path */
  {
    unsigned char allzero[8];
    memset(allzero, 0, sizeof allzero);
    TOUCH(Str_CompactSkippingZeroBytes(dst, allzero, 8));
  }
}

/* ---- Compat_DirectDrawSurfaceHandleIsLost ---------------------------- */
TEST(cov00_compat, ddsurface_handle_is_lost) {
  static unsigned char handleBuf[256];
  static unsigned char fakeDDSurface[256];
  int surface_handle;

  memset(handleBuf, 0, sizeof handleBuf);
  memset(fakeDDSurface, 0, sizeof fakeDDSurface);

  /* surface_handle == 0 */
  CHECK_EQ(Compat_DirectDrawSurfaceHandleIsLost(0), 0);

  surface_handle = (int)(intptr_t)(uintptr_t)handleBuf;

  /* direct_draw_surface == 0 */
  *(_DWORD *)(handleBuf + 164) = 0;
  CHECK_EQ(Compat_DirectDrawSurfaceHandleIsLost(surface_handle), 0);

  /* direct_draw_surface != 0 -> calls through to the DDraw compat shim */
  *(_DWORD *)(handleBuf + 164) = (unsigned int)(uintptr_t)fakeDDSurface;
  TOUCH(Compat_DirectDrawSurfaceHandleIsLost(surface_handle));
}

/* ---- Palette_SetBrightnessOffset ------------------------------------- */
TEST(cov00_pal, set_brightness_offset) {
  static unsigned char buf[256];
  int result_addr;
  memset(buf, 0, sizeof buf);
  result_addr = (int)(intptr_t)(uintptr_t)buf;

  CHECK_EQ(Palette_SetBrightnessOffset(result_addr, 5), result_addr);
  CHECK_EQ(*(int *)(buf + 216), 5);
}

/* ---- Palette_CrossfadeToTarget --------------------------------------- */
TEST(cov00_pal, crossfade_to_target) {
  static int a1buf[600];
  static unsigned char a2buf[1024];
  int i;

  memset(a1buf, 0, sizeof a1buf);
  for (i = 0; i < 1024; ++i) a2buf[i] = (unsigned char)(i * 3);

  /* a3 < 0: loop body never executes */
  TOUCH(Palette_CrossfadeToTarget(a1buf, a2buf, -1));

  /* a3 >= 0: loop runs, exercising Palette_CrossfadeStep multiple times
   * (including the a3==0 qmemcpy-priming branch on the first iteration). */
  TOUCH(Palette_CrossfadeToTarget(a1buf, a2buf, 2));
}

/* ---- Sprite_DrawSimpleIgnoringRect ------------------------------------ */
TEST(cov00_sprite, draw_simple_ignoring_rect) {
  /* a1 (sprite pointer) == 0 makes Compat_RenderDeviceDrawMenuSprite bail
   * out immediately via its `!sprite_for_char` guard -- safe regardless of
   * renderer/global state. */
  TOUCH(Sprite_DrawSimpleIgnoringRect(0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 1));
}

/* ---- SurfaceCursor_Get*Unbounded / GetOffsetZero ---------------------- */
TEST(cov00_cursor, unbounded_and_zero) {
  CHECK_EQ(SurfaceCursor_GetIncrUnbounded(), 0x7FFFFFFF);
  CHECK_EQ(SurfaceCursor_GetExtentUnbounded(), 0x7FFFFFFF);
  CHECK_EQ(SurfaceCursor_GetOffsetZero(), 0);
}

/* ---- RenderSurface_GetBlitCursor* / AdvanceBlitCursor ----------------- */
TEST(cov00_cursor, blit_cursor) {
  static unsigned char buf[64];
  int addr;
  memset(buf, 0, sizeof buf);
  addr = (int)(intptr_t)(uintptr_t)buf;

  *(_DWORD *)(buf + 8) = 42;
  CHECK_EQ(RenderSurface_GetBlitCursorRowStride(addr), 42);

  CHECK_EQ(RenderSurface_GetBlitCursorCapacity(), 0x7FFFFFFF);

  *(_DWORD *)(buf + 4) = 5;
  CHECK_EQ(RenderSurface_AdvanceBlitCursor(addr, 3), addr);
  CHECK_EQ(*(_DWORD *)(buf + 4), 8);

  CHECK_EQ(RenderSurface_GetBlitCursorPosition(addr), 8);
}

/* ---- RenderSurface_GetLinkedBlitCursor* / AdvanceLinkedBlitCursor ----- */
TEST(cov00_cursor, linked_blit_cursor) {
  static unsigned char buf[64];
  int addr;
  memset(buf, 0, sizeof buf);
  addr = (int)(intptr_t)(uintptr_t)buf;

  CHECK_EQ(RenderSurface_GetLinkedBlitCursorCapacity(), 0x7FFFFFFF);

  *(_DWORD *)(buf + 8) = 7;
  CHECK_EQ(RenderSurface_AdvanceLinkedBlitCursor(addr, 3), addr);
  CHECK_EQ(*(_DWORD *)(buf + 8), 10);

  CHECK_EQ(RenderSurface_GetLinkedBlitCursorPosition(addr), 10);
}

/* ---- RenderSurface_CloneInternalArray --------------------------------- */
TEST(cov00_rsurf, clone_internal_array) {
  static unsigned char buf[64];
  memset(buf, 0, sizeof buf);
  TOUCH(RenderSurface_CloneInternalArray(buf));
}
