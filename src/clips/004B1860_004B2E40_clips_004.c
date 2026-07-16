/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004B1860) --------------------------------------------------------
int Class_FindUnusedSlotNameID(void)
{
  int candidateID; // ecx
  unsigned int bucketIndex; // ebx
  int bucketOffset; // esi
  int i; // eax

  candidateID = 0;
LABEL_2:
  bucketIndex = 0;
  bucketOffset = 0;
  do
  {
    for ( i = *(_DWORD *)(bucketOffset + g_Defclass_SlotNameHashTablePtr); i; i = *(_DWORD *)(i + 20) )
    {
      if ( candidateID == *(_DWORD *)(i + 8) )
        break;
    }
    if ( i )
    {
      ++candidateID;
      goto LABEL_2;
    }
    ++bucketIndex;
    bucketOffset += 4;
  }
  while ( bucketIndex < 0xA7 );
  return candidateID;
}
// 4B1898: conditional instruction was optimized away because ebx.4<A7u
// 51AD70: using guessed type int dword_51AD70;

//----- (004B18C0) --------------------------------------------------------
int  Class_ReleaseSlotIDMapEntry(int classID, int a2)
{
  int idCursor; // ecx
  unsigned int scanIndex; // ebx
  int result; // eax
  int tableOffset; // esi
  int cursorOffset; // esi
  int shrinkPending; // edi
  int oldTableSize; // [esp+0h] [ebp-20h]

  idCursor = classID;
  scanIndex = classID + 1;
  result = g_ClipsDefclassIdTable;
  tableOffset = 4 * scanIndex;
  *(_DWORD *)(g_ClipsDefclassIdTable + 4 * idCursor) = 0;
  while ( scanIndex < (unsigned __int16)g_ClipsDefclassIdCount )
  {
    if ( *(_DWORD *)(g_ClipsDefclassIdTable + tableOffset) )
      return result;
    tableOffset += 4;
    ++scanIndex;
  }
  cursorOffset = 4 * idCursor;
  shrinkPending = 0;
  while ( !*(_DWORD *)(g_ClipsDefclassIdTable + cursorOffset) )
  {
    result = (unsigned __int16)idCursor / 30;
    g_ClipsDefclassIdCount = idCursor;
    if ( !((unsigned __int16)idCursor % 30) )
    {
      a2 = (unsigned __int16)idCursor;
      if ( !shrinkPending )
      {
        shrinkPending = 1;
        oldTableSize = (unsigned __int16)idCursor + 30;
      }
    }
    if ( !idCursor )
      break;
    cursorOffset -= 4;
    --idCursor;
  }
  if ( shrinkPending )
  {
    result = (int)Mem_Realloc((char *)g_ClipsDefclassIdTable, 4 * oldTableSize, 4 * a2);
    g_ClipsDefclassIdTable = result;
  }
  return result;
}
// 4B1971: variable 'v8' is possibly undefined
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;

//----- (004B1990) --------------------------------------------------------
int  Rules_EvaluatePatternQueryExpression(_DWORD *returnValue, double a2)
{
  int savedDelayFlag; // eax
  double v4; // st7
  int v5; // ecx
  int v6; // ecx

  savedDelayFlag = Rules_SetObjectPatternMatchDelay(1, a2);
  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), returnValue, savedDelayFlag, v4);
  if ( !g_ClipsEvaluationError )
    return Rules_SetObjectPatternMatchDelay(v5, v4);
  Rules_SetEvaluationErrorFlag(0);
  Lexer_ErrorRecover(0);
  Rules_SetObjectPatternMatchDelay(v6, v4);
  return Lexer_ErrorRecover(1);
}
// 4B19A8: variable 'v4' is possibly undefined
// 4B19C6: variable 'v6' is possibly undefined
// 4B19DA: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;

//----- (004B19F0) --------------------------------------------------------
int  Rules_SetObjectPatternMatchDelay(int delayFlag, double a2)
{
  int oldFlag; // ecx

  oldFlag = g_Rules_ObjectMatchDelayFlag;
  if ( delayFlag )
  {
    g_Rules_ObjectMatchDelayFlag = 1;
  }
  else
  {
    g_Rules_ObjectMatchDelayFlag = 0;
    Rules_ObjectMatchAction(0, 0, -1, a2);
  }
  return oldFlag;
}
// 4B1A05: variable 'v2' is possibly undefined
// 51AEB4: using guessed type int dword_51AEB4;

//----- (004B1A40) --------------------------------------------------------
int Rules_GetObjectPatternNetworkRoot(void)
{
  return g_Rules_ObjectPatternNetworkRoot;
}
// 51AEAC: using guessed type int dword_51AEAC;

//----- (004B1A50) --------------------------------------------------------
int Rules_GetReactiveRuleList(void)
{
  return g_ReactiveRuleListHead;
}
// 51AEB0: using guessed type int dword_51AEB0;

//----- (004B1A60) --------------------------------------------------------
int  Rules_SetObjectPatternNetworkRoot(int result)
{
  g_Rules_ObjectPatternNetworkRoot = result;
  return result;
}
// 51AEAC: using guessed type int dword_51AEAC;

//----- (004B1A70) --------------------------------------------------------
int  Rules_SetReactiveRuleList(int result)
{
  g_ReactiveRuleListHead = result;
  return result;
}
// 51AEB0: using guessed type int dword_51AEB0;

//----- (004B1A80) --------------------------------------------------------
void  Rules_ObjectMatchAction(unsigned __int16 *actionType, _DWORD *theInstance, signed int slotNameID, double a4)
{
  unsigned __int16 *slotBitmap; // ebx

  if ( !g_Rules_JoinOperationInProgress )
  {
    g_Rules_ObjectMatchTimeTag = g_Rules_EntityTimeTagCounter;
    g_Rules_JoinOperationInProgress = 1;
    ++g_Rules_EntityTimeTagCounter;
    if ( theInstance )
    {
      if ( g_Rules_ObjectMatchDelayFlag )
      {
        Rules_EnqueueObjectMatchAction(actionType, (uintptr_t)theInstance, slotNameID);
        goto LABEL_6;
      }
      if ( !actionType )
        goto LABEL_5;
      if ( (unsigned int)actionType <= 1 )
      {
        Rules_AssertNewObjectIntoNetwork((int)theInstance, a4);
        goto LABEL_6;
      }
      if ( actionType == (unsigned __int16 *)2 )
      {
        Rules_RetractObjectPatternMatches(theInstance, 0, a4);
      }
      else
      {
LABEL_5:
        slotBitmap = Rules_GrowSlotBitmapSetBit(0, slotNameID);
        Rules_ReassertObjectSlotChange(theInstance, slotBitmap, a4);
        Mem_SmallBlockFree(slotBitmap, ((int)*slotBitmap >> 3) + 3);
      }
    }
LABEL_6:
    Rules_FlushQueuedObjectMatchActions(a4);
    g_Rules_JoinOperationInProgress = 0;
    Rules_FlushPendingDependencyDestructors();
  }
}
// 4B1AD1: variable 'v5' is possibly undefined
// 51A954: using guessed type int dword_51A954;
// 51A998: using guessed type int dword_51A998;
// 51AEB4: using guessed type int dword_51AEB4;
// 51AEBC: using guessed type int dword_51AEBC;

//----- (004B1B30) --------------------------------------------------------
int Rules_ResetRuleMarkCounters(void)
{
  int result; // eax
  _DWORD *ruleCursor; // edx

  result = g_RuleTraversalMarkCounter + 1;
  if ( g_RuleTraversalMarkCounter + 1 < (unsigned int)g_RuleTraversalMarkCounter )
  {
    result = g_ReactiveRuleListHead;
    g_RuleTraversalMarkCounter = 0;
    ruleCursor = (_DWORD *)g_ReactiveRuleListHead;
    if ( g_ReactiveRuleListHead )
    {
      do
      {
LABEL_3:
        result = ruleCursor[7];
        ruleCursor[4] = 0;
        if ( result )
        {
          while ( *(_DWORD *)(result + 4) )
          {
            *(_DWORD *)(result + 4) = 0;
            result = *(_DWORD *)(result + 20);
            if ( !result )
            {
              ruleCursor = (_DWORD *)ruleCursor[9];
              if ( ruleCursor )
                goto LABEL_3;
              return result;
            }
          }
        }
        ruleCursor = (_DWORD *)ruleCursor[9];
      }
      while ( ruleCursor );
    }
  }
  return result;
}
// 51AEB0: using guessed type int dword_51AEB0;
// 51AEB8: using guessed type int dword_51AEB8;

//----- (004B1B90) --------------------------------------------------------
unsigned __int16 * Rules_EnqueueObjectMatchAction(unsigned __int16 *result, uintptr_t theInstance, signed int slotNameID)
{
  uintptr_t change_kind; // ebp
  uintptr_t instance; // esi
  uintptr_t node; // ecx
  uintptr_t previous; // ebx
  uintptr_t bitmap; // edx/eax
  uintptr_t new_node; // edi/eax

  change_kind = (uintptr_t)result;
  instance = theInstance;
  node = (uintptr_t)(unsigned int)g_ClipsObjectMatchQueueHead;
  previous = 0;
  while ( node )
  {
    if ( instance == (uintptr_t)(unsigned int)*(_DWORD *)(node + 4) )
    {
      if ( *(_DWORD *)node == 1 )
      {
        if ( change_kind == 2 )
        {
          if ( previous )
            *(_DWORD *)(previous + 12) = *(_DWORD *)(node + 12);
          else
            g_ClipsObjectMatchQueueHead = *(_DWORD *)(node + 12);
          --*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(node + 4) + 40);
          return (unsigned __int16 *)Rules_FreeQueuedObjectMatchNode((_DWORD *)node);
        }
        return result;
      }
      if ( change_kind == 2 )
      {
        bitmap = (uintptr_t)(unsigned int)*(_DWORD *)(node + 8);
        *(_DWORD *)node = (int)change_kind;
        if ( bitmap )
        {
          Mem_SmallBlockFree((void *)bitmap, (((int)*(unsigned __int16 *)bitmap) >> 3) + 3);
          *(_DWORD *)(node + 8) = 0;
        }
        return result;
      }
      bitmap = (uintptr_t)Rules_GrowSlotBitmapSetBit(
        (unsigned __int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8),
        slotNameID);
      *(_DWORD *)(node + 8) = (int)bitmap;
      return (unsigned __int16 *)bitmap;
    }
    previous = node;
    node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 12);
  }

  if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)(uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
    new_node = (uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
  }
  else
  {
    new_node = (uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *(_DWORD *)new_node = (int)change_kind;
  *(_DWORD *)(new_node + 12) = 0;
  if ( change_kind == 3 )
    bitmap = (uintptr_t)Rules_GrowSlotBitmapSetBit(0, slotNameID);
  else
    bitmap = 0;
  *(_DWORD *)(new_node + 8) = (int)bitmap;
  *(_DWORD *)(new_node + 4) = (int)instance;
  ++*(_DWORD *)(instance + 40);
  if ( previous )
    *(_DWORD *)(previous + 12) = (int)new_node;
  else
    g_ClipsObjectMatchQueueHead = (int)new_node;
  return (unsigned __int16 *)bitmap;
}
// 51AEA8: using guessed type int dword_51AEA8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1CA0) --------------------------------------------------------
unsigned __int16 * Rules_GrowSlotBitmapSetBit(unsigned __int16 *oldBitmap, signed int bitIndex)
{
  unsigned __int16 *bitmap; // [esp+0h] [ebp-18h]
  unsigned __int16 bit_capacity; // [esp+4h] [ebp-14h]
  int allocation_size; // edx
  int old_size; // edx
  char *target_byte; // edi

  if ( oldBitmap && bitIndex <= *oldBitmap )
  {
    bitmap = oldBitmap;
  }
  else
  {
    bit_capacity = 2 * bitIndex;
    allocation_size = ((int)bit_capacity >> 3) + 3;
    bitmap = (unsigned __int16 *)Mem_SmallBlockAlloc(allocation_size);
    Mem_AllocArray((_BYTE *)bitmap, allocation_size);
    if ( oldBitmap )
    {
      old_size = ((int)*oldBitmap >> 3) + 3;
      qmemcpy(bitmap, oldBitmap, old_size);
      Mem_SmallBlockFree(oldBitmap, old_size);
    }
    *bitmap = bit_capacity;
  }
  target_byte = (char *)bitmap + ((bitIndex - (__CFSHL__(bitIndex >> 31, 3) + 8 * (bitIndex >> 31))) >> 3);
  target_byte[2] |= 1 << (bitIndex % 8);
  return bitmap;
}

//----- (004B1D80) --------------------------------------------------------
int  Rules_FreeQueuedObjectMatchNode(_DWORD *theNode)
{
  _DWORD *node; // ecx
  _DWORD *slotBitmap; // edx
  int result; // eax

  node = theNode;
  slotBitmap = (_DWORD *)theNode[2];
  if ( slotBitmap )
    Mem_SmallBlockFree(slotBitmap, ((int)*(unsigned __int16 *)slotBitmap >> 3) + 3);
  g_ClipsMemFreeListTemp = (int)node;
  *node = *(_DWORD *)(g_ClipsMemoryTable + 64);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 4B1D90: variable 'v1' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1DD0) --------------------------------------------------------
int  Rules_FlushQueuedObjectMatchActions(double a1)
{
  uintptr_t queued_change; // ecx
  uintptr_t instance; // eax
  uintptr_t slot_bitmap; // edx
  int change_kind; // eax
  int result; // eax

  result = 0;
  if ( g_ClipsObjectMatchQueueHead )
  {
    while ( g_ClipsObjectMatchQueueHead && !g_Rules_ObjectMatchDelayFlag )
    {
      queued_change = (uintptr_t)(unsigned int)g_ClipsObjectMatchQueueHead;
      g_ClipsObjectMatchQueueHead = *(_DWORD *)(queued_change + 12);
      change_kind = *(_DWORD *)queued_change;
      instance = (uintptr_t)(unsigned int)*(_DWORD *)(queued_change + 4);
      slot_bitmap = (uintptr_t)(unsigned int)*(_DWORD *)(queued_change + 8);
      if ( change_kind == 1 )
      {
        Rules_AssertNewObjectIntoNetwork((int)instance, a1);
      }
      else if ( change_kind == 2 )
      {
        Rules_RetractObjectPatternMatches((_DWORD *)instance, (unsigned __int16 *)slot_bitmap, a1);
      }
      else
      {
        Rules_ReassertObjectSlotChange((_DWORD *)instance, (unsigned __int16 *)slot_bitmap, a1);
      }
      --*(_DWORD *)(instance + 40);
      result = Rules_FreeQueuedObjectMatchNode((_DWORD *)queued_change);
    }
  }
  return result;
}
// 51AEA8: using guessed type int dword_51AEA8;
// 51AEB4: using guessed type int dword_51AEB4;

//----- (004B1E40) --------------------------------------------------------
char  Rules_MarkDependentRulesForSlotChange(unsigned __int16 *slotBitmap)
{
  uintptr_t rule; // ebx
  uintptr_t slot_record; // edx
  unsigned int slot_id; // [esp+0h] [ebp-1Ch]
  unsigned int slot_byte; // edi
  unsigned char slot_mask; // cl
  uintptr_t rule_bitmap_owner; // eax
  unsigned int rule_bitmap; // eax
  uintptr_t dependency_owner; // eax
  unsigned int dependency_bitmap; // edx
  uintptr_t dependent; // eax
  int mark_id; // ebp

  Rules_ResetRuleMarkCounters();
  ++g_RuleTraversalMarkCounter;
  rule = (uintptr_t)(unsigned int)g_ReactiveRuleListHead;
  slot_record = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 44);
  slot_id = *(unsigned __int16 *)(slot_record + 24);
  slot_mask = 1 << (slot_id & 7);
  slot_byte = slot_id >> 3;
  while ( rule )
  {
    if ( !g_IncrementalResetInProgress || (*(_BYTE *)(rule + 12) & 8) != 0 )
    {
      rule_bitmap_owner = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 20);
      rule_bitmap = rule_bitmap_owner ? *(_DWORD *)(rule_bitmap_owner + 16) : 0;
      if ( rule_bitmap
        && *(unsigned __int16 *)(uintptr_t)(unsigned int)rule_bitmap >= slot_id
        && (*(_BYTE *)((uintptr_t)(unsigned int)rule_bitmap + slot_byte + 2) & slot_mask) != 0 )
      {
        if ( slotBitmap )
        {
          dependency_owner = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 24);
          dependency_bitmap = dependency_owner ? *(_DWORD *)(dependency_owner + 16) : 0;
          if ( !dependency_bitmap
            || !Rules_BitmapsIntersect(slotBitmap, (unsigned __int16 *)(uintptr_t)(unsigned int)dependency_bitmap) )
            goto next_rule;
        }
        mark_id = g_RuleTraversalMarkCounter;
        *(_DWORD *)(rule + 16) = mark_id;
        for ( dependent = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 28);
              dependent;
              dependent = (uintptr_t)(unsigned int)*(_DWORD *)(dependent + 20) )
        {
          if ( *(_DWORD *)(dependent + 4) == mark_id )
            break;
          *(_DWORD *)(dependent + 4) = mark_id;
        }
      }
    }
next_rule:
    rule = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 36);
  }
  return 0;
}
// 51AEB0: using guessed type int dword_51AEB0;
// 51AEB8: using guessed type int dword_51AEB8;
// 51B354: using guessed type int dword_51B354;
// 51B478: using guessed type int dword_51B478;

//----- (004B1F50) --------------------------------------------------------
signed int  Rules_BitmapsIntersect(unsigned __int16 *bitmap1, unsigned __int16 *bitmap2)
{
  unsigned __int16 minBits; // ax
  unsigned __int16 i; // dx

  minBits = *bitmap1;
  if ( *bitmap1 >= (int)*bitmap2 )
    minBits = *bitmap2;
  for ( i = 0; i <= (int)minBits >> 3; ++i )
  {
    if ( (*((_BYTE *)bitmap2 + i + 2) & *((_BYTE *)bitmap1 + i + 2)) != 0 )
      return 1;
  }
  return 0;
}

//----- (004B1FC0) --------------------------------------------------------
_DWORD * Rules_TraverseObjectPatternNetwork(_DWORD *result, _DWORD *patternNode, int endMark, double a4)
{
  int offset; // esi
  _DWORD *patternCursor; // ecx
  unsigned int slotNameID; // ebx
  int savedFieldCount; // ebp
  int slotValue; // eax
  int savedSlotNode; // [esp+0h] [ebp-14h]

  offset = (int)result;
  patternCursor = patternNode;
  while ( patternCursor )
  {
    while ( 1 )
    {
      if ( g_RuleTraversalMarkCounter == patternCursor[1] )
      {
        slotNameID = patternCursor[2];
        if ( slotNameID > 1 )
        {
          if ( !g_ObjectPatternActiveClassNode || *(_DWORD *)(*(_DWORD *)(*(_DWORD *)g_ObjectPatternActiveClassNode + 8) + 8) != slotNameID )
          {
            slotValue = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72)
                           + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60) + 4 * patternCursor[2])
                           - 4);
            g_ObjectPatternActiveClassNode = slotValue;
            offset = 0;
            if ( (**(_BYTE **)slotValue & 2) != 0 )
              g_ObjectPatternMatchFieldCount = *(_DWORD *)(*(_DWORD *)(slotValue + 8) + 6);
            else
              g_ObjectPatternMatchFieldCount = 1;
          }
        }
        else
        {
          offset = 0;
          g_ObjectPatternActiveClassNode = 0;
          g_ObjectPatternMatchFieldCount = 1;
        }
        savedSlotNode = g_ObjectPatternActiveClassNode;
        savedFieldCount = g_ObjectPatternMatchFieldCount;
        Rules_MatchObjectPatternNode(offset, (int)patternCursor, endMark, a4);
        g_ObjectPatternMatchFieldCount = savedFieldCount;
        g_ObjectPatternActiveClassNode = savedSlotNode;
      }
      result = (_DWORD *)(*patternCursor & 1);
      if ( result == (_DWORD *)1 )
        break;
      patternCursor = (_DWORD *)patternCursor[7];
      if ( !patternCursor )
        return result;
    }
    *(_BYTE *)patternCursor &= ~1u;
    result = patternCursor;
    patternCursor = (_DWORD *)patternCursor[7];
    if ( patternCursor )
    {
      while ( patternCursor[2] == result[2] && *patternCursor << 21 >> 24 == *result << 21 >> 24 )
      {
        patternCursor = (_DWORD *)patternCursor[7];
        if ( !patternCursor )
          return result;
      }
    }
  }
  return result;
}
// 4B1FE5: simplified comparisons for 'ebx.4': !=0 && !=1 became >=2u
// 4B2021: variable 'v5' is possibly undefined
// 51AEB8: using guessed type int dword_51AEB8;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;
// 51B480: using guessed type int dword_51B480;

//----- (004B2110) --------------------------------------------------------
int  Rules_MatchObjectPatternNode(int offset, int patternNode, int endMark, double a4)
{
  int whichField; // edx
  int fieldPosition; // ebp
  int *alphaNodeList; // eax
  int result; // eax
  int networkTest; // ebx
  _DWORD *freeNode; // ebx
  _DWORD *newMarker; // eax
  int slotNameRecord; // edx
  _DWORD *theMarker; // edi
  int markerPosition; // edx
  int savedSlotNode; // [esp+4h] [ebp-20h]
  int savedFieldCount; // [esp+8h] [ebp-1Ch]
  int i; // [esp+10h] [ebp-14h]

  whichField = *(_DWORD *)patternNode << 21 >> 24;
  fieldPosition = offset + whichField;
  if ( !g_ObjectPatternActiveClassNode )
  {
    if ( *(_DWORD *)(patternNode + 12) )
    {
      result = Rules_EvaluatePatternConstraint(fieldPosition, 0, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4);
      if ( !result )
        return result;
    }
    if ( !*(_DWORD *)(patternNode + 32) )
      return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
    alphaNodeList = *(int **)(patternNode + 32);
LABEL_5:
    Rules_AssertObjectPatternMatch(alphaNodeList, a4);
    return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
  }
  if ( (*(_BYTE *)patternNode & 2) != 0 )
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 80);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
      *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeNode;
      newMarker = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newMarker = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    *newMarker = whichField;
    slotNameRecord = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)g_ObjectPatternActiveClassNode + 8) + 12);
    newMarker[4] = 0;
    newMarker[1] = slotNameRecord;
    newMarker[2] = fieldPosition;
    theMarker = newMarker;
    if ( g_ObjectPatternMarkerListHead )
      *(_DWORD *)(endMark + 16) = newMarker;
    else
      g_ObjectPatternMarkerListHead = (int)newMarker;
    if ( (*(_BYTE *)patternNode & 4) != 0 )
    {
      newMarker[3] = g_ObjectPatternMatchFieldCount;
      if ( !*(_DWORD *)(patternNode + 12) || Rules_EvaluatePatternConstraint(fieldPosition, (int)newMarker, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4) )
      {
        if ( *(_DWORD *)(patternNode + 32) )
          Rules_AssertObjectPatternMatch(*(int **)(patternNode + 32), a4);
        Rules_TraverseObjectPatternNetwork(0, *(_DWORD *)(patternNode + 16), (int)theMarker, a4);
      }
    }
    else
    {
      savedFieldCount = g_ObjectPatternMatchFieldCount;
      savedSlotNode = g_ObjectPatternActiveClassNode;
      markerPosition = newMarker[2];
      newMarker[3] = markerPosition - 1;
      for ( i = savedFieldCount - markerPosition - (*(_DWORD *)patternNode << 13 >> 24) + 2; i > 0; ++theMarker[3] )
      {
        if ( !*(_DWORD *)(patternNode + 12) || Rules_EvaluatePatternConstraint(fieldPosition, (int)theMarker, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4) )
        {
          if ( *(_DWORD *)(patternNode + 32) )
            Rules_AssertObjectPatternMatch(*(int **)(patternNode + 32), a4);
          Rules_TraverseObjectPatternNetwork(offset + theMarker[3] - fieldPosition, *(_DWORD *)(patternNode + 16), (int)theMarker, a4);
          g_ObjectPatternMatchFieldCount = savedFieldCount;
          g_ObjectPatternActiveClassNode = savedSlotNode;
        }
        --i;
      }
    }
    if ( theMarker == (_DWORD *)g_ObjectPatternMarkerListHead )
      g_ObjectPatternMarkerListHead = 0;
    else
      *(_DWORD *)(endMark + 16) = 0;
    g_ClipsMemFreeListTemp = (int)theMarker;
    *theMarker = *(_DWORD *)(g_ClipsMemoryTable + 80);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
  }
  else
  {
    networkTest = *(_DWORD *)(patternNode + 12);
    if ( !networkTest || (result = Rules_EvaluatePatternConstraint(offset + whichField, 0, (_BYTE *)patternNode, networkTest, a4)) != 0 )
    {
      if ( !*(_DWORD *)(patternNode + 32) )
        return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
      alphaNodeList = *(int **)(patternNode + 32);
      goto LABEL_5;
    }
  }
  return result;
}
// 51B47C: using guessed type int dword_51B47C;
// 51B480: using guessed type int dword_51B480;
// 51B484: using guessed type int dword_51B484;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B2350) --------------------------------------------------------
int * Rules_AssertObjectPatternMatch(int *result, double a2)
{
  int pattern; // edi
  int partial_match; // esi
  int link_record; // eax
  int free_record; // ebx
  int join; // ecx

  pattern = (int)(uintptr_t)result;
  while ( pattern )
  {
    if ( g_RuleTraversalMarkCounter == *(_DWORD *)((uintptr_t)(unsigned int)pattern + 16) )
    {
      ++*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 40);
      partial_match = Rules_AppendExpressionValueNode(g_ClipsObjectReteCurrentInstance, (_DWORD *)(uintptr_t)(unsigned int)g_ObjectPatternMarkerListHead, (signed int *)(uintptr_t)(unsigned int)pattern);
      free_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
      if ( free_record )
      {
        g_ClipsMemFreeListTemp = free_record;
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = *(_DWORD *)(uintptr_t)(unsigned int)free_record;
        link_record = g_ClipsMemFreeListTemp;
      }
      else
      {
        link_record = Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      *(_DWORD *)(uintptr_t)(unsigned int)link_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 16);
      *(_DWORD *)((uintptr_t)(unsigned int)link_record + 8) = pattern;
      *(_DWORD *)((uintptr_t)(unsigned int)link_record + 4) = partial_match;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 16) = link_record;
      join = *(_DWORD *)((uintptr_t)(unsigned int)pattern + 8);
      while ( join )
      {
        result = Rules_DriveJoinNetwork(
                   (int *)(uintptr_t)(unsigned int)partial_match,
                   (char *)(uintptr_t)(unsigned int)join,
                   1,
                   a2);
        join = *(_DWORD *)((uintptr_t)(unsigned int)join + 32);
      }
    }
    pattern = *(_DWORD *)((uintptr_t)(unsigned int)pattern + 32);
  }
  return result;
}
// 51AEB8: using guessed type int dword_51AEB8;
// 51B478: using guessed type int dword_51B478;
// 51B484: using guessed type int dword_51B484;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B2410) --------------------------------------------------------
int  Rules_EvaluatePatternConstraint(int objectSlotField, int selfSlotMarker, _BYTE *patternNode, int theTest, double a5)
{
  int testHead; // eax
  int orClause; // esi
  int result; // eax
  int savedExpression; // ebp
  _BYTE *v11; // ecx
  int andClause; // esi
  _DWORD evalResult[2]; // [esp+0h] [ebp-28h] BYREF
  int resultValue; // [esp+8h] [ebp-20h]
  int objectSlotFieldCopy; // [esp+18h] [ebp-10h]

  objectSlotFieldCopy = objectSlotField;
  if ( *(_WORD *)theTest == 50 )
  {
    savedExpression = g_ClipsCurrentExpression;
    g_ClipsCurrentExpression = theTest;
    result = Rules_EvalObjectSlotBoundVariableEqual(*(_DWORD *)(theTest + 2), (int)evalResult, (int)patternNode, a5);
    g_ClipsCurrentExpression = savedExpression;
    if ( result )
    {
      if ( **(char **)(*(_DWORD *)(theTest + 2) + 16) < 0 )
        *v11 |= 1u;
      return 1;
    }
  }
  else
  {
    testHead = *(_DWORD *)(theTest + 2);
    if ( testHead == g_ClipsSymbolOr )
    {
      orClause = *(_DWORD *)(theTest + 6);
      if ( orClause )
      {
        while ( !Rules_EvaluatePatternConstraint(objectSlotFieldCopy, selfSlotMarker, (int)patternNode, orClause, a5) )
        {
          *patternNode &= ~1u;
          orClause = *(_DWORD *)(orClause + 10);
          if ( !orClause )
            return 0;
        }
        result = 1;
        *patternNode &= ~1u;
      }
      else
      {
        return 0;
      }
    }
    else if ( testHead == g_Clips_SymbolAnd )
    {
      andClause = *(_DWORD *)(theTest + 6);
      if ( andClause )
      {
        while ( 1 )
        {
          result = Rules_EvaluatePatternConstraint(objectSlotFieldCopy, selfSlotMarker, (int)patternNode, andClause, a5);
          if ( !result )
            break;
          *patternNode &= ~1u;
          andClause = *(_DWORD *)(andClause + 10);
          if ( !andClause )
            return 1;
        }
        *patternNode &= ~1u;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      g_ClipsHaltExecution = 0;
      if ( Parser_ParseForm((__int16 *)theTest, evalResult, (int)patternNode, a5) )
      {
        Rules_PrintObjectPatternNetworkError();
        g_ClipsEvaluationError = 0;
        g_ClipsHaltExecution = 0;
        return 0;
      }
      else if ( resultValue == g_ClipsFalseSymbol && evalResult[1] == 2 )
      {
        return g_ClipsFalseSymbol ^ resultValue;
      }
      else
      {
        return 1;
      }
    }
  }
  return result;
}
// 4B248F: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DD70: using guessed type int dword_54DD70;
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (004B2550) --------------------------------------------------------
_DWORD * Rules_AssertNewObjectIntoNetwork(int theInstance, double a2)
{
  *(_DWORD *)(theInstance + 12) = g_Rules_ObjectMatchTimeTag;
  g_ClipsObjectReteCurrentInstance = theInstance;
  g_ObjectPatternActiveClassNode = 0;
  Rules_MarkDependentRulesForSlotChange(0);
  return Rules_TraverseObjectPatternNetwork(0, (_DWORD *)g_Rules_ObjectPatternNetworkRoot, 0, a2);
}
// 51AEAC: using guessed type int dword_51AEAC;
// 51AEBC: using guessed type int dword_51AEBC;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;

//----- (004B2590) --------------------------------------------------------
_DWORD * Rules_ReassertObjectSlotChange(_DWORD *theInstance, unsigned __int16 *slotBitmap, double a3)
{
  theInstance[3] = g_Rules_ObjectMatchTimeTag;
  Rules_RetractObjectPatternMatches(theInstance, slotBitmap, a3);
  g_ClipsObjectReteCurrentInstance = (int)(uintptr_t)theInstance;
  g_ObjectPatternActiveClassNode = 0;
  Rules_MarkDependentRulesForSlotChange(slotBitmap);
  return Rules_TraverseObjectPatternNetwork(0, (_DWORD *)g_Rules_ObjectPatternNetworkRoot, 0, a3);
}
// 51AEAC: using guessed type int dword_51AEAC;
// 51AEBC: using guessed type int dword_51AEBC;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;

//----- (004B25D0) --------------------------------------------------------
_DWORD * Rules_RetractObjectPatternMatches(_DWORD *result, unsigned __int16 *slotBitmap, double a3)
{
  uintptr_t instance; // ebx
  unsigned int current_link; // ecx
  unsigned int previous_link; // esi
  unsigned int removed_links; // edi
  unsigned int next_link; // eax
  unsigned int pattern; // eax
  unsigned int dependency; // edx
  unsigned int dependency_bitmap; // edx
  unsigned int link; // ecx
  int saved_rule_head; // edx

  instance = (uintptr_t)result;
  if ( !slotBitmap )
  {
    current_link = *(_DWORD *)(instance + 16);
    if ( current_link )
    {
      for ( link = current_link; link; link = *(_DWORD *)(uintptr_t)link )
        --*(_DWORD *)(instance + 40);
      result = (_DWORD *)Rules_RetractFactFromNetwork((_DWORD *)(uintptr_t)current_link, a3);
      *(_DWORD *)(instance + 16) = 0;
    }
    return result;
  }

  current_link = *(_DWORD *)(instance + 16);
  previous_link = 0;
  removed_links = 0;
  while ( current_link )
  {
    uintptr_t link_record = (uintptr_t)current_link;
    pattern = *(_DWORD *)(link_record + 8);
    dependency = pattern ? *(_DWORD *)((uintptr_t)pattern + 24) : 0;
    dependency_bitmap = dependency ? *(_DWORD *)((uintptr_t)dependency + 16) : 0;
    if ( dependency_bitmap
      && Rules_BitmapsIntersect(slotBitmap, (unsigned __int16 *)(uintptr_t)dependency_bitmap) )
    {
      --*(_DWORD *)(instance + 40);
      next_link = *(_DWORD *)link_record;
      if ( previous_link )
        *(_DWORD *)(uintptr_t)previous_link = next_link;
      else
        *(_DWORD *)(instance + 16) = next_link;
      *(_DWORD *)link_record = removed_links;
      removed_links = current_link;
      current_link = next_link;
    }
    else
    {
      previous_link = current_link;
      current_link = *(_DWORD *)link_record;
    }
  }

  if ( removed_links )
  {
    saved_rule_head = *(_DWORD *)(instance + 4);
    *(_DWORD *)(instance + 4) = 0;
    result = (_DWORD *)Rules_RetractFactFromNetwork((_DWORD *)(uintptr_t)removed_links, a3);
    *(_DWORD *)(instance + 4) = saved_rule_head;
  }
  return result;
}

//----- (004B2680) --------------------------------------------------------
signed int Rules_PrintObjectPatternNetworkError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int slotNameSymbol; // eax
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // ecx
  int v10; // ecx
  int *v11; // ecx
  int v12; // ecx

  Rules_PrintErrorID((int)aObjrtmch, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_2, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCurrentlyAct_0, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 28) + 16), v2);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509714, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aProblemResid_2, v4);
  slotNameSymbol = Class_GetSlotNameByID(*(_DWORD *)(v5 + 8));
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotNameSymbol + 16), v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField, v8);
  Rules_PrintLongInteger((int)v9, *v9 << 21 >> 24);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509740, v10);
  Rules_PrintObjectPatternErrorDetail(1, v11, (int)v11);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509740, v12);
}
// 4B26A0: variable 'v0' is possibly undefined
// 4B26AF: variable 'v1' is possibly undefined
// 4B26C4: variable 'v2' is possibly undefined
// 4B26D3: variable 'v3' is possibly undefined
// 4B26E2: variable 'v4' is possibly undefined
// 4B26E7: variable 'v5' is possibly undefined
// 4B26F7: variable 'v7' is possibly undefined
// 4B2706: variable 'v8' is possibly undefined
// 4B2718: variable 'v9' is possibly undefined
// 4B2727: variable 'v10' is possibly undefined
// 4B2733: variable 'v11' is possibly undefined
// 4B2742: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B478: using guessed type int dword_51B478;

//----- (004B2750) --------------------------------------------------------
int  Rules_PrintObjectPatternErrorDetail(int result, int *patternNode, int j)
{
  int stopAfterFirst; // esi
  int *i; // ebx
  int alphaNode; // edx
  _DWORD *v6; // ecx
  int v7; // ecx
  int v8; // ecx

  stopAfterFirst = result;
  for ( i = patternNode; i; i = (int *)i[7] )
  {
    alphaNode = i[8];
    if ( alphaNode )
    {
      for ( j = *(_DWORD *)(alphaNode + 8); j; j = *(_DWORD *)(v8 + 32) )
      {
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfPattern, j);
        Rules_PrintLongInteger((int)v6, *v6 << 16 >> 25);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInRuleS, v7);
        Rules_PrintJoinNetworkSharingReport();
      }
    }
    result = Rules_PrintObjectPatternErrorDetail(0, i[4], j);
    if ( stopAfterFirst )
      break;
  }
  return result;
}
// 4B2792: variable 'v6' is possibly undefined
// 4B27A1: variable 'v7' is possibly undefined
// 4B27AF: variable 'v8' is possibly undefined
// 4B27BB: variable 'j' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B2840) --------------------------------------------------------
BOOL  Method_CharRestrictionAllowsType(int typeChar, char *constraints)
{
  BOOL result; // eax
  char restrictionFlags; // bh
  char typeFlagByte; // dh

  if ( !constraints || (*constraints & 1) != 0 )
    return 1;
  switch ( typeChar )
  {
    case 'a':
      return *constraints < 0;
    case 'b':
    case 'c':
    case 'w':
      return (*constraints & 2) != 0;
    case 'd':
    case 'f':
      return (*constraints & 8) != 0;
    case 'i':
    case 'l':
      return (*constraints & 0x10) != 0;
    case 'j':
      restrictionFlags = *constraints;
      return (*constraints & 2) != 0 || (restrictionFlags & 4) != 0 || (restrictionFlags & 0x20) != 0;
    case 'k':
      typeFlagByte = *constraints;
      return (*constraints & 2) != 0 || (typeFlagByte & 4) != 0;
    case 'm':
      return constraints[1] < 0;
    case 'n':
      return (*constraints & 0x10) != 0 || (*constraints & 8) != 0;
    case 'o':
      if ( (*constraints & 0x20) != 0 )
        return 1;
      goto LABEL_29;
    case 's':
      return (*constraints & 4) != 0;
    case 'v':
LABEL_29:
      result = 0;
      break;
    case 'x':
      if ( (*constraints & 0x40) != 0 )
        return 1;
      result = 0;
      break;
    default:
      return 1;
  }
  return result;
}

//----- (004B2900) --------------------------------------------------------
BOOL  Method_TypeCodeAllowsRestriction(BOOL result, int constraints)
{
  if ( result == 105 )
    return 0;
  if ( !constraints )
    return 1;
  if ( (*(_DWORD *)constraints & 1) == 1 )
    return 1;
  if ( result == 2 && (*(_BYTE *)constraints & 2) == 0 || result == 3 && (*(_BYTE *)constraints & 4) == 0 )
    return 0;
  if ( result || (*(_BYTE *)constraints & 8) != 0 )
    return (result != 1 || (*(_BYTE *)constraints & 0x10) != 0)
        && (result != 8 || (*(_BYTE *)constraints & 0x20) != 0)
        && (result != 7 || (*(_BYTE *)constraints & 0x40) != 0)
        && (result != 5 || *(char *)constraints < 0)
        && (result != 6 || (*(_BYTE *)(constraints + 1) & 1) != 0);
  return result;
}

//----- (004B2990) --------------------------------------------------------
BOOL  Method_ParamCountInRange(int number, int constraints)
{
  int minRestriction; // ecx
  int minExpr; // ebx
  int maxRestriction; // ebp
  int maxExpr; // ecx
  BOOL result; // eax

  result = 1;
  if ( constraints )
  {
    minRestriction = *(_DWORD *)(constraints + 18);
    if ( minRestriction )
    {
      minExpr = *(_DWORD *)(minRestriction + 2);
      if ( minExpr != g_Clips_NegativeInfinitySymbol && number < *(_DWORD *)(minExpr + 16) )
        return 0;
    }
    maxRestriction = *(_DWORD *)(constraints + 22);
    if ( maxRestriction )
    {
      maxExpr = *(_DWORD *)(maxRestriction + 2);
      if ( maxExpr != g_ClipsPositiveInfinitySymbol && number > *(_DWORD *)(maxExpr + 16) )
        return 0;
    }
  }
  return result;
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B29E0) --------------------------------------------------------
BOOL  Method_ParamRangeInBounds(int minCount, int maxCount, int constraints)
{
  int maxRestriction; // esi
  int minRestriction; // eax
  int minExpr; // ecx
  BOOL result; // eax

  result = 1;
  if ( constraints )
  {
    maxRestriction = *(_DWORD *)(constraints + 22);
    if ( maxRestriction )
    {
      if ( g_ClipsPositiveInfinitySymbol != *(_DWORD *)(maxRestriction + 2) && minCount > *(_DWORD *)(*(_DWORD *)(maxRestriction + 2) + 16) )
        return 0;
    }
    minRestriction = *(_DWORD *)(constraints + 18);
    if ( minRestriction )
    {
      if ( maxCount != -1 )
      {
        minExpr = *(_DWORD *)(minRestriction + 2);
        if ( minExpr != g_Clips_NegativeInfinitySymbol && maxCount < *(_DWORD *)(minExpr + 16) )
          return 0;
      }
    }
  }
  return result;
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B2A60) --------------------------------------------------------
signed int  Method_QueryRestrictionAllowsType(int type, int value, int constraints)
{
  char v5; // ah
  __int16 *restrictionList; // eax
  signed int result; // eax
  char v8; // ah
  char v9; // ah
  char v10; // dh
  char v11; // dh

  if ( !constraints )
    return 1;
  switch ( type )
  {
    case 0:
      v5 = *(_BYTE *)(constraints + 1);
      if ( (v5 & 0x10) == 0 && (v5 & 2) == 0 )
        goto LABEL_22;
      goto LABEL_5;
    case 1:
      v11 = *(_BYTE *)(constraints + 1);
      if ( (v11 & 0x20) == 0 && (v11 & 2) == 0 )
        goto LABEL_22;
      goto LABEL_5;
    case 2:
      v8 = *(_BYTE *)(constraints + 1);
      if ( (v8 & 4) != 0 || (v8 & 2) != 0 )
        goto LABEL_5;
      return 1;
    case 3:
      v10 = *(_BYTE *)(constraints + 1);
      if ( (v10 & 8) != 0 || (v10 & 2) != 0 )
        goto LABEL_5;
      return 1;
    case 8:
      v9 = *(_BYTE *)(constraints + 1);
      if ( (v9 & 0x40) != 0 || (v9 & 2) != 0 )
      {
LABEL_5:
        restrictionList = *(__int16 **)(constraints + 6);
        if ( !restrictionList )
          return 0;
        while ( *restrictionList != type || value != *(_DWORD *)(restrictionList + 1) )
        {
          restrictionList = *(__int16 **)(restrictionList + 5);
          if ( !restrictionList )
            return 0;
        }
LABEL_22:
        result = 1;
      }
      else
      {
        result = 1;
      }
      break;
    default:
      goto LABEL_22;
  }
  return result;
}

//----- (004B2B10) --------------------------------------------------------
signed int  Rules_ValueSatisfiesRangeConstraint(unsigned int type, int value, int constraints)
{
  __int16 *minList; // esi
  __int16 *maxList; // edi

  if ( !constraints || type > 1 )
    return 1;
  minList = *(__int16 **)(constraints + 10);
  maxList = *(__int16 **)(constraints + 14);
  if ( !minList )
    return 0;
  while ( !Rules_CompareBoundedCEValues(type, value, *(_DWORD *)(minList + 1), *minList) || Rules_CompareBoundedCEValues(type, value, *(_DWORD *)(maxList + 1), *maxList) == 1 )
  {
    minList = *(__int16 **)(minList + 5);
    maxList = *(__int16 **)(maxList + 5);
    if ( !minList )
      return 0;
  }
  return 1;
}
// 4B2B23: simplified comparisons for 'eax.4': !=1 && !=0 became >=2u

//----- (004B2B90) --------------------------------------------------------
signed int  Rules_PrintConstraintViolationMessage(
        int theWhat,
        int thePlace,
        int thePattern,
        int commandFlag,
        int theSlot,
        int theField,
        int violationType,
        int theConstraint,
        int printPrelude)
{
  int v12; // ecx
  int v13; // ecx
  char *preludeMessage; // edx
  int v15; // ecx
  int v16; // ecx
  char *violationMessage; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx

  v12 = violationType;
  if ( !printPrelude )
    goto LABEL_12;
  if ( violationType == 4 )
  {
    Rules_PrintErrorID((int)aCstrnchk_1, 1, 1);
    preludeMessage = aTheFunctionRet;
  }
  else
  {
    if ( !theWhat )
      goto LABEL_5;
    Rules_PrintErrorID((int)aCstrnchk_1, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], theWhat, v19);
    preludeMessage = asc_50979C;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)preludeMessage, v13);
LABEL_5:
  if ( thePlace )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundIn_0, v12);
    if ( commandFlag )
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe, v15);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], thePlace, v15);
    if ( commandFlag )
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCommand_0, v12);
  }
  if ( thePattern > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInCe, v12);
    Rules_PrintLongInteger(v16, thePattern);
  }
LABEL_12:
  switch ( v12 )
  {
    case 1:
    case 4:
      violationMessage = aDoesNotMatchTh;
LABEL_14:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)violationMessage, v12);
      break;
    case 2:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotFallInT, 2);
      Rules_PrintConstraintRange((int)g_IO_LogicalNameTable_WError[0], theConstraint);
      break;
    case 3:
      violationMessage = aDoesNotMatch_0;
      goto LABEL_14;
    case 5:
      violationMessage = aDoesNotSatisfy;
      goto LABEL_14;
  }
  if ( theSlot )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForSlot, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theSlot + 16), v20);
  }
  else if ( theField > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForField, v12);
    Rules_PrintLongInteger(v21, theField);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__29, v12);
}
// 4B2BD2: variable 'v13' is possibly undefined
// 4B2BE8: variable 'v12' is possibly undefined
// 4B2BFB: variable 'v15' is possibly undefined
// 4B2C3C: variable 'v16' is possibly undefined
// 4B2D35: variable 'v21' is possibly undefined
// 4B2CA5: variable 'v19' is possibly undefined
// 4B2D15: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B2D40) --------------------------------------------------------
signed int  Rules_PrintConstraintRange(int logicalName, int theConstraint)
{
  int minList; // edx
  int v4; // ecx
  int v5; // ecx
  int maxList; // edx

  minList = *(_DWORD *)(theConstraint + 10);
  if ( g_Clips_NegativeInfinitySymbol == *(_DWORD *)(minList + 2) )
    Output_Write(logicalName, *(_DWORD *)(g_Clips_NegativeInfinitySymbol + 16), logicalName);
  else
    Rules_PrintFieldExprList(logicalName, (__int16 *)minList);
  Output_Write(v4, (int)aTo_1, v4);
  maxList = *(_DWORD *)(theConstraint + 14);
  if ( g_ClipsPositiveInfinitySymbol == *(_DWORD *)(maxList + 2) )
    return Output_Write(v5, *(_DWORD *)(g_ClipsPositiveInfinitySymbol + 16), v5);
  else
    return Rules_PrintFieldExprList(v5, (__int16 *)maxList);
}
// 4B2D64: variable 'v4' is possibly undefined
// 4B2D7C: variable 'v5' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B2DA0) --------------------------------------------------------
signed int  Rules_CheckFieldAgainstConstraint(_DWORD *theData, int theConstraint)
{
  int fieldIndex; // esi
  __int16 *fieldPtr; // ecx
  signed int result; // eax
  int v7; // ecx

  if ( !theConstraint )
    return 0;
  if ( theData[1] != 4 )
  {
    if ( Method_ParamCountInRange(1, theConstraint) )
      return Rules_CheckValueAgainstConstraint(theData[1], theData[2], theConstraint);
    else
      return 5;
  }
  if ( !Method_ParamCountInRange(theData[4] - theData[3] + 1, theConstraint) )
    return 5;
  fieldIndex = theData[3];
  if ( fieldIndex > theData[4] )
    return 0;
  fieldPtr = (__int16 *)(6 * fieldIndex + theData[2] + 14);
  while ( 1 )
  {
    result = Rules_CheckValueAgainstConstraint(*fieldPtr, *(_DWORD *)(fieldPtr + 1), theConstraint);
    if ( result )
      break;
    ++fieldIndex;
    fieldPtr = (__int16 *)(v7 + 6);
    if ( fieldIndex > theData[4] )
      return 0;
  }
  return result;
}
// 4B2DF7: variable 'v7' is possibly undefined

//----- (004B2E40) --------------------------------------------------------
signed int  Rules_CheckValueAgainstConstraint(unsigned int type, int value, int theConstraint)
{
  int v6; // ecx
  char *v7; // ecx

  if ( !Method_TypeCodeAllowsRestriction(type, theConstraint) )
    return 1;
  if ( !Method_QueryRestrictionAllowsType(type, value, theConstraint) )
    return 3;
  if ( !Rules_ValueSatisfiesRangeConstraint(type, value, v6) )
    return 2;
  if ( type != 10 || Method_CharRestrictionAllowsType(*(unsigned __int8 *)(value + 8), v7) )
    return 0;
  return 4;
}
// 4B2E79: variable 'v6' is possibly undefined
// 4B2E9D: variable 'v7' is possibly undefined
