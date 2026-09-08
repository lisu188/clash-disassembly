#include "media/avi_bitmap_info_view.h"

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

TEST(cpp_avi_bitmap_info_view, reads_standard_header_prefix) {
  using clash95::media::AviBitmapInfoHeaderView;

  std::array<std::byte, AviBitmapInfoHeaderView::kRequiredPrefixSize> storage{};
  storeValue<std::int32_t>(storage.data(), AviBitmapInfoHeaderView::kWidthOffset, 640);
  storeValue<std::int32_t>(storage.data(), AviBitmapInfoHeaderView::kHeightOffset, -480);
  storeValue<std::uint16_t>(storage.data(), AviBitmapInfoHeaderView::kBitCountOffset, 24);

  const AviBitmapInfoHeaderView view(storage.data());
  CHECK_EQ(view.width(), 640);
  CHECK_EQ(view.signedHeight(), -480);
  CHECK_EQ(view.absoluteHeight(), 480);
  CHECK_EQ(view.bitsPerPixel(), 24u);
  CHECK_EQ(view.bytesPerPixel(), 3);
}

TEST(cpp_avi_bitmap_info_view, preserves_int32_min_height_bit_pattern) {
  using clash95::media::AviBitmapInfoHeaderView;

  std::array<std::byte, AviBitmapInfoHeaderView::kRequiredPrefixSize> storage{};
  storeValue<std::int32_t>(storage.data(), AviBitmapInfoHeaderView::kHeightOffset,
                           static_cast<std::int32_t>(0x80000000u));

  const AviBitmapInfoHeaderView view(storage.data());
  CHECK_EQ(static_cast<std::uint32_t>(view.absoluteHeight()), 0x80000000u);
}

TEST(cpp_avi_bitmap_info_view, rounds_bit_count_up_to_bytes) {
  using clash95::media::AviBitmapInfoHeaderView;

  std::array<std::byte, AviBitmapInfoHeaderView::kRequiredPrefixSize> storage{};
  storeValue<std::uint16_t>(storage.data(), AviBitmapInfoHeaderView::kBitCountOffset, 15);

  const AviBitmapInfoHeaderView view(storage.data());
  CHECK_EQ(view.bytesPerPixel(), 2);
}
