#ifndef CLASH95_UNIT_STACK_RECORD_H
#define CLASH95_UNIT_STACK_RECORD_H

#include <stddef.h>
#include <stdint.h>

#include "../recovered_types.h"

#pragma pack(push, 1)

typedef struct UnitStackSlotRecord
{
  uint8_t raw[UNIT_STACK_SLOT_STRIDE];
} UnitStackSlotRecord;

typedef struct UnitStackRecord
{
  int16_t tile_row;
  int16_t tile_column;
  uint8_t owner_index;
  uint8_t facing;
  UnitStackSlotRecord slots[UNIT_STACK_SLOT_COUNT];
  uint8_t queued_path[UNIT_STACK_PATH_BYTES];
  uint8_t unknown_tail[UNIT_STACK_STRIDE - UNIT_STACK_PATH_OFFSET - UNIT_STACK_PATH_BYTES];
} UnitStackRecord;

#pragma pack(pop)

_Static_assert(sizeof(UnitStackSlotRecord) == UNIT_STACK_SLOT_STRIDE, "UnitStackSlotRecord layout drift");
_Static_assert(offsetof(UnitStackRecord, tile_row) == 0, "UnitStackRecord.tile_row offset drift");
_Static_assert(offsetof(UnitStackRecord, tile_column) == 2, "UnitStackRecord.tile_column offset drift");
_Static_assert(offsetof(UnitStackRecord, owner_index) == 4, "UnitStackRecord.owner_index offset drift");
_Static_assert(offsetof(UnitStackRecord, facing) == 5, "UnitStackRecord.facing offset drift");
_Static_assert(offsetof(UnitStackRecord, slots) == UNIT_STACK_SLOT_BASE_OFFSET, "UnitStackRecord.slots offset drift");
_Static_assert(offsetof(UnitStackRecord, queued_path) == UNIT_STACK_PATH_OFFSET, "UnitStackRecord.queued_path offset drift");
_Static_assert(sizeof(UnitStackRecord) == UNIT_STACK_STRIDE, "UnitStackRecord size drift");

static inline UnitStackRecord *UnitStack_RecordAt(int stack_index)
{
  return (UnitStackRecord *)(uintptr_t)UNIT_STACK(stack_index);
}

static inline const UnitStackRecord *UnitStack_RecordAtConst(int stack_index)
{
  return (const UnitStackRecord *)(uintptr_t)UNIT_STACK(stack_index);
}

static inline UnitStackSlotRecord *UnitStack_SlotAt(UnitStackRecord *stack, int slot_index)
{
  return &stack->slots[slot_index];
}

static inline const UnitStackSlotRecord *UnitStack_SlotAtConst(const UnitStackRecord *stack, int slot_index)
{
  return &stack->slots[slot_index];
}

#endif
