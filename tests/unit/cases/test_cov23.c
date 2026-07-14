/* cov23: Rules constraint-attribute parsing / object-pattern-network / CRT misc cluster
 *
 * NOTE: CRT_BeginThread and CRT_IsExtendedMbcsLeadByte are intentionally NOT
 * exercised here. Both reference CRT symbols (CreateThread, ismbclegal_)
 * that have no definition anywhere in this port (verified via a link probe);
 * calling them pulls the reference into the link and breaks the whole
 * coverage binary. They are left uncovered rather than break the build.
 *
 * NOTE: buffers whose address is stored into a narrow (32-bit _DWORD/int)
 * struct field and later read back as a pointer by the recovered code are
 * declared `static` here, not as plain locals. This process is 64-bit;
 * stack addresses run ~0x7fxxxxxxxxxx and get silently truncated when
 * squeezed through a 32-bit field, corrupting the pointer. `static` (and
 * global) data lives in the low, sub-4GB image (this target links
 * -no-pie), so the round trip through a 32-bit field is lossless. */

/* ---- Rules_TestConstraintAttributeParsedFlag ---- */
TEST(cov23_testparsedflag, type_bit)
{
    _DWORD bits[4];
    memset(bits, 0, sizeof(bits));
    bits[0] = 1; /* bit 0 set -> Type branch returns 1 */
    CHECK_EQ(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aType_0, bits), 1);
}

TEST(cov23_testparsedflag, all_known_names)
{
    _DWORD bits[4];
    memset(bits, 0, sizeof(bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aRange_0, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aCardinality, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedValues, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedSymbols, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedStrings, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedLexemes, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedInstanc, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedInteg_0, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedFloats, bits));
    TOUCH(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)aAllowedNumbers, bits));
}

TEST(cov23_testparsedflag, unmatched_name)
{
    _DWORD bits[4];
    memset(bits, 0, sizeof(bits));
    CHECK_EQ(Rules_TestConstraintAttributeParsedFlag((int)(intptr_t)"zzz-unmatched", bits), 1);
}

/* ---- Rules_ParseStandardConstraintAttribute ---- */
TEST(cov23_parsestdattr, already_parsed_branch)
{
    char a1buf[256];
    _DWORD a3buf[64];
    memset(a1buf, 0, sizeof(a1buf));
    memset(a3buf, 0, sizeof(a3buf));
    a3buf[0] = 1; /* Type bit set -> TestConstraintAttributeParsedFlag true */
    TOUCH(Rules_ParseStandardConstraintAttribute(
        a1buf, aType_0, (_BYTE *)a3buf, 0, 0));
}

TEST(cov23_parsestdattr, else_branch_mark_parsed)
{
    char a1buf[256];
    _DWORD a3buf[64];
    memset(a1buf, 0, sizeof(a1buf));
    memset(a3buf, 0, sizeof(a3buf)); /* bit clear -> false -> else branch */
    TOUCH(Rules_ParseStandardConstraintAttribute(
        a1buf, aType_0, (_BYTE *)a3buf, 0, 0));
}

/* ---- Rules_MarkConstraintAttributeParsed ---- */
TEST(cov23_markparsed, all_known_names)
{
    _BYTE a1buf[64];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aRange_0));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aType_0));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aCardinality));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedSymbols));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedStrings));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedLexemes));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedInteg_0));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedFloats));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedNumbers));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)aAllowedValues));
    TOUCH(Rules_MarkConstraintAttributeParsed(a1buf, (int)(intptr_t)"zzz-unmatched"));
}

/* ---- Rules_SetConstraintAllowedTypeFlag ---- */
TEST(cov23_setallowedtypeflag, sweep_values)
{
    static unsigned char a2buf[64];
    unsigned int vals[] = {0, 1, 2, 3, 4, 8, 0x67u, 0x6Eu, 111u, 0x68u};
    size_t i;
    for (i = 0; i < sizeof(vals) / sizeof(vals[0]); ++i) {
        memset(a2buf, 0, sizeof(a2buf));
        TOUCH(Rules_SetConstraintAllowedTypeFlag(vals[i], (int)(intptr_t)a2buf, 1));
        memset(a2buf, 0xFF, sizeof(a2buf));
        TOUCH(Rules_SetConstraintAllowedTypeFlag(vals[i], (int)(intptr_t)a2buf, 0));
    }
}

/* ---- Rules_GetAllowedAttributeTokenCode ---- */
TEST(cov23_getallowedtok, all_branches)
{
    CHECK_EQ(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedValues), 103);
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedSymbols));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedStrings));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedLexemes));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInteg_0));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedNumbers));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedInstanc));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)aAllowedFloats));
    TOUCH(Rules_GetAllowedAttributeTokenCode((int)(intptr_t)"zzz-unmatched"));
}

/* ---- Rules_GetTypeNameTokenCode ---- */
TEST(cov23_gettypenametok, all_branches)
{
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aSymbol_7));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aString_3));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aLexeme_1));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInteger_4));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aFloat_4));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aNumber_2));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstanceName_4));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstanceAddr_8));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aInstance_6));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aExternalAddr_1));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)aFactAddress_2));
    TOUCH(Rules_GetTypeNameTokenCode((int)(intptr_t)"zzz-unmatched"));
}

/* ---- Rules_MergeConstraintValueList ---- */
TEST(cov23_mergeconstraintvaluelist, no_match_chain)
{
    static unsigned char node1[64], node2[64], a3buf[64], a2buf[64];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    memset(a3buf, 0, sizeof(a3buf));
    memset(a2buf, 0, sizeof(a2buf));

    *(short *)(node1 + 0) = 1;   /* value != v3(999) */
    *(int *)(node1 + 10) = (int)(intptr_t)node2; /* next */
    *(short *)(node2 + 0) = 2;   /* value != v3(999) */
    /* node2 next stays NULL -> inner while hits "if(!i) return result;" safely */

    *(int *)(a3buf + 6) = (int)(intptr_t)node1; /* a3+6 -> head */

    TOUCH(Rules_MergeConstraintValueList(999, (int)(intptr_t)a2buf, (int)(intptr_t)a3buf));
}

/* ---- Rules_FindExistingJoinTestNode ---- */
TEST(cov23_findjointestnode, null_head)
{
    CHECK(Rules_FindExistingJoinTestNode(0, 1, 0, 0, 0, 0, 0, 0, 0, 0) == 0);
}

TEST(cov23_findjointestnode, no_match_via_fallback_chain)
{
    static _DWORD node1[16], node2[16];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    node1[4] = 111; /* mismatch vs a2=222 -> short-circuits before JoinTestNodeMatches */
    node1[7] = (int)(intptr_t)node2; /* fallback link */
    node2[4] = 333;
    node2[7] = 0;
    TOUCH(Rules_FindExistingJoinTestNode(node1, 222, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(cov23_findjointestnode, a4_nonzero_v10_8_null)
{
    _DWORD node1[16];
    memset(node1, 0, sizeof(node1));
    node1[4] = 111; /* mismatch vs a2=222 */
    node1[8] = 0;   /* traversal ptr NULL -> return 0 */
    TOUCH(Rules_FindExistingJoinTestNode(node1, 222, 0, 5, 0, 0, 0, 0, 0, 0));
}

/* ---- Rules_SetupDefinstancesBsaveBload ----
 * Pulls in Rules_RegisterBinaryItem, which indexes the Mem_ reserve arena
 * rooted at dword_54DBA8; that arena is NULL until Mem_InitReserveBlock
 * carves it out (same setup convention used by other cov batches). */
TEST(cov23_setupdefinstbsavebload, basic)
{
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_SetupDefinstancesBsaveBload());
}

/* ---- Compiler_CloseDefinstancesCodeFiles ----
 * a2/a1 nonzero drives Rules_ConstructCodeFileClose down its "handle is
 * open" path, which ultimately calls Output_WriteFormatted with our plain
 * int as the stream handle; the compat layer only hardens fclose_-style
 * handle lookups, not that formatted-write path, so this is expected to
 * crash past the line covered here. The harness isolates it. */
TEST(cov23_closedefinstcodefiles, all_zero)
{
    TOUCH(Compiler_CloseDefinstancesCodeFiles(0, 0, 3, 3));
}

TEST(cov23_closedefinstcodefiles, a2_nonzero)
{
    TOUCH(Compiler_CloseDefinstancesCodeFiles(0, 5, 7, 7));
}

TEST(cov23_closedefinstcodefiles, a1_nonzero_a2_zero)
{
    TOUCH(Compiler_CloseDefinstancesCodeFiles(9, 0, 4, 4));
}

/* ---- Parser_ParseInstanceQueryNoAction ----
 * Deep parser/lexer chain; inputs cannot be fully controlled safely. The
 * harness's crash isolation catches any segfault while still keeping the
 * coverage already accumulated by earlier tests in this run. */
TEST(cov23_parseinstqueryna, basic)
{
    static unsigned char a1buf[256];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Parser_ParseInstanceQueryNoAction((int)(intptr_t)a1buf, 0));
}

/* ---- Compiler_AssignObjectPatternAndRuleCodeIndices ---- */
TEST(cov23_assignobjpatruleidx, empty_lists)
{
    int savedRoot = g_Rules_ObjectPatternNetworkRoot;
    int savedList = g_ReactiveRuleListHead;
    g_Rules_ObjectPatternNetworkRoot = 0;
    g_ReactiveRuleListHead = 0;
    TOUCH(Compiler_AssignObjectPatternAndRuleCodeIndices());
    g_Rules_ObjectPatternNetworkRoot = savedRoot;
    g_ReactiveRuleListHead = savedList;
}

TEST(cov23_assignobjpatruleidx, single_node_each_list)
{
    static _DWORD patNode[16];
    static _DWORD ruleNode[16];
    int savedRoot = g_Rules_ObjectPatternNetworkRoot;
    int savedList = g_ReactiveRuleListHead;
    memset(patNode, 0, sizeof(patNode));
    memset(ruleNode, 0, sizeof(ruleNode));
    /* patNode: child(4)=0, sibling(7)=0, parent(5)=0 -> next-node() returns NULL after 1 step */
    g_Rules_ObjectPatternNetworkRoot = (int)(intptr_t)patNode;
    /* ruleNode: next(9)=0 -> loop stops after 1 step */
    g_ReactiveRuleListHead = (int)(intptr_t)ruleNode;
    TOUCH(Compiler_AssignObjectPatternAndRuleCodeIndices());
    g_Rules_ObjectPatternNetworkRoot = savedRoot;
    g_ReactiveRuleListHead = savedList;
}

/* ---- Rules_GetNextObjectPatternNode ---- */
TEST(cov23_getnextobjpatnode, child_branch)
{
    static _DWORD node[16], child[16];
    memset(node, 0, sizeof(node));
    memset(child, 0, sizeof(child));
    node[4] = (int)(intptr_t)child;
    CHECK(Rules_GetNextObjectPatternNode(node) == child);
}

TEST(cov23_getnextobjpatnode, sibling_branch)
{
    static _DWORD node[16], sibling[16];
    memset(node, 0, sizeof(node));
    memset(sibling, 0, sizeof(sibling));
    node[7] = (int)(intptr_t)sibling;
    CHECK(Rules_GetNextObjectPatternNode(node) == sibling);
}

TEST(cov23_getnextobjpatnode, parent_null_branch)
{
    _DWORD node[16];
    memset(node, 0, sizeof(node));
    /* child=0, sibling=0, parent=0 -> returns NULL */
    CHECK(Rules_GetNextObjectPatternNode(node) == 0);
}

TEST(cov23_getnextobjpatnode, parent_walk_then_sibling)
{
    static _DWORD node1[16], node2[16];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    node1[5] = (int)(intptr_t)node2; /* parent link */
    node2[7] = (int)(intptr_t)node2; /* sibling found on parent */
    CHECK(Rules_GetNextObjectPatternNode(node1) == node2);
}

/* ---- Compiler_WriteObjectPatternsAndRulesToCode ---- */
TEST(cov23_writeobjpatandrules, empty_networks)
{
    int savedRoot = g_Rules_ObjectPatternNetworkRoot;
    int savedList = g_ReactiveRuleListHead;
    g_Rules_ObjectPatternNetworkRoot = 0;
    g_ReactiveRuleListHead = 0;
    TOUCH(Compiler_WriteObjectPatternsAndRulesToCode("cov23test", 0, 0, 0, 0));
    g_Rules_ObjectPatternNetworkRoot = savedRoot;
    g_ReactiveRuleListHead = savedList;
}

/* ---- Rules_BuildSlotBoundTestNode / Rules_BuildSlotBoundTestExpression /
 *      Rules_BuildSlotRangeTestNode / mblen_ / Rules_BuildSlotUnboundTestExpression /
 *      mblen__0 ----
 * All are thin wrappers around Rules_BuildSlotConstraintBitmapTestNode /
 * Rules_BuildDualSlotConstraintBitmapTestNode, which contain decompiler
 * artifacts (stores through an uninitialized pointer register). The
 * wrapper's own call line is still recorded as covered even if the callee
 * later crashes; the harness isolates any such crash. Mem_InitReserveBlock
 * is primed first since the callees start with Mem_AllocArray. */
TEST(cov23_slotboundtestnode, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_BuildSlotBoundTestNode(0, (int)(intptr_t)slot));
}

TEST(cov23_slotboundtestexpr, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_BuildSlotBoundTestExpression((int)(intptr_t)slot));
}

TEST(cov23_slotrangetestnode, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_BuildSlotRangeTestNode((int)(intptr_t)slot, (int)(intptr_t)slot));
}

TEST(cov23_mblen, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(mblen_((int)(intptr_t)slot, 0));
}

TEST(cov23_slotunboundtestexpr, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_BuildSlotUnboundTestExpression((int)(intptr_t)slot));
}

TEST(cov23_mblen0, basic)
{
    static _DWORD slot[128];
    memset(slot, 0, sizeof(slot));
    Mem_InitReserveBlock(0, 0);
    TOUCH(mblen__0((int)(intptr_t)slot, (int)(intptr_t)slot));
}

/* ---- Rules_RegisterObjectPatternNetworkBinaryItem ---- */
TEST(cov23_registerobjpatnetbinitem, basic)
{
    Mem_InitReserveBlock(0, 0);
    TOUCH(Rules_RegisterObjectPatternNetworkBinaryItem());
}

/* ---- Class_FindClassLinkNode ---- */
TEST(cov23_findclasslinknode, match_second)
{
    static _DWORD node1[16], node2[16];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    node1[0] = 1;
    node1[3] = (int)(intptr_t)node2;
    node2[0] = 2;
    CHECK(Class_FindClassLinkNode(node1, 2) == node2);
}

TEST(cov23_findclasslinknode, no_match)
{
    _DWORD node1[16];
    memset(node1, 0, sizeof(node1));
    node1[0] = 1;
    CHECK(Class_FindClassLinkNode(node1, 999) == 0);
}

TEST(cov23_findclasslinknode, null_result)
{
    CHECK(Class_FindClassLinkNode(0, 5) == 0);
}

/* ---- AST_AccumulateFieldAccessTestChain ---- */
TEST(cov23_accumfieldaccesschain, single_node_untagged)
{
    static _DWORD node[32];
    signed int outA3 = -1, outA4 = -1;
    Mem_InitReserveBlock(0, 0);
    memset(node, 0, sizeof(node));
    node[0] = 100; /* field-type tag matching no branch in Dispatch -> safe no-op */
    /* offset 64 bytes = index 16 -> next pointer, 0 ends the chain */
    node[16] = 0;
    TOUCH(AST_AccumulateFieldAccessTestChain(node, 1, &outA3, &outA4));
}

TEST(cov23_accumfieldaccesschain, two_node_chain)
{
    static _DWORD node1[32], node2[32];
    signed int outA3 = -1, outA4 = -1;
    Mem_InitReserveBlock(0, 0);
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    node1[0] = 100;
    node1[16] = (int)(intptr_t)node2; /* next -> node2 */
    node2[0] = 100;
    node2[16] = 0; /* end chain */
    TOUCH(AST_AccumulateFieldAccessTestChain(node1, 0, &outA3, &outA4));
}

TEST(cov23_accumfieldaccesschain, null_head)
{
    signed int outA3 = -1, outA4 = -1;
    CHECK(AST_AccumulateFieldAccessTestChain(0, 1, &outA3, &outA4) == 0);
    CHECK_EQ(outA3, 0);
    CHECK_EQ(outA4, 0);
}

/* ---- CRT_StrToULongRadix / CRT_StrToXLong ----
 * CRT_StrToXLong's digit-accumulation loop reassigns its cursor via an
 * uninitialized register ("i = v11 + 1" in the recovered C, a decompiler
 * artifact) on every iteration, including the first. The only way to avoid
 * dereferencing that corrupted cursor is to make the loop bail out via
 * "v16 >= radix" on its very first character (i.e. give it a string with
 * no leading digit valid for the requested radix), which still exercises
 * the whitespace/sign-skip and radix auto-detection logic. Inputs that do
 * contain a real leading digit are included too (for the extra lines they
 * cover before the loop reassigns the cursor) and are expected to crash;
 * the harness isolates that. */
TEST(cov23_strtoulongradix, decimal_no_leading_digit_safe)
{
    int endpos = 0;
    CHECK_EQ(CRT_StrToULongRadix((unsigned __int8 *)"z", &endpos, 10), 0);
}

TEST(cov23_strtoulongradix, sign_no_leading_digit_safe)
{
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"-z", 0, 10));
}

TEST(cov23_strtoulongradix, hex_prefix_only_safe)
{
    int endpos = 0;
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"0x", &endpos, 0));
}

TEST(cov23_strtoulongradix, invalid_radix_low)
{
    int endpos = 0;
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"5", &endpos, 1));
}

TEST(cov23_strtoulongradix, invalid_radix_high)
{
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"5", 0, 40));
}

TEST(cov23_strtoulongradix, real_digit_expect_crash)
{
    int endpos = 0;
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"123", &endpos, 10));
}

TEST(cov23_strtoulongradix, hex_digit_expect_crash)
{
    TOUCH(CRT_StrToULongRadix((unsigned __int8 *)"0x1A", 0, 0));
}

/* ---- CRT_DigitCharToValue ---- */
TEST(cov23_digitchartoval, digit_fast_path)
{
    CHECK_EQ(CRT_DigitCharToValue('7', 0, 0), 7);
}

TEST(cov23_digitchartoval, lower_az_range)
{
    /* a3 feeds tolower_ directly (decompiler quirk); a1 just needs to be
       a non-digit so the fast path is skipped. */
    CHECK_EQ(CRT_DigitCharToValue('x', 0, 'B'), 11); /* tolower('B')='b'=0x62 -> 0x62-87 */
}

TEST(cov23_digitchartoval, mid_az_range)
{
    TOUCH(CRT_DigitCharToValue('x', 0, 'N'));
}

TEST(cov23_digitchartoval, fallback)
{
    CHECK_EQ(CRT_DigitCharToValue('x', 0, ' '), 37);
}

/* ---- CRT_DefaultZeroStub ---- */
TEST(cov23_defaultzerostub, basic)
{
    CHECK_EQ(CRT_DefaultZeroStub(), 0);
}
