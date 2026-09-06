/* Differential harness: production bodies and frozen reference bodies are
 * prepended by test_class_unit_pilot.py. Only fixture bytes are manufactured. */
static unsigned long stack_cases;
static unsigned long path_cases;

static void put16(unsigned char *where, int value) {
  const int16_t word = (int16_t)value;
  memcpy(where, &word, sizeof(word));
}

static void put32(unsigned char *where, uint32_t value) {
  memcpy(where, &value, sizeof(value));
}

static unsigned char *slot(unsigned char *stack, int index) {
  return stack + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * index;
}

static void init_stack(unsigned char *stack) {
  memset(stack - 16, 0xa5, UNIT_STACK_STRIDE + 32);
  for (int index = 0; index < UNIT_STACK_SLOT_COUNT; ++index) {
    put16(slot(stack, index), 0);
    slot(stack, index)[8] = 255;
    slot(stack, index)[13] = 0;
  }
}

static int observe(const char *operation, unsigned char *stack,
                   const unsigned char *snapshot, int actual, int expected,
                   const char *scenario, int alignment) {
  if (actual != expected || memcmp(snapshot, stack - 16, UNIT_STACK_STRIDE + 32)) {
    fprintf(stderr, "%s/%s alignment=%d result=%d expected=%d mutated=%d\n",
            scenario, operation, alignment, actual, expected,
            memcmp(snapshot, stack - 16, UNIT_STACK_STRIDE + 32) != 0);
    return 1;
  }
  return 0;
}

static int check_stack(unsigned char *stack, const char *scenario, int alignment,
                       int minimum, int ready, int builder) {
  unsigned char snapshot[UNIT_STACK_STRIDE + 32];
  memcpy(snapshot, stack - 16, sizeof(snapshot));
  const intptr_t address = (intptr_t)stack;
  const clash95::UnitStack view(address);
  int failed = 0;
#define CHECK_STACK(label, expression, expected) \
  do { const int result = (expression); \
       failed |= observe(label, stack, snapshot, result, expected, scenario, alignment); } while (0)
  CHECK_STACK("reference minimum", Reference_UnitStack_GetMinCurrentActionPoints(address), minimum);
  CHECK_STACK("ABI minimum", UnitStack_GetMinCurrentActionPoints(address), minimum);
  CHECK_STACK("method minimum", view.UnitStack_GetMinCurrentActionPoints(), minimum);
  CHECK_STACK("reference ready", Reference_UnitStack_HasReadyUnits((int)address), ready);
  CHECK_STACK("ABI ready", UnitStack_HasReadyUnits((int)address), ready);
  CHECK_STACK("method ready", view.UnitStack_HasReadyUnits(), ready);
  CHECK_STACK("reference builder", Reference_UnitStack_HasBuilder(0), builder);
  CHECK_STACK("ABI builder", UnitStack_HasBuilder(0), builder);
  CHECK_STACK("method builder", view.UnitStack_HasBuilder(), builder);
#undef CHECK_STACK
  ++stack_cases;
  return failed;
}

static int check_path(unsigned char *stack, int alignment, int row, int column,
                      int expected, const char *scenario) {
  unsigned char snapshot[UNIT_STACK_STRIDE + 32];
  memcpy(snapshot, stack - 16, sizeof(snapshot));
  _DWORD *path = (_DWORD *)(stack + UNIT_STACK_PATH_OFFSET);
  const clash95::QueuedPath view(path, gameData);
  int failed = 0;
#define CHECK_PATH(label, expression) \
  do { const int result = (expression); \
       failed |= observe(label, stack, snapshot, result, expected, scenario, alignment); } while (0)
  CHECK_PATH("reference path", Reference_QueuedPath_StartsAtTile(path, row, column));
  CHECK_PATH("ABI path", QueuedPath_StartsAtTile(path, row, column));
  CHECK_PATH("method path", view.QueuedPath_StartsAtTile(row, column));
#undef CHECK_PATH
  ++path_cases;
  return failed;
}

int main() {
  const size_t allocation_size = UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE + 128;
  void *allocation = mmap(nullptr, allocation_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
  if (allocation == MAP_FAILED || (uintptr_t)allocation + allocation_size > INT32_MAX) {
    fprintf(stderr, "low32 mmap failed\n");
    return 99;
  }
  int failed = 0;
  const unsigned char action_points[] = {0, 1, 127, 128, 254, 255};
  const unsigned char flags[] = {0, 1, 2, 3, 128, 255};
  for (int alignment = 0; alignment < 16 && !failed; ++alignment) {
    gameData = (int)((uintptr_t)allocation + 32 + alignment);
    unsigned char *stack = (unsigned char *)(uintptr_t)gameData + UNIT_STACK_TABLE_OFFSET;

    init_stack(stack);
    failed |= check_stack(stack, "ten populated slots", alignment, 255, 0, 0);

    // Every physical slot independently supplies low/high AP, ready-bit
    // combinations, and the builder type. None may be skipped at the tail.
    for (int index = 0; index < UNIT_STACK_SLOT_COUNT && !failed; ++index) {
      for (unsigned char ap : action_points) {
        for (unsigned char state_flags : flags) {
          init_stack(stack);
          put16(slot(stack, index), UNIT_TYPE_BUILDER);
          slot(stack, index)[8] = ap;
          slot(stack, index)[13] = state_flags;
          failed |= check_stack(stack, "each populated slot", alignment, ap,
                                (state_flags & UNIT_SLOT_FLAG_READY) != 0, 1);
        }
      }
    }

    // Each possible sentinel closes the ready/builder scan. A ready builder
    // after a hole must be ignored. Minimum AP starts at slot zero's AP and
    // tests sentinels only from slot one, including the empty-slot-zero case.
    for (int hole = 0; hole < UNIT_STACK_SLOT_COUNT && !failed; ++hole) {
      init_stack(stack);
      slot(stack, 0)[8] = 37;
      put16(slot(stack, hole), -1);
      if (hole + 1 < UNIT_STACK_SLOT_COUNT) {
        put16(slot(stack, hole + 1), UNIT_TYPE_BUILDER);
        slot(stack, hole + 1)[8] = 0;
        slot(stack, hole + 1)[13] = 255;
      }
      failed |= check_stack(stack, "sentinel hides later live slot", alignment,
                            hole == 0 ? 0 : 37, 0, 0);
      if (hole > 0) {
        put16(slot(stack, hole - 1), UNIT_TYPE_BUILDER);
        slot(stack, hole - 1)[8] = 23;
        slot(stack, hole - 1)[13] = UNIT_SLOT_FLAG_READY;
        failed |= check_stack(stack, "live slot before sentinel", alignment, 23, 1, 1);
      }
    }

    for (unsigned char ap : action_points) {
      init_stack(stack);
      for (int index = 0; index < UNIT_STACK_SLOT_COUNT; ++index) {
        put16(slot(stack, index), -1);
        slot(stack, index)[8] = 0;
        slot(stack, index)[13] = 255;
      }
      slot(stack, 0)[8] = ap;
      failed |= check_stack(stack, "empty stack retains first-slot AP", alignment, ap, 0, 0);
    }

    const int counts[] = {0, 1, 100, -1, INT32_MIN, INT32_MAX};
    const uint32_t first_steps[] = {0, 0x00000102u, 0x000080ffu, 0x0000ffffu, 0xabcd1234u};
    const int coordinates[] = {-1, 0, 1, 2, 18, 52, 128, 255, 256};
    for (int count : counts) {
      for (uint32_t first : first_steps) {
        init_stack(stack);
        unsigned char *path = stack + UNIT_STACK_PATH_OFFSET;
        put32(path, (uint32_t)count);
        put32(path + 4, first);
        for (int index = 1; index < 100; ++index)
          put32(path + 4 + 4 * index, 0xffff0102u);
        for (int row : coordinates) {
          for (int column : coordinates) {
            const int expected = count != 0 && row == (int)(first & 255u)
                                 && column == (int)((first >> 8) & 255u);
            failed |= check_path(stack, alignment, row, column, expected,
                                 "count and byte-coordinate domain");
          }
        }
      }
    }
    init_stack(stack);
    unsigned char *path = stack + UNIT_STACK_PATH_OFFSET;
    put32(path, 100);
    put32(path + 4, 0x00000201u);
    put32(path + 4 + 99 * 4, 0x00000403u);
    failed |= check_path(stack, alignment, 1, 2, 1, "first waypoint matches");
    failed |= check_path(stack, alignment, 3, 4, 0, "tail waypoint is ignored");
    failed |= check_path(stack, alignment, 2, 1, 0, "row and column are distinct");
  }
  munmap(allocation, allocation_size);
  if (failed) return 1;
  printf("class unit pilot: PASS stack_cases=%lu path_cases=%lu alignments=16\n",
         stack_cases, path_cases);
  return 0;
}
