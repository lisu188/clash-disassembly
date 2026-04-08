#include "clash95/cpp/csync_object.hpp"

namespace clash95 {
namespace cpp {

CSyncObject::CSyncObject() noexcept : raw_(nullptr) {}

CSyncObject::CSyncObject(RawHandle raw) noexcept : raw_(raw) {}

CSyncObject CSyncObject::from_raw(RawHandle raw) noexcept
{
  return CSyncObject(raw);
}

RawHandle CSyncObject::raw() noexcept
{
  return raw_;
}

const void *CSyncObject::raw() const noexcept
{
  return raw_;
}

bool CSyncObject::empty() const noexcept
{
  return raw_ == nullptr;
}

void CSyncObject::reset(RawHandle raw) noexcept
{
  raw_ = raw;
}

int CSyncObject::unlock(long, long *) noexcept
{
  // The map only confirms the unlock seam. This is a conservative raw-handle
  // wrapper until the owning runtime object is lifted into the C++ tree.
  return raw_ == nullptr ? 0 : 1;
}

} // namespace cpp
} // namespace clash95
