#include "units/units_internal.h"
#include "units/units_state.h"
#include "units/units_shared_state.h"
#include "buildings/buildings_api.h"
#include "strategic/strategic_api.h"
#include <sys/mman.h>
#include <vector>
#include <string>
#include <limits.h>

int gameData=0, g_CurrentPlayerIndex=0, g_SelectedUnitIndex=0;
int logEnabled=0, battleLogEnabled=0;
char aUnit_newturn[15]="Unit_NewTurn";
char aLogallunits[12]="LogAllUnits";
__int16 g_BuildingTypeMaxHitPoints[4]={100,200,300,400};
static unsigned char *world;
static constexpr size_t BYTES=0x90000;
static std::vector<std::string> calls;
static int wrapped_calls;
static void require(bool condition,const char *message) { if(!condition) { fprintf(stderr,"FAIL %s\n",message); exit(1); } }
static void p16(unsigned char *p,int v) { int16_t value=(int16_t)v; memcpy(p,&value,2); }
static void p32(unsigned char *p,int v) { int32_t value=v; memcpy(p,&value,4); }
static unsigned char *stack0() { return world+UNIT_STACK_TABLE_OFFSET; }
static void prepare() {
  memset(world,0,BYTES);
  for(int i=0;i<500;i++) p16(world+UNIT_STACK_TABLE_OFFSET+725*i+6,-1);
  auto *stack=stack0(); p16(stack,1); p16(stack+2,2); p16(stack+6,1); p16(stack+37,-1);
  p32(stack+316,1); stack[320]=4; stack[321]=5; stack[19]=1;
  p16(world+TILE_MAP_OFFSET+TILE_ROW_STRIDE*4+2*5,TILE_OCCUPANT_BUILDING_INDEX_BASE);
  auto *building=world+509674; building[2]=1; building[4]=0; p16(building+16,1);
  p16(world+140022,1);
  calls.clear(); wrapped_calls=0;
}
void Diagnostics_TraceWorldMapActionEvent(const char *stage,int,int,int,int) { calls.push_back(stage); }
BOOL UnitSlot_CanRecoverFatigue(int) { return 1; }
BOOL UnitSlot_ShouldGainFatigueFromLowActionPoints(int) { return 1; }
BOOL UnitSlot_HasSevereFatigue(int) { return 1; }
signed int UnitStack_AdjustFatigueByPredicate(__int16 *p,int delta,BOOL(*predicate)(int),DWORD mask,double context) {
  require((unsigned char *)p==stack0() && delta==-20 && predicate==UnitSlot_CanRecoverFatigue && mask==0xFFFFFFFF && context==1.25,"fatigue callback contract");
  calls.push_back("fatigue"); return 0;
}
signed int UnitStack_AdjustMoraleByPredicate(__int16 *,int,BOOL(*)(int),DWORD,double) { require(false,"unexpected morale callback"); return 0; }
__int16 *UnitStack_ClearSpentTurnFlag(int p) { require(p==(int)(intptr_t)stack0(),"spent receiver"); calls.push_back("clear_spent"); return (__int16 *)(intptr_t)p; }
int UnitSlot_CalcActionPointsFromFatigue(__int16 *p) { require((unsigned char *)p==stack0()+6,"AP receiver"); calls.push_back("calc_ap"); return 17; }
signed int Rules_LinkArmyFact(clash95_unaligned_int16 *p,int,int,double context,char,DWORD) { require((unsigned char *)p==stack0() && context==1.25,"rule receiver/context"); calls.push_back("rules_link"); return 0; }
void Unit_CheckLowMorale(_BYTE *p,double context) { require(p==stack0() && context==1.25,"morale receiver/context"); calls.push_back("low_morale"); }
signed int UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *p,DWORD,double context) { require((unsigned char *)p==stack0() && context==1.25,"plague receiver/context"); calls.push_back("plague"); return 0; }
__int16 *UnitStack_ClearReadyFlags(int p) { require(p==(int)(intptr_t)stack0(),"clear receiver"); calls.push_back("clear_ready"); stack0()[19]=0; return (__int16 *)(intptr_t)p; }
void UnitStack_ExecuteQueuedPath(unsigned int,int,char,DWORD,double) { require(false,"enemy contact must skip path execution"); }
signed int Unit_DebugDumpFormationSizes(int p,DWORD context) { require(p==(int)(intptr_t)stack0() && context==0xFFFFFFFF,"formation callback"); calls.push_back("formation"); stack0()[20]^=0x5A; return 91; }
extern "C" signed int __real_LogAllUnits(int,char,DWORD);
extern "C" signed int __wrap_LogAllUnits(int context,char second,DWORD third) {
  require(context==0,"first-stack exit must supply defined zero logging context");
  require(second==0 && third==0xFFFFFFFF,"other logging context preserved");
  ++wrapped_calls; calls.push_back("log_all");
  return __real_LogAllUnits(context,second,third);
}
int main() {
  world=(unsigned char *)mmap(nullptr,BYTES,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
  require(world!=MAP_FAILED && (uintptr_t)world+BYTES<INT_MAX,"low32 allocation"); gameData=(int)(intptr_t)world;
  const std::vector<std::string> expected_calls={"unit_new_turn_enter","unit_new_turn_stack","fatigue","unit_new_turn_after_recover_fatigue","unit_new_turn_after_human_fatigue","clear_spent","unit_new_turn_after_clear_spent","calc_ap","unit_new_turn_after_ap","rules_link","unit_new_turn_after_rules_fact","low_morale","unit_new_turn_after_low_morale","plague","unit_new_turn_after_plague","unit_new_turn_after_ready_check","clear_ready","unit_new_turn_done_enemy_contact","log_all","formation"};
  int cases=0;
  for(int flags=0;flags<4;flags++) {
    logEnabled=flags&1; battleLogEnabled=(flags>>1)&1;
    prepare(); std::vector<unsigned char> expected(world,world+BYTES);
    expected[UNIT_STACK_TABLE_OFFSET+14]=17; expected[UNIT_STACK_TABLE_OFFSET+19]=0; expected[UNIT_STACK_TABLE_OFFSET+20]^=0x5A;
    require(Unit_NewTurn(41,(char)0xD3,0xF1234567,1.25)==-1,"original LogAllUnits result");
    require(wrapped_calls==1 && calls==expected_calls,"enemy-exit callback order");
    require(expected==std::vector<unsigned char>(world,world+BYTES),"complete world state after first-stack exit");
    ++cases;
    // The actual production LogAllUnits and Debug_Log must ignore argument one.
    const int arguments[]={INT_MIN,-1,0,1,725,362500,INT_MAX};
    for(int argument:arguments) {
      prepare(); expected.assign(world,world+BYTES); expected[UNIT_STACK_TABLE_OFFSET+20]^=0x5A;
      require(__real_LogAllUnits(argument,0,0xFFFFFFFF)==-1,"argument-independent log result");
      require(calls==std::vector<std::string>{"formation"},"argument-independent callbacks");
      require(expected==std::vector<unsigned char>(world,world+BYTES),"argument-independent complete world"); ++cases;
    }
  }
  printf("PASS recovery_cases=%d first_stack_enemy_exits=4 logging_context_extremes=28 complete_world_bytes=589824 actual_logging_callees=2\n",cases);
  munmap(world,BYTES);
}
