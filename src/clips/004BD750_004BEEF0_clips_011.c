/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004BD750) --------------------------------------------------------
signed int  Parser_ValidateFunctionCallArgs(int theExpression, int restrictions, int functionName)
{
  int argPosition; // ebp
  _BYTE *restrictionPtr; // edx
  int argCount; // ecx
  int minArgs; // ebx
  int restrictionIndex; // edi
  int maxArgs; // eax
  int argNode; // ebx
  _BYTE *v12; // esi
  char v13; // cl
  char *v14; // eax
  char v16; // [esp+8h] [ebp-1Ch]

  argPosition = 1;
  if ( !restrictions )
    return 0;
  argCount = AST_CountListNodes(*(_DWORD *)(theExpression + 6));
  if ( (IsTable[(unsigned __int8)(*restrictionPtr + 1)] & 0x20) != 0 )
  {
    minArgs = atoi_(argCount);
  }
  else
  {
    if ( *restrictionPtr != 42 )
      return 0;
    minArgs = -1;
  }
  v16 = restrictionPtr[1];
  restrictionIndex = 2;
  if ( (IsTable[(unsigned __int8)(v16 + 1)] & 0x20) == 0 )
  {
    if ( v16 == 42 )
    {
      maxArgs = 10000;
      goto LABEL_9;
    }
    return 0;
  }
  maxArgs = atoi_(argCount);
LABEL_9:
  if ( minArgs == maxArgs )
  {
    if ( argCount == maxArgs )
      goto LABEL_11;
LABEL_22:
    Rules_ExpectedCountError(functionName, minArgs);
    return 1;
  }
  if ( argCount < minArgs )
    goto LABEL_22;
  if ( argCount > maxArgs )
  {
    Rules_ExpectedCountError(functionName, maxArgs);
    return 1;
  }
LABEL_11:
  if ( restrictionPtr[2] )
    restrictionIndex = 3;
  argNode = *(_DWORD *)(theExpression + 6);
  if ( !argNode )
    return 0;
  v12 = &restrictionPtr[restrictionIndex];
  while ( 1 )
  {
    if ( *v12 )
    {
      ++v12;
      ++restrictionIndex;
    }
    if ( Rules_ExpressionConstraintsCompatible((__int16 *)argNode) )
      break;
    argNode = *(_DWORD *)(argNode + 10);
    ++argPosition;
    if ( !argNode )
      return 0;
  }
  v14 = Rules_GetArgTypeName(v13);
  Parser_ReportError(argPosition, (int)v14);
  return 1;
}
// 4BD789: variable 'v6' is possibly undefined
// 4BD7ED: variable 'v7' is possibly undefined
// 4BD8ED: variable 'v13' is possibly undefined
// 48523F: using guessed type int __thiscall unknown_libname_2(_DWORD);

//----- (004BD910) --------------------------------------------------------
int  Parser_CollectFunctionArguments(int exprNode, int readSource, int context)
{
  int v5; // edx
  int v6; // ecx
  signed int argNode; // eax
  int lastArg; // ecx
  _DWORD errorFlag[5]; // [esp+0h] [ebp-14h] BYREF

  errorFlag[3] = context;
  while ( 1 )
  {
    IO_OutWriteToken(asc_50A444);
    errorFlag[0] = v5;
    argNode = Parser_ParseArgument(readSource, errorFlag, v6);
    if ( errorFlag[0] == 1 )
    {
      AST_Free(exprNode);
      return 0;
    }
    if ( !argNode )
      break;
    if ( lastArg )
      *(_DWORD *)(lastArg + 10) = argNode;
    else
      *(_DWORD *)(exprNode + 6) = argNode;
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50A448);
  return exprNode;
}
// 4BD929: variable 'v5' is possibly undefined
// 4BD930: variable 'v6' is possibly undefined
// 4BD945: variable 'v8' is possibly undefined

//----- (004BD980) --------------------------------------------------------
signed int  Parser_ParseArgument(int readSource, _DWORD *errorFlag, int context)
{
  int v4; // ecx
  signed int result; // eax
  int v6; // ecx
  _DWORD token[5]; // [esp+0h] [ebp-14h] BYREF

  token[4] = context;
  Parser_NextToken(readSource, (int)token);
  if ( token[0] == 101 )
    return 0;
  if ( token[0] == 15 || token[0] == 16 || token[0] == 2 || token[0] == 3 || token[0] == 13 || token[0] == 14 || token[0] == 8 || token[0] < 2u )
    return AST_NewNode(token[0], token[1]);
  if ( token[0] == 100 )
  {
    result = Parser_ParseExpression(v4, 100, v4);
    if ( !result )
      *errorFlag = 1;
  }
  else
  {
    Rules_PrintErrorID((int)aExprnpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAConst, v6);
    *errorFlag = 1;
    return 0;
  }
  return result;
}
// 4BD9BD: simplified comparisons for '%var_14.4': ==0 || ==1 became <2u
// 4BD9CB: variable 'v4' is possibly undefined
// 4BDA15: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDA30) --------------------------------------------------------
int  Parser_ParseSingleExpression(int readSource, __int16 *theToken, int context)
{
  int v3; // ecx
  __int16 *tokenPtr; // ebx
  unsigned int tokenType; // edx
  int v6; // edx
  int result; // eax
  int v8; // ecx
  _DWORD token[5]; // [esp-10h] [ebp-14h] BYREF

  token[3] = context;
  v3 = readSource;
  tokenPtr = theToken;
  if ( !theToken )
  {
    tokenPtr = (__int16 *)token;
    Parser_NextToken(readSource, (int)token);
  }
  tokenType = *(_DWORD *)tokenPtr;
  if ( *(_DWORD *)tokenPtr == 2 || tokenType == 3 || tokenType < 2 || tokenType == 8 || tokenType == 13 || tokenType == 14 || tokenType == 15 || tokenType == 16 )
    return AST_NewNode(*(_DWORD *)tokenPtr, *((_DWORD *)tokenPtr + 1));
  if ( tokenType != 100 )
  {
    Rules_PrintErrorID((int)aExprnpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAConst, v8);
    return 0;
  }
  result = Parser_ParseExpression(v3, v3);
  v6 = result;
  if ( result )
    return v6;
  return result;
}
// 4BDA6B: simplified comparisons for 'edx.4': ==1 || ==0 became <2u
// 4BDA91: variable 'v3' is possibly undefined
// 4BDAC0: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDAD0) --------------------------------------------------------
int  Parser_ParseProgram(int readSource, unsigned int *theToken, signed int readFirstToken)
{
  int **Symbol; // eax
  signed int lastNode; // ebx
  int v8; // ecx
  unsigned int tokenType; // eax
  signed int argNode; // eax
  int v11; // edx
  int v12; // ecx
  int **v14; // ebx
  int v15; // edx
  int v16; // ecx
  signed int topNode; // [esp+0h] [ebp-10h]

  Symbol = Rules_MakeSymbol(aProgn_2);
  lastNode = 0;
  topNode = AST_NewNode(10, (int)Symbol);
  while ( 1 )
  {
    if ( readFirstToken )
      Parser_NextToken(readSource, (int)theToken);
    else
      readFirstToken = 1;
    if ( *theToken == 2 && v8 && !strcmp_(v8, v8) )
      return topNode;
    tokenType = *theToken;
    if ( *theToken == 2 || tokenType == 3 || tokenType < 2 || tokenType == 13 || tokenType == 14 || tokenType == 8 || tokenType == 15 || tokenType == 16 )
    {
      argNode = AST_NewNode(*theToken, theToken[1]);
      goto LABEL_10;
    }
    if ( tokenType != 100 )
      break;
    argNode = Parser_ParseExpression(readSource, v8);
LABEL_10:
    if ( !argNode )
    {
      *theToken = 103;
      AST_Free(topNode);
      return 0;
    }
    if ( lastNode )
    {
      *(_DWORD *)(lastNode + 10) = argNode;
      lastNode = argNode;
      AST_Append(v12, v11);
    }
    else
    {
      *(_DWORD *)(topNode + 6) = argNode;
      lastNode = argNode;
      AST_Append(v12, topNode);
    }
  }
  Rules_MakeSymbol(aExpand_0);
  v14 = Rules_MakeSymbol(aExpansionCal_0);
  if ( !Parser_ParseExpansion(topNode, v15, v16, (int)v14) )
    return topNode;
  AST_Free(topNode);
  return 0;
}
// 4BDB67: simplified comparisons for 'eax.4': ==1 || ==0 became <2u
// 4BDB07: variable 'v8' is possibly undefined
// 4BDB48: variable 'v12' is possibly undefined
// 4BDBB1: variable 'v15' is possibly undefined
// 4BDBB1: variable 'v16' is possibly undefined
// 4BDBE7: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004BDC10) --------------------------------------------------------
int Parser_GetSequenceOperatorRecognition(void)
{
  return g_SequenceOperatorRecognition;
}
// 51B360: using guessed type int dword_51B360;

//----- (004BDC20) --------------------------------------------------------
const char * Parser_ParseCLIPSFunctionArgString(const char *result, _DWORD *errorFlag)
{
  signed int lastNode; // esi
  signed int argNode; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD token[8]; // [esp+0h] [ebp-20h] BYREF

  lastNode = 0;
  *errorFlag = 0;
  if ( result )
  {
    if ( IO_OpenStringSource((int)aClipsfnxargs, result, 0) )
    {
      Parser_NextToken((int)aClipsfnxargs, (int)token);
      if ( token[0] == 102 )
      {
LABEL_11:
        IO_CloseStringRouter((int)aClipsfnxargs);
        return (const char *)v6;
      }
      else
      {
        while ( token[0] == 2 || token[0] == 3 || token[0] < 2u || token[0] == 8 )
        {
          argNode = AST_NewNode(token[0], token[1]);
          if ( v5 )
            *(_DWORD *)(lastNode + 10) = argNode;
          lastNode = argNode;
          Parser_NextToken((int)aClipsfnxargs, (int)token);
          if ( token[0] == 102 )
            goto LABEL_11;
        }
        Rules_PrintErrorID((int)aExprnpsr, 7, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOnlyConstantAr, v8);
        AST_Free(v9);
        *errorFlag = 1;
        IO_CloseStringRouter((int)aClipsfnxargs);
        return 0;
      }
    }
    else
    {
      Rules_PrintErrorID((int)aExprnpsr, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotReadArgu, v7);
      *errorFlag = 1;
      return 0;
    }
  }
  return result;
}
// 4BDC73: simplified comparisons for '%var_20.4': ==0 || ==1 became <2u
// 4BDC8F: variable 'v5' is possibly undefined
// 4BDCB2: variable 'v6' is possibly undefined
// 4BDCD8: variable 'v7' is possibly undefined
// 4BDD09: variable 'v8' is possibly undefined
// 4BDD10: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDC00) --------------------------------------------------------
int Parser_SetSequenceOperatorRecognition(int value)
{
  int previous_value; // eax

  previous_value = g_SequenceOperatorRecognition;
  g_SequenceOperatorRecognition = value;
  return previous_value;
}
// 51B360: using guessed type int dword_51B360;

//----- (004BDD20) --------------------------------------------------------
signed int Parser_AddFunctionParser(_BYTE *function_name, int handler)
{
  int **symbol; // eax
  int v3; // ecx

  symbol = Rules_MakeSymbol(function_name);
  if ( symbol )
  {
    *(int **)((char *)symbol + 17) = 0;
    *(_WORD *)((char *)symbol + 21) = 0;
    *(int **)((char *)symbol + 13) = (int *)handler;
    return 1;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionParser, v3);
  return 0;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDD40) --------------------------------------------------------
int Parser_RegisterProceduralFunctionParsers()
{
  if ( !Parser_AddFunctionParser(aBind, (int)Parser_ParseBind) )
    return 0;
  if ( !Parser_AddFunctionParser(aProgn, (int)Parser_ParseProgn) )
    return 0;
  if ( !Parser_AddFunctionParser(aIf, (int)Parser_ParseIf) )
    return 0;
  if ( !Parser_AddFunctionParser(aWhile, (int)Parser_ParseWhile) )
    return 0;
  if ( !Parser_AddFunctionParser(aLoopForCount, (int)Parser_ParseLoopForCount) )
    return 0;
  if ( !Parser_AddFunctionParser(aReturn, (int)Parser_ParseReturn) )
    return 0;
  if ( !Parser_AddFunctionParser(aBreak, (int)Parser_ParseBreak) )
    return 0;
  return Parser_AddFunctionParser(aSwitch, (int)Parser_ParseSwitch);
}

//----- (004BDDC0) --------------------------------------------------------
int Parser_GetLoopContextStack(void)
{
  return g_ClipsLoopContextStackTop;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDDD0) --------------------------------------------------------
int  Parser_SetLoopContextStack(int result)
{
  g_ClipsLoopContextStackTop = result;
  return result;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDDE0) --------------------------------------------------------
int Parser_FreeLoopContextStack(void)
{
  int result; // eax
  int nextEntry; // edx

  if ( g_ClipsLoopContextStackTop )
  {
    do
    {
      AST_DecrementNodeRefCount(*(_DWORD **)(g_ClipsLoopContextStackTop + 4));
      g_ClipsMemFreeListTemp = g_ClipsLoopContextStackTop;
      *(_DWORD *)g_ClipsLoopContextStackTop = *(_DWORD *)(g_ClipsMemoryTable + 48);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      g_ClipsLoopContextStackTop = nextEntry;
    }
    while ( nextEntry );
  }
  return result;
}
// 4BDE23: variable 'v1' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BDE40) --------------------------------------------------------
BOOL Parser_LoopContextStackIsEmpty(void)
{
  return g_ClipsLoopContextStackTop == 0;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDE50) --------------------------------------------------------
int  Parser_ParseWhile(int topNode, int readSource)
{
  int v4; // ecx
  int testExpr; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  signed int readFirstToken; // ebx
  int v11; // edx
  int v12; // ecx
  unsigned int token; // [esp+0h] [ebp-20h] BYREF
  char *indentToken; // [esp+8h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  testExpr = Parser_ParseSingleExpression(readSource, 0, v4);
  *(_DWORD *)(topNode + 6) = testExpr;
  if ( !testExpr )
    goto LABEL_10;
  Parser_NextToken(readSource, (int)&token);
  if ( token == 2 && !strcmp_(v6, aDo) )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A54C);
    IO_OutWriteToken(indentToken);
    readFirstToken = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v12, v11);
  }
  else
  {
    if ( token != 100 )
    {
LABEL_9:
      Parser_ReportSyntaxError();
LABEL_10:
      AST_Free(topNode);
      return 0;
    }
    IO_OutNewline();
    Rules_IncrementIndentDepth(3);
    AST_Append(v8, v7);
    readFirstToken = 0;
    IO_OutWriteToken(indentToken);
  }
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  g_ParserBreakContextFlag = 1;
  *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = Parser_ParseProgram(readSource, &token, readFirstToken);
  if ( !*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) )
    goto LABEL_10;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(indentToken);
  if ( token != 101 )
    goto LABEL_9;
  Rules_DecrementIndentDepth(3);
  return topNode;
}
// 4BDE6A: variable 'v4' is possibly undefined
// 4BDEA2: variable 'v8' is possibly undefined
// 4BDEA2: variable 'v7' is possibly undefined
// 4BDF2A: variable 'v6' is possibly undefined
// 4BDF5E: variable 'v12' is possibly undefined
// 4BDF5E: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BDF80) --------------------------------------------------------
int  Parser_ParseLoopForCount(int topNode, int readSource)
{
  int v4; // edx
  int loopVar; // esi
  int *defaultLowerBound; // eax
  int v7; // ecx
  int v8; // ecx
  signed int readFirstToken; // ebx
  int v10; // edx
  int v11; // ecx
  int prevContext; // eax
  int scanContext; // ecx
  int *v14; // eax
  int v16; // ecx
  __int16 *rangeExpr; // eax
  int v18; // edx
  int v19; // ecx
  int *lowerBoundValue; // eax
  signed int lowerBoundNode; // eax
  int v22; // edx
  int v23; // ecx
  int v24; // ecx
  unsigned int token; // [esp+0h] [ebp-28h] BYREF
  int tokenValue; // [esp+4h] [ebp-24h]
  char *indentToken; // [esp+8h] [ebp-20h]
  int savedLoopStack; // [esp+Ch] [ebp-1Ch]
  int loopScope; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(readSource, v4);
  loopVar = 0;
  if ( token == 100 )
  {
    Parser_NextToken(readSource, (int)&token);
    if ( token == 15 )
    {
      loopVar = tokenValue;
      IO_OutWriteToken(asc_50A54C);
      rangeExpr = (__int16 *)Parser_ParseSingleExpression(readSource, 0, v16);
      *(_DWORD *)(topNode + 6) = rangeExpr;
      if ( !rangeExpr )
        goto LABEL_23;
      if ( Rules_ExpressionConstraintsCompatible(rangeExpr) )
        goto LABEL_18;
      IO_OutWriteToken(asc_50A54C);
      Parser_NextToken(readSource, v18);
      if ( token == 101 )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(indentToken);
        lowerBoundValue = Rules_AddIntegerValue(1);
        lowerBoundNode = AST_NewNode(1, (int)lowerBoundValue);
        *(_DWORD *)(lowerBoundNode + 10) = *(_DWORD *)(topNode + 6);
        *(_DWORD *)(topNode + 6) = lowerBoundNode;
      }
      else
      {
        *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = Parser_ParseSingleExpression(readSource, (__int16 *)&token, v19);
        if ( !*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) )
          goto LABEL_23;
        Parser_NextToken(readSource, (int)&token);
        if ( token != 101 )
          goto LABEL_18;
      }
      IO_OutWriteToken(asc_50A54C);
      goto LABEL_3;
    }
    if ( token != 2 )
      goto LABEL_18;
    v14 = Rules_AddIntegerValue(1);
    *(_DWORD *)(topNode + 6) = AST_NewNode(1, (int)v14);
    *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = Parser_ParseFunctionCallExpr(readSource, *(_BYTE **)(tokenValue + 16));
    if ( *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) )
      goto LABEL_3;
LABEL_23:
    AST_Free(topNode);
    return 0;
  }
  defaultLowerBound = Rules_AddIntegerValue(1);
  *(_DWORD *)(topNode + 6) = AST_NewNode(1, (int)defaultLowerBound);
  *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = Parser_ParseSingleExpression(readSource, (__int16 *)&token, v7);
  if ( !*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) )
    goto LABEL_23;
LABEL_3:
  if ( Rules_ExpressionConstraintsCompatible(*(__int16 **)(*(_DWORD *)(topNode + 6) + 10)) )
    goto LABEL_18;
  Parser_NextToken(readSource, (int)&token);
  if ( token == 2 && !strcmp_(v8, aDo) )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A54C);
    IO_OutWriteToken(indentToken);
    readFirstToken = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v11, v10);
    goto LABEL_7;
  }
  if ( token != 100 )
  {
LABEL_18:
    Parser_ReportSyntaxError();
    goto LABEL_23;
  }
  IO_OutNewline();
  Rules_IncrementIndentDepth(3);
  AST_Append(v23, v22);
  readFirstToken = 0;
  IO_OutWriteToken(indentToken);
LABEL_7:
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  g_ParserBreakContextFlag = 1;
  savedLoopStack = g_ClipsLoopContextStackTop;
  loopScope = g_ClipsLoopContextStackTop;
  g_ClipsLoopContextStackTop = 0;
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) + 10) = Parser_ParseProgram(readSource, &token, readFirstToken);
  if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) + 10) )
  {
    g_ClipsLoopContextStackTop = savedLoopStack;
    AST_Free(topNode);
    return 0;
  }
  prevContext = 0;
  scanContext = g_ClipsLoopContextStackTop;
  if ( !g_ClipsLoopContextStackTop )
  {
LABEL_13:
    if ( prevContext )
      *(_DWORD *)(prevContext + 8) = loopScope;
    else
      g_ClipsLoopContextStackTop = loopScope;
    if ( loopVar )
      Parser_ReplaceLoopCountVars(loopVar, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) + 10), 0);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(indentToken);
    if ( token == 101 )
    {
      Rules_DecrementIndentDepth(3);
      return topNode;
    }
    goto LABEL_18;
  }
  while ( !loopVar || strcmp_(scanContext, *(_DWORD *)(loopVar + 16)) )
  {
    prevContext = scanContext;
    scanContext = *(_DWORD *)(scanContext + 8);
    if ( !scanContext )
      goto LABEL_13;
  }
  Parser_FreeLoopContextStack();
  g_ClipsLoopContextStackTop = loopScope;
  Rules_PrintErrorID((int)aPrcdrpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindLo, v24);
  AST_Free(topNode);
  return 0;
}
// 4BDF9A: variable 'v4' is possibly undefined
// 4BDFCA: variable 'v7' is possibly undefined
// 4BE019: variable 'v8' is possibly undefined
// 4BE04D: variable 'v11' is possibly undefined
// 4BE04D: variable 'v10' is possibly undefined
// 4BE0BD: variable 'v13' is possibly undefined
// 4BE19A: variable 'v16' is possibly undefined
// 4BE1CA: variable 'v18' is possibly undefined
// 4BE21A: variable 'v19' is possibly undefined
// 4BE25F: variable 'v23' is possibly undefined
// 4BE25F: variable 'v22' is possibly undefined
// 4BE2D5: variable 'v24' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;
// 54E880: using guessed type int dword_54E880;

//----- (004BE310) --------------------------------------------------------
int  Parser_ReplaceLoopCountVars(int result, int exprNode, signed int depth)
{
  int loopVar; // esi
  int currentNode; // ecx
  signed int innerDepth; // ebp
  signed int childDepth; // ebx
  int **Symbol; // eax
  int v9; // ecx
  int *v10; // eax
  int **v11; // eax

  loopVar = result;
  currentNode = exprNode;
  if ( exprNode )
  {
    innerDepth = depth + 1;
    do
    {
      if ( *(_WORD *)currentNode == 15 && (result = strcmp_(currentNode, *(_DWORD *)(loopVar + 16)) == 0) != 0 )
      {
        *(_WORD *)currentNode = 10;
        Symbol = Rules_MakeSymbol(aGetLoopCount_0);
        *(_DWORD *)(v9 + 2) = Symbol;
        v10 = Rules_AddIntegerValue(depth);
        result = AST_NewNode(1, (int)v10);
        *(_DWORD *)(currentNode + 6) = result;
      }
      else if ( *(_DWORD *)(currentNode + 6) )
      {
        if ( *(_WORD *)currentNode == 10 && (v11 = Rules_MakeSymbol(aLoopForCount_0), v11 == *(int ***)(currentNode + 2)) )
          childDepth = innerDepth;
        else
          childDepth = depth;
        result = Parser_ReplaceLoopCountVars(loopVar, *(_DWORD *)(currentNode + 6), childDepth);
      }
      currentNode = *(_DWORD *)(currentNode + 10);
    }
    while ( currentNode );
  }
  return result;
}
// 4BE327: variable 'v4' is possibly undefined
// 4BE374: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004BE3B0) --------------------------------------------------------
int  Parser_ParseIf(int topNode, int readSource)
{
  int v4; // ecx
  int testExpr; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  unsigned int token[8]; // [esp+0h] [ebp-20h] BYREF

  IO_OutWriteToken(asc_50A54C);
  testExpr = Parser_ParseSingleExpression(readSource, 0, v4);
  *(_DWORD *)(topNode + 6) = testExpr;
  if ( !testExpr )
    goto LABEL_15;
  Rules_IncrementIndentDepth(3);
  AST_Append(v7, v6);
  Parser_NextToken(readSource, v8);
  if ( token[0] != 2 || strcmp_(v9, aThen) )
    goto LABEL_14;
  AST_Append(v11, v10);
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  if ( *(_DWORD *)(g_ClipsParseContextSaveStack + 4) == 1 )
    g_ParserBreakContextFlag = 1;
  *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = Parser_ParseProgram(readSource, token, 1);
  if ( !*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) )
    goto LABEL_15;
  if ( token[0] == 101 )
  {
    Rules_DecrementIndentDepth(3);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)token[2]);
    return topNode;
  }
  else
  {
    if ( token[0] != 2 || strcmp_(v12, aElse_0) )
      goto LABEL_14;
    AST_Append(v14, v13);
    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) + 10) = Parser_ParseProgram(readSource, token, 1);
    if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) + 10) )
    {
LABEL_15:
      AST_Free(topNode);
      return 0;
    }
    if ( token[0] != 101 )
    {
LABEL_14:
      Parser_ReportSyntaxError();
      goto LABEL_15;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50A5F4);
    Rules_DecrementIndentDepth(3);
    return topNode;
  }
}
// 4BE3CA: variable 'v4' is possibly undefined
// 4BE3E6: variable 'v7' is possibly undefined
// 4BE3E6: variable 'v6' is possibly undefined
// 4BE3ED: variable 'v8' is possibly undefined
// 4BE408: variable 'v9' is possibly undefined
// 4BE415: variable 'v11' is possibly undefined
// 4BE415: variable 'v10' is possibly undefined
// 4BE47A: variable 'v12' is possibly undefined
// 4BE483: variable 'v14' is possibly undefined
// 4BE483: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE520) --------------------------------------------------------
int  Parser_ParseProgn(int topNode, int readSource)
{
  int v3; // edx
  int v4; // ecx
  unsigned int *theToken; // edx
  int v6; // edx
  char *indentToken; // [esp+0h] [ebp-10h]

  AST_Free(topNode);
  g_ParserBreakContextFlag = *(_DWORD *)(g_ClipsParseContextSaveStack + 4);
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  Rules_IncrementIndentDepth(3);
  AST_Append(v4, v3);
  Parser_ParseProgram(readSource, theToken, 1);
  Rules_DecrementIndentDepth(3);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(indentToken);
  return v6;
}
// 4BE555: variable 'v4' is possibly undefined
// 4BE555: variable 'v3' is possibly undefined
// 4BE55C: variable 'v5' is possibly undefined
// 4BE57B: variable 'v8' is possibly undefined
// 4BE580: variable 'v6' is possibly undefined
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE590) --------------------------------------------------------
int  Parser_ParseBind(int topNode, int readSource)
{
  int v4; // edx
  _BYTE *varConstraint; // ebp
  int v6; // edx
  _DWORD *v7; // ebx
  signed int v8; // ecx
  _DWORD *v9; // ecx
  int varNode; // eax
  int tokenType; // [esp+0h] [ebp-28h]
  int varSymbol; // [esp+4h] [ebp-24h]
  int v14; // [esp+Ch] [ebp-1Ch] BYREF
  int boundVar; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(readSource, v4);
  varConstraint = 0;
  if ( tokenType != 15 && tokenType != 13 && (tokenType != 16 || g_SequenceOperatorRecognition) )
  {
    Parser_ReportSyntaxError();
    AST_Free(topNode);
    return 0;
  }
  *(_DWORD *)(topNode + 6) = AST_NewNode(2, varSymbol);
  boundVar = varSymbol;
  if ( tokenType == 13 && (v6 = Rules_FindImportExportConstruct(aDefglobal_4, &v14, *(_BYTE **)(varSymbol + 16), 1, 0)) != 0 )
  {
    **(_WORD **)(topNode + 6) = 60;
    *(_DWORD *)(*(_DWORD *)(topNode + 6) + 2) = v6;
  }
  else if ( tokenType == 13 )
  {
    Defglobal_PrintUndefinedVariableError();
LABEL_19:
    AST_Free(topNode);
    return 0;
  }
  v7 = *(_DWORD **)(g_ClipsMemoryTable + 56);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *v7;
    v8 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_DWORD *)(v8 + 10) = 0;
  *(_DWORD *)(v8 + 6) = *(_DWORD *)(v8 + 10);
  if ( !Parser_CollectFunctionArguments(v8, readSource, v8) )
    goto LABEL_19;
  *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = *(_DWORD *)((char *)v9 + 6);
  g_ClipsMemFreeListTemp = (int)v9;
  *v9 = *(_DWORD *)(g_ClipsMemoryTable + 56);
  *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
  varNode = *(_DWORD *)(topNode + 6);
  if ( *(_WORD *)varNode != 60 )
  {
    if ( *(_DWORD *)(varNode + 10) )
      varConstraint = Rules_BuildLHSNodeFromToken(*(__int16 **)(varNode + 10));
    Rules_PushNamedContextEntry(boundVar, varConstraint);
  }
  return topNode;
}
// 4BE5AA: variable 'v4' is possibly undefined
// 4BE5B7: variable 'v12' is possibly undefined
// 4BE5DD: variable 'v13' is possibly undefined
// 4BE66D: variable 'v9' is possibly undefined
// 51B360: using guessed type int dword_51B360;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004BE720) --------------------------------------------------------
int __fastcall Parser_ParseReturn(int topNode, int readSource)
{
  _DWORD *v3; // edx
  int v4; // ecx
  signed int argExpr; // eax
  int v6; // ecx
  int v7; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int tokenType; // [esp+0h] [ebp-1Ch]

  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
  {
    g_ClipsParseReturnContext = 1;
  }
  else if ( !g_ClipsParseReturnContext )
  {
    Rules_PrintErrorID((int)aPrcdrpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheReturnFunct, v9);
    AST_Free(v10);
    return 0;
  }
  g_ClipsParseReturnContext = 0;
  IO_OutWriteToken(asc_50A54C);
  argExpr = Parser_ParseArgument(readSource, v3, v4);
  *(_DWORD *)(v6 + 6) = argExpr;
  if ( !argExpr || (IO_OutWriteToken(asc_50A54C), Parser_NextToken(readSource, v11), tokenType == 101) )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50A5F4);
    return v7;
  }
  else
  {
    Parser_ReportSyntaxError();
    AST_Free(v12);
    return 0;
  }
}
// 4BE769: conditional instruction was optimized away because %var_10.4==0
// 4BE75C: variable 'v3' is possibly undefined
// 4BE75C: variable 'v4' is possibly undefined
// 4BE761: variable 'v6' is possibly undefined
// 4BE783: variable 'v7' is possibly undefined
// 4BE7B2: variable 'v9' is possibly undefined
// 4BE7B9: variable 'v10' is possibly undefined
// 4BE7D0: variable 'v11' is possibly undefined
// 4BE7D9: variable 'v13' is possibly undefined
// 4BE7E7: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE800) --------------------------------------------------------
int __fastcall Parser_ParseBreak(int topNode, int readSource)
{
  int v3; // edx
  int v4; // ecx
  int v6; // ecx
  int v7; // ecx
  int tokenType; // [esp+0h] [ebp-14h]

  if ( !*(_DWORD *)(g_ClipsParseContextSaveStack + 4) )
  {
    Rules_PrintErrorID((int)aPrcdrpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheBreakFuncti, v6);
    goto LABEL_4;
  }
  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(readSource, v3);
  if ( tokenType != 101 )
  {
    Parser_ReportSyntaxError();
LABEL_4:
    AST_Free(v4);
    return 0;
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50A5F4);
  return v7;
}
// 4BE822: variable 'v3' is possibly undefined
// 4BE82B: variable 'v8' is possibly undefined
// 4BE839: variable 'v4' is possibly undefined
// 4BE864: variable 'v6' is possibly undefined
// 4BE87F: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;

//----- (004BE890) --------------------------------------------------------
int  Parser_ParseSwitch(int topNode, int readSource)
{
  int caseCount; // ebp
  __int16 *v4; // edx
  int v5; // ecx
  int caseNode; // esi
  int v7; // edx
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  __int16 *existingCaseValue; // ecx
  __int16 *newCaseValue; // eax
  int v14; // ecx
  int caseBody; // esi
  int v16; // edx
  int v17; // ecx
  unsigned int *v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  int token; // [esp+0h] [ebp-28h] BYREF
  char *indentToken; // [esp+8h] [ebp-20h]
  int switchNode; // [esp+Ch] [ebp-1Ch]
  int sawDefault; // [esp+10h] [ebp-18h]

  switchNode = topNode;
  Rules_IncrementIndentDepth(3);
  IO_OutWriteToken(asc_50A54C);
  caseCount = 0;
  sawDefault = 0;
  caseNode = Parser_ParseSingleExpression(readSource, v4, v5);
  *(_DWORD *)(switchNode + 6) = caseNode;
  if ( !caseNode )
    goto LABEL_5;
  Parser_NextToken(readSource, (int)&token);
  while ( token != 101 )
  {
    IO_OutNewline();
    AST_Append(v8, v7);
    IO_OutWriteToken(indentToken);
    if ( token != 100 )
      goto LABEL_4;
    Parser_NextToken(readSource, (int)&token);
    IO_OutWriteToken(asc_50A54C);
    if ( token == 2 && !strcmp_(v10, aCase) )
    {
      if ( sawDefault )
        goto LABEL_4;
      *(_DWORD *)(caseNode + 10) = Parser_ParseSingleExpression(readSource, 0, v11);
      IO_OutWriteToken(asc_50A54C);
      if ( !*(_DWORD *)(caseNode + 10) )
        goto LABEL_5;
      existingCaseValue = *(__int16 **)(*(_DWORD *)(switchNode + 6) + 10);
      if ( existingCaseValue != *(__int16 **)(caseNode + 10) )
      {
        while ( 1 )
        {
          newCaseValue = *(__int16 **)(caseNode + 10);
          if ( *existingCaseValue == *newCaseValue
            && *(_DWORD *)(existingCaseValue + 1) == *(_DWORD *)(newCaseValue + 1)
            && AST_NodeListsEqual(*(__int16 **)(existingCaseValue + 3), *(__int16 **)(newCaseValue + 3)) )
          {
            break;
          }
          existingCaseValue = *(__int16 **)(existingCaseValue + 5);
          if ( existingCaseValue == *(__int16 **)(caseNode + 10) )
            goto LABEL_15;
        }
        Rules_PrintErrorID((int)aPrcdrpsr, 3, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateCaseF, v21);
        goto LABEL_5;
      }
LABEL_15:
      Parser_NextToken(readSource, (int)&token);
      if ( token != 2 || strcmp_(v14, aThen) )
        goto LABEL_4;
      ++caseCount;
    }
    else
    {
      if ( token != 2 || strcmp_(2, aDefault_1) || caseCount < v22 || sawDefault )
        goto LABEL_4;
      *(_DWORD *)(caseNode + 10) = AST_NewNode(105, 0);
      sawDefault = 1;
    }
    caseBody = *(_DWORD *)(caseNode + 10);
    if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
      g_ClipsParseReturnContext = 1;
    if ( *(_DWORD *)(g_ClipsParseContextSaveStack + 4) == 1 )
      g_ParserBreakContextFlag = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v17, v16);
    *(_DWORD *)(caseBody + 10) = Parser_ParseProgram(readSource, v18, 1);
    Rules_DecrementIndentDepth(3);
    g_ClipsParseReturnContext = v19;
    g_ParserBreakContextFlag = v19;
    if ( !*(_DWORD *)(caseBody + 10) )
      goto LABEL_5;
    caseNode = *(_DWORD *)(caseBody + 10);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(indentToken);
    Parser_NextToken(readSource, v20);
  }
  if ( caseCount < 2 )
  {
LABEL_4:
    Parser_ReportSyntaxError();
LABEL_5:
    AST_Free(switchNode);
    Rules_DecrementIndentDepth(3);
    return 0;
  }
  Rules_DecrementIndentDepth(3);
  return switchNode;
}
// 4BE8B8: variable 'v4' is possibly undefined
// 4BE8B8: variable 'v5' is possibly undefined
// 4BE8E6: variable 'v8' is possibly undefined
// 4BE8E6: variable 'v7' is possibly undefined
// 4BE94B: variable 'v10' is possibly undefined
// 4BE962: variable 'v11' is possibly undefined
// 4BE9B3: variable 'v12' is possibly undefined
// 4BE9DA: variable 'v14' is possibly undefined
// 4BEA29: variable 'v17' is possibly undefined
// 4BEA29: variable 'v16' is possibly undefined
// 4BEA32: variable 'v18' is possibly undefined
// 4BEA46: variable 'v19' is possibly undefined
// 4BEA76: variable 'v20' is possibly undefined
// 4BEAC3: variable 'v21' is possibly undefined
// 4BEAF4: variable 'v22' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BEB30) --------------------------------------------------------
signed int  Rules_FindNamedContextDepth(int contextName)
{
  _DWORD *entry; // eax
  int depth; // edx

  entry = (_DWORD *)g_ClipsLoopContextStackTop;
  depth = 1;
  if ( !g_ClipsLoopContextStackTop )
    return 0;
  while ( contextName != *entry )
  {
    entry = (_DWORD *)entry[2];
    ++depth;
    if ( !entry )
      return 0;
  }
  return depth;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEB60) --------------------------------------------------------
int  Rules_GetNamedContextValue(int contextName)
{
  _DWORD *entry; // eax

  entry = (_DWORD *)g_ClipsLoopContextStackTop;
  if ( !g_ClipsLoopContextStackTop )
    return 0;
  while ( contextName != *entry )
  {
    entry = (_DWORD *)entry[2];
    if ( !entry )
      return 0;
  }
  return entry[1];
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEB80) --------------------------------------------------------
int Rules_CountNamedContextEntries(void)
{
  int entry; // eax
  int i; // edx

  entry = g_ClipsLoopContextStackTop;
  for ( i = 0; entry; ++i )
    entry = *(_DWORD *)(entry + 8);
  return i;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEBB0) --------------------------------------------------------
signed int  Rules_PushNamedContextEntry(int contextName, _DWORD *constraint)
{
  int depth; // ebx
  _DWORD *entry; // ecx
  _DWORD *prevEntry; // edx
  _DWORD *oldConstraint; // esi
  int v8; // eax
  int v9; // ecx
  _DWORD *freeBlock; // ecx
  _DWORD *newEntry; // eax

  depth = 1;
  entry = (_DWORD *)g_ClipsLoopContextStackTop;
  prevEntry = 0;
  if ( g_ClipsLoopContextStackTop )
  {
    while ( contextName != *entry )
    {
      prevEntry = entry;
      entry = (_DWORD *)entry[2];
      ++depth;
      if ( !entry )
        goto LABEL_7;
    }
    if ( constraint )
    {
      oldConstraint = (_DWORD *)entry[1];
      v8 = Rules_UnionConstraints((int)constraint, (int)oldConstraint);
      *(_DWORD *)(v9 + 4) = v8;
      AST_DecrementNodeRefCount(oldConstraint);
      AST_DecrementNodeRefCount(constraint);
    }
    return depth;
  }
  else
  {
LABEL_7:
    freeBlock = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( freeBlock )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeBlock;
      newEntry = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newEntry = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    newEntry[2] = 0;
    *newEntry = contextName;
    newEntry[1] = constraint;
    if ( prevEntry )
      prevEntry[2] = newEntry;
    else
      g_ClipsLoopContextStackTop = (int)newEntry;
    return depth;
  }
}
// 4BEBDD: variable 'v9' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BEC50) --------------------------------------------------------
int  Rules_RemoveNamedContextEntry(int result)
{
  int nameKey; // ebx
  int entry; // edx
  int i; // ecx
  _DWORD *v4; // edx

  nameKey = result;
  entry = g_ClipsLoopContextStackTop;
  for ( i = 0; entry; entry = *(_DWORD *)(entry + 8) )
  {
    result = nameKey != *(_DWORD *)entry;
    if ( nameKey == *(_DWORD *)entry )
      break;
    i = entry;
  }
  if ( entry )
  {
    if ( i )
      *(_DWORD *)(i + 8) = *(_DWORD *)(entry + 8);
    else
      g_ClipsLoopContextStackTop = *(_DWORD *)(entry + 8);
    AST_DecrementNodeRefCount(*(_DWORD **)(entry + 4));
    g_ClipsMemFreeListTemp = (int)v4;
    *v4 = *(_DWORD *)(g_ClipsMemoryTable + 48);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4BEC91: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BECC0) --------------------------------------------------------
signed int Rules_RegisterRuleCommands(void)
{
  Rules_RegisterHostFunction(aRun, 118, (int)aRuncommand, (int)Rules_RunCommand, (int)a1i);
  Rules_RegisterHostFunction(aHalt, 118, (int)aHaltcommand, (int)Rules_HaltCommand, (int)a00_9);
  Rules_RegisterHostFunction(aFocus_2, 98, (int)aFocuscommand, (int)Rules_FocusCommand, (int)a1W_1);
  Rules_RegisterHostFunction(aClearFocusStac, 118, (int)aClearfocusstac, (int)Rules_ClearFocusStackCommand, (int)a00_9);
  Rules_RegisterHostFunction(aGetFocusStack, 109, (int)aGetfocusstackf, (int)Rules_GetFocusStackFunction, (int)a00_9);
  Rules_RegisterHostFunction(aPopFocus, 119, (int)aPopfocusfuncti, (int)Rules_PopFocusFunction, (int)a00_9);
  Rules_RegisterHostFunction(aGetFocus, 119, (int)aGetfocusfuncti, (int)Rules_GetFocusFunction, (int)a00_9);
  Rules_RegisterHostFunction(aSetBreak, 118, (int)aSetbreakcomman, (int)Rules_SetBreakCommand, (int)a11w_8);
  Rules_RegisterHostFunction(aRemoveBreak, 118, (int)aRemovebreakcom, (int)Rules_RemoveBreakCommand, (int)a1w);
  Rules_RegisterHostFunction(aShowBreaks, 118, (int)aShowbreakscomm, (int)Rules_ShowBreaksCommand, (int)a01w_5);
  Rules_RegisterHostFunction(aMatches, 118, (int)aMatchescommand, (int)Rules_MatchesCommand, (int)a11w_8);
  Rules_RegisterHostFunction(aListFocusStack, 118, (int)aListfocusstack, (int)Rules_ListFocusStackCommand, (int)a00_9);
  Rules_RegisterHostFunction(aDependencies, 118, (int)aDependenciesco, (int)Rules_Dependencies, (int)a11h);
  Rules_RegisterHostFunction(aDependents, 118, (int)aDependentscomm, (int)Rules_Dependents, (int)a11h);
  Rules_RegisterHostFunction(aGetIncremental, 98, (int)aGetincremental, (int)Rules_GetIncrementalResetCommand, (int)a00_9);
  Rules_RegisterHostFunction(aSetIncremental, 98, (int)aSetincremental, (int)Rules_SetIncrementalResetCommand, (int)a11_4);
  Rules_RegisterHostFunction(aGetStrategy, 119, (int)aGetstrategycom, (int)Rules_GetStrategyCommand, (int)a00_9);
  return Rules_RegisterHostFunction(aSetStrategy, 119, (int)aSetstrategycom, (int)Rules_SetStrategyCommand, (int)a11w_8);
}

//----- (004BEEF0) --------------------------------------------------------
_BYTE * Rules_MatchesCommand(int a1, double a2)
{
  _BYTE *result; // eax
  int v3; // ecx
  _DWORD *theDefrule; // eax
  int v5; // edx
  int v6; // ecx

  result = (_BYTE *)Rules_GetConstructNameArg((int)aRuleName_0, a1, a2);
  if ( result )
  {
    theDefrule = (_DWORD *)Rules_FindDefruleByName(result, v3);
    if ( theDefrule )
      return (_BYTE *)Rules_ListDefruleMatches(theDefrule, v6);
    else
      return (_BYTE *)Rules_ReportCantFindItem(v6, v5);
  }
  return result;
}
// 4BEF08: variable 'v3' is possibly undefined
// 4BEF16: variable 'v6' is possibly undefined
// 4BEF16: variable 'v5' is possibly undefined
