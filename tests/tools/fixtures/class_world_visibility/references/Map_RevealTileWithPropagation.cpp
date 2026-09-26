signed int  Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex)
{
  int revealByteAddr; // eax
  int diagRightTileX2; // edi

  if ( tileX < 0
    || tileY < 0
    || tileX >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
    || tileY >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
    || Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
  {
    return 0;
  }
  revealByteAddr = PLAYER_DATA(playerIndex) + PLAYER_REVEALED_TILE_ROW_BYTES * tileX + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3);
  *(_BYTE *)(uintptr_t)(revealByteAddr + PLAYER_REVEALED_TILES_OFFSET) |= 1 << (tileY & 7);
  MiniMap_DrawTileCell((void *)(uintptr_t)tileX, tileY);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(tileX - 1, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(tileX + 1, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, tileY + 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX - 1, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX + 1, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX - 1, tileY + 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY + 2, playerIndex) )
  {
    diagRightTileX2 = tileX + 1;
    if ( !Map_IsTileVisibleToPlayer(diagRightTileX2, tileY + 1, playerIndex) )
      Map_RevealTileWithPropagation(diagRightTileX2, tileY + 1, playerIndex);
  }
  return 1;
}
