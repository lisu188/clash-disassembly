/* cov19 cluster: Rules_Register{InstanceIO,MultifieldSlot} command tables,
 * MessageHandler build/send/preview/marker helpers, Class watch/module/busy
 * accessors, Rules_RetractObjectPatternMatches, Rules_ValueSatisfiesRange-
 * Constraint, IO_ScanfDigitValue, CRT window/exception/file-mode helpers
 * (see cov_batches/cov_19.json). Buffers that get their address stored into
 * a recovered `_DWORD` field (later reread as a pointer) are declared
 * `static` so the address survives 32-bit round-tripping on this 64-bit,
 * non-PIE build (same trick used by cov13/cov17). NOTE: CRT_HasActiveWindow
 * is intentionally NOT exercised -- it calls LoadLibraryA/GetProcAddress,
 * which have no definition anywhere in this project (only declared, one
 * commented out) and are normally dead-stripped; calling it here pulls in
 * two undefined externs and breaks the *whole* coverage binary's link. */

/* ---- Rules_RegisterInstanceIOCommands / Rules_RegisterMultifieldSlotCommands:
 * chains of Rules_RegisterHostFunction calls. That allocates host-function
 * nodes from the dword_54DBA8 reserve-block arena and interns a symbol via
 * Str_Intern() into the dword_54DD50 atom tables -- both zero/NULL until
 * carved out by Mem_InitReserveBlock()/Rules_InitAtomTables(), exactly the
 * setup cov13/cov17 use for the same reason. */
TEST(cov19_reg, register_instance_io_commands) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterInstanceIOCommands());
}

TEST(cov19_reg, register_multifield_slot_commands) {
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(Rules_RegisterMultifieldSlotCommands());
}

/* ---- Rules_BloadBuildSlotValue ----
 * a4==0: single-value ephemeral-multifield path (fully safe once the arena
 * is initialized).
 * a4==1: atom path; a2[0] is fed straight into Rules_BloadLookupAtomByIndex's
 * switch as the "type" tag -- pick 5 (the `result = 0;` case) so it returns
 * immediately without touching any of the dword_54E67x atom tables.
 * a4>=2: multi-value path. Its `v7`/`v12` locals are genuine decompiler
 * "possibly undefined" artifacts (clash95.c comments at 4AD4D5/4AD4FE) with
 * no way to seed them from our arguments, so the loop body's first read
 * reliably segfaults; the setup lines (a1[1..4] assignments, ephemeral
 * multifield alloc, v8/v9/v10 arithmetic) still execute first. */
TEST(cov19_bload, build_slot_value_single) {
  static _DWORD obj[128];
  static _DWORD atomArg[8];
  memset(obj, 0, sizeof obj);
  memset(atomArg, 0, sizeof atomArg);
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_BloadBuildSlotValue(obj, atomArg, 0, 0));
}

TEST(cov19_bload, build_slot_value_atom) {
  static _DWORD obj[128];
  static _DWORD atomArg[8];
  memset(obj, 0, sizeof obj);
  memset(atomArg, 0, sizeof atomArg);
  atomArg[0] = 5; /* Rules_BloadLookupAtomByIndex: case 5 -> result = 0 */
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_BloadBuildSlotValue(obj, atomArg, 0, 1));
}

TEST(cov19_bload, build_slot_value_multi) {
  static _DWORD obj[128];
  static _DWORD atomArg[8];
  memset(obj, 0, sizeof obj);
  memset(atomArg, 0, sizeof atomArg);
  Mem_InitReserveBlock(0, 0);
  TOUCH(Rules_BloadBuildSlotValue(obj, atomArg, 0, 2));
}

/* ---- MessageHandler_AnyHandlerBusy ----
 * a1+96 = handler count (word-checked as _DWORD), a1+88 = head of a 36-byte-
 * stride node array whose +4 field is the "busy" bit; walks until a node
 * with +4 != 0 (busy -> return 1) or the count is exhausted (return 0). */
TEST(cov19_msg, any_handler_busy_zero_count) {
  static _DWORD a1[32];
  memset(a1, 0, sizeof a1);
  /* offset 96 = count = 0 -> short-circuit return 0, node array untouched */
  CHECK_EQ(MessageHandler_AnyHandlerBusy((int)(intptr_t)a1), 0);
}

TEST(cov19_msg, any_handler_busy_immediately_busy) {
  static _DWORD a1[32];
  static unsigned char nodes[2][36];
  memset(a1, 0, sizeof a1);
  memset(nodes, 0, sizeof nodes);
  *(_DWORD *)((char *)nodes[0] + 4) = 1; /* first node already busy */
  *(_DWORD *)((char *)a1 + 88) = (_DWORD)(intptr_t)nodes;
  *(_DWORD *)((char *)a1 + 96) = 1;
  CHECK_EQ(MessageHandler_AnyHandlerBusy((int)(intptr_t)a1), 1);
}

TEST(cov19_msg, any_handler_busy_walks_then_busy) {
  static _DWORD a1[32];
  static unsigned char nodes[2][36];
  memset(a1, 0, sizeof a1);
  memset(nodes, 0, sizeof nodes);
  /* node0 not busy, node1 busy -> loop advances once then exits busy */
  *(_DWORD *)((char *)nodes[1] + 4) = 1;
  *(_DWORD *)((char *)a1 + 88) = (_DWORD)(intptr_t)nodes;
  *(_DWORD *)((char *)a1 + 96) = 2;
  CHECK_EQ(MessageHandler_AnyHandlerBusy((int)(intptr_t)a1), 1);
}

TEST(cov19_msg, any_handler_busy_walks_then_free) {
  static _DWORD a1[32];
  static unsigned char nodes[1][36];
  memset(a1, 0, sizeof a1);
  memset(nodes, 0, sizeof nodes);
  /* single node, never busy, count reached -> return 0 from inside loop */
  *(_DWORD *)((char *)a1 + 88) = (_DWORD)(intptr_t)nodes;
  *(_DWORD *)((char *)a1 + 96) = 1;
  CHECK_EQ(MessageHandler_AnyHandlerBusy((int)(intptr_t)a1), 0);
}

/* ---- MessageHandler_BuildPreviewHandlerCore / BuildSendHandlerCore ----
 * Both walk a1+46 (word count) over an array of class pointers at a1+48,
 * calling MessageHandler_CollectClassHandlersIntoCore(classPtr, ...) per
 * class. Each classPtr's offset 96 (its own [24]) is left 0 so
 * Class_FindMessageHandlerNameGroup() returns -1 immediately -- safe, no
 * handler-table traversal. Afterward both always call
 * MessageHandler_JoinHandlerLinks() with an all-zero head array, which
 * (per its own else-branch reading truly uninitialized locals) reliably
 * segfaults -- but that crash is inside a non-batch function reached only
 * after every line of *our* two functions has already executed. */
TEST(cov19_msg, build_preview_handler_core_no_classes) {
  static _DWORD host[64];
  memset(host, 0, sizeof host);
  *(unsigned short *)((char *)host + 46) = 0;
  TOUCH(MessageHandler_BuildPreviewHandlerCore((int)(intptr_t)host, 7));
}

TEST(cov19_msg, build_preview_handler_core_two_classes) {
  static _DWORD host[64];
  static _DWORD classArr[4];
  static _DWORD classStruct[64];
  memset(host, 0, sizeof host);
  memset(classArr, 0, sizeof classArr);
  memset(classStruct, 0, sizeof classStruct);
  classArr[0] = (_DWORD)(intptr_t)classStruct;
  classArr[1] = (_DWORD)(intptr_t)classStruct;
  *(unsigned short *)((char *)host + 46) = 2;
  *(_DWORD *)((char *)host + 48) = (_DWORD)(intptr_t)classArr;
  TOUCH(MessageHandler_BuildPreviewHandlerCore((int)(intptr_t)host, 7));
}

TEST(cov19_msg, build_send_handler_core_no_classes) {
  static _DWORD host[64];
  memset(host, 0, sizeof host);
  *(unsigned short *)((char *)host + 46) = 0;
  TOUCH(MessageHandler_BuildSendHandlerCore((int)(intptr_t)host, 9));
}

TEST(cov19_msg, build_send_handler_core_two_classes) {
  static _DWORD host[64];
  static _DWORD classArr[4];
  static _DWORD classStruct[64];
  memset(host, 0, sizeof host);
  memset(classArr, 0, sizeof classArr);
  memset(classStruct, 0, sizeof classStruct);
  classArr[0] = (_DWORD)(intptr_t)classStruct;
  classArr[1] = (_DWORD)(intptr_t)classStruct;
  *(unsigned short *)((char *)host + 46) = 2;
  *(_DWORD *)((char *)host + 48) = (_DWORD)(intptr_t)classArr;
  TOUCH(MessageHandler_BuildSendHandlerCore((int)(intptr_t)host, 9));
}

/* ---- MessageHandler_PrintIndentedHandlerMarker ----
 * a4 MUST be 0: the recovered `for` loop's "increment" clause is an
 * Output_Write() call rather than `++i` (a genuine decompiler information
 * loss, not something our inputs can fix), so any a4 > 0 spins forever.
 * a1 must be a real NUL-terminated string: with no CLIPS routers
 * registered, Output_Write() always falls through to
 * `strcmp_(off_51A614[0], a1)`, which dereferences a1 as a string
 * unconditionally. a2 must point at a handler record whose [2] slot (byte
 * +8) is a valid pointer (read at +16 by MessageHandler_PrintNameTypeAndClass)
 * -- everything past that first Output_Write inside PrintNameTypeAndClass
 * uses genuinely undefined locals and crashes in Class_PrintName, which is
 * outside this batch and reached only after our own function's every line
 * has run. */
TEST(cov19_msg, print_indented_handler_marker) {
  static char logical_name[16];
  static _DWORD classA[32];
  static _DWORD handlerRec[8];
  static _DWORD handlerPtr[1];
  strcpy(logical_name, "clips");
  memset(classA, 0, sizeof classA);
  memset(handlerRec, 0, sizeof handlerRec);
  handlerRec[2] = (_DWORD)(intptr_t)classA; /* a2[2]: readable at +16 */
  handlerPtr[0] = (_DWORD)(intptr_t)handlerRec;
  TOUCH(MessageHandler_PrintIndentedHandlerMarker(
      (int)(intptr_t)logical_name, (int *)handlerPtr, 0, 0));
}

/* ---- MessageHandler_SendToInstanceAddress ----
 * a1 flows into MessageHandler_Send as its a3, dereferenced at +16 -- back
 * it with a zeroed static buffer. a3 becomes the "next" field AST_CountList-
 * Nodes walks (at +10 of the built message expression); keep it 0 so that
 * walk terminates after one node instead of chasing a bogus address.
 * Exercised with both a NULL and a non-NULL result pointer to hit both
 * sides of the `if (!result_buffer)` branch. */
TEST(cov19_msg, send_to_instance_address_null_result) {
  static _DWORD a1[64];
  memset(a1, 0, sizeof a1);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(MessageHandler_SendToInstanceAddress(
      (int)(intptr_t)a1, 1, 0, (int *)0, 0.0));
}

TEST(cov19_msg, send_to_instance_address_with_result) {
  static _DWORD a1[64];
  static _DWORD resultBuf[8];
  memset(a1, 0, sizeof a1);
  memset(resultBuf, 0, sizeof resultBuf);
  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  TOUCH(MessageHandler_SendToInstanceAddress(
      (int)(intptr_t)a1, 1, 0, (int *)resultBuf, 0.0));
}

/* ---- Class_IsDeletableAlt ----
 * Its `v0` local is a genuine decompiler artifact (comment: "possibly
 * undefined") with no argument to seed it from; whatever garbage is on the
 * stack decides whether it calls Class_DeleteRecursive(garbage) or
 * Class_RemoveAllDeletableClasses(). Called for whatever coverage the
 * entry/Rules_IsBloaded() check yields; crash isolation covers the rest. */
TEST(cov19_class, is_deletable_alt) {
  TOUCH(Class_IsDeletableAlt());
}

/* ---- Class_GetWatchInstances / Class_SetWatchInstances ---- */
TEST(cov19_class, get_watch_instances_both_ways) {
  static _DWORD buf[16];
  memset(buf, 0, sizeof buf);
  *(_DWORD *)((char *)buf + 20) = 0;
  TOUCH(Class_GetWatchInstances((int)(intptr_t)buf));
  *(_DWORD *)((char *)buf + 20) = 0x10;
  TOUCH(Class_GetWatchInstances((int)(intptr_t)buf));
}

TEST(cov19_class, set_watch_instances_both_branches) {
  static _DWORD buf[16];
  memset(buf, 0, sizeof buf);
  /* bit2 (0x4) clear -> body runs, sets/clears bit4 (0x10) from result&1 */
  TOUCH(Class_SetWatchInstances(1, (int)(intptr_t)buf));
  TOUCH(Class_SetWatchInstances(0, (int)(intptr_t)buf));
  /* bit2 set -> guarded body skipped */
  *(_BYTE *)((char *)buf + 20) = 4;
  TOUCH(Class_SetWatchInstances(1, (int)(intptr_t)buf));
}

/* ---- Class_GetWatchSlots / Class_SetWatchSlots ---- */
TEST(cov19_class, get_watch_slots_both_ways) {
  static _DWORD buf[16];
  memset(buf, 0, sizeof buf);
  *(_DWORD *)((char *)buf + 20) = 0;
  TOUCH(Class_GetWatchSlots((int)(intptr_t)buf));
  *(_DWORD *)((char *)buf + 20) = 0x20;
  TOUCH(Class_GetWatchSlots((int)(intptr_t)buf));
}

TEST(cov19_class, set_watch_slots) {
  static _DWORD buf[16];
  memset(buf, 0, sizeof buf);
  TOUCH(Class_SetWatchSlots(1, (int)(intptr_t)buf));
  TOUCH(Class_SetWatchSlots(0, (int)(intptr_t)buf));
}

/* ---- Class_PrintModuleList ----
 * offset+4 must be a real NUL-terminated string (Rules_GetModuleConstructList
 * Head() just returns it, and Output_WriteLongString() strlen()s it). offset
 * +88 = 0 makes the first MessageHandler_EnumNext(a1,0) call return 0, so the
 * `for` loop that follows -- whose own `v9` argument to the second EnumNext
 * call is a genuine decompiler-undefined local -- is skipped. Even so,
 * Output_WriteLongString() ends by calling Output_Write() with this
 * function's own uninitialized `v3`/`v2` as the router name, which reliably
 * segfaults inside that (non-batch) helper after our own lines up through
 * that call have executed. */
TEST(cov19_class, print_module_list) {
  static char modName[16];
  static _DWORD buf[32];
  strcpy(modName, "TestMod");
  memset(buf, 0, sizeof buf);
  *(_DWORD *)((char *)buf + 4) = (_DWORD)(intptr_t)modName;
  *(_DWORD *)((char *)buf + 88) = 0;
  TOUCH(Class_PrintModuleList((int)(intptr_t)buf));
}

TEST(cov19_class, print_module_list_no_head) {
  static _DWORD buf[32];
  memset(buf, 0, sizeof buf);
  /* offset+4 = 0 -> Rules_GetModuleConstructListHead returns 0, whole body
   * skipped, safe return with no nested calls at all. */
  CHECK_EQ(Class_PrintModuleList((int)(intptr_t)buf), 0);
}

/* ---- Class_AddBusyReference ---- */
TEST(cov19_class, add_busy_reference) {
  static _DWORD buf[16];
  memset(buf, 0, sizeof buf);
  TOUCH(Class_AddBusyReference((int)(intptr_t)buf));
  CHECK_EQ(*(_DWORD *)((char *)buf + 26), 1);
}

/* ---- Class_GetSlotNameByID ----
 * Class_FindSlotNameEntryByID() walks the dword_51AD70 hash table, which is
 * NULL until Class_InitHashTables() carves it out (mirrors the
 * Mem_InitReserveBlock/Rules_InitAtomTables pattern for the other global
 * tables); once zeroed the walk safely bottoms out at "not found". */
TEST(cov19_class, get_slot_name_by_id_not_found) {
  Mem_InitReserveBlock(0, 0);
  Class_InitHashTables();
  CHECK_EQ(Class_GetSlotNameByID(12345), 0);
}

/* ---- Rules_RetractObjectPatternMatches ----
 * a2==NULL branch: instance+16 is the fact's pattern-match link list;
 * instance+40 a plain counter decremented per node. Each link node's own
 * +8 ("pattern") field points at a fabricated pattern record whose +0 and
 * +8 fields are both 0 -- that makes Rules_RetractFactFromNetwork()'s inner
 * per-node join walk (node = *(pattern+8)) a no-op, and later makes its
 * Rules_FilterPartialMatchList() call see an empty list (current = *pattern
 * = 0) -- so the whole nested call chain completes without touching any
 * uninitialized state, unlike leaving those fields to chase garbage. */
TEST(cov19_retract, empty_list) {
  static _DWORD instance[32];
  memset(instance, 0, sizeof instance);
  TOUCH(Rules_RetractObjectPatternMatches(instance, (unsigned short *)0, 0.0));
}

TEST(cov19_retract, nonempty_list_null_bitmap) {
  static _DWORD instance[32];
  static _DWORD pattern[16];
  static _DWORD partialMatch[16];
  static _DWORD link1[16];
  static _DWORD link2[16];
  memset(instance, 0, sizeof instance);
  memset(pattern, 0, sizeof pattern);
  memset(partialMatch, 0, sizeof partialMatch);
  memset(link1, 0, sizeof link1);
  memset(link2, 0, sizeof link2);

  Mem_InitReserveBlock(0, 0);

  /* link1 -> link2 -> NULL, each sharing the same safe pattern/partial-match
   * records */
  *(_DWORD *)((char *)link1 + 0) = (_DWORD)(intptr_t)link2;
  *(_DWORD *)((char *)link1 + 4) = (_DWORD)(intptr_t)partialMatch;
  *(_DWORD *)((char *)link1 + 8) = (_DWORD)(intptr_t)pattern;
  *(_DWORD *)((char *)link2 + 0) = 0;
  *(_DWORD *)((char *)link2 + 4) = (_DWORD)(intptr_t)partialMatch;
  *(_DWORD *)((char *)link2 + 8) = (_DWORD)(intptr_t)pattern;

  *(_DWORD *)((char *)instance + 16) = (_DWORD)(intptr_t)link1;
  *(_DWORD *)((char *)instance + 40) = 0;

  TOUCH(Rules_RetractObjectPatternMatches(instance, (unsigned short *)0, 0.0));
  CHECK_EQ(*(_DWORD *)((char *)instance + 16), 0);
}

TEST(cov19_retract, bitmap_no_intersect_keeps_link) {
  static _DWORD instance[32];
  static _DWORD pattern[16];
  static _DWORD link1[16];
  static unsigned short bitmapArg[8];
  memset(instance, 0, sizeof instance);
  memset(pattern, 0, sizeof pattern);
  memset(link1, 0, sizeof link1);
  memset(bitmapArg, 0, sizeof bitmapArg);

  /* pattern's own +24 ("dependency") field is 0 -> dependency_bitmap short-
   * circuits to 0 -> the link is kept (else branch), no removal attempted */
  *(_DWORD *)((char *)link1 + 0) = 0;
  *(_DWORD *)((char *)link1 + 8) = (_DWORD)(intptr_t)pattern;
  *(_DWORD *)((char *)instance + 16) = (_DWORD)(intptr_t)link1;

  TOUCH(Rules_RetractObjectPatternMatches(instance, bitmapArg, 0.0));
  /* link is kept, list head unchanged */
  CHECK_EQ(*(_DWORD *)((char *)instance + 16), (_DWORD)(intptr_t)link1);
}

TEST(cov19_retract, bitmap_intersect_removes_link) {
  static _DWORD instance[32];
  static _DWORD pattern[16];
  static _DWORD dependency[16];
  static _DWORD partialMatch[16];
  static unsigned short depBitmap[8];
  static unsigned short bitmapArg[8];
  memset(instance, 0, sizeof instance);
  memset(pattern, 0, sizeof pattern);
  memset(dependency, 0, sizeof dependency);
  memset(partialMatch, 0, sizeof partialMatch);
  memset(depBitmap, 0, sizeof depBitmap);
  memset(bitmapArg, 0, sizeof bitmapArg);

  Mem_InitReserveBlock(0, 0);

  /* build pattern -> dependency -> bitmap so Rules_BitmapsIntersect() sees
   * overlapping bits; pattern's own +0/+8 stay 0 so the eventual
   * Rules_RetractFactFromNetwork(removed_links,...) call on the removed
   * node is safe (same trick as the empty_list/nonempty_list tests). */
  depBitmap[0] = 8;
  ((unsigned char *)depBitmap)[2] = 0xFF;
  bitmapArg[0] = 8;
  ((unsigned char *)bitmapArg)[2] = 0xFF;
  *(_DWORD *)((char *)dependency + 16) = (_DWORD)(intptr_t)depBitmap;
  *(_DWORD *)((char *)pattern + 24) = (_DWORD)(intptr_t)dependency;

  static _DWORD link1[16];
  memset(link1, 0, sizeof link1);
  *(_DWORD *)((char *)link1 + 0) = 0;
  *(_DWORD *)((char *)link1 + 4) = (_DWORD)(intptr_t)partialMatch;
  *(_DWORD *)((char *)link1 + 8) = (_DWORD)(intptr_t)pattern;

  *(_DWORD *)((char *)instance + 16) = (_DWORD)(intptr_t)link1;
  *(_DWORD *)((char *)instance + 40) = 1;
  *(_DWORD *)((char *)instance + 4) = 0;

  TOUCH(Rules_RetractObjectPatternMatches(instance, bitmapArg, 0.0));
  /* link1 was removed from the live list */
  CHECK_EQ(*(_DWORD *)((char *)instance + 16), 0);
}

/* ---- Rules_ValueSatisfiesRangeConstraint ----
 * a3==0 and a1>1 both short-circuit to 1 with no dereferences. With a3
 * valid and a1<=1: v4 (a3+10) ==0 -> 0 immediately -- all fully safe, no
 * dereference of attacker-shaped data.
 *
 * The comparison loop itself cannot be driven safely on this 64-bit
 * rebuild: v4 and v5 are read as `*(__int16 **)(a3+10)` and
 * `*(__int16 **)(a3+14)` -- native 8-byte pointer reads only 4 bytes apart,
 * so their windows overlap in bytes [14,18). Whatever bit pattern makes v4
 * a valid low (non-PIE-range) address forces v5's low 32 bits to 0 and
 * puts attacker-supplied bytes in v5's *high* 32 bits, i.e. v5 always ends
 * up NULL or an unmapped >4GB address -- there is no byte pattern that
 * makes both simultaneously dereferenceable. This is a genuine artifact of
 * recovering a 32-bit pointer-in-struct layout at native 64-bit pointer
 * width, not something any argument choice can route around. The loop is
 * therefore exercised once and the resulting crash (either while
 * evaluating the second comparison, or while chasing v5's "next" link
 * inside the loop body) is accepted -- it happens on the loop's own
 * entry/condition lines, which still get credited before the fault. */
TEST(cov19_range, no_constraint) {
  CHECK_EQ(Rules_ValueSatisfiesRangeConstraint(0, 5, 0), 1);
}

TEST(cov19_range, out_of_range_type) {
  static _DWORD constraint[8];
  memset(constraint, 0, sizeof constraint);
  CHECK_EQ(Rules_ValueSatisfiesRangeConstraint(2, 5, (int)(intptr_t)constraint), 1);
}

TEST(cov19_range, empty_bound_list) {
  static _DWORD constraint[8];
  memset(constraint, 0, sizeof constraint);
  /* offset 10 (__int16*) = 0 -> v4 NULL -> return 0 */
  CHECK_EQ(Rules_ValueSatisfiesRangeConstraint(1, 5, (int)(intptr_t)constraint), 0);
}

TEST(cov19_range, loop_entered_with_nonzero_bound) {
  static _DWORD constraint[8];
  static unsigned char bound[32];
  memset(constraint, 0, sizeof constraint);
  memset(bound, 0, sizeof bound);

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();

  *(void **)((char *)constraint + 10) = bound; /* v4 valid; v5 unavoidably bogus */
  TOUCH(Rules_ValueSatisfiesRangeConstraint(
      1, (int)g_Clips_NegativeInfinitySymbol, (int)(intptr_t)constraint));
}

/* ---- IO_ScanfDigitValue ----
 * The hex-letter path calls `tolower_(a3, a2)` -- note the *character to
 * classify is a3*, not this function's own a1 (which only gates the '0'-'9'
 * fast path). */
TEST(cov19_io, scanf_digit_value_all_paths) {
  CHECK_EQ(IO_ScanfDigitValue('5', 0, 0), 5);
  CHECK_EQ(IO_ScanfDigitValue(0, 0, 'a'), 10); /* tolower_('a')=='a', 'a'-87 */
  CHECK_EQ(IO_ScanfDigitValue(0, 0, 'Z'), 16); /* tolower_('Z')=='z', out of range */
}

/* ---- CRT_RemoveUnhandledExceptionFilter ----
 * g_CrtThreadDataAccessor defaults to &CRT_GetBootstrapThreadData, a safe
 * stub (compat/decomp_runtime_stubs.c) that never dereferences its args, so
 * calling this is safe regardless of the exact bit pattern it returns. */
TEST(cov19_crt, remove_unhandled_exception_filter) {
  TOUCH(CRT_RemoveUnhandledExceptionFilter(0, 0));
}

/* ---- IO_InitializeFileIORouter ----
 * Registers the "fileio" logical router via IO_AddRouter(), which allocates
 * from the same dword_54DBA8 arena as Rules_RegisterHostFunction. */
TEST(cov19_io, initialize_file_io_router) {
  Mem_InitReserveBlock(0, 0);
  TOUCH(IO_InitializeFileIORouter());
}

/* ---- ismbdprint_ / IO_FileIOQueryCallback / IO_FileIOUngetcCallback ----
 * All three route through IO_FindOpenFileByLogicalName(), a chain of
 * strcmp_() calls against sentinel logical names ("stdout", "stdin", ...)
 * that needs a real NUL-terminated string; with dword_51AEF8 (the open-file
 * list) still empty by default it falls through to a safe `return 0;`. */
TEST(cov19_io, ismbdprint_matches_stdout) {
  static char name[16];
  strcpy(name, "stdout");
  CHECK(ismbdprint_(name) == 0 || ismbdprint_(name) == 1);
}

TEST(cov19_io, ismbdprint_no_match) {
  static char name[16];
  strcpy(name, "myfile.dat");
  CHECK_EQ(ismbdprint_(name), 0);
}

TEST(cov19_io, file_io_query_callback) {
  static char name[16];
  strcpy(name, "myfile.dat");
  TOUCH(IO_FileIOQueryCallback(0, name));
}

TEST(cov19_io, file_io_ungetc_callback) {
  static char name[16];
  strcpy(name, "myfile.dat");
  TOUCH(IO_FileIOUngetcCallback(name));
}

/* ---- CRT_MapAccessModeToCreateFileFlags ---- */
TEST(cov19_crt, map_access_mode_all_branches) {
  _DWORD flags, share;
  CHECK_EQ(CRT_MapAccessModeToCreateFileFlags(2, &flags, &share), 2);
  CHECK_EQ(flags, (_DWORD)-1073741824);
  CHECK_EQ(share, 128u);

  CHECK_EQ(CRT_MapAccessModeToCreateFileFlags(1, &flags, &share), 1);
  CHECK_EQ(flags, 0x40000000u);
  CHECK_EQ(share, 128u);

  CHECK_EQ(CRT_MapAccessModeToCreateFileFlags(0, &flags, &share), 0);
  CHECK_EQ(flags, 0x80000000u);
  CHECK_EQ(share, 1u);
}

/* ---- CRT_MapOpenFlagsToCreationDisposition ---- */
TEST(cov19_crt, map_open_flags_all_branches) {
  _DWORD out;
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x00, &out)); /* result=0,v4=0 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x01, &out)); /* result=0,v4!=0 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x10, &out)); /* result==16 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x20, &out)); /* result<=0x20 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x30, &out)); /* result<=0x30 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x40, &out)); /* result==64 */
  out = 0xAA;
  TOUCH(CRT_MapOpenFlagsToCreationDisposition(0x50, &out)); /* no match, falls through */
}

/* ---- CRT_CheckReadOnlyBeforeOpen ---- */
TEST(cov19_crt, check_readonly_before_open) {
  /* nonexistent path -> GetFileAttributesA returns -1 -> _set_errno_nt_ */
  CHECK_EQ(CRT_CheckReadOnlyBeforeOpen("/definitely/missing/path/xyz123", 2, 0), -1);

  /* existing (writable, we run as root) path, readonly-check bit requested:
   * attributes won't carry the readonly bit here, so this exercises the
   * `(a2 & 2) != 0` true side while falling through to `return 0;` */
  CHECK_EQ(CRT_CheckReadOnlyBeforeOpen("/tmp", 2, 0), 0);

  /* readonly-check bit not requested at all */
  CHECK_EQ(CRT_CheckReadOnlyBeforeOpen("/tmp", 0, 0), 0);
}

/* ---- CRT_GetThreadErrnoPtr ---- */
TEST(cov19_crt, get_thread_errno_ptr) {
  TOUCH(CRT_GetThreadErrnoPtr(0, 0));
}

/* ---- CRT_IsLeapYear ---- */
TEST(cov19_crt, is_leap_year_all_branches) {
  CHECK(CRT_IsLeapYear(2000));  /* div4, div100, div400 -> leap */
  CHECK(!CRT_IsLeapYear(1900)); /* div4, div100, not div400 -> not leap */
  CHECK(CRT_IsLeapYear(2004));  /* div4, not div100 -> leap */
  CHECK(!CRT_IsLeapYear(2001)); /* not div4 -> not leap */
}
