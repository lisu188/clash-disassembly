// Relocated recovered methods; ABI adapters and bindings remain at their original anchor.
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "core_internal.h"
#include "core_state.h"
#include "core_shared_state.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../core/GameRandom.hpp"
/* CLASH95_GENERATED_INCLUDES_END */

void  clash95::GameRandom::initRandomSeed(char a1, DWORD a2) const
{
  this->state_ = ::time_();
  ::Debug_Log(0, a1, a2, (int)(intptr_t)this->format_);
}

unsigned int  clash95::GameRandom::Rng_RandRange(int minValue, int maxValue) const
{
  unsigned int range;
  unsigned int seed;

  this->state_ ^= ::Time_Now(0, 0) + 0x34523471u;
  seed = (unsigned int)this->state_ + 0x83356532u * (unsigned int)::Time_Now(0, 0);
  this->state_ = (int)seed;
  range = (unsigned int)((__int64)maxValue + 1 - minValue);
  if ( !range )
    return (unsigned int)minValue;
  return seed % range + (unsigned int)minValue;
}
