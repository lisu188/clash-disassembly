#include "render/render_surface_view.h"

TEST(cpp_render_surface_view, reads_proven_base_offsets) {
  unsigned char storage[clash95::render::RenderSurfaceWithStrideView::kObjectSize] = {};
  const std::uint16_t width = 640;
  const std::uint16_t height = 480;
  const std::uint32_t pixels = 0x10203040u;
  const std::uint32_t methods = 0x50607080u;
  const std::int32_t stride = 640;

  std::memcpy(storage + clash95::render::RenderSurfaceView::kWidthOffset,
              &width, sizeof(width));
  std::memcpy(storage + clash95::render::RenderSurfaceView::kHeightOffset,
              &height, sizeof(height));
  std::memcpy(storage + clash95::render::RenderSurfaceView::kPixelBufferHandleOffset,
              &pixels, sizeof(pixels));
  std::memcpy(storage + clash95::render::RenderSurfaceView::kMethodTableHandleOffset,
              &methods, sizeof(methods));
  std::memcpy(storage + clash95::render::RenderSurfaceWithStrideView::kRowStrideOffset,
              &stride, sizeof(stride));

  clash95::render::RenderSurfaceWithStrideView view(storage);
  CHECK_EQ(view.base().width(), 640);
  CHECK_EQ(view.base().height(), 480);
  CHECK_EQ(view.base().pixelBufferHandle(), 0x10203040u);
  CHECK_EQ(view.base().methodTableHandle(), 0x50607080u);
  CHECK(view.base().hasPixelBuffer());
  CHECK_EQ(view.rowStride(), 640);
}

TEST(cpp_render_surface_view, writes_match_raw_storage_offsets) {
  unsigned char storage[clash95::render::RenderSurfaceWithStrideView::kObjectSize] = {};
  clash95::render::RenderSurfaceWithStrideMutableView view(storage);

  view.base().setDimensions(320, 200);
  view.base().setPixelBufferHandle(0x11223344u);
  view.base().setMethodTableHandle(0x55667788u);
  view.setRowStride(336);

  std::uint16_t raw_width = 0;
  std::uint16_t raw_height = 0;
  std::uint32_t raw_pixels = 0;
  std::uint32_t raw_methods = 0;
  std::int32_t raw_stride = 0;

  std::memcpy(&raw_width,
              storage + clash95::render::RenderSurfaceView::kWidthOffset,
              sizeof(raw_width));
  std::memcpy(&raw_height,
              storage + clash95::render::RenderSurfaceView::kHeightOffset,
              sizeof(raw_height));
  std::memcpy(&raw_pixels,
              storage + clash95::render::RenderSurfaceView::kPixelBufferHandleOffset,
              sizeof(raw_pixels));
  std::memcpy(&raw_methods,
              storage + clash95::render::RenderSurfaceView::kMethodTableHandleOffset,
              sizeof(raw_methods));
  std::memcpy(&raw_stride,
              storage + clash95::render::RenderSurfaceWithStrideView::kRowStrideOffset,
              sizeof(raw_stride));

  CHECK_EQ(raw_width, 320);
  CHECK_EQ(raw_height, 200);
  CHECK_EQ(raw_pixels, 0x11223344u);
  CHECK_EQ(raw_methods, 0x55667788u);
  CHECK_EQ(raw_stride, 336);

  view.base().clearPixelBufferHandle();
  CHECK(!view.readOnly().base().hasPixelBuffer());
}
