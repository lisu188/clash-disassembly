#include "render/render_surface_tracking_view.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace {

template <typename T>
void storeValue(std::byte *bytes, std::size_t offset, T value) {
  std::memcpy(bytes + offset, &value, sizeof(value));
}

}

TEST(cpp_render_surface_tracking_view, reads_stride_dirty_and_resource_fields) {
  using clash95::render::RenderSurfaceTrackingView;
  using clash95::render::RenderSurfaceWithStrideView;

  std::array<std::byte, RenderSurfaceTrackingView::kRequiredPrefixSize> storage{};
  storeValue<std::int32_t>(storage.data(), RenderSurfaceWithStrideView::kRowStrideOffset, -640);
  storeValue<std::uint32_t>(storage.data(), RenderSurfaceTrackingView::kDirtyFlagOffset, 1u);
  storeValue<std::uint32_t>(storage.data(), RenderSurfaceTrackingView::kResourceHandleOffset, 0x12345678u);

  const RenderSurfaceTrackingView view(storage.data());
  CHECK_EQ(view.rowStride(), -640);
  CHECK(view.isDirty());
  CHECK_EQ(view.dirtyFlag(), 1u);
  CHECK_EQ(view.resourceHandle(), 0x12345678u);
}

TEST(cpp_render_surface_tracking_view, mutates_dirty_and_resource_fields_only) {
  using clash95::render::RenderSurfaceTrackingMutableView;
  using clash95::render::RenderSurfaceTrackingView;

  std::array<std::byte, RenderSurfaceTrackingView::kRequiredPrefixSize> storage{};
  RenderSurfaceTrackingMutableView view(storage.data());

  view.markDirty();
  CHECK(view.readOnly().isDirty());
  CHECK_EQ(view.swapResourceHandle(0xAABBCCDDu), 0u);
  CHECK_EQ(view.readOnly().resourceHandle(), 0xAABBCCDDu);
  CHECK_EQ(view.swapResourceHandle(0x10203040u), 0xAABBCCDDu);
  CHECK_EQ(view.readOnly().resourceHandle(), 0x10203040u);

  view.clearDirty();
  CHECK(!view.readOnly().isDirty());
  CHECK_EQ(view.readOnly().dirtyFlag(), 0u);
}
