/* CLIPS events, handlers, patterns, and runtime metadata.
 * Original function-marker range: 0x00496000..0x0049FF80.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00496000) --------------------------------------------------------
int Event_ClearHandlers()
{
  int result; // eax

  for ( result = Rules_GetFunctionDefinitionListHead(); result; result = *(_DWORD *)(result + 27) )
    *(_WORD *)(result + 25) = 0;
  return result;
}

//----- (00496030) --------------------------------------------------------
int Event_InitHandlers()
{
  int i; // edx
  int result; // eax
  int currentItem; // edx

  for ( i = g_BinaryItemListHead; i; i = *(_DWORD *)(currentItem + 36) )
  {
    while ( !*(_DWORD *)(i + 4) )
    {
      i = *(_DWORD *)(i + 36);
      if ( !i )
        return result;
    }
    result = (*(int (**)(void))(i + 4))();
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
  for ( i = Rules_GetFunctionDefinitionListHead(); i; i = *(_DWORD *)(i + 27) )
  {
    if ( *(_WORD *)(i + 25) )
    {
      assignedIndex = functionCount[0];
      ++functionCount[0];
      *(_WORD *)(i + 25) = assignedIndex;
    }
    else
    {
      *(_WORD *)(i + 25) = -1;
    }
  }
  Rules_BsaveWriteBlock(4, fp, functionCount);
  if ( !functionCount[0] )
    return Rules_BsaveWriteBlock(4, fp, functionCount);
  space = Rules_BsaveFunctionNamesLength();
  Rules_BsaveWriteBlock(4, fp, &space);
  result = (const void *)Rules_GetFunctionDefinitionListHead();
  functionCursor = (int)result;
  if ( result )
  {
    do
    {
      if ( *(__int16 *)(functionCursor + 25) >= 0 )
        result = Rules_BsaveWriteBlock(strlen(*(const char **)(*(_DWORD *)functionCursor + 16)) + 1, fp, *(const void **)(*(_DWORD *)functionCursor + 16));
      functionCursor = *(_DWORD *)(functionCursor + 27);
    }
    while ( functionCursor );
  }
  return result;
}

//----- (00496130) --------------------------------------------------------
int Rules_BsaveFunctionNamesLength()
{
  int functionDef; // edx
  int totalLength; // ebx

  functionDef = Rules_GetFunctionDefinitionListHead();
  totalLength = 0;
  if ( !functionDef )
    return totalLength;
  do
  {
    while ( *(__int16 *)(functionDef + 25) < 0 )
    {
      functionDef = *(_DWORD *)(functionDef + 27);
      if ( !functionDef )
        return totalLength;
    }
    totalLength += strlen(*(const char **)(*(_DWORD *)functionDef + 16)) + 1;
    functionDef = *(_DWORD *)(functionDef + 27);
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

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListHead;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  *result = item;
  newNode = result;
  if ( g_ClipsConstructQueueHead )
  {
    for ( result = (_DWORD *)g_ClipsConstructQueueHead; result[1]; result = (_DWORD *)result[1] )
      ;
    result[1] = newNode;
  }
  else
  {
    g_ClipsConstructQueueHead = (int)result;
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

  *itemOut = *(_DWORD *)g_ClipsConstructQueueHead;
  poppedNode = (_DWORD *)g_ClipsConstructQueueHead;
  g_ClipsConstructQueueHead = *(_DWORD *)(g_ClipsConstructQueueHead + 4);
  g_ClipsMemFreeListTemp = (int)poppedNode;
  *poppedNode = *(_DWORD *)(g_ClipsMemoryTable + 32);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
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
      if ( (unsigned __int16)result >= 0xAu )
      {
        if ( (unsigned __int16)result <= 0xAu )
        {
          result = *(__int16 **)(i + 1);
          *(__int16 *)((char *)result + 25) = 1;
          goto LABEL_4;
        }
        if ( (unsigned __int16)result < 0xDu )
          goto LABEL_10;
        if ( (unsigned __int16)result > 0xDu )
        {
          if ( (_WORD)result == 105 )
            goto LABEL_4;
LABEL_10:
          result = (__int16 *)(4 * *i);
          entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + (_DWORD)result);
          if ( !entityRecord || (*(_BYTE *)(entityRecord + 1) & 0x40) == 0 )
            goto LABEL_4;
        }
      }
      else if ( (_WORD)result != 8 )
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
  return (__int16)result;
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

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 160);
  prevItem = 0;
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *freeListHead;
    newItem = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newItem = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x28);
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
  newItemAddr = (int)newItem;
  if ( !g_BinaryItemListHead )
  {
    newItem[9] = 0;
    g_BinaryItemListHead = (int)newItem;
    return 1;
  }
  currentItem = g_BinaryItemListHead;
  do
  {
    if ( priority >= *(_DWORD *)(currentItem + 32) )
      break;
    prevItem = currentItem;
    currentItem = *(_DWORD *)(currentItem + 36);
  }
  while ( currentItem );
  if ( !prevItem )
  {
    *(_DWORD *)(newItemAddr + 36) = g_BinaryItemListHead;
    g_BinaryItemListHead = newItemAddr;
    return 1;
  }
  *(_DWORD *)(newItemAddr + 36) = currentItem;
  *(_DWORD *)(prevItem + 36) = newItemAddr;
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
    return (const void *)fwrite_(result, size, fp, 1);
  return result;
}

//----- (004967B0) --------------------------------------------------------
signed int Rules_RegisterConstraintCheckingCommands()
{
  int i; // eax

  g_ConstraintHashTable = (int)Mem_SmallBlockAlloc(0x29Cu);
  if ( !g_ConstraintHashTable )
    IO_RunRouterExitCallbacks();
  for ( i = 0; i != 668; i += 4 )
    *(_DWORD *)(g_ConstraintHashTable + i) = 0;
  Rules_RegisterHostFunction(aGetDynamicCons, 98, (int)aGdccommand, (int)Rules_GetDynamicConstraintCheckingCommand, (int)a00_14);
  Rules_RegisterHostFunction(aSetDynamicCons, 98, (int)aSdccommand, (int)Rules_SetDynamicConstraintCheckingCommand, (int)a11_0);
  Rules_RegisterHostFunction(aGetStaticConst, 98, (int)aGsccommand, (int)Rules_GetStaticConstraintCheckingCommand, (int)a00_14);
  return Rules_RegisterHostFunction(aSetStaticConst, 98, (int)aSsccommand, (int)Rules_SetStaticConstraintCheckingCommand, (int)a11_0);
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
    if ( *(int *)(result + 34) < 0 )
    {
      AST_Free(*(_DWORD *)(result + 6));
      AST_Free(*(_DWORD *)(v3 + 14));
      AST_Free(*(_DWORD *)(v4 + 10));
      AST_Free(*(_DWORD *)(v5 + 18));
      AST_Free(*(_DWORD *)(v6 + 22));
    }
    AST_FreeNodeChildren(*(_DWORD *)(constraints + 26));
    g_ClipsMemFreeListTemp = (int)v2;
    *v2 = *(_DWORD *)(g_ClipsMemoryTable + 168);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 168) = g_ClipsMemFreeListTemp;
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
__int16 * AST_ReleaseNodeChildSlots(int constraints, int a2)
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
    while ( *(int *)(constraints + 34) < 0 )
    {
      AST_DeinstallNodeChain(*(__int16 **)(constraints + 6));
      AST_DeinstallNodeChain(*(__int16 **)(v3 + 14));
      AST_DeinstallNodeChain(*(__int16 **)(v4 + 10));
      AST_DeinstallNodeChain(*(__int16 **)(v5 + 18));
      result = AST_DeinstallNodeChain(*(__int16 **)(v6 + 22));
      if ( !*(_DWORD *)(v8 + 26) )
        return result;
      constraints = *(_DWORD *)(v8 + 26);
    }
    AST_RemoveHashedNodeChain(*(__int16 **)(constraints + 6), a2);
    AST_RemoveHashedNodeChain(*(__int16 **)(v9 + 14), v10);
    AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 10), v12);
    AST_RemoveHashedNodeChain(*(__int16 **)(v13 + 18), v14);
    result = AST_RemoveHashedNodeChain(*(__int16 **)(v15 + 22), v16);
    if ( !*(_DWORD *)(v17 + 26) )
      break;
    constraints = *(_DWORD *)(v17 + 26);
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

  v1 = (int)result;
  prevConstraint = 0;
  if ( result )
  {
    bucketIndex = *(_DWORD *)((char *)result + 34);
    if ( bucketIndex < 0 )
    {
      return (_DWORD *)AST_FreeNodeChildren((int)result);
    }
    else
    {
      result = *(_DWORD **)(g_ConstraintHashTable + 4 * bucketIndex);
      if ( result )
      {
        while ( result != (_DWORD *)v1 )
        {
          prevConstraint = result;
          result = *(_DWORD **)((char *)result + 30);
          if ( !result )
            return result;
        }
        newCount = *(_DWORD *)(v1 + 38) - 1;
        *(_DWORD *)(v1 + 38) = newCount;
        if ( !newCount )
        {
          if ( prevConstraint )
          {
            *(_DWORD *)((char *)prevConstraint + 30) = *(_DWORD *)(v1 + 30);
          }
          else
          {
            prevConstraint = (_DWORD *)(4 * *(_DWORD *)(v1 + 34) + g_ConstraintHashTable);
            *prevConstraint = *(_DWORD *)(v1 + 30);
          }
          AST_ReleaseNodeChildSlots(v1, (int)prevConstraint);
          return (_DWORD *)AST_FreeNodeChildren(v5);
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
  __int16 *restrictionList; // edi
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

  restrictionList = *(__int16 **)((char *)theConstraint + 6);
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
          + 17 * (*theConstraint & 1); restrictionList; i += fieldHash )
  {
    fieldHash = Rules_ComputeFieldHashValue(*restrictionList, *(_DWORD *)(restrictionList + 1), count);
    count = v6 + 1;
    restrictionList = *(__int16 **)(restrictionList + 5);
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
    existingConstraint = *(_DWORD **)(g_ConstraintHashTable + 4 * hashValue);
    savedHash = hashValue;
    if ( existingConstraint )
    {
      while ( !AST_NodesStructurallyEqual(theConstraint, existingConstraint) )
      {
        existingConstraint = *(_DWORD **)(v5 + 30);
        if ( !existingConstraint )
          goto LABEL_5;
      }
      ++*(_DWORD *)(v5 + 38);
      AST_FreeNodeChildren((int)theConstraint);
      return (_DWORD *)v6;
    }
    else
    {
LABEL_5:
      AST_CollapseNodeChildSlots((int)theConstraint, (int)existingConstraint);
      *(_DWORD *)((char *)theConstraint + 38) = 1;
      *(_DWORD *)((char *)theConstraint + 34) = savedHash;
      *(_DWORD *)((char *)theConstraint + 30) = *(_DWORD *)(g_ConstraintHashTable + 4 * savedHash);
      *(_DWORD *)(g_ConstraintHashTable + 4 * savedHash) = theConstraint;
      return theConstraint;
    }
  }
  return result;
}
// 496F90: variable 'v5' is possibly undefined
// 496FD0: variable 'v6' is possibly undefined
// 54E694: using guessed type int dword_54E694;

//----- (00496FE0) --------------------------------------------------------
int  AST_CollapseNodeChildSlots(int constraints, int a2)
{
  int v3; // edx
  int v4; // edx
  __int16 *v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  __int16 *v9; // eax
  int v10; // ecx
  int v11; // edx
  int v12; // edx
  __int16 *v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // edx
  __int16 *v17; // eax
  int v18; // ecx
  int v19; // edx
  int result; // eax
  int v21; // edx
  int v22; // ecx

  while ( 1 )
  {
    AST_AddHashedNodeChain(*(__int16 **)(constraints + 6), constraints, a2);
    AST_Free(*(_DWORD *)(v3 + 6));
    v5 = *(__int16 **)(v4 + 14);
    *(_DWORD *)(v4 + 6) = v6;
    AST_AddHashedNodeChain(v5, v4, v6);
    AST_Free(*(_DWORD *)(v7 + 14));
    v9 = *(__int16 **)(v8 + 10);
    *(_DWORD *)(v8 + 14) = v10;
    AST_AddHashedNodeChain(v9, v8, v10);
    AST_Free(*(_DWORD *)(v11 + 10));
    v13 = *(__int16 **)(v12 + 18);
    *(_DWORD *)(v12 + 10) = v14;
    AST_AddHashedNodeChain(v13, v12, v14);
    AST_Free(*(_DWORD *)(v15 + 18));
    v17 = *(__int16 **)(v16 + 22);
    *(_DWORD *)(v16 + 18) = v18;
    AST_AddHashedNodeChain(v17, v16, v18);
    result = AST_Free(*(_DWORD *)(v19 + 22));
    *(_DWORD *)(v21 + 22) = v22;
    a2 = *(_DWORD *)(v21 + 26);
    if ( !a2 )
      break;
    constraints = *(_DWORD *)(v21 + 26);
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
int  Rules_SetDynamicConstraintCheckingCommand(int a1, double context)
{
  int argCheck; // eax
  int v4; // ecx
  int v5; // esi
  int argBuffer; // [esp-4h] [ebp-28h] BYREF
  __int64 argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  argCheck = Lexer_TokenExpect(1);
  v5 = v4;
  if ( argCheck == -1 )
    return v4;
  Rules_RtnUnknown(1, &argBuffer, context);
  g_CLIPS_DynamicConstraintCheckingFlag = argValue != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 49707E: variable 'v4' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;
// 54DD70: using guessed type int dword_54DD70;

//----- (004970E0) --------------------------------------------------------
int Rules_GetDynamicConstraintCheckingCommand()
{
  int currentFlag; // ecx

  Lexer_TokenExpect(0);
  return currentFlag;
}
// 4970FA: variable 'v0' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;

//----- (00497100) --------------------------------------------------------
int  Rules_SetStaticConstraintCheckingCommand(int a1, double context)
{
  int argCheck; // eax
  int v4; // ecx
  int v5; // esi
  int argBuffer; // [esp-4h] [ebp-28h] BYREF
  __int64 argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  argCheck = Lexer_TokenExpect(1);
  v5 = v4;
  if ( argCheck == -1 )
    return v4;
  Rules_RtnUnknown(1, &argBuffer, context);
  g_CLIPS_StaticConstraintCheckingFlag = argValue != __PAIR64__(g_ClipsFalseSymbol, 2);
  return v5;
}
// 49711E: variable 'v4' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00497180) --------------------------------------------------------
int Rules_GetStaticConstraintCheckingCommand()
{
  int currentFlag; // ecx

  Lexer_TokenExpect(0);
  return currentFlag;
}
// 49719A: variable 'v0' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;

//----- (004971A0) --------------------------------------------------------
int __fastcall Rules_SetDynamicConstraintChecking(int a1, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = g_CLIPS_DynamicConstraintCheckingFlag;
  g_CLIPS_DynamicConstraintCheckingFlag = a1;
  return previous_state;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971B0) --------------------------------------------------------
int Rules_DynamicConstraintCheckingEnabled()
{
  return g_CLIPS_DynamicConstraintCheckingFlag;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971D0) --------------------------------------------------------
int Rules_StaticConstraintCheckingEnabled()
{
  return g_CLIPS_StaticConstraintCheckingFlag;
}
// 51AAB0: using guessed type int dword_51AAB0;

//----- (004971E0) --------------------------------------------------------
_DWORD *Rules_InitDeffactsConstruct()
{
  _DWORD *result; // eax

  Rules_RegisterDeffactsModuleItem();
  Deffacts_CommandDefinitions();
  result = Rules_RegisterConstructType(
             (int)aDeffacts,
             (int)aDeffacts,
             (int)Rules_ParseDeffactsConstruct,
             (int)Deffacts_ParseAndInstall,
             (int)Rules_GetConstructNameSymbol,
             (int)Rules_GetModuleConstructListHead,
             (int)Rules_GetConstructOwnerModule,
             (int)Rules_DeffactsGetNextItem,
             (int)Rules_SetConstructNextInModule,
             (int)Rules_DeffactsIsDeletable,
             (int)Deffacts_DeleteConstruct,
             (int)Deffacts_FreeConstruct);
  g_ClipsDeffactsConstructType = (int)result;
  return result;
}
// 497310: using guessed type int sub_497310();
// 54E69C: using guessed type int dword_54E69C;

//----- (00497240) --------------------------------------------------------
int Rules_RegisterDeffactsModuleItem()
{
  int result; // eax

  result = Module_RegisterItem(
             (int)aDeffacts,
             (int)Rules_AllocDeffactsModuleData,
             (int)Deffacts_GetModuleItem,
             (int)Rules_FreeDeffactsModuleData,
             (int)Deffacts_PrintModuleReference,
             (int)Rules_ParseDeffactsConstruct);
  g_ClipsDeffactsModuleItemId = result;
  return result;
}
// 54E698: using guessed type int dword_54E698;

//----- (00497270) --------------------------------------------------------
signed int Rules_AllocDeffactsModuleData()
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListHead;
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
  *(_DWORD *)theModuleItem = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
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
int  Rules_ParseDeffactsConstruct(_BYTE *constructName, int a2)
{
  return Rules_FindConstructByNameGeneric(constructName, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (00497300) --------------------------------------------------------
int  Rules_DeffactsGetNextItem(int deffactsPtr)
{
  return Class_Enum(deffactsPtr, g_ClipsDeffactsModuleItemId);
}
// 54E698: using guessed type int dword_54E698;

//----- (00497310) --------------------------------------------------------
int Rules_DeffactsIsDeletable()
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
    expression = *(_DWORD *)(fact + 20);
    AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)expression);
    AST_FreePackedNodeChain(expression);
    Rules_FreeConstructHeaderString((int *)(uintptr_t)(unsigned int)fact, fact);
    g_ClipsMemFreeListTemp = fact;
    *(_DWORD *)fact = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    result = g_ClipsMemoryTable;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00497370) --------------------------------------------------------
int Defgeneric_SetupConstruct()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_Defgeneric, 11);
  g_DefgenericModuleItemIndex = Module_RegisterItem(
                   (int)aDefgeneric,
                   (int)Defgeneric_AllocateModule,
                   (int)Defgeneric_RecordAtIndex,
                   (int)Defgeneric_FreeModule,
                   (int)Defgeneric_PrintModuleReference,
                   (int)Defgeneric_ParseConstruct);
  g_Clips_DefgenericConstructType = (int)Rules_RegisterConstructType(
                        (int)aDefgeneric,
                        (int)aDefgenerics,
                        (int)Defgeneric_ParseConstruct,
                        (int)Defgeneric_ParseDefgeneric,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Defgeneric_GetNextInModule,
                        (int)Rules_SetConstructNextInModule,
                        (int)Defgeneric_IsDeletable,
                        (int)Defgeneric_RemoveConstruct,
                        (int)Defgeneric_RemoveDefgeneric);
  Rules_AddClearReadyFunction((int)aDefgeneric, (int)Defgeneric_NoActiveCall, 0);
  Defgeneric_RegisterBinaryItem();
  Defgeneric_CompilerSetup();
  Module_RegisterImportExportConstructType((int)aDefgeneric, 2);
  Rules_RegisterConstructType((int)aDefmethod, (int)aDefmethods, 0, (int)Defgeneric_ParseDefmethod, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_AddSaveFunction((int)aDefgeneric, (int)Defgeneric_SaveConstructs, 1000);
  Rules_AddSaveFunction((int)aDefmethod, (int)Defmethod_SaveConstructs, -1000);
  Rules_RegisterHostFunction(aUndefgeneric, 118, v0, (int)Defgeneric_UndefgenericCommand, (int)a11w_2);
  Rules_RegisterHostFunction(aUndefmethod, 118, (int)aUndefmethodcom, (int)Defgeneric_UndefmethodCommand, (int)a22Wg);
  Rules_RegisterHostFunction(aCallNextMethod, 117, (int)aCallnextmethod, (int)Method_OverrideNextMethod, (int)a00_2);
  Rules_SetFunctionSeqOverloadFlags(aCallNextMethod, 0);
  Rules_RegisterHostFunction(aCallSpecificMe, 117, v1, (int)Method_EvaluateCallSpecificMethod, (int)a2Wi);
  Rules_SetFunctionSeqOverloadFlags(aCallSpecificMe, 0);
  Rules_RegisterHostFunction(aOverrideNextMe, 117, v2, (int)Method_CallNextMethod, 0);
  Rules_SetFunctionSeqOverloadFlags(aOverrideNextMe, 0);
  Rules_RegisterHostFunction(aNextMethodp, 98, v3, (int)Method_HasNextApplicableMethod, (int)a00_2);
  Rules_SetFunctionSeqOverloadFlags(aNextMethodp, 0);
  Rules_RegisterHostFunction(aGnrcCurrentArg, 117, v4, (int)Method_SaveCurrentArgContext, 0);
  Rules_RegisterHostFunction(aPpdefgeneric, 118, (int)aPpdefgenericco, (int)Defgeneric_PpdefgenericCommand, (int)a11w_2);
  Rules_RegisterHostFunction(aListDefgeneric, 118, (int)aListdefgeneric, (int)Defgeneric_ListDefgenericsCommand, (int)a01);
  Rules_RegisterHostFunction(aPpdefmethod, 118, (int)aPpdefmethodcom, (int)Defgeneric_PpdefmethodCommand, (int)a22Wi);
  Rules_RegisterHostFunction(aListDefmethods, 118, (int)aListdefmethods, (int)Defgeneric_ListDefmethodsCommand, (int)a01w_2);
  Rules_RegisterHostFunction(aPreviewGeneric, 118, (int)aPreviewgeneric, (int)Defgeneric_PreviewGenericCommand, (int)a1W_0);
  Rules_RegisterHostFunction(aGetDefgenericL, 109, (int)aGetdefgenericl, (int)Defgeneric_GetDefgenericListCommand, (int)a01);
  Rules_RegisterHostFunction(aGetDefmethodLi, 109, (int)aGetdefmethodli, (int)Defgeneric_GetDefmethodListCommand, (int)a01w_2);
  Rules_RegisterHostFunction(aGetMethodRestr, 109, (int)aGetmethodrestr, (int)Defgeneric_GetMethodRestrictionsCommand, (int)a22iw);
  Rules_RegisterHostFunction(aDefgenericModu, 119, (int)aGetdefgenericm, (int)Defgeneric_ModuleCommand, (int)a11w_2);
  Rules_RegisterHostFunction(aType, 117, (int)aClasscommand, (int)Rules_ClassCommand, (int)a11_1);
  Rules_AddWatchItem((int)aGenericFunctio, 0, 34, (int)&g_Rules_WatchGenericFunctions, (int)Defgeneric_WatchAccessFunction, (int)Defgeneric_WatchPrintFunction);
  return Rules_AddWatchItem((int)aMethods, 0, 33, (int)&g_Rules_WatchMethods, (int)Defgeneric_MethodsWatchAccessFunction, (int)Defgeneric_MethodsWatchPrintFunction);
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
int  Defgeneric_ParseConstruct(_BYTE *genericName, int a2)
{
  return Rules_FindConstructByNameGeneric(genericName, a2);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497700) --------------------------------------------------------
int  Defgeneric_LookupWithImports(_BYTE *genericName)
{
  return Symbol_LookupInModule((char **)g_Clips_DefgenericConstructType, genericName, 1);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497720) --------------------------------------------------------
int  Defgeneric_LookupLocalOnly(_BYTE *genericName)
{
  return Symbol_LookupInModule((char **)g_Clips_DefgenericConstructType, genericName, 0);
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
    if ( nextPosition == *(_DWORD *)(v5 + 32) )
      return 0;
    else
      return *(_DWORD *)(*(_DWORD *)(v5 + 28) + 40 * nextPosition);
  }
  else
  {
    methodArray = *(_DWORD *)(theGeneric + 28);
    if ( methodArray )
      return *(_DWORD *)methodArray;
    else
      return 0;
  }
}
// 497771: variable 'v5' is possibly undefined

//----- (00497790) --------------------------------------------------------
BOOL Defgeneric_IsDeletable()
{
  int v0; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(v0 + 20) == 0;
}
// 4977A0: variable 'v0' is possibly undefined

//----- (00497800) --------------------------------------------------------
int __thiscall Defgeneric_UndefgenericCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497820) --------------------------------------------------------
int __thiscall Defgeneric_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497840) --------------------------------------------------------
signed int  Defgeneric_UndefmethodCommand(int a1, double context)
{
  signed int result; // eax
  int theGeneric; // ecx
  int methodIndex; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int argData; // [esp-4h] [ebp-24h] BYREF
  int argType; // [esp+0h] [ebp-20h]
  int argValue; // [esp+4h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-8h]

  v12 = a1;
  result = Lexer_ParseValueList(1, &argData, 2, context);
  if ( result )
  {
    if ( Symbol_LookupInModule((char **)g_Clips_DefgenericConstructType, *(_BYTE **)(argValue + 16), 1) || !strcmp_(0, asc_50529C) )
    {
      Rules_RtnUnknown(2, &argData, context);
      if ( argType == 2 )
      {
        methodIndex = strcmp_(theGeneric, asc_50529C);
        if ( methodIndex )
        {
LABEL_7:
          Rules_PrintErrorID((int)aGenrccom, 2, 0);
          return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_0, v5);
        }
      }
      else
      {
        if ( argType != 1 )
          goto LABEL_7;
        methodIndex = *(_DWORD *)(argValue + 16);
        if ( !methodIndex )
          goto LABEL_7;
      }
      return Defgeneric_RemoveMethod(theGeneric, methodIndex);
    }
    else
    {
      Rules_PrintErrorID((int)aGenrccom, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchGenericF, v6);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(argValue + 16), v7);
      return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunctionUnde, v8);
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
BOOL  Defgeneric_RemoveConstruct(int a1)
{
  int v1; // ecx
  BOOL result; // eax
  int v3; // edx
  int v4; // ecx

  if ( a1 )
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
int __fastcall Defgeneric_RemoveMethod(int theGeneric, int methodIndex)
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
    Rules_PrintErrorID((int)aPrntutil_0, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDelete, v7);
    if ( v8 )
    {
      v9 = Rules_GetConstructNameString(v8);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v9, (int)g_IO_LogicalNameTable_WError[0]);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505344, v10);
      Rules_PrintLongInteger(v11, methodIndex);
    }
    else
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50529C, 0);
    }
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__15, v12);
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
      methodPosition = Defgeneric_CheckMethodExists((int)aUndefmethod, v14, v13);
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
      Rules_PrintErrorID((int)aGenrccom, 3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIncompleteMeth, v5);
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
  return Defgeneric_AppendMethodSignatureText(buffer, bufferMax, v7, 40 * methodPosition + *(_DWORD *)(theGeneric + 28));
}
// 497B0A: variable 'v7' is possibly undefined

//----- (00497B20) --------------------------------------------------------
int  Defgeneric_GetTraceFlag(int theGeneric)
{
  return *(_DWORD *)(theGeneric + 24);
}

//----- (00497B30) --------------------------------------------------------
int  Defgeneric_SetTraceFlag(int result, int theGeneric)
{
  *(_DWORD *)(theGeneric + 24) = result;
  return result;
}

//----- (00497B40) --------------------------------------------------------
int  Defgeneric_GetMethodTraceFlag(int theGeneric, int methodIndex)
{
  signed int methodPosition; // eax
  int v3; // ecx

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  return *(_DWORD *)(*(_DWORD *)(v3 + 28) + 40 * methodPosition + 24) << 30 >> 31;
}
// 497B53: variable 'v3' is possibly undefined

//----- (00497B70) --------------------------------------------------------
int  Defgeneric_SetMethodTraceFlag(char newState, int theGeneric, int methodIndex)
{
  signed int methodPosition; // eax
  int v5; // ecx
  int result; // eax

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  result = *(_DWORD *)(v5 + 28) + 40 * methodPosition;
  *(_BYTE *)(result + 24) &= ~2u;
  *(_DWORD *)(result + 24) |= 2 * (newState & 1);
  return result;
}
// 497B91: variable 'v5' is possibly undefined

//----- (00497BB0) --------------------------------------------------------
int __thiscall Defgeneric_PpdefgenericCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497BD0) --------------------------------------------------------
int  Defgeneric_PpdefmethodCommand(int a1, double context)
{
  int result; // eax
  _BYTE *genericName; // esi
  int v4; // ecx
  int methodPtr; // edx
  _DWORD argData[2]; // [esp-8h] [ebp-28h] BYREF
  int argValue; // [esp+0h] [ebp-20h]
  int v8; // [esp+18h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, argData, 2, context);
  if ( result )
  {
    genericName = *(_BYTE **)(argValue + 16);
    result = Lexer_ParseValueList(2, argData, 1, context);
    if ( result )
    {
      result = Defgeneric_CheckGenericExists((int)aPpdefmethod, genericName);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)aPpdefmethod, result, *(_DWORD *)(argValue + 16));
        if ( result != -1 )
        {
          result *= 40;
          methodPtr = result + *(_DWORD *)(v4 + 28);
          if ( *(_DWORD *)(methodPtr + 36) )
            return Output_WriteLongString((signed int)g_IO_LogicalName_WDisplay, *(char **)(methodPtr + 36));
        }
      }
    }
  }
  return result;
}
// 497C56: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (00497C80) --------------------------------------------------------
int  Defgeneric_ListDefmethodsCommand(int a1, double context)
{
  int v2; // ecx
  int result; // eax
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  if ( !Rules_RtnArgCount() )
    return Defgeneric_ListMethodsAndTally((int)g_IO_LogicalName_WDisplay, 0, v2);
  result = Lexer_ParseValueList(1, argData, 2, context);
  if ( result )
  {
    result = Defgeneric_CheckGenericExists((int)aListDefmethods, *(_BYTE **)(argData[2] + 16));
    if ( result )
      return Defgeneric_ListMethodsAndTally((int)g_IO_LogicalName_WDisplay, result, (int)g_IO_LogicalName_WDisplay);
  }
  return result;
}
// 497CB7: variable 'v2' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (00497D10) --------------------------------------------------------
int  Defgeneric_ListDefgenericsCommand(int logicalName, double context)
{
  return Rules_ListConstructsCommand(g_Clips_DefgenericConstructType, logicalName, context);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497D50) --------------------------------------------------------
int  Defgeneric_ListMethodsAndTally(int logicalName, int theGeneric, int a3)
{
  int methodCount; // edi
  int i; // ecx
  int v6; // ecx
  int v7; // ecx

  if ( theGeneric )
  {
    methodCount = Defgeneric_PrintMethodsList(a3, theGeneric);
  }
  else
  {
    methodCount = 0;
    for ( i = Class_Enum(0, g_DefgenericModuleItemIndex); i; i = Class_Enum(v7, g_DefgenericModuleItemIndex) )
    {
      methodCount += Defgeneric_PrintMethodsList(i, i);
      if ( Class_Enum(v6, g_DefgenericModuleItemIndex) )
        Output_Write(logicalName, (int)asc_50537C, v7);
    }
  }
  return Rules_PrintTally(logicalName, methodCount, (int)aMethods, (int)aMethod_1);
}
// 497D82: variable 'v6' is possibly undefined
// 497D92: variable 'v7' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497DD0) --------------------------------------------------------
_DWORD * Defgeneric_GetDefgenericListCommand(int returnValue, double context)
{
  return Rules_GetConstructListCommand(returnValue, g_Clips_DefgenericConstructType, context);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497E10) --------------------------------------------------------
_DWORD * Defgeneric_GetDefmethodListCommand(_DWORD *returnValue, int a2, double context)
{
  int theGeneric; // eax
  _DWORD argData[10]; // [esp-8h] [ebp-28h] BYREF

  argData[8] = a2;
  theGeneric = Rules_RtnArgCount();
  if ( !theGeneric )
    return Defgeneric_BuildMethodListValue(theGeneric, returnValue);
  if ( Lexer_ParseValueList(1, argData, 2, context) && (theGeneric = Defgeneric_CheckGenericExists((int)aGetDefmethodLi, *(_BYTE **)(argData[2] + 16))) != 0 )
    return Defgeneric_BuildMethodListValue(theGeneric, returnValue);
  else
    return Rules_SetMultifieldErrorValue((int)returnValue);
}

//----- (00497E70) --------------------------------------------------------
_DWORD * Defgeneric_BuildMethodListValue(int theGeneric, _DWORD *returnValue)
{
  int v4; // eax
  int genericCursor; // ecx
  int i; // ebx
  signed int multifieldSize; // ebx
  _DWORD *result; // eax
  int v9; // ecx
  int currentGeneric; // ebx
  _DWORD *theMultifield; // edi
  int v12; // esi
  int v13; // ebp
  int v14; // ecx
  int v15; // ecx
  unsigned int v16; // edx
  int savedNext; // [esp+0h] [ebp-20h]
  int v18; // [esp+4h] [ebp-1Ch]
  int firstGeneric; // [esp+8h] [ebp-18h]

  if ( theGeneric )
  {
    savedNext = Class_Enum(theGeneric, g_DefgenericModuleItemIndex);
    Rules_SetConstructNextInModule(theGeneric, 0);
  }
  else
  {
    v4 = Class_Enum(0, g_DefgenericModuleItemIndex);
    genericCursor = v4;
    if ( v4 )
      v4 = Class_Enum(v4, g_DefgenericModuleItemIndex);
    savedNext = v4;
  }
  firstGeneric = genericCursor;
  for ( i = 0; genericCursor; genericCursor = Class_Enum(genericCursor, g_DefgenericModuleItemIndex) )
    i += *(_DWORD *)(genericCursor + 32);
  multifieldSize = 2 * i;
  returnValue[1] = 4;
  returnValue[4] = multifieldSize - 1;
  returnValue[3] = 0;
  result = Rules_CreateEphemeralMultifield(multifieldSize);
  currentGeneric = firstGeneric;
  theMultifield = result;
  returnValue[2] = result;
  if ( firstGeneric )
  {
    do
    {
      if ( *(_DWORD *)(currentGeneric + 32) )
      {
        v12 = 0;
        do
        {
          v13 = 6 * (v9 - 1);
          v18 = v9;
          *(_WORD *)((char *)theMultifield + v13 + 14) = 2;
          *(_DWORD *)((char *)theMultifield + v13 + 16) = Rules_GetConstructNameSymbol(currentGeneric);
          *((_WORD *)theMultifield + 3 * v18 + 7) = 1;
          v12 += 40;
          *(_DWORD *)((char *)theMultifield + 6 * v14 + 16) = Rules_AddIntegerValue(*(_DWORD *)(v12 + *(_DWORD *)(currentGeneric + 28) - 40));
          v9 = v15 + 1;
        }
        while ( v16 < *(_DWORD *)(currentGeneric + 32) );
      }
      result = (_DWORD *)Class_Enum(currentGeneric, g_DefgenericModuleItemIndex);
      currentGeneric = (int)result;
    }
    while ( result );
  }
  if ( firstGeneric )
    return (_DWORD *)Rules_SetConstructNextInModule(firstGeneric, savedNext);
  return result;
}
// 497EA3: variable 'v5' is possibly undefined
// 497F0A: variable 'v9' is possibly undefined
// 497F3C: variable 'v14' is possibly undefined
// 497F57: variable 'v15' is possibly undefined
// 497F5A: variable 'v16' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497FC0) --------------------------------------------------------
int * Defgeneric_GetMethodRestrictionsCommand(_DWORD *returnValue, int a2, double context)
{
  int theGeneric; // edi
  _DWORD argData[2]; // [esp-8h] [ebp-2Ch] BYREF
  int argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  if ( Lexer_ParseValueList(1, argData, 2, context)
    && (theGeneric = Defgeneric_CheckGenericExists((int)aGetMethodRestr, *(_BYTE **)(argValue + 16))) != 0
    && Lexer_ParseValueList(2, argData, 1, context)
    && Defgeneric_CheckMethodExists((int)aGetMethodRestr, theGeneric, *(_DWORD *)(argValue + 16)) != -1 )
  {
    return Defgeneric_BuildMethodRestrictionsValue(theGeneric, *(_DWORD *)(argValue + 16), returnValue);
  }
  else
  {
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
}

//----- (00498060) --------------------------------------------------------
int * Defgeneric_BuildMethodRestrictionsValue(int theGeneric, int methodIndex, _DWORD *returnValue)
{
  signed int methodPosition; // eax
  int v5; // ecx
  int methodAddr; // edx
  signed int fieldCount; // ecx
  signed int v8; // eax
  int v9; // edx
  _DWORD *theMultifield; // eax
  int v11; // ecx
  _DWORD *v12; // ebx
  int *result; // eax
  int v14; // edx
  signed int v15; // edx
  _DWORD *restriction; // edi
  int *v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  unsigned int v23; // esi
  int v24; // ecx
  char *v25; // ebx
  char *v26; // ebp
  char *v27; // eax
  int v28; // ecx
  int v29; // edx
  char *v30; // [esp+4h] [ebp-28h]
  int v31; // [esp+8h] [ebp-24h]
  int v32; // [esp+Ch] [ebp-20h]
  signed int restrictionIndex; // [esp+10h] [ebp-1Ch]
  signed int *theMethod; // [esp+14h] [ebp-18h]
  _DWORD *multifieldPtr; // [esp+18h] [ebp-14h]

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  methodAddr = 40 * methodPosition + *(_DWORD *)(v5 + 28);
  fieldCount = 3;
  theMethod = (signed int *)methodAddr;
  v8 = 0;
  if ( *(int *)(methodAddr + 8) > 0 )
  {
    v9 = *(_DWORD *)(methodAddr + 28);
    do
    {
      fieldCount += *(_DWORD *)(v9 + 8) + 3;
      ++v8;
      v9 += 12;
    }
    while ( v8 < theMethod[2] );
  }
  theMultifield = Rules_CreateEphemeralMultifield(fieldCount);
  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[2] = theMultifield;
  v12 = theMultifield;
  returnValue[4] = v11 - 1;
  multifieldPtr = theMultifield;
  *((_WORD *)theMultifield + 7) = 1;
  theMultifield[4] = Rules_AddIntegerValue(theMethod[3]);
  *((_WORD *)v12 + 10) = 1;
  *(_DWORD *)((char *)v12 + 22) = Rules_AddIntegerValue(theMethod[4]);
  *((_WORD *)v12 + 13) = 1;
  v12[7] = Rules_AddIntegerValue(theMethod[2]);
  restrictionIndex = 0;
  result = theMethod;
  v31 = 4;
  v15 = *(_DWORD *)(v14 + 8) + 4;
  if ( theMethod[2] > 0 )
  {
    v30 = (char *)v12 + 18;
    v32 = 0;
    do
    {
      restriction = (_DWORD *)(v32 + theMethod[7]);
      *((_WORD *)v30 + 7) = 1;
      v17 = Rules_AddIntegerValue(v15);
      *(_DWORD *)(v19 + 16) = v17;
      *((_WORD *)multifieldPtr + 3 * v18 + 4) = 2;
      v30 += 6;
      ++v31;
      if ( restriction[1] )
        v20 = g_ClipsTrueSymbol;
      else
        v20 = g_ClipsFalseSymbol;
      *(_DWORD *)((char *)multifieldPtr + 6 * v18 + 10) = v20;
      *((_WORD *)multifieldPtr + 3 * v18 + 7) = 1;
      result = Rules_AddIntegerValue(restriction[2]);
      *(_DWORD *)(v21 + 16) = result;
      v15 = v22 + 1;
      v23 = 0;
      if ( restriction[2] )
      {
        v24 = 0;
        v25 = (char *)multifieldPtr + 6 * v15 - 6;
        do
        {
          *((_WORD *)v25 + 7) = 2;
          v25 += 6;
          ++v23;
          v26 = (char *)multifieldPtr + 6 * v15 - 6;
          v27 = (char *)Rules_GetConstructNameString(*(_DWORD *)(v24 + *restriction));
          *((_DWORD *)v26 + 4) = Str_Intern(v27, v28);
          v15 = v29 + 1;
          result = (int *)restriction[2];
        }
        while ( v23 < (unsigned int)result );
      }
      v32 += 12;
      ++restrictionIndex;
    }
    while ( restrictionIndex < theMethod[2] );
  }
  return result;
}
// 498082: variable 'v5' is possibly undefined
// 4980D5: variable 'v11' is possibly undefined
// 498138: variable 'v14' is possibly undefined
// 498185: variable 'v19' is possibly undefined
// 498188: variable 'v18' is possibly undefined
// 4981E2: variable 'v21' is possibly undefined
// 4981E5: variable 'v22' is possibly undefined
// 49821D: variable 'v24' is possibly undefined
// 498229: variable 'v28' is possibly undefined
// 498231: variable 'v29' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (00498280) --------------------------------------------------------
int  Defgeneric_EvaluateGenericFunctionCall(int theGeneric, _DWORD *returnValue, double context)
{
  int v4; // eax

  Method_DispatchGenericCall(theGeneric, 0, *(_DWORD **)(g_ClipsCurrentExpression + 6), 0, context, returnValue);
  if ( returnValue[1] == 2 && (v4 = returnValue[2], v4 == g_ClipsFalseSymbol) )
    return g_ClipsFalseSymbol ^ v4;
  else
    return 1;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004982C0) --------------------------------------------------------
int  Defgeneric_DecrementGenericBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 20);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004982D0) --------------------------------------------------------
int  Defgeneric_IncrementGenericBusyCount(int result)
{
  ++*(_DWORD *)(result + 20);
  return result;
}

//----- (004982E0) --------------------------------------------------------
int  Defgeneric_SaveConstructs(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (004982F0) --------------------------------------------------------
signed int Defmethod_SaveConstructs()
{
  return Rules_DoForAllConstructs((void (*)(void))Defgeneric_WriteMethodPPForms, 0);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00498310) --------------------------------------------------------
signed int  Defgeneric_WriteMethodPPForms(signed int result, signed int logicalName)
{
  signed int theGeneric; // edi
  signed int logName; // ecx
  unsigned int methodIndex; // ebx
  int methodOffset; // esi
  char *ppForm; // edx
  int v7; // ecx

  theGeneric = result;
  logName = logicalName;
  methodIndex = 0;
  if ( *(_DWORD *)(result + 32) )
  {
    methodOffset = 0;
    do
    {
      result = methodOffset + *(_DWORD *)(theGeneric + 28);
      ppForm = *(char **)(result + 36);
      if ( ppForm )
      {
        Output_WriteLongString(logName, ppForm);
        result = Output_Write(v7, (int)asc_50537C, v7);
      }
      ++methodIndex;
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(theGeneric + 32) );
  }
  return result;
}
// 498343: variable 'v3' is possibly undefined
// 49834F: variable 'v7' is possibly undefined

//----- (00498360) --------------------------------------------------------
signed int  Defgeneric_DeleteMethod(int theGeneric, int methodIndex)
{
  int methodAddr; // edx
  int methodCount; // edx
  unsigned int copyIndex; // ebx
  char *newMethodArray; // eax
  int v6; // edx
  char *destPtr; // ebp
  signed int result; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  signed int newArrayAddr; // [esp+0h] [ebp-14h]

  methodAddr = 40 * methodIndex + *(_DWORD *)(theGeneric + 28);
  if ( (*(_BYTE *)(methodAddr + 24) & 1) != 0 )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)aGenrccom, v9, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRemoveIm, v10);
    v11 = Rules_GetConstructNameString(theGeneric);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v11, v12);
    return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__15, v13);
  }
  else
  {
    Defgeneric_DeleteMethodInfo(theGeneric, methodAddr);
    methodCount = *(_DWORD *)(theGeneric + 32);
    if ( methodCount == 1 )
    {
      Mem_SmallBlockFree(*(_DWORD **)(theGeneric + 28), 40);
      result = theGeneric;
      *(_DWORD *)(theGeneric + 32) = 0;
      *(_DWORD *)(theGeneric + 28) = 0;
    }
    else
    {
      *(_DWORD *)(theGeneric + 32) = methodCount - 1;
      copyIndex = 0;
      newMethodArray = (char *)Mem_SmallBlockAlloc(40 * (methodCount - 1));
      newArrayAddr = (signed int)newMethodArray;
      if ( *(_DWORD *)(theGeneric + 32) )
      {
        destPtr = newMethodArray;
        do
        {
          if ( copyIndex == methodIndex )
            ++v6;
          qmemcpy(destPtr, (const void *)(40 * v6 + *(_DWORD *)(theGeneric + 28)), 0x28u);
          ++copyIndex;
          destPtr += 40;
          ++v6;
        }
        while ( copyIndex < *(_DWORD *)(theGeneric + 32) );
      }
      Mem_SmallBlockFree(*(_DWORD **)(theGeneric + 28), 40 * (*(_DWORD *)(theGeneric + 32) + 1));
      result = newArrayAddr;
      *(_DWORD *)(theGeneric + 28) = newArrayAddr;
    }
  }
  return result;
}
// 4983E4: variable 'v6' is possibly undefined
// 498466: variable 'v9' is possibly undefined
// 498475: variable 'v10' is possibly undefined
// 49848D: variable 'v12' is possibly undefined
// 49849C: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004984D0) --------------------------------------------------------
int __fastcall Defgeneric_PrintMethodsList(int logicalName, int theGeneric)
{
  unsigned int methodIndex; // ebp
  int methodOffset; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char signatureBuffer[276]; // [esp+0h] [ebp-114h] BYREF

  methodIndex = 0;
  if ( *(_DWORD *)(theGeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      v5 = Rules_GetConstructNameString(theGeneric);
      Output_Write(v6, v5, v6);
      Output_Write(v7, (int)asc_505344, v7);
      Defgeneric_AppendMethodSignatureText(signatureBuffer, 255, v8, methodOffset + *(_DWORD *)(theGeneric + 28));
      Output_Write(v9, (int)signatureBuffer, v9);
      ++methodIndex;
      Output_Write(v10, (int)asc_50537C, v10);
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(theGeneric + 32) );
  }
  return *(_DWORD *)(theGeneric + 32);
}
// 4984F5: variable 'v6' is possibly undefined
// 498501: variable 'v7' is possibly undefined
// 498512: variable 'v8' is possibly undefined
// 49851B: variable 'v9' is possibly undefined
// 498528: variable 'v10' is possibly undefined

//----- (00498550) --------------------------------------------------------
signed int  Defgeneric_WatchAccessFunction(int newState, int argExprs, double context)
{
  return Rules_ApplyWatchFlagCommand(g_Clips_DefgenericConstructType, newState, (int)Defgeneric_GetTraceFlag, argExprs, context, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498570) --------------------------------------------------------
signed int  Defgeneric_WatchPrintFunction(int logicalName, int argExprs, double context)
{
  return Rules_ListWatchFlagStatus(g_Clips_DefgenericConstructType, logicalName, (int)Defgeneric_GetTraceFlag, argExprs, context, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498590) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchAccessFunction(int newState, int argExprs, double context)
{
  if ( newState )
    return Defgeneric_WatchMethodsDispatch((int)aWatch_1, 0, 0, newState, 0, context, (void (*)(void))Defgeneric_SetMethodTraceFlag, argExprs);
  else
    return Defgeneric_WatchMethodsDispatch((int)aUnwatch_0, 0, 0, 0, 0, context, (void (*)(void))Defgeneric_SetMethodTraceFlag, argExprs);
}

//----- (004985C0) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchPrintFunction(int logicalName, int argExprs, int a3, double context)
{
  return Defgeneric_WatchMethodsDispatch((int)aListWatchIte_1, logicalName, (void (*)(void))Method_PrintWatchStatusLine, -1, a3, context, 0, argExprs);
}

//----- (004985E0) --------------------------------------------------------
signed int  Defgeneric_WatchMethodsDispatch(
        int funcName,
        int logicalName,
        void (*printFunc)(void),
        int newState,
        int i,
        double context,
        void (*traceFunc)(void),
        int argExprs)
{
  int v9; // ecx
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int k; // esi
  int m; // ecx
  int v16; // ecx
  int theGeneric; // ecx
  int nextExpr; // ebx
  int v19; // ecx
  int v20; // ecx
  _DWORD indexArgData[2]; // [esp+0h] [ebp-50h] BYREF
  int indexArgValue; // [esp+8h] [ebp-48h]
  _DWORD argData[8]; // [esp+18h] [ebp-38h] BYREF
  int j; // [esp+38h] [ebp-18h]
  int argIndex; // [esp+3Ch] [ebp-14h]
  void (*savedPrintFunc)(void); // [esp+40h] [ebp-10h]

  argData[7] = funcName;
  argData[6] = newState;
  savedPrintFunc = printFunc;
  v9 = argExprs;
  argIndex = 2;
  if ( argExprs )
  {
    while ( 1 )
    {
      if ( !argExprs )
        return 1;
      if ( Parser_ParseForm((__int16 *)argExprs, argData, v9, context) )
        return 0;
      if ( argData[1] != 2 || (theGeneric = Symbol_LookupInModule((char **)g_Clips_DefgenericConstructType, *(_BYTE **)(argData[2] + 16), 1)) == 0 )
      {
        Parser_ReportError(argIndex, (int)aGenericFunct_4);
        return 0;
      }
      nextExpr = *(_DWORD *)(argExprs + 10);
      if ( !nextExpr )
        goto LABEL_20;
      ++argIndex;
      argExprs = nextExpr;
      if ( Parser_ParseForm((__int16 *)nextExpr, indexArgData, theGeneric, context) )
        return 0;
      if ( indexArgData[1] != 1 || *(int *)(indexArgValue + 16) <= 0 || Method_FindByIndex(v20, i) == -1 )
      {
        Parser_ReportError(argIndex, (int)aMethodIndex);
        return 0;
      }
      i = *(_DWORD *)(indexArgValue + 16);
      if ( i )
      {
        if ( traceFunc )
          ((void (__fastcall *)(int, int))traceFunc)(theGeneric, theGeneric);
        else
          ((void (__fastcall *)(int, int))savedPrintFunc)(theGeneric, theGeneric);
        argExprs = *(_DWORD *)(nextExpr + 10);
        ++argIndex;
      }
      else
      {
LABEL_20:
        for ( i = Class_NextMethod(theGeneric, 0); i; i = Class_NextMethod(v19, i) )
        {
          if ( traceFunc )
            ((void (__fastcall *)(int, int))traceFunc)(v9, v9);
          else
            ((void (__fastcall *)(int, int))savedPrintFunc)(v9, v9);
        }
        argExprs = *(_DWORD *)(argExprs + 10);
        ++argIndex;
      }
    }
  }
  Module_BeginEnum();
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    if ( !traceFunc )
    {
      Name = Module_GetName(j);
      Output_Write(logicalName, Name, v12);
      Output_Write(logicalName, (int)asc_5053F0, v13);
    }
    for ( k = Class_Enum(0, g_DefgenericModuleItemIndex); k; k = Class_Enum(k, g_DefgenericModuleItemIndex) )
    {
      for ( m = Class_NextMethod(k, 0); m; m = Class_NextMethod(k, v16) )
      {
        if ( traceFunc )
        {
          traceFunc();
        }
        else
        {
          Output_Write(logicalName, (int)asc_5053F4, m);
          savedPrintFunc();
        }
      }
    }
  }
  Module_EndEnum();
  return 1;
}
// 498655: variable 'v12' is possibly undefined
// 498661: variable 'v13' is possibly undefined
// 49869A: variable 'v16' is possibly undefined
// 4986FE: variable 'v9' is possibly undefined
// 498749: variable 'v17' is possibly undefined
// 49876A: variable 'v19' is possibly undefined
// 4987E0: variable 'v20' is possibly undefined
// 54E6A0: using guessed type int dword_54E6A0;
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00498870) --------------------------------------------------------
signed int  Method_PrintWatchStatusLine(int logicalName, int theGeneric, int methodIndex)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char signatureBuffer[76]; // [esp+0h] [ebp-4Ch] BYREF

  v5 = Rules_GetConstructNameString(theGeneric);
  Output_Write(logicalName, v5, methodIndex);
  Output_Write(logicalName, (int)asc_505420, v6);
  Defgeneric_FormatMethodRestrictionsString(signatureBuffer, 59, v7, theGeneric);
  Output_Write(logicalName, (int)signatureBuffer, v8);
  if ( Defgeneric_GetMethodTraceFlag(theGeneric, methodIndex) )
    return Output_Write(logicalName, (int)aOn_3, v9);
  else
    return Output_Write(logicalName, (int)aOff_3, v9);
}
// 498898: variable 'v6' is possibly undefined
// 4988A4: variable 'v7' is possibly undefined
// 4988AD: variable 'v8' is possibly undefined
// 4988C6: variable 'v9' is possibly undefined

//----- (004988F0) --------------------------------------------------------
int Deffunction_InitConstructType()
{
  int v0; // ecx

  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_Deffunction, 12);
  g_Clips_DeffunctionModuleItemIndex = Module_RegisterItem(
                   (int)aDeffunction,
                   (int)Deffunction_AllocateModule,
                   (int)Deffunction_RecordAtIndex,
                   (int)Deffunction_FreeModule,
                   (int)Deffunction_WriteModuleItemReference,
                   (int)Deffunction_FindByName);
  g_ClipsDeffunctionConstructType = (int)Rules_RegisterConstructType(
                        (int)aDeffunction,
                        (int)aDeffunctions,
                        (int)Deffunction_FindByName,
                        (int)Deffunction_ParseConstruct,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Deffunction_EnumNext,
                        (int)Rules_SetConstructNextInModule,
                        (int)Deffunction_IsDeletable,
                        (int)Deffunction_Delete,
                        (int)Deffunction_Free);
  Rules_AddClearReadyFunction((int)aDeffunction, (int)Deffunction_IsClearReady, 0);
  Module_RegisterImportExportConstructType((int)aDeffunction, 2);
  Rules_AddSaveFunction((int)aDeffunctionHea, (int)Deffunction_SaveHeaders, 1000);
  Rules_AddSaveFunction((int)aDeffunctions, (int)Deffunction_SaveBodies, 0);
  Rules_RegisterHostFunction(aUndeffunction, 118, v0, (int)Deffunction_UndeffunctionCommand, (int)a11w_3);
  Rules_RegisterHostFunction(aListDeffunctio, 118, (int)aListdeffunctio, (int)Deffunction_ListCommand, (int)a01_0);
  Rules_RegisterHostFunction(aPpdeffunction, 118, (int)aPpdeffunctionc, (int)Deffunction_PPCommand, (int)a11w_3);
  Rules_RegisterHostFunction(aGetDeffunction, 109, (int)aGetdeffunction, (int)Deffunction_GetListCommand, (int)a01_0);
  Rules_RegisterHostFunction(aDeffunctionMod, 119, (int)aGetdeffuncti_0, (int)Deffunction_ModuleCommand, (int)a11w_3);
  Deffunction_RegisterBinaryItem();
  Deffunction_RegisterCodeGenerator();
  return Rules_AddWatchItem((int)aDeffunctions, 0, 32, (int)&g_Rules_WatchDeffunctions, (int)Deffunction_SetWatchAll, (int)Deffunction_GetWatchAll);
}
// 4989CE: variable 'v0' is possibly undefined
// 51AAE8: using guessed type int dword_51AAE8;
// 54E6A8: using guessed type int dword_54E6A8;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498A80) --------------------------------------------------------
int  Deffunction_FindByName(_BYTE *deffunctionName, int a2)
{
  return Rules_FindConstructByNameGeneric(deffunctionName, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498AB0) --------------------------------------------------------
int  Deffunction_LookupByName(_BYTE *deffunctionName)
{
  return Symbol_LookupInModule((char **)g_ClipsDeffunctionConstructType, deffunctionName, 0);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498AD0) --------------------------------------------------------
signed int Deffunction_Delete()
{
  int v0; // edx
  signed int result; // eax
  int v2; // edx

  if ( Rules_IsBloaded() == 1 )
    return 0;
  if ( !v0 )
    return Deffunction_ClearAll();
  result = Deffunction_IsDeletable();
  if ( result )
  {
    Rules_UnlinkListNode(v2);
    Deffunction_Free(v2);
    return 1;
  }
  return result;
}
// 498ADF: variable 'v0' is possibly undefined
// 498AFB: variable 'v2' is possibly undefined

//----- (00498B10) --------------------------------------------------------
int  Deffunction_EnumNext(int deffunctionPtr)
{
  return Class_Enum(deffunctionPtr, g_Clips_DeffunctionModuleItemIndex);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498B20) --------------------------------------------------------
BOOL Deffunction_IsDeletable()
{
  int v0; // edx

  return !Rules_IsBloaded() && !*(_DWORD *)(v0 + 20) && !*(_DWORD *)(v0 + 24);
}
// 498B2C: variable 'v0' is possibly undefined

//----- (00498B50) --------------------------------------------------------
int  Deffunction_Free(int result)
{
  int v1; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  signed int v6; // ecx
  _DWORD *v7; // ecx

  if ( result )
  {
    v1 = Rules_GetConstructNameSymbol(result);
    Rules_DecrementSymbolCount(v1, v2);
    AST_DeinstallNodeChain(*(__int16 **)(v3 + 30));
    AST_FreePackedNodeChain(*(_DWORD *)(v4 + 30));
    Rules_ReplaceConstructPPForm(v6, v5);
    g_ClipsMemFreeListTemp = (int)v7;
    *v7 = *(_DWORD *)(g_ClipsMemoryTable + 184);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 184) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 498B5F: variable 'v2' is possibly undefined
// 498B64: variable 'v3' is possibly undefined
// 498B6C: variable 'v4' is possibly undefined
// 498B78: variable 'v6' is possibly undefined
// 498B78: variable 'v5' is possibly undefined
// 498B82: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00498BB0) --------------------------------------------------------
int __thiscall Deffunction_UndeffunctionCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BD0) --------------------------------------------------------
int __thiscall Deffunction_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BF0) --------------------------------------------------------
int __thiscall Deffunction_PPCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C10) --------------------------------------------------------
int  Deffunction_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDeffunctionConstructType, a1, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C50) --------------------------------------------------------
_DWORD * Deffunction_GetListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_ClipsDeffunctionConstructType, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C90) --------------------------------------------------------
int  Deffunction_CheckArgumentCount(int result, int argCount)
{
  int minArgs; // ecx
  int expectedArgs; // ebx
  int deffunctionName; // eax

  if ( result )
  {
    minArgs = *(_DWORD *)(result + 34);
    if ( argCount >= minArgs )
    {
      if ( argCount <= minArgs || *(_DWORD *)(result + 38) == -1 )
        return 1;
    }
    else if ( *(_DWORD *)(result + 38) == -1 )
    {
      expectedArgs = *(_DWORD *)(result + 34);
LABEL_5:
      deffunctionName = Rules_GetConstructNameString(result);
      Rules_ExpectedCountError(deffunctionName, expectedArgs);
      return 0;
    }
    expectedArgs = *(_DWORD *)(result + 34);
    goto LABEL_5;
  }
  return result;
}

//----- (00498CE0) --------------------------------------------------------
int  Deffunction_CallForBooleanResult(int theDeffunction, _DWORD *returnValue, double context)
{
  int v3; // ecx
  int resultValue; // eax

  Deffunction_CallDeffunction(theDeffunction, *(_DWORD **)(g_ClipsCurrentExpression + 6), returnValue, context);
  if ( *(_DWORD *)(v3 + 4) == 2 && (resultValue = *(_DWORD *)(v3 + 8), resultValue == g_ClipsFalseSymbol) )
    return g_ClipsFalseSymbol ^ resultValue;
  else
    return 1;
}
// 498CF4: variable 'v3' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (00498D20) --------------------------------------------------------
int  Deffunction_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 20);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (00498D30) --------------------------------------------------------
int  Deffunction_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(result + 20);
  return result;
}

//----- (00498D40) --------------------------------------------------------
signed int Deffunction_AllocateModule()
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00498D70) --------------------------------------------------------
int  Deffunction_FreeModule(int theModuleItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theModuleItem, g_ClipsDeffunctionConstructType, theModuleItem);
  freed_node = (_DWORD *)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498DB0) --------------------------------------------------------
BOOL Deffunction_IsClearReady()
{
  return g_CurrentDeffunction == 0;
}
// 51B3E8: using guessed type int dword_51B3E8;

//----- (00498DC0) --------------------------------------------------------
signed int Deffunction_ClearAll()
{
  int clearSuccess; // ebx
  int i; // ecx
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int theDeffunction; // esi
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  signed int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // edx
  int v17; // ecx

  clearSuccess = 1;
  if ( Rules_IsBloaded() == 1 )
    return 0;
  for ( i = Class_Enum(0, g_Clips_DeffunctionModuleItemIndex); i; i = Class_Enum(v5, g_Clips_DeffunctionModuleItemIndex) )
  {
    if ( *(_DWORD *)(i + 24) )
    {
      v3 = Rules_GetConstructNameString(i);
      Deffunction_ReportCantDelete(v3, v4);
      clearSuccess = 0;
    }
    else
    {
      AST_DeinstallNodeChain(*(__int16 **)(i + 30));
      v15 = *(_DWORD *)(v14 + 30);
      *(_DWORD *)(v14 + 20) = v16;
      AST_FreePackedNodeChain(v15);
      *(_DWORD *)(v5 + 30) = 0;
    }
  }
  theDeffunction = Class_Enum(0, g_Clips_DeffunctionModuleItemIndex);
  if ( !theDeffunction )
    return clearSuccess;
  do
  {
    while ( 1 )
    {
      theDeffunction = Class_Enum(theDeffunction, g_Clips_DeffunctionModuleItemIndex);
      if ( !*(_DWORD *)(v7 + 24) )
        break;
LABEL_11:
      if ( !theDeffunction )
        return clearSuccess;
    }
    if ( *(_DWORD *)(v7 + 20) )
    {
      Rules_PrintWarningID((int)aDffnxfun, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aDeffunction_6, v8);
      v10 = Rules_GetConstructNameString(v9);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], v10, v11);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aOnlyPartiallyD, v12);
      clearSuccess = 0;
      Rules_ReplaceConstructPPForm(v13, 0);
      goto LABEL_11;
    }
    Rules_UnlinkListNode(v7);
    Deffunction_Free(v17);
  }
  while ( theDeffunction );
  return clearSuccess;
}
// 498DFB: variable 'v4' is possibly undefined
// 498E0A: variable 'v5' is possibly undefined
// 498E3B: variable 'v7' is possibly undefined
// 498E69: variable 'v8' is possibly undefined
// 498E70: variable 'v9' is possibly undefined
// 498E7F: variable 'v11' is possibly undefined
// 498E8E: variable 'v12' is possibly undefined
// 498E99: variable 'v13' is possibly undefined
// 498EB5: variable 'v14' is possibly undefined
// 498EB8: variable 'v16' is possibly undefined
// 498ED5: variable 'v17' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498EF0) --------------------------------------------------------
signed int  Deffunction_ReportCantDelete(int deffunctionName, int a2)
{
  return Rules_ReportCantDeleteItem(a2, deffunctionName);
}

//----- (00498F00) --------------------------------------------------------
signed int Deffunction_SaveHeaders()
{
  return Rules_DoForAllConstructs((void (*)(void))Deffunction_WriteHeaderForm, 0);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498F20) --------------------------------------------------------
int  Deffunction_WriteHeaderForm(int theDeffunction, int logicalName)
{
  int result; // eax
  int v6; // ecx
  int nameString; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int i; // ebx
  int v12; // ecx

  result = Rules_GetModuleConstructListHead(theDeffunction);
  if ( result )
  {
    Output_Write(logicalName, (int)aDeffunction_1, v6);
    nameString = Rules_GetConstructNameString(theDeffunction);
    Output_Write(logicalName, nameString, v8);
    Output_Write(logicalName, (int)asc_5055B4, v9);
    for ( i = 0; i < *(_DWORD *)(theDeffunction + 34); ++i )
    {
      Output_Write(v10, (int)aQuestionP_DeffunctionArgumentPrefix, v10);
      Rules_PrintLongInteger(v12, i);
      if ( i != *(_DWORD *)(theDeffunction + 34) - 1 )
        Output_Write(v10, (int)asc_5055BC, v10);
    }
    if ( *(_DWORD *)(theDeffunction + 38) == -1 )
    {
      if ( *(_DWORD *)(theDeffunction + 34) )
        Output_Write(v10, (int)asc_5055BC, v10);
      return Output_Write(v10, (int)a_wildargs, v10);
    }
    else
    {
      return Output_Write(v10, (int)asc_5055D0, v10);
    }
  }
  return result;
}
// 498F41: variable 'v6' is possibly undefined
// 498F51: variable 'v8' is possibly undefined
// 498F5D: variable 'v9' is possibly undefined
// 498F72: variable 'v10' is possibly undefined
// 498F7B: variable 'v12' is possibly undefined

//----- (00498FE0) --------------------------------------------------------
int  Deffunction_SaveBodies(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498FF0) --------------------------------------------------------
signed int  Deffunction_SetWatchAll(int newState, int argExprs, double context)
{
  return Rules_ApplyWatchFlagCommand(g_ClipsDeffunctionConstructType, newState, (int)Deffunction_GetWatchFlagField, argExprs, context, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499010) --------------------------------------------------------
signed int  Deffunction_GetWatchAll(int logicalName, int argExprs, double context)
{
  return Rules_ListWatchFlagStatus(g_ClipsDeffunctionConstructType, logicalName, (int)Deffunction_GetWatchFlagField, argExprs, context, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499030) --------------------------------------------------------
__int16  Deffunction_SetWatchFlagField(__int16 result, int theDeffunction)
{
  *(_WORD *)(theDeffunction + 28) = result;
  return result;
}

//----- (00499040) --------------------------------------------------------
int  Deffunction_GetWatchFlagField(int theDeffunction)
{
  return *(unsigned __int16 *)(theDeffunction + 28);
}

//----- (00499050) --------------------------------------------------------
_DWORD *Defglobal_InitConstructType()
{
  _DWORD *result; // eax

  g_CLIPS_DefglobalEvalNodeDescriptor[4] = (int)(uintptr_t)Defglobal_EvaluateReference;
  g_Defglobal_PtrEntityRecord[4] = (int)(uintptr_t)Mem_CopyDataObjectRecord;
  g_Defglobal_PtrEntityRecord[6] = (int)(uintptr_t)Class_DecrementBusyCount;
  g_Defglobal_PtrEntityRecord[7] = (int)(uintptr_t)Class_IncrementBusyCount;
  Rules_RegisterEvaluationHandler((int)&g_CLIPS_DefglobalEvalNodeDescriptor, 13);
  Rules_RegisterEvaluationHandler((int)&g_Defglobal_PtrEntityRecord, 60);
  Defglobal_RegisterModuleItem();
  Defglobal_RegisterConstructCommands();
  Defglobal_RegisterResetGlobalsCommands();
  result = Rules_RegisterConstructType(
             (int)aDefglobal,
             (int)aDefglobals,
             (int)Defglobal_FindByName,
             (int)Defglobal_ParseDefglobalConstruct,
             (int)Rules_GetConstructNameSymbol,
             (int)Rules_GetModuleConstructListHead,
             (int)Rules_GetConstructOwnerModule,
             (int)Defglobal_EnumNext,
             (int)Rules_SetConstructNextInModule,
             (int)Defglobal_IsDeletable,
             (int)Defglobal_DeleteConstructOrAll,
             (int)Defglobal_Free);
  g_ClipsDefglobalConstructType = (int)result;
  return result;
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004990D0) --------------------------------------------------------
int *Defglobal_RegisterModuleItem()
{
  g_ClipsDefglobalModuleItemId = Module_RegisterItem(
                   (int)aDefglobal,
                   (int)Defglobal_AllocateModule,
                   (int)Rules_GetDefglobalModulePointer,
                   (int)Defglobal_FreeModule,
                   (int)Defglobal_WriteModuleItemHeaderReference,
                   (int)Defglobal_FindByName);
  return Module_RegisterImportExportConstructType((int)aDefglobal, 2);
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (00499110) --------------------------------------------------------
signed int Defglobal_AllocateModule()
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499140) --------------------------------------------------------
int  Defglobal_FreeModule(int theModuleItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theModuleItem, g_ClipsDefglobalConstructType, theModuleItem);
  freed_node = (_DWORD *)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B4: using guessed type int dword_54E6B4;

//----- (00499190) --------------------------------------------------------
int  Defglobal_FindByName(_BYTE *defglobalName, int a2)
{
  return Rules_FindConstructByNameGeneric(defglobalName, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004991A0) --------------------------------------------------------
int  Defglobal_EnumNext(int defglobalPtr)
{
  return Class_Enum(defglobalPtr, g_ClipsDefglobalModuleItemId);
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004991B0) --------------------------------------------------------
BOOL Defglobal_IsDeletable()
{
  int v0; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(v0 + 24) == 0;
}
// 4991BC: variable 'v0' is possibly undefined

//----- (004991D0) --------------------------------------------------------
int  Defglobal_Free(int result)
{
  int v1; // edx
  int v2; // ecx
  int *v3; // ecx
  _DWORD *v4; // ecx

  if ( result )
  {
    Rules_ValueDeinstall(result + 28, result);
    if ( *(_DWORD *)(v1 + 32) == 4 )
      Rules_ReturnMultifieldToPool(*(_DWORD **)(v1 + 36));
    AST_RemoveHashedNodeChain(*(__int16 **)(v2 + 52), v2);
    Rules_FreeConstructHeaderString(v3, (int)v3);
    g_ClipsMemFreeListTemp = (int)v4;
    *v4 = *(_DWORD *)(g_ClipsMemoryTable + 224);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 224) = g_ClipsMemFreeListTemp;
    g_Defglobal_ChangedFlag = 1;
  }
  return result;
}
// 4991E5: variable 'v1' is possibly undefined
// 4991F4: variable 'v2' is possibly undefined
// 4991FE: variable 'v3' is possibly undefined
// 499208: variable 'v4' is possibly undefined
// 51AB1C: using guessed type int dword_51AB1C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499240) --------------------------------------------------------
int  Defglobal_SetValue(int theGlobal, _DWORD *vPtr, int resetVar, double context)
{
  int record; // ecx
  int new_type; // eax
  int result; // eax

  record = theGlobal;
  if ( resetVar )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(theGlobal + 52), vPtr, theGlobal, context);
    if ( g_ClipsEvaluationError )
    {
      vPtr[1] = 2;
      vPtr[2] = g_ClipsFalseSymbol;
    }
  }
  if ( (*(_BYTE *)(record + 20) & 1) != 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aDefglobalWatchPrefix, record);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)record + 16), record);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_5055F8, record);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WTrace[0], (int)vPtr);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_505600, record);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WTrace[0], record + 28);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_505608, record);
  }
  Rules_ValueDeinstall(record + 28, record);
  if ( *(_DWORD *)(record + 32) == 4 )
    Rules_ReturnMultifieldToPool((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(record + 36));
  new_type = vPtr[1];
  *(_DWORD *)(record + 32) = new_type;
  if ( new_type == 4 )
    Rules_AssignMultifieldRangeCopy((_DWORD *)(record + 28), (int)vPtr);
  else
    *(_DWORD *)(record + 36) = vPtr[2];
  Rules_ValueInstall(record + 28, record);
  result = g_ClipsCurrentEvaluationDepth;
  g_Defglobal_ChangedFlag = 1;
  if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
    return Rules_RunPeriodicCleanup(1, 0);
  return result;
}
// 51A618: using guessed type char *off_51A618[4];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AB1C: using guessed type int dword_51AB1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (00499360) --------------------------------------------------------
_DWORD *Defglobal_FindNextChanged()
{
  _DWORD *result; // eax
  int v1; // ecx

  result = (_DWORD *)Class_Enum(0, g_ClipsDefglobalModuleItemId);
  if ( !result )
    return 0;
  while ( v1 != *result )
  {
    result = (_DWORD *)Class_Enum((int)result, g_ClipsDefglobalModuleItemId);
    if ( !result )
      return 0;
  }
  return result;
}
// 499377: variable 'v1' is possibly undefined
// 54E6B0: using guessed type int dword_54E6B0;

//----- (00499410) --------------------------------------------------------
signed int  Defglobal_EvaluateReference(int theValue, _DWORD *returnValue, int a3)
{
  _DWORD *theGlobal; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD countBuf[5]; // [esp+0h] [ebp-14h] BYREF

  countBuf[3] = a3;
  theGlobal = (_DWORD *)Rules_FindImportExportConstruct(aDefglobal, countBuf, *(_BYTE **)(theValue + 16), 1, 0);
  if ( !theGlobal )
  {
    Rules_PrintErrorID((int)aGlobldef, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGlobalVariab_0, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theValue + 16), v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUnbound_, v9);
    goto LABEL_4;
  }
  if ( countBuf[0] > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)aDefglobal, *(_DWORD *)(theValue + 16));
LABEL_4:
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    Lexer_ErrorRecover(1);
    return 0;
  }
  Mem_CopyDataObjectRecord(theGlobal, returnValue);
  return 1;
}
// 499487: variable 'v7' is possibly undefined
// 499494: variable 'v8' is possibly undefined
// 4994A3: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (004994C0) --------------------------------------------------------
signed int  Mem_CopyDataObjectRecord(_DWORD *src, _DWORD *dst)
{
  int fieldCount; // eax
  int v3; // ebx
  _DWORD *newMultifield; // eax
  int v6; // edx
  int copyLength; // ebx
  int v8; // ecx

  dst[1] = src[8];
  dst[2] = src[9];
  dst[3] = src[10];
  fieldCount = src[11];
  v3 = dst[1];
  dst[4] = fieldCount;
  if ( v3 == 4 )
  {
    newMultifield = Rules_CreateEphemeralMultifield(fieldCount + 1);
    copyLength = *(_DWORD *)(v6 + 16) + 1;
    *(_DWORD *)(v6 + 8) = newMultifield;
    qmemcpy(
      (void *)(*(_DWORD *)(v6 + 8) + 14),
      (const void *)(6 * *(_DWORD *)(v8 + 40) + *(_DWORD *)(v8 + 36) + 14),
      6 * copyLength);
  }
  return 1;
}
// 4994F4: variable 'v6' is possibly undefined
// 499507: variable 'v8' is possibly undefined

//----- (00499590) --------------------------------------------------------
int  Class_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 24);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004995A0) --------------------------------------------------------
int  Class_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(result + 24);
  return result;
}

//----- (004995B0) --------------------------------------------------------
int Class_RefreshWatchFlags()
{
  int result; // eax
  int i; // edi
  _BYTE *j; // esi
  _DWORD countBuf[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    for ( j = *(_BYTE **)(Module_GetItem(i, g_ClipsDefglobalModuleItemId) + 4); j; j = (_BYTE *)Class_Enum((int)j, g_ClipsDefglobalModuleItemId) )
    {
      if ( Rules_FindImportExportConstruct(aDefglobal, countBuf, *(_BYTE **)(*(_DWORD *)j + 16), 1, 0) )
        j[20] |= 2u;
      else
        j[20] &= ~2u;
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004996D0) --------------------------------------------------------
signed int __thiscall Rules_InitObjectSystem(void *this)
{
  (void)this;
  g_Symbol_IsA = (int)Str_Intern(aIsA, 0);
  ++*(_DWORD *)(g_Symbol_IsA + 4);
  g_Clips_NameSymbol = (int)Str_Intern(aName, 0);
  ++*(_DWORD *)(g_Clips_NameSymbol + 4);
  g_Rules_InitialObjectSymbol = (int)Str_Intern(aInitialObject, 0);
  ++*(_DWORD *)(g_Rules_InitialObjectSymbol + 4);
  Rules_RegisterDefclassConstruct();
  Rules_RegisterInstanceFunctions();
  MessageHandler_RegisterCommands();
  Definstances_SetupConstruct();
  InstanceQuery_SetupFunctions(0);
  Class_RegisterBinaryItem();
  ObjectsCompiler_RegisterCodeGenerator();
  return Rules_RegisterObjectPatternType(0);
}
// 54E6F4: using guessed type int dword_54E6F4;
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (00499730) --------------------------------------------------------
int Class_CreateSystemClasses()
{
  int primitive_class; // ecx
  int number_class; // ebp
  int lexeme_class; // [esp+8h] [ebp-20h]
  int address_class; // esi
  int instance_class; // [esp+4h] [ebp-24h]
  int user_class; // [esp+0h] [ebp-28h]
  int initial_object_class; // edi
  char initial_object_flags; // ah
  int result; // eax
  int object_class; // [esp+Ch] [ebp-1Ch]

  Class_InternSlotName((_DWORD *)g_Symbol_IsA, 0, 1);
  Class_InternSlotName((_DWORD *)g_Clips_NameSymbol, 1, 1);
  object_class = Class_CreateSystemClass(aObject_0, 0, 0);
  primitive_class = Class_CreateSystemClass(aPrimitive, object_class, 0);
  user_class = Class_CreateSystemClass(aUser, object_class, 0);
  number_class = Class_CreateSystemClass(aNumber_1, primitive_class, 0);
  g_ClipsIntegerClass = Class_CreateSystemClass(aInteger_2, number_class, 0);
  g_ClipsPrimitiveTypeClassMap[0] = Class_CreateSystemClass(aFloat_2, number_class, 0);
  lexeme_class = Class_CreateSystemClass(aLexeme_0, primitive_class, 0);
  g_ClipsSymbolClass = Class_CreateSystemClass(aSymbol_3, lexeme_class, 0);
  g_ClipsStringClass = Class_CreateSystemClass(aString_2, lexeme_class, 0);
  g_ClipsMultifieldClass = Class_CreateSystemClass(aMultifield_1, primitive_class, 0);
  address_class = Class_CreateSystemClass(aAddress_0, primitive_class, 0);
  g_ClipsExternalAddressClass = Class_CreateSystemClass(aExternalAddr_0, address_class, 0);
  g_ClipsFactAddressClass = Class_CreateSystemClass(aFactAddress_1, address_class, 0);
  instance_class = Class_CreateSystemClass(aInstance_3, primitive_class, 0);
  g_Class_InstanceAddress = Class_CreateSystemClass(aInstanceAddr_7, instance_class, 0);
  g_Class_InstanceName = Class_CreateSystemClass(aInstanceName_2, instance_class, 0);
  initial_object_class = Class_CreateSystemClass(aInitialObjec_0, user_class, 0);
  initial_object_flags = *(_BYTE *)(initial_object_class + 20) & 0xFB;
  *(_BYTE *)(initial_object_class + 20) = initial_object_flags;
  *(_BYTE *)(initial_object_class + 20) = initial_object_flags | 8;
  Class_InsertLinkEntry((unsigned __int16 *)(g_Class_InstanceAddress + 34), address_class, -1);
  Class_InsertLinkEntry((unsigned __int16 *)(g_Class_InstanceAddress + 46), address_class, 2);
  Class_InsertLinkEntry((unsigned __int16 *)(address_class + 40), g_Class_InstanceAddress, -1);
  Rules_AppendConstructToModuleList(g_ClipsPrimitiveTypeClassMap[0]);
  Rules_AppendConstructToModuleList(g_ClipsIntegerClass);
  Rules_AppendConstructToModuleList(g_ClipsSymbolClass);
  Rules_AppendConstructToModuleList(g_ClipsStringClass);
  Rules_AppendConstructToModuleList(g_ClipsMultifieldClass);
  Rules_AppendConstructToModuleList(g_ClipsExternalAddressClass);
  Rules_AppendConstructToModuleList(g_ClipsFactAddressClass);
  Rules_AppendConstructToModuleList(g_Class_InstanceAddress);
  Rules_AppendConstructToModuleList(g_Class_InstanceName);
  Rules_AppendConstructToModuleList(object_class);
  Rules_AppendConstructToModuleList(primitive_class);
  Rules_AppendConstructToModuleList(number_class);
  Rules_AppendConstructToModuleList(lexeme_class);
  Rules_AppendConstructToModuleList(address_class);
  Rules_AppendConstructToModuleList(instance_class);
  Rules_AppendConstructToModuleList(user_class);
  Rules_AppendConstructToModuleList(initial_object_class);
  result = Class_GetNextRecord(0);
  while ( result )
  {
    Class_AssignID(result);
    result = Class_GetNextRecord(result);
  }
  return result;
}
// 51AD7C: using guessed type int dword_51AD7C[];
// 51AD80: using guessed type int dword_51AD80;
// 51AD84: using guessed type int dword_51AD84;
// 51AD88: using guessed type int dword_51AD88;
// 51AD8C: using guessed type int dword_51AD8C;
// 51AD90: using guessed type int dword_51AD90;
// 51AD94: using guessed type int dword_51AD94;
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (00499990) --------------------------------------------------------
int Rules_RegisterDefclassConstruct()
{
  int v0; // ecx
  int v1; // ecx

  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_Defclass, 57);
  g_CLIPS_DefclassModuleItemIndex = Module_RegisterItem(
                   (int)aDefclass,
                   (int)Class_AllocRecord,
                   (int)Class_RecordAtIndex,
                   (int)Class_FreeRecord,
                   (int)ObjectsCompiler_WriteModuleItemHeaderRef,
                   (int)Class_LookupCurrentScopedName);
  g_ClipsDefclassConstructType = (int)Rules_RegisterConstructType(
                        (int)aDefclass,
                        (int)aDefclasses,
                        (int)Class_LookupCurrentScopedName,
                        (int)Rules_ParseDefclass,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Class_GetNextRecord,
                        (int)Rules_SetConstructNextInModule,
                        (int)Class_IsDeletable,
                        (int)Class_IsDeletableAlt,
                        (int)Class_DestroyRecord);
  Rules_AddClearReadyFunction((int)aDefclass, (int)Class_PrepareUndefineCheck, 0);
  Rules_AddClearFunction((int)aDefclass, (int)Class_CreateSystemClasses, 0);
  Class_InitHashTables();
  Module_RegisterImportExportConstructType((int)aDefclass, 2);
  Module_AddAfterModuleDefinedCallback((int)aDefclass, (int)Class_RefreshWatchExpressions, 0);
  Rules_RegisterHostFunction(aUndefclass, 118, v0, (int)Class_UndefineCommand, (int)a11w_5);
  Rules_AddSaveFunction((int)aDefclass, (int)Class_ListAllConstructs, 10);
  Rules_RegisterHostFunction(aListDefclasses, 118, v1, (int)Class_ListConstructsCommand, (int)a01_1);
  Rules_RegisterHostFunction(aPpdefclass, 118, (int)aPpdefclasscomm, (int)Class_PrettyPrintCommand, (int)a11w_5);
  Rules_RegisterHostFunction(aDescribeClass, 118, (int)aDescribeclassc, (int)Class_DescribeClassCommand, (int)a11w_5);
  Rules_RegisterHostFunction(aBrowseClasses, 118, (int)aBrowseclassesc, (int)Class_BrowseClassesCommand, (int)a01w_3);
  Rules_RegisterHostFunction(aGetDefclassLis, 109, (int)aGetdefclasslis, (int)Class_GetConstructListCommand, (int)a01_1);
  Rules_RegisterHostFunction(aSuperclassp, 98, (int)aSuperclasspcom, (int)Class_SuperclassPCommand, (int)a22w);
  Rules_RegisterHostFunction(aSubclassp, 98, (int)aSubclasspcomma, (int)Class_SubclassPCommand, (int)a22w);
  Rules_RegisterHostFunction(aClassExistp, 98, (int)aClassexistpcom, (int)Class_ClassExistPCommand, (int)a11w_5);
  Rules_RegisterHostFunction(aMessageHandler, 98, (int)aMessagehandler, (int)Class_MessageHandlerExistPCommand, (int)a23w);
  Rules_RegisterHostFunction(aClassAbstractp, 98, (int)aClassabstractp, (int)Class_ClassAbstractPCommand, (int)a11w_5);
  Rules_RegisterHostFunction(aClassReactivep, 98, (int)aClassreactivep, (int)Class_ClassReactivePCommand, (int)a11w_5);
  Rules_RegisterHostFunction(aClassSlots, 109, (int)aClassslotscomm, (int)Class_ClassSlotsCommand, (int)a12w);
  Rules_RegisterHostFunction(aClassSuperclas, 109, (int)aClasssuperclas, (int)Class_ClassSuperclassesCommand, (int)a12w);
  Rules_RegisterHostFunction(aClassSubclasse, 109, (int)aClasssubclasse, (int)Class_ClassSubclassesCommand, (int)a12w);
  Rules_RegisterHostFunction(aGetDefmessageH, 109, (int)aGetdefmessageh, (int)Class_GetDefmessageHandlerListCommand, (int)a02w);
  Rules_RegisterHostFunction(aSlotExistp, 98, (int)aSlotexistpcomm, (int)Class_SlotExistPCommand, (int)a23w);
  Rules_RegisterHostFunction(aSlotFacets, 109, (int)aSlotfacetscomm, (int)Class_SlotFacetsCommand, (int)a22w);
  Rules_RegisterHostFunction(aSlotSources, 109, (int)aSlotsourcescom, (int)Class_SlotSourcesCommand, (int)a22w);
  Rules_RegisterHostFunction(aSlotTypes, 109, (int)aSlottypescomma, (int)Class_SlotTypesCommand, (int)a22w);
  Rules_RegisterHostFunction(aSlotAllowedVal, 109, (int)aSlotallowedval, (int)Class_SlotAllowedValuesFunction, (int)a22w);
  Rules_RegisterHostFunction(aSlotRange, 109, (int)aSlotrangecomma, (int)Class_SlotRangeFunction, (int)a22w);
  Rules_RegisterHostFunction(aSlotCardinalit, 109, (int)aSlotcardinalit, (int)Class_SlotCardinalityFunction, (int)a22w);
  Rules_RegisterHostFunction(aSlotWritablep, 98, (int)aSlotwritablepc, (int)Class_SlotWritablePCommand, (int)a22we);
  Rules_RegisterHostFunction(aSlotInitablep, 98, (int)aSlotinitablepc, (int)Class_SlotInitablePCommand, (int)a22we);
  Rules_RegisterHostFunction(aSlotPublicp, 98, (int)aSlotpublicpcom, (int)Class_SlotPublicPCommand, (int)a22we);
  Rules_RegisterHostFunction(aSlotDirectAcce, 98, (int)aSlotdirectacce, (int)Class_SlotDirectAccessPCommand, (int)a22we);
  Rules_RegisterHostFunction(aDefclassModule, 119, (int)aGetdefclassmod, (int)Class_DefclassModuleCommand, (int)a11w_5);
  Rules_AddWatchItem((int)aInstances_0, 0, 75, (int)&g_Rules_WatchInstances, (int)Class_SetWatchFlagCommand, (int)Class_SetWatchFlagForModuleCommand);
  return Rules_AddWatchItem((int)aSlots, 1, 74, (int)g_Class_WatchSlots, (int)Class_SetWatchFlagCommand, (int)Class_SetWatchFlagForModuleCommand);
}
// 499A70: variable 'v0' is possibly undefined
// 499AA2: variable 'v1' is possibly undefined
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 54E6B8: using guessed type int dword_54E6B8;
// 54E6BC: using guessed type int dword_54E6BC;

//----- (00499E00) --------------------------------------------------------
int  Class_CreateSystemClass(char *a1, int a2, int a3)
{
  signed int *class_symbol; // eax
  char class_flags; // dl
  int symbol; // eax
  unsigned int bucket_index; // eax
  int expression; // eax
  unsigned int inherited_index; // esi
  int inherited_class; // edx
  int class_record; // [esp+0h] [ebp-1Ch]
  _BYTE *class_bitmap; // [esp+4h] [ebp-18h]

  (void)a3;
  class_symbol = Str_Intern(a1, a2);
  class_record = Class_AllocateRecord((int)class_symbol);
  class_flags = *(_BYTE *)(class_record + 20) | 4;
  *(_BYTE *)(class_record + 20) = class_flags;
  symbol = *(_DWORD *)class_record;
  *(_BYTE *)(class_record + 20) = class_flags & 0xF7;
  ++*(_DWORD *)(symbol + 4);
  symbol = *(_DWORD *)class_record;
  *(_BYTE *)(class_record + 20) |= 3u;
  bucket_index = Class_HashClassName(symbol);
  *(_DWORD *)(class_record + 30) = bucket_index;
  Class_InsertLinkEntry((unsigned __int16 *)(class_record + 46), class_record, -1);
  if ( a2 )
  {
    Class_InsertLinkEntry((unsigned __int16 *)(class_record + 34), a2, -1);
    Class_InsertLinkEntry((unsigned __int16 *)(a2 + 40), class_record, -1);
    inherited_index = 1;
    inherited_class = a2;
    while ( 1 )
    {
      Class_InsertLinkEntry((unsigned __int16 *)(class_record + 46), inherited_class, -1);
      if ( inherited_index >= *(unsigned __int16 *)(a2 + 46) )
        break;
      inherited_class = *(_DWORD *)(*(_DWORD *)(a2 + 48) + 4 * inherited_index);
      ++inherited_index;
    }
  }
  *(_DWORD *)(class_record + 100) = *(_DWORD *)(g_DefclassHashTable + 4 * *(_DWORD *)(class_record + 30));
  *(_DWORD *)(g_DefclassHashTable + 4 * *(_DWORD *)(class_record + 30)) = class_record;
  class_bitmap = Mem_SmallBlockAlloc(1);
  Mem_AllocArray(class_bitmap, 1);
  class_bitmap[0] |= 1u;
  expression = Rules_AddBitmapValue(class_bitmap, 1);
  Mem_SmallBlockFree((_DWORD *)class_bitmap, 1);
  *(_DWORD *)(class_record + 104) = expression;
  ++*(_DWORD *)(expression + 4);
  return class_record;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (00499F20) --------------------------------------------------------
signed int Class_AllocRecord()
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499F50) --------------------------------------------------------
int  Class_FreeRecord(int theModuleItem)
{
  _DWORD *isaSlotName; // eax
  _DWORD *nameSlotName; // eax
  _DWORD *freed_node; // ecx
  int result; // eax

  Rules_ClearModuleConstructList(theModuleItem, g_ClipsDefclassConstructType, theModuleItem);
  isaSlotName = (_DWORD *)Class_FindSlotNameEntryByID(0);
  Class_ReleaseSlotName(isaSlotName);
  nameSlotName = (_DWORD *)Class_FindSlotNameEntryByID(1);
  Class_ReleaseSlotName(nameSlotName);
  freed_node = (_DWORD *)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 499F7F: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B8: using guessed type int dword_54E6B8;

//----- (00499FA0) --------------------------------------------------------
signed int Class_RefreshWatchExpressions()
{
  int moduleCount; // eax
  int v1; // edx
  int v2; // ecx
  int *theClass; // ebp
  _BYTE *v4; // edi
  int v5; // ebx
  _BYTE *className; // ebx
  int newBitmap; // eax
  int v9; // [esp+0h] [ebp-34h] BYREF
  _BYTE *scopeBytePtr; // [esp+4h] [ebp-30h]
  int bucketOffset; // [esp+8h] [ebp-2Ch]
  int v12; // [esp+Ch] [ebp-28h]
  int scopeBitMask; // [esp+10h] [ebp-24h]
  int bitmapSize; // [esp+14h] [ebp-20h]
  _BYTE *bitmapBuffer; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  moduleCount = Module_GetModuleCount();
  bitmapSize = ((moduleCount - (__CFSHL__(moduleCount >> 31, 3) + 8 * (moduleCount >> 31))) >> 3) + 1;
  bitmapBuffer = Mem_SmallBlockAlloc(bitmapSize);
  bucketOffset = 0;
  scopeBytePtr = &bitmapBuffer[(v2 - (__CFSHL__(v1 >> 31, 3) + 8 * (v1 >> 31))) >> 3];
  scopeBitMask = 1 << (v2 % 8);
  do
  {
    theClass = *(int **)(bucketOffset + g_DefclassHashTable);
    if ( theClass )
    {
      v4 = bitmapBuffer;
      do
      {
        v5 = *theClass;
        v12 = *(_DWORD *)theClass[2];
        className = *(_BYTE **)(v5 + 16);
        Mem_AllocArray(bitmapBuffer, bitmapSize);
        qmemcpy(v4, *(const void **)(theClass[26] + 16), *(unsigned __int16 *)(theClass[26] + 20));
        Rules_DecrementBitmapCount(theClass[26], 0);
        if ( (theClass[5] & 2) != 0 || Rules_FindImportExportConstruct(aDefclass, &v9, className, 1, 0) )
          *scopeBytePtr |= scopeBitMask;
        newBitmap = Rules_AddBitmapValue(bitmapBuffer, bitmapSize);
        theClass[26] = newBitmap;
        ++*(_DWORD *)(newBitmap + 4);
        theClass = (int *)theClass[25];
      }
      while ( theClass );
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  return Mem_SmallBlockFree(bitmapBuffer, bitmapSize);
}
// 499FDD: variable 'v2' is possibly undefined
// 499FCF: variable 'v1' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (0049A0E0) --------------------------------------------------------
int __cdecl ProcParam_RegisterPrimitiveTypes(void)
{
  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_ProcArgument, 65);
  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_ProcWildcardArgument, 66);
  Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_ProcBoundVariable, 67);
  return Rules_RegisterEvaluationHandler((int)&g_EvalDescriptor_ProcBindLocalVariable, 68);
}

//----- (0049A120) --------------------------------------------------------
int  Parser_ParseProcParameters(
        int readSource,
        _DWORD *theToken,
        _DWORD *wildcardSymbol,
        int parameterList,
        _DWORD *minParamsOut,
        _DWORD *maxParamsOut,
        _DWORD *errorFlag,
        int (*checkfunc)(void))
{
  _DWORD *tokenPtr; // esi
  int paramListHead; // edi
  int i; // eax
  int j; // eax
  _DWORD *v13; // ecx
  int tokenType; // edx
  int duplicateCursor; // eax
  signed int newParamNode; // eax
  _DWORD *v17; // ecx
  int v19; // ecx
  int v20; // ecx
  int paramPrinted; // [esp+4h] [ebp-10h]

  tokenPtr = theToken;
  paramListHead = parameterList;
  *wildcardSymbol = 0;
  *minParamsOut = 0;
  paramPrinted = 0;
  *errorFlag = 1;
  for ( i = parameterList; i; i = *(_DWORD *)(i + 10) )
  {
    ++*minParamsOut;
    parameterList = i;
  }
  if ( *theToken == 100 )
  {
    for ( j = readSource; ; j = readSource )
    {
      Parser_NextToken(j, (int)theToken);
      tokenType = *tokenPtr;
      if ( *tokenPtr != 15 && tokenType != 16 )
        break;
      duplicateCursor = paramListHead;
      if ( paramListHead )
      {
        while ( *(_DWORD *)(duplicateCursor + 2) != tokenPtr[1] )
        {
          duplicateCursor = *(_DWORD *)(duplicateCursor + 10);
          if ( !duplicateCursor )
            goto LABEL_9;
        }
        Rules_PrintErrorID((int)aPrccode_0, 7, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicatePar_0, v19);
        AST_Free(paramListHead);
        return 0;
      }
LABEL_9:
      if ( *wildcardSymbol )
      {
        Rules_PrintErrorID((int)aPrccode_0, 8, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoParameters_0, v20);
        AST_Free(paramListHead);
        return 0;
      }
      if ( checkfunc && checkfunc() )
        goto LABEL_18;
      newParamNode = AST_NewNode(*tokenPtr, tokenPtr[1]);
      if ( *tokenPtr == 16 )
        *wildcardSymbol = tokenPtr[1];
      else
        ++*v17;
      if ( parameterList )
        *(_DWORD *)(parameterList + 10) = newParamNode;
      else
        paramListHead = newParamNode;
      parameterList = newParamNode;
      IO_OutWriteToken(asc_505C54);
      theToken = tokenPtr;
      paramPrinted = 1;
    }
    if ( tokenType != 101 )
      goto LABEL_17;
    if ( paramPrinted )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_505C58);
    }
    *errorFlag = 0;
    if ( *wildcardSymbol )
      *maxParamsOut = -1;
    else
      *maxParamsOut = *v13;
    return paramListHead;
  }
  else
  {
LABEL_17:
    Parser_ReportSyntaxError();
LABEL_18:
    AST_Free(paramListHead);
    return 0;
  }
}
// 49A282: variable 'v19' is possibly undefined
// 49A2B4: variable 'v20' is possibly undefined
// 49A2CB: variable 'v17' is possibly undefined
// 49A2DA: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049A2F0) --------------------------------------------------------
_DWORD * Parser_ParseProcActions(
        int bodyType,
        int readSource,
        int parameterList,
        int wildcardSymbol,
        int (*altVarFunc)(void),
        int (*altBindFunc)(void),
        int *localVarCountOut,
        int userBuffer)
{
  unsigned int *v11; // edx
  _DWORD *result; // eax
  _DWORD *actions; // esi
  int v14; // eax
  int v15; // ecx
  _DWORD *unwrappedActions; // eax
  int v17; // ecx
  int v18; // edx

  Parser_FreeLoopContextStack();
  result = (_DWORD *)Parser_ParseProgram(readSource, v11, 1);
  actions = result;
  if ( result )
  {
    if ( altBindFunc && Parser_ScanBindStatementsForSymbol((int)result, altBindFunc, userBuffer) )
    {
      Parser_FreeLoopContextStack();
      v14 = v15;
    }
    else
    {
      *localVarCountOut = Rules_CountNamedContextEntries();
      if ( !Parser_ReplaceProcVars(bodyType, (int)actions, wildcardSymbol, parameterList, altVarFunc, userBuffer) )
      {
        unwrappedActions = AST_UnwrapActionListWrapper(actions);
        AST_PackNodeChain(unwrappedActions);
        AST_Free(v17);
        Parser_FreeLoopContextStack();
        return (_DWORD *)v18;
      }
      Parser_FreeLoopContextStack();
      v14 = (int)actions;
    }
    AST_Free(v14);
    return 0;
  }
  return result;
}
// 49A309: variable 'v11' is possibly undefined
// 49A36C: variable 'v15' is possibly undefined
// 49A382: variable 'v17' is possibly undefined
// 49A38C: variable 'v18' is possibly undefined

//----- (0049A3A0) --------------------------------------------------------
signed int  Parser_ReplaceProcVars(
        int bodyType,
        int actions,
        int wildcardSymbol,
        int parameterList,
        int (*altVarFunc)(void),
        int specData)
{
  int actionExpr; // esi
  int v8; // ecx
  signed int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  signed int v18; // eax
  _DWORD *v19; // edx
  _DWORD *varNode; // ebx
  int v21; // eax
  int bindExpr; // eax
  signed int v23; // edx
  _DWORD *v24; // eax
  signed int paramIndex; // [esp+0h] [ebp-28h] BYREF
  signed int bindIndex; // [esp+4h] [ebp-24h] BYREF
  int bitmapData; // [esp+8h] [ebp-20h] BYREF
  int v28; // [esp+Ch] [ebp-1Ch]
  int v29; // [esp+10h] [ebp-18h]
  _DWORD *savedVarNode; // [esp+14h] [ebp-14h]
  int v31; // [esp+18h] [ebp-10h]

  v31 = bodyType;
  actionExpr = actions;
  v28 = parameterList;
  v29 = wildcardSymbol;
  if ( !actions )
    return 0;
  while ( 1 )
  {
    if ( *(_WORD *)actionExpr == 15 )
    {
      paramIndex = Parser_FindProcParamIndex(*(_DWORD *)(actionExpr + 2), v28, v29);
      v9 = Rules_FindNamedContextDepth(v8);
      bindIndex = v9;
      if ( paramIndex || v9 )
      {
        if ( paramIndex <= 0 || bindIndex )
        {
          if ( altVarFunc )
          {
            varNode = (_DWORD *)AST_NewNode(*(_WORD *)actionExpr, *(_DWORD *)(actionExpr + 2));
            savedVarNode = varNode;
            v21 = altVarFunc();
            if ( v21 )
            {
              if ( v21 == -1 )
              {
                g_ClipsMemFreeListTemp = (int)varNode;
                *varNode = *(_DWORD *)(g_ClipsMemoryTable + 56);
                *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
                return 1;
              }
            }
            else
            {
              g_ClipsMemFreeListTemp = (int)varNode;
              *varNode = *(_DWORD *)(g_ClipsMemoryTable + 56);
              savedVarNode = 0;
              *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
            }
          }
          else
          {
            savedVarNode = 0;
          }
          *(_WORD *)actionExpr = 67;
          Mem_AllocArray(&bitmapData, 4);
          LOWORD(bitmapData) = bitmapData & 1;
          bitmapData |= 2 * (bindIndex & 0x7FFF);
          HIWORD(bitmapData) = BYTE2(bitmapData) & 1;
          bitmapData |= (paramIndex & 0x7FFF) << 17;
          BYTE2(bitmapData) &= ~1u;
          bitmapData |= (v16 == v29) << 16;
          *(_DWORD *)(actionExpr + 2) = Rules_AddBitmapValue(&bitmapData, 4);
          v18 = AST_NewNode(2, v17);
          v19 = savedVarNode;
          *(_DWORD *)(actionExpr + 6) = v18;
          *(_DWORD *)(v18 + 10) = v19;
        }
        else
        {
          *(_WORD *)actionExpr = (v10 == v29) + 65;
          *(_DWORD *)(actionExpr + 2) = Rules_AddBitmapValue(&paramIndex, 4);
        }
      }
      else if ( !altVarFunc || altVarFunc() != 1 )
      {
        Rules_PrintErrorID((int)aPrccode_0, 3, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUndefinedVaria, v11);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v12 + 16), v12);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReferencedIn, v13);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], v31, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ExpressionError, v15);
        return 1;
      }
    }
    else if ( *(_WORD *)actionExpr == 13 && !Defglobal_ResolveGlobalVariableReference(actionExpr, wildcardSymbol) )
    {
      return -1;
    }
    if ( altVarFunc && ((int (__fastcall *)(int, int))altVarFunc)(wildcardSymbol, specData) == -1 )
      return 1;
    wildcardSymbol = *(_DWORD *)(actionExpr + 6);
    if ( wildcardSymbol )
      break;
LABEL_6:
    actionExpr = *(_DWORD *)(actionExpr + 10);
    if ( !actionExpr )
      return 0;
  }
  if ( !Parser_ReplaceProcVars(v31, wildcardSymbol, v29, v28, (int (__fastcall *)(_DWORD, _DWORD))altVarFunc, specData) )
  {
    if ( Rules_MakeSymbol(aBind_1) == *(int ***)(actionExpr + 2) && **(_WORD **)(actionExpr + 6) == 2 )
    {
      bindExpr = *(_DWORD *)(actionExpr + 6);
      *(_WORD *)actionExpr = 68;
      bindIndex = Rules_FindNamedContextDepth(*(_DWORD *)(bindExpr + 2));
      *(_DWORD *)(actionExpr + 2) = Rules_AddBitmapValue(&bindIndex, v23);
      v24 = *(_DWORD **)(actionExpr + 6);
      wildcardSymbol = *(_DWORD *)((char *)v24 + 10);
      g_ClipsMemFreeListTemp = (int)v24;
      *v24 = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
      *(_DWORD *)(actionExpr + 6) = wildcardSymbol;
    }
    goto LABEL_6;
  }
  return 1;
}
// 49A40F: variable 'v8' is possibly undefined
// 49A460: variable 'v11' is possibly undefined
// 49A46A: variable 'v12' is possibly undefined
// 49A47C: variable 'v13' is possibly undefined
// 49A48A: variable 'v14' is possibly undefined
// 49A499: variable 'v15' is possibly undefined
// 49A531: variable 'v16' is possibly undefined
// 49A55D: variable 'v17' is possibly undefined
// 49A578: variable 'v10' is possibly undefined
// 49A610: variable 'a3' is possibly undefined
// 49A6B4: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A6F0) --------------------------------------------------------
signed int  AST_NewProcParamNode(int paramIndex)
{
  int bitmapValue; // eax
  int bitmapData; // [esp+0h] [ebp-8h] BYREF

  bitmapData = paramIndex;
  bitmapValue = Rules_AddBitmapValue(&bitmapData, 4);
  return AST_NewNode(66, bitmapValue);
}

//----- (0049A720) --------------------------------------------------------
int (* ProcParam_PushEvaluatedArgumentFrame(
        _DWORD *a1,
        int a2,
        int a3,
        int a4,
        double a5,
        int (*a6)(void)))(void)
{
  _DWORD *v7; // ebp
  _DWORD *v8; // esi
  _DWORD *v9; // esi
  int (*result)(void); // eax

  v7 = *(_DWORD **)(g_ClipsMemoryTable + 96);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = *v7;
    v8 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  *v8 = g_ClipsProcParamArray;
  v8[2] = g_ClipsProcParamCount;
  v8[4] = g_ProcParam_ErrorContextCallback;
  v8[5] = g_ProcParamSavedFrameStack;
  g_ProcParamSavedFrameStack = (int)v8;
  ProcParam_EvaluateArgumentExpressions(a1, a2, a3, a4, a5);
  if ( g_ClipsEvaluationError )
  {
    v9 = (_DWORD *)g_ProcParamSavedFrameStack;
    g_ProcParamSavedFrameStack = *(_DWORD *)(g_ProcParamSavedFrameStack + 20);
    g_ClipsMemFreeListTemp = (int)v9;
    *v9 = *(_DWORD *)(g_ClipsMemoryTable + 96);
    result = (int (*)(void))g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8[1] = g_Clips_ProcParamArgChain;
    g_Clips_ProcParamArgChain = 0;
    v8[3] = g_ClipsProcParamWildcardValue;
    result = a6;
    g_ClipsProcParamWildcardValue = 0;
    g_ProcParam_ErrorContextCallback = a6;
  }
  return result;
}
// 49A76B: variable 'a3' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;
// 51ABC4: using guessed type int dword_51ABC4;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A7F0) --------------------------------------------------------
int ProcParam_PopFrame()
{
  int *frameNode; // edx
  int result; // eax

  if ( g_ClipsProcParamArray )
    Mem_SmallBlockFree((_DWORD *)g_ClipsProcParamArray, 24 * g_ClipsProcParamCount);
  if ( g_Clips_ProcParamArgChain )
    Mem_SmallBlockFree((_DWORD *)g_Clips_ProcParamArgChain, 14 * g_ClipsProcParamCount);
  frameNode = (int *)g_ProcParamSavedFrameStack;
  g_ProcParamSavedFrameStack = *(_DWORD *)(g_ProcParamSavedFrameStack + 20);
  g_ClipsProcParamArray = *frameNode;
  g_ClipsProcParamCount = frameNode[2];
  g_Clips_ProcParamArgChain = frameNode[1];
  if ( g_ClipsProcParamWildcardValue )
  {
    Rules_DeinstallMultifield(*(__int16 **)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(g_ClipsProcParamWildcardValue + 8));
    g_ClipsMemFreeListTemp = g_ClipsProcParamWildcardValue;
    *(_DWORD *)g_ClipsProcParamWildcardValue = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  }
  g_ClipsProcParamWildcardValue = frameNode[3];
  g_ProcParam_ErrorContextCallback = (int (*)(void))frameNode[4];
  g_ClipsMemFreeListTemp = (int)frameNode;
  *frameNode = *(_DWORD *)(g_ClipsMemoryTable + 96);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  return result;
}
// 49A853: variable 'v0' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;
// 51ABC4: using guessed type int dword_51ABC4;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A8F0) --------------------------------------------------------
int ProcParam_BuildArgumentExpressionChain()
{
  int v1; // ecx
  int paramIndex; // edx
  int chainOffset; // eax
  int valueSlot; // ebx
  int v5; // ebx
  int nextLink; // ebx

  if ( !g_ClipsProcParamArray || g_Clips_ProcParamArgChain )
    return g_Clips_ProcParamArgChain;
  g_Clips_ProcParamArgChain = (int)Mem_SmallBlockAlloc(14 * g_ClipsProcParamCount);
  paramIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    chainOffset = 0;
    do
    {
      *(_WORD *)(g_Clips_ProcParamArgChain + chainOffset) = *(_WORD *)(g_ClipsProcParamArray + v1 + 4);
      valueSlot = v1 + g_ClipsProcParamArray;
      if ( *(_DWORD *)(v1 + g_ClipsProcParamArray + 4) != 4 )
        valueSlot = *(_DWORD *)(valueSlot + 8);
      *(_DWORD *)(g_Clips_ProcParamArgChain + chainOffset + 2) = valueSlot;
      *(_DWORD *)(g_Clips_ProcParamArgChain + chainOffset + 6) = 0;
      v5 = paramIndex + 1;
      if ( paramIndex + 1 == g_ClipsProcParamCount )
        nextLink = g_ClipsProcParamCount ^ v5;
      else
        nextLink = g_Clips_ProcParamArgChain + 14 * v5;
      v1 += 24;
      *(_DWORD *)(g_Clips_ProcParamArgChain + chainOffset + 10) = nextLink;
      ++paramIndex;
      chainOffset += 14;
    }
    while ( paramIndex < g_ClipsProcParamCount );
  }
  return g_Clips_ProcParamArgChain;
}
// 49A949: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;

//----- (0049A9E0) --------------------------------------------------------
int  Rules_ExecuteRuleActions(
        int theModule,
        __int16 *actions,
        _DWORD *returnValue,
        int localVarCount,
        double context,
        void (*crtproc)(void))
{
  _DWORD *localVarArray; // eax
  int v10; // eax
  int v11; // ebx
  _DWORD *varSlot; // ecx
  int saved_module; // ecx
  int v14; // eax
  int v16; // ecx
  int v17; // ecx
  int varOffset; // edx
  int result; // eax
  int savedLocalVarArray; // [esp+0h] [ebp-14h]

  savedLocalVarArray = g_ClipsProcFrameDataObjectArray;
  if ( localVarCount )
    localVarArray = Mem_SmallBlockAlloc(24 * localVarCount);
  else
    localVarArray = 0;
  g_ClipsProcFrameDataObjectArray = (int)localVarArray;
  if ( localVarCount > 0 )
  {
    v10 = 0;
    v11 = 24 * localVarCount;
    do
    {
      varSlot = (_DWORD *)(g_ClipsProcFrameDataObjectArray + v10);
      v10 += 24;
      *varSlot = g_ClipsFalseSymbol;
    }
    while ( v10 < v11 );
  }
  saved_module = Module_GetCurrent();
  if ( saved_module != theModule )
    Module_SetCurrent(theModule);
  if ( Parser_ParseForm(actions, returnValue, saved_module, context) )
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  v14 = Module_GetCurrent();
  if ( saved_module != v14 )
    Module_SetCurrent(saved_module);
  if ( crtproc && g_ClipsHaltExecution )
  {
    Rules_PrintErrorID((int)aPrccode_0, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExecutionHal_0, v16);
    crtproc();
  }
  v17 = g_ClipsProcParamWildcardValue;
  if ( g_ClipsProcParamWildcardValue && returnValue[2] == *(_DWORD *)(g_ClipsProcParamWildcardValue + 8) )
  {
    Rules_DeinstallMultifield(*(__int16 **)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(g_ClipsProcParamWildcardValue + 8));
    g_ClipsMemFreeListTemp = g_ClipsProcParamWildcardValue;
    *(_DWORD *)g_ClipsProcParamWildcardValue = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    g_ClipsProcParamWildcardValue = 0;
  }
  if ( localVarCount )
  {
    if ( localVarCount > 0 )
    {
      varOffset = 0;
      do
      {
        if ( g_ClipsTrueSymbol == *(_DWORD *)(varOffset + g_ClipsProcFrameDataObjectArray) )
          Rules_ValueDeinstall(varOffset + g_ClipsProcFrameDataObjectArray, v17);
        varOffset += 24;
      }
      while ( varOffset < 24 * localVarCount );
    }
    Mem_SmallBlockFree((_DWORD *)g_ClipsProcFrameDataObjectArray, 24 * localVarCount);
  }
  result = savedLocalVarArray;
  g_ClipsProcFrameDataObjectArray = savedLocalVarArray;
  return result;
}
// 49AAAB: variable 'v16' is possibly undefined
// 49AB3B: variable 'v17' is possibly undefined
// 49AB40: variable 'v18' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A968: using guessed type int dword_51A968;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABCC: using guessed type int dword_51ABCC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049AB90) --------------------------------------------------------
signed int  ProcParam_PrintArguments(int logicalName)
{
  int v1; // ecx
  int paramIndex; // ebx
  int paramOffset; // esi

  Output_Write(logicalName, (int)asc_505CB4, logicalName);
  paramIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    paramOffset = 0;
    do
    {
      Rules_PrintDataObject(v1, paramOffset + g_ClipsProcParamArray);
      if ( paramIndex != g_ClipsProcParamCount - 1 )
        Output_Write(v1, (int)asc_505C54, v1);
      ++paramIndex;
      paramOffset += 24;
    }
    while ( paramIndex < g_ClipsProcParamCount );
  }
  return Output_Write(v1, (int)asc_505CB8, v1);
}
// 49ABB9: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;

//----- (0049AC00) --------------------------------------------------------
__int16 * ProcParam_BuildWildcardMultifield(_DWORD *returnValue, int theIndex)
{
  _DWORD *freeListHead; // ebx
  signed int newWildcardRec; // eax
  signed int size; // esi
  int v6; // ebx
  int v7; // eax
  _DWORD *theMultifield; // eax
  int destFieldIndex; // esi
  int v10; // eax
  int paramRecord; // ebx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  __int16 *result; // eax
  int wildcardRec; // eax
  _DWORD *emptyMultifield; // eax
  int v18; // edx
  int paramIndex; // [esp+0h] [ebp-18h]
  int paramOffset; // [esp+4h] [ebp-14h]

  returnValue[1] = 4;
  returnValue[3] = 0;
  if ( g_ClipsProcParamWildcardValue )
  {
    if ( theIndex == g_ProcParamCachedWildcardArgIndex )
    {
      returnValue[4] = *(_DWORD *)(g_ClipsProcParamWildcardValue + 16);
      result = *(__int16 **)(g_ClipsProcParamWildcardValue + 8);
      returnValue[2] = result;
      return result;
    }
    Rules_DeinstallMultifield(*(__int16 **)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(g_ClipsProcParamWildcardValue + 8));
  }
  else
  {
    freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListHead;
      newWildcardRec = g_ClipsMemFreeListTemp;
    }
    else
    {
      newWildcardRec = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    g_ClipsProcParamWildcardValue = newWildcardRec;
    *(_DWORD *)(newWildcardRec + 12) = 0;
  }
  size = g_ClipsProcParamCount - theIndex + 1;
  g_ProcParamCachedWildcardArgIndex = theIndex;
  if ( size <= 0 )
  {
    wildcardRec = g_ClipsProcParamWildcardValue;
    *(_DWORD *)(g_ClipsProcParamWildcardValue + 16) = -1;
    returnValue[4] = *(_DWORD *)(wildcardRec + 16);
    emptyMultifield = Rules_CreateMultifield(0);
    *(_DWORD *)(g_ClipsProcParamWildcardValue + 8) = emptyMultifield;
    returnValue[2] = emptyMultifield;
    return Rules_InstallMultifield(*(__int16 **)(g_ClipsProcParamWildcardValue + 8));
  }
  else
  {
    v6 = theIndex - 1;
    if ( theIndex - 1 < g_ClipsProcParamCount )
    {
      v7 = 24 * v6;
      do
      {
        if ( *(_DWORD *)(v7 + g_ClipsProcParamArray + 4) == 4 )
          size += *(_DWORD *)(v7 + g_ClipsProcParamArray + 16) - *(_DWORD *)(v7 + g_ClipsProcParamArray + 12);
        v7 += 24;
        ++v6;
      }
      while ( v7 < 24 * g_ClipsProcParamCount );
    }
    *(_DWORD *)(g_ClipsProcParamWildcardValue + 16) = size - 1;
    returnValue[4] = size - 1;
    theMultifield = Rules_CreateMultifield(size);
    *(_DWORD *)(g_ClipsProcParamWildcardValue + 8) = theMultifield;
    paramIndex = theIndex - 1;
    returnValue[2] = theMultifield;
    destFieldIndex = 1;
    if ( theIndex - 1 < g_ClipsProcParamCount )
    {
      paramOffset = 24 * (theIndex - 1);
      do
      {
        v10 = paramOffset + g_ClipsProcParamArray;
        if ( *(_DWORD *)(paramOffset + g_ClipsProcParamArray + 4) == 4 )
        {
          paramRecord = paramOffset + g_ClipsProcParamArray;
          v12 = *(_DWORD *)(v10 + 12) + 1;
          v13 = 6 * destFieldIndex - 6;
          v14 = 6 * v12 - 6;
          while ( v12 <= *(_DWORD *)(paramRecord + 16) + 1 )
          {
            v14 += 6;
            ++v12;
            *(_WORD *)(v13 + returnValue[2] + 14) = *(_WORD *)(v14 + *(_DWORD *)(paramRecord + 8) + 8);
            v13 += 6;
            ++destFieldIndex;
            *(_DWORD *)(v13 + returnValue[2] + 10) = *(_DWORD *)(v14 + *(_DWORD *)(paramRecord + 8) + 10);
          }
        }
        else
        {
          v18 = 6 * (destFieldIndex - 1);
          *(_WORD *)(returnValue[2] + v18 + 14) = *(_WORD *)(v10 + 4);
          ++destFieldIndex;
          *(_DWORD *)(returnValue[2] + v18 + 16) = *(_DWORD *)(g_ClipsProcParamArray + paramOffset + 8);
        }
        paramOffset += 24;
        ++paramIndex;
      }
      while ( paramIndex < g_ClipsProcParamCount );
    }
    return Rules_InstallMultifield(*(__int16 **)(g_ClipsProcParamWildcardValue + 8));
  }
}
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC8: using guessed type int dword_51ABC8;
// 51AC94: using guessed type int dword_51AC94;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049AE70) --------------------------------------------------------
_DWORD * ProcParam_EvaluateArgumentExpressions(uintptr_t result, int numberOfParameters, int functionName, int bodyType, double context)
{
  uintptr_t expression; // esi
  _DWORD *argument_values; // eax
  _DWORD *argument_slot; // ecx
  _DWORD parsed[6]; // [esp+0h] [ebp-2Ch] BYREF

  expression = result;
  if ( numberOfParameters )
  {
    argument_values = Mem_SmallBlockAlloc(24 * numberOfParameters);
    if ( expression )
    {
      argument_slot = argument_values;
      while ( Parser_ParseForm((__int16 *)expression, parsed, (int)(uintptr_t)argument_slot, context) != 1 && parsed[1] != 105 )
      {
        argument_slot[1] = parsed[1];
        argument_slot[2] = parsed[2];
        argument_slot[3] = parsed[3];
        argument_slot[4] = parsed[4];
        expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
        argument_slot += 6;
        if ( !expression )
          goto LABEL_11;
      }
      if ( parsed[1] == 105 )
      {
        Rules_PrintErrorID((int)aPrccode_0, 2, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionsWitho, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArguments__0, 0);
        Lexer_ErrorRecover(1);
      }
      Rules_PrintErrorID((int)aPrccode_0, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForThe, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505C54, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], bodyType, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ExpressionError, 0);
      return (_DWORD *)Mem_SmallBlockFree(argument_values, 24 * numberOfParameters);
    }
    else
    {
LABEL_11:
      result = (uintptr_t)argument_values;
      g_ClipsProcParamCount = numberOfParameters;
      g_ClipsProcParamArray = (int)(uintptr_t)argument_values;
    }
  }
  else
  {
    g_ClipsProcParamArray = 0;
    g_ClipsProcParamCount = 0;
  }
  return (_DWORD *)result;
}
// 49AEEE: variable 'v11' is possibly undefined
// 49AEFA: variable 'v12' is possibly undefined
// 49AF09: variable 'v13' is possibly undefined
// 49AF33: variable 'v14' is possibly undefined
// 49AF42: variable 'v15' is possibly undefined
// 49AF4E: variable 'v16' is possibly undefined
// 49AF5D: variable 'v17' is possibly undefined
// 49AF6B: variable 'v18' is possibly undefined
// 49AF7A: variable 'v19' is possibly undefined
// 49AFB6: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;

//----- (0049B000) --------------------------------------------------------
signed int  ProcParam_GetArgumentValue(int theValue, _DWORD *returnValue)
{
  int payload; // eax
  int record; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  record = g_ClipsProcParamArray + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  returnValue[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
  returnValue[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
  returnValue[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
  returnValue[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
  return 1;
}
// 51ABB8: using guessed type int dword_51ABB8;

//----- (0049B040) --------------------------------------------------------
signed int  ProcParam_GetBoundVariableValue(int theValue, _DWORD *returnValue, double context)
{
  int payload; // edx
  int record; // eax
  int expression; // eax
  unsigned int raw_index; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  raw_index = *(_DWORD *)(uintptr_t)(unsigned int)payload;
  record = g_ClipsProcFrameDataObjectArray + 24 * ((((unsigned int)raw_index << 16) >> 17) - 1);
  if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
    goto LABEL_6;
  expression = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)expression + 10), returnValue, (int)(uintptr_t)returnValue, context);
    return 1;
  }
  if ( (*(_WORD *)((uintptr_t)(unsigned int)payload + 2) & 0xFFFE) != 0 )
  {
    if ( (*(_BYTE *)((uintptr_t)(unsigned int)payload + 2) & 1) == 0 )
    {
      record = 24 * ((raw_index >> 17) - 1) + g_ClipsProcParamArray;
LABEL_6:
      returnValue[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
      returnValue[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
      returnValue[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
      returnValue[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
      return 1;
    }
    ProcParam_BuildWildcardMultifield(returnValue, raw_index >> 17);
    return 1;
  }
  else
  {
    Rules_PrintErrorID((int)aPrccode_0, 5, 0);
    Lexer_ErrorRecover(1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable, 0);
    Output_Write(
      (int)g_IO_LogicalNameTable_WError[0],
      *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)expression + 2) + 16),
      0);
    if ( g_ProcParam_ErrorContextCallback )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnboundIn, 0);
      g_ProcParam_ErrorContextCallback();
    }
    else
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnbound_, 0);
    }
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return 1;
  }
}
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABCC: using guessed type int dword_51ABCC;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B190) --------------------------------------------------------
signed int  ProcParam_BindLocalVariable(int theValue, _DWORD *returnValue, double context)
{
  int payload; // eax
  int record; // ecx
  int expression; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  record = g_ClipsProcFrameDataObjectArray + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  expression = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
  {
    if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
      Rules_ValueDeinstall(record, record);
    *(_DWORD *)(uintptr_t)(unsigned int)record = g_ClipsFalseSymbol;
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return 1;
  }
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(returnValue, expression, 1, context);
  else
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)expression, returnValue, record, context);
  if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
    Rules_ValueDeinstall(record, record);
  *(_DWORD *)(uintptr_t)(unsigned int)record = g_ClipsTrueSymbol;
  *(_DWORD *)((uintptr_t)(unsigned int)record + 4) = returnValue[1];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 8) = returnValue[2];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 12) = returnValue[3];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 16) = returnValue[4];
  Rules_ValueInstall(record, record);
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 51ABCC: using guessed type int dword_51ABCC;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B250) --------------------------------------------------------
signed int  ProcParam_GetWildcardArgumentValue(int theValue, _DWORD *returnValue)
{
  int payload; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  ProcParam_BuildWildcardMultifield(returnValue, *(_DWORD *)(uintptr_t)(unsigned int)payload);
  return 1;
}

//----- (0049B270) --------------------------------------------------------
signed int  Parser_FindProcParamIndex(int variableSymbol, int parameterList, int wildcardSymbol)
{
  signed int result; // eax

  result = 1;
  if ( parameterList )
  {
    while ( variableSymbol != *(_DWORD *)(parameterList + 2) )
    {
      parameterList = *(_DWORD *)(parameterList + 10);
      ++result;
      if ( !parameterList )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    if ( variableSymbol != wildcardSymbol )
      return 0;
  }
  return result;
}

//----- (0049B2A0) --------------------------------------------------------
signed int  Parser_ScanBindStatementsForSymbol(int actions, int (*altBindFunc)(void), int userBuffer)
{
  int exprCursor; // ecx
  int **Symbol; // eax
  int bindArgs; // eax
  int bindSymbol; // ebx
  int bindCode; // eax
  int v11; // ecx

  exprCursor = actions;
  if ( !actions )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(exprCursor + 6) )
      {
        if ( Parser_ScanBindStatementsForSymbol(*(_DWORD *)(exprCursor + 6), (int (__fastcall *)(_DWORD, _DWORD))altBindFunc, userBuffer) )
          return 1;
        Symbol = Rules_MakeSymbol(aBind_1);
        if ( Symbol == *(int ***)(exprCursor + 2) )
        {
          bindArgs = *(_DWORD *)(exprCursor + 6);
          if ( *(_WORD *)bindArgs == 2 )
          {
            bindSymbol = *(_DWORD *)(bindArgs + 2);
            bindCode = altBindFunc();
            if ( bindCode == -1 )
              return 1;
            if ( bindCode == 1 )
              break;
          }
        }
      }
      exprCursor = *(_DWORD *)(exprCursor + 10);
      if ( !exprCursor )
        return 0;
    }
    Rules_RemoveNamedContextEntry(bindSymbol);
    exprCursor = *(_DWORD *)(v11 + 10);
  }
  while ( exprCursor );
  return 0;
}
// 49B2B4: variable 'v3' is possibly undefined
// 49B30B: variable 'v11' is possibly undefined

//----- (0049B320) --------------------------------------------------------
_DWORD * AST_UnwrapActionListWrapper(_DWORD *result)
{
  int childExpr; // edx
  _DWORD *wrapperNode; // ecx

  childExpr = *(_DWORD *)((char *)result + 6);
  if ( childExpr )
  {
    if ( !*(_DWORD *)(childExpr + 10) )
    {
      wrapperNode = result;
      result = *(_DWORD **)((char *)result + 6);
      g_ClipsMemFreeListTemp = (int)wrapperNode;
      *wrapperNode = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    }
  }
  else
  {
    *(_WORD *)result = 2;
    *(_DWORD *)((char *)result + 2) = g_ClipsFalseSymbol;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B370) --------------------------------------------------------
signed int Rules_RegisterFileIOCommands()
{
  Rules_RegisterHostFunction(aBatch, 98, (int)aBatchcommand, (int)Rules_BatchCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aBatch_0, 98, (int)aBatchstarcomma, (int)Rules_BatchStarCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aDribbleOn, 98, (int)aDribbleoncomma, (int)Rules_DribbleOnCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aDribbleOff, 98, (int)aDribbleoffcomm, (int)Rules_DribbleOffCommand, (int)a00_4);
  Rules_RegisterHostFunction(aSave, 98, (int)aSavecommand, (int)Rules_SaveCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aLoad, 98, (int)aLoadcommand, (int)Rules_LoadCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aLoad_0, 98, (int)aLoadstarcomman, (int)Rules_LoadStarCommand, (int)a11k_4);
  Rules_RegisterHostFunction(aBsave, 98, (int)aBsavecommand, (int)Rules_BsaveCommand, (int)a11k_4);
  return Rules_RegisterHostFunction(aBload_1, 98, (int)aBloadcommand, (int)Rules_BloadCommand, (int)a11k_4);
}

//----- (0049B490) --------------------------------------------------------
BOOL  Dribble_QueryRouter(int logicalName)
{
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  return !strcmp_(logicalName, aStdout_2)
      || !strcmp_(v1, aStdin_2)
      || !strcmp_(v3, g_IO_LogicalNameTable_WClips[0])
      || !strcmp_(v4, g_IO_LogicalNameTable_WTrace[0])
      || !strcmp_(v5, g_IO_LogicalNameTable_WError[0])
      || !strcmp_(v6, g_IO_LogicalNameTable_WWarning[0])
      || !strcmp_(v7, g_IO_LogicalName_WDisplay)
      || !strcmp_(v8, g_IO_LogicalNameTable_WDialog[0]);
}
// 49B4B1: variable 'v1' is possibly undefined
// 49B4C2: variable 'v3' is possibly undefined
// 49B4D3: variable 'v4' is possibly undefined
// 49B4E4: variable 'v5' is possibly undefined
// 49B4F5: variable 'v6' is possibly undefined
// 49B506: variable 'v7' is possibly undefined
// 49B517: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A620: using guessed type char *off_51A620[2];
// 51A624: using guessed type char *off_51A624;

//----- (0049B530) --------------------------------------------------------
signed int  Dribble_PrintRouter(int logicalName, unsigned __int8 *str, int a3)
{
  unsigned __int8 *v4; // ecx
  unsigned __int8 *charPtr; // edx
  _BYTE *v6; // edx
  char v7; // al
  int v8; // ecx
  int timestampIndex; // edx
  int v11; // edx
  char v12; // al
  _BYTE timestampBuffer[16]; // [esp+0h] [ebp-18h] BYREF
  int v14; // [esp+10h] [ebp-8h]

  v14 = a3;
  v4 = str;
  if ( g_Dribble_LineStartNeedsTimestamp )
  {
    sprintf_(
      timestampBuffer,
      "%03d:%02d:%02d ",
      *(_DWORD *)g_CLIPS_DribbleClockCentisecsPtr / 0x1770u % 0x3C,
      *(_DWORD *)g_CLIPS_DribbleClockCentisecsPtr / 0x64u % 0x3C,
      *(_DWORD *)g_CLIPS_DribbleClockCentisecsPtr % 0x64u);
    timestampIndex = 0;
    if ( timestampBuffer[0] )
    {
      do
      {
        Dribble_AppendChar((char *)(unsigned __int8)timestampBuffer[timestampIndex], timestampIndex, (int)v4);
        v12 = timestampBuffer[v11 + 1];
        timestampIndex = v11 + 1;
      }
      while ( v12 );
    }
    g_Dribble_LineStartNeedsTimestamp = 0;
  }
  charPtr = v4;
  if ( *v4 )
  {
    do
    {
      Dribble_AppendChar((char *)*charPtr, (int)charPtr, (int)v4);
      if ( *v6 == 10 )
        g_Dribble_LineStartNeedsTimestamp = 1;
      v7 = v6[1];
      charPtr = v6 + 1;
    }
    while ( v7 );
  }
  IO_DeactivateRouter((int)aDribble);
  Output_Write(logicalName, v8, v8);
  IO_ActivateRouter((int)aDribble);
  return 1;
}
// 49B545: variable 'v4' is possibly undefined
// 49B559: variable 'v6' is possibly undefined
// 49B57A: variable 'v8' is possibly undefined
// 49B5F4: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACBC: using guessed type int dword_51ACBC;
// 54E6C0: using guessed type int dword_54E6C0;

//----- (0049B610) --------------------------------------------------------
int Dribble_GetcRouter()
{
  int v0; // edx
  unsigned int v1; // ecx
  char *v2; // edx
  int v3; // ecx
  int v4; // edx

  IO_DeactivateRouter((int)aDribble);
  Lexer_PeekChar(v0, v1);
  IO_ActivateRouter((int)aDribble);
  Dribble_AppendChar(v2, (int)v2, v3);
  return v4;
}
// 49B61F: variable 'v0' is possibly undefined
// 49B61F: variable 'v1' is possibly undefined
// 49B632: variable 'v2' is possibly undefined
// 49B632: variable 'v3' is possibly undefined
// 49B637: variable 'v4' is possibly undefined
// 49B610: using guessed type int sub_49B610();

//----- (0049B640) --------------------------------------------------------
char * Dribble_AppendChar(char *result, int a2, int a3)
{
  if ( result == (char *)-1 )
  {
    if ( g_DribbleBufferLength > 0 )
    {
      Output_WriteFormatted(g_DribbleFileHandle, g_Clips_DribbleBuffer, g_DribbleFileHandle, (int)aS_3, g_Clips_DribbleBuffer);
      result = (char *)g_Clips_DribbleBuffer;
      g_DribbleBufferLength = 0;
      *(_BYTE *)g_Clips_DribbleBuffer = 0;
    }
  }
  else if ( g_Lexer_PendingLineCharIndex >= 0 )
  {
    result = Str_AppendCharEscaping(
               (int)result,
               (char *)g_Clips_DribbleBuffer,
               (unsigned int *)&g_Dribble_BufferCapacity,
               &g_DribbleBufferLength,
               g_Dribble_BufferCapacity + 120);
    g_Clips_DribbleBuffer = (int)result;
  }
  else
  {
    if ( g_DribbleBufferLength > 0 )
    {
      Output_WriteFormatted(a3, a2, g_DribbleFileHandle, (int)aS_3, g_Clips_DribbleBuffer);
      g_DribbleBufferLength = 0;
      *(_BYTE *)g_Clips_DribbleBuffer = 0;
    }
    return (char *)CRT_PutcToStream(a3, g_DribbleFileHandle);
  }
  return result;
}
// 49B6CF: variable 'a3' is possibly undefined
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);
// 51A628: using guessed type int dword_51A628;
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA0: using guessed type int dword_51ACA0;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B710) --------------------------------------------------------
int Dribble_UngetcRouter()
{
  int v0; // edx
  signed int v1; // ecx
  int v2; // edx

  if ( g_DribbleBufferLength > 0 )
    --g_DribbleBufferLength;
  *(_BYTE *)(g_DribbleBufferLength + g_Clips_DribbleBuffer) = 0;
  IO_DeactivateRouter((int)aDribble);
  Lexer_SkipChar(v1, v0, v1);
  IO_ActivateRouter((int)aDribble);
  return v2;
}
// 49B743: variable 'v1' is possibly undefined
// 49B743: variable 'v0' is possibly undefined
// 49B754: variable 'v2' is possibly undefined
// 51AC9C: using guessed type int dword_51AC9C;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B760) --------------------------------------------------------
int __fastcall Dribble_ExitRouter(int a1, int a2)
{
  int v3; // [esp-4h] [ebp-8h]

  if ( g_DribbleBufferLength > 0 )
  {
    v3 = a1;
    Output_WriteFormatted(g_Clips_DribbleBuffer, a2, g_DribbleFileHandle, (int)aS_3, g_Clips_DribbleBuffer);
    a1 = v3;
  }
  if ( g_DribbleFileHandle )
    fclose_(a1);
  return 1;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B7B0) --------------------------------------------------------
const CHAR * Rules_DribbleOnCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)Dribble_TurnOn(result, a1);
  return result;
}
// 49B7D7: variable 'v2' is possibly undefined

//----- (0049B7F0) --------------------------------------------------------
signed int  Dribble_TurnOn(const CHAR *fileName, DWORD a2)
{
  const CHAR *v2; // ecx
  int v3; // ecx

  v2 = fileName;
  if ( g_DribbleFileHandle )
    Dribble_TurnOff();
  g_DribbleFileHandle = IO_FOpen(v2, (unsigned __int8 *)aW_3, (int)v2, a2);
  if ( g_DribbleFileHandle )
  {
    IO_AddRouter((int)aDribble, 40, (int)Dribble_PrintRouter, (int)Dribble_QueryRouter, (int)Dribble_GetcRouter, (int)Dribble_UngetcRouter, (int)Dribble_ExitRouter);
    g_DribbleBufferLength = 0;
    if ( g_Dribble_StatusChangeCallback )
      g_Dribble_StatusChangeCallback(0);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v3, v3);
    return 0;
  }
}
// 49B809: variable 'v2' is possibly undefined
// 49B86D: variable 'v3' is possibly undefined
// 49B610: using guessed type int sub_49B610();
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA4: using guessed type int (__thiscall *dword_51ACA4)(_DWORD);

//----- (0049B890) --------------------------------------------------------
signed int Rules_DribbleOffCommand()
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Dribble_TurnOff();
}

//----- (0049B8C0) --------------------------------------------------------
signed int Dribble_TurnOff()
{
  int (__thiscall *statusCallback)(_DWORD); // edx
  int v1; // ecx
  int v2; // ecx
  signed int v3; // ecx
  signed int result; // eax

  statusCallback = g_Dribble_StatusChangeCallback;
  v1 = 0;
  if ( g_Dribble_StatusChangeCallback )
    g_Dribble_StatusChangeCallback(0);
  if ( !g_DribbleFileHandle )
    goto LABEL_7;
  if ( g_DribbleBufferLength > 0 )
    Output_WriteFormatted(v1, (int)statusCallback, g_DribbleFileHandle, (int)aS_3, g_Clips_DribbleBuffer);
  IO_DeleteRouter((int)aDribble);
  if ( !fclose_(v2) )
LABEL_7:
    v3 = 1;
  g_DribbleFileHandle = 0;
  if ( g_Clips_DribbleBuffer )
  {
    Mem_SmallBlockFree((_DWORD *)g_Clips_DribbleBuffer, g_Dribble_BufferCapacity);
    g_Clips_DribbleBuffer = 0;
  }
  result = v3;
  g_DribbleBufferLength = 0;
  g_Dribble_BufferCapacity = 0;
  return result;
}
// 49B8F1: variable 'v1' is possibly undefined
// 49B8F1: variable 'v0' is possibly undefined
// 49B909: variable 'v2' is possibly undefined
// 49B92A: variable 'v3' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA0: using guessed type int dword_51ACA0;
// 51ACA4: using guessed type int (__thiscall *dword_51ACA4)(_DWORD);
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B980) --------------------------------------------------------
BOOL __thiscall Rules_BatchQueryStdin(void *this)
{
  return strcmp_(this, aStdin_2) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0049B9A0) --------------------------------------------------------
int  Rules_BatchGetChar(int logicalName)
{
  return Rules_BatchReadChar(logicalName, 0);
}

//----- (0049B9B0) --------------------------------------------------------
int  Rules_BatchReadChar(int logicalName, unsigned int returnOnEOF)
{
  unsigned int returnOnEofFlag; // esi
  signed int v4; // ecx
  int v5; // edi
  int ch; // eax
  unsigned int v7; // ecx
  unsigned __int8 *v9; // eax
  char *appended; // eax
  int v11; // ecx
  int rv; // [esp+0h] [ebp-18h]

  returnOnEofFlag = returnOnEOF;
  v4 = 1;
  do
  {
    if ( g_ClipsBatchSourceIsStringFlag )
    {
      ch = Lexer_PeekChar(g_CurrentStringInputSource, v4);
    }
    else
    {
      v5 = *(_DWORD *)(g_CurrentStringInputSource + 4);
      if ( v5 > 0 && (returnOnEOF = **(unsigned __int8 **)g_CurrentStringInputSource - 13, returnOnEOF > 0xFD) )
      {
        *(_DWORD *)(g_CurrentStringInputSource + 4) = v5 - 1;
        returnOnEOF = g_CurrentStringInputSource;
        v9 = (unsigned __int8 *)(*(_DWORD *)g_CurrentStringInputSource)++;
        ch = *v9;
      }
      else
      {
        ch = fgetc_(v4, returnOnEOF);
      }
    }
    rv = ch;
    if ( ch == -1 )
    {
      if ( g_BatchEchoBufferLength > 0 )
        Output_Write((int)aStdout_2, g_ClipsBatchEchoLineBuffer, v4);
      v4 = Rules_CloseBatch();
    }
  }
  while ( rv == -1 && v4 == 1 );
  if ( rv == -1 )
  {
    if ( g_BatchEchoBufferLength > 0 )
      Output_Write((int)aStdout_2, g_ClipsBatchEchoLineBuffer, v4);
    IO_DeleteRouter((int)aBatch);
    Rules_CloseBatch();
    if ( returnOnEofFlag == 1 )
      return -1;
    else
      return Lexer_PeekChar(logicalName, v7);
  }
  else
  {
    appended = Str_AppendCharEscaping(
                 (unsigned __int8)rv,
                 (char *)g_ClipsBatchEchoLineBuffer,
                 (unsigned int *)&g_ClipsBatchLineBufferCapacity,
                 &g_BatchEchoBufferLength,
                 g_ClipsBatchLineBufferCapacity + 120);
    g_ClipsBatchEchoLineBuffer = (int)appended;
    if ( (_BYTE)rv == 10 )
    {
      Output_Write((int)aStdout_2, (int)appended, v11);
      g_BatchEchoBufferLength = 0;
      if ( g_ClipsBatchEchoLineBuffer )
      {
        if ( g_ClipsBatchLineBufferCapacity > 120 )
        {
          Mem_SmallBlockFree((_DWORD *)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
          g_ClipsBatchLineBufferCapacity = 0;
          g_ClipsBatchEchoLineBuffer = 0;
        }
      }
    }
    return rv;
  }
}
// 49B9F8: variable 'v4' is possibly undefined
// 49B9F8: variable 'a2' is possibly undefined
// 49BAA2: variable 'v7' is possibly undefined
// 49BAE1: variable 'v11' is possibly undefined
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BB30) --------------------------------------------------------
signed int  Rules_BatchUngetChar(signed int ch, int logicalName)
{
  if ( g_BatchEchoBufferLength > 0 )
    logicalName = --g_BatchEchoBufferLength;
  if ( g_ClipsBatchEchoLineBuffer )
    *(_BYTE *)(g_ClipsBatchEchoLineBuffer + g_BatchEchoBufferLength) = 0;
  if ( g_ClipsBatchSourceIsStringFlag )
    return Lexer_SkipChar(ch, g_CurrentStringInputSource, logicalName);
  else
    return CRT_FlushBufferAndPutChar(ch, logicalName);
}
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BB90) --------------------------------------------------------
signed int __thiscall Rules_BatchExitFunction(void *this)
{
  Rules_CloseAllBatchSources(this);
  return 1;
}

//----- (0049BBA0) --------------------------------------------------------
const CHAR * Rules_BatchCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)Rules_OpenBatch(result, 0, v4, a1);
  return result;
}
// 49BBC7: variable 'v2' is possibly undefined
// 49BBD2: variable 'v4' is possibly undefined

//----- (0049BBF0) --------------------------------------------------------
signed int  Rules_OpenBatch(const CHAR *fileName, int placeAtEnd, int a3, DWORD a4)
{
  int v6; // ecx
  int theFile; // edi

  theFile = IO_FOpen(fileName, (unsigned __int8 *)aR_1, a3, a4);
  if ( theFile )
  {
    if ( !g_Rules_BatchStackTop )
      IO_AddRouter((int)aBatch, 20, 0, (int)Rules_BatchQueryStdin, (int)Rules_BatchGetChar, (int)Rules_BatchUngetChar, (int)Rules_BatchExitFunction);
    Rules_AddBatchEntry(placeAtEnd, theFile, 0, 0);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v6, (int)fileName);
    return 0;
  }
}
// 49BC54: variable 'v6' is possibly undefined
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BCC0) --------------------------------------------------------
_DWORD * Rules_AddBatchEntry(int placeAtEnd, int theSource, int theString, int sourceType)
{
  _DWORD *freeListHead; // edi
  _DWORD *result; // eax

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 64);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListHead;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  result[3] = 0;
  *result = sourceType;
  result[1] = theSource;
  result[2] = theString;
  if ( g_Rules_BatchStackTop )
  {
    if ( placeAtEnd )
    {
      *(_DWORD *)(g_Batch_ListTail + 12) = result;
      g_Batch_ListTail = (int)result;
    }
    else
    {
      result[3] = g_Rules_BatchStackTop;
      g_Rules_BatchStackTop = (int)result;
      g_ClipsBatchSourceIsStringFlag = sourceType;
      g_CurrentStringInputSource = theSource;
      g_BatchEchoBufferLength = 0;
    }
  }
  else
  {
    g_Rules_BatchStackTop = (int)result;
    g_Batch_ListTail = (int)result;
    g_ClipsBatchSourceIsStringFlag = sourceType;
    g_CurrentStringInputSource = theSource;
    g_BatchEchoBufferLength = 0;
  }
  return result;
}
// 49BCED: variable 'a3' is possibly undefined
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB4: using guessed type int dword_51ACB4;
// 51ACB8: using guessed type int dword_51ACB8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BD60) --------------------------------------------------------
signed int Rules_CloseBatch()
{
  _DWORD *poppedEntry; // eax
  signed int result; // eax

  if ( !g_Rules_BatchStackTop )
    return 0;
  if ( *(_DWORD *)g_Rules_BatchStackTop )
  {
    IO_CloseStringRouter(*(_DWORD *)(g_Rules_BatchStackTop + 4));
    Mem_SmallBlockFree(*(_DWORD **)(g_Rules_BatchStackTop + 8), strlen(*(const char **)(g_Rules_BatchStackTop + 8)) + 1);
  }
  else
  {
    fclose_(0);
  }
  poppedEntry = (_DWORD *)g_Rules_BatchStackTop;
  g_Rules_BatchStackTop = *(_DWORD *)(g_Rules_BatchStackTop + 12);
  g_ClipsMemFreeListTemp = (int)poppedEntry;
  *poppedEntry = *(_DWORD *)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  if ( g_Rules_BatchStackTop )
  {
    g_ClipsBatchSourceIsStringFlag = *(_DWORD *)g_Rules_BatchStackTop;
    g_CurrentStringInputSource = *(_DWORD *)(g_Rules_BatchStackTop + 4);
    g_BatchEchoBufferLength = 0;
    return 1;
  }
  else
  {
    g_Batch_ListTail = 0;
    g_CurrentStringInputSource = 0;
    if ( g_ClipsBatchEchoLineBuffer )
    {
      Mem_SmallBlockFree((_DWORD *)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
      g_ClipsBatchEchoLineBuffer = 0;
    }
    result = 0;
    g_BatchEchoBufferLength = 0;
    g_ClipsBatchLineBufferCapacity = 0;
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 51ACB4: using guessed type int dword_51ACB4;
// 51ACB8: using guessed type int dword_51ACB8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BE60) --------------------------------------------------------
BOOL Rules_BatchIsActive()
{
  return g_Rules_BatchStackTop != 0;
}
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BE70) --------------------------------------------------------
signed int __thiscall Rules_CloseAllBatchSources(void *this)
{
  signed int result; // eax

  if ( g_ClipsBatchEchoLineBuffer )
  {
    if ( g_BatchEchoBufferLength > 0 )
      Output_Write((int)aStdout_2, g_ClipsBatchEchoLineBuffer, (int)this);
    Mem_SmallBlockFree((_DWORD *)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
    g_ClipsBatchEchoLineBuffer = 0;
    g_BatchEchoBufferLength = 0;
    g_ClipsBatchLineBufferCapacity = 0;
  }
  IO_DeleteRouter((int)aBatch);
  do
    result = Rules_CloseBatch();
  while ( result );
  return result;
}
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 54E6C8: using guessed type int dword_54E6C8;

//----- (0049BED0) --------------------------------------------------------
const CHAR * Rules_BatchStarCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)Rules_BatchStar(result, a1, context);
  return result;
}
// 49BEF7: variable 'v2' is possibly undefined

//----- (0049BF10) --------------------------------------------------------
signed int  Rules_BatchStar(const CHAR *fileName, DWORD a2, double context)
{
  char *appended; // edi
  int v4; // ecx
  int *theFile; // esi
  int v6; // edx
  int v7; // ecx
  int ch; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  unsigned __int8 *v13; // eax
  int lineLength; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int bufferSize[6]; // [esp+4h] [ebp-18h] BYREF

  appended = 0;
  lineLength = 0;
  bufferSize[0] = 0;
  theFile = (int *)IO_FOpen(fileName, (unsigned __int8 *)aR_1, (int)fileName, a2);
  if ( theFile )
  {
    Rules_SetEvaluationErrorFlag(0);
    Lexer_ErrorRecover(0);
    while ( 1 )
    {
      if ( theFile[1] <= 0 || (unsigned int)*(unsigned __int8 *)*theFile - 13 <= 0xFD )
      {
        ch = fgetc_(v7, v6);
      }
      else
      {
        v13 = (unsigned __int8 *)*theFile;
        v9 = *theFile + 1;
        --theFile[1];
        *theFile = v9;
        ch = *v13;
      }
      if ( ch == -1 )
        break;
      appended = Str_AppendCharEscaping(ch, appended, bufferSize, &lineLength, bufferSize[0] + 80);
      if ( Lexer_IsCommandTextComplete((signed int)appended) )
      {
        Rules_FlushPPBuffer();
        Rules_SetPPBufferStatus(0);
        Rules_RouteCommand(v10, 0, v10, context);
        Rules_FlushPPBuffer();
        Rules_SetEvaluationErrorFlag(0);
        Lexer_ErrorRecover(0);
        Rules_FreeBoundVariableEntry();
        appended = 0;
        Mem_ReleasePoolBlock(v11, bufferSize[0]);
        bufferSize[0] = 0;
        lineLength = 0;
      }
    }
    fclose_(v9);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v4, v4);
    return 0;
  }
}
// 49BF53: variable 'v7' is possibly undefined
// 49BF53: variable 'v6' is possibly undefined
// 49BF95: variable 'v10' is possibly undefined
// 49BFBA: variable 'v11' is possibly undefined
// 49BFD3: variable 'v4' is possibly undefined
// 49C016: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);

//----- (0049C030) --------------------------------------------------------
int  Rules_LoadCommand(DWORD a1, double context)
{
  int v2; // ecx
  int result; // eax
  const CHAR *v4; // edx
  int v5; // ecx
  int loadResult; // ecx
  int v7; // edx
  int v8; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, context);
  if ( result )
  {
    Rules_SetLoadInProgress(1);
    if ( Rules_Load(v4, v5, a1) )
    {
      Rules_SetLoadInProgress(0);
      return loadResult != -1;
    }
    else
    {
      Rules_SetLoadInProgress(0);
      Rules_OpenFileErrorMessage(v8, v7);
      return 0;
    }
  }
  return result;
}
// 49C059: variable 'v2' is possibly undefined
// 49C070: variable 'v4' is possibly undefined
// 49C070: variable 'v5' is possibly undefined
// 49C085: variable 'v6' is possibly undefined
// 49C097: variable 'v8' is possibly undefined
// 49C097: variable 'v7' is possibly undefined

//----- (0049C0B0) --------------------------------------------------------
const CHAR * Rules_LoadStarCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx
  int fileName; // edx
  signed int loadResult; // eax
  int v7; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, context);
  fileName = (int)result;
  if ( result )
  {
    loadResult = Rules_Load(result, v4, a1);
    if ( loadResult )
    {
      return (const CHAR *)(loadResult != -1);
    }
    else
    {
      Rules_OpenFileErrorMessage(v7, fileName);
      return 0;
    }
  }
  return result;
}
// 49C0D7: variable 'v2' is possibly undefined
// 49C0E2: variable 'v4' is possibly undefined
// 49C0FA: variable 'v7' is possibly undefined

//----- (0049C110) --------------------------------------------------------
int  Rules_SaveCommand(DWORD a1, double context)
{
  int v2; // ecx
  int result; // eax
  int v4; // ecx
  int fileName; // edx
  int v6; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, context);
  fileName = result;
  if ( result )
  {
    if ( Rules_Save((const CHAR *)result, v4, a1) )
    {
      return 1;
    }
    else
    {
      Rules_OpenFileErrorMessage(v6, fileName);
      return 0;
    }
  }
  return result;
}
// 49C137: variable 'v2' is possibly undefined
// 49C142: variable 'v4' is possibly undefined
// 49C158: variable 'v6' is possibly undefined

//----- (0049C170) --------------------------------------------------------
signed int  Rules_Load(const CHAR *fileName, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  result = IO_FOpen(fileName, (unsigned __int8 *)aR_2, a2, a3);
  if ( result )
  {
    IO_SetFastLoadFile(result);
    Rules_LoadConstructsFromLogicalName(v4, v5);
    IO_SetFastLoadFile(0);
    fclose_(v6);
    if ( v7 )
      return 1;
    else
      return -1;
  }
  return result;
}
// 49C18C: variable 'v4' is possibly undefined
// 49C18C: variable 'v5' is possibly undefined
// 49C19C: variable 'v6' is possibly undefined
// 49C1A3: variable 'v7' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (0049C1C0) --------------------------------------------------------
int  Rules_LoadConstructsFromLogicalName(int readSource, int a2)
{
  int v4; // edx
  _DWORD *v5; // ecx
  int v6; // ecx
  char *v7; // eax
  _DWORD *v8; // ecx
  signed int errorCorrection; // ebx
  int v11; // ecx
  int theToken; // [esp-4h] [ebp-20h] BYREF
  _DWORD noErrorsFlag[5]; // [esp+8h] [ebp-14h] BYREF

  noErrorsFlag[3] = a2;
  noErrorsFlag[0] = 1;
  if ( !g_ClipsCurrentEvaluationDepth )
    Rules_SetEvaluationErrorFlag(0);
  Lexer_ErrorRecover(0);
  Parser_NextToken(readSource, v4);
  if ( Rules_SkipToConstructBeginning(readSource, &theToken, v5, 0) == 1 )
  {
    do
    {
      if ( Rules_GetEvaluationErrorFlag() )
        break;
      Rules_FlushPPBuffer();
      if ( Rules_ParseConstruct() == 1 )
      {
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aError_2, v6);
        v7 = (char *)Rules_GetPPBuffer();
        Output_WriteLongString((signed int)g_IO_LogicalNameTable_WError[0], v7);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505E94, (int)noErrorsFlag);
        noErrorsFlag[0] = 0;
        Parser_NextToken(readSource, (int)&theToken);
        errorCorrection = 1;
      }
      else
      {
        Parser_NextToken(readSource, (int)&theToken);
        errorCorrection = 0;
      }
    }
    while ( Rules_SkipToConstructBeginning(readSource, &theToken, v8, errorCorrection) == 1 );
  }
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 || !Rules_GetLoadInProgress() )
  {
    Rules_DestroyPPBuffer();
    return noErrorsFlag[0];
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_505E94, v11);
    Rules_DestroyPPBuffer();
    return noErrorsFlag[0];
  }
}
// 49C1F1: variable 'v4' is possibly undefined
// 49C1FA: variable 'v5' is possibly undefined
// 49C237: variable 'v6' is possibly undefined
// 49C27B: variable 'v8' is possibly undefined
// 49C2D5: variable 'v11' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A96C: using guessed type int dword_51A96C;

//----- (0049C2F0) --------------------------------------------------------
signed int  Rules_SkipToConstructBeginning(int readSource, _DWORD *theToken, _DWORD *noErrorsOut, signed int errorCorrection)
{
  int firstAttempt; // ecx
  int leftParenFound; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  firstAttempt = 1;
  leftParenFound = 0;
  if ( *theToken == 102 )
    return 0;
  while ( *theToken == 100 )
  {
    leftParenFound = 1;
LABEL_4:
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken == 102 )
      return 0;
  }
  if ( *theToken != 2 || leftParenFound != 1 )
  {
    if ( firstAttempt )
    {
      if ( !errorCorrection )
      {
        errorCorrection = 1;
        *noErrorsOut = 0;
        Rules_PrintErrorID((int)aCstrcpsr, 1, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedTheBeg, v10);
      }
    }
    leftParenFound = 0;
    goto LABEL_4;
  }
  if ( !Rules_FindConstructByName() )
  {
    if ( v11 && !errorCorrection )
    {
      *noErrorsOut = 0;
      errorCorrection = 1;
      Rules_PrintErrorID((int)aCstrcpsr, 1, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedTheBeg, v12);
    }
    leftParenFound = 0;
    goto LABEL_4;
  }
  return 1;
}
// 49C33D: variable 'v7' is possibly undefined
// 49C367: variable 'v10' is possibly undefined
// 49C383: variable 'v11' is possibly undefined
// 49C3A4: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049C3C0) --------------------------------------------------------
signed int Rules_ParseConstruct()
{
  int constructRecord; // ebx
  int v2; // edx
  int v3; // ecx

  constructRecord = Rules_FindConstructByName();
  if ( !constructRecord )
    return -1;
  Rules_GetEvaluationErrorFlag();
  Lexer_ErrorRecover(0);
  Rules_SetEvaluationErrorFlag(0);
  Parser_FreeLoopContextStack();
  Parser_PushFunctionParseState();
  g_ClipsParseReturnContext = 0;
  g_ParserBreakContextFlag = 0;
  ++g_ClipsCurrentEvaluationDepth;
  (*(void (**)(void))(constructRecord + 8))();
  --g_ClipsCurrentEvaluationDepth;
  Parser_PopFunctionParseState();
  Parser_FreeLoopContextStack();
  Rules_SetPPBufferStatus(0);
  Rules_SetEvaluationErrorFlag(v2);
  return v3;
}
// 49C434: variable 'v2' is possibly undefined
// 49C439: variable 'v3' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (0049C440) --------------------------------------------------------
int  Rules_GetConstructNameAndComment(
        int readSource,
        int inputToken,
        int (*findFunction)(void),
        char *constructName,
        int (*deleteFunction)(void),
        char *constructSymbol,
        int fullMessageCR,
        int getComment,
        int moduleNameAllowed)
{
  signed int moduleSeparator; // eax
  int separatorPosition; // ebx
  signed int *moduleNameSymbol; // eax
  int *theModule; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  signed int *constructNameSymbol; // ecx
  int v20; // ecx
  int v21; // ecx
  char *v22; // edx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  char *v27; // edx
  int v28; // ecx
  int v29; // edx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // edx
  char *Name; // eax
  int v36; // ecx
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int savedModule; // [esp+0h] [ebp-18h]
  int redefining; // [esp+8h] [ebp-10h]

  redefining = 0;
  Parser_NextToken(readSource, inputToken);
  if ( *(_DWORD *)inputToken != 2 )
  {
    Rules_PrintErrorID((int)aCstrcpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMissingNameFor, v31);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)constructName, v32);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConstruct, v33);
    return 0;
  }
  moduleSeparator = Rules_FindModuleSeparator(*(_BYTE **)(*(_DWORD *)(inputToken + 4) + 16));
  separatorPosition = moduleSeparator;
  if ( moduleSeparator )
  {
    if ( !moduleNameAllowed )
      goto LABEL_23;
    moduleNameSymbol = Rules_ExtractModuleName(moduleSeparator);
    if ( !moduleNameSymbol )
      goto LABEL_23;
    theModule = Module_FindByName((_BYTE *)moduleNameSymbol[4]);
    savedModule = (int)theModule;
    if ( !theModule )
    {
      Rules_ReportCantFindItem(v17, *(_DWORD *)(v16 + 16));
      return 0;
    }
    Module_SetCurrent((int)theModule);
    constructNameSymbol = Rules_ExtractConstructName(separatorPosition, *(char **)(v18 + 16), v18);
    if ( !constructNameSymbol )
    {
LABEL_23:
      Parser_ReportSyntaxError();
      return 0;
    }
  }
  else
  {
    savedModule = Module_GetCurrent();
    if ( moduleNameAllowed )
    {
      IO_OutNewline();
      Name = (char *)Module_GetName(v34);
      IO_OutWriteToken(Name);
      IO_OutWriteToken(asc_505F2C);
      IO_OutWriteToken(*(char **)(v36 + 16));
    }
  }
  if ( Rules_FindImportExportConflict(constructName, savedModule, (_BYTE *)constructNameSymbol[4]) )
  {
    Lexer_WarnImpliedTemplate((int)constructName, *(_DWORD *)(v20 + 16), 0);
    return 0;
  }
  if ( findFunction )
  {
    if ( findFunction() )
    {
      redefining = 1;
      if ( deleteFunction )
      {
        if ( !deleteFunction() )
        {
          Rules_PrintErrorID((int)aCstrcpsr, 4, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRedefine, v37);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)constructName, v38);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505F44, v39);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v40 + 16), v40);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWhileItIsInUse, v41);
          return 0;
        }
      }
    }
  }
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
  {
    if ( redefining )
      v22 = aRedefining;
    else
      v22 = aDefining;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v22, v21);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)constructName, v23);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_505F78, v24);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(v25 + 16), v25);
    if ( fullMessageCR )
      v27 = asc_505E94;
    else
      v27 = asc_505F44;
    goto LABEL_15;
  }
  if ( Rules_GetLoadInProgress() )
  {
    v27 = constructSymbol;
LABEL_15:
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v27, v26);
  }
  Parser_NextToken(readSource, inputToken);
  if ( *(_DWORD *)inputToken == 3 && getComment )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F44);
    IO_OutWriteToken(*(char **)(inputToken + 8));
    Parser_NextToken(readSource, v29);
  }
  if ( *(_DWORD *)inputToken != 101 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F7C);
    IO_OutWriteToken(*(char **)(inputToken + 8));
  }
  return v28;
}
// 49C4B4: variable 'v18' is possibly undefined
// 49C4CB: variable 'v19' is possibly undefined
// 49C51B: variable 'v21' is possibly undefined
// 49C527: variable 'v23' is possibly undefined
// 49C536: variable 'v24' is possibly undefined
// 49C540: variable 'v25' is possibly undefined
// 49C55E: variable 'v26' is possibly undefined
// 49C593: variable 'v29' is possibly undefined
// 49C5B4: variable 'v28' is possibly undefined
// 49C5DD: variable 'v31' is possibly undefined
// 49C5E9: variable 'v32' is possibly undefined
// 49C5F8: variable 'v33' is possibly undefined
// 49C63A: variable 'v17' is possibly undefined
// 49C637: variable 'v16' is possibly undefined
// 49C667: variable 'v34' is possibly undefined
// 49C67B: variable 'v36' is possibly undefined
// 49C68A: variable 'v20' is possibly undefined
// 49C6EA: variable 'v37' is possibly undefined
// 49C6F6: variable 'v38' is possibly undefined
// 49C705: variable 'v39' is possibly undefined
// 49C70F: variable 'v40' is possibly undefined
// 49C721: variable 'v41' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];

//----- (0049C760) --------------------------------------------------------
int  Rules_UnlinkListNode(int theConstruct)
{
  int constructAddr; // ecx
  int currentItem; // eax
  int i; // ebx
  int result; // eax

  constructAddr = theConstruct;
  currentItem = *(_DWORD *)(*(_DWORD *)(theConstruct + 8) + 4);
  for ( i = 0; currentItem != constructAddr; currentItem = *(_DWORD *)(currentItem + 16) )
    i = currentItem;
  if ( !currentItem )
  {
    Rules_ReportSystemError(constructAddr, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( i )
  {
    *(_DWORD *)(i + 16) = *(_DWORD *)(constructAddr + 16);
    result = *(_DWORD *)(constructAddr + 8);
    if ( constructAddr != *(_DWORD *)(result + 8) )
      return result;
    goto LABEL_9;
  }
  *(_DWORD *)(*(_DWORD *)(constructAddr + 8) + 4) = *(_DWORD *)(constructAddr + 16);
  result = *(_DWORD *)(constructAddr + 8);
  if ( constructAddr == *(_DWORD *)(result + 8) )
LABEL_9:
    *(_DWORD *)(result + 8) = i;
  return result;
}
// 49C7A4: variable 'v1' is possibly undefined

//----- (0049C7D0) --------------------------------------------------------
signed int  Rules_ImportExportConflictMessage(int constructName, int itemName, int causedByConstruct)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  Rules_PrintErrorID((int)aCstrcpsr, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotDefine, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], constructName, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505F44, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], itemName, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBecauseOfAnImp, v9);
  if ( causedByConstruct )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedByThe, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], causedByConstruct, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505F44, v13);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v14, v14);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ConstructError, v10);
}
// 49C7F7: variable 'v5' is possibly undefined
// 49C803: variable 'v6' is possibly undefined
// 49C812: variable 'v7' is possibly undefined
// 49C81E: variable 'v8' is possibly undefined
// 49C82D: variable 'v9' is possibly undefined
// 49C853: variable 'v10' is possibly undefined
// 49C85F: variable 'v12' is possibly undefined
// 49C86E: variable 'v13' is possibly undefined
// 49C87A: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049C8A0) --------------------------------------------------------
signed int Rules_RegisterControlFlowFunctions()
{
  Rules_RegisterHostFunction(aIf, 117, (int)aIffunction, (int)Rules_IfFunction, 0);
  Rules_RegisterHostFunction(aWhile, 117, (int)aWhilefunction, (int)Rules_WhileFunction, 0);
  Rules_RegisterHostFunction(aLoopForCount, 117, (int)aLoopforcountfu, (int)Rules_LoopForCountFunction, 0);
  Rules_RegisterHostFunction(aGetLoopCount, 108, (int)aGetloopcount, (int)Rules_GetLoopCountFunction, 0);
  Rules_RegisterHostFunction(aBind, 117, (int)aBindfunction, (int)Rules_BindFunction, 0);
  Rules_RegisterHostFunction(aProgn, 117, (int)aPrognfunction, (int)Rules_PrognFunction, 0);
  Rules_RegisterHostFunction(aReturn, 117, (int)aReturnfunction, (int)Rules_ReturnFunction, 0);
  Rules_RegisterHostFunction(aBreak, 118, (int)aBreakfunction, (int)Rules_BreakFunction, 0);
  Rules_RegisterHostFunction(aSwitch, 117, (int)aSwitchfunction, (int)Rules_SwitchFunction, 0);
  Parser_RegisterProceduralFunctionParsers();
  Rules_SetFunctionSeqOverloadFlags(aProgn, 0);
  Rules_SetFunctionSeqOverloadFlags(aIf, 0);
  Rules_SetFunctionSeqOverloadFlags(aWhile, 0);
  Rules_SetFunctionSeqOverloadFlags(aLoopForCount, 0);
  Rules_SetFunctionSeqOverloadFlags(aReturn, 0);
  return Rules_SetFunctionSeqOverloadFlags(aSwitch, 0);
}
// 49CD20: using guessed type int sub_49CD20();
// 4BDD40: using guessed type int sub_4BDD40(void);

//----- (0049CA00) --------------------------------------------------------
int  Rules_WhileFunction(double context)
{
  _DWORD *returnValue; // ecx
  int result; // eax
  int theResult; // [esp+0h] [ebp-30h] BYREF
  int resultType; // [esp+4h] [ebp-2Ch]
  int resultValue; // [esp+8h] [ebp-28h]
  int resultBegin; // [esp+Ch] [ebp-24h]
  int resultEnd; // [esp+10h] [ebp-20h]

  ++g_ClipsCurrentEvaluationDepth;
  Rules_RtnUnknown(1, &theResult, context);
  while ( resultValue != g_ClipsFalseSymbol || resultType != 2 )
  {
    if ( g_ClipsHaltExecution == 1 )
      break;
    if ( g_ClipsBreakFlag == 1 )
      break;
    if ( g_ClipsHaltExecutionFlag == 1 )
      break;
    Rules_RtnUnknown(2, &theResult, context);
    --g_ClipsCurrentEvaluationDepth;
    Rules_RunPeriodicCleanup(0, 1);
    ++g_ClipsCurrentEvaluationDepth;
    if ( g_ClipsBreakFlag == 1 || g_ClipsHaltExecutionFlag == 1 )
      break;
    Rules_RtnUnknown(1, &theResult, context);
  }
  g_ClipsBreakFlag = 0;
  --g_ClipsCurrentEvaluationDepth;
  if ( g_ClipsHaltExecutionFlag == 1 )
  {
    returnValue[1] = resultType;
    returnValue[2] = resultValue;
    returnValue[3] = resultBegin;
    result = resultEnd;
    returnValue[4] = resultEnd;
  }
  else
  {
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  return result;
}
// 49CA6D: variable 'v1' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CB10) --------------------------------------------------------
int  Rules_LoopForCountFunction(_DWORD *returnValue, double context)
{
  _DWORD *freeListHead; // edx
  int *loopVarNode; // edi
  int *savedLoopVarNode; // esi
  int result; // eax
  int endCount; // ecx
  int nextCount; // edi
  _DWORD argData[2]; // [esp+0h] [ebp-30h] BYREF
  int argValue; // [esp+8h] [ebp-28h]
  int v11; // [esp+Ch] [ebp-24h]
  int v12; // [esp+10h] [ebp-20h]

  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListHead;
    loopVarNode = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    loopVarNode = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *loopVarNode = 0;
  savedLoopVarNode = loopVarNode;
  loopVarNode[1] = g_LoopForCountBindingStack;
  g_LoopForCountBindingStack = (int)loopVarNode;
  if ( Lexer_ParseValueList(1, argData, 1, context) )
  {
    *loopVarNode = *(_DWORD *)(argValue + 16);
    if ( Lexer_ParseValueList(2, argData, 1, context) )
    {
      if ( *(_DWORD *)(argValue + 16) >= *loopVarNode )
      {
        do
        {
          if ( g_ClipsHaltExecution == 1 )
            break;
          if ( g_ClipsBreakFlag == 1 )
            break;
          if ( g_ClipsHaltExecutionFlag == 1 )
            break;
          ++g_ClipsCurrentEvaluationDepth;
          Rules_RtnUnknown(3, argData, context);
          --g_ClipsCurrentEvaluationDepth;
          Rules_RunPeriodicCleanup(0, 1);
          if ( g_ClipsBreakFlag == 1 )
            break;
          if ( g_ClipsHaltExecutionFlag == 1 )
            break;
          nextCount = *savedLoopVarNode + 1;
          *savedLoopVarNode = nextCount;
        }
        while ( endCount >= nextCount );
      }
      g_ClipsBreakFlag = 0;
      if ( g_ClipsHaltExecutionFlag == 1 )
      {
        returnValue[1] = argData[1];
        returnValue[2] = argValue;
        returnValue[3] = v11;
        returnValue[4] = v12;
      }
      else
      {
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
      }
      g_LoopForCountBindingStack = savedLoopVarNode[1];
      g_ClipsMemFreeListTemp = (int)savedLoopVarNode;
      *savedLoopVarNode = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
      g_LoopForCountBindingStack = loopVarNode[1];
      g_ClipsMemFreeListTemp = (int)loopVarNode;
      *loopVarNode = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    g_LoopForCountBindingStack = loopVarNode[1];
    g_ClipsMemFreeListTemp = (int)loopVarNode;
    *loopVarNode = *(_DWORD *)(g_ClipsMemoryTable + 32);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 49CCFF: variable 'v7' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 51ACC8: using guessed type int dword_51ACC8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CD20) --------------------------------------------------------
int Rules_GetLoopCountFunction()
{
  int depth; // eax
  _DWORD *i; // edx

  depth = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = (_DWORD *)g_LoopForCountBindingStack; depth > 0; i = (_DWORD *)i[1] )
    --depth;
  return *i;
}
// 49CD20: using guessed type int sub_49CD20();
// 51A960: using guessed type int dword_51A960;
// 51ACC8: using guessed type int dword_51ACC8;

//----- (0049CD60) --------------------------------------------------------
int  Rules_IfFunction(double context)
{
  int result; // eax
  _DWORD *returnValue; // ecx
  int argCount; // ebx
  _DWORD *resultValue; // ecx

  result = Rules_ArgRangeCheck((int)aIf, 3);
  argCount = result;
  if ( result == -1 )
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    result = Rules_RtnUnknown(1, returnValue, context);
    if ( g_ClipsBreakFlag != 1 && g_ClipsHaltExecutionFlag != 1 )
    {
      if ( g_ClipsFalseSymbol == resultValue[2] && resultValue[1] == 2 && argCount == 3 )
      {
        return Rules_RtnUnknown(3, resultValue, context);
      }
      else if ( g_ClipsFalseSymbol == resultValue[2] && resultValue[1] == 2 )
      {
        resultValue[2] = g_ClipsFalseSymbol;
      }
      else
      {
        return Rules_RtnUnknown(2, resultValue, context);
      }
    }
  }
  return result;
}
// 49CD81: variable 'v2' is possibly undefined
// 49CDBA: variable 'v4' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CE10) --------------------------------------------------------
__int16 * Rules_BindFunction(_DWORD *returnValue, double context)
{
  int foundFlag; // ecx
  int firstArgExpr; // eax
  int unbindFlag; // ebp
  int variableSymbol; // esi
  int v7; // eax
  int valueExpr; // ebx
  _DWORD *prevBinding; // ebx
  _DWORD *currentBinding; // edx
  _DWORD *freeListHead; // edx
  _DWORD *newBinding; // eax
  _DWORD *theBinding; // edx
  __int16 *result; // eax
  __int16 *v15; // eax
  int theGlobal; // [esp+0h] [ebp-1Ch]

  foundFlag = 0;
  firstArgExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  unbindFlag = 0;
  variableSymbol = 0;
  theGlobal = 0;
  if ( *(_WORD *)firstArgExpr == 60 )
  {
    theGlobal = *(_DWORD *)(firstArgExpr + 2);
  }
  else
  {
    Parser_ParseForm((__int16 *)firstArgExpr, returnValue, 0, context);
    variableSymbol = returnValue[2];
  }
  v7 = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  valueExpr = *(_DWORD *)(v7 + 10);
  if ( valueExpr )
  {
    v15 = *(__int16 **)(v7 + 10);
    if ( *(_DWORD *)(valueExpr + 10) )
      Rules_StoreEvaluatedNodesAsMultifield(returnValue, (int)v15, 1, context);
    else
      Parser_ParseForm(v15, returnValue, foundFlag, context);
  }
  else
  {
    unbindFlag = 1;
  }
  prevBinding = (_DWORD *)theGlobal;
  if ( theGlobal )
    return (__int16 *)Defglobal_SetValue(theGlobal, returnValue, unbindFlag, context);
  currentBinding = (_DWORD *)g_BoundVariableList;
  if ( g_BoundVariableList )
  {
    do
    {
      if ( foundFlag )
        break;
      if ( variableSymbol == *currentBinding )
      {
        foundFlag = 1;
      }
      else
      {
        prevBinding = currentBinding;
        currentBinding = (_DWORD *)currentBinding[5];
      }
    }
    while ( currentBinding );
  }
  if ( foundFlag )
  {
    Rules_ValueDeinstall((int)currentBinding, foundFlag);
  }
  else
  {
    if ( unbindFlag )
    {
LABEL_21:
      returnValue[1] = 2;
      result = (__int16 *)g_ClipsFalseSymbol;
      returnValue[2] = g_ClipsFalseSymbol;
      return result;
    }
    freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListHead;
      newBinding = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newBinding = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    newBinding[5] = 0;
    theBinding = newBinding;
    *newBinding = variableSymbol;
    if ( prevBinding )
      prevBinding[5] = newBinding;
    else
      g_BoundVariableList = (int)newBinding;
  }
  if ( unbindFlag )
  {
    if ( prevBinding )
      prevBinding[5] = theBinding[5];
    else
      g_BoundVariableList = theBinding[5];
    g_ClipsMemFreeListTemp = (int)theBinding;
    *theBinding = *(_DWORD *)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    goto LABEL_21;
  }
  theBinding[1] = returnValue[1];
  theBinding[2] = returnValue[2];
  theBinding[3] = returnValue[3];
  theBinding[4] = returnValue[4];
  return Rules_ValueInstall((int)returnValue, foundFlag);
}
// 49CE6E: variable 'v3' is possibly undefined
// 49CECF: variable 'v13' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACCC: using guessed type int dword_51ACCC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CFD0) --------------------------------------------------------
signed int  Rules_FindBoundVariable(_DWORD *vPtr, int variableSymbol)
{
  _DWORD *bindEntry; // eax

  bindEntry = (_DWORD *)g_BoundVariableList;
  if ( !g_BoundVariableList )
    return 0;
  while ( variableSymbol != *bindEntry )
  {
    bindEntry = (_DWORD *)bindEntry[5];
    if ( !bindEntry )
      return 0;
  }
  vPtr[1] = bindEntry[1];
  vPtr[2] = bindEntry[2];
  vPtr[3] = bindEntry[3];
  vPtr[4] = bindEntry[4];
  return 1;
}
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D010) --------------------------------------------------------
int Rules_FreeBoundVariableEntry()
{
  int result; // eax
  int v1; // edx

  result = Rules_DeinstallValueChain(g_BoundVariableList);
  g_BoundVariableList = v1;
  return result;
}
// 49D01D: variable 'v1' is possibly undefined
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D030) --------------------------------------------------------
int  Rules_PrognFunction(_DWORD *returnValue, double context)
{
  int v3; // eax
  int argCount; // esi
  int v5; // ecx
  int v6; // ecx
  int result; // eax

  v3 = Rules_RtnArgCount();
  argCount = v3;
  if ( !v3 )
    goto LABEL_8;
  if ( v3 >= 1 )
  {
    do
    {
      if ( Rules_GetEvaluationErrorFlag() == 1 )
        break;
      Rules_RtnUnknown(v5, returnValue, context);
      if ( g_ClipsBreakFlag == 1 )
        break;
    }
    while ( g_ClipsHaltExecutionFlag != 1 && v6 + 1 <= argCount );
  }
  result = Rules_GetEvaluationErrorFlag();
  if ( result == 1 )
  {
LABEL_8:
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  return result;
}
// 49D058: variable 'v5' is possibly undefined
// 49D06F: variable 'v6' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0A0) --------------------------------------------------------
int  Rules_ReturnFunction(double context)
{
  _DWORD *returnValue; // edx
  int result; // eax

  if ( Rules_RtnArgCount() )
  {
    result = Rules_RtnUnknown(1, returnValue, context);
  }
  else
  {
    returnValue[1] = 105;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  g_ClipsHaltExecutionFlag = 1;
  return result;
}
// 49D0AC: variable 'v1' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0E0) --------------------------------------------------------
void Rules_BreakFunction()
{
  g_ClipsBreakFlag = 1;
}
// 51ACC4: using guessed type int dword_51ACC4;

//----- (0049D0F0) --------------------------------------------------------
int  Rules_SwitchFunction(_DWORD *returnValue, int a2, double context)
{
  int result; // eax
  int caseExpr; // ecx
  int caseData; // [esp-4h] [ebp-40h] BYREF
  int caseType; // [esp+0h] [ebp-3Ch]
  int caseValue; // [esp+4h] [ebp-38h]
  int switchData; // [esp+14h] [ebp-28h] BYREF
  int switchType; // [esp+18h] [ebp-24h]
  int switchValue; // [esp+1Ch] [ebp-20h]
  int v13; // [esp+34h] [ebp-8h]

  v13 = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &switchData, a2, context);
  if ( !g_ClipsEvaluationError )
  {
    caseExpr = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
    if ( caseExpr )
    {
      while ( *(_WORD *)caseExpr != 105 )
      {
        result = Parser_ParseForm((__int16 *)caseExpr, &caseData, caseExpr, context);
        if ( g_ClipsEvaluationError )
          return result;
        result = switchType;
        if ( switchType == caseType )
        {
          result = caseType == 4 ? Rules_MultifieldRangesEqual(&switchData, &caseData) : switchValue == caseValue;
          if ( result )
            break;
        }
        caseExpr = *(_DWORD *)(*(_DWORD *)(caseExpr + 10) + 10);
        if ( !caseExpr )
          return result;
      }
      return Parser_ParseForm(*(__int16 **)(caseExpr + 10), returnValue, caseExpr, context);
    }
  }
  return result;
}
// 49D16A: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D1A0) --------------------------------------------------------
signed int Rules_RegisterMiscFunctions()
{
  int v0; // ecx

  Rules_RegisterHostFunction(aGensym, 119, (int)aGensymfunction, (int)Rules_GensymFunction, (int)a00_5);
  Rules_RegisterHostFunction(aGensym_0, 119, (int)aGensymstarfunc, (int)Rules_GensymStarFunction, (int)a00_5);
  Rules_RegisterHostFunction(aSetgen, 108, (int)aSetgenfunction, (int)Rules_SetGenFunction, (int)a11i_1);
  Rules_RegisterHostFunction(aSystem, 118, (int)aGensystem, (int)Rules_SystemCommand, (int)a1K);
  Rules_RegisterHostFunction(aLength, 108, (int)aLengthfunction, (int)Rules_HostLength, (int)a11q);
  Rules_RegisterHostFunction(aLength_0, 108, (int)aLengthfunction, (int)Rules_HostLength, (int)a11q);
  Rules_RegisterHostFunction(aTime, 100, (int)aGentime, (int)Rules_TimeCommand, (int)a00_5);
  Rules_RegisterHostFunction(aRandom, 108, (int)aRandomfunction, (int)Rules_HostRandom, (int)a00_5);
  Rules_RegisterHostFunction(aSeed, 118, (int)aSeedfunction, (int)Rules_HostSeed, (int)a11i_1);
  Rules_RegisterHostFunction(aConserveMem, 118, (int)aConservememcom, (int)Rules_HostConserveMem, (int)a11w_6);
  Rules_RegisterHostFunction(aReleaseMem, 108, (int)aReleasememcomm, (int)Rules_HostReleaseMem, (int)a00_5);
  Rules_RegisterHostFunction(aMemUsed, 108, (int)aMemusedcommand, (int)Rules_HostMemUsed, (int)a00_5);
  Rules_RegisterHostFunction(aMemRequests, 108, (int)aMemrequestscom, (int)Rules_HostMemRequests, (int)a00_5);
  Rules_RegisterHostFunction(aOptions, 118, (int)aOptionscommand, (int)Rules_HostOptionsCommand, (int)a00_5);
  Rules_RegisterHostFunction(aExpansionCall, 117, (int)aExpandfunccall, (int)Rules_HostExpansionCall, 0);
  Rules_RegisterHostFunction(aExpand, 117, (int)aDummyexpandfun, (int)Rules_HostExpandDummy, (int)a11m);
  Rules_SetFunctionSeqOverloadFlags(aExpand, 0);
  Rules_RegisterHostFunction(aSetEvaluationE, 119, v0, (int)Rules_HostSetEvaluationError, 0);
  Rules_RegisterHostFunction(aSetSequenceOpe, 98, (int)aSetsorcommand, (int)Rules_HostSetSequenceOperatorRecognition, (int)a11w_6);
  Rules_RegisterHostFunction(aGetSequenceOpe, 98, (int)aGetsequenceope, (int)Parser_GetSequenceOperatorRecognition, (int)a00_5);
  Rules_RegisterHostFunction(aGetFunctionRes, 115, (int)aGetfunctionres, (int)Rules_HostGetFunctionRestrictions, (int)a11w_6);
  Rules_RegisterHostFunction(aCreate, 109, (int)aCreatefunction, (int)Rules_CreateMultifieldFunction, 0);
  Rules_RegisterHostFunction(aMvAppend, 109, (int)aCreatefunction, (int)Rules_CreateMultifieldFunction, 0);
  return Rules_RegisterHostFunction(aApropos, 118, (int)aAproposcommand, (int)Rules_HostApropos, (int)a11w_6);
}
// 49D3A4: variable 'v0' is possibly undefined
// 49E070: using guessed type int sub_49E070();

//----- (0049D460) --------------------------------------------------------
_DWORD * Rules_CreateMultifieldFunction(_DWORD *returnValue, double context)
{
  return Rules_StoreEvaluatedNodesAsMultifield(returnValue, *(_DWORD *)(g_ClipsCurrentExpression + 6), 1, context);
}
// 51A960: using guessed type int dword_51A960;

//----- (0049D480) --------------------------------------------------------
signed int  Rules_SetGenFunction(int a1, double context)
{
  signed int result; // eax
  int argData; // [esp-8h] [ebp-24h] BYREF
  int argValue; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-8h]

  v5 = a1;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &argData, 1, context) )
    return g_ClipsGensymCounter;
  result = *(_DWORD *)(argValue + 16);
  if ( result < 1 )
  {
    Parser_ReportError(1, (int)aNumberGreaterT);
    return g_ClipsGensymCounter;
  }
  else
  {
    g_ClipsGensymCounter = *(_DWORD *)(argValue + 16);
  }
  return result;
}
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D500) --------------------------------------------------------
signed int *__fastcall Rules_GensymFunction(int a1, int a2)
{
  char symbolBuffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v4; // [esp+14h] [ebp-8h]

  v4 = a1;
  Lexer_TokenExpect(0);
  sprintf_(symbolBuffer, "gen%ld", g_ClipsGensymCounter);
  return Str_Intern(symbolBuffer, ++g_ClipsGensymCounter);
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D550) --------------------------------------------------------
signed int *__thiscall Rules_GensymStarFunction(void *this)
{
  int v1; // ecx
  char symbolBuffer[20]; // [esp+0h] [ebp-18h] BYREF
  void *v4; // [esp+14h] [ebp-4h]

  v4 = this;
  Lexer_TokenExpect(0);
  do
  {
    sprintf_(symbolBuffer, "gen%ld", g_ClipsGensymCounter);
    ++g_ClipsGensymCounter;
  }
  while ( Rules_FindSymbolEntry(symbolBuffer) );
  return Str_Intern(symbolBuffer, v1);
}
// 49D598: variable 'v1' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D5B0) --------------------------------------------------------
int Rules_HostRandom()
{
  Lexer_TokenExpect(0);
  return j_rand_();
}
// 47D520: using guessed type int j_rand_(void);

//----- (0049D5D0) --------------------------------------------------------
int  Rules_HostSeed(int a1, double context)
{
  int result; // eax
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, argData, 1, context);
    if ( result )
      return j_srand_();
  }
  return result;
}
// 47D530: using guessed type int j_srand_(void);

//----- (0049D620) --------------------------------------------------------
int  Rules_HostLength(double context)
{
  int result; // eax
  int v2; // edx
  int argData; // [esp-4h] [ebp-20h] BYREF
  int argType; // [esp+0h] [ebp-1Ch]
  int argValue; // [esp+4h] [ebp-18h]
  int rangeBegin; // [esp+8h] [ebp-14h]
  int rangeEnd; // [esp+Ch] [ebp-10h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, &argData, context);
    if ( argType == 3 || argType == 2 )
    {
      return strlen(*(const char **)(argValue + 16));
    }
    else if ( argType == 4 )
    {
      return rangeEnd - rangeBegin + 1;
    }
    else
    {
      Lexer_ErrorRecover(1);
      Rules_ReportSymbolTypeError(aLength_0, v2);
      return -1;
    }
  }
  return result;
}
// 49D6A0: variable 'v2' is possibly undefined

//----- (0049D6B0) --------------------------------------------------------
int Rules_HostReleaseMem()
{
  int v0; // ecx

  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_PurgeFreeListsForSpace(-1, 0, v0);
}
// 49D6D1: variable 'v0' is possibly undefined

//----- (0049D6E0) --------------------------------------------------------
int  Rules_HostConserveMem(int a1, double context)
{
  int result; // eax
  int v3; // edx
  int v4; // ecx
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, argData, 2, context);
    if ( result )
    {
      if ( !strcmp_(*(_DWORD *)(argData[2] + 16), aOn_0) || !strcmp_(v4, aOff_0) )
        return Mem_SetAllocFlag(v4, v3);
      else
        return Parser_ReportError(1, (int)aSymbolWithVa_2);
    }
  }
  return result;
}
// 49D73B: variable 'v4' is possibly undefined
// 49D744: variable 'v3' is possibly undefined
// 472B00: using guessed type int __fastcall unknown_libname_5(_DWORD, _DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0049D780) --------------------------------------------------------
int Rules_HostMemUsed()
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_GetTotalAllocatedBytes();
}

//----- (0049D7B0) --------------------------------------------------------
int Rules_HostMemRequests()
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Mem_GetTotalAllocationCount();
}

//----- (0049D7E0) --------------------------------------------------------
int ** Rules_HostApropos(double context)
{
  int **result; // eax
  int ***symbolEntry; // esi
  char *searchString; // ebp
  unsigned int searchLength; // kr04_4
  int v5; // ecx
  int v6; // ecx
  _DWORD argData[12]; // [esp+0h] [ebp-30h] BYREF

  result = (int **)Lexer_TokenExpect(1);
  symbolEntry = 0;
  if ( result != (int **)-1 )
  {
    result = (int **)Lexer_ParseValueList(1, argData, 2, context);
    if ( result )
    {
      searchString = *(char **)(argData[2] + 16);
      searchLength = strlen(searchString) + 1;
      while ( 1 )
      {
        result = Rules_GetNextSymbolMatch((int **)searchString, searchLength - 1, 1, symbolEntry, 0);
        symbolEntry = (int ***)result;
        if ( !result )
          break;
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)result[4], v5);
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5063E0, v6);
      }
    }
  }
  return result;
}
// 49D85A: variable 'v5' is possibly undefined
// 49D869: variable 'v6' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0049D870) --------------------------------------------------------
int Rules_HostOptionsCommand()
{
  int result; // eax
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // ecx
  int v35; // ecx
  int v36; // ecx
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int v44; // ecx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  int v48; // ecx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  int v52; // ecx
  int v53; // ecx
  int v54; // ecx
  int v55; // ecx
  int v56; // ecx
  int v57; // ecx
  int v58; // ecx
  int v59; // ecx
  int v60; // ecx
  int v61; // ecx
  int v62; // ecx
  int v63; // ecx
  int v64; // ecx
  int v65; // ecx
  int v66; // ecx
  int v67; // ecx
  int v68; // ecx
  int v69; // ecx
  int v70; // ecx
  int v71; // ecx
  int v72; // ecx
  int v73; // ecx
  int v74; // ecx
  int v75; // ecx
  int v76; // ecx
  int v77; // ecx
  int v78; // ecx

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
  {
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aMachineType, v1);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aUnixSystemIiiV, v2);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5063E0, v3);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aAnsiCompilerIs, v4);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v5);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDefruleConstru, v6);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v7);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aConflictResolu, v8);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v9);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDynamicSalienc, v10);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v11);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aIncrementalRes, v12);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v13);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aLogicalDepende, v14);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v15);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDefmoduleConst, v16);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v17);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDeftemplateCon, v18);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v19);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDeffactsConstr, v20);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v21);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDefglobalConst, v22);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v23);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDeffunctionCon, v24);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v25);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDefgenericDefm, v26);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v27);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aImperativeMeth, v28);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v29);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aObjectSystemIs, v30);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v31);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDefinstancesCo, v32);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v33);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aImperativeArou, v34);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v35);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aAuxiliaryBefor, v36);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v37);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aInstanceSetQue, v38);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v39);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDirectPatternM, v40);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v41);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBinaryLoadingO, v42);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v43);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBinarySavingOf, v44);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v45);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aExtendedMathPa, v46);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v47);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aTextProcessing, v48);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v49);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aHelpSystemIs, v50);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v51);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBloadCapabilit, v52);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBloadAndBsave, v53);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5063E0, v54);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aEmacsEditorIs, v55);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOff_1, v56);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aConstructCompi, v57);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v58);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBasicIOIs, v59);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v60);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aExtendedIOIs, v61);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v62);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aStringFunction, v63);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v64);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aMultifieldFunc, v65);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v66);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDebuggingFunct, v67);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v68);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aBlockMemoryIs, v69);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOn_1, v70);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aWindowInterfac, v71);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOff_1, v72);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aShortLinkNames, v73);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOff_1, v74);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aDeveloperFlagI, v75);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOff_1, v76);
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aRunTimeModuleI, v77);
    return Output_Write((int)g_IO_LogicalName_WDisplay, (int)aOff_1, v78);
  }
  return result;
}
// 49D892: variable 'v1' is possibly undefined
// 49D8A1: variable 'v2' is possibly undefined
// 49D8B0: variable 'v3' is possibly undefined
// 49D8BF: variable 'v4' is possibly undefined
// 49D8CE: variable 'v5' is possibly undefined
// 49D8DD: variable 'v6' is possibly undefined
// 49D8EC: variable 'v7' is possibly undefined
// 49D8FB: variable 'v8' is possibly undefined
// 49D90A: variable 'v9' is possibly undefined
// 49D919: variable 'v10' is possibly undefined
// 49D928: variable 'v11' is possibly undefined
// 49D937: variable 'v12' is possibly undefined
// 49D946: variable 'v13' is possibly undefined
// 49D955: variable 'v14' is possibly undefined
// 49D964: variable 'v15' is possibly undefined
// 49D973: variable 'v16' is possibly undefined
// 49D982: variable 'v17' is possibly undefined
// 49D991: variable 'v18' is possibly undefined
// 49D9A0: variable 'v19' is possibly undefined
// 49D9AF: variable 'v20' is possibly undefined
// 49D9BE: variable 'v21' is possibly undefined
// 49D9CD: variable 'v22' is possibly undefined
// 49D9DC: variable 'v23' is possibly undefined
// 49D9EB: variable 'v24' is possibly undefined
// 49D9FA: variable 'v25' is possibly undefined
// 49DA09: variable 'v26' is possibly undefined
// 49DA18: variable 'v27' is possibly undefined
// 49DA27: variable 'v28' is possibly undefined
// 49DA36: variable 'v29' is possibly undefined
// 49DA45: variable 'v30' is possibly undefined
// 49DA54: variable 'v31' is possibly undefined
// 49DA63: variable 'v32' is possibly undefined
// 49DA72: variable 'v33' is possibly undefined
// 49DA81: variable 'v34' is possibly undefined
// 49DA90: variable 'v35' is possibly undefined
// 49DA9F: variable 'v36' is possibly undefined
// 49DAAE: variable 'v37' is possibly undefined
// 49DABD: variable 'v38' is possibly undefined
// 49DACC: variable 'v39' is possibly undefined
// 49DADB: variable 'v40' is possibly undefined
// 49DAEA: variable 'v41' is possibly undefined
// 49DAF9: variable 'v42' is possibly undefined
// 49DB08: variable 'v43' is possibly undefined
// 49DB17: variable 'v44' is possibly undefined
// 49DB26: variable 'v45' is possibly undefined
// 49DB35: variable 'v46' is possibly undefined
// 49DB44: variable 'v47' is possibly undefined
// 49DB53: variable 'v48' is possibly undefined
// 49DB62: variable 'v49' is possibly undefined
// 49DB71: variable 'v50' is possibly undefined
// 49DB80: variable 'v51' is possibly undefined
// 49DB8F: variable 'v52' is possibly undefined
// 49DB9E: variable 'v53' is possibly undefined
// 49DBAD: variable 'v54' is possibly undefined
// 49DBBC: variable 'v55' is possibly undefined
// 49DBCB: variable 'v56' is possibly undefined
// 49DBDA: variable 'v57' is possibly undefined
// 49DBE9: variable 'v58' is possibly undefined
// 49DBF8: variable 'v59' is possibly undefined
// 49DC07: variable 'v60' is possibly undefined
// 49DC16: variable 'v61' is possibly undefined
// 49DC25: variable 'v62' is possibly undefined
// 49DC34: variable 'v63' is possibly undefined
// 49DC43: variable 'v64' is possibly undefined
// 49DC52: variable 'v65' is possibly undefined
// 49DC61: variable 'v66' is possibly undefined
// 49DC70: variable 'v67' is possibly undefined
// 49DC7F: variable 'v68' is possibly undefined
// 49DC8E: variable 'v69' is possibly undefined
// 49DC9D: variable 'v70' is possibly undefined
// 49DCAC: variable 'v71' is possibly undefined
// 49DCBB: variable 'v72' is possibly undefined
// 49DCCA: variable 'v73' is possibly undefined
// 49DCD9: variable 'v74' is possibly undefined
// 49DCE8: variable 'v75' is possibly undefined
// 49DCF7: variable 'v76' is possibly undefined
// 49DD06: variable 'v77' is possibly undefined
// 49DD15: variable 'v78' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0049DD20) --------------------------------------------------------
int  Rules_HostExpansionCall(int returnValue, double context)
{
  int **Symbol; // eax
  _DWORD *freeListHead; // edx
  signed int newExpr; // ecx
  int v6; // eax
  __int16 *exprNode; // edi
  _DWORD *argList; // eax
  __int16 exprType; // dx
  int v10; // eax
  int v11; // ecx
  int theFunction; // ebx
  int argCount; // eax
  int v15[7]; // [esp+0h] [ebp-1Ch] BYREF

  v15[0] = AST_CloneNodeList(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 6));
  Symbol = Rules_MakeSymbol(aExpand);
  Rules_ExpandFuncCallForm((int **)returnValue, (_DWORD *)v15[0], (int)Symbol, v15, context);
  freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 56);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListHead;
    newExpr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_WORD *)newExpr = **(_WORD **)(g_ClipsCurrentExpression + 6);
  v6 = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2);
  *(_DWORD *)(newExpr + 10) = 0;
  *(_DWORD *)(newExpr + 2) = v6;
  exprNode = (__int16 *)newExpr;
  argList = (_DWORD *)v15[0];
  exprType = *(_WORD *)newExpr;
  *(_DWORD *)(newExpr + 6) = v15[0];
  if ( exprType == 10 )
  {
    theFunction = *(_DWORD *)(newExpr + 2);
    argCount = AST_CountListNodes((int)argList);
    if ( !Rules_CheckFunctionArgCount(*(_DWORD *)(*(_DWORD *)theFunction + 16), *(_BYTE **)(theFunction + 17), argCount) )
    {
      *(_DWORD *)(returnValue + 4) = 2;
      *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
      return AST_Free(newExpr);
    }
  }
  else if ( exprType == 12 )
  {
    v10 = AST_CountListNodes((int)argList);
    if ( !Deffunction_CheckArgumentCount(*(_DWORD *)(v11 + 2), v10) )
    {
      *(_DWORD *)(returnValue + 4) = 2;
      *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
      AST_Free(newExpr);
      return Lexer_ErrorRecover(1);
    }
  }
  Parser_ParseForm(exprNode, (_DWORD *)returnValue, newExpr, context);
  return AST_Free((int)exprNode);
}
// 49DDBA: variable 'v11' is possibly undefined
// 49DDDB: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DE60) --------------------------------------------------------
signed int  Rules_HostExpandDummy(int returnValue)
{
  int v1; // edx
  int v2; // ecx

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  Lexer_ErrorRecover(1);
  Rules_PrintErrorID((int)aMiscfun, v1, 0);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpandMustBeUs, v2);
}
// 49DE88: variable 'v1' is possibly undefined
// 49DE97: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DEA0) --------------------------------------------------------
int ** Rules_ExpandFuncCallForm(int **result, _DWORD *theExp, int expandFuncSymbol, int *stoPtr, double context)
{
  int **returnValue; // edi
  _DWORD *exprCursor; // esi
  int fieldOffset; // edx
  _DWORD *freeListHead; // ebx
  signed int newNode; // eax
  int fieldValue; // ebx
  int v12; // [esp+4h] [ebp-18h]
  int newListHead; // [esp+8h] [ebp-14h]
  int lastNode; // [esp+Ch] [ebp-10h]

  returnValue = result;
  exprCursor = theExp;
  v12 = expandFuncSymbol;
  if ( theExp )
  {
    while ( 1 )
    {
      while ( v12 != *(_DWORD *)((char *)exprCursor + 2) )
      {
        expandFuncSymbol = *(_DWORD *)((char *)exprCursor + 6);
        if ( expandFuncSymbol )
          Rules_ExpandFuncCallForm((int)returnValue, *(_DWORD *)((char *)exprCursor + 6), v12, (int)exprCursor + 6, context);
        result = (int **)((char *)exprCursor + 10);
        stoPtr = (_DWORD *)((char *)exprCursor + 10);
        exprCursor = *(_DWORD **)((char *)exprCursor + 10);
        if ( !exprCursor )
          return result;
      }
      Parser_ParseForm(*(__int16 **)((char *)exprCursor + 6), returnValue, expandFuncSymbol, context);
      AST_Free(*(_DWORD *)((char *)exprCursor + 6));
      if ( g_ClipsEvaluationError || returnValue[1] != (int *)4 )
        break;
      expandFuncSymbol = (int)returnValue[3] + 1;
      lastNode = g_ClipsEvaluationError;
      newListHead = g_ClipsEvaluationError;
      fieldOffset = 6 * expandFuncSymbol - 6;
      while ( expandFuncSymbol <= (int)returnValue[4] + 1 )
      {
        freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 56);
        if ( freeListHead )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListHead;
          newNode = g_ClipsMemFreeListTemp;
        }
        else
        {
          newNode = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_WORD *)newNode = *(_WORD *)((char *)returnValue[2] + fieldOffset + 14);
        fieldValue = *(int *)((char *)returnValue[2] + fieldOffset + 16);
        *(_DWORD *)(newNode + 6) = 0;
        *(_DWORD *)(newNode + 2) = fieldValue;
        *(_DWORD *)(newNode + 10) = 0;
        if ( newListHead )
          *(_DWORD *)(lastNode + 10) = newNode;
        else
          newListHead = newNode;
        lastNode = newNode;
        fieldOffset += 6;
        ++expandFuncSymbol;
      }
      if ( newListHead )
      {
        *(_DWORD *)(lastNode + 10) = *(_DWORD *)((char *)exprCursor + 10);
        *stoPtr = newListHead;
        g_ClipsMemFreeListTemp = (int)exprCursor;
        *exprCursor = *(_DWORD *)(g_ClipsMemoryTable + 56);
        *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
        result = (int **)(lastNode + 10);
        exprCursor = *(_DWORD **)(lastNode + 10);
        stoPtr = (int *)(lastNode + 10);
        if ( !exprCursor )
          return result;
      }
      else
      {
        *stoPtr = *(_DWORD *)((char *)exprCursor + 10);
        g_ClipsMemFreeListTemp = (int)exprCursor;
        *exprCursor = *(_DWORD *)(g_ClipsMemoryTable + 56);
        result = (int **)g_ClipsMemoryTable;
        *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
        exprCursor = (_DWORD *)*stoPtr;
        if ( !*stoPtr )
          return result;
      }
    }
    *(_DWORD *)((char *)exprCursor + 6) = 0;
    if ( !g_ClipsEvaluationError && returnValue[1] != (int *)4 )
      Rules_ReportSymbolTypeError(aExpand, 1);
    result = Rules_MakeSymbol(aSetEvaluationE);
    *(_DWORD *)((char *)exprCursor + 2) = result;
    g_ClipsEvaluationError = 0;
    g_ClipsHaltExecution = 0;
  }
  return result;
}
// 49DEEE: variable 'a3' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049E070) --------------------------------------------------------
int Rules_HostSetEvaluationError()
{
  Lexer_ErrorRecover(1);
  return g_ClipsFalseSymbol;
}
// 49E070: using guessed type int sub_49E070();
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E080) --------------------------------------------------------
int  Rules_HostSetSequenceOperatorRecognition(int a1, double context)
{
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = a1;
  if ( Lexer_ParseValueList(1, argData, 2, context) )
    return Parser_SetSequenceOperatorRecognition(argData[2] != g_ClipsFalseSymbol);
  else
    return g_SequenceOperatorRecognition;
}
// 51B360: using guessed type int dword_51B360;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E0D0) --------------------------------------------------------
signed int * Rules_HostGetFunctionRestrictions(int a1, double context)
{
  int v3; // ecx
  int **Symbol; // eax
  char *restrictionString; // eax
  int argData; // [esp-8h] [ebp-24h] BYREF
  int argValue; // [esp+0h] [ebp-1Ch]
  int v9; // [esp+14h] [ebp-8h]

  v9 = a1;
  if ( !Lexer_ParseValueList(1, &argData, 2, context) )
  {
    restrictionString = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(restrictionString, v3);
  }
  Symbol = Rules_MakeSymbol(*(_BYTE **)(argValue + 16));
  if ( !Symbol )
  {
    Rules_ReportCantFindItem(v3, *(_DWORD *)(argValue + 16));
    Lexer_ErrorRecover(1);
    restrictionString = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(restrictionString, v3);
  }
  if ( !*(int **)((char *)Symbol + 17) )
  {
    restrictionString = a0_0;
    return Str_Intern(restrictionString, v3);
  }
  return Str_Intern(*(char **)((char *)Symbol + 17), v3);
}
// 49E10C: variable 'v3' is possibly undefined

//----- (0049E150) --------------------------------------------------------
signed int Rules_RegisterIOHostFunctions()
{
  Rules_RegisterHostFunction(aPrintout, 118, (int)aPrintoutfuncti, (int)Rules_HostPrintout, (int)a1_0);
  Rules_RegisterHostFunction(aRead, 117, (int)aReadfunction, (int)Rules_HostRead, (int)a1);
  Rules_RegisterHostFunction(aOpen, 98, (int)aOpenfunction, (int)Rules_HostOpen, (int)a23K);
  Rules_RegisterHostFunction(aClose, 98, (int)aClosefunction, (int)Rules_HostClose, (int)a1);
  Rules_RegisterHostFunction(aRemove, 98, (int)aRemovefunction, (int)Rules_HostRemoveFile, (int)a11k_0);
  Rules_RegisterHostFunction(aRename, 98, (int)aRenamefunction, (int)Rules_HostRenameFile, (int)a22k);
  Rules_RegisterHostFunction(aFormat, 115, (int)aFormatfunction, (int)Rules_HostFormat, (int)a2Us);
  return Rules_RegisterHostFunction(aReadline, 107, (int)aReadlinefuncti, (int)Rules_HostReadline, (int)a1);
}

//----- (0049E250) --------------------------------------------------------
int  Rules_HostPrintout(int a1, double context)
{
  int result; // eax
  int v3; // ecx
  int argCount; // edi
  int v5; // esi
  int argIndex; // ebx
  int v7; // ecx
  char *outputString; // edx
  int v9; // eax
  int logical_name; // ecx
  int argData; // [esp-4h] [ebp-2Ch] BYREF
  unsigned int argType; // [esp+0h] [ebp-28h]
  int argValue; // [esp+4h] [ebp-24h]
  int v13; // [esp+20h] [ebp-8h]

  v13 = a1;
  result = Lexer_TokenExpect(1);
  argCount = result;
  v5 = result;
  if ( result != -1 )
  {
    logical_name = Rules_GetLogicalNameArg(1, (int)aStdout_0, v3, context);
    if ( !logical_name )
    {
      Rules_ReportIllegalLogicalName();
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    result = IO_QueryRouters(logical_name);
    if ( !result )
      return IO_ReportUnrecognizedRouter(logical_name);
    argIndex = 2;
    if ( argCount >= 2 )
    {
      while ( 1 )
      {
        result = Rules_RtnUnknown(argIndex, &argData, context);
        if ( g_ClipsHaltExecution )
          return result;
        if ( argType < 2 )
          goto LABEL_26;
        if ( argType > 2 )
        {
          if ( argType == 3 )
            goto LABEL_17;
LABEL_26:
          result = Rules_PrintDataObject(v7, (int)&argData);
          if ( ++argIndex > v5 )
            return result;
        }
        else
        {
          if ( strcmp_(v7, aCrlf) )
          {
            if ( !strcmp_(v7, aTab) )
            {
              outputString = asc_5069C0;
              goto LABEL_11;
            }
            if ( !strcmp_(v7, aVtab) )
            {
              outputString = asc_5069CC;
              goto LABEL_11;
            }
            if ( !strcmp_(v7, aFf) )
            {
              outputString = (char *)&g_Rules_PrintoutFormFeedChar;
              goto LABEL_11;
            }
            if ( strcmp_(v7, &g_Rules_PrintoutCrlfAliasName) )
            {
LABEL_17:
              v9 = v7;
              outputString = *(char **)(argValue + 16);
              goto LABEL_12;
            }
          }
          outputString = asc_5069B8;
LABEL_11:
          v9 = v7;
LABEL_12:
          result = Output_Write(logical_name, (int)outputString, v7);
          if ( ++argIndex > v5 )
            return result;
        }
      }
    }
  }
  return result;
}
// 49E285: variable 'v3' is possibly undefined
// 49E2D5: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A968: using guessed type int dword_51A968;

//----- (0049E3E0) --------------------------------------------------------
signed int * Rules_HostRead(int a1, double context)
{
  int argCount; // eax
  int v4; // ecx
  char *logicalName; // esi
  int v6; // ecx
  unsigned int v7; // ecx
  int tokenType; // eax
  signed int *result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int theToken; // [esp+0h] [ebp-1Ch] BYREF
  signed int *tokenValue; // [esp+4h] [ebp-18h]
  char *tokenString; // [esp+8h] [ebp-14h]
  int v16; // [esp+14h] [ebp-8h]

  v16 = a1;
  argCount = Lexer_TokenExpect(1);
  logicalName = 0;
  if ( argCount == -1 )
    goto LABEL_14;
  if ( argCount )
  {
    if ( argCount == 1 )
    {
      logicalName = (char *)Rules_GetLogicalNameArg(1, (int)aStdin, v4, context);
      if ( !logicalName )
      {
        Rules_ReportIllegalLogicalName();
        Rules_SetEvaluationErrorFlag(1);
        Lexer_ErrorRecover(1);
        goto LABEL_14;
      }
    }
  }
  else
  {
    logicalName = aStdin;
  }
  if ( !IO_QueryRouters((int)logicalName) )
  {
    IO_ReportUnrecognizedRouter((int)logicalName);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    goto LABEL_14;
  }
  if ( !strcmp_(v6, aStdin) )
    Rules_ReadStdinLineToken(&theToken, v7);
  else
    Parser_NextToken((int)logicalName, (int)&theToken);
  tokenType = theToken;
  g_Lexer_PendingLineCharIndex = -1;
  *(_DWORD *)(v4 + 4) = theToken;
  switch ( tokenType )
  {
    case 0:
    case 3:
    case 8:
    case 2:
    case 1:
      result = tokenValue;
      *(_DWORD *)(v4 + 8) = tokenValue;
      break;
    case 102:
      *(_DWORD *)(v4 + 4) = 2;
      result = Str_Intern(aEof, v4);
      *(_DWORD *)(v11 + 8) = result;
      break;
    case 103:
LABEL_14:
      *(_DWORD *)(v4 + 4) = 3;
      result = Str_Intern(aReadError, v4);
      *(_DWORD *)(v10 + 8) = result;
      return result;
    default:
      *(_DWORD *)(v4 + 4) = 3;
      result = Str_Intern(tokenString, v4);
      *(_DWORD *)(v12 + 8) = result;
      break;
  }
  return result;
}
// 49E42B: variable 'v6' is possibly undefined
// 49E43A: variable 'v7' is possibly undefined
// 49E44D: variable 'v4' is possibly undefined
// 49E49F: variable 'v10' is possibly undefined
// 49E532: variable 'v11' is possibly undefined
// 49E54D: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A628: using guessed type int dword_51A628;

//----- (0049E560) --------------------------------------------------------
signed int * Rules_ReadStdinLineToken(_DWORD *theToken, unsigned int a2)
{
  char *appended; // edi
  int i; // esi
  unsigned int v5; // ecx
  signed int *result; // eax
  unsigned int bufferSize[7]; // [esp+0h] [ebp-1Ch] BYREF

  *theToken = 102;
  do
  {
    appended = 0;
    g_Lexer_PendingLineCharIndex = 0;
    bufferSize[0] = 0;
    for ( i = Lexer_PeekChar((int)aStdin, a2); i != 10; i = Lexer_PeekChar((int)aStdin, v5) )
    {
      if ( i == 13 )
        break;
      if ( i == -1 )
        break;
      if ( Rules_GetEvaluationErrorFlag() )
        break;
      appended = Str_AppendCharEscaping(i, appended, bufferSize, &g_Lexer_PendingLineCharIndex, bufferSize[0] + 80);
    }
    IO_OpenStringSource((int)aRead, appended, 0);
    Parser_NextToken((int)aRead, (int)theToken);
    IO_CloseStringRouter((int)aRead);
    if ( (int)bufferSize[0] > 0 )
      Mem_SmallBlockFree(appended, bufferSize[0]);
    result = (signed int *)Rules_GetEvaluationErrorFlag();
    if ( result )
    {
      *theToken = 3;
      result = Str_Intern(aReadError, a2);
      theToken[1] = result;
    }
    if ( *theToken == 102 && i == -1 )
    {
      *theToken = 2;
      result = Str_Intern(aEof, a2);
      theToken[1] = result;
    }
  }
  while ( *theToken == 102 );
  return result;
}
// 49E581: variable 'a2' is possibly undefined
// 49E5BE: variable 'v5' is possibly undefined
// 51A628: using guessed type int dword_51A628;

//----- (0049E650) --------------------------------------------------------
const CHAR * Rules_HostOpen(double context)
{
  int argCount; // ebx
  const CHAR *result; // eax
  int v3; // ecx
  const CHAR *fileName; // edi
  const char *logicalName; // esi
  char *accessMode; // ecx
  unsigned __int8 *v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  _DWORD argData[12]; // [esp+0h] [ebp-30h] BYREF

  argCount = Rules_ArgRangeCheck((int)aOpen, 3);
  if ( argCount == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, 0, context);
  fileName = result;
  if ( result )
  {
    logicalName = (const char *)Rules_GetLogicalNameArg(2, 0, v3, context);
    if ( !logicalName )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_ReportIllegalLogicalName();
      return 0;
    }
    if ( ismbdprint_((void *)logicalName) )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_PrintErrorID((int)aIofun, v9, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLogicalName_0, v10);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)logicalName, v11);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAlreadyInUse_, v12);
      return 0;
    }
    if ( argCount == 2 )
    {
      accessMode = aR_3;
    }
    else if ( argCount == 3 )
    {
      result = (const CHAR *)Lexer_ParseValueList(3, argData, 3, context);
      if ( !result )
        return result;
      accessMode = *(char **)(argData[2] + 16);
    }
    if ( !strcmp_(accessMode, aR_3) || !strcmp_(v7, aR_4) || !strcmp_(v7, aW_4) || !strcmp_(v7, aA_2) )
    {
      return (const CHAR *)IO_OpenNamedFile(fileName, v7, (int)v7, logicalName, (DWORD)logicalName);
    }
    else
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Parser_ReportError(v8, (int)aStringWithValu);
      return 0;
    }
  }
  return result;
}
// 49E69E: variable 'v3' is possibly undefined
// 49E6D1: variable 'v6' is possibly undefined
// 49E6E5: variable 'v7' is possibly undefined
// 49E73D: variable 'v8' is possibly undefined
// 49E798: variable 'v9' is possibly undefined
// 49E7A7: variable 'v10' is possibly undefined
// 49E7B3: variable 'v11' is possibly undefined
// 49E7C2: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (0049E820) --------------------------------------------------------
signed int  Rules_HostClose(double context)
{
  int argCount; // eax
  void *v2; // ecx
  int logicalName; // eax

  argCount = Lexer_TokenExpect(1);
  if ( argCount == -1 )
    return 0;
  if ( !argCount )
    return IO_CloseAllNamedFiles(v2);
  logicalName = Rules_GetLogicalNameArg(1, 0, (int)v2, context);
  if ( !logicalName )
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return IO_CloseNamedFile(logicalName);
}
// 49E846: variable 'v2' is possibly undefined

//----- (0049E890) --------------------------------------------------------
int  Rules_HostRemoveFile(double context)
{
  int v1; // ecx
  int result; // eax
  int v3; // edx
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v1, context);
  if ( result )
    return Rules_BloadDeleteFile(v4, v3);
  return result;
}
// 49E8B7: variable 'v1' is possibly undefined
// 49E8C0: variable 'v4' is possibly undefined
// 49E8C0: variable 'v3' is possibly undefined

//----- (0049E8D0) --------------------------------------------------------
const CHAR * Rules_HostRenameFile(double context)
{
  int v1; // ecx
  const CHAR *result; // eax
  const CHAR *oldFileName; // ecx

  if ( Lexer_TokenExpect(2) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v1, context);
  if ( result )
  {
    result = (const CHAR *)Rules_GetFileNameArg(2, (int)result, context);
    if ( result )
      return (const CHAR *)Rules_RenameFile(oldFileName, result, (int)oldFileName);
  }
  return result;
}
// 49E8F9: variable 'v1' is possibly undefined
// 49E91B: variable 'v3' is possibly undefined

//----- (0049E930) --------------------------------------------------------
signed int * Rules_HostFormat(double context)
{
  signed int *emptyResult; // ebp
  char *outputString; // esi
  int v3; // ecx
  int argCount; // ebx
  int logicalName; // ecx
  int v7; // ecx
  signed int formatString; // ebp
  char v9; // ah
  int segmentStart; // ecx
  int segmentLength; // edi
  _BYTE *i; // eax
  int percentPos; // edi
  int v14; // ecx
  char v15; // cl
  unsigned __int8 conversionChar; // ch
  int v17; // edx
  int v18; // eax
  const char *convertedString; // eax
  signed int *v20; // eax
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  char flagBuffer[512]; // [esp+0h] [ebp-284h] BYREF
  char specBuffer[80]; // [esp+200h] [ebp-84h] BYREF
  int formatIndex; // [esp+250h] [ebp-34h] BYREF
  int outputCapacity; // [esp+254h] [ebp-30h] BYREF
  int outputLength; // [esp+258h] [ebp-2Ch] BYREF
  int longFlag; // [esp+25Ch] [ebp-28h] BYREF
  int argIndex; // [esp+260h] [ebp-24h]
  int savedLogicalName; // [esp+264h] [ebp-20h]
  signed int *fallbackResult; // [esp+268h] [ebp-1Ch]

  argIndex = 3;
  formatIndex = 0;
  outputCapacity = 0;
  outputLength = 0;
  emptyResult = Str_Intern(g_Rules_HostFormatEmptyResult, 0);
  fallbackResult = emptyResult;
  outputString = 0;
  argCount = Lexer_TokenExpect(2);
  if ( argCount == -1 )
    return emptyResult;
  logicalName = Rules_GetLogicalNameArg(1, (int)aStdout_0, v3, context);
  savedLogicalName = logicalName;
  if ( logicalName )
  {
    if ( !strcmp_(logicalName, aNil_0) || IO_QueryRouters(logicalName) )
    {
      formatString = Rules_FormatCountConversionSpecs(argCount, context);
      if ( formatString )
      {
        while ( 1 )
        {
          v9 = *(_BYTE *)(formatString + formatIndex);
          if ( !v9 )
            break;
          if ( v9 == 37 )
          {
            percentPos = formatIndex++;
            LOBYTE(v14) = Rules_FormatParseFlag(formatString, &formatIndex, &longFlag, flagBuffer);
            BYTE1(v14) = v14;
            if ( (_BYTE)v14 == 32 )
            {
              outputString = Str_Append(flagBuffer, outputString, (unsigned int *)&outputCapacity, &outputLength);
              if ( !outputString )
                return fallbackResult;
            }
            else
            {
              strncpy_(v14, percentPos + formatString);
              v17 = longFlag;
              specBuffer[formatIndex - percentPos] = 0;
              if ( !v17 && (v15 == 100 || v15 == 111 || v15 == 117 || v15 == 120) )
              {
                v18 = formatIndex - percentPos;
                flagBuffer[v18 + 511] = 108;
                specBuffer[v18] = conversionChar;
                longFlag = 1;
                specBuffer[v18 + 1] = 0;
              }
              convertedString = (const char *)Rules_FormatConvertArg(specBuffer, argIndex, longFlag, conversionChar, context);
              if ( !convertedString )
              {
                if ( outputString )
                  Mem_SmallBlockFree(outputString, outputCapacity);
                return fallbackResult;
              }
              outputString = Str_Append(convertedString, outputString, (unsigned int *)&outputCapacity, &outputLength);
              if ( !outputString )
                return fallbackResult;
              ++argIndex;
            }
          }
          else
          {
            segmentStart = formatIndex;
            segmentLength = 0;
            for ( i = (_BYTE *)(formatString + formatIndex); *i != 37; ++segmentLength )
            {
              if ( !*i )
                break;
              if ( segmentLength >= 80 )
                break;
              ++i;
              ++formatIndex;
            }
            outputString = Str_AppendBounded(segmentStart + formatString, outputString, &outputLength, formatIndex - segmentStart, (unsigned int *)&outputCapacity);
          }
        }
        if ( outputString )
        {
          v20 = Str_Intern(outputString, v7);
          if ( strcmp_(v20, v21) )
            Output_Write(savedLogicalName, (int)outputString, v22);
          Mem_SmallBlockFree(outputString, outputCapacity);
          return (signed int *)v23;
        }
        else
        {
          return Str_Intern(g_Rules_HostFormatEmptyResult, v7);
        }
      }
      else
      {
        return fallbackResult;
      }
    }
    else
    {
      IO_ReportUnrecognizedRouter(savedLogicalName);
      return emptyResult;
    }
  }
  else
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return emptyResult;
  }
}
// 49E9A8: variable 'v3' is possibly undefined
// 49EB1A: variable 'v14' is possibly undefined
// 49EB3F: variable 'v15' is possibly undefined
// 49EB5E: variable 'v16' is possibly undefined
// 49EC37: variable 'v7' is possibly undefined
// 49EC45: variable 'v21' is possibly undefined
// 49EC57: variable 'v22' is possibly undefined
// 49EC6A: variable 'v23' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (0049ECA0) --------------------------------------------------------
signed int  Rules_FormatCountConversionSpecs(int argCount, double context)
{
  signed int result; // eax
  int specCount; // edi
  int formatString; // esi
  char ch; // dl
  _DWORD argData[6]; // [esp+0h] [ebp-44h] BYREF
  _BYTE flagBuffer[12]; // [esp+18h] [ebp-2Ch] BYREF
  int longFlag; // [esp+24h] [ebp-20h] BYREF
  int formatIndex[7]; // [esp+28h] [ebp-1Ch] BYREF

  result = Lexer_ParseValueList(2, argData, 3, context);
  if ( result )
  {
    specCount = 0;
    formatString = *(_DWORD *)(argData[2] + 16);
    formatIndex[0] = 0;
    while ( 1 )
    {
      ch = *(_BYTE *)(formatString + formatIndex[0]);
      if ( !ch )
        break;
      if ( ch == 37 )
      {
        ++formatIndex[0];
        if ( Rules_FormatParseFlag(formatString, formatIndex, &longFlag, flagBuffer) != 32 )
          ++specCount;
      }
      else
      {
        ++formatIndex[0];
      }
    }
    if ( specCount == argCount - 2 )
    {
      return formatString;
    }
    else
    {
      Rules_ExpectedCountError((int)aFormat, specCount + 2);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}

//----- (0049ED50) --------------------------------------------------------
char  Rules_FormatParseFlag(int formatString, int *formatIndex, _DWORD *longFlagOut, _BYTE *flagBuffer)
{
  int copyIndex; // esi
  char formatChar; // bl
  _BYTE *bufferCursor; // ecx
  char *charPtr; // eax
  char result; // al
  _DWORD *v11; // edx
  _DWORD *v12; // edx
  _DWORD *v13; // edx
  _DWORD *v14; // edx
  _DWORD *v15; // edx
  int startIndex; // [esp+0h] [ebp-18h]

  copyIndex = 0;
  *longFlagOut = 0;
  formatChar = *(_BYTE *)(*formatIndex + formatString);
  switch ( formatChar )
  {
    case 'n':
      sprintf_(flagBuffer, asc_5069B8);
      result = 32;
      ++*v11;
      break;
    case 'r':
      sprintf_(flagBuffer, asc_506A6C);
      result = 32;
      ++*v12;
      break;
    case 't':
      sprintf_(flagBuffer, asc_5069C0);
      result = 32;
      ++*v13;
      break;
    case 'v':
      sprintf_(flagBuffer, asc_5069CC);
      result = 32;
      ++*v14;
      break;
    case '%':
      sprintf_(flagBuffer, asc_506A70);
      result = 32;
      ++*v15;
      break;
    default:
      startIndex = *formatIndex;
      *flagBuffer = 0;
      bufferCursor = flagBuffer;
      while ( 1 )
      {
        charPtr = (char *)(*formatIndex + formatString);
        if ( *charPtr == 37 || !*charPtr || *formatIndex - startIndex >= 80 )
          return 32;
        result = *charPtr;
        ++bufferCursor;
        flagBuffer[copyIndex++] = result;
        *bufferCursor = 0;
        if ( result == 100
          || result == 111
          || result == 120
          || result == 117
          || result == 99
          || result == 115
          || result == 101
          || result == 102
          || result == 103 )
        {
          break;
        }
        ++*formatIndex;
      }
      if ( *(_BYTE *)(formatString + *formatIndex - 1) == 108 )
        *longFlagOut = 1;
      ++*formatIndex;
      break;
  }
  return result;
}
// 49EE0B: variable 'v11' is possibly undefined
// 49EE27: variable 'v12' is possibly undefined
// 49EE43: variable 'v13' is possibly undefined
// 49EE5F: variable 'v14' is possibly undefined
// 49EE7B: variable 'v15' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (0049EEE0) --------------------------------------------------------
signed int  Rules_FormatConvertArg(
        const char *formatSpec,
        int argIndex,
        int longFlag,
        unsigned int conversionChar,
        double context)
{
  signed int result; // eax
  _DWORD *charBuffer; // eax
  char *v9; // ecx
  signed int v10; // esi
  int v11; // edx
  _DWORD *v12; // ecx
  int v13; // ecx
  _DWORD *stringBuffer; // eax
  _DWORD *numberBuffer; // eax
  int v17; // eax
  _DWORD *floatBuffer; // eax
  double floatValue; // [esp+0h] [ebp-30h]
  int argData; // [esp+8h] [ebp-28h] BYREF
  int argType; // [esp+Ch] [ebp-24h]
  int argValue; // [esp+10h] [ebp-20h]
  int intValue; // [esp+20h] [ebp-10h]

  if ( conversionChar >= 0x67 )
  {
    if ( conversionChar <= 0x67 )
      goto LABEL_19;
    if ( conversionChar >= 0x73 )
    {
      if ( conversionChar <= 0x73 )
      {
        result = Lexer_ParseValueList(argIndex, &argData, 111, context);
        if ( !result )
          return result;
        stringBuffer = Mem_SmallBlockAlloc(strlen(*(const char **)(argValue + 16)) + strlen(formatSpec) + 200);
        sprintf_(stringBuffer, formatSpec, *(_DWORD *)(argValue + 16));
        goto LABEL_6;
      }
      if ( conversionChar < 0x75 || conversionChar > 0x75 && conversionChar != 120 )
        goto LABEL_17;
    }
    else if ( conversionChar != 111 )
    {
      goto LABEL_17;
    }
LABEL_11:
    result = Lexer_ParseValueList(argIndex, &argData, 110, context);
    if ( !result )
      return result;
    numberBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
    if ( argType )
    {
      sprintf_(numberBuffer, formatSpec, *(_DWORD *)(argValue + 16));
    }
    else
    {
      intValue = (int)*(double *)(argValue + 16);
      sprintf_(v17, formatSpec, intValue);
    }
LABEL_6:
    v10 = Str_Intern(v9, (int)v9)[4];
    Mem_SmallBlockFree(v12, v11);
    return v10;
  }
  if ( conversionChar < 0x64 )
  {
    if ( conversionChar == 99 )
    {
      result = Lexer_ParseValueList(argIndex, &argData, 111, context);
      if ( !result )
        return result;
      charBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
      sprintf_(charBuffer, formatSpec, **(unsigned __int8 **)(argValue + 16));
      goto LABEL_6;
    }
LABEL_17:
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aErrorInFormatT, longFlag);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForFormattedOu, v13);
    return 0;
  }
  if ( conversionChar <= 0x64 )
    goto LABEL_11;
LABEL_19:
  result = Lexer_ParseValueList(argIndex, &argData, 110, context);
  if ( result )
  {
    floatBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
    if ( argType )
    {
      floatValue = (double)*(int *)(argValue + 16);
      sprintf_(floatBuffer, formatSpec, floatValue);
    }
    else
    {
      sprintf_(floatBuffer, formatSpec, *(double *)(argValue + 16));
    }
    goto LABEL_6;
  }
  return result;
}
// 49F064: inconsistent fpu stack
// 49EF4A: variable 'v9' is possibly undefined
// 49EF54: variable 'v12' is possibly undefined
// 49EF54: variable 'v11' is possibly undefined
// 49EFB5: variable 'v13' is possibly undefined
// 49F077: variable 'v17' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0049F120) --------------------------------------------------------
signed int * Rules_HostReadline(int returnValue, unsigned int a2, double context)
{
  int argCount; // eax
  int v4; // ecx
  char *logicalName; // esi
  unsigned int v6; // ecx
  char *lineBuffer; // ebx
  int v8; // ecx
  signed int *result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  signed int *v16; // eax
  int v17; // ecx
  unsigned int bufferSize[5]; // [esp+0h] [ebp-14h] BYREF

  bufferSize[3] = a2;
  bufferSize[0] = 0;
  *(_DWORD *)(returnValue + 4) = 3;
  argCount = Lexer_TokenExpect(1);
  if ( argCount == -1 )
  {
    result = Str_Intern(aReadError, v4);
LABEL_8:
    *(_DWORD *)(v10 + 8) = result;
    return result;
  }
  if ( argCount )
  {
    logicalName = (char *)Rules_GetLogicalNameArg(1, (int)aStdin, v4, context);
    if ( !logicalName )
    {
      Rules_ReportIllegalLogicalName();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      result = Str_Intern(aReadError, v11);
      *(_DWORD *)(v12 + 8) = result;
      return result;
    }
  }
  else
  {
    logicalName = aStdin;
  }
  if ( !IO_QueryRouters((int)logicalName) )
  {
    IO_ReportUnrecognizedRouter((int)logicalName);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    result = Str_Intern(aReadError, v13);
    *(_DWORD *)(v14 + 8) = result;
    return result;
  }
  g_Lexer_PendingLineCharIndex = 0;
  lineBuffer = Rules_ReadLineWithEscaping((int)logicalName, &g_Lexer_PendingLineCharIndex, bufferSize, v6);
  g_Lexer_PendingLineCharIndex = -1;
  if ( !Rules_GetEvaluationErrorFlag() )
  {
    if ( lineBuffer )
    {
      v16 = Str_Intern(lineBuffer, v8);
      *(_DWORD *)(v17 + 8) = v16;
      return (signed int *)Mem_SmallBlockFree(lineBuffer, bufferSize[0]);
    }
    result = Str_Intern(aEof, v8);
    *(_DWORD *)(v10 + 4) = 2;
    goto LABEL_8;
  }
  result = Str_Intern(aReadError, v8);
  *(_DWORD *)(v15 + 8) = result;
  if ( lineBuffer )
    return (signed int *)Mem_SmallBlockFree(lineBuffer, bufferSize[0]);
  return result;
}
// 49F17C: variable 'v6' is possibly undefined
// 49F1A3: variable 'v8' is possibly undefined
// 49F1A8: variable 'v10' is possibly undefined
// 49F1BF: variable 'v4' is possibly undefined
// 49F202: variable 'v11' is possibly undefined
// 49F207: variable 'v12' is possibly undefined
// 49F232: variable 'v13' is possibly undefined
// 49F237: variable 'v14' is possibly undefined
// 49F24C: variable 'v15' is possibly undefined
// 49F270: variable 'v17' is possibly undefined
// 51A628: using guessed type int dword_51A628;

//----- (0049F290) --------------------------------------------------------
char * Rules_ReadLineWithEscaping(int logicalName, int *currentPosition, unsigned int *maximumSize, unsigned int a4)
{
  int ch; // esi
  char *appended; // edx
  unsigned int v7; // ecx

  ch = Lexer_PeekChar(logicalName, a4);
  appended = 0;
  if ( ch == -1 )
    return 0;
  while ( ch != 10 && ch != 13 && ch != -1 && !Rules_GetEvaluationErrorFlag() )
  {
    appended = Str_AppendCharEscaping(ch, appended, maximumSize, currentPosition, *maximumSize + 80);
    ch = Lexer_PeekChar(logicalName, v7);
  }
  return Str_AppendCharEscaping(0, appended, maximumSize, currentPosition, *maximumSize + 80);
}
// 49F2D2: variable 'appended' is possibly undefined
// 49F2DB: variable 'v7' is possibly undefined

//----- (0049F310) --------------------------------------------------------
signed int Rules_ReportIllegalLogicalName()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aIofun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalLogical, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction_, v2);
}
// 49F330: variable 'v0' is possibly undefined
// 49F33C: variable 'v1' is possibly undefined
// 49F34B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049F360) --------------------------------------------------------
signed int Rules_RegisterPredicateHostFunctions()
{
  Rules_RegisterHostFunction(aNot_0, 98, (int)aNotfunction, (int)Rules_NotFunction, (int)a11_6);
  Rules_RegisterHostFunction(aAnd_0, 98, (int)aAndfunction, (int)Rules_AndFunction, (int)a2);
  Rules_RegisterHostFunction(aOr_0, 98, (int)aOrfunction, (int)Rules_OrFunction, (int)a2);
  Rules_RegisterHostFunction(aEq_0, 98, (int)aEqfunction, (int)Rules_HostEq, (int)a2);
  Rules_RegisterHostFunction(aNeq_0, 98, (int)aNeqfunction, (int)Rules_HostNeq, (int)a2);
  Rules_RegisterHostFunction(asc_506B64, 98, (int)aLessthanorequa, (int)Rules_LessThanOrEqualFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506B84, 98, (int)aGreaterthanore, (int)Rules_GreaterThanOrEqualFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506B9C, 98, (int)aLessthanfuncti, (int)Rules_LessThanFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506BB4, 98, (int)aGreaterthanfun, (int)Rules_GreaterThanFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506BD0, 98, (int)aNumericequalfu, (int)Rules_NumericEqualFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506BEC, 98, (int)aNumericnotequa, (int)Rules_NumericNotEqualFunction, (int)a2N);
  Rules_RegisterHostFunction(asc_506BF0, 98, (int)aNumericnotequa, (int)Rules_NumericNotEqualFunction, (int)a2N);
  Rules_RegisterHostFunction(aSymbolp, 98, (int)aSymbolpfunctio, (int)Rules_HostSymbolp, (int)a11_6);
  Rules_RegisterHostFunction(aWordp, 98, (int)aSymbolpfunctio, (int)Rules_HostSymbolp, (int)a11_6);
  Rules_RegisterHostFunction(aStringp, 98, (int)aStringpfunctio, (int)Rules_HostStringp, (int)a11_6);
  Rules_RegisterHostFunction(aLexemep, 98, (int)aLexemepfunctio, (int)Rules_HostLexemep, (int)a11_6);
  Rules_RegisterHostFunction(aNumberp, 98, (int)aNumberpfunctio, (int)Rules_HostNumberp, (int)a11_6);
  Rules_RegisterHostFunction(aIntegerp, 98, (int)aIntegerpfuncti, (int)Rules_HostIntegerp, (int)a11_6);
  Rules_RegisterHostFunction(aFloatp, 98, (int)aFloatpfunction, (int)Rules_HostFloatp, (int)a11_6);
  Rules_RegisterHostFunction(aOddp, 98, (int)aOddpfunction, (int)Rules_OddpFunction, (int)a11i_2);
  Rules_RegisterHostFunction(aEvenp, 98, (int)aEvenpfunction, (int)Rules_EvenpFunction, (int)a11i_2);
  Rules_RegisterHostFunction(aMultifieldp, 98, (int)aMultifieldpfun, (int)Rules_HostMultifieldp, (int)a11_6);
  Rules_RegisterHostFunction(aSequencep, 98, (int)aMultifieldpfun, (int)Rules_HostMultifieldp, (int)a11_6);
  return Rules_RegisterHostFunction(aPointerp, 98, (int)aPointerpfuncti, (int)Rules_PointerpFunction, (int)a11_6);
}

//----- (0049F640) --------------------------------------------------------
int  Rules_HostEq(int a1, double a2)
{
  int result; // eax
  int argument_count; // esi
  int argument_index; // ebx
  uintptr_t expression; // ecx
  _DWORD first[6]; // [esp-4h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+14h] [ebp-2Ch] BYREF

  (void)a1;
  result = Rules_RtnArgCount();
  argument_count = result;
  if ( result )
  {
    argument_index = 2;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
    if ( !expression )
      return 1;
    Parser_ParseForm((__int16 *)expression, first, (int)expression, a2);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    if ( argument_count < 2 )
      return 1;
    while ( expression )
    {
      Parser_ParseForm((__int16 *)expression, current, (int)expression, a2);
      if ( current[1] != first[1] )
        return 0;
      if ( current[1] == 4 )
      {
        result = Rules_MultifieldRangesEqual(current, first);
        if ( !result )
          return result;
      }
      else if ( current[2] != first[2] )
      {
        return 0;
      }
      ++argument_index;
      expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
      if ( argument_index > argument_count )
        return 1;
    }
    return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049F6E0) --------------------------------------------------------
int  Rules_HostNeq(double a1)
{
  int result; // eax
  int argument_index; // ebx
  uintptr_t expression; // ecx
  _DWORD first[6]; // [esp+0h] [ebp-48h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-30h] BYREF

  result = Rules_RtnArgCount();
  if ( result )
  {
    argument_index = 2;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
    if ( !expression )
      return 1;
    Parser_ParseForm((__int16 *)expression, first, (int)expression, a1);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    if ( result < 2 )
      return 1;
    while ( expression )
    {
      Parser_ParseForm((__int16 *)expression, current, (int)expression, a1);
      if ( current[1] == first[1] )
      {
        if ( current[1] == 4 )
        {
          if ( Rules_MultifieldRangesEqual(current, first) == 1 )
            return 0;
        }
        else if ( current[2] == first[2] )
        {
          return 0;
        }
      }
      ++argument_index;
      expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
      if ( argument_index > result )
        return 1;
    }
    return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049F790) --------------------------------------------------------
BOOL  Rules_HostStringp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 3 )
      return 1;
  }
  return result;
}

//----- (0049F7E0) --------------------------------------------------------
BOOL  Rules_HostSymbolp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 2 )
      return 1;
  }
  return result;
}

//----- (0049F830) --------------------------------------------------------
BOOL  Rules_HostLexemep(double context)
{
  BOOL result; // eax
  int argData; // [esp-4h] [ebp-20h] BYREF
  int argType; // [esp+0h] [ebp-1Ch]

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &argData, context);
    if ( argType == 2 || argType == 3 )
      return 1;
  }
  return result;
}

//----- (0049F880) --------------------------------------------------------
BOOL  Rules_HostNumberp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] <= 1u )
      return 1;
  }
  return result;
}
// 49F8B5: simplified comparisons for '%var_1C.4': !=0 && !=1 became >=2u

//----- (0049F8D0) --------------------------------------------------------
BOOL  Rules_HostFloatp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( !argData[1] )
      return 1;
  }
  return result;
}

//----- (0049F920) --------------------------------------------------------
BOOL  Rules_HostIntegerp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 1 )
      return 1;
  }
  return result;
}

//----- (0049F960) --------------------------------------------------------
BOOL  Rules_HostMultifieldp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 4 )
      return 1;
  }
  return result;
}

//----- (0049F9B0) --------------------------------------------------------
BOOL  Rules_PointerpFunction(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 5 )
      return 1;
  }
  return result;
}

//----- (0049FA00) --------------------------------------------------------
int  Rules_NotFunction(int a1, double context)
{
  uintptr_t expression; // eax
  _DWORD parsed[6]; // [esp-4h] [ebp-1Ch] BYREF

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 0;
  if ( Parser_ParseForm((__int16 *)expression, parsed, a1, context) )
    return 0;
  return parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FA50) --------------------------------------------------------
int  Rules_AndFunction(int a1, double context)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)a1;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, context) )
      return 0;
    if ( parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2 )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FAB0) --------------------------------------------------------
int  Rules_OrFunction(int a1, double context)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)a1;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, context) )
      return 0;
    if ( parsed[2] != g_ClipsFalseSymbol || parsed[1] != 2 )
      return 1;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 0;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FB00) --------------------------------------------------------
double  Rules_LessThanOrEqualFunction(int a1, double result, int a3)
{
  int firstExpr; // esi
  int v4; // eax
  int currentExpr; // esi
  int i; // edi
  int v7; // eax
  int previousData; // [esp+0h] [ebp-44h] BYREF
  int previousType; // [esp+4h] [ebp-40h]
  int previousValue; // [esp+8h] [ebp-3Ch]
  int currentData; // [esp+18h] [ebp-2Ch] BYREF
  int currentType; // [esp+1Ch] [ebp-28h]
  int currentValue; // [esp+20h] [ebp-24h]
  int v14; // [esp+38h] [ebp-Ch]
  int v15; // [esp+3Ch] [ebp-8h]

  v15 = a1;
  v14 = a3;
  firstExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  if ( firstExpr )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)firstExpr, 0, &previousData, result, 1);
    if ( v4 )
    {
      currentExpr = *(_DWORD *)(firstExpr + 10);
      for ( i = 2; currentExpr; ++i )
      {
        result = Rules_CoerceFormToNumericArg((__int16 *)currentExpr, 0, &currentData, result, i);
        if ( !v7 )
          break;
        if ( previousType == 1 )
        {
          if ( currentType == 1 )
          {
            if ( *(_DWORD *)(previousValue + 16) > *(_DWORD *)(currentValue + 16) )
              return result;
          }
          else if ( (double)*(int *)(previousValue + 16) > *(double *)(currentValue + 16) )
          {
            return result;
          }
        }
        else if ( currentType == 1 )
        {
          if ( (double)*(int *)(currentValue + 16) < *(double *)(previousValue + 16) )
            return result;
        }
        else if ( *(double *)(previousValue + 16) > *(double *)(currentValue + 16) )
        {
          return result;
        }
        previousType = currentType;
        previousValue = currentValue;
        currentExpr = *(_DWORD *)(currentExpr + 10);
      }
    }
  }
  return result;
}
// 49FB39: variable 'v4' is possibly undefined
// 49FB5C: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;

static int Parser_ParseNumericFormCompat(__int16 *expression, int coerce_integer_to_float, _DWORD *parsed, double context, int argument_index)
{
  unsigned int value_type;
  int value;

  if ( !expression || !parsed )
    return 0;
  if ( (unsigned __int16)*expression > 1u )
  {
    Parser_ParseForm(expression, parsed, coerce_integer_to_float, context);
    value_type = parsed[1];
    value = parsed[2];
  }
  else
  {
    value_type = *expression;
    value = *(_DWORD *)(expression + 1);
  }
  if ( value_type > 1 )
  {
    Parser_ReportError(argument_index, (int)aIntegerOrFlo_0);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    parsed[1] = 1;
    parsed[2] = Rules_AddIntegerValue(0);
    return 0;
  }
  if ( coerce_integer_to_float && value_type == 1 )
    value = Rules_AddDoubleValue((double)*(int *)((uintptr_t)(unsigned int)value + 16));
  parsed[1] = value_type;
  parsed[2] = value;
  return 1;
}

static int Parser_NumberValueAsInt(int value)
{
  if ( !value )
    return 0;
  return *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
}

static double Parser_NumberValueAsDouble(int value)
{
  if ( !value )
    return 0.0;
  return *(double *)((uintptr_t)(unsigned int)value + 16);
}

static double Parser_NumberValueAsComparableDouble(int type, int value)
{
  return type == 1 ? (double)Parser_NumberValueAsInt(value) : Parser_NumberValueAsDouble(value);
}

//----- (0049FC20) --------------------------------------------------------
int  Rules_GreaterThanOrEqualFunction(int a1, double result, int a3)
{
  uintptr_t expression; // esi
  int argument_index; // edi
  _DWORD previous[6]; // [esp+0h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-2Ch] BYREF

  (void)a1;
  (void)a3;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, previous, result, 1) )
    return 0;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  for ( argument_index = 2; expression; ++argument_index )
  {
    if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, current, result, argument_index) )
      return 0;
    if ( previous[1] == 1 )
    {
      if ( current[1] == 1 )
      {
        if ( Parser_NumberValueAsInt(previous[2]) < Parser_NumberValueAsInt(current[2]) )
          return 0;
      }
      else if ( (double)Parser_NumberValueAsInt(previous[2]) < Parser_NumberValueAsDouble(current[2]) )
      {
        return 0;
      }
    }
    else if ( current[1] == 1 )
    {
      if ( (double)Parser_NumberValueAsInt(current[2]) > Parser_NumberValueAsDouble(previous[2]) )
        return 0;
    }
    else if ( Parser_NumberValueAsDouble(previous[2]) < Parser_NumberValueAsDouble(current[2]) )
    {
      return 0;
    }
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FD40) --------------------------------------------------------
int  Rules_LessThanFunction(int a1, double result, int a3)
{
  uintptr_t expression; // esi
  int argument_index; // edi
  _DWORD previous[6]; // [esp+0h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-2Ch] BYREF

  (void)a1;
  (void)a3;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, previous, result, 1) )
    return 0;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  for ( argument_index = 2; expression; ++argument_index )
  {
    if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, current, result, argument_index) )
      return 0;
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) >= Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FE60) --------------------------------------------------------
int  Rules_GreaterThanFunction(int a1, double result, int a3)
{
  uintptr_t expression; // esi
  int argument_index; // edi
  _DWORD previous[6]; // [esp+0h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-2Ch] BYREF

  (void)a1;
  (void)a3;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, previous, result, 1) )
    return 0;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  for ( argument_index = 2; expression; ++argument_index )
  {
    if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, current, result, argument_index) )
      return 0;
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) <= Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FF80) --------------------------------------------------------
int  Rules_NumericEqualFunction(int a1, double result, int a3)
{
  uintptr_t expression; // esi
  int argument_index; // edi
  _DWORD previous[6]; // [esp+0h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-2Ch] BYREF

  (void)a1;
  (void)a3;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, previous, result, 1) )
    return 0;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  for ( argument_index = 2; expression; ++argument_index )
  {
    if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, current, result, argument_index) )
      return 0;
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) != Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

