#include <array>
#include <bit>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {
constexpr int kExpectedSinTable[363] = {
#include "sine_table.inc"
};
constexpr size_t kPage = 4096;
unsigned char expected_page[kPage];
uint64_t cases = 0;
uint32_t random_state = 0xA51C395Du;

void require(bool condition, const char* message)
{
  if (!condition) {
    std::fprintf(stderr, "failure: %s, case=%llu\n", message,
                 static_cast<unsigned long long>(cases));
    std::exit(1);
  }
}
int next_signed()
{
  random_state ^= random_state << 13;
  random_state ^= random_state >> 17;
  random_state ^= random_state << 5;
  return std::bit_cast<int32_t>(random_state);
}
}

extern "C" {
alignas(4096) unsigned char world_geometry_table_storage[3 * 4096] = {};
}
asm(".global g_MathSinTableQ16\n"
    ".set g_MathSinTableQ16, world_geometry_table_storage+4096\n");

namespace {
void prepare_table()
{
  require(sysconf(_SC_PAGESIZE) == static_cast<long>(kPage), "fixture needs 4096-byte pages");
  require(reinterpret_cast<uintptr_t>(world_geometry_table_storage) + sizeof(world_geometry_table_storage)
          <= UINT32_MAX, "table must retain the recovered low32 address domain");
  for (size_t index = 0; index < kPage; ++index)
    expected_page[index] = static_cast<unsigned char>((index * 73u + 91u) & 255u);
  std::memcpy(expected_page, kExpectedSinTable, sizeof(kExpectedSinTable));
  std::memcpy(world_geometry_table_storage + kPage, expected_page, kPage);
  require(mprotect(world_geometry_table_storage, kPage, PROT_NONE) == 0, "leading guard page");
  require(mprotect(world_geometry_table_storage + 2 * kPage, kPage, PROT_NONE) == 0, "trailing guard page");
  require(mprotect(world_geometry_table_storage + kPage, kPage, PROT_READ) == 0, "read-only table image");
}
void unchanged()
{
  require(std::memcmp(world_geometry_table_storage + kPage, expected_page, kPage) == 0,
          "full table page including suffix guard bytes changed");
}

// The original EAX/EDX/ECX integer instructions, with an explicit 32-bit
// effective-address calculation. This retains x86 NEG and scaled-address
// wrap for INT_MIN rather than relying on host C++ signed overflow.
__attribute__((noinline)) int x86_sine(int angle)
{
  const uint32_t base = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_MathSinTableQ16));
  asm volatile(
      "movl %%eax, %%edx\n\t"
      "testl %%eax, %%eax\n\t"
      "jl 1f\n\t"
      "cmpl $360, %%eax\n\t"
      "jl 2f\n\t"
      "movl $360, %%ecx\n\t"
      "sarl $31, %%edx\n\t"
      "idivl %%ecx\n\t"
      "2: leal (%[base],%%edx,4), %%edx\n\t"
      "movl (%%rdx), %%eax\n\t"
      "jmp 3f\n\t"
      "1: negl %%edx\n\t"
      "cmpl $360, %%edx\n\t"
      "jl 4f\n\t"
      "movl $360, %%ecx\n\t"
      "movl %%edx, %%eax\n\t"
      "sarl $31, %%edx\n\t"
      "idivl %%ecx\n\t"
      "4: leal (%[base],%%edx,4), %%edx\n\t"
      "movl (%%rdx), %%eax\n\t"
      "negl %%eax\n\t"
      "3:"
      : "+&a"(angle)
      : [base] "r"(base)
      : "ecx", "edx", "cc", "memory");
  return angle;
}

template<class Check> void sine_corpus(Check check)
{
  const int edges[] = {INT_MIN, INT_MIN + 1, INT_MIN + 2, INT_MIN + 359,
                       INT_MIN + 360, -2147483520, -1000000001, -721, -720, -719,
                       -361, -360, -359, -1, 0, 1, 359, 360, 361, 719, 720, 721,
                       1000000001, INT_MAX - 360, INT_MAX - 1, INT_MAX};
  for (int angle : edges) check(angle);
  for (int angle = -8192; angle <= 8192; ++angle) check(angle);
  for (int residue = 0; residue < 360; ++residue) {
    check(2147483160 + residue);
    check(-2147483160 - residue);
  }
  for (unsigned index = 0; index < 65536; ++index) check(next_signed());
  // These original caller expressions are defined int32 operations and reach
  // INT_MIN without any preceding overflow.
  volatile int shrine_tick = -1073741779;
  volatile int battle_pulse_tick = -536870912;
  const int shrine_angle = 2 * shrine_tick - 90;
  const int pulse_angle = 4 * battle_pulse_tick;
  require(shrine_angle == INT_MIN && pulse_angle == INT_MIN, "reachable caller edge examples");
  check(shrine_angle);
  check(pulse_angle);
}
}
