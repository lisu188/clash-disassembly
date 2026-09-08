BOOL  QueuedPath_StartsAtTile(_DWORD *pathBuffer, int tileRow, int tileColumn)
{
  int firstStep; // eax

  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  return (unsigned __int8)firstStep == tileRow && BYTE1(firstStep) == tileColumn;
}
