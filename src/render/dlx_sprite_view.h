#ifndef CLASH95_RENDER_DLX_SPRITE_VIEW_H
#define CLASH95_RENDER_DLX_SPRITE_VIEW_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::render {

class DLXSpriteView final {
public:
  static constexpr std::size_t kObjectSize = 22;
  static constexpr std::size_t kHeightOffset = 0;
  static constexpr std::size_t kWidthOffset = 2;
  static constexpr std::size_t kSerializedHeaderSize = 10;
  static constexpr std::size_t kPayloadHandleOffset = 10;
  static constexpr std::size_t kSerializedSizeOffset = 14;
  static constexpr std::size_t kOwnsPayloadOffset = 18;

  explicit DLXSpriteView(const void *sprite) noexcept
      : bytes_(static_cast<const std::byte *>(sprite)) {}

  std::uint16_t height() const noexcept {
    return load<std::uint16_t>(kHeightOffset);
  }

  std::uint16_t width() const noexcept {
    return load<std::uint16_t>(kWidthOffset);
  }

  std::uint32_t payloadHandle() const noexcept {
    return load<std::uint32_t>(kPayloadHandleOffset);
  }

  std::uint32_t serializedSize() const noexcept {
    return load<std::uint32_t>(kSerializedSizeOffset);
  }

  bool ownsPayload() const noexcept {
    return load<std::uint32_t>(kOwnsPayloadOffset) != 0;
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

class DLXSpriteMutableView final {
public:
  explicit DLXSpriteMutableView(void *sprite) noexcept
      : bytes_(static_cast<std::byte *>(sprite)) {}

  DLXSpriteView readOnly() const noexcept {
    return DLXSpriteView(bytes_);
  }

  void copySerializedHeaderFrom(const void *source) noexcept {
    std::memcpy(bytes_, source, DLXSpriteView::kSerializedHeaderSize);
  }

  void clearPayloadHandle() noexcept {
    setPayloadHandle(0);
  }

  void setPayloadHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(DLXSpriteView::kPayloadHandleOffset, handle);
  }

  void setSerializedSize(std::uint32_t size) noexcept {
    store<std::uint32_t>(DLXSpriteView::kSerializedSizeOffset, size);
  }

  void setOwnsPayload(bool ownsPayload) noexcept {
    store<std::uint32_t>(DLXSpriteView::kOwnsPayloadOffset, ownsPayload ? 1u : 0u);
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

static_assert(DLXSpriteView::kPayloadHandleOffset == DLXSpriteView::kSerializedHeaderSize);
static_assert(DLXSpriteView::kOwnsPayloadOffset + sizeof(std::uint32_t)
              == DLXSpriteView::kObjectSize);

} // namespace clash95::render

#endif
