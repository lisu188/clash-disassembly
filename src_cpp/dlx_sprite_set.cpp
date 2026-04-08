#include "clash95/cpp/dlx_sprite_set.hpp"

namespace clash95 {
namespace cpp {

DLXSpriteSet::DLXSpriteSet() noexcept : raw_(nullptr) {}

DLXSpriteSet::DLXSpriteSet(RawHandle raw) noexcept : raw_(raw) {}

DLXSpriteSet DLXSpriteSet::from_raw(RawHandle raw) noexcept
{
  return DLXSpriteSet(raw);
}

RawHandle DLXSpriteSet::raw() noexcept
{
  return raw_;
}

const void *DLXSpriteSet::raw() const noexcept
{
  return raw_;
}

bool DLXSpriteSet::empty() const noexcept
{
  return raw_ == nullptr;
}

void DLXSpriteSet::reset(RawHandle raw) noexcept
{
  raw_ = raw;
}

int DLXSpriteSet::save(int, char) const noexcept
{
  // Placeholder wrapper only: the recovered C++ tree has not yet lifted the
  // sprite-file format semantics into this layer.
  return raw_ == nullptr ? 0 : 1;
}

int DLXSpriteSet::draw_text(int, int, int, const unsigned char *) const noexcept
{
  // Placeholder wrapper only: the renderer path remains in the recovered C
  // baseline until a higher-confidence class extraction pass lands.
  return raw_ == nullptr ? 0 : 1;
}

} // namespace cpp
} // namespace clash95
