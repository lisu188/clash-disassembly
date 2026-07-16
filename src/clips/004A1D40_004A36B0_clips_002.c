/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004A1D40) --------------------------------------------------------
int  Rules_ParsePrognMultifieldForm(int top, int infile)
{
  int v4; // edx
  int v5; // ecx
  int fieldVar; // esi
  int parsedArg; // eax
  unsigned int *v8; // edx
  int argList; // edx
  int argListNext; // ecx
  int tmp; // eax
  int newBindList; // ecx
  int prev; // eax
  int fnCallExpr; // eax
  int v16; // ecx
  int parsedExpr; // eax
  int v18; // edx
  int v19; // ecx
  int tkn; // [esp+0h] [ebp-28h] BYREF
  int tknValue; // [esp+4h] [ebp-24h]
  char *tknPrintForm; // [esp+8h] [ebp-20h]
  int oldBindList; // [esp+Ch] [ebp-1Ch]
  int savedBindList; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_5070CC);
  Parser_NextToken(infile, v4);
  fieldVar = 0;
  if ( tkn != 100 )
  {
    parsedArg = Parser_ParseSingleExpression(infile, (__int16 *)&tkn, v5);
    *(_DWORD *)(uintptr_t)(top + 6) = parsedArg;
    if ( parsedArg )
      goto LABEL_3;
LABEL_17:
    AST_Free(top);
    return 0;
  }
  Parser_NextToken(infile, (int)(intptr_t)&tkn);
  if ( tkn != 15 )
  {
    if ( tkn != 2 )
      goto LABEL_25;
    fnCallExpr = Parser_ParseFunctionCallExpr(infile, *(_BYTE **)(uintptr_t)(tknValue + 16));
    *(_DWORD *)(uintptr_t)(top + 6) = fnCallExpr;
    if ( fnCallExpr )
      goto LABEL_3;
    goto LABEL_17;
  }
  fieldVar = tknValue;
  IO_OutWriteToken(asc_5070CC);
  parsedExpr = Parser_ParseSingleExpression(infile, 0, v16);
  *(_DWORD *)(uintptr_t)(top + 6) = parsedExpr;
  if ( !parsedExpr )
    goto LABEL_17;
  Parser_NextToken(infile, (int)(intptr_t)&tkn);
  if ( tkn != 101 )
    goto LABEL_25;
  IO_OutNewline();
  IO_OutWriteToken(tknPrintForm);
  IO_OutWriteToken(asc_5070CC);
LABEL_3:
  if ( Rules_ExpressionConstraintsCompatible(*(__int16 **)(uintptr_t)(top + 6)) )
  {
LABEL_25:
    Parser_ReportSyntaxError();
    AST_Free(top);
    return 0;
  }
  oldBindList = Parser_GetLoopContextStack();
  savedBindList = oldBindList;
  Parser_SetLoopContextStack(0);
  Rules_IncrementIndentDepth(3);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)(uintptr_t)g_ClipsParseContextSaveStack;
  AST_Append(0, (int)(intptr_t)&tkn);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(top + 6) + 10) = Parser_ParseProgram(infile, v8, 1);
  Rules_DecrementIndentDepth(3);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(tknPrintForm);
  argList = *(_DWORD *)(uintptr_t)(top + 6);
  argListNext = *(_DWORD *)(uintptr_t)(argList + 10);
  if ( argListNext )
  {
    tmp = *(_DWORD *)(uintptr_t)(argList + 10);
    *(_DWORD *)(uintptr_t)(argList + 10) = *(_DWORD *)(uintptr_t)(argListNext + 6);
    *(_DWORD *)(uintptr_t)(tmp + 6) = 0;
    AST_Free(tmp);
    newBindList = Parser_GetLoopContextStack();
    prev = 0;
    if ( newBindList )
    {
      while ( !fieldVar || strcmp_(newBindList, *(_DWORD *)(uintptr_t)(fieldVar + 16)) )
      {
        prev = newBindList;
        newBindList = *(_DWORD *)(uintptr_t)(newBindList + 8);
        if ( !newBindList )
          goto LABEL_8;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(savedBindList);
      Rules_PrintErrorID((int)(intptr_t)aMultifun, v18, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotRebindFi, v19);
      AST_Free(top);
      return 0;
    }
    else
    {
LABEL_8:
      if ( prev )
        *(_DWORD *)(uintptr_t)(prev + 8) = savedBindList;
      else
        Parser_SetLoopContextStack(savedBindList);
      if ( fieldVar )
        Rules_RewritePrognFieldRefs(fieldVar, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(top + 6) + 10), 0);
      return top;
    }
  }
  else
  {
    Parser_SetLoopContextStack(oldBindList);
    AST_Free(top);
    return 0;
  }
}
// 4A1D5A: variable 'v4' is possibly undefined
// 4A1D71: variable 'v5' is possibly undefined
// 4A1DDA: variable 'v8' is possibly undefined
// 4A1E3B: variable 'v12' is possibly undefined
// 4A1EDC: variable 'v16' is possibly undefined
// 4A1F6A: variable 'v18' is possibly undefined
// 4A1F79: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004A1FC0) --------------------------------------------------------
int  Rules_RewritePrognFieldRefs(int fieldVar, int theExp, signed int depth)
{
  int currentExp; // esi
  const char *fieldVarName; // edi
  int result; // eax
  unsigned int flen; // ecx
  signed int nextDepth; // edi
  int fieldVarArg; // eax
  signed int childDepth; // ebx
  int *fieldDepthConstant; // eax
  int *indexDepthConstant; // eax

  currentExp = theExp;
  fieldVarName = *(const char **)(uintptr_t)(fieldVar + 16);
  result = 0;
  flen = strlen(fieldVarName);
  if ( theExp )
  {
    nextDepth = depth + 1;
    while ( *(_WORD *)(uintptr_t)currentExp == 15 )
    {
      result = strncmp_(flen, *(_DWORD *)(uintptr_t)(fieldVar + 16)) == 0;
      if ( !result )
        break;
      if ( *(_BYTE *)(uintptr_t)(flen + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(currentExp + 2) + 16)) )
      {
        result = strcmp_(flen, aIndex);
        if ( result )
        {
LABEL_9:
          currentExp = *(_DWORD *)(uintptr_t)(currentExp + 10);
          if ( !currentExp )
            return result;
        }
        else
        {
          *(_WORD *)(uintptr_t)currentExp = 10;
          *(_DWORD *)(uintptr_t)(currentExp + 2) = Rules_MakeSymbol(aGetPrognIndex);
          indexDepthConstant = Rules_AddIntegerValue(depth);
          result = AST_NewNode(1, (int)(intptr_t)indexDepthConstant);
          *(_DWORD *)(uintptr_t)(currentExp + 6) = result;
          currentExp = *(_DWORD *)(uintptr_t)(currentExp + 10);
          if ( !currentExp )
            return result;
        }
      }
      else
      {
        *(_WORD *)(uintptr_t)currentExp = 10;
        *(_DWORD *)(uintptr_t)(currentExp + 2) = Rules_MakeSymbol(aGetPrognField);
        fieldDepthConstant = Rules_AddIntegerValue(depth);
        result = AST_NewNode(1, (int)(intptr_t)fieldDepthConstant);
        *(_DWORD *)(uintptr_t)(currentExp + 6) = result;
        currentExp = *(_DWORD *)(uintptr_t)(currentExp + 10);
        if ( !currentExp )
          return result;
      }
    }
    if ( *(_DWORD *)(uintptr_t)(currentExp + 6) )
    {
      if ( *(_WORD *)(uintptr_t)currentExp == 10 && Rules_MakeSymbol(aProgn_0) == *(int ***)(uintptr_t)(currentExp + 2) )
      {
        fieldVarArg = fieldVar;
        childDepth = nextDepth;
      }
      else
      {
        fieldVarArg = fieldVar;
        childDepth = depth;
      }
      result = Rules_RewritePrognFieldRefs(fieldVarArg, *(_DWORD *)(uintptr_t)(currentExp + 6), childDepth);
    }
    goto LABEL_9;
  }
  return result;
}
// 4A2035: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004A20F0) --------------------------------------------------------
int  Rules_EvalPrognMultifieldBuiltin(_DWORD *returnValue, double a2)
{
  _DWORD *freeListNode; // edx
  _DWORD *tmpField; // edi
  _DWORD *tmpFieldPtr; // ebp
  int fieldIndex; // ebx
  int fieldOffset; // edi
  __int16 *theExp; // ecx
  int exprNode; // ecx
  int result; // eax
  int argval; // [esp+0h] [ebp-34h] BYREF
  int argvalValue; // [esp+8h] [ebp-2Ch]
  int argvalBegin; // [esp+Ch] [ebp-28h]
  int argvalEnd; // [esp+10h] [ebp-24h]
  int endIndex; // [esp+18h] [ebp-1Ch]

  freeListNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 64);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListNode;
    tmpField = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    tmpField = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *tmpField = 2;
  tmpField[1] = g_ClipsFalseSymbol;
  tmpField[3] = g_PrognFieldBindingStack;
  g_PrognFieldBindingStack = (int)(intptr_t)tmpField;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  tmpFieldPtr = tmpField;
  if ( Lexer_ParseValueList(1, &argval, 4, a2) )
  {
    fieldIndex = argvalBegin + 1;
    endIndex = argvalEnd + 1;
    if ( argvalBegin + 1 > argvalEnd + 1 )
    {
LABEL_18:
      g_ClipsBreakFlag = 0;
    }
    else
    {
      fieldOffset = 6 * fieldIndex - 6;
      while ( 1 )
      {
        *tmpFieldPtr = *(__int16 *)(uintptr_t)(argvalValue + fieldOffset + 14);
        tmpFieldPtr[1] = *(_DWORD *)(uintptr_t)(argvalValue + fieldOffset + 16);
        tmpFieldPtr[2] = fieldIndex;
        theExp = *(__int16 **)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
        if ( theExp )
          break;
LABEL_17:
        ++fieldIndex;
        fieldOffset += 6;
        if ( fieldIndex > endIndex )
          goto LABEL_18;
      }
      while ( 1 )
      {
        Parser_ParseForm(theExp, returnValue, (int)(intptr_t)theExp, a2);
        if ( g_ClipsHaltExecution || g_ClipsBreakFlag || g_ClipsHaltExecutionFlag )
          break;
        theExp = *(__int16 **)(uintptr_t)(exprNode + 10);
        if ( !theExp )
          goto LABEL_17;
      }
      g_ClipsBreakFlag = 0;
      if ( g_ClipsHaltExecution )
      {
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
      }
    }
    g_PrognFieldBindingStack = tmpFieldPtr[3];
    g_ClipsMemFreeListTemp = (int)(intptr_t)tmpFieldPtr;
    *tmpFieldPtr = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  }
  else
  {
    g_PrognFieldBindingStack = tmpField[3];
    g_ClipsMemFreeListTemp = (int)(intptr_t)tmpField;
    *tmpField = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  }
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 4A2266: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A968: using guessed type int dword_51A968;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 51ACD8: using guessed type int dword_51ACD8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A2290) --------------------------------------------------------
int  Rules_EvalGetPrognFieldBuiltin(int returnValue)
{
  int depth; // eax
  _DWORD *i; // edx
  int result; // eax

  depth = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = (_DWORD *)(uintptr_t)g_PrognFieldBindingStack; depth > 0; i = (_DWORD *)(uintptr_t)i[3] )
    --depth;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = *i;
  result = i[1];
  *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A22D0) --------------------------------------------------------
int Rules_EvalGetPrognIndexBuiltin(void)
{
  int depth; // eax
  int i; // edx

  depth = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = g_PrognFieldBindingStack; depth > 0; i = *(_DWORD *)(uintptr_t)(i + 12) )
    --depth;
  return *(_DWORD *)(uintptr_t)(i + 8);
}
// 4A22D0: using guessed type int sub_4A22D0();
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A2310) --------------------------------------------------------
signed int  Rules_MultifieldReplaceRange(
        _DWORD *dst,
        _DWORD *src,
        int rangeEnd,
        int rangeBegin,
        _DWORD *field,
        int functionName CLASH95_UNUSED)
{
  int srcLength; // eax
  int srcBegin; // ecx
  int absBegin; // ebp
  int replaceCount; // ecx
  int combinedLength; // eax
  int dstByteOffset; // ebx
  int v14; // edx
  int srcIndex; // edx
  int dstIndex; // eax
  int srcByteOffset; // ecx
  int srcMultifield; // eax
  int dstMultifield; // ebp
  __int16 fieldType; // di
  int dstFieldPtr; // ebx
  int fieldIndex; // ecx
  int fieldByteOffset; // ebx
  int tailSrcByteOffset; // ecx
  int tailDstByteOffset; // edx
  int srcFieldsBase; // ebp
  int dstFieldsBase; // ebx
  int dstWritePtr; // [esp+0h] [ebp-34h]
  int srcReadPtr; // [esp+4h] [ebp-30h]
  int dstLength; // [esp+Ch] [ebp-28h]
  int absBeginByteOffset; // [esp+14h] [ebp-20h]
  int absEnd; // [esp+18h] [ebp-1Ch]
  int nextDstIndex; // [esp+1Ch] [ebp-18h]
  int dstFieldByteOffset; // [esp+24h] [ebp-10h]

  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  if ( rangeBegin > rangeEnd || rangeBegin < 1 || rangeEnd < 1 || rangeBegin > srcLength || srcLength < rangeEnd )
  {
    Rules_MultifieldIndexRangeError(rangeBegin, rangeEnd, srcLength);
    return 0;
  }
  else
  {
    srcBegin = src[3];
    absBegin = srcBegin + rangeBegin - 1;
    absEnd = srcBegin + rangeEnd - 1;
    replaceCount = rangeEnd - rangeBegin + 1;
    if ( field[1] == 4 )
      combinedLength = field[4] - field[3] + 1 + srcLength;
    else
      combinedLength = srcLength + 1;
    dstLength = combinedLength - replaceCount;
    dst[1] = 4;
    dst[3] = 0;
    dstByteOffset = 0;
    dst[2] = Rules_CreateEphemeralMultifield(combinedLength - replaceCount);
    dst[4] = dstLength - 1;
    srcIndex = *(_DWORD *)(uintptr_t)(v14 + 12);
    absBeginByteOffset = 6 * absBegin;
    dstIndex = 0;
    srcByteOffset = 6 * srcIndex;
    while ( 1 )
    {
      nextDstIndex = dstIndex + 1;
      if ( srcByteOffset >= absBeginByteOffset )
        break;
      srcMultifield = src[2];
      dstMultifield = dst[2];
      fieldType = *(_WORD *)(uintptr_t)(srcByteOffset + srcMultifield + 14);
      srcByteOffset += 6;
      *(_WORD *)(uintptr_t)(dstByteOffset + dstMultifield + 14) = fieldType;
      dstByteOffset += 6;
      ++srcIndex;
      *(_DWORD *)(uintptr_t)(dstByteOffset + dstMultifield + 10) = *(_DWORD *)(uintptr_t)(srcByteOffset + srcMultifield + 10);
      dstIndex = nextDstIndex;
    }
    if ( field[1] == 4 )
    {
      fieldIndex = field[3];
      if ( fieldIndex <= field[4] )
      {
        fieldByteOffset = 6 * fieldIndex;
        dstFieldByteOffset = 6 * dstIndex;
        do
        {
          dstWritePtr = dst[2] + 14 + dstFieldByteOffset;
          srcReadPtr = fieldByteOffset + field[2] + 14;
          *(_WORD *)(uintptr_t)dstWritePtr = *(_WORD *)(uintptr_t)srcReadPtr;
          *(_DWORD *)(uintptr_t)(dstWritePtr + 2) = *(_DWORD *)(uintptr_t)(srcReadPtr + 2);
          dstFieldByteOffset += 6;
          ++fieldIndex;
          ++dstIndex;
          fieldByteOffset += 6;
        }
        while ( fieldIndex <= field[4] );
      }
    }
    else
    {
      dstFieldPtr = dst[2] + 14 + dstByteOffset;
      *(_WORD *)(uintptr_t)dstFieldPtr = *((_WORD *)field + 2);
      ++dstIndex;
      *(_DWORD *)(uintptr_t)(dstFieldPtr + 2) = field[2];
    }
    while ( srcIndex < absEnd )
      ++srcIndex;
    if ( dstIndex < dstLength )
    {
      tailSrcByteOffset = 6 * (srcIndex + 1);
      tailDstByteOffset = 6 * dstIndex;
      do
      {
        srcFieldsBase = src[2];
        dstFieldsBase = dst[2];
        *(_WORD *)(uintptr_t)(tailDstByteOffset + dstFieldsBase + 14) = *(_WORD *)(uintptr_t)(tailSrcByteOffset + srcFieldsBase + 14);
        tailDstByteOffset += 6;
        ++dstIndex;
        *(_DWORD *)(uintptr_t)(tailDstByteOffset + dstFieldsBase + 10) = *(_DWORD *)(uintptr_t)(tailSrcByteOffset + srcFieldsBase + 16);
        tailSrcByteOffset += 6;
      }
      while ( tailDstByteOffset < 6 * dstLength );
    }
    return 1;
  }
}
// 4A23D8: variable 'v14' is possibly undefined

//----- (004A2580) --------------------------------------------------------
signed int  Rules_MultifieldInsertRange(_DWORD *dst, _DWORD *src, _DWORD *theField, int theIndex, int functionName CLASH95_UNUSED)
{
  int srcLength; // eax
  int srcLengthCopy; // edx
  int maxInsertPos; // eax
  int dstMultifield; // eax
  signed int dstLength; // edx
  int v14; // edx
  int insertOffset; // ebp
  int srcIndex; // edx
  int dstIndex; // eax
  int srcByteOffset; // ecx
  int dstFieldPtr; // ebp
  int insertFieldPtr; // ecx
  int tailSrcByteOffset; // ecx
  int tailDstFieldPtr; // ebp
  int fieldIndex; // ecx
  int fieldCopyDstPtr; // ebp
  int srcReadPtr; // [esp+4h] [ebp-2Ch]
  int v26; // [esp+4h] [ebp-2Ch]
  int fieldReadPtr; // [esp+4h] [ebp-2Ch]
  int insertPos; // [esp+8h] [ebp-28h]
  int insertSlot; // [esp+8h] [ebp-28h]
  int insertByteOffsetEnd; // [esp+Ch] [ebp-24h]
  int fieldByteOffset; // [esp+14h] [ebp-1Ch]
  int fieldCopyDstByteOffset; // [esp+18h] [ebp-18h]
  int tailDstByteOffset; // [esp+1Ch] [ebp-14h]
  int headDstByteOffset; // [esp+20h] [ebp-10h]

  insertPos = theIndex;
  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  srcLengthCopy = srcLength;
  maxInsertPos = srcLength + 1;
  if ( theIndex < 1 )
  {
    Rules_MultifieldIndexRangeError(theIndex, theIndex, maxInsertPos);
    return 0;
  }
  else
  {
    if ( maxInsertPos < theIndex )
      insertPos = maxInsertPos;
    dst[1] = 4;
    dst[3] = 0;
    if ( src )
    {
      if ( theField[1] == 4 )
        dstLength = theField[4] - theField[3] + 1 + srcLengthCopy;
      else
        dstLength = srcLengthCopy + 1;
      dst[2] = Rules_CreateEphemeralMultifield(dstLength);
      insertOffset = insertPos - 1;
      dst[4] = v14 - 1;
      insertSlot = insertOffset;
      srcIndex = src[3];
      dstIndex = 0;
      if ( srcIndex < insertOffset )
      {
        headDstByteOffset = 0;
        srcByteOffset = 6 * srcIndex;
        insertByteOffsetEnd = 6 * insertOffset;
        do
        {
          dstFieldPtr = dst[2] + 14 + headDstByteOffset;
          srcReadPtr = srcByteOffset + src[2] + 14;
          *(_WORD *)(uintptr_t)dstFieldPtr = *(_WORD *)(uintptr_t)srcReadPtr;
          ++dstIndex;
          ++srcIndex;
          *(_DWORD *)(uintptr_t)(dstFieldPtr + 2) = *(_DWORD *)(uintptr_t)(srcReadPtr + 2);
          srcByteOffset += 6;
          headDstByteOffset += 6;
        }
        while ( srcByteOffset < insertByteOffsetEnd );
      }
      if ( theField[1] == 4 )
      {
        fieldIndex = theField[3];
        if ( fieldIndex <= theField[4] )
        {
          fieldByteOffset = 6 * fieldIndex;
          fieldCopyDstByteOffset = 6 * dstIndex;
          do
          {
            fieldReadPtr = theField[2] + 14 + fieldByteOffset;
            fieldCopyDstPtr = dst[2] + 14 + fieldCopyDstByteOffset;
            *(_WORD *)(uintptr_t)fieldCopyDstPtr = *(_WORD *)(uintptr_t)fieldReadPtr;
            *(_DWORD *)(uintptr_t)(fieldCopyDstPtr + 2) = *(_DWORD *)(uintptr_t)(fieldReadPtr + 2);
            fieldByteOffset += 6;
            ++fieldIndex;
            fieldCopyDstByteOffset += 6;
            ++dstIndex;
          }
          while ( fieldIndex <= theField[4] );
        }
      }
      else
      {
        insertFieldPtr = dst[2] + 14 + 6 * insertSlot;
        *(_WORD *)(uintptr_t)insertFieldPtr = *((_WORD *)theField + 2);
        ++dstIndex;
        *(_DWORD *)(uintptr_t)(insertFieldPtr + 2) = theField[2];
      }
      tailSrcByteOffset = 6 * srcIndex;
      tailDstByteOffset = 6 * dstIndex;
      while ( srcIndex <= src[4] )
      {
        tailDstFieldPtr = dst[2] + 14 + tailDstByteOffset;
        v26 = tailSrcByteOffset + src[2] + 14;
        *(_WORD *)(uintptr_t)tailDstFieldPtr = *(_WORD *)(uintptr_t)v26;
        ++dstIndex;
        *(_DWORD *)(uintptr_t)(tailDstFieldPtr + 2) = *(_DWORD *)(uintptr_t)(v26 + 2);
        ++srcIndex;
        tailSrcByteOffset += 6;
        tailDstByteOffset += 6;
      }
    }
    else if ( theField[1] == 4 )
    {
      Rules_AssignMultifieldRangeCopy(dst, (int)(intptr_t)theField);
      Rules_RegisterEphemeralMultifield(dst[2]);
    }
    else
    {
      dst[2] = Rules_CreateEphemeralMultifield(0);
      dst[4] = 0;
      dstMultifield = dst[2];
      *(_WORD *)(uintptr_t)(dstMultifield + 14) = *((_WORD *)theField + 2);
      *(_DWORD *)(uintptr_t)(dstMultifield + 16) = theField[2];
    }
    return 1;
  }
}
// 4A2655: variable 'v14' is possibly undefined

//----- (004A2810) --------------------------------------------------------
signed int  Rules_MultifieldIndexRangeError(int rangeBegin, int rangeEnd, int fieldCount)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int indexToPrint; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx
  int v15; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMultifun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMultifieldInde, v5);
  if ( rangeBegin == rangeEnd )
  {
    indexToPrint = rangeBegin;
  }
  else
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aRange, v6);
    Rules_PrintLongInteger(v7, rangeBegin);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__, v8);
    indexToPrint = rangeEnd;
  }
  Rules_PrintLongInteger(v6, indexToPrint);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOutOfRange1__, v10);
  Rules_PrintLongInteger(v11, fieldCount);
  if ( !v12 )
    return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__16, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction_0, v12);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v14, v14);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__16, v15);
}
// 4A2834: variable 'v5' is possibly undefined
// 4A2847: variable 'v6' is possibly undefined
// 4A2853: variable 'v7' is possibly undefined
// 4A2862: variable 'v8' is possibly undefined
// 4A287D: variable 'v10' is possibly undefined
// 4A2889: variable 'v11' is possibly undefined
// 4A2890: variable 'v12' is possibly undefined
// 4A28C4: variable 'v14' is possibly undefined
// 4A28D3: variable 'v15' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A28E0) --------------------------------------------------------
signed int  Rules_MultifieldDeleteRange(_DWORD *dst, _DWORD *src, int rangeEnd, int rangeBegin, int functionName CLASH95_UNUSED)
{
  int srcLength; // eax
  int absBegin; // edi
  signed int dstLength; // eax
  int v9; // edx
  int srcIndex; // edx
  int dstIndex; // eax
  int dstByteOffset; // ebx
  int srcByteOffset; // ecx
  int resultFlag; // edx
  _DWORD *emptyMultifield; // eax
  int tailSrcByteOffset; // ecx
  int tailDstByteOffset; // edx
  int dstFieldPtr; // ebp
  int srcMultifield; // ebx
  int fieldValue; // ebx
  int headDstFieldPtr; // [esp+0h] [ebp-24h]
  int headSrcFieldPtr; // [esp+4h] [ebp-20h]
  int absEnd; // [esp+10h] [ebp-14h]

  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  if ( rangeEnd < rangeBegin || rangeBegin < 1 || rangeEnd < 1 || srcLength < rangeBegin || srcLength < rangeEnd )
  {
    Rules_MultifieldIndexRangeError(rangeBegin, rangeEnd, srcLength);
    return 0;
  }
  dst[1] = 4;
  dst[3] = 0;
  if ( !srcLength )
  {
    emptyMultifield = Rules_CreateEphemeralMultifield(0);
    dst[4] = -1;
    resultFlag = 1;
    dst[2] = emptyMultifield;
    return resultFlag;
  }
  absBegin = rangeBegin + src[3] - 1;
  absEnd = rangeEnd + src[3] - 1;
  dstLength = srcLength - (rangeEnd + src[3] - absBegin);
  dst[4] = dstLength - 1;
  dst[2] = Rules_CreateEphemeralMultifield(dstLength);
  srcIndex = *(_DWORD *)(uintptr_t)(v9 + 12);
  dstIndex = 0;
  if ( srcIndex < absBegin )
  {
    dstByteOffset = 0;
    srcByteOffset = 6 * srcIndex;
    do
    {
      headDstFieldPtr = dstByteOffset + dst[2] + 14;
      headSrcFieldPtr = srcByteOffset + src[2] + 14;
      ++dstIndex;
      *(_WORD *)(uintptr_t)headDstFieldPtr = *(_WORD *)(uintptr_t)headSrcFieldPtr;
      ++srcIndex;
      srcByteOffset += 6;
      *(_DWORD *)(uintptr_t)(headDstFieldPtr + 2) = *(_DWORD *)(uintptr_t)(headSrcFieldPtr + 2);
      dstByteOffset += 6;
    }
    while ( srcByteOffset < 6 * absBegin );
  }
  while ( srcIndex < absEnd )
    ++srcIndex;
  if ( dstIndex <= dst[4] )
  {
    tailSrcByteOffset = 6 * (srcIndex + 1);
    tailDstByteOffset = 6 * dstIndex;
    do
    {
      dstFieldPtr = dst[2] + 14 + tailDstByteOffset;
      srcMultifield = src[2];
      *(_WORD *)(uintptr_t)dstFieldPtr = *(_WORD *)(uintptr_t)(tailSrcByteOffset + srcMultifield + 14);
      fieldValue = *(_DWORD *)(uintptr_t)(tailSrcByteOffset + srcMultifield + 16);
      tailSrcByteOffset += 6;
      *(_DWORD *)(uintptr_t)(dstFieldPtr + 2) = fieldValue;
      ++dstIndex;
      tailDstByteOffset += 6;
    }
    while ( dstIndex <= dst[4] );
  }
  return 1;
}
// 4A2988: variable 'v9' is possibly undefined

//----- (004A2AB0) --------------------------------------------------------
signed int Rules_RegisterStringBuiltins(void)
{
  Rules_RegisterHostFunction(aStrCat, 107, (int)(intptr_t)aStrcatfunction, (int)(intptr_t)Rules_StrCatBuiltin, (int)(intptr_t)a1_1);
  Rules_RegisterHostFunction(aSymCat, 107, (int)(intptr_t)aSymcatfunction, (int)(intptr_t)Rules_SymCatBuiltin, (int)(intptr_t)a1_1);
  Rules_RegisterHostFunction(aStrLength, 108, (int)(intptr_t)aStrlengthfunct, (int)(intptr_t)Rules_StrLengthBuiltin, (int)(intptr_t)a11j);
  Rules_RegisterHostFunction(aStrCompare, 108, (int)(intptr_t)aStrcomparefunc, (int)(intptr_t)Rules_StrCompareBuiltin, (int)(intptr_t)a23Jji);
  Rules_RegisterHostFunction(aUpcase, 106, (int)(intptr_t)aUpcasefunction, (int)(intptr_t)Rules_UpcaseBuiltin, (int)(intptr_t)a11j);
  Rules_RegisterHostFunction(aLowcase, 106, (int)(intptr_t)aLowcasefunctio, (int)(intptr_t)Rules_LowcaseBuiltin, (int)(intptr_t)a11j);
  Rules_RegisterHostFunction(aSubString, 115, (int)(intptr_t)aSubstringfunct, (int)(intptr_t)Rules_SubStringBuiltin, (int)(intptr_t)a33Iij);
  Rules_RegisterHostFunction(aStrIndex, 117, (int)(intptr_t)aStrindexfuncti, (int)(intptr_t)Rules_StrIndexBuiltin, (int)(intptr_t)a22j);
  Rules_RegisterHostFunction(aEval, 117, (int)(intptr_t)aEvalfunction, (int)(intptr_t)Rules_EvalBuiltin, (int)(intptr_t)a11k_1);
  return Rules_RegisterHostFunction(aBuild, 98, (int)(intptr_t)aBuildfunction, (int)(intptr_t)Rules_BuildBuiltin, (int)(intptr_t)a11k_1);
}

//----- (004A2BC0) --------------------------------------------------------
signed int  Rules_StrCatBuiltin(int returnValue, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(returnValue, 3, a2, a3);
}

//----- (004A2C00) --------------------------------------------------------
signed int  Rules_SymCatBuiltin(int returnValue, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(returnValue, 2, a2, a3);
}

//----- (004A2C40) --------------------------------------------------------
signed int  Rules_ConcatBuiltinCore(int returnValue, int returnType, int a3, double a4)
{
  signed int *v4; // eax
  int v5; // edx
  _BYTE *v6; // eax
  int argIndex; // esi
  int v8; // edx
  _BYTE *stringArrayCursor; // ebp
  char *symbolString; // eax
  int v11; // ecx
  signed int *internedSymbol; // eax
  unsigned int lengthWithNull; // kr04_4
  int writeOffset; // ebx
  int stringIndex; // ebp
  int segmentLength; // ecx
  char *theString; // esi
  int v18; // edx
  const char **readCursor; // edx
  signed int *v20; // eax
  int v21; // edx
  char *v23; // ecx
  int theArg; // [esp+0h] [ebp-40h] BYREF
  int theArgType; // [esp+4h] [ebp-3Ch]
  int theArgValue; // [esp+8h] [ebp-38h]
  const char **arrayOfStrings; // [esp+18h] [ebp-28h]
  int v28 CLASH95_UNUSED; // [esp+1Ch] [ebp-24h]
  char *functionName CLASH95_UNUSED; // [esp+20h] [ebp-20h]
  unsigned int totalSize; // [esp+24h] [ebp-1Ch]
  int numArgs; // [esp+28h] [ebp-18h]

  v28 = returnValue;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = returnType;
  if ( returnType == 3 )
  {
    v4 = Str_Intern(g_Rules_EmptyStringLiteral, (int)(intptr_t)aStrCat);
    functionName = v23;
  }
  else
  {
    functionName = aSymCat;
    v4 = Str_Intern(aNil_4, a3);
  }
  *(_DWORD *)(uintptr_t)(v5 + 8) = v4;
  numArgs = Rules_RtnArgCount();
  v6 = Mem_SmallBlockAllocZeroed(4 * numArgs);
  totalSize = 1;
  argIndex = 1;
  arrayOfStrings = (const char **)v6;
  if ( v8 < 1 )
  {
LABEL_11:
    writeOffset = 0;
    stringIndex = 0;
    theString = (char *)Mem_SmallBlockAlloc(totalSize);
    if ( v18 > 0 )
    {
      readCursor = arrayOfStrings;
      do
      {
        sprintf_(&theString[writeOffset], "%s", *readCursor);
        ++stringIndex;
        segmentLength = strlen(*(readCursor - 1));
        writeOffset += segmentLength;
      }
      while ( stringIndex < numArgs );
    }
    v20 = Str_Intern(theString, segmentLength);
    *(_DWORD *)(uintptr_t)(v21 + 8) = v20;
    Mem_SmallBlockFree(theString, totalSize);
  }
  else
  {
    stringArrayCursor = v6 + 4;
    while ( 1 )
    {
      Rules_RtnUnknown(argIndex, &theArg, a4);
      switch ( theArgType )
      {
        case 0:
          symbolString = (char *)(uintptr_t)Rules_FloatToSymbol(theArgType, *(double *)(uintptr_t)(theArgValue + 16));
          goto LABEL_7;
        case 1:
          symbolString = (char *)(uintptr_t)Rules_LongIntegerToSymbol(*(_DWORD *)(uintptr_t)(theArgValue + 16));
LABEL_7:
          internedSymbol = Str_Intern(symbolString, v11);
          goto LABEL_8;
        case 2:
        case 3:
        case 8:
          internedSymbol = (signed int *)(uintptr_t)theArgValue;
LABEL_8:
          *((_DWORD *)stringArrayCursor - 1) = internedSymbol[4];
          break;
        default:
          Parser_ReportError(argIndex, (int)(intptr_t)aStringInstance);
          Lexer_ErrorRecover(1);
          break;
      }
      if ( g_ClipsEvaluationError )
        break;
      lengthWithNull = strlen(*((const char **)stringArrayCursor - 1)) + 1;
      stringArrayCursor += 4;
      ++argIndex;
      totalSize += lengthWithNull - 1;
      if ( argIndex > numArgs )
        goto LABEL_11;
    }
  }
  return Mem_SmallBlockFree(arrayOfStrings, 4 * numArgs);
}
// 4A2C6F: variable 'v5' is possibly undefined
// 4A2C9A: variable 'v8' is possibly undefined
// 4A2CCF: variable 'v11' is possibly undefined
// 4A2D1F: variable 'v18' is possibly undefined
// 4A2D27: variable 'v19' is possibly undefined
// 4A2D66: variable 'v16' is possibly undefined
// 4A2D6B: variable 'v21' is possibly undefined
// 4A2DA9: variable 'v23' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A964: using guessed type int dword_51A964;

//----- (004A2DF0) --------------------------------------------------------
int  Rules_StrLengthBuiltin(int returnValue, double a2)
{
  int result; // eax
  _DWORD theValue[9]; // [esp-8h] [ebp-24h] BYREF

  theValue[7] = returnValue;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( Lexer_ParseValueList(1, theValue, 111, a2) )
      return strlen(*(const char **)(uintptr_t)(theValue[2] + 16));
    else
      return -1;
  }
  return result;
}

//----- (004A2E60) --------------------------------------------------------
signed int * Rules_UpcaseBuiltin(int returnValue, double a2)
{
  int v3; // ecx
  signed int slen; // kr04_4
  signed int charIndex; // ebx
  char *nsptr; // eax
  _BYTE *osptr; // edx
  char *writePtr; // ecx
  int ch; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD item[7]; // [esp+0h] [ebp-30h] BYREF
  char *newString; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, item, 111, a2) )
  {
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  else
  {
    slen = strlen(*(const char **)(uintptr_t)(item[2] + 16)) + 1;
    charIndex = 0;
    nsptr = (char *)Mem_SmallBlockAlloc(slen);
    newString = nsptr;
    if ( slen > 0 )
    {
      writePtr = nsptr;
      do
      {
        if ( IsTable[(unsigned __int8)(*osptr + 1)] >= 0 )
        {
          LOBYTE(ch) = *osptr;
        }
        else
        {
          ch = toupper_(writePtr);
          item[6] = ch;
        }
        *writePtr++ = ch;
        ++charIndex;
        ++osptr;
      }
      while ( charIndex < slen );
    }
    *(_DWORD *)(uintptr_t)(returnValue + 4) = item[1];
    *(_DWORD *)(uintptr_t)(returnValue + 8) = Str_Intern(newString, (int)(intptr_t)writePtr);
    return (signed int *)(uintptr_t)Mem_SmallBlockFree(newString, v10);
  }
  return result;
}
// 4A2ECC: variable 'v7' is possibly undefined
// 4A2EED: variable 'v8' is possibly undefined
// 4A2F0F: variable 'v10' is possibly undefined
// 4A2F2A: variable 'v3' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004A2F40) --------------------------------------------------------
signed int * Rules_LowcaseBuiltin(int returnValue, double a2)
{
  int v3; // ecx
  signed int slen; // kr04_4
  signed int charIndex; // ebx
  char *nsptr; // eax
  _BYTE *osptr; // edx
  char *writePtr; // ecx
  int ch; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD item[7]; // [esp+0h] [ebp-30h] BYREF
  char *newString; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, item, 111, a2) )
  {
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  else
  {
    slen = strlen(*(const char **)(uintptr_t)(item[2] + 16)) + 1;
    charIndex = 0;
    nsptr = (char *)Mem_SmallBlockAlloc(slen);
    newString = nsptr;
    if ( slen > 0 )
    {
      writePtr = nsptr;
      do
      {
        if ( (IsTable[(unsigned __int8)(*osptr + 1)] & 0x40) != 0 )
        {
          ch = tolower_(writePtr, osptr);
          item[6] = ch;
        }
        else
        {
          LOBYTE(ch) = *osptr;
        }
        *writePtr++ = ch;
        ++charIndex;
        ++osptr;
      }
      while ( charIndex < slen );
    }
    *(_DWORD *)(uintptr_t)(returnValue + 4) = item[1];
    *(_DWORD *)(uintptr_t)(returnValue + 8) = Str_Intern(newString, (int)(intptr_t)writePtr);
    return (signed int *)(uintptr_t)Mem_SmallBlockFree(newString, v10);
  }
  return result;
}
// 4A2FAC: variable 'v7' is possibly undefined
// 4A2FCD: variable 'v8' is possibly undefined
// 4A2FEF: variable 'v10' is possibly undefined
// 4A300A: variable 'v3' is possibly undefined
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004A3020) --------------------------------------------------------
signed int  Rules_StrCompareBuiltin(int returnValue, double a2)
{
  int numArgs; // esi
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  double maxCharsFloat; // st7
  int arg3; // [esp-4h] [ebp-5Ch] BYREF
  int arg3Type; // [esp+0h] [ebp-58h]
  int arg3Value; // [esp+4h] [ebp-54h]
  int arg1; // [esp+14h] [ebp-44h] BYREF
  int arg2; // [esp+2Ch] [ebp-2Ch] BYREF
  int arg2Value; // [esp+34h] [ebp-24h]
  int maxChars CLASH95_UNUSED; // [esp+44h] [ebp-14h]
  int v14 CLASH95_UNUSED; // [esp+50h] [ebp-8h]

  v14 = returnValue;
  numArgs = Rules_ArgRangeCheck((int)(intptr_t)aStrCompare, 3);
  if ( numArgs == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &arg1, 111, a2);
  if ( result )
  {
    result = Lexer_ParseValueList(2, &arg2, 111, a2);
    if ( result )
    {
      if ( numArgs == 3 )
      {
        result = Lexer_ParseValueList(3, &arg3, 1, a2);
        if ( !result )
          return result;
        if ( arg3Type == 1 )
        {
          maxChars = *(_DWORD *)(uintptr_t)(arg3Value + 16);
        }
        else
        {
          maxCharsFloat = *(double *)(uintptr_t)(arg3Value + 16);
          _CHP(arg3, arg3Type);
          maxChars = (int)maxCharsFloat;
        }
        result = strncmp_(v5, *(_DWORD *)(uintptr_t)(arg2Value + 16));
      }
      else
      {
        result = strcmp_(v4, *(_DWORD *)(uintptr_t)(arg2Value + 16));
      }
      if ( result < 0 )
      {
        return -1;
      }
      else if ( result > 0 )
      {
        return 1;
      }
    }
  }
  return result;
}
// 4A3097: variable 'v4' is possibly undefined
// 4A30EE: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004A3120) --------------------------------------------------------
signed int * Rules_SubStringBuiltin(double a1)
{
  int sourceLength; // ecx
  int start; // ebp
  int end; // esi
  _DWORD *tempPtr; // eax
  int charIndex; // ecx
  char *returnString; // edi
  char *sourcePtr; // edx
  char ch; // bl
  int v9; // edx
  int internedString; // ecx
  int theArgument; // [esp+0h] [ebp-38h] BYREF
  int argType; // [esp+4h] [ebp-34h]
  int argValue; // [esp+8h] [ebp-30h]
  int endRaw; // [esp+18h] [ebp-20h]
  int startRaw; // [esp+1Ch] [ebp-1Ch]

  if ( Lexer_TokenExpect(3) == -1 || !Lexer_ParseValueList(1, &theArgument, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, sourceLength);
  if ( argType == 1 )
  {
    startRaw = *(_DWORD *)(uintptr_t)(argValue + 16);
  }
  else
  {
    a1 = *(double *)(uintptr_t)(argValue + 16);
    _CHP(theArgument, argType);
    startRaw = (int)a1;
  }
  start = startRaw - 1;
  if ( !Lexer_ParseValueList(2, &theArgument, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, sourceLength);
  if ( argType == 1 )
  {
    endRaw = *(_DWORD *)(uintptr_t)(argValue + 16);
  }
  else
  {
    a1 = *(double *)(uintptr_t)(argValue + 16);
    _CHP(theArgument, argType);
    endRaw = (int)a1;
  }
  end = endRaw - 1;
  if ( !Lexer_ParseValueList(3, &theArgument, 111, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, sourceLength);
  if ( start < 0 )
    start = 0;
  sourceLength = strlen(*(const char **)(uintptr_t)(argValue + 16));
  if ( end > sourceLength )
  {
    sourceLength = strlen(*(const char **)(uintptr_t)(argValue + 16));
    end = sourceLength;
  }
  if ( start > end )
    return Str_Intern(g_Rules_EmptyStringLiteral, sourceLength);
  tempPtr = Mem_SmallBlockAlloc(end - start + 2);
  charIndex = start;
  returnString = (char *)tempPtr;
  sourcePtr = (char *)(uintptr_t)(start + *(_DWORD *)(uintptr_t)(argValue + 16));
  do
  {
    tempPtr = (_DWORD *)((char *)tempPtr + 1);
    ch = *sourcePtr++;
    ++charIndex;
    *((_BYTE *)tempPtr - 1) = ch;
  }
  while ( charIndex <= end );
  *(_BYTE *)tempPtr = 0;
  Str_Intern(returnString, charIndex);
  Mem_SmallBlockFree(returnString, v9 - start + 2);
  return (signed int *)(uintptr_t)internedString;
}
// 4A323C: variable 'v9' is possibly undefined
// 4A324A: variable 'v10' is possibly undefined
// 4A325B: variable 'v1' is possibly undefined

//----- (004A32A0) --------------------------------------------------------
int * Rules_StrIndexBuiltin(int returnValue, double a2)
{
  int *result; // eax
  const char *strg1; // ebp
  _BYTE *strg2; // esi
  signed int position; // edi
  _BYTE *strg2Ptr; // edx
  int matchLength; // ecx
  char ch; // bh
  const char *searchString; // edi
  int v11; // edx
  int v12; // edx
  int theArgument1; // [esp+0h] [ebp-4Ch] BYREF
  int arg1Value; // [esp+8h] [ebp-44h]
  int theArgument2; // [esp+18h] [ebp-34h] BYREF
  int arg2Value; // [esp+20h] [ebp-2Ch]
  int v17; // [esp+30h] [ebp-1Ch]

  v17 = returnValue;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(v17 + 8) = g_ClipsFalseSymbol;
  result = (int *)(uintptr_t)Lexer_TokenExpect(2);
  if ( result != (int *)-1 )
  {
    result = (int *)(uintptr_t)Lexer_ParseValueList(1, &theArgument1, 111, a2);
    if ( result )
    {
      result = (int *)(uintptr_t)Lexer_ParseValueList(2, &theArgument2, 111, a2);
      if ( result )
      {
        strg1 = *(const char **)(uintptr_t)(arg1Value + 16);
        strg2 = *(_BYTE **)(uintptr_t)(arg2Value + 16);
        result = 0;
        if ( strlen(strg1) )
        {
          BYTE1(result) = *strg2;
          position = 1;
          if ( *strg2 )
          {
            while ( 1 )
            {
              result = *(int **)(uintptr_t)(arg1Value + 16);
              strg2Ptr = strg2;
              matchLength = 0;
              if ( *strg1 )
              {
                do
                {
                  if ( *(_BYTE *)result != *strg2Ptr )
                    break;
                  ++strg2Ptr;
                  ch = *((_BYTE *)result + 1);
                  result = (int *)((char *)result + 1);
                  ++matchLength;
                }
                while ( ch );
              }
              if ( !strg1[matchLength] )
                break;
              ++position;
              if ( !*++strg2 )
                return result;
            }
            *(_DWORD *)(uintptr_t)(v17 + 4) = 1;
            result = Rules_AddIntegerValue(position);
            *(_DWORD *)(uintptr_t)(v12 + 8) = result;
          }
        }
        else
        {
          searchString = *(const char **)(uintptr_t)(arg2Value + 16);
          *(_DWORD *)(uintptr_t)(v17 + 4) = 1;
          result = Rules_AddIntegerValue(strlen(searchString) + 1);
          *(_DWORD *)(uintptr_t)(v11 + 8) = result;
        }
      }
    }
  }
  return result;
}
// 4A3398: variable 'v11' is possibly undefined
// 4A33BB: variable 'v12' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004A33D0) --------------------------------------------------------
int  Rules_EvalBuiltin(_DWORD *returnValue, int a2, double a3)
{
  int result; // eax
  int v6; // ecx
  _DWORD item[10]; // [esp-8h] [ebp-28h] BYREF

  item[8] = a2;
  if ( Lexer_TokenExpect(1) != -1 && Lexer_ParseValueList(1, item, 111, a3) )
    return Rules_EvalStringCore(v6, returnValue);
  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  return result;
}
// 4A3429: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004A3440) --------------------------------------------------------
BOOL __fastcall Rules_EvalStringCore(_DWORD theString CLASH95_UNUSED, _DWORD *returnValue)
{
  double v3; // st7
  const char *v4; // ecx
  BOOL result; // eax
  int ppBufferStatus; // ebx
  int oldBindList; // edi
  __int16 *v8; // edx
  int v9; // ecx
  int top; // ebp
  _WORD *v11; // ecx
  __int16 *v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE logicalNameBuffer[40]; // [esp+0h] [ebp-28h] BYREF

  v3 = sprintf_(logicalNameBuffer, "Eval-%d", ++g_EvalStringRouterCounter);
  if ( IO_OpenStringSource((int)(intptr_t)logicalNameBuffer, v4, 0) )
  {
    ppBufferStatus = Rules_GetPPBufferStatus();
    Rules_SetPPBufferStatus(0);
    oldBindList = Parser_GetLoopContextStack();
    Parser_SetLoopContextStack(0);
    top = Parser_ParseSingleExpression((int)(intptr_t)logicalNameBuffer, v8, v9);
    Rules_SetPPBufferStatus(ppBufferStatus);
    Parser_FreeLoopContextStack();
    Parser_SetLoopContextStack(oldBindList);
    if ( v11 )
    {
      if ( *v11 == 14 || *v11 == 16 )
      {
        Rules_PrintErrorID((int)(intptr_t)aMiscfun_0, 1, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpandMustBe_0, v14);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)(intptr_t)logicalNameBuffer);
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
        AST_Free(top);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else if ( AST_TreeContainsSpecialTag((int)(intptr_t)v11, 0) )
      {
        Rules_PrintErrorID((int)(intptr_t)aStrngfun, 2, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSomeVariablesC, v15);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)(intptr_t)logicalNameBuffer);
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
        AST_Free(v16);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else
      {
        Parser_ParseForm(v12, returnValue, (int)(intptr_t)v12, v3);
        --g_EvalStringRouterCounter;
        AST_Free(v13);
        IO_CloseStringRouter((int)(intptr_t)logicalNameBuffer);
        return Rules_GetHaltExecutionFlag() == 0;
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      IO_CloseStringRouter((int)(intptr_t)logicalNameBuffer);
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
      result = 0;
      --g_EvalStringRouterCounter;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    result = 0;
    --g_EvalStringRouterCounter;
  }
  return result;
}
// 4A3474: variable 'v4' is possibly undefined
// 4A34C4: variable 'v8' is possibly undefined
// 4A34C4: variable 'v9' is possibly undefined
// 4A34E2: variable 'v11' is possibly undefined
// 4A3510: variable 'v12' is possibly undefined
// 4A3524: variable 'v13' is possibly undefined
// 4A359B: variable 'v14' is possibly undefined
// 4A35FA: variable 'v15' is possibly undefined
// 4A3621: variable 'v16' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];
// 51ACDC: using guessed type int dword_51ACDC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A3650) --------------------------------------------------------
signed int  Rules_BuildBuiltin(int returnValue, double a2)
{
  signed int result; // eax
  _DWORD theArg[9]; // [esp-8h] [ebp-24h] BYREF

  theArg[7] = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, theArg, 111, a2);
  if ( result )
    return Rules_BuildConstructFromString(*(const char **)(uintptr_t)(theArg[2] + 16));
  return result;
}

//----- (004A36B0) --------------------------------------------------------
signed int  Rules_BuildConstructFromString(const char *theString)
{
  signed int result; // eax
  signed int errorFlag; // ebx
  int v3; // ecx
  int v4; // edx
  char *ppBuffer; // eax
  int v6; // ecx
  int theToken; // [esp+0h] [ebp-14h] BYREF

  if ( g_Rules_JoinOperationInProgress )
    return 0;
  result = IO_OpenStringSource((int)(intptr_t)aBuild, theString, 0);
  if ( result )
  {
    Parser_NextToken((int)(intptr_t)aBuild, (int)(intptr_t)&theToken);
    if ( theToken != 100 || (Parser_NextToken((int)(intptr_t)aBuild, (int)(intptr_t)&theToken), theToken != 2) )
    {
      IO_CloseStringRouter((int)(intptr_t)aBuild);
      return 0;
    }
    errorFlag = Rules_ParseConstruct();
    IO_CloseStringRouter((int)(intptr_t)aBuild);
    if ( v4 == 1 )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aError_3, v3);
      ppBuffer = (char *)(uintptr_t)Rules_GetPPBuffer();
      Output_WriteLongString((signed int)(intptr_t)g_IO_LogicalNameTable_WError[0], ppBuffer);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_507374, v6);
    }
    Rules_DestroyPPBuffer();
    return !errorFlag;
  }
  return result;
}
// 4A3722: variable 'v4' is possibly undefined
// 4A372F: variable 'v3' is possibly undefined
// 4A3752: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A954: using guessed type int dword_51A954;
