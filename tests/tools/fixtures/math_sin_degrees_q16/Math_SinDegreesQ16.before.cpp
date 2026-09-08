int  Math_SinDegreesQ16(signed int degrees)
{
  int angle; // edx
  int absAngle; // edx

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
