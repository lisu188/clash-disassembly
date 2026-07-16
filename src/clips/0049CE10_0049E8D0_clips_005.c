/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0049CE10) --------------------------------------------------------
__int16 * Rules_BindFunction(_DWORD *returnValue, double context)
{
  int foundFlag; // ecx
  int firstArgExpr; // eax
  int unbindFlag; // ebp
  int variableSymbol; // esi
  int v7; // eax
  int valueExpr; // ebx
  _DWORD *prevBinding; // ebx
  _DWORD *currentBinding; // edx
  _DWORD *freeListHead; // edx
  _DWORD *newBinding; // eax
  _DWORD *theBinding; // edx
  __int16 *result; // eax
  __int16 *v15; // eax
  int theGlobal; // [esp+0h] [ebp-1Ch]

  foundFlag = 0;
  firstArgExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  unbindFlag = 0;
  variableSymbol = 0;
  theGlobal = 0;
  if ( *(_WORD *)(uintptr_t)firstArgExpr == 60 )
  {
    theGlobal = *(_DWORD *)(uintptr_t)(firstArgExpr + 2);
  }
  else
  {
    Parser_ParseForm((__int16 *)(uintptr_t)firstArgExpr, returnValue, 0, context);
    variableSymbol = returnValue[2];
  }
  v7 = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  valueExpr = *(_DWORD *)(uintptr_t)(v7 + 10);
  if ( valueExpr )
  {
    v15 = *(__int16 **)(uintptr_t)(v7 + 10);
    if ( *(_DWORD *)(uintptr_t)(valueExpr + 10) )
      Rules_StoreEvaluatedNodesAsMultifield(returnValue, (int)(intptr_t)v15, 1, context);
    else
      Parser_ParseForm(v15, returnValue, foundFlag, context);
  }
  else
  {
    unbindFlag = 1;
  }
  prevBinding = (_DWORD *)(uintptr_t)theGlobal;
  if ( theGlobal )
    return (__int16 *)(uintptr_t)Defglobal_SetValue(theGlobal, returnValue, unbindFlag, context);
  currentBinding = (_DWORD *)(uintptr_t)g_BoundVariableList;
  if ( g_BoundVariableList )
  {
    do
    {
      if ( foundFlag )
        break;
      if ( variableSymbol == *currentBinding )
      {
        foundFlag = 1;
      }
      else
      {
        prevBinding = currentBinding;
        currentBinding = (_DWORD *)(uintptr_t)currentBinding[5];
      }
    }
    while ( currentBinding );
  }
  if ( foundFlag )
  {
    Rules_ValueDeinstall((int)(intptr_t)currentBinding, foundFlag);
  }
  else
  {
    if ( unbindFlag )
    {
LABEL_21:
      returnValue[1] = 2;
      result = (__int16 *)(uintptr_t)g_ClipsFalseSymbol;
      returnValue[2] = g_ClipsFalseSymbol;
      return result;
    }
    freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 96);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *freeListHead;
      newBinding = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newBinding = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    newBinding[5] = 0;
    theBinding = newBinding;
    *newBinding = variableSymbol;
    if ( prevBinding )
      prevBinding[5] = newBinding;
    else
      g_BoundVariableList = (int)(intptr_t)newBinding;
  }
  if ( unbindFlag )
  {
    if ( prevBinding )
      prevBinding[5] = theBinding[5];
    else
      g_BoundVariableList = theBinding[5];
    g_ClipsMemFreeListTemp = (int)(intptr_t)theBinding;
    *theBinding = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    goto LABEL_21;
  }
  theBinding[1] = returnValue[1];
  theBinding[2] = returnValue[2];
  theBinding[3] = returnValue[3];
  theBinding[4] = returnValue[4];
  return Rules_ValueInstall((int)(intptr_t)returnValue, foundFlag);
}
// 49CE6E: variable 'v3' is possibly undefined
// 49CECF: variable 'v13' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACCC: using guessed type int dword_51ACCC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CFD0) --------------------------------------------------------
signed int  Rules_FindBoundVariable(_DWORD *vPtr, int variableSymbol)
{
  _DWORD *bindEntry; // eax

  bindEntry = (_DWORD *)(uintptr_t)g_BoundVariableList;
  if ( !g_BoundVariableList )
    return 0;
  while ( variableSymbol != *bindEntry )
  {
    bindEntry = (_DWORD *)(uintptr_t)bindEntry[5];
    if ( !bindEntry )
      return 0;
  }
  vPtr[1] = bindEntry[1];
  vPtr[2] = bindEntry[2];
  vPtr[3] = bindEntry[3];
  vPtr[4] = bindEntry[4];
  return 1;
}
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D010) --------------------------------------------------------
int Rules_FreeBoundVariableEntry(void)
{
  int result; // eax
  int v1; // edx

  result = Rules_DeinstallValueChain(g_BoundVariableList);
  g_BoundVariableList = v1;
  return result;
}
// 49D01D: variable 'v1' is possibly undefined
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D030) --------------------------------------------------------
int  Rules_PrognFunction(_DWORD *returnValue, double context)
{
  int v3; // eax
  int argCount; // esi
  int v5; // ecx
  int v6; // ecx
  int result; // eax

  v3 = Rules_RtnArgCount();
  argCount = v3;
  if ( !v3 )
    goto LABEL_8;
  if ( v3 >= 1 )
  {
    do
    {
      if ( Rules_GetEvaluationErrorFlag() == 1 )
        break;
      Rules_RtnUnknown(v5, returnValue, context);
      if ( g_ClipsBreakFlag == 1 )
        break;
    }
    while ( g_ClipsHaltExecutionFlag != 1 && v6 + 1 <= argCount );
  }
  result = Rules_GetEvaluationErrorFlag();
  if ( result == 1 )
  {
LABEL_8:
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  return result;
}
// 49D058: variable 'v5' is possibly undefined
// 49D06F: variable 'v6' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0A0) --------------------------------------------------------
int  Rules_ReturnFunction(double context)
{
  _DWORD *returnValue; // edx
  int result; // eax

  if ( Rules_RtnArgCount() )
  {
    result = Rules_RtnUnknown(1, returnValue, context);
  }
  else
  {
    returnValue[1] = 105;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  g_ClipsHaltExecutionFlag = 1;
  return result;
}
// 49D0AC: variable 'v1' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0E0) --------------------------------------------------------
void Rules_BreakFunction(void)
{
  g_ClipsBreakFlag = 1;
}
// 51ACC4: using guessed type int dword_51ACC4;

//----- (0049D0F0) --------------------------------------------------------
int  Rules_SwitchFunction(_DWORD *returnValue, int a2, double context)
{
  int result; // eax
  int caseExpr; // ecx
  int caseData; // [esp-4h] [ebp-40h] BYREF
  int caseType; // [esp+0h] [ebp-3Ch]
  int caseValue; // [esp+4h] [ebp-38h]
  int switchData; // [esp+14h] [ebp-28h] BYREF
  int switchType; // [esp+18h] [ebp-24h]
  int switchValue; // [esp+1Ch] [ebp-20h]
  int v13 CLASH95_UNUSED; // [esp+34h] [ebp-8h]

  v13 = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Parser_ParseForm(*(__int16 **)(uintptr_t)(g_ClipsCurrentExpression + 6), &switchData, a2, context);
  if ( !g_ClipsEvaluationError )
  {
    caseExpr = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
    if ( caseExpr )
    {
      while ( *(_WORD *)(uintptr_t)caseExpr != 105 )
      {
        result = Parser_ParseForm((__int16 *)(uintptr_t)caseExpr, &caseData, caseExpr, context);
        if ( g_ClipsEvaluationError )
          return result;
        result = switchType;
        if ( switchType == caseType )
        {
          result = caseType == 4 ? Rules_MultifieldRangesEqual(&switchData, &caseData) : switchValue == caseValue;
          if ( result )
            break;
        }
        caseExpr = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(caseExpr + 10) + 10);
        if ( !caseExpr )
          return result;
      }
      return Parser_ParseForm(*(__int16 **)(uintptr_t)(caseExpr + 10), returnValue, caseExpr, context);
    }
  }
  return result;
}
// 49D16A: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D1A0) --------------------------------------------------------
signed int Rules_RegisterMiscFunctions(void)
{
  int v0; // ecx

  Rules_RegisterHostFunction(aGensym, 119, (int)(intptr_t)aGensymfunction, (int)(intptr_t)Rules_GensymFunction, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aGensym_0, 119, (int)(intptr_t)aGensymstarfunc, (int)(intptr_t)Rules_GensymStarFunction, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aSetgen, 108, (int)(intptr_t)aSetgenfunction, (int)(intptr_t)Rules_SetGenFunction, (int)(intptr_t)a11i_1);
  Rules_RegisterHostFunction(aSystem, 118, (int)(intptr_t)aGensystem, (int)(intptr_t)Rules_SystemCommand, (int)(intptr_t)a1K);
  Rules_RegisterHostFunction(aLength, 108, (int)(intptr_t)aLengthfunction, (int)(intptr_t)Rules_HostLength, (int)(intptr_t)a11q);
  Rules_RegisterHostFunction(aLength_0, 108, (int)(intptr_t)aLengthfunction, (int)(intptr_t)Rules_HostLength, (int)(intptr_t)a11q);
  Rules_RegisterHostFunction(aTime, 100, (int)(intptr_t)aGentime, (int)(intptr_t)Rules_TimeCommand, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aRandom, 108, (int)(intptr_t)aRandomfunction, (int)(intptr_t)Rules_HostRandom, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aSeed, 118, (int)(intptr_t)aSeedfunction, (int)(intptr_t)Rules_HostSeed, (int)(intptr_t)a11i_1);
  Rules_RegisterHostFunction(aConserveMem, 118, (int)(intptr_t)aConservememcom, (int)(intptr_t)Rules_HostConserveMem, (int)(intptr_t)a11w_6);
  Rules_RegisterHostFunction(aReleaseMem, 108, (int)(intptr_t)aReleasememcomm, (int)(intptr_t)Rules_HostReleaseMem, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aMemUsed, 108, (int)(intptr_t)aMemusedcommand, (int)(intptr_t)Rules_HostMemUsed, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aMemRequests, 108, (int)(intptr_t)aMemrequestscom, (int)(intptr_t)Rules_HostMemRequests, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aOptions, 118, (int)(intptr_t)aOptionscommand, (int)(intptr_t)Rules_HostOptionsCommand, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aExpansionCall, 117, (int)(intptr_t)aExpandfunccall, (int)(intptr_t)Rules_HostExpansionCall, 0);
  Rules_RegisterHostFunction(aExpand, 117, (int)(intptr_t)aDummyexpandfun, (int)(intptr_t)Rules_HostExpandDummy, (int)(intptr_t)a11m);
  Rules_SetFunctionSeqOverloadFlags(aExpand, 0);
  Rules_RegisterHostFunction(aSetEvaluationE, 119, v0, (int)(intptr_t)Rules_HostSetEvaluationError, 0);
  Rules_RegisterHostFunction(aSetSequenceOpe, 98, (int)(intptr_t)aSetsorcommand, (int)(intptr_t)Rules_HostSetSequenceOperatorRecognition, (int)(intptr_t)a11w_6);
  Rules_RegisterHostFunction(aGetSequenceOpe, 98, (int)(intptr_t)aGetsequenceope, (int)(intptr_t)Parser_GetSequenceOperatorRecognition, (int)(intptr_t)a00_5);
  Rules_RegisterHostFunction(aGetFunctionRes, 115, (int)(intptr_t)aGetfunctionres, (int)(intptr_t)Rules_HostGetFunctionRestrictions, (int)(intptr_t)a11w_6);
  Rules_RegisterHostFunction(aCreate, 109, (int)(intptr_t)aCreatefunction, (int)(intptr_t)Rules_CreateMultifieldFunction, 0);
  Rules_RegisterHostFunction(aMvAppend, 109, (int)(intptr_t)aCreatefunction, (int)(intptr_t)Rules_CreateMultifieldFunction, 0);
  return Rules_RegisterHostFunction(aApropos, 118, (int)(intptr_t)aAproposcommand, (int)(intptr_t)Rules_HostApropos, (int)(intptr_t)a11w_6);
}
// 49D3A4: variable 'v0' is possibly undefined
// 49E070: using guessed type int sub_49E070();

//----- (0049D460) --------------------------------------------------------
_DWORD * Rules_CreateMultifieldFunction(_DWORD *returnValue, double context)
{
  return Rules_StoreEvaluatedNodesAsMultifield(returnValue, *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), 1, context);
}
// 51A960: using guessed type int dword_51A960;

//----- (0049D480) --------------------------------------------------------
signed int  Rules_SetGenFunction(int a1, double context)
{
  signed int result; // eax
  int argData; // [esp-8h] [ebp-24h] BYREF
  int argValue; // [esp+0h] [ebp-1Ch]
  int v5 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v5 = a1;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &argData, 1, context) )
    return g_ClipsGensymCounter;
  result = *(_DWORD *)(uintptr_t)(argValue + 16);
  if ( result < 1 )
  {
    Parser_ReportError(1, (int)(intptr_t)aNumberGreaterT);
    return g_ClipsGensymCounter;
  }
  else
  {
    g_ClipsGensymCounter = *(_DWORD *)(uintptr_t)(argValue + 16);
  }
  return result;
}
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D500) --------------------------------------------------------
signed int *__fastcall Rules_GensymFunction(int a1, int a2 CLASH95_UNUSED)
{
  char symbolBuffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v4 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v4 = a1;
  Lexer_TokenExpect(0);
  sprintf_(symbolBuffer, "gen%ld", g_ClipsGensymCounter);
  return Str_Intern(symbolBuffer, ++g_ClipsGensymCounter);
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D550) --------------------------------------------------------
signed int *__thiscall Rules_GensymStarFunction(void *this)
{
  int v1; // ecx
  char symbolBuffer[20]; // [esp+0h] [ebp-18h] BYREF
  void *v4 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

  v4 = this;
  Lexer_TokenExpect(0);
  do
  {
    sprintf_(symbolBuffer, "gen%ld", g_ClipsGensymCounter);
    ++g_ClipsGensymCounter;
  }
  while ( Rules_FindSymbolEntry(symbolBuffer) );
  return Str_Intern(symbolBuffer, v1);
}
// 49D598: variable 'v1' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D5B0) --------------------------------------------------------
int Rules_HostRandom(void)
{
  Lexer_TokenExpect(0);
  return j_rand_();
}
// 47D520: using guessed type int j_rand_(void);

//----- (0049D5D0) --------------------------------------------------------
int  Rules_HostSeed(int a1, double context)
{
  int result; // eax
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, argData, 1, context);
    if ( result )
      return j_srand_();
  }
  return result;
}
// 47D530: using guessed type int j_srand_(void);

//----- (0049D620) --------------------------------------------------------
int  Rules_HostLength(double context)
{
  int result; // eax
  int v2; // edx
  int argData; // [esp-4h] [ebp-20h] BYREF
  int argType; // [esp+0h] [ebp-1Ch]
  int argValue; // [esp+4h] [ebp-18h]
  int rangeBegin; // [esp+8h] [ebp-14h]
  int rangeEnd; // [esp+Ch] [ebp-10h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, &argData, context);
    if ( argType == 3 || argType == 2 )
    {
      return strlen(*(const char **)(uintptr_t)(argValue + 16));
    }
    else if ( argType == 4 )
    {
      return rangeEnd - rangeBegin + 1;
    }
    else
    {
      Lexer_ErrorRecover(1);
      Rules_ReportSymbolTypeError(aLength_0, v2);
      return -1;
    }
  }
  return result;
}
// 49D6A0: variable 'v2' is possibly undefined

//----- (0049D6B0) --------------------------------------------------------
int Rules_HostReleaseMem(void)
{
  int v0; // ecx

  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_PurgeFreeListsForSpace(-1, 0, v0);
}
// 49D6D1: variable 'v0' is possibly undefined

//----- (0049D6E0) --------------------------------------------------------
int  Rules_HostConserveMem(int a1, double context)
{
  int result; // eax
  int v3; // edx
  int v4; // ecx
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, argData, 2, context);
    if ( result )
    {
      if ( !strcmp_(*(_DWORD *)(uintptr_t)(argData[2] + 16), aOn_0) || !strcmp_(v4, aOff_0) )
        return Mem_SetAllocFlag(v4, v3);
      else
        return Parser_ReportError(1, (int)(intptr_t)aSymbolWithVa_2);
    }
  }
  return result;
}
// 49D73B: variable 'v4' is possibly undefined
// 49D744: variable 'v3' is possibly undefined
// 472B00: using guessed type int __fastcall unknown_libname_5(_DWORD, _DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0049D780) --------------------------------------------------------
int Rules_HostMemUsed(void)
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_GetTotalAllocatedBytes();
}

//----- (0049D7B0) --------------------------------------------------------
int Rules_HostMemRequests(void)
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_GetTotalAllocationCount();
}

//----- (0049D7E0) --------------------------------------------------------
int ** Rules_HostApropos(double context)
{
  int **result; // eax
  int ***symbolEntry; // esi
  char *searchString; // ebp
  unsigned int searchLength; // kr04_4
  int v5; // ecx
  int v6; // ecx
  _DWORD argData[12]; // [esp+0h] [ebp-30h] BYREF

  result = (int **)(uintptr_t)Lexer_TokenExpect(1);
  symbolEntry = 0;
  if ( result != (int **)-1 )
  {
    result = (int **)(uintptr_t)Lexer_ParseValueList(1, argData, 2, context);
    if ( result )
    {
      searchString = *(char **)(uintptr_t)(argData[2] + 16);
      searchLength = strlen(searchString) + 1;
      while ( 1 )
      {
        result = Rules_GetNextSymbolMatch((int **)searchString, searchLength - 1, 1, symbolEntry, 0);
        symbolEntry = (int ***)result;
        if ( !result )
          break;
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)result[4], v5);
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_5063E0, v6);
      }
    }
  }
  return result;
}
// 49D85A: variable 'v5' is possibly undefined
// 49D869: variable 'v6' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0049D870) --------------------------------------------------------
int Rules_HostOptionsCommand(void)
{
  int result; // eax
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  int v36; // ecx
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int v44; // ecx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  int v48; // ecx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  int v52; // ecx
  int v53; // ecx
  int v54; // ecx
  int v55; // ecx
  int v56; // ecx
  int v57; // ecx
  int v58; // ecx
  int v59; // ecx
  int v60; // ecx
  int v61; // ecx
  int v62; // ecx
  int v63; // ecx
  int v64; // ecx
  int v65; // ecx
  int v66; // ecx
  int v67; // ecx
  int v68; // ecx
  int v69; // ecx
  int v70; // ecx
  int v71; // ecx
  int v72; // ecx
  int v73; // ecx
  int v74; // ecx
  int v75; // ecx
  int v76; // ecx
  int v77; // ecx
  int v78; // ecx

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aMachineType, v1);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aUnixSystemIiiV, v2);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_5063E0, v3);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aAnsiCompilerIs, v4);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v5);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDefruleConstru, v6);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v7);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aConflictResolu, v8);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v9);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDynamicSalienc, v10);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v11);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aIncrementalRes, v12);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v13);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aLogicalDepende, v14);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v15);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDefmoduleConst, v16);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v17);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDeftemplateCon, v18);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v19);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDeffactsConstr, v20);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v21);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDefglobalConst, v22);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v23);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDeffunctionCon, v24);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v25);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDefgenericDefm, v26);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v27);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aImperativeMeth, v28);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v29);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aObjectSystemIs, v30);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v31);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDefinstancesCo, v32);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v33);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aImperativeArou, v34);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v35);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aAuxiliaryBefor, v36);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v37);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aInstanceSetQue, v38);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v39);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDirectPatternM, v40);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v41);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBinaryLoadingO, v42);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v43);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBinarySavingOf, v44);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v45);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aExtendedMathPa, v46);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v47);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aTextProcessing, v48);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v49);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aHelpSystemIs, v50);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v51);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBloadCapabilit, v52);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBloadAndBsave, v53);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_5063E0, v54);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aEmacsEditorIs, v55);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOff_1, v56);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aConstructCompi, v57);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v58);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBasicIOIs, v59);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v60);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aExtendedIOIs, v61);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v62);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aStringFunction, v63);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v64);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aMultifieldFunc, v65);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v66);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDebuggingFunct, v67);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v68);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aBlockMemoryIs, v69);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOn_1, v70);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aWindowInterfac, v71);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOff_1, v72);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aShortLinkNames, v73);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOff_1, v74);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aDeveloperFlagI, v75);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOff_1, v76);
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aRunTimeModuleI, v77);
    return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aOff_1, v78);
  }
  return result;
}
// 49D892: variable 'v1' is possibly undefined
// 49D8A1: variable 'v2' is possibly undefined
// 49D8B0: variable 'v3' is possibly undefined
// 49D8BF: variable 'v4' is possibly undefined
// 49D8CE: variable 'v5' is possibly undefined
// 49D8DD: variable 'v6' is possibly undefined
// 49D8EC: variable 'v7' is possibly undefined
// 49D8FB: variable 'v8' is possibly undefined
// 49D90A: variable 'v9' is possibly undefined
// 49D919: variable 'v10' is possibly undefined
// 49D928: variable 'v11' is possibly undefined
// 49D937: variable 'v12' is possibly undefined
// 49D946: variable 'v13' is possibly undefined
// 49D955: variable 'v14' is possibly undefined
// 49D964: variable 'v15' is possibly undefined
// 49D973: variable 'v16' is possibly undefined
// 49D982: variable 'v17' is possibly undefined
// 49D991: variable 'v18' is possibly undefined
// 49D9A0: variable 'v19' is possibly undefined
// 49D9AF: variable 'v20' is possibly undefined
// 49D9BE: variable 'v21' is possibly undefined
// 49D9CD: variable 'v22' is possibly undefined
// 49D9DC: variable 'v23' is possibly undefined
// 49D9EB: variable 'v24' is possibly undefined
// 49D9FA: variable 'v25' is possibly undefined
// 49DA09: variable 'v26' is possibly undefined
// 49DA18: variable 'v27' is possibly undefined
// 49DA27: variable 'v28' is possibly undefined
// 49DA36: variable 'v29' is possibly undefined
// 49DA45: variable 'v30' is possibly undefined
// 49DA54: variable 'v31' is possibly undefined
// 49DA63: variable 'v32' is possibly undefined
// 49DA72: variable 'v33' is possibly undefined
// 49DA81: variable 'v34' is possibly undefined
// 49DA90: variable 'v35' is possibly undefined
// 49DA9F: variable 'v36' is possibly undefined
// 49DAAE: variable 'v37' is possibly undefined
// 49DABD: variable 'v38' is possibly undefined
// 49DACC: variable 'v39' is possibly undefined
// 49DADB: variable 'v40' is possibly undefined
// 49DAEA: variable 'v41' is possibly undefined
// 49DAF9: variable 'v42' is possibly undefined
// 49DB08: variable 'v43' is possibly undefined
// 49DB17: variable 'v44' is possibly undefined
// 49DB26: variable 'v45' is possibly undefined
// 49DB35: variable 'v46' is possibly undefined
// 49DB44: variable 'v47' is possibly undefined
// 49DB53: variable 'v48' is possibly undefined
// 49DB62: variable 'v49' is possibly undefined
// 49DB71: variable 'v50' is possibly undefined
// 49DB80: variable 'v51' is possibly undefined
// 49DB8F: variable 'v52' is possibly undefined
// 49DB9E: variable 'v53' is possibly undefined
// 49DBAD: variable 'v54' is possibly undefined
// 49DBBC: variable 'v55' is possibly undefined
// 49DBCB: variable 'v56' is possibly undefined
// 49DBDA: variable 'v57' is possibly undefined
// 49DBE9: variable 'v58' is possibly undefined
// 49DBF8: variable 'v59' is possibly undefined
// 49DC07: variable 'v60' is possibly undefined
// 49DC16: variable 'v61' is possibly undefined
// 49DC25: variable 'v62' is possibly undefined
// 49DC34: variable 'v63' is possibly undefined
// 49DC43: variable 'v64' is possibly undefined
// 49DC52: variable 'v65' is possibly undefined
// 49DC61: variable 'v66' is possibly undefined
// 49DC70: variable 'v67' is possibly undefined
// 49DC7F: variable 'v68' is possibly undefined
// 49DC8E: variable 'v69' is possibly undefined
// 49DC9D: variable 'v70' is possibly undefined
// 49DCAC: variable 'v71' is possibly undefined
// 49DCBB: variable 'v72' is possibly undefined
// 49DCCA: variable 'v73' is possibly undefined
// 49DCD9: variable 'v74' is possibly undefined
// 49DCE8: variable 'v75' is possibly undefined
// 49DCF7: variable 'v76' is possibly undefined
// 49DD06: variable 'v77' is possibly undefined
// 49DD15: variable 'v78' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0049DD20) --------------------------------------------------------
int  Rules_HostExpansionCall(int returnValue, double context)
{
  int **Symbol; // eax
  _DWORD *freeListHead; // edx
  signed int newExpr; // ecx
  int nodeValue; // eax
  __int16 *exprNode; // edi
  _DWORD *argList; // eax
  __int16 exprType; // dx
  int deffunctionArgCount; // eax
  int v11; // ecx
  int theFunction; // ebx
  int argCount; // eax
  int v15[7]; // [esp+0h] [ebp-1Ch] BYREF

  v15[0] = AST_CloneNodeList(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 6));
  Symbol = Rules_MakeSymbol(aExpand);
  Rules_ExpandFuncCallForm((int **)(uintptr_t)returnValue, (_DWORD *)(uintptr_t)v15[0], (int)(intptr_t)Symbol, v15, context);
  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 56);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *freeListHead;
    newExpr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_WORD *)(uintptr_t)newExpr = **(_WORD **)(uintptr_t)(g_ClipsCurrentExpression + 6);
  nodeValue = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2);
  *(_DWORD *)(uintptr_t)(newExpr + 10) = 0;
  *(_DWORD *)(uintptr_t)(newExpr + 2) = nodeValue;
  exprNode = (__int16 *)(uintptr_t)newExpr;
  argList = (_DWORD *)(uintptr_t)v15[0];
  exprType = *(_WORD *)(uintptr_t)newExpr;
  *(_DWORD *)(uintptr_t)(newExpr + 6) = v15[0];
  if ( exprType == 10 )
  {
    theFunction = *(_DWORD *)(uintptr_t)(newExpr + 2);
    argCount = AST_CountListNodes((int)(intptr_t)argList);
    if ( !Rules_CheckFunctionArgCount(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theFunction + 16), *(_BYTE **)(uintptr_t)(theFunction + 17), argCount) )
    {
      *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
      *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
      return AST_Free(newExpr);
    }
  }
  else if ( exprType == 12 )
  {
    deffunctionArgCount = AST_CountListNodes((int)(intptr_t)argList);
    if ( !Deffunction_CheckArgumentCount(*(_DWORD *)(uintptr_t)(v11 + 2), deffunctionArgCount) )
    {
      *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
      *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
      AST_Free(newExpr);
      return Lexer_ErrorRecover(1);
    }
  }
  Parser_ParseForm(exprNode, (_DWORD *)(uintptr_t)returnValue, newExpr, context);
  return AST_Free((int)(intptr_t)exprNode);
}
// 49DDBA: variable 'v11' is possibly undefined
// 49DDDB: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DE60) --------------------------------------------------------
signed int  Rules_HostExpandDummy(int returnValue)
{
  int v1; // edx
  int v2; // ecx

  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  Lexer_ErrorRecover(1);
  Rules_PrintErrorID((int)(intptr_t)aMiscfun, v1, 0);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpandMustBeUs, v2);
}
// 49DE88: variable 'v1' is possibly undefined
// 49DE97: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DEA0) --------------------------------------------------------
int ** Rules_ExpandFuncCallForm(int **result, _DWORD *theExp, int expandFuncSymbol, int *stoPtr, double context)
{
  int **returnValue; // edi
  _DWORD *exprCursor; // esi
  int fieldOffset; // edx
  _DWORD *freeListHead; // ebx
  signed int newNode; // eax
  int fieldValue; // ebx
  int v12; // [esp+4h] [ebp-18h]
  int newListHead; // [esp+8h] [ebp-14h]
  int lastNode; // [esp+Ch] [ebp-10h]

  returnValue = result;
  exprCursor = theExp;
  v12 = expandFuncSymbol;
  if ( theExp )
  {
    while ( 1 )
    {
      while ( v12 != *(_DWORD *)((char *)exprCursor + 2) )
      {
        expandFuncSymbol = *(_DWORD *)((char *)exprCursor + 6);
        if ( expandFuncSymbol )
          Rules_ExpandFuncCallForm((int)(intptr_t)returnValue, *(_DWORD *)((char *)exprCursor + 6), v12, (int)(intptr_t)exprCursor + 6, context);
        result = (int **)((char *)exprCursor + 10);
        stoPtr = (_DWORD *)((char *)exprCursor + 10);
        exprCursor = *(_DWORD **)((char *)exprCursor + 10);
        if ( !exprCursor )
          return result;
      }
      Parser_ParseForm(*(__int16 **)((char *)exprCursor + 6), returnValue, expandFuncSymbol, context);
      AST_Free(*(_DWORD *)((char *)exprCursor + 6));
      if ( g_ClipsEvaluationError || returnValue[1] != (int *)4 )
        break;
      expandFuncSymbol = (int)(intptr_t)returnValue[3] + 1;
      lastNode = g_ClipsEvaluationError;
      newListHead = g_ClipsEvaluationError;
      fieldOffset = 6 * expandFuncSymbol - 6;
      while ( expandFuncSymbol <= (int)(intptr_t)returnValue[4] + 1 )
      {
        freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 56);
        if ( freeListHead )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *freeListHead;
          newNode = g_ClipsMemFreeListTemp;
        }
        else
        {
          newNode = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_WORD *)(uintptr_t)newNode = *(_WORD *)((char *)returnValue[2] + fieldOffset + 14);
        fieldValue = *(int *)((char *)returnValue[2] + fieldOffset + 16);
        *(_DWORD *)(uintptr_t)(newNode + 6) = 0;
        *(_DWORD *)(uintptr_t)(newNode + 2) = fieldValue;
        *(_DWORD *)(uintptr_t)(newNode + 10) = 0;
        if ( newListHead )
          *(_DWORD *)(uintptr_t)(lastNode + 10) = newNode;
        else
          newListHead = newNode;
        lastNode = newNode;
        fieldOffset += 6;
        ++expandFuncSymbol;
      }
      if ( newListHead )
      {
        *(_DWORD *)(uintptr_t)(lastNode + 10) = *(_DWORD *)((char *)exprCursor + 10);
        *stoPtr = newListHead;
        g_ClipsMemFreeListTemp = (int)(intptr_t)exprCursor;
        *exprCursor = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
        result = (int **)(uintptr_t)(lastNode + 10);
        exprCursor = *(_DWORD **)(uintptr_t)(lastNode + 10);
        stoPtr = (int *)(uintptr_t)(lastNode + 10);
        if ( !exprCursor )
          return result;
      }
      else
      {
        *stoPtr = *(_DWORD *)((char *)exprCursor + 10);
        g_ClipsMemFreeListTemp = (int)(intptr_t)exprCursor;
        *exprCursor = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
        result = (int **)(uintptr_t)g_ClipsMemoryTable;
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
        exprCursor = (_DWORD *)(uintptr_t)*stoPtr;
        if ( !*stoPtr )
          return result;
      }
    }
    *(_DWORD *)((char *)exprCursor + 6) = 0;
    if ( !g_ClipsEvaluationError && returnValue[1] != (int *)4 )
      Rules_ReportSymbolTypeError(aExpand, 1);
    result = Rules_MakeSymbol(aSetEvaluationE);
    *(_DWORD *)((char *)exprCursor + 2) = result;
    g_ClipsEvaluationError = 0;
    g_ClipsHaltExecution = 0;
  }
  return result;
}
// 49DEEE: variable 'a3' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049E070) --------------------------------------------------------
int Rules_HostSetEvaluationError(void)
{
  Lexer_ErrorRecover(1);
  return g_ClipsFalseSymbol;
}
// 49E070: using guessed type int sub_49E070();
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E080) --------------------------------------------------------
int  Rules_HostSetSequenceOperatorRecognition(int returnValue, double context)
{
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = returnValue;
  if ( Lexer_ParseValueList(1, argData, 2, context) )
    return Parser_SetSequenceOperatorRecognition(argData[2] != g_ClipsFalseSymbol);
  else
    return g_SequenceOperatorRecognition;
}
// 51B360: using guessed type int dword_51B360;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E0D0) --------------------------------------------------------
signed int * Rules_HostGetFunctionRestrictions(int returnValue, double context)
{
  int v3; // ecx
  int **Symbol; // eax
  char *restrictionString; // eax
  int argData; // [esp-8h] [ebp-24h] BYREF
  int argValue; // [esp+0h] [ebp-1Ch]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v9 = returnValue;
  if ( !Lexer_ParseValueList(1, &argData, 2, context) )
  {
    restrictionString = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(restrictionString, v3);
  }
  Symbol = Rules_MakeSymbol(*(_BYTE **)(uintptr_t)(argValue + 16));
  if ( !Symbol )
  {
    Rules_ReportCantFindItem(v3, *(_DWORD *)(uintptr_t)(argValue + 16));
    Lexer_ErrorRecover(1);
    restrictionString = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(restrictionString, v3);
  }
  if ( !*(int **)((char *)Symbol + 17) )
  {
    restrictionString = a0_0;
    return Str_Intern(restrictionString, v3);
  }
  return Str_Intern(*(char **)((char *)Symbol + 17), v3);
}
// 49E10C: variable 'v3' is possibly undefined

//----- (0049E150) --------------------------------------------------------
signed int Rules_RegisterIOHostFunctions(void)
{
  Rules_RegisterHostFunction(aPrintout, 118, (int)(intptr_t)aPrintoutfuncti, (int)(intptr_t)Rules_HostPrintout, (int)(intptr_t)a1_0);
  Rules_RegisterHostFunction(aRead, 117, (int)(intptr_t)aReadfunction, (int)(intptr_t)Rules_HostRead, (int)(intptr_t)a1);
  Rules_RegisterHostFunction(aOpen, 98, (int)(intptr_t)aOpenfunction, (int)(intptr_t)Rules_HostOpen, (int)(intptr_t)a23K);
  Rules_RegisterHostFunction(aClose, 98, (int)(intptr_t)aClosefunction, (int)(intptr_t)Rules_HostClose, (int)(intptr_t)a1);
  Rules_RegisterHostFunction(aRemove, 98, (int)(intptr_t)aRemovefunction, (int)(intptr_t)Rules_HostRemoveFile, (int)(intptr_t)a11k_0);
  Rules_RegisterHostFunction(aRename, 98, (int)(intptr_t)aRenamefunction, (int)(intptr_t)Rules_HostRenameFile, (int)(intptr_t)a22k);
  Rules_RegisterHostFunction(aFormat, 115, (int)(intptr_t)aFormatfunction, (int)(intptr_t)Rules_HostFormat, (int)(intptr_t)a2Us);
  return Rules_RegisterHostFunction(aReadline, 107, (int)(intptr_t)aReadlinefuncti, (int)(intptr_t)Rules_HostReadline, (int)(intptr_t)a1);
}

//----- (0049E250) --------------------------------------------------------
int  Rules_HostPrintout(int returnValue, double context)
{
  int result; // eax
  int v3; // ecx
  int argCount; // edi
  int lastArgIndex; // esi
  int argIndex; // ebx
  int argString; // ecx
  char *outputString; // edx
  int v9 CLASH95_UNUSED; // eax
  int logical_name; // ecx
  int argData; // [esp-4h] [ebp-2Ch] BYREF
  unsigned int argType; // [esp+0h] [ebp-28h]
  int argValue; // [esp+4h] [ebp-24h]
  int v13 CLASH95_UNUSED; // [esp+20h] [ebp-8h]

  v13 = returnValue;
  result = Lexer_TokenExpect(1);
  argCount = result;
  lastArgIndex = result;
  if ( result != -1 )
  {
    logical_name = Rules_GetLogicalNameArg(1, (int)(intptr_t)aStdout_0, v3, context);
    if ( !logical_name )
    {
      Rules_ReportIllegalLogicalName();
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    result = IO_QueryRouters(logical_name);
    if ( !result )
      return IO_ReportUnrecognizedRouter(logical_name);
    argIndex = 2;
    if ( argCount >= 2 )
    {
      while ( 1 )
      {
        result = Rules_RtnUnknown(argIndex, &argData, context);
        if ( g_ClipsHaltExecution )
          return result;
        if ( argType < 2 )
          goto LABEL_26;
        if ( argType > 2 )
        {
          if ( argType == 3 )
            goto LABEL_17;
LABEL_26:
          result = Rules_PrintDataObject(argString, (int)(intptr_t)&argData);
          if ( ++argIndex > lastArgIndex )
            return result;
        }
        else
        {
          if ( strcmp_(argString, aCrlf) )
          {
            if ( !strcmp_(argString, aTab) )
            {
              outputString = asc_5069C0;
              goto LABEL_11;
            }
            if ( !strcmp_(argString, aVtab) )
            {
              outputString = asc_5069CC;
              goto LABEL_11;
            }
            if ( !strcmp_(argString, aFf) )
            {
              outputString = (char *)&g_Rules_PrintoutFormFeedChar;
              goto LABEL_11;
            }
            if ( strcmp_(argString, &g_Rules_PrintoutCrlfAliasName) )
            {
LABEL_17:
              v9 = argString;
              outputString = *(char **)(uintptr_t)(argValue + 16);
              goto LABEL_12;
            }
          }
          outputString = asc_5069B8;
LABEL_11:
          v9 = argString;
LABEL_12:
          result = Output_Write(logical_name, (int)(intptr_t)outputString, argString);
          if ( ++argIndex > lastArgIndex )
            return result;
        }
      }
    }
  }
  return result;
}
// 49E285: variable 'v3' is possibly undefined
// 49E2D5: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A968: using guessed type int dword_51A968;

//----- (0049E3E0) --------------------------------------------------------
signed int * Rules_HostRead(int returnValue, double context)
{
  int argCount; // eax
  int v4; // ecx
  char *logicalName; // esi
  int v6; // ecx
  unsigned int v7; // ecx
  int tokenType; // eax
  signed int *result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int theToken; // [esp+0h] [ebp-1Ch] BYREF
  signed int *tokenValue; // [esp+4h] [ebp-18h]
  char *tokenString; // [esp+8h] [ebp-14h]
  int v16 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v16 = returnValue;
  argCount = Lexer_TokenExpect(1);
  logicalName = 0;
  if ( argCount == -1 )
    goto LABEL_14;
  if ( argCount )
  {
    if ( argCount == 1 )
    {
      logicalName = (char *)(uintptr_t)Rules_GetLogicalNameArg(1, (int)(intptr_t)aStdin, v4, context);
      if ( !logicalName )
      {
        Rules_ReportIllegalLogicalName();
        Rules_SetEvaluationErrorFlag(1);
        Lexer_ErrorRecover(1);
        goto LABEL_14;
      }
    }
  }
  else
  {
    logicalName = aStdin;
  }
  if ( !IO_QueryRouters((int)(intptr_t)logicalName) )
  {
    IO_ReportUnrecognizedRouter((int)(intptr_t)logicalName);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    goto LABEL_14;
  }
  if ( !strcmp_(v6, aStdin) )
    Rules_ReadStdinLineToken(&theToken, v7);
  else
    Parser_NextToken((int)(intptr_t)logicalName, (int)(intptr_t)&theToken);
  tokenType = theToken;
  g_Lexer_PendingLineCharIndex = -1;
  *(_DWORD *)(uintptr_t)(v4 + 4) = theToken;
  switch ( tokenType )
  {
    case 0:
    case 3:
    case 8:
    case 2:
    case 1:
      result = tokenValue;
      *(_DWORD *)(uintptr_t)(v4 + 8) = tokenValue;
      break;
    case 102:
      *(_DWORD *)(uintptr_t)(v4 + 4) = 2;
      result = Str_Intern(aEof, v4);
      *(_DWORD *)(uintptr_t)(v11 + 8) = result;
      break;
    case 103:
LABEL_14:
      *(_DWORD *)(uintptr_t)(v4 + 4) = 3;
      result = Str_Intern(aReadError, v4);
      *(_DWORD *)(uintptr_t)(v10 + 8) = result;
      return result;
    default:
      *(_DWORD *)(uintptr_t)(v4 + 4) = 3;
      result = Str_Intern(tokenString, v4);
      *(_DWORD *)(uintptr_t)(v12 + 8) = result;
      break;
  }
  return result;
}
// 49E42B: variable 'v6' is possibly undefined
// 49E43A: variable 'v7' is possibly undefined
// 49E44D: variable 'v4' is possibly undefined
// 49E49F: variable 'v10' is possibly undefined
// 49E532: variable 'v11' is possibly undefined
// 49E54D: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A628: using guessed type int dword_51A628;

//----- (0049E560) --------------------------------------------------------
signed int * Rules_ReadStdinLineToken(_DWORD *theToken, unsigned int a2)
{
  char *appended; // edi
  int i; // esi
  unsigned int v5; // ecx
  signed int *result; // eax
  unsigned int bufferSize[7]; // [esp+0h] [ebp-1Ch] BYREF

  *theToken = 102;
  do
  {
    appended = 0;
    g_Lexer_PendingLineCharIndex = 0;
    bufferSize[0] = 0;
    for ( i = Lexer_PeekChar((int)(intptr_t)aStdin, a2); i != 10; i = Lexer_PeekChar((int)(intptr_t)aStdin, v5) )
    {
      if ( i == 13 )
        break;
      if ( i == -1 )
        break;
      if ( Rules_GetEvaluationErrorFlag() )
        break;
      appended = Str_AppendCharEscaping(i, appended, bufferSize, &g_Lexer_PendingLineCharIndex, bufferSize[0] + 80);
    }
    IO_OpenStringSource((int)(intptr_t)aRead, appended, 0);
    Parser_NextToken((int)(intptr_t)aRead, (int)(intptr_t)theToken);
    IO_CloseStringRouter((int)(intptr_t)aRead);
    if ( (int)bufferSize[0] > 0 )
      Mem_SmallBlockFree(appended, bufferSize[0]);
    result = (signed int *)(uintptr_t)Rules_GetEvaluationErrorFlag();
    if ( result )
    {
      *theToken = 3;
      result = Str_Intern(aReadError, a2);
      theToken[1] = result;
    }
    if ( *theToken == 102 && i == -1 )
    {
      *theToken = 2;
      result = Str_Intern(aEof, a2);
      theToken[1] = result;
    }
  }
  while ( *theToken == 102 );
  return result;
}
// 49E581: variable 'a2' is possibly undefined
// 49E5BE: variable 'v5' is possibly undefined
// 51A628: using guessed type int dword_51A628;

//----- (0049E650) --------------------------------------------------------
const CHAR * Rules_HostOpen(double context)
{
  int argCount; // ebx
  const CHAR *result; // eax
  int v3; // ecx
  const CHAR *fileName; // edi
  const char *logicalName; // esi
  char *accessMode; // ecx
  unsigned __int8 *v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  _DWORD argData[12]; // [esp+0h] [ebp-30h] BYREF

  argCount = Rules_ArgRangeCheck((int)(intptr_t)aOpen, 3);
  if ( argCount == -1 )
    return 0;
  result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(1, 0, context);
  fileName = result;
  if ( result )
  {
    logicalName = (const char *)(uintptr_t)Rules_GetLogicalNameArg(2, 0, v3, context);
    if ( !logicalName )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_ReportIllegalLogicalName();
      return 0;
    }
    if ( ismbdprint_((void *)logicalName) )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_PrintErrorID((int)(intptr_t)aIofun, v9, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aLogicalName_0, v10);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)logicalName, v11);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAlreadyInUse_, v12);
      return 0;
    }
    if ( argCount == 2 )
    {
      accessMode = aR_3;
    }
    else if ( argCount == 3 )
    {
      result = (const CHAR *)(uintptr_t)Lexer_ParseValueList(3, argData, 3, context);
      if ( !result )
        return result;
      accessMode = *(char **)(uintptr_t)(argData[2] + 16);
    }
    if ( !strcmp_(accessMode, aR_3) || !strcmp_(v7, aR_4) || !strcmp_(v7, aW_4) || !strcmp_(v7, aA_2) )
    {
      return (const CHAR *)(uintptr_t)IO_OpenNamedFile(fileName, v7, (int)(intptr_t)v7, logicalName, (DWORD)(intptr_t)logicalName);
    }
    else
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Parser_ReportError(v8, (int)(intptr_t)aStringWithValu);
      return 0;
    }
  }
  return result;
}
// 49E69E: variable 'v3' is possibly undefined
// 49E6D1: variable 'v6' is possibly undefined
// 49E6E5: variable 'v7' is possibly undefined
// 49E73D: variable 'v8' is possibly undefined
// 49E798: variable 'v9' is possibly undefined
// 49E7A7: variable 'v10' is possibly undefined
// 49E7B3: variable 'v11' is possibly undefined
// 49E7C2: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (0049E820) --------------------------------------------------------
signed int  Rules_HostClose(double context)
{
  int argCount; // eax
  void *v2; // ecx
  int logicalName; // eax

  argCount = Lexer_TokenExpect(1);
  if ( argCount == -1 )
    return 0;
  if ( !argCount )
    return IO_CloseAllNamedFiles(v2);
  logicalName = Rules_GetLogicalNameArg(1, 0, (int)(intptr_t)v2, context);
  if ( !logicalName )
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return IO_CloseNamedFile(logicalName);
}
// 49E846: variable 'v2' is possibly undefined

//----- (0049E890) --------------------------------------------------------
int  Rules_HostRemoveFile(double context)
{
  int v1; // ecx
  int result; // eax
  int v3; // edx
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v1, context);
  if ( result )
    return Rules_BloadDeleteFile(v4, v3);
  return result;
}
// 49E8B7: variable 'v1' is possibly undefined
// 49E8C0: variable 'v4' is possibly undefined
// 49E8C0: variable 'v3' is possibly undefined

//----- (0049E8D0) --------------------------------------------------------
const CHAR * Rules_HostRenameFile(double context)
{
  int v1; // ecx
  const CHAR *result; // eax
  const CHAR *oldFileName; // ecx

  if ( Lexer_TokenExpect(2) == -1 )
    return 0;
  result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(1, v1, context);
  if ( result )
  {
    result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(2, (int)(intptr_t)result, context);
    if ( result )
      return (const CHAR *)(uintptr_t)Rules_RenameFile(oldFileName, result, (int)(intptr_t)oldFileName);
  }
  return result;
}
// 49E8F9: variable 'v1' is possibly undefined
// 49E91B: variable 'v3' is possibly undefined
