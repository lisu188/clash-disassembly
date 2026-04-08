#pragma once

#include "common.hpp"

namespace clash95 {
namespace cpp {

// Conservative view of the `CSyncObject` seam. The C side currently exposes
// `CSyncObject_Unlock`; this wrapper keeps the original name searchable while
// remaining intentionally minimal.
class CSyncObject final {
public:
  CSyncObject() noexcept;
  explicit CSyncObject(RawHandle raw) noexcept;

  static CSyncObject from_raw(RawHandle raw) noexcept;

  RawHandle raw() noexcept;
  const void *raw() const noexcept;

  bool empty() const noexcept;
  void reset(RawHandle raw = nullptr) noexcept;

  int unlock(long lock_state, long *previous_lock_state) noexcept;

private:
  RawHandle raw_;
};

} // namespace cpp
} // namespace clash95
