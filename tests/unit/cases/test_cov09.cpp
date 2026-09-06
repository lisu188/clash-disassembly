/* cov09: Compat_StringHolder, Compat_FileSystem, Compat_FileFinder, Compat_FileStream,
 * Str_FormatSignedRadixDigits, Output_WriteFormatted, Res_ helpers. */

/* ---- Compat_StringHolderDestructor / GetText ---- */
TEST(cov09_strholder, destructor_and_gettext) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* GetText: null holder pointer */
  CHECK_EQ(Compat_StringHolderGetText(0), 0);

  /* GetText: holder with null text word */
  CHECK_EQ(Compat_StringHolderGetText(holder), 0);

  /* Give the holder some real (heap) text via CopyText, then GetText */
  Compat_StringHolderCopyText(holder, "hello");
  CHECK(Compat_StringHolderGetText(holder) != 0);

  /* Destructor frees text (via no-op j__nfree_ stub) and clears the slot */
  TOUCH(Compat_StringHolderDestructor(holder));
  CHECK_EQ(holder[0], 0);
}

/* ---- Compat_StringHolderAssignJoined ---- */
TEST(cov09_strholder, assign_joined) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* both null/empty -> frees and returns (branch: !prefix_size && !suffix_size) */
  Compat_StringHolderAssignJoined(holder, 0, 0);
  CHECK_EQ(holder[0], 0);

  /* prefix only */
  Compat_StringHolderAssignJoined(holder, "abc", 0);
  CHECK(Compat_StringHolderGetText(holder) != 0);
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abc"), 0);

  /* prefix + suffix */
  Compat_StringHolderAssignJoined(holder, "abc", "def");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abcdef"), 0);

  /* suffix only */
  Compat_StringHolderAssignJoined(holder, 0, "xyz");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "xyz"), 0);

  /* null holder -> immediate return */
  Compat_StringHolderAssignJoined(0, "a", "b");
}

/* ---- Compat_StringHolderInsertText ---- */
TEST(cov09_strholder, insert_text) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* null holder -> return */
  Compat_StringHolderInsertText(0, 0, "x");

  /* no existing text, insert at index 0 */
  Compat_StringHolderInsertText(holder, 0, "abc");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abc"), 0);

  /* insert in the middle */
  Compat_StringHolderInsertText(holder, 1, "XY");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "aXYbc"), 0);

  /* invalid index (negative) -> no-op */
  Compat_StringHolderInsertText(holder, -1, "Z");

  /* index beyond existing size -> no-op */
  Compat_StringHolderInsertText(holder, 999, "Z");

  /* empty inserted text -> no-op (inserted_size == 0) */
  Compat_StringHolderInsertText(holder, 0, "");
  Compat_StringHolderInsertText(holder, 0, 0);
}

/* ---- Compat_StringHolderCopyText / InitText ---- */
TEST(cov09_strholder, copy_and_init_text) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* null holder */
  Compat_StringHolderCopyText(0, "z");

  /* null source -> frees only */
  Compat_StringHolderCopyText(holder, 0);
  CHECK_EQ(holder[0], 0);

  /* empty source string -> frees only (branch: !*source) */
  Compat_StringHolderCopyText(holder, "");
  CHECK_EQ(holder[0], 0);

  /* real source */
  Compat_StringHolderCopyText(holder, "world");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "world"), 0);

  /* InitText: null holder */
  Compat_StringHolderInitText(0, "q");

  /* InitText: null source -> just frees */
  Compat_StringHolderInitText(holder, 0);
  CHECK_EQ(holder[0], 0);

  /* InitText: empty source -> frees, does not copy (branch source && *source false) */
  Compat_StringHolderInitText(holder, "");
  CHECK_EQ(holder[0], 0);

  /* InitText: real source -> copies */
  Compat_StringHolderInitText(holder, "init");
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "init"), 0);
}

/* ---- Append / Prepend text ---- */
TEST(cov09_strholder, append_prepend_text) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  Compat_StringHolderCopyText(holder, "mid");
  TOUCH(Compat_StringHolderAppendText((const char **)holder, "end"));
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "midend"), 0);

  /* append with null/empty a2 -> no-op branch */
  TOUCH(Compat_StringHolderAppendText((const char **)holder, 0));
  TOUCH(Compat_StringHolderAppendText((const char **)holder, ""));

  TOUCH(Compat_StringHolderPrependText((const char **)holder, "start_"));
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "start_midend"), 0);

  TOUCH(Compat_StringHolderPrependText((const char **)holder, 0));
  TOUCH(Compat_StringHolderPrependText((const char **)holder, ""));
}

/* ---- FindSubstringOffset: only the safe short-circuit branches (a2==0 /
 * *a1==0) are exercised -- the true branch calls through the weak `strstr_`
 * symbol which resolves to a null function pointer in this build and would
 * crash by design; not worth chasing for one extra line. */
TEST(cov09_strholder, find_substring_offset_safe_paths) {
  _DWORD a1buf[4];
  memset(a1buf, 0, sizeof(a1buf));

  CHECK_EQ(Compat_StringHolderFindSubstringOffset(a1buf, 0, 0), -1);

  a1buf[0] = 0; /* *a1 still 0 -> short circuits before calling strstr_ */
  CHECK_EQ(Compat_StringHolderFindSubstringOffset(a1buf, 1, 0), -1);
}

/* ---- UppercaseInPlace ---- */
TEST(cov09_strholder, uppercase_in_place) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* empty text -> no-op branch */
  TOUCH(Compat_StringHolderUppercaseInPlace((const char **)holder, 0));

  Compat_StringHolderCopyText(holder, "lower");
  TOUCH(Compat_StringHolderUppercaseInPlace((const char **)holder, 0));
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "LOWER"), 0);
}

/* ---- FindCharFrom ---- */
TEST(cov09_strholder, find_char_from) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* empty text -> -1 */
  CHECK_EQ(Compat_StringHolderFindCharFrom((const char **)holder, 'a', 0), -1);

  Compat_StringHolderCopyText(holder, "abcabc");

  /* negative start -> -1 */
  CHECK_EQ(Compat_StringHolderFindCharFrom((const char **)holder, 'b', -1), -1);

  /* start beyond length -> -1 */
  CHECK_EQ(Compat_StringHolderFindCharFrom((const char **)holder, 'b', 999), -1);

  /* found */
  CHECK_EQ(Compat_StringHolderFindCharFrom((const char **)holder, 'b', 0), 1);

  /* not found char */
  CHECK_EQ(Compat_StringHolderFindCharFrom((const char **)holder, 'z', 0), -1);
}

/* ---- FindLastBackslash / FindLastBackslashBefore ---- */
TEST(cov09_strholder, find_last_backslash) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* empty text -> -1 */
  CHECK_EQ(Compat_StringHolderFindLastBackslash((_BYTE **)holder), -1);

  Compat_StringHolderCopyText(holder, "a\\b\\c");
  CHECK_EQ(Compat_StringHolderFindLastBackslash((_BYTE **)holder), 3);

  /* no backslash present */
  Compat_StringHolderCopyText(holder, "noslash");
  CHECK_EQ(Compat_StringHolderFindLastBackslash((_BYTE **)holder), -1);
}

TEST(cov09_strholder, find_last_backslash_before) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* empty text -> -1 */
  CHECK_EQ(Compat_StringHolderFindLastBackslashBefore((char **)holder, 0), -1);

  Compat_StringHolderCopyText(holder, "a\\b\\c");

  /* negative index -> -1 */
  CHECK_EQ(Compat_StringHolderFindLastBackslashBefore((char **)holder, -1), -1);

  /* index beyond length -> -1 */
  CHECK_EQ(Compat_StringHolderFindLastBackslashBefore((char **)holder, 999), -1);

  /* valid index, backslash found before it */
  CHECK_EQ(Compat_StringHolderFindLastBackslashBefore((char **)holder, 3), 3);

  /* valid index, no backslash before truncation point */
  Compat_StringHolderCopyText(holder, "noslash");
  CHECK_EQ(Compat_StringHolderFindLastBackslashBefore((char **)holder, 2), -1);
}

/* ---- RemoveRange ---- */
TEST(cov09_strholder, remove_range) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  /* empty text -> a1 unchanged, returned as-is */
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 0, 0, 0));

  Compat_StringHolderCopyText(holder, "abcdef");

  /* negative a2 -> no-op branch */
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, -1, 0, 0));
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abcdef"), 0);

  /* text_len == a4 -> destroys holder entirely (goes straight to Destructor) */
  Compat_StringHolderCopyText(holder, "abcdef");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 0, 0, 6));
  CHECK_EQ(holder[0], 0);

  /* remove a middle chunk: text_len != a4 */
  Compat_StringHolderCopyText(holder, "abcdef");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 2, 0, 2)); /* remove "cd" */
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abef"), 0);

  /* remove a trailing chunk: (a2+a4) >= text_len branch false path skipped */
  Compat_StringHolderCopyText(holder, "abcdef");
  TOUCH(Compat_StringHolderRemoveRange((char **)holder, 4, 0, 2)); /* remove "ef" */
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abcd"), 0);
}

/* ---- InsertTextChecked ---- */
TEST(cov09_strholder, insert_text_checked) {
  _DWORD holder[4];
  memset(holder, 0, sizeof(holder));

  Compat_StringHolderCopyText(holder, "ac");

  /* valid insert */
  TOUCH(Compat_StringHolderInsertTextChecked((const char **)holder, 1, "b"));
  CHECK_EQ(strcmp((const char *)Compat_StringHolderGetText(holder), "abc"), 0);

  /* negative index -> guarded no-op */
  TOUCH(Compat_StringHolderInsertTextChecked((const char **)holder, -1, "z"));

  /* null text -> guarded no-op */
  TOUCH(Compat_StringHolderInsertTextChecked((const char **)holder, 0, 0));

  /* empty text -> guarded no-op */
  TOUCH(Compat_StringHolderInsertTextChecked((const char **)holder, 0, ""));
}

/* ---- Compat_NoOpQueryCallback ---- */
TEST(cov09_query, no_op_callback) {
  CHECK_EQ(Compat_NoOpQueryCallback(), 0);
}

/* ---- Compat_FileSystemQueryResultRelease ----
 * Build a fake "opened query" object: word[0] is the vtable pointer. We
 * exercise: null query, null vtable, a non-matching vtable, the FileStream
 * triple (-> Compat_FileStreamRelease) and the Compat_Query triple
 * (-> Compat_QueryDestruct). word[1] is kept 0 so Compat_FileStreamRelease's
 * internal fclose_() call is skipped (result[1] == 0 branch). */
TEST(cov09_filesys, query_result_release) {
  _DWORD query[4];
  uintptr_t vt_none[3];
  uintptr_t vt_stream[3];
  uintptr_t vt_query[3];

  /* null query -> immediate return */
  Compat_FileSystemQueryResultRelease(0);

  /* null vtable slot -> immediate return */
  memset(query, 0, sizeof(query));
  Compat_FileSystemQueryResultRelease(query);

  /* non-matching vtable -> falls through both ifs, implicit return */
  vt_none[0] = 0;
  vt_none[1] = 0;
  vt_none[2] = 0;
  query[0] = (_DWORD)(uintptr_t)vt_none;
  query[1] = 0;
  Compat_FileSystemQueryResultRelease(query);

  /* FileStream-shaped vtable -> Compat_FileStreamRelease(opened_query, 2) */
  vt_stream[0] = (uintptr_t)Compat_FileStreamSeekFromStart;
  vt_stream[1] = (uintptr_t)Compat_FileStreamTell;
  vt_stream[2] = (uintptr_t)Compat_FileStreamSeekFromEnd;
  query[0] = (_DWORD)(uintptr_t)vt_stream;
  query[1] = 0;
  Compat_FileSystemQueryResultRelease(query);

  /* Query-shaped vtable -> Compat_QueryDestruct(opened_query, 2) */
  vt_query[0] = (uintptr_t)Compat_QuerySkipBytes;
  vt_query[1] = (uintptr_t)Compat_QueryGetLength;
  vt_query[2] = (uintptr_t)Compat_QuerySkipBytesFromBase;
  query[0] = (_DWORD)(uintptr_t)vt_query;
  query[1] = 0;
  Compat_FileSystemQueryResultRelease(query);
}

/* ---- Compat_FileSystemOpenIfReady ----
 * Only the a1==0 short-circuit path is safe to drive directly: any nonzero
 * file_system routes deep into the disk-mount / archive query machinery
 * (Compat_FileSystemQueryOpen -> FileSystem_DiskMountOpenFileQuery /
 * File_OpenMountRootEntry) which is well outside this batch and not safely
 * fakeable from a bare buffer. */
TEST(cov09_filesys, open_if_ready_null) {
  CHECK_EQ(Compat_FileSystemOpenIfReady(0, 0), 0);
  CHECK_EQ(Compat_FileSystemOpenIfReady(0, 7), 0);
}

/* ---- Str_FormatSignedRadixDigits ---- */
TEST(cov09_str, format_signed_radix_digits) {
  char buf[36];
  const struct {
    int value;
    unsigned int radix;
    const char *expected;
  } cases[] = {
    {-123, 10, "-123"},
    {123, 10, "123"},
    {255, 16, "ff"},
    {0, 2, "0"},
    {(-2147483647 - 1), 10, "-2147483648"},
    {2147483647, 10, "2147483647"},
    {-1, 16, "ffffffff"},
    {-1, 2, "11111111111111111111111111111111"},
    {35, 36, "z"},
    {36, 36, "10"}
  };

  for ( const auto &entry : cases ) {
    memset(buf, 0xa5, sizeof(buf));
    CHECK_EQ(Str_FormatSignedRadixDigits(entry.value, buf, entry.radix),
             (int)(uintptr_t)buf);
    CHECK_EQ(strcmp(buf, entry.expected), 0);
    CHECK_EQ((unsigned char)buf[strlen(entry.expected) + 1], 0xa5);
  }
}

/* ---- Output_WriteFormatted ----
 * The early-return guard (!a3 || !a4) is fully safe. The remaining lines
 * (argument counting, allocation, varargs collection, and the final
 * CRT_VfprintfLockedWrite call) are exercised too: CRT_VfprintfLockedWrite
 * dereferences its stream argument assuming a real CRT FILE-like structure,
 * which a bare zeroed buffer does not provide, so those calls may crash
 * deep inside a callee outside this batch. The harness isolates that via
 * siglongjmp, and Output_WriteFormatted's own lines up through the call are
 * still recorded as covered. */
TEST(cov09_output, write_formatted_guards) {
  CHECK_EQ(Output_WriteFormatted(0, 0, 0, 0), 0);
  CHECK_EQ(Output_WriteFormatted(0, 0, 1, 0), 0);
  CHECK_EQ(Output_WriteFormatted(0, 0, 0, (int)(intptr_t)"fmt"), 0);
}

TEST(cov09_output, write_formatted_no_args) {
  _DWORD fake_stream[32];
  memset(fake_stream, 0, sizeof(fake_stream));
  TOUCH(Output_WriteFormatted(0, 0, (int)(intptr_t)fake_stream,
                               (int)(intptr_t)"plain text, no specifiers\n"));
}

TEST(cov09_output, write_formatted_with_args) {
  _DWORD fake_stream[32];
  memset(fake_stream, 0, sizeof(fake_stream));
  TOUCH(Output_WriteFormatted(0, 0, (int)(intptr_t)fake_stream,
                               (int)(intptr_t)"%d %s\n", 5, "x"));
}

/* ---- Compat_FileSystemFreeFileRecordName ---- */
TEST(cov09_filesys, free_file_record_name) {
  TOUCH(Compat_FileSystemFreeFileRecordName());
}

/* ---- Compat_FileSystemFindMountedPathById ---- */
TEST(cov09_filesys, find_mounted_path_by_id) {
  _DWORD a1buf[16];
  _DWORD entries[8]; /* two 16-byte (4-dword) entries */

  memset(a1buf, 0, sizeof(a1buf));
  memset(entries, 0, sizeof(entries));

  /* count == 0 -> v3 < 0 -> immediate return 0 */
  a1buf[28 / 4] = 0;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 42), 0);

  /* one entry, matching id */
  entries[0] = 1234; /* key */
  entries[1] = 5678; /* value returned */
  a1buf[20 / 4] = (_DWORD)(intptr_t)entries;
  a1buf[28 / 4] = 1;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 1234), 5678);

  /* one entry, no match -> loop exhausts, returns 0 */
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 9999), 0);

  /* two entries, match on the earlier (higher-offset) one first */
  entries[4] = 111;
  entries[5] = 222;
  a1buf[28 / 4] = 2;
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 111), 222);
  /* and match on the second-to-last entry after one loop iteration */
  CHECK_EQ(Compat_FileSystemFindMountedPathById((int)(intptr_t)a1buf, 1234), 5678);
}

/* ---- Compat_FileStreamUngetChar ----
 * Pass a2 == -1 so CRT_FlushBufferAndPutChar's guarded body (which relies on
 * an aliased-register value decompiled as an uninitialized local) is
 * short-circuited by its own `result != -1` guard; this wrapper itself has
 * no branches so this single safe call fully covers it. */
TEST(cov09_filestream, ungetchar) {
  CHECK_EQ(Compat_FileStreamUngetChar(0, -1), -1);
  CHECK_EQ(Compat_FileStreamUngetChar(1234, -1), -1);
}

/* ---- Compat_FileFinderGetName / GetAttributes / GetSize ---- */
TEST(cov09_filefinder, getters) {
  _DWORD finder[16];
  memset(finder, 0, sizeof(finder));
  finder[4 / 4] = 0xAA;   /* attributes offset */
  finder[20 / 4] = 4096;  /* size offset */

  CHECK_EQ(Compat_FileFinderGetName((int)(intptr_t)finder), (int)(intptr_t)finder + 24);
  CHECK_EQ(Compat_FileFinderGetAttributes((int)(intptr_t)finder), 0xAA);
  CHECK_EQ(Compat_FileFinderGetSize((int)(intptr_t)finder), 4096);
}

/* ---- Compat_FileFinderAdvance ----
 * findnext_() itself is safe for a bogus handle (an unregistered "handle"
 * value simply fails the internal handle lookup and returns 0), but the
 * subsequent store through the decompiler's stray uninitialized `v2` is
 * genuine undefined behaviour that may fault; isolate it in its own test so
 * a crash here can't cost other tests' coverage. */
TEST(cov09_filefinder, advance_bogus_handle) {
  TOUCH(Compat_FileFinderAdvance(0));
}

/* ---- Res_StreamSeekClamped ---- */
TEST(cov09_res, stream_seek_clamped) {
  _DWORD buf[8];
  memset(buf, 0, sizeof(buf));
  buf[12 / 4] = 100; /* clamp max */

  /* negative offset -> clamps to 0 */
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)buf, -5));
  CHECK_EQ(buf[8 / 4], 0);

  /* within range */
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)buf, 50));
  CHECK_EQ(buf[8 / 4], 50);

  /* beyond range -> clamps to max */
  TOUCH(Res_StreamSeekClamped((int)(intptr_t)buf, 500));
  CHECK_EQ(buf[8 / 4], 100);
}

/* ---- Res_BuildTaggedRecordHeader ---- */
TEST(cov09_res, build_tagged_record_header) {
  _DWORD hdr[8];
  memset(hdr, 0, sizeof(hdr));
  TOUCH(Res_BuildTaggedRecordHeader(hdr, 11, 22, 33));
  CHECK_EQ(hdr[1], 11);
  CHECK_EQ(hdr[3], 22);
  CHECK_EQ(hdr[2], 33);
}

/* ---- Res_XorDecodeByte ---- */
TEST(cov09_res, xor_decode_byte) {
  _DWORD ctx[8];
  memset(ctx, 0, sizeof(ctx));
  ctx[20 / 4] = 0x10;
  CHECK_EQ(Res_XorDecodeByte((int)(intptr_t)ctx, 0x05, 0xFF), 0xFF ^ (0x05 + 0x10));
}
