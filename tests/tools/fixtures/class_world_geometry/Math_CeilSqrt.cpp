signed int  Math_CeilSqrt(signed int value)
{
  int quotient; // eax
  int estimate; // ecx

  if ( value < 4 )
    return 1;
  quotient = value / 20 + 2;
  estimate = quotient;
  do
  {
    while ( 1 )
    {
      estimate = (estimate + quotient) / 2;
      quotient = value / estimate;
      if ( estimate - value / estimate <= 0 )
        break;
      if ( estimate - value / estimate <= 1 )
        return estimate;
    }
  }
  while ( value / estimate - estimate > 1 );
  return estimate;
}
