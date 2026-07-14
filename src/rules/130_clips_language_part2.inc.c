/* CLIPS lexer, parser, expressions, and procedural language support, continued.
 * Original function-marker range: 0x00481720..0x00491530.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00481720) --------------------------------------------------------
double  Rules_CoerceFormToNumericArg(__int16 *a1, int a2, _DWORD *a3, double result, int a5)
{
  unsigned int v5; // edx
  int v6; // eax

  if ( (unsigned __int16)*a1 > 1u )
  {
    Parser_ParseForm(a1, a3, a2, result);
    v5 = a3[1];
    v6 = a3[2];
  }
  else
  {
    v5 = *a1;
    v6 = *(_DWORD *)(a1 + 1);
  }
  if ( v5 > 1 )
  {
    Parser_ReportError(a5, (int)aIntegerOrFlo_0);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    a3[1] = 1;
    a3[2] = Rules_AddIntegerValue(0);
  }
  else
  {
    if ( a2 )
    {
      if ( v5 == 1 )
        v6 = Rules_AddDoubleValue((double)*(int *)(v6 + 16));
    }
    a3[1] = v5;
    a3[2] = v6;
  }
  return result;
}
// 48173C: simplified comparisons for 'edx.4': !=0 && !=1 became >=2u
// 48172C: simplified comparisons for '[ds.2:eax.4].2': !=0 && !=1 became >=2u
// 481745: variable 'a2' is possibly undefined
// 48175C: variable 'v5' is possibly undefined

//----- (004817C0) --------------------------------------------------------
int  Rules_GetLogicalNameArg(int a1, int a2, int a3, double a4)
{
  int v5; // ecx
  int v6; // ecx
  char *v8; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ecx
  int v12; // [esp-4h] [ebp-20h] BYREF
  int v13; // [esp+0h] [ebp-1Ch]
  int v14; // [esp+4h] [ebp-18h]
  int v15; // [esp+14h] [ebp-8h]

  v15 = a3;
  Rules_RtnUnknown(a1, &v12, a4);
  if ( v13 == 2 || v13 == 3 || v13 == 8 )
  {
    if ( !strcmp_(*(_DWORD *)(v14 + 16), aT) || !strcmp_(v5, aT_0) )
      return a2;
    return v6;
  }
  else if ( v13 )
  {
    if ( v13 == 1 )
    {
      v10 = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(v14 + 16));
      return Str_Intern(v10, v11)[4];
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v8 = (char *)Rules_FloatToSymbol(*(_DWORD *)(v14 + 16), *(double *)(v14 + 16));
    return Str_Intern(v8, v9)[4];
  }
}
// 4817FA: variable 'v6' is possibly undefined
// 481809: variable 'v5' is possibly undefined
// 481838: variable 'v9' is possibly undefined
// 481854: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (00481870) --------------------------------------------------------
int  Rules_GetFileNameArg(int a1, int a2, double a3)
{
  int v3; // ecx
  int v5; // [esp-4h] [ebp-20h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+4h] [ebp-18h]
  int v8; // [esp+18h] [ebp-4h]

  v8 = a2;
  Rules_RtnUnknown(a1, &v5, a3);
  if ( v6 == 3 || v6 == 2 )
    return *(_DWORD *)(v7 + 16);
  Parser_ReportError(v3, (int)aFileName);
  return 0;
}
// 4818A7: variable 'v3' is possibly undefined

//----- (004818C0) --------------------------------------------------------
signed int __fastcall Rules_OpenFileErrorMessage(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_FileError, v7);
}
// 4818E2: variable 'v3' is possibly undefined
// 4818EE: variable 'v4' is possibly undefined
// 4818FD: variable 'v5' is possibly undefined
// 481909: variable 'v6' is possibly undefined
// 481918: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481930) --------------------------------------------------------
int * Rules_GetModuleNameArg(int a1, int a2, _DWORD *a3, double a4)
{
  int v4; // ecx
  int *result; // eax
  int v6; // ecx
  _DWORD v7[2]; // [esp-4h] [ebp-24h] BYREF
  int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+1Ch] [ebp-4h]

  v9 = a2;
  *a3 = 0;
  Rules_RtnUnknown(a1, v7, a4);
  if ( v7[1] == 2 )
  {
    result = Module_FindByName(*(_BYTE **)(v8 + 16));
    if ( !result )
    {
      if ( strcmp_(v6, *(_DWORD *)(v8 + 16)) )
      {
        Parser_ReportError(1, (int)aDefmoduleNam_0);
        *a3 = 1;
      }
      return 0;
    }
  }
  else
  {
    Parser_ReportError(v4, (int)aDefmoduleNam_0);
    *a3 = 1;
    return 0;
  }
  return result;
}
// 481972: variable 'v4' is possibly undefined
// 48198D: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004819C0) --------------------------------------------------------
int  Rules_GetConstructNameArg(int a1, int a2, double a3)
{
  int v4; // ecx
  _DWORD v6[8]; // [esp-4h] [ebp-20h] BYREF

  v6[6] = a2;
  if ( Rules_RtnArgCount() == 1 )
  {
    Rules_RtnUnknown(1, v6, a3);
    if ( v6[1] == 2 )
    {
      return *(_DWORD *)(v6[2] + 16);
    }
    else
    {
      Parser_ReportError(1, a1);
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
signed int  Rules_NonexistentArgError(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument, v7);
  Rules_PrintLongInteger(v8, a2);
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
signed int  Rules_ExpectedCountError(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *v6; // edx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)aArgacces, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v4);
  if ( v5 )
  {
    if ( v5 == 1 )
    {
      v6 = aExpectedAtLeas;
    }
    else if ( v5 == 2 )
    {
      v6 = aExpectedNoMore;
    }
    else
    {
      v6 = aGeneratedAnIll;
    }
  }
  else
  {
    v6 = aExpectedExactl;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v6, v5);
  Rules_PrintLongInteger(v7, a2);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArgumentS, v8);
}
// 481AC4: variable 'v3' is possibly undefined
// 481AD0: variable 'v4' is possibly undefined
// 481AD7: variable 'v5' is possibly undefined
// 481AF9: variable 'v7' is possibly undefined
// 481B08: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00481B30) --------------------------------------------------------
signed int  Rules_CheckFunctionArgCount(int a1, _BYTE *a2, int a3)
{
  int v3; // ecx
  int v5; // ebx
  int v6; // eax

  v3 = a1;
  if ( !a2 )
    return 1;
  if ( (IsTable[(unsigned __int8)(*a2 + 1)] & 0x20) != 0 )
    v5 = atoi_(a1);
  else
    v5 = -1;
  if ( (IsTable[(unsigned __int8)(a2[1] + 1)] & 0x20) != 0 )
    v6 = atoi_(v3);
  else
    v6 = 10000;
  if ( v5 == v6 )
  {
    if ( a3 == v6 )
      return 1;
    goto LABEL_15;
  }
  if ( a3 < v5 )
  {
LABEL_15:
    Rules_ExpectedCountError(v3, v5);
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( a3 <= v6 )
    return 1;
  Rules_ExpectedCountError(v3, v6);
  Lexer_ErrorRecover(1);
  return 0;
}
// 481B5F: variable 'a2' is possibly undefined
// 481B7A: variable 'v3' is possibly undefined
// 48523F: using guessed type int __thiscall unknown_libname_2(_DWORD);

//----- (00481C20) --------------------------------------------------------
signed int  Parser_ReportError(int a1, int a2)
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
  Rules_PrintLongInteger(v6, a1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aToBeOfType, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v8);
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
int ** Rules_ReportSymbolTypeError(_BYTE *a1, int a2)
{
  int **result; // eax
  int v4; // edx
  char v5; // al
  char *v6; // eax

  result = Rules_MakeSymbol(a1);
  if ( result )
  {
    v5 = Rules_GetArgRestrictionType((int)result, v4);
    v6 = Rules_GetArgTypeName(v5);
    return (int **)Parser_ReportError(a2, (int)v6);
  }
  return result;
}
// 481CB3: variable 'v4' is possibly undefined

//----- (00481CD0) --------------------------------------------------------
signed int  Rules_ExpectedTypeError(int a1, int a2, int a3)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReceivedAReque, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument, v9);
  Rules_PrintLongInteger(v10, a3);
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
signed int * Str_Intern(char *a1, int a2)
{
  char *v2; // esi
  int v3; // ebx
  signed int v4; // ecx
  int v6; // edx
  signed int v7; // eax
  int v8; // ebp
  int v9; // eax
  __int16 v10; // dx
  char *v11; // edi
  char v12; // al
  char v13; // al
  int v15; // [esp+0h] [ebp-18h]

  v2 = a1;
  v3 = 0;
  if ( !a1 )
  {
    Rules_ReportSystemError(a2, 1);
    IO_RunRouterExitCallbacks();
  }
  v15 = Rules_HashSymbolName(v2, 0x3F5u);
  v4 = *(_DWORD *)((uintptr_t)(unsigned int)g_Clips_SymbolHashTable + 4 * v15);
  if ( v4 )
  {
    while ( strcmp(v2, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)v4 + 16)) )
    {
      v3 = v4;
      v4 = *(_DWORD *)(uintptr_t)(unsigned int)v4;
      if ( !v4 )
        goto LABEL_6;
    }
    return (signed int *)(uintptr_t)(unsigned int)v4;
  }
  else
  {
LABEL_6:
    v6 = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80);
    if ( v6 )
    {
      g_ClipsMemFreeListTemp = v6;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80) = *(_DWORD *)(uintptr_t)(unsigned int)v6;
      v7 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v7 = Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    v8 = v7;
    if ( v3 )
      *(_DWORD *)(uintptr_t)(unsigned int)v3 = v7;
    else
      *(_DWORD *)((uintptr_t)(unsigned int)g_Clips_SymbolHashTable + 4 * v15) = v7;
    v9 = (int)(uintptr_t)Mem_SmallBlockAlloc(strlen(v2) + 1);
    *(_DWORD *)(uintptr_t)(unsigned int)v8 = 0;
    *(_DWORD *)((uintptr_t)(unsigned int)v8 + 4) = 0;
    v10 = *(_WORD *)((uintptr_t)(unsigned int)v8 + 12);
    *(_DWORD *)((uintptr_t)(unsigned int)v8 + 16) = v9;
    *(_WORD *)((uintptr_t)(unsigned int)v8 + 12) = v10 & 3;
    v11 = (char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)v8 + 16);
    *(_DWORD *)((uintptr_t)(unsigned int)v8 + 12) |= 4 * (v15 & 0x3FFF);
    do
    {
      v12 = *v2;
      *v11 = *v2;
      if ( !v12 )
        break;
      v13 = v2[1];
      v2 += 2;
      v11[1] = v13;
      v11 += 2;
    }
    while ( v13 );
    Rules_AddEphemeralHashNode(v8, &g_Rules_EphemeralSymbolListHead, 10, 20);
    *(_DWORD *)((uintptr_t)(unsigned int)v8 + 8) = g_ClipsCurrentEvaluationDepth;
    return (signed int *)(uintptr_t)(unsigned int)v8;
  }
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A268: using guessed type _DWORD dword_51A268;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD50: using guessed type int dword_54DD50;

//----- (00481EC0) --------------------------------------------------------
int * Rules_FindSymbolEntry(_BYTE *a1)
{
  int trace_load_save; // eax
  int bucket_index; // eax
  int bucket_entry; // ecx

  trace_load_save = 0;
  if ( !g_Clips_SymbolHashTable )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] symbol-lookup-missing-table %s\n", a1);
    return 0;
  }
  bucket_index = Rules_HashSymbolName(a1, 0x3F5u);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] symbol-lookup table=%08x bucket=%d key=%s\n", g_Clips_SymbolHashTable, bucket_index, a1);
  bucket_entry = *(_DWORD *)(g_Clips_SymbolHashTable + 4 * bucket_index);
  while ( bucket_entry )
  {
    if ( !strcmp_((int)a1, *(_DWORD *)(bucket_entry + 16)) )
      return (int *)bucket_entry;
    bucket_entry = *(_DWORD *)bucket_entry;
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD50: using guessed type int dword_54DD50;

//----- (00481F00) --------------------------------------------------------
int __stdcall Rules_AddDoubleValue(double a1)
{
  unsigned int v1; // ebx
  signed int v2; // edx
  signed int *v3; // ecx
  _DWORD *v4; // esi
  signed int v5; // eax
  signed int v6; // esi
  __int16 v7; // dx

  v1 = Rules_HashDoubleValue(LODWORD(a1), SHIDWORD(a1), 0x1F7u);
  v2 = *(_DWORD *)(4 * v1 + g_ClipsFloatHashTable);
  v3 = 0;
  if ( v2 )
  {
    while ( a1 != *(double *)(v2 + 16) )
    {
      v3 = (signed int *)v2;
      v2 = *(_DWORD *)v2;
      if ( !v2 )
        goto LABEL_4;
    }
    return v2;
  }
  else
  {
LABEL_4:
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *v4;
      v5 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    v6 = v5;
    if ( v3 )
      *v3 = v5;
    else
      *(_DWORD *)(g_ClipsFloatHashTable + 4 * v1) = v5;
    *(_DWORD *)v5 = 0;
    v7 = *(_WORD *)(v5 + 12);
    *(_DWORD *)(v5 + 4) = 0;
    *(double *)(v5 + 16) = a1;
    *(_WORD *)(v5 + 12) = v7 & 3;
    *(_DWORD *)(v5 + 12) |= 4 * (v1 & 0x3FFF);
    Rules_AddEphemeralHashNode(v5, &g_Rules_EphemeralFloatListHead, 0, 24);
    *(_DWORD *)(v6 + 8) = g_ClipsCurrentEvaluationDepth;
    return v6;
  }
}
// 481F66: variable 'v3' is possibly undefined
// 51A26C: using guessed type _DWORD dword_51A26C;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD58: using guessed type int dword_54DD58;

//----- (00482000) --------------------------------------------------------
int  Rules_AddIntegerValue(int a1)
{
  int bucket_index; // edx
  int node; // eax
  int previous_node; // ecx
  int free_node; // esi
  int new_node; // eax
  __int16 flags; // bx

  bucket_index = Rules_HashIntegerValue(a1, 167);
  node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsIntegerHashTable + 4 * bucket_index);
  previous_node = 0;
  while ( node )
  {
    if ( a1 == *(_DWORD *)((uintptr_t)(unsigned int)node + 16) )
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
  *(_DWORD *)((uintptr_t)(unsigned int)new_node + 16) = a1;
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
int * Rules_FindIntegerValue(signed int a1)
{
  int *result; // eax
  int v2; // ecx

  result = *(int **)(g_ClipsIntegerHashTable + 4 * Rules_HashIntegerValue(a1, 167));
  if ( !result )
    return 0;
  while ( v2 != result[4] )
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
int  Rules_AddBitmapValue(_BYTE *a1, signed int a2)
{
  int v4; // eax
  signed int *v5; // ecx
  int v6; // edi
  int v7; // eax
  signed int v8; // eax
  _BYTE *v9; // edx
  int v10; // ecx
  int free_node; // edx
  signed int v12; // eax
  _DWORD *v13; // eax
  __int16 v14; // dx
  int v15; // ecx
  signed int v16; // eax
  char *v17; // edx
  char v18; // bl
  int v20; // [esp+0h] [ebp-18h]

  if ( !a1 )
  {
    Rules_ReportSystemError(0, 2);
    IO_RunRouterExitCallbacks();
  }
  v4 = Rules_HashBitmapValue((int)a1, 0xA7u, a2);
  v6 = *(_DWORD *)(g_ClipsBitmapHashTable + 4 * v4);
  v5 = 0;
  v20 = v4;
  if ( v6 )
  {
    while ( 1 )
    {
      v7 = *(unsigned __int16 *)(v6 + 20);
      if ( (unsigned __int16)v7 == a2 )
      {
        v8 = a2 ^ v7;
        if ( a2 > 0 )
        {
          v9 = a1;
          v10 = *(_DWORD *)(v6 + 16);
          do
          {
            if ( *(_BYTE *)v10 != *v9 )
              break;
            ++v9;
            ++v8;
            ++v10;
          }
          while ( v8 < a2 );
        }
        if ( v8 == a2 )
          break;
      }
      v5 = (signed int *)v6;
      v6 = *(_DWORD *)v6;
      if ( !v6 )
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
      v12 = g_ClipsMemFreeListTemp;
    }
    else
    {
      v12 = Mem_HeapAllocWithRetry((_DWORD *)0x16);
    }
    v6 = v12;
    if ( v5 )
      *v5 = v12;
    else
      *(_DWORD *)(g_ClipsBitmapHashTable + 4 * v20) = v12;
    v13 = Mem_SmallBlockAlloc(a2);
    *(_DWORD *)v6 = 0;
    *(_DWORD *)(v6 + 4) = 0;
    v14 = *(_WORD *)(v6 + 12);
    *(_DWORD *)(v6 + 16) = v13;
    *(_WORD *)(v6 + 12) = v14 & 3;
    v15 = *(_DWORD *)(v6 + 12);
    *(_WORD *)(v6 + 20) = a2;
    v16 = 0;
    *(_DWORD *)(v6 + 12) = (4 * (v20 & 0x3FFF)) | v15;
    if ( a2 > 0 )
    {
      v17 = a1;
      do
      {
        ++v16;
        v18 = *v17++;
        *(_BYTE *)(*(_DWORD *)(v6 + 16) + v16 - 1) = v18;
      }
      while ( v16 < a2 );
    }
    Rules_AddEphemeralHashNode(v6, &g_Rules_EphemeralBitmapListHead, 4, 22);
    *(_DWORD *)(v6 + 8) = g_ClipsCurrentEvaluationDepth;
  }
  return v6;
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
int  Rules_HashSymbolName(_BYTE *a1, unsigned int a2)
{
  _BYTE *v2; // edi
  unsigned int v3; // ebp
  char v4; // dh
  int v5; // ecx
  signed int v6; // ebp
  int *v7; // eax
  char *v8; // edx
  int *v9; // esi
  char v10; // bl
  char *v11; // edi
  int *v12; // eax
  char v13; // dl
  signed int v14; // edx
  int v16; // [esp+0h] [ebp-28h] BYREF
  unsigned int v17; // [esp+4h] [ebp-24h]
  int *v18; // [esp+8h] [ebp-20h]
  int v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]

  v2 = a1;
  v17 = a2;
  v3 = 0;
  v19 = 0;
  v18 = &v16;
  if ( *a1 )
  {
    do
    {
      v4 = *++a1;
      ++v3;
    }
    while ( v4 );
  }
  v5 = 0;
  v6 = v3 >> 2;
  v20 = 0;
  if ( v6 )
  {
    do
    {
      v7 = v18;
      v8 = &v2[v5];
      v9 = v18 + 1;
      do
      {
        v7 = (int *)((char *)v7 + 1);
        v10 = *v8++;
        ++v5;
        *((_BYTE *)v7 - 1) = v10;
      }
      while ( v7 != v9 );
      v19 += v16;
      ++v20;
    }
    while ( v6 > v20 );
  }
  v11 = &v2[v5];
  v16 = 0;
  if ( *v11 )
  {
    v12 = v18;
    do
    {
      v13 = *v11++;
      *(_BYTE *)v12 = v13;
      v12 = (int *)((char *)v12 + 1);
    }
    while ( *v11 );
  }
  v14 = (v16 + v19) % v17;
  v19 += v16;
  if ( v14 < 0 )
    return -v14;
  else
    return v14;
}

//----- (00482440) --------------------------------------------------------
unsigned int __stdcall Rules_HashDoubleValue(unsigned int a1, int a2, unsigned int a3)
{
  if ( ((a1 % a3) & 0x80000000) != 0 )
    return -(a1 % a3);
  else
    return a1 % a3;
}

//----- (00482480) --------------------------------------------------------
int  Rules_HashIntegerValue(signed int a1, signed int a2)
{
  int v2; // edx

  v2 = a1 % a2;
  if ( v2 < 0 )
    return -v2;
  else
    return v2;
}

//----- (004824A0) --------------------------------------------------------
int  Rules_HashBitmapValue(int a1, unsigned int a2, unsigned int a3)
{
  unsigned int v3; // edi
  signed int v4; // ebp
  signed int v5; // ecx
  int *v6; // eax
  int *v7; // esi
  char *v8; // edx
  char v9; // bl
  int v10; // eax
  int v11; // edx
  int v13; // [esp+0h] [ebp-28h] BYREF
  unsigned int v14; // [esp+4h] [ebp-24h]
  int v15; // [esp+8h] [ebp-20h]
  signed int v16; // [esp+Ch] [ebp-1Ch]
  signed int v17; // [esp+10h] [ebp-18h]
  int *v18; // [esp+14h] [ebp-14h]

  v15 = a1;
  v14 = a2;
  v16 = a3;
  v3 = 0;
  v18 = &v13;
  v4 = 0;
  v5 = 0;
  v17 = a3 >> 2;
  if ( a3 >> 2 )
  {
    do
    {
      v6 = v18;
      v7 = v18 + 1;
      v8 = (char *)(v5 + v15);
      do
      {
        v6 = (int *)((char *)v6 + 1);
        v9 = *v8++;
        ++v5;
        *((_BYTE *)v6 - 1) = v9;
      }
      while ( v6 != v7 );
      ++v4;
      v3 += v13;
    }
    while ( v4 < v17 );
  }
  v10 = v5 + v15;
  while ( v5 < v16 )
  {
    ++v10;
    ++v5;
    v3 += *(unsigned __int8 *)(v10 - 1);
  }
  v11 = v3 % v14;
  if ( ((v3 % v14) & 0x80000000) != 0 )
    return -v11;
  return v11;
}
// 4824A0: could not find valid save-restore pair for ebx

//----- (00482530) --------------------------------------------------------
int  Rules_DecrementSymbolCount(int result, int a2)
{
  int v2; // esi
  int v3; // ebx

  v2 = result;
  if ( *(int *)(result + 4) < 0 )
  {
    Rules_ReportSystemError(a2, 3);
    result = IO_RunRouterExitCallbacks();
  }
  if ( !*(_DWORD *)(v2 + 4) )
  {
    Rules_ReportSystemError(a2, 4);
    result = IO_RunRouterExitCallbacks();
  }
  v3 = *(_DWORD *)(v2 + 4) - 1;
  *(_DWORD *)(v2 + 4) = v3;
  if ( !v3 && (*(_BYTE *)(v2 + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(v2, &g_Rules_EphemeralSymbolListHead, 10, 20);
  return result;
}
// 48254B: variable 'a2' is possibly undefined
// 51A268: using guessed type _DWORD dword_51A268;

//----- (004825B0) --------------------------------------------------------
int  Rules_DecrementFloatCount(int result, int a2)
{
  int v2; // esi
  int v3; // ecx

  v2 = result;
  if ( *(int *)(result + 4) <= 0 )
  {
    Rules_ReportSystemError(a2, 5);
    result = IO_RunRouterExitCallbacks();
  }
  v3 = *(_DWORD *)(v2 + 4) - 1;
  *(_DWORD *)(v2 + 4) = v3;
  if ( !v3 && (*(_BYTE *)(v2 + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(v2, &g_Rules_EphemeralFloatListHead, 0, 24);
  return result;
}
// 51A26C: using guessed type _DWORD dword_51A26C;

//----- (00482600) --------------------------------------------------------
int  Rules_DecrementIntegerCount(int result, int a2)
{
  int v2; // esi
  int v3; // ecx

  v2 = result;
  if ( *(int *)(result + 4) <= 0 )
  {
    Rules_ReportSystemError(a2, 6);
    result = IO_RunRouterExitCallbacks();
  }
  v3 = *(_DWORD *)(v2 + 4) - 1;
  *(_DWORD *)(v2 + 4) = v3;
  if ( !v3 && (*(_BYTE *)(v2 + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(v2, &g_Rules_EphemeralIntegerListHead, 0, 20);
  return result;
}
// 51A270: using guessed type _DWORD dword_51A270;

//----- (00482650) --------------------------------------------------------
int  Rules_DecrementBitmapCount(int result, int a2)
{
  int v2; // esi
  int v3; // ebx

  v2 = result;
  if ( *(int *)(result + 4) < 0 )
  {
    Rules_ReportSystemError(a2, 7);
    result = IO_RunRouterExitCallbacks();
  }
  if ( !*(_DWORD *)(v2 + 4) )
  {
    Rules_ReportSystemError(a2, 8);
    result = IO_RunRouterExitCallbacks();
  }
  v3 = *(_DWORD *)(v2 + 4) - 1;
  *(_DWORD *)(v2 + 4) = v3;
  if ( !v3 && (*(_BYTE *)(v2 + 12) & 1) == 0 )
    return Rules_AddEphemeralHashNode(v2, &g_Rules_EphemeralBitmapListHead, 4, 22);
  return result;
}
// 48266B: variable 'a2' is possibly undefined
// 51A274: using guessed type _DWORD dword_51A274;

//----- (004826D0) --------------------------------------------------------
_DWORD * Rules_RemoveHashNode(int a1, int a2, int a3, int a4)
{
  _DWORD *v7; // ecx
  _DWORD *v8; // edi
  _DWORD *result; // eax

  v7 = *(_DWORD **)(a2 + 4 * (*(_DWORD *)(a1 + 12) << 16 >> 18));
  v8 = 0;
  while ( v7 != (_DWORD *)a1 )
  {
    v8 = v7;
    v7 = (_DWORD *)*v7;
    if ( !v7 )
    {
      Rules_ReportSystemError(0, 9);
      IO_RunRouterExitCallbacks();
    }
  }
  if ( v8 )
    *v8 = *v7;
  else
    *(_DWORD *)(4 * (*(_DWORD *)(a1 + 12) << 16 >> 18) + a2) = *(_DWORD *)a1;
  if ( a3 == 2 )
  {
    Mem_SmallBlockFree(*(_DWORD **)(a1 + 16), strlen(*(const char **)(a1 + 16)) + 1);
  }
  else if ( a3 == 19 )
  {
    Mem_SmallBlockFree(*(_DWORD **)(a1 + 16), *(unsigned __int16 *)(a1 + 20));
  }
  g_ClipsMemFreeListTemp = a1;
  *(_DWORD *)a1 = *(_DWORD *)(g_ClipsMemoryTable + 4 * a4);
  result = (_DWORD *)(g_ClipsMemoryTable + 4 * a4);
  *result = g_ClipsMemFreeListTemp;
  return result;
}
// 4826FA: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004827B0) --------------------------------------------------------
int  Rules_AddEphemeralHashNode(int a1, _DWORD *a2, int a3, int a4)
{
  int free_node; // ebp
  int link_node; // eax
  int result; // eax

  if ( *(_DWORD *)(a1 + 4) )
  {
    Rules_ReportSystemError(a3, 10);
    IO_RunRouterExitCallbacks();
  }
  *(_BYTE *)(a1 + 12) |= 1u;
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
  *(_DWORD *)link_node = a1;
  *(_DWORD *)(link_node + 4) = *a2;
  *a2 = link_node;
  result = ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += a4 + 8 + a3;
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
int  Rules_RemoveEphemeralHashNodes(uintptr_t result, uintptr_t a2, int a3, int a4, int a5)
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
    node_charge = a4 + 8 + a5;
    do
    {
      object = (uintptr_t)(unsigned int)*(_DWORD *)node;
      next = (uintptr_t)(unsigned int)*(_DWORD *)(node + 4);
      if ( !*(_DWORD *)(object + 4) && g_ClipsCurrentEvaluationDepth < *(_DWORD *)(object + 8) )
      {
        Rules_RemoveHashNode((int)object, (int)a2, a3, a4);
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
  return a4 + 8 + a5;
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
int  Mem_AllocArray(_BYTE *a1, int a2)
{
  int result; // eax
  _BYTE *v5; // edx

  result = 0;
  if ( a2 > 0 )
  {
    v5 = a1;
    do
    {
      ++result;
      *v5++ = 0;
    }
    while ( result < a2 );
  }
  return result;
}

//----- (00482BB0) --------------------------------------------------------
int ** Rules_GetNextSymbolMatch(int **a1, int a2, int a3, int ***a4, int *a5)
{
  int **v8; // ebx
  int *v9; // eax
  int v10; // eax
  int **v11; // eax
  int v12; // eax
  int v14; // edx
  int v15; // [esp+0h] [ebp-1Ch]
  int v16; // [esp+8h] [ebp-14h]

  if ( a3 && a5 )
    *a5 = 0;
  if ( a4 )
  {
    v10 = (_DWORD)a4[3] << 16 >> 18;
    v8 = *a4;
    v16 = v10;
  }
  else
  {
    v16 = 0;
    v8 = *(int ***)g_Clips_SymbolHashTable;
  }
  v15 = 4 * v16;
  while ( 1 )
  {
    while ( !v8 )
    {
      v14 = v15 + 4;
      v15 = v14;
      ++v16;
      if ( v14 >= 4052 )
        return 0;
      v8 = *(int ***)(v14 + g_Clips_SymbolHashTable);
    }
    v9 = v8[4];
    if ( *(_BYTE *)v9 != 40 && ((_BYTE)v8[3] & 1) == 0 )
      break;
LABEL_9:
    v8 = (int **)*v8;
  }
  if ( a3 )
  {
    if ( Rules_StringWithinString(v9, a1) )
      return v8;
    goto LABEL_9;
  }
  if ( a4 )
    v11 = a4[4];
  else
    v11 = a1;
  v12 = Rules_CommonPrefixLength(v11, v8[4]);
  if ( v12 < a2 )
    goto LABEL_9;
  if ( a5 )
  {
    if ( a4 )
    {
      if ( v12 < *a5 )
        *a5 = v12;
    }
    else
    {
      *a5 = strlen((const char *)v8[4]);
    }
  }
  return v8;
}
// 482BFD: conditional instruction was optimized away because %var_18.4==1
// 54DD50: using guessed type int dword_54DD50;

//----- (00482CD0) --------------------------------------------------------
_BYTE * Rules_StringWithinString(_BYTE *a1, _BYTE *a2)
{
  _BYTE *v3; // ebp
  int v4; // esi
  _BYTE *v5; // eax
  int v6; // ecx
  _BYTE *v7; // edx
  char v8; // bh
  char v9; // dh

  v3 = a1;
  v4 = 0;
  if ( !*a1 )
    return 0;
  while ( 1 )
  {
    v5 = a2;
    v6 = 0;
    v7 = &a1[v4];
    if ( *a2 )
    {
      do
      {
        if ( *v7 != *v5 )
          break;
        ++v7;
        v8 = *++v5;
        ++v6;
      }
      while ( v8 );
    }
    if ( !a2[v6] && v6 )
      break;
    v9 = *++v3;
    ++v4;
    if ( !v9 )
      return 0;
  }
  return &a1[v4];
}

//----- (00482D40) --------------------------------------------------------
int  Rules_CommonPrefixLength(_BYTE *a1, _BYTE *a2)
{
  int v2; // ecx
  char v3; // bl

  v2 = 0;
  if ( *a1 )
  {
    do
    {
      if ( !*a2 )
        break;
      if ( *a2 != *a1 )
        break;
      ++a2;
      v3 = *++a1;
      ++v2;
    }
    while ( v3 );
  }
  return v2;
}

//----- (00482D70) --------------------------------------------------------
int  Rules_SetAtomicValueIndices(int a1)
{
  int v2; // ecx
  int **v3; // esi
  int v4; // edi
  int *i; // eax
  int v6; // ebp
  int v7; // ecx
  int **v8; // esi
  int v9; // edi
  int *j; // eax
  int v11; // ebp
  int v12; // ecx
  int **v13; // esi
  int v14; // edi
  int *k; // eax
  int v16; // ebp
  int v17; // ecx
  int *v18; // esi
  int v19; // edi
  int result; // eax
  int v21; // ebp

  v2 = 0;
  v3 = (int **)g_Clips_SymbolHashTable;
  v4 = g_Clips_SymbolHashTable + 4052;
  do
  {
    for ( i = *v3; i; i = (int *)*i )
    {
      if ( (i[3] & 2) != 0 || a1 )
      {
        *((_BYTE *)i + 13) = 0;
        *((_BYTE *)i + 12) &= 3u;
        v6 = (4 * (v2++ & 0x3FFF)) | i[3];
        i[3] = v6;
      }
    }
    ++v3;
  }
  while ( v3 != (int **)v4 );
  v7 = 0;
  v8 = (int **)g_ClipsFloatHashTable;
  v9 = g_ClipsFloatHashTable + 2012;
  do
  {
    for ( j = *v8; j; j = (int *)*j )
    {
      if ( (j[3] & 2) != 0 || a1 )
      {
        *((_BYTE *)j + 13) = 0;
        *((_BYTE *)j + 12) &= 3u;
        v11 = (4 * (v7++ & 0x3FFF)) | j[3];
        j[3] = v11;
      }
    }
    ++v8;
  }
  while ( v8 != (int **)v9 );
  v12 = 0;
  v13 = (int **)g_ClipsIntegerHashTable;
  v14 = g_ClipsIntegerHashTable + 668;
  do
  {
    for ( k = *v13; k; k = (int *)*k )
    {
      if ( (k[3] & 2) != 0 || a1 )
      {
        *((_BYTE *)k + 13) = 0;
        *((_BYTE *)k + 12) &= 3u;
        v16 = (4 * (v12++ & 0x3FFF)) | k[3];
        k[3] = v16;
      }
    }
    ++v13;
  }
  while ( v13 != (int **)v14 );
  v17 = 0;
  v18 = (int *)g_ClipsBitmapHashTable;
  v19 = g_ClipsBitmapHashTable + 668;
  do
  {
    for ( result = *v18; result; result = *(_DWORD *)result )
    {
      if ( (*(_BYTE *)(result + 12) & 2) != 0 || a1 )
      {
        *(_BYTE *)(result + 13) = 0;
        *(_BYTE *)(result + 12) &= 3u;
        v21 = (4 * (v17++ & 0x3FFF)) | *(_DWORD *)(result + 12);
        *(_DWORD *)(result + 12) = v21;
      }
    }
    ++v18;
  }
  while ( v18 != (int *)v19 );
  return result;
}
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00482EF0) --------------------------------------------------------
int *Rules_RestoreAtomicValueBuckets()
{
  _DWORD *v0; // ebx
  int i; // ecx
  _DWORD *v2; // eax
  unsigned int v3; // ebp
  _DWORD *v4; // ebx
  int j; // ecx
  _DWORD *v6; // eax
  unsigned int v7; // ebp
  _DWORD *v8; // ebx
  int k; // ecx
  _DWORD *v10; // eax
  unsigned int v11; // ebp
  int *v12; // ebx
  int m; // ecx
  int *result; // eax
  unsigned int v15; // ebp

  v0 = (_DWORD *)g_Clips_SymbolHashTable;
  for ( i = 0; i < 1013; ++i )
  {
    v2 = (_DWORD *)*v0;
    if ( *v0 )
    {
      do
      {
        v3 = v2[3] & 0xFFFF0003;
        v2[3] = v3;
        v2[3] = (4 * (i & 0x3FFF)) | v3;
        v2 = (_DWORD *)*v2;
      }
      while ( v2 );
    }
    ++v0;
  }
  v4 = (_DWORD *)g_ClipsFloatHashTable;
  for ( j = 0; j < 503; ++j )
  {
    v6 = (_DWORD *)*v4;
    if ( *v4 )
    {
      do
      {
        v7 = v6[3] & 0xFFFF0003;
        v6[3] = v7;
        v6[3] = (4 * (j & 0x3FFF)) | v7;
        v6 = (_DWORD *)*v6;
      }
      while ( v6 );
    }
    ++v4;
  }
  v8 = (_DWORD *)g_ClipsIntegerHashTable;
  for ( k = 0; k < 167; ++k )
  {
    v10 = (_DWORD *)*v8;
    if ( *v8 )
    {
      do
      {
        v11 = v10[3] & 0xFFFF0003;
        v10[3] = v11;
        v10[3] = (4 * (k & 0x3FFF)) | v11;
        v10 = (_DWORD *)*v10;
      }
      while ( v10 );
    }
    ++v8;
  }
  v12 = (int *)g_ClipsBitmapHashTable;
  for ( m = 0; m < 167; ++m )
  {
    result = (int *)*v12;
    if ( *v12 )
    {
      do
      {
        v15 = result[3] & 0xFFFF0003;
        result[3] = v15;
        result[3] = (4 * (m & 0x3FFF)) | v15;
        result = (int *)*result;
      }
      while ( result );
    }
    ++v12;
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
unsigned int  Instance_HashNameToBucket(int a1)
{
  return 11329 * (*(_DWORD *)(a1 + 12) << 16 >> 18) % 0x2ABu;
}

//----- (004831B0) --------------------------------------------------------
int  Instance_PrintClassInstanceSummary(double a1)
{
  int v1; // edi
  _DWORD *i; // esi
  int v3; // edx
  int v4; // ecx

  Module_BeginEnum();
  v1 = g_Instance_PurgeInProgress;
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
  g_Instance_PurgeInProgress = v1;
  return Module_EndEnum();
}
// 4831F0: variable 'v3' is possibly undefined
// 4831F0: variable 'v4' is possibly undefined
// 51A280: using guessed type int dword_51A280;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD38: using guessed type int dword_51AD38;

//----- (00483230) --------------------------------------------------------
signed int  Instance_ReleaseSlotValues(int a1)
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

  instance = (uintptr_t)(unsigned int)a1;
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
_DWORD * Instance_FindByName(int a1)
{
  int current_module; // ebp
  signed int qualifier_length; // eax
  int name_text; // edx
  int local_symbol; // eax
  signed int *module_symbol; // eax
  int module_record; // esi

  current_module = Module_GetCurrent();
  name_text = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( getenv("CLASH95_TRACE_PARSER_QUALIFIER_SCAN") )
  {
    fprintf(
      stderr,
      "[parser] fact-lookup symbol=%08x tag=%04x flags=%04x name=%08x caller=%p\n",
      a1,
      *(unsigned short *)(uintptr_t)(unsigned int)a1,
      *(unsigned short *)((uintptr_t)(unsigned int)a1 + 12),
      name_text,
      __builtin_return_address(0));
    fflush(stderr);
  }
  qualifier_length = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)name_text);
  if ( !qualifier_length )
    return Instance_LookupInHashBucket(a1, current_module, 0, current_module);
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
_DWORD * Instance_LookupInHashBucket(int a1, int a2, _DWORD *a3, int a4)
{
  int instance; // ebx
  int current; // ecx
  int class_record; // eax
  unsigned int bucket_index; // edx

  bucket_index = 11329 * ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 12) << 16 >> 18) % 0x2ABu;
  instance = *(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket_index);
  while ( instance )
  {
    if ( a1 == *(_DWORD *)((uintptr_t)(unsigned int)instance + 28) )
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
    if ( a2 == *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)class_record + 8)
      && Class_IsInScope(class_record, a4) )
      return (_DWORD *)(uintptr_t)(unsigned int)current;
    current = *(_DWORD *)((uintptr_t)(unsigned int)current + 60);
  }
  while ( current );
  if ( a3 )
  {
    Rules_ClearModuleSearchMarkers();
    return Instance_FindInSubclasses(a2, (_DWORD *)(uintptr_t)(unsigned int)instance);
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (00483440) --------------------------------------------------------
int  Instance_GetSlotValueBySymbol(int a1, int a2)
{
  unsigned int slot_index; // eax
  int class_record; // eax
  int slot_value_table; // eax

  class_record = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 44);
  slot_index = Instance_ResolveSlotIndex(class_record, a2);
  if ( slot_index == (unsigned int)-1 )
    return 0;
  slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 72);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_value_table + 4 * slot_index);
}

//----- (00483470) --------------------------------------------------------
unsigned int __fastcall Instance_ResolveSlotIndex(int a1, int a2)
{
  unsigned int slot_id; // eax
  int slot_index_table; // eax

  slot_id = Class_FindSlotNameID(a2);
  if ( slot_id == (unsigned int)-1 )
    return slot_id;
  if ( slot_id > *(_DWORD *)((uintptr_t)(unsigned int)a1 + 76) )
    return (unsigned int)-1;
  slot_index_table = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 60);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_index_table + 4 * slot_id) - 1;
}

//----- (004834A0) --------------------------------------------------------
BOOL  Parser_ParseSlotDefaultOrRestriction(int a1, int a2, _DWORD *a3, double a4)
{
  a3[1] = 4;
  a3[3] = 0;
  a3[4] = -1;
  if ( a2 )
  {
    if ( a1 || *(_DWORD *)(a2 + 10) )
    {
      Rules_StoreEvaluatedNodesAsMultifield(a3, a2, 1, a4);
      return g_ClipsEvaluationError == 0;
    }
    else
    {
      Parser_ParseForm((__int16 *)a2, a3, (int)a3, a4);
      return g_ClipsEvaluationError == 0;
    }
  }
  else
  {
    a3[2] = Rules_CreateEphemeralMultifield(0);
    return 1;
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (00483520) --------------------------------------------------------
signed int  Instance_PutSlotValue(_DWORD *a1, int *a2, _DWORD *a3, double a4)
{
  signed int result; // eax

  result = Instance_ValidateSlotValueConstraints(a3, *a2, (int)a1);
  if ( result )
    return Instance_StoreSlotValueAndMatch(a1, a2, 0, (uintptr_t)a3, a4);
  return result;
}

//----- (00483550) --------------------------------------------------------
signed int  Instance_StoreSlotValueAndMatch(_DWORD *a1, int *a2, __int16 a3, uintptr_t a4, double a5)
{
  int v6; // eax
  int v7; // edx
  __int16 v8; // cx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  char *v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  signed int v19; // eax
  int v21; // ecx
  int v22; // ecx
  char v23; // dh
  int v24; // edi
  int v25; // eax
  int v26; // edx
  int v27; // ecx
  _DWORD *v28; // eax
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // eax
  int v33; // ecx
  int v35; // [esp+Ch] [ebp-Ch]

  if ( !a4 )
  {
    Rules_ReportSystemError(a3, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( g_Rules_JoinOperationInProgress
    && (*(_BYTE *)(*a2 + 1) & 2) != 0
    && ((*(_BYTE *)(a1[11] + 20) & 8) != 0 || (*(_BYTE *)*a2 & 1) != 0) )
  {
    Rules_PrintErrorID((int)aInsfun, 5, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotModifyRe, v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternMatchin, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
    if ( a1[5] )
    {
      v6 = a1[5]
         + 12 * ((4 * (*(_DWORD *)(*(_DWORD *)(a1[11] + 60) + 4 * *(_DWORD *)(*(_DWORD *)(*a2 + 8) + 8)) - 1)) >> 2);
      if ( !*(_DWORD *)(v6 + 8) )
      {
        LOBYTE(a3) = *(_BYTE *)(v6 + 4) & 3;
        v7 = a2[1];
        *(_BYTE *)(v6 + 4) = a3;
        *(_DWORD *)(v6 + 4) |= v7 & 0xFC;
        *(_DWORD *)(v6 + 8) = a2[2];
        if ( (*(_BYTE *)*a2 & 2) != 0 )
          Rules_InstallMultifield(*(__int16 **)(v6 + 8));
        else
          Rules_AtomInstall(*(_DWORD *)(v6 + 4) << 24 >> 26, *(_DWORD *)(v6 + 8), a3);
      }
    }
    if ( (*(_BYTE *)*a2 & 2) != 0 )
    {
      Rules_DeinstallMultifield((__int16 *)a2[2]);
      Rules_RegisterEphemeralMultifield(a2[2]);
      v23 = a2[1] & 3;
      *((_BYTE *)a2 + 4) = v23;
      *((_BYTE *)a2 + 4) = v23 | 0x10;
      if ( *(_DWORD *)(a4 + 4) == 4 )
      {
        a2[2] = (int)Rules_CreateMultifield(*(_DWORD *)(a4 + 16) - *(_DWORD *)(a4 + 12) + 1);
        v24 = 1;
        v35 = *(_DWORD *)(a4 + 12) + 1;
        v25 = 0;
        v26 = 6 * v35 - 6;
        while ( v24 <= *(_DWORD *)(a4 + 16) - *(_DWORD *)(a4 + 12) + 1 )
        {
          *(_WORD *)(v25 + a2[2] + 14) = *(_WORD *)(v26 + *(_DWORD *)(a4 + 8) + 14);
          ++v24;
          v27 = *(_DWORD *)(*(_DWORD *)(a4 + 8) + v26 + 16);
          v26 += 6;
          *(_DWORD *)(v25 + a2[2] + 16) = v27;
          v25 += 6;
          ++v35;
        }
      }
      else
      {
        v28 = Rules_CreateMultifield(1);
        a2[2] = (int)v28;
        *((_WORD *)v28 + 7) = *(_WORD *)(a4 + 4);
        *(_DWORD *)(a2[2] + 16) = *(_DWORD *)(a4 + 8);
      }
      Rules_InstallMultifield((__int16 *)a2[2]);
    }
    else
    {
      Rules_AtomDeinstall((unsigned int)(a2[1] << 24) >> 26, (__int16 *)a2[2], a3);
      HIBYTE(v8) = a2[1] & 3;
      v9 = *(_DWORD *)(a4 + 4) & 0x3F;
      *((_BYTE *)a2 + 4) = HIBYTE(v8);
      a2[1] |= 4 * v9;
      v10 = *(_DWORD *)(a4 + 8);
      a2[2] = v10;
      Rules_AtomInstall((unsigned int)(a2[1] << 24) >> 26, v10, v8);
    }
    if ( (*(_BYTE *)(a1[11] + 20) & 0x20) != 0 )
    {
      if ( (*(_BYTE *)*a2 & 1) != 0 )
        v12 = aSharedSlot;
      else
        v12 = aLocalSlot;
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)v12, v11);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*a2 + 8) + 12) + 16), v13);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aInInstance, v14);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(a1[7] + 16), v15);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_503AF0, v16);
      if ( (a2[1] & 0xFC) == 0x10 )
        Lexer_OutputFieldRange((int)g_IO_LogicalNameTable_WTrace[0], a2[2], *(_DWORD *)(a2[2] + 6) - 1, 0, 1);
      else
        Rules_PrintAtomValue((int)g_IO_LogicalNameTable_WTrace[0], (unsigned int)(a2[1] << 24) >> 26, (int *)a2[2]);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_503AF8, v17);
    }
    g_Instance_InstancesChangedFlag = 1;
    if ( (*(_BYTE *)(a1[11] + 20) & 8) == 0 )
      return 1;
    v18 = *a2;
    if ( (*(_BYTE *)(*a2 + 1) & 2) == 0 )
      return 1;
    if ( (*(_BYTE *)v18 & 1) != 0 )
    {
      v19 = Class_NewTraversalID();
      if ( v19 != -1 )
      {
        Rules_MarkObjectPatternNetworkTraversal(v19, *(_DWORD *)(*a2 + 4), *a2, a5);
        Class_ReleaseTraversalID();
        return 1;
      }
      Rules_PrintErrorID((int)aInsfun, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToPatter, v29);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*a2 + 8) + 12) + 16), v30);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInClass, v31);
      v32 = Rules_GetConstructNameString(*(_DWORD *)(*a2 + 4));
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v32, (int)g_IO_LogicalNameTable_WError[0]);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v33);
      return 1;
    }
    else
    {
      Rules_ObjectMatchAction((unsigned __int16 *)3, a1, *(_DWORD *)(*(_DWORD *)(v18 + 8) + 8), a5);
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
signed int  Instance_ValidateSlotValueConstraints(_DWORD *a1, int a2, int a3)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int v14; // [esp+0h] [ebp-10h]

  if ( (*(_BYTE *)a2 & 2) == 0 && a1[1] == 4 )
  {
    Rules_PrintErrorID((int)aInsfun, 7, 0);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)a1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalForSing, v6);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], a2, v7, a3);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v8);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( a1[1] == 105 )
  {
    Rules_PrintErrorID((int)aInsfun, 8, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVoidFunctionIl, v9);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], a2, v10, a3);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v11);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( Rules_DynamicConstraintCheckingEnabled() && (v14 = Rules_CheckFieldAgainstConstraint(a1, *(_DWORD *)(a2 + 20))) != 0 )
  {
    Rules_PrintErrorID((int)aCstrnchk, 1, 0);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)a1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFor, v12);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], a2, v13, a3);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, v14, *(_DWORD *)(a2 + 20), 0);
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
_DWORD * Instance_ResolveArgumentToInstance(int a1, int a2, double a3)
{
  _DWORD *v4; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // [esp-4h] [ebp-20h] BYREF
  int v11; // [esp+0h] [ebp-1Ch]
  int v12; // [esp+4h] [ebp-18h]
  int v13; // [esp+18h] [ebp-4h]

  v13 = a2;
  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &v10, a1, a3);
  if ( v11 == 7 )
  {
    v4 = (_DWORD *)v12;
    if ( (*(_BYTE *)(v12 + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    if ( v11 != 8 && v11 != 2 )
    {
      Rules_PrintErrorID((int)aInsfun, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_1, v7);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v8, v8);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_InstanceError, v9);
      Lexer_ErrorRecover(1);
      return 0;
    }
    v4 = Instance_FindByName(v12);
    if ( !v4 )
    {
      Instance_ReportNoSuchInstanceError(v6, v6);
      return 0;
    }
  }
  return v4;
}
// 483B28: variable 'v6' is possibly undefined
// 483B51: variable 'v7' is possibly undefined
// 483B5D: variable 'v8' is possibly undefined
// 483B6C: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;

//----- (00483B90) --------------------------------------------------------
int __fastcall Instance_ReportNoSuchInstanceError(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
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
int __fastcall Instance_ReportNoSuchSlotError(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
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
signed int  Instance_PrintSlotErrorContext(int a1, int a2, int a3, int a4)
{
  int v6; // ecx
  int v7; // ecx
  char *v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx

  Output_Write(a1, (int)aSlot, a3);
  Output_Write(a1, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 8) + 12) + 16), v6);
  if ( a4 )
  {
    Output_Write(a1, (int)aOfInstance, v7);
    Output_Write(a1, *(_DWORD *)(*(_DWORD *)(a4 + 28) + 16), v12);
    v8 = asc_503C24;
  }
  else
  {
    if ( !*(_DWORD *)(a2 + 4) )
      goto LABEL_5;
    Output_Write(a1, (int)aOfClass, v7);
    v8 = (char *)Rules_GetConstructNameString(*(_DWORD *)(a2 + 4));
  }
  Output_Write(a1, (int)v8, v9);
LABEL_5:
  Output_Write(a1, (int)aFoundIn, v7);
  if ( v10 )
    return Output_Write(a1, v10, v10);
  else
    return MessageHandler_PrintNameTypeAndClass(a1, *(_DWORD **)g_ClipsCurrentHandlerCore, 0);
}
// 483CFB: variable 'v6' is possibly undefined
// 483D11: variable 'v7' is possibly undefined
// 483D22: variable 'v9' is possibly undefined
// 483D35: variable 'v10' is possibly undefined
// 483D57: variable 'v12' is possibly undefined
// 51AD58: using guessed type int dword_51AD58;

//----- (00483D80) --------------------------------------------------------
signed int  Instance_PrintNameOfClass(int a1, int a2, int a3)
{
  int v4; // eax
  int v5; // ecx
  int v6; // ecx

  Output_Write(a1, (int)asc_503C40, a1);
  v4 = Rules_GetInstanceClassName(a2);
  Output_Write(v5, v4, v5);
  Output_Write(v6, (int)aOf, v6);
  return Class_PrintName(*(_DWORD *)(a2 + 44), a3);
}
// 483D9B: variable 'v5' is possibly undefined
// 483DA7: variable 'v6' is possibly undefined

//----- (00483DC0) --------------------------------------------------------
_DWORD * Instance_FindInSubclasses(int a1, _DWORD *a2)
{
  _DWORD *v3; // ebp
  _DWORD *v4; // ebx
  int v5; // ecx
  int *v6; // edi
  int v7; // eax
  _DWORD *result; // eax

  if ( *(_DWORD *)(a1 + 20) )
    return 0;
  v3 = *(_DWORD **)(a1 + 12);
  *(_DWORD *)(a1 + 20) = 1;
  if ( !v3 )
  {
LABEL_10:
    for ( result = a2; result; result = (_DWORD *)result[15] )
    {
      if ( result[7] != a2[7] )
        break;
      if ( (*(_BYTE *)(result[11] + 20) & 2) != 0 )
        return result;
    }
    return 0;
  }
  while ( 1 )
  {
    v4 = a2;
    v6 = Module_FindByName(*(_BYTE **)(*v3 + 16));
    if ( a2 )
    {
      while ( v4[7] == a2[7] )
      {
        v7 = v4[11];
        if ( v6 == **(int ***)(v7 + 8) && Class_IsInScope(v7, v5) )
          return v4;
        v4 = (_DWORD *)v4[15];
        if ( !v4 )
          break;
      }
    }
    result = (_DWORD *)Instance_FindInSubclasses((int)v6, (int)a2);
    if ( result )
      return result;
    v3 = (_DWORD *)v3[3];
    if ( !v3 )
      goto LABEL_10;
  }
}
// 483E0F: variable 'v5' is possibly undefined

//----- (00483E70) --------------------------------------------------------
signed int  Instance_PrintStaleOrClassLabel(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v6; // ecx
  signed int *v7; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (*(_BYTE *)(a2 + 24) & 2) != 0 )
  {
    Output_Write(a1, (int)aStaleInstance, a1);
    Output_Write(v3, *(_DWORD *)(*(_DWORD *)(a2 + 28) + 16), v3);
    return Output_Write(v4, (int)asc_503C60, v4);
  }
  else
  {
    Output_Write(a1, (int)asc_503C40, a1);
    v7 = Instance_GetQualifiedName(a2, v6);
    Output_Write(v8, v7[4], v8);
    return Output_Write(v9, (int)asc_503C24, v9);
  }
}
// 483E90: variable 'v3' is possibly undefined
// 483E9C: variable 'v4' is possibly undefined
// 483EB2: variable 'v6' is possibly undefined
// 483EBC: variable 'v8' is possibly undefined
// 483EC8: variable 'v9' is possibly undefined

//----- (00483ED0) --------------------------------------------------------
signed int  Instance_PrintNameOrDummyLabel(int a1, void **a2)
{
  int v2; // ecx
  char *v5; // edx
  signed int result; // eax
  int v7; // ecx
  signed int *v8; // eax
  int v9; // ecx
  char *v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int *v14; // eax
  int v15; // ecx

  v2 = a1;
  if ( g_Print_InstanceAddressesToNamesFlag )
  {
    if ( a2 == &g_Instance_DummyInstanceRecord )
    {
      v5 = aDummyInstanc_0;
    }
    else
    {
      Output_Write(a1, (int)asc_503C40, a1);
      v8 = Instance_GetQualifiedName((int)a2, v7);
      Output_Write(v9, v8[4], v9);
      v5 = asc_503C24;
      a1 = v2;
    }
    return Output_Write(a1, (int)v5, v2);
  }
  else
  {
    if ( g_Print_AddressesToStringsFlag )
      Output_Write(a1, (int)asc_503C78, a1);
    if ( a2 == &g_Instance_DummyInstanceRecord )
    {
      v10 = aDummyInstanc_1;
    }
    else
    {
      if ( ((_BYTE)a2[6] & 2) != 0 )
      {
        Output_Write(v2, (int)aStaleInstanc_0, v2);
        Output_Write(v12, *((_DWORD *)a2[7] + 4), v12);
      }
      else
      {
        Output_Write(v2, (int)aInstance_7, v2);
        v14 = Instance_GetQualifiedName((int)a2, v13);
        Output_Write(v15, v14[4], v15);
      }
      v10 = asc_503CA4;
    }
    result = Output_Write(v2, (int)v10, v2);
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
signed int  Rules_MarkObjectPatternNetworkTraversal(signed int a1, signed int a2, int a3, double a4)
{
  int v6; // ebx
  signed int result; // eax
  unsigned int v8; // edx
  unsigned int v9; // ecx
  int j; // edi
  int v11; // edi
  _DWORD *i; // ecx
  int v13; // ecx

  v6 = ((a1 - (__CFSHL__(a1 >> 31, 3) + 8 * (a1 >> 31))) >> 3) + a2;
  result = 1 << (a1 % 8);
  if ( ((unsigned __int8)result & *(_BYTE *)(v6 + 108)) == 0 )
  {
    *(_BYTE *)(v6 + 108) |= result;
    v8 = *(_DWORD *)(*(_DWORD *)(a3 + 8) + 8);
    if ( v8 <= *(_DWORD *)(a2 + 76) )
    {
      v11 = *(_DWORD *)(*(_DWORD *)(a2 + 60) + 4 * v8);
      if ( v11 )
      {
        if ( a3 == *(_DWORD *)(*(_DWORD *)(a2 + 56) + 4 * v11 - 4) )
        {
          for ( i = *(_DWORD **)(a2 + 80); i; i = *(_DWORD **)(v13 + 52) )
            Rules_ObjectMatchAction((unsigned __int16 *)3, i, *(_DWORD *)(*(_DWORD *)(a3 + 8) + 8), a4);
        }
      }
    }
    v9 = 0;
    for ( j = 0; ; Rules_MarkObjectPatternNetworkTraversal(a1, *(_DWORD *)(*(_DWORD *)(a2 + 42) + j - 4), a3, a4) )
    {
      result = a2;
      if ( v9 >= *(unsigned __int16 *)(a2 + 40) )
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
  int v1; // esi
  int v2; // edx
  unsigned int v3; // ebx
  int i; // ecx
  unsigned int v5; // edi
  int v6; // eax
  __int16 *v7; // ebp

  v1 = result;
  v2 = *(_DWORD *)(result + 8) - 1;
  *(_DWORD *)(result + 8) = v2;
  if ( !v2 )
  {
    if ( (*(_BYTE *)(result + 24) & 2) != 0 )
      Instance_ReleaseSlotValues(result);
    result = *(_DWORD *)(v1 + 44);
    if ( *(_DWORD *)(result + 72) )
    {
      v3 = 0;
      for ( i = 0; ; i += 12 )
      {
        v5 = *(_DWORD *)(*(_DWORD *)(v1 + 44) + 72);
        if ( v3 >= v5 )
          break;
        v6 = i + *(_DWORD *)(v1 + 20);
        v7 = *(__int16 **)(v6 + 8);
        if ( v7 )
        {
          if ( (**(_BYTE **)v6 & 2) != 0 )
            Rules_DeinstallMultifield(*(__int16 **)(v6 + 8));
          else
            Rules_AtomDeinstall(*(_DWORD *)(v6 + 4) << 24 >> 26, v7, i);
        }
        ++v3;
      }
      result = Mem_SmallBlockFree(*(_DWORD **)(v1 + 20), 12 * v5);
      *(_DWORD *)(v1 + 20) = 0;
    }
  }
  return result;
}
// 4840D2: variable 'i' is possibly undefined

//----- (00484130) --------------------------------------------------------
_DWORD * Instance_AcquireLocalSlotArray(_DWORD *result)
{
  _DWORD *v2; // edx
  int v3; // esi
  int v4; // ebx
  _DWORD *v5; // eax
  int v6; // ecx
  unsigned int v7; // ecx

  v2 = result;
  if ( !result[2] )
  {
    v3 = *(_DWORD *)(result[11] + 72);
    if ( v3 )
    {
      v4 = 0;
      v5 = Mem_SmallBlockAlloc(12 * v3);
      *(_DWORD *)(v6 + 20) = v5;
      v7 = 0;
      result = 0;
      while ( v7 < *(_DWORD *)(v2[11] + 72) )
      {
        *(_DWORD *)((char *)result + v2[5]) = **(_DWORD **)(v2[18] + v4);
        result += 3;
        v4 += 4;
        ++v7;
        *(_DWORD *)((char *)result + v2[5] - 4) = 0;
      }
    }
  }
  ++v2[2];
  return result;
}
// 48414A: variable 'v2' is possibly undefined
// 48416C: variable 'v6' is possibly undefined

//----- (004841A0) --------------------------------------------------------
void  Instance_NotifyCreated(_DWORD *a1, double a2)
{
  Rules_ObjectMatchAction((unsigned __int16 *)1, a1, -1, a2);
}

//----- (004842DF) --------------------------------------------------------
#if 0
void  __noreturn CRT_WatcomEHHandleNestedException(int a1, int a2)
{
  int *v3; // edi
  int *v4; // ebp
  char v5; // al
  int *v6; // eax
  int v7; // edx
  int v8; // ecx
  _DWORD *v9; // eax
  int *v10; // eax
  int *v11; // eax
  int v12; // ecx
  _EXC_PR_FNEXC *v13[26]; // [esp+0h] [ebp-14Ch] BYREF
  char v14; // [esp+D8h] [ebp-74h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+110h] [ebp-3Ch]
  tagRECT *v16; // [esp+114h] [ebp-38h]
  void *v17; // [esp+118h] [ebp-34h]
  int v18; // [esp+11Ch] [ebp-30h]
  _EXC_PR_FNEXC **v19; // [esp+124h] [ebp-28h]
  char v20; // [esp+128h] [ebp-24h]
  int v21; // [esp+130h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v16 = &j____wcpp_4_fs_handler_rtn_;
  v17 = &g_CRTWatcomEHHandleNestedException_ScopeTable;
  v18 = 0;
  v21 = **(_DWORD **)(a1 + 8);
  v3 = *(int **)(v21 + 8);
  *(_DWORD *)(v21 + 12) = aViolationOfFun;
  v4 = v3;
  v3[7] = a1;
  while ( 1 )
  {
    if ( !v4 )
    {
      v3[7] = a1;
      v5 = *((_BYTE *)v3 + 12);
      *((_BYTE *)v3 + 12) = 2;
      *((_BYTE *)v3 + 13) = v5;
      if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
        v6 = 0;
      else
        v6 = v3;
      _EXC_PR_FNEXC::_EXC_PR_FNEXC(v6);
      v18 = 1;
      unexpected();
      v14 = 3;
      _wcpp_4_call_terminate__(v8, v7);
      v18 = 0;
      _EXC_PR_FNEXC::~_EXC_PR_FNEXC(v13[0]);
    }
    v9 = (_DWORD *)v4[7];
    if ( v9 && *(_DWORD *)a1 == *v9 && *(_DWORD *)(a1 + 32) == v9[8] )
    {
      if ( *((_BYTE *)v4 + 12) == 2 )
      {
        *((_BYTE *)v3 + 12) = 7;
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          v10 = 0;
        else
          v10 = v3;
        _EXC_PR_FNEXC::_EXC_PR_FNEXC(v10);
        v20 = 0;
        v19 = v13;
        v18 = 4;
        ExcString_Ctor();
        v18 = 5;
        ExcString_Ctor();
        v13[25] = (_EXC_PR_FNEXC *)&g_BadException_VTable;
        v18 = 7;
        CRT_ThrowExcStringException();
        v19 = v13;
        v20 = 0;
        v18 = 0;
        _EXC_PR_FNEXC::~_EXC_PR_FNEXC(v13[0]);
      }
      if ( *((_BYTE *)v4 + 12) == 7 )
      {
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          v11 = 0;
        else
          v11 = v3;
        _EXC_PR_DTOR::_EXC_PR_DTOR(v11);
        v18 = 14;
        _wcpp_4_call_terminate__(v12, v21);
        v18 = 0;
        _EXC_PR_DTOR::~_EXC_PR_DTOR(v13[0]);
      }
      if ( v4 != v3 )
        _wcpp_4_corrupted_stack__(a2);
    }
    v4 = (int *)*v4;
    if ( v3 == v4 )
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
  int v3; // ebx

  result = fputs_(this, &g_CRT_StdoutStream);
  v3 = result;
  if ( result != -1 )
  {
    result = CRT_PutcToStream(v2, &g_CRT_StdoutStream);
    if ( result == 10 )
      return v3 + 1;
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
unsigned int  CRT_WatcomEHUnwindToState(unsigned int a1, int a2, int a3)
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
  v19 = a1;
  v20 |= 1u;
  v21 = CRT_WatcomEHTraverseUnwindState((int)v17, v5);
  while ( 1 )
  {
    result = v18;
    if ( v18 == a1 )
      break;
    if ( v18 < a1 )
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
int  Str_ParseSignedInt(char *a1)
{
  char v1; // cl
  int v2; // ebx
  int v3; // ebx

  while ( (IsTable[(unsigned __int8)(*a1 + 1)] & 2) != 0 )
    ++a1;
  v1 = *a1;
  if ( *a1 == 43 || v1 == 45 )
    ++a1;
  v2 = 0;
  while ( (IsTable[(unsigned __int8)(*a1 + 1)] & 0x20) != 0 )
  {
    v3 = (unsigned __int8)*a1++ + 10 * v2;
    v2 = v3 - 48;
  }
  if ( v1 == 45 )
    return -v2;
  return v2;
}

//----- (00485384) --------------------------------------------------------
int  CRT_InitializeProcessStartupInfo(int a1, int a2, int a3, HMODULE a4)
{
  int result; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  CHAR *v9; // eax
  _BYTE *v10; // eax
  int v11; // ecx
  int v12; // [esp-208h] [ebp-624h] BYREF
  _BYTE v13[520]; // [esp+0h] [ebp-41Ch] BYREF
  CHAR Filename[260]; // [esp+208h] [ebp-214h] BYREF
  CHAR v15[268]; // [esp+30Ch] [ebp-110h] BYREF
  int v16; // [esp+418h] [ebp-4h]

  v16 = a3;
  g_CrtThreadDataMgmtDisabledFlag = a1;
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
    v9 = (CHAR *)CRT_FinalizeAnsiApiStringResult(v8, v7);
    if ( *v9 != 34 )
    {
      while ( (IsTable[(unsigned __int8)(*v9 + 1)] & 2) == 0 && *v9 )
        ++v9;
      goto LABEL_12;
    }
    do
      ++v9;
    while ( *v9 != 34 && *v9 );
    if ( !*v9 )
      goto LABEL_12;
    do
    {
      ++v9;
LABEL_12:
      ;
    }
    while ( (IsTable[(unsigned __int8)(*v9 + 1)] & 2) != 0 );
    lpCmdLine = v9;
    if ( GetCommandLineW() )
    {
      v10 = (_BYTE *)CRT_FinalizeWideApiStringResult();
      if ( *(_WORD *)v10 != 34 )
      {
        while ( (IsTable[(unsigned __int8)(*v10 + 1)] & 2) == 0 && *(_WORD *)v10 )
          v10 += 2;
        goto LABEL_22;
      }
      do
        v10 += 2;
      while ( *(_WORD *)v10 != 34 && *(_WORD *)v10 );
      if ( !*(_WORD *)v10 )
        goto LABEL_22;
      do
      {
        v10 += 2;
LABEL_22:
        ;
      }
      while ( (IsTable[(unsigned __int8)(*v10 + 1)] & 2) != 0 );
    }
    else
    {
      v10 = (_BYTE *)CRT_FinalizeWideApiStringResult();
    }
    g_CRT_WideCommandLine = (int)v10;
    if ( a1 )
    {
      GetModuleFileNameA(a4, v15, 0x104u);
      g_CRT_ModulePathA = CRT_FinalizeAnsiApiStringResult(v11, v13);
      _lib_GetModuleFileNameW_();
      g_CRT_ModulePathW = CRT_FinalizeWideApiStringResult();
    }
    return 1;
  }
  else if ( !a1 )
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
signed int  Output_WriteLongString(signed int result, char *a2)
{
  int v2; // esi
  char *v3; // ebx
  int v4; // ecx
  int v5; // edx
  char saved_char; // cl

  v2 = result;
  v3 = a2;
  if ( a2 )
  {
    while ( 1 )
    {
      v4 = strlen(v3);
      if ( v4 <= 500 )
        break;
      v5 = (int)v3;
      v3 += 500;
      LOBYTE(v4) = *v3;
      saved_char = *v3;
      *v3 = 0;
      Output_Write(v2, v5, v4);
      *v3 = saved_char;
    }
    return Output_Write(v2, (int)v3, v4);
  }
  return result;
}

//----- (00485740) --------------------------------------------------------
signed int  Rules_PrintFloat(int a1, double a2)
{
  int v2; // eax

  v2 = Rules_FloatToSymbol(a1, a2);
  return Output_Write(a1, v2, a1);
}

//----- (00485770) --------------------------------------------------------
signed int __fastcall Rules_PrintLongInteger(int a1, int a2)
{
  _BYTE v4[32]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v5 = a1;
  sprintf_(v4, "%ld", a2);
  return Output_Write(v5, (int)v4, v5);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004857A0) --------------------------------------------------------
unsigned int  Rules_PrintAtomValue(int a1, unsigned int a2, int *a3)
{
  int v3; // ecx
  unsigned int result; // eax
  int v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE v17[32]; // [esp+8h] [ebp-20h] BYREF

  v3 = a1;
  result = a2;
  if ( a2 < 3 )
  {
    if ( a2 )
    {
      if ( a2 > 1 )
        return Output_Write(v3, a3[4], v3);
      else
        return Rules_PrintLongInteger(v3, a3[4]);
    }
    else
    {
      v11 = Rules_FloatToSymbol(v3, *((double *)a3 + 2));
      return Output_Write(v12, v11, v12);
    }
  }
  if ( a2 <= 3 )
  {
    if ( g_Print_PreserveEscapedCharactersFlag )
    {
      v6 = Str_InternQuotedEscapedString((int *)a3[4], v3);
      return Output_Write(v7, v6, v7);
    }
    else
    {
      Output_Write(v3, (int)asc_503EA4, v3);
      Output_Write(v13, a3[4], v13);
      return Output_Write(v14, (int)asc_503EA4, v14);
    }
  }
  if ( a2 < 8 )
  {
    if ( a2 == 5 )
    {
      if ( g_Print_AddressesToStringsFlag )
        Output_Write(v3, (int)asc_503EA4, v3);
      Output_Write(v3, (int)aPointer, v3);
      sprintf_(v17, "%p", a3);
      Output_Write(v8, (int)v17, v8);
      result = Output_Write(v9, (int)asc_503EB8, v9);
      if ( g_Print_AddressesToStringsFlag )
        return Output_Write(v10, (int)asc_503EA4, v10);
      return result;
    }
    goto LABEL_4;
  }
  if ( a2 <= 8 )
  {
    Output_Write(v3, (int)asc_503EBC, v3);
    Output_Write(v15, a3[4], v15);
    return Output_Write(v16, (int)asc_503EC0, v16);
  }
  if ( a2 != 105 )
  {
LABEL_4:
    result = 4 * a2;
    v5 = g_Clips_PrimitiveEntityTable[a2];
    if ( v5 )
    {
      if ( *(_DWORD *)(v5 + 8) )
        return (*(int (**)(void))(v5 + 8))();
      else
        return Output_Write(v3, (int)aUnknownAtomTyp, v3);
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
int  Rules_PrintTally(int result, int a2, int a3, int a4)
{
  int v4; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx

  v4 = result;
  if ( a2 )
  {
    Output_Write(result, (int)aForATotalOf, a3);
    Rules_PrintLongInteger(v6, a2);
    Output_Write(v4, (int)asc_503EE8, v7);
    if ( a2 != 1 )
      a4 = v8;
    Output_Write(v4, a4, v8);
    return Output_Write(v4, (int)a__14, v10);
  }
  return result;
}
// 48596B: variable 'v6' is possibly undefined
// 485977: variable 'v7' is possibly undefined
// 485985: variable 'v8' is possibly undefined
// 485991: variable 'v10' is possibly undefined

//----- (004859A0) --------------------------------------------------------
signed int  Rules_PrintErrorID(int a1, int a2, int a3)
{
  if ( a3 )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EF0, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EBC, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, 0);
  Rules_PrintLongInteger((int)g_IO_LogicalNameTable_WError[0], a2);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_503EF4, 0);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00485A00) --------------------------------------------------------
signed int  Rules_PrintWarningID(int a1, int a2, int a3)
{
  if ( a3 )
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)asc_503EF0, 0);
  Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)asc_503EBC, 0);
  Output_Write((int)g_IO_LogicalNameTable_WWarning[0], a1, 0);
  Rules_PrintLongInteger((int)g_IO_LogicalNameTable_WWarning[0], a2);
  return Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWarning, 0);
}
// 51A610: using guessed type char *off_51A610[6];

//----- (00485A60) --------------------------------------------------------
signed int __fastcall Rules_ReportCantFindItem(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v7);
}
// 485A82: variable 'v3' is possibly undefined
// 485A8E: variable 'v4' is possibly undefined
// 485A9D: variable 'v5' is possibly undefined
// 485AA9: variable 'v6' is possibly undefined
// 485AB8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485AD0) --------------------------------------------------------
signed int __fastcall Rules_ReportCantDeleteItem(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__14, v7);
}
// 485AF2: variable 'v3' is possibly undefined
// 485AFE: variable 'v4' is possibly undefined
// 485B0D: variable 'v5' is possibly undefined
// 485B19: variable 'v6' is possibly undefined
// 485B28: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485B40) --------------------------------------------------------
signed int __fastcall Rules_ReportAlreadyParsed(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)aPrntutil, 5, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_0, v3);
  if ( v4 )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  if ( a2 )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v4);
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
signed int __fastcall Rules_ReportSystemError(int a1, int a2)
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
  Rules_PrintLongInteger(v6, a2);
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
int __fastcall Rules_FloatToSymbol(int a1, double a2)
{
  int v3; // esi
  int v4; // ecx
  char v5; // al
  char *v7; // esi
  unsigned int v8; // kr04_4
  char *v9; // edi
  char v10; // al
  char v11; // al
  char v12[52]; // [esp+0h] [ebp-34h] BYREF

  *(_DWORD *)&v12[48] = a1;
  v3 = 0;
  sprintf_(v12, "%.16g", a2);
  while ( 1 )
  {
    v5 = v12[v3];
    if ( !v5 )
      break;
    if ( v5 == 46 || v5 == 101 )
      return Str_Intern(v12, v4)[4];
    ++v3;
  }
  v7 = a_0;
  v8 = strlen(v12) + 1;
  v9 = &v12[v8 - 1];
  do
  {
    v10 = *v7;
    *v9 = *v7;
    if ( !v10 )
      break;
    v11 = v7[1];
    v7 += 2;
    v9[1] = v11;
    v9 += 2;
  }
  while ( v11 );
  return Str_Intern(v12, ~v8)[4];
}
// 485DA8: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00485E00) --------------------------------------------------------
int  Rules_LongIntegerToSymbol(int a1)
{
  int v1; // ecx
  char v3[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf_(v3, "%ld", a1);
  return Str_Intern(v3, v1)[4];
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
signed int  Output_Write(int a1, int a2, int a3)
{
  int v5; // ecx
  void (__fastcall *router_write)(int, int); // ecx

  if ( g_IO_FastSaveFilePtr && a1 == g_IO_FastSaveFilePtr )
  {
    Output_WriteFormatted(0, 0, g_IO_FastSaveFilePtr, (int)aS_1, a2);
    return 2;
  }
  else
  {
    v5 = g_IO_RouterListHead;
    if ( g_IO_RouterListHead )
    {
      while ( !*(_DWORD *)(v5 + 16) || !IO_RouterMatchesName(a1, v5) )
      {
        v5 = *(_DWORD *)(v5 + 32);
        if ( !v5 )
          goto LABEL_5;
      }
      router_write = (void (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(v5 + 16);
      router_write(a1, a2);
      return 1;
    }
    else
    {
LABEL_5:
      if ( strcmp_((int)g_IO_LogicalNameTable_WError[0], a1) )
        IO_ReportUnrecognizedRouter(a1);
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
int  Lexer_PeekChar(int a1, unsigned int a2)
{
  int result; // eax
  unsigned __int8 *v3; // ecx
  int v4; // ecx
  int (__fastcall *router_read)(int); // eax

  if ( a1 == g_IO_FastLoadFilePtr )
  {
    if ( *(int *)(g_IO_FastLoadFilePtr + 4) > 0 && (a2 = **(unsigned __int8 **)g_IO_FastLoadFilePtr - 13, a2 > 0xFD) )
    {
      --*(_DWORD *)(g_IO_FastLoadFilePtr + 4);
      v3 = (unsigned __int8 *)(*(_DWORD *)g_IO_FastLoadFilePtr)++;
      result = *v3;
    }
    else
    {
      result = fgetc_(a2, g_IO_FastLoadFilePtr);
    }
    if ( result != 13 )
      return result;
    return 10;
  }
  v4 = g_IO_RouterListHead;
  if ( !g_IO_RouterListHead )
  {
LABEL_12:
    IO_ReportUnrecognizedRouter(a1);
    return -1;
  }
  while ( !*(_DWORD *)(v4 + 24) || !IO_RouterMatchesName(a1, v4) )
  {
    v4 = *(_DWORD *)(v4 + 32);
    if ( !v4 )
      goto LABEL_12;
  }
  router_read = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(v4 + 24);
  result = router_read(a1);
  if ( result == 13 )
    return 10;
  return result;
}
// 485F4E: variable 'v4' is possibly undefined
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;
// 51A608: using guessed type int dword_51A608;

//----- (00485F90) --------------------------------------------------------
signed int  Lexer_SkipChar(signed int a1, int a2, int a3)
{
  int v4; // ecx
  int (__fastcall *router_skip)(int, int); // eax

  if ( a2 == g_IO_FastLoadFilePtr )
    return CRT_FlushBufferAndPutChar(a1, a3);
  v4 = g_IO_RouterListHead;
  if ( g_IO_RouterListHead )
  {
    while ( !*(_DWORD *)(v4 + 28) || !IO_RouterMatchesName(a2, v4) )
    {
      v4 = *(_DWORD *)(v4 + 32);
      if ( !v4 )
        goto LABEL_5;
    }
    router_skip = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(v4 + 28);
    return router_skip(a1, a2);
  }
  else
  {
LABEL_5:
    IO_ReportUnrecognizedRouter(a2);
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
int IO_RunRouterExitCallbacks(a1)
int a1;
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
      result = router_exit(a1);
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
signed int  IO_AddRouter(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  _DWORD *v10; // ebx
  _DWORD *v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // ecx

  v10 = *(_DWORD **)(g_ClipsMemoryTable + 144);
  if ( v10 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 144);
    *(_DWORD *)(g_ClipsMemoryTable + 144) = *v10;
    v11 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v11 = (_DWORD *)Mem_HeapAllocWithRetry(36);
  }
  v11[1] = 1;
  v11[8] = 0;
  *v11 = a1;
  v11[2] = a2;
  v11[3] = a4;
  v11[4] = a3;
  v11[5] = a7;
  v11[6] = a5;
  v11[7] = a6;
  v12 = (int)v11;
  if ( !g_IO_RouterListHead )
  {
    g_IO_RouterListHead = (int)v11;
    return 1;
  }
  v13 = g_IO_RouterListHead;
  v14 = 0;
  do
  {
    if ( a2 >= *(_DWORD *)(v13 + 8) )
      break;
    v14 = v13;
    v13 = *(_DWORD *)(v13 + 32);
  }
  while ( v13 );
  if ( !v14 )
  {
    *(_DWORD *)(v12 + 32) = g_IO_RouterListHead;
    g_IO_RouterListHead = v12;
    return 1;
  }
  *(_DWORD *)(v12 + 32) = v13;
  *(_DWORD *)(v14 + 32) = v12;
  return 1;
}
// 4860C4: variable 'a3' is possibly undefined
// 51A604: using guessed type int dword_51A604;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00486150) --------------------------------------------------------
signed int  IO_DeleteRouter(int a1)
{
  int router; // ecx
  _DWORD *previous_router; // esi

  router = g_IO_RouterListHead;
  previous_router = 0;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, a1) )
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
int  IO_QueryRouters(int a1)
{
  int logical_name; // ebx
  int router; // ecx

  logical_name = a1;
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
int __fastcall IO_RouterMatchesName(int a1, int a2)
{
  int result; // eax
  int (__fastcall *router_query)(int); // eax

  if ( !*(_DWORD *)(a2 + 4) )
    return 0;
  if ( !*(_DWORD *)(a2 + 12) )
    return 0;
  router_query = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(a2 + 12);
  result = router_query(a1);
  if ( result != 1 )
    return 0;
  return result;
}

//----- (00486200) --------------------------------------------------------
signed int  IO_DeactivateRouter(int a1)
{
  int router; // ecx

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, a1) )
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
signed int  IO_ActivateRouter(int a1)
{
  int router; // ecx
  signed int result; // eax

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)router, a1) )
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
int  IO_ReportUnrecognizedRouter(int a1)
{
  static int reporting_router_error;
  int result; // eax

  if ( reporting_router_error )
    return 0;
  reporting_router_error = 1;
  Rules_PrintErrorID((int)aRouter, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLogicalName, 0);
  if ( a1 )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, 0);
  result = Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasNotRecogniz, 0);
  reporting_router_error = 0;
  return result;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00486414) --------------------------------------------------------
char *__thiscall CRT_AllocateLockSlot(void *this)
{
  int v1; // edx
  int v2; // ebx
  int v3; // ecx

  v1 = g_CRT_UsedLockSlotCount;
  if ( g_CRT_UsedLockSlotCount >= 64 )
  {
    v2 = calloc_(this, 24);
    if ( !v2 )
      _fatal_runtime_error_(v3, 1);
  }
  else
  {
    ++g_CRT_UsedLockSlotCount;
    return (char *)&g_CRT_LockSlotPool + 24 * v1;
  }
  return (char *)v2;
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
void  CRT_AcquireFileHandleLock(char a1)
{
  CRT_LockEnter((int)&g_CRT_FileHandleLockSlots + 16 * (a1 & 0xF));
}

//----- (004864B7) --------------------------------------------------------
void  CRT_ReleaseFileHandleLock(char a1)
{
  CRT_LockLeave((int)&g_CRT_FileHandleLockSlots + 16 * (a1 & 0xF));
}

//----- (004864CC) --------------------------------------------------------
int  CRT_ReleaseAndUnregisterFileHandle(char a1)
{
  CRT_ResetLockSlot((int)&g_CRT_FileHandleLockSlots + 16 * (a1 & 0xF));
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
void  CRT_LockEnter(int a1)
{
  DWORD CurrentThreadId; // esi
  void *v3; // ecx
  char *v4; // eax

  CurrentThreadId = GetCurrentThreadId();
  if ( CurrentThreadId != *(_DWORD *)(a1 + 8) )
  {
    if ( !*(_DWORD *)(a1 + 4) )
    {
      CRT_LockEnter((int)&g_CRT_LockInitCriticalSection);
      if ( !*(_DWORD *)(a1 + 4) )
      {
        v4 = CRT_AllocateLockSlot(v3);
        *(_DWORD *)a1 = v4;
        InitializeCriticalSection((LPCRITICAL_SECTION)v4);
        *(_DWORD *)(a1 + 4) = 1;
      }
      CRT_LockLeave((int)&g_CRT_LockInitCriticalSection);
    }
    EnterCriticalSection(*(LPCRITICAL_SECTION *)a1);
    *(_DWORD *)(a1 + 8) = CurrentThreadId;
  }
  ++*(_DWORD *)(a1 + 12);
}
// 486549: variable 'v3' is possibly undefined
// 54DECC: using guessed type int dword_54DECC;

//----- (00486583) --------------------------------------------------------
void  CRT_LockLeave(int result)
{
  int v1; // edx
  struct _RTL_CRITICAL_SECTION *v2; // [esp-10h] [ebp-14h]

  v1 = *(_DWORD *)(result + 12);
  if ( v1 )
  {
    *(_DWORD *)(result + 12) = v1 - 1;
    if ( v1 == 1 )
    {
      v2 = *(struct _RTL_CRITICAL_SECTION **)result;
      *(_DWORD *)(result + 8) = 0;
      LeaveCriticalSection(v2);
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
  int v2; // eax
  int v3; // ebx
  int v4; // edx

  if ( !a1 )
  {
    v2 = calloc_(a2, g_CRT_ThreadDataBlockSize);
    if ( v2 )
    {
      v3 = g_CRT_ThreadDataBlockSize;
      *(_BYTE *)(v2 + 82) = 1;
      *(_DWORD *)(v2 + 240) = v3;
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
  void *v4; // ebx
  int v5; // ecx

  if ( dwTlsIndex == -1 )
    return 0;
  result = CRT_AllocateThreadDataBlock(a1, a2);
  v4 = (void *)result;
  if ( result )
  {
    if ( !_AddThreadData_(v3, result) )
    {
      nfree_(v5);
      return 0;
    }
    TlsSetValue(dwTlsIndex, v4);
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
  char *v1; // ebx
  void *v2; // esi

  v1 = result;
  if ( dwTlsIndex != -1 )
  {
    result = (char *)TlsGetValue(dwTlsIndex);
    if ( result )
    {
      v2 = *(void **)(result + 222);
      _RemoveThreadData_();
      result = (char *)TlsSetValue(dwTlsIndex, 0);
      if ( v2 )
      {
        if ( v1 )
          return (char *)CloseHandle(v2);
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
  return loc_48672B();
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
int  Surface_DDCopyBitmapToNewSurface(int a1, const CHAR *a2, _DWORD *a3, int a4)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  int v9; // ecx
  _DWORD *v10; // esi
  void *v12; // [esp+4h] [ebp-A0h]
  _DWORD v13[2]; // [esp+8h] [ebp-9Ch] BYREF
  int v14; // [esp+10h] [ebp-94h]
  int v15; // [esp+14h] [ebp-90h]
  int v16; // [esp+70h] [ebp-34h]
  _BYTE pv[4]; // [esp+74h] [ebp-30h] BYREF
  int v18; // [esp+78h] [ebp-2Ch]
  int v19; // [esp+7Ch] [ebp-28h]
  int v20; // [esp+8Ch] [ebp-18h] BYREF
  int v21; // [esp+90h] [ebp-14h]
  _DWORD *v22; // [esp+94h] [ebp-10h]

  v21 = a4;
  v22 = a3;
  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, a2, 0, 0, 0, 0x2000u);
  if ( !ImageA )
  {
    ImageA = LoadImageA(0, a2, 0, 0, 0, 0x2010u);
    if ( !ImageA )
      return 0;
  }
  GetObjectA(ImageA, 24, pv);
  memset_(7, 0);
  v15 = v18;
  v13[1] = v9;
  v14 = v19;
  v13[0] = 108;
  v16 = 64;
  if ( (*(int (__stdcall **)(int, _DWORD *, int *, _DWORD))(*(_DWORD *)a1 + 24))(a1, v13, &v20, 0) )
    return 0;
  Surface_DDCopyBitmap(v20, ImageA, 0, 0, 0, 0);
  v12 = ImageA;
  v10 = (_DWORD *)v21;
  DeleteObject(v12);
  *v10 = v15;
  *v22 = v14;
  return v20;
}
// 486A9B: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00486B10) --------------------------------------------------------
signed int  Surface_DDCopyBitmapFromFile(int a1, const CHAR *a2)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  signed int v6; // ebx

  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, a2, 0, 0, 0, 0x2000u);
  if ( !ImageA )
    ImageA = LoadImageA(0, a2, 0, 0, 0, 0x2010u);
  if ( ImageA )
  {
    v6 = Surface_DDCopyBitmap(a1, ImageA, 0, 0, 0, 0);
    if ( v6 )
      OutputDebugStringA(aDdcopybitmapFa);
    DeleteObject(ImageA);
    return v6;
  }
  else
  {
    OutputDebugStringA(aHandleIsNull);
    return -2147467259;
  }
}

//----- (00486BA0) --------------------------------------------------------
signed int  Surface_DDCopyBitmap(int a1, void *a2, int a3, int a4, int a5, int a6)
{
  HDC CompatibleDC; // ebx
  int v11; // eax
  int v12; // edi
  _DWORD v13[27]; // [esp+Ch] [ebp-A0h] BYREF
  _BYTE pv[4]; // [esp+78h] [ebp-34h] BYREF
  int v15; // [esp+7Ch] [ebp-30h]
  int hSrc; // [esp+80h] [ebp-2Ch]
  HDC hdcDest; // [esp+90h] [ebp-1Ch] BYREF
  int v18; // [esp+94h] [ebp-18h]
  int ySrc; // [esp+98h] [ebp-14h]
  int wSrc; // [esp+9Ch] [ebp-10h]

  ySrc = a3;
  if ( !a2 || !a1 )
    return -2147467259;
  (*(void (__stdcall **)(int))(*(_DWORD *)a1 + 108))(a1);
  CompatibleDC = CreateCompatibleDC(0);
  if ( !CompatibleDC )
    OutputDebugStringA(OutputString);
  SelectObject(CompatibleDC, a2);
  GetObjectA(a2, 24, pv);
  if ( a5 )
    v11 = a5;
  else
    v11 = v15;
  wSrc = v11;
  if ( a6 )
    v12 = a6;
  else
    v12 = hSrc;
  v13[0] = 108;
  v13[1] = 6;
  (*(void (__stdcall **)(int, _DWORD *))(*(_DWORD *)a1 + 88))(a1, v13);
  v18 = (*(int (__stdcall **)(int, HDC *))(*(_DWORD *)a1 + 68))(a1, &hdcDest);
  if ( !v18 )
  {
    StretchBlt(hdcDest, 0, 0, v13[3], v13[2], CompatibleDC, a4, ySrc, wSrc, v12, 0xCC0020u);
    (*(void (__stdcall **)(int, HDC))(*(_DWORD *)a1 + 104))(a1, hdcDest);
  }
  DeleteDC(CompatibleDC);
  return v18;
}

//----- (00486CE0) --------------------------------------------------------
int  Surface_BuildPaletteFromBitmap(int a1, const CHAR *a2)
{
  int v4; // ebx
  int v5; // ecx
  __int64 v6; // rtt
  HRSRC ResourceA; // eax
  HGLOBAL Resource; // eax
  _DWORD *v10; // esi
  _BYTE *v11; // edx
  int v12; // esi
  int v13; // ecx
  _BYTE *v14; // eax
  unsigned __int16 v15; // ax
  HFILE v16; // ebx
  int v17; // esi
  int v18; // eax
  char v19; // dl
  _BYTE v20[4]; // [esp+0h] [ebp-458h]
  char v21[1024]; // [esp+4h] [ebp-454h] BYREF
  _DWORD v22[3]; // [esp+404h] [ebp-54h] BYREF
  unsigned __int16 v23; // [esp+412h] [ebp-46h]
  int v24; // [esp+424h] [ebp-34h]
  _BYTE Buffer[16]; // [esp+42Ch] [ebp-2Ch] BYREF
  int v26; // [esp+43Ch] [ebp-1Ch] BYREF
  int v27; // [esp+440h] [ebp-18h]

  v4 = 0;
  v5 = 0;
  do
  {
    v21[v5] = 255 * ((v4 >> 5) & 7) / 7;
    v27 = 3;
    v21[v5 + 1] = 255 * ((v4 >> 2) & 7) / 7;
    LODWORD(v6) = 255 * (v4 & 3);
    HIDWORD(v6) = (v4 & 3u) / 0x808081;
    v5 += 4;
    v20[v5 + 2] = v6 / v27;
    ++v4;
    v20[v5 + 3] = 0;
  }
  while ( v4 < 256 );
  if ( a2 && (ResourceA = FindResourceA(0, a2, (LPCSTR)2)) != 0 )
  {
    Resource = LoadResource(0, ResourceA);
    v10 = LockResource(Resource);
    if ( !v10 )
      OutputDebugStringA(aLockResourceFa);
    v11 = (char *)v10 + *v10;
    if ( *v10 < 0x28u || (v15 = *((_WORD *)v10 + 7), v15 > 8u) )
    {
      v12 = 0;
    }
    else if ( v10[8] )
    {
      v12 = v10[8];
    }
    else
    {
      v12 = 1 << v15;
    }
    v13 = 0;
    if ( v12 > 0 )
    {
      v14 = v11;
      do
      {
        v21[4 * v13] = v14[2];
        v21[4 * v13++ + 1] = v14[1];
        v20[4 * v13 + 2] = *v14;
        v14 += 4;
        v20[4 * v13 + 3] = 0;
      }
      while ( v13 < v12 );
    }
  }
  else if ( a2 )
  {
    v16 = lopen(a2, 0);
    if ( v16 != -1 )
    {
      lread(v16, Buffer, 0xEu);
      lread(v16, v22, 0x28u);
      lread(v16, v21, 0x400u);
      lclose(v16);
      if ( v22[0] == 40 && v23 <= 8u )
        v17 = v24 ? v24 : 1 << v23;
      else
        v17 = 0;
      if ( v17 > 0 )
      {
        v18 = 0;
        do
        {
          v18 += 4;
          v19 = v20[v18];
          v20[v18] = v20[v18 + 2];
          v20[v18 + 2] = v19;
        }
        while ( v18 < 4 * v17 );
      }
    }
  }
  (*(void (__stdcall **)(int, int, char *, int *, _DWORD))(*(_DWORD *)a1 + 20))(a1, 4, v21, &v26, 0);
  return v26;
}
// 486CE0: too many cbuild loops

//----- (00486F00) --------------------------------------------------------
int  Surface_MatchColorToNativePixel(int a1, COLORREF a2, COLORREF Pixel)
{
  int v5; // esi
  int v6; // eax
  _DWORD v8[21]; // [esp+0h] [ebp-84h] BYREF
  char v9; // [esp+54h] [ebp-30h]
  HDC hdc[6]; // [esp+6Ch] [ebp-18h] BYREF

  v5 = -1;
  if ( a2 != -1 && !(*(int (__stdcall **)(int, HDC *))(*(_DWORD *)a1 + 68))(a1, hdc) )
  {
    Pixel = GetPixel(hdc[0], 0, 0);
    SetPixel(hdc[0], 0, 0, a2);
    (*(void (__stdcall **)(int, HDC))(*(_DWORD *)a1 + 104))(a1, hdc[0]);
  }
  v8[0] = 108;
  do
    v6 = (*(int (__stdcall **)(int, _DWORD, _DWORD *, _DWORD, _DWORD))(*(_DWORD *)a1 + 100))(a1, 0, v8, 0, 0);
  while ( v6 == -2005532132 );
  if ( !v6 )
  {
    v5 = ((1 << v9) - 1) & *(_DWORD *)v8[9];
    (*(void (__stdcall **)(int, _DWORD))(*(_DWORD *)a1 + 128))(a1, 0);
  }
  if ( a2 == -1 || (*(int (__stdcall **)(int, HDC *))(*(_DWORD *)a1 + 68))(a1, hdc) )
    return v5;
  SetPixel(hdc[0], 0, 0, Pixel);
  (*(void (__stdcall **)(int, HDC))(*(_DWORD *)a1 + 104))(a1, hdc[0]);
  return v5;
}

//----- (00487002) --------------------------------------------------------
int __fastcall CRT_RunRegisteredFinalizers(int a1, __lock *a2)
{
  int result; // eax
  int v3; // edx
  __lock *v4; // [esp-8h] [ebp-8h]
  __lock *v5; // [esp-8h] [ebp-8h]

  v4 = a2;
  while ( 1 )
  {
    __lock_p(v4);
    if ( g_CrtFinalizerListHead )
      g_CrtFinalizerListHead = *(_DWORD *)g_CrtFinalizerListHead;
    __lock_v(v5);
    if ( !v3 )
      break;
    (*(void (**)(void))(*(_DWORD *)(v3 + 4) + 4))();
  }
  return result;
}
// 487009: variable 'v4' is possibly undefined
// 487024: variable 'v5' is possibly undefined
// 48702B: variable 'v3' is possibly undefined
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (0048703D) --------------------------------------------------------
int  CRT_RegisterFinalizer(int a1, __lock *a2, int a3)
{
  _DWORD *v3; // edx
  int result; // eax
  __lock *v6; // [esp-4h] [ebp-4h]

  g_CrtThreadDataAccessor(a3, a1);
  __lock_p(a2);
  *v3 = g_CrtFinalizerListHead;
  g_CrtFinalizerListHead = (int)v3;
  __lock_v(v6);
  return result;
}
// 487055: variable 'v3' is possibly undefined
// 487062: variable 'v6' is possibly undefined
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (00487069) --------------------------------------------------------
int  CRT_PrintfFormatEngine(int a1, _BYTE *a2, void (*a3)(void), int *a4)
{
  char *v6; // edi
  char v7; // al
  int v8; // edx
  _DWORD *v9; // edx
  int v10; // eoff
  int v11; // eax
  _DWORD *v12; // edx
  int v13; // edi
  int v14; // ecx
  int v15; // ebx
  _WORD *v16; // edx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  unsigned __int16 *v20; // edi
  __int16 v21; // dx
  unsigned __int8 *v22; // ebx
  int v24; // [esp+0h] [ebp-80h] BYREF
  int v25; // [esp+4h] [ebp-7Ch]
  int v26; // [esp+10h] [ebp-70h]
  char v27; // [esp+15h] [ebp-6Bh]
  char v28; // [esp+16h] [ebp-6Ah]
  __int16 v29; // [esp+1Ch] [ebp-64h]
  __int16 v30; // [esp+1Eh] [ebp-62h]
  int v31; // [esp+20h] [ebp-60h]
  int v32; // [esp+24h] [ebp-5Ch]
  int v33; // [esp+28h] [ebp-58h]
  int v34; // [esp+2Ch] [ebp-54h]
  int v35; // [esp+30h] [ebp-50h]
  int v36; // [esp+34h] [ebp-4Ch]
  unsigned __int8 v37[40]; // [esp+38h] [ebp-48h] BYREF
  int v38; // [esp+60h] [ebp-20h] BYREF
  int v39; // [esp+64h] [ebp-1Ch] BYREF
  _BYTE *v40; // [esp+68h] [ebp-18h]
  char v41; // [esp+6Ch] [ebp-14h]

  v24 = a1;
  v41 = 0;
  v40 = a2;
  v30 = 0;
  v29 = 100;
  v26 = 0;
  while ( *v40 )
  {
    if ( *v40 == 37 )
    {
      v38 = *a4;
      v6 = CRT_ParseWidthPrecisionSpec(v40 + 1, &v38, (int)&v24);
      *a4 = v38;
      v7 = *v6;
      v27 = v7;
      v40 = v6 + 1;
      if ( !v7 )
        return v26;
      if ( v7 == 110 )
      {
        if ( (v30 & 0x20) != 0 )
        {
          if ( (v30 & 0x80u) != 0 )
          {
            v8 = *a4 + 8;
            *a4 = v8;
            v10 = v8 - 8;
            v9 = *(_DWORD **)(v8 - 8);
            __ES__ = *(_WORD *)(v10 + 4);
            goto LABEL_7;
          }
          if ( (v30 & 0x40) != 0 )
          {
            v11 = *a4 + 4;
            *a4 = v11;
            v12 = *(_DWORD **)(v11 - 4);
            goto LABEL_11;
          }
LABEL_10:
          v13 = *a4 + 4;
          *a4 = v13;
          v12 = *(_DWORD **)(v13 - 4);
          goto LABEL_11;
        }
        if ( (v30 & 0x10) != 0 )
        {
          if ( (v30 & 0x80u) == 0 )
          {
            if ( (v30 & 0x40) != 0 )
            {
              v15 = *a4 + 4;
              *a4 = v15;
              v16 = *(_WORD **)(v15 - 4);
            }
            else
            {
              v17 = *a4 + 4;
              *a4 = v17;
              v16 = *(_WORD **)(v17 - 4);
            }
            *v16 = v26;
          }
          else
          {
            v14 = *a4 + 8;
            *a4 = v14;
            *(_DWORD *)MK_FP(*(_WORD *)(v14 - 8 + 4), *(_DWORD *)(v14 - 8)) = v26;
          }
        }
        else if ( (v30 & 0x80u) == 0 )
        {
          if ( (v30 & 0x40) != 0 )
            goto LABEL_10;
          v19 = *a4 + 4;
          *a4 = v19;
          v12 = *(_DWORD **)(v19 - 4);
LABEL_11:
          *v12 = v26;
        }
        else
        {
          v18 = *a4 + 8;
          *a4 = v18;
          v9 = *(_DWORD **)(v18 - 8);
          __ES__ = *(_WORD *)(v18 - 8 + 4);
LABEL_7:
          *v9 = v26;
        }
      }
      else
      {
        v39 = *a4;
        v20 = CRT_ConvertPrintfArgument(v37, &v39, (int)&v24);
        __ES__ = v21;
        *a4 = v39;
        v25 -= v36 + v35 + v34 + v33 + v32 + v31;
        if ( (v30 & 8) == 0 && v28 == 32 )
        {
          while ( v25 > 0 )
          {
            a3();
            --v25;
          }
        }
        v22 = v37;
        while ( v31 > 0 )
        {
          a3();
          ++v22;
          --v31;
        }
        while ( v32 > 0 )
        {
          a3();
          --v32;
        }
        if ( v27 == 115 )
        {
          if ( (v30 & 0x20) != 0 )
            goto LABEL_37;
          while ( v33 > 0 )
          {
            a3();
            v20 = (unsigned __int16 *)((char *)v20 + 1);
            --v33;
          }
        }
        else
        {
          if ( v27 == 83 )
          {
LABEL_37:
            CRT_OutputWideStringAsMultiByte(v20, __ES__, (unsigned __int8 *)a3, (int)&v24);
            goto LABEL_43;
          }
          while ( v33 > 0 )
          {
            ((void (__cdecl *)(int))a3)(v24);
            v20 = (unsigned __int16 *)((char *)v20 + 1);
            --v33;
          }
        }
LABEL_43:
        while ( v34 > 0 )
        {
          a3();
          --v34;
        }
        while ( v35 > 0 )
        {
          a3();
          v20 = (unsigned __int16 *)((char *)v20 + 1);
          --v35;
        }
        while ( v36 > 0 )
        {
          a3();
          --v36;
        }
        if ( (v30 & 8) != 0 )
        {
          while ( v25 > 0 )
          {
            a3();
            --v25;
          }
        }
      }
    }
    else
    {
      ++v40;
      a3();
    }
  }
  return v26;
}
// 4871CA: variable 'v21' is possibly undefined

//----- (0048732A) --------------------------------------------------------
char * CRT_ParseWidthPrecisionSpec(char *a1, int *a2, int a3)
{
  char *result; // eax
  int v5; // edx
  int v6; // edx
  char v7; // ch
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  char v12; // dl

  *(_BYTE *)(a3 + 22) = 32;
  result = CRT_ParsePrintfFlags(a1, a3);
  *(_DWORD *)(a3 + 4) = 0;
  if ( *result == 42 )
  {
    v5 = *a2 + 4;
    *a2 = v5;
    v6 = *(_DWORD *)(v5 - 4);
    *(_DWORD *)(a3 + 4) = v6;
    if ( v6 < 0 )
    {
      v7 = *(_BYTE *)(a3 + 30) | 8;
      *(_DWORD *)(a3 + 4) = -v6;
      *(_BYTE *)(a3 + 30) = v7;
    }
    ++result;
  }
  else
  {
    while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
    {
      v8 = (unsigned __int8)*result++ - 48;
      *(_DWORD *)(a3 + 4) = v8 + 10 * *(_DWORD *)(a3 + 4);
    }
  }
  *(_DWORD *)(a3 + 8) = -1;
  if ( *result == 46 )
  {
    ++result;
    *(_DWORD *)(a3 + 8) = 0;
    if ( *result == 42 )
    {
      v9 = *a2 + 4;
      *a2 = v9;
      v10 = *(_DWORD *)(v9 - 4);
      *(_DWORD *)(a3 + 8) = v10;
      if ( v10 < 0 )
        *(_DWORD *)(a3 + 8) = -1;
      ++result;
    }
    else
    {
      while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
      {
        v11 = (unsigned __int8)*result++ - 48;
        *(_DWORD *)(a3 + 8) = v11 + 10 * *(_DWORD *)(a3 + 8);
      }
    }
    if ( *(_DWORD *)(a3 + 8) != -1 )
      *(_BYTE *)(a3 + 22) = 32;
  }
  v12 = *result;
  if ( (unsigned __int8)*result >= 0x4Eu )
  {
    if ( (unsigned __int8)*result <= 0x4Eu )
    {
      *(_BYTE *)(a3 + 30) |= 0x40u;
    }
    else
    {
      if ( (unsigned __int8)v12 >= 0x6Cu )
      {
        if ( (unsigned __int8)v12 <= 0x6Cu || v12 == 119 )
        {
          ++result;
          *(_BYTE *)(a3 + 30) |= 0x20u;
        }
        return result;
      }
      if ( v12 != 104 )
        return result;
      *(_BYTE *)(a3 + 30) |= 0x10u;
    }
    return ++result;
  }
  if ( (unsigned __int8)v12 < 0x49u )
  {
    if ( v12 != 70 )
      return result;
    *(_BYTE *)(a3 + 30) |= 0x80u;
    return ++result;
  }
  if ( (unsigned __int8)v12 <= 0x49u )
  {
    if ( result[1] == 54 && result[2] == 52 )
    {
      result += 3;
      *(_BYTE *)(a3 + 31) |= 1u;
    }
  }
  else if ( v12 == 76 )
  {
    ++result;
    *(_BYTE *)(a3 + 31) |= 1u;
  }
  return result;
}

//----- (00487477) --------------------------------------------------------
char * CRT_ParsePrintfFlags(char *result, int a2)
{
  char v2; // bl
  char v3; // ch
  char v4; // bh

  *(_WORD *)(a2 + 30) = 0;
  while ( 1 )
  {
    v2 = *result;
    if ( *result == 45 )
    {
      *(_BYTE *)(a2 + 30) |= 8u;
      goto LABEL_13;
    }
    if ( v2 == 35 )
    {
      *(_BYTE *)(a2 + 30) |= 1u;
      goto LABEL_13;
    }
    if ( v2 == 43 )
    {
      v3 = *(_BYTE *)(a2 + 30) | 4;
      *(_BYTE *)(a2 + 30) = v3;
      *(_BYTE *)(a2 + 30) = v3 & 0xFD;
      goto LABEL_13;
    }
    if ( v2 != 32 )
      break;
    v4 = *(_BYTE *)(a2 + 30);
    if ( (v4 & 4) == 0 )
      *(_BYTE *)(a2 + 30) = v4 | 2;
LABEL_13:
    ++result;
  }
  if ( v2 == 48 )
  {
    *(_BYTE *)(a2 + 22) = 48;
    goto LABEL_13;
  }
  return result;
}

//----- (004874D4) --------------------------------------------------------
int  CRT_FarStrLenBounded(int a1, __int16 a2, int a3)
{
  int result; // eax
  char v7; // bl

  for ( result = 0; ; ++result )
  {
    v7 = *(_BYTE *)MK_FP(a2, a1++);
    if ( !v7 || result == a3 )
      break;
  }
  return result;
}

//----- (004874F8) --------------------------------------------------------
int  CRT_WideCharToMultiByteLenBounded(unsigned __int16 *a1, __int16 a2, int a3)
{
  int v6; // ecx
  unsigned __int16 v7; // dx
  int v8; // eax
  int v10; // eax

  __ES__ = a2;
  v6 = 0;
  if ( a3 == -1 )
  {
    while ( *a1 )
    {
      v7 = *a1++;
      v8 = wctomb_(v6, v7);
      if ( v8 != -1 )
        v6 += v8;
    }
    return v6;
  }
  while ( *a1 && v6 <= a3 )
  {
    v10 = wctomb_(v6, *a1++);
    if ( v10 != -1 )
      v6 += v10;
  }
  if ( v6 <= a3 )
    return v6;
  return a3;
}
// 48751E: variable 'v6' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);

//----- (00487561) --------------------------------------------------------
int  CRT_FormatPaddedHexDigits(signed int a1, char *a2, int a3)
{
  int result; // eax
  char *v6; // edx
  char *v7; // ebx
  char *v8; // edx

  Str_FormatSignedRadixDigits(a1, a2, 0x10u);
  result = a3 - 1;
  v6 = &a2[strlen(a2)];
  v7 = &a2[a3 - 1];
  while ( v6 != a2 )
  {
    --v6;
    --result;
    *v7-- = *v6;
  }
  v8 = &a2[result];
  while ( result >= 0 )
  {
    --result;
    *v8-- = 48;
  }
  a2[a3] = 0;
  return result;
}

//----- (004875BF) --------------------------------------------------------
char  CRT_FormatFixedDecimal(char *a1, int a2, int a3)
{
  char *v3; // ecx
  _BYTE *v5; // eax
  _BYTE *v6; // ecx
  _BYTE *v7; // ebx
  _BYTE *v8; // ecx
  int v10; // [esp+0h] [ebp-10h]

  v3 = a1;
  v10 = a2;
  if ( a2 < 0 )
  {
    v3 = a1 + 1;
    *a1 = 45;
    v10 = -a2;
  }
  if ( *(_DWORD *)(a3 + 8) == -1 )
    *(_DWORD *)(a3 + 8) = 4;
  LOBYTE(v5) = Str_FormatSignedRadixDigits(HIWORD(v10), v3, 0xAu);
  v7 = v6;
  while ( *v6 )
    ++v6;
  if ( *(_DWORD *)(a3 + 8) )
  {
    *v6 = 46;
    v5 = 0;
    ++v6;
    while ( (int)v5 < *(_DWORD *)(a3 + 8) )
    {
      v10 = 10 * (unsigned __int16)v10;
      ++v5;
      *v6++ = BYTE2(v10) + 48;
    }
    *v6 = 0;
  }
  if ( (v10 & 0x8000) != 0 )
  {
    while ( v6 != v7 )
    {
      if ( *--v6 == 46 )
        --v6;
      LOBYTE(v5) = *v6;
      if ( *v6 != 57 )
      {
        *v6 = (_BYTE)v5 + 1;
        return (char)v5;
      }
      *v6 = 48;
    }
    v8 = v7 + 1;
    *v7 = 49;
    while ( 1 )
    {
      v5 = v8 + 1;
      if ( *v8 != 48 )
        break;
      ++v8;
    }
    if ( *v8 == 46 )
    {
      *v8 = 48;
      v8 += 2;
      *v5 = 46;
      while ( *v8 == 48 )
        ++v8;
    }
    *v8 = 48;
    v8[1] = 0;
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
        __int16 a2,
        unsigned __int8 *a3,
        int a4)
{
  unsigned __int16 *v4; // esi
  void (__fastcall *v5)(unsigned __int8 *, _DWORD); // ebp
  int v6; // edi
  int v7; // ecx
  int v8; // [esp+0h] [ebp-14h] BYREF

  __ES__ = a2;
  v4 = result;
  v5 = (void (__fastcall *)(unsigned __int8 *, _DWORD))a3;
  while ( *(int *)(a4 + 40) > 0 )
  {
    result = (unsigned __int16 *)wctomb_(a3, *v4++);
    v6 = (int)result;
    if ( result != (unsigned __int16 *)-1 )
    {
      if ( (int)result > *(_DWORD *)(a4 + 40) )
      {
        *(_DWORD *)(a4 + 40) = 0;
        return result;
      }
      a3 = (unsigned __int8 *)&v8;
      while ( --v6 != -1 )
      {
        v5(a3, *a3);
        result = (unsigned __int16 *)(*(_DWORD *)(a4 + 40) - 1);
        a3 = (unsigned __int8 *)(v7 + 1);
        *(_DWORD *)(a4 + 40) = result;
      }
    }
  }
  return result;
}
// 4876FF: variable 'a3' is possibly undefined
// 487727: variable 'v7' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);

//----- (0048773C) --------------------------------------------------------
unsigned __int16 * CRT_ConvertPrintfArgument(unsigned __int8 *a1, int *a2, int a3)
{
  int v4; // ecx
  unsigned __int16 *v5; // edi
  unsigned __int8 v6; // al
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
  unsigned __int8 v23; // al
  bool v24; // zf
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  int v28; // ecx
  char v29; // al
  int v30; // ebp
  int v31; // esi
  unsigned __int16 *v32; // eax
  int v33; // ebx
  int v34; // eax
  int v35; // ecx
  int v36; // edx
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // eax
  signed int v45; // ebp
  int v46; // eax
  char *v47; // edx
  signed int v48; // eax
  int v49; // ecx
  int v50; // eax
  int v51; // ecx
  char v52; // bl
  int v53; // ebx
  int v54; // ecx
  int v55; // ebp
  int v56; // eax
  int v57; // ebp
  int v59; // [esp+0h] [ebp-20h]
  __int64 v60; // [esp+4h] [ebp-1Ch]
  unsigned __int8 v61; // [esp+Ch] [ebp-14h]
  unsigned __int8 v62; // [esp+Dh] [ebp-13h]

  v4 = a3;
  __ES__ = __DS__;
  *(_DWORD *)(a3 + 32) = 0;
  *(_DWORD *)(a3 + 36) = 0;
  *(_DWORD *)(a3 + 40) = 0;
  *(_DWORD *)(a3 + 44) = 0;
  *(_DWORD *)(a3 + 48) = 0;
  v5 = (unsigned __int16 *)a1;
  v6 = *(_BYTE *)(a3 + 21);
  *(_DWORD *)(a3 + 52) = 0;
  if ( v6 < 0x69u )
  {
    if ( v6 < 0x58u )
      goto LABEL_42;
    if ( v6 <= 0x58u )
      goto LABEL_13;
    if ( v6 != 100 )
      goto LABEL_42;
  }
  else if ( v6 > 0x69u )
  {
    if ( v6 < 0x75u )
    {
      v7 = v6 == 111;
LABEL_6:
      if ( !v7 )
        goto LABEL_42;
      goto LABEL_13;
    }
    if ( v6 > 0x75u )
    {
      v7 = v6 == 120;
      goto LABEL_6;
    }
LABEL_13:
    if ( (*(_BYTE *)(a3 + 31) & 1) == 0 )
    {
      if ( (*(_BYTE *)(a3 + 30) & 0x20) != 0 )
      {
        v11 = *a2 + 4;
        *a2 = v11;
        v12 = *(_DWORD *)(v11 - 4);
      }
      else
      {
        v13 = *a2 + 4;
        *a2 = v13;
        HIDWORD(v60) = *(_DWORD *)(v13 - 4);
        if ( (*(_BYTE *)(a3 + 30) & 0x10) == 0 )
          goto LABEL_42;
        v12 = WORD2(v60);
      }
      HIDWORD(v60) = v12;
      goto LABEL_42;
    }
    v8 = *a2 + 4;
    *a2 = v8;
    v59 = *(_DWORD *)(v8 - 4);
    v9 = *a2 + 4;
    *a2 = v9;
    v10 = *(_DWORD *)(v9 - 4);
    goto LABEL_15;
  }
  if ( (*(_BYTE *)(a3 + 31) & 1) == 0 )
  {
    if ( (*(_BYTE *)(a3 + 30) & 0x20) != 0 )
    {
      v16 = *a2 + 4;
      *a2 = v16;
      v17 = *(_DWORD *)(v16 - 4);
    }
    else
    {
      v18 = *a2 + 4;
      *a2 = v18;
      HIDWORD(v60) = *(_DWORD *)(v18 - 4);
      if ( (*(_BYTE *)(v4 + 30) & 0x10) == 0 )
        goto LABEL_28;
      v17 = *(int *)((char *)&v60 + 2) >> 16;
    }
    HIDWORD(v60) = v17;
    goto LABEL_28;
  }
  v14 = *a2 + 4;
  *a2 = v14;
  v59 = *(_DWORD *)(v14 - 4);
  v15 = *a2 + 4;
  *a2 = v15;
  LODWORD(v60) = *(_DWORD *)(v15 - 4);
LABEL_28:
  if ( (*(_BYTE *)(v4 + 31) & 1) != 0 )
  {
    if ( (v60 & 0x80000000LL) != 0 )
      goto LABEL_33;
  }
  else if ( v60 < 0 )
  {
LABEL_33:
    v19 = *(_DWORD *)(v4 + 32);
    *(_DWORD *)(v4 + 32) = v19 + 1;
    a1[v19] = 45;
    if ( (*(_BYTE *)(v4 + 31) & 1) == 0 )
    {
      HIDWORD(v60) = -HIDWORD(v60);
      goto LABEL_42;
    }
    v59 = -v59;
    if ( v59 )
      v10 = ~(_DWORD)v60;
    else
      v10 = -(int)v60;
LABEL_15:
    LODWORD(v60) = v10;
    goto LABEL_42;
  }
  v20 = *(_BYTE *)(v4 + 30);
  if ( (v20 & 4) != 0 )
  {
    v21 = *(_DWORD *)(v4 + 32);
    *(_DWORD *)(v4 + 32) = v21 + 1;
    a1[v21] = 43;
  }
  else if ( (v20 & 2) != 0 )
  {
    v22 = *(_DWORD *)(v4 + 32);
    *(_DWORD *)(v4 + 32) = v22 + 1;
    a1[v22] = 32;
  }
LABEL_42:
  v23 = *(_BYTE *)(v4 + 21);
  if ( v23 >= 0x64u )
  {
    if ( v23 <= 0x64u )
      goto LABEL_104;
    if ( v23 >= 0x6Fu )
    {
      if ( v23 <= 0x6Fu )
        goto LABEL_101;
      if ( v23 >= 0x73u )
      {
        if ( v23 > 0x73u )
        {
          if ( v23 >= 0x75u )
          {
            if ( v23 <= 0x75u )
              goto LABEL_104;
            if ( v23 != 120 )
              goto LABEL_139;
LABEL_94:
            if ( (*(_BYTE *)(v4 + 30) & 1) != 0 )
            {
              if ( (*(_BYTE *)(v4 + 31) & 1) != 0 )
              {
                if ( v59 || (_DWORD)v60 )
                  goto LABEL_100;
              }
              else if ( HIDWORD(v60) )
              {
LABEL_100:
                v37 = *(_DWORD *)(v4 + 32);
                *(_DWORD *)(v4 + 32) = v37 + 1;
                a1[v37] = 48;
                v38 = *(_DWORD *)(v4 + 32);
                *(_DWORD *)(v4 + 32) = v38 + 1;
                a1[v38] = *(_BYTE *)(v4 + 21);
              }
            }
LABEL_101:
            if ( *(_BYTE *)(v4 + 21) == 111 && (*(_BYTE *)(v4 + 30) & 1) != 0 )
            {
              v39 = *(_DWORD *)(v4 + 32);
              *(_DWORD *)(v4 + 32) = v39 + 1;
              a1[v39] = 48;
            }
            goto LABEL_104;
          }
LABEL_139:
          *(_DWORD *)(v4 + 4) = 0;
          *a1 = *(_BYTE *)(v4 + 21);
          *(_DWORD *)(v4 + 32) = 1;
          return v5;
        }
LABEL_77:
        *a1 = 0;
        v29 = *(_BYTE *)(v4 + 30);
        if ( v29 >= 0 )
        {
          if ( (v29 & 0x40) != 0 )
          {
            v31 = *a2 + 4;
            *a2 = v31;
            v32 = *(unsigned __int16 **)(v31 - 4);
            if ( !v32 )
              goto LABEL_86;
          }
          else
          {
            v33 = *a2 + 4;
            *a2 = v33;
            v32 = *(unsigned __int16 **)(v33 - 4);
            if ( !v32 )
              goto LABEL_86;
          }
          v5 = v32;
          __ES__ = __DS__;
        }
        else
        {
          v30 = *a2 + 8;
          *a2 = v30;
          if ( *(_DWORD *)(v30 - 8) || *(_WORD *)(v30 - 4) )
          {
            __ES__ = *(_WORD *)(v30 - 4);
            v5 = *(unsigned __int16 **)(v30 - 8);
          }
        }
LABEL_86:
        if ( *(_BYTE *)(v4 + 21) == 83 )
        {
          if ( (*(_BYTE *)(v4 + 30) & 0x10) == 0 )
          {
LABEL_88:
            v34 = CRT_WideCharToMultiByteLenBounded(v5, __ES__, *(_DWORD *)(v4 + 8));
LABEL_91:
            v36 = *(_DWORD *)(v35 + 8);
            *(_DWORD *)(v35 + 40) = v34;
            if ( v36 >= 0 && v34 > v36 )
              *(_DWORD *)(v35 + 40) = v36;
            return v5;
          }
        }
        else if ( (*(_BYTE *)(v4 + 30) & 0x20) != 0 )
        {
          goto LABEL_88;
        }
        v34 = CRT_FarStrLenBounded((int)v5, __ES__, *(_DWORD *)(v4 + 8));
        goto LABEL_91;
      }
      v24 = v23 == 112;
      goto LABEL_53;
    }
    if ( v23 >= 0x66u )
    {
      if ( v23 > 0x66u )
      {
        if ( v23 > 0x67u )
        {
          if ( v23 != 105 )
            goto LABEL_139;
LABEL_104:
          v5 = (unsigned __int16 *)&a1[*(_DWORD *)(v4 + 32)];
          if ( (*(_BYTE *)(v4 + 31) & 1) != 0 )
          {
            if ( !*(_DWORD *)(v4 + 8) && !v59 && !(_DWORD)v60 )
            {
LABEL_108:
              a1[*(_DWORD *)(v4 + 32)] = 0;
              v40 = 0;
LABEL_116:
              *(_DWORD *)(v4 + 40) = v40;
              v42 = v40;
              v43 = *(_DWORD *)(v4 + 8);
              if ( v42 < v43 )
                *(_DWORD *)(v4 + 36) = v43 - v42;
              if ( *(_DWORD *)(v4 + 8) == -1 )
                CRT_ApplyZeroPadWidth(v4);
              return v5;
            }
            _clib_ulltoa_(v4, &a1[*(_DWORD *)(v4 + 32)]);
            if ( *(_BYTE *)(v41 + 21) == 88 )
              goto LABEL_114;
          }
          else
          {
            if ( !*(_DWORD *)(v4 + 8) && !HIDWORD(v60) )
              goto LABEL_108;
            CRT_SignedLongToDecimalString(v4, &a1[*(_DWORD *)(v4 + 32)]);
            if ( *(_BYTE *)(v41 + 21) == 88 )
LABEL_114:
              CRT_ToUpperInPlace(a1, v41);
          }
          v40 = CRT_FarStrLenBounded((int)v5, __DS__, -1);
          goto LABEL_116;
        }
        goto LABEL_76;
      }
LABEL_74:
      if ( (*(_BYTE *)(v4 + 30) & 0x10) != 0 )
      {
        v25 = *a2 + 4;
        *a2 = v25;
        CRT_FormatFixedDecimal((char *)a1, *(_DWORD *)(v25 - 4), v4);
        v26 = CRT_FarStrLenBounded((int)a1, __DS__, '\xFF');
        *(_DWORD *)(v27 + 40) = v26;
        return v5;
      }
    }
LABEL_76:
    CRT_DispatchFloatFormat();
    CRT_ApplyZeroPadWidth(v28);
    return (unsigned __int16 *)(a1 + 1);
  }
  if ( v23 < 0x47u )
  {
    if ( v23 < 0x45u )
    {
      if ( v23 != 67 )
        goto LABEL_139;
      v57 = *a2 + 4;
      *a2 = v57;
      v50 = wctomb_(v4, *(unsigned __int16 *)(v57 - 4));
      if ( v50 == -1 )
      {
        *(_DWORD *)(v51 + 32) = 0;
        return v5;
      }
      goto LABEL_130;
    }
    if ( v23 > 0x45u )
      goto LABEL_74;
    goto LABEL_76;
  }
  if ( v23 <= 0x47u )
    goto LABEL_76;
  if ( v23 < 0x53u )
  {
    v24 = v23 == 80;
LABEL_53:
    if ( !v24 )
      goto LABEL_139;
    if ( !*(_DWORD *)(v4 + 4) )
    {
      if ( *(char *)(v4 + 30) >= 0 )
        *(_DWORD *)(v4 + 4) = 8;
      else
        *(_DWORD *)(v4 + 4) = 13;
    }
    *(_BYTE *)(v4 + 30) &= 0xF9u;
    v44 = *a2 + 4;
    *a2 = v44;
    v45 = *(_DWORD *)(v44 - 4);
    if ( *(char *)(v4 + 30) >= 0 )
    {
      v47 = (char *)a1;
      v48 = *(_DWORD *)(v44 - 4);
    }
    else
    {
      v46 = v44 + 4;
      *a2 = v46;
      CRT_FormatPaddedHexDigits((unsigned __int16)*(_DWORD *)(v46 - 4), (char *)a1, 4);
      v47 = (char *)(a1 + 5);
      v48 = v45;
      a1[4] = 58;
    }
    CRT_FormatPaddedHexDigits(v48, v47, 8);
    if ( *(_BYTE *)(v49 + 21) == 80 )
      CRT_ToUpperInPlace(a1, v49);
    v50 = CRT_FarStrLenBounded((int)a1, __DS__, -1);
LABEL_130:
    *(_DWORD *)(v51 + 32) = v50;
    return v5;
  }
  if ( v23 <= 0x53u )
    goto LABEL_77;
  if ( v23 < 0x58u )
    goto LABEL_139;
  if ( v23 <= 0x58u )
    goto LABEL_94;
  if ( v23 != 99 )
    goto LABEL_139;
  v52 = *(_BYTE *)(v4 + 30);
  *(_DWORD *)(v4 + 32) = 1;
  if ( (v52 & 0x20) != 0 )
  {
    v53 = *a2 + 4;
    *a2 = v53;
    if ( wctomb_(v4, *(unsigned __int16 *)(v53 - 4)) != -1 )
    {
      v55 = g_CRT_MbcsCodePageActive;
      *a1 = v61;
      if ( v55 )
      {
        if ( (g_Clips_DbcsLeadByteTable[v61] & 1) != 0 )
        {
          a1[1] = v62;
          ++*(_DWORD *)(v54 + 32);
        }
      }
    }
  }
  else
  {
    v56 = *a2 + 4;
    *a2 = v56;
    *a1 = *(_BYTE *)(v56 - 4);
  }
  return v5;
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
unsigned int  CRT_OpenFile(DWORD a1, const CHAR *a2, int a3)
{
  return CRT_OpenFileShared(a1, a2, a3, 0);
}

//----- (004881A1) --------------------------------------------------------
unsigned int  CRT_OpenFileShared(DWORD a1, const CHAR *a2, int a3, int a4)
{
  return CRT_CreateFileHandleFromPath(a2, a3, a4, a1);
}

//----- (004881C8) --------------------------------------------------------
unsigned int  CRT_CreateFileHandleFromPath(const CHAR *a1, int a2, int a3, DWORD a4)
{
  char v5; // dl
  int v7; // esi
  DWORD v8; // ebx
  int *v9; // ecx
  unsigned int v10; // edi
  int v11; // ebp
  DWORD v12; // eax
  HANDLE FileA; // ecx
  void *v14; // ecx
  struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+0h] [ebp-2Ch] BYREF
  DWORD dwShareMode; // [esp+Ch] [ebp-20h] BYREF
  DWORD dwDesiredAccess; // [esp+10h] [ebp-1Ch] BYREF
  int v18; // [esp+14h] [ebp-18h] BYREF
  int v19; // [esp+18h] [ebp-14h]
  int v20; // [esp+1Ch] [ebp-10h]

  v20 = a2;
  v19 = a3;
  if ( _NTAtMaxFiles_() )
    goto LABEL_2;
  v7 = v5 & 7;
  CRT_MapAccessModeToCreateFileFlags(v7, &dwDesiredAccess, &v18);
  v8 = 128;
  CRT_MapOpenFlagsToCreationDisposition(v7 | v19, &dwShareMode);
  SecurityAttributes.lpSecurityDescriptor = 0;
  SecurityAttributes.nLength = 12;
  SecurityAttributes.bInheritHandle = (v20 & 0x80u) == 0;
  if ( g_CRT_ConsoleOpenHook && !stricmp_(v9, aCon_0) )
  {
    _NTGetFakeHandle_(
      SecurityAttributes.nLength,
      SecurityAttributes.lpSecurityDescriptor,
      SecurityAttributes.bInheritHandle);
    v10 = g_CRT_AddFileHandleHook();
    g_CRT_ConsoleOpenHook(0, v10, -1);
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
      v8 = 1;
    if ( (v20 & 0x400) != 0 )
    {
      a4 = 1;
      v12 = 1;
      goto LABEL_18;
    }
    if ( (v20 & 0x40) != 0 )
    {
      a4 = 2;
LABEL_14:
      v12 = 5;
      goto LABEL_18;
    }
    a4 = 4;
  }
  else if ( (v20 & 0x40) != 0 )
  {
    goto LABEL_14;
  }
  v12 = 3;
LABEL_18:
  FileA = CreateFileA(a1, dwDesiredAccess, dwShareMode, &SecurityAttributes, v12, v8, 0);
  if ( FileA == (HANDLE)-1 )
  {
    if ( (v20 & 0x20) != 0 )
      FileA = CreateFileA(a1, dwDesiredAccess, dwShareMode, 0, a4, v8, 0);
    if ( FileA == (HANDLE)-1 )
      return _set_errno_nt_(SecurityAttributes.nLength);
  }
  v10 = g_CRT_AddFileHandleHook();
  if ( v10 >= g_CRT_MaxFileDescriptor )
  {
    CloseHandle(v14);
LABEL_2:
    _set_errno_(SecurityAttributes.nLength);
    return -1;
  }
  isatty_(v14, 0);
LABEL_26:
  _SetIOMode_(SecurityAttributes.nLength, SecurityAttributes.lpSecurityDescriptor, SecurityAttributes.bInheritHandle);
  return v10;
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
signed int  CRT_MkTime(_DWORD *a1)
{
  int v2; // esi
  int v3; // edi
  int v5; // esi
  char *v6; // ecx
  int v7; // edi
  int i; // esi
  int v9; // esi
  int v10; // esi

  v2 = a1[5];
  v3 = a1[4] % 12;
  if ( v2 < -184844639 )
    return -1;
  v5 = a1[4] / 12 + v2;
  while ( v3 < 0 )
  {
    --v5;
    v3 += 12;
  }
  if ( v5 < 0 )
    return -1;
  if ( CRT_IsLeapYear(v5 + 1900) )
    v6 = (char *)&g_CRT_LeapMonthDayTable + 2;
  v7 = a1[3]
     + (v5 + 299) / 400
     + ((v5 + 3 - (__CFSHL__((v5 + 3) >> 31, 2) + 4 * ((v5 + 3) >> 31))) >> 2)
     + 365 * v5
     - (v5 + 99) / 100
     + *(__int16 *)&v6[2 * v3]
     - 1;
  for ( i = 60 * (60 * a1[2] + a1[1]) + *a1; i < 0; i += 86400 )
    --v7;
  _brktime_(a1, i);
  CRT_TzSet();
  v9 = g_CRT_TimezoneSeconds + i;
  if ( (int)a1[8] < 0 )
    CRT_IsDaylightTime(a1);
  if ( (int)a1[8] > 0 )
    v9 -= g_CRT_DaylightBiasSeconds;
  while ( v9 < 0 )
  {
    --v7;
    v9 += 86400;
  }
  if ( v7 < 25566 )
    return -1;
  if ( v7 != 25566 )
    return 86400 * (v7 - 25567) + v9;
  v10 = v9 - 86400;
  if ( g_CRT_TimezoneSeconds <= 0 || v10 < 0 )
    return -1;
  return v10;
}
// 488C9B: variable 'v6' is possibly undefined
// 4B6243: using guessed type int __fastcall _brktime_(_DWORD, _DWORD);
// 5110EE: using guessed type int dword_5110EE;
// 511108: using guessed type int dword_511108;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0C2: using guessed type int dword_51B0C2;

//----- (00488DE1) --------------------------------------------------------
int  CRT_PutcCallbackForWrite(_DWORD *a1, int a2)
{
  int result; // eax

  result = CRT_PutcToStream(a2, *a1);
  ++a1[4];
  return result;
}
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (00488DF2) --------------------------------------------------------
int  CRT_VfprintfLockedWrite(int a1, int a2, int *a3)
{
  int lock_key;
  int stream_state;
  int busy_state;
  int saved_mode_bits;
  int flush_after_write;
  int write_result;
  unsigned char stream_flags;

  lock_key = *(_DWORD *)(a1 + 16);
  g_CRT_FileHandleLockAcquireHook(lock_key);
  stream_state = *(_DWORD *)(a1 + 8);
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
  saved_mode_bits = *(_DWORD *)(a1 + 12) & 0x30;
  *(_BYTE *)(a1 + 12) &= 0xCFu;
  if ( !*(_DWORD *)(*(_DWORD *)(a1 + 8) + 8) )
    _ioalloc_();
  flush_after_write = 0;
  if ( (*(_BYTE *)(a1 + 13) & 4) != 0 )
  {
    stream_flags = *(_BYTE *)(a1 + 13) & 0xFA;
    *(_BYTE *)(a1 + 13) = stream_flags;
    *(_BYTE *)(a1 + 13) = stream_flags | 1;
    flush_after_write = 1;
  }
  write_result = CRT_PrintfFormatEngine(a1, (_BYTE *)(uintptr_t)(unsigned int)a2, (void (*)(void))CRT_PutcCallbackForWrite, a3);
  if ( flush_after_write )
  {
    stream_flags = *(_BYTE *)(a1 + 13) & 0xFA;
    *(_BYTE *)(a1 + 13) = stream_flags;
    *(_BYTE *)(a1 + 13) = stream_flags | 4;
    _flush_(a1, write_result);
  }
  if ( (*(_BYTE *)(a1 + 12) & 0x20) != 0 )
    write_result = -1;
  *(_DWORD *)(a1 + 12) |= saved_mode_bits;
  g_CRT_FileHandleLockReleaseHook(lock_key, write_result);
  return write_result;
}
// 4886DD: using guessed type int __fastcall _flush_(_DWORD, _DWORD);
// 488946: using guessed type int _ioalloc_(void);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (00488EB2) --------------------------------------------------------
DWORD  CRT_ReadFileHandle(int a1, int a2, DWORD a3)
{
  void *v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  DWORD NumberOfBytesRead; // [esp+0h] [ebp-Ch] BYREF
  int v12; // [esp+8h] [ebp-4h]

  v12 = a2;
  if ( a1 >= 0 && a1 <= (unsigned int)g_CRT_MaxFileDescriptor )
  {
    g_CRT_FileHandleLockAcquireHook(a2);
    if ( g_CRT_CustomReadHook && g_CRT_CustomReadAvailablePredicateHook() )
    {
      v6 = g_CRT_CustomReadHook();
      g_CRT_FileHandleLockReleaseHook(v7, v6);
      return v8;
    }
    else if ( ReadFile(*(HANDLE *)(g_CRT_OsHandleTable + 4 * a1), v5, a3, &NumberOfBytesRead, 0) )
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
int  CRT_DeleteFile(const CHAR *a1, int a2)
{
  if ( DeleteFileA(a1) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489DAA) --------------------------------------------------------
signed int  CRT_FlushBufferAndPutChar(signed int result, int a2)
{
  signed int v3; // ebx
  unsigned __int8 **v4; // edx
  unsigned __int8 *v5; // eax
  unsigned __int8 *v6; // ecx
  unsigned __int8 *v7; // ebp
  unsigned __int8 *v8; // edi
  unsigned __int8 *v9; // ebp

  v3 = result;
  if ( result != -1 )
  {
    g_CRT_FileHandleLockAcquireHook(a2);
    v5 = v4[2];
    v6 = (unsigned __int8 *)*((_DWORD *)v5 + 3);
    if ( v6 != (unsigned __int8 *)1 )
    {
      if ( v6 )
      {
LABEL_4:
        g_CRT_FileHandleLockReleaseHook(v6, v4);
        return -1;
      }
      *((_DWORD *)v5 + 3) = 1;
    }
    if ( (*((_BYTE *)v4 + 13) & 0x10) != 0 || ((_BYTE)v4[3] & 1) == 0 )
      goto LABEL_4;
    if ( !*((_DWORD *)v4[2] + 2) )
      _ioalloc_();
    v7 = v4[1];
    if ( v7 )
    {
      v6 = *v4;
      if ( *v4 == *((unsigned __int8 **)v4[2] + 2) )
        goto LABEL_4;
      v8 = v7 + 1;
      v9 = *v4;
      v4[1] = v8;
      *v4 = --v9;
      if ( *v9 == v3 )
        goto LABEL_15;
    }
    else
    {
      v4[1] = (unsigned __int8 *)1;
      v6 = v4[5];
      *v4 = &v6[*((_DWORD *)v4[2] + 2) - 1];
    }
    *((_BYTE *)v4 + 12) |= 4u;
LABEL_15:
    **v4 = v3;
    *((_BYTE *)v4 + 12) &= ~0x10u;
    g_CRT_FileHandleLockReleaseHook(v6, v4);
    return (unsigned __int8)v3;
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
signed int  CRT_FindFirstFile(const CHAR *a1, _DWORD *a2, int a3)
{
  HANDLE find_handle; // eax
  WIN32_FIND_DATAA find_data; // [esp+0h] [ebp-140h] BYREF

  (void)a3;
  find_handle = FindFirstFileA(a1, &find_data);
  if ( find_handle == (HANDLE)-1 )
    return _set_errno_nt_(0);
  CRT_FillFindDataRecord((int)(intptr_t)&find_data, a2);
  return (signed int)(intptr_t)find_handle;
}

//----- (00489EC6) --------------------------------------------------------
char  CRT_FillFindDataRecord(int a1, _DWORD *a2)
{
  WIN32_FIND_DATAA *find_data; // esi

  find_data = (WIN32_FIND_DATAA *)(uintptr_t)(unsigned int)a1;
  if ( !find_data || !a2 )
    return 0;
  *a2 = 0;
  if ( (find_data->dwFileAttributes & 0x20) != 0 )
    *(_BYTE *)a2 |= 0x20u;
  if ( (find_data->dwFileAttributes & 0x10) != 0 )
    *(_BYTE *)a2 |= 0x10u;
  if ( (find_data->dwFileAttributes & 2) != 0 )
    *(_BYTE *)a2 |= 2u;
  if ( (find_data->dwFileAttributes & 1) != 0 )
    *(_BYTE *)a2 |= 1u;
  if ( (find_data->dwFileAttributes & 4) != 0 )
    *(_BYTE *)a2 |= 4u;
  a2[1] = Compat_FileTimeToUnixSeconds(find_data->ftCreationTimeLow, find_data->ftCreationTimeHigh);
  a2[2] = Compat_FileTimeToUnixSeconds(find_data->ftLastAccessTimeLow, find_data->ftLastAccessTimeHigh);
  a2[3] = Compat_FileTimeToUnixSeconds(find_data->ftLastWriteTimeLow, find_data->ftLastWriteTimeHigh);
  a2[4] = find_data->nFileSizeLow;
  qmemcpy((char *)(a2 + 5), find_data->cFileName, sizeof(find_data->cFileName));
  return 0;
}

//----- (00489FBA) --------------------------------------------------------
int  CRT_MakeDirectory(const CHAR *a1, int a2)
{
  if ( CreateDirectoryA(a1, 0) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489FD7) --------------------------------------------------------
int  CRT_RemoveDirectory(const CHAR *a1, int a2)
{
  if ( RemoveDirectoryA(a1) )
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
int  Rules_ConstructHandleVectorDtor(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesHandleVector_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
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
int  Rules_ConstructRecordVectorDtor(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesRecordArrayDtorSlot);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
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
_DWORD * Rules_ParseDeftemplateSlotList(int a1, _DWORD *a2)
{
  int v3; // eax
  _BYTE *v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // esi
  int i; // eax
  BOOL v9; // ebp
  int v11; // edx
  int v12; // [esp+0h] [ebp-28h] BYREF
  int v13; // [esp+4h] [ebp-24h] BYREF
  _DWORD *v14; // [esp+8h] [ebp-20h]
  int v15; // [esp+Ch] [ebp-1Ch]

  v3 = *(_DWORD *)(a1 + 64);
  v4 = *(_BYTE **)(*(_DWORD *)(*(_DWORD *)(v3 + 68) + 4) + 16);
  v5 = Rules_PruneDeftemplateParseTree(v3);
  *(_DWORD *)(a1 + 64) = v5;
  v6 = *(_DWORD *)(v5 + 64);
  v15 = 0;
  if ( v6 )
  {
    *(_DWORD *)(a1 + 64) = v6;
    v15 = v5;
    *(_DWORD *)(v5 + 64) = 0;
    AST_FreeNode(v5);
  }
  else
  {
    AST_Free(*(_DWORD *)(v5 + 52));
    *(_DWORD *)(*(_DWORD *)(a1 + 64) + 52) = v11;
  }
  g_ClipsDeftemplateBeingParsedPtr = Rules_FindImportExportConstruct(aDeftemplate_5, &v13, v4, 1, 0);
  v14 = 0;
  v7 = *(_DWORD *)(a1 + 64);
  for ( i = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32); v7; i = a2[7] )
  {
    if ( (*(_BYTE *)(v7 + 8) & 4) != 0 )
    {
      v15 = v7;
      v7 = *(_DWORD *)(v7 + 68);
    }
    v9 = !*(_DWORD *)(v7 + 64) && v15;
    a2 = (_DWORD *)Rules_FindDuplicateDeftemplateSlot(i, (int *)v7, v9, &v12);
    if ( !a2 )
      a2 = Rules_CreateDeftemplateSlot((int *)v7, v12, v9, (int)v14);
    if ( !*(_DWORD *)(v7 + 64) && v15 )
    {
      v7 = v15;
      v15 = 0;
    }
    v7 = *(_DWORD *)(v7 + 64);
    if ( !v7 )
      *((_BYTE *)a2 + 12) |= 4u;
    v14 = a2;
  }
  return a2;
}
// 48A395: variable 'v11' is possibly undefined
// 54E514: using guessed type int dword_54E514;

//----- (0048A3B0) --------------------------------------------------------
int  Rules_FindDuplicateDeftemplateSlot(int a1, int *a2, int a3, int *a4)
{
  int v4; // esi
  int v6; // edx

  v4 = a1;
  *a4 = 0;
  if ( !a1 )
    return 0;
  do
  {
    while ( 1 )
    {
      v6 = *a2;
      if ( *a2 == 17 || v6 == 15 )
      {
        if ( (*(_BYTE *)(v4 + 12) & 1) != 0
          && *(_DWORD *)(v4 + 12) << 25 >> 31 == a3
          && (unsigned __int8)*(_DWORD *)(v4 + 20) == a2[8]
          && *(_DWORD *)(v4 + 20) << 16 >> 24 == a2[10] - 1
          && AST_NodeListsEqual(*(__int16 **)(v4 + 24), (__int16 *)a2[13]) )
        {
          return v4;
        }
        goto LABEL_8;
      }
      if ( v6 != 18 && v6 != 16 )
        break;
      if ( (*(_BYTE *)(v4 + 12) & 2) != 0
        && *(_DWORD *)(v4 + 12) << 25 >> 31 == a3
        && *(_DWORD *)(v4 + 20) << 8 >> 24 == (unsigned int)(a2[3] << 18) >> 25
        && (unsigned __int8)*(_DWORD *)(v4 + 20) == a2[8]
        && *(_DWORD *)(v4 + 20) << 16 >> 24 == a2[10] - 1
        && AST_NodeListsEqual(*(__int16 **)(v4 + 24), (__int16 *)a2[13]) )
      {
        return v4;
      }
LABEL_8:
      *a4 = v4;
      v4 = *(_DWORD *)(v4 + 40);
      if ( !v4 )
        return 0;
    }
    *a4 = v4;
    v4 = *(_DWORD *)(v4 + 40);
  }
  while ( v4 );
  return 0;
}
// 48A3D9: variable 'a3' is possibly undefined

//----- (0048A4A0) --------------------------------------------------------
int  Rules_PruneDeftemplateParseTree(int a1)
{
  int v1; // ecx
  int v2; // esi
  int v3; // ebx
  int v4; // edx
  signed int v6; // eax
  int v7; // ecx
  _DWORD *ShouldEmit; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // ecx
  int v12; // eax

  v1 = a1;
  v2 = a1;
  v3 = 0;
  if ( !a1 )
    return v2;
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
                v4 = *(_DWORD *)v1;
                if ( *(_DWORD *)v1 != 17 && v4 != 15 )
                  break;
                if ( *(_DWORD *)(v1 + 52) )
                  break;
                if ( v3 )
                  *(_DWORD *)(v3 + 64) = *(_DWORD *)(v1 + 64);
                else
                  v2 = *(_DWORD *)(v1 + 64);
                *(_DWORD *)(v1 + 64) = 0;
                AST_FreeNode(v1);
                if ( !v3 )
                  goto LABEL_21;
                v1 = *(_DWORD *)(v3 + 64);
                if ( !v1 )
                  return v2;
              }
              if ( *(_DWORD *)v1 != 18 && *(_DWORD *)v1 != 16
                || (*(_BYTE *)(v1 + 8) & 4) != 0
                || *(_DWORD *)(v1 + 52)
                || (*(_DWORD *)(v1 + 8) & 0x3F8000) != 0
                || (*(_WORD *)(v1 + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( v3 )
                *(_DWORD *)(v3 + 64) = *(_DWORD *)(v1 + 64);
              else
                v2 = *(_DWORD *)(v1 + 64);
              *(_DWORD *)(v1 + 64) = 0;
              AST_FreeNode(v1);
              if ( !v3 )
                goto LABEL_21;
              v1 = *(_DWORD *)(v3 + 64);
              if ( !v1 )
                return v2;
            }
            if ( *(_DWORD *)v1 != 18 && *(_DWORD *)v1 != 16
              || (*(_BYTE *)(v1 + 8) & 4) != 0
              || !*(_DWORD *)(v1 + 52)
              || (*(_DWORD *)(v1 + 8) & 0x3F8000) != 0
              || (*(_WORD *)(v1 + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)v1 = 17;
            v3 = v1;
            v1 = *(_DWORD *)(v1 + 64);
            if ( !v1 )
              return v2;
          }
          if ( *(_DWORD *)v1 != 18 || (*(_BYTE *)(v1 + 8) & 4) == 0 || *(_DWORD *)(v1 + 68) )
            break;
          *(_DWORD *)v1 = 17;
          v6 = PP_MakeConst25(v1, v4);
          *(_DWORD *)(v7 + 52) = v6;
          *(_BYTE *)(v7 + 8) &= ~4u;
LABEL_41:
          v3 = v7;
          v1 = *(_DWORD *)(v7 + 64);
          if ( !v1 )
            return v2;
        }
        if ( *(_DWORD *)v1 == 18 && (*(_BYTE *)(v1 + 8) & 4) != 0 )
          break;
        v3 = v1;
        v1 = *(_DWORD *)(v1 + 64);
        if ( !v1 )
          return v2;
      }
      ShouldEmit = (_DWORD *)PP_ShouldEmit(*(_DWORD *)(v1 + 68));
      v10 = AST_MergeFieldAccessNodes(ShouldEmit, *(_DWORD **)(*(_DWORD *)(v9 + 68) + 52));
      *(_DWORD *)(*(_DWORD *)(v11 + 68) + 52) = v10;
      v12 = Rules_PruneDeftemplateParseTree(*(_DWORD *)(v11 + 68));
      *(_DWORD *)(v7 + 68) = v12;
      if ( v12 )
        goto LABEL_41;
      if ( v3 )
        *(_DWORD *)(v3 + 64) = *(_DWORD *)(v7 + 64);
      else
        v2 = *(_DWORD *)(v7 + 64);
      *(_DWORD *)(v7 + 64) = 0;
      AST_FreeNode(v7);
      if ( v3 )
        break;
LABEL_21:
      v1 = v2;
      if ( !v2 )
        return 0;
    }
    v1 = *(_DWORD *)(v3 + 64);
  }
  while ( v1 );
  return v2;
}
// 48A5EF: variable 'v7' is possibly undefined
// 48A612: variable 'v9' is possibly undefined
// 48A61D: variable 'v11' is possibly undefined

//----- (0048A670) --------------------------------------------------------
_DWORD * Rules_CreateDeftemplateSlot(int *a1, int a2, char a3, int a4)
{
  _DWORD *v7; // ecx
  signed int v8; // ecx
  unsigned int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  __int16 *v15; // eax
  _DWORD *v16; // edx
  int v18; // eax
  int v19; // eax
  int v20; // ebx

  v7 = *(_DWORD **)(g_ClipsMemoryTable + 176);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = *v7;
    v8 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(v8 + 28) = 0;
  *(_DWORD *)(v8 + 40) = 0;
  *(_DWORD *)(v8 + 36) = 0;
  v9 = (unsigned int)(a1[3] << 18) >> 25 << 16;
  *(_BYTE *)(v8 + 22) = 0;
  *(_DWORD *)(v8 + 20) |= v9;
  Rules_ResetDataObjectValue(v8);
  v11 = a1[8];
  v12 = v10;
  *(_BYTE *)(v10 + 20) = 0;
  if ( v11 > 0 )
    *(_DWORD *)(v10 + 20) |= (unsigned __int8)v11;
  v13 = a1[10];
  if ( v13 < 0 )
  {
    v18 = (unsigned __int8)*(_DWORD *)(v12 + 20);
    *(_BYTE *)(v12 + 21) = 0;
    *(_DWORD *)(v12 + 20) |= v18 << 8;
  }
  else
  {
    *(_BYTE *)(v12 + 21) = 0;
    v13 = ((unsigned __int8)(v13 - 1) << 8) | *(_DWORD *)(v12 + 20);
    *(_DWORD *)(v12 + 20) = v13;
  }
  v14 = *a1;
  if ( *a1 == 17 || v14 == 15 )
  {
    *(_BYTE *)(v12 + 12) |= 1u;
  }
  else if ( v14 == 18 || v14 == 16 )
  {
    *(_BYTE *)(v12 + 12) |= 2u;
  }
  BYTE1(v13) = *(_BYTE *)(v12 + 12) & 0xBF;
  *(_BYTE *)(v12 + 12) = BYTE1(v13);
  *(_DWORD *)(v12 + 12) |= (a3 & 1) << 6;
  v15 = AST_AddHashedNodeChain((__int16 *)a1[13], v12, v13);
  v16[6] = v15;
  v16[8] = a4;
  if ( !a2 )
  {
    if ( a4 )
    {
      *(_DWORD *)(a4 + 28) = v16;
      return v16;
    }
LABEL_11:
    *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32) = v16;
    return v16;
  }
  if ( a4 )
  {
    v19 = *(_DWORD *)(a4 + 28);
    v16[10] = v19;
    if ( v19 )
      *(_DWORD *)(v19 + 36) = v16;
    *(_DWORD *)(a4 + 28) = v16;
    return v16;
  }
  else
  {
    v16[10] = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32);
    v20 = *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32);
    if ( !v20 )
      goto LABEL_11;
    *(_DWORD *)(v20 + 36) = v16;
    *(_DWORD *)(g_ClipsDeftemplateBeingParsedPtr + 32) = v16;
    return v16;
  }
}
// 48A6D8: variable 'v10' is possibly undefined
// 48A735: variable 'v16' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E514: using guessed type int dword_54E514;

//----- (0048A7E0) --------------------------------------------------------
int  Rules_FreeDeftemplateSlotList(int a1)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ebx
  int v6; // ecx
  char v7; // dl
  int v8; // edi
  int v9; // eax
  _DWORD *v10; // ebx
  int v11; // ebx
  int v12; // ecx

  result = Rules_PurgeDeftemplateSlotReferences(a1);
  if ( !*(_DWORD *)(v3 + 8) )
    *(_BYTE *)(v3 + 12) &= ~4u;
  if ( !*(_DWORD *)(a1 + 28) )
  {
    v4 = a1;
    while ( !*(_DWORD *)(v4 + 36) && !*(_DWORD *)(v4 + 40) )
    {
      v5 = v4;
      v6 = *(_DWORD *)(v4 + 32);
      if ( v6 )
      {
        v7 = *(_BYTE *)(v6 + 12);
        *(_DWORD *)(v6 + 28) = 0;
        if ( (v7 & 4) != 0 )
          v6 = 0;
      }
      else
      {
        Rules_PatchDeftemplateSlotModuleRef(0, 0);
      }
      AST_RemoveHashedNodeChain(*(__int16 **)(v5 + 24), v6);
      g_ClipsMemFreeListTemp = v5;
      *(_DWORD *)v5 = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      if ( !v4 )
        return result;
    }
    v8 = *(_DWORD *)(v4 + 36);
    if ( v8 )
    {
      v9 = *(_DWORD *)(v4 + 40);
      v10 = (_DWORD *)v4;
      *(_DWORD *)(v8 + 40) = v9;
      if ( v9 )
        *(_DWORD *)(v9 + 36) = *(_DWORD *)(v4 + 36);
      AST_RemoveHashedNodeChain(*(__int16 **)(v4 + 24), v4);
      g_ClipsMemFreeListTemp = (int)v10;
      *v10 = *(_DWORD *)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
    else
    {
      v11 = v4;
      v12 = *(_DWORD *)(v4 + 32);
      if ( v12 )
        *(_DWORD *)(v12 + 28) = *(_DWORD *)(v11 + 40);
      else
        Rules_PatchDeftemplateSlotModuleRef(0, *(_DWORD *)(v11 + 40));
      *(_DWORD *)(*(_DWORD *)(v11 + 40) + 36) = 0;
      AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 24), v12);
      g_ClipsMemFreeListTemp = v11;
      *(_DWORD *)v11 = *(_DWORD *)(g_ClipsMemoryTable + 176);
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
int __fastcall Rules_PatchDeftemplateSlotModuleRef(int a1, int a2)
{
  int Enum; // ebx
  int v4; // edx
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
    v4 = Rules_GetNextDeftemplate(0);
    if ( v4 )
      break;
LABEL_5:
    Enum = Module_NextEnum(Enum);
    if ( !Enum )
      return Module_EndEnum();
  }
  while ( v5 != *(_DWORD *)(v4 + 32) )
  {
    v4 = Rules_GetNextDeftemplate(v4);
    if ( !v4 )
      goto LABEL_5;
  }
  result = Module_EndEnum();
  *(_DWORD *)(v7 + 32) = a2;
  return result;
}
// 48A940: variable 'v5' is possibly undefined
// 48A96A: variable 'v7' is possibly undefined

//----- (0048A980) --------------------------------------------------------
int  Rules_PurgeDeftemplateSlotReferences(int a1)
{
  int result; // eax
  int i; // ecx
  _DWORD *v4; // eax
  _DWORD *v5; // edx

  result = Rules_GetNextFact(0);
  for ( i = result; result; i = result )
  {
    v4 = *(_DWORD **)(i + 20);
    v5 = 0;
    while ( v4 )
    {
      if ( a1 == v4[2] )
      {
        if ( v5 )
        {
          *v5 = *v4;
          g_ClipsMemFreeListTemp = (int)v4;
          *v4 = *(_DWORD *)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          v4 = (_DWORD *)*v5;
        }
        else
        {
          *(_DWORD *)(i + 20) = *v4;
          g_ClipsMemFreeListTemp = (int)v4;
          *v4 = *(_DWORD *)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          v4 = *(_DWORD **)(i + 20);
        }
      }
      else
      {
        v5 = v4;
        v4 = (_DWORD *)*v4;
      }
    }
    result = Rules_GetNextFact(i);
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AA20) --------------------------------------------------------
int  Rules_HashFactEntry(int a1)
{
  int relation_slot; // eax
  int relation_symbol; // eax
  int relation_hash; // edx
  int field_hash; // eax
  int result; // eax

  relation_slot = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  relation_symbol = *(_DWORD *)(uintptr_t)(unsigned int)relation_slot;
  relation_hash = Rules_HashSymbolName(
    (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)relation_symbol + 16),
    0x3F5u);
  field_hash = Rules_HashFactFieldList(a1 + 40);
  result = (field_hash + relation_hash) % 1013;
  if ( result < 0 )
    return -result;
  return result;
}

//----- (0048AA80) --------------------------------------------------------
int  Rules_HashFactFieldList(int a1)
{
  int v1; // ebx
  int v2; // ebp
  int v3; // ecx
  int v4; // edi
  int v5; // esi
  int v6; // eax
  int value; // eax

  v1 = a1 + 14;
  v2 = *(_DWORD *)(a1 + 6);
  v3 = 0;
  v4 = 0;
  if ( v2 > 0 )
  {
    v5 = 29;
    do
    {
      switch ( *(_WORD *)v1 )
      {
        case 0:
          value = *(_DWORD *)(v1 + 2);
          v6 = v5 * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case 1:
          value = *(_DWORD *)(v1 + 2);
          v6 = v5 * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case 2:
        case 3:
        case 8:
          value = *(_DWORD *)(v1 + 2);
          v6 = v5
             * Rules_HashSymbolName(
                 (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)value + 16),
                 0x3F5u);
          goto LABEL_5;
        case 4:
          v6 = Rules_HashFactFieldList(*(_DWORD *)(v1 + 2));
          goto LABEL_5;
        case 5:
        case 6:
        case 7:
          v6 = v5 * *(_DWORD *)(v1 + 2);
LABEL_5:
          v3 += v6;
          break;
        default:
          break;
      }
      v1 += 6;
      ++v4;
      ++v5;
    }
    while ( v4 < v2 );
  }
  return v3;
}

//----- (0048AB10) --------------------------------------------------------
int  Rules_FindFactInHashTable(int a1, int a2)
{
  int v3; // ecx
  int candidate; // edx

  v3 = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsFactHashTable + 4 * a2);
  if ( !v3 )
    return 0;
  while ( 1 )
  {
    candidate = *(_DWORD *)(uintptr_t)(unsigned int)v3;
    if ( *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16) == *(_DWORD *)((uintptr_t)(unsigned int)candidate + 16)
      && Rules_MultifieldsEqual(a1 + 40, candidate + 40) )
      return candidate;
    v3 = *(_DWORD *)((uintptr_t)(unsigned int)v3 + 4);
    if ( !v3 )
      return 0;
  }
}
// 54E518: using guessed type int dword_54E518;

//----- (0048AB50) --------------------------------------------------------
int * Rules_InsertFactHashEntry(int a1, int a2)
{
  int v2; // ecx
  _DWORD *v3; // ebx
  int *result; // eax
  int bucket_head; // edx
  int v6; // ecx

  v2 = a1;
  v3 = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( v3 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *v3;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *result = v2;
  bucket_head = g_ClipsFactHashTable + 4 * a2;
  v6 = *(_DWORD *)bucket_head;
  *(_DWORD *)bucket_head = (int)(uintptr_t)result;
  result[1] = v6;
  return result;
}
// 48AB70: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E518: using guessed type int dword_54E518;

//----- (0048ABA0) --------------------------------------------------------
signed int  Rules_RemoveFactHashEntry(int a1)
{
  uintptr_t target; // edx
  int bucket; // ebx
  uintptr_t bucket_slot; // ecx
  uintptr_t current; // eax
  uintptr_t previous; // ecx

  target = (uintptr_t)(unsigned int)a1;
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
signed int  Rules_DeduplicateFactOnAssert(int a1)
{
  int v1; // eax
  int v3; // ebx
  int v6; // esi

  v1 = Rules_HashFactEntry(a1);
  v3 = v1;
  if ( g_Rules_FactDuplicationEnabled )
    return v3;
  v6 = Rules_FindFactInHashTable(a1, v1);
  if ( !v6 )
    return v3;
  Rules_ReturnFact((_DWORD *)(uintptr_t)(unsigned int)a1);
  Rules_AddLogicalDependencyLink(v6, 1);
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
int  Rules_RunPeriodicCleanup(int result, int a2)
{
  int v2; // ecx
  int v4; // edx
  int i; // esi
  int v6; // edx
  int j; // edx
  int v8; // edx
  int v9; // ecx

  v2 = result;
  v4 = g_Rules_PeriodicFunctionListHead;
  for ( i = -1; v4; v4 = *(_DWORD *)(v6 + 12) )
    result = (*(int (__fastcall **)(int))(v4 + 4))(v2);
  if ( g_Rules_LastCleanupEvalDepth > g_ClipsCurrentEvaluationDepth )
  {
    result = 10240;
    g_Rules_LastCleanupEvalDepth = g_ClipsCurrentEvaluationDepth;
    g_Rules_EphemeralCountGCThreshold = 1000;
    g_Rules_EphemeralSizeThreshold = 10240;
  }
  if ( !a2 || g_ClipsEphemeralItemCount >= (unsigned int)g_Rules_EphemeralCountGCThreshold || g_ClipsEphemeralItemBytes >= (unsigned int)g_Rules_EphemeralSizeThreshold )
  {
    if ( v2 )
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
signed int  Rules_AddPeriodicFunction(int a1, int a2, int a3)
{
  return Rules_InsertPriorityCallbackByRef(a1, a2, &g_CLIPS_PeriodicFunctionListHead, a3);
}
// 51A92C: using guessed type int dword_51A92C;

//----- (0048AE10) --------------------------------------------------------
signed int  Rules_InsertPriorityCallbackByRef(int a1, int a2, int *a3, int a4)
{
  _DWORD *v6; // edx
  int v7; // ecx
  _DWORD *v8; // eax
  _DWORD *v9; // edi
  int v10; // eax

  v6 = *(_DWORD **)(g_ClipsMemoryTable + 64);
  v7 = 0;
  if ( v6 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *v6;
    v8 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *v8 = a1;
  v8[2] = a4;
  v8[1] = a2;
  v9 = v8;
  if ( !*a3 )
  {
    v8[3] = 0;
    *a3 = (int)v8;
    return 1;
  }
  v10 = *a3;
  do
  {
    if ( a4 >= *(_DWORD *)(v10 + 8) )
      break;
    v7 = v10;
    v10 = *(_DWORD *)(v10 + 12);
  }
  while ( v10 );
  if ( !v7 )
  {
    v9[3] = *a3;
    *a3 = (int)v9;
    return 1;
  }
  v9[3] = v10;
  *(_DWORD *)(v7 + 12) = v9;
  return 1;
}
// 48AE6B: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AED0) --------------------------------------------------------
signed int __fastcall Rules_RemoveNamedCallListEntry(int a1, _DWORD *a2)
{
  _DWORD *v3; // ecx
  _DWORD *v4; // esi
  _DWORD *v5; // ecx

  v3 = (_DWORD *)*a2;
  v4 = 0;
  if ( !*a2 )
    return 0;
  while ( strcmp_(v3, *v3) )
  {
    v4 = v5;
    v3 = (_DWORD *)v5[3];
    if ( !v3 )
      return 0;
  }
  if ( v4 )
    v4[3] = v5[3];
  else
    *a2 = v5[3];
  g_ClipsMemFreeListTemp = (int)v5;
  *v5 = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return 1;
}
// 48AEF1: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AF40) --------------------------------------------------------
int  Str_InternQuotedEscapedString(int *a1, unsigned int a2)
{
  char *appended; // edx
  unsigned __int8 v5; // bl
  char *v6; // edx
  char *v7; // eax
  char *v8; // eax
  signed int *v9; // ebx
  _DWORD *v10; // ecx
  int v12; // [esp+0h] [ebp-18h] BYREF
  unsigned int v13[5]; // [esp+4h] [ebp-14h] BYREF

  v13[3] = a2;
  v12 = 0;
  v13[0] = 0;
  appended = Str_AppendCharEscaping(34, 0, v13, &v12, 0x50u);
  while ( 1 )
  {
    v5 = *(_BYTE *)a1;
    if ( !*(_BYTE *)a1 )
      break;
    if ( v5 == 34 || v5 == 92 )
    {
      v6 = Str_AppendCharEscaping(92, appended, v13, &v12, v13[0] + 80);
      v7 = Str_AppendCharEscaping(*(unsigned __int8 *)a1, v6, v13, &v12, v13[0] + 80);
    }
    else
    {
      v7 = Str_AppendCharEscaping(v5, appended, v13, &v12, v13[0] + 80);
    }
    appended = v7;
    a1 = (int *)((char *)a1 + 1);
  }
  v8 = Str_AppendCharEscaping(34, appended, v13, &v12, v13[0] + 80);
  v9 = Str_Intern(v8, (int)v8);
  Mem_SmallBlockFree(v10, v13[0]);
  return v9[4];
}
// 48AFEB: variable 'v10' is possibly undefined

//----- (0048B000) --------------------------------------------------------
int  Str_Concat(const char *a1, const char *a2, unsigned int a3)
{
  char *v4; // eax
  char *v5; // eax
  signed int *v6; // ebx
  _DWORD *v7; // ecx
  int v9; // [esp+0h] [ebp-14h] BYREF
  unsigned int v10[4]; // [esp+4h] [ebp-10h] BYREF

  v10[2] = a3;
  v9 = 0;
  v10[0] = 0;
  v4 = Str_Append(a1, 0, v10, &v9);
  v5 = Str_Append(a2, v4, v10, &v9);
  v6 = Str_Intern(v5, (int)v5);
  Mem_SmallBlockFree(v7, v10[0]);
  return v6[4];
}
// 48B03A: variable 'v7' is possibly undefined

//----- (0048B050) --------------------------------------------------------
char * Str_Append(const char *a1, char *a2, unsigned int *a3, _DWORD *a4)
{
  const char *v4; // esi
  char *v5; // ebp
  unsigned int v6; // kr04_4
  signed int v7; // ebx
  int v9; // ecx
  char *v10; // edi
  char v11; // al
  char v12; // al

  v4 = a1;
  v5 = a2;
  v6 = strlen(a1) + 1;
  v7 = v6 + *a4;
  if ( v7 > (int)*a3 )
  {
    v5 = (char *)Mem_Realloc(a2, *a3, v7);
    *a3 = *a4 + v6;
    if ( !v5 )
      return 0;
  }
  else if ( !a2 )
  {
    return 0;
  }
  v10 = &v5[*a4];
  do
  {
    v11 = *v4;
    *v10 = *v4;
    if ( !v11 )
      break;
    v12 = v4[1];
    v4 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  *a4 += v6 - 1;
  return v5;
}
// 48B09C: variable 'v9' is possibly undefined

//----- (0048B0F0) --------------------------------------------------------
char * Str_AppendBounded(int a1, char *a2, _DWORD *a3, int a4, unsigned int *a5)
{
  char *v6; // esi
  signed int v7; // ebx
  int *v9; // ecx
  int v10; // edx
  int v11; // [esp+0h] [ebp-10h]

  v6 = a2;
  if ( *(_BYTE *)(a4 + a1 - 1) )
    v11 = a4 + 1;
  else
    v11 = a4;
  v7 = *a3 + v11;
  if ( v7 > (int)*a5 )
  {
    v6 = (char *)Mem_Realloc(a2, *a5, v7);
    *a5 = v11 + *a3;
  }
  if ( !v6 )
    return 0;
  strncpy_(a3, a1);
  v10 = v11 - 1 + *v9;
  *v9 = v10;
  v6[v10] = 0;
  return v6;
}
// 48B121: variable 'a3' is possibly undefined
// 48B153: variable 'v9' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (0048B170) --------------------------------------------------------
char * Str_AppendCharEscaping(
        int a1,
        char *a2,
        unsigned int *a3,
        int *a4,
        unsigned int a5)
{
  char *result; // eax
  int v7; // edx

  result = a2;
  if ( (int)(*a3 - 1) <= *a4 )
  {
    result = (char *)Mem_Realloc(a2, *a3, a5);
    *a3 = a5;
    if ( !result )
      return 0;
  }
  if ( a1 == 8 )
  {
    if ( *a4 > 0 )
      --*a4;
    result[*a4] = 0;
  }
  else
  {
    result[*a4] = a1;
    v7 = *a4 + 1;
    *a4 = v7;
    result[v7] = 0;
  }
  return result;
}
// 48B1B3: variable 'v6' is possibly undefined

//----- (0048B1E0) --------------------------------------------------------
_DWORD * Rules_InsertPriorityCallbackReturningHead(int a1, int a2, signed int a3, int a4)
{
  _DWORD *v7; // edi
  signed int v8; // ecx
  _DWORD *result; // eax
  _DWORD *v10; // edi
  signed int v11; // eax

  v7 = *(_DWORD **)(g_ClipsMemoryTable + 64);
  v8 = 0;
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *v7;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  result[1] = a4;
  result[2] = a2;
  v10 = result;
  *result = a1;
  if ( a3 )
  {
    v11 = a3;
    do
    {
      if ( a2 >= *(int *)(v11 + 8) )
        break;
      v8 = v11;
      v11 = *(_DWORD *)(v11 + 12);
    }
    while ( v11 );
    if ( v8 )
    {
      v10[3] = v11;
      *(_DWORD *)(v8 + 12) = v10;
      return (_DWORD *)a3;
    }
    else
    {
      v10[3] = a3;
      return v10;
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
int  Rules_RemoveNamedCallbackReturningHead(int a1, int a2, _DWORD *a3)
{
  int list_head; // edi
  int current; // ecx
  int previous; // ebx

  list_head = a2;
  current = a2;
  *a3 = 0;
  previous = 0;
  if ( !current )
    return list_head;
  while ( strcmp_(a1, *(_DWORD *)current) )
  {
    previous = current;
    current = *(_DWORD *)(current + 12);
    if ( !current )
      return list_head;
  }
  *a3 = 1;
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
  signed int *v1; // eax
  char v2; // dl

  v1 = Str_Intern(aInitialFact_2, (int)this);
  return Rules_CreateDeftemplateRecord((int)v1, v2);
}
// 48B3DD: variable 'v2' is possibly undefined

//----- (0048B3F0) --------------------------------------------------------
int  Rules_ClearDeftemplateModuleData(signed int a1)
{
  return Rules_SaveConstruct(a1, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B400) --------------------------------------------------------
int __thiscall Rules_UndeftemplateCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B420) --------------------------------------------------------
int  Rules_DeleteDeftemplate(int a1, int a2)
{
  return Rules_DeleteConstructOrAll(a1, g_DeftemplateConstructType, a2);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B430) --------------------------------------------------------
_DWORD * Rules_GetDeftemplateListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_DeftemplateConstructType, a2);
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
int  Rules_GetFactWatchFlag(int a1)
{
  return *(_DWORD *)(a1 + 24) << 30 >> 31;
}

//----- (0048B510) --------------------------------------------------------
int  Rules_SetFactWatchFlag(char a1, int a2)
{
  int result; // eax

  *(_BYTE *)(a2 + 24) &= ~2u;
  result = 2 * (a1 & 1);
  *(_DWORD *)(a2 + 24) |= result;
  return result;
}

//----- (0048B530) --------------------------------------------------------
signed int  Rules_ToggleFactWatchFlag(int a1, int a2, double a3)
{
  return Rules_ApplyWatchFlagCommand(g_DeftemplateConstructType, a1, (int)Rules_GetFactWatchFlag, a2, a3, (void (*)(void))Rules_SetFactWatchFlag);
}
// 48B500: using guessed type int sub_48B500();
// 54E650: using guessed type int dword_54E650;

//----- (0048B550) --------------------------------------------------------
signed int  Rules_WatchPrintFactsState(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(g_DeftemplateConstructType, a1, (int)Rules_GetFactWatchFlag, a2, a3, (void (*)(void))Rules_SetFactWatchFlag);
}
// 48B500: using guessed type int sub_48B500();
// 54E650: using guessed type int dword_54E650;

//----- (0048B570) --------------------------------------------------------
int  Rules_AddWatchItem(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int watch_item; // ecx
  int previous_watch_item; // ebx
  int result; // eax
  _DWORD *v13; // edx
  _DWORD *v14; // eax

  watch_item = g_WatchItemListHead;
  previous_watch_item = 0;
  if ( watch_item )
  {
    while ( 1 )
    {
      result = strcmp_(*(_DWORD *)watch_item, a1);
      if ( !result )
        break;
      if ( a3 < *(_DWORD *)(watch_item + 12) )
        previous_watch_item = watch_item;
      watch_item = *(_DWORD *)(watch_item + 24);
      if ( !watch_item )
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    v13 = *(_DWORD **)(g_ClipsMemoryTable + 112);
    if ( v13 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(g_ClipsMemoryTable + 112) = *v13;
      v14 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v14 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
    }
    *v14 = a1;
    v14[2] = a2;
    v14[3] = a3;
    v14[1] = a4;
    v14[4] = a5;
    v14[5] = a6;
    if ( previous_watch_item )
    {
      v14[6] = *(_DWORD *)(previous_watch_item + 24);
      *(_DWORD *)(previous_watch_item + 24) = (int)v14;
      return 1;
    }
    else
    {
      v14[6] = g_WatchItemListHead;
      g_WatchItemListHead = (int)v14;
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
signed int  Rules_SetWatchItemState(unsigned int a1, int a2, int a3)
{
  int v5; // ecx
  _DWORD *v6; // ecx
  int v7; // ecx

  if ( a1 >= 2 )
    return 0;
  if ( !strcmp_(a2, aAll_1) )
  {
    v5 = g_WatchItemListHead;
    if ( !g_WatchItemListHead )
      return 1;
    while ( 1 )
    {
      if ( !a3 )
        **(_DWORD **)(v5 + 4) = a1;
      if ( *(_DWORD *)(v5 + 16) && !(*(int (__fastcall **)(int, unsigned int))(v5 + 16))(v5, a1) )
        break;
      v5 = *(_DWORD *)(v5 + 24);
      if ( !v5 )
        return 1;
    }
  }
  else
  {
    v6 = (_DWORD *)g_WatchItemListHead;
    if ( !g_WatchItemListHead )
      return 0;
    while ( strcmp_(v6, *v6) )
    {
      v6 = *(_DWORD **)(v7 + 24);
      if ( !v6 )
        return 0;
    }
    if ( !a3 )
      **(_DWORD **)(v7 + 4) = a1;
    if ( !*(_DWORD *)(v7 + 16) || (*(int (__fastcall **)(int, unsigned int))(v7 + 16))(v7, a1) )
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
signed int Rules_GetWatchItemState(int a1)
{
  int watch_item; // ecx
  int value_pointer; // eax

  watch_item = g_WatchItemListHead;
  if ( !g_WatchItemListHead )
    return -1;
  while ( strcmp_(a1, *(_DWORD *)watch_item) )
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
int __fastcall Rules_FindWatchItem(int a1, _DWORD *a2)
{
  int result; // eax
  _DWORD *v4; // ecx
  int v5; // ecx

  *a2 = 1;
  result = strcmp_(a1, aAll_1);
  if ( result )
  {
    v4 = (_DWORD *)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      while ( strcmp_(v4, *v4) )
      {
        v4 = *(_DWORD **)(v5 + 24);
        if ( !v4 )
          goto LABEL_5;
      }
      return v5;
    }
    else
    {
LABEL_5:
      *a2 = 0;
      return 0;
    }
  }
  return result;
}
// 48B7C2: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A94C: using guessed type int dword_51A94C;

//----- (0048B840) --------------------------------------------------------
signed int  Rules_WatchCommand(int a1, double a2)
{
  signed int result; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  _DWORD v6[6]; // [esp-8h] [ebp-28h] BYREF
  _DWORD v7[4]; // [esp+10h] [ebp-10h] BYREF

  v7[2] = a1;
  result = Lexer_ParseValueList(1, v6, 2, a2);
  if ( result )
  {
    v3 = Rules_FindWatchItem(*(_DWORD *)(v6[2] + 16), v7);
    if ( v7[0] )
    {
      if ( !*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) || v3 && *(_DWORD *)(v3 + 16) )
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
signed int  Rules_UnwatchCommand(int a1, double a2)
{
  signed int result; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  _DWORD v6[6]; // [esp-8h] [ebp-28h] BYREF
  _DWORD v7[4]; // [esp+10h] [ebp-10h] BYREF

  v7[2] = a1;
  result = Lexer_ParseValueList(1, v6, 2, a2);
  if ( result )
  {
    v3 = Rules_FindWatchItem(*(_DWORD *)(v6[2] + 16), v7);
    if ( v7[0] )
    {
      if ( !*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) || v3 && *(_DWORD *)(v3 + 16) )
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
signed int  Rules_ListWatchItemsCommand(int a1, double a2)
{
  signed int result; // eax
  int *v3; // ecx
  int v4; // ecx
  char *v5; // edx
  int v6; // ecx
  int v7; // ecx
  int *v8; // eax
  int v9; // ecx
  char *v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // [esp-8h] [ebp-28h] BYREF
  _DWORD v14[4]; // [esp+10h] [ebp-10h] BYREF

  v14[2] = a1;
  result = g_ClipsCurrentExpression;
  if ( *(_DWORD *)(g_ClipsCurrentExpression + 6) )
  {
    result = Lexer_ParseValueList(1, &v13, 2, a2);
    if ( result )
    {
      v8 = (int *)Rules_FindWatchItem(v7, v14);
      if ( v14[0] && v8 )
      {
        if ( !v8[5] && *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) )
        {
          Lexer_ErrorRecover(1);
          return Rules_ExpectedCountError((int)aListWatchItems, 1);
        }
        else
        {
          Output_Write((int)g_IO_LogicalName_WDisplay, *v8, (int)v8);
          if ( **(_DWORD **)(v9 + 4) )
            v10 = aOn;
          else
            v10 = aOff;
          result = Output_Write((int)g_IO_LogicalName_WDisplay, (int)v10, v9);
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
    v3 = (int *)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      do
      {
        Output_Write((int)g_IO_LogicalName_WDisplay, *v3, (int)v3);
        if ( **(_DWORD **)(v4 + 4) )
          v5 = aOn;
        else
          v5 = aOff;
        result = Output_Write((int)g_IO_LogicalName_WDisplay, (int)v5, v4);
        v3 = *(int **)(v6 + 24);
      }
      while ( v3 );
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
  int v3; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return g_ClipsFalseSymbol;
  v3 = Rules_ResolveFactArgument(1, v1, 0, a1);
  if ( !v3 )
    return g_ClipsFalseSymbol;
  else
    return **(_DWORD **)(v3 + 16);
}
// 48BCCC: variable 'v1' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BCF0) --------------------------------------------------------
int  Rules_CheckFactExistp(double a1)
{
  int result; // eax
  int v2; // ecx
  int v3; // eax

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    v3 = Rules_ResolveFactArgument(1, v2, 0, a1);
    return Rules_CheckFactStillAsserted(v3);
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
int  Lexer_ParseSlotConstraint(_DWORD *a1, int a2, double a3)
{
  int result; // eax
  int v5; // ecx
  int v6; // edi
  _DWORD v7[11]; // [esp-8h] [ebp-2Ch] BYREF

  v7[9] = a2;
  a1[1] = 2;
  a1[2] = g_ClipsFalseSymbol;
  result = Lexer_TokenExpect(2);
  if ( result != -1 )
  {
    result = Rules_ResolveFactArgument(1, v5, 1, a3);
    v6 = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, v7, 2, a3);
      if ( result )
        return Lexer_BuildSlotNode(v6, *(char **)(v7[2] + 16), a1);
    }
  }
  return result;
}
// 48BD94: variable 'v5' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BDD0) --------------------------------------------------------
int  Lexer_BuildSlotNode(int a1, char *a2, _DWORD *a3)
{
  char *v5; // ecx
  int v7; // ecx
  signed int *v8; // eax
  int v9; // ecx
  int v10; // [esp+0h] [ebp-18h] BYREF
  int v11; // [esp+4h] [ebp-14h]

  if ( (*(_BYTE *)(*(_DWORD *)(a1 + 16) + 24) & 1) != 0 )
  {
    if ( strcmp_(a2, aImplied) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v7, *(_DWORD *)(**(_DWORD **)(a1 + 16) + 16));
    }
  }
  else
  {
    v8 = Str_Intern(a2, (int)a2);
    v11 = *(_DWORD *)(a1 + 16);
    if ( !Lexer_FindTemplateSlot(v11, (int)v8, &v10) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v9, *(_DWORD *)(**(_DWORD **)(a1 + 16) + 16));
    }
  }
  if ( (*(_BYTE *)(*(_DWORD *)(a1 + 16) + 24) & 1) != 0 )
    return Lexer_EmitSlotBinding(a1, 0, (int)v5, a3);
  else
    return Lexer_EmitSlotBinding(a1, v5, (int)v5, a3);
}
// 48BE07: variable 'v5' is possibly undefined
// 48BE28: variable 'v7' is possibly undefined
// 48BE62: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0048BE80) --------------------------------------------------------
int  Lexer_ParseFieldSpec(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // ecx

  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
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
int  Rules_BuildFactSlotNameList(int a1, _DWORD *a2)
{
  int v3; // edx
  int v5; // edx
  signed int i; // eax
  _DWORD *v7; // eax
  int v8; // ecx
  _DWORD *v9; // ebx
  _DWORD *v10; // edx
  int result; // eax
  _DWORD *v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  v3 = *(_DWORD *)(a1 + 16);
  if ( (*(_BYTE *)(v3 + 24) & 1) != 0 )
  {
    a2[1] = 4;
    a2[3] = 0;
    a2[4] = 0;
    *((_WORD *)Rules_CreateEphemeralMultifield(1) + 7) = 2;
    result = (int)Str_Intern(aImplied, v13);
    *(_DWORD *)(v14 + 16) = result;
    *(_DWORD *)(v15 + 8) = v14;
  }
  else
  {
    v5 = *(_DWORD *)(v3 + 20);
    for ( i = 0; v5; ++i )
      v5 = *(_DWORD *)(v5 + 16);
    a2[1] = 4;
    a2[3] = 0;
    a2[4] = i - 1;
    v7 = Rules_CreateEphemeralMultifield(i);
    *(_DWORD *)(v8 + 8) = v7;
    v9 = v7;
    v10 = *(_DWORD **)(*(_DWORD *)(a1 + 16) + 20);
    result = 1;
    if ( v10 )
    {
      v12 = v9;
      do
      {
        *((_WORD *)v12 + 7) = 2;
        v12[4] = *v10;
        v12 = (_DWORD *)((char *)v12 + 6);
        v10 = (_DWORD *)v10[4];
        ++result;
      }
      while ( v10 );
    }
  }
  return result;
}
// 48BF19: variable 'v8' is possibly undefined
// 48BF80: variable 'v13' is possibly undefined
// 48BF85: variable 'v14' is possibly undefined
// 48BF88: variable 'v15' is possibly undefined

//----- (0048BF90) --------------------------------------------------------
_DWORD * Rules_GetFactListFunction(int a1, double a2)
{
  int v3; // eax
  int v4; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  _DWORD v9[2]; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+4h] [ebp-1Ch]
  int v11; // [esp+18h] [ebp-8h]

  v11 = a1;
  v3 = Lexer_TokenExpect(1);
  if ( v3 == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( v3 == 1 )
  {
    Rules_RtnUnknown(1, v9, a2);
    if ( v9[1] != 2 || !Module_FindByName(*(_BYTE **)(v10 + 16)) && strcmp_(v7, *(_DWORD *)(v10 + 16)) )
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
  int v1; // esi
  int v2; // eax
  _DWORD *v3; // ecx
  signed int i; // edx
  int v5; // edx
  _DWORD *v6; // eax
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
  v1 = v0;
  if ( v0 )
  {
    Module_SetCurrent(v0);
    Lexer_MarkImpliedTemplates();
    v2 = Rules_GetNextFactInModule(0);
    for ( i = 0; v2; i = v5 + 1 )
      v2 = Rules_GetNextFactInModule(v2);
  }
  else
  {
    for ( j = Rules_GetNextFact(0); j; i = v12 + 1 )
      j = Rules_GetNextFact(j);
  }
  v3[1] = 4;
  v3[4] = i - 1;
  v3[3] = 0;
  v6 = Rules_CreateEphemeralMultifield(i);
  *(_DWORD *)(v7 + 8) = v6;
  if ( v1 )
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
int  Rules_ResolveFactArgument(int a1, int a2, int a3, double a4)
{
  int v4; // ecx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // [esp-4h] [ebp-34h] BYREF
  int v9; // [esp+0h] [ebp-30h]
  int v10; // [esp+4h] [ebp-2Ch]
  _BYTE v11[24]; // [esp+14h] [ebp-1Ch] BYREF
  int v12; // [esp+2Ch] [ebp-4h]

  v12 = a2;
  Rules_RtnUnknown(a1, &v8, a4);
  if ( v9 == 6 )
  {
    result = v10;
    if ( *(char *)(v10 + 29) < 0 )
      return 0;
  }
  else if ( v9 == 1 && *(int *)(v10 + 16) >= 0 )
  {
    result = Rules_FindFactByIndex();
    if ( !result && a3 )
    {
      sprintf_(v11, "f-%ld", v6);
      Rules_ReportCantFindItem(v7, (int)v11);
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
const void * Rules_FactPatternNetworkAssignNodeIds(const void *result, int a2, _DWORD *a3)
{
  const void *v3; // ecx

  v3 = result;
  if ( a3 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        if ( v3 )
        {
          if ( v3 == (const void *)1 )
            result = Rules_FactPatternNetworkWriteNodeRecord((int)a3, a2);
        }
        else
        {
          result = (const void *)g_FactPatternNodeCount++;
          a3[4] = result;
        }
        if ( !a3[7] )
          break;
        a3 = (_DWORD *)a3[7];
      }
      while ( !a3[10] )
      {
        a3 = (_DWORD *)a3[8];
        if ( !a3 )
          return result;
      }
      a3 = (_DWORD *)a3[10];
    }
  }
  return result;
}
// 48C27D: variable 'v3' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C2D0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteHeader(int a1, int a2)
{
  int v2; // ecx
  _DWORD v4[4]; // [esp+0h] [ebp-10h] BYREF

  v4[2] = a2;
  v4[0] = 4;
  Rules_BsaveWriteBlock(4, a1, v4);
  return Rules_BsaveWriteBlock(4, v2, &g_FactPatternNodeCount);
}
// 48C2F5: variable 'v2' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C310) --------------------------------------------------------
int  Rules_FactPatternNetworkBsaveStorage(int a1)
{
  int i; // edi
  int j; // ecx
  int v4; // ecx
  int result; // eax
  int v6[7]; // [esp+0h] [ebp-1Ch] BYREF

  v6[0] = 32 * g_FactPatternNodeCount;
  Rules_BsaveWriteBlock(4, a1, v6);
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(v4) )
      Rules_FactPatternNetworkAssignNodeIds((const void *)1, a1, *(_DWORD **)(j + 32));
  }
  result = Rules_IsBloaded();
  if ( result )
    return Rules_ConstructQueuePop(&g_FactPatternNodeCount);
  return result;
}
// 48C368: variable 'v4' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C3B0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteNodeRecord(int a1, int a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // ecx
  int v8; // ebp
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // esi
  int v15; // eax
  _BYTE v17[8]; // [esp+0h] [ebp-34h] BYREF
  int v18; // [esp+8h] [ebp-2Ch]
  signed int v19; // [esp+Ch] [ebp-28h]
  int v20; // [esp+10h] [ebp-24h]
  int v21; // [esp+14h] [ebp-20h]
  int v22; // [esp+18h] [ebp-1Ch]
  int v23; // [esp+1Ch] [ebp-18h]

  Rules_BsavePackSharedRecordHeader((int)v17, a1);
  v4 = *(_DWORD *)(v3 + 20);
  BYTE1(v18) = 0;
  v18 |= (unsigned __int8)v4 << 8;
  v5 = *(_DWORD *)(v3 + 20);
  BYTE2(v18) = 0;
  v18 |= v5 & 0xFF0000;
  v6 = *(_DWORD *)(v3 + 20) << 16;
  LOBYTE(v18) = 0;
  v18 |= HIBYTE(v6);
  v19 = AST_GetHashedNodeIndex(*(__int16 **)(v3 + 24));
  v8 = v7[7];
  if ( v8 )
    v9 = *(_DWORD *)(v8 + 16);
  else
    v9 = -1;
  v20 = v9;
  v10 = v7[8];
  if ( v10 )
    v11 = *(_DWORD *)(v10 + 16);
  else
    v11 = -1;
  v21 = v11;
  v12 = v7[9];
  if ( v12 )
    v13 = *(_DWORD *)(v12 + 16);
  else
    v13 = -1;
  v22 = v13;
  v14 = v7[10];
  if ( v14 )
    v15 = *(_DWORD *)(v14 + 16);
  else
    v15 = -1;
  v23 = v15;
  return Rules_BsaveWriteBlock(32, a2, v17);
}
// 48C3C7: variable 'v3' is possibly undefined
// 48C41A: variable 'v7' is possibly undefined

//----- (0048C490) --------------------------------------------------------
int Rules_FactPatternNetworkBloadStorage()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h] BYREF

  Rules_BloadReadBlock((uintptr_t)&v1, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_FactPatternNodeCount, 4u);
  if ( g_FactPatternNodeCount )
  {
    v1 = 44 * g_FactPatternNodeCount;
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
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  return Rules_BloadAndRefresh(g_FactPatternNodeCount, 32, (void (__fastcall *)(signed int, signed int))Rules_FactPatternNetworkFixupNodeRecord);
}
// 54E520: using guessed type int dword_54E520;

//----- (0048C510) --------------------------------------------------------
int  Rules_FactPatternNetworkFixupNodeRecord(int *a1, int a2)
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

  record_offset = 44 * a2;
  record = g_ClipsFactPatternNodeBloadArray + record_offset;
  Rules_BloadUnpackSharedRecordHeader(record, a1);
  *(_DWORD *)(record + 16) = 0;

  flags = (unsigned int)a1[2];
  *(_BYTE *)(record + 20) = 0;
  *(_DWORD *)(record + 20) |= (flags >> 8) & 0xFF;
  *(_BYTE *)(record + 22) = 0;
  *(_DWORD *)(record + 20) |= flags & 0xFF0000;
  *(_BYTE *)(record + 21) = 0;
  *(_DWORD *)(record + 20) |= (flags & 0xFF) << 8;

  relation_index = a1[3];
  *(_DWORD *)(record + 24) = relation_index == -1 ? 0 : g_ClipsPackedExpressionArray + 14 * relation_index;

  previous_index = a1[7];
  *(_DWORD *)(record + 40) = previous_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * previous_index;

  next_index = a1[4];
  *(_DWORD *)(record + 28) = next_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * next_index;

  parent_index = a1[5];
  *(_DWORD *)(record + 32) = parent_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * parent_index;

  child_index = a1[6];
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
  int v1; // esi
  int i; // edi
  int v3; // ecx
  int j; // ebx
  _DWORD *v5; // eax
  int v6; // ecx

  result = Module_NextEnum(0);
  v1 = 0;
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(j) )
    {
      v5 = *(_DWORD **)(j + 32);
      for ( *(_DWORD *)(j + 12) = v1++; v5; v3 = v6 + 1 )
      {
        v5[4] = v3;
        v5 = Rules_FactPatternNetworkNextNode(v5);
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
int  Rules_FactPatternNetworkToCode(const char *a1, const char *a2, int a3, int a4, int a5)
{
  int v5; // esi
  int v6; // ecx
  _DWORD *v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // esi
  int v12; // [esp+0h] [ebp-30h] BYREF
  int v13; // [esp+4h] [ebp-2Ch] BYREF
  int v14; // [esp+8h] [ebp-28h] BYREF
  int Enum; // [esp+Ch] [ebp-24h]
  int v16; // [esp+10h] [ebp-20h]
  const char *v17; // [esp+14h] [ebp-1Ch]
  const char *v18; // [esp+18h] [ebp-18h]
  int v19; // [esp+1Ch] [ebp-14h]
  int v20; // [esp+20h] [ebp-10h]

  v18 = a1;
  v17 = a2;
  v19 = a4;
  v20 = a3;
  v13 = 0;
  v14 = 1;
  Output_WriteFormatted(0, 1, a4, (int)aIncludeFactbld, 1);
  v5 = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v16 = Rules_GetNextDeftemplate(0);
      if ( v16 )
        break;
LABEL_7:
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_8;
    }
    while ( 1 )
    {
      v7 = *(_DWORD **)(v16 + 32);
      if ( v7 )
        break;
LABEL_6:
      v16 = Rules_GetNextDeftemplate(v16);
      if ( !v16 )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v8 = Rules_ConstructCodeFileOpen(
             v5,
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
      v10 = v8;
      if ( !v8 )
        break;
      Rules_FactPatternNetworkNodeToCode(v8, (int)v7, a5, v20);
      ++v13;
      v5 = Rules_ConstructCodeFileClose(v10, &v13, a5, &v14, 0, 0);
      v7 = Rules_FactPatternNetworkNextNode(v7);
      if ( !v7 )
        goto LABEL_6;
    }
    Rules_FactPatternNetworkToCodeClose(0, a5, v9);
    return 0;
  }
  else
  {
LABEL_8:
    Rules_FactPatternNetworkToCodeClose(v5, a5, v6);
    return 1;
  }
}
// 48C885: variable 'v6' is possibly undefined
// 48C89A: variable 'v9' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048C8B0) --------------------------------------------------------
int  Rules_FactPatternNetworkToCodeClose(int result, int a2, int a3)
{
  int v3; // [esp+0h] [ebp-Ch] BYREF
  _DWORD v4[2]; // [esp+4h] [ebp-8h] BYREF

  v4[1] = a3;
  v3 = a2;
  v4[0] = 0;
  if ( result )
    return Rules_ConstructCodeFileClose(result, &v3, a2, v4, 0, 0);
  return result;
}

//----- (0048C8E0) --------------------------------------------------------
int  Rules_FactPatternNetworkNodeToCode(int a1, int a2, int a3, char a4)
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

  Output_WriteFormatted(a3, a2, a1, (int)asc_504530, a4);
  Rules_PrintPatternNetworkNodeTrace(a1, v7, v8);
  Output_WriteFormatted(a3, v9, a1, (int)a0DDD, *(_DWORD *)(a2 + 20));
  Rules_WriteExpressionRefToCode(a1, *(__int16 **)(a2 + 24), v10, v20);
  v12 = *(_DWORD *)(a2 + 28);
  if ( v12 )
    Output_WriteFormatted(v20, *(_DWORD *)(v12 + 16) % a3, a1, (int)aSD_LdLd_1, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v11, 0, a1, (int)aNull_14, v20);
  if ( *(_DWORD *)(a2 + 32) )
    Output_WriteFormatted(**(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), v20, a1, (int)aSD_LdLd_2, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v14, v13, a1, (int)aNull_12, v20);
  if ( *(_DWORD *)(a2 + 36) )
    Output_WriteFormatted(v16, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), a1, (int)aSD_LdLd_2, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v16, v15, a1, (int)aNull_12, v20);
  v18 = *(_DWORD *)(a2 + 40);
  if ( v18 )
    return Output_WriteFormatted(v18, *(_DWORD *)(v18 + 16) % a3, a1, (int)aSD_LdLd_3, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(0, v17, a1, (int)aNull_13, v20);
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
int  Rules_FactPatternNetworkWriteNodeRefToCode(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a1 )
    return Output_WriteFormatted(a3, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20), a2, (int)aSD_LdLd_4, **(_DWORD **)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(a3, a2, a2, (int)aNull_16, v4);
}
// 48CAB0: variable 'v4' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048CAF0) --------------------------------------------------------
_DWORD * Rules_CreateMultifield(signed int a1)
{
  signed int v1; // ecx
  signed int v2; // edx
  int v3; // eax
  _DWORD *result; // eax
  __int16 v5; // dx

  v1 = a1;
  v2 = a1;
  if ( a1 <= 0 )
    v2 = 1;
  if ( (unsigned int)(6 * (v2 - 1) + 20) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (v2 - 1) + 80) )
  {
    v3 = g_ClipsMemoryTable + 24 * (v2 - 1);
    g_ClipsMemFreeListTemp = *(_DWORD *)(v3 + 80);
    *(_DWORD *)(v3 + 80) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (v2 - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = v1;
  v5 = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = v5;
  return result;
}
// 48CB51: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048CB90) --------------------------------------------------------
_DWORD * Rules_ReturnMultifieldToPool(_DWORD *result)
{
  int v1; // edx
  unsigned int v2; // edx

  if ( result )
  {
    v1 = *(_DWORD *)((char *)result + 6);
    if ( !v1 )
      v1 = 1;
    v2 = 6 * (v1 - 1) + 20;
    g_ClipsMemPoolReturnBucketIndex = v2;
    if ( v2 >= 0x1F4 )
    {
      return (_DWORD *)Mem_SmallBlockRelease(result, v2);
    }
    else
    {
      g_ClipsMemFreeListTemp = (int)result;
      *result = *(_DWORD *)(g_ClipsMemoryTable + 4 * v2);
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
_DWORD * Rules_CreateMultifieldFromString(const char *a1)
{
  int v1; // esi
  int v2; // ecx
  signed int v3; // edi
  signed int *v4; // edx
  __int16 v5; // ax
  signed int v6; // eax
  _DWORD *v8; // ebx
  char *v9; // edx
  int v10; // ecx
  int i; // eax
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int node_count;

  token_buffer_ptr = Compat_AllocLow32Bytes(12);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  IO_OpenStringSource((int)aMultifieldStr, a1, 0);
  v1 = 0;
  Parser_NextToken((int)aMultifieldStr, token_buffer_ptr);
  v3 = 0;
  node_count = 0;
  while ( token_buffer[0] != 102 )
  {
    if ( token_buffer[0] == 2 || token_buffer[0] == 3 || token_buffer[0] < 2u || token_buffer[0] == 8 )
    {
      v4 = (signed int *)(uintptr_t)(unsigned int)token_buffer[1];
      v5 = token_buffer[0];
    }
    else
    {
      v4 = Str_Intern((char *)(uintptr_t)(unsigned int)token_buffer[2], v2);
      v5 = 3;
    }
    v6 = AST_NewNode(v5, (int)v4);
    ++node_count;
    if ( v1 )
      *(_DWORD *)(v3 + 10) = v6;
    else
      v1 = v6;
    v3 = v6;
    Parser_NextToken((int)aMultifieldStr, token_buffer_ptr);
  }
  IO_CloseStringRouter((int)aMultifieldStr);
  v8 = Rules_CreateEphemeralMultifield(node_count);
  v9 = (char *)v8 + 14;
  v10 = 0;
  for ( i = v1; i; ++v10 )
  {
    *(_WORD *)v9 = *(_WORD *)i;
    *(_DWORD *)(v9 + 2) = *(_DWORD *)(i + 2);
    v9 += 6;
    i = *(_DWORD *)(i + 10);
  }
  AST_Free(v1);
  Compat_FreeLow32Bytes(token_buffer_ptr);
  return v8;
}
// 48CD3A: simplified comparisons for '%var_24.4': ==0 || ==1 became <2u
// 48CD52: variable 'v2' is possibly undefined

//----- (0048CD70) --------------------------------------------------------
_DWORD * Rules_CreateEphemeralMultifield(signed int a1)
{
  signed int v1; // ecx
  signed int v2; // edx
  int v3; // eax
  _DWORD *result; // eax
  __int16 v5; // bx

  v1 = a1;
  if ( a1 <= 0 )
    v2 = 1;
  else
    v2 = a1;
  if ( (unsigned int)(6 * (v2 - 1) + 20) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (v2 - 1) + 80) )
  {
    v3 = 24 * (v2 - 1) + g_ClipsMemoryTable;
    g_ClipsMemFreeListTemp = *(_DWORD *)(v3 + 80);
    *(_DWORD *)(v3 + 80) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (v2 - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = v1;
  v5 = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = v5;
  *(_DWORD *)((char *)result + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = (int)result;
  ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += 6 * v2 + 20;
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
_DWORD * Rules_MaterializeMultifieldRange(_DWORD *a1)
{
  _DWORD *v2; // ebx
  int v3; // edx

  if ( a1[1] != 4 )
    return 0;
  v2 = Rules_CreateMultifield(a1[4] - a1[3] + 1);
  qmemcpy(
    (char *)v2 + 14,
    (const void *)(6 * *(_DWORD *)(v3 + 12) + *(_DWORD *)(v3 + 8) + 14),
    6 * *(_DWORD *)((char *)v2 + 6));
  return v2;
}
// 48CE95: variable 'v3' is possibly undefined

//----- (0048CED0) --------------------------------------------------------
int  Rules_RegisterEphemeralMultifield(int a1)
{
  int result; // eax

  *(_WORD *)(a1 + 4) = g_ClipsCurrentEvaluationDepth;
  *(_DWORD *)(a1 + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = a1;
  ++g_ClipsEphemeralItemCount;
  result = 6 * *(_DWORD *)(a1 + 6) + 20;
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
  int v1; // ebx
  int v2; // ecx
  int v3; // edx
  unsigned int v4; // edx

  result = g_ClipsEphemeralMultifieldListHead;
  v1 = 0;
  if ( g_ClipsEphemeralMultifieldListHead )
  {
    do
    {
      while ( 1 )
      {
        v2 = *(_DWORD *)(result + 10);
        if ( *(__int16 *)(result + 4) <= g_ClipsCurrentEvaluationDepth || *(_DWORD *)result )
          break;
        --g_ClipsEphemeralItemCount;
        g_ClipsEphemeralItemBytes -= 6 * *(_DWORD *)(result + 6) + 20;
        if ( *(_DWORD *)(result + 6) )
          v3 = *(_DWORD *)(result + 6);
        else
          v3 = 1;
        v4 = 6 * (v3 - 1) + 20;
        g_ClipsMemPoolReturnBucketIndex = v4;
        if ( v4 >= 0x1F4 )
        {
          Mem_SmallBlockRelease((_DWORD *)result, v4);
        }
        else
        {
          g_ClipsMemFreeListTemp = result;
          *(_DWORD *)result = *(_DWORD *)(g_ClipsMemoryTable + 4 * v4);
          *(_DWORD *)(4 * g_ClipsMemPoolReturnBucketIndex + g_ClipsMemoryTable) = g_ClipsMemFreeListTemp;
        }
        if ( v1 )
        {
          *(_DWORD *)(v1 + 10) = v2;
          result = v2;
          if ( !v2 )
            return result;
        }
        else
        {
          g_ClipsEphemeralMultifieldListHead = v2;
          result = v2;
          if ( !v2 )
            return result;
        }
      }
      v1 = result;
      result = *(_DWORD *)(result + 10);
    }
    while ( v2 );
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
int  Rules_AssignMultifieldRangeCopy(_DWORD *a1, int a2)
{
  int v3; // eax
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // ebx
  int v7; // edx
  int result; // eax

  a1[1] = 4;
  a1[3] = 0;
  v3 = *(_DWORD *)(a2 + 16) - *(_DWORD *)(a2 + 12);
  a1[4] = v3;
  v4 = Rules_CreateMultifield(v3 + 1);
  v6 = *(_DWORD *)(v5 + 16) + 1;
  *(_DWORD *)(v5 + 8) = v4;
  result = 6 * v6;
  qmemcpy(
    (void *)(*(_DWORD *)(v5 + 8) + 14),
    (const void *)(6 * *(_DWORD *)(v7 + 12) + *(_DWORD *)(v7 + 8) + 14),
    6 * v6);
  return result;
}
// 48D035: variable 'v5' is possibly undefined
// 48D048: variable 'v7' is possibly undefined

//----- (0048D080) --------------------------------------------------------
_DWORD * Rules_CloneMultifield(int a1)
{
  _DWORD *v1; // ebx
  int v2; // edx

  v1 = Rules_CreateMultifield(*(_DWORD *)(a1 + 6));
  qmemcpy((char *)v1 + 14, (const void *)(v2 + 14), 6 * *(_DWORD *)(v2 + 6));
  return v1;
}
// 48D09B: variable 'v2' is possibly undefined

//----- (0048D0C0) --------------------------------------------------------
int  Rules_PrintMultifieldRange(int result, int a2, int a3, int a4, int a5)
{
  int v5; // esi
  int v7; // edi
  int v8; // ecx
  __int16 *v9; // edi
  int v10; // ecx

  v5 = result;
  v7 = a2 + 14;
  if ( a5 )
    result = Output_Write(result, (int)asc_5045B8, a3);
  v8 = a4;
  if ( a4 <= a3 )
  {
    v9 = (__int16 *)(6 * a4 + v7);
    do
    {
      result = Rules_PrintAtomValue(v5, *v9, *(int **)(v9 + 1));
      v8 = v10 + 1;
      v9 += 3;
      if ( v8 <= a3 )
        result = Output_Write(v5, (int)asc_5045BC, v8);
    }
    while ( v8 <= a3 );
  }
  if ( a5 )
    return Output_Write(v5, (int)asc_5045C0, v8);
  return result;
}
// 48D0F1: variable 'v10' is possibly undefined
// 48D107: variable 'v8' is possibly undefined

//----- (0048D140) --------------------------------------------------------
_DWORD * Rules_StoreEvaluatedNodesAsMultifield(_DWORD *a1, int a2, int a3, double a4)
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

  out = (EvalResultBuffer *)a1;
  node_count = AST_CountListNodes(a2);
  if ( !node_count )
  {
    out->type = 4;
    out->begin = 0;
    out->end = -1;
    multifield_raw = a3 ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
    out->value = (int)(uintptr_t)multifield_raw;
    return multifield_raw;
  }

  allocation_size = sizeof(*entries) * node_count;
  entries_raw = Mem_NewArray(allocation_size);
  entries = (EvalMultifieldEntry *)(uintptr_t)(unsigned int)(uintptr_t)entries_raw;
  output_count = 0;
  node = a2;
  for ( entry_index = 0; entry_index < node_count; ++entry_index )
  {
    memset(&parsed, 0, sizeof(parsed));
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)node, (_DWORD *)&parsed, node, a4);
    if ( g_ClipsEvaluationError )
    {
      out->type = 4;
      out->begin = 0;
      out->end = -1;
      multifield_raw = a3 ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
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

  multifield_raw = a3 ? Rules_CreateEphemeralMultifield(output_count) : Rules_CreateMultifield(output_count);
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
signed int  Rules_MultifieldRangesEqual(_DWORD *a1, _DWORD *a2)
{
  int v3; // eax
  __int16 *v4; // ecx
  __int16 *v5; // edx

  v3 = a1[4] - a1[3] + 1;
  if ( v3 == a2[4] - a2[3] + 1 )
  {
    v4 = (__int16 *)(a1[2] + 14 + 6 * a1[3]);
    v5 = (__int16 *)(6 * a2[3] + a2[2] + 14);
    if ( !v3 )
      return 1;
    while ( *v4 == *v5 && *(_DWORD *)(v4 + 1) == *(_DWORD *)(v5 + 1) )
    {
      if ( --v3 > 0 )
      {
        v4 += 3;
        v5 += 3;
      }
      if ( !v3 )
        return 1;
    }
  }
  return 0;
}

//----- (0048D440) --------------------------------------------------------
int  Rules_MultifieldsEqual(int a1, int a2)
{
  int v2; // edi
  int v3; // ecx
  int v4; // esi
  __int16 *v5; // eax
  __int16 *v6; // ebx
  __int16 *i; // ecx
  int result; // eax

  v2 = *(_DWORD *)(a1 + 6);
  v3 = *(_DWORD *)(a2 + 6);
  v4 = 0;
  if ( v2 == v3 )
  {
    v5 = (__int16 *)(a1 + 14);
    v6 = (__int16 *)(a2 + 14);
    if ( v3 <= 0 )
      return 1;
    for ( i = v5; *i == *v6; i += 3 )
    {
      if ( *i == 4 )
      {
        result = Rules_MultifieldsEqual(*(_DWORD *)(i + 1), *(_DWORD *)(v6 + 1));
        if ( !result )
          return result;
      }
      else if ( *(_DWORD *)(i + 1) != *(_DWORD *)(v6 + 1) )
      {
        return 0;
      }
      v6 += 3;
      if ( ++v4 >= v2 )
        return 1;
    }
  }
  return 0;
}
// 48D478: variable 'i' is possibly undefined

//----- (0048D4B0) --------------------------------------------------------
signed int __fastcall Rules_ReportInvalidSlotError(int a1, int a2)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v6);
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
int __fastcall Rules_ReportMultifieldAssertIntoSingleSlotError(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *v6; // edx
  char *v7; // eax
  int v8; // ecx
  int v9; // ecx
  char *v10; // eax
  char *v11; // edx
  int v12; // ecx

  Rules_PrintErrorID((int)aTmpltfun, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttemptedToAss, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIntoTheSingleF, v4);
  if ( v5 )
  {
    v7 = g_IO_LogicalNameTable_WError[0];
    v6 = *(char **)(*(_DWORD *)v5 + 16);
  }
  else
  {
    v6 = aUnknown_2;
    v7 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)v7, (int)v6, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfDeftemplate, v8);
  if ( a2 )
  {
    v10 = g_IO_LogicalNameTable_WError[0];
    v11 = *(char **)(*(_DWORD *)a2 + 16);
  }
  else
  {
    v11 = aUnknown_2;
    v10 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)v10, (int)v11, v9);
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
int  Rules_CheckFactAgainstSlotConstraints(int a1)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ebx
  __int16 *v6; // edx
  int v7; // ecx
  int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int *v11; // ecx
  int v12; // [esp+0h] [ebp-44h] BYREF
  int v13; // [esp+4h] [ebp-40h]
  int v14; // [esp+8h] [ebp-3Ch]
  int v15; // [esp+Ch] [ebp-38h]
  int v16; // [esp+10h] [ebp-34h]
  _BYTE v17[44]; // [esp+18h] [ebp-2Ch] BYREF

  result = Rules_DynamicConstraintCheckingEnabled();
  if ( result )
  {
    v3 = *(_DWORD *)(a1 + 16);
    if ( v3 )
    {
      if ( (*(_BYTE *)(v3 + 24) & 1) == 0 )
      {
        v4 = *(_DWORD *)(v3 + 20);
        v5 = 0;
        if ( v4 )
        {
          while ( 1 )
          {
            v6 = (__int16 *)(a1 + 54 + 6 * v5);
            if ( (*(_BYTE *)(v4 + 4) & 1) != 0 )
            {
              v13 = 4;
              v14 = *(_DWORD *)(v6 + 1);
              v15 = 0;
              ++v5;
              v16 = *(_DWORD *)(*(_DWORD *)(v6 + 1) + 6) - 1;
            }
            else
            {
              v13 = *v6;
              ++v5;
              v14 = *(_DWORD *)(v6 + 1);
            }
            result = Rules_CheckFieldAgainstConstraint(&v12, *(_DWORD *)(v4 + 8));
            v8 = result;
            if ( result )
              break;
            v4 = *(_DWORD *)(v7 + 16);
            if ( !v4 )
              return result;
          }
          sprintf_(v17, "fact f-%-5ld ", *(_DWORD *)(a1 + 24));
          Rules_PrintErrorID((int)aCstrnchk_0, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlotValue, v9);
          Rules_PrintDataObject((int)g_IO_LogicalNameTable_WError[0], (int)&v12);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_5046F0, v10);
          Rules_PrintConstraintViolationMessage(0, (int)v17, 0, 0, *v11, 0, v8, v11[2], 1);
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
signed int  Rules_CheckLiteralSlotValueConstraint(int *a1, int a2)
{
  int v3; // edx
  signed int v5; // eax
  int *v6; // ecx
  int v7; // edx
  char *v8; // eax

  if ( !Rules_StaticConstraintCheckingEnabled() )
    return 1;
  v5 = Rules_CheckFieldExprListAgainstConstraint(a1, *(_DWORD *)(v3 + 8));
  v7 = v5;
  if ( !v5 )
    return 1;
  if ( v5 == 5 )
    v8 = aLiteralSlotVal;
  else
    v8 = aALiteralSlotVa;
  Rules_PrintConstraintViolationMessage((int)v8, a2, 0, 1, *v6, 0, v7, v6[2], 1);
  return 0;
}
// 48D74D: variable 'v3' is possibly undefined
// 48D76E: variable 'v6' is possibly undefined

//----- (0048D790) --------------------------------------------------------
int  Lexer_GetSlotByOrdinal(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = *(_DWORD *)(a1 + 20);
  v4 = 0;
  if ( !result )
    return 0;
  while ( v4 != a2 )
  {
    result = *(_DWORD *)(result + 16);
    ++v4;
    if ( !result )
      return 0;
  }
  return result;
}

//----- (0048D7B0) --------------------------------------------------------
signed int  Lexer_FindSymbolIndex(int a1, int a2)
{
  _DWORD *v3; // eax
  int v4; // edx

  v3 = *(_DWORD **)(a1 + 20);
  v4 = 1;
  if ( !v3 )
    return 0;
  while ( a2 != *v3 )
  {
    v3 = (_DWORD *)v3[4];
    ++v4;
    if ( !v3 )
      return 0;
  }
  return v4;
}

//----- (0048D7E0) --------------------------------------------------------
signed int  Rules_PrintTemplateFactSlots(int a1, int a2, int a3)
{
  __int16 *v4; // ebp
  _DWORD *v5; // edi
  int v6; // ecx
  int v7; // ecx
  int v8; // edi
  int v9; // ecx
  int v10; // ecx
  int v12; // ebx

  v4 = (__int16 *)(a2 + 54);
  v5 = *(_DWORD **)(a2 + 16);
  Output_Write(a1, (int)asc_504720, a3);
  Output_Write(a1, *(_DWORD *)(*v5 + 16), v6);
  if ( v5[5] )
    Output_Write(a1, (int)asc_5046F0, v7);
  v8 = v5[5];
  if ( v8 )
  {
    while ( 1 )
    {
      Output_Write(a1, (int)asc_504720, v7);
      Output_Write(a1, *(_DWORD *)(*(_DWORD *)v8 + 16), v9);
      if ( (*(_BYTE *)(v8 + 4) & 1) != 0 )
      {
        v12 = *(_DWORD *)(v4 + 1);
        if ( *(int *)(v12 + 6) > 0 )
        {
          Output_Write(a1, (int)asc_5046F0, v10);
          Lexer_OutputFieldRange(a1, *(_DWORD *)(v4 + 1), *(_DWORD *)(v12 + 6) - 1, 0, 0);
        }
      }
      else
      {
        Output_Write(a1, (int)asc_5046F0, v10);
        Rules_PrintAtomValue(a1, *v4, *(int **)(v4 + 1));
      }
      Output_Write(a1, (int)asc_504724, v10);
      v8 = *(_DWORD *)(v8 + 16);
      v4 += 3;
      if ( !v8 )
        break;
      Output_Write(a1, (int)asc_5046F0, v7);
    }
  }
  return Output_Write(a1, (int)asc_504724, v7);
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
_DWORD * Lexer_FindSlotWithIndex(int a1, int a2, _DWORD *a3)
{
  _DWORD *result; // eax

  *a3 = 1;
  result = *(_DWORD **)(a1 + 20);
  if ( result )
  {
    while ( a2 != *result )
    {
      ++*a3;
      result = (_DWORD *)result[4];
      if ( !result )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    *a3 = -1;
    return 0;
  }
  return result;
}

//----- (0048D970) --------------------------------------------------------
int  Rules_CreateDeftemplateRecord(int a1, char a2)
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
  *(_DWORD *)template_record = a1;
  *(_BYTE *)(template_record + 24) &= 0xFEu;
  *(_DWORD *)(template_record + 20) = 0;
  *(_DWORD *)(template_record + 24) |= a2 & 1;
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
        int a2,
        _DWORD *a3,
        int a4,
        double a5,
        int a6)
{
  int v6; // esi
  int v8; // ebx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int v14; // [esp+0h] [ebp-1Ch]
  int v16; // [esp+Ch] [ebp-10h]

  v14 = result;
  v6 = a2;
  if ( a2 )
  {
    v16 = *(_DWORD *)(a2 + 20) << 16 >> 24;
    g_ClipsFactMatchMarkerList = (int)a3;
    g_CurrentPatternFact = result;
    do
    {
      v8 = (unsigned __int8)*(_DWORD *)(v6 + 20);
      if ( *(_DWORD *)(v6 + 20) << 16 >> 24 == v16 )
        v8 += a4;
      result = Rules_ShouldProcessPatternNode(v6);
      if ( !result )
      {
        BYTE1(result) = *(_BYTE *)(v6 + 12);
        if ( (result & 0x100) != 0 )
        {
          if ( (*(_BYTE *)(v6 + 12) & 0x40) == 0
            || !g_ClipsFactMatchMarkerList
            || (v12 = *(_DWORD *)(v6 + 20) << 16 >> 24, *(__int16 *)(g_ClipsFactMatchMarkerList + 4) != v12)
            || (v13 = 6 * v12 + g_CurrentPatternFact, *(_WORD *)(v13 + 54) != 4)
            || (v9 = *(_DWORD *)(*(_DWORD *)(v13 + 56) + 6), v8 + (*(_DWORD *)(v6 + 20) << 8 >> 24) == v9) )
          {
            if ( Rules_EvaluatePatternNetworkTest(v6, *(_DWORD *)(v6 + 24), 0, a5) )
            {
              if ( (*(_BYTE *)(v6 + 12) & 4) != 0 )
                Rules_AttachFactPatternMatch(v14, a3, (signed int *)v6, a5);
              v11 = v6;
              v10 = 0;
              goto LABEL_7;
            }
          }
        }
        else
        {
          if ( (result & 0x200) == 0 )
            continue;
          if ( *(_DWORD *)(v6 + 20) << 16 >> 24 == v16 )
            Rules_MatchMultifieldWildcardInPattern(v6, (int)a3, a4, a6, a5);
          else
            Rules_MatchMultifieldWildcardInPattern(v6, (int)a3, 0, a6, a5);
        }
      }
      v10 = 1;
      v11 = v6;
LABEL_7:
      result = Rules_AdvancePatternNetworkNode(v10, v11);
      v6 = result;
    }
    while ( v6 );
  }
  return result;
}
// 48DAE1: conditional instruction was optimized away because %var_18.4==0
// 48DB2F: variable 'v9' is possibly undefined
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DBA0) --------------------------------------------------------
int  Rules_MatchMultifieldWildcardInPattern(int a1, int a2, int a3, int a4, double a5)
{
  int v6; // edi
  _DWORD *v7; // edx
  signed int v8; // eax
  int v9; // eax
  int v10; // edi
  int result; // eax
  int v12; // edi
  int v13; // ebp
  int v14; // edx
  _DWORD *v17; // [esp+Ch] [ebp-10h]

  v6 = *(_DWORD *)(g_CurrentPatternFact + 6 * (*(_DWORD *)(a1 + 20) << 16 >> 24) + 56);
  v7 = *(_DWORD **)(g_ClipsMemoryTable + 80);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(g_ClipsMemoryTable + 80) = *v7;
    v8 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  *(_DWORD *)v8 = (unsigned __int8)*(_DWORD *)(a1 + 20) - 1;
  *(_WORD *)(v8 + 4) = HIBYTE(*(_WORD *)(a1 + 20));
  v17 = (_DWORD *)v8;
  *(_DWORD *)(v8 + 8) = (unsigned __int8)*(_DWORD *)(a1 + 20) - 1 + a3;
  *(_DWORD *)(v8 + 16) = 0;
  if ( a4 )
    *(_DWORD *)(a4 + 16) = v8;
  else
    g_ClipsFactMatchMarkerList = v8;
  if ( (*(_BYTE *)(a1 + 12) & 0x40) != 0 )
  {
    v9 = *(_DWORD *)(v6 + 6) - ((*(_DWORD *)(a1 + 20) << 8 >> 24) + 1);
    v10 = v17[2];
    v17[3] = v9;
    if ( v9 < v10 )
      v17[3] = v10 - 1;
    if ( !*(_DWORD *)(a1 + 24) || Rules_EvaluatePatternNetworkTest(a1, *(_DWORD *)(a1 + 24), a4, a5) )
    {
      if ( (*(_BYTE *)(a1 + 12) & 4) != 0 )
        Rules_AttachFactPatternMatch(g_CurrentPatternFact, (_DWORD *)g_ClipsFactMatchMarkerList, (signed int *)a1, a5);
      Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(a1 + 28), g_ClipsFactMatchMarkerList, 0, a5, (int)v17);
    }
    g_ClipsMemFreeListTemp = (int)v17;
    *v17 = *(_DWORD *)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    if ( a4 )
      *(_DWORD *)(a4 + 16) = 0;
LABEL_14:
    result = a2;
    g_ClipsFactMatchMarkerList = a2;
    return result;
  }
  v12 = *(_DWORD *)(v6 + 6) - (*(_DWORD *)(v8 + 8) + (*(_DWORD *)(a1 + 20) << 8 >> 24));
  if ( v12 >= 0 )
  {
    v13 = a3 + v12 - 1;
    do
    {
      v17[3] = v12 - 1 + v17[2];
      v14 = *(_DWORD *)(a1 + 24);
      if ( !v14 || Rules_EvaluatePatternNetworkTest(a1, v14, a3, a5) )
        Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(a1 + 28), g_ClipsFactMatchMarkerList, v13, a5, (int)v17);
      --v12;
      --v13;
    }
    while ( v12 >= 0 );
  }
  g_ClipsMemFreeListTemp = (int)v17;
  *v17 = *(_DWORD *)(g_ClipsMemoryTable + 80);
  *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
  if ( !a4 )
    goto LABEL_14;
  *(_DWORD *)(a4 + 16) = 0;
  result = a2;
  g_ClipsFactMatchMarkerList = a2;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DDF0) --------------------------------------------------------
int  Rules_AdvancePatternNetworkNode(int a1, int a2)
{
  g_ClipsEvaluationError = 0;
  if ( a1 || !*(_DWORD *)(a2 + 28) )
  {
    while ( !*(_DWORD *)(a2 + 40) )
    {
      a2 = *(_DWORD *)(a2 + 32);
      if ( !a2 )
        return a2;
      if ( (*(_BYTE *)(a2 + 12) & 2) != 0 )
        return 0;
    }
    return *(_DWORD *)(a2 + 40);
  }
  else
  {
    return *(_DWORD *)(a2 + 28);
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (0048DE30) --------------------------------------------------------
int * Rules_AttachFactPatternMatch(int a1, _DWORD *a2, signed int *a3, double a4)
{
  int *partial_match; // esi
  int link; // eax
  int old_fact_links; // ebx
  int join; // ecx
  int *result; // eax

  partial_match = (int *)(uintptr_t)(unsigned int)Rules_AppendExpressionValueNode(a1, a2, a3);
  old_fact_links = *(_DWORD *)(a1 + 20);
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
  *(_DWORD *)(a1 + 20) = link;
  *(_DWORD *)link = old_fact_links;
  *(_DWORD *)(link + 8) = (int)a3;
  *(_DWORD *)(link + 4) = (int)partial_match;
  result = (int *)(uintptr_t)(unsigned int)link;
  join = a3[2];
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
int  Rules_EvaluatePatternNetworkTest(signed int a1, int a2, int a3, double a4)
{
  __int16 v5; // ax
  int v6; // eax
  int v7; // ecx
  int result; // eax
  int v9; // ecx
  int v10; // esi
  int v11; // esi
  int v12; // esi
  int v13; // ecx
  int v14; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-24h] BYREF
  int v17; // [esp+1Ch] [ebp-4h]

  v17 = a3;
  if ( !a2 )
    return 1;
  v5 = *(_WORD *)a2;
  if ( *(_WORD *)a2 >= 0x20u )
  {
    if ( *(_WORD *)a2 <= 0x20u )
    {
      v11 = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = a2;
      result = Rules_TestPatternFieldSimple(*(_DWORD *)(a2 + 2));
      g_ClipsCurrentExpression = v11;
      return result;
    }
    if ( v5 == 33 )
    {
      v10 = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = a2;
      result = Rules_TestPatternNestedField(*(_DWORD *)(a2 + 2));
      g_ClipsCurrentExpression = v10;
      return result;
    }
  }
  else if ( v5 == 25 )
  {
    v12 = g_ClipsCurrentExpression;
    g_ClipsCurrentExpression = a2;
    result = Rules_EvalMultifieldIndexInRange(*(_DWORD *)(a2 + 2), (uintptr_t)parsed);
    g_ClipsCurrentExpression = v12;
    return result;
  }
  v6 = *(_DWORD *)(a2 + 2);
  if ( v6 == g_ClipsSymbolOr )
  {
    v7 = *(_DWORD *)(a2 + 6);
    if ( v7 )
    {
      while ( 1 )
      {
        result = Rules_EvaluatePatternNetworkTest(a1, v7, v7, a4);
        if ( result == 1 )
          break;
        if ( g_ClipsEvaluationError )
          return 0;
        v7 = *(_DWORD *)(v7 + 10);
        if ( !v7 )
          return 0;
      }
      if ( !g_ClipsEvaluationError )
        return result;
    }
    return 0;
  }
  if ( v6 != g_Clips_SymbolAnd )
  {
    if ( Parser_ParseForm((__int16 *)a2, parsed, a2, a4) )
    {
      Rules_ReportPatternNetworkError(a1);
      return 0;
    }
    if ( parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2 )
      return g_ClipsFalseSymbol ^ parsed[2];
    return 1;
  }
  v13 = *(_DWORD *)(a2 + 6);
  if ( !v13 )
    return 1;
  while ( 1 )
  {
    result = Rules_EvaluatePatternNetworkTest(a1, v13, v13, a4);
    if ( !result )
      break;
    if ( g_ClipsEvaluationError )
      return 0;
    v13 = *(_DWORD *)(v13 + 10);
    if ( !v13 )
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
signed int  Rules_ReportPatternNetworkError(signed int a1)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // edx
  _DWORD *v8; // edx
  int i; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // [esp-4h] [ebp-4Ch]
  _BYTE v15[72]; // [esp+0h] [ebp-48h] BYREF

  Rules_PrintErrorID((int)aFactmch, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_0, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCurrentlyActiv, v4);
  Rules_PrintFact((int)g_IO_LogicalNameTable_WError[0], g_CurrentPatternFact);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504794, v5);
  v7 = *(_DWORD *)(g_CurrentPatternFact + 16);
  if ( (*(_BYTE *)(v7 + 24) & 1) != 0 )
  {
    sprintf_(v15, "   Problem resides in field #%d\n", (unsigned __int8)*(_DWORD *)(a1 + 20));
  }
  else
  {
    v14 = v6;
    v8 = *(_DWORD **)(v7 + 20);
    for ( i = 0; i < *(_DWORD *)(a1 + 20) << 16 >> 24; ++i )
      v8 = (_DWORD *)v8[4];
    sprintf_(v15, "   Problem resides in slot %s\n", *(const char **)(*v8 + 16));
    v10 = v14;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v15, v10);
  Rules_ReportPatternNetworkRules(a1, 0, v11);
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
signed int  Rules_ReportPatternNetworkRules(signed int result, int a2, int j)
{
  signed int i; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  _BYTE v8[68]; // [esp+0h] [ebp-4Ch] BYREF
  int v9; // [esp+44h] [ebp-8h]

  v9 = j;
  for ( i = result; i; i = *(_DWORD *)(i + 40) )
  {
    if ( (*(_BYTE *)(i + 12) & 4) != 0 )
    {
      for ( j = *(_DWORD *)(i + 8); j; j = *(_DWORD *)(v7 + 32) )
      {
        v5 = Rules_CountJoinNetworkEntryNodes(j);
        sprintf_(v8, "      Of pattern #%d in rule(s):\n", v5);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v8, v6);
        result = Rules_PrintJoinNetworkSharingReport();
      }
    }
    else
    {
      result = Rules_ReportPatternNetworkRules(*(_DWORD *)(i + 28), 1, j);
    }
    if ( !a2 )
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
BOOL  Rules_ShouldProcessPatternNode(int a1)
{
  return g_IncrementalResetInProgress && (*(_BYTE *)(a1 + 12) & 8) == 0;
}
// 51B354: using guessed type int dword_51B354;

//----- (0048E1A0) --------------------------------------------------------
void  Rules_PropagatePatternNodeResetFlag(int a1, char a2)
{
  int v2; // edx

  if ( (*(_BYTE *)(a1 + 12) & 8) != 0 )
  {
    v2 = 8 * (a2 & 1);
    while ( a1 )
    {
      *(_BYTE *)(a1 + 12) &= ~8u;
      *(_DWORD *)(a1 + 12) |= v2;
      a1 = *(_DWORD *)(a1 + 32);
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
int * Rules_DriveJoinNetwork(int *result, char *a2, int a3, double a4)
{
  int v5; // ecx
  int *v6; // ebp
  int *v7; // esi
  char v8; // dl
  char v9; // bh
  int *v10; // ecx
  int i; // edx
  int *v12; // [esp+0h] [ebp-20h]
  signed int v13; // [esp+4h] [ebp-1Ch]
  int *v14; // [esp+8h] [ebp-18h]

  v12 = result;
  v5 = g_IncrementalResetInProgress;
  v6 = 0;
  v7 = 0;
  v14 = 0;
  if ( g_IncrementalResetInProgress && (*a2 & 0x10) == 0 )
    return result;
  if ( !a3 )
  {
    v8 = *a2;
    if ( (*a2 & 8) != 0 || (v8 & 4) != 0 )
    {
      result = (int *)Rules_MultifieldAppendValue(result, 0, *(_DWORD *)a2 << 30 >> 31, *((_DWORD *)a2 + 9) != 0);
      *(_BYTE *)result |= 0x30u;
      result[1] = *((_DWORD *)a2 + 2);
      v12 = result;
      *((_DWORD *)a2 + 2) = result;
    }
  }
  v9 = *a2;
  if ( (*a2 & 1) != 0 )
    return Rules_AddJoinLeftMemoryEntry((int)a2, v12, v5, a4);
  if ( a3 )
  {
    if ( a3 == 1 )
    {
      if ( (v9 & 8) != 0 || (v9 & 4) != 0 )
        v7 = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(a2 + 8);
      else
        v7 = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(a2 + 24) + 8);
      result = v12;
      v14 = v12;
    }
    else
    {
      Rules_ReportSystemError(a3, 1);
      result = (int *)IO_RunRouterExitCallbacks();
    }
  }
  else
  {
    if ( (v9 & 4) != 0 )
      v7 = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(a2 + 16) + 8);
    else
      v7 = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(a2 + 16);
    v6 = v12;
  }
  while ( v7 )
  {
    if ( a3 == 1 )
    {
      v6 = v7;
      if ( (*(_BYTE *)v7 & 0x20) == 0 || (*a2 & 8) != 0 || (*a2 & 4) != 0 )
      {
        if ( ((*a2 & 8) != 0 || (*a2 & 4) != 0) && (*(_BYTE *)v7 & 0x20) != 0 )
          goto LABEL_31;
        goto LABEL_33;
      }
      v7 = (int *)(uintptr_t)(unsigned int)v7[1];
    }
    else
    {
      v14 = v7;
LABEL_33:
      if ( *((_DWORD *)a2 + 3) )
      {
        result = (int *)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(a2 + 12), v6, (_BYTE *)a2, (int)v14, a4);
        v13 = (signed int)result;
        if ( g_ClipsEvaluationError )
        {
          if ( (*a2 & 8) != 0 )
            v13 = 1;
          result = (int *)Lexer_ErrorRecover(0);
        }
      }
      else
      {
        v13 = 1;
        if ( (*a2 & 4) != 0 )
        {
          v10 = v14;
          result = v6;
          for ( i = 0; i < (int)(((unsigned int)(*v6 << 17) >> 23) - 1); ++i )
          {
            if ( result[2] != v10[2] )
              goto LABEL_31;
            ++v10;
            ++result;
          }
        }
      }
      if ( v13 )
      {
        if ( (*a2 & 8) != 0 || (*a2 & 4) != 0 )
        {
          if ( a3 == 1 )
          {
            result = (int *)Rules_ProcessJoinMemoryMatches((int)a2, v7, (int)v14, a4);
            v7 = (int *)(uintptr_t)(unsigned int)v7[1];
          }
          else
          {
            if ( a3 )
              goto LABEL_31;
            result = &v12[(unsigned int)(*v12 << 17) >> 23];
            v7 = 0;
            result[1] = (int)v14;
          }
        }
        else
        {
          result = Rules_CreateJoinPartialMatch(v6, v14, a2, a4);
          v7 = (int *)(uintptr_t)(unsigned int)v7[1];
        }
      }
      else
      {
LABEL_31:
        v7 = (int *)(uintptr_t)(unsigned int)v7[1];
      }
    }
  }
  BYTE1(result) = *a2;
  if ( ((*a2 & 8) != 0 || (BYTE1(result) & 4) != 0) && !a3 )
  {
    result = &v12[(unsigned int)(*v12 << 17) >> 23];
    if ( !result[1] )
      return Rules_AddJoinRightMemoryEntry((int)a2, v12, a4);
  }
  return result;
}
// 48E2F0: variable 'v5' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51B354: using guessed type int dword_51B354;

//----- (0048E4A0) --------------------------------------------------------
signed int  Rules_EvaluateJoinExpression(
        __int16 *a1,
        _WORD *a2,
        _BYTE *a3,
        int a4,
        double a5)
{
  __int16 *v5; // esi
  int v7; // edi
  int v8; // eax
  char v9; // dl
  int v10; // eax
  int v11; // edi
  int v12; // eax
  __int16 v13; // ax
  __int16 v15; // ax
  uintptr_t evaluator; // eax
  int v16; // ecx
  __int16 v18; // ax
  __int16 v19; // ax
  __int16 v20; // ax
  __int16 v21; // ax
  int v22; // edx
  int v23; // ecx
  __int16 v24; // ax
  __int16 v25; // ax
  __int16 v26; // ax
  _DWORD v27[6]; // [esp+0h] [ebp-3Ch] BYREF
  int v28; // [esp+18h] [ebp-24h]
  int v29; // [esp+1Ch] [ebp-20h]
  int v30; // [esp+20h] [ebp-1Ch]
  int v31; // [esp+24h] [ebp-18h]
  int v32; // [esp+28h] [ebp-14h]
  _BYTE *v33; // [esp+2Ch] [ebp-10h]

  v5 = a1;
  v31 = a4;
  v33 = a3;
  v7 = 1;
  if ( !a1 )
    return 1;
  v30 = g_Clips_CurrentPartialMatch;
  g_Clips_CurrentPartialMatch = (int)a2;
  v29 = g_Rules_GlobalRHSBinds;
  g_Rules_GlobalRHSBinds = a4;
  v8 = g_CurrentPatternEntityPtr;
  g_CurrentPatternEntityPtr = (int)a3;
  v9 = *a3;
  v28 = v8;
  if ( (v9 & 8) != 0 )
  {
    v15 = ((unsigned __int16)(2 * *a2) >> 7) - 1;
    *a2 &= 0x803Fu;
    *(_DWORD *)a2 |= (v15 & 0x1FF) << 6;
  }
  v10 = *(_DWORD *)(v5 + 1);
  if ( v10 == g_Clips_SymbolAnd )
  {
    v5 = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)v5 + 6);
    v32 = 1;
  }
  else if ( v10 == g_ClipsSymbolOr )
  {
    v5 = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)v5 + 6);
    v32 = 0;
  }
  else
  {
    v32 = 1;
  }
  while ( v5 )
  {
    v11 = g_Clips_PrimitiveEntityTable[*v5];
    evaluator = v11 ? (uintptr_t)(unsigned int)*(_DWORD *)(v11 + 16) : 0;
    if ( evaluator )
    {
      v16 = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = (int)(uintptr_t)v5;
      v7 = ((int (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)((char *)v5 + 2), v27, a5);
      g_ClipsCurrentExpression = v16;
    }
    else
    {
      v12 = *(_DWORD *)(v5 + 1);
      if ( v12 == g_ClipsSymbolOr )
      {
        v7 = 0;
        if ( Rules_EvaluateJoinExpression(v5, a2, v33, v31, a5) == 1 )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*v33 & 8) != 0 )
            {
              v19 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
              *a2 &= 0x803Fu;
              *(_DWORD *)a2 |= (v19 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
          v7 = 1;
        }
        else if ( g_ClipsEvaluationError )
        {
          if ( (*v33 & 8) != 0 )
          {
            v20 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
            *a2 &= 0x803Fu;
            *(_DWORD *)a2 |= (v20 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
      }
      else if ( v12 == g_Clips_SymbolAnd )
      {
        v7 = 1;
        if ( Rules_EvaluateJoinExpression(v5, a2, v33, v31, a5) )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*v33 & 8) != 0 )
            {
              v21 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
              *a2 &= 0x803Fu;
              *(_DWORD *)a2 |= (v21 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
        }
        else
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*v33 & 8) != 0 )
            {
              v13 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
              *a2 &= 0x803Fu;
              *(_DWORD *)a2 |= (v13 & 0x1FF) << 6;
            }
LABEL_14:
            g_Clips_CurrentPartialMatch = v30;
            g_Rules_GlobalRHSBinds = v29;
            g_CurrentPatternEntityPtr = v28;
            return 0;
          }
          v7 = 0;
        }
      }
      else
      {
        Parser_ParseForm(v5, v27, g_ClipsSymbolOr, a5);
        v7 = g_ClipsEvaluationError;
        if ( g_ClipsEvaluationError )
        {
          Rules_ReportJoinNetworkError((int)(uintptr_t)v33, 0);
          if ( (*v33 & 8) != 0 )
          {
            v24 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
            *a2 &= 0x803Fu;
            *(_DWORD *)a2 |= (v24 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
        if ( v27[2] != g_ClipsFalseSymbol || v27[1] != 2 )
          v7 = 1;
      }
    }
    if ( v32 == 1 && !v7 )
    {
      if ( (*v33 & 8) != 0 )
      {
        v18 = v32 + ((unsigned __int16)(2 * *a2) >> 7);
        *a2 &= 0x803Fu;
        *(_DWORD *)a2 |= (v18 & 0x1FF) << 6;
      }
      goto LABEL_14;
    }
    if ( !v32 && v7 == 1 )
    {
      if ( (*v33 & 8) != 0 )
      {
        v25 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
        *a2 &= 0x803Fu;
        *(_DWORD *)a2 |= (v25 & 0x1FF) << 6;
      }
      g_Clips_CurrentPartialMatch = v30;
      g_Rules_GlobalRHSBinds = v29;
      g_CurrentPatternEntityPtr = v28;
      return 1;
    }
    v5 = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)v5 + 10);
  }
  g_Clips_CurrentPartialMatch = v30;
  g_Rules_GlobalRHSBinds = v29;
  g_CurrentPatternEntityPtr = v28;
  if ( (*v33 & 8) != 0 )
  {
    v26 = ((unsigned __int16)(2 * *a2) >> 7) + 1;
    *a2 &= 0x803Fu;
    *(_DWORD *)a2 |= (v26 & 0x1FF) << 6;
  }
  return v7;
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
_DWORD * Rules_CreateJoinPartialMatch(_DWORD *a1, _DWORD *a2, _DWORD *a3, double a4)
{
  _DWORD *result; // eax
  int partial_match; // esi
  int action; // ebp
  uintptr_t join; // ecx

  result = Rules_MergeMultifieldValues(a1, a2, *a3 << 30 >> 31, a3[9] != 0);
  result[1] = a3[2];
  partial_match = (int)(uintptr_t)result;
  action = a3[9];
  a3[2] = result;
  if ( action )
    result = Rules_AddActivation(action, (int)(uintptr_t)result, a4);
  join = (uintptr_t)(unsigned int)a3[5];
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) == (uintptr_t)(unsigned int)(uintptr_t)a3 )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 1, a4);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 0, a4);
        join = (uintptr_t)(unsigned int)*(_DWORD *)(join + 28);
      }
      while ( join );
    }
  }
  return result;
}
// 48E923: conditional instruction was optimized away because ecx.4!=0

//----- (0048E960) --------------------------------------------------------
int  Rules_ProcessJoinMemoryMatches(int result, _BYTE *a2, int a3, double a4)
{
  _DWORD *v4; // ebp
  _BYTE *v6; // edx
  int v7; // esi

  v4 = (_DWORD *)result;
  BYTE1(result) = *a2;
  if ( (*a2 & 0x20) == 0 )
  {
    *a2 = BYTE1(result) | 0x20;
    if ( (result & 0x400) != 0 )
    {
      v6 = &a2[4 * (*(_DWORD *)a2 << 17 >> 23)];
      if ( *((_DWORD *)v6 + 2) )
        Rules_RemoveActivation(*((_DWORD **)v6 + 2), 1, 1);
    }
    v7 = v4[5];
    if ( v7 )
    {
      if ( v4 == *(_DWORD **)(v7 + 16) )
      {
        Rules_UpdateBetaMemoryOnRetract((_DWORD *)v4[5], (int)a2, 0, a4);
      }
      else
      {
        while ( v7 )
        {
          Rules_PropagateRetractToJoinNode(v7, *(_DWORD *)&a2[4 * (*(_DWORD *)a2 << 17 >> 23) + 4], (*v4 << 16 >> 25) - 1, (int)a2, a4, 0);
          v7 = *(_DWORD *)(v7 + 28);
        }
      }
    }
    if ( (*a2 & 8) != 0 )
      Rules_RemovePMDependencies((int)a2);
    *(_DWORD *)(*(_DWORD *)&a2[4 * (*(_DWORD *)a2 << 17 >> 23) + 4] + 8) = g_ReteGarbageAlphaMatchList;
    g_ReteGarbageAlphaMatchList = *(_DWORD *)&a2[4 * (*(_DWORD *)a2 << 17 >> 23) + 4];
    result = *(_DWORD *)a2 << 17 >> 23;
    *(_DWORD *)&a2[4 * result + 4] = a3;
  }
  return result;
}
// 51A978: using guessed type int dword_51A978;

//----- (0048EA40) --------------------------------------------------------
_DWORD * Rules_AddJoinRightMemoryEntry(int a1, _BYTE *a2, double a3)
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
  *a2 &= ~0x20u;
  *(_DWORD *)&a2[4 * (*(_DWORD *)a2 << 17 >> 23) + 4] = (int)(uintptr_t)result;
  if ( *(_DWORD *)(a1 + 36) )
    result = Rules_AddActivation(*(_DWORD *)(a1 + 36), (int)(uintptr_t)a2, a3);
  join = (uintptr_t)(unsigned int)*(_DWORD *)(a1 + 20);
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)a1 == (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)a2, (char *)join, 1, a3);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)a2, (char *)join, 0, a3);
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
_DWORD * Rules_AddJoinLeftMemoryEntry(int a1, int *a2, int a3, double a4)
{
  _DWORD *result; // eax
  signed int v7; // esi
  int v8; // edx
  int join; // ecx

  if ( !*(_DWORD *)(a1 + 12)
    || (result = (_DWORD *)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 12), 0, (_BYTE *)(uintptr_t)(unsigned int)a1, (int)a2, a4),
        a3 = 0,
        g_ClipsEvaluationError = 0,
        result) )
  {
    if ( (*(_BYTE *)a1 & 8) != 0 )
    {
      Rules_ReportSystemError(a3, 2);
      IO_RunRouterExitCallbacks();
    }
    result = Rules_MultifieldCopyWithMarkers(a2, *(_DWORD *)(a1 + 36) != 0, *(_DWORD *)a1 << 30 >> 31);
    result[1] = *(_DWORD *)(a1 + 8);
    v7 = (signed int)result;
    v8 = *(_DWORD *)(a1 + 36);
    *(_DWORD *)(a1 + 8) = result;
    if ( v8 )
      result = Rules_AddActivation(v8, (int)result, a4);
    join = *(_DWORD *)(a1 + 20);
    while ( join )
    {
      result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)v7, (char *)(uintptr_t)(unsigned int)join, 0, a4);
      join = *(_DWORD *)(join + 28);
    }
  }
  return result;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048EBA0) --------------------------------------------------------
signed int __fastcall Rules_ReportJoinNetworkError(int a1, int a2)
{
  uintptr_t join; // ecx
  char v7[64]; // [esp+0h] [ebp-48h] BYREF

  (void)a2;
  join = (uintptr_t)(unsigned int)a1;
  Rules_PrintErrorID((int)aDrive, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_1, 0);
  sprintf_(v7, "   Problem resides in join #%d in rule(s):\n", join ? (*(_DWORD *)join << 16) >> 25 : 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)(uintptr_t)v7, 0);
  Rules_ClearJoinNetworkMarkedFlags();
  Rules_PrintJoinNetworkNodeRuleOwners((int)join, (int)(uintptr_t)"      ");
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504874, 0);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048EC20) --------------------------------------------------------
int  Rules_AddLogicalDependencyLink(int a1, int a2)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // edx
  _DWORD *v5; // esi
  _DWORD *v6; // eax
  _DWORD *v7; // edi
  _DWORD *v8; // eax

  if ( !g_Rules_CurrentLogicalJoin )
  {
    if ( a2 )
      Rules_ReleaseLogicalSupportList(a1);
    return 1;
  }
  if ( a2 && !*(_DWORD *)(a1 + 4) )
    return 1;
  result = (int)Rules_FindLogicalDependencyEntry(g_Rules_CurrentLogicalJoin, g_Clips_CurrentPartialMatch);
  v4 = (_DWORD *)result;
  if ( result )
  {
    v5 = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *v5;
      v6 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *v6 = v3;
    v6[1] = v4[(*v4 << 17 >> 23) + 2 + (*v4 << 29 >> 31)];
    v4[(*v4 << 29 >> 31) + 2 + (*v4 << 17 >> 23)] = v6;
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 32);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *v7;
      v8 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *v8 = v4;
    v8[1] = *(_DWORD *)(v3 + 4);
    *(_DWORD *)(v3 + 4) = v8;
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
_DWORD * Rules_FindLogicalDependencyEntry(int a1, int a2)
{
  _DWORD *v3; // esi
  int v4; // ecx
  _DWORD *v5; // eax
  unsigned int i; // edx

  v3 = *(_DWORD **)(a1 + 8);
  if ( v3 )
  {
    while ( 2 )
    {
      v4 = a2;
      v5 = v3;
      for ( i = 0; ; ++i )
      {
        if ( i >= *v3 << 17 >> 23 )
          return v3;
        if ( v5[2] != *(_DWORD *)(v4 + 8) )
          break;
        v4 += 4;
        ++v5;
      }
      v3 = (_DWORD *)v3[1];
      if ( v3 )
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
_DWORD * Rules_RemoveDependencyLink(_DWORD *a1, int a2)
{
  uintptr_t head; // esi
  uintptr_t current; // eax
  uintptr_t previous; // ecx

  head = (uintptr_t)(unsigned int)(uintptr_t)a1;
  current = head;
  previous = 0;
  while ( current )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
    if ( a2 == *(_DWORD *)current )
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
int  Rules_RemoveEntityDependencies(_DWORD *a1)
{
  _DWORD *v2; // ecx
  int v3; // ebx
  _DWORD *v4; // esi
  _DWORD *v5; // ecx
  int result; // eax

  v2 = (_DWORD *)a1[(*a1 << 29 >> 31) + 2 + (*a1 << 17 >> 23)];
  if ( v2 )
  {
    do
    {
      v3 = *v2;
      v4 = (_DWORD *)v2[1];
      *(_DWORD *)(v3 + 4) = Rules_RemoveDependencyLink(*(_DWORD **)(*v2 + 4), (int)a1);
      g_ClipsMemFreeListTemp = (int)v5;
      *v5 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      v2 = v4;
    }
    while ( v4 );
  }
  result = (*a1 << 17 >> 23) + (*a1 << 29 >> 31);
  a1[result + 2] = 0;
  return result;
}
// 48EE78: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EEC0) --------------------------------------------------------
int  Rules_RemovePMDependencies(int result)
{
  _DWORD *v1; // edi
  _DWORD *v2; // ecx
  int v3; // ebx
  _DWORD *v4; // esi
  _DWORD *v5; // eax
  _DWORD *v6; // ecx

  v1 = (_DWORD *)result;
  if ( (*(_BYTE *)result & 8) != 0 )
  {
    v2 = *(_DWORD **)(result + 4 * ((*(_DWORD *)result << 17 >> 23) + (*(_DWORD *)result << 29 >> 31)) + 8);
    if ( v2 )
    {
      do
      {
        v3 = *v2;
        v4 = (_DWORD *)v2[1];
        v5 = Rules_RemoveDependencyLink(*(_DWORD **)(*v2 + 4), (int)v1);
        *(_DWORD *)(v3 + 4) = v5;
        if ( v5 )
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
        v2 = v4;
      }
      while ( v4 );
    }
    result = (*v1 << 17 >> 23) + (*v1 << 29 >> 31);
    v1[result + 2] = 0;
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
  _DWORD *v0; // eax
  int v1; // edx

  if ( !g_Rules_FlushingDependencyDestructors )
  {
    g_Rules_FlushingDependencyDestructors = 1;
    while ( g_ClipsPendingDependencyDestructorList )
    {
      v0 = (_DWORD *)g_ClipsPendingDependencyDestructorList;
      v1 = *(_DWORD *)g_ClipsPendingDependencyDestructorList;
      g_ClipsPendingDependencyDestructorList = *(_DWORD *)(g_ClipsPendingDependencyDestructorList + 4);
      g_ClipsMemFreeListTemp = (int)v0;
      *v0 = *(_DWORD *)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      (*(void (**)(void))(*(_DWORD *)v1 + 12))();
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
  _DWORD **v2; // ecx
  int v3; // ecx
  signed int v4; // eax
  int v5; // ecx

  if ( !*(_DWORD *)(result + 4) )
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone, a2);
  v2 = *(_DWORD ***)(result + 4);
  do
  {
    Rules_PrintArgumentValueList((int)g_IO_LogicalName_WDisplay, *v2);
    v4 = Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504880, v3);
    v2 = *(_DWORD ***)(v5 + 4);
  }
  while ( v2 );
  return v4;
}
// 48EFDB: conditional instruction was optimized away because edx.4!=0
// 48EFF3: variable 'v3' is possibly undefined
// 48EFF8: variable 'v5' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F020) --------------------------------------------------------
signed int  Rules_PrintDependentList(int a1, int a2)
{
  int v4; // ecx
  int v5; // esi
  _DWORD **v6; // ecx
  int v7; // ecx
  _DWORD *v9; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD v10[6]; // [esp+4h] [ebp-18h] BYREF

  v10[4] = a2;
  v9 = 0;
  v10[0] = 0;
  Rules_FindPatternParser(v10, &v9);
  v5 = 0;
  while ( v9 )
  {
    v6 = (_DWORD **)v9[1];
    if ( v6 )
    {
      while ( Rules_ArrayContainsValue(a1, *v6) != 1 )
      {
        v6 = *(_DWORD ***)(v7 + 4);
        if ( !v6 )
          goto LABEL_7;
      }
      if ( v5 )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504884, v7);
      v5 = 1;
      (*(void (**)(void))(*v9 + 4))();
    }
LABEL_7:
    Rules_FindPatternParser(v10, &v9);
  }
  if ( v5 )
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_504880, v4);
  else
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone, v4);
}
// 48F06D: variable 'v7' is possibly undefined
// 48F0A6: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F0E0) --------------------------------------------------------
signed int  Rules_ArrayContainsValue(int a1, _DWORD *a2)
{
  __int16 i; // ax

  for ( i = 0; i < *a2 << 17 >> 23; ++i )
  {
    if ( a1 == *(_DWORD *)a2[i + 2] )
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
  int v4; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&v4, aDependencies_0, v2, a1);
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
  int v4; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&v4, aDependents_0, v2, a1);
    if ( result )
      return (_DWORD *)Rules_PrintDependentList((int)result, v3);
  }
  return result;
}
// 48F188: variable 'v2' is possibly undefined
// 48F191: variable 'v3' is possibly undefined

//----- (0048F1A0) --------------------------------------------------------
_DWORD * Rules_ResolveFactOrInstanceArg(_DWORD *a1, _BYTE *a2, int a3, double a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  _DWORD *v8; // ebx
  _BYTE *v9; // edx
  int v11; // ecx
  _BYTE v12[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+14h] [ebp-8h]

  v13 = a3;
  Rules_RtnUnknown(1, a1, a4);
  v6 = *(_DWORD *)(v5 + 4);
  if ( v6 == 6 || v6 == 7 )
    return *(_DWORD **)(v5 + 8);
  if ( v6 == 1 )
  {
    v8 = (_DWORD *)Rules_FindFactByIndex();
    if ( v8 )
      return v8;
    sprintf_(v12, "f-%ld", *(_DWORD *)(*(_DWORD *)(v11 + 8) + 16));
    v9 = v12;
    goto LABEL_8;
  }
  if ( v6 != 8 && v6 != 2 )
  {
    Rules_ReportSymbolTypeError(a2, 1);
    return 0;
  }
  v8 = Instance_FindByName(*(_DWORD *)(v5 + 8));
  if ( !v8 )
  {
    v9 = *(_BYTE **)(*(_DWORD *)(v7 + 8) + 16);
LABEL_8:
    Rules_ReportCantFindItem(v7, (int)v9);
  }
  return v8;
}
// 48F1B5: variable 'v5' is possibly undefined
// 48F1DF: variable 'v7' is possibly undefined
// 48F20D: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (0048F300) --------------------------------------------------------
int  Parser_ParseForm(__int16 *a1, _DWORD *a2, int a3, double a4)
{
  _DWORD *v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // ebx
  int v9; // edx
  void *v10; // eax
  int v11; // ecx
  int *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // edi
  int v20; // ecx
  uintptr_t function_ptr;
  uintptr_t evaluator;
  double v21; // [esp+0h] [ebp-18h]
  char v22[8]; // [esp+Ch] [ebp-Ch] BYREF
  int v23; // [esp+14h] [ebp-4h]

  v23 = a3;
  v5 = a2;
  if ( a1 )
  {
    switch ( *a1 )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 5:
      case 7:
      case 8:
        v6 = *a1;
        goto LABEL_4;
      case 4:
        a2[1] = 4;
        a2[2] = *(_DWORD *)(*(_DWORD *)(a1 + 1) + 8);
        a2[3] = *(_DWORD *)(*(_DWORD *)(a1 + 1) + 12);
        a2[4] = *(_DWORD *)(*(_DWORD *)(a1 + 1) + 16);
        Rules_PropagateReturnValueDepth((uintptr_t)a2);
        return g_ClipsEvaluationError;
      case 10:
        v8 = g_ClipsCurrentExpression;
        g_ClipsCurrentExpression = (int)a1;
        v9 = *(_DWORD *)(a1 + 1);
        function_ptr = (uintptr_t)(unsigned int)*(_DWORD *)(v9 + 9);
        switch ( *(_BYTE *)(v9 + 8) )
        {
          case 'a':
            v5[1] = 5;
            goto LABEL_9;
          case 'b':
            v5[1] = 2;
            if ( !((int (*)(void))function_ptr)() )
              goto LABEL_13;
            v10 = (void *)g_ClipsTrueSymbol;
            goto LABEL_10;
          case 'c':
            v22[0] = ((int (*)(_DWORD *))function_ptr)(v5);
            v22[1] = 0;
            v5[1] = 2;
            v10 = Str_Intern(v22, 0);
            goto LABEL_10;
          case 'd':
          case 'f':
            v5[1] = 0;
            v21 = ((double (*)(void))function_ptr)();
            v10 = (void *)Rules_AddDoubleValue(v21);
            goto LABEL_10;
          case 'i':
          case 'l':
            v5[1] = 1;
            v12 = (int *)((uintptr_t)(unsigned int)((int (*)(void))function_ptr)());
            v10 = Rules_AddIntegerValue(v12);
            goto LABEL_10;
          case 'j':
          case 'k':
          case 'm':
          case 'n':
          case 'u':
            ((void (*)(uintptr_t, uintptr_t, double))function_ptr)((uintptr_t)v5, (uintptr_t)v5, a4);
            break;
          case 'o':
            v5[1] = 8;
            goto LABEL_9;
          case 's':
            v5[1] = 3;
            goto LABEL_9;
          case 'v':
            ((void (*)(void))function_ptr)();
            v5[1] = 105;
LABEL_13:
            v10 = (void *)g_ClipsFalseSymbol;
            goto LABEL_10;
          case 'w':
            v5[1] = 2;
            goto LABEL_9;
          case 'x':
            v5[1] = 7;
LABEL_9:
            v10 = (void *)(uintptr_t)(unsigned int)((int (*)(void))function_ptr)();
LABEL_10:
            v5[2] = (int)(uintptr_t)v10;
            break;
          default:
            Rules_ReportSystemError((int)v5, 2);
            IO_RunRouterExitCallbacks(5);
            break;
        }
        g_ClipsCurrentExpression = v8;
        Rules_PropagateReturnValueDepth((uintptr_t)v5);
        return g_ClipsEvaluationError;
      case 15:
      case 16:
        if ( Rules_FindBoundVariable(a2, *(_DWORD *)(a1 + 1)) )
          goto LABEL_5;
        Rules_PrintErrorID((int)aEvaluatn, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(a1 + 1) + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUnbound, v16);
        v5[1] = 2;
        v5[2] = g_ClipsFalseSymbol;
        g_ClipsEvaluationError = 1;
        g_ClipsHaltExecution = 1;
        Rules_PropagateReturnValueDepth((uintptr_t)v5);
        result = g_ClipsEvaluationError;
        break;
      default:
        if ( !g_Clips_PrimitiveEntityTable[*a1] )
        {
          Rules_ReportSystemError((int)a2, 3);
          IO_RunRouterExitCallbacks(5);
        }
        v6 = *a1;
        v18 = g_Clips_PrimitiveEntityTable[v6];
        if ( (*(_BYTE *)(v18 + 1) & 0x20) != 0 )
        {
LABEL_4:
          v5[1] = v6;
          v5[2] = *(_DWORD *)(a1 + 1);
LABEL_5:
          Rules_PropagateReturnValueDepth((uintptr_t)v5);
          result = g_ClipsEvaluationError;
        }
        else
        {
          if ( !*(_DWORD *)(v18 + 16) )
          {
            Rules_ReportSystemError((int)v5, 4);
            IO_RunRouterExitCallbacks(5);
          }
          v19 = g_ClipsCurrentExpression;
          g_ClipsCurrentExpression = (int)a1;
          evaluator = (uintptr_t)(unsigned int)*(_DWORD *)(g_Clips_PrimitiveEntityTable[*a1] + 16);
          ((void (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)(a1 + 1), v5, a4);
          g_ClipsCurrentExpression = v19;
          Rules_PropagateReturnValueDepth((uintptr_t)v5);
          result = g_ClipsEvaluationError;
        }
        break;
    }
  }
  else
  {
    a2[1] = 2;
    a2[2] = g_ClipsFalseSymbol;
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
int  Rules_RegisterEvaluationHandler(int result, int a2)
{
  int v2; // ebx
  int v3; // ecx

  v2 = result;
  if ( g_Clips_PrimitiveEntityTable[a2] )
  {
    Rules_ReportSystemError(a2, 5);
    result = IO_RunRouterExitCallbacks();
    g_Clips_PrimitiveEntityTable[v3] = v2;
  }
  else
  {
    g_Clips_PrimitiveEntityTable[a2] = result;
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
  int v1; // edx
  _DWORD *v2; // edx
  int v3; // ecx

  v1 = result;
  if ( result )
  {
    do
    {
      Rules_ValueDeinstall(v1, *(_DWORD *)(v1 + 20));
      g_ClipsMemFreeListTemp = (int)v2;
      *v2 = *(_DWORD *)(g_ClipsMemoryTable + 96);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
      v1 = v3;
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
signed int  Rules_PrintDataObject(int a1, int a2)
{
  unsigned int v3; // eax
  signed int result; // eax
  int v5; // ecx
  int v6; // ecx

  v3 = *(_DWORD *)(a2 + 4);
  if ( v3 < 4 )
    return Rules_PrintAtomValue(a1, *(_DWORD *)(a2 + 4), *(int **)(a2 + 8));
  if ( v3 <= 4 )
    return Lexer_OutputFieldRange(a1, *(_DWORD *)(a2 + 8), *(_DWORD *)(a2 + 16), *(_DWORD *)(a2 + 12), 1);
  if ( v3 <= 8 || v3 == 105 )
    return Rules_PrintAtomValue(a1, *(_DWORD *)(a2 + 4), *(int **)(a2 + 8));
  Output_Write(a1, (int)aUnknownprintty, a2);
  Rules_PrintLongInteger(v5, *(_DWORD *)(v5 + 4));
  result = Output_Write(a1, (int)asc_5048FC, v6);
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
_DWORD * Rules_SetMultifieldErrorValue(int a1)
{
  _DWORD *result; // eax
  _DWORD *v2; // edx

  *(_DWORD *)(a1 + 4) = 4;
  result = Rules_CreateEphemeralMultifield(0);
  v2[3] = 1;
  v2[4] = 0;
  v2[2] = result;
  return result;
}
// 48F731: variable 'v2' is possibly undefined

//----- (0048F750) --------------------------------------------------------
__int16 * Rules_ValueInstall(int a1, int a2)
{
  if ( *(_DWORD *)(a1 + 4) == 4 )
    return Rules_InstallMultifield(*(__int16 **)(a1 + 8));
  else
    return (__int16 *)Rules_AtomInstall(*(_DWORD *)(a1 + 4), *(_DWORD *)(a1 + 8), a2);
}

//----- (0048F770) --------------------------------------------------------
__int16 * Rules_ValueDeinstall(int a1, int a2)
{
  if ( *(_DWORD *)(a1 + 4) == 4 )
    return Rules_DeinstallMultifield(*(__int16 **)(a1 + 8));
  else
    return (__int16 *)Rules_AtomDeinstall(*(_DWORD *)(a1 + 4), *(__int16 **)(a1 + 8), a2);
}

//----- (0048F790) --------------------------------------------------------
unsigned int  Rules_AtomInstall(unsigned int result, int a2, int a3)
{
  int v3; // esi

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
    return (unsigned int)Rules_InstallMultifield((__int16 *)a2);
  }
  result *= 4;
  v3 = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( !v3 )
    return result;
  result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( (*(_BYTE *)(v3 + 1) & 0x40) != 0 )
  {
LABEL_15:
    ++*(_DWORD *)(a2 + 4);
    return result;
  }
  if ( *(_DWORD *)(v3 + 28) )
    return (*(int (__cdecl **)(int))(v3 + 28))(a3);
  return result;
}
// 48F795: simplified comparisons for 'eax.4': >=3u && >=4u became >=4u
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F800) --------------------------------------------------------
unsigned int  Rules_AtomDeinstall(unsigned int result, __int16 *a2, int a3)
{
  int v3; // ecx

  if ( result < 3 )
  {
    if ( !result )
      return Rules_DecrementFloatCount((int)a2, a3);
    if ( result <= 1 )
      return Rules_DecrementIntegerCount((int)a2, a3);
    return Rules_DecrementSymbolCount((int)a2, a3);
  }
  if ( result <= 3 )
    return Rules_DecrementSymbolCount((int)a2, a3);
  if ( result < 8 )
  {
    if ( result == 4 )
      return (unsigned int)Rules_DeinstallMultifield(a2);
    goto LABEL_4;
  }
  if ( result <= 8 )
    return Rules_DecrementSymbolCount((int)a2, a3);
  if ( result >= 0xD )
  {
    if ( result > 0xD )
    {
      if ( result == 105 )
        return result;
      goto LABEL_4;
    }
    return Rules_DecrementSymbolCount((int)a2, a3);
  }
LABEL_4:
  result *= 4;
  v3 = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( v3 )
  {
    result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
    if ( (*(_BYTE *)(v3 + 1) & 0x40) != 0 )
    {
      return Rules_DecrementBitmapCount((int)a2, v3);
    }
    else if ( *(_DWORD *)(v3 + 24) )
    {
      return (*(int (__cdecl **)(int))(v3 + 24))(a3);
    }
  }
  return result;
}
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F8A0) --------------------------------------------------------
int  Rules_PropagateReturnValueDepth(uintptr_t a1)
{
  int result; // eax
  int v3; // ebx
  int end; // edi
  __int16 *v4; // ecx

  if ( *(_DWORD *)(a1 + 4) != 4 )
    return Rules_ClampEvaluationDepth(*(_DWORD *)(a1 + 4), (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 8));
  result = *(_DWORD *)(a1 + 8);
  if ( *(__int16 *)((uintptr_t)(unsigned int)result + 4) > g_ClipsCurrentEvaluationDepth )
    *(_WORD *)((uintptr_t)(unsigned int)result + 4) = g_ClipsCurrentEvaluationDepth;
  v3 = *(_DWORD *)(a1 + 12);
  end = *(int *)(a1 + 16);
  if ( v3 <= end )
  {
    v4 = (__int16 *)((uintptr_t)(unsigned int)result + 6 * v3 + 14);
    do
    {
      result = Rules_ClampEvaluationDepth(*v4, (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(v4 + 1));
      ++v3;
      v4 += 3;
    }
    while ( v3 <= end );
  }
  return result;
}
// 48F8E8: variable 'v5' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;

//----- (0048F940) --------------------------------------------------------
int  Rules_ClampEvaluationDepth(int result, _DWORD *a2)
{
  __int16 v2; // bx

  switch ( result )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
      if ( g_ClipsCurrentEvaluationDepth < a2[2] )
        a2[2] = g_ClipsCurrentEvaluationDepth;
      break;
    case 6:
      v2 = g_ClipsCurrentEvaluationDepth;
      result = a2[7] & 0x7FFF;
      if ( result > g_ClipsCurrentEvaluationDepth )
      {
        *((_WORD *)a2 + 14) &= 0x8000u;
        result = v2 & 0x7FFF;
        a2[7] |= result;
      }
      break;
    case 7:
      if ( g_ClipsCurrentEvaluationDepth < a2[8] )
        a2[8] = g_ClipsCurrentEvaluationDepth;
      break;
    default:
      return result;
  }
  return result;
}
// 51A96C: using guessed type int dword_51A96C;

//----- (0048FB10) --------------------------------------------------------
signed int  AST_BuildExpressionFromValue(_DWORD *a1)
{
  int v2; // ecx
  signed int v3; // ebx
  int v4; // ecx
  int v5; // esi
  signed int v7; // eax
  int v8; // ecx
  int **Symbol; // eax
  signed int v10; // [esp+0h] [ebp-18h]

  v2 = a1[1];
  v3 = 0;
  v10 = 0;
  if ( v2 != 4 )
    return AST_NewNode(v2, a1[2]);
  v4 = a1[3] + 1;
  v5 = 6 * v4 - 6;
  while ( v4 <= a1[4] + 1 )
  {
    v7 = AST_NewNode(*(_WORD *)(v5 + a1[2] + 14), *(_DWORD *)(v5 + a1[2] + 16));
    if ( v3 )
      *(_DWORD *)(v3 + 10) = v7;
    else
      v10 = v7;
    v3 = v7;
    v5 += 6;
    v4 = v8 + 1;
  }
  if ( v10 )
    return v10;
  Symbol = Rules_MakeSymbol(aCreate_1);
  return AST_NewNode(10, (int)Symbol);
}
// 48FB80: variable 'v8' is possibly undefined

//----- (0048FBD0) --------------------------------------------------------
int  Rules_ComputeFieldHashValue(int a1, int a2, int a3)
{
  int result; // eax

  result = a2;
  switch ( a1 )
  {
    case 0:
      result = *(_DWORD *)(a2 + 16);
      goto LABEL_3;
    case 1:
      result = *(_DWORD *)(a2 + 16);
      goto LABEL_3;
    case 2:
    case 3:
    case 8:
      result = *(_DWORD *)(a2 + 12) << 16 >> 18;
      goto LABEL_3;
    case 5:
    case 6:
    case 7:
LABEL_3:
      if ( a3 >= 0 )
        result *= a3 + 29;
      break;
    default:
      result = a1;
      if ( a3 >= 0 )
        result = (a3 + 29) * a1;
      break;
  }
  return result;
}

//----- (0048FC30) --------------------------------------------------------
int  Rules_RetractFactFromNetwork(_DWORD *a1, double a2)
{
  unsigned int link_record; // edi
  unsigned int pattern; // esi
  unsigned int node; // esi/ecx
  unsigned int partial_match; // ebx
  unsigned int next_link; // eax
  int removed_nodes; // [esp+0h] [ebp-20h] BYREF
  int retained_tail; // [esp+4h] [ebp-1Ch] BYREF

  for ( link_record = (unsigned int)(uintptr_t)a1; link_record; link_record = *(_DWORD *)(uintptr_t)link_record )
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

  link_record = (unsigned int)(uintptr_t)a1;
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
int  Rules_PropagateRetractToJoinNode(int result, int a2, int a3, int a4, double a5, int a6)
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
             a2,
             (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8),
             a3,
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
          Rules_UpdateBetaMemoryOnRetract((_DWORD *)child, (int)removed, a6, a5);
          removed = (uintptr_t)(unsigned int)*(_DWORD *)(removed + 4);
        }
        return Rules_FreePartialMatchList(removed_nodes, 1);
      }
      last = Rules_FreePartialMatchList(removed_nodes, 1);
      while ( *(_DWORD *)(child + 28) )
      {
        last = Rules_PropagateRetractToJoinNode((int)child, a2, a3, a4, a5, a6);
        child = (uintptr_t)(unsigned int)*(_DWORD *)(child + 28);
      }
      node = child;
    }
  }
  return last;
}

//----- (0048FE40) --------------------------------------------------------
_DWORD * Rules_UpdateBetaMemoryOnRetract(_DWORD *result, int a2, int a3, double a4)
{
  int v4; // edi
  int v6; // esi
  int v7; // edx
  _DWORD *v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD *v11; // ecx

  v4 = (int)result;
  v6 = result[2];
  if ( v6 )
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)v6 & 0x20) == 0 )
        goto LABEL_3;
      result = (_DWORD *)(v6 + 4 * (*(_DWORD *)v6 << 17 >> 23));
      v7 = result[1];
      if ( a2 != v7 )
        goto LABEL_3;
      result[1] = 0;
      result = (_DWORD *)Rules_EvaluateJoinTest((_WORD *)v6, *(_DWORD *)(v7 + 4), v4, a4);
      if ( result )
        goto LABEL_3;
      *(_BYTE *)v6 &= ~0x20u;
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
      *(_DWORD *)(v6 + 4 * (*(_DWORD *)v6 << 17 >> 23) + 4) = result;
      if ( *(_DWORD *)(v4 + 36) )
        result = Rules_AddActivation(*(_DWORD *)(v4 + 36), v6, a4);
      v9 = *(_DWORD *)(v4 + 20);
      if ( !v9 )
        goto LABEL_3;
      if ( v4 == *(_DWORD *)(v9 + 16) )
      {
        result = (_DWORD *)Rules_DriveJoinNetwork(v6, *(_DWORD *)(v4 + 20), 1, a4);
        v6 = *(_DWORD *)(v6 + 4);
        if ( !v6 )
          return result;
      }
      else if ( a3 )
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
        *result = v6;
        result[1] = *(_DWORD *)(v4 + 20);
        result[2] = g_ClipsDeferredJoinDriveListHead;
        g_ClipsDeferredJoinDriveListHead = (int)result;
        v6 = *(_DWORD *)(v6 + 4);
        if ( !v6 )
          return result;
      }
      else
      {
        while ( v9 )
        {
          result = (_DWORD *)Rules_DriveJoinNetwork(v6, v9, 0, a4);
          v9 = *(_DWORD *)(v10 + 28);
        }
LABEL_3:
        v6 = *(_DWORD *)(v6 + 4);
        if ( !v6 )
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
signed int  Rules_EvaluateJoinTest(_WORD *a1, int a2, int a3, double a4)
{
  _WORD *v6; // edx
  int v7; // ecx
  int i; // eax
  signed int v10; // [esp+0h] [ebp-14h]

  if ( (*(_BYTE *)a3 & 4) != 0 )
    a2 = *(_DWORD *)(*(_DWORD *)(a3 + 16) + 8);
  while ( a2 )
  {
    v10 = 0;
    if ( (*(_BYTE *)a2 & 0x20) == 0 )
    {
      if ( *(_DWORD *)(a3 + 12) )
      {
        v10 = Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(a3 + 12), a1, (_BYTE *)(uintptr_t)(unsigned int)a3, a2, a4);
        if ( g_ClipsEvaluationError )
        {
          g_ClipsEvaluationError = 0;
LABEL_15:
          *(_DWORD *)&a1[2 * (*(_DWORD *)a1 << 17 >> 23) + 2] = a2;
          return 1;
        }
      }
      else
      {
        v10 = 1;
        if ( (*(_BYTE *)a3 & 4) != 0 )
        {
          v6 = a1;
          v7 = a2;
          for ( i = 0; i < (*(_DWORD *)a1 << 17 >> 23) - 1; ++i )
          {
            if ( *(_DWORD *)(v7 + 8) != *((_DWORD *)v6 + 2) )
              goto LABEL_6;
            v6 += 2;
            v7 += 4;
          }
        }
      }
    }
    if ( v10 )
      goto LABEL_15;
LABEL_6:
    a2 = *(_DWORD *)(a2 + 4);
  }
  return 0;
}
// 51A964: using guessed type int dword_51A964;

//----- (00490060) --------------------------------------------------------
int  Rules_FilterPartialMatchList(int a1, _DWORD *a2, int a3, int *a4, int *a5)
{
  uintptr_t current; // esi
  uintptr_t removed_tail; // ebp
  uintptr_t previous; // ecx
  uintptr_t head; // [esp+Ch] [ebp-10h]
  int slot_offset; // [esp+0h] [ebp-1Ch]

  current = (uintptr_t)(unsigned int)(uintptr_t)a2;
  head = current;
  previous = current;
  removed_tail = 0;
  slot_offset = 4 * a3;
  *a4 = 0;
  while ( current )
  {
    unsigned int field_count = ((unsigned int)*(_DWORD *)current << 17) >> 23;
    int keep = ((*(_BYTE *)current & 0x20) != 0 && (int)field_count - 1 == a3);
    if ( !keep )
      keep = a1 != *(_DWORD *)(current + slot_offset + 8);
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
        if ( *a4 )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *a4 = (int)current;
        removed_tail = current;
        head = next;
        *(_DWORD *)(current + 4) = 0;
        current = next;
        previous = head;
      }
      else
      {
        *(_DWORD *)(previous + 4) = (int)next;
        if ( *a4 )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *a4 = (int)current;
        *(_DWORD *)(current + 4) = 0;
        removed_tail = current;
        current = next;
      }
    }
  }
  *a5 = (int)previous;
  return (int)head;
}

//----- (00490160) --------------------------------------------------------
signed int  Rules_FreePartialMatchList(signed int result, int a2)
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
    if ( !a2 || ((*(_BYTE *)node & 0x10) != 0 && (*(_BYTE *)node & 0x20) == 0) )
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
signed int  Rules_FreePartialMatch(int a1)
{
  uintptr_t node; // ecx
  uintptr_t value_record; // eax
  unsigned int free_bucket; // eax
  signed int result; // eax

  node = (uintptr_t)(unsigned int)a1;
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
  int v3; // ecx
  int result; // eax

  if ( g_ClipsDeferredJoinDriveListHead )
  {
    do
    {
      for ( i = *(char **)(g_ClipsDeferredJoinDriveListHead + 4); i; i = *(char **)(v2 + 28) )
        Rules_DriveJoinNetwork(*(int **)g_ClipsDeferredJoinDriveListHead, i, 0, a1);
      v3 = *(_DWORD *)(g_ClipsDeferredJoinDriveListHead + 8);
      g_ClipsMemFreeListTemp = g_ClipsDeferredJoinDriveListHead;
      *(_DWORD *)g_ClipsDeferredJoinDriveListHead = *(_DWORD *)(g_ClipsMemoryTable + 48);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      g_ClipsDeferredJoinDriveListHead = v3;
    }
    while ( v3 );
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
BOOL  Lexer_AppendCharToPendingToken(int a1)
{
  int v1; // esi

  v1 = g_Lexer_PendingLineCharIndex;
  g_Lexer_PendingTokenBuffer = (int)Str_AppendCharEscaping(
                        a1,
                        (char *)g_Lexer_PendingTokenBuffer,
                        (unsigned int *)&g_Lexer_TokenBufferCapacity,
                        &g_Lexer_PendingLineCharIndex,
                        g_Lexer_TokenBufferCapacity + 80);
  return v1 != g_Lexer_PendingLineCharIndex;
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
  int v1; // ecx
  int v2; // esi
  int v3; // edi
  int v4; // ebp
  int v5; // eax
  unsigned __int8 v6; // dl
  char v7; // dl
  _DWORD v8[7]; // [esp+0h] [ebp-1Ch] BYREF

  v1 = result;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  if ( !result )
    return result;
  v5 = 0;
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
            v6 = *(_BYTE *)(v1 + v5++);
            if ( !v6 )
              return 0;
            if ( v6 >= 0x20u )
              break;
            if ( v6 >= 0xAu )
            {
              if ( v6 <= 0xAu )
                goto LABEL_29;
              if ( v6 < 0xCu )
                goto LABEL_22;
              if ( v6 > 0xCu )
              {
                if ( v6 != 13 )
                  goto LABEL_22;
LABEL_29:
                if ( v4 )
                  return -1;
                if ( v3 && !v2 )
                  return 1;
              }
LABEL_7:
              v5 = Str_SkipInlineWhitespaceAt(v1, v5);
            }
            else
            {
              if ( v6 == 9 )
                goto LABEL_7;
LABEL_22:
              if ( !v2 && (IsTable[(unsigned __int8)(v6 + 1)] & 8) != 0 )
              {
                while ( 1 )
                {
                  v7 = *(_BYTE *)(v1 + v5++);
                  if ( !v7 )
                    break;
                  if ( v7 == 10 || v7 == 13 )
                  {
                    if ( !v4 )
                      return 1;
                    return -1;
                  }
                }
                return 0;
              }
            }
          }
          if ( v6 <= 0x20u )
            goto LABEL_7;
          if ( v6 >= 0x28u )
            break;
          if ( v6 != 34 )
            goto LABEL_22;
          v5 = Lexer_SkipQuotedStringSpan(v1, v5, v8);
          if ( !v2 && v8[0] )
            v3 = 1;
        }
        if ( v6 > 0x28u )
          break;
        if ( v2 > 0 || !v3 )
        {
          v3 = 1;
          ++v2;
        }
      }
      if ( v6 > 0x29u )
        break;
      if ( v2 <= 0 )
      {
        if ( !v3 )
          v4 = 1;
      }
      else
      {
        --v2;
      }
    }
    if ( v6 != 59 )
      goto LABEL_22;
    v5 = Lexer_SkipLineComment(v1, v5);
    if ( v3 )
    {
      if ( !v2 && *(_BYTE *)(v1 + v5) )
        break;
    }
    if ( *(_BYTE *)(v1 + v5) )
      ++v5;
  }
  if ( !v4 )
    return 1;
  return -1;
}
// 490549: variable 'v1' is possibly undefined

//----- (004906D0) --------------------------------------------------------
int  Lexer_SkipQuotedStringSpan(int a1, int a2, _DWORD *a3)
{
  int v4; // eax
  int result; // eax

  v4 = *(unsigned __int8 *)(a2 + a1);
  if ( v4 == 34 )
  {
LABEL_6:
    result = a2 + 1;
    *a3 = 1;
  }
  else
  {
    while ( 1 )
    {
      if ( v4 == 92 )
      {
        ++a2;
        v4 = *(unsigned __int8 *)(a1 + a2);
      }
      if ( !v4 )
        break;
      ++a2;
      v4 = *(unsigned __int8 *)(a1 + a2);
      if ( v4 == 34 )
        goto LABEL_6;
    }
    *a3 = 0;
    return a2;
  }
  return result;
}

//----- (00490720) --------------------------------------------------------
int  Lexer_SkipLineComment(int a1, int a2)
{
  int v2; // ecx
  unsigned __int8 *v3; // edx
  int i; // eax

  v2 = a2;
  v3 = (unsigned __int8 *)(a1 + a2);
  for ( i = *v3; i != 10; ++v2 )
  {
    if ( i == 13 )
      break;
    if ( !i )
      break;
    i = *++v3;
  }
  return v2;
}

//----- (00490750) --------------------------------------------------------
int  Str_SkipInlineWhitespaceAt(int a1, int a2)
{
  int v2; // ecx
  _BYTE *v3; // edx
  int i; // eax

  v2 = a2;
  v3 = (_BYTE *)(a1 + a2);
  for ( i = 0; ; i = 0 )
  {
    LOBYTE(i) = *v3;
    if ( i != 32 && i != 12 && i != 9 )
      break;
    ++v3;
    ++v2;
  }
  return v2;
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
int  Rules_RouteCommand(int result, int a2, int a3, double a4)
{
  int v5; // ecx
  _BYTE *v6; // ecx
  signed int v7; // ebx
  int v8; // ecx
  int v9; // edx
  char *v10; // eax
  int v11; // ecx
  __int16 *v12; // eax
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
  _DWORD v23[6]; // [esp-4h] [ebp-34h] BYREF
  unsigned int v24; // [esp+14h] [ebp-1Ch] BYREF
  int *v25; // [esp+18h] [ebp-18h]
  int v26; // [esp+28h] [ebp-8h]

  v26 = a3;
  if ( !result )
    return result;
  IO_OpenStringSource((int)aCommand_2, (const char *)result, 0);
  Parser_NextToken((int)aCommand_2, (int)&v24);
  if ( v24 == 2 || v24 == 3 || v24 < 2 || v24 == 8 )
  {
    IO_CloseStringRouter((int)aCommand_2);
    if ( a2 )
    {
      Rules_PrintAtomValue((int)aStdout, v24, v25);
      Output_Write((int)aStdout, (int)asc_504990, v5);
    }
    return 1;
  }
  if ( v24 != 13 )
  {
    if ( v24 != 100 )
    {
      Rules_PrintErrorID((int)aCommline, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedACon_0, v15);
      IO_CloseStringRouter((int)aCommand_2);
      return 0;
    }
    Parser_NextToken((int)aCommand_2, (int)&v24);
    if ( v24 == 2 )
    {
      v7 = Rules_ParseConstruct();
      if ( v7 != -1 )
      {
        IO_CloseStringRouter((int)aCommand_2);
        if ( v9 == 1 )
        {
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aError_1, v8);
          v10 = (char *)Rules_GetPPBuffer();
          Output_WriteLongString((signed int)g_IO_LogicalNameTable_WError[0], v10);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504990, v11);
        }
        Rules_DestroyPPBuffer();
        return v7;
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
        if ( v23[1] != 105 && a2 )
        {
          Rules_PrintDataObject((int)aStdout, (int)v23);
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
  v12 = (__int16 *)AST_NewNode(v24, (int)v25);
  Parser_ParseForm(v12, v23, (int)v12, a4);
  g_ClipsMemFreeListTemp = (int)v13;
  *v13 = *(_DWORD *)(g_ClipsMemoryTable + 56);
  *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
  if ( a2 )
  {
    Rules_PrintDataObject((int)aStdout, (int)v23);
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
  int v1; // eax
  unsigned __int8 v2; // dl

  v1 = Lexer_PeekChar((int)aStdin_1, (unsigned int)this);
  v2 = v1;
  if ( v1 == -1 )
    v2 = 10;
  return Lexer_AppendCharToPendingToken(v2);
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
  _DWORD *v0; // edx
  signed int result; // eax

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 64);
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *v0;
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
int  Rules_FreeDefruleModule(int a1)
{
  int result; // eax

  result = Rules_ClearModuleConstructList(a1, g_DefruleConstructTypePtr, a1);
  g_ClipsMemFreeListTemp = a1;
  *(_DWORD *)a1 = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E648: using guessed type int dword_54E648;

//----- (00490D30) --------------------------------------------------------
int  Rules_GetDefruleModuleItem(int a1)
{
  return Rules_GetModuleConstructData(a1, g_DefruleConstructClass);
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490D40) --------------------------------------------------------
int  Rules_FindDefruleByName(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (00490D50) --------------------------------------------------------
int  Rules_GetNextDefrule(int a1)
{
  return Class_Enum(a1, g_DefruleConstructClass);
}
// 54E64C: using guessed type int dword_54E64C;

//----- (00490D60) --------------------------------------------------------
BOOL Rules_IsDefruleDeletable()
{
  int v0; // edx
  int v1; // eax

  if ( Rules_IsBloaded() )
    return 0;
  v1 = v0;
  if ( v0 )
  {
    while ( *(char *)(v1 + 29) >= 0 )
    {
      v1 = *(_DWORD *)(v1 + 48);
      if ( !v1 )
        return !g_Rules_JoinOperationInProgress;
    }
    return 0;
  }
  return !g_Rules_JoinOperationInProgress;
}
// 490D6C: variable 'v0' is possibly undefined
// 51A954: using guessed type int dword_51A954;

//----- (00490DA0) --------------------------------------------------------
signed int  Rules_DeriveDefaultFromConstraints(char *a1, _DWORD *a2, int a3)
{
  _DWORD *v4; // ecx
  signed int result; // eax
  int v6; // edx
  signed int *v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int v11; // esi
  int *v12; // eax
  void **v13; // edi
  int v14; // ebx
  signed int v15; // edx
  int v16; // edx
  int v17; // ecx
  char v18; // dl
  signed int *v19; // eax
  int *v20; // eax
  signed int *v21; // eax
  int v22; // edx

  v4 = a2;
  if ( !a1 )
  {
    if ( a3 )
    {
      a2[1] = 4;
      a2[4] = -1;
      a2[3] = 0;
      result = (signed int)Rules_CreateEphemeralMultifield(0);
    }
    else
    {
      a2[1] = 2;
      result = (signed int)Str_Intern(aNil, (int)a2);
    }
    *(_DWORD *)(v6 + 8) = result;
    return result;
  }
  if ( (*a1 & 1) != 0 || (v18 = *a1, (*a1 & 2) != 0) )
  {
    v7 = Str_Intern(aNil, (int)v4);
    v8 = (int)a1;
    v9 = (int)v7;
    v10 = 2;
    v11 = 2;
LABEL_9:
    v12 = Rules_DeriveNumericDefaultFromRange(v10, v8, v9, v11);
LABEL_10:
    v13 = (void **)v12;
    goto LABEL_11;
  }
  if ( (v18 & 4) != 0 )
  {
    v19 = Str_Intern(g_Rules_DefaultEmptyStringConstraint, (int)v4);
    v8 = (int)a1;
    v9 = (int)v19;
    v10 = 3;
    v11 = 3;
    goto LABEL_9;
  }
  if ( (v18 & 0x10) != 0 )
  {
    v20 = Rules_AddIntegerValue(0);
    v8 = (int)a1;
    v9 = (int)v20;
    v10 = 1;
    v11 = 1;
    goto LABEL_9;
  }
  if ( (v18 & 8) != 0 )
  {
    v9 = Rules_AddDoubleValue(0.0);
    v10 = 0;
    v11 = 0;
    goto LABEL_9;
  }
  if ( (v18 & 0x20) != 0 )
  {
    v21 = Str_Intern(aNil, (int)v4);
    v8 = (int)a1;
    v9 = (int)v21;
    v10 = 8;
    v11 = 8;
    goto LABEL_9;
  }
  if ( (v18 & 0x40) != 0 )
  {
    LOWORD(v11) = 7;
    v13 = &g_Instance_DummyInstanceRecord;
    goto LABEL_11;
  }
  if ( (a1[1] & 1) != 0 )
  {
    LOWORD(v11) = 6;
    v13 = &g_Rules_DummyFactPtr;
    goto LABEL_11;
  }
  if ( *a1 >= 0 )
  {
    LOWORD(v11) = 2;
    v12 = Str_Intern(aNil, (int)v4);
    goto LABEL_10;
  }
  LOWORD(v11) = 5;
  v13 = 0;
LABEL_11:
  if ( a3 )
  {
    v14 = *(_DWORD *)(a1 + 18);
    if ( v14 )
    {
      v22 = *(_DWORD *)(v14 + 2);
      if ( v22 == g_Clips_NegativeInfinitySymbol )
        v15 = g_Clips_NegativeInfinitySymbol ^ v22;
      else
        v15 = *(_DWORD *)(v22 + 16);
    }
    else
    {
      v15 = 0;
    }
    v4[1] = 4;
    v4[4] = v15 - 1;
    v4[3] = 0;
    result = (signed int)Rules_CreateEphemeralMultifield(v15);
    *(_DWORD *)(v17 + 8) = result;
    if ( v16 > 0 )
    {
      result = 6 * v16 - 6;
      do
      {
        *(_WORD *)(*(_DWORD *)(v17 + 8) + result + 14) = v11;
        result -= 6;
        --v16;
        *(_DWORD *)(*(_DWORD *)(v17 + 8) + result + 22) = v13;
      }
      while ( result > -6 );
    }
  }
  else
  {
    result = (__int16)v11;
    v4[2] = v13;
    v4[1] = (__int16)v11;
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
int * Rules_DeriveNumericDefaultFromRange(int a1, int a2, int a3, int a4)
{
  __int16 *v5; // eax
  double v7; // st7
  int v8; // [esp+8h] [ebp-Ch]

  v5 = *(__int16 **)(a2 + 6);
  if ( v5 )
  {
    while ( *v5 != a1 )
    {
      v5 = *(__int16 **)(v5 + 5);
      if ( !v5 )
        goto LABEL_4;
    }
    return *(int **)(v5 + 1);
  }
LABEL_4:
  if ( a1 == 1 )
  {
    v5 = *(__int16 **)(a2 + 10);
    if ( *v5 != 1 )
    {
      if ( !*v5 )
      {
LABEL_11:
        v7 = *(double *)(*(_DWORD *)(v5 + 1) + 16);
        _CHP(v8, a4);
        return Rules_AddIntegerValue((int)v7);
      }
      v5 = *(__int16 **)(a2 + 14);
      if ( *v5 != 1 )
      {
        if ( *v5 )
          return (int *)a3;
        goto LABEL_11;
      }
    }
    return *(int **)(v5 + 1);
  }
  if ( a1 )
    return (int *)a3;
  v5 = *(__int16 **)(a2 + 10);
  if ( !*v5 )
    return *(int **)(v5 + 1);
  if ( *v5 != 1 )
  {
    v5 = *(__int16 **)(a2 + 14);
    if ( !*v5 )
      return *(int **)(v5 + 1);
    if ( *v5 != 1 )
      return (int *)a3;
  }
  return (int *)Rules_AddDoubleValue((double)*(int *)(*(_DWORD *)(v5 + 1) + 16));
}
// 490F90: could not find valid save-restore pair for esi
// 490FE8: variable 'v8' is possibly undefined

//----- (00491040) --------------------------------------------------------
int  Rules_ParseDefaultAttribute(
        int a1,
        int a2,
        int a3,
        int a4,
        double a5,
        _DWORD *a6,
        _DWORD *a7,
        _DWORD *a8)
{
  int v9; // esi
  int v10; // edx
  int v11; // ecx
  _WORD *v12; // ebx
  _WORD *v13; // eax
  int v14; // ecx
  int v15; // ecx
  _WORD *v16; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int v23; // ebx
  int v24; // ecx
  char *v25; // eax
  _DWORD *v26; // edx
  int v27; // edi
  _DWORD *v28; // edx
  __int16 *v29; // ecx
  int v30; // ecx
  signed int v31; // eax
  int v32; // ecx
  _DWORD v33[6]; // [esp+0h] [ebp-40h] BYREF
  _DWORD v34[3]; // [esp+18h] [ebp-28h] BYREF
  int v35; // [esp+24h] [ebp-1Ch]
  int v36; // [esp+28h] [ebp-18h]
  int v37; // [esp+2Ch] [ebp-14h]
  _WORD *v38; // [esp+30h] [ebp-10h]

  v37 = a2;
  v36 = a4;
  v35 = a3;
  v9 = 0;
  *a6 = 0;
  *a7 = 0;
  IO_OutWriteToken(asc_504A54);
  Parser_NextToken(a1, v10);
  v12 = 0;
  if ( v34[0] == 101 )
  {
LABEL_28:
    IO_OutNewline();
    IO_OutNewline();
    v23 = v37;
    IO_OutWriteToken(asc_504A98);
    if ( v23 )
      goto LABEL_37;
    if ( !v9 || *(_DWORD *)(v9 + 10) )
    {
      *a8 = 1;
    }
    else
    {
      v25 = Rules_BuildLHSNodeFromToken((__int16 *)v9);
      v25[1] &= ~0x80u;
      if ( Rules_ConstraintIsUnmatchable(v25) )
        *a8 = 1;
      AST_DecrementNodeRefCount(v26);
      if ( !*a8 )
      {
LABEL_37:
        if ( v36 || !v35 || !v9 )
          return v9;
        v27 = v9;
        v9 = 0;
        do
        {
          Lexer_ErrorRecover(0);
          if ( Parser_ParseForm(v29, v28, (int)v29, a5) )
            *a8 = 1;
          if ( v33[1] == 4 && !v37 && !*a8 )
          {
            Rules_PrintErrorID((int)aDefault_0, 1, 1);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheDefaultValu, v30);
            *a8 = 1;
LABEL_47:
            v16 = (_WORD *)v27;
            goto LABEL_9;
          }
          if ( *a8 )
            goto LABEL_47;
          v31 = AST_BuildExpressionFromValue(v33);
          v9 = AST_AppendNodeList(v9, v31);
        }
        while ( *(_DWORD *)(v32 + 10) );
        AST_Free(v27);
        return v9;
      }
    }
    Rules_PrintErrorID((int)aDefault_0, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheDefaultValu, v24);
    AST_Free(v9);
    return 0;
  }
  while ( 1 )
  {
    v13 = (_WORD *)Parser_ParseSingleExpression(a1, (__int16 *)v34, v11);
    v38 = v13;
    if ( !v13 )
      goto LABEL_10;
    if ( *v13 == 15 || *v13 == 16 )
      break;
    if ( AST_TreeContainsSpecialTag((int)v13, 0) == 1 )
    {
      AST_Free(v9);
      AST_Free(v21);
      *a8 = 1;
      Parser_ReportSyntaxError();
      return 0;
    }
    if ( v12 )
      *(_DWORD *)(v12 + 5) = v20;
    else
      v9 = v20;
    IO_OutWriteToken(asc_504A54);
    Parser_NextToken(a1, v22);
    v11 = v34[0];
    v12 = v38;
    if ( v34[0] == 101 )
      goto LABEL_28;
  }
  if ( !strcmp_(v13, aNone_0) )
  {
    v15 = 0;
  }
  else if ( !strcmp_(v14, aDerive) )
  {
    v15 = 1;
  }
  else
  {
    v15 = -1;
  }
  if ( v36 || *v38 == 16 || v15 == -1 || v9 )
  {
    Parser_ReportSyntaxError();
    v16 = v38;
LABEL_9:
    AST_Free((int)v16);
LABEL_10:
    AST_Free(v9);
    *a8 = 1;
    return 0;
  }
  AST_Free((int)v38);
  Parser_NextToken(a1, v18);
  if ( v34[0] != 101 )
  {
    Parser_ReportSyntaxError();
    IO_OutNewline();
    IO_OutWriteToken(asc_504A54);
    IO_OutWriteToken((char *)v34[2]);
    *a8 = 1;
  }
  if ( v19 )
    *a7 = 1;
  else
    *a6 = 1;
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
int  Module_RegisterItem(int a1, int a2, int a3, int a4, int a5, int a6)
{
  _DWORD *v7; // edi
  _DWORD *v8; // eax
  int v9; // edx

  v7 = *(_DWORD **)(g_ClipsMemoryTable + 128);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = *v7;
    v8 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  *v8 = a1;
  v8[2] = a2;
  v8[3] = a4;
  v8[4] = a3;
  v8[5] = a5;
  v8[6] = a6;
  v9 = g_ClipsModuleItemCount++;
  v8[7] = 0;
  v8[1] = v9;
  if ( g_Module_ItemListTail )
    *(_DWORD *)(g_Module_ItemListTail + 28) = v8;
  else
    g_ModuleItemDescriptorListHead = (int)v8;
  g_Module_ItemListTail = (int)v8;
  return v8[1];
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
int  Module_FindItemByName(int a1)
{
  int current; // ecx

  current = g_ModuleItemDescriptorListHead;
  while ( current )
  {
    if ( !strcmp_(*(_DWORD *)current, a1) )
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
int  Module_SetCurrent(int a1)
{
  int v1; // ecx
  int v2; // edx
  int v3; // edx

  v1 = g_Clips_CurrentModule;
  g_Clips_CurrentModule = a1;
  if ( g_Module_ChangeNotifyEnabled )
  {
    v2 = g_CLIPS_AfterModuleChangeListHead;
    ++g_Module_ChangeGeneration;
    if ( g_CLIPS_AfterModuleChangeListHead )
    {
      do
      {
        (*(void (__fastcall **)(int))(v2 + 4))(v1);
        v2 = *(_DWORD *)(v3 + 12);
      }
      while ( v2 );
    }
  }
  return v1;
}
// 49155F: variable 'v1' is possibly undefined
// 491562: variable 'v3' is possibly undefined
// 51A9A0: using guessed type int dword_51A9A0;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 51A9C0: using guessed type int dword_51A9C0;

