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
