
#include "common.hpp"
#include <cstring>
#include <climits>
#include <cstdio>
#include <cstdlib>

int gameData;
alignas(4) static unsigned char fog_memory[0x25000], fog_before[0x25000];
static int center_x, center_y, active_player, calls, style_calls, entry_lane;
static const clash95::WorldMap *held_world;
static unsigned int visible_mask;
static unsigned char style;
static int trace[9][3];
static const int bit_dx[9] = {1, 0, -1, 1, -1, 1, 0, -1, 0};
static const int bit_dy[9] = {1, 1, 1, 0, 0, -1, -1, -1, 0};
static bool in_bounds(int x, int y) {
  return x >= 0 && y >= 0 && x < 100 && y < 100;
}
static void query_trace(int x,int y,int player) {
  if(calls==9)std::abort();
  trace[calls][0]=x;trace[calls][1]=y;trace[calls++][2]=player;
}
extern "C" BOOL __real_Reference_Map_IsTileVisibleToPlayer(int,int,int);
extern "C" BOOL __wrap_Reference_Map_IsTileVisibleToPlayer(int x,int y,int player) {
  query_trace(x,y,player);return __real_Reference_Map_IsTileVisibleToPlayer(x,y,player);
}
extern "C" BOOL __real__ZNK7clash958WorldMap25Map_IsTileVisibleToPlayerEiii(const clash95::WorldMap*,int,int,int);
extern "C" BOOL __wrap__ZNK7clash958WorldMap25Map_IsTileVisibleToPlayerEiii(const clash95::WorldMap *object,int x,int y,int player) {
  query_trace(x,y,player);return __real__ZNK7clash958WorldMap25Map_IsTileVisibleToPlayerEiii(object,x,y,player);
}
void *MiniMap_DrawTileCell(void*,int) { std::abort(); }
char TextSprite_SetStyleFlag(char value) {
  ++style_calls;
  style = (unsigned char)value;
  return value;
}
static int Fixture_Classify(int x,int y,int player) {
  if(entry_lane==0)return Reference_Map_ClassifyFogOfWarOverlayForPlayer(x,y,player);
  if(entry_lane==1)return Map_ClassifyFogOfWarOverlayForPlayer(x,y,player);
  return held_world->Map_ClassifyFogOfWarOverlayForPlayer(x,y,player);
}
static const signed char expected[256] = {0,12,7,7,11,12,7,7,5,5,8,8,5,5,8,8,4,4,6,6,4,4,6,6,-1,-1,-1,-1,-1,-1,-1,-1,10,12,7,7,11,12,7,7,5,5,8,8,5,5,8,8,4,4,6,6,4,4,6,6,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,2,2,-1,-1,3,3,-1,-1,3,3,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,2,2,-1,-1,3,3,-1,-1,3,3,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,12,7,7,9,12,7,7,5,5,8,8,5,5,8,8,4,4,6,6,4,4,6,6,-1,-1,-1,-1,-1,-1,-1,-1,9,12,7,7,9,12,7,7,5,5,8,8,5,5,8,8,4,4,6,6,4,4,6,6,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,2,2,-1,-1,3,3,-1,-1,3,3,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,2,2,-1,-1,3,3,-1,-1,3,3,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int main() {
  if((uintptr_t)fog_memory+sizeof fog_memory>INT_MAX)std::abort();
  gameData=(int)(intptr_t)fog_memory;
  auto held=clash95::WorldMap::borrow();held_world=&held;
  const int positions[][2] = {{50,50}, {0,0}, {99,99}, {0,50}, {99,50},
                              {50,0}, {50,99}, {-1,50}, {100,50}, {50,-1}, {50,100}};
  const int order_dx[9] = {0,-1,0,1,-1,1,-1,0,1};
  const int order_dy[9] = {0,-1,-1,-1,0,0,1,1,1};
  unsigned int tested = 0;
  for(entry_lane=0;entry_lane<3;entry_lane++)
  for (const auto &position : positions) for (int player = 0; player < 6; ++player)
    for (unsigned int mask = 0; mask < 512; ++mask) {
      center_x = position[0]; center_y = position[1]; active_player = player;
      visible_mask = mask; calls = 0; style_calls = 0; style = 0xa5;
      unsigned int clipped_mask = 0;
      for (int bit = 0; bit < 9; ++bit)
        if ((mask & (1u << bit)) && in_bounds(center_x + bit_dx[bit], center_y + bit_dy[bit]))
          clipped_mask |= 1u << bit;
      std::memset(fog_memory,0xa5,sizeof fog_memory);
      *(_DWORD*)(fog_memory+MAP_WIDTH_TILES_OFFSET)=100;
      *(_DWORD*)(fog_memory+MAP_HEIGHT_TILES_OFFSET)=100;
      for(int p=0;p<6;p++)std::memset(fog_memory+PLAYER_RUNTIME_STATE_OFFSET+PLAYER_DATA_STRIDE*p+PLAYER_REVEALED_TILES_OFFSET,0,1300);
      for(int bit=0;bit<9;bit++)if(clipped_mask&(1u<<bit)) {
        int x=center_x+bit_dx[bit],y=center_y+bit_dy[bit];
        fog_memory[PLAYER_RUNTIME_STATE_OFFSET+PLAYER_DATA_STRIDE*player+PLAYER_REVEALED_TILES_OFFSET+13*x+y/8]|=(unsigned char)(1u<<(y&7));
      }
      std::memcpy(fog_before,fog_memory,sizeof fog_memory);
      const bool center_visible = (clipped_mask & 256) != 0;
      const int want = center_visible ? -1 : expected[clipped_mask & 255];
      const int want_style_calls = !center_visible && (clipped_mask & 255) ? 1 : 0;
      const int result = Fixture_Classify(center_x, center_y, player);
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
      if(std::memcmp(fog_memory,fog_before,sizeof fog_memory))std::abort();
      ++tested;
    }
  if(tested!=3*33792)std::abort();
  std::printf("fog cases=33792 lanes=3 actual_query_order=exact complete_bytes=151552\n");
}
