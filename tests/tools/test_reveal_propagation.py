#!/usr/bin/env python3
"""Asset-free checks of the actual recovered reveal and visibility functions.

The checked-in endpoint table and callback order were measured by executing
unchanged original PE code at 0x40EDE0 with actual visibility at 0x40F060 and a
traced minimap boundary. Running this test needs no retail files or artifacts.
"""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


REPO = Path(__file__).resolve().parents[2]
SOURCE = REPO / "src/world/0040D6D0_0040F4D0_world_004.cpp"

# Endpoint and final-neighbor bits: L=1, R=2, U=4, D=8, NW=16, NE=32,
# SW=64, SE=128. The parent center is revealed in every table case.
ORIGINAL_NEIGHBORS = (
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    52, 53, 54, 55, 52, 53, 54, 55, 60, 61, 62, 63, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    81, 81, 83, 83, 85, 85, 87, 87, 89, 89, 91, 91, 93, 93, 95, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    117, 117, 119, 119, 117, 117, 119, 119, 125, 125, 127, 127, 125, 125, 127, 127,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    162, 163, 162, 163, 166, 167, 166, 167, 170, 171, 170, 171, 174, 175, 174, 175,
    182, 183, 182, 183, 182, 183, 182, 183, 190, 191, 190, 191, 190, 191, 190, 191,
    200, 201, 202, 203, 204, 205, 206, 207, 200, 201, 202, 203, 204, 205, 206, 207,
    217, 217, 219, 219, 221, 221, 223, 223, 217, 217, 219, 219, 221, 221, 223, 223,
    234, 235, 234, 235, 238, 239, 238, 239, 234, 235, 234, 235, 238, 239, 238, 239,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
)

HARNESS = r'''
#include "recovered_types.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

alignas(4) static unsigned char memory[0x25000], before[0x25000], expected[0x25000];
static int gameData, active_player, width, height, trace_count, case_count;
static int trace[10000][2];
static unsigned char seen[100][100];
// Original branch order: left, right, up, down, NW, NE, SW, SE.
static const int dx[8] = {-1,1,0,0,-1,1,-1,1};
static const int dy[8] = {0,0,-1,1,-1,-1,1,1};
static const unsigned char original_neighbors[256] = {@ORIGINAL_NEIGHBORS@};
static void fail(const char *message) {
  std::fprintf(stderr, "reveal case=%d player=%d: %s\n", case_count, active_player, message);
  std::exit(1);
}
static bool in_bounds(int x, int y) {
  return x >= 0 && y >= 0 && x < width && y < height;
}
static int byte_offset(int x, int y, int player) {
  return PLAYER_RUNTIME_STATE_OFFSET + PLAYER_DATA_STRIDE * player +
         PLAYER_REVEALED_TILES_OFFSET + PLAYER_REVEALED_TILE_ROW_BYTES * x + y / 8;
}
static bool bit(const unsigned char *data, int x, int y, int player) {
  return in_bounds(x,y) && (data[byte_offset(x,y,player)] & (1u << (y % 8)));
}
static void seed(unsigned char *data, int x, int y, int player) {
  if (in_bounds(x,y)) data[byte_offset(x,y,player)] |= (unsigned char)(1u << (y % 8));
}
@VISIBILITY@
static void *MiniMap_DrawTileCell(void *row, int y) {
  const int x = (int)(intptr_t)row;
  if (!in_bounds(x,y)) fail("callback outside map");
  if (!Map_IsTileVisibleToPlayer(x,y,active_player)) fail("callback before reveal bit update");
  if (seen[x][y] || bit(before,x,y,active_player)) fail("callback for an already revealed tile");
  if (trace_count >= 10000) fail("callback capacity exceeded");
  seen[x][y] = 1;
  trace[trace_count][0] = x;
  trace[trace_count++][1] = y;
  return row;
}
@REVEAL@

static void reset(int player, int map_width = 100, int map_height = 100) {
  ++case_count;
  width = map_width; height = map_height; active_player = player; trace_count = 0;
  std::memset(memory, 0xa5, sizeof memory);
  std::memset(seen, 0, sizeof seen);
  *(_DWORD *)(memory + MAP_WIDTH_TILES_OFFSET) = (unsigned int)width;
  *(_DWORD *)(memory + MAP_HEIGHT_TILES_OFFSET) = (unsigned int)height;
  for (int p = 0; p < 6; ++p) {
    std::memset(memory + PLAYER_RUNTIME_STATE_OFFSET + p * PLAYER_DATA_STRIDE +
                PLAYER_REVEALED_TILES_OFFSET, 0, 1300);
    if (p != player) {
      seed(memory, 1, 1, p);
      seed(memory, width-2, height-2, p);
    }
  }
}

// Independently ordered FIFO closure. Only newly revealed nodes trigger
// propagation; initial seeds are visible endpoints, not pending reveal calls.
static void closure(int start_x, int start_y) {
  std::memcpy(expected, before, sizeof expected);
  if (!in_bounds(start_x,start_y) || bit(expected,start_x,start_y,active_player)) return;
  int queue[10000][2], read = 0, write = 0;
  seed(expected,start_x,start_y,active_player);
  queue[write][0] = start_x; queue[write++][1] = start_y;
  while (read != write) {
    const int x = queue[read][0], y = queue[read++][1];
    // Row-major neighborhood order deliberately differs from the original
    // cardinal-first depth-first implementation whose final bitmap we check.
    for (int oy = -1; oy <= 1; ++oy) for (int ox = -1; ox <= 1; ++ox) {
      if ((!ox && !oy) || !bit(expected,x+2*ox,y+2*oy,active_player) ||
          bit(expected,x+ox,y+oy,active_player)) continue;
      if (!in_bounds(x+ox,y+oy) || write >= 10000) fail("invalid oracle midpoint");
      seed(expected,x+ox,y+oy,active_player);
      queue[write][0] = x+ox; queue[write++][1] = y+oy;
    }
  }
}

static void run_case(int x, int y) {
  std::memcpy(before, memory, sizeof before);
  closure(x,y);
  const int want_return = in_bounds(x,y) && !bit(before,x,y,active_player);
  if (Map_RevealTileWithPropagation(x,y,active_player) != want_return) fail("return value");
  // Includes padding, unrelated state and every other player's bitmap.
  if (std::memcmp(memory,expected,sizeof memory)) fail("bitmap/state differs from independent closure");
  int added = 0;
  for (int tx = 0; tx < width; ++tx) for (int ty = 0; ty < height; ++ty) {
    const bool old_bit = bit(before,tx,ty,active_player), new_bit = bit(memory,tx,ty,active_player);
    if (old_bit && !new_bit) fail("reveal cleared a bit");
    if (new_bit && !old_bit) {
      ++added;
      if (!seen[tx][ty]) fail("new tile without callback");
    }
  }
  if (trace_count != added) fail("callback count differs from new bit count");
  if (want_return && (trace[0][0] != x || trace[0][1] != y)) fail("parent callback is not first");
  const int old_count = trace_count;
  if (Map_RevealTileWithPropagation(x,y,active_player) != 0 || trace_count != old_count ||
      std::memcmp(memory,expected,sizeof memory)) fail("repeat call changed state or called minimap");
}

int main() {
  if ((uintptr_t)memory + sizeof memory > INT_MAX) fail("static gameData is not in signed low32 memory");
  gameData = (int)(intptr_t)memory;
  for (int player = 0; player < 6; ++player) {
    for (unsigned int mask = 0; mask < 256; ++mask) {
      reset(player);
      for (int d = 0; d < 8; ++d)
        if (mask & (1u << d)) seed(memory,50+2*dx[d],50+2*dy[d],player);
      run_case(50,50);
      unsigned int final_neighbors = 0;
      for (int d = 0; d < 8; ++d)
        if (bit(memory,50+dx[d],50+dy[d],player)) final_neighbors |= 1u << d;
      if (final_neighbors != original_neighbors[mask]) fail("original PE endpoint table mismatch");
      if (mask == 255) {
        if (trace_count != 9) fail("all-endpoint callback count");
        for (int d = 0; d < 8; ++d)
          if (trace[d+1][0] != 50+dx[d] || trace[d+1][1] != 50+dy[d])
            fail("original all-endpoint callback order");
      }
    }
    // Each isolated endpoint must add exactly the parent and its midpoint.
    for (int d = 0; d < 8; ++d) {
      reset(player);
      seed(memory,50+2*dx[d],50+2*dy[d],player);
      run_case(50,50);
      if (trace_count != 2 || trace[1][0] != 50+dx[d] || trace[1][1] != 50+dy[d])
        fail("isolated endpoint did not fill its midpoint");
    }
    const int invalid[][2] = {{-1,50},{100,50},{50,-1},{50,100},
                              {INT_MIN,50},{INT_MAX,50},{50,INT_MIN},{50,INT_MAX}};
    for (const auto &pos : invalid) { reset(player); run_case(pos[0],pos[1]); }
    reset(player); seed(memory,50,50,player); run_case(50,50);
    const int edges[][2] = {{0,0},{0,99},{99,0},{99,99},{0,50},{99,50},{50,0},{50,99}};
    for (const auto &pos : edges) for (int d = 0; d < 8; ++d) {
      reset(player);
      seed(memory,pos[0]+2*dx[d],pos[1]+2*dy[d],player);
      run_case(pos[0],pos[1]);
    }
    // A diagonal pair induces a cardinal midpoint during recursive descent.
    reset(player); seed(memory,48,48,player); seed(memory,52,48,player);
    run_case(50,50);
    if (trace_count != 4 || !bit(memory,50,49,player)) fail("diagonal cascade");
    // A bounded staircase requires propagation beyond the initial neighborhood.
    reset(player,12,9);
    seed(memory,5,3,player); seed(memory,4,5,player);
    seed(memory,6,4,player); seed(memory,5,6,player);
    run_case(3,3);
    // Exact original PE callback trace, measured for all six players.
    const int original_staircase[][2] = {{3,3},{4,3},{4,4},{5,4},{5,5}};
    if (trace_count != 5) fail("original staircase callback count");
    for (int step = 0; step < 5; ++step)
      if (trace[step][0] != original_staircase[step][0] || trace[step][1] != original_staircase[step][1])
        fail("original staircase callback order");
  }
  std::printf("reveal cases=%d\n", case_count);
}
'''


class RevealPropagationTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        self.assertEqual(len(ORIGINAL_NEIGHBORS), 256)
        source = HARNESS.replace("@ORIGINAL_NEIGHBORS@", ",".join(map(str, ORIGINAL_NEIGHBORS)))
        canonical = SOURCE.read_text()
        for placeholder, name, result_type in (
            ("@VISIBILITY@", "Map_IsTileVisibleToPlayer", "BOOL"),
            ("@REVEAL@", "Map_RevealTileWithPropagation", "signed int"),
        ):
            match = re.search(r"(?m)^" + result_type + r"\s+" + name +
                              r"\([^\n]*\)\n\{.*?^\}", canonical, re.DOTALL)
            self.assertIsNotNone(match, "actual canonical definition not found: " + name)
            source = source.replace(placeholder, match.group())
        with tempfile.TemporaryDirectory(prefix="clash95-reveal-test-") as temp:
            path = Path(temp) / "reveal.cpp"
            path.write_text(source)
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = Path(temp) / ("reveal-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror",
                               # Retain actual signed-coordinate/DWORD bounds comparisons.
                               "-Wno-error=sign-compare", "-fsanitize=undefined",
                               "-fsanitize-undefined-trap-on-error", "-isystem", str(REPO / "src"),
                               str(path), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], capture_output=True, text=True, timeout=30)
                    self.assertEqual(run.returncode, 0, run.stdout + run.stderr)
                    self.assertEqual(run.stdout, "reveal cases=2034\n")
                    self.assertEqual(run.stderr, "")

    def test_gcc_actual_propagation(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_actual_propagation(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
