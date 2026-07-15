/* Generated from src/recovered/media/00472B00_media_part2.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (00472B00) --------------------------------------------------------
int __fastcall Mem_SetAllocFlag(int new_alloc_flag, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = g_Mem_AllocFlag;
  g_Mem_AllocFlag = new_alloc_flag;
  return previous_state;
}
