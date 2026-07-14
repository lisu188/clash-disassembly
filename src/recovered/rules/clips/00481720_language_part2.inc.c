/* CLIPS lexer, parser, expressions, and procedural language support, continued.
 * Original function-marker range: 0x00481720..0x00491530.
 * Included by clash95.c; not a standalone translation unit. */

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
int *Rules_InitAtomTables()
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
int Rules_RemoveEphemeralAtoms()
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
int Rules_GetSymbolTable()
{
  return g_Clips_SymbolHashTable;
}
// 54DD50: using guessed type int dword_54DD50;

//----- (00482A10) --------------------------------------------------------
int Rules_GetFloatTable()
{
  return g_ClipsFloatHashTable;
}
// 54DD58: using guessed type int dword_54DD58;

//----- (00482A30) --------------------------------------------------------
int Rules_GetIntegerTable()
{
  return g_ClipsIntegerHashTable;
}
// 54DD54: using guessed type int dword_54DD54;

//----- (00482A50) --------------------------------------------------------
int Rules_GetBitmapTable()
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

//----- (00482D70) --------------------------------------------------------
int  Rules_SetAtomicValueIndices(int setAll)
{
  int symbolIndex; // ecx
  int **symbolBucket; // esi
  int symbolTableEnd; // edi
  int *i; // eax
  int symbolFlags; // ebp
  int floatIndex; // ecx
  int **floatBucket; // esi
  int floatTableEnd; // edi
  int *j; // eax
  int floatFlags; // ebp
  int integerIndex; // ecx
  int **integerBucket; // esi
  int integerTableEnd; // edi
  int *k; // eax
  int integerFlags; // ebp
  int bitmapIndex; // ecx
  int *bitmapBucket; // esi
  int bitmapTableEnd; // edi
  int result; // eax
  int bitmapFlags; // ebp

  symbolIndex = 0;
  symbolBucket = (int **)g_Clips_SymbolHashTable;
  symbolTableEnd = g_Clips_SymbolHashTable + 4052;
  do
  {
    for ( i = *symbolBucket; i; i = (int *)*i )
    {
      if ( (i[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)i + 13) = 0;
        *((_BYTE *)i + 12) &= 3u;
        symbolFlags = (4 * (symbolIndex++ & 0x3FFF)) | i[3];
        i[3] = symbolFlags;
      }
    }
    ++symbolBucket;
  }
  while ( symbolBucket != (int **)symbolTableEnd );
  floatIndex = 0;
  floatBucket = (int **)g_ClipsFloatHashTable;
  floatTableEnd = g_ClipsFloatHashTable + 2012;
  do
  {
    for ( j = *floatBucket; j; j = (int *)*j )
    {
      if ( (j[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)j + 13) = 0;
        *((_BYTE *)j + 12) &= 3u;
        floatFlags = (4 * (floatIndex++ & 0x3FFF)) | j[3];
        j[3] = floatFlags;
      }
    }
    ++floatBucket;
  }
  while ( floatBucket != (int **)floatTableEnd );
  integerIndex = 0;
  integerBucket = (int **)g_ClipsIntegerHashTable;
  integerTableEnd = g_ClipsIntegerHashTable + 668;
  do
  {
    for ( k = *integerBucket; k; k = (int *)*k )
    {
      if ( (k[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)k + 13) = 0;
        *((_BYTE *)k + 12) &= 3u;
        integerFlags = (4 * (integerIndex++ & 0x3FFF)) | k[3];
        k[3] = integerFlags;
      }
    }
    ++integerBucket;
  }
  while ( integerBucket != (int **)integerTableEnd );
  bitmapIndex = 0;
  bitmapBucket = (int *)g_ClipsBitmapHashTable;
  bitmapTableEnd = g_ClipsBitmapHashTable + 668;
  do
  {
    for ( result = *bitmapBucket; result; result = *(_DWORD *)result )
    {
      if ( (*(_BYTE *)(result + 12) & 2) != 0 || setAll )
      {
        *(_BYTE *)(result + 13) = 0;
        *(_BYTE *)(result + 12) &= 3u;
        bitmapFlags = (4 * (bitmapIndex++ & 0x3FFF)) | *(_DWORD *)(result + 12);
        *(_DWORD *)(result + 12) = bitmapFlags;
      }
    }
    ++bitmapBucket;
  }
  while ( bitmapBucket != (int *)bitmapTableEnd );
  return result;
}
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00482EF0) --------------------------------------------------------
int *Rules_RestoreAtomicValueBuckets()
{
  _DWORD *symbolBucket; // ebx
  int i; // ecx
  _DWORD *symbolNode; // eax
  unsigned int symbolFlags; // ebp
  _DWORD *floatBucket; // ebx
  int j; // ecx
  _DWORD *floatNode; // eax
  unsigned int floatFlags; // ebp
  _DWORD *integerBucket; // ebx
  int k; // ecx
  _DWORD *integerNode; // eax
  unsigned int integerFlags; // ebp
  int *bitmapBucket; // ebx
  int m; // ecx
  int *result; // eax
  unsigned int bitmapFlags; // ebp

  symbolBucket = (_DWORD *)g_Clips_SymbolHashTable;
  for ( i = 0; i < 1013; ++i )
  {
    symbolNode = (_DWORD *)*symbolBucket;
    if ( *symbolBucket )
    {
      do
      {
        symbolFlags = symbolNode[3] & 0xFFFF0003;
        symbolNode[3] = symbolFlags;
        symbolNode[3] = (4 * (i & 0x3FFF)) | symbolFlags;
        symbolNode = (_DWORD *)*symbolNode;
      }
      while ( symbolNode );
    }
    ++symbolBucket;
  }
  floatBucket = (_DWORD *)g_ClipsFloatHashTable;
  for ( j = 0; j < 503; ++j )
  {
    floatNode = (_DWORD *)*floatBucket;
    if ( *floatBucket )
    {
      do
      {
        floatFlags = floatNode[3] & 0xFFFF0003;
        floatNode[3] = floatFlags;
        floatNode[3] = (4 * (j & 0x3FFF)) | floatFlags;
        floatNode = (_DWORD *)*floatNode;
      }
      while ( floatNode );
    }
    ++floatBucket;
  }
  integerBucket = (_DWORD *)g_ClipsIntegerHashTable;
  for ( k = 0; k < 167; ++k )
  {
    integerNode = (_DWORD *)*integerBucket;
    if ( *integerBucket )
    {
      do
      {
        integerFlags = integerNode[3] & 0xFFFF0003;
        integerNode[3] = integerFlags;
        integerNode[3] = (4 * (k & 0x3FFF)) | integerFlags;
        integerNode = (_DWORD *)*integerNode;
      }
      while ( integerNode );
    }
    ++integerBucket;
  }
  bitmapBucket = (int *)g_ClipsBitmapHashTable;
  for ( m = 0; m < 167; ++m )
  {
    result = (int *)*bitmapBucket;
    if ( *bitmapBucket )
    {
      do
      {
        bitmapFlags = result[3] & 0xFFFF0003;
        result[3] = bitmapFlags;
        result[3] = (4 * (m & 0x3FFF)) | bitmapFlags;
        result = (int *)*result;
      }
      while ( result );
    }
    ++bitmapBucket;
  }
  return result;
}
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00483040) --------------------------------------------------------
int  Rules_IncrementRefCountField40(int result)
{
  ++*(_DWORD *)(result + 40);
  return result;
}

//----- (00483050) --------------------------------------------------------
int  Instance_DecrementBusyCount(int result)
{
  --*(_DWORD *)(result + 40);
  return result;
}

//----- (00483060) --------------------------------------------------------
int Instance_InitHashTable()
{
  int result; // eax

  g_Instance_HashTableBase = (int)Mem_SmallBlockAlloc(0xAACu);
  for ( result = 0; result != 2732; result += 4 )
    *(_DWORD *)(g_Instance_HashTableBase + result) = 0;
  return result;
}
// 51A278: using guessed type int dword_51A278;

//----- (004830A0) --------------------------------------------------------
void Instance_PurgeDeletedInstances()
{
  int current_node; // edx
  int previous_node; // ecx
  int object_record; // eax
  int next_node; // eax

  if ( !g_Instance_PurgeInProgress )
  {
    current_node = g_Instance_DeletedListHead;
    previous_node = 0;
    while ( current_node )
    {
      object_record = *(_DWORD *)(uintptr_t)(unsigned int)current_node;
      if ( *(_DWORD *)(object_record + 40)
        || g_ClipsCurrentEvaluationDepth >= *(_DWORD *)(object_record + 32)
        || *(_DWORD *)(object_record + 8) )
      {
        previous_node = current_node;
        current_node = *(_DWORD *)(uintptr_t)(unsigned int)(current_node + 4);
        continue;
      }

      g_ClipsEphemeralItemCount -= 2;
      g_ClipsEphemeralItemBytes -= 88;
      Rules_DecrementSymbolCount(*(_DWORD *)(object_record + 28), previous_node);

      g_ClipsMemFreeListTemp = object_record;
      *(_DWORD *)(uintptr_t)(unsigned int)object_record = *(_DWORD *)(g_ClipsMemoryTable + 320);
      *(_DWORD *)(g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;

      next_node = *(_DWORD *)(uintptr_t)(unsigned int)(current_node + 4);
      if ( previous_node )
        *(_DWORD *)(uintptr_t)(unsigned int)(previous_node + 4) = next_node;
      else
        g_Instance_DeletedListHead = next_node;

      g_ClipsMemFreeListTemp = current_node;
      *(_DWORD *)(uintptr_t)(unsigned int)current_node = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      current_node = next_node;
    }
  }
}
// 51A280: using guessed type int dword_51A280;
// 51A28C: using guessed type int dword_51A28C;
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00483190) --------------------------------------------------------
unsigned int  Instance_HashNameToBucket(int instanceName)
{
  return 11329 * (*(_DWORD *)(instanceName + 12) << 16 >> 18) % 0x2ABu;
}

//----- (004831B0) --------------------------------------------------------
int  Instance_PrintClassInstanceSummary(double a1)
{
  int savedPurgeFlag; // edi
  _DWORD *i; // esi
  int v3; // edx
  int v4; // ecx

  Module_BeginEnum();
  savedPurgeFlag = g_Instance_PurgeInProgress;
  i = (_DWORD *)g_Clips_InstanceListHead;
  g_Instance_PurgeInProgress = 1;
  if ( g_Clips_InstanceListHead )
  {
    do
    {
      Module_SetCurrent(**(_DWORD **)(i[11] + 8));
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, v3, v4, 0, a1);
      for ( i = (_DWORD *)i[17]; i; i = (_DWORD *)i[17] )
      {
        if ( (i[6] & 2) == 0 )
          break;
      }
    }
    while ( i );
  }
  g_Instance_PurgeInProgress = savedPurgeFlag;
  return Module_EndEnum();
}
// 4831F0: variable 'v3' is possibly undefined
// 4831F0: variable 'v4' is possibly undefined
// 51A280: using guessed type int dword_51A280;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD38: using guessed type int dword_51AD38;

//----- (00483230) --------------------------------------------------------
signed int  Instance_ReleaseSlotValues(int theInstance)
{
  uintptr_t instance; // edi
  uintptr_t class_record; // eax
  unsigned int slot_index; // ebx
  unsigned int slot_offset; // esi
  signed int result; // eax
  unsigned int slot_count; // edx
  uintptr_t slot_value; // ecx
  uintptr_t slot_descriptor; // eax
  int shared_ref_count; // ebp
  unsigned int local_slot_count; // ebx

  instance = (uintptr_t)(unsigned int)theInstance;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  Class_ReleaseBusyReference((int)class_record);
  slot_index = 0;
  slot_offset = 0;
  while ( 1 )
  {
    class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
    slot_count = *(_DWORD *)(class_record + 72);
    if ( slot_index >= slot_count )
      break;
    slot_value = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 72) + slot_offset);
    slot_descriptor = (uintptr_t)(unsigned int)*(_DWORD *)slot_value;
    if ( slot_value == slot_descriptor + 32 )
    {
      shared_ref_count = *(_DWORD *)(slot_descriptor + 24) - 1;
      *(_DWORD *)(slot_descriptor + 24) = shared_ref_count;
      if ( shared_ref_count )
        goto next_slot;
    }
    if ( (*(_BYTE *)slot_descriptor & 2) != 0 )
    {
      Rules_DeinstallMultifield((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot_value + 8));
      Rules_RegisterEphemeralMultifield(*(_DWORD *)(slot_value + 8));
    }
    else
    {
      Rules_AtomDeinstall(*(_DWORD *)(slot_value + 4) << 24 >> 26, (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot_value + 8), (int)slot_value);
    }
    *(_DWORD *)(slot_value + 8) = 0;
next_slot:
    slot_offset += 4;
    ++slot_index;
  }
  result = 0;
  if ( slot_count )
  {
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(instance + 72), 4 * slot_count);
    local_slot_count = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 44) + 68);
    if ( local_slot_count )
      result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(instance + 76), 12 * local_slot_count);
  }
  *(_DWORD *)(instance + 76) = 0;
  *(_DWORD *)(instance + 72) = 0;
  return result;
}

//----- (00483300) --------------------------------------------------------
_DWORD * Instance_FindByName(int instanceName)
{
  int current_module; // ebp
  signed int qualifier_length; // eax
  int name_text; // edx
  int local_symbol; // eax
  signed int *module_symbol; // eax
  int module_record; // esi

  current_module = Module_GetCurrent();
  name_text = *(_DWORD *)((uintptr_t)(unsigned int)instanceName + 16);
  if ( getenv("CLASH95_TRACE_PARSER_QUALIFIER_SCAN") )
  {
    fprintf(
      stderr,
      "[parser] fact-lookup symbol=%08x tag=%04x flags=%04x name=%08x caller=%p\n",
      instanceName,
      *(unsigned short *)(uintptr_t)(unsigned int)instanceName,
      *(unsigned short *)((uintptr_t)(unsigned int)instanceName + 12),
      name_text,
      __builtin_return_address(0));
    fflush(stderr);
  }
  qualifier_length = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)name_text);
  if ( !qualifier_length )
    return Instance_LookupInHashBucket(instanceName, current_module, 0, current_module);
  if ( qualifier_length == 1 )
  {
    local_symbol = (int)(uintptr_t)Rules_ExtractConstructName(1, (char *)(uintptr_t)(unsigned int)name_text, 1);
    return Instance_LookupInHashBucket(local_symbol, current_module, (_DWORD *)1, current_module);
  }
  else
  {
    module_symbol = Rules_ExtractModuleName(qualifier_length);
    module_record = module_symbol
                  ? (int)(uintptr_t)Module_FindByName((_BYTE *)(uintptr_t)(unsigned int)module_symbol[4])
                  : 0;
    local_symbol = (int)(uintptr_t)Rules_ExtractConstructName(
                                      qualifier_length,
                                      (char *)(uintptr_t)(unsigned int)name_text,
                                      qualifier_length);
    if ( module_record )
      return Instance_LookupInHashBucket(local_symbol, module_record, 0, current_module);
    else
      return 0;
  }
}

//----- (00483390) --------------------------------------------------------
_DWORD * Instance_LookupInHashBucket(int instanceName, int theModule, _DWORD *searchImports, int currentModule)
{
  int instance; // ebx
  int current; // ecx
  int class_record; // eax
  unsigned int bucket_index; // edx

  bucket_index = 11329 * ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instanceName + 12) << 16 >> 18) % 0x2ABu;
  instance = *(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket_index);
  while ( instance )
  {
    if ( instanceName == *(_DWORD *)((uintptr_t)(unsigned int)instance + 28) )
      break;
    instance = *(_DWORD *)((uintptr_t)(unsigned int)instance + 60);
  }
  if ( !instance )
    return 0;
  current = instance;
  do
  {
    if ( *(_DWORD *)((uintptr_t)(unsigned int)current + 28) != *(_DWORD *)((uintptr_t)(unsigned int)instance + 28) )
      break;
    class_record = *(_DWORD *)((uintptr_t)(unsigned int)current + 44);
    if ( theModule == *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)class_record + 8)
      && Class_IsInScope(class_record, currentModule) )
      return (_DWORD *)(uintptr_t)(unsigned int)current;
    current = *(_DWORD *)((uintptr_t)(unsigned int)current + 60);
  }
  while ( current );
  if ( searchImports )
  {
    Rules_ClearModuleSearchMarkers();
    return Instance_FindInSubclasses(theModule, (_DWORD *)(uintptr_t)(unsigned int)instance);
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (00483440) --------------------------------------------------------
int  Instance_GetSlotValueBySymbol(int theInstance, int slotName)
{
  unsigned int slot_index; // eax
  int class_record; // eax
  int slot_value_table; // eax

  class_record = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 44);
  slot_index = Instance_ResolveSlotIndex(class_record, slotName);
  if ( slot_index == (unsigned int)-1 )
    return 0;
  slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 72);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_value_table + 4 * slot_index);
}

//----- (00483470) --------------------------------------------------------
unsigned int __fastcall Instance_ResolveSlotIndex(int theClass, int slotName)
{
  unsigned int slot_id; // eax
  int slot_index_table; // eax

  slot_id = Class_FindSlotNameID(slotName);
  if ( slot_id == (unsigned int)-1 )
    return slot_id;
  if ( slot_id > *(_DWORD *)((uintptr_t)(unsigned int)theClass + 76) )
    return (unsigned int)-1;
  slot_index_table = *(_DWORD *)((uintptr_t)(unsigned int)theClass + 60);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_index_table + 4 * slot_id) - 1;
}

//----- (004834A0) --------------------------------------------------------
BOOL  Parser_ParseSlotDefaultOrRestriction(int mfp, int theExp, _DWORD *val, double a4)
{
  val[1] = 4;
  val[3] = 0;
  val[4] = -1;
  if ( theExp )
  {
    if ( mfp || *(_DWORD *)(theExp + 10) )
    {
      Rules_StoreEvaluatedNodesAsMultifield(val, theExp, 1, a4);
      return g_ClipsEvaluationError == 0;
    }
    else
    {
      Parser_ParseForm((__int16 *)theExp, val, (int)val, a4);
      return g_ClipsEvaluationError == 0;
    }
  }
  else
  {
    val[2] = Rules_CreateEphemeralMultifield(0);
    return 1;
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (00483520) --------------------------------------------------------
signed int  Instance_PutSlotValue(_DWORD *ins, int *sp, _DWORD *val, double a4)
{
  signed int result; // eax

  result = Instance_ValidateSlotValueConstraints(val, *sp, (int)ins);
  if ( result )
    return Instance_StoreSlotValueAndMatch(ins, sp, 0, (uintptr_t)val, a4);
  return result;
}

//----- (00483550) --------------------------------------------------------
signed int  Instance_StoreSlotValueAndMatch(_DWORD *ins, int *sp, __int16 a3, uintptr_t val, double a5)
{
  int savedSlotEntry; // eax
  int sourceSlotFlags; // edx
  __int16 v8; // cx
  int valueType; // eax
  int valueField; // eax
  int v11; // ecx
  char *slotScopeText; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int slotDesc; // eax
  signed int traversalID; // eax
  int v21; // ecx
  int v22; // ecx
  char flagBits; // dh
  int fieldIndex; // edi
  int destOffset; // eax
  int srcOffset; // edx
  int fieldValue; // ecx
  _DWORD *newSegment; // eax
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int classNameText; // eax
  int v33; // ecx
  int srcFieldIndex; // [esp+Ch] [ebp-Ch]

  if ( !val )
  {
    Rules_ReportSystemError(a3, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( g_Rules_JoinOperationInProgress
    && (*(_BYTE *)(*sp + 1) & 2) != 0
    && ((*(_BYTE *)(ins[11] + 20) & 8) != 0 || (*(_BYTE *)*sp & 1) != 0) )
  {
    Rules_PrintErrorID((int)aInsfun, 5, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotModifyRe, v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternMatchin, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
    if ( ins[5] )
    {
      savedSlotEntry = ins[5]
         + 12 * ((4 * (*(_DWORD *)(*(_DWORD *)(ins[11] + 60) + 4 * *(_DWORD *)(*(_DWORD *)(*sp + 8) + 8)) - 1)) >> 2);
      if ( !*(_DWORD *)(savedSlotEntry + 8) )
      {
        LOBYTE(a3) = *(_BYTE *)(savedSlotEntry + 4) & 3;
        sourceSlotFlags = sp[1];
        *(_BYTE *)(savedSlotEntry + 4) = a3;
        *(_DWORD *)(savedSlotEntry + 4) |= sourceSlotFlags & 0xFC;
        *(_DWORD *)(savedSlotEntry + 8) = sp[2];
        if ( (*(_BYTE *)*sp & 2) != 0 )
          Rules_InstallMultifield(*(__int16 **)(savedSlotEntry + 8));
        else
          Rules_AtomInstall(*(_DWORD *)(savedSlotEntry + 4) << 24 >> 26, *(_DWORD *)(savedSlotEntry + 8), a3);
      }
    }
    if ( (*(_BYTE *)*sp & 2) != 0 )
    {
      Rules_DeinstallMultifield((__int16 *)sp[2]);
      Rules_RegisterEphemeralMultifield(sp[2]);
      flagBits = sp[1] & 3;
      *((_BYTE *)sp + 4) = flagBits;
      *((_BYTE *)sp + 4) = flagBits | 0x10;
      if ( *(_DWORD *)(val + 4) == 4 )
      {
        sp[2] = (int)Rules_CreateMultifield(*(_DWORD *)(val + 16) - *(_DWORD *)(val + 12) + 1);
        fieldIndex = 1;
        srcFieldIndex = *(_DWORD *)(val + 12) + 1;
        destOffset = 0;
        srcOffset = 6 * srcFieldIndex - 6;
        while ( fieldIndex <= *(_DWORD *)(val + 16) - *(_DWORD *)(val + 12) + 1 )
        {
          *(_WORD *)(destOffset + sp[2] + 14) = *(_WORD *)(srcOffset + *(_DWORD *)(val + 8) + 14);
          ++fieldIndex;
          fieldValue = *(_DWORD *)(*(_DWORD *)(val + 8) + srcOffset + 16);
          srcOffset += 6;
          *(_DWORD *)(destOffset + sp[2] + 16) = fieldValue;
          destOffset += 6;
          ++srcFieldIndex;
        }
      }
      else
      {
        newSegment = Rules_CreateMultifield(1);
        sp[2] = (int)newSegment;
        *((_WORD *)newSegment + 7) = *(_WORD *)(val + 4);
        *(_DWORD *)(sp[2] + 16) = *(_DWORD *)(val + 8);
      }
      Rules_InstallMultifield((__int16 *)sp[2]);
    }
    else
    {
      Rules_AtomDeinstall((unsigned int)(sp[1] << 24) >> 26, (__int16 *)sp[2], a3);
      HIBYTE(v8) = sp[1] & 3;
      valueType = *(_DWORD *)(val + 4) & 0x3F;
      *((_BYTE *)sp + 4) = HIBYTE(v8);
      sp[1] |= 4 * valueType;
      valueField = *(_DWORD *)(val + 8);
      sp[2] = valueField;
      Rules_AtomInstall((unsigned int)(sp[1] << 24) >> 26, valueField, v8);
    }
    if ( (*(_BYTE *)(ins[11] + 20) & 0x20) != 0 )
    {
      if ( (*(_BYTE *)*sp & 1) != 0 )
        slotScopeText = aSharedSlot;
      else
        slotScopeText = aLocalSlot;
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)slotScopeText, v11);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*sp + 8) + 12) + 16), v13);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aInInstance, v14);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(ins[7] + 16), v15);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_503AF0, v16);
      if ( (sp[1] & 0xFC) == 0x10 )
        Lexer_OutputFieldRange((int)g_IO_LogicalNameTable_WTrace[0], sp[2], *(_DWORD *)(sp[2] + 6) - 1, 0, 1);
      else
        Rules_PrintAtomValue((int)g_IO_LogicalNameTable_WTrace[0], (unsigned int)(sp[1] << 24) >> 26, (int *)sp[2]);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_503AF8, v17);
    }
    g_Instance_InstancesChangedFlag = 1;
    if ( (*(_BYTE *)(ins[11] + 20) & 8) == 0 )
      return 1;
    slotDesc = *sp;
    if ( (*(_BYTE *)(*sp + 1) & 2) == 0 )
      return 1;
    if ( (*(_BYTE *)slotDesc & 1) != 0 )
    {
      traversalID = Class_NewTraversalID();
      if ( traversalID != -1 )
      {
        Rules_MarkObjectPatternNetworkTraversal(traversalID, *(_DWORD *)(*sp + 4), *sp, a5);
        Class_ReleaseTraversalID();
        return 1;
      }
      Rules_PrintErrorID((int)aInsfun, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToPatter, v29);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*sp + 8) + 12) + 16), v30);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInClass, v31);
      classNameText = Rules_GetConstructNameString(*(_DWORD *)(*sp + 4));
      Output_Write((int)g_IO_LogicalNameTable_WError[0], classNameText, (int)g_IO_LogicalNameTable_WError[0]);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v33);
      return 1;
    }
    else
    {
      Rules_ObjectMatchAction((unsigned __int16 *)3, ins, *(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 8), a5);
      return 1;
    }
  }
}
// 483628: variable 'a3' is possibly undefined
// 483657: variable 'v8' is possibly undefined
// 483682: variable 'v11' is possibly undefined
// 483697: variable 'v13' is possibly undefined
// 4836A6: variable 'v14' is possibly undefined
// 4836BA: variable 'v15' is possibly undefined
// 4836C9: variable 'v16' is possibly undefined
// 4836FF: variable 'v17' is possibly undefined
// 48378F: variable 'v21' is possibly undefined
// 48379E: variable 'v22' is possibly undefined
// 4838E3: variable 'v29' is possibly undefined
// 4838F8: variable 'v30' is possibly undefined
// 483907: variable 'v31' is possibly undefined
// 48392F: variable 'v33' is possibly undefined
// 51A288: using guessed type int dword_51A288;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A954: using guessed type int dword_51A954;

//----- (00483960) --------------------------------------------------------
signed int  Instance_ValidateSlotValueConstraints(_DWORD *val, int sd, int ins)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int violationCode; // [esp+0h] [ebp-10h]

  if ( (*(_BYTE *)sd & 2) == 0 && val[1] == 4 )
  {
    Rules_PrintErrorID((int)aInsfun, 7, 0);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)val);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalForSing, v6);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], sd, v7, ins);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v8);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( val[1] == 105 )
  {
    Rules_PrintErrorID((int)aInsfun, 8, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVoidFunctionIl, v9);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], sd, v10, ins);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v11);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( Rules_DynamicConstraintCheckingEnabled() && (violationCode = Rules_CheckFieldAgainstConstraint(val, *(_DWORD *)(sd + 20))) != 0 )
  {
    Rules_PrintErrorID((int)aCstrnchk, 1, 0);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)val);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFor, v12);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], sd, v13, ins);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, *(_DWORD *)(sd + 20), 0);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
    return 1;
  }
}
// 4839D4: variable 'v6' is possibly undefined
// 4839E0: variable 'v7' is possibly undefined
// 4839EF: variable 'v8' is possibly undefined
// 483A22: variable 'v9' is possibly undefined
// 483A30: variable 'v10' is possibly undefined
// 483A3F: variable 'v11' is possibly undefined
// 483A80: variable 'v12' is possibly undefined
// 483A8C: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483AC0) --------------------------------------------------------
_DWORD * Instance_ResolveArgumentToInstance(int a1, int functionName, double a3)
{
  _DWORD *ins; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int valueBuffer; // [esp-4h] [ebp-20h] BYREF
  int theType; // [esp+0h] [ebp-1Ch]
  int theValue; // [esp+4h] [ebp-18h]
  int v13; // [esp+18h] [ebp-4h]

  v13 = functionName;
  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &valueBuffer, a1, a3);
  if ( theType == 7 )
  {
    ins = (_DWORD *)theValue;
    if ( (*(_BYTE *)(theValue + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    if ( theType != 8 && theType != 2 )
    {
      Rules_PrintErrorID((int)aInsfun, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_1, v7);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v8, v8);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v9);
      Lexer_ErrorRecover(1);
      return 0;
    }
    ins = Instance_FindByName(theValue);
    if ( !ins )
    {
      Instance_ReportNoSuchInstanceError(v6, v6);
      return 0;
    }
  }
  return ins;
}
// 483B28: variable 'v6' is possibly undefined
// 483B51: variable 'v7' is possibly undefined
// 483B5D: variable 'v8' is possibly undefined
// 483B6C: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;

//----- (00483B90) --------------------------------------------------------
int __fastcall Instance_ReportNoSuchInstanceError(int instanceName, int functionName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aInsfun, 2, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchInstance, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v7);
  return Lexer_ErrorRecover(1);
}
// 483BB2: variable 'v3' is possibly undefined
// 483BBE: variable 'v4' is possibly undefined
// 483BCD: variable 'v5' is possibly undefined
// 483BD9: variable 'v6' is possibly undefined
// 483BE8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483C00) --------------------------------------------------------
int __fastcall Instance_ReportNoSuchSlotError(int slotName, int functionName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aInsfun, 3, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchSlot, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v7);
  return Lexer_ErrorRecover(1);
}
// 483C22: variable 'v3' is possibly undefined
// 483C2E: variable 'v4' is possibly undefined
// 483C3D: variable 'v5' is possibly undefined
// 483C49: variable 'v6' is possibly undefined
// 483C58: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483C70) --------------------------------------------------------
signed int Instance_ReportInvalidInstanceAddressError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aInsfun, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInvalidInstanc, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v2);
}
// 483C90: variable 'v0' is possibly undefined
// 483C9C: variable 'v1' is possibly undefined
// 483CAB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483CD0) --------------------------------------------------------
int  Instance_SetModifiedFlag(int result)
{
  g_Instance_InstancesChangedFlag = result;
  return result;
}
// 51A288: using guessed type int dword_51A288;

//----- (00483CE0) --------------------------------------------------------
signed int  Instance_PrintSlotErrorContext(int logicalName, int sd, int a3, int ins)
{
  int v6; // ecx
  int v7; // ecx
  char *contextText; // edx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx

  Output_Write(logicalName, (int)aSlot, a3);
  Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(sd + 8) + 12) + 16), v6);
  if ( ins )
  {
    Output_Write(logicalName, (int)aOfInstance, v7);
    Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)(ins + 28) + 16), v12);
    contextText = asc_503C24;
  }
  else
  {
    if ( !*(_DWORD *)(sd + 4) )
      goto LABEL_5;
    Output_Write(logicalName, (int)aOfClass, v7);
    contextText = (char *)Rules_GetConstructNameString(*(_DWORD *)(sd + 4));
  }
  Output_Write(logicalName, (int)contextText, v9);
LABEL_5:
  Output_Write(logicalName, (int)aFoundIn, v7);
  if ( v10 )
    return Output_Write(logicalName, v10, v10);
  else
    return MessageHandler_PrintNameTypeAndClass(logicalName, *(_DWORD **)g_ClipsCurrentHandlerCore, 0);
}
// 483CFB: variable 'v6' is possibly undefined
// 483D11: variable 'v7' is possibly undefined
// 483D22: variable 'v9' is possibly undefined
// 483D35: variable 'v10' is possibly undefined
// 483D57: variable 'v12' is possibly undefined
// 51AD58: using guessed type int dword_51AD58;

//----- (00483D80) --------------------------------------------------------
signed int  Instance_PrintNameOfClass(int logicalName, int theInstance, int a3)
{
  int class_name; // eax
  int v5; // ecx
  int v6; // ecx

  Output_Write(logicalName, (int)asc_503C40, logicalName);
  class_name = Rules_GetInstanceClassName(theInstance);
  Output_Write(v5, class_name, v5);
  Output_Write(v6, (int)aOf, v6);
  return Class_PrintName(*(_DWORD *)(theInstance + 44), a3);
}
// 483D9B: variable 'v5' is possibly undefined
// 483DA7: variable 'v6' is possibly undefined

//----- (00483DC0) --------------------------------------------------------
_DWORD * Instance_FindInSubclasses(int theModule, _DWORD *startInstance)
{
  _DWORD *importList; // ebp
  _DWORD *ins; // ebx
  int v5; // ecx
  int *importedModule; // edi
  int theClass; // eax
  _DWORD *result; // eax

  if ( *(_DWORD *)(theModule + 20) )
    return 0;
  importList = *(_DWORD **)(theModule + 12);
  *(_DWORD *)(theModule + 20) = 1;
  if ( !importList )
  {
LABEL_10:
    for ( result = startInstance; result; result = (_DWORD *)result[15] )
    {
      if ( result[7] != startInstance[7] )
        break;
      if ( (*(_BYTE *)(result[11] + 20) & 2) != 0 )
        return result;
    }
    return 0;
  }
  while ( 1 )
  {
    ins = startInstance;
    importedModule = Module_FindByName(*(_BYTE **)(*importList + 16));
    if ( startInstance )
    {
      while ( ins[7] == startInstance[7] )
      {
        theClass = ins[11];
        if ( importedModule == **(int ***)(theClass + 8) && Class_IsInScope(theClass, v5) )
          return ins;
        ins = (_DWORD *)ins[15];
        if ( !ins )
          break;
      }
    }
    result = (_DWORD *)Instance_FindInSubclasses((int)importedModule, (int)startInstance);
    if ( result )
      return result;
    importList = (_DWORD *)importList[3];
    if ( !importList )
      goto LABEL_10;
  }
}
// 483E0F: variable 'v5' is possibly undefined

//----- (00483E70) --------------------------------------------------------
signed int  Instance_PrintStaleOrClassLabel(int logicalName, int theInstance)
{
  int v3; // ecx
  int v4; // ecx
  int v6; // ecx
  signed int *qualifiedName; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (*(_BYTE *)(theInstance + 24) & 2) != 0 )
  {
    Output_Write(logicalName, (int)aStaleInstance, logicalName);
    Output_Write(v3, *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 16), v3);
    return Output_Write(v4, (int)asc_503C60, v4);
  }
  else
  {
    Output_Write(logicalName, (int)asc_503C40, logicalName);
    qualifiedName = Instance_GetQualifiedName(theInstance, v6);
    Output_Write(v8, qualifiedName[4], v8);
    return Output_Write(v9, (int)asc_503C24, v9);
  }
}
// 483E90: variable 'v3' is possibly undefined
// 483E9C: variable 'v4' is possibly undefined
// 483EB2: variable 'v6' is possibly undefined
// 483EBC: variable 'v8' is possibly undefined
// 483EC8: variable 'v9' is possibly undefined

//----- (00483ED0) --------------------------------------------------------
signed int  Instance_PrintNameOrDummyLabel(int logicalName, void **theInstance)
{
  int v2; // ecx
  char *labelText; // edx
  signed int result; // eax
  int v7; // ecx
  signed int *qualifiedName; // eax
  int v9; // ecx
  char *suffixText; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int *fullName; // eax
  int v15; // ecx

  v2 = logicalName;
  if ( g_Print_InstanceAddressesToNamesFlag )
  {
    if ( theInstance == &g_Instance_DummyInstanceRecord )
    {
      labelText = aDummyInstanc_0;
    }
    else
    {
      Output_Write(logicalName, (int)asc_503C40, logicalName);
      qualifiedName = Instance_GetQualifiedName((int)theInstance, v7);
      Output_Write(v9, qualifiedName[4], v9);
      labelText = asc_503C24;
      logicalName = v2;
    }
    return Output_Write(logicalName, (int)labelText, v2);
  }
  else
  {
    if ( g_Print_AddressesToStringsFlag )
      Output_Write(logicalName, (int)asc_503C78, logicalName);
    if ( theInstance == &g_Instance_DummyInstanceRecord )
    {
      suffixText = aDummyInstanc_1;
    }
    else
    {
      if ( ((_BYTE)theInstance[6] & 2) != 0 )
      {
        Output_Write(v2, (int)aStaleInstanc_0, v2);
        Output_Write(v12, *((_DWORD *)theInstance[7] + 4), v12);
      }
      else
      {
        Output_Write(v2, (int)aInstance_7, v2);
        fullName = Instance_GetQualifiedName((int)theInstance, v13);
        Output_Write(v15, fullName[4], v15);
      }
      suffixText = asc_503CA4;
    }
    result = Output_Write(v2, (int)suffixText, v2);
    if ( g_Print_AddressesToStringsFlag )
      return Output_Write(v11, (int)asc_503C78, v11);
  }
  return result;
}
// 483EEF: variable 'v2' is possibly undefined
// 483F04: variable 'v7' is possibly undefined
// 483F0E: variable 'v9' is possibly undefined
// 483F53: variable 'v11' is possibly undefined
// 483F76: variable 'v12' is possibly undefined
// 483F90: variable 'v13' is possibly undefined
// 483F9A: variable 'v15' is possibly undefined
// 51A214: using guessed type void *off_51A214;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (00483FB0) --------------------------------------------------------
signed int  Rules_MarkObjectPatternNetworkTraversal(signed int traversalID, signed int theClass, int sd, double a4)
{
  int traversalRecord; // ebx
  signed int result; // eax
  unsigned int slotNameID; // edx
  unsigned int subclassIndex; // ecx
  int j; // edi
  int slotIndex; // edi
  _DWORD *i; // ecx
  int v13; // ecx

  traversalRecord = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  result = 1 << (traversalID % 8);
  if ( ((unsigned __int8)result & *(_BYTE *)(traversalRecord + 108)) == 0 )
  {
    *(_BYTE *)(traversalRecord + 108) |= result;
    slotNameID = *(_DWORD *)(*(_DWORD *)(sd + 8) + 8);
    if ( slotNameID <= *(_DWORD *)(theClass + 76) )
    {
      slotIndex = *(_DWORD *)(*(_DWORD *)(theClass + 60) + 4 * slotNameID);
      if ( slotIndex )
      {
        if ( sd == *(_DWORD *)(*(_DWORD *)(theClass + 56) + 4 * slotIndex - 4) )
        {
          for ( i = *(_DWORD **)(theClass + 80); i; i = *(_DWORD **)(v13 + 52) )
            Rules_ObjectMatchAction((unsigned __int16 *)3, i, *(_DWORD *)(*(_DWORD *)(sd + 8) + 8), a4);
        }
      }
    }
    subclassIndex = 0;
    for ( j = 0; ; Rules_MarkObjectPatternNetworkTraversal(traversalID, *(_DWORD *)(*(_DWORD *)(theClass + 42) + j - 4), sd, a4) )
    {
      result = theClass;
      if ( subclassIndex >= *(unsigned __int16 *)(theClass + 40) )
        break;
      j += 4;
    }
  }
  return result;
}
// 48401F: variable 'v9' is possibly undefined
// 48406C: variable 'v13' is possibly undefined

//----- (00484090) --------------------------------------------------------
int  Instance_ReleaseSlotValueContainer(int result)
{
  int theInstance; // esi
  int newRefCount; // edx
  unsigned int slotIndex; // ebx
  int i; // ecx
  unsigned int slotCount; // edi
  int slotEntry; // eax
  __int16 *slotValue; // ebp

  theInstance = result;
  newRefCount = *(_DWORD *)(result + 8) - 1;
  *(_DWORD *)(result + 8) = newRefCount;
  if ( !newRefCount )
  {
    if ( (*(_BYTE *)(result + 24) & 2) != 0 )
      Instance_ReleaseSlotValues(result);
    result = *(_DWORD *)(theInstance + 44);
    if ( *(_DWORD *)(result + 72) )
    {
      slotIndex = 0;
      for ( i = 0; ; i += 12 )
      {
        slotCount = *(_DWORD *)(*(_DWORD *)(theInstance + 44) + 72);
        if ( slotIndex >= slotCount )
          break;
        slotEntry = i + *(_DWORD *)(theInstance + 20);
        slotValue = *(__int16 **)(slotEntry + 8);
        if ( slotValue )
        {
          if ( (**(_BYTE **)slotEntry & 2) != 0 )
            Rules_DeinstallMultifield(*(__int16 **)(slotEntry + 8));
          else
            Rules_AtomDeinstall(*(_DWORD *)(slotEntry + 4) << 24 >> 26, slotValue, i);
        }
        ++slotIndex;
      }
      result = Mem_SmallBlockFree(*(_DWORD **)(theInstance + 20), 12 * slotCount);
      *(_DWORD *)(theInstance + 20) = 0;
    }
  }
  return result;
}
// 4840D2: variable 'i' is possibly undefined

//----- (00484130) --------------------------------------------------------
_DWORD * Instance_AcquireLocalSlotArray(_DWORD *result)
{
  _DWORD *theInstance; // edx
  int sharedSlotCount; // esi
  int srcOffset; // ebx
  _DWORD *slotArray; // eax
  int v6; // ecx
  unsigned int slotIndex; // ecx

  theInstance = result;
  if ( !result[2] )
  {
    sharedSlotCount = *(_DWORD *)(result[11] + 72);
    if ( sharedSlotCount )
    {
      srcOffset = 0;
      slotArray = Mem_SmallBlockAlloc(12 * sharedSlotCount);
      *(_DWORD *)(v6 + 20) = slotArray;
      slotIndex = 0;
      result = 0;
      while ( slotIndex < *(_DWORD *)(theInstance[11] + 72) )
      {
        *(_DWORD *)((char *)result + theInstance[5]) = **(_DWORD **)(theInstance[18] + srcOffset);
        result += 3;
        srcOffset += 4;
        ++slotIndex;
        *(_DWORD *)((char *)result + theInstance[5] - 4) = 0;
      }
    }
  }
  ++theInstance[2];
  return result;
}
// 48414A: variable 'v2' is possibly undefined
// 48416C: variable 'v6' is possibly undefined

//----- (004841A0) --------------------------------------------------------
void  Instance_NotifyCreated(_DWORD *theInstance, double a2)
{
  Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a2);
}

//----- (004842DF) --------------------------------------------------------
#if 0
void  __noreturn CRT_WatcomEHHandleNestedException(int a1, int a2)
{
  int *currentExc; // edi
  int *nestedExc; // ebp
  char savedState; // al
  int *fnexcThis; // eax
  int v7; // edx
  int v8; // ecx
  _DWORD *nestedThrowRec; // eax
  int *fnexcThis2; // eax
  int *dtorThis; // eax
  int v12; // ecx
  _EXC_PR_FNEXC *strExcBuf[26]; // [esp+0h] [ebp-14Ch] BYREF
  char v14; // [esp+D8h] [ebp-74h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+110h] [ebp-3Ch]
  tagRECT *fsHandlerRtn; // [esp+114h] [ebp-38h]
  void *scopeTable; // [esp+118h] [ebp-34h]
  int ehState; // [esp+11Ch] [ebp-30h]
  _EXC_PR_FNEXC **excCleanup; // [esp+124h] [ebp-28h]
  char v20; // [esp+128h] [ebp-24h]
  int pgmThread; // [esp+130h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  fsHandlerRtn = &j____wcpp_4_fs_handler_rtn_;
  scopeTable = &g_CRTWatcomEHHandleNestedException_ScopeTable;
  ehState = 0;
  pgmThread = **(_DWORD **)(a1 + 8);
  currentExc = *(int **)(pgmThread + 8);
  *(_DWORD *)(pgmThread + 12) = aViolationOfFun;
  nestedExc = currentExc;
  currentExc[7] = a1;
  while ( 1 )
  {
    if ( !nestedExc )
    {
      currentExc[7] = a1;
      savedState = *((_BYTE *)currentExc + 12);
      *((_BYTE *)currentExc + 12) = 2;
      *((_BYTE *)currentExc + 13) = savedState;
      if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
        fnexcThis = 0;
      else
        fnexcThis = currentExc;
      _EXC_PR_FNEXC::_EXC_PR_FNEXC(fnexcThis);
      ehState = 1;
      unexpected();
      v14 = 3;
      _wcpp_4_call_terminate__(v8, v7);
      ehState = 0;
      _EXC_PR_FNEXC::~_EXC_PR_FNEXC(strExcBuf[0]);
    }
    nestedThrowRec = (_DWORD *)nestedExc[7];
    if ( nestedThrowRec && *(_DWORD *)a1 == *nestedThrowRec && *(_DWORD *)(a1 + 32) == nestedThrowRec[8] )
    {
      if ( *((_BYTE *)nestedExc + 12) == 2 )
      {
        *((_BYTE *)currentExc + 12) = 7;
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          fnexcThis2 = 0;
        else
          fnexcThis2 = currentExc;
        _EXC_PR_FNEXC::_EXC_PR_FNEXC(fnexcThis2);
        v20 = 0;
        excCleanup = strExcBuf;
        ehState = 4;
        ExcString_Ctor();
        ehState = 5;
        ExcString_Ctor();
        strExcBuf[25] = (_EXC_PR_FNEXC *)&g_BadException_VTable;
        ehState = 7;
        CRT_ThrowExcStringException();
        excCleanup = strExcBuf;
        v20 = 0;
        ehState = 0;
        _EXC_PR_FNEXC::~_EXC_PR_FNEXC(strExcBuf[0]);
      }
      if ( *((_BYTE *)nestedExc + 12) == 7 )
      {
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          dtorThis = 0;
        else
          dtorThis = currentExc;
        _EXC_PR_DTOR::_EXC_PR_DTOR(dtorThis);
        ehState = 14;
        _wcpp_4_call_terminate__(v12, pgmThread);
        ehState = 0;
        _EXC_PR_DTOR::~_EXC_PR_DTOR(strExcBuf[0]);
      }
      if ( nestedExc != currentExc )
        _wcpp_4_corrupted_stack__(a2);
    }
    nestedExc = (int *)*nestedExc;
    if ( currentExc == nestedExc )
      _wcpp_4_corrupted_stack__(a2);
  }
}
// 484394: variable 'v8' is possibly undefined
// 484394: variable 'v7' is possibly undefined
// 4844C5: variable 'v12' is possibly undefined
// 4844E7: variable 'a2' is possibly undefined
// 4B403E: using guessed type _DWORD __stdcall _EXC_PR_DTOR::_EXC_PR_DTOR(_DWORD);
// 4B404D: using guessed type _DWORD __stdcall _EXC_PR_FNEXC::_EXC_PR_FNEXC(_DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B40FF: using guessed type int __fastcall _wcpp_4_call_terminate__(_DWORD, _DWORD);
// 510F44: using guessed type _DWORD (__cdecl *off_510F44)(bad_exception *this);

//----- (0048469F) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
// positive sp value has been detected, the output may be wrong!
int  CRT_WatcomEHFrameHandler(
        int a1,
        int a2,
        int a3,
        __int128 a4,
        int ExceptionRecord_6,
        __int128 ExceptionRecord_10,
        int ExceptionRecord_26,
        int ExceptionRecord_30,
        int ExceptionRecord_34,
        int ExceptionRecord_38,
        int ExceptionRecord_42,
        __int128 ExceptionRecord_46,
        int ExceptionRecord_62,
        int ExceptionRecord_66,
        int ExceptionRecord_70,
        int ExceptionRecord_74,
        int ExceptionRecord_78,
        __int64 a18,
        int a19,
        __int64 a20)
{
  int v21; // ecx
  int v22; // ecx
  void *v24; // esp
  int v25; // eax
  int v26; // ecx
  int v27; // ebx
  int v28; // eax
  int v29; // ecx
  _EXC_PR_FREE *v30; // [esp-92h] [ebp-12Eh]
  _EXC_PR *v31; // [esp-82h] [ebp-11Eh]
  PVOID TargetFrame; // [esp+82h] [ebp-1Ah] BYREF
  int v33; // [esp+8Eh] [ebp-Eh]
  int var2; // [esp+9Ah] [ebp-2h]
  int vars6; // [esp+A2h] [ebp+6h]
  char varsA; // [esp+A6h] [ebp+Ah]
  char varsB; // [esp+A7h] [ebp+Bh]

  *(_DWORD *)((char *)&ExceptionRecord_46 + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 6) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 10) = &g_CRTWatcomEHFrameHandler_ScopeTable;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
  *(_DWORD *)((char *)&a18 + 2) = _wcpp_4_pgm_thread__(a2);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 2) + 12) = 0;
  _wcpp_4_exc_setup__(a1, (char *)&a4 + 10);
  if ( (unsigned int)stackavail_(v21) > 0x10 )
  {
    CRT_ProbeStackForAlloca(16);
    v24 = alloca(16);
  }
  *(_DWORD *)((char *)&a20 + 2) = 0;
  if ( !*(_DWORD *)((char *)&a4 + 2) )
  {
    varsA = 3;
    goto LABEL_5;
  }
  RaiseException(
    *(DWORD *)((char *)&a4 + 10),
    *(DWORD *)((char *)&a4 + 14),
    *(DWORD *)((char *)&ExceptionRecord_10 + 6),
    (const ULONG_PTR *)((char *)&ExceptionRecord_10 + 10));
  if ( (unsigned __int8)varsA >= 2u )
  {
    if ( (unsigned __int8)varsA > 2u )
    {
      if ( varsA != 4 )
        goto LABEL_20;
      if ( !*(_DWORD *)((char *)&a4 + 6) )
        _wcpp_4_corrupted_stack__(v22);
      switch ( *(_BYTE *)(*(_DWORD *)((char *)&a4 + 6) + 12) )
      {
        case 0:
          if ( (varsB & 2) != 0 )
            v25 = 0;
          else
            v25 = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 2) + 8);
          _EXC_PR_FREE::_EXC_PR_FREE(v25);
          *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 1;
          _wcpp_4_call_terminate__(v26, *(_DWORD *)((char *)&a18 + 2));
          *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
          _EXC_PR_FREE::~_EXC_PR_FREE(v30);
          goto LABEL_14;
        case 3:
LABEL_14:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          goto LABEL_15;
        case 5:
LABEL_15:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          goto LABEL_16;
        case 6:
LABEL_16:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          break;
        default:
          break;
      }
      _wcpp_4_corrupted_stack__(v22);
    }
  }
  else if ( varsA != 1 )
  {
    goto LABEL_20;
  }
  if ( *(_DWORD *)((char *)&a20 + 2) )
  {
LABEL_19:
    CRT_WatcomEHUnwindThreadToState(vars6, v22);
    goto LABEL_20;
  }
  *(_DWORD *)((char *)&a20 + 2) = 1;
  if ( (varsB & 2) != 0 )
  {
    *(_BYTE *)(v33 + 13) = *(_BYTE *)(v33 + 12);
    if ( (varsB & 4) != 0 )
    {
      v27 = v33;
      *(_DWORD *)(v33 + 24) = var2;
      *(_DWORD *)(v27 + 32) = TargetFrame;
    }
  }
  else
  {
    v28 = ((int (*)(void))_wcpp_4_alloc_exc__)();
    v33 = v28;
    *(_DWORD *)(v28 + 24) = var2;
    *(_DWORD *)(v28 + 32) = TargetFrame;
  }
  if ( varsA != 2 )
  {
    *(_BYTE *)(v33 + 12) = 0;
    RtlUnwind(TargetFrame, *(PVOID *)((char *)&ExceptionRecord_10 + 2), (PEXCEPTION_RECORD)((char *)&a4 + 10), 0);
    goto LABEL_19;
  }
  if ( (varsB & 2) != 0 )
    *(_BYTE *)(v33 + 12) = *(_BYTE *)(v33 + 13);
LABEL_20:
  if ( (unsigned __int8)varsA < 2u )
  {
    if ( varsA != 1 )
      return _wcpp_4_corrupted_stack__(v22);
    CRT_WatcomEHResetStateOnUnwind();
    goto LABEL_5;
  }
  if ( (unsigned __int8)varsA <= 2u )
    CRT_WatcomEHHandleNestedException((int)&TargetFrame, v22);
  if ( varsA == 3 )
  {
LABEL_5:
    if ( (varsB & 2) != 0 )
    {
      _wcpp_4_fatal_runtime_error__(v22, 1);
    }
    else
    {
      ((void (__fastcall *)(int, char *))_EXC_PR::_EXC_PR)(3, (char *)&a18 + 2);
      *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 3;
      _wcpp_4_call_terminate__(v29, *(_DWORD *)((char *)&a18 + 2));
      *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
      _EXC_PR::~_EXC_PR(v31);
    }
  }
  return _wcpp_4_corrupted_stack__(v22);
}
// 484747: positive sp value 82 has been found
// 4848B6: inconsistent variable size for '^154.16'
// 4846D2: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48479E: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 4847AF: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48490E: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48491F: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 47C1C0: using guessed type _DWORD __stdcall sub_47C1C0(_DWORD);
// 48455B: using guessed type _DWORD sub_48455B();
// 486342: using guessed type int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD, _DWORD);
// 4B3FC7: using guessed type _DWORD _EXC_PR::_EXC_PR();
// 4B4001: using guessed type _DWORD __stdcall _EXC_PR_FREE::_EXC_PR_FREE(_DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B40FF: using guessed type int __fastcall _wcpp_4_call_terminate__(_DWORD, _DWORD);
// 4B42EA: using guessed type __int64 __thiscall _wcpp_4_pgm_thread__(_DWORD);
// 4B431A: using guessed type _DWORD __stdcall _wcpp_4_exc_setup__(_DWORD, _DWORD);
// 4B43B3: using guessed type int __thiscall stackavail_(_DWORD);
#endif

//----- (004849EE) --------------------------------------------------------
// Deferred to compat/decomp_runtime_stubs.c until the ExcString throw helper is reconstructed.

//----- (00484AED) --------------------------------------------------------
int CRT_ConstructBadExceptionFromCurrentSEH()
{
  int result; // eax

  result = ExcString_CtorFromPtr((void *)NtCurrentTeb()->NtTib.ExceptionList);
  *(_DWORD *)(result + 100) = &g_BadException_VTable;
  return result;
}
// 510F44: using guessed type _DWORD (__cdecl *off_510F44)(bad_exception *this);

//----- (00484DBD) --------------------------------------------------------
int __thiscall CRT_WriteMessageAndCountNewline(void *this)
{
  int result; // eax
  int v2; // ecx
  int charsWritten; // ebx

  result = fputs_(this, &g_CRT_StdoutStream);
  charsWritten = result;
  if ( result != -1 )
  {
    result = CRT_PutcToStream(v2, &g_CRT_StdoutStream);
    if ( result == 10 )
      return charsWritten + 1;
  }
  return result;
}
// 484DDA: variable 'v2' is possibly undefined
// 4850C6: using guessed type int __fastcall fputs_(_DWORD, _DWORD);
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (00484EBB) --------------------------------------------------------
int  CRT_WatcomEHTraverseUnwindState(int a1, int a2)
{
  int v2; // eax
  int v3; // edx
  int v4; // ecx

  v2 = _wcpp_4_stab_trav_move__(a2, a1);
  v4 = v2;
  if ( v2 && !*(_DWORD *)v2 && *(_DWORD *)(v3 + 4) != *(_DWORD *)(v3 + 8) )
  {
    switch ( **(_BYTE **)(v2 + 4) )
    {
      case 2:
      case 3:
      case 4:
        goto LABEL_6;
      case 6:
      case 7:
      case 8:
      case 9:
      case 0xA:
      case 0xB:
      case 0xC:
      case 0xD:
        return v4;
      default:
        _wcpp_4_corrupted_stack__(v2);
LABEL_6:
        _wcpp_4_corrupted_stack__(v4);
        break;
    }
  }
  return v4;
}
// 484ED0: variable 'v3' is possibly undefined
// 484EF2: variable 'v4' is possibly undefined
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B47CD: using guessed type int __fastcall _wcpp_4_stab_trav_move__(_DWORD, _DWORD);

//----- (00484EFD) --------------------------------------------------------
int  CRT_WatcomEHInvokeStateDestructor(int a1, unsigned __int8 a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)(a1 + 4) + *(_DWORD *)(a3 + 4);
  if ( (a2 & *(_BYTE *)(result + 4)) == 0 )
    return (*(int (**)(void))(a1 + 12))();
  return result;
}

//----- (00484F53) --------------------------------------------------------
unsigned int  CRT_WatcomEHUnwindToState(unsigned int targetState, int a2, int a3)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  unsigned __int8 v9; // cl
  int v10; // ebx
  int v11; // eax
  unsigned int result; // eax
  int v13; // esi
  int v14; // ecx
  int v15; // esi
  _BYTE v17[4]; // [esp+4h] [ebp-24h] BYREF
  unsigned int v18; // [esp+8h] [ebp-20h]
  unsigned int v19; // [esp+Ch] [ebp-1Ch]
  char v20; // [esp+11h] [ebp-17h]
  int v21; // [esp+14h] [ebp-14h]

  *(_DWORD *)(a2 + 4) = a3;
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(a3 + 8);
  _wcpp_4_stab_trav_init__();
  v19 = targetState;
  v20 |= 1u;
  v21 = CRT_WatcomEHTraverseUnwindState((int)v17, v5);
  while ( 1 )
  {
    result = v18;
    if ( v18 == targetState )
      break;
    if ( v18 < targetState )
      _wcpp_4_corrupted_stack__(v6);
    _wcpp_4_stab_trav_next__();
    v13 = v21;
    v21 = CRT_WatcomEHTraverseUnwindState((int)v17, v14);
    *(_DWORD *)(a3 + 12) = v18;
    if ( *(_DWORD *)v13 )
    {
      (*(void (**)(void))v13)();
    }
    else
    {
      v15 = *(_DWORD *)(v13 + 4);
      switch ( *(_BYTE *)v15 )
      {
        case 0:
          goto LABEL_3;
        case 2:
        case 3:
        case 4:
          _wcpp_4_corrupted_stack__(v7);
          continue;
        case 6:
          v9 = 17;
          goto LABEL_7;
        case 7:
          v9 = 16;
LABEL_7:
          v10 = a2;
          v11 = v15;
          goto LABEL_8;
        case 8:
          v9 = 16;
          v10 = a2;
          v11 = v15;
LABEL_8:
          CRT_WatcomEHInvokeStateDestructor(v11, v9, v10);
          continue;
        case 9:
          v8 = *(_DWORD *)(a3 + *(_DWORD *)(v15 + 4) + 8);
          goto LABEL_4;
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
          (*(void (**)(void))(v15 + 8))();
          continue;
        default:
          _wcpp_4_corrupted_stack__(v7);
LABEL_3:
          v8 = *(_DWORD *)(v15 + 8);
LABEL_4:
          _wcpp_4_dtor_array__(v7, v8);
          break;
      }
    }
  }
  *(_DWORD *)(a3 + 12) = v18;
  return result;
}
// 484F81: variable 'v5' is possibly undefined
// 484F8C: variable 'v7' is possibly undefined
// 484FF9: variable 'v6' is possibly undefined
// 48500F: variable 'v14' is possibly undefined
// 473197: using guessed type int __fastcall _wcpp_4_dtor_array__(_DWORD, _DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B475C: using guessed type int _wcpp_4_stab_trav_init__(void);
// 4B477E: using guessed type int _wcpp_4_stab_trav_next__(void);

//----- (0048507C) --------------------------------------------------------
unsigned int  CRT_WatcomEHUnwindThreadToState(int a1, int a2)
{
  __int64 v2; // rax
  unsigned int v3; // ecx
  _DWORD v5[5]; // [esp+0h] [ebp-14h] BYREF

  v5[3] = a2;
  v2 = _wcpp_4_pgm_thread__(a1);
  v5[0] = v2;
  return CRT_WatcomEHUnwindToState(v3, (int)v5, SHIDWORD(v2));
}
// 485091: variable 'v3' is possibly undefined
// 4B42EA: using guessed type __int64 __thiscall _wcpp_4_pgm_thread__(_DWORD);

//----- (0048509C) --------------------------------------------------------
unsigned int __fastcall CRT_WatcomEHUnwindToExceptionList(int a1, int a2)
{
  unsigned int v2; // ecx
  _DWORD v4[6]; // [esp+0h] [ebp-18h] BYREF

  v4[4] = a1;
  v4[0] = _wcpp_4_pgm_thread__(0);
  return CRT_WatcomEHUnwindToState(v2, (int)v4, (int)NtCurrentTeb()->NtTib.ExceptionList);
}
// 4850BA: variable 'v2' is possibly undefined
// 4B42EA: using guessed type int __thiscall _wcpp_4_pgm_thread__(_DWORD);

//----- (00485296) --------------------------------------------------------
int  Str_ParseSignedInt(char *str)
{
  char signChar; // cl
  int value; // ebx
  int accum; // ebx

  while ( (IsTable[(unsigned __int8)(*str + 1)] & 2) != 0 )
    ++str;
  signChar = *str;
  if ( *str == 43 || signChar == 45 )
    ++str;
  value = 0;
  while ( (IsTable[(unsigned __int8)(*str + 1)] & 0x20) != 0 )
  {
    accum = (unsigned __int8)*str++ + 10 * value;
    value = accum - 48;
  }
  if ( signChar == 45 )
    return -value;
  return value;
}

//----- (00485384) --------------------------------------------------------
int  CRT_InitializeProcessStartupInfo(int threadDataMgmtDisabled, int a2, int a3, HMODULE moduleHandle)
{
  int result; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  CHAR *cmdLineA; // eax
  _BYTE *cmdLineW; // eax
  int v11; // ecx
  int v12; // [esp-208h] [ebp-624h] BYREF
  _BYTE v13[520]; // [esp+0h] [ebp-41Ch] BYREF
  CHAR Filename[260]; // [esp+208h] [ebp-214h] BYREF
  CHAR moduleFilename[268]; // [esp+30Ch] [ebp-110h] BYREF
  int v16; // [esp+418h] [ebp-4h]

  v16 = a3;
  g_CrtThreadDataMgmtDisabledFlag = threadDataMgmtDisabled;
  result = CRT_AllocateThreadDataBlock(a2, a3);
  lpTlsValue = (LPVOID)result;
  if ( result )
  {
    _NTInitFileHandles_();
    g_CRT_EnvironmentStringsPtr = (int)GetEnvironmentStrings();
    g_CRT_EnvVarPointerArray = 0;
    g_WindowsVersionDword = GetVersion();
    g_CRT_OsBuildNumber = HIWORD(g_WindowsVersionDword);
    g_CRT_WinMajorVersion = (unsigned __int8)g_WindowsVersionDword;
    g_CRT_WinMinorVersion = BYTE1(g_WindowsVersionDword);
    g_CRT_WinVersion = BYTE1(g_WindowsVersionDword) | ((unsigned __int8)g_WindowsVersionDword << 8);
    GetModuleFileNameA(0, Filename, 0x104u);
    g_CRT_ExecutablePathA = CRT_FinalizeAnsiApiStringResult(v6, &v12);
    _lib_GetModuleFileNameW_();
    g_CRT_ExecutablePathW = CRT_FinalizeWideApiStringResult();
    GetCommandLineA();
    cmdLineA = (CHAR *)CRT_FinalizeAnsiApiStringResult(v8, v7);
    if ( *cmdLineA != 34 )
    {
      while ( (IsTable[(unsigned __int8)(*cmdLineA + 1)] & 2) == 0 && *cmdLineA )
        ++cmdLineA;
      goto LABEL_12;
    }
    do
      ++cmdLineA;
    while ( *cmdLineA != 34 && *cmdLineA );
    if ( !*cmdLineA )
      goto LABEL_12;
    do
    {
      ++cmdLineA;
LABEL_12:
      ;
    }
    while ( (IsTable[(unsigned __int8)(*cmdLineA + 1)] & 2) != 0 );
    lpCmdLine = cmdLineA;
    if ( GetCommandLineW() )
    {
      cmdLineW = (_BYTE *)CRT_FinalizeWideApiStringResult();
      if ( *(_WORD *)cmdLineW != 34 )
      {
        while ( (IsTable[(unsigned __int8)(*cmdLineW + 1)] & 2) == 0 && *(_WORD *)cmdLineW )
          cmdLineW += 2;
        goto LABEL_22;
      }
      do
        cmdLineW += 2;
      while ( *(_WORD *)cmdLineW != 34 && *(_WORD *)cmdLineW );
      if ( !*(_WORD *)cmdLineW )
        goto LABEL_22;
      do
      {
        cmdLineW += 2;
LABEL_22:
        ;
      }
      while ( (IsTable[(unsigned __int8)(*cmdLineW + 1)] & 2) != 0 );
    }
    else
    {
      cmdLineW = (_BYTE *)CRT_FinalizeWideApiStringResult();
    }
    g_CRT_WideCommandLine = (int)cmdLineW;
    if ( threadDataMgmtDisabled )
    {
      GetModuleFileNameA(moduleHandle, moduleFilename, 0x104u);
      g_CRT_ModulePathA = CRT_FinalizeAnsiApiStringResult(v11, v13);
      _lib_GetModuleFileNameW_();
      g_CRT_ModulePathW = CRT_FinalizeWideApiStringResult();
    }
    return 1;
  }
  else if ( !threadDataMgmtDisabled )
  {
    ExitProcess(1u);
  }
  return result;
}
// 48545C: variable 'v6' is possibly undefined
// 485480: variable 'v8' is possibly undefined
// 485480: variable 'v7' is possibly undefined
// 48557E: variable 'v11' is possibly undefined
// 4B4C8F: using guessed type int _NTInitFileHandles_(void);
// 4B4D17: using guessed type int __fastcall sub_4B4D17(_DWORD, _DWORD);
// 4B4D5C: using guessed type int _lib_GetModuleFileNameW_(void);
// 4B4DEC: using guessed type int sub_4B4DEC(void);
// 51A868: using guessed type int dword_51A868;
// 51A86C: using guessed type int dword_51A86C;
// 51A870: using guessed type int dword_51A870;
// 51A874: using guessed type int dword_51A874;
// 51A878: using guessed type int dword_51A878;
// 51A8A1: using guessed type int dword_51A8A1;
// 51A8A7: using guessed type int dword_51A8A7;
// 51A8AB: using guessed type int dword_51A8AB;
// 51A8AF: using guessed type int dword_51A8AF;
// 51A8B3: using guessed type int dword_51A8B3;
// 51A8B7: using guessed type int dword_51A8B7;
// 54E704: using guessed type int dword_54E704;

//----- (004855AF) --------------------------------------------------------
int  CRT_InitializeRuntimeBeforeWinMain(int a1, int a2)
{
  HMODULE ModuleHandleA; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  ModuleHandleA = GetModuleHandleA(0);
  CRT_InitializeProcessStartupInfo(0, a2, v5, ModuleHandleA);
  g_CrtThreadDataAccessor(v6, &g_CRT_StartupThreadDataBlock);
  _init_stack_limits_();
  CRT_InstallUnhandledExceptionFilter(a1, v7);
  _InitRtns();
  g_CRT_ThreadStartupHook();
  return _InitRtns();
}
// 4855C6: variable 'v5' is possibly undefined
// 4855D0: variable 'v6' is possibly undefined
// 4855DD: variable 'v7' is possibly undefined
// 485379: using guessed type _DWORD nullsub_8();
// 48564F: using guessed type int _InitRtns(void);
// 4B4E13: using guessed type int _init_stack_limits_(void);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A5A8: using guessed type _DWORD (*off_51A5A8)();

//----- (004856F0) --------------------------------------------------------
signed int  Output_WriteLongString(signed int result, char *str)
{
  int logicalName; // esi
  char *strPtr; // ebx
  int length; // ecx
  int segmentStart; // edx
  char saved_char; // cl

  logicalName = result;
  strPtr = str;
  if ( str )
  {
    while ( 1 )
    {
      length = strlen(strPtr);
      if ( length <= 500 )
        break;
      segmentStart = (int)strPtr;
      strPtr += 500;
      LOBYTE(length) = *strPtr;
      saved_char = *strPtr;
      *strPtr = 0;
      Output_Write(logicalName, segmentStart, length);
      *strPtr = saved_char;
    }
    return Output_Write(logicalName, (int)strPtr, length);
  }
  return result;
}

//----- (00485740) --------------------------------------------------------
signed int  Rules_PrintFloat(int logicalName, double number)
{
  int floatText; // eax

  floatText = Rules_FloatToSymbol(logicalName, number);
  return Output_Write(logicalName, floatText, logicalName);
}

//----- (00485770) --------------------------------------------------------
signed int __fastcall Rules_PrintLongInteger(int logicalName, int number)
{
  _BYTE printBuffer[32]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v5 = logicalName;
  sprintf_(printBuffer, "%ld", number);
  return Output_Write(v5, (int)printBuffer, v5);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004857A0) --------------------------------------------------------
unsigned int  Rules_PrintAtomValue(int logicalName, unsigned int type, int *value)
{
  int logName; // ecx
  unsigned int result; // eax
  int entityRecord; // edi
  int escapedText; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int floatText; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE addressBuffer[32]; // [esp+8h] [ebp-20h] BYREF

  logName = logicalName;
  result = type;
  if ( type < 3 )
  {
    if ( type )
    {
      if ( type > 1 )
        return Output_Write(logName, value[4], logName);
      else
        return Rules_PrintLongInteger(logName, value[4]);
    }
    else
    {
      floatText = Rules_FloatToSymbol(logName, *((double *)value + 2));
      return Output_Write(v12, floatText, v12);
    }
  }
  if ( type <= 3 )
  {
    if ( g_Print_PreserveEscapedCharactersFlag )
    {
      escapedText = Str_InternQuotedEscapedString((int *)value[4], logName);
      return Output_Write(v7, escapedText, v7);
    }
    else
    {
      Output_Write(logName, (int)asc_503EA4, logName);
      Output_Write(v13, value[4], v13);
      return Output_Write(v14, (int)asc_503EA4, v14);
    }
  }
  if ( type < 8 )
  {
    if ( type == 5 )
    {
      if ( g_Print_AddressesToStringsFlag )
        Output_Write(logName, (int)asc_503EA4, logName);
      Output_Write(logName, (int)aPointer, logName);
      sprintf_(addressBuffer, "%p", value);
      Output_Write(v8, (int)addressBuffer, v8);
      result = Output_Write(v9, (int)asc_503EB8, v9);
      if ( g_Print_AddressesToStringsFlag )
        return Output_Write(v10, (int)asc_503EA4, v10);
      return result;
    }
    goto LABEL_4;
  }
  if ( type <= 8 )
  {
    Output_Write(logName, (int)asc_503EBC, logName);
    Output_Write(v15, value[4], v15);
    return Output_Write(v16, (int)asc_503EC0, v16);
  }
  if ( type != 105 )
  {
LABEL_4:
    result = 4 * type;
    entityRecord = g_Clips_PrimitiveEntityTable[type];
    if ( entityRecord )
    {
      if ( *(_DWORD *)(entityRecord + 8) )
        return (*(int (**)(void))(entityRecord + 8))();
      else
        return Output_Write(logName, (int)aUnknownAtomTyp, logName);
    }
  }
  return result;
}
// 4858CB: variable 'v12' is possibly undefined
// 48580C: variable 'v7' is possibly undefined
// 48583E: variable 'v3' is possibly undefined
// 48585A: variable 'v8' is possibly undefined
// 485866: variable 'v9' is possibly undefined
// 48587F: variable 'v10' is possibly undefined
// 4858F9: variable 'v13' is possibly undefined
// 485905: variable 'v14' is possibly undefined
// 485922: variable 'v15' is possibly undefined
// 48592E: variable 'v16' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 54E530: using guessed type int dword_54E530[70];

//----- (00485950) --------------------------------------------------------
int  Rules_PrintTally(int result, int count, int a3, int singularWord)
{
  int logName; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx

  logName = result;
  if ( count )
  {
    Output_Write(result, (int)aForATotalOf, a3);
    Rules_PrintLongInteger(v6, count);
    Output_Write(logName, (int)asc_503EE8, v7);
    if ( count != 1 )
      singularWord = v8;
    Output_Write(logName, singularWord, v8);
    return Output_Write(logName, (int)a__14, v10);
  }
  return result;
}
// 48596B: variable 'v6' is possibly undefined
// 485977: variable 'v7' is possibly undefined
// 485985: variable 'v8' is possibly undefined
// 485991: variable 'v10' is possibly undefined

//----- (004859A0) --------------------------------------------------------
signed int  Rules_PrintErrorID(int module, int errorID, int printCR)
{
  if ( printCR )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EF0, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EBC, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], module, 0);
  Rules_PrintLongInteger((int)g_IO_LogicalNameTable_WError[0], errorID);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EF4, 0);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00485A00) --------------------------------------------------------
signed int  Rules_PrintWarningID(int module, int warningID, int printCR)
{
  if ( printCR )
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)asc_503EF0, 0);
  Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)asc_503EBC, 0);
  Output_Write((int)g_IO_LogicalNameTable_WWarning[0], module, 0);
  Rules_PrintLongInteger((int)g_IO_LogicalNameTable_WWarning[0], warningID);
  return Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWarning, 0);
}
// 51A610: using guessed type char *off_51A610[6];

//----- (00485A60) --------------------------------------------------------
signed int __fastcall Rules_ReportCantFindItem(int itemType, int itemName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aPrntutil, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFind, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EE8, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], itemName, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v7);
}
// 485A82: variable 'v3' is possibly undefined
// 485A8E: variable 'v4' is possibly undefined
// 485A9D: variable 'v5' is possibly undefined
// 485AA9: variable 'v6' is possibly undefined
// 485AB8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485AD0) --------------------------------------------------------
signed int __fastcall Rules_ReportCantDeleteItem(int itemType, int itemName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aPrntutil, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDele_3, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EE8, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], itemName, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v7);
}
// 485AF2: variable 'v3' is possibly undefined
// 485AFE: variable 'v4' is possibly undefined
// 485B0D: variable 'v5' is possibly undefined
// 485B19: variable 'v6' is possibly undefined
// 485B28: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485B40) --------------------------------------------------------
signed int __fastcall Rules_ReportAlreadyParsed(int coupler, int whichItem)
{
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)aPrntutil, 5, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_0, v3);
  if ( v4 )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  if ( whichItem )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], whichItem, v4);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasAlreadyBeen, v4);
}
// 485B65: variable 'v3' is possibly undefined
// 485B6C: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485BC0) --------------------------------------------------------
int Parser_ReportSyntaxError()
{
  int v0; // ecx
  int v1; // ecx
  int v3; // ecx

  Rules_PrintErrorID((int)aPrntutil, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSyntaxError, v0);
  if ( v1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCheckAppropria, v1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v3, v3);
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v1);
  return Lexer_ErrorRecover(1);
}
// 485BE3: variable 'v0' is possibly undefined
// 485BEA: variable 'v1' is possibly undefined
// 485C1F: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485C30) --------------------------------------------------------
signed int Rules_ReportLocalVariableError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aPrntutil, 6, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLocalVariables, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v2);
}
// 485C53: variable 'v0' is possibly undefined
// 485C5F: variable 'v1' is possibly undefined
// 485C6E: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485C80) --------------------------------------------------------
signed int __fastcall Rules_ReportSystemError(int module, int errorID)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  Rules_PrintErrorID((int)aPrntutil, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClipsSystemErr, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aId, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
  Rules_PrintLongInteger(v6, errorID);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EF0, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClipsDataStruc, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorMayHa, v9);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504060, v10);
}
// 485CA5: variable 'v3' is possibly undefined
// 485CB4: variable 'v4' is possibly undefined
// 485CC0: variable 'v5' is possibly undefined
// 485CCC: variable 'v6' is possibly undefined
// 485CDB: variable 'v7' is possibly undefined
// 485CEA: variable 'v8' is possibly undefined
// 485CF9: variable 'v9' is possibly undefined
// 485D08: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485D20) --------------------------------------------------------
signed int Rules_ReportDivideByZeroError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aPrntutil, 7, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttemptToDivid, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction__0, v2);
}
// 485D40: variable 'v0' is possibly undefined
// 485D4C: variable 'v1' is possibly undefined
// 485D5B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485D70) --------------------------------------------------------
int __fastcall Rules_FloatToSymbol(int a1, double number)
{
  int char_index; // esi
  int v4; // ecx
  char curr_char; // al
  char *suffix_ptr; // esi
  unsigned int buffer_length; // kr04_4
  char *append_ptr; // edi
  char v10; // al
  char v11; // al
  char print_buffer[52]; // [esp+0h] [ebp-34h] BYREF

  *(_DWORD *)&print_buffer[48] = a1;
  char_index = 0;
  sprintf_(print_buffer, "%.16g", number);
  while ( 1 )
  {
    curr_char = print_buffer[char_index];
    if ( !curr_char )
      break;
    if ( curr_char == 46 || curr_char == 101 )
      return Str_Intern(print_buffer, v4)[4];
    ++char_index;
  }
  suffix_ptr = a_0;
  buffer_length = strlen(print_buffer) + 1;
  append_ptr = &print_buffer[buffer_length - 1];
  do
  {
    v10 = *suffix_ptr;
    *append_ptr = *suffix_ptr;
    if ( !v10 )
      break;
    v11 = suffix_ptr[1];
    suffix_ptr += 2;
    append_ptr[1] = v11;
    append_ptr += 2;
  }
  while ( v11 );
  return Str_Intern(print_buffer, ~buffer_length)[4];
}
// 485DA8: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00485E00) --------------------------------------------------------
int  Rules_LongIntegerToSymbol(int number)
{
  int v1; // ecx
  char printBuffer[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf_(printBuffer, "%ld", number);
  return Str_Intern(printBuffer, v1)[4];
}
// 485E18: variable 'v1' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00485E30) --------------------------------------------------------
signed int Rules_RegisterExitFunction()
{
  Rules_RegisterHostFunction(aExit, 118, (int)aExitcommand, (int)Rules_ExitCommand, (int)a00_16);
  IO_InitializeFileIORouter();
  return IO_RegisterStringRouter();
}

//----- (00485E60) --------------------------------------------------------
signed int  Output_Write(int logicalName, int str, int a3)
{
  int router; // ecx
  void (__fastcall *router_write)(int, int); // ecx

  if ( g_IO_FastSaveFilePtr && logicalName == g_IO_FastSaveFilePtr )
  {
    Output_WriteFormatted(0, 0, g_IO_FastSaveFilePtr, (int)aS_1, str);
    return 2;
  }
  else
  {
    router = g_IO_RouterListHead;
    if ( g_IO_RouterListHead )
    {
      while ( !*(_DWORD *)(router + 16) || !IO_RouterMatchesName(logicalName, router) )
      {
        router = *(_DWORD *)(router + 32);
        if ( !router )
          goto LABEL_5;
      }
      router_write = (void (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(router + 16);
      router_write(logicalName, str);
      return 1;
    }
    else
    {
LABEL_5:
      if ( strcmp_((int)g_IO_LogicalNameTable_WError[0], logicalName) )
        IO_ReportUnrecognizedRouter(logicalName);
      return 0;
    }
  }
}
// 485E81: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;
// 51A60C: using guessed type int dword_51A60C;
// 51A614: using guessed type char *off_51A614[5];

//----- (00485EE0) --------------------------------------------------------
int  Lexer_PeekChar(int logicalName, unsigned int a2)
{
  int result; // eax
  unsigned __int8 *buffer_ptr; // ecx
  int router; // ecx
  int (__fastcall *router_read)(int); // eax

  if ( logicalName == g_IO_FastLoadFilePtr )
  {
    if ( *(int *)(g_IO_FastLoadFilePtr + 4) > 0 && (a2 = **(unsigned __int8 **)g_IO_FastLoadFilePtr - 13, a2 > 0xFD) )
    {
      --*(_DWORD *)(g_IO_FastLoadFilePtr + 4);
      buffer_ptr = (unsigned __int8 *)(*(_DWORD *)g_IO_FastLoadFilePtr)++;
      result = *buffer_ptr;
    }
    else
    {
      result = fgetc_(a2, g_IO_FastLoadFilePtr);
    }
    if ( result != 13 )
      return result;
    return 10;
  }
  router = g_IO_RouterListHead;
  if ( !g_IO_RouterListHead )
  {
LABEL_12:
    IO_ReportUnrecognizedRouter(logicalName);
    return -1;
  }
  while ( !*(_DWORD *)(router + 24) || !IO_RouterMatchesName(logicalName, router) )
  {
    router = *(_DWORD *)(router + 32);
    if ( !router )
      goto LABEL_12;
  }
  router_read = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(router + 24);
  result = router_read(logicalName);
  if ( result == 13 )
    return 10;
  return result;
}
// 485F4E: variable 'v4' is possibly undefined
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;
// 51A608: using guessed type int dword_51A608;

//----- (00485F90) --------------------------------------------------------
signed int  Lexer_SkipChar(signed int ch, int logicalName, int a3)
{
  int router; // ecx
  int (__fastcall *router_skip)(int, int); // eax

  if ( logicalName == g_IO_FastLoadFilePtr )
    return CRT_FlushBufferAndPutChar(ch, a3);
  router = g_IO_RouterListHead;
  if ( g_IO_RouterListHead )
  {
    while ( !*(_DWORD *)(router + 28) || !IO_RouterMatchesName(logicalName, router) )
    {
      router = *(_DWORD *)(router + 32);
      if ( !router )
        goto LABEL_5;
    }
    router_skip = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(router + 28);
    return router_skip(ch, logicalName);
  }
  else
  {
LABEL_5:
    IO_ReportUnrecognizedRouter(logicalName);
    return -1;
  }
}
// 485FB1: variable 'v4' is possibly undefined
// 51A604: using guessed type int dword_51A604;
// 51A608: using guessed type int dword_51A608;

//----- (00485FF0) --------------------------------------------------------
int Rules_ExitCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return IO_RunRouterExitCallbacks();
  return result;
}

//----- (00486020) --------------------------------------------------------
int IO_RunRouterExitCallbacks(num)
int num;
{
  int router; // edx
  int next_router; // ecx
  int (*router_exit)(int); // eax
  int result; // eax

  g_IO_RouterExitHandledFlag = 0;
  router = g_IO_RouterListHead;
  while ( router )
  {
    next_router = *(_DWORD *)(router + 32);
    if ( *(_DWORD *)(router + 4) == 1 && *(_DWORD *)(router + 20) )
    {
      router_exit = (int (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(router + 20);
      result = router_exit(num);
    }
    router = next_router;
  }
  if ( !g_IO_RouterExitHandledFlag )
    return plib_malloc__1();
  return result;
}
// 47D510: using guessed type int plib_malloc__1(void);
// 51A604: using guessed type int dword_51A604;
// 54DD98: using guessed type int dword_54DD98;

//----- (00486080) --------------------------------------------------------
signed int  IO_AddRouter(int routerName, int priority, int printFunction, int queryFunction, int getcFunction, int ungetcFunction, int exitFunction)
{
  _DWORD *free_entry; // ebx
  _DWORD *new_router; // eax
  int router_ptr; // ebx
  int current_router; // eax
  int previous_router; // ecx

  free_entry = *(_DWORD **)(g_ClipsMemoryTable + 144);
  if ( free_entry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 144);
    *(_DWORD *)(g_ClipsMemoryTable + 144) = *free_entry;
    new_router = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    new_router = (_DWORD *)Mem_HeapAllocWithRetry(36);
  }
  new_router[1] = 1;
  new_router[8] = 0;
  *new_router = routerName;
  new_router[2] = priority;
  new_router[3] = queryFunction;
  new_router[4] = printFunction;
  new_router[5] = exitFunction;
  new_router[6] = getcFunction;
  new_router[7] = ungetcFunction;
  router_ptr = (int)new_router;
  if ( !g_IO_RouterListHead )
  {
    g_IO_RouterListHead = (int)new_router;
    return 1;
  }
  current_router = g_IO_RouterListHead;
  previous_router = 0;
  do
  {
    if ( priority >= *(_DWORD *)(current_router + 8) )
      break;
    previous_router = current_router;
    current_router = *(_DWORD *)(current_router + 32);
  }
  while ( current_router );
  if ( !previous_router )
  {
    *(_DWORD *)(router_ptr + 32) = g_IO_RouterListHead;
    g_IO_RouterListHead = router_ptr;
    return 1;
  }
  *(_DWORD *)(router_ptr + 32) = current_router;
  *(_DWORD *)(previous_router + 32) = router_ptr;
  return 1;
}
// 4860C4: variable 'a3' is possibly undefined
// 51A604: using guessed type int dword_51A604;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00486150) --------------------------------------------------------
signed int  IO_DeleteRouter(int routerName)
{
  int router; // ecx
  _DWORD *previous_router; // esi

  router = g_IO_RouterListHead;
  previous_router = 0;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, routerName) )
  {
    previous_router = (_DWORD *)router;
    router = *(_DWORD *)(router + 32);
    if ( !router )
      return 0;
  }
  if ( previous_router )
    previous_router[8] = *(_DWORD *)(router + 32);
  else
    g_IO_RouterListHead = *(_DWORD *)(router + 32);
  Mem_SmallBlockFree((_DWORD *)router, 36);
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (004861B0) --------------------------------------------------------
int  IO_QueryRouters(int logicalName)
{
  int logical_name; // ebx
  int router; // ecx

  logical_name = logicalName;
  router = g_IO_RouterListHead;
  if ( !g_IO_RouterListHead )
    return 0;
  while ( IO_RouterMatchesName(logical_name, router) != 1 )
  {
    router = *(_DWORD *)(router + 32);
    if ( !router )
      return 0;
  }
  return 1;
}
// 51A604: using guessed type int dword_51A604;

//----- (004861E0) --------------------------------------------------------
int __fastcall IO_RouterMatchesName(int logicalName, int router)
{
  int result; // eax
  int (__fastcall *router_query)(int); // eax

  if ( !*(_DWORD *)(router + 4) )
    return 0;
  if ( !*(_DWORD *)(router + 12) )
    return 0;
  router_query = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(router + 12);
  result = router_query(logicalName);
  if ( result != 1 )
    return 0;
  return result;
}

//----- (00486200) --------------------------------------------------------
signed int  IO_DeactivateRouter(int routerName)
{
  int router; // ecx

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, routerName) )
  {
    router = *(_DWORD *)(router + 32);
    if ( !router )
      return 0;
  }
  *(_DWORD *)(router + 4) = 0;
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (00486240) --------------------------------------------------------
signed int  IO_ActivateRouter(int routerName)
{
  int router; // ecx
  signed int result; // eax

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, routerName) )
  {
    router = *(_DWORD *)(router + 32);
    if ( !router )
      return 0;
  }
  result = 1;
  *(_DWORD *)(router + 4) = 1;
  return result;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (00486280) --------------------------------------------------------
int  IO_SetFastLoadFile(int result)
{
  g_IO_FastLoadFilePtr = result;
  return result;
}
// 51A608: using guessed type int dword_51A608;

//----- (00486290) --------------------------------------------------------
int  IO_SetFastSaveFile(int result)
{
  g_IO_FastSaveFilePtr = result;
  return result;
}
// 51A60C: using guessed type int dword_51A60C;

//----- (004862A0) --------------------------------------------------------
int IO_GetFastLoadFile()
{
  return g_IO_FastLoadFilePtr;
}
// 51A608: using guessed type int dword_51A608;

//----- (004862C0) --------------------------------------------------------
int  IO_ReportUnrecognizedRouter(int logicalName)
{
  static int reporting_router_error;
  int result; // eax

  if ( reporting_router_error )
    return 0;
  reporting_router_error = 1;
  Rules_PrintErrorID((int)aRouter, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLogicalName, 0);
  if ( logicalName )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], logicalName, 0);
  result = Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasNotRecogniz, 0);
  reporting_router_error = 0;
  return result;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00486414) --------------------------------------------------------
char *__thiscall CRT_AllocateLockSlot(void *this)
{
  int slotIndex; // edx
  int allocatedSlot; // ebx
  int v3; // ecx

  slotIndex = g_CRT_UsedLockSlotCount;
  if ( g_CRT_UsedLockSlotCount >= 64 )
  {
    allocatedSlot = calloc_(this, 24);
    if ( !allocatedSlot )
      _fatal_runtime_error_(v3, 1);
  }
  else
  {
    ++g_CRT_UsedLockSlotCount;
    return (char *)&g_CRT_LockSlotPool + 24 * slotIndex;
  }
  return (char *)allocatedSlot;
}
// 48645D: variable 'v3' is possibly undefined
// 49499A: using guessed type int __fastcall _fatal_runtime_error_(_DWORD, _DWORD);
// 4B56B6: using guessed type int __fastcall calloc_(_DWORD, _DWORD);
// 54DEFC: using guessed type int dword_54DEFC;

//----- (00486468) --------------------------------------------------------
void  CRT_ResetLockSlot(int result)
{
  if ( *(_DWORD *)(result + 4) )
    DeleteCriticalSection(*(LPCRITICAL_SECTION *)result);
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)(result + 8) = 0;
  *(_DWORD *)(result + 12) = 0;
}

//----- (00486496) --------------------------------------------------------
void CRT_AcquireStaticLock1()
{
  CRT_LockEnter((int)&g_CRT_StaticLock1);
}

//----- (004864A0) --------------------------------------------------------
void CRT_ReleaseStaticLock1()
{
  CRT_LockLeave((int)&g_CRT_StaticLock1);
}

//----- (004864AA) --------------------------------------------------------
void  CRT_AcquireFileHandleLock(char fileHandle)
{
  CRT_LockEnter((int)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
}

//----- (004864B7) --------------------------------------------------------
void  CRT_ReleaseFileHandleLock(char fileHandle)
{
  CRT_LockLeave((int)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
}

//----- (004864CC) --------------------------------------------------------
int  CRT_ReleaseAndUnregisterFileHandle(char fileHandle)
{
  CRT_ResetLockSlot((int)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
  return _NTRemoveFileHandle_();
}
// 4B4C63: using guessed type int _NTRemoveFileHandle_(void);

//----- (004864E8) --------------------------------------------------------
void CRT_AcquireStaticLock2()
{
  CRT_LockEnter((int)&g_CRT_StaticLock2);
}

//----- (004864EF) --------------------------------------------------------
void CRT_ReleaseStaticLock2()
{
  CRT_LockLeave((int)&g_CRT_StaticLock2);
}

//----- (004864F9) --------------------------------------------------------
void CRT_AcquireStaticLock3()
{
  CRT_LockEnter((int)&g_CRT_StaticLock3);
}

//----- (00486500) --------------------------------------------------------
void CRT_ReleaseStaticLock3()
{
  CRT_LockLeave((int)&g_CRT_StaticLock3);
}

//----- (0048650A) --------------------------------------------------------
void CRT_AcquireStaticLock4()
{
  CRT_LockEnter((int)&g_CRT_StaticLock4);
}

//----- (00486511) --------------------------------------------------------
void CRT_ReleaseStaticLock4()
{
  CRT_LockLeave((int)&g_CRT_StaticLock4);
}

//----- (0048651D) --------------------------------------------------------
void  CRT_LockEnter(int lock)
{
  DWORD CurrentThreadId; // esi
  void *v3; // ecx
  char *criticalSection; // eax

  CurrentThreadId = GetCurrentThreadId();
  if ( CurrentThreadId != *(_DWORD *)(lock + 8) )
  {
    if ( !*(_DWORD *)(lock + 4) )
    {
      CRT_LockEnter((int)&g_CRT_LockInitCriticalSection);
      if ( !*(_DWORD *)(lock + 4) )
      {
        criticalSection = CRT_AllocateLockSlot(v3);
        *(_DWORD *)lock = criticalSection;
        InitializeCriticalSection((LPCRITICAL_SECTION)criticalSection);
        *(_DWORD *)(lock + 4) = 1;
      }
      CRT_LockLeave((int)&g_CRT_LockInitCriticalSection);
    }
    EnterCriticalSection(*(LPCRITICAL_SECTION *)lock);
    *(_DWORD *)(lock + 8) = CurrentThreadId;
  }
  ++*(_DWORD *)(lock + 12);
}
// 486549: variable 'v3' is possibly undefined
// 54DECC: using guessed type int dword_54DECC;

//----- (00486583) --------------------------------------------------------
void  CRT_LockLeave(int result)
{
  int lockCount; // edx
  struct _RTL_CRITICAL_SECTION *criticalSection; // [esp-10h] [ebp-14h]

  lockCount = *(_DWORD *)(result + 12);
  if ( lockCount )
  {
    *(_DWORD *)(result + 12) = lockCount - 1;
    if ( lockCount == 1 )
    {
      criticalSection = *(struct _RTL_CRITICAL_SECTION **)result;
      *(_DWORD *)(result + 8) = 0;
      LeaveCriticalSection(criticalSection);
    }
  }
}

//----- (004865AA) --------------------------------------------------------
_BYTE *CRT_GetOrCreateThreadDataPreserveLastError()
{
  DWORD LastError; // esi
  _BYTE *Value; // eax
  _BYTE *v2; // ebx
  int ThreadData; // eax

  LastError = GetLastError();
  Value = TlsGetValue(dwTlsIndex);
  v2 = Value;
  if ( !Value )
  {
    ThreadData = _GetThreadData_();
LABEL_5:
    v2 = (_BYTE *)ThreadData;
    goto LABEL_6;
  }
  if ( Value[83] )
  {
    ThreadData = _ReallocThreadData_();
    goto LABEL_5;
  }
LABEL_6:
  SetLastError(LastError);
  return v2;
}
// 4B56CE: using guessed type int _GetThreadData_(void);
// 4B5707: using guessed type int _ReallocThreadData_(void);

//----- (004865EE) --------------------------------------------------------
int  CRT_AllocateThreadDataBlock(int a1, int a2)
{
  int thread_data; // eax
  int block_size; // ebx
  int v4; // edx

  if ( !a1 )
  {
    thread_data = calloc_(a2, g_CRT_ThreadDataBlockSize);
    if ( thread_data )
    {
      block_size = g_CRT_ThreadDataBlockSize;
      *(_BYTE *)(thread_data + 82) = 1;
      *(_DWORD *)(thread_data + 240) = block_size;
    }
  }
  _InitThreadData_(a2);
  return v4;
}
// 48661E: variable 'a2' is possibly undefined
// 486623: variable 'v4' is possibly undefined
// 4B56B6: using guessed type int __fastcall calloc_(_DWORD, _DWORD);
// 4B58D2: using guessed type int __fastcall _InitThreadData_(_DWORD);
// 51AF00: using guessed type int dword_51AF00;

//----- (00486628) --------------------------------------------------------
BOOL CRT_AllocateTlsIndex()
{
  dwTlsIndex = TlsAlloc();
  if ( HIWORD(g_WindowsVersionDword) >= 0x8000u && (unsigned __int8)g_WindowsVersionDword < 4u )
  {
    while ( dwTlsIndex <= 2 )
      dwTlsIndex = TlsAlloc();
  }
  return dwTlsIndex != -1;
}
// 486656: simplified comparisons for '$dwTlsIndex.4': ==FFFFFFFF || >=3u became >=3u
// 51A8A7: using guessed type int dword_51A8A7;

//----- (0048667D) --------------------------------------------------------
int  CRT_CreateAndAttachThreadData(int a1, int a2)
{
  int result; // eax
  int v3; // ecx
  void *thread_data; // ebx
  int v5; // ecx

  if ( dwTlsIndex == -1 )
    return 0;
  result = CRT_AllocateThreadDataBlock(a1, a2);
  thread_data = (void *)result;
  if ( result )
  {
    if ( !_AddThreadData_(v3, result) )
    {
      nfree_(v5);
      return 0;
    }
    TlsSetValue(dwTlsIndex, thread_data);
    return 1;
  }
  return result;
}
// 4866A2: variable 'v3' is possibly undefined
// 4866AD: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4B57DB: using guessed type int __fastcall _AddThreadData_(_DWORD, _DWORD);

//----- (004866CC) --------------------------------------------------------
char * CRT_DetachThreadDataAndMaybeCloseHandle(char *result)
{
  char *closeHandleFlag; // ebx
  void *threadHandle; // esi

  closeHandleFlag = result;
  if ( dwTlsIndex != -1 )
  {
    result = (char *)TlsGetValue(dwTlsIndex);
    if ( result )
    {
      threadHandle = *(void **)(result + 222);
      _RemoveThreadData_();
      result = (char *)TlsSetValue(dwTlsIndex, 0);
      if ( threadHandle )
      {
        if ( closeHandleFlag )
          return (char *)CloseHandle(threadHandle);
      }
    }
  }
  return result;
}
// 4B583C: using guessed type int _RemoveThreadData_(void);

//----- (00486721) --------------------------------------------------------
char *CRT_DestroyTlsIndexAndThreadData()
{
  char *result; // eax

  result = CRT_DetachThreadDataAndMaybeCloseHandle((char *)1);
  if ( dwTlsIndex != -1 )
  {
    result = (char *)TlsFree(dwTlsIndex);
    dwTlsIndex = -1;
  }
  return result;
}

//----- (0048674D) --------------------------------------------------------
void CRT_InitializeThreadAndFileHandleHooks()
{
  g_CRT_FileHandleLockAcquireHook = (int (__thiscall *)(_DWORD))CRT_AcquireFileHandleLock;
  g_CRT_FileHandleLockReleaseHook = (int (__fastcall *)(_DWORD, _DWORD))CRT_ReleaseFileHandleLock;
  g_CRT_AddFileHandleHook = j___NTAddFileHandle__0;
  g_CRT_FileHandleRemoveHookTable[0] = (int (*)())CRT_ReleaseAndUnregisterFileHandle;
  g_CRT_StaticLock1AcquireHook = (_DWORD (*)())CRT_AcquireStaticLock1;
  g_CRT_StaticLock1ReleaseHook = (_DWORD (*)())CRT_ReleaseStaticLock1;
  g_CRT_StaticLock4AcquireHookTable[0] = (int (*)())CRT_AcquireStaticLock4;
  g_CRT_StaticLock4ReleaseHookTable[0] = (int (*)())CRT_ReleaseStaticLock4;
  g_CRT_LockEnterHookTable[0] = (int (*)())CRT_LockEnter;
  g_CRT_LockLeaveHookTable[0] = (int (*)())CRT_LockLeave;
  g_CRT_LockSlotResetHook = (int (__fastcall *)(_DWORD, _DWORD))CRT_ResetLockSlot;
  g_CRT_StaticLock2AcquireHook = (_DWORD (*)())CRT_AcquireStaticLock2;
  g_CRT_StaticLock3AcquireHookTable[0] = (int (*)())CRT_AcquireStaticLock3;
  g_CRT_StaticLock2ReleaseHook = (_DWORD (*)())CRT_ReleaseStaticLock2;
  g_CRT_StaticLock3ReleaseHookTable[0] = (int (*)())CRT_ReleaseStaticLock3;
  g_CRT_LockInitCriticalSection = (int)CRT_AllocateLockSlot(CRT_LockLeave);
  InitializeCriticalSection((LPCRITICAL_SECTION)g_CRT_LockInitCriticalSection);
  g_CRT_ThreadLockSystemInitialized = 1;
  g_CRT_ThreadDataDestroyHookTable[0] = CRT_DestroyThreadDataBlock;
  g_CRT_TlsIndexDestroyHook = (_DWORD (*)())CRT_DestroyTlsIndexAndThreadData;
  g_CRT_ThreadDataConstructHookTable[0] = CRT_ConstructThreadDataBlock;
  _AddThreadData_(CRT_ConstructThreadDataBlock, lpTlsValue);
  TlsSetValue(dwTlsIndex, lpTlsValue);
  g_CrtThreadDataAccessor = (__int64 (__fastcall *)(_DWORD, _DWORD))CRT_GetOrCreateThreadDataPreserveLastError;
  return;
}
// 4864C7: using guessed type int j___NTAddFileHandle__0();
// 486518: using guessed type int sub_486518();
// 48657E: using guessed type int sub_48657E();
// 4B57DB: using guessed type int __fastcall _AddThreadData_(_DWORD, _DWORD);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);
// 51A574: using guessed type _DWORD (*off_51A574)();
// 51A578: using guessed type int (*off_51A578[14])();
// 51A57C: using guessed type _DWORD (*off_51A57C)();
// 51A580: using guessed type _DWORD (*off_51A580)();
// 51A584: using guessed type _DWORD (*off_51A584)();
// 51A588: using guessed type int (*off_51A588[10])();
// 51A58C: using guessed type _DWORD (*off_51A58C)();
// 51A590: using guessed type int (*off_51A590[8])();
// 51A594: using guessed type int (*off_51A594[7])();
// 51A598: using guessed type int (*off_51A598[6])();
// 51A59C: using guessed type int (*off_51A59C[5])();
// 51A5A0: using guessed type int (*off_51A5A0[4])();
// 51A5A4: using guessed type _DWORD (*off_51A5A4)();
// 51A62C: using guessed type int (*off_51A62C[3])();
// 51A630: using guessed type int (*off_51A630[2])();
// 51A634: using guessed type int (__fastcall *off_51A634)(_DWORD, _DWORD);
// 54DECC: using guessed type int dword_54DECC;
// 54DED0: using guessed type int dword_54DED0;

//----- (00486869) --------------------------------------------------------
int __thiscall CRT_ShutdownThreadAndFileHandleHooks(void *this)
{
  int v1; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx

  g_CRT_LockSlotResetHook(this, &g_CRT_FileHandleLockSlots);
  v3 = v1 + 256;
  do
    g_CRT_LockSlotResetHook(v2, v1 + 16);
  while ( v1 != v3 );
  g_CRT_LockSlotResetHook(v2, v1);
  j___FreeThreadDataList_();
  g_CRT_LockSlotResetHook(v5, v4);
  g_CRT_LockSlotResetHook(v7, v6);
  g_CRT_LockSlotResetHook(v9, v8);
  g_CRT_LockSlotResetHook(v11, v10);
  return CRT_FreeTlsIndex();
}
// 48687B: variable 'v1' is possibly undefined
// 486886: variable 'v2' is possibly undefined
// 4868A5: variable 'v5' is possibly undefined
// 4868A5: variable 'v4' is possibly undefined
// 4868B0: variable 'v7' is possibly undefined
// 4868B0: variable 'v6' is possibly undefined
// 4868BB: variable 'v9' is possibly undefined
// 4868BB: variable 'v8' is possibly undefined
// 4868C6: variable 'v11' is possibly undefined
// 4868C6: variable 'v10' is possibly undefined
// 48672B: using guessed type _DWORD loc_48672B();
// 4B58FA: using guessed type int j___FreeThreadDataList_(void);
// 51A634: using guessed type int (__fastcall *off_51A634)(_DWORD, _DWORD);

//----- (004869F0) --------------------------------------------------------
int  Surface_DDCopyBitmapToNewSurface(int directDraw, const CHAR *bitmapName, _DWORD *heightOut, int widthOut)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  int v9; // ecx
  _DWORD *width_ptr; // esi
  void *image_handle; // [esp+4h] [ebp-A0h]
  _DWORD surface_desc[2]; // [esp+8h] [ebp-9Ch] BYREF
  int surface_height; // [esp+10h] [ebp-94h]
  int surface_width; // [esp+14h] [ebp-90h]
  int surface_caps; // [esp+70h] [ebp-34h]
  _BYTE pv[4]; // [esp+74h] [ebp-30h] BYREF
  int bitmap_width; // [esp+78h] [ebp-2Ch]
  int bitmap_height; // [esp+7Ch] [ebp-28h]
  int new_surface; // [esp+8Ch] [ebp-18h] BYREF
  int v21; // [esp+90h] [ebp-14h]
  _DWORD *height_ptr; // [esp+94h] [ebp-10h]

  v21 = widthOut;
  height_ptr = heightOut;
  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, bitmapName, 0, 0, 0, 0x2000u);
  if ( !ImageA )
  {
    ImageA = LoadImageA(0, bitmapName, 0, 0, 0, 0x2010u);
    if ( !ImageA )
      return 0;
  }
  GetObjectA(ImageA, 24, pv);
  memset_(7, 0);
  surface_width = bitmap_width;
  surface_desc[1] = v9;
  surface_height = bitmap_height;
  surface_desc[0] = 108;
  surface_caps = 64;
  if ( (*(int (__stdcall **)(int, _DWORD *, int *, _DWORD))(*(_DWORD *)directDraw + 24))(directDraw, surface_desc, &new_surface, 0) )
    return 0;
  Surface_DDCopyBitmap(new_surface, ImageA, 0, 0, 0, 0);
  image_handle = ImageA;
  width_ptr = (_DWORD *)v21;
  DeleteObject(image_handle);
  *width_ptr = surface_width;
  *height_ptr = surface_height;
  return new_surface;
}
// 486A9B: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00486B10) --------------------------------------------------------
signed int  Surface_DDCopyBitmapFromFile(int surface, const CHAR *bitmapName)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  signed int copyResult; // ebx

  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, bitmapName, 0, 0, 0, 0x2000u);
  if ( !ImageA )
    ImageA = LoadImageA(0, bitmapName, 0, 0, 0, 0x2010u);
  if ( ImageA )
  {
    copyResult = Surface_DDCopyBitmap(surface, ImageA, 0, 0, 0, 0);
    if ( copyResult )
      OutputDebugStringA(aDdcopybitmapFa);
    DeleteObject(ImageA);
    return copyResult;
  }
  else
  {
    OutputDebugStringA(aHandleIsNull);
    return -2147467259;
  }
}

//----- (00486BA0) --------------------------------------------------------
signed int  Surface_DDCopyBitmap(int surface, void *bitmap, int x, int y, int dx, int dy)
{
  HDC CompatibleDC; // ebx
  int copy_width; // eax
  int copy_height; // edi
  _DWORD surface_desc[27]; // [esp+Ch] [ebp-A0h] BYREF
  _BYTE pv[4]; // [esp+78h] [ebp-34h] BYREF
  int bitmap_width; // [esp+7Ch] [ebp-30h]
  int hSrc; // [esp+80h] [ebp-2Ch]
  HDC hdcDest; // [esp+90h] [ebp-1Ch] BYREF
  int hr; // [esp+94h] [ebp-18h]
  int ySrc; // [esp+98h] [ebp-14h]
  int wSrc; // [esp+9Ch] [ebp-10h]

  ySrc = x;
  if ( !bitmap || !surface )
    return -2147467259;
  (*(void (__stdcall **)(int))(*(_DWORD *)surface + 108))(surface);
  CompatibleDC = CreateCompatibleDC(0);
  if ( !CompatibleDC )
    OutputDebugStringA(OutputString);
  SelectObject(CompatibleDC, bitmap);
  GetObjectA(bitmap, 24, pv);
  if ( dx )
    copy_width = dx;
  else
    copy_width = bitmap_width;
  wSrc = copy_width;
  if ( dy )
    copy_height = dy;
  else
    copy_height = hSrc;
  surface_desc[0] = 108;
  surface_desc[1] = 6;
  (*(void (__stdcall **)(int, _DWORD *))(*(_DWORD *)surface + 88))(surface, surface_desc);
  hr = (*(int (__stdcall **)(int, HDC *))(*(_DWORD *)surface + 68))(surface, &hdcDest);
  if ( !hr )
  {
    StretchBlt(hdcDest, 0, 0, surface_desc[3], surface_desc[2], CompatibleDC, y, ySrc, wSrc, copy_height, 0xCC0020u);
    (*(void (__stdcall **)(int, HDC))(*(_DWORD *)surface + 104))(surface, hdcDest);
  }
  DeleteDC(CompatibleDC);
  return hr;
}

//----- (00486CE0) --------------------------------------------------------
int  Surface_BuildPaletteFromBitmap(int pdd, const CHAR *bitmapName)
{
  int colorIndex; // ebx
  int byteOffset; // ecx
  __int64 v6; // rtt
  HRSRC ResourceA; // eax
  HGLOBAL Resource; // eax
  _DWORD *bitmapInfo; // esi
  _BYTE *rgbQuads; // edx
  int colorCount; // esi
  int copyIndex; // ecx
  _BYTE *quadPtr; // eax
  unsigned __int16 bitCount; // ax
  HFILE fileHandle; // ebx
  int fileColorCount; // esi
  int swapIndex; // eax
  char swapTemp; // dl
  _BYTE v20[4]; // [esp+0h] [ebp-458h]
  char paletteEntries[1024]; // [esp+4h] [ebp-454h] BYREF
  _DWORD bmpHeader[3]; // [esp+404h] [ebp-54h] BYREF
  unsigned __int16 biBitCount; // [esp+412h] [ebp-46h]
  int biClrUsed; // [esp+424h] [ebp-34h]
  _BYTE Buffer[16]; // [esp+42Ch] [ebp-2Ch] BYREF
  int ddPalette; // [esp+43Ch] [ebp-1Ch] BYREF
  int v27; // [esp+440h] [ebp-18h]

  colorIndex = 0;
  byteOffset = 0;
  do
  {
    paletteEntries[byteOffset] = 255 * ((colorIndex >> 5) & 7) / 7;
    v27 = 3;
    paletteEntries[byteOffset + 1] = 255 * ((colorIndex >> 2) & 7) / 7;
    LODWORD(v6) = 255 * (colorIndex & 3);
    HIDWORD(v6) = (colorIndex & 3u) / 0x808081;
    byteOffset += 4;
    v20[byteOffset + 2] = v6 / v27;
    ++colorIndex;
    v20[byteOffset + 3] = 0;
  }
  while ( colorIndex < 256 );
  if ( bitmapName && (ResourceA = FindResourceA(0, bitmapName, (LPCSTR)2)) != 0 )
  {
    Resource = LoadResource(0, ResourceA);
    bitmapInfo = LockResource(Resource);
    if ( !bitmapInfo )
      OutputDebugStringA(aLockResourceFa);
    rgbQuads = (char *)bitmapInfo + *bitmapInfo;
    if ( *bitmapInfo < 0x28u || (bitCount = *((_WORD *)bitmapInfo + 7), bitCount > 8u) )
    {
      colorCount = 0;
    }
    else if ( bitmapInfo[8] )
    {
      colorCount = bitmapInfo[8];
    }
    else
    {
      colorCount = 1 << bitCount;
    }
    copyIndex = 0;
    if ( colorCount > 0 )
    {
      quadPtr = rgbQuads;
      do
      {
        paletteEntries[4 * copyIndex] = quadPtr[2];
        paletteEntries[4 * copyIndex++ + 1] = quadPtr[1];
        v20[4 * copyIndex + 2] = *quadPtr;
        quadPtr += 4;
        v20[4 * copyIndex + 3] = 0;
      }
      while ( copyIndex < colorCount );
    }
  }
  else if ( bitmapName )
  {
    fileHandle = lopen(bitmapName, 0);
    if ( fileHandle != -1 )
    {
      lread(fileHandle, Buffer, 0xEu);
      lread(fileHandle, bmpHeader, 0x28u);
      lread(fileHandle, paletteEntries, 0x400u);
      lclose(fileHandle);
      if ( bmpHeader[0] == 40 && biBitCount <= 8u )
        fileColorCount = biClrUsed ? biClrUsed : 1 << biBitCount;
      else
        fileColorCount = 0;
      if ( fileColorCount > 0 )
      {
        swapIndex = 0;
        do
        {
          swapIndex += 4;
          swapTemp = v20[swapIndex];
          v20[swapIndex] = v20[swapIndex + 2];
          v20[swapIndex + 2] = swapTemp;
        }
        while ( swapIndex < 4 * fileColorCount );
      }
    }
  }
  (*(void (__stdcall **)(int, int, char *, int *, _DWORD))(*(_DWORD *)pdd + 20))(pdd, 4, paletteEntries, &ddPalette, 0);
  return ddPalette;
}
// 486CE0: too many cbuild loops

//----- (00486F00) --------------------------------------------------------
int  Surface_MatchColorToNativePixel(int pdds, COLORREF rgb, COLORREF Pixel)
{
  int matchedPixel; // esi
  int hres; // eax
  _DWORD surfaceDesc[21]; // [esp+0h] [ebp-84h] BYREF
  char rgbBitCount; // [esp+54h] [ebp-30h]
  HDC hdc[6]; // [esp+6Ch] [ebp-18h] BYREF

  matchedPixel = -1;
  if ( rgb != -1 && !(*(int (__stdcall **)(int, HDC *))(*(_DWORD *)pdds + 68))(pdds, hdc) )
  {
    Pixel = GetPixel(hdc[0], 0, 0);
    SetPixel(hdc[0], 0, 0, rgb);
    (*(void (__stdcall **)(int, HDC))(*(_DWORD *)pdds + 104))(pdds, hdc[0]);
  }
  surfaceDesc[0] = 108;
  do
    hres = (*(int (__stdcall **)(int, _DWORD, _DWORD *, _DWORD, _DWORD))(*(_DWORD *)pdds + 100))(pdds, 0, surfaceDesc, 0, 0);
  while ( hres == -2005532132 );
  if ( !hres )
  {
    matchedPixel = ((1 << rgbBitCount) - 1) & *(_DWORD *)surfaceDesc[9];
    (*(void (__stdcall **)(int, _DWORD))(*(_DWORD *)pdds + 128))(pdds, 0);
  }
  if ( rgb == -1 || (*(int (__stdcall **)(int, HDC *))(*(_DWORD *)pdds + 68))(pdds, hdc) )
    return matchedPixel;
  SetPixel(hdc[0], 0, 0, Pixel);
  (*(void (__stdcall **)(int, HDC))(*(_DWORD *)pdds + 104))(pdds, hdc[0]);
  return matchedPixel;
}

//----- (00487002) --------------------------------------------------------
int __fastcall CRT_RunRegisteredFinalizers(int a1, __lock *lock)
{
  int result; // eax
  int finalizerEntry; // edx
  __lock *v4; // [esp-8h] [ebp-8h]
  __lock *v5; // [esp-8h] [ebp-8h]

  v4 = lock;
  while ( 1 )
  {
    __lock_p(v4);
    if ( g_CrtFinalizerListHead )
      g_CrtFinalizerListHead = *(_DWORD *)g_CrtFinalizerListHead;
    __lock_v(v5);
    if ( !finalizerEntry )
      break;
    (*(void (**)(void))(*(_DWORD *)(finalizerEntry + 4) + 4))();
  }
  return result;
}
// 487009: variable 'v4' is possibly undefined
// 487024: variable 'v5' is possibly undefined
// 48702B: variable 'v3' is possibly undefined
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (0048703D) --------------------------------------------------------
int  CRT_RegisterFinalizer(int a1, __lock *lock, int a3)
{
  _DWORD *newEntry; // edx
  int result; // eax
  __lock *v6; // [esp-4h] [ebp-4h]

  g_CrtThreadDataAccessor(a3, a1);
  __lock_p(lock);
  *newEntry = g_CrtFinalizerListHead;
  g_CrtFinalizerListHead = (int)newEntry;
  __lock_v(v6);
  return result;
}
// 487055: variable 'v3' is possibly undefined
// 487062: variable 'v6' is possibly undefined
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (00487069) --------------------------------------------------------
int  CRT_PrintfFormatEngine(int stream, _BYTE *format, void (*outputFn)(void), int *argList)
{
  char *spec_ptr; // edi
  char v7; // al
  int v8; // edx
  _DWORD *nFarPtr; // edx
  int v10; // eoff
  int v11; // eax
  _DWORD *nDwordPtr; // edx
  int v13; // edi
  int v14; // ecx
  int v15; // ebx
  _WORD *nWordPtr; // edx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  unsigned __int16 *converted_text; // edi
  __int16 v21; // dx
  unsigned __int8 *buffer_ptr; // ebx
  int outputStream; // [esp+0h] [ebp-80h] BYREF
  int field_width; // [esp+4h] [ebp-7Ch]
  int char_count; // [esp+10h] [ebp-70h]
  char conversion_char; // [esp+15h] [ebp-6Bh]
  char pad_char; // [esp+16h] [ebp-6Ah]
  __int16 v29; // [esp+1Ch] [ebp-64h]
  __int16 flags; // [esp+1Eh] [ebp-62h]
  int prefix_len; // [esp+20h] [ebp-60h]
  int zero_pad_len; // [esp+24h] [ebp-5Ch]
  int text_len; // [esp+28h] [ebp-58h]
  int v34; // [esp+2Ch] [ebp-54h]
  int v35; // [esp+30h] [ebp-50h]
  int v36; // [esp+34h] [ebp-4Ch]
  unsigned __int8 conversion_buffer[40]; // [esp+38h] [ebp-48h] BYREF
  int argCursor; // [esp+60h] [ebp-20h] BYREF
  int convArgCursor; // [esp+64h] [ebp-1Ch] BYREF
  _BYTE *format_ptr; // [esp+68h] [ebp-18h]
  char v41; // [esp+6Ch] [ebp-14h]

  outputStream = stream;
  v41 = 0;
  format_ptr = format;
  flags = 0;
  v29 = 100;
  char_count = 0;
  while ( *format_ptr )
  {
    if ( *format_ptr == 37 )
    {
      argCursor = *argList;
      spec_ptr = CRT_ParseWidthPrecisionSpec(format_ptr + 1, &argCursor, (int)&outputStream);
      *argList = argCursor;
      v7 = *spec_ptr;
      conversion_char = v7;
      format_ptr = spec_ptr + 1;
      if ( !v7 )
        return char_count;
      if ( v7 == 110 )
      {
        if ( (flags & 0x20) != 0 )
        {
          if ( (flags & 0x80u) != 0 )
          {
            v8 = *argList + 8;
            *argList = v8;
            v10 = v8 - 8;
            nFarPtr = *(_DWORD **)(v8 - 8);
            __ES__ = *(_WORD *)(v10 + 4);
            goto LABEL_7;
          }
          if ( (flags & 0x40) != 0 )
          {
            v11 = *argList + 4;
            *argList = v11;
            nDwordPtr = *(_DWORD **)(v11 - 4);
            goto LABEL_11;
          }
LABEL_10:
          v13 = *argList + 4;
          *argList = v13;
          nDwordPtr = *(_DWORD **)(v13 - 4);
          goto LABEL_11;
        }
        if ( (flags & 0x10) != 0 )
        {
          if ( (flags & 0x80u) == 0 )
          {
            if ( (flags & 0x40) != 0 )
            {
              v15 = *argList + 4;
              *argList = v15;
              nWordPtr = *(_WORD **)(v15 - 4);
            }
            else
            {
              v17 = *argList + 4;
              *argList = v17;
              nWordPtr = *(_WORD **)(v17 - 4);
            }
            *nWordPtr = char_count;
          }
          else
          {
            v14 = *argList + 8;
            *argList = v14;
            *(_DWORD *)MK_FP(*(_WORD *)(v14 - 8 + 4), *(_DWORD *)(v14 - 8)) = char_count;
          }
        }
        else if ( (flags & 0x80u) == 0 )
        {
          if ( (flags & 0x40) != 0 )
            goto LABEL_10;
          v19 = *argList + 4;
          *argList = v19;
          nDwordPtr = *(_DWORD **)(v19 - 4);
LABEL_11:
          *nDwordPtr = char_count;
        }
        else
        {
          v18 = *argList + 8;
          *argList = v18;
          nFarPtr = *(_DWORD **)(v18 - 8);
          __ES__ = *(_WORD *)(v18 - 8 + 4);
LABEL_7:
          *nFarPtr = char_count;
        }
      }
      else
      {
        convArgCursor = *argList;
        converted_text = CRT_ConvertPrintfArgument(conversion_buffer, &convArgCursor, (int)&outputStream);
        __ES__ = v21;
        *argList = convArgCursor;
        field_width -= v36 + v35 + v34 + text_len + zero_pad_len + prefix_len;
        if ( (flags & 8) == 0 && pad_char == 32 )
        {
          while ( field_width > 0 )
          {
            outputFn();
            --field_width;
          }
        }
        buffer_ptr = conversion_buffer;
        while ( prefix_len > 0 )
        {
          outputFn();
          ++buffer_ptr;
          --prefix_len;
        }
        while ( zero_pad_len > 0 )
        {
          outputFn();
          --zero_pad_len;
        }
        if ( conversion_char == 115 )
        {
          if ( (flags & 0x20) != 0 )
            goto LABEL_37;
          while ( text_len > 0 )
          {
            outputFn();
            converted_text = (unsigned __int16 *)((char *)converted_text + 1);
            --text_len;
          }
        }
        else
        {
          if ( conversion_char == 83 )
          {
LABEL_37:
            CRT_OutputWideStringAsMultiByte(converted_text, __ES__, (unsigned __int8 *)outputFn, (int)&outputStream);
            goto LABEL_43;
          }
          while ( text_len > 0 )
          {
            ((void (__cdecl *)(int))outputFn)(outputStream);
            converted_text = (unsigned __int16 *)((char *)converted_text + 1);
            --text_len;
          }
        }
LABEL_43:
        while ( v34 > 0 )
        {
          outputFn();
          --v34;
        }
        while ( v35 > 0 )
        {
          outputFn();
          converted_text = (unsigned __int16 *)((char *)converted_text + 1);
          --v35;
        }
        while ( v36 > 0 )
        {
          outputFn();
          --v36;
        }
        if ( (flags & 8) != 0 )
        {
          while ( field_width > 0 )
          {
            outputFn();
            --field_width;
          }
        }
      }
    }
    else
    {
      ++format_ptr;
      outputFn();
    }
  }
  return char_count;
}
// 4871CA: variable 'v21' is possibly undefined

//----- (0048732A) --------------------------------------------------------
char * CRT_ParseWidthPrecisionSpec(char *formatPtr, int *args, int spec)
{
  char *result; // eax
  int v5; // edx
  int widthValue; // edx
  char v7; // ch
  int v8; // edx
  int v9; // edx
  int precisionValue; // edx
  int v11; // edx
  char modifierChar; // dl

  *(_BYTE *)(spec + 22) = 32;
  result = CRT_ParsePrintfFlags(formatPtr, spec);
  *(_DWORD *)(spec + 4) = 0;
  if ( *result == 42 )
  {
    v5 = *args + 4;
    *args = v5;
    widthValue = *(_DWORD *)(v5 - 4);
    *(_DWORD *)(spec + 4) = widthValue;
    if ( widthValue < 0 )
    {
      v7 = *(_BYTE *)(spec + 30) | 8;
      *(_DWORD *)(spec + 4) = -widthValue;
      *(_BYTE *)(spec + 30) = v7;
    }
    ++result;
  }
  else
  {
    while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
    {
      v8 = (unsigned __int8)*result++ - 48;
      *(_DWORD *)(spec + 4) = v8 + 10 * *(_DWORD *)(spec + 4);
    }
  }
  *(_DWORD *)(spec + 8) = -1;
  if ( *result == 46 )
  {
    ++result;
    *(_DWORD *)(spec + 8) = 0;
    if ( *result == 42 )
    {
      v9 = *args + 4;
      *args = v9;
      precisionValue = *(_DWORD *)(v9 - 4);
      *(_DWORD *)(spec + 8) = precisionValue;
      if ( precisionValue < 0 )
        *(_DWORD *)(spec + 8) = -1;
      ++result;
    }
    else
    {
      while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
      {
        v11 = (unsigned __int8)*result++ - 48;
        *(_DWORD *)(spec + 8) = v11 + 10 * *(_DWORD *)(spec + 8);
      }
    }
    if ( *(_DWORD *)(spec + 8) != -1 )
      *(_BYTE *)(spec + 22) = 32;
  }
  modifierChar = *result;
  if ( (unsigned __int8)*result >= 0x4Eu )
  {
    if ( (unsigned __int8)*result <= 0x4Eu )
    {
      *(_BYTE *)(spec + 30) |= 0x40u;
    }
    else
    {
      if ( (unsigned __int8)modifierChar >= 0x6Cu )
      {
        if ( (unsigned __int8)modifierChar <= 0x6Cu || modifierChar == 119 )
        {
          ++result;
          *(_BYTE *)(spec + 30) |= 0x20u;
        }
        return result;
      }
      if ( modifierChar != 104 )
        return result;
      *(_BYTE *)(spec + 30) |= 0x10u;
    }
    return ++result;
  }
  if ( (unsigned __int8)modifierChar < 0x49u )
  {
    if ( modifierChar != 70 )
      return result;
    *(_BYTE *)(spec + 30) |= 0x80u;
    return ++result;
  }
  if ( (unsigned __int8)modifierChar <= 0x49u )
  {
    if ( result[1] == 54 && result[2] == 52 )
    {
      result += 3;
      *(_BYTE *)(spec + 31) |= 1u;
    }
  }
  else if ( modifierChar == 76 )
  {
    ++result;
    *(_BYTE *)(spec + 31) |= 1u;
  }
  return result;
}

//----- (00487477) --------------------------------------------------------
char * CRT_ParsePrintfFlags(char *result, int spec)
{
  char flagChar; // bl
  char v3; // ch
  char v4; // bh

  *(_WORD *)(spec + 30) = 0;
  while ( 1 )
  {
    flagChar = *result;
    if ( *result == 45 )
    {
      *(_BYTE *)(spec + 30) |= 8u;
      goto LABEL_13;
    }
    if ( flagChar == 35 )
    {
      *(_BYTE *)(spec + 30) |= 1u;
      goto LABEL_13;
    }
    if ( flagChar == 43 )
    {
      v3 = *(_BYTE *)(spec + 30) | 4;
      *(_BYTE *)(spec + 30) = v3;
      *(_BYTE *)(spec + 30) = v3 & 0xFD;
      goto LABEL_13;
    }
    if ( flagChar != 32 )
      break;
    v4 = *(_BYTE *)(spec + 30);
    if ( (v4 & 4) == 0 )
      *(_BYTE *)(spec + 30) = v4 | 2;
LABEL_13:
    ++result;
  }
  if ( flagChar == 48 )
  {
    *(_BYTE *)(spec + 22) = 48;
    goto LABEL_13;
  }
  return result;
}

//----- (004874D4) --------------------------------------------------------
int  CRT_FarStrLenBounded(int stringOffset, __int16 stringSegment, int maxLength)
{
  int result; // eax
  char curr_char; // bl

  for ( result = 0; ; ++result )
  {
    curr_char = *(_BYTE *)MK_FP(stringSegment, stringOffset++);
    if ( !curr_char || result == maxLength )
      break;
  }
  return result;
}

//----- (004874F8) --------------------------------------------------------
int  CRT_WideCharToMultiByteLenBounded(unsigned __int16 *wideStr, __int16 segment, int maxLength)
{
  int byteCount; // ecx
  unsigned __int16 wideChar; // dx
  int charBytes; // eax
  int v10; // eax

  __ES__ = segment;
  byteCount = 0;
  if ( maxLength == -1 )
  {
    while ( *wideStr )
    {
      wideChar = *wideStr++;
      charBytes = wctomb_(byteCount, wideChar);
      if ( charBytes != -1 )
        byteCount += charBytes;
    }
    return byteCount;
  }
  while ( *wideStr && byteCount <= maxLength )
  {
    v10 = wctomb_(byteCount, *wideStr++);
    if ( v10 != -1 )
      byteCount += v10;
  }
  if ( byteCount <= maxLength )
    return byteCount;
  return maxLength;
}
// 48751E: variable 'v6' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);

//----- (00487561) --------------------------------------------------------
int  CRT_FormatPaddedHexDigits(signed int value, char *buffer, int digitCount)
{
  int result; // eax
  char *srcPtr; // edx
  char *destPtr; // ebx
  char *padPtr; // edx

  Str_FormatSignedRadixDigits(value, buffer, 0x10u);
  result = digitCount - 1;
  srcPtr = &buffer[strlen(buffer)];
  destPtr = &buffer[digitCount - 1];
  while ( srcPtr != buffer )
  {
    --srcPtr;
    --result;
    *destPtr-- = *srcPtr;
  }
  padPtr = &buffer[result];
  while ( result >= 0 )
  {
    --result;
    *padPtr-- = 48;
  }
  buffer[digitCount] = 0;
  return result;
}

//----- (004875BF) --------------------------------------------------------
char  CRT_FormatFixedDecimal(char *buffer, int value, int spec)
{
  char *digitsDest; // ecx
  _BYTE *v5; // eax
  _BYTE *digitPtr; // ecx
  _BYTE *digitsStart; // ebx
  _BYTE *roundPtr; // ecx
  int absValue; // [esp+0h] [ebp-10h]

  digitsDest = buffer;
  absValue = value;
  if ( value < 0 )
  {
    digitsDest = buffer + 1;
    *buffer = 45;
    absValue = -value;
  }
  if ( *(_DWORD *)(spec + 8) == -1 )
    *(_DWORD *)(spec + 8) = 4;
  LOBYTE(v5) = Str_FormatSignedRadixDigits(HIWORD(absValue), digitsDest, 0xAu);
  digitsStart = digitPtr;
  while ( *digitPtr )
    ++digitPtr;
  if ( *(_DWORD *)(spec + 8) )
  {
    *digitPtr = 46;
    v5 = 0;
    ++digitPtr;
    while ( (int)v5 < *(_DWORD *)(spec + 8) )
    {
      absValue = 10 * (unsigned __int16)absValue;
      ++v5;
      *digitPtr++ = BYTE2(absValue) + 48;
    }
    *digitPtr = 0;
  }
  if ( (absValue & 0x8000) != 0 )
  {
    while ( digitPtr != digitsStart )
    {
      if ( *--digitPtr == 46 )
        --digitPtr;
      LOBYTE(v5) = *digitPtr;
      if ( *digitPtr != 57 )
      {
        *digitPtr = (_BYTE)v5 + 1;
        return (char)v5;
      }
      *digitPtr = 48;
    }
    roundPtr = digitsStart + 1;
    *digitsStart = 49;
    while ( 1 )
    {
      v5 = roundPtr + 1;
      if ( *roundPtr != 48 )
        break;
      ++roundPtr;
    }
    if ( *roundPtr == 46 )
    {
      *roundPtr = 48;
      roundPtr += 2;
      *v5 = 46;
      while ( *roundPtr == 48 )
        ++roundPtr;
    }
    *roundPtr = 48;
    roundPtr[1] = 0;
  }
  return (char)v5;
}
// 4875FB: variable 'v6' is possibly undefined

//----- (0048769A) --------------------------------------------------------
// attributes: thunk
int CRT_DispatchFloatFormat()
{
  return g_FloatEfgFormatFn();
}
// 51AF04: using guessed type int (*off_51AF04)();

//----- (004876A1) --------------------------------------------------------
int  CRT_ApplyZeroPadWidth(int result)
{
  int v1; // esi
  int v2; // edi
  int v3; // ebp
  int v4; // ebx

  if ( (*(_BYTE *)(result + 30) & 8) == 0 && *(_BYTE *)(result + 22) == 48 )
  {
    v1 = *(_DWORD *)(result + 40);
    v2 = *(_DWORD *)(result + 44);
    v3 = *(_DWORD *)(result + 48);
    v4 = *(_DWORD *)(result + 52);
    if ( *(_DWORD *)(result + 4) - *(_DWORD *)(result + 32) - *(_DWORD *)(result + 36) - v1 - v2 - v3 - v4 > 0 )
      *(_DWORD *)(result + 36) = *(_DWORD *)(result + 4) - *(_DWORD *)(result + 32) - v1 - v2 - v3 - v4;
  }
  return result;
}

//----- (004876E4) --------------------------------------------------------
unsigned __int16 * CRT_OutputWideStringAsMultiByte(
        unsigned __int16 *result,
        __int16 segment,
        unsigned __int8 *a3,
        int spec)
{
  unsigned __int16 *widePtr; // esi
  void (__fastcall *putcFn)(unsigned __int8 *, _DWORD); // ebp
  int mbLength; // edi
  int v7; // ecx
  int mbBuffer; // [esp+0h] [ebp-14h] BYREF

  __ES__ = segment;
  widePtr = result;
  putcFn = (void (__fastcall *)(unsigned __int8 *, _DWORD))a3;
  while ( *(int *)(spec + 40) > 0 )
  {
    result = (unsigned __int16 *)wctomb_(a3, *widePtr++);
    mbLength = (int)result;
    if ( result != (unsigned __int16 *)-1 )
    {
      if ( (int)result > *(_DWORD *)(spec + 40) )
      {
        *(_DWORD *)(spec + 40) = 0;
        return result;
      }
      a3 = (unsigned __int8 *)&mbBuffer;
      while ( --mbLength != -1 )
      {
        putcFn(a3, *a3);
        result = (unsigned __int16 *)(*(_DWORD *)(spec + 40) - 1);
        a3 = (unsigned __int8 *)(v7 + 1);
        *(_DWORD *)(spec + 40) = result;
      }
    }
  }
  return result;
}
// 4876FF: variable 'a3' is possibly undefined
// 487727: variable 'v7' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);

//----- (0048773C) --------------------------------------------------------
unsigned __int16 * CRT_ConvertPrintfArgument(unsigned __int8 *outputBuffer, int *argList, int formatCtx)
{
  int ctx; // ecx
  unsigned __int16 *result_text; // edi
  unsigned __int8 format_char; // al
  bool v7; // zf
  int v8; // ebx
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebp
  int v14; // eax
  int v15; // ebx
  int v16; // ebp
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  char v20; // al
  int v21; // eax
  int v22; // eax
  unsigned __int8 conversion_char; // al
  bool v24; // zf
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  int v28; // ecx
  char v29; // al
  int v30; // ebp
  int v31; // esi
  unsigned __int16 *string_arg; // eax
  int v33; // ebx
  int string_length; // eax
  int v35; // ecx
  int v36; // edx
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int formattedLength; // eax
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // eax
  signed int pointer_value; // ebp
  int v46; // eax
  char *v47; // edx
  signed int v48; // eax
  int v49; // ecx
  int converted_length; // eax
  int v51; // ecx
  char format_flags; // bl
  int wideCharArgCursor; // ebx
  int v54; // ecx
  int mbcsCodePageActive; // ebp
  int charArgCursor; // eax
  int arg_ptr; // ebp
  int valueLow; // [esp+0h] [ebp-20h]
  __int64 value64; // [esp+4h] [ebp-1Ch]
  unsigned __int8 mbLeadByte; // [esp+Ch] [ebp-14h]
  unsigned __int8 mbTrailByte; // [esp+Dh] [ebp-13h]

  ctx = formatCtx;
  __ES__ = __DS__;
  *(_DWORD *)(formatCtx + 32) = 0;
  *(_DWORD *)(formatCtx + 36) = 0;
  *(_DWORD *)(formatCtx + 40) = 0;
  *(_DWORD *)(formatCtx + 44) = 0;
  *(_DWORD *)(formatCtx + 48) = 0;
  result_text = (unsigned __int16 *)outputBuffer;
  format_char = *(_BYTE *)(formatCtx + 21);
  *(_DWORD *)(formatCtx + 52) = 0;
  if ( format_char < 0x69u )
  {
    if ( format_char < 0x58u )
      goto LABEL_42;
    if ( format_char <= 0x58u )
      goto LABEL_13;
    if ( format_char != 100 )
      goto LABEL_42;
  }
  else if ( format_char > 0x69u )
  {
    if ( format_char < 0x75u )
    {
      v7 = format_char == 111;
LABEL_6:
      if ( !v7 )
        goto LABEL_42;
      goto LABEL_13;
    }
    if ( format_char > 0x75u )
    {
      v7 = format_char == 120;
      goto LABEL_6;
    }
LABEL_13:
    if ( (*(_BYTE *)(formatCtx + 31) & 1) == 0 )
    {
      if ( (*(_BYTE *)(formatCtx + 30) & 0x20) != 0 )
      {
        v11 = *argList + 4;
        *argList = v11;
        v12 = *(_DWORD *)(v11 - 4);
      }
      else
      {
        v13 = *argList + 4;
        *argList = v13;
        HIDWORD(value64) = *(_DWORD *)(v13 - 4);
        if ( (*(_BYTE *)(formatCtx + 30) & 0x10) == 0 )
          goto LABEL_42;
        v12 = WORD2(value64);
      }
      HIDWORD(value64) = v12;
      goto LABEL_42;
    }
    v8 = *argList + 4;
    *argList = v8;
    valueLow = *(_DWORD *)(v8 - 4);
    v9 = *argList + 4;
    *argList = v9;
    v10 = *(_DWORD *)(v9 - 4);
    goto LABEL_15;
  }
  if ( (*(_BYTE *)(formatCtx + 31) & 1) == 0 )
  {
    if ( (*(_BYTE *)(formatCtx + 30) & 0x20) != 0 )
    {
      v16 = *argList + 4;
      *argList = v16;
      v17 = *(_DWORD *)(v16 - 4);
    }
    else
    {
      v18 = *argList + 4;
      *argList = v18;
      HIDWORD(value64) = *(_DWORD *)(v18 - 4);
      if ( (*(_BYTE *)(ctx + 30) & 0x10) == 0 )
        goto LABEL_28;
      v17 = *(int *)((char *)&value64 + 2) >> 16;
    }
    HIDWORD(value64) = v17;
    goto LABEL_28;
  }
  v14 = *argList + 4;
  *argList = v14;
  valueLow = *(_DWORD *)(v14 - 4);
  v15 = *argList + 4;
  *argList = v15;
  LODWORD(value64) = *(_DWORD *)(v15 - 4);
LABEL_28:
  if ( (*(_BYTE *)(ctx + 31) & 1) != 0 )
  {
    if ( (value64 & 0x80000000LL) != 0 )
      goto LABEL_33;
  }
  else if ( value64 < 0 )
  {
LABEL_33:
    v19 = *(_DWORD *)(ctx + 32);
    *(_DWORD *)(ctx + 32) = v19 + 1;
    outputBuffer[v19] = 45;
    if ( (*(_BYTE *)(ctx + 31) & 1) == 0 )
    {
      HIDWORD(value64) = -HIDWORD(value64);
      goto LABEL_42;
    }
    valueLow = -valueLow;
    if ( valueLow )
      v10 = ~(_DWORD)value64;
    else
      v10 = -(int)value64;
LABEL_15:
    LODWORD(value64) = v10;
    goto LABEL_42;
  }
  v20 = *(_BYTE *)(ctx + 30);
  if ( (v20 & 4) != 0 )
  {
    v21 = *(_DWORD *)(ctx + 32);
    *(_DWORD *)(ctx + 32) = v21 + 1;
    outputBuffer[v21] = 43;
  }
  else if ( (v20 & 2) != 0 )
  {
    v22 = *(_DWORD *)(ctx + 32);
    *(_DWORD *)(ctx + 32) = v22 + 1;
    outputBuffer[v22] = 32;
  }
LABEL_42:
  conversion_char = *(_BYTE *)(ctx + 21);
  if ( conversion_char >= 0x64u )
  {
    if ( conversion_char <= 0x64u )
      goto LABEL_104;
    if ( conversion_char >= 0x6Fu )
    {
      if ( conversion_char <= 0x6Fu )
        goto LABEL_101;
      if ( conversion_char >= 0x73u )
      {
        if ( conversion_char > 0x73u )
        {
          if ( conversion_char >= 0x75u )
          {
            if ( conversion_char <= 0x75u )
              goto LABEL_104;
            if ( conversion_char != 120 )
              goto LABEL_139;
LABEL_94:
            if ( (*(_BYTE *)(ctx + 30) & 1) != 0 )
            {
              if ( (*(_BYTE *)(ctx + 31) & 1) != 0 )
              {
                if ( valueLow || (_DWORD)value64 )
                  goto LABEL_100;
              }
              else if ( HIDWORD(value64) )
              {
LABEL_100:
                v37 = *(_DWORD *)(ctx + 32);
                *(_DWORD *)(ctx + 32) = v37 + 1;
                outputBuffer[v37] = 48;
                v38 = *(_DWORD *)(ctx + 32);
                *(_DWORD *)(ctx + 32) = v38 + 1;
                outputBuffer[v38] = *(_BYTE *)(ctx + 21);
              }
            }
LABEL_101:
            if ( *(_BYTE *)(ctx + 21) == 111 && (*(_BYTE *)(ctx + 30) & 1) != 0 )
            {
              v39 = *(_DWORD *)(ctx + 32);
              *(_DWORD *)(ctx + 32) = v39 + 1;
              outputBuffer[v39] = 48;
            }
            goto LABEL_104;
          }
LABEL_139:
          *(_DWORD *)(ctx + 4) = 0;
          *outputBuffer = *(_BYTE *)(ctx + 21);
          *(_DWORD *)(ctx + 32) = 1;
          return result_text;
        }
LABEL_77:
        *outputBuffer = 0;
        v29 = *(_BYTE *)(ctx + 30);
        if ( v29 >= 0 )
        {
          if ( (v29 & 0x40) != 0 )
          {
            v31 = *argList + 4;
            *argList = v31;
            string_arg = *(unsigned __int16 **)(v31 - 4);
            if ( !string_arg )
              goto LABEL_86;
          }
          else
          {
            v33 = *argList + 4;
            *argList = v33;
            string_arg = *(unsigned __int16 **)(v33 - 4);
            if ( !string_arg )
              goto LABEL_86;
          }
          result_text = string_arg;
          __ES__ = __DS__;
        }
        else
        {
          v30 = *argList + 8;
          *argList = v30;
          if ( *(_DWORD *)(v30 - 8) || *(_WORD *)(v30 - 4) )
          {
            __ES__ = *(_WORD *)(v30 - 4);
            result_text = *(unsigned __int16 **)(v30 - 8);
          }
        }
LABEL_86:
        if ( *(_BYTE *)(ctx + 21) == 83 )
        {
          if ( (*(_BYTE *)(ctx + 30) & 0x10) == 0 )
          {
LABEL_88:
            string_length = CRT_WideCharToMultiByteLenBounded(result_text, __ES__, *(_DWORD *)(ctx + 8));
LABEL_91:
            v36 = *(_DWORD *)(v35 + 8);
            *(_DWORD *)(v35 + 40) = string_length;
            if ( v36 >= 0 && string_length > v36 )
              *(_DWORD *)(v35 + 40) = v36;
            return result_text;
          }
        }
        else if ( (*(_BYTE *)(ctx + 30) & 0x20) != 0 )
        {
          goto LABEL_88;
        }
        string_length = CRT_FarStrLenBounded((int)result_text, __ES__, *(_DWORD *)(ctx + 8));
        goto LABEL_91;
      }
      v24 = conversion_char == 112;
      goto LABEL_53;
    }
    if ( conversion_char >= 0x66u )
    {
      if ( conversion_char > 0x66u )
      {
        if ( conversion_char > 0x67u )
        {
          if ( conversion_char != 105 )
            goto LABEL_139;
LABEL_104:
          result_text = (unsigned __int16 *)&outputBuffer[*(_DWORD *)(ctx + 32)];
          if ( (*(_BYTE *)(ctx + 31) & 1) != 0 )
          {
            if ( !*(_DWORD *)(ctx + 8) && !valueLow && !(_DWORD)value64 )
            {
LABEL_108:
              outputBuffer[*(_DWORD *)(ctx + 32)] = 0;
              formattedLength = 0;
LABEL_116:
              *(_DWORD *)(ctx + 40) = formattedLength;
              v42 = formattedLength;
              v43 = *(_DWORD *)(ctx + 8);
              if ( v42 < v43 )
                *(_DWORD *)(ctx + 36) = v43 - v42;
              if ( *(_DWORD *)(ctx + 8) == -1 )
                CRT_ApplyZeroPadWidth(ctx);
              return result_text;
            }
            _clib_ulltoa_(ctx, &outputBuffer[*(_DWORD *)(ctx + 32)]);
            if ( *(_BYTE *)(v41 + 21) == 88 )
              goto LABEL_114;
          }
          else
          {
            if ( !*(_DWORD *)(ctx + 8) && !HIDWORD(value64) )
              goto LABEL_108;
            CRT_SignedLongToDecimalString(ctx, &outputBuffer[*(_DWORD *)(ctx + 32)]);
            if ( *(_BYTE *)(v41 + 21) == 88 )
LABEL_114:
              CRT_ToUpperInPlace(outputBuffer, v41);
          }
          formattedLength = CRT_FarStrLenBounded((int)result_text, __DS__, -1);
          goto LABEL_116;
        }
        goto LABEL_76;
      }
LABEL_74:
      if ( (*(_BYTE *)(ctx + 30) & 0x10) != 0 )
      {
        v25 = *argList + 4;
        *argList = v25;
        CRT_FormatFixedDecimal((char *)outputBuffer, *(_DWORD *)(v25 - 4), ctx);
        v26 = CRT_FarStrLenBounded((int)outputBuffer, __DS__, '\xFF');
        *(_DWORD *)(v27 + 40) = v26;
        return result_text;
      }
    }
LABEL_76:
    CRT_DispatchFloatFormat();
    CRT_ApplyZeroPadWidth(v28);
    return (unsigned __int16 *)(outputBuffer + 1);
  }
  if ( conversion_char < 0x47u )
  {
    if ( conversion_char < 0x45u )
    {
      if ( conversion_char != 67 )
        goto LABEL_139;
      arg_ptr = *argList + 4;
      *argList = arg_ptr;
      converted_length = wctomb_(ctx, *(unsigned __int16 *)(arg_ptr - 4));
      if ( converted_length == -1 )
      {
        *(_DWORD *)(v51 + 32) = 0;
        return result_text;
      }
      goto LABEL_130;
    }
    if ( conversion_char > 0x45u )
      goto LABEL_74;
    goto LABEL_76;
  }
  if ( conversion_char <= 0x47u )
    goto LABEL_76;
  if ( conversion_char < 0x53u )
  {
    v24 = conversion_char == 80;
LABEL_53:
    if ( !v24 )
      goto LABEL_139;
    if ( !*(_DWORD *)(ctx + 4) )
    {
      if ( *(char *)(ctx + 30) >= 0 )
        *(_DWORD *)(ctx + 4) = 8;
      else
        *(_DWORD *)(ctx + 4) = 13;
    }
    *(_BYTE *)(ctx + 30) &= 0xF9u;
    v44 = *argList + 4;
    *argList = v44;
    pointer_value = *(_DWORD *)(v44 - 4);
    if ( *(char *)(ctx + 30) >= 0 )
    {
      v47 = (char *)outputBuffer;
      v48 = *(_DWORD *)(v44 - 4);
    }
    else
    {
      v46 = v44 + 4;
      *argList = v46;
      CRT_FormatPaddedHexDigits((unsigned __int16)*(_DWORD *)(v46 - 4), (char *)outputBuffer, 4);
      v47 = (char *)(outputBuffer + 5);
      v48 = pointer_value;
      outputBuffer[4] = 58;
    }
    CRT_FormatPaddedHexDigits(v48, v47, 8);
    if ( *(_BYTE *)(v49 + 21) == 80 )
      CRT_ToUpperInPlace(outputBuffer, v49);
    converted_length = CRT_FarStrLenBounded((int)outputBuffer, __DS__, -1);
LABEL_130:
    *(_DWORD *)(v51 + 32) = converted_length;
    return result_text;
  }
  if ( conversion_char <= 0x53u )
    goto LABEL_77;
  if ( conversion_char < 0x58u )
    goto LABEL_139;
  if ( conversion_char <= 0x58u )
    goto LABEL_94;
  if ( conversion_char != 99 )
    goto LABEL_139;
  format_flags = *(_BYTE *)(ctx + 30);
  *(_DWORD *)(ctx + 32) = 1;
  if ( (format_flags & 0x20) != 0 )
  {
    wideCharArgCursor = *argList + 4;
    *argList = wideCharArgCursor;
    if ( wctomb_(ctx, *(unsigned __int16 *)(wideCharArgCursor - 4)) != -1 )
    {
      mbcsCodePageActive = g_CRT_MbcsCodePageActive;
      *outputBuffer = mbLeadByte;
      if ( mbcsCodePageActive )
      {
        if ( (g_Clips_DbcsLeadByteTable[mbLeadByte] & 1) != 0 )
        {
          outputBuffer[1] = mbTrailByte;
          ++*(_DWORD *)(v54 + 32);
        }
      }
    }
  }
  else
  {
    charArgCursor = *argList + 4;
    *argList = charArgCursor;
    *outputBuffer = *(_BYTE *)(charArgCursor - 4);
  }
  return result_text;
}
// 487859: variable 'v60' is possibly undefined
// 4878A6: variable 'v59' is possibly undefined
// 4879CB: variable 'v27' is possibly undefined
// 4879DE: variable 'v28' is possibly undefined
// 487A6A: variable 'v35' is possibly undefined
// 487B25: variable 'v41' is possibly undefined
// 487B6A: variable 'v4' is possibly undefined
// 487BFA: variable 'v49' is possibly undefined
// 487C15: variable 'v51' is possibly undefined
// 487C58: variable 'v61' is possibly undefined
// 487C77: variable 'v62' is possibly undefined
// 487C7A: variable 'v54' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);
// 4B5946: using guessed type int __fastcall _clib_ulltoa_(_DWORD, _DWORD);
// 4B5A33: using guessed type int __fastcall sub_4B5A33(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

//----- (00487CD8) --------------------------------------------------------
_BYTE * CRT_ToUpperInPlace(_BYTE *result, int a2)
{
  _BYTE *i; // edx
  _BYTE *v3; // edx

  for ( i = result; *i; i = v3 + 1 )
  {
    result = (_BYTE *)toupper_(a2);
    *v3 = (_BYTE)result;
  }
  return result;
}
// 487CE4: variable 'a2' is possibly undefined
// 487CE9: variable 'v3' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004880E1) --------------------------------------------------------
int Mem_NearMallocHookStub()
{
  return 0;
}

//----- (0048817D) --------------------------------------------------------
unsigned int  CRT_OpenFile(DWORD pmode, const CHAR *path, int openFlags)
{
  return CRT_OpenFileShared(pmode, path, openFlags, 0);
}

//----- (004881A1) --------------------------------------------------------
unsigned int  CRT_OpenFileShared(DWORD pmode, const CHAR *fileName, int openMode, int shareFlags)
{
  return CRT_CreateFileHandleFromPath(fileName, openMode, shareFlags, pmode);
}

//----- (004881C8) --------------------------------------------------------
unsigned int  CRT_CreateFileHandleFromPath(const CHAR *fileName, int openMode, int extraOpenFlags, DWORD retryDisposition)
{
  char v5; // dl
  int access_bits; // esi
  DWORD file_attributes; // ebx
  int *v9; // ecx
  unsigned int file_descriptor; // edi
  int v11; // ebp
  DWORD creation_disposition; // eax
  HANDLE FileA; // ecx
  void *v14; // ecx
  struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+0h] [ebp-2Ch] BYREF
  DWORD dwShareMode; // [esp+Ch] [ebp-20h] BYREF
  DWORD dwDesiredAccess; // [esp+10h] [ebp-1Ch] BYREF
  int v18; // [esp+14h] [ebp-18h] BYREF
  int v19; // [esp+18h] [ebp-14h]
  int v20; // [esp+1Ch] [ebp-10h]

  v20 = openMode;
  v19 = extraOpenFlags;
  if ( _NTAtMaxFiles_() )
    goto LABEL_2;
  access_bits = v5 & 7;
  CRT_MapAccessModeToCreateFileFlags(access_bits, &dwDesiredAccess, &v18);
  file_attributes = 128;
  CRT_MapOpenFlagsToCreationDisposition(access_bits | v19, &dwShareMode);
  SecurityAttributes.lpSecurityDescriptor = 0;
  SecurityAttributes.nLength = 12;
  SecurityAttributes.bInheritHandle = (v20 & 0x80u) == 0;
  if ( g_CRT_ConsoleOpenHook && !stricmp_(v9, aCon_0) )
  {
    _NTGetFakeHandle_(
      SecurityAttributes.nLength,
      SecurityAttributes.lpSecurityDescriptor,
      SecurityAttributes.bInheritHandle);
    file_descriptor = g_CRT_AddFileHandleHook();
    g_CRT_ConsoleOpenHook(0, file_descriptor, -1);
    goto LABEL_26;
  }
  if ( (v20 & 0x20) != 0 )
  {
    v11 = *v9 + 4;
    *v9 = v11;
    v18 = *(_DWORD *)(v11 - 4);
    *v9 = 0;
    v18 &= ~g_CRT_OpenModeStripMask;
    if ( (v18 & 0x100) != 0 && (v18 & 0x80u) == 0 )
      file_attributes = 1;
    if ( (v20 & 0x400) != 0 )
    {
      retryDisposition = 1;
      creation_disposition = 1;
      goto LABEL_18;
    }
    if ( (v20 & 0x40) != 0 )
    {
      retryDisposition = 2;
LABEL_14:
      creation_disposition = 5;
      goto LABEL_18;
    }
    retryDisposition = 4;
  }
  else if ( (v20 & 0x40) != 0 )
  {
    goto LABEL_14;
  }
  creation_disposition = 3;
LABEL_18:
  FileA = CreateFileA(fileName, dwDesiredAccess, dwShareMode, &SecurityAttributes, creation_disposition, file_attributes, 0);
  if ( FileA == (HANDLE)-1 )
  {
    if ( (v20 & 0x20) != 0 )
      FileA = CreateFileA(fileName, dwDesiredAccess, dwShareMode, 0, retryDisposition, file_attributes, 0);
    if ( FileA == (HANDLE)-1 )
      return _set_errno_nt_(SecurityAttributes.nLength);
  }
  file_descriptor = g_CRT_AddFileHandleHook();
  if ( file_descriptor >= g_CRT_MaxFileDescriptor )
  {
    CloseHandle(v14);
LABEL_2:
    _set_errno_(SecurityAttributes.nLength);
    return -1;
  }
  isatty_(v14, 0);
LABEL_26:
  _SetIOMode_(SecurityAttributes.nLength, SecurityAttributes.lpSecurityDescriptor, SecurityAttributes.bInheritHandle);
  return file_descriptor;
}
// 488386: simplified comparisons for 'esi.4': ==0 || !=1 became !=1
// 48837D: simplified comparisons for 'esi.4': ==2 || !=1 became !=1
// 4881FB: variable 'v5' is possibly undefined
// 48824F: variable 'v9' is possibly undefined
// 48835B: variable 'v14' is possibly undefined
// 484E2A: using guessed type int __fastcall stricmp_(_DWORD, _DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 48537A: using guessed type _DWORD j___NTAddFileHandle_();
// 488DC0: using guessed type int __cdecl _SetIOMode_(_DWORD, _DWORD, _DWORD);
// 4B4B00: using guessed type int _NTAtMaxFiles_(void);
// 4B4CEE: using guessed type int __cdecl _NTGetFakeHandle_(_DWORD, _DWORD, _DWORD);
// 4B5C24: using guessed type int __fastcall isatty_(_DWORD, _DWORD);
// 51A549: using guessed type int dword_51A549;
// 51A574: using guessed type _DWORD (*off_51A574)();
// 51A5BC: using guessed type int (__cdecl *dword_51A5BC)(_DWORD, _DWORD, _DWORD);
// 51A768: using guessed type int dword_51A768;
// 51AF64: using guessed type int dword_51AF64;

//----- (00488514) --------------------------------------------------------
DWORD Process_GetCurrentId()
{
  return GetCurrentProcessId();
}

//----- (00488BDC) --------------------------------------------------------
signed int  CRT_MkTime(_DWORD *brokenDownTime)
{
  int rawYear; // esi
  int month; // edi
  int year; // esi
  char *monthDayTable; // ecx
  int dayCount; // edi
  int i; // esi
  int utcSeconds; // esi
  int adjustedSeconds; // esi

  rawYear = brokenDownTime[5];
  month = brokenDownTime[4] % 12;
  if ( rawYear < -184844639 )
    return -1;
  year = brokenDownTime[4] / 12 + rawYear;
  while ( month < 0 )
  {
    --year;
    month += 12;
  }
  if ( year < 0 )
    return -1;
  if ( CRT_IsLeapYear(year + 1900) )
    monthDayTable = (char *)&g_CRT_LeapMonthDayTable + 2;
  dayCount = brokenDownTime[3]
     + (year + 299) / 400
     + ((year + 3 - (__CFSHL__((year + 3) >> 31, 2) + 4 * ((year + 3) >> 31))) >> 2)
     + 365 * year
     - (year + 99) / 100
     + *(__int16 *)&monthDayTable[2 * month]
     - 1;
  for ( i = 60 * (60 * brokenDownTime[2] + brokenDownTime[1]) + *brokenDownTime; i < 0; i += 86400 )
    --dayCount;
  _brktime_(brokenDownTime, i);
  CRT_TzSet();
  utcSeconds = g_CRT_TimezoneSeconds + i;
  if ( (int)brokenDownTime[8] < 0 )
    CRT_IsDaylightTime(brokenDownTime);
  if ( (int)brokenDownTime[8] > 0 )
    utcSeconds -= g_CRT_DaylightBiasSeconds;
  while ( utcSeconds < 0 )
  {
    --dayCount;
    utcSeconds += 86400;
  }
  if ( dayCount < 25566 )
    return -1;
  if ( dayCount != 25566 )
    return 86400 * (dayCount - 25567) + utcSeconds;
  adjustedSeconds = utcSeconds - 86400;
  if ( g_CRT_TimezoneSeconds <= 0 || adjustedSeconds < 0 )
    return -1;
  return adjustedSeconds;
}
// 488C9B: variable 'v6' is possibly undefined
// 4B6243: using guessed type int __fastcall _brktime_(_DWORD, _DWORD);
// 5110EE: using guessed type int dword_5110EE;
// 511108: using guessed type int dword_511108;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0C2: using guessed type int dword_51B0C2;

//----- (00488DE1) --------------------------------------------------------
int  CRT_PutcCallbackForWrite(_DWORD *writeContext, int ch)
{
  int result; // eax

  result = CRT_PutcToStream(ch, *writeContext);
  ++writeContext[4];
  return result;
}
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (00488DF2) --------------------------------------------------------
int  CRT_VfprintfLockedWrite(int stream, int format, int *argList)
{
  int lock_key;
  int stream_state;
  int busy_state;
  int saved_mode_bits;
  int flush_after_write;
  int write_result;
  unsigned char stream_flags;

  lock_key = *(_DWORD *)(stream + 16);
  g_CRT_FileHandleLockAcquireHook(lock_key);
  stream_state = *(_DWORD *)(stream + 8);
  busy_state = *(_DWORD *)(stream_state + 12);
  if ( busy_state != 1 )
  {
    if ( busy_state )
    {
      g_CRT_FileHandleLockReleaseHook(lock_key, 0);
      return 0;
    }
    *(_DWORD *)(stream_state + 12) = 1;
  }
  saved_mode_bits = *(_DWORD *)(stream + 12) & 0x30;
  *(_BYTE *)(stream + 12) &= 0xCFu;
  if ( !*(_DWORD *)(*(_DWORD *)(stream + 8) + 8) )
    _ioalloc_();
  flush_after_write = 0;
  if ( (*(_BYTE *)(stream + 13) & 4) != 0 )
  {
    stream_flags = *(_BYTE *)(stream + 13) & 0xFA;
    *(_BYTE *)(stream + 13) = stream_flags;
    *(_BYTE *)(stream + 13) = stream_flags | 1;
    flush_after_write = 1;
  }
  write_result = CRT_PrintfFormatEngine(stream, (_BYTE *)(uintptr_t)(unsigned int)format, (void (*)(void))CRT_PutcCallbackForWrite, argList);
  if ( flush_after_write )
  {
    stream_flags = *(_BYTE *)(stream + 13) & 0xFA;
    *(_BYTE *)(stream + 13) = stream_flags;
    *(_BYTE *)(stream + 13) = stream_flags | 4;
    _flush_(stream, write_result);
  }
  if ( (*(_BYTE *)(stream + 12) & 0x20) != 0 )
    write_result = -1;
  *(_DWORD *)(stream + 12) |= saved_mode_bits;
  g_CRT_FileHandleLockReleaseHook(lock_key, write_result);
  return write_result;
}
// 4886DD: using guessed type int __fastcall _flush_(_DWORD, _DWORD);
// 488946: using guessed type int _ioalloc_(void);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (00488EB2) --------------------------------------------------------
DWORD  CRT_ReadFileHandle(int fileDescriptor, int buffer, DWORD length)
{
  void *v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  DWORD NumberOfBytesRead; // [esp+0h] [ebp-Ch] BYREF
  int v12; // [esp+8h] [ebp-4h]

  v12 = buffer;
  if ( fileDescriptor >= 0 && fileDescriptor <= (unsigned int)g_CRT_MaxFileDescriptor )
  {
    g_CRT_FileHandleLockAcquireHook(buffer);
    if ( g_CRT_CustomReadHook && g_CRT_CustomReadAvailablePredicateHook() )
    {
      v6 = g_CRT_CustomReadHook();
      g_CRT_FileHandleLockReleaseHook(v7, v6);
      return v8;
    }
    else if ( ReadFile(*(HANDLE *)(g_CRT_OsHandleTable + 4 * fileDescriptor), v5, length, &NumberOfBytesRead, 0) )
    {
      g_CRT_FileHandleLockReleaseHook(v10, v9);
      return NumberOfBytesRead;
    }
    else
    {
      g_CRT_FileHandleLockReleaseHook(v10, v9);
      return _set_errno_nt_(NumberOfBytesRead);
    }
  }
  else
  {
    _set_errno_(NumberOfBytesRead);
    return -1;
  }
}
// 488EFB: variable 'v7' is possibly undefined
// 488F01: variable 'v8' is possibly undefined
// 488F19: variable 'v5' is possibly undefined
// 488F26: variable 'v10' is possibly undefined
// 488F26: variable 'v9' is possibly undefined
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);
// 51A5B4: using guessed type int (*dword_51A5B4)(void);
// 51A5DC: using guessed type int (*dword_51A5DC)(void);
// 51A768: using guessed type int dword_51A768;
// 51AED0: using guessed type int dword_51AED0;

//----- (004890EC) --------------------------------------------------------
void CRT_InstallFloatPrintfSupport()
{
  g_FloatEfgFormatFn = EFG_Format_;
  g_StringToDoubleScanFn = (int (__fastcall *)(_DWORD, _DWORD))_cnvs2d_;
}
// 489119: using guessed type int _cnvs2d_();
// 4B681E: using guessed type int EFG_Format_();
// 51AF04: using guessed type int (*off_51AF04)();
// 51AF08: using guessed type int (__fastcall *off_51AF08)(_DWORD, _DWORD);

//----- (00489D18) --------------------------------------------------------
int  CRT_DeleteFile(const CHAR *path, int a2)
{
  if ( DeleteFileA(path) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489DAA) --------------------------------------------------------
signed int  CRT_FlushBufferAndPutChar(signed int result, int lockKey)
{
  signed int char_value; // ebx
  unsigned __int8 **stream; // edx
  unsigned __int8 *stream_state; // eax
  unsigned __int8 *v6; // ecx
  unsigned __int8 *v7; // ebp
  unsigned __int8 *v8; // edi
  unsigned __int8 *v9; // ebp

  char_value = result;
  if ( result != -1 )
  {
    g_CRT_FileHandleLockAcquireHook(lockKey);
    stream_state = stream[2];
    v6 = (unsigned __int8 *)*((_DWORD *)stream_state + 3);
    if ( v6 != (unsigned __int8 *)1 )
    {
      if ( v6 )
      {
LABEL_4:
        g_CRT_FileHandleLockReleaseHook(v6, stream);
        return -1;
      }
      *((_DWORD *)stream_state + 3) = 1;
    }
    if ( (*((_BYTE *)stream + 13) & 0x10) != 0 || ((_BYTE)stream[3] & 1) == 0 )
      goto LABEL_4;
    if ( !*((_DWORD *)stream[2] + 2) )
      _ioalloc_();
    v7 = stream[1];
    if ( v7 )
    {
      v6 = *stream;
      if ( *stream == *((unsigned __int8 **)stream[2] + 2) )
        goto LABEL_4;
      v8 = v7 + 1;
      v9 = *stream;
      stream[1] = v8;
      *stream = --v9;
      if ( *v9 == char_value )
        goto LABEL_15;
    }
    else
    {
      stream[1] = (unsigned __int8 *)1;
      v6 = stream[5];
      *stream = &v6[*((_DWORD *)stream[2] + 2) - 1];
    }
    *((_BYTE *)stream + 12) |= 4u;
LABEL_15:
    **stream = char_value;
    *((_BYTE *)stream + 12) &= ~0x10u;
    g_CRT_FileHandleLockReleaseHook(v6, stream);
    return (unsigned __int8)char_value;
  }
  return result;
}
// 489DC2: variable 'v4' is possibly undefined
// 488946: using guessed type int _ioalloc_(void);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

static DWORD Compat_FileTimeToUnixSeconds(DWORD low_part, DWORD high_part)
{
  unsigned long long filetime_ticks;

  filetime_ticks = ((unsigned long long)high_part << 32) | low_part;
  if ( filetime_ticks < 116444736000000000ULL )
    return 0;
  return (DWORD)((filetime_ticks - 116444736000000000ULL) / 10000000ULL);
}

//----- (00489E64) --------------------------------------------------------
signed int  CRT_FindFirstFile(const CHAR *pathPattern, _DWORD *findBuffer, int attributes)
{
  HANDLE find_handle; // eax
  WIN32_FIND_DATAA find_data; // [esp+0h] [ebp-140h] BYREF

  (void)attributes;
  find_handle = FindFirstFileA(pathPattern, &find_data);
  if ( find_handle == (HANDLE)-1 )
    return _set_errno_nt_(0);
  CRT_FillFindDataRecord((int)(intptr_t)&find_data, findBuffer);
  return (signed int)(intptr_t)find_handle;
}

//----- (00489EC6) --------------------------------------------------------
char  CRT_FillFindDataRecord(int winFindData, _DWORD *findBuffer)
{
  WIN32_FIND_DATAA *find_data; // esi

  find_data = (WIN32_FIND_DATAA *)(uintptr_t)(unsigned int)winFindData;
  if ( !find_data || !findBuffer )
    return 0;
  *findBuffer = 0;
  if ( (find_data->dwFileAttributes & 0x20) != 0 )
    *(_BYTE *)findBuffer |= 0x20u;
  if ( (find_data->dwFileAttributes & 0x10) != 0 )
    *(_BYTE *)findBuffer |= 0x10u;
  if ( (find_data->dwFileAttributes & 2) != 0 )
    *(_BYTE *)findBuffer |= 2u;
  if ( (find_data->dwFileAttributes & 1) != 0 )
    *(_BYTE *)findBuffer |= 1u;
  if ( (find_data->dwFileAttributes & 4) != 0 )
    *(_BYTE *)findBuffer |= 4u;
  findBuffer[1] = Compat_FileTimeToUnixSeconds(find_data->ftCreationTimeLow, find_data->ftCreationTimeHigh);
  findBuffer[2] = Compat_FileTimeToUnixSeconds(find_data->ftLastAccessTimeLow, find_data->ftLastAccessTimeHigh);
  findBuffer[3] = Compat_FileTimeToUnixSeconds(find_data->ftLastWriteTimeLow, find_data->ftLastWriteTimeHigh);
  findBuffer[4] = find_data->nFileSizeLow;
  qmemcpy((char *)(findBuffer + 5), find_data->cFileName, sizeof(find_data->cFileName));
  return 0;
}

//----- (00489FBA) --------------------------------------------------------
int  CRT_MakeDirectory(const CHAR *path, int a2)
{
  if ( CreateDirectoryA(path, 0) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489FD7) --------------------------------------------------------
int  CRT_RemoveDirectory(const CHAR *path, int a2)
{
  if ( RemoveDirectoryA(path) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (0048A080) --------------------------------------------------------
_DWORD * IO_StreambufAlloc(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax

  result = (_DWORD *)Mem_Alloc(4, a1, a2, a3);
  if ( result )
    *result = g_IOStreambuf_VTable;
  return result;
}
// 511054: using guessed type int (*off_511054[4])();

//----- (0048A0A0) --------------------------------------------------------
int Rules_Builtin_0()
{
  return 0;
}

//----- (0048A0C0) --------------------------------------------------------
void *Rules_Builtin_1()
{
  return &g_Rules_BuiltinSentinelAddress;
}

//----- (0048A0D0) --------------------------------------------------------
int Rules_Builtin_2()
{
  return 0;
}

//----- (0048A0E0) --------------------------------------------------------
int Rules_Builtin_3()
{
  return 0;
}

//----- (0048A0F0) --------------------------------------------------------
int IO_StreambufStubZero()
{
  return 0;
}

//----- (0048A100) --------------------------------------------------------
_DWORD * IO_StreambufAllocDerived(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax

  result = (_DWORD *)Mem_Alloc(4, a1, a2, a3);
  if ( result )
    *result = g_FuncTable_511094;
  return result;
}
// 511094: using guessed type int (*g_FuncTable_511094[6])();

//----- (0048A120) --------------------------------------------------------
_DWORD * IO_StreambufInitVTable(_DWORD *result)
{
  *result = g_IOStreambuf_VTable;
  return result;
}
// 511054: using guessed type int (*off_511054[4])();

//----- (0048A170) --------------------------------------------------------
int Rules_Builtin_4()
{
  return 0;
}

//----- (0048A180) --------------------------------------------------------
int  Rules_ConstructHandleVectorDtor(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesHandleVector_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 48A1A9: variable 'v4' is possibly undefined
// 48A1A0: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0048A1B0) --------------------------------------------------------
_DWORD * Rules_ConstructRecordInitVTable(_DWORD *result)
{
  *result = g_FuncTable_511094;
  return result;
}
// 511094: using guessed type int (*g_FuncTable_511094[6])();

//----- (0048A1C0) --------------------------------------------------------
int  Rules_ConstructRecordVectorDtor(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesRecordArrayDtorSlot);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 48A1E9: variable 'v4' is possibly undefined
// 48A1E0: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0048A230) --------------------------------------------------------
signed int Rules_RegisterFactsConstruct()
{
  Rules_RegisterPatternConstraintEvaluators();
  return Rules_AddPatternParser(
           (int)aFacts_2,
           0,
           (int)CSyncObject_Unlock,
           (int)&g_Rules_FactPatternEntityRecord,
           (int)Rules_ParseFactPatternRelation,
           0,
           (int)Rules_ParseDeftemplateSlotList,
           (int)Rules_FreeDeftemplateSlotList,
           0,
           (int)PP_PatchHighTierConst,
           (int)PP_ParsePrimary,
           (int)Rules_BuildFieldRangeOrValueConstraintNode,
           (int)Rules_BuildFieldIndexConstraintNode,
           (int)PP_PatchLowTierConst,
           (int)PP_MakeLowTierConst,
           (int)Rules_BuildFieldRangeConstraintNode,
           0,
           0,
           (int)Rules_PropagatePatternNodeResetFlag,
           (int)Rules_RematchAllFactsAgainstPatternNetwork,
           (int)Rules_CreateInitialFactPatternNode,
           (int)Rules_FactPatternNetworkWriteNodeRefToCode);
}
// 4B6DD0: using guessed type int .fn_init(void);

//----- (0048A2A0) --------------------------------------------------------
_DWORD * Rules_ParseDeftemplateSlotList(int thePattern, _DWORD *theSlot)
{
  int parseTree; // eax
  _BYTE *deftemplateName; // ebx
  int prunedTree; // eax
  int nextNode; // ecx
  int fieldNode; // esi
  int i; // eax
  BOOL withinMultifield; // ebp
  int v11; // edx
  int precedingSlot; // [esp+0h] [ebp-28h] BYREF
  int count; // [esp+4h] [ebp-24h] BYREF
  _DWORD *lastSlot; // [esp+8h] [ebp-20h]
  int savedNode; // [esp+Ch] [ebp-1Ch]

  parseTree = *(_DWORD *)(thePattern + 64);
  deftemplateName = *(_BYTE **)(*(_DWORD *)(*(_DWORD *)(parseTree + 68) + 4) + 16);
  prunedTree = Rules_PruneDeftemplateParseTree(parseTree);
  *(_DWORD *)(thePattern + 64) = prunedTree;
  nextNode = *(_DWORD *)(prunedTree + 64);
  savedNode = 0;
  if ( nextNode )
  {
    *(_DWORD *)(thePattern + 64) = nextNode;
    savedNode = prunedTree;
    *(_DWORD *)(prunedTree + 64) = 0;
    AST_FreeNode(prunedTree);
  }
  else
  {
    AST_Free(*(_DWORD *)(prunedTree + 52));
    *(_DWORD *)(*(_DWORD *)(thePattern + 64) + 52) = v11;
  }
  g_ClipsDeftemplateBeingParsedPtr = Rules_FindImportExportConstruct(aDeftemplate_5, &count, deftemplateName, 1, 0);
  lastSlot = 0;
  fieldNode = *(_DWORD *)(thePattern + 64);
  for ( i = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32); fieldNode; i = theSlot[7] )
  {
    if ( (*(_BYTE *)(fieldNode + 8) & 4) != 0 )
    {
      savedNode = fieldNode;
      fieldNode = *(_DWORD *)(fieldNode + 68);
    }
    withinMultifield = !*(_DWORD *)(fieldNode + 64) && savedNode;
    theSlot = (_DWORD *)Rules_FindDuplicateDeftemplateSlot(i, (int *)fieldNode, withinMultifield, &precedingSlot);
    if ( !theSlot )
      theSlot = Rules_CreateDeftemplateSlot((int *)fieldNode, precedingSlot, withinMultifield, (int)lastSlot);
    if ( !*(_DWORD *)(fieldNode + 64) && savedNode )
    {
      fieldNode = savedNode;
      savedNode = 0;
    }
    fieldNode = *(_DWORD *)(fieldNode + 64);
    if ( !fieldNode )
      *((_BYTE *)theSlot + 12) |= 4u;
    lastSlot = theSlot;
  }
  return theSlot;
}
// 48A395: variable 'v11' is possibly undefined
// 54E514: using guessed type int dword_54E514;

//----- (0048A3B0) --------------------------------------------------------
int  Rules_FindDuplicateDeftemplateSlot(int slotList, int *fieldNode, int withinMultifield, int *precedingSlot)
{
  int curSlot; // esi
  int nodeType; // edx

  curSlot = slotList;
  *precedingSlot = 0;
  if ( !slotList )
    return 0;
  do
  {
    while ( 1 )
    {
      nodeType = *fieldNode;
      if ( *fieldNode == 17 || nodeType == 15 )
      {
        if ( (*(_BYTE *)(curSlot + 12) & 1) != 0
          && *(_DWORD *)(curSlot + 12) << 25 >> 31 == withinMultifield
          && (unsigned __int8)*(_DWORD *)(curSlot + 20) == fieldNode[8]
          && *(_DWORD *)(curSlot + 20) << 16 >> 24 == fieldNode[10] - 1
          && AST_NodeListsEqual(*(__int16 **)(curSlot + 24), (__int16 *)fieldNode[13]) )
        {
          return curSlot;
        }
        goto LABEL_8;
      }
      if ( nodeType != 18 && nodeType != 16 )
        break;
      if ( (*(_BYTE *)(curSlot + 12) & 2) != 0
        && *(_DWORD *)(curSlot + 12) << 25 >> 31 == withinMultifield
        && *(_DWORD *)(curSlot + 20) << 8 >> 24 == (unsigned int)(fieldNode[3] << 18) >> 25
        && (unsigned __int8)*(_DWORD *)(curSlot + 20) == fieldNode[8]
        && *(_DWORD *)(curSlot + 20) << 16 >> 24 == fieldNode[10] - 1
        && AST_NodeListsEqual(*(__int16 **)(curSlot + 24), (__int16 *)fieldNode[13]) )
      {
        return curSlot;
      }
LABEL_8:
      *precedingSlot = curSlot;
      curSlot = *(_DWORD *)(curSlot + 40);
      if ( !curSlot )
        return 0;
    }
    *precedingSlot = curSlot;
    curSlot = *(_DWORD *)(curSlot + 40);
  }
  while ( curSlot );
  return 0;
}
// 48A3D9: variable 'a3' is possibly undefined

//----- (0048A4A0) --------------------------------------------------------
int  Rules_PruneDeftemplateParseTree(int nodeList)
{
  int curNode; // ecx
  int listHead; // esi
  int prevNode; // ebx
  int nodeType; // edx
  signed int constExpr; // eax
  int v7; // ecx
  _DWORD *ShouldEmit; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // ecx
  int prunedChild; // eax

  curNode = nodeList;
  listHead = nodeList;
  prevNode = 0;
  if ( !nodeList )
    return listHead;
  do
  {
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
              while ( 1 )
              {
                nodeType = *(_DWORD *)curNode;
                if ( *(_DWORD *)curNode != 17 && nodeType != 15 )
                  break;
                if ( *(_DWORD *)(curNode + 52) )
                  break;
                if ( prevNode )
                  *(_DWORD *)(prevNode + 64) = *(_DWORD *)(curNode + 64);
                else
                  listHead = *(_DWORD *)(curNode + 64);
                *(_DWORD *)(curNode + 64) = 0;
                AST_FreeNode(curNode);
                if ( !prevNode )
                  goto LABEL_21;
                curNode = *(_DWORD *)(prevNode + 64);
                if ( !curNode )
                  return listHead;
              }
              if ( *(_DWORD *)curNode != 18 && *(_DWORD *)curNode != 16
                || (*(_BYTE *)(curNode + 8) & 4) != 0
                || *(_DWORD *)(curNode + 52)
                || (*(_DWORD *)(curNode + 8) & 0x3F8000) != 0
                || (*(_WORD *)(curNode + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( prevNode )
                *(_DWORD *)(prevNode + 64) = *(_DWORD *)(curNode + 64);
              else
                listHead = *(_DWORD *)(curNode + 64);
              *(_DWORD *)(curNode + 64) = 0;
              AST_FreeNode(curNode);
              if ( !prevNode )
                goto LABEL_21;
              curNode = *(_DWORD *)(prevNode + 64);
              if ( !curNode )
                return listHead;
            }
            if ( *(_DWORD *)curNode != 18 && *(_DWORD *)curNode != 16
              || (*(_BYTE *)(curNode + 8) & 4) != 0
              || !*(_DWORD *)(curNode + 52)
              || (*(_DWORD *)(curNode + 8) & 0x3F8000) != 0
              || (*(_WORD *)(curNode + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)curNode = 17;
            prevNode = curNode;
            curNode = *(_DWORD *)(curNode + 64);
            if ( !curNode )
              return listHead;
          }
          if ( *(_DWORD *)curNode != 18 || (*(_BYTE *)(curNode + 8) & 4) == 0 || *(_DWORD *)(curNode + 68) )
            break;
          *(_DWORD *)curNode = 17;
          constExpr = PP_MakeConst25(curNode, nodeType);
          *(_DWORD *)(v7 + 52) = constExpr;
          *(_BYTE *)(v7 + 8) &= ~4u;
LABEL_41:
          prevNode = v7;
          curNode = *(_DWORD *)(v7 + 64);
          if ( !curNode )
            return listHead;
        }
        if ( *(_DWORD *)curNode == 18 && (*(_BYTE *)(curNode + 8) & 4) != 0 )
          break;
        prevNode = curNode;
        curNode = *(_DWORD *)(curNode + 64);
        if ( !curNode )
          return listHead;
      }
      ShouldEmit = (_DWORD *)PP_ShouldEmit(*(_DWORD *)(curNode + 68));
      v10 = AST_MergeFieldAccessNodes(ShouldEmit, *(_DWORD **)(*(_DWORD *)(v9 + 68) + 52));
      *(_DWORD *)(*(_DWORD *)(v11 + 68) + 52) = v10;
      prunedChild = Rules_PruneDeftemplateParseTree(*(_DWORD *)(v11 + 68));
      *(_DWORD *)(v7 + 68) = prunedChild;
      if ( prunedChild )
        goto LABEL_41;
      if ( prevNode )
        *(_DWORD *)(prevNode + 64) = *(_DWORD *)(v7 + 64);
      else
        listHead = *(_DWORD *)(v7 + 64);
      *(_DWORD *)(v7 + 64) = 0;
      AST_FreeNode(v7);
      if ( prevNode )
        break;
LABEL_21:
      curNode = listHead;
      if ( !listHead )
        return 0;
    }
    curNode = *(_DWORD *)(prevNode + 64);
  }
  while ( curNode );
  return listHead;
}
// 48A5EF: variable 'v7' is possibly undefined
// 48A612: variable 'v9' is possibly undefined
// 48A61D: variable 'v11' is possibly undefined

//----- (0048A670) --------------------------------------------------------
_DWORD * Rules_CreateDeftemplateSlot(int *fieldNode, int precedingSlot, char withinMultifield, int lastSlot)
{
  _DWORD *freeListHead; // ecx
  signed int newSlot; // ecx
  unsigned int v9; // eax
  int v10; // ecx
  int minFields; // eax
  int v12; // edx
  int maxFields; // ecx
  int nodeType; // eax
  __int16 *slotNameChain; // eax
  _DWORD *slotRecord; // edx
  int v18; // eax
  int prevChild; // eax
  int existingHeadSlot; // ebx

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 176);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = *freeListHead;
    newSlot = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSlot = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(newSlot + 28) = 0;
  *(_DWORD *)(newSlot + 40) = 0;
  *(_DWORD *)(newSlot + 36) = 0;
  v9 = (unsigned int)(fieldNode[3] << 18) >> 25 << 16;
  *(_BYTE *)(newSlot + 22) = 0;
  *(_DWORD *)(newSlot + 20) |= v9;
  Rules_ResetDataObjectValue(newSlot);
  minFields = fieldNode[8];
  v12 = v10;
  *(_BYTE *)(v10 + 20) = 0;
  if ( minFields > 0 )
    *(_DWORD *)(v10 + 20) |= (unsigned __int8)minFields;
  maxFields = fieldNode[10];
  if ( maxFields < 0 )
  {
    v18 = (unsigned __int8)*(_DWORD *)(v12 + 20);
    *(_BYTE *)(v12 + 21) = 0;
    *(_DWORD *)(v12 + 20) |= v18 << 8;
  }
  else
  {
    *(_BYTE *)(v12 + 21) = 0;
    maxFields = ((unsigned __int8)(maxFields - 1) << 8) | *(_DWORD *)(v12 + 20);
    *(_DWORD *)(v12 + 20) = maxFields;
  }
  nodeType = *fieldNode;
  if ( *fieldNode == 17 || nodeType == 15 )
  {
    *(_BYTE *)(v12 + 12) |= 1u;
  }
  else if ( nodeType == 18 || nodeType == 16 )
  {
    *(_BYTE *)(v12 + 12) |= 2u;
  }
  BYTE1(maxFields) = *(_BYTE *)(v12 + 12) & 0xBF;
  *(_BYTE *)(v12 + 12) = BYTE1(maxFields);
  *(_DWORD *)(v12 + 12) |= (withinMultifield & 1) << 6;
  slotNameChain = AST_AddHashedNodeChain((__int16 *)fieldNode[13], v12, maxFields);
  slotRecord[6] = slotNameChain;
  slotRecord[8] = lastSlot;
  if ( !precedingSlot )
  {
    if ( lastSlot )
    {
      *(_DWORD *)(lastSlot + 28) = slotRecord;
      return slotRecord;
    }
LABEL_11:
    *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32) = slotRecord;
    return slotRecord;
  }
  if ( lastSlot )
  {
    prevChild = *(_DWORD *)(lastSlot + 28);
    slotRecord[10] = prevChild;
    if ( prevChild )
      *(_DWORD *)(prevChild + 36) = slotRecord;
    *(_DWORD *)(lastSlot + 28) = slotRecord;
    return slotRecord;
  }
  else
  {
    slotRecord[10] = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32);
    existingHeadSlot = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32);
    if ( !existingHeadSlot )
      goto LABEL_11;
    *(_DWORD *)(existingHeadSlot + 36) = slotRecord;
    *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32) = slotRecord;
    return slotRecord;
  }
}
// 48A6D8: variable 'v10' is possibly undefined
// 48A735: variable 'v16' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E514: using guessed type int dword_54E514;

//----- (0048A7E0) --------------------------------------------------------
int  Rules_FreeDeftemplateSlotList(int slotList)
{
  int result; // eax
  int v3; // ecx
  int currentNode; // ecx
  int nodeToFree; // ebx
  int parentNode; // ecx
  char parentFlags; // dl
  int prevNode; // edi
  int nextNode; // eax
  _DWORD *freedNode; // ebx
  int lastNode; // ebx
  int ownerNode; // ecx

  result = Rules_PurgeDeftemplateSlotReferences(slotList);
  if ( !*(_DWORD *)(v3 + 8) )
    *(_BYTE *)(v3 + 12) &= ~4u;
  if ( !*(_DWORD *)(slotList + 28) )
  {
    currentNode = slotList;
    while ( !*(_DWORD *)(currentNode + 36) && !*(_DWORD *)(currentNode + 40) )
    {
      nodeToFree = currentNode;
      parentNode = *(_DWORD *)(currentNode + 32);
      if ( parentNode )
      {
        parentFlags = *(_BYTE *)(parentNode + 12);
        *(_DWORD *)(parentNode + 28) = 0;
        if ( (parentFlags & 4) != 0 )
          parentNode = 0;
      }
      else
      {
        Rules_PatchDeftemplateSlotModuleRef(0, 0);
      }
      AST_RemoveHashedNodeChain(*(__int16 **)(nodeToFree + 24), parentNode);
      g_ClipsMemFreeListTemp = nodeToFree;
      *(_DWORD *)nodeToFree = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      if ( !currentNode )
        return result;
    }
    prevNode = *(_DWORD *)(currentNode + 36);
    if ( prevNode )
    {
      nextNode = *(_DWORD *)(currentNode + 40);
      freedNode = (_DWORD *)currentNode;
      *(_DWORD *)(prevNode + 40) = nextNode;
      if ( nextNode )
        *(_DWORD *)(nextNode + 36) = *(_DWORD *)(currentNode + 36);
      AST_RemoveHashedNodeChain(*(__int16 **)(currentNode + 24), currentNode);
      g_ClipsMemFreeListTemp = (int)freedNode;
      *freedNode = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
    else
    {
      lastNode = currentNode;
      ownerNode = *(_DWORD *)(currentNode + 32);
      if ( ownerNode )
        *(_DWORD *)(ownerNode + 28) = *(_DWORD *)(lastNode + 40);
      else
        Rules_PatchDeftemplateSlotModuleRef(0, *(_DWORD *)(lastNode + 40));
      *(_DWORD *)(*(_DWORD *)(lastNode + 40) + 36) = 0;
      AST_RemoveHashedNodeChain(*(__int16 **)(lastNode + 24), ownerNode);
      g_ClipsMemFreeListTemp = lastNode;
      *(_DWORD *)lastNode = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 48A7EE: variable 'v3' is possibly undefined
// 48A7FC: variable 'v4' is possibly undefined
// 48A81E: variable 'v6' is possibly undefined
// 48A8D3: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048A910) --------------------------------------------------------
int __fastcall Rules_PatchDeftemplateSlotModuleRef(int oldSlotHead, int newPatternHead)
{
  int Enum; // ebx
  int theDeftemplate; // edx
  int v5; // ecx
  int result; // eax
  int v7; // edx

  Module_BeginEnum();
  Enum = Module_NextEnum(0);
  if ( !Enum )
    return Module_EndEnum();
  while ( 1 )
  {
    Module_SetCurrent(Enum);
    theDeftemplate = Rules_GetNextDeftemplate(0);
    if ( theDeftemplate )
      break;
LABEL_5:
    Enum = Module_NextEnum(Enum);
    if ( !Enum )
      return Module_EndEnum();
  }
  while ( v5 != *(_DWORD *)(theDeftemplate + 32) )
  {
    theDeftemplate = Rules_GetNextDeftemplate(theDeftemplate);
    if ( !theDeftemplate )
      goto LABEL_5;
  }
  result = Module_EndEnum();
  *(_DWORD *)(v7 + 32) = newPatternHead;
  return result;
}
// 48A940: variable 'v5' is possibly undefined
// 48A96A: variable 'v7' is possibly undefined

//----- (0048A980) --------------------------------------------------------
int  Rules_PurgeDeftemplateSlotReferences(int patternNode)
{
  int result; // eax
  int i; // ecx
  _DWORD *matchLink; // eax
  _DWORD *prevLink; // edx

  result = Rules_GetNextFact(0);
  for ( i = result; result; i = result )
  {
    matchLink = *(_DWORD **)(i + 20);
    prevLink = 0;
    while ( matchLink )
    {
      if ( patternNode == matchLink[2] )
      {
        if ( prevLink )
        {
          *prevLink = *matchLink;
          g_ClipsMemFreeListTemp = (int)matchLink;
          *matchLink = *(_DWORD *)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          matchLink = (_DWORD *)*prevLink;
        }
        else
        {
          *(_DWORD *)(i + 20) = *matchLink;
          g_ClipsMemFreeListTemp = (int)matchLink;
          *matchLink = *(_DWORD *)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          matchLink = *(_DWORD **)(i + 20);
        }
      }
      else
      {
        prevLink = matchLink;
        matchLink = (_DWORD *)*matchLink;
      }
    }
    result = Rules_GetNextFact(i);
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AA20) --------------------------------------------------------
int  Rules_HashFactEntry(int theFact)
{
  int relation_slot; // eax
  int relation_symbol; // eax
  int relation_hash; // edx
  int field_hash; // eax
  int result; // eax

  relation_slot = *(_DWORD *)((uintptr_t)(unsigned int)theFact + 16);
  relation_symbol = *(_DWORD *)(uintptr_t)(unsigned int)relation_slot;
  relation_hash = Rules_HashSymbolName(
    (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)relation_symbol + 16),
    0x3F5u);
  field_hash = Rules_HashFactFieldList(theFact + 40);
  result = (field_hash + relation_hash) % 1013;
  if ( result < 0 )
    return -result;
  return result;
}

//----- (0048AA80) --------------------------------------------------------
int  Rules_HashFactFieldList(int theSegment)
{
  int fieldPtr; // ebx
  int fieldCount; // ebp
  int hashValue; // ecx
  int fieldIndex; // edi
  int multiplier; // esi
  int fieldHash; // eax
  int value; // eax

  fieldPtr = theSegment + 14;
  fieldCount = *(_DWORD *)(theSegment + 6);
  hashValue = 0;
  fieldIndex = 0;
  if ( fieldCount > 0 )
  {
    multiplier = 29;
    do
    {
      switch ( *(_WORD *)fieldPtr )
      {
        case CLIPS_TYPE_FLOAT:
          value = *(_DWORD *)(fieldPtr + 2);
          fieldHash = multiplier * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case CLIPS_TYPE_INTEGER:
          value = *(_DWORD *)(fieldPtr + 2);
          fieldHash = multiplier * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case CLIPS_TYPE_SYMBOL:
        case CLIPS_TYPE_STRING:
        case CLIPS_TYPE_INSTANCE_NAME:
          value = *(_DWORD *)(fieldPtr + 2);
          fieldHash = multiplier
             * Rules_HashSymbolName(
                 (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)value + 16),
                 0x3F5u);
          goto LABEL_5;
        case CLIPS_TYPE_MULTIFIELD:
          fieldHash = Rules_HashFactFieldList(*(_DWORD *)(fieldPtr + 2));
          goto LABEL_5;
        case CLIPS_TYPE_EXTERNAL_ADDRESS:
        case CLIPS_TYPE_FACT_ADDRESS:
        case CLIPS_TYPE_INSTANCE_ADDRESS:
          fieldHash = multiplier * *(_DWORD *)(fieldPtr + 2);
LABEL_5:
          hashValue += fieldHash;
          break;
        default:
          break;
      }
      fieldPtr += 6;
      ++fieldIndex;
      ++multiplier;
    }
    while ( fieldIndex < fieldCount );
  }
  return hashValue;
}

//----- (0048AB10) --------------------------------------------------------
int  Rules_FindFactInHashTable(int theFact, int hashValue)
{
  int hashEntry; // ecx
  int candidate; // edx

  hashEntry = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsFactHashTable + 4 * hashValue);
  if ( !hashEntry )
    return 0;
  while ( 1 )
  {
    candidate = *(_DWORD *)(uintptr_t)(unsigned int)hashEntry;
    if ( *(_DWORD *)((uintptr_t)(unsigned int)theFact + 16) == *(_DWORD *)((uintptr_t)(unsigned int)candidate + 16)
      && Rules_MultifieldsEqual(theFact + 40, candidate + 40) )
      return candidate;
    hashEntry = *(_DWORD *)((uintptr_t)(unsigned int)hashEntry + 4);
    if ( !hashEntry )
      return 0;
  }
}
// 54E518: using guessed type int dword_54E518;

//----- (0048AB50) --------------------------------------------------------
int * Rules_InsertFactHashEntry(int theFact, int hashValue)
{
  int v2; // ecx
  _DWORD *freeEntry; // ebx
  int *result; // eax
  int bucket_head; // edx
  int oldBucketHead; // ecx

  v2 = theFact;
  freeEntry = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeEntry;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *result = v2;
  bucket_head = g_ClipsFactHashTable + 4 * hashValue;
  oldBucketHead = *(_DWORD *)bucket_head;
  *(_DWORD *)bucket_head = (int)(uintptr_t)result;
  result[1] = oldBucketHead;
  return result;
}
// 48AB70: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E518: using guessed type int dword_54E518;

//----- (0048ABA0) --------------------------------------------------------
signed int  Rules_RemoveFactHashEntry(int theFact)
{
  uintptr_t target; // edx
  int bucket; // ebx
  uintptr_t bucket_slot; // ecx
  uintptr_t current; // eax
  uintptr_t previous; // ecx

  target = (uintptr_t)(unsigned int)theFact;
  bucket = Rules_HashFactEntry((int)target);
  bucket_slot = (uintptr_t)(unsigned int)g_ClipsFactHashTable + 4 * bucket;
  current = (uintptr_t)(unsigned int)*(_DWORD *)bucket_slot;
  previous = 0;
  while ( current )
  {
    if ( (int)target == *(_DWORD *)current )
    {
      int next = *(_DWORD *)(current + 4);
      if ( previous )
        *(_DWORD *)(previous + 4) = next;
      else
        *(_DWORD *)bucket_slot = next;
      g_ClipsMemFreeListTemp = (int)current;
      *(_DWORD *)current = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      return 1;
    }
    previous = current;
    current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
  }
  return 1;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E518: using guessed type int dword_54E518;

//----- (0048AC20) --------------------------------------------------------
signed int  Rules_DeduplicateFactOnAssert(int theFact)
{
  int hashValue; // eax
  int v3; // ebx
  int duplicateFact; // esi

  hashValue = Rules_HashFactEntry(theFact);
  v3 = hashValue;
  if ( g_Rules_FactDuplicationEnabled )
    return v3;
  duplicateFact = Rules_FindFactInHashTable(theFact, hashValue);
  if ( !duplicateFact )
    return v3;
  Rules_ReturnFact((_DWORD *)(uintptr_t)(unsigned int)theFact);
  Rules_AddLogicalDependencyLink(duplicateFact, 1);
  return -1;
}
// 51A928: using guessed type int dword_51A928;

//----- (0048AC70) --------------------------------------------------------
int Rules_GetFactDuplicationFlag()
{
  return g_Rules_FactDuplicationEnabled;
}
// 51A928: using guessed type int dword_51A928;

//----- (0048AC80) --------------------------------------------------------
int __fastcall Rules_SetFactDuplicationEnabled(int a1)
{
  int result; // eax

  result = g_Rules_FactDuplicationEnabled;
  g_Rules_FactDuplicationEnabled = a1;
  return result;
}
// 51A928: using guessed type int dword_51A928;

//----- (0048AC90) --------------------------------------------------------
int Rules_InitFactHashTable()
{
  int result; // eax

  g_ClipsFactHashTable = (int)Mem_SmallBlockAlloc(0xFD4u);
  if ( !g_ClipsFactHashTable )
    IO_RunRouterExitCallbacks();
  for ( result = 0; result != 4052; result += 4 )
    *(_DWORD *)(g_ClipsFactHashTable + result) = 0;
  return result;
}
// 54E518: using guessed type int dword_54E518;

//----- (0048ACE0) --------------------------------------------------------
int  Rules_RunPeriodicCleanup(int result, int useHeuristics)
{
  int cleanupAllDepths; // ecx
  int cleanupFnNode; // edx
  int i; // esi
  int v6; // edx
  int j; // edx
  int v8; // edx
  int v9; // ecx

  cleanupAllDepths = result;
  cleanupFnNode = g_Rules_PeriodicFunctionListHead;
  for ( i = -1; cleanupFnNode; cleanupFnNode = *(_DWORD *)(v6 + 12) )
    result = (*(int (__fastcall **)(int))(cleanupFnNode + 4))(cleanupAllDepths);
  if ( g_Rules_LastCleanupEvalDepth > g_ClipsCurrentEvaluationDepth )
  {
    result = 10240;
    g_Rules_LastCleanupEvalDepth = g_ClipsCurrentEvaluationDepth;
    g_Rules_EphemeralCountGCThreshold = 1000;
    g_Rules_EphemeralSizeThreshold = 10240;
  }
  if ( !useHeuristics || g_ClipsEphemeralItemCount >= (unsigned int)g_Rules_EphemeralCountGCThreshold || g_ClipsEphemeralItemBytes >= (unsigned int)g_Rules_EphemeralSizeThreshold )
  {
    if ( cleanupAllDepths )
    {
      i = g_ClipsCurrentEvaluationDepth;
      g_ClipsCurrentEvaluationDepth = -1;
    }
    Rules_FreeUnusedEphemeralMultifields();
    for ( j = g_CLIPS_PeriodicFunctionListHead; j; j = *(_DWORD *)(v8 + 12) )
      (*(void (**)(void))(j + 4))();
    Rules_RemoveEphemeralAtoms();
    if ( v9 )
      g_ClipsCurrentEvaluationDepth = i;
    result = g_Rules_EphemeralCountGCThreshold;
    if ( g_ClipsEphemeralItemCount + 1000 > (unsigned int)g_Rules_EphemeralCountGCThreshold )
      g_Rules_EphemeralCountGCThreshold = g_ClipsEphemeralItemCount + 1000;
    if ( g_ClipsEphemeralItemBytes + 10240 > (unsigned int)g_Rules_EphemeralSizeThreshold )
      g_Rules_EphemeralSizeThreshold = g_ClipsEphemeralItemBytes + 10240;
    g_Rules_LastCleanupEvalDepth = g_ClipsCurrentEvaluationDepth;
  }
  return result;
}
// 48ACF8: variable 'v2' is possibly undefined
// 48ACFB: variable 'v6' is possibly undefined
// 48AD86: variable 'v8' is possibly undefined
// 48AD97: variable 'v9' is possibly undefined
// 51A92C: using guessed type int dword_51A92C;
// 51A930: using guessed type int dword_51A930;
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A93C: using guessed type int dword_51A93C;
// 51A940: using guessed type int dword_51A940;
// 51A944: using guessed type int dword_51A944;
// 51A96C: using guessed type int dword_51A96C;

//----- (0048ADF0) --------------------------------------------------------
signed int  Rules_AddPeriodicFunction(int name, int theFunction, int priority)
{
  return Rules_InsertPriorityCallbackByRef(name, theFunction, &g_CLIPS_PeriodicFunctionListHead, priority);
}
// 51A92C: using guessed type int dword_51A92C;

//----- (0048AE10) --------------------------------------------------------
signed int  Rules_InsertPriorityCallbackByRef(int name, int theFunction, int *listHead, int priority)
{
  _DWORD *freeListEntry; // edx
  int lastNode; // ecx
  _DWORD *newNode; // eax
  _DWORD *v9; // edi
  int currentNode; // eax

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 64);
  lastNode = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListEntry;
    newNode = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *newNode = name;
  newNode[2] = priority;
  newNode[1] = theFunction;
  v9 = newNode;
  if ( !*listHead )
  {
    newNode[3] = 0;
    *listHead = (int)newNode;
    return 1;
  }
  currentNode = *listHead;
  do
  {
    if ( priority >= *(_DWORD *)(currentNode + 8) )
      break;
    lastNode = currentNode;
    currentNode = *(_DWORD *)(currentNode + 12);
  }
  while ( currentNode );
  if ( !lastNode )
  {
    v9[3] = *listHead;
    *listHead = (int)v9;
    return 1;
  }
  v9[3] = currentNode;
  *(_DWORD *)(lastNode + 12) = v9;
  return 1;
}
// 48AE6B: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AED0) --------------------------------------------------------
signed int __fastcall Rules_RemoveNamedCallListEntry(int name, _DWORD *listHead)
{
  _DWORD *currentNode; // ecx
  _DWORD *lastNode; // esi
  _DWORD *nodeToRemove; // ecx

  currentNode = (_DWORD *)*listHead;
  lastNode = 0;
  if ( !*listHead )
    return 0;
  while ( strcmp_(currentNode, *currentNode) )
  {
    lastNode = nodeToRemove;
    currentNode = (_DWORD *)nodeToRemove[3];
    if ( !currentNode )
      return 0;
  }
  if ( lastNode )
    lastNode[3] = nodeToRemove[3];
  else
    *listHead = nodeToRemove[3];
  g_ClipsMemFreeListTemp = (int)nodeToRemove;
  *nodeToRemove = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return 1;
}
// 48AEF1: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AF40) --------------------------------------------------------
int  Str_InternQuotedEscapedString(int *theString, unsigned int a2)
{
  char *appended; // edx
  unsigned __int8 theChar; // bl
  char *escapedBuffer; // edx
  char *updatedBuffer; // eax
  char *finalBuffer; // eax
  signed int *theSymbol; // ebx
  _DWORD *v10; // ecx
  int position; // [esp+0h] [ebp-18h] BYREF
  unsigned int bufferMax[5]; // [esp+4h] [ebp-14h] BYREF

  bufferMax[3] = a2;
  position = 0;
  bufferMax[0] = 0;
  appended = Str_AppendCharEscaping(34, 0, bufferMax, &position, 0x50u);
  while ( 1 )
  {
    theChar = *(_BYTE *)theString;
    if ( !*(_BYTE *)theString )
      break;
    if ( theChar == 34 || theChar == 92 )
    {
      escapedBuffer = Str_AppendCharEscaping(92, appended, bufferMax, &position, bufferMax[0] + 80);
      updatedBuffer = Str_AppendCharEscaping(*(unsigned __int8 *)theString, escapedBuffer, bufferMax, &position, bufferMax[0] + 80);
    }
    else
    {
      updatedBuffer = Str_AppendCharEscaping(theChar, appended, bufferMax, &position, bufferMax[0] + 80);
    }
    appended = updatedBuffer;
    theString = (int *)((char *)theString + 1);
  }
  finalBuffer = Str_AppendCharEscaping(34, appended, bufferMax, &position, bufferMax[0] + 80);
  theSymbol = Str_Intern(finalBuffer, (int)finalBuffer);
  Mem_SmallBlockFree(v10, bufferMax[0]);
  return theSymbol[4];
}
// 48AFEB: variable 'v10' is possibly undefined

//----- (0048B000) --------------------------------------------------------
int  Str_Concat(const char *string1, const char *string2, unsigned int a3)
{
  char *buffer; // eax
  char *appendedBuffer; // eax
  signed int *theSymbol; // ebx
  _DWORD *v7; // ecx
  int position; // [esp+0h] [ebp-14h] BYREF
  unsigned int bufferMax[4]; // [esp+4h] [ebp-10h] BYREF

  bufferMax[2] = a3;
  position = 0;
  bufferMax[0] = 0;
  buffer = Str_Append(string1, 0, bufferMax, &position);
  appendedBuffer = Str_Append(string2, buffer, bufferMax, &position);
  theSymbol = Str_Intern(appendedBuffer, (int)appendedBuffer);
  Mem_SmallBlockFree(v7, bufferMax[0]);
  return theSymbol[4];
}
// 48B03A: variable 'v7' is possibly undefined

//----- (0048B050) --------------------------------------------------------
char * Str_Append(const char *appendStr, char *oldStr, unsigned int *oldMax, _DWORD *oldPos)
{
  const char *sourcePtr; // esi
  char *theString; // ebp
  unsigned int lengthWithNull; // kr04_4
  signed int requiredSize; // ebx
  int v9; // ecx
  char *destPtr; // edi
  char currentChar; // al
  char nextChar; // al

  sourcePtr = appendStr;
  theString = oldStr;
  lengthWithNull = strlen(appendStr) + 1;
  requiredSize = lengthWithNull + *oldPos;
  if ( requiredSize > (int)*oldMax )
  {
    theString = (char *)Mem_Realloc(oldStr, *oldMax, requiredSize);
    *oldMax = *oldPos + lengthWithNull;
    if ( !theString )
      return 0;
  }
  else if ( !oldStr )
  {
    return 0;
  }
  destPtr = &theString[*oldPos];
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
  *oldPos += lengthWithNull - 1;
  return theString;
}
// 48B09C: variable 'v9' is possibly undefined

//----- (0048B0F0) --------------------------------------------------------
char * Str_AppendBounded(int appendStr, char *oldStr, _DWORD *oldPos, int length, unsigned int *oldMax)
{
  char *theString; // esi
  signed int requiredSize; // ebx
  int *v9; // ecx
  int newPosition; // edx
  int lengthWithNull; // [esp+0h] [ebp-10h]

  theString = oldStr;
  if ( *(_BYTE *)(length + appendStr - 1) )
    lengthWithNull = length + 1;
  else
    lengthWithNull = length;
  requiredSize = *oldPos + lengthWithNull;
  if ( requiredSize > (int)*oldMax )
  {
    theString = (char *)Mem_Realloc(oldStr, *oldMax, requiredSize);
    *oldMax = lengthWithNull + *oldPos;
  }
  if ( !theString )
    return 0;
  strncpy_(oldPos, appendStr);
  newPosition = lengthWithNull - 1 + *v9;
  *v9 = newPosition;
  theString[newPosition] = 0;
  return theString;
}
// 48B121: variable 'a3' is possibly undefined
// 48B153: variable 'v9' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (0048B170) --------------------------------------------------------
char * Str_AppendCharEscaping(
        int inchar,
        char *str,
        unsigned int *max,
        int *pos,
        unsigned int newSize)
{
  char *result; // eax
  int newPos; // edx

  result = str;
  if ( (int)(*max - 1) <= *pos )
  {
    result = (char *)Mem_Realloc(str, *max, newSize);
    *max = newSize;
    if ( !result )
      return 0;
  }
  if ( inchar == 8 )
  {
    if ( *pos > 0 )
      --*pos;
    result[*pos] = 0;
  }
  else
  {
    result[*pos] = inchar;
    newPos = *pos + 1;
    *pos = newPos;
    result[newPos] = 0;
  }
  return result;
}
// 48B1B3: variable 'v6' is possibly undefined

//----- (0048B1E0) --------------------------------------------------------
_DWORD * Rules_InsertPriorityCallbackReturningHead(int name, int priority, signed int listHead, int theFunction)
{
  _DWORD *freeListEntry; // edi
  signed int lastNode; // ecx
  _DWORD *result; // eax
  _DWORD *newNode; // edi
  signed int currentNode; // eax

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 64);
  lastNode = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListEntry;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  result[1] = theFunction;
  result[2] = priority;
  newNode = result;
  *result = name;
  if ( listHead )
  {
    currentNode = listHead;
    do
    {
      if ( priority >= *(int *)(currentNode + 8) )
        break;
      lastNode = currentNode;
      currentNode = *(_DWORD *)(currentNode + 12);
    }
    while ( currentNode );
    if ( lastNode )
    {
      newNode[3] = currentNode;
      *(_DWORD *)(lastNode + 12) = newNode;
      return (_DWORD *)listHead;
    }
    else
    {
      newNode[3] = listHead;
      return newNode;
    }
  }
  else
  {
    result[3] = 0;
  }
  return result;
}
// 48B220: conditional instruction was optimized away because ebx.4!=0
// 48B23B: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048B270) --------------------------------------------------------
int  Rules_RemoveNamedCallbackReturningHead(int name, int head, _DWORD *foundFlag)
{
  int list_head; // edi
  int current; // ecx
  int previous; // ebx

  list_head = head;
  current = head;
  *foundFlag = 0;
  previous = 0;
  if ( !current )
    return list_head;
  while ( strcmp_(name, *(_DWORD *)current) )
  {
    previous = current;
    current = *(_DWORD *)(current + 12);
    if ( !current )
      return list_head;
  }
  *foundFlag = 1;
  if ( previous )
    *(_DWORD *)(previous + 12) = *(_DWORD *)(current + 12);
  else
    list_head = *(_DWORD *)(current + 12);
  g_ClipsMemFreeListTemp = current;
  *(_DWORD *)current = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return list_head;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048B2E0) --------------------------------------------------------
int __fastcall Rules_RegisterDeftemplateFunctions(int a1, int a2)
{
  int v2; // ecx

  Rules_AddResetFunction((int)aDeftemplate_0, (int)Noop_DeftemplateResetCallback, 0);
  Rules_AddClearFunction((int)aDeftemplate_0, (int)Rules_InternInitialFactSymbol, 0);
  Rules_AddSaveFunction((int)aDeftemplate_0, (int)Rules_ClearDeftemplateModuleData, 10);
  Rules_RegisterHostFunction(aGetDeftemplate, 109, v2, (int)Rules_GetDeftemplateListCommand, (int)a01w_1);
  Rules_RegisterHostFunction(aUndeftemplate, 118, (int)aUndeftemplatec, (int)Rules_UndeftemplateCommand, (int)a11w_1);
  Rules_RegisterHostFunction(aDeftemplateMod, 119, (int)aDeftemplatemod, (int)Rules_DeftemplateModuleCommand, (int)a11w_1);
  Rules_RegisterHostFunction(aListDeftemplat, 118, (int)aListdeftemplat, (int)Rules_ListDeftemplatesCommand, (int)a01w_1);
  Rules_RegisterHostFunction(aPpdeftemplate, 118, (int)aPpdeftemplatec, (int)Rules_PPDeftemplateCommand, (int)a11w_1);
  Rules_RegisterDeftemplateBinaryItem();
  Rules_RegisterDeftemplateCodeGen();
  return Noop_DeftemplateResetCallback(a1, a2);
}
// 48B332: variable 'v2' is possibly undefined
// 48B3C0: using guessed type int __fastcall nullsub_11(_DWORD, _DWORD);

//----- (0048B3D0) --------------------------------------------------------
int __thiscall Rules_InternInitialFactSymbol(void *this)
{
  signed int *initialFactSymbol; // eax
  char v2; // dl

  initialFactSymbol = Str_Intern(aInitialFact_2, (int)this);
  return Rules_CreateDeftemplateRecord((int)initialFactSymbol, v2);
}
// 48B3DD: variable 'v2' is possibly undefined

//----- (0048B3F0) --------------------------------------------------------
int  Rules_ClearDeftemplateModuleData(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B400) --------------------------------------------------------
int __thiscall Rules_UndeftemplateCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B420) --------------------------------------------------------
int  Rules_DeleteDeftemplate(int theDeftemplate, int a2)
{
  return Rules_DeleteConstructOrAll(theDeftemplate, g_DeftemplateConstructType, a2);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B430) --------------------------------------------------------
_DWORD * Rules_GetDeftemplateListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_DeftemplateConstructType, a2);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B470) --------------------------------------------------------
int __thiscall Rules_DeftemplateModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B490) --------------------------------------------------------
int __thiscall Rules_PPDeftemplateCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B4C0) --------------------------------------------------------
int  Rules_ListDeftemplatesCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_DeftemplateConstructType, a1, a2);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B500) --------------------------------------------------------
int  Rules_GetFactWatchFlag(int theTemplate)
{
  return *(_DWORD *)(theTemplate + 24) << 30 >> 31;
}

//----- (0048B510) --------------------------------------------------------
int  Rules_SetFactWatchFlag(char newState, int theTemplate)
{
  int result; // eax

  *(_BYTE *)(theTemplate + 24) &= ~2u;
  result = 2 * (newState & 1);
  *(_DWORD *)(theTemplate + 24) |= result;
  return result;
}

//----- (0048B530) --------------------------------------------------------
signed int  Rules_ToggleFactWatchFlag(int newState, int argExprs, double a3)
{
  return Rules_ApplyWatchFlagCommand(g_DeftemplateConstructType, newState, (int)Rules_GetFactWatchFlag, argExprs, a3, (void (*)(void))Rules_SetFactWatchFlag);
}
// 48B500: using guessed type int sub_48B500();
// 54E650: using guessed type int dword_54E650;

//----- (0048B550) --------------------------------------------------------
signed int  Rules_WatchPrintFactsState(int code, int argExprs, double a3)
{
  return Rules_ListWatchFlagStatus(g_DeftemplateConstructType, code, (int)Rules_GetFactWatchFlag, argExprs, a3, (void (*)(void))Rules_SetFactWatchFlag);
}
// 48B500: using guessed type int sub_48B500();
// 54E650: using guessed type int dword_54E650;

//----- (0048B570) --------------------------------------------------------
int  Rules_AddWatchItem(int name, int flag, int priority, int code, int accessFunc, int printFunc)
{
  int watch_item; // ecx
  int previous_watch_item; // ebx
  int result; // eax
  _DWORD *freeListEntry; // edx
  _DWORD *newWatchItem; // eax

  watch_item = g_WatchItemListHead;
  previous_watch_item = 0;
  if ( watch_item )
  {
    while ( 1 )
    {
      result = strcmp_(*(_DWORD *)watch_item, name);
      if ( !result )
        break;
      if ( priority < *(_DWORD *)(watch_item + 12) )
        previous_watch_item = watch_item;
      watch_item = *(_DWORD *)(watch_item + 24);
      if ( !watch_item )
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 112);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(g_ClipsMemoryTable + 112) = *freeListEntry;
      newWatchItem = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newWatchItem = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
    }
    *newWatchItem = name;
    newWatchItem[2] = flag;
    newWatchItem[3] = priority;
    newWatchItem[1] = code;
    newWatchItem[4] = accessFunc;
    newWatchItem[5] = printFunc;
    if ( previous_watch_item )
    {
      newWatchItem[6] = *(_DWORD *)(previous_watch_item + 24);
      *(_DWORD *)(previous_watch_item + 24) = (int)newWatchItem;
      return 1;
    }
    else
    {
      newWatchItem[6] = g_WatchItemListHead;
      g_WatchItemListHead = (int)newWatchItem;
      return 1;
    }
  }
  return result;
}
// 48B598: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A94C: using guessed type int dword_51A94C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048B660) --------------------------------------------------------
signed int  Rules_SetWatchItemState(unsigned int newState, int itemName, int argExprs)
{
  int currentItem; // ecx
  _DWORD *namedItem; // ecx
  int v7; // ecx

  if ( newState >= 2 )
    return 0;
  if ( !strcmp_(itemName, aAll_1) )
  {
    currentItem = g_WatchItemListHead;
    if ( !g_WatchItemListHead )
      return 1;
    while ( 1 )
    {
      if ( !argExprs )
        **(_DWORD **)(currentItem + 4) = newState;
      if ( *(_DWORD *)(currentItem + 16) && !(*(int (__fastcall **)(int, unsigned int))(currentItem + 16))(currentItem, newState) )
        break;
      currentItem = *(_DWORD *)(currentItem + 24);
      if ( !currentItem )
        return 1;
    }
  }
  else
  {
    namedItem = (_DWORD *)g_WatchItemListHead;
    if ( !g_WatchItemListHead )
      return 0;
    while ( strcmp_(namedItem, *namedItem) )
    {
      namedItem = *(_DWORD **)(v7 + 24);
      if ( !namedItem )
        return 0;
    }
    if ( !argExprs )
      **(_DWORD **)(v7 + 4) = newState;
    if ( !*(_DWORD *)(v7 + 16) || (*(int (__fastcall **)(int, unsigned int))(v7 + 16))(v7, newState) )
      return 1;
  }
  Lexer_ErrorRecover(1);
  return 0;
}
// 48B66D: simplified comparisons for 'edx.4': ==1 || ==0 became <2u
// 48B69E: variable 'v5' is possibly undefined
// 48B6F8: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A94C: using guessed type int dword_51A94C;

//----- (0048B750) --------------------------------------------------------
signed int Rules_GetWatchItemState(int itemName)
{
  int watch_item; // ecx
  int value_pointer; // eax

  watch_item = g_WatchItemListHead;
  if ( !g_WatchItemListHead )
    return -1;
  while ( strcmp_(itemName, *(_DWORD *)watch_item) )
  {
    watch_item = *(_DWORD *)(watch_item + 24);
    if ( !watch_item )
      return -1;
  }
  value_pointer = *(_DWORD *)(watch_item + 4);
  return *(_DWORD *)(uintptr_t)(unsigned int)value_pointer;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A94C: using guessed type int dword_51A94C;

//----- (0048B790) --------------------------------------------------------
int __fastcall Rules_FindWatchItem(int itemName, _DWORD *recognized)
{
  int result; // eax
  _DWORD *currentItem; // ecx
  int v5; // ecx

  *recognized = 1;
  result = strcmp_(itemName, aAll_1);
  if ( result )
  {
    currentItem = (_DWORD *)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      while ( strcmp_(currentItem, *currentItem) )
      {
        currentItem = *(_DWORD **)(v5 + 24);
        if ( !currentItem )
          goto LABEL_5;
      }
      return v5;
    }
    else
    {
LABEL_5:
      *recognized = 0;
      return 0;
    }
  }
  return result;
}
// 48B7C2: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A94C: using guessed type int dword_51A94C;

//----- (0048B840) --------------------------------------------------------
signed int  Rules_WatchCommand(int returnValue, double a2)
{
  signed int result; // eax
  int watchItem; // eax
  int v4; // ecx
  int v5; // edx
  _DWORD argValue[6]; // [esp-8h] [ebp-28h] BYREF
  _DWORD recognized[4]; // [esp+10h] [ebp-10h] BYREF

  recognized[2] = returnValue;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
  {
    watchItem = Rules_FindWatchItem(*(_DWORD *)(argValue[2] + 16), recognized);
    if ( recognized[0] )
    {
      if ( !*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) || watchItem && *(_DWORD *)(watchItem + 16) )
      {
        return Rules_SetWatchItemState(1u, v4, *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10));
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Rules_ExpectedCountError((int)aWatch, 1);
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      return Parser_ReportError(v5, (int)aWatchableSymbo);
    }
  }
  return result;
}
// 48B8DC: variable 'v5' is possibly undefined
// 48B8FB: variable 'v4' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (0048B910) --------------------------------------------------------
signed int  Rules_UnwatchCommand(int returnValue, double a2)
{
  signed int result; // eax
  int watchItem; // eax
  int v4; // ecx
  int v5; // edx
  _DWORD argValue[6]; // [esp-8h] [ebp-28h] BYREF
  _DWORD recognized[4]; // [esp+10h] [ebp-10h] BYREF

  recognized[2] = returnValue;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
  {
    watchItem = Rules_FindWatchItem(*(_DWORD *)(argValue[2] + 16), recognized);
    if ( recognized[0] )
    {
      if ( !*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) || watchItem && *(_DWORD *)(watchItem + 16) )
      {
        return Rules_SetWatchItemState(0, v4, *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10));
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Rules_ExpectedCountError((int)aUnwatch, 1);
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      return Parser_ReportError(v5, (int)aWatchableSymbo);
    }
  }
  return result;
}
// 48B9AC: variable 'v5' is possibly undefined
// 48B9C8: variable 'v4' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (0048B9E0) --------------------------------------------------------
signed int  Rules_ListWatchItemsCommand(int returnValue, double a2)
{
  signed int result; // eax
  int *currentItem; // ecx
  int v4; // ecx
  char *stateText; // edx
  int v6; // ecx
  int v7; // ecx
  int *theItem; // eax
  int v9; // ecx
  char *itemStateText; // edx
  int v11; // ecx
  int v12; // edx
  int argValue; // [esp-8h] [ebp-28h] BYREF
  _DWORD recognized[4]; // [esp+10h] [ebp-10h] BYREF

  recognized[2] = returnValue;
  result = g_ClipsCurrentExpression;
  if ( *(_DWORD *)(g_ClipsCurrentExpression + 6) )
  {
    result = Lexer_ParseValueList(1, &argValue, 2, a2);
    if ( result )
    {
      theItem = (int *)Rules_FindWatchItem(v7, recognized);
      if ( recognized[0] && theItem )
      {
        if ( !theItem[5] && *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) )
        {
          Lexer_ErrorRecover(1);
          return Rules_ExpectedCountError((int)aListWatchItems, 1);
        }
        else
        {
          Output_Write((int)g_IO_LogicalName_WDisplay, *theItem, (int)theItem);
          if ( **(_DWORD **)(v9 + 4) )
            itemStateText = aOn;
          else
            itemStateText = aOff;
          result = Output_Write((int)g_IO_LogicalName_WDisplay, (int)itemStateText, v9);
          if ( *(_DWORD *)(v11 + 20) )
          {
            result = (*(int (__fastcall **)(int, _DWORD))(v11 + 20))(v11, *(_DWORD *)(v11 + 8));
            if ( !result )
              return Lexer_ErrorRecover(1);
          }
        }
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Parser_ReportError(v12, (int)aWatchableSymbo);
      }
    }
  }
  else
  {
    currentItem = (int *)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      do
      {
        Output_Write((int)g_IO_LogicalName_WDisplay, *currentItem, (int)currentItem);
        if ( **(_DWORD **)(v4 + 4) )
          stateText = aOn;
        else
          stateText = aOff;
        result = Output_Write((int)g_IO_LogicalName_WDisplay, (int)stateText, v4);
        currentItem = *(int **)(v6 + 24);
      }
      while ( currentItem );
    }
  }
  return result;
}
// 48BA07: variable 'v4' is possibly undefined
// 48BA1E: variable 'v6' is possibly undefined
// 48BA58: variable 'v7' is possibly undefined
// 48BA93: variable 'v9' is possibly undefined
// 48BAAE: variable 'v11' is possibly undefined
// 48BB01: variable 'v12' is possibly undefined
// 51A624: using guessed type char *off_51A624;
// 51A94C: using guessed type int dword_51A94C;
// 51A960: using guessed type int dword_51A960;

//----- (0048BB40) --------------------------------------------------------
signed int Rules_RegisterWatchFunctions()
{
  Rules_RegisterHostFunction(aWatch, 118, (int)aWatchcommand, (int)Rules_WatchCommand, (int)a1W);
  Rules_RegisterHostFunction(aUnwatch, 118, (int)aUnwatchcommand, (int)Rules_UnwatchCommand, (int)a1W);
  Rules_RegisterHostFunction(aListWatchItems, 118, (int)aListwatchitems, (int)Rules_ListWatchItemsCommand, (int)a0W);
  IO_AddRouter((int)g_IO_LogicalNameTable_WTrace[0], 1000, (int)Rules_WatchAlwaysTrueStub, (int)Rules_WatchNameMatches, 0, 0, 0);
  return IO_DeactivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
}
// 48BBF0: using guessed type int sub_48BBF0();
// 51A618: using guessed type char *off_51A618[4];

//----- (0048BBD0) --------------------------------------------------------
BOOL __thiscall Rules_WatchNameMatches(void *this)
{
  return strcmp_(this, g_IO_LogicalNameTable_WTrace[0]) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A618: using guessed type char *off_51A618[4];

//----- (0048BBF0) --------------------------------------------------------
int Rules_WatchAlwaysTrueStub()
{
  return 1;
}
// 48BBF0: using guessed type int sub_48BBF0();

//----- (0048BC00) --------------------------------------------------------
signed int Rules_RegisterFactQueryFunctions()
{
  Rules_RegisterHostFunction(aFactExistp, 98, (int)aFactexistpfunc, (int)Rules_CheckFactExistp, (int)a11z);
  Rules_RegisterHostFunction(aFactRelation, 119, (int)aFactrelationfu, (int)Rules_GetFactRelationName, (int)a11z);
  Rules_RegisterHostFunction(aFactSlotValue, 117, (int)aFactslotvaluef, (int)Lexer_ParseSlotConstraint, (int)a22Zw);
  Rules_RegisterHostFunction(aFactSlotNames, 117, (int)aFactslotnamesf, (int)Lexer_ParseFieldSpec, (int)a11z);
  return Rules_RegisterHostFunction(aGetFactList, 109, (int)aGetfactlistfun, (int)Rules_GetFactListFunction, (int)a01w_0);
}

//----- (0048BCA0) --------------------------------------------------------
int  Rules_GetFactRelationName(double a1)
{
  int v1; // ecx
  int theFact; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return g_ClipsFalseSymbol;
  theFact = Rules_ResolveFactArgument(1, v1, 0, a1);
  if ( !theFact )
    return g_ClipsFalseSymbol;
  else
    return **(_DWORD **)(theFact + 16);
}
// 48BCCC: variable 'v1' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BCF0) --------------------------------------------------------
int  Rules_CheckFactExistp(double a1)
{
  int result; // eax
  int v2; // ecx
  int theFact; // eax

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    theFact = Rules_ResolveFactArgument(1, v2, 0, a1);
    return Rules_CheckFactStillAsserted(theFact);
  }
  return result;
}
// 48BD17: variable 'v2' is possibly undefined

//----- (0048BD30) --------------------------------------------------------
BOOL  Rules_CheckFactStillAsserted(BOOL result)
{
  if ( result )
    return *(char *)(result + 29) >= 0;
  return result;
}

//----- (0048BD50) --------------------------------------------------------
int  Lexer_ParseSlotConstraint(_DWORD *returnValue, int a2, double a3)
{
  int result; // eax
  int v5; // ecx
  int theFact; // edi
  _DWORD slotNameArg[11]; // [esp-8h] [ebp-2Ch] BYREF

  slotNameArg[9] = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Lexer_TokenExpect(2);
  if ( result != -1 )
  {
    result = Rules_ResolveFactArgument(1, v5, 1, a3);
    theFact = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, slotNameArg, 2, a3);
      if ( result )
        return Lexer_BuildSlotNode(theFact, *(char **)(slotNameArg[2] + 16), returnValue);
    }
  }
  return result;
}
// 48BD94: variable 'v5' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BDD0) --------------------------------------------------------
int  Lexer_BuildSlotNode(int theFact, char *slotName, _DWORD *returnValue)
{
  char *v5; // ecx
  int v7; // ecx
  signed int *slotSymbol; // eax
  int v9; // ecx
  int slotPosition; // [esp+0h] [ebp-18h] BYREF
  int theDeftemplate; // [esp+4h] [ebp-14h]

  if ( (*(_BYTE *)(*(_DWORD *)(theFact + 16) + 24) & 1) != 0 )
  {
    if ( strcmp_(slotName, aImplied) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v7, *(_DWORD *)(**(_DWORD **)(theFact + 16) + 16));
    }
  }
  else
  {
    slotSymbol = Str_Intern(slotName, (int)slotName);
    theDeftemplate = *(_DWORD *)(theFact + 16);
    if ( !Lexer_FindTemplateSlot(theDeftemplate, (int)slotSymbol, &slotPosition) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v9, *(_DWORD *)(**(_DWORD **)(theFact + 16) + 16));
    }
  }
  if ( (*(_BYTE *)(*(_DWORD *)(theFact + 16) + 24) & 1) != 0 )
    return Lexer_EmitSlotBinding(theFact, 0, (int)v5, returnValue);
  else
    return Lexer_EmitSlotBinding(theFact, v5, (int)v5, returnValue);
}
// 48BE07: variable 'v5' is possibly undefined
// 48BE28: variable 'v7' is possibly undefined
// 48BE62: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0048BE80) --------------------------------------------------------
int  Lexer_ParseFieldSpec(int returnValue, double a2)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // ecx

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Rules_ResolveFactArgument(1, v3, 1, a2);
    if ( result )
      return Rules_BuildFactSlotNameList(result, v4);
  }
  return result;
}
// 48BEBA: variable 'v3' is possibly undefined
// 48BEC5: variable 'v4' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BED0) --------------------------------------------------------
int  Rules_BuildFactSlotNameList(int theFact, _DWORD *returnValue)
{
  int theDeftemplate; // edx
  int slotChain; // edx
  signed int i; // eax
  _DWORD *theList; // eax
  int v8; // ecx
  _DWORD *theMultifield; // ebx
  _DWORD *currentSlot; // edx
  int result; // eax
  _DWORD *fieldPtr; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  theDeftemplate = *(_DWORD *)(theFact + 16);
  if ( (*(_BYTE *)(theDeftemplate + 24) & 1) != 0 )
  {
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = 0;
    *((_WORD *)Rules_CreateEphemeralMultifield(1) + 7) = 2;
    result = (int)Str_Intern(aImplied, v13);
    *(_DWORD *)(v14 + 16) = result;
    *(_DWORD *)(v15 + 8) = v14;
  }
  else
  {
    slotChain = *(_DWORD *)(theDeftemplate + 20);
    for ( i = 0; slotChain; ++i )
      slotChain = *(_DWORD *)(slotChain + 16);
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = i - 1;
    theList = Rules_CreateEphemeralMultifield(i);
    *(_DWORD *)(v8 + 8) = theList;
    theMultifield = theList;
    currentSlot = *(_DWORD **)(*(_DWORD *)(theFact + 16) + 20);
    result = 1;
    if ( currentSlot )
    {
      fieldPtr = theMultifield;
      do
      {
        *((_WORD *)fieldPtr + 7) = 2;
        fieldPtr[4] = *currentSlot;
        fieldPtr = (_DWORD *)((char *)fieldPtr + 6);
        currentSlot = (_DWORD *)currentSlot[4];
        ++result;
      }
      while ( currentSlot );
    }
  }
  return result;
}
// 48BF19: variable 'v8' is possibly undefined
// 48BF80: variable 'v13' is possibly undefined
// 48BF85: variable 'v14' is possibly undefined
// 48BF88: variable 'v15' is possibly undefined

//----- (0048BF90) --------------------------------------------------------
_DWORD * Rules_GetFactListFunction(int returnValue, double a2)
{
  int numArgs; // eax
  int v4; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  _DWORD argValue[2]; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+4h] [ebp-1Ch]
  int v11; // [esp+18h] [ebp-8h]

  v11 = returnValue;
  numArgs = Lexer_TokenExpect(1);
  if ( numArgs == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( numArgs == 1 )
  {
    Rules_RtnUnknown(1, argValue, a2);
    if ( argValue[1] != 2 || !Module_FindByName(*(_BYTE **)(v10 + 16)) && strcmp_(v7, *(_DWORD *)(v10 + 16)) )
    {
      Rules_SetMultifieldErrorValue(v6);
      return (_DWORD *)Parser_ReportError(v8, (int)aDefmoduleNam_1);
    }
  }
  else
  {
    Module_GetCurrent();
  }
  return (_DWORD *)Rules_BuildFactAddressList();
}
// 48BFCD: variable 'v4' is possibly undefined
// 48BFFE: variable 'v7' is possibly undefined
// 48C013: variable 'v6' is possibly undefined
// 48C01D: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0048C030) --------------------------------------------------------
int Rules_BuildFactAddressList()
{
  int v0; // edx
  int theModule; // esi
  int theFact; // eax
  _DWORD *v3; // ecx
  signed int i; // edx
  int v5; // edx
  _DWORD *theList; // eax
  int v7; // ecx
  int m; // eax
  int v9; // edx
  int v10; // edx
  int j; // eax
  int v12; // edx
  int k; // eax
  int v14; // edx
  int v15; // edx

  Module_BeginEnum();
  theModule = v0;
  if ( v0 )
  {
    Module_SetCurrent(v0);
    Lexer_MarkImpliedTemplates();
    theFact = Rules_GetNextFactInModule(0);
    for ( i = 0; theFact; i = v5 + 1 )
      theFact = Rules_GetNextFactInModule(theFact);
  }
  else
  {
    for ( j = Rules_GetNextFact(0); j; i = v12 + 1 )
      j = Rules_GetNextFact(j);
  }
  v3[1] = 4;
  v3[4] = i - 1;
  v3[3] = 0;
  theList = Rules_CreateEphemeralMultifield(i);
  *(_DWORD *)(v7 + 8) = theList;
  if ( theModule )
  {
    for ( k = Rules_GetNextFactInModule(0); k; v14 = v15 + 6 )
    {
      *(_WORD *)(v14 + 14) = 6;
      *(_DWORD *)(v14 + 16) = k;
      k = Rules_GetNextFactInModule(k);
    }
  }
  else
  {
    for ( m = Rules_GetNextFact(0); m; v9 = v10 + 6 )
    {
      *(_WORD *)(v9 + 14) = 6;
      *(_DWORD *)(v9 + 16) = m;
      m = Rules_GetNextFact(m);
    }
  }
  Module_EndEnum();
  return Lexer_MarkImpliedTemplates();
}
// 48C039: variable 'v0' is possibly undefined
// 48C061: variable 'v5' is possibly undefined
// 48C073: variable 'v3' is possibly undefined
// 48C070: variable 'i' is possibly undefined
// 48C08D: variable 'v7' is possibly undefined
// 48C09F: variable 'v9' is possibly undefined
// 48C0AD: variable 'v10' is possibly undefined
// 48C0DD: variable 'v12' is possibly undefined
// 48C0EF: variable 'v14' is possibly undefined
// 48C0FD: variable 'v15' is possibly undefined

//----- (0048C120) --------------------------------------------------------
int  Rules_ResolveFactArgument(int argumentPosition, int theFunction, int noFactError, double a4)
{
  int v4; // ecx
  int result; // eax
  int factIndex; // edx
  int v7; // ecx
  int v8; // [esp-4h] [ebp-34h] BYREF
  int argType; // [esp+0h] [ebp-30h]
  int argValue; // [esp+4h] [ebp-2Ch]
  _BYTE tempBuffer[24]; // [esp+14h] [ebp-1Ch] BYREF
  int v12; // [esp+2Ch] [ebp-4h]

  v12 = theFunction;
  Rules_RtnUnknown(argumentPosition, &v8, a4);
  if ( argType == 6 )
  {
    result = argValue;
    if ( *(char *)(argValue + 29) < 0 )
      return 0;
  }
  else if ( argType == 1 && *(int *)(argValue + 16) >= 0 )
  {
    result = Rules_FindFactByIndex();
    if ( !result && noFactError )
    {
      sprintf_(tempBuffer, "f-%ld", factIndex);
      Rules_ReportCantFindItem(v7, (int)tempBuffer);
      return 0;
    }
  }
  else
  {
    Parser_ReportError(v4, (int)aFactAddressOrF);
    return 0;
  }
  return result;
}
// 48C17F: variable 'v4' is possibly undefined
// 48C197: variable 'v6' is possibly undefined
// 48C1A8: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (0048C1C0) --------------------------------------------------------
signed int Rules_RegisterFactPatternNetworkPersistence()
{
  return Rules_RegisterBinaryItem(
           (int)aFacts_3,
           0,
           0,
           (int)Rules_FactPatternNetworkBsaveFind,
           (int)Rules_FactPatternNetworkWriteHeader,
           (int)Rules_FactPatternNetworkBsaveStorage,
           (int)Rules_FactPatternNetworkBloadStorage,
           (int)Rules_FactPatternNetworkBload,
           (int)Rules_FactPatternNetworkClearBloaded);
}

//----- (0048C200) --------------------------------------------------------
int Rules_FactPatternNetworkBsaveFind()
{
  int result; // eax
  int i; // esi
  int j; // ecx
  int v3; // ecx

  if ( Rules_IsBloaded() )
    Rules_ConstructQueuePush(g_FactPatternNodeCount);
  g_FactPatternNodeCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(v3) )
      Rules_FactPatternNetworkAssignNodeIds(0, 0, *(_DWORD **)(j + 32));
    result = Module_NextEnum(i);
  }
  return result;
}
// 48C251: variable 'v3' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C270) --------------------------------------------------------
const void * Rules_FactPatternNetworkAssignNodeIds(const void *result, int theFile, _DWORD *thePattern)
{
  const void *v3; // ecx

  v3 = result;
  if ( thePattern )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        if ( v3 )
        {
          if ( v3 == (const void *)1 )
            result = Rules_FactPatternNetworkWriteNodeRecord((int)thePattern, theFile);
        }
        else
        {
          result = (const void *)g_FactPatternNodeCount++;
          thePattern[4] = result;
        }
        if ( !thePattern[7] )
          break;
        thePattern = (_DWORD *)thePattern[7];
      }
      while ( !thePattern[10] )
      {
        thePattern = (_DWORD *)thePattern[8];
        if ( !thePattern )
          return result;
      }
      thePattern = (_DWORD *)thePattern[10];
    }
  }
  return result;
}
// 48C27D: variable 'v3' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C2D0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteHeader(int theFile, int a2)
{
  int v2; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 4;
  Rules_BsaveWriteBlock(4, theFile, space);
  return Rules_BsaveWriteBlock(4, v2, &g_FactPatternNodeCount);
}
// 48C2F5: variable 'v2' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C310) --------------------------------------------------------
int  Rules_FactPatternNetworkBsaveStorage(int theFile)
{
  int i; // edi
  int j; // ecx
  int v4; // ecx
  int result; // eax
  int space[7]; // [esp+0h] [ebp-1Ch] BYREF

  space[0] = 32 * g_FactPatternNodeCount;
  Rules_BsaveWriteBlock(4, theFile, space);
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(v4) )
      Rules_FactPatternNetworkAssignNodeIds((const void *)1, theFile, *(_DWORD **)(j + 32));
  }
  result = Rules_IsBloaded();
  if ( result )
    return Rules_ConstructQueuePop(&g_FactPatternNodeCount);
  return result;
}
// 48C368: variable 'v4' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C3B0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteNodeRecord(int thePattern, int theFile)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // ecx
  int nextLevelPtr; // ebp
  int v9; // eax
  int lastLevelPtr; // eax
  int v11; // eax
  int leftNodePtr; // edx
  int v13; // eax
  int rightNodePtr; // esi
  int v15; // eax
  _BYTE tempNode[8]; // [esp+0h] [ebp-34h] BYREF
  int packedFields; // [esp+8h] [ebp-2Ch]
  signed int networkTestIndex; // [esp+Ch] [ebp-28h]
  int nextLevelIndex; // [esp+10h] [ebp-24h]
  int lastLevelIndex; // [esp+14h] [ebp-20h]
  int leftNodeIndex; // [esp+18h] [ebp-1Ch]
  int rightNodeIndex; // [esp+1Ch] [ebp-18h]

  Rules_BsavePackSharedRecordHeader((int)tempNode, thePattern);
  v4 = *(_DWORD *)(v3 + 20);
  BYTE1(packedFields) = 0;
  packedFields |= (unsigned __int8)v4 << 8;
  v5 = *(_DWORD *)(v3 + 20);
  BYTE2(packedFields) = 0;
  packedFields |= v5 & 0xFF0000;
  v6 = *(_DWORD *)(v3 + 20) << 16;
  LOBYTE(packedFields) = 0;
  packedFields |= HIBYTE(v6);
  networkTestIndex = AST_GetHashedNodeIndex(*(__int16 **)(v3 + 24));
  nextLevelPtr = v7[7];
  if ( nextLevelPtr )
    v9 = *(_DWORD *)(nextLevelPtr + 16);
  else
    v9 = -1;
  nextLevelIndex = v9;
  lastLevelPtr = v7[8];
  if ( lastLevelPtr )
    v11 = *(_DWORD *)(lastLevelPtr + 16);
  else
    v11 = -1;
  lastLevelIndex = v11;
  leftNodePtr = v7[9];
  if ( leftNodePtr )
    v13 = *(_DWORD *)(leftNodePtr + 16);
  else
    v13 = -1;
  leftNodeIndex = v13;
  rightNodePtr = v7[10];
  if ( rightNodePtr )
    v15 = *(_DWORD *)(rightNodePtr + 16);
  else
    v15 = -1;
  rightNodeIndex = v15;
  return Rules_BsaveWriteBlock(32, theFile, tempNode);
}
// 48C3C7: variable 'v3' is possibly undefined
// 48C41A: variable 'v7' is possibly undefined

//----- (0048C490) --------------------------------------------------------
int Rules_FactPatternNetworkBloadStorage()
{
  int result; // eax
  int space; // [esp+0h] [ebp-8h] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_FactPatternNodeCount, 4u);
  if ( g_FactPatternNodeCount )
  {
    space = 44 * g_FactPatternNodeCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(44 * g_FactPatternNodeCount));
    g_ClipsFactPatternNodeBloadArray = result;
  }
  else
  {
    g_ClipsFactPatternNodeBloadArray = 0;
  }
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E520: using guessed type int dword_54E520;

//----- (0048C4E0) --------------------------------------------------------
signed int Rules_FactPatternNetworkBload()
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  return Rules_BloadAndRefresh(g_FactPatternNodeCount, 32, (void (__fastcall *)(signed int, signed int))Rules_FactPatternNetworkFixupNodeRecord);
}
// 54E520: using guessed type int dword_54E520;

//----- (0048C510) --------------------------------------------------------
int  Rules_FactPatternNetworkFixupNodeRecord(int *bsaveNode, int nodeIndex)
{
  int record_offset;
  int record;
  unsigned int flags;
  int relation_index;
  int previous_index;
  int next_index;
  int parent_index;
  int child_index;
  int result;

  record_offset = 44 * nodeIndex;
  record = g_ClipsFactPatternNodeBloadArray + record_offset;
  Rules_BloadUnpackSharedRecordHeader(record, bsaveNode);
  *(_DWORD *)(record + 16) = 0;

  flags = (unsigned int)bsaveNode[2];
  *(_BYTE *)(record + 20) = 0;
  *(_DWORD *)(record + 20) |= (flags >> 8) & 0xFF;
  *(_BYTE *)(record + 22) = 0;
  *(_DWORD *)(record + 20) |= flags & 0xFF0000;
  *(_BYTE *)(record + 21) = 0;
  *(_DWORD *)(record + 20) |= (flags & 0xFF) << 8;

  relation_index = bsaveNode[3];
  *(_DWORD *)(record + 24) = relation_index == -1 ? 0 : g_ClipsPackedExpressionArray + 14 * relation_index;

  previous_index = bsaveNode[7];
  *(_DWORD *)(record + 40) = previous_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * previous_index;

  next_index = bsaveNode[4];
  *(_DWORD *)(record + 28) = next_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * next_index;

  parent_index = bsaveNode[5];
  *(_DWORD *)(record + 32) = parent_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * parent_index;

  child_index = bsaveNode[6];
  result = child_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * child_index;
  *(_DWORD *)(record + 36) = result;
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E688: using guessed type int dword_54E688;

//----- (0048C670) --------------------------------------------------------
signed int Rules_FactPatternNetworkClearBloaded()
{
  signed int result; // eax

  if ( 44 * g_FactPatternNodeCount )
    return Mem_ReleasePoolBlock(g_ClipsFactPatternNodeBloadArray, 44 * g_FactPatternNodeCount);
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E520: using guessed type int dword_54E520;

//----- (0048C690) --------------------------------------------------------
int Rules_RegisterFactPatternNetworkCodeGen()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aFacts_4, 0, 0, (int)Rules_FactPatternNetworkAssignCodeGenIds, (int)Rules_FactPatternNetworkToCode, 1);
  g_ClipsFactPatternNetworkCodeGenItem = result;
  return result;
}
// 54E524: using guessed type int dword_54E524;

//----- (0048C6C0) --------------------------------------------------------
int Rules_FactPatternNetworkAssignCodeGenIds()
{
  int result; // eax
  int deftemplateIndex; // esi
  int i; // edi
  int nodeIndex; // ecx
  int j; // ebx
  _DWORD *thePattern; // eax
  int v6; // ecx

  result = Module_NextEnum(0);
  deftemplateIndex = 0;
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(j) )
    {
      thePattern = *(_DWORD **)(j + 32);
      for ( *(_DWORD *)(j + 12) = deftemplateIndex++; thePattern; nodeIndex = v6 + 1 )
      {
        thePattern[4] = nodeIndex;
        thePattern = Rules_FactPatternNetworkNextNode(thePattern);
      }
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 48C6F7: variable 'v3' is possibly undefined
// 48C6FF: variable 'v6' is possibly undefined

//----- (0048C730) --------------------------------------------------------
_DWORD * Rules_FactPatternNetworkNextNode(_DWORD *result)
{
  if ( result[7] )
    return (_DWORD *)result[7];
  while ( !result[10] )
  {
    result = (_DWORD *)result[8];
    if ( !result )
      return result;
  }
  return (_DWORD *)result[10];
}

//----- (0048C760) --------------------------------------------------------
int  Rules_FactPatternNetworkToCode(const char *fileName, const char *fileID, int imageID, int headerFP, int maxIndices)
{
  int fileVersion; // esi
  int v6; // ecx
  _DWORD *thePattern; // edi
  int v8; // eax
  int v9; // ecx
  int theFile; // esi
  int v12; // [esp+0h] [ebp-30h] BYREF
  int itemCount; // [esp+4h] [ebp-2Ch] BYREF
  int v14; // [esp+8h] [ebp-28h] BYREF
  int Enum; // [esp+Ch] [ebp-24h]
  int theDeftemplate; // [esp+10h] [ebp-20h]
  const char *v17; // [esp+14h] [ebp-1Ch]
  const char *v18; // [esp+18h] [ebp-18h]
  int v19; // [esp+1Ch] [ebp-14h]
  int v20; // [esp+20h] [ebp-10h]

  v18 = fileName;
  v17 = fileID;
  v19 = headerFP;
  v20 = imageID;
  itemCount = 0;
  v14 = 1;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeFactbld, 1);
  fileVersion = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      theDeftemplate = Rules_GetNextDeftemplate(0);
      if ( theDeftemplate )
        break;
LABEL_7:
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_8;
    }
    while ( 1 )
    {
      thePattern = *(_DWORD **)(theDeftemplate + 32);
      if ( thePattern )
        break;
LABEL_6:
      theDeftemplate = Rules_GetNextDeftemplate(theDeftemplate);
      if ( !theDeftemplate )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v8 = Rules_ConstructCodeFileOpen(
             fileVersion,
             v18,
             v20,
             v17,
             &v12,
             v14,
             v19,
             (char)aStructFactpatt,
             **(const char ***)(g_ClipsFactPatternNetworkCodeGenItem + 20),
             0,
             0);
      theFile = v8;
      if ( !v8 )
        break;
      Rules_FactPatternNetworkNodeToCode(v8, (int)thePattern, maxIndices, v20);
      ++itemCount;
      fileVersion = Rules_ConstructCodeFileClose(theFile, &itemCount, maxIndices, &v14, 0, 0);
      thePattern = Rules_FactPatternNetworkNextNode(thePattern);
      if ( !thePattern )
        goto LABEL_6;
    }
    Rules_FactPatternNetworkToCodeClose(0, maxIndices, v9);
    return 0;
  }
  else
  {
LABEL_8:
    Rules_FactPatternNetworkToCodeClose(fileVersion, maxIndices, v6);
    return 1;
  }
}
// 48C885: variable 'v6' is possibly undefined
// 48C89A: variable 'v9' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048C8B0) --------------------------------------------------------
int  Rules_FactPatternNetworkToCodeClose(int result, int maxIndices, int imageID)
{
  int v3; // [esp+0h] [ebp-Ch] BYREF
  _DWORD v4[2]; // [esp+4h] [ebp-8h] BYREF

  v4[1] = imageID;
  v3 = maxIndices;
  v4[0] = 0;
  if ( result )
    return Rules_ConstructCodeFileClose(result, &v3, maxIndices, v4, 0, 0);
  return result;
}

//----- (0048C8E0) --------------------------------------------------------
int  Rules_FactPatternNetworkNodeToCode(int theFile, int thePattern, int maxIndices, char imageID)
{
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v20; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, thePattern, theFile, (int)asc_504530, imageID);
  Rules_PrintPatternNetworkNodeTrace(theFile, v7, v8);
  Output_WriteFormatted(maxIndices, v9, theFile, (int)a0DDD, *(_DWORD *)(thePattern + 20));
  Rules_WriteExpressionRefToCode(theFile, *(__int16 **)(thePattern + 24), v10, v20);
  v12 = *(_DWORD *)(thePattern + 28);
  if ( v12 )
    Output_WriteFormatted(v20, *(_DWORD *)(v12 + 16) % maxIndices, theFile, (int)aSD_LdLd_1, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v11, 0, theFile, (int)aNull_14, v20);
  if ( *(_DWORD *)(thePattern + 32) )
    Output_WriteFormatted(**(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), v20, theFile, (int)aSD_LdLd_2, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v14, v13, theFile, (int)aNull_12, v20);
  if ( *(_DWORD *)(thePattern + 36) )
    Output_WriteFormatted(v16, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), theFile, (int)aSD_LdLd_2, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v16, v15, theFile, (int)aNull_12, v20);
  v18 = *(_DWORD *)(thePattern + 40);
  if ( v18 )
    return Output_WriteFormatted(v18, *(_DWORD *)(v18 + 16) % maxIndices, theFile, (int)aSD_LdLd_3, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(0, v17, theFile, (int)aNull_13, v20);
}
// 48C8FF: variable 'v7' is possibly undefined
// 48C8FF: variable 'v8' is possibly undefined
// 48C929: variable 'v9' is possibly undefined
// 48C939: variable 'v10' is possibly undefined
// 48C939: variable 'v20' is possibly undefined
// 48C98D: variable 'v14' is possibly undefined
// 48C98D: variable 'v13' is possibly undefined
// 48C9A6: variable 'v16' is possibly undefined
// 48C9A6: variable 'v15' is possibly undefined
// 48C9BF: variable 'v17' is possibly undefined
// 48C9D4: variable 'v11' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048CAA0) --------------------------------------------------------
int  Rules_FactPatternNetworkWriteNodeRefToCode(int thePattern, int theFile, int imageID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( thePattern )
    return Output_WriteFormatted(imageID, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), theFile, (int)aSD_LdLd_4, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(imageID, theFile, theFile, (int)aNull_16, v4);
}
// 48CAB0: variable 'v4' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048CAF0) --------------------------------------------------------
_DWORD * Rules_CreateMultifield(signed int size)
{
  signed int originalSize; // ecx
  signed int adjustedSize; // edx
  int bucketAddress; // eax
  _DWORD *result; // eax
  __int16 evaluationDepth; // dx

  originalSize = size;
  adjustedSize = size;
  if ( size <= 0 )
    adjustedSize = 1;
  if ( (unsigned int)(6 * (adjustedSize - 1) + 20) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (adjustedSize - 1) + 80) )
  {
    bucketAddress = g_ClipsMemoryTable + 24 * (adjustedSize - 1);
    g_ClipsMemFreeListTemp = *(_DWORD *)(bucketAddress + 80);
    *(_DWORD *)(bucketAddress + 80) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (adjustedSize - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = originalSize;
  evaluationDepth = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = evaluationDepth;
  return result;
}
// 48CB51: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048CB90) --------------------------------------------------------
_DWORD * Rules_ReturnMultifieldToPool(_DWORD *result)
{
  int fieldCount; // edx
  unsigned int byteSize; // edx

  if ( result )
  {
    fieldCount = *(_DWORD *)((char *)result + 6);
    if ( !fieldCount )
      fieldCount = 1;
    byteSize = 6 * (fieldCount - 1) + 20;
    g_ClipsMemPoolReturnBucketIndex = byteSize;
    if ( byteSize >= 0x1F4 )
    {
      return (_DWORD *)Mem_SmallBlockRelease(result, byteSize);
    }
    else
    {
      g_ClipsMemFreeListTemp = (int)result;
      *result = *(_DWORD *)(g_ClipsMemoryTable + 4 * byteSize);
      result = (_DWORD *)g_ClipsMemFreeListTemp;
      *(_DWORD *)(4 * g_ClipsMemPoolReturnBucketIndex + g_ClipsMemoryTable) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0048CC00) --------------------------------------------------------
__int16 * Rules_InstallMultifield(__int16 *result)
{
  unsigned char *multifield;
  unsigned char *field;
  int count;
  int index;

  if ( result )
  {
    multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)result;
    count = *(_DWORD *)(multifield + 6);
    ++*(_DWORD *)multifield;
    if ( count > 0 )
    {
      field = multifield + 14;
      for ( index = 0; index < count; ++index )
      {
        Rules_AtomInstall(*(__int16 *)field, *(_DWORD *)(field + 2), (int)(uintptr_t)field);
        field += 6;
      }
    }
  }
  return result;
}

//----- (0048CC40) --------------------------------------------------------
__int16 * Rules_DeinstallMultifield(__int16 *result)
{
  unsigned char *multifield;
  unsigned char *field;
  int count;
  int index;

  if ( result )
  {
    multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)result;
    count = *(_DWORD *)(multifield + 6);
    --*(_DWORD *)multifield;
    if ( count > 0 )
    {
      field = multifield + 14;
      for ( index = 0; index < count; ++index )
      {
        Rules_AtomDeinstall(*(__int16 *)field, (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(field + 2), (int)(uintptr_t)field);
        field += 6;
      }
    }
  }
  return result;
}

//----- (0048CC80) --------------------------------------------------------
_DWORD * Rules_CreateMultifieldFromString(const char *theString)
{
  int topNode; // esi
  int v2; // ecx
  signed int lastNode; // edi
  signed int *theValue; // edx
  __int16 valueType; // ax
  signed int newNode; // eax
  _DWORD *theMultifield; // ebx
  char *fieldPtr; // edx
  int fieldIndex; // ecx
  int i; // eax
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int node_count;

  token_buffer_ptr = Compat_AllocLow32Bytes(12);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  IO_OpenStringSource((int)aMultifieldStr, theString, 0);
  topNode = 0;
  Parser_NextToken((int)aMultifieldStr, token_buffer_ptr);
  lastNode = 0;
  node_count = 0;
  while ( token_buffer[0] != 102 )
  {
    if ( token_buffer[0] == 2 || token_buffer[0] == 3 || token_buffer[0] < 2u || token_buffer[0] == 8 )
    {
      theValue = (signed int *)(uintptr_t)(unsigned int)token_buffer[1];
      valueType = token_buffer[0];
    }
    else
    {
      theValue = Str_Intern((char *)(uintptr_t)(unsigned int)token_buffer[2], v2);
      valueType = 3;
    }
    newNode = AST_NewNode(valueType, (int)theValue);
    ++node_count;
    if ( topNode )
      *(_DWORD *)(lastNode + 10) = newNode;
    else
      topNode = newNode;
    lastNode = newNode;
    Parser_NextToken((int)aMultifieldStr, token_buffer_ptr);
  }
  IO_CloseStringRouter((int)aMultifieldStr);
  theMultifield = Rules_CreateEphemeralMultifield(node_count);
  fieldPtr = (char *)theMultifield + 14;
  fieldIndex = 0;
  for ( i = topNode; i; ++fieldIndex )
  {
    *(_WORD *)fieldPtr = *(_WORD *)i;
    *(_DWORD *)(fieldPtr + 2) = *(_DWORD *)(i + 2);
    fieldPtr += 6;
    i = *(_DWORD *)(i + 10);
  }
  AST_Free(topNode);
  Compat_FreeLow32Bytes(token_buffer_ptr);
  return theMultifield;
}
// 48CD3A: simplified comparisons for '%var_24.4': ==0 || ==1 became <2u
// 48CD52: variable 'v2' is possibly undefined

//----- (0048CD70) --------------------------------------------------------
_DWORD * Rules_CreateEphemeralMultifield(signed int size)
{
  signed int originalSize; // ecx
  signed int adjustedSize; // edx
  int bucketAddress; // eax
  _DWORD *result; // eax
  __int16 evaluationDepth; // bx

  originalSize = size;
  if ( size <= 0 )
    adjustedSize = 1;
  else
    adjustedSize = size;
  if ( (unsigned int)(6 * (adjustedSize - 1) + 20) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (adjustedSize - 1) + 80) )
  {
    bucketAddress = 24 * (adjustedSize - 1) + g_ClipsMemoryTable;
    g_ClipsMemFreeListTemp = *(_DWORD *)(bucketAddress + 80);
    *(_DWORD *)(bucketAddress + 80) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (adjustedSize - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = originalSize;
  evaluationDepth = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = evaluationDepth;
  *(_DWORD *)((char *)result + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = (int)result;
  ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += 6 * adjustedSize + 20;
  return result;
}
// 48CDE6: variable 'v1' is possibly undefined
// 48CE21: variable 'v2' is possibly undefined
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048CE70) --------------------------------------------------------
_DWORD * Rules_MaterializeMultifieldRange(_DWORD *theValue)
{
  _DWORD *theCopy; // ebx
  int v3; // edx

  if ( theValue[1] != 4 )
    return 0;
  theCopy = Rules_CreateMultifield(theValue[4] - theValue[3] + 1);
  qmemcpy(
    (char *)theCopy + 14,
    (const void *)(6 * *(_DWORD *)(v3 + 12) + *(_DWORD *)(v3 + 8) + 14),
    6 * *(_DWORD *)((char *)theCopy + 6));
  return theCopy;
}
// 48CE95: variable 'v3' is possibly undefined

//----- (0048CED0) --------------------------------------------------------
int  Rules_RegisterEphemeralMultifield(int theSegment)
{
  int result; // eax

  *(_WORD *)(theSegment + 4) = g_ClipsCurrentEvaluationDepth;
  *(_DWORD *)(theSegment + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = theSegment;
  ++g_ClipsEphemeralItemCount;
  result = 6 * *(_DWORD *)(theSegment + 6) + 20;
  g_ClipsEphemeralItemBytes += result;
  return result;
}
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;

//----- (0048CF20) --------------------------------------------------------
int Rules_FreeUnusedEphemeralMultifields()
{
  int result; // eax
  int lastSegment; // ebx
  int nextSegment; // ecx
  int fieldCount; // edx
  unsigned int byteSize; // edx

  result = g_ClipsEphemeralMultifieldListHead;
  lastSegment = 0;
  if ( g_ClipsEphemeralMultifieldListHead )
  {
    do
    {
      while ( 1 )
      {
        nextSegment = *(_DWORD *)(result + 10);
        if ( *(__int16 *)(result + 4) <= g_ClipsCurrentEvaluationDepth || *(_DWORD *)result )
          break;
        --g_ClipsEphemeralItemCount;
        g_ClipsEphemeralItemBytes -= 6 * *(_DWORD *)(result + 6) + 20;
        if ( *(_DWORD *)(result + 6) )
          fieldCount = *(_DWORD *)(result + 6);
        else
          fieldCount = 1;
        byteSize = 6 * (fieldCount - 1) + 20;
        g_ClipsMemPoolReturnBucketIndex = byteSize;
        if ( byteSize >= 0x1F4 )
        {
          Mem_SmallBlockRelease((_DWORD *)result, byteSize);
        }
        else
        {
          g_ClipsMemFreeListTemp = result;
          *(_DWORD *)result = *(_DWORD *)(g_ClipsMemoryTable + 4 * byteSize);
          *(_DWORD *)(4 * g_ClipsMemPoolReturnBucketIndex + g_ClipsMemoryTable) = g_ClipsMemFreeListTemp;
        }
        if ( lastSegment )
        {
          *(_DWORD *)(lastSegment + 10) = nextSegment;
          result = nextSegment;
          if ( !nextSegment )
            return result;
        }
        else
        {
          g_ClipsEphemeralMultifieldListHead = nextSegment;
          result = nextSegment;
          if ( !nextSegment )
            return result;
        }
      }
      lastSegment = result;
      result = *(_DWORD *)(result + 10);
    }
    while ( nextSegment );
  }
  return result;
}
// 48CFBE: variable 'v2' is possibly undefined
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0048D010) --------------------------------------------------------
int  Rules_AssignMultifieldRangeCopy(_DWORD *dst, int src)
{
  int rangeSize; // eax
  _DWORD *theCopy; // eax
  int v5; // ecx
  int fieldCount; // ebx
  int v7; // edx
  int result; // eax

  dst[1] = 4;
  dst[3] = 0;
  rangeSize = *(_DWORD *)(src + 16) - *(_DWORD *)(src + 12);
  dst[4] = rangeSize;
  theCopy = Rules_CreateMultifield(rangeSize + 1);
  fieldCount = *(_DWORD *)(v5 + 16) + 1;
  *(_DWORD *)(v5 + 8) = theCopy;
  result = 6 * fieldCount;
  qmemcpy(
    (void *)(*(_DWORD *)(v5 + 8) + 14),
    (const void *)(6 * *(_DWORD *)(v7 + 12) + *(_DWORD *)(v7 + 8) + 14),
    6 * fieldCount);
  return result;
}
// 48D035: variable 'v5' is possibly undefined
// 48D048: variable 'v7' is possibly undefined

//----- (0048D080) --------------------------------------------------------
_DWORD * Rules_CloneMultifield(int theMultifield)
{
  _DWORD *theCopy; // ebx
  int v2; // edx

  theCopy = Rules_CreateMultifield(*(_DWORD *)(theMultifield + 6));
  qmemcpy((char *)theCopy + 14, (const void *)(v2 + 14), 6 * *(_DWORD *)(v2 + 6));
  return theCopy;
}
// 48D09B: variable 'v2' is possibly undefined

//----- (0048D0C0) --------------------------------------------------------
int  Rules_PrintMultifieldRange(int result, int theSegment, int end, int begin, int printParens)
{
  int logicalName; // esi
  int fieldsBase; // edi
  int fieldIndex; // ecx
  __int16 *fieldPtr; // edi
  int v10; // ecx

  logicalName = result;
  fieldsBase = theSegment + 14;
  if ( printParens )
    result = Output_Write(result, (int)asc_5045B8, end);
  fieldIndex = begin;
  if ( begin <= end )
  {
    fieldPtr = (__int16 *)(6 * begin + fieldsBase);
    do
    {
      result = Rules_PrintAtomValue(logicalName, *fieldPtr, *(int **)(fieldPtr + 1));
      fieldIndex = v10 + 1;
      fieldPtr += 3;
      if ( fieldIndex <= end )
        result = Output_Write(logicalName, (int)asc_5045BC, fieldIndex);
    }
    while ( fieldIndex <= end );
  }
  if ( printParens )
    return Output_Write(logicalName, (int)asc_5045C0, fieldIndex);
  return result;
}
// 48D0F1: variable 'v10' is possibly undefined
// 48D107: variable 'v8' is possibly undefined

//----- (0048D140) --------------------------------------------------------
_DWORD * Rules_StoreEvaluatedNodesAsMultifield(_DWORD *returnValue, int expressionList, int garbageSegment, double a4)
{
  EvalResultBuffer *out;
  EvalResultBuffer parsed;
  EvalMultifieldEntry *entries;
  EvalMultifieldEntry *entry;
  _DWORD *entries_raw;
  _DWORD *multifield_raw;
  unsigned char *multifield;
  unsigned char *source_multifield;
  int node_count;
  int node;
  int output_count;
  int entry_index;
  int source_index;
  int destination_index;
  int source_offset;
  int destination_offset;
  int allocation_size;

  out = (EvalResultBuffer *)returnValue;
  node_count = AST_CountListNodes(expressionList);
  if ( !node_count )
  {
    out->type = 4;
    out->begin = 0;
    out->end = -1;
    multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
    out->value = (int)(uintptr_t)multifield_raw;
    return multifield_raw;
  }

  allocation_size = sizeof(*entries) * node_count;
  entries_raw = Mem_NewArray(allocation_size);
  entries = (EvalMultifieldEntry *)(uintptr_t)(unsigned int)(uintptr_t)entries_raw;
  output_count = 0;
  node = expressionList;
  for ( entry_index = 0; entry_index < node_count; ++entry_index )
  {
    memset(&parsed, 0, sizeof(parsed));
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)node, (_DWORD *)&parsed, node, a4);
    if ( g_ClipsEvaluationError )
    {
      out->type = 4;
      out->begin = 0;
      out->end = -1;
      multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
      out->value = (int)(uintptr_t)multifield_raw;
      Mem_SmallBlockRelease(entries_raw, allocation_size);
      return multifield_raw;
    }

    entry = &entries[entry_index];
    entry->type = parsed.type;
    entry->value = parsed.value;
    if ( parsed.type == 4 )
    {
      entry->begin = parsed.begin;
      entry->end = parsed.end;
      output_count += parsed.end - parsed.begin + 1;
    }
    else if ( parsed.type == 105 )
    {
      entry->begin = 0;
      entry->end = -1;
    }
    else
    {
      entry->begin = -2;
      entry->end = -2;
      ++output_count;
    }
    node = *(_DWORD *)((uintptr_t)(unsigned int)node + 10);
  }

  multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(output_count) : Rules_CreateMultifield(output_count);
  multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)multifield_raw;
  destination_index = 0;
  for ( entry_index = 0; entry_index < node_count; ++entry_index )
  {
    entry = &entries[entry_index];
    if ( entry->type == 4 )
    {
      source_multifield = (unsigned char *)(uintptr_t)(unsigned int)entry->value;
      for ( source_index = entry->begin; source_index <= entry->end; ++source_index )
      {
        source_offset = 14 + 6 * source_index;
        destination_offset = 14 + 6 * destination_index;
        *(_WORD *)(multifield + destination_offset) = *(_WORD *)(source_multifield + source_offset);
        *(_DWORD *)(multifield + destination_offset + 2) = *(_DWORD *)(source_multifield + source_offset + 2);
        ++destination_index;
      }
    }
    else
    {
      destination_offset = 14 + 6 * destination_index;
      *(_WORD *)(multifield + destination_offset) = (__int16)entry->type;
      *(_DWORD *)(multifield + destination_offset + 2) = entry->value;
      ++destination_index;
    }
  }

  out->type = 4;
  out->begin = 0;
  out->end = output_count - 1;
  out->value = (int)(uintptr_t)multifield_raw;
  Mem_SmallBlockRelease(entries_raw, allocation_size);
  return multifield_raw;
}
// 48D39A: conditional instruction was optimized away because esi.4!=4
// 48D1C0: variable 'v11' is possibly undefined
// 48D1CD: variable 'v10' is possibly undefined
// 48D26F: variable 'v13' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (0048D3C0) --------------------------------------------------------
signed int  Rules_MultifieldRangesEqual(_DWORD *dobj1, _DWORD *dobj2)
{
  int extent; // eax
  __int16 *fieldPtr1; // ecx
  __int16 *fieldPtr2; // edx

  extent = dobj1[4] - dobj1[3] + 1;
  if ( extent == dobj2[4] - dobj2[3] + 1 )
  {
    fieldPtr1 = (__int16 *)(dobj1[2] + 14 + 6 * dobj1[3]);
    fieldPtr2 = (__int16 *)(6 * dobj2[3] + dobj2[2] + 14);
    if ( !extent )
      return 1;
    while ( *fieldPtr1 == *fieldPtr2 && *(_DWORD *)(fieldPtr1 + 1) == *(_DWORD *)(fieldPtr2 + 1) )
    {
      if ( --extent > 0 )
      {
        fieldPtr1 += 3;
        fieldPtr2 += 3;
      }
      if ( !extent )
        return 1;
    }
  }
  return 0;
}

//----- (0048D440) --------------------------------------------------------
int  Rules_MultifieldsEqual(int segment1, int segment2)
{
  int length1; // edi
  int length2; // ecx
  int fieldIndex; // esi
  __int16 *fields1; // eax
  __int16 *fieldPtr2; // ebx
  __int16 *i; // ecx
  int result; // eax

  length1 = *(_DWORD *)(segment1 + 6);
  length2 = *(_DWORD *)(segment2 + 6);
  fieldIndex = 0;
  if ( length1 == length2 )
  {
    fields1 = (__int16 *)(segment1 + 14);
    fieldPtr2 = (__int16 *)(segment2 + 14);
    if ( length2 <= 0 )
      return 1;
    for ( i = fields1; *i == *fieldPtr2; i += 3 )
    {
      if ( *i == 4 )
      {
        result = Rules_MultifieldsEqual(*(_DWORD *)(i + 1), *(_DWORD *)(fieldPtr2 + 1));
        if ( !result )
          return result;
      }
      else if ( *(_DWORD *)(i + 1) != *(_DWORD *)(fieldPtr2 + 1) )
      {
        return 0;
      }
      fieldPtr2 += 3;
      if ( ++fieldIndex >= length1 )
        return 1;
    }
  }
  return 0;
}
// 48D478: variable 'i' is possibly undefined

//----- (0048D4B0) --------------------------------------------------------
signed int __fastcall Rules_ReportInvalidSlotError(int a1, int deftemplateName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aTmpltdef, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInvalidSlot, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNotDefinedInCo, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], deftemplateName, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__10, v7);
}
// 48D4D2: variable 'v3' is possibly undefined
// 48D4DE: variable 'v4' is possibly undefined
// 48D4ED: variable 'v5' is possibly undefined
// 48D4F9: variable 'v6' is possibly undefined
// 48D508: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D520) --------------------------------------------------------
signed int Rules_ReportSingleFieldSlotCardError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aTmpltdef, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheSingleField, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCanOnlyContain, v2);
}
// 48D543: variable 'v0' is possibly undefined
// 48D54F: variable 'v1' is possibly undefined
// 48D55E: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D570) --------------------------------------------------------
int __fastcall Rules_ReportMultifieldAssertIntoSingleSlotError(int a1, int theDeftemplate)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *slotName; // edx
  char *v7; // eax
  int v8; // ecx
  int v9; // ecx
  char *v10; // eax
  char *deftemplateName; // edx
  int v12; // ecx

  Rules_PrintErrorID((int)aTmpltfun, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttemptedToAss, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIntoTheSingleF, v4);
  if ( v5 )
  {
    v7 = g_IO_LogicalNameTable_WError[0];
    slotName = *(char **)(*(_DWORD *)v5 + 16);
  }
  else
  {
    slotName = aUnknown_2;
    v7 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)v7, (int)slotName, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfDeftemplate, v8);
  if ( theDeftemplate )
  {
    v10 = g_IO_LogicalNameTable_WError[0];
    deftemplateName = *(char **)(*(_DWORD *)theDeftemplate + 16);
  }
  else
  {
    deftemplateName = aUnknown_2;
    v10 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)v10, (int)deftemplateName, v9);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__10, v12);
  return Lexer_ErrorRecover(1);
}
// 48D595: variable 'v3' is possibly undefined
// 48D5A4: variable 'v4' is possibly undefined
// 48D5AB: variable 'v5' is possibly undefined
// 48D5C6: variable 'v8' is possibly undefined
// 48D5D9: variable 'v9' is possibly undefined
// 48D5E8: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D620) --------------------------------------------------------
int  Rules_CheckFactAgainstSlotConstraints(int theFact)
{
  int result; // eax
  int theDeftemplate; // ecx
  int slotPtr; // ecx
  int fieldIndex; // ebx
  __int16 *fieldPtr; // edx
  int v7; // ecx
  int violationCode; // esi
  int v9; // ecx
  int v10; // ecx
  int *v11; // ecx
  int dataObject; // [esp+0h] [ebp-44h] BYREF
  int valueType; // [esp+4h] [ebp-40h]
  int value; // [esp+8h] [ebp-3Ch]
  int rangeBegin; // [esp+Ch] [ebp-38h]
  int rangeEnd; // [esp+10h] [ebp-34h]
  _BYTE factIdBuffer[44]; // [esp+18h] [ebp-2Ch] BYREF

  result = Rules_DynamicConstraintCheckingEnabled();
  if ( result )
  {
    theDeftemplate = *(_DWORD *)(theFact + 16);
    if ( theDeftemplate )
    {
      if ( (*(_BYTE *)(theDeftemplate + 24) & 1) == 0 )
      {
        slotPtr = *(_DWORD *)(theDeftemplate + 20);
        fieldIndex = 0;
        if ( slotPtr )
        {
          while ( 1 )
          {
            fieldPtr = (__int16 *)(theFact + 54 + 6 * fieldIndex);
            if ( (*(_BYTE *)(slotPtr + 4) & 1) != 0 )
            {
              valueType = 4;
              value = *(_DWORD *)(fieldPtr + 1);
              rangeBegin = 0;
              ++fieldIndex;
              rangeEnd = *(_DWORD *)(*(_DWORD *)(fieldPtr + 1) + 6) - 1;
            }
            else
            {
              valueType = *fieldPtr;
              ++fieldIndex;
              value = *(_DWORD *)(fieldPtr + 1);
            }
            result = Rules_CheckFieldAgainstConstraint(&dataObject, *(_DWORD *)(slotPtr + 8));
            violationCode = result;
            if ( result )
              break;
            slotPtr = *(_DWORD *)(v7 + 16);
            if ( !slotPtr )
              return result;
          }
          sprintf_(factIdBuffer, "fact f-%-5ld ", *(_DWORD *)(theFact + 24));
          Rules_PrintErrorID((int)aCstrnchk_0, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlotValue, v9);
          Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)&dataObject);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_5046F0, v10);
          Rules_PrintConstraintViolationMessage(0, (int)factIdBuffer, 0, 0, *v11, 0, violationCode, v11[2], 1);
          return Rules_SetEvaluationErrorFlag(1);
        }
      }
    }
  }
  return result;
}
// 48D68A: variable 'v7' is possibly undefined
// 48D6DD: variable 'v9' is possibly undefined
// 48D6F8: variable 'v10' is possibly undefined
// 48D70E: variable 'v11' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D730) --------------------------------------------------------
signed int  Rules_CheckLiteralSlotValueConstraint(int *exprList, int thePlace)
{
  int v3; // edx
  signed int violationCode; // eax
  int *v6; // ecx
  int v7; // edx
  char *errorMessage; // eax

  if ( !Rules_StaticConstraintCheckingEnabled() )
    return 1;
  violationCode = Rules_CheckFieldExprListAgainstConstraint(exprList, *(_DWORD *)(v3 + 8));
  v7 = violationCode;
  if ( !violationCode )
    return 1;
  if ( violationCode == 5 )
    errorMessage = aLiteralSlotVal;
  else
    errorMessage = aALiteralSlotVa;
  Rules_PrintConstraintViolationMessage((int)errorMessage, thePlace, 0, 1, *v6, 0, v7, v6[2], 1);
  return 0;
}
// 48D74D: variable 'v3' is possibly undefined
// 48D76E: variable 'v6' is possibly undefined

//----- (0048D790) --------------------------------------------------------
int  Lexer_GetSlotByOrdinal(int theDeftemplate, int position)
{
  int result; // eax
  int slotIndex; // edx

  result = *(_DWORD *)(theDeftemplate + 20);
  slotIndex = 0;
  if ( !result )
    return 0;
  while ( slotIndex != position )
  {
    result = *(_DWORD *)(result + 16);
    ++slotIndex;
    if ( !result )
      return 0;
  }
  return result;
}

//----- (0048D7B0) --------------------------------------------------------
signed int  Lexer_FindSymbolIndex(int theDeftemplate, int slotName)
{
  _DWORD *slotPtr; // eax
  int position; // edx

  slotPtr = *(_DWORD **)(theDeftemplate + 20);
  position = 1;
  if ( !slotPtr )
    return 0;
  while ( slotName != *slotPtr )
  {
    slotPtr = (_DWORD *)slotPtr[4];
    ++position;
    if ( !slotPtr )
      return 0;
  }
  return position;
}

//----- (0048D7E0) --------------------------------------------------------
signed int  Rules_PrintTemplateFactSlots(int logicalName, int theFact, int a3)
{
  __int16 *fieldPtr; // ebp
  _DWORD *theDeftemplate; // edi
  int v6; // ecx
  int v7; // ecx
  int slotPtr; // edi
  int v9; // ecx
  int v10; // ecx
  int theSegment; // ebx

  fieldPtr = (__int16 *)(theFact + 54);
  theDeftemplate = *(_DWORD **)(theFact + 16);
  Output_Write(logicalName, (int)asc_504720, a3);
  Output_Write(logicalName, *(_DWORD *)(*theDeftemplate + 16), v6);
  if ( theDeftemplate[5] )
    Output_Write(logicalName, (int)asc_5046F0, v7);
  slotPtr = theDeftemplate[5];
  if ( slotPtr )
  {
    while ( 1 )
    {
      Output_Write(logicalName, (int)asc_504720, v7);
      Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)slotPtr + 16), v9);
      if ( (*(_BYTE *)(slotPtr + 4) & 1) != 0 )
      {
        theSegment = *(_DWORD *)(fieldPtr + 1);
        if ( *(int *)(theSegment + 6) > 0 )
        {
          Output_Write(logicalName, (int)asc_5046F0, v10);
          Lexer_OutputFieldRange(logicalName, *(_DWORD *)(fieldPtr + 1), *(_DWORD *)(theSegment + 6) - 1, 0, 0);
        }
      }
      else
      {
        Output_Write(logicalName, (int)asc_5046F0, v10);
        Rules_PrintAtomValue(logicalName, *fieldPtr, *(int **)(fieldPtr + 1));
      }
      Output_Write(logicalName, (int)asc_504724, v10);
      slotPtr = *(_DWORD *)(slotPtr + 16);
      fieldPtr += 3;
      if ( !slotPtr )
        break;
      Output_Write(logicalName, (int)asc_5046F0, v7);
    }
  }
  return Output_Write(logicalName, (int)asc_504724, v7);
}
// 48D7FE: variable 'v6' is possibly undefined
// 48D88B: variable 'v7' is possibly undefined
// 48D827: variable 'v9' is possibly undefined
// 48D839: variable 'v10' is possibly undefined

//----- (0048D8C0) --------------------------------------------------------
int Lexer_MarkImpliedTemplates()
{
  int result; // eax
  int i; // edi
  _BYTE *j; // esi
  _DWORD v3[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    for ( j = *(_BYTE **)(Module_GetItem(i, g_ClipsDeftemplateModuleItemId) + 4); j; j = (_BYTE *)Rules_GetNextDeftemplate((int)j) )
    {
      if ( Rules_FindImportExportConstruct(aDeftemplate_6, v3, *(_BYTE **)(*(_DWORD *)j + 16), 1, 0) )
        j[24] |= 4u;
      else
        j[24] &= ~4u;
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 54E654: using guessed type int dword_54E654;

//----- (0048D940) --------------------------------------------------------
_DWORD * Lexer_FindSlotWithIndex(int theDeftemplate, int slotName, _DWORD *whichOne)
{
  _DWORD *result; // eax

  *whichOne = 1;
  result = *(_DWORD **)(theDeftemplate + 20);
  if ( result )
  {
    while ( slotName != *result )
    {
      ++*whichOne;
      result = (_DWORD *)result[4];
      if ( !result )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    *whichOne = -1;
    return 0;
  }
  return result;
}

//----- (0048D970) --------------------------------------------------------
int  Rules_CreateDeftemplateRecord(int deftemplateName, char implied)
{
  int free_template_record; // ecx
  int template_record; // edx
  int module_data; // eax

  free_template_record = *(_DWORD *)(g_ClipsMemoryTable + 144);
  if ( free_template_record )
  {
    g_ClipsMemFreeListTemp = free_template_record;
    *(_DWORD *)(g_ClipsMemoryTable + 144) = *(_DWORD *)free_template_record;
    template_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    template_record = Mem_HeapAllocWithRetry((_DWORD *)0x24);
  }
  *(_DWORD *)(template_record + 4) = 0;
  *(_DWORD *)template_record = deftemplateName;
  *(_BYTE *)(template_record + 24) &= 0xFEu;
  *(_DWORD *)(template_record + 20) = 0;
  *(_DWORD *)(template_record + 24) |= implied & 1;
  *(_DWORD *)(template_record + 32) = 0;
  *(_BYTE *)(template_record + 24) |= 4u;
  *(_DWORD *)(template_record + 28) = 0;
  *(_DWORD *)(template_record + 16) = 0;
  *(_WORD *)(template_record + 24) &= 5u;
  if ( Rules_GetWatchItemState((int)aFacts_0) )
    Rules_SetFactWatchFlag(1, template_record);
  module_data = Module_GetItem(0, g_ClipsDeftemplateModuleItemId);
  *(_DWORD *)(template_record + 8) = module_data;
  Rules_AppendConstructToModuleList(template_record);
  Rules_DeftemplateInstallSlots((_DWORD *)template_record, template_record);
  return template_record;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E654: using guessed type int dword_54E654;

//----- (0048DA40) --------------------------------------------------------
int  Rules_MatchFactAgainstPatternNetwork(
        int result,
        int patternPtr,
        _DWORD *markers,
        int offset,
        double a5,
        int endMark)
{
  int currentPattern; // esi
  int fieldIndex; // ebx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int theFact; // [esp+0h] [ebp-1Ch]
  int whichSlot; // [esp+Ch] [ebp-10h]

  theFact = result;
  currentPattern = patternPtr;
  if ( patternPtr )
  {
    whichSlot = *(_DWORD *)(patternPtr + 20) << 16 >> 24;
    g_ClipsFactMatchMarkerList = (int)markers;
    g_CurrentPatternFact = result;
    do
    {
      fieldIndex = (unsigned __int8)*(_DWORD *)(currentPattern + 20);
      if ( *(_DWORD *)(currentPattern + 20) << 16 >> 24 == whichSlot )
        fieldIndex += offset;
      result = Rules_ShouldProcessPatternNode(currentPattern);
      if ( !result )
      {
        BYTE1(result) = *(_BYTE *)(currentPattern + 12);
        if ( (result & 0x100) != 0 )
        {
          if ( (*(_BYTE *)(currentPattern + 12) & 0x40) == 0
            || !g_ClipsFactMatchMarkerList
            || (v12 = *(_DWORD *)(currentPattern + 20) << 16 >> 24, *(__int16 *)(g_ClipsFactMatchMarkerList + 4) != v12)
            || (v13 = 6 * v12 + g_CurrentPatternFact, *(_WORD *)(v13 + 54) != 4)
            || (v9 = *(_DWORD *)(*(_DWORD *)(v13 + 56) + 6), fieldIndex + (*(_DWORD *)(currentPattern + 20) << 8 >> 24) == v9) )
          {
            if ( Rules_EvaluatePatternNetworkTest(currentPattern, *(_DWORD *)(currentPattern + 24), 0, a5) )
            {
              if ( (*(_BYTE *)(currentPattern + 12) & 4) != 0 )
                Rules_AttachFactPatternMatch(theFact, markers, (signed int *)currentPattern, a5);
              v11 = currentPattern;
              v10 = 0;
              goto LABEL_7;
            }
          }
        }
        else
        {
          if ( (result & 0x200) == 0 )
            continue;
          if ( *(_DWORD *)(currentPattern + 20) << 16 >> 24 == whichSlot )
            Rules_MatchMultifieldWildcardInPattern(currentPattern, (int)markers, offset, endMark, a5);
          else
            Rules_MatchMultifieldWildcardInPattern(currentPattern, (int)markers, 0, endMark, a5);
        }
      }
      v10 = 1;
      v11 = currentPattern;
LABEL_7:
      result = Rules_AdvancePatternNetworkNode(v10, v11);
      currentPattern = result;
    }
    while ( currentPattern );
  }
  return result;
}
// 48DAE1: conditional instruction was optimized away because %var_18.4==0
// 48DB2F: variable 'v9' is possibly undefined
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DBA0) --------------------------------------------------------
int  Rules_MatchMultifieldWildcardInPattern(int theNode, int markers, int offset, int endMark, double a5)
{
  int theSegment; // edi
  _DWORD *freeMark; // edx
  signed int newMark; // eax
  int v9; // eax
  int v10; // edi
  int result; // eax
  int repeatCount; // edi
  int newOffset; // ebp
  int theTest; // edx
  _DWORD *theMark; // [esp+Ch] [ebp-10h]

  theSegment = *(_DWORD *)(g_CurrentPatternFact + 6 * (*(_DWORD *)(theNode + 20) << 16 >> 24) + 56);
  freeMark = *(_DWORD **)(g_ClipsMemoryTable + 80);
  if ( freeMark )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeMark;
    newMark = g_ClipsMemFreeListTemp;
  }
  else
  {
    newMark = Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  *(_DWORD *)newMark = (unsigned __int8)*(_DWORD *)(theNode + 20) - 1;
  *(_WORD *)(newMark + 4) = HIBYTE(*(_WORD *)(theNode + 20));
  theMark = (_DWORD *)newMark;
  *(_DWORD *)(newMark + 8) = (unsigned __int8)*(_DWORD *)(theNode + 20) - 1 + offset;
  *(_DWORD *)(newMark + 16) = 0;
  if ( endMark )
    *(_DWORD *)(endMark + 16) = newMark;
  else
    g_ClipsFactMatchMarkerList = newMark;
  if ( (*(_BYTE *)(theNode + 12) & 0x40) != 0 )
  {
    v9 = *(_DWORD *)(theSegment + 6) - ((*(_DWORD *)(theNode + 20) << 8 >> 24) + 1);
    v10 = theMark[2];
    theMark[3] = v9;
    if ( v9 < v10 )
      theMark[3] = v10 - 1;
    if ( !*(_DWORD *)(theNode + 24) || Rules_EvaluatePatternNetworkTest(theNode, *(_DWORD *)(theNode + 24), endMark, a5) )
    {
      if ( (*(_BYTE *)(theNode + 12) & 4) != 0 )
        Rules_AttachFactPatternMatch(g_CurrentPatternFact, (_DWORD *)g_ClipsFactMatchMarkerList, (signed int *)theNode, a5);
      Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(theNode + 28), g_ClipsFactMatchMarkerList, 0, a5, (int)theMark);
    }
    g_ClipsMemFreeListTemp = (int)theMark;
    *theMark = *(_DWORD *)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    if ( endMark )
      *(_DWORD *)(endMark + 16) = 0;
LABEL_14:
    result = markers;
    g_ClipsFactMatchMarkerList = markers;
    return result;
  }
  repeatCount = *(_DWORD *)(theSegment + 6) - (*(_DWORD *)(newMark + 8) + (*(_DWORD *)(theNode + 20) << 8 >> 24));
  if ( repeatCount >= 0 )
  {
    newOffset = offset + repeatCount - 1;
    do
    {
      theMark[3] = repeatCount - 1 + theMark[2];
      theTest = *(_DWORD *)(theNode + 24);
      if ( !theTest || Rules_EvaluatePatternNetworkTest(theNode, theTest, offset, a5) )
        Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(theNode + 28), g_ClipsFactMatchMarkerList, newOffset, a5, (int)theMark);
      --repeatCount;
      --newOffset;
    }
    while ( repeatCount >= 0 );
  }
  g_ClipsMemFreeListTemp = (int)theMark;
  *theMark = *(_DWORD *)(g_ClipsMemoryTable + 80);
  *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
  if ( !endMark )
    goto LABEL_14;
  *(_DWORD *)(endMark + 16) = 0;
  result = markers;
  g_ClipsFactMatchMarkerList = markers;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DDF0) --------------------------------------------------------
int  Rules_AdvancePatternNetworkNode(int finishedMatching, int thePattern)
{
  g_ClipsEvaluationError = 0;
  if ( finishedMatching || !*(_DWORD *)(thePattern + 28) )
  {
    while ( !*(_DWORD *)(thePattern + 40) )
    {
      thePattern = *(_DWORD *)(thePattern + 32);
      if ( !thePattern )
        return thePattern;
      if ( (*(_BYTE *)(thePattern + 12) & 2) != 0 )
        return 0;
    }
    return *(_DWORD *)(thePattern + 40);
  }
  else
  {
    return *(_DWORD *)(thePattern + 28);
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (0048DE30) --------------------------------------------------------
int * Rules_AttachFactPatternMatch(int theFact, _DWORD *markers, signed int *thePattern, double a4)
{
  int *partial_match; // esi
  int link; // eax
  int old_fact_links; // ebx
  int join; // ecx
  int *result; // eax

  partial_match = (int *)(uintptr_t)(unsigned int)Rules_AppendExpressionValueNode(theFact, markers, thePattern);
  old_fact_links = *(_DWORD *)(theFact + 20);
  link = *(_DWORD *)(g_ClipsMemoryTable + 48);
  if ( link )
  {
    g_ClipsMemFreeListTemp = link;
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *(_DWORD *)link;
    link = g_ClipsMemFreeListTemp;
  }
  else
  {
    link = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *(_DWORD *)(theFact + 20) = link;
  *(_DWORD *)link = old_fact_links;
  *(_DWORD *)(link + 8) = (int)thePattern;
  *(_DWORD *)(link + 4) = (int)partial_match;
  result = (int *)(uintptr_t)(unsigned int)link;
  join = thePattern[2];
  while ( join )
  {
    result = Rules_DriveJoinNetwork(partial_match, (char *)(uintptr_t)(unsigned int)join, 1, a4);
    join = *(_DWORD *)(join + 32);
  }
  return result;
}
// 48DE46: variable 'v5' is possibly undefined
// 48DE85: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048DEA0) --------------------------------------------------------
int  Rules_EvaluatePatternNetworkTest(signed int patternPtr, int theTest, int a3, double a4)
{
  __int16 exprType; // ax
  int operatorValue; // eax
  int orChild; // ecx
  int result; // eax
  int v9; // ecx
  int savedExprNested; // esi
  int savedExprSimple; // esi
  int savedExprRange; // esi
  int andChild; // ecx
  int v14; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-24h] BYREF
  int v17; // [esp+1Ch] [ebp-4h]

  v17 = a3;
  if ( !theTest )
    return 1;
  exprType = *(_WORD *)theTest;
  if ( *(_WORD *)theTest >= 0x20u )
  {
    if ( *(_WORD *)theTest <= 0x20u )
    {
      savedExprSimple = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = theTest;
      result = Rules_TestPatternFieldSimple(*(_DWORD *)(theTest + 2));
      g_ClipsCurrentExpression = savedExprSimple;
      return result;
    }
    if ( exprType == 33 )
    {
      savedExprNested = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = theTest;
      result = Rules_TestPatternNestedField(*(_DWORD *)(theTest + 2));
      g_ClipsCurrentExpression = savedExprNested;
      return result;
    }
  }
  else if ( exprType == 25 )
  {
    savedExprRange = g_ClipsCurrentExpression;
    g_ClipsCurrentExpression = theTest;
    result = Rules_EvalMultifieldIndexInRange(*(_DWORD *)(theTest + 2), (uintptr_t)parsed);
    g_ClipsCurrentExpression = savedExprRange;
    return result;
  }
  operatorValue = *(_DWORD *)(theTest + 2);
  if ( operatorValue == g_ClipsSymbolOr )
  {
    orChild = *(_DWORD *)(theTest + 6);
    if ( orChild )
    {
      while ( 1 )
      {
        result = Rules_EvaluatePatternNetworkTest(patternPtr, orChild, orChild, a4);
        if ( result == 1 )
          break;
        if ( g_ClipsEvaluationError )
          return 0;
        orChild = *(_DWORD *)(orChild + 10);
        if ( !orChild )
          return 0;
      }
      if ( !g_ClipsEvaluationError )
        return result;
    }
    return 0;
  }
  if ( operatorValue != g_Clips_SymbolAnd )
  {
    if ( Parser_ParseForm((__int16 *)theTest, parsed, theTest, a4) )
    {
      Rules_ReportPatternNetworkError(patternPtr);
      return 0;
    }
    if ( parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2 )
      return g_ClipsFalseSymbol ^ parsed[2];
    return 1;
  }
  andChild = *(_DWORD *)(theTest + 6);
  if ( !andChild )
    return 1;
  while ( 1 )
  {
    result = Rules_EvaluatePatternNetworkTest(patternPtr, andChild, andChild, a4);
    if ( !result )
      break;
    if ( g_ClipsEvaluationError )
      return 0;
    andChild = *(_DWORD *)(andChild + 10);
    if ( !andChild )
      return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (0048E020) --------------------------------------------------------
signed int  Rules_ReportPatternNetworkError(signed int patternPtr)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int theDeftemplate; // edx
  _DWORD *slotPtr; // edx
  int i; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // [esp-4h] [ebp-4Ch]
  _BYTE messageBuffer[72]; // [esp+0h] [ebp-48h] BYREF

  Rules_PrintErrorID((int)aFactmch, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_0, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCurrentlyActiv, v4);
  Rules_PrintFact((int)g_IO_LogicalNameTable_WError[0], g_CurrentPatternFact);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504794, v5);
  theDeftemplate = *(_DWORD *)(g_CurrentPatternFact + 16);
  if ( (*(_BYTE *)(theDeftemplate + 24) & 1) != 0 )
  {
    sprintf_(messageBuffer, "   Problem resides in field #%d\n", (unsigned __int8)*(_DWORD *)(patternPtr + 20));
  }
  else
  {
    v14 = v6;
    slotPtr = *(_DWORD **)(theDeftemplate + 20);
    for ( i = 0; i < *(_DWORD *)(patternPtr + 20) << 16 >> 24; ++i )
      slotPtr = (_DWORD *)slotPtr[4];
    sprintf_(messageBuffer, "   Problem resides in slot %s\n", *(const char **)(*slotPtr + 16));
    v10 = v14;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)messageBuffer, v10);
  Rules_ReportPatternNetworkRules(patternPtr, 0, v11);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504794, v12);
}
// 48E043: variable 'v3' is possibly undefined
// 48E052: variable 'v4' is possibly undefined
// 48E071: variable 'v5' is possibly undefined
// 48E085: variable 'v6' is possibly undefined
// 48E0C0: variable 'v10' is possibly undefined
// 48E0C9: variable 'v11' is possibly undefined
// 48E0D8: variable 'v12' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];
// 54E528: using guessed type int dword_54E528;

//----- (0048E100) --------------------------------------------------------
signed int  Rules_ReportPatternNetworkRules(signed int result, int processSiblings, int j)
{
  signed int i; // ebx
  int patternCount; // eax
  int v6; // ecx
  int v7; // ecx
  _BYTE messageBuffer[68]; // [esp+0h] [ebp-4Ch] BYREF
  int v9; // [esp+44h] [ebp-8h]

  v9 = j;
  for ( i = result; i; i = *(_DWORD *)(i + 40) )
  {
    if ( (*(_BYTE *)(i + 12) & 4) != 0 )
    {
      for ( j = *(_DWORD *)(i + 8); j; j = *(_DWORD *)(v7 + 32) )
      {
        patternCount = Rules_CountJoinNetworkEntryNodes(j);
        sprintf_(messageBuffer, "      Of pattern #%d in rule(s):\n", patternCount);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)messageBuffer, v6);
        result = Rules_PrintJoinNetworkSharingReport();
      }
    }
    else
    {
      result = Rules_ReportPatternNetworkRules(*(_DWORD *)(i + 28), 1, j);
    }
    if ( !processSiblings )
      break;
  }
  return result;
}
// 48E142: variable 'v6' is possibly undefined
// 48E150: variable 'v7' is possibly undefined
// 48E172: variable 'j' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048E180) --------------------------------------------------------
BOOL  Rules_ShouldProcessPatternNode(int thePattern)
{
  return g_IncrementalResetInProgress && (*(_BYTE *)(thePattern + 12) & 8) == 0;
}
// 51B354: using guessed type int dword_51B354;

//----- (0048E1A0) --------------------------------------------------------
void  Rules_PropagatePatternNodeResetFlag(int thePattern, char value)
{
  int flagBits; // edx

  if ( (*(_BYTE *)(thePattern + 12) & 8) != 0 )
  {
    flagBits = 8 * (value & 1);
    while ( thePattern )
    {
      *(_BYTE *)(thePattern + 12) &= ~8u;
      *(_DWORD *)(thePattern + 12) |= flagBits;
      thePattern = *(_DWORD *)(thePattern + 32);
    }
  }
  return;
}

//----- (0048E1D0) --------------------------------------------------------
int  Rules_RematchAllFactsAgainstPatternNetwork(double a1)
{
  int result; // eax
  int i; // esi

  result = Rules_GetNextFact(0);
  for ( i = result; result; i = result )
  {
    Rules_MatchFactAgainstPatternNetwork(i, *(_DWORD *)(*(_DWORD *)(i + 16) + 32), 0, 0, a1, 0);
    result = Rules_GetNextFact(i);
  }
  return result;
}

//----- (0048E220) --------------------------------------------------------
int * Rules_DriveJoinNetwork(int *result, char *join, int operation, double a4)
{
  int resetInProgress; // ecx
  int *lhsBinds; // ebp
  int *oppositeBinds; // esi
  char joinFlags; // dl
  char v9; // bh
  int *compareBinds; // ecx
  int i; // edx
  int *binds; // [esp+0h] [ebp-20h]
  signed int exprResult; // [esp+4h] [ebp-1Ch]
  int *rhsBinds; // [esp+8h] [ebp-18h]

  binds = result;
  resetInProgress = g_IncrementalResetInProgress;
  lhsBinds = 0;
  oppositeBinds = 0;
  rhsBinds = 0;
  if ( g_IncrementalResetInProgress && (*join & 0x10) == 0 )
    return result;
  if ( !operation )
  {
    joinFlags = *join;
    if ( (*join & 8) != 0 || (joinFlags & 4) != 0 )
    {
      result = (int *)Rules_MultifieldAppendValue(result, 0, *(_DWORD *)join << 30 >> 31, *((_DWORD *)join + 9) != 0);
      *(_BYTE *)result |= 0x30u;
      result[1] = *((_DWORD *)join + 2);
      binds = result;
      *((_DWORD *)join + 2) = result;
    }
  }
  v9 = *join;
  if ( (*join & 1) != 0 )
    return Rules_AddJoinLeftMemoryEntry((int)join, binds, resetInProgress, a4);
  if ( operation )
  {
    if ( operation == 1 )
    {
      if ( (v9 & 8) != 0 || (v9 & 4) != 0 )
        oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
      else
        oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(join + 24) + 8);
      result = binds;
      rhsBinds = binds;
    }
    else
    {
      Rules_ReportSystemError(operation, 1);
      result = (int *)IO_RunRouterExitCallbacks();
    }
  }
  else
  {
    if ( (v9 & 4) != 0 )
      oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(join + 16) + 8);
    else
      oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 16);
    lhsBinds = binds;
  }
  while ( oppositeBinds )
  {
    if ( operation == 1 )
    {
      lhsBinds = oppositeBinds;
      if ( (*(_BYTE *)oppositeBinds & 0x20) == 0 || (*join & 8) != 0 || (*join & 4) != 0 )
      {
        if ( ((*join & 8) != 0 || (*join & 4) != 0) && (*(_BYTE *)oppositeBinds & 0x20) != 0 )
          goto LABEL_31;
        goto LABEL_33;
      }
      oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
    }
    else
    {
      rhsBinds = oppositeBinds;
LABEL_33:
      if ( *((_DWORD *)join + 3) )
      {
        result = (int *)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 12), lhsBinds, (_BYTE *)join, (int)rhsBinds, a4);
        exprResult = (signed int)result;
        if ( g_ClipsEvaluationError )
        {
          if ( (*join & 8) != 0 )
            exprResult = 1;
          result = (int *)Lexer_ErrorRecover(0);
        }
      }
      else
      {
        exprResult = 1;
        if ( (*join & 4) != 0 )
        {
          compareBinds = rhsBinds;
          result = lhsBinds;
          for ( i = 0; i < (int)(((unsigned int)(*lhsBinds << 17) >> 23) - 1); ++i )
          {
            if ( result[2] != compareBinds[2] )
              goto LABEL_31;
            ++compareBinds;
            ++result;
          }
        }
      }
      if ( exprResult )
      {
        if ( (*join & 8) != 0 || (*join & 4) != 0 )
        {
          if ( operation == 1 )
          {
            result = (int *)Rules_ProcessJoinMemoryMatches((int)join, oppositeBinds, (int)rhsBinds, a4);
            oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
          }
          else
          {
            if ( operation )
              goto LABEL_31;
            result = &binds[(unsigned int)(*binds << 17) >> 23];
            oppositeBinds = 0;
            result[1] = (int)rhsBinds;
          }
        }
        else
        {
          result = Rules_CreateJoinPartialMatch(lhsBinds, rhsBinds, join, a4);
          oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
        }
      }
      else
      {
LABEL_31:
        oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
      }
    }
  }
  BYTE1(result) = *join;
  if ( ((*join & 8) != 0 || (BYTE1(result) & 4) != 0) && !operation )
  {
    result = &binds[(unsigned int)(*binds << 17) >> 23];
    if ( !result[1] )
      return Rules_AddJoinRightMemoryEntry((int)join, binds, a4);
  }
  return result;
}
// 48E2F0: variable 'v5' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51B354: using guessed type int dword_51B354;

//----- (0048E4A0) --------------------------------------------------------
signed int  Rules_EvaluateJoinExpression(
        __int16 *joinExpr,
        _WORD *lbinds,
        _BYTE *theJoin,
        int rbinds,
        double a5)
{
  __int16 *exprPtr; // esi
  int testResult; // edi
  int v8; // eax
  char joinFlags; // dl
  int exprFunction; // eax
  int entityRecord; // edi
  int v12; // eax
  __int16 v13; // ax
  __int16 v15; // ax
  uintptr_t evaluator; // eax
  int oldExpression; // ecx
  __int16 v18; // ax
  __int16 v19; // ax
  __int16 v20; // ax
  __int16 v21; // ax
  int v22; // edx
  int v23; // ecx
  __int16 v24; // ax
  __int16 v25; // ax
  __int16 v26; // ax
  _DWORD theResult[6]; // [esp+0h] [ebp-3Ch] BYREF
  int oldJoin; // [esp+18h] [ebp-24h]
  int oldRHSBinds; // [esp+1Ch] [ebp-20h]
  int oldLHSBinds; // [esp+20h] [ebp-1Ch]
  int rhsBindsCopy; // [esp+24h] [ebp-18h]
  int andLogic; // [esp+28h] [ebp-14h]
  _BYTE *joinNode; // [esp+2Ch] [ebp-10h]

  exprPtr = joinExpr;
  rhsBindsCopy = rbinds;
  joinNode = theJoin;
  testResult = 1;
  if ( !joinExpr )
    return 1;
  oldLHSBinds = g_Clips_CurrentPartialMatch;
  g_Clips_CurrentPartialMatch = (int)lbinds;
  oldRHSBinds = g_Rules_GlobalRHSBinds;
  g_Rules_GlobalRHSBinds = rbinds;
  v8 = g_CurrentPatternEntityPtr;
  g_CurrentPatternEntityPtr = (int)theJoin;
  joinFlags = *theJoin;
  oldJoin = v8;
  if ( (joinFlags & 8) != 0 )
  {
    v15 = ((unsigned __int16)(2 * *lbinds) >> 7) - 1;
    *lbinds &= 0x803Fu;
    *(_DWORD *)lbinds |= (v15 & 0x1FF) << 6;
  }
  exprFunction = *(_DWORD *)(exprPtr + 1);
  if ( exprFunction == g_Clips_SymbolAnd )
  {
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 6);
    andLogic = 1;
  }
  else if ( exprFunction == g_ClipsSymbolOr )
  {
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 6);
    andLogic = 0;
  }
  else
  {
    andLogic = 1;
  }
  while ( exprPtr )
  {
    entityRecord = g_Clips_PrimitiveEntityTable[*exprPtr];
    evaluator = entityRecord ? (uintptr_t)(unsigned int)*(_DWORD *)(entityRecord + 16) : 0;
    if ( evaluator )
    {
      oldExpression = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = (int)(uintptr_t)exprPtr;
      testResult = ((int (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)((char *)exprPtr + 2), theResult, a5);
      g_ClipsCurrentExpression = oldExpression;
    }
    else
    {
      v12 = *(_DWORD *)(exprPtr + 1);
      if ( v12 == g_ClipsSymbolOr )
      {
        testResult = 0;
        if ( Rules_EvaluateJoinExpression(exprPtr, lbinds, joinNode, rhsBindsCopy, a5) == 1 )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v19 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v19 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
          testResult = 1;
        }
        else if ( g_ClipsEvaluationError )
        {
          if ( (*joinNode & 8) != 0 )
          {
            v20 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
            *lbinds &= 0x803Fu;
            *(_DWORD *)lbinds |= (v20 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
      }
      else if ( v12 == g_Clips_SymbolAnd )
      {
        testResult = 1;
        if ( Rules_EvaluateJoinExpression(exprPtr, lbinds, joinNode, rhsBindsCopy, a5) )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v21 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v21 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
        }
        else
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v13 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v13 & 0x1FF) << 6;
            }
LABEL_14:
            g_Clips_CurrentPartialMatch = oldLHSBinds;
            g_Rules_GlobalRHSBinds = oldRHSBinds;
            g_CurrentPatternEntityPtr = oldJoin;
            return 0;
          }
          testResult = 0;
        }
      }
      else
      {
        Parser_ParseForm(exprPtr, theResult, g_ClipsSymbolOr, a5);
        testResult = g_ClipsEvaluationError;
        if ( g_ClipsEvaluationError )
        {
          Rules_ReportJoinNetworkError((int)(uintptr_t)joinNode, 0);
          if ( (*joinNode & 8) != 0 )
          {
            v24 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
            *lbinds &= 0x803Fu;
            *(_DWORD *)lbinds |= (v24 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
        if ( theResult[2] != g_ClipsFalseSymbol || theResult[1] != 2 )
          testResult = 1;
      }
    }
    if ( andLogic == 1 && !testResult )
    {
      if ( (*joinNode & 8) != 0 )
      {
        v18 = andLogic + ((unsigned __int16)(2 * *lbinds) >> 7);
        *lbinds &= 0x803Fu;
        *(_DWORD *)lbinds |= (v18 & 0x1FF) << 6;
      }
      goto LABEL_14;
    }
    if ( !andLogic && testResult == 1 )
    {
      if ( (*joinNode & 8) != 0 )
      {
        v25 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
        *lbinds &= 0x803Fu;
        *(_DWORD *)lbinds |= (v25 & 0x1FF) << 6;
      }
      g_Clips_CurrentPartialMatch = oldLHSBinds;
      g_Rules_GlobalRHSBinds = oldRHSBinds;
      g_CurrentPatternEntityPtr = oldJoin;
      return 1;
    }
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 10);
  }
  g_Clips_CurrentPartialMatch = oldLHSBinds;
  g_Rules_GlobalRHSBinds = oldRHSBinds;
  g_CurrentPatternEntityPtr = oldJoin;
  if ( (*joinNode & 8) != 0 )
  {
    v26 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
    *lbinds &= 0x803Fu;
    *(_DWORD *)lbinds |= (v26 & 0x1FF) << 6;
  }
  return testResult;
}
// 48E659: variable 'v17' is possibly undefined
// 48E7BE: variable 'v23' is possibly undefined
// 48E7BE: variable 'v22' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;
// 54DD70: using guessed type int dword_54DD70;
// 54E530: using guessed type int dword_54E530[70];
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (0048E8E0) --------------------------------------------------------
_DWORD * Rules_CreateJoinPartialMatch(_DWORD *lhsBinds, _DWORD *rhsBinds, _DWORD *theJoin, double unused_fp)
{
  _DWORD *result; // eax
  int partial_match; // esi
  int action; // ebp
  uintptr_t join; // ecx

  result = Rules_MergeMultifieldValues(lhsBinds, rhsBinds, *theJoin << 30 >> 31, theJoin[9] != 0);
  result[1] = theJoin[2];
  partial_match = (int)(uintptr_t)result;
  action = theJoin[9];
  theJoin[2] = result;
  if ( action )
    result = Rules_AddActivation(action, (int)(uintptr_t)result, unused_fp);
  join = (uintptr_t)(unsigned int)theJoin[5];
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) == (uintptr_t)(unsigned int)(uintptr_t)theJoin )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 1, unused_fp);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 0, unused_fp);
        join = (uintptr_t)(unsigned int)*(_DWORD *)(join + 28);
      }
      while ( join );
    }
  }
  return result;
}
// 48E923: conditional instruction was optimized away because ecx.4!=0

//----- (0048E960) --------------------------------------------------------
int  Rules_ProcessJoinMemoryMatches(int result, _BYTE *theBind, int newAlphaMatch, double a4)
{
  _DWORD *theJoin; // ebp
  _BYTE *v6; // edx
  int childJoin; // esi

  theJoin = (_DWORD *)result;
  BYTE1(result) = *theBind;
  if ( (*theBind & 0x20) == 0 )
  {
    *theBind = BYTE1(result) | 0x20;
    if ( (result & 0x400) != 0 )
    {
      v6 = &theBind[4 * (*(_DWORD *)theBind << 17 >> 23)];
      if ( *((_DWORD *)v6 + 2) )
        Rules_RemoveActivation(*((_DWORD **)v6 + 2), 1, 1);
    }
    childJoin = theJoin[5];
    if ( childJoin )
    {
      if ( theJoin == *(_DWORD **)(childJoin + 16) )
      {
        Rules_UpdateBetaMemoryOnRetract((_DWORD *)theJoin[5], (int)theBind, 0, a4);
      }
      else
      {
        while ( childJoin )
        {
          Rules_PropagateRetractToJoinNode(childJoin, *(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4], (*theJoin << 16 >> 25) - 1, (int)theBind, a4, 0);
          childJoin = *(_DWORD *)(childJoin + 28);
        }
      }
    }
    if ( (*theBind & 8) != 0 )
      Rules_RemovePMDependencies((int)theBind);
    *(_DWORD *)(*(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4] + 8) = g_ReteGarbageAlphaMatchList;
    g_ReteGarbageAlphaMatchList = *(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4];
    result = *(_DWORD *)theBind << 17 >> 23;
    *(_DWORD *)&theBind[4 * result + 4] = newAlphaMatch;
  }
  return result;
}
// 51A978: using guessed type int dword_51A978;

//----- (0048EA40) --------------------------------------------------------
_DWORD * Rules_AddJoinRightMemoryEntry(int theJoin, _BYTE *binds, double a3)
{
  _DWORD *result; // eax
  uintptr_t runtime_state; // eax
  unsigned int free_node; // edx
  uintptr_t join; // ecx

  runtime_state = (uintptr_t)(unsigned int)g_ClipsMemoryTable;
  free_node = *(_DWORD *)(runtime_state + 48);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = free_node;
    result = (_DWORD *)(uintptr_t)free_node;
    *(_DWORD *)(runtime_state + 48) = *result;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  result[2] = 0;
  *result = 0;
  result[1] = 0;
  *binds &= ~0x20u;
  *(_DWORD *)&binds[4 * (*(_DWORD *)binds << 17 >> 23) + 4] = (int)(uintptr_t)result;
  if ( *(_DWORD *)(theJoin + 36) )
    result = Rules_AddActivation(*(_DWORD *)(theJoin + 36), (int)(uintptr_t)binds, a3);
  join = (uintptr_t)(unsigned int)*(_DWORD *)(theJoin + 20);
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)theJoin == (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)binds, (char *)join, 1, a3);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)binds, (char *)join, 0, a3);
        join = (uintptr_t)(unsigned int)*(_DWORD *)(join + 28);
      }
      while ( join );
    }
  }
  return result;
}
// 48EAA4: conditional instruction was optimized away because ecx.4!=0
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EAE0) --------------------------------------------------------
_DWORD * Rules_AddJoinLeftMemoryEntry(int theJoin, int *rhsBinds, int a3, double a4)
{
  _DWORD *result; // eax
  signed int linker; // esi
  int ruleToActivate; // edx
  int join; // ecx

  if ( !*(_DWORD *)(theJoin + 12)
    || (result = (_DWORD *)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(theJoin + 12), 0, (_BYTE *)(uintptr_t)(unsigned int)theJoin, (int)rhsBinds, a4),
        a3 = 0,
        g_ClipsEvaluationError = 0,
        result) )
  {
    if ( (*(_BYTE *)theJoin & 8) != 0 )
    {
      Rules_ReportSystemError(a3, 2);
      IO_RunRouterExitCallbacks();
    }
    result = Rules_MultifieldCopyWithMarkers(rhsBinds, *(_DWORD *)(theJoin + 36) != 0, *(_DWORD *)theJoin << 30 >> 31);
    result[1] = *(_DWORD *)(theJoin + 8);
    linker = (signed int)result;
    ruleToActivate = *(_DWORD *)(theJoin + 36);
    *(_DWORD *)(theJoin + 8) = result;
    if ( ruleToActivate )
      result = Rules_AddActivation(ruleToActivate, (int)result, a4);
    join = *(_DWORD *)(theJoin + 20);
    while ( join )
    {
      result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)linker, (char *)(uintptr_t)(unsigned int)join, 0, a4);
      join = *(_DWORD *)(join + 28);
    }
  }
  return result;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048EBA0) --------------------------------------------------------
signed int __fastcall Rules_ReportJoinNetworkError(int joinPtr, int a2)
{
  uintptr_t join; // ecx
  char messageBuffer[64]; // [esp+0h] [ebp-48h] BYREF

  (void)a2;
  join = (uintptr_t)(unsigned int)joinPtr;
  Rules_PrintErrorID((int)aDrive, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_1, 0);
  sprintf_(messageBuffer, "   Problem resides in join #%d in rule(s):\n", join ? (*(_DWORD *)join << 16) >> 25 : 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)(uintptr_t)messageBuffer, 0);
  Rules_ClearJoinNetworkMarkedFlags();
  Rules_PrintJoinNetworkNodeRuleOwners((int)join, (int)(uintptr_t)"      ");
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504874, 0);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048EC20) --------------------------------------------------------
int  Rules_AddLogicalDependencyLink(int theEntity, int existingEntity)
{
  int result; // eax
  int v3; // ecx
  _DWORD *theBind; // edx
  _DWORD *freeNode; // esi
  _DWORD *newDependency; // eax
  _DWORD *v7; // edi
  _DWORD *newDependent; // eax

  if ( !g_Rules_CurrentLogicalJoin )
  {
    if ( existingEntity )
      Rules_ReleaseLogicalSupportList(theEntity);
    return 1;
  }
  if ( existingEntity && !*(_DWORD *)(theEntity + 4) )
    return 1;
  result = (int)Rules_FindLogicalDependencyEntry(g_Rules_CurrentLogicalJoin, g_Clips_CurrentPartialMatch);
  theBind = (_DWORD *)result;
  if ( result )
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeNode;
      newDependency = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDependency = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *newDependency = v3;
    newDependency[1] = theBind[(*theBind << 17 >> 23) + 2 + (*theBind << 29 >> 31)];
    theBind[(*theBind << 29 >> 31) + 2 + (*theBind << 17 >> 23)] = newDependency;
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *v7;
      newDependent = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDependent = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *newDependent = theBind;
    newDependent[1] = *(_DWORD *)(v3 + 4);
    *(_DWORD *)(v3 + 4) = newDependent;
    return 1;
  }
  return result;
}
// 48EC79: variable 'v3' is possibly undefined
// 51A1F8: using guessed type int dword_51A1F8;
// 51ACFC: using guessed type int dword_51ACFC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048ED00) --------------------------------------------------------
_DWORD * Rules_FindLogicalDependencyEntry(int theJoin, int theBinds)
{
  _DWORD *compPtr; // esi
  int bindsPtr; // ecx
  _DWORD *compFieldPtr; // eax
  unsigned int i; // edx

  compPtr = *(_DWORD **)(theJoin + 8);
  if ( compPtr )
  {
    while ( 2 )
    {
      bindsPtr = theBinds;
      compFieldPtr = compPtr;
      for ( i = 0; ; ++i )
      {
        if ( i >= *compPtr << 17 >> 23 )
          return compPtr;
        if ( compFieldPtr[2] != *(_DWORD *)(bindsPtr + 8) )
          break;
        bindsPtr += 4;
        ++compFieldPtr;
      }
      compPtr = (_DWORD *)compPtr[1];
      if ( compPtr )
        continue;
      break;
    }
  }
  return 0;
}

//----- (0048ED60) --------------------------------------------------------
int  Rules_ReleaseLogicalSupportList(int result)
{
  uintptr_t fact; // edi
  uintptr_t support; // ebx
  int last; // eax

  fact = (uintptr_t)(unsigned int)result;
  support = fact ? (uintptr_t)(unsigned int)*(_DWORD *)(fact + 4) : 0;
  last = result;
  while ( support )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(support + 4);
    uintptr_t match = (uintptr_t)(unsigned int)*(_DWORD *)support;
    if ( match )
    {
      unsigned int slot_index = ((*(_DWORD *)match << 17) >> 23) + ((*(_DWORD *)match << 29) >> 31);
      _DWORD *head = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(match + 4 * slot_index + 8);
      _DWORD *new_head = Rules_RemoveDependencyLink(head, (int)fact);
      *(_DWORD *)(match + 4 * slot_index + 8) = (int)(uintptr_t)new_head;
    }
    g_ClipsMemFreeListTemp = (int)support;
    *(_DWORD *)support = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
    last = g_ClipsMemFreeListTemp;
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    support = next;
  }
  if ( fact )
    *(_DWORD *)(fact + 4) = 0;
  return last;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EDE0) --------------------------------------------------------
_DWORD * Rules_RemoveDependencyLink(_DWORD *theList, int theEntity)
{
  uintptr_t head; // esi
  uintptr_t current; // eax
  uintptr_t previous; // ecx

  head = (uintptr_t)(unsigned int)(uintptr_t)theList;
  current = head;
  previous = 0;
  while ( current )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
    if ( theEntity == *(_DWORD *)current )
    {
      if ( previous )
        *(_DWORD *)(previous + 4) = (int)next;
      else
        head = next;
      g_ClipsMemFreeListTemp = (int)current;
      *(_DWORD *)current = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      current = next;
    }
    else
    {
      previous = current;
      current = next;
    }
  }
  return (_DWORD *)(uintptr_t)(unsigned int)head;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EE40) --------------------------------------------------------
int  Rules_RemoveEntityDependencies(_DWORD *theBinds)
{
  _DWORD *dependencyPtr; // ecx
  int theBind; // ebx
  _DWORD *nextDependency; // esi
  _DWORD *v5; // ecx
  int result; // eax

  dependencyPtr = (_DWORD *)theBinds[(*theBinds << 29 >> 31) + 2 + (*theBinds << 17 >> 23)];
  if ( dependencyPtr )
  {
    do
    {
      theBind = *dependencyPtr;
      nextDependency = (_DWORD *)dependencyPtr[1];
      *(_DWORD *)(theBind + 4) = Rules_RemoveDependencyLink(*(_DWORD **)(*dependencyPtr + 4), (int)theBinds);
      g_ClipsMemFreeListTemp = (int)v5;
      *v5 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      dependencyPtr = nextDependency;
    }
    while ( nextDependency );
  }
  result = (*theBinds << 17 >> 23) + (*theBinds << 29 >> 31);
  theBinds[result + 2] = 0;
  return result;
}
// 48EE78: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EEC0) --------------------------------------------------------
int  Rules_RemovePMDependencies(int result)
{
  _DWORD *theBinds; // edi
  _DWORD *dependencyPtr; // ecx
  int theBind; // ebx
  _DWORD *nextDependency; // esi
  _DWORD *updatedList; // eax
  _DWORD *v6; // ecx

  theBinds = (_DWORD *)result;
  if ( (*(_BYTE *)result & 8) != 0 )
  {
    dependencyPtr = *(_DWORD **)(result + 4 * ((*(_DWORD *)result << 17 >> 23) + (*(_DWORD *)result << 29 >> 31)) + 8);
    if ( dependencyPtr )
    {
      do
      {
        theBind = *dependencyPtr;
        nextDependency = (_DWORD *)dependencyPtr[1];
        updatedList = Rules_RemoveDependencyLink(*(_DWORD **)(*dependencyPtr + 4), (int)theBinds);
        *(_DWORD *)(theBind + 4) = updatedList;
        if ( updatedList )
        {
          g_ClipsMemFreeListTemp = (int)v6;
          *v6 = *(_DWORD *)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        }
        else
        {
          v6[1] = g_ClipsPendingDependencyDestructorList;
          g_ClipsPendingDependencyDestructorList = (int)v6;
        }
        dependencyPtr = nextDependency;
      }
      while ( nextDependency );
    }
    result = (*theBinds << 17 >> 23) + (*theBinds << 29 >> 31);
    theBinds[result + 2] = 0;
  }
  return result;
}
// 48EF05: variable 'v6' is possibly undefined
// 51A958: using guessed type int dword_51A958;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EF60) --------------------------------------------------------
void Rules_FlushPendingDependencyDestructors()
{
  _DWORD *dependencyPtr; // eax
  int theEntity; // edx

  if ( !g_Rules_FlushingDependencyDestructors )
  {
    g_Rules_FlushingDependencyDestructors = 1;
    while ( g_ClipsPendingDependencyDestructorList )
    {
      dependencyPtr = (_DWORD *)g_ClipsPendingDependencyDestructorList;
      theEntity = *(_DWORD *)g_ClipsPendingDependencyDestructorList;
      g_ClipsPendingDependencyDestructorList = *(_DWORD *)(g_ClipsPendingDependencyDestructorList + 4);
      g_ClipsMemFreeListTemp = (int)dependencyPtr;
      *dependencyPtr = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      (*(void (**)(void))(*(_DWORD *)theEntity + 12))();
    }
    g_Rules_FlushingDependencyDestructors = 0;
  }
}
// 51A958: using guessed type int dword_51A958;
// 51A95C: using guessed type int dword_51A95C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EFD0) --------------------------------------------------------
signed int  Rules_PrintDependencyList(signed int result, int a2)
{
  _DWORD **dependencyPtr; // ecx
  int v3; // ecx
  signed int v4; // eax
  int v5; // ecx

  if ( !*(_DWORD *)(result + 4) )
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone, a2);
  dependencyPtr = *(_DWORD ***)(result + 4);
  do
  {
    Rules_PrintArgumentValueList((int)g_IO_LogicalName_WDisplay, *dependencyPtr);
    v4 = Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504880, v3);
    dependencyPtr = *(_DWORD ***)(v5 + 4);
  }
  while ( dependencyPtr );
  return v4;
}
// 48EFDB: conditional instruction was optimized away because edx.4!=0
// 48EFF3: variable 'v3' is possibly undefined
// 48EFF8: variable 'v5' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F020) --------------------------------------------------------
signed int  Rules_PrintDependentList(int theEntity, int a2)
{
  int v4; // ecx
  int found; // esi
  _DWORD **dependencyPtr; // ecx
  int v7; // ecx
  _DWORD *entityPtr; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD traversalBuffer[6]; // [esp+4h] [ebp-18h] BYREF

  traversalBuffer[4] = a2;
  entityPtr = 0;
  traversalBuffer[0] = 0;
  Rules_FindPatternParser(traversalBuffer, &entityPtr);
  found = 0;
  while ( entityPtr )
  {
    dependencyPtr = (_DWORD **)entityPtr[1];
    if ( dependencyPtr )
    {
      while ( Rules_ArrayContainsValue(theEntity, *dependencyPtr) != 1 )
      {
        dependencyPtr = *(_DWORD ***)(v7 + 4);
        if ( !dependencyPtr )
          goto LABEL_7;
      }
      if ( found )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504884, v7);
      found = 1;
      (*(void (**)(void))(*entityPtr + 4))();
    }
LABEL_7:
    Rules_FindPatternParser(traversalBuffer, &entityPtr);
  }
  if ( found )
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504880, v4);
  else
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone, v4);
}
// 48F06D: variable 'v7' is possibly undefined
// 48F0A6: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F0E0) --------------------------------------------------------
signed int  Rules_ArrayContainsValue(int theEntity, _DWORD *theMatch)
{
  __int16 i; // ax

  for ( i = 0; i < *theMatch << 17 >> 23; ++i )
  {
    if ( theEntity == *(_DWORD *)theMatch[i + 2] )
      return 1;
  }
  return 0;
}

//----- (0048F120) --------------------------------------------------------
_DWORD * Rules_Dependencies(double a1)
{
  _DWORD *result; // eax
  int v2; // ecx
  int v3; // ecx
  int itemBuffer; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&itemBuffer, aDependencies_0, v2, a1);
    if ( result )
      return (_DWORD *)Rules_PrintDependencyList((signed int)result, v3);
  }
  return result;
}
// 48F148: variable 'v2' is possibly undefined
// 48F151: variable 'v3' is possibly undefined

//----- (0048F160) --------------------------------------------------------
_DWORD * Rules_Dependents(double a1)
{
  _DWORD *result; // eax
  int v2; // ecx
  int v3; // ecx
  int itemBuffer; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&itemBuffer, aDependents_0, v2, a1);
    if ( result )
      return (_DWORD *)Rules_PrintDependentList((int)result, v3);
  }
  return result;
}
// 48F188: variable 'v2' is possibly undefined
// 48F191: variable 'v3' is possibly undefined

//----- (0048F1A0) --------------------------------------------------------
_DWORD * Rules_ResolveFactOrInstanceArg(_DWORD *item, _BYTE *functionName, int a3, double a4)
{
  int v5; // ecx
  int theType; // edx
  int v7; // ecx
  _DWORD *foundEntity; // ebx
  _BYTE *itemName; // edx
  int v11; // ecx
  _BYTE numberBuffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+14h] [ebp-8h]

  v13 = a3;
  Rules_RtnUnknown(1, item, a4);
  theType = *(_DWORD *)(v5 + 4);
  if ( theType == 6 || theType == 7 )
    return *(_DWORD **)(v5 + 8);
  if ( theType == 1 )
  {
    foundEntity = (_DWORD *)Rules_FindFactByIndex();
    if ( foundEntity )
      return foundEntity;
    sprintf_(numberBuffer, "f-%ld", *(_DWORD *)(*(_DWORD *)(v11 + 8) + 16));
    itemName = numberBuffer;
    goto LABEL_8;
  }
  if ( theType != 8 && theType != 2 )
  {
    Rules_ReportSymbolTypeError(functionName, 1);
    return 0;
  }
  foundEntity = Instance_FindByName(*(_DWORD *)(v5 + 8));
  if ( !foundEntity )
  {
    itemName = *(_BYTE **)(*(_DWORD *)(v7 + 8) + 16);
LABEL_8:
    Rules_ReportCantFindItem(v7, (int)itemName);
  }
  return foundEntity;
}
// 48F1B5: variable 'v5' is possibly undefined
// 48F1DF: variable 'v7' is possibly undefined
// 48F20D: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (0048F300) --------------------------------------------------------
int  Parser_ParseForm(__int16 *problem, _DWORD *returnValue, int a3, double a4)
{
  _DWORD *valuePtr; // ecx
  int theType; // eax
  int result; // eax
  int oldArgument; // ebx
  int theFunction; // edx
  void *theValue; // eax
  int v11; // ecx
  int *longResult; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int entityRecord; // edx
  int savedExpression; // edi
  int v20; // ecx
  uintptr_t function_ptr;
  uintptr_t evaluator;
  double doubleResult; // [esp+0h] [ebp-18h]
  char charBuffer[8]; // [esp+Ch] [ebp-Ch] BYREF
  int v23; // [esp+14h] [ebp-4h]

  v23 = a3;
  valuePtr = returnValue;
  if ( problem )
  {
    switch ( *problem )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 5:
      case 7:
      case 8:
        theType = *problem;
        goto LABEL_4;
      case 4:
        returnValue[1] = 4;
        returnValue[2] = *(_DWORD *)(*(_DWORD *)(problem + 1) + 8);
        returnValue[3] = *(_DWORD *)(*(_DWORD *)(problem + 1) + 12);
        returnValue[4] = *(_DWORD *)(*(_DWORD *)(problem + 1) + 16);
        Rules_PropagateReturnValueDepth((uintptr_t)returnValue);
        return g_ClipsEvaluationError;
      case 10:
        oldArgument = g_ClipsCurrentExpression;
        g_ClipsCurrentExpression = (int)problem;
        theFunction = *(_DWORD *)(problem + 1);
        function_ptr = (uintptr_t)(unsigned int)*(_DWORD *)(theFunction + 9);
        switch ( *(_BYTE *)(theFunction + 8) )
        {
          case 'a':
            valuePtr[1] = 5;
            goto LABEL_9;
          case 'b':
            valuePtr[1] = 2;
            if ( !((int (*)(void))function_ptr)() )
              goto LABEL_13;
            theValue = (void *)g_ClipsTrueSymbol;
            goto LABEL_10;
          case 'c':
            charBuffer[0] = ((int (*)(_DWORD *))function_ptr)(valuePtr);
            charBuffer[1] = 0;
            valuePtr[1] = 2;
            theValue = Str_Intern(charBuffer, 0);
            goto LABEL_10;
          case 'd':
          case 'f':
            valuePtr[1] = 0;
            doubleResult = ((double (*)(void))function_ptr)();
            theValue = (void *)Rules_AddDoubleValue(doubleResult);
            goto LABEL_10;
          case 'i':
          case 'l':
            valuePtr[1] = 1;
            longResult = (int *)((uintptr_t)(unsigned int)((int (*)(void))function_ptr)());
            theValue = Rules_AddIntegerValue(longResult);
            goto LABEL_10;
          case 'j':
          case 'k':
          case 'm':
          case 'n':
          case 'u':
            ((void (*)(uintptr_t, uintptr_t, double))function_ptr)((uintptr_t)valuePtr, (uintptr_t)valuePtr, a4);
            break;
          case 'o':
            valuePtr[1] = 8;
            goto LABEL_9;
          case 's':
            valuePtr[1] = 3;
            goto LABEL_9;
          case 'v':
            ((void (*)(void))function_ptr)();
            valuePtr[1] = 105;
LABEL_13:
            theValue = (void *)g_ClipsFalseSymbol;
            goto LABEL_10;
          case 'w':
            valuePtr[1] = 2;
            goto LABEL_9;
          case 'x':
            valuePtr[1] = 7;
LABEL_9:
            theValue = (void *)(uintptr_t)(unsigned int)((int (*)(void))function_ptr)();
LABEL_10:
            valuePtr[2] = (int)(uintptr_t)theValue;
            break;
          default:
            Rules_ReportSystemError((int)valuePtr, 2);
            IO_RunRouterExitCallbacks(5);
            break;
        }
        g_ClipsCurrentExpression = oldArgument;
        Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
        return g_ClipsEvaluationError;
      case 15:
      case 16:
        if ( Rules_FindBoundVariable(returnValue, *(_DWORD *)(problem + 1)) )
          goto LABEL_5;
        Rules_PrintErrorID((int)aEvaluatn, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(problem + 1) + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUnbound, v16);
        valuePtr[1] = 2;
        valuePtr[2] = g_ClipsFalseSymbol;
        g_ClipsEvaluationError = 1;
        g_ClipsHaltExecution = 1;
        Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
        result = g_ClipsEvaluationError;
        break;
      default:
        if ( !g_Clips_PrimitiveEntityTable[*problem] )
        {
          Rules_ReportSystemError((int)returnValue, 3);
          IO_RunRouterExitCallbacks(5);
        }
        theType = *problem;
        entityRecord = g_Clips_PrimitiveEntityTable[theType];
        if ( (*(_BYTE *)(entityRecord + 1) & 0x20) != 0 )
        {
LABEL_4:
          valuePtr[1] = theType;
          valuePtr[2] = *(_DWORD *)(problem + 1);
LABEL_5:
          Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
          result = g_ClipsEvaluationError;
        }
        else
        {
          if ( !*(_DWORD *)(entityRecord + 16) )
          {
            Rules_ReportSystemError((int)valuePtr, 4);
            IO_RunRouterExitCallbacks(5);
          }
          savedExpression = g_ClipsCurrentExpression;
          g_ClipsCurrentExpression = (int)problem;
          evaluator = (uintptr_t)(unsigned int)*(_DWORD *)(g_Clips_PrimitiveEntityTable[*problem] + 16);
          ((void (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)(problem + 1), valuePtr, a4);
          g_ClipsCurrentExpression = savedExpression;
          Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
          result = g_ClipsEvaluationError;
        }
        break;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return g_ClipsEvaluationError;
  }
  return result;
}
// 48F3F2: inconsistent fpu stack
// 48F32A: variable 'v5' is possibly undefined
// 48F392: variable 'v11' is possibly undefined
// 48F437: variable 'v13' is possibly undefined
// 48F4D2: variable 'v14' is possibly undefined
// 48F4E2: variable 'v15' is possibly undefined
// 48F4F1: variable 'v16' is possibly undefined
// 48F4F6: variable 'v17' is possibly undefined
// 48F5AA: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F5C0) --------------------------------------------------------
int  Rules_RegisterEvaluationHandler(int result, int whichPosition)
{
  int thePrimitive; // ebx
  int v3; // ecx

  thePrimitive = result;
  if ( g_Clips_PrimitiveEntityTable[whichPosition] )
  {
    Rules_ReportSystemError(whichPosition, 5);
    result = IO_RunRouterExitCallbacks();
    g_Clips_PrimitiveEntityTable[v3] = thePrimitive;
  }
  else
  {
    g_Clips_PrimitiveEntityTable[whichPosition] = result;
  }
  return result;
}
// 48F5F3: variable 'v3' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F600) --------------------------------------------------------
int  Lexer_ErrorRecover(int result)
{
  g_ClipsEvaluationError = result;
  if ( result == 1 )
    return Rules_SetEvaluationErrorFlag(1);
  return result;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048F610) --------------------------------------------------------
int  Rules_SetEvaluationErrorFlag(int result)
{
  g_ClipsHaltExecution = result;
  return result;
}
// 51A968: using guessed type int dword_51A968;

//----- (0048F620) --------------------------------------------------------
int Rules_GetHaltExecutionFlag()
{
  return g_ClipsEvaluationError;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048F630) --------------------------------------------------------
int Rules_GetEvaluationErrorFlag()
{
  return g_ClipsHaltExecution;
}
// 51A968: using guessed type int dword_51A968;

//----- (0048F640) --------------------------------------------------------
int  Rules_DeinstallValueChain(int result)
{
  int currentValue; // edx
  _DWORD *v2; // edx
  int v3; // ecx

  currentValue = result;
  if ( result )
  {
    do
    {
      Rules_ValueDeinstall(currentValue, *(_DWORD *)(currentValue + 20));
      g_ClipsMemFreeListTemp = (int)v2;
      *v2 = *(_DWORD *)(g_ClipsMemoryTable + 96);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
      currentValue = v3;
    }
    while ( v3 );
  }
  return result;
}
// 48F657: variable 'v2' is possibly undefined
// 48F670: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048F690) --------------------------------------------------------
signed int  Rules_PrintDataObject(int logicalName, int argPtr)
{
  unsigned int theType; // eax
  signed int result; // eax
  int v5; // ecx
  int v6; // ecx

  theType = *(_DWORD *)(argPtr + 4);
  if ( theType < 4 )
    return Rules_PrintAtomValue(logicalName, *(_DWORD *)(argPtr + 4), *(int **)(argPtr + 8));
  if ( theType <= 4 )
    return Lexer_OutputFieldRange(logicalName, *(_DWORD *)(argPtr + 8), *(_DWORD *)(argPtr + 16), *(_DWORD *)(argPtr + 12), 1);
  if ( theType <= 8 || theType == 105 )
    return Rules_PrintAtomValue(logicalName, *(_DWORD *)(argPtr + 4), *(int **)(argPtr + 8));
  Output_Write(logicalName, (int)aUnknownprintty, argPtr);
  Rules_PrintLongInteger(v5, *(_DWORD *)(v5 + 4));
  result = Output_Write(logicalName, (int)asc_5048FC, v6);
  g_ClipsEvaluationError = 1;
  g_ClipsHaltExecution = 1;
  return result;
}
// 48F6BE: simplified comparisons for 'eax.4': <7u || <8u became <8u
// 48F6BE: simplified comparisons for 'eax.4': <8u || <9u became <9u
// 48F6DD: variable 'v5' is possibly undefined
// 48F6E9: variable 'v6' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;

//----- (0048F720) --------------------------------------------------------
_DWORD * Rules_SetMultifieldErrorValue(int returnValue)
{
  _DWORD *result; // eax
  _DWORD *v2; // edx

  *(_DWORD *)(returnValue + 4) = 4;
  result = Rules_CreateEphemeralMultifield(0);
  v2[3] = 1;
  v2[4] = 0;
  v2[2] = result;
  return result;
}
// 48F731: variable 'v2' is possibly undefined

//----- (0048F750) --------------------------------------------------------
__int16 * Rules_ValueInstall(int vPtr, int a2)
{
  if ( *(_DWORD *)(vPtr + 4) == 4 )
    return Rules_InstallMultifield(*(__int16 **)(vPtr + 8));
  else
    return (__int16 *)Rules_AtomInstall(*(_DWORD *)(vPtr + 4), *(_DWORD *)(vPtr + 8), a2);
}

//----- (0048F770) --------------------------------------------------------
__int16 * Rules_ValueDeinstall(int vPtr, int a2)
{
  if ( *(_DWORD *)(vPtr + 4) == 4 )
    return Rules_DeinstallMultifield(*(__int16 **)(vPtr + 8));
  else
    return (__int16 *)Rules_AtomDeinstall(*(_DWORD *)(vPtr + 4), *(__int16 **)(vPtr + 8), a2);
}

//----- (0048F790) --------------------------------------------------------
unsigned int  Rules_AtomInstall(unsigned int result, int vPtr, int a3)
{
  int entityRecord; // esi

  if ( result < 4 )
    goto LABEL_15;
  if ( result >= 8 )
  {
    if ( result <= 8 )
      goto LABEL_15;
    if ( result >= 0xD )
    {
      if ( result <= 0xD )
        goto LABEL_15;
      if ( result == 105 )
        return result;
    }
  }
  else if ( result == 4 )
  {
    return (unsigned int)Rules_InstallMultifield((__int16 *)vPtr);
  }
  result *= 4;
  entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( !entityRecord )
    return result;
  result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( (*(_BYTE *)(entityRecord + 1) & 0x40) != 0 )
  {
LABEL_15:
    ++*(_DWORD *)(vPtr + 4);
    return result;
  }
  if ( *(_DWORD *)(entityRecord + 28) )
    return (*(int (__cdecl **)(int))(entityRecord + 28))(a3);
  return result;
}
// 48F795: simplified comparisons for 'eax.4': >=3u && >=4u became >=4u
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F800) --------------------------------------------------------
unsigned int  Rules_AtomDeinstall(unsigned int result, __int16 *vPtr, int a3)
{
  int entityRecord; // ecx

  if ( result < 3 )
  {
    if ( !result )
      return Rules_DecrementFloatCount((int)vPtr, a3);
    if ( result <= 1 )
      return Rules_DecrementIntegerCount((int)vPtr, a3);
    return Rules_DecrementSymbolCount((int)vPtr, a3);
  }
  if ( result <= 3 )
    return Rules_DecrementSymbolCount((int)vPtr, a3);
  if ( result < 8 )
  {
    if ( result == 4 )
      return (unsigned int)Rules_DeinstallMultifield(vPtr);
    goto LABEL_4;
  }
  if ( result <= 8 )
    return Rules_DecrementSymbolCount((int)vPtr, a3);
  if ( result >= 0xD )
  {
    if ( result > 0xD )
    {
      if ( result == 105 )
        return result;
      goto LABEL_4;
    }
    return Rules_DecrementSymbolCount((int)vPtr, a3);
  }
LABEL_4:
  result *= 4;
  entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( entityRecord )
  {
    result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
    if ( (*(_BYTE *)(entityRecord + 1) & 0x40) != 0 )
    {
      return Rules_DecrementBitmapCount((int)vPtr, entityRecord);
    }
    else if ( *(_DWORD *)(entityRecord + 24) )
    {
      return (*(int (__cdecl **)(int))(entityRecord + 24))(a3);
    }
  }
  return result;
}
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F8A0) --------------------------------------------------------
int  Rules_PropagateReturnValueDepth(uintptr_t vPtr)
{
  int result; // eax
  int fieldIndex; // ebx
  int end; // edi
  __int16 *fieldPtr; // ecx

  if ( *(_DWORD *)(vPtr + 4) != 4 )
    return Rules_ClampEvaluationDepth(*(_DWORD *)(vPtr + 4), (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(vPtr + 8));
  result = *(_DWORD *)(vPtr + 8);
  if ( *(__int16 *)((uintptr_t)(unsigned int)result + 4) > g_ClipsCurrentEvaluationDepth )
    *(_WORD *)((uintptr_t)(unsigned int)result + 4) = g_ClipsCurrentEvaluationDepth;
  fieldIndex = *(_DWORD *)(vPtr + 12);
  end = *(int *)(vPtr + 16);
  if ( fieldIndex <= end )
  {
    fieldPtr = (__int16 *)((uintptr_t)(unsigned int)result + 6 * fieldIndex + 14);
    do
    {
      result = Rules_ClampEvaluationDepth(*fieldPtr, (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(fieldPtr + 1));
      ++fieldIndex;
      fieldPtr += 3;
    }
    while ( fieldIndex <= end );
  }
  return result;
}
// 48F8E8: variable 'v5' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;

//----- (0048F940) --------------------------------------------------------
int  Rules_ClampEvaluationDepth(int result, _DWORD *theValue)
{
  __int16 currentDepth; // bx

  switch ( result )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
      if ( g_ClipsCurrentEvaluationDepth < theValue[2] )
        theValue[2] = g_ClipsCurrentEvaluationDepth;
      break;
    case 6:
      currentDepth = g_ClipsCurrentEvaluationDepth;
      result = theValue[7] & 0x7FFF;
      if ( result > g_ClipsCurrentEvaluationDepth )
      {
        *((_WORD *)theValue + 14) &= 0x8000u;
        result = currentDepth & 0x7FFF;
        theValue[7] |= result;
      }
      break;
    case 7:
      if ( g_ClipsCurrentEvaluationDepth < theValue[8] )
        theValue[8] = g_ClipsCurrentEvaluationDepth;
      break;
    default:
      return result;
  }
  return result;
}
// 51A96C: using guessed type int dword_51A96C;

//----- (0048FB10) --------------------------------------------------------
signed int  AST_BuildExpressionFromValue(_DWORD *theValue)
{
  int theType; // ecx
  signed int lastNode; // ebx
  int fieldIndex; // ecx
  int fieldOffset; // esi
  signed int newNode; // eax
  int v8; // ecx
  int **Symbol; // eax
  signed int topNode; // [esp+0h] [ebp-18h]

  theType = theValue[1];
  lastNode = 0;
  topNode = 0;
  if ( theType != 4 )
    return AST_NewNode(theType, theValue[2]);
  fieldIndex = theValue[3] + 1;
  fieldOffset = 6 * fieldIndex - 6;
  while ( fieldIndex <= theValue[4] + 1 )
  {
    newNode = AST_NewNode(*(_WORD *)(fieldOffset + theValue[2] + 14), *(_DWORD *)(fieldOffset + theValue[2] + 16));
    if ( lastNode )
      *(_DWORD *)(lastNode + 10) = newNode;
    else
      topNode = newNode;
    lastNode = newNode;
    fieldOffset += 6;
    fieldIndex = v8 + 1;
  }
  if ( topNode )
    return topNode;
  Symbol = Rules_MakeSymbol(aCreate_1);
  return AST_NewNode(10, (int)Symbol);
}
// 48FB80: variable 'v8' is possibly undefined

//----- (0048FBD0) --------------------------------------------------------
int  Rules_ComputeFieldHashValue(int theType, int value, int position)
{
  int result; // eax

  result = value;
  switch ( theType )
  {
    case CLIPS_TYPE_FLOAT:
      result = *(_DWORD *)(value + 16);
      goto LABEL_3;
    case CLIPS_TYPE_INTEGER:
      result = *(_DWORD *)(value + 16);
      goto LABEL_3;
    case CLIPS_TYPE_SYMBOL:
    case CLIPS_TYPE_STRING:
    case CLIPS_TYPE_INSTANCE_NAME:
      result = *(_DWORD *)(value + 12) << 16 >> 18;
      goto LABEL_3;
    case CLIPS_TYPE_EXTERNAL_ADDRESS:
    case CLIPS_TYPE_FACT_ADDRESS:
    case CLIPS_TYPE_INSTANCE_ADDRESS:
LABEL_3:
      if ( position >= 0 )
        result *= position + 29;
      break;
    default:
      result = theType;
      if ( position >= 0 )
        result = (position + 29) * theType;
      break;
  }
  return result;
}

//----- (0048FC30) --------------------------------------------------------
int  Rules_RetractFactFromNetwork(_DWORD *matchList, double a2)
{
  unsigned int link_record; // edi
  unsigned int pattern; // esi
  unsigned int node; // esi/ecx
  unsigned int partial_match; // ebx
  unsigned int next_link; // eax
  int removed_nodes; // [esp+0h] [ebp-20h] BYREF
  int retained_tail; // [esp+4h] [ebp-1Ch] BYREF

  for ( link_record = (unsigned int)(uintptr_t)matchList; link_record; link_record = *(_DWORD *)(uintptr_t)link_record )
  {
    pattern = *(_DWORD *)((uintptr_t)link_record + 8);
    partial_match = *(_DWORD *)((uintptr_t)link_record + 4);
    for ( node = *(_DWORD *)((uintptr_t)pattern + 8); node; node = *(_DWORD *)((uintptr_t)node + 32) )
    {
      if ( (*(_BYTE *)(uintptr_t)node & 8) == 0 )
        Rules_PropagateRetractToJoinNode(
          (int)node,
          *(_DWORD *)((uintptr_t)partial_match + 8),
          ((*(_DWORD *)(uintptr_t)node << 16) >> 25) - 1,
          partial_match,
          a2,
          1);
    }
  }

  link_record = (unsigned int)(uintptr_t)matchList;
  while ( link_record )
  {
    pattern = *(_DWORD *)((uintptr_t)link_record + 8);
    partial_match = *(_DWORD *)((uintptr_t)link_record + 4);
    for ( node = *(_DWORD *)((uintptr_t)pattern + 8); node; node = *(_DWORD *)((uintptr_t)node + 32) )
    {
      if ( (*(_BYTE *)(uintptr_t)node & 8) != 0 )
      {
        if ( (*(_DWORD *)(uintptr_t)node & 1) == 1 )
        {
          Rules_ReportSystemError((int)node, 3);
          IO_RunRouterExitCallbacks();
        }
        else
        {
          Rules_UpdateBetaMemoryOnRetract((_DWORD *)(uintptr_t)node, partial_match, 1, a2);
        }
      }
    }
    removed_nodes = 0;
    retained_tail = 0;
    *(_DWORD *)(uintptr_t)pattern = Rules_FilterPartialMatchList(
                                      *(_DWORD *)((uintptr_t)partial_match + 8),
                                      (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)pattern,
                                      0,
                                      &removed_nodes,
                                      &retained_tail);
    *(_DWORD *)((uintptr_t)pattern + 4) = retained_tail;
    Rules_FreePartialMatchList(removed_nodes, 0);
    next_link = *(_DWORD *)(uintptr_t)link_record;
    g_ClipsMemFreeListTemp = link_record;
    *(_DWORD *)(uintptr_t)link_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
    link_record = next_link;
  }
  return Rules_FlushDeferredRetractQueue(a2);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048FD50) --------------------------------------------------------
int  Rules_PropagateRetractToJoinNode(int result, int theEntity, int position, int a4, double a5, int deferJoinDrive)
{
  uintptr_t node; // [esp+8h] [ebp-14h]
  int removed_nodes; // [esp+0h] [ebp-1Ch] BYREF
  int retained_tail; // [esp+4h] [ebp-18h] BYREF
  int last; // eax

  node = (uintptr_t)(unsigned int)result;
  last = result;
  while ( node )
  {
    if ( !*(_DWORD *)(node + 8) )
      return last;
    last = Rules_FilterPartialMatchList(
             theEntity,
             (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8),
             position,
             &removed_nodes,
             &retained_tail);
    *(_DWORD *)(node + 8) = last;
    if ( !removed_nodes )
      return last;
    {
      uintptr_t child = (uintptr_t)(unsigned int)*(_DWORD *)(node + 20);
      if ( !child )
        return Rules_FreePartialMatchList(removed_nodes, 1);
      if ( (int)node == *(_DWORD *)(child + 16) )
      {
        uintptr_t removed = (uintptr_t)(unsigned int)removed_nodes;
        while ( removed )
        {
          Rules_UpdateBetaMemoryOnRetract((_DWORD *)child, (int)removed, deferJoinDrive, a5);
          removed = (uintptr_t)(unsigned int)*(_DWORD *)(removed + 4);
        }
        return Rules_FreePartialMatchList(removed_nodes, 1);
      }
      last = Rules_FreePartialMatchList(removed_nodes, 1);
      while ( *(_DWORD *)(child + 28) )
      {
        last = Rules_PropagateRetractToJoinNode((int)child, theEntity, position, a4, a5, deferJoinDrive);
        child = (uintptr_t)(unsigned int)*(_DWORD *)(child + 28);
      }
      node = child;
    }
  }
  return last;
}

//----- (0048FE40) --------------------------------------------------------
_DWORD * Rules_UpdateBetaMemoryOnRetract(_DWORD *result, int theBind, int deferJoinDrive, double a4)
{
  int theJoin; // edi
  int currentMatch; // esi
  int v7; // edx
  _DWORD *v8; // ecx
  int childJoin; // ecx
  int v10; // ecx
  _DWORD *v11; // ecx

  theJoin = (int)result;
  currentMatch = result[2];
  if ( currentMatch )
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)currentMatch & 0x20) == 0 )
        goto LABEL_3;
      result = (_DWORD *)(currentMatch + 4 * (*(_DWORD *)currentMatch << 17 >> 23));
      v7 = result[1];
      if ( theBind != v7 )
        goto LABEL_3;
      result[1] = 0;
      result = (_DWORD *)Rules_EvaluateJoinTest((_WORD *)currentMatch, *(_DWORD *)(v7 + 4), theJoin, a4);
      if ( result )
        goto LABEL_3;
      *(_BYTE *)currentMatch &= ~0x20u;
      v8 = *(_DWORD **)(g_ClipsMemoryTable + 48);
      if ( v8 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(g_ClipsMemoryTable + 48) = *v8;
        result = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      result[2] = 0;
      *result = 0;
      result[1] = 0;
      *(_DWORD *)(currentMatch + 4 * (*(_DWORD *)currentMatch << 17 >> 23) + 4) = result;
      if ( *(_DWORD *)(theJoin + 36) )
        result = Rules_AddActivation(*(_DWORD *)(theJoin + 36), currentMatch, a4);
      childJoin = *(_DWORD *)(theJoin + 20);
      if ( !childJoin )
        goto LABEL_3;
      if ( theJoin == *(_DWORD *)(childJoin + 16) )
      {
        result = (_DWORD *)Rules_DriveJoinNetwork(currentMatch, *(_DWORD *)(theJoin + 20), 1, a4);
        currentMatch = *(_DWORD *)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
      else if ( deferJoinDrive )
      {
        v11 = *(_DWORD **)(g_ClipsMemoryTable + 48);
        if ( v11 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(g_ClipsMemoryTable + 48) = *v11;
          result = (_DWORD *)g_ClipsMemFreeListTemp;
        }
        else
        {
          result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
        }
        *result = currentMatch;
        result[1] = *(_DWORD *)(theJoin + 20);
        result[2] = g_ClipsDeferredJoinDriveListHead;
        g_ClipsDeferredJoinDriveListHead = (int)result;
        currentMatch = *(_DWORD *)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
      else
      {
        while ( childJoin )
        {
          result = (_DWORD *)Rules_DriveJoinNetwork(currentMatch, childJoin, 0, a4);
          childJoin = *(_DWORD *)(v10 + 28);
        }
LABEL_3:
        currentMatch = *(_DWORD *)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
    }
  }
  return result;
}
// 48FF0A: variable 'v10' is possibly undefined
// 51A970: using guessed type int dword_51A970;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048FFA0) --------------------------------------------------------
signed int  Rules_EvaluateJoinTest(_WORD *theBind, int listOfMatches, int theJoin, double a4)
{
  _WORD *bindFieldPtr; // edx
  int matchFieldPtr; // ecx
  int i; // eax
  signed int testResult; // [esp+0h] [ebp-14h]

  if ( (*(_BYTE *)theJoin & 4) != 0 )
    listOfMatches = *(_DWORD *)(*(_DWORD *)(theJoin + 16) + 8);
  while ( listOfMatches )
  {
    testResult = 0;
    if ( (*(_BYTE *)listOfMatches & 0x20) == 0 )
    {
      if ( *(_DWORD *)(theJoin + 12) )
      {
        testResult = Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(theJoin + 12), theBind, (_BYTE *)(uintptr_t)(unsigned int)theJoin, listOfMatches, a4);
        if ( g_ClipsEvaluationError )
        {
          g_ClipsEvaluationError = 0;
LABEL_15:
          *(_DWORD *)&theBind[2 * (*(_DWORD *)theBind << 17 >> 23) + 2] = listOfMatches;
          return 1;
        }
      }
      else
      {
        testResult = 1;
        if ( (*(_BYTE *)theJoin & 4) != 0 )
        {
          bindFieldPtr = theBind;
          matchFieldPtr = listOfMatches;
          for ( i = 0; i < (*(_DWORD *)theBind << 17 >> 23) - 1; ++i )
          {
            if ( *(_DWORD *)(matchFieldPtr + 8) != *((_DWORD *)bindFieldPtr + 2) )
              goto LABEL_6;
            bindFieldPtr += 2;
            matchFieldPtr += 4;
          }
        }
      }
    }
    if ( testResult )
      goto LABEL_15;
LABEL_6:
    listOfMatches = *(_DWORD *)(listOfMatches + 4);
  }
  return 0;
}
// 51A964: using guessed type int dword_51A964;

//----- (00490060) --------------------------------------------------------
int  Rules_FilterPartialMatchList(int theEntity, _DWORD *listOfPMs, int position, int *deletedMatches, int *lastMatch)
{
  uintptr_t current; // esi
  uintptr_t removed_tail; // ebp
  uintptr_t previous; // ecx
  uintptr_t head; // [esp+Ch] [ebp-10h]
  int slot_offset; // [esp+0h] [ebp-1Ch]

  current = (uintptr_t)(unsigned int)(uintptr_t)listOfPMs;
  head = current;
  previous = current;
  removed_tail = 0;
  slot_offset = 4 * position;
  *deletedMatches = 0;
  while ( current )
  {
    unsigned int field_count = ((unsigned int)*(_DWORD *)current << 17) >> 23;
    int keep = ((*(_BYTE *)current & 0x20) != 0 && (int)field_count - 1 == position);
    if ( !keep )
      keep = theEntity != *(_DWORD *)(current + slot_offset + 8);
    if ( keep )
    {
      previous = current;
      current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
    }
    else
    {
      uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
      if ( (*(_BYTE *)current & 4) != 0 )
      {
        unsigned int nested = *(_DWORD *)(current + 4 * field_count + 8);
        if ( nested )
          Rules_RemoveActivation((_DWORD *)(uintptr_t)nested, 1, 1);
      }
      if ( current == head )
      {
        if ( *deletedMatches )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *deletedMatches = (int)current;
        removed_tail = current;
        head = next;
        *(_DWORD *)(current + 4) = 0;
        current = next;
        previous = head;
      }
      else
      {
        *(_DWORD *)(previous + 4) = (int)next;
        if ( *deletedMatches )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *deletedMatches = (int)current;
        *(_DWORD *)(current + 4) = 0;
        removed_tail = current;
        current = next;
      }
    }
  }
  *lastMatch = (int)previous;
  return (int)head;
}

//----- (00490160) --------------------------------------------------------
signed int  Rules_FreePartialMatchList(signed int result, int betaDelete)
{
  uintptr_t node; // ecx
  signed int last; // eax

  node = (uintptr_t)(unsigned int)result;
  last = result;
  while ( node )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(node + 4);
    if ( (*(_BYTE *)node & 8) != 0 )
      Rules_RemovePMDependencies((int)node);
    if ( !betaDelete || ((*(_BYTE *)node & 0x10) != 0 && (*(_BYTE *)node & 0x20) == 0) )
    {
      last = g_PartialMatchFreeListHead;
      *(_DWORD *)(node + 4) = g_PartialMatchFreeListHead;
      g_PartialMatchFreeListHead = (int)node;
    }
    else
    {
      last = Rules_FreePartialMatch((int)node);
    }
    node = next;
  }
  return last;
}
// 51A974: using guessed type int dword_51A974;

//----- (004901C0) --------------------------------------------------------
signed int  Rules_FreePartialMatch(int theMatch)
{
  uintptr_t node; // ecx
  uintptr_t value_record; // eax
  unsigned int free_bucket; // eax
  signed int result; // eax

  node = (uintptr_t)(unsigned int)theMatch;
  if ( (*(_BYTE *)node & 2) != 0 )
  {
    result = g_PartialMatchFreeListHead;
    *(_DWORD *)(node + 4) = g_PartialMatchFreeListHead;
    g_PartialMatchFreeListHead = (int)node;
  }
  else
  {
    if ( (*(_BYTE *)node & 1) == 0 )
    {
      value_record = (uintptr_t)(unsigned int)*(_DWORD *)(node + 8);
      if ( *(_DWORD *)(value_record + 4) )
        Rules_FreeValueRecordChain((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(value_record + 4));
      Mem_SmallBlockFree((_DWORD *)value_record, 12);
    }
    if ( (*(_BYTE *)node & 8) != 0 )
      Rules_RemoveEntityDependencies((_DWORD *)node);
    free_bucket = 4
                * ((((unsigned int)*(_DWORD *)node << 29) >> 31)
                 + (((unsigned int)*(_DWORD *)node << 17) >> 23)
                 + (((unsigned int)*(_DWORD *)node << 28) >> 31))
                + 8;
    g_Rules_MemPoolFreeBucketIndex = free_bucket;
    if ( free_bucket >= 0x1F4 )
    {
      return Mem_ReleasePoolBlock((int)node, free_bucket);
    }
    else
    {
      g_ClipsMemFreeListTemp = (int)node;
      *(_DWORD *)node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 4 * free_bucket);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 4 * g_Rules_MemPoolFreeBucketIndex) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 4901E8: variable 'v1' is possibly undefined
// 51A974: using guessed type int dword_51A974;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB0: using guessed type int dword_54DBB0;

//----- (00490280) --------------------------------------------------------
_DWORD * Rules_FreeValueRecordChain(_DWORD *result)
{
  uintptr_t node; // eax
  unsigned int next_node; // edx

  node = (uintptr_t)(unsigned int)(uintptr_t)result;
  if ( node )
  {
    do
    {
      next_node = *(_DWORD *)(node + 16);
      g_ClipsMemFreeListTemp = (int)node;
      *(_DWORD *)node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
      node = (uintptr_t)next_node;
    }
    while ( node );
  }
  return (_DWORD *)node;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004902C0) --------------------------------------------------------
int  Rules_FlushDeferredRetractQueue(double a1)
{
  char *i; // ecx
  int v2; // ecx
  int nextEntry; // ecx
  int result; // eax

  if ( g_ClipsDeferredJoinDriveListHead )
  {
    do
    {
      for ( i = *(char **)(g_ClipsDeferredJoinDriveListHead + 4); i; i = *(char **)(v2 + 28) )
        Rules_DriveJoinNetwork(*(int **)g_ClipsDeferredJoinDriveListHead, i, 0, a1);
      nextEntry = *(_DWORD *)(g_ClipsDeferredJoinDriveListHead + 8);
      g_ClipsMemFreeListTemp = g_ClipsDeferredJoinDriveListHead;
      *(_DWORD *)g_ClipsDeferredJoinDriveListHead = *(_DWORD *)(g_ClipsMemoryTable + 48);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      g_ClipsDeferredJoinDriveListHead = nextEntry;
    }
    while ( nextEntry );
  }
  return result;
}
// 4902EC: variable 'v2' is possibly undefined
// 51A970: using guessed type int dword_51A970;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00490330) --------------------------------------------------------
void Rules_FlushPendingNetworkGarbage()
{
  unsigned int next_parser;
  unsigned int next_fact;
  uintptr_t parser_node;
  uintptr_t parser_bucket;
  unsigned int nested_node;

  while ( g_ReteGarbageAlphaMatchList )
  {
    parser_node = (uintptr_t)(unsigned int)g_ReteGarbageAlphaMatchList;
    next_parser = *(_DWORD *)(parser_node + 8);
    g_ClipsMemFreeListTemp = g_ReteGarbageAlphaMatchList;
    *(_DWORD *)parser_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
    g_ReteGarbageAlphaMatchList = next_parser;
  }
  while ( g_PartialMatchFreeListHead )
  {
    parser_node = (uintptr_t)(unsigned int)g_PartialMatchFreeListHead;
    next_fact = *(_DWORD *)(parser_node + 4);
    if ( (*(_BYTE *)parser_node & 0x10) != 0 && (*(_BYTE *)parser_node & 0x20) == 0 )
    {
      parser_bucket = parser_node + 4 * (((unsigned int)*(_DWORD *)parser_node << 17) >> 23);
      nested_node = *(_DWORD *)(parser_bucket + 4);
      if ( nested_node )
      {
        g_ClipsMemFreeListTemp = nested_node;
        *(_DWORD *)(uintptr_t)nested_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      }
    }
    *(_BYTE *)parser_node &= ~2u;
    Rules_FreePartialMatch((int)parser_node);
    g_PartialMatchFreeListHead = next_fact;
  }
}
// 51A974: using guessed type int dword_51A974;
// 51A978: using guessed type int dword_51A978;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004903E0) --------------------------------------------------------
BOOL  Lexer_AppendCharToPendingToken(int inchar)
{
  int oldLength; // esi

  oldLength = g_Lexer_PendingLineCharIndex;
  g_Lexer_PendingTokenBuffer = (int)Str_AppendCharEscaping(
                        inchar,
                        (char *)g_Lexer_PendingTokenBuffer,
                        (unsigned int *)&g_Lexer_TokenBufferCapacity,
                        &g_Lexer_PendingLineCharIndex,
                        g_Lexer_TokenBufferCapacity + 80);
  return oldLength != g_Lexer_PendingLineCharIndex;
}
// 51A628: using guessed type int dword_51A628;
// 51A980: using guessed type int dword_51A980;
// 51A984: using guessed type int dword_51A984;

//----- (00490430) --------------------------------------------------------
signed int Lexer_ResetPendingTokenBuffer()
{
  signed int result; // eax

  if ( g_Lexer_PendingTokenBuffer )
    result = Mem_SmallBlockFree((_DWORD *)g_Lexer_PendingTokenBuffer, g_Lexer_TokenBufferCapacity);
  g_Lexer_PendingTokenBuffer = 0;
  g_Lexer_TokenBufferCapacity = 0;
  g_Lexer_PendingLineCharIndex = 0;
  return result;
}
// 51A628: using guessed type int dword_51A628;
// 51A980: using guessed type int dword_51A980;
// 51A984: using guessed type int dword_51A984;

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
            theChar = *(_BYTE *)(theString + charIndex++);
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
                  lineChar = *(_BYTE *)(theString + charIndex++);
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
      if ( !depth && *(_BYTE *)(theString + charIndex) )
        break;
    }
    if ( *(_BYTE *)(theString + charIndex) )
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

  theChar = *(unsigned __int8 *)(pos + theString);
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
        theChar = *(unsigned __int8 *)(theString + pos);
      }
      if ( !theChar )
        break;
      ++pos;
      theChar = *(unsigned __int8 *)(theString + pos);
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
  charPtr = (unsigned __int8 *)(theString + pos);
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
  charPtr = (_BYTE *)(theString + pos);
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

  result = Output_Write((int)g_IO_LogicalNameTable_WClips[0], (int)aClips, (int)this);
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
  _DWORD *v13; // ecx
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
  int v26; // [esp+28h] [ebp-8h]

  v26 = a3;
  if ( !result )
    return result;
  IO_OpenStringSource((int)aCommand_2, (const char *)result, 0);
  Parser_NextToken((int)aCommand_2, (int)&tokenType);
  if ( tokenType == 2 || tokenType == 3 || tokenType < 2 || tokenType == 8 )
  {
    IO_CloseStringRouter((int)aCommand_2);
    if ( printResult )
    {
      Rules_PrintAtomValue((int)aStdout, tokenType, tokenValue);
      Output_Write((int)aStdout, (int)asc_504990, v5);
    }
    return 1;
  }
  if ( tokenType != 13 )
  {
    if ( tokenType != 100 )
    {
      Rules_PrintErrorID((int)aCommline, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedACon_0, v15);
      IO_CloseStringRouter((int)aCommand_2);
      return 0;
    }
    Parser_NextToken((int)aCommand_2, (int)&tokenType);
    if ( tokenType == 2 )
    {
      errorFlag = Rules_ParseConstruct();
      if ( errorFlag != -1 )
      {
        IO_CloseStringRouter((int)aCommand_2);
        if ( v9 == 1 )
        {
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aError_1, v8);
          ppBuffer = (char *)Rules_GetPPBuffer();
          Output_WriteLongString((signed int)g_IO_LogicalNameTable_WError[0], ppBuffer);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504990, v11);
        }
        Rules_DestroyPPBuffer();
        return errorFlag;
      }
      g_Rules_EvaluatingTopLevelCommand = 1;
      Parser_ParseFunctionCallExpr((int)aCommand_2, v6);
      g_Rules_EvaluatingTopLevelCommand = 0;
      Parser_FreeLoopContextStack();
      IO_CloseStringRouter((int)aCommand_2);
      if ( v17 )
      {
        g_ClipsCommandEvalInProgress = 1;
        AST_InstallNodeChain(v17);
        Parser_ParseForm(v19, v18, (int)v19, a4);
        AST_DeinstallNodeChain(v20);
        g_ClipsCommandEvalInProgress = 0;
        AST_Free(v21);
        if ( theResult[1] != 105 && printResult )
        {
          Rules_PrintDataObject((int)aStdout, (int)theResult);
          Output_Write((int)aStdout, (int)asc_504990, v22);
        }
        return 1;
      }
    }
    else
    {
      Rules_PrintErrorID((int)aCommline, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAComma, v16);
      IO_CloseStringRouter((int)aCommand_2);
    }
    return 0;
  }
  IO_CloseStringRouter((int)aCommand_2);
  theExpression = (__int16 *)AST_NewNode(tokenType, (int)tokenValue);
  Parser_ParseForm(theExpression, theResult, (int)theExpression, a4);
  g_ClipsMemFreeListTemp = (int)v13;
  *v13 = *(_DWORD *)(g_ClipsMemoryTable + 56);
  *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
  if ( printResult )
  {
    Rules_PrintDataObject((int)aStdout, (int)theResult);
    Output_Write((int)aStdout, (int)asc_504990, v14);
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

  readChar = Lexer_PeekChar((int)aStdin_1, (unsigned int)this);
  inchar = readChar;
  if ( readChar == -1 )
    inchar = 10;
  return Lexer_AppendCharToPendingToken(inchar);
}

//----- (00490BB0) --------------------------------------------------------
int Rules_IsEvaluatingTopLevelCommand()
{
  return g_Rules_EvaluatingTopLevelCommand;
}
// 51A988: using guessed type int dword_51A988;

//----- (00490BC0) --------------------------------------------------------
_DWORD *Rules_InitializeDefrules()
{
  _DWORD *result; // eax

  Rules_RegisterAgendaWatchFlags();
  Rules_RegisterAgendaCommands();
  Rules_RegisterDefruleModuleItem();
  Rules_AddReservedPatternSymbol((int)aAnd_2, 0);
  Rules_AddReservedPatternSymbol((int)aNot_2, 0);
  Rules_AddReservedPatternSymbol((int)aOr_2, 0);
  Rules_AddReservedPatternSymbol((int)aTest, 0);
  Rules_AddReservedPatternSymbol((int)aLogical, 0);
  Rules_AddReservedPatternSymbol((int)aExists, 0);
  Rules_AddReservedPatternSymbol((int)aForall, 0);
  Rules_DefruleCommandDefinitions();
  Rules_RegisterRuleCommands();
  result = Rules_RegisterConstructType(
             (int)aDefrule,
             (int)aDefrules,
             (int)Rules_FindDefruleByName,
             (int)Rules_ParseDefrule,
             (int)Rules_GetConstructNameSymbol,
             (int)Rules_GetModuleConstructListHead,
             (int)Rules_GetConstructOwnerModule,
             (int)Rules_GetNextDefrule,
             (int)Rules_SetConstructNextInModule,
             (int)Rules_IsDefruleDeletable,
             (int)Rules_DeleteDefruleOrAll,
             (int)Rules_FreeDefruleDisjunctChain);
  g_DefruleConstructTypePtr = (int)result;
  return result;
}
// 54E648: using guessed type int dword_54E648;

//----- (00490C80) --------------------------------------------------------
int Rules_RegisterDefruleModuleItem()
{
  int result; // eax

  result = Module_RegisterItem(
             (int)aDefrule,
             (int)Rules_AllocateDefruleModule,
             (int)Rules_JoinNetworkModuleRecord,
             (int)Rules_FreeDefruleModule,
             (int)Rules_WriteJoinHashStructRef,
             (int)Rules_FindDefruleByName);
  g_DefruleConstructClass = result;
  return result;
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490CB0) --------------------------------------------------------
signed int Rules_AllocateDefruleModule()
{
  _DWORD *freeListEntry; // edx
  signed int result; // eax

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 64);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListEntry;
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemFreeListTemp + 12) = 0;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x10);
    *(_DWORD *)(result + 12) = 0;
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
  *(_DWORD *)theItem = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
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
int  Rules_FindDefruleByName(_BYTE *defruleName, int a2)
{
  return Rules_FindConstructByNameGeneric(defruleName, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (00490D50) --------------------------------------------------------
int  Rules_GetNextDefrule(int defrulePtr)
{
  return Class_Enum(defrulePtr, g_DefruleConstructClass);
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490D60) --------------------------------------------------------
BOOL Rules_IsDefruleDeletable()
{
  int v0; // edx
  int theDefrule; // eax

  if ( Rules_IsBloaded() )
    return 0;
  theDefrule = v0;
  if ( v0 )
  {
    while ( *(char *)(theDefrule + 29) >= 0 )
    {
      theDefrule = *(_DWORD *)(theDefrule + 48);
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
      result = (signed int)Rules_CreateEphemeralMultifield(0);
    }
    else
    {
      theDefault[1] = 2;
      result = (signed int)Str_Intern(aNil, (int)theDefault);
    }
    *(_DWORD *)(v6 + 8) = result;
    return result;
  }
  if ( (*constraints & 1) != 0 || (constraintFlags = *constraints, (*constraints & 2) != 0) )
  {
    v7 = Str_Intern(aNil, (int)defaultObj);
    v8 = (int)constraints;
    standardValue = (int)v7;
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
    v19 = Str_Intern(g_Rules_DefaultEmptyStringConstraint, (int)defaultObj);
    v8 = (int)constraints;
    standardValue = (int)v19;
    theType = 3;
    fieldType = 3;
    goto LABEL_9;
  }
  if ( (constraintFlags & 0x10) != 0 )
  {
    zeroInteger = Rules_AddIntegerValue(0);
    v8 = (int)constraints;
    standardValue = (int)zeroInteger;
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
    v21 = Str_Intern(aNil, (int)defaultObj);
    v8 = (int)constraints;
    standardValue = (int)v21;
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
    v12 = Str_Intern(aNil, (int)defaultObj);
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
      v22 = *(_DWORD *)(v14 + 2);
      if ( v22 == g_Clips_NegativeInfinitySymbol )
        fieldCount = g_Clips_NegativeInfinitySymbol ^ v22;
      else
        fieldCount = *(_DWORD *)(v22 + 16);
    }
    else
    {
      fieldCount = 0;
    }
    defaultObj[1] = 4;
    defaultObj[4] = fieldCount - 1;
    defaultObj[3] = 0;
    result = (signed int)Rules_CreateEphemeralMultifield(fieldCount);
    *(_DWORD *)(v17 + 8) = result;
    if ( v16 > 0 )
    {
      result = 6 * v16 - 6;
      do
      {
        *(_WORD *)(*(_DWORD *)(v17 + 8) + result + 14) = fieldType;
        result -= 6;
        --v16;
        *(_DWORD *)(*(_DWORD *)(v17 + 8) + result + 22) = theValue;
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

  theList = *(__int16 **)(theConstraints + 6);
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
    theList = *(__int16 **)(theConstraints + 10);
    if ( *theList != 1 )
    {
      if ( !*theList )
      {
LABEL_11:
        theValue = *(double *)(*(_DWORD *)(theList + 1) + 16);
        _CHP(v8, a4);
        return Rules_AddIntegerValue((int)theValue);
      }
      theList = *(__int16 **)(theConstraints + 14);
      if ( *theList != 1 )
      {
        if ( *theList )
          return (int *)standardValue;
        goto LABEL_11;
      }
    }
    return *(int **)(theList + 1);
  }
  if ( theType )
    return (int *)standardValue;
  theList = *(__int16 **)(theConstraints + 10);
  if ( !*theList )
    return *(int **)(theList + 1);
  if ( *theList != 1 )
  {
    theList = *(__int16 **)(theConstraints + 14);
    if ( !*theList )
      return *(int **)(theList + 1);
    if ( *theList != 1 )
      return (int *)standardValue;
  }
  return (int *)Rules_AddDoubleValue((double)*(int *)(*(_DWORD *)(theList + 1) + 16));
}
// 490F90: could not find valid save-restore pair for esi
// 490FE8: variable 'v8' is possibly undefined

//----- (00491040) --------------------------------------------------------
int  Rules_ParseDefaultAttribute(
        int readSource,
        int multifield,
        int a3,
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
  int v35; // [esp+24h] [ebp-1Ch]
  int v36; // [esp+28h] [ebp-18h]
  int v37; // [esp+2Ch] [ebp-14h]
  _WORD *newItem; // [esp+30h] [ebp-10h]

  v37 = multifield;
  v36 = dynamic;
  v35 = a3;
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
    v23 = v37;
    IO_OutWriteToken(asc_504A98);
    if ( v23 )
      goto LABEL_37;
    if ( !defaultList || *(_DWORD *)(defaultList + 10) )
    {
      *error = 1;
    }
    else
    {
      theConstraint = Rules_BuildLHSNodeFromToken((__int16 *)defaultList);
      theConstraint[1] &= ~0x80u;
      if ( Rules_ConstraintIsUnmatchable(theConstraint) )
        *error = 1;
      AST_DecrementNodeRefCount(v26);
      if ( !*error )
      {
LABEL_37:
        if ( v36 || !v35 || !defaultList )
          return defaultList;
        oldDefaultList = defaultList;
        defaultList = 0;
        do
        {
          Lexer_ErrorRecover(0);
          if ( Parser_ParseForm(v29, v28, (int)v29, a5) )
            *error = 1;
          if ( theValue[1] == 4 && !v37 && !*error )
          {
            Rules_PrintErrorID((int)aDefault_0, 1, 1);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheDefaultValu, v30);
            *error = 1;
LABEL_47:
            exprToFree = (_WORD *)oldDefaultList;
            goto LABEL_9;
          }
          if ( *error )
            goto LABEL_47;
          newExpr = AST_BuildExpressionFromValue(theValue);
          defaultList = AST_AppendNodeList(defaultList, newExpr);
        }
        while ( *(_DWORD *)(v32 + 10) );
        AST_Free(oldDefaultList);
        return defaultList;
      }
    }
    Rules_PrintErrorID((int)aDefault_0, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheDefaultValu, v24);
    AST_Free(defaultList);
    return 0;
  }
  while ( 1 )
  {
    v13 = (_WORD *)Parser_ParseSingleExpression(readSource, (__int16 *)theToken, v11);
    newItem = v13;
    if ( !v13 )
      goto LABEL_10;
    if ( *v13 == 15 || *v13 == 16 )
      break;
    if ( AST_TreeContainsSpecialTag((int)v13, 0) == 1 )
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
  if ( v36 || *newItem == 16 || defaultKind == -1 || defaultList )
  {
    Parser_ReportSyntaxError();
    exprToFree = newItem;
LABEL_9:
    AST_Free((int)exprToFree);
LABEL_10:
    AST_Free(defaultList);
    *error = 1;
    return 0;
  }
  AST_Free((int)newItem);
  Parser_NextToken(readSource, v18);
  if ( theToken[0] != 101 )
  {
    Parser_ReportSyntaxError();
    IO_OutNewline();
    IO_OutWriteToken(asc_504A54);
    IO_OutWriteToken((char *)theToken[2]);
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
signed int Module_InitializeDefmodules()
{
  Module_RegisterDefmoduleCommands();
  Module_CreateMainModule();
  Rules_RegisterConstructType((int)aDefmodule, (int)aDefmodules, 0, (int)Module_ParseDefmoduleConstruct, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_RegisterHostFunction(aGetCurrentModu, 119, (int)aGetcurrentmodu, (int)Module_GetCurrentCommand, (int)a00_0);
  return Rules_RegisterHostFunction(aSetCurrentModu, 119, (int)aSetcurrentmodu, (int)Module_SetCurrentCommand, (int)a11w_0);
}

//----- (00491430) --------------------------------------------------------
int  Module_RegisterItem(int theItem, int allocateFunction, int bloadModuleReference, int freeFunction, int constructsToCModuleReference, int findFunction)
{
  _DWORD *freeListEntry; // edi
  _DWORD *newModuleItem; // eax
  int moduleIndex; // edx

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 128);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = *freeListEntry;
    newModuleItem = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newModuleItem = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
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
    *(_DWORD *)(g_Module_ItemListTail + 28) = newModuleItem;
  else
    g_ModuleItemDescriptorListHead = (int)newModuleItem;
  g_Module_ItemListTail = (int)newModuleItem;
  return newModuleItem[1];
}
// 49145F: variable 'a3' is possibly undefined
// 51A99C: using guessed type int dword_51A99C;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004914D0) --------------------------------------------------------
int Module_GetItemList()
{
  return g_ModuleItemDescriptorListHead;
}
// 51A9BC: using guessed type int dword_51A9BC;

//----- (004914E0) --------------------------------------------------------
int Module_GetItemCount()
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
    if ( !strcmp_(*(_DWORD *)current, moduleItemName) )
      return current;
    current = *(_DWORD *)(current + 28);
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9BC: using guessed type int dword_51A9BC;

//----- (00491520) --------------------------------------------------------
int Module_GetCurrent()
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
        (*(void (__fastcall **)(int))(changeFunction + 4))(oldModule);
        changeFunction = *(_DWORD *)(v3 + 12);
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

