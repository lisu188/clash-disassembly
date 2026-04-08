#pragma once

#include "common.hpp"

namespace clash95 {
namespace cpp {

// Conservative wrapper for the sprite-set seam recovered from:
// - `DLXSpriteSet_Load`
// - `DLXSpriteSet::save`
// - `DLXSpriteSet_DrawText`
//
// This keeps the original map-visible name searchable while the recovered C++
// tree is still a raw-handle view rather than a full behavior port.
class DLXSpriteSet final {
public:
  DLXSpriteSet() noexcept;
  explicit DLXSpriteSet(RawHandle raw) noexcept;

  static DLXSpriteSet from_raw(RawHandle raw) noexcept;

  RawHandle raw() noexcept;
  const void *raw() const noexcept;

  bool empty() const noexcept;
  void reset(RawHandle raw = nullptr) noexcept;

  int save(int output_slot, char preserve_case_flag) const noexcept;
  int draw_text(int x, int y, int palette_index, const unsigned char *text) const noexcept;

private:
  RawHandle raw_;
};

} // namespace cpp
} // namespace clash95
