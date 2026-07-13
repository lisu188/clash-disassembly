/* Recovered audio, music, AVI, and media support, continued.
 * Original function-marker range: 0x00472B00..0x00472B00.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00472B00) --------------------------------------------------------
int __fastcall unknown_libname_5(int a1, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = g_Mem_AllocFlag;
  g_Mem_AllocFlag = a1;
  return previous_state;
}

