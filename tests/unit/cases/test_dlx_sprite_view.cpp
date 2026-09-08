#include "render/dlx_sprite_view.h"

TEST(cpp_class_views, dlx_sprite_reads_unaligned_storage) {
  unsigned char storage[clash95::render::DLXSpriteView::kObjectSize] = {};
  const std::uint16_t height = 19;
  const std::uint16_t width = 37;
  const std::uint32_t payload = 0x10203040u;
  const std::uint32_t serializedSize = 0x55667788u;
  const std::uint32_t ownsPayload = 1;

  std::memcpy(storage + clash95::render::DLXSpriteView::kHeightOffset,
              &height, sizeof(height));
  std::memcpy(storage + clash95::render::DLXSpriteView::kWidthOffset,
              &width, sizeof(width));
  std::memcpy(storage + clash95::render::DLXSpriteView::kPayloadHandleOffset,
              &payload, sizeof(payload));
  std::memcpy(storage + clash95::render::DLXSpriteView::kSerializedSizeOffset,
              &serializedSize, sizeof(serializedSize));
  std::memcpy(storage + clash95::render::DLXSpriteView::kOwnsPayloadOffset,
              &ownsPayload, sizeof(ownsPayload));

  clash95::render::DLXSpriteView view(storage);
  CHECK_EQ(view.height(), 19);
  CHECK_EQ(view.width(), 37);
  CHECK_EQ(view.payloadHandle(), 0x10203040u);
  CHECK_EQ(view.serializedSize(), 0x55667788u);
  CHECK(view.ownsPayload());
}

TEST(cpp_class_views, dlx_sprite_mutable_view_preserves_raw_offsets) {
  unsigned char storage[clash95::render::DLXSpriteView::kObjectSize] = {};
  clash95::render::DLXSpriteMutableView view(storage);

  view.setPayloadHandle(0xA1B2C3D4u);
  view.setSerializedSize(1234);
  view.setOwnsPayload(true);

  std::uint32_t rawPayload = 0;
  std::uint32_t rawSize = 0;
  std::uint32_t rawOwnsPayload = 0;
  std::memcpy(&rawPayload,
              storage + clash95::render::DLXSpriteView::kPayloadHandleOffset,
              sizeof(rawPayload));
  std::memcpy(&rawSize,
              storage + clash95::render::DLXSpriteView::kSerializedSizeOffset,
              sizeof(rawSize));
  std::memcpy(&rawOwnsPayload,
              storage + clash95::render::DLXSpriteView::kOwnsPayloadOffset,
              sizeof(rawOwnsPayload));

  CHECK_EQ(rawPayload, 0xA1B2C3D4u);
  CHECK_EQ(rawSize, 1234);
  CHECK_EQ(rawOwnsPayload, 1);
  CHECK(view.readOnly().ownsPayload());

  view.clearPayloadHandle();
  view.setOwnsPayload(false);
  CHECK_EQ(view.readOnly().payloadHandle(), 0);
  CHECK(!view.readOnly().ownsPayload());
}

TEST(cpp_class_views, dlx_sprite_serialized_header_copy_is_exactly_ten_bytes) {
  unsigned char source[clash95::render::DLXSpriteView::kSerializedHeaderSize] = {
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  unsigned char storage[clash95::render::DLXSpriteView::kObjectSize];
  std::memset(storage, 0xA5, sizeof(storage));

  clash95::render::DLXSpriteMutableView(storage).copySerializedHeaderFrom(source);

  CHECK_EQ(std::memcmp(storage, source,
                       clash95::render::DLXSpriteView::kSerializedHeaderSize), 0);
  for (std::size_t i = clash95::render::DLXSpriteView::kSerializedHeaderSize;
       i < sizeof(storage); ++i) {
    CHECK_EQ(storage[i], 0xA5u);
  }
}
