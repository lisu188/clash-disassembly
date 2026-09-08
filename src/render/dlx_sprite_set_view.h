#ifndef CLASH95_RENDER_DLX_SPRITE_SET_VIEW_H
#define CLASH95_RENDER_DLX_SPRITE_SET_VIEW_H

#include <cstddef>
#include <cstdint>

namespace clash95::render {

class DLXSpriteSetView final {
public:
  static constexpr std::size_t kDirectoryEntryLimit = 1023;
  static constexpr std::size_t kDataHandleIndex = 1024;
  static constexpr std::size_t kEntryCountIndex = 1025;
  static constexpr std::size_t kFileSizeIndex = 1026;
  static constexpr std::size_t kVtableHandleIndex = 1027;
  static constexpr std::size_t kObjectDwordCount = 1028;
  static constexpr std::size_t kObjectSize = kObjectDwordCount * sizeof(std::uint32_t);

  explicit constexpr DLXSpriteSetView(const void *spriteSet) noexcept
      : words_(static_cast<const std::uint32_t *>(spriteSet)) {}

  constexpr const void *data() const noexcept {
    return words_;
  }

  constexpr std::uint32_t entryHandle(std::size_t index) const noexcept {
    return words_[index];
  }

  constexpr std::uint32_t entryHandleSigned(std::ptrdiff_t index) const noexcept {
    return words_[index];
  }

  constexpr std::uint32_t dataHandle() const noexcept {
    return words_[kDataHandleIndex];
  }

  constexpr std::uint32_t entryCount() const noexcept {
    return words_[kEntryCountIndex];
  }

  constexpr std::uint32_t fileSize() const noexcept {
    return words_[kFileSizeIndex];
  }

  constexpr std::uint32_t vtableHandle() const noexcept {
    return words_[kVtableHandleIndex];
  }

  constexpr std::uint16_t serializedEntryCount() const noexcept {
    return static_cast<std::uint16_t>(entryCount());
  }

  constexpr std::uint16_t lastCharIndex() const noexcept {
    return static_cast<std::uint16_t>(serializedEntryCount() - 1u);
  }

  constexpr std::uint32_t legacyLastCharResult(
      std::uint32_t incomingValue) const noexcept {
    const std::uint32_t withSerializedCount =
        (incomingValue & 0xFFFF0000u) | serializedEntryCount();
    return withSerializedCount - 1u;
  }

private:
  const std::uint32_t *words_;
};

class DLXSpriteSetMutableView final {
public:
  explicit constexpr DLXSpriteSetMutableView(void *spriteSet) noexcept
      : words_(static_cast<std::uint32_t *>(spriteSet)) {}

  constexpr void *data() const noexcept {
    return words_;
  }

  constexpr DLXSpriteSetView readOnly() const noexcept {
    return DLXSpriteSetView(words_);
  }

  constexpr void setEntryHandle(std::size_t index, std::uint32_t handle) noexcept {
    words_[index] = handle;
  }

  constexpr void setDataHandle(std::uint32_t handle) noexcept {
    words_[DLXSpriteSetView::kDataHandleIndex] = handle;
  }

  constexpr void clearDataHandle() noexcept {
    setDataHandle(0);
  }

  constexpr void setEntryCount(std::uint32_t count) noexcept {
    words_[DLXSpriteSetView::kEntryCountIndex] = count;
  }

  constexpr void setFileSize(std::uint32_t size) noexcept {
    words_[DLXSpriteSetView::kFileSizeIndex] = size;
  }

  constexpr void setVtableHandle(std::uint32_t handle) noexcept {
    words_[DLXSpriteSetView::kVtableHandleIndex] = handle;
  }

private:
  std::uint32_t *words_;
};

static_assert(DLXSpriteSetView::kDataHandleIndex * sizeof(std::uint32_t) == 4096);
static_assert(DLXSpriteSetView::kEntryCountIndex * sizeof(std::uint32_t) == 4100);
static_assert(DLXSpriteSetView::kFileSizeIndex * sizeof(std::uint32_t) == 4104);
static_assert(DLXSpriteSetView::kVtableHandleIndex * sizeof(std::uint32_t) == 4108);
static_assert(DLXSpriteSetView::kObjectSize == 4112);

} // namespace clash95::render

#endif
