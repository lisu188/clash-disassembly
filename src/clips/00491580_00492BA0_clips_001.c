/* Generated from src/recovered/rules/clips/00491580_objects.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00491580) --------------------------------------------------------
_DWORD *Module_BeginEnum(void)
{
  _DWORD *freeListNode; // edx
  _DWORD *result; // eax

  freeListNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListNode;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = g_Module_ChangeNotifyEnabled;
  g_Module_ChangeNotifyEnabled = 0;
  result[1] = g_Clips_CurrentModule;
  result[2] = g_Module_SavedEnumStackTop;
  g_Module_SavedEnumStackTop = (int)(intptr_t)result;
  return result;
}
// 51A9A4: using guessed type int dword_51A9A4;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004915E0) --------------------------------------------------------
int Module_EndEnum(void)
{
  int *savedModule; // eax
  int result; // eax

  savedModule = (int *)(uintptr_t)g_Module_SavedEnumStackTop;
  g_Module_SavedEnumStackTop = *(_DWORD *)(uintptr_t)(g_Module_SavedEnumStackTop + 8);
  g_Module_ChangeNotifyEnabled = *savedModule;
  g_Clips_CurrentModule = savedModule[1];
  g_ClipsMemFreeListTemp = (int)(intptr_t)savedModule;
  *savedModule = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
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
  itemsArray = *(_DWORD *)(uintptr_t)(result + 8);
  if ( itemsArray )
    return *(_DWORD *)(uintptr_t)(itemsArray + 4 * moduleItemIndex);
  else
    return 0;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00491680) --------------------------------------------------------
int Module_CreateMainModule(void)
{
  int free_module; // edx
  int module; // ecx
  signed int *module_name; // eax
  int index; // esi
  int construct; // ecx
  int slot_offset; // edx
  int construct_data; // eax
  int (__fastcall *construct_initializer)(int, int); // eax

  free_module = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
  if ( free_module )
  {
    g_ClipsMemFreeListTemp = free_module;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *(_DWORD *)(uintptr_t)free_module;
    module = g_ClipsMemFreeListTemp;
  }
  else
  {
    module = Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  module_name = Str_Intern(aMain_1, module);
  *(_DWORD *)(uintptr_t)module = module_name;
  ++module_name[1];
  *(_DWORD *)(uintptr_t)(module + 28) = 0;
  *(_DWORD *)(uintptr_t)(module + 4) = 0;
  *(_DWORD *)(uintptr_t)(module + 12) = 0;
  *(_DWORD *)(uintptr_t)(module + 16) = 0;
  *(_DWORD *)(uintptr_t)(module + 24) = 0;
  if ( g_ClipsModuleItemCount )
  {
    *(_DWORD *)(uintptr_t)(module + 8) = Mem_SmallBlockAlloc(4 * g_ClipsModuleItemCount);
    index = 0;
    construct = g_ModuleItemDescriptorListHead;
    if ( g_ClipsModuleItemCount > 0 )
    {
      slot_offset = 0;
      do
      {
        if ( !construct )
          break;
        if ( *(_DWORD *)(uintptr_t)(construct + 8) )
        {
          construct_initializer = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(construct + 8);
          construct_data = construct_initializer(construct, slot_offset);
          *(_DWORD *)(uintptr_t)(slot_offset + *(_DWORD *)(uintptr_t)(module + 8)) = construct_data;
          construct_data = *(_DWORD *)(uintptr_t)(slot_offset + *(_DWORD *)(uintptr_t)(module + 8));
          *(_DWORD *)(uintptr_t)(construct_data + 4) = 0;
          *(_DWORD *)(uintptr_t)(construct_data + 8) = 0;
          *(_DWORD *)(uintptr_t)construct_data = module;
        }
        else
        {
          *(_DWORD *)(uintptr_t)(slot_offset + *(_DWORD *)(uintptr_t)(module + 8)) = 0;
        }
        slot_offset += 4;
        ++index;
        construct = *(_DWORD *)(uintptr_t)(construct + 28);
      }
      while ( index < g_ClipsModuleItemCount );
    }
  }
  else
  {
    *(_DWORD *)(uintptr_t)(module + 8) = 0;
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
    while ( *(_DWORD *)(uintptr_t)(g_ClipsDefmoduleListTail + 28) )
      g_ClipsDefmoduleListTail = *(_DWORD *)(uintptr_t)(g_ClipsDefmoduleListTail + 28);
  }
  return;
}
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;

//----- (004917C0) --------------------------------------------------------
int  Module_NextEnum(int defmodulePtr)
{
  if ( defmodulePtr )
    return *(_DWORD *)(uintptr_t)(defmodulePtr + 28);
  else
    return g_DefmoduleListHead;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004917D0) --------------------------------------------------------
int  Module_GetName(int theModule)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theModule + 16);
}

//----- (004917E0) --------------------------------------------------------
int  Module_GetPPForm(int theModule)
{
  return *(_DWORD *)(uintptr_t)(theModule + 4);
}

//----- (004917F0) --------------------------------------------------------
int Module_RemoveAllModules(void)
{
  int result; // eax
  int next_module; // edx

  if ( g_DefmoduleListHead )
  {
    do
    {
      next_module = *(_DWORD *)(uintptr_t)(g_DefmoduleListHead + 28);
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
    if ( *(_DWORD *)(uintptr_t)(module + 8) )
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
          if ( *(_DWORD *)(uintptr_t)(construct + 12) )
          {
            construct_data = *(_DWORD *)(uintptr_t)(slot_offset + *(_DWORD *)(uintptr_t)(module + 8));
            construct_cleanup = (void (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(construct + 12);
            construct_cleanup(construct_data);
          }
          slot_offset += 4;
          ++construct_index;
          construct = *(_DWORD *)(uintptr_t)(construct + 28);
        }
        while ( construct_index < g_ClipsModuleItemCount );
      }
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(module + 8), 4 * g_ClipsModuleItemCount);
    }
    Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)module, 0);
    node = *(_DWORD *)(uintptr_t)(module + 12);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(uintptr_t)(node + 12);
        if ( *(_DWORD *)(uintptr_t)node )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)node, 0);
        if ( *(_DWORD *)(uintptr_t)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(node + 4), 0);
        if ( *(_DWORD *)(uintptr_t)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(node + 8), 0);
        g_ClipsMemFreeListTemp = node;
        *(_DWORD *)(uintptr_t)node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        node = next_node;
      }
      while ( next_node );
    }
    node = *(_DWORD *)(uintptr_t)(module + 16);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(uintptr_t)(node + 12);
        if ( *(_DWORD *)(uintptr_t)node )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)node, 0);
        if ( *(_DWORD *)(uintptr_t)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(node + 4), 0);
        if ( *(_DWORD *)(uintptr_t)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(node + 8), 0);
        g_ClipsMemFreeListTemp = node;
        *(_DWORD *)(uintptr_t)node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        node = next_node;
      }
      while ( next_node );
    }
    module_name = *(_DWORD *)(uintptr_t)(module + 4);
    if ( module_name )
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)module_name, strlen((const char *)(uintptr_t)module_name) + 1);
    g_ClipsMemFreeListTemp = module;
    *(_DWORD *)(uintptr_t)module = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
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
    result = (int *)(uintptr_t)g_DefmoduleListHead;
    if ( g_DefmoduleListHead )
    {
      while ( nameSymbol != (int *)(uintptr_t)*result )
      {
        result = (int *)(uintptr_t)result[7];
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
    module_symbol = *(_DWORD *)(uintptr_t)module;
    module_name = module_symbol ? *(_DWORD *)(uintptr_t)(module_symbol + 16) : 0;
    if ( module_name && !strcmp_((int)(uintptr_t)defmoduleName, module_name) )
      return (int *)(uintptr_t)(unsigned int)module;
    module = *(_DWORD *)(uintptr_t)(module + 28);
  }
  return 0;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004919E0) --------------------------------------------------------
signed int *Module_GetCurrentCommand(void)
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  if ( g_Clips_CurrentModule )
    return Str_Intern(*(char **)(uintptr_t)(*(_DWORD *)(uintptr_t)g_Clips_CurrentModule + 16), v0);
  else
    return (signed int *)(uintptr_t)g_ClipsFalseSymbol;
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
    return (signed int *)(uintptr_t)g_ClipsFalseSymbol;
  defaultReturn = Str_Intern(*(char **)(uintptr_t)(*(_DWORD *)(uintptr_t)g_Clips_CurrentModule + 16), a1);
  if ( Lexer_TokenExpect(1) == -1 )
    return defaultReturn;
  if ( !Lexer_ParseValueList(1, argPtr, 2, a2) )
    return defaultReturn;
  theModule = Module_FindByName(*(_BYTE **)(uintptr_t)(argPtr[2] + 16));
  if ( theModule )
    Module_SetCurrent((int)(intptr_t)theModule);
  else
    Rules_ReportCantFindItem(v7, v6);
  return defaultReturn;
}
// 491A94: variable 'v7' is possibly undefined
// 491A94: variable 'v6' is possibly undefined
// 51A9B0: using guessed type int dword_51A9B0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00491AE0) --------------------------------------------------------
signed int Module_ReportIllegalSpecifierError(void)
{
  int v0; // ecx

  Rules_PrintErrorID((int)(intptr_t)aModuldef, 1, 1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalUseOfTh, v0);
}
// 491AFD: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00491B10) --------------------------------------------------------
signed int IO_RegisterStringRouter(void)
{
  return IO_AddRouter((int)(intptr_t)aString, 0, (int)(intptr_t)IO_StringRouterPrint, (int)(intptr_t)IO_StringRouterQuery, (int)(intptr_t)IO_StringRouterGetc, (int)(intptr_t)IO_StringRouterUngetc, 0);
}

//----- (00491B40) --------------------------------------------------------
signed int  IO_StringRouterQuery(int logicalName)
{
  int router_entry; // ecx

  router_entry = g_StringRouterListHead;
  while ( router_entry )
  {
    if ( !strcmp_(*(_DWORD *)(uintptr_t)router_entry, logicalName) )
      return 1;
    router_entry = *(_DWORD *)(uintptr_t)(router_entry + 20);
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

  stringRouter = (_DWORD *)(uintptr_t)IO_FindStringRouter(logicalName);
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

  stringRouter = (_DWORD *)(uintptr_t)IO_FindStringRouter(logicalName);
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
    result = *(unsigned __int8 *)(uintptr_t)(currentPosition + stringRouter[1]);
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
int __fastcall IO_StringRouterUngetc(int ch CLASH95_UNUSED, int logicalName)
{
  int stringRouter; // ecx
  int currentPosition; // ebx

  stringRouter = IO_FindStringRouter(logicalName);
  if ( !stringRouter )
  {
    Rules_ReportSystemError(0, 2);
    IO_RunRouterExitCallbacks();
  }
  if ( *(_DWORD *)(uintptr_t)(stringRouter + 16) )
    return 0;
  currentPosition = *(_DWORD *)(uintptr_t)(stringRouter + 8);
  if ( currentPosition > 0 )
    *(_DWORD *)(uintptr_t)(stringRouter + 8) = currentPosition - 1;
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

  routerName = (const char *)(uintptr_t)name;
  if ( IO_FindStringRouter(name) )
    return 0;
  newStringRouter = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 96);
  if ( newStringRouter )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *newStringRouter;
  }
  else
  {
    newStringRouter = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(routerName) + 1;
  newStringRouter[0] = (int)(intptr_t)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)(uintptr_t)newStringRouter[0], routerName, name_length);
  if ( str && maximumPosition > 0 )
  {
    payload_copy = (char *)(uintptr_t)Compat_AllocLow32Bytes(maximumPosition + 1);
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
  g_StringRouterListHead = (int)(intptr_t)newStringRouter;
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

  currentRouter = (_DWORD *)(uintptr_t)g_StringRouterListHead;
  previousRouter = 0;
  while ( currentRouter )
  {
    if ( !strcmp_(currentRouter[0], name) )
      break;
    previousRouter = currentRouter;
    currentRouter = (_DWORD *)(uintptr_t)currentRouter[5];
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
  key_length = strlen((const char *)(uintptr_t)currentRouter[0]) + 1;
  Mem_SmallBlockFree((_DWORD *)(uintptr_t)currentRouter[0], key_length);
  g_ClipsMemFreeListTemp = (int)(intptr_t)currentRouter;
  currentRouter[0] = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
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

  routerName = (const char *)(uintptr_t)name;
  if ( IO_FindStringRouter(name) )
    return 0;
  newStringRouter = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 96);
  if ( newStringRouter )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *newStringRouter;
  }
  else
  {
    newStringRouter = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(routerName) + 1;
  newStringRouter[0] = (int)(intptr_t)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)(uintptr_t)newStringRouter[0], routerName, name_length);
  newStringRouter[2] = 0;
  newStringRouter[4] = 1;
  newStringRouter[1] = (int)(intptr_t)str;
  newStringRouter[3] = maximumPosition;
  newStringRouter[5] = g_StringRouterListHead;
  g_StringRouterListHead = (int)(intptr_t)newStringRouter;
  return 1;
}
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491F30) --------------------------------------------------------
int  IO_FindStringRouter(int name)
{
  _DWORD *currentRouter; // ecx

  currentRouter = (_DWORD *)(uintptr_t)g_StringRouterListHead;
  while ( currentRouter )
  {
    if ( !strcmp_(currentRouter[0], name) )
      return (int)(intptr_t)currentRouter;
    currentRouter = (_DWORD *)(uintptr_t)currentRouter[5];
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;

//----- (00491F60) --------------------------------------------------------
int  Rules_ParseAssertCommand(int logicalName, _DWORD *theToken, int atLeastOne, int *error, int readFirstParen, int a6 CLASH95_UNUSED)
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
    nextOne = Rules_ParseAssertRHSPattern(logicalName, (int)(intptr_t)theToken, 0, error, readParenFlag, 1, 101);
    if ( !nextOne )
      break;
    AST_Append(nextOne, v9);
    Symbol = Rules_MakeSymbol(aAssert_1);
    stub = AST_NewNode(10, (int)(intptr_t)Symbol);
    *(_DWORD *)(uintptr_t)(stub + 6) = v13;
    v14 = stub;
    if ( lastOne )
      *(_DWORD *)(uintptr_t)(lastOne + 10) = stub;
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
    if ( *(_DWORD *)(uintptr_t)(assertList + 10) )
    {
      prognSymbol = Rules_MakeSymbol(aProgn_3);
      assertList = AST_NewNode(10, (int)(intptr_t)prognSymbol);
      *(_DWORD *)(uintptr_t)(assertList + 6) = v17;
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
  int v11 CLASH95_UNUSED; // ecx
  int v12 CLASH95_UNUSED; // ecx
  int v13 CLASH95_UNUSED; // ecx
  int v14 CLASH95_UNUSED; // ecx
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
    tokenType = *(_DWORD *)(uintptr_t)theToken;
    if ( *(_DWORD *)(uintptr_t)theToken == endType )
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
    Rules_PrintReservedSymbolErrorMessage((int)(uintptr_t)templateNameString, (int)(intptr_t)aARelationName);
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
    Rules_ReportAmbiguousReferenceError((int)(intptr_t)aDeftemplate, (int)(uintptr_t)templateNameString);
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
      Lexer_WarnImpliedTemplate((int)(intptr_t)aImpliedDeftemp, (int)(uintptr_t)templateNameString, 0);
      *error = 1;
      return 0;
    }
    theDeftemplate = Rules_CreateDeftemplateRecord(templateName, 1);
  }
  if ( (*(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1) != 0 )
  {
    firstOne = AST_NewNode(35, theDeftemplate);
    while ( 1 )
    {
      IO_OutWriteToken(asc_504C2C);
      nextOne = Rules_ParseAssertArgument(logicalName, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, endType, constantsOnlyFlag, &printError);
      if ( !nextOne )
        break;
      if ( argHead )
        *(_DWORD *)(uintptr_t)(lastOne + 10) = nextOne;
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
      IO_OutWriteToken(*(char **)(uintptr_t)(theToken + 8));
      bitmapValue = Rules_AddBitmapValue(g_Rules_DefaultZeroBitmapValue, v24);
      multifieldExpr = AST_NewNode(34, bitmapValue);
      *(_DWORD *)(uintptr_t)(firstOne + 10) = multifieldExpr;
      *(_DWORD *)(uintptr_t)(multifieldExpr + 6) = argHead;
      return firstOne;
    }
  }
  else
  {
    deftemplateExpr = AST_NewNode(35, theDeftemplate);
    returnExpr = deftemplateExpr;
    templateArgs = Rules_ParseAssertTemplate(logicalName, theToken, endType, error, v21, theDeftemplate);
    v23 = deftemplateExpr;
    *(_DWORD *)(uintptr_t)(deftemplateExpr + 10) = templateArgs;
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
  Parser_NextToken(logicalName, (int)(intptr_t)theToken);
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
  int v6 CLASH95_UNUSED; // ecx
  int v7 CLASH95_UNUSED; // ecx
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
  IO_OpenStringSource((int)(intptr_t)aAssert_str, theString, 0);
  assertArgs = Rules_ParseAssertRHSPattern((int)(intptr_t)aAssert_str, token_buffer_ptr, 0, error, 1, 1, 101);
  IO_CloseStringRouter((int)(intptr_t)aAssert_str);
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
      i = *(_DWORD *)(uintptr_t)(i + 10);
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
        Parser_ParseForm(currentArg, (_DWORD *)&parsed, (int)(intptr_t)currentArg, a3);
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
signed int Rules_ReportNoTemplateError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aFactrhs, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTemplate, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDoesNotExistFo, v2);
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
  returnValue = Str_Intern(v8, (int)(intptr_t)v8);
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
    return (int)(intptr_t)theName;
  module_symbol = Rules_ExtractModuleName(qualifier_length);
  if ( !module_symbol )
    return 0;
  module_record = Module_FindByName((_BYTE *)(uintptr_t)module_symbol[4]);
  if ( !module_record )
    return 0;
  Module_SetCurrent((int)(intptr_t)module_record);
  local_symbol = Rules_ExtractConstructName(qualifier_length, (char *)theName, (int)(intptr_t)theName);
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
  construct_record = Module_FindItemByName((int)(intptr_t)constructName);
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

  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAmbiguousRefer, constructName);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v3, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504CA8, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], findName, v5);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a_ItIsImportedF, v6);
}
// 4927FC: variable 'v3' is possibly undefined
// 49280B: variable 'v4' is possibly undefined
// 492817: variable 'v5' is possibly undefined
// 492826: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00492830) --------------------------------------------------------
int Rules_ClearModuleSearchMarkers(void)
{
  int result; // eax

  if ( !g_Clips_CurrentModule )
  {
    result = Module_NextEnum(0);
    if ( !result )
      return 0;
    Module_SetCurrent(result);
  }
  *(_DWORD *)(uintptr_t)(g_Clips_CurrentModule + 20) = 0;
  for ( result = Module_NextEnum(0); result; result = Module_NextEnum(result) )
    *(_DWORD *)(uintptr_t)(result + 20) = 0;
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
      Output_Write(logicalName, (int)(intptr_t)asc_504CDC, v14);
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
            Output_Write(logicalName, (int)(intptr_t)asc_504CE0, i);
          printFunction(i, i);
          goto LABEL_14;
        }
        constructName = nameFunction();
        if ( constructName )
        {
          if ( allModules )
            Output_Write(logicalName, (int)(intptr_t)asc_504CE0, v17);
          Output_Write(logicalName, constructName, v17);
LABEL_14:
          Output_Write(logicalName, (int)(intptr_t)asc_504CE4, v19);
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
int Rules_RegisterDeftemplateConstruct(void)
{
  int v0; // edx
  int v1; // ecx

  Rules_InitFacts();
  Rules_InitDeftemplateHashTable();
  Rules_RegisterDeftemplateFunctions(v1, v0);
  Rules_RegisterModifyDuplicateFunctions();
  g_DeftemplateConstructType = (int)(intptr_t)Rules_RegisterConstructType(
                        (int)(intptr_t)aDeftemplate_1,
                        (int)(intptr_t)aDeftemplates,
                        (int)(intptr_t)Rules_FindDeftemplateByName,
                        (int)(intptr_t)Rules_ParseDeftemplate,
                        (int)(intptr_t)Rules_GetConstructNameSymbol,
                        (int)(intptr_t)Rules_GetModuleConstructListHead,
                        (int)(intptr_t)Rules_GetConstructOwnerModule,
                        (int)(intptr_t)Rules_GetNextDeftemplate,
                        (int)(intptr_t)Rules_SetConstructNextInModule,
                        (int)(intptr_t)Rules_DeftemplateIsDeletable,
                        (int)(intptr_t)Rules_DeleteDeftemplate,
                        (int)(intptr_t)Rules_FreeDeftemplateRecord);
  return Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_Deftemplate, 35);
}
// 492B3D: variable 'v1' is possibly undefined
// 492B3D: variable 'v0' is possibly undefined
// 54E650: using guessed type int dword_54E650;

//----- (00492BA0) --------------------------------------------------------
int *Rules_InitDeftemplateHashTable(void)
{
  g_ClipsDeftemplateModuleItemId = Module_RegisterItem(
                   (int)(intptr_t)aDeftemplate_1,
                   (int)(intptr_t)Rules_AllocDeftemplateHashNode,
                   (int)(intptr_t)Rules_DeftemplateGetBloadedModuleItem,
                   (int)(intptr_t)Rules_FreeDeftemplateHashNode,
                   (int)(intptr_t)Rules_DeftemplateWriteModuleHeaderRef,
                   (int)(intptr_t)Rules_FindDeftemplateByName);
  return Module_RegisterImportExportConstructType((int)(intptr_t)aDeftemplate_1, 2);
}
// 54E654: using guessed type int dword_54E654;
