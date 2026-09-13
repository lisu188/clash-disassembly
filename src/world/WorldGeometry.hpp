#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows the recovered Q16 lookup table; construction never changes storage.
class CLASH95_INTERNAL WorldGeometry final {
 public:
  explicit WorldGeometry(const int (&borrowed_values)[363]) noexcept : state_(borrowed_values) {}
  signed int Facing_DirectionFromDelta8(int deltaRow, int deltaColumn) const;
  int Math_SinDegreesQ16(signed int degrees) const;
  signed int Math_CeilSqrt(signed int value) const;
 private:
  const int (&state_)[363];
};
}
