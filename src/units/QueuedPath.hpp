#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows the original count and 100-waypoint storage without reordering it.
class CLASH95_INTERNAL QueuedPath final {
 public:
  explicit QueuedPath(_DWORD *bytes) noexcept : bytes_(bytes) {}
  BOOL QueuedPath_StartsAtTile(int tileRow, int tileColumn) const;
 private:
  _DWORD *bytes_;
};
}
