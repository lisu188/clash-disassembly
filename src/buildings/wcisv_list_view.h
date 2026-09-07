#ifndef CLASH95_BUILDINGS_WCISV_LIST_VIEW_H
#define CLASH95_BUILDINGS_WCISV_LIST_VIEW_H

#include "../recovered_types.h"
#include <cstddef>
#include <cstdint>

namespace clash95::buildings {

class WCIsvLinkView final {
public:
  explicit constexpr WCIsvLinkView(const WCCompatLink *link) noexcept
      : link_(link) {}

  constexpr std::int32_t nextHandle() const noexcept {
    return link_->next_link;
  }

  constexpr std::int32_t value() const noexcept {
    return link_->value;
  }

private:
  const WCCompatLink *link_;
};

class WCIsvListBaseView final {
public:
  static constexpr std::size_t kObjectSize = sizeof(WCCompatListBase);

  explicit WCIsvListBaseView(const WCIsvListBase *list) noexcept
      : list_(reinterpret_cast<const WCCompatListBase *>(list)) {}

  explicit constexpr WCIsvListBaseView(const WCCompatListBase *list) noexcept
      : list_(list) {}

  constexpr std::int32_t headHandle() const noexcept {
    return list_->head_link;
  }

  constexpr std::int32_t vtableHandle() const noexcept {
    return list_->vtable;
  }

  constexpr std::int32_t tailHandle() const noexcept {
    return list_->tail_link;
  }

  constexpr std::int32_t count() const noexcept {
    return list_->count;
  }

  constexpr std::int32_t allocatorHandle() const noexcept {
    return list_->alloc_fn;
  }

  constexpr std::int32_t deallocatorHandle() const noexcept {
    return list_->free_fn;
  }

  constexpr bool empty() const noexcept {
    return list_->head_link == 0;
  }

  constexpr const WCCompatListBase *data() const noexcept {
    return list_;
  }

private:
  const WCCompatListBase *list_;
};

class WCIsvListBaseMutableView final {
public:
  explicit WCIsvListBaseMutableView(WCIsvListBase *list) noexcept
      : list_(reinterpret_cast<WCCompatListBase *>(list)) {}

  explicit constexpr WCIsvListBaseMutableView(WCCompatListBase *list) noexcept
      : list_(list) {}

  constexpr WCIsvListBaseView readOnly() const noexcept {
    return WCIsvListBaseView(list_);
  }

  constexpr void setHeadHandle(std::int32_t handle) noexcept {
    list_->head_link = handle;
  }

  constexpr void setVtableHandle(std::int32_t handle) noexcept {
    list_->vtable = handle;
  }

  constexpr void setTailHandle(std::int32_t handle) noexcept {
    list_->tail_link = handle;
  }

  constexpr void setCount(std::int32_t count) noexcept {
    list_->count = count;
  }

  constexpr void setAllocatorHandle(std::int32_t handle) noexcept {
    list_->alloc_fn = handle;
  }

  constexpr void setDeallocatorHandle(std::int32_t handle) noexcept {
    list_->free_fn = handle;
  }

  constexpr WCCompatListBase *data() const noexcept {
    return list_;
  }

private:
  WCCompatListBase *list_;
};

static_assert(sizeof(WCCompatLink) == 8);
static_assert(offsetof(WCCompatLink, next_link) == 0);
static_assert(offsetof(WCCompatLink, value) == 4);
static_assert(sizeof(WCCompatListBase) == 24);
static_assert(offsetof(WCCompatListBase, head_link) == 0);
static_assert(offsetof(WCCompatListBase, vtable) == 4);
static_assert(offsetof(WCCompatListBase, tail_link) == 8);
static_assert(offsetof(WCCompatListBase, count) == 12);
static_assert(offsetof(WCCompatListBase, alloc_fn) == 16);
static_assert(offsetof(WCCompatListBase, free_fn) == 20);

} // namespace clash95::buildings

#endif
