#ifndef CLASH95_MEDIA_AVI_BITMAP_INFO_VIEW_H
#define CLASH95_MEDIA_AVI_BITMAP_INFO_VIEW_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::media {

class AviBitmapInfoHeaderView final {
public:
  static constexpr std::size_t kRequiredPrefixSize = 16;
  static constexpr std::size_t kWidthOffset = 4;
  static constexpr std::size_t kHeightOffset = 8;
  static constexpr std::size_t kBitCountOffset = 14;

  explicit AviBitmapInfoHeaderView(const void *header) noexcept
      : bytes_(static_cast<const std::byte *>(header)) {}

  static AviBitmapInfoHeaderView fromHandle(std::uint32_t handle) noexcept {
    return AviBitmapInfoHeaderView(
        reinterpret_cast<const void *>(static_cast<std::uintptr_t>(handle)));
  }

  std::int32_t width() const noexcept {
    return load<std::int32_t>(kWidthOffset);
  }

  std::int32_t signedHeight() const noexcept {
    return load<std::int32_t>(kHeightOffset);
  }

  std::int32_t absoluteHeight() const noexcept {
    const std::int32_t value = signedHeight();
    if (value >= 0)
      return value;
    const std::uint32_t bits = static_cast<std::uint32_t>(value);
    return static_cast<std::int32_t>(0u - bits);
  }

  std::uint16_t bitsPerPixel() const noexcept {
    return load<std::uint16_t>(kBitCountOffset);
  }

  std::int32_t bytesPerPixel() const noexcept {
    return (static_cast<std::int32_t>(bitsPerPixel()) + 7) >> 3;
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

static_assert(AviBitmapInfoHeaderView::kBitCountOffset + sizeof(std::uint16_t)
              == AviBitmapInfoHeaderView::kRequiredPrefixSize);

} // namespace clash95::media

#endif
