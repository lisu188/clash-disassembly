BOOL  QueuedPath_StartsInBuildingFootprint(_DWORD *pathBuffer, int buildingIndex)
{
  unsigned __int8 *buildingRecord; // eax
  int firstStep; // edx
  BOOL result; // eax
  unsigned __int8 buildingColumn; // bh

  buildingRecord = (unsigned __int8 *)(uintptr_t)(UNIT_RECORD(buildingIndex));
  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  if ( !buildingRecord[4] )
    return (_WORD)firstStep == *(_WORD *)buildingRecord;
  result = 0;
  if ( (unsigned __int8)firstStep >= *buildingRecord && (unsigned __int8)firstStep <= *buildingRecord + 1 )
  {
    buildingColumn = buildingRecord[1];
    if ( BYTE1(firstStep) >= buildingColumn && BYTE1(firstStep) <= buildingColumn + 1 )
      return 1;
  }
  return result;
}
