// cov13: Rules_/Lexer_ cluster - fact hashing, deftemplate registration,
// fact-watch flags, fact query/pattern-network helpers, multifield helpers,
// dependency lists, field hashing, and lexer scanning helpers.
//
// NOTE: buffers whose address is truncated to a 32-bit `int` (mirroring the
// recovered code's 32-bit pointer parameters) must use `static` storage, not
// stack storage: this is a -no-pie 64-bit build, so stack addresses live far
// above 4GB and truncate to garbage, while static/global addresses are low
// and survive the truncation intact.

// ---- Rules_HashFactEntry ----
TEST(cov13_hash, fact_entry_basic)
{
    static unsigned char factBuf[256];
    static unsigned char slotBuf[64];
    static unsigned char symBuf[64];
    memset(factBuf, 0, sizeof factBuf);
    memset(slotBuf, 0, sizeof slotBuf);
    memset(symBuf, 0, sizeof symBuf);

    static const char name[] = "SomeRelation";
    *(intptr_t *)(symBuf + 16) = (intptr_t)name;
    *(intptr_t *)(slotBuf + 0) = (intptr_t)symBuf;
    *(intptr_t *)(factBuf + 16) = (intptr_t)slotBuf;
    /* field-list count (offset 40+6) = 0 so Rules_HashFactFieldList loop is skipped */
    *(_WORD *)(factBuf + 40 + 6) = 0;

    TOUCH(Rules_HashFactEntry((int)(intptr_t)factBuf));
}

// ---- Rules_RegisterDeftemplateFunctions / Rules_InternInitialFactSymbol ----
TEST(cov13_reg, deftemplate_functions)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    TOUCH(Rules_RegisterDeftemplateFunctions(0, 0));
}

TEST(cov13_reg, intern_initial_fact_symbol)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    static unsigned char thisBuf[256];
    memset(thisBuf, 0, sizeof thisBuf);
    TOUCH(Rules_InternInitialFactSymbol(thisBuf));
}

// ---- Rules_GetFactWatchFlag / Rules_SetFactWatchFlag ----
TEST(cov13_watch, get_flag_both_ways)
{
    static _DWORD buf[16];
    memset(buf, 0, sizeof buf);
    buf[6] = 0; /* offset 24, bit1 clear */
    CHECK_EQ(Rules_GetFactWatchFlag((int)(intptr_t)buf), 0);
    buf[6] = 2; /* offset 24, bit1 set */
    /* Note: the recovered body operates on the _DWORD (unsigned) header
       word, so the shift pair is a logical shift and yields 1, not a
       sign-extended -1. */
    CHECK_EQ(Rules_GetFactWatchFlag((int)(intptr_t)buf), 1);
}

TEST(cov13_watch, set_flag_both_ways)
{
    static _DWORD buf[16];
    memset(buf, 0, sizeof buf);
    TOUCH(Rules_SetFactWatchFlag(1, (int)(intptr_t)buf));
    TOUCH(Rules_SetFactWatchFlag(0, (int)(intptr_t)buf));
}

// ---- Rules_WatchAlwaysTrueStub / Rules_RegisterFactQueryFunctions ----
TEST(cov13_watch, always_true_stub)
{
    CHECK_EQ(Rules_WatchAlwaysTrueStub(), 1);
}

TEST(cov13_reg, fact_query_functions)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    TOUCH(Rules_RegisterFactQueryFunctions());
}

// ---- Rules_CheckFactExistp / Rules_CheckFactStillAsserted ----
TEST(cov13_fact, check_fact_existp)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    TOUCH(Rules_CheckFactExistp(0.0));
}

TEST(cov13_fact, check_fact_still_asserted)
{
    CHECK_EQ(Rules_CheckFactStillAsserted(0), 0);

    static unsigned char factBuf[64];
    memset(factBuf, 0, sizeof factBuf);
    factBuf[29] = 0x01; /* signed byte >= 0 */
    TOUCH(Rules_CheckFactStillAsserted((int)(intptr_t)factBuf));

    factBuf[29] = 0x80; /* signed byte < 0 */
    TOUCH(Rules_CheckFactStillAsserted((int)(intptr_t)factBuf));
}

// ---- Rules_BuildFactAddressList ----
TEST(cov13_fact, build_fact_address_list)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    /* This function reads several uninitialized locals in the recovered
       C; call it defensively inside its own test so a crash here does not
       cost other tests' coverage. */
    TOUCH(Rules_BuildFactAddressList());
}

// ---- Rules_RegisterFactPatternNetworkPersistence ----
TEST(cov13_reg, fact_pattern_network_persistence)
{
    TOUCH(Rules_RegisterFactPatternNetworkPersistence());
}

// ---- Rules_FactPatternNetworkNextNode ----
TEST(cov13_net, next_node_direct_child)
{
    static _DWORD node[16];
    memset(node, 0, sizeof node);
    node[7] = 0xAAAA; /* nonzero child pointer value, not dereferenced */
    TOUCH(Rules_FactPatternNetworkNextNode(node));
}

TEST(cov13_net, next_node_sibling_present)
{
    static _DWORD node[16];
    memset(node, 0, sizeof node);
    node[7] = 0;
    node[10] = 0xBBBB; /* sibling present, loop not entered */
    TOUCH(Rules_FactPatternNetworkNextNode(node));
}

TEST(cov13_net, next_node_walk_to_null)
{
    static _DWORD node[16];
    memset(node, 0, sizeof node);
    node[7] = 0;
    node[10] = 0;
    node[8] = 0; /* parent is null -> loop returns null immediately */
    TOUCH(Rules_FactPatternNetworkNextNode(node));
}

TEST(cov13_net, next_node_walk_to_parent_sibling)
{
    static _DWORD parent[16];
    static _DWORD node[16];
    memset(parent, 0, sizeof parent);
    memset(node, 0, sizeof node);
    parent[10] = 0xCCCC;
    node[7] = 0;
    node[10] = 0;
    node[8] = (intptr_t)parent;
    TOUCH(Rules_FactPatternNetworkNextNode(node));
}

// ---- Rules_FactPatternNetworkToCodeClose ----
TEST(cov13_net, to_code_close_zero_result)
{
    CHECK_EQ(Rules_FactPatternNetworkToCodeClose(0, 5, 9), 0);
}

TEST(cov13_net, to_code_close_nonzero_result)
{
    /* v8 = a3 = a2, so a3 > *a2ptr(==a2) is always false; a5==NULL so the
       error-report branch is skipped and we fall to the formatted-write
       tail. Kept in its own test in case the tail path crashes. */
    TOUCH(Rules_FactPatternNetworkToCodeClose(1, 5, 9));
}

// ---- Rules_MaterializeMultifieldRange ----
TEST(cov13_mf, materialize_range_type_mismatch)
{
    static _DWORD buf[16];
    memset(buf, 0, sizeof buf);
    buf[1] = 0; /* not 4 -> early return 0 */
    CHECK(Rules_MaterializeMultifieldRange(buf) == 0);
}

TEST(cov13_mf, materialize_range_type_match)
{
    Mem_InitReserveBlock(0, 0);
    static _DWORD buf[16];
    memset(buf, 0, sizeof buf);
    buf[1] = 4;
    buf[3] = 1;
    buf[4] = 1;
    /* The recovered body reads an uninitialized local pointer here; call
       it in isolation so a crash doesn't affect other tests. */
    TOUCH(Rules_MaterializeMultifieldRange(buf));
}

// ---- Rules_PrintMultifieldRange ----
TEST(cov13_mf, print_range_no_loop_no_brackets)
{
    static unsigned char buf[512];
    memset(buf, 0, sizeof buf);
    static const char logical[] = "stdout";
    TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 1, 0));
}

TEST(cov13_mf, print_range_no_loop_with_brackets)
{
    static unsigned char buf[512];
    memset(buf, 0, sizeof buf);
    static const char logical[] = "stdout";
    TOUCH(Rules_PrintMultifieldRange((int)(intptr_t)logical, (int)(intptr_t)buf, 0, 1, 1));
}

// ---- Rules_CheckLiteralSlotValueConstraint ----
TEST(cov13_constraint, literal_slot_value_disabled)
{
    int saved = g_CLIPS_StaticConstraintCheckingFlag;
    g_CLIPS_StaticConstraintCheckingFlag = 0; /* force "checking disabled" -> safe early return */
    static int a1[8];
    memset(a1, 0, sizeof a1);
    CHECK_EQ(Rules_CheckLiteralSlotValueConstraint(a1, 0), 1);
    g_CLIPS_StaticConstraintCheckingFlag = saved;
}

// ---- Lexer_GetSlotByOrdinal ----
TEST(cov13_slots, get_slot_by_ordinal)
{
    static _DWORD head[16];
    static _DWORD n1[16];
    static _DWORD n2[16];
    memset(head, 0, sizeof head);
    memset(n1, 0, sizeof n1);
    memset(n2, 0, sizeof n2);

    /* Empty list -> immediate 0 */
    CHECK_EQ(Lexer_GetSlotByOrdinal((int)(intptr_t)head, 0), 0);

    head[5] = (intptr_t)n1; /* offset 20 */
    n1[4] = (intptr_t)n2;   /* offset 16 */
    n2[4] = 0;

    CHECK_EQ(Lexer_GetSlotByOrdinal((int)(intptr_t)head, 0), (intptr_t)n1);
    CHECK_EQ(Lexer_GetSlotByOrdinal((int)(intptr_t)head, 1), (intptr_t)n2);
    CHECK_EQ(Lexer_GetSlotByOrdinal((int)(intptr_t)head, 5), 0); /* walk off end */
}

// ---- Lexer_FindSymbolIndex ----
TEST(cov13_slots, find_symbol_index)
{
    static _DWORD head[16];
    static _DWORD n1[16];
    static _DWORD n2[16];
    memset(head, 0, sizeof head);
    memset(n1, 0, sizeof n1);
    memset(n2, 0, sizeof n2);

    CHECK_EQ(Lexer_FindSymbolIndex((int)(intptr_t)head, 42), 0); /* empty list */

    head[5] = (intptr_t)n1; /* offset 20 */
    n1[0] = 111;
    n1[4] = (intptr_t)n2; /* offset 16 */
    n2[0] = 222;
    n2[4] = 0;

    CHECK_EQ(Lexer_FindSymbolIndex((int)(intptr_t)head, 111), 1);
    CHECK_EQ(Lexer_FindSymbolIndex((int)(intptr_t)head, 222), 2);
    CHECK_EQ(Lexer_FindSymbolIndex((int)(intptr_t)head, 999), 0); /* not found */
}

// ---- Lexer_FindSlotWithIndex ----
TEST(cov13_slots, find_slot_with_index)
{
    static _DWORD head[16];
    static _DWORD n1[16];
    static _DWORD n2[16];
    static _DWORD idx;
    memset(head, 0, sizeof head);
    memset(n1, 0, sizeof n1);
    memset(n2, 0, sizeof n2);

    CHECK(Lexer_FindSlotWithIndex((int)(intptr_t)head, 42, &idx) == 0);
    CHECK_EQ((int)idx, -1);

    head[5] = (intptr_t)n1;
    n1[0] = 10;
    n1[4] = (intptr_t)n2;
    n2[0] = 20;
    n2[4] = 0;

    TOUCH(Lexer_FindSlotWithIndex((int)(intptr_t)head, 10, &idx));
    TOUCH(Lexer_FindSlotWithIndex((int)(intptr_t)head, 20, &idx));
    CHECK(Lexer_FindSlotWithIndex((int)(intptr_t)head, 999, &idx) == 0);
    CHECK_EQ((int)idx, -1);
}

// ---- Rules_CreateJoinPartialMatch ----
TEST(cov13_join, create_join_partial_match_no_action_no_join)
{
    Mem_InitReserveBlock(0, 0);

    static _DWORD a1buf[16];
    static _DWORD a2buf[16];
    static _DWORD a3buf[16];
    memset(a1buf, 0, sizeof a1buf);
    memset(a2buf, 0, sizeof a2buf);
    memset(a3buf, 0, sizeof a3buf);
    /* a1/a2 header counts = 0 so Rules_MergeMultifieldValues does no
       per-field copying; a3[9] (action) = 0 and a3[5] (join) = 0 so the
       activation/join-network branches are skipped. */
    a3buf[9] = 0;
    a3buf[5] = 0;

    TOUCH(Rules_CreateJoinPartialMatch(a1buf, a2buf, a3buf, 0.0));
}

// ---- Rules_FindLogicalDependencyEntry ----
TEST(cov13_dep, find_logical_dependency_entry_null_head)
{
    static _DWORD a1buf[16];
    memset(a1buf, 0, sizeof a1buf);
    a1buf[2] = 0; /* offset 8 = NULL */
    CHECK(Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf, 0) == 0);
}

TEST(cov13_dep, find_logical_dependency_entry_empty_count)
{
    static _DWORD a1buf[16];
    static _DWORD v3buf[16];
    memset(a1buf, 0, sizeof a1buf);
    memset(v3buf, 0, sizeof v3buf);
    v3buf[0] = 0; /* packed count = 0 -> immediately returned */
    a1buf[2] = (intptr_t)v3buf; /* offset 8 */
    CHECK((intptr_t)Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf, 0) == (intptr_t)v3buf);
}

TEST(cov13_dep, find_logical_dependency_entry_mismatch_then_null)
{
    static _DWORD a1buf[16];
    static _DWORD v3buf[16];
    static _DWORD a2buf[16];
    memset(a1buf, 0, sizeof a1buf);
    memset(v3buf, 0, sizeof v3buf);
    memset(a2buf, 0, sizeof a2buf);

    v3buf[0] = (1 << 6); /* packed count = 1 */
    v3buf[2] = 777;       /* value stored at index 2 */
    v3buf[1] = 0;         /* next = NULL (offset 4) */
    a2buf[2] = 555;        /* mismatching value at offset 8 */
    a1buf[2] = (intptr_t)v3buf;

    CHECK(Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf, (int)(intptr_t)a2buf) == 0);
}

TEST(cov13_dep, find_logical_dependency_entry_match)
{
    static _DWORD a1buf[16];
    static _DWORD v3buf[16];
    static _DWORD a2buf[16];
    memset(a1buf, 0, sizeof a1buf);
    memset(v3buf, 0, sizeof v3buf);
    memset(a2buf, 0, sizeof a2buf);

    v3buf[0] = (1 << 6); /* packed count = 1 */
    v3buf[2] = 777;
    a2buf[2] = 777; /* matching value at offset 8 */
    a1buf[2] = (intptr_t)v3buf;

    CHECK((intptr_t)Rules_FindLogicalDependencyEntry((int)(intptr_t)a1buf, (int)(intptr_t)a2buf) == (intptr_t)v3buf);
}

// ---- Rules_ArrayContainsValue ----
TEST(cov13_arr, array_contains_value)
{
    static _DWORD arr[16];
    static _DWORD val1, val2, val3;
    val1 = 111; val2 = 222; val3 = 333;
    memset(arr, 0, sizeof arr);

    arr[0] = 0; /* count 0 -> loop skipped */
    CHECK_EQ(Rules_ArrayContainsValue(999, arr), 0);

    arr[0] = (3 << 6); /* count 3 */
    arr[2] = (intptr_t)&val1;
    arr[3] = (intptr_t)&val2;
    arr[4] = (intptr_t)&val3;

    CHECK_EQ(Rules_ArrayContainsValue(222, arr), 1);
    CHECK_EQ(Rules_ArrayContainsValue(9999, arr), 0);
}

// ---- Rules_Dependencies / Rules_Dependents ----
TEST(cov13_dep, dependencies_and_dependents)
{
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    TOUCH(Rules_Dependencies(0.0));
    TOUCH(Rules_Dependents(0.0));
}

// ---- Rules_SetMultifieldErrorValue ----
TEST(cov13_mf, set_multifield_error_value)
{
    Mem_InitReserveBlock(0, 0);
    static unsigned char a1buf[64];
    memset(a1buf, 0, sizeof a1buf);
    /* Recovered body dereferences an uninitialized local pointer; kept in
       its own test in case of a crash. */
    TOUCH(Rules_SetMultifieldErrorValue((int)(intptr_t)a1buf));
}

// ---- Rules_ComputeFieldHashValue ----
TEST(cov13_hash, compute_field_hash_value)
{
    static _DWORD buf[16];
    memset(buf, 0, sizeof buf);
    buf[4] = 55;  /* offset 16 */
    buf[3] = 200; /* offset 12 */

    TOUCH(Rules_ComputeFieldHashValue(0, (int)(intptr_t)buf, 3));  /* case 0/1, a3>=0 */
    TOUCH(Rules_ComputeFieldHashValue(1, (int)(intptr_t)buf, -1)); /* case 0/1, a3<0 */
    TOUCH(Rules_ComputeFieldHashValue(2, (int)(intptr_t)buf, 5));  /* case 2/3/8, a3>=0 */
    TOUCH(Rules_ComputeFieldHashValue(3, (int)(intptr_t)buf, -1)); /* case 2/3/8, a3<0 */
    TOUCH(Rules_ComputeFieldHashValue(8, (int)(intptr_t)buf, 0));
    TOUCH(Rules_ComputeFieldHashValue(5, (int)(intptr_t)buf, 2));  /* case 5/6/7 */
    TOUCH(Rules_ComputeFieldHashValue(6, (int)(intptr_t)buf, -2));
    TOUCH(Rules_ComputeFieldHashValue(7, (int)(intptr_t)buf, 4));
    TOUCH(Rules_ComputeFieldHashValue(42, (int)(intptr_t)buf, 1));  /* default, a3>=0 */
    TOUCH(Rules_ComputeFieldHashValue(42, (int)(intptr_t)buf, -1)); /* default, a3<0 */
}

// ---- Lexer_SkipQuotedStringSpan ----
TEST(cov13_lex, skip_quoted_string_span)
{
    static const char s1[] = "\"rest";
    static _DWORD flag;

    CHECK_EQ(Lexer_SkipQuotedStringSpan((int)(intptr_t)s1, 0, &flag), 1);
    CHECK_EQ((int)flag, 1);

    {
    static const char s2[] = "ab\\ycd\"more";
    TOUCH(Lexer_SkipQuotedStringSpan((int)(intptr_t)s2, 0, &flag));
    }

    {
    static const char s3[] = "abcNOQUOTE";
    int r3 = Lexer_SkipQuotedStringSpan((int)(intptr_t)s3, 0, &flag);
    CHECK_EQ((int)flag, 0);
    TOUCH(r3);
    }
}

// ---- Lexer_SkipLineComment ----
TEST(cov13_lex, skip_line_comment)
{
    static const char s1[] = "abc\n";
    CHECK_EQ(Lexer_SkipLineComment((int)(intptr_t)s1, 0), 3);

    static const char s2[] = "abc\rXX";
    CHECK_EQ(Lexer_SkipLineComment((int)(intptr_t)s2, 0), 3);

    static const char s3[] = "abc";
    CHECK_EQ(Lexer_SkipLineComment((int)(intptr_t)s3, 0), 3);
}

// ---- Str_SkipInlineWhitespaceAt ----
TEST(cov13_lex, skip_inline_whitespace)
{
    static const char s1[] = "   abc";
    CHECK_EQ(Str_SkipInlineWhitespaceAt((int)(intptr_t)s1, 0), 3);

    static const char s2[] = "\t\f abc";
    CHECK_EQ(Str_SkipInlineWhitespaceAt((int)(intptr_t)s2, 0), 3);

    static const char s3[] = "abc";
    CHECK_EQ(Str_SkipInlineWhitespaceAt((int)(intptr_t)s3, 0), 0);
}

// ---- Lexer_ClassifyNextStdinChar ----
TEST(cov13_lex, classify_next_stdin_char)
{
    static unsigned char thisBuf[64];
    memset(thisBuf, 0, sizeof thisBuf);
    TOUCH(Lexer_ClassifyNextStdinChar(thisBuf));
}
