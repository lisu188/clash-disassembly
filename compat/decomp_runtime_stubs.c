#include "../defs.h"

/*
 * Narrow compile-time quarantine for late runtime helpers that still need
 * asm-backed reconstruction. These are outside the user-priority gameplay
 * path and are kept isolated so clash95.c can continue compiling.
 */

unsigned __int16 __ES__;
unsigned __int16 __DS__;

int __fastcall sub_4697E0(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int sub_4849EE(void)
{
  return 0;
}

void __noreturn sub_4842DF(int a1, int a2)
{
  (void)a1;
  (void)a2;
  abort();
}

int sub_48469F(void)
{
  return 0;
}
