/* cov5_02: stack-spray coverage pass for a batch of functions whose
 * remaining uncovered lines sit behind a decompiler "possibly undefined"
 * local (see scratchpad/cov5_batches/cov5_02.json):
 *   Rules_MultifieldDeleteRange, Map_ClassifyFogOfWarOverlayForPlayer,
 *   Class_SlotExistPCommand, Rules_ParseDefruleRHS,
 *   Rules_WriteConstructModuleItemHeaderToCode, CRT_BeginThread,
 *   Rules_MathCoth, Deffunction_Delete, Defgeneric_GetMethodRestrictionsCommand.
 *
 * KEY TECHNIQUE (per tests/unit/cases/test_cov3_01.c): a decompiler-lost
 * local reads whatever the current stack slot last contained. Spraying a
 * large volatile buffer with a chosen value immediately before the target
 * call reliably steers that "undefined" read to the sprayed value, because
 * every sibling call made from the same TEST(...) body starts from the same
 * stack pointer.
 *
 * Every test runs isolated in its own forked child (see tests/unit/test_all.c,
 * fork()+alarm(8) per TEST), so calls that crash, exit(), or spin are safe --
 * coverage up to the fault point is kept regardless. Buffers whose address
 * is threaded through a narrowed 32-bit int/_DWORD field are declared
 * `static` so they land in the low .bss image instead of a stack address
 * that would truncate to garbage on this 64-bit -no-pie build.
 *
 * Every TEST below is prefixed cov5_02_ to avoid symbol collisions with all
 * earlier cov/cov2/cov3/cov4 batch files (all #included into one
 * translation unit by tests/unit/test_all.c). */

/* ---- shared stack-spray helper: fills a large volatile int buffer with a
 * chosen dword value right before the target call (see test_cov3_01.c's
 * cov3_01_stack_prime for the original of this trick). ---- */
static void cov5_02_prime_int(int val) {
  volatile int buf[65536];
  int i;
  for (i = 0; i < 65536; i++) {
    buf[i] = val;
  }
}

/* =========================================================================
 * Rules_MultifieldDeleteRange (128599-128687, 28 uncovered): the whole back
 * half of the function is gated behind `v10 = *(_DWORD *)(v9 + 12);` where
 * v9 is a genuinely decompiler-lost local (comment: "variable 'v9' is
 * possibly undefined") -- every prior test crashed immediately on that
 * dereference, truncating coverage right there. Priming v9 with the address
 * of a real zeroed buffer makes v10 start at 0 (a sane "no prior elements
 * scanned" state), letting both internal copy loops run for real.
 *
 * NOTE on the OTHER uncovered cluster (128633-128637, the `if (!v6)` empty-
 * multifield branch): the guard just above it is
 *   `if (a3 < a4 || a4 < 1 || a3 < 1 || v6 < a4 || v6 < a3) { ...error... }`
 * Passing this guard requires a4 >= 1 (else `a4 < 1` fires) and v6 >= a4
 * (else `v6 < a4` fires), which together force v6 >= 1 whenever the guard is
 * satisfied -- so `v6 == 0` and "guard passed" are mutually exclusive for
 * any real int a3/a4/v6, regardless of how v6 (a2[4]-a2[3]+1) is driven
 * negative/zero. That branch is unreachable through this entry point; not
 * attempted (same class of dead branch documented for Class_SlotExistPCommand's
 * `return 13` case below). ========================================= */
TEST(cov5_02_multifielddeleterange, primed_v9_full_run_both_loops) {
  static _DWORD a1buf[16], a2buf[16];
  static _DWORD source[256];
  static _DWORD v9target[64];

  memset(a1buf, 0, sizeof a1buf);
  memset(a2buf, 0, sizeof a2buf);
  memset(source, 0, sizeof source);
  memset(v9target, 0, sizeof v9target); /* *(v9target+12) == 0 -> v10 starts at 0 */

  /* source multifield: begin=0, end=4 -> count v6 = 5 */
  a2buf[2] = (_DWORD)(intptr_t)source;
  a2buf[3] = 0;
  a2buf[4] = 4;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_prime_int((int)(intptr_t)v9target);
  /* a3=3 (range end), a4=2 (range start): v7=1>0 drives the prefix-copy
   * do-while (one trip), then the skip-while, then (v11<=a1[4]) drives the
   * tail-copy do-while (two trips using the real trailing source elements
   * at indices 3,4) -- exercising every line in the back half. */
  TOUCH(Rules_MultifieldDeleteRange(a1buf, a2buf, 3, 2, 0));
}

/* =========================================================================
 * Map_ClassifyFogOfWarOverlayForPlayer (23971-24029, 13 uncovered): every
 * `Map_IsTileVisibleToPlayer` call short-circuits to `false` for free (no
 * memory touched) as long as its first coordinate is negative -- so calling
 * with a1=-10 makes v7 (the final visibility bool) reliably 0 without any
 * game-state fixture at all. What remains, `v9 = v7 | (v8 & 0xFE)` and the
 * whole `~v10 & mask` cascade, read `v8`/`v10` (comments: "variable
 * 'v8'/'v10' is possibly undefined"). The obvious next step -- byte-spray
 * the stack with a chosen value right before the call, same as every other
 * function in this file -- does NOT work here: verified empirically with a
 * private scratch build+gdb-style debug print inserted right after the read
 * (per this pass's instructions), `v8` and `v10` come out to the exact same
 * fixed byte value regardless of the sprayed byte, regardless of the input
 * coordinates, and even regardless of how much/what kind of code runs
 * between the spray and the call (tried a bare call, an engine bootstrap, a
 * small local buffer, a 4KB int-spray, and two back-to-back calls in the
 * same TEST -- all six shapes produced an IDENTICAL v8/v10 pair). That
 * value's bytes are ASCII-printable in every case tried (e.g. 'R'/'e',
 * 'B'/'8'), which points to these two reads landing on pristine,
 * never-written stack memory left over from process/thread startup (glibc
 * argv/envp strings) that sits BELOW every frame this test can reach --
 * genuinely out of reach for a spray issued from the calling TEST body, not
 * a probabilistic miss. Kept to a small, honest set of calls that still
 * banks the unconditional prefix (23971-23991) and whichever single branch
 * the ambient environment happens to select, without overclaiming control
 * over the specific numbered branch. ====================================== */
TEST(cov5_02_fogoverlay, negative_coords_no_gamedata_needed) {
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-10, -10, 0));
}
TEST(cov5_02_fogoverlay, negative_coords_different_player_index) {
  TOUCH(Map_ClassifyFogOfWarOverlayForPlayer(-4, -7, 1));
}

/* =========================================================================
 * Class_SlotExistPCommand (172416-172455, 12 uncovered): the whole
 * `if (result)` body sits behind Class_CheckSlotExists -> Class_ParseClass-
 * Reference -> Class_LookupByQualifiedName actually finding a real class
 * (prior passes' test_cov4_03.c/test_cov2_00.c notes document this as the
 * hard ceiling), AND behind Lexer_ParseValueList's own decompiler-lost
 * check `a3 == *(_DWORD *)(v7 + 4)` (v7 undefined) which is the ONLY success
 * path for a SYMBOL(2)-type request in Lexer_ParseValueList (every other
 * branch in that function is a type-mismatch error report for a3==2) --
 * without priming that slot, every SYMBOL argument parse in this whole call
 * chain dies right there, which is almost certainly why cov3_02/cov4_03's
 * earlier attempts (predating this stack-spray technique) never actually
 * reached past Class_ParseClassReference's first parse despite a
 * real-looking argument chain. Combine both fixes: register a real (fake)
 * class via the cov4_01/cov3_02 "class hash table" recipe so
 * Class_LookupByQualifiedName succeeds, a real 3-node SYMBOL chain (class
 * name, slot name, "inherit") so Rules_RtnArgCount()==3, and prime the
 * Lexer_ParseValueList undefined slot so every SYMBOL(2) parse in the chain
 * succeeds instead of crashing. This reaches the Rules_RtnArgCount()==3
 * branch and the inner Lexer_ParseValueList(3,...) call, but the final
 * `strcmp_(v5, aInherit_0)` (v5 ALSO decompiler-lost, comment: "variable
 * 'v5' is possibly undefined") reads the SAME sprayed slot -- which holds
 * our v7-priming buffer's address, not a real "inherit" string -- so the
 * comparison mismatches and this lands in the error-report branch rather
 * than the `v3 = 1` success path. Getting v5 to ALSO resolve to a real
 * "inherit" string while v7 keeps resolving to the priming buffer would
 * need two different leftover values in the same call frame; not chased
 * further here (documented hard ceiling, same spirit as the other notes in
 * this file). This still banks the Rules_RtnArgCount()==3 branch and the
 * inherit-mismatch error-report lines. ==================================== */
static int *cov5_02_register_fake_class(const char *name) {
  static _DWORD classTable[0xA7];
  static _DWORD classRecord[128];
  static _DWORD scopeInfo[8];
  static unsigned char scopeBits[8];
  static _DWORD fakeModule[16];
  signed int *symbol;
  unsigned int bucket;

  memset(classTable, 0, sizeof classTable);
  memset(classRecord, 0, sizeof classRecord);
  memset(scopeInfo, 0, sizeof scopeInfo);
  memset(scopeBits, 0xFF, sizeof scopeBits);
  memset(fakeModule, 0, sizeof fakeModule);

  symbol = Str_Intern((char *)name, 0);
  bucket = Class_HashClassName((int)(intptr_t)symbol);

  scopeInfo[4] = (_DWORD)(intptr_t)scopeBits;

  classRecord[0] = (_DWORD)(intptr_t)symbol;
  *((unsigned char *)classRecord + 20) |= 1;
  classRecord[25] = 0;
  classRecord[26] = (_DWORD)(intptr_t)scopeInfo;

  classTable[bucket % 0xA7u] = (_DWORD)(intptr_t)classRecord;
  dword_51AD68 = (int)(intptr_t)classTable;

  fakeModule[6] = 0;
  dword_51A9B0 = (int)(intptr_t)fakeModule;

  return (int *)(intptr_t)classRecord;
}

static void cov5_02_arg_node_init(unsigned char *node, short type_tag,
                                  void *value_ptr, unsigned char *next_node) {
  memset(node, 0, 32);
  *(short *)(node + 0) = type_tag;
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)value_ptr;
  *(_DWORD *)(node + 10) = (_DWORD)(intptr_t)next_node;
}

static void cov5_02_install_arg_chain(unsigned char *argnode,
                                       unsigned char *head_node) {
  memset(argnode, 0, 32);
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)head_node;
  dword_51A960 = (int)(intptr_t)argnode;
}

TEST(cov5_02_class, slot_exist_p_command_fake_class_primed_chain) {
  static unsigned char argnode[32], node1[32], node2[32], node3[32];
  static _DWORD classval[8], slotval[8], inheritval[8];
  static _DWORD lexprime[8];
  static int a1out[8];
  int saved960 = dword_51A960;
  int saved964 = dword_51A964;

  memset(classval, 0, sizeof classval);
  memset(slotval, 0, sizeof slotval);
  memset(inheritval, 0, sizeof inheritval);
  memset(a1out, 0, sizeof a1out);
  memset(lexprime, 0, sizeof lexprime);

  classval[4] = (_DWORD)(intptr_t)"Cov5_02FakeClass";
  slotval[4] = (_DWORD)(intptr_t)"slot1";
  inheritval[4] = (_DWORD)(intptr_t)"inherit";
  lexprime[1] = 2; /* offset+4 == 2 (SYMBOL): satisfies Lexer_ParseValueList's
                     * `a3 == *(_DWORD *)(v7 + 4)` shortcut for every SYMBOL
                     * request in this call chain. */

  cov5_02_arg_node_init(node3, 2 /* SYMBOL */, inheritval, 0);
  cov5_02_arg_node_init(node2, 2 /* SYMBOL */, slotval, node3);
  cov5_02_arg_node_init(node1, 2 /* SYMBOL */, classval, node2);
  cov5_02_install_arg_chain(argnode, node1);

  /* Str_Intern/the atom tables need the reserve-block arena carved out
   * first (same ordering every other test in this project uses) --
   * calling the fake-class registration before this bootstrap crashes
   * immediately inside Str_Intern. */
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_register_fake_class("Cov5_02FakeClass");
  dword_51A964 = 0;
  cov5_02_prime_int((int)(intptr_t)lexprime);
  TOUCH(Class_SlotExistPCommand(a1out, 0.0));

  dword_51A960 = saved960;
  dword_51A964 = saved964;
}

/* =========================================================================
 * Rules_ParseDefruleRHS (153895-153932, 10 uncovered): every local past
 * `Parser_ParseProgram`'s call is decompiler-lost (v2 itself -- the pointer
 * PASSED INTO Parser_ParseProgram -- plus v6/v7/v4/v5 read after it
 * returns). Unprimed, v2 is whatever garbage int happens to be on the
 * stack, used as a WRITABLE address inside Parser_ParseProgram
 * (`Parser_NextToken(a1, (int)a2)` writes the lexed token into `*a2`) --
 * so a bad v2 crashes immediately on the very first token, before
 * `if (result)` can ever be reached. Priming v2 with the address of a real
 * zeroed scratch buffer makes that write land safely; combined with a real
 * lexer-router single-character input (matching test_cov3_02.c's own
 * documented recipe: a bare symbol character makes Parser_ParseProgram's
 * `*a2 == 2 && v8 && !strcmp_(v8, v8)` shortcut trip, since any v8 compared
 * against itself is trivially equal once it points at readable memory),
 * this reaches the `if (result)` body. v6 (the `==101` selector) is
 * unprimed/unconstrained here -- whichever way it happens to land, one of
 * the two inner branches (101 vs not) still executes, banking that side of
 * this attempt. ========================================================== */
static int cov5_02_lex_query(int a1) {
  (void)a1;
  return 1;
}
static int cov5_02_lex_skip(int a1, int a2) {
  (void)a1;
  (void)a2;
  return 0;
}
static const char *cov5_02_lex_seq;
static int cov5_02_lex_pos;
static int cov5_02_lex_read(int a1) {
  unsigned char c;
  (void)a1;
  c = (unsigned char)cov5_02_lex_seq[cov5_02_lex_pos];
  if (c) {
    ++cov5_02_lex_pos;
  } else {
    c = ' ';
  }
  return c;
}
static void cov5_02_install_lex_router(_DWORD *router, const char *text) {
  memset(router, 0, 16 * sizeof(_DWORD));
  router[1] = 1; /* offset4: active */
  router[3] = (_DWORD)(intptr_t)cov5_02_lex_query; /* offset12: query */
  router[6] = (_DWORD)(intptr_t)cov5_02_lex_read;  /* offset24: read */
  router[7] = (_DWORD)(intptr_t)cov5_02_lex_skip;  /* offset28: skip */
  dword_51A604 = (int)(intptr_t)router;
  cov5_02_lex_seq = text;
  cov5_02_lex_pos = 0;
}

TEST(cov5_02_parsedefrulerhs, primed_v2_real_token_drives_success) {
  static _DWORD router[16];
  static _DWORD v2target[64];
  int saved604 = dword_51A604;

  memset(v2target, 0, sizeof v2target);
  cov5_02_install_lex_router(router, "a)");

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_prime_int((int)(intptr_t)v2target);
  TOUCH(Rules_ParseDefruleRHS(717171));

  dword_51A604 = saved604;
}

/* =========================================================================
 * Rules_WriteConstructModuleItemHeaderToCode (133174-133218, 9 uncovered):
 * every local past the first Output_WriteFormatted call is decompiler-lost.
 * `v8 = Module_GetItem(a2, v7)` is real (Module_GetItem is a clean function
 * with no UB of its own), so priming its index argument (v7) to equal the
 * ADDRESS of a real static "spray target" buffer -- and choosing the fake
 * module's item-array base via `arrBase = itemArraySlotAddr - 4*spray_addr`
 * (plain 32-bit int arithmetic, matching the project's own 32-bit-pointer
 * truncation model) -- makes `arrBase + 4*v7` land exactly on our
 * itemArraySlot regardless of what the spray address numerically is. That
 * slot holds the address of a second real struct ("itemstruct"), so v8
 * resolves to a genuinely valid, readable pointer. v20 (used later for the
 * `*(v20+8)` read) aliases the SAME sprayed value, which we also make equal
 * to the spray-target buffer's own (real, readable) address, so that read
 * is safe too. This lets both `if (v12)`/`if (v15)` branches run for real
 * instead of crashing on the first dereference; two variants flip which of
 * v12/v15 (from itemstruct[1] and spraytarget[2] respectively) is
 * zero/nonzero to cover both sides of each branch. ======================== */
static void cov5_02_wcmih_prime(int val) {
  volatile int buf[65536];
  int i;
  for (i = 0; i < 65536; i++) {
    buf[i] = val;
  }
}

TEST(cov5_02_wcmih, v12_nonzero_v15_zero) {
  static _DWORD spraytarget[8];
  static _DWORD fakemodule[8];
  static _DWORD itemarrayslot[4];
  static _DWORD itemstruct[8];
  static _DWORD v12target[8];
  int arrBase;
  int savedModule = dword_51A9B0;

  memset(spraytarget, 0, sizeof spraytarget);
  memset(fakemodule, 0, sizeof fakemodule);
  memset(itemarrayslot, 0, sizeof itemarrayslot);
  memset(itemstruct, 0, sizeof itemstruct);
  memset(v12target, 0, sizeof v12target);

  itemstruct[1] = (_DWORD)(intptr_t)v12target; /* v8+4 -> v12: real, valid ptr */
  itemarrayslot[0] = (_DWORD)(intptr_t)itemstruct; /* Module_GetItem's return (v8) */

  arrBase = (int)(intptr_t)itemarrayslot - 4 * (int)(intptr_t)spraytarget;
  fakemodule[2] = (_DWORD)arrBase; /* module+8: item array base */
  dword_51A9B0 = (int)(intptr_t)fakemodule;

  /* spraytarget itself is zeroed, and v20 also aliases its address, so
   * *(v20+8) reads 0 -> v15 == 0 -> else branch (line 133203). */
  cov5_02_wcmih_prime((int)(intptr_t)spraytarget);
  TOUCH(Rules_WriteConstructModuleItemHeaderToCode(0, 0, 0, 0, 0));

  dword_51A9B0 = savedModule;
}

TEST(cov5_02_wcmih, v12_zero_v15_nonzero) {
  static _DWORD spraytarget2[8];
  static _DWORD fakemodule2[8];
  static _DWORD itemarrayslot2[4];
  static _DWORD itemstruct2[8];
  static _DWORD v15target[8];
  int arrBase;
  int savedModule = dword_51A9B0;

  memset(spraytarget2, 0, sizeof spraytarget2);
  memset(fakemodule2, 0, sizeof fakemodule2);
  memset(itemarrayslot2, 0, sizeof itemarrayslot2);
  memset(itemstruct2, 0, sizeof itemstruct2);
  memset(v15target, 0, sizeof v15target);

  itemstruct2[1] = 0; /* v8+4 -> v12 == 0 -> else branch (line 133198) */
  itemarrayslot2[0] = (_DWORD)(intptr_t)itemstruct2;

  arrBase = (int)(intptr_t)itemarrayslot2 - 4 * (int)(intptr_t)spraytarget2;
  fakemodule2[2] = (_DWORD)arrBase;
  dword_51A9B0 = (int)(intptr_t)fakemodule2;

  /* spraytarget2[2] (its own byte offset+8, read back as v20+8 == v15) is
   * set to point at a second real, zeroed struct -- so v15 is nonzero and
   * valid, and *(v15+12) reads a safe 0. */
  spraytarget2[2] = (_DWORD)(intptr_t)v15target;

  cov5_02_wcmih_prime((int)(intptr_t)spraytarget2);
  TOUCH(Rules_WriteConstructModuleItemHeaderToCode(0, 0, 0, 0, 0));

  dword_51A9B0 = savedModule;
}

/* =========================================================================
 * CRT_BeginThread (186453-186492, 8 uncovered): tests/unit/test_all.c stubs
 * CreateThread() to unconditionally return NULL ("pretend thread creation
 * failed"), which test_cov4_04.c's own note already documents makes line
 * 186483 (`WaitForSingleObject(...)` inside `if (Thread)`) provably
 * unreachable in this harness -- not attempted. The other 7 lines
 * (CreateEventA, the `v10 = &Thread` store, the CreateThread call itself,
 * the `if (Thread)` check, the `else` assignment, CloseHandle, and the
 * final return) are all plain reachable code with no decompiler-lost
 * locals involved; a single normal call exercises all of them. ========== */
TEST(cov5_02_crtbeginthread, normal_call_exercises_reachable_lines) {
  DWORD savedTls = dwTlsIndex;
  dwTlsIndex = 0xFFFFFFFFu; /* force the AllocateTlsIndex/InitializeThread... branch */
  TOUCH(CRT_BeginThread(0, 4096, 0));
  dwTlsIndex = savedTls;
}

/* =========================================================================
 * Rules_MathCoth (129831-129855, 7 uncovered): unlike most of this batch,
 * every local INSIDE Rules_MathCoth itself is a clean, properly-assigned
 * value -- no decompiler UB there. The gate is
 * `Rules_MathParseSingleArg(&v6, a3, a4)` actually succeeding, which itself
 * calls `Lexer_TokenExpect(1)` (own decompiler-lost mode-selector `v2`, only
 * a small {0,1,2} value gives an exact-count match) and THEN
 * `Lexer_ParseValueList(1, v5, 0, a3)` (own decompiler-lost `v7`, whose only
 * success path for a3==0/FLOAT is the `a3 == *(_DWORD*)(v7+4)` shortcut,
 * needing v7 to be a real POINTER). Empirically (verified with a private
 * scratch build of this exact harness, per this pass's instructions) these
 * two decompiler-lost reads alias the SAME stack slot from a single uniform
 * stack-spray call: priming with a small int (0/1/2) satisfies
 * Lexer_TokenExpect's `v2` but makes Lexer_ParseValueList's `v7`
 * dereference a near-null address and crash; priming with a real pointer
 * address avoids that crash but makes `v2` a large nonzero, non-{1,2}
 * value, which Lexer_TokenExpect's own cascade rejects as a count
 * mismatch before Lexer_ParseValueList is ever reached. No single spray
 * value threads both needles, so `Rules_MathParseSingleArg` cannot be
 * driven to success from this call site with the tools available in this
 * pass -- a real (documented) hard ceiling, not a probabilistic one. Kept
 * as a real one-node FLOAT argument chain (harmless, no regression) so the
 * attempt is on record and costs nothing; the three branches past the
 * `Rules_MathParseSingleArg` gate remain uncovered. ======================= */
static void cov5_02_mathcoth_install_float_arg(double value) {
  static _DWORD anchor[16];
  static _DWORD node[16];
  static _DWORD valnode[8];

  memset(anchor, 0, sizeof anchor);
  memset(node, 0, sizeof node);
  memset(valnode, 0, sizeof valnode);

  *(double *)&valnode[4] = value; /* offset+16 payload: the FLOAT value */
  *(short *)node = 0;             /* type tag 0 == FLOAT */
  *(_DWORD *)((char *)node + 2) = (_DWORD)(intptr_t)valnode;
  *(_DWORD *)((char *)node + 10) = 0; /* single-node chain */
  *(_DWORD *)((char *)anchor + 6) = (_DWORD)(intptr_t)node;

  dword_51A960 = (int)(intptr_t)anchor;
}

TEST(cov5_02_mathcoth, zero_argument_singularity) {
  static _DWORD lexprime[8];
  int saved = dword_51A960;
  memset(lexprime, 0, sizeof lexprime);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_mathcoth_install_float_arg(0.0);
  cov5_02_prime_int((int)(intptr_t)lexprime);
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0));
  dword_51A960 = saved;
}

TEST(cov5_02_mathcoth, normal_nonzero_argument) {
  static _DWORD lexprime[8];
  int saved = dword_51A960;
  memset(lexprime, 0, sizeof lexprime);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_mathcoth_install_float_arg(2.0);
  cov5_02_prime_int((int)(intptr_t)lexprime);
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0));
  dword_51A960 = saved;
}

TEST(cov5_02_mathcoth, near_zero_nonzero_argument_overflow) {
  static _DWORD lexprime[8];
  int saved = dword_51A960;
  memset(lexprime, 0, sizeof lexprime);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  cov5_02_mathcoth_install_float_arg(1.0e-30);
  cov5_02_prime_int((int)(intptr_t)lexprime);
  TOUCH(Rules_MathCoth(0, 0, 0, 0.0));
  dword_51A960 = saved;
}

/* =========================================================================
 * Deffunction_Delete (120369-120392, 6 uncovered): takes no arguments at
 * all -- both `v0` (the "!v0 -> ClearAll" selector) and `v2` (the unlink/free
 * target) are purely decompiler-lost register reads with nothing to seed
 * them from except the stack-spray trick. Priming with 0 drives the `!v0`
 * branch (Deffunction_ClearAll). Priming with the address of a real zeroed
 * buffer makes v0 nonzero (skip ClearAll) AND -- because
 * Deffunction_IsDeletable() is called as an immediate sibling from the same
 * frame and has an IDENTICAL "v0 possibly undefined" register read at its
 * own `*(v0+20)`/`*(v0+24)` checks -- gives it a real, safely-zeroed buffer
 * too, so `!Rules_IsBloaded() && !*(v0+20) && !*(v0+24)` is true (bloaded
 * defaults to 0), making Deffunction_IsDeletable() return true and driving
 * Deffunction_Delete into its Rules_UnlinkListNode/Deffunction_Free calls
 * (v2 aliasing the same sprayed buffer address). =========================== */
TEST(cov5_02_deffunctiondelete, primed_zero_clears_all) {
  cov5_02_prime_int(0);
  TOUCH(Deffunction_Delete());
}

TEST(cov5_02_deffunctiondelete, primed_real_buffer_deletable_path) {
  static _DWORD target[64];
  static _DWORD listhead[8];
  memset(target, 0, sizeof target);
  memset(listhead, 0, sizeof listhead);
  /* Rules_UnlinkListNode(v2) reads `*(_DWORD*)(*(_DWORD*)(v2+8)+4)` as the
   * list head to walk -- give it a real (fake) owning-list struct whose
   * head IS v2/target itself, so the unlink walk's loop terminates on its
   * very first check instead of chasing a null +4 offset. This banks
   * Rules_UnlinkListNode's OWN call-site line (120382) and
   * Deffunction_IsDeletable's success path (120379/380), but empirically
   * (private scratch build) still doesn't reach the Deffunction_Free call
   * site (120383/384): Deffunction_IsDeletable()'s own call between the
   * spray and this read appears to leave a different leftover in v2's
   * slot than what was sprayed, the same "intervening real call disrupts a
   * naive uniform spray" limit seen elsewhere in this pass. Kept as the
   * best partial result obtained. */
  target[2] = (_DWORD)(intptr_t)listhead; /* v1+8 */
  listhead[1] = (_DWORD)(intptr_t)target; /* list head == v1 itself */
  cov5_02_prime_int((int)(intptr_t)target);
  TOUCH(Deffunction_Delete());
}

/* =========================================================================
 * Defgeneric_GetMethodRestrictionsCommand (119794-119816, 5 uncovered): the
 * whole `if (...)` chain is gated by the SAME Lexer_ParseValueList "SYMBOL
 * success only via the decompiler-lost `a3 == *(v7+4)` shortcut" ceiling
 * documented above for Class_SlotExistPCommand. Two shapes:
 *   (1) a safe EMPTY argument chain (Rules_RtnUnknown's not-found fallback,
 *       same "funcrec/symnode" safety-net recipe used throughout this
 *       project's tests) drives `dword_51A964` nonzero inside
 *       Lexer_ParseValueList *before* it ever reaches the v7 dereference,
 *       so the whole `&&` chain fails cleanly at the very first term --
 *       landing on the untouched `else` (line 119811) without needing any
 *       v7 priming at all.
 *   (2) priming v7 (so the SYMBOL(2) request succeeds) plus a real one-node
 *       SYMBOL argument reaches `v5 = Defgeneric_CheckGenericExists(...)`
 *       (line 119803) for real -- new coverage regardless of what
 *       Defgeneric_CheckGenericExists itself does deep inside
 *       Defgeneric_LookupWithImports (registering dword_54E6A0 with a
 *       harmless zeroed buffer avoids an immediate NULL-deref there, so it
 *       has a chance to return cleanly rather than fault a frame down).
 * ========================================================================= */
TEST(cov5_02_defgenericgetmethodrestrictions, empty_chain_else_branch) {
  static unsigned char argnode[256];
  static _DWORD funcrec[8], symnode[8];
  static _DWORD out[16];
  int saved960 = dword_51A960;
  int saved964 = dword_51A964;

  memset(argnode, 0, 256);
  memset(funcrec, 0, sizeof funcrec);
  memset(symnode, 0, sizeof symnode);
  memset(out, 0, sizeof out);
  funcrec[0] = (_DWORD)(intptr_t)symnode;
  *(_DWORD *)(argnode + 2) = (_DWORD)(intptr_t)funcrec;
  dword_51A960 = (int)(intptr_t)argnode; /* empty chain: offset+6 left 0 */

  dword_51A964 = 0;
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(out, 0, 0.0));

  dword_51A960 = saved960;
  dword_51A964 = saved964;
}

TEST(cov5_02_defgenericgetmethodrestrictions, primed_symbol_reaches_checkgeneric) {
  static unsigned char argnode[32], node[32];
  static _DWORD val[8];
  static _DWORD lexprime[8];
  static _DWORD out[16];
  int saved960 = dword_51A960;
  int saved964 = dword_51A964;
  int saved54E6A0 = dword_54E6A0;
  static _DWORD safeModuleItem[8];

  memset(argnode, 0, 32);
  memset(node, 0, 32);
  memset(val, 0, sizeof val);
  memset(lexprime, 0, sizeof lexprime);
  memset(out, 0, sizeof out);
  memset(safeModuleItem, 0, sizeof safeModuleItem);

  val[4] = (_DWORD)(intptr_t)"Cov5_02FakeGeneric";
  lexprime[1] = 2; /* SYMBOL(2) shortcut for Lexer_ParseValueList's v7 check */

  *(short *)(node + 0) = 2; /* SYMBOL */
  *(_DWORD *)(node + 2) = (_DWORD)(intptr_t)val;
  *(_DWORD *)(node + 10) = 0;
  *(_DWORD *)(argnode + 6) = (_DWORD)(intptr_t)node;
  dword_51A960 = (int)(intptr_t)argnode;

  /* avoid an immediate NULL-deref inside Symbol_LookupInModule's `*a1` read
   * (dword_54E6A0 defaults to 0/unregistered); a harmless zeroed "module
   * name" record lets it fail to find anything cleanly instead. */
  dword_54E6A0 = (int)(intptr_t)safeModuleItem;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  dword_51A964 = 0;
  cov5_02_prime_int((int)(intptr_t)lexprime);
  TOUCH(Defgeneric_GetMethodRestrictionsCommand(out, 0, 0.0));

  dword_51A960 = saved960;
  dword_51A964 = saved964;
  dword_54E6A0 = saved54E6A0;
}
