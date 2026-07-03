/* Batch 08: Compat render-state helpers, ExcString stubs, and
 * CAviDecompressor (AVI decompressor) pixel/row/lifecycle helpers. */

/* Real function used as a fake vtable-slot / row-blit callback target for
 * CAviDecompressor_BlitRows. Its address lives in the low, fixed .text
 * range of this non-PIE build, so truncating it into a _DWORD slot (as the
 * recovered 32-bit code does) and reading it back is safe. */
static void cov08_blit_row_cb(_DWORD *obj, char *row) {
  (void)obj;
  (void)row;
}

TEST(cov08_compat, render_state_method_pointer) {
  /* render_state is an "int" standing in for a 32-bit pointer in the
   * original binary; back it with a static buffer so its address survives
   * truncation to a DWORD and back on a 64-bit host. */
  static unsigned char rs[2048];
  static uintptr_t vt[8];
  int rs_addr;

  memset(rs, 0, sizeof rs);
  rs_addr = (int)(intptr_t)rs;

  /* field @ +1120 is zero -> null-vtable branch. */
  CHECK_EQ(Compat_RenderStateMethodPointer(rs_addr, 8), 0);

  /* Now populate the vtable pointer field and hit the non-null branch. */
  vt[0] = 0x1000;
  vt[1] = 0x2000;
  vt[2] = 0x3000;
  vt[3] = 0x4000;
  *(uint32_t *)(rs + 1120) = (uint32_t)(uintptr_t)vt;
  CHECK_EQ(Compat_RenderStateMethodPointer(rs_addr, 8), 0x3000);
}

TEST(cov08_compat, render_state_surface) {
  static unsigned char rs[256];
  int rs_addr;

  memset(rs, 0, sizeof rs);
  *(uint32_t *)(rs + 16) = 0xDEADBEEFu;
  rs_addr = (int)(intptr_t)rs;

  TOUCH(Compat_RenderStateSurface(rs_addr, 0));
  TOUCH(Compat_RenderStateSurface(rs_addr, 16));
}

TEST(cov08_compat, render_state_cursor_descriptor) {
  static unsigned char rs[256];
  int rs_addr;

  memset(rs, 0, sizeof rs);
  rs_addr = (int)(intptr_t)rs;

  /* field @ +60 starts zero -> sets the default descriptor (if-branch). */
  TOUCH(Compat_RenderStateCursorDescriptor(rs_addr));
  /* field is now non-zero -> skip-set branch. */
  TOUCH(Compat_RenderStateCursorDescriptor(rs_addr));
}

TEST(cov08_dd, get_surface_pitch) {
  /* Compat_RenderStateTailFields ignores its argument entirely and returns
   * a fixed static struct, so any int is safe here. */
  TOUCH(DD_GetSurfacePitch(0));
  TOUCH(DD_GetSurfacePitch(1234));
}

TEST(cov08_io, stream_adapter_read_stub) {
  CHECK_EQ(IO_StreamAdapterReadStub(), 0);
}

TEST(cov08_excstring, release_text) {
  _DWORD buf[4];
  memset(buf, 0, sizeof buf);
  TOUCH(ExcString_ReleaseText(buf));
  buf[0] = 0x1234;
  TOUCH(ExcString_ReleaseText(buf));
}

TEST(cov08_excstring, get_text_ptr) {
  static unsigned char buf[64];
  int addr;
  memset(buf, 0, sizeof buf);
  *(uint32_t *)buf = 0xCAFEBABEu;
  addr = (int)(intptr_t)buf;
  TOUCH(ExcString_GetTextPtr(addr));
}

TEST(cov08_excstring, get_text_ptr_dup) {
  static unsigned char buf[64];
  int addr;
  memset(buf, 0, sizeof buf);
  *(uint32_t *)buf = 0x11223344u;
  addr = (int)(intptr_t)buf;
  TOUCH(ExcString_GetTextPtrDup(addr));
}

TEST(cov08_excstring, release_text_dup) {
  _DWORD buf[4];
  memset(buf, 0, sizeof buf);
  TOUCH(ExcString_ReleaseTextDup(buf));
  buf[0] = 5;
  TOUCH(ExcString_ReleaseTextDup(buf));
}

TEST(cov08_excstring, get_error_code_stub) {
  CHECK_EQ(ExcString_GetErrorCodeStub(), 0);
}

TEST(cov08_excstring, get_error_code_stub_dup) {
  CHECK_EQ(ExcString_GetErrorCodeStubDup(), 0);
}

TEST(cov08_avi, convert_rgb888_to565_row) {
  unsigned char src[64];
  _WORD dst[16];
  int i;

  for (i = 0; i < (int)sizeof src; ++i)
    src[i] = (unsigned char)(i * 7 + 1);
  memset(dst, 0, sizeof dst);

  TOUCH(CAviDecompressor_ConvertRGB888to565Row(dst, (_DWORD *)src, 4));
}

TEST(cov08_avi, convert_rgb565_to888_row) {
  unsigned char src[32];
  unsigned char dst[64];
  int i;

  for (i = 0; i < (int)sizeof src; ++i)
    src[i] = (unsigned char)(i * 3 + 2);
  memset(dst, 0, sizeof dst);

  TOUCH(CAviDecompressor_ConvertRGB565to888Row((unsigned int *)dst,
                                                (_WORD *)src, 4));
}

TEST(cov08_avi, copy_pixel_row16bpp) {
  unsigned char src[64];
  unsigned char dst[64];
  memset(src, 0xAB, sizeof src);
  memset(dst, 0, sizeof dst);
  TOUCH(CAviDecompressor_CopyPixelRow16bpp(dst, src, 8));
}

TEST(cov08_avi, copy_pixel_row24bpp) {
  unsigned char src[64];
  unsigned char dst[64];
  memset(src, 0xCD, sizeof src);
  memset(dst, 0, sizeof dst);
  TOUCH(CAviDecompressor_CopyPixelRow24bpp(dst, src, 8));
}

TEST(cov08_avi, blit_rows_memcpy_branch) {
  _DWORD a1arr[8];
  unsigned char a2buf[64];
  unsigned char a3buf[64];

  memset(a1arr, 0, sizeof a1arr);
  a1arr[0] = 2; /* bytes-per-pixel-ish factor */
  a1arr[1] = 2; /* rows */
  a1arr[4] = 2; /* non-zero => straight qmemcpy branch */
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0x11, sizeof a3buf);

  TOUCH(CAviDecompressor_BlitRows(a1arr, (char *)a2buf, (char *)a3buf));
}

TEST(cov08_avi, blit_rows_callback_positive_strides) {
  _DWORD a1arr[8];
  unsigned char a2buf[64];
  unsigned char a3buf[64];

  memset(a1arr, 0, sizeof a1arr);
  a1arr[1] = 1; /* single row -> loop body executes exactly once */
  a1arr[2] = 4; /* positive vertical stride */
  a1arr[3] = 4; /* positive horizontal/row stride */
  a1arr[4] = 0; /* forces the per-row callback branch */
  a1arr[5] = (_DWORD)(uintptr_t)cov08_blit_row_cb;
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0x22, sizeof a3buf);

  TOUCH(CAviDecompressor_BlitRows(a1arr, (char *)a2buf, (char *)a3buf));
}

TEST(cov08_avi, blit_rows_callback_negative_strides) {
  _DWORD a1arr[8];
  unsigned char a2buf[64];
  unsigned char a3buf[64];

  memset(a1arr, 0, sizeof a1arr);
  a1arr[1] = 1;  /* single row: (rows-1)==0 keeps the negative-stride pointer
                    adjustments a no-op, so this stays memory-safe. */
  a1arr[2] = -4; /* negative vertical stride branch */
  a1arr[3] = -4; /* negative row stride branch */
  a1arr[4] = 0;
  a1arr[5] = (_DWORD)(uintptr_t)cov08_blit_row_cb;
  memset(a2buf, 0, sizeof a2buf);
  memset(a3buf, 0x33, sizeof a3buf);

  TOUCH(CAviDecompressor_BlitRows(a1arr, (char *)a2buf, (char *)a3buf));
}

TEST(cov08_avi, normalize_color_mask) {
  TOUCH(CAviDecompressor_NormalizeColorMask(6));
  TOUCH(CAviDecompressor_NormalizeColorMask(1));
  TOUCH(CAviDecompressor_NormalizeColorMask(0x80000000u));
}

TEST(cov08_avi, dtor) {
  _DWORD buf[4];
  memset(buf, 0, sizeof buf);
  TOUCH(CAviDecompressor_dtor(buf));
}

TEST(cov08_avi, init_source) {
  /* Forwards straight into a no-op stub (CAviDecompressor_ApplyDecoderFormatParams);
   * no dereference of a1/a2 happens, so plain ints are safe. */
  TOUCH(CAviDecompressor_InitSource(1, 2));
}

TEST(cov08_avi, set_background) {
  static unsigned char obj[2600];
  int base;
  _DWORD a2arr[4];

  memset(obj, 0, sizeof obj);
  base = (int)(intptr_t)obj;
  a2arr[0] = 1;
  a2arr[1] = 2;
  a2arr[2] = 3;
  a2arr[3] = 4;

  TOUCH(CAviDecompressor_SetBackground(&base, a2arr, 99));
}

TEST(cov08_avi, init_color_keys) {
  static unsigned char obj[2600];
  int base;

  memset(obj, 0, sizeof obj);
  base = (int)(intptr_t)obj;

  TOUCH(CAviDecompressor_InitColorKeys(&base, 10, 20));
}

TEST(cov08_avi, init_pos) {
  static unsigned char obj[2600];
  int base;

  memset(obj, 0, sizeof obj);
  base = (int)(intptr_t)obj;

  TOUCH(CAviDecompressor_InitPos(&base, 30, 40));
}

TEST(cov08_avi, init_rect) {
  static unsigned char obj[2600];
  int base;
  _DWORD a2arr[4];

  memset(obj, 0, sizeof obj);
  base = (int)(intptr_t)obj;
  a2arr[0] = 5;
  a2arr[1] = 6;
  a2arr[2] = 7;
  a2arr[3] = 8;

  TOUCH(CAviDecompressor_InitRect(&base, a2arr));
}

TEST(cov08_avi, init_and_done_thread_guard) {
  static unsigned char obj[256];
  int addr;

  memset(obj, 0, sizeof obj);
  addr = (int)(intptr_t)obj;

  TOUCH(CAviDecompressor_InitThreadGuard(addr));
  TOUCH(CAviDecompressor_DoneThreadGuard(addr));
}

TEST(cov08_avi, construct_event_handle) {
  HANDLE h1 = 0;
  HANDLE h2 = 0;

  TOUCH(CAviDecompressor_ConstructEventHandle(&h1, 1, 0));
  TOUCH(CAviDecompressor_ConstructEventHandle(&h2, 0, 1));
}

TEST(cov08_avi, free_members) {
  /* Both forward to a no-op stub and return an intentionally-undefined
   * value in the recovered code; only touch for coverage. */
  TOUCH(CAviDecompressor_FreeMemberA());
  TOUCH(CAviDecompressor_FreeMemberB());
}

TEST(cov08_avi, get_video_format) {
  static unsigned char obj[256];
  int addr;

  memset(obj, 0, sizeof obj);
  *(uint32_t *)(obj + 151) = 0x1234u;
  addr = (int)(intptr_t)obj;

  TOUCH(CAviDecompressor_GetVideoFormat(addr));
}

TEST(cov08_avi, release_video_codec) {
  _DWORD buf[8];
  memset(buf, 0, sizeof buf);
  /* *result == 0 keeps CAviDecompressor_CloseCodecHandle on its no-op path. */
  TOUCH(CAviDecompressor_ReleaseVideoCodec(buf, 5));
}
