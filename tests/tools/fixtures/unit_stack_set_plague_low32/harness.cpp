#include "recovered_layout.h"
#include "units/units_internal.h"
#include "units/UnitStack.hpp"
#include <sys/mman.h>
static_assert(sizeof(int)==4 && sizeof(uintptr_t)==8);
static_assert(sizeof(UnitSlotRecord)==31 && alignof(UnitSlotRecord)==1);
static_assert(UNIT_SLOT_FLAG_PLAGUE==8 && UNIT_STACK_SLOT_COUNT==10);
__TARGET__
int main() {
  const uintptr_t starts[]={0x30000000u,0x7ffff000u,0x90000000u};
  const size_t lengths[]={4096,12288,4096};
  for(int i=0;i<3;++i) {
    void *p=mmap((void*)starts[i],lengths[i],PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
    if(p!=(void*)starts[i])return 2;
  }
  uint32_t row[2];unsigned char input[800];
  while(fread(row,8,1,stdin)==1) {
    if(fread(input,800,1,stdin)!=1 || row[0]!=0)return 3;
    auto *image=(unsigned char*)uintptr_t(row[1]-32);memcpy(image,input,800);
    int address;memcpy(&address,&row[1],4);
    int signed_result=UnitStack_SetPlagueFlag(address);
    uint32_t result;memcpy(&result,&signed_result,4);
    if(fwrite(&result,4,1,stdout)!=1 || fwrite(image,800,1,stdout)!=1)return 4;
  }
  if(ferror(stdin)||fflush(stdout))return 5;
  for(int i=0;i<3;++i)if(munmap((void*)starts[i],lengths[i]))return 6;
  return 0;
}
