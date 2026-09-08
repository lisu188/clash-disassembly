#ifndef CLASH95_RENDER_RENDER_SURFACE_TRACKING_VIEW_H
#define CLASH95_RENDER_RENDER_SURFACE_TRACKING_VIEW_H

#include "render_surface_view.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::render {

class RenderSurfaceTrackingView final {
public:
  static constexpr std::size_t kRequiredPrefixSize = 208;
  static constexpr std::size_t kDirtyFlagOffset = 200;
  static constexpr std::size_t kResourceHandleOffset = 204;

  explicit RenderSurfaceTrackingView(const void *surface) noexcept
      : bytes_(static_cast<const std::byte *>(surface)) {}

  RenderSurfaceWithStrideView strideView() const noexcept {
    return RenderSurfaceWithStrideView(bytes_);
  }

  std::int32_t rowStride() const noexcept {
    return strideView().rowStride();
  }

  bool isDirty() const noexcept {
    return load<std::uint32_t>(kDirtyFlagOffset) != 0;
  }

  std::uint32_t dirtyFlag() const noexcept {
    return load<std::uint32_t>(kDirtyFlagOffset);
  }

  std::uint32_t resourceHandle() const noexcept {
    return load<std::uint32_t>(kResourceHandleOffset);
  }

private:
  template <typename T>
  T load(std::size_t offset) const noexcept {
    T value{};
    std::memcpy(&value, bytes_ + offset, sizeof(value));
    return value;
  }

  const std::byte *bytes_;
};

class RenderSurfaceTrackingMutableView final {
public:
  explicit RenderSurfaceTrackingMutableView(void *surface) noexcept
      : bytes_(static_cast<std::byte *>(surface)) {}

  RenderSurfaceTrackingView readOnly() const noexcept {
    return RenderSurfaceTrackingView(bytes_);
  }

  void markDirty() noexcept {
    store<std::uint32_t>(RenderSurfaceTrackingView::kDirtyFlagOffset, 1u);
  }

  void clearDirty() noexcept {
    store<std::uint32_t>(RenderSurfaceTrackingView::kDirtyFlagOffset, 0u);
  }

  void setResourceHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(RenderSurfaceTrackingView::kResourceHandleOffset, handle);
  }

  std::uint32_t swapResourceHandle(std::uint32_t handle) noexcept {
    const std::uint32_t previous = readOnly().resourceHandle();
    setResourceHandle(handle);
    return previous;
  }

private:
  template <typename T>
  void store(std::size_t offset, T value) noexcept {
    std::memcpy(bytes_ + offset, &value, sizeof(value));
  }

  std::byte *bytes_;
};

static_assert(RenderSurfaceTrackingView::kDirtyFlagOffset == 200);
static_assert(RenderSurfaceTrackingView::kResourceHandleOffset == 204);
static_assert(RenderSurfaceTrackingView::kResourceHandleOffset + sizeof(std::uint32_t)
              == RenderSurfaceTrackingView::kRequiredPrefixSize);

} // namespace clash95::render

#endif
