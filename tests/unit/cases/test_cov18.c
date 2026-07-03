/* cov18: Rules construct-code-gen / module-record / Instance modify-duplicate cluster */

/* ---- Rules_WriteExpressionRefToCode ---- */
TEST(cov18_expr, null_node)
{
    /* a2 == NULL -> Output_WriteFormatted(a3,0,a1,...) ; a1==0 => safe immediate return */
    TOUCH(Rules_WriteExpressionRefToCode(0, 0, 1, 0));
}

TEST(cov18_expr, real_node)
{
    __int16 buf[64];
    memset(buf, 0, sizeof(buf));
    /* a1==0 keeps the Output_WriteFormatted call safe (fd param == 0) */
    TOUCH(Rules_WriteExpressionRefToCode(0, buf, 7, 1));
}

/* ---- Rules_RegisterConstructsToCFunction ---- */
TEST(cov18_registerctoc, basic)
{
    TOUCH(Rules_RegisterConstructsToCFunction());
}

/* ---- Rules_ConstructCodeFileOpen ---- */
TEST(cov18_codefileopen, a10_zero_a11_null)
{
    int counter = 0;
    TOUCH(Rules_ConstructCodeFileOpen(0, "cov18test", 3, "ext", &counter, 1, 2, 'x', "prefix", 0, 0));
}

TEST(cov18_codefileopen, a10_zero_a11_present)
{
    int counter = 0;
    const char *a11arr[3];
    a11arr[0] = "n1"; a11arr[1] = "n2"; a11arr[2] = "n3";
    TOUCH(Rules_ConstructCodeFileOpen(0, "cov18test2", 5, "ext2", &counter, 4, 5, 'y', "prefix2", 0, a11arr));
}

TEST(cov18_codefileopen, a10_nonzero_a11_present)
{
    int counter = 0;
    const char *a11arr[3];
    a11arr[0] = "n1b"; a11arr[1] = "n2b"; a11arr[2] = "n3b";
    TOUCH(Rules_ConstructCodeFileOpen(0, "cov18test3", 2, "ext3", &counter, 1, 1, 'z', "prefix3", 1, a11arr));
}

TEST(cov18_codefileopen, a1_nonzero_early_return)
{
    /* Exercises the if(a1) branch; may hit deep CRT stream code and crash - harness catches it. */
    unsigned char fakeEnv[256];
    memset(fakeEnv, 0, sizeof(fakeEnv));
    int counter = 0;
    TOUCH(Rules_ConstructCodeFileOpen((int)(intptr_t)fakeEnv, "cov18test4", 1, "ext4", &counter, 1, 1, 'w', "prefix4", 0, 0));
}

/* ---- Rules_WriteConstructHeaderToCode ---- */
TEST(cov18_writeheader, v16_zero)
{
    unsigned char a2buf[256];
    memset(a2buf, 0, sizeof(a2buf)); /* offset 16 == 0 -> else branch */
    TOUCH(Rules_WriteConstructHeaderToCode(0, (int)(intptr_t)a2buf, 3, 1, 2, 'c'));
}

TEST(cov18_writeheader, v16_nonzero)
{
    unsigned char a2buf[256];
    unsigned char nested[64];
    memset(a2buf, 0, sizeof(a2buf));
    memset(nested, 0, sizeof(nested));
    *(int *)(a2buf + 16) = (int)(intptr_t)nested; /* v16 != 0 -> if branch */
    *(int *)(nested + 12) = 5;
    TOUCH(Rules_WriteConstructHeaderToCode(0, (int)(intptr_t)a2buf, 3, 1, 2, 'c'));
}

/* ---- Rules_WriteConstructModuleItemHeaderToCode ---- */
TEST(cov18_writemoduleitemheader, basic)
{
    unsigned char a2buf[256];
    memset(a2buf, 0, sizeof(a2buf));
    TOUCH(Rules_WriteConstructModuleItemHeaderToCode(0, 0, 1, 2, 'q'));
}

/* ---- IO_RenameFile ---- */
TEST(cov18_renamefile, missing_src)
{
    TOUCH(IO_RenameFile("cov18_nonexistent_src.tmp", "cov18_nonexistent_dst.tmp", 5));
}

/* ---- Rules_ResetDataObjectValue ---- */
TEST(cov18_resetdataobj, basic)
{
    unsigned char buf[256];
    memset(buf, 0, sizeof(buf));
    TOUCH(Rules_ResetDataObjectValue((int)(intptr_t)buf));
}

/* ---- Rules_PrintJoinNetworkSharingReport ---- */
TEST(cov18_joinsharing, basic)
{
    TOUCH(Rules_PrintJoinNetworkSharingReport());
}

/* ---- Rules_ClearDefrules ---- */
TEST(cov18_cleardefrules, basic)
{
    TOUCH(Rules_ClearDefrules());
}

/* ---- Rules_SetInheritedFlagBit4 / Bit5 ---- */
TEST(cov18_inheritedflag, bit4_zero_chain)
{
    TOUCH(Rules_SetInheritedFlagBit4(1, 0));
}

TEST(cov18_inheritedflag, bit4_chain)
{
    unsigned char node1[64], node2[64];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    *(int *)(node1 + 48) = (int)(intptr_t)node2; /* node1 -> node2 -> NULL */
    *(int *)(node2 + 48) = 0;
    TOUCH(Rules_SetInheritedFlagBit4(0, (int)(intptr_t)node1));
}

TEST(cov18_inheritedflag, bit5_zero_chain)
{
    TOUCH(Rules_SetInheritedFlagBit5(1, 0));
}

TEST(cov18_inheritedflag, bit5_chain)
{
    unsigned char node1[64], node2[64];
    memset(node1, 0, sizeof(node1));
    memset(node2, 0, sizeof(node2));
    *(int *)(node1 + 48) = (int)(intptr_t)node2;
    *(int *)(node2 + 48) = 0;
    TOUCH(Rules_SetInheritedFlagBit5(1, (int)(intptr_t)node1));
}

/* ---- Rules_GetConstructNameSymbol ---- */
TEST(cov18_getconstructnamesym, basic)
{
    int val = 0x1234;
    CHECK_EQ(Rules_GetConstructNameSymbol((int)(intptr_t)&val), 0x1234);
}

/* ---- Rules_SetConstructNextInModule / Rules_GetConstructOwnerModule / Rules_GetModuleConstructListHead ---- */
TEST(cov18_constructnextinmodule, basic)
{
    unsigned char buf[64];
    memset(buf, 0, sizeof(buf));
    int r = (int)(intptr_t)buf;
    TOUCH(Rules_SetConstructNextInModule(r, 99));
    CHECK_EQ(*(int *)(buf + 16), 99);
}

TEST(cov18_getconstructownermodule, basic)
{
    unsigned char buf[64];
    memset(buf, 0, sizeof(buf));
    *(int *)(buf + 8) = 77;
    CHECK_EQ(Rules_GetConstructOwnerModule((int)(intptr_t)buf), 77);
}

TEST(cov18_getmoduleconstructlisthead, basic)
{
    unsigned char buf[64];
    memset(buf, 0, sizeof(buf));
    *(int *)(buf + 4) = 55;
    CHECK_EQ(Rules_GetModuleConstructListHead((int)(intptr_t)buf), 55);
}

/* ---- Class_Enum ---- */
TEST(cov18_classenum, a1_nonzero)
{
    unsigned char buf[64];
    memset(buf, 0, sizeof(buf));
    *(int *)(buf + 16) = 321;
    CHECK_EQ(Class_Enum((int)(intptr_t)buf, 0), 321);
}

TEST(cov18_classenum, a1_zero_result_zero)
{
    int saved = dword_51A9B0;
    dword_51A9B0 = 0;
    TOUCH(Class_Enum(0, 0));
    dword_51A9B0 = saved;
}

TEST(cov18_classenum, a1_zero_result_nonzero)
{
    static int leafBuf[8];
    static int itemArr[4];
    static int modRec[4];
    int saved = dword_51A9B0;
    memset(leafBuf, 0, sizeof(leafBuf));
    memset(itemArr, 0, sizeof(itemArr));
    memset(modRec, 0, sizeof(modRec));
    itemArr[0] = (int)(intptr_t)leafBuf;
    modRec[2] = (int)(intptr_t)itemArr; /* offset +8 */
    dword_51A9B0 = (int)(intptr_t)modRec;
    TOUCH(Class_Enum(0, 0));
    dword_51A9B0 = saved;
}

/* ---- Rules_GetModuleConstructData ---- */
TEST(cov18_getmoduleconstructdata, a1_zero)
{
    int saved = dword_51A9B0;
    dword_51A9B0 = 0;
    TOUCH(Rules_GetModuleConstructData(0, 0));
    dword_51A9B0 = saved;
}

TEST(cov18_getmoduleconstructdata, a1_nonzero)
{
    unsigned char buf[64];
    memset(buf, 0, sizeof(buf)); /* offset+8 == 0 -> Module_GetItem returns 0 safely */
    TOUCH(Rules_GetModuleConstructData((int)(intptr_t)buf, 0));
}

/* ---- sub_4A94D0_Impl / Rules_InitConstructModuleRecord ---- */
TEST(cov18_initmodulerecord, basic)
{
    static int fakeModRec[8];
    int savedList = dword_51A9BC;
    int savedCur = dword_51A9B0;
    unsigned char constructData[64];
    const char *name = "cov18_modname";

    memset(fakeModRec, 0, sizeof(fakeModRec));
    memset(constructData, 0, sizeof(constructData));
    fakeModRec[0] = (int)(intptr_t)name; /* name pointer compared via strcmp_ */
    fakeModRec[1] = 0;                   /* index used as a2 for Module_GetItem */
    fakeModRec[7] = 0;                   /* offset 28 -> next == NULL */

    dword_51A9BC = (int)(intptr_t)fakeModRec;
    dword_51A9B0 = 0; /* keeps Module_GetItem(0, idx) path safe */

    TOUCH(Rules_InitConstructModuleRecord((int)(intptr_t)name, (int)(intptr_t)constructData));
    TOUCH(sub_4A94D0_Impl((int)(intptr_t)name, (int)(intptr_t)constructData, (int)(intptr_t)constructData));

    dword_51A9BC = savedList;
    dword_51A9B0 = savedCur;
}

/* ---- Instance_InitializeInstanceFunction / Instance_MakeInstanceFunction ---- */
TEST(cov18_instanceinit, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = dword_51A960;

    memset(fakeParserCtx, 0, sizeof(fakeParserCtx));
    memset(fakeExprNode, 0, sizeof(fakeExprNode));
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    dword_51A960 = (int)(intptr_t)fakeParserCtx;

    TOUCH(Instance_InitializeInstanceFunction(1, 2, 1.0));

    dword_51A960 = saved;
}

TEST(cov18_instancemake, basic)
{
    static unsigned char fakeParserCtx[64];
    static __int16 fakeExprNode[64];
    int saved = dword_51A960;

    memset(fakeParserCtx, 0, sizeof(fakeParserCtx));
    memset(fakeExprNode, 0, sizeof(fakeExprNode));
    *(int *)(fakeParserCtx + 6) = (int)(intptr_t)fakeExprNode;
    dword_51A960 = (int)(intptr_t)fakeParserCtx;

    TOUCH(Instance_MakeInstanceFunction(1, 2, 1.0));

    dword_51A960 = saved;
}

/* ---- Instance_RegisterModifyAndDuplicateFunctions ---- */
TEST(cov18_registermodifydup, basic)
{
    TOUCH(Instance_RegisterModifyAndDuplicateFunctions());
}

/* ---- Instance_ModifyInstanceFunction / Instance_MessageModifyInstanceFunction ---- */
/* ---- Instance_DuplicateInstanceFunction / Instance_MessageDuplicateInstanceFunction ---- */
/* These pass uninitialized locals into nested Active* calls (decompiler artifact);
   we still exercise them for partial coverage - the harness catches any crash. */
TEST(cov18_modifyinstancefn, basic)
{
    TOUCH(Instance_ModifyInstanceFunction(1.0));
}

TEST(cov18_msgmodifyinstancefn, basic)
{
    TOUCH(Instance_MessageModifyInstanceFunction(1.0));
}

TEST(cov18_duplicateinstancefn, basic)
{
    TOUCH(Instance_DuplicateInstanceFunction(1.0));
}

TEST(cov18_msgduplicateinstancefn, basic)
{
    TOUCH(Instance_MessageDuplicateInstanceFunction(1.0));
}

/* ---- Instance_DirectDuplicateFunction / MessageDuplicateFunction / DirectModifyFunction / MessageModifyFunction ---- */
/* dword_51AD1C defaults to 0, taking the safe early-error-report-and-return path
   inside Rules_DuplicateInstanceCore / Rules_ModifyInstanceCore. */
TEST(cov18_directduplicatefn, basic)
{
    int a1buf[16];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Instance_DirectDuplicateFunction(a1buf, 1.0));
}

TEST(cov18_msgduplicatefn, basic)
{
    int a1buf[16];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Instance_MessageDuplicateFunction(a1buf, 1.0));
}

TEST(cov18_directmodifyfn, basic)
{
    unsigned char a1buf[64];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Instance_DirectModifyFunction((int)(intptr_t)a1buf, 1.0));
}

TEST(cov18_msgmodifyfn, basic)
{
    unsigned char a1buf[64];
    memset(a1buf, 0, sizeof(a1buf));
    TOUCH(Instance_MessageModifyFunction((int)(intptr_t)a1buf, 1.0));
}
