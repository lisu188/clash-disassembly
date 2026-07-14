/* CLIPS modules, classes, methods, and object metadata.
 * Original function-marker range: 0x00491580..0x004943A0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00491580) --------------------------------------------------------
_DWORD *Module_BeginEnum()
{
  _DWORD *freeListNode; // edx
  _DWORD *result; // eax

  freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListNode;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = g_Module_ChangeNotifyEnabled;
  g_Module_ChangeNotifyEnabled = 0;
  result[1] = g_Clips_CurrentModule;
  result[2] = g_Module_SavedEnumStackTop;
  g_Module_SavedEnumStackTop = (int)result;
  return result;
}
// 51A9A4: using guessed type int dword_51A9A4;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004915E0) --------------------------------------------------------
int Module_EndEnum()
{
  int *savedModule; // eax
  int result; // eax

  savedModule = (int *)g_Module_SavedEnumStackTop;
  g_Module_SavedEnumStackTop = *(_DWORD *)(g_Module_SavedEnumStackTop + 8);
  g_Module_ChangeNotifyEnabled = *savedModule;
  g_Clips_CurrentModule = savedModule[1];
  g_ClipsMemFreeListTemp = (int)savedModule;
  *savedModule = *(_DWORD *)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 51A9A4: using guessed type int dword_51A9A4;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491620) --------------------------------------------------------
int  Module_GetItem(int result, int moduleItemIndex)
{
  int itemsArray; // ebx

  if ( !result )
  {
    if ( !g_Clips_CurrentModule )
      return result;
    result = g_Clips_CurrentModule;
  }
  itemsArray = *(_DWORD *)(result + 8);
  if ( itemsArray )
    return *(_DWORD *)(itemsArray + 4 * moduleItemIndex);
  else
    return 0;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00491680) --------------------------------------------------------
int Module_CreateMainModule()
{
  int free_module; // edx
  int module; // ecx
  signed int *module_name; // eax
  int index; // esi
  int construct; // ecx
  int slot_offset; // edx
  int construct_data; // eax
  int (__fastcall *construct_initializer)(int, int); // eax

  free_module = *(_DWORD *)(g_ClipsMemoryTable + 128);
  if ( free_module )
  {
    g_ClipsMemFreeListTemp = free_module;
    *(_DWORD *)(g_ClipsMemoryTable + 128) = *(_DWORD *)free_module;
    module = g_ClipsMemFreeListTemp;
  }
  else
  {
    module = Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  module_name = Str_Intern(aMain_1, module);
  *(_DWORD *)module = module_name;
  ++module_name[1];
  *(_DWORD *)(module + 28) = 0;
  *(_DWORD *)(module + 4) = 0;
  *(_DWORD *)(module + 12) = 0;
  *(_DWORD *)(module + 16) = 0;
  *(_DWORD *)(module + 24) = 0;
  if ( g_ClipsModuleItemCount )
  {
    *(_DWORD *)(module + 8) = Mem_SmallBlockAlloc(4 * g_ClipsModuleItemCount);
    index = 0;
    construct = g_ModuleItemDescriptorListHead;
    if ( g_ClipsModuleItemCount > 0 )
    {
      slot_offset = 0;
      do
      {
        if ( !construct )
          break;
        if ( *(_DWORD *)(construct + 8) )
        {
          construct_initializer = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(construct + 8);
          construct_data = construct_initializer(construct, slot_offset);
          *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8)) = construct_data;
          construct_data = *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8));
          *(_DWORD *)(construct_data + 4) = 0;
          *(_DWORD *)(construct_data + 8) = 0;
          *(_DWORD *)construct_data = module;
        }
        else
        {
          *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8)) = 0;
        }
        slot_offset += 4;
        ++index;
        construct = *(_DWORD *)(construct + 28);
      }
      while ( index < g_ClipsModuleItemCount );
    }
  }
  else
  {
    *(_DWORD *)(module + 8) = 0;
  }
  Module_SetModuleCount(1);
  g_ClipsDefmoduleListTail = module;
  g_DefmoduleListHead = module;
  return Module_SetCurrent(module);
}
// 4916B3: variable 'v3' is possibly undefined
// 491728: variable 'v7' is possibly undefined
// 491759: variable 'v9' is possibly undefined
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491790) --------------------------------------------------------
void  Module_SetModuleListHead(int defmoduleList)
{
  g_DefmoduleListHead = defmoduleList;
  g_ClipsDefmoduleListTail = defmoduleList;
  if ( defmoduleList )
  {
    while ( *(_DWORD *)(g_ClipsDefmoduleListTail + 28) )
      g_ClipsDefmoduleListTail = *(_DWORD *)(g_ClipsDefmoduleListTail + 28);
  }
  return;
}
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;

//----- (004917C0) --------------------------------------------------------
int  Module_NextEnum(int defmodulePtr)
{
  if ( defmodulePtr )
    return *(_DWORD *)(defmodulePtr + 28);
  else
    return g_DefmoduleListHead;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004917D0) --------------------------------------------------------
int  Module_GetName(int theModule)
{
  return *(_DWORD *)(*(_DWORD *)theModule + 16);
}

//----- (004917E0) --------------------------------------------------------
int  Module_GetPPForm(int theModule)
{
  return *(_DWORD *)(theModule + 4);
}

//----- (004917F0) --------------------------------------------------------
int Module_RemoveAllModules()
{
  int result; // eax
  int next_module; // edx

  if ( g_DefmoduleListHead )
  {
    do
    {
      next_module = *(_DWORD *)(g_DefmoduleListHead + 28);
      result = Module_FreeModule(g_DefmoduleListHead);
      g_DefmoduleListHead = next_module;
    }
    while ( next_module );
  }
  g_Clips_CurrentModule = 0;
  g_ClipsDefmoduleListTail = 0;
  return result;
}
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B0: using guessed type int dword_51A9B0;
// 51A9B4: using guessed type int dword_51A9B4;

//----- (00491840) --------------------------------------------------------
int  Module_FreeModule(int result)
{
  int module; // esi
  int construct; // edx
  int construct_index; // ecx
  int slot_offset; // ebx
  int construct_data; // eax
  void (*construct_cleanup)(int); // eax
  int node; // edx
  int next_node; // ecx
  int module_name; // ebp

  module = result;
  if ( result )
  {
    Module_SetCurrent(result);
    if ( *(_DWORD *)(module + 8) )
    {
      construct = g_ModuleItemDescriptorListHead;
      construct_index = 0;
      if ( g_ClipsModuleItemCount > 0 )
      {
        slot_offset = 0;
        do
        {
          if ( !construct )
            break;
          if ( *(_DWORD *)(construct + 12) )
          {
            construct_data = *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8));
            construct_cleanup = (void (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(construct + 12);
            construct_cleanup(construct_data);
          }
          slot_offset += 4;
          ++construct_index;
          construct = *(_DWORD *)(construct + 28);
        }
        while ( construct_index < g_ClipsModuleItemCount );
      }
      Mem_SmallBlockFree((_DWORD *)*(_DWORD *)(module + 8), 4 * g_ClipsModuleItemCount);
    }
    Rules_DecrementSymbolCount(*(_DWORD *)module, 0);
    node = *(_DWORD *)(module + 12);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(node + 12);
        if ( *(_DWORD *)node )
          Rules_DecrementSymbolCount(*(_DWORD *)node, 0);
        if ( *(_DWORD *)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 4), 0);
        if ( *(_DWORD *)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 8), 0);
        g_ClipsMemFreeListTemp = node;
        *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        node = next_node;
      }
      while ( next_node );
    }
    node = *(_DWORD *)(module + 16);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(node + 12);
        if ( *(_DWORD *)node )
          Rules_DecrementSymbolCount(*(_DWORD *)node, 0);
        if ( *(_DWORD *)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 4), 0);
        if ( *(_DWORD *)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 8), 0);
        g_ClipsMemFreeListTemp = node;
        *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        node = next_node;
      }
      while ( next_node );
    }
    module_name = *(_DWORD *)(module + 4);
    if ( module_name )
      Mem_SmallBlockFree((_DWORD *)module_name, strlen((const char *)module_name) + 1);
    g_ClipsMemFreeListTemp = module;
    *(_DWORD *)module = *(_DWORD *)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 49188A: variable 'v4' is possibly undefined
// 49188B: variable 'v3' is possibly undefined
// 4918A9: variable 'v2' is possibly undefined
// 4918C3: variable 'v6' is possibly undefined
// 4918CC: variable 'v7' is possibly undefined
// 491918: variable 'v8' is possibly undefined
// 491921: variable 'v9' is possibly undefined
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004919B0) --------------------------------------------------------
int * Module_FindByName(_BYTE *defmoduleName)
{
  int *result; // eax
  int *nameSymbol; // edx
  int module;
  int module_symbol;
  int module_name;

  result = Rules_FindSymbolEntry(defmoduleName);
  nameSymbol = result;
  if ( result )
  {
    result = (int *)g_DefmoduleListHead;
    if ( g_DefmoduleListHead )
    {
      while ( nameSymbol != (int *)*result )
      {
        result = (int *)result[7];
        if ( !result )
          return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  if ( result )
    return result;
  module = g_DefmoduleListHead;
  while ( module )
  {
    module_symbol = *(_DWORD *)module;
    module_name = module_symbol ? *(_DWORD *)(module_symbol + 16) : 0;
    if ( module_name && !strcmp_((int)(uintptr_t)defmoduleName, module_name) )
      return (int *)(uintptr_t)(unsigned int)module;
    module = *(_DWORD *)(module + 28);
  }
  return 0;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004919E0) --------------------------------------------------------
signed int *Module_GetCurrentCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  if ( g_Clips_CurrentModule )
    return Str_Intern(*(char **)(*(_DWORD *)g_Clips_CurrentModule + 16), v0);
  else
    return (signed int *)g_ClipsFalseSymbol;
}
// 491A06: variable 'v0' is possibly undefined
// 51A9B0: using guessed type int dword_51A9B0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00491A10) --------------------------------------------------------
signed int * Module_SetCurrentCommand(int a1, double a2)
{
  signed int *defaultReturn; // esi
  int *theModule; // eax
  int v6; // edx
  int v7; // ecx
  _DWORD argPtr[10]; // [esp-8h] [ebp-28h] BYREF

  argPtr[8] = a1;
  if ( !g_Clips_CurrentModule )
    return (signed int *)g_ClipsFalseSymbol;
  defaultReturn = Str_Intern(*(char **)(*(_DWORD *)g_Clips_CurrentModule + 16), a1);
  if ( Lexer_TokenExpect(1) == -1 )
    return defaultReturn;
  if ( !Lexer_ParseValueList(1, argPtr, 2, a2) )
    return defaultReturn;
  theModule = Module_FindByName(*(_BYTE **)(argPtr[2] + 16));
  if ( theModule )
    Module_SetCurrent((int)theModule);
  else
    Rules_ReportCantFindItem(v7, v6);
  return defaultReturn;
}
// 491A94: variable 'v7' is possibly undefined
// 491A94: variable 'v6' is possibly undefined
// 51A9B0: using guessed type int dword_51A9B0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00491AE0) --------------------------------------------------------
signed int Module_ReportIllegalSpecifierError()
{
  int v0; // ecx

  Rules_PrintErrorID((int)aModuldef, 1, 1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalUseOfTh, v0);
}
// 491AFD: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00491B10) --------------------------------------------------------
signed int IO_RegisterStringRouter()
{
  return IO_AddRouter((int)aString, 0, (int)IO_StringRouterPrint, (int)IO_StringRouterQuery, (int)IO_StringRouterGetc, (int)IO_StringRouterUngetc, 0);
}

//----- (00491B40) --------------------------------------------------------
signed int  IO_StringRouterQuery(int logicalName)
{
  int router_entry; // ecx

  router_entry = g_StringRouterListHead;
  while ( router_entry )
  {
    if ( !strcmp_(*(_DWORD *)router_entry, logicalName) )
      return 1;
    router_entry = *(_DWORD *)(router_entry + 20);
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;

//----- (00491B80) --------------------------------------------------------
int  IO_StringRouterPrint(int logicalName, const char *str)
{
  int v3; // ecx
  _DWORD *stringRouter; // esi
  int currentPosition; // ecx

  stringRouter = (_DWORD *)IO_FindStringRouter(logicalName);
  if ( !stringRouter )
  {
    Rules_ReportSystemError(v3, 3);
    IO_RunRouterExitCallbacks();
  }
  if ( stringRouter[4] != 1 )
    return 1;
  currentPosition = stringRouter[2];
  if ( stringRouter[3] - 1 <= currentPosition )
    return stringRouter[4];
  strncpy_(currentPosition, str);
  stringRouter[2] += strlen(str);
  return 1;
}
// 491BB4: variable 'v3' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00491C00) --------------------------------------------------------
int  IO_StringRouterGetc(int logicalName)
{
  _DWORD *stringRouter; // ecx
  int result; // eax
  int currentPosition; // esi

  stringRouter = (_DWORD *)IO_FindStringRouter(logicalName);
  if ( !stringRouter )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( stringRouter[4] )
    return -1;
  if ( stringRouter[2] < stringRouter[3] )
  {
    currentPosition = stringRouter[2];
    result = *(unsigned __int8 *)(currentPosition + stringRouter[1]);
    stringRouter[2] = currentPosition + 1;
  }
  else
  {
    result = -1;
    ++stringRouter[2];
  }
  return result;
}
// 491C0F: variable 'v1' is possibly undefined

//----- (00491C70) --------------------------------------------------------
int __fastcall IO_StringRouterUngetc(int ch, int logicalName)
{
  int stringRouter; // ecx
  int currentPosition; // ebx

  stringRouter = IO_FindStringRouter(logicalName);
  if ( !stringRouter )
  {
    Rules_ReportSystemError(0, 2);
    IO_RunRouterExitCallbacks();
  }
  if ( *(_DWORD *)(stringRouter + 16) )
    return 0;
  currentPosition = *(_DWORD *)(stringRouter + 8);
  if ( currentPosition > 0 )
    *(_DWORD *)(stringRouter + 8) = currentPosition - 1;
  return 1;
}
// 491C7E: variable 'v2' is possibly undefined

//----- (00491CC0) --------------------------------------------------------
signed int  IO_OpenStringSource(int name, const char *str, int currentPosition)
{
  if ( str )
    return IO_OpenTextSource(name, str, strlen(str), currentPosition);
  else
    return IO_OpenTextSource(name, 0, 0, 0);
}

//----- (00491D00) --------------------------------------------------------
signed int  IO_OpenTextSource(int name, const void *str, int maximumPosition, int currentPosition)
{
  const char *routerName; // esi
  _DWORD *newStringRouter; // edx
  char *payload_copy; // eax
  size_t name_length; // eax

  routerName = (const char *)name;
  if ( IO_FindStringRouter(name) )
    return 0;
  newStringRouter = *(_DWORD **)(g_ClipsMemoryTable + 96);
  if ( newStringRouter )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = *newStringRouter;
  }
  else
  {
    newStringRouter = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(routerName) + 1;
  newStringRouter[0] = (int)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)newStringRouter[0], routerName, name_length);
  if ( str && maximumPosition > 0 )
  {
    payload_copy = (char *)Compat_AllocLow32Bytes(maximumPosition + 1);
    if ( !payload_copy )
      return 0;
    memcpy(payload_copy, str, maximumPosition);
    payload_copy[maximumPosition] = 0;
    newStringRouter[1] = (int)(uintptr_t)payload_copy;
  }
  else
  {
    newStringRouter[1] = 0;
  }
  newStringRouter[2] = currentPosition;
  newStringRouter[3] = maximumPosition;
  newStringRouter[4] = 0;
  newStringRouter[5] = g_StringRouterListHead;
  g_StringRouterListHead = (int)newStringRouter;
  return 1;
}
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491DB0) --------------------------------------------------------
signed int  IO_CloseStringRouter(int name)
{
  _DWORD *currentRouter; // ebx
  _DWORD *previousRouter; // esi
  int key_length; // edx

  currentRouter = (_DWORD *)g_StringRouterListHead;
  previousRouter = 0;
  while ( currentRouter )
  {
    if ( !strcmp_(currentRouter[0], name) )
      break;
    previousRouter = currentRouter;
    currentRouter = (_DWORD *)currentRouter[5];
  }
  if ( !currentRouter )
    return 0;
  if ( previousRouter )
  {
    previousRouter[5] = currentRouter[5];
  }
  else
  {
    g_StringRouterListHead = currentRouter[5];
  }
  if ( !currentRouter[4] && currentRouter[1] )
    Compat_FreeLow32Bytes(currentRouter[1]);
  key_length = strlen((const char *)currentRouter[0]) + 1;
  Mem_SmallBlockFree((_DWORD *)currentRouter[0], key_length);
  g_ClipsMemFreeListTemp = (int)currentRouter;
  currentRouter[0] = *(_DWORD *)(g_ClipsMemoryTable + 96);
  *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491E80) --------------------------------------------------------
signed int  IO_OpenStringDestination(int name, const void *str, int maximumPosition)
{
  const char *routerName; // esi
  _DWORD *newStringRouter; // edx
  size_t name_length; // eax

  routerName = (const char *)name;
  if ( IO_FindStringRouter(name) )
    return 0;
  newStringRouter = *(_DWORD **)(g_ClipsMemoryTable + 96);
  if ( newStringRouter )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = *newStringRouter;
  }
  else
  {
    newStringRouter = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(routerName) + 1;
  newStringRouter[0] = (int)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)newStringRouter[0], routerName, name_length);
  newStringRouter[2] = 0;
  newStringRouter[4] = 1;
  newStringRouter[1] = (int)str;
  newStringRouter[3] = maximumPosition;
  newStringRouter[5] = g_StringRouterListHead;
  g_StringRouterListHead = (int)newStringRouter;
  return 1;
}
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491F30) --------------------------------------------------------
int  IO_FindStringRouter(int name)
{
  _DWORD *currentRouter; // ecx

  currentRouter = (_DWORD *)g_StringRouterListHead;
  while ( currentRouter )
  {
    if ( !strcmp_(currentRouter[0], name) )
      return (int)currentRouter;
    currentRouter = (_DWORD *)currentRouter[5];
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;

//----- (00491F60) --------------------------------------------------------
int  Rules_ParseAssertCommand(int logicalName, _DWORD *theToken, int atLeastOne, int *error, int readFirstParen, int a6)
{
  int readParenFlag; // eax
  signed int lastOne; // esi
  int v9; // edx
  unsigned int nextOne; // ecx
  int **Symbol; // eax
  signed int stub; // eax
  int v13; // ecx
  signed int v14; // ecx
  int **prognSymbol; // eax
  int v17; // ecx
  signed int assertList; // [esp+8h] [ebp-10h]

  readParenFlag = readFirstParen;
  *error = 0;
  if ( !readFirstParen && *theToken == 101 )
  {
    if ( atLeastOne )
    {
      *error = 1;
      Parser_ReportSyntaxError();
    }
    return 0;
  }
  lastOne = 0;
  assertList = 0;
  while ( 1 )
  {
    nextOne = Rules_ParseAssertRHSPattern(logicalName, (int)theToken, 0, error, readParenFlag, 1, 101);
    if ( !nextOne )
      break;
    AST_Append(nextOne, v9);
    Symbol = Rules_MakeSymbol(aAssert_1);
    stub = AST_NewNode(10, (int)Symbol);
    *(_DWORD *)(stub + 6) = v13;
    v14 = stub;
    if ( lastOne )
      *(_DWORD *)(lastOne + 10) = stub;
    else
      assertList = stub;
    readParenFlag = 1;
    lastOne = v14;
  }
  if ( *error )
  {
    AST_Free(assertList);
    return 0;
  }
  else
  {
    if ( *theToken == 101 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_504BB8);
    }
    if ( !assertList )
    {
      if ( atLeastOne )
      {
        *error = 1;
        Parser_ReportSyntaxError();
        return 0;
      }
      return 0;
    }
    if ( *(_DWORD *)(assertList + 10) )
    {
      prognSymbol = Rules_MakeSymbol(aProgn_3);
      assertList = AST_NewNode(10, (int)prognSymbol);
      *(_DWORD *)(assertList + 6) = v17;
    }
    return assertList;
  }
}
// 491FA6: variable 'v9' is possibly undefined
// 491FC1: variable 'v13' is possibly undefined
// 492079: variable 'v17' is possibly undefined

//----- (00492090) --------------------------------------------------------
unsigned int  Rules_ParseAssertRHSPattern(
        int logicalName,
        int theToken,
        int constantsOnly,
        int *error,
        int readFirstParen,
        int checkFirstParen,
        int endType)
{
  unsigned int tokenType; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int foundConstruct; // eax
  int theDeftemplate; // ebx
  int nextOne; // eax
  _BYTE *templateNameString; // ebx
  int currentModule; // eax
  int v21; // ecx
  int templateArgs; // eax
  int v23; // edx
  signed int v24; // edx
  int bitmapValue; // eax
  signed int multifieldExpr; // eax
  int printError; // [esp+0h] [ebp-30h] BYREF
  int count; // [esp+4h] [ebp-2Ch] BYREF
  signed int returnExpr; // [esp+8h] [ebp-28h]
  signed int deftemplateExpr; // [esp+Ch] [ebp-24h]
  int firstOne; // [esp+10h] [ebp-20h]
  int templateName; // [esp+14h] [ebp-1Ch]
  int constantsOnlyFlag; // [esp+18h] [ebp-18h]
  int lastOne; // [esp+1Ch] [ebp-14h]
  int argHead; // [esp+20h] [ebp-10h]

  constantsOnlyFlag = constantsOnly;
  lastOne = 0;
  *error = 0;
  argHead = 0;
  if ( readFirstParen )
    Parser_NextToken(logicalName, theToken);
  if ( checkFirstParen )
  {
    tokenType = *(_DWORD *)theToken;
    if ( *(_DWORD *)theToken == endType )
      return endType ^ tokenType;
    if ( tokenType != 100 )
      goto LABEL_20;
  }
  Parser_NextToken(logicalName, theToken);
  templateName = *(_DWORD *)((uintptr_t)(unsigned int)theToken + 4);
  templateNameString = (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)templateName + 16);
  if ( *(_DWORD *)(uintptr_t)(unsigned int)theToken != 2 || !strcmp((const char *)templateNameString, asc_504BF4) || !strcmp((const char *)templateNameString, asc_504BF8) )
  {
LABEL_20:
    Parser_ReportSyntaxError();
    *error = 1;
    return 0;
  }
  if ( Rules_IsReservedPatternSymbol((int)(uintptr_t)templateNameString, 0) )
  {
    Rules_PrintReservedSymbolErrorMessage((int)(uintptr_t)templateNameString, (int)aARelationName);
    *error = 1;
    return 0;
  }
  if ( Rules_FindModuleSeparator(templateNameString) )
  {
    Module_ReportIllegalSpecifierError();
    *error = 1;
    return 0;
  }
  foundConstruct = Rules_FindImportExportConstruct(aDeftemplate, &count, templateNameString, 1, 0);
  theDeftemplate = foundConstruct;
  if ( count > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)aDeftemplate, (int)(uintptr_t)templateNameString);
    *error = 1;
    return 0;
  }
  if ( !foundConstruct )
  {
    if ( Rules_IsBloaded() )
    {
      Rules_ReportNoTemplateError();
      *error = 1;
      return 0;
    }
    currentModule = Module_GetCurrent();
    if ( Rules_FindImportExportConflict(aDeftemplate, currentModule, templateNameString) )
    {
      Lexer_WarnImpliedTemplate((int)aImpliedDeftemp, (int)(uintptr_t)templateNameString, 0);
      *error = 1;
      return 0;
    }
    theDeftemplate = Rules_CreateDeftemplateRecord(templateName, 1);
  }
  if ( (*(_BYTE *)(theDeftemplate + 24) & 1) != 0 )
  {
    firstOne = AST_NewNode(35, theDeftemplate);
    while ( 1 )
    {
      IO_OutWriteToken(asc_504C2C);
      nextOne = Rules_ParseAssertArgument(logicalName, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, endType, constantsOnlyFlag, &printError);
      if ( !nextOne )
        break;
      if ( argHead )
        *(_DWORD *)(lastOne + 10) = nextOne;
      else
        argHead = nextOne;
      lastOne = nextOne;
    }
    if ( *error )
    {
      if ( printError )
        Parser_ReportSyntaxError();
      AST_Free(firstOne);
      AST_Free(argHead);
      return 0;
    }
    else
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(*(char **)(theToken + 8));
      bitmapValue = Rules_AddBitmapValue(g_Rules_DefaultZeroBitmapValue, v24);
      multifieldExpr = AST_NewNode(34, bitmapValue);
      *(_DWORD *)(firstOne + 10) = multifieldExpr;
      *(_DWORD *)(multifieldExpr + 6) = argHead;
      return firstOne;
    }
  }
  else
  {
    deftemplateExpr = AST_NewNode(35, theDeftemplate);
    returnExpr = deftemplateExpr;
    templateArgs = Rules_ParseAssertTemplate(logicalName, theToken, endType, error, v21, theDeftemplate);
    v23 = deftemplateExpr;
    *(_DWORD *)(deftemplateExpr + 10) = templateArgs;
    if ( *error )
    {
      AST_Free(v23);
      return 0;
    }
    return returnExpr;
  }
}
// 4920F3: variable 'v11' is possibly undefined
// 49210B: variable 'v12' is possibly undefined
// 492124: variable 'v13' is possibly undefined
// 49222E: variable 'v14' is possibly undefined
// 49231D: variable 'v21' is possibly undefined
// 4923AB: variable 'v24' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 504C30: using guessed type _BYTE byte_504C30[4];

//----- (004923E0) --------------------------------------------------------
int  Rules_ParseAssertArgument(int logicalName, unsigned int *theToken, _DWORD *error, int endType, int constantsOnly, _DWORD *printError)
{
  unsigned int theType; // edx
  int token_symbol; // eax
  const char *token_text; // eax
  bool parse_expression; // zf
  int result; // eax
  unsigned int token_type; // eax

  *printError = 1;
  Parser_NextToken(logicalName, (int)theToken);
  theType = *theToken;
  if ( endType == *theToken )
    return 0;
  if ( theType == 2 )
  {
    token_symbol = theToken[1];
    token_text = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)token_symbol + 16);
    parse_expression = strcmp(token_text, asc_504BF4) == 0;
  }
  else
  {
    parse_expression = theType == 100;
  }
  if ( !parse_expression )
  {
    token_type = *theToken;
    if ( *theToken != 2 && token_type != 3 && token_type != 8 && token_type >= 2 )
    {
      if ( token_type != 15 && token_type != 13 && token_type != 14 && token_type != 16 )
      {
        *error = 1;
        return 0;
      }
      if ( constantsOnly )
      {
        *error = 1;
        return 0;
      }
    }
    return AST_NewNode(*theToken, theToken[1]);
  }
  if ( constantsOnly )
  {
    *error = 1;
    return 0;
  }
  else
  {
    if ( *theToken == 100 )
      result = Parser_ParseExpression(logicalName, endType);
    else
      result = Parser_ParseRequiredFunctionCall(logicalName, endType);
    if ( !result )
    {
      *printError = 0;
      *error = 1;
    }
  }
  return result;
}
// 49247B: simplified comparisons for 'eax.4': ==0 || ==1 became <2u

//----- (004924D0) --------------------------------------------------------
_DWORD * Rules_StringToFact(const char *theString, int a2, double a3)
{
  signed int numberOfFields; // esi
  unsigned int assertArgs; // edi
  int v6; // ecx
  int v7; // ecx
  int i; // eax
  _DWORD *theFact; // eax
  __int16 *currentArg; // ecx
  _DWORD *factPtr; // esi
  _DWORD *fieldPtr; // ebx
  EvalResultBuffer parsed; // [esp-4h] [ebp-3Ch] BYREF
  int token_buffer_ptr; // [esp+14h] [ebp-24h]
  int error[6]; // [esp+20h] [ebp-18h] BYREF

  error[4] = a2;
  numberOfFields = 0;
  error[0] = 0;
  token_buffer_ptr = Compat_AllocLow32Bytes(12);
  if ( !token_buffer_ptr )
    return 0;
  IO_OpenStringSource((int)aAssert_str, theString, 0);
  assertArgs = Rules_ParseAssertRHSPattern((int)aAssert_str, token_buffer_ptr, 0, error, 1, 1, 101);
  IO_CloseStringRouter((int)aAssert_str);
  if ( error[0] )
  {
    AST_Free(assertArgs);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return 0;
  }
  else if ( AST_TreeContainsSpecialTag(assertArgs, 0) )
  {
    Rules_ReportLocalVariableError();
    Lexer_ErrorRecover(1);
    AST_Free(assertArgs);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return 0;
  }
  else
  {
    for ( i = *(_DWORD *)((uintptr_t)(unsigned int)assertArgs + 10); i; ++numberOfFields )
      i = *(_DWORD *)(i + 10);
    theFact = Module_AllocList(numberOfFields);
    theFact[4] = *(_DWORD *)((uintptr_t)(unsigned int)assertArgs + 2);
    currentArg = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)assertArgs + 10);
    factPtr = theFact;
    if ( currentArg )
    {
      fieldPtr = theFact;
      do
      {
        memset(&parsed, 0, sizeof(parsed));
        Parser_ParseForm(currentArg, (_DWORD *)&parsed, (int)currentArg, a3);
        *((_WORD *)fieldPtr + 27) = parsed.type;
        fieldPtr[14] = parsed.value;
        currentArg = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)currentArg + 10);
        fieldPtr = (_DWORD *)((char *)fieldPtr + 6);
      }
      while ( currentArg );
    }
    AST_Free(assertArgs);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return factPtr;
  }
}

//----- (004925D0) --------------------------------------------------------
signed int Rules_ReportNoTemplateError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aFactrhs, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTemplate, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotExistFo, v2);
}
// 4925F0: variable 'v0' is possibly undefined
// 4925FC: variable 'v1' is possibly undefined
// 49260B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00492620) --------------------------------------------------------
int  Rules_FindModuleSeparator(_BYTE *theString)
{
  int position; // ecx
  int foundColon; // edx
  char currentChar; // bl

  if ( getenv("CLASH95_TRACE_PARSER_QUALIFIER_SCAN") )
  {
    fprintf(stderr, "[parser] qualifier-scan text=%p caller=%p\n", theString, __builtin_return_address(0));
    fflush(stderr);
  }
  position = 0;
  foundColon = 0;
  if ( *theString )
  {
    do
    {
      if ( *theString == 58 )
      {
        if ( foundColon )
          return position;
        foundColon = 1;
      }
      else
      {
        foundColon = 0;
      }
      currentChar = *++theString;
      ++position;
    }
    while ( currentChar );
  }
  return 0;
}

//----- (00492660) --------------------------------------------------------
signed int * Rules_ExtractModuleName(signed int thePosition)
{
  char *newString; // esi
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  signed int *returnValue; // ebx
  int v7; // edx

  if ( thePosition <= 1 )
    return 0;
  newString = (char *)Mem_SmallBlockAlloc(thePosition);
  strncpy_(v4, v3);
  newString[v5 - 1] = 0;
  returnValue = Str_Intern(newString, v5);
  Mem_SmallBlockFree(newString, v7);
  return returnValue;
}
// 492678: variable 'v4' is possibly undefined
// 492678: variable 'v3' is possibly undefined
// 49267D: variable 'v5' is possibly undefined
// 492691: variable 'v7' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004926A0) --------------------------------------------------------
signed int * Rules_ExtractConstructName(int thePosition, char *theString, int a3)
{
  signed int theLength; // ecx
  int newStringSize; // esi
  _DWORD *newString; // eax
  int v7; // edx
  char *v8; // ecx
  signed int *returnValue; // ebx
  _DWORD *v10; // ecx

  if ( !thePosition )
    return Str_Intern(theString, a3);
  theLength = strlen(theString);
  if ( theLength <= thePosition + 1 )
    return 0;
  newStringSize = theLength - thePosition;
  newString = Mem_SmallBlockAlloc(theLength - thePosition);
  strncpy_(newString, v7);
  returnValue = Str_Intern(v8, (int)v8);
  Mem_SmallBlockFree(v10, newStringSize);
  return returnValue;
}
// 4926E1: variable 'v7' is possibly undefined
// 4926E8: variable 'v8' is possibly undefined
// 4926F3: variable 'v10' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00492700) --------------------------------------------------------
int  Rules_ExtractModuleAndConstructName(_BYTE *theName)
{
  signed int qualifier_length; // eax
  signed int *module_symbol; // eax
  int *module_record; // eax
  signed int *local_symbol; // eax

  qualifier_length = Rules_FindModuleSeparator(theName);
  if ( !qualifier_length )
    return (int)theName;
  module_symbol = Rules_ExtractModuleName(qualifier_length);
  if ( !module_symbol )
    return 0;
  module_record = Module_FindByName((_BYTE *)module_symbol[4]);
  if ( !module_record )
    return 0;
  Module_SetCurrent((int)module_record);
  local_symbol = Rules_ExtractConstructName(qualifier_length, (char *)theName, (int)theName);
  if ( !local_symbol )
    return 0;
  return local_symbol[4];
}

//----- (00492760) --------------------------------------------------------
int  Rules_FindImportExportConstruct(char *constructName, _DWORD *count, _BYTE *findName, int searchCurrent, int notYetDefinedInModule)
{
  int construct_record; // ebx
  signed int *local_symbol; // ecx
  signed int *construct_symbol; // eax
  int result; // edx

  *count = 0;
  if ( Rules_FindModuleSeparator(findName) )
    return 0;
  Module_BeginEnum();
  construct_record = Module_FindItemByName((int)constructName);
  if ( construct_record && *(_DWORD *)((uintptr_t)(unsigned int)construct_record + 24) )
  {
    Rules_ClearModuleSearchMarkers();
    local_symbol = Str_Intern((char *)findName, 0);
    construct_symbol = Str_Intern(constructName, 0);
    result = Rules_SearchImportExportModules((int)(uintptr_t)construct_symbol, 0, (int)(uintptr_t)local_symbol, construct_record, count, searchCurrent, notYetDefinedInModule);
    Module_EndEnum();
    return result;
  }
  else
  {
    Module_EndEnum();
    return 0;
  }
}

//----- (004927E0) --------------------------------------------------------
signed int  Rules_ReportAmbiguousReferenceError(int constructName, int findName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAmbiguousRefer, constructName);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v3, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504CA8, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], findName, v5);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a_ItIsImportedF, v6);
}
// 4927FC: variable 'v3' is possibly undefined
// 49280B: variable 'v4' is possibly undefined
// 492817: variable 'v5' is possibly undefined
// 492826: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00492830) --------------------------------------------------------
int Rules_ClearModuleSearchMarkers()
{
  int result; // eax

  if ( !g_Clips_CurrentModule )
  {
    result = Module_NextEnum(0);
    if ( !result )
      return 0;
    Module_SetCurrent(result);
  }
  *(_DWORD *)(g_Clips_CurrentModule + 20) = 0;
  for ( result = Module_NextEnum(0); result; result = Module_NextEnum(result) )
    *(_DWORD *)(result + 20) = 0;
  return result;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00492870) --------------------------------------------------------
int  Rules_SearchImportExportModules(int constructType, int matchModule, int findName, int theModuleItem, _DWORD *count, int searchCurrent, int notYetDefinedInModule)
{
  int current_module; // edx
  int found_construct; // eax
  int import_node; // ebp
  int imported_module; // eax
  int export_node; // eax
  int import_matches; // ecx
  int export_matches; // edx
  int result; // [esp+8h] [ebp-14h]
  int (*lookup_by_name)(const char *, int); // [esp+Ch] [ebp-10h]
  const char *local_name; // eax

  current_module = Module_GetCurrent();
  result = 0;
  if ( *(_DWORD *)((uintptr_t)(unsigned int)current_module + 20) )
    return 0;
  if ( searchCurrent && (!matchModule || current_module == matchModule) )
  {
    lookup_by_name = (int (*)(const char *, int))(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theModuleItem + 24);
    local_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)findName + 16);
    found_construct = lookup_by_name(local_name, theModuleItem);
    if ( current_module == notYetDefinedInModule )
    {
      result = found_construct;
      ++*count;
    }
    else if ( found_construct )
    {
      if ( current_module == *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)found_construct + 8) )
        ++*count;
      result = found_construct;
    }
  }
  *(_DWORD *)((uintptr_t)(unsigned int)current_module + 20) = 1;
  current_module = Module_GetCurrent();
  import_node = *(_DWORD *)((uintptr_t)(unsigned int)current_module + 12);
  while ( import_node )
  {
    imported_module = current_module;
    import_matches = 0;
    found_construct = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 4);
    if ( !found_construct || constructType == found_construct )
    {
      found_construct = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 8);
      if ( !found_construct || findName == found_construct )
      {
        import_matches = 1;
        imported_module = (int)(uintptr_t)Module_FindByName(
                                            (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)import_node + 16));
        if ( !imported_module )
          goto next_import;
      }
    }
    if ( import_matches )
    {
      export_matches = 0;
      export_node = *(_DWORD *)((uintptr_t)(unsigned int)imported_module + 16);
      while ( export_node )
      {
        found_construct = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 4);
        if ( !found_construct || constructType == found_construct )
        {
          found_construct = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 8);
          if ( !found_construct || findName == found_construct )
          {
            export_matches = 1;
            break;
          }
        }
        export_node = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 12);
      }
      if ( !export_matches )
        goto next_import;
    }
    if ( import_matches )
    {
      Module_SetCurrent(imported_module);
      found_construct = Rules_SearchImportExportModules(constructType, matchModule, findName, theModuleItem, count, 1, notYetDefinedInModule);
      if ( found_construct )
        result = found_construct;
    }
next_import:
    import_node = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 12);
  }
  return result;
}

//----- (004929E0) --------------------------------------------------------
int  Rules_ListConstructsAcrossModules(
        int logicalName,
        int Enum,
        int singleName,
        int pluralName,
        int (__cdecl *nextFunction)(int),
        int (*nameFunction)(void),
        void (__fastcall *printFunction)(int, int),
        int (*doItFunction)(void))
{
  int count; // ebp
  int allModules; // edi
  int v11; // edx
  int Name; // eax
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int i; // ecx
  int v17; // ecx
  int constructName; // ebx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-18h]

  v20 = singleName;
  Module_BeginEnum();
  count = 0;
  allModules = 0;
  if ( !v11 )
  {
    allModules = 1;
    Enum = Module_NextEnum(0);
  }
  while ( Enum )
  {
    if ( allModules )
    {
      Name = Module_GetName(Enum);
      Output_Write(logicalName, Name, v13);
      Output_Write(logicalName, (int)asc_504CDC, v14);
    }
    Module_SetCurrent(Enum);
    result = nextFunction(v20);
    for ( i = result; result; i = result )
    {
      if ( g_ClipsHaltExecution == 1 )
        return result;
      if ( !doItFunction || doItFunction() )
      {
        if ( !nameFunction )
        {
          if ( !printFunction )
            goto LABEL_15;
          if ( allModules )
            Output_Write(logicalName, (int)asc_504CE0, i);
          printFunction(i, i);
          goto LABEL_14;
        }
        constructName = nameFunction();
        if ( constructName )
        {
          if ( allModules )
            Output_Write(logicalName, (int)asc_504CE0, v17);
          Output_Write(logicalName, constructName, v17);
LABEL_14:
          Output_Write(logicalName, (int)asc_504CE4, v19);
        }
      }
LABEL_15:
      result = ((int (*)(void))nextFunction)();
      ++count;
    }
    if ( !allModules )
      break;
    Enum = Module_NextEnum(Enum);
  }
  if ( pluralName )
    Rules_PrintTally(logicalName, count, v20, pluralName);
  return Module_EndEnum();
}
// 4929FE: variable 'v11' is possibly undefined
// 492A1F: variable 'v13' is possibly undefined
// 492A2B: variable 'v14' is possibly undefined
// 492A3B: variable 'v20' is possibly undefined
// 492A7F: variable 'v17' is possibly undefined
// 492A94: variable 'v19' is possibly undefined
// 492B04: variable 'i' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (00492B30) --------------------------------------------------------
int Rules_RegisterDeftemplateConstruct()
{
  int v0; // edx
  int v1; // ecx

  Rules_InitFacts();
  Rules_InitDeftemplateHashTable();
  Rules_RegisterDeftemplateFunctions(v1, v0);
  Rules_RegisterModifyDuplicateFunctions();
  g_DeftemplateConstructType = (int)Rules_RegisterConstructType(
                        (int)aDeftemplate_1,
                        (int)aDeftemplates,
                        (int)Rules_FindDeftemplateByName,
                        (int)Rules_ParseDeftemplate,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Rules_GetNextDeftemplate,
                        (int)Rules_SetConstructNextInModule,
                        (int)Rules_DeftemplateIsDeletable,
                        (int)Rules_DeleteDeftemplate,
                        (int)Rules_FreeDeftemplateRecord);
  return Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_Deftemplate, 35);
}
// 492B3D: variable 'v1' is possibly undefined
// 492B3D: variable 'v0' is possibly undefined
// 54E650: using guessed type int dword_54E650;

//----- (00492BA0) --------------------------------------------------------
int *Rules_InitDeftemplateHashTable()
{
  g_ClipsDeftemplateModuleItemId = Module_RegisterItem(
                   (int)aDeftemplate_1,
                   (int)Rules_AllocDeftemplateHashNode,
                   (int)Rules_DeftemplateGetBloadedModuleItem,
                   (int)Rules_FreeDeftemplateHashNode,
                   (int)Rules_DeftemplateWriteModuleHeaderRef,
                   (int)Rules_FindDeftemplateByName);
  return Module_RegisterImportExportConstructType((int)aDeftemplate_1, 2);
}
// 54E654: using guessed type int dword_54E654;

//----- (00492BE0) --------------------------------------------------------
signed int Rules_AllocDeftemplateHashNode()
{
  _DWORD *freeListNode; // edx

  freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListNode )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListNode;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492C10) --------------------------------------------------------
int  Rules_FreeDeftemplateHashNode(int theItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theItem, g_DeftemplateConstructType, theItem);
  freed_node = (_DWORD *)theItem;
  g_ClipsMemFreeListTemp = theItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E650: using guessed type int dword_54E650;

//----- (00492C60) --------------------------------------------------------
int  Rules_FindDeftemplateByName(_BYTE *deftemplateName, int a2)
{
  return Rules_FindConstructByNameGeneric(deftemplateName, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (00492C70) --------------------------------------------------------
int  Rules_GetNextDeftemplate(int deftemplatePtr)
{
  return Class_Enum(deftemplatePtr, g_ClipsDeftemplateModuleItemId);
}
// 54E654: using guessed type int dword_54E654;

//----- (00492C80) --------------------------------------------------------
int Rules_DeftemplateIsDeletable()
{
  int result; // eax
  int theDeftemplate; // edx

  result = Rules_IsBloaded();
  if ( result )
    return 0;
  if ( *(int *)(theDeftemplate + 28) <= 0 && !*(_DWORD *)(theDeftemplate + 32) )
    return 1;
  return result;
}
// 492C8C: variable 'v1' is possibly undefined

//----- (00492CB0) --------------------------------------------------------
int  Rules_FreeDeftemplateRecord(int result)
{
  int template_def; // ecx
  int slot; // edx
  int next_slot; // ecx

  template_def = result;
  if ( result )
  {
    g_Rules_DeftemplateWatchFlag = (*(_BYTE *)(template_def + 24) & 2) != 0;
    slot = *(_DWORD *)(template_def + 20);
    while ( slot )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)slot, template_def);
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 12), template_def);
      AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 8));
      *(_DWORD *)(slot + 12) = 0;
      *(_DWORD *)(slot + 8) = 0;
      next_slot = *(_DWORD *)(slot + 16);
      slot = next_slot;
    }
    Rules_FreeTemplateSlotList(*(_DWORD *)(template_def + 20));
    Rules_FreeConstructHeaderString((int *)(uintptr_t)(unsigned int)template_def, template_def);
    g_ClipsMemFreeListTemp = template_def;
    *(_DWORD *)template_def = *(_DWORD *)(g_ClipsMemoryTable + 144);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 144) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 51A948: using guessed type int dword_51A948;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492D60) --------------------------------------------------------
int  Rules_FreeTemplateSlotList(int result)
{
  int node; // edx
  int next; // ecx
  int last_result; // eax

  node = result;
  last_result = 0;
  while ( node )
  {
    next = *(_DWORD *)(node + 16);
    AST_Free(*(_DWORD *)(node + 12));
    AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8));
    g_ClipsMemFreeListTemp = node;
    *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 80);
    last_result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    node = next;
  }
  return last_result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492DB0) --------------------------------------------------------
int  Rules_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 28);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (00492DC0) --------------------------------------------------------
int  Rules_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(result + 28);
  return result;
}

//----- (00492DD0) --------------------------------------------------------
int Rules_InitExpressionHashTable()
{
  int result; // eax

  Rules_CacheConnectiveSymbols();
  g_ExpressionHashTable = (int)Mem_SmallBlockAlloc(0x7DCu);
  for ( result = 0; result != 2012; result += 4 )
    *(_DWORD *)(g_ExpressionHashTable + result) = 0;
  return result;
}
// 51A9FC: using guessed type int dword_51A9FC;

//----- (00492E10) --------------------------------------------------------
int **Rules_CacheConnectiveSymbols()
{
  int **result; // eax
  int v1; // ecx

  g_Clips_SymbolAnd = (int)Rules_MakeSymbol(aAnd);
  g_ClipsSymbolOr = (int)Rules_MakeSymbol(aOr);
  g_ClipsSymbolEq = (int)Rules_MakeSymbol(aEq);
  g_ClipsSymbolNeq = (int)Rules_MakeSymbol(aNeq);
  result = Rules_MakeSymbol(aNot);
  g_ClipsNotSymbol = (int)result;
  if ( !g_Clips_SymbolAnd || !g_ClipsSymbolOr || !g_ClipsSymbolEq || !g_ClipsSymbolNeq || !result )
  {
    Rules_ReportSystemError(v1, 1);
    return (int **)IO_RunRouterExitCallbacks();
  }
  return result;
}
// 492E91: variable 'v1' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E65C: using guessed type int dword_54E65C;
// 54E660: using guessed type int dword_54E660;
// 54E664: using guessed type int dword_54E664;
// 54E668: using guessed type int dword_54E668;

//----- (00492EB0) --------------------------------------------------------
__int16 * AST_InstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomInstall(*node, *(_DWORD *)(node + 1), (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_InstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492EE0) --------------------------------------------------------
__int16 * AST_DeinstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomDeinstall(
      *node,
      (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)node + 2),
      (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492F10) --------------------------------------------------------
_DWORD * AST_PackNodeChain(_DWORD *result)
{
  int node_count; // eax
  _DWORD *copy; // esi

  if ( result )
  {
    node_count = AST_CountTreeNodes((int)result);
    copy = Mem_NewArray(14 * node_count);
    AST_CopyNodeChainToArray((int)result, (int)copy, 0);
    return copy;
  }
  return result;
}

//----- (00492F50) --------------------------------------------------------
int  AST_CopyNodeChainToArray(int theList, int theArray, int storeIndex)
{
  int node; // ecx
  int current_index; // edi
  int output_node; // eax
  int child_node; // edx
  int next_node; // edi

  node = theList;
  if ( !theList )
    return storeIndex;
  while ( node )
  {
    current_index = storeIndex;
    output_node = theArray + 14 * storeIndex;
    *(_WORD *)output_node = *(_WORD *)node;
    *(_DWORD *)(output_node + 2) = *(_DWORD *)(node + 2);
    ++storeIndex;
    child_node = *(_DWORD *)(node + 6);
    if ( child_node )
    {
      *(_DWORD *)(output_node + 6) = theArray + 14 * storeIndex;
      storeIndex = AST_CopyNodeChainToArray(child_node, theArray, storeIndex);
    }
    else
    {
      *(_DWORD *)(output_node + 6) = 0;
    }
    next_node = *(_DWORD *)(node + 10);
    if ( next_node )
      *(_DWORD *)(theArray + 14 * current_index + 10) = theArray + 14 * storeIndex;
    else
      *(_DWORD *)(theArray + 14 * current_index + 10) = 0;
    node = next_node;
  }
  return storeIndex;
}

//----- (00492FD0) --------------------------------------------------------
int  AST_FreePackedNodeChain(int result)
{
  int node_count; // eax

  if ( result )
  {
    node_count = AST_CountTreeNodes(result);
    return Mem_SmallBlockRelease((_DWORD *)result, 14 * node_count);
  }
  return result;
}

//----- (00492FF0) --------------------------------------------------------
signed int AST_AllocNode()
{
  int node;

  node = *(_DWORD *)(g_ClipsMemoryTable + 288);
  if ( node )
  {
    g_ClipsMemFreeListTemp = node;
    *(_DWORD *)(g_ClipsMemoryTable + 288) = *(_DWORD *)node;
    node = g_ClipsMemFreeListTemp;
  }
  else
  {
    node = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }

  *(_DWORD *)node = 103;
  *(_DWORD *)(node + 4) = 0;
  *(_DWORD *)(node + 16) = 0;
  *(_DWORD *)(node + 20) = 0;
  *(_DWORD *)(node + 24) = 0;
  *(_DWORD *)(node + 28) = -1;
  *(_DWORD *)(node + 32) = -1;
  *(_DWORD *)(node + 36) = 0;
  *(_DWORD *)(node + 40) = -1;
  *(_DWORD *)(node + 44) = 1;
  *(_DWORD *)(node + 48) = 1;
  *(_DWORD *)(node + 52) = 0;
  *(_DWORD *)(node + 56) = 0;
  *(_DWORD *)(node + 60) = 0;
  *(_DWORD *)(node + 64) = 0;
  *(_DWORD *)(node + 68) = 0;
  *(_DWORD *)(node + 8) &= 0xE0003FC0;
  *(_WORD *)(node + 12) &= 0xC000u;
  *(_BYTE *)(node + 8) |= 0x20u;
  return node;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
int AST_FreeNode(int result)
{
  int node;
  int owner;
  int (__thiscall *cleanup_fn)(void *this, int);

  node = result;
  if ( !node )
    return 0;

  AST_Free(*(_DWORD *)(node + 52));
  AST_FreeNode(*(_DWORD *)(node + 64));
  AST_FreeNode(*(_DWORD *)(node + 68));
  AST_FreeNode(*(_DWORD *)(node + 56));
  if ( *(_BYTE *)(node + 8) & 0x10 )
    AST_DecrementNodeRefCount(*(_DWORD **)(node + 16));

  if ( *(_DWORD *)(node + 60) )
  {
    owner = *(_DWORD *)(node + 24);
    if ( owner )
    {
      cleanup_fn = *(int (__thiscall **)(void *this, int))(owner + 64);
      if ( cleanup_fn )
        cleanup_fn((void *)owner, *(_DWORD *)(node + 60));
    }
  }

  g_ClipsMemFreeListTemp = node;
  *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 288);
  *(_DWORD *)(g_ClipsMemoryTable + 288) = g_ClipsMemFreeListTemp;
  return g_ClipsMemoryTable;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493000) --------------------------------------------------------
int  AST_Free(int result)
{
  int i; // edx
  _DWORD *currentNode; // eax

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp )
  {
    if ( *(_DWORD *)(i + 6) )
      AST_Free(*(_DWORD *)(i + 6));
    currentNode = (_DWORD *)i;
    i = *(_DWORD *)(i + 10);
    g_ClipsMemFreeListTemp = (int)currentNode;
    *currentNode = *(_DWORD *)(g_ClipsMemoryTable + 56);
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 493015: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
__int16 * AST_FindHashedNodeChain(__int16 *result, _DWORD *hashInfo)
{
  __int16 *theExpression; // esi
  unsigned int hashValue; // eax
  unsigned int *v5; // edx
  int hashEntry; // ecx
  int v7; // ecx

  theExpression = result;
  if ( result )
  {
    hashValue = AST_HashNodeChain(result);
    *v5 = hashValue;
    *hashInfo = 0;
    hashEntry = *(_DWORD *)(g_ExpressionHashTable + 4 * *v5);
    if ( hashEntry )
    {
      while ( !AST_NodeListsEqual(*(__int16 **)(hashEntry + 8), theExpression) )
      {
        *hashInfo = v7;
        hashEntry = *(_DWORD *)(v7 + 12);
        if ( !hashEntry )
          return 0;
      }
      return (__int16 *)v7;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 493060: variable 'v5' is possibly undefined
// 493084: variable 'v7' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;

//----- (004930A0) --------------------------------------------------------
unsigned int  AST_HashNodeChain(__int16 *theExp)
{
  __int16 *currentExpr; // edx
  int argList; // ecx
  unsigned int tally; // eax
  int nodeValue; // ebx
  unsigned int v5; // eax

  currentExpr = theExp;
  argList = *(_DWORD *)(theExp + 3);
  tally = 269;
  if ( argList )
    tally = 257 * AST_HashNodeChain(argList) + 269;
  while ( currentExpr )
  {
    nodeValue = *(_DWORD *)(currentExpr + 1);
    v5 = 263 * *currentExpr + tally;
    currentExpr = *(__int16 **)(currentExpr + 5);
    tally = nodeValue + v5;
  }
  return tally % 0x1F7;
}
// 4930B3: variable 'v1' is possibly undefined

//----- (004930F0) --------------------------------------------------------
__int16 * AST_RemoveHashedNodeChain(__int16 *theExpression, int a2)
{
  __int16 *result; // eax
  int newCount; // ecx
  int v5; // edx
  _DWORD *v6; // edx
  _DWORD hashInfo[5]; // [esp+0h] [ebp-14h] BYREF

  hashInfo[3] = a2;
  result = AST_FindHashedNodeChain(theExpression, hashInfo);
  if ( result )
  {
    newCount = *((_DWORD *)result + 1) - 1;
    *((_DWORD *)result + 1) = newCount;
    if ( !newCount )
    {
      if ( hashInfo[0] )
        *(_DWORD *)(hashInfo[0] + 12) = *((_DWORD *)result + 3);
      else
        *(_DWORD *)(g_ExpressionHashTable + 4 * hashInfo[1]) = *((_DWORD *)result + 3);
      AST_DeinstallNodeChain(*((__int16 **)result + 2));
      AST_FreePackedNodeChain(*(_DWORD *)(v5 + 8));
      g_ClipsMemFreeListTemp = (int)v6;
      *v6 = *(_DWORD *)(g_ClipsMemoryTable + 80);
      result = (__int16 *)g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 493127: variable 'v5' is possibly undefined
// 493134: variable 'v6' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493170) --------------------------------------------------------
__int16 * AST_AddHashedNodeChain(__int16 *result, int a2, int a3)
{
  __int16 *foundEntry; // eax
  _DWORD *v4; // ecx
  _DWORD *freeListEntry; // edx
  _DWORD *newEntry; // edx
  __int16 *packedChain; // eax
  int v8; // edx
  _DWORD *hashEntry; // edx
  _DWORD searchContext[5]; // [esp-4h] [ebp-14h] BYREF

  searchContext[3] = a3;
  searchContext[2] = a2;
  if ( result )
  {
    foundEntry = AST_FindHashedNodeChain(result, searchContext);
    if ( foundEntry )
    {
      ++*((_DWORD *)foundEntry + 1);
      return (__int16 *)*((_DWORD *)foundEntry + 2);
    }
    else
    {
      freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 80);
      if ( freeListEntry )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
        *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeListEntry;
        newEntry = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        newEntry = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
      }
      *newEntry = searchContext[1];
      newEntry[1] = 1;
      packedChain = (__int16 *)AST_PackNodeChain(v4);
      *(_DWORD *)(v8 + 8) = packedChain;
      AST_InstallNodeChain(packedChain);
      hashEntry[3] = *(_DWORD *)(g_ExpressionHashTable + 4 * *hashEntry);
      *(_DWORD *)(g_ExpressionHashTable + 4 * *hashEntry) = hashEntry;
      hashEntry[4] = 0;
      return (__int16 *)hashEntry[2];
    }
  }
  return result;
}
// 4931B9: variable 'v4' is possibly undefined
// 4931BE: variable 'v8' is possibly undefined
// 4931CC: variable 'v9' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493210) --------------------------------------------------------
signed int  AST_GetHashedNodeIndex(__int16 *theExpression)
{
  __int16 *hashEntry; // eax
  int hashInfo; // [esp+0h] [ebp-8h] BYREF

  if ( !theExpression )
    return -1;
  hashEntry = AST_FindHashedNodeChain(theExpression, &hashInfo);
  if ( hashEntry )
    return *((_DWORD *)hashEntry + 4);
  else
    return -1;
}

//----- (00493250) --------------------------------------------------------
char * Parser_NextToken(int readSource, int theToken)
{
  unsigned int v4; // ecx
  char charType; // dl
  signed int firstChar; // eax
  unsigned int v7; // ecx
  int v8; // eax
  signed int count; // edx
  signed int *tokenSymbol; // eax
  int printForm; // eax
  char *printText; // eax
  char *result; // eax
  unsigned int v14; // ecx
  int nextChar; // ecx
  unsigned int v16; // ecx
  signed int sfNameLength; // ecx
  int sfVarSymbol; // edi
  const char *sfVarName; // edi
  int v20; // edx
  int v21; // edx
  unsigned int sfBufferLength; // kr0C_4
  int v23; // ecx
  signed int *tildeSymbol; // eax
  unsigned int v25; // ecx
  int v26; // ecx
  unsigned int v27; // ecx
  signed int mfNameLength; // ecx
  int mfVarSymbol; // edi
  const char *mfVarName; // edi
  int v31; // edx
  int v32; // edx
  unsigned int mfBufferLength; // kr18_4
  int v34; // ecx
  signed int *lparenSymbol; // eax
  signed int *eofSymbol; // eax
  int stringSymbol; // eax
  unsigned int v38; // ecx
  signed int v39; // ecx
  signed int v40; // eax
  int v41; // ecx
  int v42; // ecx
  char *appended; // eax
  signed int *rparenSymbol; // eax
  signed int *orSymbol; // eax
  signed int *ampersandSymbol; // eax
  unsigned int v47; // ecx
  int v48; // ecx
  int scannedType; // [esp+0h] [ebp-1Ch] BYREF
  int i; // [esp+4h] [ebp-18h]

  if ( getenv("CLASH95_TRACE_PARSER_TOKEN") )
  {
    fprintf(
      stderr,
      "[parser] next-token lexer=%08x token=%08x caller=%p\n",
      readSource,
      theToken,
      __builtin_return_address(0));
    fflush(stderr);
  }
  *(_DWORD *)theToken = 103;
  *(_DWORD *)(theToken + 4) = 0;
  *(_DWORD *)(theToken + 8) = aUnknown;
  g_TokenCap = 0;
  g_TokenLen = 0;
  for ( i = Lexer_PeekChar(readSource, 0xDu);
        i == 32 || i == 10 || i == 12 || v4 == i || i == 59 || i == 9;
        i = Lexer_PeekChar(readSource, v4) )
  {
    if ( i == 59 )
    {
      for ( i = Lexer_PeekChar(readSource, v4); i != 10; i = Lexer_PeekChar(readSource, v4) )
      {
        if ( v4 == i )
          break;
        if ( i == -1 )
          break;
      }
    }
  }
  charType = IsTable[(unsigned __int8)(i + 1)];
  if ( (charType & 0xC0) != 0 )
  {
    firstChar = i;
    *(_DWORD *)theToken = 2;
    Lexer_SkipChar(firstChar, readSource, v4);
    v8 = readSource;
    count = 0;
LABEL_12:
    tokenSymbol = (signed int *)(uintptr_t)(unsigned int)(uintptr_t)Lexer_ReadToken(v8, count, &scannedType, v7);
    *(_DWORD *)(theToken + 4) = (int)(uintptr_t)tokenSymbol;
LABEL_13:
    printForm = tokenSymbol[4];
LABEL_14:
    *(_DWORD *)(theToken + 8) = printForm;
    goto LABEL_15;
  }
  if ( (charType & 0x20) != 0 )
    goto LABEL_37;
  if ( i >= 41 )
  {
    if ( i <= 41 )
    {
      *(_DWORD *)theToken = 101;
      rparenSymbol = Str_Intern(asc_504D38, v4);
      *(_DWORD *)(theToken + 8) = asc_504D38;
      *(_DWORD *)(theToken + 4) = rparenSymbol;
      goto LABEL_15;
    }
    if ( i >= 60 )
    {
      if ( i <= 60 )
      {
        *(_DWORD *)theToken = 2;
        appended = Str_AppendCharEscaping(
                     60,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        count = 1;
        g_TokenBuf = (int)appended;
        v8 = readSource;
        goto LABEL_12;
      }
      if ( i >= 124 )
      {
        if ( i <= 124 )
        {
          *(_DWORD *)theToken = 92;
          orSymbol = Str_Intern(asc_504D40, v4);
          *(_DWORD *)(theToken + 8) = asc_504D40;
          *(_DWORD *)(theToken + 4) = orSymbol;
          goto LABEL_15;
        }
        if ( i == 126 )
        {
          *(_DWORD *)theToken = 90;
          tildeSymbol = Str_Intern(asc_504D3C, v4);
          *(_DWORD *)(theToken + 8) = asc_504D3C;
          *(_DWORD *)(theToken + 4) = tildeSymbol;
          goto LABEL_15;
        }
      }
      else if ( i == 63 )
      {
        i = Lexer_PeekChar(readSource, v4);
        nextChar = i;
        if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
        {
          Lexer_SkipChar(i, readSource, i);
          *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v16);
          sfVarSymbol = *(_DWORD *)(theToken + 4);
          *(_DWORD *)theToken = 15;
          sfVarName = *(const char **)(sfVarSymbol + 16);
          if ( *sfVarName != 42
            || (sfNameLength = strlen(sfVarName), sfNameLength <= 1)
            || (v20 = *(_DWORD *)(theToken + 4),
                sfNameLength = strlen(*(const char **)(v20 + 16)),
                *(_BYTE *)(sfNameLength + *(_DWORD *)(v20 + 16) - 1) != 42) )
          {
            printForm = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(*(_DWORD *)(theToken + 4) + 16), sfNameLength);
            goto LABEL_14;
          }
          v21 = *(_DWORD *)(theToken + 4);
          *(_DWORD *)theToken = 13;
          *(_DWORD *)(theToken + 8) = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(v21 + 16), sfNameLength);
          sfBufferLength = strlen((const char *)g_TokenBuf) + 1;
          *(_BYTE *)(sfBufferLength - 1 + g_TokenBuf - 1) = 0;
          *(_DWORD *)(theToken + 4) = Str_Intern((char *)(g_TokenBuf + 1), sfBufferLength - 1);
          *(_BYTE *)(g_TokenBuf + v23 - 1) = i;
        }
        else
        {
          *(_DWORD *)theToken = 17;
          *(_DWORD *)(theToken + 4) = Str_Intern(aQuestion_LexerSingleFieldVarPrefix, nextChar);
          Lexer_SkipChar(v39, readSource, v39);
          *(_DWORD *)(theToken + 8) = aQuestion_LexerSingleFieldVarPrefix;
        }
        goto LABEL_15;
      }
      goto LABEL_30;
    }
    if ( i >= 45 )
    {
      if ( i > 46 )
        goto LABEL_30;
    }
    else if ( i != 43 )
    {
      goto LABEL_30;
    }
LABEL_37:
    Lexer_SkipChar(i, readSource, v4);
    Lexer_ScanNumberToken(readSource, (_DWORD *)theToken, v14);
    goto LABEL_15;
  }
  if ( i < 34 )
  {
    if ( i >= 0 )
    {
      if ( i > 0 && i != 3 )
        goto LABEL_30;
LABEL_66:
      *(_DWORD *)theToken = 102;
      eofSymbol = Str_Intern(aStop, v4);
      *(_DWORD *)(theToken + 8) = g_Lexer_EmptyQuotedStringBuffer;
      *(_DWORD *)(theToken + 4) = eofSymbol;
      goto LABEL_15;
    }
    if ( i == -1 )
      goto LABEL_66;
LABEL_30:
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) != 0 )
    {
      Lexer_SkipChar(i, readSource, v4);
      *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v47);
      *(_DWORD *)theToken = scannedType;
      tokenSymbol = (signed int *)(uintptr_t)(unsigned int)*(_DWORD *)(theToken + 4);
      goto LABEL_13;
    }
    *(_DWORD *)(theToken + 8) = aUnprintableCha;
    goto LABEL_15;
  }
  if ( i <= 34 )
  {
    *(_DWORD *)(theToken + 4) = Lexer_ReadQuotedString(readSource, v4);
    stringSymbol = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 3;
    printForm = Str_InternQuotedEscapedString(*(int **)(stringSymbol + 16), v38);
    goto LABEL_14;
  }
  if ( i >= 38 )
  {
    if ( i <= 38 )
    {
      *(_DWORD *)theToken = 91;
      ampersandSymbol = Str_Intern(asc_504D44, v4);
      *(_DWORD *)(theToken + 8) = asc_504D44;
      *(_DWORD *)(theToken + 4) = ampersandSymbol;
      goto LABEL_15;
    }
    if ( i == 40 )
    {
      *(_DWORD *)theToken = 100;
      lparenSymbol = Str_Intern(asc_504D34, v4);
      *(_DWORD *)(theToken + 8) = asc_504D34;
      *(_DWORD *)(theToken + 4) = lparenSymbol;
      goto LABEL_15;
    }
    goto LABEL_30;
  }
  if ( i != 36 )
    goto LABEL_30;
  i = Lexer_PeekChar(readSource, v4);
  if ( i != 63 )
  {
    *(_DWORD *)theToken = 2;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        36,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    Lexer_SkipChar(i, readSource, v42);
    count = 1;
    v8 = readSource;
    goto LABEL_12;
  }
  i = Lexer_PeekChar(readSource, v25);
  if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
  {
    Lexer_SkipChar(i, readSource, v26);
    *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v27);
    mfVarSymbol = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 16;
    mfVarName = *(const char **)(mfVarSymbol + 16);
    if ( *mfVarName != 42
      || (mfNameLength = strlen(mfVarName), mfNameLength <= 1)
      || (v31 = *(_DWORD *)(theToken + 4),
          mfNameLength = strlen(*(const char **)(v31 + 16)),
          *(_BYTE *)(mfNameLength + *(_DWORD *)(v31 + 16) - 1) != 42) )
    {
      printForm = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(*(_DWORD *)(theToken + 4) + 16), mfNameLength);
      goto LABEL_14;
    }
    v32 = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 14;
    *(_DWORD *)(theToken + 8) = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(v32 + 16), mfNameLength);
    mfBufferLength = strlen((const char *)g_TokenBuf) + 1;
    *(_BYTE *)(mfBufferLength - 1 + g_TokenBuf - 1) = 0;
    *(_DWORD *)(theToken + 4) = Str_Intern((char *)(g_TokenBuf + 1), mfBufferLength - 1);
    *(_BYTE *)(v34 + g_TokenBuf - 1) = i;
  }
  else
  {
    *(_DWORD *)theToken = 18;
    *(_DWORD *)(theToken + 4) = Str_Intern(aQuestion_LexerMultiFieldVarPrefix, v26);
    v40 = i;
    *(_DWORD *)(theToken + 8) = aQuestion_LexerMultiFieldVarPrefix;
    Lexer_SkipChar(v40, readSource, v41);
  }
LABEL_15:
  if ( *(_DWORD *)theToken == 8 )
  {
    IO_OutWriteToken(asc_504D70);
    IO_OutWriteToken(*(char **)(theToken + 8));
    printText = asc_504D74;
  }
  else
  {
    printText = *(char **)(theToken + 8);
  }
  result = IO_OutWriteToken(printText);
  if ( g_TokenBuf )
  {
    result = (char *)Mem_SmallBlockFree((_DWORD *)g_TokenBuf, g_TokenLen);
    g_TokenBuf = 0;
    g_TokenLen = 0;
    g_TokenCap = 0;
  }
  return result;
}
// 493549: simplified comparisons for '%var_18.4': <2E || ==2E became <2F
// 4932C2: variable 'v4' is possibly undefined
// 4932FD: variable 'v7' is possibly undefined
// 49341B: variable 'v14' is possibly undefined
// 493478: variable 'v16' is possibly undefined
// 49350D: variable 'v23' is possibly undefined
// 49358B: variable 'v25' is possibly undefined
// 4935BB: variable 'v26' is possibly undefined
// 4935C4: variable 'v27' is possibly undefined
// 49365D: variable 'v34' is possibly undefined
// 4936D2: variable 'v38' is possibly undefined
// 4936E7: variable 'v17' is possibly undefined
// 493708: variable 'v39' is possibly undefined
// 493724: variable 'v28' is possibly undefined
// 49374E: variable 'v41' is possibly undefined
// 49378B: variable 'v42' is possibly undefined
// 493846: variable 'v47' is possibly undefined
// 493875: variable 'v48' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00493890) --------------------------------------------------------
signed int * Lexer_ReadToken(
        int readSource,
        signed int count,
        _DWORD *type,
        unsigned int a4)
{
  int v6; // ecx
  unsigned int v7; // ecx
  int v8; // ecx
  signed int *result; // eax
  int i; // [esp+0h] [ebp-14h]

  for ( i = Lexer_PeekChar(readSource, a4); i != 60; i = Lexer_PeekChar(readSource, v7) )
  {
    if ( i == 34 )
      break;
    if ( i == 40 )
      break;
    if ( i == 41 )
      break;
    if ( i == 38 )
      break;
    if ( i == 124 )
      break;
    if ( i == 126 )
      break;
    if ( i == 32 )
      break;
    if ( i == 59 )
      break;
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) == 0 )
      break;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        i,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    ++count;
  }
  Lexer_SkipChar(i, readSource, v6);
  if ( count > 2 && *(_BYTE *)g_TokenBuf == 91 && *(_BYTE *)(count + g_TokenBuf - 1) == 93 )
  {
    *type = 8;
    *(_BYTE *)(count + g_TokenBuf - 1) = 0;
    result = Str_Intern((char *)(g_TokenBuf + 1), v8);
    *(_BYTE *)(g_TokenBuf + count - 1) = 93;
  }
  else
  {
    *type = 2;
    return Str_Intern((char *)g_TokenBuf, v8);
  }
  return result;
}
// 493922: variable 'v7' is possibly undefined
// 493938: variable 'v6' is possibly undefined
// 49397A: variable 'v8' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (004939B0) --------------------------------------------------------
signed int * Lexer_ReadQuotedString(int logicalName, unsigned int a2)
{
  char *appended; // edi
  int i; // eax
  unsigned int v6; // ecx
  unsigned int v7; // ecx
  int stringSymbol; // ecx
  int stringCapacity; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int stringLength[6]; // [esp+4h] [ebp-18h] BYREF

  stringLength[4] = a2;
  appended = 0;
  stringCapacity = 0;
  stringLength[0] = 0;
  for ( i = Lexer_PeekChar(logicalName, a2); i != 34; i = Lexer_PeekChar(logicalName, v7) )
  {
    if ( i == -1 )
      break;
    if ( i == 92 )
      i = Lexer_PeekChar(logicalName, v6);
    appended = Str_AppendCharEscaping(i, appended, stringLength, &stringCapacity, stringLength[0] + 80);
  }
  if ( i == -1 && !g_Lexer_SuppressEofError )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aEncounteredEnd, v6);
  if ( !appended )
    return Str_Intern(g_Lexer_EmptyQuotedStringBuffer, v6);
  Str_Intern(appended, v6);
  Mem_SmallBlockFree(appended, stringLength[0]);
  return (signed int *)stringSymbol;
}
// 4939DB: variable 'v6' is possibly undefined
// 4939FB: variable 'v7' is possibly undefined
// 493A51: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AA0C: using guessed type int dword_51AA0C;

//----- (00493A60) --------------------------------------------------------
int  Lexer_ScanNumberToken(int logicalName, _DWORD *theToken, unsigned int a3)
{
  int digitFound; // ebp
  char charType; // bl
  unsigned int bufferSize; // eax
  int v6; // ecx
  char *v7; // edx
  int count; // edi
  int phase; // esi
  char *appended; // eax
  unsigned int v11; // ecx
  char *digitBuffer; // eax
  int v13; // ecx
  int theLong; // eax
  signed int longValue; // ecx
  int v16; // ecx
  int *integerValue; // eax
  int v18; // edx
  int result; // eax
  int v20; // edx
  signed int symbolCount; // edi
  char *symbolBuffer; // eax
  unsigned int v23; // ecx
  signed int *scannedSymbol; // eax
  _DWORD *v25; // edx
  char lastChar; // al
  signed int *symbolValue; // eax
  int v28; // edx
  int doubleValue; // eax
  int v30; // edx
  int v31; // edx
  double theFloat; // [esp+0h] [ebp-44h]
  int scannedType; // [esp+8h] [ebp-3Ch] BYREF
  _DWORD *tokenOut; // [esp+Ch] [ebp-38h]
  int v35; // [esp+10h] [ebp-34h]
  int readSource; // [esp+14h] [ebp-30h]
  int processFloat; // [esp+18h] [ebp-2Ch]
  int nextCount; // [esp+1Ch] [ebp-28h]
  int inchar; // [esp+20h] [ebp-24h]
  unsigned __int8 v40; // [esp+24h] [ebp-20h]
  unsigned __int8 v41; // [esp+28h] [ebp-1Ch]
  unsigned __int8 v42; // [esp+2Ch] [ebp-18h]

  readSource = logicalName;
  tokenOut = theToken;
  inchar = Lexer_PeekChar(logicalName, a3);
  digitFound = 0;
  processFloat = 0;
  v35 = 1;
  charType = IsTable[(unsigned __int8)(inchar + 1)];
  bufferSize = g_TokenLen + 80;
  if ( (charType & 0x20) != 0 )
  {
    digitFound = 1;
    count = v35;
    v7 = (char *)g_TokenBuf;
    goto LABEL_5;
  }
  v6 = inchar;
  if ( inchar == 43 || inchar == 45 )
  {
    v7 = (char *)g_TokenBuf;
    bufferSize = g_TokenLen + 80;
    count = 1;
LABEL_5:
    phase = 0;
    appended = Str_AppendCharEscaping(inchar, v7, (unsigned int *)&g_TokenLen, &g_TokenCap, bufferSize);
    goto LABEL_6;
  }
  if ( inchar == 46 )
  {
    phase = 1;
    processFloat = 1;
    count = v35;
    appended = Str_AppendCharEscaping(46, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
    goto LABEL_6;
  }
  if ( inchar != 69 && inchar != 101 )
  {
    if ( inchar != 60
      && inchar != 34
      && inchar != 40
      && inchar != 41
      && inchar != 38
      && inchar != 124
      && inchar != 126
      && inchar != 32
      && inchar != 59
      && (charType & 8) != 0 )
    {
      symbolCount = v35;
      symbolBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
      goto LABEL_33;
    }
    goto LABEL_18;
  }
  processFloat = 1;
  phase = 2;
  count = 1;
  appended = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_6:
  for ( g_TokenBuf = (int)appended; ; g_TokenBuf = (int)digitBuffer )
  {
    inchar = Lexer_PeekChar(readSource, v11);
    v40 = inchar + 1;
    v42 = inchar + 1;
    v41 = inchar + 1;
    switch ( phase )
    {
      case 0:
        if ( (IsTable[v40] & 0x20) == 0 )
        {
          if ( inchar == 46 )
          {
            phase = 1;
            processFloat = 1;
            ++count;
            appended = Str_AppendCharEscaping(
                         46,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar == 69 || inchar == 101 )
          {
            phase = 2;
            processFloat = 1;
            ++count;
            appended = Str_AppendCharEscaping(
                         inchar,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
        goto LABEL_9;
      case 1:
        if ( (IsTable[v42] & 0x20) == 0 )
        {
          if ( inchar == 69 || inchar == 101 )
          {
            phase = 2;
            ++count;
            appended = Str_AppendCharEscaping(
                         inchar,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
LABEL_9:
        digitFound = 1;
        ++count;
        digitBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
        continue;
      case 2:
        if ( (IsTable[v41] & 0x20) == 0 && inchar != 43 && inchar != 45 )
        {
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
LABEL_68:
            symbolCount = count + 1;
            symbolBuffer = Str_AppendCharEscaping(
                    inchar,
                    (char *)g_TokenBuf,
                    (unsigned int *)&g_TokenLen,
                    &g_TokenCap,
                    g_TokenLen + 80);
            goto LABEL_33;
          }
          digitFound = 0;
LABEL_18:
          Lexer_SkipChar(inchar, readSource, v6);
          if ( digitFound )
          {
            if ( processFloat )
            {
              theFloat = strtod((const char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
              *tokenOut = 0;
              doubleValue = Rules_AddDoubleValue(theFloat);
              *(_DWORD *)((uintptr_t)tokenOut + 4) = doubleValue;
              result = Rules_FloatToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)doubleValue + 16), *(double *)((uintptr_t)(unsigned int)doubleValue + 16));
              *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
            }
            else
            {
              theLong = Str_ParseSignedInt((char *)g_TokenBuf);
              longValue = theLong;
              if ( theLong == 0x7FFFFFFF || theLong == 0x80000000 )
              {
                Rules_PrintWarningID((int)aScanner, 1, 0);
                Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aOverOrUnderflo, v16);
              }
              *tokenOut = 1;
              integerValue = Rules_AddIntegerValue(longValue);
              *(_DWORD *)((uintptr_t)tokenOut + 4) = integerValue;
              result = Rules_LongIntegerToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)integerValue + 16));
              *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
            }
          }
          else
          {
            *tokenOut = 2;
            symbolValue = Str_Intern((char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
            *(_DWORD *)((uintptr_t)tokenOut + 4) = symbolValue;
            result = *(_DWORD *)((uintptr_t)(unsigned int)symbolValue + 16);
            *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
          }
          return result;
        }
        phase = 3;
        ++count;
        appended = Str_AppendCharEscaping(
                     inchar,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        goto LABEL_6;
    }
    nextCount = count + 1;
    if ( (IsTable[v41] & 0x20) == 0 )
      break;
    count = nextCount;
    digitBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
  }
  v6 = inchar;
  if ( inchar == 60
    || inchar == 34
    || inchar == 40
    || inchar == 41
    || inchar == 38
    || inchar == 124
    || inchar == 126
    || inchar == 32
    || inchar == 59
    || (IsTable[v41] & 8) == 0 )
  {
    lastChar = *(_BYTE *)(g_TokenBuf + count - 1);
    if ( lastChar == 43 || lastChar == 45 )
      digitFound = 0;
    goto LABEL_18;
  }
  symbolCount = nextCount;
  symbolBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_33:
  g_TokenBuf = (int)symbolBuffer;
  scannedSymbol = Lexer_ReadToken(readSource, symbolCount, &scannedType, v23);
  v25 = tokenOut;
  tokenOut[1] = scannedSymbol;
  *v25 = scannedType;
  result = *(_DWORD *)(v25[1] + 16);
  v25[2] = result;
  return result;
}
// 493B07: conditional instruction was optimized away because esi.4<4u
// 493B10: conditional instruction was optimized away because esi.4<4u
// 493B19: conditional instruction was optimized away because esi.4<4u
// 493B6B: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493B70: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493FEC: conditional instruction was optimized away because esi.4==3
// 493AE9: variable 'v11' is possibly undefined
// 493C13: variable 'v6' is possibly undefined
// 493C5D: variable 'v16' is possibly undefined
// 493C72: variable 'v15' is possibly undefined
// 493C77: variable 'v18' is possibly undefined
// 493C82: variable 'v20' is possibly undefined
// 493D0C: variable 'v23' is possibly undefined
// 4940CB: variable 'v13' is possibly undefined
// 4940D0: variable 'v28' is possibly undefined
// 49410E: variable 'v30' is possibly undefined
// 494122: variable 'v31' is possibly undefined
// 4B6AC6: using guessed type double __fastcall strtod_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00494160) --------------------------------------------------------
signed int  Rules_ExpressionConstraintsCompatible(__int16 *theExpression)
{
  _BYTE *rv; // ebx
  _BYTE *implicit; // eax
  _DWORD *v3; // ecx
  char *v4; // edx
  _DWORD *intersection; // edx

  rv = Rules_BuildLHSNodeFromToken(theExpression);
  implicit = Rules_ApplyPatternKeywordFlags();
  Rules_IntersectConstraints((int)rv, (int)implicit);
  AST_DecrementNodeRefCount(rv);
  AST_DecrementNodeRefCount(v3);
  if ( Rules_ConstraintIsUnmatchable(v4) )
  {
    AST_DecrementNodeRefCount(intersection);
    return 1;
  }
  else
  {
    AST_DecrementNodeRefCount(intersection);
    return 0;
  }
}
// 494186: variable 'v3' is possibly undefined
// 49418D: variable 'v4' is possibly undefined
// 494198: variable 'v5' is possibly undefined

//----- (00494230) --------------------------------------------------------
signed int  Rules_TagIsConstantType(int theType)
{
  signed int result; // eax

  switch ( theType )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

//----- (00494250) --------------------------------------------------------
int  AST_NodeListsEqual(__int16 *firstList, __int16 *secondList)
{
  __int16 *i; // ecx
  int result; // eax
  int v5; // ecx

  for ( i = firstList; i; secondList = *(__int16 **)(secondList + 5) )
  {
    if ( !secondList )
      break;
    if ( *i != *secondList || *(_DWORD *)(i + 1) != *(_DWORD *)(secondList + 1) )
      return 0;
    result = AST_NodeListsEqual(*(_DWORD *)(i + 3), *(_DWORD *)(secondList + 3));
    if ( !result )
      return result;
    i = *(__int16 **)(v5 + 10);
  }
  return i == secondList;
}
// 49427F: variable 'v5' is possibly undefined

//----- (004942A0) --------------------------------------------------------
int  AST_CountListNodes(uintptr_t exprList)
{
  int i; // edx

  for ( i = 0; exprList; ++i )
    exprList = (uintptr_t)(unsigned int)*(_DWORD *)(exprList + 10);
  return i;
}

//----- (004942C0) --------------------------------------------------------
signed int  AST_CloneNodeList(signed int result)
{
  signed int lastCopy; // ebx
  signed int topLevel; // esi
  int v3; // ecx
  int v4; // ecx
  int i; // ecx
  int v6; // ecx
  signed int copiedArgList; // eax
  signed int newCopy; // edx
  int v9; // ecx

  if ( result )
  {
    lastCopy = AST_NewNode(*(_WORD *)result, *(_DWORD *)(result + 2));
    topLevel = lastCopy;
    *(_DWORD *)(lastCopy + 6) = AST_CloneNodeList(*(_DWORD *)(v3 + 6));
    for ( i = *(_DWORD *)(v4 + 10); i; lastCopy = newCopy )
    {
      AST_NewNode(*(_WORD *)i, *(_DWORD *)(i + 2));
      copiedArgList = AST_CloneNodeList(*(_DWORD *)(v6 + 6));
      *(_DWORD *)(newCopy + 6) = copiedArgList;
      *(_DWORD *)(lastCopy + 10) = newCopy;
      i = *(_DWORD *)(v9 + 10);
    }
    return topLevel;
  }
  return result;
}
// 4942DB: variable 'v3' is possibly undefined
// 4942E6: variable 'v4' is possibly undefined
// 4942FA: variable 'v6' is possibly undefined
// 494302: variable 'v8' is possibly undefined
// 494308: variable 'v9' is possibly undefined

//----- (00494330) --------------------------------------------------------
signed int  AST_TreeContainsSpecialTag(int theExpression, int globalsAreVariables)
{
  int exprPtr; // ecx
  __int16 nodeType; // dx

  exprPtr = theExpression;
  if ( !theExpression )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(exprPtr + 6) && AST_TreeContainsSpecialTag(*(_DWORD *)(exprPtr + 6), globalsAreVariables) )
        return 1;
      nodeType = *(_WORD *)exprPtr;
      if ( *(_WORD *)exprPtr == 16 || nodeType == 15 || nodeType == 6 )
        return 1;
      if ( nodeType != 13 && nodeType != 14 )
        break;
      if ( globalsAreVariables == 1 )
        return 1;
      exprPtr = *(_DWORD *)(exprPtr + 10);
      if ( !exprPtr )
        return 0;
    }
    exprPtr = *(_DWORD *)(exprPtr + 10);
  }
  while ( exprPtr );
  return 0;
}
// 494341: variable 'v2' is possibly undefined

//----- (004943A0) --------------------------------------------------------
int  AST_CountTreeNodes(int testPtr)
{
  int node; // edx
  int count; // ecx
  int child_node; // ebx

  node = testPtr;
  count = 0;
  if ( !testPtr )
    return count;
  while ( node )
  {
    ++count;
    child_node = *(_DWORD *)(node + 6);
    if ( child_node )
      count += AST_CountTreeNodes(child_node);
    node = *(_DWORD *)(node + 10);
  }
  return count;
}

