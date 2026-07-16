/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00481720) --------------------------------------------------------
double  Rules_CoerceFormToNumericArg(__int16 *theArgument, int convertToFloat, _DWORD *returnValue, double result, int whichArgument)
{
  unsigned int theType; // edx
  int theValue; // eax

  if ( (unsigned __int16)*theArgument > 1u )
  {
    Parser_ParseForm(theArgument, returnValue, convertToFloat, result);
    theType = returnValue[1];
    theValue = returnValue[2];
  }
  else
  {
    theType = *theArgument;
    theValue = *(_DWORD *)(theArgument + 1);
  }
  if ( theType > 1 )
  {
    Parser_ReportError(whichArgument, (int)aIntegerOrFlo_0);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    returnValue[1] = 1;
    returnValue[2] = Rules_AddIntegerValue(0);
  }
  else
  {
    if ( convertToFloat )
    {
      if ( theType == 1 )
        theValue = Rules_AddDoubleValue((double)*(int *)(theValue + 16));
    }
    returnValue[1] = theType;
    returnValue[2] = theValue;
  }
  return result;
}
// 48173C: simplified comparisons for 'edx.4': !=0 && !=1 became >=2u
// 48172C: simplified comparisons for '[ds.2:eax.4].2': !=0 && !=1 became >=2u
// 481745: variable 'a2' is possibly undefined
// 48175C: variable 'v5' is possibly undefined

//----- (004817C0) --------------------------------------------------------
int  Rules_GetLogicalNameArg(int whichArgument, int defaultLogicalName, int a3, double a4)
{
  int v5; // ecx
  int v6; // ecx
  char *floatSymbol; // eax
  int v9; // ecx
  char *integerSymbol; // eax
  int v11; // ecx
  int valueBuffer; // [esp-4h] [ebp-20h] BYREF
  int theType; // [esp+0h] [ebp-1Ch]
  int theValue; // [esp+4h] [ebp-18h]
  int v15; // [esp+14h] [ebp-8h]

  v15 = a3;
  Rules_RtnUnknown(whichArgument, &valueBuffer, a4);
  if ( theType == 2 || theType == 3 || theType == 8 )
  {
    if ( !strcmp_(*(_DWORD *)(theValue + 16), aT) || !strcmp_(v5, aT_0) )
      return defaultLogicalName;
    return v6;
  }
  else if ( theType )
  {
    if ( theType == 1 )
    {
      integerSymbol = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(theValue + 16));
      return Str_Intern(integerSymbol, v11)[4];
    }
    else
    {
      return 0;
    }
  }
  else
  {
    floatSymbol = (char *)Rules_FloatToSymbol(*(_DWORD *)(theValue + 16), *(double *)(theValue + 16));
    return Str_Intern(floatSymbol, v9)[4];
  }
}
// 4817FA: variable 'v6' is possibly undefined
// 481809: variable 'v5' is possibly undefined
// 481838: variable 'v9' is possibly undefined
// 481854: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (00481870) --------------------------------------------------------
int  Rules_GetFileNameArg(int whichArgument, int functionName, double a3)
{
  int v3; // ecx
  int valueBuffer; // [esp-4h] [ebp-20h] BYREF
  int theType; // [esp+0h] [ebp-1Ch]
  int theValue; // [esp+4h] [ebp-18h]
  int v8; // [esp+18h] [ebp-4h]

  v8 = functionName;
  Rules_RtnUnknown(whichArgument, &valueBuffer, a3);
  if ( theType == 3 || theType == 2 )
    return *(_DWORD *)(theValue + 16);
  Parser_ReportError(v3, (int)aFileName);
  return 0;
}
// 4818A7: variable 'v3' is possibly undefined

//----- (004818C0) --------------------------------------------------------
signed int __fastcall Rules_OpenFileErrorMessage(int functionName, int fileName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aArgacces, 2, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasUnableToOpe, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_FileError, v7);
}
// 4818E2: variable 'v3' is possibly undefined
// 4818EE: variable 'v4' is possibly undefined
// 4818FD: variable 'v5' is possibly undefined
// 481909: variable 'v6' is possibly undefined
// 481918: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481930) --------------------------------------------------------
int * Rules_GetModuleNameArg(int whichArgument, int functionName, _DWORD *error, double a4)
{
  int v4; // ecx
  int *result; // eax
  int v6; // ecx
  _DWORD valueBuffer[2]; // [esp-4h] [ebp-24h] BYREF
  int theValue; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+1Ch] [ebp-4h]

  v9 = functionName;
  *error = 0;
  Rules_RtnUnknown(whichArgument, valueBuffer, a4);
  if ( valueBuffer[1] == 2 )
  {
    result = Module_FindByName(*(_BYTE **)(theValue + 16));
    if ( !result )
    {
      if ( strcmp_(v6, *(_DWORD *)(theValue + 16)) )
      {
        Parser_ReportError(1, (int)aDefmoduleNam_0);
        *error = 1;
      }
      return 0;
    }
  }
  else
  {
    Parser_ReportError(v4, (int)aDefmoduleNam_0);
    *error = 1;
    return 0;
  }
  return result;
}
// 481972: variable 'v4' is possibly undefined
// 48198D: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004819C0) --------------------------------------------------------
int  Rules_GetConstructNameArg(int constructType, int functionName, double a3)
{
  int v4; // ecx
  _DWORD valueBuffer[8]; // [esp-4h] [ebp-20h] BYREF

  valueBuffer[6] = functionName;
  if ( Rules_RtnArgCount() == 1 )
  {
    Rules_RtnUnknown(1, valueBuffer, a3);
    if ( valueBuffer[1] == 2 )
    {
      return *(_DWORD *)(valueBuffer[2] + 16);
    }
    else
    {
      Parser_ReportError(1, constructType);
      return 0;
    }
  }
  else
  {
    Rules_ExpectedCountError(v4, 1);
    return 0;
  }
}
// 4819F7: variable 'v4' is possibly undefined

//----- (00481A20) --------------------------------------------------------
signed int  Rules_NonexistentArgError(int functionName, int argumentPosition)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  Rules_PrintErrorID((int)aArgacces, 3, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReceivedAReque, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument, v7);
  Rules_PrintLongInteger(v8, argumentPosition);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWhichIsNonExis, v9);
}
// 481A44: variable 'v3' is possibly undefined
// 481A50: variable 'v4' is possibly undefined
// 481A5F: variable 'v5' is possibly undefined
// 481A6B: variable 'v6' is possibly undefined
// 481A7A: variable 'v7' is possibly undefined
// 481A86: variable 'v8' is possibly undefined
// 481A95: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481AA0) --------------------------------------------------------
signed int  Rules_ExpectedCountError(int functionName, int expectedNumber)
{
  int v3; // ecx
  int v4; // ecx
  int countRelation; // ecx
  char *countRelationText; // edx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)aArgacces, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v4);
  if ( countRelation )
  {
    if ( countRelation == 1 )
    {
      countRelationText = aExpectedAtLeas;
    }
    else if ( countRelation == 2 )
    {
      countRelationText = aExpectedNoMore;
    }
    else
    {
      countRelationText = aGeneratedAnIll;
    }
  }
  else
  {
    countRelationText = aExpectedExactl;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)countRelationText, countRelation);
  Rules_PrintLongInteger(v7, expectedNumber);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArgumentS, v8);
}
// 481AC4: variable 'v3' is possibly undefined
// 481AD0: variable 'v4' is possibly undefined
// 481AD7: variable 'v5' is possibly undefined
// 481AF9: variable 'v7' is possibly undefined
// 481B08: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481B30) --------------------------------------------------------
signed int  Rules_CheckFunctionArgCount(int functionName, _BYTE *restrictions, int argumentCount)
{
  int v3; // ecx
  int minArguments; // ebx
  int maxArguments; // eax

  v3 = functionName;
  if ( !restrictions )
    return 1;
  if ( (IsTable[(unsigned __int8)(*restrictions + 1)] & 0x20) != 0 )
    minArguments = atoi_(functionName);
  else
    minArguments = -1;
  if ( (IsTable[(unsigned __int8)(restrictions[1] + 1)] & 0x20) != 0 )
    maxArguments = atoi_(v3);
  else
    maxArguments = 10000;
  if ( minArguments == maxArguments )
  {
    if ( argumentCount == maxArguments )
      return 1;
    goto LABEL_15;
  }
  if ( argumentCount < minArguments )
  {
LABEL_15:
    Rules_ExpectedCountError(v3, minArguments);
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( argumentCount <= maxArguments )
    return 1;
  Rules_ExpectedCountError(v3, maxArguments);
  Lexer_ErrorRecover(1);
  return 0;
}
// 481B5F: variable 'a2' is possibly undefined
// 481B7A: variable 'v3' is possibly undefined
// 48523F: using guessed type int __thiscall unknown_libname_2(_DWORD);

//----- (00481C20) --------------------------------------------------------
signed int  Parser_ReportError(int whichArgument, int expectedType)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  Rules_PrintErrorID((int)aArgacces, 5, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedArgume, v5);
  Rules_PrintLongInteger(v6, whichArgument);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aToBeOfType, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], expectedType, v8);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503A24, v9);
}
// 481C44: variable 'v3' is possibly undefined
// 481C50: variable 'v4' is possibly undefined
// 481C5F: variable 'v5' is possibly undefined
// 481C6B: variable 'v6' is possibly undefined
// 481C7A: variable 'v7' is possibly undefined
// 481C86: variable 'v8' is possibly undefined
// 481C95: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481CA0) --------------------------------------------------------
int ** Rules_ReportSymbolTypeError(_BYTE *functionName, int whichArgument)
{
  int **result; // eax
  int v4; // edx
  char restrictionType; // al
  char *typeName; // eax

  result = Rules_MakeSymbol(functionName);
  if ( result )
  {
    restrictionType = Rules_GetArgRestrictionType((int)result, v4);
    typeName = Rules_GetArgTypeName(restrictionType);
    return (int **)Parser_ReportError(whichArgument, (int)typeName);
  }
  return result;
}
// 481CB3: variable 'v4' is possibly undefined

//----- (00481CD0) --------------------------------------------------------
signed int  Rules_ExpectedTypeError(int accessFunction, int functionName, int argumentPosition)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  Rules_PrintErrorID((int)aArgacces, 6, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], accessFunction, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReceivedAReque, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument, v9);
  Rules_PrintLongInteger(v10, argumentPosition);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWhichIsNotOfTy, v11);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v12, v12);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503A24, v13);
}
// 481CF4: variable 'v5' is possibly undefined
// 481D00: variable 'v6' is possibly undefined
// 481D0F: variable 'v7' is possibly undefined
// 481D1B: variable 'v8' is possibly undefined
// 481D2A: variable 'v9' is possibly undefined
// 481D36: variable 'v10' is possibly undefined
// 481D45: variable 'v11' is possibly undefined
// 481D51: variable 'v12' is possibly undefined
// 481D60: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481D70) --------------------------------------------------------
signed int * Str_Intern(char *str, int a2)
{
  char *srcPtr; // esi
  int prevEntry; // ebx
  signed int curEntry; // ecx
  int freeListHead; // edx
  signed int allocatedNode; // eax
  int newSymbol; // ebp
  int nameBuffer; // eax
  __int16 flagsWord; // dx
  char *destPtr; // edi
  char firstByte; // al
  char secondByte; // al
  int hashValue; // [esp+0h] [ebp-18h]

  srcPtr = str;
  prevEntry = 0;
  if ( !str )
  {
    Rules_ReportSystemError(a2, 1);
    IO_RunRouterExitCallbacks();
  }
  hashValue = Rules_HashSymbolName(srcPtr, 0x3F5u);
  curEntry = *(_DWORD *)((uintptr_t)(unsigned int)g_Clips_SymbolHashTable + 4 * hashValue);
  if ( curEntry )
  {
    while ( strcmp(srcPtr, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)curEntry + 16)) )
    {
      prevEntry = curEntry;
      curEntry = *(_DWORD *)(uintptr_t)(unsigned int)curEntry;
      if ( !curEntry )
        goto LABEL_6;
    }
    return (signed int *)(uintptr_t)(unsigned int)curEntry;
  }
  else
  {
LABEL_6:
    freeListHead = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = freeListHead;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80) = *(_DWORD *)(uintptr_t)(unsigned int)freeListHead;
      allocatedNode = g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedNode = Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    newSymbol = allocatedNode;
    if ( prevEntry )
      *(_DWORD *)(uintptr_t)(unsigned int)prevEntry = allocatedNode;
    else
      *(_DWORD *)((uintptr_t)(unsigned int)g_Clips_SymbolHashTable + 4 * hashValue) = allocatedNode;
    nameBuffer = (int)(uintptr_t)Mem_SmallBlockAlloc(strlen(srcPtr) + 1);
    *(_DWORD *)(uintptr_t)(unsigned int)newSymbol = 0;
    *(_DWORD *)((uintptr_t)(unsigned int)newSymbol + 4) = 0;
    flagsWord = *(_WORD *)((uintptr_t)(unsigned int)newSymbol + 12);
    *(_DWORD *)((uintptr_t)(unsigned int)newSymbol + 16) = nameBuffer;
    *(_WORD *)((uintptr_t)(unsigned int)newSymbol + 12) = flagsWord & 3;
    destPtr = (char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)newSymbol + 16);
    *(_DWORD *)((uintptr_t)(unsigned int)newSymbol + 12) |= 4 * (hashValue & 0x3FFF);
    do
    {
      firstByte = *srcPtr;
      *destPtr = *srcPtr;
      if ( !firstByte )
        break;
      secondByte = srcPtr[1];
      srcPtr += 2;
      destPtr[1] = secondByte;
      destPtr += 2;
    }
    while ( secondByte );
    Rules_AddEphemeralHashNode(newSymbol, &g_Rules_EphemeralSymbolListHead, 10, 20);
    *(_DWORD *)((uintptr_t)(unsigned int)newSymbol + 8) = g_ClipsCurrentEvaluationDepth;
    return (signed int *)(uintptr_t)(unsigned int)newSymbol;
  }
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A268: using guessed type _DWORD dword_51A268;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD50: using guessed type int dword_54DD50;

//----- (00481EC0) --------------------------------------------------------
int * Rules_FindSymbolEntry(_BYTE *str)
{
  int trace_load_save; // eax
  int bucket_index; // eax
  int bucket_entry; // ecx

  trace_load_save = 0;
  if ( !g_Clips_SymbolHashTable )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] symbol-lookup-missing-table %s\n", str);
    return 0;
  }
  bucket_index = Rules_HashSymbolName(str, 0x3F5u);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] symbol-lookup table=%08x bucket=%d key=%s\n", g_Clips_SymbolHashTable, bucket_index, str);
  bucket_entry = *(_DWORD *)(g_Clips_SymbolHashTable + 4 * bucket_index);
  while ( bucket_entry )
  {
    if ( !strcmp_((int)str, *(_DWORD *)(bucket_entry + 16)) )
      return (int *)bucket_entry;
    bucket_entry = *(_DWORD *)bucket_entry;
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD50: using guessed type int dword_54DD50;

//----- (00481F00) --------------------------------------------------------
int __stdcall Rules_AddDoubleValue(double number)
{
  unsigned int hashValue; // ebx
  signed int curEntry; // edx
  signed int *prevEntry; // ecx
  _DWORD *freeListHead; // esi
  signed int allocatedNode; // eax
  signed int newFloat; // esi
  __int16 flagsWord; // dx

  hashValue = Rules_HashDoubleValue(LODWORD(number), SHIDWORD(number), 0x1F7u);
  curEntry = *(_DWORD *)(4 * hashValue + g_ClipsFloatHashTable);
  prevEntry = 0;
  if ( curEntry )
  {
    while ( number != *(double *)(curEntry + 16) )
    {
      prevEntry = (signed int *)curEntry;
      curEntry = *(_DWORD *)curEntry;
      if ( !curEntry )
        goto LABEL_4;
    }
    return curEntry;
  }
  else
  {
LABEL_4:
    freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListHead;
      allocatedNode = g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedNode = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    newFloat = allocatedNode;
    if ( prevEntry )
      *prevEntry = allocatedNode;
    else
      *(_DWORD *)(g_ClipsFloatHashTable + 4 * hashValue) = allocatedNode;
    *(_DWORD *)allocatedNode = 0;
    flagsWord = *(_WORD *)(allocatedNode + 12);
    *(_DWORD *)(allocatedNode + 4) = 0;
    *(double *)(allocatedNode + 16) = number;
    *(_WORD *)(allocatedNode + 12) = flagsWord & 3;
    *(_DWORD *)(allocatedNode + 12) |= 4 * (hashValue & 0x3FFF);
    Rules_AddEphemeralHashNode(allocatedNode, &g_Rules_EphemeralFloatListHead, 0, 24);
    *(_DWORD *)(newFloat + 8) = g_ClipsCurrentEvaluationDepth;
    return newFloat;
  }
}
// 481F66: variable 'v3' is possibly undefined
// 51A26C: using guessed type _DWORD dword_51A26C;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD58: using guessed type int dword_54DD58;

//----- (00482000) --------------------------------------------------------
int  Rules_AddIntegerValue(int number)
{
  int bucket_index; // edx
  int node; // eax
  int previous_node; // ecx
  int free_node; // esi
  int new_node; // eax
  __int16 flags; // bx

  bucket_index = Rules_HashIntegerValue(number, 167);
  node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsIntegerHashTable + 4 * bucket_index);
  previous_node = 0;
  while ( node )
  {
    if ( number == *(_DWORD *)((uintptr_t)(unsigned int)node + 16) )
      return node;
    previous_node = node;
    node = *(_DWORD *)(uintptr_t)(unsigned int)node;
  }
  free_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = free_node;
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80) = *(_DWORD *)(uintptr_t)(unsigned int)free_node;
    new_node = g_ClipsMemFreeListTemp;
  }
  else
  {
    new_node = Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  if ( previous_node )
    *(_DWORD *)(uintptr_t)(unsigned int)previous_node = new_node;
  else
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsIntegerHashTable + 4 * bucket_index) = new_node;
  *(_DWORD *)((uintptr_t)(unsigned int)new_node + 16) = number;
  flags = *(_WORD *)((uintptr_t)(unsigned int)new_node + 12);
  *(_DWORD *)(uintptr_t)(unsigned int)new_node = 0;
  *(_DWORD *)((uintptr_t)(unsigned int)new_node + 4) = 0;
  *(_WORD *)((uintptr_t)(unsigned int)new_node + 12) = flags & 3;
  *(_DWORD *)((uintptr_t)(unsigned int)new_node + 12) |= 4 * (bucket_index & 0x3FFF);
  Rules_AddEphemeralHashNode(new_node, &g_Rules_EphemeralIntegerListHead, 0, 20);
  *(_DWORD *)((uintptr_t)(unsigned int)new_node + 8) = g_ClipsCurrentEvaluationDepth;
  return new_node;
}
// 51A270: using guessed type _DWORD dword_51A270;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD54: using guessed type int dword_54DD54;

//----- (004820D0) --------------------------------------------------------
int * Rules_FindIntegerValue(signed int number)
{
  int *result; // eax
  int searchValue; // ecx

  result = *(int **)(g_ClipsIntegerHashTable + 4 * Rules_HashIntegerValue(number, 167));
  if ( !result )
    return 0;
  while ( searchValue != result[4] )
  {
    result = (int *)*result;
    if ( !result )
      return 0;
  }
  return result;
}
// 4820EE: variable 'v2' is possibly undefined
// 54DD54: using guessed type int dword_54DD54;

//----- (00482100) --------------------------------------------------------
int  Rules_AddBitmapValue(_BYTE *theBitMap, signed int size)
{
  int hashValue; // eax
  signed int *prevEntry; // ecx
  int curEntry; // edi
  int entrySize; // eax
  signed int compareCount; // eax
  _BYTE *srcPtr; // edx
  int entryData; // ecx
  int free_node; // edx
  signed int allocatedNode; // eax
  _DWORD *dataBuffer; // eax
  __int16 flagsWord; // dx
  int flagsDword; // ecx
  signed int copyIndex; // eax
  char *copySrc; // edx
  char byteValue; // bl
  int savedHash; // [esp+0h] [ebp-18h]

  if ( !theBitMap )
  {
    Rules_ReportSystemError(0, 2);
    IO_RunRouterExitCallbacks();
  }
  hashValue = Rules_HashBitmapValue((int)theBitMap, 0xA7u, size);
  curEntry = *(_DWORD *)(g_ClipsBitmapHashTable + 4 * hashValue);
  prevEntry = 0;
  savedHash = hashValue;
  if ( curEntry )
  {
    while ( 1 )
    {
      entrySize = *(unsigned __int16 *)(curEntry + 20);
      if ( (unsigned __int16)entrySize == size )
      {
        compareCount = size ^ entrySize;
        if ( size > 0 )
        {
          srcPtr = theBitMap;
          entryData = *(_DWORD *)(curEntry + 16);
          do
          {
            if ( *(_BYTE *)entryData != *srcPtr )
              break;
            ++srcPtr;
            ++compareCount;
            ++entryData;
          }
          while ( compareCount < size );
        }
        if ( compareCount == size )
          break;
      }
      prevEntry = (signed int *)curEntry;
      curEntry = *(_DWORD *)curEntry;
      if ( !curEntry )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_10:
    free_node = *(_DWORD *)(g_ClipsMemoryTable + 88);
    if ( free_node )
    {
      g_ClipsMemFreeListTemp = free_node;
      *(_DWORD *)(g_ClipsMemoryTable + 88) = *(_DWORD *)free_node;
      allocatedNode = g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedNode = Mem_HeapAllocWithRetry((_DWORD *)0x16);
    }
    curEntry = allocatedNode;
    if ( prevEntry )
      *prevEntry = allocatedNode;
    else
      *(_DWORD *)(g_ClipsBitmapHashTable + 4 * savedHash) = allocatedNode;
    dataBuffer = Mem_SmallBlockAlloc(size);
    *(_DWORD *)curEntry = 0;
    *(_DWORD *)(curEntry + 4) = 0;
    flagsWord = *(_WORD *)(curEntry + 12);
    *(_DWORD *)(curEntry + 16) = dataBuffer;
    *(_WORD *)(curEntry + 12) = flagsWord & 3;
    flagsDword = *(_DWORD *)(curEntry + 12);
    *(_WORD *)(curEntry + 20) = size;
    copyIndex = 0;
    *(_DWORD *)(curEntry + 12) = (4 * (savedHash & 0x3FFF)) | flagsDword;
    if ( size > 0 )
    {
      copySrc = theBitMap;
      do
      {
        ++copyIndex;
        byteValue = *copySrc++;
        *(_BYTE *)(*(_DWORD *)(curEntry + 16) + copyIndex - 1) = byteValue;
      }
      while ( copyIndex < size );
    }
    Rules_AddEphemeralHashNode(curEntry, &g_Rules_EphemeralBitmapListHead, 4, 22);
    *(_DWORD *)(curEntry + 8) = g_ClipsCurrentEvaluationDepth;
  }
  return curEntry;
}
// 482196: variable 'v5' is possibly undefined
// 51A274: using guessed type _DWORD dword_51A274;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00482260) --------------------------------------------------------
int *Rules_InitAtomTables(void)
{
  int v0; // ecx
  int i; // eax
  int j; // eax
  int k; // eax
  int m; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int *result; // eax

  g_Clips_SymbolHashTable = (int)Mem_SmallBlockAlloc(0xFD4u);
  g_ClipsFloatHashTable = (int)Mem_SmallBlockAlloc(0x7DCu);
  g_ClipsIntegerHashTable = (int)Mem_SmallBlockAlloc(0x29Cu);
  g_ClipsBitmapHashTable = (int)Mem_SmallBlockAlloc(0x29Cu);
  for ( i = 0; i != 4052; i += 4 )
    *(_DWORD *)(g_Clips_SymbolHashTable + i) = 0;
  for ( j = 0; j != 2012; j += 4 )
    *(_DWORD *)(g_ClipsFloatHashTable + j) = 0;
  for ( k = 0; k != 668; k += 4 )
    *(_DWORD *)(g_ClipsIntegerHashTable + k) = 0;
  for ( m = 0; m != 668; m += 4 )
    *(_DWORD *)(g_ClipsBitmapHashTable + m) = 0;
  g_ClipsTrueSymbol = (int)Str_Intern(aTrue, v0);
  ++*(_DWORD *)(g_ClipsTrueSymbol + 4);
  g_ClipsFalseSymbol = (int)Str_Intern(aFalse, v5);
  ++*(_DWORD *)(g_ClipsFalseSymbol + 4);
  g_ClipsPositiveInfinitySymbol = (int)Str_Intern(aOo, v6);
  ++*(_DWORD *)(g_ClipsPositiveInfinitySymbol + 4);
  g_Clips_NegativeInfinitySymbol = (int)Str_Intern(aOo_0, v7);
  ++*(_DWORD *)(g_Clips_NegativeInfinitySymbol + 4);
  result = Rules_AddIntegerValue(0);
  g_CLIPS_IntegerZeroValueNode = (int)result;
  ++result[1];
  return result;
}
// 48231C: variable 'v0' is possibly undefined
// 48232E: variable 'v5' is possibly undefined
// 482340: variable 'v6' is possibly undefined
// 482352: variable 'v7' is possibly undefined
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;
// 54DD60: using guessed type int dword_54DD60;
// 54DD64: using guessed type int dword_54DD64;
// 54DD68: using guessed type int dword_54DD68;
// 54DD6C: using guessed type int dword_54DD6C;
// 54DD70: using guessed type int dword_54DD70;

//----- (00482370) --------------------------------------------------------
int  Rules_HashSymbolName(_BYTE *word, unsigned int range)
{
  _BYTE *wordPtr; // edi
  unsigned int length; // ebp
  char currentChar; // dh
  int charIndex; // ecx
  signed int fullChunkCount; // ebp
  int *chunkDest; // eax
  char *chunkSrc; // edx
  int *chunkDestEnd; // esi
  char chunkByte; // bl
  char *tailSrc; // edi
  int *tailDest; // eax
  char tailByte; // dl
  signed int hashValue; // edx
  int chunkValue; // [esp+0h] [ebp-28h] BYREF
  unsigned int v17; // [esp+4h] [ebp-24h]
  int *chunkBuffer; // [esp+8h] [ebp-20h]
  int tally; // [esp+Ch] [ebp-1Ch]
  int chunkIndex; // [esp+10h] [ebp-18h]

  wordPtr = word;
  v17 = range;
  length = 0;
  tally = 0;
  chunkBuffer = &chunkValue;
  if ( *word )
  {
    do
    {
      currentChar = *++word;
      ++length;
    }
    while ( currentChar );
  }
  charIndex = 0;
  fullChunkCount = length >> 2;
  chunkIndex = 0;
  if ( fullChunkCount )
  {
    do
    {
      chunkDest = chunkBuffer;
      chunkSrc = &wordPtr[charIndex];
      chunkDestEnd = chunkBuffer + 1;
      do
      {
        chunkDest = (int *)((char *)chunkDest + 1);
        chunkByte = *chunkSrc++;
        ++charIndex;
        *((_BYTE *)chunkDest - 1) = chunkByte;
      }
      while ( chunkDest != chunkDestEnd );
      tally += chunkValue;
      ++chunkIndex;
    }
    while ( fullChunkCount > chunkIndex );
  }
  tailSrc = &wordPtr[charIndex];
  chunkValue = 0;
  if ( *tailSrc )
  {
    tailDest = chunkBuffer;
    do
    {
      tailByte = *tailSrc++;
      *(_BYTE *)tailDest = tailByte;
      tailDest = (int *)((char *)tailDest + 1);
    }
    while ( *tailSrc );
  }
  hashValue = (chunkValue + tally) % v17;
  tally += chunkValue;
  if ( hashValue < 0 )
    return -hashValue;
  else
    return hashValue;
}

//----- (00482440) --------------------------------------------------------
unsigned int __stdcall Rules_HashDoubleValue(unsigned int valueLowBits, int valueHighBits, unsigned int range)
{
  if ( ((valueLowBits % range) & 0x80000000) != 0 )
    return -(valueLowBits % range);
  else
    return valueLowBits % range;
}

//----- (00482480) --------------------------------------------------------
int  Rules_HashIntegerValue(signed int number, signed int range)
{
  int remainder; // edx

  remainder = number % range;
  if ( remainder < 0 )
    return -remainder;
  else
    return remainder;
}

//----- (004824A0) --------------------------------------------------------
int  Rules_HashBitmapValue(int bitMap, unsigned int range, unsigned int length)
{
  unsigned int tally; // edi
  signed int chunkIndex; // ebp
  signed int byteIndex; // ecx
  int *chunkDest; // eax
  int *chunkDestEnd; // esi
  char *chunkSrc; // edx
  char chunkByte; // bl
  int tailPtr; // eax
  int hashValue; // edx
  int chunkValue; // [esp+0h] [ebp-28h] BYREF
  unsigned int hashRange; // [esp+4h] [ebp-24h]
  int bitMapBase; // [esp+8h] [ebp-20h]
  signed int byteCount; // [esp+Ch] [ebp-1Ch]
  signed int fullChunkCount; // [esp+10h] [ebp-18h]
  int *chunkBuffer; // [esp+14h] [ebp-14h]

  bitMapBase = bitMap;
  hashRange = range;
  byteCount = length;
  tally = 0;
  chunkBuffer = &chunkValue;
  chunkIndex = 0;
  byteIndex = 0;
  fullChunkCount = length >> 2;
  if ( length >> 2 )
  {
    do
    {
      chunkDest = chunkBuffer;
      chunkDestEnd = chunkBuffer + 1;
      chunkSrc = (char *)(byteIndex + bitMapBase);
      do
      {
        chunkDest = (int *)((char *)chunkDest + 1);
        chunkByte = *chunkSrc++;
        ++byteIndex;
        *((_BYTE *)chunkDest - 1) = chunkByte;
      }
      while ( chunkDest != chunkDestEnd );
      ++chunkIndex;
      tally += chunkValue;
    }
    while ( chunkIndex < fullChunkCount );
  }
  tailPtr = byteIndex + bitMapBase;
  while ( byteIndex < byteCount )
  {
    ++tailPtr;
    ++byteIndex;
    tally += *(unsigned __int8 *)(tailPtr - 1);
  }
  hashValue = tally % hashRange;
  if ( ((tally % hashRange) & 0x80000000) != 0 )
    return -hashValue;
  return hashValue;
}
// 4824A0: could not find valid save-restore pair for ebx

//----- (00482530) --------------------------------------------------------
int  Rules_DecrementSymbolCount(int result, int a2)
{
  int theSymbol; // esi
  int newCount; // ebx

  theSymbol = result;
  if ( *(int *)(result + 4) < 0 )
  {
    Rules_ReportSystemError(a2, 3);
    result = IO_RunRouterExitCallbacks();
  }
  if ( !*(_DWORD *)(theSymbol + 4) )
  {
    Rules_ReportSystemError(a2, 4);
    result = IO_RunRouterExitCallbacks();
  }
  newCount = *(_DWORD *)(theSymbol + 4) - 1;
  *(_DWORD *)(theSymbol + 4) = newCount;
  if ( !newCount && (*(_BYTE *)(theSymbol + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(theSymbol, &g_Rules_EphemeralSymbolListHead, 10, 20);
  return result;
}
// 48254B: variable 'a2' is possibly undefined
// 51A268: using guessed type _DWORD dword_51A268;

//----- (004825B0) --------------------------------------------------------
int  Rules_DecrementFloatCount(int result, int a2)
{
  int theFloat; // esi
  int newCount; // ecx

  theFloat = result;
  if ( *(int *)(result + 4) <= 0 )
  {
    Rules_ReportSystemError(a2, 5);
    result = IO_RunRouterExitCallbacks();
  }
  newCount = *(_DWORD *)(theFloat + 4) - 1;
  *(_DWORD *)(theFloat + 4) = newCount;
  if ( !newCount && (*(_BYTE *)(theFloat + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(theFloat, &g_Rules_EphemeralFloatListHead, 0, 24);
  return result;
}
// 51A26C: using guessed type _DWORD dword_51A26C;

//----- (00482600) --------------------------------------------------------
int  Rules_DecrementIntegerCount(int result, int a2)
{
  int theInteger; // esi
  int newCount; // ecx

  theInteger = result;
  if ( *(int *)(result + 4) <= 0 )
  {
    Rules_ReportSystemError(a2, 6);
    result = IO_RunRouterExitCallbacks();
  }
  newCount = *(_DWORD *)(theInteger + 4) - 1;
  *(_DWORD *)(theInteger + 4) = newCount;
  if ( !newCount && (*(_BYTE *)(theInteger + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(theInteger, &g_Rules_EphemeralIntegerListHead, 0, 20);
  return result;
}
// 51A270: using guessed type _DWORD dword_51A270;

//----- (00482650) --------------------------------------------------------
int  Rules_DecrementBitmapCount(int result, int a2)
{
  int theBitMap; // esi
  int newCount; // ebx

  theBitMap = result;
  if ( *(int *)(result + 4) < 0 )
  {
    Rules_ReportSystemError(a2, 7);
    result = IO_RunRouterExitCallbacks();
  }
  if ( !*(_DWORD *)(theBitMap + 4) )
  {
    Rules_ReportSystemError(a2, 8);
    result = IO_RunRouterExitCallbacks();
  }
  newCount = *(_DWORD *)(theBitMap + 4) - 1;
  *(_DWORD *)(theBitMap + 4) = newCount;
  if ( !newCount && (*(_BYTE *)(theBitMap + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(theBitMap, &g_Rules_EphemeralBitmapListHead, 4, 22);
  return result;
}
// 48266B: variable 'a2' is possibly undefined
// 51A274: using guessed type _DWORD dword_51A274;

//----- (004826D0) --------------------------------------------------------
_DWORD * Rules_RemoveHashNode(int theValue, int theTable, int type, int size)
{
  _DWORD *curEntry; // ecx
  _DWORD *prevEntry; // edi
  _DWORD *result; // eax

  curEntry = *(_DWORD **)(theTable + 4 * (*(_DWORD *)(theValue + 12) << 16 >> 18));
  prevEntry = 0;
  while ( curEntry != (_DWORD *)theValue )
  {
    prevEntry = curEntry;
    curEntry = (_DWORD *)*curEntry;
    if ( !curEntry )
    {
      Rules_ReportSystemError(0, 9);
      IO_RunRouterExitCallbacks();
    }
  }
  if ( prevEntry )
    *prevEntry = *curEntry;
  else
    *(_DWORD *)(4 * (*(_DWORD *)(theValue + 12) << 16 >> 18) + theTable) = *(_DWORD *)theValue;
  if ( type == 2 )
  {
    Mem_SmallBlockFree(*(_DWORD **)(theValue + 16), strlen(*(const char **)(theValue + 16)) + 1);
  }
  else if ( type == 19 )
  {
    Mem_SmallBlockFree(*(_DWORD **)(theValue + 16), *(unsigned __int16 *)(theValue + 20));
  }
  g_ClipsMemFreeListTemp = theValue;
  *(_DWORD *)theValue = *(_DWORD *)(g_ClipsMemoryTable + 4 * size);
  result = (_DWORD *)(g_ClipsMemoryTable + 4 * size);
  *result = g_ClipsMemFreeListTemp;
  return result;
}
// 4826FA: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004827B0) --------------------------------------------------------
int  Rules_AddEphemeralHashNode(int theHashNode, _DWORD *theEphemeralList, int averageContentsSize, int hashNodeSize)
{
  int free_node; // ebp
  int link_node; // eax
  int result; // eax

  if ( *(_DWORD *)(theHashNode + 4) )
  {
    Rules_ReportSystemError(averageContentsSize, 10);
    IO_RunRouterExitCallbacks();
  }
  *(_BYTE *)(theHashNode + 12) |= 1u;
  free_node = *(_DWORD *)(g_ClipsMemoryTable + 32);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = free_node;
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *(_DWORD *)free_node;
    link_node = g_ClipsMemFreeListTemp;
  }
  else
  {
    link_node = Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *(_DWORD *)link_node = theHashNode;
  *(_DWORD *)(link_node + 4) = *theEphemeralList;
  *theEphemeralList = link_node;
  result = ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += hashNodeSize + 8 + averageContentsSize;
  return result;
}
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00482830) --------------------------------------------------------
int Rules_RemoveEphemeralAtoms(void)
{
  Rules_RemoveEphemeralHashNodes((uintptr_t)&g_Rules_EphemeralSymbolListHead, (uintptr_t)(unsigned int)g_Clips_SymbolHashTable, 2, 20, 10);
  Rules_RemoveEphemeralHashNodes((uintptr_t)&g_Rules_EphemeralFloatListHead, (uintptr_t)(unsigned int)g_ClipsFloatHashTable, 0, 24, 0);
  Rules_RemoveEphemeralHashNodes((uintptr_t)&g_Rules_EphemeralIntegerListHead, (uintptr_t)(unsigned int)g_ClipsIntegerHashTable, 1, 20, 0);
  return Rules_RemoveEphemeralHashNodes((uintptr_t)&g_Rules_EphemeralBitmapListHead, (uintptr_t)(unsigned int)g_ClipsBitmapHashTable, 19, 22, 4);
}
// 51A268: using guessed type _DWORD dword_51A268;
// 51A26C: using guessed type _DWORD dword_51A26C;
// 51A270: using guessed type _DWORD dword_51A270;
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (004828B0) --------------------------------------------------------
int  Rules_RemoveEphemeralHashNodes(uintptr_t result, uintptr_t theTable, int hashNodeType, int hashNodeSize, int averageContentsSize)
{
  uintptr_t node; // esi
  uintptr_t previous; // ebp
  uintptr_t object; // eax
  uintptr_t next; // edi
  int node_charge; // [esp+10h] [ebp-10h]

  node = (uintptr_t)(unsigned int)*(_DWORD *)result;
  previous = 0;
  if ( node )
  {
    node_charge = hashNodeSize + 8 + averageContentsSize;
    do
    {
      object = (uintptr_t)(unsigned int)*(_DWORD *)node;
      next = (uintptr_t)(unsigned int)*(_DWORD *)(node + 4);
      if ( !*(_DWORD *)(object + 4) && g_ClipsCurrentEvaluationDepth < *(_DWORD *)(object + 8) )
      {
        Rules_RemoveHashNode((int)object, (int)theTable, hashNodeType, hashNodeSize);
        g_ClipsMemFreeListTemp = (int)node;
        *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        if ( previous )
          *(_DWORD *)(previous + 4) = (int)next;
        else
          *(_DWORD *)result = (int)next;
        --g_ClipsEphemeralItemCount;
        g_ClipsEphemeralItemBytes -= node_charge;
        node = next;
        continue;
      }
      if ( *(int *)(object + 4) > 0 )
      {
        *(_BYTE *)(object + 12) &= ~1u;
        g_ClipsMemFreeListTemp = (int)node;
        *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        if ( previous )
          *(_DWORD *)(previous + 4) = (int)next;
        else
          *(_DWORD *)result = (int)next;
        --g_ClipsEphemeralItemCount;
        g_ClipsEphemeralItemBytes -= node_charge;
        node = next;
      }
      else
      {
        previous = node;
        node = next;
      }
    }
    while ( node );
  }
  return hashNodeSize + 8 + averageContentsSize;
}
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004829F0) --------------------------------------------------------
int Rules_GetSymbolTable(void)
{
  return g_Clips_SymbolHashTable;
}
// 54DD50: using guessed type int dword_54DD50;

//----- (00482A10) --------------------------------------------------------
int Rules_GetFloatTable(void)
{
  return g_ClipsFloatHashTable;
}
// 54DD58: using guessed type int dword_54DD58;

//----- (00482A30) --------------------------------------------------------
int Rules_GetIntegerTable(void)
{
  return g_ClipsIntegerHashTable;
}
// 54DD54: using guessed type int dword_54DD54;

//----- (00482A50) --------------------------------------------------------
int Rules_GetBitmapTable(void)
{
  return g_ClipsBitmapHashTable;
}
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00482B80) --------------------------------------------------------
int  Mem_AllocArray(_BYTE *buffer, int size)
{
  int result; // eax
  _BYTE *writePtr; // edx

  result = 0;
  if ( size > 0 )
  {
    writePtr = buffer;
    do
    {
      ++result;
      *writePtr++ = 0;
    }
    while ( result < size );
  }
  return result;
}

//----- (00482BB0) --------------------------------------------------------
int ** Rules_GetNextSymbolMatch(int **searchString, int length, int anywhere, int ***prevSymbol, int *commonPrefix)
{
  int **curSymbol; // ebx
  int *symbolName; // eax
  int prevBucketIndex; // eax
  int **compareString; // eax
  int prefixLength; // eax
  int nextBucketOffset; // edx
  int bucketOffset; // [esp+0h] [ebp-1Ch]
  int bucketIndex; // [esp+8h] [ebp-14h]

  if ( anywhere && commonPrefix )
    *commonPrefix = 0;
  if ( prevSymbol )
  {
    prevBucketIndex = (_DWORD)prevSymbol[3] << 16 >> 18;
    curSymbol = *prevSymbol;
    bucketIndex = prevBucketIndex;
  }
  else
  {
    bucketIndex = 0;
    curSymbol = *(int ***)g_Clips_SymbolHashTable;
  }
  bucketOffset = 4 * bucketIndex;
  while ( 1 )
  {
    while ( !curSymbol )
    {
      nextBucketOffset = bucketOffset + 4;
      bucketOffset = nextBucketOffset;
      ++bucketIndex;
      if ( nextBucketOffset >= 4052 )
        return 0;
      curSymbol = *(int ***)(nextBucketOffset + g_Clips_SymbolHashTable);
    }
    symbolName = curSymbol[4];
    if ( *(_BYTE *)symbolName != 40 && ((_BYTE)curSymbol[3] & 1) == 0 )
      break;
LABEL_9:
    curSymbol = (int **)*curSymbol;
  }
  if ( anywhere )
  {
    if ( Rules_StringWithinString(symbolName, searchString) )
      return curSymbol;
    goto LABEL_9;
  }
  if ( prevSymbol )
    compareString = prevSymbol[4];
  else
    compareString = searchString;
  prefixLength = Rules_CommonPrefixLength(compareString, curSymbol[4]);
  if ( prefixLength < length )
    goto LABEL_9;
  if ( commonPrefix )
  {
    if ( prevSymbol )
    {
      if ( prefixLength < *commonPrefix )
        *commonPrefix = prefixLength;
    }
    else
    {
      *commonPrefix = strlen((const char *)curSymbol[4]);
    }
  }
  return curSymbol;
}
// 482BFD: conditional instruction was optimized away because %var_18.4==1
// 54DD50: using guessed type int dword_54DD50;

//----- (00482CD0) --------------------------------------------------------
_BYTE * Rules_StringWithinString(_BYTE *str, _BYTE *withinStr)
{
  _BYTE *scanPtr; // ebp
  int offset; // esi
  _BYTE *patternPtr; // eax
  int matchLength; // ecx
  _BYTE *strPtr; // edx
  char patternChar; // bh
  char scanChar; // dh

  scanPtr = str;
  offset = 0;
  if ( !*str )
    return 0;
  while ( 1 )
  {
    patternPtr = withinStr;
    matchLength = 0;
    strPtr = &str[offset];
    if ( *withinStr )
    {
      do
      {
        if ( *strPtr != *patternPtr )
          break;
        ++strPtr;
        patternChar = *++patternPtr;
        ++matchLength;
      }
      while ( patternChar );
    }
    if ( !withinStr[matchLength] && matchLength )
      break;
    scanChar = *++scanPtr;
    ++offset;
    if ( !scanChar )
      return 0;
  }
  return &str[offset];
}

//----- (00482D40) --------------------------------------------------------
int  Rules_CommonPrefixLength(_BYTE *str1, _BYTE *str2)
{
  int prefixLength; // ecx
  char currentChar; // bl

  prefixLength = 0;
  if ( *str1 )
  {
    do
    {
      if ( !*str2 )
        break;
      if ( *str2 != *str1 )
        break;
      ++str2;
      currentChar = *++str1;
      ++prefixLength;
    }
    while ( currentChar );
  }
  return prefixLength;
}
