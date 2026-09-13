
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>
static unsigned char arena[800], frozen[800];
static uint32_t random_state=0x412ac0af;
static unsigned scenarios;
static uint32_t random_word() {
 random_state^=random_state<<13;random_state^=random_state>>17;random_state^=random_state<<5;
 return random_state;
}
static void require(bool good,const char *what) {
 if(!good){fprintf(stderr,"scenario=%u %s\n",scenarios,what);abort();}
}
static void type(unsigned char *slot,int16_t value){memcpy(slot,&value,2);}
static void prepare(unsigned char *base,int prefix,int marked,unsigned flags) {
 static const int16_t ids[]={-32768,-2,0,1,32,127,32767};
 for(int i=0;i<10;++i) {
  unsigned char *slot=base+6+31*i;
  type(slot,i==prefix?-1:ids[(i+prefix+marked)%7]);
  slot[13]=uint8_t((random_word()&~12u)|((i>prefix)?12:0));
  if(i==marked)slot[13]=uint8_t(flags);
 }
}
static int invoke(int family,int route,intptr_t p) {
 const clash95::UnitStack record(p);
 if(family==0) {
  if(route==0)return Reference_UnitStack_HasPlague(int(p));
  if(route==1)return record.UnitStack_HasPlague();
  return UnitStack_HasPlague(int(p));
 }
 if(route==0)return Reference_UnitStack_HasLowMoraleUnit(int(p));
 if(route==1)return record.UnitStack_HasLowMoraleUnit();
 return UnitStack_HasLowMoraleUnit(int(p));
}
static void check(unsigned char *base,int prefix,int marked,unsigned flags) {
 memcpy(frozen,arena,800);
 for(int family=0;family<2;++family)for(int route=0;route<3;++route) {
  const unsigned mask=family==0?8:4;
  const int wanted=marked<prefix && marked<10 && (flags&mask)?1:0;
  const int actual=invoke(family,route,intptr_t(base));
  require(actual==wanted,"Boolean or sentinel contract");
  require(!memcmp(arena,frozen,800),"query or constructor changed backing bytes");
 }
 ++scenarios;
}
int main() {
 require(uintptr_t(arena)+sizeof(arena)<=INT_MAX,"fixture address must fit signed low32");
 const unsigned patterns[]={0,2,4,8,12,128,255,85,170,252,247,251,127,129,64,16};
 for(int alignment=0;alignment<16;++alignment)
  for(int prefix=0;prefix<=10;++prefix)
   for(int marked=0;marked<=10;++marked)
    for(unsigned flags:patterns) {
     for(auto &byte:arena)byte=uint8_t(random_word());
     unsigned char *base=arena+32+alignment;
     prepare(base,prefix,marked,flags);check(base,prefix,marked,flags);
    }
 for(unsigned flags=0;flags<=255;++flags)
  for(int prefix=0;prefix<=10;++prefix)
   for(int marked=0;marked<=10;++marked) {
    for(auto &byte:arena)byte=uint8_t(random_word());
    unsigned char *base=arena+32+(flags+prefix+marked)%16;
    prepare(base,prefix,marked,flags);check(base,prefix,marked,flags);
   }
 // Sentinel type reads end exactly at an inaccessible page. Its flags and all
 // following slots are unreadable; neither query may read them first.
 const long page=sysconf(_SC_PAGESIZE);require(page>0,"page size");
 auto *guard=(unsigned char*)mmap(nullptr,size_t(page)*3,PROT_NONE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT,-1,0);
 require(guard!=MAP_FAILED,"guard mapping");
 require(!mprotect(guard+page,size_t(page),PROT_READ|PROT_WRITE),"guard protection");
 for(int prefix=0;prefix<=10;++prefix) {
  auto *base=guard+2*page-2-6-31*prefix;
  memset(guard+page,0,size_t(page));
  for(int i=0;i<prefix;++i)type(base+6+31*i,32);
  type(base+6+31*prefix,-1);
  for(int family=0;family<2;++family)for(int route=0;route<3;++route)
   require(invoke(family,route,intptr_t(base))==0,"sentinel guard");
  ++scenarios;
 }
 auto *full=guard+2*page-(6+31*9+14);
 memset(guard+page,0,size_t(page));
 for(int i=0;i<10;++i)type(full+6+31*i,32);
 for(int family=0;family<2;++family)for(int route=0;route<3;++route)
  require(invoke(family,route,intptr_t(full))==0,"ten-slot guard");
 ++scenarios;require(!munmap(guard,size_t(page)*3),"guard release");
 // A positive record address whose later slots cross INT_MAX remains safe for
 // these queries. Do not silently constrain the borrowed record's full span.
 auto *edge=(unsigned char*)mmap((void*)uintptr_t(0x7ffff000),8192,PROT_READ|PROT_WRITE,
  MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
 require(edge==(void*)uintptr_t(0x7ffff000),"sign-boundary mapping");
 for(int alignment=0;alignment<16;++alignment)for(int prefix=0;prefix<=10;++prefix) {
  auto *base=edge+4096-32-alignment;
  memset(edge,0,8192);prepare(base,prefix,prefix?prefix-1:0,12);
  for(int family=0;family<2;++family)for(int route=0;route<3;++route)
   require(invoke(family,route,intptr_t(base))==(prefix?1:0),"sign-boundary query");
  ++scenarios;
 }
 require(!munmap(edge,8192),"sign-boundary release");
 printf("PASS cases=%u reference,direct,adapter full_bytes=exact sentinel_guards=exact sign_boundary=exact\n",scenarios);
}
