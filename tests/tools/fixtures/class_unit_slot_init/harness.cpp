#include "units/UnitSlot.hpp"
#include "world/world_api.h"
#include "recovered_structs.h"
#include <sys/mman.h>
#include <type_traits>

static_assert(sizeof(clash95::UnitSlot)==sizeof(intptr_t));
static_assert(std::is_trivially_destructible_v<clash95::UnitSlot>);
static_assert(std::is_same_v<decltype(&UnitSlot_InitFromType),int (*)(int,unit_type,char)>);
static_assert(sizeof(unit_type)==4 && sizeof(UnitSlotRecord)==31);
static_assert(offsetof(UnitTypeRuntimeCoreMetadataRecord,flags)==18);
extern int Reference_UnitSlot_InitFromType(int,unit_type,char);
extern "C" const UnitTypeRuntimeCoreMetadataRecord *__real_UnitSlot_BorrowTypeMetadata(void);
extern "C" const UnitTypeRuntimeCoreMetadataRecord *__wrap_UnitSlot_BorrowTypeMetadata(void);
const UnitTypeRuntimeCoreMetadataRecord *fixtureMetadata;
static UnitTypeRuntimeCoreMetadataRecord mutable_table[40];
static unsigned long calls,cases,sentinel_cases;
static bool real_binding;
extern "C" const UnitTypeRuntimeCoreMetadataRecord *__wrap_UnitSlot_BorrowTypeMetadata(void) {
  ++calls;
  return real_binding ? __real_UnitSlot_BorrowTypeMetadata() : fixtureMetadata;
}
using Callback=int (*)(int,unit_type,char);
static int check(unsigned char *arena,int alignment,unsigned type,int owner,int seed,int ap,unsigned flags,int prior_ap=-1,int prior_morale=-1) {
  unsigned char initial[256],expected[256];
  UnitTypeRuntimeCoreMetadataRecord table_before[40];
  for(unsigned i=0;i<256;++i)initial[i]=(unsigned char)(i*73u+seed);
  unsigned char *record=arena+96+alignment;
  int receiver=(int)(intptr_t)record;
  if(prior_ap>=0)initial[96+alignment+8]=(unsigned char)prior_ap;
  if(prior_morale>=0)initial[96+alignment+11]=(unsigned char)prior_morale;
  if(!real_binding && type<40){mutable_table[type].base_action_points=(unsigned char)ap;mutable_table[type].flags=flags;}
  memcpy(table_before,fixtureMetadata,sizeof(table_before));
  memcpy(arena,initial,sizeof(initial));
  Callback volatile reference=Reference_UnitSlot_InitFromType;
  int wanted=reference(receiver,(unit_type)type,(char)owner);
  memcpy(expected,arena,sizeof(expected));
  if(wanted!=receiver || memcmp(table_before,fixtureMetadata,sizeof(table_before)))return 90;
  for(int route=0;route<2;++route){
    memcpy(arena,initial,sizeof(initial));calls=0;
    const clash95::UnitSlot slot((intptr_t)receiver);
    if(memcmp(arena,initial,sizeof(initial)) || calls)return 91;
    Callback volatile adapter=UnitSlot_InitFromType;
    int result=route ? slot.UnitSlot_InitFromType((unit_type)type,(char)owner) : adapter(receiver,(unit_type)type,(char)owner);
    if(result!=wanted || memcmp(arena,expected,sizeof(expected)) || memcmp(table_before,fixtureMetadata,sizeof(table_before)) || calls!=(type==0xFFFFFFFFu?0u:2u)){
      fprintf(stderr,"FAIL case=%lu type=%u owner=%d seed=%d alignment=%d ap=%d flags=%x route=%d returned=%d/%d calls=%lu\n",cases,type,owner,seed,alignment,ap,flags,route,result,wanted,calls);
      return 1;
    }
  }
  ++cases;if(type==0xFFFFFFFFu)++sentinel_cases;return 0;
}
int main(){
  auto *arena=(unsigned char *)mmap(nullptr,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
  if(arena==MAP_FAILED || (uintptr_t)arena>0x7FFFF000u)return 92;
  const auto *real_table=__real_UnitSlot_BorrowTypeMetadata();
  if(!real_table)return 93;
  memcpy(mutable_table,real_table,sizeof(mutable_table));fixtureMetadata=mutable_table;
  const unsigned flags[]={0u,1u,2u,3u,0xFFFFFFFFu,0xFFFFFFFDu,0x80000000u,0x80000002u};
  for(int a=0;a<16;++a)for(unsigned t=0;t<41;++t)for(int owner=0;owner<256;++owner){
    unsigned type=t==40?0xFFFFFFFFu:t;
    if(int error=check(arena,a,type,owner,(owner*19)&255,owner,flags[owner&7]))return error;
  }
  for(int a=0;a<16;++a)for(unsigned t=0;t<40;++t)for(unsigned f:flags)for(int ap=0;ap<256;++ap)
    if(int error=check(arena,a,t,ap,(ap*17+t)&255,ap,f))return error;
  for(int a=0;a<16;++a)for(int ap=0;ap<256;++ap)for(int morale=0;morale<256;++morale)
    if(int error=check(arena,a,0xFFFFFFFFu,ap^morale,(ap+morale)&255,0,0,ap,morale))return error;
  for(int a=0;a<16;++a)for(unsigned t=0;t<41;++t)for(int seed=0;seed<256;++seed)
    if(int error=check(arena,a,t==40?0xFFFFFFFFu:t,seed,seed,seed,flags[seed&7]))return error;
  real_binding=true;fixtureMetadata=real_table;
  for(int a=0;a<16;++a)for(unsigned t=0;t<41;++t)for(int seed=0;seed<256;++seed)
    if(int error=check(arena,a,t==40?0xFFFFFFFFu:t,seed,seed,0,0))return error;
  printf("PASS cases=%lu sentinel_cases=%lu alignments=16 callback_and_method=exact full_record_and_table_bytes=exact explicit_initializer=pass\n",cases,sentinel_cases);
  return munmap(arena,4096)!=0;
}
