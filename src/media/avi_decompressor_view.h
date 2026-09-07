#ifndef CLASH95_MEDIA_AVI_DECOMPRESSOR_VIEW_H
#define CLASH95_MEDIA_AVI_DECOMPRESSOR_VIEW_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::media {

class CAviDecompressorView final {
public:
  static constexpr std::size_t kObjectSize = 2236;
  static constexpr std::size_t kStreamScaleOffset = 31;
  static constexpr std::size_t kStreamRateOffset = 35;
  static constexpr std::size_t kFrameCountOffset = 43;
  static constexpr std::size_t kPrimaryReadyOffset = 7;
  static constexpr std::size_t kSecondaryReadyOffset = 415;
  static constexpr std::size_t kBlitReadyOffset = 1940;
  static constexpr std::size_t kSurfaceReadyOffset = 1944;
  static constexpr std::size_t kPaletteHandleOffset = 1948;
  static constexpr std::size_t kBitmapHeaderHandleOffset = 151;
  static constexpr std::size_t kDecodedFrameOffset = 2021;
  static constexpr std::size_t kSumSleepTimeOffset = 2038;
  static constexpr std::size_t kOverlaysEnabledOffset = 2050;
  static constexpr std::size_t kPositionModeOffset = 2062;
  static constexpr std::size_t kDestinationLeftOffset = 2063;
  static constexpr std::size_t kDestinationTopOffset = 2067;
  static constexpr std::size_t kDestinationRightOffset = 2071;
  static constexpr std::size_t kDestinationBottomOffset = 2075;
  static constexpr std::size_t kPlayingOffset = 2191;
  static constexpr std::size_t kFrameEventHandleOffset = 2196;
  static constexpr std::size_t kDestroyVtableOffset = 2232;

  explicit CAviDecompressorView(const void *instance) noexcept
      : bytes_(static_cast<const std::byte *>(instance)) {}

  static CAviDecompressorView fromPlayerHandle(const void *playerHandle) noexcept {
    std::uint32_t instance = 0;
    std::memcpy(&instance, playerHandle, sizeof(instance));
    return CAviDecompressorView(
        reinterpret_cast<const void *>(static_cast<std::uintptr_t>(instance)));
  }

  const void *data() const noexcept {
    return bytes_;
  }

  std::int32_t streamScale() const noexcept {
    return load<std::int32_t>(kStreamScaleOffset);
  }

  std::int32_t streamRate() const noexcept {
    return load<std::int32_t>(kStreamRateOffset);
  }

  std::int32_t frames() const noexcept {
    return load<std::int32_t>(kFrameCountOffset);
  }

  std::int32_t fps() const noexcept {
    return streamRate() / streamScale();
  }

  bool initialized() const noexcept {
    return load<std::uint32_t>(kPrimaryReadyOffset) != 0
        && (load<std::uint32_t>(kSecondaryReadyOffset) != 0
            || load<std::uint32_t>(kSurfaceReadyOffset) != 0
            || load<std::uint32_t>(kBlitReadyOffset) != 0);
  }

  bool isPlaying() const noexcept {
    return load<std::uint8_t>(kPlayingOffset) != 0;
  }

  std::uint32_t paletteHandle() const noexcept {
    return load<std::uint32_t>(kPaletteHandleOffset);
  }

  std::uint32_t bitmapHeaderHandle() const noexcept {
    return load<std::uint32_t>(kBitmapHeaderHandleOffset);
  }

  std::int32_t decodedFrame() const noexcept {
    return load<std::int32_t>(kDecodedFrameOffset);
  }

  std::int32_t sumSleepTime() const noexcept {
    return load<std::int32_t>(kSumSleepTimeOffset);
  }

  bool overlaysEnabled() const noexcept {
    return load<std::uint8_t>(kOverlaysEnabledOffset) != 0;
  }

  bool usesExplicitDestination() const noexcept {
    return load<std::uint8_t>(kPositionModeOffset) != 0;
  }

  std::int32_t destinationLeft() const noexcept {
    return load<std::int32_t>(kDestinationLeftOffset);
  }

  std::int32_t destinationTop() const noexcept {
    return load<std::int32_t>(kDestinationTopOffset);
  }

  std::int32_t destinationRight() const noexcept {
    return load<std::int32_t>(kDestinationRightOffset);
  }

  std::int32_t destinationBottom() const noexcept {
    return load<std::int32_t>(kDestinationBottomOffset);
  }

  std::uint32_t frameEventHandle() const noexcept {
    return load<std::uint32_t>(kFrameEventHandleOffset);
  }

  std::uint32_t destroyVtableHandle() const noexcept {
    return load<std::uint32_t>(kDestroyVtableOffset);
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

class CAviDecompressorMutableView final {
public:
  explicit CAviDecompressorMutableView(void *instance) noexcept
      : bytes_(static_cast<std::byte *>(instance)) {}

  static CAviDecompressorMutableView fromPlayerHandle(void *playerHandle) noexcept {
    std::uint32_t instance = 0;
    std::memcpy(&instance, playerHandle, sizeof(instance));
    return CAviDecompressorMutableView(
        reinterpret_cast<void *>(static_cast<std::uintptr_t>(instance)));
  }

  void *data() const noexcept {
    return bytes_;
  }

  CAviDecompressorView readOnly() const noexcept {
    return CAviDecompressorView(bytes_);
  }

  void setOverlaysEnabled(bool enabled) noexcept {
    store<std::uint8_t>(CAviDecompressorView::kOverlaysEnabledOffset,
                        enabled ? 1u : 0u);
  }

  void setPosition(std::int32_t x, std::int32_t y) noexcept {
    store<std::int32_t>(CAviDecompressorView::kDestinationRightOffset, 0);
    store<std::int32_t>(CAviDecompressorView::kDestinationBottomOffset, 0);
    store<std::uint8_t>(CAviDecompressorView::kPositionModeOffset, 1);
    store<std::int32_t>(CAviDecompressorView::kDestinationLeftOffset, x);
    store<std::int32_t>(CAviDecompressorView::kDestinationTopOffset, y);
  }

  void setDestinationRect(std::int32_t left, std::int32_t top,
                          std::int32_t right, std::int32_t bottom) noexcept {
    store<std::int32_t>(CAviDecompressorView::kDestinationLeftOffset, left);
    store<std::int32_t>(CAviDecompressorView::kDestinationTopOffset, top);
    store<std::int32_t>(CAviDecompressorView::kDestinationRightOffset, right);
    store<std::int32_t>(CAviDecompressorView::kDestinationBottomOffset, bottom);
    store<std::uint8_t>(CAviDecompressorView::kPositionModeOffset, 1);
  }

private:
  template <typename T>
  void store(std::size_t offset, T value) noexcept {
    std::memcpy(bytes_ + offset, &value, sizeof(value));
  }

  std::byte *bytes_;
};

static_assert(CAviDecompressorView::kDestroyVtableOffset + sizeof(std::uint32_t)
              == CAviDecompressorView::kObjectSize);

} // namespace clash95::media

#endif
