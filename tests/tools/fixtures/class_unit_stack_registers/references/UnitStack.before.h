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
 private:
  intptr_t address_;
};
}
