#include "production-reference.inc"

int gameData = 0;
int g_SelectedUnitIndex = 0;
int g_CurrentPlayerIndex = 0;
char aUnit_newturn[15] = "Unit_NewTurn";
__int16 g_BuildingTypeMaxHitPoints[4] = {100,200,400,800};

namespace fixture {
constexpr size_t WORLD = 0x90000;
constexpr size_t SPAN = WORLD + 96;
unsigned char *arena;
unsigned char *world[2];
struct Event {
  std::string name;
  std::array<long long,6> args;
  bool operator==(const Event &) const = default;
};
std::vector<Event> events;
int rng_pos, rng_mode, switch_mode;
bool switched;
int phase, scenario, alignment;
long long address(intptr_t p) {
  if (p >= (intptr_t)arena && p < (intptr_t)arena + 2*(intptr_t)SPAN) return p - (intptr_t)arena;
  return p;
}
void event(const char *n, long long a=0,long long b=0,long long c=0,long long d=0,long long e=0,long long f=0) {
  events.push_back({n,{a,b,c,d,e,f}});
}
int integer(const void *p) { return (int)(intptr_t)p; }
void put16(unsigned char *p,int x) { uint16_t v=(uint16_t)x; memcpy(p,&v,2); }
void put32(unsigned char *p,int x) { uint32_t v=(uint32_t)x; memcpy(p,&v,4); }
int get16(const unsigned char *p) { int16_t v; memcpy(&v,p,2); return v; }
int get32(const unsigned char *p) { int32_t v; memcpy(&v,p,4); return v; }
void fail(const char *what) {
  fprintf(stderr,"FAIL %s phase=%d scenario=%d alignment=%d events=%zu\n",what,phase,scenario,alignment,events.size());
  exit(1);
}
int pred(BOOL (*p)(int)) {
  if(p == UnitSlot_CanRecoverFatigue) return 1;
  if(p == UnitSlot_ShouldGainFatigueFromLowActionPoints) return 2;
  if(p == UnitSlot_HasSevereFatigue) return 3;
  fail("predicate identity"); return 0;
}
void reset_calls() { events.clear(); rng_pos=0; switched=false; }
struct Result {
  std::vector<unsigned char> bytes;
  std::vector<Event> calls;
  intptr_t returned;
  int final_game, player, selected, rng;
  std::array<__int16,4> hitpoints;
  std::array<char,15> log_text;
};
Result snapshot(intptr_t returned,size_t bytes) {
  Result result{{arena,arena+bytes},events,returned,gameData,g_CurrentPlayerIndex,g_SelectedUnitIndex,rng_pos,{}, {}};
  memcpy(result.hitpoints.data(),g_BuildingTypeMaxHitPoints,sizeof(g_BuildingTypeMaxHitPoints));
  memcpy(result.log_text.data(),aUnit_newturn,sizeof(aUnit_newturn));
  return result;
}
void same(const Result &want,const Result &got) {
  if(want.bytes != got.bytes) fail("complete bytes differ");
  if(want.calls != got.calls) {
    size_t n=std::min(want.calls.size(),got.calls.size());
    for(size_t i=0;i<n;i++) if(!(want.calls[i]==got.calls[i])) {
      fprintf(stderr,"event %zu expected=%s actual=%s\n",i,want.calls[i].name.c_str(),got.calls[i].name.c_str());
      for(int j=0;j<6;j++) fprintf(stderr," %lld/%lld",want.calls[i].args[j],got.calls[i].args[j]);
      fprintf(stderr,"\n"); break;
    }
    fail("ordered callback/RNG trace differs");
  }
  if(want.returned != got.returned || want.final_game != got.final_game || want.player != got.player || want.selected != got.selected || want.rng != got.rng || want.hitpoints != got.hitpoints || want.log_text != got.log_text) fail("result or globals differ");
}
}

void Debug_Log(int a1,char a2,DWORD a3,int a4,...) { fixture::event("debug",a1,a2,a3,a4); }
void Diagnostics_TraceWorldMapActionEvent(const char *s,int a,int b,int c,int d) {
  using namespace fixture;
  event(s,a,b,c,d);
  ((unsigned char *)(intptr_t)gameData)[80]++;
  if(!switched && std::string(s)=="unit_new_turn_after_ap" && a==1 && switch_mode) {
    switched=true;
    if(switch_mode==1) gameData=integer(world[1]);
    else { g_CurrentPlayerIndex=(g_CurrentPlayerIndex+1)&3; g_SelectedUnitIndex=499; }
    event("fixture_switch_live_state",address(gameData),g_CurrentPlayerIndex,g_SelectedUnitIndex);
  }
}
BOOL UnitSlot_CanRecoverFatigue(int) { return 1; }
BOOL UnitSlot_ShouldGainFatigueFromLowActionPoints(int) { return 1; }
BOOL UnitSlot_HasSevereFatigue(int) { return 1; }
signed int UnitStack_AdjustFatigueByPredicate(__int16 *p,int delta,BOOL(*f)(int),DWORD mask,double ctx) {
  using namespace fixture; event("fatigue",address((intptr_t)p),delta,pred(f),mask,(int)(ctx*8));
  ((unsigned char *)p)[16]=(unsigned char)(((unsigned char *)p)[16]+delta);
  return 17;
}
signed int UnitStack_AdjustMoraleByPredicate(__int16 *p,int delta,BOOL(*f)(int),DWORD mask,double ctx) {
  using namespace fixture; event("morale",address((intptr_t)p),delta,pred(f),mask,(int)(ctx*8));
  ((unsigned char *)p)[17]^=0x18; return 18;
}
#ifndef UNIT_TURN_COMPOSED_SLOT_AP
int UnitSlot_CalcActionPointsFromFatigue(__int16 *p) {
  fixture::event("calc_ap",fixture::address((intptr_t)p)); return (255-((unsigned char *)p)[10])&255;
}
#endif
signed int Rules_LinkArmyFact(clash95_unaligned_int16 *p,int a,int b,double c,char d,DWORD e) {
  fixture::event("rules_link",fixture::address((intptr_t)p),fixture::address(a),b,(int)(c*8),d,e);
  ((unsigned char *)p)[721]^=0x3C; return 19;
}
void Unit_CheckLowMorale(_BYTE *p,double c) {
  fixture::event("low_morale",fixture::address((intptr_t)p),(int)(c*8)); p[18]^=0x35;
}
signed int UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *p,DWORD a,double c) {
  fixture::event("plague",fixture::address((intptr_t)p),a,(int)(c*8)); ((unsigned char *)p)[19]^=0x28; return 20;
}
__int16 *UnitStack_ClearReadyFlags(int p) {
  fixture::event("clear_ready",fixture::address(p)); ((unsigned char *)(intptr_t)p)[19]&=0xFE; return (__int16 *)(intptr_t)p;
}
void UnitStack_ExecuteQueuedPath(unsigned int index,int animate,char a,DWORD b,double c) {
  using namespace fixture; event("execute_path",index,animate,a,b,(int)(c*8));
  unsigned char *p=(unsigned char *)(intptr_t)gameData+UNIT_STACK_TABLE_OFFSET+UNIT_STACK_STRIDE*index;
  put16(p,get16(p)+1); put32(p+316,0); p[50]^=0x5A;
}
signed int LogAllUnits(int a,char b,DWORD c) { fixture::event("log_all",a,b,c); return 2301; }
unsigned int Rng_RandRange(int lo,int hi) {
  using namespace fixture;
  static const int values[12]={INT_MIN,-123,-1,0,1,89,99,100,101,255,256,INT_MAX};
  int answer=values[(rng_mode+rng_pos)%12]; event("rng",lo,hi,answer,rng_pos); ++rng_pos; return (unsigned int)answer;
}

#ifdef UNIT_TURN_CLASS_RANDOM_BOUNDARY
int g_RngState = 0;
char aRandom_initSee[29] = "Random_Init(): seed = 0x%08x";
// Preserve this fixture's arbitrary RNG boundary values, including values outside
// the requested interval. The GameRandom gate separately compiles its real body.
unsigned int clash95::GameRandom::Rng_RandRange(int lo, int hi) const {
  return ::Rng_RandRange(lo, hi);
}
#endif

namespace fixture {
void building_input(int seed,int countdown) {
  for(int i=0;i<1024;i++) arena[i]=(unsigned char)(i*37+seed*53);
  unsigned char *p=arena+32+alignment;
  p[421]=(unsigned char)(seed*7); p[429]=(unsigned char)countdown;
  for(int i=0;i<7;i++) p[422+i]=(unsigned char)(seed+i*41);
  gameData=integer(world[0]); g_CurrentPlayerIndex=seed&3; g_SelectedUnitIndex=seed*3; reset_calls();
}
void world_input(int seed) {
  for(size_t i=0;i<2*SPAN;i++) arena[i]=(unsigned char)(i*29+seed*13);
  world[0]=arena+32+alignment; world[1]=arena+SPAN+32+alignment;
  gameData=integer(world[0]); g_CurrentPlayerIndex=seed&3; g_SelectedUnitIndex=17;
  switch_mode=seed==13?1:seed==14?2:0;
  for(int w=0;w<2;w++) {
    for(int i=0;i<500;i++) {
      unsigned char *p=world[w]+UNIT_STACK_TABLE_OFFSET+i*UNIT_STACK_STRIDE;
      put16(p+6,-1); p[4]=(unsigned char)((g_CurrentPlayerIndex+1)&3);
    }
    for(int pl=0;pl<4;pl++) put32(world[w]+PLAYER_DATA_STRIDE*pl+140051,(seed&1)?1:0);
    put16(world[w]+140022,seed+31+w*100);
    if(seed==0) continue;
    int indexes[3]={seed==16?0:1,3,499};
    for(int index:indexes) {
      if(seed==15 && index!=499) continue;
      unsigned char *p=world[w]+UNIT_STACK_TABLE_OFFSET+index*UNIT_STACK_STRIDE;
      put16(p,20+index%7); put16(p+2,30); p[4]=(unsigned char)(seed==1 ? ((g_CurrentPlayerIndex+1)&3) : g_CurrentPlayerIndex);
      for(int j=0;j<10;j++) { put16(p+6+31*j,-1); p[19+31*j]&=0xFE; }
      int count=seed==7 || seed==19?10:seed==6 || seed==18?2:3;
      for(int j=0;j<count;j++) put16(p+6+31*j,(j+seed)%UNIT_TYPE_COUNT);
      if(seed==5) put16(p+6,UNIT_TYPE_COUNT);
      p[19]=(unsigned char)((seed>=3 && seed!=5 && seed<17)?1:0);
      if(seed==17) p[19+31]=1;
      if(seed==18) { put16(p+6+31*3,1); p[19+31*3]=1; }
      if(seed==19) p[19+31*9]=1;
      if(seed==20) { put16(p+6+31,UNIT_TYPE_COUNT); p[19+31*2]=1; }
      put32(p+316,seed==4 || seed==13 ? 4:0);
      p[320]=20; p[321]=30;
    }
    int building=-1;
    if(seed==8 || seed==9 || seed==10 || seed==16) building=0;
    if(seed==11) building=100;
    if(seed==12) building=101;
    put16(world[w]+TILE_MAP_OFFSET+TILE_ROW_STRIDE*20+2*30,building<0?0:TILE_OCCUPANT_BUILDING_INDEX_BASE+building);
    if(building>=0 && building<=100) {
      unsigned char *b=world[w]+509674+BUILDING_RECORD_SIZE*building;
      b[4]=(unsigned char)(seed==9?4:0); put16(b+16,seed==10?-1:0);
      b[2]=(unsigned char)((g_CurrentPlayerIndex+1)&3);
    }
  }
  reset_calls();
}
void run() {
  arena=(unsigned char *)mmap(nullptr,2*SPAN,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
  if(arena==MAP_FAILED || (uintptr_t)arena+2*SPAN>INT_MAX) fail("low32 mmap");
  world[0]=arena+32; world[1]=arena+SPAN+32;
  auto service=clash95::UnitTurn::borrow(); // Retain it while all referenced globals change.
  int regen_cases=0, damage_cases=0, turn_cases=0;
  phase=1;
  for(alignment=0;alignment<16;alignment++) for(scenario=0;scenario<256;scenario++) {
    building_input(scenario,scenario);
    unsigned char *p=arena+32+alignment;
    Result reference=snapshot((intptr_t)Reference_Unit_NewTurnRegen(p),1024);
    if(reference.returned!=(intptr_t)p+7) fail("regen original return contract");
    for(int path=0;path<2;path++) {
      building_input(scenario,scenario);
      intptr_t answer=(intptr_t)(path?Unit_NewTurnRegen(p):service.Unit_NewTurnRegen(p));
      same(reference,snapshot(answer,1024));
    }
    ++regen_cases;
  }
  phase=2;
  const int hp_values[]={0,1,99,100,101,-1,32767,-32768};
  for(alignment=0;alignment<16;alignment++) for(scenario=0;scenario<384;scenario++) {
    int type=scenario%4, hp=hp_values[(scenario/4)%8]; rng_mode=scenario/32;
    auto setup=[&](){ building_input(scenario,4); auto p=arena+32+alignment; p[4]=(unsigned char)type; put16(p+16,hp); for(int i=0;i<4;i++) g_BuildingTypeMaxHitPoints[i]=(__int16)(100+i*151+(scenario%3)*23); };
    setup(); int p=integer(arena+32+alignment);
    Result reference=snapshot(Reference_Unit_UpdatePerTurn(p,0x1234),1024);
    if(reference.rng != (hp==0?0:7)) fail("damage original RNG count");
    for(int path=0;path<2;path++) { setup(); int answer=path?Unit_UpdatePerTurn(p,-567):service.Unit_UpdatePerTurn(p,123); same(reference,snapshot(answer,1024)); }
    ++damage_cases;
  }
  phase=3;
  for(alignment=0;alignment<16;alignment++) for(scenario=0;scenario<21;scenario++) {
    world_input(scenario);
    Result reference=snapshot(Reference_Unit_NewTurn(101,(char)0xD3,0xF0102030,1.25),2*SPAN);
    if(scenario==16 && (reference.calls.back().name!="log_all" || reference.calls.back().args[0]!=0)) fail("repaired first-stack logging argument");
    for(int path=0;path<2;path++) { world_input(scenario); int answer=path?Unit_NewTurn(101,(char)0xD3,0xF0102030,1.25):service.Unit_NewTurn(101,(char)0xD3,0xF0102030,1.25); same(reference,snapshot(answer,2*SPAN)); }
    ++turn_cases;
  }
  printf("PASS regen_cases=%d damage_cases=%d turn_cases=%d alignments=16 entry_paths=method,adapter callback_and_rng_order=exact complete_bytes=exact live_binding_switches=covered\n",regen_cases,damage_cases,turn_cases);
  munmap(arena,2*SPAN);
}
}
int main() { fixture::run(); }
