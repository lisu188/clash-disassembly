extern int gameData;
clash95::WorldMap clash95::WorldMap::borrow() noexcept
{
  return WorldMap(::gameData);
}
