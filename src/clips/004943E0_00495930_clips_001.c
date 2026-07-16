/* Generated from src/recovered/rules/clips/004943E0_ast.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004943E0) --------------------------------------------------------
signed int  AST_NewNode(__int16 type, int value)
{
  __int16 nodeType; // cx
  _DWORD *freeListHead; // ebx
  signed int result; // eax

  nodeType = type;
  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 56);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListHead;
    result = g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_DWORD *)(result + 10) = 0;
  *(_DWORD *)(result + 6) = 0;
  *(_WORD *)result = nodeType;
  *(_DWORD *)(result + 2) = value;
  return result;
}
// 49440E: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00494440) --------------------------------------------------------
signed int  Rules_PrintFieldExprList(signed int result, __int16 *theExpression)
{
  int fileid; // ecx
  __int16 *exprPtr; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *printString; // edx
  int v8; // eax
  int oldExpression; // edi

  fileid = result;
  exprPtr = theExpression;
  if ( theExpression )
  {
    while ( exprPtr )
    {
      switch ( *exprPtr )
      {
        case 10:
          Output_Write(fileid, (int)asc_504DE0, fileid);
          Output_Write(v4, *(_DWORD *)(**(_DWORD **)(exprPtr + 1) + 16), v4);
          if ( *(_DWORD *)(exprPtr + 3) )
            Output_Write(v5, (int)asc_504DE4, v5);
          Rules_PrintFieldExprList(v5, *(_DWORD *)(exprPtr + 3));
          printString = asc_504DE8;
          v8 = v6;
          goto LABEL_7;
        case 13:
        case 15:
          Output_Write(fileid, (int)aQuestion_PrintSingleFieldVarPrefix, fileid);
          v8 = v6;
          printString = *(char **)(*(_DWORD *)(exprPtr + 1) + 16);
          goto LABEL_7;
        case 14:
        case 16:
          Output_Write(fileid, (int)aQuestion_PrintMultiFieldVarPrefix, fileid);
          v8 = v6;
          printString = *(char **)(*(_DWORD *)(exprPtr + 1) + 16);
LABEL_7:
          result = Output_Write(v8, (int)printString, v6);
          break;
        default:
          oldExpression = g_ClipsCurrentExpression;
          g_ClipsCurrentExpression = (int)exprPtr;
          result = Rules_PrintAtomValue(fileid, *exprPtr, *(int **)(exprPtr + 1));
          g_ClipsCurrentExpression = oldExpression;
          break;
      }
      exprPtr = *(__int16 **)(exprPtr + 5);
      if ( exprPtr )
        result = Output_Write(fileid, (int)asc_504DE4, fileid);
    }
  }
  return result;
}
// 494482: variable 'v2' is possibly undefined
// 494491: variable 'v4' is possibly undefined
// 4944A0: variable 'v5' is possibly undefined
// 4944B4: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (00494520) --------------------------------------------------------
_DWORD * AST_MergeFieldAccessNodes(_DWORD *result, _DWORD *expr2)
{
  _DWORD *expr1; // ecx
  int lastArg; // eax
  int expr2ArgList; // eax
  int expr1LastArg; // eax
  int firstArg; // ecx

  expr1 = result;
  if ( !result )
    return expr2;
  if ( expr2 )
  {
    if ( g_Clips_SymbolAnd != *(_DWORD *)((char *)result + 2) || g_Clips_SymbolAnd == *(_DWORD *)((char *)expr2 + 2) )
    {
      if ( g_Clips_SymbolAnd == *(_DWORD *)((char *)result + 2) || g_Clips_SymbolAnd != *(_DWORD *)((char *)expr2 + 2) )
      {
        if ( g_Clips_SymbolAnd == *(_DWORD *)((char *)result + 2) && g_Clips_SymbolAnd == *(_DWORD *)((char *)expr2 + 2) )
        {
          expr1LastArg = *(_DWORD *)((char *)result + 6);
          if ( expr1LastArg )
          {
            while ( *(_DWORD *)(expr1LastArg + 10) )
              expr1LastArg = *(_DWORD *)(expr1LastArg + 10);
            *(_DWORD *)(expr1LastArg + 10) = *(_DWORD *)((char *)expr2 + 6);
            g_ClipsMemFreeListTemp = (int)expr2;
            *expr2 = *(_DWORD *)(g_ClipsMemoryTable + 56);
            *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
            return expr1;
          }
          else
          {
            g_ClipsMemFreeListTemp = (int)expr1;
            *expr1 = *(_DWORD *)(g_ClipsMemoryTable + 56);
            *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
            return expr2;
          }
        }
        else
        {
          result = (_DWORD *)AST_NewNode(10, g_Clips_SymbolAnd);
          *(_DWORD *)((char *)result + 6) = firstArg;
          *(_DWORD *)(firstArg + 10) = expr2;
        }
      }
      else
      {
        expr2ArgList = *(_DWORD *)((char *)expr2 + 6);
        if ( expr2ArgList )
        {
          *(_DWORD *)((char *)expr2 + 6) = expr1;
          *(_DWORD *)((char *)expr1 + 10) = expr2ArgList;
          return expr2;
        }
        else
        {
          g_ClipsMemFreeListTemp = (int)expr2;
          *expr2 = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
          return expr1;
        }
      }
    }
    else
    {
      lastArg = *(_DWORD *)((char *)result + 6);
      if ( lastArg )
      {
        while ( *(_DWORD *)(lastArg + 10) )
          lastArg = *(_DWORD *)(lastArg + 10);
        *(_DWORD *)(lastArg + 10) = expr2;
        return expr1;
      }
      else
      {
        g_ClipsMemFreeListTemp = (int)expr1;
        *expr1 = *(_DWORD *)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
        return expr2;
      }
    }
  }
  return result;
}
// 494653: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E65C: using guessed type int dword_54E65C;

//----- (00494660) --------------------------------------------------------
int  AST_AppendNodeList(int expr1, int expr2)
{
  int listHead; // ecx

  listHead = expr1;
  if ( !expr1 )
    return expr2;
  if ( expr2 )
  {
    for ( ; *(_DWORD *)(expr1 + 10); expr1 = *(_DWORD *)(expr1 + 10) )
      ;
    *(_DWORD *)(expr1 + 10) = expr2;
  }
  return listHead;
}

//----- (00494690) --------------------------------------------------------
void Rules_FlushPPBuffer(void)
{
  if ( g_Clips_PPBuffer )
  {
    g_ClipsPPBackupOnce = 0;
    g_Rules_PPBackupTwicePos = 0;
    g_PPBufferLength = 0;
    *(_BYTE *)g_Clips_PPBuffer = 0;
  }
}
// 51AA18: using guessed type int dword_51AA18;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (004946C0) --------------------------------------------------------
signed int Rules_DestroyPPBuffer(void)
{
  signed int result; // eax

  g_ClipsPPBackupOnce = 0;
  g_Rules_PPBackupTwicePos = 0;
  g_PPBufferLength = 0;
  if ( g_Clips_PPBuffer )
    result = Mem_SmallBlockFree((_DWORD *)g_Clips_PPBuffer, g_ClipsPPBufferMax);
  g_Clips_PPBuffer = 0;
  g_ClipsPPBufferMax = 0;
  return result;
}
// 51AA18: using guessed type int dword_51AA18;
// 51AA1C: using guessed type int dword_51AA1C;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (00494720) --------------------------------------------------------
char * Rules_SavePPBuffer(char *result)
{
  const char *str; // esi

  str = result;
  if ( g_Rules_PPBufferEnabled )
  {
    strlen(result);
    if ( (int)(strlen(result) + 1 + g_PPBufferLength) >= g_ClipsPPBufferMax )
    {
      g_Clips_PPBuffer = (int)Mem_Realloc((char *)g_Clips_PPBuffer, g_ClipsPPBufferMax, g_ClipsPPBufferMax + 512);
      g_ClipsPPBufferMax += 512;
    }
    g_Rules_PPBackupTwicePos = g_ClipsPPBackupOnce;
    g_ClipsPPBackupOnce = g_PPBufferLength;
    result = Str_Append(str, (char *)g_Clips_PPBuffer, (unsigned int *)&g_ClipsPPBufferMax, &g_PPBufferLength);
    g_Clips_PPBuffer = (int)result;
  }
  return result;
}
// 51AA10: using guessed type int dword_51AA10;
// 51AA18: using guessed type int dword_51AA18;
// 51AA1C: using guessed type int dword_51AA1C;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (004947D0) --------------------------------------------------------
int Rules_BackupPPBuffer()
{
  int backupPos; // ebx
  int result; // eax

  if ( g_Rules_PPBufferEnabled )
  {
    if ( g_Clips_PPBuffer )
    {
      g_PPBufferLength = g_ClipsPPBackupOnce;
      backupPos = g_ClipsPPBackupOnce;
      g_ClipsPPBackupOnce = g_Rules_PPBackupTwicePos;
      result = g_Clips_PPBuffer + backupPos;
      *(_BYTE *)(g_Clips_PPBuffer + backupPos) = 0;
    }
  }
  return result;
}
// 51AA10: using guessed type int dword_51AA10;
// 51AA18: using guessed type int dword_51AA18;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (00494810) --------------------------------------------------------
char *Rules_CopyPPBuffer(void)
{
  char *copyBuffer; // eax
  char *sourcePtr; // esi
  char *destPtr; // edi
  char *bufferStart; // edx
  char currentChar; // al
  char nextChar; // al

  copyBuffer = (char *)Mem_SmallBlockAlloc(strlen((const char *)g_Clips_PPBuffer) + 1);
  sourcePtr = (char *)g_Clips_PPBuffer;
  destPtr = copyBuffer;
  bufferStart = copyBuffer;
  do
  {
    currentChar = *sourcePtr;
    *destPtr = *sourcePtr;
    if ( !currentChar )
      break;
    nextChar = sourcePtr[1];
    sourcePtr += 2;
    destPtr[1] = nextChar;
    destPtr += 2;
  }
  while ( nextChar );
  return bufferStart;
}
// 51AA28: using guessed type int dword_51AA28;

//----- (00494860) --------------------------------------------------------
int Rules_GetPPBuffer(void)
{
  return g_Clips_PPBuffer;
}
// 51AA28: using guessed type int dword_51AA28;

//----- (00494870) --------------------------------------------------------
char *__fastcall AST_Append(int a1, int a2)
{
  int i; // eax
  int indentDepth; // ecx
  char buffer[128]; // [esp+2h] [ebp-80h] BYREF

  *(_DWORD *)&buffer[124] = a1;
  buffer[0] = 10;
  i = 1;
  if ( g_Rules_PPIndentDepth >= 1 )
  {
    indentDepth = g_Rules_PPIndentDepth;
    do
      buffer[i++] = 32;
    while ( i <= indentDepth );
  }
  buffer[i] = 0;
  return IO_OutWriteToken(buffer);
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948C0) --------------------------------------------------------
int  Rules_IncrementIndentDepth(int result)
{
  g_Rules_PPIndentDepth += result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948D0) --------------------------------------------------------
int  Rules_DecrementIndentDepth(int result)
{
  g_Rules_PPIndentDepth -= result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948E0) --------------------------------------------------------
int  Rules_SetIndentDepth(int result)
{
  g_Rules_PPIndentDepth = result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948F0) --------------------------------------------------------
int  Rules_SetPPBufferStatus(int result)
{
  g_Rules_PPBufferEnabled = result;
  return result;
}
// 51AA10: using guessed type int dword_51AA10;

//----- (00494900) --------------------------------------------------------
int Rules_GetPPBufferStatus(void)
{
  return g_Rules_PPBufferEnabled;
}
// 51AA10: using guessed type int dword_51AA10;

//----- (004949C0) --------------------------------------------------------
const void * Rules_BsaveAtomTables(int fp)
{
  int v1; // edx
  int v2; // edx
  int v3; // edx

  Rules_BsaveSymbolTable(fp);
  Rules_BsaveFloatTable(v1);
  Rules_BsaveIntegerTable(v2);
  return Rules_BsaveBitmapTable(v3);
}
// 4949CA: variable 'v1' is possibly undefined
// 4949D1: variable 'v2' is possibly undefined
// 4949D8: variable 'v3' is possibly undefined

//----- (004949E0) --------------------------------------------------------
int *Rules_ClearAtomInUseMarks(void)
{
  _DWORD *symbolBucket; // edx
  _DWORD *symbolTableEnd; // ecx
  _DWORD *symbolPtr; // eax
  _DWORD *floatBucket; // edx
  _DWORD *floatTableEnd; // ecx
  _DWORD *floatPtr; // eax
  _DWORD *integerBucket; // edx
  _DWORD *integerTableEnd; // ecx
  _DWORD *integerPtr; // eax
  int *bitmapBucket; // edx
  int *bitmapTableEnd; // ecx
  int *result; // eax

  symbolBucket = (_DWORD *)Rules_GetSymbolTable();
  symbolTableEnd = symbolBucket + 1013;
  do
  {
    symbolPtr = (_DWORD *)*symbolBucket;
    if ( *symbolBucket )
    {
      do
      {
        symbolPtr[3] &= ~2u;
        symbolPtr = (_DWORD *)*symbolPtr;
      }
      while ( symbolPtr );
    }
    ++symbolBucket;
  }
  while ( symbolBucket != symbolTableEnd );
  floatBucket = (_DWORD *)Rules_GetFloatTable();
  floatTableEnd = floatBucket + 503;
  do
  {
    floatPtr = (_DWORD *)*floatBucket;
    if ( *floatBucket )
    {
      do
      {
        floatPtr[3] &= ~2u;
        floatPtr = (_DWORD *)*floatPtr;
      }
      while ( floatPtr );
    }
    ++floatBucket;
  }
  while ( floatBucket != floatTableEnd );
  integerBucket = (_DWORD *)Rules_GetIntegerTable();
  integerTableEnd = integerBucket + 167;
  do
  {
    integerPtr = (_DWORD *)*integerBucket;
    if ( *integerBucket )
    {
      do
      {
        integerPtr[3] &= ~2u;
        integerPtr = (_DWORD *)*integerPtr;
      }
      while ( integerPtr );
    }
    ++integerBucket;
  }
  while ( integerBucket != integerTableEnd );
  bitmapBucket = (int *)Rules_GetBitmapTable();
  bitmapTableEnd = bitmapBucket + 167;
  do
  {
    result = (int *)*bitmapBucket;
    if ( *bitmapBucket )
    {
      do
      {
        result[3] &= ~2u;
        result = (int *)*result;
      }
      while ( result );
    }
    ++bitmapBucket;
  }
  while ( bitmapBucket != bitmapTableEnd );
  return result;
}

//----- (00494AB0) --------------------------------------------------------
const void * Rules_BsaveSymbolTable(int fp)
{
  int ***bucketPtr; // ebx
  int **i; // edx
  const void *result; // eax
  int **j; // esi
  int numberOfUsedSymbols; // [esp+0h] [ebp-2Ch] BYREF
  int size; // [esp+4h] [ebp-28h] BYREF
  int symbolTable; // [esp+8h] [ebp-24h]
  int ***tableEnd; // [esp+Ch] [ebp-20h]
  int ***writeBucket; // [esp+10h] [ebp-1Ch]

  numberOfUsedSymbols = 0;
  size = 0;
  symbolTable = Rules_GetSymbolTable();
  bucketPtr = (int ***)symbolTable;
  do
  {
    for ( i = *bucketPtr; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
      {
        ++numberOfUsedSymbols;
        size += strlen((const char *)i[4]) + 1;
      }
    }
    ++bucketPtr;
  }
  while ( bucketPtr != (int ***)(symbolTable + 4052) );
  Rules_BsaveWriteBlock(4, fp, &numberOfUsedSymbols);
  Rules_BsaveWriteBlock(4, fp, &size);
  writeBucket = (int ***)symbolTable;
  result = (const void *)(symbolTable + 4052);
  tableEnd = (int ***)(symbolTable + 4052);
  do
  {
    for ( j = *writeBucket; j; j = (int **)*j )
    {
      if ( ((_BYTE)j[3] & 2) != 0 )
        result = Rules_BsaveWriteBlock(strlen((const char *)j[4]) + 1, fp, j[4]);
    }
    ++writeBucket;
  }
  while ( writeBucket != tableEnd );
  return result;
}

//----- (00494BA0) --------------------------------------------------------
const void * Rules_BsaveFloatTable(int fp)
{
  int floatTable; // ebp
  int ***bucketPtr; // edi
  int **i; // eax
  const void *result; // eax
  int **writeBucket; // edi
  int **tableEnd; // ebp
  int **floatPtr; // ecx
  _DWORD numberOfUsedFloats[7]; // [esp+0h] [ebp-1Ch] BYREF

  numberOfUsedFloats[0] = 0;
  floatTable = Rules_GetFloatTable();
  bucketPtr = (int ***)floatTable;
  do
  {
    for ( i = *bucketPtr; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
        ++numberOfUsedFloats[0];
    }
    ++bucketPtr;
  }
  while ( bucketPtr != (int ***)(floatTable + 2012) );
  result = Rules_BsaveWriteBlock(4, fp, numberOfUsedFloats);
  writeBucket = (int **)floatTable;
  tableEnd = (int **)(floatTable + 2012);
  do
  {
    floatPtr = (int **)*writeBucket;
    if ( *writeBucket )
    {
      do
      {
        if ( ((_BYTE)floatPtr[3] & 2) != 0 )
          result = Rules_BsaveWriteBlock(8, fp, floatPtr + 4);
        floatPtr = (int **)*floatPtr;
      }
      while ( floatPtr );
    }
    ++writeBucket;
  }
  while ( writeBucket != tableEnd );
  return result;
}
// 494C1B: variable 'v8' is possibly undefined

//----- (00494C40) --------------------------------------------------------
const void * Rules_BsaveIntegerTable(int fp)
{
  int integerTable; // ebp
  int ***bucketPtr; // edi
  int **i; // eax
  const void *result; // eax
  int **writeBucket; // edi
  int **tableEnd; // ebp
  int **integerPtr; // ecx
  _DWORD numberOfUsedIntegers[7]; // [esp+0h] [ebp-1Ch] BYREF

  numberOfUsedIntegers[0] = 0;
  integerTable = Rules_GetIntegerTable();
  bucketPtr = (int ***)integerTable;
  do
  {
    for ( i = *bucketPtr; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
        ++numberOfUsedIntegers[0];
    }
    ++bucketPtr;
  }
  while ( bucketPtr != (int ***)(integerTable + 668) );
  result = Rules_BsaveWriteBlock(4, fp, numberOfUsedIntegers);
  writeBucket = (int **)integerTable;
  tableEnd = (int **)(integerTable + 668);
  do
  {
    integerPtr = (int **)*writeBucket;
    if ( *writeBucket )
    {
      do
      {
        if ( ((_BYTE)integerPtr[3] & 2) != 0 )
          result = Rules_BsaveWriteBlock(4, fp, integerPtr + 4);
        integerPtr = (int **)*integerPtr;
      }
      while ( integerPtr );
    }
    ++writeBucket;
  }
  while ( writeBucket != tableEnd );
  return result;
}
// 494CBB: variable 'v8' is possibly undefined

//----- (00494CE0) --------------------------------------------------------
const void * Rules_BsaveBitmapTable(int fp)
{
  int bitmapTable; // ebp
  int ***bucketPtr; // ebx
  int **i; // eax
  int **writeBucket; // edi
  const void *result; // eax
  int **tableEnd; // ebp
  int *j; // ecx
  int bitmapNode; // ecx
  int numberOfUsedBitMaps; // [esp+0h] [ebp-24h] BYREF
  int size; // [esp+4h] [ebp-20h] BYREF
  _BYTE tempSize[28]; // [esp+8h] [ebp-1Ch] BYREF

  numberOfUsedBitMaps = 0;
  size = 0;
  bitmapTable = Rules_GetBitmapTable();
  bucketPtr = (int ***)bitmapTable;
  do
  {
    for ( i = *bucketPtr; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
      {
        ++numberOfUsedBitMaps;
        size += *((unsigned __int16 *)i + 10) + 1;
      }
    }
    ++bucketPtr;
  }
  while ( bucketPtr != (int ***)(bitmapTable + 668) );
  Rules_BsaveWriteBlock(4, fp, &numberOfUsedBitMaps);
  writeBucket = (int **)bitmapTable;
  result = Rules_BsaveWriteBlock(4, fp, &size);
  tableEnd = (int **)(bitmapTable + 668);
  do
  {
    for ( j = *writeBucket; j; j = (int *)*j )
    {
      if ( (j[3] & 2) != 0 )
      {
        tempSize[0] = *((_BYTE *)j + 20);
        Rules_BsaveWriteBlock(1, fp, tempSize);
        result = Rules_BsaveWriteBlock(*(unsigned __int16 *)(bitmapNode + 20), fp, *(const void **)(bitmapNode + 16));
      }
    }
    ++writeBucket;
  }
  while ( writeBucket != tableEnd );
  return result;
}
// 494D8A: variable 'v9' is possibly undefined
// 494D93: variable 'j' is possibly undefined

//----- (00494DB0) --------------------------------------------------------
int Rules_BloadAtomTables(void)
{
  int result; // eax
  int buffer; // edi
  int table; // eax
  unsigned __int8 *entry; // ecx
  int i; // esi
  int byte_count; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadSymbolTable();
  Rules_BloadFloatTable();
  Rules_BloadIntegerTable();
  Rules_BloadReadBlock((uintptr_t)&g_Rules_BloadBitmapCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&byte_count, 4u);
  if ( g_Rules_BloadBitmapCount )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(byte_count);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, byte_count);
    table = (int)(uintptr_t)Mem_NewArray(4 * g_Rules_BloadBitmapCount);
    g_ClipsBloadBitmapPointerTable = table;
    entry = (unsigned __int8 *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < g_Rules_BloadBitmapCount; ++i )
    {
      *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * i) = Rules_AddBitmapValue(entry + 1, *entry);
      entry += *entry + 1;
    }
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, byte_count);
  }
  else
  {
    g_ClipsBloadBitmapPointerTable = 0;
  }
  return result;
}
// 51AA38: using guessed type int dword_51AA38;
// 54E67C: using guessed type int dword_54E67C;

//----- (00494E00) --------------------------------------------------------
int Rules_BloadSymbolTable(void)
{
  int result; // eax
  int buffer; // ebp
  int table; // eax
  char *symbol_name; // edx
  int i; // ebx
  int byte_count; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&g_Rules_BloadSymbolCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&byte_count, 4u);
  if ( g_Rules_BloadSymbolCount )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(byte_count);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, byte_count);
    table = (int)(uintptr_t)Mem_NewArray(4 * g_Rules_BloadSymbolCount);
    g_ClipsBloadSymbolPointerArray = table;
    symbol_name = (char *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < g_Rules_BloadSymbolCount; ++i )
    {
      *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * i) = (int)(uintptr_t)Str_Intern(symbol_name, 0);
      symbol_name += strlen(symbol_name) + 1;
    }
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, byte_count);
  }
  else
  {
    g_ClipsBloadSymbolPointerArray = 0;
  }
  return result;
}
// 51AA2C: using guessed type int dword_51AA2C;
// 54E674: using guessed type int dword_54E674;

//----- (00494ED0) --------------------------------------------------------
int Rules_BloadFloatTable(void)
{
  int result; // eax
  int buffer; // esi
  double *numbers; // edx
  int i; // ecx

  result = Rules_BloadReadBlock((uintptr_t)&g_BloadFloatTableCount, 4u);
  if ( g_BloadFloatTableCount )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(8 * g_BloadFloatTableCount);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, 8 * g_BloadFloatTableCount);
    g_Clips_FloatConstantTable = (int)(uintptr_t)Mem_NewArray(4 * g_BloadFloatTableCount);
    numbers = (double *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < g_BloadFloatTableCount; ++i )
      *(_DWORD *)(g_Clips_FloatConstantTable + 4 * i) = Rules_AddDoubleValue(numbers[i]);
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, 8 * g_BloadFloatTableCount);
  }
  else
  {
    g_Clips_FloatConstantTable = 0;
  }
  return result;
}
// 51AA30: using guessed type int dword_51AA30;
// 54E670: using guessed type int dword_54E670;

//----- (00494F90) --------------------------------------------------------
int Rules_BloadIntegerTable(void)
{
  int result; // eax
  int buffer; // edi
  int *integers; // ecx
  int i; // edx

  result = Rules_BloadReadBlock((uintptr_t)&g_BloadIntegerTableCount, 4u);
  if ( g_BloadIntegerTableCount )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(4 * g_BloadIntegerTableCount);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, 4 * g_BloadIntegerTableCount);
    g_Clips_IntegerConstantTable = (int)(uintptr_t)Mem_NewArray(4 * g_BloadIntegerTableCount);
    integers = (int *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < g_BloadIntegerTableCount; ++i )
      *(_DWORD *)(g_Clips_IntegerConstantTable + 4 * i) = Rules_AddIntegerValue(integers[i]);
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, 4 * g_BloadIntegerTableCount);
  }
  else
  {
    g_Clips_IntegerConstantTable = 0;
  }
  return result;
}
// 51AA34: using guessed type int dword_51AA34;
// 54E678: using guessed type int dword_54E678;

//----- (004950D0) --------------------------------------------------------
signed int Rules_FreeBloadAtomTables(void)
{
  signed int result; // eax

  if ( g_ClipsBloadSymbolPointerArray )
    result = Mem_SmallBlockRelease((_DWORD *)g_ClipsBloadSymbolPointerArray, 4 * g_Rules_BloadSymbolCount);
  if ( g_Clips_FloatConstantTable )
    result = Mem_SmallBlockRelease((_DWORD *)g_Clips_FloatConstantTable, 4 * g_BloadFloatTableCount);
  if ( g_Clips_IntegerConstantTable )
    result = Mem_SmallBlockRelease((_DWORD *)g_Clips_IntegerConstantTable, 4 * g_BloadIntegerTableCount);
  if ( g_ClipsBloadBitmapPointerTable )
    return Mem_SmallBlockRelease((_DWORD *)g_ClipsBloadBitmapPointerTable, 4 * g_Rules_BloadBitmapCount);
  return result;
}
// 51AA2C: using guessed type int dword_51AA2C;
// 51AA30: using guessed type int dword_51AA30;
// 51AA34: using guessed type int dword_51AA34;
// 51AA38: using guessed type int dword_51AA38;
// 54E670: using guessed type int dword_54E670;
// 54E674: using guessed type int dword_54E674;
// 54E678: using guessed type int dword_54E678;
// 54E67C: using guessed type int dword_54E67C;

//----- (00495160) --------------------------------------------------------
int Rules_BloadAllocExpressionArray(void)
{
  int result; // eax

  result = Rules_BloadReadBlock((uintptr_t)&g_ClipsBloadExpressionCount, 4u);
  if ( g_ClipsBloadExpressionCount )
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)(14 * g_ClipsBloadExpressionCount));
    g_ClipsPackedExpressionArray = result;
  }
  else
  {
    g_ClipsPackedExpressionArray = 0;
  }
  return result;
}
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004951A0) --------------------------------------------------------
void Rules_BloadRefreshExpressions(void)
{
  if ( g_ClipsPackedExpressionArray )
    Rules_BloadAndRefresh(g_ClipsBloadExpressionCount, 14, (void (__fastcall *)(signed int, signed int))Rules_RefreshExpressionEntry);
}
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004951D0) --------------------------------------------------------
int  Rules_RefreshExpressionEntry(__int16 *bexp, int obji)
{
  int exprOffset; // ebx
  unsigned __int16 theType; // ax
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int nextArgIndex; // ebx
  int v10; // edi
  int argListIndex; // ecx
  int v12; // ebx
  int result; // eax
  int classIndex; // ebx
  int theDefclass; // ebx
  int primitiveEntity; // edi
  int genericIndex; // eax
  int theDefgeneric; // eax
  int deffunctionIndex; // edi
  int theDeffunction; // ebx

  exprOffset = 14 * obji;
  theType = *bexp;
  *(_WORD *)(g_ClipsPackedExpressionArray + 14 * obji) = *bexp;
  if ( theType < 8u )
  {
    if ( theType < 3u )
    {
      if ( !theType )
      {
        v6 = g_Clips_FloatConstantTable;
        v7 = 4 * *(_DWORD *)(bexp + 1);
LABEL_5:
        *(_DWORD *)(g_ClipsPackedExpressionArray + 14 * obji + 2) = *(_DWORD *)(v7 + v6);
        v8 = 14 * obji;
LABEL_6:
        ++*(_DWORD *)(*(_DWORD *)(v8 + g_ClipsPackedExpressionArray + 2) + 4);
        goto LABEL_7;
      }
      if ( theType <= 1u )
      {
        v7 = g_Clips_IntegerConstantTable;
        v6 = 4 * *(_DWORD *)(bexp + 1);
        goto LABEL_5;
      }
LABEL_12:
      v8 = 14 * obji;
      *(_DWORD *)(g_ClipsPackedExpressionArray + 14 * obji + 2) = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * *(_DWORD *)(bexp + 1));
      goto LABEL_6;
    }
    if ( theType <= 3u )
      goto LABEL_12;
    if ( theType >= 6u )
    {
      if ( theType > 6u )
      {
        *(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2) = &g_Instance_DummyInstanceRecord;
        Rules_IncrementRefCountField40(*(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2));
      }
      else
      {
        *(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2) = &g_Rules_DummyFactPtr;
        Rules_IncrementFactRefCount(*(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2));
      }
      goto LABEL_7;
    }
    if ( theType == 5 )
    {
      *(_DWORD *)(14 * obji + g_ClipsPackedExpressionArray + 2) = 0;
      goto LABEL_7;
    }
LABEL_26:
    primitiveEntity = g_Clips_PrimitiveEntityTable[*bexp];
    if ( !primitiveEntity || (*(_BYTE *)(primitiveEntity + 1) & 0x40) == 0 )
      goto LABEL_7;
    v8 = 14 * obji;
    *(_DWORD *)(14 * obji + g_ClipsPackedExpressionArray + 2) = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * *(_DWORD *)(bexp + 1));
    goto LABEL_6;
  }
  if ( theType <= 8u )
    goto LABEL_12;
  if ( theType >= 0xDu )
  {
    if ( theType <= 0xDu )
      goto LABEL_12;
    if ( theType < 0x39u )
    {
      if ( theType == 35 )
      {
        *(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2) = g_DeftemplateRecordTable + 36 * *(_DWORD *)(bexp + 1);
        goto LABEL_7;
      }
      goto LABEL_26;
    }
    if ( theType > 0x39u )
    {
      if ( theType < 0x3Cu )
        goto LABEL_26;
      if ( theType <= 0x3Cu )
      {
        *(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2) = g_DefglobalBloadRecords + 56 * *(_DWORD *)(bexp + 1);
        goto LABEL_7;
      }
      if ( theType != 105 )
        goto LABEL_26;
    }
    else
    {
      classIndex = *(_DWORD *)(bexp + 1);
      if ( classIndex == -1 )
        theDefclass = 0;
      else
        theDefclass = 124 * classIndex + g_Clips_DefclassArrayBase;
      *(_DWORD *)(14 * obji + g_ClipsPackedExpressionArray + 2) = theDefclass;
    }
  }
  else
  {
    if ( theType < 0xBu )
    {
      if ( theType == 10 )
      {
        *(_DWORD *)(g_ClipsPackedExpressionArray + exprOffset + 2) = *(_DWORD *)(4 * *(_DWORD *)(bexp + 1) + g_Rules_BloadFunctionPtrTable);
        goto LABEL_7;
      }
      goto LABEL_26;
    }
    if ( theType > 0xBu )
    {
      deffunctionIndex = *(_DWORD *)(bexp + 1);
      if ( deffunctionIndex == -1 )
        theDeffunction = 0;
      else
        theDeffunction = 46 * deffunctionIndex + g_DeffunctionBloadRecordArray;
      *(_DWORD *)(14 * obji + g_ClipsPackedExpressionArray + 2) = theDeffunction;
    }
    else
    {
      genericIndex = *(_DWORD *)(bexp + 1);
      if ( genericIndex == -1 )
        theDefgeneric = 0;
      else
        theDefgeneric = 40 * genericIndex + g_DefgenericMethodArray;
      *(_DWORD *)(g_ClipsPackedExpressionArray + 14 * obji + 2) = theDefgeneric;
    }
  }
LABEL_7:
  nextArgIndex = *(_DWORD *)(bexp + 5);
  v10 = 14 * obji;
  if ( nextArgIndex == -1 )
    *(_DWORD *)(v10 + g_ClipsPackedExpressionArray + 10) = 0;
  else
    *(_DWORD *)(v10 + g_ClipsPackedExpressionArray + 10) = g_ClipsPackedExpressionArray + 14 * nextArgIndex;
  argListIndex = *(_DWORD *)(bexp + 3);
  v12 = 14 * obji;
  result = g_ClipsPackedExpressionArray;
  if ( argListIndex == -1 )
    *(_DWORD *)(v12 + g_ClipsPackedExpressionArray + 6) = 0;
  else
    *(_DWORD *)(v12 + g_ClipsPackedExpressionArray + 6) = g_ClipsPackedExpressionArray + 14 * argListIndex;
  return result;
}
// 49526E: variable 'a2' is possibly undefined
// 51A114: using guessed type void *off_51A114;
// 51A214: using guessed type void *off_51A214;
// 51B370: using guessed type int dword_51B370;
// 51B378: using guessed type int dword_51B378;
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3AC: using guessed type int dword_51B3AC;
// 54DD24: using guessed type int dword_54DD24;
// 54E530: using guessed type int dword_54E530[70];
// 54E670: using guessed type int dword_54E670;
// 54E674: using guessed type int dword_54E674;
// 54E678: using guessed type int dword_54E678;
// 54E67C: using guessed type int dword_54E67C;
// 54E688: using guessed type int dword_54E688;
// 54E840: using guessed type int dword_54E840;

//----- (00495590) --------------------------------------------------------
signed int Rules_FreeBloadedExpressions(void)
{
  unsigned int exprIndex; // ebx
  int exprOffset; // ecx
  int exprPtr; // edx
  unsigned __int16 theType; // ax
  signed int result; // eax
  int primitiveEntity; // edi

  exprIndex = 0;
  if ( g_ClipsBloadExpressionCount )
  {
    exprOffset = 0;
    do
    {
      exprPtr = exprOffset + g_ClipsPackedExpressionArray;
      theType = *(_WORD *)(exprOffset + g_ClipsPackedExpressionArray);
      if ( theType >= 6u )
      {
        if ( theType <= 6u )
        {
          Rules_DecrementFactRefCount(*(_DWORD *)(exprPtr + 2));
          goto LABEL_6;
        }
        if ( theType < 8u )
        {
          Instance_DecrementBusyCount(*(_DWORD *)(exprPtr + 2));
          goto LABEL_6;
        }
        if ( theType <= 8u )
          goto LABEL_21;
        if ( theType < 0xDu )
          goto LABEL_13;
        if ( theType <= 0xDu )
          goto LABEL_21;
        if ( theType != 105 )
          goto LABEL_13;
      }
      else
      {
        if ( theType )
        {
          if ( theType <= 1u )
          {
            Rules_DecrementIntegerCount(*(_DWORD *)(exprPtr + 2), exprOffset);
            goto LABEL_6;
          }
          if ( theType >= 4u )
          {
LABEL_13:
            primitiveEntity = g_Clips_PrimitiveEntityTable[*(__int16 *)(exprOffset + g_ClipsPackedExpressionArray)];
            if ( primitiveEntity && (*(_BYTE *)(primitiveEntity + 1) & 0x40) != 0 )
              Rules_DecrementBitmapCount(*(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2), exprOffset);
            goto LABEL_6;
          }
LABEL_21:
          Rules_DecrementSymbolCount(*(_DWORD *)(exprOffset + g_ClipsPackedExpressionArray + 2), exprOffset);
          goto LABEL_6;
        }
        Rules_DecrementFloatCount(*(_DWORD *)(exprPtr + 2), exprOffset);
      }
LABEL_6:
      ++exprIndex;
      exprOffset += 14;
    }
    while ( exprIndex < g_ClipsBloadExpressionCount );
  }
  result = 14 * g_ClipsBloadExpressionCount;
  if ( 14 * g_ClipsBloadExpressionCount )
    return Mem_ReleasePoolBlock(g_ClipsPackedExpressionArray, 14 * g_ClipsBloadExpressionCount);
  return result;
}
// 49564B: simplified comparisons for 'ax.2': >=3u && !=3 became >=4u
// 4955D2: variable 'v1' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004956B0) --------------------------------------------------------
int Rules_CountHashedExpressions(void)
{
  int i; // ecx
  int result; // eax
  int j; // edx
  int exphash; // edx
  int v4; // edx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = g_ExpressionHashTable;
    for ( j = *(_DWORD *)(i + g_ExpressionHashTable); j; j = *(_DWORD *)(v4 + 12) )
    {
      Rules_MarkReferencedFunctions(*(__int16 **)(j + 8));
      *(_DWORD *)(exphash + 16) = g_ClipsExpressionNodeIndex;
      result = AST_CountTreeNodes(*(_DWORD *)(exphash + 8));
      g_ClipsExpressionNodeIndex += result;
    }
  }
  return result;
}
// 4956D9: variable 'v3' is possibly undefined
// 4956EA: variable 'v4' is possibly undefined
// 4956F1: variable 'i' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54E680: using guessed type int dword_54E680;

//----- (00495700) --------------------------------------------------------
__int16 * Rules_AssignHashedExpressionIndices(int fp)
{
  int i; // esi
  __int16 *result; // eax
  int j; // ecx
  int v5; // ecx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = (__int16 *)g_ExpressionHashTable;
    for ( j = *(_DWORD *)(i + g_ExpressionHashTable); j; j = *(_DWORD *)(v5 + 12) )
      result = Rules_BsaveWriteExpression(*(__int16 **)(j + 8), fp);
  }
  return result;
}
// 495726: variable 'v5' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;

//----- (00495740) --------------------------------------------------------
int Rules_InvokeConstructCallbacks(void)
{
  int i; // edx
  int result; // eax
  int v2; // edx

  for ( i = g_BinaryItemListHead; i; i = *(_DWORD *)(v2 + 36) )
  {
    while ( !*(_DWORD *)(i + 20) )
    {
      i = *(_DWORD *)(i + 36);
      if ( !i )
        return result;
    }
    result = (*(int (**)(void))(i + 20))();
  }
  return result;
}
// 495763: variable 'v2' is possibly undefined
// 51AA3C: using guessed type int dword_51AA3C;

//----- (00495770) --------------------------------------------------------
__int16 * Rules_BsaveWriteExpression(__int16 *result, int fp)
{
  __int16 *i; // ecx
  int currentIndex; // edx
  unsigned __int16 theType; // ax
  int bsaveValue; // eax
  int v7; // ecx
  int theDeftemplate; // ebx
  int theDefclass; // eax
  int primitiveEntity; // ebp
  int theDefglobal; // edi
  int theDefgeneric; // edx
  int theDeffunction; // ebp
  unsigned __int16 newTestType; // [esp+0h] [ebp-24h] BYREF
  int newTestValue; // [esp+2h] [ebp-22h]
  int newTestArgList; // [esp+6h] [ebp-1Eh]
  int newTestNextArg; // [esp+Ah] [ebp-1Ah]

  for ( i = result; i; i = *(__int16 **)(v7 + 10) )
  {
    currentIndex = ++g_ClipsExpressionNodeIndex;
    newTestType = *i;
    if ( *(_DWORD *)(i + 3) )
      newTestArgList = currentIndex;
    else
      newTestArgList = -1;
    if ( *(_DWORD *)(i + 5) )
      newTestNextArg = g_ClipsExpressionNodeIndex + AST_CountTreeNodes(*(_DWORD *)(i + 3));
    else
      newTestNextArg = -1;
    theType = *i;
    if ( (unsigned __int16)*i >= 8u )
    {
      if ( (unsigned __int16)*i <= 8u )
        goto LABEL_8;
      if ( theType >= 0xDu )
      {
        if ( theType <= 0xDu )
          goto LABEL_8;
        if ( theType >= 0x39u )
        {
          if ( theType <= 0x39u )
          {
            theDefclass = *(_DWORD *)(i + 1);
            if ( !theDefclass )
              goto LABEL_42;
            bsaveValue = *(_DWORD *)(theDefclass + 12);
            goto LABEL_9;
          }
          if ( theType >= 0x3Cu )
          {
            if ( theType <= 0x3Cu )
            {
              theDefglobal = *(_DWORD *)(i + 1);
              if ( !theDefglobal )
                goto LABEL_42;
              bsaveValue = *(_DWORD *)(theDefglobal + 12);
              goto LABEL_9;
            }
            if ( theType == 105 )
              goto LABEL_10;
          }
        }
        else if ( theType == 35 )
        {
          theDeftemplate = *(_DWORD *)(i + 1);
          if ( !theDeftemplate )
            goto LABEL_42;
          bsaveValue = *(_DWORD *)(theDeftemplate + 12);
          goto LABEL_9;
        }
      }
      else
      {
        if ( theType >= 0xBu )
        {
          if ( theType > 0xBu )
          {
            theDeffunction = *(_DWORD *)(i + 1);
            if ( !theDeffunction )
            {
LABEL_42:
              newTestValue = -1;
              goto LABEL_10;
            }
            bsaveValue = *(_DWORD *)(theDeffunction + 12);
          }
          else
          {
            theDefgeneric = *(_DWORD *)(i + 1);
            if ( !theDefgeneric )
              goto LABEL_42;
            bsaveValue = *(_DWORD *)(theDefgeneric + 12);
          }
          goto LABEL_9;
        }
        if ( theType == 10 )
        {
          bsaveValue = *(__int16 *)(*(_DWORD *)(i + 1) + 25);
          goto LABEL_9;
        }
      }
    }
    else
    {
      if ( theType < 4u )
        goto LABEL_8;
      if ( theType > 4u )
        goto LABEL_42;
    }
    primitiveEntity = g_Clips_PrimitiveEntityTable[*i];
    if ( primitiveEntity && (*(_BYTE *)(primitiveEntity + 1) & 0x40) != 0 )
    {
LABEL_8:
      bsaveValue = *(_DWORD *)(*(_DWORD *)(i + 1) + 12) << 16 >> 18;
LABEL_9:
      newTestValue = bsaveValue;
    }
LABEL_10:
    Rules_BsaveWriteBlock(14, fp, &newTestType);
    result = *(__int16 **)(v7 + 6);
    if ( result )
      result = (__int16 *)Rules_BsaveWriteExpression((int)result, fp);
  }
  return result;
}
// 495904: simplified comparisons for 'ax.2': <6u && !=5 became <5u
// 4957C9: simplified comparisons for 'ax.2': >=3u && >=4u became >=4u
// 4957B8: variable 'i' is possibly undefined
// 4957FC: variable 'v7' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];
// 54E680: using guessed type int dword_54E680;

//----- (00495930) --------------------------------------------------------
const void * Rules_BsaveWriteConstraints(int fp)
{
  int hashOffset; // edx
  int theIndex; // eax
  int i; // ecx
  int v5; // ecx
  int v6; // ecx
  const void *result; // eax
  int j; // edi
  int *k; // ecx
  int v10; // ecx
  _BYTE bsaveRecord[24]; // [esp+0h] [ebp-34h] BYREF
  _DWORD numberOfConstraints[7]; // [esp+18h] [ebp-1Ch] BYREF

  hashOffset = 0;
  theIndex = 0;
  numberOfConstraints[0] = 0;
  do
  {
    for ( i = *(_DWORD *)(g_ConstraintHashTable + hashOffset); i; ++theIndex )
    {
      *(_WORD *)(i + 4) = theIndex;
      ++numberOfConstraints[0];
      i = *(_DWORD *)(i + 30);
    }
    hashOffset += 4;
  }
  while ( hashOffset != 668 );
  if ( !Rules_DynamicConstraintCheckingEnabled() && numberOfConstraints[0] )
  {
    numberOfConstraints[0] = 0;
    Rules_PrintWarningID((int)aCstrnbin, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aConstraintsAre, v5);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWhenDynamicCon, v6);
  }
  result = Rules_BsaveWriteBlock(4, fp, numberOfConstraints);
  if ( numberOfConstraints[0] )
  {
    for ( j = 0; j != 668; j += 4 )
    {
      result = (const void *)g_ConstraintHashTable;
      for ( k = *(int **)(j + g_ConstraintHashTable); k; k = *(int **)(v10 + 30) )
      {
        Rules_PackConstraintRecord(k, (int)bsaveRecord);
        result = Rules_BsaveWriteBlock(24, fp, bsaveRecord);
      }
    }
  }
  return result;
}
// 4959A7: variable 'v5' is possibly undefined
// 4959B6: variable 'v6' is possibly undefined
// 495A00: variable 'v10' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];
// 54E694: using guessed type int dword_54E694;
