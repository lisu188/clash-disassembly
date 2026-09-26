BOOL  Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex)
{
  return tileX >= 0
      && tileY >= 0
      && tileX < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
      && tileY < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && ((1 << (tileY & 7)) & *(unsigned __int8 *)(uintptr_t)(PLAYER_DATA(playerIndex)
                                               + PLAYER_REVEALED_TILE_ROW_BYTES * tileX
                                               + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3)
                                               + PLAYER_REVEALED_TILES_OFFSET)) != 0;
}
