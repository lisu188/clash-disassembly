/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004D9FD0) --------------------------------------------------------
int  Lexer_ParseDeclareOptions(_DWORD *error, double a2)
{
  int salienceParsed; // ebx
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int autoFocusParsed; // ebp
  int v8; // ecx
  int result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  _DWORD theToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  IO_OutWriteToken(asc_50D764);
  salienceParsed = 0;
  Parser_NextToken(v5, v4);
  autoFocusParsed = 0;
  if ( theToken[0] == 100 )
  {
    while ( 1 )
    {
      Parser_NextToken(v6, (int)(intptr_t)theToken);
      if ( theToken[0] != 2 )
      {
LABEL_3:
        Parser_ReportSyntaxError();
LABEL_4:
        *error = 1;
LABEL_5:
        result = AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        return result;
      }
      if ( !strcmp_(v8, aSalience) )
      {
        if ( salienceParsed )
          goto LABEL_18;
        Lexer_ParseSalienceOption(error, a2);
        salienceParsed = 1;
      }
      else
      {
        if ( strcmp_(v10, aAutoFocus) )
          goto LABEL_3;
        if ( autoFocusParsed )
        {
LABEL_18:
          Rules_ReportAlreadyParsed(v10, 0);
          goto LABEL_4;
        }
        autoFocusParsed = 1;
        Lexer_ParseAutoFocusOption(v10);
      }
      if ( *error )
        goto LABEL_5;
      Parser_NextToken(v11, (int)(intptr_t)theToken);
      if ( theToken[0] != 101 )
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_50D764);
        IO_OutWriteToken((char *)(uintptr_t)theToken[2]);
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = v13;
        result = Parser_ReportSyntaxError();
        *error = 1;
        return result;
      }
      Parser_NextToken(v12, (int)(intptr_t)theToken);
      if ( theToken[0] == 101 )
        break;
      if ( theToken[0] != 100 )
      {
        AST_Free(g_ClipsParsedFormAst);
        g_ClipsParsedFormAst = 0;
        result = Parser_ReportSyntaxError();
        *error = 1;
        return result;
      }
      IO_OutNewline();
      IO_OutWriteToken(Lexer_Token_OpenParenSpace);
    }
    AST_PackNodeChain((_DWORD *)(uintptr_t)g_ClipsParsedFormAst);
    result = AST_Free(g_ClipsParsedFormAst);
    g_ClipsParsedFormAst = v14;
  }
  else
  {
    result = Parser_ReportSyntaxError();
    *error = 1;
  }
  return result;
}
// 4D9FED: variable 'v5' is possibly undefined
// 4D9FED: variable 'v4' is possibly undefined
// 4DA000: variable 'v6' is possibly undefined
// 4DA053: variable 'v8' is possibly undefined
// 4DA079: variable 'v11' is possibly undefined
// 4DA08C: variable 'v12' is possibly undefined
// 4DA0D7: variable 'v10' is possibly undefined
// 4DA135: variable 'v13' is possibly undefined
// 4DA18E: variable 'v14' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51C6F4: using guessed type int dword_51C6F4;

//----- (004DA1A0) --------------------------------------------------------
int  Lexer_ParseSalienceOption(_DWORD *error, double a2)
{
  int v2; // ecx
  int result; // eax
  _DWORD *v4; // edx
  int v5; // ecx
  int salienceValue; // ecx
  int parsedType; // [esp+0h] [ebp-1Ch]
  int parsedValueNode; // [esp+4h] [ebp-18h]

  IO_OutWriteToken(asc_50D764);
  result = Parser_ParseSingleExpression(v2, 0, v2);
  g_ClipsParsedFormAst = result;
  if ( result )
  {
    Lexer_ErrorRecover(0);
    if ( Parser_ParseForm((__int16 *)(uintptr_t)g_ClipsParsedFormAst, v4, v5, a2) )
    {
      result = Rules_SalienceInformationError();
      *error = 1;
    }
    else if ( parsedType == 1 )
    {
      salienceValue = *(_DWORD *)(uintptr_t)(parsedValueNode + 16);
      if ( salienceValue > 10000 || salienceValue < -10000 )
      {
        result = Rules_SalienceRangeError();
        *error = 1;
      }
      else
      {
        result = g_ClipsParsedFormAst;
        if ( *(_WORD *)(uintptr_t)g_ClipsParsedFormAst == 1 )
        {
          result = AST_Free(g_ClipsParsedFormAst);
          g_ClipsParsedFormAst = 0;
        }
        g_CLIPS_CurrentRuleSalience = salienceValue;
      }
    }
    else
    {
      result = Rules_SalienceNonIntegerError();
      *error = 1;
    }
  }
  else
  {
    *error = 1;
  }
  return result;
}
// 4DA1B7: variable 'v2' is possibly undefined
// 4DA1DF: variable 'v4' is possibly undefined
// 4DA1DF: variable 'v5' is possibly undefined
// 4DA1ED: variable 'v7' is possibly undefined
// 4DA1F3: variable 'v8' is possibly undefined
// 4DA21E: variable 'v6' is possibly undefined
// 51C6F4: using guessed type int dword_51C6F4;
// 54E910: using guessed type int dword_54E910;

//----- (004DA260) --------------------------------------------------------
int  Lexer_ParseAutoFocusOption(int readSource)
{
  int v2; // edx
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  _DWORD *errorPtr; // ecx
  int tokenType; // [esp+0h] [ebp-14h]

  IO_OutWriteToken(asc_50D764);
  Parser_NextToken(readSource, v2);
  if ( tokenType != 2 )
    goto LABEL_5;
  result = strcmp_(v3, aTrue_0);
  if ( result )
  {
    result = strcmp_(v5, aFalse_0);
    if ( !result )
    {
      g_Rules_DeclaredAutoFocusFlag = 0;
      return result;
    }
LABEL_5:
    result = Parser_ReportSyntaxError();
    *errorPtr = 1;
    return result;
  }
  g_Rules_DeclaredAutoFocusFlag = 1;
  return result;
}
// 4DA277: variable 'v2' is possibly undefined
// 4DA280: variable 'v7' is possibly undefined
// 4DA28E: variable 'v3' is possibly undefined
// 4DA2B1: variable 'v6' is possibly undefined
// 4DA2C5: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E90C: using guessed type int dword_54E90C;

//----- (004DA2E0) --------------------------------------------------------
_DWORD * Lexer_ParsePatternCE(int readSource, int terminator, int terminatorString, double a4, int allowDeclaration, int firstToken, int ruleName)
{
  _DWORD *v9; // ecx
  _DWORD *result; // eax
  _DWORD *v11; // ecx
  _DWORD *v12; // ecx
  _DWORD *v13; // ecx
  _DWORD *v14; // ecx
  _DWORD *v15; // ecx
  _DWORD *v16; // ecx
  _DWORD *v17; // ecx
  _DWORD *v18; // ecx
  _DWORD *v19; // ecx
  int theToken; // [esp+0h] [ebp-18h] BYREF

  if ( firstToken )
    qmemcpy(&theToken, (const void *)(uintptr_t)firstToken, 12);
  else
    Parser_NextToken(readSource, (int)(intptr_t)&theToken);
  if ( theToken != 100 )
  {
    if ( theToken == 15 )
    {
      result = (_DWORD *)(uintptr_t)Lexer_ParsePatternBinding((int)(intptr_t)v9, v9);
      if ( *v11 != 1 )
        return result;
LABEL_33:
      AST_FreeNode((int)(intptr_t)result);
      return 0;
    }
    if ( terminator == theToken && !strcmp_(v9, terminatorString) )
      return 0;
LABEL_15:
    Parser_ReportSyntaxError();
    *v14 = 1;
    return 0;
  }
  Parser_NextToken(readSource, (int)(intptr_t)&theToken);
  if ( theToken != 2 )
    goto LABEL_15;
  if ( allowDeclaration && !strcmp_(v12, aDeclare) )
  {
    if ( !ruleName )
      Rules_ReportSystemError((int)(intptr_t)v12, 1);
    Lexer_ParseDeclareOptions(v12, a4);
    result = 0;
    if ( *v13 == 1 )
      goto LABEL_33;
  }
  else if ( !strcmp_(v12, aTest_0) )
  {
    result = (_DWORD *)(uintptr_t)Lexer_ParseTestCE(readSource, v15, (int)(intptr_t)v15);
    if ( *v16 == 1 )
      goto LABEL_33;
  }
  else if ( !strcmp_(v15, aAnd_1)
         || !strcmp_(v17, aLogical_0)
         || !strcmp_(v17, aNot_1)
         || !strcmp_(v17, aExists_0)
         || !strcmp_(v17, aForall_0)
         || !strcmp_(v17, aOr_1) )
  {
    result = (_DWORD *)(uintptr_t)Lexer_ParseConnectiveCE(v17, readSource, a4);
    if ( *v18 == 1 )
      goto LABEL_33;
  }
  else
  {
    result = Rules_DispatchPatternTypeParser(&theToken, (int)(intptr_t)v17, v17);
    if ( *v19 == 1 )
      goto LABEL_33;
  }
  return result;
}
// 4DA316: variable 'v9' is possibly undefined
// 4DA31B: variable 'v11' is possibly undefined
// 4DA358: variable 'v12' is possibly undefined
// 4DA381: variable 'v13' is possibly undefined
// 4DA39D: variable 'v14' is possibly undefined
// 4DA3C7: variable 'v15' is possibly undefined
// 4DA3CC: variable 'v16' is possibly undefined
// 4DA3FF: variable 'v17' is possibly undefined
// 4DA467: variable 'v18' is possibly undefined
// 4DA480: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 494140: using guessed type int COleDateTimeSpan::operator=(void);

//----- (004DA4E0) --------------------------------------------------------
signed int  Lexer_ParseConnectiveCE(_DWORD *error, int readSource, double a3)
{
  int connectorValue; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *connectorString; // eax
  int v8; // edx
  signed int theGroup; // ecx
  signed int v10; // edx
  int v11; // ecx
  signed int theNode; // ebp
  int logicalBits; // edi
  signed int result; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int savedRightNode; // esi
  _DWORD *v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // ecx
  signed int v29; // eax
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // eax
  int v34; // esi
  _DWORD *v35; // eax
  int v36; // edx
  int v37; // ecx
  int v38; // eax
  signed int v39; // eax
  int v40; // edx
  int v41; // eax
  int v42; // ecx
  _DWORD *v43; // eax
  int v44; // eax
  int v45; // ecx
  int savedNegatedFlag; // [esp+4h] [ebp-18h]
  int logicalCE; // [esp+8h] [ebp-14h]

  Rules_IncrementIndentDepth(5);
  connectorValue = 0;
  logicalCE = 0;
  if ( !strcmp_(v4, aOr_1) )
  {
    connectorValue = 82;
    connectorString = asc_50D870;
    goto LABEL_4;
  }
  if ( !strcmp_(v5, aAnd_1) )
  {
    connectorValue = 81;
    connectorString = asc_50D764;
LABEL_4:
    IO_OutWriteToken(connectorString);
    goto LABEL_5;
  }
  if ( !strcmp_(v6, aNot_1) )
  {
    connectorValue = 83;
    connectorString = asc_50D764;
    goto LABEL_4;
  }
  if ( !strcmp_(v15, aExists_0) )
  {
    AST_Append(v17, v16);
    connectorValue = 86;
  }
  else if ( !strcmp_(v17, aForall_0) )
  {
    AST_Append(v19, v18);
    connectorValue = 87;
  }
  else if ( !strcmp_(v19, aLogical_0) )
  {
    AST_Append(v21, v20);
    connectorValue = 81;
    logicalCE = 1;
  }
LABEL_5:
  if ( g_Parser_InsideNegatedCEFlag && logicalCE )
  {
    Rules_PrintErrorID((int)(intptr_t)aRulelhs, 1, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheLogicalCeCa, v22);
    *error = 1;
    return 0;
  }
  savedNegatedFlag = g_Parser_InsideNegatedCEFlag;
  if ( connectorValue == 83 || connectorValue == 86 || connectorValue == 87 )
    g_Parser_InsideNegatedCEFlag = 1;
  Lexer_ParsePatternCEList(101, error, asc_50D94C, readSource, a3);
  g_Parser_InsideNegatedCEFlag = savedNegatedFlag;
  Rules_DecrementIndentDepth(5);
  if ( *error == 1 )
  {
    AST_FreeNode(v8);
    return 0;
  }
  if ( logicalCE )
    AST_MarkLogicalCEChain(v8);
  if ( !theGroup )
  {
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
  if ( connectorValue == 83 && *(_DWORD *)(uintptr_t)(theGroup + 68) || connectorValue == 87 && !*(_DWORD *)(uintptr_t)(theGroup + 68) )
  {
    Parser_ReportSyntaxError();
    AST_FreeNode(v23);
    *error = 1;
    return 0;
  }
  if ( (connectorValue == 81 || connectorValue == 82) && !*(_DWORD *)(uintptr_t)(theGroup + 68) )
  {
    *(_BYTE *)(uintptr_t)(theGroup + 8) &= ~2u;
    result = theGroup;
    *(_DWORD *)(uintptr_t)(theGroup + 8) |= 2 * (logicalCE & 1);
    return result;
  }
  v10 = AST_AllocNode();
  theNode = v10;
  *(_BYTE *)(uintptr_t)(v10 + 8) &= ~2u;
  logicalBits = 2 * (logicalCE & 1);
  *(_DWORD *)(uintptr_t)(v10 + 8) |= logicalBits;
  if ( connectorValue == 81 || connectorValue == 82 || connectorValue == 83 )
  {
    *(_DWORD *)(uintptr_t)v10 = connectorValue;
    *(_DWORD *)(uintptr_t)(v10 + 64) = v11;
    return v10;
  }
  if ( connectorValue != 86 )
  {
    if ( connectorValue == 87 )
    {
      *(_DWORD *)(uintptr_t)v10 = 83;
      savedRightNode = *(_DWORD *)(uintptr_t)(v11 + 68);
      *(_DWORD *)(uintptr_t)(v11 + 68) = 0;
      v25 = (_DWORD *)(uintptr_t)AST_AllocNode();
      *(_DWORD *)(uintptr_t)(v26 + 64) = v25;
      *v25 = 81;
      v27 = *(_DWORD *)(uintptr_t)(v26 + 64);
      *(_BYTE *)(uintptr_t)(v27 + 8) &= ~2u;
      *(_DWORD *)(uintptr_t)(v27 + 8) |= logicalBits;
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v26 + 64) + 64) = v28;
      v29 = AST_AllocNode();
      v30 = savedRightNode;
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v31 + 64) + 64) + 68) = v29;
      **(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v31 + 64) + 64) + 68) = 83;
      v32 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v31 + 64) + 64) + 68);
      *(_BYTE *)(uintptr_t)(v32 + 8) &= ~2u;
      *(_DWORD *)(uintptr_t)(v32 + 8) |= logicalBits;
      v33 = *(_DWORD *)(uintptr_t)(savedRightNode + 68);
      v34 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v31 + 64) + 64) + 68);
      if ( v33 )
      {
        v43 = (_DWORD *)(uintptr_t)AST_AllocNode();
        *(_DWORD *)(uintptr_t)(v34 + 64) = v43;
        *v43 = 81;
        v44 = *(_DWORD *)(uintptr_t)(v34 + 64);
        *(_BYTE *)(uintptr_t)(v44 + 8) &= ~2u;
        *(_DWORD *)(uintptr_t)(v44 + 8) |= logicalBits;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v34 + 64) + 64) = v45;
      }
      else
      {
        *(_DWORD *)(uintptr_t)(v34 + 64) = v30;
      }
      return theNode;
    }
    return v10;
  }
  *(_DWORD *)(uintptr_t)v10 = 83;
  v35 = (_DWORD *)(uintptr_t)AST_AllocNode();
  *(_DWORD *)(uintptr_t)(v36 + 64) = v35;
  *v35 = 83;
  v38 = *(_DWORD *)(uintptr_t)(v36 + 64);
  *(_BYTE *)(uintptr_t)(v38 + 8) &= ~2u;
  *(_DWORD *)(uintptr_t)(v38 + 8) |= logicalBits;
  if ( *(_DWORD *)(uintptr_t)(v37 + 68) )
  {
    v39 = AST_AllocNode();
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v40 + 64) + 64) = v39;
    **(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(v40 + 64) + 64) = 81;
    v41 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v40 + 64) + 64);
    *(_BYTE *)(uintptr_t)(v41 + 8) &= ~2u;
    *(_DWORD *)(uintptr_t)(v41 + 8) |= logicalBits;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v40 + 64) + 64) + 64) = v42;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v36 + 64) + 64) = v37;
  }
  return theNode;
}
// 4DA509: variable 'v4' is possibly undefined
// 4DA521: variable 'v5' is possibly undefined
// 4DA5B0: variable 'v8' is possibly undefined
// 4DA5B7: variable 'v9' is possibly undefined
// 4DA618: variable 'v11' is possibly undefined
// 4DA644: variable 'v6' is possibly undefined
// 4DA658: variable 'v15' is possibly undefined
// 4DA66C: variable 'v17' is possibly undefined
// 4DA675: variable 'v19' is possibly undefined
// 4DA675: variable 'v18' is possibly undefined
// 4DA69D: variable 'v16' is possibly undefined
// 4DA6C9: variable 'v21' is possibly undefined
// 4DA6C9: variable 'v20' is possibly undefined
// 4DA701: variable 'v22' is possibly undefined
// 4DA760: variable 'v23' is possibly undefined
// 4DA7E1: variable 'v26' is possibly undefined
// 4DA7F7: variable 'v28' is possibly undefined
// 4DA801: variable 'v31' is possibly undefined
// 4DA851: variable 'v36' is possibly undefined
// 4DA864: variable 'v37' is possibly undefined
// 4DA87F: variable 'v40' is possibly undefined
// 4DA8A4: variable 'v42' is possibly undefined
// 4DA8CC: variable 'v45' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51C6F0: using guessed type int dword_51C6F0;

//----- (004DA8E0) --------------------------------------------------------
int  Lexer_ParsePatternCEList(int terminator, _DWORD *error, char *terminatorString, int readSource, double a5)
{
  int lastNode; // edi
  int newNode; // eax
  int v8; // edx
  int v10; // edx
  int v11; // ecx
  int head; // [esp+8h] [ebp-10h]

  lastNode = 0;
  head = 0;
  while ( 1 )
  {
    newNode = Lexer_ParsePatternCE(readSource, terminator, (int)(intptr_t)terminatorString, a5, 0, 0, 0);
    if ( *error )
    {
      AST_FreeNode(head);
      return 0;
    }
    if ( !newNode )
      break;
    if ( lastNode )
      *(_DWORD *)(uintptr_t)(lastNode + 68) = newNode;
    else
      head = newNode;
    AST_Append(0, newNode);
    lastNode = v8;
  }
  IO_OutNewline();
  IO_OutNewline();
  if ( terminator != 101 )
    AST_Append(v11, v10);
  IO_OutWriteToken(terminatorString);
  return head;
}
// 4DA929: variable 'v8' is possibly undefined
// 4DA95F: variable 'v11' is possibly undefined
// 4DA95F: variable 'v10' is possibly undefined

//----- (004DA980) --------------------------------------------------------
int  Lexer_ParseTestCE(int readSource, _DWORD *error, int a3)
{
  _DWORD *theNode; // eax
  __int16 *theExpression; // eax
  __int16 *expressionCopy; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v13; // ecx
  _DWORD theToken[6]; // [esp+0h] [ebp-18h] BYREF

  theToken[4] = a3;
  IO_OutWriteToken(asc_50D764);
  theNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *theNode = 84;
  theExpression = (__int16 *)(uintptr_t)Parser_ParseRequiredFunctionCall(readSource, (int)(intptr_t)theNode);
  expressionCopy = Rules_CECloneRestrictionExpr(theExpression);
  *(_DWORD *)(uintptr_t)(v8 + 56) = expressionCopy;
  AST_Free(v9);
  if ( *(_DWORD *)(uintptr_t)(v10 + 56) )
  {
    Parser_NextToken(readSource, (int)(intptr_t)theToken);
    if ( theToken[0] == 101 )
    {
      return v11;
    }
    else
    {
      Parser_ReportSyntaxError();
      *error = 1;
      AST_FreeNode(v13);
      return 0;
    }
  }
  else
  {
    *error = 1;
    AST_FreeNode(v10);
    return 0;
  }
}
// 4DA9AF: variable 'v8' is possibly undefined
// 4DA9B4: variable 'v9' is possibly undefined
// 4DA9B9: variable 'v10' is possibly undefined
// 4DA9CE: variable 'v11' is possibly undefined
// 4DA9FA: variable 'v13' is possibly undefined

//----- (004DAA10) --------------------------------------------------------
int  Lexer_ParsePatternBinding(int readSource, _DWORD *error)
{
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int tokenType; // [esp+0h] [ebp-18h]
  int v11; // [esp+14h] [ebp-4h]

  v11 = readSource;
  if ( g_Parser_InsideNegatedCEFlag )
  {
    Rules_PrintErrorID((int)(intptr_t)aRulelhs, 2, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAPatternCeCann, v8);
    *error = 1;
    return 0;
  }
  else
  {
    IO_OutWriteToken(asc_50D764);
    Parser_NextToken(v4, v3);
    if ( tokenType == 2 && !strcmp_(v5, asc_50D9B0) )
    {
      IO_OutWriteToken(asc_50D764);
      Parser_NextToken(v7, v6);
    }
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
}
// 4DAA7A: conditional instruction was optimized away because %var_18.4==2
// 4DAA37: variable 'v4' is possibly undefined
// 4DAA37: variable 'v3' is possibly undefined
// 4DAA52: variable 'v5' is possibly undefined
// 4DAA71: variable 'v7' is possibly undefined
// 4DAA71: variable 'v6' is possibly undefined
// 4DAABD: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51C6F0: using guessed type int dword_51C6F0;

//----- (004DAAF0) --------------------------------------------------------
int  AST_MarkLogicalCEChain(int result)
{
  int i; // edx
  int nodeType; // ecx
  int v3; // edx

  for ( i = result; i; i = *(_DWORD *)(uintptr_t)(i + 68) )
  {
    while ( 1 )
    {
      BYTE1(result) = *(_BYTE *)(uintptr_t)(i + 8) | 2;
      nodeType = *(_DWORD *)(uintptr_t)i;
      *(_BYTE *)(uintptr_t)(i + 8) = BYTE1(result);
      if ( nodeType != 81 && nodeType != 82 && nodeType != 83 )
        break;
      result = AST_MarkLogicalCEChain(*(_DWORD *)(uintptr_t)(i + 64));
      i = *(_DWORD *)(uintptr_t)(v3 + 68);
      if ( !i )
        return result;
    }
  }
  return result;
}
// 4DAB15: variable 'v3' is possibly undefined

//----- (004DAB30) --------------------------------------------------------
_DWORD * Rules_DispatchPatternTypeParser(_DWORD *theToken, int a2, _DWORD *error)
{
  int v5; // ecx
  signed int newNode; // eax
  char nodeFlags; // dl
  int patternParser; // ecx
  _DWORD *theNode; // ebx
  int v10; // ecx
  int parsedPattern; // eax
  int v13; // ecx

  if ( *theToken != 2 || !strcmp_(a2, asc_50D9C8) || !strcmp_(v5, asc_50D9CC) )
  {
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
  newNode = AST_AllocNode();
  nodeFlags = *(_BYTE *)(uintptr_t)(newNode + 8);
  *(_DWORD *)(uintptr_t)newNode = 80;
  *(_BYTE *)(uintptr_t)(newNode + 8) = nodeFlags & 0xFE;
  patternParser = g_PatternParserListHead;
  theNode = (_DWORD *)(uintptr_t)newNode;
  if ( !g_PatternParserListHead )
  {
LABEL_7:
    *error = 1;
    Parser_ReportSyntaxError();
    AST_FreeNode((int)(intptr_t)theNode);
    return 0;
  }
  while ( !(*(int (**)(void))(uintptr_t)(patternParser + 12))() )
  {
    patternParser = *(_DWORD *)(uintptr_t)(v10 + 92);
    if ( !patternParser )
      goto LABEL_7;
  }
  theNode[6] = v10;
  parsedPattern = (*(int (__fastcall **)(int, _DWORD *))(uintptr_t)(v10 + 16))(v10, theToken);
  theNode[16] = parsedPattern;
  if ( parsedPattern )
  {
    AST_PropagateDepthTag(theNode, v13);
    return theNode;
  }
  else
  {
    *error = 1;
    AST_FreeNode((int)(intptr_t)theNode);
    return 0;
  }
}
// 4DAB66: variable 'v5' is possibly undefined
// 4DAB99: variable 'v10' is possibly undefined
// 4DAC0B: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B348: using guessed type int dword_51B348;

//----- (004DAC20) --------------------------------------------------------
_DWORD * AST_PropagateDepthTag(_DWORD *result, int depth)
{
  _DWORD *i; // ecx
  int childNode; // edx

  for ( i = result; i; i = (_DWORD *)(uintptr_t)i[17] )
  {
    childNode = i[16];
    i[6] = depth;
    if ( childNode )
      result = (_DWORD *)AST_PropagateDepthTag(childNode, depth);
    if ( i[14] )
      result = (_DWORD *)AST_PropagateDepthTag(i[14], depth);
  }
  return result;
}
// 4DAC35: variable 'i' is possibly undefined

//----- (004DAC60) --------------------------------------------------------
_DWORD * AST_MarkNodeFieldBound(_DWORD *result, int theBsaveID)
{
  *(_BYTE *)(uintptr_t)(*result + 12) |= 2u;
  result[3] = theBsaveID;
  return result;
}

//----- (004DAC70) --------------------------------------------------------
_DWORD * AST_ExtractPatternBindingInfo(_DWORD *result, int theConstruct)
{
  int nextConstruct; // ecx

  *result = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theConstruct + 12) << 16 >> 18;
  result[1] = *(_DWORD *)(uintptr_t)(**(_DWORD **)(uintptr_t)(theConstruct + 8) + 24);
  nextConstruct = *(_DWORD *)(uintptr_t)(theConstruct + 16);
  if ( nextConstruct )
    result[2] = *(_DWORD *)(uintptr_t)(nextConstruct + 12);
  else
    result[2] = -1;
  return result;
}

//----- (004DACB0) --------------------------------------------------------
int  Rules_BuildIndexedSlotDescriptor(int result, _DWORD *theConstruct, int moduleItemArray, int moduleItemSize, int constructSize, int constructArray)
{
  int nameSymbol; // ecx
  int nextIndex; // ebp

  theConstruct[2] = *(_DWORD *)(uintptr_t)(result + 4) * moduleItemSize + moduleItemArray;
  nameSymbol = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * *(_DWORD *)(uintptr_t)result);
  *theConstruct = nameSymbol;
  ++*(_DWORD *)(uintptr_t)(nameSymbol + 4);
  nextIndex = *(_DWORD *)(uintptr_t)(result + 8);
  if ( nextIndex == -1 )
  {
    theConstruct[4] = 0;
  }
  else
  {
    result = nextIndex * constructSize;
    theConstruct[4] = nextIndex * constructSize + constructArray;
  }
  theConstruct[1] = 0;
  theConstruct[3] = 0;
  return result;
}
// 54E674: using guessed type int dword_54E674;

//----- (004DAD10) --------------------------------------------------------
int  Rules_ReleaseSymbolReference(int *symbolPtr, int a2)
{
  return Rules_DecrementSymbolCount(*symbolPtr, a2);
}

//----- (004DAD20) --------------------------------------------------------
_DWORD *Module_RegisterBsaveBloadHandlers(void)
{
  Rules_AddBeforeBloadFunction((int)(intptr_t)aDefmodule_3, (int)(intptr_t)Module_RemoveAllModules, 2000);
  Rules_RegisterBinaryItem(
    (int)(intptr_t)aDefmodule_3,
    0,
    0,
    (int)(intptr_t)Module_BsaveCountModulesAndItems,
    (int)(intptr_t)Module_BsaveWriteHeaderCounts,
    (int)(intptr_t)Module_BsaveWriteModuleRecords,
    (int)(intptr_t)Module_BloadReadHeaderCounts,
    (int)(intptr_t)Module_BloadRefreshModules,
    (int)(intptr_t)Module_ClearBloadData);
  return Rules_AddAbortBloadFunction((int)(intptr_t)aDefmodule_3, (int)(intptr_t)Module_CreateMainModule, 0);
}

//----- (004DAD80) --------------------------------------------------------
_DWORD * Module_UpdateItemHeader(_DWORD *result, _DWORD *theHeader, int itemArray, int itemSize)
{
  int firstItemIndex; // esi
  int firstItemOffset; // esi
  int lastItemOffset; // ebx

  *theHeader = 32 * *result + g_ClipsModuleArrayBase;
  firstItemIndex = result[1];
  if ( firstItemIndex == -1 )
  {
    theHeader[1] = 0;
    theHeader[2] = 0;
  }
  else
  {
    firstItemOffset = itemSize * firstItemIndex;
    lastItemOffset = result[2] * itemSize;
    result = (_DWORD *)(uintptr_t)(itemArray + firstItemOffset);
    theHeader[1] = itemArray + firstItemOffset;
    theHeader[2] = lastItemOffset + itemArray;
  }
  return result;
}
// 51C704: using guessed type int dword_51C704;

//----- (004DADC0) --------------------------------------------------------
_DWORD * Module_AssignBsaveItemHeaderIndices(_DWORD *result, _DWORD *theHeader)
{
  int firstItem; // ecx

  *result = *(_DWORD *)(uintptr_t)(*theHeader + 24);
  firstItem = theHeader[1];
  if ( firstItem )
  {
    result[1] = *(_DWORD *)(uintptr_t)(firstItem + 12);
    result[2] = *(_DWORD *)(uintptr_t)(theHeader[2] + 12);
  }
  else
  {
    result[1] = -1;
    result[2] = -1;
  }
  return result;
}

//----- (004DADF0) --------------------------------------------------------
_DWORD *Module_BsaveCountModulesAndItems(void)
{
  _DWORD *result; // eax
  _DWORD *i; // ecx
  _DWORD *j; // eax
  int importConstructType; // edx
  int importItemName; // ebp
  _DWORD *k; // eax
  int exportConstructType; // ebp
  int exportItemName; // ebp

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_ClipsBsaveModuleCount);
    Rules_ConstructQueuePush(g_ClipsBloadPortItemCount);
  }
  g_ClipsBsaveModuleCount = 0;
  g_ClipsBloadPortItemCount = 0;
  result = (_DWORD *)(uintptr_t)Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ++g_ClipsBsaveModuleCount;
    *(_DWORD *)(uintptr_t)(*i + 12) |= 2u;
    for ( j = (_DWORD *)(uintptr_t)i[3]; j; j = (_DWORD *)(uintptr_t)j[3] )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *j )
        *(_DWORD *)(uintptr_t)(*j + 12) |= 2u;
      importConstructType = j[1];
      if ( importConstructType )
        *(_DWORD *)(uintptr_t)(importConstructType + 12) |= 2u;
      importItemName = j[2];
      if ( importItemName )
        *(_DWORD *)(uintptr_t)(importItemName + 12) |= 2u;
    }
    for ( k = (_DWORD *)(uintptr_t)i[4]; k; k = (_DWORD *)(uintptr_t)k[3] )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *k )
        *(_DWORD *)(uintptr_t)(*k + 12) |= 2u;
      exportConstructType = k[1];
      if ( exportConstructType )
        *(_DWORD *)(uintptr_t)(exportConstructType + 12) |= 2u;
      exportItemName = k[2];
      if ( exportItemName )
        *(_DWORD *)(uintptr_t)(exportItemName + 12) |= 2u;
    }
    result = (_DWORD *)(uintptr_t)Module_NextEnum((int)(intptr_t)i);
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAEC0) --------------------------------------------------------
const void * Module_BsaveWriteHeaderCounts(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD spaceNeeded[4]; // [esp+0h] [ebp-10h] BYREF

  spaceNeeded[2] = a2;
  spaceNeeded[0] = 8;
  Rules_BsaveWriteBlock(4, fp, spaceNeeded);
  Rules_BsaveWriteBlock(4, v2, &g_ClipsBsaveModuleCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ClipsBloadPortItemCount);
}
// 4DAEEA: variable 'v2' is possibly undefined
// 4DAEFB: variable 'v3' is possibly undefined
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DAF10) --------------------------------------------------------
int  Module_BsaveWriteModuleRecords(int filePtr)
{
  int v2; // ecx
  _DWORD *i; // ecx
  int nextModuleIndex; // ebp
  int v5; // eax
  int v6; // ecx
  int m; // edi
  _DWORD *n; // ecx
  int importTypeSymbol; // eax
  int importNameSymbol; // ebx
  int v11; // ecx
  _DWORD *ii; // ecx
  int exportTypeSymbol; // eax
  int exportNameSymbol; // ebx
  int v15; // ecx
  int result; // eax
  int j; // eax
  int k; // eax
  int nameIndex; // [esp+0h] [ebp-40h] BYREF
  int importListIndex; // [esp+4h] [ebp-3Ch]
  int exportListIndex; // [esp+8h] [ebp-38h]
  int nextIndex; // [esp+Ch] [ebp-34h]
  int bsaveId; // [esp+10h] [ebp-30h]
  int portModuleName; // [esp+14h] [ebp-2Ch] BYREF
  int portConstructType; // [esp+18h] [ebp-28h]
  int portConstructName; // [esp+1Ch] [ebp-24h]
  int portNextIndex; // [esp+20h] [ebp-20h]
  int space[7]; // [esp+24h] [ebp-1Ch] BYREF

  space[0] = 16 * g_ClipsBloadPortItemCount + 20 * g_ClipsBsaveModuleCount;
  Rules_BsaveWriteBlock(4, filePtr, space);
  g_ClipsBsaveModuleCount = v2;
  g_ClipsBloadPortItemCount = v2;
  for ( i = (_DWORD *)(uintptr_t)Module_NextEnum(0); i; i = (_DWORD *)(uintptr_t)Module_NextEnum(v6) )
  {
    nextModuleIndex = g_ClipsBsaveModuleCount + 1;
    v5 = *(_DWORD *)(uintptr_t)(*i + 12) << 16 >> 18;
    ++g_ClipsBsaveModuleCount;
    nameIndex = v5;
    if ( i[7] )
      nextIndex = nextModuleIndex;
    else
      nextIndex = -1;
    if ( i[3] )
    {
      importListIndex = g_ClipsBloadPortItemCount;
      for ( j = i[3]; j; j = *(_DWORD *)(uintptr_t)(j + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      importListIndex = -1;
    }
    if ( i[4] )
    {
      exportListIndex = g_ClipsBloadPortItemCount;
      for ( k = i[4]; k; k = *(_DWORD *)(uintptr_t)(k + 12) )
        ++g_ClipsBloadPortItemCount;
    }
    else
    {
      exportListIndex = -1;
    }
    bsaveId = i[6];
    Rules_BsaveWriteBlock(20, filePtr, &nameIndex);
  }
  g_ClipsBloadPortItemCount = 0;
  for ( m = Module_NextEnum(0); m; m = Module_NextEnum(m) )
  {
    for ( n = *(_DWORD **)(uintptr_t)(m + 12); n; n = *(_DWORD **)(uintptr_t)(v11 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *n )
        portModuleName = *(_DWORD *)(uintptr_t)(*n + 12) << 16 >> 18;
      else
        portModuleName = -1;
      importTypeSymbol = n[1];
      if ( importTypeSymbol )
        portConstructType = *(_DWORD *)(uintptr_t)(importTypeSymbol + 12) << 16 >> 18;
      else
        portConstructType = -1;
      importNameSymbol = n[2];
      if ( importNameSymbol )
        portConstructName = *(_DWORD *)(uintptr_t)(importNameSymbol + 12) << 16 >> 18;
      else
        portConstructName = -1;
      if ( n[3] )
        portNextIndex = g_ClipsBloadPortItemCount;
      else
        portNextIndex = -1;
      Rules_BsaveWriteBlock(16, filePtr, &portModuleName);
    }
    for ( ii = *(_DWORD **)(uintptr_t)(m + 16); ii; ii = *(_DWORD **)(uintptr_t)(v15 + 12) )
    {
      ++g_ClipsBloadPortItemCount;
      if ( *ii )
        portModuleName = *(_DWORD *)(uintptr_t)(*ii + 12) << 16 >> 18;
      else
        portModuleName = -1;
      exportTypeSymbol = ii[1];
      if ( exportTypeSymbol )
        portConstructType = *(_DWORD *)(uintptr_t)(exportTypeSymbol + 12) << 16 >> 18;
      else
        portConstructType = -1;
      exportNameSymbol = ii[2];
      if ( exportNameSymbol )
        portConstructName = *(_DWORD *)(uintptr_t)(exportNameSymbol + 12) << 16 >> 18;
      else
        portConstructName = -1;
      if ( ii[3] )
        portNextIndex = g_ClipsBloadPortItemCount;
      else
        portNextIndex = -1;
      Rules_BsaveWriteBlock(16, filePtr, &portModuleName);
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_ClipsBsaveModuleCount);
    return Rules_ConstructQueuePop(&g_ClipsBloadPortItemCount);
  }
  return result;
}
// 4DAF59: variable 'v2' is possibly undefined
// 4DAFD7: variable 'v6' is possibly undefined
// 4DB063: variable 'v11' is possibly undefined
// 4DB0D0: variable 'v15' is possibly undefined
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;

//----- (004DB200) --------------------------------------------------------
int __fastcall Module_BloadReadHeaderCounts(int a1)
{
  int result; // eax
  _DWORD space[3]; // [esp+0h] [ebp-Ch] BYREF

  space[2] = a1;
  Rules_BloadReadBlock((uintptr_t)space, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveModuleCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_ClipsBloadPortItemCount, 4u);
  if ( g_ClipsBsaveModuleCount )
  {
    space[0] = 32 * g_ClipsBsaveModuleCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(32 * g_ClipsBsaveModuleCount));
    g_ClipsModuleArrayBase = result;
    if ( g_ClipsBloadPortItemCount )
    {
      space[0] = 16 * g_ClipsBloadPortItemCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(16 * g_ClipsBloadPortItemCount));
      g_Defmodule_PortItemArrayPtr = result;
    }
    else
    {
      g_Defmodule_PortItemArrayPtr = 0;
    }
  }
  else
  {
    g_ClipsModuleArrayBase = 0;
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;

//----- (004DB290) --------------------------------------------------------
int Module_BloadRefreshModules(void)
{
  int result; // eax
  int Enum; // eax
  int space; // [esp-8h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&space, 4u);
  if ( g_ClipsBsaveModuleCount )
  {
    Rules_BloadAndRefresh(g_ClipsBsaveModuleCount, 20, (void (__fastcall *)(signed int, signed int))Module_BloadFixupModuleRecord);
    Rules_BloadAndRefresh(g_ClipsBloadPortItemCount, 16, (void (__fastcall *)(signed int, signed int))Module_BloadFixupPortItemRecord);
    Module_SetModuleListHead(g_ClipsModuleArrayBase);
    Enum = Module_NextEnum(0);
    return Module_SetCurrent(Enum);
  }
  return result;
}
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C704: using guessed type int dword_51C704;

//----- (004DB300) --------------------------------------------------------
int  Module_BloadFixupModuleRecord(_DWORD *bsaveModule, int moduleIndex)
{
  int module_offset; // edx
  int module; // ebx
  int parent_index; // edi
  int constraint; // edx
  int constraint_index; // ebx
  int constraint_offset; // ecx
  int value; // eax
  int import_index; // edx
  int export_index; // ecx
  int result; // eax

  module_offset = 32 * moduleIndex;
  module = g_ClipsModuleArrayBase + module_offset;
  *(_DWORD *)(uintptr_t)module = *(_DWORD *)(uintptr_t)(4 * *bsaveModule + g_ClipsBloadSymbolPointerArray);
  ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)module + 4);
  parent_index = bsaveModule[3];
  if ( parent_index == -1 )
    *(_DWORD *)(uintptr_t)(module + 28) = 0;
  else
    *(_DWORD *)(uintptr_t)(module + 28) = g_ClipsModuleArrayBase + 32 * parent_index;
  *(_DWORD *)(uintptr_t)(module + 8) = Mem_SmallBlockAlloc(4 * Module_GetItemCount());
  constraint = Module_GetItemList();
  constraint_index = 0;
  constraint_offset = 0;
  while ( constraint_index < Module_GetItemCount() && constraint )
  {
    if ( *(_DWORD *)(uintptr_t)(constraint + 16) )
      value = ((int (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(constraint + 16))(moduleIndex);
    else
      value = 0;
    *(_DWORD *)(uintptr_t)(constraint_offset + *(_DWORD *)(uintptr_t)(module + 8)) = value;
    constraint_offset += 4;
    ++constraint_index;
    constraint = *(_DWORD *)(uintptr_t)(constraint + 28);
  }
  *(_DWORD *)(uintptr_t)(module + 4) = 0;
  import_index = bsaveModule[1];
  if ( import_index == -1 )
    *(_DWORD *)(uintptr_t)(module + 12) = 0;
  else
    *(_DWORD *)(uintptr_t)(module + 12) = 16 * import_index + g_Defmodule_PortItemArrayPtr;
  export_index = bsaveModule[2];
  if ( export_index == -1 )
    *(_DWORD *)(uintptr_t)(module + 16) = 0;
  else
    *(_DWORD *)(uintptr_t)(module + 16) = 16 * export_index + g_Defmodule_PortItemArrayPtr;
  result = bsaveModule[4];
  *(_DWORD *)(uintptr_t)(module + 24) = result;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;
// 54E674: using guessed type int dword_54E674;

//----- (004DB470) --------------------------------------------------------
int  Module_BloadFixupPortItemRecord(_DWORD *bsavePortItem, int portItemIndex)
{
  int constructTypeIndex; // ebp
  int portOffset; // ecx
  int itemNameIndex; // esi
  int v5; // ecx
  int nextIndex; // ebp
  int v7; // edx
  int result; // eax

  if ( *bsavePortItem == -1 )
  {
    *(_DWORD *)(uintptr_t)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) = *(_DWORD *)(uintptr_t)(4 * *bsavePortItem + g_ClipsBloadSymbolPointerArray);
    ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Defmodule_PortItemArrayPtr + 16 * portItemIndex) + 4);
  }
  constructTypeIndex = bsavePortItem[1];
  portOffset = 16 * portItemIndex;
  if ( constructTypeIndex == -1 )
  {
    *(_DWORD *)(uintptr_t)(portOffset + g_Defmodule_PortItemArrayPtr + 4) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(portOffset + g_Defmodule_PortItemArrayPtr + 4) = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * constructTypeIndex);
    ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(portOffset + g_Defmodule_PortItemArrayPtr + 4) + 4);
  }
  itemNameIndex = bsavePortItem[2];
  v5 = 16 * portItemIndex;
  if ( itemNameIndex == -1 )
  {
    *(_DWORD *)(uintptr_t)(v5 + g_Defmodule_PortItemArrayPtr + 8) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(g_Defmodule_PortItemArrayPtr + v5 + 8) = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * itemNameIndex);
    ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + g_Defmodule_PortItemArrayPtr + 8) + 4);
  }
  nextIndex = bsavePortItem[3];
  v7 = 16 * portItemIndex;
  result = g_Defmodule_PortItemArrayPtr;
  if ( nextIndex == -1 )
    *(_DWORD *)(uintptr_t)(v7 + g_Defmodule_PortItemArrayPtr + 12) = 0;
  else
    *(_DWORD *)(uintptr_t)(v7 + g_Defmodule_PortItemArrayPtr + 12) = g_Defmodule_PortItemArrayPtr + 16 * nextIndex;
  return result;
}
// 51C700: using guessed type int dword_51C700;
// 54E674: using guessed type int dword_54E674;

//----- (004DB590) --------------------------------------------------------
int Module_ClearBloadData(void)
{
  int moduleIndex; // ebx
  int moduleOffset; // ecx
  int v2; // ecx
  int *i; // edx
  int importConstructType; // eax
  int *j; // edx
  int exportConstructType; // eax
  int itemCount; // eax
  int v8; // ecx
  int v9; // ecx
  int result; // eax

  moduleIndex = 0;
  if ( g_ClipsBsaveModuleCount > 0 )
  {
    moduleOffset = 0;
    do
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(moduleOffset + g_ClipsModuleArrayBase), moduleOffset);
      for ( i = *(int **)(uintptr_t)(v2 + g_ClipsModuleArrayBase + 12); i; i = (int *)(uintptr_t)i[3] )
      {
        if ( *i )
          Rules_DecrementSymbolCount(*i, v2);
        importConstructType = i[1];
        if ( importConstructType )
          Rules_DecrementSymbolCount(importConstructType, v2);
        if ( i[2] )
          Rules_DecrementSymbolCount(i[2], v2);
      }
      for ( j = *(int **)(uintptr_t)(v2 + g_ClipsModuleArrayBase + 16); j; j = (int *)(uintptr_t)j[3] )
      {
        if ( *j )
          Rules_DecrementSymbolCount(*j, v2);
        exportConstructType = j[1];
        if ( exportConstructType )
          Rules_DecrementSymbolCount(exportConstructType, v2);
        if ( j[2] )
          Rules_DecrementSymbolCount(j[2], v2);
      }
      itemCount = Module_GetItemCount();
      ++moduleIndex;
      Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)(v8 + g_ClipsModuleArrayBase + 8), 4 * itemCount);
      moduleOffset = v9 + 32;
    }
    while ( moduleIndex < g_ClipsBsaveModuleCount );
  }
  if ( 32 * g_ClipsBsaveModuleCount )
    Mem_ReleasePoolBlock(g_ClipsModuleArrayBase, 32 * g_ClipsBsaveModuleCount);
  if ( 16 * g_ClipsBloadPortItemCount )
    Mem_ReleasePoolBlock(g_Defmodule_PortItemArrayPtr, 16 * g_ClipsBloadPortItemCount);
  Module_SetModuleListHead(0);
  result = Module_CreateMainModule();
  g_Module_MainRedefinable = 1;
  return result;
}
// 4DB5BD: variable 'v2' is possibly undefined
// 4DB5D2: variable 'i' is possibly undefined
// 4DB60D: variable 'j' is possibly undefined
// 4DB63F: variable 'v8' is possibly undefined
// 4DB64F: variable 'v9' is possibly undefined
// 51A9C4: using guessed type int dword_51A9C4;
// 51C6F8: using guessed type int dword_51C6F8;
// 51C6FC: using guessed type int dword_51C6FC;
// 51C700: using guessed type int dword_51C700;
// 51C704: using guessed type int dword_51C704;

//----- (004DB6B0) --------------------------------------------------------
signed int  Rules_CheckConstraintParseConflicts(int constraints, __int16 *theExp)
{
  _WORD *maxValue; // edx
  int v5; // ecx

  if ( (*(_DWORD *)(uintptr_t)constraints & 1) == 1 )
    goto LABEL_2;
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 4) != 0 && (*(_BYTE *)(uintptr_t)constraints & 2) == 0 )
  {
    Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aAllowedSymbols);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 8) != 0 && (*(_BYTE *)(uintptr_t)constraints & 4) == 0 )
  {
    Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aAllowedStrings);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 0x20) != 0 && (*(_BYTE *)(uintptr_t)constraints & 0x10) == 0 )
  {
    Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aAllowedInteger);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 0x10) != 0 && (*(_BYTE *)(uintptr_t)constraints & 8) == 0 )
  {
    Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aAllowedFloatsN);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 0x40) != 0 && (*(_BYTE *)(uintptr_t)constraints & 0x20) == 0 )
  {
    Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aAllowedInstanc);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraints + 1) & 2) != 0 && (theExp = *(__int16 **)(uintptr_t)(constraints + 6)) != 0 )
  {
    while ( !Rules_CheckValueAgainstConstraint(*theExp, *(_DWORD *)(theExp + 1), constraints) )
    {
      theExp = *(__int16 **)(uintptr_t)(v5 + 10);
      if ( !theExp )
        goto LABEL_2;
    }
    Rules_ReportAttributeConflict(v5, (int)(intptr_t)aAllowedValues);
    return 0;
  }
  else
  {
LABEL_2:
    maxValue = *(_WORD **)(uintptr_t)(constraints + 14);
    if ( (!maxValue
       || (*(_BYTE *)(uintptr_t)constraints & 1) != 0
       || (*maxValue != 1 || (*(_BYTE *)(uintptr_t)constraints & 0x10) != 0) && (**(_WORD **)(uintptr_t)(constraints + 14) || (*(_BYTE *)(uintptr_t)constraints & 8) != 0))
      && (!*(_DWORD *)(uintptr_t)(constraints + 10)
       || (*(_BYTE *)(uintptr_t)constraints & 1) != 0
       || (**(_WORD **)(uintptr_t)(constraints + 10) != 1 || (*(_BYTE *)(uintptr_t)constraints & 0x10) != 0)
       && (**(_WORD **)(uintptr_t)(constraints + 10) || (*(_BYTE *)(uintptr_t)constraints & 8) != 0)) )
    {
      return 1;
    }
    else
    {
      Rules_ReportAttributeConflict((int)(intptr_t)theExp, (int)(intptr_t)aRange_0);
      return 0;
    }
  }
}
// 4DB7A1: variable 'v5' is possibly undefined

//----- (004DB850) --------------------------------------------------------
signed int __fastcall Rules_ReportAttributeConflict(int attribute1, int attribute2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aCstrnpsr, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThe_2, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAttributeConfl, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], attribute2, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAttribute_, v7);
}
// 4DB872: variable 'v3' is possibly undefined
// 4DB87E: variable 'v4' is possibly undefined
// 4DB88D: variable 'v5' is possibly undefined
// 4DB899: variable 'v6' is possibly undefined
// 4DB8A8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DB8C0) --------------------------------------------------------
_WORD * Rules_ResetConstraintParsedFlags(_WORD *result)
{
  *result &= 0xF800u;
  return result;
}

//----- (004DB8D0) --------------------------------------------------------
BOOL  Rules_IsConstraintAttributeKeyword(int constraintName)
{
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  return !strcmp_(constraintName, aType_0)
      || !strcmp_(v1, aRange_0)
      || !strcmp_(v3, aCardinality)
      || !strcmp_(v4, aAllowedSymbols)
      || !strcmp_(v5, aAllowedStrings)
      || !strcmp_(v6, aAllowedLexemes)
      || !strcmp_(v7, aAllowedInteg_0)
      || !strcmp_(v8, aAllowedFloats)
      || !strcmp_(v9, aAllowedNumbers)
      || !strcmp_(v10, aAllowedInstanc)
      || !strcmp_(v11, aAllowedValues);
}
// 4DB8F1: variable 'v1' is possibly undefined
// 4DB901: variable 'v3' is possibly undefined
// 4DB911: variable 'v4' is possibly undefined
// 4DB921: variable 'v5' is possibly undefined
// 4DB931: variable 'v6' is possibly undefined
// 4DB941: variable 'v7' is possibly undefined
// 4DB951: variable 'v8' is possibly undefined
// 4DB961: variable 'v9' is possibly undefined
// 4DB975: variable 'v10' is possibly undefined
// 4DB989: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
