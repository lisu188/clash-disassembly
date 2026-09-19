#include <array>
#include <bit>
#include <climits>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

extern "C" {
alignas(16) unsigned char random_state_image[64] = {};
}
asm(".global g_RngState\n.set g_RngState, random_state_image+16\n");
char aRandom_initSee[29] = "Random_Init(): seed = 0x%08x";
int logEnabled;
int battleLogEnabled;

namespace {
struct Event {
  int kind;
  uint32_t state;
  int first;
  int second;
  uint32_t third;
  uint32_t fourth;
  bool operator==(const Event&) const = default;
};
std::vector<Event> events;
std::array<int, 2> ticks;
unsigned tick_index;
int wall_time;
unsigned long long cases;
void require(bool condition, const char *message) {
  if (!condition) {
    std::fprintf(stderr, "failure: %s case=%llu\n", message, cases);
    std::exit(1);
  }
}
int bits(uint32_t value) { return std::bit_cast<int32_t>(value); }
void fill_state(uint32_t state) {
  for (unsigned i=0; i<sizeof(random_state_image); ++i)
    random_state_image[i] = static_cast<unsigned char>(i * 71u + 53u);
  g_RngState = bits(state);
}
void guards() {
  for (unsigned i=0; i<sizeof(random_state_image); ++i)
    if (i<16 || i>=20)
      require(random_state_image[i] == static_cast<unsigned char>(i * 71u + 53u), "RNG storage guard");
}
__attribute__((noinline)) unsigned x86_result(uint32_t seed, uint32_t range, uint32_t minimum) {
  unsigned result = seed;
  asm volatile("xorl %%edx, %%edx\n\tdivl %[range]\n\tleal (%%edx,%[minimum]), %%eax"
               : "+&a"(result) : [range] "r"(range), [minimum] "r"(minimum) : "edx", "cc");
  return result;
}
}
int time_(void) {
  events.push_back({1, static_cast<uint32_t>(g_RngState), 0, 0, 0, 0});
  return wall_time;
}
int Time_Now(int first, int second) {
  require(tick_index < ticks.size(), "too many time reads");
  events.push_back({2, static_cast<uint32_t>(g_RngState), first, second, tick_index, 0});
  return ticks[tick_index++];
}
