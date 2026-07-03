/* cov3 batch 07: third-pass coverage lift for a grab-bag of partially
 * covered functions (see scratchpad/cov3_batches/cov3_07.json). Each test
 * was designed by reading the actual current build-cov gcov annotations for
 * clash95.c (not just the stale batch JSON) to target the exact still-
 * uncovered lines/branches. Anything that funnels through a genuinely
 * uninitialized decompiler-lost register ("possibly undefined" per
 * clash95.c's own annotations) uses TOUCH only, since the branch actually
 * taken there cannot be predicted from static reading alone; crashes from
 * those are expected and isolated by the per-test fork + alarm(8)
 * watchdog. */

/* =======================================================================
 * UnitStack_HasPeasantCargo: a1 is a pointer to a linear array of 31-byte
 * unit-stack-slot records; offset+6 (int16) holds the slot's unit type.
 * -1 means "end of stack" (immediate return 0); UNIT_TYPE_PEASANT_CARGO
 * (32) means "found" (return 1, breaking the loop); otherwise it walks up
 * to 10 slots before giving up (return 0 via the v1>=10 counter check).
 * Three shapes below hit all three return points and the loop-increment
 * lines in between. ========================================================= */

TEST(cov3_07_unitstack, peasant_cargo_immediate_end_marker) {
  static unsigned char slots[11 * 31];
  memset(slots, 0, sizeof(slots));
  *(__int16 *)(slots + 6) = -1;
  CHECK_EQ(UnitStack_HasPeasantCargo((int)(intptr_t)slots), 0);
}

TEST(cov3_07_unitstack, peasant_cargo_found_after_a_few_slots) {
  static unsigned char slots[11 * 31];
  int i;
  memset(slots, 0, sizeof(slots));
  for (i = 0; i < 3; ++i) {
    *(__int16 *)(slots + i * 31 + 6) = 7; /* some other, non-matching type */
  }
  *(__int16 *)(slots + 3 * 31 + 6) = UNIT_TYPE_PEASANT_CARGO;
  CHECK_EQ(UnitStack_HasPeasantCargo((int)(intptr_t)slots), 1);
}

TEST(cov3_07_unitstack, peasant_cargo_walks_off_after_ten_slots) {
  static unsigned char slots[11 * 31];
  int i;
  memset(slots, 0, sizeof(slots));
  for (i = 0; i < 10; ++i) {
    *(__int16 *)(slots + i * 31 + 6) = 7; /* never -1, never the target type */
  }
  CHECK_EQ(UnitStack_HasPeasantCargo((int)(intptr_t)slots), 0);
}

/* =======================================================================
 * MessageHandler_UndefineForClassOrAll: cov2_04 already drives a1==NULL
 * (both a2==NULL and a2-present) and a1-present+a2-present combinations.
 * The one shape it doesn't cover is a1-present with a2==NULL, which forces
 * the Str_Intern(a3) branch on a *class-present* call (a1!=0), a
 * genuinely different code path through the function than any of its
 * NULL-a1 variants (those hit the Str_Intern call too, but then take the
 * Class_GetNextRecord enumeration branch instead of the direct
 * MessageHandler_RemoveByNameAndType(a1,...) branch). ======================= */
TEST(cov3_07_msghandler, undefine_a1_present_a2_null) {
  static _DWORD cls[256];
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  memset(cls, 0, sizeof cls);
  TOUCH(MessageHandler_UndefineForClassOrAll(cls, 0,
                                              (int)(intptr_t)"cov3_07_undef",
                                              0));
}

/* =======================================================================
 * Rules_LoadStarCommand: needs Lexer_TokenExpect(1) to succeed (arg-count
 * chain length == 1) before Rules_GetFileNameArg gets a chance to run.
 * Rules_GetFileNameArg calls Rules_RtnUnknown *directly* (not through the
 * "buggy" Lexer_ParseValueList indirection that depends on an undefined
 * register elsewhere in this file), so its tag==2/3 success check is fully
 * controllable via the single-argument-chain trick below (same technique
 * documented in tests/unit/cases/test_cov2_02.c / test_cov2_04.c). Once
 * Rules_GetFileNameArg hands back a real, valid (but nonexistent-on-disk)
 * filename, Rules_Load's IO_FOpen() call fails cleanly (unlike a bogus
 * 1-valued "pointer", which would crash trying to read a string at address
 * 1), so this reaches the real "open failed" -> Rules_OpenFileErrorMessage
 * -> return 0 path deterministically. ==================================== */
static void cov3_07_arg1(unsigned char *anchor, unsigned char *node,
                          short tag, void *valptr) {
  memset(anchor, 0, 32);
  memset(node, 0, 32);
  *(short *)node = tag;
  *(int *)(node + 2) = (int)(intptr_t)valptr;
  *(int *)(node + 10) = 0;
  *(int *)(anchor + 6) = (int)(intptr_t)node;
  dword_51A960 = (int)(intptr_t)anchor;
}

TEST(cov3_07_rulesload, filename_open_fails_cleanly) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov3_07_missing_star_file.bin";
  int saved = dword_51A960;
  valnode[4] = (int)(intptr_t)path; /* offset+16 payload slot */
  cov3_07_arg1(anchor, node, 3, valnode);
  CHECK_EQ(Rules_LoadStarCommand(0, 0.0), 0);
  dword_51A960 = saved;
}

/* Rules_HostRemoveFile has the exact same Lexer_TokenExpect(1) +
 * Rules_GetFileNameArg shape, forwarding a resolved filename into
 * Rules_BloadDeleteFile instead of Rules_Load; drive it with a real (but
 * nonexistent) path too so any failure inside Rules_BloadDeleteFile is a
 * clean "not found" rather than a crash on a bogus pointer. */
TEST(cov3_07_hostremovefile, filename_resolves_to_real_string) {
  static unsigned char anchor[32], node[32];
  static _DWORD valnode[8];
  static const char *path = "/nonexistent/cov3_07_missing_bload_file.bin";
  int saved = dword_51A960;
  valnode[4] = (int)(intptr_t)path;
  cov3_07_arg1(anchor, node, 3, valnode);
  TOUCH(Rules_HostRemoveFile(0.0));
  dword_51A960 = saved;
}

/* =======================================================================
 * Rules_PatchDeftemplateSlotModuleRef: Module_BeginEnum/EndEnum need the
 * dword_54DBA8 reserve arena (Mem_InitReserveBlock bootstrap, same
 * convention as other Rules_* enum-driving tests). Module_NextEnum(0)
 * reads dword_51A9AC directly, so pointing that at a single zeroed fake
 * "module" record (next-module link at +28 == 0, construct-list head at
 * +8 == 0) drives exactly one trip around the while(1) loop: Enum is
 * non-NULL (skips the immediate empty-enum return), Rules_GetNextDeftemplate
 * (via Class_Enum -> Module_GetItem) safely returns 0 for our all-zero
 * module record, so it falls to LABEL_5, Module_NextEnum(Enum) reads our
 * zeroed +28 link (0), and the function returns via Module_EndEnum(). This
 * reaches every line up through the first loop iteration; the nested
 * "while (v5 != ...)" deftemplate-walk loop needs a *real* registered
 * deftemplate list, which requires full engine/parser bring-up outside the
 * scope of this batch. ==================================================== */
TEST(cov3_07_rulespatch, module_enum_one_trip_then_end) {
  static _DWORD fakeModule[16];
  int savedNextEnum = dword_51A9AC;
  Mem_InitReserveBlock(0, 0);
  memset(fakeModule, 0, sizeof fakeModule);
  dword_51A9AC = (int)(intptr_t)fakeModule;
  TOUCH(Rules_PatchDeftemplateSlotModuleRef(0, 42));
  dword_51A9AC = savedNextEnum;
}

/* =======================================================================
 * Rules_MathCsch: the guard (!Rules_MathParseSingleArg(...)) is already
 * covered by the "parse fails" shape used throughout test_cov17.c. Reaching
 * its post-parse branches requires Rules_MathParseSingleArg's own
 * Lexer_ParseValueList() call to report "success", but that routes through
 * a tag-match check keyed off a genuinely undefined register ('v7' in
 * Lexer_ParseValueList) rather than anything this test can set -- the same
 * conclusion test_cov17.c's math-builtin battery already documents. Call it
 * a few more times from a fresh site (varying preceding stack contents) in
 * case that leftover garbage differs here and happens to take the
 * success path; TOUCH-only since the outcome is unpredictable. ============ */
TEST(cov3_07_rulesmath, csch_retry_for_leftover_register_luck) {
  static unsigned char argnode[256];
  char pad[256]; /* perturb stack contents between calls */
  int i;
  int saved = dword_51A960;
  memset(argnode, 0, sizeof argnode);
  dword_51A960 = (int)(intptr_t)argnode;
  for (i = 0; i < 4; ++i) {
    memset(pad, i, (size_t)(37 + i * 11));
    TOUCH(Rules_MathCsch(0, 0, 0, 0.0));
  }
  dword_51A960 = saved;
}

/* =======================================================================
 * Building_ApplySiegeDamageToWallSections: a2 must be >= 300 so a2/100 (3)
 * is strictly greater than 2, forcing the `v5 = 2` cap line. Giving every
 * wall-section health byte a small value (3, well under
 * Rng_RandRange(10,25)'s minimum of 10) makes the repair block's inner
 * do/while exit on its very first draw (no infinite-loop hazard from the
 * uninitialized 'v7' comparison) *and* deterministically satisfies
 * `result > v11`, reaching the `v9 = v11` clamp line too. One call this
 * shape walks every previously-uncovered line in the function. ============ */
TEST(cov3_07_building, siege_damage_cap_and_clamp_branches) {
  static unsigned char wall[512];
  memset(wall, 0, sizeof(wall));
  memset(wall + 422, 3, 7);
  TOUCH(Building_ApplySiegeDamageToWallSections((int)(intptr_t)wall, 350));
}

/* =======================================================================
 * MainMenu_RequestCampaignMenu: a plain never-called-in-pass-one wrapper
 * around UIWidget_PlayPressedReleaseAnimation plus two global writes.
 * UIWidget_PlayPressedReleaseAnimation reads widget offset 49 (skip
 * Audio_PlayButtonSound when zero) then keeps UIWidget_RefreshActionButtonState
 * on its safe "offset0 >= 640" early-return branch -- the exact proven-safe
 * widget shape test_cov2_04.c's MainMenu_RequestMultiplayerMenu test already
 * established for this same family of wrappers. ========================== */
TEST(cov3_07_mainmenu, request_campaign_menu) {
  static unsigned char widget[128];
  memset(widget, 0, sizeof widget);
  *(_DWORD *)(widget + 0) = 1000;
  *(_DWORD *)(widget + 49) = 0;
  TOUCH(MainMenu_RequestCampaignMenu((uintptr_t)(intptr_t)widget));
  CHECK_EQ(g_MainMenuRequestedScreen, MAIN_MENU_REQUEST_CAMPAIGN);
  CHECK_EQ(g_PlayGameMenuExitRequested, 1);
}

/* =======================================================================
 * Definstances_DeleteRecord: Rules_IsBloaded() reads the plain global
 * dword_51A1AC directly, so forcing it nonzero drives the immediate
 * "return 0" branch deterministically (previously uncovered). The
 * remaining branches ("if (!v0) return Definstances_RemoveAll();" and the
 * IsDeletable()/UnlinkListNode/FreeRecord tail) all key off registers the
 * decompiler lost entirely (no parameters exist to steer them), so those
 * are only reachable by chance; call the not-bloaded shape a few times
 * from varied stack contexts too, TOUCH-only, in case leftover garbage
 * happens to land favorably. ============================================= */
TEST(cov3_07_definstances, delete_record_bloaded_short_circuit) {
  int saved = dword_51A1AC;
  dword_51A1AC = 1;
  CHECK_EQ(Definstances_DeleteRecord(), 0);
  dword_51A1AC = saved;
}

TEST(cov3_07_definstances, delete_record_not_bloaded_retry_for_luck) {
  char pad[128];
  int saved = dword_51A1AC;
  int i;
  dword_51A1AC = 0;
  for (i = 0; i < 4; ++i) {
    memset(pad, i + 1, (size_t)(29 + i * 13));
    TOUCH(Definstances_DeleteRecord());
  }
  dword_51A1AC = saved;
}

/* =======================================================================
 * Method_PrintWatchStatusLine: the first three Output_Write/format calls
 * are already covered; the remainder (the fourth Output_Write plus the
 * Defgeneric_GetMethodTraceFlag branch) were simply never reached because
 * pass one's Output_Write's own 4th-arg register happens to blow up. Drive
 * it with a1 == 0 (the default "no router" Output_Write short-circuit used
 * throughout this codebase's other Output_Write-adjacent tests) so those
 * calls return harmlessly instead of touching real router state, letting
 * control fall through to the trace-flag branch. Defgeneric_GetMethodTraceFlag
 * itself dereferences a genuinely undefined register ('v3'), so the branch
 * actually taken (and whether it crashes first) can't be predicted --
 * TOUCH only. ============================================================= */
TEST(cov3_07_method, print_watch_status_line_a1_zero_router) {
  TOUCH(Method_PrintWatchStatusLine(0, 0, 0));
}

/* =======================================================================
 * CRT_RemoveUnhandledExceptionFilter: g_CrtThreadDataAccessor defaults to
 * &CRT_GetBootstrapThreadData, whose compat stub returns
 * __PAIR64__(a2, lpTlsValue) -- on this 32-bit-modeled build only the low
 * word (lpTlsValue) survives the `+ 84` pointer arithmetic, so a1/a2 never
 * matter, but `lpTlsValue` itself is a plain writable global. Pointing it
 * at a real static buffer whose +84 offset holds a valid self-pointer lets
 * both `*v2` (via the harmless __writefsdword stub, a true no-op) and the
 * final `*(result + 84) = 0` write land in mapped memory, reaching every
 * previously-uncovered line in the function safely and deterministically.
 * ========================================================================= */
TEST(cov3_07_crt, remove_unhandled_exception_filter_populated_tls) {
  static unsigned char tlsBlock[128];
  void *savedTls = lpTlsValue;
  memset(tlsBlock, 0, sizeof tlsBlock);
  *(void **)(tlsBlock + 84) = tlsBlock; /* *v2 reads back into the same block */
  lpTlsValue = tlsBlock;
  TOUCH(CRT_RemoveUnhandledExceptionFilter(0, 0));
  lpTlsValue = savedTls;
}

/* =======================================================================
 * Rules_LogTreasureFact: both of its executable lines are already fully
 * covered by earlier passes (sprintf_ + Rules_Log). One more call from a
 * fresh site with different argument values costs nothing and keeps this
 * batch's function list complete. ======================================== */
TEST(cov3_07_ruleslog, log_treasure_fact_again) {
  TOUCH(Rules_LogTreasureFact(3, 7));
}

/* =======================================================================
 * Lexer_TokenExpect: `if (!v2)` / `if (v2 == 1)` / the trailing "v2==2"
 * path all key off a genuinely undefined register ('v2') that pass one's
 * many indirect callers already happened to exercise two of the three
 * branches for. Call it directly several more times with varied `a1` and
 * varied preceding stack contents in case the leftover garbage lands on
 * the still-missing shapes (v2==1 with result<a1, or v2==2 with
 * result<=a1 falling through to the final `return result`). TOUCH-only:
 * outcome is unpredictable by construction. ============================== */
TEST(cov3_07_lexer, token_expect_retry_for_leftover_register_luck) {
  char pad[256];
  int i;
  for (i = 0; i < 6; ++i) {
    memset(pad, i + 3, (size_t)(19 + i * 17));
    TOUCH(Lexer_TokenExpect(i));
  }
}

/* =======================================================================
 * Deffunction_CloseCodeFiles / Compiler_CloseDefinstancesCodeFiles: the
 * still-missing lines in both (the "if (!a1) return result;"/"goto
 * LABEL_5" fallthrough reached only when the *first* branch's nested
 * Rules_ConstructCodeFileClose call actually returns) require that nested
 * call not to crash. That call ends by forwarding our plain int "handle"
 * straight into CRT_VfprintfLockedWrite as if it were a real FILE*;
 * test_cov09.c already established that even a fully zeroed, properly
 * *aligned* fake-stream buffer isn't enough (the real CRT struct's
 * callback/lock fields aren't zero-safe), so this reliably faults inside
 * that callee before returning, regardless of whether the "handle" is a
 * bare small int or a real backing buffer's address. Try the backing-buffer
 * shape anyway (in case some other call shape avoids the fault this time)
 * -- TOUCH-only, isolated in its own TEST per call so one crash can't
 * suppress the other function's attempt. ================================= */
TEST(cov3_07_deffunction, close_code_files_backing_buffer_handle) {
  static _DWORD fakeHandle[64];
  memset(fakeHandle, 0, sizeof fakeHandle);
  TOUCH(Deffunction_CloseCodeFiles(0, (int)(intptr_t)fakeHandle, 5, 0));
}

TEST(cov3_07_compiler, close_definstances_code_files_backing_buffer_handle) {
  static _DWORD fakeHandle[64];
  memset(fakeHandle, 0, sizeof fakeHandle);
  TOUCH(Compiler_CloseDefinstancesCodeFiles(0, (int)(intptr_t)fakeHandle, 5, 0));
}

/* =======================================================================
 * Parser_ParseInstanceQueryNoAction: a deep recursive-descent parser chain
 * (Parser_ParseInstanceQueryRestrictions -> Parser_NextToken over the real
 * lexer token stream rooted at whatever router `a1` names). Reaching its
 * "restrictions parsed successfully" branch requires the live lexer/token
 * buffer to actually yield token type 100 twice in a row, which isn't
 * controllable from a static a1/a2 buffer without standing up a real
 * input router -- test_cov23.c already reached this same conclusion for
 * this exact function. Call it a couple more times with varied a2 anyway;
 * TOUCH-only, isolated so a crash deep in the lexer can't suppress
 * anything else in this file. ============================================ */
TEST(cov3_07_parser, parse_instance_query_no_action_variant_a2) {
  static unsigned char a1buf[256];
  memset(a1buf, 0, sizeof(a1buf));
  TOUCH(Parser_ParseInstanceQueryNoAction((int)(intptr_t)a1buf, 1));
}

TEST(cov3_07_parser, parse_instance_query_no_action_nonzero_a1_tail) {
  static unsigned char a1buf[256];
  memset(a1buf, 0, sizeof(a1buf));
  *(int *)(a1buf + 6) = (int)(intptr_t)a1buf; /* a1+6 deref'd on the success tail */
  TOUCH(Parser_ParseInstanceQueryNoAction((int)(intptr_t)a1buf, 0));
}
