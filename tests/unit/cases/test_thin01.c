/* thin01: final top-up pass over a batch of near-fully-covered functions
 * (see scratchpad thin_batches/thin_01.json). Most of the batch's remaining
 * gaps turned out to already have documented, failed prior attempts
 * elsewhere in this suite (test_cov03/04/09/11/16/21/2_09/4_01/4_03/4_05/
 * 4_06/4_07.c), each confirmed via source review and/or gdb repro to be
 * either (a) gated by a decompiler "possibly undefined" register whose value
 * is uncontrollable stack/register garbage (Map_RevealTilesInRadius2ForPlayer,
 * Rules_AssertParsedFact, Building_ApplySiegeDamageToWallSections,
 * CastleProduction_ReloadLicenceSlotSprites's non-incrementing "i", and every
 * Lexer_TokenExpect-gated Rules_*Command function -- confirmed by a live gdb
 * repro that Lexer_TokenExpect's own decompiler-lost 'v2' deterministically
 * steers Rules_RefreshAgendaCommand/Rules_Dependencies/Rules_Dependents/
 * Defgeneric_GetDefmethodListCommand/Rules_HostSeed/Rules_BsaveCommand away
 * from their "success" branches even with a carefully engineered one-node
 * argument chain), (b) structurally unreachable in this 64-bit port
 * (Compat_StringHolderAssignJoined's OOM branch, Compat_RenderDeviceFillSolid-
 * Rect's surface_pixels-null branch, WCIsvListBase_base_insert's tail-lookup-
 * failed branch, and all five Unit_Build*Path sibling functions' early-break
 * lines, which depend on a fixed-length global string parity that no runtime
 * input can change), or (c) a genuine decompiler byte-offset/pointer-width
 * mismatch baked into the recovered function body itself rather than into
 * caller-controlled state -- confirmed via gdb for Method_FindByIndex (the
 * for-loop's `_DWORD **` cast reads a1's 4-byte count field as the pointer's
 * upper half, producing an unmapped >4GB address on every non-trivial call)
 * and MessageHandler_PrintHandlerListTally (MessageHandler_CountAndPrintHandlers
 * assumes its caller's locals sit at a fixed byte offset from each other that
 * this recompilation does not reproduce, segfaulting on the very first call
 * with a real class record). Compat_FileSystemOpenIfReady, Rules_AssertCastleFact
 * and Rules_FindImportExportConstruct were independently already documented
 * (test_cov4_05.c/test_cov4_07.c) as needing full CLIPS-engine/module-system
 * object graphs "well beyond a two-line fixture". Palette_LoadFromQueryHandle's
 * remaining line needs a real mounted filesystem entry to avoid
 * App_RequestQuit()'s __noreturn exit deep inside Compat_LoadPalCOLIntoTable.
 * Castle_DrawAllAmbientAnimationLayers's existing zeroed-buffer fixture still
 * crashes because its case 5/10 branches call through unconditionally
 * (result != -1 default) into the real sprite-draw stack.
 *
 * The two genuinely new, deterministic fixes below were verified with a
 * private scratch build (gcov line-hit counts) across repeated runs. */

/* ---- Rules_ReportSymbolTypeError (target: 100323,100324 -- the "symbol
 * found" success branch). Rules_MakeSymbol looks a1 up in dword_54DD40, the
 * *function-name* hash table (not the plain string-intern table dword_54DD50
 * that Str_Intern/Rules_FindSymbolEntry share) -- a bucket entry there is a
 * {function_record_ptr, next_ptr} node whose function_record's own first
 * field must equal the interned-name pointer Rules_FindSymbolEntry(a1)
 * resolves to. Rules_InitAtomTables() never populates dword_54DD40 (only
 * Rules_RegisterHostFunction/Rules_InsertFunctionHashEntry do, via the
 * Rules_Register*HostFunctions bring-up this fixture skips), so this builds
 * the single matching bucket node directly: intern the symbol name (giving
 * a real dword_54DD50 entry), point a small zeroed "function record" buffer's
 * first field at that interned entry, and chain it into dword_54DD40's
 * bucket at the exact index Rules_HashSymbolName(a1,0x33) will recompute.
 * That makes Rules_MakeSymbol return the function-record pointer, whose
 * offset+17 "restriction string" field reads 0 out of the zeroed buffer, so
 * Rules_GetArgRestrictionType safely takes its own early "117" ('u') return
 * without touching v4 (also decompiler-lost, but provably unused on this
 * path since the offset+17 guard returns first). Rules_GetArgTypeName(117)
 * and Parser_ReportError are pure formatting helpers already proven safe
 * elsewhere in this suite (off_51A614[0] == "werror", a real non-NULL
 * string, so Output_Write's default-router fallback never dereferences
 * NULL). ---- */
TEST(thin01_reportsymerr, symbol_found_reaches_error_report) {
  static char sym_name[32] = "thin01_symtypeerror";
  static _DWORD func_record[64];
  static _DWORD bucket_node[4];
  int hidx;
  int *interned;

  Mem_InitReserveBlock(0, 0);
  Rules_InitAtomTables();
  Rules_InitFunctionNameHashTable();

  interned = (int *)Str_Intern(sym_name, 0);
  memset(func_record, 0, sizeof func_record);
  func_record[0] = (_DWORD)(intptr_t)interned;

  hidx = Rules_HashSymbolName((_BYTE *)sym_name, 0x33u);
  bucket_node[0] = (_DWORD)(intptr_t)func_record;
  bucket_node[1] = 0;
  *(_DWORD *)(g_ClipsFunctionNameHashTable + 4 * hidx) = (_DWORD)(intptr_t)bucket_node;

  TOUCH(Rules_ReportSymbolTypeError((_BYTE *)sym_name, 0));
}

/* ---- BuildingEconomyDialog_SetExitSignal (target: 44271 -- the diagnostics
 * fprintf gated on Diagnostics_IsWorldMapClickTraceEnabled()). Two separate
 * prior attempts each got half of this right but not both at once:
 * test_cov04.c's set_exit_signal passes a valid zeroed widget buffer (so the
 * unconditional UIWidget_PlayPressedReleaseAnimationWithDelay(a1,1) call at
 * the top of the function doesn't dereference a1+49 on a NULL a1) but never
 * sets the trace env var, while test_cov2_09.c/test_cov4_03.c's
 * set_exit_signal_trace_enabled set the env var but call with a1==0, which
 * crashes inside UIWidget_PlayPressedReleaseAnimationWithDelay before ever
 * reaching the trace check (confirmed: both of those tests show as CRASH in
 * a full test run). Combining both fixes -- a real zeroed widget buffer AND
 * the env var set before the first call in this forked child -- reaches the
 * fprintf line without crashing. ---- */
TEST(thin01_economydialog, set_exit_signal_trace_enabled_with_widget) {
  static unsigned char widget[256];
  memset(widget, 0, sizeof widget);
  setenv("CLASH95_TRACE_WORLD_CLICK", "1", 1);
  g_BuildingEconomyDialogExitSignal = 0;
  TOUCH(BuildingEconomyDialog_SetExitSignal((int)(intptr_t)widget, 1));
  CHECK_EQ(g_BuildingEconomyDialogExitSignal, 1);
}
