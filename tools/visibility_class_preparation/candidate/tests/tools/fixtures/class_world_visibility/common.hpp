#pragma once
#include "world/world_api.h"
#include "world/WorldMap.hpp"
extern int gameData;
extern "C" {
signed int Reference_Map_RevealTileWithPropagation(int,int,int);
BOOL Reference_Map_IsTileVisibleToPlayer(int,int,int);
signed int Reference_Map_ClassifyFogOfWarOverlayForPlayer(int,int,int);
}
