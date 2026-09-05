/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00496000) --------------------------------------------------------
int Event_ClearHandlers(void)
{
  int result; // eax

  for ( result = Rules_GetFunctionDefinitionListHead(); result; result = *(_DWORD *)(uintptr_t)(result + 27) )
    *(_WORD *)(uintptr_t)(result + 25) = 0;
  return result;
}

//----- (00496030) --------------------------------------------------------
int Event_InitHandlers(void)
{
  int i; // edx
  int result; // eax
  int currentItem; // edx

  for ( i = g_BinaryItemListHead; i; i = *(_DWORD *)(uintptr_t)(i + 36) )
  {
    while ( !*(_DWORD *)(uintptr_t)(i + 4) )
    {
      i = *(_DWORD *)(uintptr_t)(i + 36);
      if ( !i )
        return result;
    }
    result = (*(int (**)(void))(uintptr_t)(i + 4))();
  }
  return result;
}
// 49604D: variable 'v2' is possibly undefined
// 51AA3C: using guessed type int dword_51AA3C;

//----- (00496060) --------------------------------------------------------
const void * Rules_BsaveWriteFunctionNames(int fp)
{
  int i; // eax
  __int16 assignedIndex; // dx
  const void *result; // eax
  int functionCursor; // esi
  int space; // [esp+0h] [ebp-20h] BYREF
  _DWORD functionCount[7]; // [esp+4h] [ebp-1Ch] BYREF

  functionCount[0] = 0;
  for ( i = Rules_GetFunctionDefinitionListHead(); i; i = *(_DWORD *)(uintptr_t)(i + 27) )
  {
    if ( *(_WORD *)(uintptr_t)(i + 25) )
    {
      assignedIndex = functionCount[0];
      ++functionCount[0];
      *(_WORD *)(uintptr_t)(i + 25) = assignedIndex;
    }
    else
    {
      *(_WORD *)(uintptr_t)(i + 25) = -1;
    }
  }
  Rules_BsaveWriteBlock(4, fp, functionCount);
  if ( !functionCount[0] )
    return Rules_BsaveWriteBlock(4, fp, functionCount);
  space = Rules_BsaveFunctionNamesLength();
  Rules_BsaveWriteBlock(4, fp, &space);
  result = (const void *)(uintptr_t)Rules_GetFunctionDefinitionListHead();
  functionCursor = (int)(intptr_t)result;
  if ( result )
  {
    do
    {
      if ( *(__int16 *)(uintptr_t)(functionCursor + 25) >= 0 )
        result = Rules_BsaveWriteBlock(strlen((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)functionCursor + 16)) + 1, fp, *(const void **)(uintptr_t)(*(_DWORD *)(uintptr_t)functionCursor + 16));
      functionCursor = *(_DWORD *)(uintptr_t)(functionCursor + 27);
    }
    while ( functionCursor );
  }
  return result;
}

//----- (00496130) --------------------------------------------------------
int Rules_BsaveFunctionNamesLength(void)
{
  int functionDef; // edx
  int totalLength; // ebx

  functionDef = Rules_GetFunctionDefinitionListHead();
  totalLength = 0;
  if ( !functionDef )
    return totalLength;
  do
  {
    while ( *(__int16 *)(uintptr_t)(functionDef + 25) < 0 )
    {
      functionDef = *(_DWORD *)(uintptr_t)(functionDef + 27);
      if ( !functionDef )
        return totalLength;
    }
    totalLength += strlen((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)functionDef + 16)) + 1;
    functionDef = *(_DWORD *)(uintptr_t)(functionDef + 27);
  }
  while ( functionDef );
  return totalLength;
}

//----- (00496180) --------------------------------------------------------
_DWORD * Rules_ConstructQueuePush(int item)
{
  _DWORD *freeListHead; // ecx
  _DWORD *result; // eax
  _DWORD *newNode; // ecx

  freeListHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeListHead;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  *result = item;
  newNode = result;
  if ( g_ClipsConstructQueueHead )
  {
    for ( result = (_DWORD *)(uintptr_t)g_ClipsConstructQueueHead; result[1]; result = (_DWORD *)(uintptr_t)result[1] )
      ;
    result[1] = newNode;
  }
  else
  {
    g_ClipsConstructQueueHead = (int)(intptr_t)result;
  }
  return result;
}
// 51AA40: using guessed type int dword_51AA40;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004961F0) --------------------------------------------------------
int  Rules_ConstructQueuePop(_DWORD *itemOut)
{
  _DWORD *poppedNode; // eax
  int result; // eax

  *itemOut = *(_DWORD *)(uintptr_t)g_ClipsConstructQueueHead;
  poppedNode = (_DWORD *)(uintptr_t)g_ClipsConstructQueueHead;
  g_ClipsConstructQueueHead = *(_DWORD *)(uintptr_t)(g_ClipsConstructQueueHead + 4);
  g_ClipsMemFreeListTemp = (int)(intptr_t)poppedNode;
  *poppedNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  return result;
}
// 51AA40: using guessed type int dword_51AA40;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00496230) --------------------------------------------------------
__int16  Rules_MarkReferencedFunctions(__int16 *result)
{
  __int16 *i; // edx
  int entityRecord; // ecx

  for ( i = result; i; i = *(__int16 **)(i + 5) )
  {
    LOWORD(result) = *i;
    if ( (unsigned __int16)*i >= 4u )
    {
      if ( (unsigned __int16)(intptr_t)result >= 0xAu )
      {
        if ( (unsigned __int16)(intptr_t)result <= 0xAu )
        {
          result = *(__int16 **)(i + 1);
          *(__int16 *)((char *)result + 25) = 1;
          goto LABEL_4;
        }
        if ( (unsigned __int16)(intptr_t)result < 0xDu )
          goto LABEL_10;
        if ( (unsigned __int16)(intptr_t)result > 0xDu )
        {
          if ( (_WORD)(intptr_t)result == 105 )
            goto LABEL_4;
LABEL_10:
          result = (__int16 *)(uintptr_t)(4 * *i);
          entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + (_DWORD)(intptr_t)result);
          if ( !entityRecord || (*(_BYTE *)(uintptr_t)(entityRecord + 1) & 0x40) == 0 )
            goto LABEL_4;
        }
      }
      else if ( (_WORD)(intptr_t)result != 8 )
      {
        goto LABEL_10;
      }
    }
    result = *(__int16 **)(i + 1);
    *((_BYTE *)result + 12) |= 2u;
LABEL_4:
    if ( *(_DWORD *)(i + 3) )
      LOWORD(result) = Rules_MarkReferencedFunctions(*(_DWORD *)(i + 3));
  }
  return (__int16)(intptr_t)result;
}
// 496240: simplified comparisons for '[ds.2:edx.4].2': >=3u && >=4u became >=4u
// 496266: variable 'i' is possibly undefined
// 54E530: using guessed type int dword_54E530[];

//----- (004962C0) --------------------------------------------------------
const void * Rules_BsaveWriteHeader(int fp)
{
  Rules_BsaveWriteBlock(strlen((const char *)g_Rules_BloadFileHeaderID) + 1, fp, g_Rules_BloadFileHeaderID);
  return Rules_BsaveWriteBlock(strlen(g_Rules_BsaveVersionID) + 1, fp, g_Rules_BsaveVersionID);
}
// 51A1C0: using guessed type void *off_51A1C0;
// 51A1C4: using guessed type char *off_51A1C4;

//----- (00496310) --------------------------------------------------------
const void * Rules_BsaveWriteEndTag(int a1, int a2)
{
  int v2; // ecx
  _DWORD footerBuffer[8]; // [esp-1Ch] [ebp-20h] BYREF

  footerBuffer[6] = a2;
  strncpy_(a1, g_Rules_BloadFileHeaderID);
  return Rules_BsaveWriteBlock(20, v2, footerBuffer);
}
// 496333: variable 'v2' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);
// 51A1C0: using guessed type void *off_51A1C0;

//----- (00496340) --------------------------------------------------------
signed int  Rules_RegisterBinaryItem(
        int itemName,
        int priority,
        int findFunction,
        int expressionFunction,
        int bsaveStorageFunction,
        int bsaveFunction,
        int bloadStorageFunction,
        int bloadFunction,
        int clearFunction)
{
  _DWORD *freeListHead; // ebx
  int prevItem; // ecx
  _DWORD *newItem; // eax
  int newItemAddr; // ebx
  int currentItem; // eax

  freeListHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
  prevItem = 0;
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = *freeListHead;
    newItem = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newItem = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  newItem[1] = expressionFunction;
  newItem[5] = findFunction;
  newItem[8] = priority;
  *newItem = itemName;
  newItem[6] = bsaveStorageFunction;
  newItem[7] = bsaveFunction;
  newItem[2] = bloadStorageFunction;
  newItem[3] = bloadFunction;
  newItem[4] = clearFunction;
  newItemAddr = (int)(intptr_t)newItem;
  if ( !g_BinaryItemListHead )
  {
    newItem[9] = 0;
    g_BinaryItemListHead = (int)(intptr_t)newItem;
    return 1;
  }
  currentItem = g_BinaryItemListHead;
  do
  {
    if ( priority >= *(_DWORD *)(uintptr_t)(currentItem + 32) )
      break;
    prevItem = currentItem;
    currentItem = *(_DWORD *)(uintptr_t)(currentItem + 36);
  }
  while ( currentItem );
  if ( !prevItem )
  {
    *(_DWORD *)(uintptr_t)(newItemAddr + 36) = g_BinaryItemListHead;
    g_BinaryItemListHead = newItemAddr;
    return 1;
  }
  *(_DWORD *)(uintptr_t)(newItemAddr + 36) = currentItem;
  *(_DWORD *)(uintptr_t)(prevItem + 36) = newItemAddr;
  return 1;
}
// 4963D1: variable 'v13' is possibly undefined
// 51AA3C: using guessed type int dword_51AA3C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00496420) --------------------------------------------------------
const void * Rules_BsaveWriteBlock(int size, int fp, const void *result)
{
  if ( size )
    return (const void *)(uintptr_t)fwrite_(result, size, fp, 1);
  return result;
}

//----- (004967B0) --------------------------------------------------------
signed int Rules_RegisterConstraintCheckingCommands(void)
{
  int i; // eax

  g_ConstraintHashTable = (int)(intptr_t)Mem_SmallBlockAlloc(0x29Cu);
  if ( !g_ConstraintHashTable )
    IO_RunRouterExitCallbacks();
  for ( i = 0; i != 668; i += 4 )
    *(_DWORD *)(uintptr_t)(g_ConstraintHashTable + i) = 0;
  Rules_RegisterHostFunction(aGetDynamicCons, 98, (int)(intptr_t)aGdccommand, (int)(intptr_t)Rules_GetDynamicConstraintCheckingCommand, (int)(intptr_t)a00_14);
  Rules_RegisterHostFunction(aSetDynamicCons, 98, (int)(intptr_t)aSdccommand, (int)(intptr_t)Rules_SetDynamicConstraintCheckingCommand, (int)(intptr_t)a11_0);
  Rules_RegisterHostFunction(aGetStaticConst, 98, (int)(intptr_t)aGsccommand, (int)(intptr_t)Rules_GetStaticConstraintCheckingCommand, (int)(intptr_t)a00_14);
  return Rules_RegisterHostFunction(aSetStaticConst, 98, (int)(intptr_t)aSsccommand, (int)(intptr_t)Rules_SetStaticConstraintCheckingCommand, (int)(intptr_t)a11_0);
}
// 54E694: using guessed type int dword_54E694;

//----- (00496880) --------------------------------------------------------
int  AST_FreeNodeChildren(int result)
{
  int constraints; // edx
  _DWORD *v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx

  constraints = result;
  if ( result )
  {
    if ( *(int *)(uintptr_t)(result + 34) < 0 )
    {
      AST_Free(*(_DWORD *)(uintptr_t)(result + 6));
      AST_Free(*(_DWORD *)(uintptr_t)(v3 + 14));
      AST_Free(*(_DWORD *)(uintptr_t)(v4 + 10));
      AST_Free(*(_DWORD *)(uintptr_t)(v5 + 18));
      AST_Free(*(_DWORD *)(uintptr_t)(v6 + 22));
    }
    AST_FreeNodeChildren(*(_DWORD *)(uintptr_t)(constraints + 26));
    g_ClipsMemFreeListTemp = (int)(intptr_t)v2;
    *v2 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 168);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 168) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4968C3: variable 'v3' is possibly undefined
// 4968CB: variable 'v4' is possibly undefined
// 4968D3: variable 'v5' is possibly undefined
// 4968DB: variable 'v6' is possibly undefined
// 49688D: variable 'v1' is possibly undefined
// 49689A: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004968F0) --------------------------------------------------------
__int16 * AST_ReleaseNodeChildSlots(int constraints, int hashBucket)
{
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx
  __int16 *result; // eax
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx

  while ( 1 )
  {
    while ( *(int *)(uintptr_t)(constraints + 34) < 0 )
    {
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraints + 6));
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v3 + 14));
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 10));
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 18));
      result = AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6 + 22));
      if ( !*(_DWORD *)(uintptr_t)(v8 + 26) )
        return result;
      constraints = *(_DWORD *)(uintptr_t)(v8 + 26);
    }
    AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraints + 6), hashBucket);
    AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v9 + 14), v10);
    AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v11 + 10), v12);
    AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v13 + 18), v14);
    result = AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v15 + 22), v16);
    if ( !*(_DWORD *)(uintptr_t)(v17 + 26) )
      break;
    constraints = *(_DWORD *)(uintptr_t)(v17 + 26);
  }
  return result;
}
// 496902: variable 'v3' is possibly undefined
// 49690A: variable 'v4' is possibly undefined
// 496912: variable 'v5' is possibly undefined
// 49691A: variable 'v6' is possibly undefined
// 496922: variable 'v8' is possibly undefined
// 496930: variable 'a2' is possibly undefined
// 496935: variable 'v9' is possibly undefined
// 496938: variable 'v10' is possibly undefined
// 49693D: variable 'v11' is possibly undefined
// 496940: variable 'v12' is possibly undefined
// 496945: variable 'v13' is possibly undefined
// 496948: variable 'v14' is possibly undefined
// 49694D: variable 'v15' is possibly undefined
// 496950: variable 'v16' is possibly undefined
// 496955: variable 'v17' is possibly undefined

//----- (00496970) --------------------------------------------------------
_DWORD * AST_DecrementNodeRefCount(_DWORD *result)
{
  int v1; // edx
  _DWORD *prevConstraint; // ecx
  int bucketIndex; // ebx
  int newCount; // esi
  int v5; // edx

  v1 = (int)(intptr_t)result;
  prevConstraint = 0;
  if ( result )
  {
    bucketIndex = *(_DWORD *)((char *)result + 34);
    if ( bucketIndex < 0 )
    {
      return (_DWORD *)(uintptr_t)AST_FreeNodeChildren((int)(intptr_t)result);
    }
    else
    {
      result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ConstraintHashTable + 4 * bucketIndex);
      if ( result )
      {
        while ( result != (_DWORD *)(uintptr_t)v1 )
        {
          prevConstraint = result;
          result = *(_DWORD **)((char *)result + 30);
          if ( !result )
            return result;
        }
        newCount = *(_DWORD *)(uintptr_t)(v1 + 38) - 1;
        *(_DWORD *)(uintptr_t)(v1 + 38) = newCount;
        if ( !newCount )
        {
          if ( prevConstraint )
          {
            *(_DWORD *)((char *)prevConstraint + 30) = *(_DWORD *)(uintptr_t)(v1 + 30);
          }
          else
          {
            prevConstraint = (_DWORD *)(uintptr_t)(4 * *(_DWORD *)(uintptr_t)(v1 + 34) + g_ConstraintHashTable);
            *prevConstraint = *(_DWORD *)(uintptr_t)(v1 + 30);
          }
          AST_ReleaseNodeChildSlots(v1, (int)(intptr_t)prevConstraint);
          return (_DWORD *)(uintptr_t)AST_FreeNodeChildren(v5);
        }
      }
    }
  }
  return result;
}
// 4969C7: variable 'v5' is possibly undefined
// 54E694: using guessed type int dword_54E694;

//----- (00496A00) --------------------------------------------------------
unsigned int  AST_HashNodeChildren(_DWORD *theConstraint)
{
  __int16 *classList; // edi
  int count; // ecx
  unsigned int i; // esi
  int fieldHash; // eax
  int v6; // ecx
  __int16 *j; // edi
  int v8; // eax
  int v9; // ecx
  __int16 *k; // edi
  int v11; // eax
  int v12; // ecx
  __int16 *m; // edi
  int v14; // eax
  int v15; // ecx
  __int16 *n; // edi
  int v17; // eax
  int v18; // ecx

  classList = *(__int16 **)((char *)theConstraint + 6);
  count = 0;
  for ( i = 9 * (*theConstraint << 18 >> 31)
          + 37 * (*theConstraint << 19 >> 31)
          + 3 * (*theConstraint << 20 >> 31)
          + 7 * (*theConstraint << 17 >> 31)
          + 59 * (*theConstraint << 22 >> 31)
          + 79 * (*theConstraint << 23 >> 31)
          + 29 * (*theConstraint << 16 >> 31)
          + 29 * (*theConstraint << 24 >> 31)
          + 61 * (*theConstraint << 21 >> 31)
          + 17 * (*theConstraint << 25 >> 31)
          + 31 * (*theConstraint << 26 >> 31)
          + 29 * (*theConstraint << 27 >> 31)
          + 19 * (*theConstraint << 28 >> 31)
          + 23 * (*theConstraint << 29 >> 31)
          + 5 * (*theConstraint << 30 >> 31)
          + 17 * (*theConstraint & 1); classList; i += fieldHash )
  {
    fieldHash = Rules_ComputeFieldHashValue(*classList, *(_DWORD *)(classList + 1), count);
    count = v6 + 1;
    classList = *(__int16 **)(classList + 5);
  }
  for ( j = *(__int16 **)((char *)theConstraint + 10); j; i += v8 )
  {
    v8 = Rules_ComputeFieldHashValue(*j, *(_DWORD *)(j + 1), count);
    count = v9 + 1;
    j = *(__int16 **)(j + 5);
  }
  for ( k = *(__int16 **)((char *)theConstraint + 14); k; i += v11 )
  {
    v11 = Rules_ComputeFieldHashValue(*k, *(_DWORD *)(k + 1), count);
    count = v12 + 1;
    k = *(__int16 **)(k + 5);
  }
  for ( m = *(__int16 **)((char *)theConstraint + 18); m; i += v14 )
  {
    v14 = Rules_ComputeFieldHashValue(*m, *(_DWORD *)(m + 1), count);
    count = v15 + 1;
    m = *(__int16 **)(m + 5);
  }
  for ( n = *(__int16 **)((char *)theConstraint + 22); n; i += v17 )
  {
    v17 = Rules_ComputeFieldHashValue(*n, *(_DWORD *)(n + 1), count);
    count = v18 + 1;
    n = *(__int16 **)(n + 5);
  }
  if ( *(_DWORD *)((char *)theConstraint + 26) )
    i += AST_HashNodeChildren(*(_DWORD *)((char *)theConstraint + 26));
  return i % 0xA7;
}
// 496B9A: variable 'v6' is possibly undefined
// 496BC4: variable 'v9' is possibly undefined
// 496BE4: variable 'v12' is possibly undefined
// 496C04: variable 'v15' is possibly undefined
// 496C24: variable 'v18' is possibly undefined

//----- (00496C70) --------------------------------------------------------
signed int  AST_NodesStructurallyEqual(_DWORD *constraint1, _DWORD *constraint2)
{
  __int16 *classList1; // eax
  __int16 *classList2; // edx
  __int16 *restrictionList1; // eax
  __int16 *restrictionList2; // edx
  __int16 *minValueList1; // eax
  __int16 *minValueList2; // edx
  __int16 *maxValueList1; // eax
  __int16 *maxValueList2; // edx
  __int16 *minFieldsList1; // eax
  __int16 *minFieldsList2; // edx

  while ( 1 )
  {
    if ( (*constraint1 & 1) != (*constraint2 & 1)
      || *constraint1 << 30 >> 31 != *constraint2 << 30 >> 31
      || *constraint1 << 29 >> 31 != *constraint2 << 29 >> 31
      || *constraint1 << 28 >> 31 != *constraint2 << 28 >> 31
      || *constraint1 << 27 >> 31 != *constraint2 << 27 >> 31
      || *constraint1 << 26 >> 31 != *constraint2 << 26 >> 31
      || *constraint1 << 25 >> 31 != *constraint2 << 25 >> 31
      || *constraint1 << 24 >> 31 != *constraint2 << 24 >> 31
      || *constraint1 << 16 >> 31 != *constraint2 << 16 >> 31
      || *constraint1 << 15 >> 31 != *constraint2 << 15 >> 31
      || *constraint1 << 23 >> 31 != *constraint2 << 23 >> 31
      || *constraint1 << 22 >> 31 != *constraint2 << 22 >> 31
      || *constraint1 << 21 >> 31 != *constraint2 << 21 >> 31
      || *constraint1 << 20 >> 31 != *constraint2 << 20 >> 31
      || *constraint1 << 19 >> 31 != *constraint2 << 19 >> 31
      || *constraint1 << 18 >> 31 != *constraint2 << 18 >> 31
      || *constraint1 << 17 >> 31 != *constraint2 << 17 >> 31 )
    {
      return 0;
    }
    classList1 = *(__int16 **)((char *)constraint1 + 6);
    classList2 = *(__int16 **)((char *)constraint2 + 6);
    if ( classList1 )
    {
      while ( classList2 )
      {
        if ( *classList1 != *classList2 || *(_DWORD *)(classList1 + 1) != *(_DWORD *)(classList2 + 1) )
          return 0;
        classList1 = *(__int16 **)(classList1 + 5);
        classList2 = *(__int16 **)(classList2 + 5);
        if ( !classList1 )
          break;
      }
    }
    if ( classList1 != classList2 )
      return 0;
    restrictionList1 = *(__int16 **)((char *)constraint1 + 10);
    restrictionList2 = *(__int16 **)((char *)constraint2 + 10);
    if ( restrictionList1 )
    {
      while ( restrictionList2 )
      {
        if ( *restrictionList1 != *restrictionList2 || *(_DWORD *)(restrictionList1 + 1) != *(_DWORD *)(restrictionList2 + 1) )
          return 0;
        restrictionList1 = *(__int16 **)(restrictionList1 + 5);
        restrictionList2 = *(__int16 **)(restrictionList2 + 5);
        if ( !restrictionList1 )
          break;
      }
    }
    if ( restrictionList1 != restrictionList2 )
      return 0;
    minValueList1 = *(__int16 **)((char *)constraint1 + 14);
    minValueList2 = *(__int16 **)((char *)constraint2 + 14);
    if ( minValueList1 )
    {
      while ( minValueList2 )
      {
        if ( *minValueList1 != *minValueList2 || *(_DWORD *)(minValueList1 + 1) != *(_DWORD *)(minValueList2 + 1) )
          return 0;
        minValueList1 = *(__int16 **)(minValueList1 + 5);
        minValueList2 = *(__int16 **)(minValueList2 + 5);
        if ( !minValueList1 )
          break;
      }
    }
    if ( minValueList1 != minValueList2 )
      return 0;
    maxValueList1 = *(__int16 **)((char *)constraint1 + 18);
    maxValueList2 = *(__int16 **)((char *)constraint2 + 18);
    if ( maxValueList1 )
    {
      while ( maxValueList2 )
      {
        if ( *maxValueList1 != *maxValueList2 || *(_DWORD *)(maxValueList1 + 1) != *(_DWORD *)(maxValueList2 + 1) )
          return 0;
        maxValueList1 = *(__int16 **)(maxValueList1 + 5);
        maxValueList2 = *(__int16 **)(maxValueList2 + 5);
        if ( !maxValueList1 )
          break;
      }
    }
    if ( maxValueList1 != maxValueList2 )
      return 0;
    minFieldsList1 = *(__int16 **)((char *)constraint1 + 22);
    minFieldsList2 = *(__int16 **)((char *)constraint2 + 22);
    if ( minFieldsList1 )
    {
      while ( minFieldsList2 )
      {
        if ( *minFieldsList1 != *minFieldsList2 || *(_DWORD *)(minFieldsList1 + 1) != *(_DWORD *)(minFieldsList2 + 1) )
          return 0;
        minFieldsList1 = *(__int16 **)(minFieldsList1 + 5);
        minFieldsList2 = *(__int16 **)(minFieldsList2 + 5);
        if ( !minFieldsList1 )
          break;
      }
    }
    if ( minFieldsList1 != minFieldsList2
      || !*(_DWORD *)((char *)constraint1 + 26) && *(_DWORD *)((char *)constraint2 + 26)
      || *(_DWORD *)((char *)constraint1 + 26) && !*(_DWORD *)((char *)constraint2 + 26) )
    {
      return 0;
    }
    if ( *(_DWORD *)((char *)constraint1 + 26) == *(_DWORD *)((char *)constraint2 + 26) )
      return 1;
    constraint2 = *(_DWORD **)((char *)constraint2 + 26);
    constraint1 = *(_DWORD **)((char *)constraint1 + 26);
  }
}

//----- (00496F60) --------------------------------------------------------
_DWORD * AST_InternNode(_DWORD *result)
{
  _DWORD *theConstraint; // ebx
  unsigned int hashValue; // eax
  _DWORD *existingConstraint; // ecx
  unsigned int savedHash; // esi
  int v5; // ecx
  int v6; // ecx

  theConstraint = result;
  if ( result )
  {
    hashValue = AST_HashNodeChildren(result);
    existingConstraint = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ConstraintHashTable + 4 * hashValue);
    savedHash = hashValue;
    if ( existingConstraint )
    {
      while ( !AST_NodesStructurallyEqual(theConstraint, existingConstraint) )
      {
        existingConstraint = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 30);
        if ( !existingConstraint )
          goto LABEL_5;
      }
      ++*(_DWORD *)(uintptr_t)(v5 + 38);
      AST_FreeNodeChildren((int)(intptr_t)theConstraint);
      return (_DWORD *)(uintptr_t)v6;
    }
    else
    {
LABEL_5:
      AST_CollapseNodeChildSlots((int)(intptr_t)theConstraint, (int)(intptr_t)existingConstraint);
      *(_DWORD *)((char *)theConstraint + 38) = 1;
      *(_DWORD *)((char *)theConstraint + 34) = savedHash;
      *(_DWORD *)((char *)theConstraint + 30) = *(_DWORD *)(uintptr_t)(g_ConstraintHashTable + 4 * savedHash);
      *(_DWORD *)(uintptr_t)(g_ConstraintHashTable + 4 * savedHash) = theConstraint;
      return theConstraint;
    }
  }
  return result;
}
// 496F90: variable 'v5' is possibly undefined
// 496FD0: variable 'v6' is possibly undefined
// 54E694: using guessed type int dword_54E694;

//----- (00496FE0) --------------------------------------------------------
int  AST_CollapseNodeChildSlots(int constraints, int hashBucket)
{
  int v3; // edx
  int v4; // edx
  __int16 *childNode1; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  __int16 *childNode2; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // edx
  __int16 *childNode3; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // edx
  __int16 *childNode4; // eax
  int v18; // ecx
  int v19; // edx
  int result; // eax
  int v21; // edx
  int v22; // ecx

  while ( 1 )
  {
    AST_AddHashedNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraints + 6), constraints, hashBucket);
    AST_Free(*(_DWORD *)(uintptr_t)(v3 + 6));
    childNode1 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v4 + 14);
    *(_DWORD *)(uintptr_t)(v4 + 6) = v6;
    AST_AddHashedNodeChain(childNode1, v4, v6);
    AST_Free(*(_DWORD *)(uintptr_t)(v7 + 14));
    childNode2 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v8 + 10);
    *(_DWORD *)(uintptr_t)(v8 + 14) = v10;
    AST_AddHashedNodeChain(childNode2, v8, v10);
    AST_Free(*(_DWORD *)(uintptr_t)(v11 + 10));
    childNode3 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v12 + 18);
    *(_DWORD *)(uintptr_t)(v12 + 10) = v14;
    AST_AddHashedNodeChain(childNode3, v12, v14);
    AST_Free(*(_DWORD *)(uintptr_t)(v15 + 18));
    childNode4 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 22);
    *(_DWORD *)(uintptr_t)(v16 + 18) = v18;
    AST_AddHashedNodeChain(childNode4, v16, v18);
    result = AST_Free(*(_DWORD *)(uintptr_t)(v19 + 22));
    *(_DWORD *)(uintptr_t)(v21 + 22) = v22;
    hashBucket = *(_DWORD *)(uintptr_t)(v21 + 26);
    if ( !hashBucket )
      break;
    constraints = *(_DWORD *)(uintptr_t)(v21 + 26);
  }
  return result;
}
// 496FEE: variable 'v3' is possibly undefined
// 496FF6: variable 'v4' is possibly undefined
// 496FF9: variable 'v6' is possibly undefined
// 497003: variable 'v7' is possibly undefined
// 49700B: variable 'v8' is possibly undefined
// 49700E: variable 'v10' is possibly undefined
// 497018: variable 'v11' is possibly undefined
// 497020: variable 'v12' is possibly undefined
// 497023: variable 'v14' is possibly undefined
// 49702D: variable 'v15' is possibly undefined
// 497035: variable 'v16' is possibly undefined
// 497038: variable 'v18' is possibly undefined
// 497042: variable 'v19' is possibly undefined
// 49704A: variable 'v22' is possibly undefined
// 49704A: variable 'v21' is possibly undefined

//----- (00497060) --------------------------------------------------------
int  Rules_SetDynamicConstraintCheckingCommand(int returnValue, double context)
{
  int argCheck; // eax
  int v4; // ecx
  int v5; // esi
  int argBuffer; // [esp-4h] [ebp-28h] BYREF
  __int64 argData[2]; // [esp+0h] [ebp-24h]
  int savedReturnValue CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  savedReturnValue = returnValue;
  argCheck = Lexer_TokenExpect((int)(intptr_t)aSetDynamicCons, 0, 1);
  v5 = v4;
  if ( argCheck == -1 )
    return v4;
  Rules_RtnUnknown(1, &argBuffer, context);
  g_CLIPS_DynamicConstraintCheckingFlag = argData[2] != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 49707E: variable 'v4' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;
// 54DD70: using guessed type int dword_54DD70;

//----- (004970E0) --------------------------------------------------------
int Rules_GetDynamicConstraintCheckingCommand(void)
{
  int currentFlag; // ecx

  Lexer_TokenExpect((int)(intptr_t)aGetDynamicCons, 0, 0);
  return currentFlag;
}
// 4970FA: variable 'v0' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;

//----- (00497100) --------------------------------------------------------
int  Rules_SetStaticConstraintCheckingCommand(int returnValue, double context)
{
  int argCheck; // eax
  int v4; // ecx
  int v5; // esi
  int argBuffer; // [esp-4h] [ebp-28h] BYREF
  __int64 argData[2]; // [esp+0h] [ebp-24h]
  int savedReturnValue CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  savedReturnValue = returnValue;
  argCheck = Lexer_TokenExpect((int)(intptr_t)aSetStaticConst, 0, 1);
  v5 = v4;
  if ( argCheck == -1 )
    return v4;
  Rules_RtnUnknown(1, &argBuffer, context);
  g_CLIPS_StaticConstraintCheckingFlag = argData[2] != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 49711E: variable 'v4' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00497180) --------------------------------------------------------
int Rules_GetStaticConstraintCheckingCommand(void)
{
  int currentFlag; // ecx

  Lexer_TokenExpect((int)(intptr_t)aGetStaticConst, 0, 0);
  return currentFlag;
}
// 49719A: variable 'v0' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;

//----- (004971A0) --------------------------------------------------------
int __fastcall Rules_SetDynamicConstraintChecking(int newValue, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = g_CLIPS_DynamicConstraintCheckingFlag;
  g_CLIPS_DynamicConstraintCheckingFlag = newValue;
  return previous_state;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971B0) --------------------------------------------------------
int Rules_DynamicConstraintCheckingEnabled(void)
{
  return g_CLIPS_DynamicConstraintCheckingFlag;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971D0) --------------------------------------------------------
int Rules_StaticConstraintCheckingEnabled(void)
{
  return g_CLIPS_StaticConstraintCheckingFlag;
}
// 51AAB0: using guessed type int dword_51AAB0;

//----- (004971E0) --------------------------------------------------------
_DWORD *Rules_InitDeffactsConstruct(void)
{
  _DWORD *result; // eax

  Rules_RegisterDeffactsModuleItem();
  Deffacts_CommandDefinitions();
  result = Rules_RegisterConstructType(
             (int)(intptr_t)aDeffacts,
             (int)(intptr_t)aDeffacts,
             (int)(intptr_t)Rules_ParseDeffactsConstruct,
             (int)(intptr_t)Deffacts_ParseAndInstall,
             (int)(intptr_t)Rules_GetConstructNameSymbol,
             (int)(intptr_t)Rules_GetModuleConstructListHead,
             (int)(intptr_t)Rules_GetConstructOwnerModule,
             (int)(intptr_t)Rules_DeffactsGetNextItem,
             (int)(intptr_t)Rules_SetConstructNextInModule,
             (int)(intptr_t)Rules_DeffactsIsDeletable,
             (int)(intptr_t)Deffacts_DeleteConstruct,
             (int)(intptr_t)Deffacts_FreeConstruct);
  g_ClipsDeffactsConstructType = (int)(intptr_t)result;
  return result;
}
// 497310: using guessed type int sub_497310();
// 54E69C: using guessed type int dword_54E69C;

//----- (00497240) --------------------------------------------------------
int Rules_RegisterDeffactsModuleItem(void)
{
  int result; // eax

  result = Module_RegisterItem(
             (int)(intptr_t)aDeffacts,
             (int)(intptr_t)Rules_AllocDeffactsModuleData,
             (int)(intptr_t)Deffacts_GetModuleItem,
             (int)(intptr_t)Rules_FreeDeffactsModuleData,
             (int)(intptr_t)Deffacts_PrintModuleReference,
             (int)(intptr_t)Rules_ParseDeffactsConstruct);
  g_ClipsDeffactsModuleItemId = result;
  return result;
}
// 54E698: using guessed type int dword_54E698;

//----- (00497270) --------------------------------------------------------
signed int Rules_AllocDeffactsModuleData(void)
{
  _DWORD *freeListHead; // edx

  freeListHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004972A0) --------------------------------------------------------
int  Rules_FreeDeffactsModuleData(int theModuleItem)
{
  int result; // eax

  result = Rules_ClearModuleConstructList(theModuleItem, g_ClipsDeffactsConstructType, theModuleItem);
  g_ClipsMemFreeListTemp = theModuleItem;
  *(_DWORD *)(uintptr_t)theModuleItem = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E69C: using guessed type int dword_54E69C;

//----- (004972E0) --------------------------------------------------------
int  Rules_GetDeffactsModuleItem(int theModule)
{
  return Rules_GetModuleConstructData(theModule, g_ClipsDeffactsModuleItemId);
}
// 54E698: using guessed type int dword_54E698;

//----- (004972F0) --------------------------------------------------------
int  Rules_ParseDeffactsConstruct(_BYTE *constructName, int a2 CLASH95_UNUSED)
{
  return Rules_FindConstructByNameGeneric(constructName, g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (00497300) --------------------------------------------------------
int  Rules_DeffactsGetNextItem(int deffactsPtr)
{
  return Class_Enum(deffactsPtr, g_ClipsDeffactsModuleItemId);
}
// 54E698: using guessed type int dword_54E698;

//----- (00497310) --------------------------------------------------------
int Rules_DeffactsIsDeletable(void)
{
  int result; // eax

  result = Rules_IsBloaded();
  if ( result )
    return 0;
  if ( !g_Rules_ResetInProgressFlag )
    return 1;
  return result;
}
// 497310: using guessed type int sub_497310();
// 51A184: using guessed type int dword_51A184;

//----- (00497330) --------------------------------------------------------
int  Deffacts_FreeConstruct(int result)
{
  int fact; // edx
  int expression; // eax

  if ( result )
  {
    fact = result;
    expression = *(_DWORD *)(uintptr_t)(fact + 20);
    AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)expression);
    AST_FreePackedNodeChain(expression);
    Rules_FreeConstructHeaderString((int *)(uintptr_t)(unsigned int)fact, fact);
    g_ClipsMemFreeListTemp = fact;
    *(_DWORD *)(uintptr_t)fact = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    result = g_ClipsMemoryTable;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00497370) --------------------------------------------------------
int Defgeneric_SetupConstruct(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_Defgeneric, 11);
  g_DefgenericModuleItemIndex = Module_RegisterItem(
                   (int)(intptr_t)aDefgeneric,
                   (int)(intptr_t)Defgeneric_AllocateModule,
                   (int)(intptr_t)Defgeneric_RecordAtIndex,
                   (int)(intptr_t)Defgeneric_FreeModule,
                   (int)(intptr_t)Defgeneric_PrintModuleReference,
                   (int)(intptr_t)Defgeneric_ParseConstruct);
  g_Clips_DefgenericConstructType = (int)(intptr_t)Rules_RegisterConstructType(
                        (int)(intptr_t)aDefgeneric,
                        (int)(intptr_t)aDefgenerics,
                        (int)(intptr_t)Defgeneric_ParseConstruct,
                        (int)(intptr_t)Defgeneric_ParseDefgeneric,
                        (int)(intptr_t)Rules_GetConstructNameSymbol,
                        (int)(intptr_t)Rules_GetModuleConstructListHead,
                        (int)(intptr_t)Rules_GetConstructOwnerModule,
                        (int)(intptr_t)Defgeneric_GetNextInModule,
                        (int)(intptr_t)Rules_SetConstructNextInModule,
                        (int)(intptr_t)Defgeneric_IsDeletable,
                        (int)(intptr_t)Defgeneric_RemoveConstruct,
                        (int)(intptr_t)Defgeneric_RemoveDefgeneric);
  Rules_AddClearReadyFunction((int)(intptr_t)aDefgeneric, (int)(intptr_t)Defgeneric_NoActiveCall, 0);
  Defgeneric_RegisterBinaryItem();
  Defgeneric_CompilerSetup();
  Module_RegisterImportExportConstructType((int)(intptr_t)aDefgeneric, 2);
  Rules_RegisterConstructType((int)(intptr_t)aDefmethod, (int)(intptr_t)aDefmethods, 0, (int)(intptr_t)Defgeneric_ParseDefmethod, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_AddSaveFunction((int)(intptr_t)aDefgeneric, (int)(intptr_t)Defgeneric_SaveConstructs, 1000);
  Rules_AddSaveFunction((int)(intptr_t)aDefmethod, (int)(intptr_t)Defmethod_SaveConstructs, -1000);
  Rules_RegisterHostFunction(aUndefgeneric, 118, v0, (int)(intptr_t)Defgeneric_UndefgenericCommand, (int)(intptr_t)a11w_2);
  Rules_RegisterHostFunction(aUndefmethod, 118, (int)(intptr_t)aUndefmethodcom, (int)(intptr_t)Defgeneric_UndefmethodCommand, (int)(intptr_t)a22Wg);
  Rules_RegisterHostFunction(aCallNextMethod, 117, (int)(intptr_t)aCallnextmethod, (int)(intptr_t)Method_OverrideNextMethod, (int)(intptr_t)a00_2);
  Rules_SetFunctionSeqOverloadFlags(aCallNextMethod, 0);
  Rules_RegisterHostFunction(aCallSpecificMe, 117, v1, (int)(intptr_t)Method_EvaluateCallSpecificMethod, (int)(intptr_t)a2Wi);
  Rules_SetFunctionSeqOverloadFlags(aCallSpecificMe, 0);
  Rules_RegisterHostFunction(aOverrideNextMe, 117, v2, (int)(intptr_t)Method_CallNextMethod, 0);
  Rules_SetFunctionSeqOverloadFlags(aOverrideNextMe, 0);
  Rules_RegisterHostFunction(aNextMethodp, 98, v3, (int)(intptr_t)Method_HasNextApplicableMethod, (int)(intptr_t)a00_2);
  Rules_SetFunctionSeqOverloadFlags(aNextMethodp, 0);
  Rules_RegisterHostFunction(aGnrcCurrentArg, 117, v4, (int)(intptr_t)Method_SaveCurrentArgContext, 0);
  Rules_RegisterHostFunction(aPpdefgeneric, 118, (int)(intptr_t)aPpdefgenericco, (int)(intptr_t)Defgeneric_PpdefgenericCommand, (int)(intptr_t)a11w_2);
  Rules_RegisterHostFunction(aListDefgeneric, 118, (int)(intptr_t)aListdefgeneric, (int)(intptr_t)Defgeneric_ListDefgenericsCommand, (int)(intptr_t)a01);
  Rules_RegisterHostFunction(aPpdefmethod, 118, (int)(intptr_t)aPpdefmethodcom, (int)(intptr_t)Defgeneric_PpdefmethodCommand, (int)(intptr_t)a22Wi);
  Rules_RegisterHostFunction(aListDefmethods, 118, (int)(intptr_t)aListdefmethods, (int)(intptr_t)Defgeneric_ListDefmethodsCommand, (int)(intptr_t)a01w_2);
  Rules_RegisterHostFunction(aPreviewGeneric, 118, (int)(intptr_t)aPreviewgeneric, (int)(intptr_t)Defgeneric_PreviewGenericCommand, (int)(intptr_t)a1W_0);
  Rules_RegisterHostFunction(aGetDefgenericL, 109, (int)(intptr_t)aGetdefgenericl, (int)(intptr_t)Defgeneric_GetDefgenericListCommand, (int)(intptr_t)a01);
  Rules_RegisterHostFunction(aGetDefmethodLi, 109, (int)(intptr_t)aGetdefmethodli, (int)(intptr_t)Defgeneric_GetDefmethodListCommand, (int)(intptr_t)a01w_2);
  Rules_RegisterHostFunction(aGetMethodRestr, 109, (int)(intptr_t)aGetmethodrestr, (int)(intptr_t)Defgeneric_GetMethodRestrictionsCommand, (int)(intptr_t)a22iw);
  Rules_RegisterHostFunction(aDefgenericModu, 119, (int)(intptr_t)aGetdefgenericm, (int)(intptr_t)Defgeneric_ModuleCommand, (int)(intptr_t)a11w_2);
  Rules_RegisterHostFunction(aType, 117, (int)(intptr_t)aClasscommand, (int)(intptr_t)Rules_ClassCommand, (int)(intptr_t)a11_1);
  Rules_AddWatchItem((int)(intptr_t)aGenericFunctio, 0, 34, (int)(intptr_t)&g_Rules_WatchGenericFunctions, (int)(intptr_t)Defgeneric_WatchAccessFunction, (int)(intptr_t)Defgeneric_WatchPrintFunction);
  return Rules_AddWatchItem((int)(intptr_t)aMethods, 0, 33, (int)(intptr_t)&g_Rules_WatchMethods, (int)(intptr_t)Defgeneric_MethodsWatchAccessFunction, (int)(intptr_t)Defgeneric_MethodsWatchPrintFunction);
}
// 497481: variable 'v0' is possibly undefined
// 4974EC: variable 'v1' is possibly undefined
// 497518: variable 'v2' is possibly undefined
// 497547: variable 'v3' is possibly undefined
// 497573: variable 'v4' is possibly undefined
// 51B3E0: using guessed type int dword_51B3E0;
// 51B3E4: using guessed type int dword_51B3E4;
// 54E6A0: using guessed type int dword_54E6A0;
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004976F0) --------------------------------------------------------
int  Defgeneric_ParseConstruct(_BYTE *genericName, int a2 CLASH95_UNUSED)
{
  return Rules_FindConstructByNameGeneric(genericName, g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497700) --------------------------------------------------------
int  Defgeneric_LookupWithImports(_BYTE *genericName)
{
  return Symbol_LookupInModule((char **)(uintptr_t)g_Clips_DefgenericConstructType, genericName, 1);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497720) --------------------------------------------------------
int  Defgeneric_LookupLocalOnly(_BYTE *genericName)
{
  return Symbol_LookupInModule((char **)(uintptr_t)g_Clips_DefgenericConstructType, genericName, 0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497740) --------------------------------------------------------
int  Defgeneric_GetNextInModule(int genericPtr)
{
  return Class_Enum(genericPtr, g_DefgenericModuleItemIndex);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497750) --------------------------------------------------------
int  Class_NextMethod(int theGeneric, int methodIndex)
{
  int methodArray; // esi
  int nextPosition; // edx
  int v5; // ecx

  if ( methodIndex )
  {
    nextPosition = Method_FindByIndex(theGeneric, methodIndex) + 1;
    if ( nextPosition == *(_DWORD *)(uintptr_t)(v5 + 32) )
      return 0;
    else
      return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 28) + 40 * nextPosition);
  }
  else
  {
    methodArray = *(_DWORD *)(uintptr_t)(theGeneric + 28);
    if ( methodArray )
      return *(_DWORD *)(uintptr_t)methodArray;
    else
      return 0;
  }
}
// 497771: variable 'v5' is possibly undefined

//----- (00497790) --------------------------------------------------------
BOOL Defgeneric_IsDeletable(void)
{
  int v0; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(uintptr_t)(v0 + 20) == 0;
}
// 4977A0: variable 'v0' is possibly undefined

//----- (00497800) --------------------------------------------------------
int __thiscall Defgeneric_UndefgenericCommand(void *this)
{
  return Rules_UndefconstructCommand((int)(intptr_t)this, g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497820) --------------------------------------------------------
int __thiscall Defgeneric_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497840) --------------------------------------------------------
signed int  Defgeneric_UndefmethodCommand(int returnValue, double context)
{
  signed int result; // eax
  int theGeneric; // ecx
  int methodIndex; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  _DWORD argData[6]; // [esp-4h] [ebp-24h] BYREF
  /* stack alias of argData[1] */
  /* stack alias of argData[2]: the DATA_OBJECT value slot */
  int savedReturnValue CLASH95_UNUSED; // [esp+18h] [ebp-8h]

  savedReturnValue = returnValue;
  result = Lexer_ParseValueList(1, argData, 2, context);
  if ( result )
  {
    if ( Symbol_LookupInModule((char **)(uintptr_t)g_Clips_DefgenericConstructType, (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argData[2] + 16), 1) || !strcmp_(0, asc_50529C) )
    {
      Rules_RtnUnknown(2, argData, context);
      if ( argData[1] == 2 )
      {
        methodIndex = strcmp_(theGeneric, asc_50529C);
        if ( methodIndex )
        {
LABEL_7:
          Rules_PrintErrorID((int)(intptr_t)aGenrccom, 2, 0);
          return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAVal_0, v5);
        }
      }
      else
      {
        if ( argData[1] != 1 )
          goto LABEL_7;
        methodIndex = *(_DWORD *)(uintptr_t)(argData[2] + 16);
        if ( !methodIndex )
          goto LABEL_7;
      }
      return Defgeneric_RemoveMethod(theGeneric, methodIndex);
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrccom, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoSuchGenericF, v6);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(argData[2] + 16), v7);
      return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunctionUnde, v8);
    }
  }
  return result;
}
// 4978E8: variable 'v5' is possibly undefined
// 49790F: variable 'v6' is possibly undefined
// 497920: variable 'v7' is possibly undefined
// 49792F: variable 'v8' is possibly undefined
// 497947: variable 'v3' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497970) --------------------------------------------------------
BOOL  Defgeneric_RemoveConstruct(int theConstruct)
{
  int v1; // ecx
  BOOL result; // eax
  int v3; // edx
  int v4; // ecx

  if ( theConstruct )
  {
    result = Defgeneric_IsDeletable();
    if ( result )
    {
      Rules_UnlinkListNode(v3);
      Defgeneric_RemoveDefgeneric(v3);
      return v4;
    }
  }
  else
  {
    Defgeneric_ClearDefgenericsReady();
    if ( !Defgeneric_ClearDefgenerics() )
      return 0;
    return v1;
  }
  return result;
}
// 497993: variable 'v1' is possibly undefined
// 4979A3: variable 'v3' is possibly undefined
// 4979AF: variable 'v4' is possibly undefined

//----- (004979C0) --------------------------------------------------------
int __fastcall Defgeneric_RemoveMethod(int theGeneric CLASH95_UNUSED, int methodIndex)
{
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  signed int methodPosition; // eax
  int v16; // ecx

  if ( Rules_IsBloaded() == 1 )
  {
    Rules_PrintErrorID((int)(intptr_t)aPrntutil_0, 4, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDelete, v7);
    if ( v8 )
    {
      v9 = Rules_GetConstructNameString(v8);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v9, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505344, v10);
      Rules_PrintLongInteger(v11, methodIndex);
    }
    else
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50529C, 0);
    }
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__15, v12);
    return 0;
  }
  else if ( v4 )
  {
    if ( Defgeneric_MethodsExecuting(v4) )
    {
      Defgeneric_PrintCannotModifyError();
      return 0;
    }
    else if ( v13 )
    {
      methodPosition = Defgeneric_CheckMethodExists((int)(intptr_t)aUndefmethod, v14, v13);
      if ( methodPosition == -1 )
        return 0;
      Defgeneric_DeleteMethod(v16, methodPosition);
      return 1;
    }
    else
    {
      Defgeneric_RemoveAllExplicitMethods(v14);
      return 1;
    }
  }
  else
  {
    if ( v3 )
    {
      Rules_PrintErrorID((int)(intptr_t)aGenrccom, 3, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIncompleteMeth, v5);
      return 0;
    }
    return Defgeneric_ClearDefgenericsReady();
  }
}
// 4979D3: variable 'v4' is possibly undefined
// 4979DB: variable 'v3' is possibly undefined
// 4979FC: variable 'v5' is possibly undefined
// 497A22: variable 'v7' is possibly undefined
// 497A29: variable 'v8' is possibly undefined
// 497A4B: variable 'v10' is possibly undefined
// 497A57: variable 'v11' is possibly undefined
// 497A66: variable 'v12' is possibly undefined
// 497A98: variable 'v13' is possibly undefined
// 497A9C: variable 'v14' is possibly undefined
// 497AD2: variable 'v16' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00497AE0) --------------------------------------------------------
_DWORD * Defgeneric_FormatMethodRestrictionsString(const char *buffer, int bufferMax, int methodIndex, int theGeneric)
{
  signed int methodPosition; // eax
  int v7; // ecx

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  return Defgeneric_AppendMethodSignatureText(buffer, bufferMax, v7, 40 * methodPosition + *(_DWORD *)(uintptr_t)(theGeneric + 28));
}
// 497B0A: variable 'v7' is possibly undefined

//----- (00497B20) --------------------------------------------------------
int  Defgeneric_GetTraceFlag(int theGeneric)
{
  return *(_DWORD *)(uintptr_t)(theGeneric + 24);
}

//----- (00497B30) --------------------------------------------------------
int  Defgeneric_SetTraceFlag(int result, int theGeneric)
{
  *(_DWORD *)(uintptr_t)(theGeneric + 24) = result;
  return result;
}

//----- (00497B40) --------------------------------------------------------
int  Defgeneric_GetMethodTraceFlag(int theGeneric, int methodIndex)
{
  signed int methodPosition; // eax
  int v3; // ecx

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v3 + 28) + 40 * methodPosition + 24) << 30 >> 31;
}
// 497B53: variable 'v3' is possibly undefined

//----- (00497B70) --------------------------------------------------------
int  Defgeneric_SetMethodTraceFlag(char newState, int theGeneric, int methodIndex)
{
  signed int methodPosition; // eax
  int v5; // ecx
  int result; // eax

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  result = *(_DWORD *)(uintptr_t)(v5 + 28) + 40 * methodPosition;
  *(_BYTE *)(uintptr_t)(result + 24) &= ~2u;
  *(_DWORD *)(uintptr_t)(result + 24) |= 2 * (newState & 1);
  return result;
}
// 497B91: variable 'v5' is possibly undefined

//----- (00497BB0) --------------------------------------------------------
int __thiscall Defgeneric_PpdefgenericCommand(void *this)
{
  return Rules_PPConstructCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497BD0) --------------------------------------------------------
int  Defgeneric_PpdefmethodCommand(int returnValue, double context)
{
  int result; // eax
  _BYTE *genericName; // esi
  int v4; // ecx
  int methodPtr; // edx
  _DWORD argData[6]; // DATA_OBJECT BYREF
  /* stack alias of argData[2]: the value slot */
  int savedReturnValue CLASH95_UNUSED; // [esp+18h] [ebp-8h]

  savedReturnValue = returnValue;
  result = Lexer_ParseValueList(1, argData, 2, context);
  if ( result )
  {
    genericName = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argData[2] + 16);
    result = Lexer_ParseValueList(2, argData, 1, context);
    if ( result )
    {
      result = Defgeneric_CheckGenericExists((int)(intptr_t)aPpdefmethod, genericName);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)(intptr_t)aPpdefmethod, result, *(_DWORD *)(uintptr_t)(argData[2] + 16));
        if ( result != -1 )
        {
          result *= 40;
          methodPtr = result + *(_DWORD *)(uintptr_t)(v4 + 28);
          if ( *(_DWORD *)(uintptr_t)(methodPtr + 36) )
            return Output_WriteLongString((signed int)(intptr_t)g_IO_LogicalName_WDisplay, (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(methodPtr + 36));
        }
      }
    }
  }
  return result;
}
// 497C56: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;
