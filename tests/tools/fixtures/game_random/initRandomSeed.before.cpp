void  initRandomSeed(char a1, DWORD a2)
{
  int v2; // ecx

  g_RngState = time_();
  Debug_Log(v2, a1, a2, (int)(intptr_t)aRandom_initSee);
}
