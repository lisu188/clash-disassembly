/* Generated from src/recovered/core/004015A0_utilities.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004015A0) --------------------------------------------------------
int  Str_ConstructHolderViaBaseCtor(_DWORD *holder)
{
  int holderBase; // ecx
  int result; // eax

  *holder = 0;
  holder[1] = (_DWORD)(uintptr_t)&g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(holder);
  result = holderBase;
  *(_DWORD *)(holderBase + 4) = (_DWORD)(uintptr_t)&g_PathEntry_Vtable;
  return result;
}
// 4015B7: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004015D0) --------------------------------------------------------
_DWORD * Str_ConstructHolderInline(_DWORD *result)
{
  *result = 0;
  result[1] = (_DWORD)(uintptr_t)&g_CompatStringHolder_Vtable;
  result[1] = (_DWORD)(uintptr_t)&g_PathEntry_Vtable;
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
  return _wcpp_4_ctor_array__((_DWORD)(uintptr_t)this, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (00401640) --------------------------------------------------------
int * PathEntryArray_CopyConstruct(int *dest, _DWORD *source, int a3)
{
  int capacity; // eax
  int index; // edi
  int storage; // eax
  int count; // ecx
  int byteOffset; // ecx
  _DWORD *srcEntry; // ebx
  _DWORD *destEntry; // esi
  int v12; // ecx

  dest[4] = (int)g_PathEntryArray_Vtable;
  dest[1] = source[1];
  dest[2] = source[2];
  capacity = source[3];
  dest[3] = capacity;
  if ( !capacity )
  {
    *dest = 0;
    return dest;
  }
  (void)a3;
  index = 0;
  storage = Compat_WcppCtorArrayStorage1s(
         (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(16 * dest[3] + 4),
         dest[3],
         &g_PathEntryArray_ElementDtorDescriptor);
  count = dest[2];
  *dest = storage;
  if ( count <= 0 )
    return dest;
  byteOffset = 0;
  do
  {
    srcEntry = (_DWORD *)(byteOffset + *source);
    destEntry = (_DWORD *)(byteOffset + *dest);
    *destEntry = *srcEntry;
    Compat_StringHolderDestructor(destEntry + 1);
    destEntry[3] = srcEntry[3];
    ++index;
    byteOffset += 16;
  }
  while ( index < dest[2] );
  return dest;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 50ECA4: using guessed type int (*off_50ECA4[2])();

//----- (004016E0) --------------------------------------------------------
int  PathEntryArray_Destruct(_DWORD *array, char dtorFlags)
{
  int v2; // ecx
  char v3; // dl
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__((_DWORD)(uintptr_t)array, (_DWORD)(uintptr_t)&g_PathEntryArray_DtorDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    array[4] = (_DWORD)(uintptr_t)g_PathEntryArray_Vtable;
    PathEntryArray_DestructElements(array);
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
  _DWORD *array; // ecx
  int index; // edi
  int byteOffset; // esi
  int entryAddr; // ebx
  int vtable; // ebp
  _DWORD *v6; // ecx
  int tempEntry; // [esp+4h] [ebp-14h] BYREF
  int (**tempEntryVtable)(); // [esp+8h] [ebp-10h]
  int tempEntryData; // [esp+Ch] [ebp-Ch]

  array = result;
  if ( *result )
  {
    index = 0;
    if ( (int)result[2] > 0 )
    {
      byteOffset = 0;
      do
      {
        entryAddr = byteOffset + *array;
        vtable = array[4];
        tempEntry = 0;
        tempEntryVtable = &g_CompatStringHolder_Vtable;
        Compat_StringHolderDestructor(&tempEntry);
        tempEntryVtable = &g_PathEntry_Vtable;
        tempEntryData = *(_DWORD *)(entryAddr + 12);
        (*(void (**)(void))(vtable + 4))();
        ++index;
        Compat_StringHolderScalarDeletingDtor((int)&tempEntry, 0);
        byteOffset += 16;
      }
      while ( index < array[2] );
    }
    _wcpp_4_dtor_array_store__((_DWORD)(uintptr_t)array, (_DWORD)(uintptr_t)&g_PathEntryArray_ElementDtorDescriptor);
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
int  PathEntryArray_GrowByDelta(int *array, int delta)
{
  bool becameEmpty; // zf
  int allocated; // eax
  int index; // ecx
  _DWORD *destHolder; // ebx
  _DWORD *srcEntry; // esi
  _DWORD *destEntry; // edi
  int result; // eax
  int newStorage; // [esp+0h] [ebp-Ch]

  becameEmpty = delta + array[3] == 0;
  array[3] = delta + array[3];
  if ( becameEmpty )
  {
    _wcpp_4_dtor_array_store__(*array, (_DWORD)(uintptr_t)&g_PathEntryArray_ElementDtorDescriptor);
    result = j_j__nfree_();
    *array = 0;
  }
  else
  {
    allocated = Compat_WcppCtorArrayStorage1s(
           (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(16 * array[3] + 4),
           array[3],
           &g_PathEntryArray_ElementDtorDescriptor);
    newStorage = allocated;
    index = 0;
    if ( array[2] > 0 )
    {
      destHolder = (_DWORD *)(allocated + 4);
      do
      {
        srcEntry = (_DWORD *)(16 * index + *array);
        destEntry = (_DWORD *)(newStorage + 16 * index);
        *destEntry = *srcEntry;
        Compat_StringHolderCopyText(destHolder, Compat_StringHolderGetText(srcEntry + 1));
        destEntry[3] = srcEntry[3];
        ++index;
        destHolder += 4;
      }
      while ( index < array[2] );
    }
    _wcpp_4_dtor_array_store__(*array, (_DWORD)(uintptr_t)&g_PathEntryArray_ElementDtorDescriptor);
    j_j__nfree_();
    result = newStorage;
    *array = newStorage;
  }
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00401890) --------------------------------------------------------
_DWORD * PathEntryArray_RemoveAt(_DWORD *result, int index, int destroyElement)
{
  _DWORD *array; // ebp
  int destOffset; // edi
  _DWORD *srcEntry; // ebx
  _DWORD *destEntry; // esi
  int vtable; // esi
  int *removedEntry; // ebx
  int removedValue; // [esp+0h] [ebp-20h]
  int tempEntry; // [esp+4h] [ebp-1Ch] BYREF
  int (**tempEntryVtable)(); // [esp+8h] [ebp-18h]
  int tempEntryData; // [esp+Ch] [ebp-14h]

  array = result;
  if ( destroyElement )
  {
    vtable = result[4];
    removedEntry = (int *)(*result + 16 * index);
    removedValue = *removedEntry;
    tempEntry = 0;
    tempEntryVtable = &g_CompatStringHolder_Vtable;
    Compat_StringHolderCopyText((_DWORD *)&tempEntry, Compat_StringHolderGetText((_DWORD *)(removedEntry + 1)));
    tempEntryVtable = &g_PathEntry_Vtable;
    tempEntryData = removedEntry[3];
    (*(void (__cdecl **)(int))(vtable + 4))(removedValue);
    result = (_DWORD *)Compat_StringHolderScalarDeletingDtor((int)&tempEntry, 0);
  }
  index += 1;
  if ( index < array[2] )
  {
    destOffset = 16 * index - 16;
    do
    {
      srcEntry = (_DWORD *)(*array + 16 * index);
      destEntry = (_DWORD *)(destOffset + *array);
      *destEntry = *srcEntry;
      Compat_StringHolderCopyText(destEntry + 1, Compat_StringHolderGetText(srcEntry + 1));
      result = (_DWORD *)srcEntry[3];
      destEntry[3] = (_DWORD)(uintptr_t)result;
      ++index;
      destOffset += 16;
    }
    while ( index < array[2] );
  }
  --array[2];
  return result;
}
// 40189F: variable 'v4' is possibly undefined
// 4018D0: variable 'v9' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00401940) --------------------------------------------------------
_DWORD * Mem_ZeroFieldOffset316(int objectBase)
{
  _DWORD *fieldPtr; // eax

  fieldPtr = (_DWORD *)(objectBase + 316);
  *fieldPtr = 0;
  return fieldPtr - 79;
}

//----- (00401970) --------------------------------------------------------
int  PathEntry_CopyConstruct(_DWORD *dest, _DWORD *source)
{
  *dest = *source;
  dest[1] = 0;
  dest[2] = (_DWORD)(uintptr_t)&g_CompatStringHolder_Vtable;
  Compat_StringHolderCopyText(dest + 1, Compat_StringHolderGetText(source + 1));
  dest[2] = (_DWORD)(uintptr_t)&g_PathEntry_Vtable;
  dest[3] = source[3];
  return (int)dest;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004019C0) --------------------------------------------------------
int  PathEntry_Destruct(int entry, char dtorFlags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(entry, (_DWORD)(uintptr_t)&g_PathEntry_DtorDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = Compat_StringHolderScalarDeletingDtor(entry, 1);
    if ( (dtorFlags & 2) != 0 )
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
int  PathEntry_ConstructDefault(_DWORD *entry)
{
  _DWORD *holder; // eax
  int holderBase; // ecx
  int result; // eax

  *entry = 0;
  entry[1] = 0;
  holder = entry + 1;
  holder[1] = (_DWORD)(uintptr_t)&g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(holder);
  result = holderBase - 4;
  *(_DWORD *)(holderBase + 4) = (_DWORD)(uintptr_t)&g_PathEntry_Vtable;
  *(_DWORD *)(holderBase - 4 + 12) = 0;
  return result;
}
// 401A24: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
