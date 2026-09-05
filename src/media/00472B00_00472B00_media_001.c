/* Generated from src/recovered/media/00472B00_media_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00472B00) --------------------------------------------------------
int __fastcall Mem_SetAllocFlag(int new_alloc_flag, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = g_Mem_AllocFlag;
  g_Mem_AllocFlag = new_alloc_flag;
  return previous_state;
}
