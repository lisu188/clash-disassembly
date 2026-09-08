#include "media/avi_decompressor_view.h"
#include "render/dlx_sprite_set_view.h"

TEST(cpp_mutable_views, avi_writes_match_recovered_offsets) {
  unsigned char storage[clash95::media::CAviDecompressorView::kObjectSize] = {};
  clash95::media::CAviDecompressorMutableView view(storage);

  view.setOverlaysEnabled(true);
  CHECK_EQ(storage[clash95::media::CAviDecompressorView::kOverlaysEnabledOffset], 1);
  CHECK(view.readOnly().overlaysEnabled());

  view.setPosition(-17, 29);
  CHECK(view.readOnly().usesExplicitDestination());
  CHECK_EQ(view.readOnly().destinationLeft(), -17);
  CHECK_EQ(view.readOnly().destinationTop(), 29);
  CHECK_EQ(view.readOnly().destinationRight(), 0);
  CHECK_EQ(view.readOnly().destinationBottom(), 0);

  std::int32_t rawLeft = 0;
  std::int32_t rawTop = 0;
  std::memcpy(&rawLeft,
              storage + clash95::media::CAviDecompressorView::kDestinationLeftOffset,
              sizeof(rawLeft));
  std::memcpy(&rawTop,
              storage + clash95::media::CAviDecompressorView::kDestinationTopOffset,
              sizeof(rawTop));
  CHECK_EQ(rawLeft, -17);
  CHECK_EQ(rawTop, 29);

  view.setDestinationRect(3, 5, 41, 43);
  CHECK_EQ(view.readOnly().destinationLeft(), 3);
  CHECK_EQ(view.readOnly().destinationTop(), 5);
  CHECK_EQ(view.readOnly().destinationRight(), 41);
  CHECK_EQ(view.readOnly().destinationBottom(), 43);

  view.setOverlaysEnabled(false);
  CHECK(!view.readOnly().overlaysEnabled());
}

TEST(cpp_mutable_views, dlx_writes_match_recovered_words) {
  std::uint32_t storage[clash95::render::DLXSpriteSetView::kObjectDwordCount] = {};
  clash95::render::DLXSpriteSetMutableView view(storage);

  view.setEntryHandle(7, 0x10203040u);
  view.setDataHandle(0xA0B0C0D0u);
  view.setEntryCount(0x1234002Au);
  view.setFileSize(0x55667788u);
  view.setVtableHandle(0xCAFEBABEu);

  CHECK_EQ(storage[7], 0x10203040u);
  CHECK_EQ(storage[clash95::render::DLXSpriteSetView::kDataHandleIndex], 0xA0B0C0D0u);
  CHECK_EQ(storage[clash95::render::DLXSpriteSetView::kEntryCountIndex], 0x1234002Au);
  CHECK_EQ(storage[clash95::render::DLXSpriteSetView::kFileSizeIndex], 0x55667788u);
  CHECK_EQ(storage[clash95::render::DLXSpriteSetView::kVtableHandleIndex], 0xCAFEBABEu);

  CHECK_EQ(view.readOnly().entryHandle(7), 0x10203040u);
  CHECK_EQ(view.readOnly().serializedEntryCount(), 42);
  CHECK_EQ(view.readOnly().lastCharIndex(), 41);

  view.clearDataHandle();
  CHECK_EQ(view.readOnly().dataHandle(), 0);
}
