#ifndef CLASH95_MEDIA_STRING_HOLDER_VIEW_H
#define CLASH95_MEDIA_STRING_HOLDER_VIEW_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

namespace clash95::media {

struct StringHolderStorage final {
  std::uint32_t text_handle;
  std::uint32_t vtable_handle;
};

class StringHolderView final {
public:
  static constexpr std::size_t kObjectSize = sizeof(StringHolderStorage);
  static constexpr std::size_t kTextHandleOffset = offsetof(StringHolderStorage, text_handle);
  static constexpr std::size_t kVtableHandleOffset = offsetof(StringHolderStorage, vtable_handle);

  explicit StringHolderView(const void *holder) noexcept
      : bytes_(static_cast<const std::byte *>(holder)) {}

  explicit StringHolderView(const StringHolderStorage *holder) noexcept
      : bytes_(reinterpret_cast<const std::byte *>(holder)) {}

  std::uint32_t textHandle() const noexcept {
    return load<std::uint32_t>(kTextHandleOffset);
  }

  std::uint32_t vtableHandle() const noexcept {
    return load<std::uint32_t>(kVtableHandleOffset);
  }

  bool hasText() const noexcept {
    return textHandle() != 0;
  }

  const char *text() const noexcept {
    return reinterpret_cast<const char *>(
        static_cast<std::uintptr_t>(textHandle()));
  }

  const void *data() const noexcept {
    return bytes_;
  }

private:
  template <typename T>
  T load(std::size_t offset) const noexcept {
    T value{};
    std::memcpy(&value, bytes_ + offset, sizeof(value));
    return value;
  }

  const std::byte *bytes_;
};

class StringHolderMutableView final {
public:
  explicit StringHolderMutableView(void *holder) noexcept
      : bytes_(static_cast<std::byte *>(holder)) {}

  explicit StringHolderMutableView(StringHolderStorage *holder) noexcept
      : bytes_(reinterpret_cast<std::byte *>(holder)) {}

  StringHolderView readOnly() const noexcept {
    return StringHolderView(bytes_);
  }

  void setTextHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(StringHolderView::kTextHandleOffset, handle);
  }

  void clearTextHandle() noexcept {
    setTextHandle(0);
  }

  void setVtableHandle(std::uint32_t handle) noexcept {
    store<std::uint32_t>(StringHolderView::kVtableHandleOffset, handle);
  }

  void *data() const noexcept {
    return bytes_;
  }

private:
  template <typename T>
  void store(std::size_t offset, T value) noexcept {
    std::memcpy(bytes_ + offset, &value, sizeof(value));
  }

  std::byte *bytes_;
};

static_assert(std::is_standard_layout_v<StringHolderStorage>);
static_assert(std::is_trivially_copyable_v<StringHolderStorage>);
static_assert(sizeof(StringHolderStorage) == 8);
static_assert(offsetof(StringHolderStorage, text_handle) == 0);
static_assert(offsetof(StringHolderStorage, vtable_handle) == 4);

} // namespace clash95::media

#endif
