signed int  Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex)
{
  if ( Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
    return -1;

  // 0040F0E3..0040F1A8: each visibility result replaces one bit of CL.
  unsigned int neighborMask = 0;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) & 1u) << 7;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) & 1u) << 6;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) & 1u) << 5;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) & 1u) << 4;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) & 1u) << 3;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) & 1u) << 2;
  neighborMask |= (Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) & 1u) << 1;
  neighborMask |= Map_IsTileVisibleToPlayer(tileX + 1, tileY + 1, playerIndex) & 1u;
  if ( !neighborMask )
    return 0;

  TextSprite_SetStyleFlag(1);
  if ( !(neighborMask & 0x5A) && (neighborMask & 1) != 0 )
    return 12;
  if ( !(neighborMask & 0x5A) && (neighborMask & 0x80) != 0 )
    return 9;
  if ( !(neighborMask & 0x5A) && (neighborMask & 4) != 0 )
    return 11;
  if ( !(neighborMask & 0x5A) && (neighborMask & 0x20) != 0 )
    return 10;
  if ( !(neighborMask & 0x58) && (neighborMask & 2) != 0 )
    return 7;
  if ( !(neighborMask & 0x4A) && (neighborMask & 0x10) != 0 )
    return 4;
  if ( !(neighborMask & 0x52) && (neighborMask & 8) != 0 )
    return 5;
  if ( !(neighborMask & 0x1A) && (neighborMask & 0x40) != 0 )
    return 2;
  if ( !(neighborMask & 0xA) && (neighborMask & 0x50) == 0x50 )
    return 1;
  if ( !(neighborMask & 0x12) && (neighborMask & 0x48) == 0x48 )
    return 3;
  if ( !(neighborMask & 0x48) && (neighborMask & 0x12) == 0x12 )
    return 6;
  if ( !(neighborMask & 0x50) && (neighborMask & 0xA) == 0xA )
    return 8;
  if ( (neighborMask & 0x18) == 0x18 || (neighborMask & 0x42) == 0x42 )
    return -1;
  // Retain the original branch order, including the shadowed 0xFF case.
  if ( neighborMask == 255 )
    return 13;
  return 14;
}
