signed int  Facing_DirectionFromDelta8(int deltaRow, int deltaColumn)
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
