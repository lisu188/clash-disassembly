/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004D1F50) --------------------------------------------------------
_DWORD * Rules_AddObjectPatternNode(int thePattern)
{
  int multifieldNode; // ebp
  int patternList; // eax
  _DWORD *v4; // edx
  int prunedPattern; // eax
  int curPattern; // esi
  BOOL endSlot; // edi
  int *patternNode; // edx
  _DWORD *alphaNode; // edx
  _DWORD *freeAlphaNode; // ebp
  _DWORD *newAlphaNode; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  _DWORD *nodeSlotGroup; // [esp+0h] [ebp-2Ch] BYREF
  int classBitmap; // [esp+4h] [ebp-28h]
  int slotBitmap; // [esp+8h] [ebp-24h]
  int currentLevel; // [esp+Ch] [ebp-20h]
  int *lastNode; // [esp+10h] [ebp-1Ch]

  currentLevel = Rules_GetObjectPatternNetworkRoot();
  multifieldNode = 0;
  slotBitmap = Rules_BuildAttributeIndexBitmap(*(_DWORD *)(uintptr_t)(thePattern + 64));
  patternList = *(_DWORD *)(uintptr_t)(thePattern + 64);
  lastNode = 0;
  prunedPattern = Rules_PruneEmptyObjectPatternNodes(patternList, v4);
  *(_DWORD *)(uintptr_t)(thePattern + 64) = prunedPattern;
  curPattern = prunedPattern;
  do
  {
    if ( (*(_BYTE *)(uintptr_t)(curPattern + 8) & 4) != 0 )
    {
      multifieldNode = curPattern;
      curPattern = *(_DWORD *)(uintptr_t)(curPattern + 68);
    }
    endSlot = !*(_DWORD *)(uintptr_t)(curPattern + 64) && multifieldNode;
    patternNode = (int *)(uintptr_t)Rules_FindObjectPatternNode(currentLevel, curPattern, endSlot, (int *)&nodeSlotGroup);
    if ( !patternNode )
      patternNode = Rules_CreateObjectPatternNode(curPattern, nodeSlotGroup, endSlot, (int)(intptr_t)lastNode);
    if ( !*(_DWORD *)(uintptr_t)(curPattern + 64) && multifieldNode )
    {
      curPattern = multifieldNode;
      multifieldNode = 0;
    }
    lastNode = patternNode;
    curPattern = *(_DWORD *)(uintptr_t)(curPattern + 64);
    currentLevel = patternNode[4];
  }
  while ( curPattern && !*(_DWORD *)(uintptr_t)(curPattern + 60) );
  alphaNode = (_DWORD *)(uintptr_t)lastNode[8];
  if ( alphaNode )
  {
    while ( classBitmap != alphaNode[5] || slotBitmap != alphaNode[6] )
    {
      alphaNode = (_DWORD *)(uintptr_t)alphaNode[8];
      if ( !alphaNode )
        goto LABEL_18;
    }
    return alphaNode;
  }
  else
  {
LABEL_18:
    freeAlphaNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
    if ( freeAlphaNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = *freeAlphaNode;
      newAlphaNode = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newAlphaNode = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x2C);
    }
    Rules_ResetDataObjectValue((int)(intptr_t)newAlphaNode);
    v12 = (int)(intptr_t)lastNode;
    newAlphaNode[4] = 0;
    newAlphaNode[7] = v12;
    v13 = classBitmap;
    newAlphaNode[5] = classBitmap;
    ++*(_DWORD *)(uintptr_t)(v13 + 4);
    Rules_AdjustClassBusyCountFromBitmap(classBitmap, 1);
    v14 = slotBitmap;
    newAlphaNode[6] = slotBitmap;
    if ( v14 )
      ++*(_DWORD *)(uintptr_t)(v14 + 4);
    v15 = (int)(intptr_t)lastNode;
    newAlphaNode[10] = 0;
    newAlphaNode[8] = *(_DWORD *)(uintptr_t)(v15 + 32);
    lastNode[8] = (int)(intptr_t)newAlphaNode;
    newAlphaNode[9] = Rules_GetReactiveRuleList();
    Rules_SetReactiveRuleList((int)(intptr_t)newAlphaNode);
    return newAlphaNode;
  }
}
// 4D1F7D: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D20F0) --------------------------------------------------------
int  Rules_FindObjectPatternNode(int listOfNodes, int thePattern, int endSlot, int *nodeSlotGroup)
{
  int curNode; // esi
  BOOL selectorsMatch; // eax

  curNode = listOfNodes;
  *nodeSlotGroup = 0;
  if ( !listOfNodes )
    return 0;
  while ( 1 )
  {
    selectorsMatch = *(_DWORD *)(uintptr_t)thePattern == 18 || *(_DWORD *)(uintptr_t)thePattern == 16 ? *(_DWORD *)(uintptr_t)curNode << 30 >> 31 : (*(_BYTE *)(uintptr_t)curNode & 2) == 0;
    if ( selectorsMatch
      && *(_DWORD *)(uintptr_t)(thePattern + 40) == *(_DWORD *)(uintptr_t)(curNode + 8)
      && *(_DWORD *)(uintptr_t)curNode << 21 >> 24 == *(_DWORD *)(uintptr_t)(thePattern + 32)
      && *(_DWORD *)(uintptr_t)(thePattern + 12) << 18 >> 25 == *(_DWORD *)(uintptr_t)curNode << 13 >> 24
      && endSlot == *(_DWORD *)(uintptr_t)curNode << 29 >> 31
      && AST_NodeListsEqual((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(curNode + 12), (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(thePattern + 52)) )
    {
      break;
    }
    if ( !*nodeSlotGroup && *(_DWORD *)(uintptr_t)curNode << 21 >> 24 == *(_DWORD *)(uintptr_t)(thePattern + 32) && *(_DWORD *)(uintptr_t)(thePattern + 40) == *(_DWORD *)(uintptr_t)(curNode + 8) )
      *nodeSlotGroup = curNode;
    curNode = *(_DWORD *)(uintptr_t)(curNode + 28);
    if ( !curNode )
      return 0;
  }
  return curNode;
}
// 4D2152: variable 'a3' is possibly undefined

//----- (004D21C0) --------------------------------------------------------
int * Rules_CreateObjectPatternNode(int thePattern, _DWORD *nodeSlotGroup, int endSlot, int upperLevel)
{
  _DWORD *freeListNode; // edx
  signed int nodeMem; // edx
  char flagsByte; // ah
  __int16 *networkTest; // eax
  int *nodeRecord; // edx
  char v12; // cl
  int *newNode; // ebx
  int flagsWord; // edx
  int nextNode; // ecx
  _DWORD *curNode; // edx
  _DWORD *prevNode; // edi
  int curNetworkTest; // eax
  int prevSibling; // ecx
  int parentNode; // esi
  int patternField; // [esp+0h] [ebp-10h]
  int patternBits; // [esp+0h] [ebp-10h]

  freeListNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = *freeListNode;
    nodeMem = g_ClipsMemFreeListTemp;
  }
  else
  {
    nodeMem = Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  *(_DWORD *)(uintptr_t)(nodeMem + 32) = 0;
  *(_DWORD *)(uintptr_t)(nodeMem + 4) = 0;
  *(_DWORD *)(uintptr_t)(nodeMem + 16) = 0;
  *(_DWORD *)(uintptr_t)(nodeMem + 28) = 0;
  *(_DWORD *)(uintptr_t)(nodeMem + 24) = 0;
  flagsByte = *(_BYTE *)(uintptr_t)nodeMem;
  *(_DWORD *)(uintptr_t)(nodeMem + 36) = 0;
  *(_BYTE *)(uintptr_t)nodeMem = flagsByte & 0xFC;
  networkTest = AST_AddHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(thePattern + 52), nodeMem, endSlot);
  nodeRecord[3] = (int)(intptr_t)networkTest;
  patternField = (unsigned __int8)*(_DWORD *)(uintptr_t)(thePattern + 32);
  *(_WORD *)nodeRecord &= 0xF807u;
  *nodeRecord |= 8 * patternField;
  patternBits = *(_DWORD *)(uintptr_t)(thePattern + 12) << 18 >> 25;
  *nodeRecord &= 0xFFF807FF;
  *nodeRecord |= patternBits << 11;
  nodeRecord[2] = *(_DWORD *)(uintptr_t)(thePattern + 40);
  newNode = nodeRecord;
  if ( *(_DWORD *)(uintptr_t)thePattern == 18 || *(_DWORD *)(uintptr_t)thePattern == 16 )
    *(_BYTE *)nodeRecord |= 2u;
  *(_BYTE *)nodeRecord &= ~4u;
  flagsWord = *nodeRecord;
  newNode[5] = upperLevel;
  *newNode = (4 * (v12 & 1)) | flagsWord;
  if ( nodeSlotGroup )
  {
    curNode = nodeSlotGroup;
    prevNode = 0;
    do
    {
      if ( curNode[2] != nodeSlotGroup[2] )
        break;
      if ( *curNode << 21 >> 24 != *nodeSlotGroup << 21 >> 24 )
        break;
      curNetworkTest = curNode[3];
      if ( curNetworkTest )
      {
        if ( *(_WORD *)(uintptr_t)curNetworkTest == 50 && (*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(curNetworkTest + 2) + 16) & 0x80) != 0 )
          break;
      }
      prevNode = curNode;
      curNode = (_DWORD *)(uintptr_t)curNode[7];
    }
    while ( curNode );
    if ( curNode )
    {
      newNode[6] = curNode[6];
      newNode[7] = (int)(intptr_t)curNode;
      prevSibling = curNode[6];
      if ( prevSibling )
      {
        *(_DWORD *)(uintptr_t)(prevSibling + 28) = newNode;
      }
      else
      {
        parentNode = curNode[5];
        if ( parentNode )
          *(_DWORD *)(uintptr_t)(parentNode + 16) = newNode;
        else
          Rules_SetObjectPatternNetworkRoot((int)(intptr_t)newNode);
      }
      curNode[6] = newNode;
      return newNode;
    }
    else
    {
      newNode[6] = (int)(intptr_t)prevNode;
      prevNode[7] = newNode;
      return newNode;
    }
  }
  else
  {
    if ( upperLevel )
    {
      newNode[7] = *(_DWORD *)(uintptr_t)(upperLevel + 16);
      *(_DWORD *)(uintptr_t)(upperLevel + 16) = newNode;
    }
    else
    {
      newNode[7] = Rules_GetObjectPatternNetworkRoot();
      Rules_SetObjectPatternNetworkRoot((int)(intptr_t)newNode);
    }
    nextNode = newNode[7];
    if ( nextNode )
      *(_DWORD *)(uintptr_t)(nextNode + 24) = newNode;
    return newNode;
  }
}
// 4D2227: variable 'a3' is possibly undefined
// 4D222C: variable 'v11' is possibly undefined
// 4D2281: variable 'v12' is possibly undefined
// 4D2330: variable 'v17' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D2380) --------------------------------------------------------
int  Rules_RemoveObjectPatternNode(int *alphaNode)
{
  int v2; // edx
  int v3; // ecx
  int v4; // ecx
  int curReactiveNode; // edx
  _DWORD *v6; // ecx
  int i; // ebx
  _DWORD *curAlphaNode; // edx
  _DWORD *j; // eax
  int nextAlphaNode; // ebx
  int result; // eax
  int patternNode; // edx
  int rightNode; // ebp
  int v14; // ecx
  int parentNode; // edx
  _DWORD *v16; // ecx
  int rightSibling; // eax
  _DWORD *v18; // ecx
  int v19; // ecx
  int lastLevel; // edx
  _DWORD *v21; // ecx

  Rules_UnlinkObjectPatternFromGlobalLists(alphaNode);
  Rules_AdjustClassBusyCountFromBitmap(alphaNode[5], v2);
  Rules_DecrementBitmapRefCountIfSet(alphaNode[5], v3);
  if ( alphaNode[6] )
    Rules_DecrementBitmapCount(alphaNode[6], v4);
  curReactiveNode = Rules_GetReactiveRuleList();
  for ( i = 0; (_DWORD *)(uintptr_t)curReactiveNode != v6; curReactiveNode = *(_DWORD *)(uintptr_t)(curReactiveNode + 36) )
    i = curReactiveNode;
  if ( i )
    *(_DWORD *)(uintptr_t)(i + 36) = *(_DWORD *)(uintptr_t)(curReactiveNode + 36);
  else
    Rules_SetReactiveRuleList(*(_DWORD *)(uintptr_t)(curReactiveNode + 36));
  curAlphaNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6[7] + 32);
  for ( j = 0; curAlphaNode != v6; curAlphaNode = (_DWORD *)(uintptr_t)curAlphaNode[8] )
    j = curAlphaNode;
  if ( j )
  {
    j[8] = v6[8];
    g_ClipsMemFreeListTemp = (int)(intptr_t)v6;
    *v6 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
  }
  else
  {
    nextAlphaNode = v6[8];
    if ( nextAlphaNode )
    {
      *(_DWORD *)(uintptr_t)(v6[7] + 32) = nextAlphaNode;
      g_ClipsMemFreeListTemp = (int)(intptr_t)v6;
      *v6 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(v6[7] + 32) = 0;
      g_ClipsMemFreeListTemp = (int)(intptr_t)v6;
      *v6 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176);
      result = g_ClipsMemoryTable;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      patternNode = v6[7];
      if ( !*(_DWORD *)(uintptr_t)(patternNode + 16) )
      {
        while ( patternNode )
        {
          if ( *(_DWORD *)(uintptr_t)(patternNode + 24) || (rightNode = *(_DWORD *)(uintptr_t)(patternNode + 28)) != 0 )
          {
            if ( *(_DWORD *)(uintptr_t)(patternNode + 24) )
            {
              rightSibling = *(_DWORD *)(uintptr_t)(patternNode + 28);
              *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(patternNode + 24) + 28) = rightSibling;
              if ( rightSibling )
                *(_DWORD *)(uintptr_t)(rightSibling + 24) = *(_DWORD *)(uintptr_t)(patternNode + 24);
              AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(patternNode + 12), patternNode);
              g_ClipsMemFreeListTemp = (int)(intptr_t)v18;
              *v18 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
              result = g_ClipsMemFreeListTemp;
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
            }
            else
            {
              v19 = patternNode;
              lastLevel = *(_DWORD *)(uintptr_t)(patternNode + 20);
              if ( lastLevel )
                *(_DWORD *)(uintptr_t)(lastLevel + 16) = *(_DWORD *)(uintptr_t)(v19 + 28);
              else
                Rules_SetObjectPatternNetworkRoot(*(_DWORD *)(uintptr_t)(v19 + 28));
              *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v19 + 28) + 24) = 0;
              AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v19 + 12), v19);
              g_ClipsMemFreeListTemp = (int)(intptr_t)v21;
              *v21 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
              result = g_ClipsMemFreeListTemp;
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
            }
            return result;
          }
          v14 = patternNode;
          parentNode = *(_DWORD *)(uintptr_t)(patternNode + 20);
          if ( parentNode )
            *(_DWORD *)(uintptr_t)(parentNode + 16) = rightNode;
          else
            Rules_SetObjectPatternNetworkRoot(rightNode);
          AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v14 + 12), v14);
          g_ClipsMemFreeListTemp = (int)(intptr_t)v16;
          *v16 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
          result = g_ClipsMemoryTable;
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
        }
      }
    }
  }
  return result;
}
// 4D2397: variable 'v2' is possibly undefined
// 4D239F: variable 'v3' is possibly undefined
// 4D24AC: variable 'v4' is possibly undefined
// 4D23BA: variable 'v6' is possibly undefined
// 4D244C: variable 'v12' is possibly undefined
// 4D247C: variable 'v14' is possibly undefined
// 4D2489: variable 'v16' is possibly undefined
// 4D2562: variable 'v18' is possibly undefined
// 4D2599: variable 'v19' is possibly undefined
// 4D25B0: variable 'v21' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D25E0) --------------------------------------------------------
int * Rules_UnlinkObjectPatternFromGlobalLists(int *result)
{
  int alphaNodeAddr; // ebx
  int i; // ecx
  int v3; // ecx
  int *deletedInstance; // ecx
  int v5; // ecx

  alphaNodeAddr = (int)(intptr_t)result;
  for ( i = g_Clips_InstanceListHead; i; i = *(_DWORD *)(uintptr_t)(i + 68) )
    result = Rules_RemoveMatchingPatternListEntry(i, alphaNodeAddr);
  deletedInstance = (int *)(uintptr_t)g_Instance_DeletedListHead;
  if ( g_Instance_DeletedListHead )
  {
    do
    {
      result = Rules_RemoveMatchingPatternListEntry(*deletedInstance, alphaNodeAddr);
      deletedInstance = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 4);
    }
    while ( deletedInstance );
  }
  return result;
}
// 4D25F8: variable 'v3' is possibly undefined
// 4D2613: variable 'v5' is possibly undefined
// 51A28C: using guessed type int dword_51A28C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004D2630) --------------------------------------------------------
int * Rules_RemoveMatchingPatternListEntry(int theInstance, int patternNode)
{
  int *result; // eax
  int *prevEntry; // edx

  result = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theInstance + 16);
  prevEntry = 0;
  if ( result )
  {
    do
    {
      while ( 1 )
      {
        while ( patternNode != result[2] )
        {
          prevEntry = result;
          result = (int *)(uintptr_t)*result;
          if ( !result )
            return result;
        }
        --*(_DWORD *)(uintptr_t)(theInstance + 40);
        if ( prevEntry )
          break;
        *(_DWORD *)(uintptr_t)(theInstance + 16) = *result;
        g_ClipsMemFreeListTemp = (int)(intptr_t)result;
        *result = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
        result = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(theInstance + 16);
        if ( !result )
          return result;
      }
      *prevEntry = *result;
      g_ClipsMemFreeListTemp = (int)(intptr_t)result;
      *result = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      result = (int *)(uintptr_t)*prevEntry;
    }
    while ( *prevEntry );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D26C0) --------------------------------------------------------
signed int  Rules_CheckDuplicateAttributeRestriction(int restrictionList, int slotName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  if ( !restrictionList )
    return 0;
  while ( slotName != *(_DWORD *)(uintptr_t)(restrictionList + 36) )
  {
    restrictionList = *(_DWORD *)(uintptr_t)(restrictionList + 64);
    if ( !restrictionList )
      return 0;
  }
  Rules_PrintErrorID((int)(intptr_t)aObjrtbld, 4, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMultipleRestri, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(v4 + 16), v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNotAllowed_, v5);
  return 1;
}
// 4D26F6: variable 'v3' is possibly undefined
// 4D2700: variable 'v4' is possibly undefined
// 4D2712: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D2720) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternClassRestriction(int readSource, int theToken)
{
  int *newNode; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  newNode = (int *)(uintptr_t)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)newNode & 0xFC;
  *(_BYTE *)newNode = v5;
  *(_BYTE *)newNode = v5 | 2;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, theToken);
  result = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, v6, 0, 0, newNode, 0);
  if ( !result )
  {
    v9 = newNode;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)(uintptr_t)theToken != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)(uintptr_t)theToken != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = newNode;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2765: variable 'v6' is possibly undefined
// 4D27A4: variable 'v8' is possibly undefined

//----- (004D27E0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternNameRestriction(int readSource, int theToken)
{
  int *newNode; // esi
  char v5; // dl
  int v6; // ecx
  unsigned int *result; // eax
  int v8; // ecx
  int *v9; // eax

  newNode = (int *)(uintptr_t)Rules_CreateLHSParseNode();
  v5 = *(_BYTE *)newNode & 0xDE;
  *(_BYTE *)newNode = v5;
  *(_BYTE *)newNode = v5 | 0x20;
  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, theToken);
  result = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, v6, 0, 1u, newNode, 0);
  if ( !result )
  {
    v9 = newNode;
LABEL_7:
    AST_DecrementNodeRefCount(v9);
    return 0;
  }
  if ( *(_DWORD *)(uintptr_t)theToken != 101 || *result == 18 || *result == 16 )
  {
    IO_OutNewline();
    if ( *(_DWORD *)(uintptr_t)theToken != 101 )
    {
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
    }
    Parser_ReportSyntaxError();
    AST_FreeNode(v8);
    v9 = newNode;
    goto LABEL_7;
  }
  *((_BYTE *)result + 8) |= 0x10u;
  return result;
}
// 4D2825: variable 'v6' is possibly undefined
// 4D2864: variable 'v8' is possibly undefined

//----- (004D28A0) --------------------------------------------------------
unsigned int * Rules_ParseObjectPatternSlotRestriction(int readSource, int theToken, int multiSlot, int *slotConstraints)
{
  int v8; // edx
  int v9; // ecx
  unsigned int slotNameID; // eax
  int v11; // ecx
  unsigned int *result; // eax
  int v13; // edx
  unsigned int *v14; // ecx

  IO_OutWriteToken(asc_50C7F8);
  Parser_NextToken(readSource, v8);
  slotNameID = Class_FindSlotNameID(v9);
  result = Rules_ParsePatternFieldList(readSource, (int *)(uintptr_t)theToken, v11, multiSlot, slotNameID, slotConstraints, 1);
  if ( result )
  {
    if ( *(_DWORD *)(uintptr_t)theToken == 101 )
    {
      if ( !result[17] && (result[2] & 4) != 0 )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50C928);
        result = v14;
        *((_BYTE *)v14 + 8) |= 0x10u;
      }
      else
      {
        *((_BYTE *)result + 8) |= 0x10u;
      }
    }
    else
    {
      IO_OutNewline();
      IO_OutWriteToken(asc_50C7F8);
      IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
      Parser_ReportSyntaxError();
      AST_FreeNode(v13);
      AST_DecrementNodeRefCount(slotConstraints);
      return 0;
    }
  }
  else
  {
    AST_DecrementNodeRefCount(slotConstraints);
    return 0;
  }
  return result;
}
// 4D28BA: variable 'v8' is possibly undefined
// 4D28C4: variable 'v9' is possibly undefined
// 4D28CE: variable 'v11' is possibly undefined
// 4D292B: variable 'v13' is possibly undefined
// 4D2957: variable 'v14' is possibly undefined

//----- (004D2960) --------------------------------------------------------
int  Rules_AllocateClassBitmap(int maxClassID, int set)
{
  int clampedMaxClassID; // ebx
  _BYTE *bitmapMem; // eax
  int v5; // edx
  _WORD *theBitmap; // ecx
  int v7; // ecx

  clampedMaxClassID = maxClassID;
  if ( maxClassID == -1 )
    clampedMaxClassID = 0;
  bitmapMem = Mem_SmallBlockAlloc(((clampedMaxClassID - (__CFSHL__(clampedMaxClassID >> 31, 3) + 8 * (clampedMaxClassID >> 31))) >> 3) + 3);
  Mem_AllocArray(bitmapMem, v5);
  *theBitmap = clampedMaxClassID;
  Rules_ResetClassBitmapToScope(theBitmap, set);
  return v7;
}
// 4D2989: variable 'v5' is possibly undefined
// 4D2992: variable 'v6' is possibly undefined
// 4D299A: variable 'v7' is possibly undefined

//----- (004D29A0) --------------------------------------------------------
__int16  Rules_ResetClassBitmapToScope(_WORD *theBitmap, int set)
{
  int v3; // eax
  int bytesRemaining; // ebx
  char *bytePtr; // esi
  int classID; // ebx
  int tableOffset; // esi
  int theDefclass; // ecx
  char classFlags; // ah
  char *classBytePtr; // edi
  int theModule; // [esp+0h] [ebp-18h]

  v3 = (int)(unsigned __int16)*theBitmap >> 3;
  bytesRemaining = v3 + 1;
  if ( v3 + 1 > 0 )
  {
    bytePtr = (char *)theBitmap + bytesRemaining;
    do
    {
      --bytePtr;
      --bytesRemaining;
      bytePtr[2] = 0;
    }
    while ( bytesRemaining > 0 );
  }
  if ( set )
  {
    theModule = Module_GetCurrent();
    classID = 0;
    tableOffset = 0;
    while ( 1 )
    {
      LOWORD(v3) = *theBitmap;
      if ( classID > (unsigned __int16)*theBitmap )
        break;
      if ( *(_DWORD *)(uintptr_t)(tableOffset + g_ClipsDefclassIdTable)
        && Class_IsInScope(*(_DWORD *)(uintptr_t)(tableOffset + g_ClipsDefclassIdTable), theModule)
        && (classFlags = *(_BYTE *)(uintptr_t)(theDefclass + 20), (classFlags & 8) != 0)
        && (classFlags & 4) == 0 )
      {
        classBytePtr = (char *)theBitmap + ((classID - (__CFSHL__(classID >> 31, 3) + 8 * (classID >> 31))) >> 3);
        classBytePtr[2] |= 1 << (classID % 8);
        tableOffset += 4;
        ++classID;
      }
      else
      {
        tableOffset += 4;
        ++classID;
      }
    }
  }
  return v3;
}
// 4D2A23: variable 'v8' is possibly undefined
// 51AD64: using guessed type int dword_51AD64;

//----- (004D2AA0) --------------------------------------------------------
int  Rules_IncrementBitmapRefCount(int result)
{
  if ( result )
    ++*(_DWORD *)(uintptr_t)(result + 4);
  return result;
}

//----- (004D2AB0) --------------------------------------------------------
int  Rules_DecrementBitmapRefCountIfSet(int result, int a2)
{
  if ( result )
    return Rules_DecrementBitmapCount(result, a2);
  return result;
}

//----- (004D2AC0) --------------------------------------------------------
void  Rules_AdjustClassBusyCountFromBitmap(int bitmapHashNode, int offset)
{
  unsigned __int16 *theBitmap; // edi
  unsigned __int16 i; // si

  if ( !g_Rules_ClearInProgressFlag )
  {
    theBitmap = *(unsigned __int16 **)(uintptr_t)(bitmapHashNode + 16);
    for ( i = 0; i <= (int)*theBitmap; ++i )
    {
      if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)theBitmap + ((int)i >> 3) + 2)) != 0 )
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefclassIdTable + 4 * i) + 26) += offset;
    }
  }
  return;
}
// 4D2AD2: control flows out of bounds to 4D29E4
// 51A180: using guessed type int dword_51A180;
// 51AD64: using guessed type int dword_51AD64;

//----- (004D2B40) --------------------------------------------------------
signed int  Rules_IsClassBitmapEmpty(unsigned __int16 *theBitmap)
{
  int byteIndex; // eax

  byteIndex = ((int)*theBitmap >> 3) + 1;
  if ( !(_WORD)byteIndex )
    return 1;
  while ( !*((_BYTE *)theBitmap + (unsigned __int16)byteIndex + 1) )
  {
    LOWORD(byteIndex) = byteIndex - 1;
    if ( !(_WORD)byteIndex )
      return 1;
  }
  return 0;
}

//----- (004D2B80) --------------------------------------------------------
signed int  Rules_ClassBitmapsIdentical(unsigned __int16 *cs1, _WORD *cs2)
{
  unsigned __int16 *v2; // edi
  int v3; // ecx
  _WORD *bytePtr2; // ebx
  unsigned __int16 *bytePtr1; // esi
  int i; // ecx

  v2 = cs1;
  v3 = *cs1;
  HIWORD(cs1) = 0;
  if ( (unsigned __int16)v3 != (unsigned __int16)*cs2 )
    return 0;
  bytePtr2 = cs2;
  bytePtr1 = v2;
  LOWORD(cs1) = *cs2;
  for ( i = (unsigned int)(intptr_t)cs1 ^ v3; i < ((int)*v2 >> 3) + 1; ++i )
  {
    if ( *((_BYTE *)bytePtr1 + 2) != *((_BYTE *)bytePtr2 + 2) )
      return 0;
    bytePtr2 = (_WORD *)((char *)bytePtr2 + 1);
    bytePtr1 = (unsigned __int16 *)((char *)bytePtr1 + 1);
  }
  return 1;
}

//----- (004D2BD0) --------------------------------------------------------
signed int  Rules_ProcessObjectPatternClassRestriction(_WORD *clsset, int *classRestrictions, int defaultToScope)
{
  unsigned __int16 *tmpset1; // ebp
  int v6; // ecx
  int tmpset2Alloc; // eax
  _DWORD **v8; // ecx
  _DWORD *chkNode; // ecx
  unsigned __int16 *tmpset2; // esi
  int tmpset2Map; // edi
  int theNode; // eax
  int *v13; // ecx
  int *theDefclass; // eax
  int v15; // ecx
  int v16; // ecx
  int includeFlag; // ebx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int constantRestriction; // [esp+8h] [ebp-14h]

  while ( 1 )
  {
    constantRestriction = 1;
    if ( !*classRestrictions )
      break;
    tmpset1 = (unsigned __int16 *)(uintptr_t)Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - 1, 1);
    tmpset2Alloc = Rules_AllocateClassBitmap((unsigned __int16)g_ClipsDefclassIdCount - v6, 0);
    chkNode = *v8;
    tmpset2 = (unsigned __int16 *)(uintptr_t)tmpset2Alloc;
    if ( chkNode )
    {
      tmpset2Map = tmpset2Alloc + 2;
      do
      {
        if ( *chkNode == 2 )
        {
          theDefclass = Class_LookupInScope((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(chkNode[1] + 16));
          *(_DWORD *)(uintptr_t)(v15 + 4) = theDefclass;
          if ( !theDefclass )
          {
            Rules_PrintErrorID((int)(intptr_t)aObjrtbld, 5, 0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUndefinedClass, v18);
            Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
            Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
            return 0;
          }
          if ( (*(_BYTE *)(uintptr_t)(v15 + 8) & 1) != 0 )
          {
            Rules_ResetClassBitmapToScope(tmpset2, 1);
            includeFlag = 0;
          }
          else
          {
            includeFlag = 1;
            Rules_ResetClassBitmapToScope(tmpset2, 0);
          }
          Class_MarkBitmapSubclasses(tmpset2Map, *(_DWORD *)(uintptr_t)(v16 + 4), includeFlag);
          Rules_AndClassBitmaps((int)(intptr_t)tmpset1, tmpset2);
        }
        else
        {
          constantRestriction = 0;
        }
        chkNode = (_DWORD *)(uintptr_t)chkNode[16];
      }
      while ( chkNode );
    }
    if ( Rules_IsClassBitmapEmpty(tmpset1) )
    {
      Rules_PrintErrorID((int)(intptr_t)aObjrtbld, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoObjectsOfE_0, v19);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsARestriction, v20);
      Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
      Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
      return 0;
    }
    if ( constantRestriction )
    {
      theNode = *classRestrictions;
      *classRestrictions = *(_DWORD *)(uintptr_t)(*classRestrictions + 68);
      *(_DWORD *)(uintptr_t)(theNode + 68) = 0;
      AST_FreeNode(theNode);
    }
    Rules_OrClassBitmaps((int)(intptr_t)clsset, tmpset1);
    Mem_SmallBlockFree(tmpset1, ((int)*tmpset1 >> 3) + 3);
    classRestrictions = v13;
    Mem_SmallBlockFree(tmpset2, ((int)*tmpset2 >> 3) + 3);
    defaultToScope = 0;
  }
  if ( defaultToScope )
    Rules_ResetClassBitmapToScope(clsset, 1);
  return 1;
}
// 4D2C2B: variable 'v6' is possibly undefined
// 4D2C36: variable 'v8' is possibly undefined
// 4D2C50: variable 'v9' is possibly undefined
// 4D2CCA: variable 'v13' is possibly undefined
// 4D2CE5: variable 'v15' is possibly undefined
// 4D2D06: variable 'v16' is possibly undefined
// 4D2D37: variable 'v18' is possibly undefined
// 4D2DAD: variable 'v19' is possibly undefined
// 4D2DBC: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD6C: using guessed type __int16 word_51AD6C;

//----- (004D2E20) --------------------------------------------------------
_DWORD * Rules_ResolveSlotConstraintAcrossClasses(int clsset, int slotName, _DWORD *multip)
{
  _DWORD *slotConstraints; // esi
  int i; // ebx
  int v6; // ecx
  unsigned int slotIndex; // eax
  _BYTE *slotDesc; // edx
  _DWORD *v9; // edx
  int v11; // edi
  int bucketOffset; // [esp+4h] [ebp-18h]

  slotConstraints = 0;
  bucketOffset = 0;
  *multip = 0;
  do
  {
    for ( i = *(_DWORD *)(uintptr_t)(bucketOffset + g_DefclassHashTable); i; i = *(_DWORD *)(uintptr_t)(i + 100) )
    {
      v6 = 8;
      if ( ((unsigned __int8)(1 << (*(unsigned __int16 *)(uintptr_t)(i + 24) % 8)) & *(_BYTE *)(uintptr_t)(clsset
                                                                                   + ((int)*(unsigned __int16 *)(uintptr_t)(i + 24) >> 3)
                                                                                   + 2)) != 0 )
      {
        LOBYTE(v6) = *(unsigned __int16 *)(uintptr_t)(i + 24) % 8;
        slotIndex = Instance_ResolveSlotIndex(v6, slotName);
        if ( slotIndex == -1 || (slotDesc = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(4 * slotIndex + *(_DWORD *)(uintptr_t)(i + 56)), (*(_DWORD *)slotDesc & 0x200) == 0) )
        {
          v11 = ((int)*(unsigned __int16 *)(uintptr_t)(i + 24) >> 3) + clsset;
          *(_BYTE *)(uintptr_t)(v11 + 2) &= ~(1 << (*(unsigned __int16 *)(uintptr_t)(i + 24) % 8));
        }
        else
        {
          if ( (*slotDesc & 2) != 0 )
            *multip = 1;
          Rules_UnionConstraints(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 56) + 4 * slotIndex) + 20), (int)(intptr_t)slotConstraints);
          AST_DecrementNodeRefCount(slotConstraints);
          slotConstraints = v9;
        }
      }
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  return slotConstraints;
}
// 4D2EE2: variable 'v9' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004D2F50) --------------------------------------------------------
int  Rules_AndClassBitmaps(int cs1, unsigned __int16 *cs2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*cs2 >> 3) + 1;
  if ( (int)*cs2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = cs1 + (unsigned __int16)result;
      v6 = *((_BYTE *)cs2 + (unsigned __int16)result-- + 1) & *(_BYTE *)(uintptr_t)(v5 + 1);
      *(_BYTE *)(uintptr_t)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FA0) --------------------------------------------------------
int  Rules_OrClassBitmaps(int cs1, unsigned __int16 *cs2)
{
  int result; // eax
  int v5; // edx
  char v6; // ch

  result = ((int)*cs2 >> 3) + 1;
  if ( (int)*cs2 >> 3 != 0xFFFF )
  {
    do
    {
      v5 = cs1 + (unsigned __int16)result;
      v6 = *((_BYTE *)cs2 + (unsigned __int16)result-- + 1) | *(_BYTE *)(uintptr_t)(v5 + 1);
      *(_BYTE *)(uintptr_t)(v5 + 1) = v6;
    }
    while ( (_WORD)result );
  }
  return result;
}

//----- (004D2FF0) --------------------------------------------------------
_WORD * Rules_TrimClassBitmapToHighestBit(_WORD *result)
{
  _DWORD *oldBitmap; // ebp
  unsigned __int16 i; // bx
  int newBitmap; // ebx
  int v4; // ecx

  oldBitmap = result;
  for ( i = *result; i; --i )
  {
    if ( ((unsigned __int8)(1 << (i % 8)) & *((_BYTE *)result + ((int)i >> 3) + 2)) != 0 )
      break;
  }
  if ( i != (unsigned __int16)*result )
  {
    newBitmap = Rules_AllocateClassBitmap(i, 0);
    qmemcpy((void *)(uintptr_t)(newBitmap + 2), (char *)oldBitmap + 2, ((v4 - (__CFSHL__(v4 >> 31, 3) + 8 * (v4 >> 31))) >> 3) + 1);
    Mem_SmallBlockFree(oldBitmap, ((int)*(unsigned __int16 *)oldBitmap >> 3) + 3);
    return (_WORD *)(uintptr_t)newBitmap;
  }
  return result;
}
// 4D3071: variable 'v4' is possibly undefined

//----- (004D30C0) --------------------------------------------------------
int  Rules_ExtractObjectPatternRestrictionNodes(int a1, int restrictionList, _DWORD *isaNodeOut, int endNodeOut, int *nameNodeOut)
{
  _DWORD *newNode; // eax
  int *v7; // ecx
  int curNode; // eax
  int slotSymbol; // edx
  int lastNode; // edx

  *isaNodeOut = 0;
  *nameNodeOut = 0;
  newNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *(_DWORD *)(uintptr_t)endNodeOut = newNode;
  *newNode = 17;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)endNodeOut + 36) = g_Symbol_IsA;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)endNodeOut + 40) = 0;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)endNodeOut + 32) = 1;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)endNodeOut + 24) = a1;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)endNodeOut + 60) = *(_DWORD *)(uintptr_t)(restrictionList + 60);
  curNode = restrictionList;
  *(_DWORD *)(uintptr_t)(restrictionList + 60) = 0;
  do
  {
    slotSymbol = *(_DWORD *)(uintptr_t)(curNode + 36);
    if ( slotSymbol == g_Symbol_IsA )
    {
      *v7 = curNode;
    }
    else if ( slotSymbol == g_Clips_NameSymbol )
    {
      *nameNodeOut = curNode;
    }
    lastNode = curNode;
    curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
  }
  while ( curNode );
  if ( !lastNode )
    return *(_DWORD *)(uintptr_t)endNodeOut;
  *(_DWORD *)(uintptr_t)(lastNode + 64) = *(_DWORD *)(uintptr_t)endNodeOut;
  return restrictionList;
}
// 4D3150: variable 'v7' is possibly undefined
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (004D3170) --------------------------------------------------------
int  Rules_BuildAttributeIndexBitmap(int thePattern)
{
  int v1; // esi
  int i; // ebx
  int bitmapSize; // ebp
  _BYTE *theBitmap; // edi
  _WORD *v5; // ecx
  int j; // ebx
  _BYTE *bytePtr; // esi
  int bitmapValue; // ecx

  v1 = thePattern;
  for ( i = -1; thePattern; thePattern = *(_DWORD *)(uintptr_t)(thePattern + 64) )
  {
    if ( i < *(_DWORD *)(uintptr_t)(thePattern + 40) )
      i = *(_DWORD *)(uintptr_t)(thePattern + 40);
  }
  if ( (unsigned int)i < 2 )
    return 0;
  bitmapSize = ((i - (__CFSHL__(i >> 31, 3) + 8 * (i >> 31))) >> 3) + 3;
  theBitmap = Mem_SmallBlockAlloc(bitmapSize);
  Mem_AllocArray(theBitmap, bitmapSize);
  *v5 = i;
  for ( j = v1; j; j = *(_DWORD *)(uintptr_t)(j + 64) )
  {
    bytePtr = &theBitmap[(*(_DWORD *)(uintptr_t)(j + 40) - (__CFSHL__(*(int *)(uintptr_t)(j + 40) >> 31, 3) + 8 * (*(int *)(uintptr_t)(j + 40) >> 31))) >> 3];
    bytePtr[2] |= 1 << (*(_DWORD *)(uintptr_t)(j + 40) % 8);
  }
  Rules_AddBitmapValue(theBitmap, ((int)*(unsigned __int16 *)theBitmap >> 3) + 3);
  Mem_SmallBlockFree(theBitmap, bitmapSize);
  return bitmapValue;
}
// 4D3191: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 4D31C6: variable 'v5' is possibly undefined
// 4D3237: variable 'v8' is possibly undefined

//----- (004D3250) --------------------------------------------------------
int  Rules_PruneEmptyObjectPatternNodes(int topNode, _DWORD *classBitmapOut)
{
  int curNode; // ecx
  int listHead; // esi
  int prevNode; // ebx
  int bitmapValue; // edx
  int v8; // ecx
  int v9; // ecx
  int childList; // eax

  curNode = topNode;
  listHead = topNode;
  prevNode = 0;
  if ( !topNode )
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
                bitmapValue = *(_DWORD *)(uintptr_t)(curNode + 60);
                if ( bitmapValue )
                {
                  *classBitmapOut = bitmapValue;
                  prevNode = curNode;
                  curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
                  goto LABEL_9;
                }
                if ( *(_DWORD *)(uintptr_t)curNode != 17 && *(_DWORD *)(uintptr_t)curNode != 15 || *(_DWORD *)(uintptr_t)(curNode + 52) )
                  break;
                if ( prevNode )
                  *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(curNode + 64);
                else
                  listHead = *(_DWORD *)(uintptr_t)(curNode + 64);
                *(_DWORD *)(uintptr_t)(curNode + 64) = 0;
                AST_FreeNode(curNode);
                if ( !prevNode )
                  goto LABEL_24;
                curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
LABEL_9:
                if ( !curNode )
                  return listHead;
              }
              if ( *(_DWORD *)(uintptr_t)curNode != 18 && *(_DWORD *)(uintptr_t)curNode != 16
                || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0
                || *(_DWORD *)(uintptr_t)(curNode + 52)
                || (*(_DWORD *)(uintptr_t)(curNode + 8) & 0x3F8000) != 0
                || (*(_WORD *)(uintptr_t)(curNode + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( prevNode )
                *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(curNode + 64);
              else
                listHead = *(_DWORD *)(uintptr_t)(curNode + 64);
              *(_DWORD *)(uintptr_t)(curNode + 64) = 0;
              AST_FreeNode(curNode);
              if ( !prevNode )
                goto LABEL_24;
              curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
              if ( !curNode )
                return listHead;
            }
            if ( *(_DWORD *)(uintptr_t)curNode != 18 && *(_DWORD *)(uintptr_t)curNode != 16
              || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0
              || !*(_DWORD *)(uintptr_t)(curNode + 52)
              || (*(_DWORD *)(uintptr_t)(curNode + 8) & 0x3F8000) != 0
              || (*(_WORD *)(uintptr_t)(curNode + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)(uintptr_t)curNode = 17;
            prevNode = curNode;
            curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
            if ( !curNode )
              return listHead;
          }
          if ( *(_DWORD *)(uintptr_t)curNode != 18 || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) == 0 || *(_DWORD *)(uintptr_t)(curNode + 68) )
            break;
          *(_DWORD *)(uintptr_t)curNode = 17;
          Rules_AppendMultifieldWildcardBitmapTest(curNode, 0);
          *(_BYTE *)(uintptr_t)(v8 + 8) &= ~4u;
LABEL_44:
          prevNode = v8;
          curNode = *(_DWORD *)(uintptr_t)(v8 + 64);
          if ( !curNode )
            return listHead;
        }
        if ( *(_DWORD *)(uintptr_t)curNode == 18 && (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0 )
          break;
        prevNode = curNode;
        curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
        if ( !curNode )
          return listHead;
      }
      Rules_AppendFieldCardinalityBitmapTest((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(curNode + 68));
      childList = Rules_PruneEmptyObjectPatternNodes(*(_DWORD *)(uintptr_t)(v9 + 68), (int)(intptr_t)classBitmapOut);
      *(_DWORD *)(uintptr_t)(v8 + 68) = childList;
      if ( childList )
        goto LABEL_44;
      if ( prevNode )
        *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(v8 + 64);
      else
        listHead = *(_DWORD *)(uintptr_t)(v8 + 64);
      *(_DWORD *)(uintptr_t)(v8 + 64) = 0;
      AST_FreeNode(v8);
      if ( prevNode )
        break;
LABEL_24:
      curNode = listHead;
      if ( !listHead )
        return 0;
    }
    curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
  }
  while ( curNode );
  return listHead;
}
// 4D33BA: variable 'v8' is possibly undefined
// 4D33DD: variable 'v9' is possibly undefined

//----- (004D3430) --------------------------------------------------------
int Rules_CreateDefaultObjectPatternRestriction(void)
{
  int classID; // ecx
  _WORD *theBitmap; // eax
  int v2; // ecx
  char *bytePtr; // esi
  _WORD *packedBitmap; // ebx
  int v5; // edx
  int bitmapValue; // eax
  int v7; // ecx
  _DWORD *topNode; // ecx
  int v9; // eax
  _DWORD *valueNode; // eax
  int v11; // ecx

  LOWORD(classID) = *((_WORD *)Class_LookupInScope(aInitialObjec_2) + 12);
  theBitmap = (_WORD *)(uintptr_t)Rules_AllocateClassBitmap(classID, 0);
  bytePtr = (char *)theBitmap + ((v2 - (__CFSHL__(v2 >> 31, 3) + 8 * (v2 >> 31))) >> 3);
  bytePtr[2] |= 1 << (v2 % 8);
  packedBitmap = Rules_TrimClassBitmapToHighestBit(theBitmap);
  AST_AllocNode();
  LOWORD(v5) = *packedBitmap;
  bitmapValue = Rules_AddBitmapValue(packedBitmap, v5 / 8 + 3);
  *(_DWORD *)(uintptr_t)(v7 + 60) = bitmapValue;
  ++*(_DWORD *)(uintptr_t)(bitmapValue + 4);
  Mem_SmallBlockFree(packedBitmap, (unsigned __int16)*packedBitmap / 8 + 3);
  *topNode = 17;
  topNode[8] = 1;
  v9 = g_Clips_NameSymbol;
  topNode[10] = 1;
  topNode[9] = v9;
  valueNode = (_DWORD *)(uintptr_t)AST_AllocNode();
  *(_DWORD *)(uintptr_t)(v11 + 68) = valueNode;
  *valueNode = 8;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v11 + 68) + 4) = g_Rules_InitialObjectSymbol;
  return v11;
}
// 4D3449: variable 'v0' is possibly undefined
// 4D345A: variable 'v2' is possibly undefined
// 4D3496: variable 'v5' is possibly undefined
// 4D34A2: variable 'v7' is possibly undefined
// 4D34BE: variable 'v8' is possibly undefined
// 4D34DF: variable 'v11' is possibly undefined
// 54E6F4: using guessed type int dword_54E6F4;
// 54E6F8: using guessed type int dword_54E6F8;

//----- (004D3500) --------------------------------------------------------
int  Rules_ParseActionExpressionList(int a1, int readSource)
{
  int v4; // edx
  int v5; // ecx
  unsigned int *v6; // edx
  char *v8; // [esp+0h] [ebp-14h]

  Rules_IncrementIndentDepth(3);
  AST_Append(v5, v4);
  *(_DWORD *)(uintptr_t)(a1 + 6) = Parser_ParseProgram(readSource, v6, 1);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(v8);
  Rules_DecrementIndentDepth(3);
  if ( *(_DWORD *)(uintptr_t)(a1 + 6) )
    return a1;
  AST_Free(a1);
  return 0;
}
// 4D351C: variable 'v5' is possibly undefined
// 4D351C: variable 'v4' is possibly undefined
// 4D3525: variable 'v6' is possibly undefined
// 4D353B: variable 'v8' is possibly undefined

//----- (004D3570) --------------------------------------------------------
int  Rules_SetObjectPatternNegatedFlag(int result, char value)
{
  char patternFlags; // bl

  patternFlags = *(_BYTE *)(uintptr_t)(result + 12);
  if ( (patternFlags & 8) != 0 )
  {
    *(_BYTE *)(uintptr_t)(result + 12) = patternFlags & 0xF7;
    *(_DWORD *)(uintptr_t)(result + 12) |= 8 * (value & 1);
  }
  return result;
}

//----- (004D35A0) --------------------------------------------------------
void  Rules_TriggerObjectPatternMatchForAll(double a1)
{
  _DWORD *theInstance; // ecx
  int v2; // ecx

  theInstance = (_DWORD *)(uintptr_t)g_Clips_InstanceListHead;
  if ( g_Clips_InstanceListHead )
  {
    do
    {
      Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a1);
      theInstance = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v2 + 68);
    }
    while ( theInstance );
  }
}
// 4D35BE: variable 'v2' is possibly undefined
// 51AD0C: using guessed type int dword_51AD0C;
