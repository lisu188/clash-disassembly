#pragma once

#include <cstddef>

namespace clash95 {
namespace cpp {

using RawHandle = void *;

struct Rect {
  long left;
  long top;
  long right;
  long bottom;
};

struct Point {
  long x;
  long y;
};

} // namespace cpp
} // namespace clash95
