#pragma once
#include "../recovered_types.h"

namespace clash95 {
// Borrows the existing seed word and exact format bytes; binding has no effects.
class CLASH95_INTERNAL GameRandom final {
 public:
  explicit GameRandom(char (&format)[29], int &state) noexcept
      : format_(format), state_(state) {}
  static GameRandom borrow() noexcept;
  void initRandomSeed(char arg_0, DWORD arg_1) const;
  unsigned int Rng_RandRange(int minValue, int maxValue) const;
 private:
  char (&format_)[29];
  int &state_;
};
} // namespace clash95
