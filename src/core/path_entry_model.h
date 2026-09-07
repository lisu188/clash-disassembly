#ifndef CLASH95_CORE_PATH_ENTRY_MODEL_H
#define CLASH95_CORE_PATH_ENTRY_MODEL_H

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace clash95::core {

class CompatStringHolderLayout final {
public:
  std::uint32_t text_handle;
  std::uint32_t vtable_handle;
};

class PathEntryLayout final {
public:
  std::int32_t leading_value;
  CompatStringHolderLayout text_holder;
  std::int32_t trailing_value;
};

class PathEntryArrayLayout final {
public:
  std::uint32_t storage_handle;
  std::int32_t unrecovered_04;
  std::int32_t element_count;
  std::int32_t capacity;
  std::uint32_t vtable_handle;

  constexpr bool empty() const noexcept {
    return element_count == 0;
  }
};

static_assert(std::is_standard_layout_v<CompatStringHolderLayout>);
static_assert(std::is_trivially_copyable_v<CompatStringHolderLayout>);
static_assert(sizeof(CompatStringHolderLayout) == 8);
static_assert(offsetof(CompatStringHolderLayout, text_handle) == 0);
static_assert(offsetof(CompatStringHolderLayout, vtable_handle) == 4);

static_assert(std::is_standard_layout_v<PathEntryLayout>);
static_assert(std::is_trivially_copyable_v<PathEntryLayout>);
static_assert(sizeof(PathEntryLayout) == 16);
static_assert(offsetof(PathEntryLayout, leading_value) == 0);
static_assert(offsetof(PathEntryLayout, text_holder) == 4);
static_assert(offsetof(PathEntryLayout, trailing_value) == 12);

static_assert(std::is_standard_layout_v<PathEntryArrayLayout>);
static_assert(std::is_trivially_copyable_v<PathEntryArrayLayout>);
static_assert(sizeof(PathEntryArrayLayout) == 20);
static_assert(offsetof(PathEntryArrayLayout, storage_handle) == 0);
static_assert(offsetof(PathEntryArrayLayout, unrecovered_04) == 4);
static_assert(offsetof(PathEntryArrayLayout, element_count) == 8);
static_assert(offsetof(PathEntryArrayLayout, capacity) == 12);
static_assert(offsetof(PathEntryArrayLayout, vtable_handle) == 16);

} // namespace clash95::core

#endif
