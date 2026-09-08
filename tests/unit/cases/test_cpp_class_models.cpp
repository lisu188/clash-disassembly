#include "core/path_entry_model.h"
#include "media/avi_decompressor_view.h"

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

TEST(cpp_class_models, path_entry_layout) {
  using clash95::core::CompatStringHolderLayout;
  using clash95::core::PathEntryArrayLayout;
  using clash95::core::PathEntryLayout;

  CHECK_EQ(sizeof(CompatStringHolderLayout), 8u);
  CHECK_EQ(sizeof(PathEntryLayout), 16u);
  CHECK_EQ(sizeof(PathEntryArrayLayout), 20u);
  CHECK_EQ(offsetof(PathEntryLayout, text_holder), 4u);
  CHECK_EQ(offsetof(PathEntryLayout, trailing_value), 12u);
  CHECK_EQ(offsetof(PathEntryArrayLayout, element_count), 8u);
  CHECK_EQ(offsetof(PathEntryArrayLayout, capacity), 12u);
  CHECK_EQ(offsetof(PathEntryArrayLayout, vtable_handle), 16u);
}

TEST(cpp_class_models, avi_decompressor_view) {
  using clash95::media::CAviDecompressorView;

  std::array<std::byte, CAviDecompressorView::kObjectSize> storage{};
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kStreamScaleOffset, 2);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kStreamRateOffset, 50);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kFrameCountOffset, 123);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kPrimaryReadyOffset, 1);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kSecondaryReadyOffset, 0);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kSurfaceReadyOffset, 7);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBlitReadyOffset, 0);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kPaletteHandleOffset, 0x12345678u);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kBitmapHeaderHandleOffset, 0x10203040u);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kDecodedFrameOffset, 42);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kSumSleepTimeOffset, 900);
  storeValue<std::uint8_t>(storage.data(), CAviDecompressorView::kOverlaysEnabledOffset, 1);
  storeValue<std::uint8_t>(storage.data(), CAviDecompressorView::kPositionModeOffset, 1);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kDestinationLeftOffset, 11);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kDestinationTopOffset, 12);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kDestinationRightOffset, 311);
  storeValue<std::int32_t>(storage.data(), CAviDecompressorView::kDestinationBottomOffset, 212);
  storeValue<std::uint8_t>(storage.data(), CAviDecompressorView::kPlayingOffset, 1);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kFrameEventHandleOffset, 0x1357u);
  storeValue<std::uint32_t>(storage.data(), CAviDecompressorView::kDestroyVtableOffset, 0x2468u);

  const CAviDecompressorView view(storage.data());
  CHECK_EQ(view.streamScale(), 2);
  CHECK_EQ(view.streamRate(), 50);
  CHECK_EQ(view.frames(), 123);
  CHECK_EQ(view.fps(), 25);
  CHECK_EQ(view.initialized(), true);
  CHECK_EQ(view.isPlaying(), true);
  CHECK_EQ(view.paletteHandle(), 0x12345678u);
  CHECK_EQ(view.bitmapHeaderHandle(), 0x10203040u);
  CHECK_EQ(view.decodedFrame(), 42);
  CHECK_EQ(view.sumSleepTime(), 900);
  CHECK_EQ(view.overlaysEnabled(), true);
  CHECK_EQ(view.usesExplicitDestination(), true);
  CHECK_EQ(view.destinationLeft(), 11);
  CHECK_EQ(view.destinationTop(), 12);
  CHECK_EQ(view.destinationRight(), 311);
  CHECK_EQ(view.destinationBottom(), 212);

  const clash95::media::AviDestinationRect rect = view.destinationRect();
  CHECK_EQ(rect.left, 11);
  CHECK_EQ(rect.top, 12);
  CHECK_EQ(rect.right, 311);
  CHECK_EQ(rect.bottom, 212);

  std::int32_t copied_rect[4] = {};
  view.copyDestinationRect(copied_rect);
  CHECK_EQ(copied_rect[0], 11);
  CHECK_EQ(copied_rect[1], 12);
  CHECK_EQ(copied_rect[2], 311);
  CHECK_EQ(copied_rect[3], 212);

  CHECK_EQ(view.frameEventHandle(), 0x1357u);
  CHECK_EQ(view.destroyVtableHandle(), 0x2468u);
}
