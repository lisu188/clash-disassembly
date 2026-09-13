_BYTE * Unit_NewTurnRegen(_BYTE *result)
{
  _BYTE *slotsEnd; // ecx
  unsigned __int8 v2; // dl
  char countdown; // dl

  if ( result[429] )
  {
    countdown = result[429] - 1;
    result[429] = countdown;
    if ( !countdown )
      ++result[421];
  }
  slotsEnd = result + 7;
  do
  {
    v2 = result[422];
    if ( v2 < 0x64u )
    {
      result[422] = v2 + 10;
      if ( (unsigned __int8)(v2 + 10) > 0x64u )
        result[422] = 100;
    }
    ++result;
  }
  while ( result != slotsEnd );
  return result;
}
