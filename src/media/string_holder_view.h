#ifndef CLASH95_MEDIA_STRING_HOLDER_VIEW_H
#define CLASH95_MEDIA_STRING_HOLDER_VIEW_H

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace clash95::media {

class StringHolderView final {
public:
  static constexpr std::size_t kObjectSize = 8;
  static constexpr std::size_t kTextHandleOffset = 0;
  static constexpr std::size_t kVtableHandleOffset = 4;

  explicit StringHolderView(const void *holder) noexcept
      : bytes_(static_cast<const std::byte *>(holder)) {}

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

static_assert(StringHolderView::kVtableHandleOffset + sizeof(std::uint32_t)
              == StringHolderView::kObjectSize);

} // namespace clash95::media

#endif
