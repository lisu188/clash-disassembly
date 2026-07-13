/* Recovered strings, memory, containers, paths, and shared utilities.
 * Original function-marker range: 0x004015A0..0x00401A00.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004015A0) --------------------------------------------------------
int  Str_ConstructHolderViaBaseCtor(_DWORD *a1)
{
  int v2; // ecx
  int result; // eax

  *a1 = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(a1);
  result = v2;
  *(_DWORD *)(v2 + 4) = &g_PathEntry_Vtable;
  return result;
}
// 4015B7: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004015D0) --------------------------------------------------------
_DWORD * Str_ConstructHolderInline(_DWORD *result)
{
  *result = 0;
  result[1] = &g_CompatStringHolder_Vtable;
  result[1] = &g_PathEntry_Vtable;
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00401600) --------------------------------------------------------
_BYTE * Mem_ZeroFourByteGlobal(_BYTE *result)
{
  *result = 0;
  result[1] = 0;
  result[2] = 0;
  result[3] = 0;
  return result;
}

//----- (00401610) --------------------------------------------------------
int __thiscall PathEntryArray_ConstructCapacity256(void *this)
{
  return _wcpp_4_ctor_array__(this, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401640) --------------------------------------------------------
int * PathEntryArray_CopyConstruct(int *a1, _DWORD *a2, int a3)
{
  int v4; // eax
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  _DWORD *v10; // ebx
  _DWORD *v11; // esi
  int v12; // ecx

  a1[4] = (int)g_PathEntryArray_Vtable;
  a1[1] = a2[1];
  a1[2] = a2[2];
  v4 = a2[3];
  a1[3] = v4;
  if ( !v4 )
  {
    *a1 = 0;
    return a1;
  }
  (void)a3;
  v6 = 0;
  v7 = Compat_WcppCtorArrayStorage1s(
         (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(16 * a1[3] + 4),
         a1[3],
         &g_PathEntryArray_ElementDtorDescriptor);
  v8 = a1[2];
  *a1 = v7;
  if ( v8 <= 0 )
    return a1;
  v9 = 0;
  do
  {
    v10 = (_DWORD *)(v9 + *a2);
    v11 = (_DWORD *)(v9 + *a1);
    *v11 = *v10;
    Compat_StringHolderDestructor(v11 + 1);
    v11[3] = v10[3];
    ++v6;
    v9 += 16;
  }
  while ( v6 < a1[2] );
  return a1;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 50ECA4: using guessed type int (*off_50ECA4[2])();

//----- (004016E0) --------------------------------------------------------
int  PathEntryArray_Destruct(_DWORD *a1, char a2)
{
  int v2; // ecx
  char v3; // dl
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_PathEntryArray_DtorDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    a1[4] = g_PathEntryArray_Vtable;
    PathEntryArray_DestructElements(a1);
    if ( (v3 & 2) != 0 )
      j__nfree_();
    return v2;
  }
}
// 4016F4: variable 'v3' is possibly undefined
// 4016F9: variable 'v2' is possibly undefined
// 40170C: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50ECA4: using guessed type int (*off_50ECA4[2])();

//----- (00401720) --------------------------------------------------------
_DWORD * PathEntryArray_DestructElements(_DWORD *result)
{
  _DWORD *v1; // ecx
  int v2; // edi
  int v3; // esi
  int v4; // ebx
  int v5; // ebp
  _DWORD *v6; // ecx
  int v7; // [esp+4h] [ebp-14h] BYREF
  int (**v8)(); // [esp+8h] [ebp-10h]
  int v9; // [esp+Ch] [ebp-Ch]

  v1 = result;
  if ( *result )
  {
    v2 = 0;
    if ( (int)result[2] > 0 )
    {
      v3 = 0;
      do
      {
        v4 = v3 + *v1;
        v5 = v1[4];
        v7 = 0;
        v8 = &g_CompatStringHolder_Vtable;
        Compat_StringHolderDestructor(&v7);
        v8 = &g_PathEntry_Vtable;
        v9 = *(_DWORD *)(v4 + 12);
        (*(void (**)(void))(v5 + 4))();
        ++v2;
        Compat_StringHolderScalarDeletingDtor((int)&v7, 0);
        v3 += 16;
      }
      while ( v2 < v1[2] );
    }
    _wcpp_4_dtor_array_store__(v1, &g_PathEntryArray_ElementDtorDescriptor);
    result = (_DWORD *)j_j__nfree_();
    *v6 = 0;
    v6[2] = 0;
    v6[3] = 0;
  }
  return result;
}
// 40173F: variable 'v1' is possibly undefined
// 4017B1: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004017D0) --------------------------------------------------------
int  PathEntryArray_GrowByDelta(int *a1, int a2)
{
  bool v4; // zf
  int v6; // eax
  int v7; // ecx
  _DWORD *v8; // ebx
  _DWORD *v9; // esi
  _DWORD *v10; // edi
  int result; // eax
  int v14; // [esp+0h] [ebp-Ch]

  v4 = a2 + a1[3] == 0;
  a1[3] = a2 + a1[3];
  if ( v4 )
  {
    _wcpp_4_dtor_array_store__(*a1, &g_PathEntryArray_ElementDtorDescriptor);
    result = j_j__nfree_();
    *a1 = 0;
  }
  else
  {
    v6 = Compat_WcppCtorArrayStorage1s(
           (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(16 * a1[3] + 4),
           a1[3],
           &g_PathEntryArray_ElementDtorDescriptor);
    v14 = v6;
    v7 = 0;
    if ( a1[2] > 0 )
    {
      v8 = (_DWORD *)(v6 + 4);
      do
      {
        v9 = (_DWORD *)(16 * v7 + *a1);
        v10 = (_DWORD *)(v14 + 16 * v7);
        *v10 = *v9;
        Compat_StringHolderCopyText(v8, Compat_StringHolderGetText(v9 + 1));
        v10[3] = v9[3];
        ++v7;
        v8 += 4;
      }
      while ( v7 < a1[2] );
    }
    _wcpp_4_dtor_array_store__(*a1, &g_PathEntryArray_ElementDtorDescriptor);
    j_j__nfree_();
    result = v14;
    *a1 = v14;
  }
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00401890) --------------------------------------------------------
_DWORD * PathEntryArray_RemoveAt(_DWORD *result, int a2, int a3)
{
  _DWORD *v3; // ebp
  int v6; // edi
  _DWORD *v7; // ebx
  _DWORD *v8; // esi
  int v10; // esi
  int *v11; // ebx
  int v12; // [esp+0h] [ebp-20h]
  int v13; // [esp+4h] [ebp-1Ch] BYREF
  int (**v14)(); // [esp+8h] [ebp-18h]
  int v15; // [esp+Ch] [ebp-14h]

  v3 = result;
  if ( a3 )
  {
    v10 = result[4];
    v11 = (int *)(*result + 16 * a2);
    v12 = *v11;
    v13 = 0;
    v14 = &g_CompatStringHolder_Vtable;
    Compat_StringHolderCopyText((_DWORD *)&v13, Compat_StringHolderGetText((_DWORD *)(v11 + 1)));
    v14 = &g_PathEntry_Vtable;
    v15 = v11[3];
    (*(void (__cdecl **)(int))(v10 + 4))(v12);
    result = (_DWORD *)Compat_StringHolderScalarDeletingDtor((int)&v13, 0);
  }
  a2 += 1;
  if ( a2 < v3[2] )
  {
    v6 = 16 * a2 - 16;
    do
    {
      v7 = (_DWORD *)(*v3 + 16 * a2);
      v8 = (_DWORD *)(v6 + *v3);
      *v8 = *v7;
      Compat_StringHolderCopyText(v8 + 1, Compat_StringHolderGetText(v7 + 1));
      result = (_DWORD *)v7[3];
      v8[3] = result;
      ++a2;
      v6 += 16;
    }
    while ( a2 < v3[2] );
  }
  --v3[2];
  return result;
}
// 40189F: variable 'v4' is possibly undefined
// 4018D0: variable 'v9' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00401940) --------------------------------------------------------
_DWORD * Mem_ZeroFieldOffset316(int a1)
{
  _DWORD *v1; // eax

  v1 = (_DWORD *)(a1 + 316);
  *v1 = 0;
  return v1 - 79;
}

//----- (00401970) --------------------------------------------------------
int  PathEntry_CopyConstruct(_DWORD *a1, _DWORD *a2)
{
  *a1 = *a2;
  a1[1] = 0;
  a1[2] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderCopyText(a1 + 1, Compat_StringHolderGetText(a2 + 1));
  a1[2] = &g_PathEntry_Vtable;
  a1[3] = a2[3];
  return (int)a1;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004019C0) --------------------------------------------------------
int  PathEntry_Destruct(int a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_PathEntry_DtorDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = Compat_StringHolderScalarDeletingDtor(a1, 1);
    if ( (a2 & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 4019F0: variable 'v4' is possibly undefined
// 4019FA: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00401A00) --------------------------------------------------------
int  PathEntry_ConstructDefault(_DWORD *a1)
{
  _DWORD *v1; // eax
  int v2; // ecx
  int result; // eax

  *a1 = 0;
  a1[1] = 0;
  v1 = a1 + 1;
  v1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(v1);
  result = v2 - 4;
  *(_DWORD *)(v2 + 4) = &g_PathEntry_Vtable;
  *(_DWORD *)(v2 - 4 + 12) = 0;
  return result;
}
// 401A24: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

