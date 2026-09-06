/* cov22: Rules class-bitmap / Class introspection-command / misc runtime cluster
 *
 * NOTE: this coverage TU is built as a normal 64-bit executable, but the
 * recovered functions treat addresses as 32-bit ints (the original binary's
 * pointer width). Any buffer whose address we truncate via
 * (int)(intptr_t)ptr / (_DWORD)(intptr_t)ptr MUST be `static` (or another
 * fixed/low address) rather than a stack local: this build is linked
 * -no-pie, so static/global data sits in the low, 32-bit-representable
 * part of the address space, while stack addresses are high 64-bit values
 * that get corrupted by the truncation and crash immediately. Genuine
 * pointer-typed parameters (e.g. unsigned __int16 *) are passed as real
 * pointers and are not affected, but every buffer here is still declared
 * `static` for consistency and safety. */

/* ---- Rules_IncrementBitmapRefCount ---- */
TEST(cov22_incbitmap, null_result)
{
    TOUCH(Rules_IncrementBitmapRefCount(0));
}

TEST(cov22_incbitmap, real_result)
{
    static _DWORD obj[64];
    memset(obj, 0, sizeof obj);
    TOUCH(Rules_IncrementBitmapRefCount((int)(intptr_t)obj));
    CHECK_EQ(*(int *)((char *)obj + 4), 1);
}

/* ---- Rules_DecrementBitmapRefCountIfSet ---- */
TEST(cov22_decbitmap, null_result)
{
    TOUCH(Rules_DecrementBitmapRefCountIfSet(0, 0));
}

TEST(cov22_decbitmap, positive_after_decrement)
{
    static _DWORD obj[64];
    memset(obj, 0, sizeof obj);
    *(int *)((char *)obj + 4) = 2; /* refcount 2 -> 1, skips error + ephemeral-hash branches */
    TOUCH(Rules_DecrementBitmapRefCountIfSet((int)(intptr_t)obj, 0));
}

TEST(cov22_decbitmap, zero_after_decrement_flag_set)
{
    static _DWORD obj[64];
    memset(obj, 0, sizeof obj);
    *(int *)((char *)obj + 4) = 1;         /* refcount 1 -> 0 */
    *(char *)((char *)obj + 12) |= 1;      /* bit0 set so AddEphemeralHashNode path is skipped */
    TOUCH(Rules_DecrementBitmapRefCountIfSet((int)(intptr_t)obj, 0));
}

/* ---- Rules_IsClassBitmapEmpty ---- */
TEST(cov22_bitmapempty, empty_via_loop)
{
    static unsigned __int16 buf[64];
    memset(buf, 0, sizeof buf);
    buf[0] = 8; /* v2 = (8>>3)+1 = 2, all following bytes zero -> loop decrements to 0 -> return 1 */
    CHECK_EQ(Rules_IsClassBitmapEmpty(buf), 1);
}

TEST(cov22_bitmapempty, nonempty_immediate)
{
    static unsigned __int16 buf[64];
    memset(buf, 0, sizeof buf);
    buf[0] = 8;
    ((unsigned char *)buf)[3] = 1; /* byte at v2+1 nonzero -> loop body never runs -> return 0 */
    CHECK_EQ(Rules_IsClassBitmapEmpty(buf), 0);
}

/* ---- Rules_AndClassBitmaps / Rules_OrClassBitmaps ---- */
TEST(cov22_andbitmaps, basic)
{
    static unsigned char a1buf[128];
    static unsigned __int16 a2buf[64];
    memset(a1buf, 0xFF, sizeof a1buf);
    memset(a2buf, 0, sizeof a2buf);
    a2buf[0] = 8; /* small bit count -> a couple loop iterations */
    TOUCH(Rules_AndClassBitmaps((int)(intptr_t)a1buf, a2buf));
}

TEST(cov22_orbitmaps, basic)
{
    static unsigned char a1buf[128];
    static unsigned __int16 a2buf[64];
    memset(a1buf, 0, sizeof a1buf);
    memset(a2buf, 0, sizeof a2buf);
    a2buf[0] = 8;
    TOUCH(Rules_OrClassBitmaps((int)(intptr_t)a1buf, a2buf));
}

/* ---- Rules_SetObjectPatternNegatedFlag ---- */
TEST(cov22_setnegflag, bit_clear_noop)
{
    static unsigned char obj[64];
    memset(obj, 0, sizeof obj); /* byte at +12 has bit3 clear -> if() skipped */
    TOUCH(Rules_SetObjectPatternNegatedFlag((int)(intptr_t)obj, 1));
}

TEST(cov22_setnegflag, bit_set_toggled)
{
    static unsigned char obj[64];
    memset(obj, 0, sizeof obj);
    obj[12] = 0x08; /* bit3 set -> if() taken */
    TOUCH(Rules_SetObjectPatternNegatedFlag((int)(intptr_t)obj, 1));
    TOUCH(Rules_SetObjectPatternNegatedFlag((int)(intptr_t)obj, 0));
}

/* ---- Rules_LinkClassToSuperclasses ---- */
TEST(cov22_linkclass, zero_count)
{
    static unsigned char cls[128];
    memset(cls, 0, sizeof cls); /* word at +34 == 0 -> if() skipped entirely */
    CHECK_EQ(Rules_LinkClassToSuperclasses((int)(intptr_t)cls), 0);
}

TEST(cov22_linkclass, one_superclass)
{
    /* Best-effort: exercises the loop/setup lines; the nested
       Class_InsertLinkEntry -> Mem_SmallBlockAlloc call depends on the
       decompiled heap-pool globals (dword_54DBA8) which default to zero in
       this harness, so this may crash deeper in the allocator - caught by
       the harness's signal handler. */
    static unsigned char cls[128];
    static unsigned char super[128];
    static _DWORD ptrArr[4];
    memset(cls, 0, sizeof cls);
    memset(super, 0, sizeof super);
    memset(ptrArr, 0, sizeof ptrArr);
    *(unsigned __int16 *)(cls + 34) = 1;               /* one superclass */
    ptrArr[0] = (_DWORD)(intptr_t)super;
    *(_DWORD *)(cls + 36) = (_DWORD)(intptr_t)ptrArr;  /* array of class ptrs */
    TOUCH(Rules_LinkClassToSuperclasses((int)(intptr_t)cls));
}

/* ---- Class_GenerateDefaultSlotHandlersAndFlag ---- */
TEST(cov22_gendefaultslot, both_flags_zero)
{
    static _DWORD obj[64];
    memset(obj, 0, sizeof obj); /* result[16]==0 and result[24]==0 -> both ifs skipped */
    TOUCH(Class_GenerateDefaultSlotHandlersAndFlag(obj));
}

TEST(cov22_gendefaultslot, second_loop_only)
{
    static _DWORD obj[64];
    static _DWORD handlers[32];
    memset(obj, 0, sizeof obj);
    memset(handlers, 0, sizeof handlers);
    obj[16] = 0;                        /* skip first (uninitialized-bound) loop */
    obj[22] = (_DWORD)(intptr_t)handlers;
    obj[24] = 2;                        /* run second loop twice */
    TOUCH(Class_GenerateDefaultSlotHandlersAndFlag(obj));
}

/* ---- Class_SuperclassPCommand / Class_SubclassPCommand ---- */
/* Best-effort: these route through Class_ParseTwoClassNameArgs ->
   Lexer_ParseValueList, which reads the parser argument-list global
   (dword_51A960). We seed it the same way tests/unit/cases/test_cov18.c does
   for similar router commands so the entry lines get exercised; deeper
   parser state (expression trees) is not modeled, so a crash further down
   is expected and caught by the harness. */
TEST(cov22_superclasspcmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_SuperclassPCommand(1.0));

    g_ClipsCurrentExpression = saved;
}

TEST(cov22_subclasspcmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_SubclassPCommand(1.0));

    g_ClipsCurrentExpression = saved;
}

/* ---- Class_SlotExistPCommand ---- */
TEST(cov22_slotexistpcmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    static int a1val;
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;
    a1val = 0;

    TOUCH(Class_SlotExistPCommand(&a1val, 1.0));

    g_ClipsCurrentExpression = saved;
}

/* ---- Class_LookupClassOrReportError ---- */
TEST(cov22_lookupclassorerror, not_found)
{
    /* Empty class hash table by default -> Class_LookupByQualifiedName
       returns 0 -> falls into Class_ReportLookupError, whose Output_Write
       calls all target off_51A614[0] with no router registered (default
       globals), which is a safe no-op path already exercised elsewhere. */
    static const char name[] = "Cov22NoSuchClass";
    TOUCH(Class_LookupClassOrReportError(0, (_BYTE *)name));
}

/* ---- Class_ParseClassNameArg ---- */
TEST(cov22_parseclassnamearg, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_ParseClassNameArg(1, 1.0));

    g_ClipsCurrentExpression = saved;
}

/* ---- Class_PrintSeparatorLine ---- */
TEST(cov22_printsepline, basic)
{
    /* a1 (router/logical-name) is only ever compared via the null-safe
       strcmp_ stub and passed through Output_Write, never dereferenced
       directly here, so any string works safely. */
    static const char routerName[] = "stdout";
    static char lineBuf[64];
    memset(lineBuf, 'X', sizeof lineBuf);
    TOUCH(Class_PrintSeparatorLine((int)(intptr_t)routerName, (int)(intptr_t)(lineBuf + 1), '-', 10));
}

TEST(cov22_printsepline, zero_width)
{
    static const char routerName[] = "stdout";
    static char lineBuf[64];
    memset(lineBuf, 'X', sizeof lineBuf);
    TOUCH(Class_PrintSeparatorLine((int)(intptr_t)routerName, (int)(intptr_t)(lineBuf + 1), '-', 2));
}

/* ---- Class_ClassSlotsCommand / Class_ClassSuperclassesCommand /
   Class_ClassSubclassesCommand / Class_GetDefmessageHandlerListCommand ---- */
TEST(cov22_classslotscmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_ClassSlotsCommand(1, 1.0));

    g_ClipsCurrentExpression = saved;
}

TEST(cov22_classsuperclassescmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_ClassSuperclassesCommand(1, 1.0));

    g_ClipsCurrentExpression = saved;
}

TEST(cov22_classsubclassescmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_ClassSubclassesCommand(1, 1.0));

    g_ClipsCurrentExpression = saved;
}

TEST(cov22_getdefmsghandlerlistcmd, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = g_ClipsCurrentExpression;
    memset(fakeParserCtx, 0, sizeof fakeParserCtx);
    memset(fakeExprNode, 0, sizeof fakeExprNode);
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    g_ClipsCurrentExpression = (int)(intptr_t)fakeParserCtx;

    TOUCH(Class_GetDefmessageHandlerListCommand(1, 1.0));

    g_ClipsCurrentExpression = saved;
}

/* ---- Class_IsAbstract ---- */
TEST(cov22_isabstract, flag_clear)
{
    static unsigned char obj[64];
    memset(obj, 0, sizeof obj);
    CHECK_EQ(Class_IsAbstract((int)(intptr_t)obj), 0);
}

TEST(cov22_isabstract, flag_set)
{
    static unsigned char obj[64];
    memset(obj, 0, sizeof obj);
    *(int *)(obj + 20) = 1 << 2; /* bit that ends up in the sign-extracted low bit */
    TOUCH(Class_IsAbstract((int)(intptr_t)obj));
}

/* ---- Math_CompareAbsToEpsilon ---- */
TEST(cov22_cmpabseps, basic)
{
    Math_CompareAbsToEpsilon();
    CHECK(1);
}

/* ---- Compiler_GenerateConstructTables ---- */
/* Best-effort: chains into several Compiler_Write*File helpers with
   decompiler-uninitialized filename/int arguments; likely crashes deep
   inside file I/O, caught by the harness. */
TEST(cov22_genconstructtables, basic)
{
    TOUCH(Compiler_GenerateConstructTables(0));
}

/* ---- Compiler_AssignModuleIndices ---- */
TEST(cov22_assignmoduleidx, empty_list)
{
    int saved = g_DefmoduleListHead;
    g_DefmoduleListHead = 0;
    CHECK_EQ(Compiler_AssignModuleIndices(), 0);
    g_DefmoduleListHead = saved;
}

TEST(cov22_assignmoduleidx, one_module)
{
    static _DWORD modBuf[16];
    int saved = g_DefmoduleListHead;
    memset(modBuf, 0, sizeof modBuf); /* offset+28 == 0 terminates after one iteration */
    g_DefmoduleListHead = (int)(intptr_t)modBuf;
    TOUCH(Compiler_AssignModuleIndices());
    g_DefmoduleListHead = saved;
}

/* ---- Rules_FetchJoinObjectSlotFieldSimple ---- */
/* Best-effort: v3 (the destination buffer passed to
   Rules_FetchObjectSlotFieldSimpleCore) is a decompiler-uninitialized
   local, so this may crash deep in the core fetch helper - caught safely. */
TEST(cov22_fetchjoinslotfield, basic)
{
    static unsigned char a1buf[64];
    static unsigned char v2buf[64];
    memset(a1buf, 0, sizeof a1buf);
    memset(v2buf, 0, sizeof v2buf);
    *(_DWORD *)(a1buf + 16) = (_DWORD)(intptr_t)v2buf;
    TOUCH(Rules_FetchJoinObjectSlotFieldSimple((int)(intptr_t)a1buf, 0));
}

/* ---- Fpu_ClearExceptions ---- */
TEST(cov22_fpuclearexc, basic)
{
    Fpu_ClearExceptions();
    CHECK(1);
}

/* ---- CRT_GetThreadMbcinfoPtr ---- */
TEST(cov22_crtmbcinfoptr, basic)
{
    /* g_CrtThreadDataAccessor defaults to CRT_GetBootstrapThreadData, which
       does no dereferencing (just returns a2 paired with a TLS value), so
       the pointer arithmetic here is safe for arbitrary ints. */
    TOUCH(CRT_GetThreadMbcinfoPtr(1, 2));
}

/* ---- Lexer_CheckDuplicateSlotName ---- */
TEST(cov22_checkdupslotname, null_a1)
{
    CHECK_EQ(Lexer_CheckDuplicateSlotName(0, 0x1234), 0);
}

TEST(cov22_checkdupslotname, immediate_match)
{
    static unsigned char node[64];
    static unsigned char nameHolder[64];
    memset(node, 0, sizeof node);
    memset(nameHolder, 0, sizeof nameHolder);
    *(_DWORD *)(node + 36) = (_DWORD)(intptr_t)nameHolder;
    CHECK_EQ(Lexer_CheckDuplicateSlotName((int)(intptr_t)node, (int)(intptr_t)nameHolder), 1);
}

TEST(cov22_checkdupslotname, chain_terminates_no_match)
{
    static unsigned char node1[64];
    memset(node1, 0, sizeof node1);
    *(_DWORD *)(node1 + 36) = 0x9999;   /* mismatches a2 */
    *(_DWORD *)(node1 + 64) = 0;        /* chain ends -> inner return 0 */
    CHECK_EQ(Lexer_CheckDuplicateSlotName((int)(intptr_t)node1, 0x1234), 0);
}

TEST(cov22_checkdupslotname, chain_match_on_second_node)
{
    static unsigned char node1[128];
    static unsigned char node2[128];
    static unsigned char nameHolder[64];
    memset(node1, 0, sizeof node1);
    memset(node2, 0, sizeof node2);
    memset(nameHolder, 0, sizeof nameHolder);
    *(_DWORD *)(node1 + 36) = 0x9999;                       /* mismatch on first node */
    *(_DWORD *)(node1 + 64) = (_DWORD)(intptr_t)node2;       /* chain to node2 */
    *(_DWORD *)(node2 + 36) = (_DWORD)(intptr_t)nameHolder;  /* match on second node */
    CHECK_EQ(Lexer_CheckDuplicateSlotName((int)(intptr_t)node1, (int)(intptr_t)nameHolder), 1);
}

/* ---- AST_PropagateDepthTag ---- */
TEST(cov22_propagatedepthtag, null_result)
{
    CHECK(AST_PropagateDepthTag(0, 5) == 0);
}

TEST(cov22_propagatedepthtag, single_node_no_children)
{
    static _DWORD node[32];
    memset(node, 0, sizeof node); /* i[16], i[14], i[17] all zero -> no recursion, no chain */
    TOUCH(AST_PropagateDepthTag(node, 7));
    CHECK_EQ(node[6], 7);
}

TEST(cov22_propagatedepthtag, with_children_and_chain)
{
    static _DWORD child1[32];
    static _DWORD child2[32];
    static _DWORD next[32];
    static _DWORD root[32];
    memset(child1, 0, sizeof child1);
    memset(child2, 0, sizeof child2);
    memset(next, 0, sizeof next);
    memset(root, 0, sizeof root);
    root[16] = (_DWORD)(intptr_t)child1; /* recurse into child1 */
    root[14] = (_DWORD)(intptr_t)child2; /* recurse into child2 */
    root[17] = (_DWORD)(intptr_t)next;   /* continue loop to sibling node */
    TOUCH(AST_PropagateDepthTag(root, 3));
}

/* ---- Module_RegisterBsaveBloadHandlers ---- */
/* Best-effort: registers callbacks through the decompiled heap-pool
   allocator (Mem_SmallBlockAlloc / Mem_HeapAllocWithRetry), which depends on
   pool globals (dword_54DBA8) that default to zero in this harness and are
   not modeled here; a crash deep in the allocator is expected and caught. */
TEST(cov22_registerbsaveblload, basic)
{
    TOUCH(Module_RegisterBsaveBloadHandlers());
}

/* ---- Rules_ResetConstraintParsedFlags ---- */
TEST(cov22_resetconstraintflags, basic)
{
    static _WORD buf[8];
    memset(buf, 0xFF, sizeof buf);
    TOUCH(Rules_ResetConstraintParsedFlags(buf));
    CHECK_EQ(buf[0], (_WORD)0xF800);
}

/* ---- Rules_IsConstraintAttributeKeyword ---- */
TEST(cov22_isconstraintkw, no_match)
{
    static const char s[] = "not-a-known-keyword";
    CHECK_EQ(Rules_IsConstraintAttributeKeyword((int)(intptr_t)s), 0);
}

TEST(cov22_isconstraintkw, match_type)
{
    static const char s[] = "type";
    TOUCH(Rules_IsConstraintAttributeKeyword((int)(intptr_t)s));
}
