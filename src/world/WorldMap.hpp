#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows the arena handle variable; each operation reads its current value.
class CLASH95_INTERNAL WorldMap final {
 public:
  static WorldMap borrow() noexcept;
  signed int Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex) const;
  BOOL Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex) const;
  signed int Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex) const;
 private:
  explicit WorldMap(int &arenaHandle) noexcept : state_field_0_(arenaHandle) {}
  int &state_field_0_;
};
}
