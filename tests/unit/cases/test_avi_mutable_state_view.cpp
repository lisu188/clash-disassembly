#include "media/avi_decompressor_view.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace {

template <typename T>
T loadValue(const std::byte *bytes, std::size_t offset) {
  T value{};
  std::memcpy(&value, bytes + offset, sizeof(value));
  return value;
}

}

TEST(cpp_avi_mutable_state_view, writes_clip_rect_words) {
  using clash95::media::CAviDecompressorMutableView;
  using clash95::media::CAviDecompressorView;

  std::array<std::byte, CAviDecompressorView::kObjectSize> storage{};
  const std::uint32_t rect[] = {11u, 12u, 211u, 212u};
  CAviDecompressorMutableView(storage.data()).setClipRect(rect);

  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kClipLeftOffset), 11u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kClipTopOffset), 12u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kClipRightOffset), 211u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kClipBottomOffset), 212u);
}

TEST(cpp_avi_mutable_state_view, writes_color_key_contract) {
  using clash95::media::CAviDecompressorMutableView;
  using clash95::media::CAviDecompressorView;

  std::array<std::byte, CAviDecompressorView::kObjectSize> storage{};
  CAviDecompressorMutableView(storage.data()).setColorKeys(0x11223344, 0x55667788);

  CHECK_EQ(loadValue<std::int32_t>(storage.data(), CAviDecompressorView::kColorKeyModeOffset), 8);
  CHECK_EQ(static_cast<std::uint32_t>(loadValue<std::int32_t>(storage.data(), CAviDecompressorView::kColorKeyLowOffset)), 0x11223344u);
  CHECK_EQ(static_cast<std::uint32_t>(loadValue<std::int32_t>(storage.data(), CAviDecompressorView::kColorKeyHighOffset)), 0x55667788u);
}

TEST(cpp_avi_mutable_state_view, writes_background_rect_and_object) {
  using clash95::media::CAviDecompressorMutableView;
  using clash95::media::CAviDecompressorView;

  std::array<std::byte, CAviDecompressorView::kObjectSize> storage{};
  const std::uint32_t rect[] = {1u, 2u, 101u, 202u};
  CAviDecompressorMutableView(storage.data()).setBackground(0x10203040, rect);

  CHECK_EQ(static_cast<std::uint32_t>(loadValue<std::int32_t>(storage.data(), CAviDecompressorView::kBackgroundObjectHandleOffset)), 0x10203040u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBackgroundLeftOffset), 1u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBackgroundTopOffset), 2u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBackgroundRightOffset), 101u);
  CHECK_EQ(loadValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBackgroundBottomOffset), 202u);
}
