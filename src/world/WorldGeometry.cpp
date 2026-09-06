/* World geometry behavior; recovered storage and ABI adapters remain anchored. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "world_internal.h"
#include "world_state.h"
#include "../world/WorldGeometry.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

signed int  clash95::WorldGeometry::Facing_DirectionFromDelta8(int deltaRow, int deltaColumn) const
{
  if ( deltaRow <= 0 )
  {
    if ( deltaRow < 0 )
    {
      if ( deltaColumn < 0 )
      {
        return DIRECTION8_NORTHWEST;
      }
      else if ( deltaColumn )
      {
        return DIRECTION8_NORTHEAST;
      }
      else
      {
        return DIRECTION8_NORTH;
      }
    }
    else if ( deltaColumn < 0 )
    {
      return DIRECTION8_WEST;
    }
    else
    {
      return DIRECTION8_EAST;
    }
  }
  else if ( deltaColumn < 0 )
  {
    return DIRECTION8_SOUTHWEST;
  }
  else if ( deltaColumn )
  {
    return DIRECTION8_SOUTHEAST;
  }
  else
  {
    return DIRECTION8_SOUTH;
  }
}

int  clash95::WorldGeometry::Math_SinDegreesQ16(signed int degrees) const
{
  int angle; // edx
  int absAngle; // edx

  // x86 NEG preserves INT_MIN; its scaled DWORD address wraps to table[0].
  if ( degrees == INT32_MIN )
    return -state_[0];

  angle = degrees;
  if ( degrees < 0 )
  {
    absAngle = -degrees;
    if ( -degrees >= 360 )
      absAngle %= 360;
    return -state_[absAngle];
  }
  else
  {
    if ( degrees >= 360 )
      angle = degrees % 360;
    return state_[angle];
  }
}

signed int  clash95::WorldGeometry::Math_CeilSqrt(signed int value) const
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
