#include "units/UnitSlot.hpp"
#include "units/units_internal.h"
#include "recovered_structs.h"
#include <sys/mman.h>
#include <type_traits>
#include <limits.h>

static_assert(sizeof(clash95::UnitSlot) == sizeof(intptr_t));
static_assert(std::is_trivially_destructible_v<clash95::UnitSlot>);
static_assert(!std::is_polymorphic_v<clash95::UnitSlot>);
static_assert(alignof(UnitSlotRecord) == 1);
static_assert(std::is_same_v<decltype(&UnitSlot_CycleOrderState), int (*)(int)>);
static_assert(std::is_same_v<decltype(&UnitSlot_ShouldGainFatigueFromLowActionPoints), BOOL (*)(int)>);
static_assert(std::is_same_v<decltype(&UnitSlot_CanRecoverFatigue), BOOL (*)(int)>);
static_assert(std::is_same_v<decltype(&UnitSlot_HasSevereFatigue), BOOL (*)(int)>);

extern BOOL Reference_UnitSlot_ShouldGainFatigueFromLowActionPoints(int);
extern BOOL Reference_UnitSlot_CanRecoverFatigue(int);
extern BOOL Reference_UnitSlot_HasSevereFatigue(int);
extern int Reference_UnitSlot_CycleOrderState(int);

using Callback = int (*)(int);
static Callback const references[] = {
  Reference_UnitSlot_ShouldGainFatigueFromLowActionPoints,
  Reference_UnitSlot_CanRecoverFatigue,
  Reference_UnitSlot_HasSevereFatigue,
  Reference_UnitSlot_CycleOrderState
};
// These are ordinary original-signature function pointers, not member pointers.
static Callback const adapters[] = {
  UnitSlot_ShouldGainFatigueFromLowActionPoints,
  UnitSlot_CanRecoverFatigue,
  UnitSlot_HasSevereFatigue,
  UnitSlot_CycleOrderState
};

static int method(const clash95::UnitSlot &slot, int operation) {
  switch (operation) {
    case 0: return slot.UnitSlot_ShouldGainFatigueFromLowActionPoints();
    case 1: return slot.UnitSlot_CanRecoverFatigue();
    case 2: return slot.UnitSlot_HasSevereFatigue();
    default: return slot.UnitSlot_CycleOrderState();
  }
}

int main() {
  constexpr size_t arena_bytes = 256;
  void *allocation = mmap(nullptr, 4096, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
  if (allocation == MAP_FAILED || (uintptr_t)allocation + 4096 > INT32_MAX) return 99;
  auto *arena = static_cast<unsigned char *>(allocation);
  unsigned char initial[arena_bytes], expected[arena_bytes];
  unsigned long scenarios = 0;
  for (int alignment = 0; alignment != 16; ++alignment) {
    unsigned char *slot = arena + 96 + alignment;
    const int address = (int)(intptr_t)slot;
    memset(arena, 0xa5, arena_bytes);
    memcpy(initial, arena, arena_bytes);
    // One view remains bound while every relevant byte changes between calls.
    const clash95::UnitSlot view((intptr_t)slot);
    if (memcmp(initial, arena, arena_bytes)) return 90;
    for (int value = 0; value != 256; ++value) {
      for (int flags = 0; flags != 256; ++flags) {
        for (size_t i = 0; i != arena_bytes; ++i)
          initial[i] = (unsigned char)(i * 73u + value * 19u + flags * 29u + alignment);
        const size_t offset = 96 + alignment;
        // Exhaust every AP/flag pair, every signed fatigue byte and stance byte.
        // The ignored type word also spans all values, including -1 and extremes.
        initial[offset] = (unsigned char)value;
        initial[offset + 1] = (unsigned char)flags;
        initial[offset + 8] = (unsigned char)value;
        initial[offset + 10] = (unsigned char)value;
        initial[offset + 12] = (unsigned char)flags;
        initial[offset + 13] = (unsigned char)flags;
        for (int operation = 0; operation != 4; ++operation) {
          memcpy(arena, initial, arena_bytes);
          Callback volatile reference = references[operation];
          const int expected_result = reference(address);
          memcpy(expected, arena, arena_bytes);
          if (operation < 3 && memcmp(initial, expected, arena_bytes)) return 91;
          if (operation == 3 && expected_result != address) return 92;
          for (int route = 0; route != 2; ++route) {
            memcpy(arena, initial, arena_bytes);
            Callback volatile adapter = adapters[operation];
            const int actual_result = route ? method(view, operation) : adapter(address);
            if (actual_result != expected_result || memcmp(expected, arena, arena_bytes)) {
              fprintf(stderr, "alignment=%d value=%d flags=%d operation=%d route=%d actual=%d expected=%d bytes_differ=%d\n",
                      alignment, value, flags, operation, route, actual_result, expected_result,
                      memcmp(expected, arena, arena_bytes) != 0);
              return 1;
            }
          }
        }
        ++scenarios;
      }
    }
  }
  munmap(allocation, 4096);
  printf("scenarios=%lu operations=4 alignments=16 arena_bytes=256 callback_and_method=pass\n", scenarios);
  return 0;
}
