#ifndef CLASH95_RENDER_RENDER_SURFACE_VIEW_H
#define CLASH95_RENDER_RENDER_SURFACE_VIEW_H

#include "../recovered_types.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::render {

class RenderSurfaceView final {
public:
  static constexpr std::size_t kObjectSize = 188;
  static constexpr std::size_t kWidthOffset = 0;
  static constexpr std::size_t kHeightOffset = 2;
  static constexpr std::size_t kPixelBufferHandleOffset = 4;
  static constexpr std::size_t kMethodTableHandleOffset = 184;

  explicit RenderSurfaceView(const void *surface) noexcept
      : bytes_(static_cast<const std::byte *>(surface)) {}

  std::uint16_t width() const noexcept {
    return load<std::uint16_t>(kWidthOffset);
  }

  std::uint16_t height() const noexcept {
    return load<std::uint16_t>(kHeightOffset);
  }

  std::uint32_t pixelBufferHandle() const noexcept {
    return load<std::uint32_t>(kPixelBufferHandleOffset);
  }

  std::uint32_t methodTableHandle() const noexcept {
    return load<std::uint32_t>(kMethodTableHandleOffset);
  }

  bool hasPixelBuffer() const noexcept {
    return pixelBufferHandle() != 0;
  }

  const void *data() const noexcept {
    return bytes_;
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

class RenderSurfaceMutableView final {
public:
  explicit RenderSurfaceMutableView(void *surface) noexcept
      : bytes_(static_cast<std::byte *>(surface)) {}

  RenderSurfaceView readOnly() const noexcept {
    return RenderSurfaceView(bytes_);
  }

  void setDimensions(std::uint16_t width, std::uint16_t height) noexcept {
    store<std::uint16_t>(RenderSurfaceView::kWidthOffset, width);
    store<std::uint16_t>(RenderSurfaceView::kHeightOffset, height);
  }

  void setPixelBufferHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(RenderSurfaceView::kPixelBufferHandleOffset, handle);
  }

  void clearPixelBufferHandle() noexcept {
    setPixelBufferHandle(0);
  }

  void setMethodTableHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(RenderSurfaceView::kMethodTableHandleOffset, handle);
  }

  void *data() const noexcept {
    return bytes_;
  }

private:
  template <typename T>
  void store(std::size_t offset, T value) noexcept {
    std::memcpy(bytes_ + offset, &value, sizeof(value));
  }

  std::byte *bytes_;
};

class RenderSurfaceWithStrideView final {
public:
  static constexpr std::size_t kObjectSize = sizeof(RenderSurfaceStorage);
  static constexpr std::size_t kRowStrideOffset = RenderSurfaceView::kObjectSize;

  explicit RenderSurfaceWithStrideView(const void *surface) noexcept
      : bytes_(static_cast<const std::byte *>(surface)) {}

  RenderSurfaceView base() const noexcept {
    return RenderSurfaceView(bytes_);
  }

  std::int32_t rowStride() const noexcept {
    std::int32_t value{};
    std::memcpy(&value, bytes_ + kRowStrideOffset, sizeof(value));
    return value;
  }

  const void *data() const noexcept {
    return bytes_;
  }

private:
  const std::byte *bytes_;
};

class RenderSurfaceWithStrideMutableView final {
public:
  explicit RenderSurfaceWithStrideMutableView(void *surface) noexcept
      : bytes_(static_cast<std::byte *>(surface)) {}

  RenderSurfaceMutableView base() const noexcept {
    return RenderSurfaceMutableView(bytes_);
  }

  RenderSurfaceWithStrideView readOnly() const noexcept {
    return RenderSurfaceWithStrideView(bytes_);
  }

  void setRowStride(std::int32_t stride) noexcept {
    std::memcpy(bytes_ + RenderSurfaceWithStrideView::kRowStrideOffset,
                &stride, sizeof(stride));
  }

private:
  std::byte *bytes_;
};

static_assert(RenderSurfaceView::kMethodTableHandleOffset + sizeof(std::uint32_t)
              == RenderSurfaceView::kObjectSize);
static_assert(sizeof(RenderSurfaceStorage) == 192);
static_assert(RenderSurfaceWithStrideView::kRowStrideOffset == 188);
static_assert(RenderSurfaceWithStrideView::kObjectSize == 192);

} // namespace clash95::render

#endif
