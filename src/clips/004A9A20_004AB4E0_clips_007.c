/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004A9A20) --------------------------------------------------------
_DWORD * Instance_BuildInstance(int instanceName, int theDefclass, int initMessage, double a4)
{
  signed int *nameSymbol; // esi
  signed int separatorPosition; // eax
  signed int *moduleName; // eax
  int v8; // ecx
  _DWORD *existingInstance; // eax
  int v10; // ecx
  _DWORD *oldInstance; // ebp
  int v12; // eax
  int bucketHead; // ebx
  int classRecord; // ecx
  int newInstance; // eax
  _DWORD *theInstance; // ecx
  _DWORD *result; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int classNameString; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int nextHashInstance; // ecx
  int v31; // eax
  int prevInstance; // [esp+0h] [ebp-20h] BYREF
  int hashBucket; // [esp+4h] [ebp-1Ch]
  int deleteMessageSymbol CLASH95_UNUSED; // [esp+8h] [ebp-18h]
  int savedInitMessage; // [esp+Ch] [ebp-14h]

  nameSymbol = (signed int *)(uintptr_t)instanceName;
  savedInitMessage = initMessage;
  if ( g_Rules_JoinOperationInProgress && (*(_BYTE *)(uintptr_t)(theDefclass + 20) & 8) != 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 10, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotCreate_0, v18);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPatternMatch_0, v19);
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(theDefclass + 20) & 4) != 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 3, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotCreate_1, v20);
    classNameString = Rules_GetConstructNameString(theDefclass);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], classNameString, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__17, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  separatorPosition = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(instanceName + 16));
  if ( separatorPosition )
  {
    moduleName = Rules_ExtractModuleName(separatorPosition);
    if ( !moduleName || moduleName != ***(signed int ****)(uintptr_t)(theDefclass + 8) )
    {
      Rules_PrintErrorID((int)(intptr_t)aInsmngr, 11, 1);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInvalidModuleS, v23);
      Lexer_ErrorRecover(1);
      return 0;
    }
    nameSymbol = Rules_ExtractConstructName(v8, (char *)(uintptr_t)nameSymbol[4], v8);
  }
  existingInstance = Instance_FindHashEntryForBuild(theDefclass, (int)(intptr_t)nameSymbol, &prevInstance, &hashBucket);
  oldInstance = existingInstance;
  if ( !existingInstance )
    goto LABEL_14;
  if ( (existingInstance[6] & 1) == 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 4, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheInstance, v24);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], nameSymbol[4], v25);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aHasASlotValueW, v26);
    Lexer_ErrorRecover(1);
    return 0;
  }
  ++existingInstance[10];
  ++nameSymbol[1];
  if ( (existingInstance[6] & 2) == 0 )
  {
    if ( g_Instance_UseMessageDispatchForInit )
    {
      deleteMessageSymbol = g_ClipsDeleteMessageSymbol;
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, (int)(intptr_t)existingInstance, 0, 0, a4);
    }
    else
    {
      Instance_DeleteInstance((int)(intptr_t)existingInstance, a4);
    }
  }
  --oldInstance[10];
  Rules_DecrementSymbolCount((int)(intptr_t)nameSymbol, v10);
  if ( (oldInstance[6] & 2) == 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 5, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDele_0, v27);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], nameSymbol[4], v28);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__17, v29);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
LABEL_14:
    g_ClipsInstanceUnderConstruction = Instance_AllocateInstanceRecord();
    if ( Rules_AddLogicalDependencyLink(g_ClipsInstanceUnderConstruction, 0) )
    {
      *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 28) = nameSymbol;
      *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 44) = theDefclass;
      Instance_AllocateSlotValueTable(savedInitMessage);
      v12 = hashBucket;
      *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 36) = hashBucket;
      if ( prevInstance )
      {
        *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(uintptr_t)(prevInstance + 60);
        nextHashInstance = *(_DWORD *)(uintptr_t)(prevInstance + 60);
        if ( nextHashInstance )
          *(_DWORD *)(uintptr_t)(nextHashInstance + 56) = g_ClipsInstanceUnderConstruction;
        v31 = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(uintptr_t)(prevInstance + 60) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(uintptr_t)(v31 + 56) = prevInstance;
      }
      else
      {
        *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(uintptr_t)(g_Instance_HashTableBase + 4 * v12);
        bucketHead = *(_DWORD *)(uintptr_t)(g_Instance_HashTableBase + 4 * hashBucket);
        if ( bucketHead )
          *(_DWORD *)(uintptr_t)(bucketHead + 56) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(uintptr_t)(4 * hashBucket + g_Instance_HashTableBase) = g_ClipsInstanceUnderConstruction;
      }
      classRecord = *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 44);
      if ( *(_DWORD *)(uintptr_t)(classRecord + 80) )
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(classRecord + 84) + 52) = g_ClipsInstanceUnderConstruction;
      else
        *(_DWORD *)(uintptr_t)(classRecord + 80) = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 48) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 44) + 84);
      newInstance = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 44) + 84) = g_ClipsInstanceUnderConstruction;
      if ( g_Clips_InstanceListHead )
        *(_DWORD *)(uintptr_t)(g_Instance_GlobalListTail + 68) = newInstance;
      else
        g_Clips_InstanceListHead = newInstance;
      *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 64) = g_Instance_GlobalListTail;
      g_Instance_InstancesChangedFlag = 1;
      g_Instance_GlobalListTail = g_ClipsInstanceUnderConstruction;
      Instance_SetActiveFlag(g_ClipsInstanceUnderConstruction, 1);
      theInstance = (_DWORD *)(uintptr_t)g_ClipsInstanceUnderConstruction;
      g_ClipsInstanceUnderConstruction = 0;
      if ( (*(_BYTE *)(uintptr_t)(theInstance[11] + 20) & 8) != 0 )
        Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a4);
      return theInstance;
    }
    else
    {
      g_ClipsMemFreeListTemp = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)(uintptr_t)g_ClipsInstanceUnderConstruction = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;
      result = 0;
      g_ClipsInstanceUnderConstruction = 0;
    }
  }
  return result;
}
// 4A9A7C: variable 'v8' is possibly undefined
// 4A9AD9: variable 'v10' is possibly undefined
// 4A9C15: variable 'v16' is possibly undefined
// 4A9C3A: variable 'v18' is possibly undefined
// 4A9C49: variable 'v19' is possibly undefined
// 4A9C7D: variable 'v20' is possibly undefined
// 4A9CA2: variable 'v22' is possibly undefined
// 4A9CD9: variable 'v23' is possibly undefined
// 4A9D0D: variable 'v24' is possibly undefined
// 4A9D1A: variable 'v25' is possibly undefined
// 4A9D29: variable 'v26' is possibly undefined
// 4A9D67: variable 'v27' is possibly undefined
// 4A9D74: variable 'v28' is possibly undefined
// 4A9D83: variable 'v29' is possibly undefined
// 51A278: using guessed type int dword_51A278;
// 51A284: using guessed type int dword_51A284;
// 51A288: using guessed type int dword_51A288;
// 51A614: using guessed type char *off_51A614[5];
// 51A954: using guessed type int dword_51A954;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD14: using guessed type int dword_51AD14;
// 51AD18: using guessed type int dword_51AD18;
// 51AD38: using guessed type int dword_51AD38;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A9E30) --------------------------------------------------------
char  Instance_InitSlotsCommand(uintptr_t returnValue, uintptr_t a2, double a3)
{
  signed int v2; // eax
  int selfArgument; // eax

  (void)a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  v2 = MessageHandler_CheckCurrentMessage((int)(intptr_t)aInitSlots, 1);
  if ( v2 )
  {
    selfArgument = MessageHandler_GetNthArgument(0);
    LOBYTE(v2) = Instance_InitSlots(*(_DWORD *)(uintptr_t)(selfArgument + 8), (__int16)returnValue, a3);
    if ( !g_ClipsEvaluationError )
    {
      *(_DWORD *)(returnValue + 4) = 7;
      v2 = *(_DWORD *)(uintptr_t)(MessageHandler_GetNthArgument(0) + 8);
      *(_DWORD *)(returnValue + 8) = v2;
    }
  }
  return v2;
}
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9E90) --------------------------------------------------------
signed int  Instance_DeleteInstance(int theInstance, double a2)
{
  uintptr_t instance; // ecx
  uintptr_t class_record; // eax
  unsigned char flags; // dh
  unsigned int previous_hash_link; // ebx
  unsigned int next_hash_link; // esi
  unsigned int previous_class_link; // edi
  unsigned int next_class_link; // ebp
  unsigned int previous_global_link; // eax
  unsigned int next_global_link; // edx
  int was_active; // ebx
  unsigned int deferred_node; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx

  instance = (uintptr_t)(unsigned int)theInstance;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  if ( g_Rules_JoinOperationInProgress && (*(_BYTE *)(class_record + 20) & 8) != 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 12, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotDeleteIn, v14);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPatternMatch_0, v15);
    Lexer_ErrorRecover(1);
    return 0;
  }
  flags = *(_BYTE *)(instance + 24);
  if ( (flags & 2) != 0 )
    return 0;
  if ( (flags & 1) != 0 )
  {
    if ( (*(_BYTE *)(class_record + 20) & 0x10) != 0 )
      Instance_PrintWatchTrace((int)(intptr_t)asc_508714, (int)instance);
    Rules_ReleaseLogicalSupportList((int)instance);
    if ( (*(_BYTE *)(class_record + 20) & 8) != 0 )
      Rules_ObjectMatchAction((unsigned __int16 *)2, (_DWORD *)instance, -1, a2);
    previous_hash_link = *(_DWORD *)(instance + 56);
    if ( previous_hash_link )
      *(_DWORD *)((uintptr_t)previous_hash_link + 60) = *(_DWORD *)(instance + 60);
    else
      *(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * *(_DWORD *)(instance + 36)) = *(_DWORD *)(instance + 60);
    next_hash_link = *(_DWORD *)(instance + 60);
    if ( next_hash_link )
      *(_DWORD *)((uintptr_t)next_hash_link + 56) = *(_DWORD *)(instance + 56);
    previous_class_link = *(_DWORD *)(instance + 48);
    if ( previous_class_link )
      *(_DWORD *)((uintptr_t)previous_class_link + 52) = *(_DWORD *)(instance + 52);
    else
      *(_DWORD *)(class_record + 80) = *(_DWORD *)(instance + 52);
    next_class_link = *(_DWORD *)(instance + 52);
    if ( next_class_link )
      *(_DWORD *)((uintptr_t)next_class_link + 48) = *(_DWORD *)(instance + 48);
    else
      *(_DWORD *)(class_record + 84) = *(_DWORD *)(instance + 48);
    previous_global_link = *(_DWORD *)(instance + 64);
    if ( previous_global_link )
      *(_DWORD *)((uintptr_t)previous_global_link + 68) = *(_DWORD *)(instance + 68);
    else
      g_Clips_InstanceListHead = *(_DWORD *)(instance + 68);
    next_global_link = *(_DWORD *)(instance + 68);
    if ( next_global_link )
      *(_DWORD *)((uintptr_t)next_global_link + 64) = *(_DWORD *)(instance + 64);
    else
      g_Instance_GlobalListTail = *(_DWORD *)(instance + 64);
    was_active = *(_DWORD *)(instance + 24) & 1;
    Instance_SetActiveFlag((int)instance, 0);
    if ( was_active == 1 && !*(_DWORD *)(instance + 8) )
      Instance_ReleaseSlotValues((int)instance);
    if ( *(_DWORD *)(instance + 40)
      || g_ClipsCurrentEvaluationDepth >= *(_DWORD *)(instance + 32)
      || g_Instance_PurgeInProgress
      || *(_DWORD *)(instance + 8) )
    {
      deferred_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
      if ( deferred_node )
      {
        g_ClipsMemFreeListTemp = deferred_node;
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = *(_DWORD *)(uintptr_t)deferred_node;
        deferred_node = g_ClipsMemFreeListTemp;
      }
      else
      {
        deferred_node = Mem_HeapAllocWithRetry((_DWORD *)8);
      }
      *(_BYTE *)(instance + 24) |= 2u;
      *(_DWORD *)(uintptr_t)deferred_node = (int)instance;
      *(_DWORD *)((uintptr_t)deferred_node + 4) = g_Instance_DeletedListHead;
      g_Instance_DeletedListHead = deferred_node;
      g_ClipsEphemeralItemCount += 2;
      g_ClipsEphemeralItemBytes += 88;
      g_Instance_InstancesChangedFlag = 1;
      return 1;
    }
    else
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(instance + 28), (int)instance);
      g_ClipsMemFreeListTemp = (int)instance;
      *(_DWORD *)instance = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 320);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;
      g_Instance_InstancesChangedFlag = 1;
      return 1;
    }
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 6, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotDelete_0, v16);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 28) + 16), v17);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDuringInitiali, v18);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 4AA009: variable 'v14' is possibly undefined
// 4AA018: variable 'v15' is possibly undefined
// 4AA049: variable 'v16' is possibly undefined
// 4AA04E: variable 'v17' is possibly undefined
// 4AA068: variable 'v18' is possibly undefined
// 51A278: using guessed type int dword_51A278;
// 51A280: using guessed type int dword_51A280;
// 51A288: using guessed type int dword_51A288;
// 51A28C: using guessed type int dword_51A28C;
// 51A614: using guessed type char *off_51A614[5];
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A954: using guessed type int dword_51A954;
// 51A96C: using guessed type int dword_51A96C;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD18: using guessed type int dword_51AD18;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AA140) --------------------------------------------------------
int  Instance_InitializeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveInitializeInstanceFunction(returnValue, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA170) --------------------------------------------------------
int  Instance_MakeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveMakeInstanceFunction(returnValue, returnValue, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA1A0) --------------------------------------------------------
signed int Instance_AllocateInstanceRecord(void)
{
  _DWORD *freeNode; // edx
  signed int result; // eax
  char flagsByte; // dl
  int evalDepth; // edx

  Rules_EnsureObjectPatternVTable();
  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320) = *freeNode;
    result = g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x50);
  }
  *(_DWORD *)(uintptr_t)result = (int)(uintptr_t)g_Rules_ObjectPatternVTable;
  *(_DWORD *)(uintptr_t)(result + 4) = 0;
  *(_DWORD *)(uintptr_t)(result + 8) = 0;
  *(_DWORD *)(uintptr_t)(result + 12) = 0;
  *(_DWORD *)(uintptr_t)(result + 16) = 0;
  *(_DWORD *)(uintptr_t)(result + 20) = 0;
  flagsByte = *(_BYTE *)(uintptr_t)(result + 24);
  *(_DWORD *)(uintptr_t)(result + 40) = 0;
  *(_BYTE *)(uintptr_t)(result + 24) = flagsByte & 0xF8;
  evalDepth = g_ClipsCurrentEvaluationDepth;
  *(_DWORD *)(uintptr_t)(result + 28) = 0;
  *(_DWORD *)(uintptr_t)(result + 36) = 0;
  *(_DWORD *)(uintptr_t)(result + 44) = 0;
  *(_DWORD *)(uintptr_t)(result + 76) = 0;
  *(_DWORD *)(uintptr_t)(result + 72) = 0;
  *(_DWORD *)(uintptr_t)(result + 48) = 0;
  *(_DWORD *)(uintptr_t)(result + 52) = 0;
  *(_DWORD *)(uintptr_t)(result + 56) = 0;
  *(_DWORD *)(uintptr_t)(result + 60) = 0;
  *(_DWORD *)(uintptr_t)(result + 64) = 0;
  *(_DWORD *)(uintptr_t)(result + 68) = 0;
  *(_DWORD *)(uintptr_t)(result + 32) = evalDepth;
  return result;
}
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AA270) --------------------------------------------------------
_DWORD * Instance_FindHashEntryForBuild(int theDefclass, int instanceName, _DWORD *prevInstance, _DWORD *hashTableIndex)
{
  unsigned int bucket; // eax
  _DWORD *result; // eax

  bucket = Instance_HashNameToBucket(instanceName);
  *hashTableIndex = bucket;
  result = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket);
  for ( *prevInstance = 0; result; result = (_DWORD *)(uintptr_t)(unsigned int)result[15] )
  {
    if ( instanceName == (int)result[7] )
      break;
    *prevInstance = (int)(uintptr_t)result;
  }
  while ( result && instanceName == (int)result[7] )
  {
    if ( *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theDefclass + 8) ==
         *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)result[11] + 8) )
      return result;
    *prevInstance = (int)(uintptr_t)result;
    result = (_DWORD *)(uintptr_t)(unsigned int)result[15];
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (004AA2E0) --------------------------------------------------------
int  Instance_SetActiveFlag(int result, int set)
{
  int theInstance; // ecx

  theInstance = result;
  if ( set == 1 )
  {
    if ( (*(_BYTE *)(uintptr_t)(result + 24) & 1) == 0 )
    {
      if ( (*(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 44) + 20) & 0x10) != 0 )
        Instance_PrintWatchTrace((int)(intptr_t)asc_508718, result);
      *(_BYTE *)(uintptr_t)(theInstance + 24) |= 1u;
      *(_DWORD *)(uintptr_t)(theInstance + 32) = g_ClipsCurrentEvaluationDepth;
      ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 4);
      result = Class_AddBusyReference(*(_DWORD *)(uintptr_t)(theInstance + 44));
      ++g_Rules_ActiveInstanceCount;
    }
  }
  else if ( (*(_BYTE *)(uintptr_t)(result + 24) & 1) != 0 )
  {
    *(_BYTE *)(uintptr_t)(result + 24) &= ~1u;
    --g_Rules_ActiveInstanceCount;
  }
  return result;
}
// 4AA303: variable 'v2' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 51AD10: using guessed type int dword_51AD10;

//----- (004AA340) --------------------------------------------------------
int  Instance_AllocateSlotValueTable(int initMessage)
{
  int class_record; // edx
  int slot_count; // eax
  int local_slot_count; // edx
  int slot_value_table; // ecx
  int local_slot_values; // ebx
  int local_slot_cursor; // ebx
  int slot_descriptors; // esi
  int slot_value_cursor; // ecx
  int slot_descriptor; // eax
  int slot_value; // eax
  int create_mode; // [esp+4h] [ebp-20h]
  int index; // edi

  class_record = *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 44);
  slot_count = *(_DWORD *)(uintptr_t)(class_record + 72);
  local_slot_count = *(_DWORD *)(uintptr_t)(class_record + 68);
  if ( slot_count <= 0 )
    return slot_count;
  slot_value_table = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * slot_count);
  *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 72) = slot_value_table;
  local_slot_values = 0;
  if ( local_slot_count )
  {
    local_slot_values = (int)(uintptr_t)Mem_SmallBlockAlloc(12 * local_slot_count);
    *(_DWORD *)(uintptr_t)(g_ClipsInstanceUnderConstruction + 76) = local_slot_values;
  }
  slot_descriptors = *(_DWORD *)(uintptr_t)(class_record + 56);
  create_mode = initMessage & 1;
  local_slot_cursor = local_slot_values;
  slot_value_cursor = slot_value_table;
  for ( index = 0; index < slot_count; ++index )
  {
    slot_descriptor = *(_DWORD *)(uintptr_t)(slot_descriptors + 4 * index);
    if ( (*(_BYTE *)(uintptr_t)slot_descriptor & 1) != 0 )
    {
      ++*(_DWORD *)(uintptr_t)(slot_descriptor + 24);
      slot_value = slot_descriptor + 32;
      *(_DWORD *)(uintptr_t)slot_value_cursor = slot_value;
    }
    else
    {
      slot_value = local_slot_cursor;
      *(_DWORD *)(uintptr_t)(slot_value + 8) = 0;
      *(_DWORD *)(uintptr_t)slot_value = slot_descriptor;
      local_slot_cursor += 12;
      *(_DWORD *)(uintptr_t)slot_value_cursor = slot_value;
    }
    if ( *(_DWORD *)(uintptr_t)(slot_value + 8) )
    {
      *(_BYTE *)(uintptr_t)(slot_value + 4) &= ~1u;
    }
    else
    {
      *(_BYTE *)(uintptr_t)(slot_value + 4) &= ~1u;
      *(_BYTE *)(uintptr_t)(slot_value + 4) |= create_mode;
      if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)slot_value & 2) != 0 )
      {
        *(_BYTE *)(uintptr_t)(slot_value + 4) = (*(_BYTE *)(uintptr_t)(slot_value + 4) & 3) | 0x10;
        *(_DWORD *)(uintptr_t)(slot_value + 8) = (int)(uintptr_t)Rules_CreateMultifield(0);
        Rules_InstallMultifield((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(slot_value + 8));
      }
      else
      {
        *(_BYTE *)(uintptr_t)(slot_value + 4) = (*(_BYTE *)(uintptr_t)(slot_value + 4) & 3) | 8;
        *(_DWORD *)(uintptr_t)(slot_value + 8) = (int)(uintptr_t)Str_Intern(aNil_3, 0);
        Rules_AtomInstall(((unsigned int)*(_DWORD *)(uintptr_t)(slot_value + 4) << 24) >> 26, *(_DWORD *)(uintptr_t)(slot_value + 8), slot_value);
      }
    }
    *(_BYTE *)(uintptr_t)(slot_value + 4) &= ~2u;
    slot_value_cursor += 4;
  }
  return slot_value;
}
// 51AD14: using guessed type int dword_51AD14;

//----- (004AA4A0) --------------------------------------------------------
BOOL  Instance_InitializeSlots(int theInstance, int overrideExprs, double a3)
{
  int busyCount; // ecx
  char clearedFlags; // bl
  __int16 v6; // cx
  int savedSlotInit; // edi
  char restoredFlags; // cl
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int messageResult[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( (*(_BYTE *)(uintptr_t)(theInstance + 24) & 1) != 0 )
  {
    busyCount = *(_DWORD *)(uintptr_t)(theInstance + 40) + 1;
    clearedFlags = *(_BYTE *)(uintptr_t)(theInstance + 24) & 0xFE;
    *(_DWORD *)(uintptr_t)(theInstance + 40) = busyCount;
    *(_BYTE *)(uintptr_t)(theInstance + 24) = clearedFlags;
    if ( Instance_ApplySlotOverrideList((_DWORD *)(uintptr_t)theInstance, overrideExprs, busyCount, a3) )
    {
      *(_BYTE *)(uintptr_t)(theInstance + 24) |= 4u;
      savedSlotInit = g_Instance_SlotInitInProgress;
      g_Instance_SlotInitInProgress = 1;
      if ( g_Instance_UseMessageDispatchForInit )
        MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, theInstance, 0, messageResult, a3);
      else
        Instance_InitSlots(theInstance, v6, a3);
      g_Instance_SlotInitInProgress = savedSlotInit;
      restoredFlags = *(_BYTE *)(uintptr_t)(theInstance + 24) | 1;
      --*(_DWORD *)(uintptr_t)(theInstance + 40);
      *(_BYTE *)(uintptr_t)(theInstance + 24) = restoredFlags;
      if ( g_ClipsEvaluationError )
      {
        Rules_PrintErrorID((int)(intptr_t)aInsmngr, 8, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAnErrorOccurre, v14);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 16), v15);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__17, v16);
        return 0;
      }
      else
      {
        return (restoredFlags & 4) == 0;
      }
    }
    else
    {
      v13 = *(_DWORD *)(uintptr_t)(theInstance + 40) - 1;
      *(_BYTE *)(uintptr_t)(theInstance + 24) |= 1u;
      *(_DWORD *)(uintptr_t)(theInstance + 40) = v13;
      return 0;
    }
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 7, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInstance_4, v10);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 16), v11);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsAlreadyBeing, v12);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 4AA558: variable 'v10' is possibly undefined
// 4AA568: variable 'v11' is possibly undefined
// 4AA577: variable 'v12' is possibly undefined
// 4AA5AD: variable 'v6' is possibly undefined
// 4AA5D2: variable 'v14' is possibly undefined
// 4AA5E2: variable 'v15' is possibly undefined
// 4AA5F1: variable 'v16' is possibly undefined
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD34: using guessed type int dword_51AD34;

//----- (004AA610) --------------------------------------------------------
signed int  Instance_ApplySlotOverrideList(_DWORD *theInstance, int slotOverrides, int a3, double a4)
{
  int slot_override; // edi
  int *slot_value; // esi
  signed int result; // eax
  int parsed_ptr; // ecx
  int saved_context; // [esp+18h] [ebp-1Ch]
  int *saved_slot_value; // [esp+1Ch] [ebp-18h]
  _DWORD *parsed; // [esp+0h] [ebp-34h] BYREF

  slot_override = slotOverrides;
  g_ClipsEvaluationError = 0;
  saved_context = g_Instance_SlotInitInProgress;
  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  if ( !slotOverrides )
  {
    result = 1;
    goto done;
  }
  while ( 1 )
  {
    int slot_name_symbol;
    int pair_node;
    int value_expression;

    if ( Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)slot_override, parsed, a3, a4) == 1 || parsed[1] != 2 )
    {
      Rules_PrintErrorID((int)(intptr_t)aInsmngr, 9, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAVal_4, 0);
      Lexer_ErrorRecover(1);
      result = 0;
      goto done;
    }
    slot_name_symbol = parsed[2];
    slot_value = (int *)(uintptr_t)Instance_GetSlotValueBySymbol((int)(uintptr_t)theInstance, slot_name_symbol);
    saved_slot_value = slot_value;
    if ( !slot_value )
      break;
    g_Instance_SlotInitInProgress = 1;
    pair_node = *(_DWORD *)((uintptr_t)(unsigned int)slot_override + 10);
    value_expression = *(_DWORD *)((uintptr_t)(unsigned int)pair_node + 6);
    if ( g_Instance_UseMessageDispatchForInit )
    {
      MessageHandler_SendToInstanceAddress(*(_DWORD *)((uintptr_t)(unsigned int)*slot_value + 12), (int)(uintptr_t)theInstance, value_expression, 0, a4);
    }
    else if ( Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)(unsigned int)*slot_value << 30 >> 31, value_expression, parsed, a4) )
    {
      Instance_PutSlotValue(theInstance, slot_value, parsed, a4);
    }
    g_Instance_SlotInitInProgress = saved_context;
    if ( g_ClipsEvaluationError )
    {
      result = 0;
      goto done;
    }
    *((_BYTE *)saved_slot_value + 4) |= 2u;
    slot_override = *(_DWORD *)((uintptr_t)(unsigned int)pair_node + 10);
    if ( !slot_override )
    {
      result = 1;
      goto done;
    }
  }
  Rules_PrintErrorID((int)(intptr_t)aInsmngr, 13, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSlot_2, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)parsed[2] + 16), 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDoesNotExistIn, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)theInstance[7] + 16), 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__17, 0);
  Lexer_ErrorRecover(1);
  result = 0;
done:
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;

//----- (004AA7C0) --------------------------------------------------------
char  Instance_InitSlots(int theInstance, __int16 a2, double a3)
{
  int slot_value_offset; // ebp
  int slot_value; // esi
  int slot_descriptor; // eax
  int slot_value_table; // eax
  unsigned __int8 slot_flags; // dh
  unsigned __int8 descriptor_flags; // bl
  char result; // al
  int parsed_ptr; // ecx
  _DWORD *parsed; // [esp+0h] [ebp-34h] BYREF
  unsigned int i; // [esp+18h] [ebp-1Ch]

  result = 1;
  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  if ( (*(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) & 4) != 0 )
  {
    slot_value_offset = 0;
    for ( i = 0; ; ++i )
    {
      int class_record = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 44);
      if ( i >= *(_DWORD *)((uintptr_t)(unsigned int)class_record + 72) )
        break;
      slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 72);
      slot_value = *(_DWORD *)((uintptr_t)(unsigned int)slot_value_table + slot_value_offset);
      slot_flags = *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4);
      if ( (slot_flags & 2) != 0 )
      {
        *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) = slot_flags & 0xFD;
      }
      else
      {
        slot_descriptor = *(_DWORD *)(uintptr_t)(unsigned int)slot_value;
        descriptor_flags = *(_BYTE *)(uintptr_t)(unsigned int)slot_descriptor;
        if ( (descriptor_flags & 0x40) != 0 )
        {
          if ( Parser_ParseSlotDefaultOrRestriction(
                 ((unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)slot_descriptor << 30) >> 31,
                 *(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 16),
                 parsed,
                 a3) )
            result = Instance_PutSlotValue(
                       (_DWORD *)(uintptr_t)(unsigned int)theInstance,
                       (int *)(uintptr_t)(unsigned int)slot_value,
                       parsed,
                       a3);
        }
        else if ( ((descriptor_flags & 1) != 0
                && *(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 24) != 1)
               || (*(_BYTE *)((uintptr_t)(unsigned int)slot_descriptor + 1) & 1) != 0 )
        {
          if ( (*(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) & 1) != 0 )
          {
            Rules_PrintErrorID((int)(intptr_t)aInsmngr, 14, 0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOverrideRequir, 0);
            Output_Write(
              (int)(intptr_t)g_IO_LogicalNameTable_WError[0],
              *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 8) + 12) + 16),
              0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInInstance_0, 0);
            Output_Write(
              (int)(intptr_t)g_IO_LogicalNameTable_WError[0],
              *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theInstance + 28) + 16),
              0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__17, 0);
            result = Lexer_ErrorRecover(1);
          }
        }
        else
        {
          result = Instance_StoreSlotValueAndMatch(
                     (_DWORD *)(uintptr_t)(unsigned int)theInstance,
                     (int *)(uintptr_t)(unsigned int)slot_value,
                     a2,
                     (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 16),
                     a3);
        }
      }
      *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) &= ~1u;
      if ( (*(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) & 2) != 0 )
      {
        Output_Write(
          (int)(intptr_t)g_IO_LogicalNameTable_WError[0],
          *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theInstance + 28) + 16),
          0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInstanceDelete, 0);
        result = Lexer_ErrorRecover(1);
      }
      if ( g_ClipsEvaluationError )
        goto done;
      slot_value_offset += 4;
    }
    *(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) &= ~4u;
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmngr, 15, 0);
    Lexer_ErrorRecover(1);
    result = Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInitSlotsNotVa, 0);
  }
done:
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;

//----- (004AA980) --------------------------------------------------------
signed int  Instance_PrintWatchTrace(int traceString, int theInstance)
{
  int v2; // ecx
  int v3; // ecx

  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], traceString, theInstance);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aInstance, v2);
  return Instance_PrintNameOfClass((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], v3, 1);
}
// 4AA9A2: variable 'v2' is possibly undefined
// 4AA9AE: variable 'v3' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];

//----- (004AA9C0) --------------------------------------------------------
int __fastcall Rules_ParseObjectInstanceFunctionCall(int top, int readSource)
{
  int **Symbol; // eax
  int v4; // ecx
  int callType; // esi
  _WORD *v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int **v11; // eax
  int v12; // ecx
  int **v13; // eax
  int v14; // ecx
  int **v15; // eax
  int v16; // ecx
  int **v17; // eax
  int v18; // ecx
  int **v19; // eax
  int v20; // ecx
  int **v21; // eax
  int v22; // ecx
  int **v23; // eax
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  signed int v29; // eax
  int v30; // ecx
  int v31; // ecx
  signed int v32; // eax
  _WORD *parsedArgNode; // edi
  int **v34; // eax
  int v35; // edx
  int v36; // ecx
  int v37; // ecx
  int v38; // eax
  int v39; // ecx
  int v40; // edx
  int v41; // ecx
  int **v42; // eax
  signed int v43; // eax
  _DWORD *v44; // edx
  int v45; // ecx
  signed int v46; // eax
  int v47; // ecx
  int v48; // ecx
  _DWORD errorFlag[5]; // [esp+0h] [ebp-14h] BYREF

  errorFlag[3] = top;
  Symbol = Rules_MakeSymbol(aMakeInstance_0);
  if ( Symbol == *(int ***)(uintptr_t)(v4 + 2) || (v11 = Rules_MakeSymbol(aActiveMakeIn_0), v11 == *(int ***)(uintptr_t)(v12 + 2)) )
  {
    callType = 0;
  }
  else
  {
    v13 = Rules_MakeSymbol(aInitializeIn_1);
    if ( v13 == *(int ***)(uintptr_t)(v14 + 2) || (v15 = Rules_MakeSymbol(aActiveInitia_0), v15 == *(int ***)(uintptr_t)(v16 + 2)) )
    {
      callType = 1;
    }
    else
    {
      v17 = Rules_MakeSymbol(aModifyInstan_0);
      if ( v17 == *(int ***)(uintptr_t)(v18 + 2)
        || (v19 = Rules_MakeSymbol(aActiveModify_0), v19 == *(int ***)(uintptr_t)(v20 + 2))
        || (v21 = Rules_MakeSymbol(aMessageModif_0), v21 == *(int ***)(uintptr_t)(v22 + 2))
        || (v23 = Rules_MakeSymbol(aActiveMessag_0), v23 == *(int ***)(uintptr_t)(v24 + 2)) )
      {
        callType = 2;
      }
      else
      {
        callType = 3;
      }
    }
  }
  Rules_IncrementIndentDepth(3);
  errorFlag[0] = 0;
  if ( *v6 == 103 )
    *v6 = 10;
  else
    IO_OutWriteToken(asc_508954);
  v7 = Parser_ParseArgument(readSource, errorFlag, (int)(intptr_t)v6);
  *(_DWORD *)(uintptr_t)(v8 + 6) = v7;
  if ( errorFlag[0] )
    goto LABEL_8;
  if ( !v7 )
    goto LABEL_7;
  IO_OutWriteToken(asc_508954);
  if ( !callType )
  {
    if ( *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v26 + 6) == 2 && !strcmp_(v26, aOf_0) )
    {
      v32 = Parser_ParseArgument(readSource, errorFlag, v31);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v28 + 6) + 10) = v32;
      if ( errorFlag[0] == 1 )
        goto LABEL_8;
      parsedArgNode = (_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v28 + 6) + 10);
      if ( !parsedArgNode )
        goto LABEL_7;
      if ( *parsedArgNode != 2 || strcmp_(v28, aOf_0) )
      {
        *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v28 + 6) = 10;
        v34 = Rules_MakeSymbol(aGensym_1);
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v30 + 6) + 2) = v34;
LABEL_33:
        if ( !Rules_ResolveClassNameNode(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v30 + 6) + 10)) )
          goto LABEL_8;
        goto LABEL_34;
      }
    }
    else
    {
      Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 2 || strcmp_(v27, *(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16)) )
        goto LABEL_7;
      IO_OutWriteToken(asc_508954);
    }
    v29 = Parser_ParseArgument(readSource, errorFlag, v28);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v30 + 6) + 10) = v29;
    if ( errorFlag[0] )
      goto LABEL_8;
    if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v30 + 6) + 10) )
    {
LABEL_7:
      Parser_ReportSyntaxError();
LABEL_8:
      Lexer_ErrorRecover(1);
      AST_Free(v9);
      Rules_DecrementIndentDepth(3);
      return 0;
    }
    goto LABEL_33;
  }
  AST_Append(v26, v25);
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  if ( callType == 3 )
  {
    if ( g_ParserCurrentTokenType != 2 || strcmp_(v41, aTo_2) )
    {
      v42 = Rules_MakeSymbol(aGensym_1);
      v43 = AST_NewNode(10, (int)(intptr_t)v42);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v37 + 6) + 10) = v43;
      goto LABEL_35;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
    IO_OutWriteToken(asc_508954);
    v46 = Parser_ParseArgument(readSource, v44, v45);
    v35 = *(_DWORD *)(uintptr_t)(v36 + 6);
    *(_DWORD *)(uintptr_t)(v35 + 10) = v46;
    if ( errorFlag[0] )
      goto LABEL_8;
    if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v36 + 6) + 10) )
      goto LABEL_7;
LABEL_34:
    AST_Append(v36, v35);
    Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
LABEL_35:
    v38 = Rules_ParseObjectFunctionArgList(readSource, errorFlag, v37);
    v40 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v39 + 6) + 10);
    goto LABEL_36;
  }
  v38 = Rules_ParseObjectFunctionArgList(readSource, errorFlag, v41);
  v40 = *(_DWORD *)(uintptr_t)(v47 + 6);
LABEL_36:
  *(_DWORD *)(uintptr_t)(v40 + 10) = v38;
  if ( errorFlag[0] )
    goto LABEL_8;
  if ( g_ParserCurrentTokenType != 101 )
    goto LABEL_7;
  Rules_DecrementIndentDepth(3);
  return v48;
}
// 4AA9D5: variable 'v4' is possibly undefined
// 4AA9EB: variable 'v6' is possibly undefined
// 4AAA03: variable 'v8' is possibly undefined
// 4AAA2A: variable 'v9' is possibly undefined
// 4AAA4D: variable 'v12' is possibly undefined
// 4AAA5C: variable 'v14' is possibly undefined
// 4AAA75: variable 'v16' is possibly undefined
// 4AAA84: variable 'v18' is possibly undefined
// 4AAA9D: variable 'v20' is possibly undefined
// 4AAAAC: variable 'v22' is possibly undefined
// 4AAABB: variable 'v24' is possibly undefined
// 4AAAEB: variable 'v26' is possibly undefined
// 4AAB1B: variable 'v27' is possibly undefined
// 4AAB3E: variable 'v28' is possibly undefined
// 4AAB43: variable 'v30' is possibly undefined
// 4AAB8A: variable 'v31' is possibly undefined
// 4AABDC: variable 'v36' is possibly undefined
// 4AABDC: variable 'v35' is possibly undefined
// 4AABF1: variable 'v37' is possibly undefined
// 4AABF6: variable 'v39' is possibly undefined
// 4AAC4F: variable 'v25' is possibly undefined
// 4AACA0: variable 'v41' is possibly undefined
// 4AACD3: variable 'v44' is possibly undefined
// 4AACD3: variable 'v45' is possibly undefined
// 4AAD08: variable 'v47' is possibly undefined
// 4AAD1A: variable 'v48' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;
// 54E904: using guessed type int dword_54E904;

//----- (004AAD30) --------------------------------------------------------
int  Rules_ParseObjectFunctionArgList(int readSource, _DWORD *errorFlag, int a3)
{
  int top; // edi
  int tail; // ebp
  signed int argExpr; // eax
  signed int valueListNode; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  signed int slotNameExpr; // [esp+0h] [ebp-18h]

  top = 0;
  tail = 0;
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      *errorFlag = 0;
      argExpr = Parser_ParseArgument(readSource, errorFlag, a3);
      slotNameExpr = argExpr;
      if ( *errorFlag == 1 )
      {
        AST_Free(top);
        return 0;
      }
      if ( !argExpr )
      {
        Parser_ReportSyntaxError();
        *errorFlag = 1;
        AST_Free(top);
        Lexer_ErrorRecover(1);
        return 0;
      }
      valueListNode = AST_NewNode(2, g_ClipsTrueSymbol);
      *(_DWORD *)(uintptr_t)(v9 + 10) = valueListNode;
      if ( !Parser_CollectFunctionArguments(valueListNode, readSource, v9) )
        break;
      if ( top )
        *(_DWORD *)(uintptr_t)(tail + 10) = v10;
      else
        top = v10;
      tail = *(_DWORD *)(uintptr_t)(slotNameExpr + 10);
      AST_Append(v10, (int)(intptr_t)&g_ParserCurrentTokenType);
      Parser_NextToken(readSource, v11);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_8;
    }
    *errorFlag = 1;
    AST_Free(top);
    return 0;
  }
  else
  {
LABEL_8:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
    return top;
  }
}
// 4AAD55: variable 'a3' is possibly undefined
// 4AAD7A: variable 'v9' is possibly undefined
// 4AAD92: variable 'v10' is possibly undefined
// 4AADA6: variable 'v11' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E904: using guessed type int dword_54E904;

//----- (004AAE30) --------------------------------------------------------
int  Rules_ParseMakeInstanceNode(int topNode, int readSource)
{
  int override_head; // ebx
  int slot_override_parent; // edi
  int token_type; // edi
  int override_tail; // esi
  int value_node; // eax
  int create_symbol; // eax
  int trace_load_save; // eax

  trace_load_save = 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-enter\n");
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token1=%d\n", g_ParserCurrentTokenType);
  override_head = 0;
  if ( g_ParserCurrentTokenType != 8 && g_ParserCurrentTokenType != 2 )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(uintptr_t)(topNode + 6) = AST_NewNode(8, g_ClipsParserTokenValue);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-head-node\n");
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  token_type = g_ParserCurrentTokenType;
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] parse-make-instance-token2=%d symbol=%s\n",
      token_type,
      g_ClipsParserTokenValue ? (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16) : "<null>");
  if ( token_type != 2 )
    goto MAKE_INSTANCE_ERROR;
  if ( strcmp_((int)(intptr_t)aOf_0, *(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16)) )
    goto MAKE_INSTANCE_ERROR;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-of\n");
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] parse-make-instance-token3=%d symbol=%s\n",
      g_ParserCurrentTokenType,
      g_ClipsParserTokenValue ? (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16) : "<null>");
  if ( g_ParserCurrentTokenType != token_type )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(topNode + 6) + 10) = AST_NewNode(g_ParserCurrentTokenType, g_ClipsParserTokenValue);
  slot_override_parent = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(topNode + 6) + 10);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-before-class-lookup\n");
  if ( !Rules_ResolveClassNameNode(slot_override_parent) )
    goto MAKE_INSTANCE_ERROR;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-class-lookup\n");
  Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token4=%d\n", g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 100 )
    goto CHECK_END_TOKEN;
  while ( 1 )
  {
    Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType != 2 )
      goto SLOT_OVERRIDE_ERROR;
    *(_DWORD *)(uintptr_t)(slot_override_parent + 10) = AST_NewNode(2, g_ClipsParserTokenValue);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slot_override_parent + 10) + 10) = AST_NewNode(2, g_ClipsTrueSymbol);
    slot_override_parent = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slot_override_parent + 10) + 10);
    Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
    override_tail = 0;
    while ( g_ParserCurrentTokenType != 101 )
    {
      if ( g_ParserCurrentTokenType == 100 )
      {
        Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType != 2 )
          goto SLOT_OVERRIDE_ERROR;
        if ( strcmp_(*(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16), (int)(intptr_t)aCreate_0) )
          goto SLOT_OVERRIDE_ERROR;
        Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType != 101 )
          goto SLOT_OVERRIDE_ERROR;
        create_symbol = (int)(intptr_t)Rules_MakeSymbol(aCreate_0);
        value_node = AST_NewNode(10, create_symbol);
      }
      else
      {
        if ( g_ParserCurrentTokenType != 2
          && g_ParserCurrentTokenType != 3
          && g_ParserCurrentTokenType != 0
          && g_ParserCurrentTokenType != 1
          && g_ParserCurrentTokenType != 8 )
        {
          goto SLOT_OVERRIDE_ERROR;
        }
        value_node = AST_NewNode(g_ParserCurrentTokenType, g_ClipsParserTokenValue);
      }
      if ( override_head )
        *(_DWORD *)(uintptr_t)(override_tail + 10) = value_node;
      else
        override_head = value_node;
      override_tail = value_node;
      Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
    }
    *(_DWORD *)(uintptr_t)(slot_override_parent + 6) = override_head;
    Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
    override_head = 0;
    if ( g_ParserCurrentTokenType != 100 )
      break;
  }
CHECK_END_TOKEN:
  if ( g_ParserCurrentTokenType == 101 )
    return topNode;
SLOT_OVERRIDE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(topNode);
  AST_Free(override_head);
  return 0;
MAKE_INSTANCE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(topNode);
  return 0;
}
// 4AB03F: simplified comparisons for '$dword_54E8FC.4': ==0 || ==1 became <2u
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD64: using guessed type int dword_54DD64;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004AB0B0) --------------------------------------------------------
signed int  Rules_ResolveClassNameNode(int theExpression)
{
  int class_name; // edx
  int *class_record; // ebx
  int trace_load_save; // eax

  if ( *(_WORD *)(uintptr_t)theExpression != 2 )
    return 1;
  class_name = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theExpression + 2) + 16);
  trace_load_save = 0;
  class_record = Class_LookupInScope((_BYTE *)(uintptr_t)class_name);
  if ( class_record )
  {
    if ( Class_IsAbstract((int)(intptr_t)class_record) )
    {
      if ( trace_load_save )
        fprintf(
          stderr,
          "[menu-probe] class-lookup-cannot-create name=%s class=%p\n",
          class_name ? (const char *)(uintptr_t)(unsigned int)class_name : "<null>",
          (void *)(uintptr_t)(unsigned int)(intptr_t)class_record);
      Rules_PrintErrorID((int)(intptr_t)aInsmngr_0, 3, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotCreateIn, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], class_name, class_name);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__7, 0);
      return 0;
    }
    *(_WORD *)(uintptr_t)theExpression = 57;
    *(_DWORD *)(uintptr_t)(theExpression + 2) = class_record;
    return 1;
  }
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] class-lookup-failed name=%s\n",
      class_name ? (const char *)(uintptr_t)(unsigned int)class_name : "<null>");
  Rules_ReportCantFindItem((int)(intptr_t)aClass, class_name);
  return 0;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004AB150) --------------------------------------------------------
signed int Instance_RegisterModifyAndDuplicateFunctions(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx

  Rules_RegisterHostFunction(aModifyInstance, 117, (int)(intptr_t)aInactivemodify, (int)(intptr_t)Instance_ModifyInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveModifyIn, 117, (int)(intptr_t)aModifyinstance, (int)(intptr_t)Instance_ActiveModifyInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveModifyIn);
  Rules_RegisterHostFunction(aMessageModifyI, 117, v0, (int)(intptr_t)Instance_MessageModifyInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMessageM, 117, (int)(intptr_t)aMsgmodifyinsta, (int)(intptr_t)Instance_ActiveMessageModifyInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMessageM);
  Rules_RegisterHostFunction(aDuplicateInsta, 117, v1, (int)(intptr_t)Instance_DuplicateInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveDuplicat, 117, (int)(intptr_t)aDuplicateinsta, (int)(intptr_t)Instance_ActiveDuplicateInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveDuplicat);
  Rules_RegisterHostFunction(aMessageDuplica, 117, v2, (int)(intptr_t)Instance_MessageDuplicateInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMessageD, 117, (int)(intptr_t)aMsgduplicatein, (int)(intptr_t)Instance_ActiveMessageDuplicateInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMessageD);
  Rules_RegisterHostFunction(aDirectModify, 117, v3, (int)(intptr_t)Instance_DirectModifyFunction, 0);
  Rules_RegisterHostFunction(aMessageModify, 117, (int)(intptr_t)aMsgmodifymsgha, (int)(intptr_t)Instance_MessageModifyFunction, 0);
  Rules_RegisterHostFunction(aDirectDuplicat, 117, (int)(intptr_t)aDirectduplicat, (int)(intptr_t)Instance_DirectDuplicateFunction, 0);
  Rules_RegisterHostFunction(aMessageDupli_0, 117, (int)(intptr_t)aMsgduplicatems, (int)(intptr_t)Instance_MessageDuplicateFunction, 0);
  Rules_AddFunctionParser(aModifyInstance);
  Rules_AddFunctionParser(aMessageModifyI);
  Rules_AddFunctionParser(aDuplicateInsta);
  return Rules_AddFunctionParser(aMessageDuplica);
}
// 4AB1AE: variable 'v0' is possibly undefined
// 4AB1F3: variable 'v1' is possibly undefined
// 4AB238: variable 'v2' is possibly undefined
// 4AB27D: variable 'v3' is possibly undefined

//----- (004AB320) --------------------------------------------------------
_DWORD * Instance_ActiveModifyInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int savedGuardState; // ebp
  int *messageSymbol; // eax
  int v8; // edx
  int v9; // ecx
  int overrideCount; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD errorFlag[6]; // [esp+14h] [ebp-18h] BYREF

  overrides = (_DWORD *)(uintptr_t)Instance_ParseSlotOverrideArgs(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)(uintptr_t)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      savedGuardState = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      messageSymbol = Rules_FindSymbolEntry(aDirectModify_0);
      MessageHandler_SendToInstanceAddress((int)(intptr_t)messageSymbol, v8, v9, returnValue, a2);
      g_InstanceDirectMessageGuardActive = savedGuardState;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB371: variable 'v3' is possibly undefined
// 4AB3D8: variable 'v8' is possibly undefined
// 4AB3D8: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB400) --------------------------------------------------------
_DWORD * Instance_ActiveMessageModifyInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int savedGuardState; // ebp
  int *messageSymbol; // eax
  int v8; // edx
  int v9; // ecx
  int overrideCount; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD errorFlag[6]; // [esp+14h] [ebp-18h] BYREF

  overrides = (_DWORD *)(uintptr_t)Instance_ParseSlotOverrideArgs(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)(uintptr_t)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      savedGuardState = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      messageSymbol = Rules_FindSymbolEntry(aMessageModif_1);
      MessageHandler_SendToInstanceAddress((int)(intptr_t)messageSymbol, v8, v9, returnValue, a2);
      g_InstanceDirectMessageGuardActive = savedGuardState;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB451: variable 'v3' is possibly undefined
// 4AB4B8: variable 'v8' is possibly undefined
// 4AB4B8: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB4E0) --------------------------------------------------------
_DWORD * Instance_ActiveDuplicateInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int *messageSymbol; // eax
  int v7; // edx
  int v8; // ecx
  int newNameValue; // [esp+1Ch] [ebp-3Ch] BYREF
  int savedGuardState; // [esp+34h] [ebp-24h]
  int overrideCount; // [esp+38h] [ebp-20h] BYREF
  _DWORD errorFlag[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  overrides = (_DWORD *)(uintptr_t)Instance_ParseSlotOverrideArgs(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)(uintptr_t)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &newNameValue, 8, a2) )
  {
    savedGuardState = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    messageSymbol = Rules_FindSymbolEntry(aDirectDuplic_0);
    MessageHandler_SendToInstanceAddress((int)(intptr_t)messageSymbol, v7, v8, returnValue, a2);
    g_InstanceDirectMessageGuardActive = savedGuardState;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB536: variable 'v3' is possibly undefined
// 4AB5E2: variable 'v7' is possibly undefined
// 4AB5E2: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;
