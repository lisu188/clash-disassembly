#include "render/dlx_sprite_view.h"
#include <array>
#include <csetjmp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <vector>

using DWORD = std::uint32_t;
using _DWORD = std::uint32_t;
static constexpr int DLX_DIRECTORY_BYTES = 4096;
static constexpr std::uint64_t unchanged = UINT64_C(0x100000000);
static constexpr std::uint32_t initialSize = 0xA1A2A3A4u;
static constexpr std::uint32_t initialOwner = 0x8BADF00Du;
static constexpr int queryHandle = 0x317;
static constexpr int entryStart = 100;

struct Case {
  const char *name = "next-offset";
  int index = 2;
  std::uint32_t recordSize = 26;
  bool queryFails = false;
  bool useEof = false;
  bool mutateStartAtEof = false;
  std::uint64_t seekSize = unchanged;
  std::uint64_t headerSize = unchanged;
  std::uint64_t allocatorSize = unchanged;
  bool allocationFails = false;
  bool terminalQuit = false;
  bool mutateInDebugLog = false;
  bool mutateAtPayloadRead = false;
  bool wideAllocatorReturn = false;
};

enum Kind { Resolve, DirectoryRead, StreamSize, Seek, HeaderRead, Allocate,
            Log, Quit, PayloadRead, Release };
struct Event {
  Kind kind;
  std::uint32_t a, b, c;
  std::array<unsigned char, 96> arena;
  bool operator==(const Event &) const = default;
};
struct Result {
  bool returned;
  DWORD value;
  std::vector<Event> events;
  std::array<unsigned char, 96> arena;
  std::array<unsigned char, 128> payload;
  std::array<std::uint32_t, 1030> directory;
  bool operator==(const Result &) const = default;
};

static Case current;
static int alignment;
alignas(16) static std::array<unsigned char, 96> arena;
alignas(16) static std::array<unsigned char, 128> payload;
alignas(4) static std::array<std::uint32_t, 1030> directory;
static std::array<std::uint32_t, 1024> directoryImage;
// Original globals alias consecutive DWORDs. Padding makes negative signed
// index -1 a valid access within the same actual backing array in this fixture.
static std::uint32_t *g_DlxDirectoryEntryStartOffsets = directory.data() + 2;
static std::uint32_t *g_DlxDirectoryEntryEndOffsets = directory.data() + 3;
static int g_FileSystemMountTable;
static const char aGfx_3[] = "gfx\\";
static const char aNotEnoughMem_7[] = "allocation log";
static const char aNotEnoughMem_8[] = "allocation quit";
static std::vector<Event> events;
static std::jmp_buf quitTarget;
static DWORD returnedValue;
static bool didReturn;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "DLX cached entry %s alignment=%d: %s\n",
               current.name, alignment, message);
  std::exit(1);
}
static void require(bool condition, const char *message) {
  if (!condition) fail(message);
}
static unsigned char *spriteBytes() { return arena.data() + 32 + alignment; }
static std::uint32_t low32(const void *pointer) {
  const auto value = reinterpret_cast<std::uintptr_t>(pointer);
  require(value <= INT32_MAX, "fixture storage must be signed-low32 addressable");
  return static_cast<std::uint32_t>(value);
}
static std::uint32_t get32(const unsigned char *address) {
  std::uint32_t value;
  std::memcpy(&value, address, sizeof value);
  return value;
}
static void put32(unsigned char *address, std::uint32_t value) {
  std::memcpy(address, &value, sizeof value);
}
static void record(Kind kind, std::uint32_t a = 0, std::uint32_t b = 0,
                   std::uint32_t c = 0) {
  events.push_back({kind, a, b, c, arena});
}
static int FileSystem_ResolveReadPath(const char *path, int mode) {
  require(std::strcmp(path, "gfx\\synthetic.s32") == 0, "path prefix/name changed");
  require(mode == 1, "query mode changed");
  record(Resolve, mode);
  return current.queryFails ? 0 : queryHandle;
}
static int IO_QueryVTableStreamSize(int handle) {
  require(handle == queryHandle, "size-query handle changed");
  record(StreamSize, handle);
  if (current.mutateStartAtEof)
    g_DlxDirectoryEntryStartOffsets[current.index] = entryStart + 7;
  return entryStart + static_cast<int>(current.recordSize);
}
static int Compat_QuerySeek(int handle, int offset) {
  require(handle == queryHandle, "seek handle changed");
  record(Seek, handle, static_cast<std::uint32_t>(offset));
  if (current.seekSize != unchanged)
    put32(spriteBytes() + 14, static_cast<std::uint32_t>(current.seekSize));
  return 0;
}
static int Compat_QueryRead(int handle, void *destination, int count) {
  require(handle == queryHandle, "read handle changed");
  if (destination == g_DlxDirectoryEntryStartOffsets) {
    record(DirectoryRead, handle, low32(destination), static_cast<std::uint32_t>(count));
    require(count == 4096, "directory read length changed");
    std::memcpy(destination, directoryImage.data(), 4096);
  } else if (destination == spriteBytes()) {
    record(HeaderRead, handle, low32(destination), static_cast<std::uint32_t>(count));
    require(count == 10, "serialized header read must be exactly ten bytes");
    for (int i = 0; i != count; ++i) spriteBytes()[i] = static_cast<unsigned char>(0x10 + i);
    if (current.headerSize != unchanged)
      put32(spriteBytes() + 14, static_cast<std::uint32_t>(current.headerSize));
  } else {
    record(PayloadRead, handle, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(destination)),
           static_cast<std::uint32_t>(count));
    // Huge/negative lengths and a returning failed-allocation hook are trace
    // probes only; this fixture never dereferences their synthetic destinations.
    if (destination == payload.data() && count >= 0 && count <= 128)
      for (int i = 0; i != count; ++i) payload[i] = static_cast<unsigned char>(i ^ 0x6D);
    if (current.mutateAtPayloadRead) {
      put32(spriteBytes() + 10, 0x12345678u);
      put32(spriteBytes() + 14, 0x55667788u);
    }
  }
  return count;
}
static std::uint64_t nmalloc_(std::uint32_t count, std::uint32_t registerNoise) {
  record(Allocate, count, registerNoise);
  require(registerNoise == 4, "allocator compatibility argument changed");
  if (current.allocatorSize != unchanged) {
    put32(spriteBytes() + 14, static_cast<std::uint32_t>(current.allocatorSize));
    put32(spriteBytes() + 10, 0xCAFEBABEu);
  }
  const std::uint64_t handle = current.allocationFails ? 0 : low32(payload.data());
  return handle | (current.wideAllocatorReturn ? UINT64_C(0xFEDCBA9800000000) : 0);
}
static int Debug_Log(int a, int b, int count, int message) {
  require(message == static_cast<int>(low32(aNotEnoughMem_7)), "log message changed");
  record(Log, a, b, static_cast<std::uint32_t>(count));
  if (current.mutateInDebugLog) {
    put32(spriteBytes() + 10, low32(payload.data() + 64));
    put32(spriteBytes() + 14, 777);
  }
  return 0;
}
static int App_RequestQuit(int message) {
  require(message == static_cast<int>(low32(aNotEnoughMem_8)), "quit message changed");
  record(Quit);
  if (current.terminalQuit) std::longjmp(quitTarget, 1);
  return 0;
}
static int Compat_FileSystemQueryRelease(int mount, int *handle) {
  require(mount == static_cast<int>(low32(&g_FileSystemMountTable)), "release mount changed");
  record(Release, *handle);
  *handle = 0;
  return 0;
}

#define DLXSprite_LoadCachedEntry frozen_LoadCachedEntry
@FROZEN_BODY@
#undef DLXSprite_LoadCachedEntry
@ACTUAL_BODY@

static void reset() {
  arena.fill(0xD7);
  payload.fill(0xC5);
  directory.fill(0xB0B0B0B0u);
  directoryImage.fill(0);
  put32(spriteBytes() + 10, 0x11223344u);
  put32(spriteBytes() + 14, initialSize);
  put32(spriteBytes() + 18, initialOwner);
  const auto setDirectory = [](int index, std::uint32_t value) {
    g_DlxDirectoryEntryStartOffsets[index] = value;
    if (index >= 0 && index < 1024) directoryImage[index] = value;
  };
  setDirectory(current.index, entryStart);
  setDirectory(current.index + 1, current.useEof ? 0 : entryStart + current.recordSize);
  events.clear();
  returnedValue = 0;
  didReturn = false;
}
using Loader = DWORD (*)(DWORD, char *, int);
static Result run(Loader loader) {
  reset();
  char name[] = "synthetic.s32";
  if (setjmp(quitTarget) == 0) {
    returnedValue = loader(low32(spriteBytes()), name, current.index);
    didReturn = true;
  }
  return {didReturn, returnedValue, events, arena, payload, directory};
}
static const Event &event(const Result &result, Kind kind) {
  const Event *found = nullptr;
  for (const auto &item : result.events) if (item.kind == kind) {
    require(found == nullptr, "event repeated unexpectedly");
    found = &item;
  }
  require(found != nullptr, "required event missing");
  return *found;
}
static void contract(const Result &result) {
  std::vector<Kind> order{Resolve};
  if (!current.queryFails) {
    order.push_back(DirectoryRead);
    if (current.useEof) order.push_back(StreamSize);
    order.insert(order.end(), {Seek, HeaderRead, Allocate});
    if (current.allocationFails) order.insert(order.end(), {Log, Quit});
    if (!current.allocationFails || !current.terminalQuit)
      order.insert(order.end(), {PayloadRead, Release});
  }
  require(order.size() == result.events.size(), "callback count changed");
  for (std::size_t i = 0; i != order.size(); ++i)
    require(order[i] == result.events[i].kind, "callback order changed");
  require(result.returned == !(current.allocationFails && current.terminalQuit), "quit return behavior changed");
  if (result.returned) require(result.value == low32(spriteBytes()), "loader return identity changed");
  const std::size_t offset = 32 + alignment;
  const Event &resolve = event(result, Resolve);
  require(get32(resolve.arena.data() + offset + 10) == 0, "payload not cleared before resolve callback");
  require(get32(resolve.arena.data() + offset + 14) == initialSize, "size modified before query");
  std::array<unsigned char, 96> expected;
  expected.fill(0xD7);
  put32(expected.data() + offset + 10, 0);
  put32(expected.data() + offset + 14, initialSize);
  put32(expected.data() + offset + 18, initialOwner);
  if (!current.queryFails) {
    const Event &seek = event(result, Seek);
    require(seek.b == entryStart, "canonical cached start offset was not preserved");
    require(get32(seek.arena.data() + offset + 14) == current.recordSize, "record size not written before seek");
    std::uint32_t size = current.recordSize;
    if (current.seekSize != unchanged) size = static_cast<std::uint32_t>(current.seekSize);
    require(get32(event(result, HeaderRead).arena.data() + offset + 14) == size, "header callback order changed");
    if (current.headerSize != unchanged) size = static_cast<std::uint32_t>(current.headerSize);
    const std::uint32_t requested = size - std::uint32_t{10};
    require(event(result, Allocate).a == requested, "fresh post-header uint32 size subtraction changed");
    require(get32(event(result, Allocate).arena.data() + offset + 10) == 0, "payload handle written before allocator");
    if (current.allocatorSize != unchanged) size = static_cast<std::uint32_t>(current.allocatorSize);
    std::uint32_t handle = current.allocationFails ? 0 : low32(payload.data());
    if (current.allocationFails) {
      const Event &log = event(result, Log);
      require(log.a == 0 && log.b == 10 && log.c == requested, "canonical log arguments changed");
      require(get32(log.arena.data() + offset + 10) == 0, "failed allocation handle not stored before log");
      if (current.mutateInDebugLog) { handle = low32(payload.data() + 64); size = 777; }
    }
    if (!current.allocationFails || !current.terminalQuit) {
      const Event &read = event(result, PayloadRead);
      require(read.b == (current.allocationFails ? 0 : low32(payload.data())), "canonical cached payload handle changed");
      require(read.c == requested, "canonical cached payload count changed");
      require(get32(read.arena.data() + offset + 10) == handle, "stored payload handle/callback mutation changed");
      if (current.mutateAtPayloadRead) { handle = 0x12345678u; size = 0x55667788u; }
      require(event(result, Release).a == queryHandle, "query release identity changed");
    }
    for (int i = 0; i != 10; ++i) expected[offset + i] = static_cast<unsigned char>(0x10 + i);
    put32(expected.data() + offset + 10, handle);
    put32(expected.data() + offset + 14, size);
    std::array<unsigned char, 128> expectedPayload;
    expectedPayload.fill(0xC5);
    if (!current.allocationFails && requested <= expectedPayload.size())
      for (std::uint32_t i = 0; i != requested; ++i) expectedPayload[i] = static_cast<unsigned char>(i ^ 0x6D);
    require(result.payload == expectedPayload, "payload bytes/canary changed");
  }
  require(result.arena == expected, "header/fields/ownership/canary write footprint changed");
}

int main() {
  std::vector<Case> cases;
  Case c;
  cases.push_back(c);
  c = {}; c.name = "null-query"; c.queryFails = true; cases.push_back(c);
  c = {}; c.name = "EOF-fallback"; c.useEof = true; cases.push_back(c);
  c = {}; c.name = "signed-negative-index"; c.index = -1; cases.push_back(c);
  c = {}; c.name = "last-backed-index"; c.index = 1023; cases.push_back(c);
  c = {}; c.name = "zero-payload"; c.recordSize = 10; cases.push_back(c);
  c = {}; c.name = "uint32-underflow"; c.recordSize = 6; cases.push_back(c);
  c = {}; c.name = "header-high-bit-size"; c.headerSize = 0x80000010u; cases.push_back(c);
  c = {}; c.name = "header-max-size"; c.headerSize = UINT32_MAX; cases.push_back(c);
  c = {}; c.name = "EOF-mutates-start"; c.useEof = true; c.mutateStartAtEof = true; cases.push_back(c);
  c = {}; c.name = "seek-mutates-size"; c.seekSize = 41; cases.push_back(c);
  c = {}; c.name = "header-mutates-size"; c.headerSize = 24; cases.push_back(c);
  c = {}; c.name = "allocator-mutates-fields"; c.allocatorSize = 999; cases.push_back(c);
  c = {}; c.name = "payload-read-mutates-fields"; c.mutateAtPayloadRead = true; cases.push_back(c);
  c = {}; c.name = "returning-quit-mutates-fields"; c.allocationFails = true; c.mutateInDebugLog = true; cases.push_back(c);
  c = {}; c.name = "terminal-quit"; c.allocationFails = true; c.terminalQuit = true; cases.push_back(c);
  c = {}; c.name = "wide-allocator-success"; c.wideAllocatorReturn = true; cases.push_back(c);
  c = {}; c.name = "wide-allocator-zero-low32"; c.wideAllocatorReturn = true; c.allocationFails = true; cases.push_back(c);
  unsigned count = 0;
  for (const Case &test : cases) for (alignment = 0; alignment != 2; ++alignment) {
    current = test;
    const Result oracle = run(frozen_LoadCachedEntry);
    contract(oracle);
    const Result actual = run(DLXSprite_LoadCachedEntry);
    contract(actual);
    require(actual == oracle, "actual source differs from frozen trace/full-byte state");
    ++count;
  }
  std::printf("%u cases; actual/frozen traces and byte contracts agree\n", count);
}
