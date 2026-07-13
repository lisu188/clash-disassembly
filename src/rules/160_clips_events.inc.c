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
  int v2; // edx

  for ( i = dword_51AA3C; i; i = *(_DWORD *)(v2 + 36) )
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
const void * Rules_BsaveWriteFunctionNames(int a1)
{
  int i; // eax
  __int16 v3; // dx
  const void *result; // eax
  int v5; // esi
  int v6; // [esp+0h] [ebp-20h] BYREF
  _DWORD v7[7]; // [esp+4h] [ebp-1Ch] BYREF

  v7[0] = 0;
  for ( i = Rules_GetFunctionDefinitionListHead(); i; i = *(_DWORD *)(i + 27) )
  {
    if ( *(_WORD *)(i + 25) )
    {
      v3 = v7[0];
      ++v7[0];
      *(_WORD *)(i + 25) = v3;
    }
    else
    {
      *(_WORD *)(i + 25) = -1;
    }
  }
  Rules_BsaveWriteBlock(4, a1, v7);
  if ( !v7[0] )
    return Rules_BsaveWriteBlock(4, a1, v7);
  v6 = Rules_BsaveFunctionNamesLength();
  Rules_BsaveWriteBlock(4, a1, &v6);
  result = (const void *)Rules_GetFunctionDefinitionListHead();
  v5 = (int)result;
  if ( result )
  {
    do
    {
      if ( *(__int16 *)(v5 + 25) >= 0 )
        result = Rules_BsaveWriteBlock(strlen(*(const char **)(*(_DWORD *)v5 + 16)) + 1, a1, *(const void **)(*(_DWORD *)v5 + 16));
      v5 = *(_DWORD *)(v5 + 27);
    }
    while ( v5 );
  }
  return result;
}

//----- (00496130) --------------------------------------------------------
int Rules_BsaveFunctionNamesLength()
{
  int v0; // edx
  int v1; // ebx

  v0 = Rules_GetFunctionDefinitionListHead();
  v1 = 0;
  if ( !v0 )
    return v1;
  do
  {
    while ( *(__int16 *)(v0 + 25) < 0 )
    {
      v0 = *(_DWORD *)(v0 + 27);
      if ( !v0 )
        return v1;
    }
    v1 += strlen(*(const char **)(*(_DWORD *)v0 + 16)) + 1;
    v0 = *(_DWORD *)(v0 + 27);
  }
  while ( v0 );
  return v1;
}

//----- (00496180) --------------------------------------------------------
_DWORD * Rules_ConstructQueuePush(int a1)
{
  _DWORD *v2; // ecx
  _DWORD *result; // eax
  _DWORD *v4; // ecx

  v2 = *(_DWORD **)(dword_54DBA8 + 32);
  if ( v2 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 32);
    *(_DWORD *)(dword_54DBA8 + 32) = *v2;
    result = (_DWORD *)dword_54DBAC;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  *result = a1;
  v4 = result;
  if ( dword_51AA40 )
  {
    for ( result = (_DWORD *)dword_51AA40; result[1]; result = (_DWORD *)result[1] )
      ;
    result[1] = v4;
  }
  else
  {
    dword_51AA40 = (int)result;
  }
  return result;
}
// 51AA40: using guessed type int dword_51AA40;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004961F0) --------------------------------------------------------
int  Rules_ConstructQueuePop(_DWORD *a1)
{
  _DWORD *v1; // eax
  int result; // eax

  *a1 = *(_DWORD *)dword_51AA40;
  v1 = (_DWORD *)dword_51AA40;
  dword_51AA40 = *(_DWORD *)(dword_51AA40 + 4);
  dword_54DBAC = (int)v1;
  *v1 = *(_DWORD *)(dword_54DBA8 + 32);
  result = dword_54DBAC;
  *(_DWORD *)(dword_54DBA8 + 32) = dword_54DBAC;
  return result;
}
// 51AA40: using guessed type int dword_51AA40;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00496230) --------------------------------------------------------
__int16  Rules_MarkReferencedFunctions(__int16 *result)
{
  __int16 *i; // edx
  int v2; // ecx

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
          v2 = *(int *)((char *)dword_54E530 + (_DWORD)result);
          if ( !v2 || (*(_BYTE *)(v2 + 1) & 0x40) == 0 )
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
const void * Rules_BsaveWriteHeader(int a1)
{
  Rules_BsaveWriteBlock(strlen((const char *)g_Rules_BloadFileHeaderID) + 1, a1, g_Rules_BloadFileHeaderID);
  return Rules_BsaveWriteBlock(strlen(g_Rules_BsaveVersionID) + 1, a1, g_Rules_BsaveVersionID);
}
// 51A1C0: using guessed type void *off_51A1C0;
// 51A1C4: using guessed type char *off_51A1C4;

//----- (00496310) --------------------------------------------------------
const void * Rules_BsaveWriteEndTag(int a1, int a2)
{
  int v2; // ecx
  _DWORD v4[8]; // [esp-1Ch] [ebp-20h] BYREF

  v4[6] = a2;
  strncpy_(a1, g_Rules_BloadFileHeaderID);
  return Rules_BsaveWriteBlock(20, v2, v4);
}
// 496333: variable 'v2' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);
// 51A1C0: using guessed type void *off_51A1C0;

//----- (00496340) --------------------------------------------------------
signed int  Rules_RegisterBinaryItem(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9)
{
  _DWORD *v12; // ebx
  int v13; // ecx
  _DWORD *v14; // eax
  int v15; // ebx
  int v16; // eax

  v12 = *(_DWORD **)(dword_54DBA8 + 160);
  v13 = 0;
  if ( v12 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 160);
    *(_DWORD *)(dword_54DBA8 + 160) = *v12;
    v14 = (_DWORD *)dword_54DBAC;
  }
  else
  {
    v14 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x28);
  }
  v14[1] = a4;
  v14[5] = a3;
  v14[8] = a2;
  *v14 = a1;
  v14[6] = a5;
  v14[7] = a6;
  v14[2] = a7;
  v14[3] = a8;
  v14[4] = a9;
  v15 = (int)v14;
  if ( !dword_51AA3C )
  {
    v14[9] = 0;
    dword_51AA3C = (int)v14;
    return 1;
  }
  v16 = dword_51AA3C;
  do
  {
    if ( a2 >= *(_DWORD *)(v16 + 32) )
      break;
    v13 = v16;
    v16 = *(_DWORD *)(v16 + 36);
  }
  while ( v16 );
  if ( !v13 )
  {
    *(_DWORD *)(v15 + 36) = dword_51AA3C;
    dword_51AA3C = v15;
    return 1;
  }
  *(_DWORD *)(v15 + 36) = v16;
  *(_DWORD *)(v13 + 36) = v15;
  return 1;
}
// 4963D1: variable 'v13' is possibly undefined
// 51AA3C: using guessed type int dword_51AA3C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00496420) --------------------------------------------------------
const void * Rules_BsaveWriteBlock(int a1, int a2, const void *result)
{
  if ( a1 )
    return (const void *)fwrite_(result, a1, a2, 1);
  return result;
}

//----- (004967B0) --------------------------------------------------------
signed int Rules_RegisterConstraintCheckingCommands()
{
  int i; // eax

  dword_54E694 = (int)Mem_SmallBlockAlloc(0x29Cu);
  if ( !dword_54E694 )
    IO_RunRouterExitCallbacks();
  for ( i = 0; i != 668; i += 4 )
    *(_DWORD *)(dword_54E694 + i) = 0;
  Rules_RegisterHostFunction(aGetDynamicCons, 98, (int)aGdccommand, (int)Rules_GetDynamicConstraintCheckingCommand, (int)a00_14);
  Rules_RegisterHostFunction(aSetDynamicCons, 98, (int)aSdccommand, (int)Rules_SetDynamicConstraintCheckingCommand, (int)a11_0);
  Rules_RegisterHostFunction(aGetStaticConst, 98, (int)aGsccommand, (int)Rules_GetStaticConstraintCheckingCommand, (int)a00_14);
  return Rules_RegisterHostFunction(aSetStaticConst, 98, (int)aSsccommand, (int)Rules_SetStaticConstraintCheckingCommand, (int)a11_0);
}
// 54E694: using guessed type int dword_54E694;

//----- (00496880) --------------------------------------------------------
int  AST_FreeNodeChildren(int result)
{
  int v1; // edx
  _DWORD *v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // edx
  int v6; // edx

  v1 = result;
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
    AST_FreeNodeChildren(*(_DWORD *)(v1 + 26));
    dword_54DBAC = (int)v2;
    *v2 = *(_DWORD *)(dword_54DBA8 + 168);
    result = dword_54DBA8;
    *(_DWORD *)(dword_54DBA8 + 168) = dword_54DBAC;
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
__int16 * AST_ReleaseNodeChildSlots(int a1, int a2)
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
    while ( *(int *)(a1 + 34) < 0 )
    {
      AST_DeinstallNodeChain(*(__int16 **)(a1 + 6));
      AST_DeinstallNodeChain(*(__int16 **)(v3 + 14));
      AST_DeinstallNodeChain(*(__int16 **)(v4 + 10));
      AST_DeinstallNodeChain(*(__int16 **)(v5 + 18));
      result = AST_DeinstallNodeChain(*(__int16 **)(v6 + 22));
      if ( !*(_DWORD *)(v8 + 26) )
        return result;
      a1 = *(_DWORD *)(v8 + 26);
    }
    AST_RemoveHashedNodeChain(*(__int16 **)(a1 + 6), a2);
    AST_RemoveHashedNodeChain(*(__int16 **)(v9 + 14), v10);
    AST_RemoveHashedNodeChain(*(__int16 **)(v11 + 10), v12);
    AST_RemoveHashedNodeChain(*(__int16 **)(v13 + 18), v14);
    result = AST_RemoveHashedNodeChain(*(__int16 **)(v15 + 22), v16);
    if ( !*(_DWORD *)(v17 + 26) )
      break;
    a1 = *(_DWORD *)(v17 + 26);
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
  _DWORD *v2; // ecx
  int v3; // ebx
  int v4; // esi
  int v5; // edx

  v1 = (int)result;
  v2 = 0;
  if ( result )
  {
    v3 = *(_DWORD *)((char *)result + 34);
    if ( v3 < 0 )
    {
      return (_DWORD *)AST_FreeNodeChildren((int)result);
    }
    else
    {
      result = *(_DWORD **)(dword_54E694 + 4 * v3);
      if ( result )
      {
        while ( result != (_DWORD *)v1 )
        {
          v2 = result;
          result = *(_DWORD **)((char *)result + 30);
          if ( !result )
            return result;
        }
        v4 = *(_DWORD *)(v1 + 38) - 1;
        *(_DWORD *)(v1 + 38) = v4;
        if ( !v4 )
        {
          if ( v2 )
          {
            *(_DWORD *)((char *)v2 + 30) = *(_DWORD *)(v1 + 30);
          }
          else
          {
            v2 = (_DWORD *)(4 * *(_DWORD *)(v1 + 34) + dword_54E694);
            *v2 = *(_DWORD *)(v1 + 30);
          }
          AST_ReleaseNodeChildSlots(v1, (int)v2);
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
unsigned int  AST_HashNodeChildren(_DWORD *a1)
{
  __int16 *v2; // edi
  int v3; // ecx
  unsigned int i; // esi
  int v5; // eax
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

  v2 = *(__int16 **)((char *)a1 + 6);
  v3 = 0;
  for ( i = 9 * (*a1 << 18 >> 31)
          + 37 * (*a1 << 19 >> 31)
          + 3 * (*a1 << 20 >> 31)
          + 7 * (*a1 << 17 >> 31)
          + 59 * (*a1 << 22 >> 31)
          + 79 * (*a1 << 23 >> 31)
          + 29 * (*a1 << 16 >> 31)
          + 29 * (*a1 << 24 >> 31)
          + 61 * (*a1 << 21 >> 31)
          + 17 * (*a1 << 25 >> 31)
          + 31 * (*a1 << 26 >> 31)
          + 29 * (*a1 << 27 >> 31)
          + 19 * (*a1 << 28 >> 31)
          + 23 * (*a1 << 29 >> 31)
          + 5 * (*a1 << 30 >> 31)
          + 17 * (*a1 & 1); v2; i += v5 )
  {
    v5 = Rules_ComputeFieldHashValue(*v2, *(_DWORD *)(v2 + 1), v3);
    v3 = v6 + 1;
    v2 = *(__int16 **)(v2 + 5);
  }
  for ( j = *(__int16 **)((char *)a1 + 10); j; i += v8 )
  {
    v8 = Rules_ComputeFieldHashValue(*j, *(_DWORD *)(j + 1), v3);
    v3 = v9 + 1;
    j = *(__int16 **)(j + 5);
  }
  for ( k = *(__int16 **)((char *)a1 + 14); k; i += v11 )
  {
    v11 = Rules_ComputeFieldHashValue(*k, *(_DWORD *)(k + 1), v3);
    v3 = v12 + 1;
    k = *(__int16 **)(k + 5);
  }
  for ( m = *(__int16 **)((char *)a1 + 18); m; i += v14 )
  {
    v14 = Rules_ComputeFieldHashValue(*m, *(_DWORD *)(m + 1), v3);
    v3 = v15 + 1;
    m = *(__int16 **)(m + 5);
  }
  for ( n = *(__int16 **)((char *)a1 + 22); n; i += v17 )
  {
    v17 = Rules_ComputeFieldHashValue(*n, *(_DWORD *)(n + 1), v3);
    v3 = v18 + 1;
    n = *(__int16 **)(n + 5);
  }
  if ( *(_DWORD *)((char *)a1 + 26) )
    i += AST_HashNodeChildren(*(_DWORD *)((char *)a1 + 26));
  return i % 0xA7;
}
// 496B9A: variable 'v6' is possibly undefined
// 496BC4: variable 'v9' is possibly undefined
// 496BE4: variable 'v12' is possibly undefined
// 496C04: variable 'v15' is possibly undefined
// 496C24: variable 'v18' is possibly undefined

//----- (00496C70) --------------------------------------------------------
signed int  AST_NodesStructurallyEqual(_DWORD *a1, _DWORD *a2)
{
  __int16 *v4; // eax
  __int16 *v5; // edx
  __int16 *v6; // eax
  __int16 *v7; // edx
  __int16 *v8; // eax
  __int16 *v9; // edx
  __int16 *v10; // eax
  __int16 *v11; // edx
  __int16 *v12; // eax
  __int16 *v13; // edx

  while ( 1 )
  {
    if ( (*a1 & 1) != (*a2 & 1)
      || *a1 << 30 >> 31 != *a2 << 30 >> 31
      || *a1 << 29 >> 31 != *a2 << 29 >> 31
      || *a1 << 28 >> 31 != *a2 << 28 >> 31
      || *a1 << 27 >> 31 != *a2 << 27 >> 31
      || *a1 << 26 >> 31 != *a2 << 26 >> 31
      || *a1 << 25 >> 31 != *a2 << 25 >> 31
      || *a1 << 24 >> 31 != *a2 << 24 >> 31
      || *a1 << 16 >> 31 != *a2 << 16 >> 31
      || *a1 << 15 >> 31 != *a2 << 15 >> 31
      || *a1 << 23 >> 31 != *a2 << 23 >> 31
      || *a1 << 22 >> 31 != *a2 << 22 >> 31
      || *a1 << 21 >> 31 != *a2 << 21 >> 31
      || *a1 << 20 >> 31 != *a2 << 20 >> 31
      || *a1 << 19 >> 31 != *a2 << 19 >> 31
      || *a1 << 18 >> 31 != *a2 << 18 >> 31
      || *a1 << 17 >> 31 != *a2 << 17 >> 31 )
    {
      return 0;
    }
    v4 = *(__int16 **)((char *)a1 + 6);
    v5 = *(__int16 **)((char *)a2 + 6);
    if ( v4 )
    {
      while ( v5 )
      {
        if ( *v4 != *v5 || *(_DWORD *)(v4 + 1) != *(_DWORD *)(v5 + 1) )
          return 0;
        v4 = *(__int16 **)(v4 + 5);
        v5 = *(__int16 **)(v5 + 5);
        if ( !v4 )
          break;
      }
    }
    if ( v4 != v5 )
      return 0;
    v6 = *(__int16 **)((char *)a1 + 10);
    v7 = *(__int16 **)((char *)a2 + 10);
    if ( v6 )
    {
      while ( v7 )
      {
        if ( *v6 != *v7 || *(_DWORD *)(v6 + 1) != *(_DWORD *)(v7 + 1) )
          return 0;
        v6 = *(__int16 **)(v6 + 5);
        v7 = *(__int16 **)(v7 + 5);
        if ( !v6 )
          break;
      }
    }
    if ( v6 != v7 )
      return 0;
    v8 = *(__int16 **)((char *)a1 + 14);
    v9 = *(__int16 **)((char *)a2 + 14);
    if ( v8 )
    {
      while ( v9 )
      {
        if ( *v8 != *v9 || *(_DWORD *)(v8 + 1) != *(_DWORD *)(v9 + 1) )
          return 0;
        v8 = *(__int16 **)(v8 + 5);
        v9 = *(__int16 **)(v9 + 5);
        if ( !v8 )
          break;
      }
    }
    if ( v8 != v9 )
      return 0;
    v10 = *(__int16 **)((char *)a1 + 18);
    v11 = *(__int16 **)((char *)a2 + 18);
    if ( v10 )
    {
      while ( v11 )
      {
        if ( *v10 != *v11 || *(_DWORD *)(v10 + 1) != *(_DWORD *)(v11 + 1) )
          return 0;
        v10 = *(__int16 **)(v10 + 5);
        v11 = *(__int16 **)(v11 + 5);
        if ( !v10 )
          break;
      }
    }
    if ( v10 != v11 )
      return 0;
    v12 = *(__int16 **)((char *)a1 + 22);
    v13 = *(__int16 **)((char *)a2 + 22);
    if ( v12 )
    {
      while ( v13 )
      {
        if ( *v12 != *v13 || *(_DWORD *)(v12 + 1) != *(_DWORD *)(v13 + 1) )
          return 0;
        v12 = *(__int16 **)(v12 + 5);
        v13 = *(__int16 **)(v13 + 5);
        if ( !v12 )
          break;
      }
    }
    if ( v12 != v13
      || !*(_DWORD *)((char *)a1 + 26) && *(_DWORD *)((char *)a2 + 26)
      || *(_DWORD *)((char *)a1 + 26) && !*(_DWORD *)((char *)a2 + 26) )
    {
      return 0;
    }
    if ( *(_DWORD *)((char *)a1 + 26) == *(_DWORD *)((char *)a2 + 26) )
      return 1;
    a2 = *(_DWORD **)((char *)a2 + 26);
    a1 = *(_DWORD **)((char *)a1 + 26);
  }
}

//----- (00496F60) --------------------------------------------------------
_DWORD * AST_InternNode(_DWORD *result)
{
  _DWORD *v1; // ebx
  unsigned int v2; // eax
  _DWORD *v3; // ecx
  unsigned int v4; // esi
  int v5; // ecx
  int v6; // ecx

  v1 = result;
  if ( result )
  {
    v2 = AST_HashNodeChildren(result);
    v3 = *(_DWORD **)(dword_54E694 + 4 * v2);
    v4 = v2;
    if ( v3 )
    {
      while ( !AST_NodesStructurallyEqual(v1, v3) )
      {
        v3 = *(_DWORD **)(v5 + 30);
        if ( !v3 )
          goto LABEL_5;
      }
      ++*(_DWORD *)(v5 + 38);
      AST_FreeNodeChildren((int)v1);
      return (_DWORD *)v6;
    }
    else
    {
LABEL_5:
      AST_CollapseNodeChildSlots((int)v1, (int)v3);
      *(_DWORD *)((char *)v1 + 38) = 1;
      *(_DWORD *)((char *)v1 + 34) = v4;
      *(_DWORD *)((char *)v1 + 30) = *(_DWORD *)(dword_54E694 + 4 * v4);
      *(_DWORD *)(dword_54E694 + 4 * v4) = v1;
      return v1;
    }
  }
  return result;
}
// 496F90: variable 'v5' is possibly undefined
// 496FD0: variable 'v6' is possibly undefined
// 54E694: using guessed type int dword_54E694;

//----- (00496FE0) --------------------------------------------------------
int  AST_CollapseNodeChildSlots(int a1, int a2)
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
    AST_AddHashedNodeChain(*(__int16 **)(a1 + 6), a1, a2);
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
    a1 = *(_DWORD *)(v21 + 26);
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
int  Rules_SetDynamicConstraintCheckingCommand(int a1, double a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // [esp-4h] [ebp-28h] BYREF
  __int64 v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  v3 = Lexer_TokenExpect(1);
  v5 = v4;
  if ( v3 == -1 )
    return v4;
  Rules_RtnUnknown(1, &v7, a2);
  dword_51AAB4 = v8 != __PAIR64__(dword_54DD70, 2);
  return v5;
}
// 49707E: variable 'v4' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;
// 54DD70: using guessed type int dword_54DD70;

//----- (004970E0) --------------------------------------------------------
int Rules_GetDynamicConstraintCheckingCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  return v0;
}
// 4970FA: variable 'v0' is possibly undefined
// 51AAB4: using guessed type int dword_51AAB4;

//----- (00497100) --------------------------------------------------------
int  Rules_SetStaticConstraintCheckingCommand(int a1, double a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // [esp-4h] [ebp-28h] BYREF
  __int64 v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a1;
  v3 = Lexer_TokenExpect(1);
  v5 = v4;
  if ( v3 == -1 )
    return v4;
  Rules_RtnUnknown(1, &v7, a2);
  dword_51AAB0 = v8 != __PAIR64__(dword_54DD70, 2);
  return v5;
}
// 49711E: variable 'v4' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00497180) --------------------------------------------------------
int Rules_GetStaticConstraintCheckingCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  return v0;
}
// 49719A: variable 'v0' is possibly undefined
// 51AAB0: using guessed type int dword_51AAB0;

//----- (004971A0) --------------------------------------------------------
int __fastcall unknown_libname_10(int a1, int a2)
{
  int previous_state;

  (void)a2;
  previous_state = dword_51AAB4;
  dword_51AAB4 = a1;
  return previous_state;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971B0) --------------------------------------------------------
int Rules_DynamicConstraintCheckingEnabled()
{
  return dword_51AAB4;
}
// 51AAB4: using guessed type int dword_51AAB4;

//----- (004971D0) --------------------------------------------------------
int Rules_StaticConstraintCheckingEnabled()
{
  return dword_51AAB0;
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
  dword_54E69C = (int)result;
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
  dword_54E698 = result;
  return result;
}
// 54E698: using guessed type int dword_54E698;

//----- (00497270) --------------------------------------------------------
signed int Rules_AllocDeffactsModuleData()
{
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = *v0;
  return dword_54DBAC;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004972A0) --------------------------------------------------------
int  Rules_FreeDeffactsModuleData(int a1)
{
  int result; // eax

  result = Rules_ClearModuleConstructList(a1, dword_54E69C, a1);
  dword_54DBAC = a1;
  *(_DWORD *)a1 = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E69C: using guessed type int dword_54E69C;

//----- (004972E0) --------------------------------------------------------
int  Rules_GetDeffactsModuleItem(int a1)
{
  return Rules_GetModuleConstructData(a1, dword_54E698);
}
// 54E698: using guessed type int dword_54E698;

//----- (004972F0) --------------------------------------------------------
int  Rules_ParseDeffactsConstruct(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (00497300) --------------------------------------------------------
int  Rules_DeffactsGetNextItem(int a1)
{
  return Class_Enum(a1, dword_54E698);
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
    dword_54DBAC = fact;
    *(_DWORD *)fact = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
    result = dword_54DBA8;
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

  Rules_RegisterEvaluationHandler((int)&unk_51AAB8, 11);
  dword_54E6A4 = Module_RegisterItem(
                   (int)aDefgeneric,
                   (int)Defgeneric_AllocateModule,
                   (int)Defgeneric_RecordAtIndex,
                   (int)Defgeneric_FreeModule,
                   (int)Defgeneric_PrintModuleReference,
                   (int)Defgeneric_ParseConstruct);
  dword_54E6A0 = (int)Rules_RegisterConstructType(
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
  Rules_AddWatchItem((int)aGenericFunctio, 0, 34, (int)&dword_51B3E0, (int)Defgeneric_WatchAccessFunction, (int)Defgeneric_WatchPrintFunction);
  return Rules_AddWatchItem((int)aMethods, 0, 33, (int)&dword_51B3E4, (int)Defgeneric_MethodsWatchAccessFunction, (int)Defgeneric_MethodsWatchPrintFunction);
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
int  Defgeneric_ParseConstruct(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497700) --------------------------------------------------------
int  Defgeneric_LookupWithImports(_BYTE *a1)
{
  return Symbol_LookupInModule((char **)dword_54E6A0, a1, 1);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497720) --------------------------------------------------------
int  Defgeneric_LookupLocalOnly(_BYTE *a1)
{
  return Symbol_LookupInModule((char **)dword_54E6A0, a1, 0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497740) --------------------------------------------------------
int  Defgeneric_GetNextInModule(int a1)
{
  return Class_Enum(a1, dword_54E6A4);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497750) --------------------------------------------------------
int  Class_NextMethod(int a1, int a2)
{
  int v2; // esi
  int v4; // edx
  int v5; // ecx

  if ( a2 )
  {
    v4 = Method_FindByIndex(a1, a2) + 1;
    if ( v4 == *(_DWORD *)(v5 + 32) )
      return 0;
    else
      return *(_DWORD *)(*(_DWORD *)(v5 + 28) + 40 * v4);
  }
  else
  {
    v2 = *(_DWORD *)(a1 + 28);
    if ( v2 )
      return *(_DWORD *)v2;
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
  return Rules_UndefconstructCommand((int)this, dword_54E6A0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497820) --------------------------------------------------------
int __thiscall Defgeneric_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)dword_54E6A0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497840) --------------------------------------------------------
signed int  Defgeneric_UndefmethodCommand(int a1, double a2)
{
  signed int result; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+0h] [ebp-20h]
  int v11; // [esp+4h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-8h]

  v12 = a1;
  result = Lexer_ParseValueList(1, &v9, 2, a2);
  if ( result )
  {
    if ( Symbol_LookupInModule((char **)dword_54E6A0, *(_BYTE **)(v11 + 16), 1) || !strcmp_(0, asc_50529C) )
    {
      Rules_RtnUnknown(2, &v9, a2);
      if ( v10 == 2 )
      {
        v4 = strcmp_(v3, asc_50529C);
        if ( v4 )
        {
LABEL_7:
          Rules_PrintErrorID((int)aGenrccom, 2, 0);
          return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_0, v5);
        }
      }
      else
      {
        if ( v10 != 1 )
          goto LABEL_7;
        v4 = *(_DWORD *)(v11 + 16);
        if ( !v4 )
          goto LABEL_7;
      }
      return Defgeneric_RemoveMethod(v3, v4);
    }
    else
    {
      Rules_PrintErrorID((int)aGenrccom, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchGenericF, v6);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v11 + 16), v7);
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
int __fastcall Defgeneric_RemoveMethod(int a1, int a2)
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
  signed int v15; // eax
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
      Rules_PrintLongInteger(v11, a2);
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
      v15 = Defgeneric_CheckMethodExists((int)aUndefmethod, v14, v13);
      if ( v15 == -1 )
        return 0;
      Defgeneric_DeleteMethod(v16, v15);
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
_DWORD * Defgeneric_FormatMethodRestrictionsString(const char *a1, int a2, int a3, int a4)
{
  signed int v6; // eax
  int v7; // ecx

  v6 = Method_FindByIndex(a4, a3);
  return Defgeneric_AppendMethodSignatureText(a1, a2, v7, 40 * v6 + *(_DWORD *)(a4 + 28));
}
// 497B0A: variable 'v7' is possibly undefined

//----- (00497B20) --------------------------------------------------------
int  Defgeneric_GetTraceFlag(int a1)
{
  return *(_DWORD *)(a1 + 24);
}

//----- (00497B30) --------------------------------------------------------
int  Defgeneric_SetTraceFlag(int result, int a2)
{
  *(_DWORD *)(a2 + 24) = result;
  return result;
}

//----- (00497B40) --------------------------------------------------------
int  Defgeneric_GetMethodTraceFlag(int a1, int a2)
{
  signed int v2; // eax
  int v3; // ecx

  v2 = Method_FindByIndex(a1, a2);
  return *(_DWORD *)(*(_DWORD *)(v3 + 28) + 40 * v2 + 24) << 30 >> 31;
}
// 497B53: variable 'v3' is possibly undefined

//----- (00497B70) --------------------------------------------------------
int  Defgeneric_SetMethodTraceFlag(char a1, int a2, int a3)
{
  signed int v4; // eax
  int v5; // ecx
  int result; // eax

  v4 = Method_FindByIndex(a2, a3);
  result = *(_DWORD *)(v5 + 28) + 40 * v4;
  *(_BYTE *)(result + 24) &= ~2u;
  *(_DWORD *)(result + 24) |= 2 * (a1 & 1);
  return result;
}
// 497B91: variable 'v5' is possibly undefined

//----- (00497BB0) --------------------------------------------------------
int __thiscall Defgeneric_PpdefgenericCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)dword_54E6A0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497BD0) --------------------------------------------------------
int  Defgeneric_PpdefmethodCommand(int a1, double a2)
{
  int result; // eax
  _BYTE *v3; // esi
  int v4; // ecx
  int v5; // edx
  _DWORD v6[2]; // [esp-8h] [ebp-28h] BYREF
  int v7; // [esp+0h] [ebp-20h]
  int v8; // [esp+18h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, v6, 2, a2);
  if ( result )
  {
    v3 = *(_BYTE **)(v7 + 16);
    result = Lexer_ParseValueList(2, v6, 1, a2);
    if ( result )
    {
      result = Defgeneric_CheckGenericExists((int)aPpdefmethod, v3);
      if ( result )
      {
        result = Defgeneric_CheckMethodExists((int)aPpdefmethod, result, *(_DWORD *)(v7 + 16));
        if ( result != -1 )
        {
          result *= 40;
          v5 = result + *(_DWORD *)(v4 + 28);
          if ( *(_DWORD *)(v5 + 36) )
            return Output_WriteLongString((signed int)g_IO_LogicalName_WDisplay, *(char **)(v5 + 36));
        }
      }
    }
  }
  return result;
}
// 497C56: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (00497C80) --------------------------------------------------------
int  Defgeneric_ListDefmethodsCommand(int a1, double a2)
{
  int v2; // ecx
  int result; // eax
  _DWORD v4[9]; // [esp-8h] [ebp-24h] BYREF

  v4[7] = a1;
  if ( !Rules_RtnArgCount() )
    return Defgeneric_ListMethodsAndTally((int)g_IO_LogicalName_WDisplay, 0, v2);
  result = Lexer_ParseValueList(1, v4, 2, a2);
  if ( result )
  {
    result = Defgeneric_CheckGenericExists((int)aListDefmethods, *(_BYTE **)(v4[2] + 16));
    if ( result )
      return Defgeneric_ListMethodsAndTally((int)g_IO_LogicalName_WDisplay, result, (int)g_IO_LogicalName_WDisplay);
  }
  return result;
}
// 497CB7: variable 'v2' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (00497D10) --------------------------------------------------------
int  Defgeneric_ListDefgenericsCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(dword_54E6A0, a1, a2);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497D50) --------------------------------------------------------
int  Defgeneric_ListMethodsAndTally(int a1, int a2, int a3)
{
  int v4; // edi
  int i; // ecx
  int v6; // ecx
  int v7; // ecx

  if ( a2 )
  {
    v4 = Defgeneric_PrintMethodsList(a3, a2);
  }
  else
  {
    v4 = 0;
    for ( i = Class_Enum(0, dword_54E6A4); i; i = Class_Enum(v7, dword_54E6A4) )
    {
      v4 += Defgeneric_PrintMethodsList(i, i);
      if ( Class_Enum(v6, dword_54E6A4) )
        Output_Write(a1, (int)asc_50537C, v7);
    }
  }
  return Rules_PrintTally(a1, v4, (int)aMethods, (int)aMethod_1);
}
// 497D82: variable 'v6' is possibly undefined
// 497D92: variable 'v7' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497DD0) --------------------------------------------------------
_DWORD * Defgeneric_GetDefgenericListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, dword_54E6A0, a2);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497E10) --------------------------------------------------------
_DWORD * Defgeneric_GetDefmethodListCommand(_DWORD *a1, int a2, double a3)
{
  int v5; // eax
  _DWORD v7[10]; // [esp-8h] [ebp-28h] BYREF

  v7[8] = a2;
  v5 = Rules_RtnArgCount();
  if ( !v5 )
    return Defgeneric_BuildMethodListValue(v5, a1);
  if ( Lexer_ParseValueList(1, v7, 2, a3) && (v5 = Defgeneric_CheckGenericExists((int)aGetDefmethodLi, *(_BYTE **)(v7[2] + 16))) != 0 )
    return Defgeneric_BuildMethodListValue(v5, a1);
  else
    return Rules_SetMultifieldErrorValue((int)a1);
}

//----- (00497E70) --------------------------------------------------------
_DWORD * Defgeneric_BuildMethodListValue(int a1, _DWORD *a2)
{
  int v4; // eax
  int v5; // ecx
  int i; // ebx
  signed int v7; // ebx
  _DWORD *result; // eax
  int v9; // ecx
  int v10; // ebx
  _DWORD *v11; // edi
  int v12; // esi
  int v13; // ebp
  int v14; // ecx
  int v15; // ecx
  unsigned int v16; // edx
  int v17; // [esp+0h] [ebp-20h]
  int v18; // [esp+4h] [ebp-1Ch]
  int v19; // [esp+8h] [ebp-18h]

  if ( a1 )
  {
    v17 = Class_Enum(a1, dword_54E6A4);
    Rules_SetConstructNextInModule(a1, 0);
  }
  else
  {
    v4 = Class_Enum(0, dword_54E6A4);
    v5 = v4;
    if ( v4 )
      v4 = Class_Enum(v4, dword_54E6A4);
    v17 = v4;
  }
  v19 = v5;
  for ( i = 0; v5; v5 = Class_Enum(v5, dword_54E6A4) )
    i += *(_DWORD *)(v5 + 32);
  v7 = 2 * i;
  a2[1] = 4;
  a2[4] = v7 - 1;
  a2[3] = 0;
  result = Rules_CreateEphemeralMultifield(v7);
  v10 = v19;
  v11 = result;
  a2[2] = result;
  if ( v19 )
  {
    do
    {
      if ( *(_DWORD *)(v10 + 32) )
      {
        v12 = 0;
        do
        {
          v13 = 6 * (v9 - 1);
          v18 = v9;
          *(_WORD *)((char *)v11 + v13 + 14) = 2;
          *(_DWORD *)((char *)v11 + v13 + 16) = Rules_GetConstructNameSymbol(v10);
          *((_WORD *)v11 + 3 * v18 + 7) = 1;
          v12 += 40;
          *(_DWORD *)((char *)v11 + 6 * v14 + 16) = Rules_AddIntegerValue(*(_DWORD *)(v12 + *(_DWORD *)(v10 + 28) - 40));
          v9 = v15 + 1;
        }
        while ( v16 < *(_DWORD *)(v10 + 32) );
      }
      result = (_DWORD *)Class_Enum(v10, dword_54E6A4);
      v10 = (int)result;
    }
    while ( result );
  }
  if ( v19 )
    return (_DWORD *)Rules_SetConstructNextInModule(v19, v17);
  return result;
}
// 497EA3: variable 'v5' is possibly undefined
// 497F0A: variable 'v9' is possibly undefined
// 497F3C: variable 'v14' is possibly undefined
// 497F57: variable 'v15' is possibly undefined
// 497F5A: variable 'v16' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497FC0) --------------------------------------------------------
int * Defgeneric_GetMethodRestrictionsCommand(_DWORD *a1, int a2, double a3)
{
  int v5; // edi
  _DWORD v7[2]; // [esp-8h] [ebp-2Ch] BYREF
  int v8; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  if ( Lexer_ParseValueList(1, v7, 2, a3)
    && (v5 = Defgeneric_CheckGenericExists((int)aGetMethodRestr, *(_BYTE **)(v8 + 16))) != 0
    && Lexer_ParseValueList(2, v7, 1, a3)
    && Defgeneric_CheckMethodExists((int)aGetMethodRestr, v5, *(_DWORD *)(v8 + 16)) != -1 )
  {
    return Defgeneric_BuildMethodRestrictionsValue(v5, *(_DWORD *)(v8 + 16), a1);
  }
  else
  {
    return Rules_SetMultifieldErrorValue((int)a1);
  }
}

//----- (00498060) --------------------------------------------------------
int * Defgeneric_BuildMethodRestrictionsValue(int a1, int a2, _DWORD *a3)
{
  signed int v4; // eax
  int v5; // ecx
  int v6; // edx
  signed int v7; // ecx
  signed int v8; // eax
  int v9; // edx
  _DWORD *v10; // eax
  int v11; // ecx
  _DWORD *v12; // ebx
  int *result; // eax
  int v14; // edx
  signed int v15; // edx
  _DWORD *v16; // edi
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
  signed int v33; // [esp+10h] [ebp-1Ch]
  signed int *v34; // [esp+14h] [ebp-18h]
  _DWORD *v35; // [esp+18h] [ebp-14h]

  v4 = Method_FindByIndex(a1, a2);
  v6 = 40 * v4 + *(_DWORD *)(v5 + 28);
  v7 = 3;
  v34 = (signed int *)v6;
  v8 = 0;
  if ( *(int *)(v6 + 8) > 0 )
  {
    v9 = *(_DWORD *)(v6 + 28);
    do
    {
      v7 += *(_DWORD *)(v9 + 8) + 3;
      ++v8;
      v9 += 12;
    }
    while ( v8 < v34[2] );
  }
  v10 = Rules_CreateEphemeralMultifield(v7);
  a3[1] = 4;
  a3[3] = 0;
  a3[2] = v10;
  v12 = v10;
  a3[4] = v11 - 1;
  v35 = v10;
  *((_WORD *)v10 + 7) = 1;
  v10[4] = Rules_AddIntegerValue(v34[3]);
  *((_WORD *)v12 + 10) = 1;
  *(_DWORD *)((char *)v12 + 22) = Rules_AddIntegerValue(v34[4]);
  *((_WORD *)v12 + 13) = 1;
  v12[7] = Rules_AddIntegerValue(v34[2]);
  v33 = 0;
  result = v34;
  v31 = 4;
  v15 = *(_DWORD *)(v14 + 8) + 4;
  if ( v34[2] > 0 )
  {
    v30 = (char *)v12 + 18;
    v32 = 0;
    do
    {
      v16 = (_DWORD *)(v32 + v34[7]);
      *((_WORD *)v30 + 7) = 1;
      v17 = Rules_AddIntegerValue(v15);
      *(_DWORD *)(v19 + 16) = v17;
      *((_WORD *)v35 + 3 * v18 + 4) = 2;
      v30 += 6;
      ++v31;
      if ( v16[1] )
        v20 = dword_54DD64;
      else
        v20 = dword_54DD70;
      *(_DWORD *)((char *)v35 + 6 * v18 + 10) = v20;
      *((_WORD *)v35 + 3 * v18 + 7) = 1;
      result = Rules_AddIntegerValue(v16[2]);
      *(_DWORD *)(v21 + 16) = result;
      v15 = v22 + 1;
      v23 = 0;
      if ( v16[2] )
      {
        v24 = 0;
        v25 = (char *)v35 + 6 * v15 - 6;
        do
        {
          *((_WORD *)v25 + 7) = 2;
          v25 += 6;
          ++v23;
          v26 = (char *)v35 + 6 * v15 - 6;
          v27 = (char *)Rules_GetConstructNameString(*(_DWORD *)(v24 + *v16));
          *((_DWORD *)v26 + 4) = Str_Intern(v27, v28);
          v15 = v29 + 1;
          result = (int *)v16[2];
        }
        while ( v23 < (unsigned int)result );
      }
      v32 += 12;
      ++v33;
    }
    while ( v33 < v34[2] );
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
int  Defgeneric_EvaluateGenericFunctionCall(int a1, _DWORD *a2, double a3)
{
  int v4; // eax

  Method_DispatchGenericCall(a1, 0, *(_DWORD **)(dword_51A960 + 6), 0, a3, a2);
  if ( a2[1] == 2 && (v4 = a2[2], v4 == dword_54DD70) )
    return dword_54DD70 ^ v4;
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
int  Defgeneric_SaveConstructs(signed int a1)
{
  return Rules_SaveConstruct(a1, dword_54E6A0);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (004982F0) --------------------------------------------------------
signed int Defmethod_SaveConstructs()
{
  return Rules_DoForAllConstructs((void (*)(void))Defgeneric_WriteMethodPPForms, 0);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00498310) --------------------------------------------------------
signed int  Defgeneric_WriteMethodPPForms(signed int result, signed int a2)
{
  signed int v2; // edi
  signed int v3; // ecx
  unsigned int v4; // ebx
  int v5; // esi
  char *v6; // edx
  int v7; // ecx

  v2 = result;
  v3 = a2;
  v4 = 0;
  if ( *(_DWORD *)(result + 32) )
  {
    v5 = 0;
    do
    {
      result = v5 + *(_DWORD *)(v2 + 28);
      v6 = *(char **)(result + 36);
      if ( v6 )
      {
        Output_WriteLongString(v3, v6);
        result = Output_Write(v7, (int)asc_50537C, v7);
      }
      ++v4;
      v5 += 40;
    }
    while ( v4 < *(_DWORD *)(v2 + 32) );
  }
  return result;
}
// 498343: variable 'v3' is possibly undefined
// 49834F: variable 'v7' is possibly undefined

//----- (00498360) --------------------------------------------------------
signed int  Defgeneric_DeleteMethod(int a1, int a2)
{
  int v2; // edx
  int v3; // edx
  unsigned int v4; // ebx
  char *v5; // eax
  int v6; // edx
  char *v7; // ebp
  signed int result; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  signed int v14; // [esp+0h] [ebp-14h]

  v2 = 40 * a2 + *(_DWORD *)(a1 + 28);
  if ( (*(_BYTE *)(v2 + 24) & 1) != 0 )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)aGenrccom, v9, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRemoveIm, v10);
    v11 = Rules_GetConstructNameString(a1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v11, v12);
    return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__15, v13);
  }
  else
  {
    Defgeneric_DeleteMethodInfo(a1, v2);
    v3 = *(_DWORD *)(a1 + 32);
    if ( v3 == 1 )
    {
      Mem_SmallBlockFree(*(_DWORD **)(a1 + 28), 40);
      result = a1;
      *(_DWORD *)(a1 + 32) = 0;
      *(_DWORD *)(a1 + 28) = 0;
    }
    else
    {
      *(_DWORD *)(a1 + 32) = v3 - 1;
      v4 = 0;
      v5 = (char *)Mem_SmallBlockAlloc(40 * (v3 - 1));
      v14 = (signed int)v5;
      if ( *(_DWORD *)(a1 + 32) )
      {
        v7 = v5;
        do
        {
          if ( v4 == a2 )
            ++v6;
          qmemcpy(v7, (const void *)(40 * v6 + *(_DWORD *)(a1 + 28)), 0x28u);
          ++v4;
          v7 += 40;
          ++v6;
        }
        while ( v4 < *(_DWORD *)(a1 + 32) );
      }
      Mem_SmallBlockFree(*(_DWORD **)(a1 + 28), 40 * (*(_DWORD *)(a1 + 32) + 1));
      result = v14;
      *(_DWORD *)(a1 + 28) = v14;
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
int __fastcall Defgeneric_PrintMethodsList(int a1, int a2)
{
  unsigned int v3; // ebp
  int v4; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char v12[276]; // [esp+0h] [ebp-114h] BYREF

  v3 = 0;
  if ( *(_DWORD *)(a2 + 32) )
  {
    v4 = 0;
    do
    {
      v5 = Rules_GetConstructNameString(a2);
      Output_Write(v6, v5, v6);
      Output_Write(v7, (int)asc_505344, v7);
      Defgeneric_AppendMethodSignatureText(v12, 255, v8, v4 + *(_DWORD *)(a2 + 28));
      Output_Write(v9, (int)v12, v9);
      ++v3;
      Output_Write(v10, (int)asc_50537C, v10);
      v4 += 40;
    }
    while ( v3 < *(_DWORD *)(a2 + 32) );
  }
  return *(_DWORD *)(a2 + 32);
}
// 4984F5: variable 'v6' is possibly undefined
// 498501: variable 'v7' is possibly undefined
// 498512: variable 'v8' is possibly undefined
// 49851B: variable 'v9' is possibly undefined
// 498528: variable 'v10' is possibly undefined

//----- (00498550) --------------------------------------------------------
signed int  Defgeneric_WatchAccessFunction(int a1, int a2, double a3)
{
  return Rules_ApplyWatchFlagCommand(dword_54E6A0, a1, (int)Defgeneric_GetTraceFlag, a2, a3, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498570) --------------------------------------------------------
signed int  Defgeneric_WatchPrintFunction(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(dword_54E6A0, a1, (int)Defgeneric_GetTraceFlag, a2, a3, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498590) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchAccessFunction(int a1, int a2, double a3)
{
  if ( a1 )
    return Defgeneric_WatchMethodsDispatch((int)aWatch_1, 0, 0, a1, 0, a3, (void (*)(void))Defgeneric_SetMethodTraceFlag, a2);
  else
    return Defgeneric_WatchMethodsDispatch((int)aUnwatch_0, 0, 0, 0, 0, a3, (void (*)(void))Defgeneric_SetMethodTraceFlag, a2);
}

//----- (004985C0) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchPrintFunction(int a1, int a2, int a3, double a4)
{
  return Defgeneric_WatchMethodsDispatch((int)aListWatchIte_1, a1, (void (*)(void))Method_PrintWatchStatusLine, -1, a3, a4, 0, a2);
}

//----- (004985E0) --------------------------------------------------------
signed int  Defgeneric_WatchMethodsDispatch(
        int a1,
        int a2,
        void (*a3)(void),
        int a4,
        int i,
        double a6,
        void (*a7)(void),
        int a8)
{
  int v9; // ecx
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int k; // esi
  int m; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ebx
  int v19; // ecx
  int v20; // ecx
  _DWORD v21[2]; // [esp+0h] [ebp-50h] BYREF
  int v22; // [esp+8h] [ebp-48h]
  _DWORD v23[8]; // [esp+18h] [ebp-38h] BYREF
  int j; // [esp+38h] [ebp-18h]
  int v25; // [esp+3Ch] [ebp-14h]
  void (*v26)(void); // [esp+40h] [ebp-10h]

  v23[7] = a1;
  v23[6] = a4;
  v26 = a3;
  v9 = a8;
  v25 = 2;
  if ( a8 )
  {
    while ( 1 )
    {
      if ( !a8 )
        return 1;
      if ( Parser_ParseForm((__int16 *)a8, v23, v9, a6) )
        return 0;
      if ( v23[1] != 2 || (v17 = Symbol_LookupInModule((char **)dword_54E6A0, *(_BYTE **)(v23[2] + 16), 1)) == 0 )
      {
        Parser_ReportError(v25, (int)aGenericFunct_4);
        return 0;
      }
      v18 = *(_DWORD *)(a8 + 10);
      if ( !v18 )
        goto LABEL_20;
      ++v25;
      a8 = v18;
      if ( Parser_ParseForm((__int16 *)v18, v21, v17, a6) )
        return 0;
      if ( v21[1] != 1 || *(int *)(v22 + 16) <= 0 || Method_FindByIndex(v20, i) == -1 )
      {
        Parser_ReportError(v25, (int)aMethodIndex);
        return 0;
      }
      i = *(_DWORD *)(v22 + 16);
      if ( i )
      {
        if ( a7 )
          ((void (__fastcall *)(int, int))a7)(v17, v17);
        else
          ((void (__fastcall *)(int, int))v26)(v17, v17);
        a8 = *(_DWORD *)(v18 + 10);
        ++v25;
      }
      else
      {
LABEL_20:
        for ( i = Class_NextMethod(v17, 0); i; i = Class_NextMethod(v19, i) )
        {
          if ( a7 )
            ((void (__fastcall *)(int, int))a7)(v9, v9);
          else
            ((void (__fastcall *)(int, int))v26)(v9, v9);
        }
        a8 = *(_DWORD *)(a8 + 10);
        ++v25;
      }
    }
  }
  Module_BeginEnum();
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    if ( !a7 )
    {
      Name = Module_GetName(j);
      Output_Write(a2, Name, v12);
      Output_Write(a2, (int)asc_5053F0, v13);
    }
    for ( k = Class_Enum(0, dword_54E6A4); k; k = Class_Enum(k, dword_54E6A4) )
    {
      for ( m = Class_NextMethod(k, 0); m; m = Class_NextMethod(k, v16) )
      {
        if ( a7 )
        {
          a7();
        }
        else
        {
          Output_Write(a2, (int)asc_5053F4, m);
          v26();
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
signed int  Method_PrintWatchStatusLine(int a1, int a2, int a3)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char v11[76]; // [esp+0h] [ebp-4Ch] BYREF

  v5 = Rules_GetConstructNameString(a2);
  Output_Write(a1, v5, a3);
  Output_Write(a1, (int)asc_505420, v6);
  Defgeneric_FormatMethodRestrictionsString(v11, 59, v7, a2);
  Output_Write(a1, (int)v11, v8);
  if ( Defgeneric_GetMethodTraceFlag(a2, a3) )
    return Output_Write(a1, (int)aOn_3, v9);
  else
    return Output_Write(a1, (int)aOff_3, v9);
}
// 498898: variable 'v6' is possibly undefined
// 4988A4: variable 'v7' is possibly undefined
// 4988AD: variable 'v8' is possibly undefined
// 4988C6: variable 'v9' is possibly undefined

//----- (004988F0) --------------------------------------------------------
int Deffunction_InitConstructType()
{
  int v0; // ecx

  Rules_RegisterEvaluationHandler((int)&unk_51AAEC, 12);
  dword_54E6A8 = Module_RegisterItem(
                   (int)aDeffunction,
                   (int)Deffunction_AllocateModule,
                   (int)Deffunction_RecordAtIndex,
                   (int)Deffunction_FreeModule,
                   (int)Deffunction_WriteModuleItemReference,
                   (int)Deffunction_FindByName);
  dword_54E6AC = (int)Rules_RegisterConstructType(
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
  return Rules_AddWatchItem((int)aDeffunctions, 0, 32, (int)&dword_51AAE8, (int)Deffunction_SetWatchAll, (int)Deffunction_GetWatchAll);
}
// 4989CE: variable 'v0' is possibly undefined
// 51AAE8: using guessed type int dword_51AAE8;
// 54E6A8: using guessed type int dword_54E6A8;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498A80) --------------------------------------------------------
int  Deffunction_FindByName(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498AB0) --------------------------------------------------------
int  Deffunction_LookupByName(_BYTE *a1)
{
  return Symbol_LookupInModule((char **)dword_54E6AC, a1, 0);
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
int  Deffunction_EnumNext(int a1)
{
  return Class_Enum(a1, dword_54E6A8);
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
    dword_54DBAC = (int)v7;
    *v7 = *(_DWORD *)(dword_54DBA8 + 184);
    result = dword_54DBA8;
    *(_DWORD *)(dword_54DBA8 + 184) = dword_54DBAC;
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
  return Rules_UndefconstructCommand((int)this, dword_54E6AC);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BD0) --------------------------------------------------------
int __thiscall Deffunction_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)dword_54E6AC);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BF0) --------------------------------------------------------
int __thiscall Deffunction_PPCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)dword_54E6AC);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C10) --------------------------------------------------------
int  Deffunction_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(dword_54E6AC, a1, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C50) --------------------------------------------------------
_DWORD * Deffunction_GetListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, dword_54E6AC, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C90) --------------------------------------------------------
int  Deffunction_CheckArgumentCount(int result, int a2)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // eax

  if ( result )
  {
    v2 = *(_DWORD *)(result + 34);
    if ( a2 >= v2 )
    {
      if ( a2 <= v2 || *(_DWORD *)(result + 38) == -1 )
        return 1;
    }
    else if ( *(_DWORD *)(result + 38) == -1 )
    {
      v3 = *(_DWORD *)(result + 34);
LABEL_5:
      v4 = Rules_GetConstructNameString(result);
      Rules_ExpectedCountError(v4, v3);
      return 0;
    }
    v3 = *(_DWORD *)(result + 34);
    goto LABEL_5;
  }
  return result;
}

//----- (00498CE0) --------------------------------------------------------
int  Deffunction_CallForBooleanResult(int a1, _DWORD *a2, double a3)
{
  int v3; // ecx
  int v4; // eax

  Deffunction_CallDeffunction(a1, *(_DWORD **)(dword_51A960 + 6), a2, a3);
  if ( *(_DWORD *)(v3 + 4) == 2 && (v4 = *(_DWORD *)(v3 + 8), v4 == dword_54DD70) )
    return dword_54DD70 ^ v4;
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
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = *v0;
  return dword_54DBAC;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00498D70) --------------------------------------------------------
int  Deffunction_FreeModule(int a1)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(a1, dword_54E6AC, a1);
  freed_node = (_DWORD *)a1;
  dword_54DBAC = a1;
  *freed_node = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498DB0) --------------------------------------------------------
BOOL Deffunction_IsClearReady()
{
  return dword_51B3E8 == 0;
}
// 51B3E8: using guessed type int dword_51B3E8;

//----- (00498DC0) --------------------------------------------------------
signed int Deffunction_ClearAll()
{
  int v0; // ebx
  int i; // ecx
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // esi
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

  v0 = 1;
  if ( Rules_IsBloaded() == 1 )
    return 0;
  for ( i = Class_Enum(0, dword_54E6A8); i; i = Class_Enum(v5, dword_54E6A8) )
  {
    if ( *(_DWORD *)(i + 24) )
    {
      v3 = Rules_GetConstructNameString(i);
      Deffunction_ReportCantDelete(v3, v4);
      v0 = 0;
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
  v6 = Class_Enum(0, dword_54E6A8);
  if ( !v6 )
    return v0;
  do
  {
    while ( 1 )
    {
      v6 = Class_Enum(v6, dword_54E6A8);
      if ( !*(_DWORD *)(v7 + 24) )
        break;
LABEL_11:
      if ( !v6 )
        return v0;
    }
    if ( *(_DWORD *)(v7 + 20) )
    {
      Rules_PrintWarningID((int)aDffnxfun, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aDeffunction_6, v8);
      v10 = Rules_GetConstructNameString(v9);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], v10, v11);
      Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aOnlyPartiallyD, v12);
      v0 = 0;
      Rules_ReplaceConstructPPForm(v13, 0);
      goto LABEL_11;
    }
    Rules_UnlinkListNode(v7);
    Deffunction_Free(v17);
  }
  while ( v6 );
  return v0;
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
signed int  Deffunction_ReportCantDelete(int a1, int a2)
{
  return Rules_ReportCantDeleteItem(a2, a1);
}

//----- (00498F00) --------------------------------------------------------
signed int Deffunction_SaveHeaders()
{
  return Rules_DoForAllConstructs((void (*)(void))Deffunction_WriteHeaderForm, 0);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498F20) --------------------------------------------------------
int  Deffunction_WriteHeaderForm(int a1, int a2)
{
  int result; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int i; // ebx
  int v12; // ecx

  result = Rules_GetModuleConstructListHead(a1);
  if ( result )
  {
    Output_Write(a2, (int)aDeffunction_1, v6);
    v7 = Rules_GetConstructNameString(a1);
    Output_Write(a2, v7, v8);
    Output_Write(a2, (int)asc_5055B4, v9);
    for ( i = 0; i < *(_DWORD *)(a1 + 34); ++i )
    {
      Output_Write(v10, (int)aQuestionP_DeffunctionArgumentPrefix, v10);
      Rules_PrintLongInteger(v12, i);
      if ( i != *(_DWORD *)(a1 + 34) - 1 )
        Output_Write(v10, (int)asc_5055BC, v10);
    }
    if ( *(_DWORD *)(a1 + 38) == -1 )
    {
      if ( *(_DWORD *)(a1 + 34) )
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
int  Deffunction_SaveBodies(signed int a1)
{
  return Rules_SaveConstruct(a1, dword_54E6AC);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498FF0) --------------------------------------------------------
signed int  Deffunction_SetWatchAll(int a1, int a2, double a3)
{
  return Rules_ApplyWatchFlagCommand(dword_54E6AC, a1, (int)Deffunction_GetWatchFlagField, a2, a3, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499010) --------------------------------------------------------
signed int  Deffunction_GetWatchAll(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(dword_54E6AC, a1, (int)Deffunction_GetWatchFlagField, a2, a3, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499030) --------------------------------------------------------
__int16  Deffunction_SetWatchFlagField(__int16 result, int a2)
{
  *(_WORD *)(a2 + 28) = result;
  return result;
}

//----- (00499040) --------------------------------------------------------
int  Deffunction_GetWatchFlagField(int a1)
{
  return *(unsigned __int16 *)(a1 + 28);
}

//----- (00499050) --------------------------------------------------------
_DWORD *Defglobal_InitConstructType()
{
  _DWORD *result; // eax

  unk_51AB20[4] = (int)(uintptr_t)Defglobal_EvaluateReference;
  unk_51AB50[4] = (int)(uintptr_t)Mem_CopyDataObjectRecord;
  unk_51AB50[6] = (int)(uintptr_t)Class_DecrementBusyCount;
  unk_51AB50[7] = (int)(uintptr_t)Class_IncrementBusyCount;
  Rules_RegisterEvaluationHandler((int)&unk_51AB20, 13);
  Rules_RegisterEvaluationHandler((int)&unk_51AB50, 60);
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
  dword_54E6B4 = (int)result;
  return result;
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004990D0) --------------------------------------------------------
int *Defglobal_RegisterModuleItem()
{
  dword_54E6B0 = Module_RegisterItem(
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
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = *v0;
  return dword_54DBAC;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499140) --------------------------------------------------------
int  Defglobal_FreeModule(int a1)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(a1, dword_54E6B4, a1);
  freed_node = (_DWORD *)a1;
  dword_54DBAC = a1;
  *freed_node = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B4: using guessed type int dword_54E6B4;

//----- (00499190) --------------------------------------------------------
int  Defglobal_FindByName(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004991A0) --------------------------------------------------------
int  Defglobal_EnumNext(int a1)
{
  return Class_Enum(a1, dword_54E6B0);
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
    dword_54DBAC = (int)v4;
    *v4 = *(_DWORD *)(dword_54DBA8 + 224);
    result = dword_54DBAC;
    *(_DWORD *)(dword_54DBA8 + 224) = dword_54DBAC;
    dword_51AB1C = 1;
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
int  Defglobal_SetValue(int a1, _DWORD *a2, int a3, double a4)
{
  int record; // ecx
  int new_type; // eax
  int result; // eax

  record = a1;
  if ( a3 )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 52), a2, a1, a4);
    if ( dword_51A964 )
    {
      a2[1] = 2;
      a2[2] = dword_54DD70;
    }
  }
  if ( (*(_BYTE *)(record + 20) & 1) != 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aDefglobalWatchPrefix, record);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)record + 16), record);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_5055F8, record);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WTrace[0], (int)a2);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_505600, record);
    Rules_PrintDataObject((int)g_IO_LogicalNameTable_WTrace[0], record + 28);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_505608, record);
  }
  Rules_ValueDeinstall(record + 28, record);
  if ( *(_DWORD *)(record + 32) == 4 )
    Rules_ReturnMultifieldToPool((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(record + 36));
  new_type = a2[1];
  *(_DWORD *)(record + 32) = new_type;
  if ( new_type == 4 )
    Rules_AssignMultifieldRangeCopy((_DWORD *)(record + 28), (int)a2);
  else
    *(_DWORD *)(record + 36) = a2[2];
  Rules_ValueInstall(record + 28, record);
  result = dword_51A96C;
  dword_51AB1C = 1;
  if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
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

  result = (_DWORD *)Class_Enum(0, dword_54E6B0);
  if ( !result )
    return 0;
  while ( v1 != *result )
  {
    result = (_DWORD *)Class_Enum((int)result, dword_54E6B0);
    if ( !result )
      return 0;
  }
  return result;
}
// 499377: variable 'v1' is possibly undefined
// 54E6B0: using guessed type int dword_54E6B0;

//----- (00499410) --------------------------------------------------------
signed int  Defglobal_EvaluateReference(int a1, _DWORD *a2, int a3)
{
  _DWORD *v5; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a3;
  v5 = (_DWORD *)Rules_FindImportExportConstruct(aDefglobal, v10, *(_BYTE **)(a1 + 16), 1, 0);
  if ( !v5 )
  {
    Rules_PrintErrorID((int)aGlobldef, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGlobalVariab_0, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(a1 + 16), v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUnbound_, v9);
    goto LABEL_4;
  }
  if ( v10[0] > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)aDefglobal, *(_DWORD *)(a1 + 16));
LABEL_4:
    a2[1] = 2;
    a2[2] = dword_54DD70;
    Lexer_ErrorRecover(1);
    return 0;
  }
  Mem_CopyDataObjectRecord(v5, a2);
  return 1;
}
// 499487: variable 'v7' is possibly undefined
// 499494: variable 'v8' is possibly undefined
// 4994A3: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (004994C0) --------------------------------------------------------
signed int  Mem_CopyDataObjectRecord(_DWORD *a1, _DWORD *a2)
{
  int v2; // eax
  int v3; // ebx
  _DWORD *v5; // eax
  int v6; // edx
  int v7; // ebx
  int v8; // ecx

  a2[1] = a1[8];
  a2[2] = a1[9];
  a2[3] = a1[10];
  v2 = a1[11];
  v3 = a2[1];
  a2[4] = v2;
  if ( v3 == 4 )
  {
    v5 = Rules_CreateEphemeralMultifield(v2 + 1);
    v7 = *(_DWORD *)(v6 + 16) + 1;
    *(_DWORD *)(v6 + 8) = v5;
    qmemcpy(
      (void *)(*(_DWORD *)(v6 + 8) + 14),
      (const void *)(6 * *(_DWORD *)(v8 + 40) + *(_DWORD *)(v8 + 36) + 14),
      6 * v7);
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
  _DWORD v3[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    for ( j = *(_BYTE **)(Module_GetItem(i, dword_54E6B0) + 4); j; j = (_BYTE *)Class_Enum((int)j, dword_54E6B0) )
    {
      if ( Rules_FindImportExportConstruct(aDefglobal, v3, *(_BYTE **)(*(_DWORD *)j + 16), 1, 0) )
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
  dword_54E6FC = (int)Str_Intern(aIsA, 0);
  ++*(_DWORD *)(dword_54E6FC + 4);
  dword_54E6F8 = (int)Str_Intern(aName, 0);
  ++*(_DWORD *)(dword_54E6F8 + 4);
  dword_54E6F4 = (int)Str_Intern(aInitialObject, 0);
  ++*(_DWORD *)(dword_54E6F4 + 4);
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

  Class_InternSlotName((_DWORD *)dword_54E6FC, 0, 1);
  Class_InternSlotName((_DWORD *)dword_54E6F8, 1, 1);
  object_class = Class_CreateSystemClass(aObject_0, 0, 0);
  primitive_class = Class_CreateSystemClass(aPrimitive, object_class, 0);
  user_class = Class_CreateSystemClass(aUser, object_class, 0);
  number_class = Class_CreateSystemClass(aNumber_1, primitive_class, 0);
  dword_51AD80 = Class_CreateSystemClass(aInteger_2, number_class, 0);
  dword_51AD7C[0] = Class_CreateSystemClass(aFloat_2, number_class, 0);
  lexeme_class = Class_CreateSystemClass(aLexeme_0, primitive_class, 0);
  dword_51AD84 = Class_CreateSystemClass(aSymbol_3, lexeme_class, 0);
  dword_51AD88 = Class_CreateSystemClass(aString_2, lexeme_class, 0);
  dword_51AD8C = Class_CreateSystemClass(aMultifield_1, primitive_class, 0);
  address_class = Class_CreateSystemClass(aAddress_0, primitive_class, 0);
  dword_51AD90 = Class_CreateSystemClass(aExternalAddr_0, address_class, 0);
  dword_51AD94 = Class_CreateSystemClass(aFactAddress_1, address_class, 0);
  instance_class = Class_CreateSystemClass(aInstance_3, primitive_class, 0);
  dword_51AD98 = Class_CreateSystemClass(aInstanceAddr_7, instance_class, 0);
  dword_51AD9C = Class_CreateSystemClass(aInstanceName_2, instance_class, 0);
  initial_object_class = Class_CreateSystemClass(aInitialObjec_0, user_class, 0);
  initial_object_flags = *(_BYTE *)(initial_object_class + 20) & 0xFB;
  *(_BYTE *)(initial_object_class + 20) = initial_object_flags;
  *(_BYTE *)(initial_object_class + 20) = initial_object_flags | 8;
  Class_InsertLinkEntry((unsigned __int16 *)(dword_51AD98 + 34), address_class, -1);
  Class_InsertLinkEntry((unsigned __int16 *)(dword_51AD98 + 46), address_class, 2);
  Class_InsertLinkEntry((unsigned __int16 *)(address_class + 40), dword_51AD98, -1);
  Rules_AppendConstructToModuleList(dword_51AD7C[0]);
  Rules_AppendConstructToModuleList(dword_51AD80);
  Rules_AppendConstructToModuleList(dword_51AD84);
  Rules_AppendConstructToModuleList(dword_51AD88);
  Rules_AppendConstructToModuleList(dword_51AD8C);
  Rules_AppendConstructToModuleList(dword_51AD90);
  Rules_AppendConstructToModuleList(dword_51AD94);
  Rules_AppendConstructToModuleList(dword_51AD98);
  Rules_AppendConstructToModuleList(dword_51AD9C);
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

  Rules_RegisterEvaluationHandler((int)&unk_51AB88, 57);
  dword_54E6BC = Module_RegisterItem(
                   (int)aDefclass,
                   (int)Class_AllocRecord,
                   (int)Class_RecordAtIndex,
                   (int)Class_FreeRecord,
                   (int)ObjectsCompiler_WriteModuleItemHeaderRef,
                   (int)Class_LookupCurrentScopedName);
  dword_54E6B8 = (int)Rules_RegisterConstructType(
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
  Rules_AddWatchItem((int)aInstances_0, 0, 75, (int)&dword_51AD74, (int)Class_SetWatchFlagCommand, (int)Class_SetWatchFlagForModuleCommand);
  return Rules_AddWatchItem((int)aSlots, 1, 74, (int)dword_51AD78, (int)Class_SetWatchFlagCommand, (int)Class_SetWatchFlagForModuleCommand);
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
  *(_DWORD *)(class_record + 100) = *(_DWORD *)(dword_51AD68 + 4 * *(_DWORD *)(class_record + 30));
  *(_DWORD *)(dword_51AD68 + 4 * *(_DWORD *)(class_record + 30)) = class_record;
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
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = *v0;
  return dword_54DBAC;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499F50) --------------------------------------------------------
int  Class_FreeRecord(int a1)
{
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  _DWORD *freed_node; // ecx
  int result; // eax

  Rules_ClearModuleConstructList(a1, dword_54E6B8, a1);
  v1 = (_DWORD *)Class_FindSlotNameEntryByID(0);
  Class_ReleaseSlotName(v1);
  v2 = (_DWORD *)Class_FindSlotNameEntryByID(1);
  Class_ReleaseSlotName(v2);
  freed_node = (_DWORD *)a1;
  dword_54DBAC = a1;
  *freed_node = *(_DWORD *)(dword_54DBA8 + 48);
  result = dword_54DBA8;
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 499F7F: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B8: using guessed type int dword_54E6B8;

//----- (00499FA0) --------------------------------------------------------
signed int Class_RefreshWatchExpressions()
{
  int v0; // eax
  int v1; // edx
  int v2; // ecx
  int *v3; // ebp
  _BYTE *v4; // edi
  int v5; // ebx
  _BYTE *v6; // ebx
  int v7; // eax
  int v9; // [esp+0h] [ebp-34h] BYREF
  _BYTE *v10; // [esp+4h] [ebp-30h]
  int v11; // [esp+8h] [ebp-2Ch]
  int v12; // [esp+Ch] [ebp-28h]
  int v13; // [esp+10h] [ebp-24h]
  int v14; // [esp+14h] [ebp-20h]
  _BYTE *v15; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  v0 = Module_GetModuleCount();
  v14 = ((v0 - (__CFSHL__(v0 >> 31, 3) + 8 * (v0 >> 31))) >> 3) + 1;
  v15 = Mem_SmallBlockAlloc(v14);
  v11 = 0;
  v10 = &v15[(v2 - (__CFSHL__(v1 >> 31, 3) + 8 * (v1 >> 31))) >> 3];
  v13 = 1 << (v2 % 8);
  do
  {
    v3 = *(int **)(v11 + dword_51AD68);
    if ( v3 )
    {
      v4 = v15;
      do
      {
        v5 = *v3;
        v12 = *(_DWORD *)v3[2];
        v6 = *(_BYTE **)(v5 + 16);
        Mem_AllocArray(v15, v14);
        qmemcpy(v4, *(const void **)(v3[26] + 16), *(unsigned __int16 *)(v3[26] + 20));
        Rules_DecrementBitmapCount(v3[26], 0);
        if ( (v3[5] & 2) != 0 || Rules_FindImportExportConstruct(aDefclass, &v9, v6, 1, 0) )
          *v10 |= v13;
        v7 = Rules_AddBitmapValue(v15, v14);
        v3[26] = v7;
        ++*(_DWORD *)(v7 + 4);
        v3 = (int *)v3[25];
      }
      while ( v3 );
    }
    v11 += 4;
  }
  while ( v11 != 668 );
  return Mem_SmallBlockFree(v15, v14);
}
// 499FDD: variable 'v2' is possibly undefined
// 499FCF: variable 'v1' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (0049A0E0) --------------------------------------------------------
int __cdecl ProcParam_RegisterPrimitiveTypes(void)
{
  Rules_RegisterEvaluationHandler((int)&unk_51ABD4, 65);
  Rules_RegisterEvaluationHandler((int)&unk_51AC04, 66);
  Rules_RegisterEvaluationHandler((int)&unk_51AC34, 67);
  return Rules_RegisterEvaluationHandler((int)&unk_51AC64, 68);
}

//----- (0049A120) --------------------------------------------------------
int  Parser_ParseProcParameters(
        int a1,
        _DWORD *a2,
        _DWORD *a3,
        int a4,
        _DWORD *a5,
        _DWORD *a6,
        _DWORD *a7,
        int (*a8)(void))
{
  _DWORD *v8; // esi
  int v9; // edi
  int i; // eax
  int j; // eax
  _DWORD *v13; // ecx
  int v14; // edx
  int v15; // eax
  signed int v16; // eax
  _DWORD *v17; // ecx
  int v19; // ecx
  int v20; // ecx
  int v22; // [esp+4h] [ebp-10h]

  v8 = a2;
  v9 = a4;
  *a3 = 0;
  *a5 = 0;
  v22 = 0;
  *a7 = 1;
  for ( i = a4; i; i = *(_DWORD *)(i + 10) )
  {
    ++*a5;
    a4 = i;
  }
  if ( *a2 == 100 )
  {
    for ( j = a1; ; j = a1 )
    {
      Parser_NextToken(j, (int)a2);
      v14 = *v8;
      if ( *v8 != 15 && v14 != 16 )
        break;
      v15 = v9;
      if ( v9 )
      {
        while ( *(_DWORD *)(v15 + 2) != v8[1] )
        {
          v15 = *(_DWORD *)(v15 + 10);
          if ( !v15 )
            goto LABEL_9;
        }
        Rules_PrintErrorID((int)aPrccode_0, 7, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicatePar_0, v19);
        AST_Free(v9);
        return 0;
      }
LABEL_9:
      if ( *a3 )
      {
        Rules_PrintErrorID((int)aPrccode_0, 8, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoParameters_0, v20);
        AST_Free(v9);
        return 0;
      }
      if ( a8 && a8() )
        goto LABEL_18;
      v16 = AST_NewNode(*v8, v8[1]);
      if ( *v8 == 16 )
        *a3 = v8[1];
      else
        ++*v17;
      if ( a4 )
        *(_DWORD *)(a4 + 10) = v16;
      else
        v9 = v16;
      a4 = v16;
      IO_OutWriteToken(asc_505C54);
      a2 = v8;
      v22 = 1;
    }
    if ( v14 != 101 )
      goto LABEL_17;
    if ( v22 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_505C58);
    }
    *a7 = 0;
    if ( *a3 )
      *a6 = -1;
    else
      *a6 = *v13;
    return v9;
  }
  else
  {
LABEL_17:
    Parser_ReportSyntaxError();
LABEL_18:
    AST_Free(v9);
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
        int a1,
        int a2,
        int a3,
        int a4,
        int (*a5)(void),
        int (*a6)(void),
        int *a7,
        int a8)
{
  unsigned int *v11; // edx
  _DWORD *result; // eax
  _DWORD *v13; // esi
  int v14; // eax
  int v15; // ecx
  _DWORD *v16; // eax
  int v17; // ecx
  int v18; // edx

  Parser_FreeLoopContextStack();
  result = (_DWORD *)Parser_ParseProgram(a2, v11, 1);
  v13 = result;
  if ( result )
  {
    if ( a6 && Parser_ScanBindStatementsForSymbol((int)result, a6, a8) )
    {
      Parser_FreeLoopContextStack();
      v14 = v15;
    }
    else
    {
      *a7 = Rules_CountNamedContextEntries();
      if ( !Parser_ReplaceProcVars(a1, (int)v13, a4, a3, a5, a8) )
      {
        v16 = AST_UnwrapActionListWrapper(v13);
        AST_PackNodeChain(v16);
        AST_Free(v17);
        Parser_FreeLoopContextStack();
        return (_DWORD *)v18;
      }
      Parser_FreeLoopContextStack();
      v14 = (int)v13;
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
        int a1,
        int a2,
        int a3,
        int a4,
        int (*a5)(void),
        int a6)
{
  int v6; // esi
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
  _DWORD *v20; // ebx
  int v21; // eax
  int v22; // eax
  signed int v23; // edx
  _DWORD *v24; // eax
  signed int v25; // [esp+0h] [ebp-28h] BYREF
  signed int v26; // [esp+4h] [ebp-24h] BYREF
  int v27; // [esp+8h] [ebp-20h] BYREF
  int v28; // [esp+Ch] [ebp-1Ch]
  int v29; // [esp+10h] [ebp-18h]
  _DWORD *v30; // [esp+14h] [ebp-14h]
  int v31; // [esp+18h] [ebp-10h]

  v31 = a1;
  v6 = a2;
  v28 = a4;
  v29 = a3;
  if ( !a2 )
    return 0;
  while ( 1 )
  {
    if ( *(_WORD *)v6 == 15 )
    {
      v25 = Parser_FindProcParamIndex(*(_DWORD *)(v6 + 2), v28, v29);
      v9 = Rules_FindNamedContextDepth(v8);
      v26 = v9;
      if ( v25 || v9 )
      {
        if ( v25 <= 0 || v26 )
        {
          if ( a5 )
          {
            v20 = (_DWORD *)AST_NewNode(*(_WORD *)v6, *(_DWORD *)(v6 + 2));
            v30 = v20;
            v21 = a5();
            if ( v21 )
            {
              if ( v21 == -1 )
              {
                dword_54DBAC = (int)v20;
                *v20 = *(_DWORD *)(dword_54DBA8 + 56);
                *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
                return 1;
              }
            }
            else
            {
              dword_54DBAC = (int)v20;
              *v20 = *(_DWORD *)(dword_54DBA8 + 56);
              v30 = 0;
              *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
            }
          }
          else
          {
            v30 = 0;
          }
          *(_WORD *)v6 = 67;
          Mem_AllocArray(&v27, 4);
          LOWORD(v27) = v27 & 1;
          v27 |= 2 * (v26 & 0x7FFF);
          HIWORD(v27) = BYTE2(v27) & 1;
          v27 |= (v25 & 0x7FFF) << 17;
          BYTE2(v27) &= ~1u;
          v27 |= (v16 == v29) << 16;
          *(_DWORD *)(v6 + 2) = Rules_AddBitmapValue(&v27, 4);
          v18 = AST_NewNode(2, v17);
          v19 = v30;
          *(_DWORD *)(v6 + 6) = v18;
          *(_DWORD *)(v18 + 10) = v19;
        }
        else
        {
          *(_WORD *)v6 = (v10 == v29) + 65;
          *(_DWORD *)(v6 + 2) = Rules_AddBitmapValue(&v25, 4);
        }
      }
      else if ( !a5 || a5() != 1 )
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
    else if ( *(_WORD *)v6 == 13 && !Defglobal_ResolveGlobalVariableReference(v6, a3) )
    {
      return -1;
    }
    if ( a5 && ((int (__fastcall *)(int, int))a5)(a3, a6) == -1 )
      return 1;
    a3 = *(_DWORD *)(v6 + 6);
    if ( a3 )
      break;
LABEL_6:
    v6 = *(_DWORD *)(v6 + 10);
    if ( !v6 )
      return 0;
  }
  if ( !Parser_ReplaceProcVars(v31, a3, v29, v28, (int (__fastcall *)(_DWORD, _DWORD))a5, a6) )
  {
    if ( Rules_MakeSymbol(aBind_1) == *(int ***)(v6 + 2) && **(_WORD **)(v6 + 6) == 2 )
    {
      v22 = *(_DWORD *)(v6 + 6);
      *(_WORD *)v6 = 68;
      v26 = Rules_FindNamedContextDepth(*(_DWORD *)(v22 + 2));
      *(_DWORD *)(v6 + 2) = Rules_AddBitmapValue(&v26, v23);
      v24 = *(_DWORD **)(v6 + 6);
      a3 = *(_DWORD *)((char *)v24 + 10);
      dword_54DBAC = (int)v24;
      *v24 = *(_DWORD *)(dword_54DBA8 + 56);
      *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
      *(_DWORD *)(v6 + 6) = a3;
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
signed int  AST_NewProcParamNode(int a1)
{
  int v2; // eax
  int v4; // [esp+0h] [ebp-8h] BYREF

  v4 = a1;
  v2 = Rules_AddBitmapValue(&v4, 4);
  return AST_NewNode(66, v2);
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

  v7 = *(_DWORD **)(dword_54DBA8 + 96);
  if ( v7 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = *v7;
    v8 = (_DWORD *)dword_54DBAC;
  }
  else
  {
    v8 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  *v8 = dword_51ABB8;
  v8[2] = dword_51ABBC;
  v8[4] = dword_51ABD0;
  v8[5] = dword_51ABC4;
  dword_51ABC4 = (int)v8;
  ProcParam_EvaluateArgumentExpressions(a1, a2, a3, a4, a5);
  if ( dword_51A964 )
  {
    v9 = (_DWORD *)dword_51ABC4;
    dword_51ABC4 = *(_DWORD *)(dword_51ABC4 + 20);
    dword_54DBAC = (int)v9;
    *v9 = *(_DWORD *)(dword_54DBA8 + 96);
    result = (int (*)(void))dword_54DBAC;
    *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
  }
  else
  {
    v8[1] = dword_51ABC0;
    dword_51ABC0 = 0;
    v8[3] = dword_51ABC8;
    result = a6;
    dword_51ABC8 = 0;
    dword_51ABD0 = a6;
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
  int *v0; // edx
  int result; // eax

  if ( dword_51ABB8 )
    Mem_SmallBlockFree((_DWORD *)dword_51ABB8, 24 * dword_51ABBC);
  if ( dword_51ABC0 )
    Mem_SmallBlockFree((_DWORD *)dword_51ABC0, 14 * dword_51ABBC);
  v0 = (int *)dword_51ABC4;
  dword_51ABC4 = *(_DWORD *)(dword_51ABC4 + 20);
  dword_51ABB8 = *v0;
  dword_51ABBC = v0[2];
  dword_51ABC0 = v0[1];
  if ( dword_51ABC8 )
  {
    Rules_DeinstallMultifield(*(__int16 **)(dword_51ABC8 + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(dword_51ABC8 + 8));
    dword_54DBAC = dword_51ABC8;
    *(_DWORD *)dword_51ABC8 = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
  }
  dword_51ABC8 = v0[3];
  dword_51ABD0 = (int (*)(void))v0[4];
  dword_54DBAC = (int)v0;
  *v0 = *(_DWORD *)(dword_54DBA8 + 96);
  result = dword_54DBA8;
  *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
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
  int v2; // edx
  int v3; // eax
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx

  if ( !dword_51ABB8 || dword_51ABC0 )
    return dword_51ABC0;
  dword_51ABC0 = (int)Mem_SmallBlockAlloc(14 * dword_51ABBC);
  v2 = 0;
  if ( dword_51ABBC > 0 )
  {
    v3 = 0;
    do
    {
      *(_WORD *)(dword_51ABC0 + v3) = *(_WORD *)(dword_51ABB8 + v1 + 4);
      v4 = v1 + dword_51ABB8;
      if ( *(_DWORD *)(v1 + dword_51ABB8 + 4) != 4 )
        v4 = *(_DWORD *)(v4 + 8);
      *(_DWORD *)(dword_51ABC0 + v3 + 2) = v4;
      *(_DWORD *)(dword_51ABC0 + v3 + 6) = 0;
      v5 = v2 + 1;
      if ( v2 + 1 == dword_51ABBC )
        v6 = dword_51ABBC ^ v5;
      else
        v6 = dword_51ABC0 + 14 * v5;
      v1 += 24;
      *(_DWORD *)(dword_51ABC0 + v3 + 10) = v6;
      ++v2;
      v3 += 14;
    }
    while ( v2 < dword_51ABBC );
  }
  return dword_51ABC0;
}
// 49A949: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;

//----- (0049A9E0) --------------------------------------------------------
int  Rules_ExecuteRuleActions(
        int a1,
        __int16 *a2,
        _DWORD *a3,
        int a4,
        double a5,
        void (*a6)(void))
{
  _DWORD *v9; // eax
  int v10; // eax
  int v11; // ebx
  _DWORD *v12; // ecx
  int saved_module; // ecx
  int v14; // eax
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int result; // eax
  int v20; // [esp+0h] [ebp-14h]

  v20 = dword_51ABCC;
  if ( a4 )
    v9 = Mem_SmallBlockAlloc(24 * a4);
  else
    v9 = 0;
  dword_51ABCC = (int)v9;
  if ( a4 > 0 )
  {
    v10 = 0;
    v11 = 24 * a4;
    do
    {
      v12 = (_DWORD *)(dword_51ABCC + v10);
      v10 += 24;
      *v12 = dword_54DD70;
    }
    while ( v10 < v11 );
  }
  saved_module = Module_GetCurrent();
  if ( saved_module != a1 )
    Module_SetCurrent(a1);
  if ( Parser_ParseForm(a2, a3, saved_module, a5) )
  {
    a3[1] = 2;
    a3[2] = dword_54DD70;
  }
  v14 = Module_GetCurrent();
  if ( saved_module != v14 )
    Module_SetCurrent(saved_module);
  if ( a6 && dword_51A968 )
  {
    Rules_PrintErrorID((int)aPrccode_0, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExecutionHal_0, v16);
    a6();
  }
  v17 = dword_51ABC8;
  if ( dword_51ABC8 && a3[2] == *(_DWORD *)(dword_51ABC8 + 8) )
  {
    Rules_DeinstallMultifield(*(__int16 **)(dword_51ABC8 + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(dword_51ABC8 + 8));
    dword_54DBAC = dword_51ABC8;
    *(_DWORD *)dword_51ABC8 = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
    dword_51ABC8 = 0;
  }
  if ( a4 )
  {
    if ( a4 > 0 )
    {
      v18 = 0;
      do
      {
        if ( dword_54DD64 == *(_DWORD *)(v18 + dword_51ABCC) )
          Rules_ValueDeinstall(v18 + dword_51ABCC, v17);
        v18 += 24;
      }
      while ( v18 < 24 * a4 );
    }
    Mem_SmallBlockFree((_DWORD *)dword_51ABCC, 24 * a4);
  }
  result = v20;
  dword_51ABCC = v20;
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
signed int  ProcParam_PrintArguments(int a1)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // esi

  Output_Write(a1, (int)asc_505CB4, a1);
  v2 = 0;
  if ( dword_51ABBC > 0 )
  {
    v3 = 0;
    do
    {
      Rules_PrintDataObject(v1, v3 + dword_51ABB8);
      if ( v2 != dword_51ABBC - 1 )
        Output_Write(v1, (int)asc_505C54, v1);
      ++v2;
      v3 += 24;
    }
    while ( v2 < dword_51ABBC );
  }
  return Output_Write(v1, (int)asc_505CB8, v1);
}
// 49ABB9: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;

//----- (0049AC00) --------------------------------------------------------
__int16 * ProcParam_BuildWildcardMultifield(_DWORD *a1, int a2)
{
  _DWORD *v3; // ebx
  signed int v4; // eax
  signed int v5; // esi
  int v6; // ebx
  int v7; // eax
  _DWORD *v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ebx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  __int16 *result; // eax
  int v16; // eax
  _DWORD *v17; // eax
  int v18; // edx
  int v19; // [esp+0h] [ebp-18h]
  int v20; // [esp+4h] [ebp-14h]

  a1[1] = 4;
  a1[3] = 0;
  if ( dword_51ABC8 )
  {
    if ( a2 == dword_51AC94 )
    {
      a1[4] = *(_DWORD *)(dword_51ABC8 + 16);
      result = *(__int16 **)(dword_51ABC8 + 8);
      a1[2] = result;
      return result;
    }
    Rules_DeinstallMultifield(*(__int16 **)(dword_51ABC8 + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(dword_51ABC8 + 8));
  }
  else
  {
    v3 = *(_DWORD **)(dword_54DBA8 + 96);
    if ( v3 )
    {
      dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 96);
      *(_DWORD *)(dword_54DBA8 + 96) = *v3;
      v4 = dword_54DBAC;
    }
    else
    {
      v4 = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    dword_51ABC8 = v4;
    *(_DWORD *)(v4 + 12) = 0;
  }
  v5 = dword_51ABBC - a2 + 1;
  dword_51AC94 = a2;
  if ( v5 <= 0 )
  {
    v16 = dword_51ABC8;
    *(_DWORD *)(dword_51ABC8 + 16) = -1;
    a1[4] = *(_DWORD *)(v16 + 16);
    v17 = Rules_CreateMultifield(0);
    *(_DWORD *)(dword_51ABC8 + 8) = v17;
    a1[2] = v17;
    return Rules_InstallMultifield(*(__int16 **)(dword_51ABC8 + 8));
  }
  else
  {
    v6 = a2 - 1;
    if ( a2 - 1 < dword_51ABBC )
    {
      v7 = 24 * v6;
      do
      {
        if ( *(_DWORD *)(v7 + dword_51ABB8 + 4) == 4 )
          v5 += *(_DWORD *)(v7 + dword_51ABB8 + 16) - *(_DWORD *)(v7 + dword_51ABB8 + 12);
        v7 += 24;
        ++v6;
      }
      while ( v7 < 24 * dword_51ABBC );
    }
    *(_DWORD *)(dword_51ABC8 + 16) = v5 - 1;
    a1[4] = v5 - 1;
    v8 = Rules_CreateMultifield(v5);
    *(_DWORD *)(dword_51ABC8 + 8) = v8;
    v19 = a2 - 1;
    a1[2] = v8;
    v9 = 1;
    if ( a2 - 1 < dword_51ABBC )
    {
      v20 = 24 * (a2 - 1);
      do
      {
        v10 = v20 + dword_51ABB8;
        if ( *(_DWORD *)(v20 + dword_51ABB8 + 4) == 4 )
        {
          v11 = v20 + dword_51ABB8;
          v12 = *(_DWORD *)(v10 + 12) + 1;
          v13 = 6 * v9 - 6;
          v14 = 6 * v12 - 6;
          while ( v12 <= *(_DWORD *)(v11 + 16) + 1 )
          {
            v14 += 6;
            ++v12;
            *(_WORD *)(v13 + a1[2] + 14) = *(_WORD *)(v14 + *(_DWORD *)(v11 + 8) + 8);
            v13 += 6;
            ++v9;
            *(_DWORD *)(v13 + a1[2] + 10) = *(_DWORD *)(v14 + *(_DWORD *)(v11 + 8) + 10);
          }
        }
        else
        {
          v18 = 6 * (v9 - 1);
          *(_WORD *)(a1[2] + v18 + 14) = *(_WORD *)(v10 + 4);
          ++v9;
          *(_DWORD *)(a1[2] + v18 + 16) = *(_DWORD *)(dword_51ABB8 + v20 + 8);
        }
        v20 += 24;
        ++v19;
      }
      while ( v19 < dword_51ABBC );
    }
    return Rules_InstallMultifield(*(__int16 **)(dword_51ABC8 + 8));
  }
}
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC8: using guessed type int dword_51ABC8;
// 51AC94: using guessed type int dword_51AC94;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049AE70) --------------------------------------------------------
_DWORD * ProcParam_EvaluateArgumentExpressions(uintptr_t result, int a2, int a3, int a4, double a5)
{
  uintptr_t expression; // esi
  _DWORD *argument_values; // eax
  _DWORD *argument_slot; // ecx
  _DWORD parsed[6]; // [esp+0h] [ebp-2Ch] BYREF

  expression = result;
  if ( a2 )
  {
    argument_values = Mem_SmallBlockAlloc(24 * a2);
    if ( expression )
    {
      argument_slot = argument_values;
      while ( Parser_ParseForm((__int16 *)expression, parsed, (int)(uintptr_t)argument_slot, a5) != 1 && parsed[1] != 105 )
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
        Output_Write((int)g_IO_LogicalNameTable_WError[0], a3, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArguments__0, 0);
        Lexer_ErrorRecover(1);
      }
      Rules_PrintErrorID((int)aPrccode_0, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForThe, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], a3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505C54, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], a4, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ExpressionError, 0);
      return (_DWORD *)Mem_SmallBlockFree(argument_values, 24 * a2);
    }
    else
    {
LABEL_11:
      result = (uintptr_t)argument_values;
      dword_51ABBC = a2;
      dword_51ABB8 = (int)(uintptr_t)argument_values;
    }
  }
  else
  {
    dword_51ABB8 = 0;
    dword_51ABBC = 0;
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
signed int  ProcParam_GetArgumentValue(int a1, _DWORD *a2)
{
  int payload; // eax
  int record; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  record = dword_51ABB8 + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  a2[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
  a2[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
  a2[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
  a2[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
  return 1;
}
// 51ABB8: using guessed type int dword_51ABB8;

//----- (0049B040) --------------------------------------------------------
signed int  ProcParam_GetBoundVariableValue(int a1, _DWORD *a2, double a3)
{
  int payload; // edx
  int record; // eax
  int expression; // eax
  unsigned int raw_index; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  raw_index = *(_DWORD *)(uintptr_t)(unsigned int)payload;
  record = dword_51ABCC + 24 * ((((unsigned int)raw_index << 16) >> 17) - 1);
  if ( dword_54DD64 == *(_DWORD *)(uintptr_t)(unsigned int)record )
    goto LABEL_6;
  expression = *(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)expression + 10), a2, (int)(uintptr_t)a2, a3);
    return 1;
  }
  if ( (*(_WORD *)((uintptr_t)(unsigned int)payload + 2) & 0xFFFE) != 0 )
  {
    if ( (*(_BYTE *)((uintptr_t)(unsigned int)payload + 2) & 1) == 0 )
    {
      record = 24 * ((raw_index >> 17) - 1) + dword_51ABB8;
LABEL_6:
      a2[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
      a2[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
      a2[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
      a2[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
      return 1;
    }
    ProcParam_BuildWildcardMultifield(a2, raw_index >> 17);
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
    if ( dword_51ABD0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnboundIn, 0);
      dword_51ABD0();
    }
    else
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnbound_, 0);
    }
    a2[1] = 2;
    a2[2] = dword_54DD70;
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
signed int  ProcParam_BindLocalVariable(int a1, _DWORD *a2, double a3)
{
  int payload; // eax
  int record; // ecx
  int expression; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  record = dword_51ABCC + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  expression = *(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
  if ( !expression )
  {
    if ( dword_54DD64 == *(_DWORD *)(uintptr_t)(unsigned int)record )
      Rules_ValueDeinstall(record, record);
    *(_DWORD *)(uintptr_t)(unsigned int)record = dword_54DD70;
    a2[1] = 2;
    a2[2] = dword_54DD70;
    return 1;
  }
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(a2, expression, 1, a3);
  else
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)expression, a2, record, a3);
  if ( dword_54DD64 == *(_DWORD *)(uintptr_t)(unsigned int)record )
    Rules_ValueDeinstall(record, record);
  *(_DWORD *)(uintptr_t)(unsigned int)record = dword_54DD64;
  *(_DWORD *)((uintptr_t)(unsigned int)record + 4) = a2[1];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 8) = a2[2];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 12) = a2[3];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 16) = a2[4];
  Rules_ValueInstall(record, record);
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 51ABCC: using guessed type int dword_51ABCC;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B250) --------------------------------------------------------
signed int  ProcParam_GetWildcardArgumentValue(int a1, _DWORD *a2)
{
  int payload; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  ProcParam_BuildWildcardMultifield(a2, *(_DWORD *)(uintptr_t)(unsigned int)payload);
  return 1;
}

//----- (0049B270) --------------------------------------------------------
signed int  Parser_FindProcParamIndex(int a1, int a2, int a3)
{
  signed int result; // eax

  result = 1;
  if ( a2 )
  {
    while ( a1 != *(_DWORD *)(a2 + 2) )
    {
      a2 = *(_DWORD *)(a2 + 10);
      ++result;
      if ( !a2 )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    if ( a1 != a3 )
      return 0;
  }
  return result;
}

//----- (0049B2A0) --------------------------------------------------------
signed int  Parser_ScanBindStatementsForSymbol(int a1, int (*a2)(void), int a3)
{
  int v3; // ecx
  int **Symbol; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ecx

  v3 = a1;
  if ( !a1 )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(v3 + 6) )
      {
        if ( Parser_ScanBindStatementsForSymbol(*(_DWORD *)(v3 + 6), (int (__fastcall *)(_DWORD, _DWORD))a2, a3) )
          return 1;
        Symbol = Rules_MakeSymbol(aBind_1);
        if ( Symbol == *(int ***)(v3 + 2) )
        {
          v8 = *(_DWORD *)(v3 + 6);
          if ( *(_WORD *)v8 == 2 )
          {
            v9 = *(_DWORD *)(v8 + 2);
            v10 = a2();
            if ( v10 == -1 )
              return 1;
            if ( v10 == 1 )
              break;
          }
        }
      }
      v3 = *(_DWORD *)(v3 + 10);
      if ( !v3 )
        return 0;
    }
    Rules_RemoveNamedContextEntry(v9);
    v3 = *(_DWORD *)(v11 + 10);
  }
  while ( v3 );
  return 0;
}
// 49B2B4: variable 'v3' is possibly undefined
// 49B30B: variable 'v11' is possibly undefined

//----- (0049B320) --------------------------------------------------------
_DWORD * AST_UnwrapActionListWrapper(_DWORD *result)
{
  int v1; // edx
  _DWORD *v2; // ecx

  v1 = *(_DWORD *)((char *)result + 6);
  if ( v1 )
  {
    if ( !*(_DWORD *)(v1 + 10) )
    {
      v2 = result;
      result = *(_DWORD **)((char *)result + 6);
      dword_54DBAC = (int)v2;
      *v2 = *(_DWORD *)(dword_54DBA8 + 56);
      *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
    }
  }
  else
  {
    *(_WORD *)result = 2;
    *(_DWORD *)((char *)result + 2) = dword_54DD70;
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
BOOL  Dribble_QueryRouter(int a1)
{
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  return !strcmp_(a1, aStdout_2)
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
signed int  Dribble_PrintRouter(int a1, unsigned __int8 *a2, int a3)
{
  unsigned __int8 *v4; // ecx
  unsigned __int8 *v5; // edx
  _BYTE *v6; // edx
  char v7; // al
  int v8; // ecx
  int v10; // edx
  int v11; // edx
  char v12; // al
  _BYTE v13[16]; // [esp+0h] [ebp-18h] BYREF
  int v14; // [esp+10h] [ebp-8h]

  v14 = a3;
  v4 = a2;
  if ( dword_51ACBC )
  {
    sprintf_(
      v13,
      "%03d:%02d:%02d ",
      *(_DWORD *)dword_54E6C0 / 0x1770u % 0x3C,
      *(_DWORD *)dword_54E6C0 / 0x64u % 0x3C,
      *(_DWORD *)dword_54E6C0 % 0x64u);
    v10 = 0;
    if ( v13[0] )
    {
      do
      {
        Dribble_AppendChar((char *)(unsigned __int8)v13[v10], v10, (int)v4);
        v12 = v13[v11 + 1];
        v10 = v11 + 1;
      }
      while ( v12 );
    }
    dword_51ACBC = 0;
  }
  v5 = v4;
  if ( *v4 )
  {
    do
    {
      Dribble_AppendChar((char *)*v5, (int)v5, (int)v4);
      if ( *v6 == 10 )
        dword_51ACBC = 1;
      v7 = v6[1];
      v5 = v6 + 1;
    }
    while ( v7 );
  }
  IO_DeactivateRouter((int)aDribble);
  Output_Write(a1, v8, v8);
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
    if ( dword_51AC9C > 0 )
    {
      Output_WriteFormatted(dword_51AC98, dword_54E6C4, dword_51AC98, (int)aS_3, dword_54E6C4);
      result = (char *)dword_54E6C4;
      dword_51AC9C = 0;
      *(_BYTE *)dword_54E6C4 = 0;
    }
  }
  else if ( g_Lexer_PendingLineCharIndex >= 0 )
  {
    result = Str_AppendCharEscaping(
               (int)result,
               (char *)dword_54E6C4,
               (unsigned int *)&dword_51ACA0,
               &dword_51AC9C,
               dword_51ACA0 + 120);
    dword_54E6C4 = (int)result;
  }
  else
  {
    if ( dword_51AC9C > 0 )
    {
      Output_WriteFormatted(a3, a2, dword_51AC98, (int)aS_3, dword_54E6C4);
      dword_51AC9C = 0;
      *(_BYTE *)dword_54E6C4 = 0;
    }
    return (char *)CRT_PutcToStream(a3, dword_51AC98);
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

  if ( dword_51AC9C > 0 )
    --dword_51AC9C;
  *(_BYTE *)(dword_51AC9C + dword_54E6C4) = 0;
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

  if ( dword_51AC9C > 0 )
  {
    v3 = a1;
    Output_WriteFormatted(dword_54E6C4, a2, dword_51AC98, (int)aS_3, dword_54E6C4);
    a1 = v3;
  }
  if ( dword_51AC98 )
    fclose_(a1);
  return 1;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B7B0) --------------------------------------------------------
const CHAR * Rules_DribbleOnCommand(DWORD a1, double a2)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
  if ( result )
    return (const CHAR *)Dribble_TurnOn(result, a1);
  return result;
}
// 49B7D7: variable 'v2' is possibly undefined

//----- (0049B7F0) --------------------------------------------------------
signed int  Dribble_TurnOn(const CHAR *a1, DWORD a2)
{
  const CHAR *v2; // ecx
  int v3; // ecx

  v2 = a1;
  if ( dword_51AC98 )
    Dribble_TurnOff();
  dword_51AC98 = IO_FOpen(v2, (unsigned __int8 *)aW_3, (int)v2, a2);
  if ( dword_51AC98 )
  {
    IO_AddRouter((int)aDribble, 40, (int)Dribble_PrintRouter, (int)Dribble_QueryRouter, (int)Dribble_GetcRouter, (int)Dribble_UngetcRouter, (int)Dribble_ExitRouter);
    dword_51AC9C = 0;
    if ( dword_51ACA4 )
      dword_51ACA4(0);
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
  int (__thiscall *v0)(_DWORD); // edx
  int v1; // ecx
  int v2; // ecx
  signed int v3; // ecx
  signed int result; // eax

  v0 = dword_51ACA4;
  v1 = 0;
  if ( dword_51ACA4 )
    dword_51ACA4(0);
  if ( !dword_51AC98 )
    goto LABEL_7;
  if ( dword_51AC9C > 0 )
    Output_WriteFormatted(v1, (int)v0, dword_51AC98, (int)aS_3, dword_54E6C4);
  IO_DeleteRouter((int)aDribble);
  if ( !fclose_(v2) )
LABEL_7:
    v3 = 1;
  dword_51AC98 = 0;
  if ( dword_54E6C4 )
  {
    Mem_SmallBlockFree((_DWORD *)dword_54E6C4, dword_51ACA0);
    dword_54E6C4 = 0;
  }
  result = v3;
  dword_51AC9C = 0;
  dword_51ACA0 = 0;
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
int  Rules_BatchGetChar(int a1)
{
  return Rules_BatchReadChar(a1, 0);
}

//----- (0049B9B0) --------------------------------------------------------
int  Rules_BatchReadChar(int a1, unsigned int a2)
{
  unsigned int v3; // esi
  signed int v4; // ecx
  int v5; // edi
  int v6; // eax
  unsigned int v7; // ecx
  unsigned __int8 *v9; // eax
  char *appended; // eax
  int v11; // ecx
  int v12; // [esp+0h] [ebp-18h]

  v3 = a2;
  v4 = 1;
  do
  {
    if ( dword_54E6CC )
    {
      v6 = Lexer_PeekChar(dword_51ACA8, v4);
    }
    else
    {
      v5 = *(_DWORD *)(dword_51ACA8 + 4);
      if ( v5 > 0 && (a2 = **(unsigned __int8 **)dword_51ACA8 - 13, a2 > 0xFD) )
      {
        *(_DWORD *)(dword_51ACA8 + 4) = v5 - 1;
        a2 = dword_51ACA8;
        v9 = (unsigned __int8 *)(*(_DWORD *)dword_51ACA8)++;
        v6 = *v9;
      }
      else
      {
        v6 = fgetc_(v4, a2);
      }
    }
    v12 = v6;
    if ( v6 == -1 )
    {
      if ( dword_51ACAC > 0 )
        Output_Write((int)aStdout_2, dword_54E6C8, v4);
      v4 = Rules_CloseBatch();
    }
  }
  while ( v12 == -1 && v4 == 1 );
  if ( v12 == -1 )
  {
    if ( dword_51ACAC > 0 )
      Output_Write((int)aStdout_2, dword_54E6C8, v4);
    IO_DeleteRouter((int)aBatch);
    Rules_CloseBatch();
    if ( v3 == 1 )
      return -1;
    else
      return Lexer_PeekChar(a1, v7);
  }
  else
  {
    appended = Str_AppendCharEscaping(
                 (unsigned __int8)v12,
                 (char *)dword_54E6C8,
                 (unsigned int *)&dword_51ACB0,
                 &dword_51ACAC,
                 dword_51ACB0 + 120);
    dword_54E6C8 = (int)appended;
    if ( (_BYTE)v12 == 10 )
    {
      Output_Write((int)aStdout_2, (int)appended, v11);
      dword_51ACAC = 0;
      if ( dword_54E6C8 )
      {
        if ( dword_51ACB0 > 120 )
        {
          Mem_SmallBlockFree((_DWORD *)dword_54E6C8, dword_51ACB0);
          dword_51ACB0 = 0;
          dword_54E6C8 = 0;
        }
      }
    }
    return v12;
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
signed int  Rules_BatchUngetChar(signed int a1, int a2)
{
  if ( dword_51ACAC > 0 )
    a2 = --dword_51ACAC;
  if ( dword_54E6C8 )
    *(_BYTE *)(dword_54E6C8 + dword_51ACAC) = 0;
  if ( dword_54E6CC )
    return Lexer_SkipChar(a1, dword_51ACA8, a2);
  else
    return CRT_FlushBufferAndPutChar(a1, a2);
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
const CHAR * Rules_BatchCommand(DWORD a1, double a2)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
  if ( result )
    return (const CHAR *)Rules_OpenBatch(result, 0, v4, a1);
  return result;
}
// 49BBC7: variable 'v2' is possibly undefined
// 49BBD2: variable 'v4' is possibly undefined

//----- (0049BBF0) --------------------------------------------------------
signed int  Rules_OpenBatch(const CHAR *a1, int a2, int a3, DWORD a4)
{
  int v6; // ecx
  int v7; // edi

  v7 = IO_FOpen(a1, (unsigned __int8 *)aR_1, a3, a4);
  if ( v7 )
  {
    if ( !dword_51ACB4 )
      IO_AddRouter((int)aBatch, 20, 0, (int)Rules_BatchQueryStdin, (int)Rules_BatchGetChar, (int)Rules_BatchUngetChar, (int)Rules_BatchExitFunction);
    Rules_AddBatchEntry(a2, v7, 0, 0);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v6, (int)a1);
    return 0;
  }
}
// 49BC54: variable 'v6' is possibly undefined
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BCC0) --------------------------------------------------------
_DWORD * Rules_AddBatchEntry(int a1, int a2, int a3, int a4)
{
  _DWORD *v5; // edi
  _DWORD *result; // eax

  v5 = *(_DWORD **)(dword_54DBA8 + 64);
  if ( v5 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 64);
    *(_DWORD *)(dword_54DBA8 + 64) = *v5;
    result = (_DWORD *)dword_54DBAC;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  result[3] = 0;
  *result = a4;
  result[1] = a2;
  result[2] = a3;
  if ( dword_51ACB4 )
  {
    if ( a1 )
    {
      *(_DWORD *)(dword_51ACB8 + 12) = result;
      dword_51ACB8 = (int)result;
    }
    else
    {
      result[3] = dword_51ACB4;
      dword_51ACB4 = (int)result;
      dword_54E6CC = a4;
      dword_51ACA8 = a2;
      dword_51ACAC = 0;
    }
  }
  else
  {
    dword_51ACB4 = (int)result;
    dword_51ACB8 = (int)result;
    dword_54E6CC = a4;
    dword_51ACA8 = a2;
    dword_51ACAC = 0;
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
  _DWORD *v0; // eax
  signed int result; // eax

  if ( !dword_51ACB4 )
    return 0;
  if ( *(_DWORD *)dword_51ACB4 )
  {
    IO_CloseStringRouter(*(_DWORD *)(dword_51ACB4 + 4));
    Mem_SmallBlockFree(*(_DWORD **)(dword_51ACB4 + 8), strlen(*(const char **)(dword_51ACB4 + 8)) + 1);
  }
  else
  {
    fclose_(0);
  }
  v0 = (_DWORD *)dword_51ACB4;
  dword_51ACB4 = *(_DWORD *)(dword_51ACB4 + 12);
  dword_54DBAC = (int)v0;
  *v0 = *(_DWORD *)(dword_54DBA8 + 64);
  *(_DWORD *)(dword_54DBA8 + 64) = dword_54DBAC;
  if ( dword_51ACB4 )
  {
    dword_54E6CC = *(_DWORD *)dword_51ACB4;
    dword_51ACA8 = *(_DWORD *)(dword_51ACB4 + 4);
    dword_51ACAC = 0;
    return 1;
  }
  else
  {
    dword_51ACB8 = 0;
    dword_51ACA8 = 0;
    if ( dword_54E6C8 )
    {
      Mem_SmallBlockFree((_DWORD *)dword_54E6C8, dword_51ACB0);
      dword_54E6C8 = 0;
    }
    result = 0;
    dword_51ACAC = 0;
    dword_51ACB0 = 0;
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
  return dword_51ACB4 != 0;
}
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BE70) --------------------------------------------------------
signed int __thiscall Rules_CloseAllBatchSources(void *this)
{
  signed int result; // eax

  if ( dword_54E6C8 )
  {
    if ( dword_51ACAC > 0 )
      Output_Write((int)aStdout_2, dword_54E6C8, (int)this);
    Mem_SmallBlockFree((_DWORD *)dword_54E6C8, dword_51ACB0);
    dword_54E6C8 = 0;
    dword_51ACAC = 0;
    dword_51ACB0 = 0;
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
const CHAR * Rules_BatchStarCommand(DWORD a1, double a2)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
  if ( result )
    return (const CHAR *)Rules_BatchStar(result, a1, a2);
  return result;
}
// 49BEF7: variable 'v2' is possibly undefined

//----- (0049BF10) --------------------------------------------------------
signed int  Rules_BatchStar(const CHAR *a1, DWORD a2, double a3)
{
  char *appended; // edi
  int v4; // ecx
  int *v5; // esi
  int v6; // edx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  unsigned __int8 *v13; // eax
  int v14; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int v15[6]; // [esp+4h] [ebp-18h] BYREF

  appended = 0;
  v14 = 0;
  v15[0] = 0;
  v5 = (int *)IO_FOpen(a1, (unsigned __int8 *)aR_1, (int)a1, a2);
  if ( v5 )
  {
    Rules_SetEvaluationErrorFlag(0);
    Lexer_ErrorRecover(0);
    while ( 1 )
    {
      if ( v5[1] <= 0 || (unsigned int)*(unsigned __int8 *)*v5 - 13 <= 0xFD )
      {
        v8 = fgetc_(v7, v6);
      }
      else
      {
        v13 = (unsigned __int8 *)*v5;
        v9 = *v5 + 1;
        --v5[1];
        *v5 = v9;
        v8 = *v13;
      }
      if ( v8 == -1 )
        break;
      appended = Str_AppendCharEscaping(v8, appended, v15, &v14, v15[0] + 80);
      if ( Lexer_IsCommandTextComplete((signed int)appended) )
      {
        Rules_FlushPPBuffer();
        Rules_SetPPBufferStatus(0);
        Rules_RouteCommand(v10, 0, v10, a3);
        Rules_FlushPPBuffer();
        Rules_SetEvaluationErrorFlag(0);
        Lexer_ErrorRecover(0);
        Rules_FreeBoundVariableEntry();
        appended = 0;
        Mem_ReleasePoolBlock(v11, v15[0]);
        v15[0] = 0;
        v14 = 0;
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
int  Rules_LoadCommand(DWORD a1, double a2)
{
  int v2; // ecx
  int result; // eax
  const CHAR *v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  if ( result )
  {
    Rules_SetLoadInProgress(1);
    if ( Rules_Load(v4, v5, a1) )
    {
      Rules_SetLoadInProgress(0);
      return v6 != -1;
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
const CHAR * Rules_LoadStarCommand(DWORD a1, double a2)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx
  int v5; // edx
  signed int v6; // eax
  int v7; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
  v5 = (int)result;
  if ( result )
  {
    v6 = Rules_Load(result, v4, a1);
    if ( v6 )
    {
      return (const CHAR *)(v6 != -1);
    }
    else
    {
      Rules_OpenFileErrorMessage(v7, v5);
      return 0;
    }
  }
  return result;
}
// 49C0D7: variable 'v2' is possibly undefined
// 49C0E2: variable 'v4' is possibly undefined
// 49C0FA: variable 'v7' is possibly undefined

//----- (0049C110) --------------------------------------------------------
int  Rules_SaveCommand(DWORD a1, double a2)
{
  int v2; // ecx
  int result; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  v5 = result;
  if ( result )
  {
    if ( Rules_Save((const CHAR *)result, v4, a1) )
    {
      return 1;
    }
    else
    {
      Rules_OpenFileErrorMessage(v6, v5);
      return 0;
    }
  }
  return result;
}
// 49C137: variable 'v2' is possibly undefined
// 49C142: variable 'v4' is possibly undefined
// 49C158: variable 'v6' is possibly undefined

//----- (0049C170) --------------------------------------------------------
signed int  Rules_Load(const CHAR *a1, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  result = IO_FOpen(a1, (unsigned __int8 *)aR_2, a2, a3);
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
int  Rules_LoadConstructsFromLogicalName(int a1, int a2)
{
  int v4; // edx
  _DWORD *v5; // ecx
  int v6; // ecx
  char *v7; // eax
  _DWORD *v8; // ecx
  signed int v9; // ebx
  int v11; // ecx
  int v12; // [esp-4h] [ebp-20h] BYREF
  _DWORD v13[5]; // [esp+8h] [ebp-14h] BYREF

  v13[3] = a2;
  v13[0] = 1;
  if ( !dword_51A96C )
    Rules_SetEvaluationErrorFlag(0);
  Lexer_ErrorRecover(0);
  Parser_NextToken(a1, v4);
  if ( Rules_SkipToConstructBeginning(a1, &v12, v5, 0) == 1 )
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
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505E94, (int)v13);
        v13[0] = 0;
        Parser_NextToken(a1, (int)&v12);
        v9 = 1;
      }
      else
      {
        Parser_NextToken(a1, (int)&v12);
        v9 = 0;
      }
    }
    while ( Rules_SkipToConstructBeginning(a1, &v12, v8, v9) == 1 );
  }
  if ( Rules_GetWatchItemState((int)aCompilations) == 1 || !Rules_GetLoadInProgress() )
  {
    Rules_DestroyPPBuffer();
    return v13[0];
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_505E94, v11);
    Rules_DestroyPPBuffer();
    return v13[0];
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
signed int  Rules_SkipToConstructBeginning(int a1, _DWORD *a2, _DWORD *a3, signed int a4)
{
  int v7; // ecx
  int v8; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  v7 = 1;
  v8 = 0;
  if ( *a2 == 102 )
    return 0;
  while ( *a2 == 100 )
  {
    v8 = 1;
LABEL_4:
    Parser_NextToken(a1, (int)a2);
    if ( *a2 == 102 )
      return 0;
  }
  if ( *a2 != 2 || v8 != 1 )
  {
    if ( v7 )
    {
      if ( !a4 )
      {
        a4 = 1;
        *a3 = 0;
        Rules_PrintErrorID((int)aCstrcpsr, 1, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedTheBeg, v10);
      }
    }
    v8 = 0;
    goto LABEL_4;
  }
  if ( !Rules_FindConstructByName() )
  {
    if ( v11 && !a4 )
    {
      *a3 = 0;
      a4 = 1;
      Rules_PrintErrorID((int)aCstrcpsr, 1, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedTheBeg, v12);
    }
    v8 = 0;
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
  int v0; // ebx
  int v2; // edx
  int v3; // ecx

  v0 = Rules_FindConstructByName();
  if ( !v0 )
    return -1;
  Rules_GetEvaluationErrorFlag();
  Lexer_ErrorRecover(0);
  Rules_SetEvaluationErrorFlag(0);
  Parser_FreeLoopContextStack();
  Parser_PushFunctionParseState();
  dword_54E87C = 0;
  dword_54E878 = 0;
  ++dword_51A96C;
  (*(void (**)(void))(v0 + 8))();
  --dword_51A96C;
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
        int a1,
        int a2,
        int (*a3)(void),
        char *a4,
        int (*a5)(void),
        char *a6,
        int a7,
        int a8,
        int a9)
{
  signed int v12; // eax
  int v13; // ebx
  signed int *v14; // eax
  int *v15; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  signed int *v19; // ecx
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
  int v42; // [esp+0h] [ebp-18h]
  int v44; // [esp+8h] [ebp-10h]

  v44 = 0;
  Parser_NextToken(a1, a2);
  if ( *(_DWORD *)a2 != 2 )
  {
    Rules_PrintErrorID((int)aCstrcpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMissingNameFor, v31);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a4, v32);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConstruct, v33);
    return 0;
  }
  v12 = Rules_FindModuleSeparator(*(_BYTE **)(*(_DWORD *)(a2 + 4) + 16));
  v13 = v12;
  if ( v12 )
  {
    if ( !a9 )
      goto LABEL_23;
    v14 = Rules_ExtractModuleName(v12);
    if ( !v14 )
      goto LABEL_23;
    v15 = Module_FindByName((_BYTE *)v14[4]);
    v42 = (int)v15;
    if ( !v15 )
    {
      Rules_ReportCantFindItem(v17, *(_DWORD *)(v16 + 16));
      return 0;
    }
    Module_SetCurrent((int)v15);
    v19 = Rules_ExtractConstructName(v13, *(char **)(v18 + 16), v18);
    if ( !v19 )
    {
LABEL_23:
      Parser_ReportSyntaxError();
      return 0;
    }
  }
  else
  {
    v42 = Module_GetCurrent();
    if ( a9 )
    {
      IO_OutNewline();
      Name = (char *)Module_GetName(v34);
      IO_OutWriteToken(Name);
      IO_OutWriteToken(asc_505F2C);
      IO_OutWriteToken(*(char **)(v36 + 16));
    }
  }
  if ( Rules_FindImportExportConflict(a4, v42, (_BYTE *)v19[4]) )
  {
    Lexer_WarnImpliedTemplate((int)a4, *(_DWORD *)(v20 + 16), 0);
    return 0;
  }
  if ( a3 )
  {
    if ( a3() )
    {
      v44 = 1;
      if ( a5 )
      {
        if ( !a5() )
        {
          Rules_PrintErrorID((int)aCstrcpsr, 4, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRedefine, v37);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a4, v38);
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
    if ( v44 )
      v22 = aRedefining;
    else
      v22 = aDefining;
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v22, v21);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a4, v23);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_505F78, v24);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(v25 + 16), v25);
    if ( a7 )
      v27 = asc_505E94;
    else
      v27 = asc_505F44;
    goto LABEL_15;
  }
  if ( Rules_GetLoadInProgress() )
  {
    v27 = a6;
LABEL_15:
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v27, v26);
  }
  Parser_NextToken(a1, a2);
  if ( *(_DWORD *)a2 == 3 && a8 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F44);
    IO_OutWriteToken(*(char **)(a2 + 8));
    Parser_NextToken(a1, v29);
  }
  if ( *(_DWORD *)a2 != 101 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F7C);
    IO_OutWriteToken(*(char **)(a2 + 8));
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
int  Rules_UnlinkListNode(int a1)
{
  int v1; // ecx
  int v2; // eax
  int i; // ebx
  int result; // eax

  v1 = a1;
  v2 = *(_DWORD *)(*(_DWORD *)(a1 + 8) + 4);
  for ( i = 0; v2 != v1; v2 = *(_DWORD *)(v2 + 16) )
    i = v2;
  if ( !v2 )
  {
    Rules_ReportSystemError(v1, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( i )
  {
    *(_DWORD *)(i + 16) = *(_DWORD *)(v1 + 16);
    result = *(_DWORD *)(v1 + 8);
    if ( v1 != *(_DWORD *)(result + 8) )
      return result;
    goto LABEL_9;
  }
  *(_DWORD *)(*(_DWORD *)(v1 + 8) + 4) = *(_DWORD *)(v1 + 16);
  result = *(_DWORD *)(v1 + 8);
  if ( v1 == *(_DWORD *)(result + 8) )
LABEL_9:
    *(_DWORD *)(result + 8) = i;
  return result;
}
// 49C7A4: variable 'v1' is possibly undefined

//----- (0049C7D0) --------------------------------------------------------
signed int  Rules_ImportExportConflictMessage(int a1, int a2, int a3)
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_505F44, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBecauseOfAnImp, v9);
  if ( a3 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedByThe, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a3, v12);
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
int  Rules_WhileFunction(double a1)
{
  _DWORD *v1; // ecx
  int result; // eax
  int v3; // [esp+0h] [ebp-30h] BYREF
  int v4; // [esp+4h] [ebp-2Ch]
  int v5; // [esp+8h] [ebp-28h]
  int v6; // [esp+Ch] [ebp-24h]
  int v7; // [esp+10h] [ebp-20h]

  ++dword_51A96C;
  Rules_RtnUnknown(1, &v3, a1);
  while ( v5 != dword_54DD70 || v4 != 2 )
  {
    if ( dword_51A968 == 1 )
      break;
    if ( dword_51ACC4 == 1 )
      break;
    if ( qword_51ACC0 == 1 )
      break;
    Rules_RtnUnknown(2, &v3, a1);
    --dword_51A96C;
    Rules_RunPeriodicCleanup(0, 1);
    ++dword_51A96C;
    if ( dword_51ACC4 == 1 || qword_51ACC0 == 1 )
      break;
    Rules_RtnUnknown(1, &v3, a1);
  }
  dword_51ACC4 = 0;
  --dword_51A96C;
  if ( qword_51ACC0 == 1 )
  {
    v1[1] = v4;
    v1[2] = v5;
    v1[3] = v6;
    result = v7;
    v1[4] = v7;
  }
  else
  {
    v1[1] = 2;
    result = dword_54DD70;
    v1[2] = dword_54DD70;
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
int  Rules_LoopForCountFunction(_DWORD *a1, double a2)
{
  _DWORD *v3; // edx
  int *v4; // edi
  int *v5; // esi
  int result; // eax
  int v7; // ecx
  int v8; // edi
  _DWORD v9[2]; // [esp+0h] [ebp-30h] BYREF
  int v10; // [esp+8h] [ebp-28h]
  int v11; // [esp+Ch] [ebp-24h]
  int v12; // [esp+10h] [ebp-20h]

  v3 = *(_DWORD **)(dword_54DBA8 + 32);
  if ( v3 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 32);
    *(_DWORD *)(dword_54DBA8 + 32) = *v3;
    v4 = (int *)dword_54DBAC;
  }
  else
  {
    v4 = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *v4 = 0;
  v5 = v4;
  v4[1] = dword_51ACC8;
  dword_51ACC8 = (int)v4;
  if ( Lexer_ParseValueList(1, v9, 1, a2) )
  {
    *v4 = *(_DWORD *)(v10 + 16);
    if ( Lexer_ParseValueList(2, v9, 1, a2) )
    {
      if ( *(_DWORD *)(v10 + 16) >= *v4 )
      {
        do
        {
          if ( dword_51A968 == 1 )
            break;
          if ( dword_51ACC4 == 1 )
            break;
          if ( qword_51ACC0 == 1 )
            break;
          ++dword_51A96C;
          Rules_RtnUnknown(3, v9, a2);
          --dword_51A96C;
          Rules_RunPeriodicCleanup(0, 1);
          if ( dword_51ACC4 == 1 )
            break;
          if ( qword_51ACC0 == 1 )
            break;
          v8 = *v5 + 1;
          *v5 = v8;
        }
        while ( v7 >= v8 );
      }
      dword_51ACC4 = 0;
      if ( qword_51ACC0 == 1 )
      {
        a1[1] = v9[1];
        a1[2] = v10;
        a1[3] = v11;
        a1[4] = v12;
      }
      else
      {
        a1[1] = 2;
        a1[2] = dword_54DD70;
      }
      dword_51ACC8 = v5[1];
      dword_54DBAC = (int)v5;
      *v5 = *(_DWORD *)(dword_54DBA8 + 32);
      result = dword_54DBAC;
      *(_DWORD *)(dword_54DBA8 + 32) = dword_54DBAC;
    }
    else
    {
      a1[1] = 2;
      a1[2] = dword_54DD70;
      dword_51ACC8 = v4[1];
      dword_54DBAC = (int)v4;
      *v4 = *(_DWORD *)(dword_54DBA8 + 32);
      result = dword_54DBAC;
      *(_DWORD *)(dword_54DBA8 + 32) = dword_54DBAC;
    }
  }
  else
  {
    a1[1] = 2;
    a1[2] = dword_54DD70;
    dword_51ACC8 = v4[1];
    dword_54DBAC = (int)v4;
    *v4 = *(_DWORD *)(dword_54DBA8 + 32);
    result = dword_54DBA8;
    *(_DWORD *)(dword_54DBA8 + 32) = dword_54DBAC;
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
  int v0; // eax
  _DWORD *i; // edx

  v0 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(dword_51A960 + 6) + 2) + 16);
  for ( i = (_DWORD *)dword_51ACC8; v0 > 0; i = (_DWORD *)i[1] )
    --v0;
  return *i;
}
// 49CD20: using guessed type int sub_49CD20();
// 51A960: using guessed type int dword_51A960;
// 51ACC8: using guessed type int dword_51ACC8;

//----- (0049CD60) --------------------------------------------------------
int  Rules_IfFunction(double a1)
{
  int result; // eax
  _DWORD *v2; // ecx
  int v3; // ebx
  _DWORD *v4; // ecx

  result = Rules_ArgRangeCheck((int)aIf, 3);
  v3 = result;
  if ( result == -1 )
  {
    v2[1] = 2;
    v2[2] = dword_54DD70;
  }
  else
  {
    result = Rules_RtnUnknown(1, v2, a1);
    if ( dword_51ACC4 != 1 && qword_51ACC0 != 1 )
    {
      if ( dword_54DD70 == v4[2] && v4[1] == 2 && v3 == 3 )
      {
        return Rules_RtnUnknown(3, v4, a1);
      }
      else if ( dword_54DD70 == v4[2] && v4[1] == 2 )
      {
        v4[2] = dword_54DD70;
      }
      else
      {
        return Rules_RtnUnknown(2, v4, a1);
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
__int16 * Rules_BindFunction(_DWORD *a1, double a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ebp
  int v6; // esi
  int v7; // eax
  int v8; // ebx
  _DWORD *v9; // ebx
  _DWORD *v10; // edx
  _DWORD *v11; // edx
  _DWORD *v12; // eax
  _DWORD *v13; // edx
  __int16 *result; // eax
  __int16 *v15; // eax
  int v16; // [esp+0h] [ebp-1Ch]

  v3 = 0;
  v4 = *(_DWORD *)(dword_51A960 + 6);
  v5 = 0;
  v6 = 0;
  v16 = 0;
  if ( *(_WORD *)v4 == 60 )
  {
    v16 = *(_DWORD *)(v4 + 2);
  }
  else
  {
    Parser_ParseForm((__int16 *)v4, a1, 0, a2);
    v6 = a1[2];
  }
  v7 = *(_DWORD *)(dword_51A960 + 6);
  v8 = *(_DWORD *)(v7 + 10);
  if ( v8 )
  {
    v15 = *(__int16 **)(v7 + 10);
    if ( *(_DWORD *)(v8 + 10) )
      Rules_StoreEvaluatedNodesAsMultifield(a1, (int)v15, 1, a2);
    else
      Parser_ParseForm(v15, a1, v3, a2);
  }
  else
  {
    v5 = 1;
  }
  v9 = (_DWORD *)v16;
  if ( v16 )
    return (__int16 *)Defglobal_SetValue(v16, a1, v5, a2);
  v10 = (_DWORD *)dword_51ACCC;
  if ( dword_51ACCC )
  {
    do
    {
      if ( v3 )
        break;
      if ( v6 == *v10 )
      {
        v3 = 1;
      }
      else
      {
        v9 = v10;
        v10 = (_DWORD *)v10[5];
      }
    }
    while ( v10 );
  }
  if ( v3 )
  {
    Rules_ValueDeinstall((int)v10, v3);
  }
  else
  {
    if ( v5 )
    {
LABEL_21:
      a1[1] = 2;
      result = (__int16 *)dword_54DD70;
      a1[2] = dword_54DD70;
      return result;
    }
    v11 = *(_DWORD **)(dword_54DBA8 + 96);
    if ( v11 )
    {
      dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 96);
      *(_DWORD *)(dword_54DBA8 + 96) = *v11;
      v12 = (_DWORD *)dword_54DBAC;
    }
    else
    {
      v12 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    v12[5] = 0;
    v13 = v12;
    *v12 = v6;
    if ( v9 )
      v9[5] = v12;
    else
      dword_51ACCC = (int)v12;
  }
  if ( v5 )
  {
    if ( v9 )
      v9[5] = v13[5];
    else
      dword_51ACCC = v13[5];
    dword_54DBAC = (int)v13;
    *v13 = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
    goto LABEL_21;
  }
  v13[1] = a1[1];
  v13[2] = a1[2];
  v13[3] = a1[3];
  v13[4] = a1[4];
  return Rules_ValueInstall((int)a1, v3);
}
// 49CE6E: variable 'v3' is possibly undefined
// 49CECF: variable 'v13' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACCC: using guessed type int dword_51ACCC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CFD0) --------------------------------------------------------
signed int  Rules_FindBoundVariable(_DWORD *a1, int a2)
{
  _DWORD *v3; // eax

  v3 = (_DWORD *)dword_51ACCC;
  if ( !dword_51ACCC )
    return 0;
  while ( a2 != *v3 )
  {
    v3 = (_DWORD *)v3[5];
    if ( !v3 )
      return 0;
  }
  a1[1] = v3[1];
  a1[2] = v3[2];
  a1[3] = v3[3];
  a1[4] = v3[4];
  return 1;
}
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D010) --------------------------------------------------------
int Rules_FreeBoundVariableEntry()
{
  int result; // eax
  int v1; // edx

  result = Rules_DeinstallValueChain(dword_51ACCC);
  dword_51ACCC = v1;
  return result;
}
// 49D01D: variable 'v1' is possibly undefined
// 51ACCC: using guessed type int dword_51ACCC;

//----- (0049D030) --------------------------------------------------------
int  Rules_PrognFunction(_DWORD *a1, double a2)
{
  int v3; // eax
  int v4; // esi
  int v5; // ecx
  int v6; // ecx
  int result; // eax

  v3 = Rules_RtnArgCount();
  v4 = v3;
  if ( !v3 )
    goto LABEL_8;
  if ( v3 >= 1 )
  {
    do
    {
      if ( Rules_GetEvaluationErrorFlag() == 1 )
        break;
      Rules_RtnUnknown(v5, a1, a2);
      if ( dword_51ACC4 == 1 )
        break;
    }
    while ( qword_51ACC0 != 1 && v6 + 1 <= v4 );
  }
  result = Rules_GetEvaluationErrorFlag();
  if ( result == 1 )
  {
LABEL_8:
    a1[1] = 2;
    result = dword_54DD70;
    a1[2] = dword_54DD70;
  }
  return result;
}
// 49D058: variable 'v5' is possibly undefined
// 49D06F: variable 'v6' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0A0) --------------------------------------------------------
int  Rules_ReturnFunction(double a1)
{
  _DWORD *v1; // edx
  int result; // eax

  if ( Rules_RtnArgCount() )
  {
    result = Rules_RtnUnknown(1, v1, a1);
  }
  else
  {
    v1[1] = 105;
    result = dword_54DD70;
    v1[2] = dword_54DD70;
  }
  qword_51ACC0 = 1;
  return result;
}
// 49D0AC: variable 'v1' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049D0E0) --------------------------------------------------------
void Rules_BreakFunction()
{
  dword_51ACC4 = 1;
}
// 51ACC4: using guessed type int dword_51ACC4;

//----- (0049D0F0) --------------------------------------------------------
int  Rules_SwitchFunction(_DWORD *a1, int a2, double a3)
{
  int result; // eax
  int v6; // ecx
  int v7; // [esp-4h] [ebp-40h] BYREF
  int v8; // [esp+0h] [ebp-3Ch]
  int v9; // [esp+4h] [ebp-38h]
  int v10; // [esp+14h] [ebp-28h] BYREF
  int v11; // [esp+18h] [ebp-24h]
  int v12; // [esp+1Ch] [ebp-20h]
  int v13; // [esp+34h] [ebp-8h]

  v13 = a2;
  a1[1] = 2;
  a1[2] = dword_54DD70;
  result = Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), &v10, a2, a3);
  if ( !dword_51A964 )
  {
    v6 = *(_DWORD *)(*(_DWORD *)(dword_51A960 + 6) + 10);
    if ( v6 )
    {
      while ( *(_WORD *)v6 != 105 )
      {
        result = Parser_ParseForm((__int16 *)v6, &v7, v6, a3);
        if ( dword_51A964 )
          return result;
        result = v11;
        if ( v11 == v8 )
        {
          result = v8 == 4 ? Rules_MultifieldRangesEqual(&v10, &v7) : v12 == v9;
          if ( result )
            break;
        }
        v6 = *(_DWORD *)(*(_DWORD *)(v6 + 10) + 10);
        if ( !v6 )
          return result;
      }
      return Parser_ParseForm(*(__int16 **)(v6 + 10), a1, v6, a3);
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
_DWORD * Rules_CreateMultifieldFunction(_DWORD *a1, double a2)
{
  return Rules_StoreEvaluatedNodesAsMultifield(a1, *(_DWORD *)(dword_51A960 + 6), 1, a2);
}
// 51A960: using guessed type int dword_51A960;

//----- (0049D480) --------------------------------------------------------
signed int  Rules_SetGenFunction(int a1, double a2)
{
  signed int result; // eax
  int v3; // [esp-8h] [ebp-24h] BYREF
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-8h]

  v5 = a1;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &v3, 1, a2) )
    return dword_51ACD0;
  result = *(_DWORD *)(v4 + 16);
  if ( result < 1 )
  {
    Parser_ReportError(1, (int)aNumberGreaterT);
    return dword_51ACD0;
  }
  else
  {
    dword_51ACD0 = *(_DWORD *)(v4 + 16);
  }
  return result;
}
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D500) --------------------------------------------------------
signed int *__fastcall Rules_GensymFunction(int a1, int a2)
{
  char v3[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v4; // [esp+14h] [ebp-8h]

  v4 = a1;
  Lexer_TokenExpect(0);
  sprintf_(v3, "gen%ld", dword_51ACD0);
  return Str_Intern(v3, ++dword_51ACD0);
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACD0: using guessed type int dword_51ACD0;

//----- (0049D550) --------------------------------------------------------
signed int *__thiscall Rules_GensymStarFunction(void *this)
{
  int v1; // ecx
  char v3[20]; // [esp+0h] [ebp-18h] BYREF
  void *v4; // [esp+14h] [ebp-4h]

  v4 = this;
  Lexer_TokenExpect(0);
  do
  {
    sprintf_(v3, "gen%ld", dword_51ACD0);
    ++dword_51ACD0;
  }
  while ( Rules_FindSymbolEntry(v3) );
  return Str_Intern(v3, v1);
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
int  Rules_HostSeed(int a1, double a2)
{
  int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, v3, 1, a2);
    if ( result )
      return j_srand_();
  }
  return result;
}
// 47D530: using guessed type int j_srand_(void);

//----- (0049D620) --------------------------------------------------------
int  Rules_HostLength(double a1)
{
  int result; // eax
  int v2; // edx
  int v3; // [esp-4h] [ebp-20h] BYREF
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+4h] [ebp-18h]
  int v6; // [esp+8h] [ebp-14h]
  int v7; // [esp+Ch] [ebp-10h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, &v3, a1);
    if ( v4 == 3 || v4 == 2 )
    {
      return strlen(*(const char **)(v5 + 16));
    }
    else if ( v4 == 4 )
    {
      return v7 - v6 + 1;
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
int  Rules_HostConserveMem(int a1, double a2)
{
  int result; // eax
  int v3; // edx
  int v4; // ecx
  _DWORD v5[9]; // [esp-8h] [ebp-24h] BYREF

  v5[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, v5, 2, a2);
    if ( result )
    {
      if ( !strcmp_(*(_DWORD *)(v5[2] + 16), aOn_0) || !strcmp_(v4, aOff_0) )
        return unknown_libname_5(v4, v3);
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
int ** Rules_HostApropos(double a1)
{
  int **result; // eax
  int ***v2; // esi
  char *v3; // ebp
  unsigned int v4; // kr04_4
  int v5; // ecx
  int v6; // ecx
  _DWORD v7[12]; // [esp+0h] [ebp-30h] BYREF

  result = (int **)Lexer_TokenExpect(1);
  v2 = 0;
  if ( result != (int **)-1 )
  {
    result = (int **)Lexer_ParseValueList(1, v7, 2, a1);
    if ( result )
    {
      v3 = *(char **)(v7[2] + 16);
      v4 = strlen(v3) + 1;
      while ( 1 )
      {
        result = Rules_GetNextSymbolMatch((int **)v3, v4 - 1, 1, v2, 0);
        v2 = (int ***)result;
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
int  Rules_HostExpansionCall(int a1, double a2)
{
  int **Symbol; // eax
  _DWORD *v4; // edx
  signed int v5; // ecx
  int v6; // eax
  __int16 *v7; // edi
  _DWORD *v8; // eax
  __int16 v9; // dx
  int v10; // eax
  int v11; // ecx
  int v13; // ebx
  int v14; // eax
  int v15[7]; // [esp+0h] [ebp-1Ch] BYREF

  v15[0] = AST_CloneNodeList(*(_DWORD *)(*(_DWORD *)(dword_51A960 + 6) + 6));
  Symbol = Rules_MakeSymbol(aExpand);
  Rules_ExpandFuncCallForm((int **)a1, (_DWORD *)v15[0], (int)Symbol, v15, a2);
  v4 = *(_DWORD **)(dword_54DBA8 + 56);
  if ( v4 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 56);
    *(_DWORD *)(dword_54DBA8 + 56) = *v4;
    v5 = dword_54DBAC;
  }
  else
  {
    v5 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_WORD *)v5 = **(_WORD **)(dword_51A960 + 6);
  v6 = *(_DWORD *)(*(_DWORD *)(dword_51A960 + 6) + 2);
  *(_DWORD *)(v5 + 10) = 0;
  *(_DWORD *)(v5 + 2) = v6;
  v7 = (__int16 *)v5;
  v8 = (_DWORD *)v15[0];
  v9 = *(_WORD *)v5;
  *(_DWORD *)(v5 + 6) = v15[0];
  if ( v9 == 10 )
  {
    v13 = *(_DWORD *)(v5 + 2);
    v14 = AST_CountListNodes((int)v8);
    if ( !Rules_CheckFunctionArgCount(*(_DWORD *)(*(_DWORD *)v13 + 16), *(_BYTE **)(v13 + 17), v14) )
    {
      *(_DWORD *)(a1 + 4) = 2;
      *(_DWORD *)(a1 + 8) = dword_54DD70;
      return AST_Free(v5);
    }
  }
  else if ( v9 == 12 )
  {
    v10 = AST_CountListNodes((int)v8);
    if ( !Deffunction_CheckArgumentCount(*(_DWORD *)(v11 + 2), v10) )
    {
      *(_DWORD *)(a1 + 4) = 2;
      *(_DWORD *)(a1 + 8) = dword_54DD70;
      AST_Free(v5);
      return Lexer_ErrorRecover(1);
    }
  }
  Parser_ParseForm(v7, (_DWORD *)a1, v5, a2);
  return AST_Free((int)v7);
}
// 49DDBA: variable 'v11' is possibly undefined
// 49DDDB: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DE60) --------------------------------------------------------
signed int  Rules_HostExpandDummy(int a1)
{
  int v1; // edx
  int v2; // ecx

  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = dword_54DD70;
  Lexer_ErrorRecover(1);
  Rules_PrintErrorID((int)aMiscfun, v1, 0);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpandMustBeUs, v2);
}
// 49DE88: variable 'v1' is possibly undefined
// 49DE97: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (0049DEA0) --------------------------------------------------------
int ** Rules_ExpandFuncCallForm(int **result, _DWORD *a2, int a3, int *a4, double a5)
{
  int **v5; // edi
  _DWORD *v6; // esi
  int v7; // edx
  _DWORD *v8; // ebx
  signed int v9; // eax
  int v10; // ebx
  int v12; // [esp+4h] [ebp-18h]
  int v13; // [esp+8h] [ebp-14h]
  int v14; // [esp+Ch] [ebp-10h]

  v5 = result;
  v6 = a2;
  v12 = a3;
  if ( a2 )
  {
    while ( 1 )
    {
      while ( v12 != *(_DWORD *)((char *)v6 + 2) )
      {
        a3 = *(_DWORD *)((char *)v6 + 6);
        if ( a3 )
          Rules_ExpandFuncCallForm((int)v5, *(_DWORD *)((char *)v6 + 6), v12, (int)v6 + 6, a5);
        result = (int **)((char *)v6 + 10);
        a4 = (_DWORD *)((char *)v6 + 10);
        v6 = *(_DWORD **)((char *)v6 + 10);
        if ( !v6 )
          return result;
      }
      Parser_ParseForm(*(__int16 **)((char *)v6 + 6), v5, a3, a5);
      AST_Free(*(_DWORD *)((char *)v6 + 6));
      if ( dword_51A964 || v5[1] != (int *)4 )
        break;
      a3 = (int)v5[3] + 1;
      v14 = dword_51A964;
      v13 = dword_51A964;
      v7 = 6 * a3 - 6;
      while ( a3 <= (int)v5[4] + 1 )
      {
        v8 = *(_DWORD **)(dword_54DBA8 + 56);
        if ( v8 )
        {
          dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 56);
          *(_DWORD *)(dword_54DBA8 + 56) = *v8;
          v9 = dword_54DBAC;
        }
        else
        {
          v9 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
        }
        *(_WORD *)v9 = *(_WORD *)((char *)v5[2] + v7 + 14);
        v10 = *(int *)((char *)v5[2] + v7 + 16);
        *(_DWORD *)(v9 + 6) = 0;
        *(_DWORD *)(v9 + 2) = v10;
        *(_DWORD *)(v9 + 10) = 0;
        if ( v13 )
          *(_DWORD *)(v14 + 10) = v9;
        else
          v13 = v9;
        v14 = v9;
        v7 += 6;
        ++a3;
      }
      if ( v13 )
      {
        *(_DWORD *)(v14 + 10) = *(_DWORD *)((char *)v6 + 10);
        *a4 = v13;
        dword_54DBAC = (int)v6;
        *v6 = *(_DWORD *)(dword_54DBA8 + 56);
        *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
        result = (int **)(v14 + 10);
        v6 = *(_DWORD **)(v14 + 10);
        a4 = (int *)(v14 + 10);
        if ( !v6 )
          return result;
      }
      else
      {
        *a4 = *(_DWORD *)((char *)v6 + 10);
        dword_54DBAC = (int)v6;
        *v6 = *(_DWORD *)(dword_54DBA8 + 56);
        result = (int **)dword_54DBA8;
        *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
        v6 = (_DWORD *)*a4;
        if ( !*a4 )
          return result;
      }
    }
    *(_DWORD *)((char *)v6 + 6) = 0;
    if ( !dword_51A964 && v5[1] != (int *)4 )
      Rules_ReportSymbolTypeError(aExpand, 1);
    result = Rules_MakeSymbol(aSetEvaluationE);
    *(_DWORD *)((char *)v6 + 2) = result;
    dword_51A964 = 0;
    dword_51A968 = 0;
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
  return dword_54DD70;
}
// 49E070: using guessed type int sub_49E070();
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E080) --------------------------------------------------------
int  Rules_HostSetSequenceOperatorRecognition(int a1, double a2)
{
  _DWORD v4[9]; // [esp-8h] [ebp-24h] BYREF

  v4[7] = a1;
  if ( Lexer_ParseValueList(1, v4, 2, a2) )
    return unknown_libname_13(v4[2] != dword_54DD70);
  else
    return dword_51B360;
}
// 51B360: using guessed type int dword_51B360;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049E0D0) --------------------------------------------------------
signed int * Rules_HostGetFunctionRestrictions(int a1, double a2)
{
  int v3; // ecx
  int **Symbol; // eax
  char *v5; // eax
  int v7; // [esp-8h] [ebp-24h] BYREF
  int v8; // [esp+0h] [ebp-1Ch]
  int v9; // [esp+14h] [ebp-8h]

  v9 = a1;
  if ( !Lexer_ParseValueList(1, &v7, 2, a2) )
  {
    v5 = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(v5, v3);
  }
  Symbol = Rules_MakeSymbol(*(_BYTE **)(v8 + 16));
  if ( !Symbol )
  {
    Rules_ReportCantFindItem(v3, *(_DWORD *)(v8 + 16));
    Lexer_ErrorRecover(1);
    v5 = (char *)&g_Rules_HostFunctionErrorFallbackString;
    return Str_Intern(v5, v3);
  }
  if ( !*(int **)((char *)Symbol + 17) )
  {
    v5 = a0_0;
    return Str_Intern(v5, v3);
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
int  Rules_HostPrintout(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // edi
  int v5; // esi
  int v6; // ebx
  int v7; // ecx
  char *v8; // edx
  int v9; // eax
  int logical_name; // ecx
  int v10; // [esp-4h] [ebp-2Ch] BYREF
  unsigned int v11; // [esp+0h] [ebp-28h]
  int v12; // [esp+4h] [ebp-24h]
  int v13; // [esp+20h] [ebp-8h]

  v13 = a1;
  result = Lexer_TokenExpect(1);
  v4 = result;
  v5 = result;
  if ( result != -1 )
  {
    logical_name = Rules_GetLogicalNameArg(1, (int)aStdout_0, v3, a2);
    if ( !logical_name )
    {
      Rules_ReportIllegalLogicalName();
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    result = IO_QueryRouters(logical_name);
    if ( !result )
      return IO_ReportUnrecognizedRouter(logical_name);
    v6 = 2;
    if ( v4 >= 2 )
    {
      while ( 1 )
      {
        result = Rules_RtnUnknown(v6, &v10, a2);
        if ( dword_51A968 )
          return result;
        if ( v11 < 2 )
          goto LABEL_26;
        if ( v11 > 2 )
        {
          if ( v11 == 3 )
            goto LABEL_17;
LABEL_26:
          result = Rules_PrintDataObject(v7, (int)&v10);
          if ( ++v6 > v5 )
            return result;
        }
        else
        {
          if ( strcmp_(v7, aCrlf) )
          {
            if ( !strcmp_(v7, aTab) )
            {
              v8 = asc_5069C0;
              goto LABEL_11;
            }
            if ( !strcmp_(v7, aVtab) )
            {
              v8 = asc_5069CC;
              goto LABEL_11;
            }
            if ( !strcmp_(v7, aFf) )
            {
              v8 = (char *)&g_Rules_PrintoutFormFeedChar;
              goto LABEL_11;
            }
            if ( strcmp_(v7, &g_Rules_PrintoutCrlfAliasName) )
            {
LABEL_17:
              v9 = v7;
              v8 = *(char **)(v12 + 16);
              goto LABEL_12;
            }
          }
          v8 = asc_5069B8;
LABEL_11:
          v9 = v7;
LABEL_12:
          result = Output_Write(logical_name, (int)v8, v7);
          if ( ++v6 > v5 )
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
signed int * Rules_HostRead(int a1, double a2)
{
  int v3; // eax
  int v4; // ecx
  char *v5; // esi
  int v6; // ecx
  unsigned int v7; // ecx
  int v8; // eax
  signed int *result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // [esp+0h] [ebp-1Ch] BYREF
  signed int *v14; // [esp+4h] [ebp-18h]
  char *v15; // [esp+8h] [ebp-14h]
  int v16; // [esp+14h] [ebp-8h]

  v16 = a1;
  v3 = Lexer_TokenExpect(1);
  v5 = 0;
  if ( v3 == -1 )
    goto LABEL_14;
  if ( v3 )
  {
    if ( v3 == 1 )
    {
      v5 = (char *)Rules_GetLogicalNameArg(1, (int)aStdin, v4, a2);
      if ( !v5 )
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
    v5 = aStdin;
  }
  if ( !IO_QueryRouters((int)v5) )
  {
    IO_ReportUnrecognizedRouter((int)v5);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    goto LABEL_14;
  }
  if ( !strcmp_(v6, aStdin) )
    Rules_ReadStdinLineToken(&v13, v7);
  else
    Parser_NextToken((int)v5, (int)&v13);
  v8 = v13;
  g_Lexer_PendingLineCharIndex = -1;
  *(_DWORD *)(v4 + 4) = v13;
  switch ( v8 )
  {
    case 0:
    case 3:
    case 8:
    case 2:
    case 1:
      result = v14;
      *(_DWORD *)(v4 + 8) = v14;
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
      result = Str_Intern(v15, v4);
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
signed int * Rules_ReadStdinLineToken(_DWORD *a1, unsigned int a2)
{
  char *appended; // edi
  int i; // esi
  unsigned int v5; // ecx
  signed int *result; // eax
  unsigned int v7[7]; // [esp+0h] [ebp-1Ch] BYREF

  *a1 = 102;
  do
  {
    appended = 0;
    g_Lexer_PendingLineCharIndex = 0;
    v7[0] = 0;
    for ( i = Lexer_PeekChar((int)aStdin, a2); i != 10; i = Lexer_PeekChar((int)aStdin, v5) )
    {
      if ( i == 13 )
        break;
      if ( i == -1 )
        break;
      if ( Rules_GetEvaluationErrorFlag() )
        break;
      appended = Str_AppendCharEscaping(i, appended, v7, &g_Lexer_PendingLineCharIndex, v7[0] + 80);
    }
    IO_OpenStringSource((int)aRead, appended, 0);
    Parser_NextToken((int)aRead, (int)a1);
    IO_CloseStringRouter((int)aRead);
    if ( (int)v7[0] > 0 )
      Mem_SmallBlockFree(appended, v7[0]);
    result = (signed int *)Rules_GetEvaluationErrorFlag();
    if ( result )
    {
      *a1 = 3;
      result = Str_Intern(aReadError, a2);
      a1[1] = result;
    }
    if ( *a1 == 102 && i == -1 )
    {
      *a1 = 2;
      result = Str_Intern(aEof, a2);
      a1[1] = result;
    }
  }
  while ( *a1 == 102 );
  return result;
}
// 49E581: variable 'a2' is possibly undefined
// 49E5BE: variable 'v5' is possibly undefined
// 51A628: using guessed type int dword_51A628;

//----- (0049E650) --------------------------------------------------------
const CHAR * Rules_HostOpen(double a1)
{
  int v1; // ebx
  const CHAR *result; // eax
  int v3; // ecx
  const CHAR *v4; // edi
  const char *v5; // esi
  char *v6; // ecx
  unsigned __int8 *v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  _DWORD v13[12]; // [esp+0h] [ebp-30h] BYREF

  v1 = Rules_ArgRangeCheck((int)aOpen, 3);
  if ( v1 == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, 0, a1);
  v4 = result;
  if ( result )
  {
    v5 = (const char *)Rules_GetLogicalNameArg(2, 0, v3, a1);
    if ( !v5 )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_ReportIllegalLogicalName();
      return 0;
    }
    if ( ismbdprint_((void *)v5) )
    {
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      Rules_PrintErrorID((int)aIofun, v9, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLogicalName_0, v10);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v5, v11);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAlreadyInUse_, v12);
      return 0;
    }
    if ( v1 == 2 )
    {
      v6 = aR_3;
    }
    else if ( v1 == 3 )
    {
      result = (const CHAR *)Lexer_ParseValueList(3, v13, 3, a1);
      if ( !result )
        return result;
      v6 = *(char **)(v13[2] + 16);
    }
    if ( !strcmp_(v6, aR_3) || !strcmp_(v7, aR_4) || !strcmp_(v7, aW_4) || !strcmp_(v7, aA_2) )
    {
      return (const CHAR *)IO_OpenNamedFile(v4, v7, (int)v7, v5, (DWORD)v5);
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
signed int  Rules_HostClose(double a1)
{
  int v1; // eax
  void *v2; // ecx
  int v3; // eax

  v1 = Lexer_TokenExpect(1);
  if ( v1 == -1 )
    return 0;
  if ( !v1 )
    return IO_CloseAllNamedFiles(v2);
  v3 = Rules_GetLogicalNameArg(1, 0, (int)v2, a1);
  if ( !v3 )
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return IO_CloseNamedFile(v3);
}
// 49E846: variable 'v2' is possibly undefined

//----- (0049E890) --------------------------------------------------------
int  Rules_HostRemoveFile(double a1)
{
  int v1; // ecx
  int result; // eax
  int v3; // edx
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v1, a1);
  if ( result )
    return Rules_BloadDeleteFile(v4, v3);
  return result;
}
// 49E8B7: variable 'v1' is possibly undefined
// 49E8C0: variable 'v4' is possibly undefined
// 49E8C0: variable 'v3' is possibly undefined

//----- (0049E8D0) --------------------------------------------------------
const CHAR * Rules_HostRenameFile(double a1)
{
  int v1; // ecx
  const CHAR *result; // eax
  const CHAR *v3; // ecx

  if ( Lexer_TokenExpect(2) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v1, a1);
  if ( result )
  {
    result = (const CHAR *)Rules_GetFileNameArg(2, (int)result, a1);
    if ( result )
      return (const CHAR *)Rules_RenameFile(v3, result, (int)v3);
  }
  return result;
}
// 49E8F9: variable 'v1' is possibly undefined
// 49E91B: variable 'v3' is possibly undefined

//----- (0049E930) --------------------------------------------------------
signed int * Rules_HostFormat(double a1)
{
  signed int *v1; // ebp
  char *v2; // esi
  int v3; // ecx
  int v4; // ebx
  int v6; // ecx
  int v7; // ecx
  signed int v8; // ebp
  char v9; // ah
  int v10; // ecx
  int v11; // edi
  _BYTE *i; // eax
  int v13; // edi
  int v14; // ecx
  char v15; // cl
  unsigned __int8 v16; // ch
  int v17; // edx
  int v18; // eax
  const char *v19; // eax
  signed int *v20; // eax
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  char v24[512]; // [esp+0h] [ebp-284h] BYREF
  char v25[80]; // [esp+200h] [ebp-84h] BYREF
  int v26; // [esp+250h] [ebp-34h] BYREF
  int v27; // [esp+254h] [ebp-30h] BYREF
  int v28; // [esp+258h] [ebp-2Ch] BYREF
  int v29; // [esp+25Ch] [ebp-28h] BYREF
  int v30; // [esp+260h] [ebp-24h]
  int v31; // [esp+264h] [ebp-20h]
  signed int *v32; // [esp+268h] [ebp-1Ch]

  v30 = 3;
  v26 = 0;
  v27 = 0;
  v28 = 0;
  v1 = Str_Intern(g_Rules_HostFormatEmptyResult, 0);
  v32 = v1;
  v2 = 0;
  v4 = Lexer_TokenExpect(2);
  if ( v4 == -1 )
    return v1;
  v6 = Rules_GetLogicalNameArg(1, (int)aStdout_0, v3, a1);
  v31 = v6;
  if ( v6 )
  {
    if ( !strcmp_(v6, aNil_0) || IO_QueryRouters(v6) )
    {
      v8 = Rules_FormatCountConversionSpecs(v4, a1);
      if ( v8 )
      {
        while ( 1 )
        {
          v9 = *(_BYTE *)(v8 + v26);
          if ( !v9 )
            break;
          if ( v9 == 37 )
          {
            v13 = v26++;
            LOBYTE(v14) = Rules_FormatParseFlag(v8, &v26, &v29, v24);
            BYTE1(v14) = v14;
            if ( (_BYTE)v14 == 32 )
            {
              v2 = Str_Append(v24, v2, (unsigned int *)&v27, &v28);
              if ( !v2 )
                return v32;
            }
            else
            {
              strncpy_(v14, v13 + v8);
              v17 = v29;
              v25[v26 - v13] = 0;
              if ( !v17 && (v15 == 100 || v15 == 111 || v15 == 117 || v15 == 120) )
              {
                v18 = v26 - v13;
                v24[v18 + 511] = 108;
                v25[v18] = v16;
                v29 = 1;
                v25[v18 + 1] = 0;
              }
              v19 = (const char *)Rules_FormatConvertArg(v25, v30, v29, v16, a1);
              if ( !v19 )
              {
                if ( v2 )
                  Mem_SmallBlockFree(v2, v27);
                return v32;
              }
              v2 = Str_Append(v19, v2, (unsigned int *)&v27, &v28);
              if ( !v2 )
                return v32;
              ++v30;
            }
          }
          else
          {
            v10 = v26;
            v11 = 0;
            for ( i = (_BYTE *)(v8 + v26); *i != 37; ++v11 )
            {
              if ( !*i )
                break;
              if ( v11 >= 80 )
                break;
              ++i;
              ++v26;
            }
            v2 = Str_AppendBounded(v10 + v8, v2, &v28, v26 - v10, (unsigned int *)&v27);
          }
        }
        if ( v2 )
        {
          v20 = Str_Intern(v2, v7);
          if ( strcmp_(v20, v21) )
            Output_Write(v31, (int)v2, v22);
          Mem_SmallBlockFree(v2, v27);
          return (signed int *)v23;
        }
        else
        {
          return Str_Intern(g_Rules_HostFormatEmptyResult, v7);
        }
      }
      else
      {
        return v32;
      }
    }
    else
    {
      IO_ReportUnrecognizedRouter(v31);
      return v1;
    }
  }
  else
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return v1;
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
signed int  Rules_FormatCountConversionSpecs(int a1, double a2)
{
  signed int result; // eax
  int v4; // edi
  int v5; // esi
  char v6; // dl
  _DWORD v7[6]; // [esp+0h] [ebp-44h] BYREF
  _BYTE v8[12]; // [esp+18h] [ebp-2Ch] BYREF
  int v9; // [esp+24h] [ebp-20h] BYREF
  int v10[7]; // [esp+28h] [ebp-1Ch] BYREF

  result = Lexer_ParseValueList(2, v7, 3, a2);
  if ( result )
  {
    v4 = 0;
    v5 = *(_DWORD *)(v7[2] + 16);
    v10[0] = 0;
    while ( 1 )
    {
      v6 = *(_BYTE *)(v5 + v10[0]);
      if ( !v6 )
        break;
      if ( v6 == 37 )
      {
        ++v10[0];
        if ( Rules_FormatParseFlag(v5, v10, &v9, v8) != 32 )
          ++v4;
      }
      else
      {
        ++v10[0];
      }
    }
    if ( v4 == a1 - 2 )
    {
      return v5;
    }
    else
    {
      Rules_ExpectedCountError((int)aFormat, v4 + 2);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}

//----- (0049ED50) --------------------------------------------------------
char  Rules_FormatParseFlag(int a1, int *a2, _DWORD *a3, _BYTE *a4)
{
  int v6; // esi
  char v7; // bl
  _BYTE *v8; // ecx
  char *v9; // eax
  char result; // al
  _DWORD *v11; // edx
  _DWORD *v12; // edx
  _DWORD *v13; // edx
  _DWORD *v14; // edx
  _DWORD *v15; // edx
  int v16; // [esp+0h] [ebp-18h]

  v6 = 0;
  *a3 = 0;
  v7 = *(_BYTE *)(*a2 + a1);
  switch ( v7 )
  {
    case 'n':
      sprintf_(a4, asc_5069B8);
      result = 32;
      ++*v11;
      break;
    case 'r':
      sprintf_(a4, asc_506A6C);
      result = 32;
      ++*v12;
      break;
    case 't':
      sprintf_(a4, asc_5069C0);
      result = 32;
      ++*v13;
      break;
    case 'v':
      sprintf_(a4, asc_5069CC);
      result = 32;
      ++*v14;
      break;
    case '%':
      sprintf_(a4, asc_506A70);
      result = 32;
      ++*v15;
      break;
    default:
      v16 = *a2;
      *a4 = 0;
      v8 = a4;
      while ( 1 )
      {
        v9 = (char *)(*a2 + a1);
        if ( *v9 == 37 || !*v9 || *a2 - v16 >= 80 )
          return 32;
        result = *v9;
        ++v8;
        a4[v6++] = result;
        *v8 = 0;
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
        ++*a2;
      }
      if ( *(_BYTE *)(a1 + *a2 - 1) == 108 )
        *a3 = 1;
      ++*a2;
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
        const char *a1,
        int a2,
        int a3,
        unsigned int a4,
        double a5)
{
  signed int result; // eax
  _DWORD *v8; // eax
  char *v9; // ecx
  signed int v10; // esi
  int v11; // edx
  _DWORD *v12; // ecx
  int v13; // ecx
  _DWORD *v14; // eax
  _DWORD *v15; // eax
  int v17; // eax
  _DWORD *v18; // eax
  double v20; // [esp+0h] [ebp-30h]
  int v21; // [esp+8h] [ebp-28h] BYREF
  int v22; // [esp+Ch] [ebp-24h]
  int v23; // [esp+10h] [ebp-20h]
  int v24; // [esp+20h] [ebp-10h]

  if ( a4 >= 0x67 )
  {
    if ( a4 <= 0x67 )
      goto LABEL_19;
    if ( a4 >= 0x73 )
    {
      if ( a4 <= 0x73 )
      {
        result = Lexer_ParseValueList(a2, &v21, 111, a5);
        if ( !result )
          return result;
        v14 = Mem_SmallBlockAlloc(strlen(*(const char **)(v23 + 16)) + strlen(a1) + 200);
        sprintf_(v14, a1, *(_DWORD *)(v23 + 16));
        goto LABEL_6;
      }
      if ( a4 < 0x75 || a4 > 0x75 && a4 != 120 )
        goto LABEL_17;
    }
    else if ( a4 != 111 )
    {
      goto LABEL_17;
    }
LABEL_11:
    result = Lexer_ParseValueList(a2, &v21, 110, a5);
    if ( !result )
      return result;
    v15 = Mem_SmallBlockAlloc(strlen(a1) + 200);
    if ( v22 )
    {
      sprintf_(v15, a1, *(_DWORD *)(v23 + 16));
    }
    else
    {
      v24 = (int)*(double *)(v23 + 16);
      sprintf_(v17, a1, v24);
    }
LABEL_6:
    v10 = Str_Intern(v9, (int)v9)[4];
    Mem_SmallBlockFree(v12, v11);
    return v10;
  }
  if ( a4 < 0x64 )
  {
    if ( a4 == 99 )
    {
      result = Lexer_ParseValueList(a2, &v21, 111, a5);
      if ( !result )
        return result;
      v8 = Mem_SmallBlockAlloc(strlen(a1) + 200);
      sprintf_(v8, a1, **(unsigned __int8 **)(v23 + 16));
      goto LABEL_6;
    }
LABEL_17:
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aErrorInFormatT, a3);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForFormattedOu, v13);
    return 0;
  }
  if ( a4 <= 0x64 )
    goto LABEL_11;
LABEL_19:
  result = Lexer_ParseValueList(a2, &v21, 110, a5);
  if ( result )
  {
    v18 = Mem_SmallBlockAlloc(strlen(a1) + 200);
    if ( v22 )
    {
      v20 = (double)*(int *)(v23 + 16);
      sprintf_(v18, a1, v20);
    }
    else
    {
      sprintf_(v18, a1, *(double *)(v23 + 16));
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
signed int * Rules_HostReadline(int a1, unsigned int a2, double a3)
{
  int v3; // eax
  int v4; // ecx
  char *v5; // esi
  unsigned int v6; // ecx
  char *v7; // ebx
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
  unsigned int v18[5]; // [esp+0h] [ebp-14h] BYREF

  v18[3] = a2;
  v18[0] = 0;
  *(_DWORD *)(a1 + 4) = 3;
  v3 = Lexer_TokenExpect(1);
  if ( v3 == -1 )
  {
    result = Str_Intern(aReadError, v4);
LABEL_8:
    *(_DWORD *)(v10 + 8) = result;
    return result;
  }
  if ( v3 )
  {
    v5 = (char *)Rules_GetLogicalNameArg(1, (int)aStdin, v4, a3);
    if ( !v5 )
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
    v5 = aStdin;
  }
  if ( !IO_QueryRouters((int)v5) )
  {
    IO_ReportUnrecognizedRouter((int)v5);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    result = Str_Intern(aReadError, v13);
    *(_DWORD *)(v14 + 8) = result;
    return result;
  }
  g_Lexer_PendingLineCharIndex = 0;
  v7 = Rules_ReadLineWithEscaping((int)v5, &g_Lexer_PendingLineCharIndex, v18, v6);
  g_Lexer_PendingLineCharIndex = -1;
  if ( !Rules_GetEvaluationErrorFlag() )
  {
    if ( v7 )
    {
      v16 = Str_Intern(v7, v8);
      *(_DWORD *)(v17 + 8) = v16;
      return (signed int *)Mem_SmallBlockFree(v7, v18[0]);
    }
    result = Str_Intern(aEof, v8);
    *(_DWORD *)(v10 + 4) = 2;
    goto LABEL_8;
  }
  result = Str_Intern(aReadError, v8);
  *(_DWORD *)(v15 + 8) = result;
  if ( v7 )
    return (signed int *)Mem_SmallBlockFree(v7, v18[0]);
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
char * Rules_ReadLineWithEscaping(int a1, int *a2, unsigned int *a3, unsigned int a4)
{
  int v5; // esi
  char *appended; // edx
  unsigned int v7; // ecx

  v5 = Lexer_PeekChar(a1, a4);
  appended = 0;
  if ( v5 == -1 )
    return 0;
  while ( v5 != 10 && v5 != 13 && v5 != -1 && !Rules_GetEvaluationErrorFlag() )
  {
    appended = Str_AppendCharEscaping(v5, appended, a3, a2, *a3 + 80);
    v5 = Lexer_PeekChar(a1, v7);
  }
  return Str_AppendCharEscaping(0, appended, a3, a2, *a3 + 80);
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
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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
BOOL  Rules_HostStringp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] == 3 )
      return 1;
  }
  return result;
}

//----- (0049F7E0) --------------------------------------------------------
BOOL  Rules_HostSymbolp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] == 2 )
      return 1;
  }
  return result;
}

//----- (0049F830) --------------------------------------------------------
BOOL  Rules_HostLexemep(double a1)
{
  BOOL result; // eax
  int v3; // [esp-4h] [ebp-20h] BYREF
  int v4; // [esp+0h] [ebp-1Ch]

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &v3, a1);
    if ( v4 == 2 || v4 == 3 )
      return 1;
  }
  return result;
}

//----- (0049F880) --------------------------------------------------------
BOOL  Rules_HostNumberp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] <= 1u )
      return 1;
  }
  return result;
}
// 49F8B5: simplified comparisons for '%var_1C.4': !=0 && !=1 became >=2u

//----- (0049F8D0) --------------------------------------------------------
BOOL  Rules_HostFloatp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( !v3[1] )
      return 1;
  }
  return result;
}

//----- (0049F920) --------------------------------------------------------
BOOL  Rules_HostIntegerp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] == 1 )
      return 1;
  }
  return result;
}

//----- (0049F960) --------------------------------------------------------
BOOL  Rules_HostMultifieldp(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] == 4 )
      return 1;
  }
  return result;
}

//----- (0049F9B0) --------------------------------------------------------
BOOL  Rules_PointerpFunction(double a1)
{
  BOOL result; // eax
  _DWORD v3[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, v3, a1);
    if ( v3[1] == 5 )
      return 1;
  }
  return result;
}

//----- (0049FA00) --------------------------------------------------------
int  Rules_NotFunction(int a1, double a2)
{
  uintptr_t expression; // eax
  _DWORD parsed[6]; // [esp-4h] [ebp-1Ch] BYREF

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
  if ( !expression )
    return 0;
  if ( Parser_ParseForm((__int16 *)expression, parsed, a1, a2) )
    return 0;
  return parsed[2] == dword_54DD70 && parsed[1] == 2;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FA50) --------------------------------------------------------
int  Rules_AndFunction(int a1, double a2)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)a1;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
  if ( !expression )
    return 1;
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, a2) )
      return 0;
    if ( parsed[2] == dword_54DD70 && parsed[1] == 2 )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FAB0) --------------------------------------------------------
int  Rules_OrFunction(int a1, double a2)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)a1;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, a2) )
      return 0;
    if ( parsed[2] != dword_54DD70 || parsed[1] != 2 )
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
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int i; // edi
  int v7; // eax
  int v8; // [esp+0h] [ebp-44h] BYREF
  int v9; // [esp+4h] [ebp-40h]
  int v10; // [esp+8h] [ebp-3Ch]
  int v11; // [esp+18h] [ebp-2Ch] BYREF
  int v12; // [esp+1Ch] [ebp-28h]
  int v13; // [esp+20h] [ebp-24h]
  int v14; // [esp+38h] [ebp-Ch]
  int v15; // [esp+3Ch] [ebp-8h]

  v15 = a1;
  v14 = a3;
  v3 = *(_DWORD *)(dword_51A960 + 6);
  if ( v3 )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)v3, 0, &v8, result, 1);
    if ( v4 )
    {
      v5 = *(_DWORD *)(v3 + 10);
      for ( i = 2; v5; ++i )
      {
        result = Rules_CoerceFormToNumericArg((__int16 *)v5, 0, &v11, result, i);
        if ( !v7 )
          break;
        if ( v9 == 1 )
        {
          if ( v12 == 1 )
          {
            if ( *(_DWORD *)(v10 + 16) > *(_DWORD *)(v13 + 16) )
              return result;
          }
          else if ( (double)*(int *)(v10 + 16) > *(double *)(v13 + 16) )
          {
            return result;
          }
        }
        else if ( v12 == 1 )
        {
          if ( (double)*(int *)(v13 + 16) < *(double *)(v10 + 16) )
            return result;
        }
        else if ( *(double *)(v10 + 16) > *(double *)(v13 + 16) )
        {
          return result;
        }
        v9 = v12;
        v10 = v13;
        v5 = *(_DWORD *)(v5 + 10);
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

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_51A960 + 6);
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

