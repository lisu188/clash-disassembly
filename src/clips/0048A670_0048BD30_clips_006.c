/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

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

  freeListHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = *freeListHead;
    newSlot = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSlot = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(uintptr_t)(newSlot + 28) = 0;
  *(_DWORD *)(uintptr_t)(newSlot + 40) = 0;
  *(_DWORD *)(uintptr_t)(newSlot + 36) = 0;
  v9 = (unsigned int)(fieldNode[3] << 18) >> 25 << 16;
  *(_BYTE *)(uintptr_t)(newSlot + 22) = 0;
  *(_DWORD *)(uintptr_t)(newSlot + 20) |= v9;
  Rules_ResetDataObjectValue(newSlot);
  minFields = fieldNode[8];
  v12 = v10;
  *(_BYTE *)(uintptr_t)(v10 + 20) = 0;
  if ( minFields > 0 )
    *(_DWORD *)(uintptr_t)(v10 + 20) |= (unsigned __int8)minFields;
  maxFields = fieldNode[10];
  if ( maxFields < 0 )
  {
    v18 = (unsigned __int8)*(_DWORD *)(uintptr_t)(v12 + 20);
    *(_BYTE *)(uintptr_t)(v12 + 21) = 0;
    *(_DWORD *)(uintptr_t)(v12 + 20) |= v18 << 8;
  }
  else
  {
    *(_BYTE *)(uintptr_t)(v12 + 21) = 0;
    maxFields = ((unsigned __int8)(maxFields - 1) << 8) | *(_DWORD *)(uintptr_t)(v12 + 20);
    *(_DWORD *)(uintptr_t)(v12 + 20) = maxFields;
  }
  nodeType = *fieldNode;
  if ( *fieldNode == 17 || nodeType == 15 )
  {
    *(_BYTE *)(uintptr_t)(v12 + 12) |= 1u;
  }
  else if ( nodeType == 18 || nodeType == 16 )
  {
    *(_BYTE *)(uintptr_t)(v12 + 12) |= 2u;
  }
  BYTE1(maxFields) = *(_BYTE *)(uintptr_t)(v12 + 12) & 0xBF;
  *(_BYTE *)(uintptr_t)(v12 + 12) = BYTE1(maxFields);
  *(_DWORD *)(uintptr_t)(v12 + 12) |= (withinMultifield & 1) << 6;
  slotNameChain = AST_AddHashedNodeChain((__int16 *)(uintptr_t)fieldNode[13], v12, maxFields);
  slotRecord[6] = slotNameChain;
  slotRecord[8] = lastSlot;
  if ( !precedingSlot )
  {
    if ( lastSlot )
    {
      *(_DWORD *)(uintptr_t)(lastSlot + 28) = slotRecord;
      return slotRecord;
    }
LABEL_11:
    *(_DWORD *)(uintptr_t)(g_ClipsDeftemplateBeingParsedPtr + 32) = slotRecord;
    return slotRecord;
  }
  if ( lastSlot )
  {
    prevChild = *(_DWORD *)(uintptr_t)(lastSlot + 28);
    slotRecord[10] = prevChild;
    if ( prevChild )
      *(_DWORD *)(uintptr_t)(prevChild + 36) = slotRecord;
    *(_DWORD *)(uintptr_t)(lastSlot + 28) = slotRecord;
    return slotRecord;
  }
  else
  {
    slotRecord[10] = *(_DWORD *)(uintptr_t)(g_ClipsDeftemplateBeingParsedPtr + 32);
    existingHeadSlot = *(_DWORD *)(uintptr_t)(g_ClipsDeftemplateBeingParsedPtr + 32);
    if ( !existingHeadSlot )
      goto LABEL_11;
    *(_DWORD *)(uintptr_t)(existingHeadSlot + 36) = slotRecord;
    *(_DWORD *)(uintptr_t)(g_ClipsDeftemplateBeingParsedPtr + 32) = slotRecord;
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
  if ( !*(_DWORD *)(uintptr_t)(v3 + 8) )
    *(_BYTE *)(uintptr_t)(v3 + 12) &= ~4u;
  if ( !*(_DWORD *)(uintptr_t)(slotList + 28) )
  {
    currentNode = slotList;
    while ( !*(_DWORD *)(uintptr_t)(currentNode + 36) && !*(_DWORD *)(uintptr_t)(currentNode + 40) )
    {
      nodeToFree = currentNode;
      parentNode = *(_DWORD *)(uintptr_t)(currentNode + 32);
      if ( parentNode )
      {
        parentFlags = *(_BYTE *)(uintptr_t)(parentNode + 12);
        *(_DWORD *)(uintptr_t)(parentNode + 28) = 0;
        if ( (parentFlags & 4) != 0 )
          parentNode = 0;
      }
      else
      {
        Rules_PatchDeftemplateSlotModuleRef(0, 0);
      }
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(nodeToFree + 24), parentNode);
      g_ClipsMemFreeListTemp = nodeToFree;
      *(_DWORD *)(uintptr_t)nodeToFree = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      if ( !currentNode )
        return result;
    }
    prevNode = *(_DWORD *)(uintptr_t)(currentNode + 36);
    if ( prevNode )
    {
      nextNode = *(_DWORD *)(uintptr_t)(currentNode + 40);
      freedNode = (_DWORD *)(uintptr_t)currentNode;
      *(_DWORD *)(uintptr_t)(prevNode + 40) = nextNode;
      if ( nextNode )
        *(_DWORD *)(uintptr_t)(nextNode + 36) = *(_DWORD *)(uintptr_t)(currentNode + 36);
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentNode + 24), currentNode);
      g_ClipsMemFreeListTemp = (int)(intptr_t)freedNode;
      *freedNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
    else
    {
      lastNode = currentNode;
      ownerNode = *(_DWORD *)(uintptr_t)(currentNode + 32);
      if ( ownerNode )
        *(_DWORD *)(uintptr_t)(ownerNode + 28) = *(_DWORD *)(uintptr_t)(lastNode + 40);
      else
        Rules_PatchDeftemplateSlotModuleRef(0, *(_DWORD *)(uintptr_t)(lastNode + 40));
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(lastNode + 40) + 36) = 0;
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(lastNode + 24), ownerNode);
      g_ClipsMemFreeListTemp = lastNode;
      *(_DWORD *)(uintptr_t)lastNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
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
int __fastcall Rules_PatchDeftemplateSlotModuleRef(int oldSlotHead CLASH95_UNUSED, int newPatternHead)
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
  while ( v5 != *(_DWORD *)(uintptr_t)(theDeftemplate + 32) )
  {
    theDeftemplate = Rules_GetNextDeftemplate(theDeftemplate);
    if ( !theDeftemplate )
      goto LABEL_5;
  }
  result = Module_EndEnum();
  *(_DWORD *)(uintptr_t)(v7 + 32) = newPatternHead;
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
    matchLink = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(i + 20);
    prevLink = 0;
    while ( matchLink )
    {
      if ( patternNode == matchLink[2] )
      {
        if ( prevLink )
        {
          *prevLink = *matchLink;
          g_ClipsMemFreeListTemp = (int)(intptr_t)matchLink;
          *matchLink = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          matchLink = (_DWORD *)(uintptr_t)*prevLink;
        }
        else
        {
          *(_DWORD *)(uintptr_t)(i + 20) = *matchLink;
          g_ClipsMemFreeListTemp = (int)(intptr_t)matchLink;
          *matchLink = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
          matchLink = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(i + 20);
        }
      }
      else
      {
        prevLink = matchLink;
        matchLink = (_DWORD *)(uintptr_t)*matchLink;
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
  fieldCount = *(_DWORD *)(uintptr_t)(theSegment + 6);
  hashValue = 0;
  fieldIndex = 0;
  if ( fieldCount > 0 )
  {
    multiplier = 29;
    do
    {
      switch ( *(_WORD *)(uintptr_t)fieldPtr )
      {
        case CLIPS_TYPE_FLOAT:
          value = *(_DWORD *)(uintptr_t)(fieldPtr + 2);
          fieldHash = multiplier * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case CLIPS_TYPE_INTEGER:
          value = *(_DWORD *)(uintptr_t)(fieldPtr + 2);
          fieldHash = multiplier * *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
          goto LABEL_5;
        case CLIPS_TYPE_SYMBOL:
        case CLIPS_TYPE_STRING:
        case CLIPS_TYPE_INSTANCE_NAME:
          value = *(_DWORD *)(uintptr_t)(fieldPtr + 2);
          fieldHash = multiplier
             * Rules_HashSymbolName(
                 (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)value + 16),
                 0x3F5u);
          goto LABEL_5;
        case CLIPS_TYPE_MULTIFIELD:
          fieldHash = Rules_HashFactFieldList(*(_DWORD *)(uintptr_t)(fieldPtr + 2));
          goto LABEL_5;
        case CLIPS_TYPE_EXTERNAL_ADDRESS:
        case CLIPS_TYPE_FACT_ADDRESS:
        case CLIPS_TYPE_INSTANCE_ADDRESS:
          fieldHash = multiplier * *(_DWORD *)(uintptr_t)(fieldPtr + 2);
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
  freeEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeEntry;
    result = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *result = v2;
  bucket_head = g_ClipsFactHashTable + 4 * hashValue;
  oldBucketHead = *(_DWORD *)(uintptr_t)bucket_head;
  *(_DWORD *)(uintptr_t)bucket_head = (int)(uintptr_t)result;
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
int Rules_GetFactDuplicationFlag(void)
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
int Rules_InitFactHashTable(void)
{
  int result; // eax

  g_ClipsFactHashTable = (int)(intptr_t)Mem_SmallBlockAlloc(0xFD4u);
  if ( !g_ClipsFactHashTable )
    IO_RunRouterExitCallbacks();
  for ( result = 0; result != 4052; result += 4 )
    *(_DWORD *)(uintptr_t)(g_ClipsFactHashTable + result) = 0;
  return result;
}
// 54E518: using guessed type int dword_54E518;

//----- (0048ACE0) --------------------------------------------------------
int  Rules_RunPeriodicCleanup(int result, int useHeuristics)
{
  int cleanupAllDepths; // ecx
  int cleanupFnNode; // edx
  int i; // esi
  int j; // edx

  cleanupAllDepths = result;
  cleanupFnNode = g_Rules_PeriodicFunctionListHead;
  /* loc_48ACF8: `mov edx, [edx+0Ch]` - the cursor advances from the node itself. */
  for ( i = -1; cleanupFnNode; cleanupFnNode = *(_DWORD *)(uintptr_t)(cleanupFnNode + 12) )
    result = (*(int (__fastcall **)(int))(uintptr_t)(cleanupFnNode + 4))(cleanupAllDepths);
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
    /* loc_48AD83: `mov edx, [edx+0Ch]` - same list-walk cursor. */
    for ( j = g_CLIPS_PeriodicFunctionListHead; j; j = *(_DWORD *)(uintptr_t)(j + 12) )
      (*(void (**)(void))(uintptr_t)(j + 4))();
    Rules_RemoveEphemeralAtoms();
    /* loc_48AD9A: `test ecx, ecx` - ecx is the first argument (cleanupAllDepths),
       the same flag that saved the depth above. */
    if ( cleanupAllDepths )
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

  freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  lastNode = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListEntry;
    newNode = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newNode = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *newNode = name;
  newNode[2] = priority;
  newNode[1] = theFunction;
  v9 = newNode;
  if ( !*listHead )
  {
    newNode[3] = 0;
    *listHead = (int)(intptr_t)newNode;
    return 1;
  }
  currentNode = *listHead;
  do
  {
    if ( priority >= *(_DWORD *)(uintptr_t)(currentNode + 8) )
      break;
    lastNode = currentNode;
    currentNode = *(_DWORD *)(uintptr_t)(currentNode + 12);
  }
  while ( currentNode );
  if ( !lastNode )
  {
    v9[3] = *listHead;
    *listHead = (int)(intptr_t)v9;
    return 1;
  }
  v9[3] = currentNode;
  *(_DWORD *)(uintptr_t)(lastNode + 12) = v9;
  return 1;
}
// 48AE6B: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048AED0) --------------------------------------------------------
signed int __fastcall Rules_RemoveNamedCallListEntry(int name CLASH95_UNUSED, _DWORD *listHead)
{
  _DWORD *currentNode; // ecx
  _DWORD *lastNode; // esi
  _DWORD *nodeToRemove; // ecx

  currentNode = (_DWORD *)(uintptr_t)*listHead;
  lastNode = 0;
  if ( !*listHead )
    return 0;
  while ( strcmp_(currentNode, *currentNode) )
  {
    lastNode = nodeToRemove;
    currentNode = (_DWORD *)(uintptr_t)nodeToRemove[3];
    if ( !currentNode )
      return 0;
  }
  if ( lastNode )
    lastNode[3] = nodeToRemove[3];
  else
    *listHead = nodeToRemove[3];
  g_ClipsMemFreeListTemp = (int)(intptr_t)nodeToRemove;
  *nodeToRemove = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
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
  theSymbol = Str_Intern(finalBuffer, (int)(intptr_t)finalBuffer);
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
  theSymbol = Str_Intern(appendedBuffer, (int)(intptr_t)appendedBuffer);
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
  int v9 CLASH95_UNUSED; // ecx
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
  if ( *(_BYTE *)(uintptr_t)(length + appendStr - 1) )
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

  freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  lastNode = 0;
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListEntry;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
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
      if ( priority >= *(int *)(uintptr_t)(currentNode + 8) )
        break;
      lastNode = currentNode;
      currentNode = *(_DWORD *)(uintptr_t)(currentNode + 12);
    }
    while ( currentNode );
    if ( lastNode )
    {
      newNode[3] = currentNode;
      *(_DWORD *)(uintptr_t)(lastNode + 12) = newNode;
      return (_DWORD *)(uintptr_t)listHead;
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
  while ( strcmp_(name, *(_DWORD *)(uintptr_t)current) )
  {
    previous = current;
    current = *(_DWORD *)(uintptr_t)(current + 12);
    if ( !current )
      return list_head;
  }
  *foundFlag = 1;
  if ( previous )
    *(_DWORD *)(uintptr_t)(previous + 12) = *(_DWORD *)(uintptr_t)(current + 12);
  else
    list_head = *(_DWORD *)(uintptr_t)(current + 12);
  g_ClipsMemFreeListTemp = current;
  *(_DWORD *)(uintptr_t)current = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return list_head;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048B2E0) --------------------------------------------------------
int __fastcall Rules_RegisterDeftemplateFunctions(int a1, int a2)
{
  int v2; // ecx

  Rules_AddResetFunction((int)(intptr_t)aDeftemplate_0, (int)(intptr_t)Noop_DeftemplateResetCallback, 0);
  Rules_AddClearFunction((int)(intptr_t)aDeftemplate_0, (int)(intptr_t)Rules_InternInitialFactSymbol, 0);
  Rules_AddSaveFunction((int)(intptr_t)aDeftemplate_0, (int)(intptr_t)Rules_ClearDeftemplateModuleData, 10);
  Rules_RegisterHostFunction(aGetDeftemplate, 109, v2, (int)(intptr_t)Rules_GetDeftemplateListCommand, (int)(intptr_t)a01w_1);
  Rules_RegisterHostFunction(aUndeftemplate, 118, (int)(intptr_t)aUndeftemplatec, (int)(intptr_t)Rules_UndeftemplateCommand, (int)(intptr_t)a11w_1);
  Rules_RegisterHostFunction(aDeftemplateMod, 119, (int)(intptr_t)aDeftemplatemod, (int)(intptr_t)Rules_DeftemplateModuleCommand, (int)(intptr_t)a11w_1);
  Rules_RegisterHostFunction(aListDeftemplat, 118, (int)(intptr_t)aListdeftemplat, (int)(intptr_t)Rules_ListDeftemplatesCommand, (int)(intptr_t)a01w_1);
  Rules_RegisterHostFunction(aPpdeftemplate, 118, (int)(intptr_t)aPpdeftemplatec, (int)(intptr_t)Rules_PPDeftemplateCommand, (int)(intptr_t)a11w_1);
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

  initialFactSymbol = Str_Intern(aInitialFact_2, (int)(intptr_t)this);
  return Rules_CreateDeftemplateRecord((int)(intptr_t)initialFactSymbol, v2);
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
  return Rules_UndefconstructCommand((int)(intptr_t)this, g_DeftemplateConstructType);
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
  return Rules_GetConstructModuleCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (0048B490) --------------------------------------------------------
int __thiscall Rules_PPDeftemplateCommand(void *this)
{
  return Rules_PPConstructCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_DeftemplateConstructType);
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
  return *(_DWORD *)(uintptr_t)(theTemplate + 24) << 30 >> 31;
}

//----- (0048B510) --------------------------------------------------------
int  Rules_SetFactWatchFlag(char newState, int theTemplate)
{
  int result; // eax

  *(_BYTE *)(uintptr_t)(theTemplate + 24) &= ~2u;
  result = 2 * (newState & 1);
  *(_DWORD *)(uintptr_t)(theTemplate + 24) |= result;
  return result;
}

//----- (0048B530) --------------------------------------------------------
signed int  Rules_ToggleFactWatchFlag(int newState, int argExprs, double a3)
{
  return Rules_ApplyWatchFlagCommand(g_DeftemplateConstructType, newState, (int)(intptr_t)Rules_GetFactWatchFlag, argExprs, a3, (void (*)(void))Rules_SetFactWatchFlag);
}
// 48B500: using guessed type int sub_48B500();
// 54E650: using guessed type int dword_54E650;

//----- (0048B550) --------------------------------------------------------
signed int  Rules_WatchPrintFactsState(int code, int argExprs, double a3)
{
  return Rules_ListWatchFlagStatus(g_DeftemplateConstructType, code, (int)(intptr_t)Rules_GetFactWatchFlag, argExprs, a3, (void (*)(void))Rules_SetFactWatchFlag);
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
      result = strcmp_(*(_DWORD *)(uintptr_t)watch_item, name);
      if ( !result )
        break;
      if ( priority < *(_DWORD *)(uintptr_t)(watch_item + 12) )
        previous_watch_item = watch_item;
      watch_item = *(_DWORD *)(uintptr_t)(watch_item + 24);
      if ( !watch_item )
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = *freeListEntry;
      newWatchItem = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newWatchItem = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
    }
    *newWatchItem = name;
    newWatchItem[2] = flag;
    newWatchItem[3] = priority;
    newWatchItem[1] = code;
    newWatchItem[4] = accessFunc;
    newWatchItem[5] = printFunc;
    if ( previous_watch_item )
    {
      newWatchItem[6] = *(_DWORD *)(uintptr_t)(previous_watch_item + 24);
      *(_DWORD *)(uintptr_t)(previous_watch_item + 24) = (int)(intptr_t)newWatchItem;
      return 1;
    }
    else
    {
      newWatchItem[6] = g_WatchItemListHead;
      g_WatchItemListHead = (int)(intptr_t)newWatchItem;
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
        *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentItem + 4) = newState;
      if ( *(_DWORD *)(uintptr_t)(currentItem + 16) && !(*(int (__fastcall **)(int, unsigned int))(uintptr_t)(currentItem + 16))(currentItem, newState) )
        break;
      currentItem = *(_DWORD *)(uintptr_t)(currentItem + 24);
      if ( !currentItem )
        return 1;
    }
  }
  else
  {
    namedItem = (_DWORD *)(uintptr_t)g_WatchItemListHead;
    if ( !g_WatchItemListHead )
      return 0;
    while ( strcmp_(namedItem, *namedItem) )
    {
      namedItem = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v7 + 24);
      if ( !namedItem )
        return 0;
    }
    if ( !argExprs )
      *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v7 + 4) = newState;
    if ( !*(_DWORD *)(uintptr_t)(v7 + 16) || (*(int (__fastcall **)(int, unsigned int))(uintptr_t)(v7 + 16))(v7, newState) )
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
  while ( strcmp_(itemName, *(_DWORD *)(uintptr_t)watch_item) )
  {
    watch_item = *(_DWORD *)(uintptr_t)(watch_item + 24);
    if ( !watch_item )
      return -1;
  }
  value_pointer = *(_DWORD *)(uintptr_t)(watch_item + 4);
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
    currentItem = (_DWORD *)(uintptr_t)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      while ( strcmp_(currentItem, *currentItem) )
      {
        currentItem = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 24);
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
    watchItem = Rules_FindWatchItem(*(_DWORD *)(uintptr_t)(argValue[2] + 16), recognized);
    if ( recognized[0] )
    {
      if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) || watchItem && *(_DWORD *)(uintptr_t)(watchItem + 16) )
      {
        return Rules_SetWatchItemState(1u, v4, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10));
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Rules_ExpectedCountError((int)(intptr_t)aWatch, 1);
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      return Parser_ReportError(v5, (int)(intptr_t)aWatchableSymbo);
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
    watchItem = Rules_FindWatchItem(*(_DWORD *)(uintptr_t)(argValue[2] + 16), recognized);
    if ( recognized[0] )
    {
      if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) || watchItem && *(_DWORD *)(uintptr_t)(watchItem + 16) )
      {
        return Rules_SetWatchItemState(0, v4, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10));
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Rules_ExpectedCountError((int)(intptr_t)aUnwatch, 1);
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      return Parser_ReportError(v5, (int)(intptr_t)aWatchableSymbo);
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
  if ( *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) )
  {
    result = Lexer_ParseValueList(1, &argValue, 2, a2);
    if ( result )
    {
      theItem = (int *)(uintptr_t)Rules_FindWatchItem(v7, recognized);
      if ( recognized[0] && theItem )
      {
        if ( !theItem[5] && *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) )
        {
          Lexer_ErrorRecover(1);
          return Rules_ExpectedCountError((int)(intptr_t)aListWatchItems, 1);
        }
        else
        {
          Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, *theItem, (int)(intptr_t)theItem);
          if ( *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v9 + 4) )
            itemStateText = aOn;
          else
            itemStateText = aOff;
          result = Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)itemStateText, v9);
          if ( *(_DWORD *)(uintptr_t)(v11 + 20) )
          {
            result = (*(int (__fastcall **)(int, _DWORD))(uintptr_t)(v11 + 20))(v11, *(_DWORD *)(uintptr_t)(v11 + 8));
            if ( !result )
              return Lexer_ErrorRecover(1);
          }
        }
      }
      else
      {
        Lexer_ErrorRecover(1);
        return Parser_ReportError(v12, (int)(intptr_t)aWatchableSymbo);
      }
    }
  }
  else
  {
    currentItem = (int *)(uintptr_t)g_WatchItemListHead;
    if ( g_WatchItemListHead )
    {
      do
      {
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, *currentItem, (int)(intptr_t)currentItem);
        if ( *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 4) )
          stateText = aOn;
        else
          stateText = aOff;
        result = Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)stateText, v4);
        currentItem = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6 + 24);
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
signed int Rules_RegisterWatchFunctions(void)
{
  Rules_RegisterHostFunction(aWatch, 118, (int)(intptr_t)aWatchcommand, (int)(intptr_t)Rules_WatchCommand, (int)(intptr_t)a1W);
  Rules_RegisterHostFunction(aUnwatch, 118, (int)(intptr_t)aUnwatchcommand, (int)(intptr_t)Rules_UnwatchCommand, (int)(intptr_t)a1W);
  Rules_RegisterHostFunction(aListWatchItems, 118, (int)(intptr_t)aListwatchitems, (int)(intptr_t)Rules_ListWatchItemsCommand, (int)(intptr_t)a0W);
  IO_AddRouter((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], 1000, (int)(intptr_t)Rules_WatchAlwaysTrueStub, (int)(intptr_t)Rules_WatchNameMatches, 0, 0, 0);
  return IO_DeactivateRouter((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0]);
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
int Rules_WatchAlwaysTrueStub(void)
{
  return 1;
}
// 48BBF0: using guessed type int sub_48BBF0();

//----- (0048BC00) --------------------------------------------------------
signed int Rules_RegisterFactQueryFunctions(void)
{
  Rules_RegisterHostFunction(aFactExistp, 98, (int)(intptr_t)aFactexistpfunc, (int)(intptr_t)Rules_CheckFactExistp, (int)(intptr_t)a11z);
  Rules_RegisterHostFunction(aFactRelation, 119, (int)(intptr_t)aFactrelationfu, (int)(intptr_t)Rules_GetFactRelationName, (int)(intptr_t)a11z);
  Rules_RegisterHostFunction(aFactSlotValue, 117, (int)(intptr_t)aFactslotvaluef, (int)(intptr_t)Lexer_ParseSlotConstraint, (int)(intptr_t)a22Zw);
  Rules_RegisterHostFunction(aFactSlotNames, 117, (int)(intptr_t)aFactslotnamesf, (int)(intptr_t)Lexer_ParseFieldSpec, (int)(intptr_t)a11z);
  return Rules_RegisterHostFunction(aGetFactList, 109, (int)(intptr_t)aGetfactlistfun, (int)(intptr_t)Rules_GetFactListFunction, (int)(intptr_t)a01w_0);
}

//----- (0048BCA0) --------------------------------------------------------
int  Rules_GetFactRelationName(double a1)
{
  int v1; // ecx
  int theFact; // eax

  if ( Lexer_TokenExpect((int)(intptr_t)aFactRelation, 0, 1) == -1 )
    return g_ClipsFalseSymbol;
  theFact = Rules_ResolveFactArgument(1, v1, 0, a1);
  if ( !theFact )
    return g_ClipsFalseSymbol;
  else
    return *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theFact + 16);
}
// 48BCCC: variable 'v1' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BCF0) --------------------------------------------------------
int  Rules_CheckFactExistp(double a1)
{
  int result; // eax
  int v2; // ecx
  int theFact; // eax

  result = Lexer_TokenExpect((int)(intptr_t)aFactExistp, 0, 1);
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
    return *(char *)(uintptr_t)(result + 29) >= 0;
  return result;
}
