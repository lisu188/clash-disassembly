#include "render/dlx_sprite_set_view.h"

#include <array>
#include <cstdint>

TEST(cpp_class_models, dlx_sprite_set_view) {
  using clash95::render::DLXSpriteSetView;

  std::array<std::uint32_t, DLXSpriteSetView::kObjectDwordCount> storage{};
  storage[0] = 0x1000u;
  storage[12] = 0x2000u;
  storage[DLXSpriteSetView::kDataHandleIndex] = 0x3000u;
  storage[DLXSpriteSetView::kEntryCountIndex] = 13u;
  storage[DLXSpriteSetView::kFileSizeIndex] = 0x4567u;
  storage[DLXSpriteSetView::kVtableHandleIndex] = 0x5000u;

  const DLXSpriteSetView view(storage.data());
  CHECK_EQ(view.entryHandle(0), 0x1000u);
  CHECK_EQ(view.entryHandle(12), 0x2000u);
  CHECK_EQ(view.dataHandle(), 0x3000u);
  CHECK_EQ(view.entryCount(), 13u);
  CHECK_EQ(view.serializedEntryCount(), 13u);
  CHECK_EQ(view.lastCharIndex(), 12u);
  CHECK_EQ(view.fileSize(), 0x4567u);
  CHECK_EQ(view.vtableHandle(), 0x5000u);
}

TEST(cpp_class_models, dlx_last_char_preserves_original_low16_read) {
  using clash95::render::DLXSpriteSetView;

  std::array<std::uint32_t, DLXSpriteSetView::kObjectDwordCount> storage{};
  storage[DLXSpriteSetView::kEntryCountIndex] = 0x12340005u;

  const DLXSpriteSetView view(storage.data());
  CHECK_EQ(view.entryCount(), 0x12340005u);
  CHECK_EQ(view.serializedEntryCount(), 5u);
  CHECK_EQ(view.lastCharIndex(), 4u);
}
