__attribute__((used, retain))
signed int  Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex)
{
  return clash95::WorldMap::borrow().Map_ClassifyFogOfWarOverlayForPlayer(tileX, tileY, playerIndex);
}
