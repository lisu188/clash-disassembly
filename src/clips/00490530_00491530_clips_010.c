/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00490530) --------------------------------------------------------
signed int  Lexer_IsCommandTextComplete(signed int result)
{
  int theString; // ecx
  int depth; // esi
  int moreThanZero; // edi
  int errorFlag; // ebp
  int charIndex; // eax
  unsigned __int8 theChar; // dl
  char lineChar; // dl
  _DWORD closedFlag[7]; // [esp+0h] [ebp-1Ch] BYREF

  theString = result;
  depth = 0;
  moreThanZero = 0;
  errorFlag = 0;
  if ( !result )
    return result;
  charIndex = 0;
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            theChar = *(_BYTE *)(uintptr_t)(theString + charIndex++);
            if ( !theChar )
              return 0;
            if ( theChar >= 0x20u )
              break;
            if ( theChar >= 0xAu )
            {
              if ( theChar <= 0xAu )
                goto LABEL_29;
              if ( theChar < 0xCu )
                goto LABEL_22;
              if ( theChar > 0xCu )
              {
                if ( theChar != 13 )
                  goto LABEL_22;
LABEL_29:
                if ( errorFlag )
                  return -1;
                if ( moreThanZero && !depth )
                  return 1;
              }
LABEL_7:
              charIndex = Str_SkipInlineWhitespaceAt(theString, charIndex);
            }
            else
            {
              if ( theChar == 9 )
                goto LABEL_7;
LABEL_22:
              if ( !depth && (IsTable[(unsigned __int8)(theChar + 1)] & 8) != 0 )
              {
                while ( 1 )
                {
                  lineChar = *(_BYTE *)(uintptr_t)(theString + charIndex++);
                  if ( !lineChar )
                    break;
                  if ( lineChar == 10 || lineChar == 13 )
                  {
                    if ( !errorFlag )
                      return 1;
                    return -1;
                  }
                }
                return 0;
              }
            }
          }
          if ( theChar <= 0x20u )
            goto LABEL_7;
          if ( theChar >= 0x28u )
            break;
          if ( theChar != 34 )
            goto LABEL_22;
          charIndex = Lexer_SkipQuotedStringSpan(theString, charIndex, closedFlag);
          if ( !depth && closedFlag[0] )
            moreThanZero = 1;
        }
        if ( theChar > 0x28u )
          break;
        if ( depth > 0 || !moreThanZero )
        {
          moreThanZero = 1;
          ++depth;
        }
      }
      if ( theChar > 0x29u )
        break;
      if ( depth <= 0 )
      {
        if ( !moreThanZero )
          errorFlag = 1;
      }
      else
      {
        --depth;
      }
    }
    if ( theChar != 59 )
      goto LABEL_22;
    charIndex = Lexer_SkipLineComment(theString, charIndex);
    if ( moreThanZero )
    {
      if ( !depth && *(_BYTE *)(uintptr_t)(theString + charIndex) )
        break;
    }
    if ( *(_BYTE *)(uintptr_t)(theString + charIndex) )
      ++charIndex;
  }
  if ( !errorFlag )
    return 1;
  return -1;
}
// 490549: variable 'v1' is possibly undefined

//----- (004906D0) --------------------------------------------------------
int  Lexer_SkipQuotedStringSpan(int theString, int pos, _DWORD *complete)
{
  int theChar; // eax
  int result; // eax

  theChar = *(unsigned __int8 *)(uintptr_t)(pos + theString);
  if ( theChar == 34 )
  {
LABEL_6:
    result = pos + 1;
    *complete = 1;
  }
  else
  {
    while ( 1 )
    {
      if ( theChar == 92 )
      {
        ++pos;
        theChar = *(unsigned __int8 *)(uintptr_t)(theString + pos);
      }
      if ( !theChar )
        break;
      ++pos;
      theChar = *(unsigned __int8 *)(uintptr_t)(theString + pos);
      if ( theChar == 34 )
        goto LABEL_6;
    }
    *complete = 0;
    return pos;
  }
  return result;
}

//----- (00490720) --------------------------------------------------------
int  Lexer_SkipLineComment(int theString, int pos)
{
  int newPos; // ecx
  unsigned __int8 *charPtr; // edx
  int i; // eax

  newPos = pos;
  charPtr = (unsigned __int8 *)(uintptr_t)(theString + pos);
  for ( i = *charPtr; i != 10; ++newPos )
  {
    if ( i == 13 )
      break;
    if ( !i )
      break;
    i = *++charPtr;
  }
  return newPos;
}

//----- (00490750) --------------------------------------------------------
int  Str_SkipInlineWhitespaceAt(int theString, int pos)
{
  int newPos; // ecx
  _BYTE *charPtr; // edx
  int i; // eax

  newPos = pos;
  charPtr = (_BYTE *)(uintptr_t)(theString + pos);
  for ( i = 0; ; i = 0 )
  {
    LOBYTE(i) = *charPtr;
    if ( i != 32 && i != 12 && i != 9 )
      break;
    ++charPtr;
    ++newPos;
  }
  return newPos;
}

//----- (004908A0) --------------------------------------------------------
signed int __thiscall Rules_PrintPrompt(void *this)
{
  signed int result; // eax

  result = Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WClips[0], (int)(intptr_t)aClips, (int)(intptr_t)this);
  if ( g_CLIPS_AfterPromptCallback )
    return g_CLIPS_AfterPromptCallback();
  return result;
}
// 51A620: using guessed type char *off_51A620[2];
// 51A994: using guessed type int (*dword_51A994)(void);

//----- (004908E0) --------------------------------------------------------
int  Rules_RouteCommand(int result, int printResult, int a3, double a4)
{
  int v5; // ecx
  _BYTE *v6; // ecx
  signed int errorFlag; // ebx
  int v8; // ecx
  int v9; // edx
  char *ppBuffer; // eax
  int v11; // ecx
  __int16 *theExpression; // eax
  _DWORD *freedExprNode; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  __int16 *v17; // ecx
  _DWORD *v18; // edx
  __int16 *v19; // ecx
  __int16 *v20; // ecx
  int v21; // ecx
  int v22; // ecx
  _DWORD theResult[6]; // [esp-4h] [ebp-34h] BYREF
  unsigned int tokenType; // [esp+14h] [ebp-1Ch] BYREF
  int *tokenValue; // [esp+18h] [ebp-18h]
  int v26 CLASH95_UNUSED; // [esp+28h] [ebp-8h]

  v26 = a3;
  if ( !result )
    return result;
  IO_OpenStringSource((int)(intptr_t)aCommand_2, (const char *)(uintptr_t)result, 0);
  Parser_NextToken((int)(intptr_t)aCommand_2, (int)(intptr_t)&tokenType);
  if ( tokenType == 2 || tokenType == 3 || tokenType < 2 || tokenType == 8 )
  {
    IO_CloseStringRouter((int)(intptr_t)aCommand_2);
    if ( printResult )
    {
      Rules_PrintAtomValue((int)(intptr_t)aStdout, tokenType, tokenValue);
      Output_Write((int)(intptr_t)aStdout, (int)(intptr_t)asc_504990, v5);
    }
    return 1;
  }
  if ( tokenType != 13 )
  {
    if ( tokenType != 100 )
    {
      Rules_PrintErrorID((int)(intptr_t)aCommline, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedACon_0, v15);
      IO_CloseStringRouter((int)(intptr_t)aCommand_2);
      return 0;
    }
    Parser_NextToken((int)(intptr_t)aCommand_2, (int)(intptr_t)&tokenType);
    if ( tokenType == 2 )
    {
      errorFlag = Rules_ParseConstruct();
      if ( errorFlag != -1 )
      {
        IO_CloseStringRouter((int)(intptr_t)aCommand_2);
        if ( v9 == 1 )
        {
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aError_1, v8);
          ppBuffer = (char *)(uintptr_t)Rules_GetPPBuffer();
          Output_WriteLongString((signed int)(intptr_t)g_IO_LogicalNameTable_WError[0], ppBuffer);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504990, v11);
        }
        Rules_DestroyPPBuffer();
        return errorFlag;
      }
      g_Rules_EvaluatingTopLevelCommand = 1;
      Parser_ParseFunctionCallExpr((int)(intptr_t)aCommand_2, v6);
      g_Rules_EvaluatingTopLevelCommand = 0;
      Parser_FreeLoopContextStack();
      IO_CloseStringRouter((int)(intptr_t)aCommand_2);
      if ( v17 )
      {
        g_ClipsCommandEvalInProgress = 1;
        AST_InstallNodeChain(v17);
        Parser_ParseForm(v19, v18, (int)(intptr_t)v19, a4);
        AST_DeinstallNodeChain(v20);
        g_ClipsCommandEvalInProgress = 0;
        AST_Free(v21);
        if ( theResult[1] != 105 && printResult )
        {
          Rules_PrintDataObject((int)(intptr_t)aStdout, (int)(intptr_t)theResult);
          Output_Write((int)(intptr_t)aStdout, (int)(intptr_t)asc_504990, v22);
        }
        return 1;
      }
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aCommline, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAComma, v16);
      IO_CloseStringRouter((int)(intptr_t)aCommand_2);
    }
    return 0;
  }
  IO_CloseStringRouter((int)(intptr_t)aCommand_2);
  theExpression = (__int16 *)(uintptr_t)AST_NewNode(tokenType, (int)(intptr_t)tokenValue);
  Parser_ParseForm(theExpression, theResult, (int)(intptr_t)theExpression, a4);
  g_ClipsMemFreeListTemp = (int)(intptr_t)freedExprNode;
  *freedExprNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
  if ( printResult )
  {
    Rules_PrintDataObject((int)(intptr_t)aStdout, (int)(intptr_t)theResult);
    Output_Write((int)(intptr_t)aStdout, (int)(intptr_t)asc_504990, v14);
  }
  return 1;
}
// 49095D: simplified comparisons for '%var_1C.4': ==0 || ==1 became <2u
// 490949: variable 'v5' is possibly undefined
// 4909C1: variable 'v9' is possibly undefined
// 4909CD: variable 'v8' is possibly undefined
// 4909F0: variable 'v11' is possibly undefined
// 490A29: variable 'v13' is possibly undefined
// 490A5C: variable 'v14' is possibly undefined
// 490A89: variable 'v15' is possibly undefined
// 490ABD: variable 'v16' is possibly undefined
// 490AEA: variable 'v6' is possibly undefined
// 490B08: variable 'v17' is possibly undefined
// 490B1B: variable 'v19' is possibly undefined
// 490B1B: variable 'v18' is possibly undefined
// 490B22: variable 'v20' is possibly undefined
// 490B2F: variable 'v21' is possibly undefined
// 490B55: variable 'v22' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A97C: using guessed type int dword_51A97C;
// 51A988: using guessed type int dword_51A988;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00490B70) --------------------------------------------------------
BOOL __thiscall Lexer_ClassifyNextStdinChar(void *this)
{
  int readChar; // eax
  unsigned __int8 inchar; // dl

  readChar = Lexer_PeekChar((int)(intptr_t)aStdin_1, (unsigned int)(intptr_t)this);
  inchar = readChar;
  if ( readChar == -1 )
    inchar = 10;
  return Lexer_AppendCharToPendingToken(inchar);
}

//----- (00490BB0) --------------------------------------------------------
int Rules_IsEvaluatingTopLevelCommand(void)
{
  return g_Rules_EvaluatingTopLevelCommand;
}
// 51A988: using guessed type int dword_51A988;

//----- (00490BC0) --------------------------------------------------------
_DWORD *Rules_InitializeDefrules(void)
{
  _DWORD *result; // eax

  Rules_RegisterAgendaWatchFlags();
  Rules_RegisterAgendaCommands();
  Rules_RegisterDefruleModuleItem();
  Rules_AddReservedPatternSymbol((int)(intptr_t)aAnd_2, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aNot_2, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aOr_2, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aTest, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aLogical, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aExists, 0);
  Rules_AddReservedPatternSymbol((int)(intptr_t)aForall, 0);
  Rules_DefruleCommandDefinitions();
  Rules_RegisterRuleCommands();
  result = Rules_RegisterConstructType(
             (int)(intptr_t)aDefrule,
             (int)(intptr_t)aDefrules,
             (int)(intptr_t)Rules_FindDefruleByName,
             (int)(intptr_t)Rules_ParseDefrule,
             (int)(intptr_t)Rules_GetConstructNameSymbol,
             (int)(intptr_t)Rules_GetModuleConstructListHead,
             (int)(intptr_t)Rules_GetConstructOwnerModule,
             (int)(intptr_t)Rules_GetNextDefrule,
             (int)(intptr_t)Rules_SetConstructNextInModule,
             (int)(intptr_t)Rules_IsDefruleDeletable,
             (int)(intptr_t)Rules_DeleteDefruleOrAll,
             (int)(intptr_t)Rules_FreeDefruleDisjunctChain);
  g_DefruleConstructTypePtr = (int)(intptr_t)result;
  return result;
}
// 54E648: using guessed type int dword_54E648;

//----- (00490C80) --------------------------------------------------------
int Rules_RegisterDefruleModuleItem(void)
{
  int result; // eax

  result = Module_RegisterItem(
             (int)(intptr_t)aDefrule,
             (int)(intptr_t)Rules_AllocateDefruleModule,
             (int)(intptr_t)Rules_JoinNetworkModuleRecord,
             (int)(intptr_t)Rules_FreeDefruleModule,
             (int)(intptr_t)Rules_WriteJoinHashStructRef,
             (int)(intptr_t)Rules_FindDefruleByName);
  g_DefruleConstructClass = result;
  return result;
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490CB0) --------------------------------------------------------
signed int Rules_AllocateDefruleModule(void)
{
  _DWORD *freeListEntry; // edx
  signed int result; // eax

  freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListEntry;
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(uintptr_t)(g_ClipsMemFreeListTemp + 12) = 0;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x10);
    *(_DWORD *)(uintptr_t)(result + 12) = 0;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00490CF0) --------------------------------------------------------
int  Rules_FreeDefruleModule(int theItem)
{
  int result; // eax

  result = Rules_ClearModuleConstructList(theItem, g_DefruleConstructTypePtr, theItem);
  g_ClipsMemFreeListTemp = theItem;
  *(_DWORD *)(uintptr_t)theItem = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E648: using guessed type int dword_54E648;

//----- (00490D30) --------------------------------------------------------
int  Rules_GetDefruleModuleItem(int theModule)
{
  return Rules_GetModuleConstructData(theModule, g_DefruleConstructClass);
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490D40) --------------------------------------------------------
int  Rules_FindDefruleByName(_BYTE *defruleName, int a2 CLASH95_UNUSED)
{
  return Rules_FindConstructByNameGeneric(defruleName, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (00490D50) --------------------------------------------------------
int  Rules_GetNextDefrule(int defrulePtr)
{
  return Class_Enum(defrulePtr, g_DefruleConstructClass);
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490D60) --------------------------------------------------------
BOOL Rules_IsDefruleDeletable(void)
{
  int v0; // edx
  int theDefrule; // eax

  if ( Rules_IsBloaded() )
    return 0;
  theDefrule = v0;
  if ( v0 )
  {
    while ( *(char *)(uintptr_t)(theDefrule + 29) >= 0 )
    {
      theDefrule = *(_DWORD *)(uintptr_t)(theDefrule + 48);
      if ( !theDefrule )
        return !g_Rules_JoinOperationInProgress;
    }
    return 0;
  }
  return !g_Rules_JoinOperationInProgress;
}
// 490D6C: variable 'v0' is possibly undefined
// 51A954: using guessed type int dword_51A954;

//----- (00490DA0) --------------------------------------------------------
signed int  Rules_DeriveDefaultFromConstraints(char *constraints, _DWORD *theDefault, int multifield)
{
  _DWORD *defaultObj; // ecx
  signed int result; // eax
  int v6; // edx
  signed int *v7; // eax
  int v8; // edx
  int standardValue; // ebx
  int theType; // eax
  int fieldType; // esi
  int *v12; // eax
  void **theValue; // edi
  int v14; // ebx
  signed int fieldCount; // edx
  int v16; // edx
  int v17; // ecx
  char constraintFlags; // dl
  signed int *v19; // eax
  int *zeroInteger; // eax
  signed int *v21; // eax
  int v22; // edx

  defaultObj = theDefault;
  if ( !constraints )
  {
    if ( multifield )
    {
      theDefault[1] = 4;
      theDefault[4] = -1;
      theDefault[3] = 0;
      result = (signed int)(intptr_t)Rules_CreateEphemeralMultifield(0);
    }
    else
    {
      theDefault[1] = 2;
      result = (signed int)(intptr_t)Str_Intern(aNil, (int)(intptr_t)theDefault);
    }
    *(_DWORD *)(uintptr_t)(v6 + 8) = result;
    return result;
  }
  if ( (*constraints & 1) != 0 || (constraintFlags = *constraints, (*constraints & 2) != 0) )
  {
    v7 = Str_Intern(aNil, (int)(intptr_t)defaultObj);
    v8 = (int)(intptr_t)constraints;
    standardValue = (int)(intptr_t)v7;
    theType = 2;
    fieldType = 2;
LABEL_9:
    v12 = Rules_DeriveNumericDefaultFromRange(theType, v8, standardValue, fieldType);
LABEL_10:
    theValue = (void **)v12;
    goto LABEL_11;
  }
  if ( (constraintFlags & 4) != 0 )
  {
    v19 = Str_Intern(g_Rules_DefaultEmptyStringConstraint, (int)(intptr_t)defaultObj);
    v8 = (int)(intptr_t)constraints;
    standardValue = (int)(intptr_t)v19;
    theType = 3;
    fieldType = 3;
    goto LABEL_9;
  }
  if ( (constraintFlags & 0x10) != 0 )
  {
    zeroInteger = Rules_AddIntegerValue(0);
    v8 = (int)(intptr_t)constraints;
    standardValue = (int)(intptr_t)zeroInteger;
    theType = 1;
    fieldType = 1;
    goto LABEL_9;
  }
  if ( (constraintFlags & 8) != 0 )
  {
    standardValue = Rules_AddDoubleValue(0.0);
    theType = 0;
    fieldType = 0;
    goto LABEL_9;
  }
  if ( (constraintFlags & 0x20) != 0 )
  {
    v21 = Str_Intern(aNil, (int)(intptr_t)defaultObj);
    v8 = (int)(intptr_t)constraints;
    standardValue = (int)(intptr_t)v21;
    theType = 8;
    fieldType = 8;
    goto LABEL_9;
  }
  if ( (constraintFlags & 0x40) != 0 )
  {
    LOWORD(fieldType) = 7;
    theValue = &g_Instance_DummyInstanceRecord;
    goto LABEL_11;
  }
  if ( (constraints[1] & 1) != 0 )
  {
    LOWORD(fieldType) = 6;
    theValue = &g_Rules_DummyFactPtr;
    goto LABEL_11;
  }
  if ( *constraints >= 0 )
  {
    LOWORD(fieldType) = 2;
    v12 = Str_Intern(aNil, (int)(intptr_t)defaultObj);
    goto LABEL_10;
  }
  LOWORD(fieldType) = 5;
  theValue = 0;
LABEL_11:
  if ( multifield )
  {
    v14 = *(_DWORD *)(constraints + 18);
    if ( v14 )
    {
      v22 = *(_DWORD *)(uintptr_t)(v14 + 2);
      if ( v22 == g_Clips_NegativeInfinitySymbol )
        fieldCount = g_Clips_NegativeInfinitySymbol ^ v22;
      else
        fieldCount = *(_DWORD *)(uintptr_t)(v22 + 16);
    }
    else
    {
      fieldCount = 0;
    }
    defaultObj[1] = 4;
    defaultObj[4] = fieldCount - 1;
    defaultObj[3] = 0;
    result = (signed int)(intptr_t)Rules_CreateEphemeralMultifield(fieldCount);
    *(_DWORD *)(uintptr_t)(v17 + 8) = result;
    if ( v16 > 0 )
    {
      result = 6 * v16 - 6;
      do
      {
        *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v17 + 8) + result + 14) = fieldType;
        result -= 6;
        --v16;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v17 + 8) + result + 22) = theValue;
      }
      while ( result > -6 );
    }
  }
  else
  {
    result = (__int16)fieldType;
    defaultObj[2] = theValue;
    defaultObj[1] = (__int16)fieldType;
  }
  return result;
}
// 490DCC: variable 'v6' is possibly undefined
// 490E0C: variable 'v8' is possibly undefined
// 490E2D: variable 'v4' is possibly undefined
// 490E45: variable 'v17' is possibly undefined
// 490E4A: variable 'v16' is possibly undefined
// 51A114: using guessed type void *off_51A114;
// 51A214: using guessed type void *off_51A214;
// 54DD60: using guessed type int dword_54DD60;

//----- (00490F90) --------------------------------------------------------
int * Rules_DeriveNumericDefaultFromRange(int theType, int theConstraints, int standardValue, int a4)
{
  __int16 *theList; // eax
  double theValue; // st7
  int v8; // [esp+8h] [ebp-Ch]

  theList = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraints + 6);
  if ( theList )
  {
    while ( *theList != theType )
    {
      theList = *(__int16 **)(theList + 5);
      if ( !theList )
        goto LABEL_4;
    }
    return *(int **)(theList + 1);
  }
LABEL_4:
  if ( theType == 1 )
  {
    theList = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraints + 10);
    if ( *theList != 1 )
    {
      if ( !*theList )
      {
LABEL_11:
        theValue = *(double *)(uintptr_t)(*(_DWORD *)(theList + 1) + 16);
        _CHP(v8, a4);
        return Rules_AddIntegerValue((int)theValue);
      }
      theList = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraints + 14);
      if ( *theList != 1 )
      {
        if ( *theList )
          return (int *)(uintptr_t)standardValue;
        goto LABEL_11;
      }
    }
    return *(int **)(theList + 1);
  }
  if ( theType )
    return (int *)(uintptr_t)standardValue;
  theList = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraints + 10);
  if ( !*theList )
    return *(int **)(theList + 1);
  if ( *theList != 1 )
  {
    theList = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraints + 14);
    if ( !*theList )
      return *(int **)(theList + 1);
    if ( *theList != 1 )
      return (int *)(uintptr_t)standardValue;
  }
  return (int *)(uintptr_t)Rules_AddDoubleValue((double)*(int *)(uintptr_t)(*(_DWORD *)(theList + 1) + 16));
}
// 490F90: could not find valid save-restore pair for esi
// 490FE8: variable 'v8' is possibly undefined

//----- (00491040) --------------------------------------------------------
int  Rules_ParseDefaultAttribute(
        int readSource,
        int multifield,
        int constantsOnly,
        int dynamic,
        double a5,
        _DWORD *noneSpecified,
        _DWORD *deriveSpecified,
        _DWORD *error)
{
  int defaultList; // esi
  int v10; // edx
  int v11; // ecx
  _WORD *lastDefault; // ebx
  _WORD *v13; // eax
  int v14; // ecx
  int defaultKind; // ecx
  _WORD *exprToFree; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int v23; // ebx
  int v24; // ecx
  char *theConstraint; // eax
  _DWORD *v26; // edx
  int oldDefaultList; // edi
  _DWORD *v28; // edx
  __int16 *v29; // ecx
  int v30; // ecx
  signed int newExpr; // eax
  int v32; // ecx
  _DWORD theValue[6]; // [esp+0h] [ebp-40h] BYREF
  _DWORD theToken[3]; // [esp+18h] [ebp-28h] BYREF
  int constantsOnlyFlag; // [esp+24h] [ebp-1Ch]
  int dynamicFlag; // [esp+28h] [ebp-18h]
  int multifieldFlag; // [esp+2Ch] [ebp-14h]
  _WORD *newItem; // [esp+30h] [ebp-10h]

  multifieldFlag = multifield;
  dynamicFlag = dynamic;
  constantsOnlyFlag = constantsOnly;
  defaultList = 0;
  *noneSpecified = 0;
  *deriveSpecified = 0;
  IO_OutWriteToken(asc_504A54);
  Parser_NextToken(readSource, v10);
  lastDefault = 0;
  if ( theToken[0] == 101 )
  {
LABEL_28:
    IO_OutNewline();
    IO_OutNewline();
    v23 = multifieldFlag;
    IO_OutWriteToken(asc_504A98);
    if ( v23 )
      goto LABEL_37;
    if ( !defaultList || *(_DWORD *)(uintptr_t)(defaultList + 10) )
    {
      *error = 1;
    }
    else
    {
      theConstraint = Rules_BuildLHSNodeFromToken((__int16 *)(uintptr_t)defaultList);
      theConstraint[1] &= ~0x80u;
      if ( Rules_ConstraintIsUnmatchable(theConstraint) )
        *error = 1;
      AST_DecrementNodeRefCount(v26);
      if ( !*error )
      {
LABEL_37:
        if ( dynamicFlag || !constantsOnlyFlag || !defaultList )
          return defaultList;
        oldDefaultList = defaultList;
        defaultList = 0;
        do
        {
          Lexer_ErrorRecover(0);
          if ( Parser_ParseForm(v29, v28, (int)(intptr_t)v29, a5) )
            *error = 1;
          if ( theValue[1] == 4 && !multifieldFlag && !*error )
          {
            Rules_PrintErrorID((int)(intptr_t)aDefault_0, 1, 1);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheDefaultValu, v30);
            *error = 1;
LABEL_47:
            exprToFree = (_WORD *)(uintptr_t)oldDefaultList;
            goto LABEL_9;
          }
          if ( *error )
            goto LABEL_47;
          newExpr = AST_BuildExpressionFromValue(theValue);
          defaultList = AST_AppendNodeList(defaultList, newExpr);
        }
        while ( *(_DWORD *)(uintptr_t)(v32 + 10) );
        AST_Free(oldDefaultList);
        return defaultList;
      }
    }
    Rules_PrintErrorID((int)(intptr_t)aDefault_0, 1, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheDefaultValu, v24);
    AST_Free(defaultList);
    return 0;
  }
  while ( 1 )
  {
    v13 = (_WORD *)(uintptr_t)Parser_ParseSingleExpression(readSource, (__int16 *)theToken, v11);
    newItem = v13;
    if ( !v13 )
      goto LABEL_10;
    if ( *v13 == 15 || *v13 == 16 )
      break;
    if ( AST_TreeContainsSpecialTag((int)(intptr_t)v13, 0) == 1 )
    {
      AST_Free(defaultList);
      AST_Free(v21);
      *error = 1;
      Parser_ReportSyntaxError();
      return 0;
    }
    if ( lastDefault )
      *(_DWORD *)(lastDefault + 5) = v20;
    else
      defaultList = v20;
    IO_OutWriteToken(asc_504A54);
    Parser_NextToken(readSource, v22);
    v11 = theToken[0];
    lastDefault = newItem;
    if ( theToken[0] == 101 )
      goto LABEL_28;
  }
  if ( !strcmp_(v13, aNone_0) )
  {
    defaultKind = 0;
  }
  else if ( !strcmp_(v14, aDerive) )
  {
    defaultKind = 1;
  }
  else
  {
    defaultKind = -1;
  }
  if ( dynamicFlag || *newItem == 16 || defaultKind == -1 || defaultList )
  {
    Parser_ReportSyntaxError();
    exprToFree = newItem;
LABEL_9:
    AST_Free((int)(intptr_t)exprToFree);
LABEL_10:
    AST_Free(defaultList);
    *error = 1;
    return 0;
  }
  AST_Free((int)(intptr_t)newItem);
  Parser_NextToken(readSource, v18);
  if ( theToken[0] != 101 )
  {
    Parser_ReportSyntaxError();
    IO_OutNewline();
    IO_OutWriteToken(asc_504A54);
    IO_OutWriteToken((char *)(uintptr_t)theToken[2]);
    *error = 1;
  }
  if ( v19 )
    *deriveSpecified = 1;
  else
    *noneSpecified = 1;
  return 0;
}
// 49113F: conditional instruction was optimized away because ecx.4<2u
// 49130A: conditional instruction was optimized away because edi.4!=0
// 491076: variable 'v10' is possibly undefined
// 491090: variable 'v11' is possibly undefined
// 491119: variable 'v14' is possibly undefined
// 491154: variable 'v18' is possibly undefined
// 491192: variable 'v19' is possibly undefined
// 4911E8: variable 'v21' is possibly undefined
// 49122A: variable 'v20' is possibly undefined
// 49123C: variable 'v22' is possibly undefined
// 491298: variable 'v24' is possibly undefined
// 4912E1: variable 'v26' is possibly undefined
// 49131B: variable 'v29' is possibly undefined
// 49131B: variable 'v28' is possibly undefined
// 491353: variable 'v30' is possibly undefined
// 491390: variable 'v32' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004913B0) --------------------------------------------------------
signed int Module_InitializeDefmodules(void)
{
  Module_RegisterDefmoduleCommands();
  Module_CreateMainModule();
  Rules_RegisterConstructType((int)(intptr_t)aDefmodule, (int)(intptr_t)aDefmodules, 0, (int)(intptr_t)Module_ParseDefmoduleConstruct, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_RegisterHostFunction(aGetCurrentModu, 119, (int)(intptr_t)aGetcurrentmodu, (int)(intptr_t)Module_GetCurrentCommand, (int)(intptr_t)a00_0);
  return Rules_RegisterHostFunction(aSetCurrentModu, 119, (int)(intptr_t)aSetcurrentmodu, (int)(intptr_t)Module_SetCurrentCommand, (int)(intptr_t)a11w_0);
}

//----- (00491430) --------------------------------------------------------
int  Module_RegisterItem(int theItem, int allocateFunction, int bloadModuleReference, int freeFunction, int constructsToCModuleReference, int findFunction)
{
  _DWORD *freeListEntry; // edi
  _DWORD *newModuleItem; // eax
  int moduleIndex; // edx

  freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *freeListEntry;
    newModuleItem = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newModuleItem = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  *newModuleItem = theItem;
  newModuleItem[2] = allocateFunction;
  newModuleItem[3] = freeFunction;
  newModuleItem[4] = bloadModuleReference;
  newModuleItem[5] = constructsToCModuleReference;
  newModuleItem[6] = findFunction;
  moduleIndex = g_ClipsModuleItemCount++;
  newModuleItem[7] = 0;
  newModuleItem[1] = moduleIndex;
  if ( g_Module_ItemListTail )
    *(_DWORD *)(uintptr_t)(g_Module_ItemListTail + 28) = newModuleItem;
  else
    g_ModuleItemDescriptorListHead = (int)(intptr_t)newModuleItem;
  g_Module_ItemListTail = (int)(intptr_t)newModuleItem;
  return newModuleItem[1];
}
// 49145F: variable 'a3' is possibly undefined
// 51A99C: using guessed type int dword_51A99C;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004914D0) --------------------------------------------------------
int Module_GetItemList(void)
{
  return g_ModuleItemDescriptorListHead;
}
// 51A9BC: using guessed type int dword_51A9BC;

//----- (004914E0) --------------------------------------------------------
int Module_GetItemCount(void)
{
  return g_ClipsModuleItemCount;
}
// 51A9B8: using guessed type int dword_51A9B8;

//----- (004914F0) --------------------------------------------------------
int  Module_FindItemByName(int moduleItemName)
{
  int current; // ecx

  current = g_ModuleItemDescriptorListHead;
  while ( current )
  {
    if ( !strcmp_(*(_DWORD *)(uintptr_t)current, moduleItemName) )
      return current;
    current = *(_DWORD *)(uintptr_t)(current + 28);
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9BC: using guessed type int dword_51A9BC;

//----- (00491520) --------------------------------------------------------
int Module_GetCurrent(void)
{
  return g_Clips_CurrentModule;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00491530) --------------------------------------------------------
int  Module_SetCurrent(int newModule)
{
  int oldModule; // ecx
  int changeFunction; // edx
  int v3; // edx

  oldModule = g_Clips_CurrentModule;
  g_Clips_CurrentModule = newModule;
  if ( g_Module_ChangeNotifyEnabled )
  {
    changeFunction = g_CLIPS_AfterModuleChangeListHead;
    ++g_Module_ChangeGeneration;
    if ( g_CLIPS_AfterModuleChangeListHead )
    {
      do
      {
        (*(void (__fastcall **)(int))(uintptr_t)(changeFunction + 4))(oldModule);
        changeFunction = *(_DWORD *)(uintptr_t)(v3 + 12);
      }
      while ( changeFunction );
    }
  }
  return oldModule;
}
// 49155F: variable 'v1' is possibly undefined
// 491562: variable 'v3' is possibly undefined
// 51A9A0: using guessed type int dword_51A9A0;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 51A9C0: using guessed type int dword_51A9C0;
