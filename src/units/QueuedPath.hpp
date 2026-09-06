#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows the original count and 100-waypoint storage without reordering it.
class CLASH95_INTERNAL QueuedPath final {
 public:
  explicit QueuedPath(_DWORD *bytes, int &state) noexcept : bytes_(bytes), state_(state) {}
  BOOL QueuedPath_StartsAtTile(int tileRow, int tileColumn) const;
  BOOL QueuedPath_StartsInBuildingFootprint(int buildingIndex) const;
 private:
  _DWORD *bytes_;
  int &state_;
};
}
