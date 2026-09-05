/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "runtime_shared_state.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004E03F0) --------------------------------------------------------
int  Compiler_WriteDefinstancesConstructToCode(int theFile, int theDefinstances, int maxIndices, int moduleCount)
{
  int *itemNames; // eax
  DWORD constructPrefix; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theDefinstances, theFile, (int)(intptr_t)asc_50E3D0, v15);
  itemNames = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_DefinstancesCodeGenItem + 20);
  constructPrefix = *itemNames;
  Rules_WriteConstructHeaderToCode(theFile, theDefinstances, v8, moduleCount, *itemNames, itemNames[1]);
  Output_WriteFormatted(v10, v9, theFile, (int)(intptr_t)a0_2, v16);
  Rules_ExpressionToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefinstances + 24), v11, constructPrefix);
  return Output_WriteFormatted(v13, v12, theFile, (int)(intptr_t)asc_50E3D4, v17);
}
// 4E03FD: variable 'v15' is possibly undefined
// 4E041D: variable 'v8' is possibly undefined
// 4E0428: variable 'v10' is possibly undefined
// 4E0428: variable 'v9' is possibly undefined
// 4E0428: variable 'v16' is possibly undefined
// 4E0435: variable 'v11' is possibly undefined
// 4E0440: variable 'v13' is possibly undefined
// 4E0440: variable 'v12' is possibly undefined
// 4E0440: variable 'v17' is possibly undefined
// 54E918: using guessed type int dword_54E918;

//----- (004E0450) --------------------------------------------------------
char * Parser_ParseInstanceQueryNoAction(int top, int readSource)
{
  char *result; // eax
  char *insQuerySetVars; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int queryInputToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  queryInputToken[5] = readSource;
  result = (char *)(uintptr_t)Parser_ParseInstanceQueryRestrictions(top, queryInputToken);
  insQuerySetVars = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v9, v8);
      if ( queryInputToken[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(uintptr_t)(top + 6), 0, 1);
        AST_Free((int)(intptr_t)insQuerySetVars);
        return (char *)(uintptr_t)top;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(top);
        AST_Free((int)(intptr_t)insQuerySetVars);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)(intptr_t)insQuerySetVars);
      return 0;
    }
  }
  return result;
}
// 4E047A: variable 'v6' is possibly undefined
// 4E047A: variable 'v5' is possibly undefined
// 4E0483: variable 'v7' is possibly undefined
// 4E049A: variable 'v9' is possibly undefined
// 4E049A: variable 'v8' is possibly undefined

//----- (004E0510) --------------------------------------------------------
char * Parser_ParseInstanceQueryAction(int top, int readSource)
{
  char *result; // eax
  char *insQuerySetVars; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int queryInputToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  queryInputToken[5] = readSource;
  result = (char *)(uintptr_t)Parser_ParseInstanceQueryRestrictions(top, queryInputToken);
  insQuerySetVars = result;
  if ( result )
  {
    Rules_IncrementIndentDepth(3);
    AST_Append(v6, v5);
    if ( Parser_ParseInstanceQueryTestExpression(v7, v7) && (AST_Append(v9, v8), Parser_ParseInstanceQueryActionExpression(top, v10, (int)(intptr_t)insQuerySetVars)) )
    {
      Rules_DecrementIndentDepth(3);
      Parser_NextToken(v12, v11);
      if ( queryInputToken[0] == 101 )
      {
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(uintptr_t)(top + 6), 0, 1);
        Parser_ReplaceInstanceQuerySlotReferences(insQuerySetVars, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(top + 6) + 10), 0, 0);
        AST_Free((int)(intptr_t)insQuerySetVars);
        return (char *)(uintptr_t)top;
      }
      else
      {
        Parser_ReportSyntaxError();
        AST_Free(top);
        AST_Free((int)(intptr_t)insQuerySetVars);
        return 0;
      }
    }
    else
    {
      Rules_DecrementIndentDepth(3);
      AST_Free((int)(intptr_t)insQuerySetVars);
      return 0;
    }
  }
  return result;
}
// 4E053A: variable 'v6' is possibly undefined
// 4E053A: variable 'v5' is possibly undefined
// 4E0543: variable 'v7' is possibly undefined
// 4E054C: variable 'v9' is possibly undefined
// 4E054C: variable 'v8' is possibly undefined
// 4E0557: variable 'v10' is possibly undefined
// 4E056E: variable 'v12' is possibly undefined
// 4E056E: variable 'v11' is possibly undefined

//----- (004E05F0) --------------------------------------------------------
int  Parser_ParseInstanceQueryRestrictions(int top, int *queryInputToken)
{
  int insQuerySetVars; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int initialTokenType; // ebx
  int v10; // ecx
  int varScan; // eax
  signed int memberVarNode; // eax
  int v13; // ecx
  signed int classExp; // eax
  signed int lastClassExp; // ebx
  int v16; // ecx
  signed int nextClassExp; // eax
  signed int delimiterExp; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // edx
  signed int v24; // edx
  int parseError; // [esp+0h] [ebp-20h] BYREF
  signed int lastOne; // [esp+4h] [ebp-1Ch]
  signed int lastInsQuerySetVars; // [esp+8h] [ebp-18h]
  int classExpChain; // [esp+Ch] [ebp-14h]

  insQuerySetVars = 0;
  lastInsQuerySetVars = 0;
  parseError = 0;
  IO_OutWriteToken(asc_50E3F8);
  classExpChain = 0;
  Parser_NextToken(v6, v5);
  initialTokenType = *queryInputToken;
  lastOne = 0;
  if ( initialTokenType == 100 && (Parser_NextToken(v7, (int)(intptr_t)queryInputToken), *queryInputToken == 100) )
  {
    while ( *queryInputToken == 100 )
    {
      Parser_NextToken(v10, (int)(intptr_t)queryInputToken);
      if ( *queryInputToken != 15 )
        goto LABEL_2;
      varScan = insQuerySetVars;
      if ( insQuerySetVars )
      {
        while ( *(_DWORD *)(uintptr_t)(varScan + 2) != queryInputToken[1] )
        {
          varScan = *(_DWORD *)(uintptr_t)(varScan + 10);
          if ( !varScan )
            goto LABEL_12;
        }
        Rules_PrintErrorID((int)(intptr_t)aInsqypsr, 1, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDuplicateIns_0, v20);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(top + 2) + 16), v21);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__27, v22);
        goto LABEL_3;
      }
LABEL_12:
      memberVarNode = AST_NewNode(15, queryInputToken[1]);
      if ( insQuerySetVars )
        *(_DWORD *)(uintptr_t)(lastInsQuerySetVars + 10) = memberVarNode;
      else
        insQuerySetVars = memberVarNode;
      lastInsQuerySetVars = memberVarNode;
      IO_OutWriteToken(asc_50E3F8);
      classExp = Parser_ParseArgument(v13, &parseError, v13);
      lastClassExp = classExp;
      classExpChain = classExp;
      if ( parseError )
        goto LABEL_3;
      if ( !classExp )
        goto LABEL_2;
      if ( !Rules_ReplaceClassNameWithClassReference(classExp) )
        goto LABEL_3;
      IO_OutWriteToken(asc_50E3F8);
      while ( 1 )
      {
        nextClassExp = Parser_ParseArgument(v16, &parseError, v16);
        if ( !nextClassExp )
          break;
        if ( !Rules_ReplaceClassNameWithClassReference(nextClassExp) )
          goto LABEL_3;
        *(_DWORD *)(uintptr_t)(lastClassExp + 10) = v23;
        IO_OutWriteToken(asc_50E3F8);
        lastClassExp = v24;
      }
      if ( parseError )
        goto LABEL_3;
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50E444);
      delimiterExp = AST_NewNode(2, g_InternedSym_Qds);
      *(_DWORD *)(uintptr_t)(lastClassExp + 10) = delimiterExp;
      if ( *(_DWORD *)(uintptr_t)(top + 6) )
        *(_DWORD *)(uintptr_t)(lastOne + 10) = classExpChain;
      else
        *(_DWORD *)(uintptr_t)(top + 6) = classExpChain;
      lastOne = delimiterExp;
      IO_OutWriteToken(asc_50E3F8);
      Parser_NextToken(v19, (int)(intptr_t)queryInputToken);
      classExpChain = 0;
    }
    if ( *queryInputToken != 101 )
      goto LABEL_2;
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50E444);
    return insQuerySetVars;
  }
  else
  {
LABEL_2:
    Parser_ReportSyntaxError();
LABEL_3:
    AST_Free(classExpChain);
    AST_Free(top);
    AST_Free(insQuerySetVars);
    return 0;
  }
}
// 4E0618: variable 'v6' is possibly undefined
// 4E0618: variable 'v5' is possibly undefined
// 4E0657: variable 'v7' is possibly undefined
// 4E068E: variable 'v10' is possibly undefined
// 4E06DC: variable 'v13' is possibly undefined
// 4E0716: variable 'v16' is possibly undefined
// 4E077E: variable 'v19' is possibly undefined
// 4E07A7: variable 'v20' is possibly undefined
// 4E07B9: variable 'v21' is possibly undefined
// 4E07C8: variable 'v22' is possibly undefined
// 4E07F0: variable 'v23' is possibly undefined
// 4E07F8: variable 'v24' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B454: using guessed type int dword_51B454;

//----- (004E0810) --------------------------------------------------------
signed int  Rules_ReplaceClassNameWithClassReference(int theExp)
{
  int *theDefclass; // eax
  int v4; // ecx

  if ( *(_WORD *)(uintptr_t)theExp != 2 )
    return 1;
  theDefclass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theExp + 2) + 16));
  if ( theDefclass )
  {
    *(_WORD *)(uintptr_t)theExp = 57;
    *(_DWORD *)(uintptr_t)(theExp + 2) = theDefclass;
    return 1;
  }
  else
  {
    Rules_ReportCantFindItem(v4, v4);
    return 0;
  }
}
// 4E084A: variable 'v4' is possibly undefined

//----- (004E0860) --------------------------------------------------------
signed int __fastcall Parser_ParseInstanceQueryTestExpression(int top CLASH95_UNUSED, int readSource)
{
  int oldBindList; // ebx
  _DWORD *v4; // edx
  int v5; // ecx
  signed int queryTest; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx

  oldBindList = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  queryTest = Parser_ParseArgument(readSource, v4, v5);
  if ( queryTest )
  {
    *(_DWORD *)(uintptr_t)(queryTest + 10) = *(_DWORD *)(uintptr_t)(v7 + 6);
    *(_DWORD *)(uintptr_t)(v7 + 6) = queryTest;
    if ( Parser_LoopContextStackIsEmpty() )
    {
      Parser_SetLoopContextStack(oldBindList);
      return 1;
    }
    else
    {
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(oldBindList);
      Rules_PrintErrorID((int)(intptr_t)aInsqypsr, v8, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aBindsAreNotA_0, v9);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v10 + 2) + 16), v10);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__27, v11);
      AST_Free(v12);
      return 0;
    }
  }
  else
  {
    Parser_SetLoopContextStack(oldBindList);
    Parser_ReportSyntaxError();
    AST_Free(v14);
    return 0;
  }
}
// 4E088A: conditional instruction was optimized away because %var_10.4==0
// 4E0881: variable 'v4' is possibly undefined
// 4E0881: variable 'v5' is possibly undefined
// 4E0894: variable 'v7' is possibly undefined
// 4E08C2: variable 'v8' is possibly undefined
// 4E08D1: variable 'v9' is possibly undefined
// 4E08D6: variable 'v10' is possibly undefined
// 4E08F2: variable 'v11' is possibly undefined
// 4E08F9: variable 'v12' is possibly undefined
// 4E0931: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E0960) --------------------------------------------------------
signed int  Parser_ParseInstanceQueryActionExpression(int top, int readSource, int insQuerySetVars)
{
  int oldBindList; // edi
  int v6; // ecx
  signed int queryAction; // eax
  int v8; // ecx
  _DWORD *currentBind; // edx
  _DWORD *prevBind; // eax
  int setVar; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  _DWORD parseError[5]; // [esp+0h] [ebp-14h] BYREF

  parseError[0] = 0;
  oldBindList = Parser_GetLoopContextStack();
  Parser_SetLoopContextStack(0);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)(uintptr_t)g_ClipsParseContextSaveStack;
  queryAction = Parser_ParseArgument(readSource, parseError, v6);
  g_ParserBreakContextFlag = 0;
  if ( parseError[0] == 1 )
  {
    Parser_SetLoopContextStack(v8);
    AST_Free(top);
    return 0;
  }
  else if ( queryAction )
  {
    *(_DWORD *)(uintptr_t)(queryAction + 10) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(top + 6) + 10);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(top + 6) + 10) = queryAction;
    currentBind = (_DWORD *)(uintptr_t)Parser_GetLoopContextStack();
    prevBind = 0;
    if ( currentBind )
    {
      while ( 1 )
      {
        setVar = insQuerySetVars;
        if ( insQuerySetVars )
          break;
LABEL_7:
        prevBind = currentBind;
        currentBind = (_DWORD *)(uintptr_t)currentBind[2];
        if ( !currentBind )
          goto LABEL_8;
      }
      while ( *(_DWORD *)(uintptr_t)(setVar + 2) != *currentBind )
      {
        setVar = *(_DWORD *)(uintptr_t)(setVar + 10);
        if ( !setVar )
          goto LABEL_7;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(oldBindList);
      Rules_PrintErrorID((int)(intptr_t)aInsqypsr, v13, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotRebindIn, v14);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v15 + 2) + 16), v15);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction_3, v16);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(top + 2) + 16), v17);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__27, v18);
      AST_Free(top);
      return 0;
    }
    else
    {
LABEL_8:
      if ( prevBind )
        prevBind[2] = oldBindList;
      else
        Parser_SetLoopContextStack(oldBindList);
      return 1;
    }
  }
  else
  {
    Parser_SetLoopContextStack(v8);
    Parser_ReportSyntaxError();
    AST_Free(top);
    return 0;
  }
}
// 4E099A: variable 'v6' is possibly undefined
// 4E0A10: variable 'v8' is possibly undefined
// 4E0A54: variable 'v13' is possibly undefined
// 4E0A63: variable 'v14' is possibly undefined
// 4E0A68: variable 'v15' is possibly undefined
// 4E0A82: variable 'v16' is possibly undefined
// 4E0A94: variable 'v17' is possibly undefined
// 4E0AA3: variable 'v18' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004E0AD0) --------------------------------------------------------
char * Parser_ReplaceInstanceQuerySlotReferences(char *varList, int bodyExp, signed int ndepth, int sdirect)
{
  char *result; // eax
  int v8; // ecx
  int v9; // edx
  int i; // ecx
  int *depthValue; // eax
  signed int depthExpr; // ebx
  signed int v13; // ecx
  int *posnValue; // eax
  signed int childDepth; // ecx
  int childSdirect; // ebx
  signed int nestedDepth; // [esp+0h] [ebp-1Ch]
  int **Symbol; // [esp+4h] [ebp-18h]
  int querySlotSymbol; // [esp+8h] [ebp-14h]

  Symbol = Rules_MakeSymbol(aQueryInstanc_0);
  result = (char *)Rules_MakeSymbol(aQueryInstanc_1);
  querySlotSymbol = (int)(intptr_t)result;
  if ( v9 )
  {
    result = (char *)(uintptr_t)(v8 + 1);
    nestedDepth = v8 + 1;
    do
    {
      if ( *(_WORD *)(uintptr_t)bodyExp == 15 )
      {
        result = varList;
        for ( i = 0; result; ++i )
        {
          if ( *(_DWORD *)(result + 2) == *(_DWORD *)(uintptr_t)(bodyExp + 2) )
            break;
          result = *(char **)(result + 10);
        }
        if ( result )
        {
          *(_DWORD *)(uintptr_t)(bodyExp + 2) = Symbol;
          *(_WORD *)(uintptr_t)bodyExp = 10;
          depthValue = Rules_AddIntegerValue(ndepth);
          depthExpr = AST_NewNode(1, (int)(intptr_t)depthValue);
          posnValue = Rules_AddIntegerValue(v13);
          result = (char *)(uintptr_t)AST_NewNode(1, (int)(intptr_t)posnValue);
          *(_DWORD *)(uintptr_t)(depthExpr + 10) = result;
          *(_DWORD *)(uintptr_t)(bodyExp + 6) = depthExpr;
        }
        else if ( sdirect == 1 )
        {
          result = (char *)Parser_ResolveInstanceQuerySlotReference((int)(intptr_t)varList, bodyExp, ndepth, querySlotSymbol);
        }
      }
      if ( *(_DWORD *)(uintptr_t)(bodyExp + 6) )
      {
        if ( Rules_IsInstanceSetQueryFunctionCall(bodyExp) )
        {
          childDepth = nestedDepth;
          childSdirect = sdirect;
        }
        else
        {
          childSdirect = sdirect;
          childDepth = ndepth;
        }
        result = (char *)Parser_ReplaceInstanceQuerySlotReferences((int)(intptr_t)varList, *(_DWORD *)(uintptr_t)(bodyExp + 6), childDepth, childSdirect);
      }
      bodyExp = *(_DWORD *)(uintptr_t)(bodyExp + 10);
    }
    while ( bodyExp );
  }
  return result;
}
// 4E0AFE: variable 'v9' is possibly undefined
// 4E0B04: variable 'v8' is possibly undefined
// 4E0B58: variable 'v13' is possibly undefined

//----- (004E0BD0) --------------------------------------------------------
const char * Parser_ResolveInstanceQuerySlotReference(int varList, int theExp, signed int ndepth, int querySlotSymbol)
{
  const char *varName; // ebp
  const char *result; // eax
  unsigned int nameLen; // kr04_4
  int colonIndex; // esi
  int varNode; // ecx
  signed int j; // edi
  int v10; // edx
  int v11; // ecx
  int *depthValue; // eax
  int *posnValue; // eax
  __int16 tokenType; // [esp+0h] [ebp-2Ch]
  int tokenValue; // [esp+4h] [ebp-28h]
  const char *i; // [esp+1Ch] [ebp-10h]

  varName = *(const char **)(*(_DWORD *)(theExp + 2) + 16);
  result = 0;
  nameLen = strlen(varName) + 1;
  if ( (int)(nameLen - 1) >= 3 )
  {
    colonIndex = nameLen - 3;
    if ( (int)(nameLen - 3) >= 1 )
    {
      for ( i = &varName[colonIndex]; ; --i )
      {
        result = i;
        if ( *i == 58 )
        {
          result = (const char *)(colonIndex >= 1);
          if ( colonIndex >= 1 )
          {
            varNode = varList;
            for ( j = 0; varNode; ++j )
            {
              result = (const char *)(strncmp_(varNode, varName) != 0);
              if ( !result )
                break;
              varNode = *(_DWORD *)(varNode + 10);
            }
            if ( varNode )
              break;
          }
        }
        if ( --colonIndex < 1 )
          return result;
      }
      IO_OpenStringSource((int)aQueryVar, &varName[colonIndex + 1], 0);
      Rules_GetPPBufferStatus();
      Rules_SetPPBufferStatus(0);
      Parser_NextToken((int)aQueryVar, v10);
      Rules_SetPPBufferStatus(v11);
      IO_CloseStringRouter((int)aQueryVar);
      *(_WORD *)theExp = 10;
      *(_DWORD *)(theExp + 2) = querySlotSymbol;
      depthValue = Rules_AddIntegerValue(ndepth);
      *(_DWORD *)(theExp + 6) = AST_NewNode(1, (int)depthValue);
      posnValue = Rules_AddIntegerValue(j);
      *(_DWORD *)(*(_DWORD *)(theExp + 6) + 10) = AST_NewNode(1, (int)posnValue);
      result = (const char *)AST_NewNode(tokenType, tokenValue);
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theExp + 6) + 10) + 10) = result;
    }
  }
  return result;
}
// 4E0C4B: variable 'v8' is possibly undefined
// 4E0C92: variable 'v10' is possibly undefined
// 4E0C99: variable 'v11' is possibly undefined
// 4E0CFC: variable 'v14' is possibly undefined
// 4E0CFC: variable 'v15' is possibly undefined
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004E0D20) --------------------------------------------------------
BOOL  Rules_IsInstanceSetQueryFunctionCall(int theExp)
{
  int *( *theFunction)(int, double); // eax
  BOOL result; // eax

  result = 0;
  if ( *(_WORD *)(uintptr_t)theExp == 10 )
  {
    theFunction = *(int *( **)(int, double))(uintptr_t)(*(_DWORD *)(uintptr_t)(theExp + 2) + 9);
    if ( theFunction == InstanceQuery_AnyInstancep
      || (char *)theFunction == (char *)InstanceQuery_FindInstance
      || (char *)theFunction == (char *)InstanceQuery_FindAllInstances
      || (char *)theFunction == (char *)InstanceQuery_DoForInstance
      || (char *)theFunction == (char *)InstanceQuery_DoForAllInstances
      || (char *)theFunction == (char *)InstanceQuery_DelayedDoForAllInstances )
    {
      return 1;
    }
  }
  return result;
}

//----- (004E0D60) --------------------------------------------------------
int Compiler_RegisterObjectPatternNetworkCodeGenerator(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aObjectPatterns, 0, (int)(intptr_t)Compiler_WriteObjectPatternNetworkSetupCode, (int)(intptr_t)Compiler_AssignObjectPatternAndRuleCodeIndices, (int)(intptr_t)Compiler_WriteObjectPatternsAndRulesToCode, 2);
  g_ObjectPatternNetworkCodeGenItem = result;
  return result;
}
// 4E0DF0: using guessed type int sub_4E0DF0();
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0D90) --------------------------------------------------------
int  Compiler_WriteObjectPatternSecondaryIndexRef(int theNode, int theFile, int imageID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theNode )
    return Output_WriteFormatted(
             imageID,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             theFile,
             (int)(intptr_t)aSD_DD_11,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(imageID, theFile, theFile, (int)(intptr_t)aNull_33, v4);
}
// 4E0DA0: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0DF0) --------------------------------------------------------
int Compiler_AssignObjectPatternAndRuleCodeIndices(void)
{
  _DWORD *patternNode; // eax
  int i; // ecx
  int v2; // ecx
  int result; // eax
  int j; // edx

  patternNode = (_DWORD *)(uintptr_t)Rules_GetObjectPatternNetworkRoot();
  for ( i = 0; patternNode; i = v2 + 1 )
  {
    patternNode[9] = i;
    patternNode = Rules_GetNextObjectPatternNode(patternNode);
  }
  result = Rules_GetReactiveRuleList();
  for ( j = 0; result; ++j )
  {
    *(_DWORD *)(uintptr_t)(result + 40) = j;
    result = *(_DWORD *)(uintptr_t)(result + 36);
  }
  return result;
}
// 4E0E05: variable 'v2' is possibly undefined
// 4E0DF0: using guessed type int sub_4E0DF0();

//----- (004E0E40) --------------------------------------------------------
_DWORD * Rules_GetNextObjectPatternNode(_DWORD *result)
{
  if ( result[4] )
    return (_DWORD *)(uintptr_t)result[4];
  while ( !result[7] )
  {
    result = (_DWORD *)(uintptr_t)result[5];
    if ( !result )
      return result;
  }
  return (_DWORD *)(uintptr_t)result[7];
}

//----- (004E0E70) --------------------------------------------------------
int  Compiler_WriteObjectPatternNetworkSetupCode(int theFile, int maxIndices)
{
  int v3; // edx
  int v4; // ecx
  int alphaListHead; // eax
  int v6; // ecx
  int v8; // edx
  int v9; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  if ( Rules_GetObjectPatternNetworkRoot() )
  {
    Rules_GetObjectPatternNetworkRoot();
    alphaListHead = Rules_GetReactiveRuleList();
    Output_WriteFormatted(*(_DWORD *)(uintptr_t)(alphaListHead + 40), *(_DWORD *)(uintptr_t)(alphaListHead + 40), theFile, (int)(intptr_t)aSetobjectnetwo, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20));
    return Output_WriteFormatted(
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
             v6 % maxIndices,
             theFile,
             (int)(intptr_t)aSetobjectnet_0,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
  }
  else
  {
    Output_WriteFormatted(v4, v3, theFile, (int)(intptr_t)aSetobjectnet_1, v10);
    return Output_WriteFormatted(v9, v8, theFile, (int)(intptr_t)aSetobjectnet_2, v11);
  }
}
// 4E0ED3: variable 'v6' is possibly undefined
// 4E0EFD: variable 'v4' is possibly undefined
// 4E0EFD: variable 'v3' is possibly undefined
// 4E0EFD: variable 'v10' is possibly undefined
// 4E0F0B: variable 'v9' is possibly undefined
// 4E0F0B: variable 'v8' is possibly undefined
// 4E0F0B: variable 'v11' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0F20) --------------------------------------------------------
int  Compiler_WriteObjectPatternsAndRulesToCode(const char *fileName, int a2, DWORD fileID, int headerFile, int maxIndices)
{
  int result; // eax

  result = Compiler_WriteObjectPatternNodesToCode(fileName, a2, fileID, headerFile, maxIndices, 1);
  if ( result )
  {
    result = Compiler_WriteReactiveRulesToCode(fileName, a2, fileID, headerFile, maxIndices, result);
    if ( result )
      return 1;
  }
  return result;
}

//----- (004E0F80) --------------------------------------------------------
int  Compiler_WriteObjectPatternValueIndexRef(int patternNode, int outFile, int maxIndices)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( patternNode )
    return Output_WriteFormatted(maxIndices, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20), outFile, (int)(intptr_t)aSD_DD_11, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(maxIndices, outFile, outFile, (int)(intptr_t)aNull_33, v4);
}
// 4E0F90: variable 'v4' is possibly undefined
// 54E91C: using guessed type int dword_54E91C;

//----- (004E0FD0) --------------------------------------------------------
int  Compiler_WriteObjectPatternNodesToCode(const char *fileName, char a2, DWORD fileID, int headerFile, int maxIndices, int version)
{
  int v7; // edx
  int v8; // ecx
  int result; // eax
  int v10; // edx
  int patternFile; // esi
  int rootNode; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD *patternNode; // edi
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // edx
  int v27; // ecx
  _DWORD *nextNode; // eax
  int nextIndexInFile; // edx
  int v30; // ecx
  int nextVersion; // eax
  int v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  char v37; // [esp+0h] [ebp-24h]
  char v38; // [esp+0h] [ebp-24h]
  char v39; // [esp+0h] [ebp-24h]
  int newHeader; // [esp+Ch] [ebp-18h]
  int indexInFile; // [esp+10h] [ebp-14h]
  int arrayVersion; // [esp+14h] [ebp-10h]

  if ( !Rules_GetObjectPatternNetworkRoot() )
    return 1;
  Output_WriteFormatted(v8, v7, headerFile, (int)(intptr_t)aIncludeObjrt_0, a2);
  result = Rules_OpenConstructCodeFile(fileName, v10, version, fileID);
  patternFile = result;
  if ( result )
  {
    rootNode = Rules_GetObjectPatternNetworkRoot();
    v14 = 1;
    patternNode = (_DWORD *)(uintptr_t)rootNode;
    newHeader = 1;
    arrayVersion = 1;
    indexInFile = 1;
    if ( rootNode )
    {
      do
      {
        if ( newHeader )
        {
          Output_WriteFormatted(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20), arrayVersion, patternFile, (int)(intptr_t)aObject_pattern, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20));
          Output_WriteFormatted(headerFile, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20), headerFile, (int)(intptr_t)aExternObject_p, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20));
          newHeader = 0;
        }
        Output_WriteFormatted(v14, v13, patternFile, (int)(intptr_t)a0UUUU0lU, (*patternNode & 2) != 0);
        Rules_WriteExpressionRefToCode(patternFile, (__int16 *)(uintptr_t)patternNode[3], maxIndices, fileID);
        Output_WriteFormatted(v16, patternFile, patternFile, (int)(intptr_t)asc_50E654, v33);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[4], v17, maxIndices);
        Output_WriteFormatted(v18, patternFile, patternFile, (int)(intptr_t)asc_50E654, v34);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[5], v19, maxIndices);
        Output_WriteFormatted(v20, patternFile, patternFile, (int)(intptr_t)asc_50E654, v35);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[6], v21, maxIndices);
        Output_WriteFormatted(v22, patternFile, patternFile, (int)(intptr_t)asc_50E654, v36);
        Compiler_WriteObjectPatternValueIndexRef(patternNode[7], v23, maxIndices);
        Output_WriteFormatted(v24, patternFile, patternFile, (int)(intptr_t)asc_50E654, v37);
        Compiler_WriteObjectPatternSecondaryIndexRef(patternNode[8], v25, maxIndices);
        Output_WriteFormatted(v27, v26, patternFile, (int)(intptr_t)a0l_0, v38);
        nextNode = Rules_GetNextObjectPatternNode(patternNode);
        nextIndexInFile = indexInFile + 1;
        patternNode = nextNode;
        indexInFile = nextIndexInFile;
        if ( nextIndexInFile <= maxIndices && nextNode )
        {
          Output_WriteFormatted(maxIndices, nextIndexInFile, patternFile, (int)(intptr_t)asc_50E664, v39);
        }
        else
        {
          Output_WriteFormatted(maxIndices, nextIndexInFile, patternFile, (int)(intptr_t)asc_50E660, v39);
          fclose_(v30);
          indexInFile = 1;
          nextVersion = version + 1;
          v13 = arrayVersion + 1;
          ++version;
          ++arrayVersion;
          if ( patternNode )
          {
            result = Rules_OpenConstructCodeFile(fileName, v33, nextVersion, fileID);
            patternFile = result;
            if ( !result )
              return result;
            newHeader = 1;
          }
        }
      }
      while ( patternNode );
    }
    return version;
  }
  return result;
}
// 4E11FD: conditional instruction was optimized away because eax.4!=0
// 4E1000: variable 'v8' is possibly undefined
// 4E1000: variable 'v7' is possibly undefined
// 4E1012: variable 'v10' is possibly undefined
// 4E10B8: variable 'v14' is possibly undefined
// 4E10B8: variable 'v13' is possibly undefined
// 4E10D8: variable 'v16' is possibly undefined
// 4E10D8: variable 'v33' is possibly undefined
// 4E10E7: variable 'v17' is possibly undefined
// 4E10F6: variable 'v18' is possibly undefined
// 4E10F6: variable 'v34' is possibly undefined
// 4E1105: variable 'v19' is possibly undefined
// 4E1114: variable 'v20' is possibly undefined
// 4E1114: variable 'v35' is possibly undefined
// 4E1123: variable 'v21' is possibly undefined
// 4E1132: variable 'v22' is possibly undefined
// 4E1132: variable 'v36' is possibly undefined
// 4E1141: variable 'v23' is possibly undefined
// 4E1150: variable 'v24' is possibly undefined
// 4E1150: variable 'v37' is possibly undefined
// 4E115F: variable 'v25' is possibly undefined
// 4E116A: variable 'v27' is possibly undefined
// 4E116A: variable 'v26' is possibly undefined
// 4E116A: variable 'v38' is possibly undefined
// 4E1192: variable 'v39' is possibly undefined
// 4E11A1: variable 'v30' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E91C: using guessed type int dword_54E91C;

//----- (004E1210) --------------------------------------------------------
int  Compiler_WriteReactiveRulesToCode(const char *fileName, int constructFileID, DWORD fileID, int headerFile, int maxIndices, int version)
{
  int v7; // edx
  int result; // eax
  int alphaFile; // esi
  int v10; // ecx
  int *alphaNode; // edi
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // edx
  int v26; // ecx
  int v27; // ecx
  int nextVersion; // ebx
  int savedHeaderFile; // [esp+0h] [ebp-24h]
  char v30; // [esp+0h] [ebp-24h]
  char v31; // [esp+0h] [ebp-24h]
  char v32; // [esp+0h] [ebp-24h]
  char v33; // [esp+0h] [ebp-24h]
  char v34; // [esp+0h] [ebp-24h]
  char v35; // [esp+0h] [ebp-24h]
  char v36; // [esp+0h] [ebp-24h]
  int newHeader; // [esp+Ch] [ebp-18h]
  int arrayVersion; // [esp+10h] [ebp-14h]
  int indexInFile; // [esp+14h] [ebp-10h]

  savedHeaderFile = headerFile;
  if ( !Rules_GetReactiveRuleList() )
    return version;
  result = Rules_OpenConstructCodeFile(fileName, v7, version, fileID);
  alphaFile = result;
  if ( result )
  {
    alphaNode = (int *)(uintptr_t)Rules_GetReactiveRuleList();
    newHeader = 1;
    arrayVersion = 1;
    indexInFile = 1;
    if ( !alphaNode )
      return version;
    do
    {
      if ( newHeader )
      {
        Output_WriteFormatted(
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          arrayVersion,
          alphaFile,
          (int)(intptr_t)aObject_alpha_n,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        Output_WriteFormatted(
          savedHeaderFile,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4),
          savedHeaderFile,
          (int)(intptr_t)aExternObject_a,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ObjectPatternNetworkCodeGenItem + 20) + 4));
        newHeader = 0;
      }
      Output_WriteFormatted(v10, (int)(intptr_t)alphaNode, alphaFile, (int)(intptr_t)asc_50E6B4, savedHeaderFile);
      Rules_PrintPatternNetworkNodeTrace(alphaFile, v12, maxIndices);
      Output_WriteFormatted(v14, v13, alphaFile, (int)(intptr_t)a0l_1, v30);
      Compiler_WriteBitMapReference(alphaFile, alphaNode[5], v15);
      Output_WriteFormatted(v17, v16, alphaFile, (int)(intptr_t)asc_50E654, v31);
      Compiler_WriteBitMapReference(alphaFile, alphaNode[6], v18);
      Output_WriteFormatted(v19, alphaFile, alphaFile, (int)(intptr_t)asc_50E654, v32);
      Compiler_WriteObjectPatternValueIndexRef(alphaNode[7], v20, maxIndices);
      Output_WriteFormatted(v21, alphaFile, alphaFile, (int)(intptr_t)asc_50E654, v33);
      Compiler_WriteObjectPatternSecondaryIndexRef(alphaNode[8], v22, maxIndices);
      Output_WriteFormatted(v23, alphaFile, alphaFile, (int)(intptr_t)asc_50E654, v34);
      Compiler_WriteObjectPatternSecondaryIndexRef(alphaNode[9], v24, maxIndices);
      Output_WriteFormatted(v26, v25, alphaFile, (int)(intptr_t)a0l_0, v35);
      alphaNode = (int *)(uintptr_t)alphaNode[9];
      if ( ++indexInFile <= maxIndices && alphaNode )
      {
        Output_WriteFormatted(v27, maxIndices, alphaFile, (int)(intptr_t)asc_50E664, v36);
      }
      else
      {
        Output_WriteFormatted(v27, maxIndices, alphaFile, (int)(intptr_t)asc_50E660, v36);
        fclose_(1);
        indexInFile = v10;
        nextVersion = v10 + version;
        version += v10;
        arrayVersion += v10;
        if ( alphaNode )
        {
          result = Rules_OpenConstructCodeFile(fileName, constructFileID, nextVersion, fileID);
          alphaFile = result;
          if ( !result )
            return result;
          newHeader = 1;
        }
      }
    }
    while ( alphaNode );
    return version;
  }
  return result;
}
// 4E13F0: conditional instruction was optimized away because edi.4!=0
// 4E1243: variable 'v7' is possibly undefined
// 4E12AB: variable 'v29' is possibly undefined
// 4E12C1: variable 'v10' is possibly undefined
// 4E12CF: variable 'v12' is possibly undefined
// 4E12DA: variable 'v14' is possibly undefined
// 4E12DA: variable 'v13' is possibly undefined
// 4E12DA: variable 'v30' is possibly undefined
// 4E12E7: variable 'v15' is possibly undefined
// 4E12F2: variable 'v17' is possibly undefined
// 4E12F2: variable 'v16' is possibly undefined
// 4E12F2: variable 'v31' is possibly undefined
// 4E12FF: variable 'v18' is possibly undefined
// 4E130E: variable 'v19' is possibly undefined
// 4E130E: variable 'v32' is possibly undefined
// 4E131D: variable 'v20' is possibly undefined
// 4E132C: variable 'v21' is possibly undefined
// 4E132C: variable 'v33' is possibly undefined
// 4E133B: variable 'v22' is possibly undefined
// 4E134A: variable 'v23' is possibly undefined
// 4E134A: variable 'v34' is possibly undefined
// 4E1359: variable 'v24' is possibly undefined
// 4E1364: variable 'v26' is possibly undefined
// 4E1364: variable 'v25' is possibly undefined
// 4E1364: variable 'v35' is possibly undefined
// 4E1386: variable 'v27' is possibly undefined
// 4E1386: variable 'v36' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E91C: using guessed type int dword_54E91C;

//----- (004E1410) --------------------------------------------------------
int __fastcall Rules_BuildSlotBoundTestNode(int a1 CLASH95_UNUSED, int theNode)
{
  return Rules_BuildSlotConstraintBitmapTestNode(1, theNode);
}

//----- (004E1430) --------------------------------------------------------
int  Rules_BuildSlotBoundTestExpression(int theNode)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(1, theNode);
  return v2;
}
// 4E144C: variable 'v2' is possibly undefined

//----- (004E1460) --------------------------------------------------------
signed int  Rules_BuildSlotRangeTestNode(int selfNode, int referringNode)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(1, selfNode, referringNode);
}

//----- (004E1480) --------------------------------------------------------
signed int Rules_BuildMultifieldIndexTestNode(void)
{
  int slotNode; // ecx
  int bitmapFlags; // esi
  int bitmapValue; // eax
  signed int lengthTestNode; // edi
  _DWORD *v4; // ecx
  int eqBitmapValue; // eax
  signed int eqTestNode; // edi
  int *v8; // ecx
  int savedNodeType; // ebp
  _DWORD *v10; // ecx
  int nodeValue; // edx
  unsigned int fieldCountBits; // eax
  _DWORD bitmapBuffer[7]; // [esp+0h] [ebp-1Ch] BYREF

  Mem_AllocArray(bitmapBuffer, 4);
  if ( (*(_BYTE *)(uintptr_t)(slotNode + 8) & 1) != 0 )
    BYTE1(bitmapBuffer[0]) |= 1u;
  else
    LOBYTE(bitmapBuffer[0]) |= 0x80u;
  if ( (*(_BYTE *)(uintptr_t)(slotNode + 9) & 0x40) != 0 && (*(_WORD *)(uintptr_t)(slotNode + 10) & 0x1FC0) != 0 && (*(_DWORD *)(uintptr_t)(slotNode + 8) & 0x3F8000) != 0
    || *(_DWORD *)(uintptr_t)(slotNode + 40) < 2u )
  {
    BYTE1(bitmapBuffer[0]) |= 2u;
    eqBitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    eqTestNode = AST_NewNode(50, eqBitmapValue);
    *(_DWORD *)(uintptr_t)(eqTestNode + 6) = AST_NewNode(0, 0);
    savedNodeType = *v8;
    *v8 = 15;
    Rules_BuildSlotConstraintBitmapTestNode(0, (int)(intptr_t)v8);
    nodeValue = v10[1];
    *v10 = savedNodeType;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(eqTestNode + 6) + 10) = AST_NewNode(savedNodeType, nodeValue);
    return eqTestNode;
  }
  else
  {
    bitmapFlags = bitmapBuffer[0] | 0x400;
    if ( (*(_BYTE *)(uintptr_t)(slotNode + 9) & 0x40) != 0 )
    {
      if ( (*(_DWORD *)(uintptr_t)(slotNode + 8) & 0x3F8000) != 0 )
      {
        fieldCountBits = *(_DWORD *)(uintptr_t)(slotNode + 12) << 18;
        LOBYTE(bitmapBuffer[0]) &= 0x80u;
        bitmapBuffer[0] |= fieldCountBits >> 25;
      }
      else
      {
        bitmapBuffer[0] |= 0x400u;
        LOWORD(bitmapFlags) = bitmapFlags & 0xFF80;
        bitmapBuffer[0] = *(_DWORD *)(uintptr_t)(slotNode + 12) & 0x7F | bitmapFlags;
      }
    }
    else
    {
      bitmapBuffer[0] |= 0x400u;
    }
    bitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    lengthTestNode = AST_NewNode(50, bitmapValue);
    *(_DWORD *)(uintptr_t)(lengthTestNode + 6) = AST_NewNode(*v4, v4[1]);
    return lengthTestNode;
  }
}
// 4E14AC: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4E1497: variable 'v0' is possibly undefined
// 4E14E8: variable 'v4' is possibly undefined
// 4E154B: variable 'v8' is possibly undefined
// 4E155F: variable 'v10' is possibly undefined

//----- (004E15D0) --------------------------------------------------------
int __fastcall mblen_(int theNode, int a2)
{
  (void)a2;
  return Rules_BuildSlotConstraintBitmapTestNode(0, theNode);
}

//----- (004E15E0) --------------------------------------------------------
int  Rules_BuildSlotUnboundTestExpression(int theNode)
{
  int v2; // ecx

  AST_NewNode(0, 0);
  Rules_BuildSlotConstraintBitmapTestNode(0, theNode);
  return v2;
}
// 4E15F9: variable 'v2' is possibly undefined

//----- (004E1600) --------------------------------------------------------
int __fastcall mblen__0(int selfNode, int referringNode)
{
  return Rules_BuildDualSlotConstraintBitmapTestNode(0, selfNode, referringNode);
}

//----- (004E1610) --------------------------------------------------------
_DWORD * Rules_AppendFieldCardinalityBitmapTest(_DWORD *result)
{
  int slotNode; // ecx
  int fieldCount; // eax
  int bitmapValue; // eax
  _DWORD *testNode; // eax
  int v5; // ecx
  int v6; // ecx
  unsigned int multifieldCount; // eax
  _DWORD bitmapBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  if ( (result[3] & 0x3F80) != 0 || *result == 15 || *result == 17 )
  {
    Mem_AllocArray(bitmapBuffer, 4);
    if ( *(_DWORD *)(uintptr_t)slotNode == 16 || *(_DWORD *)(uintptr_t)slotNode == 18 || (*(_WORD *)(uintptr_t)(slotNode + 10) & 0x1FC0) != 0 )
      BYTE1(bitmapBuffer[0]) &= ~0x80u;
    else
      BYTE1(bitmapBuffer[0]) |= 0x80u;
    if ( *(_DWORD *)(uintptr_t)slotNode == 15 || *(_DWORD *)(uintptr_t)slotNode == 17 )
    {
      fieldCount = *(_DWORD *)(uintptr_t)(slotNode + 12) << 18 >> 25;
      LOWORD(bitmapBuffer[0]) &= 0x8000u;
      bitmapBuffer[0] |= ((_WORD)fieldCount + 1) & 0x7FFF;
    }
    else
    {
      multifieldCount = *(_DWORD *)(uintptr_t)(slotNode + 12) << 18;
      LOWORD(bitmapBuffer[0]) &= 0x8000u;
      bitmapBuffer[0] |= (multifieldCount >> 25) & 0x7FFF;
    }
    bitmapValue = Rules_AddBitmapValue(bitmapBuffer, 4);
    testNode = (_DWORD *)(uintptr_t)AST_NewNode(49, bitmapValue);
    result = AST_MergeFieldAccessNodes(testNode, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 52));
    *(_DWORD *)(uintptr_t)(v6 + 52) = result;
  }
  return result;
}
// 4E163F: variable 'v1' is possibly undefined
// 4E16A9: variable 'v5' is possibly undefined
// 4E16B1: variable 'v6' is possibly undefined

//----- (004E1700) --------------------------------------------------------
_DWORD *__fastcall Rules_AppendMultifieldWildcardBitmapTest(int a1, int a2 CLASH95_UNUSED)
{
  int bitmapValue; // eax
  _DWORD *lengthTestNode; // eax
  int v4; // ecx
  _DWORD *result; // eax
  int v6; // ecx
  _WORD matchLengthBitmap[4]; // [esp+0h] [ebp-Ch] BYREF
  int v8 CLASH95_UNUSED; // [esp+8h] [ebp-4h]

  v8 = a1;
  Mem_AllocArray(matchLengthBitmap, 4);
  HIBYTE(matchLengthBitmap[0]) |= 0x80u;
  matchLengthBitmap[0] &= 0x8000u;
  bitmapValue = Rules_AddBitmapValue(matchLengthBitmap, 4);
  lengthTestNode = (_DWORD *)(uintptr_t)AST_NewNode(49, bitmapValue);
  result = AST_MergeFieldAccessNodes(lengthTestNode, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 52));
  *(_DWORD *)(uintptr_t)(v6 + 52) = result;
  return result;
}
// 4E173C: variable 'v4' is possibly undefined
// 4E1744: variable 'v6' is possibly undefined

//----- (004E1750) --------------------------------------------------------
int  Rules_BuildSlotConstraintBitmapTestNode(int joinTest, int theNode)
{
  __int16 *v3; // ecx
  int v4; // eax
  __int16 var1NodeType; // ax
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  __int16 var2NodeType; // ax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  unsigned int matchVar1Bitmap; // [esp+0h] [ebp-20h] BYREF
  char matchVar1BitmapHi; // [esp+4h] [ebp-1Ch]
  int matchVar2Bitmap; // [esp+8h] [ebp-18h] BYREF
  int matchVar2BitmapHi; // [esp+Ch] [ebp-14h]

  Mem_AllocArray(&matchVar1Bitmap, 8);
  Mem_AllocArray(&matchVar2Bitmap, 8);
  if ( joinTest )
  {
    matchVar1Bitmap = ((unsigned __int8)*(_DWORD *)(uintptr_t)(theNode + 28) << 15) | matchVar1Bitmap & 0xFF807FFF;
    v8 = *(_DWORD *)(uintptr_t)(theNode + 28);
    LOBYTE(matchVar2BitmapHi) = 0;
    matchVar2BitmapHi |= (unsigned __int8)v8;
  }
  if ( *(int *)(uintptr_t)(theNode + 40) < 0 )
  {
    HIBYTE(matchVar1Bitmap) |= 0x80u;
    if ( !joinTest )
      goto LABEL_13;
    goto LABEL_10;
  }
  if ( (*(_BYTE *)(uintptr_t)(theNode + 12) & 0x7F) == 0
    && (*(_WORD *)(uintptr_t)(theNode + 12) & 0x3F80) == 0
    && (*(_DWORD *)(uintptr_t)(theNode + 8) & 0x3F8000) == 0
    && (*(_WORD *)(uintptr_t)(theNode + 10) & 0x1FC0) == 0
    && ((*(_BYTE *)(uintptr_t)(theNode + 9) & 0x40) == 0 || *(_DWORD *)(uintptr_t)theNode == 16 || *(_DWORD *)(uintptr_t)theNode == 18) )
  {
    matchVar1BitmapHi |= 1u;
    v4 = *(_DWORD *)(uintptr_t)(theNode + 40);
    LOWORD(matchVar1Bitmap) = matchVar1Bitmap & 0x8000;
    matchVar1Bitmap |= v4 & 0x7FFF;
    if ( !joinTest )
      goto LABEL_13;
LABEL_10:
    var1NodeType = 47;
LABEL_11:
    *v3 = var1NodeType;
    result = Rules_AddBitmapValue(&matchVar1Bitmap, 8);
    *(_DWORD *)(uintptr_t)(v7 + 2) = result;
    return result;
  }
  if ( (*(_DWORD *)(uintptr_t)theNode == 17 || *(_DWORD *)(uintptr_t)theNode == 15)
    && ((*(_DWORD *)(uintptr_t)(theNode + 8) & 0x3F8000) == 0 || (*(_WORD *)(uintptr_t)(theNode + 10) & 0x1FC0) == 0) )
  {
    v9 = *(_DWORD *)(uintptr_t)(theNode + 40);
    LOWORD(matchVar2Bitmap) = matchVar2Bitmap & 0x8000;
    matchVar2Bitmap |= v9 & 0x7FFF;
    if ( (*(_DWORD *)(uintptr_t)(theNode + 8) & 0x3F8000) != 0 )
    {
      BYTE2(matchVar2Bitmap) |= 0x80u;
      v17 = *(_DWORD *)(uintptr_t)(theNode + 12) << 18 >> 25;
      HIBYTE(matchVar2Bitmap) &= 0x80u;
      v11 = (v17 & 0x7F) << 24;
    }
    else
    {
      BYTE1(matchVar2Bitmap) |= 0x80u;
      v10 = *(_DWORD *)(uintptr_t)(theNode + 12);
      BYTE2(matchVar2Bitmap) &= 0x80u;
      v11 = (v10 & 0x7F) << 16;
    }
    matchVar2Bitmap |= v11;
    if ( joinTest )
      var2NodeType = 48;
    else
      var2NodeType = 46;
    goto LABEL_22;
  }
  if ( *(_DWORD *)(uintptr_t)theNode != 18 && *(_DWORD *)(uintptr_t)theNode != 16
    || (*(_DWORD *)(uintptr_t)(theNode + 8) & 0x3F8000) != 0
    || (*(_WORD *)(uintptr_t)(theNode + 10) & 0x1FC0) != 0 )
  {
    v18 = *(_DWORD *)(uintptr_t)(theNode + 40);
    LOWORD(matchVar1Bitmap) = matchVar1Bitmap & 0x8000;
    matchVar1Bitmap |= v18 & 0x7FFF;
    v19 = (unsigned __int8)*(_DWORD *)(uintptr_t)(theNode + 32);
    HIWORD(matchVar1Bitmap) &= 0x807Fu;
    matchVar1Bitmap |= v19 << 23;
    if ( joinTest )
      goto LABEL_10;
LABEL_13:
    var1NodeType = 45;
    goto LABEL_11;
  }
  v14 = *(_DWORD *)(uintptr_t)(theNode + 40);
  LOWORD(matchVar2Bitmap) = matchVar2Bitmap & 0x8000;
  matchVar2Bitmap |= v14 & 0x7FFF | 0x808000;
  v15 = *(_DWORD *)(uintptr_t)(theNode + 12) & 0x7F;
  BYTE2(matchVar2Bitmap) &= 0x80u;
  matchVar2Bitmap |= v15 << 16;
  v16 = *(_DWORD *)(uintptr_t)(theNode + 12) << 18 >> 25;
  HIBYTE(matchVar2Bitmap) &= 0x80u;
  matchVar2Bitmap |= (v16 & 0x7F) << 24;
  if ( joinTest )
    var2NodeType = 48;
  else
    var2NodeType = 46;
LABEL_22:
  *v3 = var2NodeType;
  result = Rules_AddBitmapValue(&matchVar2Bitmap, 8);
  *(_DWORD *)(uintptr_t)(v13 + 2) = result;
  return result;
}
// 4E17EA: variable 'v3' is possibly undefined
// 4E17F4: variable 'v7' is possibly undefined
// 4E18CE: variable 'v13' is possibly undefined

//----- (004E1A40) --------------------------------------------------------
BOOL  Rules_IsMultiplyConstrainedSlot(int theNode)
{
  return *(_DWORD *)(uintptr_t)theNode != 18
      && *(_DWORD *)(uintptr_t)theNode != 16
      && *(int *)(uintptr_t)(theNode + 40) >= 2
      && ((*(_BYTE *)(uintptr_t)(theNode + 9) & 0x40) == 0
       || (*(_BYTE *)(uintptr_t)(theNode + 8) & 4) == 0
       && ((*(_DWORD *)(uintptr_t)(theNode + 8) & 0x3F8000) == 0 || (*(_WORD *)(uintptr_t)(theNode + 10) & 0x1FC0) == 0));
}
// 4E1A53: simplified comparisons for 'ebx.4': <0 || ==0 became <1
// 4E1A53: simplified comparisons for 'ebx.4': <1 || ==1 became <2
