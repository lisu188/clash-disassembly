/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004B00A0) --------------------------------------------------------
_DWORD * MessageHandler_CallHandlers(_DWORD *result, double a2)
{
  _DWORD *returnBuffer; // ebp
  int savedHandlerCore; // esi
  int savedCursor; // edi
  int *handlerLink; // eax
  int handlerType; // edx
  int *afterLink; // edx
  _DWORD tempResult[12]; // [esp+0h] [ebp-30h] BYREF

  returnBuffer = result;
  if ( !g_ClipsHaltExecution )
  {
    savedHandlerCore = g_ClipsCurrentHandlerCore;
    savedCursor = g_ClipsMessageHandlerCursor;
    while ( 1 )
    {
      handlerLink = (int *)(uintptr_t)g_ClipsMessageHandlerCursor;
      handlerType = **(_DWORD **)(uintptr_t)g_ClipsMessageHandlerCursor & 6;
      if ( handlerType != 2 )
        break;
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(uintptr_t)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)(uintptr_t)*handlerLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], handlerLink, (int)(intptr_t)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 28),
          tempResult,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      if ( (**(_BYTE **)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_50954C);
      result = 0;
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor || g_ClipsHaltExecution )
        goto LABEL_14;
    }
    if ( handlerType == 4 )
    {
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(uintptr_t)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)(uintptr_t)*handlerLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], handlerLink, (int)(intptr_t)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 28),
          returnBuffer,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      result = *(_DWORD **)(uintptr_t)g_ClipsCurrentHandlerCore;
      if ( (**(_BYTE **)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        result = (_DWORD *)(uintptr_t)MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_50954C);
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor || g_ClipsHaltExecution )
        goto LABEL_14;
      while ( (**(_DWORD **)(uintptr_t)g_ClipsMessageHandlerCursor & 6) == 4 )
      {
        result = *(_DWORD **)(uintptr_t)(g_ClipsMessageHandlerCursor + 4);
        g_ClipsMessageHandlerCursor = (int)(intptr_t)result;
        if ( !result )
          goto LABEL_14;
      }
    }
    do
    {
      afterLink = (int *)(uintptr_t)g_ClipsMessageHandlerCursor;
      result = (_DWORD *)(uintptr_t)(**(_DWORD **)(uintptr_t)g_ClipsMessageHandlerCursor & 6);
      if ( result != (_DWORD *)6 )
        break;
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(uintptr_t)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)(uintptr_t)*afterLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], afterLink, (int)(intptr_t)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 28),
          tempResult,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      if ( (**(_BYTE **)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_50954C);
      result = (_DWORD *)(uintptr_t)g_ClipsMessageHandlerCursor;
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor )
        break;
    }
    while ( !g_ClipsHaltExecution );
LABEL_14:
    g_ClipsMessageHandlerCursor = savedCursor;
    g_ClipsCurrentHandlerCore = savedHandlerCore;
  }
  return result;
}
// 51A618: using guessed type char *off_51A618[4];
// 51A968: using guessed type int dword_51A968;
// 51ACC0: using guessed type int dword_51ACC0;
// 51AD58: using guessed type int dword_51AD58;
// 51AD60: using guessed type int dword_51AD60;

//----- (004B02F0) --------------------------------------------------------
signed int  MessageHandler_ReportStaticSlotAccessError(int theInstance, int slotClass, int slotIndex)
{
  int slotDesc; // edi
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  slotDesc = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotClass + 56) + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotClass + 60) + 4 * slotIndex) - 4);
  Rules_PrintErrorID((int)(intptr_t)aMsgpass, 3, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aStaticReferenc, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 12) + 16), v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOfClass_2, v7);
  Class_PrintName(v8, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDoesNotApplyTo, v9);
  return Instance_PrintNameOfClass((int)(intptr_t)g_IO_LogicalNameTable_WError[0], theInstance, 1);
}
// 4B031F: variable 'v5' is possibly undefined
// 4B0332: variable 'v6' is possibly undefined
// 4B0343: variable 'v7' is possibly undefined
// 4B034F: variable 'v8' is possibly undefined
// 4B0363: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B0380) --------------------------------------------------------
int Class_LookupCurrentScopedName(void)
{
  _BYTE *v0; // edx
  _BYTE *className; // eax
  int *nameSymbol; // ebx
  int v3; // edx
  int result; // eax
  int v5; // ecx

  Module_BeginEnum();
  className = (_BYTE *)(uintptr_t)Rules_ExtractModuleAndConstructName(v0);
  nameSymbol = Rules_FindSymbolEntry(className);
  Module_GetCurrent();
  Module_EndEnum();
  if ( !v3 )
    return 0;
  result = *(_DWORD *)(uintptr_t)(4 * Class_HashClassName(v3) + g_DefclassHashTable);
  if ( !result )
    return 0;
  while ( nameSymbol != *(int **)(uintptr_t)result || (*(_BYTE *)(uintptr_t)(result + 20) & 2) == 0 && v5 != **(_DWORD **)(uintptr_t)(result + 8) )
  {
    result = *(_DWORD *)(uintptr_t)(result + 100);
    if ( !result )
      return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(result + 20) & 1) == 0 )
    return 0;
  return result;
}
// 4B038C: variable 'v0' is possibly undefined
// 4B03A8: variable 'v3' is possibly undefined
// 4B03E3: variable 'v5' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0400) --------------------------------------------------------
int * Class_LookupByQualifiedName(_BYTE *qualifiedName)
{
  _BYTE *v1; // ecx
  _BYTE *v2; // ecx
  int theModule; // ebx
  _BYTE *v4; // edx
  int *result; // eax
  int v6; // ecx

  if ( !Rules_FindModuleSeparator(qualifiedName) )
    return Class_LookupInScope(v1);
  Module_BeginEnum();
  Rules_ExtractModuleAndConstructName(v2);
  theModule = Module_GetCurrent();
  Module_EndEnum();
  if ( !v4 )
    return 0;
  result = Rules_FindSymbolEntry(v4);
  if ( result )
  {
    result = *(int **)(uintptr_t)(g_DefclassHashTable + 4 * Class_HashClassName((int)(intptr_t)result));
    if ( !result )
      return 0;
    while ( v6 != *result || theModule != *(_DWORD *)(uintptr_t)result[2] )
    {
      result = (int *)(uintptr_t)result[25];
      if ( !result )
        return 0;
    }
    if ( (result[5] & 1) == 0 )
      return 0;
  }
  return result;
}
// 4B0415: variable 'v2' is possibly undefined
// 4B042A: variable 'v4' is possibly undefined
// 4B0434: variable 'v1' is possibly undefined
// 4B045E: variable 'v6' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0480) --------------------------------------------------------
int * Class_LookupInScope(_BYTE *className)
{
  int symbol; // ebx
  int class_record; // ecx
  int bucket_index; // eax

  symbol = (int)(uintptr_t)Rules_FindSymbolEntry(className);
  if ( !symbol )
    return 0;
  bucket_index = Class_HashClassName(symbol);
  class_record = *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * bucket_index);
  while ( class_record )
  {
    if ( symbol == *(_DWORD *)(uintptr_t)class_record && Class_IsInScope(class_record, 0) )
    {
      if ( (*(_BYTE *)(uintptr_t)(class_record + 20) & 1) != 0 )
        return (int *)(uintptr_t)(unsigned int)class_record;
      return 0;
    }
    class_record = *(_DWORD *)(uintptr_t)(class_record + 100);
  }
  return 0;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B04D0) --------------------------------------------------------
int *__fastcall Class_LookupByModule(int a1 CLASH95_UNUSED, _BYTE *className)
{
  int *result; // eax
  int *nameSymbol; // ebx
  int v4; // ecx

  result = Rules_FindSymbolEntry(className);
  nameSymbol = result;
  if ( result )
  {
    result = *(int **)(uintptr_t)(4 * Class_HashClassName((int)(intptr_t)result) + g_DefclassHashTable);
    if ( !result )
      return 0;
    while ( nameSymbol != (int *)(uintptr_t)*result || v4 && v4 != *(_DWORD *)(uintptr_t)result[2] )
    {
      result = (int *)(uintptr_t)result[25];
      if ( !result )
        return 0;
    }
    if ( (result[5] & 1) == 0 )
      return 0;
  }
  return result;
}
// 4B0502: variable 'v4' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0520) --------------------------------------------------------
BOOL  Class_IsInScope(int theDefclass, int theModule)
{
  int scopeMap; // ebx

  scopeMap = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theDefclass + 104) + 16);
  if ( !theModule )
    theModule = Module_GetCurrent();
  return (unsigned __int8)((1 << (*(_DWORD *)(uintptr_t)(theModule + 24) % 8)) & *(_BYTE *)(uintptr_t)(scopeMap
                                                                        + ((*(_DWORD *)(uintptr_t)(theModule + 24)
                                                                          - (__CFSHL__(*(int *)(uintptr_t)(theModule + 24) >> 31, 3)
                                                                           + 8 * (*(int *)(uintptr_t)(theModule + 24) >> 31))) >> 3))) != 0;
}

//----- (004B0580) --------------------------------------------------------
int  Class_GetNextRecord(int defclassPtr)
{
  return Class_Enum(defclassPtr, g_CLIPS_DefclassModuleItemIndex);
}
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004B0590) --------------------------------------------------------
BOOL Class_IsDeletable(void)
{
  int v0; // edx

  return !Rules_IsBloaded() && (*(_BYTE *)(uintptr_t)(v0 + 20) & 2) == 0 && Class_HierarchyHasInstances(v0) == 0;
}
// 4B059C: variable 'v0' is possibly undefined

//----- (004B05C0) --------------------------------------------------------
int __thiscall Class_UndefineCommand(void *this)
{
  return Rules_UndefconstructCommand((int)(intptr_t)this, g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B05E0) --------------------------------------------------------
signed int Class_IsDeletableAlt(void)
{
  int v0; // edx

  if ( Rules_IsBloaded() )
    return 0;
  if ( v0 )
    return Class_DeleteRecursive(v0);
  return Class_RemoveAllDeletableClasses();
}
// 4B05EE: variable 'v0' is possibly undefined

//----- (004B0610) --------------------------------------------------------
int __thiscall Class_PrettyPrintCommand(void *this)
{
  return Rules_PPConstructCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0630) --------------------------------------------------------
int  Class_ListConstructsCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefclassConstructType, a1, a2);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0670) --------------------------------------------------------
int  Class_GetWatchInstances(int theClass)
{
  return *(_DWORD *)(uintptr_t)(theClass + 20) << 27 >> 31;
}

//----- (004B0680) --------------------------------------------------------
int  Class_SetWatchInstances(int result, int theClass)
{
  char classFlags; // bl

  classFlags = *(_BYTE *)(uintptr_t)(theClass + 20);
  if ( (classFlags & 4) == 0 )
  {
    *(_BYTE *)(uintptr_t)(theClass + 20) = classFlags & 0xEF;
    result = 16 * (result & 1);
    *(_DWORD *)(uintptr_t)(theClass + 20) |= result;
  }
  return result;
}

//----- (004B06A0) --------------------------------------------------------
int  Class_GetWatchSlots(int theClass)
{
  return *(_DWORD *)(uintptr_t)(theClass + 20) << 26 >> 31;
}

//----- (004B06B0) --------------------------------------------------------
int  Class_SetWatchSlots(char newState, int theClass)
{
  int result; // eax

  *(_BYTE *)(uintptr_t)(theClass + 20) &= ~0x20u;
  result = 32 * (newState & 1);
  *(_DWORD *)(uintptr_t)(theClass + 20) |= result;
  return result;
}

//----- (004B06D0) --------------------------------------------------------
signed int  Class_SetWatchFlagCommand(int watchCode, int newState, int argExprs, double a4)
{
  if ( watchCode )
    return Rules_ApplyWatchFlagCommand(g_ClipsDefclassConstructType, newState, (int)(intptr_t)Class_GetWatchSlots, argExprs, a4, (void (*)(void))Class_SetWatchSlots);
  else
    return Rules_ApplyWatchFlagCommand(g_ClipsDefclassConstructType, newState, (int)(intptr_t)Class_GetWatchInstances, argExprs, a4, (void (*)(void))Class_SetWatchInstances);
}
// 4B0670: using guessed type int sub_4B0670();
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0710) --------------------------------------------------------
signed int  Class_SetWatchFlagForModuleCommand(int logicalName, int watchCode, int argExprs, double a4)
{
  if ( watchCode )
    return Rules_ListWatchFlagStatus(g_ClipsDefclassConstructType, logicalName, (int)(intptr_t)Class_GetWatchSlots, argExprs, a4, (void (*)(void))Class_SetWatchSlots);
  else
    return Rules_ListWatchFlagStatus(g_ClipsDefclassConstructType, logicalName, (int)(intptr_t)Class_GetWatchInstances, argExprs, a4, (void (*)(void))Class_SetWatchInstances);
}
// 4B0670: using guessed type int sub_4B0670();
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0750) --------------------------------------------------------
_DWORD * Class_GetConstructListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefclassConstructType, a2);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0790) --------------------------------------------------------
signed int  Class_HasSuperclass(int theClass, int superclass)
{
  unsigned int classIndex; // edx
  int listOffset; // eax

  classIndex = 1;
  listOffset = 4;
  while ( classIndex < *(unsigned __int16 *)(uintptr_t)(theClass + 46) )
  {
    if ( superclass == *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 48) + listOffset) )
      return 1;
    listOffset += 4;
    ++classIndex;
  }
  return 0;
}

//----- (004B07D0) --------------------------------------------------------
signed int  Class_ParseClassReference(int **classOut, int a2, double a3)
{
  signed int result; // eax
  int *classPtr; // eax
  int v6; // ecx
  _DWORD argBuffer[2]; // [esp-8h] [ebp-28h] BYREF
  int argValue; // [esp+0h] [ebp-20h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]

  v9 = a2;
  result = Lexer_ParseValueList(1, argBuffer, 2, a3);
  if ( result )
  {
    classPtr = Class_LookupByQualifiedName(*(_BYTE **)(uintptr_t)(argValue + 16));
    *classOut = classPtr;
    if ( classPtr )
    {
      result = Lexer_ParseValueList(2, argBuffer, 2, a3);
      if ( result )
        return argValue;
    }
    else
    {
      Class_ReportLookupError(v6, *(_DWORD *)(uintptr_t)(argValue + 16));
      return 0;
    }
  }
  return result;
}
// 4B082F: variable 'v6' is possibly undefined

//----- (004B0850) --------------------------------------------------------
signed int Class_ListAllConstructs(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Class_PrintModuleList, 0);
}
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004B0870) --------------------------------------------------------
char * Class_PrintModuleList(int a1)
{
  char *result; // eax
  signed int v3; // ecx
  signed int v4; // edx
  signed int v5; // esi
  int v6; // ecx
  int i; // ecx
  char *ppForm; // eax
  int v9; // ecx
  int v10; // ecx

  result = (char *)(uintptr_t)Rules_GetModuleConstructListHead(a1);
  v5 = v4;
  if ( result )
  {
    Output_WriteLongString(v3, result);
    Output_Write(v6, (int)(intptr_t)asc_509610, v6);
    result = (char *)(uintptr_t)MessageHandler_EnumNext(a1, 0);
    for ( i = (int)(intptr_t)result; result; i = (int)(intptr_t)result )
    {
      ppForm = (char *)(uintptr_t)MessageHandler_GetRecordPPForm(a1, i);
      if ( ppForm )
      {
        Output_WriteLongString(v5, ppForm);
        Output_Write(v5, (int)(intptr_t)asc_509610, v10);
      }
      result = (char *)(uintptr_t)MessageHandler_EnumNext(a1, v9);
    }
  }
  return result;
}
// 4B087C: variable 'v4' is possibly undefined
// 4B088A: variable 'v3' is possibly undefined
// 4B0896: variable 'v6' is possibly undefined
// 4B08C7: variable 'v10' is possibly undefined
// 4B08D0: variable 'v9' is possibly undefined

//----- (004B08E0) --------------------------------------------------------
int  Class_AddBusyReference(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 26);
  return result;
}

//----- (004B08F0) --------------------------------------------------------
int  Class_ReleaseBusyReference(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(uintptr_t)(result + 26);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004B0900) --------------------------------------------------------
BOOL  Class_PrepareUndefineCheck(double a1)
{
  int v1; // edx

  Instance_PrintClassInstanceSummary(a1);
  if ( !g_ClipsCurrentEvaluationDepth )
    g_ClipsCurrentEvaluationDepth = -1;
  Instance_PurgeDeletedInstances();
  g_ClipsCurrentEvaluationDepth = v1;
  return g_Clips_InstanceListHead == 0;
}
// 4B0926: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004B0940) --------------------------------------------------------
int Class_InitHashTables(void)
{
  int i; // eax
  int result; // eax

  g_DefclassHashTable = (int)(intptr_t)Mem_SmallBlockAlloc(0x29Cu);
  for ( i = 0; i != 668; i += 4 )
    *(_DWORD *)(uintptr_t)(g_DefclassHashTable + i) = 0;
  g_Defclass_SlotNameHashTablePtr = (int)(intptr_t)Mem_SmallBlockAlloc(0x29Cu);
  for ( result = 0; result != 668; result += 4 )
    *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + result) = 0;
  return result;
}
// 51AD68: using guessed type int dword_51AD68;
// 51AD70: using guessed type int dword_51AD70;

//----- (004B09B0) --------------------------------------------------------
int  Class_FindSlotBySymbol(int theClass, int slotName)
{
  int slotIndex; // edx
  int result; // eax

  slotIndex = 0;
  if ( !*(_DWORD *)(uintptr_t)(theClass + 64) )
    return 0;
  for ( result = *(_DWORD *)(uintptr_t)(theClass + 52); slotName != *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 8) + 12); result += 44 )
  {
    if ( (unsigned int)++slotIndex >= *(_DWORD *)(uintptr_t)(theClass + 64) )
      return 0;
  }
  return result;
}

//----- (004B09E0) --------------------------------------------------------
int __fastcall Class_ReportLookupError(int a1 CLASH95_UNUSED, int className)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aClassfun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFindCl, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], className, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction_1, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v6, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__21, v7);
  return Lexer_ErrorRecover(1);
}
// 4B0A02: variable 'v3' is possibly undefined
// 4B0A0E: variable 'v4' is possibly undefined
// 4B0A1D: variable 'v5' is possibly undefined
// 4B0A29: variable 'v6' is possibly undefined
// 4B0A38: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B0A50) --------------------------------------------------------
_DWORD * Mem_ReturnListToFreePool(_DWORD *result)
{
  _DWORD *i; // edx

  for ( i = result; result; i = result )
  {
    result = (_DWORD *)(uintptr_t)result[1];
    g_ClipsMemFreeListTemp = (int)(intptr_t)i;
    *i = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0AA0) --------------------------------------------------------
signed int  Class_PrintName(int theDefclass, int linefeedFlag)
{
  int currentModule; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int Name; // eax
  int v7; // ecx
  int v8; // ecx
  signed int result; // eax
  int v10; // ecx

  currentModule = Module_GetCurrent();
  if ( currentModule != *v5 && (*(_BYTE *)(uintptr_t)(theDefclass + 20) & 2) == 0 )
  {
    Name = Module_GetName(**(_DWORD **)(uintptr_t)(theDefclass + 8));
    Output_Write(v7, Name, v7);
    Output_Write(v8, (int)(intptr_t)asc_50964C, v8);
  }
  result = Output_Write(v4, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theDefclass + 16), v4);
  if ( linefeedFlag )
    return Output_Write(v10, (int)(intptr_t)asc_509650, v10);
  return result;
}
// 4B0AAE: variable 'v5' is possibly undefined
// 4B0AC6: variable 'v7' is possibly undefined
// 4B0AD2: variable 'v8' is possibly undefined
// 4B0ADE: variable 'v4' is possibly undefined
// 4B0AF1: variable 'v10' is possibly undefined

//----- (004B0B00) --------------------------------------------------------
signed int  Class_PrintNameList(int logicalName, int headerString, unsigned __int16 *classList)
{
  int v3; // ecx
  unsigned int classIndex; // edi
  int listOffset; // esi

  Output_Write(logicalName, headerString, logicalName);
  classIndex = 0;
  listOffset = 0;
  while ( classIndex < *classList )
  {
    Output_Write(v3, (int)(intptr_t)asc_509654, v3);
    listOffset += 4;
    ++classIndex;
    Class_PrintName(*(_DWORD *)(uintptr_t)(*(_DWORD *)(classList + 1) + listOffset - 4), 0);
  }
  return Output_Write(v3, (int)(intptr_t)asc_509650, v3);
}
// 4B0B22: variable 'v3' is possibly undefined

//----- (004B0B50) --------------------------------------------------------
int  Class_AddToHashTable(int theClass)
{
  unsigned int bucket; // edx

  bucket = 11329 * ((unsigned int)(*(_DWORD *)(uintptr_t)(Rules_GetConstructNameSymbol(theClass) + 12) << 16) >> 18) % 0xA7u;
  *(_DWORD *)(uintptr_t)(theClass + 30) = bucket;
  *(_DWORD *)(uintptr_t)(theClass + 100) = *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * bucket);
  *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * bucket) = theClass;
  return bucket;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0BA0) --------------------------------------------------------
int  Class_RemoveFromHashTable(int theClass)
{
  int chainCursor; // eax
  int i; // ecx
  int result; // eax

  chainCursor = *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * *(_DWORD *)(uintptr_t)(theClass + 30));
  for ( i = 0; chainCursor != theClass; chainCursor = *(_DWORD *)(uintptr_t)(chainCursor + 100) )
    i = chainCursor;
  result = *(_DWORD *)(uintptr_t)(theClass + 100);
  if ( i )
    *(_DWORD *)(uintptr_t)(i + 100) = result;
  else
    *(_DWORD *)(uintptr_t)(4 * *(_DWORD *)(uintptr_t)(theClass + 30) + g_DefclassHashTable) = result;
  return result;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0BF0) --------------------------------------------------------
signed int  Class_InsertLinkEntry(unsigned __int16 *linkArray, int newClass, int insertPosition)
{
  int old_count; // eax
  int old_items; // esi
  int new_items; // [esp+2h] [ebp-1Ah]
  int insert_slot; // edx
  unsigned __int16 new_count; // [esp+0h] [ebp-1Ch]

  old_count = *linkArray;
  new_items = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * old_count + 4);
  old_items = *(_DWORD *)(linkArray + 1);
  if ( insertPosition == -1 )
  {
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)new_items,
      (const void *)(uintptr_t)(unsigned int)old_items,
      4 * old_count);
    insert_slot = new_items + 4 * old_count;
  }
  else
  {
    if ( insertPosition )
      qmemcpy(
        (void *)(uintptr_t)(unsigned int)new_items,
        (const void *)(uintptr_t)(unsigned int)old_items,
        4 * insertPosition);
    insert_slot = new_items + 4 * insertPosition;
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)(insert_slot + 4),
      (const void *)(uintptr_t)(unsigned int)(old_items + 4 * insertPosition),
      4 * (old_count - insertPosition));
  }
  *(_DWORD *)(uintptr_t)(unsigned int)insert_slot = newClass;
  new_count = old_count + 1;
  Class_FreeOrRecycleArray(linkArray, 0);
  *linkArray = new_count;
  *(_DWORD *)(linkArray + 1) = new_items;
  return new_items;
}

//----- (004B0CE0) --------------------------------------------------------
unsigned __int16  Class_RemoveLinkEntry(int superClass, int theClass)
{
  unsigned __int16 *array_header; // ebx
  unsigned int remove_index; // edx
  int byte_offset; // eax
  unsigned __int16 count; // ax
  int old_items; // esi
  int new_items; // [esp+2h] [ebp-16h]
  unsigned __int16 new_count; // [esp+0h] [ebp-18h]

  array_header = (unsigned __int16 *)(uintptr_t)(superClass + 40);
  old_items = *(_DWORD *)(array_header + 1);
  remove_index = 0;
  byte_offset = 0;
  while ( remove_index < *array_header
       && theClass != *(_DWORD *)(uintptr_t)(unsigned int)(old_items + byte_offset) )
  {
    byte_offset += 4;
    ++remove_index;
  }
  count = *array_header;
  if ( remove_index == count )
    return count;
  if ( count <= 1u )
  {
    new_items = 0;
  }
  else
  {
    new_items = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * count - 4);
    if ( remove_index )
      qmemcpy(
        (void *)(uintptr_t)(unsigned int)new_items,
        (const void *)(uintptr_t)(unsigned int)old_items,
        4 * remove_index);
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)(new_items + 4 * remove_index),
      (const void *)(uintptr_t)(unsigned int)(old_items + 4 * remove_index + 4),
      4 * (count - remove_index) - 4);
  }
  new_count = count - 1;
  Class_FreeOrRecycleArray(array_header, 0);
  *array_header = new_count;
  *(_DWORD *)(array_header + 1) = new_items;
  return (unsigned __int16)new_items;
}

//----- (004B0DC0) --------------------------------------------------------
int  Class_AllocateRecord(int classNameSymbol)
{
  int free_record; // edx
  int class_record; // ecx
  char v4; // ah
  char v5; // dl
  int watchInstancesFlag; // eax
  char v7; // bl
  int v8; // esi

  free_record = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 496);
  if ( free_record )
  {
    g_ClipsMemFreeListTemp = free_record;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 496) = *(_DWORD *)(uintptr_t)free_record;
    class_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    class_record = Mem_HeapAllocWithRetry((_DWORD *)0x7C);
  }
  sub_4A94D0_Impl((int)(intptr_t)aDefclass_2, class_record, classNameSymbol);
  v4 = *(_BYTE *)(uintptr_t)(class_record + 20);
  *(_WORD *)(uintptr_t)(class_record + 24) = 0;
  *(_BYTE *)(uintptr_t)(class_record + 20) = v4 & 0xF0;
  v5 = *(_BYTE *)(uintptr_t)(class_record + 20);
  *(_DWORD *)(uintptr_t)(class_record + 26) = 0;
  v5 |= 8u;
  *(_BYTE *)(uintptr_t)(class_record + 20) = v5;
  watchInstancesFlag = g_Rules_WatchInstances & 1;
  *(_BYTE *)(uintptr_t)(class_record + 20) = v5 & 0xEF;
  *(_DWORD *)(uintptr_t)(class_record + 20) |= 16 * watchInstancesFlag;
  LOBYTE(watchInstancesFlag) = g_Class_WatchSlots[0];
  *(_DWORD *)(uintptr_t)(class_record + 30) = 0;
  *(_WORD *)(uintptr_t)(class_record + 34) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 36) = 0;
  *(_WORD *)(uintptr_t)(class_record + 40) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 42) = 0;
  *(_WORD *)(uintptr_t)(class_record + 46) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 48) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 52) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 56) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 60) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 72) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 68) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 64) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 76) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 88) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 92) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 96) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 80) = 0;
  v7 = *(_BYTE *)(uintptr_t)(class_record + 20);
  *(_DWORD *)(uintptr_t)(class_record + 84) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 100) = 0;
  *(_BYTE *)(uintptr_t)(class_record + 20) = v7 & 0xDF;
  v8 = *(_DWORD *)(uintptr_t)(class_record + 20);
  *(_DWORD *)(uintptr_t)(class_record + 104) = 0;
  *(_DWORD *)(uintptr_t)(class_record + 20) = (32 * (watchInstancesFlag & 1)) | v8;
  Mem_AllocArray((_BYTE *)(uintptr_t)(class_record + 108), 16);
  return class_record;
}
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0F00) --------------------------------------------------------
unsigned __int16 * Class_FreeOrRecycleArray(unsigned __int16 *result, int returnToPool)
{
  unsigned __int16 *arrayHeader; // ecx
  int items; // eax

  arrayHeader = result;
  if ( *result )
  {
    items = *(_DWORD *)(result + 1);
    result = (unsigned __int16 *)(uintptr_t)Mem_SmallBlockFree(
      (_DWORD *)(uintptr_t)(unsigned int)items,
      4 * *result);
    *arrayHeader = 0;
    *(_DWORD *)(arrayHeader + 1) = 0;
    if ( !returnToPool )
      return result;
    goto LABEL_5;
  }
  if ( returnToPool )
  {
LABEL_5:
    g_ClipsMemFreeListTemp = (int)(intptr_t)arrayHeader;
    *(_DWORD *)arrayHeader = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24);
    result = (unsigned __int16 *)(uintptr_t)g_ClipsMemFreeListTemp;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4B0F27: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0F60) --------------------------------------------------------
__int16  Class_AssignID(int theClass)
{
  __int16 result; // ax
  unsigned int idIndex; // eax
  int tableOffset; // edx

  if ( !((unsigned __int16)g_ClipsDefclassIdCount % 30) )
  {
    g_ClipsDefclassIdTable = (int)(intptr_t)Mem_Realloc(
                          (char *)(uintptr_t)g_ClipsDefclassIdTable,
                          4 * (unsigned __int16)g_ClipsDefclassIdCount,
                          4 * (unsigned __int16)g_ClipsDefclassIdCount + 120);
    idIndex = (unsigned __int16)g_ClipsDefclassIdCount;
    tableOffset = 4 * (unsigned __int16)g_ClipsDefclassIdCount;
    while ( idIndex < (unsigned int)(unsigned __int16)g_ClipsDefclassIdCount + 30 )
    {
      ++idIndex;
      *(_DWORD *)(uintptr_t)(g_ClipsDefclassIdTable + tableOffset) = 0;
      tableOffset += 4;
    }
  }
  *(_DWORD *)(uintptr_t)(4 * (unsigned __int16)g_ClipsDefclassIdCount + g_ClipsDefclassIdTable) = theClass;
  result = g_ClipsDefclassIdCount++;
  *(_WORD *)(uintptr_t)(theClass + 24) = result;
  return result;
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;

//----- (004B1010) --------------------------------------------------------
unsigned int * Class_InternSlotName(_DWORD *slotNameSymbol, int newSlotID, int useNewID)
{
  int slotNameID; // edi
  _DWORD *existingEntry; // ebx
  unsigned int i; // ecx
  _DWORD *freeNode; // ebx
  unsigned int *allocatedEntry; // eax
  unsigned int *newEntry; // ebx
  const char *slotNameStr; // edi
  char *prefixCursor; // esi
  _BYTE *destCursor; // edi
  char v15; // al
  char v16; // al
  char *nameCursor; // esi
  unsigned int prefixLen; // kr08_4
  char *appendCursor; // edi
  char v20; // al
  char v21; // al
  signed int *putSymbol; // eax
  unsigned int temp_name_bytes; // edx
  char *putName; // [esp-4h] [ebp-18h]
  _DWORD *putNameAlloc; // [esp+0h] [ebp-14h]

  slotNameID = newSlotID;
  existingEntry = *(_DWORD **)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * (11329 * (slotNameSymbol[3] << 16 >> 18) % 0xA7u));
  for ( i = 11329 * (slotNameSymbol[3] << 16 >> 18) % 0xA7u; existingEntry; existingEntry = (_DWORD *)(uintptr_t)existingEntry[5] )
  {
    if ( slotNameSymbol == (_DWORD *)(uintptr_t)existingEntry[3] )
      break;
  }
  if ( existingEntry )
  {
    if ( useNewID )
    {
      if ( newSlotID != existingEntry[2] )
      {
        Rules_ReportSystemError(i, 1);
        IO_RunRouterExitCallbacks();
      }
    }
    ++existingEntry[1];
    return existingEntry;
  }
  else
  {
    freeNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 112);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = *freeNode;
      allocatedEntry = (unsigned int *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedEntry = (unsigned int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
    }
    allocatedEntry[1] = 1;
    allocatedEntry[3] = (unsigned int)(intptr_t)slotNameSymbol;
    newEntry = allocatedEntry;
    *allocatedEntry = i;
    if ( !useNewID )
      slotNameID = Class_FindUnusedSlotNameID();
    newEntry[2] = slotNameID;
    newEntry[5] = *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * i);
    *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * i) = newEntry;
    slotNameStr = (const char *)(uintptr_t)slotNameSymbol[4];
    ++slotNameSymbol[1];
    prefixCursor = aPut_0;
    temp_name_bytes = strlen(slotNameStr) + 5;
    destCursor = Mem_SmallBlockAlloc(temp_name_bytes);
    putNameAlloc = destCursor;
    putName = destCursor;
    do
    {
      v15 = *prefixCursor;
      *destCursor = *prefixCursor;
      if ( !v15 )
        break;
      v16 = prefixCursor[1];
      prefixCursor += 2;
      destCursor[1] = v16;
      destCursor += 2;
    }
    while ( v16 );
    nameCursor = (char *)(uintptr_t)slotNameSymbol[4];
    prefixLen = strlen(putName) + 1;
    appendCursor = &putName[prefixLen - 1];
    do
    {
      v20 = *nameCursor;
      *appendCursor = *nameCursor;
      if ( !v20 )
        break;
      v21 = nameCursor[1];
      nameCursor += 2;
      appendCursor[1] = v21;
      appendCursor += 2;
    }
    while ( v21 );
    putSymbol = Str_Intern(putName, ~prefixLen);
    newEntry[4] = (unsigned int)(intptr_t)putSymbol;
    ++putSymbol[1];
    Mem_SmallBlockFree(putNameAlloc, temp_name_bytes);
    newEntry[6] = 0;
    return newEntry;
  }
}
// 4B10B0: variable 'i' is possibly undefined
// 51AD70: using guessed type int dword_51AD70;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1180) --------------------------------------------------------
_DWORD * Class_ReleaseSlotName(_DWORD *result)
{
  int entry; // edx
  int previous; // ecx
  int ref_count; // ebx

  if ( result )
  {
    entry = *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * *result);
    previous = 0;
    while ( entry != (int)(uintptr_t)result )
    {
      previous = entry;
      entry = *(_DWORD *)(uintptr_t)(entry + 20);
    }
    ref_count = *(_DWORD *)(uintptr_t)(entry + 4) - 1;
    *(_DWORD *)(uintptr_t)(entry + 4) = ref_count;
    if ( !ref_count )
    {
      if ( previous )
      {
        *(_DWORD *)(uintptr_t)(previous + 20) = *(_DWORD *)(uintptr_t)(entry + 20);
      }
      else
      {
        *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * *(_DWORD *)(uintptr_t)entry) = *(_DWORD *)(uintptr_t)(entry + 20);
      }
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(entry + 12), entry);
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(entry + 16), entry);
      g_ClipsMemFreeListTemp = entry;
      *(_DWORD *)(uintptr_t)entry = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
      result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 51AD70: using guessed type int dword_51AD70;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1210) --------------------------------------------------------
int  Class_DestroyRecord(int theClass)
{
  unsigned int i; // ecx
  int offset; // esi
  int slot; // eax
  int expression; // eax
  int count; // edi
  int handler; // edx
  int handler_name; // ecx
  int result; // eax

  i = 0;
  offset = 0;
  while ( i < *(unsigned __int16 *)(uintptr_t)(theClass + 34) )
  {
    offset += 4;
    Class_RemoveLinkEntry(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 36) + offset - 4), theClass);
    ++i;
  }
  Class_RemoveFromHashTable(theClass);
  Class_SetInstallState((__int16 *)(uintptr_t)theClass, 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(uintptr_t)(theClass + 34), 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(uintptr_t)(theClass + 46), 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(uintptr_t)(theClass + 40), 0);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(uintptr_t)(theClass + 64) )
  {
    slot = *(_DWORD *)(uintptr_t)(theClass + 52) + offset;
    expression = *(_DWORD *)(uintptr_t)(slot + 16);
    if ( expression )
    {
      if ( (*(_BYTE *)(uintptr_t)slot & 0x40) != 0 )
      {
        AST_FreePackedNodeChain(expression);
      }
      else
      {
        g_ClipsMemFreeListTemp = expression;
        *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
      }
    }
    Class_ReleaseSlotName((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(slot + 8));
    AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(slot + 20));
    ++i;
    offset += 44;
  }
  count = *(_DWORD *)(uintptr_t)(theClass + 72);
  if ( count )
  {
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theClass + 56), 4 * count);
    Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)(theClass + 60), 4 * (*(_DWORD *)(uintptr_t)(theClass + 76) + 1));
  }
  count = *(_DWORD *)(uintptr_t)(theClass + 64);
  if ( count )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theClass + 52), 44 * count);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(uintptr_t)(theClass + 96) )
  {
    handler = *(_DWORD *)(uintptr_t)(theClass + 88) + offset;
    expression = *(_DWORD *)(uintptr_t)(handler + 28);
    if ( expression )
      AST_FreePackedNodeChain(expression);
    handler_name = *(_DWORD *)(uintptr_t)(handler + 32);
    if ( handler_name )
      Mem_SmallBlockFree(
        (_DWORD *)(uintptr_t)(unsigned int)handler_name,
        strlen((const char *)(uintptr_t)(unsigned int)handler_name) + 1);
    ++i;
    offset += 36;
  }
  count = *(_DWORD *)(uintptr_t)(theClass + 96);
  if ( count )
  {
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theClass + 88), 36 * count);
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theClass + 92), 4 * count);
  }
  Rules_ReplaceConstructPPForm(theClass, 0);
  Class_ReleaseSlotIDMapEntry(*(unsigned __int16 *)(uintptr_t)(theClass + 24), 0);
  g_ClipsMemFreeListTemp = theClass;
  *(_DWORD *)(uintptr_t)theClass = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 496);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 496) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B13E0) --------------------------------------------------------
__int16 * Class_SetInstallState(__int16 *result, int install)
{
  int class_record; // ecx
  unsigned int i; // ebx
  int offset; // esi
  int slot; // edx
  int handler; // edx

  class_record = (int)(uintptr_t)result;
  if ( install )
  {
    if ( *(_BYTE *)(uintptr_t)(class_record + 20) & 1 )
      return result;
    *(_BYTE *)(uintptr_t)(class_record + 20) |= 1u;
    ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)class_record + 4);
    return result;
  }
  if ( (*(_BYTE *)(uintptr_t)(class_record + 20) & 1) == 0 )
    return result;
  *(_BYTE *)(uintptr_t)(class_record + 20) &= ~1u;
  Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)class_record, class_record);
  Rules_DecrementBitmapCount(*(_DWORD *)(uintptr_t)(class_record + 104), class_record);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(uintptr_t)(class_record + 64) )
  {
    slot = *(_DWORD *)(uintptr_t)(class_record + 52) + offset;
    Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(slot + 12), class_record);
    if ( *(_DWORD *)(uintptr_t)(slot + 16) )
    {
      if ( (*(_BYTE *)(uintptr_t)slot & 0x40) != 0 )
        AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(slot + 16));
      else
        Rules_ValueDeinstall(*(_DWORD *)(uintptr_t)(slot + 16), class_record);
    }
    ++i;
    offset += 44;
  }
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(uintptr_t)(class_record + 96) )
  {
    handler = *(_DWORD *)(uintptr_t)(class_record + 88) + offset;
    Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(handler + 8), class_record);
    if ( *(_DWORD *)(uintptr_t)(handler + 28) )
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(handler + 28));
    ++i;
    offset += 36;
  }
  return result;
}

//----- (004B14B0) --------------------------------------------------------
signed int  Class_HierarchyHasInstances(int theClass)
{
  int subclassOffset; // ecx
  int v4; // edx
  int v5; // ecx

  if ( *(_DWORD *)(uintptr_t)(theClass + 26) )
    return 1;
  subclassOffset = 0;
  if ( *(_WORD *)(uintptr_t)(theClass + 40) )
  {
    while ( !Class_HierarchyHasInstances(*(_DWORD *)(uintptr_t)(subclassOffset + *(_DWORD *)(uintptr_t)(theClass + 42))) )
    {
      subclassOffset = v5 + 4;
      if ( v4 + 1 >= (unsigned int)*(unsigned __int16 *)(uintptr_t)(theClass + 40) )
        return 0;
    }
    return 1;
  }
  return 0;
}
// 4B14E7: variable 'v5' is possibly undefined
// 4B14EA: variable 'v4' is possibly undefined

//----- (004B1500) --------------------------------------------------------
signed int Class_RemoveAllDeletableClasses(void)
{
  int success; // ebx
  int i; // ecx
  int classRecord; // edx
  int constructName; // eax
  int v5; // ecx

  success = 1;
  if ( Rules_IsBloaded() )
    return 0;
  for ( i = Class_GetNextRecord(0); i; i = Class_GetNextRecord(i) )
  {
    if ( (*(_BYTE *)(uintptr_t)(i + 20) & 2) == 0 )
      break;
  }
  while ( i )
  {
    Class_GetNextRecord(i);
    if ( Class_IsDeletable() )
    {
      Rules_UnlinkListNode(classRecord);
      Class_DestroyRecord(classRecord);
    }
    else
    {
      constructName = Rules_GetConstructNameString(classRecord);
      success = 0;
      Rules_ReportCantDeleteItem(v5, constructName);
    }
  }
  return success;
}
// 4B1528: variable 'i' is possibly undefined
// 4B1542: variable 'v3' is possibly undefined
// 4B156F: variable 'v5' is possibly undefined

//----- (004B1580) --------------------------------------------------------
int  Class_DeleteRecursive(int theClass)
{
  int v2; // ecx
  int subclassCount; // eax
  int result; // eax
  int classRecord; // edx

  if ( *(_WORD *)(uintptr_t)(theClass + 40) )
  {
    while ( 1 )
    {
      Class_DeleteRecursive(**(_DWORD **)(uintptr_t)(theClass + 42));
      subclassCount = *(unsigned __int16 *)(uintptr_t)(theClass + 40);
      if ( (unsigned __int16)subclassCount == v2 )
        return v2 ^ subclassCount;
      if ( !*(_WORD *)(uintptr_t)(theClass + 40) )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    result = Class_IsDeletable();
    if ( result )
    {
      Rules_UnlinkListNode(classRecord);
      Class_DestroyRecord(classRecord);
      return 1;
    }
  }
  return result;
}
// 4B15A6: variable 'v2' is possibly undefined
// 4B15C6: variable 'v5' is possibly undefined

//----- (004B15E0) --------------------------------------------------------
int  Class_MarkBitmapSubclasses(int bitmap, int theClass, int setBit)
{
  unsigned __int16 classID; // cx
  _BYTE *bytePtr; // esi
  int result; // eax
  unsigned int subclassIndex; // ecx
  int subclassOffset; // esi

  classID = *(_WORD *)(uintptr_t)(theClass + 24);
  bytePtr = (_BYTE *)(uintptr_t)(((int)classID >> 3) + bitmap);
  if ( setBit )
  {
    result = 1 << (classID % 8);
    *bytePtr |= result;
  }
  else
  {
    result = ~(1 << (classID % 8));
    *bytePtr &= result;
  }
  subclassIndex = 0;
  subclassOffset = 0;
  while ( subclassIndex < *(unsigned __int16 *)(uintptr_t)(theClass + 40) )
  {
    subclassOffset += 4;
    result = Class_MarkBitmapSubclasses(bitmap, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 42) + subclassOffset - 4), setBit);
  }
  return result;
}
// 4B1631: variable 'v8' is possibly undefined

//----- (004B1690) --------------------------------------------------------
signed int  Class_FindSlotNameID(int slotNameSymbol)
{
  int current; // eax
  unsigned int bucket_index; // edx

  bucket_index = 11329 * ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slotNameSymbol + 12) << 16 >> 18) % 0xA7u;
  current = *(_DWORD *)((uintptr_t)(unsigned int)g_Defclass_SlotNameHashTablePtr + 4 * bucket_index);
  while ( current )
  {
    if ( slotNameSymbol == *(_DWORD *)((uintptr_t)(unsigned int)current + 12) )
      break;
    current = *(_DWORD *)((uintptr_t)(unsigned int)current + 20);
  }
  if ( current )
    return *(_DWORD *)((uintptr_t)(unsigned int)current + 8);
  else
    return -1;
}
// 51AD70: using guessed type int dword_51AD70;

//----- (004B16F0) --------------------------------------------------------
int  Class_GetSlotNameByID(int slotNameID)
{
  int result; // eax

  result = Class_FindSlotNameEntryByID(slotNameID);
  if ( result )
    return *(_DWORD *)(uintptr_t)(result + 12);
  return result;
}

//----- (004B1700) --------------------------------------------------------
int  Class_FindSlotNameEntryByID(int slotNameID)
{
  int bucketOffset; // ecx
  int result; // eax

  bucketOffset = 0;
  while ( 1 )
  {
    result = *(_DWORD *)(uintptr_t)(bucketOffset + g_Defclass_SlotNameHashTablePtr);
    if ( result )
      break;
LABEL_5:
    bucketOffset += 4;
    if ( bucketOffset >= 668 )
      return 0;
  }
  while ( slotNameID != *(_DWORD *)(uintptr_t)(result + 8) )
  {
    result = *(_DWORD *)(uintptr_t)(result + 20);
    if ( !result )
      goto LABEL_5;
  }
  return result;
}
// 51AD70: using guessed type int dword_51AD70;

//----- (004B1730) --------------------------------------------------------
signed int Class_NewTraversalID(void)
{
  int i; // edi
  int j; // ebx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  if ( (unsigned __int8)g_Class_TraversalIDCounter >= 0x80u )
  {
    Rules_PrintErrorID((int)(intptr_t)aClassfun, 2, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMaximumNumberO, v3);
    Rules_PrintLongInteger(v4, 128);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__21, v5);
    Lexer_ErrorRecover(1);
    return -1;
  }
  else
  {
    for ( i = 0; i != 668; i += 4 )
    {
      for ( j = *(_DWORD *)(uintptr_t)(i + g_DefclassHashTable); j; j = *(_DWORD *)(uintptr_t)(j + 100) )
        *(_BYTE *)(uintptr_t)(j + (unsigned __int8)g_Class_TraversalIDCounter / 8 + 108) &= ~(1 << ((unsigned __int8)g_Class_TraversalIDCounter % 8));
    }
    return (unsigned __int8)g_Class_TraversalIDCounter++;
  }
}
// 4B17D3: variable 'v3' is possibly undefined
// 4B17E2: variable 'v4' is possibly undefined
// 4B17F1: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD68: using guessed type int dword_51AD68;
// 51ADA0: using guessed type char byte_51ADA0;

//----- (004B1810) --------------------------------------------------------
void Class_ReleaseTraversalID(void)
{
  --g_Class_TraversalIDCounter;
}
// 51ADA0: using guessed type char byte_51ADA0;

//----- (004B1820) --------------------------------------------------------
unsigned int  Class_HashClassName(int classNameSymbol)
{
  return 11329 * (*(_DWORD *)(uintptr_t)(classNameSymbol + 12) << 16 >> 18) % 0xA7u;
}
