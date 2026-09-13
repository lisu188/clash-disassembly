/* Canonical class implementations; original identities are mapped in recovered_sources.json. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../units/QueuedPath.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

BOOL clash95::QueuedPath::QueuedPath_StartsAtTile(int tileRow, int tileColumn) const
{
  typedef _DWORD PathWord __attribute__((aligned(1), may_alias));
  PathWord *pathBuffer = (PathWord *)bytes_;
  int firstStep; // eax

  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  return (unsigned __int8)firstStep == tileRow && BYTE1(firstStep) == tileColumn;
}

BOOL clash95::QueuedPath::QueuedPath_StartsInBuildingFootprint(int buildingIndex) const
{
  typedef _DWORD PathWord __attribute__((aligned(1), may_alias));
  typedef _WORD BuildingWord __attribute__((aligned(1), may_alias));
  PathWord *pathBuffer = (PathWord *)bytes_;
  unsigned __int8 *buildingRecord; // eax
  int firstStep; // edx
  BOOL result; // eax
  unsigned __int8 buildingColumn; // bh

  buildingRecord = (unsigned __int8 *)(uintptr_t)(state_ + BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * (buildingIndex));
  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  if ( !buildingRecord[4] )
    return (_WORD)firstStep == *(BuildingWord *)buildingRecord;
  result = 0;
  if ( (unsigned __int8)firstStep >= *buildingRecord && (unsigned __int8)firstStep <= *buildingRecord + 1 )
  {
    buildingColumn = buildingRecord[1];
    if ( BYTE1(firstStep) >= buildingColumn && BYTE1(firstStep) <= buildingColumn + 1 )
      return 1;
  }
  return result;
}
