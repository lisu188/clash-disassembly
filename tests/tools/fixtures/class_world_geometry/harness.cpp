#include "harness.hpp"

int main()
{
  prepare_table();
  const clash95::WorldGeometry geometry(g_MathSinTableQ16);
  uint64_t facing_cases = 0, sine_cases = 0, sqrt_cases = 0;
  const int deltas[] = {INT_MIN, INT_MIN + 1, -65536, -361, -2, -1, 0,
                        1, 2, 361, 65536, INT_MAX - 1, INT_MAX};
  for (int row : deltas) {
    for (int column : deltas) {
      const int expected = Reference_Facing_DirectionFromDelta8(row, column);
      require(Facing_DirectionFromDelta8(row, column) == expected, "facing adapter");
      require(geometry.Facing_DirectionFromDelta8(row, column) == expected, "facing method");
      unchanged();
      ++facing_cases;
      ++cases;
    }
  }
  sine_corpus([&](int angle) {
    const int expected = Reference_Math_SinDegreesQ16(angle);
    require(Math_SinDegreesQ16(angle) == expected, "sine adapter");
    require(geometry.Math_SinDegreesQ16(angle) == expected, "sine method");
    require(x86_sine(angle) == expected, "sine reference/x86 oracle");
    unchanged();
    ++sine_cases;
    ++cases;
  });
  auto check_sqrt = [&](int value) {
    const int expected = Reference_Math_CeilSqrt(value);
    require(Math_CeilSqrt(value) == expected, "sqrt adapter");
    require(geometry.Math_CeilSqrt(value) == expected, "sqrt method");
    unchanged();
    ++sqrt_cases;
    ++cases;
  };
  const int sqrt_edges[] = {INT_MIN, INT_MIN + 1, -65536, -2, -1, 0, 1, 2, 3, 4,
                           INT_MAX - 2, INT_MAX - 1, INT_MAX};
  for (int value : sqrt_edges) check_sqrt(value);
  for (int value = -8192; value <= 8192; ++value) check_sqrt(value);
  for (int value = 1; value <= 46340; ++value) {
    const int square = value * value;
    check_sqrt(square - 1);
    check_sqrt(square);
    check_sqrt(square + 1);
  }
  for (unsigned index = 0; index < 65536; ++index) check_sqrt(next_signed());
  std::printf("facing_cases=%llu sine_cases=%llu sqrt_cases=%llu guarded_table_bytes=%zu direct_and_abi=pass\n",
              static_cast<unsigned long long>(facing_cases),
              static_cast<unsigned long long>(sine_cases),
              static_cast<unsigned long long>(sqrt_cases), kPage);
}
