#include <array>
#include <bit>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <vector>
#include <sys/mman.h>

extern "C" {
alignas(16) unsigned char random_state_image[64] = {};
alignas(16) unsigned char random_format_image[64] = {};
void __real_Debug_Log(int, char, DWORD, int, ...);
}
asm(".global g_RngState\n.set g_RngState, random_state_image+16\n");
asm(".global aRandom_initSee\n.set aRandom_initSee, random_format_image+16\n");
int logEnabled, battleLogEnabled;
int gameData, g_SelectedUnitIndex, g_CurrentPlayerIndex;
char aUnit_newturn[15] = "Unit_NewTurn";
__int16 g_BuildingTypeMaxHitPoints[4] = {100,251,402,553};
void Reference_initRandomSeed(char, DWORD);
unsigned int Reference_Rng_RandRange(int, int);
static_assert(std::is_trivially_destructible_v<clash95::GameRandom>);
static_assert(!std::is_polymorphic_v<clash95::GameRandom>);
static_assert(noexcept(clash95::GameRandom(aRandom_initSee, g_RngState)));

namespace {
using Bytes = std::array<unsigned char,64>;
struct Event {
  int kind;
  uint32_t state;
  int first, second;
  uint32_t third;
  std::array<unsigned char,29> format;
  bool operator==(const Event&) const = default;
};
std::vector<Event> events;
unsigned int tick_index;
int wall_time, tick_seed;
int *active_state = &g_RngState;
unsigned char *active_format = reinterpret_cast<unsigned char*>(aRandom_initSee);
unsigned long long cases;
void require(bool condition, const char *message) {
  if (!condition) {
    std::fprintf(stderr,"FAIL %s case=%llu tick=%u\n",message,cases,tick_index);
    std::exit(1);
  }
}
int bits(uint32_t v) { return std::bit_cast<int32_t>(v); }
void event(int kind, int first=0, int second=0, uint32_t third=0) {
  Event result{kind,static_cast<uint32_t>(*active_state),first,second,third,{}};
  std::memcpy(result.format.data(),active_format,result.format.size());
  events.push_back(result);
}
Bytes bytes(const unsigned char *p) { Bytes result; std::memcpy(result.data(),p,result.size()); return result; }
void setup(uint32_t initial, unsigned serial) {
  active_state=&g_RngState;
  active_format=reinterpret_cast<unsigned char*>(aRandom_initSee);
  for (unsigned i=0; i<64; ++i) {
    random_state_image[i]=static_cast<unsigned char>(i*71u+serial);
    random_format_image[i]=static_cast<unsigned char>(i*29u+serial*3u);
  }
  g_RngState=bits(initial); tick_index=0; events.clear();
  tick_seed=bits(serial*0x29375231u); wall_time=bits(initial^0xa31792u);
  logEnabled=serial&1u; battleLogEnabled=(serial>>1)&1u;
}
void guards(const Bytes& initial, const Bytes& final, unsigned start, unsigned size) {
  for (unsigned i=0; i<64; ++i)
    if (i<start || i>=start+size) require(initial[i]==final[i],"sentinel bytes");
}
struct Snapshot {
  unsigned result;
  Bytes state,format;
  std::vector<Event> calls;
  unsigned clock_reads;
  int logging,battle_logging;
  bool operator==(const Snapshot&) const = default;
};
Snapshot snapshot(unsigned result, const unsigned char *state=random_state_image,
                  const unsigned char *format=random_format_image) {
  return {result,bytes(state),bytes(format),events,tick_index,logEnabled,battleLogEnabled};
}
}
int time_(void) {
  event(1);
  return wall_time;
}
int Time_Now(int first, int second) {
  require(tick_index<32,"clock read count");
  event(2,first,second,tick_index);
  return bits(static_cast<uint32_t>(tick_seed)+0x97172653u*tick_index++);
}
extern "C" void __wrap_Debug_Log(int a1,char a2,DWORD a3,int a4,...) {
  require(static_cast<uint32_t>(a4)==static_cast<uint32_t>(reinterpret_cast<uintptr_t>(active_format)),"exact bound format pointer");
  event(3,a1,a2,a3);
  __real_Debug_Log(a1,a2,a3,a4);
}
namespace {
unsigned draw(int mode, const clash95::GameRandom& random, int lo,int hi) {
  if (mode==0) return Reference_Rng_RandRange(lo,hi);
  if (mode==1) return random.Rng_RandRange(lo,hi);
  if (mode==2) return clash95::GameRandom::borrow().Rng_RandRange(lo,hi);
  return Rng_RandRange(lo,hi);
}
void seed(int mode, const clash95::GameRandom& random, char first,DWORD second) {
  if (mode==0) return Reference_initRandomSeed(first,second);
  if (mode==1) return random.initRandomSeed(first,second);
  if (mode==2) return clash95::GameRandom::borrow().initRandomSeed(first,second);
  return initRandomSeed(first,second);
}
void verify_range(const clash95::GameRandom& random,uint32_t initial,int lo,int hi,unsigned serial) {
  setup(initial,serial); const Bytes state_before=bytes(random_state_image),format_before=bytes(random_format_image);
  const Snapshot want=snapshot(draw(0,random,lo,hi));
  require(want.clock_reads==2,"two clock reads");
  guards(state_before,want.state,16,4); require(format_before==want.format,"range format unchanged");
  for(int mode=1;mode<=3;++mode) {
    setup(initial,serial);
    const Snapshot got=snapshot(draw(mode,random,lo,hi));
    require(got==want,"repaired range bytes/returns/callback order");
  }
  ++cases;
}
void ranges(const clash95::GameRandom& random) {
  const int edges[]={INT_MIN,INT_MIN+1,-65536,-1,0,1,65535,INT_MAX-1,INT_MAX};
  unsigned serial=0;
  for(int lo:edges) for(int hi:edges) for(int initial:edges)
    verify_range(random,static_cast<uint32_t>(initial),lo,hi,serial++);
  uint32_t generator=0x49273231u;
  for(unsigned i=0;i<65536;++i) {
    auto next=[&](){ generator=generator*1664525u+1013904223u; return generator; };
    uint32_t initial=next(); int lo=bits(next()), hi=bits(next());
    verify_range(random,initial,lo,hi,serial++);
  }
}
void initializers(const clash95::GameRandom& random) {
  unsigned serial=0;
  for(int initial:{INT_MIN,-1,0,1,INT_MAX}) for(int first:{-128,-1,0,1,127})
    for(unsigned second:{0u,1u,0x80000000u,UINT32_MAX}) for(unsigned logging=0;logging<4;++logging) {
      setup(static_cast<uint32_t>(initial),logging+4u*serial);
      Bytes state_before=bytes(random_state_image),format_before=bytes(random_format_image);
      seed(0,random,static_cast<char>(first),second); Snapshot want=snapshot(0);
      require(want.calls.size()==2 && want.calls[0].kind==1 && want.calls[1].kind==3,"seed/log ordering");
      guards(state_before,want.state,16,4); guards(format_before,want.format,16,29);
      for(int mode=1;mode<=3;++mode) {
        setup(static_cast<uint32_t>(initial),logging+4u*serial);
        seed(mode,random,static_cast<char>(first),second);
        require(snapshot(0)==want,"repaired init bytes/callback ordering");
      }
      ++serial; ++cases;
    }
}
void alternate_bindings() {
  struct State { alignas(16) unsigned char before[16]; int word; unsigned char after[44]; } state;
  static_assert(sizeof(State)==64);
  unsigned char *state_image=reinterpret_cast<unsigned char*>(&state);
  struct Format { alignas(16) unsigned char before[16]; char value[29]; unsigned char after[19]; } format;
  static_assert(sizeof(Format)==64);
  auto& word=state.word;
  const clash95::GameRandom random(format.value,word);
  for(unsigned i=0;i<1024;++i) {
    uint32_t initial=i*0x97725239u;
    setup(initial,i); Reference_initRandomSeed(static_cast<char>(i),i*71u); Snapshot seed_want=snapshot(0);
    setup(initial,i);
    std::memcpy(state_image,random_state_image,64); std::memcpy(&format,random_format_image,64);
    const auto global_state=bytes(random_state_image),global_format=bytes(random_format_image);
    active_state=&word; active_format=reinterpret_cast<unsigned char*>(format.value);
    random.initRandomSeed(static_cast<char>(i),i*71u);
    require(snapshot(0,state_image,reinterpret_cast<unsigned char*>(&format))==seed_want,"independent retained seed/format binding");
    require(global_state==bytes(random_state_image) && global_format==bytes(random_format_image),"independent binding does not touch original globals");
    setup(initial,i); Snapshot range_want=snapshot(Reference_Rng_RandRange(INT_MIN,INT_MAX-1));
    setup(initial,i); std::memcpy(state_image,random_state_image,64); std::memcpy(&format,random_format_image,64);
    active_state=&word; active_format=reinterpret_cast<unsigned char*>(format.value);
    require(snapshot(random.Rng_RandRange(INT_MIN,INT_MAX-1),state_image,reinterpret_cast<unsigned char*>(&format))==range_want,"independent retained RNG word");
    require(global_state==bytes(random_state_image) && global_format==bytes(random_format_image),"independent RNG globals unchanged");
    ++cases;
  }
}
void composed_unit_turn() {
  unsigned char *arena=static_cast<unsigned char*>(mmap(nullptr,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0));
  require(arena!=MAP_FAILED && reinterpret_cast<uintptr_t>(arena)+4096<=INT_MAX,"low32 building fixture");
  const auto turn=clash95::UnitTurn::borrow();
  auto service=turn;
  const int hitpoints[]={0,1,99,100,101,-1,32767,-32768};
  ReferenceUnitTurn reference(g_BuildingTypeMaxHitPoints);
  for(unsigned alignment=0;alignment<16;++alignment) for(unsigned index=0;index<128;++index) {
    auto prepare=[&](){
      setup(index*0x91725321u,alignment+index);
      for(unsigned i=0;i<4096;++i) arena[i]=static_cast<unsigned char>(i*37u+index);
      unsigned char *building=arena+32+alignment;
      building[4]=index%4;
      int16_t hp=static_cast<int16_t>(hitpoints[(index/4)%8]); std::memcpy(building+16,&hp,2);
    };
    prepare(); int building=static_cast<int>(reinterpret_cast<uintptr_t>(arena+32+alignment));
    Snapshot want=snapshot(static_cast<unsigned>(reference.Unit_UpdatePerTurn(building,-27)));
    std::array<unsigned char,4096> expected; std::memcpy(expected.data(),arena,4096);
    for(int mode=0;mode<2;++mode) {
      prepare(); Snapshot got=snapshot(static_cast<unsigned>(mode ? Unit_UpdatePerTurn(building,1234) : service.Unit_UpdatePerTurn(building,-9876)));
      require(got==want && std::memcmp(expected.data(),arena,4096)==0,"composed UnitTurn actual RNG factory/direct/adapters");
    }
    ++cases;
  }
  munmap(arena,4096);
}
}
int main() {
  setup(0x7a521391u,17); Snapshot before=snapshot(0);
  {
    const clash95::GameRandom binding(aRandom_initSee,g_RngState);
    const auto factory=clash95::GameRandom::borrow();
    (void)binding; (void)factory;
    require(snapshot(0)==before,"binding-only constructor/factory");
  }
  require(snapshot(0)==before,"trivial lifecycle leaves state/calls unchanged");
  const clash95::GameRandom retained(aRandom_initSee,g_RngState);
  ranges(retained); initializers(retained); alternate_bindings(); composed_unit_turn();
  std::printf("PASS cases=%llu bindings=retained,independent composed_unit_turn=2048 dispatch=direct,borrow,adapter returns=exact full_bytes=exact callbacks=exact\n",cases);
}
