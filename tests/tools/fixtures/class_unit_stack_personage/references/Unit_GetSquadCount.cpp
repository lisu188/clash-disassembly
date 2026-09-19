signed int Unit_GetSquadCount(intptr_t a1)
{
  unsigned char *slot;
  int squad_count;

  slot = (unsigned char *)(a1 + 6);
  squad_count = 0;
  while ( squad_count < 10 )
  {
    if ( *(short *)slot == -1 )
      break;
    ++squad_count;
    slot += 31;
  }
  return squad_count;
}
