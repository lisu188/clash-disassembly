/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../strategic/strategic_api.h"
#include "../clips/clips_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0047C7A0) --------------------------------------------------------
_DWORD * Rules_RegisterConstructType(
        int constructName,
        int pluralName,
        int parseFunction,
        int findFunction,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12)
{
  _DWORD *block; // edi
  _DWORD *result; // eax

  block = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208);
  if ( block )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208) = *block;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x34);
  }
  *result = constructName;
  result[1] = pluralName;
  result[2] = findFunction;
  result[3] = parseFunction;
  result[4] = a5;
  result[5] = a6;
  result[6] = a7;
  result[7] = a8;
  result[8] = a9;
  result[9] = a10;
  result[10] = a11;
  result[11] = a12;
  result[12] = g_Rules_ConstructTypeListHead;
  g_Rules_ConstructTypeListHead = (int)(intptr_t)result;
  return result;
}
// 47C7CE: variable 'a3' is possibly undefined
// 51A194: using guessed type int dword_51A194;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047C830) --------------------------------------------------------
signed int  Rules_AddSaveFunction(int name, int priority, int callback)
{
  g_Rules_SaveFunctionListHead = (int)(intptr_t)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_SaveFunctionListHead, priority);
  return 1;
}
// 51A188: using guessed type int dword_51A188;

//----- (0047C850) --------------------------------------------------------
signed int  Rules_Bload(int fileName, DWORD a2)
{
  signed int result; // eax
  int i; // edx
  int callback; // eax
  int construct; // ecx
  int next_construct; // ecx
  int construct_table; // ecx
  int skip_size; // [esp+2Ch] [ebp-20h] BYREF
  int function_table_count; // [esp+28h] [ebp-24h] BYREF
  int missing_functions; // [esp+30h] [ebp-1Ch] BYREF
  char construct_name[20]; // [esp+0h] [ebp-4Ch] BYREF
  char header[20]; // [esp+14h] [ebp-38h] BYREF

  result = Rules_BloadOpenFile((const CHAR *)(uintptr_t)(unsigned int)fileName, a2);
  if ( !result )
    return result;
  Rules_BloadReadBlock((uintptr_t)header, strlen((const char *)g_Rules_BloadFileHeaderID) + 1);
  if ( strcmp(header, (const char *)g_Rules_BloadFileHeaderID) )
  {
    Rules_PrintErrorID((int)(intptr_t)aBload_0, 2, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFile, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], fileName, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsNotABinaryCo, 0);
    Rules_BloadCloseFile(0);
    return 0;
  }
  Rules_BloadReadBlock((uintptr_t)header, strlen(g_Rules_BsaveVersionID) + 1);
  if ( strcmp(header, g_Rules_BsaveVersionID) )
  {
    Rules_PrintErrorID((int)(intptr_t)aBload_0, 3, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFile, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], fileName, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsAnIncompatib, 0);
LABEL_20:
    Rules_BloadCloseFile(0);
    return 0;
  }
  if ( g_Rules_FactsBloadedFlag && !Rules_ClearBload() )
    goto LABEL_20;
  if ( !Rules_ClearReady() )
  {
    Rules_BloadCloseFile(0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheClipsEnviro, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aBinaryLoadCann, 0);
    return 0;
  }
  for ( i = g_Rules_BeforeBloadFunctionListHead; i; i = *(_DWORD *)(uintptr_t)(i + 12) )
  {
    callback = *(_DWORD *)(uintptr_t)(i + 4);
    if ( callback )
      ((void (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  g_Rules_BloadFunctionPtrTable = Rules_ReadNeededFunctions(&function_table_count, &missing_functions);
  if ( missing_functions )
  {
    Rules_BloadCloseFile(0);
    Rules_CallAbortBloadFunctions();
    return 0;
  }
  Rules_BloadAtomTables();
  Rules_BloadAllocExpressionArray();
  Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
  while ( strncmp(construct_name, (const char *)g_Rules_BloadFileHeaderID, 0x14u) )
  {
    construct = g_BinaryItemListHead;
    if ( construct )
    {
      while ( strncmp((const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)construct, construct_name, 0x14u) )
      {
        construct = *(_DWORD *)(uintptr_t)(construct + 36);
        if ( !construct )
          goto LABEL_29;
      }
      callback = *(_DWORD *)(uintptr_t)(construct + 8);
      if ( callback )
      {
        ((void (*)(void))(uintptr_t)(unsigned int)callback)();
        goto LABEL_27;
      }
    }
LABEL_29:
    Rules_BloadReadBlock((uintptr_t)&skip_size, 4u);
    Rules_BloadSeekFile(skip_size, 0);
    if ( skip_size )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aSkipping, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], fileName, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aConstructsBeca, 0);
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
    else
    {
LABEL_27:
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
  }
  Rules_BloadRefreshExpressions();
  Rules_BloadConstraints();
  Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
  while ( strncmp(construct_name, (const char *)g_Rules_BloadFileHeaderID, 0x14u) )
  {
    construct_table = g_BinaryItemListHead;
    if ( !construct_table )
      goto LABEL_32;
    while ( strncmp((const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)construct_table, construct_name, 0x14u) )
    {
      construct_table = *(_DWORD *)(uintptr_t)(construct_table + 36);
      if ( !construct_table )
        goto LABEL_32;
    }
    next_construct = *(_DWORD *)(uintptr_t)(construct_table + 12);
    if ( next_construct )
    {
      ((void (*)(void))(uintptr_t)(unsigned int)next_construct)();
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
    else
    {
LABEL_32:
      Rules_BloadReadBlock((uintptr_t)&skip_size, 4u);
      Rules_BloadSeekFile(skip_size, 0);
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
  }
  Rules_BloadCloseFile(0);
  if ( g_Rules_BloadFunctionPtrTable )
    Mem_ReleasePoolBlock(g_Rules_BloadFunctionPtrTable, 4 * function_table_count);
  Rules_FreeBloadAtomTables();
  for ( i = g_Rules_AfterBloadCallbackListHead; i; i = *(_DWORD *)(uintptr_t)(i + 12) )
  {
    callback = *(_DWORD *)(uintptr_t)(i + 4);
    if ( callback )
      ((void (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  g_Rules_FactsBloadedFlag = 1;
  Rules_AddClearFunction((int)(intptr_t)aBload, (int)(intptr_t)Rules_ClearBload, 10000);
  return 1;
}
// 47CAF7: conditional instruction was optimized away because edi.4==0
// 47C89B: variable 'v4' is possibly undefined
// 47C8CE: variable 'v5' is possibly undefined
// 47C90B: variable 'v9' is possibly undefined
// 47C965: variable 'v10' is possibly undefined
// 47C99B: variable 'v11' is possibly undefined
// 47C9C9: variable 'v14' is possibly undefined
// 47C9FB: variable 'v15' is possibly undefined
// 47CA07: variable 'v16' is possibly undefined
// 47CA16: variable 'v17' is possibly undefined
// 47CA1B: variable 'v18' is possibly undefined
// 47CA47: variable 'v19' is possibly undefined
// 47CA53: variable 'v20' is possibly undefined
// 47CA62: variable 'v21' is possibly undefined
// 47CA67: variable 'v6' is possibly undefined
// 47CA78: variable 'v7' is possibly undefined
// 47CA87: variable 'v22' is possibly undefined
// 47CA96: variable 'v23' is possibly undefined
// 47CAD8: variable 'v25' is possibly undefined
// 47CB20: variable 'v26' is possibly undefined
// 47CB2C: variable 'v27' is possibly undefined
// 47CB3B: variable 'v28' is possibly undefined
// 47CB86: variable 'v12' is possibly undefined
// 47CBB9: variable 'v30' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);
// 51A1AC: using guessed type int dword_51A1AC;
// 51A1B0: using guessed type int dword_51A1B0;
// 51A1B4: using guessed type int dword_51A1B4;
// 51A1C0: using guessed type void *off_51A1C0;
// 51A1C4: using guessed type char *off_51A1C4;
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51AA3C: using guessed type int dword_51AA3C;
// 54DD24: using guessed type int dword_54DD24;

//----- (0047CBF0) --------------------------------------------------------
signed int  Rules_BloadAndRefresh(
        signed int result,
        int itemSize,
        void (__fastcall *updateFunction)(signed int, signed int))
{
  int previous_allocator_handler;
  signed int chunk_count;
  int chunk_bytes;
  signed int chunk_base;
  signed int initialized_count;
  int entries_this_pass;
  int entry_index;
  int entry_ptr;

  if ( !result )
    return result;

  previous_allocator_handler = Mem_SetOutOfMemoryHandler((int)(intptr_t)CSyncObject_Unlock);
  chunk_count = result;
  do
  {
    chunk_bytes = itemSize * chunk_count;
    chunk_base = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)chunk_bytes);
    if ( !chunk_base )
    {
      if ( chunk_count / 2 )
      {
        chunk_count /= 2;
      }
      else if ( ((int (__cdecl *)(int))(intptr_t)previous_allocator_handler)(chunk_bytes) == 1 )
      {
        return Mem_SetOutOfMemoryHandler(previous_allocator_handler);
      }
    }
  }
  while ( !chunk_base );

  Mem_SetOutOfMemoryHandler(previous_allocator_handler);
  initialized_count = 0;
  while ( initialized_count < result )
  {
    entries_this_pass = result - initialized_count;
    if ( entries_this_pass > chunk_count )
      entries_this_pass = chunk_count;
    Rules_BloadReadBlock(chunk_base, entries_this_pass * itemSize);
    if ( entries_this_pass > 0 )
    {
      entry_ptr = chunk_base;
      for ( entry_index = 0; entry_index < entries_this_pass; ++entry_index )
      {
        updateFunction(entry_ptr, initialized_count);
        ++initialized_count;
        entry_ptr += itemSize;
      }
    }
  }
  return Mem_ReleasePoolBlock(chunk_base, chunk_bytes);
}

//----- (0047CCF0) --------------------------------------------------------
int  Rules_ReadNeededFunctions(int *functionCountPtr, int *errorFlagPtr)
{
  int unresolved; // ebx
  int string_bytes; // [esp+0h] [ebp-28h] BYREF
  char *function_name; // esi
  int function_count; // edi
  int table_bytes; // [esp+Ch] [ebp-1Ch]
  int table; // [esp+10h] [ebp-18h]
  int resolved_function; // ebp
  int i; // [esp+1Ch] [ebp-Ch]
  char *names; // [esp+4h] [ebp-24h]

  Rules_BloadReadBlock((uintptr_t)functionCountPtr, 4u);
  Rules_BloadReadBlock((uintptr_t)&string_bytes, 4u);
  unresolved = 0;
  function_count = *functionCountPtr;
  if ( !function_count )
  {
    *errorFlagPtr = 0;
    return 0;
  }
  names = (char *)(uintptr_t)(unsigned int)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)string_bytes);
  Rules_BloadReadBlock((uintptr_t)names, (unsigned int)string_bytes);
  table_bytes = 4 * function_count;
  table = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)table_bytes);
  resolved_function = 0;
  function_name = names;
  for ( i = 0; i < function_count; ++i )
  {
    resolved_function = Rules_FindFunctionByName((int)(uintptr_t)function_name, resolved_function);
    if ( !resolved_function )
    {
      if ( !unresolved )
      {
        Rules_PrintErrorID((int)(intptr_t)aBload_0, 6, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheFollowingUn, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aReferencedByTh, 0);
      }
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_502A88, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(uintptr_t)function_name, 0);
      unresolved = 1;
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_502A8C, 0);
    }
    *(_DWORD *)(uintptr_t)(table + 4 * i) = resolved_function;
    function_name += strlen(function_name) + 1;
  }
  Mem_ReleasePoolBlock((int)(uintptr_t)names, string_bytes);
  if ( unresolved )
  {
    Mem_ReleasePoolBlock(table, table_bytes);
    table = 0;
  }
  *errorFlagPtr = unresolved;
  return table;
}
// 47CDD0: variable 'v13' is possibly undefined
// 47CDE4: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047CE60) --------------------------------------------------------
int __fastcall Rules_FindFunctionByName(int functionName, int lastFound)
{
  int head; // edi
  int current; // ecx
  int next; // ecx
  const char *registered_name; // edx

  head = Rules_GetFunctionDefinitionListHead();
  if ( !head )
    return 0;
  current = lastFound ? *(_DWORD *)(uintptr_t)(lastFound + 27) : head;
  while ( current )
  {
    registered_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)current + 16);
    if ( !strcmp((const char *)(uintptr_t)(unsigned int)functionName, registered_name) )
      return current;
    next = *(_DWORD *)(uintptr_t)(current + 27);
    if ( next == lastFound )
      return 0;
    current = next ? next : head;
  }
  return 0;
}

//----- (0047CEB0) --------------------------------------------------------
int Rules_IsBloaded(void)
{
  return g_Rules_FactsBloadedFlag;
}
// 51A1AC: using guessed type int dword_51A1AC;

//----- (0047CEC0) --------------------------------------------------------
signed int Rules_ClearBload(void)
{
  int failed; // edx
  int callback_node; // ecx
  int construct_node; // edx
  int callback; // eax

  failed = 0;
  for ( callback_node = g_Rules_BloadClearReadyCallbackListHead; callback_node; callback_node = *(_DWORD *)(uintptr_t)(callback_node + 12) )
  {
    callback = *(_DWORD *)(uintptr_t)(callback_node + 4);
    if ( callback && !((int (*)(void))(uintptr_t)(unsigned int)callback)() )
    {
      if ( !failed )
      {
        Rules_PrintErrorID((int)(intptr_t)aBload_0, 5, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSomeConstruc_0, 0);
      }
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_502A88, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(callback_node + 0), 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_502A8C, 0);
      failed = 1;
    }
  }
  if ( failed == 1 )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aBinaryClearCan, 0);
    return 0;
  }
  else
  {
    for ( construct_node = g_BinaryItemListHead; construct_node; construct_node = *(_DWORD *)(uintptr_t)(construct_node + 36) )
    {
      callback = *(_DWORD *)(uintptr_t)(construct_node + 16);
      if ( callback )
        ((void (*)(void))(uintptr_t)(unsigned int)callback)();
    }
    Rules_FreeBloadedExpressions();
    Rules_ClearBloadedConstraints();
    g_Rules_FactsBloadedFlag = 0;
    Rules_RemoveClearFunction((int)(intptr_t)aBload);
    return 1;
  }
}
// 51A1AC: using guessed type int dword_51A1AC;
// 51A1B8: using guessed type int dword_51A1B8;
// 51A614: using guessed type char *off_51A614[5];
// 51AA3C: using guessed type int dword_51AA3C;

//----- (0047CF90) --------------------------------------------------------
int Rules_CallAbortBloadFunctions(void)
{
  int callback_node; // edx
  int callback; // eax
  int result; // eax

  result = 0;
  for ( callback_node = g_Rules_AbortBloadCallbackListHead; callback_node; callback_node = *(_DWORD *)(uintptr_t)(callback_node + 12) )
  {
    callback = *(_DWORD *)(uintptr_t)(callback_node + 4);
    if ( callback )
      result = ((int (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  return result;
}
// 51A1BC: using guessed type int dword_51A1BC;

//----- (0047CFC0) --------------------------------------------------------
_DWORD * Rules_AddBeforeBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_BeforeBloadFunctionListHead, priority);
  g_Rules_BeforeBloadFunctionListHead = (int)(intptr_t)result;
  return result;
}
// 51A1B0: using guessed type int dword_51A1B0;

//----- (0047CFE0) --------------------------------------------------------
_DWORD * Rules_AddAfterBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_AfterBloadCallbackListHead, priority);
  g_Rules_AfterBloadCallbackListHead = (int)(intptr_t)result;
  return result;
}
// 51A1B4: using guessed type int dword_51A1B4;

//----- (0047D020) --------------------------------------------------------
_DWORD * Rules_AddAbortBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_AbortBloadCallbackListHead, priority);
  g_Rules_AbortBloadCallbackListHead = (int)(intptr_t)result;
  return result;
}
// 51A1BC: using guessed type int dword_51A1BC;

//----- (0047D050) --------------------------------------------------------
signed int Rules_ReportCannotLoadWithBload(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aBload_0, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotLoad, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aConstructWithB, v2);
}
// 47D070: variable 'v0' is possibly undefined
// 47D07C: variable 'v1' is possibly undefined
// 47D08B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047D0A0) --------------------------------------------------------
int  Rules_BloadCommand(DWORD a1, double a2)
{
  int v2; // ecx
  int result; // eax

  if ( Lexer_TokenExpect((int)(intptr_t)aBload, 0, 1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  if ( result )
    return Rules_Bload(result, a1);
  return result;
}
// 47D0C7: variable 'v2' is possibly undefined

//----- (0047D0E0) --------------------------------------------------------
void __fastcall Rules_InitializeEngine(int a1, int a2)
{
  (void)a1;
  (void)a2;
  if ( !g_Rules_EngineInitializedFlag )
  {
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    Rules_RegisterExitFunction();
    CRT_RegisterSignalHandler(1, (intptr_t)Rules_ShutdownEngine);
    Rules_RegisterBuiltinFunctionGroups();
    Rules_RegisterAllHostFunctions();
    Rules_RegisterConstraintCheckingCommands();
    Rules_InitExpressionHashTable();
    Rules_RegisterClearResetCommands();
    Rules_InitializeDefrules();
    Rules_InitDeffactsConstruct();
    Defgeneric_SetupConstruct();
    Deffunction_InitConstructType();
    Defglobal_InitConstructType();
    Rules_RegisterDeftemplateConstruct();
    Rules_InitObjectSystem(0);
    Module_InitializeDefmodules();
    ProcParam_RegisterPrimitiveTypes();
    Rules_Clear();
    g_Rules_EngineInitializedFlag = 1;
  }
}
// 47D4E0: using guessed type int sub_47D4E0();
// 49A0E0: using guessed type int __cdecl sub_49A0E0(void);
// 496643: using guessed type int __fastcall sub_496643(_DWORD, _DWORD);
// 51A1D4: using guessed type int dword_51A1D4;

//----- (0047D320) --------------------------------------------------------
signed int Rules_RegisterBuiltinFunctionGroups(void)
{
  Rules_RegisterControlFlowFunctions();
  Rules_RegisterMiscFunctions();
  Rules_RegisterIOHostFunctions();
  Rules_RegisterPredicateHostFunctions();
  Rules_RegisterArithmeticFunctions();
  Rules_RegisterFileIOCommands();
  Rules_RegisterWatchFunctions();
  Rules_RegisterMultifieldFunctions();
  Rules_RegisterStringBuiltins();
  Rules_RegisterMathBuiltins();
  Rules_RegisterHelpFunctions();
  return Rules_RegisterConstructsToCFunction();
}

//----- (0047D360) --------------------------------------------------------
double Rules_TimeCommand(void)
{
  struct
  {
    int time_value;
    unsigned __int16 milliseconds;
    __int16 timezone_minutes;
    __int16 dst_flag;
  } v4;

  ftime_(&v4);
  return (double)(v4.time_value % 10000) + (double)v4.milliseconds / g_Rules_MillisecondsPerSecond;
}
// 502B70: using guessed type double dbl_502B70;

//----- (0047D3D0) --------------------------------------------------------
int  Rules_SystemCommand(double frame)
{
  char *commandBuffer; // edi
  int result; // eax
  int argCount; // ebp
  int argIndex; // esi
  int v5; // edx
  _DWORD v6[6]; // [esp+0h] [ebp-38h] BYREF
  /* stack alias of v6[1] */
  /* stack alias of v6[2]: the DATA_OBJECT value slot */
  int v9; // [esp+18h] [ebp-20h] BYREF
  unsigned int v10[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  commandBuffer = 0;
  v9 = 0;
  v10[0] = 0;
  result = Lexer_TokenExpect((int)(intptr_t)aSystem_0, 1, 1);
  argCount = result;
  if ( result != -1 )
  {
    argIndex = 1;
    if ( result < 1 )
    {
LABEL_6:
      if ( commandBuffer )
      {
        if ( g_Rules_SystemCommandPreShellHook )
          g_Rules_SystemCommandPreShellHook();
        system_(commandBuffer);
        if ( g_Rules_SystemCommandPostShellHookA )
          g_Rules_SystemCommandPostShellHookA();
        if ( g_Rules_SystemCommandPostShellHookB )
          g_Rules_SystemCommandPostShellHookB();
        return Mem_SmallBlockFree(((_DWORD*)(commandBuffer)), v10[0]);
      }
    }
    else
    {
      while ( 1 )
      {
        Rules_RtnUnknown(argIndex, v6, frame);
        if ( v6[1] != 3 && v6[1] != 2 )
          break;
        ++argIndex;
        result = (int)(intptr_t)Str_Append((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6[2] + 16), commandBuffer, v10, ((_DWORD*)(&v9)));
        commandBuffer = (char *)(uintptr_t)result;
        if ( argIndex > argCount )
          goto LABEL_6;
      }
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return (int)(intptr_t)Rules_ReportSymbolTypeError(((_BYTE*)(aSystem_0)), v5);
    }
  }
  return result;
}
// 47D4AD: variable 'v5' is possibly undefined
// 51A1C8: using guessed type int (*dword_51A1C8)(void);
// 51A1CC: using guessed type int (*dword_51A1CC)(void);
// 51A1D0: using guessed type int (*dword_51A1D0)(void);

//----- (0047D4E0) --------------------------------------------------------
int Rules_ShutdownEngine(void)
{
  void *v0; // ecx
  int v1; // edx
  int v2; // ecx

  Rules_SetEvaluationErrorFlag(1);
  Rules_CloseAllBatchSources(v0);
  return CRT_RegisterSignalHandler(v2, v1);
}
// 47D4F0: variable 'v0' is possibly undefined
// 47D4FA: variable 'v2' is possibly undefined
// 47D4FA: variable 'v1' is possibly undefined
// 47D4E0: using guessed type int sub_47D4E0();
// 496643: using guessed type int __fastcall sub_496643(_DWORD, _DWORD);

//----- (0047D540) --------------------------------------------------------
BOOL __fastcall Rules_BloadDeleteFile(int path, int a2)
{
  return IO_RemoveFileByPath(path, a2) == 0;
}
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (0047D550) --------------------------------------------------------
BOOL  Rules_RenameFile(const CHAR *oldFileName, const CHAR *newFileName, int a3)
{
  return IO_RenameFile(oldFileName, newFileName, a3) == 0;
}

//----- (0047D560) --------------------------------------------------------
signed int  Rules_BloadOpenFile(const CHAR *fileName, DWORD a2)
{
  int v2; // ecx

  g_ClipsBloadFileHandle = IO_FOpen(fileName, (unsigned __int8 *)aRb_1, (int)(intptr_t)fileName, a2);
  if ( g_ClipsBloadFileHandle )
    return 1;
  Rules_OpenFileErrorMessage(v2, v2);
  return 0;
}
// 47D587: variable 'v2' is possibly undefined
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D5A0) --------------------------------------------------------
int  Rules_BloadReadBlock(uintptr_t buffer, unsigned int size)
{
  if ( !size )
    return 0;
  return fread_((void *)buffer, size, g_ClipsBloadFileHandle, 1);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D600) --------------------------------------------------------
signed int  Rules_BloadSeekFile(int offset, int a2)
{
  return IO_SeekStreamGuarded(g_ClipsBloadFileHandle, offset, 1u, a2);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D630) --------------------------------------------------------
int __thiscall Rules_BloadCloseFile(void *this_)
{
  (void)this_;
  return fclose_(g_ClipsBloadFileHandle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D660) --------------------------------------------------------
_DWORD * Rules_InsertActivationSorted(int *agenda, _DWORD *activation)
{
  uintptr_t list_ref; // ebx
  uintptr_t node; // ecx
  uintptr_t current; // esi
  uintptr_t predecessor; // edx
  uintptr_t next; // eax

  Rules_SetAgendaChanged(1);
  list_ref = (uintptr_t)agenda;
  node = (uintptr_t)activation;
  current = (uintptr_t)(unsigned int)*(_DWORD *)list_ref;
  predecessor = 0;
  if ( current )
  {
    switch ( g_Rules_ConflictResolutionStrategy )
    {
      case CLIPS_STRATEGY_DEPTH:
        predecessor = (uintptr_t)Rules_PlaceInDepthList((_DWORD *)current, (int)node);
        break;
      case CLIPS_STRATEGY_BREADTH:
        predecessor = (uintptr_t)Rules_PlaceInBreadthList((_DWORD *)current, (int)node);
        break;
      case CLIPS_STRATEGY_LEX:
        predecessor = (uintptr_t)Rules_PlaceInLexList((_DWORD *)current, (int)node);
        break;
      case CLIPS_STRATEGY_MEA:
        predecessor = (uintptr_t)Rules_PlaceInMeaList((_DWORD *)current, (int)node);
        break;
      case CLIPS_STRATEGY_COMPLEXITY:
        predecessor = (uintptr_t)Rules_PlaceInComplexityList((_DWORD *)current, (_DWORD *)node);
        break;
      case CLIPS_STRATEGY_SIMPLICITY:
        predecessor = (uintptr_t)Rules_PlaceInSimplicityList((_DWORD *)current, (_DWORD *)node);
        break;
      case CLIPS_STRATEGY_RANDOM:
        predecessor = (uintptr_t)Rules_PlaceInRandomList((_DWORD *)current, (_DWORD *)node);
        break;
      default:
        break;
    }
  }
  if ( predecessor )
  {
    next = (uintptr_t)(unsigned int)*(_DWORD *)(predecessor + 28);
    *(_DWORD *)(node + 28) = (int)next;
    *(_DWORD *)(node + 24) = (int)predecessor;
    *(_DWORD *)(predecessor + 28) = (int)node;
    if ( next )
      *(_DWORD *)(next + 24) = (int)node;
  }
  else
  {
    next = (uintptr_t)(unsigned int)*(_DWORD *)list_ref;
    *(_DWORD *)(node + 28) = (int)next;
    *(_DWORD *)list_ref = (int)node;
    if ( next )
      *(_DWORD *)(next + 24) = (int)node;
  }
  return (_DWORD *)next;
}
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047D720) --------------------------------------------------------
_DWORD * Rules_PlaceInDepthList(_DWORD *listHead, int newActivation)
{
  int salience; // ecx
  unsigned int timeTag; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // esi

  salience = *(_DWORD *)(uintptr_t)(newActivation + 8);
  timeTag = *(_DWORD *)(uintptr_t)(newActivation + 12);
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      if ( timeTag >= listHead[3] )
        break;
    }
    insertAfter = listHead;
    listHead = (_DWORD *)(uintptr_t)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D760) --------------------------------------------------------
_DWORD * Rules_PlaceInBreadthList(_DWORD *listHead, int newActivation)
{
  int salience; // ecx
  unsigned int timeTag; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // esi

  salience = *(_DWORD *)(uintptr_t)(newActivation + 8);
  timeTag = *(_DWORD *)(uintptr_t)(newActivation + 12);
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      if ( timeTag <= listHead[3] )
        break;
    }
    insertAfter = listHead;
    listHead = (_DWORD *)(uintptr_t)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D7A0) --------------------------------------------------------
_DWORD * Rules_PlaceInLexList(_DWORD *listHead, int newActivation)
{
  _DWORD *current; // ecx
  unsigned int timeTag; // ebp
  int salience; // edi
  _DWORD *insertAfter; // ebx
  int nodeSalience; // eax
  signed int comparison; // eax

  current = listHead;
  if ( !*(_DWORD *)(uintptr_t)(newActivation + 16) )
    *(_DWORD *)(uintptr_t)(newActivation + 16) = ((_DWORD)(uintptr_t)(Rules_BuildLexBasisOrder((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(newActivation + 4))));
  timeTag = *(_DWORD *)(uintptr_t)(newActivation + 12);
  salience = *(_DWORD *)(uintptr_t)(newActivation + 8);
  insertAfter = 0;
  if ( !current )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = current[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      comparison = Rules_CompareActivationBasis((int)(intptr_t)current, (_DWORD **)(uintptr_t)newActivation);
      if ( comparison )
      {
        if ( comparison == 1 )
          return insertAfter;
        if ( timeTag <= current[3] )
          break;
      }
    }
    insertAfter = current;
    current = (_DWORD *)(uintptr_t)current[7];
    if ( !current )
      return insertAfter;
  }
  return insertAfter;
}
// 47D7B9: variable 'v2' is possibly undefined

//----- (0047D810) --------------------------------------------------------
_DWORD * Rules_PlaceInMeaList(_DWORD *listHead, int newActivation)
{
  _DWORD *current; // ecx
  _DWORD *insertAfter; // esi
  int nodeSalience; // eax
  int newBasisList; // edi
  int newFirstTag; // edx
  int nodeFirstTag; // eax
  int nodeFirstMatch; // ebp
  signed int comparison; // eax
  unsigned int timeTag; // [esp+0h] [ebp-1Ch]
  int salience; // [esp+4h] [ebp-18h]

  current = listHead;
  if ( !*(_DWORD *)(uintptr_t)(newActivation + 16) )
    *(_DWORD *)(uintptr_t)(newActivation + 16) = ((_DWORD)(uintptr_t)(Rules_BuildLexBasisOrder((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(newActivation + 4))));
  timeTag = *(_DWORD *)(uintptr_t)(newActivation + 12);
  insertAfter = 0;
  salience = *(_DWORD *)(uintptr_t)(newActivation + 8);
  if ( !current )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = current[2];
    if ( nodeSalience > salience )
      goto LABEL_5;
    if ( nodeSalience < salience )
      return insertAfter;
    newBasisList = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(newActivation + 4) + 8);
    newFirstTag = -1;
    nodeFirstTag = -1;
    if ( *(_DWORD *)(uintptr_t)newBasisList )
      newFirstTag = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)newBasisList + 12);
    nodeFirstMatch = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(current[1] + 8);
    if ( nodeFirstMatch )
      nodeFirstTag = *(_DWORD *)(uintptr_t)(nodeFirstMatch + 12);
    if ( nodeFirstTag < newFirstTag )
    {
      if ( newFirstTag > 0 )
        return insertAfter;
      goto LABEL_5;
    }
    if ( nodeFirstTag > newFirstTag )
    {
      if ( nodeFirstTag <= 0 )
        return insertAfter;
      goto LABEL_5;
    }
    comparison = Rules_CompareActivationBasis((int)(intptr_t)current, (_DWORD **)(uintptr_t)newActivation);
    if ( comparison )
    {
      if ( comparison == 1 )
        return insertAfter;
      if ( timeTag <= current[3] )
        return insertAfter;
    }
LABEL_5:
    insertAfter = current;
    current = (_DWORD *)(uintptr_t)current[7];
    if ( !current )
      return insertAfter;
  }
}
// 47D833: variable 'v2' is possibly undefined

//----- (0047D8D0) --------------------------------------------------------
_DWORD * Rules_PlaceInComplexityList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // edi
  int salience; // ebx
  int complexity; // esi
  _DWORD *insertAfter; // edx
  int nodeSalience; // ecx
  int nodeComplexity; // ecx

  timeTag = newActivation[3];
  salience = newActivation[2];
  complexity = *(_DWORD *)(uintptr_t)(*newActivation + 28) & 0x7FF;
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeComplexity = *(_DWORD *)(uintptr_t)(*listHead + 28) & 0x7FF;
      if ( complexity >= nodeComplexity )
      {
        if ( complexity > nodeComplexity )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)(uintptr_t)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D930) --------------------------------------------------------
_DWORD * Rules_PlaceInSimplicityList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // edi
  int salience; // ebx
  int complexity; // esi
  _DWORD *insertAfter; // edx
  int nodeSalience; // ecx
  int nodeComplexity; // ecx

  timeTag = newActivation[3];
  salience = newActivation[2];
  complexity = *(_DWORD *)(uintptr_t)(*newActivation + 28) & 0x7FF;
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeComplexity = *(_DWORD *)(uintptr_t)(*listHead + 28) & 0x7FF;
      if ( complexity <= nodeComplexity )
      {
        if ( complexity < nodeComplexity )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)(uintptr_t)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D990) --------------------------------------------------------
_DWORD * Rules_PlaceInRandomList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // esi
  int salience; // ecx
  int randomValue; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // edi
  int nodeRandom; // edi

  timeTag = newActivation[3];
  salience = newActivation[2];
  randomValue = newActivation[5];
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeRandom = listHead[5];
      if ( randomValue <= nodeRandom )
      {
        if ( randomValue < nodeRandom )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)(uintptr_t)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D9E0) --------------------------------------------------------
_DWORD * Rules_BuildLexBasisOrder(int *pattern)
{
  _DWORD *v1; // ecx
  int count; // ebp
  int index; // ebx
  _DWORD *entry; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD *orderArray; // [esp+0h] [ebp-20h]
  int swapped; // [esp+4h] [ebp-1Ch]

  orderArray = Rules_MultifieldCopyWithMarkers(pattern, 0, 0);
  count = (*v1 << 17 >> 23) - 1;
  do
  {
    index = 0;
    swapped = 0;
    if ( count > 0 )
    {
      entry = orderArray;
      do
      {
        v5 = entry[2];
        if ( *(_DWORD *)(uintptr_t)v5 )
        {
          v6 = entry[3];
          if ( *(_DWORD *)(uintptr_t)v6 )
          {
            if ( *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v5 + 12) < *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v6 + 12) )
            {
              entry[3] = v5;
              entry[2] = v6;
              swapped = 1;
            }
          }
        }
        ++index;
        ++entry;
      }
      while ( index < count );
    }
    --count;
  }
  while ( swapped == 1 );
  return orderArray;
}
// 47D9F4: variable 'v1' is possibly undefined

//----- (0047DA60) --------------------------------------------------------
signed int  Rules_CompareActivationBasis(int activation, _DWORD **candidate)
{
  int index; // eax
  int actBasisEntry; // ecx
  _DWORD *candBasisEntry; // edx
  int *actMatchSlot; // esi
  int *candMatchSlot; // ebx
  int candMatch; // edi
  int actMatch; // esi
  int candMatch2; // ebx
  unsigned int actSalience; // edx
  unsigned int candSalience; // eax
  _DWORD *lexBasisOrder; // eax
  int v16; // edx
  int count1; // [esp+0h] [ebp-24h]
  int count2; // [esp+4h] [ebp-20h]
  int minCount; // [esp+8h] [ebp-1Ch]

  if ( !*(_DWORD *)(uintptr_t)(activation + 16) )
  {
    lexBasisOrder = Rules_BuildLexBasisOrder((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(activation + 4));
    *(_DWORD *)(uintptr_t)(v16 + 16) = ((_DWORD)(uintptr_t)(lexBasisOrder));
  }
  count2 = *candidate[4] << 17 >> 23;
  count1 = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(activation + 16) << 17 >> 23;
  if ( count1 <= count2 )
    minCount = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(activation + 16) << 17 >> 23;
  else
    minCount = *candidate[4] << 17 >> 23;
  index = 0;
  if ( minCount > 0 )
  {
    actBasisEntry = *(_DWORD *)(uintptr_t)(activation + 16);
    candBasisEntry = candidate[4];
    do
    {
      actMatchSlot = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(actBasisEntry + 8);
      if ( *actMatchSlot && (candMatchSlot = (int *)(uintptr_t)candidate[4][index + 2], (candMatch = *candMatchSlot) != 0) )
      {
        actMatch = *actMatchSlot;
        candMatch2 = *candMatchSlot;
        if ( *(_DWORD *)(uintptr_t)(candMatch + 12) < *(_DWORD *)(uintptr_t)(actMatch + 12) )
          return 0;
        if ( *(_DWORD *)(uintptr_t)(candMatch2 + 12) > *(_DWORD *)(uintptr_t)(actMatch + 12) )
          return 1;
      }
      else
      {
        if ( *(_DWORD *)(uintptr_t)candBasisEntry[2] )
          return 1;
        if ( *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(activation + 16) + 4 * index + 8) )
          return 0;
      }
      actBasisEntry += 4;
      ++index;
      ++candBasisEntry;
    }
    while ( index < minCount );
  }
  if ( count2 < count1 )
    return 0;
  if ( count2 > count1 )
    return 1;
  actSalience = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)activation + 28) & 0x7FF;
  candSalience = (*candidate)[7] & 0x7FF;
  if ( candSalience < actSalience )
  {
    return 0;
  }
  else
  {
    if ( candSalience > actSalience )
      return 1;
    return 2;
  }
}
// 47DB58: variable 'v16' is possibly undefined

//----- (0047DBB0) --------------------------------------------------------
int  Rules_SetStrategy(int strategy)
{
  int oldStrategy; // edx

  oldStrategy = g_Rules_ConflictResolutionStrategy;
  g_Rules_ConflictResolutionStrategy = strategy;
  if ( oldStrategy != strategy )
    Rules_ReorderAgenda(0);
  return oldStrategy;
}
// 47DBC0: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DBE0) --------------------------------------------------------
signed int *Rules_GetStrategyCommand(void)
{
  char *strategyName; // eax
  int v1; // ecx

  Lexer_TokenExpect(0, 0, 0);
  strategyName = Rules_GetStrategyName(g_Rules_ConflictResolutionStrategy);
  return Str_Intern(strategyName, v1);
}
// 47DBFA: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DC10) --------------------------------------------------------
signed int * Rules_SetStrategyCommand(int a1, double frame)
{
  int oldStrategy; // esi
  int newStrategy; // eax
  int argString; // ecx
  int reportedStrategy; // eax
  char *strategyName; // eax
  int v6_alias; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  char *currentStrategyName; // eax
  int v16; // ecx
  _DWORD argValue[10]; // [esp-8h] [ebp-28h] BYREF

  argValue[8] = a1;
  oldStrategy = g_Rules_ConflictResolutionStrategy;
  if ( Lexer_TokenExpect(0, 0, 1) == -1 || !Lexer_ParseValueList(1, argValue, 2, frame) )
  {
    reportedStrategy = g_Rules_ConflictResolutionStrategy;
    goto LABEL_5;
  }
  newStrategy = strcmp_(*(_DWORD *)(uintptr_t)(argValue[2] + 16), ((_DWORD)(uintptr_t)(aDepth)));
  if ( !newStrategy )
  {
LABEL_4:
    Rules_SetStrategy(newStrategy);
    reportedStrategy = oldStrategy;
LABEL_5:
    strategyName = Rules_GetStrategyName(reportedStrategy);
    return Str_Intern(strategyName, v6_alias);
  }
  if ( !strcmp_(argString, ((_DWORD)(uintptr_t)(aBreadth))) )
  {
    newStrategy = CLIPS_STRATEGY_BREADTH;
    goto LABEL_4;
  }
  if ( !strcmp_(v10, ((_DWORD)(uintptr_t)(aLex))) )
  {
    newStrategy = CLIPS_STRATEGY_LEX;
    goto LABEL_4;
  }
  if ( !strcmp_(v11, ((_DWORD)(uintptr_t)(aMea))) )
  {
    newStrategy = CLIPS_STRATEGY_MEA;
    goto LABEL_4;
  }
  if ( !strcmp_(v12, ((_DWORD)(uintptr_t)(aComplexity))) )
  {
    newStrategy = CLIPS_STRATEGY_COMPLEXITY;
    goto LABEL_4;
  }
  if ( !strcmp_(v13, ((_DWORD)(uintptr_t)(aSimplicity))) )
  {
    newStrategy = CLIPS_STRATEGY_SIMPLICITY;
    goto LABEL_4;
  }
  if ( !strcmp_(v14, ((_DWORD)(uintptr_t)(aRandom_0))) )
  {
    newStrategy = CLIPS_STRATEGY_RANDOM;
    goto LABEL_4;
  }
  Parser_ReportError(1, (int)(intptr_t)aSymbolWithVa_0);
  currentStrategyName = Rules_GetStrategyName(g_Rules_ConflictResolutionStrategy);
  return Str_Intern(currentStrategyName, v16);
}
// 47DC70: variable 'v6_alias' is possibly undefined
// 47DC8B: variable 'v5' is possibly undefined
// 47DCA2: variable 'v10' is possibly undefined
// 47DCB9: variable 'v11' is possibly undefined
// 47DCD0: variable 'v12' is possibly undefined
// 47DCE7: variable 'v13' is possibly undefined
// 47DD01: variable 'v14' is possibly undefined
// 47DD32: variable 'v16' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DD60) --------------------------------------------------------
char * Rules_GetStrategyName(int strategy)
{
  char *result; // eax

  switch ( strategy )
  {
    case CLIPS_STRATEGY_DEPTH:
      result = aDepth;
      break;
    case CLIPS_STRATEGY_BREADTH:
      result = aBreadth;
      break;
    case CLIPS_STRATEGY_LEX:
      result = aLex;
      break;
    case CLIPS_STRATEGY_MEA:
      result = aMea;
      break;
    case CLIPS_STRATEGY_COMPLEXITY:
      result = aComplexity;
      break;
    case CLIPS_STRATEGY_SIMPLICITY:
      result = aSimplicity;
      break;
    case CLIPS_STRATEGY_RANDOM:
      result = aRandom_0;
      break;
    default:
      result = aUnknown_0;
      break;
  }
  return result;
}

//----- (0047DDA0) --------------------------------------------------------
signed int Rules_RegisterAgendaCommands(void)
{
  Rules_AddClearFunction((int)(intptr_t)aAgenda_0, (int)(intptr_t)Rules_ResetActivationSequence, 0);
  Rules_AddWatchItem((int)(intptr_t)aActivations, 1, 40, (int)(intptr_t)&g_Rules_WatchActivationsFlag, (int)(intptr_t)Rules_DefruleWatchAccess, (int)(intptr_t)Rules_DefruleWatchPrint);
  Rules_RegisterHostFunction(aRefresh, 118, (int)(intptr_t)aRefreshcommand, (int)(intptr_t)Rules_RefreshCommand, (int)(intptr_t)a11w);
  Rules_RegisterHostFunction(aRefreshAgenda, 118, (int)(intptr_t)aRefreshagendac, (int)(intptr_t)Rules_RefreshAgendaCommand, (int)(intptr_t)a01w);
  Rules_RegisterHostFunction(aGetSalienceEva, 119, (int)(intptr_t)aGetsalienceeva, (int)(intptr_t)Rules_GetSalienceEvaluationCommand, (int)(intptr_t)a00);
  Rules_RegisterHostFunction(aSetSalienceEva, 119, (int)(intptr_t)aSetsalienceeva, (int)(intptr_t)Rules_SetSalienceEvaluationCommand, (int)(intptr_t)a11w);
  return Rules_RegisterHostFunction(aAgenda_0, 118, (int)(intptr_t)aAgendacommand, (int)(intptr_t)Rules_AgendaCommand, (int)(intptr_t)a01w);
}
// 51A1DC: using guessed type int dword_51A1DC;

//----- (0047DE80) --------------------------------------------------------
_DWORD * Rules_AddActivation(int rule, int binds, double a3)
{
  uintptr_t join; // ebx
  uintptr_t partial_match; // edx
  uintptr_t activation; // ecx
  uintptr_t free_head; // ecx
  uintptr_t agenda; // eax
  int salience; // eax
  int sequence; // eax
  int bucket; // eax

  join = (uintptr_t)(unsigned int)rule;
  partial_match = (uintptr_t)(unsigned int)binds;
  if ( (*(_BYTE *)(join + 29) & 0x40) != 0 )
  {
    agenda = (uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
    Rules_PushFocus(*(_DWORD *)agenda);
  }
  free_head = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 128);
  if ( free_head )
  {
    g_ClipsMemFreeListTemp = (int)free_head;
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 128) = *(_DWORD *)free_head;
    activation = (uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
  }
  else
  {
    activation = (uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  *(_DWORD *)activation = (int)join;
  *(_DWORD *)(activation + 4) = (int)partial_match;
  sequence = g_Rules_ActivationSequenceCounter++;
  *(_DWORD *)(activation + 12) = sequence;
  salience = Rules_EvaluateSalience((int)join, a3);
  *(_DWORD *)(activation + 16) = 0;
  *(_DWORD *)(activation + 8) = salience;
  *(_DWORD *)(activation + 24) = 0;
  *(_DWORD *)(activation + 28) = 0;
  *(_DWORD *)(activation + 20) = j_rand_();
  ++g_Rules_ActivationCount;
  bucket = ((unsigned int)*(_DWORD *)partial_match << 17) >> 23;
  *(_DWORD *)(partial_match + 4 * bucket + 8) = (int)activation;
  if ( (*(_BYTE *)(join + 29) & 0x10) != 0 )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aActivation_0, (int)activation);
    Rules_PrintActivation((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)activation);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502D24, (int)activation);
  }
  agenda = (uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
  return Rules_InsertActivationSorted((int *)(agenda + 12), (_DWORD *)activation);
}
// 47D520: using guessed type __int64 j_rand_(void);
// 51A1E0: using guessed type int dword_51A1E0;
// 51A1E4: using guessed type int dword_51A1E4;
// 51A618: using guessed type char *off_51A618[4];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047DF90) --------------------------------------------------------
int  Rules_ClearActivationsForRule(int result)
{
  _DWORD *activation; // ecx
  int v2; // edi
  _DWORD *nextActivation; // esi

  activation = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 8) + 12);
  v2 = result;
  if ( activation )
  {
    do
    {
      while ( 1 )
      {
        result = v2;
        nextActivation = (_DWORD *)(uintptr_t)activation[7];
        if ( v2 )
          break;
LABEL_5:
        activation = nextActivation;
        if ( !nextActivation )
          return result;
      }
      do
      {
        if ( result == *activation )
        {
          result = Rules_RemoveActivation(activation, 1, 1);
          goto LABEL_5;
        }
        result = *(_DWORD *)(uintptr_t)(result + 48);
      }
      while ( result );
      activation = (_DWORD *)(uintptr_t)activation[7];
    }
    while ( nextActivation );
  }
  return result;
}
