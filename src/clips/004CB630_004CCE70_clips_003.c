/* Generated from src/recovered/rules/clips/004C82D0_methods.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004CB630) --------------------------------------------------------
int  Deffunction_WriteConstructCodeFiles(const char *fileName, const char *pathName, int fileID, int headerFP, int maxIndices)
{
  int codeFP; // esi
  int v6; // ecx
  int openedModuleFile; // eax
  int v8; // ecx
  int v9; // edi
  int theDeffunction; // edi
  int openedDeffunctionFile; // eax
  int v12; // ecx
  int v13; // esi
  int prevModuleCount; // ebx
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int deffunctionArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int deffunctionArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v23; // [esp+1Ch] [ebp-20h]
  const char *v24; // [esp+20h] [ebp-1Ch]
  int v25; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int v27; // [esp+2Ch] [ebp-10h]

  v23 = fileName;
  v24 = pathName;
  v25 = headerFP;
  v27 = fileID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  deffunctionArrayCount = 0;
  deffunctionArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeDffnxfu, 1);
  codeFP = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      openedModuleFile = Rules_ConstructCodeFileOpen(
             moduleFile,
             v23,
             v27,
             v24,
             &fileCount,
             moduleArrayVersion,
             v25,
             (char)aDeffunction_mo,
             **(const char ***)(g_DeffunctionCodeGeneratorItem + 20),
             0,
             0);
      v9 = openedModuleFile;
      if ( !openedModuleFile )
      {
        Deffunction_CloseCodeFiles(0, codeFP, v8, maxIndices);
        return 0;
      }
      Deffunction_WriteConstructHeader(openedModuleFile, Enum, maxIndices);
      moduleFile = Rules_ConstructCodeFileClose(v9, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDeffunction = Deffunction_EnumNext(0);
      if ( theDeffunction )
        break;
LABEL_6:
      prevModuleCount = moduleCount;
      Enum = Module_NextEnum(Enum);
      moduleCount = prevModuleCount + 1;
      ++moduleArrayCount;
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      openedDeffunctionFile = Rules_ConstructCodeFileOpen(
              codeFP,
              v23,
              v27,
              v24,
              &fileCount,
              deffunctionArrayVersion,
              v25,
              (char)aDeffunction_8,
              *(const char **)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4),
              0,
              0);
      v13 = openedDeffunctionFile;
      if ( !openedDeffunctionFile )
        break;
      Deffunction_WriteConstructBody(openedDeffunctionFile, theDeffunction, maxIndices, moduleCount);
      ++deffunctionArrayCount;
      codeFP = Rules_ConstructCodeFileClose(v13, &deffunctionArrayCount, maxIndices, &deffunctionArrayVersion, 0, 0);
      theDeffunction = Deffunction_EnumNext(theDeffunction);
      if ( !theDeffunction )
        goto LABEL_6;
    }
    Deffunction_CloseCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Deffunction_CloseCodeFiles(moduleFile, codeFP, v6, maxIndices);
    return 1;
  }
}
// 4CB7C9: variable 'v6' is possibly undefined
// 4CB7E0: variable 'v8' is possibly undefined
// 4CB7F8: variable 'v12' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB810) --------------------------------------------------------
int  Deffunction_CloseCodeFiles(int headerFP, int codeFP, int a3, int maxIndices)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-14h] BYREF
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  v7[3] = a3;
  result = codeFP;
  v6 = maxIndices;
  v7[0] = 0;
  if ( codeFP )
  {
    result = Rules_ConstructCodeFileClose(codeFP, &v6, maxIndices, v7, 0, 0);
    if ( !headerFP )
      return result;
    goto LABEL_5;
  }
  if ( headerFP )
  {
LABEL_5:
    v6 = maxIndices;
    return Rules_ConstructCodeFileClose(headerFP, &v6, maxIndices, v7, 0, 0);
  }
  return result;
}

//----- (004CB870) --------------------------------------------------------
int  Deffunction_WriteConstructHeader(int filePtr, int theModule, int maxIndices)
{
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  char v9; // [esp+0h] [ebp-Ch]
  char v10; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, filePtr, (int)asc_50B89C, v9);
  Rules_WriteConstructModuleItemHeaderToCode(filePtr, v4, v5, g_Clips_DeffunctionModuleItemIndex, *(_DWORD *)(*(_DWORD *)(g_DeffunctionCodeGeneratorItem + 20) + 4));
  return Output_WriteFormatted(v7, v6, filePtr, (int)asc_50B8A0, v10);
}
// 4CB87B: variable 'v9' is possibly undefined
// 4CB898: variable 'v4' is possibly undefined
// 4CB898: variable 'v5' is possibly undefined
// 4CB8A3: variable 'v7' is possibly undefined
// 4CB8A3: variable 'v6' is possibly undefined
// 4CB8A3: variable 'v10' is possibly undefined
// 54E6A8: using guessed type int dword_54E6A8;
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB8B0) --------------------------------------------------------
int  Deffunction_WriteConstructBody(int filePtr, int deffunction, int maxIndices, int moduleCount)
{
  int *v6; // eax
  DWORD moduleImage; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, deffunction, filePtr, (int)asc_50B89C, v15);
  v6 = *(int **)(g_DeffunctionCodeGeneratorItem + 20);
  moduleImage = *v6;
  Rules_WriteConstructHeaderToCode(filePtr, deffunction, v8, moduleCount, *v6, v6[1]);
  Output_WriteFormatted(v10, v9, filePtr, (int)a000_0, v16);
  Rules_ExpressionToCode(filePtr, *(__int16 **)(deffunction + 30), v11, moduleImage);
  Output_WriteFormatted(*(_DWORD *)(deffunction + 38), *(_DWORD *)(deffunction + 42), filePtr, (int)aDDD, *(_DWORD *)(deffunction + 34));
  return Output_WriteFormatted(v13, v12, filePtr, (int)asc_50B8A0, v17);
}
// 4CB8BD: variable 'v15' is possibly undefined
// 4CB8DD: variable 'v8' is possibly undefined
// 4CB8E8: variable 'v10' is possibly undefined
// 4CB8E8: variable 'v9' is possibly undefined
// 4CB8E8: variable 'v16' is possibly undefined
// 4CB8F5: variable 'v11' is possibly undefined
// 4CB91A: variable 'v13' is possibly undefined
// 4CB91A: variable 'v12' is possibly undefined
// 4CB91A: variable 'v17' is possibly undefined
// 54E8DC: using guessed type int dword_54E8DC;

//----- (004CB930) --------------------------------------------------------
int  Deffunction_ParseConstruct(int readSource)
{
  int (*v2)(void); // edx
  int deffunctionName; // edi
  int parameterList; // esi
  int v6; // edx
  int v7; // ecx
  __int16 *v8; // edx
  int v9; // [esp+0h] [ebp-30h] BYREF
  int minParams; // [esp+4h] [ebp-2Ch] BYREF
  int maxParams; // [esp+8h] [ebp-28h] BYREF
  int v12; // [esp+Ch] [ebp-24h] BYREF
  int errorFlag; // [esp+10h] [ebp-20h] BYREF
  int deffunction; // [esp+14h] [ebp-1Ch]

  errorFlag = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDeffunction_3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  deffunctionName = Rules_GetConstructNameAndComment(readSource, (int)g_Rules_ParsedConstructNameComment, (int (*)(void))Deffunction_FindByName, aDeffunction_4, v2, asc_50B8D8, 1, 1, 1);
  if ( !deffunctionName )
    return 1;
  if ( !Deffunction_ValidateNewName() )
    return 1;
  parameterList = Parser_ParseProcParameters(readSource, g_Rules_ParsedConstructNameComment, &v9, 0, &minParams, &maxParams, &errorFlag, 0);
  if ( errorFlag )
    return 1;
  deffunction = Deffunction_AddDeffunction(deffunctionName, 0, maxParams, minParams, 0, 1);
  if ( deffunction )
  {
    AST_Append(v7, v6);
    g_ClipsParseReturnContext = 1;
    if ( !Parser_ParseProcActions((int)aDeffunction_4, readSource, parameterList, v9, 0, 0, &v12, 0) )
    {
      AST_Free(parameterList);
      if ( !*(_DWORD *)(deffunction + 20) )
      {
        Rules_UnlinkListNode(deffunction);
        Deffunction_Free(deffunction);
        return 1;
      }
      return 1;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_Clips_DeffunctionEchoToken);
    IO_OutWriteToken(asc_50B8E8);
    Deffunction_AddDeffunction(deffunctionName, v8, maxParams, minParams, v12, 0);
    AST_Free(parameterList);
    return errorFlag;
  }
  else
  {
    AST_Free(parameterList);
    return 1;
  }
}
// 4CB98B: variable 'v2' is possibly undefined
// 4CBA06: variable 'v7' is possibly undefined
// 4CBA06: variable 'v6' is possibly undefined
// 4CBAB5: variable 'v8' is possibly undefined
// 54E87C: using guessed type int dword_54E87C;
// 54E8E0: using guessed type _DWORD dword_54E8E0[2];
// 54E8E8: using guessed type int dword_54E8E8;

//----- (004CBAD0) --------------------------------------------------------
signed int Deffunction_ValidateNewName()
{
  _BYTE *v0; // edx
  _BYTE *v1; // edx
  int conflictingGeneric; // eax
  _BYTE *v3; // edx
  int conflictModule; // esi
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int Name; // eax
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int existingDeffunction; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // ecx

  if ( Rules_FindConstructByName() )
  {
    Rules_PrintErrorID((int)aDffnxpsr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctionsAr, v12);
    return 0;
  }
  else if ( Rules_MakeSymbol(v0) )
  {
    Rules_PrintErrorID((int)aDffnxpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctions_3, v13);
    return 0;
  }
  else
  {
    conflictingGeneric = Defgeneric_LookupLocalOnly(v1);
    if ( conflictingGeneric )
    {
      conflictModule = *(_DWORD *)Rules_GetConstructOwnerModule(conflictingGeneric);
      if ( conflictModule == Module_GetCurrent() )
      {
        Rules_PrintErrorID((int)aDffnxpsr, 3, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunctions_4, v14);
      }
      else
      {
        Rules_PrintErrorID((int)aDffnxpsr, 5, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgeneric_4, v5);
        v7 = Rules_GetConstructNameString(v6);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aImportedFrom_0, v8);
        Name = Module_GetName(conflictModule);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], Name, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConflictsWit_0, v10);
      }
      return 0;
    }
    else
    {
      existingDeffunction = Deffunction_FindByName(v3, 0);
      if ( existingDeffunction && *(_DWORD *)(existingDeffunction + 24) )
      {
        Rules_PrintErrorID((int)aDfnxpsr, 4, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_5, v16);
        v18 = Rules_GetConstructNameString(v17);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v18, (int)g_IO_LogicalNameTable_WError[0]);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMayNotBeRedefi, v19);
        return 0;
      }
      else
      {
        return 1;
      }
    }
  }
}
// 4CBAE5: variable 'v0' is possibly undefined
// 4CBAF4: variable 'v1' is possibly undefined
// 4CBB32: variable 'v5' is possibly undefined
// 4CBB39: variable 'v6' is possibly undefined
// 4CBB57: variable 'v8' is possibly undefined
// 4CBB7C: variable 'v10' is possibly undefined
// 4CBBA3: variable 'v12' is possibly undefined
// 4CBBCA: variable 'v13' is possibly undefined
// 4CBBF1: variable 'v14' is possibly undefined
// 4CBBFF: variable 'v3' is possibly undefined
// 4CBC35: variable 'v16' is possibly undefined
// 4CBC3C: variable 'v17' is possibly undefined
// 4CBC5A: variable 'v19' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CBC70) --------------------------------------------------------
int  Deffunction_AddDeffunction(int name, __int16 *actions, int maxParams, int minParams, int numLocalVars, int headerFlag)
{
  int existingDeffunction; // eax
  int v9; // edx
  int deffunction; // esi
  _DWORD *freeListItem; // ebx
  _DWORD *newDeffunction; // ecx
  int v13; // edx
  __int16 watchValue; // ax
  int v16; // ecx
  __int16 *oldCode; // eax
  int v18; // ecx
  int oldPackedCode; // eax
  int v20; // edx
  signed int v21; // ecx
  int v22; // ecx
  char *ppForm; // eax
  int watchFlag; // [esp+4h] [ebp-14h]

  existingDeffunction = Deffunction_FindByName(*(_BYTE **)(name + 16), maxParams);
  watchFlag = v9;
  deffunction = existingDeffunction;
  if ( existingDeffunction )
  {
    watchFlag = Deffunction_GetWatchFlagField(existingDeffunction);
    *(_DWORD *)(v16 + 38) = maxParams;
    *(_DWORD *)(v16 + 42) = numLocalVars;
    oldCode = *(__int16 **)(v16 + 30);
    *(_DWORD *)(v16 + 34) = minParams;
    AST_DeinstallNodeChain(oldCode);
    oldPackedCode = *(_DWORD *)(v18 + 30);
    *(_DWORD *)(v18 + 20) = v20;
    AST_FreePackedNodeChain(oldPackedCode);
    *(_DWORD *)(v21 + 30) = 0;
    Rules_ReplaceConstructPPForm(v21, 0);
    Rules_UnlinkListNode(v22);
  }
  else
  {
    freeListItem = *(_DWORD **)(g_ClipsMemoryTable + 184);
    if ( freeListItem )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 184);
      *(_DWORD *)(g_ClipsMemoryTable + 184) = *freeListItem;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)0x2E);
    }
    Rules_InitConstructModuleRecord((int)aDeffunction_4, name);
    ++*(_DWORD *)(name + 4);
    *(_DWORD *)((char *)newDeffunction + 30) = 0;
    newDeffunction[5] = 0;
    newDeffunction[6] = 0;
    *(_DWORD *)((char *)newDeffunction + 34) = minParams;
    *(_DWORD *)((char *)newDeffunction + 38) = maxParams;
    deffunction = (int)newDeffunction;
    *(_DWORD *)((char *)newDeffunction + 42) = numLocalVars;
  }
  Rules_AppendConstructToModuleList(deffunction);
  if ( actions )
  {
    AST_InstallNodeChain(actions);
    *(_DWORD *)(deffunction + 20) = v13;
    *(_DWORD *)(deffunction + 30) = actions;
  }
  if ( watchFlag )
    watchValue = 1;
  else
    watchValue = g_Rules_WatchDeffunctions;
  Deffunction_SetWatchFlagField(watchValue, deffunction);
  if ( Mem_GetAllocFlag() || headerFlag )
    return deffunction;
  ppForm = Rules_CopyPPBuffer();
  Rules_ReplaceConstructPPForm(deffunction, (int)ppForm);
  return deffunction;
}
// 4CBC8B: variable 'v9' is possibly undefined
// 4CBCCC: variable 'v12' is possibly undefined
// 4CBD0C: variable 'v13' is possibly undefined
// 4CBD6B: variable 'v16' is possibly undefined
// 4CBD83: variable 'v18' is possibly undefined
// 4CBD86: variable 'v20' is possibly undefined
// 4CBD92: variable 'v21' is possibly undefined
// 4CBDA0: variable 'v22' is possibly undefined
// 51AAE8: using guessed type int dword_51AAE8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CBDD0) --------------------------------------------------------
int  Deffunction_CallDeffunction(int deffunction, _DWORD *argExprs, _DWORD *returnValue, double a4)
{
  int result; // eax
  int v8; // eax
  int nameString; // ebx
  int argCount; // eax
  int v11; // ecx
  int v12; // edx
  int savedDeffunction; // [esp+4h] [ebp-18h]
  int savedReentryFlag; // [esp+8h] [ebp-14h]

  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    savedReentryFlag = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    v8 = g_CurrentDeffunction;
    g_CurrentDeffunction = deffunction;
    ++g_ClipsCurrentEvaluationDepth;
    savedDeffunction = v8;
    ++*(_DWORD *)(deffunction + 24);
    nameString = Rules_GetConstructNameString(deffunction);
    argCount = AST_CountListNodes((int)argExprs);
    ProcParam_PushEvaluatedArgumentFrame(argExprs, argCount, v11, nameString, a4, (int (*)(void))Deffunction_PrintErrorContext);
    if ( g_ClipsEvaluationError )
    {
      --*(_DWORD *)(deffunction + 24);
      g_CurrentDeffunction = savedDeffunction;
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      return Rules_SetReentryGuardFlag(savedReentryFlag);
    }
    else
    {
      if ( *(_WORD *)(deffunction + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA48);
      Rules_ExecuteRuleActions(
        **(_DWORD **)(deffunction + 8),
        *(__int16 **)(deffunction + 30),
        returnValue,
        *(_DWORD *)(deffunction + 42),
        a4,
        (void (*)(void))Deffunction_PrintErrorContext);
      if ( *(_WORD *)(deffunction + 28) )
        Deffunction_PrintCallTrace((int)asc_50BA4C);
      LODWORD(g_ClipsHaltExecutionFlag) = 0;
      --*(_DWORD *)(deffunction + 24);
      ProcParam_PopFrame();
      g_CurrentDeffunction = savedDeffunction;
      --g_ClipsCurrentEvaluationDepth;
      Rules_PropagateReturnValueDepth((int)returnValue);
      Rules_RunPeriodicCleanup(0, v12);
      return Rules_SetReentryGuardFlag(savedReentryFlag);
    }
  }
  return result;
}
// 4CBE5D: variable 'v11' is possibly undefined
// 4CBEE0: variable 'v12' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B3E8: using guessed type int dword_51B3E8;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CBF30) --------------------------------------------------------
signed int __thiscall Deffunction_PrintErrorContext(void *this)
{
  int v1; // eax
  int v2; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDeffunction_9, (int)this);
  v1 = Rules_GetConstructNameString(g_CurrentDeffunction);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, (int)g_IO_LogicalNameTable_WError[0]);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__33, v2);
}
// 4CBF64: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B3E8: using guessed type int dword_51B3E8;

//----- (004CBF70) --------------------------------------------------------
signed int  Deffunction_PrintCallTrace(int a1)
{
  int v1; // ecx
  int currentModule; // eax
  int v3; // ecx
  _DWORD *v4; // edx
  int v5; // ecx
  int v6; // ecx
  int Name; // eax
  int v9; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aDfn, a1);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v1, v1);
  currentModule = Module_GetCurrent();
  if ( currentModule != *v4 )
  {
    Name = Module_GetName(**(_DWORD **)(g_CurrentDeffunction + 8));
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], Name, (int)g_IO_LogicalNameTable_WTrace[0]);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50BA6C, v9);
  }
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)g_CurrentDeffunction + 16), v3);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aEd_2, v5);
  Rules_PrintLongInteger(v6, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments((int)g_IO_LogicalNameTable_WTrace[0]);
}
// 4CBF8A: variable 'v1' is possibly undefined
// 4CBF9C: variable 'v4' is possibly undefined
// 4CC008: variable 'v9' is possibly undefined
// 4CBFAF: variable 'v3' is possibly undefined
// 4CBFBE: variable 'v5' is possibly undefined
// 4CBFCE: variable 'v6' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];
// 51A96C: using guessed type int dword_51A96C;
// 51B3E8: using guessed type int dword_51B3E8;

//----- (004CC010) --------------------------------------------------------
int Defglobal_RegisterConstructCommands()
{
  int v0; // ecx

  Rules_AddSaveFunction((int)aDefglobal_0, (int)Defglobal_SaveDefglobals, 40);
  Rules_AddResetFunction((int)aDefglobal_0, (int)Defglobal_ResetAllDefglobals, 50);
  Rules_RegisterHostFunction(aGetDefglobalLi, 109, v0, (int)Defglobal_GetDefglobalListCommand, (int)a01w_7);
  Rules_RegisterHostFunction(aUndefglobal, 118, (int)aUndefglobalcom, (int)Defglobal_UndefglobalCommand, (int)a11w_11);
  Rules_RegisterHostFunction(aDefglobalModul, 119, (int)aDefglobalmodul, (int)Defglobal_DefglobalModuleCommand, (int)a11w_11);
  Rules_RegisterHostFunction(aListDefglobals, 118, (int)aListdefglobals, (int)Defglobal_ListDefglobalsCommand, (int)a01w_7);
  Rules_RegisterHostFunction(aPpdefglobal, 118, (int)aPpdefglobalcom, (int)Defglobal_PpdefglobalCommand, (int)a11w_11);
  Rules_AddWatchItem((int)aGlobals, 0, 0, (int)&g_Rules_WatchGlobals, (int)Defglobal_SetWatchAll, (int)Defglobal_GetWatchAll);
  Rules_RegisterDefglobalBinaryItem();
  return Defglobal_RegisterCodeGeneratorItem();
}
// 4CC054: variable 'v0' is possibly undefined
// 51B3EC: using guessed type int dword_51B3EC;

//----- (004CC100) --------------------------------------------------------
signed int Defglobal_ResetAllDefglobals()
{
  signed int result; // eax

  result = Defglobal_GetResetGlobalsFlag();
  if ( result )
    return sub_4A9430_Impl((int (*)(int, intptr_t))Defglobal_ResetSingleDefglobal, g_ClipsDefglobalModuleItemId, 0, 1);
  return result;
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CC130) --------------------------------------------------------
int  Defglobal_ResetSingleDefglobal(int defglobal, int a2, double a3)
{
  _DWORD valueBuffer[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  if ( Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(defglobal + 52), valueBuffer, defglobal, a3) )
  {
    valueBuffer[1] = 2;
    valueBuffer[2] = g_ClipsFalseSymbol;
  }
  return Defglobal_SetValue(defglobal, valueBuffer, 0, a3);
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004CC170) --------------------------------------------------------
int  Defglobal_SaveDefglobals(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC180) --------------------------------------------------------
int __thiscall Defglobal_UndefglobalCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1A0) --------------------------------------------------------
int  Defglobal_DeleteConstructOrAll(int a1, int a2)
{
  return Rules_DeleteConstructOrAll(a1, g_ClipsDefglobalConstructType, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1B0) --------------------------------------------------------
_DWORD * Defglobal_GetDefglobalListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefglobalConstructType, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC1F0) --------------------------------------------------------
int __thiscall Defglobal_DefglobalModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC210) --------------------------------------------------------
int __thiscall Defglobal_PpdefglobalCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDefglobalConstructType);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC240) --------------------------------------------------------
int  Defglobal_ListDefglobalsCommand(int logicalName, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefglobalConstructType, logicalName, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC280) --------------------------------------------------------
int  Defglobal_GetWatchFlagField(int defglobal)
{
  return *(_DWORD *)(defglobal + 20) & 1;
}

//----- (004CC290) --------------------------------------------------------
int  Defglobal_SetWatchFlagField(char newState, int defglobal)
{
  int result; // eax

  *(_BYTE *)(defglobal + 20) &= ~1u;
  result = newState & 1;
  *(_DWORD *)(defglobal + 20) |= result;
  return result;
}

//----- (004CC2A0) --------------------------------------------------------
signed int  Defglobal_SetWatchAll(int a1, int a2, double a3)
{
  return Rules_ApplyWatchFlagCommand(g_ClipsDefglobalConstructType, a1, (int)Defglobal_GetWatchFlagField, a2, a3, (void (*)(void))Defglobal_SetWatchFlagField);
}
// 4CC280: using guessed type int sub_4CC280();
// 4CC290: using guessed type int sub_4CC290();
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC2C0) --------------------------------------------------------
signed int  Defglobal_GetWatchAll(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(g_ClipsDefglobalConstructType, a1, (int)Defglobal_GetWatchFlagField, a2, a3, (void (*)(void))Defglobal_SetWatchFlagField);
}
// 4CC280: using guessed type int sub_4CC280();
// 4CC290: using guessed type int sub_4CC290();
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004CC2E0) --------------------------------------------------------
signed int Defglobal_RegisterResetGlobalsCommands()
{
  Rules_RegisterHostFunction(aSetResetGlobal, 98, (int)aSetresetglobal, (int)Defglobal_SetResetGlobalsCommand, (int)a11_5);
  Rules_RegisterHostFunction(aGetResetGlobal, 98, (int)aGetresetglobal, (int)Defglobal_GetResetGlobalsCommand, (int)a00_11);
  return Rules_RegisterHostFunction(aShowDefglobals, 118, (int)aShowdefglobals, (int)Defglobal_ShowDefglobalsCommand, (int)a01w_8);
}

//----- (004CC350) --------------------------------------------------------
int  Defglobal_SetResetGlobalsCommand(int a1, double a2)
{
  int tokenType; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // [esp-4h] [ebp-28h] BYREF
  __int64 argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  tokenType = Lexer_TokenExpect(1);
  v5 = v4;
  if ( tokenType == -1 )
    return v4;
  Rules_RtnUnknown(1, &v7, a2);
  g_DefglobalResetGlobalsFlag = argValue != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 4CC36E: variable 'v4' is possibly undefined
// 51B3F0: using guessed type int dword_51B3F0;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CC3E0) --------------------------------------------------------
int Defglobal_GetResetGlobalsCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  return v0;
}
// 4CC3FA: variable 'v0' is possibly undefined
// 51B3F0: using guessed type int dword_51B3F0;

//----- (004CC400) --------------------------------------------------------
int Defglobal_GetResetGlobalsFlag()
{
  return g_DefglobalResetGlobalsFlag;
}
// 51B3F0: using guessed type int dword_51B3F0;

//----- (004CC410) --------------------------------------------------------
void  Defglobal_ShowDefglobalsCommand(int a1, double a2, int a3)
{
  int tokenType; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int *moduleArg; // edx
  _DWORD v8[4]; // [esp+0h] [ebp-10h] BYREF

  v8[2] = a1;
  v8[1] = a3;
  tokenType = Lexer_TokenExpect(1);
  if ( tokenType != -1 )
  {
    if ( tokenType == 1 )
    {
      moduleArg = Rules_GetModuleNameArg(1, v4, v8, a2);
      if ( !v8[0] )
        Defglobal_ShowDefglobalsForModules(0, (int)moduleArg);
    }
    else
    {
      v5 = Module_GetCurrent();
      Defglobal_ShowDefglobalsForModules(v6, v5);
    }
  }
}
// 4CC440: variable 'v6' is possibly undefined
// 4CC455: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CC480) --------------------------------------------------------
void __fastcall Defglobal_ShowDefglobalsForModules(int a1, int theModule)
{
  int Enum; // edi
  int printModuleName; // esi
  int Name; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int defglobal; // ebx
  int v9; // ecx

  Enum = theModule;
  printModuleName = 0;
  if ( !theModule )
  {
    printModuleName = 1;
    Enum = Module_NextEnum(0);
  }
  while ( Enum )
  {
    if ( printModuleName )
    {
      Name = Module_GetName(Enum);
      Output_Write(v5, Name, v5);
      Output_Write(v6, (int)asc_50BBE4, v6);
    }
    defglobal = *(_DWORD *)(Module_GetItem(Enum, g_ClipsDefglobalModuleItemId) + 4);
    if ( defglobal )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( printModuleName )
          Output_Write(v7, (int)asc_50BBE8, v7);
        Defglobal_PrintDefglobalValue(v7, defglobal);
        Output_Write(v9, (int)asc_50BBEC, v9);
        defglobal = *(_DWORD *)(defglobal + 16);
        if ( !defglobal )
          goto LABEL_11;
      }
      return;
    }
LABEL_11:
    if ( !printModuleName )
      return;
    Enum = Module_NextEnum(Enum);
  }
}
// 4CC4A9: variable 'v5' is possibly undefined
// 4CC4B5: variable 'v6' is possibly undefined
// 4CC4E2: variable 'v7' is possibly undefined
// 4CC4F7: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CC530) --------------------------------------------------------
signed int  Defglobal_PrintDefglobalValue(int logicalName, int defglobal)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  Output_Write(logicalName, (int)aDefglobalVariablePrefix, logicalName);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)defglobal + 16), v3);
  Output_Write(v4, (int)asc_50BBF4, v4);
  return Rules_PrintDataObject(v5, defglobal + 28);
}
// 4CC547: variable 'v3' is possibly undefined
// 4CC553: variable 'v4' is possibly undefined
// 4CC55D: variable 'v5' is possibly undefined

//----- (004CC570) --------------------------------------------------------
int  Defglobal_ParseDefglobalConstruct(int readSource, double a2)
{
  int tokenPrimed; // ebx
  int v5; // eax
  char *Name; // eax
  int v7; // eax
  char *v8; // eax
  int v10; // ecx
  int v11; // edx
  int tokenType; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+4h] [ebp-18h]
  char *v14; // [esp+8h] [ebp-14h]
  _DWORD constructError[4]; // [esp+Ch] [ebp-10h] BYREF

  tokenPrimed = 1;
  constructError[0] = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefglobal_5);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  Parser_NextToken(readSource, (int)&tokenType);
  if ( tokenType == 2 )
  {
    tokenPrimed = 0;
    if ( Rules_FindModuleSeparator(*(_BYTE **)(v13 + 16)) )
    {
      Parser_ReportSyntaxError();
      return 1;
    }
    if ( !Module_FindByName(*(_BYTE **)(v13 + 16)) )
    {
      Rules_ReportCantFindItem(v10, *(_DWORD *)(v13 + 16));
      return 1;
    }
    IO_OutWriteToken(asc_50BC20);
    Module_SetCurrent(v11);
  }
  else
  {
    IO_OutNewline();
    v5 = Module_GetCurrent();
    Name = (char *)Module_GetName(v5);
    IO_OutWriteToken(Name);
    IO_OutWriteToken(asc_50BC20);
    IO_OutWriteToken(v14);
  }
  while ( Lexer_ParseDefglobal(readSource, constructError, &tokenType, tokenPrimed, a2) )
  {
    Rules_FlushPPBuffer();
    IO_OutWriteToken(aDefglobal_5);
    v7 = Module_GetCurrent();
    v8 = (char *)Module_GetName(v7);
    IO_OutWriteToken(v8);
    tokenPrimed = 0;
    IO_OutWriteToken(asc_50BC20);
  }
  return constructError[0];
}
// 4CC671: variable 'v11' is possibly undefined
// 4CC69D: variable 'v10' is possibly undefined

//----- (004CC6C0) --------------------------------------------------------
int  Lexer_ParseDefglobal(int readSource, _DWORD *errorFlag, _DWORD *token, int tokenPrimed, double a5)
{
  int globalSymbol; // ebp
  int v8; // ecx
  char *v9; // edx
  int v10; // ecx
  int v11; // ecx
  char *v12; // edx
  _BYTE *v13; // ebx
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int result; // eax
  __int16 *valueExpr; // ebx
  _DWORD *v20; // edx
  int v21; // ecx
  int v22; // edx

  if ( !tokenPrimed )
    Parser_NextToken(readSource, (int)token);
  if ( *token == 101 )
    return 0;
  if ( *token != 13 )
    goto LABEL_16;
  globalSymbol = token[1];
  IO_OutWriteToken(asc_50BC20);
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
  {
    if ( Defglobal_FindNextChanged() )
      v9 = aRedefiningDefg;
    else
      v9 = aDefiningDefglo;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(globalSymbol + 16), v10);
    v12 = asc_50BC64;
    goto LABEL_10;
  }
  if ( Rules_GetLoadInProgress() )
  {
    v12 = asc_50BC68;
LABEL_10:
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v12, v11);
  }
  v13 = *(_BYTE **)(globalSymbol + 16);
  v14 = Module_GetCurrent();
  if ( Rules_FindImportExportConflict(aDefglobal_2, v14, v13) )
  {
    Lexer_WarnImpliedTemplate((int)aDefglobal_2, *(_DWORD *)(globalSymbol + 16), 0);
    *errorFlag = 1;
    return 0;
  }
  Parser_NextToken(readSource, v15);
  if ( strcmp_(v16, asc_50BC6C) )
  {
LABEL_16:
    Parser_ReportSyntaxError();
    *errorFlag = 1;
    return 0;
  }
  IO_OutWriteToken(asc_50BC20);
  result = Parser_ParseSingleExpression(readSource, 0, v17);
  valueExpr = (__int16 *)result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm(valueExpr, v20, v21, a5) )
    {
      AST_Free((int)valueExpr);
      *errorFlag = 1;
      return 0;
    }
    else
    {
      IO_OutWriteToken(asc_50BC70);
      Defglobal_AddDefglobal(globalSymbol, v22, valueExpr);
      return 1;
    }
  }
  else
  {
    *errorFlag = 1;
  }
  return result;
}
// 4CC6E0: simplified comparisons for 'edx.4': ==F || !=D became !=D
// 4CC6D2: variable 'a3' is possibly undefined
// 4CC735: variable 'v8' is possibly undefined
// 4CC742: variable 'v10' is possibly undefined
// 4CC751: variable 'v11' is possibly undefined
// 4CC776: variable 'v15' is possibly undefined
// 4CC783: variable 'v16' is possibly undefined
// 4CC79A: variable 'v17' is possibly undefined
// 4CC81D: variable 'v20' is possibly undefined
// 4CC81D: variable 'v21' is possibly undefined
// 4CC84A: variable 'v22' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A61C: using guessed type char *off_51A61C[3];

//----- (004CC860) --------------------------------------------------------
char * Defglobal_AddDefglobal(int globalName, int valueData, __int16 *valueExpr)
{
  int *foundDefglobal; // eax
  int *existingDefglobal; // ebx
  int isNew; // ebp
  _DWORD *freeList; // ebx
  signed int allocatedStruct; // eax
  _DWORD *defglobal; // ecx
  int v11; // ecx
  int valueType; // eax
  int v13; // edx
  int v14; // ecx
  __int16 *v15; // eax
  int v16; // ecx
  _BYTE *v17; // edx
  _DWORD *v18; // ecx
  char watchValue; // al
  char *result; // eax
  int v21; // ecx
  int moduleItem; // eax
  int whichModule; // eax
  int v24; // ecx
  int watchFlag; // [esp+0h] [ebp-14h]

  foundDefglobal = Defglobal_FindNextChanged();
  existingDefglobal = foundDefglobal;
  isNew = 0;
  watchFlag = 0;
  if ( foundDefglobal )
  {
    Rules_FreeConstructHeaderString(foundDefglobal, (int)foundDefglobal);
    watchFlag = existingDefglobal[5] & 1;
  }
  else
  {
    freeList = *(_DWORD **)(g_ClipsMemoryTable + 224);
    isNew = 1;
    if ( freeList )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 224);
      *(_DWORD *)(g_ClipsMemoryTable + 224) = *freeList;
      allocatedStruct = g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedStruct = Mem_HeapAllocWithRetry((_DWORD *)0x38);
    }
    defglobal = (_DWORD *)allocatedStruct;
  }
  if ( !isNew )
  {
    Rules_ValueDeinstall((int)(defglobal + 7), (int)defglobal);
    if ( *(_DWORD *)(v11 + 32) == 4 )
      Rules_ReturnMultifieldToPool(*(_DWORD **)(v11 + 36));
    AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 52), v11);
  }
  valueType = *(_DWORD *)(valueData + 4);
  defglobal[8] = valueType;
  if ( valueType == 4 )
    Rules_AssignMultifieldRangeCopy(defglobal + 7, valueData);
  else
    defglobal[9] = *(_DWORD *)(valueData + 8);
  Rules_ValueInstall((int)(defglobal + 7), (int)defglobal);
  v15 = AST_AddHashedNodeChain(valueExpr, v13, v14);
  *(_DWORD *)(v16 + 52) = v15;
  AST_Free((int)valueExpr);
  g_Defglobal_ChangedFlag = 1;
  if ( watchFlag )
    watchValue = 1;
  else
    watchValue = g_Rules_WatchGlobals;
  *v17 &= ~1u;
  *(_DWORD *)v17 |= watchValue & 1;
  *v18 = globalName;
  ++*(_DWORD *)(globalName + 4);
  IO_OutWriteToken(asc_50BC64);
  result = (char *)Mem_GetAllocFlag();
  if ( result != (char *)1 )
  {
    result = Rules_CopyPPBuffer();
    *(_DWORD *)(v21 + 4) = result;
    *(_BYTE *)(v21 + 20) |= 2u;
    if ( !isNew )
      return result;
    goto LABEL_21;
  }
  *(_DWORD *)(v21 + 4) = 0;
  *(_BYTE *)(v21 + 20) |= 2u;
  if ( isNew )
  {
LABEL_21:
    *(_DWORD *)(v21 + 24) = 0;
    moduleItem = Module_FindItemByName((int)aDefglobal_2);
    whichModule = Module_GetItem(0, *(_DWORD *)(moduleItem + 4));
    *(_DWORD *)(v24 + 8) = whichModule;
    return (char *)Rules_AppendConstructToModuleList(v24);
  }
  return result;
}
// 4CC8AA: variable 'v10' is possibly undefined
// 4CC8B2: variable 'v11' is possibly undefined
// 4CC8C8: variable 'a2' is possibly undefined
// 4CC8E7: variable 'v13' is possibly undefined
// 4CC8E7: variable 'v14' is possibly undefined
// 4CC8EC: variable 'v16' is possibly undefined
// 4CC911: variable 'v17' is possibly undefined
// 4CC919: variable 'v18' is possibly undefined
// 4CC936: variable 'v21' is possibly undefined
// 4CC9BF: variable 'v24' is possibly undefined
// 51AB1C: using guessed type int dword_51AB1C;
// 51B3EC: using guessed type int dword_51B3EC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CC9E0) --------------------------------------------------------
signed int  Defglobal_ResolveGlobalVariableReference(int exprNode, int a2)
{
  int defglobal; // eax
  _DWORD lookupBuffer[5]; // [esp+0h] [ebp-14h] BYREF

  lookupBuffer[3] = a2;
  defglobal = Rules_FindImportExportConstruct(aDefglobal_2, lookupBuffer, *(_BYTE **)(*(_DWORD *)(exprNode + 2) + 16), 1, 0);
  if ( defglobal )
  {
    if ( lookupBuffer[0] > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)aDefglobal_2, *(_DWORD *)(*(_DWORD *)(exprNode + 2) + 16));
      return 0;
    }
    else
    {
      *(_WORD *)exprNode = 60;
      *(_DWORD *)(exprNode + 2) = defglobal;
      return 1;
    }
  }
  else
  {
    Defglobal_PrintUndefinedVariableError();
    return 0;
  }
}

//----- (004CCA50) --------------------------------------------------------
signed int Defglobal_PrintUndefinedVariableError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aGloblpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGlobalVariable, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasReferencedB, v2);
}
// 4CCA70: variable 'v0' is possibly undefined
// 4CCA7C: variable 'v1' is possibly undefined
// 4CCA8B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004CCAA0) --------------------------------------------------------
int Defglobal_RegisterCodeGeneratorItem()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefglobal_3, 0, (int)Defglobals_ResetCallback, (int)Defglobal_AssignModuleItemIds, (int)Defglobal_WriteConstructsToCCode, 2);
  g_ClipsDefglobalCodeGenItem = result;
  return result;
}
// 4CCAE0: using guessed type int sub_4CCAE0();
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCAD0) --------------------------------------------------------
signed int Defglobal_AssignModuleItemIds()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004CCAE0) --------------------------------------------------------
int Defglobals_ResetCallback(int filePtr)
{
  return ((int (__cdecl *)(int, const char *))Output_WriteFormatted)(filePtr, "   ResetDefglobals();\n");
}

//----- (004CCAF0) --------------------------------------------------------
int  Defglobal_WriteConstructsToCCode(const char *fileName, const char *pathName, int fileID, int headerFP, int maxIndices)
{
  int codeFP; // esi
  int v6; // ecx
  int openedModuleFile; // eax
  int v8; // ecx
  int v9; // edi
  int theDefglobal; // edi
  int openedDefglobalFile; // eax
  int v12; // ecx
  int v13; // esi
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int defglobalArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int defglobalArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v22; // [esp+1Ch] [ebp-20h]
  const char *v23; // [esp+20h] [ebp-1Ch]
  int v24; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int v26; // [esp+2Ch] [ebp-10h]

  v22 = fileName;
  v23 = pathName;
  v24 = headerFP;
  v26 = fileID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  defglobalArrayCount = 0;
  defglobalArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeGloblde, 1);
  codeFP = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      openedModuleFile = Rules_ConstructCodeFileOpen(
             moduleFile,
             v22,
             v26,
             v23,
             &fileCount,
             moduleArrayVersion,
             v24,
             (char)aStructDefgloba,
             **(const char ***)(g_ClipsDefglobalCodeGenItem + 20),
             0,
             0);
      v9 = openedModuleFile;
      if ( !openedModuleFile )
      {
        Defglobal_CloseConstructCodeFiles(0, codeFP, v8, maxIndices);
        return 0;
      }
      Defglobal_WriteModuleHeaderToCode(openedModuleFile, Enum, maxIndices, moduleCount);
      moduleFile = Rules_ConstructCodeFileClose(v9, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDefglobal = Defglobal_EnumNext(0);
      if ( theDefglobal )
        break;
LABEL_6:
      ++moduleCount;
      ++moduleArrayCount;
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      openedDefglobalFile = Rules_ConstructCodeFileOpen(
              codeFP,
              v22,
              v26,
              v23,
              &fileCount,
              defglobalArrayVersion,
              v24,
              (char)aStructDefglo_0,
              *(const char **)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
              0,
              0);
      v13 = openedDefglobalFile;
      if ( !openedDefglobalFile )
        break;
      Defglobal_WriteDefglobalEntryToCode(openedDefglobalFile, theDefglobal, maxIndices, v26, moduleCount);
      ++defglobalArrayCount;
      codeFP = Rules_ConstructCodeFileClose(v13, &defglobalArrayCount, maxIndices, &defglobalArrayVersion, 0, 0);
      theDefglobal = Defglobal_EnumNext(theDefglobal);
      if ( !theDefglobal )
        goto LABEL_6;
    }
    Defglobal_CloseConstructCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Defglobal_CloseConstructCodeFiles(moduleFile, codeFP, v6, maxIndices);
    return 1;
  }
}
// 4CCC90: variable 'v6' is possibly undefined
// 4CCCA7: variable 'v8' is possibly undefined
// 4CCCBF: variable 'v12' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCCD0) --------------------------------------------------------
int  Defglobal_CloseConstructCodeFiles(int headerFP, int codeFP, int a3, int maxIndices)
{
  int result; // eax
  int v6; // [esp+0h] [ebp-14h] BYREF
  _DWORD v7[4]; // [esp+4h] [ebp-10h] BYREF

  v7[3] = a3;
  result = codeFP;
  v6 = maxIndices;
  v7[0] = 0;
  if ( codeFP )
  {
    result = Rules_ConstructCodeFileClose(codeFP, &v6, maxIndices, v7, 0, 0);
    if ( !headerFP )
      return result;
    goto LABEL_5;
  }
  if ( headerFP )
  {
LABEL_5:
    v6 = maxIndices;
    return Rules_ConstructCodeFileClose(headerFP, &v6, maxIndices, v7, 0, 0);
  }
  return result;
}

//----- (004CCD30) --------------------------------------------------------
int  Defglobal_WriteModuleHeaderToCode(int filePtr, int theModule, int maxIndices, int moduleCount)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, filePtr, (int)asc_50BD24, v10);
  Rules_WriteConstructModuleItemHeaderToCode(filePtr, v5, v6, g_ClipsDefglobalModuleItemId, *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, filePtr, (int)asc_50BD28, v11);
}
// 4CCD3B: variable 'v10' is possibly undefined
// 4CCD58: variable 'v5' is possibly undefined
// 4CCD58: variable 'v6' is possibly undefined
// 4CCD63: variable 'v8' is possibly undefined
// 4CCD63: variable 'v7' is possibly undefined
// 4CCD63: variable 'v11' is possibly undefined
// 54E6B0: using guessed type int dword_54E6B0;
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCD80) --------------------------------------------------------
int  Defglobal_WriteDefglobalEntryToCode(int filePtr, int defglobal, int maxIndices, char a4, int moduleCount)
{
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  char v20; // [esp+0h] [ebp-10h]
  char v21; // [esp+0h] [ebp-10h]
  char v22; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, defglobal, filePtr, (int)asc_50BD24, a4);
  Rules_WriteConstructHeaderToCode(filePtr, defglobal, maxIndices, moduleCount, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  Output_WriteFormatted(v9, v8, filePtr, (int)asc_50BD2C, v19);
  Output_WriteFormatted(v11, v10, filePtr, (int)a00Ld, *(_DWORD *)(defglobal + 24));
  Output_WriteFormatted(v13, v12, filePtr, (int)aNullRvoid, v20);
  Output_WriteFormatted(maxIndices, v14, filePtr, (int)asc_50BD2C, v21);
  Rules_WriteExpressionRefToCode(filePtr, *(__int16 **)(defglobal + 52), v15, v22);
  return Output_WriteFormatted(v17, v16, filePtr, (int)asc_50BD28, v22);
}
// 4CCDC6: variable 'v9' is possibly undefined
// 4CCDC6: variable 'v8' is possibly undefined
// 4CCDC6: variable 'v19' is possibly undefined
// 4CCDD8: variable 'v11' is possibly undefined
// 4CCDD8: variable 'v10' is possibly undefined
// 4CCDE6: variable 'v13' is possibly undefined
// 4CCDE6: variable 'v12' is possibly undefined
// 4CCDE6: variable 'v20' is possibly undefined
// 4CCDF6: variable 'v14' is possibly undefined
// 4CCDF6: variable 'v21' is possibly undefined
// 4CCE06: variable 'v15' is possibly undefined
// 4CCE06: variable 'v22' is possibly undefined
// 4CCE11: variable 'v17' is possibly undefined
// 4CCE11: variable 'v16' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCE30) --------------------------------------------------------
int  Defglobal_WriteModuleItemHeaderReference(int filePtr, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20), filePtr, (int)aMihsSD_DD_6, **(_DWORD **)(g_ClipsDefglobalCodeGenItem + 20));
}
// 54E8EC: using guessed type int dword_54E8EC;

//----- (004CCE70) --------------------------------------------------------
int  Defglobal_WriteDefglobalArrayReference(int filePtr, int defglobalIndex, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( defglobalIndex )
    return Output_WriteFormatted(
             maxIndices,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4),
             filePtr,
             (int)aSD_LdLd_0,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefglobalCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(maxIndices, 0, filePtr, (int)aNull_6, v4);
}
// 4CCE80: variable 'v4' is possibly undefined
// 54E8EC: using guessed type int dword_54E8EC;
