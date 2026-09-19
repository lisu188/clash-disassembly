#include "units/units_internal.h"
#include "strategic/strategic_internal.h"
#include <unistd.h>
extern "C" int gameData;
extern const char *aPrzegrupujar_0;
extern "C" void j__nfree_();
static void output(const char*p,unsigned n){while(n){ssize_t r=write(1,p,n);if(r<=0)_exit(98);p+=r;n-=(unsigned)r;}}
static void message(const char*p){output(p,strlen(p));}
static void number(unsigned x){char b[32];int n=snprintf(b,sizeof(b),"%u ",x);output(b,n);}
static void die(unsigned x){number(x);message("FAIL\n");_exit(x);}
