#include "recovered_layout.h"
#include "units/units_api.h"
#include "recovered_legacy_imports.h"
#include <sys/mman.h>
#include <unistd.h>
__HEADER__
static_assert(sizeof(UnitSlotRecord)==31 && alignof(UnitSlotRecord)==1);
static_assert(sizeof(UnitStackRecord)==725 && alignof(UnitStackRecord)==1);
static unsigned cases_seen;
static int helper_calls;
static intptr_t helper_argument;
static unsigned char *trace_image;
static size_t trace_size;
static unsigned char helper_image[800];
static int override_count = -1000;
static void require(bool condition,const char *message) {
 if(!condition){fprintf(stderr,"case=%u %s\n",cases_seen,message);abort();}
}
__HELPER__
signed int Unit_GetSquadCount(intptr_t stackPtr) {
 ++helper_calls;helper_argument=stackPtr;
 if(trace_size)memcpy(helper_image,trace_image,trace_size);
 return override_count==-1000?Actual_Unit_GetSquadCount(stackPtr):override_count;
}
signed int UnitStack_HasSpecialPersonageUnits(intptr_t) {
 require(false,"maximum-tier method called the compatibility adapter");return -777;
}
__REFERENCES__
__METHODS__
extern "C" {
__ADAPTERS__
}
static int invoke(int family,int route,intptr_t base) {
 if(route==0) {
  if(family==0)return Reference_UnitStack_GetMaxOrderTier(base);
  if(family==1)return Reference_UnitStack_HasNormalCombatUnits(base);
  return Reference_UnitStack_HasSpecialPersonageUnits(base);
 }
 if(route==1) {
  const clash95::UnitStack stack(base);
  if(family==0)return stack.UnitStack_GetMaxOrderTier();
  if(family==1)return stack.UnitStack_HasNormalCombatUnits();
  return stack.UnitStack_HasSpecialPersonageUnits();
 }
 if(family==0)return UnitStack_GetMaxOrderTier(base);
 if(family==1)return UnitStack_HasNormalCombatUnits(base);
 return Actual_UnitStack_HasSpecialPersonageUnits(base);
}
static int checked(int family,int route,intptr_t base,const unsigned char *image) {
 int16_t first;memcpy(&first,(void*)(base+6),2);
 helper_calls=0;helper_argument=0;
 int result=invoke(family,route,base);
 require(helper_calls==int(family==1&&first!=-1),"procedural count call order/count");
 if(helper_calls){require(helper_argument==base,"procedural count receiver");if(trace_size)require(!memcmp(helper_image,image,trace_size),"procedural count observed changed bytes");}
 if(trace_size)require(!memcmp(trace_image,image,trace_size),"query changed record bytes");
 return result;
}
static void word(unsigned char *p,int16_t value){memcpy(p,&value,2);}
static void guard_cases() {
 auto *pages=(unsigned char*)mmap(nullptr,8192,PROT_NONE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
 require(pages!=MAP_FAILED,"guard map");require(mprotect(pages,4096,PROT_READ|PROT_WRITE)==0,"guard protect");
 trace_size=0;
 for(int prefix=0;prefix<=10;++prefix) {
  memset(pages,0,4096);
  unsigned char *base=pages+4096-(prefix==10?298:6+31*prefix+2);
  for(int i=0;i<prefix;++i){word(base+6+31*i,31);base[18+31*i]=1;}
  if(prefix<10)word(base+6+31*prefix,-1);
  for(int family=0;family<3;++family)for(int route=0;route<3;++route)
   require(checked(family,route,(intptr_t)base,nullptr)==int(family==0&&prefix!=0),"sentinel guard result");
  ++cases_seen;
 }
 require(munmap(pages,8192)==0,"guard unmap");
}
static void dependency_contracts(unsigned char *base) {
 unsigned char original[800];trace_image=base-32;trace_size=800;
 const int values[]={-32768,-2,-1,0,1,2,10,11};
 for(int empty=0;empty<2;++empty)for(int count:values)for(int marker=0;marker<11;++marker) {
  memset(trace_image,0x5a,800);
  for(int i=0;i<12;++i)word(base+6+31*i,i==marker?0:31);
  if(empty)word(base+6,-1);
  memcpy(original,trace_image,800);override_count=count;
  int result=checked(1,0,(intptr_t)base,original);
  for(int route=1;route<3;++route)require(checked(1,route,(intptr_t)base,original)==result,"controlled procedural return mismatch");
  ++cases_seen;
 }
 override_count=-1000;
}
int main() {
 void *normal=mmap((void*)uintptr_t(0x30000000),4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
 void *edge=mmap((void*)uintptr_t(0x7ffff000),8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
 require(normal==(void*)uintptr_t(0x30000000)&&edge==(void*)uintptr_t(0x7ffff000),"low32 maps");
 guard_cases();dependency_contracts((unsigned char*)normal+33);
 uint32_t header[2];unsigned char input[800];
 while(fread(header,8,1,stdin)==1) {
  require(header[0]==0&&fread(input,800,1,stdin)==1,"input framing");
  intptr_t base=header[1];trace_image=(unsigned char*)(base-32);trace_size=800;memcpy(trace_image,input,800);
  uint32_t output[3];
  for(int family=0;family<3;++family) {
   int reference=checked(family,0,base,input);output[family]=uint32_t(reference);
   for(int route=1;route<3;++route)require(checked(family,route,base,input)==reference,"canonical/adapter return mismatch");
  }
  require(fwrite(output,sizeof(output),1,stdout)==1&&fwrite(trace_image,800,1,stdout)==1,"output framing");
  ++cases_seen;
 }
 require(!ferror(stdin)&&fflush(stdout)==0,"stream I/O");
 require(munmap(normal,4096)==0&&munmap(edge,8192)==0,"unmap");
 fprintf(stderr,"PASS original_cases=87184 guarded_cases=11 controlled_dependency_cases=176 methods/adapters/frozen returns/full800bytes/helper_trace exact\n");
}
