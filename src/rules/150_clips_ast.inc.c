/* CLIPS AST construction, output, and compiler-front-end helpers.
 * Original function-marker range: 0x004943E0..0x00495E80.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004943E0) --------------------------------------------------------
signed int  AST_NewNode(__int16 a1, int a2)
{
  __int16 v2; // cx
  _DWORD *v3; // ebx
  signed int result; // eax

  v2 = a1;
  v3 = *(_DWORD **)(dword_54DBA8 + 56);
  if ( v3 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 56);
    *(_DWORD *)(dword_54DBA8 + 56) = *v3;
    result = dword_54DBAC;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_DWORD *)(result + 10) = 0;
  *(_DWORD *)(result + 6) = 0;
  *(_WORD *)result = v2;
  *(_DWORD *)(result + 2) = a2;
  return result;
}
// 49440E: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00494440) --------------------------------------------------------
signed int  Rules_PrintFieldExprList(signed int result, __int16 *a2)
{
  int v2; // ecx
  __int16 *v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *v7; // edx
  int v8; // eax
  int v9; // edi

  v2 = result;
  v3 = a2;
  if ( a2 )
  {
    while ( v3 )
    {
      switch ( *v3 )
      {
        case 10:
          Output_Write(v2, (int)asc_504DE0, v2);
          Output_Write(v4, *(_DWORD *)(**(_DWORD **)(v3 + 1) + 16), v4);
          if ( *(_DWORD *)(v3 + 3) )
            Output_Write(v5, (int)asc_504DE4, v5);
          Rules_PrintFieldExprList(v5, *(_DWORD *)(v3 + 3));
          v7 = asc_504DE8;
          v8 = v6;
          goto LABEL_7;
        case 13:
        case 15:
          Output_Write(v2, (int)aQuestion_PrintSingleFieldVarPrefix, v2);
          v8 = v6;
          v7 = *(char **)(*(_DWORD *)(v3 + 1) + 16);
          goto LABEL_7;
        case 14:
        case 16:
          Output_Write(v2, (int)aQuestion_PrintMultiFieldVarPrefix, v2);
          v8 = v6;
          v7 = *(char **)(*(_DWORD *)(v3 + 1) + 16);
LABEL_7:
          result = Output_Write(v8, (int)v7, v6);
          break;
        default:
          v9 = dword_51A960;
          dword_51A960 = (int)v3;
          result = Rules_PrintAtomValue(v2, *v3, *(int **)(v3 + 1));
          dword_51A960 = v9;
          break;
      }
      v3 = *(__int16 **)(v3 + 5);
      if ( v3 )
        result = Output_Write(v2, (int)asc_504DE4, v2);
    }
  }
  return result;
}
// 494482: variable 'v2' is possibly undefined
// 494491: variable 'v4' is possibly undefined
// 4944A0: variable 'v5' is possibly undefined
// 4944B4: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (00494520) --------------------------------------------------------
_DWORD * AST_MergeFieldAccessNodes(_DWORD *result, _DWORD *a2)
{
  _DWORD *v2; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx

  v2 = result;
  if ( !result )
    return a2;
  if ( a2 )
  {
    if ( dword_54E65C != *(_DWORD *)((char *)result + 2) || dword_54E65C == *(_DWORD *)((char *)a2 + 2) )
    {
      if ( dword_54E65C == *(_DWORD *)((char *)result + 2) || dword_54E65C != *(_DWORD *)((char *)a2 + 2) )
      {
        if ( dword_54E65C == *(_DWORD *)((char *)result + 2) && dword_54E65C == *(_DWORD *)((char *)a2 + 2) )
        {
          v6 = *(_DWORD *)((char *)result + 6);
          if ( v6 )
          {
            while ( *(_DWORD *)(v6 + 10) )
              v6 = *(_DWORD *)(v6 + 10);
            *(_DWORD *)(v6 + 10) = *(_DWORD *)((char *)a2 + 6);
            dword_54DBAC = (int)a2;
            *a2 = *(_DWORD *)(dword_54DBA8 + 56);
            *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
            return v2;
          }
          else
          {
            dword_54DBAC = (int)v2;
            *v2 = *(_DWORD *)(dword_54DBA8 + 56);
            *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
            return a2;
          }
        }
        else
        {
          result = (_DWORD *)AST_NewNode(10, dword_54E65C);
          *(_DWORD *)((char *)result + 6) = v7;
          *(_DWORD *)(v7 + 10) = a2;
        }
      }
      else
      {
        v5 = *(_DWORD *)((char *)a2 + 6);
        if ( v5 )
        {
          *(_DWORD *)((char *)a2 + 6) = v2;
          *(_DWORD *)((char *)v2 + 10) = v5;
          return a2;
        }
        else
        {
          dword_54DBAC = (int)a2;
          *a2 = *(_DWORD *)(dword_54DBA8 + 56);
          *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
          return v2;
        }
      }
    }
    else
    {
      v4 = *(_DWORD *)((char *)result + 6);
      if ( v4 )
      {
        while ( *(_DWORD *)(v4 + 10) )
          v4 = *(_DWORD *)(v4 + 10);
        *(_DWORD *)(v4 + 10) = a2;
        return v2;
      }
      else
      {
        dword_54DBAC = (int)v2;
        *v2 = *(_DWORD *)(dword_54DBA8 + 56);
        *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC;
        return a2;
      }
    }
  }
  return result;
}
// 494653: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E65C: using guessed type int dword_54E65C;

//----- (00494660) --------------------------------------------------------
int  AST_AppendNodeList(int a1, int a2)
{
  int v2; // ecx

  v2 = a1;
  if ( !a1 )
    return a2;
  if ( a2 )
  {
    for ( ; *(_DWORD *)(a1 + 10); a1 = *(_DWORD *)(a1 + 10) )
      ;
    *(_DWORD *)(a1 + 10) = a2;
  }
  return v2;
}

//----- (00494690) --------------------------------------------------------
void Rules_FlushPPBuffer()
{
  if ( dword_51AA28 )
  {
    dword_51AA20 = 0;
    dword_51AA24 = 0;
    dword_51AA18 = 0;
    *(_BYTE *)dword_51AA28 = 0;
  }
}
// 51AA18: using guessed type int dword_51AA18;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (004946C0) --------------------------------------------------------
signed int Rules_DestroyPPBuffer()
{
  signed int result; // eax

  dword_51AA20 = 0;
  dword_51AA24 = 0;
  dword_51AA18 = 0;
  if ( dword_51AA28 )
    result = Mem_SmallBlockFree((_DWORD *)dword_51AA28, dword_51AA1C);
  dword_51AA28 = 0;
  dword_51AA1C = 0;
  return result;
}
// 51AA18: using guessed type int dword_51AA18;
// 51AA1C: using guessed type int dword_51AA1C;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (00494720) --------------------------------------------------------
char * Rules_SavePPBuffer(char *result)
{
  const char *v1; // esi

  v1 = result;
  if ( dword_51AA10 )
  {
    strlen(result);
    if ( (int)(strlen(result) + 1 + dword_51AA18) >= dword_51AA1C )
    {
      dword_51AA28 = (int)Mem_Realloc((char *)dword_51AA28, dword_51AA1C, dword_51AA1C + 512);
      dword_51AA1C += 512;
    }
    dword_51AA24 = dword_51AA20;
    dword_51AA20 = dword_51AA18;
    result = Str_Append(v1, (char *)dword_51AA28, (unsigned int *)&dword_51AA1C, &dword_51AA18);
    dword_51AA28 = (int)result;
  }
  return result;
}
// 51AA10: using guessed type int dword_51AA10;
// 51AA18: using guessed type int dword_51AA18;
// 51AA1C: using guessed type int dword_51AA1C;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (004947D0) --------------------------------------------------------
int Rules_BackupPPBuffer()
{
  int v0; // ebx
  int result; // eax

  if ( dword_51AA10 )
  {
    if ( dword_51AA28 )
    {
      dword_51AA18 = dword_51AA20;
      v0 = dword_51AA20;
      dword_51AA20 = dword_51AA24;
      result = dword_51AA28 + v0;
      *(_BYTE *)(dword_51AA28 + v0) = 0;
    }
  }
  return result;
}
// 51AA10: using guessed type int dword_51AA10;
// 51AA18: using guessed type int dword_51AA18;
// 51AA20: using guessed type int dword_51AA20;
// 51AA24: using guessed type int dword_51AA24;
// 51AA28: using guessed type int dword_51AA28;

//----- (00494810) --------------------------------------------------------
char *Rules_CopyPPBuffer()
{
  char *v0; // eax
  char *v1; // esi
  char *v2; // edi
  char *v3; // edx
  char v4; // al
  char v5; // al

  v0 = (char *)Mem_SmallBlockAlloc(strlen((const char *)dword_51AA28) + 1);
  v1 = (char *)dword_51AA28;
  v2 = v0;
  v3 = v0;
  do
  {
    v4 = *v1;
    *v2 = *v1;
    if ( !v4 )
      break;
    v5 = v1[1];
    v1 += 2;
    v2[1] = v5;
    v2 += 2;
  }
  while ( v5 );
  return v3;
}
// 51AA28: using guessed type int dword_51AA28;

//----- (00494860) --------------------------------------------------------
int Rules_GetPPBuffer()
{
  return dword_51AA28;
}
// 51AA28: using guessed type int dword_51AA28;

//----- (00494870) --------------------------------------------------------
char *__fastcall AST_Append(int a1, int a2)
{
  int v2; // eax
  int v3; // ecx
  char v6[128]; // [esp+2h] [ebp-80h] BYREF

  *(_DWORD *)&v6[124] = a1;
  v6[0] = 10;
  v2 = 1;
  if ( dword_51AA14 >= 1 )
  {
    v3 = dword_51AA14;
    do
      v6[v2++] = 32;
    while ( v2 <= v3 );
  }
  v6[v2] = 0;
  return IO_OutWriteToken(v6);
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948C0) --------------------------------------------------------
int  Rules_IncrementIndentDepth(int result)
{
  dword_51AA14 += result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948D0) --------------------------------------------------------
int  Rules_DecrementIndentDepth(int result)
{
  dword_51AA14 -= result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948E0) --------------------------------------------------------
int  Rules_SetIndentDepth(int result)
{
  dword_51AA14 = result;
  return result;
}
// 51AA14: using guessed type int dword_51AA14;

//----- (004948F0) --------------------------------------------------------
int  Rules_SetPPBufferStatus(int result)
{
  dword_51AA10 = result;
  return result;
}
// 51AA10: using guessed type int dword_51AA10;

//----- (00494900) --------------------------------------------------------
int Rules_GetPPBufferStatus()
{
  return dword_51AA10;
}
// 51AA10: using guessed type int dword_51AA10;

//----- (004949C0) --------------------------------------------------------
const void * Rules_BsaveAtomTables(int a1)
{
  int v1; // edx
  int v2; // edx
  int v3; // edx

  Rules_BsaveSymbolTable(a1);
  Rules_BsaveFloatTable(v1);
  Rules_BsaveIntegerTable(v2);
  return Rules_BsaveBitmapTable(v3);
}
// 4949CA: variable 'v1' is possibly undefined
// 4949D1: variable 'v2' is possibly undefined
// 4949D8: variable 'v3' is possibly undefined

//----- (004949E0) --------------------------------------------------------
int *Rules_ClearAtomInUseMarks()
{
  _DWORD *v0; // edx
  _DWORD *v1; // ecx
  _DWORD *v2; // eax
  _DWORD *v3; // edx
  _DWORD *v4; // ecx
  _DWORD *v5; // eax
  _DWORD *v6; // edx
  _DWORD *v7; // ecx
  _DWORD *v8; // eax
  int *v9; // edx
  int *v10; // ecx
  int *result; // eax

  v0 = (_DWORD *)Rules_GetSymbolTable();
  v1 = v0 + 1013;
  do
  {
    v2 = (_DWORD *)*v0;
    if ( *v0 )
    {
      do
      {
        v2[3] &= ~2u;
        v2 = (_DWORD *)*v2;
      }
      while ( v2 );
    }
    ++v0;
  }
  while ( v0 != v1 );
  v3 = (_DWORD *)Rules_GetFloatTable();
  v4 = v3 + 503;
  do
  {
    v5 = (_DWORD *)*v3;
    if ( *v3 )
    {
      do
      {
        v5[3] &= ~2u;
        v5 = (_DWORD *)*v5;
      }
      while ( v5 );
    }
    ++v3;
  }
  while ( v3 != v4 );
  v6 = (_DWORD *)Rules_GetIntegerTable();
  v7 = v6 + 167;
  do
  {
    v8 = (_DWORD *)*v6;
    if ( *v6 )
    {
      do
      {
        v8[3] &= ~2u;
        v8 = (_DWORD *)*v8;
      }
      while ( v8 );
    }
    ++v6;
  }
  while ( v6 != v7 );
  v9 = (int *)Rules_GetBitmapTable();
  v10 = v9 + 167;
  do
  {
    result = (int *)*v9;
    if ( *v9 )
    {
      do
      {
        result[3] &= ~2u;
        result = (int *)*result;
      }
      while ( result );
    }
    ++v9;
  }
  while ( v9 != v10 );
  return result;
}

//----- (00494AB0) --------------------------------------------------------
const void * Rules_BsaveSymbolTable(int a1)
{
  int ***v2; // ebx
  int **i; // edx
  const void *result; // eax
  int **j; // esi
  int v6; // [esp+0h] [ebp-2Ch] BYREF
  int v7; // [esp+4h] [ebp-28h] BYREF
  int v8; // [esp+8h] [ebp-24h]
  int ***v9; // [esp+Ch] [ebp-20h]
  int ***v10; // [esp+10h] [ebp-1Ch]

  v6 = 0;
  v7 = 0;
  v8 = Rules_GetSymbolTable();
  v2 = (int ***)v8;
  do
  {
    for ( i = *v2; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
      {
        ++v6;
        v7 += strlen((const char *)i[4]) + 1;
      }
    }
    ++v2;
  }
  while ( v2 != (int ***)(v8 + 4052) );
  Rules_BsaveWriteBlock(4, a1, &v6);
  Rules_BsaveWriteBlock(4, a1, &v7);
  v10 = (int ***)v8;
  result = (const void *)(v8 + 4052);
  v9 = (int ***)(v8 + 4052);
  do
  {
    for ( j = *v10; j; j = (int **)*j )
    {
      if ( ((_BYTE)j[3] & 2) != 0 )
        result = Rules_BsaveWriteBlock(strlen((const char *)j[4]) + 1, a1, j[4]);
    }
    ++v10;
  }
  while ( v10 != v9 );
  return result;
}

//----- (00494BA0) --------------------------------------------------------
const void * Rules_BsaveFloatTable(int a1)
{
  int v2; // ebp
  int ***v3; // edi
  int **i; // eax
  const void *result; // eax
  int **v6; // edi
  int **v7; // ebp
  int **v8; // ecx
  _DWORD v9[7]; // [esp+0h] [ebp-1Ch] BYREF

  v9[0] = 0;
  v2 = Rules_GetFloatTable();
  v3 = (int ***)v2;
  do
  {
    for ( i = *v3; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
        ++v9[0];
    }
    ++v3;
  }
  while ( v3 != (int ***)(v2 + 2012) );
  result = Rules_BsaveWriteBlock(4, a1, v9);
  v6 = (int **)v2;
  v7 = (int **)(v2 + 2012);
  do
  {
    v8 = (int **)*v6;
    if ( *v6 )
    {
      do
      {
        if ( ((_BYTE)v8[3] & 2) != 0 )
          result = Rules_BsaveWriteBlock(8, a1, v8 + 4);
        v8 = (int **)*v8;
      }
      while ( v8 );
    }
    ++v6;
  }
  while ( v6 != v7 );
  return result;
}
// 494C1B: variable 'v8' is possibly undefined

//----- (00494C40) --------------------------------------------------------
const void * Rules_BsaveIntegerTable(int a1)
{
  int v2; // ebp
  int ***v3; // edi
  int **i; // eax
  const void *result; // eax
  int **v6; // edi
  int **v7; // ebp
  int **v8; // ecx
  _DWORD v9[7]; // [esp+0h] [ebp-1Ch] BYREF

  v9[0] = 0;
  v2 = Rules_GetIntegerTable();
  v3 = (int ***)v2;
  do
  {
    for ( i = *v3; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
        ++v9[0];
    }
    ++v3;
  }
  while ( v3 != (int ***)(v2 + 668) );
  result = Rules_BsaveWriteBlock(4, a1, v9);
  v6 = (int **)v2;
  v7 = (int **)(v2 + 668);
  do
  {
    v8 = (int **)*v6;
    if ( *v6 )
    {
      do
      {
        if ( ((_BYTE)v8[3] & 2) != 0 )
          result = Rules_BsaveWriteBlock(4, a1, v8 + 4);
        v8 = (int **)*v8;
      }
      while ( v8 );
    }
    ++v6;
  }
  while ( v6 != v7 );
  return result;
}
// 494CBB: variable 'v8' is possibly undefined

//----- (00494CE0) --------------------------------------------------------
const void * Rules_BsaveBitmapTable(int a1)
{
  int v2; // ebp
  int ***v3; // ebx
  int **i; // eax
  int **v5; // edi
  const void *result; // eax
  int **v7; // ebp
  int *j; // ecx
  int v9; // ecx
  int v10; // [esp+0h] [ebp-24h] BYREF
  int v11; // [esp+4h] [ebp-20h] BYREF
  _BYTE v12[28]; // [esp+8h] [ebp-1Ch] BYREF

  v10 = 0;
  v11 = 0;
  v2 = Rules_GetBitmapTable();
  v3 = (int ***)v2;
  do
  {
    for ( i = *v3; i; i = (int **)*i )
    {
      if ( ((_BYTE)i[3] & 2) != 0 )
      {
        ++v10;
        v11 += *((unsigned __int16 *)i + 10) + 1;
      }
    }
    ++v3;
  }
  while ( v3 != (int ***)(v2 + 668) );
  Rules_BsaveWriteBlock(4, a1, &v10);
  v5 = (int **)v2;
  result = Rules_BsaveWriteBlock(4, a1, &v11);
  v7 = (int **)(v2 + 668);
  do
  {
    for ( j = *v5; j; j = (int *)*j )
    {
      if ( (j[3] & 2) != 0 )
      {
        v12[0] = *((_BYTE *)j + 20);
        Rules_BsaveWriteBlock(1, a1, v12);
        result = Rules_BsaveWriteBlock(*(unsigned __int16 *)(v9 + 20), a1, *(const void **)(v9 + 16));
      }
    }
    ++v5;
  }
  while ( v5 != v7 );
  return result;
}
// 494D8A: variable 'v9' is possibly undefined
// 494D93: variable 'j' is possibly undefined

//----- (00494DB0) --------------------------------------------------------
int Rules_BloadAtomTables()
{
  int result; // eax
  int buffer; // edi
  int table; // eax
  unsigned __int8 *entry; // ecx
  int i; // esi
  int byte_count; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadSymbolTable();
  Rules_BloadFloatTable();
  Rules_BloadIntegerTable();
  Rules_BloadReadBlock((uintptr_t)&dword_51AA38, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&byte_count, 4u);
  if ( dword_51AA38 )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(byte_count);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, byte_count);
    table = (int)(uintptr_t)Mem_NewArray(4 * dword_51AA38);
    dword_54E67C = table;
    entry = (unsigned __int8 *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < dword_51AA38; ++i )
    {
      *(_DWORD *)(dword_54E67C + 4 * i) = Rules_AddBitmapValue(entry + 1, *entry);
      entry += *entry + 1;
    }
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, byte_count);
  }
  else
  {
    dword_54E67C = 0;
  }
  return result;
}
// 51AA38: using guessed type int dword_51AA38;
// 54E67C: using guessed type int dword_54E67C;

//----- (00494E00) --------------------------------------------------------
int Rules_BloadSymbolTable()
{
  int result; // eax
  int buffer; // ebp
  int table; // eax
  char *symbol_name; // edx
  int i; // ebx
  int byte_count; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&dword_51AA2C, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&byte_count, 4u);
  if ( dword_51AA2C )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(byte_count);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, byte_count);
    table = (int)(uintptr_t)Mem_NewArray(4 * dword_51AA2C);
    dword_54E674 = table;
    symbol_name = (char *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < dword_51AA2C; ++i )
    {
      *(_DWORD *)(dword_54E674 + 4 * i) = (int)(uintptr_t)Str_Intern(symbol_name, 0);
      symbol_name += strlen(symbol_name) + 1;
    }
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, byte_count);
  }
  else
  {
    dword_54E674 = 0;
  }
  return result;
}
// 51AA2C: using guessed type int dword_51AA2C;
// 54E674: using guessed type int dword_54E674;

//----- (00494ED0) --------------------------------------------------------
int Rules_BloadFloatTable()
{
  int result; // eax
  int buffer; // esi
  double *numbers; // edx
  int i; // ecx

  result = Rules_BloadReadBlock((uintptr_t)&dword_51AA30, 4u);
  if ( dword_51AA30 )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(8 * dword_51AA30);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, 8 * dword_51AA30);
    dword_54E670 = (int)(uintptr_t)Mem_NewArray(4 * dword_51AA30);
    numbers = (double *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < dword_51AA30; ++i )
      *(_DWORD *)(dword_54E670 + 4 * i) = Rules_AddDoubleValue(numbers[i]);
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, 8 * dword_51AA30);
  }
  else
  {
    dword_54E670 = 0;
  }
  return result;
}
// 51AA30: using guessed type int dword_51AA30;
// 54E670: using guessed type int dword_54E670;

//----- (00494F90) --------------------------------------------------------
int Rules_BloadIntegerTable()
{
  int result; // eax
  int buffer; // edi
  int *integers; // ecx
  int i; // edx

  result = Rules_BloadReadBlock((uintptr_t)&dword_51AA34, 4u);
  if ( dword_51AA34 )
  {
    buffer = (int)(uintptr_t)Mem_NewArray(4 * dword_51AA34);
    Rules_BloadReadBlock((uintptr_t)(unsigned int)buffer, 4 * dword_51AA34);
    dword_54E678 = (int)(uintptr_t)Mem_NewArray(4 * dword_51AA34);
    integers = (int *)(uintptr_t)(unsigned int)buffer;
    for ( i = 0; i < dword_51AA34; ++i )
      *(_DWORD *)(dword_54E678 + 4 * i) = Rules_AddIntegerValue(integers[i]);
    return Mem_SmallBlockRelease((_DWORD *)(uintptr_t)(unsigned int)buffer, 4 * dword_51AA34);
  }
  else
  {
    dword_54E678 = 0;
  }
  return result;
}
// 51AA34: using guessed type int dword_51AA34;
// 54E678: using guessed type int dword_54E678;

//----- (004950D0) --------------------------------------------------------
signed int Rules_FreeBloadAtomTables()
{
  signed int result; // eax

  if ( dword_54E674 )
    result = Mem_SmallBlockRelease((_DWORD *)dword_54E674, 4 * dword_51AA2C);
  if ( dword_54E670 )
    result = Mem_SmallBlockRelease((_DWORD *)dword_54E670, 4 * dword_51AA30);
  if ( dword_54E678 )
    result = Mem_SmallBlockRelease((_DWORD *)dword_54E678, 4 * dword_51AA34);
  if ( dword_54E67C )
    return Mem_SmallBlockRelease((_DWORD *)dword_54E67C, 4 * dword_51AA38);
  return result;
}
// 51AA2C: using guessed type int dword_51AA2C;
// 51AA30: using guessed type int dword_51AA30;
// 51AA34: using guessed type int dword_51AA34;
// 51AA38: using guessed type int dword_51AA38;
// 54E670: using guessed type int dword_54E670;
// 54E674: using guessed type int dword_54E674;
// 54E678: using guessed type int dword_54E678;
// 54E67C: using guessed type int dword_54E67C;

//----- (00495160) --------------------------------------------------------
int Rules_BloadAllocExpressionArray()
{
  int result; // eax

  result = Rules_BloadReadBlock((uintptr_t)&dword_54E684, 4u);
  if ( dword_54E684 )
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)(14 * dword_54E684));
    dword_54E688 = result;
  }
  else
  {
    dword_54E688 = 0;
  }
  return result;
}
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004951A0) --------------------------------------------------------
void Rules_BloadRefreshExpressions()
{
  if ( dword_54E688 )
    Rules_BloadAndRefresh(dword_54E684, 14, (void (__fastcall *)(signed int, signed int))Rules_RefreshExpressionEntry);
}
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004951D0) --------------------------------------------------------
int  Rules_RefreshExpressionEntry(__int16 *a1, int a2)
{
  int v4; // ebx
  unsigned __int16 v5; // ax
  int v6; // ebx
  int v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // edi
  int v11; // ecx
  int v12; // ebx
  int result; // eax
  int v14; // ebx
  int v15; // ebx
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int v20; // ebx

  v4 = 14 * a2;
  v5 = *a1;
  *(_WORD *)(dword_54E688 + 14 * a2) = *a1;
  if ( v5 < 8u )
  {
    if ( v5 < 3u )
    {
      if ( !v5 )
      {
        v6 = dword_54E670;
        v7 = 4 * *(_DWORD *)(a1 + 1);
LABEL_5:
        *(_DWORD *)(dword_54E688 + 14 * a2 + 2) = *(_DWORD *)(v7 + v6);
        v8 = 14 * a2;
LABEL_6:
        ++*(_DWORD *)(*(_DWORD *)(v8 + dword_54E688 + 2) + 4);
        goto LABEL_7;
      }
      if ( v5 <= 1u )
      {
        v7 = dword_54E678;
        v6 = 4 * *(_DWORD *)(a1 + 1);
        goto LABEL_5;
      }
LABEL_12:
      v8 = 14 * a2;
      *(_DWORD *)(dword_54E688 + 14 * a2 + 2) = *(_DWORD *)(dword_54E674 + 4 * *(_DWORD *)(a1 + 1));
      goto LABEL_6;
    }
    if ( v5 <= 3u )
      goto LABEL_12;
    if ( v5 >= 6u )
    {
      if ( v5 > 6u )
      {
        *(_DWORD *)(v4 + dword_54E688 + 2) = &g_Instance_DummyInstanceRecord;
        Rules_IncrementRefCountField40(*(_DWORD *)(v4 + dword_54E688 + 2));
      }
      else
      {
        *(_DWORD *)(v4 + dword_54E688 + 2) = &g_Rules_DummyFactPtr;
        Rules_IncrementFactRefCount(*(_DWORD *)(v4 + dword_54E688 + 2));
      }
      goto LABEL_7;
    }
    if ( v5 == 5 )
    {
      *(_DWORD *)(14 * a2 + dword_54E688 + 2) = 0;
      goto LABEL_7;
    }
LABEL_26:
    v16 = dword_54E530[*a1];
    if ( !v16 || (*(_BYTE *)(v16 + 1) & 0x40) == 0 )
      goto LABEL_7;
    v8 = 14 * a2;
    *(_DWORD *)(14 * a2 + dword_54E688 + 2) = *(_DWORD *)(dword_54E67C + 4 * *(_DWORD *)(a1 + 1));
    goto LABEL_6;
  }
  if ( v5 <= 8u )
    goto LABEL_12;
  if ( v5 >= 0xDu )
  {
    if ( v5 <= 0xDu )
      goto LABEL_12;
    if ( v5 < 0x39u )
    {
      if ( v5 == 35 )
      {
        *(_DWORD *)(v4 + dword_54E688 + 2) = dword_54E840 + 36 * *(_DWORD *)(a1 + 1);
        goto LABEL_7;
      }
      goto LABEL_26;
    }
    if ( v5 > 0x39u )
    {
      if ( v5 < 0x3Cu )
        goto LABEL_26;
      if ( v5 <= 0x3Cu )
      {
        *(_DWORD *)(v4 + dword_54E688 + 2) = dword_51B370 + 56 * *(_DWORD *)(a1 + 1);
        goto LABEL_7;
      }
      if ( v5 != 105 )
        goto LABEL_26;
    }
    else
    {
      v14 = *(_DWORD *)(a1 + 1);
      if ( v14 == -1 )
        v15 = 0;
      else
        v15 = 124 * v14 + dword_51B3AC;
      *(_DWORD *)(14 * a2 + dword_54E688 + 2) = v15;
    }
  }
  else
  {
    if ( v5 < 0xBu )
    {
      if ( v5 == 10 )
      {
        *(_DWORD *)(dword_54E688 + v4 + 2) = *(_DWORD *)(4 * *(_DWORD *)(a1 + 1) + dword_54DD24);
        goto LABEL_7;
      }
      goto LABEL_26;
    }
    if ( v5 > 0xBu )
    {
      v19 = *(_DWORD *)(a1 + 1);
      if ( v19 == -1 )
        v20 = 0;
      else
        v20 = 46 * v19 + dword_51B3A0;
      *(_DWORD *)(14 * a2 + dword_54E688 + 2) = v20;
    }
    else
    {
      v17 = *(_DWORD *)(a1 + 1);
      if ( v17 == -1 )
        v18 = 0;
      else
        v18 = 40 * v17 + dword_51B378;
      *(_DWORD *)(dword_54E688 + 14 * a2 + 2) = v18;
    }
  }
LABEL_7:
  v9 = *(_DWORD *)(a1 + 5);
  v10 = 14 * a2;
  if ( v9 == -1 )
    *(_DWORD *)(v10 + dword_54E688 + 10) = 0;
  else
    *(_DWORD *)(v10 + dword_54E688 + 10) = dword_54E688 + 14 * v9;
  v11 = *(_DWORD *)(a1 + 3);
  v12 = 14 * a2;
  result = dword_54E688;
  if ( v11 == -1 )
    *(_DWORD *)(v12 + dword_54E688 + 6) = 0;
  else
    *(_DWORD *)(v12 + dword_54E688 + 6) = dword_54E688 + 14 * v11;
  return result;
}
// 49526E: variable 'a2' is possibly undefined
// 51A114: using guessed type void *off_51A114;
// 51A214: using guessed type void *off_51A214;
// 51B370: using guessed type int dword_51B370;
// 51B378: using guessed type int dword_51B378;
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3AC: using guessed type int dword_51B3AC;
// 54DD24: using guessed type int dword_54DD24;
// 54E530: using guessed type int dword_54E530[70];
// 54E670: using guessed type int dword_54E670;
// 54E674: using guessed type int dword_54E674;
// 54E678: using guessed type int dword_54E678;
// 54E67C: using guessed type int dword_54E67C;
// 54E688: using guessed type int dword_54E688;
// 54E840: using guessed type int dword_54E840;

//----- (00495590) --------------------------------------------------------
signed int Rules_FreeBloadedExpressions()
{
  unsigned int v0; // ebx
  int v1; // ecx
  int v2; // edx
  unsigned __int16 v3; // ax
  signed int result; // eax
  int v5; // edi

  v0 = 0;
  if ( dword_54E684 )
  {
    v1 = 0;
    do
    {
      v2 = v1 + dword_54E688;
      v3 = *(_WORD *)(v1 + dword_54E688);
      if ( v3 >= 6u )
      {
        if ( v3 <= 6u )
        {
          Rules_DecrementFactRefCount(*(_DWORD *)(v2 + 2));
          goto LABEL_6;
        }
        if ( v3 < 8u )
        {
          Instance_DecrementBusyCount(*(_DWORD *)(v2 + 2));
          goto LABEL_6;
        }
        if ( v3 <= 8u )
          goto LABEL_21;
        if ( v3 < 0xDu )
          goto LABEL_13;
        if ( v3 <= 0xDu )
          goto LABEL_21;
        if ( v3 != 105 )
          goto LABEL_13;
      }
      else
      {
        if ( v3 )
        {
          if ( v3 <= 1u )
          {
            Rules_DecrementIntegerCount(*(_DWORD *)(v2 + 2), v1);
            goto LABEL_6;
          }
          if ( v3 >= 4u )
          {
LABEL_13:
            v5 = dword_54E530[*(__int16 *)(v1 + dword_54E688)];
            if ( v5 && (*(_BYTE *)(v5 + 1) & 0x40) != 0 )
              Rules_DecrementBitmapCount(*(_DWORD *)(v1 + dword_54E688 + 2), v1);
            goto LABEL_6;
          }
LABEL_21:
          Rules_DecrementSymbolCount(*(_DWORD *)(v1 + dword_54E688 + 2), v1);
          goto LABEL_6;
        }
        Rules_DecrementFloatCount(*(_DWORD *)(v2 + 2), v1);
      }
LABEL_6:
      ++v0;
      v1 += 14;
    }
    while ( v0 < dword_54E684 );
  }
  result = 14 * dword_54E684;
  if ( 14 * dword_54E684 )
    return Mem_ReleasePoolBlock(dword_54E688, 14 * dword_54E684);
  return result;
}
// 49564B: simplified comparisons for 'ax.2': >=3u && !=3 became >=4u
// 4955D2: variable 'v1' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];
// 54E684: using guessed type int dword_54E684;
// 54E688: using guessed type int dword_54E688;

//----- (004956B0) --------------------------------------------------------
int Rules_CountHashedExpressions()
{
  int i; // ecx
  int result; // eax
  int j; // edx
  int v3; // edx
  int v4; // edx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = dword_51A9FC;
    for ( j = *(_DWORD *)(i + dword_51A9FC); j; j = *(_DWORD *)(v4 + 12) )
    {
      Rules_MarkReferencedFunctions(*(__int16 **)(j + 8));
      *(_DWORD *)(v3 + 16) = dword_54E680;
      result = AST_CountTreeNodes(*(_DWORD *)(v3 + 8));
      dword_54E680 += result;
    }
  }
  return result;
}
// 4956D9: variable 'v3' is possibly undefined
// 4956EA: variable 'v4' is possibly undefined
// 4956F1: variable 'i' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54E680: using guessed type int dword_54E680;

//----- (00495700) --------------------------------------------------------
__int16 * Rules_AssignHashedExpressionIndices(int a1)
{
  int i; // esi
  __int16 *result; // eax
  int j; // ecx
  int v5; // ecx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = (__int16 *)dword_51A9FC;
    for ( j = *(_DWORD *)(i + dword_51A9FC); j; j = *(_DWORD *)(v5 + 12) )
      result = Rules_BsaveWriteExpression(*(__int16 **)(j + 8), a1);
  }
  return result;
}
// 495726: variable 'v5' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;

//----- (00495740) --------------------------------------------------------
int Rules_InvokeConstructCallbacks()
{
  int i; // edx
  int result; // eax
  int v2; // edx

  for ( i = dword_51AA3C; i; i = *(_DWORD *)(v2 + 36) )
  {
    while ( !*(_DWORD *)(i + 20) )
    {
      i = *(_DWORD *)(i + 36);
      if ( !i )
        return result;
    }
    result = (*(int (**)(void))(i + 20))();
  }
  return result;
}
// 495763: variable 'v2' is possibly undefined
// 51AA3C: using guessed type int dword_51AA3C;

//----- (00495770) --------------------------------------------------------
__int16 * Rules_BsaveWriteExpression(__int16 *result, int a2)
{
  __int16 *i; // ecx
  int v4; // edx
  unsigned __int16 v5; // ax
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // ebp
  int v11; // edi
  int v12; // edx
  int v13; // ebp
  unsigned __int16 v14; // [esp+0h] [ebp-24h] BYREF
  int v15; // [esp+2h] [ebp-22h]
  int v16; // [esp+6h] [ebp-1Eh]
  int v17; // [esp+Ah] [ebp-1Ah]

  for ( i = result; i; i = *(__int16 **)(v7 + 10) )
  {
    v4 = ++dword_54E680;
    v14 = *i;
    if ( *(_DWORD *)(i + 3) )
      v16 = v4;
    else
      v16 = -1;
    if ( *(_DWORD *)(i + 5) )
      v17 = dword_54E680 + AST_CountTreeNodes(*(_DWORD *)(i + 3));
    else
      v17 = -1;
    v5 = *i;
    if ( (unsigned __int16)*i >= 8u )
    {
      if ( (unsigned __int16)*i <= 8u )
        goto LABEL_8;
      if ( v5 >= 0xDu )
      {
        if ( v5 <= 0xDu )
          goto LABEL_8;
        if ( v5 >= 0x39u )
        {
          if ( v5 <= 0x39u )
          {
            v9 = *(_DWORD *)(i + 1);
            if ( !v9 )
              goto LABEL_42;
            v6 = *(_DWORD *)(v9 + 12);
            goto LABEL_9;
          }
          if ( v5 >= 0x3Cu )
          {
            if ( v5 <= 0x3Cu )
            {
              v11 = *(_DWORD *)(i + 1);
              if ( !v11 )
                goto LABEL_42;
              v6 = *(_DWORD *)(v11 + 12);
              goto LABEL_9;
            }
            if ( v5 == 105 )
              goto LABEL_10;
          }
        }
        else if ( v5 == 35 )
        {
          v8 = *(_DWORD *)(i + 1);
          if ( !v8 )
            goto LABEL_42;
          v6 = *(_DWORD *)(v8 + 12);
          goto LABEL_9;
        }
      }
      else
      {
        if ( v5 >= 0xBu )
        {
          if ( v5 > 0xBu )
          {
            v13 = *(_DWORD *)(i + 1);
            if ( !v13 )
            {
LABEL_42:
              v15 = -1;
              goto LABEL_10;
            }
            v6 = *(_DWORD *)(v13 + 12);
          }
          else
          {
            v12 = *(_DWORD *)(i + 1);
            if ( !v12 )
              goto LABEL_42;
            v6 = *(_DWORD *)(v12 + 12);
          }
          goto LABEL_9;
        }
        if ( v5 == 10 )
        {
          v6 = *(__int16 *)(*(_DWORD *)(i + 1) + 25);
          goto LABEL_9;
        }
      }
    }
    else
    {
      if ( v5 < 4u )
        goto LABEL_8;
      if ( v5 > 4u )
        goto LABEL_42;
    }
    v10 = dword_54E530[*i];
    if ( v10 && (*(_BYTE *)(v10 + 1) & 0x40) != 0 )
    {
LABEL_8:
      v6 = *(_DWORD *)(*(_DWORD *)(i + 1) + 12) << 16 >> 18;
LABEL_9:
      v15 = v6;
    }
LABEL_10:
    Rules_BsaveWriteBlock(14, a2, &v14);
    result = *(__int16 **)(v7 + 6);
    if ( result )
      result = (__int16 *)Rules_BsaveWriteExpression((int)result, a2);
  }
  return result;
}
// 495904: simplified comparisons for 'ax.2': <6u && !=5 became <5u
// 4957C9: simplified comparisons for 'ax.2': >=3u && >=4u became >=4u
// 4957B8: variable 'i' is possibly undefined
// 4957FC: variable 'v7' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];
// 54E680: using guessed type int dword_54E680;

//----- (00495930) --------------------------------------------------------
const void * Rules_BsaveWriteConstraints(int a1)
{
  int v2; // edx
  int v3; // eax
  int i; // ecx
  int v5; // ecx
  int v6; // ecx
  const void *result; // eax
  int j; // edi
  int *k; // ecx
  int v10; // ecx
  _BYTE v11[24]; // [esp+0h] [ebp-34h] BYREF
  _DWORD v12[7]; // [esp+18h] [ebp-1Ch] BYREF

  v2 = 0;
  v3 = 0;
  v12[0] = 0;
  do
  {
    for ( i = *(_DWORD *)(dword_54E694 + v2); i; ++v3 )
    {
      *(_WORD *)(i + 4) = v3;
      ++v12[0];
      i = *(_DWORD *)(i + 30);
    }
    v2 += 4;
  }
  while ( v2 != 668 );
  if ( !Rules_DynamicConstraintCheckingEnabled() && v12[0] )
  {
    v12[0] = 0;
    Rules_PrintWarningID((int)aCstrnbin, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aConstraintsAre, v5);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aWhenDynamicCon, v6);
  }
  result = Rules_BsaveWriteBlock(4, a1, v12);
  if ( v12[0] )
  {
    for ( j = 0; j != 668; j += 4 )
    {
      result = (const void *)dword_54E694;
      for ( k = *(int **)(j + dword_54E694); k; k = *(int **)(v10 + 30) )
      {
        Rules_PackConstraintRecord(k, (int)v11);
        result = Rules_BsaveWriteBlock(24, a1, v11);
      }
    }
  }
  return result;
}
// 4959A7: variable 'v5' is possibly undefined
// 4959B6: variable 'v6' is possibly undefined
// 495A00: variable 'v10' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];
// 54E694: using guessed type int dword_54E694;

//----- (00495A20) --------------------------------------------------------
signed int  Rules_PackConstraintRecord(int *a1, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  unsigned int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  signed int result; // eax

  v3 = *a1;
  *(_BYTE *)a2 &= ~1u;
  *(_DWORD *)a2 |= v3 & 1;
  v4 = *a1;
  *(_BYTE *)a2 &= ~2u;
  *(_DWORD *)a2 |= v4 & 2;
  v5 = *a1;
  *(_BYTE *)a2 &= ~4u;
  *(_DWORD *)a2 |= v5 & 4;
  v6 = *a1;
  *(_BYTE *)a2 &= ~8u;
  *(_DWORD *)a2 |= v6 & 8;
  v7 = *a1;
  *(_BYTE *)a2 &= ~0x10u;
  *(_DWORD *)a2 |= v7 & 0x10;
  v8 = *a1;
  *(_BYTE *)a2 &= ~0x20u;
  *(_DWORD *)a2 |= v8 & 0x20;
  v9 = *a1;
  *(_BYTE *)a2 &= ~0x40u;
  *(_DWORD *)a2 |= v9 & 0x40;
  v10 = *a1;
  *(_BYTE *)a2 &= ~0x80u;
  *(_DWORD *)a2 |= v10 & 0x80;
  v11 = (unsigned int)(*a1 << 16) >> 31;
  *(_BYTE *)(a2 + 2) &= ~1u;
  *(_DWORD *)a2 |= (v11 & 1) << 16;
  v12 = (unsigned int)(*a1 << 15) >> 31;
  *(_BYTE *)(a2 + 2) &= ~2u;
  *(_DWORD *)a2 |= (v12 & 1) << 17;
  v13 = *a1;
  *(_BYTE *)(a2 + 1) &= ~1u;
  *(_DWORD *)a2 |= v13 & 0x100;
  v14 = *a1;
  *(_BYTE *)(a2 + 1) &= ~2u;
  *(_DWORD *)a2 |= v14 & 0x200;
  v15 = *a1;
  *(_BYTE *)(a2 + 1) &= ~4u;
  *(_DWORD *)a2 |= v15 & 0x400;
  v16 = *a1;
  *(_BYTE *)(a2 + 1) &= ~8u;
  *(_DWORD *)a2 |= v16 & 0x800;
  v17 = (unsigned int)(*a1 << 19) >> 31;
  *(_BYTE *)(a2 + 1) &= ~0x20u;
  *(_DWORD *)a2 |= (v17 & 1) << 13;
  v18 = (unsigned int)(*a1 << 18) >> 31;
  *(_BYTE *)(a2 + 1) &= ~0x40u;
  *(_DWORD *)a2 |= (v18 & 1) << 14;
  v19 = (unsigned int)(*a1 << 17) >> 31;
  *(_BYTE *)(a2 + 1) &= ~0x80u;
  *(_DWORD *)a2 |= (v19 & 1) << 15;
  *(_DWORD *)(a2 + 4) = AST_GetHashedNodeIndex(*(__int16 **)((char *)a1 + 6));
  *(_DWORD *)(a2 + 8) = AST_GetHashedNodeIndex(*(__int16 **)(v20 + 10));
  *(_DWORD *)(a2 + 12) = AST_GetHashedNodeIndex(*(__int16 **)(v21 + 14));
  *(_DWORD *)(a2 + 16) = AST_GetHashedNodeIndex(*(__int16 **)(v22 + 18));
  result = AST_GetHashedNodeIndex(*(__int16 **)(v23 + 22));
  *(_DWORD *)(a2 + 20) = result;
  return result;
}
// 495B7D: variable 'v20' is possibly undefined
// 495B88: variable 'v21' is possibly undefined
// 495B93: variable 'v22' is possibly undefined
// 495B9E: variable 'v23' is possibly undefined

//----- (00495BB0) --------------------------------------------------------
int Rules_BloadConstraints()
{
  int result; // eax

  result = Rules_BloadReadBlock((uintptr_t)&dword_54E690, 4u);
  if ( dword_54E690 )
  {
    dword_54E68C = Mem_HeapAllocWithRetry((_DWORD *)(42 * dword_54E690));
    return Rules_BloadAndRefresh(dword_54E690, 24, (void (__fastcall *)(signed int, signed int))Rules_UpdateBloadedConstraint);
  }
  return result;
}
// 54E68C: using guessed type int dword_54E68C;
// 54E690: using guessed type int dword_54E690;

//----- (00495C00) --------------------------------------------------------
int  Rules_UpdateBloadedConstraint(_DWORD *a1, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  int v8; // ebx
  int v9; // ebx
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v18; // ebx
  int v19; // ebx
  int v20; // ebx
  int v21; // ebp
  _DWORD *v22; // edx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ebx
  int v27; // ecx
  int v28; // esi
  int v29; // ecx
  int v30; // edi
  int v31; // edx

  result = dword_54E68C + 42 * a2;
  v4 = *a1;
  *(_BYTE *)result &= ~1u;
  *(_DWORD *)result |= v4 & 1;
  v5 = *a1;
  *(_BYTE *)result &= ~2u;
  *(_DWORD *)result |= v5 & 2;
  v6 = *a1;
  *(_BYTE *)result &= ~4u;
  *(_DWORD *)result |= v6 & 4;
  v7 = *a1;
  *(_BYTE *)result &= ~8u;
  *(_DWORD *)result |= v7 & 8;
  v8 = *a1;
  *(_BYTE *)result &= ~0x10u;
  *(_DWORD *)result |= v8 & 0x10;
  v9 = *a1;
  *(_BYTE *)result &= ~0x20u;
  *(_DWORD *)result |= v9 & 0x20;
  v10 = *a1;
  *(_BYTE *)result &= ~0x40u;
  *(_DWORD *)result |= v10 & 0x40;
  v11 = *a1;
  *(_BYTE *)result &= ~0x80u;
  *(_DWORD *)result |= v11 & 0x80;
  v12 = *a1 << 15 >> 31;
  *(_BYTE *)(result + 1) &= ~0x80u;
  *(_DWORD *)result |= (v12 & 1) << 15;
  v13 = *a1 << 14 >> 31;
  *(_BYTE *)(result + 2) &= ~1u;
  *(_DWORD *)result |= (v13 & 1) << 16;
  v14 = *a1;
  *(_BYTE *)(result + 1) &= ~1u;
  *(_DWORD *)result |= v14 & 0x100;
  v15 = *a1;
  *(_BYTE *)(result + 1) &= ~2u;
  *(_DWORD *)result |= v15 & 0x200;
  v16 = *a1;
  *(_BYTE *)(result + 1) &= ~4u;
  *(_DWORD *)result |= v16 & 0x400;
  v17 = *a1;
  *(_BYTE *)(result + 1) &= ~8u;
  *(_DWORD *)result |= v17 & 0x800;
  v18 = *a1 << 18 >> 31;
  *(_BYTE *)(result + 1) &= ~0x10u;
  *(_DWORD *)result |= (v18 & 1) << 12;
  v19 = *a1 << 17 >> 31;
  *(_BYTE *)(result + 1) &= ~0x20u;
  *(_DWORD *)result |= (v19 & 1) << 13;
  v20 = *a1 << 16 >> 31;
  *(_BYTE *)(result + 1) &= ~0x40u;
  *(_DWORD *)result |= (v20 & 1) << 14;
  v21 = a1[1];
  v22 = a1;
  if ( v21 == -1 )
    v23 = 0;
  else
    v23 = dword_54E688 + 14 * v21;
  *(_DWORD *)(result + 6) = v23;
  v24 = v22[2];
  if ( v24 == -1 )
    v25 = 0;
  else
    v25 = dword_54E688 + 14 * v24;
  *(_DWORD *)(result + 10) = v25;
  v26 = v22[3];
  if ( v26 == -1 )
    v27 = 0;
  else
    v27 = dword_54E688 + 14 * v26;
  *(_DWORD *)(result + 14) = v27;
  v28 = v22[4];
  if ( v28 == -1 )
    v29 = 0;
  else
    v29 = dword_54E688 + 14 * v28;
  *(_DWORD *)(result + 18) = v29;
  v30 = v22[5];
  if ( v30 == -1 )
  {
    *(_DWORD *)(result + 26) = 0;
    *(_DWORD *)(result + 22) = 0;
  }
  else
  {
    v31 = 14 * v30 + dword_54E688;
    *(_DWORD *)(result + 26) = 0;
    *(_DWORD *)(result + 22) = v31;
  }
  return result;
}
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;

//----- (00495E00) --------------------------------------------------------
signed int Rules_ClearBloadedConstraints()
{
  signed int result; // eax

  if ( dword_54E690 )
  {
    result = Mem_ReleasePoolBlock(dword_54E68C, 42 * dword_54E690);
    dword_54E690 = 0;
  }
  return result;
}
// 54E68C: using guessed type int dword_54E68C;
// 54E690: using guessed type int dword_54E690;

//----- (00495E30) --------------------------------------------------------
BOOL  Rules_BsaveCommand(DWORD a1, double a2)
{
  int v2; // ecx
  BOOL result; // eax
  const CHAR *v4; // eax
  int v5; // ecx

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    v4 = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
    if ( v4 )
    {
      if ( Rules_PerformBsave(v4, a1, v5) )
        return 1;
    }
  }
  return result;
}
// 495E57: variable 'v2' is possibly undefined
// 495E60: variable 'v5' is possibly undefined

//----- (00495E80) --------------------------------------------------------
signed int  Rules_PerformBsave(const CHAR *a1, DWORD a2, int a3)
{
  int v4; // ecx
  int v5; // ebx
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int i; // esi
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int j; // esi
  int v16; // ecx
  int v17; // ecx
  int v19; // ecx
  _DWORD v20[9]; // [esp-20h] [ebp-24h] BYREF

  v20[7] = a3;
  if ( Rules_IsBloaded() )
  {
    Rules_PrintErrorID((int)aBsave_1, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotPerformA, v19);
    return 0;
  }
  else
  {
    v5 = IO_FOpen(a1, (unsigned __int8 *)aWb_3, v4, a2);
    if ( v5 )
    {
      Module_BeginEnum();
      Rules_BsaveWriteHeader(v5);
      dword_54E680 = v6;
      Event_ClearHandlers();
      Rules_ClearAtomInUseMarks();
      Rules_CountHashedExpressions();
      Event_InitHandlers();
      Rules_SetAtomicValueIndices(0);
      Rules_BsaveWriteFunctionNames(v5);
      Rules_BsaveAtomTables(v5);
      Rules_BsaveWriteBlock(v7, v5, &dword_54E680);
      for ( i = dword_51AA3C; i; i = *(_DWORD *)(i + 36) )
      {
        if ( *(_DWORD *)(i + 24) )
        {
          strncpy_(v8, *(_DWORD *)i);
          Rules_BsaveWriteBlock(20, v10, v20);
          (*(void (**)(void))(i + 24))();
        }
      }
      Rules_BsaveWriteEndTag(v8, v8);
      dword_54E680 = 0;
      Rules_AssignHashedExpressionIndices(v11);
      Rules_InvokeConstructCallbacks();
      dword_54E680 = v12;
      Rules_BsaveWriteConstraints(v13);
      for ( j = dword_51AA3C; j; j = *(_DWORD *)(j + 36) )
      {
        if ( *(_DWORD *)(j + 28) )
        {
          strncpy_(v14, *(_DWORD *)j);
          Rules_BsaveWriteBlock(20, v16, v20);
          (*(void (**)(void))(j + 28))();
        }
      }
      Rules_BsaveWriteEndTag(v14, v14);
      Rules_RestoreAtomicValueBuckets();
      fclose_(v17);
      Module_EndEnum();
      return 1;
    }
    else
    {
      Rules_OpenFileErrorMessage(0, (int)a1);
      return 0;
    }
  }
}
// 495E9D: variable 'v4' is possibly undefined
// 495EBC: variable 'v6' is possibly undefined
// 495EF5: variable 'v7' is possibly undefined
// 495F13: variable 'v8' is possibly undefined
// 495F21: variable 'v10' is possibly undefined
// 495F43: variable 'v11' is possibly undefined
// 495F57: variable 'v12' is possibly undefined
// 495F5D: variable 'v13' is possibly undefined
// 495F7B: variable 'v14' is possibly undefined
// 495F89: variable 'v16' is possibly undefined
// 495FA8: variable 'v17' is possibly undefined
// 495FDA: variable 'v19' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51AA3C: using guessed type int dword_51AA3C;
// 54E680: using guessed type int dword_54E680;

