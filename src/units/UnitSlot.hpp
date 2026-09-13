#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows one packed unit slot; construction does not change game storage.
class CLASH95_INTERNAL UnitSlot final {
 public:
  explicit UnitSlot(intptr_t address) noexcept : address_(address) {}
  BOOL UnitSlot_ShouldGainFatigueFromLowActionPoints() const;
  BOOL UnitSlot_CanRecoverFatigue() const;
  BOOL UnitSlot_HasSevereFatigue() const;
  int UnitSlot_CycleOrderState() const;
  int UnitSlot_CalcActionPointsFromFatigue() const;
  int UnitSlot_GetBaseActionPoints() const;
 private:
  intptr_t address_;
};
}
