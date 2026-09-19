unsigned int  Rng_RandRange(int minValue, int maxValue)
{
  unsigned int range;
  unsigned int seed;
  int result;

  g_RngState ^= Time_Now(0, 0) + 0x34523471u;
  seed = (unsigned int)g_RngState + 0x83356532u * (unsigned int)Time_Now(0, 0);
  g_RngState = (int)seed;
  range = (unsigned int)((__int64)maxValue + 1 - minValue);
  if ( !range )
    return (unsigned int)minValue;
  result = (int)(seed % range) + minValue;
  return (unsigned int)result;
}
