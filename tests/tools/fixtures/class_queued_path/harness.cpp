/* Actual frozen and production definitions are prepended by the Python test. */
struct GuardedImage {
  unsigned char *mapping;
  unsigned char *data;
  size_t page;

  bool create() {
    page = (size_t)sysconf(_SC_PAGESIZE);
    mapping = (unsigned char *)mmap(nullptr, page * 3, PROT_NONE,
        MAP_PRIVATE | MAP_ANONYMOUS | MAP_32BIT, -1, 0);
    if (mapping == MAP_FAILED || (uintptr_t)mapping + page * 3 > INT32_MAX)
      return false;
    data = mapping + page;
    return mprotect(data, page, PROT_READ | PROT_WRITE) == 0;
  }

  void release() { munmap(mapping, page * 3); }
};

static unsigned long cases;
static unsigned long rebindings;
static unsigned long changed_results;

static void put32(unsigned char *where, uint32_t value) {
  memcpy(where, &value, sizeof(value));
}

static int base_for(const GuardedImage &image, int alignment) {
  return (int)((uintptr_t)image.data + 32 + 3 * BUILDING_RECORD_SIZE + alignment)
      - BUILDING_TABLE_OFFSET;
}

static unsigned char *building_for(int base, int index) {
  return (unsigned char *)(uintptr_t)(base + BUILDING_TABLE_OFFSET
      + BUILDING_RECORD_SIZE * index);
}

static bool unchanged(const GuardedImage (&images)[3], const unsigned char *snapshots,
                      int expected_base, const char *role, int actual, int expected) {
  for (int index = 0; index < 3; ++index) {
    if (memcmp(images[index].data, snapshots + index * images[index].page,
               images[index].page) != 0) {
      fprintf(stderr, "%s mutated guarded image %d in case %lu\n", role, index, cases);
      return false;
    }
  }
  if (gameData != expected_base || actual != expected) {
    fprintf(stderr, "%s case=%lu actual=%d expected=%d base=%d expected_base=%d\n",
            role, cases, actual, expected, gameData, expected_base);
    return false;
  }
  return true;
}

static bool check_case(GuardedImage (&images)[3], unsigned char *snapshots,
                       int alignment, int index, int row, int column, int footprint,
                       uint32_t count, int waypoint_row, int waypoint_column,
                       uint32_t upper_bits) {
  for (int which = 0; which < 3; ++which)
    memset(images[which].data, 0xa5 + which, images[which].page);
  const int first_base = base_for(images[0], 15 - alignment);
  const int second_base = base_for(images[1], alignment);
  unsigned char *first = building_for(first_base, index);
  unsigned char *second = building_for(second_base, index);
  first[0] = (unsigned char)row;
  first[1] = (unsigned char)column;
  first[4] = (unsigned char)footprint;
  second[0] = (unsigned char)(row + 7);
  second[1] = (unsigned char)(column + 11);
  second[4] = footprint ? 0 : 255;
  unsigned char *path_bytes = images[2].data + 32 + alignment;
  put32(path_bytes, count);
  put32(path_bytes + 4, upper_bits | (uint32_t)(uint8_t)waypoint_row
        | ((uint32_t)(uint8_t)waypoint_column << 8));
  for (int which = 0; which < 3; ++which)
    memcpy(snapshots + which * images[which].page, images[which].data, images[which].page);

  _DWORD *path = (_DWORD *)path_bytes;
  gameData = first_base;
  const clash95::QueuedPath held(path, gameData);
  const int expected_first = Reference_QueuedPath_StartsInBuildingFootprint(path, index);
  if (!unchanged(images, snapshots, first_base, "reference A", expected_first, expected_first)
      || !unchanged(images, snapshots, first_base, "ABI A",
                    QueuedPath_StartsInBuildingFootprint(path, index), expected_first)
      || !unchanged(images, snapshots, first_base, "method A",
                    held.QueuedPath_StartsInBuildingFootprint(index), expected_first))
    return false;

  // The same object must observe a reassigned live world base without rebinding.
  gameData = second_base;
  const int expected_second = Reference_QueuedPath_StartsInBuildingFootprint(path, index);
  if (!unchanged(images, snapshots, second_base, "reference B", expected_second, expected_second)
      || !unchanged(images, snapshots, second_base, "ABI B",
                    QueuedPath_StartsInBuildingFootprint(path, index), expected_second)
      || !unchanged(images, snapshots, second_base, "held method B",
                    held.QueuedPath_StartsInBuildingFootprint(index), expected_second))
    return false;
  changed_results += expected_first != expected_second;
  ++rebindings;
  ++cases;

  if (!count) {
    // Computing a null building address is harmless before the count check;
    // an eager field lookup would fault on the otherwise valid empty path.
    gameData = -BUILDING_TABLE_OFFSET - BUILDING_RECORD_SIZE * index;
    const int empty_base = gameData;
    if (!unchanged(images, snapshots, empty_base, "empty reference",
                   Reference_QueuedPath_StartsInBuildingFootprint(path, index), 0)
        || !unchanged(images, snapshots, empty_base, "empty ABI",
                      QueuedPath_StartsInBuildingFootprint(path, index), 0)
        || !unchanged(images, snapshots, empty_base, "empty held method",
                      held.QueuedPath_StartsInBuildingFootprint(index), 0))
      return false;
  }
  return true;
}

int main() {
  GuardedImage images[3];
  for (GuardedImage &image : images) {
    if (!image.create()) {
      fprintf(stderr, "low32 guarded allocation failed\n");
      return 99;
    }
  }
  unsigned char *snapshots = (unsigned char *)malloc(3 * images[0].page);
  if (!snapshots)
    return 99;
  const int indices[] = {-3, -1, 0, 1, 3};
  const int origins[][2] = {{0, 0}, {1, 2}, {127, 128}, {128, 127}, {254, 254}, {255, 255}};
  const int footprints[] = {0, 1, 128, 255};
  const uint32_t counts[] = {0, 1, 2, 100, 0x80000000u, 0xffffffffu};
  const uint32_t high_bits[] = {0, 0x80000000u, 0xffff0000u};
  for (int alignment = 0; alignment < 16; ++alignment) {
    for (int index : indices) {
      for (const auto &origin : origins) {
        const int row = origin[0], column = origin[1];
        const int points[][2] = {
          {row, column}, {row + 1, column}, {row, column + 1}, {row + 1, column + 1},
          {row + 2, column}, {row, column + 2}, {row - 1, column}, {row, column - 1},
          {-1, -1}, {-128, 127}, {128, -127}, {256, 257}, {255, 0}, {0, 255}
        };
        for (int footprint : footprints) {
          for (const auto &point : points) {
            if (!check_case(images, snapshots, alignment, index, row, column, footprint,
                            counts[cases % 6], point[0], point[1], high_bits[(cases / 6) % 3]))
              return 1;
          }
        }
      }
    }
  }
  if (cases != 26880 || rebindings != cases || changed_results < 1000) {
    fprintf(stderr, "insufficient scenarios cases=%lu rebindings=%lu changed=%lu\n",
            cases, rebindings, changed_results);
    return 1;
  }
  printf("cases=%lu rebindings=%lu changed_results=%lu alignments=16 guarded_images=3\n",
         cases, rebindings, changed_results);
  free(snapshots);
  for (GuardedImage &image : images)
    image.release();
  return 0;
}
