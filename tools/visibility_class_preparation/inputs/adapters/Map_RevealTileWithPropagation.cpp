__attribute__((used, retain))
signed int  Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex)
{
  return clash95::WorldMap::borrow().Map_RevealTileWithPropagation(tileX, tileY, playerIndex);
}
