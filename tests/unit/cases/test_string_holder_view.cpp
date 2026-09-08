#include "media/string_holder_view.h"

TEST(cpp_string_holder_view, reads_two_dword_storage) {
  unsigned char storage[clash95::media::StringHolderView::kObjectSize] = {};
  const std::uint32_t text_handle = 0x10203040u;
  const std::uint32_t vtable_handle = 0x50607080u;

  std::memcpy(storage + clash95::media::StringHolderView::kTextHandleOffset,
              &text_handle, sizeof(text_handle));
  std::memcpy(storage + clash95::media::StringHolderView::kVtableHandleOffset,
              &vtable_handle, sizeof(vtable_handle));

  clash95::media::StringHolderView view(storage);
  CHECK(view.hasText());
  CHECK_EQ(view.textHandle(), 0x10203040u);
  CHECK_EQ(view.vtableHandle(), 0x50607080u);
}

TEST(cpp_string_holder_view, writes_match_holder_words) {
  unsigned char storage[clash95::media::StringHolderView::kObjectSize] = {};
  clash95::media::StringHolderMutableView view(storage);

  view.setTextHandle(0x11223344u);
  view.setVtableHandle(0x55667788u);

  std::uint32_t raw_text = 0;
  std::uint32_t raw_vtable = 0;
  std::memcpy(&raw_text,
              storage + clash95::media::StringHolderView::kTextHandleOffset,
              sizeof(raw_text));
  std::memcpy(&raw_vtable,
              storage + clash95::media::StringHolderView::kVtableHandleOffset,
              sizeof(raw_vtable));

  CHECK_EQ(raw_text, 0x11223344u);
  CHECK_EQ(raw_vtable, 0x55667788u);
  CHECK(view.readOnly().hasText());

  view.clearTextHandle();
  CHECK(!view.readOnly().hasText());
  CHECK_EQ(view.readOnly().vtableHandle(), 0x55667788u);
}
