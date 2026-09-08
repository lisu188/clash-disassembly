namespace {
#ifdef GAME_RANDOM_CLASS
constexpr int last_mode = 2;
#else
constexpr int last_mode = 1;
#endif
unsigned invoke_rng(int mode, int minimum, int maximum
#ifdef GAME_RANDOM_CLASS
                    , const clash95::GameRandom& random
#endif
                    ) {

#ifdef GAME_RANDOM_CLASS
  if (mode == 1) return random.Rng_RandRange(minimum, maximum);
#else
  (void)mode;
#endif
  return Rng_RandRange(minimum, maximum);
}
void invoke_init(int mode, char first, DWORD second
#ifdef GAME_RANDOM_CLASS
                 , const clash95::GameRandom& random
#endif
                 ) {
  if (mode < 0) return Before_initRandomSeed(first, second);

#ifdef GAME_RANDOM_CLASS
  if (mode == 1) return random.initRandomSeed(first, second);
#endif
  return initRandomSeed(first, second);
}
void one_rng(uint32_t initial, int minimum, int maximum, int first_tick, int second_tick) {
  const uint32_t intermediate = initial ^ (static_cast<uint32_t>(first_tick) + 0x34523471u);
  const uint32_t final_state = intermediate + 0x83356532u * static_cast<uint32_t>(second_tick);
  const uint32_t range = static_cast<uint32_t>(maximum) + 1u - static_cast<uint32_t>(minimum);
  const uint32_t expected = range ? x86_result(final_state, range, static_cast<uint32_t>(minimum))
                                  : static_cast<uint32_t>(minimum);
  const std::vector<Event> expected_events = {
    {2, initial, 0, 0, 0, 0}, {2, intermediate, 0, 0, 1, 0}
  };
#ifdef GAME_RANDOM_CLASS
  const clash95::GameRandom random(aRandom_initSee, g_RngState);
#endif
  for (int mode=1; mode<=last_mode; ++mode) {
    fill_state(initial); events.clear(); tick_index=0; ticks={first_tick,second_tick};
    const unsigned actual = invoke_rng(mode, minimum, maximum
#ifdef GAME_RANDOM_CLASS
                                      , random
#endif
                                      );
    require(actual == expected, "unsigned 32-bit DIV/LEA result");
    require(static_cast<uint32_t>(g_RngState) == final_state, "exact final RNG state");
    require(events == expected_events, "time reads/state progression/order");
    guards();
  }
  // Compare the unmodified recovered body wherever its signed addition is
  // defined; the full-domain oracle above covers the separately repaired loss.
  const int64_t legacy_sum = range ? static_cast<int64_t>(bits(final_state % range)) + minimum : 0;
  if (!range || (legacy_sum >= INT_MIN && legacy_sum <= INT_MAX)) {
    fill_state(initial); events.clear(); tick_index=0; ticks={first_tick,second_tick};
    require(Before_Rng_RandRange(minimum,maximum)==expected, "defined original-body result");
    require(static_cast<uint32_t>(g_RngState)==final_state, "defined original-body state");
    require(events==expected_events, "defined original-body time order");
    guards();
  }
  ++cases;
}
void initializations() {
  for (int logging=0; logging<4; ++logging) {
    logEnabled = logging & 1; battleLogEnabled = logging >> 1;
    for (int seed : {INT_MIN, INT_MIN+1, -1, 0, 1, INT_MAX}) {
      for (int first : {-128, -1, 0, 1, 127}) {
        for (uint32_t second : {0u, 1u, 0x80000000u, UINT32_MAX}) {
#ifdef GAME_RANDOM_CLASS
          const clash95::GameRandom random(aRandom_initSee, g_RngState);
#endif
          for (int mode=-1; mode<=last_mode; ++mode) {
            if (mode == 0) continue;
            fill_state(0x57a13e91u); wall_time=seed; events.clear(); tick_index=0;
            invoke_init(mode, static_cast<char>(first), second
#ifdef GAME_RANDOM_CLASS
                        , random
#endif
                        );
            require(g_RngState == seed, "init clock value");
            std::vector<Event> expected = {
              {1, 0x57a13e91u, 0, 0, 0, 0},
              {3, static_cast<uint32_t>(seed), 0, static_cast<char>(first), second,
               static_cast<uint32_t>(reinterpret_cast<uintptr_t>(aRandom_initSee))}
            };
            if (mode < 0) {
              require(events.size()==2, "original init event count");
              expected[1].first=events[1].first; // the actual logger discards only this changed context
            }
            require(events == expected, "defined discarded context and init callback order");
            guards();
          }
          ++cases;
        }
      }
    }
  }
}
void original_controls() {
  fill_state(7); wall_time=12345; events.clear();
  Before_initRandomSeed('x', 0x89abcdefu);
  require(events.size()==2 && events[1].kind==3 && events[1].first!=0, "unrepaired init context control");
  std::printf("unrepaired_init_context=%d\n", events[1].first);
  pid_t child=fork(); require(child>=0, "fork original overflow control");
  if (!child) {
    const rlimit limit={0,0}; setrlimit(RLIMIT_CORE,&limit); alarm(2);
    fill_state(0xfffffffeu ^ 0x34523471u); ticks={0,0}; tick_index=0; events.clear();
    volatile unsigned result=Before_Rng_RandRange(INT_MIN,INT_MAX-1);
    (void)result; _exit(0);
  }
  int status=0; require(waitpid(child,&status,0)==child,"wait original overflow control");
  require(WIFSIGNALED(status) && WTERMSIG(status)==SIGILL,"unrepaired range overflow traps");
  std::printf("unrepaired_range_overflow=signal:%d\n",WTERMSIG(status));
}
void sequences() {
#ifdef GAME_RANDOM_CLASS
  const clash95::GameRandom random(aRandom_initSee, g_RngState);
#endif
  for (int mode=1; mode<=last_mode; ++mode) {
    fill_state(0x9381b20du);
    uint32_t expected=0x9381b20du;
    for (unsigned i=0; i<4096; ++i) {
      // A held object must observe explicit outside updates to the same word.
      if (!(i%17)) { expected ^= 0xa83f091du; g_RngState=bits(expected); }
      const int first=bits(i*0x83356532u), second=bits(i*0x34523471u+17);
      const uint32_t intermediate=expected^(static_cast<uint32_t>(first)+0x34523471u);
      expected=intermediate+0x83356532u*static_cast<uint32_t>(second);
      ticks={first,second};tick_index=0;events.clear();
      const unsigned actual=invoke_rng(mode,-20,20
#ifdef GAME_RANDOM_CLASS
                                       ,random
#endif
                                       );
      require(actual==x86_result(expected,41u,static_cast<uint32_t>(-20)),"sequence result");
      require(static_cast<uint32_t>(g_RngState)==expected,"sequence state");
      require(events.size()==2 && events[1].state==intermediate,"sequence time ordering");
      guards();
    }
  }
}
}
int main() {
  original_controls();
  initializations();
  const int values[]={INT_MIN,INT_MIN+1,-1000000000,-1,0,1,1000000000,INT_MAX-1,INT_MAX};
  for (int minimum:values) for (int maximum:values)
    for (int tick:values) for (uint32_t initial:{0u,1u,0x80000000u,UINT32_MAX})
      one_rng(initial,minimum,maximum,tick,bits(~static_cast<uint32_t>(tick)));
  uint32_t state=0x3af239b1u;
  auto next=[&]() {state^=state<<13;state^=state>>17;state^=state<<5;return state;};
  for (unsigned i=0;i<65536;++i) {
    uint32_t initial=next();int minimum=bits(next()),maximum=bits(next()),first=bits(next()),second=bits(next());
    one_rng(initial,minimum,maximum,first,second);
  }
  sequences();
#ifdef GAME_RANDOM_CLASS
  const char *dispatch = "direct_and_abi";
#else
  const char *dispatch = "free";
#endif
  std::printf("cases=%llu sequence_steps=4096 storage_bytes=64 clocks_per_draw=2 dispatch=%s pass\n",cases,dispatch);
}
