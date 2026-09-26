__attribute__((used, retain))
BOOL  Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex)
{
  return clash95::WorldMap::borrow().Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex);
}
