#include "common.hpp"
#include <array>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <climits>
int gameData;
alignas(4) static unsigned char arenas[2][0x25000];
static std::vector<std::array<int,3>> calls;
static bool replace_on_callback;
static int lane;
static void require(bool value,const char *what) { if(!value){std::fprintf(stderr,"binding FAIL %s\n",what);std::exit(1);} }
static void dimensions(unsigned char *p) { *(_DWORD*)(p+MAP_WIDTH_TILES_OFFSET)=100;*(_DWORD*)(p+MAP_HEIGHT_TILES_OFFSET)=100; }
static void seed(unsigned char *p,int x,int y) { p[PLAYER_RUNTIME_STATE_OFFSET+PLAYER_REVEALED_TILES_OFFSET+13*x+y/8]|=(unsigned char)(1u<<(y&7)); }
static bool bit(unsigned char *p,int x,int y) { return p[PLAYER_RUNTIME_STATE_OFFSET+PLAYER_REVEALED_TILES_OFFSET+13*x+y/8]&(1u<<(y&7)); }
static void reset() {
  std::memset(arenas,0xa5,sizeof arenas);
  for(auto &arena:arenas){dimensions(arena);for(int p=0;p<6;p++)std::memset(arena+PLAYER_RUNTIME_STATE_OFFSET+PLAYER_DATA_STRIDE*p+PLAYER_REVEALED_TILES_OFFSET,0,1300);}
  gameData=(int)(intptr_t)arenas[0];calls.clear();replace_on_callback=false;
}
void *MiniMap_DrawTileCell(void *x,int y) {
  int which=gameData==(int)(intptr_t)arenas[0]?0:1;
  require(bit(arenas[which],(int)(intptr_t)x,y),"bit must be set before callback");
  calls.push_back({which,(int)(intptr_t)x,y});
  if(replace_on_callback){replace_on_callback=false;gameData=(int)(intptr_t)arenas[1];}
  return x;
}
char TextSprite_SetStyleFlag(char) { require(false,"unexpected style callback");return 0; }
int main() {
  require((uintptr_t)arenas+sizeof arenas<INT_MAX,"signed low32 arenas");reset();
  std::array<unsigned char,sizeof arenas> saved;std::memcpy(saved.data(),arenas,sizeof arenas);
  auto held=clash95::WorldMap::borrow();require(std::memcmp(saved.data(),arenas,sizeof arenas)==0,"constructor wrote bytes");
  const int invalid[][2]={{-1,50},{100,50},{50,-1},{50,100},{INT_MIN,50},{INT_MAX,50},{50,INT_MIN},{50,INT_MAX}};
  for(const auto &position:invalid) {
    require(Reference_Map_IsTileVisibleToPlayer(position[0],position[1],0)==0,"frozen query signed bounds");
    require(Map_IsTileVisibleToPlayer(position[0],position[1],0)==0,"adapter query signed bounds");
    require(held.Map_IsTileVisibleToPlayer(position[0],position[1],0)==0,"direct query signed bounds");
    require(calls.empty() && std::memcmp(saved.data(),arenas,sizeof arenas)==0,"query bounds changed bytes or callbacks");
  }
  seed(arenas[0],50,50);
  require(held.Map_IsTileVisibleToPlayer(50,50,0)==1,"initial borrowed arena");
  gameData=(int)(intptr_t)arenas[1];
  require(held.Map_IsTileVisibleToPlayer(50,50,0)==0,"held object cached arena");
  require(Map_IsTileVisibleToPlayer(50,50,0)==0,"adapter cached arena");
  seed(arenas[1],50,50);require(held.Map_IsTileVisibleToPlayer(50,50,0)==1,"held object lost live bytes");
  std::memcpy(saved.data(),arenas,sizeof arenas);gameData=INT_MIN;
  {auto inert=clash95::WorldMap::borrow();(void)inert;}
  require(gameData==INT_MIN && std::memcmp(saved.data(),arenas,sizeof arenas)==0,"binding/destruction acted on invalid handle");
  std::vector<std::array<int,3>> expected_calls;int expected_return=0,expected_handle=0;
  for(lane=0;lane<3;lane++) {
    reset();seed(arenas[1],48,50);replace_on_callback=true;int answer;
    if(lane==0)answer=Reference_Map_RevealTileWithPropagation(50,50,0);
    else if(lane==1)answer=Map_RevealTileWithPropagation(50,50,0);
    else answer=held.Map_RevealTileWithPropagation(50,50,0);
    if(lane==0){std::memcpy(saved.data(),arenas,sizeof arenas);expected_calls=calls;expected_return=answer;expected_handle=gameData;}
    else require(std::memcmp(saved.data(),arenas,sizeof arenas)==0 && calls==expected_calls && answer==expected_return && gameData==expected_handle,"callback rebinding differs from frozen source");
    require(calls==std::vector<std::array<int,3>>{{0,50,50},{1,49,50}},"exact recursive arena callback order");
    require(bit(arenas[0],50,50) && !bit(arenas[0],49,50) && bit(arenas[1],49,50) && !bit(arenas[1],50,50),"callback arena writes");
  }
  std::puts("binding lanes=3 held_rebinding=exact callback_rebinding=exact constructor_destructor=pass complete_bytes=303104");
}