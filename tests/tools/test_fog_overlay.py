#!/usr/bin/env python3
"""Asset-free truth-table checks of the actual recovered fog classifier.

The table was measured from the unchanged original 0x40F0C0 instruction bytes,
with original visibility (0x40F060) and style setter (0x40BBF0). The fixture is
checked in here so CI needs neither retail files nor private probe artifacts.
"""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


REPO = Path(__file__).resolve().parents[2]
SOURCE = REPO / "src/world/0040D6D0_0040F4D0_world_004.cpp"

# Index bits: NW=0x80, N=0x40, NE=0x20, W=0x10,
#             E=0x08, SW=0x04, S=0x02, SE=0x01.
ORIGINAL_OVERLAY = (
    0, 12, 7, 7, 11, 12, 7, 7, 5, 5, 8, 8, 5, 5, 8, 8,
    4, 4, 6, 6, 4, 4, 6, 6, -1, -1, -1, -1, -1, -1, -1, -1,
    10, 12, 7, 7, 11, 12, 7, 7, 5, 5, 8, 8, 5, 5, 8, 8,
    4, 4, 6, 6, 4, 4, 6, 6, -1, -1, -1, -1, -1, -1, -1, -1,
    2, 2, -1, -1, 2, 2, -1, -1, 3, 3, -1, -1, 3, 3, -1, -1,
    1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    2, 2, -1, -1, 2, 2, -1, -1, 3, 3, -1, -1, 3, 3, -1, -1,
    1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    9, 12, 7, 7, 9, 12, 7, 7, 5, 5, 8, 8, 5, 5, 8, 8,
    4, 4, 6, 6, 4, 4, 6, 6, -1, -1, -1, -1, -1, -1, -1, -1,
    9, 12, 7, 7, 9, 12, 7, 7, 5, 5, 8, 8, 5, 5, 8, 8,
    4, 4, 6, 6, 4, 4, 6, 6, -1, -1, -1, -1, -1, -1, -1, -1,
    2, 2, -1, -1, 2, 2, -1, -1, 3, 3, -1, -1, 3, 3, -1, -1,
    1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    2, 2, -1, -1, 2, 2, -1, -1, 3, 3, -1, -1, 3, 3, -1, -1,
    1, 1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
)

HARNESS = r'''
#include <cstdio>
#include <cstdlib>
#define __int8 char
typedef int BOOL;
static int center_x, center_y, active_player, calls, style_calls;
static unsigned int visible_mask;
static unsigned char style;
static int trace[9][3];
static const int bit_dx[9] = {1, 0, -1, 1, -1, 1, 0, -1, 0};
static const int bit_dy[9] = {1, 1, 1, 0, 0, -1, -1, -1, 0};
static bool in_bounds(int x, int y) {
  return x >= 0 && y >= 0 && x < 100 && y < 100;
}
// Traced Boolean visibility provider: no recovered implementation is copied.
static BOOL Map_IsTileVisibleToPlayer(int x, int y, int player) {
  if (calls == 9) std::abort();
  trace[calls][0] = x;
  trace[calls][1] = y;
  trace[calls++][2] = player;
  if (player != active_player || !in_bounds(x, y)) return 0;
  for (int bit = 0; bit < 9; ++bit)
    if (x == center_x + bit_dx[bit] && y == center_y + bit_dy[bit])
      return (visible_mask & (1u << bit)) != 0;
  std::abort();
}
static char TextSprite_SetStyleFlag(char value) {
  ++style_calls;
  style = (unsigned char)value;
  return value;
}
@CLASSIFIER@
static const signed char expected[256] = {@TABLE@};
int main() {
  const int positions[][2] = {{50,50}, {0,0}, {99,99}, {0,50}, {99,50},
                              {50,0}, {50,99}, {-1,50}, {100,50}, {50,-1}, {50,100}};
  const int order_dx[9] = {0,-1,0,1,-1,1,-1,0,1};
  const int order_dy[9] = {0,-1,-1,-1,0,0,1,1,1};
  unsigned int tested = 0;
  for (const auto &position : positions) for (int player = 0; player < 6; ++player)
    for (unsigned int mask = 0; mask < 512; ++mask) {
      center_x = position[0]; center_y = position[1]; active_player = player;
      visible_mask = mask; calls = 0; style_calls = 0; style = 0xa5;
      unsigned int clipped_mask = 0;
      for (int bit = 0; bit < 9; ++bit)
        if ((mask & (1u << bit)) && in_bounds(center_x + bit_dx[bit], center_y + bit_dy[bit]))
          clipped_mask |= 1u << bit;
      const bool center_visible = (clipped_mask & 256) != 0;
      const int want = center_visible ? -1 : expected[clipped_mask & 255];
      const int want_style_calls = !center_visible && (clipped_mask & 255) ? 1 : 0;
      const int result = Map_ClassifyFogOfWarOverlayForPlayer(center_x, center_y, player);
      if (result != want || style != (want_style_calls ? 1 : 0xa5) ||
          style_calls != want_style_calls || calls != (center_visible ? 1 : 9)) {
        std::fprintf(stderr, "fog x=%d y=%d player=%d mask=%03x result=%d expected=%d style=%u calls=%d setter=%d\n",
                     center_x, center_y, player, mask, result, want, style, calls, style_calls);
        return 1;
      }
      for (int call = 0; call < calls; ++call)
        if (trace[call][0] != center_x + order_dx[call] ||
            trace[call][1] != center_y + order_dy[call] || trace[call][2] != player) {
          std::fprintf(stderr, "fog visibility call order/player mismatch at call %d\n", call);
          return 2;
        }
      ++tested;
    }
  std::printf("fog cases=%u\n", tested);
}
'''


class FogOverlayTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        match = re.search(
            r"(?m)^signed int\s+Map_ClassifyFogOfWarOverlayForPlayer\([^\n]*\)\n\{.*?^\}",
            SOURCE.read_text(), re.DOTALL)
        self.assertIsNotNone(match, "actual canonical classifier definition not found")
        self.assertEqual(len(ORIGINAL_OVERLAY), 256)
        source = HARNESS.replace("@CLASSIFIER@", match.group()).replace(
            "@TABLE@", ",".join(map(str, ORIGINAL_OVERLAY)))
        with tempfile.TemporaryDirectory(prefix="clash95-fog-test-") as temp:
            path = Path(temp) / "fog.cpp"
            path.write_text(source)
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = Path(temp) / ("fog-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-Wall", "-Wextra", "-Werror",
                               # Trap mode keeps UBSan checks active without requiring
                               # a separately installed Clang sanitizer runtime in CI.
                               "-fsanitize=undefined", "-fsanitize-undefined-trap-on-error",
                               str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], capture_output=True, text=True, timeout=30)
                    self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                    self.assertEqual(run.stdout, "fog cases=33792\n")
                    self.assertEqual(run.stderr, "")

    def test_gcc_truth_table_and_visibility_order(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_truth_table_and_visibility_order(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
