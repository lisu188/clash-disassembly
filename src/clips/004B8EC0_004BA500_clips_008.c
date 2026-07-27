/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004B8EC0) --------------------------------------------------------
int * Rules_NormalizeNestedConnectives(int *ceNode, _DWORD *changedFlagPtr, int mode)
{
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *child; // eax
  _DWORD *prevChild; // ecx
  int v8; // edx
  _DWORD *nextChild; // esi
  int v10; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD *outChangedFlag; // [esp+4h] [ebp-18h]
  int changed; // [esp+8h] [ebp-14h]

  outChangedFlag = changedFlagPtr;
  *changedFlagPtr = 0;
  do
  {
    v4 = *ceNode;
    changed = 0;
    if ( v4 == 81 || v4 == 83 || v4 == 82 )
    {
      if ( mode == 1 )
        v5 = Rules_CENormalizeAndOr(ceNode, &v14);
      else
        v5 = (_DWORD *)(uintptr_t)Rules_CECollapseNotWrapper((int)(intptr_t)ceNode, &v14);
      if ( v14 )
      {
        changed = 1;
        *outChangedFlag = 1;
      }
      ceNode = (int *)(uintptr_t)Rules_CEMergeRedundantNodes((int)(intptr_t)v5, &v14);
      if ( v14 )
      {
        changed = 1;
        *outChangedFlag = 1;
      }
    }
    child = (_DWORD *)(uintptr_t)ceNode[16];
    prevChild = 0;
    if ( child )
    {
      do
      {
        v8 = *child;
        nextChild = (_DWORD *)(uintptr_t)child[17];
        if ( *child == 81 || v8 == 83 || v8 == 82 )
        {
          child[17] = 0;
          if ( prevChild )
          {
            v12 = Rules_NormalizeNestedConnectives((int)(intptr_t)child, (int)(intptr_t)&v14, mode);
            *(_DWORD *)(uintptr_t)(v13 + 68) = v12;
            *(_DWORD *)(uintptr_t)(v12 + 68) = nextChild;
            prevChild = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v13 + 68);
          }
          else
          {
            v10 = Rules_NormalizeNestedConnectives((int)(intptr_t)child, (int)(intptr_t)&v14, mode);
            ceNode[16] = v10;
            *(_DWORD *)(uintptr_t)(v10 + 68) = nextChild;
            prevChild = (_DWORD *)(uintptr_t)ceNode[16];
          }
          if ( v14 )
          {
            *outChangedFlag = 1;
            changed = 1;
          }
        }
        else
        {
          prevChild = child;
        }
        child = nextChild;
      }
      while ( nextChild );
    }
  }
  while ( changed );
  return ceNode;
}
// 4B8FDC: variable 'v13' is possibly undefined

//----- (004B8FF0) --------------------------------------------------------
_DWORD * Rules_FinalizeConjunctionChain(_DWORD *result)
{
  _DWORD *node; // ecx
  int i; // edx
  int v3; // edx
  _DWORD *j; // edx
  int firstChild; // edx
  int testNode; // esi
  _BYTE *v7; // edx
  bool v8; // al

  node = result;
  if ( *result == 82 )
  {
    for ( i = result[16]; i; i = *(_DWORD *)(uintptr_t)(i + 68) )
      result = (_DWORD *)Rules_FinalizeConjunctionChain(i);
  }
  else
  {
    for ( j = (_DWORD *)(uintptr_t)result[16]; j; j = (_DWORD *)(uintptr_t)j[17] )
    {
      if ( *j == 80 )
        break;
    }
    firstChild = result[16];
    if ( (*(_BYTE *)(uintptr_t)(firstChild + 8) & 1) != 0 || *(_DWORD *)(uintptr_t)firstChild == 84 || *(int *)(uintptr_t)(firstChild + 44) > 1 )
    {
      testNode = Rules_CEAllocTestNode();
      v7 = (_BYTE *)(uintptr_t)(testNode + 8);
      v8 = (node[2] & 2) != 0 || (*(_BYTE *)(uintptr_t)(node[16] + 8) & 2) != 0;
      *v7 &= ~2u;
      *(_DWORD *)v7 |= 2 * v8;
      *(_DWORD *)(uintptr_t)(testNode + 68) = node[16];
      node[16] = testNode;
    }
    return (_DWORD *)(uintptr_t)Rules_CEInsertBoundVariableJoinTests(node[16]);
  }
  return result;
}
// 4B9007: variable 'v3' is possibly undefined
// 4B903C: variable 'v1' is possibly undefined

//----- (004B90A0) --------------------------------------------------------
_DWORD * Rules_CENormalizeAndOr(_DWORD *ceNode, _DWORD *changedFlag)
{
  _DWORD *node; // ecx
  int childIndex; // ebx
  int i; // eax
  int prevChild; // esi
  int v7; // edi
  int v8; // edx
  int v9; // esi
  signed int v10; // edi
  char v11; // bl
  int changed; // [esp+4h] [ebp-18h]

  node = ceNode;
  *changedFlag = 0;
  do
  {
LABEL_2:
    childIndex = 1;
    i = node[16];
    prevChild = 0;
    changed = 0;
    if ( i )
    {
      while ( 1 )
      {
        if ( *node == 81 && *(_DWORD *)(uintptr_t)i == 82 )
        {
          node = Rules_CEMultiplyAndOverOr(node, *(_DWORD *)(uintptr_t)(i + 64), childIndex);
          *changedFlag = 1;
          goto LABEL_2;
        }
        if ( *node == 83 && *(_DWORD *)(uintptr_t)i == 82 )
          break;
        if ( *node == 82 && *(_DWORD *)(uintptr_t)i == 82 || *node == 81 && *(_DWORD *)(uintptr_t)i == 81 )
        {
          if ( (*(_BYTE *)(uintptr_t)(i + 8) & 2) != 0 )
            *((_BYTE *)node + 8) |= 2u;
          changed = 1;
          *changedFlag = 1;
          *(_DWORD *)(uintptr_t)(i + 64) = 0;
          v7 = *(_DWORD *)(uintptr_t)(i + 68);
          *(_DWORD *)(uintptr_t)(i + 68) = 0;
          AST_FreeNode(i);
          if ( prevChild )
            *(_DWORD *)(uintptr_t)(prevChild + 68) = v8;
          else
            node[16] = v8;
          for ( i = v8; *(_DWORD *)(uintptr_t)(v8 + 68); v8 = *(_DWORD *)(uintptr_t)(v8 + 68) )
            ;
          *(_DWORD *)(uintptr_t)(v8 + 68) = v7;
          if ( !i )
            goto LABEL_6;
        }
        else
        {
          prevChild = i;
          ++childIndex;
          i = *(_DWORD *)(uintptr_t)(i + 68);
          if ( !i )
            goto LABEL_6;
        }
      }
      changed = 1;
      *changedFlag = 1;
      *(_DWORD *)(uintptr_t)(i + 68) = 0;
      v9 = *(_DWORD *)(uintptr_t)(i + 64);
      *(_DWORD *)(uintptr_t)(i + 64) = 0;
      AST_FreeNode(i);
      *node = 81;
      for ( node[16] = v9; v9; v9 = *(_DWORD *)(uintptr_t)(v9 + 68) )
      {
        v10 = AST_AllocNode();
        Rules_CECopyNodeFields(v10, (_DWORD *)(uintptr_t)v9, 0);
        *(_DWORD *)(uintptr_t)(v10 + 64) = *(_DWORD *)(uintptr_t)(v9 + 64);
        *(_DWORD *)(uintptr_t)(v10 + 68) = 0;
        *(_DWORD *)(uintptr_t)v9 = 83;
        *(_DWORD *)(uintptr_t)(v9 + 4) = 0;
        *(_DWORD *)(uintptr_t)(v9 + 56) = 0;
        v11 = *(_BYTE *)(uintptr_t)(v9 + 8);
        *(_DWORD *)(uintptr_t)(v9 + 64) = v10;
        *(_BYTE *)(uintptr_t)(v9 + 8) = v11 & 0xFC;
      }
    }
LABEL_6:
    ;
  }
  while ( changed );
  return node;
}
// 4B90B8: variable 'v2' is possibly undefined
// 4B9157: variable 'v8' is possibly undefined

//----- (004B9220) --------------------------------------------------------
int  Rules_CECollapseNotWrapper(int ceNode, _DWORD *changedFlag)
{
  _DWORD *child; // ecx
  _DWORD *v5; // ecx
  char v7; // dl
  int v8; // eax
  char v9; // dh
  int v10; // eax
  int v11; // edx

  *changedFlag = 0;
LABEL_2:
  while ( 1 )
  {
    child = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(ceNode + 64);
    if ( !child )
      return ceNode;
    while ( 1 )
    {
      if ( *(_DWORD *)(uintptr_t)ceNode == 83 && *child == 80 )
      {
        *changedFlag = 1;
        Rules_CECopyNodeFields(ceNode, child, 0);
        *(_BYTE *)(uintptr_t)(ceNode + 8) |= 1u;
        *(_DWORD *)(uintptr_t)(ceNode + 64) = v5[16];
        v5[13] = 0;
        v5[14] = 0;
        v5[15] = 0;
        v5[16] = 0;
        v5[17] = 0;
        AST_FreeNode((int)(intptr_t)v5);
        goto LABEL_2;
      }
      if ( *(_DWORD *)(uintptr_t)ceNode == 83 && (*child == 81 || *child == 83) )
        break;
      child = (_DWORD *)(uintptr_t)child[17];
      if ( !child )
        return ceNode;
    }
    *changedFlag = 1;
    v7 = *(_BYTE *)(uintptr_t)(ceNode + 8);
    *(_DWORD *)(uintptr_t)ceNode = *child;
    v8 = child[2];
    *(_BYTE *)(uintptr_t)(ceNode + 8) = v7 & 0xFE;
    *(_DWORD *)(uintptr_t)(ceNode + 8) |= v8 & 1;
    v9 = *(_BYTE *)(uintptr_t)(ceNode + 8);
    *(_DWORD *)(uintptr_t)(ceNode + 4) = child[1];
    v10 = child[2];
    *(_BYTE *)(uintptr_t)(ceNode + 8) = v9 & 0xFD;
    *(_DWORD *)(uintptr_t)(ceNode + 8) |= v10 & 2;
    *(_DWORD *)(uintptr_t)(ceNode + 64) = child[16];
    child[16] = 0;
    child[17] = 0;
    AST_FreeNode((int)(intptr_t)child);
    Rules_CECountPatternNodes((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(ceNode + 64), v11);
  }
}
// 4B925B: variable 'v5' is possibly undefined
// 4B9318: variable 'v11' is possibly undefined

//----- (004B9330) --------------------------------------------------------
_DWORD * Rules_CEMultiplyAndOverOr(_DWORD *andNode, int orList, int branchIndex)
{
  int orBranch; // ebp
  int clone; // edi
  int v5; // eax
  int j; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  _DWORD *result; // eax
  int v11; // ecx
  int i; // [esp+8h] [ebp-14h]

  orBranch = orList;
  for ( i = 0; orBranch; orBranch = *(_DWORD *)(uintptr_t)(orBranch + 68) )
  {
    clone = Rules_CECloneNode(andNode);
    v5 = 1;
    for ( j = *(_DWORD *)(uintptr_t)(clone + 64); v5 != branchIndex; j = *(_DWORD *)(uintptr_t)(j + 68) )
      ++v5;
    AST_FreeNode(*(_DWORD *)(uintptr_t)(j + 64));
    Rules_CECopyNodeFields(v7, (_DWORD *)(uintptr_t)orBranch, 1);
    v8 = Rules_CECloneNode((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(orBranch + 64));
    *(_DWORD *)(uintptr_t)(v9 + 64) = v8;
    if ( i )
      *(_DWORD *)(uintptr_t)(i + 68) = clone;
    i = clone;
    *(_DWORD *)(uintptr_t)(clone + 68) = 0;
  }
  AST_FreeNode((int)(intptr_t)andNode);
  result = (_DWORD *)(uintptr_t)AST_AllocNode();
  *result = 82;
  result[16] = v11;
  return result;
}
// 4B937D: variable 'v7' is possibly undefined
// 4B938E: variable 'v9' is possibly undefined
// 4B93BE: variable 'v11' is possibly undefined

//----- (004B93E0) --------------------------------------------------------
int  Rules_CEMergeRedundantNodes(int ceNode, _DWORD *changedFlag)
{
  int i; // ecx
  int prevChild; // edi
  int savedTail; // ebx
  int subChildren; // edx
  _DWORD *v9; // edx
  int v10; // edx
  _DWORD *firstChild; // edx
  signed int notNode; // edi
  int v13; // ecx
  _DWORD *v14; // edx
  int v15; // ecx
  _DWORD *firstBinds; // ebx
  int v17; // ecx
  _DWORD *secondBinds; // eax
  int v19; // ecx
  __int16 *v20; // edx
  __int16 *newRestriction; // eax
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int redundantSibling; // eax
  int v26; // ecx
  int changed; // [esp+0h] [ebp-18h]

  *changedFlag = 0;
LABEL_2:
  while ( 2 )
  {
    i = *(_DWORD *)(uintptr_t)(ceNode + 64);
    prevChild = 0;
    changed = 0;
    while ( i )
    {
      if ( *(_DWORD *)(uintptr_t)ceNode == 82 && *(_DWORD *)(uintptr_t)i == 82 || *(_DWORD *)(uintptr_t)ceNode == 81 && *(_DWORD *)(uintptr_t)i == 81 )
      {
        if ( (*(_BYTE *)(uintptr_t)(i + 8) & 2) != 0 )
          *(_BYTE *)(uintptr_t)(ceNode + 8) |= 2u;
        *changedFlag = 1;
        changed = 1;
        *(_DWORD *)(uintptr_t)(i + 64) = 0;
        savedTail = *(_DWORD *)(uintptr_t)(i + 68);
        *(_DWORD *)(uintptr_t)(i + 68) = 0;
        AST_FreeNode(i);
        if ( prevChild )
          *(_DWORD *)(uintptr_t)(prevChild + 68) = subChildren;
        else
          *(_DWORD *)(uintptr_t)(ceNode + 64) = subChildren;
        for ( i = subChildren; *(_DWORD *)(uintptr_t)(subChildren + 68); subChildren = *(_DWORD *)(uintptr_t)(subChildren + 68) )
          ;
        *(_DWORD *)(uintptr_t)(subChildren + 68) = savedTail;
      }
      else
      {
        if ( *(_DWORD *)(uintptr_t)ceNode == 83 && *(_DWORD *)(uintptr_t)i == 84 )
        {
          *changedFlag = 1;
          notNode = AST_NewNode(10, g_ClipsNotSymbol);
          *(_DWORD *)(uintptr_t)(notNode + 6) = Rules_CECloneBindingList(*(_DWORD *)(uintptr_t)(v13 + 56));
          Rules_CECopyNodeFields(ceNode, v14, 1);
          AST_FreeNode(v15);
          AST_FreeNode(*(_DWORD *)(uintptr_t)(ceNode + 56));
          *(_DWORD *)(uintptr_t)(ceNode + 56) = Rules_CECloneRestrictionExpr((__int16 *)(uintptr_t)notNode);
          *(_DWORD *)(uintptr_t)(ceNode + 64) = 0;
          AST_Free(notNode);
          goto LABEL_2;
        }
        if ( *(_DWORD *)(uintptr_t)ceNode == 81
          && *(_DWORD *)(uintptr_t)i == 84
          && (v9 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(i + 68)) != 0
          && *v9 == 84
          && (v10 = *(_DWORD *)(uintptr_t)(i + 44), v10 == *(_DWORD *)(uintptr_t)(i + 48))
          && v10 == *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 68) + 44) )
        {
          *changedFlag = 1;
          changed = 1;
          firstBinds = (_DWORD *)(uintptr_t)Rules_CECloneBindingList(*(_DWORD *)(uintptr_t)(i + 56));
          secondBinds = (_DWORD *)(uintptr_t)Rules_CECloneBindingList(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v17 + 68) + 56));
          AST_MergeFieldAccessNodes(firstBinds, secondBinds);
          AST_FreeNode(*(_DWORD *)(uintptr_t)(v19 + 56));
          newRestriction = Rules_CECloneRestrictionExpr(v20);
          *(_DWORD *)(uintptr_t)(v22 + 56) = newRestriction;
          AST_Free(v23);
          redundantSibling = *(_DWORD *)(uintptr_t)(v24 + 68);
          *(_DWORD *)(uintptr_t)(v24 + 68) = *(_DWORD *)(uintptr_t)(redundantSibling + 68);
          *(_DWORD *)(uintptr_t)(redundantSibling + 68) = 0;
          AST_FreeNode(redundantSibling);
        }
        else
        {
          if ( *(_DWORD *)(uintptr_t)ceNode == 81 && *(_DWORD *)(uintptr_t)i == 84 )
          {
            firstChild = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(ceNode + 64);
            if ( (_DWORD *)(uintptr_t)i == firstChild && !firstChild[17] )
            {
              *changedFlag = 1;
              Rules_CECopyNodeFields(ceNode, firstChild, 1);
              *(_DWORD *)(uintptr_t)(ceNode + 64) = 0;
              AST_FreeNode(v26);
              goto LABEL_2;
            }
          }
          prevChild = i;
          i = *(_DWORD *)(uintptr_t)(i + 68);
        }
      }
    }
    if ( changed )
      continue;
    return ceNode;
  }
}
// 4B940B: variable 'i' is possibly undefined
// 4B9447: variable 'v7' is possibly undefined
// 4B950C: variable 'v13' is possibly undefined
// 4B951B: variable 'v14' is possibly undefined
// 4B9522: variable 'v15' is possibly undefined
// 4B9561: variable 'v17' is possibly undefined
// 4B9577: variable 'v19' is possibly undefined
// 4B9581: variable 'v20' is possibly undefined
// 4B9586: variable 'v22' is possibly undefined
// 4B958B: variable 'v23' is possibly undefined
// 4B9590: variable 'v24' is possibly undefined
// 4B95C6: variable 'v26' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004B95D0) --------------------------------------------------------
int  Rules_CECloneNode(_DWORD *node)
{
  _DWORD *srcNode; // ecx
  _DWORD *freeEntry; // edx
  signed int clone; // esi
  int v4; // ecx
  int v5; // ecx

  srcNode = node;
  if ( !node )
    return 0;
  freeEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288) = *freeEntry;
    clone = g_ClipsMemFreeListTemp;
  }
  else
  {
    clone = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }
  Rules_CECopyNodeFields(clone, srcNode, 1);
  *(_DWORD *)(uintptr_t)(clone + 64) = Rules_CECloneNode(*(_DWORD *)(uintptr_t)(v4 + 64));
  *(_DWORD *)(uintptr_t)(clone + 68) = Rules_CECloneNode(*(_DWORD *)(uintptr_t)(v5 + 68));
  return clone;
}
// 4B9607: variable 'v1' is possibly undefined
// 4B960C: variable 'v4' is possibly undefined
// 4B9617: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9640) --------------------------------------------------------
int  Rules_CECopyNodeFields(int dest, _DWORD *src, int deepCopy)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int flagWord; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int result; // eax
  signed int clonedNodeList; // eax
  _DWORD *v17; // edx
  int v18; // ecx
  int v19; // ebp
  int clonedNode; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int handlerResult; // eax
  int v25; // ecx

  *(_DWORD *)(uintptr_t)dest = *src;
  *(_DWORD *)(uintptr_t)(dest + 4) = src[1];
  v4 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 8) &= ~1u;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v4 & 1;
  v5 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 8) &= ~8u;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v5 & 8;
  v6 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 9) &= ~0x40u;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v6 & 0x4000;
  v7 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 8) &= ~4u;
  flagWord = v7 & 4 | *(_DWORD *)(uintptr_t)(dest + 8);
  *(_DWORD *)(uintptr_t)(dest + 8) = flagWord;
  v9 = src[2] & 0x3F8000;
  *(_DWORD *)(uintptr_t)(dest + 8) = flagWord & 0xFFC07FFF;
  *(_DWORD *)(uintptr_t)(dest + 8) = v9 | flagWord & 0xFFC07FFF;
  v10 = src[2];
  *(_WORD *)(uintptr_t)(dest + 10) &= 0xE03Fu;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v10 & 0x1FC00000;
  v11 = src[3];
  *(_BYTE *)(uintptr_t)(dest + 12) &= 0x80u;
  *(_DWORD *)(uintptr_t)(dest + 12) |= v11 & 0x7F;
  v12 = src[3];
  *(_WORD *)(uintptr_t)(dest + 12) &= 0xC07Fu;
  *(_DWORD *)(uintptr_t)(dest + 12) |= v12 & 0x3F80;
  v13 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 8) &= ~2u;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v13 & 2;
  v14 = src[2];
  *(_BYTE *)(uintptr_t)(dest + 8) &= ~0x20u;
  *(_DWORD *)(uintptr_t)(dest + 8) |= v14 & 0x20;
  *(_DWORD *)(uintptr_t)(dest + 20) = src[5];
  *(_DWORD *)(uintptr_t)(dest + 24) = src[6];
  *(_DWORD *)(uintptr_t)(dest + 28) = src[7];
  *(_DWORD *)(uintptr_t)(dest + 32) = src[8];
  *(_DWORD *)(uintptr_t)(dest + 36) = src[9];
  *(_DWORD *)(uintptr_t)(dest + 40) = src[10];
  *(_DWORD *)(uintptr_t)(dest + 44) = src[11];
  *(_DWORD *)(uintptr_t)(dest + 48) = src[12];
  if ( deepCopy )
  {
    clonedNodeList = AST_CloneNodeList(src[13]);
    *(_DWORD *)(uintptr_t)(v18 + 52) = clonedNodeList;
    v19 = v17[15];
    if ( v19 && *(_DWORD *)(uintptr_t)(v17[6] + 68) )
    {
      handlerResult = (*(int (**)(void))(uintptr_t)(v17[6] + 68))();
      *(_DWORD *)(uintptr_t)(v25 + 60) = handlerResult;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(v18 + 60) = v19;
    }
    clonedNode = Rules_CECloneNode(v17[14]);
    *(_DWORD *)(uintptr_t)(v21 + 56) = clonedNode;
    result = Rules_CloneLHSParseNode((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v22 + 16));
    *(_DWORD *)(uintptr_t)(v23 + 16) = result;
    if ( result )
      *(_BYTE *)(uintptr_t)(v23 + 8) |= 0x10u;
    else
      *(_BYTE *)(uintptr_t)(v23 + 8) &= ~0x10u;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(dest + 52) = src[13];
    *(_DWORD *)(uintptr_t)(dest + 60) = src[15];
    *(_DWORD *)(uintptr_t)(dest + 56) = src[14];
    *(_BYTE *)(uintptr_t)(dest + 8) &= ~0x10u;
    result = src[4];
    *(_DWORD *)(uintptr_t)(dest + 16) = result;
  }
  return result;
}
// 4B975B: variable 'v18' is possibly undefined
// 4B975E: variable 'v17' is possibly undefined
// 4B9770: variable 'v21' is possibly undefined
// 4B9773: variable 'v22' is possibly undefined
// 4B977B: variable 'v23' is possibly undefined
// 4B979B: variable 'v25' is possibly undefined

//----- (004B97B0) --------------------------------------------------------
signed int Rules_CEAllocDefaultNode()
{
  _DWORD *freeEntry; // edx
  signed int result; // eax
  int v2; // ecx
  __int16 v3; // dx

  freeEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288) = *freeEntry;
    result = g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }
  *(_DWORD *)(uintptr_t)result = 103;
  *(_DWORD *)(uintptr_t)(result + 4) = 0;
  *(_DWORD *)(uintptr_t)(result + 16) = 0;
  *(_DWORD *)(uintptr_t)(result + 20) = 0;
  *(_DWORD *)(uintptr_t)(result + 24) = 0;
  *(_DWORD *)(uintptr_t)(result + 28) = -1;
  *(_DWORD *)(uintptr_t)(result + 32) = -1;
  *(_DWORD *)(uintptr_t)(result + 36) = 0;
  *(_DWORD *)(uintptr_t)(result + 40) = -1;
  *(_DWORD *)(uintptr_t)(result + 44) = 1;
  *(_DWORD *)(uintptr_t)(result + 48) = 1;
  *(_DWORD *)(uintptr_t)(result + 60) = 0;
  *(_DWORD *)(uintptr_t)(result + 52) = 0;
  *(_DWORD *)(uintptr_t)(result + 56) = 0;
  v2 = *(_DWORD *)(uintptr_t)(result + 8);
  v3 = *(_WORD *)(uintptr_t)(result + 12);
  *(_DWORD *)(uintptr_t)(result + 64) = 0;
  *(_DWORD *)(uintptr_t)(result + 8) = v2 & 0xE0003FC0;
  *(_WORD *)(uintptr_t)(result + 12) = v3 & 0xC000;
  LOBYTE(v3) = *(_BYTE *)(uintptr_t)(result + 8);
  *(_DWORD *)(uintptr_t)(result + 68) = 0;
  *(_BYTE *)(uintptr_t)(result + 8) = v3 | 0x20;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9880) --------------------------------------------------------
int  Rules_CEFreeNode(int result)
{
  int v1; // edx
  int v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int handler; // eax

  if ( result )
  {
    AST_Free(*(_DWORD *)(uintptr_t)(result + 52));
    AST_FreeNode(*(_DWORD *)(uintptr_t)(v1 + 64));
    AST_FreeNode(*(_DWORD *)(uintptr_t)(v2 + 68));
    AST_FreeNode(*(_DWORD *)(uintptr_t)(v3 + 56));
    if ( (*(_BYTE *)(uintptr_t)(v4 + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 16));
    if ( *(_DWORD *)(uintptr_t)(v4 + 60) )
    {
      handler = *(_DWORD *)(uintptr_t)(v4 + 24);
      if ( *(_DWORD *)(uintptr_t)(handler + 64) )
        (*(void (__cdecl **)(int))(uintptr_t)(handler + 64))(v5);
    }
    g_ClipsMemFreeListTemp = v4;
    *(_DWORD *)(uintptr_t)v4 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 288) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4B9891: variable 'v1' is possibly undefined
// 4B9899: variable 'v2' is possibly undefined
// 4B98A1: variable 'v3' is possibly undefined
// 4B98A9: variable 'v4' is possibly undefined
// 4B98CC: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9900) --------------------------------------------------------
__int16 * Rules_CECloneRestrictionExpr(__int16 *result)
{
  __int16 *srcExpr; // ebx
  _DWORD *clone; // edi
  signed int v3; // eax
  int v4; // ecx
  signed int v5; // eax
  int *cloneNode; // ecx
  int v7; // edx
  int v8; // ebx
  int v9; // esi
  signed int i; // ecx
  _BYTE *v11; // eax

  srcExpr = result;
  if ( result )
  {
    clone = (_DWORD *)(uintptr_t)AST_AllocNode();
    *clone = *srcExpr;
    clone[1] = *(_DWORD *)(srcExpr + 1);
    v3 = Rules_CECloneRestrictionExpr(*(_DWORD *)(srcExpr + 5));
    *(_DWORD *)(uintptr_t)(v4 + 64) = v3;
    v5 = Rules_CECloneRestrictionExpr(*(_DWORD *)(srcExpr + 3));
    v7 = *cloneNode;
    cloneNode[17] = v5;
    if ( v7 == 10 )
    {
      v8 = 1;
      v9 = cloneNode[1];
      for ( i = v5; i; ++v8 )
      {
        if ( *(_DWORD *)(uintptr_t)i == 15 )
        {
          Rules_GetArgRestrictionType(v9, v8);
          v11 = Rules_ApplyPatternKeywordFlags();
          *(_DWORD *)(uintptr_t)(i + 16) = v11;
          *(_BYTE *)(uintptr_t)(i + 8) |= 0x10u;
        }
        i = *(_DWORD *)(uintptr_t)(i + 64);
      }
      return (__int16 *)clone;
    }
    else
    {
      return (__int16 *)cloneNode;
    }
  }
  return result;
}
// 4B992B: variable 'v4' is possibly undefined
// 4B9936: variable 'v6' is possibly undefined
// 4B9962: variable 'i' is possibly undefined

//----- (004B9980) --------------------------------------------------------
int  Rules_CECloneBindingList(int bindingList)
{
  int src; // ecx
  _DWORD *freeEntry; // ebx
  signed int clone; // edx
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // edx

  src = bindingList;
  if ( !bindingList )
    return 0;
  freeEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *freeEntry;
    clone = g_ClipsMemFreeListTemp;
  }
  else
  {
    clone = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_WORD *)(uintptr_t)clone = *(_WORD *)(uintptr_t)src;
  *(_DWORD *)(uintptr_t)(clone + 2) = *(_DWORD *)(uintptr_t)(src + 4);
  v4 = Rules_CECloneBindingList(*(_DWORD *)(uintptr_t)(src + 64));
  *(_DWORD *)(uintptr_t)(v5 + 10) = v4;
  v7 = Rules_CECloneBindingList(*(_DWORD *)(uintptr_t)(v6 + 68));
  *(_DWORD *)(uintptr_t)(v8 + 6) = v7;
  return v8;
}
// 4B99A7: variable 'v1' is possibly undefined
// 4B99BB: variable 'v5' is possibly undefined
// 4B99BE: variable 'v6' is possibly undefined
// 4B99C6: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B99F0) --------------------------------------------------------
int * Rules_CECountPatternNodes(int *result, int isTail)
{
  int *node; // ecx
  int nodeType; // edx
  BOOL v5; // edx
  int v6; // ecx
  int v7; // ecx

  node = result;
  if ( result )
  {
    while ( 1 )
    {
      nodeType = *node;
      if ( *node == 80 || nodeType == 84 )
        break;
      if ( nodeType == 81 || nodeType == 83 )
      {
        if ( isTail )
          v5 = node[17] == 0;
        else
          v5 = 0;
        result = (int *)Rules_CECountPatternNodes(node[16], v5);
        node = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6 + 68);
        if ( !node )
          return result;
      }
      else if ( nodeType == 82 )
      {
        result = (int *)(uintptr_t)Rules_ReportSystemError((int)(intptr_t)node, 1);
        node = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v7 + 68);
        if ( !node )
          return result;
      }
      else
      {
LABEL_6:
        node = (int *)(uintptr_t)node[17];
        if ( !node )
          return result;
      }
    }
    ++node[11];
    if ( !isTail || node[17] )
      ++node[12];
    goto LABEL_6;
  }
  return result;
}
// 4B9A3E: variable 'v6' is possibly undefined
// 4B9A61: variable 'v7' is possibly undefined

//----- (004B9A70) --------------------------------------------------------
int Rules_CEAllocTestNode(void)
{
  signed int testNode; // eax
  int patternParser; // edx
  char v2; // bl
  int nodeAddr; // ecx
  __int64 v5; // rax
  _DWORD *v6; // ecx
  int v7; // ecx

  testNode = AST_AllocNode();
  *(_DWORD *)(uintptr_t)testNode = 80;
  v2 = *(_BYTE *)(uintptr_t)(testNode + 8);
  *(_DWORD *)(uintptr_t)(testNode + 68) = 0;
  nodeAddr = testNode;
  *(_BYTE *)(uintptr_t)(testNode + 8) = v2 & 0xDF;
  if ( !patternParser )
    patternParser = Rules_FindPatternParserByName((int)(intptr_t)aFacts_6);
  if ( !patternParser )
  {
    patternParser = g_PatternParserListHead;
    if ( !g_PatternParserListHead )
    {
LABEL_7:
      Rules_ReportSystemError(nodeAddr, 2);
      return 0;
    }
    while ( !*(_DWORD *)(uintptr_t)(patternParser + 80) )
    {
      patternParser = *(_DWORD *)(uintptr_t)(patternParser + 92);
      if ( !patternParser )
        goto LABEL_7;
    }
  }
  v5 = ((__int64 (__fastcall *)(int))(uintptr_t)*(_DWORD *)(uintptr_t)(patternParser + 80))(nodeAddr);
  v6[16] = v5;
  AST_PropagateDepthTag(v6, SHIDWORD(v5));
  return v7;
}
// 4B9A94: variable 'v1' is possibly undefined
// 4B9ABB: variable 'v3' is possibly undefined
// 4B9AD7: variable 'v6' is possibly undefined
// 4B9AE1: variable 'v7' is possibly undefined
// 51B348: using guessed type int dword_51B348;

//----- (004B9AF0) --------------------------------------------------------
int  Rules_CEInsertBoundVariableJoinTests(int result)
{
  int i; // ecx
  int j; // esi
  int boundNode; // ecx
  int joinTestNode; // ebx
  int v5; // eax
  int v6; // eax

  for ( i = result; result; result = *(_DWORD *)(uintptr_t)(result + 68) )
    *(_BYTE *)(uintptr_t)(result + 9) &= ~0x20u;
  for ( j = 0; i; i = *(_DWORD *)(uintptr_t)(i + 68) )
  {
    if ( (*(_BYTE *)(uintptr_t)(i + 8) & 1) != 0 && (*(_DWORD *)(uintptr_t)(i + 8) & 0x2000) != 0 )
    {
      result = 0;
    }
    else if ( (*(_DWORD *)(uintptr_t)i == 84 || (*(_BYTE *)(uintptr_t)(i + 8) & 1) != 0) && (*(_DWORD *)(uintptr_t)(i + 8) & 0x2000) == 0 )
    {
      joinTestNode = Rules_CEAllocTestNode();
      v5 = *(_DWORD *)(uintptr_t)(boundNode + 8);
      *(_BYTE *)(uintptr_t)(joinTestNode + 8) &= ~2u;
      *(_DWORD *)(uintptr_t)(joinTestNode + 8) |= v5 & 2;
      v6 = *(_DWORD *)(uintptr_t)(boundNode + 44);
      *(_DWORD *)(uintptr_t)(joinTestNode + 44) = v6;
      *(_DWORD *)(uintptr_t)(joinTestNode + 48) = v6;
      if ( !j )
        Rules_ReportSystemError(boundNode, 3);
      *(_DWORD *)(uintptr_t)(j + 68) = joinTestNode;
      *(_DWORD *)(uintptr_t)(joinTestNode + 68) = boundNode;
      i = joinTestNode;
      result = *(_DWORD *)(uintptr_t)(joinTestNode + 68);
    }
    else
    {
      result = *(_DWORD *)(uintptr_t)(i + 68);
    }
    while ( result )
    {
      if ( *(_DWORD *)(uintptr_t)(result + 44) != *(_DWORD *)(uintptr_t)(i + 44) )
        goto LABEL_9;
      if ( (*(_BYTE *)(uintptr_t)(result + 8) & 1) != 0 )
      {
        *(_DWORD *)(uintptr_t)(result + 8) |= 0x2000u;
        result = *(_DWORD *)(uintptr_t)(result + 68);
      }
      else
      {
        if ( *(_DWORD *)(uintptr_t)result == 80 )
          break;
        if ( *(_DWORD *)(uintptr_t)result == 84 )
        {
          *(_DWORD *)(uintptr_t)(result + 8) |= 0x2000u;
          *(_DWORD *)(uintptr_t)(result + 24) = *(_DWORD *)(uintptr_t)(i + 24);
          result = *(_DWORD *)(uintptr_t)(result + 68);
        }
        else
        {
LABEL_9:
          result = *(_DWORD *)(uintptr_t)(result + 68);
        }
      }
    }
    j = i;
  }
  return result;
}
// 4B9B65: variable 'v3' is possibly undefined

//----- (004B9C10) --------------------------------------------------------
void  Rules_CEPrintExpression(int logicalName, int ceNode)
{
  int logName; // ecx
  int node; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  char *printStr; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  char *keyword; // edx
  int v14; // ecx

  logName = logicalName;
  node = ceNode;
  if ( ceNode )
  {
    while ( node )
    {
      switch ( *(_DWORD *)(uintptr_t)node )
      {
        case 'P':
          Output_Write(logName, (int)(intptr_t)asc_50A0A4, logName);
          if ( (*(_BYTE *)(uintptr_t)(node + 8) & 1) != 0 )
            Output_Write(v4, (int)(intptr_t)aN, v4);
          if ( (*(_DWORD *)(uintptr_t)(node + 8) & 2) != 0 )
            Output_Write(v4, (int)(intptr_t)asc_50A0AC, v4);
          Rules_PrintLongInteger(v4, *(_DWORD *)(uintptr_t)(node + 44));
          Output_Write(v5, (int)(intptr_t)asc_50A0B0, v5);
          Rules_PrintLongInteger(v6, *(_DWORD *)(uintptr_t)(node + 48));
          Output_Write(v7, (int)(intptr_t)asc_50A0B4, v7);
          Output_Write(v8, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(node + 64) + 68) + 4) + 16), v8);
          goto LABEL_9;
        case 'Q':
          if ( (*(_DWORD *)(uintptr_t)(node + 8) & 2) != 0 )
            keyword = aLand;
          else
            keyword = aAnd_3;
          goto LABEL_21;
        case 'R':
          if ( (*(_DWORD *)(uintptr_t)(node + 8) & 2) != 0 )
            keyword = aLor;
          else
            keyword = aOr_3;
          goto LABEL_21;
        case 'S':
          if ( (*(_DWORD *)(uintptr_t)(node + 8) & 2) != 0 )
            keyword = aLnot;
          else
            keyword = aNot_3;
LABEL_21:
          Output_Write(logName, (int)(intptr_t)keyword, logName);
          Rules_CEPrintExpression(v14, *(_DWORD *)(uintptr_t)(node + 64));
          goto LABEL_9;
        case 'T':
          Output_Write(logName, (int)(intptr_t)aTest_1, logName);
          Rules_PrintLongInteger(v10, *(_DWORD *)(uintptr_t)(node + 44));
          Output_Write(v11, (int)(intptr_t)asc_50A0B0, v11);
          Rules_PrintLongInteger(v12, *(_DWORD *)(uintptr_t)(node + 48));
LABEL_9:
          printStr = asc_50A0B8;
          break;
        default:
          printStr = aPrettyPrintUnknownExpressionToken;
          break;
      }
      Output_Write(logName, (int)(intptr_t)printStr, logName);
      node = *(_DWORD *)(uintptr_t)(node + 68);
      if ( node )
        Output_Write(logName, (int)(intptr_t)asc_50A0B4, logName);
    }
  }
  // 4B9C1B: jumps to the shared epilogue loc_4B9BCE (pop ebp/edi/esi/ecx/ebx; retn)
  // shared with sub_4B9AF0; in C this is the function return.
  return;
}
// 4B9C1B: control flows out of bounds to 4B9BCE
// 4B9C4C: variable 'v2' is possibly undefined
// 4B9C5E: variable 'v4' is possibly undefined
// 4B9C82: variable 'v5' is possibly undefined
// 4B9C8C: variable 'v6' is possibly undefined
// 4B9C98: variable 'v7' is possibly undefined
// 4B9CAB: variable 'v8' is possibly undefined
// 4B9CE6: variable 'v10' is possibly undefined
// 4B9CEF: variable 'v11' is possibly undefined
// 4B9CF9: variable 'v12' is possibly undefined
// 4B9D61: variable 'v14' is possibly undefined

//----- (004B9D80) --------------------------------------------------------
_DWORD * Rules_CEAssignJoinDepth(_DWORD *ceNode, int joinDepth)
{
  _DWORD *node; // ebp
  _DWORD *result; // eax
  int v5; // ecx
  _DWORD *field; // esi
  int v7; // ecx
  int v8; // ebx
  int v9; // [esp-4h] [ebp-1Ch]
  int patternIndex; // [esp+0h] [ebp-18h]

  node = ceNode;
  patternIndex = ceNode[11];
  while ( 1 )
  {
    if ( patternIndex < node[11] )
    {
      result = (_DWORD *)Rules_CEAssignJoinDepth((int)(intptr_t)node, joinDepth);
      node = result;
      if ( result[12] < v5 )
        return result;
      ++joinDepth;
      goto LABEL_5;
    }
    if ( *node != 84 )
      break;
    if ( patternIndex > node[12] )
      return node;
LABEL_5:
    node = (_DWORD *)(uintptr_t)node[17];
    if ( !node )
      return 0;
  }
  if ( *node != 80 )
    goto LABEL_5;
  field = (_DWORD *)(uintptr_t)node[16];
  for ( node[7] = joinDepth; field; field = (_DWORD *)(uintptr_t)field[16] )
  {
    v7 = field[9];
    v9 = field[10];
    v8 = field[8];
    field[7] = joinDepth;
    Rules_CEPropagateJoinCoordinates((int)(intptr_t)field, joinDepth, v7, v8, v9);
  }
  if ( patternIndex <= node[12] )
  {
    ++joinDepth;
    goto LABEL_5;
  }
  return node;
}
// 4B9DCC: variable 'v5' is possibly undefined

//----- (004B9E10) --------------------------------------------------------
int  Rules_CEPropagateJoinCoordinates(int result, int joinDepth, int patternIndex, int fieldIndex, int slotIndex)
{
  int v7; // ebx
  _DWORD *field; // eax
  int j; // [esp+0h] [ebp-14h]
  _DWORD *i; // [esp+4h] [ebp-10h]

  if ( result )
  {
    if ( (*(_BYTE *)(uintptr_t)(result + 8) & 4) != 0 )
    {
      *(_DWORD *)(uintptr_t)(result + 28) = joinDepth;
      if ( fieldIndex > 0 )
        *(_DWORD *)(uintptr_t)(result + 32) = fieldIndex;
      *(_DWORD *)(uintptr_t)(result + 36) = patternIndex;
      *(_DWORD *)(uintptr_t)(result + 40) = slotIndex;
      result = *(_DWORD *)(uintptr_t)(result + 68);
      for ( i = (_DWORD *)(uintptr_t)result; result; i = (_DWORD *)(uintptr_t)result )
      {
        i[7] = joinDepth;
        v7 = i[8];
        i[9] = patternIndex;
        Rules_CEPropagateJoinCoordinates((int)(intptr_t)i, joinDepth, patternIndex, v7, slotIndex);
        result = i[16];
      }
    }
    else
    {
      result = *(_DWORD *)(uintptr_t)(result + 68);
      for ( j = result; result; j = result )
      {
        field = (_DWORD *)(uintptr_t)j;
        if ( j )
        {
          do
          {
            field[7] = joinDepth;
            if ( fieldIndex > 0 )
              field[8] = fieldIndex;
            field[9] = patternIndex;
            field[10] = slotIndex;
            field = (_DWORD *)(uintptr_t)field[16];
          }
          while ( field );
        }
        result = *(_DWORD *)(uintptr_t)(j + 68);
      }
    }
  }
  return result;
}

//----- (004B9EC0) --------------------------------------------------------
signed int Rules_RegisterDeftemplateBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDeftemplate_2,
           0,
           0,
           (int)(intptr_t)Rules_DeftemplateBsaveFind,
           (int)(intptr_t)Rules_DeftemplateBsaveWriteCounts,
           (int)(intptr_t)Rules_DeftemplateBsaveWriteData,
           (int)(intptr_t)Rules_DeftemplateBloadStorage,
           (int)(intptr_t)Rules_DeftemplateBload,
           (int)(intptr_t)Rules_DeftemplateClearBloaded);
}

//----- (004B9F00) --------------------------------------------------------
int Rules_DeftemplateBsaveFind(void)
{
  int result; // eax
  int i; // ebx
  _DWORD *j; // ecx
  int bsaveIndex; // edx
  int v4; // ecx
  _DWORD *k; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DeftemplateBsaveCount);
    Rules_ConstructQueuePush(g_Deftemplate_SlotCount);
    Rules_ConstructQueuePush(g_DeftemplateModuleItemCount);
  }
  g_DeftemplateBsaveCount = 0;
  g_Deftemplate_SlotCount = 0;
  g_DeftemplateModuleItemCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    ++g_DeftemplateModuleItemCount;
    for ( j = (_DWORD *)(uintptr_t)Rules_GetNextDeftemplate(0); j; j = (_DWORD *)(uintptr_t)Rules_GetNextDeftemplate(v4) )
    {
      bsaveIndex = g_DeftemplateBsaveCount++;
      AST_MarkNodeFieldBound(j, bsaveIndex);
      for ( k = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 20); k; k = (_DWORD *)(uintptr_t)k[4] )
      {
        ++g_Deftemplate_SlotCount;
        *(_DWORD *)(uintptr_t)(*k + 12) |= 2u;
      }
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4B9F8F: variable 'v4' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004B9FD0) --------------------------------------------------------
const void * Rules_DeftemplateBsaveWriteCounts(int fileID, int space)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  _DWORD header[4]; // [esp+0h] [ebp-10h] BYREF

  header[2] = space;
  header[0] = 12;
  Rules_BsaveWriteBlock(4, fileID, header);
  Rules_BsaveWriteBlock(4, v2, &g_DeftemplateBsaveCount);
  Rules_BsaveWriteBlock(4, v3, &g_Deftemplate_SlotCount);
  return Rules_BsaveWriteBlock(4, v4, &g_DeftemplateModuleItemCount);
}
// 4B9FFA: variable 'v2' is possibly undefined
// 4BA00B: variable 'v3' is possibly undefined
// 4BA01C: variable 'v4' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA030) --------------------------------------------------------
int  Rules_DeftemplateBsaveWriteData(int fileID)
{
  int i; // ecx
  int deftemplateItemDescriptor; // eax
  _DWORD *theModuleItem; // eax
  int v5; // ecx
  int j; // ebp
  int k; // ecx
  _DWORD *theDeftemplate; // ecx
  int templateFlagWord; // eax
  int numberOfSlots; // eax
  int patternNetwork; // eax
  int v12; // eax
  int v13; // ecx
  int m; // ebp
  int n; // edi
  int slot; // ecx
  int constraintIndex; // eax
  int slotFlagWord; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int result; // eax
  int constraint; // ebx
  _DWORD bsaveDeftemplate[3]; // [esp+0h] [ebp-54h] BYREF
  int firstSlotIndex CLASH95_UNUSED; // [esp+Ch] [ebp-48h]
  int deftemplateBsaveFlags; // [esp+10h] [ebp-44h]
  int patternNetworkIndex CLASH95_UNUSED; // [esp+14h] [ebp-40h]
  int bsaveSlot; // [esp+18h] [ebp-3Ch] BYREF
  int slotBsaveFlags; // [esp+1Ch] [ebp-38h]
  int slotConstraintIndex CLASH95_UNUSED; // [esp+20h] [ebp-34h]
  signed int slotNameIndex CLASH95_UNUSED; // [esp+24h] [ebp-30h]
  int defaultValueIndex CLASH95_UNUSED; // [esp+28h] [ebp-2Ch]
  _DWORD bsaveModuleItem[3]; // [esp+2Ch] [ebp-28h] BYREF
  int spaceBuffer[7]; // [esp+38h] [ebp-1Ch] BYREF

  spaceBuffer[0] = 12 * g_DeftemplateModuleItemCount + 20 * g_Deftemplate_SlotCount + 24 * g_DeftemplateBsaveCount;
  Rules_BsaveWriteBlock(4, fileID, spaceBuffer);
  g_DeftemplateBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v5) )
  {
    Module_SetCurrent(i);
    deftemplateItemDescriptor = Module_FindItemByName((int)(intptr_t)aDeftemplate_2);
    theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(0, *(_DWORD *)(uintptr_t)(deftemplateItemDescriptor + 4));
    Module_AssignBsaveItemHeaderIndices(bsaveModuleItem, theModuleItem);
    Rules_BsaveWriteBlock(12, fileID, bsaveModuleItem);
  }
  g_Deftemplate_SlotCount = 0;
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_GetNextDeftemplate(0); k; k = Rules_GetNextDeftemplate(v13) )
    {
      AST_ExtractPatternBindingInfo(bsaveDeftemplate, k);
      templateFlagWord = theDeftemplate[6];
      LOBYTE(deftemplateBsaveFlags) = deftemplateBsaveFlags & 0xFE;
      deftemplateBsaveFlags |= templateFlagWord & 1;
      numberOfSlots = theDeftemplate[6] << 16 >> 19;
      LOWORD(deftemplateBsaveFlags) = deftemplateBsaveFlags & 1;
      deftemplateBsaveFlags |= 2 * (numberOfSlots & 0x7FFF);
      patternNetwork = theDeftemplate[8];
      if ( patternNetwork )
        v12 = *(_DWORD *)(uintptr_t)(patternNetwork + 16);
      else
        v12 = -1;
      patternNetworkIndex = v12;
      if ( theDeftemplate[5] )
        firstSlotIndex = g_Deftemplate_SlotCount;
      else
        firstSlotIndex = -1;
      Rules_BsaveWriteBlock(24, fileID, bsaveDeftemplate);
      g_Deftemplate_SlotCount += *(_DWORD *)(uintptr_t)(v13 + 24) << 16 >> 19;
    }
  }
  for ( m = Module_NextEnum(0); m; m = Module_NextEnum(m) )
  {
    Module_SetCurrent(m);
    for ( n = Rules_GetNextDeftemplate(0); n; n = Rules_GetNextDeftemplate(n) )
    {
      if ( *(_DWORD *)(uintptr_t)(n + 20) )
      {
        do
        {
          if ( Rules_DynamicConstraintCheckingEnabled() && (constraint = *(_DWORD *)(uintptr_t)(slot + 8)) != 0 )
            constraintIndex = *(unsigned __int16 *)(uintptr_t)(constraint + 4);
          else
            constraintIndex = -1;
          slotConstraintIndex = constraintIndex;
          bsaveSlot = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)slot + 12) << 16 >> 18;
          slotFlagWord = *(_DWORD *)(uintptr_t)(slot + 4);
          LOBYTE(slotBsaveFlags) = slotBsaveFlags & 0xFE;
          slotBsaveFlags |= slotFlagWord & 1;
          v19 = *(_DWORD *)(uintptr_t)(slot + 4);
          LOBYTE(slotBsaveFlags) = slotBsaveFlags & 0xFD;
          slotBsaveFlags |= v19 & 2;
          v20 = *(_DWORD *)(uintptr_t)(slot + 4);
          LOBYTE(slotBsaveFlags) = slotBsaveFlags & 0xFB;
          slotBsaveFlags |= v20 & 4;
          v21 = *(_DWORD *)(uintptr_t)(slot + 4);
          LOBYTE(slotBsaveFlags) = slotBsaveFlags & 0xF7;
          slotBsaveFlags |= v21 & 8;
          slotNameIndex = AST_GetHashedNodeIndex((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(slot + 12));
          defaultValueIndex = (*(_DWORD *)(uintptr_t)(v22 + 16) != 0) - 1;
          Rules_BsaveWriteBlock(20, fileID, &bsaveSlot);
        }
        while ( *(_DWORD *)(uintptr_t)(v23 + 16) );
      }
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DeftemplateBsaveCount);
    Rules_ConstructQueuePop(&g_Deftemplate_SlotCount);
    return Rules_ConstructQueuePop(&g_DeftemplateModuleItemCount);
  }
  return result;
}
// 4BA0E6: variable 'v5' is possibly undefined
// 4BA143: variable 'v8' is possibly undefined
// 4BA1AD: variable 'v13' is possibly undefined
// 4BA230: variable 'v16' is possibly undefined
// 4BA29F: variable 'v22' is possibly undefined
// 4BA2C0: variable 'v23' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA360) --------------------------------------------------------
int __thiscall Rules_DeftemplateBloadStorage(void *this)
{
  int result; // eax
  _DWORD sizeBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  sizeBuffer[2] = this;
  Rules_BloadReadBlock((uintptr_t)sizeBuffer, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DeftemplateBsaveCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_Deftemplate_SlotCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_DeftemplateModuleItemCount, 4u);
  if ( g_DeftemplateModuleItemCount )
  {
    sizeBuffer[0] = 12 * g_DeftemplateModuleItemCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_DeftemplateModuleItemCount));
    g_ClipsDeftemplateModuleItemArray = result;
    if ( g_DeftemplateBsaveCount )
    {
      sizeBuffer[0] = 36 * g_DeftemplateBsaveCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(36 * g_DeftemplateBsaveCount));
      g_DeftemplateRecordTable = result;
      if ( g_Deftemplate_SlotCount )
      {
        sizeBuffer[0] = 20 * g_Deftemplate_SlotCount;
        result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(20 * g_Deftemplate_SlotCount));
        g_DeftemplateSlotTable = result;
      }
      else
      {
        g_DeftemplateSlotTable = 0;
      }
    }
    else
    {
      g_DeftemplateRecordTable = 0;
      g_DeftemplateSlotTable = 0;
    }
  }
  else
  {
    g_DeftemplateRecordTable = 0;
    g_DeftemplateSlotTable = 0;
    g_ClipsDeftemplateModuleItemArray = 0;
  }
  return result;
}
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E848: using guessed type int dword_54E848;
// 54E84C: using guessed type int dword_54E84C;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA460) --------------------------------------------------------
signed int Rules_DeftemplateBload(void)
{
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  Rules_BloadAndRefresh(g_DeftemplateModuleItemCount, 12, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshModuleItem);
  Rules_BloadAndRefresh(g_DeftemplateBsaveCount, 24, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshRecord);
  return Rules_BloadAndRefresh(g_Deftemplate_SlotCount, 20, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshSlot);
}
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA4C0) --------------------------------------------------------
_DWORD * Rules_DeftemplateBloadRefreshModuleItem(_DWORD *moduleItem, int moduleIndex)
{
  return Module_UpdateItemHeader(moduleItem, (_DWORD *)(uintptr_t)(12 * moduleIndex + g_ClipsDeftemplateModuleItemArray), g_DeftemplateRecordTable, 36);
}
// 54E840: using guessed type int dword_54E840;
// 54E84C: using guessed type int dword_54E84C;

//----- (004BA500) --------------------------------------------------------
int  Rules_DeftemplateBloadRefreshRecord(_DWORD *bsaveRecord, int recordIndex)
{
  int targetRecord; // esi
  int slotIndex; // edx
  int patternNodeIndex; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int result; // eax

  targetRecord = g_DeftemplateRecordTable + 36 * recordIndex;
  Rules_BuildIndexedSlotDescriptor((int)(intptr_t)bsaveRecord, (_DWORD *)(uintptr_t)targetRecord, g_ClipsDeftemplateModuleItemArray, 12, 36, g_DeftemplateRecordTable);
  slotIndex = bsaveRecord[3];
  if ( slotIndex == -1 )
    *(_DWORD *)(uintptr_t)(targetRecord + 20) = 0;
  else
    *(_DWORD *)(uintptr_t)(targetRecord + 20) = 20 * slotIndex + g_DeftemplateSlotTable;
  patternNodeIndex = bsaveRecord[5];
  if ( patternNodeIndex == -1 )
    *(_DWORD *)(uintptr_t)(targetRecord + 32) = 0;
  else
    *(_DWORD *)(uintptr_t)(targetRecord + 32) = g_ClipsFactPatternNodeBloadArray + 44 * patternNodeIndex;
  v7 = bsaveRecord[4];
  *(_BYTE *)(uintptr_t)(targetRecord + 24) &= ~1u;
  *(_DWORD *)(uintptr_t)(targetRecord + 24) |= v7 & 1;
  v8 = g_Rules_WatchFactsFlag & 1;
  *(_BYTE *)(uintptr_t)(targetRecord + 24) &= ~2u;
  *(_DWORD *)(uintptr_t)(targetRecord + 24) |= 2 * v8;
  *(_BYTE *)(uintptr_t)(targetRecord + 24) &= ~4u;
  v9 = (bsaveRecord[4] << 16 >> 17) & 0x1FFF;
  *(_WORD *)(uintptr_t)(targetRecord + 24) &= 7u;
  result = 8 * v9;
  *(_DWORD *)(uintptr_t)(targetRecord + 24) |= result;
  return result;
}
// 4BA555: conditional instruction was optimized away because ecx.4!=FFFFFFFF
// 51A150: using guessed type int dword_51A150;
// 54E51C: using guessed type int dword_54E51C;
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E84C: using guessed type int dword_54E84C;
