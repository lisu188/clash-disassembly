#include "units/UnitSlot.hpp"
#include "units/units_internal.h"
#include "units/units_shared_state.h"
#include "recovered_structs.h"
#include <sys/mman.h>
#include <type_traits>
#include <limits.h>

static_assert(sizeof(clash95::UnitSlot) == sizeof(intptr_t));
static_assert(std::is_trivially_destructible_v<clash95::UnitSlot>);
static_assert(!std::is_polymorphic_v<clash95::UnitSlot>);
static_assert(alignof(UnitSlotRecord) == 1);
static_assert(offsetof(UnitTypeRuntimeCoreMetadataRecord, base_action_points) == 24);
static_assert(sizeof(UnitTypeRuntimeCoreMetadataRecord) == 88);
static_assert(std::is_same_v<decltype(&UnitSlot_CalcActionPointsFromFatigue), int (*)(__int16 *)>);
static_assert(std::is_same_v<decltype(&UnitSlot_GetBaseActionPoints), int (*)(__int16 *)>);

extern int Reference_UnitSlot_CalcActionPointsFromFatigue(__int16 *);
extern int Reference_UnitSlot_GetBaseActionPoints(__int16 *);
extern "C" const UnitTypeRuntimeCoreMetadataRecord *__real_UnitSlot_BorrowTypeMetadata(void);
extern "C" const UnitTypeRuntimeCoreMetadataRecord *__wrap_UnitSlot_BorrowTypeMetadata(void);

const UnitTypeRuntimeCoreMetadataRecord *fixtureMetadata;
static unsigned long binding_calls;
static bool use_real_binding;
static UnitTypeRuntimeCoreMetadataRecord mutable_metadata[UNIT_TYPE_METADATA_CAPACITY];

extern "C" const UnitTypeRuntimeCoreMetadataRecord *__wrap_UnitSlot_BorrowTypeMetadata(void) {
  ++binding_calls;
  return use_real_binding ? __real_UnitSlot_BorrowTypeMetadata() : fixtureMetadata;
}

using Callback = int (*)(__int16 *);
static Callback const references[] = {
  Reference_UnitSlot_CalcActionPointsFromFatigue, Reference_UnitSlot_GetBaseActionPoints
};
static Callback const adapters[] = {
  UnitSlot_CalcActionPointsFromFatigue, UnitSlot_GetBaseActionPoints
};

static int method(const clash95::UnitSlot &slot, int operation) {
  return operation ? slot.UnitSlot_GetBaseActionPoints() : slot.UnitSlot_CalcActionPointsFromFatigue();
}

static unsigned long cases;
static unsigned long getter_cases;
static unsigned long invalid_type_cases;

static int check(unsigned char *arena, int alignment, int type, int fatigue, int base_ap,
                 int address_mode, bool vary_metadata) {
  constexpr size_t arena_bytes = 256;
  unsigned char initial[arena_bytes];
  UnitTypeRuntimeCoreMetadataRecord table_snapshot[UNIT_TYPE_METADATA_CAPACITY];
  const size_t offset = 96 + alignment;
  for (size_t i = 0; i != arena_bytes; ++i)
    initial[i] = (unsigned char)(i * 73u + (unsigned)type * 19u + fatigue * 29u + base_ap);
  const int16_t type_word = (int16_t)type;
  memcpy(initial + offset, &type_word, 2);
  initial[offset + 10] = (unsigned char)fatigue;
  if (vary_metadata && type >= 0 && type < UNIT_TYPE_METADATA_CAPACITY)
    mutable_metadata[type].base_action_points = (unsigned char)base_ap;
  memcpy(table_snapshot, fixtureMetadata, sizeof(table_snapshot));
  memcpy(arena, initial, arena_bytes);
  const auto *slot = reinterpret_cast<__int16 *>(arena + offset);
  const clash95::UnitSlot view((intptr_t)slot);
  if (memcmp(initial, arena, arena_bytes)) return 91;
  for (int operation = 0; operation != 2; ++operation) {
    // The unguarded getter has no invented behavior outside the actual 40 rows.
    if (operation && (type < 0 || type >= UNIT_TYPE_METADATA_CAPACITY)) continue;
    Callback volatile reference = references[operation];
    const int expected = reference(const_cast<__int16 *>(slot));
    if (memcmp(initial, arena, arena_bytes)) return 92;
    for (int route = 0; route != 2; ++route) {
      binding_calls = 0;
      Callback volatile adapter = adapters[operation];
      const int actual = route ? method(view, operation) : adapter(const_cast<__int16 *>(slot));
      const unsigned long expected_calls = operation || (type >= 0 && type < UNIT_TYPE_COUNT) ? 1 : 0;
      if (actual != expected || binding_calls != expected_calls
          || memcmp(initial, arena, arena_bytes)
          || memcmp(table_snapshot, fixtureMetadata, sizeof(table_snapshot))) {
        fprintf(stderr, "mode=%d align=%d type=%d fatigue=%d ap=%d op=%d route=%d actual=%d expected=%d calls=%lu expected_calls=%lu\n",
                address_mode, alignment, type, fatigue, base_ap, operation, route,
                actual, expected, binding_calls, expected_calls);
        return 1;
      }
    }
    if (operation) ++getter_cases;
  }
  if (type < 0 || type >= UNIT_TYPE_COUNT) ++invalid_type_cases;
  ++cases;
  return 0;
}

int main() {
  void *low = mmap(nullptr, 4096, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
  if (low == MAP_FAILED || (uintptr_t)low + 4096 > INT32_MAX) return 99;
  void *native = mmap(nullptr, 4096, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (native == MAP_FAILED || (uintptr_t)native <= UINT32_MAX) return 98;
  // The actual storage accessor must return the exact original array itself.
  if (__real_UnitSlot_BorrowTypeMetadata() != g_UnitTypeRuntimeCoreMetadata) return 97;
  memcpy(mutable_metadata, g_UnitTypeRuntimeCoreMetadata, sizeof(mutable_metadata));
  fixtureMetadata = mutable_metadata;
  const int edge_ap[] = {0, 1, 2, 127, 128, 192, 254, 255};
  for (int mode = 0; mode != 2; ++mode) {
    auto *arena = static_cast<unsigned char *>(mode ? native : low);
    for (int alignment = 0; alignment != 16; ++alignment) {
      // Every signed type word exercises the guarded query, including invalid
      // sentinels. GetBase is evaluated only on its valid storage domain.
      for (unsigned word = 0; word != 65536; ++word) {
        const int type = (int16_t)word;
        if (check(arena, alignment, type, word & 255u, 0, mode, false)) return 1;
      }
      // Exhaust every AP/fatigue byte pair while rotating all 40 table rows.
      for (int fatigue = 0; fatigue != 256; ++fatigue)
        for (int ap = 0; ap != 256; ++ap)
          if (check(arena, alignment, (fatigue + ap + alignment) % 40,
                    fatigue, ap, mode, true)) return 1;
      // Independently hit every physical row at all fatigue bytes and AP edges.
      for (int type = 0; type != UNIT_TYPE_METADATA_CAPACITY; ++type)
        for (int fatigue = 0; fatigue != 256; ++fatigue)
          for (int ap : edge_ap)
            if (check(arena, alignment, type, fatigue, ap, mode, true)) return 1;
      // Finally exercise the actual accessor and immutable production table.
      use_real_binding = true;
      fixtureMetadata = g_UnitTypeRuntimeCoreMetadata;
      for (int type = 0; type != UNIT_TYPE_METADATA_CAPACITY; ++type)
        for (int fatigue = 0; fatigue != 256; ++fatigue)
          if (check(arena, alignment, type, fatigue, 0, mode, false)) return 1;
      use_real_binding = false;
      fixtureMetadata = mutable_metadata;
    }
  }
  munmap(low, 4096);
  munmap(native, 4096);
  printf("cases=%lu getter_cases=%lu invalid_type_cases=%lu alignments=16 pointer_widths=2 helper_and_callbacks=pass\n",
         cases, getter_cases, invalid_type_cases);
  return 0;
}
