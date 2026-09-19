void  initRandomSeed(char a1, DWORD a2)
{
  g_RngState = time_();
  Debug_Log(0, a1, a2, (int)(intptr_t)aRandom_initSee);
}
