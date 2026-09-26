// Relocated recovered methods; ABI adapters and storage remain at their original anchor.
/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "world_internal.h"
#include "world_state.h"
#include "../world/WorldMap.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

signed int  clash95::WorldMap::Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex) const
{
  int revealByteAddr; // eax
  int diagRightTileX2; // edi

  if ( tileX < 0
    || tileY < 0
    || tileX >= *(_DWORD *)(uintptr_t)(this->state_field_0_ + MAP_WIDTH_TILES_OFFSET)
    || tileY >= *(_DWORD *)(uintptr_t)(this->state_field_0_ + MAP_HEIGHT_TILES_OFFSET)
    || this->Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
  {
    return 0;
  }
  revealByteAddr = (this->state_field_0_ + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_DATA_STRIDE * (playerIndex)) + PLAYER_REVEALED_TILE_ROW_BYTES * tileX + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3);
  *(_BYTE *)(uintptr_t)(revealByteAddr + PLAYER_REVEALED_TILES_OFFSET) |= 1 << (tileY & 7);
  ::MiniMap_DrawTileCell((void *)(uintptr_t)tileX, tileY);
  if ( this->Map_IsTileVisibleToPlayer(tileX - 2, tileY, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX - 1, tileY, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX + 2, tileY, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX + 1, tileY, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX, tileY - 2, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX, tileY - 1, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX, tileY + 2, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX, tileY + 1, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX - 2, tileY - 2, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX - 1, tileY - 1, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX + 2, tileY - 2, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX + 1, tileY - 1, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX - 2, tileY + 2, playerIndex) && !this->Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) )
    this->Map_RevealTileWithPropagation(tileX - 1, tileY + 1, playerIndex);
  if ( this->Map_IsTileVisibleToPlayer(tileX + 2, tileY + 2, playerIndex) )
  {
    diagRightTileX2 = tileX + 1;
    if ( !this->Map_IsTileVisibleToPlayer(diagRightTileX2, tileY + 1, playerIndex) )
      this->Map_RevealTileWithPropagation(diagRightTileX2, tileY + 1, playerIndex);
  }
  return 1;
}

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

signed int  clash95::WorldMap::Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex) const
{
  if ( this->Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
    return -1;

  // 0040F0E3..0040F1A8: each visibility result replaces one bit of CL.
  unsigned int neighborMask = 0;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) & 1u) << 7;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) & 1u) << 6;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) & 1u) << 5;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) & 1u) << 4;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) & 1u) << 3;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) & 1u) << 2;
  neighborMask |= (this->Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) & 1u) << 1;
  neighborMask |= this->Map_IsTileVisibleToPlayer(tileX + 1, tileY + 1, playerIndex) & 1u;
  if ( !neighborMask )
    return 0;

  ::TextSprite_SetStyleFlag(1);
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
