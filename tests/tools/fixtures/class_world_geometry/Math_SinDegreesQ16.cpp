int  Math_SinDegreesQ16(signed int degrees)
{
  int angle; // edx
  int absAngle; // edx

  // x86 NEG preserves INT_MIN; its scaled DWORD address wraps to table[0].
  if ( degrees == INT32_MIN )
    return -g_MathSinTableQ16[0];

  angle = degrees;
  if ( degrees < 0 )
  {
    absAngle = -degrees;
    if ( -degrees >= 360 )
      absAngle %= 360;
    return -g_MathSinTableQ16[absAngle];
  }
  else
  {
    if ( degrees >= 360 )
      angle = degrees % 360;
    return g_MathSinTableQ16[angle];
  }
}
