#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows a current packed stack; construction never changes game storage.
class CLASH95_INTERNAL UnitStack final {
 public:
  explicit UnitStack(intptr_t address) noexcept : address_(address) {}
  signed int UnitStack_GetMinCurrentActionPoints() const;
  signed int UnitStack_HasReadyUnits() const;
  signed int UnitStack_HasBuilder() const;
  int UnitStack_CalcMilitaryStrength() const;
  signed int UnitStack_NormalizePeasantCargo(DWORD a2, double a3) const;
  signed int UnitStack_HasPlague() const;
  signed int UnitStack_HasLowMoraleUnit() const;
  signed int UnitStack_GetMaxOrderTier() const;
  signed int UnitStack_HasNormalCombatUnits() const;
  signed int UnitStack_HasSpecialPersonageUnits() const;
  int UnitStack_SetPlagueFlag() const;
  signed int UnitStack_SpendActionPointsClamped(int spendAmount, DWORD a3, double a4) const;
  signed int UnitStack_SubtractActionPointsFloorZero(int subtractAmount, DWORD a3, double a4) const;
  int UnitStack_SpendActionPointsUnchecked(char spendAmount) const;
 private:
  intptr_t address_;
};
}
