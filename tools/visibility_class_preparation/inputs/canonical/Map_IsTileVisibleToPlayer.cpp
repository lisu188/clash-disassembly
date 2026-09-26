BOOL  clash95::WorldMap::Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex) const
{
  return tileX >= 0
      && tileY >= 0
      && tileX < *(_DWORD *)(uintptr_t)(this->state_field_0_ + MAP_WIDTH_TILES_OFFSET)
      && tileY < *(_DWORD *)(uintptr_t)(this->state_field_0_ + MAP_HEIGHT_TILES_OFFSET)
      && ((1 << (tileY & 7)) & *(unsigned __int8 *)(uintptr_t)((this->state_field_0_ + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_DATA_STRIDE * (playerIndex))
                                               + PLAYER_REVEALED_TILE_ROW_BYTES * tileX
                                               + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3)
                                               + PLAYER_REVEALED_TILES_OFFSET)) != 0;
}
