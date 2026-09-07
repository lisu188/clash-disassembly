#include "buildings/wcisv_list_view.h"

TEST(cpp_class_views, wcisv_list_layout_and_reads) {
  WCCompatLink first{};
  WCCompatLink second{};
  first.next_link = 0x11223344;
  first.value = 17;
  second.next_link = 0;
  second.value = 29;

  clash95::buildings::WCIsvLinkView firstView(&first);
  clash95::buildings::WCIsvLinkView secondView(&second);
  CHECK_EQ(firstView.nextHandle(), 0x11223344);
  CHECK_EQ(firstView.value(), 17);
  CHECK_EQ(secondView.nextHandle(), 0);
  CHECK_EQ(secondView.value(), 29);

  WCCompatListBase list{};
  list.head_link = 0x10101010;
  list.vtable = 0x20202020;
  list.tail_link = 0x30303030;
  list.count = 2;
  list.alloc_fn = 0x40404040;
  list.free_fn = 0x50505050;

  clash95::buildings::WCIsvListBaseView view(&list);
  CHECK_EQ(view.headHandle(), 0x10101010);
  CHECK_EQ(view.vtableHandle(), 0x20202020);
  CHECK_EQ(view.tailHandle(), 0x30303030);
  CHECK_EQ(view.count(), 2);
  CHECK_EQ(view.allocatorHandle(), 0x40404040);
  CHECK_EQ(view.deallocatorHandle(), 0x50505050);
  CHECK(!view.empty());
}

TEST(cpp_class_views, wcisv_list_mutable_view_preserves_words) {
  WCCompatListBase list{};
  clash95::buildings::WCIsvListBaseMutableView view(&list);

  view.setHeadHandle(11);
  view.setVtableHandle(22);
  view.setTailHandle(33);
  view.setCount(4);
  view.setAllocatorHandle(55);
  view.setDeallocatorHandle(66);

  CHECK_EQ(list.head_link, 11);
  CHECK_EQ(list.vtable, 22);
  CHECK_EQ(list.tail_link, 33);
  CHECK_EQ(list.count, 4);
  CHECK_EQ(list.alloc_fn, 55);
  CHECK_EQ(list.free_fn, 66);
  CHECK_EQ(view.readOnly().count(), 4);

  view.setHeadHandle(0);
  CHECK(view.readOnly().empty());
}
